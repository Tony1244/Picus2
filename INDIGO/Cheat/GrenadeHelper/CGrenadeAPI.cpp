#include "CGrenadeAPI.h"

CGrenadeAPI cGrenade;

std::string CGrenadeAPI::parseString(std::string szBefore, std::string szAfter, std::string szSource)
{
	if (!szBefore.empty() && !szAfter.empty() && !szSource.empty() && (szSource.find(szBefore) != std::string::npos) && (szSource.find(szAfter) != std::string::npos))
	{
		std::string t = strstr(szSource.c_str(), szBefore.c_str());
		t.erase(0, szBefore.length());
		std::string::size_type loc = t.find(szAfter, 0);
		t = t.substr(0, loc);
		return t;
	}
	else
		return "";
}

std::string CGrenadeAPI::HttpGet(std::string hostaddr, std::string api)
{
	std::string request;
	std::string response;
	int resp_leng;
	char buffer[1024];
	struct sockaddr_in serveraddr;
	int sock;
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		printf("WSAStartup() failed\r\n");

	struct hostent *host;
	host = gethostbyname(hostaddr.c_str());

	int port = 80;
	request += "GET " + api + " HTTP/1.0\r\n";
	request += "Host: " + hostaddr + "\r\n";
	request += "User-Agent: GRENADE API [Build: 1.0.0] \r\n";
	request += "\r\n";

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("socket() failed\r\n");

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;

	serveraddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	serveraddr.sin_port = htons((unsigned short)port);

	struct in_addr **addr_list;

	addr_list = (struct in_addr **) host->h_addr_list;

	response = "";

	if (connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
		printf("connect() failed\r\n");

	if (send(sock, request.c_str(), request.length(), 0) != request.length())
		printf("send() sent a different number of bytes than expected\r\n");

	resp_leng = 1024;

	while (resp_leng > 0)
	{

		resp_leng = recv(sock, (char*)&buffer, 1024, 0);

		if (resp_leng > 0)
			response += std::string(buffer).substr(0, resp_leng);
	}

	closesocket(sock);
	WSACleanup();
	return response;
}

bool CGrenadeAPI::bUpdateGrenadeInfo(std::string szMapName)
{

	this->GrenadeInfo.clear();

	std::string responce = this->HttpGet(this->szHost, this->szApi + szMapName);
	if (responce.empty())
		return false;

	if (!this->parseString("<error>", "</error>", responce).empty())
		return false;

	int i = 0;

	while (true)
	{
		if (responce.find("<id>" + std::to_string(i) + "</id>") == std::string::npos)
			break;

		std::string szParseId = this->parseString("<id>", "</id>", responce);
		std::string szParseName = this->parseString("<name>", "</name>", responce);
		std::string szParseDescription = this->parseString("<description>", "</description>", responce);
		std::string szParseWeapon = this->parseString("<grenade>", "</grenade>", responce);

		std::string szParseOriginx = this->parseString("<player_x>", "</player_x>", responce);
		std::string szParseOriginy = this->parseString("<player_y>", "</player_y>", responce);
		std::string szParseOriginz = this->parseString("<player_z>", "</player_z>", responce);

		std::string szParseViewx = this->parseString("<view_x>", "</view_x>", responce);
		std::string szParseViewy = this->parseString("<view_y>", "</view_y>", responce);

		if (szParseId.empty() || szParseName.empty() || szParseDescription.empty() || szParseWeapon.empty())
			break;

		GrenadeInfo_t info;

		info.id = atoi(szParseId.c_str());
		info.szName = szParseName;
		info.szDescription = szParseDescription;
		info.szWeapon = szParseWeapon;
		info.vecOrigin = SDK::Vector(atof(szParseOriginx.c_str()), atof(szParseOriginy.c_str()), atof(szParseOriginz.c_str()));
		info.vecViewangles = SDK::Vector(atof(szParseViewx.c_str()), atof(szParseViewy.c_str()), 0);
		info.vecOrigin.z -= 64.f;

		GrenadeInfo.push_back(info);

		size_t nPos = responce.find("</view_y>");
		responce.erase(0, nPos + 7);

		i++;

	}
	return true;
}

bool CGrenadeAPI::GetInfo(int iNum, GrenadeInfo_t * info)
{
	if (iNum < 0 || iNum > GrenadeInfo.size())
		return false;

	if (GrenadeInfo.at(iNum).id > 0 && !GrenadeInfo.at(iNum).szDescription.empty() && !GrenadeInfo.at(iNum).szName.empty() && !GrenadeInfo.at(iNum).szWeapon.empty())
	{
		*info = GrenadeInfo.at(iNum);
		return true;
	}
	else return false;
}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PIATKSUPZH
{ 
  void jetEhCVlcF()
  { 
      bool rSZnXeVMHr = false;
      bool eWTjXHBBOF = false;
      bool AVgFVZjNhz = false;
      bool RABWruykjN = false;
      bool IlVHdDtaRR = false;
      bool tYUcmVkUSx = false;
      bool tHdIaeUxqb = false;
      bool IPQBxOAZaR = false;
      bool fIwQErfYiW = false;
      bool JcSmTBHNfz = false;
      bool hxjpJeISeY = false;
      bool VLtARkKNDh = false;
      bool ywNURexdhw = false;
      bool GlsaiiYGHY = false;
      bool jMsKAyiRVh = false;
      bool ptJxBliOXd = false;
      bool hdkiRiSSRh = false;
      bool LEGeykCDUT = false;
      bool ueIzFMbuZx = false;
      bool zKhcqFbKrQ = false;
      string TmIDdUlMBC;
      string xIImKHXIQe;
      string QyDwAJNeGm;
      string XIOAeIcfiB;
      string JJwABjRnAe;
      string lMtwtViLDU;
      string HGGNdosIIC;
      string eqZPVGBCuP;
      string qYdbAKNRFI;
      string YQcOtCDhVL;
      string pJeyAumdam;
      string TgQmdhbeNT;
      string aaCAcOOLUS;
      string DTfjYgsfaF;
      string XjqSnrzokM;
      string aYUCjPGeUl;
      string fbJHjAAgOw;
      string nuDHuqjjLk;
      string OYZIrdzdzJ;
      string ZNLoYwZihn;
      if(TmIDdUlMBC == pJeyAumdam){rSZnXeVMHr = true;}
      else if(pJeyAumdam == TmIDdUlMBC){hxjpJeISeY = true;}
      if(xIImKHXIQe == TgQmdhbeNT){eWTjXHBBOF = true;}
      else if(TgQmdhbeNT == xIImKHXIQe){VLtARkKNDh = true;}
      if(QyDwAJNeGm == aaCAcOOLUS){AVgFVZjNhz = true;}
      else if(aaCAcOOLUS == QyDwAJNeGm){ywNURexdhw = true;}
      if(XIOAeIcfiB == DTfjYgsfaF){RABWruykjN = true;}
      else if(DTfjYgsfaF == XIOAeIcfiB){GlsaiiYGHY = true;}
      if(JJwABjRnAe == XjqSnrzokM){IlVHdDtaRR = true;}
      else if(XjqSnrzokM == JJwABjRnAe){jMsKAyiRVh = true;}
      if(lMtwtViLDU == aYUCjPGeUl){tYUcmVkUSx = true;}
      else if(aYUCjPGeUl == lMtwtViLDU){ptJxBliOXd = true;}
      if(HGGNdosIIC == fbJHjAAgOw){tHdIaeUxqb = true;}
      else if(fbJHjAAgOw == HGGNdosIIC){hdkiRiSSRh = true;}
      if(eqZPVGBCuP == nuDHuqjjLk){IPQBxOAZaR = true;}
      if(qYdbAKNRFI == OYZIrdzdzJ){fIwQErfYiW = true;}
      if(YQcOtCDhVL == ZNLoYwZihn){JcSmTBHNfz = true;}
      while(nuDHuqjjLk == eqZPVGBCuP){LEGeykCDUT = true;}
      while(OYZIrdzdzJ == OYZIrdzdzJ){ueIzFMbuZx = true;}
      while(ZNLoYwZihn == ZNLoYwZihn){zKhcqFbKrQ = true;}
      if(rSZnXeVMHr == true){rSZnXeVMHr = false;}
      if(eWTjXHBBOF == true){eWTjXHBBOF = false;}
      if(AVgFVZjNhz == true){AVgFVZjNhz = false;}
      if(RABWruykjN == true){RABWruykjN = false;}
      if(IlVHdDtaRR == true){IlVHdDtaRR = false;}
      if(tYUcmVkUSx == true){tYUcmVkUSx = false;}
      if(tHdIaeUxqb == true){tHdIaeUxqb = false;}
      if(IPQBxOAZaR == true){IPQBxOAZaR = false;}
      if(fIwQErfYiW == true){fIwQErfYiW = false;}
      if(JcSmTBHNfz == true){JcSmTBHNfz = false;}
      if(hxjpJeISeY == true){hxjpJeISeY = false;}
      if(VLtARkKNDh == true){VLtARkKNDh = false;}
      if(ywNURexdhw == true){ywNURexdhw = false;}
      if(GlsaiiYGHY == true){GlsaiiYGHY = false;}
      if(jMsKAyiRVh == true){jMsKAyiRVh = false;}
      if(ptJxBliOXd == true){ptJxBliOXd = false;}
      if(hdkiRiSSRh == true){hdkiRiSSRh = false;}
      if(LEGeykCDUT == true){LEGeykCDUT = false;}
      if(ueIzFMbuZx == true){ueIzFMbuZx = false;}
      if(zKhcqFbKrQ == true){zKhcqFbKrQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJWEFTKGRY
{ 
  void QqbBsaMVtZ()
  { 
      bool PtKDVeEZJZ = false;
      bool HhbKfrcYbd = false;
      bool ssIrVSUsAK = false;
      bool IMFEdRakqm = false;
      bool yTwcthaVGk = false;
      bool nAXtaWkRhC = false;
      bool KKZzQtcXfO = false;
      bool QqgoeZxfxm = false;
      bool rymPVIoKcH = false;
      bool fJCobmtwLz = false;
      bool FDpqTxShOB = false;
      bool ZFTuKMXKdI = false;
      bool FRtXhHorNr = false;
      bool fAUxhnIuwY = false;
      bool oHubhaoHdO = false;
      bool PjSCtmIRIL = false;
      bool HaUWVYjWNV = false;
      bool EbOFTyWRpH = false;
      bool SgNycuhRDt = false;
      bool epljQOmXGI = false;
      string OSkiVVYyZK;
      string IrozLDAeJX;
      string ioiESgEkwL;
      string QOxeUrJltk;
      string GzCrsUGOiF;
      string iiOKEYigPo;
      string RnCNsstKdT;
      string tNkXRjmqKy;
      string ZoBpchAmZu;
      string IbWFTSwoyA;
      string awjPKUxpsU;
      string lrVRPblLkL;
      string rGjiKRqeEy;
      string myrKWcFkfH;
      string jKtFIPFFpr;
      string fjDlHTMBFr;
      string dRktgnzLtl;
      string WAfdbhMdZt;
      string LloMRCtGCC;
      string QDfmcRYzYU;
      if(OSkiVVYyZK == awjPKUxpsU){PtKDVeEZJZ = true;}
      else if(awjPKUxpsU == OSkiVVYyZK){FDpqTxShOB = true;}
      if(IrozLDAeJX == lrVRPblLkL){HhbKfrcYbd = true;}
      else if(lrVRPblLkL == IrozLDAeJX){ZFTuKMXKdI = true;}
      if(ioiESgEkwL == rGjiKRqeEy){ssIrVSUsAK = true;}
      else if(rGjiKRqeEy == ioiESgEkwL){FRtXhHorNr = true;}
      if(QOxeUrJltk == myrKWcFkfH){IMFEdRakqm = true;}
      else if(myrKWcFkfH == QOxeUrJltk){fAUxhnIuwY = true;}
      if(GzCrsUGOiF == jKtFIPFFpr){yTwcthaVGk = true;}
      else if(jKtFIPFFpr == GzCrsUGOiF){oHubhaoHdO = true;}
      if(iiOKEYigPo == fjDlHTMBFr){nAXtaWkRhC = true;}
      else if(fjDlHTMBFr == iiOKEYigPo){PjSCtmIRIL = true;}
      if(RnCNsstKdT == dRktgnzLtl){KKZzQtcXfO = true;}
      else if(dRktgnzLtl == RnCNsstKdT){HaUWVYjWNV = true;}
      if(tNkXRjmqKy == WAfdbhMdZt){QqgoeZxfxm = true;}
      if(ZoBpchAmZu == LloMRCtGCC){rymPVIoKcH = true;}
      if(IbWFTSwoyA == QDfmcRYzYU){fJCobmtwLz = true;}
      while(WAfdbhMdZt == tNkXRjmqKy){EbOFTyWRpH = true;}
      while(LloMRCtGCC == LloMRCtGCC){SgNycuhRDt = true;}
      while(QDfmcRYzYU == QDfmcRYzYU){epljQOmXGI = true;}
      if(PtKDVeEZJZ == true){PtKDVeEZJZ = false;}
      if(HhbKfrcYbd == true){HhbKfrcYbd = false;}
      if(ssIrVSUsAK == true){ssIrVSUsAK = false;}
      if(IMFEdRakqm == true){IMFEdRakqm = false;}
      if(yTwcthaVGk == true){yTwcthaVGk = false;}
      if(nAXtaWkRhC == true){nAXtaWkRhC = false;}
      if(KKZzQtcXfO == true){KKZzQtcXfO = false;}
      if(QqgoeZxfxm == true){QqgoeZxfxm = false;}
      if(rymPVIoKcH == true){rymPVIoKcH = false;}
      if(fJCobmtwLz == true){fJCobmtwLz = false;}
      if(FDpqTxShOB == true){FDpqTxShOB = false;}
      if(ZFTuKMXKdI == true){ZFTuKMXKdI = false;}
      if(FRtXhHorNr == true){FRtXhHorNr = false;}
      if(fAUxhnIuwY == true){fAUxhnIuwY = false;}
      if(oHubhaoHdO == true){oHubhaoHdO = false;}
      if(PjSCtmIRIL == true){PjSCtmIRIL = false;}
      if(HaUWVYjWNV == true){HaUWVYjWNV = false;}
      if(EbOFTyWRpH == true){EbOFTyWRpH = false;}
      if(SgNycuhRDt == true){SgNycuhRDt = false;}
      if(epljQOmXGI == true){epljQOmXGI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCSPVPOQJR
{ 
  void oCXaKXBWrh()
  { 
      bool zdmLIgfupE = false;
      bool qSEnUaimbN = false;
      bool lfQDROyopd = false;
      bool QhkFXSVlmh = false;
      bool VaynwAqAwp = false;
      bool QnscETMjtt = false;
      bool iqEMmJhzQB = false;
      bool ExztqKhcHR = false;
      bool WyrANcnHAD = false;
      bool GlqsyeVkAl = false;
      bool SritkTozls = false;
      bool ljbcWkyEzK = false;
      bool VZyNuSFFuM = false;
      bool nwcVydOyOs = false;
      bool nnVGQWKOWN = false;
      bool fRloQstUzS = false;
      bool OjEYFpGGdr = false;
      bool VAoFWgDqwY = false;
      bool HphggWJmEF = false;
      bool jtyweEjxBa = false;
      string XSmabVtqnF;
      string OFhpOBTsVp;
      string SwuzHcUBPy;
      string iCCiKWbYyc;
      string ACFEKNfawc;
      string UXrQVaWnTz;
      string BraoWLCyer;
      string ZturpPqqns;
      string xsFmdKJlNi;
      string zmFzbHaPgy;
      string KgwEDZczZF;
      string jezZBHmnLL;
      string CPkurlouQi;
      string oaKoiPxAiD;
      string gJMHzUnexT;
      string TlEUwuwALR;
      string kgiqQIUJqk;
      string KlFIdrDcwX;
      string xJywOCWorm;
      string TwnQRAaVqp;
      if(XSmabVtqnF == KgwEDZczZF){zdmLIgfupE = true;}
      else if(KgwEDZczZF == XSmabVtqnF){SritkTozls = true;}
      if(OFhpOBTsVp == jezZBHmnLL){qSEnUaimbN = true;}
      else if(jezZBHmnLL == OFhpOBTsVp){ljbcWkyEzK = true;}
      if(SwuzHcUBPy == CPkurlouQi){lfQDROyopd = true;}
      else if(CPkurlouQi == SwuzHcUBPy){VZyNuSFFuM = true;}
      if(iCCiKWbYyc == oaKoiPxAiD){QhkFXSVlmh = true;}
      else if(oaKoiPxAiD == iCCiKWbYyc){nwcVydOyOs = true;}
      if(ACFEKNfawc == gJMHzUnexT){VaynwAqAwp = true;}
      else if(gJMHzUnexT == ACFEKNfawc){nnVGQWKOWN = true;}
      if(UXrQVaWnTz == TlEUwuwALR){QnscETMjtt = true;}
      else if(TlEUwuwALR == UXrQVaWnTz){fRloQstUzS = true;}
      if(BraoWLCyer == kgiqQIUJqk){iqEMmJhzQB = true;}
      else if(kgiqQIUJqk == BraoWLCyer){OjEYFpGGdr = true;}
      if(ZturpPqqns == KlFIdrDcwX){ExztqKhcHR = true;}
      if(xsFmdKJlNi == xJywOCWorm){WyrANcnHAD = true;}
      if(zmFzbHaPgy == TwnQRAaVqp){GlqsyeVkAl = true;}
      while(KlFIdrDcwX == ZturpPqqns){VAoFWgDqwY = true;}
      while(xJywOCWorm == xJywOCWorm){HphggWJmEF = true;}
      while(TwnQRAaVqp == TwnQRAaVqp){jtyweEjxBa = true;}
      if(zdmLIgfupE == true){zdmLIgfupE = false;}
      if(qSEnUaimbN == true){qSEnUaimbN = false;}
      if(lfQDROyopd == true){lfQDROyopd = false;}
      if(QhkFXSVlmh == true){QhkFXSVlmh = false;}
      if(VaynwAqAwp == true){VaynwAqAwp = false;}
      if(QnscETMjtt == true){QnscETMjtt = false;}
      if(iqEMmJhzQB == true){iqEMmJhzQB = false;}
      if(ExztqKhcHR == true){ExztqKhcHR = false;}
      if(WyrANcnHAD == true){WyrANcnHAD = false;}
      if(GlqsyeVkAl == true){GlqsyeVkAl = false;}
      if(SritkTozls == true){SritkTozls = false;}
      if(ljbcWkyEzK == true){ljbcWkyEzK = false;}
      if(VZyNuSFFuM == true){VZyNuSFFuM = false;}
      if(nwcVydOyOs == true){nwcVydOyOs = false;}
      if(nnVGQWKOWN == true){nnVGQWKOWN = false;}
      if(fRloQstUzS == true){fRloQstUzS = false;}
      if(OjEYFpGGdr == true){OjEYFpGGdr = false;}
      if(VAoFWgDqwY == true){VAoFWgDqwY = false;}
      if(HphggWJmEF == true){HphggWJmEF = false;}
      if(jtyweEjxBa == true){jtyweEjxBa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVEYOYYTTW
{ 
  void igeGYXrVSV()
  { 
      bool aOSWLaGfBU = false;
      bool HSsGsmkEKr = false;
      bool XKEZSqbSdy = false;
      bool PMdbUQYzUe = false;
      bool hiKCFsCsau = false;
      bool YUkKKQJsDT = false;
      bool ymBDFunQkc = false;
      bool NlifKozCTY = false;
      bool oirhZuaTRD = false;
      bool GfuBftgHwK = false;
      bool FkHxhmkFAV = false;
      bool QGYddPuScJ = false;
      bool TUzhVhphzP = false;
      bool HrFJTEatAm = false;
      bool JVTulAGRWQ = false;
      bool yOdmqjkZbA = false;
      bool wDFjOYAPJZ = false;
      bool nBRpAxBDuV = false;
      bool aYKiQrOSSj = false;
      bool SARApGQigN = false;
      string sTZzjtLhRY;
      string cHkmgahqZz;
      string GURYOLUhKw;
      string AEzWotCJUK;
      string JyqJgwfiiU;
      string CCeNXYBBkX;
      string YcWVYXIOxl;
      string XXVPoIdIqS;
      string elzpsyYlyQ;
      string rBYwkgaVkJ;
      string mQlwwefPYO;
      string tsJSsmdgba;
      string zWQgtWzYdH;
      string hHWheNACsO;
      string RJMiVyqGCy;
      string CssKKQAECY;
      string eHkQglWbmf;
      string mbmNIoJgLw;
      string frVfFnOMWN;
      string MuzTiKYwCi;
      if(sTZzjtLhRY == mQlwwefPYO){aOSWLaGfBU = true;}
      else if(mQlwwefPYO == sTZzjtLhRY){FkHxhmkFAV = true;}
      if(cHkmgahqZz == tsJSsmdgba){HSsGsmkEKr = true;}
      else if(tsJSsmdgba == cHkmgahqZz){QGYddPuScJ = true;}
      if(GURYOLUhKw == zWQgtWzYdH){XKEZSqbSdy = true;}
      else if(zWQgtWzYdH == GURYOLUhKw){TUzhVhphzP = true;}
      if(AEzWotCJUK == hHWheNACsO){PMdbUQYzUe = true;}
      else if(hHWheNACsO == AEzWotCJUK){HrFJTEatAm = true;}
      if(JyqJgwfiiU == RJMiVyqGCy){hiKCFsCsau = true;}
      else if(RJMiVyqGCy == JyqJgwfiiU){JVTulAGRWQ = true;}
      if(CCeNXYBBkX == CssKKQAECY){YUkKKQJsDT = true;}
      else if(CssKKQAECY == CCeNXYBBkX){yOdmqjkZbA = true;}
      if(YcWVYXIOxl == eHkQglWbmf){ymBDFunQkc = true;}
      else if(eHkQglWbmf == YcWVYXIOxl){wDFjOYAPJZ = true;}
      if(XXVPoIdIqS == mbmNIoJgLw){NlifKozCTY = true;}
      if(elzpsyYlyQ == frVfFnOMWN){oirhZuaTRD = true;}
      if(rBYwkgaVkJ == MuzTiKYwCi){GfuBftgHwK = true;}
      while(mbmNIoJgLw == XXVPoIdIqS){nBRpAxBDuV = true;}
      while(frVfFnOMWN == frVfFnOMWN){aYKiQrOSSj = true;}
      while(MuzTiKYwCi == MuzTiKYwCi){SARApGQigN = true;}
      if(aOSWLaGfBU == true){aOSWLaGfBU = false;}
      if(HSsGsmkEKr == true){HSsGsmkEKr = false;}
      if(XKEZSqbSdy == true){XKEZSqbSdy = false;}
      if(PMdbUQYzUe == true){PMdbUQYzUe = false;}
      if(hiKCFsCsau == true){hiKCFsCsau = false;}
      if(YUkKKQJsDT == true){YUkKKQJsDT = false;}
      if(ymBDFunQkc == true){ymBDFunQkc = false;}
      if(NlifKozCTY == true){NlifKozCTY = false;}
      if(oirhZuaTRD == true){oirhZuaTRD = false;}
      if(GfuBftgHwK == true){GfuBftgHwK = false;}
      if(FkHxhmkFAV == true){FkHxhmkFAV = false;}
      if(QGYddPuScJ == true){QGYddPuScJ = false;}
      if(TUzhVhphzP == true){TUzhVhphzP = false;}
      if(HrFJTEatAm == true){HrFJTEatAm = false;}
      if(JVTulAGRWQ == true){JVTulAGRWQ = false;}
      if(yOdmqjkZbA == true){yOdmqjkZbA = false;}
      if(wDFjOYAPJZ == true){wDFjOYAPJZ = false;}
      if(nBRpAxBDuV == true){nBRpAxBDuV = false;}
      if(aYKiQrOSSj == true){aYKiQrOSSj = false;}
      if(SARApGQigN == true){SARApGQigN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLWBRPCBWG
{ 
  void NgCBuIuIJl()
  { 
      bool RjjXdrwbMM = false;
      bool thxVrYbKnN = false;
      bool ocjgkrbIjf = false;
      bool xejCFiWKcW = false;
      bool PqHHzOXVBR = false;
      bool FlABBoACmk = false;
      bool QmqfOOyuPJ = false;
      bool CQhRyxVbgV = false;
      bool UFHSaLehAP = false;
      bool iTXqGcAark = false;
      bool QbFrPnDiDE = false;
      bool SXVRQKfYFD = false;
      bool jQuAaisqKV = false;
      bool wujuErzODl = false;
      bool HuduxKxGZu = false;
      bool waUoBAgFRg = false;
      bool uMXhHXnZMX = false;
      bool LQVSwnlzCP = false;
      bool kmQPYVZutE = false;
      bool LsxVqtWumY = false;
      string mOWVPPHSqy;
      string rcDEOXfAsZ;
      string Wkyxyuymdb;
      string CErkgVtSof;
      string iAOZEMqFXA;
      string JKbVICPYWT;
      string RToOumjRWr;
      string dNKMqWWYsl;
      string EsPdRqcWbe;
      string GUwVOPKzdQ;
      string bYheVwzOdl;
      string fqfkOXDKwE;
      string JMprlIRoxa;
      string LWtbJfKjHV;
      string qOrpzOoKGq;
      string LzDZHOhprM;
      string eKRDZIxEai;
      string MTDaMuUzrW;
      string TGiGOLTTTt;
      string xUqtpgxoPp;
      if(mOWVPPHSqy == bYheVwzOdl){RjjXdrwbMM = true;}
      else if(bYheVwzOdl == mOWVPPHSqy){QbFrPnDiDE = true;}
      if(rcDEOXfAsZ == fqfkOXDKwE){thxVrYbKnN = true;}
      else if(fqfkOXDKwE == rcDEOXfAsZ){SXVRQKfYFD = true;}
      if(Wkyxyuymdb == JMprlIRoxa){ocjgkrbIjf = true;}
      else if(JMprlIRoxa == Wkyxyuymdb){jQuAaisqKV = true;}
      if(CErkgVtSof == LWtbJfKjHV){xejCFiWKcW = true;}
      else if(LWtbJfKjHV == CErkgVtSof){wujuErzODl = true;}
      if(iAOZEMqFXA == qOrpzOoKGq){PqHHzOXVBR = true;}
      else if(qOrpzOoKGq == iAOZEMqFXA){HuduxKxGZu = true;}
      if(JKbVICPYWT == LzDZHOhprM){FlABBoACmk = true;}
      else if(LzDZHOhprM == JKbVICPYWT){waUoBAgFRg = true;}
      if(RToOumjRWr == eKRDZIxEai){QmqfOOyuPJ = true;}
      else if(eKRDZIxEai == RToOumjRWr){uMXhHXnZMX = true;}
      if(dNKMqWWYsl == MTDaMuUzrW){CQhRyxVbgV = true;}
      if(EsPdRqcWbe == TGiGOLTTTt){UFHSaLehAP = true;}
      if(GUwVOPKzdQ == xUqtpgxoPp){iTXqGcAark = true;}
      while(MTDaMuUzrW == dNKMqWWYsl){LQVSwnlzCP = true;}
      while(TGiGOLTTTt == TGiGOLTTTt){kmQPYVZutE = true;}
      while(xUqtpgxoPp == xUqtpgxoPp){LsxVqtWumY = true;}
      if(RjjXdrwbMM == true){RjjXdrwbMM = false;}
      if(thxVrYbKnN == true){thxVrYbKnN = false;}
      if(ocjgkrbIjf == true){ocjgkrbIjf = false;}
      if(xejCFiWKcW == true){xejCFiWKcW = false;}
      if(PqHHzOXVBR == true){PqHHzOXVBR = false;}
      if(FlABBoACmk == true){FlABBoACmk = false;}
      if(QmqfOOyuPJ == true){QmqfOOyuPJ = false;}
      if(CQhRyxVbgV == true){CQhRyxVbgV = false;}
      if(UFHSaLehAP == true){UFHSaLehAP = false;}
      if(iTXqGcAark == true){iTXqGcAark = false;}
      if(QbFrPnDiDE == true){QbFrPnDiDE = false;}
      if(SXVRQKfYFD == true){SXVRQKfYFD = false;}
      if(jQuAaisqKV == true){jQuAaisqKV = false;}
      if(wujuErzODl == true){wujuErzODl = false;}
      if(HuduxKxGZu == true){HuduxKxGZu = false;}
      if(waUoBAgFRg == true){waUoBAgFRg = false;}
      if(uMXhHXnZMX == true){uMXhHXnZMX = false;}
      if(LQVSwnlzCP == true){LQVSwnlzCP = false;}
      if(kmQPYVZutE == true){kmQPYVZutE = false;}
      if(LsxVqtWumY == true){LsxVqtWumY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPBFYLYCEI
{ 
  void zJLyEzlcUk()
  { 
      bool frEjROXkhy = false;
      bool cNUeTXQgcY = false;
      bool HjLXfiFYZo = false;
      bool ORCUTMkazo = false;
      bool xumNXdXXOg = false;
      bool DHduiwggDh = false;
      bool IzLriLKzKH = false;
      bool lohnaMxyAB = false;
      bool LgKrlHnHkX = false;
      bool eEXQfxjteM = false;
      bool SXNGuNZoTW = false;
      bool zifCWboSGb = false;
      bool WDOmbgRQIc = false;
      bool bDTninTDxX = false;
      bool gymOYwXUtE = false;
      bool IRmCoPJZdN = false;
      bool wIgpuuPrSi = false;
      bool HlUhtYPAOf = false;
      bool IwWDUKPQyS = false;
      bool esZjbYQxSc = false;
      string CersYjCqHI;
      string MKEKSVfjJD;
      string LNDxwXgHXK;
      string MTzFDdxEJA;
      string KOHsmbWfGT;
      string JVUBsoauxB;
      string DtTwwrLzGo;
      string XbaJrwFJJT;
      string AABEAqzxMO;
      string CCHHxQuKxu;
      string QXZRuhtKJw;
      string iRlcACrPwF;
      string rNmrlVUSLb;
      string BuMNDcaiIR;
      string wnnPekQdHt;
      string XeOqCCkhfZ;
      string NbzgunEXYX;
      string bJHdJEYWMA;
      string FpLRDVfULB;
      string qsDiEToHUq;
      if(CersYjCqHI == QXZRuhtKJw){frEjROXkhy = true;}
      else if(QXZRuhtKJw == CersYjCqHI){SXNGuNZoTW = true;}
      if(MKEKSVfjJD == iRlcACrPwF){cNUeTXQgcY = true;}
      else if(iRlcACrPwF == MKEKSVfjJD){zifCWboSGb = true;}
      if(LNDxwXgHXK == rNmrlVUSLb){HjLXfiFYZo = true;}
      else if(rNmrlVUSLb == LNDxwXgHXK){WDOmbgRQIc = true;}
      if(MTzFDdxEJA == BuMNDcaiIR){ORCUTMkazo = true;}
      else if(BuMNDcaiIR == MTzFDdxEJA){bDTninTDxX = true;}
      if(KOHsmbWfGT == wnnPekQdHt){xumNXdXXOg = true;}
      else if(wnnPekQdHt == KOHsmbWfGT){gymOYwXUtE = true;}
      if(JVUBsoauxB == XeOqCCkhfZ){DHduiwggDh = true;}
      else if(XeOqCCkhfZ == JVUBsoauxB){IRmCoPJZdN = true;}
      if(DtTwwrLzGo == NbzgunEXYX){IzLriLKzKH = true;}
      else if(NbzgunEXYX == DtTwwrLzGo){wIgpuuPrSi = true;}
      if(XbaJrwFJJT == bJHdJEYWMA){lohnaMxyAB = true;}
      if(AABEAqzxMO == FpLRDVfULB){LgKrlHnHkX = true;}
      if(CCHHxQuKxu == qsDiEToHUq){eEXQfxjteM = true;}
      while(bJHdJEYWMA == XbaJrwFJJT){HlUhtYPAOf = true;}
      while(FpLRDVfULB == FpLRDVfULB){IwWDUKPQyS = true;}
      while(qsDiEToHUq == qsDiEToHUq){esZjbYQxSc = true;}
      if(frEjROXkhy == true){frEjROXkhy = false;}
      if(cNUeTXQgcY == true){cNUeTXQgcY = false;}
      if(HjLXfiFYZo == true){HjLXfiFYZo = false;}
      if(ORCUTMkazo == true){ORCUTMkazo = false;}
      if(xumNXdXXOg == true){xumNXdXXOg = false;}
      if(DHduiwggDh == true){DHduiwggDh = false;}
      if(IzLriLKzKH == true){IzLriLKzKH = false;}
      if(lohnaMxyAB == true){lohnaMxyAB = false;}
      if(LgKrlHnHkX == true){LgKrlHnHkX = false;}
      if(eEXQfxjteM == true){eEXQfxjteM = false;}
      if(SXNGuNZoTW == true){SXNGuNZoTW = false;}
      if(zifCWboSGb == true){zifCWboSGb = false;}
      if(WDOmbgRQIc == true){WDOmbgRQIc = false;}
      if(bDTninTDxX == true){bDTninTDxX = false;}
      if(gymOYwXUtE == true){gymOYwXUtE = false;}
      if(IRmCoPJZdN == true){IRmCoPJZdN = false;}
      if(wIgpuuPrSi == true){wIgpuuPrSi = false;}
      if(HlUhtYPAOf == true){HlUhtYPAOf = false;}
      if(IwWDUKPQyS == true){IwWDUKPQyS = false;}
      if(esZjbYQxSc == true){esZjbYQxSc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCBWVIHLYD
{ 
  void yQgKljVONT()
  { 
      bool gETLuxUuMz = false;
      bool CSmIZlhexQ = false;
      bool BiLPCYYKgN = false;
      bool kwkOdxemEA = false;
      bool EtsDQAjjQk = false;
      bool olHfLxrDIW = false;
      bool YKNyOGhYec = false;
      bool HuawLGoIyC = false;
      bool nnsuXzoFDf = false;
      bool EadgbtguoK = false;
      bool SKFnctLKTE = false;
      bool IjEFijRRaP = false;
      bool QbVyYgQtTR = false;
      bool ZtTnjciESc = false;
      bool mdkyXTVXyr = false;
      bool cOTZspoHPw = false;
      bool cRpCeNQQVF = false;
      bool AMzxblqXZE = false;
      bool KsuboLZttt = false;
      bool nboVAVniSJ = false;
      string HcxhXDMMEq;
      string XrmhBWIBIB;
      string TYpWxwnQYu;
      string hHexSDNuyp;
      string qfVxQTJIAH;
      string zQoTZimZkb;
      string OwmJIQMpOy;
      string JMDSJnCsFd;
      string lfPRuRRKWj;
      string QnKWaurMnA;
      string GTsCxmNVJk;
      string fsTHoifVNp;
      string yCSehVBfqN;
      string uoEFXSlNTI;
      string EuAlDWTDhr;
      string PWzyCDAOTb;
      string kgewoqoOjV;
      string wRBEkCBgaL;
      string ByyzyYoGDT;
      string SXsqXXQEwM;
      if(HcxhXDMMEq == GTsCxmNVJk){gETLuxUuMz = true;}
      else if(GTsCxmNVJk == HcxhXDMMEq){SKFnctLKTE = true;}
      if(XrmhBWIBIB == fsTHoifVNp){CSmIZlhexQ = true;}
      else if(fsTHoifVNp == XrmhBWIBIB){IjEFijRRaP = true;}
      if(TYpWxwnQYu == yCSehVBfqN){BiLPCYYKgN = true;}
      else if(yCSehVBfqN == TYpWxwnQYu){QbVyYgQtTR = true;}
      if(hHexSDNuyp == uoEFXSlNTI){kwkOdxemEA = true;}
      else if(uoEFXSlNTI == hHexSDNuyp){ZtTnjciESc = true;}
      if(qfVxQTJIAH == EuAlDWTDhr){EtsDQAjjQk = true;}
      else if(EuAlDWTDhr == qfVxQTJIAH){mdkyXTVXyr = true;}
      if(zQoTZimZkb == PWzyCDAOTb){olHfLxrDIW = true;}
      else if(PWzyCDAOTb == zQoTZimZkb){cOTZspoHPw = true;}
      if(OwmJIQMpOy == kgewoqoOjV){YKNyOGhYec = true;}
      else if(kgewoqoOjV == OwmJIQMpOy){cRpCeNQQVF = true;}
      if(JMDSJnCsFd == wRBEkCBgaL){HuawLGoIyC = true;}
      if(lfPRuRRKWj == ByyzyYoGDT){nnsuXzoFDf = true;}
      if(QnKWaurMnA == SXsqXXQEwM){EadgbtguoK = true;}
      while(wRBEkCBgaL == JMDSJnCsFd){AMzxblqXZE = true;}
      while(ByyzyYoGDT == ByyzyYoGDT){KsuboLZttt = true;}
      while(SXsqXXQEwM == SXsqXXQEwM){nboVAVniSJ = true;}
      if(gETLuxUuMz == true){gETLuxUuMz = false;}
      if(CSmIZlhexQ == true){CSmIZlhexQ = false;}
      if(BiLPCYYKgN == true){BiLPCYYKgN = false;}
      if(kwkOdxemEA == true){kwkOdxemEA = false;}
      if(EtsDQAjjQk == true){EtsDQAjjQk = false;}
      if(olHfLxrDIW == true){olHfLxrDIW = false;}
      if(YKNyOGhYec == true){YKNyOGhYec = false;}
      if(HuawLGoIyC == true){HuawLGoIyC = false;}
      if(nnsuXzoFDf == true){nnsuXzoFDf = false;}
      if(EadgbtguoK == true){EadgbtguoK = false;}
      if(SKFnctLKTE == true){SKFnctLKTE = false;}
      if(IjEFijRRaP == true){IjEFijRRaP = false;}
      if(QbVyYgQtTR == true){QbVyYgQtTR = false;}
      if(ZtTnjciESc == true){ZtTnjciESc = false;}
      if(mdkyXTVXyr == true){mdkyXTVXyr = false;}
      if(cOTZspoHPw == true){cOTZspoHPw = false;}
      if(cRpCeNQQVF == true){cRpCeNQQVF = false;}
      if(AMzxblqXZE == true){AMzxblqXZE = false;}
      if(KsuboLZttt == true){KsuboLZttt = false;}
      if(nboVAVniSJ == true){nboVAVniSJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUIKZSZRJT
{ 
  void MEISYnRcQR()
  { 
      bool XXZbpQIFos = false;
      bool jzWNnVxtQJ = false;
      bool AkQCgJBnde = false;
      bool gqWNTZFcKt = false;
      bool ZrRSllVMPd = false;
      bool DYdyWmGXuf = false;
      bool PUaKMscJsO = false;
      bool PUiViISyPt = false;
      bool moYzbIMYpg = false;
      bool ShgeeFQHGs = false;
      bool JMSAOhoHON = false;
      bool TIHArawbiD = false;
      bool fDSLwhmEqd = false;
      bool rLrVjaVXks = false;
      bool SFJcMJaglD = false;
      bool JoXCNGsHEf = false;
      bool ujQkUHQkPR = false;
      bool FXppjasoyl = false;
      bool HGSmUDmoId = false;
      bool gNSEyhnYHF = false;
      string JprFtAFIYm;
      string CCdknWyVAC;
      string LfjsQliEzI;
      string tioXdskEnL;
      string zrhAcsNUKX;
      string ZkdjucGznI;
      string QAJPsTNGHu;
      string ltgnCSyjPW;
      string XOtbiIEEbA;
      string llPftyiRGJ;
      string eHNOlfEogc;
      string eVjQjCGhgk;
      string PJdGIzdBsE;
      string jgcGrQAepC;
      string EOXzVQBywr;
      string rBjVtVdHFl;
      string BCucryrdYT;
      string CarefAkdkr;
      string xfFBLixHMW;
      string lrZDABStHX;
      if(JprFtAFIYm == eHNOlfEogc){XXZbpQIFos = true;}
      else if(eHNOlfEogc == JprFtAFIYm){JMSAOhoHON = true;}
      if(CCdknWyVAC == eVjQjCGhgk){jzWNnVxtQJ = true;}
      else if(eVjQjCGhgk == CCdknWyVAC){TIHArawbiD = true;}
      if(LfjsQliEzI == PJdGIzdBsE){AkQCgJBnde = true;}
      else if(PJdGIzdBsE == LfjsQliEzI){fDSLwhmEqd = true;}
      if(tioXdskEnL == jgcGrQAepC){gqWNTZFcKt = true;}
      else if(jgcGrQAepC == tioXdskEnL){rLrVjaVXks = true;}
      if(zrhAcsNUKX == EOXzVQBywr){ZrRSllVMPd = true;}
      else if(EOXzVQBywr == zrhAcsNUKX){SFJcMJaglD = true;}
      if(ZkdjucGznI == rBjVtVdHFl){DYdyWmGXuf = true;}
      else if(rBjVtVdHFl == ZkdjucGznI){JoXCNGsHEf = true;}
      if(QAJPsTNGHu == BCucryrdYT){PUaKMscJsO = true;}
      else if(BCucryrdYT == QAJPsTNGHu){ujQkUHQkPR = true;}
      if(ltgnCSyjPW == CarefAkdkr){PUiViISyPt = true;}
      if(XOtbiIEEbA == xfFBLixHMW){moYzbIMYpg = true;}
      if(llPftyiRGJ == lrZDABStHX){ShgeeFQHGs = true;}
      while(CarefAkdkr == ltgnCSyjPW){FXppjasoyl = true;}
      while(xfFBLixHMW == xfFBLixHMW){HGSmUDmoId = true;}
      while(lrZDABStHX == lrZDABStHX){gNSEyhnYHF = true;}
      if(XXZbpQIFos == true){XXZbpQIFos = false;}
      if(jzWNnVxtQJ == true){jzWNnVxtQJ = false;}
      if(AkQCgJBnde == true){AkQCgJBnde = false;}
      if(gqWNTZFcKt == true){gqWNTZFcKt = false;}
      if(ZrRSllVMPd == true){ZrRSllVMPd = false;}
      if(DYdyWmGXuf == true){DYdyWmGXuf = false;}
      if(PUaKMscJsO == true){PUaKMscJsO = false;}
      if(PUiViISyPt == true){PUiViISyPt = false;}
      if(moYzbIMYpg == true){moYzbIMYpg = false;}
      if(ShgeeFQHGs == true){ShgeeFQHGs = false;}
      if(JMSAOhoHON == true){JMSAOhoHON = false;}
      if(TIHArawbiD == true){TIHArawbiD = false;}
      if(fDSLwhmEqd == true){fDSLwhmEqd = false;}
      if(rLrVjaVXks == true){rLrVjaVXks = false;}
      if(SFJcMJaglD == true){SFJcMJaglD = false;}
      if(JoXCNGsHEf == true){JoXCNGsHEf = false;}
      if(ujQkUHQkPR == true){ujQkUHQkPR = false;}
      if(FXppjasoyl == true){FXppjasoyl = false;}
      if(HGSmUDmoId == true){HGSmUDmoId = false;}
      if(gNSEyhnYHF == true){gNSEyhnYHF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIOXUCBDUV
{ 
  void kNckFfAIAR()
  { 
      bool uELHgOkBMn = false;
      bool yHIRYfMcSe = false;
      bool fyznutIjVo = false;
      bool zLwsxMzAjO = false;
      bool lZpAdisazg = false;
      bool zVQmswEXLm = false;
      bool FAeXnlKPUL = false;
      bool fLrDsGIzJL = false;
      bool AhkopcuJAA = false;
      bool IbnxIktSLr = false;
      bool XdFmAmcMsl = false;
      bool nFNzlXOpgK = false;
      bool qBOTCEXtuH = false;
      bool MomRnWbxnC = false;
      bool AhPNLCNnLk = false;
      bool WEkBAWOkkw = false;
      bool OiRlZySwLP = false;
      bool wQBeKJkAIz = false;
      bool piiJkHElQQ = false;
      bool HpMrnQPdnN = false;
      string kGRxUKUUrp;
      string wXMBupzChq;
      string iifCPBeLiS;
      string KWYnCoXxKi;
      string dCyXAVgZGT;
      string hLnCACZPhT;
      string eJlYeYyYyF;
      string SCqyNgjIBt;
      string UFEPkzhVnz;
      string OHPqDTQYrb;
      string WHaBBeTooS;
      string SROmyZEWne;
      string pckzpKmAus;
      string QKPZWMdDNF;
      string erfUgxsbrc;
      string PsjMktWbKp;
      string rTtwCHBnQk;
      string wBIiAxwPSs;
      string RLHRcWaCnc;
      string pCrXNLyjSZ;
      if(kGRxUKUUrp == WHaBBeTooS){uELHgOkBMn = true;}
      else if(WHaBBeTooS == kGRxUKUUrp){XdFmAmcMsl = true;}
      if(wXMBupzChq == SROmyZEWne){yHIRYfMcSe = true;}
      else if(SROmyZEWne == wXMBupzChq){nFNzlXOpgK = true;}
      if(iifCPBeLiS == pckzpKmAus){fyznutIjVo = true;}
      else if(pckzpKmAus == iifCPBeLiS){qBOTCEXtuH = true;}
      if(KWYnCoXxKi == QKPZWMdDNF){zLwsxMzAjO = true;}
      else if(QKPZWMdDNF == KWYnCoXxKi){MomRnWbxnC = true;}
      if(dCyXAVgZGT == erfUgxsbrc){lZpAdisazg = true;}
      else if(erfUgxsbrc == dCyXAVgZGT){AhPNLCNnLk = true;}
      if(hLnCACZPhT == PsjMktWbKp){zVQmswEXLm = true;}
      else if(PsjMktWbKp == hLnCACZPhT){WEkBAWOkkw = true;}
      if(eJlYeYyYyF == rTtwCHBnQk){FAeXnlKPUL = true;}
      else if(rTtwCHBnQk == eJlYeYyYyF){OiRlZySwLP = true;}
      if(SCqyNgjIBt == wBIiAxwPSs){fLrDsGIzJL = true;}
      if(UFEPkzhVnz == RLHRcWaCnc){AhkopcuJAA = true;}
      if(OHPqDTQYrb == pCrXNLyjSZ){IbnxIktSLr = true;}
      while(wBIiAxwPSs == SCqyNgjIBt){wQBeKJkAIz = true;}
      while(RLHRcWaCnc == RLHRcWaCnc){piiJkHElQQ = true;}
      while(pCrXNLyjSZ == pCrXNLyjSZ){HpMrnQPdnN = true;}
      if(uELHgOkBMn == true){uELHgOkBMn = false;}
      if(yHIRYfMcSe == true){yHIRYfMcSe = false;}
      if(fyznutIjVo == true){fyznutIjVo = false;}
      if(zLwsxMzAjO == true){zLwsxMzAjO = false;}
      if(lZpAdisazg == true){lZpAdisazg = false;}
      if(zVQmswEXLm == true){zVQmswEXLm = false;}
      if(FAeXnlKPUL == true){FAeXnlKPUL = false;}
      if(fLrDsGIzJL == true){fLrDsGIzJL = false;}
      if(AhkopcuJAA == true){AhkopcuJAA = false;}
      if(IbnxIktSLr == true){IbnxIktSLr = false;}
      if(XdFmAmcMsl == true){XdFmAmcMsl = false;}
      if(nFNzlXOpgK == true){nFNzlXOpgK = false;}
      if(qBOTCEXtuH == true){qBOTCEXtuH = false;}
      if(MomRnWbxnC == true){MomRnWbxnC = false;}
      if(AhPNLCNnLk == true){AhPNLCNnLk = false;}
      if(WEkBAWOkkw == true){WEkBAWOkkw = false;}
      if(OiRlZySwLP == true){OiRlZySwLP = false;}
      if(wQBeKJkAIz == true){wQBeKJkAIz = false;}
      if(piiJkHElQQ == true){piiJkHElQQ = false;}
      if(HpMrnQPdnN == true){HpMrnQPdnN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTEDYJVBXO
{ 
  void OxnuLtebiu()
  { 
      bool FVeXMxYEhp = false;
      bool QPxJUVLGEA = false;
      bool xBoqyYGRHj = false;
      bool BXOhHftfIK = false;
      bool ofOsOYGCyk = false;
      bool NhrBUDfnZm = false;
      bool qGxxosBOCn = false;
      bool aeytKQlwbZ = false;
      bool SDTVWSfMMD = false;
      bool zFGUSiiQEV = false;
      bool WqAJJijyqE = false;
      bool RjMzUmmaaV = false;
      bool NoBzoVXcab = false;
      bool hUrGCaDJLn = false;
      bool hgVIlPsGAf = false;
      bool uHphIhpBUn = false;
      bool KHWOVwrFxs = false;
      bool icPmmfSsMY = false;
      bool cQctfaeJyT = false;
      bool kBoXcaKGlo = false;
      string nLyBSSylFJ;
      string YFeDWJjxXr;
      string ZMqDbboWEP;
      string oOdwOMeQLw;
      string xRYLyrunyx;
      string qSNhtaTuYp;
      string dbhoUJahoK;
      string eTlbuHnfFi;
      string gAXHYVBwCm;
      string riqURVjipn;
      string RMznRWgkll;
      string mnooIcDZQy;
      string HefBRubQJZ;
      string XEoQRUBjoB;
      string oQJPAEtCLo;
      string RJSrglfxWV;
      string uPaMOhyYWn;
      string bTkOJqUPAM;
      string BZEUHNkxif;
      string oDMSGYoxBS;
      if(nLyBSSylFJ == RMznRWgkll){FVeXMxYEhp = true;}
      else if(RMznRWgkll == nLyBSSylFJ){WqAJJijyqE = true;}
      if(YFeDWJjxXr == mnooIcDZQy){QPxJUVLGEA = true;}
      else if(mnooIcDZQy == YFeDWJjxXr){RjMzUmmaaV = true;}
      if(ZMqDbboWEP == HefBRubQJZ){xBoqyYGRHj = true;}
      else if(HefBRubQJZ == ZMqDbboWEP){NoBzoVXcab = true;}
      if(oOdwOMeQLw == XEoQRUBjoB){BXOhHftfIK = true;}
      else if(XEoQRUBjoB == oOdwOMeQLw){hUrGCaDJLn = true;}
      if(xRYLyrunyx == oQJPAEtCLo){ofOsOYGCyk = true;}
      else if(oQJPAEtCLo == xRYLyrunyx){hgVIlPsGAf = true;}
      if(qSNhtaTuYp == RJSrglfxWV){NhrBUDfnZm = true;}
      else if(RJSrglfxWV == qSNhtaTuYp){uHphIhpBUn = true;}
      if(dbhoUJahoK == uPaMOhyYWn){qGxxosBOCn = true;}
      else if(uPaMOhyYWn == dbhoUJahoK){KHWOVwrFxs = true;}
      if(eTlbuHnfFi == bTkOJqUPAM){aeytKQlwbZ = true;}
      if(gAXHYVBwCm == BZEUHNkxif){SDTVWSfMMD = true;}
      if(riqURVjipn == oDMSGYoxBS){zFGUSiiQEV = true;}
      while(bTkOJqUPAM == eTlbuHnfFi){icPmmfSsMY = true;}
      while(BZEUHNkxif == BZEUHNkxif){cQctfaeJyT = true;}
      while(oDMSGYoxBS == oDMSGYoxBS){kBoXcaKGlo = true;}
      if(FVeXMxYEhp == true){FVeXMxYEhp = false;}
      if(QPxJUVLGEA == true){QPxJUVLGEA = false;}
      if(xBoqyYGRHj == true){xBoqyYGRHj = false;}
      if(BXOhHftfIK == true){BXOhHftfIK = false;}
      if(ofOsOYGCyk == true){ofOsOYGCyk = false;}
      if(NhrBUDfnZm == true){NhrBUDfnZm = false;}
      if(qGxxosBOCn == true){qGxxosBOCn = false;}
      if(aeytKQlwbZ == true){aeytKQlwbZ = false;}
      if(SDTVWSfMMD == true){SDTVWSfMMD = false;}
      if(zFGUSiiQEV == true){zFGUSiiQEV = false;}
      if(WqAJJijyqE == true){WqAJJijyqE = false;}
      if(RjMzUmmaaV == true){RjMzUmmaaV = false;}
      if(NoBzoVXcab == true){NoBzoVXcab = false;}
      if(hUrGCaDJLn == true){hUrGCaDJLn = false;}
      if(hgVIlPsGAf == true){hgVIlPsGAf = false;}
      if(uHphIhpBUn == true){uHphIhpBUn = false;}
      if(KHWOVwrFxs == true){KHWOVwrFxs = false;}
      if(icPmmfSsMY == true){icPmmfSsMY = false;}
      if(cQctfaeJyT == true){cQctfaeJyT = false;}
      if(kBoXcaKGlo == true){kBoXcaKGlo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOGYPGNWFT
{ 
  void UMxBLwNzns()
  { 
      bool VlqBCJRClb = false;
      bool ZwWLWhSwtL = false;
      bool kqTQuyNXOP = false;
      bool zAlAuVodMX = false;
      bool XtqGPLrbyX = false;
      bool RksoneSaGD = false;
      bool wtmWcZKWQA = false;
      bool soiVnpANBj = false;
      bool FkYqyNGwLQ = false;
      bool DOXJbcHTco = false;
      bool BVLyecBWBy = false;
      bool dFYVxLUwXO = false;
      bool SNKAxdQZtK = false;
      bool hfjLhjZaLV = false;
      bool LjtMlyoBLP = false;
      bool HLuOWmKLAA = false;
      bool LbcqPyUMnN = false;
      bool ktjCCiSyNz = false;
      bool nOOdCWjUot = false;
      bool YOZKJjGDwn = false;
      string rblzGYoyDs;
      string KTEmaZVGZW;
      string aGHTWoKTew;
      string qzfJwsxjSE;
      string yWWXtDVURD;
      string fXNtFlTRbQ;
      string OUTHCLntqg;
      string clmVXDjjYS;
      string ToCaPSkkEJ;
      string ZfHCpdDOUi;
      string PadkatjrVB;
      string CirJwZSrqi;
      string ZCpgHwekft;
      string AUOpCsLQzV;
      string isPCHpnyFP;
      string LKXlINjwce;
      string OyLbBhTBGD;
      string NBrVzgmnZQ;
      string IgfPhowcho;
      string IOnUGjgmBZ;
      if(rblzGYoyDs == PadkatjrVB){VlqBCJRClb = true;}
      else if(PadkatjrVB == rblzGYoyDs){BVLyecBWBy = true;}
      if(KTEmaZVGZW == CirJwZSrqi){ZwWLWhSwtL = true;}
      else if(CirJwZSrqi == KTEmaZVGZW){dFYVxLUwXO = true;}
      if(aGHTWoKTew == ZCpgHwekft){kqTQuyNXOP = true;}
      else if(ZCpgHwekft == aGHTWoKTew){SNKAxdQZtK = true;}
      if(qzfJwsxjSE == AUOpCsLQzV){zAlAuVodMX = true;}
      else if(AUOpCsLQzV == qzfJwsxjSE){hfjLhjZaLV = true;}
      if(yWWXtDVURD == isPCHpnyFP){XtqGPLrbyX = true;}
      else if(isPCHpnyFP == yWWXtDVURD){LjtMlyoBLP = true;}
      if(fXNtFlTRbQ == LKXlINjwce){RksoneSaGD = true;}
      else if(LKXlINjwce == fXNtFlTRbQ){HLuOWmKLAA = true;}
      if(OUTHCLntqg == OyLbBhTBGD){wtmWcZKWQA = true;}
      else if(OyLbBhTBGD == OUTHCLntqg){LbcqPyUMnN = true;}
      if(clmVXDjjYS == NBrVzgmnZQ){soiVnpANBj = true;}
      if(ToCaPSkkEJ == IgfPhowcho){FkYqyNGwLQ = true;}
      if(ZfHCpdDOUi == IOnUGjgmBZ){DOXJbcHTco = true;}
      while(NBrVzgmnZQ == clmVXDjjYS){ktjCCiSyNz = true;}
      while(IgfPhowcho == IgfPhowcho){nOOdCWjUot = true;}
      while(IOnUGjgmBZ == IOnUGjgmBZ){YOZKJjGDwn = true;}
      if(VlqBCJRClb == true){VlqBCJRClb = false;}
      if(ZwWLWhSwtL == true){ZwWLWhSwtL = false;}
      if(kqTQuyNXOP == true){kqTQuyNXOP = false;}
      if(zAlAuVodMX == true){zAlAuVodMX = false;}
      if(XtqGPLrbyX == true){XtqGPLrbyX = false;}
      if(RksoneSaGD == true){RksoneSaGD = false;}
      if(wtmWcZKWQA == true){wtmWcZKWQA = false;}
      if(soiVnpANBj == true){soiVnpANBj = false;}
      if(FkYqyNGwLQ == true){FkYqyNGwLQ = false;}
      if(DOXJbcHTco == true){DOXJbcHTco = false;}
      if(BVLyecBWBy == true){BVLyecBWBy = false;}
      if(dFYVxLUwXO == true){dFYVxLUwXO = false;}
      if(SNKAxdQZtK == true){SNKAxdQZtK = false;}
      if(hfjLhjZaLV == true){hfjLhjZaLV = false;}
      if(LjtMlyoBLP == true){LjtMlyoBLP = false;}
      if(HLuOWmKLAA == true){HLuOWmKLAA = false;}
      if(LbcqPyUMnN == true){LbcqPyUMnN = false;}
      if(ktjCCiSyNz == true){ktjCCiSyNz = false;}
      if(nOOdCWjUot == true){nOOdCWjUot = false;}
      if(YOZKJjGDwn == true){YOZKJjGDwn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGISKKZLUM
{ 
  void kQIwBraAmp()
  { 
      bool HKMbWddEkJ = false;
      bool ZrRAAdquRl = false;
      bool GonzgTjQFH = false;
      bool eGZsCOeKhy = false;
      bool jeuflSEZpA = false;
      bool XNYOTSVMuD = false;
      bool tMydeSRXxl = false;
      bool zgMSCasINO = false;
      bool PKaEjQhKZi = false;
      bool rRPdEWgRAS = false;
      bool AfbEAqBGMr = false;
      bool ZNzfnilstN = false;
      bool kGyOshQhNe = false;
      bool taIuNihVEs = false;
      bool PbygJeRipU = false;
      bool kmXlhthNKR = false;
      bool ZSrhxyFESE = false;
      bool BPoByIIQEO = false;
      bool QhrrtHDVMT = false;
      bool BUKlSxiQjL = false;
      string JrHJllojaC;
      string uskFlcgeJP;
      string twXFasMKJD;
      string KVMJqIIAhh;
      string NjxNVlVjbH;
      string RgsOJMUBhs;
      string YdZWrZfaOc;
      string TgwaBJyKjn;
      string XciCkcbyAd;
      string nGRoJjJaVu;
      string FtVymkkSMz;
      string NKRtVwuXkO;
      string xhajnNOGRR;
      string zXnnicHjPA;
      string rJkAPdnXTM;
      string oloHyWSkKY;
      string VdAtzpVdKr;
      string oKHkVnxaTK;
      string YqlFcNigoL;
      string KVZpeOIpAZ;
      if(JrHJllojaC == FtVymkkSMz){HKMbWddEkJ = true;}
      else if(FtVymkkSMz == JrHJllojaC){AfbEAqBGMr = true;}
      if(uskFlcgeJP == NKRtVwuXkO){ZrRAAdquRl = true;}
      else if(NKRtVwuXkO == uskFlcgeJP){ZNzfnilstN = true;}
      if(twXFasMKJD == xhajnNOGRR){GonzgTjQFH = true;}
      else if(xhajnNOGRR == twXFasMKJD){kGyOshQhNe = true;}
      if(KVMJqIIAhh == zXnnicHjPA){eGZsCOeKhy = true;}
      else if(zXnnicHjPA == KVMJqIIAhh){taIuNihVEs = true;}
      if(NjxNVlVjbH == rJkAPdnXTM){jeuflSEZpA = true;}
      else if(rJkAPdnXTM == NjxNVlVjbH){PbygJeRipU = true;}
      if(RgsOJMUBhs == oloHyWSkKY){XNYOTSVMuD = true;}
      else if(oloHyWSkKY == RgsOJMUBhs){kmXlhthNKR = true;}
      if(YdZWrZfaOc == VdAtzpVdKr){tMydeSRXxl = true;}
      else if(VdAtzpVdKr == YdZWrZfaOc){ZSrhxyFESE = true;}
      if(TgwaBJyKjn == oKHkVnxaTK){zgMSCasINO = true;}
      if(XciCkcbyAd == YqlFcNigoL){PKaEjQhKZi = true;}
      if(nGRoJjJaVu == KVZpeOIpAZ){rRPdEWgRAS = true;}
      while(oKHkVnxaTK == TgwaBJyKjn){BPoByIIQEO = true;}
      while(YqlFcNigoL == YqlFcNigoL){QhrrtHDVMT = true;}
      while(KVZpeOIpAZ == KVZpeOIpAZ){BUKlSxiQjL = true;}
      if(HKMbWddEkJ == true){HKMbWddEkJ = false;}
      if(ZrRAAdquRl == true){ZrRAAdquRl = false;}
      if(GonzgTjQFH == true){GonzgTjQFH = false;}
      if(eGZsCOeKhy == true){eGZsCOeKhy = false;}
      if(jeuflSEZpA == true){jeuflSEZpA = false;}
      if(XNYOTSVMuD == true){XNYOTSVMuD = false;}
      if(tMydeSRXxl == true){tMydeSRXxl = false;}
      if(zgMSCasINO == true){zgMSCasINO = false;}
      if(PKaEjQhKZi == true){PKaEjQhKZi = false;}
      if(rRPdEWgRAS == true){rRPdEWgRAS = false;}
      if(AfbEAqBGMr == true){AfbEAqBGMr = false;}
      if(ZNzfnilstN == true){ZNzfnilstN = false;}
      if(kGyOshQhNe == true){kGyOshQhNe = false;}
      if(taIuNihVEs == true){taIuNihVEs = false;}
      if(PbygJeRipU == true){PbygJeRipU = false;}
      if(kmXlhthNKR == true){kmXlhthNKR = false;}
      if(ZSrhxyFESE == true){ZSrhxyFESE = false;}
      if(BPoByIIQEO == true){BPoByIIQEO = false;}
      if(QhrrtHDVMT == true){QhrrtHDVMT = false;}
      if(BUKlSxiQjL == true){BUKlSxiQjL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWMVIMZNWS
{ 
  void XRhuLEciWI()
  { 
      bool JisZYgOrYs = false;
      bool LwzojOwtMI = false;
      bool ICmEmSkUhm = false;
      bool ocBIAtMczc = false;
      bool JNyyYAwSaJ = false;
      bool lPOYSGwomF = false;
      bool usJkDhtqno = false;
      bool CSuiztEnem = false;
      bool VStYBZNbot = false;
      bool yXpthPDNtq = false;
      bool FFelGSUfZX = false;
      bool CHJziczkjd = false;
      bool TRCtpecAAi = false;
      bool qqtnhQnHRh = false;
      bool FhCQqpNqKF = false;
      bool PScQWmCjub = false;
      bool pTepgLNVQS = false;
      bool nqSCYlPkCA = false;
      bool QlpuTYNcQu = false;
      bool NDMoqkDMjf = false;
      string VZkwXNTnbt;
      string VZELJRtZNk;
      string FBQPoEeSDa;
      string tiTnclxfpR;
      string akzzIWwpRY;
      string XyaPVUJVHT;
      string iBjBAlFQhW;
      string TNjuJUBQGR;
      string HnBdCwIERI;
      string cbYWiZAxzW;
      string ReItFJNeGB;
      string SrOoLuAFyE;
      string cBzYtqoNMj;
      string TERjAbfGYr;
      string hcxPojNiKn;
      string ZuytsPfizN;
      string UzSWhOZdoj;
      string PsfGVzEjiK;
      string dFDXJYFXqk;
      string wwHKXhKaha;
      if(VZkwXNTnbt == ReItFJNeGB){JisZYgOrYs = true;}
      else if(ReItFJNeGB == VZkwXNTnbt){FFelGSUfZX = true;}
      if(VZELJRtZNk == SrOoLuAFyE){LwzojOwtMI = true;}
      else if(SrOoLuAFyE == VZELJRtZNk){CHJziczkjd = true;}
      if(FBQPoEeSDa == cBzYtqoNMj){ICmEmSkUhm = true;}
      else if(cBzYtqoNMj == FBQPoEeSDa){TRCtpecAAi = true;}
      if(tiTnclxfpR == TERjAbfGYr){ocBIAtMczc = true;}
      else if(TERjAbfGYr == tiTnclxfpR){qqtnhQnHRh = true;}
      if(akzzIWwpRY == hcxPojNiKn){JNyyYAwSaJ = true;}
      else if(hcxPojNiKn == akzzIWwpRY){FhCQqpNqKF = true;}
      if(XyaPVUJVHT == ZuytsPfizN){lPOYSGwomF = true;}
      else if(ZuytsPfizN == XyaPVUJVHT){PScQWmCjub = true;}
      if(iBjBAlFQhW == UzSWhOZdoj){usJkDhtqno = true;}
      else if(UzSWhOZdoj == iBjBAlFQhW){pTepgLNVQS = true;}
      if(TNjuJUBQGR == PsfGVzEjiK){CSuiztEnem = true;}
      if(HnBdCwIERI == dFDXJYFXqk){VStYBZNbot = true;}
      if(cbYWiZAxzW == wwHKXhKaha){yXpthPDNtq = true;}
      while(PsfGVzEjiK == TNjuJUBQGR){nqSCYlPkCA = true;}
      while(dFDXJYFXqk == dFDXJYFXqk){QlpuTYNcQu = true;}
      while(wwHKXhKaha == wwHKXhKaha){NDMoqkDMjf = true;}
      if(JisZYgOrYs == true){JisZYgOrYs = false;}
      if(LwzojOwtMI == true){LwzojOwtMI = false;}
      if(ICmEmSkUhm == true){ICmEmSkUhm = false;}
      if(ocBIAtMczc == true){ocBIAtMczc = false;}
      if(JNyyYAwSaJ == true){JNyyYAwSaJ = false;}
      if(lPOYSGwomF == true){lPOYSGwomF = false;}
      if(usJkDhtqno == true){usJkDhtqno = false;}
      if(CSuiztEnem == true){CSuiztEnem = false;}
      if(VStYBZNbot == true){VStYBZNbot = false;}
      if(yXpthPDNtq == true){yXpthPDNtq = false;}
      if(FFelGSUfZX == true){FFelGSUfZX = false;}
      if(CHJziczkjd == true){CHJziczkjd = false;}
      if(TRCtpecAAi == true){TRCtpecAAi = false;}
      if(qqtnhQnHRh == true){qqtnhQnHRh = false;}
      if(FhCQqpNqKF == true){FhCQqpNqKF = false;}
      if(PScQWmCjub == true){PScQWmCjub = false;}
      if(pTepgLNVQS == true){pTepgLNVQS = false;}
      if(nqSCYlPkCA == true){nqSCYlPkCA = false;}
      if(QlpuTYNcQu == true){QlpuTYNcQu = false;}
      if(NDMoqkDMjf == true){NDMoqkDMjf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YAOYWDAQTX
{ 
  void RZdCSrwPos()
  { 
      bool OdlUXXqLVH = false;
      bool aIRfuEqQhb = false;
      bool ktSBRTTdzQ = false;
      bool DizynKQVuV = false;
      bool XoQJOKCqMk = false;
      bool xXaSpTLjDD = false;
      bool DMLEDqITrk = false;
      bool mUVMEucIlG = false;
      bool QbQOSeHgHT = false;
      bool zfSqRKdMFW = false;
      bool CizbxbCOOu = false;
      bool qCxwmawwkY = false;
      bool jbLYkGCets = false;
      bool RPCPEgcoQp = false;
      bool csRMbwhVDp = false;
      bool OgagmaXaqp = false;
      bool ZWTUcaAhrG = false;
      bool yHetuqJywn = false;
      bool XgaDejoUcc = false;
      bool ICxZQGYxiA = false;
      string RKtwOUpxxW;
      string CaOQnUjnKW;
      string WrzIuzUFkc;
      string rxcJaBCcdP;
      string zUFhXrqXSF;
      string tpJIlZLlBP;
      string zkLUeFxFpm;
      string RHKtXClQjC;
      string IwlfiCmUWB;
      string oPaNPOJkDR;
      string ukhfmmeOjj;
      string mtByHDyfkb;
      string RbhoxCfxeJ;
      string rBNRHWOGsw;
      string WYjmNuNcGM;
      string PdAaASDshj;
      string Hhjaqlgjpk;
      string orloFrruaC;
      string nCqSsOAlRo;
      string SUXIonoIub;
      if(RKtwOUpxxW == ukhfmmeOjj){OdlUXXqLVH = true;}
      else if(ukhfmmeOjj == RKtwOUpxxW){CizbxbCOOu = true;}
      if(CaOQnUjnKW == mtByHDyfkb){aIRfuEqQhb = true;}
      else if(mtByHDyfkb == CaOQnUjnKW){qCxwmawwkY = true;}
      if(WrzIuzUFkc == RbhoxCfxeJ){ktSBRTTdzQ = true;}
      else if(RbhoxCfxeJ == WrzIuzUFkc){jbLYkGCets = true;}
      if(rxcJaBCcdP == rBNRHWOGsw){DizynKQVuV = true;}
      else if(rBNRHWOGsw == rxcJaBCcdP){RPCPEgcoQp = true;}
      if(zUFhXrqXSF == WYjmNuNcGM){XoQJOKCqMk = true;}
      else if(WYjmNuNcGM == zUFhXrqXSF){csRMbwhVDp = true;}
      if(tpJIlZLlBP == PdAaASDshj){xXaSpTLjDD = true;}
      else if(PdAaASDshj == tpJIlZLlBP){OgagmaXaqp = true;}
      if(zkLUeFxFpm == Hhjaqlgjpk){DMLEDqITrk = true;}
      else if(Hhjaqlgjpk == zkLUeFxFpm){ZWTUcaAhrG = true;}
      if(RHKtXClQjC == orloFrruaC){mUVMEucIlG = true;}
      if(IwlfiCmUWB == nCqSsOAlRo){QbQOSeHgHT = true;}
      if(oPaNPOJkDR == SUXIonoIub){zfSqRKdMFW = true;}
      while(orloFrruaC == RHKtXClQjC){yHetuqJywn = true;}
      while(nCqSsOAlRo == nCqSsOAlRo){XgaDejoUcc = true;}
      while(SUXIonoIub == SUXIonoIub){ICxZQGYxiA = true;}
      if(OdlUXXqLVH == true){OdlUXXqLVH = false;}
      if(aIRfuEqQhb == true){aIRfuEqQhb = false;}
      if(ktSBRTTdzQ == true){ktSBRTTdzQ = false;}
      if(DizynKQVuV == true){DizynKQVuV = false;}
      if(XoQJOKCqMk == true){XoQJOKCqMk = false;}
      if(xXaSpTLjDD == true){xXaSpTLjDD = false;}
      if(DMLEDqITrk == true){DMLEDqITrk = false;}
      if(mUVMEucIlG == true){mUVMEucIlG = false;}
      if(QbQOSeHgHT == true){QbQOSeHgHT = false;}
      if(zfSqRKdMFW == true){zfSqRKdMFW = false;}
      if(CizbxbCOOu == true){CizbxbCOOu = false;}
      if(qCxwmawwkY == true){qCxwmawwkY = false;}
      if(jbLYkGCets == true){jbLYkGCets = false;}
      if(RPCPEgcoQp == true){RPCPEgcoQp = false;}
      if(csRMbwhVDp == true){csRMbwhVDp = false;}
      if(OgagmaXaqp == true){OgagmaXaqp = false;}
      if(ZWTUcaAhrG == true){ZWTUcaAhrG = false;}
      if(yHetuqJywn == true){yHetuqJywn = false;}
      if(XgaDejoUcc == true){XgaDejoUcc = false;}
      if(ICxZQGYxiA == true){ICxZQGYxiA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNRDWTRDHA
{ 
  void rTfdPsFlkq()
  { 
      bool zLEKEwLcLo = false;
      bool mjWLkSwmir = false;
      bool Gkkaswagoi = false;
      bool jTcmlerKeH = false;
      bool mWwmUdsOQS = false;
      bool XRMoEOacQI = false;
      bool UdmcFSGjZG = false;
      bool ZlHbFinxGP = false;
      bool DMPWKRHniW = false;
      bool DPsWmIjThC = false;
      bool XIoJrlJkiV = false;
      bool acWBFINPRm = false;
      bool KRBCDKrknw = false;
      bool yUPEqtWGeY = false;
      bool IVFMuZsrRd = false;
      bool tTBtqFHlGh = false;
      bool sYwlWGNRJK = false;
      bool lHkseoMnGc = false;
      bool RzTKBeSUNl = false;
      bool ljzweiYSpo = false;
      string bKoGSPrHtC;
      string BRlGwcKPwX;
      string qkPQuMwSXS;
      string VjpsQGSrqh;
      string xqElMfXZSC;
      string SdkQkpuXKG;
      string TYiagQarpp;
      string JSYOZAgcDP;
      string nVzVAqzZIa;
      string LthkNXHdFw;
      string EejbrAFWpj;
      string JRUtRxZMao;
      string RAjOePjnAC;
      string sDXHLJkXdA;
      string lbjYQsYmSQ;
      string ytDPeDuUxb;
      string PRWmqGsNiI;
      string LCiZDoQKyk;
      string pxUjEyAIcH;
      string OPaCkUFwgK;
      if(bKoGSPrHtC == EejbrAFWpj){zLEKEwLcLo = true;}
      else if(EejbrAFWpj == bKoGSPrHtC){XIoJrlJkiV = true;}
      if(BRlGwcKPwX == JRUtRxZMao){mjWLkSwmir = true;}
      else if(JRUtRxZMao == BRlGwcKPwX){acWBFINPRm = true;}
      if(qkPQuMwSXS == RAjOePjnAC){Gkkaswagoi = true;}
      else if(RAjOePjnAC == qkPQuMwSXS){KRBCDKrknw = true;}
      if(VjpsQGSrqh == sDXHLJkXdA){jTcmlerKeH = true;}
      else if(sDXHLJkXdA == VjpsQGSrqh){yUPEqtWGeY = true;}
      if(xqElMfXZSC == lbjYQsYmSQ){mWwmUdsOQS = true;}
      else if(lbjYQsYmSQ == xqElMfXZSC){IVFMuZsrRd = true;}
      if(SdkQkpuXKG == ytDPeDuUxb){XRMoEOacQI = true;}
      else if(ytDPeDuUxb == SdkQkpuXKG){tTBtqFHlGh = true;}
      if(TYiagQarpp == PRWmqGsNiI){UdmcFSGjZG = true;}
      else if(PRWmqGsNiI == TYiagQarpp){sYwlWGNRJK = true;}
      if(JSYOZAgcDP == LCiZDoQKyk){ZlHbFinxGP = true;}
      if(nVzVAqzZIa == pxUjEyAIcH){DMPWKRHniW = true;}
      if(LthkNXHdFw == OPaCkUFwgK){DPsWmIjThC = true;}
      while(LCiZDoQKyk == JSYOZAgcDP){lHkseoMnGc = true;}
      while(pxUjEyAIcH == pxUjEyAIcH){RzTKBeSUNl = true;}
      while(OPaCkUFwgK == OPaCkUFwgK){ljzweiYSpo = true;}
      if(zLEKEwLcLo == true){zLEKEwLcLo = false;}
      if(mjWLkSwmir == true){mjWLkSwmir = false;}
      if(Gkkaswagoi == true){Gkkaswagoi = false;}
      if(jTcmlerKeH == true){jTcmlerKeH = false;}
      if(mWwmUdsOQS == true){mWwmUdsOQS = false;}
      if(XRMoEOacQI == true){XRMoEOacQI = false;}
      if(UdmcFSGjZG == true){UdmcFSGjZG = false;}
      if(ZlHbFinxGP == true){ZlHbFinxGP = false;}
      if(DMPWKRHniW == true){DMPWKRHniW = false;}
      if(DPsWmIjThC == true){DPsWmIjThC = false;}
      if(XIoJrlJkiV == true){XIoJrlJkiV = false;}
      if(acWBFINPRm == true){acWBFINPRm = false;}
      if(KRBCDKrknw == true){KRBCDKrknw = false;}
      if(yUPEqtWGeY == true){yUPEqtWGeY = false;}
      if(IVFMuZsrRd == true){IVFMuZsrRd = false;}
      if(tTBtqFHlGh == true){tTBtqFHlGh = false;}
      if(sYwlWGNRJK == true){sYwlWGNRJK = false;}
      if(lHkseoMnGc == true){lHkseoMnGc = false;}
      if(RzTKBeSUNl == true){RzTKBeSUNl = false;}
      if(ljzweiYSpo == true){ljzweiYSpo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENZJDQZMAK
{ 
  void FhOhzkomnF()
  { 
      bool mYBfqTPjCo = false;
      bool lOCEXyOHul = false;
      bool eLhyAsrmTQ = false;
      bool iAPFCbkzVx = false;
      bool mfoMwPhxin = false;
      bool RUEbtbqCey = false;
      bool bbQlGkywBu = false;
      bool NOkyyzVUCk = false;
      bool KuEfyNwmLa = false;
      bool kiTWUKPDFK = false;
      bool QlumaCiFct = false;
      bool GVztngXkmr = false;
      bool oKjaJeuNcn = false;
      bool jRPrTXzQEu = false;
      bool epKQTPiYin = false;
      bool mdPNUGBUcu = false;
      bool HUboKnGHaP = false;
      bool gGfrMyATGt = false;
      bool wVenBFBCXN = false;
      bool WdnJnKOUFf = false;
      string udYAEthqsl;
      string PwkdLwARLA;
      string TLUchFASDj;
      string CGeAGsqzML;
      string SXfGRPJCtn;
      string GpEZxiIwRy;
      string sOnJjJRjWS;
      string EAFAhueNKS;
      string wxYOdLBEDX;
      string ktgNRDiWWI;
      string yYfbiFkEqB;
      string DtlzCupYfX;
      string IMgygKTqie;
      string MHqCTWRweY;
      string axMCTpIgLV;
      string NJqzAlrgtY;
      string ktUMnuDife;
      string dssGxKAdep;
      string BleNQCQqBh;
      string dkBGmgbzNY;
      if(udYAEthqsl == yYfbiFkEqB){mYBfqTPjCo = true;}
      else if(yYfbiFkEqB == udYAEthqsl){QlumaCiFct = true;}
      if(PwkdLwARLA == DtlzCupYfX){lOCEXyOHul = true;}
      else if(DtlzCupYfX == PwkdLwARLA){GVztngXkmr = true;}
      if(TLUchFASDj == IMgygKTqie){eLhyAsrmTQ = true;}
      else if(IMgygKTqie == TLUchFASDj){oKjaJeuNcn = true;}
      if(CGeAGsqzML == MHqCTWRweY){iAPFCbkzVx = true;}
      else if(MHqCTWRweY == CGeAGsqzML){jRPrTXzQEu = true;}
      if(SXfGRPJCtn == axMCTpIgLV){mfoMwPhxin = true;}
      else if(axMCTpIgLV == SXfGRPJCtn){epKQTPiYin = true;}
      if(GpEZxiIwRy == NJqzAlrgtY){RUEbtbqCey = true;}
      else if(NJqzAlrgtY == GpEZxiIwRy){mdPNUGBUcu = true;}
      if(sOnJjJRjWS == ktUMnuDife){bbQlGkywBu = true;}
      else if(ktUMnuDife == sOnJjJRjWS){HUboKnGHaP = true;}
      if(EAFAhueNKS == dssGxKAdep){NOkyyzVUCk = true;}
      if(wxYOdLBEDX == BleNQCQqBh){KuEfyNwmLa = true;}
      if(ktgNRDiWWI == dkBGmgbzNY){kiTWUKPDFK = true;}
      while(dssGxKAdep == EAFAhueNKS){gGfrMyATGt = true;}
      while(BleNQCQqBh == BleNQCQqBh){wVenBFBCXN = true;}
      while(dkBGmgbzNY == dkBGmgbzNY){WdnJnKOUFf = true;}
      if(mYBfqTPjCo == true){mYBfqTPjCo = false;}
      if(lOCEXyOHul == true){lOCEXyOHul = false;}
      if(eLhyAsrmTQ == true){eLhyAsrmTQ = false;}
      if(iAPFCbkzVx == true){iAPFCbkzVx = false;}
      if(mfoMwPhxin == true){mfoMwPhxin = false;}
      if(RUEbtbqCey == true){RUEbtbqCey = false;}
      if(bbQlGkywBu == true){bbQlGkywBu = false;}
      if(NOkyyzVUCk == true){NOkyyzVUCk = false;}
      if(KuEfyNwmLa == true){KuEfyNwmLa = false;}
      if(kiTWUKPDFK == true){kiTWUKPDFK = false;}
      if(QlumaCiFct == true){QlumaCiFct = false;}
      if(GVztngXkmr == true){GVztngXkmr = false;}
      if(oKjaJeuNcn == true){oKjaJeuNcn = false;}
      if(jRPrTXzQEu == true){jRPrTXzQEu = false;}
      if(epKQTPiYin == true){epKQTPiYin = false;}
      if(mdPNUGBUcu == true){mdPNUGBUcu = false;}
      if(HUboKnGHaP == true){HUboKnGHaP = false;}
      if(gGfrMyATGt == true){gGfrMyATGt = false;}
      if(wVenBFBCXN == true){wVenBFBCXN = false;}
      if(WdnJnKOUFf == true){WdnJnKOUFf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AMRSFNTUVK
{ 
  void XBTXOQozuA()
  { 
      bool lVUsiHiNDU = false;
      bool wBNeMtuJHX = false;
      bool AOikTwanwE = false;
      bool xEZoCtjFjM = false;
      bool MWEoBuNcux = false;
      bool rZcgjXljYl = false;
      bool fuQzWrbYcS = false;
      bool KoZuLdKtjX = false;
      bool ixrzLXasFd = false;
      bool HzgxfQFFRI = false;
      bool SoAclCzhUG = false;
      bool NrABCiCQmz = false;
      bool QiSyKKIcPt = false;
      bool XEcaEtxPNJ = false;
      bool XsXyQPyetw = false;
      bool OoSRqjVBRa = false;
      bool tWSaiIOZwI = false;
      bool lmCdbXLTht = false;
      bool MchSfhlLiU = false;
      bool YuxlOAawPI = false;
      string RCmIlHylVR;
      string sxiOKsxfCW;
      string eeETOaTqIp;
      string FjxHdepQQh;
      string JpMgHoLUxM;
      string pTVykmxSsK;
      string mGceLJAake;
      string DgPTNoRXLZ;
      string OztuAlOyWp;
      string hWXFtCMgUy;
      string okiRJIDBkw;
      string VYGTunMheZ;
      string uCEuxfJJYK;
      string bkCNjdPckq;
      string hMMZUIPDKG;
      string peBuDlfnTd;
      string ztbaUjVsiR;
      string XiwnrhpeZn;
      string QFzSTwjHJy;
      string xbIHqmjkEj;
      if(RCmIlHylVR == okiRJIDBkw){lVUsiHiNDU = true;}
      else if(okiRJIDBkw == RCmIlHylVR){SoAclCzhUG = true;}
      if(sxiOKsxfCW == VYGTunMheZ){wBNeMtuJHX = true;}
      else if(VYGTunMheZ == sxiOKsxfCW){NrABCiCQmz = true;}
      if(eeETOaTqIp == uCEuxfJJYK){AOikTwanwE = true;}
      else if(uCEuxfJJYK == eeETOaTqIp){QiSyKKIcPt = true;}
      if(FjxHdepQQh == bkCNjdPckq){xEZoCtjFjM = true;}
      else if(bkCNjdPckq == FjxHdepQQh){XEcaEtxPNJ = true;}
      if(JpMgHoLUxM == hMMZUIPDKG){MWEoBuNcux = true;}
      else if(hMMZUIPDKG == JpMgHoLUxM){XsXyQPyetw = true;}
      if(pTVykmxSsK == peBuDlfnTd){rZcgjXljYl = true;}
      else if(peBuDlfnTd == pTVykmxSsK){OoSRqjVBRa = true;}
      if(mGceLJAake == ztbaUjVsiR){fuQzWrbYcS = true;}
      else if(ztbaUjVsiR == mGceLJAake){tWSaiIOZwI = true;}
      if(DgPTNoRXLZ == XiwnrhpeZn){KoZuLdKtjX = true;}
      if(OztuAlOyWp == QFzSTwjHJy){ixrzLXasFd = true;}
      if(hWXFtCMgUy == xbIHqmjkEj){HzgxfQFFRI = true;}
      while(XiwnrhpeZn == DgPTNoRXLZ){lmCdbXLTht = true;}
      while(QFzSTwjHJy == QFzSTwjHJy){MchSfhlLiU = true;}
      while(xbIHqmjkEj == xbIHqmjkEj){YuxlOAawPI = true;}
      if(lVUsiHiNDU == true){lVUsiHiNDU = false;}
      if(wBNeMtuJHX == true){wBNeMtuJHX = false;}
      if(AOikTwanwE == true){AOikTwanwE = false;}
      if(xEZoCtjFjM == true){xEZoCtjFjM = false;}
      if(MWEoBuNcux == true){MWEoBuNcux = false;}
      if(rZcgjXljYl == true){rZcgjXljYl = false;}
      if(fuQzWrbYcS == true){fuQzWrbYcS = false;}
      if(KoZuLdKtjX == true){KoZuLdKtjX = false;}
      if(ixrzLXasFd == true){ixrzLXasFd = false;}
      if(HzgxfQFFRI == true){HzgxfQFFRI = false;}
      if(SoAclCzhUG == true){SoAclCzhUG = false;}
      if(NrABCiCQmz == true){NrABCiCQmz = false;}
      if(QiSyKKIcPt == true){QiSyKKIcPt = false;}
      if(XEcaEtxPNJ == true){XEcaEtxPNJ = false;}
      if(XsXyQPyetw == true){XsXyQPyetw = false;}
      if(OoSRqjVBRa == true){OoSRqjVBRa = false;}
      if(tWSaiIOZwI == true){tWSaiIOZwI = false;}
      if(lmCdbXLTht == true){lmCdbXLTht = false;}
      if(MchSfhlLiU == true){MchSfhlLiU = false;}
      if(YuxlOAawPI == true){YuxlOAawPI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSMJQFUVBW
{ 
  void JJlzlkUxoi()
  { 
      bool MxnWTtOuuU = false;
      bool MbGrlIPYBa = false;
      bool kZcMoHEVQL = false;
      bool ZJJEUbctFW = false;
      bool FxIIACGaJl = false;
      bool EEBxxlUagM = false;
      bool pseitCRCXK = false;
      bool eVSdUnRULl = false;
      bool AcMdGVHMGh = false;
      bool GBMsgMRYNx = false;
      bool kEDzGikXbJ = false;
      bool UAOtLMgAcX = false;
      bool tFuoDcIYxI = false;
      bool VrGNBwYNXW = false;
      bool jjjxNGlSgT = false;
      bool eRwpDeINuc = false;
      bool aMaSmbsBrP = false;
      bool mTcFmKUybw = false;
      bool qpqcdDwQKW = false;
      bool nLRtwXJQJk = false;
      string hPkMqTWtgB;
      string AznpTMgNfO;
      string eVSYHgmMZe;
      string fhsUAwXdHy;
      string tYmdUNfjUd;
      string HrtVDLxLFJ;
      string fJTCUSFToW;
      string oDFgTGinDs;
      string BDquXnnWRo;
      string zLYyRjEkIC;
      string HMuxoDmMBx;
      string bIHLIcRXdg;
      string dhCAXcdGOi;
      string ByeBlnItGT;
      string AaVTMpDNpo;
      string SfGbXYJtZL;
      string YfySuddGYT;
      string UXRKfDMhmg;
      string YQQZQUrDcM;
      string dNTutUcDXi;
      if(hPkMqTWtgB == HMuxoDmMBx){MxnWTtOuuU = true;}
      else if(HMuxoDmMBx == hPkMqTWtgB){kEDzGikXbJ = true;}
      if(AznpTMgNfO == bIHLIcRXdg){MbGrlIPYBa = true;}
      else if(bIHLIcRXdg == AznpTMgNfO){UAOtLMgAcX = true;}
      if(eVSYHgmMZe == dhCAXcdGOi){kZcMoHEVQL = true;}
      else if(dhCAXcdGOi == eVSYHgmMZe){tFuoDcIYxI = true;}
      if(fhsUAwXdHy == ByeBlnItGT){ZJJEUbctFW = true;}
      else if(ByeBlnItGT == fhsUAwXdHy){VrGNBwYNXW = true;}
      if(tYmdUNfjUd == AaVTMpDNpo){FxIIACGaJl = true;}
      else if(AaVTMpDNpo == tYmdUNfjUd){jjjxNGlSgT = true;}
      if(HrtVDLxLFJ == SfGbXYJtZL){EEBxxlUagM = true;}
      else if(SfGbXYJtZL == HrtVDLxLFJ){eRwpDeINuc = true;}
      if(fJTCUSFToW == YfySuddGYT){pseitCRCXK = true;}
      else if(YfySuddGYT == fJTCUSFToW){aMaSmbsBrP = true;}
      if(oDFgTGinDs == UXRKfDMhmg){eVSdUnRULl = true;}
      if(BDquXnnWRo == YQQZQUrDcM){AcMdGVHMGh = true;}
      if(zLYyRjEkIC == dNTutUcDXi){GBMsgMRYNx = true;}
      while(UXRKfDMhmg == oDFgTGinDs){mTcFmKUybw = true;}
      while(YQQZQUrDcM == YQQZQUrDcM){qpqcdDwQKW = true;}
      while(dNTutUcDXi == dNTutUcDXi){nLRtwXJQJk = true;}
      if(MxnWTtOuuU == true){MxnWTtOuuU = false;}
      if(MbGrlIPYBa == true){MbGrlIPYBa = false;}
      if(kZcMoHEVQL == true){kZcMoHEVQL = false;}
      if(ZJJEUbctFW == true){ZJJEUbctFW = false;}
      if(FxIIACGaJl == true){FxIIACGaJl = false;}
      if(EEBxxlUagM == true){EEBxxlUagM = false;}
      if(pseitCRCXK == true){pseitCRCXK = false;}
      if(eVSdUnRULl == true){eVSdUnRULl = false;}
      if(AcMdGVHMGh == true){AcMdGVHMGh = false;}
      if(GBMsgMRYNx == true){GBMsgMRYNx = false;}
      if(kEDzGikXbJ == true){kEDzGikXbJ = false;}
      if(UAOtLMgAcX == true){UAOtLMgAcX = false;}
      if(tFuoDcIYxI == true){tFuoDcIYxI = false;}
      if(VrGNBwYNXW == true){VrGNBwYNXW = false;}
      if(jjjxNGlSgT == true){jjjxNGlSgT = false;}
      if(eRwpDeINuc == true){eRwpDeINuc = false;}
      if(aMaSmbsBrP == true){aMaSmbsBrP = false;}
      if(mTcFmKUybw == true){mTcFmKUybw = false;}
      if(qpqcdDwQKW == true){qpqcdDwQKW = false;}
      if(nLRtwXJQJk == true){nLRtwXJQJk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOCZEHINRY
{ 
  void aieFdxyOuh()
  { 
      bool EYMRjfkCwI = false;
      bool gwmcoSwsXd = false;
      bool AVXgtlZpSO = false;
      bool LgEdpxyUsT = false;
      bool OzgDSGSOTA = false;
      bool ToeHMiAfWx = false;
      bool GujhxArIlq = false;
      bool TbAEPBnUNn = false;
      bool TLVRtVBwRH = false;
      bool wSxwNTOzFS = false;
      bool NJbcfqoaqK = false;
      bool tfRidtYRmb = false;
      bool ywqetBdEpu = false;
      bool lnPuZJjskC = false;
      bool gZEGMQANRT = false;
      bool uwLcTRSwie = false;
      bool MkkuXGQWJT = false;
      bool KefjuXqjRd = false;
      bool APlWApblaH = false;
      bool qmKGowoIiG = false;
      string zwZlkSfTez;
      string EHYXdPplKV;
      string ZwgGoNUOoQ;
      string hUulKWbpcB;
      string uikWmqezce;
      string iulxGDOSwX;
      string xReOQiLlNG;
      string nzIJapLKTx;
      string iVkKgliyfH;
      string IIsFEcEVFD;
      string erkVpjlcVP;
      string qEzzobfThd;
      string ANFGyeFDFx;
      string koEPRpjOTx;
      string zGbPPDItQb;
      string xknaDRldXL;
      string diWYeCzjgy;
      string rQzketkoqt;
      string WLlcAABdMA;
      string DFqISQiDkM;
      if(zwZlkSfTez == erkVpjlcVP){EYMRjfkCwI = true;}
      else if(erkVpjlcVP == zwZlkSfTez){NJbcfqoaqK = true;}
      if(EHYXdPplKV == qEzzobfThd){gwmcoSwsXd = true;}
      else if(qEzzobfThd == EHYXdPplKV){tfRidtYRmb = true;}
      if(ZwgGoNUOoQ == ANFGyeFDFx){AVXgtlZpSO = true;}
      else if(ANFGyeFDFx == ZwgGoNUOoQ){ywqetBdEpu = true;}
      if(hUulKWbpcB == koEPRpjOTx){LgEdpxyUsT = true;}
      else if(koEPRpjOTx == hUulKWbpcB){lnPuZJjskC = true;}
      if(uikWmqezce == zGbPPDItQb){OzgDSGSOTA = true;}
      else if(zGbPPDItQb == uikWmqezce){gZEGMQANRT = true;}
      if(iulxGDOSwX == xknaDRldXL){ToeHMiAfWx = true;}
      else if(xknaDRldXL == iulxGDOSwX){uwLcTRSwie = true;}
      if(xReOQiLlNG == diWYeCzjgy){GujhxArIlq = true;}
      else if(diWYeCzjgy == xReOQiLlNG){MkkuXGQWJT = true;}
      if(nzIJapLKTx == rQzketkoqt){TbAEPBnUNn = true;}
      if(iVkKgliyfH == WLlcAABdMA){TLVRtVBwRH = true;}
      if(IIsFEcEVFD == DFqISQiDkM){wSxwNTOzFS = true;}
      while(rQzketkoqt == nzIJapLKTx){KefjuXqjRd = true;}
      while(WLlcAABdMA == WLlcAABdMA){APlWApblaH = true;}
      while(DFqISQiDkM == DFqISQiDkM){qmKGowoIiG = true;}
      if(EYMRjfkCwI == true){EYMRjfkCwI = false;}
      if(gwmcoSwsXd == true){gwmcoSwsXd = false;}
      if(AVXgtlZpSO == true){AVXgtlZpSO = false;}
      if(LgEdpxyUsT == true){LgEdpxyUsT = false;}
      if(OzgDSGSOTA == true){OzgDSGSOTA = false;}
      if(ToeHMiAfWx == true){ToeHMiAfWx = false;}
      if(GujhxArIlq == true){GujhxArIlq = false;}
      if(TbAEPBnUNn == true){TbAEPBnUNn = false;}
      if(TLVRtVBwRH == true){TLVRtVBwRH = false;}
      if(wSxwNTOzFS == true){wSxwNTOzFS = false;}
      if(NJbcfqoaqK == true){NJbcfqoaqK = false;}
      if(tfRidtYRmb == true){tfRidtYRmb = false;}
      if(ywqetBdEpu == true){ywqetBdEpu = false;}
      if(lnPuZJjskC == true){lnPuZJjskC = false;}
      if(gZEGMQANRT == true){gZEGMQANRT = false;}
      if(uwLcTRSwie == true){uwLcTRSwie = false;}
      if(MkkuXGQWJT == true){MkkuXGQWJT = false;}
      if(KefjuXqjRd == true){KefjuXqjRd = false;}
      if(APlWApblaH == true){APlWApblaH = false;}
      if(qmKGowoIiG == true){qmKGowoIiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RYXCCBMNOB
{ 
  void cEDlLnIOUP()
  { 
      bool kpwpBjpShN = false;
      bool ajaxwgobih = false;
      bool aVBHxkPHzq = false;
      bool PAKzybnINp = false;
      bool aCPGrZkFdQ = false;
      bool GXoPTPoosQ = false;
      bool UhTpxZYayU = false;
      bool rfNrGXFtOW = false;
      bool zKcikqLtfi = false;
      bool mzPxVriZIS = false;
      bool AJHJXZJxJu = false;
      bool JtZVQJEkEG = false;
      bool OduOhsPQWN = false;
      bool oflwVoDTKK = false;
      bool gOkjZrZtfL = false;
      bool myUCDVOrbe = false;
      bool KsZuGcIcza = false;
      bool GkZtYAsKoo = false;
      bool SVjKZqKirA = false;
      bool aKrfAnnpdw = false;
      string mrflJLTlFF;
      string GVCUVkWckw;
      string mtudNuwKfA;
      string MyqKOndrWs;
      string NBhktlqKEy;
      string HqyVYrxBXO;
      string PIFFrIdqFg;
      string GeFrhkMKjb;
      string DkGhsVzVkV;
      string qcUIcEwbrl;
      string HzEWrckGmn;
      string flRuKdCXMW;
      string IHGjocJxOd;
      string ojSxTDgjoP;
      string jrhxpFKYxz;
      string CXOUdAsUgO;
      string SnrJzuTUbH;
      string xRhwmPYIsj;
      string RkzPaQUxTT;
      string KLCaxuAYyt;
      if(mrflJLTlFF == HzEWrckGmn){kpwpBjpShN = true;}
      else if(HzEWrckGmn == mrflJLTlFF){AJHJXZJxJu = true;}
      if(GVCUVkWckw == flRuKdCXMW){ajaxwgobih = true;}
      else if(flRuKdCXMW == GVCUVkWckw){JtZVQJEkEG = true;}
      if(mtudNuwKfA == IHGjocJxOd){aVBHxkPHzq = true;}
      else if(IHGjocJxOd == mtudNuwKfA){OduOhsPQWN = true;}
      if(MyqKOndrWs == ojSxTDgjoP){PAKzybnINp = true;}
      else if(ojSxTDgjoP == MyqKOndrWs){oflwVoDTKK = true;}
      if(NBhktlqKEy == jrhxpFKYxz){aCPGrZkFdQ = true;}
      else if(jrhxpFKYxz == NBhktlqKEy){gOkjZrZtfL = true;}
      if(HqyVYrxBXO == CXOUdAsUgO){GXoPTPoosQ = true;}
      else if(CXOUdAsUgO == HqyVYrxBXO){myUCDVOrbe = true;}
      if(PIFFrIdqFg == SnrJzuTUbH){UhTpxZYayU = true;}
      else if(SnrJzuTUbH == PIFFrIdqFg){KsZuGcIcza = true;}
      if(GeFrhkMKjb == xRhwmPYIsj){rfNrGXFtOW = true;}
      if(DkGhsVzVkV == RkzPaQUxTT){zKcikqLtfi = true;}
      if(qcUIcEwbrl == KLCaxuAYyt){mzPxVriZIS = true;}
      while(xRhwmPYIsj == GeFrhkMKjb){GkZtYAsKoo = true;}
      while(RkzPaQUxTT == RkzPaQUxTT){SVjKZqKirA = true;}
      while(KLCaxuAYyt == KLCaxuAYyt){aKrfAnnpdw = true;}
      if(kpwpBjpShN == true){kpwpBjpShN = false;}
      if(ajaxwgobih == true){ajaxwgobih = false;}
      if(aVBHxkPHzq == true){aVBHxkPHzq = false;}
      if(PAKzybnINp == true){PAKzybnINp = false;}
      if(aCPGrZkFdQ == true){aCPGrZkFdQ = false;}
      if(GXoPTPoosQ == true){GXoPTPoosQ = false;}
      if(UhTpxZYayU == true){UhTpxZYayU = false;}
      if(rfNrGXFtOW == true){rfNrGXFtOW = false;}
      if(zKcikqLtfi == true){zKcikqLtfi = false;}
      if(mzPxVriZIS == true){mzPxVriZIS = false;}
      if(AJHJXZJxJu == true){AJHJXZJxJu = false;}
      if(JtZVQJEkEG == true){JtZVQJEkEG = false;}
      if(OduOhsPQWN == true){OduOhsPQWN = false;}
      if(oflwVoDTKK == true){oflwVoDTKK = false;}
      if(gOkjZrZtfL == true){gOkjZrZtfL = false;}
      if(myUCDVOrbe == true){myUCDVOrbe = false;}
      if(KsZuGcIcza == true){KsZuGcIcza = false;}
      if(GkZtYAsKoo == true){GkZtYAsKoo = false;}
      if(SVjKZqKirA == true){SVjKZqKirA = false;}
      if(aKrfAnnpdw == true){aKrfAnnpdw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNQOZDKTSL
{ 
  void YIfahBPKtR()
  { 
      bool wGLUIXlFeA = false;
      bool BqWpQhcPsi = false;
      bool REYPqfxktY = false;
      bool FSgmPuBWgc = false;
      bool uONwrwMrDg = false;
      bool VGWtRqgudb = false;
      bool aBLFtiJjaV = false;
      bool fFhQmDpcXt = false;
      bool SFhNCzulVX = false;
      bool NFsFCtDIBJ = false;
      bool mcQgAQYGGN = false;
      bool BEWiIUTxDu = false;
      bool mWNDHaMcOs = false;
      bool AhaOGpnANl = false;
      bool ZneHVIiJwg = false;
      bool aFEGVQOMZZ = false;
      bool DwrNNTdIcS = false;
      bool gSjRUyqGgy = false;
      bool qCggSucTrp = false;
      bool baZnhdwRtC = false;
      string ruYfMrDzLa;
      string ooONQPpzCH;
      string KFKdmsjsaF;
      string CrkbdXRAnX;
      string fFnTaguVAt;
      string SWxasmjurT;
      string HKXGXxDmir;
      string yoLdaFRqCG;
      string yOsgmftKhq;
      string mVHUQVghud;
      string cHlHucLSzn;
      string VsslUrRpSr;
      string CsFrFchqNF;
      string XiuXcpcklJ;
      string TaKtVsbUzX;
      string EpOCajCsCR;
      string uUFtPlxVJe;
      string PfEJXaiLWL;
      string BMqpAgTsws;
      string niiTOzVQdi;
      if(ruYfMrDzLa == cHlHucLSzn){wGLUIXlFeA = true;}
      else if(cHlHucLSzn == ruYfMrDzLa){mcQgAQYGGN = true;}
      if(ooONQPpzCH == VsslUrRpSr){BqWpQhcPsi = true;}
      else if(VsslUrRpSr == ooONQPpzCH){BEWiIUTxDu = true;}
      if(KFKdmsjsaF == CsFrFchqNF){REYPqfxktY = true;}
      else if(CsFrFchqNF == KFKdmsjsaF){mWNDHaMcOs = true;}
      if(CrkbdXRAnX == XiuXcpcklJ){FSgmPuBWgc = true;}
      else if(XiuXcpcklJ == CrkbdXRAnX){AhaOGpnANl = true;}
      if(fFnTaguVAt == TaKtVsbUzX){uONwrwMrDg = true;}
      else if(TaKtVsbUzX == fFnTaguVAt){ZneHVIiJwg = true;}
      if(SWxasmjurT == EpOCajCsCR){VGWtRqgudb = true;}
      else if(EpOCajCsCR == SWxasmjurT){aFEGVQOMZZ = true;}
      if(HKXGXxDmir == uUFtPlxVJe){aBLFtiJjaV = true;}
      else if(uUFtPlxVJe == HKXGXxDmir){DwrNNTdIcS = true;}
      if(yoLdaFRqCG == PfEJXaiLWL){fFhQmDpcXt = true;}
      if(yOsgmftKhq == BMqpAgTsws){SFhNCzulVX = true;}
      if(mVHUQVghud == niiTOzVQdi){NFsFCtDIBJ = true;}
      while(PfEJXaiLWL == yoLdaFRqCG){gSjRUyqGgy = true;}
      while(BMqpAgTsws == BMqpAgTsws){qCggSucTrp = true;}
      while(niiTOzVQdi == niiTOzVQdi){baZnhdwRtC = true;}
      if(wGLUIXlFeA == true){wGLUIXlFeA = false;}
      if(BqWpQhcPsi == true){BqWpQhcPsi = false;}
      if(REYPqfxktY == true){REYPqfxktY = false;}
      if(FSgmPuBWgc == true){FSgmPuBWgc = false;}
      if(uONwrwMrDg == true){uONwrwMrDg = false;}
      if(VGWtRqgudb == true){VGWtRqgudb = false;}
      if(aBLFtiJjaV == true){aBLFtiJjaV = false;}
      if(fFhQmDpcXt == true){fFhQmDpcXt = false;}
      if(SFhNCzulVX == true){SFhNCzulVX = false;}
      if(NFsFCtDIBJ == true){NFsFCtDIBJ = false;}
      if(mcQgAQYGGN == true){mcQgAQYGGN = false;}
      if(BEWiIUTxDu == true){BEWiIUTxDu = false;}
      if(mWNDHaMcOs == true){mWNDHaMcOs = false;}
      if(AhaOGpnANl == true){AhaOGpnANl = false;}
      if(ZneHVIiJwg == true){ZneHVIiJwg = false;}
      if(aFEGVQOMZZ == true){aFEGVQOMZZ = false;}
      if(DwrNNTdIcS == true){DwrNNTdIcS = false;}
      if(gSjRUyqGgy == true){gSjRUyqGgy = false;}
      if(qCggSucTrp == true){qCggSucTrp = false;}
      if(baZnhdwRtC == true){baZnhdwRtC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFFBPTUQEV
{ 
  void TrgeqxhyQx()
  { 
      bool oDPGRnQBaa = false;
      bool lSZJKkNQSW = false;
      bool WJZxKwiGkg = false;
      bool PlwPBwwZhB = false;
      bool llCeshDRAl = false;
      bool qfusCfcSuV = false;
      bool EKPtKzVKHN = false;
      bool omiQjjGtDc = false;
      bool rRFzojqDMV = false;
      bool SddLwbWHUt = false;
      bool LsJlxDwdIS = false;
      bool YiOSdmEQFZ = false;
      bool HSxluKIXUH = false;
      bool NzZJRyITBk = false;
      bool nMttwiOLhJ = false;
      bool XFCulrwWpm = false;
      bool uXJAFYJEAe = false;
      bool ekPTkuXDoL = false;
      bool wxpKjHxeXY = false;
      bool CkcNpPDtnX = false;
      string qhEqwnRraR;
      string ihWSBexONo;
      string YnOWXuomsV;
      string ojrSyaoFIK;
      string PSwZNyjIsg;
      string uyMXQCThSA;
      string zeyFbypDUa;
      string orFDZFqoIY;
      string KfsMZqXTBu;
      string HHlHKjTqxO;
      string IfnSqDrJxL;
      string LeYspSklfj;
      string aVCYShFyro;
      string kAqsQdraUV;
      string yNVpjchsRr;
      string zhLMnldOzJ;
      string ytQIZKmecL;
      string ZKRJkMALop;
      string zMfzpDndFe;
      string AdaKXEwNPY;
      if(qhEqwnRraR == IfnSqDrJxL){oDPGRnQBaa = true;}
      else if(IfnSqDrJxL == qhEqwnRraR){LsJlxDwdIS = true;}
      if(ihWSBexONo == LeYspSklfj){lSZJKkNQSW = true;}
      else if(LeYspSklfj == ihWSBexONo){YiOSdmEQFZ = true;}
      if(YnOWXuomsV == aVCYShFyro){WJZxKwiGkg = true;}
      else if(aVCYShFyro == YnOWXuomsV){HSxluKIXUH = true;}
      if(ojrSyaoFIK == kAqsQdraUV){PlwPBwwZhB = true;}
      else if(kAqsQdraUV == ojrSyaoFIK){NzZJRyITBk = true;}
      if(PSwZNyjIsg == yNVpjchsRr){llCeshDRAl = true;}
      else if(yNVpjchsRr == PSwZNyjIsg){nMttwiOLhJ = true;}
      if(uyMXQCThSA == zhLMnldOzJ){qfusCfcSuV = true;}
      else if(zhLMnldOzJ == uyMXQCThSA){XFCulrwWpm = true;}
      if(zeyFbypDUa == ytQIZKmecL){EKPtKzVKHN = true;}
      else if(ytQIZKmecL == zeyFbypDUa){uXJAFYJEAe = true;}
      if(orFDZFqoIY == ZKRJkMALop){omiQjjGtDc = true;}
      if(KfsMZqXTBu == zMfzpDndFe){rRFzojqDMV = true;}
      if(HHlHKjTqxO == AdaKXEwNPY){SddLwbWHUt = true;}
      while(ZKRJkMALop == orFDZFqoIY){ekPTkuXDoL = true;}
      while(zMfzpDndFe == zMfzpDndFe){wxpKjHxeXY = true;}
      while(AdaKXEwNPY == AdaKXEwNPY){CkcNpPDtnX = true;}
      if(oDPGRnQBaa == true){oDPGRnQBaa = false;}
      if(lSZJKkNQSW == true){lSZJKkNQSW = false;}
      if(WJZxKwiGkg == true){WJZxKwiGkg = false;}
      if(PlwPBwwZhB == true){PlwPBwwZhB = false;}
      if(llCeshDRAl == true){llCeshDRAl = false;}
      if(qfusCfcSuV == true){qfusCfcSuV = false;}
      if(EKPtKzVKHN == true){EKPtKzVKHN = false;}
      if(omiQjjGtDc == true){omiQjjGtDc = false;}
      if(rRFzojqDMV == true){rRFzojqDMV = false;}
      if(SddLwbWHUt == true){SddLwbWHUt = false;}
      if(LsJlxDwdIS == true){LsJlxDwdIS = false;}
      if(YiOSdmEQFZ == true){YiOSdmEQFZ = false;}
      if(HSxluKIXUH == true){HSxluKIXUH = false;}
      if(NzZJRyITBk == true){NzZJRyITBk = false;}
      if(nMttwiOLhJ == true){nMttwiOLhJ = false;}
      if(XFCulrwWpm == true){XFCulrwWpm = false;}
      if(uXJAFYJEAe == true){uXJAFYJEAe = false;}
      if(ekPTkuXDoL == true){ekPTkuXDoL = false;}
      if(wxpKjHxeXY == true){wxpKjHxeXY = false;}
      if(CkcNpPDtnX == true){CkcNpPDtnX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMJDCMYXLR
{ 
  void iuIzIRstGd()
  { 
      bool OfSBRBcTIl = false;
      bool lpMlQJPZTJ = false;
      bool ZSAnuUJKmE = false;
      bool DMbsIjQOUx = false;
      bool OxxcXhZemp = false;
      bool nsGwtueeFx = false;
      bool rRfEhYNTcf = false;
      bool rBFVubVWPN = false;
      bool tdXwQKFfyM = false;
      bool ElIXFwQruz = false;
      bool TGBGxlnjAS = false;
      bool ZIOqCNtjmX = false;
      bool ShUQbGrhQy = false;
      bool KcbQtnbQyd = false;
      bool WUeemwWQUq = false;
      bool CgFWfkkkeq = false;
      bool tGTCHwfxxN = false;
      bool ldkJBxCocf = false;
      bool ibMZudXEkI = false;
      bool DpkHjPBcXp = false;
      string txiwduBsOc;
      string qLnxyFehjg;
      string zUYIVEMFPq;
      string mioHyFKbLd;
      string ZWKwVdtyLl;
      string AneBOYXaaZ;
      string iudXoIVgyr;
      string tDWGGcKclq;
      string JNtcqzEnrZ;
      string hiAktesmGN;
      string HNzSrwQXtk;
      string NuniPUBAgp;
      string DhoYJKCkLb;
      string jWVYjwNakt;
      string hfsGLmuRVY;
      string crGQJZXaIg;
      string teMSBqYPyT;
      string HaPmHXnhNW;
      string PjPlzqQFOK;
      string XmREzDTaFU;
      if(txiwduBsOc == HNzSrwQXtk){OfSBRBcTIl = true;}
      else if(HNzSrwQXtk == txiwduBsOc){TGBGxlnjAS = true;}
      if(qLnxyFehjg == NuniPUBAgp){lpMlQJPZTJ = true;}
      else if(NuniPUBAgp == qLnxyFehjg){ZIOqCNtjmX = true;}
      if(zUYIVEMFPq == DhoYJKCkLb){ZSAnuUJKmE = true;}
      else if(DhoYJKCkLb == zUYIVEMFPq){ShUQbGrhQy = true;}
      if(mioHyFKbLd == jWVYjwNakt){DMbsIjQOUx = true;}
      else if(jWVYjwNakt == mioHyFKbLd){KcbQtnbQyd = true;}
      if(ZWKwVdtyLl == hfsGLmuRVY){OxxcXhZemp = true;}
      else if(hfsGLmuRVY == ZWKwVdtyLl){WUeemwWQUq = true;}
      if(AneBOYXaaZ == crGQJZXaIg){nsGwtueeFx = true;}
      else if(crGQJZXaIg == AneBOYXaaZ){CgFWfkkkeq = true;}
      if(iudXoIVgyr == teMSBqYPyT){rRfEhYNTcf = true;}
      else if(teMSBqYPyT == iudXoIVgyr){tGTCHwfxxN = true;}
      if(tDWGGcKclq == HaPmHXnhNW){rBFVubVWPN = true;}
      if(JNtcqzEnrZ == PjPlzqQFOK){tdXwQKFfyM = true;}
      if(hiAktesmGN == XmREzDTaFU){ElIXFwQruz = true;}
      while(HaPmHXnhNW == tDWGGcKclq){ldkJBxCocf = true;}
      while(PjPlzqQFOK == PjPlzqQFOK){ibMZudXEkI = true;}
      while(XmREzDTaFU == XmREzDTaFU){DpkHjPBcXp = true;}
      if(OfSBRBcTIl == true){OfSBRBcTIl = false;}
      if(lpMlQJPZTJ == true){lpMlQJPZTJ = false;}
      if(ZSAnuUJKmE == true){ZSAnuUJKmE = false;}
      if(DMbsIjQOUx == true){DMbsIjQOUx = false;}
      if(OxxcXhZemp == true){OxxcXhZemp = false;}
      if(nsGwtueeFx == true){nsGwtueeFx = false;}
      if(rRfEhYNTcf == true){rRfEhYNTcf = false;}
      if(rBFVubVWPN == true){rBFVubVWPN = false;}
      if(tdXwQKFfyM == true){tdXwQKFfyM = false;}
      if(ElIXFwQruz == true){ElIXFwQruz = false;}
      if(TGBGxlnjAS == true){TGBGxlnjAS = false;}
      if(ZIOqCNtjmX == true){ZIOqCNtjmX = false;}
      if(ShUQbGrhQy == true){ShUQbGrhQy = false;}
      if(KcbQtnbQyd == true){KcbQtnbQyd = false;}
      if(WUeemwWQUq == true){WUeemwWQUq = false;}
      if(CgFWfkkkeq == true){CgFWfkkkeq = false;}
      if(tGTCHwfxxN == true){tGTCHwfxxN = false;}
      if(ldkJBxCocf == true){ldkJBxCocf = false;}
      if(ibMZudXEkI == true){ibMZudXEkI = false;}
      if(DpkHjPBcXp == true){DpkHjPBcXp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKGPXHIGPN
{ 
  void cHbExCiCiG()
  { 
      bool mjaRLxcwbi = false;
      bool VqBjKTOydY = false;
      bool jolcAAKTYH = false;
      bool tHKxleKZPB = false;
      bool PhDOKKbScT = false;
      bool YJjGAxyyRK = false;
      bool lIXTnOgEye = false;
      bool JnibIBlWRo = false;
      bool XqpEikWDxn = false;
      bool gMIEOGKjau = false;
      bool dXTxKjaIyy = false;
      bool LbfcluSSkC = false;
      bool qcHKywfdMB = false;
      bool qCuVKAWssy = false;
      bool KOFycEfeRT = false;
      bool nqyXEAQJyN = false;
      bool DwuwHJfKRl = false;
      bool XYYlrcXIgt = false;
      bool QBMsMADXRJ = false;
      bool iMtftNSIqS = false;
      string IkHlsLoHYI;
      string UBJuplXKIP;
      string rBrhYFkJJr;
      string BNMbJaNgsI;
      string SFwXctBEFj;
      string TkpihHsYNn;
      string ZfxfHHogkO;
      string YpRzxlETFd;
      string DgDZXPWctC;
      string gnTEimIQPV;
      string EUSpKcTplw;
      string CYTikrbWHr;
      string jMmhgjWMQJ;
      string dnDjYiONOt;
      string ugpxzIUkTp;
      string LkJXkrgjJa;
      string GHYbROUjJB;
      string dOHMwCVphY;
      string Plraysefyg;
      string BdDnnnHNfk;
      if(IkHlsLoHYI == EUSpKcTplw){mjaRLxcwbi = true;}
      else if(EUSpKcTplw == IkHlsLoHYI){dXTxKjaIyy = true;}
      if(UBJuplXKIP == CYTikrbWHr){VqBjKTOydY = true;}
      else if(CYTikrbWHr == UBJuplXKIP){LbfcluSSkC = true;}
      if(rBrhYFkJJr == jMmhgjWMQJ){jolcAAKTYH = true;}
      else if(jMmhgjWMQJ == rBrhYFkJJr){qcHKywfdMB = true;}
      if(BNMbJaNgsI == dnDjYiONOt){tHKxleKZPB = true;}
      else if(dnDjYiONOt == BNMbJaNgsI){qCuVKAWssy = true;}
      if(SFwXctBEFj == ugpxzIUkTp){PhDOKKbScT = true;}
      else if(ugpxzIUkTp == SFwXctBEFj){KOFycEfeRT = true;}
      if(TkpihHsYNn == LkJXkrgjJa){YJjGAxyyRK = true;}
      else if(LkJXkrgjJa == TkpihHsYNn){nqyXEAQJyN = true;}
      if(ZfxfHHogkO == GHYbROUjJB){lIXTnOgEye = true;}
      else if(GHYbROUjJB == ZfxfHHogkO){DwuwHJfKRl = true;}
      if(YpRzxlETFd == dOHMwCVphY){JnibIBlWRo = true;}
      if(DgDZXPWctC == Plraysefyg){XqpEikWDxn = true;}
      if(gnTEimIQPV == BdDnnnHNfk){gMIEOGKjau = true;}
      while(dOHMwCVphY == YpRzxlETFd){XYYlrcXIgt = true;}
      while(Plraysefyg == Plraysefyg){QBMsMADXRJ = true;}
      while(BdDnnnHNfk == BdDnnnHNfk){iMtftNSIqS = true;}
      if(mjaRLxcwbi == true){mjaRLxcwbi = false;}
      if(VqBjKTOydY == true){VqBjKTOydY = false;}
      if(jolcAAKTYH == true){jolcAAKTYH = false;}
      if(tHKxleKZPB == true){tHKxleKZPB = false;}
      if(PhDOKKbScT == true){PhDOKKbScT = false;}
      if(YJjGAxyyRK == true){YJjGAxyyRK = false;}
      if(lIXTnOgEye == true){lIXTnOgEye = false;}
      if(JnibIBlWRo == true){JnibIBlWRo = false;}
      if(XqpEikWDxn == true){XqpEikWDxn = false;}
      if(gMIEOGKjau == true){gMIEOGKjau = false;}
      if(dXTxKjaIyy == true){dXTxKjaIyy = false;}
      if(LbfcluSSkC == true){LbfcluSSkC = false;}
      if(qcHKywfdMB == true){qcHKywfdMB = false;}
      if(qCuVKAWssy == true){qCuVKAWssy = false;}
      if(KOFycEfeRT == true){KOFycEfeRT = false;}
      if(nqyXEAQJyN == true){nqyXEAQJyN = false;}
      if(DwuwHJfKRl == true){DwuwHJfKRl = false;}
      if(XYYlrcXIgt == true){XYYlrcXIgt = false;}
      if(QBMsMADXRJ == true){QBMsMADXRJ = false;}
      if(iMtftNSIqS == true){iMtftNSIqS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSYUBMMKNJ
{ 
  void BGPWlITfwo()
  { 
      bool mfOJmFszUl = false;
      bool NyeYeFAZlQ = false;
      bool zFILkbddlH = false;
      bool ffCBUfrmit = false;
      bool alMMpGsBYl = false;
      bool wBCqQgXCXK = false;
      bool aONNFgudDz = false;
      bool MMqrpMruUe = false;
      bool icEAKecLjn = false;
      bool HoOXSMYzHI = false;
      bool KOxZYiJKAE = false;
      bool obhsbxJMDa = false;
      bool EjsPqWySZd = false;
      bool msnLUTfeaa = false;
      bool USKeyfHVwU = false;
      bool CLufEaVgiC = false;
      bool kpkWQunVYH = false;
      bool RelbGlYOQL = false;
      bool PcWEabxIHt = false;
      bool yywYpdhmND = false;
      string YPQutbXsJd;
      string EasMtwUlcn;
      string jmqyYQWnXT;
      string nxDOorGDiM;
      string GdFMgEpmQh;
      string PyUdnkYRWd;
      string EiVooHWdXB;
      string oRCQgFheRT;
      string ZjWoEpbYaE;
      string TnfEHWIPXY;
      string gLPPryuEwh;
      string CtACEUMfky;
      string exDShAkxIK;
      string wRGrmNUHwF;
      string tXbsBZndAm;
      string KceYsiIwgr;
      string NxwlkkmHPp;
      string AEieEHVKRH;
      string MHxVzTlhyD;
      string EXZErxboHP;
      if(YPQutbXsJd == gLPPryuEwh){mfOJmFszUl = true;}
      else if(gLPPryuEwh == YPQutbXsJd){KOxZYiJKAE = true;}
      if(EasMtwUlcn == CtACEUMfky){NyeYeFAZlQ = true;}
      else if(CtACEUMfky == EasMtwUlcn){obhsbxJMDa = true;}
      if(jmqyYQWnXT == exDShAkxIK){zFILkbddlH = true;}
      else if(exDShAkxIK == jmqyYQWnXT){EjsPqWySZd = true;}
      if(nxDOorGDiM == wRGrmNUHwF){ffCBUfrmit = true;}
      else if(wRGrmNUHwF == nxDOorGDiM){msnLUTfeaa = true;}
      if(GdFMgEpmQh == tXbsBZndAm){alMMpGsBYl = true;}
      else if(tXbsBZndAm == GdFMgEpmQh){USKeyfHVwU = true;}
      if(PyUdnkYRWd == KceYsiIwgr){wBCqQgXCXK = true;}
      else if(KceYsiIwgr == PyUdnkYRWd){CLufEaVgiC = true;}
      if(EiVooHWdXB == NxwlkkmHPp){aONNFgudDz = true;}
      else if(NxwlkkmHPp == EiVooHWdXB){kpkWQunVYH = true;}
      if(oRCQgFheRT == AEieEHVKRH){MMqrpMruUe = true;}
      if(ZjWoEpbYaE == MHxVzTlhyD){icEAKecLjn = true;}
      if(TnfEHWIPXY == EXZErxboHP){HoOXSMYzHI = true;}
      while(AEieEHVKRH == oRCQgFheRT){RelbGlYOQL = true;}
      while(MHxVzTlhyD == MHxVzTlhyD){PcWEabxIHt = true;}
      while(EXZErxboHP == EXZErxboHP){yywYpdhmND = true;}
      if(mfOJmFszUl == true){mfOJmFszUl = false;}
      if(NyeYeFAZlQ == true){NyeYeFAZlQ = false;}
      if(zFILkbddlH == true){zFILkbddlH = false;}
      if(ffCBUfrmit == true){ffCBUfrmit = false;}
      if(alMMpGsBYl == true){alMMpGsBYl = false;}
      if(wBCqQgXCXK == true){wBCqQgXCXK = false;}
      if(aONNFgudDz == true){aONNFgudDz = false;}
      if(MMqrpMruUe == true){MMqrpMruUe = false;}
      if(icEAKecLjn == true){icEAKecLjn = false;}
      if(HoOXSMYzHI == true){HoOXSMYzHI = false;}
      if(KOxZYiJKAE == true){KOxZYiJKAE = false;}
      if(obhsbxJMDa == true){obhsbxJMDa = false;}
      if(EjsPqWySZd == true){EjsPqWySZd = false;}
      if(msnLUTfeaa == true){msnLUTfeaa = false;}
      if(USKeyfHVwU == true){USKeyfHVwU = false;}
      if(CLufEaVgiC == true){CLufEaVgiC = false;}
      if(kpkWQunVYH == true){kpkWQunVYH = false;}
      if(RelbGlYOQL == true){RelbGlYOQL = false;}
      if(PcWEabxIHt == true){PcWEabxIHt = false;}
      if(yywYpdhmND == true){yywYpdhmND = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZKFCHFGQHB
{ 
  void gAbnBQQWwJ()
  { 
      bool LJugheKlAW = false;
      bool DZAmXgNeOa = false;
      bool DiMCMLEbeC = false;
      bool xHfUOiKuuN = false;
      bool ayzbEOKcIG = false;
      bool LPIkibwrTV = false;
      bool ZiHyZwteXo = false;
      bool WRiAAEikyx = false;
      bool BbSXpgyulm = false;
      bool lSaYmqqBBI = false;
      bool UfESjsgHkd = false;
      bool rKsVUyPiIs = false;
      bool xzskDDqKNI = false;
      bool NhjpcUWzmw = false;
      bool zpJHtaYEDo = false;
      bool bHsIKVlSPf = false;
      bool CWtcPKaDsz = false;
      bool aQuLsHokqb = false;
      bool elGXfGoaeG = false;
      bool iDiGscufqi = false;
      string kiWxmwApMj;
      string NNnTzzHIjK;
      string hNYYOhriKq;
      string bWYidTroAB;
      string REVbBfogRj;
      string QKastWJxiE;
      string DQfVIqnFof;
      string HRIhscrwXh;
      string sLQZZRuenG;
      string JtGuyAYATK;
      string qjqlcyCrAQ;
      string eNZALrAFuq;
      string uJQiWMLMjr;
      string EqcNpITexb;
      string ODeXawUFjG;
      string ASFbOhSIOP;
      string mpIHLnjLKC;
      string XUITbrerHa;
      string rFbdrkkAyH;
      string oLQgnYtXLl;
      if(kiWxmwApMj == qjqlcyCrAQ){LJugheKlAW = true;}
      else if(qjqlcyCrAQ == kiWxmwApMj){UfESjsgHkd = true;}
      if(NNnTzzHIjK == eNZALrAFuq){DZAmXgNeOa = true;}
      else if(eNZALrAFuq == NNnTzzHIjK){rKsVUyPiIs = true;}
      if(hNYYOhriKq == uJQiWMLMjr){DiMCMLEbeC = true;}
      else if(uJQiWMLMjr == hNYYOhriKq){xzskDDqKNI = true;}
      if(bWYidTroAB == EqcNpITexb){xHfUOiKuuN = true;}
      else if(EqcNpITexb == bWYidTroAB){NhjpcUWzmw = true;}
      if(REVbBfogRj == ODeXawUFjG){ayzbEOKcIG = true;}
      else if(ODeXawUFjG == REVbBfogRj){zpJHtaYEDo = true;}
      if(QKastWJxiE == ASFbOhSIOP){LPIkibwrTV = true;}
      else if(ASFbOhSIOP == QKastWJxiE){bHsIKVlSPf = true;}
      if(DQfVIqnFof == mpIHLnjLKC){ZiHyZwteXo = true;}
      else if(mpIHLnjLKC == DQfVIqnFof){CWtcPKaDsz = true;}
      if(HRIhscrwXh == XUITbrerHa){WRiAAEikyx = true;}
      if(sLQZZRuenG == rFbdrkkAyH){BbSXpgyulm = true;}
      if(JtGuyAYATK == oLQgnYtXLl){lSaYmqqBBI = true;}
      while(XUITbrerHa == HRIhscrwXh){aQuLsHokqb = true;}
      while(rFbdrkkAyH == rFbdrkkAyH){elGXfGoaeG = true;}
      while(oLQgnYtXLl == oLQgnYtXLl){iDiGscufqi = true;}
      if(LJugheKlAW == true){LJugheKlAW = false;}
      if(DZAmXgNeOa == true){DZAmXgNeOa = false;}
      if(DiMCMLEbeC == true){DiMCMLEbeC = false;}
      if(xHfUOiKuuN == true){xHfUOiKuuN = false;}
      if(ayzbEOKcIG == true){ayzbEOKcIG = false;}
      if(LPIkibwrTV == true){LPIkibwrTV = false;}
      if(ZiHyZwteXo == true){ZiHyZwteXo = false;}
      if(WRiAAEikyx == true){WRiAAEikyx = false;}
      if(BbSXpgyulm == true){BbSXpgyulm = false;}
      if(lSaYmqqBBI == true){lSaYmqqBBI = false;}
      if(UfESjsgHkd == true){UfESjsgHkd = false;}
      if(rKsVUyPiIs == true){rKsVUyPiIs = false;}
      if(xzskDDqKNI == true){xzskDDqKNI = false;}
      if(NhjpcUWzmw == true){NhjpcUWzmw = false;}
      if(zpJHtaYEDo == true){zpJHtaYEDo = false;}
      if(bHsIKVlSPf == true){bHsIKVlSPf = false;}
      if(CWtcPKaDsz == true){CWtcPKaDsz = false;}
      if(aQuLsHokqb == true){aQuLsHokqb = false;}
      if(elGXfGoaeG == true){elGXfGoaeG = false;}
      if(iDiGscufqi == true){iDiGscufqi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCNBBRQWNV
{ 
  void TkhPfquRbo()
  { 
      bool WTUXYGMCXU = false;
      bool WpeSXpWTcM = false;
      bool mcxwraWyZa = false;
      bool iQokaUpZla = false;
      bool hbmHpVcTOw = false;
      bool GbhmUtWXfx = false;
      bool jObxkFAsqD = false;
      bool AwhBdKooGV = false;
      bool yCicTHhCQg = false;
      bool xRtnpTzpVj = false;
      bool VibLwKtfIJ = false;
      bool EgRJzgezcd = false;
      bool XxcKFhCsLK = false;
      bool KzTVAOaXgI = false;
      bool MBsGbQAjnI = false;
      bool nAMrMXGQFN = false;
      bool IAUxzFNuIk = false;
      bool GGSTRVEVio = false;
      bool hRFCVKmaJc = false;
      bool HJSSALguHW = false;
      string jzAAVBrJnq;
      string miyNdIMjtt;
      string zLCRZGQAYH;
      string pJKpJheYlG;
      string UUzhjTktVa;
      string ctkgfYwiaP;
      string kqjgAdYHDu;
      string dmxnZdMUhF;
      string UVexdwXcJk;
      string luyWVckRgF;
      string tdpawowxHB;
      string LaBUtOMlCE;
      string FwySJinaRx;
      string stmbKqfDAo;
      string zaUIYKsdbH;
      string PyPczyeXRN;
      string BVeJHRmYJD;
      string hIkNEebosy;
      string oKyKgueKbM;
      string LHlmmdwKAH;
      if(jzAAVBrJnq == tdpawowxHB){WTUXYGMCXU = true;}
      else if(tdpawowxHB == jzAAVBrJnq){VibLwKtfIJ = true;}
      if(miyNdIMjtt == LaBUtOMlCE){WpeSXpWTcM = true;}
      else if(LaBUtOMlCE == miyNdIMjtt){EgRJzgezcd = true;}
      if(zLCRZGQAYH == FwySJinaRx){mcxwraWyZa = true;}
      else if(FwySJinaRx == zLCRZGQAYH){XxcKFhCsLK = true;}
      if(pJKpJheYlG == stmbKqfDAo){iQokaUpZla = true;}
      else if(stmbKqfDAo == pJKpJheYlG){KzTVAOaXgI = true;}
      if(UUzhjTktVa == zaUIYKsdbH){hbmHpVcTOw = true;}
      else if(zaUIYKsdbH == UUzhjTktVa){MBsGbQAjnI = true;}
      if(ctkgfYwiaP == PyPczyeXRN){GbhmUtWXfx = true;}
      else if(PyPczyeXRN == ctkgfYwiaP){nAMrMXGQFN = true;}
      if(kqjgAdYHDu == BVeJHRmYJD){jObxkFAsqD = true;}
      else if(BVeJHRmYJD == kqjgAdYHDu){IAUxzFNuIk = true;}
      if(dmxnZdMUhF == hIkNEebosy){AwhBdKooGV = true;}
      if(UVexdwXcJk == oKyKgueKbM){yCicTHhCQg = true;}
      if(luyWVckRgF == LHlmmdwKAH){xRtnpTzpVj = true;}
      while(hIkNEebosy == dmxnZdMUhF){GGSTRVEVio = true;}
      while(oKyKgueKbM == oKyKgueKbM){hRFCVKmaJc = true;}
      while(LHlmmdwKAH == LHlmmdwKAH){HJSSALguHW = true;}
      if(WTUXYGMCXU == true){WTUXYGMCXU = false;}
      if(WpeSXpWTcM == true){WpeSXpWTcM = false;}
      if(mcxwraWyZa == true){mcxwraWyZa = false;}
      if(iQokaUpZla == true){iQokaUpZla = false;}
      if(hbmHpVcTOw == true){hbmHpVcTOw = false;}
      if(GbhmUtWXfx == true){GbhmUtWXfx = false;}
      if(jObxkFAsqD == true){jObxkFAsqD = false;}
      if(AwhBdKooGV == true){AwhBdKooGV = false;}
      if(yCicTHhCQg == true){yCicTHhCQg = false;}
      if(xRtnpTzpVj == true){xRtnpTzpVj = false;}
      if(VibLwKtfIJ == true){VibLwKtfIJ = false;}
      if(EgRJzgezcd == true){EgRJzgezcd = false;}
      if(XxcKFhCsLK == true){XxcKFhCsLK = false;}
      if(KzTVAOaXgI == true){KzTVAOaXgI = false;}
      if(MBsGbQAjnI == true){MBsGbQAjnI = false;}
      if(nAMrMXGQFN == true){nAMrMXGQFN = false;}
      if(IAUxzFNuIk == true){IAUxzFNuIk = false;}
      if(GGSTRVEVio == true){GGSTRVEVio = false;}
      if(hRFCVKmaJc == true){hRFCVKmaJc = false;}
      if(HJSSALguHW == true){HJSSALguHW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMOMBHHLSU
{ 
  void YYgdhXEIVn()
  { 
      bool OQHACmVNXR = false;
      bool wgAKnwdHoA = false;
      bool ISVbDzEORV = false;
      bool xqIpihNset = false;
      bool yXfWUnaHcN = false;
      bool ZmwSHuufxD = false;
      bool iGuCTEXKbF = false;
      bool ikctBkmyGO = false;
      bool XwkDuKtphm = false;
      bool mguaLrbdCP = false;
      bool QQfXeoKBRW = false;
      bool IwYielVrGJ = false;
      bool JhbnSCoBiJ = false;
      bool IIuqyHQNYG = false;
      bool zsXLeqHMwY = false;
      bool ViWsGhnqFb = false;
      bool AISINzAhjW = false;
      bool VITAJQJPJa = false;
      bool tbEJmYlCjP = false;
      bool SZHwFpZPxe = false;
      string jVWIkwodjm;
      string lyYWAdXkwg;
      string qqlfYbfSeL;
      string MbndYzXSmB;
      string fjTdwWVXuQ;
      string sqsPyrjqjJ;
      string QWyXaKKuyA;
      string FEyuBHWHiC;
      string FHWORVhXef;
      string PgidkJkuDl;
      string LZYtKnryOq;
      string UbHhDIzjFE;
      string blQRkYVTJq;
      string VaExpehbDd;
      string ciInKmZAZc;
      string JBpzJYJHJl;
      string SYoWUtXJrY;
      string ZWfbarcbGy;
      string yVtggUkEnQ;
      string VaSQKEtlSQ;
      if(jVWIkwodjm == LZYtKnryOq){OQHACmVNXR = true;}
      else if(LZYtKnryOq == jVWIkwodjm){QQfXeoKBRW = true;}
      if(lyYWAdXkwg == UbHhDIzjFE){wgAKnwdHoA = true;}
      else if(UbHhDIzjFE == lyYWAdXkwg){IwYielVrGJ = true;}
      if(qqlfYbfSeL == blQRkYVTJq){ISVbDzEORV = true;}
      else if(blQRkYVTJq == qqlfYbfSeL){JhbnSCoBiJ = true;}
      if(MbndYzXSmB == VaExpehbDd){xqIpihNset = true;}
      else if(VaExpehbDd == MbndYzXSmB){IIuqyHQNYG = true;}
      if(fjTdwWVXuQ == ciInKmZAZc){yXfWUnaHcN = true;}
      else if(ciInKmZAZc == fjTdwWVXuQ){zsXLeqHMwY = true;}
      if(sqsPyrjqjJ == JBpzJYJHJl){ZmwSHuufxD = true;}
      else if(JBpzJYJHJl == sqsPyrjqjJ){ViWsGhnqFb = true;}
      if(QWyXaKKuyA == SYoWUtXJrY){iGuCTEXKbF = true;}
      else if(SYoWUtXJrY == QWyXaKKuyA){AISINzAhjW = true;}
      if(FEyuBHWHiC == ZWfbarcbGy){ikctBkmyGO = true;}
      if(FHWORVhXef == yVtggUkEnQ){XwkDuKtphm = true;}
      if(PgidkJkuDl == VaSQKEtlSQ){mguaLrbdCP = true;}
      while(ZWfbarcbGy == FEyuBHWHiC){VITAJQJPJa = true;}
      while(yVtggUkEnQ == yVtggUkEnQ){tbEJmYlCjP = true;}
      while(VaSQKEtlSQ == VaSQKEtlSQ){SZHwFpZPxe = true;}
      if(OQHACmVNXR == true){OQHACmVNXR = false;}
      if(wgAKnwdHoA == true){wgAKnwdHoA = false;}
      if(ISVbDzEORV == true){ISVbDzEORV = false;}
      if(xqIpihNset == true){xqIpihNset = false;}
      if(yXfWUnaHcN == true){yXfWUnaHcN = false;}
      if(ZmwSHuufxD == true){ZmwSHuufxD = false;}
      if(iGuCTEXKbF == true){iGuCTEXKbF = false;}
      if(ikctBkmyGO == true){ikctBkmyGO = false;}
      if(XwkDuKtphm == true){XwkDuKtphm = false;}
      if(mguaLrbdCP == true){mguaLrbdCP = false;}
      if(QQfXeoKBRW == true){QQfXeoKBRW = false;}
      if(IwYielVrGJ == true){IwYielVrGJ = false;}
      if(JhbnSCoBiJ == true){JhbnSCoBiJ = false;}
      if(IIuqyHQNYG == true){IIuqyHQNYG = false;}
      if(zsXLeqHMwY == true){zsXLeqHMwY = false;}
      if(ViWsGhnqFb == true){ViWsGhnqFb = false;}
      if(AISINzAhjW == true){AISINzAhjW = false;}
      if(VITAJQJPJa == true){VITAJQJPJa = false;}
      if(tbEJmYlCjP == true){tbEJmYlCjP = false;}
      if(SZHwFpZPxe == true){SZHwFpZPxe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGJOXQEBWJ
{ 
  void HRzAsWXtUk()
  { 
      bool cpDwbJuCpU = false;
      bool UewPHZQrdF = false;
      bool GpWrwWTMVL = false;
      bool aTOkDgnfah = false;
      bool zfyLFeCitt = false;
      bool UtKFVmTLzF = false;
      bool ohfdtAQLMZ = false;
      bool lkQwFaqKlR = false;
      bool TjRbqfJIOP = false;
      bool NcfVrQzUQE = false;
      bool OpWTIidNzt = false;
      bool uIYhkFQEmN = false;
      bool pHwwMJFuDo = false;
      bool bWshDdNxTI = false;
      bool CuJUUFDyjm = false;
      bool AtgDNGsaHz = false;
      bool diKKSXOqdH = false;
      bool rSkeLuybaG = false;
      bool FGKQogopTw = false;
      bool jlpUdTkzCw = false;
      string pmNeHeTZCG;
      string jPXPWBKrmr;
      string mXmALlBYBD;
      string aIxaBQYHqH;
      string jdWuGNkCrX;
      string iYcxMRzMSU;
      string dtYyebRxNF;
      string cDAeIJArty;
      string BygcTCfzNi;
      string QLoWdoFXPe;
      string umolufXxoD;
      string RHSTTeNueb;
      string wSieoQNdBS;
      string DbbPCNJugm;
      string ehKKRIsUCy;
      string bJsmicDJwe;
      string SsuVzoeDRG;
      string VSOqxNIYMg;
      string WrbDqthofZ;
      string JzyCUklnKb;
      if(pmNeHeTZCG == umolufXxoD){cpDwbJuCpU = true;}
      else if(umolufXxoD == pmNeHeTZCG){OpWTIidNzt = true;}
      if(jPXPWBKrmr == RHSTTeNueb){UewPHZQrdF = true;}
      else if(RHSTTeNueb == jPXPWBKrmr){uIYhkFQEmN = true;}
      if(mXmALlBYBD == wSieoQNdBS){GpWrwWTMVL = true;}
      else if(wSieoQNdBS == mXmALlBYBD){pHwwMJFuDo = true;}
      if(aIxaBQYHqH == DbbPCNJugm){aTOkDgnfah = true;}
      else if(DbbPCNJugm == aIxaBQYHqH){bWshDdNxTI = true;}
      if(jdWuGNkCrX == ehKKRIsUCy){zfyLFeCitt = true;}
      else if(ehKKRIsUCy == jdWuGNkCrX){CuJUUFDyjm = true;}
      if(iYcxMRzMSU == bJsmicDJwe){UtKFVmTLzF = true;}
      else if(bJsmicDJwe == iYcxMRzMSU){AtgDNGsaHz = true;}
      if(dtYyebRxNF == SsuVzoeDRG){ohfdtAQLMZ = true;}
      else if(SsuVzoeDRG == dtYyebRxNF){diKKSXOqdH = true;}
      if(cDAeIJArty == VSOqxNIYMg){lkQwFaqKlR = true;}
      if(BygcTCfzNi == WrbDqthofZ){TjRbqfJIOP = true;}
      if(QLoWdoFXPe == JzyCUklnKb){NcfVrQzUQE = true;}
      while(VSOqxNIYMg == cDAeIJArty){rSkeLuybaG = true;}
      while(WrbDqthofZ == WrbDqthofZ){FGKQogopTw = true;}
      while(JzyCUklnKb == JzyCUklnKb){jlpUdTkzCw = true;}
      if(cpDwbJuCpU == true){cpDwbJuCpU = false;}
      if(UewPHZQrdF == true){UewPHZQrdF = false;}
      if(GpWrwWTMVL == true){GpWrwWTMVL = false;}
      if(aTOkDgnfah == true){aTOkDgnfah = false;}
      if(zfyLFeCitt == true){zfyLFeCitt = false;}
      if(UtKFVmTLzF == true){UtKFVmTLzF = false;}
      if(ohfdtAQLMZ == true){ohfdtAQLMZ = false;}
      if(lkQwFaqKlR == true){lkQwFaqKlR = false;}
      if(TjRbqfJIOP == true){TjRbqfJIOP = false;}
      if(NcfVrQzUQE == true){NcfVrQzUQE = false;}
      if(OpWTIidNzt == true){OpWTIidNzt = false;}
      if(uIYhkFQEmN == true){uIYhkFQEmN = false;}
      if(pHwwMJFuDo == true){pHwwMJFuDo = false;}
      if(bWshDdNxTI == true){bWshDdNxTI = false;}
      if(CuJUUFDyjm == true){CuJUUFDyjm = false;}
      if(AtgDNGsaHz == true){AtgDNGsaHz = false;}
      if(diKKSXOqdH == true){diKKSXOqdH = false;}
      if(rSkeLuybaG == true){rSkeLuybaG = false;}
      if(FGKQogopTw == true){FGKQogopTw = false;}
      if(jlpUdTkzCw == true){jlpUdTkzCw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOOCNFZLST
{ 
  void lUawKkzWDf()
  { 
      bool jUnxWlTDjf = false;
      bool IzgSPjIWun = false;
      bool TcKDObpfmB = false;
      bool MyZMGsCuAZ = false;
      bool gfXwJICLEu = false;
      bool RQOHZGJkit = false;
      bool unPhTKZTMV = false;
      bool gNVVGnFNsF = false;
      bool YdariwiSmA = false;
      bool iRMFdrPocy = false;
      bool ihzhNEtsAl = false;
      bool AwqcVQNXyW = false;
      bool aHgLlOBPqN = false;
      bool YPktWperde = false;
      bool BpRAzmaijM = false;
      bool erqFXbBmuz = false;
      bool CeBlMkKwFe = false;
      bool lUsTVkofMz = false;
      bool nReehgYeWu = false;
      bool oqwebWnfmN = false;
      string LsUXcarYlY;
      string VUtXIFSrwa;
      string zDAzmcWVcd;
      string dGCsNUbAQW;
      string oMDMbKbEJe;
      string toZLxHsUjz;
      string DWwItORBKm;
      string dRbYllAmXc;
      string BSLyiogquF;
      string aGQQTSQuSN;
      string rZtVAbMAZK;
      string HGxGxkKxYF;
      string gZFELWBLFS;
      string UEUJkbYoxG;
      string bgRkxUIJSh;
      string HTVMfRToJd;
      string aBtGoDknVV;
      string LVzSczIUHq;
      string NqrXLBiHcS;
      string HjeTeamKut;
      if(LsUXcarYlY == rZtVAbMAZK){jUnxWlTDjf = true;}
      else if(rZtVAbMAZK == LsUXcarYlY){ihzhNEtsAl = true;}
      if(VUtXIFSrwa == HGxGxkKxYF){IzgSPjIWun = true;}
      else if(HGxGxkKxYF == VUtXIFSrwa){AwqcVQNXyW = true;}
      if(zDAzmcWVcd == gZFELWBLFS){TcKDObpfmB = true;}
      else if(gZFELWBLFS == zDAzmcWVcd){aHgLlOBPqN = true;}
      if(dGCsNUbAQW == UEUJkbYoxG){MyZMGsCuAZ = true;}
      else if(UEUJkbYoxG == dGCsNUbAQW){YPktWperde = true;}
      if(oMDMbKbEJe == bgRkxUIJSh){gfXwJICLEu = true;}
      else if(bgRkxUIJSh == oMDMbKbEJe){BpRAzmaijM = true;}
      if(toZLxHsUjz == HTVMfRToJd){RQOHZGJkit = true;}
      else if(HTVMfRToJd == toZLxHsUjz){erqFXbBmuz = true;}
      if(DWwItORBKm == aBtGoDknVV){unPhTKZTMV = true;}
      else if(aBtGoDknVV == DWwItORBKm){CeBlMkKwFe = true;}
      if(dRbYllAmXc == LVzSczIUHq){gNVVGnFNsF = true;}
      if(BSLyiogquF == NqrXLBiHcS){YdariwiSmA = true;}
      if(aGQQTSQuSN == HjeTeamKut){iRMFdrPocy = true;}
      while(LVzSczIUHq == dRbYllAmXc){lUsTVkofMz = true;}
      while(NqrXLBiHcS == NqrXLBiHcS){nReehgYeWu = true;}
      while(HjeTeamKut == HjeTeamKut){oqwebWnfmN = true;}
      if(jUnxWlTDjf == true){jUnxWlTDjf = false;}
      if(IzgSPjIWun == true){IzgSPjIWun = false;}
      if(TcKDObpfmB == true){TcKDObpfmB = false;}
      if(MyZMGsCuAZ == true){MyZMGsCuAZ = false;}
      if(gfXwJICLEu == true){gfXwJICLEu = false;}
      if(RQOHZGJkit == true){RQOHZGJkit = false;}
      if(unPhTKZTMV == true){unPhTKZTMV = false;}
      if(gNVVGnFNsF == true){gNVVGnFNsF = false;}
      if(YdariwiSmA == true){YdariwiSmA = false;}
      if(iRMFdrPocy == true){iRMFdrPocy = false;}
      if(ihzhNEtsAl == true){ihzhNEtsAl = false;}
      if(AwqcVQNXyW == true){AwqcVQNXyW = false;}
      if(aHgLlOBPqN == true){aHgLlOBPqN = false;}
      if(YPktWperde == true){YPktWperde = false;}
      if(BpRAzmaijM == true){BpRAzmaijM = false;}
      if(erqFXbBmuz == true){erqFXbBmuz = false;}
      if(CeBlMkKwFe == true){CeBlMkKwFe = false;}
      if(lUsTVkofMz == true){lUsTVkofMz = false;}
      if(nReehgYeWu == true){nReehgYeWu = false;}
      if(oqwebWnfmN == true){oqwebWnfmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYQNLHUZPU
{ 
  void ijVGtFTDkW()
  { 
      bool nPJTktegRK = false;
      bool BNLMObhXSD = false;
      bool ThwdpwQJVr = false;
      bool YzheBOUofc = false;
      bool dPWcrTCHTp = false;
      bool GOwSEFTfcn = false;
      bool cVLYkBegKz = false;
      bool HsqpZELSlV = false;
      bool tIoflKDPZw = false;
      bool uoMqzIDyrp = false;
      bool oVwUiNWFrA = false;
      bool sAsGtTgelZ = false;
      bool yOGOERgzpR = false;
      bool ANawgXMUwY = false;
      bool mxWZCuuFxe = false;
      bool bXMRqaPhPQ = false;
      bool gWPazfZxZW = false;
      bool HLiMlBqfLJ = false;
      bool WaCLpbBIEG = false;
      bool HdEfrQhwaW = false;
      string lEUINqbUwR;
      string BxKgynKPLM;
      string ixuClgOuzn;
      string gghsOdNjxM;
      string ULswfwYbWz;
      string tJBjQnIRVg;
      string bgUIjTPRSU;
      string aaRyqXEzWo;
      string HmYAsXexcZ;
      string UuNQknqkLL;
      string gHIBXTqDss;
      string jJufYoITOM;
      string nRnszeMAND;
      string fSmKIAdWbZ;
      string fbEioKAhrw;
      string fWWyWOSPCs;
      string GqooMQWjXY;
      string KkrogMNFDo;
      string eeIRWIwnns;
      string hOUiSnmOWY;
      if(lEUINqbUwR == gHIBXTqDss){nPJTktegRK = true;}
      else if(gHIBXTqDss == lEUINqbUwR){oVwUiNWFrA = true;}
      if(BxKgynKPLM == jJufYoITOM){BNLMObhXSD = true;}
      else if(jJufYoITOM == BxKgynKPLM){sAsGtTgelZ = true;}
      if(ixuClgOuzn == nRnszeMAND){ThwdpwQJVr = true;}
      else if(nRnszeMAND == ixuClgOuzn){yOGOERgzpR = true;}
      if(gghsOdNjxM == fSmKIAdWbZ){YzheBOUofc = true;}
      else if(fSmKIAdWbZ == gghsOdNjxM){ANawgXMUwY = true;}
      if(ULswfwYbWz == fbEioKAhrw){dPWcrTCHTp = true;}
      else if(fbEioKAhrw == ULswfwYbWz){mxWZCuuFxe = true;}
      if(tJBjQnIRVg == fWWyWOSPCs){GOwSEFTfcn = true;}
      else if(fWWyWOSPCs == tJBjQnIRVg){bXMRqaPhPQ = true;}
      if(bgUIjTPRSU == GqooMQWjXY){cVLYkBegKz = true;}
      else if(GqooMQWjXY == bgUIjTPRSU){gWPazfZxZW = true;}
      if(aaRyqXEzWo == KkrogMNFDo){HsqpZELSlV = true;}
      if(HmYAsXexcZ == eeIRWIwnns){tIoflKDPZw = true;}
      if(UuNQknqkLL == hOUiSnmOWY){uoMqzIDyrp = true;}
      while(KkrogMNFDo == aaRyqXEzWo){HLiMlBqfLJ = true;}
      while(eeIRWIwnns == eeIRWIwnns){WaCLpbBIEG = true;}
      while(hOUiSnmOWY == hOUiSnmOWY){HdEfrQhwaW = true;}
      if(nPJTktegRK == true){nPJTktegRK = false;}
      if(BNLMObhXSD == true){BNLMObhXSD = false;}
      if(ThwdpwQJVr == true){ThwdpwQJVr = false;}
      if(YzheBOUofc == true){YzheBOUofc = false;}
      if(dPWcrTCHTp == true){dPWcrTCHTp = false;}
      if(GOwSEFTfcn == true){GOwSEFTfcn = false;}
      if(cVLYkBegKz == true){cVLYkBegKz = false;}
      if(HsqpZELSlV == true){HsqpZELSlV = false;}
      if(tIoflKDPZw == true){tIoflKDPZw = false;}
      if(uoMqzIDyrp == true){uoMqzIDyrp = false;}
      if(oVwUiNWFrA == true){oVwUiNWFrA = false;}
      if(sAsGtTgelZ == true){sAsGtTgelZ = false;}
      if(yOGOERgzpR == true){yOGOERgzpR = false;}
      if(ANawgXMUwY == true){ANawgXMUwY = false;}
      if(mxWZCuuFxe == true){mxWZCuuFxe = false;}
      if(bXMRqaPhPQ == true){bXMRqaPhPQ = false;}
      if(gWPazfZxZW == true){gWPazfZxZW = false;}
      if(HLiMlBqfLJ == true){HLiMlBqfLJ = false;}
      if(WaCLpbBIEG == true){WaCLpbBIEG = false;}
      if(HdEfrQhwaW == true){HdEfrQhwaW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHUJKBKKPN
{ 
  void CfOKceiHsX()
  { 
      bool QDwCmfNhmV = false;
      bool uVqloWgHwg = false;
      bool kMLCuUnBoN = false;
      bool NMWkPPmuUQ = false;
      bool QtgfiSdOaZ = false;
      bool CNsMUDqsGR = false;
      bool rMsZIizFVY = false;
      bool jllePqeeTc = false;
      bool qZZPKzTKPM = false;
      bool XsnCYEBHXA = false;
      bool TYsCoQaNxd = false;
      bool XMZdaRlcPI = false;
      bool PooJBpxjGK = false;
      bool oXHTIRfXZt = false;
      bool XFMknKTJbG = false;
      bool RXqPjdiiAz = false;
      bool SqHlozFFUI = false;
      bool kODVjJbDUp = false;
      bool VnIzrRgrid = false;
      bool iwWZagxawn = false;
      string yjZGhkFfGS;
      string NlTszLQddy;
      string BerVglpgbt;
      string bDEYzfpNtS;
      string CXWnlSCpQM;
      string VyNIySrEYu;
      string uYEMpKhusS;
      string UCiKwcHDiO;
      string iAQOXdouZf;
      string mlozXdTJxa;
      string kHwxqTOCLU;
      string LnUKLtHooM;
      string VlUMeiNjlS;
      string JxGHcbESXD;
      string OliEUyQdmd;
      string VeUkFyliRH;
      string GeQsLNhNgj;
      string poQlxiCQrf;
      string SixIxecUCe;
      string oUAPwjVpsG;
      if(yjZGhkFfGS == kHwxqTOCLU){QDwCmfNhmV = true;}
      else if(kHwxqTOCLU == yjZGhkFfGS){TYsCoQaNxd = true;}
      if(NlTszLQddy == LnUKLtHooM){uVqloWgHwg = true;}
      else if(LnUKLtHooM == NlTszLQddy){XMZdaRlcPI = true;}
      if(BerVglpgbt == VlUMeiNjlS){kMLCuUnBoN = true;}
      else if(VlUMeiNjlS == BerVglpgbt){PooJBpxjGK = true;}
      if(bDEYzfpNtS == JxGHcbESXD){NMWkPPmuUQ = true;}
      else if(JxGHcbESXD == bDEYzfpNtS){oXHTIRfXZt = true;}
      if(CXWnlSCpQM == OliEUyQdmd){QtgfiSdOaZ = true;}
      else if(OliEUyQdmd == CXWnlSCpQM){XFMknKTJbG = true;}
      if(VyNIySrEYu == VeUkFyliRH){CNsMUDqsGR = true;}
      else if(VeUkFyliRH == VyNIySrEYu){RXqPjdiiAz = true;}
      if(uYEMpKhusS == GeQsLNhNgj){rMsZIizFVY = true;}
      else if(GeQsLNhNgj == uYEMpKhusS){SqHlozFFUI = true;}
      if(UCiKwcHDiO == poQlxiCQrf){jllePqeeTc = true;}
      if(iAQOXdouZf == SixIxecUCe){qZZPKzTKPM = true;}
      if(mlozXdTJxa == oUAPwjVpsG){XsnCYEBHXA = true;}
      while(poQlxiCQrf == UCiKwcHDiO){kODVjJbDUp = true;}
      while(SixIxecUCe == SixIxecUCe){VnIzrRgrid = true;}
      while(oUAPwjVpsG == oUAPwjVpsG){iwWZagxawn = true;}
      if(QDwCmfNhmV == true){QDwCmfNhmV = false;}
      if(uVqloWgHwg == true){uVqloWgHwg = false;}
      if(kMLCuUnBoN == true){kMLCuUnBoN = false;}
      if(NMWkPPmuUQ == true){NMWkPPmuUQ = false;}
      if(QtgfiSdOaZ == true){QtgfiSdOaZ = false;}
      if(CNsMUDqsGR == true){CNsMUDqsGR = false;}
      if(rMsZIizFVY == true){rMsZIizFVY = false;}
      if(jllePqeeTc == true){jllePqeeTc = false;}
      if(qZZPKzTKPM == true){qZZPKzTKPM = false;}
      if(XsnCYEBHXA == true){XsnCYEBHXA = false;}
      if(TYsCoQaNxd == true){TYsCoQaNxd = false;}
      if(XMZdaRlcPI == true){XMZdaRlcPI = false;}
      if(PooJBpxjGK == true){PooJBpxjGK = false;}
      if(oXHTIRfXZt == true){oXHTIRfXZt = false;}
      if(XFMknKTJbG == true){XFMknKTJbG = false;}
      if(RXqPjdiiAz == true){RXqPjdiiAz = false;}
      if(SqHlozFFUI == true){SqHlozFFUI = false;}
      if(kODVjJbDUp == true){kODVjJbDUp = false;}
      if(VnIzrRgrid == true){VnIzrRgrid = false;}
      if(iwWZagxawn == true){iwWZagxawn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGFZHNGMBL
{ 
  void SltjOSBcGg()
  { 
      bool VrmUUjjcAo = false;
      bool TJIikRxifb = false;
      bool KExEhDyVzk = false;
      bool jBqMjMfJoW = false;
      bool iuuKNaZxNV = false;
      bool rxlfZRthlQ = false;
      bool lNdPFSRwzY = false;
      bool lmsJrPIlqH = false;
      bool dAHdrlOLlS = false;
      bool RxXYjURfFt = false;
      bool IdyoiFEcmK = false;
      bool IHpemlGzWS = false;
      bool EGJgHnPUYX = false;
      bool xcgwyzBStm = false;
      bool hkXbJJHrly = false;
      bool ORIlpCTRhu = false;
      bool piEPMfasgm = false;
      bool jmFjjSigWx = false;
      bool gWhaIfTuGu = false;
      bool fjkyxygHPd = false;
      string HdgRwghgVg;
      string UBwAlmpjVE;
      string nNOZegtlwF;
      string btOanLARPV;
      string OAtXWyeitW;
      string BOKzGtPGlO;
      string mujPEamVLa;
      string mXTApnTpDf;
      string CLrZDMjOUt;
      string wsfAhSPdSw;
      string LJWTjduKJS;
      string ZYDGMaDKMr;
      string pYARdsrSRW;
      string XpXGTsnXoY;
      string RZECUXoYnH;
      string PEQaGmIFpp;
      string kbsltjBxlT;
      string mfUmZQTywG;
      string ESeJGSYwAg;
      string kigznofSHj;
      if(HdgRwghgVg == LJWTjduKJS){VrmUUjjcAo = true;}
      else if(LJWTjduKJS == HdgRwghgVg){IdyoiFEcmK = true;}
      if(UBwAlmpjVE == ZYDGMaDKMr){TJIikRxifb = true;}
      else if(ZYDGMaDKMr == UBwAlmpjVE){IHpemlGzWS = true;}
      if(nNOZegtlwF == pYARdsrSRW){KExEhDyVzk = true;}
      else if(pYARdsrSRW == nNOZegtlwF){EGJgHnPUYX = true;}
      if(btOanLARPV == XpXGTsnXoY){jBqMjMfJoW = true;}
      else if(XpXGTsnXoY == btOanLARPV){xcgwyzBStm = true;}
      if(OAtXWyeitW == RZECUXoYnH){iuuKNaZxNV = true;}
      else if(RZECUXoYnH == OAtXWyeitW){hkXbJJHrly = true;}
      if(BOKzGtPGlO == PEQaGmIFpp){rxlfZRthlQ = true;}
      else if(PEQaGmIFpp == BOKzGtPGlO){ORIlpCTRhu = true;}
      if(mujPEamVLa == kbsltjBxlT){lNdPFSRwzY = true;}
      else if(kbsltjBxlT == mujPEamVLa){piEPMfasgm = true;}
      if(mXTApnTpDf == mfUmZQTywG){lmsJrPIlqH = true;}
      if(CLrZDMjOUt == ESeJGSYwAg){dAHdrlOLlS = true;}
      if(wsfAhSPdSw == kigznofSHj){RxXYjURfFt = true;}
      while(mfUmZQTywG == mXTApnTpDf){jmFjjSigWx = true;}
      while(ESeJGSYwAg == ESeJGSYwAg){gWhaIfTuGu = true;}
      while(kigznofSHj == kigznofSHj){fjkyxygHPd = true;}
      if(VrmUUjjcAo == true){VrmUUjjcAo = false;}
      if(TJIikRxifb == true){TJIikRxifb = false;}
      if(KExEhDyVzk == true){KExEhDyVzk = false;}
      if(jBqMjMfJoW == true){jBqMjMfJoW = false;}
      if(iuuKNaZxNV == true){iuuKNaZxNV = false;}
      if(rxlfZRthlQ == true){rxlfZRthlQ = false;}
      if(lNdPFSRwzY == true){lNdPFSRwzY = false;}
      if(lmsJrPIlqH == true){lmsJrPIlqH = false;}
      if(dAHdrlOLlS == true){dAHdrlOLlS = false;}
      if(RxXYjURfFt == true){RxXYjURfFt = false;}
      if(IdyoiFEcmK == true){IdyoiFEcmK = false;}
      if(IHpemlGzWS == true){IHpemlGzWS = false;}
      if(EGJgHnPUYX == true){EGJgHnPUYX = false;}
      if(xcgwyzBStm == true){xcgwyzBStm = false;}
      if(hkXbJJHrly == true){hkXbJJHrly = false;}
      if(ORIlpCTRhu == true){ORIlpCTRhu = false;}
      if(piEPMfasgm == true){piEPMfasgm = false;}
      if(jmFjjSigWx == true){jmFjjSigWx = false;}
      if(gWhaIfTuGu == true){gWhaIfTuGu = false;}
      if(fjkyxygHPd == true){fjkyxygHPd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGVIROPBKQ
{ 
  void kXyfksugyX()
  { 
      bool DtPTVeqcQr = false;
      bool YJRjTEwpVL = false;
      bool tssMynECuR = false;
      bool AzWbeGAfqL = false;
      bool ymkWybUEem = false;
      bool NgacDJACVh = false;
      bool ZohzqYlpFM = false;
      bool DQzJMHHVOV = false;
      bool SzWIDSYtYU = false;
      bool FyJIlJFlfY = false;
      bool pezSiwhQPw = false;
      bool BemzPaSZuX = false;
      bool zrRjGEGpXD = false;
      bool CVopfmzDYG = false;
      bool kHebTaKKsK = false;
      bool pfqIZxNOLe = false;
      bool orsLtfoxTb = false;
      bool aOBnmrMoQe = false;
      bool twwMMVdgQh = false;
      bool ZjrtRsNShn = false;
      string nEpZqkqTUy;
      string IrgWcYINjZ;
      string TDpEgYVgIY;
      string HSCGlEdSOU;
      string jXJSGPwNYR;
      string bzcRfkOlrS;
      string PJKupopakX;
      string tpzPousWxQ;
      string bIIpxHokZA;
      string pqZuEZMNbQ;
      string ZVbAWkANbj;
      string qqoaqHBTyi;
      string AFAjgDPEKP;
      string ifufqGfHSL;
      string GaIoJzCzEx;
      string XrPrQUUrST;
      string UwDMBLwIij;
      string asBlbYwKZh;
      string AQzMqpQCPW;
      string lmozqKXwny;
      if(nEpZqkqTUy == ZVbAWkANbj){DtPTVeqcQr = true;}
      else if(ZVbAWkANbj == nEpZqkqTUy){pezSiwhQPw = true;}
      if(IrgWcYINjZ == qqoaqHBTyi){YJRjTEwpVL = true;}
      else if(qqoaqHBTyi == IrgWcYINjZ){BemzPaSZuX = true;}
      if(TDpEgYVgIY == AFAjgDPEKP){tssMynECuR = true;}
      else if(AFAjgDPEKP == TDpEgYVgIY){zrRjGEGpXD = true;}
      if(HSCGlEdSOU == ifufqGfHSL){AzWbeGAfqL = true;}
      else if(ifufqGfHSL == HSCGlEdSOU){CVopfmzDYG = true;}
      if(jXJSGPwNYR == GaIoJzCzEx){ymkWybUEem = true;}
      else if(GaIoJzCzEx == jXJSGPwNYR){kHebTaKKsK = true;}
      if(bzcRfkOlrS == XrPrQUUrST){NgacDJACVh = true;}
      else if(XrPrQUUrST == bzcRfkOlrS){pfqIZxNOLe = true;}
      if(PJKupopakX == UwDMBLwIij){ZohzqYlpFM = true;}
      else if(UwDMBLwIij == PJKupopakX){orsLtfoxTb = true;}
      if(tpzPousWxQ == asBlbYwKZh){DQzJMHHVOV = true;}
      if(bIIpxHokZA == AQzMqpQCPW){SzWIDSYtYU = true;}
      if(pqZuEZMNbQ == lmozqKXwny){FyJIlJFlfY = true;}
      while(asBlbYwKZh == tpzPousWxQ){aOBnmrMoQe = true;}
      while(AQzMqpQCPW == AQzMqpQCPW){twwMMVdgQh = true;}
      while(lmozqKXwny == lmozqKXwny){ZjrtRsNShn = true;}
      if(DtPTVeqcQr == true){DtPTVeqcQr = false;}
      if(YJRjTEwpVL == true){YJRjTEwpVL = false;}
      if(tssMynECuR == true){tssMynECuR = false;}
      if(AzWbeGAfqL == true){AzWbeGAfqL = false;}
      if(ymkWybUEem == true){ymkWybUEem = false;}
      if(NgacDJACVh == true){NgacDJACVh = false;}
      if(ZohzqYlpFM == true){ZohzqYlpFM = false;}
      if(DQzJMHHVOV == true){DQzJMHHVOV = false;}
      if(SzWIDSYtYU == true){SzWIDSYtYU = false;}
      if(FyJIlJFlfY == true){FyJIlJFlfY = false;}
      if(pezSiwhQPw == true){pezSiwhQPw = false;}
      if(BemzPaSZuX == true){BemzPaSZuX = false;}
      if(zrRjGEGpXD == true){zrRjGEGpXD = false;}
      if(CVopfmzDYG == true){CVopfmzDYG = false;}
      if(kHebTaKKsK == true){kHebTaKKsK = false;}
      if(pfqIZxNOLe == true){pfqIZxNOLe = false;}
      if(orsLtfoxTb == true){orsLtfoxTb = false;}
      if(aOBnmrMoQe == true){aOBnmrMoQe = false;}
      if(twwMMVdgQh == true){twwMMVdgQh = false;}
      if(ZjrtRsNShn == true){ZjrtRsNShn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLHWOPDIBZ
{ 
  void bcFAmKyBsf()
  { 
      bool AIXZpFWiyg = false;
      bool PMcShQdVUr = false;
      bool hTmXoRFUJU = false;
      bool KtxoqDJalP = false;
      bool otFlTwpTLY = false;
      bool qHlfagUzkX = false;
      bool ABZcWVOmae = false;
      bool GDjEDmOBDr = false;
      bool akIjcCIRNK = false;
      bool hJpOPmTbOy = false;
      bool gCsfRnXgcn = false;
      bool RTwrwOrpAU = false;
      bool NxZPxwNVoP = false;
      bool SllFKYrbSo = false;
      bool daoZrONxRA = false;
      bool udbtkjcciV = false;
      bool aCqNUfgphX = false;
      bool WPWKplIzWh = false;
      bool hQDoToKrUZ = false;
      bool uOswNbjbFM = false;
      string uxpQKNZfww;
      string ikAOoaMadN;
      string soFOppuJRJ;
      string zmcVAhmMkW;
      string FEHdjYNHiI;
      string KtITpGraZU;
      string RQOlwwIeNH;
      string mzpHInhadR;
      string bnZJzEdIet;
      string pMmQEnpUgn;
      string QitbUKEBKC;
      string YRwIrdpEmq;
      string RzzTQaMYCT;
      string xMspAssyon;
      string AcycUYPeYZ;
      string ylhoVQiaKt;
      string yeyqELXGHy;
      string jrPyqoBWyr;
      string LhAbVLdDTj;
      string JSmtoVdGYI;
      if(uxpQKNZfww == QitbUKEBKC){AIXZpFWiyg = true;}
      else if(QitbUKEBKC == uxpQKNZfww){gCsfRnXgcn = true;}
      if(ikAOoaMadN == YRwIrdpEmq){PMcShQdVUr = true;}
      else if(YRwIrdpEmq == ikAOoaMadN){RTwrwOrpAU = true;}
      if(soFOppuJRJ == RzzTQaMYCT){hTmXoRFUJU = true;}
      else if(RzzTQaMYCT == soFOppuJRJ){NxZPxwNVoP = true;}
      if(zmcVAhmMkW == xMspAssyon){KtxoqDJalP = true;}
      else if(xMspAssyon == zmcVAhmMkW){SllFKYrbSo = true;}
      if(FEHdjYNHiI == AcycUYPeYZ){otFlTwpTLY = true;}
      else if(AcycUYPeYZ == FEHdjYNHiI){daoZrONxRA = true;}
      if(KtITpGraZU == ylhoVQiaKt){qHlfagUzkX = true;}
      else if(ylhoVQiaKt == KtITpGraZU){udbtkjcciV = true;}
      if(RQOlwwIeNH == yeyqELXGHy){ABZcWVOmae = true;}
      else if(yeyqELXGHy == RQOlwwIeNH){aCqNUfgphX = true;}
      if(mzpHInhadR == jrPyqoBWyr){GDjEDmOBDr = true;}
      if(bnZJzEdIet == LhAbVLdDTj){akIjcCIRNK = true;}
      if(pMmQEnpUgn == JSmtoVdGYI){hJpOPmTbOy = true;}
      while(jrPyqoBWyr == mzpHInhadR){WPWKplIzWh = true;}
      while(LhAbVLdDTj == LhAbVLdDTj){hQDoToKrUZ = true;}
      while(JSmtoVdGYI == JSmtoVdGYI){uOswNbjbFM = true;}
      if(AIXZpFWiyg == true){AIXZpFWiyg = false;}
      if(PMcShQdVUr == true){PMcShQdVUr = false;}
      if(hTmXoRFUJU == true){hTmXoRFUJU = false;}
      if(KtxoqDJalP == true){KtxoqDJalP = false;}
      if(otFlTwpTLY == true){otFlTwpTLY = false;}
      if(qHlfagUzkX == true){qHlfagUzkX = false;}
      if(ABZcWVOmae == true){ABZcWVOmae = false;}
      if(GDjEDmOBDr == true){GDjEDmOBDr = false;}
      if(akIjcCIRNK == true){akIjcCIRNK = false;}
      if(hJpOPmTbOy == true){hJpOPmTbOy = false;}
      if(gCsfRnXgcn == true){gCsfRnXgcn = false;}
      if(RTwrwOrpAU == true){RTwrwOrpAU = false;}
      if(NxZPxwNVoP == true){NxZPxwNVoP = false;}
      if(SllFKYrbSo == true){SllFKYrbSo = false;}
      if(daoZrONxRA == true){daoZrONxRA = false;}
      if(udbtkjcciV == true){udbtkjcciV = false;}
      if(aCqNUfgphX == true){aCqNUfgphX = false;}
      if(WPWKplIzWh == true){WPWKplIzWh = false;}
      if(hQDoToKrUZ == true){hQDoToKrUZ = false;}
      if(uOswNbjbFM == true){uOswNbjbFM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNQDMWHHPX
{ 
  void EKQfzgPeAN()
  { 
      bool LPuGPycIWU = false;
      bool uRPfqAdeAD = false;
      bool jHuJAiEDqK = false;
      bool jrRZIYfirz = false;
      bool ctBogKuUjg = false;
      bool tkcUHDTkFg = false;
      bool sYQLkCAoXS = false;
      bool TtlBZpGGbp = false;
      bool mjSKPyPwRE = false;
      bool EudLFEcoEe = false;
      bool JFwQMzyatR = false;
      bool xNJOsJGGul = false;
      bool mDXTNYQauV = false;
      bool NQBxggmByQ = false;
      bool zoCzGqlOSw = false;
      bool xWsRrGhcDm = false;
      bool iXeYEgLLhL = false;
      bool VEHelxBXMW = false;
      bool mBHzXpWjFZ = false;
      bool yJyKgbJcuZ = false;
      string VVtqMNLzqL;
      string wLVckXlBTs;
      string uxBAyeDpLL;
      string AempbWDKeF;
      string gjwqrnMfbL;
      string OPTLiYUtsg;
      string JVnfKQYeAO;
      string TbWNMKBKHK;
      string SXOAwjKaGD;
      string CIQxuKwQfa;
      string PgeMqmrGzX;
      string XKmhOlHnia;
      string FxYxMKKYRB;
      string OjdfukrBIJ;
      string qEaherViiJ;
      string DIhFVRIhAf;
      string bTnyJmfGmc;
      string sFeYiAVpRT;
      string nboIxGCXKc;
      string bKBbgXQcYr;
      if(VVtqMNLzqL == PgeMqmrGzX){LPuGPycIWU = true;}
      else if(PgeMqmrGzX == VVtqMNLzqL){JFwQMzyatR = true;}
      if(wLVckXlBTs == XKmhOlHnia){uRPfqAdeAD = true;}
      else if(XKmhOlHnia == wLVckXlBTs){xNJOsJGGul = true;}
      if(uxBAyeDpLL == FxYxMKKYRB){jHuJAiEDqK = true;}
      else if(FxYxMKKYRB == uxBAyeDpLL){mDXTNYQauV = true;}
      if(AempbWDKeF == OjdfukrBIJ){jrRZIYfirz = true;}
      else if(OjdfukrBIJ == AempbWDKeF){NQBxggmByQ = true;}
      if(gjwqrnMfbL == qEaherViiJ){ctBogKuUjg = true;}
      else if(qEaherViiJ == gjwqrnMfbL){zoCzGqlOSw = true;}
      if(OPTLiYUtsg == DIhFVRIhAf){tkcUHDTkFg = true;}
      else if(DIhFVRIhAf == OPTLiYUtsg){xWsRrGhcDm = true;}
      if(JVnfKQYeAO == bTnyJmfGmc){sYQLkCAoXS = true;}
      else if(bTnyJmfGmc == JVnfKQYeAO){iXeYEgLLhL = true;}
      if(TbWNMKBKHK == sFeYiAVpRT){TtlBZpGGbp = true;}
      if(SXOAwjKaGD == nboIxGCXKc){mjSKPyPwRE = true;}
      if(CIQxuKwQfa == bKBbgXQcYr){EudLFEcoEe = true;}
      while(sFeYiAVpRT == TbWNMKBKHK){VEHelxBXMW = true;}
      while(nboIxGCXKc == nboIxGCXKc){mBHzXpWjFZ = true;}
      while(bKBbgXQcYr == bKBbgXQcYr){yJyKgbJcuZ = true;}
      if(LPuGPycIWU == true){LPuGPycIWU = false;}
      if(uRPfqAdeAD == true){uRPfqAdeAD = false;}
      if(jHuJAiEDqK == true){jHuJAiEDqK = false;}
      if(jrRZIYfirz == true){jrRZIYfirz = false;}
      if(ctBogKuUjg == true){ctBogKuUjg = false;}
      if(tkcUHDTkFg == true){tkcUHDTkFg = false;}
      if(sYQLkCAoXS == true){sYQLkCAoXS = false;}
      if(TtlBZpGGbp == true){TtlBZpGGbp = false;}
      if(mjSKPyPwRE == true){mjSKPyPwRE = false;}
      if(EudLFEcoEe == true){EudLFEcoEe = false;}
      if(JFwQMzyatR == true){JFwQMzyatR = false;}
      if(xNJOsJGGul == true){xNJOsJGGul = false;}
      if(mDXTNYQauV == true){mDXTNYQauV = false;}
      if(NQBxggmByQ == true){NQBxggmByQ = false;}
      if(zoCzGqlOSw == true){zoCzGqlOSw = false;}
      if(xWsRrGhcDm == true){xWsRrGhcDm = false;}
      if(iXeYEgLLhL == true){iXeYEgLLhL = false;}
      if(VEHelxBXMW == true){VEHelxBXMW = false;}
      if(mBHzXpWjFZ == true){mBHzXpWjFZ = false;}
      if(yJyKgbJcuZ == true){yJyKgbJcuZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJHYNMDUXK
{ 
  void MCiTPQzVJK()
  { 
      bool CxQBcgIrYf = false;
      bool nuVkQZzqZq = false;
      bool CYnXnUtSRh = false;
      bool RpWZeAbYSV = false;
      bool pKnbyPMsqg = false;
      bool zpPZXdJsNI = false;
      bool lpZqOxXuGQ = false;
      bool yaXDBrjLYY = false;
      bool HBbkhaawCA = false;
      bool phLKiAjxNA = false;
      bool qRlZiYSMYf = false;
      bool sxTnBkOoIm = false;
      bool WarFZPONTA = false;
      bool HmyYgoOBCJ = false;
      bool IOWWHsNWIx = false;
      bool ktnZcQYgAS = false;
      bool JErYXFzuHL = false;
      bool WMmyeIDVxf = false;
      bool CrEVOMyYuQ = false;
      bool QgAiADVyyC = false;
      string QHHgSBxeVg;
      string OdJqtQpnQU;
      string YJXmrunpEK;
      string zLbaJdweRB;
      string iIasBTRiEa;
      string yXdXqGjUnW;
      string NHaLgCCihP;
      string TKVPkQielX;
      string dFkdMahEjC;
      string tbqtmbgPLy;
      string RiBnGmCNla;
      string XFiPsHVxyF;
      string TyyeVqTbbJ;
      string iSSmGtEwWZ;
      string YTRJeosaAf;
      string GiQFeTjVSO;
      string SZlcqEluJz;
      string DYaYgzfoAg;
      string ysauDzCMHl;
      string KhdHGyhoRZ;
      if(QHHgSBxeVg == RiBnGmCNla){CxQBcgIrYf = true;}
      else if(RiBnGmCNla == QHHgSBxeVg){qRlZiYSMYf = true;}
      if(OdJqtQpnQU == XFiPsHVxyF){nuVkQZzqZq = true;}
      else if(XFiPsHVxyF == OdJqtQpnQU){sxTnBkOoIm = true;}
      if(YJXmrunpEK == TyyeVqTbbJ){CYnXnUtSRh = true;}
      else if(TyyeVqTbbJ == YJXmrunpEK){WarFZPONTA = true;}
      if(zLbaJdweRB == iSSmGtEwWZ){RpWZeAbYSV = true;}
      else if(iSSmGtEwWZ == zLbaJdweRB){HmyYgoOBCJ = true;}
      if(iIasBTRiEa == YTRJeosaAf){pKnbyPMsqg = true;}
      else if(YTRJeosaAf == iIasBTRiEa){IOWWHsNWIx = true;}
      if(yXdXqGjUnW == GiQFeTjVSO){zpPZXdJsNI = true;}
      else if(GiQFeTjVSO == yXdXqGjUnW){ktnZcQYgAS = true;}
      if(NHaLgCCihP == SZlcqEluJz){lpZqOxXuGQ = true;}
      else if(SZlcqEluJz == NHaLgCCihP){JErYXFzuHL = true;}
      if(TKVPkQielX == DYaYgzfoAg){yaXDBrjLYY = true;}
      if(dFkdMahEjC == ysauDzCMHl){HBbkhaawCA = true;}
      if(tbqtmbgPLy == KhdHGyhoRZ){phLKiAjxNA = true;}
      while(DYaYgzfoAg == TKVPkQielX){WMmyeIDVxf = true;}
      while(ysauDzCMHl == ysauDzCMHl){CrEVOMyYuQ = true;}
      while(KhdHGyhoRZ == KhdHGyhoRZ){QgAiADVyyC = true;}
      if(CxQBcgIrYf == true){CxQBcgIrYf = false;}
      if(nuVkQZzqZq == true){nuVkQZzqZq = false;}
      if(CYnXnUtSRh == true){CYnXnUtSRh = false;}
      if(RpWZeAbYSV == true){RpWZeAbYSV = false;}
      if(pKnbyPMsqg == true){pKnbyPMsqg = false;}
      if(zpPZXdJsNI == true){zpPZXdJsNI = false;}
      if(lpZqOxXuGQ == true){lpZqOxXuGQ = false;}
      if(yaXDBrjLYY == true){yaXDBrjLYY = false;}
      if(HBbkhaawCA == true){HBbkhaawCA = false;}
      if(phLKiAjxNA == true){phLKiAjxNA = false;}
      if(qRlZiYSMYf == true){qRlZiYSMYf = false;}
      if(sxTnBkOoIm == true){sxTnBkOoIm = false;}
      if(WarFZPONTA == true){WarFZPONTA = false;}
      if(HmyYgoOBCJ == true){HmyYgoOBCJ = false;}
      if(IOWWHsNWIx == true){IOWWHsNWIx = false;}
      if(ktnZcQYgAS == true){ktnZcQYgAS = false;}
      if(JErYXFzuHL == true){JErYXFzuHL = false;}
      if(WMmyeIDVxf == true){WMmyeIDVxf = false;}
      if(CrEVOMyYuQ == true){CrEVOMyYuQ = false;}
      if(QgAiADVyyC == true){QgAiADVyyC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QSKZTRFUTH
{ 
  void UlJaBVzCTK()
  { 
      bool oDPOKNXgdT = false;
      bool ojkriDkpNH = false;
      bool sZKunrDkgF = false;
      bool RLyzzOjDkX = false;
      bool TECiAozbno = false;
      bool JmTYWOrUZS = false;
      bool KlzYBcklsU = false;
      bool TgFpmoWatz = false;
      bool raxquerYbj = false;
      bool VOcRNhEchW = false;
      bool EMiTVbgdlh = false;
      bool rQZaZinHcV = false;
      bool kLKIyEEmcF = false;
      bool jssWuerdVT = false;
      bool xNmtrEoCrd = false;
      bool sxALlrCaUR = false;
      bool XtAfxyXCft = false;
      bool qKkJYWXQQt = false;
      bool PBtyMmsgkC = false;
      bool cRIEuDNHws = false;
      string hbeXUGXNzR;
      string exbyUzRSzm;
      string ojSIdErfXV;
      string UlOMRXSEtP;
      string DDJbRtosOP;
      string RWDHJyJWtQ;
      string NqocxshOfx;
      string fMYjjlZpqj;
      string OzRIDxhGDT;
      string NwKdBLNgeY;
      string LaNQjFyTXX;
      string XSeJBOZgYz;
      string KbLLjiBthX;
      string XsLRYnlBXy;
      string zOhfwuQBbm;
      string lgHeOiOBgA;
      string EDkAzeGNkN;
      string cXIaAutePn;
      string RASulqkgCo;
      string YjUWsuchgQ;
      if(hbeXUGXNzR == LaNQjFyTXX){oDPOKNXgdT = true;}
      else if(LaNQjFyTXX == hbeXUGXNzR){EMiTVbgdlh = true;}
      if(exbyUzRSzm == XSeJBOZgYz){ojkriDkpNH = true;}
      else if(XSeJBOZgYz == exbyUzRSzm){rQZaZinHcV = true;}
      if(ojSIdErfXV == KbLLjiBthX){sZKunrDkgF = true;}
      else if(KbLLjiBthX == ojSIdErfXV){kLKIyEEmcF = true;}
      if(UlOMRXSEtP == XsLRYnlBXy){RLyzzOjDkX = true;}
      else if(XsLRYnlBXy == UlOMRXSEtP){jssWuerdVT = true;}
      if(DDJbRtosOP == zOhfwuQBbm){TECiAozbno = true;}
      else if(zOhfwuQBbm == DDJbRtosOP){xNmtrEoCrd = true;}
      if(RWDHJyJWtQ == lgHeOiOBgA){JmTYWOrUZS = true;}
      else if(lgHeOiOBgA == RWDHJyJWtQ){sxALlrCaUR = true;}
      if(NqocxshOfx == EDkAzeGNkN){KlzYBcklsU = true;}
      else if(EDkAzeGNkN == NqocxshOfx){XtAfxyXCft = true;}
      if(fMYjjlZpqj == cXIaAutePn){TgFpmoWatz = true;}
      if(OzRIDxhGDT == RASulqkgCo){raxquerYbj = true;}
      if(NwKdBLNgeY == YjUWsuchgQ){VOcRNhEchW = true;}
      while(cXIaAutePn == fMYjjlZpqj){qKkJYWXQQt = true;}
      while(RASulqkgCo == RASulqkgCo){PBtyMmsgkC = true;}
      while(YjUWsuchgQ == YjUWsuchgQ){cRIEuDNHws = true;}
      if(oDPOKNXgdT == true){oDPOKNXgdT = false;}
      if(ojkriDkpNH == true){ojkriDkpNH = false;}
      if(sZKunrDkgF == true){sZKunrDkgF = false;}
      if(RLyzzOjDkX == true){RLyzzOjDkX = false;}
      if(TECiAozbno == true){TECiAozbno = false;}
      if(JmTYWOrUZS == true){JmTYWOrUZS = false;}
      if(KlzYBcklsU == true){KlzYBcklsU = false;}
      if(TgFpmoWatz == true){TgFpmoWatz = false;}
      if(raxquerYbj == true){raxquerYbj = false;}
      if(VOcRNhEchW == true){VOcRNhEchW = false;}
      if(EMiTVbgdlh == true){EMiTVbgdlh = false;}
      if(rQZaZinHcV == true){rQZaZinHcV = false;}
      if(kLKIyEEmcF == true){kLKIyEEmcF = false;}
      if(jssWuerdVT == true){jssWuerdVT = false;}
      if(xNmtrEoCrd == true){xNmtrEoCrd = false;}
      if(sxALlrCaUR == true){sxALlrCaUR = false;}
      if(XtAfxyXCft == true){XtAfxyXCft = false;}
      if(qKkJYWXQQt == true){qKkJYWXQQt = false;}
      if(PBtyMmsgkC == true){PBtyMmsgkC = false;}
      if(cRIEuDNHws == true){cRIEuDNHws = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLZNLKUGJP
{ 
  void BQDZSZtFtR()
  { 
      bool BQDcMtoeRo = false;
      bool IhVyaXebnA = false;
      bool HdAZIqnSJN = false;
      bool LLbSrGjWLR = false;
      bool NCTKllZZlE = false;
      bool kbfWCXQdTV = false;
      bool GWVDcwFDGU = false;
      bool mHQWlFKpmW = false;
      bool QOfFbjfFQU = false;
      bool pGCoKqgPgo = false;
      bool fWTRQdKJjx = false;
      bool MZpxEqqQas = false;
      bool QzlkdgEaLu = false;
      bool XtIxqttNny = false;
      bool YVVSHPPFkS = false;
      bool zQomYfjhni = false;
      bool YjxoYSQrGK = false;
      bool wdbbTtdSdN = false;
      bool QzpruHFVYK = false;
      bool JMZEZoXfso = false;
      string LfqiimrpLY;
      string JCBwiUpTCl;
      string uahFGtbtyW;
      string PKMXaLJDau;
      string hGheYfkAay;
      string JggXSjylcn;
      string LxrnJypdVX;
      string LlsHEnsCfZ;
      string IbTzMidnEq;
      string MWalikOsVa;
      string pHeDmXmYTd;
      string pwFDejcrbZ;
      string UBZeKnLHXT;
      string ZAgFiBwQMo;
      string wEUaAQQWGz;
      string HVRuFogAry;
      string MeAADpOATc;
      string mMfldPfzds;
      string WnAXLDhkzt;
      string UwXNcQEUWK;
      if(LfqiimrpLY == pHeDmXmYTd){BQDcMtoeRo = true;}
      else if(pHeDmXmYTd == LfqiimrpLY){fWTRQdKJjx = true;}
      if(JCBwiUpTCl == pwFDejcrbZ){IhVyaXebnA = true;}
      else if(pwFDejcrbZ == JCBwiUpTCl){MZpxEqqQas = true;}
      if(uahFGtbtyW == UBZeKnLHXT){HdAZIqnSJN = true;}
      else if(UBZeKnLHXT == uahFGtbtyW){QzlkdgEaLu = true;}
      if(PKMXaLJDau == ZAgFiBwQMo){LLbSrGjWLR = true;}
      else if(ZAgFiBwQMo == PKMXaLJDau){XtIxqttNny = true;}
      if(hGheYfkAay == wEUaAQQWGz){NCTKllZZlE = true;}
      else if(wEUaAQQWGz == hGheYfkAay){YVVSHPPFkS = true;}
      if(JggXSjylcn == HVRuFogAry){kbfWCXQdTV = true;}
      else if(HVRuFogAry == JggXSjylcn){zQomYfjhni = true;}
      if(LxrnJypdVX == MeAADpOATc){GWVDcwFDGU = true;}
      else if(MeAADpOATc == LxrnJypdVX){YjxoYSQrGK = true;}
      if(LlsHEnsCfZ == mMfldPfzds){mHQWlFKpmW = true;}
      if(IbTzMidnEq == WnAXLDhkzt){QOfFbjfFQU = true;}
      if(MWalikOsVa == UwXNcQEUWK){pGCoKqgPgo = true;}
      while(mMfldPfzds == LlsHEnsCfZ){wdbbTtdSdN = true;}
      while(WnAXLDhkzt == WnAXLDhkzt){QzpruHFVYK = true;}
      while(UwXNcQEUWK == UwXNcQEUWK){JMZEZoXfso = true;}
      if(BQDcMtoeRo == true){BQDcMtoeRo = false;}
      if(IhVyaXebnA == true){IhVyaXebnA = false;}
      if(HdAZIqnSJN == true){HdAZIqnSJN = false;}
      if(LLbSrGjWLR == true){LLbSrGjWLR = false;}
      if(NCTKllZZlE == true){NCTKllZZlE = false;}
      if(kbfWCXQdTV == true){kbfWCXQdTV = false;}
      if(GWVDcwFDGU == true){GWVDcwFDGU = false;}
      if(mHQWlFKpmW == true){mHQWlFKpmW = false;}
      if(QOfFbjfFQU == true){QOfFbjfFQU = false;}
      if(pGCoKqgPgo == true){pGCoKqgPgo = false;}
      if(fWTRQdKJjx == true){fWTRQdKJjx = false;}
      if(MZpxEqqQas == true){MZpxEqqQas = false;}
      if(QzlkdgEaLu == true){QzlkdgEaLu = false;}
      if(XtIxqttNny == true){XtIxqttNny = false;}
      if(YVVSHPPFkS == true){YVVSHPPFkS = false;}
      if(zQomYfjhni == true){zQomYfjhni = false;}
      if(YjxoYSQrGK == true){YjxoYSQrGK = false;}
      if(wdbbTtdSdN == true){wdbbTtdSdN = false;}
      if(QzpruHFVYK == true){QzpruHFVYK = false;}
      if(JMZEZoXfso == true){JMZEZoXfso = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUQMEDDINS
{ 
  void uLDwcadBoH()
  { 
      bool ggkJQNGtUj = false;
      bool PFcGVkaXto = false;
      bool SyAeTxfLLm = false;
      bool wMRpyPnjmI = false;
      bool AhiuSTWAmO = false;
      bool GUkMAifGpT = false;
      bool huigmDmmIF = false;
      bool wpjkojPELz = false;
      bool ZeYxfbaFoP = false;
      bool ihtTZFzBHO = false;
      bool firgSQkzXQ = false;
      bool TaupsCVlAL = false;
      bool chyrVOwQKi = false;
      bool kNwwTqmrdP = false;
      bool pagYwImDZX = false;
      bool jNBwlxkzKD = false;
      bool TTnoeFeyWC = false;
      bool PcHjUBBZwN = false;
      bool aspmzXMAJV = false;
      bool FngZwWmqsq = false;
      string EOSBcHagfZ;
      string GHNDadbhCV;
      string XMMuJnYukL;
      string gfgPlgVxmi;
      string OSyFIVsbxi;
      string PMPwkrCXro;
      string hfwTrZZyQt;
      string HduTHFNGmm;
      string uxxBwTQkes;
      string dyExAiVdNh;
      string wtKDakRuof;
      string eukFtkhtXX;
      string JnTXPJZxTX;
      string iisEqAmtZL;
      string CUwzOiMzDO;
      string BbGpYHalmR;
      string LUbQwuBfNs;
      string xmULUoqUJf;
      string wZtEWHcDfi;
      string ZAHIAhreCS;
      if(EOSBcHagfZ == wtKDakRuof){ggkJQNGtUj = true;}
      else if(wtKDakRuof == EOSBcHagfZ){firgSQkzXQ = true;}
      if(GHNDadbhCV == eukFtkhtXX){PFcGVkaXto = true;}
      else if(eukFtkhtXX == GHNDadbhCV){TaupsCVlAL = true;}
      if(XMMuJnYukL == JnTXPJZxTX){SyAeTxfLLm = true;}
      else if(JnTXPJZxTX == XMMuJnYukL){chyrVOwQKi = true;}
      if(gfgPlgVxmi == iisEqAmtZL){wMRpyPnjmI = true;}
      else if(iisEqAmtZL == gfgPlgVxmi){kNwwTqmrdP = true;}
      if(OSyFIVsbxi == CUwzOiMzDO){AhiuSTWAmO = true;}
      else if(CUwzOiMzDO == OSyFIVsbxi){pagYwImDZX = true;}
      if(PMPwkrCXro == BbGpYHalmR){GUkMAifGpT = true;}
      else if(BbGpYHalmR == PMPwkrCXro){jNBwlxkzKD = true;}
      if(hfwTrZZyQt == LUbQwuBfNs){huigmDmmIF = true;}
      else if(LUbQwuBfNs == hfwTrZZyQt){TTnoeFeyWC = true;}
      if(HduTHFNGmm == xmULUoqUJf){wpjkojPELz = true;}
      if(uxxBwTQkes == wZtEWHcDfi){ZeYxfbaFoP = true;}
      if(dyExAiVdNh == ZAHIAhreCS){ihtTZFzBHO = true;}
      while(xmULUoqUJf == HduTHFNGmm){PcHjUBBZwN = true;}
      while(wZtEWHcDfi == wZtEWHcDfi){aspmzXMAJV = true;}
      while(ZAHIAhreCS == ZAHIAhreCS){FngZwWmqsq = true;}
      if(ggkJQNGtUj == true){ggkJQNGtUj = false;}
      if(PFcGVkaXto == true){PFcGVkaXto = false;}
      if(SyAeTxfLLm == true){SyAeTxfLLm = false;}
      if(wMRpyPnjmI == true){wMRpyPnjmI = false;}
      if(AhiuSTWAmO == true){AhiuSTWAmO = false;}
      if(GUkMAifGpT == true){GUkMAifGpT = false;}
      if(huigmDmmIF == true){huigmDmmIF = false;}
      if(wpjkojPELz == true){wpjkojPELz = false;}
      if(ZeYxfbaFoP == true){ZeYxfbaFoP = false;}
      if(ihtTZFzBHO == true){ihtTZFzBHO = false;}
      if(firgSQkzXQ == true){firgSQkzXQ = false;}
      if(TaupsCVlAL == true){TaupsCVlAL = false;}
      if(chyrVOwQKi == true){chyrVOwQKi = false;}
      if(kNwwTqmrdP == true){kNwwTqmrdP = false;}
      if(pagYwImDZX == true){pagYwImDZX = false;}
      if(jNBwlxkzKD == true){jNBwlxkzKD = false;}
      if(TTnoeFeyWC == true){TTnoeFeyWC = false;}
      if(PcHjUBBZwN == true){PcHjUBBZwN = false;}
      if(aspmzXMAJV == true){aspmzXMAJV = false;}
      if(FngZwWmqsq == true){FngZwWmqsq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CAEVXSVCJH
{ 
  void lnVaoUkozd()
  { 
      bool OydAcNxkYs = false;
      bool ozskqILNcf = false;
      bool YMccTwnkEK = false;
      bool hpLNJLgBKd = false;
      bool ZDuXdLkNKc = false;
      bool KfWNdBVAgf = false;
      bool YMfNLzmfae = false;
      bool bJDyFVQFzI = false;
      bool KaabACTyiH = false;
      bool pfUdENWhLd = false;
      bool YFleAAcXHH = false;
      bool jPAXVylDNJ = false;
      bool fnwTounZtr = false;
      bool yisVjEnuaz = false;
      bool YupaWZexHF = false;
      bool bTTCyjJSpF = false;
      bool LCdPJAVenR = false;
      bool KpbOjjxUwO = false;
      bool PqRnPePqWz = false;
      bool uVFVmWRZRW = false;
      string ebjGCDPoZk;
      string pYPrjPMwaJ;
      string HNVYWmFlqU;
      string ljfENLkFnQ;
      string XXaWwhRXCi;
      string LEAyuRGKjP;
      string xdxEzFrKeY;
      string dHHJlimycn;
      string VhjHJhjgIw;
      string EaVYSsZWXp;
      string pGscEEwpMM;
      string dIgusPspuR;
      string UKCiTDkhpr;
      string IPalyOoGDE;
      string ksUwRwsaeD;
      string AjbFUeEKIB;
      string SOAUDNhtwe;
      string almpgapFQX;
      string KKCmqXnURS;
      string KeyBkVszsD;
      if(ebjGCDPoZk == pGscEEwpMM){OydAcNxkYs = true;}
      else if(pGscEEwpMM == ebjGCDPoZk){YFleAAcXHH = true;}
      if(pYPrjPMwaJ == dIgusPspuR){ozskqILNcf = true;}
      else if(dIgusPspuR == pYPrjPMwaJ){jPAXVylDNJ = true;}
      if(HNVYWmFlqU == UKCiTDkhpr){YMccTwnkEK = true;}
      else if(UKCiTDkhpr == HNVYWmFlqU){fnwTounZtr = true;}
      if(ljfENLkFnQ == IPalyOoGDE){hpLNJLgBKd = true;}
      else if(IPalyOoGDE == ljfENLkFnQ){yisVjEnuaz = true;}
      if(XXaWwhRXCi == ksUwRwsaeD){ZDuXdLkNKc = true;}
      else if(ksUwRwsaeD == XXaWwhRXCi){YupaWZexHF = true;}
      if(LEAyuRGKjP == AjbFUeEKIB){KfWNdBVAgf = true;}
      else if(AjbFUeEKIB == LEAyuRGKjP){bTTCyjJSpF = true;}
      if(xdxEzFrKeY == SOAUDNhtwe){YMfNLzmfae = true;}
      else if(SOAUDNhtwe == xdxEzFrKeY){LCdPJAVenR = true;}
      if(dHHJlimycn == almpgapFQX){bJDyFVQFzI = true;}
      if(VhjHJhjgIw == KKCmqXnURS){KaabACTyiH = true;}
      if(EaVYSsZWXp == KeyBkVszsD){pfUdENWhLd = true;}
      while(almpgapFQX == dHHJlimycn){KpbOjjxUwO = true;}
      while(KKCmqXnURS == KKCmqXnURS){PqRnPePqWz = true;}
      while(KeyBkVszsD == KeyBkVszsD){uVFVmWRZRW = true;}
      if(OydAcNxkYs == true){OydAcNxkYs = false;}
      if(ozskqILNcf == true){ozskqILNcf = false;}
      if(YMccTwnkEK == true){YMccTwnkEK = false;}
      if(hpLNJLgBKd == true){hpLNJLgBKd = false;}
      if(ZDuXdLkNKc == true){ZDuXdLkNKc = false;}
      if(KfWNdBVAgf == true){KfWNdBVAgf = false;}
      if(YMfNLzmfae == true){YMfNLzmfae = false;}
      if(bJDyFVQFzI == true){bJDyFVQFzI = false;}
      if(KaabACTyiH == true){KaabACTyiH = false;}
      if(pfUdENWhLd == true){pfUdENWhLd = false;}
      if(YFleAAcXHH == true){YFleAAcXHH = false;}
      if(jPAXVylDNJ == true){jPAXVylDNJ = false;}
      if(fnwTounZtr == true){fnwTounZtr = false;}
      if(yisVjEnuaz == true){yisVjEnuaz = false;}
      if(YupaWZexHF == true){YupaWZexHF = false;}
      if(bTTCyjJSpF == true){bTTCyjJSpF = false;}
      if(LCdPJAVenR == true){LCdPJAVenR = false;}
      if(KpbOjjxUwO == true){KpbOjjxUwO = false;}
      if(PqRnPePqWz == true){PqRnPePqWz = false;}
      if(uVFVmWRZRW == true){uVFVmWRZRW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUPLRRHLOP
{ 
  void oRxzOQnBMw()
  { 
      bool QbBMfJjukT = false;
      bool yqFeTzhUlE = false;
      bool ZwtHnHdzBH = false;
      bool AFsyumwHbh = false;
      bool NxowifchNo = false;
      bool GCkFDTgtXY = false;
      bool ejtdSrxHig = false;
      bool DarDqcGxXI = false;
      bool ewkMAyTnua = false;
      bool FBiCDcDKcq = false;
      bool hUzglfJgNZ = false;
      bool NjWPthzgdU = false;
      bool YJLHaBqoAO = false;
      bool ZuTgZJxEZU = false;
      bool nlZUNVeTIU = false;
      bool cVgIRYJqFk = false;
      bool nUgyARPook = false;
      bool kuHJfliqsF = false;
      bool VXgelEOLOA = false;
      bool zGzofTFaUw = false;
      string GsOngQstlC;
      string CmNHDGdyGW;
      string sLeVacqEtk;
      string aWiVoizBFA;
      string iPQywLBWLr;
      string NnOJstNsND;
      string YnAAafEqSU;
      string HcsGmcugYP;
      string aTsBXmIYbt;
      string UGnBauPPWP;
      string GJEpjktIWP;
      string ygTxcEtycn;
      string XePXzBnrer;
      string NfJIIQPDQl;
      string rACLwnlpXV;
      string AQmhratgpi;
      string xCcdBSWKoL;
      string oqgqwXcDaL;
      string OxTIqxsaQg;
      string WhMhooWXKc;
      if(GsOngQstlC == GJEpjktIWP){QbBMfJjukT = true;}
      else if(GJEpjktIWP == GsOngQstlC){hUzglfJgNZ = true;}
      if(CmNHDGdyGW == ygTxcEtycn){yqFeTzhUlE = true;}
      else if(ygTxcEtycn == CmNHDGdyGW){NjWPthzgdU = true;}
      if(sLeVacqEtk == XePXzBnrer){ZwtHnHdzBH = true;}
      else if(XePXzBnrer == sLeVacqEtk){YJLHaBqoAO = true;}
      if(aWiVoizBFA == NfJIIQPDQl){AFsyumwHbh = true;}
      else if(NfJIIQPDQl == aWiVoizBFA){ZuTgZJxEZU = true;}
      if(iPQywLBWLr == rACLwnlpXV){NxowifchNo = true;}
      else if(rACLwnlpXV == iPQywLBWLr){nlZUNVeTIU = true;}
      if(NnOJstNsND == AQmhratgpi){GCkFDTgtXY = true;}
      else if(AQmhratgpi == NnOJstNsND){cVgIRYJqFk = true;}
      if(YnAAafEqSU == xCcdBSWKoL){ejtdSrxHig = true;}
      else if(xCcdBSWKoL == YnAAafEqSU){nUgyARPook = true;}
      if(HcsGmcugYP == oqgqwXcDaL){DarDqcGxXI = true;}
      if(aTsBXmIYbt == OxTIqxsaQg){ewkMAyTnua = true;}
      if(UGnBauPPWP == WhMhooWXKc){FBiCDcDKcq = true;}
      while(oqgqwXcDaL == HcsGmcugYP){kuHJfliqsF = true;}
      while(OxTIqxsaQg == OxTIqxsaQg){VXgelEOLOA = true;}
      while(WhMhooWXKc == WhMhooWXKc){zGzofTFaUw = true;}
      if(QbBMfJjukT == true){QbBMfJjukT = false;}
      if(yqFeTzhUlE == true){yqFeTzhUlE = false;}
      if(ZwtHnHdzBH == true){ZwtHnHdzBH = false;}
      if(AFsyumwHbh == true){AFsyumwHbh = false;}
      if(NxowifchNo == true){NxowifchNo = false;}
      if(GCkFDTgtXY == true){GCkFDTgtXY = false;}
      if(ejtdSrxHig == true){ejtdSrxHig = false;}
      if(DarDqcGxXI == true){DarDqcGxXI = false;}
      if(ewkMAyTnua == true){ewkMAyTnua = false;}
      if(FBiCDcDKcq == true){FBiCDcDKcq = false;}
      if(hUzglfJgNZ == true){hUzglfJgNZ = false;}
      if(NjWPthzgdU == true){NjWPthzgdU = false;}
      if(YJLHaBqoAO == true){YJLHaBqoAO = false;}
      if(ZuTgZJxEZU == true){ZuTgZJxEZU = false;}
      if(nlZUNVeTIU == true){nlZUNVeTIU = false;}
      if(cVgIRYJqFk == true){cVgIRYJqFk = false;}
      if(nUgyARPook == true){nUgyARPook = false;}
      if(kuHJfliqsF == true){kuHJfliqsF = false;}
      if(VXgelEOLOA == true){VXgelEOLOA = false;}
      if(zGzofTFaUw == true){zGzofTFaUw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVXFAFFUWJ
{ 
  void MZTuSaGgPt()
  { 
      bool ztXQroajBt = false;
      bool hxnymhwfwf = false;
      bool fGDXSbqlqO = false;
      bool CEwNULxdbA = false;
      bool KUgUZygoRk = false;
      bool JCIkhrpAxP = false;
      bool xnrmrcBada = false;
      bool jRDuVLYixT = false;
      bool uBTGEzwKfc = false;
      bool VwgMCVbtcw = false;
      bool xGLqAryMOW = false;
      bool SHCdUwTlhr = false;
      bool gpuBFmjqsA = false;
      bool ieFAWoocGL = false;
      bool BjuIJNtDqG = false;
      bool BpLjPGLKlM = false;
      bool IGTOmnBCHf = false;
      bool GqfWqxtlqq = false;
      bool sgzlzsSUkP = false;
      bool cdqsDtQgVV = false;
      string mxaoWCZaJu;
      string MopHKkIbby;
      string ZcMOUelDXf;
      string NuCntTnCwp;
      string fMEUSdMGSK;
      string hyyOiJkLUq;
      string PWDdgRmCNq;
      string xGfkSNYqwp;
      string SfjMxPwmEk;
      string hcgEZIJZmA;
      string qJsbNbRMwV;
      string jsOdYjmpfR;
      string UAxcITYaLK;
      string DzEuyIlHyV;
      string xjpiAnNDfp;
      string UStVfqLQSs;
      string DqBlRkoTeP;
      string xfqJUkJNbT;
      string GUuUokEhPH;
      string wUnFSGiERO;
      if(mxaoWCZaJu == qJsbNbRMwV){ztXQroajBt = true;}
      else if(qJsbNbRMwV == mxaoWCZaJu){xGLqAryMOW = true;}
      if(MopHKkIbby == jsOdYjmpfR){hxnymhwfwf = true;}
      else if(jsOdYjmpfR == MopHKkIbby){SHCdUwTlhr = true;}
      if(ZcMOUelDXf == UAxcITYaLK){fGDXSbqlqO = true;}
      else if(UAxcITYaLK == ZcMOUelDXf){gpuBFmjqsA = true;}
      if(NuCntTnCwp == DzEuyIlHyV){CEwNULxdbA = true;}
      else if(DzEuyIlHyV == NuCntTnCwp){ieFAWoocGL = true;}
      if(fMEUSdMGSK == xjpiAnNDfp){KUgUZygoRk = true;}
      else if(xjpiAnNDfp == fMEUSdMGSK){BjuIJNtDqG = true;}
      if(hyyOiJkLUq == UStVfqLQSs){JCIkhrpAxP = true;}
      else if(UStVfqLQSs == hyyOiJkLUq){BpLjPGLKlM = true;}
      if(PWDdgRmCNq == DqBlRkoTeP){xnrmrcBada = true;}
      else if(DqBlRkoTeP == PWDdgRmCNq){IGTOmnBCHf = true;}
      if(xGfkSNYqwp == xfqJUkJNbT){jRDuVLYixT = true;}
      if(SfjMxPwmEk == GUuUokEhPH){uBTGEzwKfc = true;}
      if(hcgEZIJZmA == wUnFSGiERO){VwgMCVbtcw = true;}
      while(xfqJUkJNbT == xGfkSNYqwp){GqfWqxtlqq = true;}
      while(GUuUokEhPH == GUuUokEhPH){sgzlzsSUkP = true;}
      while(wUnFSGiERO == wUnFSGiERO){cdqsDtQgVV = true;}
      if(ztXQroajBt == true){ztXQroajBt = false;}
      if(hxnymhwfwf == true){hxnymhwfwf = false;}
      if(fGDXSbqlqO == true){fGDXSbqlqO = false;}
      if(CEwNULxdbA == true){CEwNULxdbA = false;}
      if(KUgUZygoRk == true){KUgUZygoRk = false;}
      if(JCIkhrpAxP == true){JCIkhrpAxP = false;}
      if(xnrmrcBada == true){xnrmrcBada = false;}
      if(jRDuVLYixT == true){jRDuVLYixT = false;}
      if(uBTGEzwKfc == true){uBTGEzwKfc = false;}
      if(VwgMCVbtcw == true){VwgMCVbtcw = false;}
      if(xGLqAryMOW == true){xGLqAryMOW = false;}
      if(SHCdUwTlhr == true){SHCdUwTlhr = false;}
      if(gpuBFmjqsA == true){gpuBFmjqsA = false;}
      if(ieFAWoocGL == true){ieFAWoocGL = false;}
      if(BjuIJNtDqG == true){BjuIJNtDqG = false;}
      if(BpLjPGLKlM == true){BpLjPGLKlM = false;}
      if(IGTOmnBCHf == true){IGTOmnBCHf = false;}
      if(GqfWqxtlqq == true){GqfWqxtlqq = false;}
      if(sgzlzsSUkP == true){sgzlzsSUkP = false;}
      if(cdqsDtQgVV == true){cdqsDtQgVV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CAYLSVSJSS
{ 
  void EOabAxpSrW()
  { 
      bool nMlGYizySc = false;
      bool mBbUcGjxSM = false;
      bool QrUyVeYgOG = false;
      bool nIQYCUrmIE = false;
      bool sFuWNUXHMg = false;
      bool OGTTuurmkt = false;
      bool JSiMoekDSI = false;
      bool OwoOSLwxkA = false;
      bool GQThqhnxdH = false;
      bool cECNtaVihi = false;
      bool jUoESSRFAi = false;
      bool ytCknrzAUG = false;
      bool pnZLfJsaTr = false;
      bool pNPCPkbOPY = false;
      bool QiwtIiBRZB = false;
      bool aUNarwtdYI = false;
      bool YpkIrjdAUC = false;
      bool QjjwpHqeCw = false;
      bool HaARQUzoJT = false;
      bool qypHzZxnBX = false;
      string ISulpmjnJM;
      string ZVejCSzlXF;
      string HDfmuZzImL;
      string eAGoLbfNem;
      string DuYmUmWEWM;
      string mdBggElIqQ;
      string nbAyhYOpYa;
      string llGjBLerRH;
      string CtkaXAyZHG;
      string oXVNybuaFw;
      string XgfwZAXQfV;
      string ZtpjOtpYZh;
      string ZohRkOQslY;
      string PElVjVOnBX;
      string chskguglzE;
      string kWAXViyNLK;
      string jdeGFUHUzr;
      string eCWCEruwkp;
      string gdtgmsDOAB;
      string WAcpmyDmfM;
      if(ISulpmjnJM == XgfwZAXQfV){nMlGYizySc = true;}
      else if(XgfwZAXQfV == ISulpmjnJM){jUoESSRFAi = true;}
      if(ZVejCSzlXF == ZtpjOtpYZh){mBbUcGjxSM = true;}
      else if(ZtpjOtpYZh == ZVejCSzlXF){ytCknrzAUG = true;}
      if(HDfmuZzImL == ZohRkOQslY){QrUyVeYgOG = true;}
      else if(ZohRkOQslY == HDfmuZzImL){pnZLfJsaTr = true;}
      if(eAGoLbfNem == PElVjVOnBX){nIQYCUrmIE = true;}
      else if(PElVjVOnBX == eAGoLbfNem){pNPCPkbOPY = true;}
      if(DuYmUmWEWM == chskguglzE){sFuWNUXHMg = true;}
      else if(chskguglzE == DuYmUmWEWM){QiwtIiBRZB = true;}
      if(mdBggElIqQ == kWAXViyNLK){OGTTuurmkt = true;}
      else if(kWAXViyNLK == mdBggElIqQ){aUNarwtdYI = true;}
      if(nbAyhYOpYa == jdeGFUHUzr){JSiMoekDSI = true;}
      else if(jdeGFUHUzr == nbAyhYOpYa){YpkIrjdAUC = true;}
      if(llGjBLerRH == eCWCEruwkp){OwoOSLwxkA = true;}
      if(CtkaXAyZHG == gdtgmsDOAB){GQThqhnxdH = true;}
      if(oXVNybuaFw == WAcpmyDmfM){cECNtaVihi = true;}
      while(eCWCEruwkp == llGjBLerRH){QjjwpHqeCw = true;}
      while(gdtgmsDOAB == gdtgmsDOAB){HaARQUzoJT = true;}
      while(WAcpmyDmfM == WAcpmyDmfM){qypHzZxnBX = true;}
      if(nMlGYizySc == true){nMlGYizySc = false;}
      if(mBbUcGjxSM == true){mBbUcGjxSM = false;}
      if(QrUyVeYgOG == true){QrUyVeYgOG = false;}
      if(nIQYCUrmIE == true){nIQYCUrmIE = false;}
      if(sFuWNUXHMg == true){sFuWNUXHMg = false;}
      if(OGTTuurmkt == true){OGTTuurmkt = false;}
      if(JSiMoekDSI == true){JSiMoekDSI = false;}
      if(OwoOSLwxkA == true){OwoOSLwxkA = false;}
      if(GQThqhnxdH == true){GQThqhnxdH = false;}
      if(cECNtaVihi == true){cECNtaVihi = false;}
      if(jUoESSRFAi == true){jUoESSRFAi = false;}
      if(ytCknrzAUG == true){ytCknrzAUG = false;}
      if(pnZLfJsaTr == true){pnZLfJsaTr = false;}
      if(pNPCPkbOPY == true){pNPCPkbOPY = false;}
      if(QiwtIiBRZB == true){QiwtIiBRZB = false;}
      if(aUNarwtdYI == true){aUNarwtdYI = false;}
      if(YpkIrjdAUC == true){YpkIrjdAUC = false;}
      if(QjjwpHqeCw == true){QjjwpHqeCw = false;}
      if(HaARQUzoJT == true){HaARQUzoJT = false;}
      if(qypHzZxnBX == true){qypHzZxnBX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQMZNBKASX
{ 
  void fmTuYpAcVp()
  { 
      bool UrFeAxQkOC = false;
      bool gPeGuSBJLt = false;
      bool xhqBgLqekN = false;
      bool JeimSyZmVg = false;
      bool pmQiwlHNqr = false;
      bool QIQQRmBEyo = false;
      bool FkAAsCgrmx = false;
      bool sOneDKQHEu = false;
      bool DdmswAORVf = false;
      bool wVofaEmPpt = false;
      bool EOZsyCUkMG = false;
      bool VszDkbxGEr = false;
      bool nOVHAXYHDz = false;
      bool XBRKpnDttt = false;
      bool fcEPJCVltz = false;
      bool GfLxGpsRra = false;
      bool cMgNhUboMw = false;
      bool XDLJLKJGxx = false;
      bool BmMErqoTEz = false;
      bool ulBSQTuqgo = false;
      string mlAndVCVTT;
      string BQSjzHCQLN;
      string HQFnNFMtEl;
      string RguIiEcGeZ;
      string qrWPVhbVNd;
      string LikAFWfMaX;
      string JHRhBTUJAu;
      string dwlkWPtpRe;
      string dpgZZiwuCM;
      string YQfHQiZoOB;
      string NRVRAPxzcp;
      string botutSarHS;
      string XYHmWNPdTm;
      string oFbQRLUOZK;
      string kwRMkiWjMy;
      string IhhudnKhtm;
      string zSepBVNddh;
      string yLRwgaGtCn;
      string qfRVdGXflc;
      string BmTmLSRbLO;
      if(mlAndVCVTT == NRVRAPxzcp){UrFeAxQkOC = true;}
      else if(NRVRAPxzcp == mlAndVCVTT){EOZsyCUkMG = true;}
      if(BQSjzHCQLN == botutSarHS){gPeGuSBJLt = true;}
      else if(botutSarHS == BQSjzHCQLN){VszDkbxGEr = true;}
      if(HQFnNFMtEl == XYHmWNPdTm){xhqBgLqekN = true;}
      else if(XYHmWNPdTm == HQFnNFMtEl){nOVHAXYHDz = true;}
      if(RguIiEcGeZ == oFbQRLUOZK){JeimSyZmVg = true;}
      else if(oFbQRLUOZK == RguIiEcGeZ){XBRKpnDttt = true;}
      if(qrWPVhbVNd == kwRMkiWjMy){pmQiwlHNqr = true;}
      else if(kwRMkiWjMy == qrWPVhbVNd){fcEPJCVltz = true;}
      if(LikAFWfMaX == IhhudnKhtm){QIQQRmBEyo = true;}
      else if(IhhudnKhtm == LikAFWfMaX){GfLxGpsRra = true;}
      if(JHRhBTUJAu == zSepBVNddh){FkAAsCgrmx = true;}
      else if(zSepBVNddh == JHRhBTUJAu){cMgNhUboMw = true;}
      if(dwlkWPtpRe == yLRwgaGtCn){sOneDKQHEu = true;}
      if(dpgZZiwuCM == qfRVdGXflc){DdmswAORVf = true;}
      if(YQfHQiZoOB == BmTmLSRbLO){wVofaEmPpt = true;}
      while(yLRwgaGtCn == dwlkWPtpRe){XDLJLKJGxx = true;}
      while(qfRVdGXflc == qfRVdGXflc){BmMErqoTEz = true;}
      while(BmTmLSRbLO == BmTmLSRbLO){ulBSQTuqgo = true;}
      if(UrFeAxQkOC == true){UrFeAxQkOC = false;}
      if(gPeGuSBJLt == true){gPeGuSBJLt = false;}
      if(xhqBgLqekN == true){xhqBgLqekN = false;}
      if(JeimSyZmVg == true){JeimSyZmVg = false;}
      if(pmQiwlHNqr == true){pmQiwlHNqr = false;}
      if(QIQQRmBEyo == true){QIQQRmBEyo = false;}
      if(FkAAsCgrmx == true){FkAAsCgrmx = false;}
      if(sOneDKQHEu == true){sOneDKQHEu = false;}
      if(DdmswAORVf == true){DdmswAORVf = false;}
      if(wVofaEmPpt == true){wVofaEmPpt = false;}
      if(EOZsyCUkMG == true){EOZsyCUkMG = false;}
      if(VszDkbxGEr == true){VszDkbxGEr = false;}
      if(nOVHAXYHDz == true){nOVHAXYHDz = false;}
      if(XBRKpnDttt == true){XBRKpnDttt = false;}
      if(fcEPJCVltz == true){fcEPJCVltz = false;}
      if(GfLxGpsRra == true){GfLxGpsRra = false;}
      if(cMgNhUboMw == true){cMgNhUboMw = false;}
      if(XDLJLKJGxx == true){XDLJLKJGxx = false;}
      if(BmMErqoTEz == true){BmMErqoTEz = false;}
      if(ulBSQTuqgo == true){ulBSQTuqgo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCQEEFSOQP
{ 
  void tiKTDtCRsD()
  { 
      bool VbZHmtqYDT = false;
      bool syVQwEcFMg = false;
      bool EVuMYPqTWw = false;
      bool WtPAbojBzu = false;
      bool RCYXUTxxaM = false;
      bool xsyiAzgMhW = false;
      bool DWCHwyhVnG = false;
      bool TbFRPCwWrF = false;
      bool SssKydugzb = false;
      bool HXSbrtARbV = false;
      bool kaJTrVmgTy = false;
      bool CKUcEJdqIS = false;
      bool DBWLywIdYU = false;
      bool BetVTqjYSc = false;
      bool pOMAYxDpWh = false;
      bool PJIJSjExVw = false;
      bool MJIywXPyIN = false;
      bool ZFXebnoVmB = false;
      bool sSGpFrVkCj = false;
      bool llDWQgGNEB = false;
      string RpqIWYdwCt;
      string yFyBlCQuty;
      string QZVnjOhkpe;
      string BuaVAslPxo;
      string ZPDFEAwUZK;
      string arFRgqTDYI;
      string qrGXsCecAr;
      string PBxFXAVQii;
      string RNKeEIpInI;
      string YipoyhJfLB;
      string UTThtYuzsg;
      string VDTopchaSk;
      string MVnrTgKIHp;
      string qoEgNytcje;
      string NpPGlUOAzU;
      string zhNaozfaON;
      string OlrDpgzmaq;
      string hFpnWVGgFy;
      string RJIlpIbcrO;
      string SSNWQayLQF;
      if(RpqIWYdwCt == UTThtYuzsg){VbZHmtqYDT = true;}
      else if(UTThtYuzsg == RpqIWYdwCt){kaJTrVmgTy = true;}
      if(yFyBlCQuty == VDTopchaSk){syVQwEcFMg = true;}
      else if(VDTopchaSk == yFyBlCQuty){CKUcEJdqIS = true;}
      if(QZVnjOhkpe == MVnrTgKIHp){EVuMYPqTWw = true;}
      else if(MVnrTgKIHp == QZVnjOhkpe){DBWLywIdYU = true;}
      if(BuaVAslPxo == qoEgNytcje){WtPAbojBzu = true;}
      else if(qoEgNytcje == BuaVAslPxo){BetVTqjYSc = true;}
      if(ZPDFEAwUZK == NpPGlUOAzU){RCYXUTxxaM = true;}
      else if(NpPGlUOAzU == ZPDFEAwUZK){pOMAYxDpWh = true;}
      if(arFRgqTDYI == zhNaozfaON){xsyiAzgMhW = true;}
      else if(zhNaozfaON == arFRgqTDYI){PJIJSjExVw = true;}
      if(qrGXsCecAr == OlrDpgzmaq){DWCHwyhVnG = true;}
      else if(OlrDpgzmaq == qrGXsCecAr){MJIywXPyIN = true;}
      if(PBxFXAVQii == hFpnWVGgFy){TbFRPCwWrF = true;}
      if(RNKeEIpInI == RJIlpIbcrO){SssKydugzb = true;}
      if(YipoyhJfLB == SSNWQayLQF){HXSbrtARbV = true;}
      while(hFpnWVGgFy == PBxFXAVQii){ZFXebnoVmB = true;}
      while(RJIlpIbcrO == RJIlpIbcrO){sSGpFrVkCj = true;}
      while(SSNWQayLQF == SSNWQayLQF){llDWQgGNEB = true;}
      if(VbZHmtqYDT == true){VbZHmtqYDT = false;}
      if(syVQwEcFMg == true){syVQwEcFMg = false;}
      if(EVuMYPqTWw == true){EVuMYPqTWw = false;}
      if(WtPAbojBzu == true){WtPAbojBzu = false;}
      if(RCYXUTxxaM == true){RCYXUTxxaM = false;}
      if(xsyiAzgMhW == true){xsyiAzgMhW = false;}
      if(DWCHwyhVnG == true){DWCHwyhVnG = false;}
      if(TbFRPCwWrF == true){TbFRPCwWrF = false;}
      if(SssKydugzb == true){SssKydugzb = false;}
      if(HXSbrtARbV == true){HXSbrtARbV = false;}
      if(kaJTrVmgTy == true){kaJTrVmgTy = false;}
      if(CKUcEJdqIS == true){CKUcEJdqIS = false;}
      if(DBWLywIdYU == true){DBWLywIdYU = false;}
      if(BetVTqjYSc == true){BetVTqjYSc = false;}
      if(pOMAYxDpWh == true){pOMAYxDpWh = false;}
      if(PJIJSjExVw == true){PJIJSjExVw = false;}
      if(MJIywXPyIN == true){MJIywXPyIN = false;}
      if(ZFXebnoVmB == true){ZFXebnoVmB = false;}
      if(sSGpFrVkCj == true){sSGpFrVkCj = false;}
      if(llDWQgGNEB == true){llDWQgGNEB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCETUXVZDL
{ 
  void mihtBBIYfH()
  { 
      bool UNkbDbKxtO = false;
      bool eIoMyHiilP = false;
      bool GdWXABBpDg = false;
      bool xmOCtdAnuw = false;
      bool lYmtSzxaFR = false;
      bool WqeAYqpMaC = false;
      bool aUsNRrtlSU = false;
      bool HtmochpcFA = false;
      bool DajkJFHOdD = false;
      bool mmNrVReZba = false;
      bool FLIkJcEoWp = false;
      bool ANGZyzjIDL = false;
      bool jeHOhUgtTL = false;
      bool CQAeurRzbg = false;
      bool BRrmCYgmtV = false;
      bool gWVQpZDsDo = false;
      bool uJVKmjNaeG = false;
      bool hkfWJSmTLI = false;
      bool mtAxeftioU = false;
      bool nYwlkrugAS = false;
      string cqocukNGjD;
      string ABJyiSIjtZ;
      string wlWxbtNTzl;
      string BmoGYdMIrN;
      string PATdgdAnef;
      string isFLMqUrAA;
      string XsHyBNLCYF;
      string FzrgKuRrPy;
      string tYoTCHgdth;
      string IUIqpVrVbT;
      string RxOYZjBYAQ;
      string YbbCGyEmut;
      string fhIqwjqBqo;
      string CwPwgxKPsS;
      string GIcdIgsGkq;
      string QFZhminXbo;
      string szhLNcLfVJ;
      string notcnXEeiP;
      string qkQzYxVhIx;
      string IlmDZGZRPf;
      if(cqocukNGjD == RxOYZjBYAQ){UNkbDbKxtO = true;}
      else if(RxOYZjBYAQ == cqocukNGjD){FLIkJcEoWp = true;}
      if(ABJyiSIjtZ == YbbCGyEmut){eIoMyHiilP = true;}
      else if(YbbCGyEmut == ABJyiSIjtZ){ANGZyzjIDL = true;}
      if(wlWxbtNTzl == fhIqwjqBqo){GdWXABBpDg = true;}
      else if(fhIqwjqBqo == wlWxbtNTzl){jeHOhUgtTL = true;}
      if(BmoGYdMIrN == CwPwgxKPsS){xmOCtdAnuw = true;}
      else if(CwPwgxKPsS == BmoGYdMIrN){CQAeurRzbg = true;}
      if(PATdgdAnef == GIcdIgsGkq){lYmtSzxaFR = true;}
      else if(GIcdIgsGkq == PATdgdAnef){BRrmCYgmtV = true;}
      if(isFLMqUrAA == QFZhminXbo){WqeAYqpMaC = true;}
      else if(QFZhminXbo == isFLMqUrAA){gWVQpZDsDo = true;}
      if(XsHyBNLCYF == szhLNcLfVJ){aUsNRrtlSU = true;}
      else if(szhLNcLfVJ == XsHyBNLCYF){uJVKmjNaeG = true;}
      if(FzrgKuRrPy == notcnXEeiP){HtmochpcFA = true;}
      if(tYoTCHgdth == qkQzYxVhIx){DajkJFHOdD = true;}
      if(IUIqpVrVbT == IlmDZGZRPf){mmNrVReZba = true;}
      while(notcnXEeiP == FzrgKuRrPy){hkfWJSmTLI = true;}
      while(qkQzYxVhIx == qkQzYxVhIx){mtAxeftioU = true;}
      while(IlmDZGZRPf == IlmDZGZRPf){nYwlkrugAS = true;}
      if(UNkbDbKxtO == true){UNkbDbKxtO = false;}
      if(eIoMyHiilP == true){eIoMyHiilP = false;}
      if(GdWXABBpDg == true){GdWXABBpDg = false;}
      if(xmOCtdAnuw == true){xmOCtdAnuw = false;}
      if(lYmtSzxaFR == true){lYmtSzxaFR = false;}
      if(WqeAYqpMaC == true){WqeAYqpMaC = false;}
      if(aUsNRrtlSU == true){aUsNRrtlSU = false;}
      if(HtmochpcFA == true){HtmochpcFA = false;}
      if(DajkJFHOdD == true){DajkJFHOdD = false;}
      if(mmNrVReZba == true){mmNrVReZba = false;}
      if(FLIkJcEoWp == true){FLIkJcEoWp = false;}
      if(ANGZyzjIDL == true){ANGZyzjIDL = false;}
      if(jeHOhUgtTL == true){jeHOhUgtTL = false;}
      if(CQAeurRzbg == true){CQAeurRzbg = false;}
      if(BRrmCYgmtV == true){BRrmCYgmtV = false;}
      if(gWVQpZDsDo == true){gWVQpZDsDo = false;}
      if(uJVKmjNaeG == true){uJVKmjNaeG = false;}
      if(hkfWJSmTLI == true){hkfWJSmTLI = false;}
      if(mtAxeftioU == true){mtAxeftioU = false;}
      if(nYwlkrugAS == true){nYwlkrugAS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFREZCQJZL
{ 
  void DmzspkOydZ()
  { 
      bool ZYXMMIudOX = false;
      bool SZXPzuPPxf = false;
      bool QbImgWTScI = false;
      bool dDBwstwSPD = false;
      bool PZdCCpUeiF = false;
      bool DbjIIyPkfp = false;
      bool ncAGtPYbWF = false;
      bool zwAtQqxFkp = false;
      bool CoiWECSrnu = false;
      bool dKmZPmYXIm = false;
      bool QrIdGGbprQ = false;
      bool BKzomzsdBq = false;
      bool wfnabnJZdd = false;
      bool SYxyZJfFQy = false;
      bool ZcAWtSLymQ = false;
      bool stVQqjEgBS = false;
      bool xBLOybNBOc = false;
      bool SnMDRTfRgI = false;
      bool bLmNjXDfHo = false;
      bool FzDyBYQkXS = false;
      string TNizNuNWmH;
      string PyyxkRYSWq;
      string MgpLHNtpXO;
      string QYhsKWgHnh;
      string oBXYqzrwMc;
      string hPnuLmWWqA;
      string AWzYqqQEmO;
      string jRdnBLIRTI;
      string UxctfAklgW;
      string zKPngRCzgA;
      string inJyrQkztA;
      string dECieDtErq;
      string GdWPOZBoGj;
      string IJjTZgmeCP;
      string OkrgsuHgJd;
      string XxGpsEQtiS;
      string OusJqTUiIx;
      string QPCcbVlpVT;
      string STfcLLDsZU;
      string QsuiATqhoZ;
      if(TNizNuNWmH == inJyrQkztA){ZYXMMIudOX = true;}
      else if(inJyrQkztA == TNizNuNWmH){QrIdGGbprQ = true;}
      if(PyyxkRYSWq == dECieDtErq){SZXPzuPPxf = true;}
      else if(dECieDtErq == PyyxkRYSWq){BKzomzsdBq = true;}
      if(MgpLHNtpXO == GdWPOZBoGj){QbImgWTScI = true;}
      else if(GdWPOZBoGj == MgpLHNtpXO){wfnabnJZdd = true;}
      if(QYhsKWgHnh == IJjTZgmeCP){dDBwstwSPD = true;}
      else if(IJjTZgmeCP == QYhsKWgHnh){SYxyZJfFQy = true;}
      if(oBXYqzrwMc == OkrgsuHgJd){PZdCCpUeiF = true;}
      else if(OkrgsuHgJd == oBXYqzrwMc){ZcAWtSLymQ = true;}
      if(hPnuLmWWqA == XxGpsEQtiS){DbjIIyPkfp = true;}
      else if(XxGpsEQtiS == hPnuLmWWqA){stVQqjEgBS = true;}
      if(AWzYqqQEmO == OusJqTUiIx){ncAGtPYbWF = true;}
      else if(OusJqTUiIx == AWzYqqQEmO){xBLOybNBOc = true;}
      if(jRdnBLIRTI == QPCcbVlpVT){zwAtQqxFkp = true;}
      if(UxctfAklgW == STfcLLDsZU){CoiWECSrnu = true;}
      if(zKPngRCzgA == QsuiATqhoZ){dKmZPmYXIm = true;}
      while(QPCcbVlpVT == jRdnBLIRTI){SnMDRTfRgI = true;}
      while(STfcLLDsZU == STfcLLDsZU){bLmNjXDfHo = true;}
      while(QsuiATqhoZ == QsuiATqhoZ){FzDyBYQkXS = true;}
      if(ZYXMMIudOX == true){ZYXMMIudOX = false;}
      if(SZXPzuPPxf == true){SZXPzuPPxf = false;}
      if(QbImgWTScI == true){QbImgWTScI = false;}
      if(dDBwstwSPD == true){dDBwstwSPD = false;}
      if(PZdCCpUeiF == true){PZdCCpUeiF = false;}
      if(DbjIIyPkfp == true){DbjIIyPkfp = false;}
      if(ncAGtPYbWF == true){ncAGtPYbWF = false;}
      if(zwAtQqxFkp == true){zwAtQqxFkp = false;}
      if(CoiWECSrnu == true){CoiWECSrnu = false;}
      if(dKmZPmYXIm == true){dKmZPmYXIm = false;}
      if(QrIdGGbprQ == true){QrIdGGbprQ = false;}
      if(BKzomzsdBq == true){BKzomzsdBq = false;}
      if(wfnabnJZdd == true){wfnabnJZdd = false;}
      if(SYxyZJfFQy == true){SYxyZJfFQy = false;}
      if(ZcAWtSLymQ == true){ZcAWtSLymQ = false;}
      if(stVQqjEgBS == true){stVQqjEgBS = false;}
      if(xBLOybNBOc == true){xBLOybNBOc = false;}
      if(SnMDRTfRgI == true){SnMDRTfRgI = false;}
      if(bLmNjXDfHo == true){bLmNjXDfHo = false;}
      if(FzDyBYQkXS == true){FzDyBYQkXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSBZIZXAGT
{ 
  void fpWobYTPxA()
  { 
      bool hrMmSlmwZY = false;
      bool UxzmzPqjQc = false;
      bool fAwYfhEqWC = false;
      bool XNduWpXhsx = false;
      bool tCRXafkDKl = false;
      bool dDFPmhwmGj = false;
      bool gwYXBHTDPJ = false;
      bool rJpShchXyA = false;
      bool xBfkYTHNIn = false;
      bool skaIPydtVS = false;
      bool LgmAsUMlhJ = false;
      bool AYoGlfPmyh = false;
      bool AFubQGhgDj = false;
      bool znBenPNeqE = false;
      bool HUfznUwUWj = false;
      bool ipunSGlKjm = false;
      bool leiyJMWKRW = false;
      bool RjwtafZwnu = false;
      bool KMKSBJrNLh = false;
      bool dCtERbkhoa = false;
      string iDsTJlFXNl;
      string ihiVfhUhjV;
      string bQWHdFAVhO;
      string RPjVOpzuKl;
      string tXxawNJeOl;
      string rDoskSfloE;
      string kjozUSyMHp;
      string iYXybESwKQ;
      string uUGuVNZpkw;
      string KNGFBKhyFc;
      string OwXXDSeqRg;
      string ziaXIPcscG;
      string sIbKfUSRwQ;
      string VUqgCyxhrC;
      string hhXExalhxk;
      string gnVyjFUMrh;
      string AMuAKdrsVJ;
      string SuBZXKjXNF;
      string ijULjhyrxw;
      string djpKCVmWsS;
      if(iDsTJlFXNl == OwXXDSeqRg){hrMmSlmwZY = true;}
      else if(OwXXDSeqRg == iDsTJlFXNl){LgmAsUMlhJ = true;}
      if(ihiVfhUhjV == ziaXIPcscG){UxzmzPqjQc = true;}
      else if(ziaXIPcscG == ihiVfhUhjV){AYoGlfPmyh = true;}
      if(bQWHdFAVhO == sIbKfUSRwQ){fAwYfhEqWC = true;}
      else if(sIbKfUSRwQ == bQWHdFAVhO){AFubQGhgDj = true;}
      if(RPjVOpzuKl == VUqgCyxhrC){XNduWpXhsx = true;}
      else if(VUqgCyxhrC == RPjVOpzuKl){znBenPNeqE = true;}
      if(tXxawNJeOl == hhXExalhxk){tCRXafkDKl = true;}
      else if(hhXExalhxk == tXxawNJeOl){HUfznUwUWj = true;}
      if(rDoskSfloE == gnVyjFUMrh){dDFPmhwmGj = true;}
      else if(gnVyjFUMrh == rDoskSfloE){ipunSGlKjm = true;}
      if(kjozUSyMHp == AMuAKdrsVJ){gwYXBHTDPJ = true;}
      else if(AMuAKdrsVJ == kjozUSyMHp){leiyJMWKRW = true;}
      if(iYXybESwKQ == SuBZXKjXNF){rJpShchXyA = true;}
      if(uUGuVNZpkw == ijULjhyrxw){xBfkYTHNIn = true;}
      if(KNGFBKhyFc == djpKCVmWsS){skaIPydtVS = true;}
      while(SuBZXKjXNF == iYXybESwKQ){RjwtafZwnu = true;}
      while(ijULjhyrxw == ijULjhyrxw){KMKSBJrNLh = true;}
      while(djpKCVmWsS == djpKCVmWsS){dCtERbkhoa = true;}
      if(hrMmSlmwZY == true){hrMmSlmwZY = false;}
      if(UxzmzPqjQc == true){UxzmzPqjQc = false;}
      if(fAwYfhEqWC == true){fAwYfhEqWC = false;}
      if(XNduWpXhsx == true){XNduWpXhsx = false;}
      if(tCRXafkDKl == true){tCRXafkDKl = false;}
      if(dDFPmhwmGj == true){dDFPmhwmGj = false;}
      if(gwYXBHTDPJ == true){gwYXBHTDPJ = false;}
      if(rJpShchXyA == true){rJpShchXyA = false;}
      if(xBfkYTHNIn == true){xBfkYTHNIn = false;}
      if(skaIPydtVS == true){skaIPydtVS = false;}
      if(LgmAsUMlhJ == true){LgmAsUMlhJ = false;}
      if(AYoGlfPmyh == true){AYoGlfPmyh = false;}
      if(AFubQGhgDj == true){AFubQGhgDj = false;}
      if(znBenPNeqE == true){znBenPNeqE = false;}
      if(HUfznUwUWj == true){HUfznUwUWj = false;}
      if(ipunSGlKjm == true){ipunSGlKjm = false;}
      if(leiyJMWKRW == true){leiyJMWKRW = false;}
      if(RjwtafZwnu == true){RjwtafZwnu = false;}
      if(KMKSBJrNLh == true){KMKSBJrNLh = false;}
      if(dCtERbkhoa == true){dCtERbkhoa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBXZDMLHJO
{ 
  void BWDKZaMZBc()
  { 
      bool wVtCarTVBY = false;
      bool kaLiHMDFrr = false;
      bool UazLGiugNx = false;
      bool eqKwbblbOW = false;
      bool xuilcHnexq = false;
      bool HSpJWUViuq = false;
      bool wlIDstPOGf = false;
      bool ZaqUuYrMhz = false;
      bool uQjWpMBBYH = false;
      bool FDfWZKmesh = false;
      bool rZXQQfaUOy = false;
      bool cJAwwfCkNf = false;
      bool sOozaWtTtj = false;
      bool kMTAGUrSFK = false;
      bool lflaewCjZt = false;
      bool IBRMockXpt = false;
      bool kGZdMPoAob = false;
      bool mifCtMbNUe = false;
      bool TKsAbjuHKd = false;
      bool jTcLYeFIOP = false;
      string jaPBGiheOY;
      string xXKXWbcZsX;
      string ScNcFKfrnE;
      string bIqueaRLzx;
      string WtPIoGbLis;
      string LeraEGMmuu;
      string DoqKxngOru;
      string JQZuAYMFny;
      string iTJtswQQpY;
      string OeQDthCFKA;
      string ZMTnjtEwZe;
      string sGyxLifwQA;
      string XPXTfdAWAR;
      string VGtnXWAVKy;
      string rTpLeHgTrK;
      string CFoJbKnAHF;
      string thuIImLKYo;
      string iJlSIDYMoX;
      string xgdpPQRkLN;
      string hzOFEKXhCr;
      if(jaPBGiheOY == ZMTnjtEwZe){wVtCarTVBY = true;}
      else if(ZMTnjtEwZe == jaPBGiheOY){rZXQQfaUOy = true;}
      if(xXKXWbcZsX == sGyxLifwQA){kaLiHMDFrr = true;}
      else if(sGyxLifwQA == xXKXWbcZsX){cJAwwfCkNf = true;}
      if(ScNcFKfrnE == XPXTfdAWAR){UazLGiugNx = true;}
      else if(XPXTfdAWAR == ScNcFKfrnE){sOozaWtTtj = true;}
      if(bIqueaRLzx == VGtnXWAVKy){eqKwbblbOW = true;}
      else if(VGtnXWAVKy == bIqueaRLzx){kMTAGUrSFK = true;}
      if(WtPIoGbLis == rTpLeHgTrK){xuilcHnexq = true;}
      else if(rTpLeHgTrK == WtPIoGbLis){lflaewCjZt = true;}
      if(LeraEGMmuu == CFoJbKnAHF){HSpJWUViuq = true;}
      else if(CFoJbKnAHF == LeraEGMmuu){IBRMockXpt = true;}
      if(DoqKxngOru == thuIImLKYo){wlIDstPOGf = true;}
      else if(thuIImLKYo == DoqKxngOru){kGZdMPoAob = true;}
      if(JQZuAYMFny == iJlSIDYMoX){ZaqUuYrMhz = true;}
      if(iTJtswQQpY == xgdpPQRkLN){uQjWpMBBYH = true;}
      if(OeQDthCFKA == hzOFEKXhCr){FDfWZKmesh = true;}
      while(iJlSIDYMoX == JQZuAYMFny){mifCtMbNUe = true;}
      while(xgdpPQRkLN == xgdpPQRkLN){TKsAbjuHKd = true;}
      while(hzOFEKXhCr == hzOFEKXhCr){jTcLYeFIOP = true;}
      if(wVtCarTVBY == true){wVtCarTVBY = false;}
      if(kaLiHMDFrr == true){kaLiHMDFrr = false;}
      if(UazLGiugNx == true){UazLGiugNx = false;}
      if(eqKwbblbOW == true){eqKwbblbOW = false;}
      if(xuilcHnexq == true){xuilcHnexq = false;}
      if(HSpJWUViuq == true){HSpJWUViuq = false;}
      if(wlIDstPOGf == true){wlIDstPOGf = false;}
      if(ZaqUuYrMhz == true){ZaqUuYrMhz = false;}
      if(uQjWpMBBYH == true){uQjWpMBBYH = false;}
      if(FDfWZKmesh == true){FDfWZKmesh = false;}
      if(rZXQQfaUOy == true){rZXQQfaUOy = false;}
      if(cJAwwfCkNf == true){cJAwwfCkNf = false;}
      if(sOozaWtTtj == true){sOozaWtTtj = false;}
      if(kMTAGUrSFK == true){kMTAGUrSFK = false;}
      if(lflaewCjZt == true){lflaewCjZt = false;}
      if(IBRMockXpt == true){IBRMockXpt = false;}
      if(kGZdMPoAob == true){kGZdMPoAob = false;}
      if(mifCtMbNUe == true){mifCtMbNUe = false;}
      if(TKsAbjuHKd == true){TKsAbjuHKd = false;}
      if(jTcLYeFIOP == true){jTcLYeFIOP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJECNBWXGB
{ 
  void ikCxXVKiqK()
  { 
      bool kItHSXwNFD = false;
      bool qOURrAnyxE = false;
      bool ttLNBEYcwO = false;
      bool BuSJXisVPC = false;
      bool jndheZzLey = false;
      bool EMqTdpxfFN = false;
      bool ySQqCwwLsI = false;
      bool GRitTGQcib = false;
      bool FMyyJnDzfh = false;
      bool lNQBERXmfi = false;
      bool dmRWrldxzX = false;
      bool ZTxcHkUSgN = false;
      bool rxfLVrBgpC = false;
      bool icxzyRtaGW = false;
      bool JGzIISQmtS = false;
      bool wEFRpgHGAz = false;
      bool kxGwnwWxeo = false;
      bool psMKElxWDD = false;
      bool bOmXFdXeJR = false;
      bool JnaGlLzCTM = false;
      string ThXbKDgVCY;
      string aToQQiwdnZ;
      string jNbyXZWVYc;
      string EXnSiyeQTW;
      string rBNzZCapRk;
      string kCYEwGFYDk;
      string fKwYTDeVgR;
      string DeKRghzcYU;
      string zgDnrCyiWc;
      string sFMiqgFoeV;
      string WEIzgFrGXN;
      string GcAhkyGHgR;
      string EwzEYxRaaA;
      string cKxDxtYEHl;
      string JqLIVPFdyr;
      string ZxINQaFEaj;
      string nQfWjwexjp;
      string ZCAtHMjpiI;
      string qmchZfBjlW;
      string oUdWysLoXY;
      if(ThXbKDgVCY == WEIzgFrGXN){kItHSXwNFD = true;}
      else if(WEIzgFrGXN == ThXbKDgVCY){dmRWrldxzX = true;}
      if(aToQQiwdnZ == GcAhkyGHgR){qOURrAnyxE = true;}
      else if(GcAhkyGHgR == aToQQiwdnZ){ZTxcHkUSgN = true;}
      if(jNbyXZWVYc == EwzEYxRaaA){ttLNBEYcwO = true;}
      else if(EwzEYxRaaA == jNbyXZWVYc){rxfLVrBgpC = true;}
      if(EXnSiyeQTW == cKxDxtYEHl){BuSJXisVPC = true;}
      else if(cKxDxtYEHl == EXnSiyeQTW){icxzyRtaGW = true;}
      if(rBNzZCapRk == JqLIVPFdyr){jndheZzLey = true;}
      else if(JqLIVPFdyr == rBNzZCapRk){JGzIISQmtS = true;}
      if(kCYEwGFYDk == ZxINQaFEaj){EMqTdpxfFN = true;}
      else if(ZxINQaFEaj == kCYEwGFYDk){wEFRpgHGAz = true;}
      if(fKwYTDeVgR == nQfWjwexjp){ySQqCwwLsI = true;}
      else if(nQfWjwexjp == fKwYTDeVgR){kxGwnwWxeo = true;}
      if(DeKRghzcYU == ZCAtHMjpiI){GRitTGQcib = true;}
      if(zgDnrCyiWc == qmchZfBjlW){FMyyJnDzfh = true;}
      if(sFMiqgFoeV == oUdWysLoXY){lNQBERXmfi = true;}
      while(ZCAtHMjpiI == DeKRghzcYU){psMKElxWDD = true;}
      while(qmchZfBjlW == qmchZfBjlW){bOmXFdXeJR = true;}
      while(oUdWysLoXY == oUdWysLoXY){JnaGlLzCTM = true;}
      if(kItHSXwNFD == true){kItHSXwNFD = false;}
      if(qOURrAnyxE == true){qOURrAnyxE = false;}
      if(ttLNBEYcwO == true){ttLNBEYcwO = false;}
      if(BuSJXisVPC == true){BuSJXisVPC = false;}
      if(jndheZzLey == true){jndheZzLey = false;}
      if(EMqTdpxfFN == true){EMqTdpxfFN = false;}
      if(ySQqCwwLsI == true){ySQqCwwLsI = false;}
      if(GRitTGQcib == true){GRitTGQcib = false;}
      if(FMyyJnDzfh == true){FMyyJnDzfh = false;}
      if(lNQBERXmfi == true){lNQBERXmfi = false;}
      if(dmRWrldxzX == true){dmRWrldxzX = false;}
      if(ZTxcHkUSgN == true){ZTxcHkUSgN = false;}
      if(rxfLVrBgpC == true){rxfLVrBgpC = false;}
      if(icxzyRtaGW == true){icxzyRtaGW = false;}
      if(JGzIISQmtS == true){JGzIISQmtS = false;}
      if(wEFRpgHGAz == true){wEFRpgHGAz = false;}
      if(kxGwnwWxeo == true){kxGwnwWxeo = false;}
      if(psMKElxWDD == true){psMKElxWDD = false;}
      if(bOmXFdXeJR == true){bOmXFdXeJR = false;}
      if(JnaGlLzCTM == true){JnaGlLzCTM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFUDDHVPXX
{ 
  void DOnxrUSnmw()
  { 
      bool qFfkEXtJeN = false;
      bool LoocPbUwRL = false;
      bool NQZGDrigYL = false;
      bool OyjgfWtLFc = false;
      bool HdoekyLNkj = false;
      bool krJiOZfYgM = false;
      bool nMjTzMFHxr = false;
      bool hJpoEjbuVF = false;
      bool fUwoZVoASF = false;
      bool qUdsntsUfX = false;
      bool rEPrCbBUed = false;
      bool xjDagTQusc = false;
      bool XForANexAJ = false;
      bool pGPxNaFDmx = false;
      bool TTVnHGQCLU = false;
      bool cyaCzmPXqn = false;
      bool wETUnpUGNF = false;
      bool NNHwIDiAjt = false;
      bool wbkfgreMxa = false;
      bool LgLyAPAAAR = false;
      string NyAxSuZCuM;
      string lTEWLDasSi;
      string AAtAXERSlT;
      string IanUYhAuqT;
      string WTWqajphbx;
      string rsPdWNEAZN;
      string cHPaEKejyc;
      string CfCzMgdCYm;
      string NjpnaOLKxL;
      string dAVcpODulP;
      string FGjzuMqPQp;
      string iBblzrQbAp;
      string zTllzBKYIy;
      string chQIhHzqsO;
      string XwtHcbYjcx;
      string xbuwQkTyAs;
      string CRHSMAkSDr;
      string sZhkRDZdJW;
      string cZwKABmTrw;
      string nBqALGoatb;
      if(NyAxSuZCuM == FGjzuMqPQp){qFfkEXtJeN = true;}
      else if(FGjzuMqPQp == NyAxSuZCuM){rEPrCbBUed = true;}
      if(lTEWLDasSi == iBblzrQbAp){LoocPbUwRL = true;}
      else if(iBblzrQbAp == lTEWLDasSi){xjDagTQusc = true;}
      if(AAtAXERSlT == zTllzBKYIy){NQZGDrigYL = true;}
      else if(zTllzBKYIy == AAtAXERSlT){XForANexAJ = true;}
      if(IanUYhAuqT == chQIhHzqsO){OyjgfWtLFc = true;}
      else if(chQIhHzqsO == IanUYhAuqT){pGPxNaFDmx = true;}
      if(WTWqajphbx == XwtHcbYjcx){HdoekyLNkj = true;}
      else if(XwtHcbYjcx == WTWqajphbx){TTVnHGQCLU = true;}
      if(rsPdWNEAZN == xbuwQkTyAs){krJiOZfYgM = true;}
      else if(xbuwQkTyAs == rsPdWNEAZN){cyaCzmPXqn = true;}
      if(cHPaEKejyc == CRHSMAkSDr){nMjTzMFHxr = true;}
      else if(CRHSMAkSDr == cHPaEKejyc){wETUnpUGNF = true;}
      if(CfCzMgdCYm == sZhkRDZdJW){hJpoEjbuVF = true;}
      if(NjpnaOLKxL == cZwKABmTrw){fUwoZVoASF = true;}
      if(dAVcpODulP == nBqALGoatb){qUdsntsUfX = true;}
      while(sZhkRDZdJW == CfCzMgdCYm){NNHwIDiAjt = true;}
      while(cZwKABmTrw == cZwKABmTrw){wbkfgreMxa = true;}
      while(nBqALGoatb == nBqALGoatb){LgLyAPAAAR = true;}
      if(qFfkEXtJeN == true){qFfkEXtJeN = false;}
      if(LoocPbUwRL == true){LoocPbUwRL = false;}
      if(NQZGDrigYL == true){NQZGDrigYL = false;}
      if(OyjgfWtLFc == true){OyjgfWtLFc = false;}
      if(HdoekyLNkj == true){HdoekyLNkj = false;}
      if(krJiOZfYgM == true){krJiOZfYgM = false;}
      if(nMjTzMFHxr == true){nMjTzMFHxr = false;}
      if(hJpoEjbuVF == true){hJpoEjbuVF = false;}
      if(fUwoZVoASF == true){fUwoZVoASF = false;}
      if(qUdsntsUfX == true){qUdsntsUfX = false;}
      if(rEPrCbBUed == true){rEPrCbBUed = false;}
      if(xjDagTQusc == true){xjDagTQusc = false;}
      if(XForANexAJ == true){XForANexAJ = false;}
      if(pGPxNaFDmx == true){pGPxNaFDmx = false;}
      if(TTVnHGQCLU == true){TTVnHGQCLU = false;}
      if(cyaCzmPXqn == true){cyaCzmPXqn = false;}
      if(wETUnpUGNF == true){wETUnpUGNF = false;}
      if(NNHwIDiAjt == true){NNHwIDiAjt = false;}
      if(wbkfgreMxa == true){wbkfgreMxa = false;}
      if(LgLyAPAAAR == true){LgLyAPAAAR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUGBEKZFOV
{ 
  void FWepEzREZa()
  { 
      bool JEXzLrQdrO = false;
      bool xMdMctjdMj = false;
      bool abhEUhzYeA = false;
      bool xGsDxcFPRZ = false;
      bool BnBMQYmlTr = false;
      bool hWDfihVSdd = false;
      bool srzrRpTaPz = false;
      bool oUMmhmaVnw = false;
      bool tMFlRaDMTP = false;
      bool HlkngJnIta = false;
      bool EMWTDNJPyw = false;
      bool GzehiflMaq = false;
      bool lGGArCiXGX = false;
      bool yRbMqhokiD = false;
      bool QnNWIHHDEA = false;
      bool WbhCnyFWaA = false;
      bool ekJZxnWSpB = false;
      bool pBcWayriqk = false;
      bool ueTFAVjYXs = false;
      bool bSJiYednZT = false;
      string GxlkioSUxR;
      string MuRwbbheDT;
      string gEUgMMMadN;
      string uErLPhSSpw;
      string BIMTZpFrAP;
      string IIBHhBbFYV;
      string crqjWHDGgs;
      string JOoGSXrBGV;
      string HUZNFlCjcN;
      string GNtUSIRbwR;
      string mzKGGsTuoJ;
      string JayCOIRdek;
      string FScSmwUUmJ;
      string GPEniHJSHL;
      string RHuTEfOqFK;
      string qmxLMTVrTK;
      string XzHeDsVKTG;
      string zyVSSxWJOH;
      string gcOcSSSsbO;
      string kQzxmSAPQK;
      if(GxlkioSUxR == mzKGGsTuoJ){JEXzLrQdrO = true;}
      else if(mzKGGsTuoJ == GxlkioSUxR){EMWTDNJPyw = true;}
      if(MuRwbbheDT == JayCOIRdek){xMdMctjdMj = true;}
      else if(JayCOIRdek == MuRwbbheDT){GzehiflMaq = true;}
      if(gEUgMMMadN == FScSmwUUmJ){abhEUhzYeA = true;}
      else if(FScSmwUUmJ == gEUgMMMadN){lGGArCiXGX = true;}
      if(uErLPhSSpw == GPEniHJSHL){xGsDxcFPRZ = true;}
      else if(GPEniHJSHL == uErLPhSSpw){yRbMqhokiD = true;}
      if(BIMTZpFrAP == RHuTEfOqFK){BnBMQYmlTr = true;}
      else if(RHuTEfOqFK == BIMTZpFrAP){QnNWIHHDEA = true;}
      if(IIBHhBbFYV == qmxLMTVrTK){hWDfihVSdd = true;}
      else if(qmxLMTVrTK == IIBHhBbFYV){WbhCnyFWaA = true;}
      if(crqjWHDGgs == XzHeDsVKTG){srzrRpTaPz = true;}
      else if(XzHeDsVKTG == crqjWHDGgs){ekJZxnWSpB = true;}
      if(JOoGSXrBGV == zyVSSxWJOH){oUMmhmaVnw = true;}
      if(HUZNFlCjcN == gcOcSSSsbO){tMFlRaDMTP = true;}
      if(GNtUSIRbwR == kQzxmSAPQK){HlkngJnIta = true;}
      while(zyVSSxWJOH == JOoGSXrBGV){pBcWayriqk = true;}
      while(gcOcSSSsbO == gcOcSSSsbO){ueTFAVjYXs = true;}
      while(kQzxmSAPQK == kQzxmSAPQK){bSJiYednZT = true;}
      if(JEXzLrQdrO == true){JEXzLrQdrO = false;}
      if(xMdMctjdMj == true){xMdMctjdMj = false;}
      if(abhEUhzYeA == true){abhEUhzYeA = false;}
      if(xGsDxcFPRZ == true){xGsDxcFPRZ = false;}
      if(BnBMQYmlTr == true){BnBMQYmlTr = false;}
      if(hWDfihVSdd == true){hWDfihVSdd = false;}
      if(srzrRpTaPz == true){srzrRpTaPz = false;}
      if(oUMmhmaVnw == true){oUMmhmaVnw = false;}
      if(tMFlRaDMTP == true){tMFlRaDMTP = false;}
      if(HlkngJnIta == true){HlkngJnIta = false;}
      if(EMWTDNJPyw == true){EMWTDNJPyw = false;}
      if(GzehiflMaq == true){GzehiflMaq = false;}
      if(lGGArCiXGX == true){lGGArCiXGX = false;}
      if(yRbMqhokiD == true){yRbMqhokiD = false;}
      if(QnNWIHHDEA == true){QnNWIHHDEA = false;}
      if(WbhCnyFWaA == true){WbhCnyFWaA = false;}
      if(ekJZxnWSpB == true){ekJZxnWSpB = false;}
      if(pBcWayriqk == true){pBcWayriqk = false;}
      if(ueTFAVjYXs == true){ueTFAVjYXs = false;}
      if(bSJiYednZT == true){bSJiYednZT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVDCNQESDT
{ 
  void xdHnWwUzIh()
  { 
      bool KBoofTwWex = false;
      bool lcKwVKLTrX = false;
      bool FGmMmmbLsE = false;
      bool OxreMMRAuH = false;
      bool xZzBEJnezA = false;
      bool DbGbWDOcBs = false;
      bool qkcaiokfiJ = false;
      bool rKXkafHkHc = false;
      bool zwLrBlpPII = false;
      bool xozCPLwYSP = false;
      bool YHupIrEVBq = false;
      bool wdUXttZkYw = false;
      bool zUXZLDLVVO = false;
      bool jhRqEqAUjI = false;
      bool gUORMTTaHU = false;
      bool lKAVQEjVeF = false;
      bool gizlGNMcTC = false;
      bool sEBPOdGFNq = false;
      bool ijNAcYhuaA = false;
      bool GeoebyUcKy = false;
      string jfUNNnoxPl;
      string YLHFZatWLT;
      string nZCKNpPHQj;
      string eoPmOqqWUt;
      string CzposqBtXW;
      string oIHheKcJAW;
      string YhgeGjuTpi;
      string jWCQRojMQV;
      string oUjsuWhhIE;
      string NgWxVURKiJ;
      string ugDomRGpPo;
      string aQsdhDxnij;
      string BNLkUCzEtx;
      string XYdGZHQuGd;
      string PqRSdxnsOS;
      string WdbzHhVRTj;
      string RBuSRBllDZ;
      string lCgFTKurHX;
      string OGpbaswezq;
      string lyaVLOwyAb;
      if(jfUNNnoxPl == ugDomRGpPo){KBoofTwWex = true;}
      else if(ugDomRGpPo == jfUNNnoxPl){YHupIrEVBq = true;}
      if(YLHFZatWLT == aQsdhDxnij){lcKwVKLTrX = true;}
      else if(aQsdhDxnij == YLHFZatWLT){wdUXttZkYw = true;}
      if(nZCKNpPHQj == BNLkUCzEtx){FGmMmmbLsE = true;}
      else if(BNLkUCzEtx == nZCKNpPHQj){zUXZLDLVVO = true;}
      if(eoPmOqqWUt == XYdGZHQuGd){OxreMMRAuH = true;}
      else if(XYdGZHQuGd == eoPmOqqWUt){jhRqEqAUjI = true;}
      if(CzposqBtXW == PqRSdxnsOS){xZzBEJnezA = true;}
      else if(PqRSdxnsOS == CzposqBtXW){gUORMTTaHU = true;}
      if(oIHheKcJAW == WdbzHhVRTj){DbGbWDOcBs = true;}
      else if(WdbzHhVRTj == oIHheKcJAW){lKAVQEjVeF = true;}
      if(YhgeGjuTpi == RBuSRBllDZ){qkcaiokfiJ = true;}
      else if(RBuSRBllDZ == YhgeGjuTpi){gizlGNMcTC = true;}
      if(jWCQRojMQV == lCgFTKurHX){rKXkafHkHc = true;}
      if(oUjsuWhhIE == OGpbaswezq){zwLrBlpPII = true;}
      if(NgWxVURKiJ == lyaVLOwyAb){xozCPLwYSP = true;}
      while(lCgFTKurHX == jWCQRojMQV){sEBPOdGFNq = true;}
      while(OGpbaswezq == OGpbaswezq){ijNAcYhuaA = true;}
      while(lyaVLOwyAb == lyaVLOwyAb){GeoebyUcKy = true;}
      if(KBoofTwWex == true){KBoofTwWex = false;}
      if(lcKwVKLTrX == true){lcKwVKLTrX = false;}
      if(FGmMmmbLsE == true){FGmMmmbLsE = false;}
      if(OxreMMRAuH == true){OxreMMRAuH = false;}
      if(xZzBEJnezA == true){xZzBEJnezA = false;}
      if(DbGbWDOcBs == true){DbGbWDOcBs = false;}
      if(qkcaiokfiJ == true){qkcaiokfiJ = false;}
      if(rKXkafHkHc == true){rKXkafHkHc = false;}
      if(zwLrBlpPII == true){zwLrBlpPII = false;}
      if(xozCPLwYSP == true){xozCPLwYSP = false;}
      if(YHupIrEVBq == true){YHupIrEVBq = false;}
      if(wdUXttZkYw == true){wdUXttZkYw = false;}
      if(zUXZLDLVVO == true){zUXZLDLVVO = false;}
      if(jhRqEqAUjI == true){jhRqEqAUjI = false;}
      if(gUORMTTaHU == true){gUORMTTaHU = false;}
      if(lKAVQEjVeF == true){lKAVQEjVeF = false;}
      if(gizlGNMcTC == true){gizlGNMcTC = false;}
      if(sEBPOdGFNq == true){sEBPOdGFNq = false;}
      if(ijNAcYhuaA == true){ijNAcYhuaA = false;}
      if(GeoebyUcKy == true){GeoebyUcKy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSIDFOLRBB
{ 
  void JYmCTAhDYl()
  { 
      bool TBQwHGJusp = false;
      bool aGYfmHbQCD = false;
      bool lVxyExOVKQ = false;
      bool HzruhCNloX = false;
      bool AcFRYRgInG = false;
      bool tQeAQxESrJ = false;
      bool qnjchbNdyj = false;
      bool sobeCJQeYl = false;
      bool QGgEWqUrdk = false;
      bool xusegMrcjx = false;
      bool ECJDNEoAyH = false;
      bool gZsFsjGfGq = false;
      bool HUzNlywwxo = false;
      bool QnubhNxdqR = false;
      bool BTtWEXCnlx = false;
      bool FMVrpjCwQP = false;
      bool IrDIprdRWe = false;
      bool mconomZcJN = false;
      bool uHKAiERCky = false;
      bool LAMbJIQlfL = false;
      string WPKjHRTPwN;
      string fRaZqEZBli;
      string sknPIPXxfn;
      string xhhQAOtCSm;
      string IFAMMpZJBL;
      string FATwTkaubr;
      string tWiHPyiKZc;
      string JWhzZnjbCR;
      string oNuTixOkxO;
      string mzaarkVsxO;
      string HPjXBhRTVf;
      string BzrJCgaOYR;
      string ixNLpKwHHo;
      string RqdmKZdWRA;
      string ftPQNnGQYK;
      string KGTeeJCXhq;
      string lKMgNJUEzb;
      string DEwYlohwyB;
      string EehwdKXyHA;
      string XFoaNVghDD;
      if(WPKjHRTPwN == HPjXBhRTVf){TBQwHGJusp = true;}
      else if(HPjXBhRTVf == WPKjHRTPwN){ECJDNEoAyH = true;}
      if(fRaZqEZBli == BzrJCgaOYR){aGYfmHbQCD = true;}
      else if(BzrJCgaOYR == fRaZqEZBli){gZsFsjGfGq = true;}
      if(sknPIPXxfn == ixNLpKwHHo){lVxyExOVKQ = true;}
      else if(ixNLpKwHHo == sknPIPXxfn){HUzNlywwxo = true;}
      if(xhhQAOtCSm == RqdmKZdWRA){HzruhCNloX = true;}
      else if(RqdmKZdWRA == xhhQAOtCSm){QnubhNxdqR = true;}
      if(IFAMMpZJBL == ftPQNnGQYK){AcFRYRgInG = true;}
      else if(ftPQNnGQYK == IFAMMpZJBL){BTtWEXCnlx = true;}
      if(FATwTkaubr == KGTeeJCXhq){tQeAQxESrJ = true;}
      else if(KGTeeJCXhq == FATwTkaubr){FMVrpjCwQP = true;}
      if(tWiHPyiKZc == lKMgNJUEzb){qnjchbNdyj = true;}
      else if(lKMgNJUEzb == tWiHPyiKZc){IrDIprdRWe = true;}
      if(JWhzZnjbCR == DEwYlohwyB){sobeCJQeYl = true;}
      if(oNuTixOkxO == EehwdKXyHA){QGgEWqUrdk = true;}
      if(mzaarkVsxO == XFoaNVghDD){xusegMrcjx = true;}
      while(DEwYlohwyB == JWhzZnjbCR){mconomZcJN = true;}
      while(EehwdKXyHA == EehwdKXyHA){uHKAiERCky = true;}
      while(XFoaNVghDD == XFoaNVghDD){LAMbJIQlfL = true;}
      if(TBQwHGJusp == true){TBQwHGJusp = false;}
      if(aGYfmHbQCD == true){aGYfmHbQCD = false;}
      if(lVxyExOVKQ == true){lVxyExOVKQ = false;}
      if(HzruhCNloX == true){HzruhCNloX = false;}
      if(AcFRYRgInG == true){AcFRYRgInG = false;}
      if(tQeAQxESrJ == true){tQeAQxESrJ = false;}
      if(qnjchbNdyj == true){qnjchbNdyj = false;}
      if(sobeCJQeYl == true){sobeCJQeYl = false;}
      if(QGgEWqUrdk == true){QGgEWqUrdk = false;}
      if(xusegMrcjx == true){xusegMrcjx = false;}
      if(ECJDNEoAyH == true){ECJDNEoAyH = false;}
      if(gZsFsjGfGq == true){gZsFsjGfGq = false;}
      if(HUzNlywwxo == true){HUzNlywwxo = false;}
      if(QnubhNxdqR == true){QnubhNxdqR = false;}
      if(BTtWEXCnlx == true){BTtWEXCnlx = false;}
      if(FMVrpjCwQP == true){FMVrpjCwQP = false;}
      if(IrDIprdRWe == true){IrDIprdRWe = false;}
      if(mconomZcJN == true){mconomZcJN = false;}
      if(uHKAiERCky == true){uHKAiERCky = false;}
      if(LAMbJIQlfL == true){LAMbJIQlfL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCNMMOQHBI
{ 
  void aUcxdkRpdw()
  { 
      bool bXKwLedQuN = false;
      bool JZRHoKHmjg = false;
      bool XuBzMGlcPX = false;
      bool nrLIFuMDDM = false;
      bool dHfNwGKfse = false;
      bool SjgTnfWLiE = false;
      bool rAAWYRNJCt = false;
      bool yEjWCPOmCG = false;
      bool uGikEEKrUY = false;
      bool YATyUdGJne = false;
      bool rBczgOzKQX = false;
      bool QiJcJlRPRU = false;
      bool GVodVxjkBY = false;
      bool JFyXNtciEp = false;
      bool EzawHoqqoi = false;
      bool LqqTXVMzdj = false;
      bool eOIqNLklPP = false;
      bool IhKbQHurWf = false;
      bool FswSMROezq = false;
      bool gdFUKppihw = false;
      string HgbOyZEPkb;
      string NSlBOPLJHV;
      string FXnnldFzsI;
      string PsyFfmRYUJ;
      string OOcoepVgyZ;
      string KkIfcjsmbT;
      string TEWbMUUfVa;
      string yloxGptyJw;
      string IYASxejRcu;
      string tdxAoJrAbJ;
      string VoLWbYwKYm;
      string otcfLuEDeh;
      string kCDZgTonIx;
      string xtVAZSNdqY;
      string iZspGzAQos;
      string FoVtYTlkoI;
      string iHCbouXcFr;
      string haLFzLJMTg;
      string SXzOrHXbbG;
      string fbnioaWQBL;
      if(HgbOyZEPkb == VoLWbYwKYm){bXKwLedQuN = true;}
      else if(VoLWbYwKYm == HgbOyZEPkb){rBczgOzKQX = true;}
      if(NSlBOPLJHV == otcfLuEDeh){JZRHoKHmjg = true;}
      else if(otcfLuEDeh == NSlBOPLJHV){QiJcJlRPRU = true;}
      if(FXnnldFzsI == kCDZgTonIx){XuBzMGlcPX = true;}
      else if(kCDZgTonIx == FXnnldFzsI){GVodVxjkBY = true;}
      if(PsyFfmRYUJ == xtVAZSNdqY){nrLIFuMDDM = true;}
      else if(xtVAZSNdqY == PsyFfmRYUJ){JFyXNtciEp = true;}
      if(OOcoepVgyZ == iZspGzAQos){dHfNwGKfse = true;}
      else if(iZspGzAQos == OOcoepVgyZ){EzawHoqqoi = true;}
      if(KkIfcjsmbT == FoVtYTlkoI){SjgTnfWLiE = true;}
      else if(FoVtYTlkoI == KkIfcjsmbT){LqqTXVMzdj = true;}
      if(TEWbMUUfVa == iHCbouXcFr){rAAWYRNJCt = true;}
      else if(iHCbouXcFr == TEWbMUUfVa){eOIqNLklPP = true;}
      if(yloxGptyJw == haLFzLJMTg){yEjWCPOmCG = true;}
      if(IYASxejRcu == SXzOrHXbbG){uGikEEKrUY = true;}
      if(tdxAoJrAbJ == fbnioaWQBL){YATyUdGJne = true;}
      while(haLFzLJMTg == yloxGptyJw){IhKbQHurWf = true;}
      while(SXzOrHXbbG == SXzOrHXbbG){FswSMROezq = true;}
      while(fbnioaWQBL == fbnioaWQBL){gdFUKppihw = true;}
      if(bXKwLedQuN == true){bXKwLedQuN = false;}
      if(JZRHoKHmjg == true){JZRHoKHmjg = false;}
      if(XuBzMGlcPX == true){XuBzMGlcPX = false;}
      if(nrLIFuMDDM == true){nrLIFuMDDM = false;}
      if(dHfNwGKfse == true){dHfNwGKfse = false;}
      if(SjgTnfWLiE == true){SjgTnfWLiE = false;}
      if(rAAWYRNJCt == true){rAAWYRNJCt = false;}
      if(yEjWCPOmCG == true){yEjWCPOmCG = false;}
      if(uGikEEKrUY == true){uGikEEKrUY = false;}
      if(YATyUdGJne == true){YATyUdGJne = false;}
      if(rBczgOzKQX == true){rBczgOzKQX = false;}
      if(QiJcJlRPRU == true){QiJcJlRPRU = false;}
      if(GVodVxjkBY == true){GVodVxjkBY = false;}
      if(JFyXNtciEp == true){JFyXNtciEp = false;}
      if(EzawHoqqoi == true){EzawHoqqoi = false;}
      if(LqqTXVMzdj == true){LqqTXVMzdj = false;}
      if(eOIqNLklPP == true){eOIqNLklPP = false;}
      if(IhKbQHurWf == true){IhKbQHurWf = false;}
      if(FswSMROezq == true){FswSMROezq = false;}
      if(gdFUKppihw == true){gdFUKppihw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDXIIOIHPB
{ 
  void BdhkmJOXXE()
  { 
      bool KoKNFFgbfT = false;
      bool ZTegpUpwux = false;
      bool USQyhebYFW = false;
      bool XfjZXAPZCa = false;
      bool HJWSPqZPEZ = false;
      bool PqKiRrYMfa = false;
      bool dHWJusiEJp = false;
      bool FQtUpLwxhp = false;
      bool ELTfGgUBIe = false;
      bool aCtawzmMWV = false;
      bool IUGOTyxprF = false;
      bool uadpWRmpCO = false;
      bool YhwdOCWSXp = false;
      bool YiZMhiFFLH = false;
      bool jeICjzYDEd = false;
      bool LwJIxaYbAQ = false;
      bool bdRCgLBQIm = false;
      bool MhdtetYttO = false;
      bool dSOsdbZRPG = false;
      bool KcEufFMGUX = false;
      string zjIfVmSumr;
      string RQyoCiboPI;
      string fwWkFQNtFo;
      string WSbRSalOzu;
      string koPpiVBTEN;
      string gNWIUCNXZE;
      string ZXoyUzngVa;
      string xNoTWpggCj;
      string PsorIIuTxP;
      string MOouVMzRUj;
      string gTxcPTYCkd;
      string VgVpnfixoM;
      string EUjGOiYtyJ;
      string qOLRCuwLbo;
      string jrhSsfsyGp;
      string dCcIeMjqOg;
      string tdEblHVDns;
      string jXUAbLlQMh;
      string pZmIfolClo;
      string KEwutFmGfl;
      if(zjIfVmSumr == gTxcPTYCkd){KoKNFFgbfT = true;}
      else if(gTxcPTYCkd == zjIfVmSumr){IUGOTyxprF = true;}
      if(RQyoCiboPI == VgVpnfixoM){ZTegpUpwux = true;}
      else if(VgVpnfixoM == RQyoCiboPI){uadpWRmpCO = true;}
      if(fwWkFQNtFo == EUjGOiYtyJ){USQyhebYFW = true;}
      else if(EUjGOiYtyJ == fwWkFQNtFo){YhwdOCWSXp = true;}
      if(WSbRSalOzu == qOLRCuwLbo){XfjZXAPZCa = true;}
      else if(qOLRCuwLbo == WSbRSalOzu){YiZMhiFFLH = true;}
      if(koPpiVBTEN == jrhSsfsyGp){HJWSPqZPEZ = true;}
      else if(jrhSsfsyGp == koPpiVBTEN){jeICjzYDEd = true;}
      if(gNWIUCNXZE == dCcIeMjqOg){PqKiRrYMfa = true;}
      else if(dCcIeMjqOg == gNWIUCNXZE){LwJIxaYbAQ = true;}
      if(ZXoyUzngVa == tdEblHVDns){dHWJusiEJp = true;}
      else if(tdEblHVDns == ZXoyUzngVa){bdRCgLBQIm = true;}
      if(xNoTWpggCj == jXUAbLlQMh){FQtUpLwxhp = true;}
      if(PsorIIuTxP == pZmIfolClo){ELTfGgUBIe = true;}
      if(MOouVMzRUj == KEwutFmGfl){aCtawzmMWV = true;}
      while(jXUAbLlQMh == xNoTWpggCj){MhdtetYttO = true;}
      while(pZmIfolClo == pZmIfolClo){dSOsdbZRPG = true;}
      while(KEwutFmGfl == KEwutFmGfl){KcEufFMGUX = true;}
      if(KoKNFFgbfT == true){KoKNFFgbfT = false;}
      if(ZTegpUpwux == true){ZTegpUpwux = false;}
      if(USQyhebYFW == true){USQyhebYFW = false;}
      if(XfjZXAPZCa == true){XfjZXAPZCa = false;}
      if(HJWSPqZPEZ == true){HJWSPqZPEZ = false;}
      if(PqKiRrYMfa == true){PqKiRrYMfa = false;}
      if(dHWJusiEJp == true){dHWJusiEJp = false;}
      if(FQtUpLwxhp == true){FQtUpLwxhp = false;}
      if(ELTfGgUBIe == true){ELTfGgUBIe = false;}
      if(aCtawzmMWV == true){aCtawzmMWV = false;}
      if(IUGOTyxprF == true){IUGOTyxprF = false;}
      if(uadpWRmpCO == true){uadpWRmpCO = false;}
      if(YhwdOCWSXp == true){YhwdOCWSXp = false;}
      if(YiZMhiFFLH == true){YiZMhiFFLH = false;}
      if(jeICjzYDEd == true){jeICjzYDEd = false;}
      if(LwJIxaYbAQ == true){LwJIxaYbAQ = false;}
      if(bdRCgLBQIm == true){bdRCgLBQIm = false;}
      if(MhdtetYttO == true){MhdtetYttO = false;}
      if(dSOsdbZRPG == true){dSOsdbZRPG = false;}
      if(KcEufFMGUX == true){KcEufFMGUX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBQBFRTTOO
{ 
  void ZVNeeFUSFh()
  { 
      bool GRcudeQRwU = false;
      bool eDaEHnCGro = false;
      bool dQEdtFPATq = false;
      bool wywQOVLquB = false;
      bool pBitgmAVLa = false;
      bool EyyIGpMzAX = false;
      bool OQxEXgGJpk = false;
      bool bKKpzbhKwH = false;
      bool FtormxznJY = false;
      bool JMqXmYEdVA = false;
      bool fpfZzsnIIe = false;
      bool HBCrRUbFRa = false;
      bool gSzRbOTmDZ = false;
      bool XEowbONOss = false;
      bool JqfeQHJyFR = false;
      bool xyLtSNqOyj = false;
      bool ZBEhHDLGQD = false;
      bool HNLYQpmUAT = false;
      bool FUgkcYrtcO = false;
      bool XyPISIlxWM = false;
      string BttItZkdSl;
      string oqHIHFRhla;
      string nhHseqTsPM;
      string lAqgVLpTID;
      string HeipyYOBth;
      string igyxxSmAcD;
      string FrNFAnzZmw;
      string OyYhTIzQuG;
      string cSzgcEBtjC;
      string YppFyPQdpJ;
      string YnNyTkIPdo;
      string TVFWZlrgbu;
      string mFpkXYISjE;
      string qVZkgoEBNr;
      string wkQuiCkSfL;
      string WjBuWTycZt;
      string cofZxxuTpk;
      string hqSiyBotCU;
      string momYgHTeOM;
      string pbaSPHFpyk;
      if(BttItZkdSl == YnNyTkIPdo){GRcudeQRwU = true;}
      else if(YnNyTkIPdo == BttItZkdSl){fpfZzsnIIe = true;}
      if(oqHIHFRhla == TVFWZlrgbu){eDaEHnCGro = true;}
      else if(TVFWZlrgbu == oqHIHFRhla){HBCrRUbFRa = true;}
      if(nhHseqTsPM == mFpkXYISjE){dQEdtFPATq = true;}
      else if(mFpkXYISjE == nhHseqTsPM){gSzRbOTmDZ = true;}
      if(lAqgVLpTID == qVZkgoEBNr){wywQOVLquB = true;}
      else if(qVZkgoEBNr == lAqgVLpTID){XEowbONOss = true;}
      if(HeipyYOBth == wkQuiCkSfL){pBitgmAVLa = true;}
      else if(wkQuiCkSfL == HeipyYOBth){JqfeQHJyFR = true;}
      if(igyxxSmAcD == WjBuWTycZt){EyyIGpMzAX = true;}
      else if(WjBuWTycZt == igyxxSmAcD){xyLtSNqOyj = true;}
      if(FrNFAnzZmw == cofZxxuTpk){OQxEXgGJpk = true;}
      else if(cofZxxuTpk == FrNFAnzZmw){ZBEhHDLGQD = true;}
      if(OyYhTIzQuG == hqSiyBotCU){bKKpzbhKwH = true;}
      if(cSzgcEBtjC == momYgHTeOM){FtormxznJY = true;}
      if(YppFyPQdpJ == pbaSPHFpyk){JMqXmYEdVA = true;}
      while(hqSiyBotCU == OyYhTIzQuG){HNLYQpmUAT = true;}
      while(momYgHTeOM == momYgHTeOM){FUgkcYrtcO = true;}
      while(pbaSPHFpyk == pbaSPHFpyk){XyPISIlxWM = true;}
      if(GRcudeQRwU == true){GRcudeQRwU = false;}
      if(eDaEHnCGro == true){eDaEHnCGro = false;}
      if(dQEdtFPATq == true){dQEdtFPATq = false;}
      if(wywQOVLquB == true){wywQOVLquB = false;}
      if(pBitgmAVLa == true){pBitgmAVLa = false;}
      if(EyyIGpMzAX == true){EyyIGpMzAX = false;}
      if(OQxEXgGJpk == true){OQxEXgGJpk = false;}
      if(bKKpzbhKwH == true){bKKpzbhKwH = false;}
      if(FtormxznJY == true){FtormxznJY = false;}
      if(JMqXmYEdVA == true){JMqXmYEdVA = false;}
      if(fpfZzsnIIe == true){fpfZzsnIIe = false;}
      if(HBCrRUbFRa == true){HBCrRUbFRa = false;}
      if(gSzRbOTmDZ == true){gSzRbOTmDZ = false;}
      if(XEowbONOss == true){XEowbONOss = false;}
      if(JqfeQHJyFR == true){JqfeQHJyFR = false;}
      if(xyLtSNqOyj == true){xyLtSNqOyj = false;}
      if(ZBEhHDLGQD == true){ZBEhHDLGQD = false;}
      if(HNLYQpmUAT == true){HNLYQpmUAT = false;}
      if(FUgkcYrtcO == true){FUgkcYrtcO = false;}
      if(XyPISIlxWM == true){XyPISIlxWM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZGGWFVUBU
{ 
  void uMHXYBQlFK()
  { 
      bool XkcxJliKdZ = false;
      bool MtSNQorrzZ = false;
      bool VQuBSrXlmT = false;
      bool PrEJiMzxER = false;
      bool FDcmLxHhEL = false;
      bool pxsDRHpbeR = false;
      bool NxXJJUoIeE = false;
      bool otmgTRnHoU = false;
      bool kohadSzArb = false;
      bool VXSmEIfSdq = false;
      bool HyDAVuKLiz = false;
      bool ThlJfYPwfq = false;
      bool UoPChRbAcL = false;
      bool lUdyMlkhEh = false;
      bool HmQsInlJGf = false;
      bool simlWSiBRE = false;
      bool TKiXNyDmwt = false;
      bool mgqxigXWtt = false;
      bool fRsxSChqbt = false;
      bool DjPAOxEsfJ = false;
      string cWfTlAGLXX;
      string KNBsOJgbwb;
      string VFYEUkNagx;
      string pPYpxEWzmV;
      string XLhjcTOjir;
      string feWQEXybyA;
      string leeZhuoLwJ;
      string lgoZDKWnaB;
      string WdroRKrIkZ;
      string FuBljsfHCh;
      string dCmZFypwMs;
      string AJBxdImpHW;
      string CfZWDqfCpJ;
      string eOlsWTpSiT;
      string UwurYwsDHb;
      string GpzefybQVO;
      string RmGCOkXIZK;
      string RUGnBFkhxH;
      string xcuODoOGMY;
      string qZwUBhordm;
      if(cWfTlAGLXX == dCmZFypwMs){XkcxJliKdZ = true;}
      else if(dCmZFypwMs == cWfTlAGLXX){HyDAVuKLiz = true;}
      if(KNBsOJgbwb == AJBxdImpHW){MtSNQorrzZ = true;}
      else if(AJBxdImpHW == KNBsOJgbwb){ThlJfYPwfq = true;}
      if(VFYEUkNagx == CfZWDqfCpJ){VQuBSrXlmT = true;}
      else if(CfZWDqfCpJ == VFYEUkNagx){UoPChRbAcL = true;}
      if(pPYpxEWzmV == eOlsWTpSiT){PrEJiMzxER = true;}
      else if(eOlsWTpSiT == pPYpxEWzmV){lUdyMlkhEh = true;}
      if(XLhjcTOjir == UwurYwsDHb){FDcmLxHhEL = true;}
      else if(UwurYwsDHb == XLhjcTOjir){HmQsInlJGf = true;}
      if(feWQEXybyA == GpzefybQVO){pxsDRHpbeR = true;}
      else if(GpzefybQVO == feWQEXybyA){simlWSiBRE = true;}
      if(leeZhuoLwJ == RmGCOkXIZK){NxXJJUoIeE = true;}
      else if(RmGCOkXIZK == leeZhuoLwJ){TKiXNyDmwt = true;}
      if(lgoZDKWnaB == RUGnBFkhxH){otmgTRnHoU = true;}
      if(WdroRKrIkZ == xcuODoOGMY){kohadSzArb = true;}
      if(FuBljsfHCh == qZwUBhordm){VXSmEIfSdq = true;}
      while(RUGnBFkhxH == lgoZDKWnaB){mgqxigXWtt = true;}
      while(xcuODoOGMY == xcuODoOGMY){fRsxSChqbt = true;}
      while(qZwUBhordm == qZwUBhordm){DjPAOxEsfJ = true;}
      if(XkcxJliKdZ == true){XkcxJliKdZ = false;}
      if(MtSNQorrzZ == true){MtSNQorrzZ = false;}
      if(VQuBSrXlmT == true){VQuBSrXlmT = false;}
      if(PrEJiMzxER == true){PrEJiMzxER = false;}
      if(FDcmLxHhEL == true){FDcmLxHhEL = false;}
      if(pxsDRHpbeR == true){pxsDRHpbeR = false;}
      if(NxXJJUoIeE == true){NxXJJUoIeE = false;}
      if(otmgTRnHoU == true){otmgTRnHoU = false;}
      if(kohadSzArb == true){kohadSzArb = false;}
      if(VXSmEIfSdq == true){VXSmEIfSdq = false;}
      if(HyDAVuKLiz == true){HyDAVuKLiz = false;}
      if(ThlJfYPwfq == true){ThlJfYPwfq = false;}
      if(UoPChRbAcL == true){UoPChRbAcL = false;}
      if(lUdyMlkhEh == true){lUdyMlkhEh = false;}
      if(HmQsInlJGf == true){HmQsInlJGf = false;}
      if(simlWSiBRE == true){simlWSiBRE = false;}
      if(TKiXNyDmwt == true){TKiXNyDmwt = false;}
      if(mgqxigXWtt == true){mgqxigXWtt = false;}
      if(fRsxSChqbt == true){fRsxSChqbt = false;}
      if(DjPAOxEsfJ == true){DjPAOxEsfJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXTAODSTXT
{ 
  void gCGpZOsJPq()
  { 
      bool nacQEHwZRV = false;
      bool wqsFEYoDRi = false;
      bool FasKDpzRkA = false;
      bool ZHEcTJkVom = false;
      bool csWABkIEhu = false;
      bool mnYcONgSMO = false;
      bool IdoRwomQku = false;
      bool mSNeFLDsIR = false;
      bool gtioMlhbOG = false;
      bool bSIadzEFDL = false;
      bool yrTmHUZtWC = false;
      bool JmJugNtzEK = false;
      bool GLBdSUJmAG = false;
      bool HyoxSoawgr = false;
      bool LnEMwoINsP = false;
      bool FEAsEmqoUm = false;
      bool KlsQtLyMbr = false;
      bool mxSMySGnhd = false;
      bool MusjBDxurf = false;
      bool xkbtgZunRj = false;
      string MrTruVTfhX;
      string hcfhZtLEWj;
      string VximFCJnEW;
      string ZwEudKzYGu;
      string bLEYgSbjpL;
      string aJQesPIgmr;
      string LebKxlYkDO;
      string tlyaHKrKFl;
      string aZyswPeYBO;
      string CSlOjwjsbu;
      string spfaQnLoWh;
      string WyaAQlfhOg;
      string HzioMbAjqK;
      string ayiKrjsXbI;
      string EoCSrDqkxx;
      string QBetntHqNo;
      string nbxLHXOQIg;
      string rIFFcRxPxI;
      string jOlttYSnWy;
      string cCJmUcqpLT;
      if(MrTruVTfhX == spfaQnLoWh){nacQEHwZRV = true;}
      else if(spfaQnLoWh == MrTruVTfhX){yrTmHUZtWC = true;}
      if(hcfhZtLEWj == WyaAQlfhOg){wqsFEYoDRi = true;}
      else if(WyaAQlfhOg == hcfhZtLEWj){JmJugNtzEK = true;}
      if(VximFCJnEW == HzioMbAjqK){FasKDpzRkA = true;}
      else if(HzioMbAjqK == VximFCJnEW){GLBdSUJmAG = true;}
      if(ZwEudKzYGu == ayiKrjsXbI){ZHEcTJkVom = true;}
      else if(ayiKrjsXbI == ZwEudKzYGu){HyoxSoawgr = true;}
      if(bLEYgSbjpL == EoCSrDqkxx){csWABkIEhu = true;}
      else if(EoCSrDqkxx == bLEYgSbjpL){LnEMwoINsP = true;}
      if(aJQesPIgmr == QBetntHqNo){mnYcONgSMO = true;}
      else if(QBetntHqNo == aJQesPIgmr){FEAsEmqoUm = true;}
      if(LebKxlYkDO == nbxLHXOQIg){IdoRwomQku = true;}
      else if(nbxLHXOQIg == LebKxlYkDO){KlsQtLyMbr = true;}
      if(tlyaHKrKFl == rIFFcRxPxI){mSNeFLDsIR = true;}
      if(aZyswPeYBO == jOlttYSnWy){gtioMlhbOG = true;}
      if(CSlOjwjsbu == cCJmUcqpLT){bSIadzEFDL = true;}
      while(rIFFcRxPxI == tlyaHKrKFl){mxSMySGnhd = true;}
      while(jOlttYSnWy == jOlttYSnWy){MusjBDxurf = true;}
      while(cCJmUcqpLT == cCJmUcqpLT){xkbtgZunRj = true;}
      if(nacQEHwZRV == true){nacQEHwZRV = false;}
      if(wqsFEYoDRi == true){wqsFEYoDRi = false;}
      if(FasKDpzRkA == true){FasKDpzRkA = false;}
      if(ZHEcTJkVom == true){ZHEcTJkVom = false;}
      if(csWABkIEhu == true){csWABkIEhu = false;}
      if(mnYcONgSMO == true){mnYcONgSMO = false;}
      if(IdoRwomQku == true){IdoRwomQku = false;}
      if(mSNeFLDsIR == true){mSNeFLDsIR = false;}
      if(gtioMlhbOG == true){gtioMlhbOG = false;}
      if(bSIadzEFDL == true){bSIadzEFDL = false;}
      if(yrTmHUZtWC == true){yrTmHUZtWC = false;}
      if(JmJugNtzEK == true){JmJugNtzEK = false;}
      if(GLBdSUJmAG == true){GLBdSUJmAG = false;}
      if(HyoxSoawgr == true){HyoxSoawgr = false;}
      if(LnEMwoINsP == true){LnEMwoINsP = false;}
      if(FEAsEmqoUm == true){FEAsEmqoUm = false;}
      if(KlsQtLyMbr == true){KlsQtLyMbr = false;}
      if(mxSMySGnhd == true){mxSMySGnhd = false;}
      if(MusjBDxurf == true){MusjBDxurf = false;}
      if(xkbtgZunRj == true){xkbtgZunRj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZIWSZUCYB
{ 
  void pwjTXVghbH()
  { 
      bool RgQPUTRyse = false;
      bool KRMtQcpjJu = false;
      bool JCVxndXGFf = false;
      bool ddBLAZrCkP = false;
      bool dZdBpWBAoO = false;
      bool QIgNROKSbq = false;
      bool wKrNBfQBtp = false;
      bool jmysQjYUGQ = false;
      bool bWRqOUxmsk = false;
      bool OZatTTgQzK = false;
      bool GAGyddJmxh = false;
      bool ppLKOYsByg = false;
      bool icHIbKMEZx = false;
      bool CHUwKbPSMk = false;
      bool KJpLuYNQft = false;
      bool ZeRSbcrxWT = false;
      bool RFNzehVPzm = false;
      bool JaoMVYmwND = false;
      bool wwYeXXpBUh = false;
      bool iSwrTEwqfM = false;
      string QblBZlqypp;
      string qDPGYQNlZE;
      string xbJFFZSjRX;
      string EpzjypDrmm;
      string TBmVLnUFFa;
      string hTwzPoSgwz;
      string TGgRlBEfHh;
      string NUzljwnmtQ;
      string FMeqpjtzUJ;
      string XWumTNUViK;
      string jnyWNMUJPS;
      string AelftGapaC;
      string HELxKpZLSV;
      string aSEifQOIcd;
      string PjjBJrjPsM;
      string letgCebAMW;
      string lIpsrhaCzc;
      string rSMwmWUKmR;
      string GJSGiwXXgB;
      string nOuFqGspJb;
      if(QblBZlqypp == jnyWNMUJPS){RgQPUTRyse = true;}
      else if(jnyWNMUJPS == QblBZlqypp){GAGyddJmxh = true;}
      if(qDPGYQNlZE == AelftGapaC){KRMtQcpjJu = true;}
      else if(AelftGapaC == qDPGYQNlZE){ppLKOYsByg = true;}
      if(xbJFFZSjRX == HELxKpZLSV){JCVxndXGFf = true;}
      else if(HELxKpZLSV == xbJFFZSjRX){icHIbKMEZx = true;}
      if(EpzjypDrmm == aSEifQOIcd){ddBLAZrCkP = true;}
      else if(aSEifQOIcd == EpzjypDrmm){CHUwKbPSMk = true;}
      if(TBmVLnUFFa == PjjBJrjPsM){dZdBpWBAoO = true;}
      else if(PjjBJrjPsM == TBmVLnUFFa){KJpLuYNQft = true;}
      if(hTwzPoSgwz == letgCebAMW){QIgNROKSbq = true;}
      else if(letgCebAMW == hTwzPoSgwz){ZeRSbcrxWT = true;}
      if(TGgRlBEfHh == lIpsrhaCzc){wKrNBfQBtp = true;}
      else if(lIpsrhaCzc == TGgRlBEfHh){RFNzehVPzm = true;}
      if(NUzljwnmtQ == rSMwmWUKmR){jmysQjYUGQ = true;}
      if(FMeqpjtzUJ == GJSGiwXXgB){bWRqOUxmsk = true;}
      if(XWumTNUViK == nOuFqGspJb){OZatTTgQzK = true;}
      while(rSMwmWUKmR == NUzljwnmtQ){JaoMVYmwND = true;}
      while(GJSGiwXXgB == GJSGiwXXgB){wwYeXXpBUh = true;}
      while(nOuFqGspJb == nOuFqGspJb){iSwrTEwqfM = true;}
      if(RgQPUTRyse == true){RgQPUTRyse = false;}
      if(KRMtQcpjJu == true){KRMtQcpjJu = false;}
      if(JCVxndXGFf == true){JCVxndXGFf = false;}
      if(ddBLAZrCkP == true){ddBLAZrCkP = false;}
      if(dZdBpWBAoO == true){dZdBpWBAoO = false;}
      if(QIgNROKSbq == true){QIgNROKSbq = false;}
      if(wKrNBfQBtp == true){wKrNBfQBtp = false;}
      if(jmysQjYUGQ == true){jmysQjYUGQ = false;}
      if(bWRqOUxmsk == true){bWRqOUxmsk = false;}
      if(OZatTTgQzK == true){OZatTTgQzK = false;}
      if(GAGyddJmxh == true){GAGyddJmxh = false;}
      if(ppLKOYsByg == true){ppLKOYsByg = false;}
      if(icHIbKMEZx == true){icHIbKMEZx = false;}
      if(CHUwKbPSMk == true){CHUwKbPSMk = false;}
      if(KJpLuYNQft == true){KJpLuYNQft = false;}
      if(ZeRSbcrxWT == true){ZeRSbcrxWT = false;}
      if(RFNzehVPzm == true){RFNzehVPzm = false;}
      if(JaoMVYmwND == true){JaoMVYmwND = false;}
      if(wwYeXXpBUh == true){wwYeXXpBUh = false;}
      if(iSwrTEwqfM == true){iSwrTEwqfM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KZXZAQAQBC
{ 
  void ktxUMxaYaJ()
  { 
      bool JYRenxaSiV = false;
      bool crpcQZzcuT = false;
      bool LWliKkbIsB = false;
      bool QHLpKWtnom = false;
      bool BpkbRLwfVf = false;
      bool ryUJlllhUD = false;
      bool VSZhFUfzRs = false;
      bool eLnHSVlKQy = false;
      bool nwlMJRlCEX = false;
      bool kMTkRiQDWw = false;
      bool fwNcBgKMqQ = false;
      bool zbRVOZfNYn = false;
      bool icutIRqCpi = false;
      bool EimUSqhJKb = false;
      bool HZLnXJuyVr = false;
      bool DDeiNCBSUi = false;
      bool pHWHLQnwDW = false;
      bool qVCwfIRGVz = false;
      bool WsgyfBEEGP = false;
      bool pPoakzCEbH = false;
      string BrytLHUGma;
      string RDeVhWqkfd;
      string uURwDZPGuK;
      string cNloxSJNer;
      string lckhtloLhe;
      string XljpPgZBql;
      string rOKcxEQpYO;
      string NdFnqRjiCQ;
      string kDYPlqcwYQ;
      string sIVszXRIjo;
      string UzmSRtfuzx;
      string wqyZAnptpG;
      string aUQIVFIMoS;
      string AayNwlQFyr;
      string LhwaTBJusL;
      string hWRdOAhexL;
      string lSGfxVrkdO;
      string WjuytrXpnT;
      string uMSckcJUyu;
      string DlImFrbPdy;
      if(BrytLHUGma == UzmSRtfuzx){JYRenxaSiV = true;}
      else if(UzmSRtfuzx == BrytLHUGma){fwNcBgKMqQ = true;}
      if(RDeVhWqkfd == wqyZAnptpG){crpcQZzcuT = true;}
      else if(wqyZAnptpG == RDeVhWqkfd){zbRVOZfNYn = true;}
      if(uURwDZPGuK == aUQIVFIMoS){LWliKkbIsB = true;}
      else if(aUQIVFIMoS == uURwDZPGuK){icutIRqCpi = true;}
      if(cNloxSJNer == AayNwlQFyr){QHLpKWtnom = true;}
      else if(AayNwlQFyr == cNloxSJNer){EimUSqhJKb = true;}
      if(lckhtloLhe == LhwaTBJusL){BpkbRLwfVf = true;}
      else if(LhwaTBJusL == lckhtloLhe){HZLnXJuyVr = true;}
      if(XljpPgZBql == hWRdOAhexL){ryUJlllhUD = true;}
      else if(hWRdOAhexL == XljpPgZBql){DDeiNCBSUi = true;}
      if(rOKcxEQpYO == lSGfxVrkdO){VSZhFUfzRs = true;}
      else if(lSGfxVrkdO == rOKcxEQpYO){pHWHLQnwDW = true;}
      if(NdFnqRjiCQ == WjuytrXpnT){eLnHSVlKQy = true;}
      if(kDYPlqcwYQ == uMSckcJUyu){nwlMJRlCEX = true;}
      if(sIVszXRIjo == DlImFrbPdy){kMTkRiQDWw = true;}
      while(WjuytrXpnT == NdFnqRjiCQ){qVCwfIRGVz = true;}
      while(uMSckcJUyu == uMSckcJUyu){WsgyfBEEGP = true;}
      while(DlImFrbPdy == DlImFrbPdy){pPoakzCEbH = true;}
      if(JYRenxaSiV == true){JYRenxaSiV = false;}
      if(crpcQZzcuT == true){crpcQZzcuT = false;}
      if(LWliKkbIsB == true){LWliKkbIsB = false;}
      if(QHLpKWtnom == true){QHLpKWtnom = false;}
      if(BpkbRLwfVf == true){BpkbRLwfVf = false;}
      if(ryUJlllhUD == true){ryUJlllhUD = false;}
      if(VSZhFUfzRs == true){VSZhFUfzRs = false;}
      if(eLnHSVlKQy == true){eLnHSVlKQy = false;}
      if(nwlMJRlCEX == true){nwlMJRlCEX = false;}
      if(kMTkRiQDWw == true){kMTkRiQDWw = false;}
      if(fwNcBgKMqQ == true){fwNcBgKMqQ = false;}
      if(zbRVOZfNYn == true){zbRVOZfNYn = false;}
      if(icutIRqCpi == true){icutIRqCpi = false;}
      if(EimUSqhJKb == true){EimUSqhJKb = false;}
      if(HZLnXJuyVr == true){HZLnXJuyVr = false;}
      if(DDeiNCBSUi == true){DDeiNCBSUi = false;}
      if(pHWHLQnwDW == true){pHWHLQnwDW = false;}
      if(qVCwfIRGVz == true){qVCwfIRGVz = false;}
      if(WsgyfBEEGP == true){WsgyfBEEGP = false;}
      if(pPoakzCEbH == true){pPoakzCEbH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOUHAVRSLL
{ 
  void EruBZcIgRk()
  { 
      bool ijaTQgWWOk = false;
      bool zVCCNnzZpU = false;
      bool tbyHoAoDKJ = false;
      bool eNZTsGHUwR = false;
      bool uIlQIOedPZ = false;
      bool xyLrhHlSeQ = false;
      bool rTMFGkwhJG = false;
      bool gddXZlpgzZ = false;
      bool VKmjLfCgkl = false;
      bool UnpfYawgKW = false;
      bool SwUJrTUmSw = false;
      bool RETEtggbsZ = false;
      bool hOwWlsnyzy = false;
      bool oJVbHYpdqr = false;
      bool LPOoUPTkkr = false;
      bool tTmknEAxWz = false;
      bool fVmUGIhqxV = false;
      bool qCjBOSAHCV = false;
      bool YCNGDVVknC = false;
      bool YrGrMobshM = false;
      string XtSgQVbjip;
      string QBTpIWQier;
      string pmGeBzdKDm;
      string lmNQnCQKhE;
      string DzDTiIDAam;
      string DaZfCjnmfQ;
      string qRfuEcnDCF;
      string FFBZnqilwr;
      string udiQjLMhND;
      string OceQMlTHOF;
      string UAxVhxYAqL;
      string BBqmVNiPLs;
      string QFpzpcZjMC;
      string WbXqWufMhl;
      string lMpCCNkqtz;
      string DEwVnOJyfE;
      string XomonZdAPa;
      string hVgYGDPnwc;
      string qioNzSeBCH;
      string kggcOxYBNc;
      if(XtSgQVbjip == UAxVhxYAqL){ijaTQgWWOk = true;}
      else if(UAxVhxYAqL == XtSgQVbjip){SwUJrTUmSw = true;}
      if(QBTpIWQier == BBqmVNiPLs){zVCCNnzZpU = true;}
      else if(BBqmVNiPLs == QBTpIWQier){RETEtggbsZ = true;}
      if(pmGeBzdKDm == QFpzpcZjMC){tbyHoAoDKJ = true;}
      else if(QFpzpcZjMC == pmGeBzdKDm){hOwWlsnyzy = true;}
      if(lmNQnCQKhE == WbXqWufMhl){eNZTsGHUwR = true;}
      else if(WbXqWufMhl == lmNQnCQKhE){oJVbHYpdqr = true;}
      if(DzDTiIDAam == lMpCCNkqtz){uIlQIOedPZ = true;}
      else if(lMpCCNkqtz == DzDTiIDAam){LPOoUPTkkr = true;}
      if(DaZfCjnmfQ == DEwVnOJyfE){xyLrhHlSeQ = true;}
      else if(DEwVnOJyfE == DaZfCjnmfQ){tTmknEAxWz = true;}
      if(qRfuEcnDCF == XomonZdAPa){rTMFGkwhJG = true;}
      else if(XomonZdAPa == qRfuEcnDCF){fVmUGIhqxV = true;}
      if(FFBZnqilwr == hVgYGDPnwc){gddXZlpgzZ = true;}
      if(udiQjLMhND == qioNzSeBCH){VKmjLfCgkl = true;}
      if(OceQMlTHOF == kggcOxYBNc){UnpfYawgKW = true;}
      while(hVgYGDPnwc == FFBZnqilwr){qCjBOSAHCV = true;}
      while(qioNzSeBCH == qioNzSeBCH){YCNGDVVknC = true;}
      while(kggcOxYBNc == kggcOxYBNc){YrGrMobshM = true;}
      if(ijaTQgWWOk == true){ijaTQgWWOk = false;}
      if(zVCCNnzZpU == true){zVCCNnzZpU = false;}
      if(tbyHoAoDKJ == true){tbyHoAoDKJ = false;}
      if(eNZTsGHUwR == true){eNZTsGHUwR = false;}
      if(uIlQIOedPZ == true){uIlQIOedPZ = false;}
      if(xyLrhHlSeQ == true){xyLrhHlSeQ = false;}
      if(rTMFGkwhJG == true){rTMFGkwhJG = false;}
      if(gddXZlpgzZ == true){gddXZlpgzZ = false;}
      if(VKmjLfCgkl == true){VKmjLfCgkl = false;}
      if(UnpfYawgKW == true){UnpfYawgKW = false;}
      if(SwUJrTUmSw == true){SwUJrTUmSw = false;}
      if(RETEtggbsZ == true){RETEtggbsZ = false;}
      if(hOwWlsnyzy == true){hOwWlsnyzy = false;}
      if(oJVbHYpdqr == true){oJVbHYpdqr = false;}
      if(LPOoUPTkkr == true){LPOoUPTkkr = false;}
      if(tTmknEAxWz == true){tTmknEAxWz = false;}
      if(fVmUGIhqxV == true){fVmUGIhqxV = false;}
      if(qCjBOSAHCV == true){qCjBOSAHCV = false;}
      if(YCNGDVVknC == true){YCNGDVVknC = false;}
      if(YrGrMobshM == true){YrGrMobshM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNYEOYMGRT
{ 
  void tqcYJIsUyp()
  { 
      bool GRJjTxpcSF = false;
      bool LpnUUuPYzI = false;
      bool teAimqKfFt = false;
      bool XSVIcRiisX = false;
      bool xqBRGgOCQU = false;
      bool hiSNcbRZxb = false;
      bool lKWYgrTerC = false;
      bool MffaKDchbG = false;
      bool bIOkLnAIfA = false;
      bool AIlRkmTcjN = false;
      bool MiJNHCDrDZ = false;
      bool zixqAdulMr = false;
      bool rLzqCEtNoX = false;
      bool izyOsrzBcJ = false;
      bool jIEGBRKuRH = false;
      bool qhPqVBjSKD = false;
      bool HpCepzjiyH = false;
      bool dsIDHiGrok = false;
      bool szwgfAiGrr = false;
      bool IgqYBtFZPC = false;
      string QKkqbLiJuL;
      string XGZbSWNBVT;
      string pqKdnLgzmX;
      string EiYGrmcfaM;
      string aiyrDDMVaV;
      string ZYYPxZzGCP;
      string djWXGnhTje;
      string tgZJrGrSZk;
      string zKYQxfKJIS;
      string nVcLhqMZlP;
      string UslwbryOWp;
      string gggRQTKFaZ;
      string cXKRqXEObB;
      string tSgJPFYcoE;
      string humRkGoLuO;
      string fGyLmxiUFD;
      string nimUwNAWBK;
      string uhQVrgkrfj;
      string irTNVmTUWS;
      string WDWkQyIRVW;
      if(QKkqbLiJuL == UslwbryOWp){GRJjTxpcSF = true;}
      else if(UslwbryOWp == QKkqbLiJuL){MiJNHCDrDZ = true;}
      if(XGZbSWNBVT == gggRQTKFaZ){LpnUUuPYzI = true;}
      else if(gggRQTKFaZ == XGZbSWNBVT){zixqAdulMr = true;}
      if(pqKdnLgzmX == cXKRqXEObB){teAimqKfFt = true;}
      else if(cXKRqXEObB == pqKdnLgzmX){rLzqCEtNoX = true;}
      if(EiYGrmcfaM == tSgJPFYcoE){XSVIcRiisX = true;}
      else if(tSgJPFYcoE == EiYGrmcfaM){izyOsrzBcJ = true;}
      if(aiyrDDMVaV == humRkGoLuO){xqBRGgOCQU = true;}
      else if(humRkGoLuO == aiyrDDMVaV){jIEGBRKuRH = true;}
      if(ZYYPxZzGCP == fGyLmxiUFD){hiSNcbRZxb = true;}
      else if(fGyLmxiUFD == ZYYPxZzGCP){qhPqVBjSKD = true;}
      if(djWXGnhTje == nimUwNAWBK){lKWYgrTerC = true;}
      else if(nimUwNAWBK == djWXGnhTje){HpCepzjiyH = true;}
      if(tgZJrGrSZk == uhQVrgkrfj){MffaKDchbG = true;}
      if(zKYQxfKJIS == irTNVmTUWS){bIOkLnAIfA = true;}
      if(nVcLhqMZlP == WDWkQyIRVW){AIlRkmTcjN = true;}
      while(uhQVrgkrfj == tgZJrGrSZk){dsIDHiGrok = true;}
      while(irTNVmTUWS == irTNVmTUWS){szwgfAiGrr = true;}
      while(WDWkQyIRVW == WDWkQyIRVW){IgqYBtFZPC = true;}
      if(GRJjTxpcSF == true){GRJjTxpcSF = false;}
      if(LpnUUuPYzI == true){LpnUUuPYzI = false;}
      if(teAimqKfFt == true){teAimqKfFt = false;}
      if(XSVIcRiisX == true){XSVIcRiisX = false;}
      if(xqBRGgOCQU == true){xqBRGgOCQU = false;}
      if(hiSNcbRZxb == true){hiSNcbRZxb = false;}
      if(lKWYgrTerC == true){lKWYgrTerC = false;}
      if(MffaKDchbG == true){MffaKDchbG = false;}
      if(bIOkLnAIfA == true){bIOkLnAIfA = false;}
      if(AIlRkmTcjN == true){AIlRkmTcjN = false;}
      if(MiJNHCDrDZ == true){MiJNHCDrDZ = false;}
      if(zixqAdulMr == true){zixqAdulMr = false;}
      if(rLzqCEtNoX == true){rLzqCEtNoX = false;}
      if(izyOsrzBcJ == true){izyOsrzBcJ = false;}
      if(jIEGBRKuRH == true){jIEGBRKuRH = false;}
      if(qhPqVBjSKD == true){qhPqVBjSKD = false;}
      if(HpCepzjiyH == true){HpCepzjiyH = false;}
      if(dsIDHiGrok == true){dsIDHiGrok = false;}
      if(szwgfAiGrr == true){szwgfAiGrr = false;}
      if(IgqYBtFZPC == true){IgqYBtFZPC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQOOEIGOBC
{ 
  void QVgWbMRfUp()
  { 
      bool nsTNxVdtZs = false;
      bool mUlpspdThT = false;
      bool NIZEyjabrN = false;
      bool fddpoeADEr = false;
      bool JFNYzeksuB = false;
      bool RxYxOfSPOM = false;
      bool uCBLNJpwAN = false;
      bool paOpJHtAFT = false;
      bool zggqwiFgbJ = false;
      bool LknrwHDCLp = false;
      bool norgKqhimG = false;
      bool kSJuMOUKPe = false;
      bool DITqBFlWsC = false;
      bool EqoPeKnzfE = false;
      bool AVtVXsaseh = false;
      bool lrmflfUBeF = false;
      bool FKpkCtdtPC = false;
      bool ZUeKdhOyTI = false;
      bool drrKPLEIdz = false;
      bool omUZzpfISd = false;
      string ghcUhIbLQG;
      string aWmFtQwtFf;
      string UtHwlSlfGi;
      string qggESdTzoK;
      string pUzzQHSywY;
      string nbUiolagiO;
      string WwEhPsoimQ;
      string xwEtozuHfd;
      string AmihtOLyOf;
      string DmQantQRjW;
      string RjLfbqXasp;
      string qSBEOiMVmA;
      string gqTHMJfcFu;
      string hdWIMPbCFD;
      string pkFYojkLME;
      string gtdioZPESR;
      string KtUxHMwrqy;
      string HKPjJwluRc;
      string YUQBOnzmSm;
      string zWinruQHQb;
      if(ghcUhIbLQG == RjLfbqXasp){nsTNxVdtZs = true;}
      else if(RjLfbqXasp == ghcUhIbLQG){norgKqhimG = true;}
      if(aWmFtQwtFf == qSBEOiMVmA){mUlpspdThT = true;}
      else if(qSBEOiMVmA == aWmFtQwtFf){kSJuMOUKPe = true;}
      if(UtHwlSlfGi == gqTHMJfcFu){NIZEyjabrN = true;}
      else if(gqTHMJfcFu == UtHwlSlfGi){DITqBFlWsC = true;}
      if(qggESdTzoK == hdWIMPbCFD){fddpoeADEr = true;}
      else if(hdWIMPbCFD == qggESdTzoK){EqoPeKnzfE = true;}
      if(pUzzQHSywY == pkFYojkLME){JFNYzeksuB = true;}
      else if(pkFYojkLME == pUzzQHSywY){AVtVXsaseh = true;}
      if(nbUiolagiO == gtdioZPESR){RxYxOfSPOM = true;}
      else if(gtdioZPESR == nbUiolagiO){lrmflfUBeF = true;}
      if(WwEhPsoimQ == KtUxHMwrqy){uCBLNJpwAN = true;}
      else if(KtUxHMwrqy == WwEhPsoimQ){FKpkCtdtPC = true;}
      if(xwEtozuHfd == HKPjJwluRc){paOpJHtAFT = true;}
      if(AmihtOLyOf == YUQBOnzmSm){zggqwiFgbJ = true;}
      if(DmQantQRjW == zWinruQHQb){LknrwHDCLp = true;}
      while(HKPjJwluRc == xwEtozuHfd){ZUeKdhOyTI = true;}
      while(YUQBOnzmSm == YUQBOnzmSm){drrKPLEIdz = true;}
      while(zWinruQHQb == zWinruQHQb){omUZzpfISd = true;}
      if(nsTNxVdtZs == true){nsTNxVdtZs = false;}
      if(mUlpspdThT == true){mUlpspdThT = false;}
      if(NIZEyjabrN == true){NIZEyjabrN = false;}
      if(fddpoeADEr == true){fddpoeADEr = false;}
      if(JFNYzeksuB == true){JFNYzeksuB = false;}
      if(RxYxOfSPOM == true){RxYxOfSPOM = false;}
      if(uCBLNJpwAN == true){uCBLNJpwAN = false;}
      if(paOpJHtAFT == true){paOpJHtAFT = false;}
      if(zggqwiFgbJ == true){zggqwiFgbJ = false;}
      if(LknrwHDCLp == true){LknrwHDCLp = false;}
      if(norgKqhimG == true){norgKqhimG = false;}
      if(kSJuMOUKPe == true){kSJuMOUKPe = false;}
      if(DITqBFlWsC == true){DITqBFlWsC = false;}
      if(EqoPeKnzfE == true){EqoPeKnzfE = false;}
      if(AVtVXsaseh == true){AVtVXsaseh = false;}
      if(lrmflfUBeF == true){lrmflfUBeF = false;}
      if(FKpkCtdtPC == true){FKpkCtdtPC = false;}
      if(ZUeKdhOyTI == true){ZUeKdhOyTI = false;}
      if(drrKPLEIdz == true){drrKPLEIdz = false;}
      if(omUZzpfISd == true){omUZzpfISd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNAWQYDCTB
{ 
  void gbEQKxolzh()
  { 
      bool bVqKlgsuUV = false;
      bool ADBHWQJSrc = false;
      bool mYBbPFSbjr = false;
      bool IZOFfXjCNY = false;
      bool CqnYrmwVwX = false;
      bool KhbBXCUOtg = false;
      bool NQKbMZouby = false;
      bool gGFSZujbib = false;
      bool IxeMhayNgc = false;
      bool DVIgKlgMMS = false;
      bool yAsxqDcIac = false;
      bool SreSXQkysl = false;
      bool bbOzuKyXIn = false;
      bool OXPQdHDhVd = false;
      bool yolEKKpoJt = false;
      bool AiSZpWlsBf = false;
      bool FEAmNtbOoP = false;
      bool NDbOmmoJoj = false;
      bool UIONnfEoaG = false;
      bool VJfpXtoypP = false;
      string qBwWLchmec;
      string kGgzkyjeLt;
      string LdDrSiYOuI;
      string ihpXehtZnM;
      string oJxcKWCnkh;
      string rqGnLMyEDb;
      string DTqWtDPITC;
      string DKpyFCgZgu;
      string gjcNPqaCMR;
      string jpVLIURZiH;
      string HsTidhBHiI;
      string fYWIuTqdGC;
      string bNwCSNodoj;
      string jGpZmnPtih;
      string pSSDkKTMQo;
      string dnTgetwRPQ;
      string sWSyYZixUG;
      string DxtYMJtsQH;
      string tbNzGwlJus;
      string qxdSnTAUdL;
      if(qBwWLchmec == HsTidhBHiI){bVqKlgsuUV = true;}
      else if(HsTidhBHiI == qBwWLchmec){yAsxqDcIac = true;}
      if(kGgzkyjeLt == fYWIuTqdGC){ADBHWQJSrc = true;}
      else if(fYWIuTqdGC == kGgzkyjeLt){SreSXQkysl = true;}
      if(LdDrSiYOuI == bNwCSNodoj){mYBbPFSbjr = true;}
      else if(bNwCSNodoj == LdDrSiYOuI){bbOzuKyXIn = true;}
      if(ihpXehtZnM == jGpZmnPtih){IZOFfXjCNY = true;}
      else if(jGpZmnPtih == ihpXehtZnM){OXPQdHDhVd = true;}
      if(oJxcKWCnkh == pSSDkKTMQo){CqnYrmwVwX = true;}
      else if(pSSDkKTMQo == oJxcKWCnkh){yolEKKpoJt = true;}
      if(rqGnLMyEDb == dnTgetwRPQ){KhbBXCUOtg = true;}
      else if(dnTgetwRPQ == rqGnLMyEDb){AiSZpWlsBf = true;}
      if(DTqWtDPITC == sWSyYZixUG){NQKbMZouby = true;}
      else if(sWSyYZixUG == DTqWtDPITC){FEAmNtbOoP = true;}
      if(DKpyFCgZgu == DxtYMJtsQH){gGFSZujbib = true;}
      if(gjcNPqaCMR == tbNzGwlJus){IxeMhayNgc = true;}
      if(jpVLIURZiH == qxdSnTAUdL){DVIgKlgMMS = true;}
      while(DxtYMJtsQH == DKpyFCgZgu){NDbOmmoJoj = true;}
      while(tbNzGwlJus == tbNzGwlJus){UIONnfEoaG = true;}
      while(qxdSnTAUdL == qxdSnTAUdL){VJfpXtoypP = true;}
      if(bVqKlgsuUV == true){bVqKlgsuUV = false;}
      if(ADBHWQJSrc == true){ADBHWQJSrc = false;}
      if(mYBbPFSbjr == true){mYBbPFSbjr = false;}
      if(IZOFfXjCNY == true){IZOFfXjCNY = false;}
      if(CqnYrmwVwX == true){CqnYrmwVwX = false;}
      if(KhbBXCUOtg == true){KhbBXCUOtg = false;}
      if(NQKbMZouby == true){NQKbMZouby = false;}
      if(gGFSZujbib == true){gGFSZujbib = false;}
      if(IxeMhayNgc == true){IxeMhayNgc = false;}
      if(DVIgKlgMMS == true){DVIgKlgMMS = false;}
      if(yAsxqDcIac == true){yAsxqDcIac = false;}
      if(SreSXQkysl == true){SreSXQkysl = false;}
      if(bbOzuKyXIn == true){bbOzuKyXIn = false;}
      if(OXPQdHDhVd == true){OXPQdHDhVd = false;}
      if(yolEKKpoJt == true){yolEKKpoJt = false;}
      if(AiSZpWlsBf == true){AiSZpWlsBf = false;}
      if(FEAmNtbOoP == true){FEAmNtbOoP = false;}
      if(NDbOmmoJoj == true){NDbOmmoJoj = false;}
      if(UIONnfEoaG == true){UIONnfEoaG = false;}
      if(VJfpXtoypP == true){VJfpXtoypP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUZXKHAGOC
{ 
  void qGjadnYTsp()
  { 
      bool inmesXIbTS = false;
      bool RNgEAiOQDp = false;
      bool neLCHGVYaX = false;
      bool zYMpozbtPa = false;
      bool hpBouMquVF = false;
      bool KOCCwDcjXl = false;
      bool BjAuSsBpPB = false;
      bool HTAbHxdVHt = false;
      bool OaCUNjVJtk = false;
      bool WqWcZyoGWB = false;
      bool LBeUypOZuy = false;
      bool ZGccXZhfhh = false;
      bool WqudeQxXCI = false;
      bool IWzFiNugWW = false;
      bool VwOwLPNsFz = false;
      bool PJXoeTFBpg = false;
      bool rqWloCHXtK = false;
      bool eBIKLZczRO = false;
      bool DERDszyKZO = false;
      bool ItqodeYbGJ = false;
      string YLmlxNiJMI;
      string jbXrOWhuTg;
      string WFDXVZwaGH;
      string DlioXguqOB;
      string xOAkhbgqQL;
      string FKYelTIOQW;
      string QHCFFyriTg;
      string bqgRiIESps;
      string sEKuBrMEDE;
      string YfZrkpLuej;
      string jyXijOdGud;
      string OoYXcMwHDM;
      string kmePHuQngr;
      string wJnFItgaLm;
      string OFIZojHCOY;
      string sEqRywTHbn;
      string yoZCgFBSOi;
      string eVuPyfeFaX;
      string mOZIzqRVHM;
      string aYzWoZfFrj;
      if(YLmlxNiJMI == jyXijOdGud){inmesXIbTS = true;}
      else if(jyXijOdGud == YLmlxNiJMI){LBeUypOZuy = true;}
      if(jbXrOWhuTg == OoYXcMwHDM){RNgEAiOQDp = true;}
      else if(OoYXcMwHDM == jbXrOWhuTg){ZGccXZhfhh = true;}
      if(WFDXVZwaGH == kmePHuQngr){neLCHGVYaX = true;}
      else if(kmePHuQngr == WFDXVZwaGH){WqudeQxXCI = true;}
      if(DlioXguqOB == wJnFItgaLm){zYMpozbtPa = true;}
      else if(wJnFItgaLm == DlioXguqOB){IWzFiNugWW = true;}
      if(xOAkhbgqQL == OFIZojHCOY){hpBouMquVF = true;}
      else if(OFIZojHCOY == xOAkhbgqQL){VwOwLPNsFz = true;}
      if(FKYelTIOQW == sEqRywTHbn){KOCCwDcjXl = true;}
      else if(sEqRywTHbn == FKYelTIOQW){PJXoeTFBpg = true;}
      if(QHCFFyriTg == yoZCgFBSOi){BjAuSsBpPB = true;}
      else if(yoZCgFBSOi == QHCFFyriTg){rqWloCHXtK = true;}
      if(bqgRiIESps == eVuPyfeFaX){HTAbHxdVHt = true;}
      if(sEKuBrMEDE == mOZIzqRVHM){OaCUNjVJtk = true;}
      if(YfZrkpLuej == aYzWoZfFrj){WqWcZyoGWB = true;}
      while(eVuPyfeFaX == bqgRiIESps){eBIKLZczRO = true;}
      while(mOZIzqRVHM == mOZIzqRVHM){DERDszyKZO = true;}
      while(aYzWoZfFrj == aYzWoZfFrj){ItqodeYbGJ = true;}
      if(inmesXIbTS == true){inmesXIbTS = false;}
      if(RNgEAiOQDp == true){RNgEAiOQDp = false;}
      if(neLCHGVYaX == true){neLCHGVYaX = false;}
      if(zYMpozbtPa == true){zYMpozbtPa = false;}
      if(hpBouMquVF == true){hpBouMquVF = false;}
      if(KOCCwDcjXl == true){KOCCwDcjXl = false;}
      if(BjAuSsBpPB == true){BjAuSsBpPB = false;}
      if(HTAbHxdVHt == true){HTAbHxdVHt = false;}
      if(OaCUNjVJtk == true){OaCUNjVJtk = false;}
      if(WqWcZyoGWB == true){WqWcZyoGWB = false;}
      if(LBeUypOZuy == true){LBeUypOZuy = false;}
      if(ZGccXZhfhh == true){ZGccXZhfhh = false;}
      if(WqudeQxXCI == true){WqudeQxXCI = false;}
      if(IWzFiNugWW == true){IWzFiNugWW = false;}
      if(VwOwLPNsFz == true){VwOwLPNsFz = false;}
      if(PJXoeTFBpg == true){PJXoeTFBpg = false;}
      if(rqWloCHXtK == true){rqWloCHXtK = false;}
      if(eBIKLZczRO == true){eBIKLZczRO = false;}
      if(DERDszyKZO == true){DERDszyKZO = false;}
      if(ItqodeYbGJ == true){ItqodeYbGJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJPXBNMCAH
{ 
  void cgGKVojzRa()
  { 
      bool iSGVPuhwqL = false;
      bool phYxBNByft = false;
      bool PyzcdtjZiF = false;
      bool nJELHeqBdh = false;
      bool zSpqnDqkyg = false;
      bool XonLOjScqV = false;
      bool KINkWgdMoV = false;
      bool VzUyuxIHoa = false;
      bool CzaBhyUrxW = false;
      bool LOKIWpFETH = false;
      bool YducLYUpQQ = false;
      bool bLnPSLgLDY = false;
      bool LlORJHoMaE = false;
      bool rDngBXDypI = false;
      bool deafuAZtoL = false;
      bool JtAuwmOdSD = false;
      bool jHOMYXWGNu = false;
      bool HiUutgKhWI = false;
      bool guXPtyDskO = false;
      bool IZemXVQNHW = false;
      string LIQPuXQtJO;
      string pHWisShZjA;
      string kkSlknmMHp;
      string DnWgEopzlA;
      string GRgMzLZsxs;
      string IWusiZpeeH;
      string jDlTLBkodE;
      string chnisTEFmY;
      string NtOOggrcxe;
      string yLUePCeNBx;
      string ajOsQZhLzP;
      string VjqFspoXld;
      string JHrzFRNJTp;
      string npEpycfVyH;
      string ygdhJOTOkZ;
      string NHaWnTrOmy;
      string MYrIaefBHP;
      string KSYdfbdKpp;
      string xyXscgPgCd;
      string kQhzuZnUGd;
      if(LIQPuXQtJO == ajOsQZhLzP){iSGVPuhwqL = true;}
      else if(ajOsQZhLzP == LIQPuXQtJO){YducLYUpQQ = true;}
      if(pHWisShZjA == VjqFspoXld){phYxBNByft = true;}
      else if(VjqFspoXld == pHWisShZjA){bLnPSLgLDY = true;}
      if(kkSlknmMHp == JHrzFRNJTp){PyzcdtjZiF = true;}
      else if(JHrzFRNJTp == kkSlknmMHp){LlORJHoMaE = true;}
      if(DnWgEopzlA == npEpycfVyH){nJELHeqBdh = true;}
      else if(npEpycfVyH == DnWgEopzlA){rDngBXDypI = true;}
      if(GRgMzLZsxs == ygdhJOTOkZ){zSpqnDqkyg = true;}
      else if(ygdhJOTOkZ == GRgMzLZsxs){deafuAZtoL = true;}
      if(IWusiZpeeH == NHaWnTrOmy){XonLOjScqV = true;}
      else if(NHaWnTrOmy == IWusiZpeeH){JtAuwmOdSD = true;}
      if(jDlTLBkodE == MYrIaefBHP){KINkWgdMoV = true;}
      else if(MYrIaefBHP == jDlTLBkodE){jHOMYXWGNu = true;}
      if(chnisTEFmY == KSYdfbdKpp){VzUyuxIHoa = true;}
      if(NtOOggrcxe == xyXscgPgCd){CzaBhyUrxW = true;}
      if(yLUePCeNBx == kQhzuZnUGd){LOKIWpFETH = true;}
      while(KSYdfbdKpp == chnisTEFmY){HiUutgKhWI = true;}
      while(xyXscgPgCd == xyXscgPgCd){guXPtyDskO = true;}
      while(kQhzuZnUGd == kQhzuZnUGd){IZemXVQNHW = true;}
      if(iSGVPuhwqL == true){iSGVPuhwqL = false;}
      if(phYxBNByft == true){phYxBNByft = false;}
      if(PyzcdtjZiF == true){PyzcdtjZiF = false;}
      if(nJELHeqBdh == true){nJELHeqBdh = false;}
      if(zSpqnDqkyg == true){zSpqnDqkyg = false;}
      if(XonLOjScqV == true){XonLOjScqV = false;}
      if(KINkWgdMoV == true){KINkWgdMoV = false;}
      if(VzUyuxIHoa == true){VzUyuxIHoa = false;}
      if(CzaBhyUrxW == true){CzaBhyUrxW = false;}
      if(LOKIWpFETH == true){LOKIWpFETH = false;}
      if(YducLYUpQQ == true){YducLYUpQQ = false;}
      if(bLnPSLgLDY == true){bLnPSLgLDY = false;}
      if(LlORJHoMaE == true){LlORJHoMaE = false;}
      if(rDngBXDypI == true){rDngBXDypI = false;}
      if(deafuAZtoL == true){deafuAZtoL = false;}
      if(JtAuwmOdSD == true){JtAuwmOdSD = false;}
      if(jHOMYXWGNu == true){jHOMYXWGNu = false;}
      if(HiUutgKhWI == true){HiUutgKhWI = false;}
      if(guXPtyDskO == true){guXPtyDskO = false;}
      if(IZemXVQNHW == true){IZemXVQNHW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMKRACLWYU
{ 
  void oOCJFcfcFR()
  { 
      bool dOFHxoWeks = false;
      bool DlpXHnkdTF = false;
      bool wYINcZsclB = false;
      bool NPLAYYfGpV = false;
      bool yJKQbbNcTT = false;
      bool MBdzEEGreW = false;
      bool wtrifnaoyh = false;
      bool HdmyHmOqkB = false;
      bool LQISoMkLwU = false;
      bool SnbSZEQakn = false;
      bool AYdlLhNfrR = false;
      bool oOGdLekZtT = false;
      bool COscPTBUXD = false;
      bool VmGxAmlWGG = false;
      bool yFSdeDhyHt = false;
      bool SqgQkkeAWr = false;
      bool gsHowCIIcX = false;
      bool sNSnUwuPyM = false;
      bool lDMdjdGoLO = false;
      bool IkAOZFydhc = false;
      string hWERxgSptD;
      string lgdQZFUGSm;
      string VYFPRUeoZd;
      string uVicrUlrkD;
      string kUOpqIBDik;
      string miudYIRnAb;
      string BcQQIPxAXF;
      string TbVPCBKOYI;
      string SaGnqLaFDj;
      string CxqIBHDxhb;
      string KAedRKNeaX;
      string xCPrJZWbZx;
      string orxnCVkNOu;
      string xMgxyRubWg;
      string xudflzhzya;
      string jbXklRDqau;
      string YzQfakVSsq;
      string dtEszsOQBD;
      string nkOmLUnwKf;
      string OEBaHxeyFB;
      if(hWERxgSptD == KAedRKNeaX){dOFHxoWeks = true;}
      else if(KAedRKNeaX == hWERxgSptD){AYdlLhNfrR = true;}
      if(lgdQZFUGSm == xCPrJZWbZx){DlpXHnkdTF = true;}
      else if(xCPrJZWbZx == lgdQZFUGSm){oOGdLekZtT = true;}
      if(VYFPRUeoZd == orxnCVkNOu){wYINcZsclB = true;}
      else if(orxnCVkNOu == VYFPRUeoZd){COscPTBUXD = true;}
      if(uVicrUlrkD == xMgxyRubWg){NPLAYYfGpV = true;}
      else if(xMgxyRubWg == uVicrUlrkD){VmGxAmlWGG = true;}
      if(kUOpqIBDik == xudflzhzya){yJKQbbNcTT = true;}
      else if(xudflzhzya == kUOpqIBDik){yFSdeDhyHt = true;}
      if(miudYIRnAb == jbXklRDqau){MBdzEEGreW = true;}
      else if(jbXklRDqau == miudYIRnAb){SqgQkkeAWr = true;}
      if(BcQQIPxAXF == YzQfakVSsq){wtrifnaoyh = true;}
      else if(YzQfakVSsq == BcQQIPxAXF){gsHowCIIcX = true;}
      if(TbVPCBKOYI == dtEszsOQBD){HdmyHmOqkB = true;}
      if(SaGnqLaFDj == nkOmLUnwKf){LQISoMkLwU = true;}
      if(CxqIBHDxhb == OEBaHxeyFB){SnbSZEQakn = true;}
      while(dtEszsOQBD == TbVPCBKOYI){sNSnUwuPyM = true;}
      while(nkOmLUnwKf == nkOmLUnwKf){lDMdjdGoLO = true;}
      while(OEBaHxeyFB == OEBaHxeyFB){IkAOZFydhc = true;}
      if(dOFHxoWeks == true){dOFHxoWeks = false;}
      if(DlpXHnkdTF == true){DlpXHnkdTF = false;}
      if(wYINcZsclB == true){wYINcZsclB = false;}
      if(NPLAYYfGpV == true){NPLAYYfGpV = false;}
      if(yJKQbbNcTT == true){yJKQbbNcTT = false;}
      if(MBdzEEGreW == true){MBdzEEGreW = false;}
      if(wtrifnaoyh == true){wtrifnaoyh = false;}
      if(HdmyHmOqkB == true){HdmyHmOqkB = false;}
      if(LQISoMkLwU == true){LQISoMkLwU = false;}
      if(SnbSZEQakn == true){SnbSZEQakn = false;}
      if(AYdlLhNfrR == true){AYdlLhNfrR = false;}
      if(oOGdLekZtT == true){oOGdLekZtT = false;}
      if(COscPTBUXD == true){COscPTBUXD = false;}
      if(VmGxAmlWGG == true){VmGxAmlWGG = false;}
      if(yFSdeDhyHt == true){yFSdeDhyHt = false;}
      if(SqgQkkeAWr == true){SqgQkkeAWr = false;}
      if(gsHowCIIcX == true){gsHowCIIcX = false;}
      if(sNSnUwuPyM == true){sNSnUwuPyM = false;}
      if(lDMdjdGoLO == true){lDMdjdGoLO = false;}
      if(IkAOZFydhc == true){IkAOZFydhc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQHKJFBDVZ
{ 
  void qLVToocmyn()
  { 
      bool FMkdDkGjBD = false;
      bool SBrYOoDuPq = false;
      bool WMyDlWzmui = false;
      bool bpsLOVjdQH = false;
      bool YhlXXBNKQA = false;
      bool ObrjVsNhrf = false;
      bool kSoRbbHfKs = false;
      bool FZdHSnZaek = false;
      bool JoVtUzxJpU = false;
      bool HCkkVFsUuu = false;
      bool sgzWunyjQg = false;
      bool TmCHVwwtxb = false;
      bool exoolCnrkN = false;
      bool uEeiqboyzf = false;
      bool ANsJBTzdPZ = false;
      bool IyXTQuqKkr = false;
      bool zFyDkOHSPs = false;
      bool GxuQbREfnR = false;
      bool DKcLExgLRw = false;
      bool jeNGftOoYm = false;
      string IjKYUfpPAR;
      string XFLTpQPTwd;
      string lpOrcsNjXF;
      string RiCVZSHeJg;
      string kMzlblebpb;
      string uxfOyRUSub;
      string SFrtAnDosX;
      string JjJPrYqcPq;
      string NktuKTDmWH;
      string ynjgNeUEkm;
      string hohRSKnQVZ;
      string arCDNgKwjg;
      string kPSkZUAbBM;
      string DlqcJYDbcz;
      string elQxgFlfTg;
      string TYUDCRWxrx;
      string JMOIVnAYto;
      string diSjCyyUET;
      string hUITseRnaq;
      string CGifoSWIar;
      if(IjKYUfpPAR == hohRSKnQVZ){FMkdDkGjBD = true;}
      else if(hohRSKnQVZ == IjKYUfpPAR){sgzWunyjQg = true;}
      if(XFLTpQPTwd == arCDNgKwjg){SBrYOoDuPq = true;}
      else if(arCDNgKwjg == XFLTpQPTwd){TmCHVwwtxb = true;}
      if(lpOrcsNjXF == kPSkZUAbBM){WMyDlWzmui = true;}
      else if(kPSkZUAbBM == lpOrcsNjXF){exoolCnrkN = true;}
      if(RiCVZSHeJg == DlqcJYDbcz){bpsLOVjdQH = true;}
      else if(DlqcJYDbcz == RiCVZSHeJg){uEeiqboyzf = true;}
      if(kMzlblebpb == elQxgFlfTg){YhlXXBNKQA = true;}
      else if(elQxgFlfTg == kMzlblebpb){ANsJBTzdPZ = true;}
      if(uxfOyRUSub == TYUDCRWxrx){ObrjVsNhrf = true;}
      else if(TYUDCRWxrx == uxfOyRUSub){IyXTQuqKkr = true;}
      if(SFrtAnDosX == JMOIVnAYto){kSoRbbHfKs = true;}
      else if(JMOIVnAYto == SFrtAnDosX){zFyDkOHSPs = true;}
      if(JjJPrYqcPq == diSjCyyUET){FZdHSnZaek = true;}
      if(NktuKTDmWH == hUITseRnaq){JoVtUzxJpU = true;}
      if(ynjgNeUEkm == CGifoSWIar){HCkkVFsUuu = true;}
      while(diSjCyyUET == JjJPrYqcPq){GxuQbREfnR = true;}
      while(hUITseRnaq == hUITseRnaq){DKcLExgLRw = true;}
      while(CGifoSWIar == CGifoSWIar){jeNGftOoYm = true;}
      if(FMkdDkGjBD == true){FMkdDkGjBD = false;}
      if(SBrYOoDuPq == true){SBrYOoDuPq = false;}
      if(WMyDlWzmui == true){WMyDlWzmui = false;}
      if(bpsLOVjdQH == true){bpsLOVjdQH = false;}
      if(YhlXXBNKQA == true){YhlXXBNKQA = false;}
      if(ObrjVsNhrf == true){ObrjVsNhrf = false;}
      if(kSoRbbHfKs == true){kSoRbbHfKs = false;}
      if(FZdHSnZaek == true){FZdHSnZaek = false;}
      if(JoVtUzxJpU == true){JoVtUzxJpU = false;}
      if(HCkkVFsUuu == true){HCkkVFsUuu = false;}
      if(sgzWunyjQg == true){sgzWunyjQg = false;}
      if(TmCHVwwtxb == true){TmCHVwwtxb = false;}
      if(exoolCnrkN == true){exoolCnrkN = false;}
      if(uEeiqboyzf == true){uEeiqboyzf = false;}
      if(ANsJBTzdPZ == true){ANsJBTzdPZ = false;}
      if(IyXTQuqKkr == true){IyXTQuqKkr = false;}
      if(zFyDkOHSPs == true){zFyDkOHSPs = false;}
      if(GxuQbREfnR == true){GxuQbREfnR = false;}
      if(DKcLExgLRw == true){DKcLExgLRw = false;}
      if(jeNGftOoYm == true){jeNGftOoYm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTLPZOPKCX
{ 
  void qVSRPjNrLd()
  { 
      bool EUUtuxhCFe = false;
      bool GsuOnmVgqw = false;
      bool uLkYdfCGNk = false;
      bool mGrnlyZZxR = false;
      bool QNmHfYfrER = false;
      bool DggJxsjuPP = false;
      bool tboUqzAGcp = false;
      bool NuiZegXcsF = false;
      bool AKCwhGYhqr = false;
      bool NdKhXnYRPf = false;
      bool XYOOEHxHdP = false;
      bool UGCKPiZrlj = false;
      bool aSPjbikBBq = false;
      bool IFNNgaunqa = false;
      bool JREbXHbzSn = false;
      bool OfffFFJelV = false;
      bool VwFmGOsodn = false;
      bool nkBLaJNmLU = false;
      bool GkiNbcZgHa = false;
      bool RQBUENLQUJ = false;
      string MhxiYoZCGL;
      string yDyzzPJMCQ;
      string PzYPgSNmjA;
      string YwkVOeSRDp;
      string QAjaYNSxXQ;
      string CJjcqNJhBG;
      string blSFmCSckT;
      string xqILAOPxpS;
      string zQPTyOMIdA;
      string UkPxOdhdnW;
      string upMDTKAXcc;
      string xMqiGLWzHX;
      string pKzjyLbLxV;
      string glITWJDMzn;
      string NneBDIsgqD;
      string HhVPgkqbFH;
      string hoaGuKEXLw;
      string HKzTJBeygp;
      string SuTsOzPrml;
      string SaHrFYNYFr;
      if(MhxiYoZCGL == upMDTKAXcc){EUUtuxhCFe = true;}
      else if(upMDTKAXcc == MhxiYoZCGL){XYOOEHxHdP = true;}
      if(yDyzzPJMCQ == xMqiGLWzHX){GsuOnmVgqw = true;}
      else if(xMqiGLWzHX == yDyzzPJMCQ){UGCKPiZrlj = true;}
      if(PzYPgSNmjA == pKzjyLbLxV){uLkYdfCGNk = true;}
      else if(pKzjyLbLxV == PzYPgSNmjA){aSPjbikBBq = true;}
      if(YwkVOeSRDp == glITWJDMzn){mGrnlyZZxR = true;}
      else if(glITWJDMzn == YwkVOeSRDp){IFNNgaunqa = true;}
      if(QAjaYNSxXQ == NneBDIsgqD){QNmHfYfrER = true;}
      else if(NneBDIsgqD == QAjaYNSxXQ){JREbXHbzSn = true;}
      if(CJjcqNJhBG == HhVPgkqbFH){DggJxsjuPP = true;}
      else if(HhVPgkqbFH == CJjcqNJhBG){OfffFFJelV = true;}
      if(blSFmCSckT == hoaGuKEXLw){tboUqzAGcp = true;}
      else if(hoaGuKEXLw == blSFmCSckT){VwFmGOsodn = true;}
      if(xqILAOPxpS == HKzTJBeygp){NuiZegXcsF = true;}
      if(zQPTyOMIdA == SuTsOzPrml){AKCwhGYhqr = true;}
      if(UkPxOdhdnW == SaHrFYNYFr){NdKhXnYRPf = true;}
      while(HKzTJBeygp == xqILAOPxpS){nkBLaJNmLU = true;}
      while(SuTsOzPrml == SuTsOzPrml){GkiNbcZgHa = true;}
      while(SaHrFYNYFr == SaHrFYNYFr){RQBUENLQUJ = true;}
      if(EUUtuxhCFe == true){EUUtuxhCFe = false;}
      if(GsuOnmVgqw == true){GsuOnmVgqw = false;}
      if(uLkYdfCGNk == true){uLkYdfCGNk = false;}
      if(mGrnlyZZxR == true){mGrnlyZZxR = false;}
      if(QNmHfYfrER == true){QNmHfYfrER = false;}
      if(DggJxsjuPP == true){DggJxsjuPP = false;}
      if(tboUqzAGcp == true){tboUqzAGcp = false;}
      if(NuiZegXcsF == true){NuiZegXcsF = false;}
      if(AKCwhGYhqr == true){AKCwhGYhqr = false;}
      if(NdKhXnYRPf == true){NdKhXnYRPf = false;}
      if(XYOOEHxHdP == true){XYOOEHxHdP = false;}
      if(UGCKPiZrlj == true){UGCKPiZrlj = false;}
      if(aSPjbikBBq == true){aSPjbikBBq = false;}
      if(IFNNgaunqa == true){IFNNgaunqa = false;}
      if(JREbXHbzSn == true){JREbXHbzSn = false;}
      if(OfffFFJelV == true){OfffFFJelV = false;}
      if(VwFmGOsodn == true){VwFmGOsodn = false;}
      if(nkBLaJNmLU == true){nkBLaJNmLU = false;}
      if(GkiNbcZgHa == true){GkiNbcZgHa = false;}
      if(RQBUENLQUJ == true){RQBUENLQUJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQFNARFNTJ
{ 
  void PqLAeTdQtt()
  { 
      bool gDDRHZtqft = false;
      bool VKaGZwGHlB = false;
      bool nBpBaiKgSs = false;
      bool COebjLzDbP = false;
      bool pJCwggirTH = false;
      bool kebtneNBpX = false;
      bool PNYmqGezWO = false;
      bool xCeVKdzsUt = false;
      bool ARNKHWlknE = false;
      bool xyMEAbkOEZ = false;
      bool CiVEKizFjJ = false;
      bool eUfwWyANfT = false;
      bool TtLRQyoaVh = false;
      bool sjnuqQwIAX = false;
      bool XgBdZcRPgC = false;
      bool bXijFIXDnL = false;
      bool sXjBPufkFG = false;
      bool BrMHwmrgrm = false;
      bool fZtSGVADoi = false;
      bool rrTndzwzNd = false;
      string AKqaSPcsil;
      string UzkewXIrdP;
      string BmCFBznTIt;
      string dxkDkKelCK;
      string ZPfeagbwqi;
      string fZsrdMHlZT;
      string aJjoIWNhtk;
      string rWpSolGWdT;
      string WrcZNDDsZX;
      string CrMhiPepVD;
      string SsCFpJjZCr;
      string FkHFwigKbE;
      string SUIWhAJHiZ;
      string GQAaBcoWjE;
      string TcqgRRjHkA;
      string iUORjykfWp;
      string zbpclokgET;
      string sJaXkocaEQ;
      string PCVipkBiqC;
      string rJzsErmOub;
      if(AKqaSPcsil == SsCFpJjZCr){gDDRHZtqft = true;}
      else if(SsCFpJjZCr == AKqaSPcsil){CiVEKizFjJ = true;}
      if(UzkewXIrdP == FkHFwigKbE){VKaGZwGHlB = true;}
      else if(FkHFwigKbE == UzkewXIrdP){eUfwWyANfT = true;}
      if(BmCFBznTIt == SUIWhAJHiZ){nBpBaiKgSs = true;}
      else if(SUIWhAJHiZ == BmCFBznTIt){TtLRQyoaVh = true;}
      if(dxkDkKelCK == GQAaBcoWjE){COebjLzDbP = true;}
      else if(GQAaBcoWjE == dxkDkKelCK){sjnuqQwIAX = true;}
      if(ZPfeagbwqi == TcqgRRjHkA){pJCwggirTH = true;}
      else if(TcqgRRjHkA == ZPfeagbwqi){XgBdZcRPgC = true;}
      if(fZsrdMHlZT == iUORjykfWp){kebtneNBpX = true;}
      else if(iUORjykfWp == fZsrdMHlZT){bXijFIXDnL = true;}
      if(aJjoIWNhtk == zbpclokgET){PNYmqGezWO = true;}
      else if(zbpclokgET == aJjoIWNhtk){sXjBPufkFG = true;}
      if(rWpSolGWdT == sJaXkocaEQ){xCeVKdzsUt = true;}
      if(WrcZNDDsZX == PCVipkBiqC){ARNKHWlknE = true;}
      if(CrMhiPepVD == rJzsErmOub){xyMEAbkOEZ = true;}
      while(sJaXkocaEQ == rWpSolGWdT){BrMHwmrgrm = true;}
      while(PCVipkBiqC == PCVipkBiqC){fZtSGVADoi = true;}
      while(rJzsErmOub == rJzsErmOub){rrTndzwzNd = true;}
      if(gDDRHZtqft == true){gDDRHZtqft = false;}
      if(VKaGZwGHlB == true){VKaGZwGHlB = false;}
      if(nBpBaiKgSs == true){nBpBaiKgSs = false;}
      if(COebjLzDbP == true){COebjLzDbP = false;}
      if(pJCwggirTH == true){pJCwggirTH = false;}
      if(kebtneNBpX == true){kebtneNBpX = false;}
      if(PNYmqGezWO == true){PNYmqGezWO = false;}
      if(xCeVKdzsUt == true){xCeVKdzsUt = false;}
      if(ARNKHWlknE == true){ARNKHWlknE = false;}
      if(xyMEAbkOEZ == true){xyMEAbkOEZ = false;}
      if(CiVEKizFjJ == true){CiVEKizFjJ = false;}
      if(eUfwWyANfT == true){eUfwWyANfT = false;}
      if(TtLRQyoaVh == true){TtLRQyoaVh = false;}
      if(sjnuqQwIAX == true){sjnuqQwIAX = false;}
      if(XgBdZcRPgC == true){XgBdZcRPgC = false;}
      if(bXijFIXDnL == true){bXijFIXDnL = false;}
      if(sXjBPufkFG == true){sXjBPufkFG = false;}
      if(BrMHwmrgrm == true){BrMHwmrgrm = false;}
      if(fZtSGVADoi == true){fZtSGVADoi = false;}
      if(rrTndzwzNd == true){rrTndzwzNd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWFJLJZNHO
{ 
  void lbTPbOyHNI()
  { 
      bool dKkoiDzIfM = false;
      bool ebgQriGaTe = false;
      bool DERQAZdyNs = false;
      bool DNgnNBVoRg = false;
      bool MdwBibKgsz = false;
      bool atVdKZrUoJ = false;
      bool YBtmIQusDq = false;
      bool NQJlRZHPhY = false;
      bool OxEORIrCcm = false;
      bool IBAIHLiJrR = false;
      bool gRdCkKkiLk = false;
      bool RclQtbxfUA = false;
      bool YrPPiMPAdG = false;
      bool pyXQqxSBcH = false;
      bool WIpqVfOjOf = false;
      bool NCnqsnBOSY = false;
      bool tkFFuTEVYw = false;
      bool IuDNcPCYtD = false;
      bool xflyrmJfWD = false;
      bool wEhDMlDjuB = false;
      string DBxNXWsrYD;
      string sbYjsXBOzq;
      string sCFMOUJwUO;
      string fwQpmUEnWF;
      string LjkWFopohY;
      string aCVBzAwkyD;
      string NwXJXxLhwY;
      string TMrseJRhHY;
      string dUOundZOqm;
      string XSoSrOLazI;
      string dIsIEOKcVo;
      string hNdZZrhbVs;
      string WwqIBAWYAQ;
      string xqhzuUbFqZ;
      string SxsBFJoPsz;
      string fjEGkhRjHE;
      string qkbErpfedE;
      string QbkwZYCoDq;
      string LHeAkMlbNN;
      string DqyligVoIO;
      if(DBxNXWsrYD == dIsIEOKcVo){dKkoiDzIfM = true;}
      else if(dIsIEOKcVo == DBxNXWsrYD){gRdCkKkiLk = true;}
      if(sbYjsXBOzq == hNdZZrhbVs){ebgQriGaTe = true;}
      else if(hNdZZrhbVs == sbYjsXBOzq){RclQtbxfUA = true;}
      if(sCFMOUJwUO == WwqIBAWYAQ){DERQAZdyNs = true;}
      else if(WwqIBAWYAQ == sCFMOUJwUO){YrPPiMPAdG = true;}
      if(fwQpmUEnWF == xqhzuUbFqZ){DNgnNBVoRg = true;}
      else if(xqhzuUbFqZ == fwQpmUEnWF){pyXQqxSBcH = true;}
      if(LjkWFopohY == SxsBFJoPsz){MdwBibKgsz = true;}
      else if(SxsBFJoPsz == LjkWFopohY){WIpqVfOjOf = true;}
      if(aCVBzAwkyD == fjEGkhRjHE){atVdKZrUoJ = true;}
      else if(fjEGkhRjHE == aCVBzAwkyD){NCnqsnBOSY = true;}
      if(NwXJXxLhwY == qkbErpfedE){YBtmIQusDq = true;}
      else if(qkbErpfedE == NwXJXxLhwY){tkFFuTEVYw = true;}
      if(TMrseJRhHY == QbkwZYCoDq){NQJlRZHPhY = true;}
      if(dUOundZOqm == LHeAkMlbNN){OxEORIrCcm = true;}
      if(XSoSrOLazI == DqyligVoIO){IBAIHLiJrR = true;}
      while(QbkwZYCoDq == TMrseJRhHY){IuDNcPCYtD = true;}
      while(LHeAkMlbNN == LHeAkMlbNN){xflyrmJfWD = true;}
      while(DqyligVoIO == DqyligVoIO){wEhDMlDjuB = true;}
      if(dKkoiDzIfM == true){dKkoiDzIfM = false;}
      if(ebgQriGaTe == true){ebgQriGaTe = false;}
      if(DERQAZdyNs == true){DERQAZdyNs = false;}
      if(DNgnNBVoRg == true){DNgnNBVoRg = false;}
      if(MdwBibKgsz == true){MdwBibKgsz = false;}
      if(atVdKZrUoJ == true){atVdKZrUoJ = false;}
      if(YBtmIQusDq == true){YBtmIQusDq = false;}
      if(NQJlRZHPhY == true){NQJlRZHPhY = false;}
      if(OxEORIrCcm == true){OxEORIrCcm = false;}
      if(IBAIHLiJrR == true){IBAIHLiJrR = false;}
      if(gRdCkKkiLk == true){gRdCkKkiLk = false;}
      if(RclQtbxfUA == true){RclQtbxfUA = false;}
      if(YrPPiMPAdG == true){YrPPiMPAdG = false;}
      if(pyXQqxSBcH == true){pyXQqxSBcH = false;}
      if(WIpqVfOjOf == true){WIpqVfOjOf = false;}
      if(NCnqsnBOSY == true){NCnqsnBOSY = false;}
      if(tkFFuTEVYw == true){tkFFuTEVYw = false;}
      if(IuDNcPCYtD == true){IuDNcPCYtD = false;}
      if(xflyrmJfWD == true){xflyrmJfWD = false;}
      if(wEhDMlDjuB == true){wEhDMlDjuB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALXMVJHXVI
{ 
  void OQnxrGSFmH()
  { 
      bool YopOQxdbdA = false;
      bool XbtbxfZaIf = false;
      bool jBTlgStGoK = false;
      bool xwWtZZNTWO = false;
      bool hCrSRTnzWD = false;
      bool gdOmJWVEgy = false;
      bool DWmSCbFABX = false;
      bool SFDtxgIBUM = false;
      bool duilcThijC = false;
      bool EJlXKKPZPp = false;
      bool OnxzjbZTob = false;
      bool OTiUUInBoi = false;
      bool sWPyTJTfil = false;
      bool RikeypxjBB = false;
      bool sNsHnjZQDC = false;
      bool WOjgwrXyfa = false;
      bool ItkCKehEWd = false;
      bool KEznofcHKi = false;
      bool iCbfPDzDiG = false;
      bool RyDZrybpxJ = false;
      string PhgjEkWMDO;
      string GOdaAUVSpI;
      string erybpcXaUh;
      string lyMGbTpWKy;
      string mDQFgFrcCi;
      string GoLVkXiEtb;
      string NwrUcICXzf;
      string ezIqVbbsuj;
      string jtXkbwmqUD;
      string klbikqLubY;
      string CUdVEHgTzI;
      string uoJJqSXGsg;
      string VKCuurWYFe;
      string QgRVgOQCfU;
      string OSqLIwcSqS;
      string SEBuDrShaM;
      string jHNUrOXmbc;
      string BVaYRCTpmy;
      string OEhmLMeVSo;
      string wiaTjGEWTs;
      if(PhgjEkWMDO == CUdVEHgTzI){YopOQxdbdA = true;}
      else if(CUdVEHgTzI == PhgjEkWMDO){OnxzjbZTob = true;}
      if(GOdaAUVSpI == uoJJqSXGsg){XbtbxfZaIf = true;}
      else if(uoJJqSXGsg == GOdaAUVSpI){OTiUUInBoi = true;}
      if(erybpcXaUh == VKCuurWYFe){jBTlgStGoK = true;}
      else if(VKCuurWYFe == erybpcXaUh){sWPyTJTfil = true;}
      if(lyMGbTpWKy == QgRVgOQCfU){xwWtZZNTWO = true;}
      else if(QgRVgOQCfU == lyMGbTpWKy){RikeypxjBB = true;}
      if(mDQFgFrcCi == OSqLIwcSqS){hCrSRTnzWD = true;}
      else if(OSqLIwcSqS == mDQFgFrcCi){sNsHnjZQDC = true;}
      if(GoLVkXiEtb == SEBuDrShaM){gdOmJWVEgy = true;}
      else if(SEBuDrShaM == GoLVkXiEtb){WOjgwrXyfa = true;}
      if(NwrUcICXzf == jHNUrOXmbc){DWmSCbFABX = true;}
      else if(jHNUrOXmbc == NwrUcICXzf){ItkCKehEWd = true;}
      if(ezIqVbbsuj == BVaYRCTpmy){SFDtxgIBUM = true;}
      if(jtXkbwmqUD == OEhmLMeVSo){duilcThijC = true;}
      if(klbikqLubY == wiaTjGEWTs){EJlXKKPZPp = true;}
      while(BVaYRCTpmy == ezIqVbbsuj){KEznofcHKi = true;}
      while(OEhmLMeVSo == OEhmLMeVSo){iCbfPDzDiG = true;}
      while(wiaTjGEWTs == wiaTjGEWTs){RyDZrybpxJ = true;}
      if(YopOQxdbdA == true){YopOQxdbdA = false;}
      if(XbtbxfZaIf == true){XbtbxfZaIf = false;}
      if(jBTlgStGoK == true){jBTlgStGoK = false;}
      if(xwWtZZNTWO == true){xwWtZZNTWO = false;}
      if(hCrSRTnzWD == true){hCrSRTnzWD = false;}
      if(gdOmJWVEgy == true){gdOmJWVEgy = false;}
      if(DWmSCbFABX == true){DWmSCbFABX = false;}
      if(SFDtxgIBUM == true){SFDtxgIBUM = false;}
      if(duilcThijC == true){duilcThijC = false;}
      if(EJlXKKPZPp == true){EJlXKKPZPp = false;}
      if(OnxzjbZTob == true){OnxzjbZTob = false;}
      if(OTiUUInBoi == true){OTiUUInBoi = false;}
      if(sWPyTJTfil == true){sWPyTJTfil = false;}
      if(RikeypxjBB == true){RikeypxjBB = false;}
      if(sNsHnjZQDC == true){sNsHnjZQDC = false;}
      if(WOjgwrXyfa == true){WOjgwrXyfa = false;}
      if(ItkCKehEWd == true){ItkCKehEWd = false;}
      if(KEznofcHKi == true){KEznofcHKi = false;}
      if(iCbfPDzDiG == true){iCbfPDzDiG = false;}
      if(RyDZrybpxJ == true){RyDZrybpxJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYLDKNJGKM
{ 
  void ULDfYcSNhn()
  { 
      bool WVQYgjliDq = false;
      bool tIZTIpouBP = false;
      bool utbgioJosd = false;
      bool KAywFkePaA = false;
      bool xwpLeixkFA = false;
      bool QZtzJctior = false;
      bool axoZfsJdNX = false;
      bool KZTASyDPCz = false;
      bool rXisNkGylb = false;
      bool puZiZAGPek = false;
      bool ZTXhopFsgL = false;
      bool YegozCNwMu = false;
      bool mKqkgOzkaS = false;
      bool qnjQZXABDW = false;
      bool eNRaCLNkiW = false;
      bool lKCjyOblBZ = false;
      bool qURNTkuQOa = false;
      bool CMrpPZsQhV = false;
      bool ANBDffkzSL = false;
      bool wNAdeKuDGR = false;
      string FZjyzUtjuQ;
      string bIorMnOedN;
      string ODPVppBruB;
      string xqYSGqWBAX;
      string PNZaPFYtGq;
      string SwLTbCKNHI;
      string SBntTkjWkU;
      string RMeGxAcoGk;
      string RHlEhAeEqE;
      string gIsqENZeGd;
      string VCIkYFRFVa;
      string YVHVqLPiMS;
      string GeegnITnBi;
      string ayhbPPyBec;
      string iYhQeLBWAs;
      string ypSnXpWbwQ;
      string lcDmAZneGb;
      string MNEjjgwOBc;
      string HwnIkjetDY;
      string rWEOpFVuPF;
      if(FZjyzUtjuQ == VCIkYFRFVa){WVQYgjliDq = true;}
      else if(VCIkYFRFVa == FZjyzUtjuQ){ZTXhopFsgL = true;}
      if(bIorMnOedN == YVHVqLPiMS){tIZTIpouBP = true;}
      else if(YVHVqLPiMS == bIorMnOedN){YegozCNwMu = true;}
      if(ODPVppBruB == GeegnITnBi){utbgioJosd = true;}
      else if(GeegnITnBi == ODPVppBruB){mKqkgOzkaS = true;}
      if(xqYSGqWBAX == ayhbPPyBec){KAywFkePaA = true;}
      else if(ayhbPPyBec == xqYSGqWBAX){qnjQZXABDW = true;}
      if(PNZaPFYtGq == iYhQeLBWAs){xwpLeixkFA = true;}
      else if(iYhQeLBWAs == PNZaPFYtGq){eNRaCLNkiW = true;}
      if(SwLTbCKNHI == ypSnXpWbwQ){QZtzJctior = true;}
      else if(ypSnXpWbwQ == SwLTbCKNHI){lKCjyOblBZ = true;}
      if(SBntTkjWkU == lcDmAZneGb){axoZfsJdNX = true;}
      else if(lcDmAZneGb == SBntTkjWkU){qURNTkuQOa = true;}
      if(RMeGxAcoGk == MNEjjgwOBc){KZTASyDPCz = true;}
      if(RHlEhAeEqE == HwnIkjetDY){rXisNkGylb = true;}
      if(gIsqENZeGd == rWEOpFVuPF){puZiZAGPek = true;}
      while(MNEjjgwOBc == RMeGxAcoGk){CMrpPZsQhV = true;}
      while(HwnIkjetDY == HwnIkjetDY){ANBDffkzSL = true;}
      while(rWEOpFVuPF == rWEOpFVuPF){wNAdeKuDGR = true;}
      if(WVQYgjliDq == true){WVQYgjliDq = false;}
      if(tIZTIpouBP == true){tIZTIpouBP = false;}
      if(utbgioJosd == true){utbgioJosd = false;}
      if(KAywFkePaA == true){KAywFkePaA = false;}
      if(xwpLeixkFA == true){xwpLeixkFA = false;}
      if(QZtzJctior == true){QZtzJctior = false;}
      if(axoZfsJdNX == true){axoZfsJdNX = false;}
      if(KZTASyDPCz == true){KZTASyDPCz = false;}
      if(rXisNkGylb == true){rXisNkGylb = false;}
      if(puZiZAGPek == true){puZiZAGPek = false;}
      if(ZTXhopFsgL == true){ZTXhopFsgL = false;}
      if(YegozCNwMu == true){YegozCNwMu = false;}
      if(mKqkgOzkaS == true){mKqkgOzkaS = false;}
      if(qnjQZXABDW == true){qnjQZXABDW = false;}
      if(eNRaCLNkiW == true){eNRaCLNkiW = false;}
      if(lKCjyOblBZ == true){lKCjyOblBZ = false;}
      if(qURNTkuQOa == true){qURNTkuQOa = false;}
      if(CMrpPZsQhV == true){CMrpPZsQhV = false;}
      if(ANBDffkzSL == true){ANBDffkzSL = false;}
      if(wNAdeKuDGR == true){wNAdeKuDGR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQKBEHTWMD
{ 
  void iixeiZxAQg()
  { 
      bool DVAbhfHGyA = false;
      bool rCgyBjLwaJ = false;
      bool UftyDZLMoj = false;
      bool CcZEPnnyjE = false;
      bool PrCCoLCNQE = false;
      bool VnkpTWbCYI = false;
      bool UuRNxOcchN = false;
      bool uNLWtbdrIq = false;
      bool WxwjNOqikr = false;
      bool MlZbiTZnEZ = false;
      bool iZeCIIbOwq = false;
      bool sisgkWzgAi = false;
      bool XsrpAJnjmZ = false;
      bool BonhIxSsbF = false;
      bool lbmsydrrpM = false;
      bool UsnUCohoCz = false;
      bool UqaVoEuLXn = false;
      bool DGFuwuGyqW = false;
      bool QutaFIASfT = false;
      bool PdqbjtAQDt = false;
      string PGNtcjCTBO;
      string nAxrpuZJts;
      string ZwlHprbEry;
      string BZOReDLenV;
      string BVgQpfPoGY;
      string obzqtSUFEk;
      string IxaCMOkeMl;
      string juVYqDOVRJ;
      string bmxSJZaXXL;
      string iGZCNDteDb;
      string ujbUotFZzp;
      string DymtIUAIsm;
      string mNHBDcUTKn;
      string JjRpOqKcdO;
      string TAXgHjSfsr;
      string DlkQngcaQL;
      string ZlPLgTgxeR;
      string JWddSmoZsS;
      string KoZSjWzACg;
      string OjLRohkMAn;
      if(PGNtcjCTBO == ujbUotFZzp){DVAbhfHGyA = true;}
      else if(ujbUotFZzp == PGNtcjCTBO){iZeCIIbOwq = true;}
      if(nAxrpuZJts == DymtIUAIsm){rCgyBjLwaJ = true;}
      else if(DymtIUAIsm == nAxrpuZJts){sisgkWzgAi = true;}
      if(ZwlHprbEry == mNHBDcUTKn){UftyDZLMoj = true;}
      else if(mNHBDcUTKn == ZwlHprbEry){XsrpAJnjmZ = true;}
      if(BZOReDLenV == JjRpOqKcdO){CcZEPnnyjE = true;}
      else if(JjRpOqKcdO == BZOReDLenV){BonhIxSsbF = true;}
      if(BVgQpfPoGY == TAXgHjSfsr){PrCCoLCNQE = true;}
      else if(TAXgHjSfsr == BVgQpfPoGY){lbmsydrrpM = true;}
      if(obzqtSUFEk == DlkQngcaQL){VnkpTWbCYI = true;}
      else if(DlkQngcaQL == obzqtSUFEk){UsnUCohoCz = true;}
      if(IxaCMOkeMl == ZlPLgTgxeR){UuRNxOcchN = true;}
      else if(ZlPLgTgxeR == IxaCMOkeMl){UqaVoEuLXn = true;}
      if(juVYqDOVRJ == JWddSmoZsS){uNLWtbdrIq = true;}
      if(bmxSJZaXXL == KoZSjWzACg){WxwjNOqikr = true;}
      if(iGZCNDteDb == OjLRohkMAn){MlZbiTZnEZ = true;}
      while(JWddSmoZsS == juVYqDOVRJ){DGFuwuGyqW = true;}
      while(KoZSjWzACg == KoZSjWzACg){QutaFIASfT = true;}
      while(OjLRohkMAn == OjLRohkMAn){PdqbjtAQDt = true;}
      if(DVAbhfHGyA == true){DVAbhfHGyA = false;}
      if(rCgyBjLwaJ == true){rCgyBjLwaJ = false;}
      if(UftyDZLMoj == true){UftyDZLMoj = false;}
      if(CcZEPnnyjE == true){CcZEPnnyjE = false;}
      if(PrCCoLCNQE == true){PrCCoLCNQE = false;}
      if(VnkpTWbCYI == true){VnkpTWbCYI = false;}
      if(UuRNxOcchN == true){UuRNxOcchN = false;}
      if(uNLWtbdrIq == true){uNLWtbdrIq = false;}
      if(WxwjNOqikr == true){WxwjNOqikr = false;}
      if(MlZbiTZnEZ == true){MlZbiTZnEZ = false;}
      if(iZeCIIbOwq == true){iZeCIIbOwq = false;}
      if(sisgkWzgAi == true){sisgkWzgAi = false;}
      if(XsrpAJnjmZ == true){XsrpAJnjmZ = false;}
      if(BonhIxSsbF == true){BonhIxSsbF = false;}
      if(lbmsydrrpM == true){lbmsydrrpM = false;}
      if(UsnUCohoCz == true){UsnUCohoCz = false;}
      if(UqaVoEuLXn == true){UqaVoEuLXn = false;}
      if(DGFuwuGyqW == true){DGFuwuGyqW = false;}
      if(QutaFIASfT == true){QutaFIASfT = false;}
      if(PdqbjtAQDt == true){PdqbjtAQDt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPQODUAXZM
{ 
  void JYwLfzlVnl()
  { 
      bool NcllYeBCfq = false;
      bool chkbPrqOuS = false;
      bool zFxSbMWljF = false;
      bool YQxJhUKhjo = false;
      bool nVtQKwhEbM = false;
      bool kqnNJIfTKM = false;
      bool IOSaRLkatu = false;
      bool gIeGecLfHe = false;
      bool dRJWTgbiAY = false;
      bool oqXWfYCSzy = false;
      bool LHKgfbMhhf = false;
      bool xzLehpFwHj = false;
      bool jBaUFokHaG = false;
      bool ZrfJTWHbqq = false;
      bool UtATbofrno = false;
      bool SGLOOKfobp = false;
      bool qFGbFFSCLL = false;
      bool idFQPoAGrQ = false;
      bool JrSkmTgQtJ = false;
      bool pRAAzPmYNW = false;
      string TtXSDtPfej;
      string FCRgJRuMTQ;
      string njAYxkJltR;
      string ucggHGSlIt;
      string VCpZKAPeRs;
      string oeLNOjszUS;
      string jdlMnbUkYC;
      string zIEYultZNx;
      string VeUAbQRTRX;
      string MSRpKrQclh;
      string eeFOtgalSc;
      string pTkXxFJkkX;
      string KBSBofqNOC;
      string UQnfRpYFGu;
      string oeAohshssF;
      string ifrNWdLEYN;
      string pMXPHYeFGG;
      string fDeohfBdSw;
      string xxUIToYZIm;
      string dTgrFcGjgJ;
      if(TtXSDtPfej == eeFOtgalSc){NcllYeBCfq = true;}
      else if(eeFOtgalSc == TtXSDtPfej){LHKgfbMhhf = true;}
      if(FCRgJRuMTQ == pTkXxFJkkX){chkbPrqOuS = true;}
      else if(pTkXxFJkkX == FCRgJRuMTQ){xzLehpFwHj = true;}
      if(njAYxkJltR == KBSBofqNOC){zFxSbMWljF = true;}
      else if(KBSBofqNOC == njAYxkJltR){jBaUFokHaG = true;}
      if(ucggHGSlIt == UQnfRpYFGu){YQxJhUKhjo = true;}
      else if(UQnfRpYFGu == ucggHGSlIt){ZrfJTWHbqq = true;}
      if(VCpZKAPeRs == oeAohshssF){nVtQKwhEbM = true;}
      else if(oeAohshssF == VCpZKAPeRs){UtATbofrno = true;}
      if(oeLNOjszUS == ifrNWdLEYN){kqnNJIfTKM = true;}
      else if(ifrNWdLEYN == oeLNOjszUS){SGLOOKfobp = true;}
      if(jdlMnbUkYC == pMXPHYeFGG){IOSaRLkatu = true;}
      else if(pMXPHYeFGG == jdlMnbUkYC){qFGbFFSCLL = true;}
      if(zIEYultZNx == fDeohfBdSw){gIeGecLfHe = true;}
      if(VeUAbQRTRX == xxUIToYZIm){dRJWTgbiAY = true;}
      if(MSRpKrQclh == dTgrFcGjgJ){oqXWfYCSzy = true;}
      while(fDeohfBdSw == zIEYultZNx){idFQPoAGrQ = true;}
      while(xxUIToYZIm == xxUIToYZIm){JrSkmTgQtJ = true;}
      while(dTgrFcGjgJ == dTgrFcGjgJ){pRAAzPmYNW = true;}
      if(NcllYeBCfq == true){NcllYeBCfq = false;}
      if(chkbPrqOuS == true){chkbPrqOuS = false;}
      if(zFxSbMWljF == true){zFxSbMWljF = false;}
      if(YQxJhUKhjo == true){YQxJhUKhjo = false;}
      if(nVtQKwhEbM == true){nVtQKwhEbM = false;}
      if(kqnNJIfTKM == true){kqnNJIfTKM = false;}
      if(IOSaRLkatu == true){IOSaRLkatu = false;}
      if(gIeGecLfHe == true){gIeGecLfHe = false;}
      if(dRJWTgbiAY == true){dRJWTgbiAY = false;}
      if(oqXWfYCSzy == true){oqXWfYCSzy = false;}
      if(LHKgfbMhhf == true){LHKgfbMhhf = false;}
      if(xzLehpFwHj == true){xzLehpFwHj = false;}
      if(jBaUFokHaG == true){jBaUFokHaG = false;}
      if(ZrfJTWHbqq == true){ZrfJTWHbqq = false;}
      if(UtATbofrno == true){UtATbofrno = false;}
      if(SGLOOKfobp == true){SGLOOKfobp = false;}
      if(qFGbFFSCLL == true){qFGbFFSCLL = false;}
      if(idFQPoAGrQ == true){idFQPoAGrQ = false;}
      if(JrSkmTgQtJ == true){JrSkmTgQtJ = false;}
      if(pRAAzPmYNW == true){pRAAzPmYNW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQRYFMVKWT
{ 
  void opBMDjaBKd()
  { 
      bool ufxJVjZnCy = false;
      bool axonMHayUH = false;
      bool pkugqLUtqf = false;
      bool XNQZxVsMct = false;
      bool nCmVsgMXmo = false;
      bool BxIQWKjPSK = false;
      bool PexWaMgPpq = false;
      bool ONVaTmxZnJ = false;
      bool zxHBdZEzCm = false;
      bool kctReIFQtf = false;
      bool Awgwanagxj = false;
      bool MKbJLRXusA = false;
      bool IgMCFlTDwL = false;
      bool hgeHICQLap = false;
      bool yXCSZaAjGM = false;
      bool jKXtXTjdqo = false;
      bool TXkkBfeTBJ = false;
      bool BMTDBjdscd = false;
      bool kixiaXJkjo = false;
      bool RlUlValQRt = false;
      string onCSKheZJP;
      string HGnPyPWPeA;
      string aGJiGksLns;
      string BTLJgfRxsS;
      string LPaKRhyySK;
      string MXskNhdTLZ;
      string oTlPNmudiS;
      string xZWMnKezQY;
      string lurcgcZZwy;
      string BykTdrcLwe;
      string mUOzNlBgwC;
      string CdCmmsaJik;
      string MUhjQynDiw;
      string gTCllRfsOt;
      string bsdswXwyfj;
      string RTcLRRldhO;
      string xyxAUhbPBV;
      string NgtnISqons;
      string CpWzeNqpTT;
      string eCLzwcudXN;
      if(onCSKheZJP == mUOzNlBgwC){ufxJVjZnCy = true;}
      else if(mUOzNlBgwC == onCSKheZJP){Awgwanagxj = true;}
      if(HGnPyPWPeA == CdCmmsaJik){axonMHayUH = true;}
      else if(CdCmmsaJik == HGnPyPWPeA){MKbJLRXusA = true;}
      if(aGJiGksLns == MUhjQynDiw){pkugqLUtqf = true;}
      else if(MUhjQynDiw == aGJiGksLns){IgMCFlTDwL = true;}
      if(BTLJgfRxsS == gTCllRfsOt){XNQZxVsMct = true;}
      else if(gTCllRfsOt == BTLJgfRxsS){hgeHICQLap = true;}
      if(LPaKRhyySK == bsdswXwyfj){nCmVsgMXmo = true;}
      else if(bsdswXwyfj == LPaKRhyySK){yXCSZaAjGM = true;}
      if(MXskNhdTLZ == RTcLRRldhO){BxIQWKjPSK = true;}
      else if(RTcLRRldhO == MXskNhdTLZ){jKXtXTjdqo = true;}
      if(oTlPNmudiS == xyxAUhbPBV){PexWaMgPpq = true;}
      else if(xyxAUhbPBV == oTlPNmudiS){TXkkBfeTBJ = true;}
      if(xZWMnKezQY == NgtnISqons){ONVaTmxZnJ = true;}
      if(lurcgcZZwy == CpWzeNqpTT){zxHBdZEzCm = true;}
      if(BykTdrcLwe == eCLzwcudXN){kctReIFQtf = true;}
      while(NgtnISqons == xZWMnKezQY){BMTDBjdscd = true;}
      while(CpWzeNqpTT == CpWzeNqpTT){kixiaXJkjo = true;}
      while(eCLzwcudXN == eCLzwcudXN){RlUlValQRt = true;}
      if(ufxJVjZnCy == true){ufxJVjZnCy = false;}
      if(axonMHayUH == true){axonMHayUH = false;}
      if(pkugqLUtqf == true){pkugqLUtqf = false;}
      if(XNQZxVsMct == true){XNQZxVsMct = false;}
      if(nCmVsgMXmo == true){nCmVsgMXmo = false;}
      if(BxIQWKjPSK == true){BxIQWKjPSK = false;}
      if(PexWaMgPpq == true){PexWaMgPpq = false;}
      if(ONVaTmxZnJ == true){ONVaTmxZnJ = false;}
      if(zxHBdZEzCm == true){zxHBdZEzCm = false;}
      if(kctReIFQtf == true){kctReIFQtf = false;}
      if(Awgwanagxj == true){Awgwanagxj = false;}
      if(MKbJLRXusA == true){MKbJLRXusA = false;}
      if(IgMCFlTDwL == true){IgMCFlTDwL = false;}
      if(hgeHICQLap == true){hgeHICQLap = false;}
      if(yXCSZaAjGM == true){yXCSZaAjGM = false;}
      if(jKXtXTjdqo == true){jKXtXTjdqo = false;}
      if(TXkkBfeTBJ == true){TXkkBfeTBJ = false;}
      if(BMTDBjdscd == true){BMTDBjdscd = false;}
      if(kixiaXJkjo == true){kixiaXJkjo = false;}
      if(RlUlValQRt == true){RlUlValQRt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMHXJARVPY
{ 
  void tFCGrwObMC()
  { 
      bool ixKCCwJslE = false;
      bool cFjJBdIBgt = false;
      bool loTpMjzAts = false;
      bool XPZLHVMjWn = false;
      bool OZwCDRnUey = false;
      bool gGAVOsdUoR = false;
      bool xIysgNfYCe = false;
      bool RYdseMrRlu = false;
      bool wdVuLQOEwN = false;
      bool rrtFqGaDVo = false;
      bool kORAgHbHqB = false;
      bool AMhtVSmDhP = false;
      bool zbbnmYeYBY = false;
      bool kowxKgMVND = false;
      bool oHNuMfKzjY = false;
      bool SXVFpJldMH = false;
      bool bDFRQKQjjn = false;
      bool GRodarOgbG = false;
      bool OencFNTpHA = false;
      bool thIGbkBudB = false;
      string nlFimcpBkW;
      string zXawnWgAjM;
      string LAOAauMFEB;
      string tmymiHrSiG;
      string SWASLwHbdp;
      string SmpWWnXEHq;
      string PjxicMYnMg;
      string dNRcsozuod;
      string mkbNhHxbPt;
      string jmKqqiZQpz;
      string WTOxLEVNch;
      string ncPdDeIiAU;
      string PwXSxqDZlK;
      string OiEpHTVdBd;
      string lizhGGWgmL;
      string ZqPVjauwzU;
      string BuaRSFXZWj;
      string JdgWifxpLp;
      string TWlZjXSiGg;
      string XYefcpIhPA;
      if(nlFimcpBkW == WTOxLEVNch){ixKCCwJslE = true;}
      else if(WTOxLEVNch == nlFimcpBkW){kORAgHbHqB = true;}
      if(zXawnWgAjM == ncPdDeIiAU){cFjJBdIBgt = true;}
      else if(ncPdDeIiAU == zXawnWgAjM){AMhtVSmDhP = true;}
      if(LAOAauMFEB == PwXSxqDZlK){loTpMjzAts = true;}
      else if(PwXSxqDZlK == LAOAauMFEB){zbbnmYeYBY = true;}
      if(tmymiHrSiG == OiEpHTVdBd){XPZLHVMjWn = true;}
      else if(OiEpHTVdBd == tmymiHrSiG){kowxKgMVND = true;}
      if(SWASLwHbdp == lizhGGWgmL){OZwCDRnUey = true;}
      else if(lizhGGWgmL == SWASLwHbdp){oHNuMfKzjY = true;}
      if(SmpWWnXEHq == ZqPVjauwzU){gGAVOsdUoR = true;}
      else if(ZqPVjauwzU == SmpWWnXEHq){SXVFpJldMH = true;}
      if(PjxicMYnMg == BuaRSFXZWj){xIysgNfYCe = true;}
      else if(BuaRSFXZWj == PjxicMYnMg){bDFRQKQjjn = true;}
      if(dNRcsozuod == JdgWifxpLp){RYdseMrRlu = true;}
      if(mkbNhHxbPt == TWlZjXSiGg){wdVuLQOEwN = true;}
      if(jmKqqiZQpz == XYefcpIhPA){rrtFqGaDVo = true;}
      while(JdgWifxpLp == dNRcsozuod){GRodarOgbG = true;}
      while(TWlZjXSiGg == TWlZjXSiGg){OencFNTpHA = true;}
      while(XYefcpIhPA == XYefcpIhPA){thIGbkBudB = true;}
      if(ixKCCwJslE == true){ixKCCwJslE = false;}
      if(cFjJBdIBgt == true){cFjJBdIBgt = false;}
      if(loTpMjzAts == true){loTpMjzAts = false;}
      if(XPZLHVMjWn == true){XPZLHVMjWn = false;}
      if(OZwCDRnUey == true){OZwCDRnUey = false;}
      if(gGAVOsdUoR == true){gGAVOsdUoR = false;}
      if(xIysgNfYCe == true){xIysgNfYCe = false;}
      if(RYdseMrRlu == true){RYdseMrRlu = false;}
      if(wdVuLQOEwN == true){wdVuLQOEwN = false;}
      if(rrtFqGaDVo == true){rrtFqGaDVo = false;}
      if(kORAgHbHqB == true){kORAgHbHqB = false;}
      if(AMhtVSmDhP == true){AMhtVSmDhP = false;}
      if(zbbnmYeYBY == true){zbbnmYeYBY = false;}
      if(kowxKgMVND == true){kowxKgMVND = false;}
      if(oHNuMfKzjY == true){oHNuMfKzjY = false;}
      if(SXVFpJldMH == true){SXVFpJldMH = false;}
      if(bDFRQKQjjn == true){bDFRQKQjjn = false;}
      if(GRodarOgbG == true){GRodarOgbG = false;}
      if(OencFNTpHA == true){OencFNTpHA = false;}
      if(thIGbkBudB == true){thIGbkBudB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKALGDSLDW
{ 
  void dIYzzYkPMr()
  { 
      bool qnasofOWOg = false;
      bool zbSXVDGkbD = false;
      bool dEDIInydON = false;
      bool OtLVtNUcij = false;
      bool VJtVspGNnt = false;
      bool xOcujljSjB = false;
      bool gjIARFPwdI = false;
      bool hcCqgUJhOS = false;
      bool hkpUQzRQkI = false;
      bool dCrhCkBsDn = false;
      bool ZJifLTLlNP = false;
      bool bBDRSutmjR = false;
      bool mzKUdfkUnw = false;
      bool SPdZrYCJJw = false;
      bool nfCVfbyaOG = false;
      bool qOJkBayOBf = false;
      bool iqxRwLWcZs = false;
      bool sjdmdHwooC = false;
      bool gJFgFEGsYQ = false;
      bool amIcNxhjYT = false;
      string ZjgmOETyWP;
      string YwdFkVDMzz;
      string VkHIErVtVq;
      string NDbNqkXGVc;
      string VEZioPCdzR;
      string VKHEwnbXiV;
      string iZbfCUTQOz;
      string xwpVdRLXSn;
      string prtDVCuXRC;
      string JAXztwbtgU;
      string ukOzUYUlZd;
      string cEFtepeXJA;
      string YwyLpwYqbh;
      string oRpyrEctix;
      string hJxmZEtcTD;
      string QEjguzmDJX;
      string zcJrnLNGBa;
      string NjoMSOzKkk;
      string CwWXQkgJCs;
      string RYkKxEAEzO;
      if(ZjgmOETyWP == ukOzUYUlZd){qnasofOWOg = true;}
      else if(ukOzUYUlZd == ZjgmOETyWP){ZJifLTLlNP = true;}
      if(YwdFkVDMzz == cEFtepeXJA){zbSXVDGkbD = true;}
      else if(cEFtepeXJA == YwdFkVDMzz){bBDRSutmjR = true;}
      if(VkHIErVtVq == YwyLpwYqbh){dEDIInydON = true;}
      else if(YwyLpwYqbh == VkHIErVtVq){mzKUdfkUnw = true;}
      if(NDbNqkXGVc == oRpyrEctix){OtLVtNUcij = true;}
      else if(oRpyrEctix == NDbNqkXGVc){SPdZrYCJJw = true;}
      if(VEZioPCdzR == hJxmZEtcTD){VJtVspGNnt = true;}
      else if(hJxmZEtcTD == VEZioPCdzR){nfCVfbyaOG = true;}
      if(VKHEwnbXiV == QEjguzmDJX){xOcujljSjB = true;}
      else if(QEjguzmDJX == VKHEwnbXiV){qOJkBayOBf = true;}
      if(iZbfCUTQOz == zcJrnLNGBa){gjIARFPwdI = true;}
      else if(zcJrnLNGBa == iZbfCUTQOz){iqxRwLWcZs = true;}
      if(xwpVdRLXSn == NjoMSOzKkk){hcCqgUJhOS = true;}
      if(prtDVCuXRC == CwWXQkgJCs){hkpUQzRQkI = true;}
      if(JAXztwbtgU == RYkKxEAEzO){dCrhCkBsDn = true;}
      while(NjoMSOzKkk == xwpVdRLXSn){sjdmdHwooC = true;}
      while(CwWXQkgJCs == CwWXQkgJCs){gJFgFEGsYQ = true;}
      while(RYkKxEAEzO == RYkKxEAEzO){amIcNxhjYT = true;}
      if(qnasofOWOg == true){qnasofOWOg = false;}
      if(zbSXVDGkbD == true){zbSXVDGkbD = false;}
      if(dEDIInydON == true){dEDIInydON = false;}
      if(OtLVtNUcij == true){OtLVtNUcij = false;}
      if(VJtVspGNnt == true){VJtVspGNnt = false;}
      if(xOcujljSjB == true){xOcujljSjB = false;}
      if(gjIARFPwdI == true){gjIARFPwdI = false;}
      if(hcCqgUJhOS == true){hcCqgUJhOS = false;}
      if(hkpUQzRQkI == true){hkpUQzRQkI = false;}
      if(dCrhCkBsDn == true){dCrhCkBsDn = false;}
      if(ZJifLTLlNP == true){ZJifLTLlNP = false;}
      if(bBDRSutmjR == true){bBDRSutmjR = false;}
      if(mzKUdfkUnw == true){mzKUdfkUnw = false;}
      if(SPdZrYCJJw == true){SPdZrYCJJw = false;}
      if(nfCVfbyaOG == true){nfCVfbyaOG = false;}
      if(qOJkBayOBf == true){qOJkBayOBf = false;}
      if(iqxRwLWcZs == true){iqxRwLWcZs = false;}
      if(sjdmdHwooC == true){sjdmdHwooC = false;}
      if(gJFgFEGsYQ == true){gJFgFEGsYQ = false;}
      if(amIcNxhjYT == true){amIcNxhjYT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJDRKNLUAV
{ 
  void tAwSXkapIc()
  { 
      bool KANFBAZIHS = false;
      bool bTqbDRtunW = false;
      bool afJnjaMqKC = false;
      bool RNilZWJjyG = false;
      bool ClcNMasoVo = false;
      bool koAYGdqYUZ = false;
      bool nixEAOjFCg = false;
      bool IKwgUoDubI = false;
      bool hWUURcNJew = false;
      bool ejOXRTnYMy = false;
      bool qmmngZrSER = false;
      bool awxMrQNbmX = false;
      bool BaZFCXuYOB = false;
      bool AdicRtjgnq = false;
      bool jtFNUimBfB = false;
      bool GLknxPNglI = false;
      bool eTEDQwMUux = false;
      bool gfnunGVMjS = false;
      bool kssNtnstfB = false;
      bool gCteMQpBwY = false;
      string NpcoeIUdaq;
      string qcpHNeejiZ;
      string gNfdFkYJZK;
      string RXZBrfhZCD;
      string zJEOWUPwGk;
      string JrlInzKzjs;
      string iLEPYSDoOh;
      string xFhfZWJQGk;
      string UcCnBZkRNr;
      string UipITnFooD;
      string QagYnEJGhQ;
      string psryYGIPOz;
      string hlbWMNOYLl;
      string RUbCTtudzw;
      string PeiwCbpqjM;
      string eoZpVezKMa;
      string ojtuzURpde;
      string LdPRiCCfTj;
      string WWozHbtkgo;
      string tjRYHfjnwg;
      if(NpcoeIUdaq == QagYnEJGhQ){KANFBAZIHS = true;}
      else if(QagYnEJGhQ == NpcoeIUdaq){qmmngZrSER = true;}
      if(qcpHNeejiZ == psryYGIPOz){bTqbDRtunW = true;}
      else if(psryYGIPOz == qcpHNeejiZ){awxMrQNbmX = true;}
      if(gNfdFkYJZK == hlbWMNOYLl){afJnjaMqKC = true;}
      else if(hlbWMNOYLl == gNfdFkYJZK){BaZFCXuYOB = true;}
      if(RXZBrfhZCD == RUbCTtudzw){RNilZWJjyG = true;}
      else if(RUbCTtudzw == RXZBrfhZCD){AdicRtjgnq = true;}
      if(zJEOWUPwGk == PeiwCbpqjM){ClcNMasoVo = true;}
      else if(PeiwCbpqjM == zJEOWUPwGk){jtFNUimBfB = true;}
      if(JrlInzKzjs == eoZpVezKMa){koAYGdqYUZ = true;}
      else if(eoZpVezKMa == JrlInzKzjs){GLknxPNglI = true;}
      if(iLEPYSDoOh == ojtuzURpde){nixEAOjFCg = true;}
      else if(ojtuzURpde == iLEPYSDoOh){eTEDQwMUux = true;}
      if(xFhfZWJQGk == LdPRiCCfTj){IKwgUoDubI = true;}
      if(UcCnBZkRNr == WWozHbtkgo){hWUURcNJew = true;}
      if(UipITnFooD == tjRYHfjnwg){ejOXRTnYMy = true;}
      while(LdPRiCCfTj == xFhfZWJQGk){gfnunGVMjS = true;}
      while(WWozHbtkgo == WWozHbtkgo){kssNtnstfB = true;}
      while(tjRYHfjnwg == tjRYHfjnwg){gCteMQpBwY = true;}
      if(KANFBAZIHS == true){KANFBAZIHS = false;}
      if(bTqbDRtunW == true){bTqbDRtunW = false;}
      if(afJnjaMqKC == true){afJnjaMqKC = false;}
      if(RNilZWJjyG == true){RNilZWJjyG = false;}
      if(ClcNMasoVo == true){ClcNMasoVo = false;}
      if(koAYGdqYUZ == true){koAYGdqYUZ = false;}
      if(nixEAOjFCg == true){nixEAOjFCg = false;}
      if(IKwgUoDubI == true){IKwgUoDubI = false;}
      if(hWUURcNJew == true){hWUURcNJew = false;}
      if(ejOXRTnYMy == true){ejOXRTnYMy = false;}
      if(qmmngZrSER == true){qmmngZrSER = false;}
      if(awxMrQNbmX == true){awxMrQNbmX = false;}
      if(BaZFCXuYOB == true){BaZFCXuYOB = false;}
      if(AdicRtjgnq == true){AdicRtjgnq = false;}
      if(jtFNUimBfB == true){jtFNUimBfB = false;}
      if(GLknxPNglI == true){GLknxPNglI = false;}
      if(eTEDQwMUux == true){eTEDQwMUux = false;}
      if(gfnunGVMjS == true){gfnunGVMjS = false;}
      if(kssNtnstfB == true){kssNtnstfB = false;}
      if(gCteMQpBwY == true){gCteMQpBwY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MRWUCGZAVH
{ 
  void FjkFHcQUAx()
  { 
      bool LkgmnzbzNJ = false;
      bool mQOUmKgNlX = false;
      bool xrqChikpcZ = false;
      bool NqxGxFjzzI = false;
      bool RzSFqCnKZk = false;
      bool PhKylSsdEF = false;
      bool OkWnuuSIXh = false;
      bool ZgNcGxZlKf = false;
      bool uaPqKffzUe = false;
      bool LFtttfceJu = false;
      bool ielrKhTgqn = false;
      bool sHTYKnUecP = false;
      bool PSnsVUmTia = false;
      bool UubPwPnXgc = false;
      bool LyIfkElUjF = false;
      bool KyBtfQqsWp = false;
      bool uAyQTxeDct = false;
      bool zxyADQKHHR = false;
      bool hRjcPWshif = false;
      bool XtAphLAqMn = false;
      string spJEbCsZgO;
      string tmMaioXGjU;
      string dhIKHcZhZJ;
      string SUxYIKcupy;
      string DbqSAwgrxW;
      string hJEksKgywz;
      string bKzWuYpmSX;
      string LcPlRBqoKK;
      string whjCbJQLey;
      string ceypVrbTWb;
      string FsYYKEsSTq;
      string SrnkDtawul;
      string IeIUtgdZPZ;
      string ZWRhFDIKrW;
      string PyqnekpMma;
      string QfXkTajEdd;
      string aTCtRuZFfA;
      string lQEYWJnToJ;
      string pQlnIsygOd;
      string SDfNuwuwVi;
      if(spJEbCsZgO == FsYYKEsSTq){LkgmnzbzNJ = true;}
      else if(FsYYKEsSTq == spJEbCsZgO){ielrKhTgqn = true;}
      if(tmMaioXGjU == SrnkDtawul){mQOUmKgNlX = true;}
      else if(SrnkDtawul == tmMaioXGjU){sHTYKnUecP = true;}
      if(dhIKHcZhZJ == IeIUtgdZPZ){xrqChikpcZ = true;}
      else if(IeIUtgdZPZ == dhIKHcZhZJ){PSnsVUmTia = true;}
      if(SUxYIKcupy == ZWRhFDIKrW){NqxGxFjzzI = true;}
      else if(ZWRhFDIKrW == SUxYIKcupy){UubPwPnXgc = true;}
      if(DbqSAwgrxW == PyqnekpMma){RzSFqCnKZk = true;}
      else if(PyqnekpMma == DbqSAwgrxW){LyIfkElUjF = true;}
      if(hJEksKgywz == QfXkTajEdd){PhKylSsdEF = true;}
      else if(QfXkTajEdd == hJEksKgywz){KyBtfQqsWp = true;}
      if(bKzWuYpmSX == aTCtRuZFfA){OkWnuuSIXh = true;}
      else if(aTCtRuZFfA == bKzWuYpmSX){uAyQTxeDct = true;}
      if(LcPlRBqoKK == lQEYWJnToJ){ZgNcGxZlKf = true;}
      if(whjCbJQLey == pQlnIsygOd){uaPqKffzUe = true;}
      if(ceypVrbTWb == SDfNuwuwVi){LFtttfceJu = true;}
      while(lQEYWJnToJ == LcPlRBqoKK){zxyADQKHHR = true;}
      while(pQlnIsygOd == pQlnIsygOd){hRjcPWshif = true;}
      while(SDfNuwuwVi == SDfNuwuwVi){XtAphLAqMn = true;}
      if(LkgmnzbzNJ == true){LkgmnzbzNJ = false;}
      if(mQOUmKgNlX == true){mQOUmKgNlX = false;}
      if(xrqChikpcZ == true){xrqChikpcZ = false;}
      if(NqxGxFjzzI == true){NqxGxFjzzI = false;}
      if(RzSFqCnKZk == true){RzSFqCnKZk = false;}
      if(PhKylSsdEF == true){PhKylSsdEF = false;}
      if(OkWnuuSIXh == true){OkWnuuSIXh = false;}
      if(ZgNcGxZlKf == true){ZgNcGxZlKf = false;}
      if(uaPqKffzUe == true){uaPqKffzUe = false;}
      if(LFtttfceJu == true){LFtttfceJu = false;}
      if(ielrKhTgqn == true){ielrKhTgqn = false;}
      if(sHTYKnUecP == true){sHTYKnUecP = false;}
      if(PSnsVUmTia == true){PSnsVUmTia = false;}
      if(UubPwPnXgc == true){UubPwPnXgc = false;}
      if(LyIfkElUjF == true){LyIfkElUjF = false;}
      if(KyBtfQqsWp == true){KyBtfQqsWp = false;}
      if(uAyQTxeDct == true){uAyQTxeDct = false;}
      if(zxyADQKHHR == true){zxyADQKHHR = false;}
      if(hRjcPWshif == true){hRjcPWshif = false;}
      if(XtAphLAqMn == true){XtAphLAqMn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYZFTFGRZM
{ 
  void ygEBukeJUl()
  { 
      bool mgeTFRDJNb = false;
      bool OaqLVaQEtf = false;
      bool gZdtUOxPlI = false;
      bool JNxDeklwKF = false;
      bool LALyqjCudr = false;
      bool PekQZNCkyp = false;
      bool UnXERBcmgj = false;
      bool nTtnUfOfCk = false;
      bool MBktsecgdR = false;
      bool hAxUkWcGfo = false;
      bool GPOsDukxus = false;
      bool yWhNcSCcKm = false;
      bool YwJOBmWYCx = false;
      bool DHAMdxmqpy = false;
      bool sfkjTLSiqS = false;
      bool UzwsQKFArP = false;
      bool XLtypqVUjf = false;
      bool eKlMsrLYup = false;
      bool UmgjcELGuS = false;
      bool qmzaZhkmtb = false;
      string VzEqaKqtCz;
      string HnTMlmQFcp;
      string JAsoOSwaLj;
      string nClHlSzXXf;
      string eEwOZBYnDf;
      string idxZiVFObI;
      string NPhRLECMaS;
      string nsgxLEEePN;
      string sIXeBJFLXP;
      string NjuPSPVeDU;
      string yLMkrpxzOd;
      string QazOOErCPB;
      string zpoKFDxQdw;
      string hYauOhwmmK;
      string MFxszmkfAN;
      string XSOCVIWCen;
      string rfVSuqzDAg;
      string IFPEossuLS;
      string SRPQXOKYZG;
      string LsHzSfjexH;
      if(VzEqaKqtCz == yLMkrpxzOd){mgeTFRDJNb = true;}
      else if(yLMkrpxzOd == VzEqaKqtCz){GPOsDukxus = true;}
      if(HnTMlmQFcp == QazOOErCPB){OaqLVaQEtf = true;}
      else if(QazOOErCPB == HnTMlmQFcp){yWhNcSCcKm = true;}
      if(JAsoOSwaLj == zpoKFDxQdw){gZdtUOxPlI = true;}
      else if(zpoKFDxQdw == JAsoOSwaLj){YwJOBmWYCx = true;}
      if(nClHlSzXXf == hYauOhwmmK){JNxDeklwKF = true;}
      else if(hYauOhwmmK == nClHlSzXXf){DHAMdxmqpy = true;}
      if(eEwOZBYnDf == MFxszmkfAN){LALyqjCudr = true;}
      else if(MFxszmkfAN == eEwOZBYnDf){sfkjTLSiqS = true;}
      if(idxZiVFObI == XSOCVIWCen){PekQZNCkyp = true;}
      else if(XSOCVIWCen == idxZiVFObI){UzwsQKFArP = true;}
      if(NPhRLECMaS == rfVSuqzDAg){UnXERBcmgj = true;}
      else if(rfVSuqzDAg == NPhRLECMaS){XLtypqVUjf = true;}
      if(nsgxLEEePN == IFPEossuLS){nTtnUfOfCk = true;}
      if(sIXeBJFLXP == SRPQXOKYZG){MBktsecgdR = true;}
      if(NjuPSPVeDU == LsHzSfjexH){hAxUkWcGfo = true;}
      while(IFPEossuLS == nsgxLEEePN){eKlMsrLYup = true;}
      while(SRPQXOKYZG == SRPQXOKYZG){UmgjcELGuS = true;}
      while(LsHzSfjexH == LsHzSfjexH){qmzaZhkmtb = true;}
      if(mgeTFRDJNb == true){mgeTFRDJNb = false;}
      if(OaqLVaQEtf == true){OaqLVaQEtf = false;}
      if(gZdtUOxPlI == true){gZdtUOxPlI = false;}
      if(JNxDeklwKF == true){JNxDeklwKF = false;}
      if(LALyqjCudr == true){LALyqjCudr = false;}
      if(PekQZNCkyp == true){PekQZNCkyp = false;}
      if(UnXERBcmgj == true){UnXERBcmgj = false;}
      if(nTtnUfOfCk == true){nTtnUfOfCk = false;}
      if(MBktsecgdR == true){MBktsecgdR = false;}
      if(hAxUkWcGfo == true){hAxUkWcGfo = false;}
      if(GPOsDukxus == true){GPOsDukxus = false;}
      if(yWhNcSCcKm == true){yWhNcSCcKm = false;}
      if(YwJOBmWYCx == true){YwJOBmWYCx = false;}
      if(DHAMdxmqpy == true){DHAMdxmqpy = false;}
      if(sfkjTLSiqS == true){sfkjTLSiqS = false;}
      if(UzwsQKFArP == true){UzwsQKFArP = false;}
      if(XLtypqVUjf == true){XLtypqVUjf = false;}
      if(eKlMsrLYup == true){eKlMsrLYup = false;}
      if(UmgjcELGuS == true){UmgjcELGuS = false;}
      if(qmzaZhkmtb == true){qmzaZhkmtb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOKZKNHFCW
{ 
  void ZRNVWeoJgZ()
  { 
      bool dZZXoSLzGX = false;
      bool iPJukAAXVw = false;
      bool CuxCbBfjPq = false;
      bool VtgSdVLtae = false;
      bool EbScoMParl = false;
      bool kTnGahbXum = false;
      bool maiPCniqQP = false;
      bool oGxpqZcUMO = false;
      bool lErdFBGarw = false;
      bool smymrcsDaA = false;
      bool dYKbxeWxOA = false;
      bool FGKgAiiFJA = false;
      bool hHzTVBIJyN = false;
      bool gYsLkNsQga = false;
      bool eILqqmbRlI = false;
      bool tnsZSVYpFu = false;
      bool VMzASfMzwm = false;
      bool oSYiVZwHci = false;
      bool YqXoTseTsO = false;
      bool nDKkERILXL = false;
      string UIOXOVzabk;
      string ZTgwgCkeZc;
      string WHxECAXkqB;
      string kbUMbrWJYV;
      string LhCSgUVfAf;
      string CSYEsMLKUN;
      string yNiZAyyUTo;
      string fbFEQoFdWh;
      string eqkKzRCQTP;
      string gLnLXxybSi;
      string VBLKAZMUmD;
      string GgmmiGbYah;
      string whAEHTmtfS;
      string pcKnLdfZKY;
      string EgdPIzYBcQ;
      string UZBjmmAGDg;
      string lSnTMdVzaF;
      string aCNCcOEjwH;
      string ulRPyQaZBY;
      string cYWdllrJCd;
      if(UIOXOVzabk == VBLKAZMUmD){dZZXoSLzGX = true;}
      else if(VBLKAZMUmD == UIOXOVzabk){dYKbxeWxOA = true;}
      if(ZTgwgCkeZc == GgmmiGbYah){iPJukAAXVw = true;}
      else if(GgmmiGbYah == ZTgwgCkeZc){FGKgAiiFJA = true;}
      if(WHxECAXkqB == whAEHTmtfS){CuxCbBfjPq = true;}
      else if(whAEHTmtfS == WHxECAXkqB){hHzTVBIJyN = true;}
      if(kbUMbrWJYV == pcKnLdfZKY){VtgSdVLtae = true;}
      else if(pcKnLdfZKY == kbUMbrWJYV){gYsLkNsQga = true;}
      if(LhCSgUVfAf == EgdPIzYBcQ){EbScoMParl = true;}
      else if(EgdPIzYBcQ == LhCSgUVfAf){eILqqmbRlI = true;}
      if(CSYEsMLKUN == UZBjmmAGDg){kTnGahbXum = true;}
      else if(UZBjmmAGDg == CSYEsMLKUN){tnsZSVYpFu = true;}
      if(yNiZAyyUTo == lSnTMdVzaF){maiPCniqQP = true;}
      else if(lSnTMdVzaF == yNiZAyyUTo){VMzASfMzwm = true;}
      if(fbFEQoFdWh == aCNCcOEjwH){oGxpqZcUMO = true;}
      if(eqkKzRCQTP == ulRPyQaZBY){lErdFBGarw = true;}
      if(gLnLXxybSi == cYWdllrJCd){smymrcsDaA = true;}
      while(aCNCcOEjwH == fbFEQoFdWh){oSYiVZwHci = true;}
      while(ulRPyQaZBY == ulRPyQaZBY){YqXoTseTsO = true;}
      while(cYWdllrJCd == cYWdllrJCd){nDKkERILXL = true;}
      if(dZZXoSLzGX == true){dZZXoSLzGX = false;}
      if(iPJukAAXVw == true){iPJukAAXVw = false;}
      if(CuxCbBfjPq == true){CuxCbBfjPq = false;}
      if(VtgSdVLtae == true){VtgSdVLtae = false;}
      if(EbScoMParl == true){EbScoMParl = false;}
      if(kTnGahbXum == true){kTnGahbXum = false;}
      if(maiPCniqQP == true){maiPCniqQP = false;}
      if(oGxpqZcUMO == true){oGxpqZcUMO = false;}
      if(lErdFBGarw == true){lErdFBGarw = false;}
      if(smymrcsDaA == true){smymrcsDaA = false;}
      if(dYKbxeWxOA == true){dYKbxeWxOA = false;}
      if(FGKgAiiFJA == true){FGKgAiiFJA = false;}
      if(hHzTVBIJyN == true){hHzTVBIJyN = false;}
      if(gYsLkNsQga == true){gYsLkNsQga = false;}
      if(eILqqmbRlI == true){eILqqmbRlI = false;}
      if(tnsZSVYpFu == true){tnsZSVYpFu = false;}
      if(VMzASfMzwm == true){VMzASfMzwm = false;}
      if(oSYiVZwHci == true){oSYiVZwHci = false;}
      if(YqXoTseTsO == true){YqXoTseTsO = false;}
      if(nDKkERILXL == true){nDKkERILXL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YFNLBJVRNL
{ 
  void kyTwPZfaYw()
  { 
      bool WtLbUMcVeQ = false;
      bool RQSSNUnFXK = false;
      bool xCLyUOaNBn = false;
      bool HCoICfoHbr = false;
      bool ESiGByySdm = false;
      bool HoeCsThMGF = false;
      bool lOUpIPaKQg = false;
      bool fgcfGdTExV = false;
      bool QHjNgSWmPh = false;
      bool xcAVGoyryl = false;
      bool XmCwHZLzwP = false;
      bool AcOkndeGIo = false;
      bool snthjCgGZQ = false;
      bool eaGLycFmGH = false;
      bool GWpAgTNOhb = false;
      bool KqiIrisTME = false;
      bool rEYejZWDmK = false;
      bool XqABhVxtAP = false;
      bool nRYxGmqxSO = false;
      bool jkaBOByLPH = false;
      string azEtVaUZNN;
      string DOSqasLXWp;
      string GdFVkyhqTt;
      string YIoAfcluAI;
      string uYnIMjqEFy;
      string PnMCowsiJX;
      string rdFSntZRKy;
      string HPWNuhoxIA;
      string GclVekumLi;
      string jDlcPRSUTR;
      string JYsGqzRzGG;
      string HuZIRPqjnD;
      string ylGbNDdtxd;
      string PUdpqgieee;
      string SwfEbnccLA;
      string ZhfPSXSRrm;
      string VWBcqlQiRj;
      string fMFJjCFCzZ;
      string ZAiwEgoOXS;
      string OQlqIutDMp;
      if(azEtVaUZNN == JYsGqzRzGG){WtLbUMcVeQ = true;}
      else if(JYsGqzRzGG == azEtVaUZNN){XmCwHZLzwP = true;}
      if(DOSqasLXWp == HuZIRPqjnD){RQSSNUnFXK = true;}
      else if(HuZIRPqjnD == DOSqasLXWp){AcOkndeGIo = true;}
      if(GdFVkyhqTt == ylGbNDdtxd){xCLyUOaNBn = true;}
      else if(ylGbNDdtxd == GdFVkyhqTt){snthjCgGZQ = true;}
      if(YIoAfcluAI == PUdpqgieee){HCoICfoHbr = true;}
      else if(PUdpqgieee == YIoAfcluAI){eaGLycFmGH = true;}
      if(uYnIMjqEFy == SwfEbnccLA){ESiGByySdm = true;}
      else if(SwfEbnccLA == uYnIMjqEFy){GWpAgTNOhb = true;}
      if(PnMCowsiJX == ZhfPSXSRrm){HoeCsThMGF = true;}
      else if(ZhfPSXSRrm == PnMCowsiJX){KqiIrisTME = true;}
      if(rdFSntZRKy == VWBcqlQiRj){lOUpIPaKQg = true;}
      else if(VWBcqlQiRj == rdFSntZRKy){rEYejZWDmK = true;}
      if(HPWNuhoxIA == fMFJjCFCzZ){fgcfGdTExV = true;}
      if(GclVekumLi == ZAiwEgoOXS){QHjNgSWmPh = true;}
      if(jDlcPRSUTR == OQlqIutDMp){xcAVGoyryl = true;}
      while(fMFJjCFCzZ == HPWNuhoxIA){XqABhVxtAP = true;}
      while(ZAiwEgoOXS == ZAiwEgoOXS){nRYxGmqxSO = true;}
      while(OQlqIutDMp == OQlqIutDMp){jkaBOByLPH = true;}
      if(WtLbUMcVeQ == true){WtLbUMcVeQ = false;}
      if(RQSSNUnFXK == true){RQSSNUnFXK = false;}
      if(xCLyUOaNBn == true){xCLyUOaNBn = false;}
      if(HCoICfoHbr == true){HCoICfoHbr = false;}
      if(ESiGByySdm == true){ESiGByySdm = false;}
      if(HoeCsThMGF == true){HoeCsThMGF = false;}
      if(lOUpIPaKQg == true){lOUpIPaKQg = false;}
      if(fgcfGdTExV == true){fgcfGdTExV = false;}
      if(QHjNgSWmPh == true){QHjNgSWmPh = false;}
      if(xcAVGoyryl == true){xcAVGoyryl = false;}
      if(XmCwHZLzwP == true){XmCwHZLzwP = false;}
      if(AcOkndeGIo == true){AcOkndeGIo = false;}
      if(snthjCgGZQ == true){snthjCgGZQ = false;}
      if(eaGLycFmGH == true){eaGLycFmGH = false;}
      if(GWpAgTNOhb == true){GWpAgTNOhb = false;}
      if(KqiIrisTME == true){KqiIrisTME = false;}
      if(rEYejZWDmK == true){rEYejZWDmK = false;}
      if(XqABhVxtAP == true){XqABhVxtAP = false;}
      if(nRYxGmqxSO == true){nRYxGmqxSO = false;}
      if(jkaBOByLPH == true){jkaBOByLPH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWAJPWEIXW
{ 
  void DZpuGPMYEx()
  { 
      bool UTPSxqeFNL = false;
      bool YaqapPNnUb = false;
      bool aaLEcFuLIT = false;
      bool DEepWQtpns = false;
      bool WItwMzPehn = false;
      bool rWmAtsHLpr = false;
      bool uSxtITwAEY = false;
      bool VWzaFSgPqc = false;
      bool oQdUagRdwd = false;
      bool JhAwyDLznr = false;
      bool DPZJSVWLtb = false;
      bool LrTMCdobTa = false;
      bool CREaPmWCcC = false;
      bool GhbzZZpUBE = false;
      bool JFiTRROmtT = false;
      bool NifMpkKzse = false;
      bool zUirUdPUmb = false;
      bool nUaORwhjIy = false;
      bool YiHJnXBPIn = false;
      bool OqaVFnWqym = false;
      string cZuypgpGEh;
      string LskFbSpXWb;
      string FNJkHVWcTs;
      string AGYSyyBIFr;
      string fmVXdcOipS;
      string YUzdPPQKpU;
      string KMlLhETRHc;
      string QhRdwSqkHe;
      string GmlBUfGtDi;
      string hqRkhSAKpY;
      string IxbNBpCVhw;
      string XeCLNXZkqC;
      string yYOXtZQfwc;
      string RguhVJKYAd;
      string cjMGLDnFWJ;
      string rPSmZjhDSb;
      string ZWZFdpiUoE;
      string MBjMZNLHMq;
      string kKJljCOHIk;
      string aHFXEFKHcV;
      if(cZuypgpGEh == IxbNBpCVhw){UTPSxqeFNL = true;}
      else if(IxbNBpCVhw == cZuypgpGEh){DPZJSVWLtb = true;}
      if(LskFbSpXWb == XeCLNXZkqC){YaqapPNnUb = true;}
      else if(XeCLNXZkqC == LskFbSpXWb){LrTMCdobTa = true;}
      if(FNJkHVWcTs == yYOXtZQfwc){aaLEcFuLIT = true;}
      else if(yYOXtZQfwc == FNJkHVWcTs){CREaPmWCcC = true;}
      if(AGYSyyBIFr == RguhVJKYAd){DEepWQtpns = true;}
      else if(RguhVJKYAd == AGYSyyBIFr){GhbzZZpUBE = true;}
      if(fmVXdcOipS == cjMGLDnFWJ){WItwMzPehn = true;}
      else if(cjMGLDnFWJ == fmVXdcOipS){JFiTRROmtT = true;}
      if(YUzdPPQKpU == rPSmZjhDSb){rWmAtsHLpr = true;}
      else if(rPSmZjhDSb == YUzdPPQKpU){NifMpkKzse = true;}
      if(KMlLhETRHc == ZWZFdpiUoE){uSxtITwAEY = true;}
      else if(ZWZFdpiUoE == KMlLhETRHc){zUirUdPUmb = true;}
      if(QhRdwSqkHe == MBjMZNLHMq){VWzaFSgPqc = true;}
      if(GmlBUfGtDi == kKJljCOHIk){oQdUagRdwd = true;}
      if(hqRkhSAKpY == aHFXEFKHcV){JhAwyDLznr = true;}
      while(MBjMZNLHMq == QhRdwSqkHe){nUaORwhjIy = true;}
      while(kKJljCOHIk == kKJljCOHIk){YiHJnXBPIn = true;}
      while(aHFXEFKHcV == aHFXEFKHcV){OqaVFnWqym = true;}
      if(UTPSxqeFNL == true){UTPSxqeFNL = false;}
      if(YaqapPNnUb == true){YaqapPNnUb = false;}
      if(aaLEcFuLIT == true){aaLEcFuLIT = false;}
      if(DEepWQtpns == true){DEepWQtpns = false;}
      if(WItwMzPehn == true){WItwMzPehn = false;}
      if(rWmAtsHLpr == true){rWmAtsHLpr = false;}
      if(uSxtITwAEY == true){uSxtITwAEY = false;}
      if(VWzaFSgPqc == true){VWzaFSgPqc = false;}
      if(oQdUagRdwd == true){oQdUagRdwd = false;}
      if(JhAwyDLznr == true){JhAwyDLznr = false;}
      if(DPZJSVWLtb == true){DPZJSVWLtb = false;}
      if(LrTMCdobTa == true){LrTMCdobTa = false;}
      if(CREaPmWCcC == true){CREaPmWCcC = false;}
      if(GhbzZZpUBE == true){GhbzZZpUBE = false;}
      if(JFiTRROmtT == true){JFiTRROmtT = false;}
      if(NifMpkKzse == true){NifMpkKzse = false;}
      if(zUirUdPUmb == true){zUirUdPUmb = false;}
      if(nUaORwhjIy == true){nUaORwhjIy = false;}
      if(YiHJnXBPIn == true){YiHJnXBPIn = false;}
      if(OqaVFnWqym == true){OqaVFnWqym = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJIEASBMKZ
{ 
  void jsaDADFCxj()
  { 
      bool RcWgqiwOXC = false;
      bool KSmWmIrcNT = false;
      bool BbkYVXqzlF = false;
      bool TPGdbLCuMc = false;
      bool cGRwaqSfgJ = false;
      bool amfHhpqyLT = false;
      bool qxcRhuMItb = false;
      bool GwQkptJnxd = false;
      bool ELSbegjywl = false;
      bool TDislfdANf = false;
      bool eKkECdWtQm = false;
      bool fDAhOfeAmB = false;
      bool KNMIICNXzK = false;
      bool QJZRytZNZA = false;
      bool KogIGPCBdF = false;
      bool BcMMUQxcwA = false;
      bool QzuGWWciiU = false;
      bool FQalqVgECr = false;
      bool zMssJmxNwg = false;
      bool wxRYjLsZkj = false;
      string ACncbyGXgJ;
      string YuNcxzVAxI;
      string idHKKXkall;
      string BniGohNPHS;
      string YPRPEIKIKN;
      string uDkzCWucRD;
      string MeluIjMGmP;
      string kFseiTLrGC;
      string NbPXpxDiES;
      string ljxDFsdWGT;
      string wDVubpKGPi;
      string LCWPpjPOEK;
      string gcCUdBHpYp;
      string onklFKGUuA;
      string mxTUGiNhMU;
      string dPSumTAARa;
      string hUgZsWRjKf;
      string duSDXjJhNt;
      string nZcDLZVozk;
      string KFDTRSPsbj;
      if(ACncbyGXgJ == wDVubpKGPi){RcWgqiwOXC = true;}
      else if(wDVubpKGPi == ACncbyGXgJ){eKkECdWtQm = true;}
      if(YuNcxzVAxI == LCWPpjPOEK){KSmWmIrcNT = true;}
      else if(LCWPpjPOEK == YuNcxzVAxI){fDAhOfeAmB = true;}
      if(idHKKXkall == gcCUdBHpYp){BbkYVXqzlF = true;}
      else if(gcCUdBHpYp == idHKKXkall){KNMIICNXzK = true;}
      if(BniGohNPHS == onklFKGUuA){TPGdbLCuMc = true;}
      else if(onklFKGUuA == BniGohNPHS){QJZRytZNZA = true;}
      if(YPRPEIKIKN == mxTUGiNhMU){cGRwaqSfgJ = true;}
      else if(mxTUGiNhMU == YPRPEIKIKN){KogIGPCBdF = true;}
      if(uDkzCWucRD == dPSumTAARa){amfHhpqyLT = true;}
      else if(dPSumTAARa == uDkzCWucRD){BcMMUQxcwA = true;}
      if(MeluIjMGmP == hUgZsWRjKf){qxcRhuMItb = true;}
      else if(hUgZsWRjKf == MeluIjMGmP){QzuGWWciiU = true;}
      if(kFseiTLrGC == duSDXjJhNt){GwQkptJnxd = true;}
      if(NbPXpxDiES == nZcDLZVozk){ELSbegjywl = true;}
      if(ljxDFsdWGT == KFDTRSPsbj){TDislfdANf = true;}
      while(duSDXjJhNt == kFseiTLrGC){FQalqVgECr = true;}
      while(nZcDLZVozk == nZcDLZVozk){zMssJmxNwg = true;}
      while(KFDTRSPsbj == KFDTRSPsbj){wxRYjLsZkj = true;}
      if(RcWgqiwOXC == true){RcWgqiwOXC = false;}
      if(KSmWmIrcNT == true){KSmWmIrcNT = false;}
      if(BbkYVXqzlF == true){BbkYVXqzlF = false;}
      if(TPGdbLCuMc == true){TPGdbLCuMc = false;}
      if(cGRwaqSfgJ == true){cGRwaqSfgJ = false;}
      if(amfHhpqyLT == true){amfHhpqyLT = false;}
      if(qxcRhuMItb == true){qxcRhuMItb = false;}
      if(GwQkptJnxd == true){GwQkptJnxd = false;}
      if(ELSbegjywl == true){ELSbegjywl = false;}
      if(TDislfdANf == true){TDislfdANf = false;}
      if(eKkECdWtQm == true){eKkECdWtQm = false;}
      if(fDAhOfeAmB == true){fDAhOfeAmB = false;}
      if(KNMIICNXzK == true){KNMIICNXzK = false;}
      if(QJZRytZNZA == true){QJZRytZNZA = false;}
      if(KogIGPCBdF == true){KogIGPCBdF = false;}
      if(BcMMUQxcwA == true){BcMMUQxcwA = false;}
      if(QzuGWWciiU == true){QzuGWWciiU = false;}
      if(FQalqVgECr == true){FQalqVgECr = false;}
      if(zMssJmxNwg == true){zMssJmxNwg = false;}
      if(wxRYjLsZkj == true){wxRYjLsZkj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFUTGPQKOR
{ 
  void EfUwhhjZkU()
  { 
      bool dWMSBkSzpk = false;
      bool KEipwKoCON = false;
      bool CmnFbtprzK = false;
      bool ssQhlUCuME = false;
      bool QLUcBzWUpW = false;
      bool VYBfhqiGqG = false;
      bool uZzfqRnADb = false;
      bool ItpJxqRKEb = false;
      bool WUBcoUqjAu = false;
      bool luDFJpLolj = false;
      bool LWQOOaiqip = false;
      bool ZXCPjZYWqW = false;
      bool ZDAIpMpjAH = false;
      bool ebYTQADmON = false;
      bool kzBJUNsnVi = false;
      bool QoyOKHWIYB = false;
      bool jyqbLxyhyi = false;
      bool VkIdkZCpmb = false;
      bool SCOQppdKJJ = false;
      bool duOMcmIZyX = false;
      string MUHsSDwofe;
      string RwCpfdfGZW;
      string VufsNdRKDQ;
      string OfOfUmMJqx;
      string pnjMEgoorW;
      string phIMLQoNeo;
      string lkkOQkgWVr;
      string QWPbghLSof;
      string nbSgagXBTD;
      string yzdBLECUuT;
      string zSTAGSRffc;
      string EVYzBJSEnj;
      string MeCRsRsNPb;
      string fqWUgUIRZH;
      string OrUqycZezC;
      string lxfLGUPCGn;
      string ZDQEwNyDRf;
      string AAdgUUJLSQ;
      string qOONpiKLOM;
      string EGKlhKbQtk;
      if(MUHsSDwofe == zSTAGSRffc){dWMSBkSzpk = true;}
      else if(zSTAGSRffc == MUHsSDwofe){LWQOOaiqip = true;}
      if(RwCpfdfGZW == EVYzBJSEnj){KEipwKoCON = true;}
      else if(EVYzBJSEnj == RwCpfdfGZW){ZXCPjZYWqW = true;}
      if(VufsNdRKDQ == MeCRsRsNPb){CmnFbtprzK = true;}
      else if(MeCRsRsNPb == VufsNdRKDQ){ZDAIpMpjAH = true;}
      if(OfOfUmMJqx == fqWUgUIRZH){ssQhlUCuME = true;}
      else if(fqWUgUIRZH == OfOfUmMJqx){ebYTQADmON = true;}
      if(pnjMEgoorW == OrUqycZezC){QLUcBzWUpW = true;}
      else if(OrUqycZezC == pnjMEgoorW){kzBJUNsnVi = true;}
      if(phIMLQoNeo == lxfLGUPCGn){VYBfhqiGqG = true;}
      else if(lxfLGUPCGn == phIMLQoNeo){QoyOKHWIYB = true;}
      if(lkkOQkgWVr == ZDQEwNyDRf){uZzfqRnADb = true;}
      else if(ZDQEwNyDRf == lkkOQkgWVr){jyqbLxyhyi = true;}
      if(QWPbghLSof == AAdgUUJLSQ){ItpJxqRKEb = true;}
      if(nbSgagXBTD == qOONpiKLOM){WUBcoUqjAu = true;}
      if(yzdBLECUuT == EGKlhKbQtk){luDFJpLolj = true;}
      while(AAdgUUJLSQ == QWPbghLSof){VkIdkZCpmb = true;}
      while(qOONpiKLOM == qOONpiKLOM){SCOQppdKJJ = true;}
      while(EGKlhKbQtk == EGKlhKbQtk){duOMcmIZyX = true;}
      if(dWMSBkSzpk == true){dWMSBkSzpk = false;}
      if(KEipwKoCON == true){KEipwKoCON = false;}
      if(CmnFbtprzK == true){CmnFbtprzK = false;}
      if(ssQhlUCuME == true){ssQhlUCuME = false;}
      if(QLUcBzWUpW == true){QLUcBzWUpW = false;}
      if(VYBfhqiGqG == true){VYBfhqiGqG = false;}
      if(uZzfqRnADb == true){uZzfqRnADb = false;}
      if(ItpJxqRKEb == true){ItpJxqRKEb = false;}
      if(WUBcoUqjAu == true){WUBcoUqjAu = false;}
      if(luDFJpLolj == true){luDFJpLolj = false;}
      if(LWQOOaiqip == true){LWQOOaiqip = false;}
      if(ZXCPjZYWqW == true){ZXCPjZYWqW = false;}
      if(ZDAIpMpjAH == true){ZDAIpMpjAH = false;}
      if(ebYTQADmON == true){ebYTQADmON = false;}
      if(kzBJUNsnVi == true){kzBJUNsnVi = false;}
      if(QoyOKHWIYB == true){QoyOKHWIYB = false;}
      if(jyqbLxyhyi == true){jyqbLxyhyi = false;}
      if(VkIdkZCpmb == true){VkIdkZCpmb = false;}
      if(SCOQppdKJJ == true){SCOQppdKJJ = false;}
      if(duOMcmIZyX == true){duOMcmIZyX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIOZFARFMS
{ 
  void HJaSzMmzCf()
  { 
      bool sbKElxsHcx = false;
      bool YqDGSpYShm = false;
      bool bEjKOBVWlk = false;
      bool niOmhYWWkW = false;
      bool IFENHYMFbj = false;
      bool TbDCKnrzok = false;
      bool aVVqJobQYs = false;
      bool SBgLdWAWDp = false;
      bool nQuCQLfMcs = false;
      bool gWgAwmjMDR = false;
      bool wwfhQSurXn = false;
      bool nVuzwKZTax = false;
      bool JOneMwTfOq = false;
      bool lmSlsqjNky = false;
      bool QmonEKahEl = false;
      bool MQlGHgIBUU = false;
      bool yPcfBBCJFF = false;
      bool ZLhbgVZzZC = false;
      bool UkbcdVAMdM = false;
      bool hisQzBKImD = false;
      string hFpobBDZcc;
      string jCFlJWaAzb;
      string jAQMopMokP;
      string COAniumVMG;
      string UfpBVHxkEb;
      string LzLIGhodAk;
      string oNoMZVCRDN;
      string iFmsGEKOqg;
      string sbkIDDCqgA;
      string GJVbRHqcbz;
      string FfgpsGLRCC;
      string XZlSrMbfIV;
      string SKjDHYjLbz;
      string MgmqaMttOx;
      string rjoecfXCjE;
      string eKTFfuwdhU;
      string WApCopluqe;
      string RhRLciVEZb;
      string BgbXTBNgKf;
      string QQLtZrtlom;
      if(hFpobBDZcc == FfgpsGLRCC){sbKElxsHcx = true;}
      else if(FfgpsGLRCC == hFpobBDZcc){wwfhQSurXn = true;}
      if(jCFlJWaAzb == XZlSrMbfIV){YqDGSpYShm = true;}
      else if(XZlSrMbfIV == jCFlJWaAzb){nVuzwKZTax = true;}
      if(jAQMopMokP == SKjDHYjLbz){bEjKOBVWlk = true;}
      else if(SKjDHYjLbz == jAQMopMokP){JOneMwTfOq = true;}
      if(COAniumVMG == MgmqaMttOx){niOmhYWWkW = true;}
      else if(MgmqaMttOx == COAniumVMG){lmSlsqjNky = true;}
      if(UfpBVHxkEb == rjoecfXCjE){IFENHYMFbj = true;}
      else if(rjoecfXCjE == UfpBVHxkEb){QmonEKahEl = true;}
      if(LzLIGhodAk == eKTFfuwdhU){TbDCKnrzok = true;}
      else if(eKTFfuwdhU == LzLIGhodAk){MQlGHgIBUU = true;}
      if(oNoMZVCRDN == WApCopluqe){aVVqJobQYs = true;}
      else if(WApCopluqe == oNoMZVCRDN){yPcfBBCJFF = true;}
      if(iFmsGEKOqg == RhRLciVEZb){SBgLdWAWDp = true;}
      if(sbkIDDCqgA == BgbXTBNgKf){nQuCQLfMcs = true;}
      if(GJVbRHqcbz == QQLtZrtlom){gWgAwmjMDR = true;}
      while(RhRLciVEZb == iFmsGEKOqg){ZLhbgVZzZC = true;}
      while(BgbXTBNgKf == BgbXTBNgKf){UkbcdVAMdM = true;}
      while(QQLtZrtlom == QQLtZrtlom){hisQzBKImD = true;}
      if(sbKElxsHcx == true){sbKElxsHcx = false;}
      if(YqDGSpYShm == true){YqDGSpYShm = false;}
      if(bEjKOBVWlk == true){bEjKOBVWlk = false;}
      if(niOmhYWWkW == true){niOmhYWWkW = false;}
      if(IFENHYMFbj == true){IFENHYMFbj = false;}
      if(TbDCKnrzok == true){TbDCKnrzok = false;}
      if(aVVqJobQYs == true){aVVqJobQYs = false;}
      if(SBgLdWAWDp == true){SBgLdWAWDp = false;}
      if(nQuCQLfMcs == true){nQuCQLfMcs = false;}
      if(gWgAwmjMDR == true){gWgAwmjMDR = false;}
      if(wwfhQSurXn == true){wwfhQSurXn = false;}
      if(nVuzwKZTax == true){nVuzwKZTax = false;}
      if(JOneMwTfOq == true){JOneMwTfOq = false;}
      if(lmSlsqjNky == true){lmSlsqjNky = false;}
      if(QmonEKahEl == true){QmonEKahEl = false;}
      if(MQlGHgIBUU == true){MQlGHgIBUU = false;}
      if(yPcfBBCJFF == true){yPcfBBCJFF = false;}
      if(ZLhbgVZzZC == true){ZLhbgVZzZC = false;}
      if(UkbcdVAMdM == true){UkbcdVAMdM = false;}
      if(hisQzBKImD == true){hisQzBKImD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZLPLIHKFZ
{ 
  void IcdPVrudZD()
  { 
      bool nDRHxGgQyN = false;
      bool CqLMHCrlsU = false;
      bool qWHVbCCxFx = false;
      bool mNOqMSWdtF = false;
      bool XeGBjgOsJu = false;
      bool WfludQwueu = false;
      bool EiKBZnbTAo = false;
      bool fOrmxLQFlu = false;
      bool nImKaHbTMu = false;
      bool WayzAnTEbu = false;
      bool EtsUOInyyS = false;
      bool ApJiHwuAaR = false;
      bool MIGESFPrlI = false;
      bool qLdqpsOSuS = false;
      bool TcUttfQOrE = false;
      bool rTdJhwnnCJ = false;
      bool ruLoaoMSsN = false;
      bool gcFIyimLKl = false;
      bool nAAgPXhUIt = false;
      bool EZQkZXReSF = false;
      string BdcRidXNJt;
      string zIdQDQmYei;
      string AXHTWFNzdZ;
      string dEPwmenKeO;
      string QrwdQQWWCE;
      string gQLzgcVIuc;
      string PYjjQushdY;
      string cctQSHadDF;
      string ipwYrNrQOJ;
      string IePBzqHLNV;
      string XorcbEVufZ;
      string BrEotZbLrD;
      string CcTUQxNrRb;
      string APPhgsxSwn;
      string qwjoHPaZHY;
      string PwTKSuVXMe;
      string pcdEYlbWHA;
      string bIODLFreMA;
      string WnkrLEuFOl;
      string XZGRxORePU;
      if(BdcRidXNJt == XorcbEVufZ){nDRHxGgQyN = true;}
      else if(XorcbEVufZ == BdcRidXNJt){EtsUOInyyS = true;}
      if(zIdQDQmYei == BrEotZbLrD){CqLMHCrlsU = true;}
      else if(BrEotZbLrD == zIdQDQmYei){ApJiHwuAaR = true;}
      if(AXHTWFNzdZ == CcTUQxNrRb){qWHVbCCxFx = true;}
      else if(CcTUQxNrRb == AXHTWFNzdZ){MIGESFPrlI = true;}
      if(dEPwmenKeO == APPhgsxSwn){mNOqMSWdtF = true;}
      else if(APPhgsxSwn == dEPwmenKeO){qLdqpsOSuS = true;}
      if(QrwdQQWWCE == qwjoHPaZHY){XeGBjgOsJu = true;}
      else if(qwjoHPaZHY == QrwdQQWWCE){TcUttfQOrE = true;}
      if(gQLzgcVIuc == PwTKSuVXMe){WfludQwueu = true;}
      else if(PwTKSuVXMe == gQLzgcVIuc){rTdJhwnnCJ = true;}
      if(PYjjQushdY == pcdEYlbWHA){EiKBZnbTAo = true;}
      else if(pcdEYlbWHA == PYjjQushdY){ruLoaoMSsN = true;}
      if(cctQSHadDF == bIODLFreMA){fOrmxLQFlu = true;}
      if(ipwYrNrQOJ == WnkrLEuFOl){nImKaHbTMu = true;}
      if(IePBzqHLNV == XZGRxORePU){WayzAnTEbu = true;}
      while(bIODLFreMA == cctQSHadDF){gcFIyimLKl = true;}
      while(WnkrLEuFOl == WnkrLEuFOl){nAAgPXhUIt = true;}
      while(XZGRxORePU == XZGRxORePU){EZQkZXReSF = true;}
      if(nDRHxGgQyN == true){nDRHxGgQyN = false;}
      if(CqLMHCrlsU == true){CqLMHCrlsU = false;}
      if(qWHVbCCxFx == true){qWHVbCCxFx = false;}
      if(mNOqMSWdtF == true){mNOqMSWdtF = false;}
      if(XeGBjgOsJu == true){XeGBjgOsJu = false;}
      if(WfludQwueu == true){WfludQwueu = false;}
      if(EiKBZnbTAo == true){EiKBZnbTAo = false;}
      if(fOrmxLQFlu == true){fOrmxLQFlu = false;}
      if(nImKaHbTMu == true){nImKaHbTMu = false;}
      if(WayzAnTEbu == true){WayzAnTEbu = false;}
      if(EtsUOInyyS == true){EtsUOInyyS = false;}
      if(ApJiHwuAaR == true){ApJiHwuAaR = false;}
      if(MIGESFPrlI == true){MIGESFPrlI = false;}
      if(qLdqpsOSuS == true){qLdqpsOSuS = false;}
      if(TcUttfQOrE == true){TcUttfQOrE = false;}
      if(rTdJhwnnCJ == true){rTdJhwnnCJ = false;}
      if(ruLoaoMSsN == true){ruLoaoMSsN = false;}
      if(gcFIyimLKl == true){gcFIyimLKl = false;}
      if(nAAgPXhUIt == true){nAAgPXhUIt = false;}
      if(EZQkZXReSF == true){EZQkZXReSF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEQSNIYCAG
{ 
  void YpxSbCUCcg()
  { 
      bool deKtXutyqu = false;
      bool IVRDeAdlOy = false;
      bool apCxhsOwrb = false;
      bool IbmRWJNFyQ = false;
      bool tExOWFbeYa = false;
      bool apkZomcNLd = false;
      bool fxGPmfiAfU = false;
      bool lYnxEVsmZc = false;
      bool RiXQBRpNcj = false;
      bool gAsTjwyhbp = false;
      bool WbzDnCCmVS = false;
      bool tpmiMwZoNV = false;
      bool pUWwnleUMH = false;
      bool XLKiFojTcy = false;
      bool PCrJppMJHn = false;
      bool WJTGABEDPB = false;
      bool XhaNuheEdW = false;
      bool MFLOFmbNFx = false;
      bool YUMYjOqEhD = false;
      bool kgEaahbdNH = false;
      string EaCoJhVDWK;
      string mVOXPfUiay;
      string RycztZahGQ;
      string boPIABAbGA;
      string RPrXCrLBdg;
      string eKOLZFyCui;
      string GnwGhxGGXO;
      string fsbZgCGExC;
      string OYDYlRaEit;
      string DxgXscSkpE;
      string lFdPBkhodW;
      string zsFsThkXTQ;
      string WBWcKhMEgE;
      string jUNrPJtmWA;
      string ikZLuJrmEK;
      string ruRYgjhAET;
      string YdIZmdeMcJ;
      string mxASglbLhB;
      string oYzVLoDoKf;
      string bthDaFczXQ;
      if(EaCoJhVDWK == lFdPBkhodW){deKtXutyqu = true;}
      else if(lFdPBkhodW == EaCoJhVDWK){WbzDnCCmVS = true;}
      if(mVOXPfUiay == zsFsThkXTQ){IVRDeAdlOy = true;}
      else if(zsFsThkXTQ == mVOXPfUiay){tpmiMwZoNV = true;}
      if(RycztZahGQ == WBWcKhMEgE){apCxhsOwrb = true;}
      else if(WBWcKhMEgE == RycztZahGQ){pUWwnleUMH = true;}
      if(boPIABAbGA == jUNrPJtmWA){IbmRWJNFyQ = true;}
      else if(jUNrPJtmWA == boPIABAbGA){XLKiFojTcy = true;}
      if(RPrXCrLBdg == ikZLuJrmEK){tExOWFbeYa = true;}
      else if(ikZLuJrmEK == RPrXCrLBdg){PCrJppMJHn = true;}
      if(eKOLZFyCui == ruRYgjhAET){apkZomcNLd = true;}
      else if(ruRYgjhAET == eKOLZFyCui){WJTGABEDPB = true;}
      if(GnwGhxGGXO == YdIZmdeMcJ){fxGPmfiAfU = true;}
      else if(YdIZmdeMcJ == GnwGhxGGXO){XhaNuheEdW = true;}
      if(fsbZgCGExC == mxASglbLhB){lYnxEVsmZc = true;}
      if(OYDYlRaEit == oYzVLoDoKf){RiXQBRpNcj = true;}
      if(DxgXscSkpE == bthDaFczXQ){gAsTjwyhbp = true;}
      while(mxASglbLhB == fsbZgCGExC){MFLOFmbNFx = true;}
      while(oYzVLoDoKf == oYzVLoDoKf){YUMYjOqEhD = true;}
      while(bthDaFczXQ == bthDaFczXQ){kgEaahbdNH = true;}
      if(deKtXutyqu == true){deKtXutyqu = false;}
      if(IVRDeAdlOy == true){IVRDeAdlOy = false;}
      if(apCxhsOwrb == true){apCxhsOwrb = false;}
      if(IbmRWJNFyQ == true){IbmRWJNFyQ = false;}
      if(tExOWFbeYa == true){tExOWFbeYa = false;}
      if(apkZomcNLd == true){apkZomcNLd = false;}
      if(fxGPmfiAfU == true){fxGPmfiAfU = false;}
      if(lYnxEVsmZc == true){lYnxEVsmZc = false;}
      if(RiXQBRpNcj == true){RiXQBRpNcj = false;}
      if(gAsTjwyhbp == true){gAsTjwyhbp = false;}
      if(WbzDnCCmVS == true){WbzDnCCmVS = false;}
      if(tpmiMwZoNV == true){tpmiMwZoNV = false;}
      if(pUWwnleUMH == true){pUWwnleUMH = false;}
      if(XLKiFojTcy == true){XLKiFojTcy = false;}
      if(PCrJppMJHn == true){PCrJppMJHn = false;}
      if(WJTGABEDPB == true){WJTGABEDPB = false;}
      if(XhaNuheEdW == true){XhaNuheEdW = false;}
      if(MFLOFmbNFx == true){MFLOFmbNFx = false;}
      if(YUMYjOqEhD == true){YUMYjOqEhD = false;}
      if(kgEaahbdNH == true){kgEaahbdNH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZXHJFDAXV
{ 
  void OkZQXRZCmg()
  { 
      bool YmlRmXuWPR = false;
      bool SQtPsrDhNA = false;
      bool wQrXwmzOrF = false;
      bool jRfVpXeJAT = false;
      bool sQtDcfenAb = false;
      bool sLHpdIuNVA = false;
      bool XgeJhAjYZV = false;
      bool MtgsGfWouP = false;
      bool HLOPLXKpqg = false;
      bool cRmAwMkjVb = false;
      bool wGOePyeOiy = false;
      bool lFSGsMSOyJ = false;
      bool ptgrruGfxt = false;
      bool tlTSTAwiAN = false;
      bool suHruWygHi = false;
      bool sWlLlCZWlU = false;
      bool qyQnEzlzmr = false;
      bool PiOjQtmnwU = false;
      bool wZYNAXzHgR = false;
      bool ZZxfVteSnu = false;
      string hMwzxXDztI;
      string QPbyrHXYfI;
      string oanMFpinbr;
      string lyDGZaOWwQ;
      string bibRHhNVLK;
      string hsYEoGYitH;
      string oOXBWSMVYR;
      string rAbPfFyWFX;
      string cMcQKrYyQS;
      string CfcobNLaun;
      string UrwtRgQJXj;
      string HCdWdblHpd;
      string sOEGPMXlmS;
      string tXaQCkPhyd;
      string bPagKABGLz;
      string aEjRuGnpeF;
      string JeVFpjaNTs;
      string MDIMCdmWwO;
      string LRanqonJUw;
      string xZDsUwsVpa;
      if(hMwzxXDztI == UrwtRgQJXj){YmlRmXuWPR = true;}
      else if(UrwtRgQJXj == hMwzxXDztI){wGOePyeOiy = true;}
      if(QPbyrHXYfI == HCdWdblHpd){SQtPsrDhNA = true;}
      else if(HCdWdblHpd == QPbyrHXYfI){lFSGsMSOyJ = true;}
      if(oanMFpinbr == sOEGPMXlmS){wQrXwmzOrF = true;}
      else if(sOEGPMXlmS == oanMFpinbr){ptgrruGfxt = true;}
      if(lyDGZaOWwQ == tXaQCkPhyd){jRfVpXeJAT = true;}
      else if(tXaQCkPhyd == lyDGZaOWwQ){tlTSTAwiAN = true;}
      if(bibRHhNVLK == bPagKABGLz){sQtDcfenAb = true;}
      else if(bPagKABGLz == bibRHhNVLK){suHruWygHi = true;}
      if(hsYEoGYitH == aEjRuGnpeF){sLHpdIuNVA = true;}
      else if(aEjRuGnpeF == hsYEoGYitH){sWlLlCZWlU = true;}
      if(oOXBWSMVYR == JeVFpjaNTs){XgeJhAjYZV = true;}
      else if(JeVFpjaNTs == oOXBWSMVYR){qyQnEzlzmr = true;}
      if(rAbPfFyWFX == MDIMCdmWwO){MtgsGfWouP = true;}
      if(cMcQKrYyQS == LRanqonJUw){HLOPLXKpqg = true;}
      if(CfcobNLaun == xZDsUwsVpa){cRmAwMkjVb = true;}
      while(MDIMCdmWwO == rAbPfFyWFX){PiOjQtmnwU = true;}
      while(LRanqonJUw == LRanqonJUw){wZYNAXzHgR = true;}
      while(xZDsUwsVpa == xZDsUwsVpa){ZZxfVteSnu = true;}
      if(YmlRmXuWPR == true){YmlRmXuWPR = false;}
      if(SQtPsrDhNA == true){SQtPsrDhNA = false;}
      if(wQrXwmzOrF == true){wQrXwmzOrF = false;}
      if(jRfVpXeJAT == true){jRfVpXeJAT = false;}
      if(sQtDcfenAb == true){sQtDcfenAb = false;}
      if(sLHpdIuNVA == true){sLHpdIuNVA = false;}
      if(XgeJhAjYZV == true){XgeJhAjYZV = false;}
      if(MtgsGfWouP == true){MtgsGfWouP = false;}
      if(HLOPLXKpqg == true){HLOPLXKpqg = false;}
      if(cRmAwMkjVb == true){cRmAwMkjVb = false;}
      if(wGOePyeOiy == true){wGOePyeOiy = false;}
      if(lFSGsMSOyJ == true){lFSGsMSOyJ = false;}
      if(ptgrruGfxt == true){ptgrruGfxt = false;}
      if(tlTSTAwiAN == true){tlTSTAwiAN = false;}
      if(suHruWygHi == true){suHruWygHi = false;}
      if(sWlLlCZWlU == true){sWlLlCZWlU = false;}
      if(qyQnEzlzmr == true){qyQnEzlzmr = false;}
      if(PiOjQtmnwU == true){PiOjQtmnwU = false;}
      if(wZYNAXzHgR == true){wZYNAXzHgR = false;}
      if(ZZxfVteSnu == true){ZZxfVteSnu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FYLYHDBNCF
{ 
  void lDZQVwSUOb()
  { 
      bool GgmBRVCBOC = false;
      bool GbkaqpEcjh = false;
      bool IudBDejBEO = false;
      bool IntUaweZSj = false;
      bool kFtCYZqpsi = false;
      bool XzTrnLClyl = false;
      bool lBxztRhPAt = false;
      bool LdJAxDBbcc = false;
      bool nsHVqITBfO = false;
      bool ssbgxjItIG = false;
      bool rapzWspTuk = false;
      bool JaJUyrsbIk = false;
      bool yfikASCcCM = false;
      bool tGTVkNCIyx = false;
      bool RAGuESjGhF = false;
      bool qglWILqFyE = false;
      bool qNRipDHmik = false;
      bool ojcKSyZnfh = false;
      bool hutwUNTwNZ = false;
      bool VxJsFEhWFB = false;
      string ypBNfwBaiP;
      string EDgzpLPmkb;
      string EPBQqFuzQq;
      string oMGNBSbznN;
      string ArjfHfmgYx;
      string MPwtNinjVZ;
      string BBKqZqxTyX;
      string jQyXbLeUIL;
      string SOaSeZPLzR;
      string eqdOMyhrGP;
      string iSiBNuQYSB;
      string DSbJGmarMA;
      string bkTfssljKc;
      string dmOscAeZFi;
      string IpsyNLPTHZ;
      string WoeFnxyDIU;
      string JfNoWQEigF;
      string HBldqkqVRh;
      string cSbkFnHIEe;
      string CbQkZbcDax;
      if(ypBNfwBaiP == iSiBNuQYSB){GgmBRVCBOC = true;}
      else if(iSiBNuQYSB == ypBNfwBaiP){rapzWspTuk = true;}
      if(EDgzpLPmkb == DSbJGmarMA){GbkaqpEcjh = true;}
      else if(DSbJGmarMA == EDgzpLPmkb){JaJUyrsbIk = true;}
      if(EPBQqFuzQq == bkTfssljKc){IudBDejBEO = true;}
      else if(bkTfssljKc == EPBQqFuzQq){yfikASCcCM = true;}
      if(oMGNBSbznN == dmOscAeZFi){IntUaweZSj = true;}
      else if(dmOscAeZFi == oMGNBSbznN){tGTVkNCIyx = true;}
      if(ArjfHfmgYx == IpsyNLPTHZ){kFtCYZqpsi = true;}
      else if(IpsyNLPTHZ == ArjfHfmgYx){RAGuESjGhF = true;}
      if(MPwtNinjVZ == WoeFnxyDIU){XzTrnLClyl = true;}
      else if(WoeFnxyDIU == MPwtNinjVZ){qglWILqFyE = true;}
      if(BBKqZqxTyX == JfNoWQEigF){lBxztRhPAt = true;}
      else if(JfNoWQEigF == BBKqZqxTyX){qNRipDHmik = true;}
      if(jQyXbLeUIL == HBldqkqVRh){LdJAxDBbcc = true;}
      if(SOaSeZPLzR == cSbkFnHIEe){nsHVqITBfO = true;}
      if(eqdOMyhrGP == CbQkZbcDax){ssbgxjItIG = true;}
      while(HBldqkqVRh == jQyXbLeUIL){ojcKSyZnfh = true;}
      while(cSbkFnHIEe == cSbkFnHIEe){hutwUNTwNZ = true;}
      while(CbQkZbcDax == CbQkZbcDax){VxJsFEhWFB = true;}
      if(GgmBRVCBOC == true){GgmBRVCBOC = false;}
      if(GbkaqpEcjh == true){GbkaqpEcjh = false;}
      if(IudBDejBEO == true){IudBDejBEO = false;}
      if(IntUaweZSj == true){IntUaweZSj = false;}
      if(kFtCYZqpsi == true){kFtCYZqpsi = false;}
      if(XzTrnLClyl == true){XzTrnLClyl = false;}
      if(lBxztRhPAt == true){lBxztRhPAt = false;}
      if(LdJAxDBbcc == true){LdJAxDBbcc = false;}
      if(nsHVqITBfO == true){nsHVqITBfO = false;}
      if(ssbgxjItIG == true){ssbgxjItIG = false;}
      if(rapzWspTuk == true){rapzWspTuk = false;}
      if(JaJUyrsbIk == true){JaJUyrsbIk = false;}
      if(yfikASCcCM == true){yfikASCcCM = false;}
      if(tGTVkNCIyx == true){tGTVkNCIyx = false;}
      if(RAGuESjGhF == true){RAGuESjGhF = false;}
      if(qglWILqFyE == true){qglWILqFyE = false;}
      if(qNRipDHmik == true){qNRipDHmik = false;}
      if(ojcKSyZnfh == true){ojcKSyZnfh = false;}
      if(hutwUNTwNZ == true){hutwUNTwNZ = false;}
      if(VxJsFEhWFB == true){VxJsFEhWFB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFXRSVYREO
{ 
  void NFGMJljxAH()
  { 
      bool XrxazeWPeE = false;
      bool yErMmMaLnN = false;
      bool kjnXLmrEDI = false;
      bool mHmpDAQZxP = false;
      bool dPMkXuXAhw = false;
      bool KNeUNmDZPM = false;
      bool mSMVRpRBJl = false;
      bool uBNYjUXCAP = false;
      bool OqVGyZcSbP = false;
      bool wqKkcKDpTg = false;
      bool dWqwBJAGjs = false;
      bool OBYAxuwGXq = false;
      bool MzZsoEpbuY = false;
      bool QgiSkrzZFo = false;
      bool YWhiBuRKng = false;
      bool OxSbTewyGw = false;
      bool SXKKbhRGOE = false;
      bool wWAiSpQqrs = false;
      bool mfnNKTOGyG = false;
      bool uBSIVBLWGS = false;
      string kUWhtIViGy;
      string usbuKhImyg;
      string QbZSupVAMo;
      string JIzwzoLUbr;
      string MtrYzwXjjQ;
      string VcPikJuEmD;
      string mVWRomsewV;
      string VnLFUWiASy;
      string SkPuSfrPLp;
      string tHgXEpXaiL;
      string CsmOthQJNN;
      string ZtkokBGayJ;
      string tdSFaOGnAe;
      string yIRGuZyBAk;
      string OhCxQAVrlD;
      string jxcZQYZhmf;
      string acIiPQbdtL;
      string DFZMtMaUoa;
      string rOBxtBfrpV;
      string AQNUJlYShz;
      if(kUWhtIViGy == CsmOthQJNN){XrxazeWPeE = true;}
      else if(CsmOthQJNN == kUWhtIViGy){dWqwBJAGjs = true;}
      if(usbuKhImyg == ZtkokBGayJ){yErMmMaLnN = true;}
      else if(ZtkokBGayJ == usbuKhImyg){OBYAxuwGXq = true;}
      if(QbZSupVAMo == tdSFaOGnAe){kjnXLmrEDI = true;}
      else if(tdSFaOGnAe == QbZSupVAMo){MzZsoEpbuY = true;}
      if(JIzwzoLUbr == yIRGuZyBAk){mHmpDAQZxP = true;}
      else if(yIRGuZyBAk == JIzwzoLUbr){QgiSkrzZFo = true;}
      if(MtrYzwXjjQ == OhCxQAVrlD){dPMkXuXAhw = true;}
      else if(OhCxQAVrlD == MtrYzwXjjQ){YWhiBuRKng = true;}
      if(VcPikJuEmD == jxcZQYZhmf){KNeUNmDZPM = true;}
      else if(jxcZQYZhmf == VcPikJuEmD){OxSbTewyGw = true;}
      if(mVWRomsewV == acIiPQbdtL){mSMVRpRBJl = true;}
      else if(acIiPQbdtL == mVWRomsewV){SXKKbhRGOE = true;}
      if(VnLFUWiASy == DFZMtMaUoa){uBNYjUXCAP = true;}
      if(SkPuSfrPLp == rOBxtBfrpV){OqVGyZcSbP = true;}
      if(tHgXEpXaiL == AQNUJlYShz){wqKkcKDpTg = true;}
      while(DFZMtMaUoa == VnLFUWiASy){wWAiSpQqrs = true;}
      while(rOBxtBfrpV == rOBxtBfrpV){mfnNKTOGyG = true;}
      while(AQNUJlYShz == AQNUJlYShz){uBSIVBLWGS = true;}
      if(XrxazeWPeE == true){XrxazeWPeE = false;}
      if(yErMmMaLnN == true){yErMmMaLnN = false;}
      if(kjnXLmrEDI == true){kjnXLmrEDI = false;}
      if(mHmpDAQZxP == true){mHmpDAQZxP = false;}
      if(dPMkXuXAhw == true){dPMkXuXAhw = false;}
      if(KNeUNmDZPM == true){KNeUNmDZPM = false;}
      if(mSMVRpRBJl == true){mSMVRpRBJl = false;}
      if(uBNYjUXCAP == true){uBNYjUXCAP = false;}
      if(OqVGyZcSbP == true){OqVGyZcSbP = false;}
      if(wqKkcKDpTg == true){wqKkcKDpTg = false;}
      if(dWqwBJAGjs == true){dWqwBJAGjs = false;}
      if(OBYAxuwGXq == true){OBYAxuwGXq = false;}
      if(MzZsoEpbuY == true){MzZsoEpbuY = false;}
      if(QgiSkrzZFo == true){QgiSkrzZFo = false;}
      if(YWhiBuRKng == true){YWhiBuRKng = false;}
      if(OxSbTewyGw == true){OxSbTewyGw = false;}
      if(SXKKbhRGOE == true){SXKKbhRGOE = false;}
      if(wWAiSpQqrs == true){wWAiSpQqrs = false;}
      if(mfnNKTOGyG == true){mfnNKTOGyG = false;}
      if(uBSIVBLWGS == true){uBSIVBLWGS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLIISAFAVN
{ 
  void ZDEDYywAhK()
  { 
      bool AqGAoohhnS = false;
      bool brYQrnPkme = false;
      bool wUNpRkrMfE = false;
      bool lKTaYwmQZl = false;
      bool xefibTAtqN = false;
      bool kehDLfdPiD = false;
      bool xVCigQYyrw = false;
      bool BzKAhQndNy = false;
      bool jxURTHbQOs = false;
      bool RWgWoacwCK = false;
      bool uCCtMkUhUu = false;
      bool qABjTzAkPY = false;
      bool oHizddRmLH = false;
      bool nqaDDguaFi = false;
      bool ltuTBRUxDo = false;
      bool aqgcVmSCQh = false;
      bool SgWNHzYygl = false;
      bool EZffmtMPyM = false;
      bool IUjVfwKxhQ = false;
      bool NrJWPFXgLB = false;
      string jqwxBtfJZL;
      string zFxVJjIajY;
      string sflxAKJVHs;
      string IBTjLztEKb;
      string HsQlkMHSOQ;
      string fuWAUEEzwq;
      string jKCgCxkMJJ;
      string pDQHQAOzLn;
      string DqGpNNeTOH;
      string uuISrwpjjm;
      string atJFaceOiU;
      string oFnHmrELSo;
      string SRxBOttxOT;
      string JePXNIhBPk;
      string iPktSoHAfz;
      string rdQtUIwHpf;
      string hhAOKKoPte;
      string KDwhGCgDiY;
      string msRObeNUCE;
      string MZKjCBPViI;
      if(jqwxBtfJZL == atJFaceOiU){AqGAoohhnS = true;}
      else if(atJFaceOiU == jqwxBtfJZL){uCCtMkUhUu = true;}
      if(zFxVJjIajY == oFnHmrELSo){brYQrnPkme = true;}
      else if(oFnHmrELSo == zFxVJjIajY){qABjTzAkPY = true;}
      if(sflxAKJVHs == SRxBOttxOT){wUNpRkrMfE = true;}
      else if(SRxBOttxOT == sflxAKJVHs){oHizddRmLH = true;}
      if(IBTjLztEKb == JePXNIhBPk){lKTaYwmQZl = true;}
      else if(JePXNIhBPk == IBTjLztEKb){nqaDDguaFi = true;}
      if(HsQlkMHSOQ == iPktSoHAfz){xefibTAtqN = true;}
      else if(iPktSoHAfz == HsQlkMHSOQ){ltuTBRUxDo = true;}
      if(fuWAUEEzwq == rdQtUIwHpf){kehDLfdPiD = true;}
      else if(rdQtUIwHpf == fuWAUEEzwq){aqgcVmSCQh = true;}
      if(jKCgCxkMJJ == hhAOKKoPte){xVCigQYyrw = true;}
      else if(hhAOKKoPte == jKCgCxkMJJ){SgWNHzYygl = true;}
      if(pDQHQAOzLn == KDwhGCgDiY){BzKAhQndNy = true;}
      if(DqGpNNeTOH == msRObeNUCE){jxURTHbQOs = true;}
      if(uuISrwpjjm == MZKjCBPViI){RWgWoacwCK = true;}
      while(KDwhGCgDiY == pDQHQAOzLn){EZffmtMPyM = true;}
      while(msRObeNUCE == msRObeNUCE){IUjVfwKxhQ = true;}
      while(MZKjCBPViI == MZKjCBPViI){NrJWPFXgLB = true;}
      if(AqGAoohhnS == true){AqGAoohhnS = false;}
      if(brYQrnPkme == true){brYQrnPkme = false;}
      if(wUNpRkrMfE == true){wUNpRkrMfE = false;}
      if(lKTaYwmQZl == true){lKTaYwmQZl = false;}
      if(xefibTAtqN == true){xefibTAtqN = false;}
      if(kehDLfdPiD == true){kehDLfdPiD = false;}
      if(xVCigQYyrw == true){xVCigQYyrw = false;}
      if(BzKAhQndNy == true){BzKAhQndNy = false;}
      if(jxURTHbQOs == true){jxURTHbQOs = false;}
      if(RWgWoacwCK == true){RWgWoacwCK = false;}
      if(uCCtMkUhUu == true){uCCtMkUhUu = false;}
      if(qABjTzAkPY == true){qABjTzAkPY = false;}
      if(oHizddRmLH == true){oHizddRmLH = false;}
      if(nqaDDguaFi == true){nqaDDguaFi = false;}
      if(ltuTBRUxDo == true){ltuTBRUxDo = false;}
      if(aqgcVmSCQh == true){aqgcVmSCQh = false;}
      if(SgWNHzYygl == true){SgWNHzYygl = false;}
      if(EZffmtMPyM == true){EZffmtMPyM = false;}
      if(IUjVfwKxhQ == true){IUjVfwKxhQ = false;}
      if(NrJWPFXgLB == true){NrJWPFXgLB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTIOWWPSTR
{ 
  void aOZmYBKSOd()
  { 
      bool DdIEqtxReS = false;
      bool brqsiHhLVY = false;
      bool acFSbJddXm = false;
      bool Bjlrqfidly = false;
      bool OkGUfdjkNQ = false;
      bool pbMNLZXobg = false;
      bool QTtrRqGyBD = false;
      bool YEYXKoVkmx = false;
      bool YrPGwYXXgQ = false;
      bool HsBEhuqODn = false;
      bool XljKrkDoDW = false;
      bool DmCeIYDnus = false;
      bool ThQkueDUoP = false;
      bool xHgyZmIEOL = false;
      bool UhUKMTqWwI = false;
      bool qDTKUoUyOM = false;
      bool hizmYwGEFU = false;
      bool QyYjXlNGYb = false;
      bool ngXgYtmWdj = false;
      bool SJpCcliglP = false;
      string DWIiFnsigO;
      string kLgVCZtNdy;
      string HEHtrLpxuO;
      string VpopMacEkK;
      string YfClWfGacZ;
      string PePiwzONqs;
      string yunSstVqIa;
      string xocSYbBVXM;
      string FPUUyqaGsN;
      string MONqMdqirb;
      string JPRCcZBwJU;
      string xspdniaSUB;
      string TPxuOiakGu;
      string jScwCoxSrX;
      string odwXQTXjDc;
      string CYOqItRVnt;
      string zQpOkdPtaz;
      string kIawLoSZet;
      string KqhdrLDlnI;
      string WbexYYnhml;
      if(DWIiFnsigO == JPRCcZBwJU){DdIEqtxReS = true;}
      else if(JPRCcZBwJU == DWIiFnsigO){XljKrkDoDW = true;}
      if(kLgVCZtNdy == xspdniaSUB){brqsiHhLVY = true;}
      else if(xspdniaSUB == kLgVCZtNdy){DmCeIYDnus = true;}
      if(HEHtrLpxuO == TPxuOiakGu){acFSbJddXm = true;}
      else if(TPxuOiakGu == HEHtrLpxuO){ThQkueDUoP = true;}
      if(VpopMacEkK == jScwCoxSrX){Bjlrqfidly = true;}
      else if(jScwCoxSrX == VpopMacEkK){xHgyZmIEOL = true;}
      if(YfClWfGacZ == odwXQTXjDc){OkGUfdjkNQ = true;}
      else if(odwXQTXjDc == YfClWfGacZ){UhUKMTqWwI = true;}
      if(PePiwzONqs == CYOqItRVnt){pbMNLZXobg = true;}
      else if(CYOqItRVnt == PePiwzONqs){qDTKUoUyOM = true;}
      if(yunSstVqIa == zQpOkdPtaz){QTtrRqGyBD = true;}
      else if(zQpOkdPtaz == yunSstVqIa){hizmYwGEFU = true;}
      if(xocSYbBVXM == kIawLoSZet){YEYXKoVkmx = true;}
      if(FPUUyqaGsN == KqhdrLDlnI){YrPGwYXXgQ = true;}
      if(MONqMdqirb == WbexYYnhml){HsBEhuqODn = true;}
      while(kIawLoSZet == xocSYbBVXM){QyYjXlNGYb = true;}
      while(KqhdrLDlnI == KqhdrLDlnI){ngXgYtmWdj = true;}
      while(WbexYYnhml == WbexYYnhml){SJpCcliglP = true;}
      if(DdIEqtxReS == true){DdIEqtxReS = false;}
      if(brqsiHhLVY == true){brqsiHhLVY = false;}
      if(acFSbJddXm == true){acFSbJddXm = false;}
      if(Bjlrqfidly == true){Bjlrqfidly = false;}
      if(OkGUfdjkNQ == true){OkGUfdjkNQ = false;}
      if(pbMNLZXobg == true){pbMNLZXobg = false;}
      if(QTtrRqGyBD == true){QTtrRqGyBD = false;}
      if(YEYXKoVkmx == true){YEYXKoVkmx = false;}
      if(YrPGwYXXgQ == true){YrPGwYXXgQ = false;}
      if(HsBEhuqODn == true){HsBEhuqODn = false;}
      if(XljKrkDoDW == true){XljKrkDoDW = false;}
      if(DmCeIYDnus == true){DmCeIYDnus = false;}
      if(ThQkueDUoP == true){ThQkueDUoP = false;}
      if(xHgyZmIEOL == true){xHgyZmIEOL = false;}
      if(UhUKMTqWwI == true){UhUKMTqWwI = false;}
      if(qDTKUoUyOM == true){qDTKUoUyOM = false;}
      if(hizmYwGEFU == true){hizmYwGEFU = false;}
      if(QyYjXlNGYb == true){QyYjXlNGYb = false;}
      if(ngXgYtmWdj == true){ngXgYtmWdj = false;}
      if(SJpCcliglP == true){SJpCcliglP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWUIBLMKRC
{ 
  void IOpkcjYBqI()
  { 
      bool hjWPaJAiBN = false;
      bool LxdAQjPKZJ = false;
      bool FljMmZgMLI = false;
      bool xZYdKRSrmN = false;
      bool PKyteCKdqf = false;
      bool zUAJTwzKbB = false;
      bool bmWsPlYAoz = false;
      bool RXWLttmphj = false;
      bool ODVfJcYOJO = false;
      bool RIPklcnFds = false;
      bool dKnqNaxnPY = false;
      bool JJbqlYRpim = false;
      bool MJpagIHkZR = false;
      bool GgMnGEOdRh = false;
      bool fjyjEIfYzM = false;
      bool KxWpfTUMKF = false;
      bool TLOyRcxnjg = false;
      bool JnXBHbKFVY = false;
      bool cilNGJKVIl = false;
      bool jBSMOTVARb = false;
      string AfNBtGnqXV;
      string GhNMlcYbcP;
      string qOPCHsoaVV;
      string tsyTLudait;
      string RnfJiTXJxw;
      string naLlOkQKtA;
      string RNVBbMjsBq;
      string yxshxDiFTm;
      string VedYhTgLFZ;
      string dTghcERegV;
      string jdIFxqgdoL;
      string CKpGeljwSI;
      string fXmaMeQKFr;
      string kEYyDqWXaq;
      string lDWtXTcZDq;
      string UULXpMpgsS;
      string ZWYwZylrDn;
      string PLUbWbAsDr;
      string BpHOWPsAHq;
      string AoeIQOeZTY;
      if(AfNBtGnqXV == jdIFxqgdoL){hjWPaJAiBN = true;}
      else if(jdIFxqgdoL == AfNBtGnqXV){dKnqNaxnPY = true;}
      if(GhNMlcYbcP == CKpGeljwSI){LxdAQjPKZJ = true;}
      else if(CKpGeljwSI == GhNMlcYbcP){JJbqlYRpim = true;}
      if(qOPCHsoaVV == fXmaMeQKFr){FljMmZgMLI = true;}
      else if(fXmaMeQKFr == qOPCHsoaVV){MJpagIHkZR = true;}
      if(tsyTLudait == kEYyDqWXaq){xZYdKRSrmN = true;}
      else if(kEYyDqWXaq == tsyTLudait){GgMnGEOdRh = true;}
      if(RnfJiTXJxw == lDWtXTcZDq){PKyteCKdqf = true;}
      else if(lDWtXTcZDq == RnfJiTXJxw){fjyjEIfYzM = true;}
      if(naLlOkQKtA == UULXpMpgsS){zUAJTwzKbB = true;}
      else if(UULXpMpgsS == naLlOkQKtA){KxWpfTUMKF = true;}
      if(RNVBbMjsBq == ZWYwZylrDn){bmWsPlYAoz = true;}
      else if(ZWYwZylrDn == RNVBbMjsBq){TLOyRcxnjg = true;}
      if(yxshxDiFTm == PLUbWbAsDr){RXWLttmphj = true;}
      if(VedYhTgLFZ == BpHOWPsAHq){ODVfJcYOJO = true;}
      if(dTghcERegV == AoeIQOeZTY){RIPklcnFds = true;}
      while(PLUbWbAsDr == yxshxDiFTm){JnXBHbKFVY = true;}
      while(BpHOWPsAHq == BpHOWPsAHq){cilNGJKVIl = true;}
      while(AoeIQOeZTY == AoeIQOeZTY){jBSMOTVARb = true;}
      if(hjWPaJAiBN == true){hjWPaJAiBN = false;}
      if(LxdAQjPKZJ == true){LxdAQjPKZJ = false;}
      if(FljMmZgMLI == true){FljMmZgMLI = false;}
      if(xZYdKRSrmN == true){xZYdKRSrmN = false;}
      if(PKyteCKdqf == true){PKyteCKdqf = false;}
      if(zUAJTwzKbB == true){zUAJTwzKbB = false;}
      if(bmWsPlYAoz == true){bmWsPlYAoz = false;}
      if(RXWLttmphj == true){RXWLttmphj = false;}
      if(ODVfJcYOJO == true){ODVfJcYOJO = false;}
      if(RIPklcnFds == true){RIPklcnFds = false;}
      if(dKnqNaxnPY == true){dKnqNaxnPY = false;}
      if(JJbqlYRpim == true){JJbqlYRpim = false;}
      if(MJpagIHkZR == true){MJpagIHkZR = false;}
      if(GgMnGEOdRh == true){GgMnGEOdRh = false;}
      if(fjyjEIfYzM == true){fjyjEIfYzM = false;}
      if(KxWpfTUMKF == true){KxWpfTUMKF = false;}
      if(TLOyRcxnjg == true){TLOyRcxnjg = false;}
      if(JnXBHbKFVY == true){JnXBHbKFVY = false;}
      if(cilNGJKVIl == true){cilNGJKVIl = false;}
      if(jBSMOTVARb == true){jBSMOTVARb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVTFUQLOQK
{ 
  void aQInFXrblA()
  { 
      bool ZasfmVgonz = false;
      bool uxcOXlbngU = false;
      bool IxoHNqhlDa = false;
      bool AxKGUIywIf = false;
      bool RpVsRioSGb = false;
      bool RkXtzcklRu = false;
      bool mtkMzymVtP = false;
      bool mfeADRbwoe = false;
      bool CPfaJOYPHq = false;
      bool WMdNrWEJtT = false;
      bool uSXqokGXqg = false;
      bool BowmsXOJCj = false;
      bool YWOCrZCRHg = false;
      bool NSCVijqnlX = false;
      bool HAYaphQqTU = false;
      bool HtGJtYEUzO = false;
      bool ioPKSimZDI = false;
      bool faWdcYymMK = false;
      bool ILxmYSLraJ = false;
      bool fVoXoSkNHH = false;
      string XThOQSrYuM;
      string CRXSPkSnFR;
      string lAxHmdnDlK;
      string ndQOpdiULu;
      string inABgoqcXB;
      string hioFOXVZbl;
      string dnmkYYBJbk;
      string BybKiyzwZx;
      string mKekbFnKzS;
      string HJrZQtAOcI;
      string mhBmzjGdWQ;
      string XZzezTICIT;
      string jpJJcrFCtn;
      string xkSRKEJrkr;
      string yJnithJNZx;
      string lyFJYxXqKG;
      string dEjiTmHhUt;
      string JPQQUZCZOu;
      string irbwCyeJrM;
      string fRhdNtZFPH;
      if(XThOQSrYuM == mhBmzjGdWQ){ZasfmVgonz = true;}
      else if(mhBmzjGdWQ == XThOQSrYuM){uSXqokGXqg = true;}
      if(CRXSPkSnFR == XZzezTICIT){uxcOXlbngU = true;}
      else if(XZzezTICIT == CRXSPkSnFR){BowmsXOJCj = true;}
      if(lAxHmdnDlK == jpJJcrFCtn){IxoHNqhlDa = true;}
      else if(jpJJcrFCtn == lAxHmdnDlK){YWOCrZCRHg = true;}
      if(ndQOpdiULu == xkSRKEJrkr){AxKGUIywIf = true;}
      else if(xkSRKEJrkr == ndQOpdiULu){NSCVijqnlX = true;}
      if(inABgoqcXB == yJnithJNZx){RpVsRioSGb = true;}
      else if(yJnithJNZx == inABgoqcXB){HAYaphQqTU = true;}
      if(hioFOXVZbl == lyFJYxXqKG){RkXtzcklRu = true;}
      else if(lyFJYxXqKG == hioFOXVZbl){HtGJtYEUzO = true;}
      if(dnmkYYBJbk == dEjiTmHhUt){mtkMzymVtP = true;}
      else if(dEjiTmHhUt == dnmkYYBJbk){ioPKSimZDI = true;}
      if(BybKiyzwZx == JPQQUZCZOu){mfeADRbwoe = true;}
      if(mKekbFnKzS == irbwCyeJrM){CPfaJOYPHq = true;}
      if(HJrZQtAOcI == fRhdNtZFPH){WMdNrWEJtT = true;}
      while(JPQQUZCZOu == BybKiyzwZx){faWdcYymMK = true;}
      while(irbwCyeJrM == irbwCyeJrM){ILxmYSLraJ = true;}
      while(fRhdNtZFPH == fRhdNtZFPH){fVoXoSkNHH = true;}
      if(ZasfmVgonz == true){ZasfmVgonz = false;}
      if(uxcOXlbngU == true){uxcOXlbngU = false;}
      if(IxoHNqhlDa == true){IxoHNqhlDa = false;}
      if(AxKGUIywIf == true){AxKGUIywIf = false;}
      if(RpVsRioSGb == true){RpVsRioSGb = false;}
      if(RkXtzcklRu == true){RkXtzcklRu = false;}
      if(mtkMzymVtP == true){mtkMzymVtP = false;}
      if(mfeADRbwoe == true){mfeADRbwoe = false;}
      if(CPfaJOYPHq == true){CPfaJOYPHq = false;}
      if(WMdNrWEJtT == true){WMdNrWEJtT = false;}
      if(uSXqokGXqg == true){uSXqokGXqg = false;}
      if(BowmsXOJCj == true){BowmsXOJCj = false;}
      if(YWOCrZCRHg == true){YWOCrZCRHg = false;}
      if(NSCVijqnlX == true){NSCVijqnlX = false;}
      if(HAYaphQqTU == true){HAYaphQqTU = false;}
      if(HtGJtYEUzO == true){HtGJtYEUzO = false;}
      if(ioPKSimZDI == true){ioPKSimZDI = false;}
      if(faWdcYymMK == true){faWdcYymMK = false;}
      if(ILxmYSLraJ == true){ILxmYSLraJ = false;}
      if(fVoXoSkNHH == true){fVoXoSkNHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBTEDSIYPM
{ 
  void DXWsZPXHdN()
  { 
      bool btUciKZODn = false;
      bool dswtSBbxqZ = false;
      bool xEjEjrAZRm = false;
      bool CCjJGWiPIn = false;
      bool IHsosQLyLf = false;
      bool FzloLXKPrp = false;
      bool KzwQkbImnu = false;
      bool SMoDQoLtKT = false;
      bool gCOlgCPuyi = false;
      bool LSXRdIKbDQ = false;
      bool IXJPMsKiXV = false;
      bool LPEXIHkKih = false;
      bool MNnFiAnXYI = false;
      bool djqtLIryZn = false;
      bool rfWcXwNzIV = false;
      bool XAsUEtjEgM = false;
      bool EmKPqbYKMz = false;
      bool OljupfpLhm = false;
      bool loOCkcpVoQ = false;
      bool YmRNiFVHku = false;
      string FOkOEcpieT;
      string rudBBbKQxT;
      string qOaLOqWOtB;
      string HCgRXnNFgN;
      string ujdJQXanDW;
      string KTASapnZAM;
      string GbodMoOMcM;
      string NFiiXHkRtq;
      string QhLWqnCOph;
      string AnFTHTuAwb;
      string JOKpJEjQtT;
      string EVfIwXPRlX;
      string lzVuMYzPaD;
      string LkUSgCWVNl;
      string DlTWcdHwWj;
      string EdNYoJrOcj;
      string FUopHTBNbt;
      string AsDzUAfzSi;
      string RDrqzhWwdW;
      string JHrdghxdOI;
      if(FOkOEcpieT == JOKpJEjQtT){btUciKZODn = true;}
      else if(JOKpJEjQtT == FOkOEcpieT){IXJPMsKiXV = true;}
      if(rudBBbKQxT == EVfIwXPRlX){dswtSBbxqZ = true;}
      else if(EVfIwXPRlX == rudBBbKQxT){LPEXIHkKih = true;}
      if(qOaLOqWOtB == lzVuMYzPaD){xEjEjrAZRm = true;}
      else if(lzVuMYzPaD == qOaLOqWOtB){MNnFiAnXYI = true;}
      if(HCgRXnNFgN == LkUSgCWVNl){CCjJGWiPIn = true;}
      else if(LkUSgCWVNl == HCgRXnNFgN){djqtLIryZn = true;}
      if(ujdJQXanDW == DlTWcdHwWj){IHsosQLyLf = true;}
      else if(DlTWcdHwWj == ujdJQXanDW){rfWcXwNzIV = true;}
      if(KTASapnZAM == EdNYoJrOcj){FzloLXKPrp = true;}
      else if(EdNYoJrOcj == KTASapnZAM){XAsUEtjEgM = true;}
      if(GbodMoOMcM == FUopHTBNbt){KzwQkbImnu = true;}
      else if(FUopHTBNbt == GbodMoOMcM){EmKPqbYKMz = true;}
      if(NFiiXHkRtq == AsDzUAfzSi){SMoDQoLtKT = true;}
      if(QhLWqnCOph == RDrqzhWwdW){gCOlgCPuyi = true;}
      if(AnFTHTuAwb == JHrdghxdOI){LSXRdIKbDQ = true;}
      while(AsDzUAfzSi == NFiiXHkRtq){OljupfpLhm = true;}
      while(RDrqzhWwdW == RDrqzhWwdW){loOCkcpVoQ = true;}
      while(JHrdghxdOI == JHrdghxdOI){YmRNiFVHku = true;}
      if(btUciKZODn == true){btUciKZODn = false;}
      if(dswtSBbxqZ == true){dswtSBbxqZ = false;}
      if(xEjEjrAZRm == true){xEjEjrAZRm = false;}
      if(CCjJGWiPIn == true){CCjJGWiPIn = false;}
      if(IHsosQLyLf == true){IHsosQLyLf = false;}
      if(FzloLXKPrp == true){FzloLXKPrp = false;}
      if(KzwQkbImnu == true){KzwQkbImnu = false;}
      if(SMoDQoLtKT == true){SMoDQoLtKT = false;}
      if(gCOlgCPuyi == true){gCOlgCPuyi = false;}
      if(LSXRdIKbDQ == true){LSXRdIKbDQ = false;}
      if(IXJPMsKiXV == true){IXJPMsKiXV = false;}
      if(LPEXIHkKih == true){LPEXIHkKih = false;}
      if(MNnFiAnXYI == true){MNnFiAnXYI = false;}
      if(djqtLIryZn == true){djqtLIryZn = false;}
      if(rfWcXwNzIV == true){rfWcXwNzIV = false;}
      if(XAsUEtjEgM == true){XAsUEtjEgM = false;}
      if(EmKPqbYKMz == true){EmKPqbYKMz = false;}
      if(OljupfpLhm == true){OljupfpLhm = false;}
      if(loOCkcpVoQ == true){loOCkcpVoQ = false;}
      if(YmRNiFVHku == true){YmRNiFVHku = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BPQUZFMIGG
{ 
  void cFTYnkKLWp()
  { 
      bool OfVHELkhWl = false;
      bool lrejLKixsr = false;
      bool iyXXhXCmJd = false;
      bool KoYXqHVful = false;
      bool hxeUCKxPlS = false;
      bool fcToGQHyZf = false;
      bool JxXsawTGrD = false;
      bool oDCGJkTDUW = false;
      bool alBqyhVjQa = false;
      bool AWFOckZlsF = false;
      bool qpWidbaMeV = false;
      bool wDcCFWwgus = false;
      bool ajpQDRxmdY = false;
      bool LhKOfkPRNV = false;
      bool HJEuewsDJG = false;
      bool orqzeHAFfL = false;
      bool emiGJNsNWU = false;
      bool GdTYlRetlG = false;
      bool XtcWjSqKjX = false;
      bool jJlBpTaylQ = false;
      string FHqEpWTuPh;
      string bBlDPNkqyY;
      string bDcVoyXVQl;
      string MxipTLrmaW;
      string FhQQKPutQU;
      string bVaXuBdVOq;
      string yxdcVdSwjD;
      string VyQbTsmMLZ;
      string CdEwJqVKuS;
      string gVXiXHEmuf;
      string wzJNydEzEB;
      string ORKooTshSe;
      string HIARVzahDM;
      string ozRecCTqxf;
      string lWFsEPLhtE;
      string NVUPXnzrqz;
      string CWwrLOAeLl;
      string zCkmskCGNG;
      string nrnzyTeBHn;
      string DbzxcOZNho;
      if(FHqEpWTuPh == wzJNydEzEB){OfVHELkhWl = true;}
      else if(wzJNydEzEB == FHqEpWTuPh){qpWidbaMeV = true;}
      if(bBlDPNkqyY == ORKooTshSe){lrejLKixsr = true;}
      else if(ORKooTshSe == bBlDPNkqyY){wDcCFWwgus = true;}
      if(bDcVoyXVQl == HIARVzahDM){iyXXhXCmJd = true;}
      else if(HIARVzahDM == bDcVoyXVQl){ajpQDRxmdY = true;}
      if(MxipTLrmaW == ozRecCTqxf){KoYXqHVful = true;}
      else if(ozRecCTqxf == MxipTLrmaW){LhKOfkPRNV = true;}
      if(FhQQKPutQU == lWFsEPLhtE){hxeUCKxPlS = true;}
      else if(lWFsEPLhtE == FhQQKPutQU){HJEuewsDJG = true;}
      if(bVaXuBdVOq == NVUPXnzrqz){fcToGQHyZf = true;}
      else if(NVUPXnzrqz == bVaXuBdVOq){orqzeHAFfL = true;}
      if(yxdcVdSwjD == CWwrLOAeLl){JxXsawTGrD = true;}
      else if(CWwrLOAeLl == yxdcVdSwjD){emiGJNsNWU = true;}
      if(VyQbTsmMLZ == zCkmskCGNG){oDCGJkTDUW = true;}
      if(CdEwJqVKuS == nrnzyTeBHn){alBqyhVjQa = true;}
      if(gVXiXHEmuf == DbzxcOZNho){AWFOckZlsF = true;}
      while(zCkmskCGNG == VyQbTsmMLZ){GdTYlRetlG = true;}
      while(nrnzyTeBHn == nrnzyTeBHn){XtcWjSqKjX = true;}
      while(DbzxcOZNho == DbzxcOZNho){jJlBpTaylQ = true;}
      if(OfVHELkhWl == true){OfVHELkhWl = false;}
      if(lrejLKixsr == true){lrejLKixsr = false;}
      if(iyXXhXCmJd == true){iyXXhXCmJd = false;}
      if(KoYXqHVful == true){KoYXqHVful = false;}
      if(hxeUCKxPlS == true){hxeUCKxPlS = false;}
      if(fcToGQHyZf == true){fcToGQHyZf = false;}
      if(JxXsawTGrD == true){JxXsawTGrD = false;}
      if(oDCGJkTDUW == true){oDCGJkTDUW = false;}
      if(alBqyhVjQa == true){alBqyhVjQa = false;}
      if(AWFOckZlsF == true){AWFOckZlsF = false;}
      if(qpWidbaMeV == true){qpWidbaMeV = false;}
      if(wDcCFWwgus == true){wDcCFWwgus = false;}
      if(ajpQDRxmdY == true){ajpQDRxmdY = false;}
      if(LhKOfkPRNV == true){LhKOfkPRNV = false;}
      if(HJEuewsDJG == true){HJEuewsDJG = false;}
      if(orqzeHAFfL == true){orqzeHAFfL = false;}
      if(emiGJNsNWU == true){emiGJNsNWU = false;}
      if(GdTYlRetlG == true){GdTYlRetlG = false;}
      if(XtcWjSqKjX == true){XtcWjSqKjX = false;}
      if(jJlBpTaylQ == true){jJlBpTaylQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVQFMPAWSW
{ 
  void rgQNYYnzKs()
  { 
      bool QhbgwiVihU = false;
      bool SyJCThJokh = false;
      bool nDPsISmeFe = false;
      bool oehZtJnImP = false;
      bool JVPDQktTaz = false;
      bool bYeRnMSiYd = false;
      bool uqcCfnPiIK = false;
      bool tBBVYRmLbW = false;
      bool YTDGDPAPlg = false;
      bool qFiITSrNXc = false;
      bool VKKQEaWJsV = false;
      bool YHGBFbmWyP = false;
      bool mzwaSoRsBG = false;
      bool ZZnyBNIlBc = false;
      bool spWPIiyhDr = false;
      bool eVOHpVNjxP = false;
      bool IdIlwySIAq = false;
      bool SAUVWxcgSj = false;
      bool pjoIbDLgIf = false;
      bool zYnlTOhjSJ = false;
      string TfPqdhXFCK;
      string sHDptWintj;
      string JgoWzYxEje;
      string LrhCbEAbnn;
      string FBNwNldxfz;
      string cNfFympsqE;
      string kSUWyBYANp;
      string WHzFdISsIM;
      string tzYkCyMbDo;
      string NHjjDmfqxM;
      string MdjocVOZap;
      string TwjdJktiUA;
      string nxwXbPWPBq;
      string bbuwAQPjIg;
      string jlANURWGZS;
      string swWxXPgLMM;
      string yyXjNrBndr;
      string VJamPCwhCK;
      string rQoiyeExYj;
      string jDWuhkNQAb;
      if(TfPqdhXFCK == MdjocVOZap){QhbgwiVihU = true;}
      else if(MdjocVOZap == TfPqdhXFCK){VKKQEaWJsV = true;}
      if(sHDptWintj == TwjdJktiUA){SyJCThJokh = true;}
      else if(TwjdJktiUA == sHDptWintj){YHGBFbmWyP = true;}
      if(JgoWzYxEje == nxwXbPWPBq){nDPsISmeFe = true;}
      else if(nxwXbPWPBq == JgoWzYxEje){mzwaSoRsBG = true;}
      if(LrhCbEAbnn == bbuwAQPjIg){oehZtJnImP = true;}
      else if(bbuwAQPjIg == LrhCbEAbnn){ZZnyBNIlBc = true;}
      if(FBNwNldxfz == jlANURWGZS){JVPDQktTaz = true;}
      else if(jlANURWGZS == FBNwNldxfz){spWPIiyhDr = true;}
      if(cNfFympsqE == swWxXPgLMM){bYeRnMSiYd = true;}
      else if(swWxXPgLMM == cNfFympsqE){eVOHpVNjxP = true;}
      if(kSUWyBYANp == yyXjNrBndr){uqcCfnPiIK = true;}
      else if(yyXjNrBndr == kSUWyBYANp){IdIlwySIAq = true;}
      if(WHzFdISsIM == VJamPCwhCK){tBBVYRmLbW = true;}
      if(tzYkCyMbDo == rQoiyeExYj){YTDGDPAPlg = true;}
      if(NHjjDmfqxM == jDWuhkNQAb){qFiITSrNXc = true;}
      while(VJamPCwhCK == WHzFdISsIM){SAUVWxcgSj = true;}
      while(rQoiyeExYj == rQoiyeExYj){pjoIbDLgIf = true;}
      while(jDWuhkNQAb == jDWuhkNQAb){zYnlTOhjSJ = true;}
      if(QhbgwiVihU == true){QhbgwiVihU = false;}
      if(SyJCThJokh == true){SyJCThJokh = false;}
      if(nDPsISmeFe == true){nDPsISmeFe = false;}
      if(oehZtJnImP == true){oehZtJnImP = false;}
      if(JVPDQktTaz == true){JVPDQktTaz = false;}
      if(bYeRnMSiYd == true){bYeRnMSiYd = false;}
      if(uqcCfnPiIK == true){uqcCfnPiIK = false;}
      if(tBBVYRmLbW == true){tBBVYRmLbW = false;}
      if(YTDGDPAPlg == true){YTDGDPAPlg = false;}
      if(qFiITSrNXc == true){qFiITSrNXc = false;}
      if(VKKQEaWJsV == true){VKKQEaWJsV = false;}
      if(YHGBFbmWyP == true){YHGBFbmWyP = false;}
      if(mzwaSoRsBG == true){mzwaSoRsBG = false;}
      if(ZZnyBNIlBc == true){ZZnyBNIlBc = false;}
      if(spWPIiyhDr == true){spWPIiyhDr = false;}
      if(eVOHpVNjxP == true){eVOHpVNjxP = false;}
      if(IdIlwySIAq == true){IdIlwySIAq = false;}
      if(SAUVWxcgSj == true){SAUVWxcgSj = false;}
      if(pjoIbDLgIf == true){pjoIbDLgIf = false;}
      if(zYnlTOhjSJ == true){zYnlTOhjSJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THQDMSEYAE
{ 
  void RrxIKyKWsH()
  { 
      bool HeilyBIjHf = false;
      bool BjNsUhaoXL = false;
      bool DBOmCDYXGG = false;
      bool ieBWrwrmPJ = false;
      bool CVUZeXFSNh = false;
      bool HapriGQwju = false;
      bool ckdAxVhqBY = false;
      bool omZNIgfnHd = false;
      bool xFJXzHoJmk = false;
      bool fuDTgRqTbI = false;
      bool pORorTBbjB = false;
      bool ZboFxWaGBp = false;
      bool gYDPrtjGgp = false;
      bool oMLynimUee = false;
      bool FNYlKDGyVJ = false;
      bool qkSlbQKCwy = false;
      bool jttsLNQpQO = false;
      bool jGbVjTzREn = false;
      bool nljXzEsZWX = false;
      bool YkXfuLSfZx = false;
      string egPThBNGyc;
      string pzRmFokKic;
      string clmSMDUmNj;
      string BNhIMgFGjQ;
      string CwSudBhBDI;
      string TxFFfrtxHd;
      string gZrNacRJZY;
      string jdaSZfTrnL;
      string VSjEQEHbbU;
      string mIzFicDFTB;
      string jXbdYoVmfA;
      string YBIuINpmxW;
      string UohEkbeVix;
      string bOXmbyqFfa;
      string hUwbwkzDwV;
      string lQHwftpWsx;
      string JzDhXJcUTK;
      string WkHWoAsFIA;
      string bbYNKLGbGg;
      string HTMiQhQNEl;
      if(egPThBNGyc == jXbdYoVmfA){HeilyBIjHf = true;}
      else if(jXbdYoVmfA == egPThBNGyc){pORorTBbjB = true;}
      if(pzRmFokKic == YBIuINpmxW){BjNsUhaoXL = true;}
      else if(YBIuINpmxW == pzRmFokKic){ZboFxWaGBp = true;}
      if(clmSMDUmNj == UohEkbeVix){DBOmCDYXGG = true;}
      else if(UohEkbeVix == clmSMDUmNj){gYDPrtjGgp = true;}
      if(BNhIMgFGjQ == bOXmbyqFfa){ieBWrwrmPJ = true;}
      else if(bOXmbyqFfa == BNhIMgFGjQ){oMLynimUee = true;}
      if(CwSudBhBDI == hUwbwkzDwV){CVUZeXFSNh = true;}
      else if(hUwbwkzDwV == CwSudBhBDI){FNYlKDGyVJ = true;}
      if(TxFFfrtxHd == lQHwftpWsx){HapriGQwju = true;}
      else if(lQHwftpWsx == TxFFfrtxHd){qkSlbQKCwy = true;}
      if(gZrNacRJZY == JzDhXJcUTK){ckdAxVhqBY = true;}
      else if(JzDhXJcUTK == gZrNacRJZY){jttsLNQpQO = true;}
      if(jdaSZfTrnL == WkHWoAsFIA){omZNIgfnHd = true;}
      if(VSjEQEHbbU == bbYNKLGbGg){xFJXzHoJmk = true;}
      if(mIzFicDFTB == HTMiQhQNEl){fuDTgRqTbI = true;}
      while(WkHWoAsFIA == jdaSZfTrnL){jGbVjTzREn = true;}
      while(bbYNKLGbGg == bbYNKLGbGg){nljXzEsZWX = true;}
      while(HTMiQhQNEl == HTMiQhQNEl){YkXfuLSfZx = true;}
      if(HeilyBIjHf == true){HeilyBIjHf = false;}
      if(BjNsUhaoXL == true){BjNsUhaoXL = false;}
      if(DBOmCDYXGG == true){DBOmCDYXGG = false;}
      if(ieBWrwrmPJ == true){ieBWrwrmPJ = false;}
      if(CVUZeXFSNh == true){CVUZeXFSNh = false;}
      if(HapriGQwju == true){HapriGQwju = false;}
      if(ckdAxVhqBY == true){ckdAxVhqBY = false;}
      if(omZNIgfnHd == true){omZNIgfnHd = false;}
      if(xFJXzHoJmk == true){xFJXzHoJmk = false;}
      if(fuDTgRqTbI == true){fuDTgRqTbI = false;}
      if(pORorTBbjB == true){pORorTBbjB = false;}
      if(ZboFxWaGBp == true){ZboFxWaGBp = false;}
      if(gYDPrtjGgp == true){gYDPrtjGgp = false;}
      if(oMLynimUee == true){oMLynimUee = false;}
      if(FNYlKDGyVJ == true){FNYlKDGyVJ = false;}
      if(qkSlbQKCwy == true){qkSlbQKCwy = false;}
      if(jttsLNQpQO == true){jttsLNQpQO = false;}
      if(jGbVjTzREn == true){jGbVjTzREn = false;}
      if(nljXzEsZWX == true){nljXzEsZWX = false;}
      if(YkXfuLSfZx == true){YkXfuLSfZx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QQNJJJEADJ
{ 
  void JGcIHXSmcE()
  { 
      bool FLIGzxQTat = false;
      bool eFKwMTITMh = false;
      bool oKDXMVTDaI = false;
      bool VUtaknsXBr = false;
      bool oVEdhQYaRK = false;
      bool oiqzDuHksc = false;
      bool dMrSXJLiKX = false;
      bool akSUsTFYow = false;
      bool xrlQSmdtXp = false;
      bool fHdXOcclGY = false;
      bool EoQsiEPWGi = false;
      bool oiwxflaazk = false;
      bool fQLUqTGtFP = false;
      bool pTSQqHbrhN = false;
      bool WGmnAxLgrb = false;
      bool BClUrmdwBP = false;
      bool yUQqsUPeFX = false;
      bool KhslOYdXTs = false;
      bool HZCdNnhxXE = false;
      bool depSPBpwuf = false;
      string uwrTOMtAIk;
      string BUAQiayGGF;
      string OECSMlKEkg;
      string zFxkItgDHa;
      string hmIMLJycQt;
      string MGGGUpsZGc;
      string BpPaluXPIn;
      string ttyfXbwoGD;
      string nhmpTszpPR;
      string AGxeYrWgaP;
      string khUbzSHais;
      string tESDnTCYHr;
      string wgzpnmwTGe;
      string EPNqRFNLqB;
      string kXHWWwmtpF;
      string oyZhSEidnM;
      string WmUDnepbki;
      string FqhFGYYcSq;
      string zCdApFofXN;
      string WjXdeyCEhr;
      if(uwrTOMtAIk == khUbzSHais){FLIGzxQTat = true;}
      else if(khUbzSHais == uwrTOMtAIk){EoQsiEPWGi = true;}
      if(BUAQiayGGF == tESDnTCYHr){eFKwMTITMh = true;}
      else if(tESDnTCYHr == BUAQiayGGF){oiwxflaazk = true;}
      if(OECSMlKEkg == wgzpnmwTGe){oKDXMVTDaI = true;}
      else if(wgzpnmwTGe == OECSMlKEkg){fQLUqTGtFP = true;}
      if(zFxkItgDHa == EPNqRFNLqB){VUtaknsXBr = true;}
      else if(EPNqRFNLqB == zFxkItgDHa){pTSQqHbrhN = true;}
      if(hmIMLJycQt == kXHWWwmtpF){oVEdhQYaRK = true;}
      else if(kXHWWwmtpF == hmIMLJycQt){WGmnAxLgrb = true;}
      if(MGGGUpsZGc == oyZhSEidnM){oiqzDuHksc = true;}
      else if(oyZhSEidnM == MGGGUpsZGc){BClUrmdwBP = true;}
      if(BpPaluXPIn == WmUDnepbki){dMrSXJLiKX = true;}
      else if(WmUDnepbki == BpPaluXPIn){yUQqsUPeFX = true;}
      if(ttyfXbwoGD == FqhFGYYcSq){akSUsTFYow = true;}
      if(nhmpTszpPR == zCdApFofXN){xrlQSmdtXp = true;}
      if(AGxeYrWgaP == WjXdeyCEhr){fHdXOcclGY = true;}
      while(FqhFGYYcSq == ttyfXbwoGD){KhslOYdXTs = true;}
      while(zCdApFofXN == zCdApFofXN){HZCdNnhxXE = true;}
      while(WjXdeyCEhr == WjXdeyCEhr){depSPBpwuf = true;}
      if(FLIGzxQTat == true){FLIGzxQTat = false;}
      if(eFKwMTITMh == true){eFKwMTITMh = false;}
      if(oKDXMVTDaI == true){oKDXMVTDaI = false;}
      if(VUtaknsXBr == true){VUtaknsXBr = false;}
      if(oVEdhQYaRK == true){oVEdhQYaRK = false;}
      if(oiqzDuHksc == true){oiqzDuHksc = false;}
      if(dMrSXJLiKX == true){dMrSXJLiKX = false;}
      if(akSUsTFYow == true){akSUsTFYow = false;}
      if(xrlQSmdtXp == true){xrlQSmdtXp = false;}
      if(fHdXOcclGY == true){fHdXOcclGY = false;}
      if(EoQsiEPWGi == true){EoQsiEPWGi = false;}
      if(oiwxflaazk == true){oiwxflaazk = false;}
      if(fQLUqTGtFP == true){fQLUqTGtFP = false;}
      if(pTSQqHbrhN == true){pTSQqHbrhN = false;}
      if(WGmnAxLgrb == true){WGmnAxLgrb = false;}
      if(BClUrmdwBP == true){BClUrmdwBP = false;}
      if(yUQqsUPeFX == true){yUQqsUPeFX = false;}
      if(KhslOYdXTs == true){KhslOYdXTs = false;}
      if(HZCdNnhxXE == true){HZCdNnhxXE = false;}
      if(depSPBpwuf == true){depSPBpwuf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCXODGNXBO
{ 
  void cnIkuhtaVO()
  { 
      bool pbpxNKmPuP = false;
      bool dTNhUCznVT = false;
      bool ZXxHjkOpmi = false;
      bool sFgYlQZwkf = false;
      bool HlxaRoTgur = false;
      bool FkGbeSehMb = false;
      bool uwbLVXmouE = false;
      bool bDDpMnaVpu = false;
      bool RhutcIzFsT = false;
      bool lqjJjKKkEs = false;
      bool CdkqQChPPq = false;
      bool rIrQJNBghN = false;
      bool YhwbRjTsGB = false;
      bool coRwrmwEda = false;
      bool ZioBadzSzW = false;
      bool JdCpTUhJYf = false;
      bool inJNOCquXV = false;
      bool QwCHnprtAn = false;
      bool jAtiqzmacX = false;
      bool EmeyqkYamX = false;
      string iZQklcNrKt;
      string IAAxUPVRzi;
      string mQiOgpFrGc;
      string gyusaneIow;
      string MQZjYouaZG;
      string oFUOaRpCDw;
      string WUkhNJFHVf;
      string kNcDWVqyor;
      string ueRAmadgRJ;
      string xcErYqfrWO;
      string jmEsVacRqF;
      string aqNLBrCktm;
      string fXoMiHIjde;
      string pzbZHHZYdM;
      string yMoLhFPsqf;
      string ntxjiMxrKN;
      string RrmMPbPmDt;
      string SdGhnThdec;
      string rPsypuBrpu;
      string JgOPtFZcwF;
      if(iZQklcNrKt == jmEsVacRqF){pbpxNKmPuP = true;}
      else if(jmEsVacRqF == iZQklcNrKt){CdkqQChPPq = true;}
      if(IAAxUPVRzi == aqNLBrCktm){dTNhUCznVT = true;}
      else if(aqNLBrCktm == IAAxUPVRzi){rIrQJNBghN = true;}
      if(mQiOgpFrGc == fXoMiHIjde){ZXxHjkOpmi = true;}
      else if(fXoMiHIjde == mQiOgpFrGc){YhwbRjTsGB = true;}
      if(gyusaneIow == pzbZHHZYdM){sFgYlQZwkf = true;}
      else if(pzbZHHZYdM == gyusaneIow){coRwrmwEda = true;}
      if(MQZjYouaZG == yMoLhFPsqf){HlxaRoTgur = true;}
      else if(yMoLhFPsqf == MQZjYouaZG){ZioBadzSzW = true;}
      if(oFUOaRpCDw == ntxjiMxrKN){FkGbeSehMb = true;}
      else if(ntxjiMxrKN == oFUOaRpCDw){JdCpTUhJYf = true;}
      if(WUkhNJFHVf == RrmMPbPmDt){uwbLVXmouE = true;}
      else if(RrmMPbPmDt == WUkhNJFHVf){inJNOCquXV = true;}
      if(kNcDWVqyor == SdGhnThdec){bDDpMnaVpu = true;}
      if(ueRAmadgRJ == rPsypuBrpu){RhutcIzFsT = true;}
      if(xcErYqfrWO == JgOPtFZcwF){lqjJjKKkEs = true;}
      while(SdGhnThdec == kNcDWVqyor){QwCHnprtAn = true;}
      while(rPsypuBrpu == rPsypuBrpu){jAtiqzmacX = true;}
      while(JgOPtFZcwF == JgOPtFZcwF){EmeyqkYamX = true;}
      if(pbpxNKmPuP == true){pbpxNKmPuP = false;}
      if(dTNhUCznVT == true){dTNhUCznVT = false;}
      if(ZXxHjkOpmi == true){ZXxHjkOpmi = false;}
      if(sFgYlQZwkf == true){sFgYlQZwkf = false;}
      if(HlxaRoTgur == true){HlxaRoTgur = false;}
      if(FkGbeSehMb == true){FkGbeSehMb = false;}
      if(uwbLVXmouE == true){uwbLVXmouE = false;}
      if(bDDpMnaVpu == true){bDDpMnaVpu = false;}
      if(RhutcIzFsT == true){RhutcIzFsT = false;}
      if(lqjJjKKkEs == true){lqjJjKKkEs = false;}
      if(CdkqQChPPq == true){CdkqQChPPq = false;}
      if(rIrQJNBghN == true){rIrQJNBghN = false;}
      if(YhwbRjTsGB == true){YhwbRjTsGB = false;}
      if(coRwrmwEda == true){coRwrmwEda = false;}
      if(ZioBadzSzW == true){ZioBadzSzW = false;}
      if(JdCpTUhJYf == true){JdCpTUhJYf = false;}
      if(inJNOCquXV == true){inJNOCquXV = false;}
      if(QwCHnprtAn == true){QwCHnprtAn = false;}
      if(jAtiqzmacX == true){jAtiqzmacX = false;}
      if(EmeyqkYamX == true){EmeyqkYamX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBSWUHDDGA
{ 
  void diaHOKNarP()
  { 
      bool tKYecJglds = false;
      bool uAfsnlwKBi = false;
      bool kGaFdbbnfl = false;
      bool UPKhrboIYp = false;
      bool RcnwgLohZl = false;
      bool nOXBemjTBB = false;
      bool hsFrYfpxAM = false;
      bool wmkKQISeYS = false;
      bool msNtyFqIDF = false;
      bool qVGXIXXwWA = false;
      bool UqhMoAcMkW = false;
      bool UFuiNoeKsS = false;
      bool ngtuVagMCr = false;
      bool jVHXxwKBFx = false;
      bool bdXgjlZXKS = false;
      bool rMCELnxlqO = false;
      bool TPKrlyyXlQ = false;
      bool ddFwpKJNKj = false;
      bool AICjzWTDLI = false;
      bool zYJpdMTetk = false;
      string uRZnygUbIo;
      string mIRwtxgNYX;
      string NOKgdfkKDl;
      string jZxQFWNKkU;
      string jAoxhNMmMY;
      string qVuEefHrKR;
      string uKXWFMLApX;
      string iVbDnMYMyP;
      string TxxetNeslY;
      string OVASZZcSrU;
      string CLwooVsqQS;
      string HtttyyMrcq;
      string gROQINUIdN;
      string jFTcMIAIpX;
      string UmcTRUaGUa;
      string NjpBmkwega;
      string AjNChBZQgo;
      string xDCEWtouzm;
      string lOnCAzPSob;
      string LUbOXjZZkQ;
      if(uRZnygUbIo == CLwooVsqQS){tKYecJglds = true;}
      else if(CLwooVsqQS == uRZnygUbIo){UqhMoAcMkW = true;}
      if(mIRwtxgNYX == HtttyyMrcq){uAfsnlwKBi = true;}
      else if(HtttyyMrcq == mIRwtxgNYX){UFuiNoeKsS = true;}
      if(NOKgdfkKDl == gROQINUIdN){kGaFdbbnfl = true;}
      else if(gROQINUIdN == NOKgdfkKDl){ngtuVagMCr = true;}
      if(jZxQFWNKkU == jFTcMIAIpX){UPKhrboIYp = true;}
      else if(jFTcMIAIpX == jZxQFWNKkU){jVHXxwKBFx = true;}
      if(jAoxhNMmMY == UmcTRUaGUa){RcnwgLohZl = true;}
      else if(UmcTRUaGUa == jAoxhNMmMY){bdXgjlZXKS = true;}
      if(qVuEefHrKR == NjpBmkwega){nOXBemjTBB = true;}
      else if(NjpBmkwega == qVuEefHrKR){rMCELnxlqO = true;}
      if(uKXWFMLApX == AjNChBZQgo){hsFrYfpxAM = true;}
      else if(AjNChBZQgo == uKXWFMLApX){TPKrlyyXlQ = true;}
      if(iVbDnMYMyP == xDCEWtouzm){wmkKQISeYS = true;}
      if(TxxetNeslY == lOnCAzPSob){msNtyFqIDF = true;}
      if(OVASZZcSrU == LUbOXjZZkQ){qVGXIXXwWA = true;}
      while(xDCEWtouzm == iVbDnMYMyP){ddFwpKJNKj = true;}
      while(lOnCAzPSob == lOnCAzPSob){AICjzWTDLI = true;}
      while(LUbOXjZZkQ == LUbOXjZZkQ){zYJpdMTetk = true;}
      if(tKYecJglds == true){tKYecJglds = false;}
      if(uAfsnlwKBi == true){uAfsnlwKBi = false;}
      if(kGaFdbbnfl == true){kGaFdbbnfl = false;}
      if(UPKhrboIYp == true){UPKhrboIYp = false;}
      if(RcnwgLohZl == true){RcnwgLohZl = false;}
      if(nOXBemjTBB == true){nOXBemjTBB = false;}
      if(hsFrYfpxAM == true){hsFrYfpxAM = false;}
      if(wmkKQISeYS == true){wmkKQISeYS = false;}
      if(msNtyFqIDF == true){msNtyFqIDF = false;}
      if(qVGXIXXwWA == true){qVGXIXXwWA = false;}
      if(UqhMoAcMkW == true){UqhMoAcMkW = false;}
      if(UFuiNoeKsS == true){UFuiNoeKsS = false;}
      if(ngtuVagMCr == true){ngtuVagMCr = false;}
      if(jVHXxwKBFx == true){jVHXxwKBFx = false;}
      if(bdXgjlZXKS == true){bdXgjlZXKS = false;}
      if(rMCELnxlqO == true){rMCELnxlqO = false;}
      if(TPKrlyyXlQ == true){TPKrlyyXlQ = false;}
      if(ddFwpKJNKj == true){ddFwpKJNKj = false;}
      if(AICjzWTDLI == true){AICjzWTDLI = false;}
      if(zYJpdMTetk == true){zYJpdMTetk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQMMQKNLFE
{ 
  void hlRTYbIHuW()
  { 
      bool iHXXCFgoBc = false;
      bool uLIjlmQpfz = false;
      bool FmsutIySBq = false;
      bool LTKQuyECkY = false;
      bool ZKeMNTkbOo = false;
      bool EVJxRwObdt = false;
      bool HOnJRbBqon = false;
      bool iOEGZtIfgZ = false;
      bool WWEMmoJNzz = false;
      bool ibXqRLWUtl = false;
      bool RtlaFoQCWW = false;
      bool mhuDWjJbWc = false;
      bool RmrpEGqNnO = false;
      bool XnluHbjdGx = false;
      bool XHpbLBgTTg = false;
      bool BuxQTeCwWy = false;
      bool yDOIzzwzuu = false;
      bool AfUZFKxPeC = false;
      bool ZWtGNbpUac = false;
      bool ZnGHyUshbL = false;
      string NdexwgacQo;
      string xdkzRNkViI;
      string agdxErjSig;
      string lWNEgSzlas;
      string KFYrpdMfuC;
      string TJKFkfAhrE;
      string wIsjDZQfSz;
      string NytoyUHkHa;
      string fEWgNcLHTB;
      string RRtWxCMooP;
      string NfNwnUPVHP;
      string XOaRYrkLWa;
      string NJMQgwEXru;
      string ISuqNzparr;
      string MpAEcCqbxE;
      string QASOBDTwOq;
      string PqdLHFTiEZ;
      string CKTdNXIHnd;
      string FbZmeHzfpJ;
      string esLAcVMoxW;
      if(NdexwgacQo == NfNwnUPVHP){iHXXCFgoBc = true;}
      else if(NfNwnUPVHP == NdexwgacQo){RtlaFoQCWW = true;}
      if(xdkzRNkViI == XOaRYrkLWa){uLIjlmQpfz = true;}
      else if(XOaRYrkLWa == xdkzRNkViI){mhuDWjJbWc = true;}
      if(agdxErjSig == NJMQgwEXru){FmsutIySBq = true;}
      else if(NJMQgwEXru == agdxErjSig){RmrpEGqNnO = true;}
      if(lWNEgSzlas == ISuqNzparr){LTKQuyECkY = true;}
      else if(ISuqNzparr == lWNEgSzlas){XnluHbjdGx = true;}
      if(KFYrpdMfuC == MpAEcCqbxE){ZKeMNTkbOo = true;}
      else if(MpAEcCqbxE == KFYrpdMfuC){XHpbLBgTTg = true;}
      if(TJKFkfAhrE == QASOBDTwOq){EVJxRwObdt = true;}
      else if(QASOBDTwOq == TJKFkfAhrE){BuxQTeCwWy = true;}
      if(wIsjDZQfSz == PqdLHFTiEZ){HOnJRbBqon = true;}
      else if(PqdLHFTiEZ == wIsjDZQfSz){yDOIzzwzuu = true;}
      if(NytoyUHkHa == CKTdNXIHnd){iOEGZtIfgZ = true;}
      if(fEWgNcLHTB == FbZmeHzfpJ){WWEMmoJNzz = true;}
      if(RRtWxCMooP == esLAcVMoxW){ibXqRLWUtl = true;}
      while(CKTdNXIHnd == NytoyUHkHa){AfUZFKxPeC = true;}
      while(FbZmeHzfpJ == FbZmeHzfpJ){ZWtGNbpUac = true;}
      while(esLAcVMoxW == esLAcVMoxW){ZnGHyUshbL = true;}
      if(iHXXCFgoBc == true){iHXXCFgoBc = false;}
      if(uLIjlmQpfz == true){uLIjlmQpfz = false;}
      if(FmsutIySBq == true){FmsutIySBq = false;}
      if(LTKQuyECkY == true){LTKQuyECkY = false;}
      if(ZKeMNTkbOo == true){ZKeMNTkbOo = false;}
      if(EVJxRwObdt == true){EVJxRwObdt = false;}
      if(HOnJRbBqon == true){HOnJRbBqon = false;}
      if(iOEGZtIfgZ == true){iOEGZtIfgZ = false;}
      if(WWEMmoJNzz == true){WWEMmoJNzz = false;}
      if(ibXqRLWUtl == true){ibXqRLWUtl = false;}
      if(RtlaFoQCWW == true){RtlaFoQCWW = false;}
      if(mhuDWjJbWc == true){mhuDWjJbWc = false;}
      if(RmrpEGqNnO == true){RmrpEGqNnO = false;}
      if(XnluHbjdGx == true){XnluHbjdGx = false;}
      if(XHpbLBgTTg == true){XHpbLBgTTg = false;}
      if(BuxQTeCwWy == true){BuxQTeCwWy = false;}
      if(yDOIzzwzuu == true){yDOIzzwzuu = false;}
      if(AfUZFKxPeC == true){AfUZFKxPeC = false;}
      if(ZWtGNbpUac == true){ZWtGNbpUac = false;}
      if(ZnGHyUshbL == true){ZnGHyUshbL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYULLWMQZL
{ 
  void lPULqplkcy()
  { 
      bool uXHLPSUMFh = false;
      bool ldzSEXpYmT = false;
      bool CVVkabDzqx = false;
      bool auYnaVaAwQ = false;
      bool hNuXciNnCl = false;
      bool FPxXFYBWjn = false;
      bool OUVIGpEKqh = false;
      bool xobWlnaxIq = false;
      bool OPxEqLxAhB = false;
      bool UDQIBMqmRl = false;
      bool eCwUoQnalR = false;
      bool xEOsYzXRQt = false;
      bool sDboMsYSVY = false;
      bool wneVLLScPa = false;
      bool WWOQEQoWiC = false;
      bool oZVWraaGHu = false;
      bool rUENUJYrgN = false;
      bool fuBoXVoLkw = false;
      bool EBiTjVRHdj = false;
      bool kMUTiBRAwt = false;
      string htUEylESUi;
      string SKkhfaonGI;
      string LpgxgOBbLm;
      string gzblwCCLfl;
      string LsQrGqcPFP;
      string ZVWhTrMWWi;
      string jbGgCSizkc;
      string YdHTwRYoqo;
      string llWwNLctRD;
      string oenwCiliom;
      string IcdbquNCkC;
      string SWfgxxFKTp;
      string poghnsoLRN;
      string epzDgIItER;
      string xZIPkRzHzE;
      string dbPyxSuwny;
      string GCkXWcWbzn;
      string oKGCsPgRwV;
      string thLMjDaBFO;
      string NMGGKunkrH;
      if(htUEylESUi == IcdbquNCkC){uXHLPSUMFh = true;}
      else if(IcdbquNCkC == htUEylESUi){eCwUoQnalR = true;}
      if(SKkhfaonGI == SWfgxxFKTp){ldzSEXpYmT = true;}
      else if(SWfgxxFKTp == SKkhfaonGI){xEOsYzXRQt = true;}
      if(LpgxgOBbLm == poghnsoLRN){CVVkabDzqx = true;}
      else if(poghnsoLRN == LpgxgOBbLm){sDboMsYSVY = true;}
      if(gzblwCCLfl == epzDgIItER){auYnaVaAwQ = true;}
      else if(epzDgIItER == gzblwCCLfl){wneVLLScPa = true;}
      if(LsQrGqcPFP == xZIPkRzHzE){hNuXciNnCl = true;}
      else if(xZIPkRzHzE == LsQrGqcPFP){WWOQEQoWiC = true;}
      if(ZVWhTrMWWi == dbPyxSuwny){FPxXFYBWjn = true;}
      else if(dbPyxSuwny == ZVWhTrMWWi){oZVWraaGHu = true;}
      if(jbGgCSizkc == GCkXWcWbzn){OUVIGpEKqh = true;}
      else if(GCkXWcWbzn == jbGgCSizkc){rUENUJYrgN = true;}
      if(YdHTwRYoqo == oKGCsPgRwV){xobWlnaxIq = true;}
      if(llWwNLctRD == thLMjDaBFO){OPxEqLxAhB = true;}
      if(oenwCiliom == NMGGKunkrH){UDQIBMqmRl = true;}
      while(oKGCsPgRwV == YdHTwRYoqo){fuBoXVoLkw = true;}
      while(thLMjDaBFO == thLMjDaBFO){EBiTjVRHdj = true;}
      while(NMGGKunkrH == NMGGKunkrH){kMUTiBRAwt = true;}
      if(uXHLPSUMFh == true){uXHLPSUMFh = false;}
      if(ldzSEXpYmT == true){ldzSEXpYmT = false;}
      if(CVVkabDzqx == true){CVVkabDzqx = false;}
      if(auYnaVaAwQ == true){auYnaVaAwQ = false;}
      if(hNuXciNnCl == true){hNuXciNnCl = false;}
      if(FPxXFYBWjn == true){FPxXFYBWjn = false;}
      if(OUVIGpEKqh == true){OUVIGpEKqh = false;}
      if(xobWlnaxIq == true){xobWlnaxIq = false;}
      if(OPxEqLxAhB == true){OPxEqLxAhB = false;}
      if(UDQIBMqmRl == true){UDQIBMqmRl = false;}
      if(eCwUoQnalR == true){eCwUoQnalR = false;}
      if(xEOsYzXRQt == true){xEOsYzXRQt = false;}
      if(sDboMsYSVY == true){sDboMsYSVY = false;}
      if(wneVLLScPa == true){wneVLLScPa = false;}
      if(WWOQEQoWiC == true){WWOQEQoWiC = false;}
      if(oZVWraaGHu == true){oZVWraaGHu = false;}
      if(rUENUJYrgN == true){rUENUJYrgN = false;}
      if(fuBoXVoLkw == true){fuBoXVoLkw = false;}
      if(EBiTjVRHdj == true){EBiTjVRHdj = false;}
      if(kMUTiBRAwt == true){kMUTiBRAwt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYXIUWFPAR
{ 
  void XWWVGIkbZk()
  { 
      bool FzEuWkcSJW = false;
      bool IlXiuXlOCP = false;
      bool fzIfJDegnK = false;
      bool GymzourVrz = false;
      bool RwTnUYNggz = false;
      bool xHODaGpXkT = false;
      bool FwdyQKzXsA = false;
      bool ePVDxieULk = false;
      bool oyzoNzjjXh = false;
      bool EUkYsVRVXK = false;
      bool ZpmgTgkKFq = false;
      bool bVMAdHxokR = false;
      bool ZPzLwKexKb = false;
      bool RJxBLzKSVf = false;
      bool NYdfGhIktl = false;
      bool XcjFjJpbjI = false;
      bool CnAdZSYKod = false;
      bool weSEEAkSEO = false;
      bool CtCXDnYqRB = false;
      bool JihMdYYAGn = false;
      string MEoYfDcuTw;
      string AYiQEqRaSz;
      string VrUOQWukrp;
      string mKwXNeagAZ;
      string NTNxVVoqhT;
      string QMBoxUiZHI;
      string IrCdJobLCZ;
      string PkZskBeWsu;
      string hDCYYZJHZs;
      string uBZqQVRjnf;
      string sdnIEflHDu;
      string pMgLaEodEi;
      string eUkJdOKhbP;
      string jtiMCEPtTr;
      string nBEeCiTNQM;
      string fneEAYrddp;
      string UDemLucUJV;
      string ouKLudPFGu;
      string txRPjuPdLc;
      string LkPcWjWRSH;
      if(MEoYfDcuTw == sdnIEflHDu){FzEuWkcSJW = true;}
      else if(sdnIEflHDu == MEoYfDcuTw){ZpmgTgkKFq = true;}
      if(AYiQEqRaSz == pMgLaEodEi){IlXiuXlOCP = true;}
      else if(pMgLaEodEi == AYiQEqRaSz){bVMAdHxokR = true;}
      if(VrUOQWukrp == eUkJdOKhbP){fzIfJDegnK = true;}
      else if(eUkJdOKhbP == VrUOQWukrp){ZPzLwKexKb = true;}
      if(mKwXNeagAZ == jtiMCEPtTr){GymzourVrz = true;}
      else if(jtiMCEPtTr == mKwXNeagAZ){RJxBLzKSVf = true;}
      if(NTNxVVoqhT == nBEeCiTNQM){RwTnUYNggz = true;}
      else if(nBEeCiTNQM == NTNxVVoqhT){NYdfGhIktl = true;}
      if(QMBoxUiZHI == fneEAYrddp){xHODaGpXkT = true;}
      else if(fneEAYrddp == QMBoxUiZHI){XcjFjJpbjI = true;}
      if(IrCdJobLCZ == UDemLucUJV){FwdyQKzXsA = true;}
      else if(UDemLucUJV == IrCdJobLCZ){CnAdZSYKod = true;}
      if(PkZskBeWsu == ouKLudPFGu){ePVDxieULk = true;}
      if(hDCYYZJHZs == txRPjuPdLc){oyzoNzjjXh = true;}
      if(uBZqQVRjnf == LkPcWjWRSH){EUkYsVRVXK = true;}
      while(ouKLudPFGu == PkZskBeWsu){weSEEAkSEO = true;}
      while(txRPjuPdLc == txRPjuPdLc){CtCXDnYqRB = true;}
      while(LkPcWjWRSH == LkPcWjWRSH){JihMdYYAGn = true;}
      if(FzEuWkcSJW == true){FzEuWkcSJW = false;}
      if(IlXiuXlOCP == true){IlXiuXlOCP = false;}
      if(fzIfJDegnK == true){fzIfJDegnK = false;}
      if(GymzourVrz == true){GymzourVrz = false;}
      if(RwTnUYNggz == true){RwTnUYNggz = false;}
      if(xHODaGpXkT == true){xHODaGpXkT = false;}
      if(FwdyQKzXsA == true){FwdyQKzXsA = false;}
      if(ePVDxieULk == true){ePVDxieULk = false;}
      if(oyzoNzjjXh == true){oyzoNzjjXh = false;}
      if(EUkYsVRVXK == true){EUkYsVRVXK = false;}
      if(ZpmgTgkKFq == true){ZpmgTgkKFq = false;}
      if(bVMAdHxokR == true){bVMAdHxokR = false;}
      if(ZPzLwKexKb == true){ZPzLwKexKb = false;}
      if(RJxBLzKSVf == true){RJxBLzKSVf = false;}
      if(NYdfGhIktl == true){NYdfGhIktl = false;}
      if(XcjFjJpbjI == true){XcjFjJpbjI = false;}
      if(CnAdZSYKod == true){CnAdZSYKod = false;}
      if(weSEEAkSEO == true){weSEEAkSEO = false;}
      if(CtCXDnYqRB == true){CtCXDnYqRB = false;}
      if(JihMdYYAGn == true){JihMdYYAGn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZCGJTYCLD
{ 
  void jJMASsQFuC()
  { 
      bool NdpFXzVMGW = false;
      bool uWQjAxhTxK = false;
      bool ywKstfgQTG = false;
      bool WrRYUpbMMM = false;
      bool ofIBSEpZXI = false;
      bool XZqSXQTwKq = false;
      bool SFrAACFrOJ = false;
      bool UVHkVRnIap = false;
      bool pGrLhwAyAD = false;
      bool WfBVsimIBP = false;
      bool yyKNmBSFxF = false;
      bool cKVUALMgRD = false;
      bool CHqLmoUlql = false;
      bool eeHKrrwdXf = false;
      bool dtAtZMJgUh = false;
      bool VFqxNpGyax = false;
      bool ggOKayDLcH = false;
      bool PhJkZHGwlZ = false;
      bool enQJPYnJwB = false;
      bool lxDZyxfoSb = false;
      string trukiBXjAF;
      string UPpZHUEDUl;
      string yEdgpJHCAy;
      string iHbCcgZqQK;
      string cflIQsBSAA;
      string tgKTKpNNtY;
      string tUjBVMmmwa;
      string uMlKJSRUQw;
      string InBzECxIrm;
      string SLwrPIukmD;
      string GNVZFguzKr;
      string XsxyQFSjxT;
      string PeuJHiQttB;
      string WghNptSbtW;
      string HyxzOYOybK;
      string pLmSnbSLRV;
      string QAEIVqLjHV;
      string mpoaMQguuh;
      string USRjLKsOYN;
      string aGJYGGtodW;
      if(trukiBXjAF == GNVZFguzKr){NdpFXzVMGW = true;}
      else if(GNVZFguzKr == trukiBXjAF){yyKNmBSFxF = true;}
      if(UPpZHUEDUl == XsxyQFSjxT){uWQjAxhTxK = true;}
      else if(XsxyQFSjxT == UPpZHUEDUl){cKVUALMgRD = true;}
      if(yEdgpJHCAy == PeuJHiQttB){ywKstfgQTG = true;}
      else if(PeuJHiQttB == yEdgpJHCAy){CHqLmoUlql = true;}
      if(iHbCcgZqQK == WghNptSbtW){WrRYUpbMMM = true;}
      else if(WghNptSbtW == iHbCcgZqQK){eeHKrrwdXf = true;}
      if(cflIQsBSAA == HyxzOYOybK){ofIBSEpZXI = true;}
      else if(HyxzOYOybK == cflIQsBSAA){dtAtZMJgUh = true;}
      if(tgKTKpNNtY == pLmSnbSLRV){XZqSXQTwKq = true;}
      else if(pLmSnbSLRV == tgKTKpNNtY){VFqxNpGyax = true;}
      if(tUjBVMmmwa == QAEIVqLjHV){SFrAACFrOJ = true;}
      else if(QAEIVqLjHV == tUjBVMmmwa){ggOKayDLcH = true;}
      if(uMlKJSRUQw == mpoaMQguuh){UVHkVRnIap = true;}
      if(InBzECxIrm == USRjLKsOYN){pGrLhwAyAD = true;}
      if(SLwrPIukmD == aGJYGGtodW){WfBVsimIBP = true;}
      while(mpoaMQguuh == uMlKJSRUQw){PhJkZHGwlZ = true;}
      while(USRjLKsOYN == USRjLKsOYN){enQJPYnJwB = true;}
      while(aGJYGGtodW == aGJYGGtodW){lxDZyxfoSb = true;}
      if(NdpFXzVMGW == true){NdpFXzVMGW = false;}
      if(uWQjAxhTxK == true){uWQjAxhTxK = false;}
      if(ywKstfgQTG == true){ywKstfgQTG = false;}
      if(WrRYUpbMMM == true){WrRYUpbMMM = false;}
      if(ofIBSEpZXI == true){ofIBSEpZXI = false;}
      if(XZqSXQTwKq == true){XZqSXQTwKq = false;}
      if(SFrAACFrOJ == true){SFrAACFrOJ = false;}
      if(UVHkVRnIap == true){UVHkVRnIap = false;}
      if(pGrLhwAyAD == true){pGrLhwAyAD = false;}
      if(WfBVsimIBP == true){WfBVsimIBP = false;}
      if(yyKNmBSFxF == true){yyKNmBSFxF = false;}
      if(cKVUALMgRD == true){cKVUALMgRD = false;}
      if(CHqLmoUlql == true){CHqLmoUlql = false;}
      if(eeHKrrwdXf == true){eeHKrrwdXf = false;}
      if(dtAtZMJgUh == true){dtAtZMJgUh = false;}
      if(VFqxNpGyax == true){VFqxNpGyax = false;}
      if(ggOKayDLcH == true){ggOKayDLcH = false;}
      if(PhJkZHGwlZ == true){PhJkZHGwlZ = false;}
      if(enQJPYnJwB == true){enQJPYnJwB = false;}
      if(lxDZyxfoSb == true){lxDZyxfoSb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENEWGKKCCX
{ 
  void exCVXqTpjx()
  { 
      bool zGzljtpRPH = false;
      bool SeQDWQDOsT = false;
      bool XOXoSFMjyG = false;
      bool TlxixGRIKY = false;
      bool DQTaCHubiW = false;
      bool NFXxPjhJTd = false;
      bool hGSImfhgGP = false;
      bool ytEUQGtwlK = false;
      bool KkAbsONATM = false;
      bool XHogqxxLnV = false;
      bool ZNUSXTBDfI = false;
      bool plXISwFpPX = false;
      bool SgNtqqEXdT = false;
      bool IiIPkxPhDY = false;
      bool MKTKVligNt = false;
      bool qGuPDrAaaf = false;
      bool OdZMzGcIWV = false;
      bool gWmpLIMCXF = false;
      bool IXJibCmsLs = false;
      bool xoGXJijHKO = false;
      string XVniQiRFzj;
      string JNyYotwsIR;
      string ZkGKjNLXbS;
      string yGgnWfZKeq;
      string CopKRluGBd;
      string ryWiWlPczD;
      string WsdglCgJBJ;
      string UkOQPkuusx;
      string RFWyazjyQk;
      string QwLbTJLJYO;
      string FlErIGjGSl;
      string qTjCkRWeFl;
      string SirQrYZlwG;
      string YkVdrfAeoT;
      string OdedswLJqB;
      string lfDmwWsnzj;
      string gyJMNFxFKF;
      string RrolXoDNWw;
      string MQutTshihU;
      string lLeFmQURQm;
      if(XVniQiRFzj == FlErIGjGSl){zGzljtpRPH = true;}
      else if(FlErIGjGSl == XVniQiRFzj){ZNUSXTBDfI = true;}
      if(JNyYotwsIR == qTjCkRWeFl){SeQDWQDOsT = true;}
      else if(qTjCkRWeFl == JNyYotwsIR){plXISwFpPX = true;}
      if(ZkGKjNLXbS == SirQrYZlwG){XOXoSFMjyG = true;}
      else if(SirQrYZlwG == ZkGKjNLXbS){SgNtqqEXdT = true;}
      if(yGgnWfZKeq == YkVdrfAeoT){TlxixGRIKY = true;}
      else if(YkVdrfAeoT == yGgnWfZKeq){IiIPkxPhDY = true;}
      if(CopKRluGBd == OdedswLJqB){DQTaCHubiW = true;}
      else if(OdedswLJqB == CopKRluGBd){MKTKVligNt = true;}
      if(ryWiWlPczD == lfDmwWsnzj){NFXxPjhJTd = true;}
      else if(lfDmwWsnzj == ryWiWlPczD){qGuPDrAaaf = true;}
      if(WsdglCgJBJ == gyJMNFxFKF){hGSImfhgGP = true;}
      else if(gyJMNFxFKF == WsdglCgJBJ){OdZMzGcIWV = true;}
      if(UkOQPkuusx == RrolXoDNWw){ytEUQGtwlK = true;}
      if(RFWyazjyQk == MQutTshihU){KkAbsONATM = true;}
      if(QwLbTJLJYO == lLeFmQURQm){XHogqxxLnV = true;}
      while(RrolXoDNWw == UkOQPkuusx){gWmpLIMCXF = true;}
      while(MQutTshihU == MQutTshihU){IXJibCmsLs = true;}
      while(lLeFmQURQm == lLeFmQURQm){xoGXJijHKO = true;}
      if(zGzljtpRPH == true){zGzljtpRPH = false;}
      if(SeQDWQDOsT == true){SeQDWQDOsT = false;}
      if(XOXoSFMjyG == true){XOXoSFMjyG = false;}
      if(TlxixGRIKY == true){TlxixGRIKY = false;}
      if(DQTaCHubiW == true){DQTaCHubiW = false;}
      if(NFXxPjhJTd == true){NFXxPjhJTd = false;}
      if(hGSImfhgGP == true){hGSImfhgGP = false;}
      if(ytEUQGtwlK == true){ytEUQGtwlK = false;}
      if(KkAbsONATM == true){KkAbsONATM = false;}
      if(XHogqxxLnV == true){XHogqxxLnV = false;}
      if(ZNUSXTBDfI == true){ZNUSXTBDfI = false;}
      if(plXISwFpPX == true){plXISwFpPX = false;}
      if(SgNtqqEXdT == true){SgNtqqEXdT = false;}
      if(IiIPkxPhDY == true){IiIPkxPhDY = false;}
      if(MKTKVligNt == true){MKTKVligNt = false;}
      if(qGuPDrAaaf == true){qGuPDrAaaf = false;}
      if(OdZMzGcIWV == true){OdZMzGcIWV = false;}
      if(gWmpLIMCXF == true){gWmpLIMCXF = false;}
      if(IXJibCmsLs == true){IXJibCmsLs = false;}
      if(xoGXJijHKO == true){xoGXJijHKO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWBMQNGVWK
{ 
  void GQEqLgubNb()
  { 
      bool iWzkYJWTph = false;
      bool MTmziOAtmn = false;
      bool GOBQyuumsi = false;
      bool NDflnXOikG = false;
      bool iSWEhzQHtP = false;
      bool hATUKUVhmd = false;
      bool OjZGTJmBKL = false;
      bool zQIfEnqwiy = false;
      bool ensdBNjLaT = false;
      bool BfwGrzrQjX = false;
      bool MOwiQQqmPW = false;
      bool cZzozaqwFG = false;
      bool ZaaqJSUBnF = false;
      bool uaLLkPqKMk = false;
      bool WwuDpbgGHQ = false;
      bool HuLcxlnFYx = false;
      bool uozKbCNmDi = false;
      bool igiTjdeWAh = false;
      bool lNtWxzOiNz = false;
      bool blkPogxkbm = false;
      string xltGlppXcb;
      string NJTGpszoIZ;
      string eUrIROybIj;
      string KWujKBMfUI;
      string EZRtlGkAtQ;
      string WNlCrbtloX;
      string qNPsRpOiwo;
      string gSUzUEDxWK;
      string dyhrMwksqh;
      string GZqxQqKYcu;
      string rBEEjEslhn;
      string XwPetseXfU;
      string FUrNhGaXhc;
      string seUbRbtcHH;
      string DyLDKKKMCX;
      string LmrHoWIpWd;
      string cUEEtsbmMR;
      string yBPXRHJoDW;
      string uOUKQGlMlu;
      string TDGcdhtGIR;
      if(xltGlppXcb == rBEEjEslhn){iWzkYJWTph = true;}
      else if(rBEEjEslhn == xltGlppXcb){MOwiQQqmPW = true;}
      if(NJTGpszoIZ == XwPetseXfU){MTmziOAtmn = true;}
      else if(XwPetseXfU == NJTGpszoIZ){cZzozaqwFG = true;}
      if(eUrIROybIj == FUrNhGaXhc){GOBQyuumsi = true;}
      else if(FUrNhGaXhc == eUrIROybIj){ZaaqJSUBnF = true;}
      if(KWujKBMfUI == seUbRbtcHH){NDflnXOikG = true;}
      else if(seUbRbtcHH == KWujKBMfUI){uaLLkPqKMk = true;}
      if(EZRtlGkAtQ == DyLDKKKMCX){iSWEhzQHtP = true;}
      else if(DyLDKKKMCX == EZRtlGkAtQ){WwuDpbgGHQ = true;}
      if(WNlCrbtloX == LmrHoWIpWd){hATUKUVhmd = true;}
      else if(LmrHoWIpWd == WNlCrbtloX){HuLcxlnFYx = true;}
      if(qNPsRpOiwo == cUEEtsbmMR){OjZGTJmBKL = true;}
      else if(cUEEtsbmMR == qNPsRpOiwo){uozKbCNmDi = true;}
      if(gSUzUEDxWK == yBPXRHJoDW){zQIfEnqwiy = true;}
      if(dyhrMwksqh == uOUKQGlMlu){ensdBNjLaT = true;}
      if(GZqxQqKYcu == TDGcdhtGIR){BfwGrzrQjX = true;}
      while(yBPXRHJoDW == gSUzUEDxWK){igiTjdeWAh = true;}
      while(uOUKQGlMlu == uOUKQGlMlu){lNtWxzOiNz = true;}
      while(TDGcdhtGIR == TDGcdhtGIR){blkPogxkbm = true;}
      if(iWzkYJWTph == true){iWzkYJWTph = false;}
      if(MTmziOAtmn == true){MTmziOAtmn = false;}
      if(GOBQyuumsi == true){GOBQyuumsi = false;}
      if(NDflnXOikG == true){NDflnXOikG = false;}
      if(iSWEhzQHtP == true){iSWEhzQHtP = false;}
      if(hATUKUVhmd == true){hATUKUVhmd = false;}
      if(OjZGTJmBKL == true){OjZGTJmBKL = false;}
      if(zQIfEnqwiy == true){zQIfEnqwiy = false;}
      if(ensdBNjLaT == true){ensdBNjLaT = false;}
      if(BfwGrzrQjX == true){BfwGrzrQjX = false;}
      if(MOwiQQqmPW == true){MOwiQQqmPW = false;}
      if(cZzozaqwFG == true){cZzozaqwFG = false;}
      if(ZaaqJSUBnF == true){ZaaqJSUBnF = false;}
      if(uaLLkPqKMk == true){uaLLkPqKMk = false;}
      if(WwuDpbgGHQ == true){WwuDpbgGHQ = false;}
      if(HuLcxlnFYx == true){HuLcxlnFYx = false;}
      if(uozKbCNmDi == true){uozKbCNmDi = false;}
      if(igiTjdeWAh == true){igiTjdeWAh = false;}
      if(lNtWxzOiNz == true){lNtWxzOiNz = false;}
      if(blkPogxkbm == true){blkPogxkbm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CCFXAWTGQB
{ 
  void zKIHgCaRre()
  { 
      bool mxonkEXPbH = false;
      bool uptTworeLX = false;
      bool HbjixWmOFb = false;
      bool qyUuRPzxFn = false;
      bool CKMYfHImnZ = false;
      bool TYoHwKMGpO = false;
      bool RJKzPwUyBf = false;
      bool puYXUwPLCp = false;
      bool NAaeISJNzG = false;
      bool DsHqVsAMIj = false;
      bool mJkIjYzRlz = false;
      bool uADAARieqx = false;
      bool mHztbwnhBb = false;
      bool uCCSDEORuj = false;
      bool SrazLCpHqE = false;
      bool KVULxeKqfm = false;
      bool jRPJErykww = false;
      bool DQjHeufziY = false;
      bool GgqxRZgqUX = false;
      bool tXkHzBbRuS = false;
      string zAUjplSdiC;
      string kOEKmRMGaV;
      string GqYIdshgGF;
      string fMItpCanQn;
      string IodUyGhCSa;
      string qoMIPHaLFw;
      string DlXdWXFKUj;
      string pXomMQMEKX;
      string LfNeNpAAdh;
      string aOhUjWRAxa;
      string AWghkTzZuy;
      string uWBhjXYsPf;
      string WFfmJaoUCp;
      string zLGjWoyett;
      string qaFemDNAjL;
      string yXkRDuqtYJ;
      string ddWEziQQKu;
      string ZszUowzAzF;
      string Nokqraanfb;
      string xDGjPMEBfD;
      if(zAUjplSdiC == AWghkTzZuy){mxonkEXPbH = true;}
      else if(AWghkTzZuy == zAUjplSdiC){mJkIjYzRlz = true;}
      if(kOEKmRMGaV == uWBhjXYsPf){uptTworeLX = true;}
      else if(uWBhjXYsPf == kOEKmRMGaV){uADAARieqx = true;}
      if(GqYIdshgGF == WFfmJaoUCp){HbjixWmOFb = true;}
      else if(WFfmJaoUCp == GqYIdshgGF){mHztbwnhBb = true;}
      if(fMItpCanQn == zLGjWoyett){qyUuRPzxFn = true;}
      else if(zLGjWoyett == fMItpCanQn){uCCSDEORuj = true;}
      if(IodUyGhCSa == qaFemDNAjL){CKMYfHImnZ = true;}
      else if(qaFemDNAjL == IodUyGhCSa){SrazLCpHqE = true;}
      if(qoMIPHaLFw == yXkRDuqtYJ){TYoHwKMGpO = true;}
      else if(yXkRDuqtYJ == qoMIPHaLFw){KVULxeKqfm = true;}
      if(DlXdWXFKUj == ddWEziQQKu){RJKzPwUyBf = true;}
      else if(ddWEziQQKu == DlXdWXFKUj){jRPJErykww = true;}
      if(pXomMQMEKX == ZszUowzAzF){puYXUwPLCp = true;}
      if(LfNeNpAAdh == Nokqraanfb){NAaeISJNzG = true;}
      if(aOhUjWRAxa == xDGjPMEBfD){DsHqVsAMIj = true;}
      while(ZszUowzAzF == pXomMQMEKX){DQjHeufziY = true;}
      while(Nokqraanfb == Nokqraanfb){GgqxRZgqUX = true;}
      while(xDGjPMEBfD == xDGjPMEBfD){tXkHzBbRuS = true;}
      if(mxonkEXPbH == true){mxonkEXPbH = false;}
      if(uptTworeLX == true){uptTworeLX = false;}
      if(HbjixWmOFb == true){HbjixWmOFb = false;}
      if(qyUuRPzxFn == true){qyUuRPzxFn = false;}
      if(CKMYfHImnZ == true){CKMYfHImnZ = false;}
      if(TYoHwKMGpO == true){TYoHwKMGpO = false;}
      if(RJKzPwUyBf == true){RJKzPwUyBf = false;}
      if(puYXUwPLCp == true){puYXUwPLCp = false;}
      if(NAaeISJNzG == true){NAaeISJNzG = false;}
      if(DsHqVsAMIj == true){DsHqVsAMIj = false;}
      if(mJkIjYzRlz == true){mJkIjYzRlz = false;}
      if(uADAARieqx == true){uADAARieqx = false;}
      if(mHztbwnhBb == true){mHztbwnhBb = false;}
      if(uCCSDEORuj == true){uCCSDEORuj = false;}
      if(SrazLCpHqE == true){SrazLCpHqE = false;}
      if(KVULxeKqfm == true){KVULxeKqfm = false;}
      if(jRPJErykww == true){jRPJErykww = false;}
      if(DQjHeufziY == true){DQjHeufziY = false;}
      if(GgqxRZgqUX == true){GgqxRZgqUX = false;}
      if(tXkHzBbRuS == true){tXkHzBbRuS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITEFURPJAB
{ 
  void bgOpWgAkaW()
  { 
      bool zGQImCiUow = false;
      bool VVZAodrIGJ = false;
      bool PzhgFYgxSV = false;
      bool GaMTCkIrrp = false;
      bool CTrxPNetBb = false;
      bool UcFmVAXiCN = false;
      bool VlCTotJGxD = false;
      bool UzPPGwGkRr = false;
      bool slwqAdVYyB = false;
      bool MYpeUQRYHU = false;
      bool DYxxHUMpfZ = false;
      bool tmRKUjpLSL = false;
      bool XjIupuJktp = false;
      bool dhdwnUnyie = false;
      bool QfsYHZHeJj = false;
      bool aFGwwTQBGL = false;
      bool LaupuLJUVz = false;
      bool uqbmtrqimQ = false;
      bool ndaKOYagAU = false;
      bool ElqXTojCdu = false;
      string nqXuiaaskp;
      string GOsugEFGii;
      string OpgZlfCUDh;
      string xbhsZdnDEE;
      string IXeJkmismX;
      string NwPyuxKxJC;
      string XFpCsdgAUC;
      string QBCdapKWny;
      string xIgeUBLixb;
      string TpsCgChbQG;
      string FhXjHLslXE;
      string mmIKEOXKhq;
      string SxCshZIzxX;
      string IiGgsOjxXI;
      string HZLsofhiyR;
      string dWtYnHfeCg;
      string DtnzwDgaRo;
      string eamYirlJEC;
      string rZBfslnhsk;
      string iFtpFNkLxk;
      if(nqXuiaaskp == FhXjHLslXE){zGQImCiUow = true;}
      else if(FhXjHLslXE == nqXuiaaskp){DYxxHUMpfZ = true;}
      if(GOsugEFGii == mmIKEOXKhq){VVZAodrIGJ = true;}
      else if(mmIKEOXKhq == GOsugEFGii){tmRKUjpLSL = true;}
      if(OpgZlfCUDh == SxCshZIzxX){PzhgFYgxSV = true;}
      else if(SxCshZIzxX == OpgZlfCUDh){XjIupuJktp = true;}
      if(xbhsZdnDEE == IiGgsOjxXI){GaMTCkIrrp = true;}
      else if(IiGgsOjxXI == xbhsZdnDEE){dhdwnUnyie = true;}
      if(IXeJkmismX == HZLsofhiyR){CTrxPNetBb = true;}
      else if(HZLsofhiyR == IXeJkmismX){QfsYHZHeJj = true;}
      if(NwPyuxKxJC == dWtYnHfeCg){UcFmVAXiCN = true;}
      else if(dWtYnHfeCg == NwPyuxKxJC){aFGwwTQBGL = true;}
      if(XFpCsdgAUC == DtnzwDgaRo){VlCTotJGxD = true;}
      else if(DtnzwDgaRo == XFpCsdgAUC){LaupuLJUVz = true;}
      if(QBCdapKWny == eamYirlJEC){UzPPGwGkRr = true;}
      if(xIgeUBLixb == rZBfslnhsk){slwqAdVYyB = true;}
      if(TpsCgChbQG == iFtpFNkLxk){MYpeUQRYHU = true;}
      while(eamYirlJEC == QBCdapKWny){uqbmtrqimQ = true;}
      while(rZBfslnhsk == rZBfslnhsk){ndaKOYagAU = true;}
      while(iFtpFNkLxk == iFtpFNkLxk){ElqXTojCdu = true;}
      if(zGQImCiUow == true){zGQImCiUow = false;}
      if(VVZAodrIGJ == true){VVZAodrIGJ = false;}
      if(PzhgFYgxSV == true){PzhgFYgxSV = false;}
      if(GaMTCkIrrp == true){GaMTCkIrrp = false;}
      if(CTrxPNetBb == true){CTrxPNetBb = false;}
      if(UcFmVAXiCN == true){UcFmVAXiCN = false;}
      if(VlCTotJGxD == true){VlCTotJGxD = false;}
      if(UzPPGwGkRr == true){UzPPGwGkRr = false;}
      if(slwqAdVYyB == true){slwqAdVYyB = false;}
      if(MYpeUQRYHU == true){MYpeUQRYHU = false;}
      if(DYxxHUMpfZ == true){DYxxHUMpfZ = false;}
      if(tmRKUjpLSL == true){tmRKUjpLSL = false;}
      if(XjIupuJktp == true){XjIupuJktp = false;}
      if(dhdwnUnyie == true){dhdwnUnyie = false;}
      if(QfsYHZHeJj == true){QfsYHZHeJj = false;}
      if(aFGwwTQBGL == true){aFGwwTQBGL = false;}
      if(LaupuLJUVz == true){LaupuLJUVz = false;}
      if(uqbmtrqimQ == true){uqbmtrqimQ = false;}
      if(ndaKOYagAU == true){ndaKOYagAU = false;}
      if(ElqXTojCdu == true){ElqXTojCdu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIDLKFUNAQ
{ 
  void ACPsijLVbR()
  { 
      bool gxGbBnutKw = false;
      bool aLCoLRVWjl = false;
      bool QALcQtlkEp = false;
      bool dBmSNBMsdL = false;
      bool PkPhFfnsjy = false;
      bool ubTlFglcLG = false;
      bool BKoTSZXiaJ = false;
      bool EbsXVfkdXj = false;
      bool GsAFuBhBNg = false;
      bool PjhWJEuuPf = false;
      bool IFRZsSiuPZ = false;
      bool wHFaAIKiYQ = false;
      bool rWUstUtWNR = false;
      bool joOrbBaZLb = false;
      bool SlknkHdGVB = false;
      bool tMWymljYfY = false;
      bool XMhyoHsNzz = false;
      bool gjWwyFkgIl = false;
      bool pnALWXRPEo = false;
      bool RCtmDGElyd = false;
      string dbWnCtXaHn;
      string SwksBPTKdu;
      string RIgQeLucfO;
      string RQZxcVpwxF;
      string qMdFHtrOUY;
      string rKsupUtFIp;
      string zuurWCWnPf;
      string YXNXDFeaJk;
      string TfHGVGWeGI;
      string bkmHFuQkiF;
      string XEyozUxUqk;
      string pSuWWSmnVQ;
      string eqgHEnjFSH;
      string ntrEMOhSHB;
      string IBmVRIoQjm;
      string IcORZfWqkK;
      string kqCixwaqJH;
      string kUgUHcELou;
      string zTVezLeZeg;
      string qphwPQzDXV;
      if(dbWnCtXaHn == XEyozUxUqk){gxGbBnutKw = true;}
      else if(XEyozUxUqk == dbWnCtXaHn){IFRZsSiuPZ = true;}
      if(SwksBPTKdu == pSuWWSmnVQ){aLCoLRVWjl = true;}
      else if(pSuWWSmnVQ == SwksBPTKdu){wHFaAIKiYQ = true;}
      if(RIgQeLucfO == eqgHEnjFSH){QALcQtlkEp = true;}
      else if(eqgHEnjFSH == RIgQeLucfO){rWUstUtWNR = true;}
      if(RQZxcVpwxF == ntrEMOhSHB){dBmSNBMsdL = true;}
      else if(ntrEMOhSHB == RQZxcVpwxF){joOrbBaZLb = true;}
      if(qMdFHtrOUY == IBmVRIoQjm){PkPhFfnsjy = true;}
      else if(IBmVRIoQjm == qMdFHtrOUY){SlknkHdGVB = true;}
      if(rKsupUtFIp == IcORZfWqkK){ubTlFglcLG = true;}
      else if(IcORZfWqkK == rKsupUtFIp){tMWymljYfY = true;}
      if(zuurWCWnPf == kqCixwaqJH){BKoTSZXiaJ = true;}
      else if(kqCixwaqJH == zuurWCWnPf){XMhyoHsNzz = true;}
      if(YXNXDFeaJk == kUgUHcELou){EbsXVfkdXj = true;}
      if(TfHGVGWeGI == zTVezLeZeg){GsAFuBhBNg = true;}
      if(bkmHFuQkiF == qphwPQzDXV){PjhWJEuuPf = true;}
      while(kUgUHcELou == YXNXDFeaJk){gjWwyFkgIl = true;}
      while(zTVezLeZeg == zTVezLeZeg){pnALWXRPEo = true;}
      while(qphwPQzDXV == qphwPQzDXV){RCtmDGElyd = true;}
      if(gxGbBnutKw == true){gxGbBnutKw = false;}
      if(aLCoLRVWjl == true){aLCoLRVWjl = false;}
      if(QALcQtlkEp == true){QALcQtlkEp = false;}
      if(dBmSNBMsdL == true){dBmSNBMsdL = false;}
      if(PkPhFfnsjy == true){PkPhFfnsjy = false;}
      if(ubTlFglcLG == true){ubTlFglcLG = false;}
      if(BKoTSZXiaJ == true){BKoTSZXiaJ = false;}
      if(EbsXVfkdXj == true){EbsXVfkdXj = false;}
      if(GsAFuBhBNg == true){GsAFuBhBNg = false;}
      if(PjhWJEuuPf == true){PjhWJEuuPf = false;}
      if(IFRZsSiuPZ == true){IFRZsSiuPZ = false;}
      if(wHFaAIKiYQ == true){wHFaAIKiYQ = false;}
      if(rWUstUtWNR == true){rWUstUtWNR = false;}
      if(joOrbBaZLb == true){joOrbBaZLb = false;}
      if(SlknkHdGVB == true){SlknkHdGVB = false;}
      if(tMWymljYfY == true){tMWymljYfY = false;}
      if(XMhyoHsNzz == true){XMhyoHsNzz = false;}
      if(gjWwyFkgIl == true){gjWwyFkgIl = false;}
      if(pnALWXRPEo == true){pnALWXRPEo = false;}
      if(RCtmDGElyd == true){RCtmDGElyd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JOKPHURTRC
{ 
  void KcixOrsMPH()
  { 
      bool rcpOiGFpfa = false;
      bool jxLUUuDrNP = false;
      bool mLkTQGeDew = false;
      bool aROXSPHUyg = false;
      bool rciHwjxhDY = false;
      bool plSKigqWxc = false;
      bool aBKjzShmBE = false;
      bool nitgWJbdWg = false;
      bool IxzGFozEnl = false;
      bool YjXUGpSzHd = false;
      bool BJfyjHqlmZ = false;
      bool ENAQTdBDeK = false;
      bool TdyPfDLYaf = false;
      bool pcWreyQBVx = false;
      bool xMQOhKjGAb = false;
      bool oPTwKXLQSg = false;
      bool wRLHiaqHkU = false;
      bool MAggNGMigU = false;
      bool SEYyqaJZgH = false;
      bool mAhoAeBJfG = false;
      string xKDzJFfcpQ;
      string rRGgjpLJCz;
      string fXQQxGkSUf;
      string bWWyRZSLhw;
      string SEMjLNWsWb;
      string iKMKTZsmCC;
      string UMHKoUtHPK;
      string WzbGgaKgFj;
      string jqurxQKMer;
      string ffJfaFwCup;
      string SPcLFiiFcr;
      string OMhRScROMX;
      string KhbXeqowfa;
      string eIlORTOjmN;
      string gEimcSxqMy;
      string ngoWfjmFgO;
      string smZBMGaTAy;
      string OhbzpFzotL;
      string syigmxSOhg;
      string gICYTtegZW;
      if(xKDzJFfcpQ == SPcLFiiFcr){rcpOiGFpfa = true;}
      else if(SPcLFiiFcr == xKDzJFfcpQ){BJfyjHqlmZ = true;}
      if(rRGgjpLJCz == OMhRScROMX){jxLUUuDrNP = true;}
      else if(OMhRScROMX == rRGgjpLJCz){ENAQTdBDeK = true;}
      if(fXQQxGkSUf == KhbXeqowfa){mLkTQGeDew = true;}
      else if(KhbXeqowfa == fXQQxGkSUf){TdyPfDLYaf = true;}
      if(bWWyRZSLhw == eIlORTOjmN){aROXSPHUyg = true;}
      else if(eIlORTOjmN == bWWyRZSLhw){pcWreyQBVx = true;}
      if(SEMjLNWsWb == gEimcSxqMy){rciHwjxhDY = true;}
      else if(gEimcSxqMy == SEMjLNWsWb){xMQOhKjGAb = true;}
      if(iKMKTZsmCC == ngoWfjmFgO){plSKigqWxc = true;}
      else if(ngoWfjmFgO == iKMKTZsmCC){oPTwKXLQSg = true;}
      if(UMHKoUtHPK == smZBMGaTAy){aBKjzShmBE = true;}
      else if(smZBMGaTAy == UMHKoUtHPK){wRLHiaqHkU = true;}
      if(WzbGgaKgFj == OhbzpFzotL){nitgWJbdWg = true;}
      if(jqurxQKMer == syigmxSOhg){IxzGFozEnl = true;}
      if(ffJfaFwCup == gICYTtegZW){YjXUGpSzHd = true;}
      while(OhbzpFzotL == WzbGgaKgFj){MAggNGMigU = true;}
      while(syigmxSOhg == syigmxSOhg){SEYyqaJZgH = true;}
      while(gICYTtegZW == gICYTtegZW){mAhoAeBJfG = true;}
      if(rcpOiGFpfa == true){rcpOiGFpfa = false;}
      if(jxLUUuDrNP == true){jxLUUuDrNP = false;}
      if(mLkTQGeDew == true){mLkTQGeDew = false;}
      if(aROXSPHUyg == true){aROXSPHUyg = false;}
      if(rciHwjxhDY == true){rciHwjxhDY = false;}
      if(plSKigqWxc == true){plSKigqWxc = false;}
      if(aBKjzShmBE == true){aBKjzShmBE = false;}
      if(nitgWJbdWg == true){nitgWJbdWg = false;}
      if(IxzGFozEnl == true){IxzGFozEnl = false;}
      if(YjXUGpSzHd == true){YjXUGpSzHd = false;}
      if(BJfyjHqlmZ == true){BJfyjHqlmZ = false;}
      if(ENAQTdBDeK == true){ENAQTdBDeK = false;}
      if(TdyPfDLYaf == true){TdyPfDLYaf = false;}
      if(pcWreyQBVx == true){pcWreyQBVx = false;}
      if(xMQOhKjGAb == true){xMQOhKjGAb = false;}
      if(oPTwKXLQSg == true){oPTwKXLQSg = false;}
      if(wRLHiaqHkU == true){wRLHiaqHkU = false;}
      if(MAggNGMigU == true){MAggNGMigU = false;}
      if(SEYyqaJZgH == true){SEYyqaJZgH = false;}
      if(mAhoAeBJfG == true){mAhoAeBJfG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZITAMJXVVC
{ 
  void NjoRAQJiTF()
  { 
      bool mIFchfobjQ = false;
      bool LzHRXmiUAJ = false;
      bool KOcpcCkHYi = false;
      bool YIdKDzNAGD = false;
      bool YgbwhrRebf = false;
      bool dPjwMYeOzf = false;
      bool tgDArDVxNX = false;
      bool YiNwjclfIk = false;
      bool kGfrEIXgyd = false;
      bool UzAaJrdaEd = false;
      bool VTQDHuCmMi = false;
      bool lyGOumBKwj = false;
      bool enziDZhlmq = false;
      bool yLbdPQpckJ = false;
      bool FkUOrVslfV = false;
      bool pTdUzhUgzg = false;
      bool MPAUjZWbzd = false;
      bool xXYmdtTjqg = false;
      bool gwGQBegHeg = false;
      bool uIdEwojzdR = false;
      string tLyESlYwFO;
      string TwPgpNJoYz;
      string iYrBCwOTqr;
      string bNfpNCaaRX;
      string DnDsjjXiBY;
      string ALJccVTwBV;
      string WEFMmGQZSn;
      string liXAwtVzRR;
      string YfSSrPDCMr;
      string heYuBzipFc;
      string TxQNmQnJgi;
      string ATeixqllUX;
      string DONZFHJbzw;
      string KesnybPEea;
      string atUdrNzpyJ;
      string MwVgZEjpIf;
      string HMJjXUaqjU;
      string bgHsxIsjhq;
      string HTcojOJLNs;
      string rYwzTNjkFX;
      if(tLyESlYwFO == TxQNmQnJgi){mIFchfobjQ = true;}
      else if(TxQNmQnJgi == tLyESlYwFO){VTQDHuCmMi = true;}
      if(TwPgpNJoYz == ATeixqllUX){LzHRXmiUAJ = true;}
      else if(ATeixqllUX == TwPgpNJoYz){lyGOumBKwj = true;}
      if(iYrBCwOTqr == DONZFHJbzw){KOcpcCkHYi = true;}
      else if(DONZFHJbzw == iYrBCwOTqr){enziDZhlmq = true;}
      if(bNfpNCaaRX == KesnybPEea){YIdKDzNAGD = true;}
      else if(KesnybPEea == bNfpNCaaRX){yLbdPQpckJ = true;}
      if(DnDsjjXiBY == atUdrNzpyJ){YgbwhrRebf = true;}
      else if(atUdrNzpyJ == DnDsjjXiBY){FkUOrVslfV = true;}
      if(ALJccVTwBV == MwVgZEjpIf){dPjwMYeOzf = true;}
      else if(MwVgZEjpIf == ALJccVTwBV){pTdUzhUgzg = true;}
      if(WEFMmGQZSn == HMJjXUaqjU){tgDArDVxNX = true;}
      else if(HMJjXUaqjU == WEFMmGQZSn){MPAUjZWbzd = true;}
      if(liXAwtVzRR == bgHsxIsjhq){YiNwjclfIk = true;}
      if(YfSSrPDCMr == HTcojOJLNs){kGfrEIXgyd = true;}
      if(heYuBzipFc == rYwzTNjkFX){UzAaJrdaEd = true;}
      while(bgHsxIsjhq == liXAwtVzRR){xXYmdtTjqg = true;}
      while(HTcojOJLNs == HTcojOJLNs){gwGQBegHeg = true;}
      while(rYwzTNjkFX == rYwzTNjkFX){uIdEwojzdR = true;}
      if(mIFchfobjQ == true){mIFchfobjQ = false;}
      if(LzHRXmiUAJ == true){LzHRXmiUAJ = false;}
      if(KOcpcCkHYi == true){KOcpcCkHYi = false;}
      if(YIdKDzNAGD == true){YIdKDzNAGD = false;}
      if(YgbwhrRebf == true){YgbwhrRebf = false;}
      if(dPjwMYeOzf == true){dPjwMYeOzf = false;}
      if(tgDArDVxNX == true){tgDArDVxNX = false;}
      if(YiNwjclfIk == true){YiNwjclfIk = false;}
      if(kGfrEIXgyd == true){kGfrEIXgyd = false;}
      if(UzAaJrdaEd == true){UzAaJrdaEd = false;}
      if(VTQDHuCmMi == true){VTQDHuCmMi = false;}
      if(lyGOumBKwj == true){lyGOumBKwj = false;}
      if(enziDZhlmq == true){enziDZhlmq = false;}
      if(yLbdPQpckJ == true){yLbdPQpckJ = false;}
      if(FkUOrVslfV == true){FkUOrVslfV = false;}
      if(pTdUzhUgzg == true){pTdUzhUgzg = false;}
      if(MPAUjZWbzd == true){MPAUjZWbzd = false;}
      if(xXYmdtTjqg == true){xXYmdtTjqg = false;}
      if(gwGQBegHeg == true){gwGQBegHeg = false;}
      if(uIdEwojzdR == true){uIdEwojzdR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSWFPTHGUD
{ 
  void FFAnzgWrWu()
  { 
      bool imxyQHIqiu = false;
      bool DYJwHEXRlP = false;
      bool IknwOcstcj = false;
      bool RDEeMwuCaA = false;
      bool MzqhLFpLSJ = false;
      bool OmZcKxzBin = false;
      bool NOOzdATeiK = false;
      bool JVqlDJtFjJ = false;
      bool lhaTVecbTP = false;
      bool xtSllxkqEL = false;
      bool kLbIArwnYB = false;
      bool DsQZBfntdz = false;
      bool WrLTMOCEAF = false;
      bool XCAYXaFRSc = false;
      bool hoDRLDcsjF = false;
      bool JpNFnszIwk = false;
      bool pqmScAsrBa = false;
      bool aVbBQhnsII = false;
      bool lITuuhoujd = false;
      bool bxUhlqCjnK = false;
      string CoTnmlwarr;
      string ZJwjmxoWYl;
      string MRYCPoPFpZ;
      string ecPHbFlemE;
      string EzFCBlmhSr;
      string LBRtukQQYy;
      string VpkSMwsnIg;
      string KJiUgMMWBc;
      string BhmyOdKUMq;
      string oUGohOOmoE;
      string rzYkgBSwNh;
      string YsPwwmDlEi;
      string kYbQroDsmS;
      string xYgxjCJBRM;
      string LOHdSuFJru;
      string KciGSTWIsq;
      string yYJtkzMSLt;
      string dCUqWWQyyw;
      string jsAqHUpadP;
      string eAIZOmEMsT;
      if(CoTnmlwarr == rzYkgBSwNh){imxyQHIqiu = true;}
      else if(rzYkgBSwNh == CoTnmlwarr){kLbIArwnYB = true;}
      if(ZJwjmxoWYl == YsPwwmDlEi){DYJwHEXRlP = true;}
      else if(YsPwwmDlEi == ZJwjmxoWYl){DsQZBfntdz = true;}
      if(MRYCPoPFpZ == kYbQroDsmS){IknwOcstcj = true;}
      else if(kYbQroDsmS == MRYCPoPFpZ){WrLTMOCEAF = true;}
      if(ecPHbFlemE == xYgxjCJBRM){RDEeMwuCaA = true;}
      else if(xYgxjCJBRM == ecPHbFlemE){XCAYXaFRSc = true;}
      if(EzFCBlmhSr == LOHdSuFJru){MzqhLFpLSJ = true;}
      else if(LOHdSuFJru == EzFCBlmhSr){hoDRLDcsjF = true;}
      if(LBRtukQQYy == KciGSTWIsq){OmZcKxzBin = true;}
      else if(KciGSTWIsq == LBRtukQQYy){JpNFnszIwk = true;}
      if(VpkSMwsnIg == yYJtkzMSLt){NOOzdATeiK = true;}
      else if(yYJtkzMSLt == VpkSMwsnIg){pqmScAsrBa = true;}
      if(KJiUgMMWBc == dCUqWWQyyw){JVqlDJtFjJ = true;}
      if(BhmyOdKUMq == jsAqHUpadP){lhaTVecbTP = true;}
      if(oUGohOOmoE == eAIZOmEMsT){xtSllxkqEL = true;}
      while(dCUqWWQyyw == KJiUgMMWBc){aVbBQhnsII = true;}
      while(jsAqHUpadP == jsAqHUpadP){lITuuhoujd = true;}
      while(eAIZOmEMsT == eAIZOmEMsT){bxUhlqCjnK = true;}
      if(imxyQHIqiu == true){imxyQHIqiu = false;}
      if(DYJwHEXRlP == true){DYJwHEXRlP = false;}
      if(IknwOcstcj == true){IknwOcstcj = false;}
      if(RDEeMwuCaA == true){RDEeMwuCaA = false;}
      if(MzqhLFpLSJ == true){MzqhLFpLSJ = false;}
      if(OmZcKxzBin == true){OmZcKxzBin = false;}
      if(NOOzdATeiK == true){NOOzdATeiK = false;}
      if(JVqlDJtFjJ == true){JVqlDJtFjJ = false;}
      if(lhaTVecbTP == true){lhaTVecbTP = false;}
      if(xtSllxkqEL == true){xtSllxkqEL = false;}
      if(kLbIArwnYB == true){kLbIArwnYB = false;}
      if(DsQZBfntdz == true){DsQZBfntdz = false;}
      if(WrLTMOCEAF == true){WrLTMOCEAF = false;}
      if(XCAYXaFRSc == true){XCAYXaFRSc = false;}
      if(hoDRLDcsjF == true){hoDRLDcsjF = false;}
      if(JpNFnszIwk == true){JpNFnszIwk = false;}
      if(pqmScAsrBa == true){pqmScAsrBa = false;}
      if(aVbBQhnsII == true){aVbBQhnsII = false;}
      if(lITuuhoujd == true){lITuuhoujd = false;}
      if(bxUhlqCjnK == true){bxUhlqCjnK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDVYIHZJTS
{ 
  void MkUhzFXpws()
  { 
      bool htyToVUSWJ = false;
      bool WmnYXGwyPq = false;
      bool TFSQeqOYZd = false;
      bool qWaDsgCIoQ = false;
      bool xUZoZZPOnr = false;
      bool AuNlVcagox = false;
      bool GwsrSALjfq = false;
      bool EnJzsyedqF = false;
      bool bAjhcuInhP = false;
      bool FUSqKBbgWZ = false;
      bool NehxmMkOsW = false;
      bool yxoiVFMLPW = false;
      bool qXCPkjURnr = false;
      bool WyGRrwRltQ = false;
      bool JtuKRHeiVE = false;
      bool nQRzhocSLD = false;
      bool qTZAzApXqZ = false;
      bool mZQzMxcqxc = false;
      bool EkujEGfHjC = false;
      bool SzapYpTuKR = false;
      string awbZamCCOW;
      string EMGDHuUnfl;
      string jiMTMqCHCH;
      string riiocPgJrB;
      string KEeYWjCwFB;
      string fJVoPriIMj;
      string ktzHeUcRZr;
      string NKwdaeEnwc;
      string nFCAbiNtYk;
      string fYwHPQFXsC;
      string HjVNnUMqNj;
      string nuMjufryew;
      string HhsoLnNnOK;
      string ZfttVDjoMG;
      string VWgnwjMMLj;
      string XGrxtYqfBz;
      string HYcCKHBSNq;
      string uCkYakBErb;
      string aAbdlSnwzx;
      string MDnMywtddo;
      if(awbZamCCOW == HjVNnUMqNj){htyToVUSWJ = true;}
      else if(HjVNnUMqNj == awbZamCCOW){NehxmMkOsW = true;}
      if(EMGDHuUnfl == nuMjufryew){WmnYXGwyPq = true;}
      else if(nuMjufryew == EMGDHuUnfl){yxoiVFMLPW = true;}
      if(jiMTMqCHCH == HhsoLnNnOK){TFSQeqOYZd = true;}
      else if(HhsoLnNnOK == jiMTMqCHCH){qXCPkjURnr = true;}
      if(riiocPgJrB == ZfttVDjoMG){qWaDsgCIoQ = true;}
      else if(ZfttVDjoMG == riiocPgJrB){WyGRrwRltQ = true;}
      if(KEeYWjCwFB == VWgnwjMMLj){xUZoZZPOnr = true;}
      else if(VWgnwjMMLj == KEeYWjCwFB){JtuKRHeiVE = true;}
      if(fJVoPriIMj == XGrxtYqfBz){AuNlVcagox = true;}
      else if(XGrxtYqfBz == fJVoPriIMj){nQRzhocSLD = true;}
      if(ktzHeUcRZr == HYcCKHBSNq){GwsrSALjfq = true;}
      else if(HYcCKHBSNq == ktzHeUcRZr){qTZAzApXqZ = true;}
      if(NKwdaeEnwc == uCkYakBErb){EnJzsyedqF = true;}
      if(nFCAbiNtYk == aAbdlSnwzx){bAjhcuInhP = true;}
      if(fYwHPQFXsC == MDnMywtddo){FUSqKBbgWZ = true;}
      while(uCkYakBErb == NKwdaeEnwc){mZQzMxcqxc = true;}
      while(aAbdlSnwzx == aAbdlSnwzx){EkujEGfHjC = true;}
      while(MDnMywtddo == MDnMywtddo){SzapYpTuKR = true;}
      if(htyToVUSWJ == true){htyToVUSWJ = false;}
      if(WmnYXGwyPq == true){WmnYXGwyPq = false;}
      if(TFSQeqOYZd == true){TFSQeqOYZd = false;}
      if(qWaDsgCIoQ == true){qWaDsgCIoQ = false;}
      if(xUZoZZPOnr == true){xUZoZZPOnr = false;}
      if(AuNlVcagox == true){AuNlVcagox = false;}
      if(GwsrSALjfq == true){GwsrSALjfq = false;}
      if(EnJzsyedqF == true){EnJzsyedqF = false;}
      if(bAjhcuInhP == true){bAjhcuInhP = false;}
      if(FUSqKBbgWZ == true){FUSqKBbgWZ = false;}
      if(NehxmMkOsW == true){NehxmMkOsW = false;}
      if(yxoiVFMLPW == true){yxoiVFMLPW = false;}
      if(qXCPkjURnr == true){qXCPkjURnr = false;}
      if(WyGRrwRltQ == true){WyGRrwRltQ = false;}
      if(JtuKRHeiVE == true){JtuKRHeiVE = false;}
      if(nQRzhocSLD == true){nQRzhocSLD = false;}
      if(qTZAzApXqZ == true){qTZAzApXqZ = false;}
      if(mZQzMxcqxc == true){mZQzMxcqxc = false;}
      if(EkujEGfHjC == true){EkujEGfHjC = false;}
      if(SzapYpTuKR == true){SzapYpTuKR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMWFGNRJOJ
{ 
  void KCfCCPrtGo()
  { 
      bool YAOQhiMiaw = false;
      bool fbWJnjUQXf = false;
      bool ZnMKJLkYaD = false;
      bool PwkhzANAgW = false;
      bool xRTRyahiec = false;
      bool QGRVrknDGW = false;
      bool xmHWfiqnJn = false;
      bool VUiAhHTtLh = false;
      bool dCtymIePpO = false;
      bool LKsKZJKxkP = false;
      bool jsYpGwWRmj = false;
      bool RsqYrusJjW = false;
      bool EayucLaYaX = false;
      bool xWJwxjcDrp = false;
      bool lNbGxRSUSe = false;
      bool QAMNKJudNt = false;
      bool UypOltjtaH = false;
      bool RpQskqyrxK = false;
      bool rFFuHwJukn = false;
      bool ozpxUmWNTC = false;
      string yQBdgFdFWG;
      string EZOEQgYHzw;
      string QihATmLjZm;
      string oJBiLiCADo;
      string LoWtYxZMux;
      string SkHiiOhBJs;
      string tsfiQuYerg;
      string dXEKkaMnbW;
      string NyocUECRAw;
      string BBqJuRJmcc;
      string YtUOStfwyH;
      string BsYmfuEDOM;
      string sGewfcgtPT;
      string QZKyxSdaJZ;
      string XFTrtHbEdz;
      string MGXPjSOYhp;
      string MlgdpbhaoN;
      string QdsnonlmBY;
      string BcQPGKBtNe;
      string DFrTMlXoBS;
      if(yQBdgFdFWG == YtUOStfwyH){YAOQhiMiaw = true;}
      else if(YtUOStfwyH == yQBdgFdFWG){jsYpGwWRmj = true;}
      if(EZOEQgYHzw == BsYmfuEDOM){fbWJnjUQXf = true;}
      else if(BsYmfuEDOM == EZOEQgYHzw){RsqYrusJjW = true;}
      if(QihATmLjZm == sGewfcgtPT){ZnMKJLkYaD = true;}
      else if(sGewfcgtPT == QihATmLjZm){EayucLaYaX = true;}
      if(oJBiLiCADo == QZKyxSdaJZ){PwkhzANAgW = true;}
      else if(QZKyxSdaJZ == oJBiLiCADo){xWJwxjcDrp = true;}
      if(LoWtYxZMux == XFTrtHbEdz){xRTRyahiec = true;}
      else if(XFTrtHbEdz == LoWtYxZMux){lNbGxRSUSe = true;}
      if(SkHiiOhBJs == MGXPjSOYhp){QGRVrknDGW = true;}
      else if(MGXPjSOYhp == SkHiiOhBJs){QAMNKJudNt = true;}
      if(tsfiQuYerg == MlgdpbhaoN){xmHWfiqnJn = true;}
      else if(MlgdpbhaoN == tsfiQuYerg){UypOltjtaH = true;}
      if(dXEKkaMnbW == QdsnonlmBY){VUiAhHTtLh = true;}
      if(NyocUECRAw == BcQPGKBtNe){dCtymIePpO = true;}
      if(BBqJuRJmcc == DFrTMlXoBS){LKsKZJKxkP = true;}
      while(QdsnonlmBY == dXEKkaMnbW){RpQskqyrxK = true;}
      while(BcQPGKBtNe == BcQPGKBtNe){rFFuHwJukn = true;}
      while(DFrTMlXoBS == DFrTMlXoBS){ozpxUmWNTC = true;}
      if(YAOQhiMiaw == true){YAOQhiMiaw = false;}
      if(fbWJnjUQXf == true){fbWJnjUQXf = false;}
      if(ZnMKJLkYaD == true){ZnMKJLkYaD = false;}
      if(PwkhzANAgW == true){PwkhzANAgW = false;}
      if(xRTRyahiec == true){xRTRyahiec = false;}
      if(QGRVrknDGW == true){QGRVrknDGW = false;}
      if(xmHWfiqnJn == true){xmHWfiqnJn = false;}
      if(VUiAhHTtLh == true){VUiAhHTtLh = false;}
      if(dCtymIePpO == true){dCtymIePpO = false;}
      if(LKsKZJKxkP == true){LKsKZJKxkP = false;}
      if(jsYpGwWRmj == true){jsYpGwWRmj = false;}
      if(RsqYrusJjW == true){RsqYrusJjW = false;}
      if(EayucLaYaX == true){EayucLaYaX = false;}
      if(xWJwxjcDrp == true){xWJwxjcDrp = false;}
      if(lNbGxRSUSe == true){lNbGxRSUSe = false;}
      if(QAMNKJudNt == true){QAMNKJudNt = false;}
      if(UypOltjtaH == true){UypOltjtaH = false;}
      if(RpQskqyrxK == true){RpQskqyrxK = false;}
      if(rFFuHwJukn == true){rFFuHwJukn = false;}
      if(ozpxUmWNTC == true){ozpxUmWNTC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFMSQOLNDY
{ 
  void DHAQKPsgXJ()
  { 
      bool IJhAClMWuK = false;
      bool DYmYffSwVn = false;
      bool pcFRBZHyGc = false;
      bool XaMZQmWmQo = false;
      bool UKxbkVWMWE = false;
      bool HodxheEQyb = false;
      bool dNQSlbLNHs = false;
      bool JfefTffdff = false;
      bool DtaCUixPrl = false;
      bool hGnoKGseoI = false;
      bool JJFdtbJxdC = false;
      bool zajSYimOyD = false;
      bool ewVVKDqpVM = false;
      bool lAnXVsowHr = false;
      bool YzkolHWVPa = false;
      bool TefkdNnjTq = false;
      bool kTbRQylMwe = false;
      bool tpHFdfKfiC = false;
      bool gUZtsGUCtI = false;
      bool FFcPGFXTYm = false;
      string EVsDSeFdFa;
      string CCLUlraTCs;
      string fMbEDGVnmq;
      string OSagImqQXc;
      string anoyPfJsBd;
      string pnuXIqsozL;
      string JQqNMibeMy;
      string BKwZRqWdnX;
      string xcmIBZWDXQ;
      string tCQLTJwakg;
      string DegCberVFQ;
      string UOAaOfdhMl;
      string LYGuEztkGH;
      string uwrHTSwjgV;
      string hBxHweCowm;
      string fNNzUeXkyc;
      string kHPxVXWrGw;
      string jsBqDJazyZ;
      string wEnSbghsmo;
      string tKlDjalzlX;
      if(EVsDSeFdFa == DegCberVFQ){IJhAClMWuK = true;}
      else if(DegCberVFQ == EVsDSeFdFa){JJFdtbJxdC = true;}
      if(CCLUlraTCs == UOAaOfdhMl){DYmYffSwVn = true;}
      else if(UOAaOfdhMl == CCLUlraTCs){zajSYimOyD = true;}
      if(fMbEDGVnmq == LYGuEztkGH){pcFRBZHyGc = true;}
      else if(LYGuEztkGH == fMbEDGVnmq){ewVVKDqpVM = true;}
      if(OSagImqQXc == uwrHTSwjgV){XaMZQmWmQo = true;}
      else if(uwrHTSwjgV == OSagImqQXc){lAnXVsowHr = true;}
      if(anoyPfJsBd == hBxHweCowm){UKxbkVWMWE = true;}
      else if(hBxHweCowm == anoyPfJsBd){YzkolHWVPa = true;}
      if(pnuXIqsozL == fNNzUeXkyc){HodxheEQyb = true;}
      else if(fNNzUeXkyc == pnuXIqsozL){TefkdNnjTq = true;}
      if(JQqNMibeMy == kHPxVXWrGw){dNQSlbLNHs = true;}
      else if(kHPxVXWrGw == JQqNMibeMy){kTbRQylMwe = true;}
      if(BKwZRqWdnX == jsBqDJazyZ){JfefTffdff = true;}
      if(xcmIBZWDXQ == wEnSbghsmo){DtaCUixPrl = true;}
      if(tCQLTJwakg == tKlDjalzlX){hGnoKGseoI = true;}
      while(jsBqDJazyZ == BKwZRqWdnX){tpHFdfKfiC = true;}
      while(wEnSbghsmo == wEnSbghsmo){gUZtsGUCtI = true;}
      while(tKlDjalzlX == tKlDjalzlX){FFcPGFXTYm = true;}
      if(IJhAClMWuK == true){IJhAClMWuK = false;}
      if(DYmYffSwVn == true){DYmYffSwVn = false;}
      if(pcFRBZHyGc == true){pcFRBZHyGc = false;}
      if(XaMZQmWmQo == true){XaMZQmWmQo = false;}
      if(UKxbkVWMWE == true){UKxbkVWMWE = false;}
      if(HodxheEQyb == true){HodxheEQyb = false;}
      if(dNQSlbLNHs == true){dNQSlbLNHs = false;}
      if(JfefTffdff == true){JfefTffdff = false;}
      if(DtaCUixPrl == true){DtaCUixPrl = false;}
      if(hGnoKGseoI == true){hGnoKGseoI = false;}
      if(JJFdtbJxdC == true){JJFdtbJxdC = false;}
      if(zajSYimOyD == true){zajSYimOyD = false;}
      if(ewVVKDqpVM == true){ewVVKDqpVM = false;}
      if(lAnXVsowHr == true){lAnXVsowHr = false;}
      if(YzkolHWVPa == true){YzkolHWVPa = false;}
      if(TefkdNnjTq == true){TefkdNnjTq = false;}
      if(kTbRQylMwe == true){kTbRQylMwe = false;}
      if(tpHFdfKfiC == true){tpHFdfKfiC = false;}
      if(gUZtsGUCtI == true){gUZtsGUCtI = false;}
      if(FFcPGFXTYm == true){FFcPGFXTYm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQQERIYHQN
{ 
  void CQMlDoHJqJ()
  { 
      bool LWYRBlprCJ = false;
      bool lbVSrgRXid = false;
      bool EGTEAirIhJ = false;
      bool mHYSZXDJHb = false;
      bool YQPhBtmuAD = false;
      bool CDdCnFDTRR = false;
      bool shKrWeCDrT = false;
      bool dIPHEnplCF = false;
      bool uxHdHicVeU = false;
      bool UiqphqFXLW = false;
      bool qjCgZsnWyA = false;
      bool ORQLWwZfkm = false;
      bool BfYXztRZYM = false;
      bool hSZfNLtaEN = false;
      bool uGXeFDReTk = false;
      bool RYlYULKegf = false;
      bool bNxlRwqkyK = false;
      bool CzbWquItRu = false;
      bool blGnuIfBKC = false;
      bool BPsXlgJkMJ = false;
      string APMbaLQqJY;
      string bVKQpmbigy;
      string paQYGinAHA;
      string ILfFNJybFA;
      string eIhpMZRAHH;
      string DlRUfZznVq;
      string WPiJPQoEDf;
      string oAcgTgrZLg;
      string QnrAxWsKYm;
      string JKGNcOZXZu;
      string kNxaSCIkBz;
      string hYbnZiWiMs;
      string WdePWdsODE;
      string GTAPuDpRgt;
      string NIJZFkiRnt;
      string qqLgXGhgEn;
      string JsgwsNYLsV;
      string rFBSeOUFKl;
      string ubaJNPISqn;
      string VJNskUaMfr;
      if(APMbaLQqJY == kNxaSCIkBz){LWYRBlprCJ = true;}
      else if(kNxaSCIkBz == APMbaLQqJY){qjCgZsnWyA = true;}
      if(bVKQpmbigy == hYbnZiWiMs){lbVSrgRXid = true;}
      else if(hYbnZiWiMs == bVKQpmbigy){ORQLWwZfkm = true;}
      if(paQYGinAHA == WdePWdsODE){EGTEAirIhJ = true;}
      else if(WdePWdsODE == paQYGinAHA){BfYXztRZYM = true;}
      if(ILfFNJybFA == GTAPuDpRgt){mHYSZXDJHb = true;}
      else if(GTAPuDpRgt == ILfFNJybFA){hSZfNLtaEN = true;}
      if(eIhpMZRAHH == NIJZFkiRnt){YQPhBtmuAD = true;}
      else if(NIJZFkiRnt == eIhpMZRAHH){uGXeFDReTk = true;}
      if(DlRUfZznVq == qqLgXGhgEn){CDdCnFDTRR = true;}
      else if(qqLgXGhgEn == DlRUfZznVq){RYlYULKegf = true;}
      if(WPiJPQoEDf == JsgwsNYLsV){shKrWeCDrT = true;}
      else if(JsgwsNYLsV == WPiJPQoEDf){bNxlRwqkyK = true;}
      if(oAcgTgrZLg == rFBSeOUFKl){dIPHEnplCF = true;}
      if(QnrAxWsKYm == ubaJNPISqn){uxHdHicVeU = true;}
      if(JKGNcOZXZu == VJNskUaMfr){UiqphqFXLW = true;}
      while(rFBSeOUFKl == oAcgTgrZLg){CzbWquItRu = true;}
      while(ubaJNPISqn == ubaJNPISqn){blGnuIfBKC = true;}
      while(VJNskUaMfr == VJNskUaMfr){BPsXlgJkMJ = true;}
      if(LWYRBlprCJ == true){LWYRBlprCJ = false;}
      if(lbVSrgRXid == true){lbVSrgRXid = false;}
      if(EGTEAirIhJ == true){EGTEAirIhJ = false;}
      if(mHYSZXDJHb == true){mHYSZXDJHb = false;}
      if(YQPhBtmuAD == true){YQPhBtmuAD = false;}
      if(CDdCnFDTRR == true){CDdCnFDTRR = false;}
      if(shKrWeCDrT == true){shKrWeCDrT = false;}
      if(dIPHEnplCF == true){dIPHEnplCF = false;}
      if(uxHdHicVeU == true){uxHdHicVeU = false;}
      if(UiqphqFXLW == true){UiqphqFXLW = false;}
      if(qjCgZsnWyA == true){qjCgZsnWyA = false;}
      if(ORQLWwZfkm == true){ORQLWwZfkm = false;}
      if(BfYXztRZYM == true){BfYXztRZYM = false;}
      if(hSZfNLtaEN == true){hSZfNLtaEN = false;}
      if(uGXeFDReTk == true){uGXeFDReTk = false;}
      if(RYlYULKegf == true){RYlYULKegf = false;}
      if(bNxlRwqkyK == true){bNxlRwqkyK = false;}
      if(CzbWquItRu == true){CzbWquItRu = false;}
      if(blGnuIfBKC == true){blGnuIfBKC = false;}
      if(BPsXlgJkMJ == true){BPsXlgJkMJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POZQWGYBQE
{ 
  void bQbUFCQbyR()
  { 
      bool bOlkgnRAlz = false;
      bool aRpqLkAYln = false;
      bool uOpFffQypB = false;
      bool kyKoftNAxF = false;
      bool eYquiJABgk = false;
      bool ubfmrNYgEB = false;
      bool WSJkNbHBLQ = false;
      bool WzagIWWuWW = false;
      bool ePRFFJSXwR = false;
      bool VgwwhMOFgG = false;
      bool BzoQOwAzdV = false;
      bool qcKhWHAEfE = false;
      bool IjEttpDeyu = false;
      bool HQOPUeaBqJ = false;
      bool ITsZasWNZZ = false;
      bool MKZcyRuuVY = false;
      bool rVAhOZOtNr = false;
      bool gyNVuopdSB = false;
      bool SpEXiwqkRC = false;
      bool iefSQmTKLB = false;
      string AzZeCcWtXD;
      string WWMDIIRKEN;
      string bUSGDidzxG;
      string ZskLxGiuAj;
      string WJzqCsBMdE;
      string KaFOJefTaT;
      string zWwQcclAFC;
      string ZWKTqSVaDJ;
      string gRUrwynVCS;
      string ZPTfkzMhNY;
      string HBGbenQkXp;
      string IFPRmgCEUe;
      string nPxmbJCdhq;
      string FmMeCeKrNH;
      string hDyLJUzCrD;
      string xINijrDTzU;
      string klCfkVrkPH;
      string WJqMwkQkcH;
      string JAldsxZdtJ;
      string bqrrVuARan;
      if(AzZeCcWtXD == HBGbenQkXp){bOlkgnRAlz = true;}
      else if(HBGbenQkXp == AzZeCcWtXD){BzoQOwAzdV = true;}
      if(WWMDIIRKEN == IFPRmgCEUe){aRpqLkAYln = true;}
      else if(IFPRmgCEUe == WWMDIIRKEN){qcKhWHAEfE = true;}
      if(bUSGDidzxG == nPxmbJCdhq){uOpFffQypB = true;}
      else if(nPxmbJCdhq == bUSGDidzxG){IjEttpDeyu = true;}
      if(ZskLxGiuAj == FmMeCeKrNH){kyKoftNAxF = true;}
      else if(FmMeCeKrNH == ZskLxGiuAj){HQOPUeaBqJ = true;}
      if(WJzqCsBMdE == hDyLJUzCrD){eYquiJABgk = true;}
      else if(hDyLJUzCrD == WJzqCsBMdE){ITsZasWNZZ = true;}
      if(KaFOJefTaT == xINijrDTzU){ubfmrNYgEB = true;}
      else if(xINijrDTzU == KaFOJefTaT){MKZcyRuuVY = true;}
      if(zWwQcclAFC == klCfkVrkPH){WSJkNbHBLQ = true;}
      else if(klCfkVrkPH == zWwQcclAFC){rVAhOZOtNr = true;}
      if(ZWKTqSVaDJ == WJqMwkQkcH){WzagIWWuWW = true;}
      if(gRUrwynVCS == JAldsxZdtJ){ePRFFJSXwR = true;}
      if(ZPTfkzMhNY == bqrrVuARan){VgwwhMOFgG = true;}
      while(WJqMwkQkcH == ZWKTqSVaDJ){gyNVuopdSB = true;}
      while(JAldsxZdtJ == JAldsxZdtJ){SpEXiwqkRC = true;}
      while(bqrrVuARan == bqrrVuARan){iefSQmTKLB = true;}
      if(bOlkgnRAlz == true){bOlkgnRAlz = false;}
      if(aRpqLkAYln == true){aRpqLkAYln = false;}
      if(uOpFffQypB == true){uOpFffQypB = false;}
      if(kyKoftNAxF == true){kyKoftNAxF = false;}
      if(eYquiJABgk == true){eYquiJABgk = false;}
      if(ubfmrNYgEB == true){ubfmrNYgEB = false;}
      if(WSJkNbHBLQ == true){WSJkNbHBLQ = false;}
      if(WzagIWWuWW == true){WzagIWWuWW = false;}
      if(ePRFFJSXwR == true){ePRFFJSXwR = false;}
      if(VgwwhMOFgG == true){VgwwhMOFgG = false;}
      if(BzoQOwAzdV == true){BzoQOwAzdV = false;}
      if(qcKhWHAEfE == true){qcKhWHAEfE = false;}
      if(IjEttpDeyu == true){IjEttpDeyu = false;}
      if(HQOPUeaBqJ == true){HQOPUeaBqJ = false;}
      if(ITsZasWNZZ == true){ITsZasWNZZ = false;}
      if(MKZcyRuuVY == true){MKZcyRuuVY = false;}
      if(rVAhOZOtNr == true){rVAhOZOtNr = false;}
      if(gyNVuopdSB == true){gyNVuopdSB = false;}
      if(SpEXiwqkRC == true){SpEXiwqkRC = false;}
      if(iefSQmTKLB == true){iefSQmTKLB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUMNBOHCMT
{ 
  void fRZTAObkQP()
  { 
      bool INcNhXMuUV = false;
      bool IwgUsPWplH = false;
      bool rqFqSNpTnr = false;
      bool qGeMckyYer = false;
      bool UGuktJantA = false;
      bool IOQOrRHktU = false;
      bool hrHceCQUqH = false;
      bool QyLslkuUxJ = false;
      bool mBYmibpQTL = false;
      bool cMdJKbzSGr = false;
      bool rFxliJDWbH = false;
      bool VmnkhfTTsD = false;
      bool MAAfdETBhJ = false;
      bool kcOEQgEmDY = false;
      bool YSnMopYsbe = false;
      bool IeYDfrFQHe = false;
      bool pBnRVsXiUA = false;
      bool bfPUdsLmqm = false;
      bool eaYDBFDLYX = false;
      bool ameYiWdVqu = false;
      string MmHHutOpze;
      string QZSxxyqBhJ;
      string wwHQqyyVGi;
      string tdPAsNHDMG;
      string goeqOqfItJ;
      string gWxSxPfqPw;
      string wrjPkmKREj;
      string qnobbGRPCA;
      string SobxCXfwDc;
      string gQmQKnFOGa;
      string fNEKRshVpp;
      string yQoOdGQlNN;
      string HOOaCZAXRn;
      string BDIaUEkQeI;
      string oKFMeQbXlD;
      string XTArTRycHr;
      string rJECotHNtY;
      string UzGEXxICwl;
      string yblNQhCPHC;
      string FHJmQfFCWj;
      if(MmHHutOpze == fNEKRshVpp){INcNhXMuUV = true;}
      else if(fNEKRshVpp == MmHHutOpze){rFxliJDWbH = true;}
      if(QZSxxyqBhJ == yQoOdGQlNN){IwgUsPWplH = true;}
      else if(yQoOdGQlNN == QZSxxyqBhJ){VmnkhfTTsD = true;}
      if(wwHQqyyVGi == HOOaCZAXRn){rqFqSNpTnr = true;}
      else if(HOOaCZAXRn == wwHQqyyVGi){MAAfdETBhJ = true;}
      if(tdPAsNHDMG == BDIaUEkQeI){qGeMckyYer = true;}
      else if(BDIaUEkQeI == tdPAsNHDMG){kcOEQgEmDY = true;}
      if(goeqOqfItJ == oKFMeQbXlD){UGuktJantA = true;}
      else if(oKFMeQbXlD == goeqOqfItJ){YSnMopYsbe = true;}
      if(gWxSxPfqPw == XTArTRycHr){IOQOrRHktU = true;}
      else if(XTArTRycHr == gWxSxPfqPw){IeYDfrFQHe = true;}
      if(wrjPkmKREj == rJECotHNtY){hrHceCQUqH = true;}
      else if(rJECotHNtY == wrjPkmKREj){pBnRVsXiUA = true;}
      if(qnobbGRPCA == UzGEXxICwl){QyLslkuUxJ = true;}
      if(SobxCXfwDc == yblNQhCPHC){mBYmibpQTL = true;}
      if(gQmQKnFOGa == FHJmQfFCWj){cMdJKbzSGr = true;}
      while(UzGEXxICwl == qnobbGRPCA){bfPUdsLmqm = true;}
      while(yblNQhCPHC == yblNQhCPHC){eaYDBFDLYX = true;}
      while(FHJmQfFCWj == FHJmQfFCWj){ameYiWdVqu = true;}
      if(INcNhXMuUV == true){INcNhXMuUV = false;}
      if(IwgUsPWplH == true){IwgUsPWplH = false;}
      if(rqFqSNpTnr == true){rqFqSNpTnr = false;}
      if(qGeMckyYer == true){qGeMckyYer = false;}
      if(UGuktJantA == true){UGuktJantA = false;}
      if(IOQOrRHktU == true){IOQOrRHktU = false;}
      if(hrHceCQUqH == true){hrHceCQUqH = false;}
      if(QyLslkuUxJ == true){QyLslkuUxJ = false;}
      if(mBYmibpQTL == true){mBYmibpQTL = false;}
      if(cMdJKbzSGr == true){cMdJKbzSGr = false;}
      if(rFxliJDWbH == true){rFxliJDWbH = false;}
      if(VmnkhfTTsD == true){VmnkhfTTsD = false;}
      if(MAAfdETBhJ == true){MAAfdETBhJ = false;}
      if(kcOEQgEmDY == true){kcOEQgEmDY = false;}
      if(YSnMopYsbe == true){YSnMopYsbe = false;}
      if(IeYDfrFQHe == true){IeYDfrFQHe = false;}
      if(pBnRVsXiUA == true){pBnRVsXiUA = false;}
      if(bfPUdsLmqm == true){bfPUdsLmqm = false;}
      if(eaYDBFDLYX == true){eaYDBFDLYX = false;}
      if(ameYiWdVqu == true){ameYiWdVqu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZDLUVWAFL
{ 
  void JlRtYaZsiP()
  { 
      bool qlbVbVQigQ = false;
      bool iEtxwZychn = false;
      bool QhASgadDDa = false;
      bool YtJeYXPPoG = false;
      bool ZxYYwUBnTV = false;
      bool cAcRUIlJoA = false;
      bool qNfGqotOYY = false;
      bool JinaNTJaWM = false;
      bool YpihxYQrJQ = false;
      bool kGZnPMQRhG = false;
      bool ZmPuLtMCDB = false;
      bool yKlcbAexJR = false;
      bool YCEHmDIzLB = false;
      bool CrsPllanWC = false;
      bool MNnIRaUxMO = false;
      bool hTIQgXhHHH = false;
      bool lMpCyGQVpo = false;
      bool ZpaGEKNwpM = false;
      bool iKmxTiichO = false;
      bool DSfOQAXlJL = false;
      string BdnbJUqZUW;
      string kDFSgfPnRm;
      string naKrWoYUSE;
      string yggHWbUAxY;
      string XjNWtlVHMD;
      string CnBmMZSuFT;
      string uWHPXDVxwE;
      string LPqrPEMnyk;
      string SRHPBJettw;
      string JYuccBcxyp;
      string QXKIrmxJXI;
      string MdxTBdPqOO;
      string XaCAulTNPN;
      string bPpHUtGzWO;
      string LVVliebabz;
      string lkijSoVKNG;
      string SjsKfxnozG;
      string WPTzCCFQQP;
      string JrkQbqfFof;
      string YwlQubcLGl;
      if(BdnbJUqZUW == QXKIrmxJXI){qlbVbVQigQ = true;}
      else if(QXKIrmxJXI == BdnbJUqZUW){ZmPuLtMCDB = true;}
      if(kDFSgfPnRm == MdxTBdPqOO){iEtxwZychn = true;}
      else if(MdxTBdPqOO == kDFSgfPnRm){yKlcbAexJR = true;}
      if(naKrWoYUSE == XaCAulTNPN){QhASgadDDa = true;}
      else if(XaCAulTNPN == naKrWoYUSE){YCEHmDIzLB = true;}
      if(yggHWbUAxY == bPpHUtGzWO){YtJeYXPPoG = true;}
      else if(bPpHUtGzWO == yggHWbUAxY){CrsPllanWC = true;}
      if(XjNWtlVHMD == LVVliebabz){ZxYYwUBnTV = true;}
      else if(LVVliebabz == XjNWtlVHMD){MNnIRaUxMO = true;}
      if(CnBmMZSuFT == lkijSoVKNG){cAcRUIlJoA = true;}
      else if(lkijSoVKNG == CnBmMZSuFT){hTIQgXhHHH = true;}
      if(uWHPXDVxwE == SjsKfxnozG){qNfGqotOYY = true;}
      else if(SjsKfxnozG == uWHPXDVxwE){lMpCyGQVpo = true;}
      if(LPqrPEMnyk == WPTzCCFQQP){JinaNTJaWM = true;}
      if(SRHPBJettw == JrkQbqfFof){YpihxYQrJQ = true;}
      if(JYuccBcxyp == YwlQubcLGl){kGZnPMQRhG = true;}
      while(WPTzCCFQQP == LPqrPEMnyk){ZpaGEKNwpM = true;}
      while(JrkQbqfFof == JrkQbqfFof){iKmxTiichO = true;}
      while(YwlQubcLGl == YwlQubcLGl){DSfOQAXlJL = true;}
      if(qlbVbVQigQ == true){qlbVbVQigQ = false;}
      if(iEtxwZychn == true){iEtxwZychn = false;}
      if(QhASgadDDa == true){QhASgadDDa = false;}
      if(YtJeYXPPoG == true){YtJeYXPPoG = false;}
      if(ZxYYwUBnTV == true){ZxYYwUBnTV = false;}
      if(cAcRUIlJoA == true){cAcRUIlJoA = false;}
      if(qNfGqotOYY == true){qNfGqotOYY = false;}
      if(JinaNTJaWM == true){JinaNTJaWM = false;}
      if(YpihxYQrJQ == true){YpihxYQrJQ = false;}
      if(kGZnPMQRhG == true){kGZnPMQRhG = false;}
      if(ZmPuLtMCDB == true){ZmPuLtMCDB = false;}
      if(yKlcbAexJR == true){yKlcbAexJR = false;}
      if(YCEHmDIzLB == true){YCEHmDIzLB = false;}
      if(CrsPllanWC == true){CrsPllanWC = false;}
      if(MNnIRaUxMO == true){MNnIRaUxMO = false;}
      if(hTIQgXhHHH == true){hTIQgXhHHH = false;}
      if(lMpCyGQVpo == true){lMpCyGQVpo = false;}
      if(ZpaGEKNwpM == true){ZpaGEKNwpM = false;}
      if(iKmxTiichO == true){iKmxTiichO = false;}
      if(DSfOQAXlJL == true){DSfOQAXlJL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHFLZECRFJ
{ 
  void LJkcEDIDoJ()
  { 
      bool CthuUJeiNZ = false;
      bool OosLFkyjRl = false;
      bool kKDeCNRzgQ = false;
      bool pEkRyJFtrg = false;
      bool lQrrgRQfuu = false;
      bool RkuzmrqDrG = false;
      bool rfBxiKEaMu = false;
      bool eDqkATRKxk = false;
      bool wlEkyFIkeG = false;
      bool RBBkoGPuIW = false;
      bool MpSzQNsKyS = false;
      bool ZgGHKFaPyd = false;
      bool BTwGddCFut = false;
      bool EWCaYGTFUk = false;
      bool LymMfkusaj = false;
      bool ezwdVssLUm = false;
      bool LnOENCdeiE = false;
      bool lVuNSCgjZr = false;
      bool hIeLOEaXEf = false;
      bool MHjhZXjhyd = false;
      string ScOCsFaczU;
      string hlminiUfTZ;
      string eXgaBXJabF;
      string xkEhnhaMDF;
      string hpKBKDeenm;
      string dKQMouwmBV;
      string wAAtWxgFtG;
      string IIbOrnMePy;
      string sdloalTrrs;
      string kmLhJgpPdN;
      string VYkheVhCUB;
      string iRXCcRNKSj;
      string coMAUUwtEK;
      string xwACbTsEKF;
      string DRWpKTPIEr;
      string TewtjgMjMJ;
      string YnxJElQUZJ;
      string XJANfKRWpB;
      string EnoMqRAGRu;
      string HJqAfPUNlY;
      if(ScOCsFaczU == VYkheVhCUB){CthuUJeiNZ = true;}
      else if(VYkheVhCUB == ScOCsFaczU){MpSzQNsKyS = true;}
      if(hlminiUfTZ == iRXCcRNKSj){OosLFkyjRl = true;}
      else if(iRXCcRNKSj == hlminiUfTZ){ZgGHKFaPyd = true;}
      if(eXgaBXJabF == coMAUUwtEK){kKDeCNRzgQ = true;}
      else if(coMAUUwtEK == eXgaBXJabF){BTwGddCFut = true;}
      if(xkEhnhaMDF == xwACbTsEKF){pEkRyJFtrg = true;}
      else if(xwACbTsEKF == xkEhnhaMDF){EWCaYGTFUk = true;}
      if(hpKBKDeenm == DRWpKTPIEr){lQrrgRQfuu = true;}
      else if(DRWpKTPIEr == hpKBKDeenm){LymMfkusaj = true;}
      if(dKQMouwmBV == TewtjgMjMJ){RkuzmrqDrG = true;}
      else if(TewtjgMjMJ == dKQMouwmBV){ezwdVssLUm = true;}
      if(wAAtWxgFtG == YnxJElQUZJ){rfBxiKEaMu = true;}
      else if(YnxJElQUZJ == wAAtWxgFtG){LnOENCdeiE = true;}
      if(IIbOrnMePy == XJANfKRWpB){eDqkATRKxk = true;}
      if(sdloalTrrs == EnoMqRAGRu){wlEkyFIkeG = true;}
      if(kmLhJgpPdN == HJqAfPUNlY){RBBkoGPuIW = true;}
      while(XJANfKRWpB == IIbOrnMePy){lVuNSCgjZr = true;}
      while(EnoMqRAGRu == EnoMqRAGRu){hIeLOEaXEf = true;}
      while(HJqAfPUNlY == HJqAfPUNlY){MHjhZXjhyd = true;}
      if(CthuUJeiNZ == true){CthuUJeiNZ = false;}
      if(OosLFkyjRl == true){OosLFkyjRl = false;}
      if(kKDeCNRzgQ == true){kKDeCNRzgQ = false;}
      if(pEkRyJFtrg == true){pEkRyJFtrg = false;}
      if(lQrrgRQfuu == true){lQrrgRQfuu = false;}
      if(RkuzmrqDrG == true){RkuzmrqDrG = false;}
      if(rfBxiKEaMu == true){rfBxiKEaMu = false;}
      if(eDqkATRKxk == true){eDqkATRKxk = false;}
      if(wlEkyFIkeG == true){wlEkyFIkeG = false;}
      if(RBBkoGPuIW == true){RBBkoGPuIW = false;}
      if(MpSzQNsKyS == true){MpSzQNsKyS = false;}
      if(ZgGHKFaPyd == true){ZgGHKFaPyd = false;}
      if(BTwGddCFut == true){BTwGddCFut = false;}
      if(EWCaYGTFUk == true){EWCaYGTFUk = false;}
      if(LymMfkusaj == true){LymMfkusaj = false;}
      if(ezwdVssLUm == true){ezwdVssLUm = false;}
      if(LnOENCdeiE == true){LnOENCdeiE = false;}
      if(lVuNSCgjZr == true){lVuNSCgjZr = false;}
      if(hIeLOEaXEf == true){hIeLOEaXEf = false;}
      if(MHjhZXjhyd == true){MHjhZXjhyd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOFTNZSXTK
{ 
  void ORpStpqZMB()
  { 
      bool BYhOESgKAa = false;
      bool AWFzWVjEfz = false;
      bool jgCoDXEOHm = false;
      bool iseVKwCloy = false;
      bool PnTiRMPwUw = false;
      bool ZiWyaUVsKg = false;
      bool NSDMqHrjoZ = false;
      bool TxOgjuMTWq = false;
      bool IItLNzWfuo = false;
      bool ZIaIjwkHqK = false;
      bool TeHtbbUoOe = false;
      bool HCVTYFYqzr = false;
      bool kLnzzKWGxm = false;
      bool KEcMXcBzik = false;
      bool egRPhXlHie = false;
      bool XsIzYIpHtR = false;
      bool FOqbTCYJww = false;
      bool DYINMDsYQb = false;
      bool XPWRORwdmO = false;
      bool lsFReQopwe = false;
      string iGqIxojQda;
      string wDSfkDhWKb;
      string IAdHdXTtta;
      string yKZTtzpswT;
      string QxjTrVTyLM;
      string VOgrrhcieY;
      string UoVCclcylk;
      string NnZpKLQJOH;
      string DUhhFicgbL;
      string VGNWyaagqG;
      string rVMazgnqgg;
      string RTUXUAHnxs;
      string IuWZOHaDrj;
      string jiRHPhHHiX;
      string ulztsClpBx;
      string SmjyxwzlLr;
      string GkyxwiBMHm;
      string rAFYyWubgL;
      string UjBtQxzTJS;
      string iUuqRKmCxK;
      if(iGqIxojQda == rVMazgnqgg){BYhOESgKAa = true;}
      else if(rVMazgnqgg == iGqIxojQda){TeHtbbUoOe = true;}
      if(wDSfkDhWKb == RTUXUAHnxs){AWFzWVjEfz = true;}
      else if(RTUXUAHnxs == wDSfkDhWKb){HCVTYFYqzr = true;}
      if(IAdHdXTtta == IuWZOHaDrj){jgCoDXEOHm = true;}
      else if(IuWZOHaDrj == IAdHdXTtta){kLnzzKWGxm = true;}
      if(yKZTtzpswT == jiRHPhHHiX){iseVKwCloy = true;}
      else if(jiRHPhHHiX == yKZTtzpswT){KEcMXcBzik = true;}
      if(QxjTrVTyLM == ulztsClpBx){PnTiRMPwUw = true;}
      else if(ulztsClpBx == QxjTrVTyLM){egRPhXlHie = true;}
      if(VOgrrhcieY == SmjyxwzlLr){ZiWyaUVsKg = true;}
      else if(SmjyxwzlLr == VOgrrhcieY){XsIzYIpHtR = true;}
      if(UoVCclcylk == GkyxwiBMHm){NSDMqHrjoZ = true;}
      else if(GkyxwiBMHm == UoVCclcylk){FOqbTCYJww = true;}
      if(NnZpKLQJOH == rAFYyWubgL){TxOgjuMTWq = true;}
      if(DUhhFicgbL == UjBtQxzTJS){IItLNzWfuo = true;}
      if(VGNWyaagqG == iUuqRKmCxK){ZIaIjwkHqK = true;}
      while(rAFYyWubgL == NnZpKLQJOH){DYINMDsYQb = true;}
      while(UjBtQxzTJS == UjBtQxzTJS){XPWRORwdmO = true;}
      while(iUuqRKmCxK == iUuqRKmCxK){lsFReQopwe = true;}
      if(BYhOESgKAa == true){BYhOESgKAa = false;}
      if(AWFzWVjEfz == true){AWFzWVjEfz = false;}
      if(jgCoDXEOHm == true){jgCoDXEOHm = false;}
      if(iseVKwCloy == true){iseVKwCloy = false;}
      if(PnTiRMPwUw == true){PnTiRMPwUw = false;}
      if(ZiWyaUVsKg == true){ZiWyaUVsKg = false;}
      if(NSDMqHrjoZ == true){NSDMqHrjoZ = false;}
      if(TxOgjuMTWq == true){TxOgjuMTWq = false;}
      if(IItLNzWfuo == true){IItLNzWfuo = false;}
      if(ZIaIjwkHqK == true){ZIaIjwkHqK = false;}
      if(TeHtbbUoOe == true){TeHtbbUoOe = false;}
      if(HCVTYFYqzr == true){HCVTYFYqzr = false;}
      if(kLnzzKWGxm == true){kLnzzKWGxm = false;}
      if(KEcMXcBzik == true){KEcMXcBzik = false;}
      if(egRPhXlHie == true){egRPhXlHie = false;}
      if(XsIzYIpHtR == true){XsIzYIpHtR = false;}
      if(FOqbTCYJww == true){FOqbTCYJww = false;}
      if(DYINMDsYQb == true){DYINMDsYQb = false;}
      if(XPWRORwdmO == true){XPWRORwdmO = false;}
      if(lsFReQopwe == true){lsFReQopwe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYFZIXNYRA
{ 
  void PBMIxWwkAG()
  { 
      bool ViQceaTNyB = false;
      bool VIjGEtXwNq = false;
      bool JOJLZYNKXM = false;
      bool GOTPYlBcZY = false;
      bool UxmHtSNjzd = false;
      bool duBdPHZFCG = false;
      bool MIoktGnUgR = false;
      bool suVnWMbBRH = false;
      bool LcLtiLNpAR = false;
      bool LuZTLLHBMm = false;
      bool esDgkiYMHC = false;
      bool eXnutjxuCh = false;
      bool syUOGxUBbK = false;
      bool EZodcSZeJz = false;
      bool lAhxlnHdZb = false;
      bool OMzdsfYoam = false;
      bool NXkwyFiJSa = false;
      bool KSkCwrPWbR = false;
      bool pqbzwqZKkw = false;
      bool tjDWlOPlyg = false;
      string MOJOklenbq;
      string QtzNUzrmeo;
      string pFGkCwKVVg;
      string BUSEreBwuX;
      string iroylgidJu;
      string UGQyAHIYMn;
      string aIRtouatUo;
      string yuqGFxPIyV;
      string NfMZLtEUDk;
      string WbjGxaatIp;
      string FnITwYOKrC;
      string qAZqatwriu;
      string qGpiSWLkIe;
      string WVzIPYWrcl;
      string fscBtWBseC;
      string ehKNzzxYBZ;
      string NdCNfUARbB;
      string WDOxOydoou;
      string VSFFAnKlIP;
      string axpDYCqOUY;
      if(MOJOklenbq == FnITwYOKrC){ViQceaTNyB = true;}
      else if(FnITwYOKrC == MOJOklenbq){esDgkiYMHC = true;}
      if(QtzNUzrmeo == qAZqatwriu){VIjGEtXwNq = true;}
      else if(qAZqatwriu == QtzNUzrmeo){eXnutjxuCh = true;}
      if(pFGkCwKVVg == qGpiSWLkIe){JOJLZYNKXM = true;}
      else if(qGpiSWLkIe == pFGkCwKVVg){syUOGxUBbK = true;}
      if(BUSEreBwuX == WVzIPYWrcl){GOTPYlBcZY = true;}
      else if(WVzIPYWrcl == BUSEreBwuX){EZodcSZeJz = true;}
      if(iroylgidJu == fscBtWBseC){UxmHtSNjzd = true;}
      else if(fscBtWBseC == iroylgidJu){lAhxlnHdZb = true;}
      if(UGQyAHIYMn == ehKNzzxYBZ){duBdPHZFCG = true;}
      else if(ehKNzzxYBZ == UGQyAHIYMn){OMzdsfYoam = true;}
      if(aIRtouatUo == NdCNfUARbB){MIoktGnUgR = true;}
      else if(NdCNfUARbB == aIRtouatUo){NXkwyFiJSa = true;}
      if(yuqGFxPIyV == WDOxOydoou){suVnWMbBRH = true;}
      if(NfMZLtEUDk == VSFFAnKlIP){LcLtiLNpAR = true;}
      if(WbjGxaatIp == axpDYCqOUY){LuZTLLHBMm = true;}
      while(WDOxOydoou == yuqGFxPIyV){KSkCwrPWbR = true;}
      while(VSFFAnKlIP == VSFFAnKlIP){pqbzwqZKkw = true;}
      while(axpDYCqOUY == axpDYCqOUY){tjDWlOPlyg = true;}
      if(ViQceaTNyB == true){ViQceaTNyB = false;}
      if(VIjGEtXwNq == true){VIjGEtXwNq = false;}
      if(JOJLZYNKXM == true){JOJLZYNKXM = false;}
      if(GOTPYlBcZY == true){GOTPYlBcZY = false;}
      if(UxmHtSNjzd == true){UxmHtSNjzd = false;}
      if(duBdPHZFCG == true){duBdPHZFCG = false;}
      if(MIoktGnUgR == true){MIoktGnUgR = false;}
      if(suVnWMbBRH == true){suVnWMbBRH = false;}
      if(LcLtiLNpAR == true){LcLtiLNpAR = false;}
      if(LuZTLLHBMm == true){LuZTLLHBMm = false;}
      if(esDgkiYMHC == true){esDgkiYMHC = false;}
      if(eXnutjxuCh == true){eXnutjxuCh = false;}
      if(syUOGxUBbK == true){syUOGxUBbK = false;}
      if(EZodcSZeJz == true){EZodcSZeJz = false;}
      if(lAhxlnHdZb == true){lAhxlnHdZb = false;}
      if(OMzdsfYoam == true){OMzdsfYoam = false;}
      if(NXkwyFiJSa == true){NXkwyFiJSa = false;}
      if(KSkCwrPWbR == true){KSkCwrPWbR = false;}
      if(pqbzwqZKkw == true){pqbzwqZKkw = false;}
      if(tjDWlOPlyg == true){tjDWlOPlyg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THXDKKXXWJ
{ 
  void UkxWmyqzfG()
  { 
      bool cnMMGoEWKl = false;
      bool PSbEToOilI = false;
      bool hLCjgTQUtL = false;
      bool SWljusDeyN = false;
      bool BxASOEHtdX = false;
      bool HoBnJRlbem = false;
      bool YicyTrgqJZ = false;
      bool kjkXGkKiVb = false;
      bool LVqWEcVxad = false;
      bool HazLoSUBzV = false;
      bool XPkDlWDchX = false;
      bool GCGDaCrFtp = false;
      bool WiQeSJjYhn = false;
      bool QJjzDwkmjg = false;
      bool ZrPCWEUwkm = false;
      bool aPHIynyFkb = false;
      bool metsHwRGAd = false;
      bool QFUMQeTNIN = false;
      bool onmuNABbBO = false;
      bool xfCIttxVuZ = false;
      string OBUPTVoTwS;
      string GeQfDANzXM;
      string JFSRiSOXVD;
      string NkVRJHmawH;
      string LnyJCUwywq;
      string lTTxMJhDfA;
      string GRxrFUJzWw;
      string MmDPBUGION;
      string WPadRsQXEz;
      string YjtuBtqGEg;
      string KxbzdyPDwr;
      string DZnRdqpSaL;
      string EluXWcrIOG;
      string dADhDZnazS;
      string cNbLuzubQJ;
      string DXescYBEcB;
      string FGnoODVGOE;
      string DOTHhqJibX;
      string hQqFDFUKEd;
      string XiyyMWYmxr;
      if(OBUPTVoTwS == KxbzdyPDwr){cnMMGoEWKl = true;}
      else if(KxbzdyPDwr == OBUPTVoTwS){XPkDlWDchX = true;}
      if(GeQfDANzXM == DZnRdqpSaL){PSbEToOilI = true;}
      else if(DZnRdqpSaL == GeQfDANzXM){GCGDaCrFtp = true;}
      if(JFSRiSOXVD == EluXWcrIOG){hLCjgTQUtL = true;}
      else if(EluXWcrIOG == JFSRiSOXVD){WiQeSJjYhn = true;}
      if(NkVRJHmawH == dADhDZnazS){SWljusDeyN = true;}
      else if(dADhDZnazS == NkVRJHmawH){QJjzDwkmjg = true;}
      if(LnyJCUwywq == cNbLuzubQJ){BxASOEHtdX = true;}
      else if(cNbLuzubQJ == LnyJCUwywq){ZrPCWEUwkm = true;}
      if(lTTxMJhDfA == DXescYBEcB){HoBnJRlbem = true;}
      else if(DXescYBEcB == lTTxMJhDfA){aPHIynyFkb = true;}
      if(GRxrFUJzWw == FGnoODVGOE){YicyTrgqJZ = true;}
      else if(FGnoODVGOE == GRxrFUJzWw){metsHwRGAd = true;}
      if(MmDPBUGION == DOTHhqJibX){kjkXGkKiVb = true;}
      if(WPadRsQXEz == hQqFDFUKEd){LVqWEcVxad = true;}
      if(YjtuBtqGEg == XiyyMWYmxr){HazLoSUBzV = true;}
      while(DOTHhqJibX == MmDPBUGION){QFUMQeTNIN = true;}
      while(hQqFDFUKEd == hQqFDFUKEd){onmuNABbBO = true;}
      while(XiyyMWYmxr == XiyyMWYmxr){xfCIttxVuZ = true;}
      if(cnMMGoEWKl == true){cnMMGoEWKl = false;}
      if(PSbEToOilI == true){PSbEToOilI = false;}
      if(hLCjgTQUtL == true){hLCjgTQUtL = false;}
      if(SWljusDeyN == true){SWljusDeyN = false;}
      if(BxASOEHtdX == true){BxASOEHtdX = false;}
      if(HoBnJRlbem == true){HoBnJRlbem = false;}
      if(YicyTrgqJZ == true){YicyTrgqJZ = false;}
      if(kjkXGkKiVb == true){kjkXGkKiVb = false;}
      if(LVqWEcVxad == true){LVqWEcVxad = false;}
      if(HazLoSUBzV == true){HazLoSUBzV = false;}
      if(XPkDlWDchX == true){XPkDlWDchX = false;}
      if(GCGDaCrFtp == true){GCGDaCrFtp = false;}
      if(WiQeSJjYhn == true){WiQeSJjYhn = false;}
      if(QJjzDwkmjg == true){QJjzDwkmjg = false;}
      if(ZrPCWEUwkm == true){ZrPCWEUwkm = false;}
      if(aPHIynyFkb == true){aPHIynyFkb = false;}
      if(metsHwRGAd == true){metsHwRGAd = false;}
      if(QFUMQeTNIN == true){QFUMQeTNIN = false;}
      if(onmuNABbBO == true){onmuNABbBO = false;}
      if(xfCIttxVuZ == true){xfCIttxVuZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUOEWGDDGU
{ 
  void uNIqMzPgDB()
  { 
      bool RxoANqGtHr = false;
      bool GGEqxyKNZm = false;
      bool aUAySLDVUE = false;
      bool JzyABOymhJ = false;
      bool wxRUxfbNGf = false;
      bool wdMNHxwpgB = false;
      bool mkZDiHHEpi = false;
      bool AXePpdCfBl = false;
      bool ipPnHflkrE = false;
      bool RHFfVLWOlo = false;
      bool XXWWfYyxWd = false;
      bool uQouRxUluC = false;
      bool UVLlQrRyte = false;
      bool GmsLOLSrIi = false;
      bool goOOIBSKOY = false;
      bool qkTjUCLkGm = false;
      bool GACqWHXcfF = false;
      bool eccMVfGxcP = false;
      bool ZHjVnVTJqM = false;
      bool AgkVbglWqB = false;
      string CosPpJJZWo;
      string DhKpuXBkud;
      string HDXPaBDcoX;
      string dpqyCPNeqZ;
      string EDIuJjKKVr;
      string nifAeyQcnn;
      string FfjzKMqLme;
      string JVtVYDucFp;
      string qrHwitKpTE;
      string zjpCTXTJjw;
      string syWqiRoKba;
      string DmXyxNYmPQ;
      string CArifYfqBA;
      string jksIwrUQNQ;
      string EAOrALMqEG;
      string zfsTtsGnLJ;
      string lxIaqRtOCE;
      string rIZzLBlziT;
      string MnmuBDqZND;
      string lgEDeHqmAh;
      if(CosPpJJZWo == syWqiRoKba){RxoANqGtHr = true;}
      else if(syWqiRoKba == CosPpJJZWo){XXWWfYyxWd = true;}
      if(DhKpuXBkud == DmXyxNYmPQ){GGEqxyKNZm = true;}
      else if(DmXyxNYmPQ == DhKpuXBkud){uQouRxUluC = true;}
      if(HDXPaBDcoX == CArifYfqBA){aUAySLDVUE = true;}
      else if(CArifYfqBA == HDXPaBDcoX){UVLlQrRyte = true;}
      if(dpqyCPNeqZ == jksIwrUQNQ){JzyABOymhJ = true;}
      else if(jksIwrUQNQ == dpqyCPNeqZ){GmsLOLSrIi = true;}
      if(EDIuJjKKVr == EAOrALMqEG){wxRUxfbNGf = true;}
      else if(EAOrALMqEG == EDIuJjKKVr){goOOIBSKOY = true;}
      if(nifAeyQcnn == zfsTtsGnLJ){wdMNHxwpgB = true;}
      else if(zfsTtsGnLJ == nifAeyQcnn){qkTjUCLkGm = true;}
      if(FfjzKMqLme == lxIaqRtOCE){mkZDiHHEpi = true;}
      else if(lxIaqRtOCE == FfjzKMqLme){GACqWHXcfF = true;}
      if(JVtVYDucFp == rIZzLBlziT){AXePpdCfBl = true;}
      if(qrHwitKpTE == MnmuBDqZND){ipPnHflkrE = true;}
      if(zjpCTXTJjw == lgEDeHqmAh){RHFfVLWOlo = true;}
      while(rIZzLBlziT == JVtVYDucFp){eccMVfGxcP = true;}
      while(MnmuBDqZND == MnmuBDqZND){ZHjVnVTJqM = true;}
      while(lgEDeHqmAh == lgEDeHqmAh){AgkVbglWqB = true;}
      if(RxoANqGtHr == true){RxoANqGtHr = false;}
      if(GGEqxyKNZm == true){GGEqxyKNZm = false;}
      if(aUAySLDVUE == true){aUAySLDVUE = false;}
      if(JzyABOymhJ == true){JzyABOymhJ = false;}
      if(wxRUxfbNGf == true){wxRUxfbNGf = false;}
      if(wdMNHxwpgB == true){wdMNHxwpgB = false;}
      if(mkZDiHHEpi == true){mkZDiHHEpi = false;}
      if(AXePpdCfBl == true){AXePpdCfBl = false;}
      if(ipPnHflkrE == true){ipPnHflkrE = false;}
      if(RHFfVLWOlo == true){RHFfVLWOlo = false;}
      if(XXWWfYyxWd == true){XXWWfYyxWd = false;}
      if(uQouRxUluC == true){uQouRxUluC = false;}
      if(UVLlQrRyte == true){UVLlQrRyte = false;}
      if(GmsLOLSrIi == true){GmsLOLSrIi = false;}
      if(goOOIBSKOY == true){goOOIBSKOY = false;}
      if(qkTjUCLkGm == true){qkTjUCLkGm = false;}
      if(GACqWHXcfF == true){GACqWHXcfF = false;}
      if(eccMVfGxcP == true){eccMVfGxcP = false;}
      if(ZHjVnVTJqM == true){ZHjVnVTJqM = false;}
      if(AgkVbglWqB == true){AgkVbglWqB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJESQFLJZC
{ 
  void SzHwtUPJlY()
  { 
      bool HDmGVyJUPN = false;
      bool phbeKQizti = false;
      bool XStYSigQIk = false;
      bool hoaDDLqrdR = false;
      bool OKxBatbNFB = false;
      bool xhqNVoJOnl = false;
      bool RsLdeAGXaz = false;
      bool ZqVcTNUsxX = false;
      bool HSKHnAyMhO = false;
      bool BcEqzVySVZ = false;
      bool nDmGaFLOtH = false;
      bool TQQPeyhEpe = false;
      bool CsoMxwmdcx = false;
      bool OBWWjDfEfh = false;
      bool niSatkMnLA = false;
      bool mtcpXtOZId = false;
      bool ShlwsSssfb = false;
      bool ScXIqSaOSM = false;
      bool jyRbKTYgzp = false;
      bool oFwCOGxVgb = false;
      string AhqZDMHwsu;
      string PgnxHROMan;
      string LGzZbGuYfk;
      string QeQhXudBdq;
      string QesrIEowAo;
      string RRqVEshRxw;
      string QhPIejQGZL;
      string nMhiWfNHQW;
      string RzXqSyntcd;
      string NMEgZhPkNY;
      string niVoAEiHyY;
      string fZAZeQJXof;
      string uWcwyaIBIo;
      string QbtriidipN;
      string OfuEymMdCJ;
      string YqwgcRFZpZ;
      string whzJHEfIpu;
      string mZgaRPaXxK;
      string OeyzPYfNOR;
      string cDsQRfgkws;
      if(AhqZDMHwsu == niVoAEiHyY){HDmGVyJUPN = true;}
      else if(niVoAEiHyY == AhqZDMHwsu){nDmGaFLOtH = true;}
      if(PgnxHROMan == fZAZeQJXof){phbeKQizti = true;}
      else if(fZAZeQJXof == PgnxHROMan){TQQPeyhEpe = true;}
      if(LGzZbGuYfk == uWcwyaIBIo){XStYSigQIk = true;}
      else if(uWcwyaIBIo == LGzZbGuYfk){CsoMxwmdcx = true;}
      if(QeQhXudBdq == QbtriidipN){hoaDDLqrdR = true;}
      else if(QbtriidipN == QeQhXudBdq){OBWWjDfEfh = true;}
      if(QesrIEowAo == OfuEymMdCJ){OKxBatbNFB = true;}
      else if(OfuEymMdCJ == QesrIEowAo){niSatkMnLA = true;}
      if(RRqVEshRxw == YqwgcRFZpZ){xhqNVoJOnl = true;}
      else if(YqwgcRFZpZ == RRqVEshRxw){mtcpXtOZId = true;}
      if(QhPIejQGZL == whzJHEfIpu){RsLdeAGXaz = true;}
      else if(whzJHEfIpu == QhPIejQGZL){ShlwsSssfb = true;}
      if(nMhiWfNHQW == mZgaRPaXxK){ZqVcTNUsxX = true;}
      if(RzXqSyntcd == OeyzPYfNOR){HSKHnAyMhO = true;}
      if(NMEgZhPkNY == cDsQRfgkws){BcEqzVySVZ = true;}
      while(mZgaRPaXxK == nMhiWfNHQW){ScXIqSaOSM = true;}
      while(OeyzPYfNOR == OeyzPYfNOR){jyRbKTYgzp = true;}
      while(cDsQRfgkws == cDsQRfgkws){oFwCOGxVgb = true;}
      if(HDmGVyJUPN == true){HDmGVyJUPN = false;}
      if(phbeKQizti == true){phbeKQizti = false;}
      if(XStYSigQIk == true){XStYSigQIk = false;}
      if(hoaDDLqrdR == true){hoaDDLqrdR = false;}
      if(OKxBatbNFB == true){OKxBatbNFB = false;}
      if(xhqNVoJOnl == true){xhqNVoJOnl = false;}
      if(RsLdeAGXaz == true){RsLdeAGXaz = false;}
      if(ZqVcTNUsxX == true){ZqVcTNUsxX = false;}
      if(HSKHnAyMhO == true){HSKHnAyMhO = false;}
      if(BcEqzVySVZ == true){BcEqzVySVZ = false;}
      if(nDmGaFLOtH == true){nDmGaFLOtH = false;}
      if(TQQPeyhEpe == true){TQQPeyhEpe = false;}
      if(CsoMxwmdcx == true){CsoMxwmdcx = false;}
      if(OBWWjDfEfh == true){OBWWjDfEfh = false;}
      if(niSatkMnLA == true){niSatkMnLA = false;}
      if(mtcpXtOZId == true){mtcpXtOZId = false;}
      if(ShlwsSssfb == true){ShlwsSssfb = false;}
      if(ScXIqSaOSM == true){ScXIqSaOSM = false;}
      if(jyRbKTYgzp == true){jyRbKTYgzp = false;}
      if(oFwCOGxVgb == true){oFwCOGxVgb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYIRDWSPCH
{ 
  void VyAcytIMTk()
  { 
      bool CRhZRYlkCd = false;
      bool qJbKmjRYhf = false;
      bool dAIWkSbSGS = false;
      bool cdtjHuXror = false;
      bool eBkyfUAgtP = false;
      bool hbBjnCJKnz = false;
      bool xSejBNPrDr = false;
      bool MZjoBbOKpP = false;
      bool RtYqjBbJuF = false;
      bool lNDotLWBwS = false;
      bool FHdCCIqLhL = false;
      bool mzTYhCtmzA = false;
      bool kFwxFyVuup = false;
      bool EMNXKJQWnb = false;
      bool JQajRlseHr = false;
      bool QjCwhzKfwD = false;
      bool lwPrGZkwOX = false;
      bool lXzXpTdMfT = false;
      bool FqnCYUKRoK = false;
      bool zjZjpNAhdq = false;
      string hGrGigQwkH;
      string RZgLCleXdh;
      string jTfSJaFxJY;
      string dWmrtNxwLr;
      string uJBAOjigLH;
      string ICnwbOaZwH;
      string aTlMculoQn;
      string oiLllaSeEZ;
      string rXkCPaiqPe;
      string mXzEQbWnWT;
      string ysPWSZqBJB;
      string uwUWODhjwC;
      string LtYkBQiHUK;
      string DdIjbzHNip;
      string jhhOipCcoN;
      string slqUIDTeVB;
      string pjgyxRnjuP;
      string uTAGSdMKCK;
      string NFRHQQmmbX;
      string ecrhzAAiQR;
      if(hGrGigQwkH == ysPWSZqBJB){CRhZRYlkCd = true;}
      else if(ysPWSZqBJB == hGrGigQwkH){FHdCCIqLhL = true;}
      if(RZgLCleXdh == uwUWODhjwC){qJbKmjRYhf = true;}
      else if(uwUWODhjwC == RZgLCleXdh){mzTYhCtmzA = true;}
      if(jTfSJaFxJY == LtYkBQiHUK){dAIWkSbSGS = true;}
      else if(LtYkBQiHUK == jTfSJaFxJY){kFwxFyVuup = true;}
      if(dWmrtNxwLr == DdIjbzHNip){cdtjHuXror = true;}
      else if(DdIjbzHNip == dWmrtNxwLr){EMNXKJQWnb = true;}
      if(uJBAOjigLH == jhhOipCcoN){eBkyfUAgtP = true;}
      else if(jhhOipCcoN == uJBAOjigLH){JQajRlseHr = true;}
      if(ICnwbOaZwH == slqUIDTeVB){hbBjnCJKnz = true;}
      else if(slqUIDTeVB == ICnwbOaZwH){QjCwhzKfwD = true;}
      if(aTlMculoQn == pjgyxRnjuP){xSejBNPrDr = true;}
      else if(pjgyxRnjuP == aTlMculoQn){lwPrGZkwOX = true;}
      if(oiLllaSeEZ == uTAGSdMKCK){MZjoBbOKpP = true;}
      if(rXkCPaiqPe == NFRHQQmmbX){RtYqjBbJuF = true;}
      if(mXzEQbWnWT == ecrhzAAiQR){lNDotLWBwS = true;}
      while(uTAGSdMKCK == oiLllaSeEZ){lXzXpTdMfT = true;}
      while(NFRHQQmmbX == NFRHQQmmbX){FqnCYUKRoK = true;}
      while(ecrhzAAiQR == ecrhzAAiQR){zjZjpNAhdq = true;}
      if(CRhZRYlkCd == true){CRhZRYlkCd = false;}
      if(qJbKmjRYhf == true){qJbKmjRYhf = false;}
      if(dAIWkSbSGS == true){dAIWkSbSGS = false;}
      if(cdtjHuXror == true){cdtjHuXror = false;}
      if(eBkyfUAgtP == true){eBkyfUAgtP = false;}
      if(hbBjnCJKnz == true){hbBjnCJKnz = false;}
      if(xSejBNPrDr == true){xSejBNPrDr = false;}
      if(MZjoBbOKpP == true){MZjoBbOKpP = false;}
      if(RtYqjBbJuF == true){RtYqjBbJuF = false;}
      if(lNDotLWBwS == true){lNDotLWBwS = false;}
      if(FHdCCIqLhL == true){FHdCCIqLhL = false;}
      if(mzTYhCtmzA == true){mzTYhCtmzA = false;}
      if(kFwxFyVuup == true){kFwxFyVuup = false;}
      if(EMNXKJQWnb == true){EMNXKJQWnb = false;}
      if(JQajRlseHr == true){JQajRlseHr = false;}
      if(QjCwhzKfwD == true){QjCwhzKfwD = false;}
      if(lwPrGZkwOX == true){lwPrGZkwOX = false;}
      if(lXzXpTdMfT == true){lXzXpTdMfT = false;}
      if(FqnCYUKRoK == true){FqnCYUKRoK = false;}
      if(zjZjpNAhdq == true){zjZjpNAhdq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQDXWPICCV
{ 
  void SwRSGslkdR()
  { 
      bool qPMopFBfzD = false;
      bool SldidOLhga = false;
      bool dHoTOAlJSg = false;
      bool bWfsnFxHCV = false;
      bool snPNxSGgwO = false;
      bool okYCSjZrZo = false;
      bool TrNRawFktY = false;
      bool REfKgpqbVw = false;
      bool tFMEqqydZE = false;
      bool eEgNCAaymB = false;
      bool MVlXxkENUc = false;
      bool rxVduOeIZj = false;
      bool xaKpsMWSIf = false;
      bool OroUiXSoGG = false;
      bool ljIwLghCSn = false;
      bool VRYCElKwdj = false;
      bool NlFnOAIBuW = false;
      bool upBTxMSNeL = false;
      bool dUATKwTlQx = false;
      bool NVKVrzeThL = false;
      string AKAstOqKxp;
      string FbkyCDAmPf;
      string oeRZrTHXnR;
      string XYaaPaTxDb;
      string HPGsUpOqkZ;
      string jyiRaVraAZ;
      string HTWeRfBJhb;
      string jDjnYYYYEC;
      string FPmOgYpIAt;
      string hrwdTnsaao;
      string oEJIofOusB;
      string xTWyTrfIys;
      string prIntqHGTj;
      string fxxPNAGdYB;
      string JtOzxNVxJb;
      string HkchywwUOy;
      string XIaJVzWGkT;
      string lCiwiucJqf;
      string UJwrbtUOQQ;
      string EkPZcBTFcx;
      if(AKAstOqKxp == oEJIofOusB){qPMopFBfzD = true;}
      else if(oEJIofOusB == AKAstOqKxp){MVlXxkENUc = true;}
      if(FbkyCDAmPf == xTWyTrfIys){SldidOLhga = true;}
      else if(xTWyTrfIys == FbkyCDAmPf){rxVduOeIZj = true;}
      if(oeRZrTHXnR == prIntqHGTj){dHoTOAlJSg = true;}
      else if(prIntqHGTj == oeRZrTHXnR){xaKpsMWSIf = true;}
      if(XYaaPaTxDb == fxxPNAGdYB){bWfsnFxHCV = true;}
      else if(fxxPNAGdYB == XYaaPaTxDb){OroUiXSoGG = true;}
      if(HPGsUpOqkZ == JtOzxNVxJb){snPNxSGgwO = true;}
      else if(JtOzxNVxJb == HPGsUpOqkZ){ljIwLghCSn = true;}
      if(jyiRaVraAZ == HkchywwUOy){okYCSjZrZo = true;}
      else if(HkchywwUOy == jyiRaVraAZ){VRYCElKwdj = true;}
      if(HTWeRfBJhb == XIaJVzWGkT){TrNRawFktY = true;}
      else if(XIaJVzWGkT == HTWeRfBJhb){NlFnOAIBuW = true;}
      if(jDjnYYYYEC == lCiwiucJqf){REfKgpqbVw = true;}
      if(FPmOgYpIAt == UJwrbtUOQQ){tFMEqqydZE = true;}
      if(hrwdTnsaao == EkPZcBTFcx){eEgNCAaymB = true;}
      while(lCiwiucJqf == jDjnYYYYEC){upBTxMSNeL = true;}
      while(UJwrbtUOQQ == UJwrbtUOQQ){dUATKwTlQx = true;}
      while(EkPZcBTFcx == EkPZcBTFcx){NVKVrzeThL = true;}
      if(qPMopFBfzD == true){qPMopFBfzD = false;}
      if(SldidOLhga == true){SldidOLhga = false;}
      if(dHoTOAlJSg == true){dHoTOAlJSg = false;}
      if(bWfsnFxHCV == true){bWfsnFxHCV = false;}
      if(snPNxSGgwO == true){snPNxSGgwO = false;}
      if(okYCSjZrZo == true){okYCSjZrZo = false;}
      if(TrNRawFktY == true){TrNRawFktY = false;}
      if(REfKgpqbVw == true){REfKgpqbVw = false;}
      if(tFMEqqydZE == true){tFMEqqydZE = false;}
      if(eEgNCAaymB == true){eEgNCAaymB = false;}
      if(MVlXxkENUc == true){MVlXxkENUc = false;}
      if(rxVduOeIZj == true){rxVduOeIZj = false;}
      if(xaKpsMWSIf == true){xaKpsMWSIf = false;}
      if(OroUiXSoGG == true){OroUiXSoGG = false;}
      if(ljIwLghCSn == true){ljIwLghCSn = false;}
      if(VRYCElKwdj == true){VRYCElKwdj = false;}
      if(NlFnOAIBuW == true){NlFnOAIBuW = false;}
      if(upBTxMSNeL == true){upBTxMSNeL = false;}
      if(dUATKwTlQx == true){dUATKwTlQx = false;}
      if(NVKVrzeThL == true){NVKVrzeThL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELVFHDTKVD
{ 
  void RRsyQgkDBo()
  { 
      bool txhcFFJIKS = false;
      bool YhqnqqEHxH = false;
      bool kAiRYNuTac = false;
      bool RtSPHycFQx = false;
      bool mSNAwIYFCT = false;
      bool TlIsLsNQEq = false;
      bool KoghBdOagr = false;
      bool OzpzURlhUP = false;
      bool npQGIekZEN = false;
      bool jLAZmxkfzR = false;
      bool tyXJFUwJXs = false;
      bool GfwoCUYZYV = false;
      bool soVSHCzQLX = false;
      bool gGiCVpRHBn = false;
      bool iaBLGEPLWS = false;
      bool YKGcYFbFBC = false;
      bool UexALAwsTM = false;
      bool DQYkmRmKMD = false;
      bool lmtszVAFdP = false;
      bool NLFySEdAAG = false;
      string wndYVJMAGJ;
      string beeqjFsILz;
      string IBWSRsUurM;
      string UiSeipKJeW;
      string iYmOGqZeCc;
      string RsZOEuQLHc;
      string nQItorLzHs;
      string tidoPiOILZ;
      string TpsOuaIEan;
      string ZzCChSQsYN;
      string faWJhhOkyV;
      string gHzgIyXtyN;
      string jGYTTufbGx;
      string SUjxtsTigM;
      string LXGEHRzUsj;
      string tWtLdYBDpm;
      string CmdADLXCmP;
      string dnNlBLATLB;
      string uKhWDwaXSU;
      string qQssKYtGAw;
      if(wndYVJMAGJ == faWJhhOkyV){txhcFFJIKS = true;}
      else if(faWJhhOkyV == wndYVJMAGJ){tyXJFUwJXs = true;}
      if(beeqjFsILz == gHzgIyXtyN){YhqnqqEHxH = true;}
      else if(gHzgIyXtyN == beeqjFsILz){GfwoCUYZYV = true;}
      if(IBWSRsUurM == jGYTTufbGx){kAiRYNuTac = true;}
      else if(jGYTTufbGx == IBWSRsUurM){soVSHCzQLX = true;}
      if(UiSeipKJeW == SUjxtsTigM){RtSPHycFQx = true;}
      else if(SUjxtsTigM == UiSeipKJeW){gGiCVpRHBn = true;}
      if(iYmOGqZeCc == LXGEHRzUsj){mSNAwIYFCT = true;}
      else if(LXGEHRzUsj == iYmOGqZeCc){iaBLGEPLWS = true;}
      if(RsZOEuQLHc == tWtLdYBDpm){TlIsLsNQEq = true;}
      else if(tWtLdYBDpm == RsZOEuQLHc){YKGcYFbFBC = true;}
      if(nQItorLzHs == CmdADLXCmP){KoghBdOagr = true;}
      else if(CmdADLXCmP == nQItorLzHs){UexALAwsTM = true;}
      if(tidoPiOILZ == dnNlBLATLB){OzpzURlhUP = true;}
      if(TpsOuaIEan == uKhWDwaXSU){npQGIekZEN = true;}
      if(ZzCChSQsYN == qQssKYtGAw){jLAZmxkfzR = true;}
      while(dnNlBLATLB == tidoPiOILZ){DQYkmRmKMD = true;}
      while(uKhWDwaXSU == uKhWDwaXSU){lmtszVAFdP = true;}
      while(qQssKYtGAw == qQssKYtGAw){NLFySEdAAG = true;}
      if(txhcFFJIKS == true){txhcFFJIKS = false;}
      if(YhqnqqEHxH == true){YhqnqqEHxH = false;}
      if(kAiRYNuTac == true){kAiRYNuTac = false;}
      if(RtSPHycFQx == true){RtSPHycFQx = false;}
      if(mSNAwIYFCT == true){mSNAwIYFCT = false;}
      if(TlIsLsNQEq == true){TlIsLsNQEq = false;}
      if(KoghBdOagr == true){KoghBdOagr = false;}
      if(OzpzURlhUP == true){OzpzURlhUP = false;}
      if(npQGIekZEN == true){npQGIekZEN = false;}
      if(jLAZmxkfzR == true){jLAZmxkfzR = false;}
      if(tyXJFUwJXs == true){tyXJFUwJXs = false;}
      if(GfwoCUYZYV == true){GfwoCUYZYV = false;}
      if(soVSHCzQLX == true){soVSHCzQLX = false;}
      if(gGiCVpRHBn == true){gGiCVpRHBn = false;}
      if(iaBLGEPLWS == true){iaBLGEPLWS = false;}
      if(YKGcYFbFBC == true){YKGcYFbFBC = false;}
      if(UexALAwsTM == true){UexALAwsTM = false;}
      if(DQYkmRmKMD == true){DQYkmRmKMD = false;}
      if(lmtszVAFdP == true){lmtszVAFdP = false;}
      if(NLFySEdAAG == true){NLFySEdAAG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QSNUJKVCOV
{ 
  void lKrsAhNjhs()
  { 
      bool MiiwwCqrdG = false;
      bool qYDWQVWiVS = false;
      bool NnmWxdLdFm = false;
      bool ogKrfcUFWu = false;
      bool rctKskUTcJ = false;
      bool yqycWXuMyR = false;
      bool pMmqQKOLpm = false;
      bool ARMaZjtccM = false;
      bool JqBunyigUH = false;
      bool hIHFEfoCsi = false;
      bool WJdoJgeWCl = false;
      bool cRikIzLrCR = false;
      bool agphFqKHVt = false;
      bool uqitpzNLlH = false;
      bool TLdidPZVxF = false;
      bool TxAbHoSwiR = false;
      bool WWBIqlhnuI = false;
      bool lzFuyPDHDo = false;
      bool RnJQZxqHmA = false;
      bool fRbUjwKVqr = false;
      string DCAgylgtZu;
      string fsMxoAhnQX;
      string ECaHoWAkDK;
      string PptGBYWPer;
      string IziXFfsVxE;
      string knskFAbsrb;
      string lwqPepyGuP;
      string cRJYOFSDCI;
      string cdnyYaxJAA;
      string xdXCGMHTrO;
      string glZhbTeTVA;
      string hXqiyHIspE;
      string soGuRzsGRC;
      string xzLmbpEFVF;
      string ucnzSYmoEz;
      string ENcmVrfePc;
      string ZYCTCiMEGI;
      string DCWkJPAGbs;
      string LEBSxiVXQj;
      string KYpseVZTwj;
      if(DCAgylgtZu == glZhbTeTVA){MiiwwCqrdG = true;}
      else if(glZhbTeTVA == DCAgylgtZu){WJdoJgeWCl = true;}
      if(fsMxoAhnQX == hXqiyHIspE){qYDWQVWiVS = true;}
      else if(hXqiyHIspE == fsMxoAhnQX){cRikIzLrCR = true;}
      if(ECaHoWAkDK == soGuRzsGRC){NnmWxdLdFm = true;}
      else if(soGuRzsGRC == ECaHoWAkDK){agphFqKHVt = true;}
      if(PptGBYWPer == xzLmbpEFVF){ogKrfcUFWu = true;}
      else if(xzLmbpEFVF == PptGBYWPer){uqitpzNLlH = true;}
      if(IziXFfsVxE == ucnzSYmoEz){rctKskUTcJ = true;}
      else if(ucnzSYmoEz == IziXFfsVxE){TLdidPZVxF = true;}
      if(knskFAbsrb == ENcmVrfePc){yqycWXuMyR = true;}
      else if(ENcmVrfePc == knskFAbsrb){TxAbHoSwiR = true;}
      if(lwqPepyGuP == ZYCTCiMEGI){pMmqQKOLpm = true;}
      else if(ZYCTCiMEGI == lwqPepyGuP){WWBIqlhnuI = true;}
      if(cRJYOFSDCI == DCWkJPAGbs){ARMaZjtccM = true;}
      if(cdnyYaxJAA == LEBSxiVXQj){JqBunyigUH = true;}
      if(xdXCGMHTrO == KYpseVZTwj){hIHFEfoCsi = true;}
      while(DCWkJPAGbs == cRJYOFSDCI){lzFuyPDHDo = true;}
      while(LEBSxiVXQj == LEBSxiVXQj){RnJQZxqHmA = true;}
      while(KYpseVZTwj == KYpseVZTwj){fRbUjwKVqr = true;}
      if(MiiwwCqrdG == true){MiiwwCqrdG = false;}
      if(qYDWQVWiVS == true){qYDWQVWiVS = false;}
      if(NnmWxdLdFm == true){NnmWxdLdFm = false;}
      if(ogKrfcUFWu == true){ogKrfcUFWu = false;}
      if(rctKskUTcJ == true){rctKskUTcJ = false;}
      if(yqycWXuMyR == true){yqycWXuMyR = false;}
      if(pMmqQKOLpm == true){pMmqQKOLpm = false;}
      if(ARMaZjtccM == true){ARMaZjtccM = false;}
      if(JqBunyigUH == true){JqBunyigUH = false;}
      if(hIHFEfoCsi == true){hIHFEfoCsi = false;}
      if(WJdoJgeWCl == true){WJdoJgeWCl = false;}
      if(cRikIzLrCR == true){cRikIzLrCR = false;}
      if(agphFqKHVt == true){agphFqKHVt = false;}
      if(uqitpzNLlH == true){uqitpzNLlH = false;}
      if(TLdidPZVxF == true){TLdidPZVxF = false;}
      if(TxAbHoSwiR == true){TxAbHoSwiR = false;}
      if(WWBIqlhnuI == true){WWBIqlhnuI = false;}
      if(lzFuyPDHDo == true){lzFuyPDHDo = false;}
      if(RnJQZxqHmA == true){RnJQZxqHmA = false;}
      if(fRbUjwKVqr == true){fRbUjwKVqr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZNWRAONTN
{ 
  void HfOwgzBSLL()
  { 
      bool ZlgBpIRONQ = false;
      bool lfoQqDupXh = false;
      bool NXYEwpbPuz = false;
      bool JsFZAuXXfY = false;
      bool UEPalzfKAx = false;
      bool RbDjxBMbFA = false;
      bool gCSNGraOQw = false;
      bool fWJyMIIxRw = false;
      bool JQOyghpUcy = false;
      bool huSfrRkBUt = false;
      bool XQtEQuREWn = false;
      bool sOKIpPmUfY = false;
      bool CGlRNjDcGu = false;
      bool WGcXYsWJgl = false;
      bool PlxnETkKpb = false;
      bool dQVuqQebpg = false;
      bool rnxbRmkliw = false;
      bool rdntIPJyNt = false;
      bool zrmdQGjhfH = false;
      bool OuSAtbnUVR = false;
      string PTfOunFTda;
      string schuibssnf;
      string DGsxVkjcWn;
      string YazGNEmLzK;
      string ItIVQjnkUx;
      string FSMVoJahsJ;
      string EcxoBSdagd;
      string ogscXJxWgk;
      string xyHYhGNdRE;
      string dESpGfxSUx;
      string GNDpIXYixf;
      string LDBHLFUXHt;
      string FAJcAjODWr;
      string LeCjejuRQK;
      string hdflrZDKdA;
      string KYLZrGDZpX;
      string IUMFTgARcb;
      string KCHwMaTWkZ;
      string gEZWglTcrY;
      string fUarBMRaRK;
      if(PTfOunFTda == GNDpIXYixf){ZlgBpIRONQ = true;}
      else if(GNDpIXYixf == PTfOunFTda){XQtEQuREWn = true;}
      if(schuibssnf == LDBHLFUXHt){lfoQqDupXh = true;}
      else if(LDBHLFUXHt == schuibssnf){sOKIpPmUfY = true;}
      if(DGsxVkjcWn == FAJcAjODWr){NXYEwpbPuz = true;}
      else if(FAJcAjODWr == DGsxVkjcWn){CGlRNjDcGu = true;}
      if(YazGNEmLzK == LeCjejuRQK){JsFZAuXXfY = true;}
      else if(LeCjejuRQK == YazGNEmLzK){WGcXYsWJgl = true;}
      if(ItIVQjnkUx == hdflrZDKdA){UEPalzfKAx = true;}
      else if(hdflrZDKdA == ItIVQjnkUx){PlxnETkKpb = true;}
      if(FSMVoJahsJ == KYLZrGDZpX){RbDjxBMbFA = true;}
      else if(KYLZrGDZpX == FSMVoJahsJ){dQVuqQebpg = true;}
      if(EcxoBSdagd == IUMFTgARcb){gCSNGraOQw = true;}
      else if(IUMFTgARcb == EcxoBSdagd){rnxbRmkliw = true;}
      if(ogscXJxWgk == KCHwMaTWkZ){fWJyMIIxRw = true;}
      if(xyHYhGNdRE == gEZWglTcrY){JQOyghpUcy = true;}
      if(dESpGfxSUx == fUarBMRaRK){huSfrRkBUt = true;}
      while(KCHwMaTWkZ == ogscXJxWgk){rdntIPJyNt = true;}
      while(gEZWglTcrY == gEZWglTcrY){zrmdQGjhfH = true;}
      while(fUarBMRaRK == fUarBMRaRK){OuSAtbnUVR = true;}
      if(ZlgBpIRONQ == true){ZlgBpIRONQ = false;}
      if(lfoQqDupXh == true){lfoQqDupXh = false;}
      if(NXYEwpbPuz == true){NXYEwpbPuz = false;}
      if(JsFZAuXXfY == true){JsFZAuXXfY = false;}
      if(UEPalzfKAx == true){UEPalzfKAx = false;}
      if(RbDjxBMbFA == true){RbDjxBMbFA = false;}
      if(gCSNGraOQw == true){gCSNGraOQw = false;}
      if(fWJyMIIxRw == true){fWJyMIIxRw = false;}
      if(JQOyghpUcy == true){JQOyghpUcy = false;}
      if(huSfrRkBUt == true){huSfrRkBUt = false;}
      if(XQtEQuREWn == true){XQtEQuREWn = false;}
      if(sOKIpPmUfY == true){sOKIpPmUfY = false;}
      if(CGlRNjDcGu == true){CGlRNjDcGu = false;}
      if(WGcXYsWJgl == true){WGcXYsWJgl = false;}
      if(PlxnETkKpb == true){PlxnETkKpb = false;}
      if(dQVuqQebpg == true){dQVuqQebpg = false;}
      if(rnxbRmkliw == true){rnxbRmkliw = false;}
      if(rdntIPJyNt == true){rdntIPJyNt = false;}
      if(zrmdQGjhfH == true){zrmdQGjhfH = false;}
      if(OuSAtbnUVR == true){OuSAtbnUVR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOVCRMPQQT
{ 
  void DQBQufJeDE()
  { 
      bool OzYUuKStjc = false;
      bool BJyLTzorGu = false;
      bool XtgHltnNrH = false;
      bool BpqNshZeTx = false;
      bool CGNsVDuVKS = false;
      bool TbhqTTSQiB = false;
      bool VECcbLRkSk = false;
      bool YJXIsQgmlh = false;
      bool zRDZmYIzsY = false;
      bool PJwSaxEjRJ = false;
      bool lJDYtKDYyC = false;
      bool medABDBcpC = false;
      bool DRqtVOMFhu = false;
      bool MwVbwoOdfb = false;
      bool ViBpljeuQW = false;
      bool watOGTRJCe = false;
      bool xypCppJCEL = false;
      bool nWxNgTQBHl = false;
      bool iRnLzkBHVb = false;
      bool WFaAeWszAu = false;
      string cHoKmmrGzh;
      string qlmoSnYdDG;
      string jJCwMSZiSH;
      string JKAHREXjoh;
      string MVXncxyzyB;
      string pAbuJSFsxT;
      string MInrXfkeWO;
      string PooUsNlNSP;
      string TakQRJiEyz;
      string zelUVEhePw;
      string MTcilBKGCu;
      string gqahzlXWZO;
      string xffXPkCUzn;
      string fGyVDAyBeP;
      string ybCCRHDDUi;
      string gKFAzfmETA;
      string yoHNPZrEez;
      string nVrKQVddFH;
      string gzAPHUBxWW;
      string NshdRJTnlr;
      if(cHoKmmrGzh == MTcilBKGCu){OzYUuKStjc = true;}
      else if(MTcilBKGCu == cHoKmmrGzh){lJDYtKDYyC = true;}
      if(qlmoSnYdDG == gqahzlXWZO){BJyLTzorGu = true;}
      else if(gqahzlXWZO == qlmoSnYdDG){medABDBcpC = true;}
      if(jJCwMSZiSH == xffXPkCUzn){XtgHltnNrH = true;}
      else if(xffXPkCUzn == jJCwMSZiSH){DRqtVOMFhu = true;}
      if(JKAHREXjoh == fGyVDAyBeP){BpqNshZeTx = true;}
      else if(fGyVDAyBeP == JKAHREXjoh){MwVbwoOdfb = true;}
      if(MVXncxyzyB == ybCCRHDDUi){CGNsVDuVKS = true;}
      else if(ybCCRHDDUi == MVXncxyzyB){ViBpljeuQW = true;}
      if(pAbuJSFsxT == gKFAzfmETA){TbhqTTSQiB = true;}
      else if(gKFAzfmETA == pAbuJSFsxT){watOGTRJCe = true;}
      if(MInrXfkeWO == yoHNPZrEez){VECcbLRkSk = true;}
      else if(yoHNPZrEez == MInrXfkeWO){xypCppJCEL = true;}
      if(PooUsNlNSP == nVrKQVddFH){YJXIsQgmlh = true;}
      if(TakQRJiEyz == gzAPHUBxWW){zRDZmYIzsY = true;}
      if(zelUVEhePw == NshdRJTnlr){PJwSaxEjRJ = true;}
      while(nVrKQVddFH == PooUsNlNSP){nWxNgTQBHl = true;}
      while(gzAPHUBxWW == gzAPHUBxWW){iRnLzkBHVb = true;}
      while(NshdRJTnlr == NshdRJTnlr){WFaAeWszAu = true;}
      if(OzYUuKStjc == true){OzYUuKStjc = false;}
      if(BJyLTzorGu == true){BJyLTzorGu = false;}
      if(XtgHltnNrH == true){XtgHltnNrH = false;}
      if(BpqNshZeTx == true){BpqNshZeTx = false;}
      if(CGNsVDuVKS == true){CGNsVDuVKS = false;}
      if(TbhqTTSQiB == true){TbhqTTSQiB = false;}
      if(VECcbLRkSk == true){VECcbLRkSk = false;}
      if(YJXIsQgmlh == true){YJXIsQgmlh = false;}
      if(zRDZmYIzsY == true){zRDZmYIzsY = false;}
      if(PJwSaxEjRJ == true){PJwSaxEjRJ = false;}
      if(lJDYtKDYyC == true){lJDYtKDYyC = false;}
      if(medABDBcpC == true){medABDBcpC = false;}
      if(DRqtVOMFhu == true){DRqtVOMFhu = false;}
      if(MwVbwoOdfb == true){MwVbwoOdfb = false;}
      if(ViBpljeuQW == true){ViBpljeuQW = false;}
      if(watOGTRJCe == true){watOGTRJCe = false;}
      if(xypCppJCEL == true){xypCppJCEL = false;}
      if(nWxNgTQBHl == true){nWxNgTQBHl = false;}
      if(iRnLzkBHVb == true){iRnLzkBHVb = false;}
      if(WFaAeWszAu == true){WFaAeWszAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDTVZJZXVA
{ 
  void IUYFlebyxa()
  { 
      bool lLlhsgWjcy = false;
      bool iYrUMobSoX = false;
      bool mTxOSLPhEs = false;
      bool CZZYUypXBg = false;
      bool DeBmrkRTtZ = false;
      bool xJzUEROWPg = false;
      bool RoeiuIyTAN = false;
      bool yDRIUIRJWg = false;
      bool tumdwsZFTC = false;
      bool jTITPNzSri = false;
      bool lyTfbtqqzw = false;
      bool AEAhmVBBlB = false;
      bool hrAycdtysG = false;
      bool JzRmtubHCC = false;
      bool CiGWCfTags = false;
      bool MxfpAtyUCx = false;
      bool zsyrlBmNmq = false;
      bool ttyjzzkcwx = false;
      bool KTQztLSalA = false;
      bool xGEECIjNkB = false;
      string XXJyVOGKau;
      string haIfcGnbBa;
      string RfCwAniAkW;
      string MzQXGdGqVk;
      string PCIFhRktQd;
      string TFlQyqVMyg;
      string eGZEhhJjZy;
      string AxFPKOWxOh;
      string DniHDHMAZO;
      string IsrnGJcEWz;
      string IBURcVzWFi;
      string UXyQdpWRAa;
      string VJJKpGEQJB;
      string kSZPZBTQdg;
      string HptptjubKP;
      string mKDudyqJbW;
      string RhNEyByipb;
      string WFnTSfPSQG;
      string KcGtOZOdka;
      string JKoGPYcorr;
      if(XXJyVOGKau == IBURcVzWFi){lLlhsgWjcy = true;}
      else if(IBURcVzWFi == XXJyVOGKau){lyTfbtqqzw = true;}
      if(haIfcGnbBa == UXyQdpWRAa){iYrUMobSoX = true;}
      else if(UXyQdpWRAa == haIfcGnbBa){AEAhmVBBlB = true;}
      if(RfCwAniAkW == VJJKpGEQJB){mTxOSLPhEs = true;}
      else if(VJJKpGEQJB == RfCwAniAkW){hrAycdtysG = true;}
      if(MzQXGdGqVk == kSZPZBTQdg){CZZYUypXBg = true;}
      else if(kSZPZBTQdg == MzQXGdGqVk){JzRmtubHCC = true;}
      if(PCIFhRktQd == HptptjubKP){DeBmrkRTtZ = true;}
      else if(HptptjubKP == PCIFhRktQd){CiGWCfTags = true;}
      if(TFlQyqVMyg == mKDudyqJbW){xJzUEROWPg = true;}
      else if(mKDudyqJbW == TFlQyqVMyg){MxfpAtyUCx = true;}
      if(eGZEhhJjZy == RhNEyByipb){RoeiuIyTAN = true;}
      else if(RhNEyByipb == eGZEhhJjZy){zsyrlBmNmq = true;}
      if(AxFPKOWxOh == WFnTSfPSQG){yDRIUIRJWg = true;}
      if(DniHDHMAZO == KcGtOZOdka){tumdwsZFTC = true;}
      if(IsrnGJcEWz == JKoGPYcorr){jTITPNzSri = true;}
      while(WFnTSfPSQG == AxFPKOWxOh){ttyjzzkcwx = true;}
      while(KcGtOZOdka == KcGtOZOdka){KTQztLSalA = true;}
      while(JKoGPYcorr == JKoGPYcorr){xGEECIjNkB = true;}
      if(lLlhsgWjcy == true){lLlhsgWjcy = false;}
      if(iYrUMobSoX == true){iYrUMobSoX = false;}
      if(mTxOSLPhEs == true){mTxOSLPhEs = false;}
      if(CZZYUypXBg == true){CZZYUypXBg = false;}
      if(DeBmrkRTtZ == true){DeBmrkRTtZ = false;}
      if(xJzUEROWPg == true){xJzUEROWPg = false;}
      if(RoeiuIyTAN == true){RoeiuIyTAN = false;}
      if(yDRIUIRJWg == true){yDRIUIRJWg = false;}
      if(tumdwsZFTC == true){tumdwsZFTC = false;}
      if(jTITPNzSri == true){jTITPNzSri = false;}
      if(lyTfbtqqzw == true){lyTfbtqqzw = false;}
      if(AEAhmVBBlB == true){AEAhmVBBlB = false;}
      if(hrAycdtysG == true){hrAycdtysG = false;}
      if(JzRmtubHCC == true){JzRmtubHCC = false;}
      if(CiGWCfTags == true){CiGWCfTags = false;}
      if(MxfpAtyUCx == true){MxfpAtyUCx = false;}
      if(zsyrlBmNmq == true){zsyrlBmNmq = false;}
      if(ttyjzzkcwx == true){ttyjzzkcwx = false;}
      if(KTQztLSalA == true){KTQztLSalA = false;}
      if(xGEECIjNkB == true){xGEECIjNkB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQHJTKAHKA
{ 
  void xYIXEcHAWt()
  { 
      bool rxqdWxCJRW = false;
      bool UQNtruterk = false;
      bool tMSJMtQtBd = false;
      bool muPdUCPrcb = false;
      bool pIKhiQyqSF = false;
      bool dsPoKfdhRc = false;
      bool fHHnjZAjZp = false;
      bool eCCPtkBkZw = false;
      bool uYbwzteaSo = false;
      bool XhaAuhBWxJ = false;
      bool PORbZbqztZ = false;
      bool dsIVgHfLop = false;
      bool tZRjRxbBTM = false;
      bool jemPfgGzVW = false;
      bool CegsLeZFSn = false;
      bool BogHPpxhKc = false;
      bool ApfhozFroA = false;
      bool AgoRmOrXYl = false;
      bool XWhfKtxezo = false;
      bool jYnsWMzzDL = false;
      string ZacptDaNAQ;
      string ggJStoPiwY;
      string LiYZYUbakf;
      string SzkfDYlLfW;
      string ytlLiweQZR;
      string QPiSwpBDRY;
      string bzbTxgudPU;
      string DECYZRxMpb;
      string pKASODPSiM;
      string XhsHtzRROB;
      string ABAFOMMKre;
      string snMoiQyJFs;
      string RctDxVKuda;
      string AeyobnKuEC;
      string pFZETiUEYd;
      string AHMUjXGxIs;
      string BRfRdNpXNt;
      string GDFCCMCpiN;
      string AGWAZrScEE;
      string gMlLAYYHZF;
      if(ZacptDaNAQ == ABAFOMMKre){rxqdWxCJRW = true;}
      else if(ABAFOMMKre == ZacptDaNAQ){PORbZbqztZ = true;}
      if(ggJStoPiwY == snMoiQyJFs){UQNtruterk = true;}
      else if(snMoiQyJFs == ggJStoPiwY){dsIVgHfLop = true;}
      if(LiYZYUbakf == RctDxVKuda){tMSJMtQtBd = true;}
      else if(RctDxVKuda == LiYZYUbakf){tZRjRxbBTM = true;}
      if(SzkfDYlLfW == AeyobnKuEC){muPdUCPrcb = true;}
      else if(AeyobnKuEC == SzkfDYlLfW){jemPfgGzVW = true;}
      if(ytlLiweQZR == pFZETiUEYd){pIKhiQyqSF = true;}
      else if(pFZETiUEYd == ytlLiweQZR){CegsLeZFSn = true;}
      if(QPiSwpBDRY == AHMUjXGxIs){dsPoKfdhRc = true;}
      else if(AHMUjXGxIs == QPiSwpBDRY){BogHPpxhKc = true;}
      if(bzbTxgudPU == BRfRdNpXNt){fHHnjZAjZp = true;}
      else if(BRfRdNpXNt == bzbTxgudPU){ApfhozFroA = true;}
      if(DECYZRxMpb == GDFCCMCpiN){eCCPtkBkZw = true;}
      if(pKASODPSiM == AGWAZrScEE){uYbwzteaSo = true;}
      if(XhsHtzRROB == gMlLAYYHZF){XhaAuhBWxJ = true;}
      while(GDFCCMCpiN == DECYZRxMpb){AgoRmOrXYl = true;}
      while(AGWAZrScEE == AGWAZrScEE){XWhfKtxezo = true;}
      while(gMlLAYYHZF == gMlLAYYHZF){jYnsWMzzDL = true;}
      if(rxqdWxCJRW == true){rxqdWxCJRW = false;}
      if(UQNtruterk == true){UQNtruterk = false;}
      if(tMSJMtQtBd == true){tMSJMtQtBd = false;}
      if(muPdUCPrcb == true){muPdUCPrcb = false;}
      if(pIKhiQyqSF == true){pIKhiQyqSF = false;}
      if(dsPoKfdhRc == true){dsPoKfdhRc = false;}
      if(fHHnjZAjZp == true){fHHnjZAjZp = false;}
      if(eCCPtkBkZw == true){eCCPtkBkZw = false;}
      if(uYbwzteaSo == true){uYbwzteaSo = false;}
      if(XhaAuhBWxJ == true){XhaAuhBWxJ = false;}
      if(PORbZbqztZ == true){PORbZbqztZ = false;}
      if(dsIVgHfLop == true){dsIVgHfLop = false;}
      if(tZRjRxbBTM == true){tZRjRxbBTM = false;}
      if(jemPfgGzVW == true){jemPfgGzVW = false;}
      if(CegsLeZFSn == true){CegsLeZFSn = false;}
      if(BogHPpxhKc == true){BogHPpxhKc = false;}
      if(ApfhozFroA == true){ApfhozFroA = false;}
      if(AgoRmOrXYl == true){AgoRmOrXYl = false;}
      if(XWhfKtxezo == true){XWhfKtxezo = false;}
      if(jYnsWMzzDL == true){jYnsWMzzDL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDKFZQCVZP
{ 
  void rOCNMLDeXH()
  { 
      bool LVIBepzAor = false;
      bool hBJPVhMNoU = false;
      bool BmJrekhyVC = false;
      bool JMHCeiCNzy = false;
      bool hzSglPeptA = false;
      bool sStlNXLPWs = false;
      bool HBeliUsHkm = false;
      bool ezOplCUbFP = false;
      bool FrDVJpSUnG = false;
      bool WmpFqgUfyR = false;
      bool VXFHUtEDAL = false;
      bool CiJHnPyIcr = false;
      bool BYSdQrIIzF = false;
      bool hodnshmwBP = false;
      bool kPUcEmciQa = false;
      bool hLDFPwEbqb = false;
      bool kuDtcNFVNG = false;
      bool cCGNHlEoYc = false;
      bool PZqYWVkYXx = false;
      bool cKEZdpLZzp = false;
      string QsCAhwiBfE;
      string MaKbHszBln;
      string ZQxIzniVRu;
      string qBFcXDoiRI;
      string rGXBFKULGo;
      string qWDtTAwsAt;
      string NNjkMKVhEE;
      string EPidwTsuCn;
      string SWObDUxLJW;
      string HuiXudWmou;
      string omHCjamZxz;
      string HApMapzHgq;
      string MKXgwJgLiS;
      string xFFHzfPLrb;
      string hXNJPGEVwE;
      string dOFyhdOaFa;
      string sbqdCBuiNu;
      string ZnPEJowNQp;
      string ELOdohAHZU;
      string QoFQhGfiGO;
      if(QsCAhwiBfE == omHCjamZxz){LVIBepzAor = true;}
      else if(omHCjamZxz == QsCAhwiBfE){VXFHUtEDAL = true;}
      if(MaKbHszBln == HApMapzHgq){hBJPVhMNoU = true;}
      else if(HApMapzHgq == MaKbHszBln){CiJHnPyIcr = true;}
      if(ZQxIzniVRu == MKXgwJgLiS){BmJrekhyVC = true;}
      else if(MKXgwJgLiS == ZQxIzniVRu){BYSdQrIIzF = true;}
      if(qBFcXDoiRI == xFFHzfPLrb){JMHCeiCNzy = true;}
      else if(xFFHzfPLrb == qBFcXDoiRI){hodnshmwBP = true;}
      if(rGXBFKULGo == hXNJPGEVwE){hzSglPeptA = true;}
      else if(hXNJPGEVwE == rGXBFKULGo){kPUcEmciQa = true;}
      if(qWDtTAwsAt == dOFyhdOaFa){sStlNXLPWs = true;}
      else if(dOFyhdOaFa == qWDtTAwsAt){hLDFPwEbqb = true;}
      if(NNjkMKVhEE == sbqdCBuiNu){HBeliUsHkm = true;}
      else if(sbqdCBuiNu == NNjkMKVhEE){kuDtcNFVNG = true;}
      if(EPidwTsuCn == ZnPEJowNQp){ezOplCUbFP = true;}
      if(SWObDUxLJW == ELOdohAHZU){FrDVJpSUnG = true;}
      if(HuiXudWmou == QoFQhGfiGO){WmpFqgUfyR = true;}
      while(ZnPEJowNQp == EPidwTsuCn){cCGNHlEoYc = true;}
      while(ELOdohAHZU == ELOdohAHZU){PZqYWVkYXx = true;}
      while(QoFQhGfiGO == QoFQhGfiGO){cKEZdpLZzp = true;}
      if(LVIBepzAor == true){LVIBepzAor = false;}
      if(hBJPVhMNoU == true){hBJPVhMNoU = false;}
      if(BmJrekhyVC == true){BmJrekhyVC = false;}
      if(JMHCeiCNzy == true){JMHCeiCNzy = false;}
      if(hzSglPeptA == true){hzSglPeptA = false;}
      if(sStlNXLPWs == true){sStlNXLPWs = false;}
      if(HBeliUsHkm == true){HBeliUsHkm = false;}
      if(ezOplCUbFP == true){ezOplCUbFP = false;}
      if(FrDVJpSUnG == true){FrDVJpSUnG = false;}
      if(WmpFqgUfyR == true){WmpFqgUfyR = false;}
      if(VXFHUtEDAL == true){VXFHUtEDAL = false;}
      if(CiJHnPyIcr == true){CiJHnPyIcr = false;}
      if(BYSdQrIIzF == true){BYSdQrIIzF = false;}
      if(hodnshmwBP == true){hodnshmwBP = false;}
      if(kPUcEmciQa == true){kPUcEmciQa = false;}
      if(hLDFPwEbqb == true){hLDFPwEbqb = false;}
      if(kuDtcNFVNG == true){kuDtcNFVNG = false;}
      if(cCGNHlEoYc == true){cCGNHlEoYc = false;}
      if(PZqYWVkYXx == true){PZqYWVkYXx = false;}
      if(cKEZdpLZzp == true){cKEZdpLZzp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVDJLPLQQY
{ 
  void plctNExDez()
  { 
      bool tXUJTjPdyD = false;
      bool XMXTezqBMb = false;
      bool YixJATNzeH = false;
      bool kMnblbuItT = false;
      bool LZDUBlUawa = false;
      bool BlZBGKZLJz = false;
      bool WQypSKYwgD = false;
      bool DhHrPyfbHN = false;
      bool zmCEGyllVa = false;
      bool BjztxubMCp = false;
      bool NYssWSegkH = false;
      bool exEwAjNsjT = false;
      bool YlZFBTiNuT = false;
      bool VSZQAasJhm = false;
      bool SEBNuDeDsN = false;
      bool hichRaymqC = false;
      bool jRlQlMXnuZ = false;
      bool pDLwATkMKx = false;
      bool nfThkmpqyY = false;
      bool bFReDBSjai = false;
      string ynjTWyKljm;
      string RxeojOmmaC;
      string nRzCSmwzUN;
      string scaZEGAjWR;
      string HrAwtwgeqn;
      string mDRITgogBi;
      string BLQVsnVEkd;
      string NCQJtuRCIW;
      string FRIgapLSGW;
      string RThmPwadCF;
      string ZbsMZjmHOY;
      string PlYecjDiuD;
      string cDyOMtUcsx;
      string TmACwcXuHp;
      string CDDgHftDJf;
      string sriycWdeAe;
      string PJOQEckWhz;
      string MIbFAZzQGg;
      string zQSNEbDBYY;
      string zrtbZrnmce;
      if(ynjTWyKljm == ZbsMZjmHOY){tXUJTjPdyD = true;}
      else if(ZbsMZjmHOY == ynjTWyKljm){NYssWSegkH = true;}
      if(RxeojOmmaC == PlYecjDiuD){XMXTezqBMb = true;}
      else if(PlYecjDiuD == RxeojOmmaC){exEwAjNsjT = true;}
      if(nRzCSmwzUN == cDyOMtUcsx){YixJATNzeH = true;}
      else if(cDyOMtUcsx == nRzCSmwzUN){YlZFBTiNuT = true;}
      if(scaZEGAjWR == TmACwcXuHp){kMnblbuItT = true;}
      else if(TmACwcXuHp == scaZEGAjWR){VSZQAasJhm = true;}
      if(HrAwtwgeqn == CDDgHftDJf){LZDUBlUawa = true;}
      else if(CDDgHftDJf == HrAwtwgeqn){SEBNuDeDsN = true;}
      if(mDRITgogBi == sriycWdeAe){BlZBGKZLJz = true;}
      else if(sriycWdeAe == mDRITgogBi){hichRaymqC = true;}
      if(BLQVsnVEkd == PJOQEckWhz){WQypSKYwgD = true;}
      else if(PJOQEckWhz == BLQVsnVEkd){jRlQlMXnuZ = true;}
      if(NCQJtuRCIW == MIbFAZzQGg){DhHrPyfbHN = true;}
      if(FRIgapLSGW == zQSNEbDBYY){zmCEGyllVa = true;}
      if(RThmPwadCF == zrtbZrnmce){BjztxubMCp = true;}
      while(MIbFAZzQGg == NCQJtuRCIW){pDLwATkMKx = true;}
      while(zQSNEbDBYY == zQSNEbDBYY){nfThkmpqyY = true;}
      while(zrtbZrnmce == zrtbZrnmce){bFReDBSjai = true;}
      if(tXUJTjPdyD == true){tXUJTjPdyD = false;}
      if(XMXTezqBMb == true){XMXTezqBMb = false;}
      if(YixJATNzeH == true){YixJATNzeH = false;}
      if(kMnblbuItT == true){kMnblbuItT = false;}
      if(LZDUBlUawa == true){LZDUBlUawa = false;}
      if(BlZBGKZLJz == true){BlZBGKZLJz = false;}
      if(WQypSKYwgD == true){WQypSKYwgD = false;}
      if(DhHrPyfbHN == true){DhHrPyfbHN = false;}
      if(zmCEGyllVa == true){zmCEGyllVa = false;}
      if(BjztxubMCp == true){BjztxubMCp = false;}
      if(NYssWSegkH == true){NYssWSegkH = false;}
      if(exEwAjNsjT == true){exEwAjNsjT = false;}
      if(YlZFBTiNuT == true){YlZFBTiNuT = false;}
      if(VSZQAasJhm == true){VSZQAasJhm = false;}
      if(SEBNuDeDsN == true){SEBNuDeDsN = false;}
      if(hichRaymqC == true){hichRaymqC = false;}
      if(jRlQlMXnuZ == true){jRlQlMXnuZ = false;}
      if(pDLwATkMKx == true){pDLwATkMKx = false;}
      if(nfThkmpqyY == true){nfThkmpqyY = false;}
      if(bFReDBSjai == true){bFReDBSjai = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIQKMTZKAZ
{ 
  void VpEZsTEtsU()
  { 
      bool eAQjjHJXDK = false;
      bool UiniRHwXom = false;
      bool qLDHRRRuMU = false;
      bool MzBfTKQlea = false;
      bool YMqkqjPAjp = false;
      bool YSxJsTxIRS = false;
      bool oNKhyVgHPG = false;
      bool qJsNOeTSPh = false;
      bool BRLWwtBrlz = false;
      bool NHTLlKBJmV = false;
      bool CIjcyOYitO = false;
      bool zesiRWCmkD = false;
      bool ToUPsjogbE = false;
      bool dKetfshhYh = false;
      bool URxXAiOjtO = false;
      bool HNXiBNmTjO = false;
      bool YrHpjnzyDY = false;
      bool oUODhCqwOK = false;
      bool UEmNwPmusR = false;
      bool FNyJIcKHnM = false;
      string PItEaxRhcc;
      string bjGtyETlTx;
      string DUEawrVPjm;
      string DFMLFieeoM;
      string cfVuTasagO;
      string tGQkhuDSIi;
      string aBxoYWXuoP;
      string YnxHUWzJHV;
      string yuiUrwnadJ;
      string eLWFkbhfVw;
      string CykRpGJJQK;
      string utKljeSbxc;
      string hwRejMRqVr;
      string nTnKSzJQel;
      string meKSNkAjUG;
      string JGisOGgFhc;
      string oRnXVbGATk;
      string VBxKpDkyRy;
      string LgVPihjtwM;
      string SEiBxUplxk;
      if(PItEaxRhcc == CykRpGJJQK){eAQjjHJXDK = true;}
      else if(CykRpGJJQK == PItEaxRhcc){CIjcyOYitO = true;}
      if(bjGtyETlTx == utKljeSbxc){UiniRHwXom = true;}
      else if(utKljeSbxc == bjGtyETlTx){zesiRWCmkD = true;}
      if(DUEawrVPjm == hwRejMRqVr){qLDHRRRuMU = true;}
      else if(hwRejMRqVr == DUEawrVPjm){ToUPsjogbE = true;}
      if(DFMLFieeoM == nTnKSzJQel){MzBfTKQlea = true;}
      else if(nTnKSzJQel == DFMLFieeoM){dKetfshhYh = true;}
      if(cfVuTasagO == meKSNkAjUG){YMqkqjPAjp = true;}
      else if(meKSNkAjUG == cfVuTasagO){URxXAiOjtO = true;}
      if(tGQkhuDSIi == JGisOGgFhc){YSxJsTxIRS = true;}
      else if(JGisOGgFhc == tGQkhuDSIi){HNXiBNmTjO = true;}
      if(aBxoYWXuoP == oRnXVbGATk){oNKhyVgHPG = true;}
      else if(oRnXVbGATk == aBxoYWXuoP){YrHpjnzyDY = true;}
      if(YnxHUWzJHV == VBxKpDkyRy){qJsNOeTSPh = true;}
      if(yuiUrwnadJ == LgVPihjtwM){BRLWwtBrlz = true;}
      if(eLWFkbhfVw == SEiBxUplxk){NHTLlKBJmV = true;}
      while(VBxKpDkyRy == YnxHUWzJHV){oUODhCqwOK = true;}
      while(LgVPihjtwM == LgVPihjtwM){UEmNwPmusR = true;}
      while(SEiBxUplxk == SEiBxUplxk){FNyJIcKHnM = true;}
      if(eAQjjHJXDK == true){eAQjjHJXDK = false;}
      if(UiniRHwXom == true){UiniRHwXom = false;}
      if(qLDHRRRuMU == true){qLDHRRRuMU = false;}
      if(MzBfTKQlea == true){MzBfTKQlea = false;}
      if(YMqkqjPAjp == true){YMqkqjPAjp = false;}
      if(YSxJsTxIRS == true){YSxJsTxIRS = false;}
      if(oNKhyVgHPG == true){oNKhyVgHPG = false;}
      if(qJsNOeTSPh == true){qJsNOeTSPh = false;}
      if(BRLWwtBrlz == true){BRLWwtBrlz = false;}
      if(NHTLlKBJmV == true){NHTLlKBJmV = false;}
      if(CIjcyOYitO == true){CIjcyOYitO = false;}
      if(zesiRWCmkD == true){zesiRWCmkD = false;}
      if(ToUPsjogbE == true){ToUPsjogbE = false;}
      if(dKetfshhYh == true){dKetfshhYh = false;}
      if(URxXAiOjtO == true){URxXAiOjtO = false;}
      if(HNXiBNmTjO == true){HNXiBNmTjO = false;}
      if(YrHpjnzyDY == true){YrHpjnzyDY = false;}
      if(oUODhCqwOK == true){oUODhCqwOK = false;}
      if(UEmNwPmusR == true){UEmNwPmusR = false;}
      if(FNyJIcKHnM == true){FNyJIcKHnM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QILFVPKGPK
{ 
  void OGszhbuzVa()
  { 
      bool XxwlwFNbUD = false;
      bool FyHhDrsfym = false;
      bool KSOwwRrbnl = false;
      bool SkVHeTNyGJ = false;
      bool ynBcBGbOsk = false;
      bool kfRDdFiAoe = false;
      bool NknhjUbzCj = false;
      bool dtZooWRkup = false;
      bool pchCAmSSdZ = false;
      bool kNIbuNzSrg = false;
      bool dbLJHqFbNH = false;
      bool nxFzojClhx = false;
      bool BJVbyQlyta = false;
      bool WyrOMNRYuJ = false;
      bool gpEWlmIJlK = false;
      bool KMkueTGiKp = false;
      bool FHhmjoFqma = false;
      bool SdqXPKFzoL = false;
      bool IcLiQJNxir = false;
      bool HhNEEZHRlx = false;
      string QeedhiIrHe;
      string TeUCpFxcey;
      string JdQsQmlDxV;
      string rKzZnUpazm;
      string WbcxTRJfUw;
      string fgcyhlNkNu;
      string xFtllIfuOU;
      string PVdqahASZy;
      string dGhAoLhBqB;
      string GENEoRgpLK;
      string kORAgJCkWA;
      string kuLOQqWswZ;
      string aeDMOKIYBJ;
      string AKHPMPohTe;
      string IwdqPLsyny;
      string tnskiGKEkV;
      string BdjNAanuCB;
      string CoZRQeBMwD;
      string RJkDOMQVgG;
      string EjwxdeMQpn;
      if(QeedhiIrHe == kORAgJCkWA){XxwlwFNbUD = true;}
      else if(kORAgJCkWA == QeedhiIrHe){dbLJHqFbNH = true;}
      if(TeUCpFxcey == kuLOQqWswZ){FyHhDrsfym = true;}
      else if(kuLOQqWswZ == TeUCpFxcey){nxFzojClhx = true;}
      if(JdQsQmlDxV == aeDMOKIYBJ){KSOwwRrbnl = true;}
      else if(aeDMOKIYBJ == JdQsQmlDxV){BJVbyQlyta = true;}
      if(rKzZnUpazm == AKHPMPohTe){SkVHeTNyGJ = true;}
      else if(AKHPMPohTe == rKzZnUpazm){WyrOMNRYuJ = true;}
      if(WbcxTRJfUw == IwdqPLsyny){ynBcBGbOsk = true;}
      else if(IwdqPLsyny == WbcxTRJfUw){gpEWlmIJlK = true;}
      if(fgcyhlNkNu == tnskiGKEkV){kfRDdFiAoe = true;}
      else if(tnskiGKEkV == fgcyhlNkNu){KMkueTGiKp = true;}
      if(xFtllIfuOU == BdjNAanuCB){NknhjUbzCj = true;}
      else if(BdjNAanuCB == xFtllIfuOU){FHhmjoFqma = true;}
      if(PVdqahASZy == CoZRQeBMwD){dtZooWRkup = true;}
      if(dGhAoLhBqB == RJkDOMQVgG){pchCAmSSdZ = true;}
      if(GENEoRgpLK == EjwxdeMQpn){kNIbuNzSrg = true;}
      while(CoZRQeBMwD == PVdqahASZy){SdqXPKFzoL = true;}
      while(RJkDOMQVgG == RJkDOMQVgG){IcLiQJNxir = true;}
      while(EjwxdeMQpn == EjwxdeMQpn){HhNEEZHRlx = true;}
      if(XxwlwFNbUD == true){XxwlwFNbUD = false;}
      if(FyHhDrsfym == true){FyHhDrsfym = false;}
      if(KSOwwRrbnl == true){KSOwwRrbnl = false;}
      if(SkVHeTNyGJ == true){SkVHeTNyGJ = false;}
      if(ynBcBGbOsk == true){ynBcBGbOsk = false;}
      if(kfRDdFiAoe == true){kfRDdFiAoe = false;}
      if(NknhjUbzCj == true){NknhjUbzCj = false;}
      if(dtZooWRkup == true){dtZooWRkup = false;}
      if(pchCAmSSdZ == true){pchCAmSSdZ = false;}
      if(kNIbuNzSrg == true){kNIbuNzSrg = false;}
      if(dbLJHqFbNH == true){dbLJHqFbNH = false;}
      if(nxFzojClhx == true){nxFzojClhx = false;}
      if(BJVbyQlyta == true){BJVbyQlyta = false;}
      if(WyrOMNRYuJ == true){WyrOMNRYuJ = false;}
      if(gpEWlmIJlK == true){gpEWlmIJlK = false;}
      if(KMkueTGiKp == true){KMkueTGiKp = false;}
      if(FHhmjoFqma == true){FHhmjoFqma = false;}
      if(SdqXPKFzoL == true){SdqXPKFzoL = false;}
      if(IcLiQJNxir == true){IcLiQJNxir = false;}
      if(HhNEEZHRlx == true){HhNEEZHRlx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWUEULJZNI
{ 
  void pmGRHSzWYU()
  { 
      bool UcxueWEZkb = false;
      bool fwCBrtWttt = false;
      bool tYkDiebSdq = false;
      bool XfUkIfPeZm = false;
      bool wnYylVswuL = false;
      bool nzfCqwrtLz = false;
      bool ulwtDzbRsM = false;
      bool drUHyGAmRN = false;
      bool leXRCXASsM = false;
      bool mUSZrKqdtl = false;
      bool tbDhhweYDk = false;
      bool uFcyNPNdrf = false;
      bool zJXgYIYuOm = false;
      bool OWreSKbojG = false;
      bool sbOIQhqULb = false;
      bool wNkOmkDWJY = false;
      bool WiJPWXMyeD = false;
      bool nYtllWtPPq = false;
      bool QEjlqBkdqh = false;
      bool GFfLiJRykr = false;
      string xMzihHVjKp;
      string tosgkiQcaC;
      string OkhwgryazM;
      string CcKfmQUsXM;
      string usFlWDkkiL;
      string KZYSdLdDBp;
      string JujymQdMsU;
      string NWFNGVewZc;
      string GMqmBcEqBb;
      string lRqgCAIGyF;
      string YYqNxnUKLI;
      string ghdYjwDwxK;
      string LlKRhwfXKG;
      string MXyTDgVdoN;
      string ItfstEmSxG;
      string wLJnslOZeB;
      string HxzEwIiKUC;
      string aZGjCRGRWd;
      string INZEKBNKZR;
      string SuynFLtaxl;
      if(xMzihHVjKp == YYqNxnUKLI){UcxueWEZkb = true;}
      else if(YYqNxnUKLI == xMzihHVjKp){tbDhhweYDk = true;}
      if(tosgkiQcaC == ghdYjwDwxK){fwCBrtWttt = true;}
      else if(ghdYjwDwxK == tosgkiQcaC){uFcyNPNdrf = true;}
      if(OkhwgryazM == LlKRhwfXKG){tYkDiebSdq = true;}
      else if(LlKRhwfXKG == OkhwgryazM){zJXgYIYuOm = true;}
      if(CcKfmQUsXM == MXyTDgVdoN){XfUkIfPeZm = true;}
      else if(MXyTDgVdoN == CcKfmQUsXM){OWreSKbojG = true;}
      if(usFlWDkkiL == ItfstEmSxG){wnYylVswuL = true;}
      else if(ItfstEmSxG == usFlWDkkiL){sbOIQhqULb = true;}
      if(KZYSdLdDBp == wLJnslOZeB){nzfCqwrtLz = true;}
      else if(wLJnslOZeB == KZYSdLdDBp){wNkOmkDWJY = true;}
      if(JujymQdMsU == HxzEwIiKUC){ulwtDzbRsM = true;}
      else if(HxzEwIiKUC == JujymQdMsU){WiJPWXMyeD = true;}
      if(NWFNGVewZc == aZGjCRGRWd){drUHyGAmRN = true;}
      if(GMqmBcEqBb == INZEKBNKZR){leXRCXASsM = true;}
      if(lRqgCAIGyF == SuynFLtaxl){mUSZrKqdtl = true;}
      while(aZGjCRGRWd == NWFNGVewZc){nYtllWtPPq = true;}
      while(INZEKBNKZR == INZEKBNKZR){QEjlqBkdqh = true;}
      while(SuynFLtaxl == SuynFLtaxl){GFfLiJRykr = true;}
      if(UcxueWEZkb == true){UcxueWEZkb = false;}
      if(fwCBrtWttt == true){fwCBrtWttt = false;}
      if(tYkDiebSdq == true){tYkDiebSdq = false;}
      if(XfUkIfPeZm == true){XfUkIfPeZm = false;}
      if(wnYylVswuL == true){wnYylVswuL = false;}
      if(nzfCqwrtLz == true){nzfCqwrtLz = false;}
      if(ulwtDzbRsM == true){ulwtDzbRsM = false;}
      if(drUHyGAmRN == true){drUHyGAmRN = false;}
      if(leXRCXASsM == true){leXRCXASsM = false;}
      if(mUSZrKqdtl == true){mUSZrKqdtl = false;}
      if(tbDhhweYDk == true){tbDhhweYDk = false;}
      if(uFcyNPNdrf == true){uFcyNPNdrf = false;}
      if(zJXgYIYuOm == true){zJXgYIYuOm = false;}
      if(OWreSKbojG == true){OWreSKbojG = false;}
      if(sbOIQhqULb == true){sbOIQhqULb = false;}
      if(wNkOmkDWJY == true){wNkOmkDWJY = false;}
      if(WiJPWXMyeD == true){WiJPWXMyeD = false;}
      if(nYtllWtPPq == true){nYtllWtPPq = false;}
      if(QEjlqBkdqh == true){QEjlqBkdqh = false;}
      if(GFfLiJRykr == true){GFfLiJRykr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKMBODTHIQ
{ 
  void qmYYwEsTYt()
  { 
      bool efPZgxXixC = false;
      bool HaUDNYTtgH = false;
      bool QgMYkMtRtU = false;
      bool debLkVKtBy = false;
      bool UFWZQoJDWL = false;
      bool BrsEjyTqoT = false;
      bool DGocXczJSq = false;
      bool NYshmLJmIu = false;
      bool DpthSllWam = false;
      bool CTFguOQtBm = false;
      bool pAkfyczKRY = false;
      bool nfisQMLGJl = false;
      bool qbhensSLmX = false;
      bool tPkUFCFOjo = false;
      bool laFCyVjMQi = false;
      bool DKjPwNSFqF = false;
      bool KmXsdYuOmN = false;
      bool GwWTzPWegR = false;
      bool IFtDUjeVXq = false;
      bool jzXeezDLXZ = false;
      string zaHWdXQuoS;
      string CVmBhLckfV;
      string QEWcbBFwDz;
      string bUeANtjrju;
      string xTUcgPEpEP;
      string ZjUzRtDeuc;
      string SUqopgqlnm;
      string bkBjYwituL;
      string xOqnYrAfiS;
      string pEwGcccelA;
      string YRCQmnijaU;
      string KJjifEcCPy;
      string gLCUxWnuHw;
      string TEHuleMaAk;
      string IPFOHgUNZY;
      string zZOmSNOgTP;
      string zncdBGBnxA;
      string qBCeoQFnMP;
      string CaUhwsoUbX;
      string PeHjkUmaMB;
      if(zaHWdXQuoS == YRCQmnijaU){efPZgxXixC = true;}
      else if(YRCQmnijaU == zaHWdXQuoS){pAkfyczKRY = true;}
      if(CVmBhLckfV == KJjifEcCPy){HaUDNYTtgH = true;}
      else if(KJjifEcCPy == CVmBhLckfV){nfisQMLGJl = true;}
      if(QEWcbBFwDz == gLCUxWnuHw){QgMYkMtRtU = true;}
      else if(gLCUxWnuHw == QEWcbBFwDz){qbhensSLmX = true;}
      if(bUeANtjrju == TEHuleMaAk){debLkVKtBy = true;}
      else if(TEHuleMaAk == bUeANtjrju){tPkUFCFOjo = true;}
      if(xTUcgPEpEP == IPFOHgUNZY){UFWZQoJDWL = true;}
      else if(IPFOHgUNZY == xTUcgPEpEP){laFCyVjMQi = true;}
      if(ZjUzRtDeuc == zZOmSNOgTP){BrsEjyTqoT = true;}
      else if(zZOmSNOgTP == ZjUzRtDeuc){DKjPwNSFqF = true;}
      if(SUqopgqlnm == zncdBGBnxA){DGocXczJSq = true;}
      else if(zncdBGBnxA == SUqopgqlnm){KmXsdYuOmN = true;}
      if(bkBjYwituL == qBCeoQFnMP){NYshmLJmIu = true;}
      if(xOqnYrAfiS == CaUhwsoUbX){DpthSllWam = true;}
      if(pEwGcccelA == PeHjkUmaMB){CTFguOQtBm = true;}
      while(qBCeoQFnMP == bkBjYwituL){GwWTzPWegR = true;}
      while(CaUhwsoUbX == CaUhwsoUbX){IFtDUjeVXq = true;}
      while(PeHjkUmaMB == PeHjkUmaMB){jzXeezDLXZ = true;}
      if(efPZgxXixC == true){efPZgxXixC = false;}
      if(HaUDNYTtgH == true){HaUDNYTtgH = false;}
      if(QgMYkMtRtU == true){QgMYkMtRtU = false;}
      if(debLkVKtBy == true){debLkVKtBy = false;}
      if(UFWZQoJDWL == true){UFWZQoJDWL = false;}
      if(BrsEjyTqoT == true){BrsEjyTqoT = false;}
      if(DGocXczJSq == true){DGocXczJSq = false;}
      if(NYshmLJmIu == true){NYshmLJmIu = false;}
      if(DpthSllWam == true){DpthSllWam = false;}
      if(CTFguOQtBm == true){CTFguOQtBm = false;}
      if(pAkfyczKRY == true){pAkfyczKRY = false;}
      if(nfisQMLGJl == true){nfisQMLGJl = false;}
      if(qbhensSLmX == true){qbhensSLmX = false;}
      if(tPkUFCFOjo == true){tPkUFCFOjo = false;}
      if(laFCyVjMQi == true){laFCyVjMQi = false;}
      if(DKjPwNSFqF == true){DKjPwNSFqF = false;}
      if(KmXsdYuOmN == true){KmXsdYuOmN = false;}
      if(GwWTzPWegR == true){GwWTzPWegR = false;}
      if(IFtDUjeVXq == true){IFtDUjeVXq = false;}
      if(jzXeezDLXZ == true){jzXeezDLXZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLBOJHNHGO
{ 
  void SRQgGxeZbJ()
  { 
      bool VUacZJoHMY = false;
      bool tleuTRjfrt = false;
      bool MEbfzLfCsi = false;
      bool fsjMJNNJWs = false;
      bool TIliMSBros = false;
      bool dkQfFQsudO = false;
      bool dlOcrACSkG = false;
      bool EaJyaESrTg = false;
      bool KnMzFtcEHs = false;
      bool URfIPgsJqL = false;
      bool PhGinDbRFA = false;
      bool yAawEoYOXx = false;
      bool XyLrkltAis = false;
      bool KJBHQbhdKC = false;
      bool SLzGuUqiEZ = false;
      bool IdksnRWOyC = false;
      bool IaiLpoyTfb = false;
      bool HuDVeMzExQ = false;
      bool uKwIjfXISz = false;
      bool FTeIsqbmPG = false;
      string KgHjlqtlot;
      string nfNqBoEndZ;
      string ssNwpthTGq;
      string fDumRHfxeK;
      string jHgJBlJIZB;
      string PBMQyRSKtq;
      string IaeyOjjaYt;
      string JGISplLEuE;
      string jZsFaepenA;
      string nUDnCJbitQ;
      string BiifrJrtaM;
      string FOPoGigZWj;
      string tFlYFnCUQf;
      string JcJeCBpNMR;
      string lwDbtZFNhS;
      string cBMKWwwJaD;
      string GXduCcEjmE;
      string rSMExyBJde;
      string inmxDIPzIG;
      string EgmJLORIZR;
      if(KgHjlqtlot == BiifrJrtaM){VUacZJoHMY = true;}
      else if(BiifrJrtaM == KgHjlqtlot){PhGinDbRFA = true;}
      if(nfNqBoEndZ == FOPoGigZWj){tleuTRjfrt = true;}
      else if(FOPoGigZWj == nfNqBoEndZ){yAawEoYOXx = true;}
      if(ssNwpthTGq == tFlYFnCUQf){MEbfzLfCsi = true;}
      else if(tFlYFnCUQf == ssNwpthTGq){XyLrkltAis = true;}
      if(fDumRHfxeK == JcJeCBpNMR){fsjMJNNJWs = true;}
      else if(JcJeCBpNMR == fDumRHfxeK){KJBHQbhdKC = true;}
      if(jHgJBlJIZB == lwDbtZFNhS){TIliMSBros = true;}
      else if(lwDbtZFNhS == jHgJBlJIZB){SLzGuUqiEZ = true;}
      if(PBMQyRSKtq == cBMKWwwJaD){dkQfFQsudO = true;}
      else if(cBMKWwwJaD == PBMQyRSKtq){IdksnRWOyC = true;}
      if(IaeyOjjaYt == GXduCcEjmE){dlOcrACSkG = true;}
      else if(GXduCcEjmE == IaeyOjjaYt){IaiLpoyTfb = true;}
      if(JGISplLEuE == rSMExyBJde){EaJyaESrTg = true;}
      if(jZsFaepenA == inmxDIPzIG){KnMzFtcEHs = true;}
      if(nUDnCJbitQ == EgmJLORIZR){URfIPgsJqL = true;}
      while(rSMExyBJde == JGISplLEuE){HuDVeMzExQ = true;}
      while(inmxDIPzIG == inmxDIPzIG){uKwIjfXISz = true;}
      while(EgmJLORIZR == EgmJLORIZR){FTeIsqbmPG = true;}
      if(VUacZJoHMY == true){VUacZJoHMY = false;}
      if(tleuTRjfrt == true){tleuTRjfrt = false;}
      if(MEbfzLfCsi == true){MEbfzLfCsi = false;}
      if(fsjMJNNJWs == true){fsjMJNNJWs = false;}
      if(TIliMSBros == true){TIliMSBros = false;}
      if(dkQfFQsudO == true){dkQfFQsudO = false;}
      if(dlOcrACSkG == true){dlOcrACSkG = false;}
      if(EaJyaESrTg == true){EaJyaESrTg = false;}
      if(KnMzFtcEHs == true){KnMzFtcEHs = false;}
      if(URfIPgsJqL == true){URfIPgsJqL = false;}
      if(PhGinDbRFA == true){PhGinDbRFA = false;}
      if(yAawEoYOXx == true){yAawEoYOXx = false;}
      if(XyLrkltAis == true){XyLrkltAis = false;}
      if(KJBHQbhdKC == true){KJBHQbhdKC = false;}
      if(SLzGuUqiEZ == true){SLzGuUqiEZ = false;}
      if(IdksnRWOyC == true){IdksnRWOyC = false;}
      if(IaiLpoyTfb == true){IaiLpoyTfb = false;}
      if(HuDVeMzExQ == true){HuDVeMzExQ = false;}
      if(uKwIjfXISz == true){uKwIjfXISz = false;}
      if(FTeIsqbmPG == true){FTeIsqbmPG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRVWISTPRG
{ 
  void cgIPIEmudX()
  { 
      bool WYEWZmQTon = false;
      bool PrKqBPbkwP = false;
      bool NsAjKmHqBV = false;
      bool HnPQKaXQSX = false;
      bool CoKrQMfFyX = false;
      bool laQOWcYTLl = false;
      bool eYSTgactgZ = false;
      bool rLRYNYiHTy = false;
      bool HCscifWAtg = false;
      bool CEEfrcVqLo = false;
      bool ikXYfaIrBx = false;
      bool tQANecfpjA = false;
      bool DbAAWmGkfj = false;
      bool CqudOVeTwI = false;
      bool WezwlkEpBP = false;
      bool xfHLlGkWBr = false;
      bool UXLQtCVVyI = false;
      bool yLsbcYcDOk = false;
      bool iPjQmWjjrI = false;
      bool kHSDnzShBi = false;
      string OGVbwGSttC;
      string yQbqtfSBYL;
      string VacubFAyuy;
      string WYNAkMAjjq;
      string nxbRppUbEm;
      string ZFIhfndZAq;
      string FUzueZCbGg;
      string fiRhWXyLEk;
      string jYsHYRQfUx;
      string iZjrkTyflQ;
      string nsVWHqnaKH;
      string oSUOGgaqWN;
      string JWGJyFyYwD;
      string ZRYnxqCVAg;
      string cpUMHQFVlD;
      string rGJYHQlMYB;
      string sOdHhWsfQP;
      string dEpojTBtBg;
      string AcmsKSIzff;
      string EpxznNLNdk;
      if(OGVbwGSttC == nsVWHqnaKH){WYEWZmQTon = true;}
      else if(nsVWHqnaKH == OGVbwGSttC){ikXYfaIrBx = true;}
      if(yQbqtfSBYL == oSUOGgaqWN){PrKqBPbkwP = true;}
      else if(oSUOGgaqWN == yQbqtfSBYL){tQANecfpjA = true;}
      if(VacubFAyuy == JWGJyFyYwD){NsAjKmHqBV = true;}
      else if(JWGJyFyYwD == VacubFAyuy){DbAAWmGkfj = true;}
      if(WYNAkMAjjq == ZRYnxqCVAg){HnPQKaXQSX = true;}
      else if(ZRYnxqCVAg == WYNAkMAjjq){CqudOVeTwI = true;}
      if(nxbRppUbEm == cpUMHQFVlD){CoKrQMfFyX = true;}
      else if(cpUMHQFVlD == nxbRppUbEm){WezwlkEpBP = true;}
      if(ZFIhfndZAq == rGJYHQlMYB){laQOWcYTLl = true;}
      else if(rGJYHQlMYB == ZFIhfndZAq){xfHLlGkWBr = true;}
      if(FUzueZCbGg == sOdHhWsfQP){eYSTgactgZ = true;}
      else if(sOdHhWsfQP == FUzueZCbGg){UXLQtCVVyI = true;}
      if(fiRhWXyLEk == dEpojTBtBg){rLRYNYiHTy = true;}
      if(jYsHYRQfUx == AcmsKSIzff){HCscifWAtg = true;}
      if(iZjrkTyflQ == EpxznNLNdk){CEEfrcVqLo = true;}
      while(dEpojTBtBg == fiRhWXyLEk){yLsbcYcDOk = true;}
      while(AcmsKSIzff == AcmsKSIzff){iPjQmWjjrI = true;}
      while(EpxznNLNdk == EpxznNLNdk){kHSDnzShBi = true;}
      if(WYEWZmQTon == true){WYEWZmQTon = false;}
      if(PrKqBPbkwP == true){PrKqBPbkwP = false;}
      if(NsAjKmHqBV == true){NsAjKmHqBV = false;}
      if(HnPQKaXQSX == true){HnPQKaXQSX = false;}
      if(CoKrQMfFyX == true){CoKrQMfFyX = false;}
      if(laQOWcYTLl == true){laQOWcYTLl = false;}
      if(eYSTgactgZ == true){eYSTgactgZ = false;}
      if(rLRYNYiHTy == true){rLRYNYiHTy = false;}
      if(HCscifWAtg == true){HCscifWAtg = false;}
      if(CEEfrcVqLo == true){CEEfrcVqLo = false;}
      if(ikXYfaIrBx == true){ikXYfaIrBx = false;}
      if(tQANecfpjA == true){tQANecfpjA = false;}
      if(DbAAWmGkfj == true){DbAAWmGkfj = false;}
      if(CqudOVeTwI == true){CqudOVeTwI = false;}
      if(WezwlkEpBP == true){WezwlkEpBP = false;}
      if(xfHLlGkWBr == true){xfHLlGkWBr = false;}
      if(UXLQtCVVyI == true){UXLQtCVVyI = false;}
      if(yLsbcYcDOk == true){yLsbcYcDOk = false;}
      if(iPjQmWjjrI == true){iPjQmWjjrI = false;}
      if(kHSDnzShBi == true){kHSDnzShBi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMPVACGQPV
{ 
  void VCfqgUdcTm()
  { 
      bool CLXstIKhca = false;
      bool oWaGLrQZVH = false;
      bool iLVeEsyQki = false;
      bool yVsjSoKAQC = false;
      bool NHtUcZlnzX = false;
      bool lCCXXppsnA = false;
      bool JsxtcTdpnV = false;
      bool hPJStbRABe = false;
      bool HJRMwuSVLb = false;
      bool yQMPsTKArJ = false;
      bool uuAcoWsjcw = false;
      bool YoqIsAbjxg = false;
      bool AIdLWQCsZZ = false;
      bool RQIrjLJoXZ = false;
      bool CirPDJYEWr = false;
      bool qZDKIlRnFY = false;
      bool TzJCeHgzXg = false;
      bool qmMWeQQOHN = false;
      bool ryVghqMxix = false;
      bool tUiyGCYokw = false;
      string uxctyhaznD;
      string BXcmrWWfxY;
      string BtaZNjWDiY;
      string pEarhdxzCy;
      string rDraleOyxS;
      string CcubpBVDgO;
      string KXQPMxxkFO;
      string ZWczgyCAmi;
      string UXGQWNJzCf;
      string HtSnmTmbNo;
      string gdrhrezwtq;
      string zVPxsmRzrz;
      string nyiYGfDoLN;
      string LZlxBqfXXq;
      string NMEKgldUtA;
      string CmjOBiuSbM;
      string aKjgfYiRwB;
      string GtbBlasXrU;
      string BitKKXpXwR;
      string wMuKPCbXeH;
      if(uxctyhaznD == gdrhrezwtq){CLXstIKhca = true;}
      else if(gdrhrezwtq == uxctyhaznD){uuAcoWsjcw = true;}
      if(BXcmrWWfxY == zVPxsmRzrz){oWaGLrQZVH = true;}
      else if(zVPxsmRzrz == BXcmrWWfxY){YoqIsAbjxg = true;}
      if(BtaZNjWDiY == nyiYGfDoLN){iLVeEsyQki = true;}
      else if(nyiYGfDoLN == BtaZNjWDiY){AIdLWQCsZZ = true;}
      if(pEarhdxzCy == LZlxBqfXXq){yVsjSoKAQC = true;}
      else if(LZlxBqfXXq == pEarhdxzCy){RQIrjLJoXZ = true;}
      if(rDraleOyxS == NMEKgldUtA){NHtUcZlnzX = true;}
      else if(NMEKgldUtA == rDraleOyxS){CirPDJYEWr = true;}
      if(CcubpBVDgO == CmjOBiuSbM){lCCXXppsnA = true;}
      else if(CmjOBiuSbM == CcubpBVDgO){qZDKIlRnFY = true;}
      if(KXQPMxxkFO == aKjgfYiRwB){JsxtcTdpnV = true;}
      else if(aKjgfYiRwB == KXQPMxxkFO){TzJCeHgzXg = true;}
      if(ZWczgyCAmi == GtbBlasXrU){hPJStbRABe = true;}
      if(UXGQWNJzCf == BitKKXpXwR){HJRMwuSVLb = true;}
      if(HtSnmTmbNo == wMuKPCbXeH){yQMPsTKArJ = true;}
      while(GtbBlasXrU == ZWczgyCAmi){qmMWeQQOHN = true;}
      while(BitKKXpXwR == BitKKXpXwR){ryVghqMxix = true;}
      while(wMuKPCbXeH == wMuKPCbXeH){tUiyGCYokw = true;}
      if(CLXstIKhca == true){CLXstIKhca = false;}
      if(oWaGLrQZVH == true){oWaGLrQZVH = false;}
      if(iLVeEsyQki == true){iLVeEsyQki = false;}
      if(yVsjSoKAQC == true){yVsjSoKAQC = false;}
      if(NHtUcZlnzX == true){NHtUcZlnzX = false;}
      if(lCCXXppsnA == true){lCCXXppsnA = false;}
      if(JsxtcTdpnV == true){JsxtcTdpnV = false;}
      if(hPJStbRABe == true){hPJStbRABe = false;}
      if(HJRMwuSVLb == true){HJRMwuSVLb = false;}
      if(yQMPsTKArJ == true){yQMPsTKArJ = false;}
      if(uuAcoWsjcw == true){uuAcoWsjcw = false;}
      if(YoqIsAbjxg == true){YoqIsAbjxg = false;}
      if(AIdLWQCsZZ == true){AIdLWQCsZZ = false;}
      if(RQIrjLJoXZ == true){RQIrjLJoXZ = false;}
      if(CirPDJYEWr == true){CirPDJYEWr = false;}
      if(qZDKIlRnFY == true){qZDKIlRnFY = false;}
      if(TzJCeHgzXg == true){TzJCeHgzXg = false;}
      if(qmMWeQQOHN == true){qmMWeQQOHN = false;}
      if(ryVghqMxix == true){ryVghqMxix = false;}
      if(tUiyGCYokw == true){tUiyGCYokw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KMRNEPUOHS
{ 
  void kxZhKsXZcZ()
  { 
      bool dykehwltXp = false;
      bool lirCHGTDgM = false;
      bool HBWVMImRCn = false;
      bool YVlStWyRry = false;
      bool rUHmcPLhxF = false;
      bool YbJQucbOSY = false;
      bool JTqiQQxYIk = false;
      bool IBLhTmsisw = false;
      bool xETwPwLUXQ = false;
      bool tiySoXdXVL = false;
      bool RlZMwWQbwI = false;
      bool isVWbFztTT = false;
      bool FcBqpZCrsw = false;
      bool IUMgdLdGAr = false;
      bool fjYOgBNbqj = false;
      bool YiECGojiWW = false;
      bool TXiAzOgnrP = false;
      bool artamUEmJo = false;
      bool LaAIXZQKao = false;
      bool aujcYIBXPS = false;
      string mcIIhQpKqR;
      string SQMhlOshaW;
      string KsfGPrHnVY;
      string MyXgPaXPqh;
      string EFsAbWNdUo;
      string ZxqLitxBso;
      string IBnRFUrfRL;
      string pcqsSEzees;
      string edTgzPHMxU;
      string cVWBYCQatH;
      string dgLIywGxsd;
      string uRWAJehHSp;
      string NfhwiUFoTP;
      string nXkWOySKiD;
      string JJTTZKyWqt;
      string UJIEtyyOZd;
      string pQdcpWgzkL;
      string MXXOgELOWX;
      string VixZudOfcP;
      string zDjFMrepcD;
      if(mcIIhQpKqR == dgLIywGxsd){dykehwltXp = true;}
      else if(dgLIywGxsd == mcIIhQpKqR){RlZMwWQbwI = true;}
      if(SQMhlOshaW == uRWAJehHSp){lirCHGTDgM = true;}
      else if(uRWAJehHSp == SQMhlOshaW){isVWbFztTT = true;}
      if(KsfGPrHnVY == NfhwiUFoTP){HBWVMImRCn = true;}
      else if(NfhwiUFoTP == KsfGPrHnVY){FcBqpZCrsw = true;}
      if(MyXgPaXPqh == nXkWOySKiD){YVlStWyRry = true;}
      else if(nXkWOySKiD == MyXgPaXPqh){IUMgdLdGAr = true;}
      if(EFsAbWNdUo == JJTTZKyWqt){rUHmcPLhxF = true;}
      else if(JJTTZKyWqt == EFsAbWNdUo){fjYOgBNbqj = true;}
      if(ZxqLitxBso == UJIEtyyOZd){YbJQucbOSY = true;}
      else if(UJIEtyyOZd == ZxqLitxBso){YiECGojiWW = true;}
      if(IBnRFUrfRL == pQdcpWgzkL){JTqiQQxYIk = true;}
      else if(pQdcpWgzkL == IBnRFUrfRL){TXiAzOgnrP = true;}
      if(pcqsSEzees == MXXOgELOWX){IBLhTmsisw = true;}
      if(edTgzPHMxU == VixZudOfcP){xETwPwLUXQ = true;}
      if(cVWBYCQatH == zDjFMrepcD){tiySoXdXVL = true;}
      while(MXXOgELOWX == pcqsSEzees){artamUEmJo = true;}
      while(VixZudOfcP == VixZudOfcP){LaAIXZQKao = true;}
      while(zDjFMrepcD == zDjFMrepcD){aujcYIBXPS = true;}
      if(dykehwltXp == true){dykehwltXp = false;}
      if(lirCHGTDgM == true){lirCHGTDgM = false;}
      if(HBWVMImRCn == true){HBWVMImRCn = false;}
      if(YVlStWyRry == true){YVlStWyRry = false;}
      if(rUHmcPLhxF == true){rUHmcPLhxF = false;}
      if(YbJQucbOSY == true){YbJQucbOSY = false;}
      if(JTqiQQxYIk == true){JTqiQQxYIk = false;}
      if(IBLhTmsisw == true){IBLhTmsisw = false;}
      if(xETwPwLUXQ == true){xETwPwLUXQ = false;}
      if(tiySoXdXVL == true){tiySoXdXVL = false;}
      if(RlZMwWQbwI == true){RlZMwWQbwI = false;}
      if(isVWbFztTT == true){isVWbFztTT = false;}
      if(FcBqpZCrsw == true){FcBqpZCrsw = false;}
      if(IUMgdLdGAr == true){IUMgdLdGAr = false;}
      if(fjYOgBNbqj == true){fjYOgBNbqj = false;}
      if(YiECGojiWW == true){YiECGojiWW = false;}
      if(TXiAzOgnrP == true){TXiAzOgnrP = false;}
      if(artamUEmJo == true){artamUEmJo = false;}
      if(LaAIXZQKao == true){LaAIXZQKao = false;}
      if(aujcYIBXPS == true){aujcYIBXPS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXZMTNLIME
{ 
  void RSboTMrYIH()
  { 
      bool OADuzjeiWb = false;
      bool mmUcDnatZg = false;
      bool RVagPMenNx = false;
      bool EefNOrORgi = false;
      bool yAiAOhWJTU = false;
      bool XwpFwsYWem = false;
      bool EpVZXHGHNL = false;
      bool YIMphRmZRh = false;
      bool oVTsYInaQV = false;
      bool SrmseIeIcG = false;
      bool aOuHuPiAWe = false;
      bool FyExxiVcAO = false;
      bool SfprsgVTLZ = false;
      bool mdwLGaZLxI = false;
      bool YnDlQTmoww = false;
      bool lCINmuXDON = false;
      bool sPnxraBsqW = false;
      bool IJeqpecEaY = false;
      bool tgWPnkVhXL = false;
      bool CWxjOJAGso = false;
      string uQowmlrFAI;
      string IEyUdzOFBh;
      string JbnDzVOJLr;
      string AUXCXSsDNT;
      string xQyLVWTkmy;
      string TbrzYTbkxQ;
      string WisIImfuwK;
      string FKrgjrdbhc;
      string BdVMXXbYdE;
      string pIGwxOXoDh;
      string pYnbsJjKOf;
      string oADUOsMfjj;
      string LGRqUxDujV;
      string UnYzlcotTO;
      string nQKyPpElgD;
      string CqESWjHxHw;
      string FnasKBaEil;
      string ERMVwtwTbd;
      string rRNgTdiFcC;
      string VrmXIzpQmO;
      if(uQowmlrFAI == pYnbsJjKOf){OADuzjeiWb = true;}
      else if(pYnbsJjKOf == uQowmlrFAI){aOuHuPiAWe = true;}
      if(IEyUdzOFBh == oADUOsMfjj){mmUcDnatZg = true;}
      else if(oADUOsMfjj == IEyUdzOFBh){FyExxiVcAO = true;}
      if(JbnDzVOJLr == LGRqUxDujV){RVagPMenNx = true;}
      else if(LGRqUxDujV == JbnDzVOJLr){SfprsgVTLZ = true;}
      if(AUXCXSsDNT == UnYzlcotTO){EefNOrORgi = true;}
      else if(UnYzlcotTO == AUXCXSsDNT){mdwLGaZLxI = true;}
      if(xQyLVWTkmy == nQKyPpElgD){yAiAOhWJTU = true;}
      else if(nQKyPpElgD == xQyLVWTkmy){YnDlQTmoww = true;}
      if(TbrzYTbkxQ == CqESWjHxHw){XwpFwsYWem = true;}
      else if(CqESWjHxHw == TbrzYTbkxQ){lCINmuXDON = true;}
      if(WisIImfuwK == FnasKBaEil){EpVZXHGHNL = true;}
      else if(FnasKBaEil == WisIImfuwK){sPnxraBsqW = true;}
      if(FKrgjrdbhc == ERMVwtwTbd){YIMphRmZRh = true;}
      if(BdVMXXbYdE == rRNgTdiFcC){oVTsYInaQV = true;}
      if(pIGwxOXoDh == VrmXIzpQmO){SrmseIeIcG = true;}
      while(ERMVwtwTbd == FKrgjrdbhc){IJeqpecEaY = true;}
      while(rRNgTdiFcC == rRNgTdiFcC){tgWPnkVhXL = true;}
      while(VrmXIzpQmO == VrmXIzpQmO){CWxjOJAGso = true;}
      if(OADuzjeiWb == true){OADuzjeiWb = false;}
      if(mmUcDnatZg == true){mmUcDnatZg = false;}
      if(RVagPMenNx == true){RVagPMenNx = false;}
      if(EefNOrORgi == true){EefNOrORgi = false;}
      if(yAiAOhWJTU == true){yAiAOhWJTU = false;}
      if(XwpFwsYWem == true){XwpFwsYWem = false;}
      if(EpVZXHGHNL == true){EpVZXHGHNL = false;}
      if(YIMphRmZRh == true){YIMphRmZRh = false;}
      if(oVTsYInaQV == true){oVTsYInaQV = false;}
      if(SrmseIeIcG == true){SrmseIeIcG = false;}
      if(aOuHuPiAWe == true){aOuHuPiAWe = false;}
      if(FyExxiVcAO == true){FyExxiVcAO = false;}
      if(SfprsgVTLZ == true){SfprsgVTLZ = false;}
      if(mdwLGaZLxI == true){mdwLGaZLxI = false;}
      if(YnDlQTmoww == true){YnDlQTmoww = false;}
      if(lCINmuXDON == true){lCINmuXDON = false;}
      if(sPnxraBsqW == true){sPnxraBsqW = false;}
      if(IJeqpecEaY == true){IJeqpecEaY = false;}
      if(tgWPnkVhXL == true){tgWPnkVhXL = false;}
      if(CWxjOJAGso == true){CWxjOJAGso = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUBGMXOVAG
{ 
  void EDJdOUGboc()
  { 
      bool kDBqReaNpu = false;
      bool eesXqCAfmr = false;
      bool kwrhGMrSpL = false;
      bool mDuSzQOQyd = false;
      bool ooTdXphLlB = false;
      bool BAnfBoKTjF = false;
      bool lIWeHajZXZ = false;
      bool mjhJCwbNJQ = false;
      bool dffoJlPPQK = false;
      bool FufsqgRnWw = false;
      bool GImLNQSdcE = false;
      bool MwJTaFchUU = false;
      bool KTINUrEoSV = false;
      bool enqMKVsTbs = false;
      bool TllMyIlMRk = false;
      bool DiSBllzZpU = false;
      bool MdKHYYFwIF = false;
      bool MIFbBYhwPM = false;
      bool FqXhRuUoaY = false;
      bool WTcGfpbemY = false;
      string wpYBOLzkFm;
      string EPENKHwVeH;
      string bOgNazrDLx;
      string VHdXGVnKen;
      string UgfrKyflZU;
      string GaKwsgJKZO;
      string TwZHRwkfGo;
      string TlqpmuioDb;
      string TFcpqtxgeZ;
      string McjPTYGYaO;
      string NzfkBUjTJx;
      string yUHyuNSjQW;
      string yDBgbpBbWN;
      string nKNoNTZrnW;
      string JdXhaqVkTF;
      string FWHDPKyyIK;
      string SIwwJnGRjb;
      string nautMUfTFk;
      string TPHQIQCKZC;
      string UaicDBgbXm;
      if(wpYBOLzkFm == NzfkBUjTJx){kDBqReaNpu = true;}
      else if(NzfkBUjTJx == wpYBOLzkFm){GImLNQSdcE = true;}
      if(EPENKHwVeH == yUHyuNSjQW){eesXqCAfmr = true;}
      else if(yUHyuNSjQW == EPENKHwVeH){MwJTaFchUU = true;}
      if(bOgNazrDLx == yDBgbpBbWN){kwrhGMrSpL = true;}
      else if(yDBgbpBbWN == bOgNazrDLx){KTINUrEoSV = true;}
      if(VHdXGVnKen == nKNoNTZrnW){mDuSzQOQyd = true;}
      else if(nKNoNTZrnW == VHdXGVnKen){enqMKVsTbs = true;}
      if(UgfrKyflZU == JdXhaqVkTF){ooTdXphLlB = true;}
      else if(JdXhaqVkTF == UgfrKyflZU){TllMyIlMRk = true;}
      if(GaKwsgJKZO == FWHDPKyyIK){BAnfBoKTjF = true;}
      else if(FWHDPKyyIK == GaKwsgJKZO){DiSBllzZpU = true;}
      if(TwZHRwkfGo == SIwwJnGRjb){lIWeHajZXZ = true;}
      else if(SIwwJnGRjb == TwZHRwkfGo){MdKHYYFwIF = true;}
      if(TlqpmuioDb == nautMUfTFk){mjhJCwbNJQ = true;}
      if(TFcpqtxgeZ == TPHQIQCKZC){dffoJlPPQK = true;}
      if(McjPTYGYaO == UaicDBgbXm){FufsqgRnWw = true;}
      while(nautMUfTFk == TlqpmuioDb){MIFbBYhwPM = true;}
      while(TPHQIQCKZC == TPHQIQCKZC){FqXhRuUoaY = true;}
      while(UaicDBgbXm == UaicDBgbXm){WTcGfpbemY = true;}
      if(kDBqReaNpu == true){kDBqReaNpu = false;}
      if(eesXqCAfmr == true){eesXqCAfmr = false;}
      if(kwrhGMrSpL == true){kwrhGMrSpL = false;}
      if(mDuSzQOQyd == true){mDuSzQOQyd = false;}
      if(ooTdXphLlB == true){ooTdXphLlB = false;}
      if(BAnfBoKTjF == true){BAnfBoKTjF = false;}
      if(lIWeHajZXZ == true){lIWeHajZXZ = false;}
      if(mjhJCwbNJQ == true){mjhJCwbNJQ = false;}
      if(dffoJlPPQK == true){dffoJlPPQK = false;}
      if(FufsqgRnWw == true){FufsqgRnWw = false;}
      if(GImLNQSdcE == true){GImLNQSdcE = false;}
      if(MwJTaFchUU == true){MwJTaFchUU = false;}
      if(KTINUrEoSV == true){KTINUrEoSV = false;}
      if(enqMKVsTbs == true){enqMKVsTbs = false;}
      if(TllMyIlMRk == true){TllMyIlMRk = false;}
      if(DiSBllzZpU == true){DiSBllzZpU = false;}
      if(MdKHYYFwIF == true){MdKHYYFwIF = false;}
      if(MIFbBYhwPM == true){MIFbBYhwPM = false;}
      if(FqXhRuUoaY == true){FqXhRuUoaY = false;}
      if(WTcGfpbemY == true){WTcGfpbemY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGIRDJMZXD
{ 
  void pYfrHXHsuP()
  { 
      bool eNXUWGiExu = false;
      bool ZOytkbogkr = false;
      bool WozRCSXFGp = false;
      bool QkfxgiwsSM = false;
      bool whNznDuJDC = false;
      bool CgzAZpOGSD = false;
      bool icyHdnhBNB = false;
      bool ewNYunazcy = false;
      bool XOCDmjlfXq = false;
      bool UpaPdTiFUA = false;
      bool UswBXGTZFk = false;
      bool OOcTeTatTt = false;
      bool CCdVgnUyua = false;
      bool EUecceRAeg = false;
      bool PLZlbFMHjJ = false;
      bool rolZxSPZUi = false;
      bool kVedfsjApA = false;
      bool CaOmepbqsb = false;
      bool bNOlhPiFeK = false;
      bool OrfwusgwGi = false;
      string FsmmJdHBxQ;
      string qWUshgayOb;
      string apxHdyFQZn;
      string hpRhETDFcG;
      string JVLtsLOdKQ;
      string qdGXkOueJK;
      string YpaJiAElnO;
      string cUVISEdDOR;
      string iaFJxEjsxp;
      string XXwRhSuCLr;
      string GcpwmVHyEg;
      string krQqbxkRMe;
      string QKoypEYEaA;
      string JbrVKGkJWa;
      string wkoPEeHEpj;
      string hcofawnqFh;
      string wDWEXIAtfU;
      string MatkheVYsL;
      string xUOpSflLuO;
      string SsDnerNjrw;
      if(FsmmJdHBxQ == GcpwmVHyEg){eNXUWGiExu = true;}
      else if(GcpwmVHyEg == FsmmJdHBxQ){UswBXGTZFk = true;}
      if(qWUshgayOb == krQqbxkRMe){ZOytkbogkr = true;}
      else if(krQqbxkRMe == qWUshgayOb){OOcTeTatTt = true;}
      if(apxHdyFQZn == QKoypEYEaA){WozRCSXFGp = true;}
      else if(QKoypEYEaA == apxHdyFQZn){CCdVgnUyua = true;}
      if(hpRhETDFcG == JbrVKGkJWa){QkfxgiwsSM = true;}
      else if(JbrVKGkJWa == hpRhETDFcG){EUecceRAeg = true;}
      if(JVLtsLOdKQ == wkoPEeHEpj){whNznDuJDC = true;}
      else if(wkoPEeHEpj == JVLtsLOdKQ){PLZlbFMHjJ = true;}
      if(qdGXkOueJK == hcofawnqFh){CgzAZpOGSD = true;}
      else if(hcofawnqFh == qdGXkOueJK){rolZxSPZUi = true;}
      if(YpaJiAElnO == wDWEXIAtfU){icyHdnhBNB = true;}
      else if(wDWEXIAtfU == YpaJiAElnO){kVedfsjApA = true;}
      if(cUVISEdDOR == MatkheVYsL){ewNYunazcy = true;}
      if(iaFJxEjsxp == xUOpSflLuO){XOCDmjlfXq = true;}
      if(XXwRhSuCLr == SsDnerNjrw){UpaPdTiFUA = true;}
      while(MatkheVYsL == cUVISEdDOR){CaOmepbqsb = true;}
      while(xUOpSflLuO == xUOpSflLuO){bNOlhPiFeK = true;}
      while(SsDnerNjrw == SsDnerNjrw){OrfwusgwGi = true;}
      if(eNXUWGiExu == true){eNXUWGiExu = false;}
      if(ZOytkbogkr == true){ZOytkbogkr = false;}
      if(WozRCSXFGp == true){WozRCSXFGp = false;}
      if(QkfxgiwsSM == true){QkfxgiwsSM = false;}
      if(whNznDuJDC == true){whNznDuJDC = false;}
      if(CgzAZpOGSD == true){CgzAZpOGSD = false;}
      if(icyHdnhBNB == true){icyHdnhBNB = false;}
      if(ewNYunazcy == true){ewNYunazcy = false;}
      if(XOCDmjlfXq == true){XOCDmjlfXq = false;}
      if(UpaPdTiFUA == true){UpaPdTiFUA = false;}
      if(UswBXGTZFk == true){UswBXGTZFk = false;}
      if(OOcTeTatTt == true){OOcTeTatTt = false;}
      if(CCdVgnUyua == true){CCdVgnUyua = false;}
      if(EUecceRAeg == true){EUecceRAeg = false;}
      if(PLZlbFMHjJ == true){PLZlbFMHjJ = false;}
      if(rolZxSPZUi == true){rolZxSPZUi = false;}
      if(kVedfsjApA == true){kVedfsjApA = false;}
      if(CaOmepbqsb == true){CaOmepbqsb = false;}
      if(bNOlhPiFeK == true){bNOlhPiFeK = false;}
      if(OrfwusgwGi == true){OrfwusgwGi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKXKWKPQMY
{ 
  void pbuOdYoUDb()
  { 
      bool GjGqkwJhrL = false;
      bool hfoNGKuTWz = false;
      bool pERQOcbrxR = false;
      bool nTemNAWMeR = false;
      bool nWdoKHslae = false;
      bool mOWQkCSocH = false;
      bool UQjaWNABzG = false;
      bool mhoELSZcFH = false;
      bool jpQSdZxOCL = false;
      bool hgjWxXmDRx = false;
      bool GqlUqFZRFR = false;
      bool bojUXdzRwx = false;
      bool PlzmYFxRHm = false;
      bool fWKIAsDwaX = false;
      bool AfIjjrxOzS = false;
      bool XUGUgTqyul = false;
      bool HHJRlEebTe = false;
      bool aDpYwjdPDg = false;
      bool IhSnOKQpag = false;
      bool BFAoQrVpxe = false;
      string MLtlVVwieM;
      string UmCKXFyzXX;
      string NbhkLyxXbC;
      string uPrweANolS;
      string FsOrcitUGW;
      string qNBpBkdJaX;
      string YYGbQEuGfW;
      string rINFSUNoHc;
      string EbQFLhOCut;
      string VEONsfllaY;
      string nmoiehzwXf;
      string WoByTxIBQi;
      string prKkBmtzLl;
      string haOinQlgZc;
      string iSeOWgCQtw;
      string XkVriucDhq;
      string nAjkxuaSJC;
      string LaamAWNwOU;
      string jdEPOxFVAs;
      string nhzhoihsQa;
      if(MLtlVVwieM == nmoiehzwXf){GjGqkwJhrL = true;}
      else if(nmoiehzwXf == MLtlVVwieM){GqlUqFZRFR = true;}
      if(UmCKXFyzXX == WoByTxIBQi){hfoNGKuTWz = true;}
      else if(WoByTxIBQi == UmCKXFyzXX){bojUXdzRwx = true;}
      if(NbhkLyxXbC == prKkBmtzLl){pERQOcbrxR = true;}
      else if(prKkBmtzLl == NbhkLyxXbC){PlzmYFxRHm = true;}
      if(uPrweANolS == haOinQlgZc){nTemNAWMeR = true;}
      else if(haOinQlgZc == uPrweANolS){fWKIAsDwaX = true;}
      if(FsOrcitUGW == iSeOWgCQtw){nWdoKHslae = true;}
      else if(iSeOWgCQtw == FsOrcitUGW){AfIjjrxOzS = true;}
      if(qNBpBkdJaX == XkVriucDhq){mOWQkCSocH = true;}
      else if(XkVriucDhq == qNBpBkdJaX){XUGUgTqyul = true;}
      if(YYGbQEuGfW == nAjkxuaSJC){UQjaWNABzG = true;}
      else if(nAjkxuaSJC == YYGbQEuGfW){HHJRlEebTe = true;}
      if(rINFSUNoHc == LaamAWNwOU){mhoELSZcFH = true;}
      if(EbQFLhOCut == jdEPOxFVAs){jpQSdZxOCL = true;}
      if(VEONsfllaY == nhzhoihsQa){hgjWxXmDRx = true;}
      while(LaamAWNwOU == rINFSUNoHc){aDpYwjdPDg = true;}
      while(jdEPOxFVAs == jdEPOxFVAs){IhSnOKQpag = true;}
      while(nhzhoihsQa == nhzhoihsQa){BFAoQrVpxe = true;}
      if(GjGqkwJhrL == true){GjGqkwJhrL = false;}
      if(hfoNGKuTWz == true){hfoNGKuTWz = false;}
      if(pERQOcbrxR == true){pERQOcbrxR = false;}
      if(nTemNAWMeR == true){nTemNAWMeR = false;}
      if(nWdoKHslae == true){nWdoKHslae = false;}
      if(mOWQkCSocH == true){mOWQkCSocH = false;}
      if(UQjaWNABzG == true){UQjaWNABzG = false;}
      if(mhoELSZcFH == true){mhoELSZcFH = false;}
      if(jpQSdZxOCL == true){jpQSdZxOCL = false;}
      if(hgjWxXmDRx == true){hgjWxXmDRx = false;}
      if(GqlUqFZRFR == true){GqlUqFZRFR = false;}
      if(bojUXdzRwx == true){bojUXdzRwx = false;}
      if(PlzmYFxRHm == true){PlzmYFxRHm = false;}
      if(fWKIAsDwaX == true){fWKIAsDwaX = false;}
      if(AfIjjrxOzS == true){AfIjjrxOzS = false;}
      if(XUGUgTqyul == true){XUGUgTqyul = false;}
      if(HHJRlEebTe == true){HHJRlEebTe = false;}
      if(aDpYwjdPDg == true){aDpYwjdPDg = false;}
      if(IhSnOKQpag == true){IhSnOKQpag = false;}
      if(BFAoQrVpxe == true){BFAoQrVpxe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKYYFNYPWV
{ 
  void PGnEGaNauY()
  { 
      bool RAdCHmszFs = false;
      bool PrzWUpWPwp = false;
      bool fTOHGPtmDI = false;
      bool OgfVxnrhos = false;
      bool joYsqUjQJo = false;
      bool rHyEyxlVwr = false;
      bool rFwweiLdYg = false;
      bool xnZDGptUQl = false;
      bool fdcNQGhaWz = false;
      bool CWlxAdscOH = false;
      bool IGqcqDhuxI = false;
      bool DQFJMNbheX = false;
      bool BkGZeaCcDb = false;
      bool xQFIdYmAVM = false;
      bool YmdNwkQbkl = false;
      bool CKyqGWzQyQ = false;
      bool BFrVLlKwfm = false;
      bool aaMSyOHrcs = false;
      bool JZrQZlSOCG = false;
      bool ZVCFLTtHCK = false;
      string YQpDsgPCbB;
      string mOzKLdwguH;
      string bweyrGTOEb;
      string XNKnTIPVGB;
      string cSLAbyTnVO;
      string EnLHRckrKl;
      string MAyAcYDLpD;
      string OaasdJjeWt;
      string mfroWiCCWq;
      string WXKTncULWC;
      string tHxSAdNRdI;
      string rGVQygHIct;
      string WBoyfpQGEA;
      string oXHTAehZos;
      string VjYNzQCtVH;
      string ULicfrSylJ;
      string MHMcSUyBPS;
      string zhSiXlcazP;
      string nWjxfcoemH;
      string MimefOWuud;
      if(YQpDsgPCbB == tHxSAdNRdI){RAdCHmszFs = true;}
      else if(tHxSAdNRdI == YQpDsgPCbB){IGqcqDhuxI = true;}
      if(mOzKLdwguH == rGVQygHIct){PrzWUpWPwp = true;}
      else if(rGVQygHIct == mOzKLdwguH){DQFJMNbheX = true;}
      if(bweyrGTOEb == WBoyfpQGEA){fTOHGPtmDI = true;}
      else if(WBoyfpQGEA == bweyrGTOEb){BkGZeaCcDb = true;}
      if(XNKnTIPVGB == oXHTAehZos){OgfVxnrhos = true;}
      else if(oXHTAehZos == XNKnTIPVGB){xQFIdYmAVM = true;}
      if(cSLAbyTnVO == VjYNzQCtVH){joYsqUjQJo = true;}
      else if(VjYNzQCtVH == cSLAbyTnVO){YmdNwkQbkl = true;}
      if(EnLHRckrKl == ULicfrSylJ){rHyEyxlVwr = true;}
      else if(ULicfrSylJ == EnLHRckrKl){CKyqGWzQyQ = true;}
      if(MAyAcYDLpD == MHMcSUyBPS){rFwweiLdYg = true;}
      else if(MHMcSUyBPS == MAyAcYDLpD){BFrVLlKwfm = true;}
      if(OaasdJjeWt == zhSiXlcazP){xnZDGptUQl = true;}
      if(mfroWiCCWq == nWjxfcoemH){fdcNQGhaWz = true;}
      if(WXKTncULWC == MimefOWuud){CWlxAdscOH = true;}
      while(zhSiXlcazP == OaasdJjeWt){aaMSyOHrcs = true;}
      while(nWjxfcoemH == nWjxfcoemH){JZrQZlSOCG = true;}
      while(MimefOWuud == MimefOWuud){ZVCFLTtHCK = true;}
      if(RAdCHmszFs == true){RAdCHmszFs = false;}
      if(PrzWUpWPwp == true){PrzWUpWPwp = false;}
      if(fTOHGPtmDI == true){fTOHGPtmDI = false;}
      if(OgfVxnrhos == true){OgfVxnrhos = false;}
      if(joYsqUjQJo == true){joYsqUjQJo = false;}
      if(rHyEyxlVwr == true){rHyEyxlVwr = false;}
      if(rFwweiLdYg == true){rFwweiLdYg = false;}
      if(xnZDGptUQl == true){xnZDGptUQl = false;}
      if(fdcNQGhaWz == true){fdcNQGhaWz = false;}
      if(CWlxAdscOH == true){CWlxAdscOH = false;}
      if(IGqcqDhuxI == true){IGqcqDhuxI = false;}
      if(DQFJMNbheX == true){DQFJMNbheX = false;}
      if(BkGZeaCcDb == true){BkGZeaCcDb = false;}
      if(xQFIdYmAVM == true){xQFIdYmAVM = false;}
      if(YmdNwkQbkl == true){YmdNwkQbkl = false;}
      if(CKyqGWzQyQ == true){CKyqGWzQyQ = false;}
      if(BFrVLlKwfm == true){BFrVLlKwfm = false;}
      if(aaMSyOHrcs == true){aaMSyOHrcs = false;}
      if(JZrQZlSOCG == true){JZrQZlSOCG = false;}
      if(ZVCFLTtHCK == true){ZVCFLTtHCK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CESUPQZYQM
{ 
  void qlwXwNnmsw()
  { 
      bool YiRaFMZfZZ = false;
      bool uJiHEldKmn = false;
      bool wBzJAsQlnH = false;
      bool KAekkucTPM = false;
      bool jMlzfXScBp = false;
      bool FAYVgWjHZL = false;
      bool wnrROuexWJ = false;
      bool JJuZEiPzdc = false;
      bool amkyCKaIDO = false;
      bool LVtDQuUUjk = false;
      bool rUGrfwEyRy = false;
      bool HjcwkIDsPE = false;
      bool TVtIxnPqJI = false;
      bool OtOsjGgsRG = false;
      bool FbpFGarxSH = false;
      bool raFfQWaytr = false;
      bool fNoJjMUjLd = false;
      bool bKbJzrenBW = false;
      bool uRYCQmoicN = false;
      bool ehyZZrmgVs = false;
      string wjIqwZcKDZ;
      string OFTgmHunmE;
      string UAympFyFRn;
      string nKpmwNUZNW;
      string srlDLKcRmH;
      string ADSNDukUAp;
      string aXrOkDPgjY;
      string lVaQKcOube;
      string bgRKnkrbiB;
      string cAYWuUAXRH;
      string uwgOUdbBCa;
      string gpsVNtFgZA;
      string LmxiwlxDVo;
      string cpcUjfzDoJ;
      string IpZITlHDIA;
      string PSxRuIyyRi;
      string gYfMypNXkh;
      string uCrQqVMoOJ;
      string dttUZJsLYa;
      string gBkFcjKMJd;
      if(wjIqwZcKDZ == uwgOUdbBCa){YiRaFMZfZZ = true;}
      else if(uwgOUdbBCa == wjIqwZcKDZ){rUGrfwEyRy = true;}
      if(OFTgmHunmE == gpsVNtFgZA){uJiHEldKmn = true;}
      else if(gpsVNtFgZA == OFTgmHunmE){HjcwkIDsPE = true;}
      if(UAympFyFRn == LmxiwlxDVo){wBzJAsQlnH = true;}
      else if(LmxiwlxDVo == UAympFyFRn){TVtIxnPqJI = true;}
      if(nKpmwNUZNW == cpcUjfzDoJ){KAekkucTPM = true;}
      else if(cpcUjfzDoJ == nKpmwNUZNW){OtOsjGgsRG = true;}
      if(srlDLKcRmH == IpZITlHDIA){jMlzfXScBp = true;}
      else if(IpZITlHDIA == srlDLKcRmH){FbpFGarxSH = true;}
      if(ADSNDukUAp == PSxRuIyyRi){FAYVgWjHZL = true;}
      else if(PSxRuIyyRi == ADSNDukUAp){raFfQWaytr = true;}
      if(aXrOkDPgjY == gYfMypNXkh){wnrROuexWJ = true;}
      else if(gYfMypNXkh == aXrOkDPgjY){fNoJjMUjLd = true;}
      if(lVaQKcOube == uCrQqVMoOJ){JJuZEiPzdc = true;}
      if(bgRKnkrbiB == dttUZJsLYa){amkyCKaIDO = true;}
      if(cAYWuUAXRH == gBkFcjKMJd){LVtDQuUUjk = true;}
      while(uCrQqVMoOJ == lVaQKcOube){bKbJzrenBW = true;}
      while(dttUZJsLYa == dttUZJsLYa){uRYCQmoicN = true;}
      while(gBkFcjKMJd == gBkFcjKMJd){ehyZZrmgVs = true;}
      if(YiRaFMZfZZ == true){YiRaFMZfZZ = false;}
      if(uJiHEldKmn == true){uJiHEldKmn = false;}
      if(wBzJAsQlnH == true){wBzJAsQlnH = false;}
      if(KAekkucTPM == true){KAekkucTPM = false;}
      if(jMlzfXScBp == true){jMlzfXScBp = false;}
      if(FAYVgWjHZL == true){FAYVgWjHZL = false;}
      if(wnrROuexWJ == true){wnrROuexWJ = false;}
      if(JJuZEiPzdc == true){JJuZEiPzdc = false;}
      if(amkyCKaIDO == true){amkyCKaIDO = false;}
      if(LVtDQuUUjk == true){LVtDQuUUjk = false;}
      if(rUGrfwEyRy == true){rUGrfwEyRy = false;}
      if(HjcwkIDsPE == true){HjcwkIDsPE = false;}
      if(TVtIxnPqJI == true){TVtIxnPqJI = false;}
      if(OtOsjGgsRG == true){OtOsjGgsRG = false;}
      if(FbpFGarxSH == true){FbpFGarxSH = false;}
      if(raFfQWaytr == true){raFfQWaytr = false;}
      if(fNoJjMUjLd == true){fNoJjMUjLd = false;}
      if(bKbJzrenBW == true){bKbJzrenBW = false;}
      if(uRYCQmoicN == true){uRYCQmoicN = false;}
      if(ehyZZrmgVs == true){ehyZZrmgVs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYFGNOVXPN
{ 
  void GGnBQZrAQV()
  { 
      bool PBjEzCKzun = false;
      bool kSVnchIdpr = false;
      bool cPwiJxyhpS = false;
      bool xEQwWVAmTk = false;
      bool YIGIWREPsy = false;
      bool NbqRwAFAuB = false;
      bool DbJbqgCYRH = false;
      bool gUJFTTImMq = false;
      bool rhorEVMyAW = false;
      bool QArSgwzdRo = false;
      bool PfykRrRlyb = false;
      bool qSmEIUlQWU = false;
      bool UEYtqgcqYW = false;
      bool TeUWaMjEZL = false;
      bool DazXfxMmJM = false;
      bool KhGxULGDtj = false;
      bool PaMbHLxQcw = false;
      bool khqKQsEAOs = false;
      bool TphMLlXXCP = false;
      bool FfJowcNXQT = false;
      string NpChbBfcUp;
      string YRDeXxiyse;
      string EVEfHQWWIS;
      string RdkdVVAYiq;
      string yMuUrDehwQ;
      string oFoCRrlVaK;
      string eJTBYugYJC;
      string xKOCgqZimD;
      string koZqdMohMc;
      string idyYMnrtwx;
      string WGXtTeplVa;
      string RDiWZoicWL;
      string FyMgSSLppr;
      string zflofeRfXz;
      string VCLlKfuayW;
      string FPWkrXsqaB;
      string SzwdblQsqt;
      string XDFWoDmaVl;
      string XjqSmiIBxH;
      string kZEWgWFhKY;
      if(NpChbBfcUp == WGXtTeplVa){PBjEzCKzun = true;}
      else if(WGXtTeplVa == NpChbBfcUp){PfykRrRlyb = true;}
      if(YRDeXxiyse == RDiWZoicWL){kSVnchIdpr = true;}
      else if(RDiWZoicWL == YRDeXxiyse){qSmEIUlQWU = true;}
      if(EVEfHQWWIS == FyMgSSLppr){cPwiJxyhpS = true;}
      else if(FyMgSSLppr == EVEfHQWWIS){UEYtqgcqYW = true;}
      if(RdkdVVAYiq == zflofeRfXz){xEQwWVAmTk = true;}
      else if(zflofeRfXz == RdkdVVAYiq){TeUWaMjEZL = true;}
      if(yMuUrDehwQ == VCLlKfuayW){YIGIWREPsy = true;}
      else if(VCLlKfuayW == yMuUrDehwQ){DazXfxMmJM = true;}
      if(oFoCRrlVaK == FPWkrXsqaB){NbqRwAFAuB = true;}
      else if(FPWkrXsqaB == oFoCRrlVaK){KhGxULGDtj = true;}
      if(eJTBYugYJC == SzwdblQsqt){DbJbqgCYRH = true;}
      else if(SzwdblQsqt == eJTBYugYJC){PaMbHLxQcw = true;}
      if(xKOCgqZimD == XDFWoDmaVl){gUJFTTImMq = true;}
      if(koZqdMohMc == XjqSmiIBxH){rhorEVMyAW = true;}
      if(idyYMnrtwx == kZEWgWFhKY){QArSgwzdRo = true;}
      while(XDFWoDmaVl == xKOCgqZimD){khqKQsEAOs = true;}
      while(XjqSmiIBxH == XjqSmiIBxH){TphMLlXXCP = true;}
      while(kZEWgWFhKY == kZEWgWFhKY){FfJowcNXQT = true;}
      if(PBjEzCKzun == true){PBjEzCKzun = false;}
      if(kSVnchIdpr == true){kSVnchIdpr = false;}
      if(cPwiJxyhpS == true){cPwiJxyhpS = false;}
      if(xEQwWVAmTk == true){xEQwWVAmTk = false;}
      if(YIGIWREPsy == true){YIGIWREPsy = false;}
      if(NbqRwAFAuB == true){NbqRwAFAuB = false;}
      if(DbJbqgCYRH == true){DbJbqgCYRH = false;}
      if(gUJFTTImMq == true){gUJFTTImMq = false;}
      if(rhorEVMyAW == true){rhorEVMyAW = false;}
      if(QArSgwzdRo == true){QArSgwzdRo = false;}
      if(PfykRrRlyb == true){PfykRrRlyb = false;}
      if(qSmEIUlQWU == true){qSmEIUlQWU = false;}
      if(UEYtqgcqYW == true){UEYtqgcqYW = false;}
      if(TeUWaMjEZL == true){TeUWaMjEZL = false;}
      if(DazXfxMmJM == true){DazXfxMmJM = false;}
      if(KhGxULGDtj == true){KhGxULGDtj = false;}
      if(PaMbHLxQcw == true){PaMbHLxQcw = false;}
      if(khqKQsEAOs == true){khqKQsEAOs = false;}
      if(TphMLlXXCP == true){TphMLlXXCP = false;}
      if(FfJowcNXQT == true){FfJowcNXQT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBQXHZJGRC
{ 
  void NGIDDokhgp()
  { 
      bool aKDIqPeGcd = false;
      bool ttAbPRLzGM = false;
      bool WDtMuaBCJZ = false;
      bool WgSkXQiDja = false;
      bool TeZECXIUYH = false;
      bool jVVgNXQpNQ = false;
      bool ObxCGNbPEy = false;
      bool iHOfsqcoKW = false;
      bool RgcBpBLkWz = false;
      bool AroTMrhWyo = false;
      bool wsPaYbGpnW = false;
      bool uafqygyuME = false;
      bool CpsFyqSuTA = false;
      bool JFqVZXQCcN = false;
      bool uUxADYMyUe = false;
      bool tlKsmGAKch = false;
      bool JLWmMojJQa = false;
      bool QuSyJgrsBY = false;
      bool dTZnGWuyiT = false;
      bool XGZtEiyKmO = false;
      string uzolQeLpIs;
      string IWnoPIAoRW;
      string ReyokdxKfM;
      string buNhurVawY;
      string jDzGYwefes;
      string dAVmuQBzAl;
      string hAKuRNIFtX;
      string lZssmOfrQo;
      string zRemhbYZme;
      string qWZJqisDoL;
      string mZlHGEHcAg;
      string kIhLmPVWNp;
      string niSPgPAiCD;
      string UbCFBZfXfd;
      string TwYFshnNWa;
      string NVpzWEGVaq;
      string EXawLIGcKN;
      string jxqiVrJMVy;
      string blMapylDix;
      string SJwnZuUbtk;
      if(uzolQeLpIs == mZlHGEHcAg){aKDIqPeGcd = true;}
      else if(mZlHGEHcAg == uzolQeLpIs){wsPaYbGpnW = true;}
      if(IWnoPIAoRW == kIhLmPVWNp){ttAbPRLzGM = true;}
      else if(kIhLmPVWNp == IWnoPIAoRW){uafqygyuME = true;}
      if(ReyokdxKfM == niSPgPAiCD){WDtMuaBCJZ = true;}
      else if(niSPgPAiCD == ReyokdxKfM){CpsFyqSuTA = true;}
      if(buNhurVawY == UbCFBZfXfd){WgSkXQiDja = true;}
      else if(UbCFBZfXfd == buNhurVawY){JFqVZXQCcN = true;}
      if(jDzGYwefes == TwYFshnNWa){TeZECXIUYH = true;}
      else if(TwYFshnNWa == jDzGYwefes){uUxADYMyUe = true;}
      if(dAVmuQBzAl == NVpzWEGVaq){jVVgNXQpNQ = true;}
      else if(NVpzWEGVaq == dAVmuQBzAl){tlKsmGAKch = true;}
      if(hAKuRNIFtX == EXawLIGcKN){ObxCGNbPEy = true;}
      else if(EXawLIGcKN == hAKuRNIFtX){JLWmMojJQa = true;}
      if(lZssmOfrQo == jxqiVrJMVy){iHOfsqcoKW = true;}
      if(zRemhbYZme == blMapylDix){RgcBpBLkWz = true;}
      if(qWZJqisDoL == SJwnZuUbtk){AroTMrhWyo = true;}
      while(jxqiVrJMVy == lZssmOfrQo){QuSyJgrsBY = true;}
      while(blMapylDix == blMapylDix){dTZnGWuyiT = true;}
      while(SJwnZuUbtk == SJwnZuUbtk){XGZtEiyKmO = true;}
      if(aKDIqPeGcd == true){aKDIqPeGcd = false;}
      if(ttAbPRLzGM == true){ttAbPRLzGM = false;}
      if(WDtMuaBCJZ == true){WDtMuaBCJZ = false;}
      if(WgSkXQiDja == true){WgSkXQiDja = false;}
      if(TeZECXIUYH == true){TeZECXIUYH = false;}
      if(jVVgNXQpNQ == true){jVVgNXQpNQ = false;}
      if(ObxCGNbPEy == true){ObxCGNbPEy = false;}
      if(iHOfsqcoKW == true){iHOfsqcoKW = false;}
      if(RgcBpBLkWz == true){RgcBpBLkWz = false;}
      if(AroTMrhWyo == true){AroTMrhWyo = false;}
      if(wsPaYbGpnW == true){wsPaYbGpnW = false;}
      if(uafqygyuME == true){uafqygyuME = false;}
      if(CpsFyqSuTA == true){CpsFyqSuTA = false;}
      if(JFqVZXQCcN == true){JFqVZXQCcN = false;}
      if(uUxADYMyUe == true){uUxADYMyUe = false;}
      if(tlKsmGAKch == true){tlKsmGAKch = false;}
      if(JLWmMojJQa == true){JLWmMojJQa = false;}
      if(QuSyJgrsBY == true){QuSyJgrsBY = false;}
      if(dTZnGWuyiT == true){dTZnGWuyiT = false;}
      if(XGZtEiyKmO == true){XGZtEiyKmO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRYHQSULFS
{ 
  void ZOxouuxcZW()
  { 
      bool fQyuTRAeiu = false;
      bool yHnGAicJlM = false;
      bool bGqweDVPoc = false;
      bool ICJxVFaUuN = false;
      bool DWRWfDwymi = false;
      bool rJVFaYZCPP = false;
      bool ukpGmwxqku = false;
      bool HHOYIEoTQb = false;
      bool HXbFkyfDVw = false;
      bool fYEeRSgLii = false;
      bool FFNrajtxwV = false;
      bool jFknIXIkUn = false;
      bool PtUnOiCjGp = false;
      bool XdjgVBKieB = false;
      bool EiHzLZmQWt = false;
      bool JuptSLjZdq = false;
      bool gKpGyGUESG = false;
      bool MZGTjglUbn = false;
      bool wlMMfbmoOJ = false;
      bool RjFmTsrBBF = false;
      string VQRbOAhXwE;
      string oPaIShcOau;
      string sswidtseaf;
      string fgOJbyJmpe;
      string lQjSAuJzSs;
      string xUryBbUiyU;
      string HCwQXIARfT;
      string YoYuIcIdhh;
      string ksMgiLnPHA;
      string daoVXiTTtr;
      string tqTyUIwwpY;
      string SpAPiOpPgM;
      string TjJfoxzCXY;
      string IoipnsYNLa;
      string OrZhgmaZlJ;
      string sElhXJhnIX;
      string IsYRQdHJap;
      string obDGybKazC;
      string WZQOeECBSe;
      string KkFnRUTIRC;
      if(VQRbOAhXwE == tqTyUIwwpY){fQyuTRAeiu = true;}
      else if(tqTyUIwwpY == VQRbOAhXwE){FFNrajtxwV = true;}
      if(oPaIShcOau == SpAPiOpPgM){yHnGAicJlM = true;}
      else if(SpAPiOpPgM == oPaIShcOau){jFknIXIkUn = true;}
      if(sswidtseaf == TjJfoxzCXY){bGqweDVPoc = true;}
      else if(TjJfoxzCXY == sswidtseaf){PtUnOiCjGp = true;}
      if(fgOJbyJmpe == IoipnsYNLa){ICJxVFaUuN = true;}
      else if(IoipnsYNLa == fgOJbyJmpe){XdjgVBKieB = true;}
      if(lQjSAuJzSs == OrZhgmaZlJ){DWRWfDwymi = true;}
      else if(OrZhgmaZlJ == lQjSAuJzSs){EiHzLZmQWt = true;}
      if(xUryBbUiyU == sElhXJhnIX){rJVFaYZCPP = true;}
      else if(sElhXJhnIX == xUryBbUiyU){JuptSLjZdq = true;}
      if(HCwQXIARfT == IsYRQdHJap){ukpGmwxqku = true;}
      else if(IsYRQdHJap == HCwQXIARfT){gKpGyGUESG = true;}
      if(YoYuIcIdhh == obDGybKazC){HHOYIEoTQb = true;}
      if(ksMgiLnPHA == WZQOeECBSe){HXbFkyfDVw = true;}
      if(daoVXiTTtr == KkFnRUTIRC){fYEeRSgLii = true;}
      while(obDGybKazC == YoYuIcIdhh){MZGTjglUbn = true;}
      while(WZQOeECBSe == WZQOeECBSe){wlMMfbmoOJ = true;}
      while(KkFnRUTIRC == KkFnRUTIRC){RjFmTsrBBF = true;}
      if(fQyuTRAeiu == true){fQyuTRAeiu = false;}
      if(yHnGAicJlM == true){yHnGAicJlM = false;}
      if(bGqweDVPoc == true){bGqweDVPoc = false;}
      if(ICJxVFaUuN == true){ICJxVFaUuN = false;}
      if(DWRWfDwymi == true){DWRWfDwymi = false;}
      if(rJVFaYZCPP == true){rJVFaYZCPP = false;}
      if(ukpGmwxqku == true){ukpGmwxqku = false;}
      if(HHOYIEoTQb == true){HHOYIEoTQb = false;}
      if(HXbFkyfDVw == true){HXbFkyfDVw = false;}
      if(fYEeRSgLii == true){fYEeRSgLii = false;}
      if(FFNrajtxwV == true){FFNrajtxwV = false;}
      if(jFknIXIkUn == true){jFknIXIkUn = false;}
      if(PtUnOiCjGp == true){PtUnOiCjGp = false;}
      if(XdjgVBKieB == true){XdjgVBKieB = false;}
      if(EiHzLZmQWt == true){EiHzLZmQWt = false;}
      if(JuptSLjZdq == true){JuptSLjZdq = false;}
      if(gKpGyGUESG == true){gKpGyGUESG = false;}
      if(MZGTjglUbn == true){MZGTjglUbn = false;}
      if(wlMMfbmoOJ == true){wlMMfbmoOJ = false;}
      if(RjFmTsrBBF == true){RjFmTsrBBF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDNIZSKDMR
{ 
  void KiAXpsXGON()
  { 
      bool TgiDsfzrnB = false;
      bool tPZjpXMyJp = false;
      bool HsxhmkCKkG = false;
      bool WCqyUktjOo = false;
      bool YjaqfNCUNs = false;
      bool EhZGOZjBPH = false;
      bool cnHgdqXaPE = false;
      bool cbjTRWRFBZ = false;
      bool ihwqBnckit = false;
      bool AsUGLjctNo = false;
      bool oaEJQcyFnq = false;
      bool IdzoYurQfo = false;
      bool OmqUDjHdHh = false;
      bool tXrMkIcmaY = false;
      bool pWwqlWsehQ = false;
      bool qLOXaBijFf = false;
      bool VTxFxjkmEP = false;
      bool RFpGyqpAig = false;
      bool pbwqqiJUki = false;
      bool YshtDVZptB = false;
      string TShcmBrwNf;
      string octLDArfiP;
      string yVCwYBSlKy;
      string MmZiPaxMEa;
      string fZfWAjPVRA;
      string EkdWXyPkEk;
      string hGkOTBDKub;
      string CfbHiYoewn;
      string lxTKsbJCKR;
      string LMISrZnQDy;
      string gEZoyYJVnz;
      string JjoPyklaVq;
      string rAAdQpWIOI;
      string kXbyHhXdMT;
      string SnOLIbXrUH;
      string mNuMFfEuYI;
      string CAGeOkIpIQ;
      string NHOCYElnVn;
      string RdnHUXcOra;
      string cbFERRgixW;
      if(TShcmBrwNf == gEZoyYJVnz){TgiDsfzrnB = true;}
      else if(gEZoyYJVnz == TShcmBrwNf){oaEJQcyFnq = true;}
      if(octLDArfiP == JjoPyklaVq){tPZjpXMyJp = true;}
      else if(JjoPyklaVq == octLDArfiP){IdzoYurQfo = true;}
      if(yVCwYBSlKy == rAAdQpWIOI){HsxhmkCKkG = true;}
      else if(rAAdQpWIOI == yVCwYBSlKy){OmqUDjHdHh = true;}
      if(MmZiPaxMEa == kXbyHhXdMT){WCqyUktjOo = true;}
      else if(kXbyHhXdMT == MmZiPaxMEa){tXrMkIcmaY = true;}
      if(fZfWAjPVRA == SnOLIbXrUH){YjaqfNCUNs = true;}
      else if(SnOLIbXrUH == fZfWAjPVRA){pWwqlWsehQ = true;}
      if(EkdWXyPkEk == mNuMFfEuYI){EhZGOZjBPH = true;}
      else if(mNuMFfEuYI == EkdWXyPkEk){qLOXaBijFf = true;}
      if(hGkOTBDKub == CAGeOkIpIQ){cnHgdqXaPE = true;}
      else if(CAGeOkIpIQ == hGkOTBDKub){VTxFxjkmEP = true;}
      if(CfbHiYoewn == NHOCYElnVn){cbjTRWRFBZ = true;}
      if(lxTKsbJCKR == RdnHUXcOra){ihwqBnckit = true;}
      if(LMISrZnQDy == cbFERRgixW){AsUGLjctNo = true;}
      while(NHOCYElnVn == CfbHiYoewn){RFpGyqpAig = true;}
      while(RdnHUXcOra == RdnHUXcOra){pbwqqiJUki = true;}
      while(cbFERRgixW == cbFERRgixW){YshtDVZptB = true;}
      if(TgiDsfzrnB == true){TgiDsfzrnB = false;}
      if(tPZjpXMyJp == true){tPZjpXMyJp = false;}
      if(HsxhmkCKkG == true){HsxhmkCKkG = false;}
      if(WCqyUktjOo == true){WCqyUktjOo = false;}
      if(YjaqfNCUNs == true){YjaqfNCUNs = false;}
      if(EhZGOZjBPH == true){EhZGOZjBPH = false;}
      if(cnHgdqXaPE == true){cnHgdqXaPE = false;}
      if(cbjTRWRFBZ == true){cbjTRWRFBZ = false;}
      if(ihwqBnckit == true){ihwqBnckit = false;}
      if(AsUGLjctNo == true){AsUGLjctNo = false;}
      if(oaEJQcyFnq == true){oaEJQcyFnq = false;}
      if(IdzoYurQfo == true){IdzoYurQfo = false;}
      if(OmqUDjHdHh == true){OmqUDjHdHh = false;}
      if(tXrMkIcmaY == true){tXrMkIcmaY = false;}
      if(pWwqlWsehQ == true){pWwqlWsehQ = false;}
      if(qLOXaBijFf == true){qLOXaBijFf = false;}
      if(VTxFxjkmEP == true){VTxFxjkmEP = false;}
      if(RFpGyqpAig == true){RFpGyqpAig = false;}
      if(pbwqqiJUki == true){pbwqqiJUki = false;}
      if(YshtDVZptB == true){YshtDVZptB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCZSEQWCVA
{ 
  void SCUugURfGc()
  { 
      bool jDsqHoWQJq = false;
      bool jMlMGwwgct = false;
      bool EHBIaAUQZw = false;
      bool EVXoXxhZYL = false;
      bool MTFlpLqWRy = false;
      bool FohuMbBjPH = false;
      bool UGpNlOnxnI = false;
      bool OVIRhjBPSO = false;
      bool JxzbpPncbw = false;
      bool wxJRpFcrAb = false;
      bool XsiJjifPMb = false;
      bool ZlRByXHOWV = false;
      bool ZKUrLQLqab = false;
      bool HJPpqPOoqG = false;
      bool jXPzVKfITS = false;
      bool yOVdBMXqxS = false;
      bool XonjUQWaJh = false;
      bool IRWPlBtVVB = false;
      bool kDWIdrnknd = false;
      bool qWrYitifdE = false;
      string aBlYxbtucA;
      string bZUBKEhrJC;
      string tQMjLqDtFo;
      string CymsZqLUuH;
      string DTQSIcjeEj;
      string qRhXzKnCNF;
      string XzonxcmbaS;
      string sNwByZzsai;
      string HYpVyjQPsP;
      string CJHojDecVe;
      string pIDkqdUfYZ;
      string KuadyyJTpN;
      string MXhLPiFHRu;
      string uWXwsyVEeT;
      string OkpTFHhdpk;
      string tLlHSRZrUH;
      string XNOddnXejz;
      string cEnVybgNFI;
      string BbQgAijPca;
      string YcjXuBWLoQ;
      if(aBlYxbtucA == pIDkqdUfYZ){jDsqHoWQJq = true;}
      else if(pIDkqdUfYZ == aBlYxbtucA){XsiJjifPMb = true;}
      if(bZUBKEhrJC == KuadyyJTpN){jMlMGwwgct = true;}
      else if(KuadyyJTpN == bZUBKEhrJC){ZlRByXHOWV = true;}
      if(tQMjLqDtFo == MXhLPiFHRu){EHBIaAUQZw = true;}
      else if(MXhLPiFHRu == tQMjLqDtFo){ZKUrLQLqab = true;}
      if(CymsZqLUuH == uWXwsyVEeT){EVXoXxhZYL = true;}
      else if(uWXwsyVEeT == CymsZqLUuH){HJPpqPOoqG = true;}
      if(DTQSIcjeEj == OkpTFHhdpk){MTFlpLqWRy = true;}
      else if(OkpTFHhdpk == DTQSIcjeEj){jXPzVKfITS = true;}
      if(qRhXzKnCNF == tLlHSRZrUH){FohuMbBjPH = true;}
      else if(tLlHSRZrUH == qRhXzKnCNF){yOVdBMXqxS = true;}
      if(XzonxcmbaS == XNOddnXejz){UGpNlOnxnI = true;}
      else if(XNOddnXejz == XzonxcmbaS){XonjUQWaJh = true;}
      if(sNwByZzsai == cEnVybgNFI){OVIRhjBPSO = true;}
      if(HYpVyjQPsP == BbQgAijPca){JxzbpPncbw = true;}
      if(CJHojDecVe == YcjXuBWLoQ){wxJRpFcrAb = true;}
      while(cEnVybgNFI == sNwByZzsai){IRWPlBtVVB = true;}
      while(BbQgAijPca == BbQgAijPca){kDWIdrnknd = true;}
      while(YcjXuBWLoQ == YcjXuBWLoQ){qWrYitifdE = true;}
      if(jDsqHoWQJq == true){jDsqHoWQJq = false;}
      if(jMlMGwwgct == true){jMlMGwwgct = false;}
      if(EHBIaAUQZw == true){EHBIaAUQZw = false;}
      if(EVXoXxhZYL == true){EVXoXxhZYL = false;}
      if(MTFlpLqWRy == true){MTFlpLqWRy = false;}
      if(FohuMbBjPH == true){FohuMbBjPH = false;}
      if(UGpNlOnxnI == true){UGpNlOnxnI = false;}
      if(OVIRhjBPSO == true){OVIRhjBPSO = false;}
      if(JxzbpPncbw == true){JxzbpPncbw = false;}
      if(wxJRpFcrAb == true){wxJRpFcrAb = false;}
      if(XsiJjifPMb == true){XsiJjifPMb = false;}
      if(ZlRByXHOWV == true){ZlRByXHOWV = false;}
      if(ZKUrLQLqab == true){ZKUrLQLqab = false;}
      if(HJPpqPOoqG == true){HJPpqPOoqG = false;}
      if(jXPzVKfITS == true){jXPzVKfITS = false;}
      if(yOVdBMXqxS == true){yOVdBMXqxS = false;}
      if(XonjUQWaJh == true){XonjUQWaJh = false;}
      if(IRWPlBtVVB == true){IRWPlBtVVB = false;}
      if(kDWIdrnknd == true){kDWIdrnknd = false;}
      if(qWrYitifdE == true){qWrYitifdE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITSKNWJGNU
{ 
  void CtGbgqiexK()
  { 
      bool lKBmROscSr = false;
      bool NNlBQeyaxc = false;
      bool IlBHKncNyX = false;
      bool PCiXcHcpTM = false;
      bool wFOXjwyWpM = false;
      bool lRnwjzJtbc = false;
      bool ledtbLeNYJ = false;
      bool CHGkfDXcWO = false;
      bool oGXllyNlnc = false;
      bool yhNqaRaUwY = false;
      bool QjxgJdLDPf = false;
      bool bfWMmeHrHd = false;
      bool xrYwKTsPJO = false;
      bool bDfyyFJqbH = false;
      bool mKVHARLADu = false;
      bool JiMSaYLBVo = false;
      bool jusBEYzXOh = false;
      bool VQPAqlVQus = false;
      bool IsLNEspNWY = false;
      bool sHVmWqQUDb = false;
      string fSjClpfcbX;
      string fcYbNoXEtb;
      string YSoPojhOBm;
      string fTyLsLhZKM;
      string ZyCleiimmj;
      string qHWTxMdUMB;
      string HRanrMeNhC;
      string HxtgBaQCjF;
      string BtaRuYwdNf;
      string gMNIEIWNtR;
      string EUFkcsMoSW;
      string ubjGANqJsT;
      string QAzBUtjkcs;
      string DDHSBfnooB;
      string LGLqjFbGIq;
      string QNUaBDVDQh;
      string JaMZSrTRFU;
      string YBTqIJoHQO;
      string RdclbpigQy;
      string JkYGrjslYr;
      if(fSjClpfcbX == EUFkcsMoSW){lKBmROscSr = true;}
      else if(EUFkcsMoSW == fSjClpfcbX){QjxgJdLDPf = true;}
      if(fcYbNoXEtb == ubjGANqJsT){NNlBQeyaxc = true;}
      else if(ubjGANqJsT == fcYbNoXEtb){bfWMmeHrHd = true;}
      if(YSoPojhOBm == QAzBUtjkcs){IlBHKncNyX = true;}
      else if(QAzBUtjkcs == YSoPojhOBm){xrYwKTsPJO = true;}
      if(fTyLsLhZKM == DDHSBfnooB){PCiXcHcpTM = true;}
      else if(DDHSBfnooB == fTyLsLhZKM){bDfyyFJqbH = true;}
      if(ZyCleiimmj == LGLqjFbGIq){wFOXjwyWpM = true;}
      else if(LGLqjFbGIq == ZyCleiimmj){mKVHARLADu = true;}
      if(qHWTxMdUMB == QNUaBDVDQh){lRnwjzJtbc = true;}
      else if(QNUaBDVDQh == qHWTxMdUMB){JiMSaYLBVo = true;}
      if(HRanrMeNhC == JaMZSrTRFU){ledtbLeNYJ = true;}
      else if(JaMZSrTRFU == HRanrMeNhC){jusBEYzXOh = true;}
      if(HxtgBaQCjF == YBTqIJoHQO){CHGkfDXcWO = true;}
      if(BtaRuYwdNf == RdclbpigQy){oGXllyNlnc = true;}
      if(gMNIEIWNtR == JkYGrjslYr){yhNqaRaUwY = true;}
      while(YBTqIJoHQO == HxtgBaQCjF){VQPAqlVQus = true;}
      while(RdclbpigQy == RdclbpigQy){IsLNEspNWY = true;}
      while(JkYGrjslYr == JkYGrjslYr){sHVmWqQUDb = true;}
      if(lKBmROscSr == true){lKBmROscSr = false;}
      if(NNlBQeyaxc == true){NNlBQeyaxc = false;}
      if(IlBHKncNyX == true){IlBHKncNyX = false;}
      if(PCiXcHcpTM == true){PCiXcHcpTM = false;}
      if(wFOXjwyWpM == true){wFOXjwyWpM = false;}
      if(lRnwjzJtbc == true){lRnwjzJtbc = false;}
      if(ledtbLeNYJ == true){ledtbLeNYJ = false;}
      if(CHGkfDXcWO == true){CHGkfDXcWO = false;}
      if(oGXllyNlnc == true){oGXllyNlnc = false;}
      if(yhNqaRaUwY == true){yhNqaRaUwY = false;}
      if(QjxgJdLDPf == true){QjxgJdLDPf = false;}
      if(bfWMmeHrHd == true){bfWMmeHrHd = false;}
      if(xrYwKTsPJO == true){xrYwKTsPJO = false;}
      if(bDfyyFJqbH == true){bDfyyFJqbH = false;}
      if(mKVHARLADu == true){mKVHARLADu = false;}
      if(JiMSaYLBVo == true){JiMSaYLBVo = false;}
      if(jusBEYzXOh == true){jusBEYzXOh = false;}
      if(VQPAqlVQus == true){VQPAqlVQus = false;}
      if(IsLNEspNWY == true){IsLNEspNWY = false;}
      if(sHVmWqQUDb == true){sHVmWqQUDb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJLMIDAJFK
{ 
  void EZdVJdoOjV()
  { 
      bool yUyVlTkrbX = false;
      bool CUuxQJwHMf = false;
      bool xwjpwubArl = false;
      bool fzQiUGKIZT = false;
      bool UWUGkPsiqz = false;
      bool gYLnoBkHYq = false;
      bool qkAprDEMcJ = false;
      bool ymgrKabdEg = false;
      bool BsIsEHmbsS = false;
      bool VCjibjWeOh = false;
      bool LgFgAsqSdO = false;
      bool ZGDqoybGkj = false;
      bool PcSJmuDxQa = false;
      bool EwOWVUmarL = false;
      bool PTydsPzrtc = false;
      bool IPsdRiNutF = false;
      bool psCCKcqgVU = false;
      bool LAOZTwdnQX = false;
      bool uLDnSnDkEl = false;
      bool GqgmUVRuTP = false;
      string CLbLmSHxqD;
      string UhRRfjxzsL;
      string SDigkYgdil;
      string aCzgVzJspy;
      string MPZlQCikGe;
      string HQyNnzctZN;
      string ldNFcRhkuf;
      string aEIuyCcwPi;
      string owXEdKElrW;
      string WOSbMiCUJz;
      string UyoZEDHDOl;
      string VfeqYpGIaS;
      string NurXJLkgiP;
      string zImPNqGxAa;
      string DAXGBpjbDV;
      string bssqkZGRQr;
      string SZUzlNrOdh;
      string jIIAOMXkWS;
      string bJdMmGPwem;
      string kngHIcfXUm;
      if(CLbLmSHxqD == UyoZEDHDOl){yUyVlTkrbX = true;}
      else if(UyoZEDHDOl == CLbLmSHxqD){LgFgAsqSdO = true;}
      if(UhRRfjxzsL == VfeqYpGIaS){CUuxQJwHMf = true;}
      else if(VfeqYpGIaS == UhRRfjxzsL){ZGDqoybGkj = true;}
      if(SDigkYgdil == NurXJLkgiP){xwjpwubArl = true;}
      else if(NurXJLkgiP == SDigkYgdil){PcSJmuDxQa = true;}
      if(aCzgVzJspy == zImPNqGxAa){fzQiUGKIZT = true;}
      else if(zImPNqGxAa == aCzgVzJspy){EwOWVUmarL = true;}
      if(MPZlQCikGe == DAXGBpjbDV){UWUGkPsiqz = true;}
      else if(DAXGBpjbDV == MPZlQCikGe){PTydsPzrtc = true;}
      if(HQyNnzctZN == bssqkZGRQr){gYLnoBkHYq = true;}
      else if(bssqkZGRQr == HQyNnzctZN){IPsdRiNutF = true;}
      if(ldNFcRhkuf == SZUzlNrOdh){qkAprDEMcJ = true;}
      else if(SZUzlNrOdh == ldNFcRhkuf){psCCKcqgVU = true;}
      if(aEIuyCcwPi == jIIAOMXkWS){ymgrKabdEg = true;}
      if(owXEdKElrW == bJdMmGPwem){BsIsEHmbsS = true;}
      if(WOSbMiCUJz == kngHIcfXUm){VCjibjWeOh = true;}
      while(jIIAOMXkWS == aEIuyCcwPi){LAOZTwdnQX = true;}
      while(bJdMmGPwem == bJdMmGPwem){uLDnSnDkEl = true;}
      while(kngHIcfXUm == kngHIcfXUm){GqgmUVRuTP = true;}
      if(yUyVlTkrbX == true){yUyVlTkrbX = false;}
      if(CUuxQJwHMf == true){CUuxQJwHMf = false;}
      if(xwjpwubArl == true){xwjpwubArl = false;}
      if(fzQiUGKIZT == true){fzQiUGKIZT = false;}
      if(UWUGkPsiqz == true){UWUGkPsiqz = false;}
      if(gYLnoBkHYq == true){gYLnoBkHYq = false;}
      if(qkAprDEMcJ == true){qkAprDEMcJ = false;}
      if(ymgrKabdEg == true){ymgrKabdEg = false;}
      if(BsIsEHmbsS == true){BsIsEHmbsS = false;}
      if(VCjibjWeOh == true){VCjibjWeOh = false;}
      if(LgFgAsqSdO == true){LgFgAsqSdO = false;}
      if(ZGDqoybGkj == true){ZGDqoybGkj = false;}
      if(PcSJmuDxQa == true){PcSJmuDxQa = false;}
      if(EwOWVUmarL == true){EwOWVUmarL = false;}
      if(PTydsPzrtc == true){PTydsPzrtc = false;}
      if(IPsdRiNutF == true){IPsdRiNutF = false;}
      if(psCCKcqgVU == true){psCCKcqgVU = false;}
      if(LAOZTwdnQX == true){LAOZTwdnQX = false;}
      if(uLDnSnDkEl == true){uLDnSnDkEl = false;}
      if(GqgmUVRuTP == true){GqgmUVRuTP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMQIWEBSTG
{ 
  void cmTIMDaeQx()
  { 
      bool eTrWwkDuNr = false;
      bool PVuHGKKmBN = false;
      bool qVaDasUkDk = false;
      bool mdrCtKAuKm = false;
      bool KwuMBIneZw = false;
      bool ZmhGGIsouD = false;
      bool QSrcEldrMu = false;
      bool KOcOCuZNBR = false;
      bool EpLGLzwkul = false;
      bool RLAGWqESIO = false;
      bool ewSdlKKSDL = false;
      bool hemczZHkRE = false;
      bool prwadzOVrL = false;
      bool pHFmmHXgTA = false;
      bool ochjDlYWHw = false;
      bool jTBDYmzqAm = false;
      bool unarUaZApq = false;
      bool CaQQPMJLWq = false;
      bool arNuaWGCNz = false;
      bool IffgEACpPc = false;
      string zpDgVGlfpa;
      string EKLXrzOHLU;
      string CpDNXBnYQD;
      string DdizYWejPz;
      string hROqPbAdmj;
      string kQkfuIloJU;
      string SMOmWaaLzV;
      string UeqLmkaMyu;
      string BKkgRmsDEP;
      string kpZugUCbTn;
      string BneRPGYYsJ;
      string hZpOSIahVj;
      string hXGikdEueR;
      string hysKtMfTQK;
      string OTKuhKzLcY;
      string sUGiFchugk;
      string CdsaajffTG;
      string cHQKVNNLAZ;
      string erSGYNrJEQ;
      string ejlfHkaiTy;
      if(zpDgVGlfpa == BneRPGYYsJ){eTrWwkDuNr = true;}
      else if(BneRPGYYsJ == zpDgVGlfpa){ewSdlKKSDL = true;}
      if(EKLXrzOHLU == hZpOSIahVj){PVuHGKKmBN = true;}
      else if(hZpOSIahVj == EKLXrzOHLU){hemczZHkRE = true;}
      if(CpDNXBnYQD == hXGikdEueR){qVaDasUkDk = true;}
      else if(hXGikdEueR == CpDNXBnYQD){prwadzOVrL = true;}
      if(DdizYWejPz == hysKtMfTQK){mdrCtKAuKm = true;}
      else if(hysKtMfTQK == DdizYWejPz){pHFmmHXgTA = true;}
      if(hROqPbAdmj == OTKuhKzLcY){KwuMBIneZw = true;}
      else if(OTKuhKzLcY == hROqPbAdmj){ochjDlYWHw = true;}
      if(kQkfuIloJU == sUGiFchugk){ZmhGGIsouD = true;}
      else if(sUGiFchugk == kQkfuIloJU){jTBDYmzqAm = true;}
      if(SMOmWaaLzV == CdsaajffTG){QSrcEldrMu = true;}
      else if(CdsaajffTG == SMOmWaaLzV){unarUaZApq = true;}
      if(UeqLmkaMyu == cHQKVNNLAZ){KOcOCuZNBR = true;}
      if(BKkgRmsDEP == erSGYNrJEQ){EpLGLzwkul = true;}
      if(kpZugUCbTn == ejlfHkaiTy){RLAGWqESIO = true;}
      while(cHQKVNNLAZ == UeqLmkaMyu){CaQQPMJLWq = true;}
      while(erSGYNrJEQ == erSGYNrJEQ){arNuaWGCNz = true;}
      while(ejlfHkaiTy == ejlfHkaiTy){IffgEACpPc = true;}
      if(eTrWwkDuNr == true){eTrWwkDuNr = false;}
      if(PVuHGKKmBN == true){PVuHGKKmBN = false;}
      if(qVaDasUkDk == true){qVaDasUkDk = false;}
      if(mdrCtKAuKm == true){mdrCtKAuKm = false;}
      if(KwuMBIneZw == true){KwuMBIneZw = false;}
      if(ZmhGGIsouD == true){ZmhGGIsouD = false;}
      if(QSrcEldrMu == true){QSrcEldrMu = false;}
      if(KOcOCuZNBR == true){KOcOCuZNBR = false;}
      if(EpLGLzwkul == true){EpLGLzwkul = false;}
      if(RLAGWqESIO == true){RLAGWqESIO = false;}
      if(ewSdlKKSDL == true){ewSdlKKSDL = false;}
      if(hemczZHkRE == true){hemczZHkRE = false;}
      if(prwadzOVrL == true){prwadzOVrL = false;}
      if(pHFmmHXgTA == true){pHFmmHXgTA = false;}
      if(ochjDlYWHw == true){ochjDlYWHw = false;}
      if(jTBDYmzqAm == true){jTBDYmzqAm = false;}
      if(unarUaZApq == true){unarUaZApq = false;}
      if(CaQQPMJLWq == true){CaQQPMJLWq = false;}
      if(arNuaWGCNz == true){arNuaWGCNz = false;}
      if(IffgEACpPc == true){IffgEACpPc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WICKEMDPJO
{ 
  void GTMETMsKfZ()
  { 
      bool nYiplIjEws = false;
      bool uCiGcusSgh = false;
      bool CHCjFXcNaT = false;
      bool FmcKpFckxe = false;
      bool ReikGchtWI = false;
      bool wXSZzgVzkN = false;
      bool fWdcmHYXQW = false;
      bool SIUCQWXRdb = false;
      bool phpRXhUDLI = false;
      bool jczjzuBGyy = false;
      bool EJcApmDPJb = false;
      bool JEVIXxfLFE = false;
      bool mVMImoIkDV = false;
      bool VRSeXfEpbj = false;
      bool eEtizeHpMB = false;
      bool OpAsLhxUMA = false;
      bool eRMmGqkpkq = false;
      bool rpiVZhbdIH = false;
      bool gRXBHfQZSp = false;
      bool ijcaFMrGcH = false;
      string wfmCIXbIHy;
      string OZmfzDWJph;
      string ICriAPGflR;
      string sOxflpKuYx;
      string BpNegVbsBk;
      string QJGdCsmDBr;
      string RwWoEzcHtJ;
      string rajrgSoMBd;
      string nNeAAjIScr;
      string CHsffFTXZg;
      string sTyqroYOxj;
      string DZBXEERVoU;
      string qJeBGkhDLb;
      string zRlUkTOmHK;
      string LtVsnbFVbb;
      string mxhFpinwkH;
      string HVCVjlnglk;
      string peNdIxnlNd;
      string eMbjnBifdB;
      string eRBADoqAIC;
      if(wfmCIXbIHy == sTyqroYOxj){nYiplIjEws = true;}
      else if(sTyqroYOxj == wfmCIXbIHy){EJcApmDPJb = true;}
      if(OZmfzDWJph == DZBXEERVoU){uCiGcusSgh = true;}
      else if(DZBXEERVoU == OZmfzDWJph){JEVIXxfLFE = true;}
      if(ICriAPGflR == qJeBGkhDLb){CHCjFXcNaT = true;}
      else if(qJeBGkhDLb == ICriAPGflR){mVMImoIkDV = true;}
      if(sOxflpKuYx == zRlUkTOmHK){FmcKpFckxe = true;}
      else if(zRlUkTOmHK == sOxflpKuYx){VRSeXfEpbj = true;}
      if(BpNegVbsBk == LtVsnbFVbb){ReikGchtWI = true;}
      else if(LtVsnbFVbb == BpNegVbsBk){eEtizeHpMB = true;}
      if(QJGdCsmDBr == mxhFpinwkH){wXSZzgVzkN = true;}
      else if(mxhFpinwkH == QJGdCsmDBr){OpAsLhxUMA = true;}
      if(RwWoEzcHtJ == HVCVjlnglk){fWdcmHYXQW = true;}
      else if(HVCVjlnglk == RwWoEzcHtJ){eRMmGqkpkq = true;}
      if(rajrgSoMBd == peNdIxnlNd){SIUCQWXRdb = true;}
      if(nNeAAjIScr == eMbjnBifdB){phpRXhUDLI = true;}
      if(CHsffFTXZg == eRBADoqAIC){jczjzuBGyy = true;}
      while(peNdIxnlNd == rajrgSoMBd){rpiVZhbdIH = true;}
      while(eMbjnBifdB == eMbjnBifdB){gRXBHfQZSp = true;}
      while(eRBADoqAIC == eRBADoqAIC){ijcaFMrGcH = true;}
      if(nYiplIjEws == true){nYiplIjEws = false;}
      if(uCiGcusSgh == true){uCiGcusSgh = false;}
      if(CHCjFXcNaT == true){CHCjFXcNaT = false;}
      if(FmcKpFckxe == true){FmcKpFckxe = false;}
      if(ReikGchtWI == true){ReikGchtWI = false;}
      if(wXSZzgVzkN == true){wXSZzgVzkN = false;}
      if(fWdcmHYXQW == true){fWdcmHYXQW = false;}
      if(SIUCQWXRdb == true){SIUCQWXRdb = false;}
      if(phpRXhUDLI == true){phpRXhUDLI = false;}
      if(jczjzuBGyy == true){jczjzuBGyy = false;}
      if(EJcApmDPJb == true){EJcApmDPJb = false;}
      if(JEVIXxfLFE == true){JEVIXxfLFE = false;}
      if(mVMImoIkDV == true){mVMImoIkDV = false;}
      if(VRSeXfEpbj == true){VRSeXfEpbj = false;}
      if(eEtizeHpMB == true){eEtizeHpMB = false;}
      if(OpAsLhxUMA == true){OpAsLhxUMA = false;}
      if(eRMmGqkpkq == true){eRMmGqkpkq = false;}
      if(rpiVZhbdIH == true){rpiVZhbdIH = false;}
      if(gRXBHfQZSp == true){gRXBHfQZSp = false;}
      if(ijcaFMrGcH == true){ijcaFMrGcH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTTSMESAOY
{ 
  void JJQFLLWlhH()
  { 
      bool jPgHEzYQUU = false;
      bool CuheNOAXNZ = false;
      bool RYfmrXbWlS = false;
      bool FdfIuymyjW = false;
      bool cTCCZPzzLu = false;
      bool ziImXKitOg = false;
      bool WCeCOYOYiP = false;
      bool bBmqwyWdMc = false;
      bool YcLqSVUrkk = false;
      bool PriDzaoAnB = false;
      bool AZPuTyuQqY = false;
      bool nFhlHtqnir = false;
      bool DWnyAiRjrV = false;
      bool JVoKbyMPWT = false;
      bool ZEBLwJKxuF = false;
      bool jBQuxdlRuj = false;
      bool fLYUPRPWJJ = false;
      bool gaQPSzUcBp = false;
      bool YUomlIFtNy = false;
      bool MtTmnOegud = false;
      string wUQLJAlooy;
      string fiHmQOpjMi;
      string RqppZbuggF;
      string rUIgARDezh;
      string GbnSXiAKVU;
      string LKpoqFdalg;
      string EFIjGLZalz;
      string KKkdcpDWRp;
      string akKLsgeSpu;
      string mcsRdASDMM;
      string JZXWJAZLMA;
      string CGIwFStxpZ;
      string fGjqLhRSzb;
      string XzKEfBNnBs;
      string GSGpsfTxMK;
      string FUNmgCpfKb;
      string iGMjbDwEPE;
      string FGwwSMAtyf;
      string NTGoVCkWXc;
      string LgdYKAGVNo;
      if(wUQLJAlooy == JZXWJAZLMA){jPgHEzYQUU = true;}
      else if(JZXWJAZLMA == wUQLJAlooy){AZPuTyuQqY = true;}
      if(fiHmQOpjMi == CGIwFStxpZ){CuheNOAXNZ = true;}
      else if(CGIwFStxpZ == fiHmQOpjMi){nFhlHtqnir = true;}
      if(RqppZbuggF == fGjqLhRSzb){RYfmrXbWlS = true;}
      else if(fGjqLhRSzb == RqppZbuggF){DWnyAiRjrV = true;}
      if(rUIgARDezh == XzKEfBNnBs){FdfIuymyjW = true;}
      else if(XzKEfBNnBs == rUIgARDezh){JVoKbyMPWT = true;}
      if(GbnSXiAKVU == GSGpsfTxMK){cTCCZPzzLu = true;}
      else if(GSGpsfTxMK == GbnSXiAKVU){ZEBLwJKxuF = true;}
      if(LKpoqFdalg == FUNmgCpfKb){ziImXKitOg = true;}
      else if(FUNmgCpfKb == LKpoqFdalg){jBQuxdlRuj = true;}
      if(EFIjGLZalz == iGMjbDwEPE){WCeCOYOYiP = true;}
      else if(iGMjbDwEPE == EFIjGLZalz){fLYUPRPWJJ = true;}
      if(KKkdcpDWRp == FGwwSMAtyf){bBmqwyWdMc = true;}
      if(akKLsgeSpu == NTGoVCkWXc){YcLqSVUrkk = true;}
      if(mcsRdASDMM == LgdYKAGVNo){PriDzaoAnB = true;}
      while(FGwwSMAtyf == KKkdcpDWRp){gaQPSzUcBp = true;}
      while(NTGoVCkWXc == NTGoVCkWXc){YUomlIFtNy = true;}
      while(LgdYKAGVNo == LgdYKAGVNo){MtTmnOegud = true;}
      if(jPgHEzYQUU == true){jPgHEzYQUU = false;}
      if(CuheNOAXNZ == true){CuheNOAXNZ = false;}
      if(RYfmrXbWlS == true){RYfmrXbWlS = false;}
      if(FdfIuymyjW == true){FdfIuymyjW = false;}
      if(cTCCZPzzLu == true){cTCCZPzzLu = false;}
      if(ziImXKitOg == true){ziImXKitOg = false;}
      if(WCeCOYOYiP == true){WCeCOYOYiP = false;}
      if(bBmqwyWdMc == true){bBmqwyWdMc = false;}
      if(YcLqSVUrkk == true){YcLqSVUrkk = false;}
      if(PriDzaoAnB == true){PriDzaoAnB = false;}
      if(AZPuTyuQqY == true){AZPuTyuQqY = false;}
      if(nFhlHtqnir == true){nFhlHtqnir = false;}
      if(DWnyAiRjrV == true){DWnyAiRjrV = false;}
      if(JVoKbyMPWT == true){JVoKbyMPWT = false;}
      if(ZEBLwJKxuF == true){ZEBLwJKxuF = false;}
      if(jBQuxdlRuj == true){jBQuxdlRuj = false;}
      if(fLYUPRPWJJ == true){fLYUPRPWJJ = false;}
      if(gaQPSzUcBp == true){gaQPSzUcBp = false;}
      if(YUomlIFtNy == true){YUomlIFtNy = false;}
      if(MtTmnOegud == true){MtTmnOegud = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXPQVYUHMN
{ 
  void TmhfKDHuUo()
  { 
      bool rLXxgLqOHA = false;
      bool VsWrycGAai = false;
      bool NhAWMbaZOF = false;
      bool DLNeiwQCsB = false;
      bool CrkUyUsxIb = false;
      bool JeZHjKKAkE = false;
      bool jQzBxKfqIB = false;
      bool MDHYgUxeXq = false;
      bool icRmwXkFtY = false;
      bool kPQoQkriXn = false;
      bool oBoHPFXBZP = false;
      bool MfbtUHzMFY = false;
      bool YZwiPwlRHu = false;
      bool cNHjBhnJWq = false;
      bool AjfeLFmWTJ = false;
      bool kedyOOEFqT = false;
      bool SFsemyXqrm = false;
      bool TopOYntRWK = false;
      bool IPxyJxjJUm = false;
      bool chSDXtqArM = false;
      string swkxXBGNzP;
      string RXxbUSKZly;
      string QSGcIzgEHU;
      string VswFDGSylD;
      string EbDPyPOUex;
      string fSKZmZoHnY;
      string UBGetYaqYN;
      string AMmisoOqer;
      string jLZKoChWSc;
      string RKJNhDVYUZ;
      string nWuQwSfbfx;
      string KxbunIauoq;
      string pEYuwpCYAp;
      string TpVFEMPJNV;
      string VGqUSThOYZ;
      string cZicjjyATG;
      string QGaodUaWqa;
      string rQhTViNEcb;
      string HnAaNtHsVU;
      string OPoHEPfBqx;
      if(swkxXBGNzP == nWuQwSfbfx){rLXxgLqOHA = true;}
      else if(nWuQwSfbfx == swkxXBGNzP){oBoHPFXBZP = true;}
      if(RXxbUSKZly == KxbunIauoq){VsWrycGAai = true;}
      else if(KxbunIauoq == RXxbUSKZly){MfbtUHzMFY = true;}
      if(QSGcIzgEHU == pEYuwpCYAp){NhAWMbaZOF = true;}
      else if(pEYuwpCYAp == QSGcIzgEHU){YZwiPwlRHu = true;}
      if(VswFDGSylD == TpVFEMPJNV){DLNeiwQCsB = true;}
      else if(TpVFEMPJNV == VswFDGSylD){cNHjBhnJWq = true;}
      if(EbDPyPOUex == VGqUSThOYZ){CrkUyUsxIb = true;}
      else if(VGqUSThOYZ == EbDPyPOUex){AjfeLFmWTJ = true;}
      if(fSKZmZoHnY == cZicjjyATG){JeZHjKKAkE = true;}
      else if(cZicjjyATG == fSKZmZoHnY){kedyOOEFqT = true;}
      if(UBGetYaqYN == QGaodUaWqa){jQzBxKfqIB = true;}
      else if(QGaodUaWqa == UBGetYaqYN){SFsemyXqrm = true;}
      if(AMmisoOqer == rQhTViNEcb){MDHYgUxeXq = true;}
      if(jLZKoChWSc == HnAaNtHsVU){icRmwXkFtY = true;}
      if(RKJNhDVYUZ == OPoHEPfBqx){kPQoQkriXn = true;}
      while(rQhTViNEcb == AMmisoOqer){TopOYntRWK = true;}
      while(HnAaNtHsVU == HnAaNtHsVU){IPxyJxjJUm = true;}
      while(OPoHEPfBqx == OPoHEPfBqx){chSDXtqArM = true;}
      if(rLXxgLqOHA == true){rLXxgLqOHA = false;}
      if(VsWrycGAai == true){VsWrycGAai = false;}
      if(NhAWMbaZOF == true){NhAWMbaZOF = false;}
      if(DLNeiwQCsB == true){DLNeiwQCsB = false;}
      if(CrkUyUsxIb == true){CrkUyUsxIb = false;}
      if(JeZHjKKAkE == true){JeZHjKKAkE = false;}
      if(jQzBxKfqIB == true){jQzBxKfqIB = false;}
      if(MDHYgUxeXq == true){MDHYgUxeXq = false;}
      if(icRmwXkFtY == true){icRmwXkFtY = false;}
      if(kPQoQkriXn == true){kPQoQkriXn = false;}
      if(oBoHPFXBZP == true){oBoHPFXBZP = false;}
      if(MfbtUHzMFY == true){MfbtUHzMFY = false;}
      if(YZwiPwlRHu == true){YZwiPwlRHu = false;}
      if(cNHjBhnJWq == true){cNHjBhnJWq = false;}
      if(AjfeLFmWTJ == true){AjfeLFmWTJ = false;}
      if(kedyOOEFqT == true){kedyOOEFqT = false;}
      if(SFsemyXqrm == true){SFsemyXqrm = false;}
      if(TopOYntRWK == true){TopOYntRWK = false;}
      if(IPxyJxjJUm == true){IPxyJxjJUm = false;}
      if(chSDXtqArM == true){chSDXtqArM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXDPACSVMW
{ 
  void OqzXnjyFEO()
  { 
      bool CjhTNKHZUN = false;
      bool yJNsheQGAU = false;
      bool DPykhJXajG = false;
      bool ebSAQAMuyZ = false;
      bool cPGSaFLbjh = false;
      bool cyGcsmlxlE = false;
      bool lfoNhVqMcg = false;
      bool RVIZqnIfKc = false;
      bool xupBcgUpHc = false;
      bool NPJsmxZrjF = false;
      bool NyzDPHoglE = false;
      bool dGlJGqomkB = false;
      bool ABEzSCLOlt = false;
      bool NQuFOzumlU = false;
      bool qnDCyHcAmw = false;
      bool HlGhEMsAjN = false;
      bool wZurpNKgtH = false;
      bool uCBQJMxCAL = false;
      bool ZLbombJNAC = false;
      bool FuDXYRsLLj = false;
      string sroxUeJaDJ;
      string EAZNImsQuh;
      string iQKwPwYasQ;
      string qyIJaOQsdV;
      string OPuPLzLmSo;
      string OBzrMchsgY;
      string FihlRGqQms;
      string WAmYTTVtjP;
      string klHDBoyQwy;
      string gXLFQegIyF;
      string ItAYROOaYs;
      string HmIRmTbekb;
      string HaToMzngIn;
      string mNwdGpkhkm;
      string aXqDqsOsRw;
      string DBXVygaLMS;
      string ZgSjFspdKx;
      string istxAjiQyT;
      string kuPLjkpafY;
      string PYVSMtEGxx;
      if(sroxUeJaDJ == ItAYROOaYs){CjhTNKHZUN = true;}
      else if(ItAYROOaYs == sroxUeJaDJ){NyzDPHoglE = true;}
      if(EAZNImsQuh == HmIRmTbekb){yJNsheQGAU = true;}
      else if(HmIRmTbekb == EAZNImsQuh){dGlJGqomkB = true;}
      if(iQKwPwYasQ == HaToMzngIn){DPykhJXajG = true;}
      else if(HaToMzngIn == iQKwPwYasQ){ABEzSCLOlt = true;}
      if(qyIJaOQsdV == mNwdGpkhkm){ebSAQAMuyZ = true;}
      else if(mNwdGpkhkm == qyIJaOQsdV){NQuFOzumlU = true;}
      if(OPuPLzLmSo == aXqDqsOsRw){cPGSaFLbjh = true;}
      else if(aXqDqsOsRw == OPuPLzLmSo){qnDCyHcAmw = true;}
      if(OBzrMchsgY == DBXVygaLMS){cyGcsmlxlE = true;}
      else if(DBXVygaLMS == OBzrMchsgY){HlGhEMsAjN = true;}
      if(FihlRGqQms == ZgSjFspdKx){lfoNhVqMcg = true;}
      else if(ZgSjFspdKx == FihlRGqQms){wZurpNKgtH = true;}
      if(WAmYTTVtjP == istxAjiQyT){RVIZqnIfKc = true;}
      if(klHDBoyQwy == kuPLjkpafY){xupBcgUpHc = true;}
      if(gXLFQegIyF == PYVSMtEGxx){NPJsmxZrjF = true;}
      while(istxAjiQyT == WAmYTTVtjP){uCBQJMxCAL = true;}
      while(kuPLjkpafY == kuPLjkpafY){ZLbombJNAC = true;}
      while(PYVSMtEGxx == PYVSMtEGxx){FuDXYRsLLj = true;}
      if(CjhTNKHZUN == true){CjhTNKHZUN = false;}
      if(yJNsheQGAU == true){yJNsheQGAU = false;}
      if(DPykhJXajG == true){DPykhJXajG = false;}
      if(ebSAQAMuyZ == true){ebSAQAMuyZ = false;}
      if(cPGSaFLbjh == true){cPGSaFLbjh = false;}
      if(cyGcsmlxlE == true){cyGcsmlxlE = false;}
      if(lfoNhVqMcg == true){lfoNhVqMcg = false;}
      if(RVIZqnIfKc == true){RVIZqnIfKc = false;}
      if(xupBcgUpHc == true){xupBcgUpHc = false;}
      if(NPJsmxZrjF == true){NPJsmxZrjF = false;}
      if(NyzDPHoglE == true){NyzDPHoglE = false;}
      if(dGlJGqomkB == true){dGlJGqomkB = false;}
      if(ABEzSCLOlt == true){ABEzSCLOlt = false;}
      if(NQuFOzumlU == true){NQuFOzumlU = false;}
      if(qnDCyHcAmw == true){qnDCyHcAmw = false;}
      if(HlGhEMsAjN == true){HlGhEMsAjN = false;}
      if(wZurpNKgtH == true){wZurpNKgtH = false;}
      if(uCBQJMxCAL == true){uCBQJMxCAL = false;}
      if(ZLbombJNAC == true){ZLbombJNAC = false;}
      if(FuDXYRsLLj == true){FuDXYRsLLj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQTRGYSHBD
{ 
  void FxofpQRdTc()
  { 
      bool HfzowTlPVD = false;
      bool cjmBwRhobY = false;
      bool QULoYUlVlu = false;
      bool EARGNTiTNj = false;
      bool ZFahrHWSFg = false;
      bool wSLlCmUKPb = false;
      bool hPcazbSgmb = false;
      bool iObqzLtcxR = false;
      bool xTPEzlneDa = false;
      bool zYDlCJbziP = false;
      bool npecygqUmq = false;
      bool rqMxeOzYaN = false;
      bool nmcMcJKooo = false;
      bool ittgdGnmGR = false;
      bool tTrMiILGGn = false;
      bool KDXVbANSAn = false;
      bool VBeyIxxeTX = false;
      bool aMSISUuPdT = false;
      bool xEiBeeVXFc = false;
      bool sUlRwsnsEk = false;
      string zuWzXZRHaz;
      string GttdKaYhOk;
      string gfAilJFJKs;
      string atAPieRVpy;
      string fdVQwVRozj;
      string xyBRKTtmNO;
      string THxhYMsduf;
      string ICqPEDKjlP;
      string rQKZucriEP;
      string jeIbdYgmqj;
      string bmsSauGkMH;
      string JKAxVCxWlu;
      string TKZfudsOkf;
      string VWrCmEXqyA;
      string VHVwGZdKGa;
      string aJBwPRNMWw;
      string BqzgklRyKQ;
      string eGXkZMocZV;
      string AiIJELVwlU;
      string qKTCzdHnLT;
      if(zuWzXZRHaz == bmsSauGkMH){HfzowTlPVD = true;}
      else if(bmsSauGkMH == zuWzXZRHaz){npecygqUmq = true;}
      if(GttdKaYhOk == JKAxVCxWlu){cjmBwRhobY = true;}
      else if(JKAxVCxWlu == GttdKaYhOk){rqMxeOzYaN = true;}
      if(gfAilJFJKs == TKZfudsOkf){QULoYUlVlu = true;}
      else if(TKZfudsOkf == gfAilJFJKs){nmcMcJKooo = true;}
      if(atAPieRVpy == VWrCmEXqyA){EARGNTiTNj = true;}
      else if(VWrCmEXqyA == atAPieRVpy){ittgdGnmGR = true;}
      if(fdVQwVRozj == VHVwGZdKGa){ZFahrHWSFg = true;}
      else if(VHVwGZdKGa == fdVQwVRozj){tTrMiILGGn = true;}
      if(xyBRKTtmNO == aJBwPRNMWw){wSLlCmUKPb = true;}
      else if(aJBwPRNMWw == xyBRKTtmNO){KDXVbANSAn = true;}
      if(THxhYMsduf == BqzgklRyKQ){hPcazbSgmb = true;}
      else if(BqzgklRyKQ == THxhYMsduf){VBeyIxxeTX = true;}
      if(ICqPEDKjlP == eGXkZMocZV){iObqzLtcxR = true;}
      if(rQKZucriEP == AiIJELVwlU){xTPEzlneDa = true;}
      if(jeIbdYgmqj == qKTCzdHnLT){zYDlCJbziP = true;}
      while(eGXkZMocZV == ICqPEDKjlP){aMSISUuPdT = true;}
      while(AiIJELVwlU == AiIJELVwlU){xEiBeeVXFc = true;}
      while(qKTCzdHnLT == qKTCzdHnLT){sUlRwsnsEk = true;}
      if(HfzowTlPVD == true){HfzowTlPVD = false;}
      if(cjmBwRhobY == true){cjmBwRhobY = false;}
      if(QULoYUlVlu == true){QULoYUlVlu = false;}
      if(EARGNTiTNj == true){EARGNTiTNj = false;}
      if(ZFahrHWSFg == true){ZFahrHWSFg = false;}
      if(wSLlCmUKPb == true){wSLlCmUKPb = false;}
      if(hPcazbSgmb == true){hPcazbSgmb = false;}
      if(iObqzLtcxR == true){iObqzLtcxR = false;}
      if(xTPEzlneDa == true){xTPEzlneDa = false;}
      if(zYDlCJbziP == true){zYDlCJbziP = false;}
      if(npecygqUmq == true){npecygqUmq = false;}
      if(rqMxeOzYaN == true){rqMxeOzYaN = false;}
      if(nmcMcJKooo == true){nmcMcJKooo = false;}
      if(ittgdGnmGR == true){ittgdGnmGR = false;}
      if(tTrMiILGGn == true){tTrMiILGGn = false;}
      if(KDXVbANSAn == true){KDXVbANSAn = false;}
      if(VBeyIxxeTX == true){VBeyIxxeTX = false;}
      if(aMSISUuPdT == true){aMSISUuPdT = false;}
      if(xEiBeeVXFc == true){xEiBeeVXFc = false;}
      if(sUlRwsnsEk == true){sUlRwsnsEk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJZWLALOKZ
{ 
  void GzHBqYADwX()
  { 
      bool KxmFqqrOLB = false;
      bool ZOJrrlykcQ = false;
      bool ozHSCalAEX = false;
      bool jaPoeHEmXw = false;
      bool IcysIJuwdr = false;
      bool JxeoELoTCP = false;
      bool EqJmQzzUMj = false;
      bool hKMfHMAOKs = false;
      bool epVLOluZjT = false;
      bool SjjIrQSLbJ = false;
      bool KaisKykzgq = false;
      bool KZJJjOVxYd = false;
      bool DYjrRxZEmp = false;
      bool tolBhEGbBP = false;
      bool BwrsJraZXd = false;
      bool uUlyGlppaN = false;
      bool YfLqxUnHbe = false;
      bool HswJbGfqiZ = false;
      bool VzfIuYDnuu = false;
      bool OPAmqUjBuo = false;
      string wbdLdiWxFY;
      string bjILMinbWB;
      string loqdQKFGmr;
      string bCkKFSPbjf;
      string fPFStMZHoT;
      string XKeqEHjAuS;
      string cPJNwYzyGt;
      string SMrqVViXjD;
      string jyRTTRWsFy;
      string hPfQDPFrVV;
      string NbAtAKSnVh;
      string XMQqieypse;
      string BFrILDgamF;
      string QqBNpHxWSJ;
      string ziXXZVzogX;
      string RPzqTHiriw;
      string dqAQRgKCBa;
      string gaWjfShUhp;
      string ErsPmBqKth;
      string XFnWeHhHFs;
      if(wbdLdiWxFY == NbAtAKSnVh){KxmFqqrOLB = true;}
      else if(NbAtAKSnVh == wbdLdiWxFY){KaisKykzgq = true;}
      if(bjILMinbWB == XMQqieypse){ZOJrrlykcQ = true;}
      else if(XMQqieypse == bjILMinbWB){KZJJjOVxYd = true;}
      if(loqdQKFGmr == BFrILDgamF){ozHSCalAEX = true;}
      else if(BFrILDgamF == loqdQKFGmr){DYjrRxZEmp = true;}
      if(bCkKFSPbjf == QqBNpHxWSJ){jaPoeHEmXw = true;}
      else if(QqBNpHxWSJ == bCkKFSPbjf){tolBhEGbBP = true;}
      if(fPFStMZHoT == ziXXZVzogX){IcysIJuwdr = true;}
      else if(ziXXZVzogX == fPFStMZHoT){BwrsJraZXd = true;}
      if(XKeqEHjAuS == RPzqTHiriw){JxeoELoTCP = true;}
      else if(RPzqTHiriw == XKeqEHjAuS){uUlyGlppaN = true;}
      if(cPJNwYzyGt == dqAQRgKCBa){EqJmQzzUMj = true;}
      else if(dqAQRgKCBa == cPJNwYzyGt){YfLqxUnHbe = true;}
      if(SMrqVViXjD == gaWjfShUhp){hKMfHMAOKs = true;}
      if(jyRTTRWsFy == ErsPmBqKth){epVLOluZjT = true;}
      if(hPfQDPFrVV == XFnWeHhHFs){SjjIrQSLbJ = true;}
      while(gaWjfShUhp == SMrqVViXjD){HswJbGfqiZ = true;}
      while(ErsPmBqKth == ErsPmBqKth){VzfIuYDnuu = true;}
      while(XFnWeHhHFs == XFnWeHhHFs){OPAmqUjBuo = true;}
      if(KxmFqqrOLB == true){KxmFqqrOLB = false;}
      if(ZOJrrlykcQ == true){ZOJrrlykcQ = false;}
      if(ozHSCalAEX == true){ozHSCalAEX = false;}
      if(jaPoeHEmXw == true){jaPoeHEmXw = false;}
      if(IcysIJuwdr == true){IcysIJuwdr = false;}
      if(JxeoELoTCP == true){JxeoELoTCP = false;}
      if(EqJmQzzUMj == true){EqJmQzzUMj = false;}
      if(hKMfHMAOKs == true){hKMfHMAOKs = false;}
      if(epVLOluZjT == true){epVLOluZjT = false;}
      if(SjjIrQSLbJ == true){SjjIrQSLbJ = false;}
      if(KaisKykzgq == true){KaisKykzgq = false;}
      if(KZJJjOVxYd == true){KZJJjOVxYd = false;}
      if(DYjrRxZEmp == true){DYjrRxZEmp = false;}
      if(tolBhEGbBP == true){tolBhEGbBP = false;}
      if(BwrsJraZXd == true){BwrsJraZXd = false;}
      if(uUlyGlppaN == true){uUlyGlppaN = false;}
      if(YfLqxUnHbe == true){YfLqxUnHbe = false;}
      if(HswJbGfqiZ == true){HswJbGfqiZ = false;}
      if(VzfIuYDnuu == true){VzfIuYDnuu = false;}
      if(OPAmqUjBuo == true){OPAmqUjBuo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYOGGNTQOG
{ 
  void SNrhgEuptR()
  { 
      bool YrcARyBEUO = false;
      bool OISDMKUSQR = false;
      bool rxrwRMwzas = false;
      bool TJZrKBZdDR = false;
      bool BtIRUwKIgJ = false;
      bool EtFeZazfiE = false;
      bool BCcatEhZsL = false;
      bool jqOyQyoZbV = false;
      bool CnRRnZEtSi = false;
      bool CsuzPyQgXP = false;
      bool NjOVYNeGOa = false;
      bool lYEMCNjLmU = false;
      bool AmGJIpuPiR = false;
      bool gICLHSYwrZ = false;
      bool uxfqxcohwC = false;
      bool OFsCPacEMi = false;
      bool SOXxscVrFj = false;
      bool onSNZCHPMe = false;
      bool BNSgCbOAwg = false;
      bool oTiJHfZhxT = false;
      string LdyrYKzaFX;
      string ThZfDISZfc;
      string psqnZJNUOR;
      string GRsuPcdksz;
      string sBQwgSBMxw;
      string IgxmIRlJRP;
      string weMmRCodQZ;
      string egffjnbuHH;
      string IBWRJZTFmx;
      string pTTdCNodee;
      string dWuWRaARCT;
      string oqCJHuHtdq;
      string iiqSiKNBcV;
      string yyPcdkFzAh;
      string YBCSIzRJWH;
      string GuAmutfcmG;
      string NzngVpaZfV;
      string oIsuSgfXKj;
      string sDdVPDycgi;
      string EcLtTZMVxR;
      if(LdyrYKzaFX == dWuWRaARCT){YrcARyBEUO = true;}
      else if(dWuWRaARCT == LdyrYKzaFX){NjOVYNeGOa = true;}
      if(ThZfDISZfc == oqCJHuHtdq){OISDMKUSQR = true;}
      else if(oqCJHuHtdq == ThZfDISZfc){lYEMCNjLmU = true;}
      if(psqnZJNUOR == iiqSiKNBcV){rxrwRMwzas = true;}
      else if(iiqSiKNBcV == psqnZJNUOR){AmGJIpuPiR = true;}
      if(GRsuPcdksz == yyPcdkFzAh){TJZrKBZdDR = true;}
      else if(yyPcdkFzAh == GRsuPcdksz){gICLHSYwrZ = true;}
      if(sBQwgSBMxw == YBCSIzRJWH){BtIRUwKIgJ = true;}
      else if(YBCSIzRJWH == sBQwgSBMxw){uxfqxcohwC = true;}
      if(IgxmIRlJRP == GuAmutfcmG){EtFeZazfiE = true;}
      else if(GuAmutfcmG == IgxmIRlJRP){OFsCPacEMi = true;}
      if(weMmRCodQZ == NzngVpaZfV){BCcatEhZsL = true;}
      else if(NzngVpaZfV == weMmRCodQZ){SOXxscVrFj = true;}
      if(egffjnbuHH == oIsuSgfXKj){jqOyQyoZbV = true;}
      if(IBWRJZTFmx == sDdVPDycgi){CnRRnZEtSi = true;}
      if(pTTdCNodee == EcLtTZMVxR){CsuzPyQgXP = true;}
      while(oIsuSgfXKj == egffjnbuHH){onSNZCHPMe = true;}
      while(sDdVPDycgi == sDdVPDycgi){BNSgCbOAwg = true;}
      while(EcLtTZMVxR == EcLtTZMVxR){oTiJHfZhxT = true;}
      if(YrcARyBEUO == true){YrcARyBEUO = false;}
      if(OISDMKUSQR == true){OISDMKUSQR = false;}
      if(rxrwRMwzas == true){rxrwRMwzas = false;}
      if(TJZrKBZdDR == true){TJZrKBZdDR = false;}
      if(BtIRUwKIgJ == true){BtIRUwKIgJ = false;}
      if(EtFeZazfiE == true){EtFeZazfiE = false;}
      if(BCcatEhZsL == true){BCcatEhZsL = false;}
      if(jqOyQyoZbV == true){jqOyQyoZbV = false;}
      if(CnRRnZEtSi == true){CnRRnZEtSi = false;}
      if(CsuzPyQgXP == true){CsuzPyQgXP = false;}
      if(NjOVYNeGOa == true){NjOVYNeGOa = false;}
      if(lYEMCNjLmU == true){lYEMCNjLmU = false;}
      if(AmGJIpuPiR == true){AmGJIpuPiR = false;}
      if(gICLHSYwrZ == true){gICLHSYwrZ = false;}
      if(uxfqxcohwC == true){uxfqxcohwC = false;}
      if(OFsCPacEMi == true){OFsCPacEMi = false;}
      if(SOXxscVrFj == true){SOXxscVrFj = false;}
      if(onSNZCHPMe == true){onSNZCHPMe = false;}
      if(BNSgCbOAwg == true){BNSgCbOAwg = false;}
      if(oTiJHfZhxT == true){oTiJHfZhxT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSGKFDGXLC
{ 
  void HmahSVsggV()
  { 
      bool yceilCKoMG = false;
      bool LBUcillTDc = false;
      bool rJVuHMfNmi = false;
      bool DfltRdCwDR = false;
      bool tfUtgxfZJn = false;
      bool uwQkdnHjaY = false;
      bool VxCcDeOZLE = false;
      bool ioQkiMoaNK = false;
      bool gGDynGOBQc = false;
      bool WSUdwwcqpB = false;
      bool iFNFEFfeCQ = false;
      bool zfVQrOtEox = false;
      bool QMJhgQTlol = false;
      bool jykLaarxsh = false;
      bool ajyzdqwElg = false;
      bool CYBskVweXm = false;
      bool ksoQgBtKpQ = false;
      bool WwKGVgOJEp = false;
      bool UPAIiLwqZF = false;
      bool dMZFwgthSc = false;
      string cAkaSPAIKw;
      string rlpLiEUYWG;
      string GKynaHmemp;
      string sVWmnqwKGd;
      string kccuqSELnG;
      string dFtAiSCwzK;
      string cUVTDWPDXr;
      string HKRrVcgCxH;
      string CaqgMmbWDV;
      string nAKwBPGJrU;
      string DBnwySmBdF;
      string kAzrHBdoGP;
      string trzBDHzUqG;
      string WXJbDBmuis;
      string zarxjnASoA;
      string kRCcaLClrp;
      string SRKXiNpXnG;
      string NiGMQTABRP;
      string HgfpUFUgBr;
      string yACrZgQTOW;
      if(cAkaSPAIKw == DBnwySmBdF){yceilCKoMG = true;}
      else if(DBnwySmBdF == cAkaSPAIKw){iFNFEFfeCQ = true;}
      if(rlpLiEUYWG == kAzrHBdoGP){LBUcillTDc = true;}
      else if(kAzrHBdoGP == rlpLiEUYWG){zfVQrOtEox = true;}
      if(GKynaHmemp == trzBDHzUqG){rJVuHMfNmi = true;}
      else if(trzBDHzUqG == GKynaHmemp){QMJhgQTlol = true;}
      if(sVWmnqwKGd == WXJbDBmuis){DfltRdCwDR = true;}
      else if(WXJbDBmuis == sVWmnqwKGd){jykLaarxsh = true;}
      if(kccuqSELnG == zarxjnASoA){tfUtgxfZJn = true;}
      else if(zarxjnASoA == kccuqSELnG){ajyzdqwElg = true;}
      if(dFtAiSCwzK == kRCcaLClrp){uwQkdnHjaY = true;}
      else if(kRCcaLClrp == dFtAiSCwzK){CYBskVweXm = true;}
      if(cUVTDWPDXr == SRKXiNpXnG){VxCcDeOZLE = true;}
      else if(SRKXiNpXnG == cUVTDWPDXr){ksoQgBtKpQ = true;}
      if(HKRrVcgCxH == NiGMQTABRP){ioQkiMoaNK = true;}
      if(CaqgMmbWDV == HgfpUFUgBr){gGDynGOBQc = true;}
      if(nAKwBPGJrU == yACrZgQTOW){WSUdwwcqpB = true;}
      while(NiGMQTABRP == HKRrVcgCxH){WwKGVgOJEp = true;}
      while(HgfpUFUgBr == HgfpUFUgBr){UPAIiLwqZF = true;}
      while(yACrZgQTOW == yACrZgQTOW){dMZFwgthSc = true;}
      if(yceilCKoMG == true){yceilCKoMG = false;}
      if(LBUcillTDc == true){LBUcillTDc = false;}
      if(rJVuHMfNmi == true){rJVuHMfNmi = false;}
      if(DfltRdCwDR == true){DfltRdCwDR = false;}
      if(tfUtgxfZJn == true){tfUtgxfZJn = false;}
      if(uwQkdnHjaY == true){uwQkdnHjaY = false;}
      if(VxCcDeOZLE == true){VxCcDeOZLE = false;}
      if(ioQkiMoaNK == true){ioQkiMoaNK = false;}
      if(gGDynGOBQc == true){gGDynGOBQc = false;}
      if(WSUdwwcqpB == true){WSUdwwcqpB = false;}
      if(iFNFEFfeCQ == true){iFNFEFfeCQ = false;}
      if(zfVQrOtEox == true){zfVQrOtEox = false;}
      if(QMJhgQTlol == true){QMJhgQTlol = false;}
      if(jykLaarxsh == true){jykLaarxsh = false;}
      if(ajyzdqwElg == true){ajyzdqwElg = false;}
      if(CYBskVweXm == true){CYBskVweXm = false;}
      if(ksoQgBtKpQ == true){ksoQgBtKpQ = false;}
      if(WwKGVgOJEp == true){WwKGVgOJEp = false;}
      if(UPAIiLwqZF == true){UPAIiLwqZF = false;}
      if(dMZFwgthSc == true){dMZFwgthSc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNQEKACUWV
{ 
  void jaZAyrYwsu()
  { 
      bool zyhQijXWwt = false;
      bool LudsqAokCC = false;
      bool dgxIwuwUai = false;
      bool tWSlpKrkwY = false;
      bool ciGYCDZHof = false;
      bool imWQUSAYUn = false;
      bool nDuMzncqDf = false;
      bool HEocZuZYGs = false;
      bool UnetzGABRX = false;
      bool KTQHkZmsYN = false;
      bool aiEJYeytqZ = false;
      bool raSaSzXBMs = false;
      bool naZeVnngqz = false;
      bool HgAsSliVUU = false;
      bool HFKqeiBook = false;
      bool BlfeZzIZmk = false;
      bool pQCqRLaZIf = false;
      bool QBfqkhPhzm = false;
      bool myrGyVAUSS = false;
      bool cJhjepDTZT = false;
      string FjzkWqiDeP;
      string qWjcBtgcqE;
      string hGHAdbRDOz;
      string VOzVDCJEfb;
      string wxaWyPFLII;
      string iBtKQzbyHu;
      string ZenfscXOYz;
      string jcxPHkekBO;
      string VGuFPUTnED;
      string ZLxjBQIucV;
      string rqlJYGEdCf;
      string TqwrZTjiQY;
      string IiJVYXeMNp;
      string bjHfVeTlgI;
      string QolXiiOEKh;
      string gZeEMIgPjA;
      string aqQLEjiQVt;
      string zxBHISxllp;
      string JaBeIBFCSN;
      string yDBggYYZTz;
      if(FjzkWqiDeP == rqlJYGEdCf){zyhQijXWwt = true;}
      else if(rqlJYGEdCf == FjzkWqiDeP){aiEJYeytqZ = true;}
      if(qWjcBtgcqE == TqwrZTjiQY){LudsqAokCC = true;}
      else if(TqwrZTjiQY == qWjcBtgcqE){raSaSzXBMs = true;}
      if(hGHAdbRDOz == IiJVYXeMNp){dgxIwuwUai = true;}
      else if(IiJVYXeMNp == hGHAdbRDOz){naZeVnngqz = true;}
      if(VOzVDCJEfb == bjHfVeTlgI){tWSlpKrkwY = true;}
      else if(bjHfVeTlgI == VOzVDCJEfb){HgAsSliVUU = true;}
      if(wxaWyPFLII == QolXiiOEKh){ciGYCDZHof = true;}
      else if(QolXiiOEKh == wxaWyPFLII){HFKqeiBook = true;}
      if(iBtKQzbyHu == gZeEMIgPjA){imWQUSAYUn = true;}
      else if(gZeEMIgPjA == iBtKQzbyHu){BlfeZzIZmk = true;}
      if(ZenfscXOYz == aqQLEjiQVt){nDuMzncqDf = true;}
      else if(aqQLEjiQVt == ZenfscXOYz){pQCqRLaZIf = true;}
      if(jcxPHkekBO == zxBHISxllp){HEocZuZYGs = true;}
      if(VGuFPUTnED == JaBeIBFCSN){UnetzGABRX = true;}
      if(ZLxjBQIucV == yDBggYYZTz){KTQHkZmsYN = true;}
      while(zxBHISxllp == jcxPHkekBO){QBfqkhPhzm = true;}
      while(JaBeIBFCSN == JaBeIBFCSN){myrGyVAUSS = true;}
      while(yDBggYYZTz == yDBggYYZTz){cJhjepDTZT = true;}
      if(zyhQijXWwt == true){zyhQijXWwt = false;}
      if(LudsqAokCC == true){LudsqAokCC = false;}
      if(dgxIwuwUai == true){dgxIwuwUai = false;}
      if(tWSlpKrkwY == true){tWSlpKrkwY = false;}
      if(ciGYCDZHof == true){ciGYCDZHof = false;}
      if(imWQUSAYUn == true){imWQUSAYUn = false;}
      if(nDuMzncqDf == true){nDuMzncqDf = false;}
      if(HEocZuZYGs == true){HEocZuZYGs = false;}
      if(UnetzGABRX == true){UnetzGABRX = false;}
      if(KTQHkZmsYN == true){KTQHkZmsYN = false;}
      if(aiEJYeytqZ == true){aiEJYeytqZ = false;}
      if(raSaSzXBMs == true){raSaSzXBMs = false;}
      if(naZeVnngqz == true){naZeVnngqz = false;}
      if(HgAsSliVUU == true){HgAsSliVUU = false;}
      if(HFKqeiBook == true){HFKqeiBook = false;}
      if(BlfeZzIZmk == true){BlfeZzIZmk = false;}
      if(pQCqRLaZIf == true){pQCqRLaZIf = false;}
      if(QBfqkhPhzm == true){QBfqkhPhzm = false;}
      if(myrGyVAUSS == true){myrGyVAUSS = false;}
      if(cJhjepDTZT == true){cJhjepDTZT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYVKOVJJUC
{ 
  void GiBraHnqrm()
  { 
      bool BVLFJCJkde = false;
      bool MYomVMejpm = false;
      bool KkNoiGqlVN = false;
      bool eXaFdfPkWZ = false;
      bool OgqmCHZMbT = false;
      bool oldBhQIVVD = false;
      bool LWPQAoyjIo = false;
      bool wsMQYcsZlb = false;
      bool geKBXrtYXM = false;
      bool XsOTOqRamN = false;
      bool JoDlWwZMcF = false;
      bool XhjtVgMNrH = false;
      bool uYMuRCdrBh = false;
      bool KSmXRqaXdb = false;
      bool RgwRopJTyh = false;
      bool eDheSjcHTT = false;
      bool RhLutEtLcd = false;
      bool FniPpOctGb = false;
      bool sKsTDHjHEh = false;
      bool NTDKJjUAXj = false;
      string yJqWBeyRfZ;
      string ZBYdoNqxMG;
      string YyBtwjsQLI;
      string cSrbFEcNar;
      string iFghbsEgrN;
      string JEzNwAHwaR;
      string lgFWxHJxYk;
      string jdVUXSQSSD;
      string eLYyzYSdeE;
      string wfmJGBAKkU;
      string jHIHcehepd;
      string indXmZIGWX;
      string nfRTnEqMNV;
      string RGhySWDRVU;
      string pmnBVICPVf;
      string stmMfEpnSX;
      string nVQTLcGfEP;
      string VpjChBqQyf;
      string CaqgcXSVRO;
      string gPzxfUVTor;
      if(yJqWBeyRfZ == jHIHcehepd){BVLFJCJkde = true;}
      else if(jHIHcehepd == yJqWBeyRfZ){JoDlWwZMcF = true;}
      if(ZBYdoNqxMG == indXmZIGWX){MYomVMejpm = true;}
      else if(indXmZIGWX == ZBYdoNqxMG){XhjtVgMNrH = true;}
      if(YyBtwjsQLI == nfRTnEqMNV){KkNoiGqlVN = true;}
      else if(nfRTnEqMNV == YyBtwjsQLI){uYMuRCdrBh = true;}
      if(cSrbFEcNar == RGhySWDRVU){eXaFdfPkWZ = true;}
      else if(RGhySWDRVU == cSrbFEcNar){KSmXRqaXdb = true;}
      if(iFghbsEgrN == pmnBVICPVf){OgqmCHZMbT = true;}
      else if(pmnBVICPVf == iFghbsEgrN){RgwRopJTyh = true;}
      if(JEzNwAHwaR == stmMfEpnSX){oldBhQIVVD = true;}
      else if(stmMfEpnSX == JEzNwAHwaR){eDheSjcHTT = true;}
      if(lgFWxHJxYk == nVQTLcGfEP){LWPQAoyjIo = true;}
      else if(nVQTLcGfEP == lgFWxHJxYk){RhLutEtLcd = true;}
      if(jdVUXSQSSD == VpjChBqQyf){wsMQYcsZlb = true;}
      if(eLYyzYSdeE == CaqgcXSVRO){geKBXrtYXM = true;}
      if(wfmJGBAKkU == gPzxfUVTor){XsOTOqRamN = true;}
      while(VpjChBqQyf == jdVUXSQSSD){FniPpOctGb = true;}
      while(CaqgcXSVRO == CaqgcXSVRO){sKsTDHjHEh = true;}
      while(gPzxfUVTor == gPzxfUVTor){NTDKJjUAXj = true;}
      if(BVLFJCJkde == true){BVLFJCJkde = false;}
      if(MYomVMejpm == true){MYomVMejpm = false;}
      if(KkNoiGqlVN == true){KkNoiGqlVN = false;}
      if(eXaFdfPkWZ == true){eXaFdfPkWZ = false;}
      if(OgqmCHZMbT == true){OgqmCHZMbT = false;}
      if(oldBhQIVVD == true){oldBhQIVVD = false;}
      if(LWPQAoyjIo == true){LWPQAoyjIo = false;}
      if(wsMQYcsZlb == true){wsMQYcsZlb = false;}
      if(geKBXrtYXM == true){geKBXrtYXM = false;}
      if(XsOTOqRamN == true){XsOTOqRamN = false;}
      if(JoDlWwZMcF == true){JoDlWwZMcF = false;}
      if(XhjtVgMNrH == true){XhjtVgMNrH = false;}
      if(uYMuRCdrBh == true){uYMuRCdrBh = false;}
      if(KSmXRqaXdb == true){KSmXRqaXdb = false;}
      if(RgwRopJTyh == true){RgwRopJTyh = false;}
      if(eDheSjcHTT == true){eDheSjcHTT = false;}
      if(RhLutEtLcd == true){RhLutEtLcd = false;}
      if(FniPpOctGb == true){FniPpOctGb = false;}
      if(sKsTDHjHEh == true){sKsTDHjHEh = false;}
      if(NTDKJjUAXj == true){NTDKJjUAXj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZUKSPQGLJ
{ 
  void TaSHMxbTPX()
  { 
      bool oUwEaCMOoL = false;
      bool juRpPyWUwG = false;
      bool hHBUyyqIsx = false;
      bool DmLUsPhRDd = false;
      bool qGQkOKkUTP = false;
      bool sRJJnhTbGc = false;
      bool LEVqHxiwxz = false;
      bool QERRObpPFn = false;
      bool MVodDkdCfK = false;
      bool wFLaSmkYdR = false;
      bool anXTynAqtM = false;
      bool qDWRPpOqmV = false;
      bool SgQlCKrqza = false;
      bool qQlmMYxUeP = false;
      bool klHTTritKb = false;
      bool XskHzsXkRn = false;
      bool uIqSVaRjEp = false;
      bool rtLXjfZxSK = false;
      bool ayfWDxednS = false;
      bool AMDqTcunxr = false;
      string MeMENMxdMs;
      string KVMcnQJujI;
      string pAXhUeKONx;
      string iotLkeuzYp;
      string cykmBibVSY;
      string hxyuNLGeji;
      string CiQOKUbBrJ;
      string UJVsfrOkfk;
      string CounPlqyxY;
      string XQOpnshVbg;
      string HZcJEXaEPV;
      string xVyygMnbzY;
      string dcDTkDufFl;
      string KrIzdbLkjq;
      string KlibbCSQIa;
      string FFWCCdWJYA;
      string ctzcLEMyTE;
      string ACrHNqsbrh;
      string kdWdgEVFxz;
      string FCLiNQmFPW;
      if(MeMENMxdMs == HZcJEXaEPV){oUwEaCMOoL = true;}
      else if(HZcJEXaEPV == MeMENMxdMs){anXTynAqtM = true;}
      if(KVMcnQJujI == xVyygMnbzY){juRpPyWUwG = true;}
      else if(xVyygMnbzY == KVMcnQJujI){qDWRPpOqmV = true;}
      if(pAXhUeKONx == dcDTkDufFl){hHBUyyqIsx = true;}
      else if(dcDTkDufFl == pAXhUeKONx){SgQlCKrqza = true;}
      if(iotLkeuzYp == KrIzdbLkjq){DmLUsPhRDd = true;}
      else if(KrIzdbLkjq == iotLkeuzYp){qQlmMYxUeP = true;}
      if(cykmBibVSY == KlibbCSQIa){qGQkOKkUTP = true;}
      else if(KlibbCSQIa == cykmBibVSY){klHTTritKb = true;}
      if(hxyuNLGeji == FFWCCdWJYA){sRJJnhTbGc = true;}
      else if(FFWCCdWJYA == hxyuNLGeji){XskHzsXkRn = true;}
      if(CiQOKUbBrJ == ctzcLEMyTE){LEVqHxiwxz = true;}
      else if(ctzcLEMyTE == CiQOKUbBrJ){uIqSVaRjEp = true;}
      if(UJVsfrOkfk == ACrHNqsbrh){QERRObpPFn = true;}
      if(CounPlqyxY == kdWdgEVFxz){MVodDkdCfK = true;}
      if(XQOpnshVbg == FCLiNQmFPW){wFLaSmkYdR = true;}
      while(ACrHNqsbrh == UJVsfrOkfk){rtLXjfZxSK = true;}
      while(kdWdgEVFxz == kdWdgEVFxz){ayfWDxednS = true;}
      while(FCLiNQmFPW == FCLiNQmFPW){AMDqTcunxr = true;}
      if(oUwEaCMOoL == true){oUwEaCMOoL = false;}
      if(juRpPyWUwG == true){juRpPyWUwG = false;}
      if(hHBUyyqIsx == true){hHBUyyqIsx = false;}
      if(DmLUsPhRDd == true){DmLUsPhRDd = false;}
      if(qGQkOKkUTP == true){qGQkOKkUTP = false;}
      if(sRJJnhTbGc == true){sRJJnhTbGc = false;}
      if(LEVqHxiwxz == true){LEVqHxiwxz = false;}
      if(QERRObpPFn == true){QERRObpPFn = false;}
      if(MVodDkdCfK == true){MVodDkdCfK = false;}
      if(wFLaSmkYdR == true){wFLaSmkYdR = false;}
      if(anXTynAqtM == true){anXTynAqtM = false;}
      if(qDWRPpOqmV == true){qDWRPpOqmV = false;}
      if(SgQlCKrqza == true){SgQlCKrqza = false;}
      if(qQlmMYxUeP == true){qQlmMYxUeP = false;}
      if(klHTTritKb == true){klHTTritKb = false;}
      if(XskHzsXkRn == true){XskHzsXkRn = false;}
      if(uIqSVaRjEp == true){uIqSVaRjEp = false;}
      if(rtLXjfZxSK == true){rtLXjfZxSK = false;}
      if(ayfWDxednS == true){ayfWDxednS = false;}
      if(AMDqTcunxr == true){AMDqTcunxr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOXXZCMYNR
{ 
  void xZYJtgjFzH()
  { 
      bool kuHWhcuTwS = false;
      bool XyeIUIzuwq = false;
      bool qmLXYWUEQP = false;
      bool aRwbBoOmsK = false;
      bool HuswPShmFN = false;
      bool oTmxTxjiyL = false;
      bool IpCgrGBCGf = false;
      bool tLCljwsOIG = false;
      bool ngyCaHezHD = false;
      bool FeogBQrMEJ = false;
      bool QefZTcQANX = false;
      bool EUarXarAGj = false;
      bool bCtDZOWUjS = false;
      bool DgJzoIAXhx = false;
      bool pdkjzjExJZ = false;
      bool XqGUgOkczF = false;
      bool GuPtTWLbCO = false;
      bool ZTRIsxQKDp = false;
      bool KYLKtMaoRa = false;
      bool XXYcptNqPc = false;
      string LthrdtLodP;
      string VuWehLHTge;
      string KUeWKjYRiU;
      string isnuiygZuE;
      string usEjNCfUep;
      string AErBoqPKgt;
      string VsFIgcHawj;
      string dgXbiQPtJI;
      string EElsUdBlGq;
      string iWrBiBmuDj;
      string tEXuMSfPRX;
      string aUAYoQHMnC;
      string aUUEAGoWsh;
      string dUqYNAgpgB;
      string ykTiQOWSLR;
      string taGBJZiStF;
      string dJWjtFcaLo;
      string jQfmEpBknl;
      string jVKanCOpPn;
      string QNuaWnOioL;
      if(LthrdtLodP == tEXuMSfPRX){kuHWhcuTwS = true;}
      else if(tEXuMSfPRX == LthrdtLodP){QefZTcQANX = true;}
      if(VuWehLHTge == aUAYoQHMnC){XyeIUIzuwq = true;}
      else if(aUAYoQHMnC == VuWehLHTge){EUarXarAGj = true;}
      if(KUeWKjYRiU == aUUEAGoWsh){qmLXYWUEQP = true;}
      else if(aUUEAGoWsh == KUeWKjYRiU){bCtDZOWUjS = true;}
      if(isnuiygZuE == dUqYNAgpgB){aRwbBoOmsK = true;}
      else if(dUqYNAgpgB == isnuiygZuE){DgJzoIAXhx = true;}
      if(usEjNCfUep == ykTiQOWSLR){HuswPShmFN = true;}
      else if(ykTiQOWSLR == usEjNCfUep){pdkjzjExJZ = true;}
      if(AErBoqPKgt == taGBJZiStF){oTmxTxjiyL = true;}
      else if(taGBJZiStF == AErBoqPKgt){XqGUgOkczF = true;}
      if(VsFIgcHawj == dJWjtFcaLo){IpCgrGBCGf = true;}
      else if(dJWjtFcaLo == VsFIgcHawj){GuPtTWLbCO = true;}
      if(dgXbiQPtJI == jQfmEpBknl){tLCljwsOIG = true;}
      if(EElsUdBlGq == jVKanCOpPn){ngyCaHezHD = true;}
      if(iWrBiBmuDj == QNuaWnOioL){FeogBQrMEJ = true;}
      while(jQfmEpBknl == dgXbiQPtJI){ZTRIsxQKDp = true;}
      while(jVKanCOpPn == jVKanCOpPn){KYLKtMaoRa = true;}
      while(QNuaWnOioL == QNuaWnOioL){XXYcptNqPc = true;}
      if(kuHWhcuTwS == true){kuHWhcuTwS = false;}
      if(XyeIUIzuwq == true){XyeIUIzuwq = false;}
      if(qmLXYWUEQP == true){qmLXYWUEQP = false;}
      if(aRwbBoOmsK == true){aRwbBoOmsK = false;}
      if(HuswPShmFN == true){HuswPShmFN = false;}
      if(oTmxTxjiyL == true){oTmxTxjiyL = false;}
      if(IpCgrGBCGf == true){IpCgrGBCGf = false;}
      if(tLCljwsOIG == true){tLCljwsOIG = false;}
      if(ngyCaHezHD == true){ngyCaHezHD = false;}
      if(FeogBQrMEJ == true){FeogBQrMEJ = false;}
      if(QefZTcQANX == true){QefZTcQANX = false;}
      if(EUarXarAGj == true){EUarXarAGj = false;}
      if(bCtDZOWUjS == true){bCtDZOWUjS = false;}
      if(DgJzoIAXhx == true){DgJzoIAXhx = false;}
      if(pdkjzjExJZ == true){pdkjzjExJZ = false;}
      if(XqGUgOkczF == true){XqGUgOkczF = false;}
      if(GuPtTWLbCO == true){GuPtTWLbCO = false;}
      if(ZTRIsxQKDp == true){ZTRIsxQKDp = false;}
      if(KYLKtMaoRa == true){KYLKtMaoRa = false;}
      if(XXYcptNqPc == true){XXYcptNqPc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOGITGZKEP
{ 
  void uTonJMhcrA()
  { 
      bool yfpfRsLKKi = false;
      bool EQYFKfnDZC = false;
      bool ZSeLONVFEz = false;
      bool HUGLQsOjER = false;
      bool BdDhFtGPOY = false;
      bool NeiWufBdQE = false;
      bool XFFLajKMnQ = false;
      bool QDzHBwPwGU = false;
      bool GFqflckjQk = false;
      bool rkSztuXrHU = false;
      bool itbxHJebVy = false;
      bool QEWwxROYYx = false;
      bool zawDYfjzNF = false;
      bool YWoklMdsYb = false;
      bool xINRUmNWCb = false;
      bool gySJVIyXYb = false;
      bool ZfOPZsOkKj = false;
      bool nUAxApMdik = false;
      bool RMxkXZEfPc = false;
      bool OGUxCRtyqa = false;
      string hEJZbBzjYJ;
      string SfhhbjiJKY;
      string tiBGKTKJAj;
      string UBcFHqRqxj;
      string INHHpKszBE;
      string smizyzCCPI;
      string qpjnnRCbZk;
      string RrLaQfatPA;
      string ZKHwpgRdHI;
      string nPaorSdSSY;
      string HRYQmBbIiR;
      string XImOhfhnyG;
      string zYURwCQWhx;
      string CIaprHlpJo;
      string FIuojfbLGL;
      string kpTLZhxGUj;
      string jEZkPOgwVZ;
      string sqdJBqdfhP;
      string ZEQVLMnOQK;
      string KfVYEBiJYV;
      if(hEJZbBzjYJ == HRYQmBbIiR){yfpfRsLKKi = true;}
      else if(HRYQmBbIiR == hEJZbBzjYJ){itbxHJebVy = true;}
      if(SfhhbjiJKY == XImOhfhnyG){EQYFKfnDZC = true;}
      else if(XImOhfhnyG == SfhhbjiJKY){QEWwxROYYx = true;}
      if(tiBGKTKJAj == zYURwCQWhx){ZSeLONVFEz = true;}
      else if(zYURwCQWhx == tiBGKTKJAj){zawDYfjzNF = true;}
      if(UBcFHqRqxj == CIaprHlpJo){HUGLQsOjER = true;}
      else if(CIaprHlpJo == UBcFHqRqxj){YWoklMdsYb = true;}
      if(INHHpKszBE == FIuojfbLGL){BdDhFtGPOY = true;}
      else if(FIuojfbLGL == INHHpKszBE){xINRUmNWCb = true;}
      if(smizyzCCPI == kpTLZhxGUj){NeiWufBdQE = true;}
      else if(kpTLZhxGUj == smizyzCCPI){gySJVIyXYb = true;}
      if(qpjnnRCbZk == jEZkPOgwVZ){XFFLajKMnQ = true;}
      else if(jEZkPOgwVZ == qpjnnRCbZk){ZfOPZsOkKj = true;}
      if(RrLaQfatPA == sqdJBqdfhP){QDzHBwPwGU = true;}
      if(ZKHwpgRdHI == ZEQVLMnOQK){GFqflckjQk = true;}
      if(nPaorSdSSY == KfVYEBiJYV){rkSztuXrHU = true;}
      while(sqdJBqdfhP == RrLaQfatPA){nUAxApMdik = true;}
      while(ZEQVLMnOQK == ZEQVLMnOQK){RMxkXZEfPc = true;}
      while(KfVYEBiJYV == KfVYEBiJYV){OGUxCRtyqa = true;}
      if(yfpfRsLKKi == true){yfpfRsLKKi = false;}
      if(EQYFKfnDZC == true){EQYFKfnDZC = false;}
      if(ZSeLONVFEz == true){ZSeLONVFEz = false;}
      if(HUGLQsOjER == true){HUGLQsOjER = false;}
      if(BdDhFtGPOY == true){BdDhFtGPOY = false;}
      if(NeiWufBdQE == true){NeiWufBdQE = false;}
      if(XFFLajKMnQ == true){XFFLajKMnQ = false;}
      if(QDzHBwPwGU == true){QDzHBwPwGU = false;}
      if(GFqflckjQk == true){GFqflckjQk = false;}
      if(rkSztuXrHU == true){rkSztuXrHU = false;}
      if(itbxHJebVy == true){itbxHJebVy = false;}
      if(QEWwxROYYx == true){QEWwxROYYx = false;}
      if(zawDYfjzNF == true){zawDYfjzNF = false;}
      if(YWoklMdsYb == true){YWoklMdsYb = false;}
      if(xINRUmNWCb == true){xINRUmNWCb = false;}
      if(gySJVIyXYb == true){gySJVIyXYb = false;}
      if(ZfOPZsOkKj == true){ZfOPZsOkKj = false;}
      if(nUAxApMdik == true){nUAxApMdik = false;}
      if(RMxkXZEfPc == true){RMxkXZEfPc = false;}
      if(OGUxCRtyqa == true){OGUxCRtyqa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSHUMCCSEJ
{ 
  void POnoWwZpbW()
  { 
      bool XxRZtHcqPo = false;
      bool hYBsHuXTUx = false;
      bool azdJpAfliX = false;
      bool ELrPPJsmeA = false;
      bool tZOfVTLrfl = false;
      bool BqJJhYTHit = false;
      bool apIrkWgldx = false;
      bool BjoTDAjxmW = false;
      bool nmFwVMBhgp = false;
      bool pkEkZDRWuz = false;
      bool mZOikQCpGh = false;
      bool oWTMFmkLVX = false;
      bool VzFmGPfDsz = false;
      bool hMBnjOYWKE = false;
      bool KKazBTQrem = false;
      bool SFBWdmTabV = false;
      bool kyxHzcUfcq = false;
      bool ONBQNKXFlm = false;
      bool ynYGfbKeKw = false;
      bool txtoTLNTzY = false;
      string qrLTnbzMki;
      string LnSPSbSNxh;
      string cnJihTjXPt;
      string HGYTVFAGfD;
      string mZCwfkAtit;
      string IoWFxDiclU;
      string rawpaEPzsM;
      string bLhttCkMCw;
      string SooUkSiSWS;
      string WWULLLcMUa;
      string UBBVSxHcLt;
      string RVZoBClbEI;
      string VxbZoEpWih;
      string YYqabRnSCn;
      string KFHcBBweJI;
      string ZBHMFXYagO;
      string GktcUrdzNj;
      string NSYQxPpzYm;
      string HLMZIWReVD;
      string sNlmhZLeHJ;
      if(qrLTnbzMki == UBBVSxHcLt){XxRZtHcqPo = true;}
      else if(UBBVSxHcLt == qrLTnbzMki){mZOikQCpGh = true;}
      if(LnSPSbSNxh == RVZoBClbEI){hYBsHuXTUx = true;}
      else if(RVZoBClbEI == LnSPSbSNxh){oWTMFmkLVX = true;}
      if(cnJihTjXPt == VxbZoEpWih){azdJpAfliX = true;}
      else if(VxbZoEpWih == cnJihTjXPt){VzFmGPfDsz = true;}
      if(HGYTVFAGfD == YYqabRnSCn){ELrPPJsmeA = true;}
      else if(YYqabRnSCn == HGYTVFAGfD){hMBnjOYWKE = true;}
      if(mZCwfkAtit == KFHcBBweJI){tZOfVTLrfl = true;}
      else if(KFHcBBweJI == mZCwfkAtit){KKazBTQrem = true;}
      if(IoWFxDiclU == ZBHMFXYagO){BqJJhYTHit = true;}
      else if(ZBHMFXYagO == IoWFxDiclU){SFBWdmTabV = true;}
      if(rawpaEPzsM == GktcUrdzNj){apIrkWgldx = true;}
      else if(GktcUrdzNj == rawpaEPzsM){kyxHzcUfcq = true;}
      if(bLhttCkMCw == NSYQxPpzYm){BjoTDAjxmW = true;}
      if(SooUkSiSWS == HLMZIWReVD){nmFwVMBhgp = true;}
      if(WWULLLcMUa == sNlmhZLeHJ){pkEkZDRWuz = true;}
      while(NSYQxPpzYm == bLhttCkMCw){ONBQNKXFlm = true;}
      while(HLMZIWReVD == HLMZIWReVD){ynYGfbKeKw = true;}
      while(sNlmhZLeHJ == sNlmhZLeHJ){txtoTLNTzY = true;}
      if(XxRZtHcqPo == true){XxRZtHcqPo = false;}
      if(hYBsHuXTUx == true){hYBsHuXTUx = false;}
      if(azdJpAfliX == true){azdJpAfliX = false;}
      if(ELrPPJsmeA == true){ELrPPJsmeA = false;}
      if(tZOfVTLrfl == true){tZOfVTLrfl = false;}
      if(BqJJhYTHit == true){BqJJhYTHit = false;}
      if(apIrkWgldx == true){apIrkWgldx = false;}
      if(BjoTDAjxmW == true){BjoTDAjxmW = false;}
      if(nmFwVMBhgp == true){nmFwVMBhgp = false;}
      if(pkEkZDRWuz == true){pkEkZDRWuz = false;}
      if(mZOikQCpGh == true){mZOikQCpGh = false;}
      if(oWTMFmkLVX == true){oWTMFmkLVX = false;}
      if(VzFmGPfDsz == true){VzFmGPfDsz = false;}
      if(hMBnjOYWKE == true){hMBnjOYWKE = false;}
      if(KKazBTQrem == true){KKazBTQrem = false;}
      if(SFBWdmTabV == true){SFBWdmTabV = false;}
      if(kyxHzcUfcq == true){kyxHzcUfcq = false;}
      if(ONBQNKXFlm == true){ONBQNKXFlm = false;}
      if(ynYGfbKeKw == true){ynYGfbKeKw = false;}
      if(txtoTLNTzY == true){txtoTLNTzY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSSCKKJVEP
{ 
  void GOOTKikxdp()
  { 
      bool AkhIbahSdc = false;
      bool LXRoTkDuYb = false;
      bool euYYMsDmJJ = false;
      bool oTdcQUEEtA = false;
      bool BmzjCCQLOB = false;
      bool sISGbELIwh = false;
      bool XuIUmrsoYz = false;
      bool fyAYZqwoWJ = false;
      bool cqXIPgAWAL = false;
      bool IwILcGeewJ = false;
      bool IamPUtHtgj = false;
      bool IWllEfWzEG = false;
      bool rVnNpjpowS = false;
      bool MQrMBCEInU = false;
      bool ZFpQCkKVHw = false;
      bool ieapRlmYYj = false;
      bool DSxNXreYkC = false;
      bool aNLiglfXKE = false;
      bool ZUgzigpCuO = false;
      bool OejDRGIbrK = false;
      string PBJqtAcYZm;
      string LRJeexnAgL;
      string qPqXBsXKia;
      string YoKKBYckwq;
      string LWVUFkpIEW;
      string igeISAKlpB;
      string bSoyNWHydG;
      string TDEoAUsVRP;
      string CPFLqrJBrA;
      string OqutPrgWHi;
      string dqeyCfbpIy;
      string HnUZyMMdHV;
      string MFGcqcHKYH;
      string mVOilLjHIK;
      string PTsssZWUwD;
      string fDPkVXkCGZ;
      string XRQALlZlmm;
      string bEUwGsLMjQ;
      string FmNVajGdMO;
      string ahBhlxDrhH;
      if(PBJqtAcYZm == dqeyCfbpIy){AkhIbahSdc = true;}
      else if(dqeyCfbpIy == PBJqtAcYZm){IamPUtHtgj = true;}
      if(LRJeexnAgL == HnUZyMMdHV){LXRoTkDuYb = true;}
      else if(HnUZyMMdHV == LRJeexnAgL){IWllEfWzEG = true;}
      if(qPqXBsXKia == MFGcqcHKYH){euYYMsDmJJ = true;}
      else if(MFGcqcHKYH == qPqXBsXKia){rVnNpjpowS = true;}
      if(YoKKBYckwq == mVOilLjHIK){oTdcQUEEtA = true;}
      else if(mVOilLjHIK == YoKKBYckwq){MQrMBCEInU = true;}
      if(LWVUFkpIEW == PTsssZWUwD){BmzjCCQLOB = true;}
      else if(PTsssZWUwD == LWVUFkpIEW){ZFpQCkKVHw = true;}
      if(igeISAKlpB == fDPkVXkCGZ){sISGbELIwh = true;}
      else if(fDPkVXkCGZ == igeISAKlpB){ieapRlmYYj = true;}
      if(bSoyNWHydG == XRQALlZlmm){XuIUmrsoYz = true;}
      else if(XRQALlZlmm == bSoyNWHydG){DSxNXreYkC = true;}
      if(TDEoAUsVRP == bEUwGsLMjQ){fyAYZqwoWJ = true;}
      if(CPFLqrJBrA == FmNVajGdMO){cqXIPgAWAL = true;}
      if(OqutPrgWHi == ahBhlxDrhH){IwILcGeewJ = true;}
      while(bEUwGsLMjQ == TDEoAUsVRP){aNLiglfXKE = true;}
      while(FmNVajGdMO == FmNVajGdMO){ZUgzigpCuO = true;}
      while(ahBhlxDrhH == ahBhlxDrhH){OejDRGIbrK = true;}
      if(AkhIbahSdc == true){AkhIbahSdc = false;}
      if(LXRoTkDuYb == true){LXRoTkDuYb = false;}
      if(euYYMsDmJJ == true){euYYMsDmJJ = false;}
      if(oTdcQUEEtA == true){oTdcQUEEtA = false;}
      if(BmzjCCQLOB == true){BmzjCCQLOB = false;}
      if(sISGbELIwh == true){sISGbELIwh = false;}
      if(XuIUmrsoYz == true){XuIUmrsoYz = false;}
      if(fyAYZqwoWJ == true){fyAYZqwoWJ = false;}
      if(cqXIPgAWAL == true){cqXIPgAWAL = false;}
      if(IwILcGeewJ == true){IwILcGeewJ = false;}
      if(IamPUtHtgj == true){IamPUtHtgj = false;}
      if(IWllEfWzEG == true){IWllEfWzEG = false;}
      if(rVnNpjpowS == true){rVnNpjpowS = false;}
      if(MQrMBCEInU == true){MQrMBCEInU = false;}
      if(ZFpQCkKVHw == true){ZFpQCkKVHw = false;}
      if(ieapRlmYYj == true){ieapRlmYYj = false;}
      if(DSxNXreYkC == true){DSxNXreYkC = false;}
      if(aNLiglfXKE == true){aNLiglfXKE = false;}
      if(ZUgzigpCuO == true){ZUgzigpCuO = false;}
      if(OejDRGIbrK == true){OejDRGIbrK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITKQJMLETD
{ 
  void RxKnebSZQR()
  { 
      bool ZTmVwVNxHl = false;
      bool GeeLDnBPwa = false;
      bool hKBTRPUVif = false;
      bool fJECgqYMnO = false;
      bool VKsiVbVwzc = false;
      bool iLINFPRTDg = false;
      bool ArObFwZbeL = false;
      bool OoahEXRSxo = false;
      bool sYWFwTAqwR = false;
      bool ZFIHOduRcY = false;
      bool BtQmOtkaIh = false;
      bool yzVNmaUIel = false;
      bool wieMlJfSTZ = false;
      bool bzoXnzHjqC = false;
      bool iZhOTZjtTm = false;
      bool JmlqcSOEAE = false;
      bool NRGhGyJxZn = false;
      bool TkQcDVAQsL = false;
      bool YlygQnNyuU = false;
      bool jDiloQSAIV = false;
      string mpVGnsRzNn;
      string rIppSlPXyl;
      string zSQnsnuWbh;
      string UdFOuzIqxy;
      string zAwetYrjgs;
      string UmADgTYgNz;
      string xtXeTOCauT;
      string cYazmzWltT;
      string wKohNgcBha;
      string ZbcxAEcQLe;
      string VQoNPuMAPh;
      string xmlsDlFpRl;
      string kBsTtBuczi;
      string WGaPxeVbRR;
      string UclAdlpitN;
      string ylyYtUXUTO;
      string AjBgLpMWwY;
      string QcYAQHOspH;
      string LMhkjjIBUb;
      string GAICQkbFnn;
      if(mpVGnsRzNn == VQoNPuMAPh){ZTmVwVNxHl = true;}
      else if(VQoNPuMAPh == mpVGnsRzNn){BtQmOtkaIh = true;}
      if(rIppSlPXyl == xmlsDlFpRl){GeeLDnBPwa = true;}
      else if(xmlsDlFpRl == rIppSlPXyl){yzVNmaUIel = true;}
      if(zSQnsnuWbh == kBsTtBuczi){hKBTRPUVif = true;}
      else if(kBsTtBuczi == zSQnsnuWbh){wieMlJfSTZ = true;}
      if(UdFOuzIqxy == WGaPxeVbRR){fJECgqYMnO = true;}
      else if(WGaPxeVbRR == UdFOuzIqxy){bzoXnzHjqC = true;}
      if(zAwetYrjgs == UclAdlpitN){VKsiVbVwzc = true;}
      else if(UclAdlpitN == zAwetYrjgs){iZhOTZjtTm = true;}
      if(UmADgTYgNz == ylyYtUXUTO){iLINFPRTDg = true;}
      else if(ylyYtUXUTO == UmADgTYgNz){JmlqcSOEAE = true;}
      if(xtXeTOCauT == AjBgLpMWwY){ArObFwZbeL = true;}
      else if(AjBgLpMWwY == xtXeTOCauT){NRGhGyJxZn = true;}
      if(cYazmzWltT == QcYAQHOspH){OoahEXRSxo = true;}
      if(wKohNgcBha == LMhkjjIBUb){sYWFwTAqwR = true;}
      if(ZbcxAEcQLe == GAICQkbFnn){ZFIHOduRcY = true;}
      while(QcYAQHOspH == cYazmzWltT){TkQcDVAQsL = true;}
      while(LMhkjjIBUb == LMhkjjIBUb){YlygQnNyuU = true;}
      while(GAICQkbFnn == GAICQkbFnn){jDiloQSAIV = true;}
      if(ZTmVwVNxHl == true){ZTmVwVNxHl = false;}
      if(GeeLDnBPwa == true){GeeLDnBPwa = false;}
      if(hKBTRPUVif == true){hKBTRPUVif = false;}
      if(fJECgqYMnO == true){fJECgqYMnO = false;}
      if(VKsiVbVwzc == true){VKsiVbVwzc = false;}
      if(iLINFPRTDg == true){iLINFPRTDg = false;}
      if(ArObFwZbeL == true){ArObFwZbeL = false;}
      if(OoahEXRSxo == true){OoahEXRSxo = false;}
      if(sYWFwTAqwR == true){sYWFwTAqwR = false;}
      if(ZFIHOduRcY == true){ZFIHOduRcY = false;}
      if(BtQmOtkaIh == true){BtQmOtkaIh = false;}
      if(yzVNmaUIel == true){yzVNmaUIel = false;}
      if(wieMlJfSTZ == true){wieMlJfSTZ = false;}
      if(bzoXnzHjqC == true){bzoXnzHjqC = false;}
      if(iZhOTZjtTm == true){iZhOTZjtTm = false;}
      if(JmlqcSOEAE == true){JmlqcSOEAE = false;}
      if(NRGhGyJxZn == true){NRGhGyJxZn = false;}
      if(TkQcDVAQsL == true){TkQcDVAQsL = false;}
      if(YlygQnNyuU == true){YlygQnNyuU = false;}
      if(jDiloQSAIV == true){jDiloQSAIV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDAOWOELHO
{ 
  void toPGwLKNnV()
  { 
      bool XNljwMXCxr = false;
      bool gESfrQUxSz = false;
      bool FujxtDxGuM = false;
      bool UJxdwLDUwl = false;
      bool kKAVLxxsPt = false;
      bool PmGwFbdopr = false;
      bool PQGjWXHnjg = false;
      bool NAAgOuuOlx = false;
      bool GEqAwgDAXT = false;
      bool hOeDVUDPzn = false;
      bool oIJigPlYhJ = false;
      bool gPDrlLZGmo = false;
      bool TGQPyyUwKt = false;
      bool reOxHytHSg = false;
      bool tdSOmSLlRK = false;
      bool twcJThqski = false;
      bool tpNnRBAFjn = false;
      bool QRnGtpnCce = false;
      bool lieAzuCFcZ = false;
      bool GBVjlEPewk = false;
      string DUjNnqmXhe;
      string seqxXmWhCA;
      string cJkfNxFgyO;
      string xkJlMkbbTp;
      string kDDmnMBJWQ;
      string UZKPdtiDzq;
      string kFYThHUFjl;
      string KuNMOZFyrA;
      string uuJhsXZsHR;
      string BXbbEfdjFf;
      string quYjFZLyBD;
      string nkLzuouqZJ;
      string hbxRjmSlHi;
      string uVrMIzWYbS;
      string LbrEcQMcfO;
      string jmJuyPyGAS;
      string HZpSISrypw;
      string SWPHyGisnT;
      string ZpFszIMxNr;
      string BPYILkkZwK;
      if(DUjNnqmXhe == quYjFZLyBD){XNljwMXCxr = true;}
      else if(quYjFZLyBD == DUjNnqmXhe){oIJigPlYhJ = true;}
      if(seqxXmWhCA == nkLzuouqZJ){gESfrQUxSz = true;}
      else if(nkLzuouqZJ == seqxXmWhCA){gPDrlLZGmo = true;}
      if(cJkfNxFgyO == hbxRjmSlHi){FujxtDxGuM = true;}
      else if(hbxRjmSlHi == cJkfNxFgyO){TGQPyyUwKt = true;}
      if(xkJlMkbbTp == uVrMIzWYbS){UJxdwLDUwl = true;}
      else if(uVrMIzWYbS == xkJlMkbbTp){reOxHytHSg = true;}
      if(kDDmnMBJWQ == LbrEcQMcfO){kKAVLxxsPt = true;}
      else if(LbrEcQMcfO == kDDmnMBJWQ){tdSOmSLlRK = true;}
      if(UZKPdtiDzq == jmJuyPyGAS){PmGwFbdopr = true;}
      else if(jmJuyPyGAS == UZKPdtiDzq){twcJThqski = true;}
      if(kFYThHUFjl == HZpSISrypw){PQGjWXHnjg = true;}
      else if(HZpSISrypw == kFYThHUFjl){tpNnRBAFjn = true;}
      if(KuNMOZFyrA == SWPHyGisnT){NAAgOuuOlx = true;}
      if(uuJhsXZsHR == ZpFszIMxNr){GEqAwgDAXT = true;}
      if(BXbbEfdjFf == BPYILkkZwK){hOeDVUDPzn = true;}
      while(SWPHyGisnT == KuNMOZFyrA){QRnGtpnCce = true;}
      while(ZpFszIMxNr == ZpFszIMxNr){lieAzuCFcZ = true;}
      while(BPYILkkZwK == BPYILkkZwK){GBVjlEPewk = true;}
      if(XNljwMXCxr == true){XNljwMXCxr = false;}
      if(gESfrQUxSz == true){gESfrQUxSz = false;}
      if(FujxtDxGuM == true){FujxtDxGuM = false;}
      if(UJxdwLDUwl == true){UJxdwLDUwl = false;}
      if(kKAVLxxsPt == true){kKAVLxxsPt = false;}
      if(PmGwFbdopr == true){PmGwFbdopr = false;}
      if(PQGjWXHnjg == true){PQGjWXHnjg = false;}
      if(NAAgOuuOlx == true){NAAgOuuOlx = false;}
      if(GEqAwgDAXT == true){GEqAwgDAXT = false;}
      if(hOeDVUDPzn == true){hOeDVUDPzn = false;}
      if(oIJigPlYhJ == true){oIJigPlYhJ = false;}
      if(gPDrlLZGmo == true){gPDrlLZGmo = false;}
      if(TGQPyyUwKt == true){TGQPyyUwKt = false;}
      if(reOxHytHSg == true){reOxHytHSg = false;}
      if(tdSOmSLlRK == true){tdSOmSLlRK = false;}
      if(twcJThqski == true){twcJThqski = false;}
      if(tpNnRBAFjn == true){tpNnRBAFjn = false;}
      if(QRnGtpnCce == true){QRnGtpnCce = false;}
      if(lieAzuCFcZ == true){lieAzuCFcZ = false;}
      if(GBVjlEPewk == true){GBVjlEPewk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFOITKXODK
{ 
  void LRJHkdLWIo()
  { 
      bool rQVDUxscpA = false;
      bool BArpEpitnz = false;
      bool CMaQqmYQxb = false;
      bool PzSDYfzSmT = false;
      bool BfsdgpTmFt = false;
      bool SefwdepEMh = false;
      bool XbeNkCgoQY = false;
      bool qQHTyVSwjB = false;
      bool SlKCJjTWZs = false;
      bool ouGFuYAesd = false;
      bool IeWgDCXLyH = false;
      bool LtUKOlQcEA = false;
      bool hKPWjwJBYY = false;
      bool UnCFsnOdzG = false;
      bool MIYRguZuqJ = false;
      bool IXZsuxOzwH = false;
      bool rWlYlXqORZ = false;
      bool WmcxmZlxpo = false;
      bool VOKPQxNIJu = false;
      bool YPgrNpVzfJ = false;
      string OsZoPSutuW;
      string EHoDGYIUaa;
      string GbcSTAmKWQ;
      string PbTiHIGsnn;
      string XgTPlBZxLn;
      string QtSYimQHUO;
      string ekWdHcmFuy;
      string SOglDYINfR;
      string apyhzUJuAU;
      string ryXYJlJoHJ;
      string NUBNVCNfVJ;
      string dCbDnnmnel;
      string SrFZGTpHcQ;
      string PSFVDFnjMx;
      string HcYppoWUkU;
      string zUKVpVPbHB;
      string LFDEtKxFzh;
      string zCbhepTOiQ;
      string wVWIQtIjeh;
      string pMcKkCZTuf;
      if(OsZoPSutuW == NUBNVCNfVJ){rQVDUxscpA = true;}
      else if(NUBNVCNfVJ == OsZoPSutuW){IeWgDCXLyH = true;}
      if(EHoDGYIUaa == dCbDnnmnel){BArpEpitnz = true;}
      else if(dCbDnnmnel == EHoDGYIUaa){LtUKOlQcEA = true;}
      if(GbcSTAmKWQ == SrFZGTpHcQ){CMaQqmYQxb = true;}
      else if(SrFZGTpHcQ == GbcSTAmKWQ){hKPWjwJBYY = true;}
      if(PbTiHIGsnn == PSFVDFnjMx){PzSDYfzSmT = true;}
      else if(PSFVDFnjMx == PbTiHIGsnn){UnCFsnOdzG = true;}
      if(XgTPlBZxLn == HcYppoWUkU){BfsdgpTmFt = true;}
      else if(HcYppoWUkU == XgTPlBZxLn){MIYRguZuqJ = true;}
      if(QtSYimQHUO == zUKVpVPbHB){SefwdepEMh = true;}
      else if(zUKVpVPbHB == QtSYimQHUO){IXZsuxOzwH = true;}
      if(ekWdHcmFuy == LFDEtKxFzh){XbeNkCgoQY = true;}
      else if(LFDEtKxFzh == ekWdHcmFuy){rWlYlXqORZ = true;}
      if(SOglDYINfR == zCbhepTOiQ){qQHTyVSwjB = true;}
      if(apyhzUJuAU == wVWIQtIjeh){SlKCJjTWZs = true;}
      if(ryXYJlJoHJ == pMcKkCZTuf){ouGFuYAesd = true;}
      while(zCbhepTOiQ == SOglDYINfR){WmcxmZlxpo = true;}
      while(wVWIQtIjeh == wVWIQtIjeh){VOKPQxNIJu = true;}
      while(pMcKkCZTuf == pMcKkCZTuf){YPgrNpVzfJ = true;}
      if(rQVDUxscpA == true){rQVDUxscpA = false;}
      if(BArpEpitnz == true){BArpEpitnz = false;}
      if(CMaQqmYQxb == true){CMaQqmYQxb = false;}
      if(PzSDYfzSmT == true){PzSDYfzSmT = false;}
      if(BfsdgpTmFt == true){BfsdgpTmFt = false;}
      if(SefwdepEMh == true){SefwdepEMh = false;}
      if(XbeNkCgoQY == true){XbeNkCgoQY = false;}
      if(qQHTyVSwjB == true){qQHTyVSwjB = false;}
      if(SlKCJjTWZs == true){SlKCJjTWZs = false;}
      if(ouGFuYAesd == true){ouGFuYAesd = false;}
      if(IeWgDCXLyH == true){IeWgDCXLyH = false;}
      if(LtUKOlQcEA == true){LtUKOlQcEA = false;}
      if(hKPWjwJBYY == true){hKPWjwJBYY = false;}
      if(UnCFsnOdzG == true){UnCFsnOdzG = false;}
      if(MIYRguZuqJ == true){MIYRguZuqJ = false;}
      if(IXZsuxOzwH == true){IXZsuxOzwH = false;}
      if(rWlYlXqORZ == true){rWlYlXqORZ = false;}
      if(WmcxmZlxpo == true){WmcxmZlxpo = false;}
      if(VOKPQxNIJu == true){VOKPQxNIJu = false;}
      if(YPgrNpVzfJ == true){YPgrNpVzfJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIQDDICROX
{ 
  void SeuiScmOea()
  { 
      bool MSkPIsdxPr = false;
      bool qoTeudyYVh = false;
      bool ZplxnFYJtl = false;
      bool qatBwBbaii = false;
      bool WlGTOGmGQO = false;
      bool sBimNWfnaC = false;
      bool TUDcAQtRhs = false;
      bool CXpmLmjSig = false;
      bool RSrespqHnZ = false;
      bool UnzfOBidSx = false;
      bool LVXWMULwaZ = false;
      bool lNEskBbXjK = false;
      bool YmcHXOYJXK = false;
      bool EGzkVwtVSX = false;
      bool etgOmHiFuN = false;
      bool YKtIYYrPzy = false;
      bool wBYQUfOSXn = false;
      bool GGFLedFNUQ = false;
      bool eSOJktLpMw = false;
      bool DdVUbcVPsG = false;
      string HFBfcArcLq;
      string pueuuZUexn;
      string OxDoLNNKEE;
      string TLdUjHzsCk;
      string UTReyYjEMa;
      string WHpwfJCMUP;
      string lgYGXdQJKn;
      string ZbbMSufXpl;
      string cJxcgLUgoZ;
      string EmXlymuKGT;
      string HasXBueddj;
      string ddVhlcjuZL;
      string IjUkjlDpNf;
      string AUQWdCPZak;
      string gqDEwZRozV;
      string DzktKXFInP;
      string roQyiIMyDj;
      string MKUneRfPoJ;
      string UNpqbBiWMG;
      string wHkLsrZFUm;
      if(HFBfcArcLq == HasXBueddj){MSkPIsdxPr = true;}
      else if(HasXBueddj == HFBfcArcLq){LVXWMULwaZ = true;}
      if(pueuuZUexn == ddVhlcjuZL){qoTeudyYVh = true;}
      else if(ddVhlcjuZL == pueuuZUexn){lNEskBbXjK = true;}
      if(OxDoLNNKEE == IjUkjlDpNf){ZplxnFYJtl = true;}
      else if(IjUkjlDpNf == OxDoLNNKEE){YmcHXOYJXK = true;}
      if(TLdUjHzsCk == AUQWdCPZak){qatBwBbaii = true;}
      else if(AUQWdCPZak == TLdUjHzsCk){EGzkVwtVSX = true;}
      if(UTReyYjEMa == gqDEwZRozV){WlGTOGmGQO = true;}
      else if(gqDEwZRozV == UTReyYjEMa){etgOmHiFuN = true;}
      if(WHpwfJCMUP == DzktKXFInP){sBimNWfnaC = true;}
      else if(DzktKXFInP == WHpwfJCMUP){YKtIYYrPzy = true;}
      if(lgYGXdQJKn == roQyiIMyDj){TUDcAQtRhs = true;}
      else if(roQyiIMyDj == lgYGXdQJKn){wBYQUfOSXn = true;}
      if(ZbbMSufXpl == MKUneRfPoJ){CXpmLmjSig = true;}
      if(cJxcgLUgoZ == UNpqbBiWMG){RSrespqHnZ = true;}
      if(EmXlymuKGT == wHkLsrZFUm){UnzfOBidSx = true;}
      while(MKUneRfPoJ == ZbbMSufXpl){GGFLedFNUQ = true;}
      while(UNpqbBiWMG == UNpqbBiWMG){eSOJktLpMw = true;}
      while(wHkLsrZFUm == wHkLsrZFUm){DdVUbcVPsG = true;}
      if(MSkPIsdxPr == true){MSkPIsdxPr = false;}
      if(qoTeudyYVh == true){qoTeudyYVh = false;}
      if(ZplxnFYJtl == true){ZplxnFYJtl = false;}
      if(qatBwBbaii == true){qatBwBbaii = false;}
      if(WlGTOGmGQO == true){WlGTOGmGQO = false;}
      if(sBimNWfnaC == true){sBimNWfnaC = false;}
      if(TUDcAQtRhs == true){TUDcAQtRhs = false;}
      if(CXpmLmjSig == true){CXpmLmjSig = false;}
      if(RSrespqHnZ == true){RSrespqHnZ = false;}
      if(UnzfOBidSx == true){UnzfOBidSx = false;}
      if(LVXWMULwaZ == true){LVXWMULwaZ = false;}
      if(lNEskBbXjK == true){lNEskBbXjK = false;}
      if(YmcHXOYJXK == true){YmcHXOYJXK = false;}
      if(EGzkVwtVSX == true){EGzkVwtVSX = false;}
      if(etgOmHiFuN == true){etgOmHiFuN = false;}
      if(YKtIYYrPzy == true){YKtIYYrPzy = false;}
      if(wBYQUfOSXn == true){wBYQUfOSXn = false;}
      if(GGFLedFNUQ == true){GGFLedFNUQ = false;}
      if(eSOJktLpMw == true){eSOJktLpMw = false;}
      if(DdVUbcVPsG == true){DdVUbcVPsG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BEYZDQOYRG
{ 
  void GwfGmYfCFM()
  { 
      bool teMHSVtoAd = false;
      bool YZKLIKzUzm = false;
      bool fnRkuIAqIj = false;
      bool jVyZoqntKy = false;
      bool NPolpTkADw = false;
      bool ZwuMfFNaMK = false;
      bool VDgQtDbkWR = false;
      bool VEKBYQyfub = false;
      bool XznLJnakti = false;
      bool cMhAbKhXql = false;
      bool qzdlaUktmP = false;
      bool GgfjlVPVHF = false;
      bool cqqmnJWJYO = false;
      bool hanIkXVBkn = false;
      bool CfxdbwfxNG = false;
      bool uMQlJAIqyQ = false;
      bool ybUYhfsXzO = false;
      bool ANkSCwsMKr = false;
      bool cYuRSUJCyj = false;
      bool OeDToaLYww = false;
      string IrslhBCzXG;
      string KYsUonfACp;
      string yMPWGqhWwy;
      string ndLCpeNyuk;
      string iwNQcgHKMp;
      string GHPbEucWep;
      string SfCZSfNqdJ;
      string agFRGByysY;
      string iXKGqfOiyt;
      string CqTERDtnyx;
      string TQfCOYCyVC;
      string wddGHuUuhm;
      string RdsjHjNAzC;
      string HKAuFRqHqS;
      string cPNuxXMNxV;
      string iyFKfpXwue;
      string KCySuldhAo;
      string DMDPJBQxli;
      string WACcTIFpPP;
      string tuMMHZQtzL;
      if(IrslhBCzXG == TQfCOYCyVC){teMHSVtoAd = true;}
      else if(TQfCOYCyVC == IrslhBCzXG){qzdlaUktmP = true;}
      if(KYsUonfACp == wddGHuUuhm){YZKLIKzUzm = true;}
      else if(wddGHuUuhm == KYsUonfACp){GgfjlVPVHF = true;}
      if(yMPWGqhWwy == RdsjHjNAzC){fnRkuIAqIj = true;}
      else if(RdsjHjNAzC == yMPWGqhWwy){cqqmnJWJYO = true;}
      if(ndLCpeNyuk == HKAuFRqHqS){jVyZoqntKy = true;}
      else if(HKAuFRqHqS == ndLCpeNyuk){hanIkXVBkn = true;}
      if(iwNQcgHKMp == cPNuxXMNxV){NPolpTkADw = true;}
      else if(cPNuxXMNxV == iwNQcgHKMp){CfxdbwfxNG = true;}
      if(GHPbEucWep == iyFKfpXwue){ZwuMfFNaMK = true;}
      else if(iyFKfpXwue == GHPbEucWep){uMQlJAIqyQ = true;}
      if(SfCZSfNqdJ == KCySuldhAo){VDgQtDbkWR = true;}
      else if(KCySuldhAo == SfCZSfNqdJ){ybUYhfsXzO = true;}
      if(agFRGByysY == DMDPJBQxli){VEKBYQyfub = true;}
      if(iXKGqfOiyt == WACcTIFpPP){XznLJnakti = true;}
      if(CqTERDtnyx == tuMMHZQtzL){cMhAbKhXql = true;}
      while(DMDPJBQxli == agFRGByysY){ANkSCwsMKr = true;}
      while(WACcTIFpPP == WACcTIFpPP){cYuRSUJCyj = true;}
      while(tuMMHZQtzL == tuMMHZQtzL){OeDToaLYww = true;}
      if(teMHSVtoAd == true){teMHSVtoAd = false;}
      if(YZKLIKzUzm == true){YZKLIKzUzm = false;}
      if(fnRkuIAqIj == true){fnRkuIAqIj = false;}
      if(jVyZoqntKy == true){jVyZoqntKy = false;}
      if(NPolpTkADw == true){NPolpTkADw = false;}
      if(ZwuMfFNaMK == true){ZwuMfFNaMK = false;}
      if(VDgQtDbkWR == true){VDgQtDbkWR = false;}
      if(VEKBYQyfub == true){VEKBYQyfub = false;}
      if(XznLJnakti == true){XznLJnakti = false;}
      if(cMhAbKhXql == true){cMhAbKhXql = false;}
      if(qzdlaUktmP == true){qzdlaUktmP = false;}
      if(GgfjlVPVHF == true){GgfjlVPVHF = false;}
      if(cqqmnJWJYO == true){cqqmnJWJYO = false;}
      if(hanIkXVBkn == true){hanIkXVBkn = false;}
      if(CfxdbwfxNG == true){CfxdbwfxNG = false;}
      if(uMQlJAIqyQ == true){uMQlJAIqyQ = false;}
      if(ybUYhfsXzO == true){ybUYhfsXzO = false;}
      if(ANkSCwsMKr == true){ANkSCwsMKr = false;}
      if(cYuRSUJCyj == true){cYuRSUJCyj = false;}
      if(OeDToaLYww == true){OeDToaLYww = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXYJHWBGZG
{ 
  void PNEgeTEMGL()
  { 
      bool SrjNRRQdhf = false;
      bool ysFkerHHLF = false;
      bool EpHKPEWjiG = false;
      bool ZWPlRjgzsh = false;
      bool huaEsIEEyr = false;
      bool dTMTmcjYyN = false;
      bool tgtaFadTSt = false;
      bool KHOdXIODRH = false;
      bool zSlqcFKwyo = false;
      bool AIBemAAAyR = false;
      bool ekkDhVFiue = false;
      bool NgGpNbtDxz = false;
      bool QgUdtCGipW = false;
      bool HOEAcOghIH = false;
      bool AbATaSBKRK = false;
      bool FxCyBxPHIe = false;
      bool PVrXWzcGNy = false;
      bool uLtpzngBCb = false;
      bool AuReQKLFzf = false;
      bool zYYdqdibxa = false;
      string RdwpDOOkZR;
      string ysbjnNCrAg;
      string lbqkpQfJgA;
      string CuoyNlFYTV;
      string EfnlkeeEZb;
      string qkoQmpmKzm;
      string hFDYODEdWB;
      string HdYebFnFAL;
      string kaiFIRFXKX;
      string ztZfmzcPWg;
      string ZBhXTNMKng;
      string CgKmBHVyPx;
      string yfSzCMDrqc;
      string cYhSkjsKku;
      string FujdURjlef;
      string cdzZithiVH;
      string JTSLEdyqCR;
      string NLNUrCwodk;
      string cRMKzyYIjq;
      string BJockkbYYq;
      if(RdwpDOOkZR == ZBhXTNMKng){SrjNRRQdhf = true;}
      else if(ZBhXTNMKng == RdwpDOOkZR){ekkDhVFiue = true;}
      if(ysbjnNCrAg == CgKmBHVyPx){ysFkerHHLF = true;}
      else if(CgKmBHVyPx == ysbjnNCrAg){NgGpNbtDxz = true;}
      if(lbqkpQfJgA == yfSzCMDrqc){EpHKPEWjiG = true;}
      else if(yfSzCMDrqc == lbqkpQfJgA){QgUdtCGipW = true;}
      if(CuoyNlFYTV == cYhSkjsKku){ZWPlRjgzsh = true;}
      else if(cYhSkjsKku == CuoyNlFYTV){HOEAcOghIH = true;}
      if(EfnlkeeEZb == FujdURjlef){huaEsIEEyr = true;}
      else if(FujdURjlef == EfnlkeeEZb){AbATaSBKRK = true;}
      if(qkoQmpmKzm == cdzZithiVH){dTMTmcjYyN = true;}
      else if(cdzZithiVH == qkoQmpmKzm){FxCyBxPHIe = true;}
      if(hFDYODEdWB == JTSLEdyqCR){tgtaFadTSt = true;}
      else if(JTSLEdyqCR == hFDYODEdWB){PVrXWzcGNy = true;}
      if(HdYebFnFAL == NLNUrCwodk){KHOdXIODRH = true;}
      if(kaiFIRFXKX == cRMKzyYIjq){zSlqcFKwyo = true;}
      if(ztZfmzcPWg == BJockkbYYq){AIBemAAAyR = true;}
      while(NLNUrCwodk == HdYebFnFAL){uLtpzngBCb = true;}
      while(cRMKzyYIjq == cRMKzyYIjq){AuReQKLFzf = true;}
      while(BJockkbYYq == BJockkbYYq){zYYdqdibxa = true;}
      if(SrjNRRQdhf == true){SrjNRRQdhf = false;}
      if(ysFkerHHLF == true){ysFkerHHLF = false;}
      if(EpHKPEWjiG == true){EpHKPEWjiG = false;}
      if(ZWPlRjgzsh == true){ZWPlRjgzsh = false;}
      if(huaEsIEEyr == true){huaEsIEEyr = false;}
      if(dTMTmcjYyN == true){dTMTmcjYyN = false;}
      if(tgtaFadTSt == true){tgtaFadTSt = false;}
      if(KHOdXIODRH == true){KHOdXIODRH = false;}
      if(zSlqcFKwyo == true){zSlqcFKwyo = false;}
      if(AIBemAAAyR == true){AIBemAAAyR = false;}
      if(ekkDhVFiue == true){ekkDhVFiue = false;}
      if(NgGpNbtDxz == true){NgGpNbtDxz = false;}
      if(QgUdtCGipW == true){QgUdtCGipW = false;}
      if(HOEAcOghIH == true){HOEAcOghIH = false;}
      if(AbATaSBKRK == true){AbATaSBKRK = false;}
      if(FxCyBxPHIe == true){FxCyBxPHIe = false;}
      if(PVrXWzcGNy == true){PVrXWzcGNy = false;}
      if(uLtpzngBCb == true){uLtpzngBCb = false;}
      if(AuReQKLFzf == true){AuReQKLFzf = false;}
      if(zYYdqdibxa == true){zYYdqdibxa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGORYFPLWL
{ 
  void sawAtyXJrq()
  { 
      bool MbEdtddqCn = false;
      bool clTehoeIJh = false;
      bool twgDIMjiuu = false;
      bool ufixtVOxes = false;
      bool uUIMajOncD = false;
      bool IAEsyPtBUh = false;
      bool stuHsxCVkL = false;
      bool ZhcQlZnUbY = false;
      bool ywFqltapze = false;
      bool bNcxzAYATc = false;
      bool grDQdaXnGX = false;
      bool aYYujxoDUy = false;
      bool VMWFjLEfQl = false;
      bool AmBzqFroNL = false;
      bool WljaDDngMC = false;
      bool LUfUHUVxgR = false;
      bool VqXTWmWZEd = false;
      bool FApJbjbuBf = false;
      bool XXSOafHgqV = false;
      bool jtHupfNPDQ = false;
      string bDHIaxFdli;
      string yDYtiksClV;
      string iPoziWXbMF;
      string TSZwIksSKz;
      string VbCdSrQiJg;
      string OhhoKLOHYD;
      string ZcRfOfcckx;
      string rZqmAHNKfp;
      string GnRfpkkkkw;
      string WktGYsKVOm;
      string PnxMnoqtnD;
      string yDahxkKlpc;
      string tqqnZHfjNG;
      string xqwsaSqFqB;
      string tpwgyTJLIn;
      string iXfkrXwJlf;
      string IGghGGHhGe;
      string tEtniEtJoG;
      string xTaYXYLKAD;
      string VhTLrnIOar;
      if(bDHIaxFdli == PnxMnoqtnD){MbEdtddqCn = true;}
      else if(PnxMnoqtnD == bDHIaxFdli){grDQdaXnGX = true;}
      if(yDYtiksClV == yDahxkKlpc){clTehoeIJh = true;}
      else if(yDahxkKlpc == yDYtiksClV){aYYujxoDUy = true;}
      if(iPoziWXbMF == tqqnZHfjNG){twgDIMjiuu = true;}
      else if(tqqnZHfjNG == iPoziWXbMF){VMWFjLEfQl = true;}
      if(TSZwIksSKz == xqwsaSqFqB){ufixtVOxes = true;}
      else if(xqwsaSqFqB == TSZwIksSKz){AmBzqFroNL = true;}
      if(VbCdSrQiJg == tpwgyTJLIn){uUIMajOncD = true;}
      else if(tpwgyTJLIn == VbCdSrQiJg){WljaDDngMC = true;}
      if(OhhoKLOHYD == iXfkrXwJlf){IAEsyPtBUh = true;}
      else if(iXfkrXwJlf == OhhoKLOHYD){LUfUHUVxgR = true;}
      if(ZcRfOfcckx == IGghGGHhGe){stuHsxCVkL = true;}
      else if(IGghGGHhGe == ZcRfOfcckx){VqXTWmWZEd = true;}
      if(rZqmAHNKfp == tEtniEtJoG){ZhcQlZnUbY = true;}
      if(GnRfpkkkkw == xTaYXYLKAD){ywFqltapze = true;}
      if(WktGYsKVOm == VhTLrnIOar){bNcxzAYATc = true;}
      while(tEtniEtJoG == rZqmAHNKfp){FApJbjbuBf = true;}
      while(xTaYXYLKAD == xTaYXYLKAD){XXSOafHgqV = true;}
      while(VhTLrnIOar == VhTLrnIOar){jtHupfNPDQ = true;}
      if(MbEdtddqCn == true){MbEdtddqCn = false;}
      if(clTehoeIJh == true){clTehoeIJh = false;}
      if(twgDIMjiuu == true){twgDIMjiuu = false;}
      if(ufixtVOxes == true){ufixtVOxes = false;}
      if(uUIMajOncD == true){uUIMajOncD = false;}
      if(IAEsyPtBUh == true){IAEsyPtBUh = false;}
      if(stuHsxCVkL == true){stuHsxCVkL = false;}
      if(ZhcQlZnUbY == true){ZhcQlZnUbY = false;}
      if(ywFqltapze == true){ywFqltapze = false;}
      if(bNcxzAYATc == true){bNcxzAYATc = false;}
      if(grDQdaXnGX == true){grDQdaXnGX = false;}
      if(aYYujxoDUy == true){aYYujxoDUy = false;}
      if(VMWFjLEfQl == true){VMWFjLEfQl = false;}
      if(AmBzqFroNL == true){AmBzqFroNL = false;}
      if(WljaDDngMC == true){WljaDDngMC = false;}
      if(LUfUHUVxgR == true){LUfUHUVxgR = false;}
      if(VqXTWmWZEd == true){VqXTWmWZEd = false;}
      if(FApJbjbuBf == true){FApJbjbuBf = false;}
      if(XXSOafHgqV == true){XXSOafHgqV = false;}
      if(jtHupfNPDQ == true){jtHupfNPDQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQLQXIIAWV
{ 
  void FLLKGieWLI()
  { 
      bool PzIfAFtIzH = false;
      bool tHHEcfFYBU = false;
      bool SlEglCGmra = false;
      bool PuyoVAUiIf = false;
      bool igGfnZajwo = false;
      bool ISOHddtbsy = false;
      bool zGPYqyISib = false;
      bool KVPUlkeXsM = false;
      bool aVpDSwfqKq = false;
      bool FspKgbQhno = false;
      bool RIBTelCtUs = false;
      bool yVhfWcQMGt = false;
      bool RQHqWQfFmK = false;
      bool TxjDuRUVXf = false;
      bool tlVRsiKJmD = false;
      bool LEbtWABJxN = false;
      bool FxGKYAlekF = false;
      bool ItnZAfuoym = false;
      bool GWRiyPVpgt = false;
      bool QLYKZwfKsr = false;
      string ZqldhoVMVi;
      string RPFgVMLTWf;
      string SeAoUwNhXh;
      string wdVwSjiiVb;
      string PMDwmNtzUy;
      string ogYqnupxIl;
      string bnomlntJOl;
      string dbyuPGbECG;
      string BNNYsPEeHX;
      string slZjzbWQKy;
      string TkkhUMhdag;
      string SluBjOaQtV;
      string iOBprqCOun;
      string iLtDmQceDf;
      string haDZEHqXzk;
      string BGVnPFitpd;
      string KTimxHrrOT;
      string kuMNnILblk;
      string AdOJlcoFmh;
      string gioZVNrPcw;
      if(ZqldhoVMVi == TkkhUMhdag){PzIfAFtIzH = true;}
      else if(TkkhUMhdag == ZqldhoVMVi){RIBTelCtUs = true;}
      if(RPFgVMLTWf == SluBjOaQtV){tHHEcfFYBU = true;}
      else if(SluBjOaQtV == RPFgVMLTWf){yVhfWcQMGt = true;}
      if(SeAoUwNhXh == iOBprqCOun){SlEglCGmra = true;}
      else if(iOBprqCOun == SeAoUwNhXh){RQHqWQfFmK = true;}
      if(wdVwSjiiVb == iLtDmQceDf){PuyoVAUiIf = true;}
      else if(iLtDmQceDf == wdVwSjiiVb){TxjDuRUVXf = true;}
      if(PMDwmNtzUy == haDZEHqXzk){igGfnZajwo = true;}
      else if(haDZEHqXzk == PMDwmNtzUy){tlVRsiKJmD = true;}
      if(ogYqnupxIl == BGVnPFitpd){ISOHddtbsy = true;}
      else if(BGVnPFitpd == ogYqnupxIl){LEbtWABJxN = true;}
      if(bnomlntJOl == KTimxHrrOT){zGPYqyISib = true;}
      else if(KTimxHrrOT == bnomlntJOl){FxGKYAlekF = true;}
      if(dbyuPGbECG == kuMNnILblk){KVPUlkeXsM = true;}
      if(BNNYsPEeHX == AdOJlcoFmh){aVpDSwfqKq = true;}
      if(slZjzbWQKy == gioZVNrPcw){FspKgbQhno = true;}
      while(kuMNnILblk == dbyuPGbECG){ItnZAfuoym = true;}
      while(AdOJlcoFmh == AdOJlcoFmh){GWRiyPVpgt = true;}
      while(gioZVNrPcw == gioZVNrPcw){QLYKZwfKsr = true;}
      if(PzIfAFtIzH == true){PzIfAFtIzH = false;}
      if(tHHEcfFYBU == true){tHHEcfFYBU = false;}
      if(SlEglCGmra == true){SlEglCGmra = false;}
      if(PuyoVAUiIf == true){PuyoVAUiIf = false;}
      if(igGfnZajwo == true){igGfnZajwo = false;}
      if(ISOHddtbsy == true){ISOHddtbsy = false;}
      if(zGPYqyISib == true){zGPYqyISib = false;}
      if(KVPUlkeXsM == true){KVPUlkeXsM = false;}
      if(aVpDSwfqKq == true){aVpDSwfqKq = false;}
      if(FspKgbQhno == true){FspKgbQhno = false;}
      if(RIBTelCtUs == true){RIBTelCtUs = false;}
      if(yVhfWcQMGt == true){yVhfWcQMGt = false;}
      if(RQHqWQfFmK == true){RQHqWQfFmK = false;}
      if(TxjDuRUVXf == true){TxjDuRUVXf = false;}
      if(tlVRsiKJmD == true){tlVRsiKJmD = false;}
      if(LEbtWABJxN == true){LEbtWABJxN = false;}
      if(FxGKYAlekF == true){FxGKYAlekF = false;}
      if(ItnZAfuoym == true){ItnZAfuoym = false;}
      if(GWRiyPVpgt == true){GWRiyPVpgt = false;}
      if(QLYKZwfKsr == true){QLYKZwfKsr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUXHILTQKJ
{ 
  void gVlcizdHSN()
  { 
      bool GrhMdBNKba = false;
      bool GlwnwnweiC = false;
      bool PUHQlwJKSP = false;
      bool QVxnGhzmfS = false;
      bool WKDgYDEwiX = false;
      bool jUGgVljQah = false;
      bool rDqMKkoHhN = false;
      bool oJzQfFQaqh = false;
      bool rNbuewOQST = false;
      bool xiMyaTSqWn = false;
      bool OwNUiaVpAP = false;
      bool UIYroebwgN = false;
      bool WYoNPFxAoM = false;
      bool lZEDTuzGLE = false;
      bool aXPCzoKTIw = false;
      bool qWJIQoHAEd = false;
      bool cUAncuEUYt = false;
      bool eUkcmyIlOa = false;
      bool tcqsUPPuld = false;
      bool myCgaFXbYE = false;
      string YqxbcjoYYz;
      string xgQBtFhJhy;
      string fIlcJIaEYp;
      string MXQMjQuttD;
      string JuojZmbkzQ;
      string XzGFMPFTST;
      string IjAhlYPERd;
      string KnOenjSBCV;
      string gpFISNRKzT;
      string KabatYuGxA;
      string WXSUGijaRb;
      string xERwlSeqPY;
      string HEExTiMnkO;
      string nLDByJWkBi;
      string cpsWWGIeoa;
      string tDqXsSTVBW;
      string VwpDnkAQxb;
      string wsofwRLgZM;
      string ZgzKTkUeIf;
      string pAjeMgApil;
      if(YqxbcjoYYz == WXSUGijaRb){GrhMdBNKba = true;}
      else if(WXSUGijaRb == YqxbcjoYYz){OwNUiaVpAP = true;}
      if(xgQBtFhJhy == xERwlSeqPY){GlwnwnweiC = true;}
      else if(xERwlSeqPY == xgQBtFhJhy){UIYroebwgN = true;}
      if(fIlcJIaEYp == HEExTiMnkO){PUHQlwJKSP = true;}
      else if(HEExTiMnkO == fIlcJIaEYp){WYoNPFxAoM = true;}
      if(MXQMjQuttD == nLDByJWkBi){QVxnGhzmfS = true;}
      else if(nLDByJWkBi == MXQMjQuttD){lZEDTuzGLE = true;}
      if(JuojZmbkzQ == cpsWWGIeoa){WKDgYDEwiX = true;}
      else if(cpsWWGIeoa == JuojZmbkzQ){aXPCzoKTIw = true;}
      if(XzGFMPFTST == tDqXsSTVBW){jUGgVljQah = true;}
      else if(tDqXsSTVBW == XzGFMPFTST){qWJIQoHAEd = true;}
      if(IjAhlYPERd == VwpDnkAQxb){rDqMKkoHhN = true;}
      else if(VwpDnkAQxb == IjAhlYPERd){cUAncuEUYt = true;}
      if(KnOenjSBCV == wsofwRLgZM){oJzQfFQaqh = true;}
      if(gpFISNRKzT == ZgzKTkUeIf){rNbuewOQST = true;}
      if(KabatYuGxA == pAjeMgApil){xiMyaTSqWn = true;}
      while(wsofwRLgZM == KnOenjSBCV){eUkcmyIlOa = true;}
      while(ZgzKTkUeIf == ZgzKTkUeIf){tcqsUPPuld = true;}
      while(pAjeMgApil == pAjeMgApil){myCgaFXbYE = true;}
      if(GrhMdBNKba == true){GrhMdBNKba = false;}
      if(GlwnwnweiC == true){GlwnwnweiC = false;}
      if(PUHQlwJKSP == true){PUHQlwJKSP = false;}
      if(QVxnGhzmfS == true){QVxnGhzmfS = false;}
      if(WKDgYDEwiX == true){WKDgYDEwiX = false;}
      if(jUGgVljQah == true){jUGgVljQah = false;}
      if(rDqMKkoHhN == true){rDqMKkoHhN = false;}
      if(oJzQfFQaqh == true){oJzQfFQaqh = false;}
      if(rNbuewOQST == true){rNbuewOQST = false;}
      if(xiMyaTSqWn == true){xiMyaTSqWn = false;}
      if(OwNUiaVpAP == true){OwNUiaVpAP = false;}
      if(UIYroebwgN == true){UIYroebwgN = false;}
      if(WYoNPFxAoM == true){WYoNPFxAoM = false;}
      if(lZEDTuzGLE == true){lZEDTuzGLE = false;}
      if(aXPCzoKTIw == true){aXPCzoKTIw = false;}
      if(qWJIQoHAEd == true){qWJIQoHAEd = false;}
      if(cUAncuEUYt == true){cUAncuEUYt = false;}
      if(eUkcmyIlOa == true){eUkcmyIlOa = false;}
      if(tcqsUPPuld == true){tcqsUPPuld = false;}
      if(myCgaFXbYE == true){myCgaFXbYE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOJCSJXTND
{ 
  void wlcaAyHbNT()
  { 
      bool IZChPzHWKk = false;
      bool aKYhWLHiWI = false;
      bool VjCGLLxhUP = false;
      bool IWzewtBWXT = false;
      bool IwOBPiibLR = false;
      bool sHQMGYWuVD = false;
      bool BYBtbELtlb = false;
      bool KjLDzYUBqc = false;
      bool cUWDWBGlXW = false;
      bool XFBTRitUYL = false;
      bool XnoiGIwNNg = false;
      bool DVEsagCxXa = false;
      bool yZWPEEiqkP = false;
      bool eAbfEnenwN = false;
      bool ErXqSBBHsk = false;
      bool gwwyMyRZdC = false;
      bool ZFbxCDsXnm = false;
      bool BOBJWFBfwC = false;
      bool CaxzihDdSG = false;
      bool VFJsmzQanO = false;
      string yddxlJojUe;
      string rnymzaoaJU;
      string LTKsQmJXqP;
      string hUDZXxNIQr;
      string eHSDWMSSNo;
      string BPLHRdSjfy;
      string zQrFxWkXPC;
      string NgKQoDBHWE;
      string TqJBNSIuIs;
      string dcbRsOOMGz;
      string auCLbUFtRN;
      string cLNaeIGpqd;
      string NoPWXjErXa;
      string nnBXcYnyZs;
      string NNdtQSPAmj;
      string HXUbklefmq;
      string PMWpYnJoyF;
      string UIQyQAKUGE;
      string UDFmSQSZlq;
      string sIKhcAqnVb;
      if(yddxlJojUe == auCLbUFtRN){IZChPzHWKk = true;}
      else if(auCLbUFtRN == yddxlJojUe){XnoiGIwNNg = true;}
      if(rnymzaoaJU == cLNaeIGpqd){aKYhWLHiWI = true;}
      else if(cLNaeIGpqd == rnymzaoaJU){DVEsagCxXa = true;}
      if(LTKsQmJXqP == NoPWXjErXa){VjCGLLxhUP = true;}
      else if(NoPWXjErXa == LTKsQmJXqP){yZWPEEiqkP = true;}
      if(hUDZXxNIQr == nnBXcYnyZs){IWzewtBWXT = true;}
      else if(nnBXcYnyZs == hUDZXxNIQr){eAbfEnenwN = true;}
      if(eHSDWMSSNo == NNdtQSPAmj){IwOBPiibLR = true;}
      else if(NNdtQSPAmj == eHSDWMSSNo){ErXqSBBHsk = true;}
      if(BPLHRdSjfy == HXUbklefmq){sHQMGYWuVD = true;}
      else if(HXUbklefmq == BPLHRdSjfy){gwwyMyRZdC = true;}
      if(zQrFxWkXPC == PMWpYnJoyF){BYBtbELtlb = true;}
      else if(PMWpYnJoyF == zQrFxWkXPC){ZFbxCDsXnm = true;}
      if(NgKQoDBHWE == UIQyQAKUGE){KjLDzYUBqc = true;}
      if(TqJBNSIuIs == UDFmSQSZlq){cUWDWBGlXW = true;}
      if(dcbRsOOMGz == sIKhcAqnVb){XFBTRitUYL = true;}
      while(UIQyQAKUGE == NgKQoDBHWE){BOBJWFBfwC = true;}
      while(UDFmSQSZlq == UDFmSQSZlq){CaxzihDdSG = true;}
      while(sIKhcAqnVb == sIKhcAqnVb){VFJsmzQanO = true;}
      if(IZChPzHWKk == true){IZChPzHWKk = false;}
      if(aKYhWLHiWI == true){aKYhWLHiWI = false;}
      if(VjCGLLxhUP == true){VjCGLLxhUP = false;}
      if(IWzewtBWXT == true){IWzewtBWXT = false;}
      if(IwOBPiibLR == true){IwOBPiibLR = false;}
      if(sHQMGYWuVD == true){sHQMGYWuVD = false;}
      if(BYBtbELtlb == true){BYBtbELtlb = false;}
      if(KjLDzYUBqc == true){KjLDzYUBqc = false;}
      if(cUWDWBGlXW == true){cUWDWBGlXW = false;}
      if(XFBTRitUYL == true){XFBTRitUYL = false;}
      if(XnoiGIwNNg == true){XnoiGIwNNg = false;}
      if(DVEsagCxXa == true){DVEsagCxXa = false;}
      if(yZWPEEiqkP == true){yZWPEEiqkP = false;}
      if(eAbfEnenwN == true){eAbfEnenwN = false;}
      if(ErXqSBBHsk == true){ErXqSBBHsk = false;}
      if(gwwyMyRZdC == true){gwwyMyRZdC = false;}
      if(ZFbxCDsXnm == true){ZFbxCDsXnm = false;}
      if(BOBJWFBfwC == true){BOBJWFBfwC = false;}
      if(CaxzihDdSG == true){CaxzihDdSG = false;}
      if(VFJsmzQanO == true){VFJsmzQanO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBOVCQMCGP
{ 
  void SxAAodCAsw()
  { 
      bool wEqrrxclkl = false;
      bool sMDIhxqitC = false;
      bool lqonGPbexm = false;
      bool OqZPPdGaxG = false;
      bool GpTTqkncSI = false;
      bool YDeteFPClc = false;
      bool VyoyXBlmrE = false;
      bool qPkmuuWUxU = false;
      bool ayLoNKLfkK = false;
      bool NDnTkIBUwo = false;
      bool yAkNQISqyi = false;
      bool htEQBWlzjN = false;
      bool oGCgpmaQCm = false;
      bool tBYIVaNxXF = false;
      bool rUgBcSzXSN = false;
      bool VBkhAryDXd = false;
      bool gBoKofVwta = false;
      bool InbeUUYADX = false;
      bool nDynRrQpHd = false;
      bool bJZtXqeWMw = false;
      string VNMZAOoDaC;
      string pMXpaxkqNP;
      string VYJdPoEroL;
      string XGnyMmYqsr;
      string ZVKwiXQcNX;
      string CXiDgxDiJK;
      string JxOOdjYYdn;
      string XtxVpAOMtr;
      string YaeQJAXjRP;
      string ioghhbGuSz;
      string yqzYzIZMMg;
      string hqoRliRxFd;
      string LoHOEiMPnO;
      string sSttsgbFRB;
      string ZKXjgrAOwz;
      string JIpomJjkUQ;
      string uKXymPwuXE;
      string GMfDDBQWgM;
      string hxSoEjcFGj;
      string xqkAGPmZxR;
      if(VNMZAOoDaC == yqzYzIZMMg){wEqrrxclkl = true;}
      else if(yqzYzIZMMg == VNMZAOoDaC){yAkNQISqyi = true;}
      if(pMXpaxkqNP == hqoRliRxFd){sMDIhxqitC = true;}
      else if(hqoRliRxFd == pMXpaxkqNP){htEQBWlzjN = true;}
      if(VYJdPoEroL == LoHOEiMPnO){lqonGPbexm = true;}
      else if(LoHOEiMPnO == VYJdPoEroL){oGCgpmaQCm = true;}
      if(XGnyMmYqsr == sSttsgbFRB){OqZPPdGaxG = true;}
      else if(sSttsgbFRB == XGnyMmYqsr){tBYIVaNxXF = true;}
      if(ZVKwiXQcNX == ZKXjgrAOwz){GpTTqkncSI = true;}
      else if(ZKXjgrAOwz == ZVKwiXQcNX){rUgBcSzXSN = true;}
      if(CXiDgxDiJK == JIpomJjkUQ){YDeteFPClc = true;}
      else if(JIpomJjkUQ == CXiDgxDiJK){VBkhAryDXd = true;}
      if(JxOOdjYYdn == uKXymPwuXE){VyoyXBlmrE = true;}
      else if(uKXymPwuXE == JxOOdjYYdn){gBoKofVwta = true;}
      if(XtxVpAOMtr == GMfDDBQWgM){qPkmuuWUxU = true;}
      if(YaeQJAXjRP == hxSoEjcFGj){ayLoNKLfkK = true;}
      if(ioghhbGuSz == xqkAGPmZxR){NDnTkIBUwo = true;}
      while(GMfDDBQWgM == XtxVpAOMtr){InbeUUYADX = true;}
      while(hxSoEjcFGj == hxSoEjcFGj){nDynRrQpHd = true;}
      while(xqkAGPmZxR == xqkAGPmZxR){bJZtXqeWMw = true;}
      if(wEqrrxclkl == true){wEqrrxclkl = false;}
      if(sMDIhxqitC == true){sMDIhxqitC = false;}
      if(lqonGPbexm == true){lqonGPbexm = false;}
      if(OqZPPdGaxG == true){OqZPPdGaxG = false;}
      if(GpTTqkncSI == true){GpTTqkncSI = false;}
      if(YDeteFPClc == true){YDeteFPClc = false;}
      if(VyoyXBlmrE == true){VyoyXBlmrE = false;}
      if(qPkmuuWUxU == true){qPkmuuWUxU = false;}
      if(ayLoNKLfkK == true){ayLoNKLfkK = false;}
      if(NDnTkIBUwo == true){NDnTkIBUwo = false;}
      if(yAkNQISqyi == true){yAkNQISqyi = false;}
      if(htEQBWlzjN == true){htEQBWlzjN = false;}
      if(oGCgpmaQCm == true){oGCgpmaQCm = false;}
      if(tBYIVaNxXF == true){tBYIVaNxXF = false;}
      if(rUgBcSzXSN == true){rUgBcSzXSN = false;}
      if(VBkhAryDXd == true){VBkhAryDXd = false;}
      if(gBoKofVwta == true){gBoKofVwta = false;}
      if(InbeUUYADX == true){InbeUUYADX = false;}
      if(nDynRrQpHd == true){nDynRrQpHd = false;}
      if(bJZtXqeWMw == true){bJZtXqeWMw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZZJHTZDBP
{ 
  void aLNSZdpGWD()
  { 
      bool qSPfnBNuJU = false;
      bool anBLmRrBcS = false;
      bool SxaOGgpnwT = false;
      bool mZVaYUEmtM = false;
      bool gsIJLATsOA = false;
      bool XuREwtqBYH = false;
      bool LYypgBSZmS = false;
      bool MEHQkZnRDF = false;
      bool NxZwwrIQed = false;
      bool cDNlAItSbK = false;
      bool hsGumSmATV = false;
      bool GZySsOzCto = false;
      bool sCuIoJqUPc = false;
      bool eVorXUpdIc = false;
      bool FHwIXCFtsl = false;
      bool IrXmQfxxFd = false;
      bool aSjqpjkFuY = false;
      bool XVsQikFljm = false;
      bool DwbdTmxBbr = false;
      bool WsXdClWFSm = false;
      string YretdaFMhT;
      string hVDmbpDsHa;
      string RwEhcZAqfm;
      string ebbaCVMQBe;
      string oAWqbtolHQ;
      string KylndcnwQE;
      string aNfuoGsbjG;
      string dlrclRYMFh;
      string jNjPcfpnxY;
      string hQAwDaTbBV;
      string AMCBmYGICL;
      string DapiTNdQSJ;
      string QFeLXMluYK;
      string yxKjgXLhbE;
      string ZgkkVHZQcp;
      string xCJrFuhqcZ;
      string lKjqNGPGBw;
      string BuoOijTsoQ;
      string mUShNunSel;
      string oUFBRPwtXO;
      if(YretdaFMhT == AMCBmYGICL){qSPfnBNuJU = true;}
      else if(AMCBmYGICL == YretdaFMhT){hsGumSmATV = true;}
      if(hVDmbpDsHa == DapiTNdQSJ){anBLmRrBcS = true;}
      else if(DapiTNdQSJ == hVDmbpDsHa){GZySsOzCto = true;}
      if(RwEhcZAqfm == QFeLXMluYK){SxaOGgpnwT = true;}
      else if(QFeLXMluYK == RwEhcZAqfm){sCuIoJqUPc = true;}
      if(ebbaCVMQBe == yxKjgXLhbE){mZVaYUEmtM = true;}
      else if(yxKjgXLhbE == ebbaCVMQBe){eVorXUpdIc = true;}
      if(oAWqbtolHQ == ZgkkVHZQcp){gsIJLATsOA = true;}
      else if(ZgkkVHZQcp == oAWqbtolHQ){FHwIXCFtsl = true;}
      if(KylndcnwQE == xCJrFuhqcZ){XuREwtqBYH = true;}
      else if(xCJrFuhqcZ == KylndcnwQE){IrXmQfxxFd = true;}
      if(aNfuoGsbjG == lKjqNGPGBw){LYypgBSZmS = true;}
      else if(lKjqNGPGBw == aNfuoGsbjG){aSjqpjkFuY = true;}
      if(dlrclRYMFh == BuoOijTsoQ){MEHQkZnRDF = true;}
      if(jNjPcfpnxY == mUShNunSel){NxZwwrIQed = true;}
      if(hQAwDaTbBV == oUFBRPwtXO){cDNlAItSbK = true;}
      while(BuoOijTsoQ == dlrclRYMFh){XVsQikFljm = true;}
      while(mUShNunSel == mUShNunSel){DwbdTmxBbr = true;}
      while(oUFBRPwtXO == oUFBRPwtXO){WsXdClWFSm = true;}
      if(qSPfnBNuJU == true){qSPfnBNuJU = false;}
      if(anBLmRrBcS == true){anBLmRrBcS = false;}
      if(SxaOGgpnwT == true){SxaOGgpnwT = false;}
      if(mZVaYUEmtM == true){mZVaYUEmtM = false;}
      if(gsIJLATsOA == true){gsIJLATsOA = false;}
      if(XuREwtqBYH == true){XuREwtqBYH = false;}
      if(LYypgBSZmS == true){LYypgBSZmS = false;}
      if(MEHQkZnRDF == true){MEHQkZnRDF = false;}
      if(NxZwwrIQed == true){NxZwwrIQed = false;}
      if(cDNlAItSbK == true){cDNlAItSbK = false;}
      if(hsGumSmATV == true){hsGumSmATV = false;}
      if(GZySsOzCto == true){GZySsOzCto = false;}
      if(sCuIoJqUPc == true){sCuIoJqUPc = false;}
      if(eVorXUpdIc == true){eVorXUpdIc = false;}
      if(FHwIXCFtsl == true){FHwIXCFtsl = false;}
      if(IrXmQfxxFd == true){IrXmQfxxFd = false;}
      if(aSjqpjkFuY == true){aSjqpjkFuY = false;}
      if(XVsQikFljm == true){XVsQikFljm = false;}
      if(DwbdTmxBbr == true){DwbdTmxBbr = false;}
      if(WsXdClWFSm == true){WsXdClWFSm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AAWLKCTBLH
{ 
  void HTWxtmQnud()
  { 
      bool OibPCSoYgu = false;
      bool tgfwBFQNeM = false;
      bool InIcEyEtkt = false;
      bool FOTAnfeVVh = false;
      bool sDCemFpyoh = false;
      bool EleuiaZyLE = false;
      bool OtnlofNfIV = false;
      bool ZtqwTEldpz = false;
      bool HGFCoTiXRM = false;
      bool FgKRTyPPoG = false;
      bool rKoTHJthbd = false;
      bool nwHLwIokwV = false;
      bool wpOuPsjZcU = false;
      bool oVnjHxQkuf = false;
      bool ZAumYJYyVL = false;
      bool IdTTKBusDO = false;
      bool YUFHoSHXEy = false;
      bool qDpQwutbWG = false;
      bool TlDRLKCUYF = false;
      bool BWhgGEunyF = false;
      string BfuXlgiGhH;
      string CcXAwKmEYS;
      string ktJUbOgGKD;
      string ApVjsOCuRn;
      string nMzqDpcwWG;
      string xhTebGWawX;
      string AcudGMGnGh;
      string IqmkeYuRRk;
      string kjiEFSVqHm;
      string qaytnLQUkq;
      string jopoxFuizD;
      string KEJLlPsqXm;
      string qPfSpgssxT;
      string HZgZButtGz;
      string XlqEbmRlHX;
      string RZxxATIWzQ;
      string MClfukXiKq;
      string VzjXPEYbqC;
      string OGkYBhciZg;
      string lWtpmUzKIq;
      if(BfuXlgiGhH == jopoxFuizD){OibPCSoYgu = true;}
      else if(jopoxFuizD == BfuXlgiGhH){rKoTHJthbd = true;}
      if(CcXAwKmEYS == KEJLlPsqXm){tgfwBFQNeM = true;}
      else if(KEJLlPsqXm == CcXAwKmEYS){nwHLwIokwV = true;}
      if(ktJUbOgGKD == qPfSpgssxT){InIcEyEtkt = true;}
      else if(qPfSpgssxT == ktJUbOgGKD){wpOuPsjZcU = true;}
      if(ApVjsOCuRn == HZgZButtGz){FOTAnfeVVh = true;}
      else if(HZgZButtGz == ApVjsOCuRn){oVnjHxQkuf = true;}
      if(nMzqDpcwWG == XlqEbmRlHX){sDCemFpyoh = true;}
      else if(XlqEbmRlHX == nMzqDpcwWG){ZAumYJYyVL = true;}
      if(xhTebGWawX == RZxxATIWzQ){EleuiaZyLE = true;}
      else if(RZxxATIWzQ == xhTebGWawX){IdTTKBusDO = true;}
      if(AcudGMGnGh == MClfukXiKq){OtnlofNfIV = true;}
      else if(MClfukXiKq == AcudGMGnGh){YUFHoSHXEy = true;}
      if(IqmkeYuRRk == VzjXPEYbqC){ZtqwTEldpz = true;}
      if(kjiEFSVqHm == OGkYBhciZg){HGFCoTiXRM = true;}
      if(qaytnLQUkq == lWtpmUzKIq){FgKRTyPPoG = true;}
      while(VzjXPEYbqC == IqmkeYuRRk){qDpQwutbWG = true;}
      while(OGkYBhciZg == OGkYBhciZg){TlDRLKCUYF = true;}
      while(lWtpmUzKIq == lWtpmUzKIq){BWhgGEunyF = true;}
      if(OibPCSoYgu == true){OibPCSoYgu = false;}
      if(tgfwBFQNeM == true){tgfwBFQNeM = false;}
      if(InIcEyEtkt == true){InIcEyEtkt = false;}
      if(FOTAnfeVVh == true){FOTAnfeVVh = false;}
      if(sDCemFpyoh == true){sDCemFpyoh = false;}
      if(EleuiaZyLE == true){EleuiaZyLE = false;}
      if(OtnlofNfIV == true){OtnlofNfIV = false;}
      if(ZtqwTEldpz == true){ZtqwTEldpz = false;}
      if(HGFCoTiXRM == true){HGFCoTiXRM = false;}
      if(FgKRTyPPoG == true){FgKRTyPPoG = false;}
      if(rKoTHJthbd == true){rKoTHJthbd = false;}
      if(nwHLwIokwV == true){nwHLwIokwV = false;}
      if(wpOuPsjZcU == true){wpOuPsjZcU = false;}
      if(oVnjHxQkuf == true){oVnjHxQkuf = false;}
      if(ZAumYJYyVL == true){ZAumYJYyVL = false;}
      if(IdTTKBusDO == true){IdTTKBusDO = false;}
      if(YUFHoSHXEy == true){YUFHoSHXEy = false;}
      if(qDpQwutbWG == true){qDpQwutbWG = false;}
      if(TlDRLKCUYF == true){TlDRLKCUYF = false;}
      if(BWhgGEunyF == true){BWhgGEunyF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMINTUSDUV
{ 
  void AeWSJFYzXk()
  { 
      bool mFklmzmcVG = false;
      bool LUFzjwKsMZ = false;
      bool lMWPditjCf = false;
      bool NeaCKNfyZn = false;
      bool ymszrxwoGZ = false;
      bool rjSrqZhUHE = false;
      bool FCZorfsCnW = false;
      bool QLSXbyTXWg = false;
      bool lEcbmcMhLj = false;
      bool eKqUiuMDHM = false;
      bool EtAjJfRtPs = false;
      bool GKyaSAZyBO = false;
      bool TKpDrFUxog = false;
      bool kQQKcqDsSH = false;
      bool LRSRdTMPCh = false;
      bool UOBrrsDwqD = false;
      bool LTFiHotmya = false;
      bool wfetCBrYZX = false;
      bool sFuGLVOXRi = false;
      bool mHBPwrMiKn = false;
      string RATbIEmxsO;
      string FtwMkrsmml;
      string uSwIwOuYYR;
      string OByjzOacGF;
      string OJnndIxJeX;
      string zxYuuzEKft;
      string JNYbzDuLMW;
      string RQggXkeIdm;
      string RktBSQbDnA;
      string KPwMwBkLnZ;
      string NkxIFhQqWK;
      string UugrcXTWJi;
      string bqWLMBUUkV;
      string zSTDZfmkuj;
      string zjfdeOiDiX;
      string hOCFyVNkwD;
      string NwGBLCbcSw;
      string jhaYirKsfx;
      string SQkNnkQOFD;
      string SBnqWDdeSc;
      if(RATbIEmxsO == NkxIFhQqWK){mFklmzmcVG = true;}
      else if(NkxIFhQqWK == RATbIEmxsO){EtAjJfRtPs = true;}
      if(FtwMkrsmml == UugrcXTWJi){LUFzjwKsMZ = true;}
      else if(UugrcXTWJi == FtwMkrsmml){GKyaSAZyBO = true;}
      if(uSwIwOuYYR == bqWLMBUUkV){lMWPditjCf = true;}
      else if(bqWLMBUUkV == uSwIwOuYYR){TKpDrFUxog = true;}
      if(OByjzOacGF == zSTDZfmkuj){NeaCKNfyZn = true;}
      else if(zSTDZfmkuj == OByjzOacGF){kQQKcqDsSH = true;}
      if(OJnndIxJeX == zjfdeOiDiX){ymszrxwoGZ = true;}
      else if(zjfdeOiDiX == OJnndIxJeX){LRSRdTMPCh = true;}
      if(zxYuuzEKft == hOCFyVNkwD){rjSrqZhUHE = true;}
      else if(hOCFyVNkwD == zxYuuzEKft){UOBrrsDwqD = true;}
      if(JNYbzDuLMW == NwGBLCbcSw){FCZorfsCnW = true;}
      else if(NwGBLCbcSw == JNYbzDuLMW){LTFiHotmya = true;}
      if(RQggXkeIdm == jhaYirKsfx){QLSXbyTXWg = true;}
      if(RktBSQbDnA == SQkNnkQOFD){lEcbmcMhLj = true;}
      if(KPwMwBkLnZ == SBnqWDdeSc){eKqUiuMDHM = true;}
      while(jhaYirKsfx == RQggXkeIdm){wfetCBrYZX = true;}
      while(SQkNnkQOFD == SQkNnkQOFD){sFuGLVOXRi = true;}
      while(SBnqWDdeSc == SBnqWDdeSc){mHBPwrMiKn = true;}
      if(mFklmzmcVG == true){mFklmzmcVG = false;}
      if(LUFzjwKsMZ == true){LUFzjwKsMZ = false;}
      if(lMWPditjCf == true){lMWPditjCf = false;}
      if(NeaCKNfyZn == true){NeaCKNfyZn = false;}
      if(ymszrxwoGZ == true){ymszrxwoGZ = false;}
      if(rjSrqZhUHE == true){rjSrqZhUHE = false;}
      if(FCZorfsCnW == true){FCZorfsCnW = false;}
      if(QLSXbyTXWg == true){QLSXbyTXWg = false;}
      if(lEcbmcMhLj == true){lEcbmcMhLj = false;}
      if(eKqUiuMDHM == true){eKqUiuMDHM = false;}
      if(EtAjJfRtPs == true){EtAjJfRtPs = false;}
      if(GKyaSAZyBO == true){GKyaSAZyBO = false;}
      if(TKpDrFUxog == true){TKpDrFUxog = false;}
      if(kQQKcqDsSH == true){kQQKcqDsSH = false;}
      if(LRSRdTMPCh == true){LRSRdTMPCh = false;}
      if(UOBrrsDwqD == true){UOBrrsDwqD = false;}
      if(LTFiHotmya == true){LTFiHotmya = false;}
      if(wfetCBrYZX == true){wfetCBrYZX = false;}
      if(sFuGLVOXRi == true){sFuGLVOXRi = false;}
      if(mHBPwrMiKn == true){mHBPwrMiKn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWPMNKTQBF
{ 
  void yunTWUjCNL()
  { 
      bool OylHWIQFpl = false;
      bool erRqKkTskn = false;
      bool jPdtqzBSAH = false;
      bool WtdFJFMbVN = false;
      bool opxZqxjmuQ = false;
      bool gRtKEyUqQX = false;
      bool HyEiPkOLhF = false;
      bool XqXWysSDDt = false;
      bool PNWjZFzSBK = false;
      bool jVLyGqlNKF = false;
      bool hXFpspsWLK = false;
      bool fQmVHtaUIJ = false;
      bool kuJXUBeZQH = false;
      bool HEsyLqHgqj = false;
      bool LcGqeThopM = false;
      bool PQFATmNgUq = false;
      bool KTGECaXoKQ = false;
      bool ltdYxInSsB = false;
      bool ToiDqpzrdY = false;
      bool caLAZrVBoE = false;
      string lsQXrmlISK;
      string sZFDwYigCX;
      string eEFMjxhInH;
      string PNEBkwSjat;
      string tBGGeousGN;
      string jhLwSgnEnt;
      string FdTKtfVERz;
      string GyFHccyygu;
      string CoCaWgBHiD;
      string INwgoQhuLz;
      string SqaGGlcETo;
      string ipXsrPbrmN;
      string eNVOqsCYRL;
      string uDlgbKNuTk;
      string ExnsUSoDoY;
      string ooHyUFULPN;
      string jDlHtfDpQg;
      string BfXCIhZctX;
      string DyjsWGumMV;
      string oCeFBBKfyn;
      if(lsQXrmlISK == SqaGGlcETo){OylHWIQFpl = true;}
      else if(SqaGGlcETo == lsQXrmlISK){hXFpspsWLK = true;}
      if(sZFDwYigCX == ipXsrPbrmN){erRqKkTskn = true;}
      else if(ipXsrPbrmN == sZFDwYigCX){fQmVHtaUIJ = true;}
      if(eEFMjxhInH == eNVOqsCYRL){jPdtqzBSAH = true;}
      else if(eNVOqsCYRL == eEFMjxhInH){kuJXUBeZQH = true;}
      if(PNEBkwSjat == uDlgbKNuTk){WtdFJFMbVN = true;}
      else if(uDlgbKNuTk == PNEBkwSjat){HEsyLqHgqj = true;}
      if(tBGGeousGN == ExnsUSoDoY){opxZqxjmuQ = true;}
      else if(ExnsUSoDoY == tBGGeousGN){LcGqeThopM = true;}
      if(jhLwSgnEnt == ooHyUFULPN){gRtKEyUqQX = true;}
      else if(ooHyUFULPN == jhLwSgnEnt){PQFATmNgUq = true;}
      if(FdTKtfVERz == jDlHtfDpQg){HyEiPkOLhF = true;}
      else if(jDlHtfDpQg == FdTKtfVERz){KTGECaXoKQ = true;}
      if(GyFHccyygu == BfXCIhZctX){XqXWysSDDt = true;}
      if(CoCaWgBHiD == DyjsWGumMV){PNWjZFzSBK = true;}
      if(INwgoQhuLz == oCeFBBKfyn){jVLyGqlNKF = true;}
      while(BfXCIhZctX == GyFHccyygu){ltdYxInSsB = true;}
      while(DyjsWGumMV == DyjsWGumMV){ToiDqpzrdY = true;}
      while(oCeFBBKfyn == oCeFBBKfyn){caLAZrVBoE = true;}
      if(OylHWIQFpl == true){OylHWIQFpl = false;}
      if(erRqKkTskn == true){erRqKkTskn = false;}
      if(jPdtqzBSAH == true){jPdtqzBSAH = false;}
      if(WtdFJFMbVN == true){WtdFJFMbVN = false;}
      if(opxZqxjmuQ == true){opxZqxjmuQ = false;}
      if(gRtKEyUqQX == true){gRtKEyUqQX = false;}
      if(HyEiPkOLhF == true){HyEiPkOLhF = false;}
      if(XqXWysSDDt == true){XqXWysSDDt = false;}
      if(PNWjZFzSBK == true){PNWjZFzSBK = false;}
      if(jVLyGqlNKF == true){jVLyGqlNKF = false;}
      if(hXFpspsWLK == true){hXFpspsWLK = false;}
      if(fQmVHtaUIJ == true){fQmVHtaUIJ = false;}
      if(kuJXUBeZQH == true){kuJXUBeZQH = false;}
      if(HEsyLqHgqj == true){HEsyLqHgqj = false;}
      if(LcGqeThopM == true){LcGqeThopM = false;}
      if(PQFATmNgUq == true){PQFATmNgUq = false;}
      if(KTGECaXoKQ == true){KTGECaXoKQ = false;}
      if(ltdYxInSsB == true){ltdYxInSsB = false;}
      if(ToiDqpzrdY == true){ToiDqpzrdY = false;}
      if(caLAZrVBoE == true){caLAZrVBoE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJZSRDIWYZ
{ 
  void yRgLCCobIt()
  { 
      bool bXisGeYTIn = false;
      bool KlUkrgTKLX = false;
      bool KdaQAnGZCo = false;
      bool tcKSlrLeXo = false;
      bool owaErIBNCb = false;
      bool JLaLkyxRrR = false;
      bool YyQStgaCzA = false;
      bool UolWiNCVYr = false;
      bool mrWZfiCzgm = false;
      bool tsmGQqeIKL = false;
      bool gzNCGUYEcX = false;
      bool uaszefbpmL = false;
      bool ebULFbCfGr = false;
      bool itLMLndUTL = false;
      bool JxVJqTzmbj = false;
      bool OnUyfEdBxd = false;
      bool RsyknBPgnp = false;
      bool BHWbBgGLUl = false;
      bool bPEVctYMfG = false;
      bool KcWosPzjUp = false;
      string kWghTzhurb;
      string laUDtWttrl;
      string jyPkrPOcCm;
      string JLjjcYFrSQ;
      string sKekGCkrZh;
      string bhNdTmGwoD;
      string kFrFRZpjZV;
      string QBbbrYSeep;
      string eWCTKbxFQp;
      string RJDOenRYSg;
      string LBSDQZFlkt;
      string TaRzYODYup;
      string bjSjEHyNwE;
      string HtMydcEyDj;
      string VLTWVpqDoQ;
      string jsdbEahhzI;
      string broglZOTUw;
      string KFUKTPQuNN;
      string PtXeUNPjsD;
      string uVzuIdVmju;
      if(kWghTzhurb == LBSDQZFlkt){bXisGeYTIn = true;}
      else if(LBSDQZFlkt == kWghTzhurb){gzNCGUYEcX = true;}
      if(laUDtWttrl == TaRzYODYup){KlUkrgTKLX = true;}
      else if(TaRzYODYup == laUDtWttrl){uaszefbpmL = true;}
      if(jyPkrPOcCm == bjSjEHyNwE){KdaQAnGZCo = true;}
      else if(bjSjEHyNwE == jyPkrPOcCm){ebULFbCfGr = true;}
      if(JLjjcYFrSQ == HtMydcEyDj){tcKSlrLeXo = true;}
      else if(HtMydcEyDj == JLjjcYFrSQ){itLMLndUTL = true;}
      if(sKekGCkrZh == VLTWVpqDoQ){owaErIBNCb = true;}
      else if(VLTWVpqDoQ == sKekGCkrZh){JxVJqTzmbj = true;}
      if(bhNdTmGwoD == jsdbEahhzI){JLaLkyxRrR = true;}
      else if(jsdbEahhzI == bhNdTmGwoD){OnUyfEdBxd = true;}
      if(kFrFRZpjZV == broglZOTUw){YyQStgaCzA = true;}
      else if(broglZOTUw == kFrFRZpjZV){RsyknBPgnp = true;}
      if(QBbbrYSeep == KFUKTPQuNN){UolWiNCVYr = true;}
      if(eWCTKbxFQp == PtXeUNPjsD){mrWZfiCzgm = true;}
      if(RJDOenRYSg == uVzuIdVmju){tsmGQqeIKL = true;}
      while(KFUKTPQuNN == QBbbrYSeep){BHWbBgGLUl = true;}
      while(PtXeUNPjsD == PtXeUNPjsD){bPEVctYMfG = true;}
      while(uVzuIdVmju == uVzuIdVmju){KcWosPzjUp = true;}
      if(bXisGeYTIn == true){bXisGeYTIn = false;}
      if(KlUkrgTKLX == true){KlUkrgTKLX = false;}
      if(KdaQAnGZCo == true){KdaQAnGZCo = false;}
      if(tcKSlrLeXo == true){tcKSlrLeXo = false;}
      if(owaErIBNCb == true){owaErIBNCb = false;}
      if(JLaLkyxRrR == true){JLaLkyxRrR = false;}
      if(YyQStgaCzA == true){YyQStgaCzA = false;}
      if(UolWiNCVYr == true){UolWiNCVYr = false;}
      if(mrWZfiCzgm == true){mrWZfiCzgm = false;}
      if(tsmGQqeIKL == true){tsmGQqeIKL = false;}
      if(gzNCGUYEcX == true){gzNCGUYEcX = false;}
      if(uaszefbpmL == true){uaszefbpmL = false;}
      if(ebULFbCfGr == true){ebULFbCfGr = false;}
      if(itLMLndUTL == true){itLMLndUTL = false;}
      if(JxVJqTzmbj == true){JxVJqTzmbj = false;}
      if(OnUyfEdBxd == true){OnUyfEdBxd = false;}
      if(RsyknBPgnp == true){RsyknBPgnp = false;}
      if(BHWbBgGLUl == true){BHWbBgGLUl = false;}
      if(bPEVctYMfG == true){bPEVctYMfG = false;}
      if(KcWosPzjUp == true){KcWosPzjUp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSYFVIEQXW
{ 
  void lOEZoxFblX()
  { 
      bool CixFueGTWx = false;
      bool zjfgEIukct = false;
      bool mLnLYaDmWp = false;
      bool ZfQURoaRXo = false;
      bool iqWgJexYXw = false;
      bool LaxXBqtkfU = false;
      bool bTxgXTTKOP = false;
      bool gdMmKwnHCt = false;
      bool cePZdyhrSa = false;
      bool tpkDNPtpIp = false;
      bool LlJHPhNJNF = false;
      bool DmilqwDXCZ = false;
      bool kbrnUqrJZt = false;
      bool BxyMiqVHJw = false;
      bool jYdMXHHzLR = false;
      bool LVmiFitUmY = false;
      bool oEjTDFnVDA = false;
      bool awNFoLxeQM = false;
      bool iryIheJPGz = false;
      bool xATkGfnKJR = false;
      string VJNYrMQyzW;
      string wAqHHacSmL;
      string bzifpfkRUa;
      string lDsEQCRjfx;
      string BVhcerqehL;
      string QYNPEWahhM;
      string bydYkrHlqE;
      string IrloKFQGAy;
      string nFjIKMpcAs;
      string biBTVCrJrl;
      string jEmcCXlYFy;
      string FTgiYVOVNX;
      string CdkxbZpSTH;
      string NGOOOiSGFl;
      string aQXCnIBRuz;
      string mWuTiFToBc;
      string gTFxjyFSUo;
      string DIPbxkGiJT;
      string XYXTUpLteI;
      string PcFbFHLZRo;
      if(VJNYrMQyzW == jEmcCXlYFy){CixFueGTWx = true;}
      else if(jEmcCXlYFy == VJNYrMQyzW){LlJHPhNJNF = true;}
      if(wAqHHacSmL == FTgiYVOVNX){zjfgEIukct = true;}
      else if(FTgiYVOVNX == wAqHHacSmL){DmilqwDXCZ = true;}
      if(bzifpfkRUa == CdkxbZpSTH){mLnLYaDmWp = true;}
      else if(CdkxbZpSTH == bzifpfkRUa){kbrnUqrJZt = true;}
      if(lDsEQCRjfx == NGOOOiSGFl){ZfQURoaRXo = true;}
      else if(NGOOOiSGFl == lDsEQCRjfx){BxyMiqVHJw = true;}
      if(BVhcerqehL == aQXCnIBRuz){iqWgJexYXw = true;}
      else if(aQXCnIBRuz == BVhcerqehL){jYdMXHHzLR = true;}
      if(QYNPEWahhM == mWuTiFToBc){LaxXBqtkfU = true;}
      else if(mWuTiFToBc == QYNPEWahhM){LVmiFitUmY = true;}
      if(bydYkrHlqE == gTFxjyFSUo){bTxgXTTKOP = true;}
      else if(gTFxjyFSUo == bydYkrHlqE){oEjTDFnVDA = true;}
      if(IrloKFQGAy == DIPbxkGiJT){gdMmKwnHCt = true;}
      if(nFjIKMpcAs == XYXTUpLteI){cePZdyhrSa = true;}
      if(biBTVCrJrl == PcFbFHLZRo){tpkDNPtpIp = true;}
      while(DIPbxkGiJT == IrloKFQGAy){awNFoLxeQM = true;}
      while(XYXTUpLteI == XYXTUpLteI){iryIheJPGz = true;}
      while(PcFbFHLZRo == PcFbFHLZRo){xATkGfnKJR = true;}
      if(CixFueGTWx == true){CixFueGTWx = false;}
      if(zjfgEIukct == true){zjfgEIukct = false;}
      if(mLnLYaDmWp == true){mLnLYaDmWp = false;}
      if(ZfQURoaRXo == true){ZfQURoaRXo = false;}
      if(iqWgJexYXw == true){iqWgJexYXw = false;}
      if(LaxXBqtkfU == true){LaxXBqtkfU = false;}
      if(bTxgXTTKOP == true){bTxgXTTKOP = false;}
      if(gdMmKwnHCt == true){gdMmKwnHCt = false;}
      if(cePZdyhrSa == true){cePZdyhrSa = false;}
      if(tpkDNPtpIp == true){tpkDNPtpIp = false;}
      if(LlJHPhNJNF == true){LlJHPhNJNF = false;}
      if(DmilqwDXCZ == true){DmilqwDXCZ = false;}
      if(kbrnUqrJZt == true){kbrnUqrJZt = false;}
      if(BxyMiqVHJw == true){BxyMiqVHJw = false;}
      if(jYdMXHHzLR == true){jYdMXHHzLR = false;}
      if(LVmiFitUmY == true){LVmiFitUmY = false;}
      if(oEjTDFnVDA == true){oEjTDFnVDA = false;}
      if(awNFoLxeQM == true){awNFoLxeQM = false;}
      if(iryIheJPGz == true){iryIheJPGz = false;}
      if(xATkGfnKJR == true){xATkGfnKJR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AELTHQFLAK
{ 
  void xIQdsDZecr()
  { 
      bool BcTQCcRxeI = false;
      bool ufXYduxXfV = false;
      bool tBEbJrnRNF = false;
      bool NVKBzTEcfn = false;
      bool goXBSVPLpP = false;
      bool PZUVZAXrGK = false;
      bool oziYtYUWYJ = false;
      bool qTrqnEcCIm = false;
      bool bbbyonBobz = false;
      bool uMWVzhFzGs = false;
      bool AsmfYwgcgU = false;
      bool WViThMXkjG = false;
      bool XfuZNdxWrG = false;
      bool ydwOliouZs = false;
      bool HXHGcZcCmm = false;
      bool JUOzUUxNRt = false;
      bool yJjZWrYUgz = false;
      bool WbKqzzXown = false;
      bool AtjFxdPwsR = false;
      bool kbdftxnhjk = false;
      string fToWXlVaqe;
      string ETrgICfLXT;
      string GDpljlZsnB;
      string jMkqToiRMJ;
      string NVRRZTAcBg;
      string ROkWHbdClk;
      string LbmotqhANT;
      string TNzOFjlXLQ;
      string lxrHjVaOjq;
      string LgebxlibWi;
      string kzPhMDPWQW;
      string pFpVyOifFY;
      string PTPVHmiWQT;
      string BJAcelhKtf;
      string FExMAGpJci;
      string CCWyTQisZZ;
      string UrGxUgENpM;
      string fYkYTLVDUB;
      string wYthRymCJN;
      string CnjTLNxArT;
      if(fToWXlVaqe == kzPhMDPWQW){BcTQCcRxeI = true;}
      else if(kzPhMDPWQW == fToWXlVaqe){AsmfYwgcgU = true;}
      if(ETrgICfLXT == pFpVyOifFY){ufXYduxXfV = true;}
      else if(pFpVyOifFY == ETrgICfLXT){WViThMXkjG = true;}
      if(GDpljlZsnB == PTPVHmiWQT){tBEbJrnRNF = true;}
      else if(PTPVHmiWQT == GDpljlZsnB){XfuZNdxWrG = true;}
      if(jMkqToiRMJ == BJAcelhKtf){NVKBzTEcfn = true;}
      else if(BJAcelhKtf == jMkqToiRMJ){ydwOliouZs = true;}
      if(NVRRZTAcBg == FExMAGpJci){goXBSVPLpP = true;}
      else if(FExMAGpJci == NVRRZTAcBg){HXHGcZcCmm = true;}
      if(ROkWHbdClk == CCWyTQisZZ){PZUVZAXrGK = true;}
      else if(CCWyTQisZZ == ROkWHbdClk){JUOzUUxNRt = true;}
      if(LbmotqhANT == UrGxUgENpM){oziYtYUWYJ = true;}
      else if(UrGxUgENpM == LbmotqhANT){yJjZWrYUgz = true;}
      if(TNzOFjlXLQ == fYkYTLVDUB){qTrqnEcCIm = true;}
      if(lxrHjVaOjq == wYthRymCJN){bbbyonBobz = true;}
      if(LgebxlibWi == CnjTLNxArT){uMWVzhFzGs = true;}
      while(fYkYTLVDUB == TNzOFjlXLQ){WbKqzzXown = true;}
      while(wYthRymCJN == wYthRymCJN){AtjFxdPwsR = true;}
      while(CnjTLNxArT == CnjTLNxArT){kbdftxnhjk = true;}
      if(BcTQCcRxeI == true){BcTQCcRxeI = false;}
      if(ufXYduxXfV == true){ufXYduxXfV = false;}
      if(tBEbJrnRNF == true){tBEbJrnRNF = false;}
      if(NVKBzTEcfn == true){NVKBzTEcfn = false;}
      if(goXBSVPLpP == true){goXBSVPLpP = false;}
      if(PZUVZAXrGK == true){PZUVZAXrGK = false;}
      if(oziYtYUWYJ == true){oziYtYUWYJ = false;}
      if(qTrqnEcCIm == true){qTrqnEcCIm = false;}
      if(bbbyonBobz == true){bbbyonBobz = false;}
      if(uMWVzhFzGs == true){uMWVzhFzGs = false;}
      if(AsmfYwgcgU == true){AsmfYwgcgU = false;}
      if(WViThMXkjG == true){WViThMXkjG = false;}
      if(XfuZNdxWrG == true){XfuZNdxWrG = false;}
      if(ydwOliouZs == true){ydwOliouZs = false;}
      if(HXHGcZcCmm == true){HXHGcZcCmm = false;}
      if(JUOzUUxNRt == true){JUOzUUxNRt = false;}
      if(yJjZWrYUgz == true){yJjZWrYUgz = false;}
      if(WbKqzzXown == true){WbKqzzXown = false;}
      if(AtjFxdPwsR == true){AtjFxdPwsR = false;}
      if(kbdftxnhjk == true){kbdftxnhjk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIPPMURBIV
{ 
  void BeBLZMwGou()
  { 
      bool dkAaRMLMQc = false;
      bool cuJwBAzNfu = false;
      bool FmyZWVMZqH = false;
      bool IZIlMMrIOG = false;
      bool pqrwHSInnH = false;
      bool SYnwJqmZDu = false;
      bool zlVJUDmWjn = false;
      bool IpzZFNuBSE = false;
      bool MYlinjkMcV = false;
      bool ZRFSGDVibD = false;
      bool fkEzycYOpu = false;
      bool ukHzhaAlUk = false;
      bool RZtNNqkfTB = false;
      bool rMZOXbUljL = false;
      bool KWVhZnJFke = false;
      bool CjNplFqpkH = false;
      bool rrtnDiLsaG = false;
      bool GNBJZtDMnY = false;
      bool heunyHyibS = false;
      bool jdAcSRbhdp = false;
      string tFLrZwPsXU;
      string odGYdqSCJb;
      string rppnhjRUqY;
      string OAXBCnDmyA;
      string WhLXopoFtt;
      string binekEPWJp;
      string dtByGnFEWp;
      string mfEIEKdRzr;
      string tMawxfMsPx;
      string XfcHWcfNRA;
      string jjiEGueeZa;
      string ZxWRuRTEBa;
      string bMoYRHCwkb;
      string dQAzHJcWoB;
      string AgSoXaIKMF;
      string JbMqYWuKlz;
      string sityxJwXKk;
      string nwPzZutAAp;
      string yrjfSCEJZj;
      string OSjoIRlTqO;
      if(tFLrZwPsXU == jjiEGueeZa){dkAaRMLMQc = true;}
      else if(jjiEGueeZa == tFLrZwPsXU){fkEzycYOpu = true;}
      if(odGYdqSCJb == ZxWRuRTEBa){cuJwBAzNfu = true;}
      else if(ZxWRuRTEBa == odGYdqSCJb){ukHzhaAlUk = true;}
      if(rppnhjRUqY == bMoYRHCwkb){FmyZWVMZqH = true;}
      else if(bMoYRHCwkb == rppnhjRUqY){RZtNNqkfTB = true;}
      if(OAXBCnDmyA == dQAzHJcWoB){IZIlMMrIOG = true;}
      else if(dQAzHJcWoB == OAXBCnDmyA){rMZOXbUljL = true;}
      if(WhLXopoFtt == AgSoXaIKMF){pqrwHSInnH = true;}
      else if(AgSoXaIKMF == WhLXopoFtt){KWVhZnJFke = true;}
      if(binekEPWJp == JbMqYWuKlz){SYnwJqmZDu = true;}
      else if(JbMqYWuKlz == binekEPWJp){CjNplFqpkH = true;}
      if(dtByGnFEWp == sityxJwXKk){zlVJUDmWjn = true;}
      else if(sityxJwXKk == dtByGnFEWp){rrtnDiLsaG = true;}
      if(mfEIEKdRzr == nwPzZutAAp){IpzZFNuBSE = true;}
      if(tMawxfMsPx == yrjfSCEJZj){MYlinjkMcV = true;}
      if(XfcHWcfNRA == OSjoIRlTqO){ZRFSGDVibD = true;}
      while(nwPzZutAAp == mfEIEKdRzr){GNBJZtDMnY = true;}
      while(yrjfSCEJZj == yrjfSCEJZj){heunyHyibS = true;}
      while(OSjoIRlTqO == OSjoIRlTqO){jdAcSRbhdp = true;}
      if(dkAaRMLMQc == true){dkAaRMLMQc = false;}
      if(cuJwBAzNfu == true){cuJwBAzNfu = false;}
      if(FmyZWVMZqH == true){FmyZWVMZqH = false;}
      if(IZIlMMrIOG == true){IZIlMMrIOG = false;}
      if(pqrwHSInnH == true){pqrwHSInnH = false;}
      if(SYnwJqmZDu == true){SYnwJqmZDu = false;}
      if(zlVJUDmWjn == true){zlVJUDmWjn = false;}
      if(IpzZFNuBSE == true){IpzZFNuBSE = false;}
      if(MYlinjkMcV == true){MYlinjkMcV = false;}
      if(ZRFSGDVibD == true){ZRFSGDVibD = false;}
      if(fkEzycYOpu == true){fkEzycYOpu = false;}
      if(ukHzhaAlUk == true){ukHzhaAlUk = false;}
      if(RZtNNqkfTB == true){RZtNNqkfTB = false;}
      if(rMZOXbUljL == true){rMZOXbUljL = false;}
      if(KWVhZnJFke == true){KWVhZnJFke = false;}
      if(CjNplFqpkH == true){CjNplFqpkH = false;}
      if(rrtnDiLsaG == true){rrtnDiLsaG = false;}
      if(GNBJZtDMnY == true){GNBJZtDMnY = false;}
      if(heunyHyibS == true){heunyHyibS = false;}
      if(jdAcSRbhdp == true){jdAcSRbhdp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKIIOWCGFU
{ 
  void EHfqQLbdoc()
  { 
      bool wkRYIQJHEt = false;
      bool lekzkllotp = false;
      bool wRsNOCcGql = false;
      bool roAmHLyiDM = false;
      bool iwlOmcfZTb = false;
      bool VcpkkerEKG = false;
      bool mCPSBwdyrY = false;
      bool mCkhHzeeZl = false;
      bool VDmOPOzOBb = false;
      bool TtYxYffTMq = false;
      bool yhgtnSqHdk = false;
      bool zMdXjiPBCm = false;
      bool wPwPEsdnJb = false;
      bool TLRinmVrZx = false;
      bool XrkQcGPAMo = false;
      bool PeQZtilRou = false;
      bool nDyBRmuujx = false;
      bool NXaEPEdely = false;
      bool dcaTLntqnE = false;
      bool ADCeITtizo = false;
      string SPlmnsmYYk;
      string tsTMDPdLoJ;
      string xAfVitcRUL;
      string lGkbPnWfai;
      string RUytXDlCbN;
      string VjwKWSjPDs;
      string QUENznIqxO;
      string sxkGrbBkyf;
      string IapGpCJaEx;
      string EGcgRwQkui;
      string ttENUXzpSt;
      string QyRXkpdxXw;
      string dhmAJlUEnu;
      string LQoOkOVblR;
      string CTIKfFoEub;
      string RTNyELGEDh;
      string CtBWhzIDlW;
      string TBKFtKZbTE;
      string xQILcrDqJY;
      string HRYEOHSkbg;
      if(SPlmnsmYYk == ttENUXzpSt){wkRYIQJHEt = true;}
      else if(ttENUXzpSt == SPlmnsmYYk){yhgtnSqHdk = true;}
      if(tsTMDPdLoJ == QyRXkpdxXw){lekzkllotp = true;}
      else if(QyRXkpdxXw == tsTMDPdLoJ){zMdXjiPBCm = true;}
      if(xAfVitcRUL == dhmAJlUEnu){wRsNOCcGql = true;}
      else if(dhmAJlUEnu == xAfVitcRUL){wPwPEsdnJb = true;}
      if(lGkbPnWfai == LQoOkOVblR){roAmHLyiDM = true;}
      else if(LQoOkOVblR == lGkbPnWfai){TLRinmVrZx = true;}
      if(RUytXDlCbN == CTIKfFoEub){iwlOmcfZTb = true;}
      else if(CTIKfFoEub == RUytXDlCbN){XrkQcGPAMo = true;}
      if(VjwKWSjPDs == RTNyELGEDh){VcpkkerEKG = true;}
      else if(RTNyELGEDh == VjwKWSjPDs){PeQZtilRou = true;}
      if(QUENznIqxO == CtBWhzIDlW){mCPSBwdyrY = true;}
      else if(CtBWhzIDlW == QUENznIqxO){nDyBRmuujx = true;}
      if(sxkGrbBkyf == TBKFtKZbTE){mCkhHzeeZl = true;}
      if(IapGpCJaEx == xQILcrDqJY){VDmOPOzOBb = true;}
      if(EGcgRwQkui == HRYEOHSkbg){TtYxYffTMq = true;}
      while(TBKFtKZbTE == sxkGrbBkyf){NXaEPEdely = true;}
      while(xQILcrDqJY == xQILcrDqJY){dcaTLntqnE = true;}
      while(HRYEOHSkbg == HRYEOHSkbg){ADCeITtizo = true;}
      if(wkRYIQJHEt == true){wkRYIQJHEt = false;}
      if(lekzkllotp == true){lekzkllotp = false;}
      if(wRsNOCcGql == true){wRsNOCcGql = false;}
      if(roAmHLyiDM == true){roAmHLyiDM = false;}
      if(iwlOmcfZTb == true){iwlOmcfZTb = false;}
      if(VcpkkerEKG == true){VcpkkerEKG = false;}
      if(mCPSBwdyrY == true){mCPSBwdyrY = false;}
      if(mCkhHzeeZl == true){mCkhHzeeZl = false;}
      if(VDmOPOzOBb == true){VDmOPOzOBb = false;}
      if(TtYxYffTMq == true){TtYxYffTMq = false;}
      if(yhgtnSqHdk == true){yhgtnSqHdk = false;}
      if(zMdXjiPBCm == true){zMdXjiPBCm = false;}
      if(wPwPEsdnJb == true){wPwPEsdnJb = false;}
      if(TLRinmVrZx == true){TLRinmVrZx = false;}
      if(XrkQcGPAMo == true){XrkQcGPAMo = false;}
      if(PeQZtilRou == true){PeQZtilRou = false;}
      if(nDyBRmuujx == true){nDyBRmuujx = false;}
      if(NXaEPEdely == true){NXaEPEdely = false;}
      if(dcaTLntqnE == true){dcaTLntqnE = false;}
      if(ADCeITtizo == true){ADCeITtizo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMSMHHVMAH
{ 
  void OVxlLJRPOe()
  { 
      bool WNHLemqfPg = false;
      bool PglQFdDXjf = false;
      bool EGdouyMIMY = false;
      bool VHQFuGqQpu = false;
      bool qZcPzJzCla = false;
      bool xTrVhPiRPg = false;
      bool aiSpLIQfUz = false;
      bool mmgonedOpl = false;
      bool yJVlaBOtWf = false;
      bool WZAJTHGmEp = false;
      bool sThmmKlChC = false;
      bool lUadhQNgOJ = false;
      bool sVJobNlXUf = false;
      bool YpJArebhyP = false;
      bool OMMUtCyWaD = false;
      bool tZXuwXKrLZ = false;
      bool YOhBduKakC = false;
      bool nfhytgInuY = false;
      bool OPwRlyRODU = false;
      bool UjWXqAeLpy = false;
      string oewjJArPRg;
      string MlZlLcjjHI;
      string MVRrVDMmyx;
      string pypigSLthE;
      string FbSlHbbaPz;
      string cGhYbSNDNF;
      string mERUpOwqFs;
      string QpBCDkDejt;
      string blXzUjPQHN;
      string EIfbQAKyws;
      string ejVWhmEeVp;
      string PiSTdBgRAG;
      string yejqnIKZkC;
      string aEiqOqQBRh;
      string fkuQyVoLyP;
      string TryptzAehY;
      string cesSOKzbEl;
      string jfARZNjSrR;
      string TybViiFsxO;
      string qlSrFBqbCm;
      if(oewjJArPRg == ejVWhmEeVp){WNHLemqfPg = true;}
      else if(ejVWhmEeVp == oewjJArPRg){sThmmKlChC = true;}
      if(MlZlLcjjHI == PiSTdBgRAG){PglQFdDXjf = true;}
      else if(PiSTdBgRAG == MlZlLcjjHI){lUadhQNgOJ = true;}
      if(MVRrVDMmyx == yejqnIKZkC){EGdouyMIMY = true;}
      else if(yejqnIKZkC == MVRrVDMmyx){sVJobNlXUf = true;}
      if(pypigSLthE == aEiqOqQBRh){VHQFuGqQpu = true;}
      else if(aEiqOqQBRh == pypigSLthE){YpJArebhyP = true;}
      if(FbSlHbbaPz == fkuQyVoLyP){qZcPzJzCla = true;}
      else if(fkuQyVoLyP == FbSlHbbaPz){OMMUtCyWaD = true;}
      if(cGhYbSNDNF == TryptzAehY){xTrVhPiRPg = true;}
      else if(TryptzAehY == cGhYbSNDNF){tZXuwXKrLZ = true;}
      if(mERUpOwqFs == cesSOKzbEl){aiSpLIQfUz = true;}
      else if(cesSOKzbEl == mERUpOwqFs){YOhBduKakC = true;}
      if(QpBCDkDejt == jfARZNjSrR){mmgonedOpl = true;}
      if(blXzUjPQHN == TybViiFsxO){yJVlaBOtWf = true;}
      if(EIfbQAKyws == qlSrFBqbCm){WZAJTHGmEp = true;}
      while(jfARZNjSrR == QpBCDkDejt){nfhytgInuY = true;}
      while(TybViiFsxO == TybViiFsxO){OPwRlyRODU = true;}
      while(qlSrFBqbCm == qlSrFBqbCm){UjWXqAeLpy = true;}
      if(WNHLemqfPg == true){WNHLemqfPg = false;}
      if(PglQFdDXjf == true){PglQFdDXjf = false;}
      if(EGdouyMIMY == true){EGdouyMIMY = false;}
      if(VHQFuGqQpu == true){VHQFuGqQpu = false;}
      if(qZcPzJzCla == true){qZcPzJzCla = false;}
      if(xTrVhPiRPg == true){xTrVhPiRPg = false;}
      if(aiSpLIQfUz == true){aiSpLIQfUz = false;}
      if(mmgonedOpl == true){mmgonedOpl = false;}
      if(yJVlaBOtWf == true){yJVlaBOtWf = false;}
      if(WZAJTHGmEp == true){WZAJTHGmEp = false;}
      if(sThmmKlChC == true){sThmmKlChC = false;}
      if(lUadhQNgOJ == true){lUadhQNgOJ = false;}
      if(sVJobNlXUf == true){sVJobNlXUf = false;}
      if(YpJArebhyP == true){YpJArebhyP = false;}
      if(OMMUtCyWaD == true){OMMUtCyWaD = false;}
      if(tZXuwXKrLZ == true){tZXuwXKrLZ = false;}
      if(YOhBduKakC == true){YOhBduKakC = false;}
      if(nfhytgInuY == true){nfhytgInuY = false;}
      if(OPwRlyRODU == true){OPwRlyRODU = false;}
      if(UjWXqAeLpy == true){UjWXqAeLpy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MCMXNHYDNO
{ 
  void yjlSfVUdsr()
  { 
      bool eQsTrKJaAW = false;
      bool AwuwzJEHHa = false;
      bool BwuubRCfxO = false;
      bool qnpdhFuFpy = false;
      bool BRrwXjuEWK = false;
      bool deuQVhVyra = false;
      bool IddlfMFQNt = false;
      bool OyQJYiDzWq = false;
      bool VxIljLrYIA = false;
      bool iwNPpXnGPL = false;
      bool edqbweNlql = false;
      bool eWaAFKUqCT = false;
      bool TgINKRkBTB = false;
      bool uxiLMqGfpE = false;
      bool yGgWVMUMJe = false;
      bool DxEwqxVdRd = false;
      bool tMRppgnPnO = false;
      bool EnAxVNzlqy = false;
      bool xXqnxyrlUO = false;
      bool UbOMKknpfn = false;
      string oiCkWDpNSd;
      string WNcPMmrWqr;
      string utGrkywaCP;
      string aNuaudXtWG;
      string rReIQTtnZl;
      string xhKmlucJzY;
      string HPKCCJRBUh;
      string OxAjzcOxaQ;
      string DIBPSsDHnz;
      string ANuxzbGcGH;
      string BrSqWAgZnJ;
      string gfhhUyNujJ;
      string GKNUhBBCjW;
      string WlpTOLoKrS;
      string McTeSUeMcB;
      string OLrxAqeyJV;
      string ydpQluoOSI;
      string IDCRwdqhCM;
      string VoZiIKssSX;
      string gqBWThlDrX;
      if(oiCkWDpNSd == BrSqWAgZnJ){eQsTrKJaAW = true;}
      else if(BrSqWAgZnJ == oiCkWDpNSd){edqbweNlql = true;}
      if(WNcPMmrWqr == gfhhUyNujJ){AwuwzJEHHa = true;}
      else if(gfhhUyNujJ == WNcPMmrWqr){eWaAFKUqCT = true;}
      if(utGrkywaCP == GKNUhBBCjW){BwuubRCfxO = true;}
      else if(GKNUhBBCjW == utGrkywaCP){TgINKRkBTB = true;}
      if(aNuaudXtWG == WlpTOLoKrS){qnpdhFuFpy = true;}
      else if(WlpTOLoKrS == aNuaudXtWG){uxiLMqGfpE = true;}
      if(rReIQTtnZl == McTeSUeMcB){BRrwXjuEWK = true;}
      else if(McTeSUeMcB == rReIQTtnZl){yGgWVMUMJe = true;}
      if(xhKmlucJzY == OLrxAqeyJV){deuQVhVyra = true;}
      else if(OLrxAqeyJV == xhKmlucJzY){DxEwqxVdRd = true;}
      if(HPKCCJRBUh == ydpQluoOSI){IddlfMFQNt = true;}
      else if(ydpQluoOSI == HPKCCJRBUh){tMRppgnPnO = true;}
      if(OxAjzcOxaQ == IDCRwdqhCM){OyQJYiDzWq = true;}
      if(DIBPSsDHnz == VoZiIKssSX){VxIljLrYIA = true;}
      if(ANuxzbGcGH == gqBWThlDrX){iwNPpXnGPL = true;}
      while(IDCRwdqhCM == OxAjzcOxaQ){EnAxVNzlqy = true;}
      while(VoZiIKssSX == VoZiIKssSX){xXqnxyrlUO = true;}
      while(gqBWThlDrX == gqBWThlDrX){UbOMKknpfn = true;}
      if(eQsTrKJaAW == true){eQsTrKJaAW = false;}
      if(AwuwzJEHHa == true){AwuwzJEHHa = false;}
      if(BwuubRCfxO == true){BwuubRCfxO = false;}
      if(qnpdhFuFpy == true){qnpdhFuFpy = false;}
      if(BRrwXjuEWK == true){BRrwXjuEWK = false;}
      if(deuQVhVyra == true){deuQVhVyra = false;}
      if(IddlfMFQNt == true){IddlfMFQNt = false;}
      if(OyQJYiDzWq == true){OyQJYiDzWq = false;}
      if(VxIljLrYIA == true){VxIljLrYIA = false;}
      if(iwNPpXnGPL == true){iwNPpXnGPL = false;}
      if(edqbweNlql == true){edqbweNlql = false;}
      if(eWaAFKUqCT == true){eWaAFKUqCT = false;}
      if(TgINKRkBTB == true){TgINKRkBTB = false;}
      if(uxiLMqGfpE == true){uxiLMqGfpE = false;}
      if(yGgWVMUMJe == true){yGgWVMUMJe = false;}
      if(DxEwqxVdRd == true){DxEwqxVdRd = false;}
      if(tMRppgnPnO == true){tMRppgnPnO = false;}
      if(EnAxVNzlqy == true){EnAxVNzlqy = false;}
      if(xXqnxyrlUO == true){xXqnxyrlUO = false;}
      if(UbOMKknpfn == true){UbOMKknpfn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEACHICVWX
{ 
  void uxrHQAxHBr()
  { 
      bool nOwHmqzwII = false;
      bool kpjjGJpLUl = false;
      bool dCVCbSuAyc = false;
      bool gtanNpRbXB = false;
      bool HkrTUgoBDe = false;
      bool nuBNplrsfU = false;
      bool uyyfapOwVQ = false;
      bool qOnTdrJBht = false;
      bool dsxSnlsNyb = false;
      bool xYwCFImMsd = false;
      bool SsflnZHgix = false;
      bool bpKkqCBfqo = false;
      bool xAxsSSRkOU = false;
      bool FxIEbjNKeO = false;
      bool dLdAAGOKLD = false;
      bool HGUEfRulTU = false;
      bool HWSOrdhFJG = false;
      bool nqBcKkVxsL = false;
      bool DHYLNzbDXK = false;
      bool obpJGHsPIW = false;
      string bPgOnJSOqs;
      string ENxyrEpkwt;
      string iszRjdrDgl;
      string OsuaufAADK;
      string wYpFbWGnth;
      string gwAeVhQOdK;
      string RPgFdLSWDL;
      string EohkyKDtpM;
      string XEIzESrQEM;
      string PlVssfrkbP;
      string EijidqOOfL;
      string eWYQmMHgAL;
      string SBSpwRSorR;
      string SSRZInTYVN;
      string DdjrgsNEGg;
      string YKjQxCQtmL;
      string XYWNsMEyIy;
      string shKmHnRZJC;
      string EOiLrHhBcF;
      string WZlKoeHWzU;
      if(bPgOnJSOqs == EijidqOOfL){nOwHmqzwII = true;}
      else if(EijidqOOfL == bPgOnJSOqs){SsflnZHgix = true;}
      if(ENxyrEpkwt == eWYQmMHgAL){kpjjGJpLUl = true;}
      else if(eWYQmMHgAL == ENxyrEpkwt){bpKkqCBfqo = true;}
      if(iszRjdrDgl == SBSpwRSorR){dCVCbSuAyc = true;}
      else if(SBSpwRSorR == iszRjdrDgl){xAxsSSRkOU = true;}
      if(OsuaufAADK == SSRZInTYVN){gtanNpRbXB = true;}
      else if(SSRZInTYVN == OsuaufAADK){FxIEbjNKeO = true;}
      if(wYpFbWGnth == DdjrgsNEGg){HkrTUgoBDe = true;}
      else if(DdjrgsNEGg == wYpFbWGnth){dLdAAGOKLD = true;}
      if(gwAeVhQOdK == YKjQxCQtmL){nuBNplrsfU = true;}
      else if(YKjQxCQtmL == gwAeVhQOdK){HGUEfRulTU = true;}
      if(RPgFdLSWDL == XYWNsMEyIy){uyyfapOwVQ = true;}
      else if(XYWNsMEyIy == RPgFdLSWDL){HWSOrdhFJG = true;}
      if(EohkyKDtpM == shKmHnRZJC){qOnTdrJBht = true;}
      if(XEIzESrQEM == EOiLrHhBcF){dsxSnlsNyb = true;}
      if(PlVssfrkbP == WZlKoeHWzU){xYwCFImMsd = true;}
      while(shKmHnRZJC == EohkyKDtpM){nqBcKkVxsL = true;}
      while(EOiLrHhBcF == EOiLrHhBcF){DHYLNzbDXK = true;}
      while(WZlKoeHWzU == WZlKoeHWzU){obpJGHsPIW = true;}
      if(nOwHmqzwII == true){nOwHmqzwII = false;}
      if(kpjjGJpLUl == true){kpjjGJpLUl = false;}
      if(dCVCbSuAyc == true){dCVCbSuAyc = false;}
      if(gtanNpRbXB == true){gtanNpRbXB = false;}
      if(HkrTUgoBDe == true){HkrTUgoBDe = false;}
      if(nuBNplrsfU == true){nuBNplrsfU = false;}
      if(uyyfapOwVQ == true){uyyfapOwVQ = false;}
      if(qOnTdrJBht == true){qOnTdrJBht = false;}
      if(dsxSnlsNyb == true){dsxSnlsNyb = false;}
      if(xYwCFImMsd == true){xYwCFImMsd = false;}
      if(SsflnZHgix == true){SsflnZHgix = false;}
      if(bpKkqCBfqo == true){bpKkqCBfqo = false;}
      if(xAxsSSRkOU == true){xAxsSSRkOU = false;}
      if(FxIEbjNKeO == true){FxIEbjNKeO = false;}
      if(dLdAAGOKLD == true){dLdAAGOKLD = false;}
      if(HGUEfRulTU == true){HGUEfRulTU = false;}
      if(HWSOrdhFJG == true){HWSOrdhFJG = false;}
      if(nqBcKkVxsL == true){nqBcKkVxsL = false;}
      if(DHYLNzbDXK == true){DHYLNzbDXK = false;}
      if(obpJGHsPIW == true){obpJGHsPIW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCZBTOMFWX
{ 
  void ZoAmXjVzDp()
  { 
      bool QWuRFwxXmO = false;
      bool PWLTIFgNZZ = false;
      bool SWYpjmcBKj = false;
      bool lkIHIRcjIV = false;
      bool dPNUcNReCc = false;
      bool kParXtyEhS = false;
      bool TuMDceNDLq = false;
      bool cxFDwCIENV = false;
      bool UxzgyWJQjN = false;
      bool SXBoChCJqy = false;
      bool zNTKAmJWuU = false;
      bool ktqLxVweFF = false;
      bool UxTxXEwPBO = false;
      bool AzMPWGcngK = false;
      bool NlUObYgorf = false;
      bool kWElcCsVlu = false;
      bool qsVgTlhbop = false;
      bool sIytribEVz = false;
      bool XGXVcctalT = false;
      bool MHBkSTQnuo = false;
      string xMmfodnLpF;
      string YICwQKZoWs;
      string oHNBXOnVPm;
      string ZlxEwAnONO;
      string KacbmtpBWn;
      string rzUSApzkHa;
      string pSwDflLyzP;
      string WKaIiOelOd;
      string YmzauaRdEG;
      string BCHmYrdZuA;
      string iqBGRgXLjk;
      string KNWcBCTUHF;
      string UgtsNTCnjq;
      string jFpOtglrIN;
      string CFtSunedlV;
      string XJRpeCxIsx;
      string dibsAFWIiT;
      string QbMtCPlaxZ;
      string oXBNSamAir;
      string jcyKiScBRp;
      if(xMmfodnLpF == iqBGRgXLjk){QWuRFwxXmO = true;}
      else if(iqBGRgXLjk == xMmfodnLpF){zNTKAmJWuU = true;}
      if(YICwQKZoWs == KNWcBCTUHF){PWLTIFgNZZ = true;}
      else if(KNWcBCTUHF == YICwQKZoWs){ktqLxVweFF = true;}
      if(oHNBXOnVPm == UgtsNTCnjq){SWYpjmcBKj = true;}
      else if(UgtsNTCnjq == oHNBXOnVPm){UxTxXEwPBO = true;}
      if(ZlxEwAnONO == jFpOtglrIN){lkIHIRcjIV = true;}
      else if(jFpOtglrIN == ZlxEwAnONO){AzMPWGcngK = true;}
      if(KacbmtpBWn == CFtSunedlV){dPNUcNReCc = true;}
      else if(CFtSunedlV == KacbmtpBWn){NlUObYgorf = true;}
      if(rzUSApzkHa == XJRpeCxIsx){kParXtyEhS = true;}
      else if(XJRpeCxIsx == rzUSApzkHa){kWElcCsVlu = true;}
      if(pSwDflLyzP == dibsAFWIiT){TuMDceNDLq = true;}
      else if(dibsAFWIiT == pSwDflLyzP){qsVgTlhbop = true;}
      if(WKaIiOelOd == QbMtCPlaxZ){cxFDwCIENV = true;}
      if(YmzauaRdEG == oXBNSamAir){UxzgyWJQjN = true;}
      if(BCHmYrdZuA == jcyKiScBRp){SXBoChCJqy = true;}
      while(QbMtCPlaxZ == WKaIiOelOd){sIytribEVz = true;}
      while(oXBNSamAir == oXBNSamAir){XGXVcctalT = true;}
      while(jcyKiScBRp == jcyKiScBRp){MHBkSTQnuo = true;}
      if(QWuRFwxXmO == true){QWuRFwxXmO = false;}
      if(PWLTIFgNZZ == true){PWLTIFgNZZ = false;}
      if(SWYpjmcBKj == true){SWYpjmcBKj = false;}
      if(lkIHIRcjIV == true){lkIHIRcjIV = false;}
      if(dPNUcNReCc == true){dPNUcNReCc = false;}
      if(kParXtyEhS == true){kParXtyEhS = false;}
      if(TuMDceNDLq == true){TuMDceNDLq = false;}
      if(cxFDwCIENV == true){cxFDwCIENV = false;}
      if(UxzgyWJQjN == true){UxzgyWJQjN = false;}
      if(SXBoChCJqy == true){SXBoChCJqy = false;}
      if(zNTKAmJWuU == true){zNTKAmJWuU = false;}
      if(ktqLxVweFF == true){ktqLxVweFF = false;}
      if(UxTxXEwPBO == true){UxTxXEwPBO = false;}
      if(AzMPWGcngK == true){AzMPWGcngK = false;}
      if(NlUObYgorf == true){NlUObYgorf = false;}
      if(kWElcCsVlu == true){kWElcCsVlu = false;}
      if(qsVgTlhbop == true){qsVgTlhbop = false;}
      if(sIytribEVz == true){sIytribEVz = false;}
      if(XGXVcctalT == true){XGXVcctalT = false;}
      if(MHBkSTQnuo == true){MHBkSTQnuo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUGHERQEDJ
{ 
  void wAwfIAjVsF()
  { 
      bool DktLTWAhLb = false;
      bool nsBaGhYyyV = false;
      bool XGTWVTJtpt = false;
      bool YALVwUtsFL = false;
      bool DGEHXNgffb = false;
      bool PPVsrxQWpA = false;
      bool MFrQCmgedk = false;
      bool mesmSQCMyH = false;
      bool mdOOeJeScz = false;
      bool DXCEyyOmEk = false;
      bool gBCtnkVhaa = false;
      bool uDXhNiqdlr = false;
      bool HOBegPbnnU = false;
      bool COHNalaTZs = false;
      bool mwrCEzzUqP = false;
      bool HkBMcSzWNY = false;
      bool IhtGXguKHb = false;
      bool HWDrEKVzag = false;
      bool PHxXMRMujI = false;
      bool lEGBkFCleX = false;
      string XrFEfxMhKB;
      string yrVQiSiFXq;
      string wBBOBNEYwJ;
      string HPTHlzhjOk;
      string dyOrYCAglq;
      string nPHPIWqqCS;
      string snkBtiYOdi;
      string kzpmMylIoy;
      string NWlFUrHDyO;
      string IpguqpNNxp;
      string dkCCGoYUDK;
      string khBDFVBffC;
      string aUPPatSuuW;
      string kXLyUbUiyf;
      string SmAndancoV;
      string nghuPIUmbL;
      string WdYfYNWDic;
      string BRgzinUalA;
      string FoFZhDoPiL;
      string HhHlJoOTOP;
      if(XrFEfxMhKB == dkCCGoYUDK){DktLTWAhLb = true;}
      else if(dkCCGoYUDK == XrFEfxMhKB){gBCtnkVhaa = true;}
      if(yrVQiSiFXq == khBDFVBffC){nsBaGhYyyV = true;}
      else if(khBDFVBffC == yrVQiSiFXq){uDXhNiqdlr = true;}
      if(wBBOBNEYwJ == aUPPatSuuW){XGTWVTJtpt = true;}
      else if(aUPPatSuuW == wBBOBNEYwJ){HOBegPbnnU = true;}
      if(HPTHlzhjOk == kXLyUbUiyf){YALVwUtsFL = true;}
      else if(kXLyUbUiyf == HPTHlzhjOk){COHNalaTZs = true;}
      if(dyOrYCAglq == SmAndancoV){DGEHXNgffb = true;}
      else if(SmAndancoV == dyOrYCAglq){mwrCEzzUqP = true;}
      if(nPHPIWqqCS == nghuPIUmbL){PPVsrxQWpA = true;}
      else if(nghuPIUmbL == nPHPIWqqCS){HkBMcSzWNY = true;}
      if(snkBtiYOdi == WdYfYNWDic){MFrQCmgedk = true;}
      else if(WdYfYNWDic == snkBtiYOdi){IhtGXguKHb = true;}
      if(kzpmMylIoy == BRgzinUalA){mesmSQCMyH = true;}
      if(NWlFUrHDyO == FoFZhDoPiL){mdOOeJeScz = true;}
      if(IpguqpNNxp == HhHlJoOTOP){DXCEyyOmEk = true;}
      while(BRgzinUalA == kzpmMylIoy){HWDrEKVzag = true;}
      while(FoFZhDoPiL == FoFZhDoPiL){PHxXMRMujI = true;}
      while(HhHlJoOTOP == HhHlJoOTOP){lEGBkFCleX = true;}
      if(DktLTWAhLb == true){DktLTWAhLb = false;}
      if(nsBaGhYyyV == true){nsBaGhYyyV = false;}
      if(XGTWVTJtpt == true){XGTWVTJtpt = false;}
      if(YALVwUtsFL == true){YALVwUtsFL = false;}
      if(DGEHXNgffb == true){DGEHXNgffb = false;}
      if(PPVsrxQWpA == true){PPVsrxQWpA = false;}
      if(MFrQCmgedk == true){MFrQCmgedk = false;}
      if(mesmSQCMyH == true){mesmSQCMyH = false;}
      if(mdOOeJeScz == true){mdOOeJeScz = false;}
      if(DXCEyyOmEk == true){DXCEyyOmEk = false;}
      if(gBCtnkVhaa == true){gBCtnkVhaa = false;}
      if(uDXhNiqdlr == true){uDXhNiqdlr = false;}
      if(HOBegPbnnU == true){HOBegPbnnU = false;}
      if(COHNalaTZs == true){COHNalaTZs = false;}
      if(mwrCEzzUqP == true){mwrCEzzUqP = false;}
      if(HkBMcSzWNY == true){HkBMcSzWNY = false;}
      if(IhtGXguKHb == true){IhtGXguKHb = false;}
      if(HWDrEKVzag == true){HWDrEKVzag = false;}
      if(PHxXMRMujI == true){PHxXMRMujI = false;}
      if(lEGBkFCleX == true){lEGBkFCleX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUJSLKSAWF
{ 
  void cSUyhNXNSA()
  { 
      bool KjZEpscOkk = false;
      bool GDYKDxhykI = false;
      bool FqQBFpTkfN = false;
      bool raLpRmyWgt = false;
      bool IXRfGQMzVh = false;
      bool lBfyNTSXyA = false;
      bool ZrhWsfrhsP = false;
      bool yLRpAhZjun = false;
      bool cTPyaquMcy = false;
      bool TZXgUPotmZ = false;
      bool YeGFiaioye = false;
      bool thcKWFcjwB = false;
      bool keEtwYmkVj = false;
      bool rewUPyNJPz = false;
      bool HFOxEkwNJP = false;
      bool mFylosZLJJ = false;
      bool myTOmPkItX = false;
      bool rSUwseQHpK = false;
      bool bZaGwlfKeV = false;
      bool YBAFLIlzKo = false;
      string aAqRNXxspW;
      string tkutsEVHmJ;
      string obiYrMFyUw;
      string RyYHMmPpAh;
      string yUeilwdicF;
      string NWRwmzQRYB;
      string SyYtFuMngF;
      string neGFLUwzmw;
      string hVVPitgcTN;
      string WyRzOzwkdq;
      string ipBWQhQLkS;
      string DQebSwcILL;
      string NjTTipMHpL;
      string YLVuMrTyyA;
      string cUqBKFSofS;
      string WmYSdzWhnZ;
      string UIVZtqtiOa;
      string bdJKhrrSJc;
      string WXaXnklDRN;
      string UlKYeTzRGS;
      if(aAqRNXxspW == ipBWQhQLkS){KjZEpscOkk = true;}
      else if(ipBWQhQLkS == aAqRNXxspW){YeGFiaioye = true;}
      if(tkutsEVHmJ == DQebSwcILL){GDYKDxhykI = true;}
      else if(DQebSwcILL == tkutsEVHmJ){thcKWFcjwB = true;}
      if(obiYrMFyUw == NjTTipMHpL){FqQBFpTkfN = true;}
      else if(NjTTipMHpL == obiYrMFyUw){keEtwYmkVj = true;}
      if(RyYHMmPpAh == YLVuMrTyyA){raLpRmyWgt = true;}
      else if(YLVuMrTyyA == RyYHMmPpAh){rewUPyNJPz = true;}
      if(yUeilwdicF == cUqBKFSofS){IXRfGQMzVh = true;}
      else if(cUqBKFSofS == yUeilwdicF){HFOxEkwNJP = true;}
      if(NWRwmzQRYB == WmYSdzWhnZ){lBfyNTSXyA = true;}
      else if(WmYSdzWhnZ == NWRwmzQRYB){mFylosZLJJ = true;}
      if(SyYtFuMngF == UIVZtqtiOa){ZrhWsfrhsP = true;}
      else if(UIVZtqtiOa == SyYtFuMngF){myTOmPkItX = true;}
      if(neGFLUwzmw == bdJKhrrSJc){yLRpAhZjun = true;}
      if(hVVPitgcTN == WXaXnklDRN){cTPyaquMcy = true;}
      if(WyRzOzwkdq == UlKYeTzRGS){TZXgUPotmZ = true;}
      while(bdJKhrrSJc == neGFLUwzmw){rSUwseQHpK = true;}
      while(WXaXnklDRN == WXaXnklDRN){bZaGwlfKeV = true;}
      while(UlKYeTzRGS == UlKYeTzRGS){YBAFLIlzKo = true;}
      if(KjZEpscOkk == true){KjZEpscOkk = false;}
      if(GDYKDxhykI == true){GDYKDxhykI = false;}
      if(FqQBFpTkfN == true){FqQBFpTkfN = false;}
      if(raLpRmyWgt == true){raLpRmyWgt = false;}
      if(IXRfGQMzVh == true){IXRfGQMzVh = false;}
      if(lBfyNTSXyA == true){lBfyNTSXyA = false;}
      if(ZrhWsfrhsP == true){ZrhWsfrhsP = false;}
      if(yLRpAhZjun == true){yLRpAhZjun = false;}
      if(cTPyaquMcy == true){cTPyaquMcy = false;}
      if(TZXgUPotmZ == true){TZXgUPotmZ = false;}
      if(YeGFiaioye == true){YeGFiaioye = false;}
      if(thcKWFcjwB == true){thcKWFcjwB = false;}
      if(keEtwYmkVj == true){keEtwYmkVj = false;}
      if(rewUPyNJPz == true){rewUPyNJPz = false;}
      if(HFOxEkwNJP == true){HFOxEkwNJP = false;}
      if(mFylosZLJJ == true){mFylosZLJJ = false;}
      if(myTOmPkItX == true){myTOmPkItX = false;}
      if(rSUwseQHpK == true){rSUwseQHpK = false;}
      if(bZaGwlfKeV == true){bZaGwlfKeV = false;}
      if(YBAFLIlzKo == true){YBAFLIlzKo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVSETLKLXM
{ 
  void tXAZDsqRxH()
  { 
      bool Fpyikdeaoz = false;
      bool RJfXGbyeUj = false;
      bool pbrqVfhfDK = false;
      bool PQhslaCsWw = false;
      bool YwLfRotATY = false;
      bool wiCsHdyGNE = false;
      bool wzXejBamle = false;
      bool ZEIXKsQLZg = false;
      bool kgLeOfNnkH = false;
      bool cufRzYYfuQ = false;
      bool NGOnyqZdiO = false;
      bool MlggSPmrPD = false;
      bool mlCdCeYpYk = false;
      bool TjQJSdRXfX = false;
      bool GiFVupNyyj = false;
      bool lgQrcaEjlT = false;
      bool SiFxtcVXNn = false;
      bool xPMrxEffiL = false;
      bool QZrnzmTXfq = false;
      bool ZhlLEWcIaR = false;
      string efACrMjuKH;
      string wBbtkbPPcC;
      string duoynngHmw;
      string FaWDNAyCtd;
      string JycXeoWHbi;
      string PclyIjqBOE;
      string fbIOCUdXfj;
      string cNVyreRQTz;
      string RZfEfboYud;
      string JwnpygoOUJ;
      string KyaqFCGmGc;
      string RZhOmGwEhZ;
      string fFcCagZfAL;
      string oDwJnSyoyd;
      string UBRRLiOYCr;
      string kkftdFUXPY;
      string camtnNcXaT;
      string HGFEEdmLqq;
      string RAcHZEXBfi;
      string yaYZAtOWcy;
      if(efACrMjuKH == KyaqFCGmGc){Fpyikdeaoz = true;}
      else if(KyaqFCGmGc == efACrMjuKH){NGOnyqZdiO = true;}
      if(wBbtkbPPcC == RZhOmGwEhZ){RJfXGbyeUj = true;}
      else if(RZhOmGwEhZ == wBbtkbPPcC){MlggSPmrPD = true;}
      if(duoynngHmw == fFcCagZfAL){pbrqVfhfDK = true;}
      else if(fFcCagZfAL == duoynngHmw){mlCdCeYpYk = true;}
      if(FaWDNAyCtd == oDwJnSyoyd){PQhslaCsWw = true;}
      else if(oDwJnSyoyd == FaWDNAyCtd){TjQJSdRXfX = true;}
      if(JycXeoWHbi == UBRRLiOYCr){YwLfRotATY = true;}
      else if(UBRRLiOYCr == JycXeoWHbi){GiFVupNyyj = true;}
      if(PclyIjqBOE == kkftdFUXPY){wiCsHdyGNE = true;}
      else if(kkftdFUXPY == PclyIjqBOE){lgQrcaEjlT = true;}
      if(fbIOCUdXfj == camtnNcXaT){wzXejBamle = true;}
      else if(camtnNcXaT == fbIOCUdXfj){SiFxtcVXNn = true;}
      if(cNVyreRQTz == HGFEEdmLqq){ZEIXKsQLZg = true;}
      if(RZfEfboYud == RAcHZEXBfi){kgLeOfNnkH = true;}
      if(JwnpygoOUJ == yaYZAtOWcy){cufRzYYfuQ = true;}
      while(HGFEEdmLqq == cNVyreRQTz){xPMrxEffiL = true;}
      while(RAcHZEXBfi == RAcHZEXBfi){QZrnzmTXfq = true;}
      while(yaYZAtOWcy == yaYZAtOWcy){ZhlLEWcIaR = true;}
      if(Fpyikdeaoz == true){Fpyikdeaoz = false;}
      if(RJfXGbyeUj == true){RJfXGbyeUj = false;}
      if(pbrqVfhfDK == true){pbrqVfhfDK = false;}
      if(PQhslaCsWw == true){PQhslaCsWw = false;}
      if(YwLfRotATY == true){YwLfRotATY = false;}
      if(wiCsHdyGNE == true){wiCsHdyGNE = false;}
      if(wzXejBamle == true){wzXejBamle = false;}
      if(ZEIXKsQLZg == true){ZEIXKsQLZg = false;}
      if(kgLeOfNnkH == true){kgLeOfNnkH = false;}
      if(cufRzYYfuQ == true){cufRzYYfuQ = false;}
      if(NGOnyqZdiO == true){NGOnyqZdiO = false;}
      if(MlggSPmrPD == true){MlggSPmrPD = false;}
      if(mlCdCeYpYk == true){mlCdCeYpYk = false;}
      if(TjQJSdRXfX == true){TjQJSdRXfX = false;}
      if(GiFVupNyyj == true){GiFVupNyyj = false;}
      if(lgQrcaEjlT == true){lgQrcaEjlT = false;}
      if(SiFxtcVXNn == true){SiFxtcVXNn = false;}
      if(xPMrxEffiL == true){xPMrxEffiL = false;}
      if(QZrnzmTXfq == true){QZrnzmTXfq = false;}
      if(ZhlLEWcIaR == true){ZhlLEWcIaR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFNRKYGRTR
{ 
  void IZKQFEebNh()
  { 
      bool xHRFQRCDQY = false;
      bool UOkthuZLIG = false;
      bool LSMEcOsJwg = false;
      bool eTTGzTeWPH = false;
      bool GJEJLylyfU = false;
      bool dGIoLduMbC = false;
      bool XrHjsAuetO = false;
      bool QDwBABNCre = false;
      bool cudaCXKduU = false;
      bool YRtMiNCUPK = false;
      bool CHDQEaJGoJ = false;
      bool QrTxZcOfgU = false;
      bool pRiYpyJiSm = false;
      bool zslhbUqMWb = false;
      bool NDokEfywmG = false;
      bool yWntUkXdaG = false;
      bool QanCKWFlVE = false;
      bool kCIEHlbyTJ = false;
      bool AMwLnbFqNp = false;
      bool wNlQKmPmZh = false;
      string rUuSSEsclk;
      string eNpBMLCRxC;
      string bXmMPkzPYQ;
      string LgSIWeicNi;
      string CYGTckmUGO;
      string QerJAUghCg;
      string EdEUYythdg;
      string cZEOADQTjd;
      string xeIJzgoJHC;
      string yAafdXUlue;
      string qFqZlqZcJx;
      string EMyXjZUuUr;
      string JkZbhczXjb;
      string heYEmrmiWI;
      string GLzKxkBCwD;
      string DZQCVGePqJ;
      string rCrhOZntkq;
      string mkXMkxkPdw;
      string awbgYINVhf;
      string NXrNQESRuX;
      if(rUuSSEsclk == qFqZlqZcJx){xHRFQRCDQY = true;}
      else if(qFqZlqZcJx == rUuSSEsclk){CHDQEaJGoJ = true;}
      if(eNpBMLCRxC == EMyXjZUuUr){UOkthuZLIG = true;}
      else if(EMyXjZUuUr == eNpBMLCRxC){QrTxZcOfgU = true;}
      if(bXmMPkzPYQ == JkZbhczXjb){LSMEcOsJwg = true;}
      else if(JkZbhczXjb == bXmMPkzPYQ){pRiYpyJiSm = true;}
      if(LgSIWeicNi == heYEmrmiWI){eTTGzTeWPH = true;}
      else if(heYEmrmiWI == LgSIWeicNi){zslhbUqMWb = true;}
      if(CYGTckmUGO == GLzKxkBCwD){GJEJLylyfU = true;}
      else if(GLzKxkBCwD == CYGTckmUGO){NDokEfywmG = true;}
      if(QerJAUghCg == DZQCVGePqJ){dGIoLduMbC = true;}
      else if(DZQCVGePqJ == QerJAUghCg){yWntUkXdaG = true;}
      if(EdEUYythdg == rCrhOZntkq){XrHjsAuetO = true;}
      else if(rCrhOZntkq == EdEUYythdg){QanCKWFlVE = true;}
      if(cZEOADQTjd == mkXMkxkPdw){QDwBABNCre = true;}
      if(xeIJzgoJHC == awbgYINVhf){cudaCXKduU = true;}
      if(yAafdXUlue == NXrNQESRuX){YRtMiNCUPK = true;}
      while(mkXMkxkPdw == cZEOADQTjd){kCIEHlbyTJ = true;}
      while(awbgYINVhf == awbgYINVhf){AMwLnbFqNp = true;}
      while(NXrNQESRuX == NXrNQESRuX){wNlQKmPmZh = true;}
      if(xHRFQRCDQY == true){xHRFQRCDQY = false;}
      if(UOkthuZLIG == true){UOkthuZLIG = false;}
      if(LSMEcOsJwg == true){LSMEcOsJwg = false;}
      if(eTTGzTeWPH == true){eTTGzTeWPH = false;}
      if(GJEJLylyfU == true){GJEJLylyfU = false;}
      if(dGIoLduMbC == true){dGIoLduMbC = false;}
      if(XrHjsAuetO == true){XrHjsAuetO = false;}
      if(QDwBABNCre == true){QDwBABNCre = false;}
      if(cudaCXKduU == true){cudaCXKduU = false;}
      if(YRtMiNCUPK == true){YRtMiNCUPK = false;}
      if(CHDQEaJGoJ == true){CHDQEaJGoJ = false;}
      if(QrTxZcOfgU == true){QrTxZcOfgU = false;}
      if(pRiYpyJiSm == true){pRiYpyJiSm = false;}
      if(zslhbUqMWb == true){zslhbUqMWb = false;}
      if(NDokEfywmG == true){NDokEfywmG = false;}
      if(yWntUkXdaG == true){yWntUkXdaG = false;}
      if(QanCKWFlVE == true){QanCKWFlVE = false;}
      if(kCIEHlbyTJ == true){kCIEHlbyTJ = false;}
      if(AMwLnbFqNp == true){AMwLnbFqNp = false;}
      if(wNlQKmPmZh == true){wNlQKmPmZh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXJUASFYWQ
{ 
  void BPBRNXqulN()
  { 
      bool ftnflVPBFo = false;
      bool wzfxPpPqhm = false;
      bool bKMsjqXLok = false;
      bool QmQfwgqtSE = false;
      bool fJHuzSStmV = false;
      bool TNhGQVhuwt = false;
      bool xDLTXIhzBi = false;
      bool yUYdGSDRsQ = false;
      bool YcYTQCEKPa = false;
      bool zwyXGbxmWp = false;
      bool kSsDWzoEzy = false;
      bool SQBfUUeqDV = false;
      bool EWjZjBWAWe = false;
      bool UPtCfGjUxQ = false;
      bool NAKRIitSDl = false;
      bool wFiBlNiSTU = false;
      bool cogUcCVzAO = false;
      bool kKtlIELSRB = false;
      bool HExkiOfrQR = false;
      bool XQAbnYSpnG = false;
      string kWVotMslJY;
      string DbhXdGrkZR;
      string ViDDerIgVN;
      string AFBKkhCWOY;
      string iFhtcFTwFP;
      string AXcFYCSRJC;
      string EMQwYxaXmw;
      string DVVAiPAIZZ;
      string XLbGMcbwkh;
      string OjMMUVolVe;
      string dwJILeBbVI;
      string BKrjdrjJiw;
      string VdlEgTIJfM;
      string aOltubCTuh;
      string aAZbfErchb;
      string leDZJAJEaq;
      string VquIhmXxnB;
      string pQOBUUEKYc;
      string bfaEZuLMju;
      string RyrDLjEQsr;
      if(kWVotMslJY == dwJILeBbVI){ftnflVPBFo = true;}
      else if(dwJILeBbVI == kWVotMslJY){kSsDWzoEzy = true;}
      if(DbhXdGrkZR == BKrjdrjJiw){wzfxPpPqhm = true;}
      else if(BKrjdrjJiw == DbhXdGrkZR){SQBfUUeqDV = true;}
      if(ViDDerIgVN == VdlEgTIJfM){bKMsjqXLok = true;}
      else if(VdlEgTIJfM == ViDDerIgVN){EWjZjBWAWe = true;}
      if(AFBKkhCWOY == aOltubCTuh){QmQfwgqtSE = true;}
      else if(aOltubCTuh == AFBKkhCWOY){UPtCfGjUxQ = true;}
      if(iFhtcFTwFP == aAZbfErchb){fJHuzSStmV = true;}
      else if(aAZbfErchb == iFhtcFTwFP){NAKRIitSDl = true;}
      if(AXcFYCSRJC == leDZJAJEaq){TNhGQVhuwt = true;}
      else if(leDZJAJEaq == AXcFYCSRJC){wFiBlNiSTU = true;}
      if(EMQwYxaXmw == VquIhmXxnB){xDLTXIhzBi = true;}
      else if(VquIhmXxnB == EMQwYxaXmw){cogUcCVzAO = true;}
      if(DVVAiPAIZZ == pQOBUUEKYc){yUYdGSDRsQ = true;}
      if(XLbGMcbwkh == bfaEZuLMju){YcYTQCEKPa = true;}
      if(OjMMUVolVe == RyrDLjEQsr){zwyXGbxmWp = true;}
      while(pQOBUUEKYc == DVVAiPAIZZ){kKtlIELSRB = true;}
      while(bfaEZuLMju == bfaEZuLMju){HExkiOfrQR = true;}
      while(RyrDLjEQsr == RyrDLjEQsr){XQAbnYSpnG = true;}
      if(ftnflVPBFo == true){ftnflVPBFo = false;}
      if(wzfxPpPqhm == true){wzfxPpPqhm = false;}
      if(bKMsjqXLok == true){bKMsjqXLok = false;}
      if(QmQfwgqtSE == true){QmQfwgqtSE = false;}
      if(fJHuzSStmV == true){fJHuzSStmV = false;}
      if(TNhGQVhuwt == true){TNhGQVhuwt = false;}
      if(xDLTXIhzBi == true){xDLTXIhzBi = false;}
      if(yUYdGSDRsQ == true){yUYdGSDRsQ = false;}
      if(YcYTQCEKPa == true){YcYTQCEKPa = false;}
      if(zwyXGbxmWp == true){zwyXGbxmWp = false;}
      if(kSsDWzoEzy == true){kSsDWzoEzy = false;}
      if(SQBfUUeqDV == true){SQBfUUeqDV = false;}
      if(EWjZjBWAWe == true){EWjZjBWAWe = false;}
      if(UPtCfGjUxQ == true){UPtCfGjUxQ = false;}
      if(NAKRIitSDl == true){NAKRIitSDl = false;}
      if(wFiBlNiSTU == true){wFiBlNiSTU = false;}
      if(cogUcCVzAO == true){cogUcCVzAO = false;}
      if(kKtlIELSRB == true){kKtlIELSRB = false;}
      if(HExkiOfrQR == true){HExkiOfrQR = false;}
      if(XQAbnYSpnG == true){XQAbnYSpnG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNUAFFRBJH
{ 
  void ROQdmObXtl()
  { 
      bool DOBQAeugad = false;
      bool MSuQrmCXzg = false;
      bool WnGucIcYrI = false;
      bool GdugXSzHHS = false;
      bool PTKztCEHWV = false;
      bool FMzeZPHFmq = false;
      bool BVnSWiXNsY = false;
      bool muPgQDdGBZ = false;
      bool DVCWCtdPHI = false;
      bool KtTQQserbL = false;
      bool epOxiKxSOV = false;
      bool kAENnfTRPc = false;
      bool EHGjOrazPW = false;
      bool XldouNGEmq = false;
      bool wLBkXJpGbk = false;
      bool ZNbzGXjdip = false;
      bool jyCqxyVORa = false;
      bool YPeXfsFUME = false;
      bool CUWexKKehW = false;
      bool ccVwHyIJnY = false;
      string TfjjjikleH;
      string pcZinKVdiT;
      string fqJYYMBAQp;
      string JUfaFCtOfY;
      string mdYoxMhCjW;
      string ALHImbWKLX;
      string gkUoxUxyck;
      string PHxJfBSTaM;
      string dyQtpxNXnd;
      string fiCIrBIiqb;
      string PiYyGrOxbk;
      string ICizshUazz;
      string HYKzFgEnRe;
      string sjczxtZRnx;
      string iPwDUczDPJ;
      string ghiqUpYZsY;
      string nafwrXZjCy;
      string ICmCQqcGdb;
      string gBXIxKAkdG;
      string UAYOJIjzLx;
      if(TfjjjikleH == PiYyGrOxbk){DOBQAeugad = true;}
      else if(PiYyGrOxbk == TfjjjikleH){epOxiKxSOV = true;}
      if(pcZinKVdiT == ICizshUazz){MSuQrmCXzg = true;}
      else if(ICizshUazz == pcZinKVdiT){kAENnfTRPc = true;}
      if(fqJYYMBAQp == HYKzFgEnRe){WnGucIcYrI = true;}
      else if(HYKzFgEnRe == fqJYYMBAQp){EHGjOrazPW = true;}
      if(JUfaFCtOfY == sjczxtZRnx){GdugXSzHHS = true;}
      else if(sjczxtZRnx == JUfaFCtOfY){XldouNGEmq = true;}
      if(mdYoxMhCjW == iPwDUczDPJ){PTKztCEHWV = true;}
      else if(iPwDUczDPJ == mdYoxMhCjW){wLBkXJpGbk = true;}
      if(ALHImbWKLX == ghiqUpYZsY){FMzeZPHFmq = true;}
      else if(ghiqUpYZsY == ALHImbWKLX){ZNbzGXjdip = true;}
      if(gkUoxUxyck == nafwrXZjCy){BVnSWiXNsY = true;}
      else if(nafwrXZjCy == gkUoxUxyck){jyCqxyVORa = true;}
      if(PHxJfBSTaM == ICmCQqcGdb){muPgQDdGBZ = true;}
      if(dyQtpxNXnd == gBXIxKAkdG){DVCWCtdPHI = true;}
      if(fiCIrBIiqb == UAYOJIjzLx){KtTQQserbL = true;}
      while(ICmCQqcGdb == PHxJfBSTaM){YPeXfsFUME = true;}
      while(gBXIxKAkdG == gBXIxKAkdG){CUWexKKehW = true;}
      while(UAYOJIjzLx == UAYOJIjzLx){ccVwHyIJnY = true;}
      if(DOBQAeugad == true){DOBQAeugad = false;}
      if(MSuQrmCXzg == true){MSuQrmCXzg = false;}
      if(WnGucIcYrI == true){WnGucIcYrI = false;}
      if(GdugXSzHHS == true){GdugXSzHHS = false;}
      if(PTKztCEHWV == true){PTKztCEHWV = false;}
      if(FMzeZPHFmq == true){FMzeZPHFmq = false;}
      if(BVnSWiXNsY == true){BVnSWiXNsY = false;}
      if(muPgQDdGBZ == true){muPgQDdGBZ = false;}
      if(DVCWCtdPHI == true){DVCWCtdPHI = false;}
      if(KtTQQserbL == true){KtTQQserbL = false;}
      if(epOxiKxSOV == true){epOxiKxSOV = false;}
      if(kAENnfTRPc == true){kAENnfTRPc = false;}
      if(EHGjOrazPW == true){EHGjOrazPW = false;}
      if(XldouNGEmq == true){XldouNGEmq = false;}
      if(wLBkXJpGbk == true){wLBkXJpGbk = false;}
      if(ZNbzGXjdip == true){ZNbzGXjdip = false;}
      if(jyCqxyVORa == true){jyCqxyVORa = false;}
      if(YPeXfsFUME == true){YPeXfsFUME = false;}
      if(CUWexKKehW == true){CUWexKKehW = false;}
      if(ccVwHyIJnY == true){ccVwHyIJnY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDQWRMKDZX
{ 
  void FobIAjhpBk()
  { 
      bool zANSyCgeCY = false;
      bool xyzmFNputb = false;
      bool bynnxgUSMs = false;
      bool uzeRfLGHpk = false;
      bool izoOlGsEdq = false;
      bool FFatWBLYUR = false;
      bool hOSJcySgHs = false;
      bool GiFIrbIYCq = false;
      bool mPnUnoYkud = false;
      bool zhlYCUfflm = false;
      bool mMxjkVARBt = false;
      bool rlVddSZyVm = false;
      bool ZhlctXwfFX = false;
      bool ucmPDaREjR = false;
      bool oGiAlMMHtj = false;
      bool uhJyNEZTpM = false;
      bool YTLdyOyGZC = false;
      bool AVODySykqh = false;
      bool LokVcNToBy = false;
      bool AyNWrUtFCW = false;
      string LyhGmQFVFp;
      string QjGFEOpjEL;
      string hDxiqIndMc;
      string OAWjwRMZJj;
      string RubUUBltbG;
      string DnRgdIBzOe;
      string bbIcbQMVIl;
      string BQaUtlabNp;
      string VsBFYZhpFm;
      string PNKeHplzsE;
      string oQkoFmNxmq;
      string hZkYIhZDDB;
      string hWPVVnFwNE;
      string zaiJBFIMAl;
      string MkCNFpbkVY;
      string QiwqVRAPTQ;
      string gQjhrGpbXC;
      string ZNCQnxTBQf;
      string LTZnnPermi;
      string FsriEuBUVy;
      if(LyhGmQFVFp == oQkoFmNxmq){zANSyCgeCY = true;}
      else if(oQkoFmNxmq == LyhGmQFVFp){mMxjkVARBt = true;}
      if(QjGFEOpjEL == hZkYIhZDDB){xyzmFNputb = true;}
      else if(hZkYIhZDDB == QjGFEOpjEL){rlVddSZyVm = true;}
      if(hDxiqIndMc == hWPVVnFwNE){bynnxgUSMs = true;}
      else if(hWPVVnFwNE == hDxiqIndMc){ZhlctXwfFX = true;}
      if(OAWjwRMZJj == zaiJBFIMAl){uzeRfLGHpk = true;}
      else if(zaiJBFIMAl == OAWjwRMZJj){ucmPDaREjR = true;}
      if(RubUUBltbG == MkCNFpbkVY){izoOlGsEdq = true;}
      else if(MkCNFpbkVY == RubUUBltbG){oGiAlMMHtj = true;}
      if(DnRgdIBzOe == QiwqVRAPTQ){FFatWBLYUR = true;}
      else if(QiwqVRAPTQ == DnRgdIBzOe){uhJyNEZTpM = true;}
      if(bbIcbQMVIl == gQjhrGpbXC){hOSJcySgHs = true;}
      else if(gQjhrGpbXC == bbIcbQMVIl){YTLdyOyGZC = true;}
      if(BQaUtlabNp == ZNCQnxTBQf){GiFIrbIYCq = true;}
      if(VsBFYZhpFm == LTZnnPermi){mPnUnoYkud = true;}
      if(PNKeHplzsE == FsriEuBUVy){zhlYCUfflm = true;}
      while(ZNCQnxTBQf == BQaUtlabNp){AVODySykqh = true;}
      while(LTZnnPermi == LTZnnPermi){LokVcNToBy = true;}
      while(FsriEuBUVy == FsriEuBUVy){AyNWrUtFCW = true;}
      if(zANSyCgeCY == true){zANSyCgeCY = false;}
      if(xyzmFNputb == true){xyzmFNputb = false;}
      if(bynnxgUSMs == true){bynnxgUSMs = false;}
      if(uzeRfLGHpk == true){uzeRfLGHpk = false;}
      if(izoOlGsEdq == true){izoOlGsEdq = false;}
      if(FFatWBLYUR == true){FFatWBLYUR = false;}
      if(hOSJcySgHs == true){hOSJcySgHs = false;}
      if(GiFIrbIYCq == true){GiFIrbIYCq = false;}
      if(mPnUnoYkud == true){mPnUnoYkud = false;}
      if(zhlYCUfflm == true){zhlYCUfflm = false;}
      if(mMxjkVARBt == true){mMxjkVARBt = false;}
      if(rlVddSZyVm == true){rlVddSZyVm = false;}
      if(ZhlctXwfFX == true){ZhlctXwfFX = false;}
      if(ucmPDaREjR == true){ucmPDaREjR = false;}
      if(oGiAlMMHtj == true){oGiAlMMHtj = false;}
      if(uhJyNEZTpM == true){uhJyNEZTpM = false;}
      if(YTLdyOyGZC == true){YTLdyOyGZC = false;}
      if(AVODySykqh == true){AVODySykqh = false;}
      if(LokVcNToBy == true){LokVcNToBy = false;}
      if(AyNWrUtFCW == true){AyNWrUtFCW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNFADXIJQG
{ 
  void IqpGDaNcRA()
  { 
      bool jCOCZFFJih = false;
      bool DMQQhhmCJI = false;
      bool JCDXJKgHNO = false;
      bool WqbZWBNPee = false;
      bool aEpHYWnXxo = false;
      bool ghHSMhzpsP = false;
      bool XywUKMjqsg = false;
      bool UWXdhELuzm = false;
      bool VIJXhnjJMo = false;
      bool CWWOHcIVxL = false;
      bool lweQUJKdkH = false;
      bool VDqFtOnXmW = false;
      bool caeDdyzIWE = false;
      bool wpymAYdsDX = false;
      bool cFXESyeQUr = false;
      bool okiZiLRalV = false;
      bool JBGgLfFDFU = false;
      bool kuTOsWCZkf = false;
      bool ShndOLGXEo = false;
      bool HCGgNazqsm = false;
      string iyxxVxrIma;
      string LihqggNdyX;
      string aiFDllrDEk;
      string URxaZbNPZd;
      string ACOiiRwUxD;
      string AYWepArsKj;
      string FoECFtlHQE;
      string SxETXYTWUU;
      string oWFAjutRjZ;
      string iTFpYKxMco;
      string fnEsjCUCGR;
      string fVYothiESK;
      string zTWpUyrOuM;
      string aHseoASMQh;
      string arLStNuPup;
      string bstSoMQNXk;
      string KGHtpXcsAs;
      string PVmjiHIEwH;
      string DbSFkgNZpc;
      string iFoeWUjQbW;
      if(iyxxVxrIma == fnEsjCUCGR){jCOCZFFJih = true;}
      else if(fnEsjCUCGR == iyxxVxrIma){lweQUJKdkH = true;}
      if(LihqggNdyX == fVYothiESK){DMQQhhmCJI = true;}
      else if(fVYothiESK == LihqggNdyX){VDqFtOnXmW = true;}
      if(aiFDllrDEk == zTWpUyrOuM){JCDXJKgHNO = true;}
      else if(zTWpUyrOuM == aiFDllrDEk){caeDdyzIWE = true;}
      if(URxaZbNPZd == aHseoASMQh){WqbZWBNPee = true;}
      else if(aHseoASMQh == URxaZbNPZd){wpymAYdsDX = true;}
      if(ACOiiRwUxD == arLStNuPup){aEpHYWnXxo = true;}
      else if(arLStNuPup == ACOiiRwUxD){cFXESyeQUr = true;}
      if(AYWepArsKj == bstSoMQNXk){ghHSMhzpsP = true;}
      else if(bstSoMQNXk == AYWepArsKj){okiZiLRalV = true;}
      if(FoECFtlHQE == KGHtpXcsAs){XywUKMjqsg = true;}
      else if(KGHtpXcsAs == FoECFtlHQE){JBGgLfFDFU = true;}
      if(SxETXYTWUU == PVmjiHIEwH){UWXdhELuzm = true;}
      if(oWFAjutRjZ == DbSFkgNZpc){VIJXhnjJMo = true;}
      if(iTFpYKxMco == iFoeWUjQbW){CWWOHcIVxL = true;}
      while(PVmjiHIEwH == SxETXYTWUU){kuTOsWCZkf = true;}
      while(DbSFkgNZpc == DbSFkgNZpc){ShndOLGXEo = true;}
      while(iFoeWUjQbW == iFoeWUjQbW){HCGgNazqsm = true;}
      if(jCOCZFFJih == true){jCOCZFFJih = false;}
      if(DMQQhhmCJI == true){DMQQhhmCJI = false;}
      if(JCDXJKgHNO == true){JCDXJKgHNO = false;}
      if(WqbZWBNPee == true){WqbZWBNPee = false;}
      if(aEpHYWnXxo == true){aEpHYWnXxo = false;}
      if(ghHSMhzpsP == true){ghHSMhzpsP = false;}
      if(XywUKMjqsg == true){XywUKMjqsg = false;}
      if(UWXdhELuzm == true){UWXdhELuzm = false;}
      if(VIJXhnjJMo == true){VIJXhnjJMo = false;}
      if(CWWOHcIVxL == true){CWWOHcIVxL = false;}
      if(lweQUJKdkH == true){lweQUJKdkH = false;}
      if(VDqFtOnXmW == true){VDqFtOnXmW = false;}
      if(caeDdyzIWE == true){caeDdyzIWE = false;}
      if(wpymAYdsDX == true){wpymAYdsDX = false;}
      if(cFXESyeQUr == true){cFXESyeQUr = false;}
      if(okiZiLRalV == true){okiZiLRalV = false;}
      if(JBGgLfFDFU == true){JBGgLfFDFU = false;}
      if(kuTOsWCZkf == true){kuTOsWCZkf = false;}
      if(ShndOLGXEo == true){ShndOLGXEo = false;}
      if(HCGgNazqsm == true){HCGgNazqsm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FYTIBJYNNG
{ 
  void uUTyoPEdVD()
  { 
      bool BsDaPWUKeD = false;
      bool moJSykDAmp = false;
      bool xLtrdzlqWM = false;
      bool mdIkYBfjpr = false;
      bool WcSyJSlxjW = false;
      bool yMmSfpzLxP = false;
      bool jcnSPJgYsw = false;
      bool ETKuTTswiK = false;
      bool MoGANZppEi = false;
      bool CTlZHsozhz = false;
      bool lNDmRdCrzL = false;
      bool wCclDuWmEo = false;
      bool SqTKtjgjmZ = false;
      bool esNiYylSij = false;
      bool XyqslzqzVM = false;
      bool WBurgutrsh = false;
      bool xREYgDotNE = false;
      bool JDEURTAZXu = false;
      bool rgNaDcxUBd = false;
      bool DsZBlFsRMi = false;
      string pZngsRWXAG;
      string IkdeSEJeBL;
      string iBOHpNgTQT;
      string ZBiKUVZLsK;
      string mCaCebiLcJ;
      string uXMOzoLfqf;
      string kCHffHCTJw;
      string exkpYfZMcN;
      string eVpGYCnTKe;
      string KsUNZkuuVW;
      string ZPBfexlVpS;
      string PzCcAOLBGd;
      string ShIdlkbXQn;
      string kdpFnOTJbb;
      string PScqPKprMK;
      string YtorDrGXts;
      string UOFChlIwnl;
      string uBZdNAEROa;
      string ujKFOqnxCw;
      string HwPhHBMaJc;
      if(pZngsRWXAG == ZPBfexlVpS){BsDaPWUKeD = true;}
      else if(ZPBfexlVpS == pZngsRWXAG){lNDmRdCrzL = true;}
      if(IkdeSEJeBL == PzCcAOLBGd){moJSykDAmp = true;}
      else if(PzCcAOLBGd == IkdeSEJeBL){wCclDuWmEo = true;}
      if(iBOHpNgTQT == ShIdlkbXQn){xLtrdzlqWM = true;}
      else if(ShIdlkbXQn == iBOHpNgTQT){SqTKtjgjmZ = true;}
      if(ZBiKUVZLsK == kdpFnOTJbb){mdIkYBfjpr = true;}
      else if(kdpFnOTJbb == ZBiKUVZLsK){esNiYylSij = true;}
      if(mCaCebiLcJ == PScqPKprMK){WcSyJSlxjW = true;}
      else if(PScqPKprMK == mCaCebiLcJ){XyqslzqzVM = true;}
      if(uXMOzoLfqf == YtorDrGXts){yMmSfpzLxP = true;}
      else if(YtorDrGXts == uXMOzoLfqf){WBurgutrsh = true;}
      if(kCHffHCTJw == UOFChlIwnl){jcnSPJgYsw = true;}
      else if(UOFChlIwnl == kCHffHCTJw){xREYgDotNE = true;}
      if(exkpYfZMcN == uBZdNAEROa){ETKuTTswiK = true;}
      if(eVpGYCnTKe == ujKFOqnxCw){MoGANZppEi = true;}
      if(KsUNZkuuVW == HwPhHBMaJc){CTlZHsozhz = true;}
      while(uBZdNAEROa == exkpYfZMcN){JDEURTAZXu = true;}
      while(ujKFOqnxCw == ujKFOqnxCw){rgNaDcxUBd = true;}
      while(HwPhHBMaJc == HwPhHBMaJc){DsZBlFsRMi = true;}
      if(BsDaPWUKeD == true){BsDaPWUKeD = false;}
      if(moJSykDAmp == true){moJSykDAmp = false;}
      if(xLtrdzlqWM == true){xLtrdzlqWM = false;}
      if(mdIkYBfjpr == true){mdIkYBfjpr = false;}
      if(WcSyJSlxjW == true){WcSyJSlxjW = false;}
      if(yMmSfpzLxP == true){yMmSfpzLxP = false;}
      if(jcnSPJgYsw == true){jcnSPJgYsw = false;}
      if(ETKuTTswiK == true){ETKuTTswiK = false;}
      if(MoGANZppEi == true){MoGANZppEi = false;}
      if(CTlZHsozhz == true){CTlZHsozhz = false;}
      if(lNDmRdCrzL == true){lNDmRdCrzL = false;}
      if(wCclDuWmEo == true){wCclDuWmEo = false;}
      if(SqTKtjgjmZ == true){SqTKtjgjmZ = false;}
      if(esNiYylSij == true){esNiYylSij = false;}
      if(XyqslzqzVM == true){XyqslzqzVM = false;}
      if(WBurgutrsh == true){WBurgutrsh = false;}
      if(xREYgDotNE == true){xREYgDotNE = false;}
      if(JDEURTAZXu == true){JDEURTAZXu = false;}
      if(rgNaDcxUBd == true){rgNaDcxUBd = false;}
      if(DsZBlFsRMi == true){DsZBlFsRMi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSJVXTIVKI
{ 
  void eQRJLxSGlg()
  { 
      bool kiwWufFOyB = false;
      bool BIXtuKSgcW = false;
      bool bQuXCoaCDo = false;
      bool zGFEazAxDe = false;
      bool TSSPOUIeUX = false;
      bool KegNPUmYTF = false;
      bool FCKIBuCSTu = false;
      bool JUcxCJxfIg = false;
      bool gwhfeUYroF = false;
      bool LbcyZRIKNT = false;
      bool SpKYNoBiKG = false;
      bool XHPmYITddf = false;
      bool VKdNjgqdWk = false;
      bool BlRoOpkJSo = false;
      bool SoghhEMpYR = false;
      bool xdfhxHMwof = false;
      bool yXMYFkpZXh = false;
      bool WKLoNfcuee = false;
      bool UBFFmXGjrG = false;
      bool doUlqucIcx = false;
      string tyiSVbOjXf;
      string gEujBogApL;
      string YtwyiPhRYO;
      string UpMyrlXqRi;
      string IskMFWRLBY;
      string gsCiXABjiF;
      string twKJKpqxqP;
      string RpiGDeJjsM;
      string xVQAgandZr;
      string jmHLoLhbBO;
      string eUTkHqKwfs;
      string pRqVIXfKbj;
      string CNWzediXQq;
      string wgidhbBerp;
      string QqxgBSwkCR;
      string fXARMRyUGc;
      string ImfnwJhMnf;
      string VARlSKPpxL;
      string hxUzLYgRRQ;
      string dgYPhcLJjr;
      if(tyiSVbOjXf == eUTkHqKwfs){kiwWufFOyB = true;}
      else if(eUTkHqKwfs == tyiSVbOjXf){SpKYNoBiKG = true;}
      if(gEujBogApL == pRqVIXfKbj){BIXtuKSgcW = true;}
      else if(pRqVIXfKbj == gEujBogApL){XHPmYITddf = true;}
      if(YtwyiPhRYO == CNWzediXQq){bQuXCoaCDo = true;}
      else if(CNWzediXQq == YtwyiPhRYO){VKdNjgqdWk = true;}
      if(UpMyrlXqRi == wgidhbBerp){zGFEazAxDe = true;}
      else if(wgidhbBerp == UpMyrlXqRi){BlRoOpkJSo = true;}
      if(IskMFWRLBY == QqxgBSwkCR){TSSPOUIeUX = true;}
      else if(QqxgBSwkCR == IskMFWRLBY){SoghhEMpYR = true;}
      if(gsCiXABjiF == fXARMRyUGc){KegNPUmYTF = true;}
      else if(fXARMRyUGc == gsCiXABjiF){xdfhxHMwof = true;}
      if(twKJKpqxqP == ImfnwJhMnf){FCKIBuCSTu = true;}
      else if(ImfnwJhMnf == twKJKpqxqP){yXMYFkpZXh = true;}
      if(RpiGDeJjsM == VARlSKPpxL){JUcxCJxfIg = true;}
      if(xVQAgandZr == hxUzLYgRRQ){gwhfeUYroF = true;}
      if(jmHLoLhbBO == dgYPhcLJjr){LbcyZRIKNT = true;}
      while(VARlSKPpxL == RpiGDeJjsM){WKLoNfcuee = true;}
      while(hxUzLYgRRQ == hxUzLYgRRQ){UBFFmXGjrG = true;}
      while(dgYPhcLJjr == dgYPhcLJjr){doUlqucIcx = true;}
      if(kiwWufFOyB == true){kiwWufFOyB = false;}
      if(BIXtuKSgcW == true){BIXtuKSgcW = false;}
      if(bQuXCoaCDo == true){bQuXCoaCDo = false;}
      if(zGFEazAxDe == true){zGFEazAxDe = false;}
      if(TSSPOUIeUX == true){TSSPOUIeUX = false;}
      if(KegNPUmYTF == true){KegNPUmYTF = false;}
      if(FCKIBuCSTu == true){FCKIBuCSTu = false;}
      if(JUcxCJxfIg == true){JUcxCJxfIg = false;}
      if(gwhfeUYroF == true){gwhfeUYroF = false;}
      if(LbcyZRIKNT == true){LbcyZRIKNT = false;}
      if(SpKYNoBiKG == true){SpKYNoBiKG = false;}
      if(XHPmYITddf == true){XHPmYITddf = false;}
      if(VKdNjgqdWk == true){VKdNjgqdWk = false;}
      if(BlRoOpkJSo == true){BlRoOpkJSo = false;}
      if(SoghhEMpYR == true){SoghhEMpYR = false;}
      if(xdfhxHMwof == true){xdfhxHMwof = false;}
      if(yXMYFkpZXh == true){yXMYFkpZXh = false;}
      if(WKLoNfcuee == true){WKLoNfcuee = false;}
      if(UBFFmXGjrG == true){UBFFmXGjrG = false;}
      if(doUlqucIcx == true){doUlqucIcx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYZLCFLWZG
{ 
  void embkkYMxId()
  { 
      bool wAAjpLVqIo = false;
      bool HgLHtrBMFx = false;
      bool PqSDayCJfn = false;
      bool EtcipggxdK = false;
      bool RFxhQbnZca = false;
      bool dgKMhEhxIq = false;
      bool JMLUjNDbQN = false;
      bool KEhteKtklz = false;
      bool KbgFJXiQBl = false;
      bool yinmBFtcxC = false;
      bool XMJOPZyQhX = false;
      bool KxKIggfGKL = false;
      bool dmadObQusZ = false;
      bool QQmibxRRoj = false;
      bool ZShcaAYfFT = false;
      bool ZnSkYjkezn = false;
      bool JCWIGtKagi = false;
      bool PNQZlLFxDO = false;
      bool DjpZAcyBKq = false;
      bool MmRBaWuZWg = false;
      string gdCHgDFwjF;
      string tAYeUhjMFy;
      string kQxcZmapRR;
      string UDJUbJRcbL;
      string XNyyEMGrlR;
      string pUkVyQgZgt;
      string cPeRjqpDDK;
      string QGjsaXRyXN;
      string fhDzaARmVK;
      string crwhiHhfNM;
      string VCnbAijqua;
      string yhBTNtLfpj;
      string YDhsgYKBJS;
      string pljLqctbzr;
      string PartLtqcUo;
      string wCodnSUttb;
      string YigbkMypbj;
      string zjfyUyKmhm;
      string hggUWnwGWY;
      string IAgWSfsQJy;
      if(gdCHgDFwjF == VCnbAijqua){wAAjpLVqIo = true;}
      else if(VCnbAijqua == gdCHgDFwjF){XMJOPZyQhX = true;}
      if(tAYeUhjMFy == yhBTNtLfpj){HgLHtrBMFx = true;}
      else if(yhBTNtLfpj == tAYeUhjMFy){KxKIggfGKL = true;}
      if(kQxcZmapRR == YDhsgYKBJS){PqSDayCJfn = true;}
      else if(YDhsgYKBJS == kQxcZmapRR){dmadObQusZ = true;}
      if(UDJUbJRcbL == pljLqctbzr){EtcipggxdK = true;}
      else if(pljLqctbzr == UDJUbJRcbL){QQmibxRRoj = true;}
      if(XNyyEMGrlR == PartLtqcUo){RFxhQbnZca = true;}
      else if(PartLtqcUo == XNyyEMGrlR){ZShcaAYfFT = true;}
      if(pUkVyQgZgt == wCodnSUttb){dgKMhEhxIq = true;}
      else if(wCodnSUttb == pUkVyQgZgt){ZnSkYjkezn = true;}
      if(cPeRjqpDDK == YigbkMypbj){JMLUjNDbQN = true;}
      else if(YigbkMypbj == cPeRjqpDDK){JCWIGtKagi = true;}
      if(QGjsaXRyXN == zjfyUyKmhm){KEhteKtklz = true;}
      if(fhDzaARmVK == hggUWnwGWY){KbgFJXiQBl = true;}
      if(crwhiHhfNM == IAgWSfsQJy){yinmBFtcxC = true;}
      while(zjfyUyKmhm == QGjsaXRyXN){PNQZlLFxDO = true;}
      while(hggUWnwGWY == hggUWnwGWY){DjpZAcyBKq = true;}
      while(IAgWSfsQJy == IAgWSfsQJy){MmRBaWuZWg = true;}
      if(wAAjpLVqIo == true){wAAjpLVqIo = false;}
      if(HgLHtrBMFx == true){HgLHtrBMFx = false;}
      if(PqSDayCJfn == true){PqSDayCJfn = false;}
      if(EtcipggxdK == true){EtcipggxdK = false;}
      if(RFxhQbnZca == true){RFxhQbnZca = false;}
      if(dgKMhEhxIq == true){dgKMhEhxIq = false;}
      if(JMLUjNDbQN == true){JMLUjNDbQN = false;}
      if(KEhteKtklz == true){KEhteKtklz = false;}
      if(KbgFJXiQBl == true){KbgFJXiQBl = false;}
      if(yinmBFtcxC == true){yinmBFtcxC = false;}
      if(XMJOPZyQhX == true){XMJOPZyQhX = false;}
      if(KxKIggfGKL == true){KxKIggfGKL = false;}
      if(dmadObQusZ == true){dmadObQusZ = false;}
      if(QQmibxRRoj == true){QQmibxRRoj = false;}
      if(ZShcaAYfFT == true){ZShcaAYfFT = false;}
      if(ZnSkYjkezn == true){ZnSkYjkezn = false;}
      if(JCWIGtKagi == true){JCWIGtKagi = false;}
      if(PNQZlLFxDO == true){PNQZlLFxDO = false;}
      if(DjpZAcyBKq == true){DjpZAcyBKq = false;}
      if(MmRBaWuZWg == true){MmRBaWuZWg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQVAQZULDG
{ 
  void OgcEXnYtNb()
  { 
      bool fPoZsiWIHP = false;
      bool ICXYWuLjXV = false;
      bool zHKgVeKpIh = false;
      bool fMVwzoBXaj = false;
      bool OIgnWQmWgW = false;
      bool sgLHoYEHEN = false;
      bool XfzYjwfaYh = false;
      bool smInHpZWKE = false;
      bool rmJkoyAOGa = false;
      bool jsTNLhIIDa = false;
      bool jLyycFXXAy = false;
      bool zhxzVjWOjk = false;
      bool uRTyyASubY = false;
      bool hRSiUfoKIi = false;
      bool ZcOIaBuUqa = false;
      bool LtXSeSrzAb = false;
      bool lcuaQhONdp = false;
      bool uLFAKSDLWw = false;
      bool EyDBNnsAEC = false;
      bool mpJfwxgmrs = false;
      string JNRHAJJHXg;
      string mamFbjPhVS;
      string DiHkrfeorL;
      string ulcEtMqStX;
      string PHYejbWKbC;
      string bKGCHZGgPU;
      string eTPMkAyiKO;
      string swmxDuKbAP;
      string JTNoikfZxT;
      string GKDZsurLsi;
      string dnzMJeWIzL;
      string OdfAKKGZdA;
      string UXkpIhsNDH;
      string DyhRlVTAeD;
      string NWakFbdDOi;
      string oRhsNFCJEa;
      string lJEqHPwONo;
      string pGtZlywzkf;
      string EpyUSlQnDf;
      string SKuDRERjdo;
      if(JNRHAJJHXg == dnzMJeWIzL){fPoZsiWIHP = true;}
      else if(dnzMJeWIzL == JNRHAJJHXg){jLyycFXXAy = true;}
      if(mamFbjPhVS == OdfAKKGZdA){ICXYWuLjXV = true;}
      else if(OdfAKKGZdA == mamFbjPhVS){zhxzVjWOjk = true;}
      if(DiHkrfeorL == UXkpIhsNDH){zHKgVeKpIh = true;}
      else if(UXkpIhsNDH == DiHkrfeorL){uRTyyASubY = true;}
      if(ulcEtMqStX == DyhRlVTAeD){fMVwzoBXaj = true;}
      else if(DyhRlVTAeD == ulcEtMqStX){hRSiUfoKIi = true;}
      if(PHYejbWKbC == NWakFbdDOi){OIgnWQmWgW = true;}
      else if(NWakFbdDOi == PHYejbWKbC){ZcOIaBuUqa = true;}
      if(bKGCHZGgPU == oRhsNFCJEa){sgLHoYEHEN = true;}
      else if(oRhsNFCJEa == bKGCHZGgPU){LtXSeSrzAb = true;}
      if(eTPMkAyiKO == lJEqHPwONo){XfzYjwfaYh = true;}
      else if(lJEqHPwONo == eTPMkAyiKO){lcuaQhONdp = true;}
      if(swmxDuKbAP == pGtZlywzkf){smInHpZWKE = true;}
      if(JTNoikfZxT == EpyUSlQnDf){rmJkoyAOGa = true;}
      if(GKDZsurLsi == SKuDRERjdo){jsTNLhIIDa = true;}
      while(pGtZlywzkf == swmxDuKbAP){uLFAKSDLWw = true;}
      while(EpyUSlQnDf == EpyUSlQnDf){EyDBNnsAEC = true;}
      while(SKuDRERjdo == SKuDRERjdo){mpJfwxgmrs = true;}
      if(fPoZsiWIHP == true){fPoZsiWIHP = false;}
      if(ICXYWuLjXV == true){ICXYWuLjXV = false;}
      if(zHKgVeKpIh == true){zHKgVeKpIh = false;}
      if(fMVwzoBXaj == true){fMVwzoBXaj = false;}
      if(OIgnWQmWgW == true){OIgnWQmWgW = false;}
      if(sgLHoYEHEN == true){sgLHoYEHEN = false;}
      if(XfzYjwfaYh == true){XfzYjwfaYh = false;}
      if(smInHpZWKE == true){smInHpZWKE = false;}
      if(rmJkoyAOGa == true){rmJkoyAOGa = false;}
      if(jsTNLhIIDa == true){jsTNLhIIDa = false;}
      if(jLyycFXXAy == true){jLyycFXXAy = false;}
      if(zhxzVjWOjk == true){zhxzVjWOjk = false;}
      if(uRTyyASubY == true){uRTyyASubY = false;}
      if(hRSiUfoKIi == true){hRSiUfoKIi = false;}
      if(ZcOIaBuUqa == true){ZcOIaBuUqa = false;}
      if(LtXSeSrzAb == true){LtXSeSrzAb = false;}
      if(lcuaQhONdp == true){lcuaQhONdp = false;}
      if(uLFAKSDLWw == true){uLFAKSDLWw = false;}
      if(EyDBNnsAEC == true){EyDBNnsAEC = false;}
      if(mpJfwxgmrs == true){mpJfwxgmrs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGUVBTCXMM
{ 
  void zUexzuqfFd()
  { 
      bool BVZBWUVbTr = false;
      bool pORUtQNoGz = false;
      bool SpVeXtbDEp = false;
      bool hoZacDWMJx = false;
      bool rsOLPynjBh = false;
      bool BIrPmKAudc = false;
      bool rRWdKAopqp = false;
      bool tAeIHYbJOY = false;
      bool FrCWnYxJnS = false;
      bool DbigEZWjAP = false;
      bool IyrKnAdiIN = false;
      bool ipfEXAPAok = false;
      bool CeBYmRRyDg = false;
      bool CqJyQGzqin = false;
      bool uNBajMudIE = false;
      bool KVuPMdwTXV = false;
      bool ifeaKqghnQ = false;
      bool BXRBpndaoZ = false;
      bool VmozVfutkl = false;
      bool KeTMEOiZPr = false;
      string jCUttNPgqs;
      string uDioKTPRBx;
      string XtBRxEYSNq;
      string gCXpaDAcdS;
      string lEwdQVPpKI;
      string IPIFPoBCwp;
      string owTzLsesOG;
      string SmnhLTyXAa;
      string nhIEhRsSZk;
      string CxfndpjwRX;
      string qWbDoVbZtw;
      string pdCUBGmOQt;
      string zMScDUHAEU;
      string iBFcjQFFPM;
      string pTXcuYuKlX;
      string CUfXYdEzzT;
      string NaVYNoXZkj;
      string AhzDEfnoge;
      string ZxNgSNVhDF;
      string MGFuzOxyPG;
      if(jCUttNPgqs == qWbDoVbZtw){BVZBWUVbTr = true;}
      else if(qWbDoVbZtw == jCUttNPgqs){IyrKnAdiIN = true;}
      if(uDioKTPRBx == pdCUBGmOQt){pORUtQNoGz = true;}
      else if(pdCUBGmOQt == uDioKTPRBx){ipfEXAPAok = true;}
      if(XtBRxEYSNq == zMScDUHAEU){SpVeXtbDEp = true;}
      else if(zMScDUHAEU == XtBRxEYSNq){CeBYmRRyDg = true;}
      if(gCXpaDAcdS == iBFcjQFFPM){hoZacDWMJx = true;}
      else if(iBFcjQFFPM == gCXpaDAcdS){CqJyQGzqin = true;}
      if(lEwdQVPpKI == pTXcuYuKlX){rsOLPynjBh = true;}
      else if(pTXcuYuKlX == lEwdQVPpKI){uNBajMudIE = true;}
      if(IPIFPoBCwp == CUfXYdEzzT){BIrPmKAudc = true;}
      else if(CUfXYdEzzT == IPIFPoBCwp){KVuPMdwTXV = true;}
      if(owTzLsesOG == NaVYNoXZkj){rRWdKAopqp = true;}
      else if(NaVYNoXZkj == owTzLsesOG){ifeaKqghnQ = true;}
      if(SmnhLTyXAa == AhzDEfnoge){tAeIHYbJOY = true;}
      if(nhIEhRsSZk == ZxNgSNVhDF){FrCWnYxJnS = true;}
      if(CxfndpjwRX == MGFuzOxyPG){DbigEZWjAP = true;}
      while(AhzDEfnoge == SmnhLTyXAa){BXRBpndaoZ = true;}
      while(ZxNgSNVhDF == ZxNgSNVhDF){VmozVfutkl = true;}
      while(MGFuzOxyPG == MGFuzOxyPG){KeTMEOiZPr = true;}
      if(BVZBWUVbTr == true){BVZBWUVbTr = false;}
      if(pORUtQNoGz == true){pORUtQNoGz = false;}
      if(SpVeXtbDEp == true){SpVeXtbDEp = false;}
      if(hoZacDWMJx == true){hoZacDWMJx = false;}
      if(rsOLPynjBh == true){rsOLPynjBh = false;}
      if(BIrPmKAudc == true){BIrPmKAudc = false;}
      if(rRWdKAopqp == true){rRWdKAopqp = false;}
      if(tAeIHYbJOY == true){tAeIHYbJOY = false;}
      if(FrCWnYxJnS == true){FrCWnYxJnS = false;}
      if(DbigEZWjAP == true){DbigEZWjAP = false;}
      if(IyrKnAdiIN == true){IyrKnAdiIN = false;}
      if(ipfEXAPAok == true){ipfEXAPAok = false;}
      if(CeBYmRRyDg == true){CeBYmRRyDg = false;}
      if(CqJyQGzqin == true){CqJyQGzqin = false;}
      if(uNBajMudIE == true){uNBajMudIE = false;}
      if(KVuPMdwTXV == true){KVuPMdwTXV = false;}
      if(ifeaKqghnQ == true){ifeaKqghnQ = false;}
      if(BXRBpndaoZ == true){BXRBpndaoZ = false;}
      if(VmozVfutkl == true){VmozVfutkl = false;}
      if(KeTMEOiZPr == true){KeTMEOiZPr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGOWNJAHNA
{ 
  void SdRJSypqlL()
  { 
      bool pPxPqgOixm = false;
      bool pIeWcMrbLa = false;
      bool trUqHhLSeU = false;
      bool uimkfklpSl = false;
      bool QuiKiuWfBz = false;
      bool znJjEytGHJ = false;
      bool UwDbqHVspr = false;
      bool ZBJZJyIJHM = false;
      bool KeQfUGYDfh = false;
      bool pfhJQUqGTb = false;
      bool YdpJYyeiZG = false;
      bool okyuyoeXGj = false;
      bool hRMICsSzJo = false;
      bool GCpemgoHGW = false;
      bool bpcZrFglKa = false;
      bool pTzjtHQhGe = false;
      bool eeZkzmtTIR = false;
      bool AXRjHrnmPx = false;
      bool MgohymCGkf = false;
      bool PHAaqwQraF = false;
      string pDxTdZPCEr;
      string AHCrLMBVeX;
      string KWkTOdhYWx;
      string WJKXZucDuS;
      string AzkhGwzquy;
      string rEiQJSRcEz;
      string qqfHVpxdRP;
      string jxaLXLlDMS;
      string eqdXESasOH;
      string dzzuaJTdMP;
      string yUZfOucWsy;
      string gOQkUAMHCC;
      string PEOKljyfjO;
      string qHpxTJQxJJ;
      string oDAQZOiNZa;
      string wLbKztGPtd;
      string xxldGZXSQK;
      string iPxrMMExkW;
      string AjFJSeefxZ;
      string DBDeMrQVKz;
      if(pDxTdZPCEr == yUZfOucWsy){pPxPqgOixm = true;}
      else if(yUZfOucWsy == pDxTdZPCEr){YdpJYyeiZG = true;}
      if(AHCrLMBVeX == gOQkUAMHCC){pIeWcMrbLa = true;}
      else if(gOQkUAMHCC == AHCrLMBVeX){okyuyoeXGj = true;}
      if(KWkTOdhYWx == PEOKljyfjO){trUqHhLSeU = true;}
      else if(PEOKljyfjO == KWkTOdhYWx){hRMICsSzJo = true;}
      if(WJKXZucDuS == qHpxTJQxJJ){uimkfklpSl = true;}
      else if(qHpxTJQxJJ == WJKXZucDuS){GCpemgoHGW = true;}
      if(AzkhGwzquy == oDAQZOiNZa){QuiKiuWfBz = true;}
      else if(oDAQZOiNZa == AzkhGwzquy){bpcZrFglKa = true;}
      if(rEiQJSRcEz == wLbKztGPtd){znJjEytGHJ = true;}
      else if(wLbKztGPtd == rEiQJSRcEz){pTzjtHQhGe = true;}
      if(qqfHVpxdRP == xxldGZXSQK){UwDbqHVspr = true;}
      else if(xxldGZXSQK == qqfHVpxdRP){eeZkzmtTIR = true;}
      if(jxaLXLlDMS == iPxrMMExkW){ZBJZJyIJHM = true;}
      if(eqdXESasOH == AjFJSeefxZ){KeQfUGYDfh = true;}
      if(dzzuaJTdMP == DBDeMrQVKz){pfhJQUqGTb = true;}
      while(iPxrMMExkW == jxaLXLlDMS){AXRjHrnmPx = true;}
      while(AjFJSeefxZ == AjFJSeefxZ){MgohymCGkf = true;}
      while(DBDeMrQVKz == DBDeMrQVKz){PHAaqwQraF = true;}
      if(pPxPqgOixm == true){pPxPqgOixm = false;}
      if(pIeWcMrbLa == true){pIeWcMrbLa = false;}
      if(trUqHhLSeU == true){trUqHhLSeU = false;}
      if(uimkfklpSl == true){uimkfklpSl = false;}
      if(QuiKiuWfBz == true){QuiKiuWfBz = false;}
      if(znJjEytGHJ == true){znJjEytGHJ = false;}
      if(UwDbqHVspr == true){UwDbqHVspr = false;}
      if(ZBJZJyIJHM == true){ZBJZJyIJHM = false;}
      if(KeQfUGYDfh == true){KeQfUGYDfh = false;}
      if(pfhJQUqGTb == true){pfhJQUqGTb = false;}
      if(YdpJYyeiZG == true){YdpJYyeiZG = false;}
      if(okyuyoeXGj == true){okyuyoeXGj = false;}
      if(hRMICsSzJo == true){hRMICsSzJo = false;}
      if(GCpemgoHGW == true){GCpemgoHGW = false;}
      if(bpcZrFglKa == true){bpcZrFglKa = false;}
      if(pTzjtHQhGe == true){pTzjtHQhGe = false;}
      if(eeZkzmtTIR == true){eeZkzmtTIR = false;}
      if(AXRjHrnmPx == true){AXRjHrnmPx = false;}
      if(MgohymCGkf == true){MgohymCGkf = false;}
      if(PHAaqwQraF == true){PHAaqwQraF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TINGYLUQHP
{ 
  void MuULiCHcBw()
  { 
      bool XCiwcYVNoK = false;
      bool ZXwlxqitip = false;
      bool YhmwAHVwLT = false;
      bool TZWiOuitfR = false;
      bool hOUqzhwzuD = false;
      bool GfPWgpPlwV = false;
      bool DZBUqzBMXC = false;
      bool IoOQHKMuxR = false;
      bool KWBINmJzCX = false;
      bool fxyKOIMzAz = false;
      bool gjartQRyOW = false;
      bool cTndLfXsHD = false;
      bool oBJAWKqECz = false;
      bool xMuxkZuINw = false;
      bool VLjftLITyh = false;
      bool kTqwKeZaVj = false;
      bool ZNwPYQXqrk = false;
      bool kOeLgdRdFK = false;
      bool BWFTOcUylG = false;
      bool ATlcWIOTGd = false;
      string frsVwmsiuj;
      string EcneOyzUtm;
      string pGMLzQujjw;
      string YICfduVYCz;
      string KlehZZFiwM;
      string ImlbNYehWe;
      string qIzzKuZIBT;
      string caSubDbekZ;
      string KMnWmkVZRE;
      string QnCXICmfWd;
      string zxhcjhUqAK;
      string xzwwTeTbLY;
      string ZzpwDoXtmZ;
      string PwHGZNeLmF;
      string PeZHHQqFDc;
      string hLTxEzHkYt;
      string KaEatBroWG;
      string AIoGItZiom;
      string xSqJqEbJBZ;
      string GslruoazMF;
      if(frsVwmsiuj == zxhcjhUqAK){XCiwcYVNoK = true;}
      else if(zxhcjhUqAK == frsVwmsiuj){gjartQRyOW = true;}
      if(EcneOyzUtm == xzwwTeTbLY){ZXwlxqitip = true;}
      else if(xzwwTeTbLY == EcneOyzUtm){cTndLfXsHD = true;}
      if(pGMLzQujjw == ZzpwDoXtmZ){YhmwAHVwLT = true;}
      else if(ZzpwDoXtmZ == pGMLzQujjw){oBJAWKqECz = true;}
      if(YICfduVYCz == PwHGZNeLmF){TZWiOuitfR = true;}
      else if(PwHGZNeLmF == YICfduVYCz){xMuxkZuINw = true;}
      if(KlehZZFiwM == PeZHHQqFDc){hOUqzhwzuD = true;}
      else if(PeZHHQqFDc == KlehZZFiwM){VLjftLITyh = true;}
      if(ImlbNYehWe == hLTxEzHkYt){GfPWgpPlwV = true;}
      else if(hLTxEzHkYt == ImlbNYehWe){kTqwKeZaVj = true;}
      if(qIzzKuZIBT == KaEatBroWG){DZBUqzBMXC = true;}
      else if(KaEatBroWG == qIzzKuZIBT){ZNwPYQXqrk = true;}
      if(caSubDbekZ == AIoGItZiom){IoOQHKMuxR = true;}
      if(KMnWmkVZRE == xSqJqEbJBZ){KWBINmJzCX = true;}
      if(QnCXICmfWd == GslruoazMF){fxyKOIMzAz = true;}
      while(AIoGItZiom == caSubDbekZ){kOeLgdRdFK = true;}
      while(xSqJqEbJBZ == xSqJqEbJBZ){BWFTOcUylG = true;}
      while(GslruoazMF == GslruoazMF){ATlcWIOTGd = true;}
      if(XCiwcYVNoK == true){XCiwcYVNoK = false;}
      if(ZXwlxqitip == true){ZXwlxqitip = false;}
      if(YhmwAHVwLT == true){YhmwAHVwLT = false;}
      if(TZWiOuitfR == true){TZWiOuitfR = false;}
      if(hOUqzhwzuD == true){hOUqzhwzuD = false;}
      if(GfPWgpPlwV == true){GfPWgpPlwV = false;}
      if(DZBUqzBMXC == true){DZBUqzBMXC = false;}
      if(IoOQHKMuxR == true){IoOQHKMuxR = false;}
      if(KWBINmJzCX == true){KWBINmJzCX = false;}
      if(fxyKOIMzAz == true){fxyKOIMzAz = false;}
      if(gjartQRyOW == true){gjartQRyOW = false;}
      if(cTndLfXsHD == true){cTndLfXsHD = false;}
      if(oBJAWKqECz == true){oBJAWKqECz = false;}
      if(xMuxkZuINw == true){xMuxkZuINw = false;}
      if(VLjftLITyh == true){VLjftLITyh = false;}
      if(kTqwKeZaVj == true){kTqwKeZaVj = false;}
      if(ZNwPYQXqrk == true){ZNwPYQXqrk = false;}
      if(kOeLgdRdFK == true){kOeLgdRdFK = false;}
      if(BWFTOcUylG == true){BWFTOcUylG = false;}
      if(ATlcWIOTGd == true){ATlcWIOTGd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVDOLIBEHW
{ 
  void fLrlfpftoc()
  { 
      bool SaOtzmVntO = false;
      bool NDGfYxeZwZ = false;
      bool kKgYXGPyhk = false;
      bool MHQodutzsk = false;
      bool ZDOVpieyEh = false;
      bool eqoKrItoWs = false;
      bool WWGICGlRCd = false;
      bool DfgKzhuLio = false;
      bool aQtzGURGxV = false;
      bool AEcAOCwGTj = false;
      bool wNwaezKeKK = false;
      bool MiGgRFcGCg = false;
      bool nfTfcyCfwx = false;
      bool knqyrNTTUG = false;
      bool KmulIRyuhI = false;
      bool ZoEluQsQxf = false;
      bool xdhNYXqHoE = false;
      bool lJluWBjhXL = false;
      bool AGynXwjFDa = false;
      bool UDVnIfEhNj = false;
      string GaeOjQxeRd;
      string dpytkVLMiF;
      string XojzJiGXua;
      string nYFYtwSiHE;
      string LgsNNrixCM;
      string idiVFRpfEB;
      string KZiqpFjYAo;
      string CcFesquWkR;
      string AIViqJpjTb;
      string FmdFtlxBWI;
      string HJxMKFYEbO;
      string VStmACDAzg;
      string PAFXiOzzkG;
      string sszcKpKIXl;
      string jkHEFlrqFq;
      string hxCprGDYcu;
      string GZTUUbTQcK;
      string qubNwdsASx;
      string WItsYuqJjD;
      string lkecfKRljc;
      if(GaeOjQxeRd == HJxMKFYEbO){SaOtzmVntO = true;}
      else if(HJxMKFYEbO == GaeOjQxeRd){wNwaezKeKK = true;}
      if(dpytkVLMiF == VStmACDAzg){NDGfYxeZwZ = true;}
      else if(VStmACDAzg == dpytkVLMiF){MiGgRFcGCg = true;}
      if(XojzJiGXua == PAFXiOzzkG){kKgYXGPyhk = true;}
      else if(PAFXiOzzkG == XojzJiGXua){nfTfcyCfwx = true;}
      if(nYFYtwSiHE == sszcKpKIXl){MHQodutzsk = true;}
      else if(sszcKpKIXl == nYFYtwSiHE){knqyrNTTUG = true;}
      if(LgsNNrixCM == jkHEFlrqFq){ZDOVpieyEh = true;}
      else if(jkHEFlrqFq == LgsNNrixCM){KmulIRyuhI = true;}
      if(idiVFRpfEB == hxCprGDYcu){eqoKrItoWs = true;}
      else if(hxCprGDYcu == idiVFRpfEB){ZoEluQsQxf = true;}
      if(KZiqpFjYAo == GZTUUbTQcK){WWGICGlRCd = true;}
      else if(GZTUUbTQcK == KZiqpFjYAo){xdhNYXqHoE = true;}
      if(CcFesquWkR == qubNwdsASx){DfgKzhuLio = true;}
      if(AIViqJpjTb == WItsYuqJjD){aQtzGURGxV = true;}
      if(FmdFtlxBWI == lkecfKRljc){AEcAOCwGTj = true;}
      while(qubNwdsASx == CcFesquWkR){lJluWBjhXL = true;}
      while(WItsYuqJjD == WItsYuqJjD){AGynXwjFDa = true;}
      while(lkecfKRljc == lkecfKRljc){UDVnIfEhNj = true;}
      if(SaOtzmVntO == true){SaOtzmVntO = false;}
      if(NDGfYxeZwZ == true){NDGfYxeZwZ = false;}
      if(kKgYXGPyhk == true){kKgYXGPyhk = false;}
      if(MHQodutzsk == true){MHQodutzsk = false;}
      if(ZDOVpieyEh == true){ZDOVpieyEh = false;}
      if(eqoKrItoWs == true){eqoKrItoWs = false;}
      if(WWGICGlRCd == true){WWGICGlRCd = false;}
      if(DfgKzhuLio == true){DfgKzhuLio = false;}
      if(aQtzGURGxV == true){aQtzGURGxV = false;}
      if(AEcAOCwGTj == true){AEcAOCwGTj = false;}
      if(wNwaezKeKK == true){wNwaezKeKK = false;}
      if(MiGgRFcGCg == true){MiGgRFcGCg = false;}
      if(nfTfcyCfwx == true){nfTfcyCfwx = false;}
      if(knqyrNTTUG == true){knqyrNTTUG = false;}
      if(KmulIRyuhI == true){KmulIRyuhI = false;}
      if(ZoEluQsQxf == true){ZoEluQsQxf = false;}
      if(xdhNYXqHoE == true){xdhNYXqHoE = false;}
      if(lJluWBjhXL == true){lJluWBjhXL = false;}
      if(AGynXwjFDa == true){AGynXwjFDa = false;}
      if(UDVnIfEhNj == true){UDVnIfEhNj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMUUWHYVPW
{ 
  void QCsdmSetUU()
  { 
      bool suhbLenzpc = false;
      bool sDxDKwhtSJ = false;
      bool TQrndkkXVa = false;
      bool QpQPnjPdCW = false;
      bool iSCAtqgRRU = false;
      bool AscxgcCsyZ = false;
      bool sPdOLDlhPZ = false;
      bool gEqwZBNqtl = false;
      bool DTGBaWNThL = false;
      bool hVfccTonnq = false;
      bool FzCqmwCfWf = false;
      bool OLzLVZJbno = false;
      bool oRzDrLYOTG = false;
      bool LZDCgEQONe = false;
      bool UgwCxWVTGC = false;
      bool KMAzBmzzzb = false;
      bool XmLQTnHwdQ = false;
      bool ItOIUIVxFV = false;
      bool oEIRwzYEBt = false;
      bool FROkHgUehI = false;
      string NkHRfbsNpQ;
      string OJcnaXUuYs;
      string uiIdSgJwoe;
      string PQenGibGtB;
      string AduhhOazPi;
      string RxVCIdcczz;
      string SwXLAxeogr;
      string wOBXrQnZwD;
      string GKfFNSubec;
      string GyGtiDFjgj;
      string ikRXmCuxKq;
      string pCgwsHPRxg;
      string CDKDlxIGoo;
      string KDrLTUrIRK;
      string WxQmmDQKAa;
      string mnlAhfaNlp;
      string tnIUflJVbY;
      string PHzlJFlXQh;
      string fxGOBWRrcn;
      string tdVbQinwGB;
      if(NkHRfbsNpQ == ikRXmCuxKq){suhbLenzpc = true;}
      else if(ikRXmCuxKq == NkHRfbsNpQ){FzCqmwCfWf = true;}
      if(OJcnaXUuYs == pCgwsHPRxg){sDxDKwhtSJ = true;}
      else if(pCgwsHPRxg == OJcnaXUuYs){OLzLVZJbno = true;}
      if(uiIdSgJwoe == CDKDlxIGoo){TQrndkkXVa = true;}
      else if(CDKDlxIGoo == uiIdSgJwoe){oRzDrLYOTG = true;}
      if(PQenGibGtB == KDrLTUrIRK){QpQPnjPdCW = true;}
      else if(KDrLTUrIRK == PQenGibGtB){LZDCgEQONe = true;}
      if(AduhhOazPi == WxQmmDQKAa){iSCAtqgRRU = true;}
      else if(WxQmmDQKAa == AduhhOazPi){UgwCxWVTGC = true;}
      if(RxVCIdcczz == mnlAhfaNlp){AscxgcCsyZ = true;}
      else if(mnlAhfaNlp == RxVCIdcczz){KMAzBmzzzb = true;}
      if(SwXLAxeogr == tnIUflJVbY){sPdOLDlhPZ = true;}
      else if(tnIUflJVbY == SwXLAxeogr){XmLQTnHwdQ = true;}
      if(wOBXrQnZwD == PHzlJFlXQh){gEqwZBNqtl = true;}
      if(GKfFNSubec == fxGOBWRrcn){DTGBaWNThL = true;}
      if(GyGtiDFjgj == tdVbQinwGB){hVfccTonnq = true;}
      while(PHzlJFlXQh == wOBXrQnZwD){ItOIUIVxFV = true;}
      while(fxGOBWRrcn == fxGOBWRrcn){oEIRwzYEBt = true;}
      while(tdVbQinwGB == tdVbQinwGB){FROkHgUehI = true;}
      if(suhbLenzpc == true){suhbLenzpc = false;}
      if(sDxDKwhtSJ == true){sDxDKwhtSJ = false;}
      if(TQrndkkXVa == true){TQrndkkXVa = false;}
      if(QpQPnjPdCW == true){QpQPnjPdCW = false;}
      if(iSCAtqgRRU == true){iSCAtqgRRU = false;}
      if(AscxgcCsyZ == true){AscxgcCsyZ = false;}
      if(sPdOLDlhPZ == true){sPdOLDlhPZ = false;}
      if(gEqwZBNqtl == true){gEqwZBNqtl = false;}
      if(DTGBaWNThL == true){DTGBaWNThL = false;}
      if(hVfccTonnq == true){hVfccTonnq = false;}
      if(FzCqmwCfWf == true){FzCqmwCfWf = false;}
      if(OLzLVZJbno == true){OLzLVZJbno = false;}
      if(oRzDrLYOTG == true){oRzDrLYOTG = false;}
      if(LZDCgEQONe == true){LZDCgEQONe = false;}
      if(UgwCxWVTGC == true){UgwCxWVTGC = false;}
      if(KMAzBmzzzb == true){KMAzBmzzzb = false;}
      if(XmLQTnHwdQ == true){XmLQTnHwdQ = false;}
      if(ItOIUIVxFV == true){ItOIUIVxFV = false;}
      if(oEIRwzYEBt == true){oEIRwzYEBt = false;}
      if(FROkHgUehI == true){FROkHgUehI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLOUQDDLSF
{ 
  void ZdaamOjPAL()
  { 
      bool CZCyxydAsO = false;
      bool nFnexnNZHc = false;
      bool MgjbslOkqj = false;
      bool tBhRGddSjQ = false;
      bool zXwlZHlYKf = false;
      bool ZqljiVpZEK = false;
      bool isJJUmXWXT = false;
      bool KtpqcnjxCk = false;
      bool AoaLKCPxik = false;
      bool nDOZhGOmRm = false;
      bool jPBpVeBuGt = false;
      bool krXSKtRyyR = false;
      bool XZmmeGfPJW = false;
      bool ZwfOBjnjof = false;
      bool BTpnzueuPm = false;
      bool nQoAPJcNKO = false;
      bool zkljUnMIRZ = false;
      bool GhISPDiymj = false;
      bool bjAViJHfzq = false;
      bool HZYafPhGTL = false;
      string EUzTmpOAPb;
      string XRIXpBgZMT;
      string elbDemYiYi;
      string TQiPWzRXaS;
      string JCpORgJxPz;
      string CArNlSswnz;
      string RfbfIHisAp;
      string jIysJcuNky;
      string daSYgTXUdE;
      string GVibBdaKFK;
      string yPxYPsBzDJ;
      string WeLpVqMCyo;
      string jNPujNYWrf;
      string BkHazNcsJn;
      string RYRUhaKsFK;
      string QXLQZkACoB;
      string TeHWHlXjqH;
      string NSsKWLwuNJ;
      string DfQgOdYpAO;
      string NaEHTmRtNu;
      if(EUzTmpOAPb == yPxYPsBzDJ){CZCyxydAsO = true;}
      else if(yPxYPsBzDJ == EUzTmpOAPb){jPBpVeBuGt = true;}
      if(XRIXpBgZMT == WeLpVqMCyo){nFnexnNZHc = true;}
      else if(WeLpVqMCyo == XRIXpBgZMT){krXSKtRyyR = true;}
      if(elbDemYiYi == jNPujNYWrf){MgjbslOkqj = true;}
      else if(jNPujNYWrf == elbDemYiYi){XZmmeGfPJW = true;}
      if(TQiPWzRXaS == BkHazNcsJn){tBhRGddSjQ = true;}
      else if(BkHazNcsJn == TQiPWzRXaS){ZwfOBjnjof = true;}
      if(JCpORgJxPz == RYRUhaKsFK){zXwlZHlYKf = true;}
      else if(RYRUhaKsFK == JCpORgJxPz){BTpnzueuPm = true;}
      if(CArNlSswnz == QXLQZkACoB){ZqljiVpZEK = true;}
      else if(QXLQZkACoB == CArNlSswnz){nQoAPJcNKO = true;}
      if(RfbfIHisAp == TeHWHlXjqH){isJJUmXWXT = true;}
      else if(TeHWHlXjqH == RfbfIHisAp){zkljUnMIRZ = true;}
      if(jIysJcuNky == NSsKWLwuNJ){KtpqcnjxCk = true;}
      if(daSYgTXUdE == DfQgOdYpAO){AoaLKCPxik = true;}
      if(GVibBdaKFK == NaEHTmRtNu){nDOZhGOmRm = true;}
      while(NSsKWLwuNJ == jIysJcuNky){GhISPDiymj = true;}
      while(DfQgOdYpAO == DfQgOdYpAO){bjAViJHfzq = true;}
      while(NaEHTmRtNu == NaEHTmRtNu){HZYafPhGTL = true;}
      if(CZCyxydAsO == true){CZCyxydAsO = false;}
      if(nFnexnNZHc == true){nFnexnNZHc = false;}
      if(MgjbslOkqj == true){MgjbslOkqj = false;}
      if(tBhRGddSjQ == true){tBhRGddSjQ = false;}
      if(zXwlZHlYKf == true){zXwlZHlYKf = false;}
      if(ZqljiVpZEK == true){ZqljiVpZEK = false;}
      if(isJJUmXWXT == true){isJJUmXWXT = false;}
      if(KtpqcnjxCk == true){KtpqcnjxCk = false;}
      if(AoaLKCPxik == true){AoaLKCPxik = false;}
      if(nDOZhGOmRm == true){nDOZhGOmRm = false;}
      if(jPBpVeBuGt == true){jPBpVeBuGt = false;}
      if(krXSKtRyyR == true){krXSKtRyyR = false;}
      if(XZmmeGfPJW == true){XZmmeGfPJW = false;}
      if(ZwfOBjnjof == true){ZwfOBjnjof = false;}
      if(BTpnzueuPm == true){BTpnzueuPm = false;}
      if(nQoAPJcNKO == true){nQoAPJcNKO = false;}
      if(zkljUnMIRZ == true){zkljUnMIRZ = false;}
      if(GhISPDiymj == true){GhISPDiymj = false;}
      if(bjAViJHfzq == true){bjAViJHfzq = false;}
      if(HZYafPhGTL == true){HZYafPhGTL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYTPIPKLPL
{ 
  void maDQZpiyTl()
  { 
      bool FreBJtQgRh = false;
      bool UEwduaJxFC = false;
      bool GMzLXoMwtM = false;
      bool NBYeGogliu = false;
      bool VxlTupUxGX = false;
      bool biHqyrsSdU = false;
      bool hUmETTeQXF = false;
      bool tWNJgIafQg = false;
      bool UOpWjeshgO = false;
      bool wNINMAKgzb = false;
      bool KEYAcFUyKp = false;
      bool RNCwASeQUo = false;
      bool ZxjJJgNzwf = false;
      bool ysfoWPpose = false;
      bool KuXqxiKMNt = false;
      bool VsMJBNTPqu = false;
      bool qUBeqYgMYj = false;
      bool cpXoedZsMZ = false;
      bool VAlCKEfWmJ = false;
      bool uZyxmotszX = false;
      string xrCycbBIfd;
      string nCwsCbbwNx;
      string GsnAMzRErG;
      string GCFQkMaVif;
      string kJfUdEFNOG;
      string MRgeoEEBkd;
      string JwPZWlxeHp;
      string AFMgMwMSWH;
      string sEpltoVabg;
      string HYkEWnsGyr;
      string HaGXFHFASr;
      string qkeckFFdfh;
      string PWCZhbTHKX;
      string CFUdASyRfl;
      string iVHipWsHTR;
      string hPaPbjXfpd;
      string mxptpkQBbS;
      string HnysytOSjL;
      string hLnsomeEBQ;
      string tRbBzlfNsE;
      if(xrCycbBIfd == HaGXFHFASr){FreBJtQgRh = true;}
      else if(HaGXFHFASr == xrCycbBIfd){KEYAcFUyKp = true;}
      if(nCwsCbbwNx == qkeckFFdfh){UEwduaJxFC = true;}
      else if(qkeckFFdfh == nCwsCbbwNx){RNCwASeQUo = true;}
      if(GsnAMzRErG == PWCZhbTHKX){GMzLXoMwtM = true;}
      else if(PWCZhbTHKX == GsnAMzRErG){ZxjJJgNzwf = true;}
      if(GCFQkMaVif == CFUdASyRfl){NBYeGogliu = true;}
      else if(CFUdASyRfl == GCFQkMaVif){ysfoWPpose = true;}
      if(kJfUdEFNOG == iVHipWsHTR){VxlTupUxGX = true;}
      else if(iVHipWsHTR == kJfUdEFNOG){KuXqxiKMNt = true;}
      if(MRgeoEEBkd == hPaPbjXfpd){biHqyrsSdU = true;}
      else if(hPaPbjXfpd == MRgeoEEBkd){VsMJBNTPqu = true;}
      if(JwPZWlxeHp == mxptpkQBbS){hUmETTeQXF = true;}
      else if(mxptpkQBbS == JwPZWlxeHp){qUBeqYgMYj = true;}
      if(AFMgMwMSWH == HnysytOSjL){tWNJgIafQg = true;}
      if(sEpltoVabg == hLnsomeEBQ){UOpWjeshgO = true;}
      if(HYkEWnsGyr == tRbBzlfNsE){wNINMAKgzb = true;}
      while(HnysytOSjL == AFMgMwMSWH){cpXoedZsMZ = true;}
      while(hLnsomeEBQ == hLnsomeEBQ){VAlCKEfWmJ = true;}
      while(tRbBzlfNsE == tRbBzlfNsE){uZyxmotszX = true;}
      if(FreBJtQgRh == true){FreBJtQgRh = false;}
      if(UEwduaJxFC == true){UEwduaJxFC = false;}
      if(GMzLXoMwtM == true){GMzLXoMwtM = false;}
      if(NBYeGogliu == true){NBYeGogliu = false;}
      if(VxlTupUxGX == true){VxlTupUxGX = false;}
      if(biHqyrsSdU == true){biHqyrsSdU = false;}
      if(hUmETTeQXF == true){hUmETTeQXF = false;}
      if(tWNJgIafQg == true){tWNJgIafQg = false;}
      if(UOpWjeshgO == true){UOpWjeshgO = false;}
      if(wNINMAKgzb == true){wNINMAKgzb = false;}
      if(KEYAcFUyKp == true){KEYAcFUyKp = false;}
      if(RNCwASeQUo == true){RNCwASeQUo = false;}
      if(ZxjJJgNzwf == true){ZxjJJgNzwf = false;}
      if(ysfoWPpose == true){ysfoWPpose = false;}
      if(KuXqxiKMNt == true){KuXqxiKMNt = false;}
      if(VsMJBNTPqu == true){VsMJBNTPqu = false;}
      if(qUBeqYgMYj == true){qUBeqYgMYj = false;}
      if(cpXoedZsMZ == true){cpXoedZsMZ = false;}
      if(VAlCKEfWmJ == true){VAlCKEfWmJ = false;}
      if(uZyxmotszX == true){uZyxmotszX = false;}
    } 
}; 
