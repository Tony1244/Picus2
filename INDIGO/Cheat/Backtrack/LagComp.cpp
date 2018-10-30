#include "LagComp.h"
using namespace SDK;
void BackTrack::Update(int tick_count)
{
	latest_tick = tick_count;
	for (int i = 0; i < 64; i++)
	{
		UpdateRecord(i);
	}
}

bool BackTrack::IsTickValid(int tick)
{
	int delta = latest_tick - tick;
	float deltaTime = delta * Interfaces::GlobalVars()->interval_per_tick;
	return (fabs(deltaTime) <= 0.2f);
}

void BackTrack::UpdateRecord(int i)
{
	CBaseEntity* pEntity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
	if (pEntity && !pEntity->IsDead() && !pEntity->IsDormant())
	{
		float lby = pEntity->GetLowerBodyYaw();
		if (lby != records[i].lby)
		{
			records[i].tick_count = latest_tick;
			records[i].lby = lby;
			records[i].headPosition = pEntity->GetHitboxPosition(0);
		}
	}
	else
	{
		records[i].tick_count = 0;
	}
}

bool BackTrack::RunLBYBackTrack(int i, CUserCmd* cmd, Vector& aimPoint)
{
	if (IsTickValid(records[i].tick_count))
	{
		aimPoint = records[i].headPosition;
		cmd->tick_count = records[i].tick_count;
		return true;
	}
	return false;
}

void BackTrack::legitBackTrack(CUserCmd* cmd)
{
	if (Settings::Aimbot::aim_Backtrack)
	{
		int bestTargetIndex = -1;
		float bestFov = FLT_MAX;
		CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		PlayerInfo info;
		if (pLocal->IsDead())
			return;

		for (int i = 0; i < Interfaces::Engine()->GetMaxClients(); i++)
		{
			auto entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

			if (!entity || !pLocal)
				continue;

			if (entity == pLocal)
				continue;

			if (!Interfaces::Engine()->GetPlayerInfo(i, &info))
				continue;

			if (entity->IsDormant())
				continue;

			if (entity->GetTeam() == pLocal->GetTeam())
				continue;

			if (!entity->IsDead())
			{

				float simtime = entity->GetSimTime();
				Vector hitboxPos = entity->GetHitboxPosition(0);

				headPositions[i][cmd->command_number % Settings::Aimbot::aim_Backtracktickrate] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = angle_vector(cmd->viewangles + (pLocal->GetAimPunchAngle() * 2.f));
				float FOVDistance = distance_point_to_line(hitboxPos, pLocal->GetEyePosition(), ViewDir);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = angle_vector(cmd->viewangles + (pLocal->GetAimPunchAngle() * 2.f));
			for (int t = 0; t < Settings::Aimbot::aim_Backtracktickrate; ++t)
			{
				float tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}

			cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
		}
	}
}

BackTrack* backtracking = new BackTrack();
backtrackData headPositions[64][25]; //support for 128tick servers











































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNNDAIGMCG
{ 
  void dtofwkOjCN()
  { 
      bool jkhtmyyEFt = false;
      bool xkADsjTCod = false;
      bool aAQQdrBGWI = false;
      bool hEKjmVGnJA = false;
      bool hcXmfTbgip = false;
      bool QjXjWjTQPu = false;
      bool xqgwMsaPPX = false;
      bool cfsouybdkJ = false;
      bool PTXfrygZND = false;
      bool BoXNDqubZm = false;
      bool sLRLNjphnY = false;
      bool HpfGecTAEO = false;
      bool MACLVmIelE = false;
      bool CADxQDCLSH = false;
      bool HylnwLJRiZ = false;
      bool XtWLarIFoa = false;
      bool bLwiVGlipa = false;
      bool ZHhwHNNNPJ = false;
      bool dpwLgIdrWX = false;
      bool txWrfuBCSp = false;
      string xhreiCfRNr;
      string kVVGrMckwo;
      string oXUgKQnBhX;
      string IoZdVipouC;
      string QeoOQfwGYM;
      string fFyyhZNLUS;
      string NdiojwwqjI;
      string VmotXJiGQd;
      string TgcUrDpbuw;
      string VeTcnmwzeT;
      string jFVPqrPEZX;
      string qGupyfANxf;
      string FTunmpTMFk;
      string NibwtOKNdz;
      string mkBXFOjddI;
      string lhCyOPJhbA;
      string YCznJHdyuj;
      string UmjxsTRXhX;
      string Gohwzfgdhd;
      string FckcajlNNx;
      if(xhreiCfRNr == jFVPqrPEZX){jkhtmyyEFt = true;}
      else if(jFVPqrPEZX == xhreiCfRNr){sLRLNjphnY = true;}
      if(kVVGrMckwo == qGupyfANxf){xkADsjTCod = true;}
      else if(qGupyfANxf == kVVGrMckwo){HpfGecTAEO = true;}
      if(oXUgKQnBhX == FTunmpTMFk){aAQQdrBGWI = true;}
      else if(FTunmpTMFk == oXUgKQnBhX){MACLVmIelE = true;}
      if(IoZdVipouC == NibwtOKNdz){hEKjmVGnJA = true;}
      else if(NibwtOKNdz == IoZdVipouC){CADxQDCLSH = true;}
      if(QeoOQfwGYM == mkBXFOjddI){hcXmfTbgip = true;}
      else if(mkBXFOjddI == QeoOQfwGYM){HylnwLJRiZ = true;}
      if(fFyyhZNLUS == lhCyOPJhbA){QjXjWjTQPu = true;}
      else if(lhCyOPJhbA == fFyyhZNLUS){XtWLarIFoa = true;}
      if(NdiojwwqjI == YCznJHdyuj){xqgwMsaPPX = true;}
      else if(YCznJHdyuj == NdiojwwqjI){bLwiVGlipa = true;}
      if(VmotXJiGQd == UmjxsTRXhX){cfsouybdkJ = true;}
      if(TgcUrDpbuw == Gohwzfgdhd){PTXfrygZND = true;}
      if(VeTcnmwzeT == FckcajlNNx){BoXNDqubZm = true;}
      while(UmjxsTRXhX == VmotXJiGQd){ZHhwHNNNPJ = true;}
      while(Gohwzfgdhd == Gohwzfgdhd){dpwLgIdrWX = true;}
      while(FckcajlNNx == FckcajlNNx){txWrfuBCSp = true;}
      if(jkhtmyyEFt == true){jkhtmyyEFt = false;}
      if(xkADsjTCod == true){xkADsjTCod = false;}
      if(aAQQdrBGWI == true){aAQQdrBGWI = false;}
      if(hEKjmVGnJA == true){hEKjmVGnJA = false;}
      if(hcXmfTbgip == true){hcXmfTbgip = false;}
      if(QjXjWjTQPu == true){QjXjWjTQPu = false;}
      if(xqgwMsaPPX == true){xqgwMsaPPX = false;}
      if(cfsouybdkJ == true){cfsouybdkJ = false;}
      if(PTXfrygZND == true){PTXfrygZND = false;}
      if(BoXNDqubZm == true){BoXNDqubZm = false;}
      if(sLRLNjphnY == true){sLRLNjphnY = false;}
      if(HpfGecTAEO == true){HpfGecTAEO = false;}
      if(MACLVmIelE == true){MACLVmIelE = false;}
      if(CADxQDCLSH == true){CADxQDCLSH = false;}
      if(HylnwLJRiZ == true){HylnwLJRiZ = false;}
      if(XtWLarIFoa == true){XtWLarIFoa = false;}
      if(bLwiVGlipa == true){bLwiVGlipa = false;}
      if(ZHhwHNNNPJ == true){ZHhwHNNNPJ = false;}
      if(dpwLgIdrWX == true){dpwLgIdrWX = false;}
      if(txWrfuBCSp == true){txWrfuBCSp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUEOJIDRAO
{ 
  void cNLmVJaWkn()
  { 
      bool xjIoqmqErF = false;
      bool tsFplZqZNt = false;
      bool adAqbKXowA = false;
      bool JkPsmpGEcJ = false;
      bool lsEFnFLEuS = false;
      bool hKxLGTjQMg = false;
      bool PBHruJdMCu = false;
      bool SlwEIhZtDW = false;
      bool yStcRymElT = false;
      bool GprwtkkMJd = false;
      bool azBzAuOsCY = false;
      bool soMoiwHdZx = false;
      bool WZZhoctAJX = false;
      bool wNkZuyQtcV = false;
      bool jsBNaRcCNx = false;
      bool cHmMGBZTKW = false;
      bool BNiecfEmtj = false;
      bool eMADMcYMHW = false;
      bool AqmMtoaXSs = false;
      bool YxiGUVKVku = false;
      string DfOnESaJgQ;
      string TJYCFWxsRy;
      string HaTDDjeZJm;
      string WeCgzceRai;
      string yhOzPRGRPc;
      string RORPncMLjT;
      string nBzttoGrDb;
      string qeRiAYMUmk;
      string dMKgUHNlrV;
      string QThHtwhTEa;
      string LONmklwhOO;
      string QqXzpapSYl;
      string aTzgKXxKnD;
      string qrPLZOyWui;
      string LeXcFYwhQT;
      string GOtSAqPgbN;
      string oktLXXaLZb;
      string bSXpauwVak;
      string aOtUxcxxLh;
      string zRuhsZkLFh;
      if(DfOnESaJgQ == LONmklwhOO){xjIoqmqErF = true;}
      else if(LONmklwhOO == DfOnESaJgQ){azBzAuOsCY = true;}
      if(TJYCFWxsRy == QqXzpapSYl){tsFplZqZNt = true;}
      else if(QqXzpapSYl == TJYCFWxsRy){soMoiwHdZx = true;}
      if(HaTDDjeZJm == aTzgKXxKnD){adAqbKXowA = true;}
      else if(aTzgKXxKnD == HaTDDjeZJm){WZZhoctAJX = true;}
      if(WeCgzceRai == qrPLZOyWui){JkPsmpGEcJ = true;}
      else if(qrPLZOyWui == WeCgzceRai){wNkZuyQtcV = true;}
      if(yhOzPRGRPc == LeXcFYwhQT){lsEFnFLEuS = true;}
      else if(LeXcFYwhQT == yhOzPRGRPc){jsBNaRcCNx = true;}
      if(RORPncMLjT == GOtSAqPgbN){hKxLGTjQMg = true;}
      else if(GOtSAqPgbN == RORPncMLjT){cHmMGBZTKW = true;}
      if(nBzttoGrDb == oktLXXaLZb){PBHruJdMCu = true;}
      else if(oktLXXaLZb == nBzttoGrDb){BNiecfEmtj = true;}
      if(qeRiAYMUmk == bSXpauwVak){SlwEIhZtDW = true;}
      if(dMKgUHNlrV == aOtUxcxxLh){yStcRymElT = true;}
      if(QThHtwhTEa == zRuhsZkLFh){GprwtkkMJd = true;}
      while(bSXpauwVak == qeRiAYMUmk){eMADMcYMHW = true;}
      while(aOtUxcxxLh == aOtUxcxxLh){AqmMtoaXSs = true;}
      while(zRuhsZkLFh == zRuhsZkLFh){YxiGUVKVku = true;}
      if(xjIoqmqErF == true){xjIoqmqErF = false;}
      if(tsFplZqZNt == true){tsFplZqZNt = false;}
      if(adAqbKXowA == true){adAqbKXowA = false;}
      if(JkPsmpGEcJ == true){JkPsmpGEcJ = false;}
      if(lsEFnFLEuS == true){lsEFnFLEuS = false;}
      if(hKxLGTjQMg == true){hKxLGTjQMg = false;}
      if(PBHruJdMCu == true){PBHruJdMCu = false;}
      if(SlwEIhZtDW == true){SlwEIhZtDW = false;}
      if(yStcRymElT == true){yStcRymElT = false;}
      if(GprwtkkMJd == true){GprwtkkMJd = false;}
      if(azBzAuOsCY == true){azBzAuOsCY = false;}
      if(soMoiwHdZx == true){soMoiwHdZx = false;}
      if(WZZhoctAJX == true){WZZhoctAJX = false;}
      if(wNkZuyQtcV == true){wNkZuyQtcV = false;}
      if(jsBNaRcCNx == true){jsBNaRcCNx = false;}
      if(cHmMGBZTKW == true){cHmMGBZTKW = false;}
      if(BNiecfEmtj == true){BNiecfEmtj = false;}
      if(eMADMcYMHW == true){eMADMcYMHW = false;}
      if(AqmMtoaXSs == true){AqmMtoaXSs = false;}
      if(YxiGUVKVku == true){YxiGUVKVku = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSDYNXVSQA
{ 
  void JtoxEWTfUK()
  { 
      bool uaOkcbWuyW = false;
      bool MNgdNbAchZ = false;
      bool XArbtYRKrG = false;
      bool DInQfomyhb = false;
      bool UMZkTGCsXt = false;
      bool JBikSthlqE = false;
      bool JLCqSDZPyX = false;
      bool nBtGFLaGIm = false;
      bool WYlxxCYCyl = false;
      bool GBHdRIKhSP = false;
      bool fluAGHGcfH = false;
      bool SadDhjZEsQ = false;
      bool eWRMQmtQow = false;
      bool BsnrGjdlqo = false;
      bool wuWqSfWDug = false;
      bool iFnCkJUiiT = false;
      bool NoniGZllwy = false;
      bool FnNETizZsk = false;
      bool PpVHNuElHx = false;
      bool PuCWbGHnkr = false;
      string ikaGMsKpEj;
      string TPGUgKlrIp;
      string UoLostSLqi;
      string LJYXREbMNr;
      string jduySIXYeF;
      string dyCNSsYkMS;
      string azyUYKphDb;
      string iZdPFpsMWk;
      string WsflFNHLFX;
      string fpzuRkfaZI;
      string RoUCVETmHb;
      string ALObugSMPK;
      string CebfwrZixU;
      string KSmNSgYdPA;
      string tTEcXTbXzk;
      string RSKOFmMoGd;
      string djolRgYAIN;
      string HowOQiazHb;
      string QCjLDqIXIf;
      string TiWlWJeRLq;
      if(ikaGMsKpEj == RoUCVETmHb){uaOkcbWuyW = true;}
      else if(RoUCVETmHb == ikaGMsKpEj){fluAGHGcfH = true;}
      if(TPGUgKlrIp == ALObugSMPK){MNgdNbAchZ = true;}
      else if(ALObugSMPK == TPGUgKlrIp){SadDhjZEsQ = true;}
      if(UoLostSLqi == CebfwrZixU){XArbtYRKrG = true;}
      else if(CebfwrZixU == UoLostSLqi){eWRMQmtQow = true;}
      if(LJYXREbMNr == KSmNSgYdPA){DInQfomyhb = true;}
      else if(KSmNSgYdPA == LJYXREbMNr){BsnrGjdlqo = true;}
      if(jduySIXYeF == tTEcXTbXzk){UMZkTGCsXt = true;}
      else if(tTEcXTbXzk == jduySIXYeF){wuWqSfWDug = true;}
      if(dyCNSsYkMS == RSKOFmMoGd){JBikSthlqE = true;}
      else if(RSKOFmMoGd == dyCNSsYkMS){iFnCkJUiiT = true;}
      if(azyUYKphDb == djolRgYAIN){JLCqSDZPyX = true;}
      else if(djolRgYAIN == azyUYKphDb){NoniGZllwy = true;}
      if(iZdPFpsMWk == HowOQiazHb){nBtGFLaGIm = true;}
      if(WsflFNHLFX == QCjLDqIXIf){WYlxxCYCyl = true;}
      if(fpzuRkfaZI == TiWlWJeRLq){GBHdRIKhSP = true;}
      while(HowOQiazHb == iZdPFpsMWk){FnNETizZsk = true;}
      while(QCjLDqIXIf == QCjLDqIXIf){PpVHNuElHx = true;}
      while(TiWlWJeRLq == TiWlWJeRLq){PuCWbGHnkr = true;}
      if(uaOkcbWuyW == true){uaOkcbWuyW = false;}
      if(MNgdNbAchZ == true){MNgdNbAchZ = false;}
      if(XArbtYRKrG == true){XArbtYRKrG = false;}
      if(DInQfomyhb == true){DInQfomyhb = false;}
      if(UMZkTGCsXt == true){UMZkTGCsXt = false;}
      if(JBikSthlqE == true){JBikSthlqE = false;}
      if(JLCqSDZPyX == true){JLCqSDZPyX = false;}
      if(nBtGFLaGIm == true){nBtGFLaGIm = false;}
      if(WYlxxCYCyl == true){WYlxxCYCyl = false;}
      if(GBHdRIKhSP == true){GBHdRIKhSP = false;}
      if(fluAGHGcfH == true){fluAGHGcfH = false;}
      if(SadDhjZEsQ == true){SadDhjZEsQ = false;}
      if(eWRMQmtQow == true){eWRMQmtQow = false;}
      if(BsnrGjdlqo == true){BsnrGjdlqo = false;}
      if(wuWqSfWDug == true){wuWqSfWDug = false;}
      if(iFnCkJUiiT == true){iFnCkJUiiT = false;}
      if(NoniGZllwy == true){NoniGZllwy = false;}
      if(FnNETizZsk == true){FnNETizZsk = false;}
      if(PpVHNuElHx == true){PpVHNuElHx = false;}
      if(PuCWbGHnkr == true){PuCWbGHnkr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBZEZJHRSK
{ 
  void lYfaCFJqdi()
  { 
      bool eSJSJQtmAS = false;
      bool TAyfUtfnRC = false;
      bool pTOkGcyfRm = false;
      bool PSDiAiEKyY = false;
      bool ABshJJykSd = false;
      bool ofJYrKDXMg = false;
      bool SOVMDAwPel = false;
      bool pUorBoagaw = false;
      bool eMNmyjJepo = false;
      bool efxRFlfgdJ = false;
      bool MiGfnTpQWD = false;
      bool jVxQCGAhNS = false;
      bool qRYpGJXXmO = false;
      bool JtCRiuGgze = false;
      bool trImFIigPz = false;
      bool kySKSuKPYd = false;
      bool wRdHtpSegG = false;
      bool zThiYyJkjy = false;
      bool apImdKarzn = false;
      bool kpHVibOAsO = false;
      string eGlFNluKnW;
      string NaTOMOpXdg;
      string rQoNOkrkNo;
      string eImmYbaWTP;
      string jpynHeNkVt;
      string NbDaIORYqc;
      string sJxyqEnfoj;
      string mSENxCRAFi;
      string WHPSbDFLdK;
      string KCfpVarAxC;
      string qgukHuXodG;
      string wQSHGlsdWn;
      string zbCeZklNrW;
      string JRDDroMdKg;
      string eQhXNsiYjj;
      string gNcJCOePLW;
      string IJwGxeNPOQ;
      string ZPTpIitdRf;
      string BNdIountAd;
      string KwRmYUTaai;
      if(eGlFNluKnW == qgukHuXodG){eSJSJQtmAS = true;}
      else if(qgukHuXodG == eGlFNluKnW){MiGfnTpQWD = true;}
      if(NaTOMOpXdg == wQSHGlsdWn){TAyfUtfnRC = true;}
      else if(wQSHGlsdWn == NaTOMOpXdg){jVxQCGAhNS = true;}
      if(rQoNOkrkNo == zbCeZklNrW){pTOkGcyfRm = true;}
      else if(zbCeZklNrW == rQoNOkrkNo){qRYpGJXXmO = true;}
      if(eImmYbaWTP == JRDDroMdKg){PSDiAiEKyY = true;}
      else if(JRDDroMdKg == eImmYbaWTP){JtCRiuGgze = true;}
      if(jpynHeNkVt == eQhXNsiYjj){ABshJJykSd = true;}
      else if(eQhXNsiYjj == jpynHeNkVt){trImFIigPz = true;}
      if(NbDaIORYqc == gNcJCOePLW){ofJYrKDXMg = true;}
      else if(gNcJCOePLW == NbDaIORYqc){kySKSuKPYd = true;}
      if(sJxyqEnfoj == IJwGxeNPOQ){SOVMDAwPel = true;}
      else if(IJwGxeNPOQ == sJxyqEnfoj){wRdHtpSegG = true;}
      if(mSENxCRAFi == ZPTpIitdRf){pUorBoagaw = true;}
      if(WHPSbDFLdK == BNdIountAd){eMNmyjJepo = true;}
      if(KCfpVarAxC == KwRmYUTaai){efxRFlfgdJ = true;}
      while(ZPTpIitdRf == mSENxCRAFi){zThiYyJkjy = true;}
      while(BNdIountAd == BNdIountAd){apImdKarzn = true;}
      while(KwRmYUTaai == KwRmYUTaai){kpHVibOAsO = true;}
      if(eSJSJQtmAS == true){eSJSJQtmAS = false;}
      if(TAyfUtfnRC == true){TAyfUtfnRC = false;}
      if(pTOkGcyfRm == true){pTOkGcyfRm = false;}
      if(PSDiAiEKyY == true){PSDiAiEKyY = false;}
      if(ABshJJykSd == true){ABshJJykSd = false;}
      if(ofJYrKDXMg == true){ofJYrKDXMg = false;}
      if(SOVMDAwPel == true){SOVMDAwPel = false;}
      if(pUorBoagaw == true){pUorBoagaw = false;}
      if(eMNmyjJepo == true){eMNmyjJepo = false;}
      if(efxRFlfgdJ == true){efxRFlfgdJ = false;}
      if(MiGfnTpQWD == true){MiGfnTpQWD = false;}
      if(jVxQCGAhNS == true){jVxQCGAhNS = false;}
      if(qRYpGJXXmO == true){qRYpGJXXmO = false;}
      if(JtCRiuGgze == true){JtCRiuGgze = false;}
      if(trImFIigPz == true){trImFIigPz = false;}
      if(kySKSuKPYd == true){kySKSuKPYd = false;}
      if(wRdHtpSegG == true){wRdHtpSegG = false;}
      if(zThiYyJkjy == true){zThiYyJkjy = false;}
      if(apImdKarzn == true){apImdKarzn = false;}
      if(kpHVibOAsO == true){kpHVibOAsO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUMJAWGTPW
{ 
  void oleOwyDjbC()
  { 
      bool HYpPwIOghH = false;
      bool HPVBANuUDp = false;
      bool ZyOakaVDec = false;
      bool CDOfKXFVYJ = false;
      bool jZQZnECZZa = false;
      bool rixCiIJPeV = false;
      bool mKCFFDAppb = false;
      bool HYwtFAgnmg = false;
      bool XwdEjTFLwB = false;
      bool OoqCVYWLUj = false;
      bool DMixSSlDxi = false;
      bool bUbxxqgxUl = false;
      bool xosoNRgsYf = false;
      bool cUTCcLNgkQ = false;
      bool gCONZsNtEe = false;
      bool rZpimOSsiA = false;
      bool lrdQFGAYUl = false;
      bool dALEEtZfOU = false;
      bool EmotnDdkPN = false;
      bool rTxkeoYyHS = false;
      string pwcESncZQe;
      string DddIyCPtiz;
      string PZTYeSeyli;
      string eDibwbTPSn;
      string cfzkOiOEMy;
      string SRCROPcEZA;
      string JdmhzAtCMV;
      string izauWiZhKw;
      string DalmQMARMf;
      string zPpSdyrRkN;
      string oMqqPSpGte;
      string otscwirAQm;
      string zcofWSJIQY;
      string pHxwHqiuWx;
      string VsXhqEVMVu;
      string GrAyNMWKTx;
      string JhpVngxxVF;
      string zxdTQFEHoR;
      string wwlURyGyhu;
      string TXaZnnDBsJ;
      if(pwcESncZQe == oMqqPSpGte){HYpPwIOghH = true;}
      else if(oMqqPSpGte == pwcESncZQe){DMixSSlDxi = true;}
      if(DddIyCPtiz == otscwirAQm){HPVBANuUDp = true;}
      else if(otscwirAQm == DddIyCPtiz){bUbxxqgxUl = true;}
      if(PZTYeSeyli == zcofWSJIQY){ZyOakaVDec = true;}
      else if(zcofWSJIQY == PZTYeSeyli){xosoNRgsYf = true;}
      if(eDibwbTPSn == pHxwHqiuWx){CDOfKXFVYJ = true;}
      else if(pHxwHqiuWx == eDibwbTPSn){cUTCcLNgkQ = true;}
      if(cfzkOiOEMy == VsXhqEVMVu){jZQZnECZZa = true;}
      else if(VsXhqEVMVu == cfzkOiOEMy){gCONZsNtEe = true;}
      if(SRCROPcEZA == GrAyNMWKTx){rixCiIJPeV = true;}
      else if(GrAyNMWKTx == SRCROPcEZA){rZpimOSsiA = true;}
      if(JdmhzAtCMV == JhpVngxxVF){mKCFFDAppb = true;}
      else if(JhpVngxxVF == JdmhzAtCMV){lrdQFGAYUl = true;}
      if(izauWiZhKw == zxdTQFEHoR){HYwtFAgnmg = true;}
      if(DalmQMARMf == wwlURyGyhu){XwdEjTFLwB = true;}
      if(zPpSdyrRkN == TXaZnnDBsJ){OoqCVYWLUj = true;}
      while(zxdTQFEHoR == izauWiZhKw){dALEEtZfOU = true;}
      while(wwlURyGyhu == wwlURyGyhu){EmotnDdkPN = true;}
      while(TXaZnnDBsJ == TXaZnnDBsJ){rTxkeoYyHS = true;}
      if(HYpPwIOghH == true){HYpPwIOghH = false;}
      if(HPVBANuUDp == true){HPVBANuUDp = false;}
      if(ZyOakaVDec == true){ZyOakaVDec = false;}
      if(CDOfKXFVYJ == true){CDOfKXFVYJ = false;}
      if(jZQZnECZZa == true){jZQZnECZZa = false;}
      if(rixCiIJPeV == true){rixCiIJPeV = false;}
      if(mKCFFDAppb == true){mKCFFDAppb = false;}
      if(HYwtFAgnmg == true){HYwtFAgnmg = false;}
      if(XwdEjTFLwB == true){XwdEjTFLwB = false;}
      if(OoqCVYWLUj == true){OoqCVYWLUj = false;}
      if(DMixSSlDxi == true){DMixSSlDxi = false;}
      if(bUbxxqgxUl == true){bUbxxqgxUl = false;}
      if(xosoNRgsYf == true){xosoNRgsYf = false;}
      if(cUTCcLNgkQ == true){cUTCcLNgkQ = false;}
      if(gCONZsNtEe == true){gCONZsNtEe = false;}
      if(rZpimOSsiA == true){rZpimOSsiA = false;}
      if(lrdQFGAYUl == true){lrdQFGAYUl = false;}
      if(dALEEtZfOU == true){dALEEtZfOU = false;}
      if(EmotnDdkPN == true){EmotnDdkPN = false;}
      if(rTxkeoYyHS == true){rTxkeoYyHS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJRTKHFMGS
{ 
  void dLcUClmJPn()
  { 
      bool zRDeCmtriT = false;
      bool ItDPSotFXU = false;
      bool qujjTXIAbp = false;
      bool YWIWBIgKHR = false;
      bool boOdAJtzyS = false;
      bool qzgkbDhSKe = false;
      bool esPrukkfNJ = false;
      bool HixFrBgGjJ = false;
      bool cJCIyYpXtx = false;
      bool aNzcmhZWhO = false;
      bool YOknLIBbrZ = false;
      bool WbhBBUqGsV = false;
      bool uNkQitjURJ = false;
      bool bKXVkOXOxp = false;
      bool XNeTZyeyaR = false;
      bool qScLSLcTEQ = false;
      bool XgJhyMDMPm = false;
      bool xbICyghRqj = false;
      bool OkszSJgMCZ = false;
      bool kEJfSqExVM = false;
      string ACaKyprGTF;
      string wqCdUDhlil;
      string QJbEdhIyBM;
      string IfBUSZzPFR;
      string HsCHMlBnGX;
      string XJOYxpZVfQ;
      string gtFGwPohLu;
      string DRgRdXGUrr;
      string fUqcnyRcWb;
      string zdjnjNnuKw;
      string xTcLTGcxtZ;
      string jFdnkMCbSy;
      string yLKiuZgsgQ;
      string iKKutMqeJh;
      string VUiwrtzwDX;
      string KMcLykIsQs;
      string YjPdqYthsX;
      string UXRkcdcOpB;
      string ajoJFWgyxI;
      string ExOQIlEFFT;
      if(ACaKyprGTF == xTcLTGcxtZ){zRDeCmtriT = true;}
      else if(xTcLTGcxtZ == ACaKyprGTF){YOknLIBbrZ = true;}
      if(wqCdUDhlil == jFdnkMCbSy){ItDPSotFXU = true;}
      else if(jFdnkMCbSy == wqCdUDhlil){WbhBBUqGsV = true;}
      if(QJbEdhIyBM == yLKiuZgsgQ){qujjTXIAbp = true;}
      else if(yLKiuZgsgQ == QJbEdhIyBM){uNkQitjURJ = true;}
      if(IfBUSZzPFR == iKKutMqeJh){YWIWBIgKHR = true;}
      else if(iKKutMqeJh == IfBUSZzPFR){bKXVkOXOxp = true;}
      if(HsCHMlBnGX == VUiwrtzwDX){boOdAJtzyS = true;}
      else if(VUiwrtzwDX == HsCHMlBnGX){XNeTZyeyaR = true;}
      if(XJOYxpZVfQ == KMcLykIsQs){qzgkbDhSKe = true;}
      else if(KMcLykIsQs == XJOYxpZVfQ){qScLSLcTEQ = true;}
      if(gtFGwPohLu == YjPdqYthsX){esPrukkfNJ = true;}
      else if(YjPdqYthsX == gtFGwPohLu){XgJhyMDMPm = true;}
      if(DRgRdXGUrr == UXRkcdcOpB){HixFrBgGjJ = true;}
      if(fUqcnyRcWb == ajoJFWgyxI){cJCIyYpXtx = true;}
      if(zdjnjNnuKw == ExOQIlEFFT){aNzcmhZWhO = true;}
      while(UXRkcdcOpB == DRgRdXGUrr){xbICyghRqj = true;}
      while(ajoJFWgyxI == ajoJFWgyxI){OkszSJgMCZ = true;}
      while(ExOQIlEFFT == ExOQIlEFFT){kEJfSqExVM = true;}
      if(zRDeCmtriT == true){zRDeCmtriT = false;}
      if(ItDPSotFXU == true){ItDPSotFXU = false;}
      if(qujjTXIAbp == true){qujjTXIAbp = false;}
      if(YWIWBIgKHR == true){YWIWBIgKHR = false;}
      if(boOdAJtzyS == true){boOdAJtzyS = false;}
      if(qzgkbDhSKe == true){qzgkbDhSKe = false;}
      if(esPrukkfNJ == true){esPrukkfNJ = false;}
      if(HixFrBgGjJ == true){HixFrBgGjJ = false;}
      if(cJCIyYpXtx == true){cJCIyYpXtx = false;}
      if(aNzcmhZWhO == true){aNzcmhZWhO = false;}
      if(YOknLIBbrZ == true){YOknLIBbrZ = false;}
      if(WbhBBUqGsV == true){WbhBBUqGsV = false;}
      if(uNkQitjURJ == true){uNkQitjURJ = false;}
      if(bKXVkOXOxp == true){bKXVkOXOxp = false;}
      if(XNeTZyeyaR == true){XNeTZyeyaR = false;}
      if(qScLSLcTEQ == true){qScLSLcTEQ = false;}
      if(XgJhyMDMPm == true){XgJhyMDMPm = false;}
      if(xbICyghRqj == true){xbICyghRqj = false;}
      if(OkszSJgMCZ == true){OkszSJgMCZ = false;}
      if(kEJfSqExVM == true){kEJfSqExVM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RHSVRKDXJR
{ 
  void abFmRbWHFR()
  { 
      bool WzKBSbiNSy = false;
      bool dbUfhKtmgB = false;
      bool tSxriDboUi = false;
      bool ZgqrtiZsuU = false;
      bool JLrpVxYOfq = false;
      bool lqNUgDBRSP = false;
      bool ztsiYxkbky = false;
      bool jBqLqiaHWk = false;
      bool eNIcwhTVKq = false;
      bool hIZfVPRIRY = false;
      bool MwdhHkACcy = false;
      bool btugklkQlp = false;
      bool dOQsQaaLob = false;
      bool QSpxYhjaVL = false;
      bool hQsMPmMrtj = false;
      bool eBVauxfjQf = false;
      bool KnMBhJDxID = false;
      bool BJtaIMVEdc = false;
      bool OhRFwPwPCa = false;
      bool CzKoAsDqeF = false;
      string FYignAhsEI;
      string VerIyNGkks;
      string XOmXSdiMqF;
      string EUgURIbPtL;
      string jWBYpFsuEY;
      string ZlGibqkLNK;
      string RVByEAyXpo;
      string lppYJBMNgN;
      string kmHSfROxrZ;
      string XQCjtNVCUo;
      string GUFPmiugYa;
      string dWdzYdOiSl;
      string lAePRVnGeu;
      string fJsqGPhrew;
      string VgXRwAlDKP;
      string yljhDGpoxR;
      string uoCduTdlrI;
      string wWDVPEbNTR;
      string ikuOxsZKnA;
      string ZstNBgetWb;
      if(FYignAhsEI == GUFPmiugYa){WzKBSbiNSy = true;}
      else if(GUFPmiugYa == FYignAhsEI){MwdhHkACcy = true;}
      if(VerIyNGkks == dWdzYdOiSl){dbUfhKtmgB = true;}
      else if(dWdzYdOiSl == VerIyNGkks){btugklkQlp = true;}
      if(XOmXSdiMqF == lAePRVnGeu){tSxriDboUi = true;}
      else if(lAePRVnGeu == XOmXSdiMqF){dOQsQaaLob = true;}
      if(EUgURIbPtL == fJsqGPhrew){ZgqrtiZsuU = true;}
      else if(fJsqGPhrew == EUgURIbPtL){QSpxYhjaVL = true;}
      if(jWBYpFsuEY == VgXRwAlDKP){JLrpVxYOfq = true;}
      else if(VgXRwAlDKP == jWBYpFsuEY){hQsMPmMrtj = true;}
      if(ZlGibqkLNK == yljhDGpoxR){lqNUgDBRSP = true;}
      else if(yljhDGpoxR == ZlGibqkLNK){eBVauxfjQf = true;}
      if(RVByEAyXpo == uoCduTdlrI){ztsiYxkbky = true;}
      else if(uoCduTdlrI == RVByEAyXpo){KnMBhJDxID = true;}
      if(lppYJBMNgN == wWDVPEbNTR){jBqLqiaHWk = true;}
      if(kmHSfROxrZ == ikuOxsZKnA){eNIcwhTVKq = true;}
      if(XQCjtNVCUo == ZstNBgetWb){hIZfVPRIRY = true;}
      while(wWDVPEbNTR == lppYJBMNgN){BJtaIMVEdc = true;}
      while(ikuOxsZKnA == ikuOxsZKnA){OhRFwPwPCa = true;}
      while(ZstNBgetWb == ZstNBgetWb){CzKoAsDqeF = true;}
      if(WzKBSbiNSy == true){WzKBSbiNSy = false;}
      if(dbUfhKtmgB == true){dbUfhKtmgB = false;}
      if(tSxriDboUi == true){tSxriDboUi = false;}
      if(ZgqrtiZsuU == true){ZgqrtiZsuU = false;}
      if(JLrpVxYOfq == true){JLrpVxYOfq = false;}
      if(lqNUgDBRSP == true){lqNUgDBRSP = false;}
      if(ztsiYxkbky == true){ztsiYxkbky = false;}
      if(jBqLqiaHWk == true){jBqLqiaHWk = false;}
      if(eNIcwhTVKq == true){eNIcwhTVKq = false;}
      if(hIZfVPRIRY == true){hIZfVPRIRY = false;}
      if(MwdhHkACcy == true){MwdhHkACcy = false;}
      if(btugklkQlp == true){btugklkQlp = false;}
      if(dOQsQaaLob == true){dOQsQaaLob = false;}
      if(QSpxYhjaVL == true){QSpxYhjaVL = false;}
      if(hQsMPmMrtj == true){hQsMPmMrtj = false;}
      if(eBVauxfjQf == true){eBVauxfjQf = false;}
      if(KnMBhJDxID == true){KnMBhJDxID = false;}
      if(BJtaIMVEdc == true){BJtaIMVEdc = false;}
      if(OhRFwPwPCa == true){OhRFwPwPCa = false;}
      if(CzKoAsDqeF == true){CzKoAsDqeF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELXMPXRPPR
{ 
  void JkrVJbSkER()
  { 
      bool GyYcGLEXsJ = false;
      bool HELBSLSNNf = false;
      bool APljMHGVXZ = false;
      bool inJNQTmaLb = false;
      bool eKWcrqCWyd = false;
      bool OfAgMpLoPz = false;
      bool EiASaTuyky = false;
      bool XqBlBosJqV = false;
      bool EjWsLCmcAZ = false;
      bool HyKMWwKECY = false;
      bool wElzGWdOeX = false;
      bool xCxttULHGX = false;
      bool gRxKqYfoPF = false;
      bool dnHSYAxXmn = false;
      bool YXxcbEBQSB = false;
      bool jDxdrdGaIg = false;
      bool qozZsIueUs = false;
      bool WnTSyIUUhl = false;
      bool XPVNUaqcZu = false;
      bool sWOFxjYXiS = false;
      string RkLJZiCZHR;
      string ilhOsnIMoT;
      string yeOCcsxyLY;
      string oeXPoDdjBo;
      string WswmqptjVj;
      string RYccumWIgg;
      string lDOibDNSZo;
      string KXKzxFhaLm;
      string zMbaHQCuTB;
      string gUCTDSeNLm;
      string baKfZsNcfp;
      string EuxtgYamaK;
      string BSzXIoUqwd;
      string aUPXKXBwBN;
      string DYPcxkWIld;
      string qqlAlJamXj;
      string XWfBPieYjJ;
      string WelNHbCWaW;
      string RMESmiiPlA;
      string wOXQpgsOMN;
      if(RkLJZiCZHR == baKfZsNcfp){GyYcGLEXsJ = true;}
      else if(baKfZsNcfp == RkLJZiCZHR){wElzGWdOeX = true;}
      if(ilhOsnIMoT == EuxtgYamaK){HELBSLSNNf = true;}
      else if(EuxtgYamaK == ilhOsnIMoT){xCxttULHGX = true;}
      if(yeOCcsxyLY == BSzXIoUqwd){APljMHGVXZ = true;}
      else if(BSzXIoUqwd == yeOCcsxyLY){gRxKqYfoPF = true;}
      if(oeXPoDdjBo == aUPXKXBwBN){inJNQTmaLb = true;}
      else if(aUPXKXBwBN == oeXPoDdjBo){dnHSYAxXmn = true;}
      if(WswmqptjVj == DYPcxkWIld){eKWcrqCWyd = true;}
      else if(DYPcxkWIld == WswmqptjVj){YXxcbEBQSB = true;}
      if(RYccumWIgg == qqlAlJamXj){OfAgMpLoPz = true;}
      else if(qqlAlJamXj == RYccumWIgg){jDxdrdGaIg = true;}
      if(lDOibDNSZo == XWfBPieYjJ){EiASaTuyky = true;}
      else if(XWfBPieYjJ == lDOibDNSZo){qozZsIueUs = true;}
      if(KXKzxFhaLm == WelNHbCWaW){XqBlBosJqV = true;}
      if(zMbaHQCuTB == RMESmiiPlA){EjWsLCmcAZ = true;}
      if(gUCTDSeNLm == wOXQpgsOMN){HyKMWwKECY = true;}
      while(WelNHbCWaW == KXKzxFhaLm){WnTSyIUUhl = true;}
      while(RMESmiiPlA == RMESmiiPlA){XPVNUaqcZu = true;}
      while(wOXQpgsOMN == wOXQpgsOMN){sWOFxjYXiS = true;}
      if(GyYcGLEXsJ == true){GyYcGLEXsJ = false;}
      if(HELBSLSNNf == true){HELBSLSNNf = false;}
      if(APljMHGVXZ == true){APljMHGVXZ = false;}
      if(inJNQTmaLb == true){inJNQTmaLb = false;}
      if(eKWcrqCWyd == true){eKWcrqCWyd = false;}
      if(OfAgMpLoPz == true){OfAgMpLoPz = false;}
      if(EiASaTuyky == true){EiASaTuyky = false;}
      if(XqBlBosJqV == true){XqBlBosJqV = false;}
      if(EjWsLCmcAZ == true){EjWsLCmcAZ = false;}
      if(HyKMWwKECY == true){HyKMWwKECY = false;}
      if(wElzGWdOeX == true){wElzGWdOeX = false;}
      if(xCxttULHGX == true){xCxttULHGX = false;}
      if(gRxKqYfoPF == true){gRxKqYfoPF = false;}
      if(dnHSYAxXmn == true){dnHSYAxXmn = false;}
      if(YXxcbEBQSB == true){YXxcbEBQSB = false;}
      if(jDxdrdGaIg == true){jDxdrdGaIg = false;}
      if(qozZsIueUs == true){qozZsIueUs = false;}
      if(WnTSyIUUhl == true){WnTSyIUUhl = false;}
      if(XPVNUaqcZu == true){XPVNUaqcZu = false;}
      if(sWOFxjYXiS == true){sWOFxjYXiS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFTDKEZMAJ
{ 
  void bkFlZAwCrr()
  { 
      bool IEXbeWToVM = false;
      bool QAGQhVywLn = false;
      bool IlyShPyDzo = false;
      bool lwOLHLCnSh = false;
      bool KDThanOZVA = false;
      bool ujDfJVGEsO = false;
      bool XQogaUktJV = false;
      bool TKdcdFSPrt = false;
      bool BYgztBrhCl = false;
      bool FxtDKtNmHG = false;
      bool CUPAgjGaCE = false;
      bool CpMzNyiplZ = false;
      bool bDqWPVPZRj = false;
      bool qeIlqfIgRJ = false;
      bool tRfyiPkupL = false;
      bool KWBgdzdskL = false;
      bool UgIRMXgaHh = false;
      bool pBXbfKXrnz = false;
      bool kUjGYTdbHr = false;
      bool BPuGoNJNkL = false;
      string kVVeEaSoYs;
      string opUKeXJeLk;
      string GYIAKbtyNI;
      string TNlhlUniWn;
      string tNRTAWuGqx;
      string hkeYTMMUTb;
      string fTaQYbDmXJ;
      string iZIWqsGoAm;
      string gnGQaiiNOZ;
      string ITPtIZlBtY;
      string SIhhNHbHhZ;
      string GXUfuqNKpo;
      string spXxAPKOOQ;
      string GEtaUYFXCT;
      string HaenTkyjyQ;
      string LbLEfbjjgy;
      string wNsQSBctLW;
      string koHVhSLjdP;
      string QaPxFespur;
      string nVqDWsgOUR;
      if(kVVeEaSoYs == SIhhNHbHhZ){IEXbeWToVM = true;}
      else if(SIhhNHbHhZ == kVVeEaSoYs){CUPAgjGaCE = true;}
      if(opUKeXJeLk == GXUfuqNKpo){QAGQhVywLn = true;}
      else if(GXUfuqNKpo == opUKeXJeLk){CpMzNyiplZ = true;}
      if(GYIAKbtyNI == spXxAPKOOQ){IlyShPyDzo = true;}
      else if(spXxAPKOOQ == GYIAKbtyNI){bDqWPVPZRj = true;}
      if(TNlhlUniWn == GEtaUYFXCT){lwOLHLCnSh = true;}
      else if(GEtaUYFXCT == TNlhlUniWn){qeIlqfIgRJ = true;}
      if(tNRTAWuGqx == HaenTkyjyQ){KDThanOZVA = true;}
      else if(HaenTkyjyQ == tNRTAWuGqx){tRfyiPkupL = true;}
      if(hkeYTMMUTb == LbLEfbjjgy){ujDfJVGEsO = true;}
      else if(LbLEfbjjgy == hkeYTMMUTb){KWBgdzdskL = true;}
      if(fTaQYbDmXJ == wNsQSBctLW){XQogaUktJV = true;}
      else if(wNsQSBctLW == fTaQYbDmXJ){UgIRMXgaHh = true;}
      if(iZIWqsGoAm == koHVhSLjdP){TKdcdFSPrt = true;}
      if(gnGQaiiNOZ == QaPxFespur){BYgztBrhCl = true;}
      if(ITPtIZlBtY == nVqDWsgOUR){FxtDKtNmHG = true;}
      while(koHVhSLjdP == iZIWqsGoAm){pBXbfKXrnz = true;}
      while(QaPxFespur == QaPxFespur){kUjGYTdbHr = true;}
      while(nVqDWsgOUR == nVqDWsgOUR){BPuGoNJNkL = true;}
      if(IEXbeWToVM == true){IEXbeWToVM = false;}
      if(QAGQhVywLn == true){QAGQhVywLn = false;}
      if(IlyShPyDzo == true){IlyShPyDzo = false;}
      if(lwOLHLCnSh == true){lwOLHLCnSh = false;}
      if(KDThanOZVA == true){KDThanOZVA = false;}
      if(ujDfJVGEsO == true){ujDfJVGEsO = false;}
      if(XQogaUktJV == true){XQogaUktJV = false;}
      if(TKdcdFSPrt == true){TKdcdFSPrt = false;}
      if(BYgztBrhCl == true){BYgztBrhCl = false;}
      if(FxtDKtNmHG == true){FxtDKtNmHG = false;}
      if(CUPAgjGaCE == true){CUPAgjGaCE = false;}
      if(CpMzNyiplZ == true){CpMzNyiplZ = false;}
      if(bDqWPVPZRj == true){bDqWPVPZRj = false;}
      if(qeIlqfIgRJ == true){qeIlqfIgRJ = false;}
      if(tRfyiPkupL == true){tRfyiPkupL = false;}
      if(KWBgdzdskL == true){KWBgdzdskL = false;}
      if(UgIRMXgaHh == true){UgIRMXgaHh = false;}
      if(pBXbfKXrnz == true){pBXbfKXrnz = false;}
      if(kUjGYTdbHr == true){kUjGYTdbHr = false;}
      if(BPuGoNJNkL == true){BPuGoNJNkL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPJCCHZEIN
{ 
  void BPmFWMrNwV()
  { 
      bool xNUIzSQGlL = false;
      bool bnhyuXrqRA = false;
      bool zNFWNfwJIA = false;
      bool jdoMzUUkNb = false;
      bool tpYqcdEkpS = false;
      bool chiofjIyuS = false;
      bool WGylaxyVza = false;
      bool DHcpGJoOti = false;
      bool bKSoWCtAgP = false;
      bool MWotEmrlPe = false;
      bool eilPPUEshV = false;
      bool ttDMqMmIPY = false;
      bool CxojOfShlS = false;
      bool RCzODrYDYC = false;
      bool xBRKUSTcDr = false;
      bool ziWqbhtCBj = false;
      bool CWHPEqunIz = false;
      bool njjNaBfdOw = false;
      bool MpesSifIlV = false;
      bool yVBozatBFc = false;
      string wBAcCxEysr;
      string gthjATJqbZ;
      string gjBncCEwmg;
      string jgfQmQNkEt;
      string UjWtIPRszn;
      string ZGSLfLALAA;
      string sIKMHANRwj;
      string GXlgFwNGfM;
      string kLwyHcNTka;
      string PBjDALYKmH;
      string BzwPhBUkGi;
      string ysfmPhMMEd;
      string lsgUTEmhft;
      string XCTXLkOfQF;
      string IcNBbWVxnS;
      string zMFIUHSaud;
      string OmEMLwYHbe;
      string TfwzVJferx;
      string hptNtKwLCE;
      string RmjlqVYBpf;
      if(wBAcCxEysr == BzwPhBUkGi){xNUIzSQGlL = true;}
      else if(BzwPhBUkGi == wBAcCxEysr){eilPPUEshV = true;}
      if(gthjATJqbZ == ysfmPhMMEd){bnhyuXrqRA = true;}
      else if(ysfmPhMMEd == gthjATJqbZ){ttDMqMmIPY = true;}
      if(gjBncCEwmg == lsgUTEmhft){zNFWNfwJIA = true;}
      else if(lsgUTEmhft == gjBncCEwmg){CxojOfShlS = true;}
      if(jgfQmQNkEt == XCTXLkOfQF){jdoMzUUkNb = true;}
      else if(XCTXLkOfQF == jgfQmQNkEt){RCzODrYDYC = true;}
      if(UjWtIPRszn == IcNBbWVxnS){tpYqcdEkpS = true;}
      else if(IcNBbWVxnS == UjWtIPRszn){xBRKUSTcDr = true;}
      if(ZGSLfLALAA == zMFIUHSaud){chiofjIyuS = true;}
      else if(zMFIUHSaud == ZGSLfLALAA){ziWqbhtCBj = true;}
      if(sIKMHANRwj == OmEMLwYHbe){WGylaxyVza = true;}
      else if(OmEMLwYHbe == sIKMHANRwj){CWHPEqunIz = true;}
      if(GXlgFwNGfM == TfwzVJferx){DHcpGJoOti = true;}
      if(kLwyHcNTka == hptNtKwLCE){bKSoWCtAgP = true;}
      if(PBjDALYKmH == RmjlqVYBpf){MWotEmrlPe = true;}
      while(TfwzVJferx == GXlgFwNGfM){njjNaBfdOw = true;}
      while(hptNtKwLCE == hptNtKwLCE){MpesSifIlV = true;}
      while(RmjlqVYBpf == RmjlqVYBpf){yVBozatBFc = true;}
      if(xNUIzSQGlL == true){xNUIzSQGlL = false;}
      if(bnhyuXrqRA == true){bnhyuXrqRA = false;}
      if(zNFWNfwJIA == true){zNFWNfwJIA = false;}
      if(jdoMzUUkNb == true){jdoMzUUkNb = false;}
      if(tpYqcdEkpS == true){tpYqcdEkpS = false;}
      if(chiofjIyuS == true){chiofjIyuS = false;}
      if(WGylaxyVza == true){WGylaxyVza = false;}
      if(DHcpGJoOti == true){DHcpGJoOti = false;}
      if(bKSoWCtAgP == true){bKSoWCtAgP = false;}
      if(MWotEmrlPe == true){MWotEmrlPe = false;}
      if(eilPPUEshV == true){eilPPUEshV = false;}
      if(ttDMqMmIPY == true){ttDMqMmIPY = false;}
      if(CxojOfShlS == true){CxojOfShlS = false;}
      if(RCzODrYDYC == true){RCzODrYDYC = false;}
      if(xBRKUSTcDr == true){xBRKUSTcDr = false;}
      if(ziWqbhtCBj == true){ziWqbhtCBj = false;}
      if(CWHPEqunIz == true){CWHPEqunIz = false;}
      if(njjNaBfdOw == true){njjNaBfdOw = false;}
      if(MpesSifIlV == true){MpesSifIlV = false;}
      if(yVBozatBFc == true){yVBozatBFc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTFFPQAPUP
{ 
  void ytRJVIfVRL()
  { 
      bool QKmGOAWlNn = false;
      bool LHqXGQbpgf = false;
      bool pOfwmYhxQg = false;
      bool OPgukXWBZz = false;
      bool BmnSLGpBsR = false;
      bool VdFnkBdqTp = false;
      bool RYUfYwZwli = false;
      bool tZPgdCZNjg = false;
      bool hgEyKkJrJj = false;
      bool sfhjhcSIsP = false;
      bool ftOKXwOXKi = false;
      bool aPGlHkUWVm = false;
      bool lhmCoNrezA = false;
      bool jRTUAnRsZO = false;
      bool WlhZIcZucx = false;
      bool IwmFdyGLVK = false;
      bool EiYJzJwlkS = false;
      bool SawGQzzMtL = false;
      bool nwCCrmeNpC = false;
      bool gFXPKnNXay = false;
      string NRNMQNKNEg;
      string rsNmlEaLqx;
      string AbENikjuTk;
      string jTQRFHMrME;
      string bBRDdNeKmL;
      string dAdIwlNzce;
      string cOtTxXcuhd;
      string rhymUzKBiV;
      string GYIHHjpHVT;
      string tMOgaNGyFF;
      string jicJTuBqnw;
      string bMPGYEGlLN;
      string hVZOjeSRLH;
      string rLudlWwynL;
      string hzTYqhwIIW;
      string HTlrWNIOZn;
      string bjegEPQlUB;
      string HHxAeiCBWB;
      string hKIozXZCGX;
      string NhYAixTlUb;
      if(NRNMQNKNEg == jicJTuBqnw){QKmGOAWlNn = true;}
      else if(jicJTuBqnw == NRNMQNKNEg){ftOKXwOXKi = true;}
      if(rsNmlEaLqx == bMPGYEGlLN){LHqXGQbpgf = true;}
      else if(bMPGYEGlLN == rsNmlEaLqx){aPGlHkUWVm = true;}
      if(AbENikjuTk == hVZOjeSRLH){pOfwmYhxQg = true;}
      else if(hVZOjeSRLH == AbENikjuTk){lhmCoNrezA = true;}
      if(jTQRFHMrME == rLudlWwynL){OPgukXWBZz = true;}
      else if(rLudlWwynL == jTQRFHMrME){jRTUAnRsZO = true;}
      if(bBRDdNeKmL == hzTYqhwIIW){BmnSLGpBsR = true;}
      else if(hzTYqhwIIW == bBRDdNeKmL){WlhZIcZucx = true;}
      if(dAdIwlNzce == HTlrWNIOZn){VdFnkBdqTp = true;}
      else if(HTlrWNIOZn == dAdIwlNzce){IwmFdyGLVK = true;}
      if(cOtTxXcuhd == bjegEPQlUB){RYUfYwZwli = true;}
      else if(bjegEPQlUB == cOtTxXcuhd){EiYJzJwlkS = true;}
      if(rhymUzKBiV == HHxAeiCBWB){tZPgdCZNjg = true;}
      if(GYIHHjpHVT == hKIozXZCGX){hgEyKkJrJj = true;}
      if(tMOgaNGyFF == NhYAixTlUb){sfhjhcSIsP = true;}
      while(HHxAeiCBWB == rhymUzKBiV){SawGQzzMtL = true;}
      while(hKIozXZCGX == hKIozXZCGX){nwCCrmeNpC = true;}
      while(NhYAixTlUb == NhYAixTlUb){gFXPKnNXay = true;}
      if(QKmGOAWlNn == true){QKmGOAWlNn = false;}
      if(LHqXGQbpgf == true){LHqXGQbpgf = false;}
      if(pOfwmYhxQg == true){pOfwmYhxQg = false;}
      if(OPgukXWBZz == true){OPgukXWBZz = false;}
      if(BmnSLGpBsR == true){BmnSLGpBsR = false;}
      if(VdFnkBdqTp == true){VdFnkBdqTp = false;}
      if(RYUfYwZwli == true){RYUfYwZwli = false;}
      if(tZPgdCZNjg == true){tZPgdCZNjg = false;}
      if(hgEyKkJrJj == true){hgEyKkJrJj = false;}
      if(sfhjhcSIsP == true){sfhjhcSIsP = false;}
      if(ftOKXwOXKi == true){ftOKXwOXKi = false;}
      if(aPGlHkUWVm == true){aPGlHkUWVm = false;}
      if(lhmCoNrezA == true){lhmCoNrezA = false;}
      if(jRTUAnRsZO == true){jRTUAnRsZO = false;}
      if(WlhZIcZucx == true){WlhZIcZucx = false;}
      if(IwmFdyGLVK == true){IwmFdyGLVK = false;}
      if(EiYJzJwlkS == true){EiYJzJwlkS = false;}
      if(SawGQzzMtL == true){SawGQzzMtL = false;}
      if(nwCCrmeNpC == true){nwCCrmeNpC = false;}
      if(gFXPKnNXay == true){gFXPKnNXay = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWWMQPZAFU
{ 
  void AIaVAUXeGV()
  { 
      bool HaRFcBqWeT = false;
      bool bwYuMjQmAq = false;
      bool PBWFhSjtDo = false;
      bool TWjASeYuNg = false;
      bool rGqnqxwUJr = false;
      bool BcretGEMXJ = false;
      bool RwSpzFLYcg = false;
      bool KUZSzJJhOj = false;
      bool VOkKmpdFGM = false;
      bool aMXDPumBnl = false;
      bool lXrbggDYek = false;
      bool wVynnCLIDI = false;
      bool aFSQFyxWDE = false;
      bool WItbxxWIcG = false;
      bool mEZUPFOiOM = false;
      bool idxeKfFaVi = false;
      bool ifVaOnaVpp = false;
      bool fDfxVVfxAA = false;
      bool iNHpUrKORQ = false;
      bool rulsWHiyGb = false;
      string CeanGfXhWK;
      string xgJIPnAYbX;
      string AIDoOdjSFY;
      string dlspUqgwiH;
      string urmMtVZiBk;
      string LqGwasakYc;
      string uFbyfLnTmX;
      string GDoTbIUqur;
      string DBQUMmfwPa;
      string QuWGLpPofi;
      string hGuddHBlUS;
      string YipgYtnHks;
      string eqDMHLfiIk;
      string rfKLJxFmpE;
      string ktbxCgEohR;
      string CIDmEqCiVS;
      string bSdiarYdXb;
      string oARgHjPGKa;
      string GqBpiicWHS;
      string tVQWcSQrVJ;
      if(CeanGfXhWK == hGuddHBlUS){HaRFcBqWeT = true;}
      else if(hGuddHBlUS == CeanGfXhWK){lXrbggDYek = true;}
      if(xgJIPnAYbX == YipgYtnHks){bwYuMjQmAq = true;}
      else if(YipgYtnHks == xgJIPnAYbX){wVynnCLIDI = true;}
      if(AIDoOdjSFY == eqDMHLfiIk){PBWFhSjtDo = true;}
      else if(eqDMHLfiIk == AIDoOdjSFY){aFSQFyxWDE = true;}
      if(dlspUqgwiH == rfKLJxFmpE){TWjASeYuNg = true;}
      else if(rfKLJxFmpE == dlspUqgwiH){WItbxxWIcG = true;}
      if(urmMtVZiBk == ktbxCgEohR){rGqnqxwUJr = true;}
      else if(ktbxCgEohR == urmMtVZiBk){mEZUPFOiOM = true;}
      if(LqGwasakYc == CIDmEqCiVS){BcretGEMXJ = true;}
      else if(CIDmEqCiVS == LqGwasakYc){idxeKfFaVi = true;}
      if(uFbyfLnTmX == bSdiarYdXb){RwSpzFLYcg = true;}
      else if(bSdiarYdXb == uFbyfLnTmX){ifVaOnaVpp = true;}
      if(GDoTbIUqur == oARgHjPGKa){KUZSzJJhOj = true;}
      if(DBQUMmfwPa == GqBpiicWHS){VOkKmpdFGM = true;}
      if(QuWGLpPofi == tVQWcSQrVJ){aMXDPumBnl = true;}
      while(oARgHjPGKa == GDoTbIUqur){fDfxVVfxAA = true;}
      while(GqBpiicWHS == GqBpiicWHS){iNHpUrKORQ = true;}
      while(tVQWcSQrVJ == tVQWcSQrVJ){rulsWHiyGb = true;}
      if(HaRFcBqWeT == true){HaRFcBqWeT = false;}
      if(bwYuMjQmAq == true){bwYuMjQmAq = false;}
      if(PBWFhSjtDo == true){PBWFhSjtDo = false;}
      if(TWjASeYuNg == true){TWjASeYuNg = false;}
      if(rGqnqxwUJr == true){rGqnqxwUJr = false;}
      if(BcretGEMXJ == true){BcretGEMXJ = false;}
      if(RwSpzFLYcg == true){RwSpzFLYcg = false;}
      if(KUZSzJJhOj == true){KUZSzJJhOj = false;}
      if(VOkKmpdFGM == true){VOkKmpdFGM = false;}
      if(aMXDPumBnl == true){aMXDPumBnl = false;}
      if(lXrbggDYek == true){lXrbggDYek = false;}
      if(wVynnCLIDI == true){wVynnCLIDI = false;}
      if(aFSQFyxWDE == true){aFSQFyxWDE = false;}
      if(WItbxxWIcG == true){WItbxxWIcG = false;}
      if(mEZUPFOiOM == true){mEZUPFOiOM = false;}
      if(idxeKfFaVi == true){idxeKfFaVi = false;}
      if(ifVaOnaVpp == true){ifVaOnaVpp = false;}
      if(fDfxVVfxAA == true){fDfxVVfxAA = false;}
      if(iNHpUrKORQ == true){iNHpUrKORQ = false;}
      if(rulsWHiyGb == true){rulsWHiyGb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUATHDXAXS
{ 
  void xcRjbmSSBo()
  { 
      bool PbwAeiVqUy = false;
      bool jVcdxCcpyG = false;
      bool JSTHFXITbH = false;
      bool wBKalZLzFb = false;
      bool CoWhoxrbRF = false;
      bool uCUNOxHntG = false;
      bool ZBPMBiKCrW = false;
      bool pcjWETwkRH = false;
      bool fgBVMtfwMo = false;
      bool SWFzCAZJfG = false;
      bool lpjuORRyJt = false;
      bool AVWlarAsAH = false;
      bool CNoDDTXkTD = false;
      bool smEKVpxGHt = false;
      bool chmSnwASXJ = false;
      bool AgIYEXAfqu = false;
      bool sfdFBMQLQk = false;
      bool uskGdTaWOH = false;
      bool TFNKDLeeGx = false;
      bool oQOLAwEhRa = false;
      string ZpVVAmJpGq;
      string hLcfXPMAWB;
      string XkGgbKHMzn;
      string BRTsDPmjIw;
      string urxaNtNSRG;
      string YuLYmnjnsp;
      string fwpRoPricI;
      string ccrZGeneSg;
      string xnurOGFtGO;
      string eypRQyCeky;
      string CdpJdwDkRH;
      string AEVMrqAxCi;
      string JxcNcelZJI;
      string cJsUeTylOS;
      string CUcyOabdZY;
      string xEbBnEAbfz;
      string KdbJdqKAhY;
      string sOijgoUezC;
      string CHAkKXgqgZ;
      string SVFOIYrTTX;
      if(ZpVVAmJpGq == CdpJdwDkRH){PbwAeiVqUy = true;}
      else if(CdpJdwDkRH == ZpVVAmJpGq){lpjuORRyJt = true;}
      if(hLcfXPMAWB == AEVMrqAxCi){jVcdxCcpyG = true;}
      else if(AEVMrqAxCi == hLcfXPMAWB){AVWlarAsAH = true;}
      if(XkGgbKHMzn == JxcNcelZJI){JSTHFXITbH = true;}
      else if(JxcNcelZJI == XkGgbKHMzn){CNoDDTXkTD = true;}
      if(BRTsDPmjIw == cJsUeTylOS){wBKalZLzFb = true;}
      else if(cJsUeTylOS == BRTsDPmjIw){smEKVpxGHt = true;}
      if(urxaNtNSRG == CUcyOabdZY){CoWhoxrbRF = true;}
      else if(CUcyOabdZY == urxaNtNSRG){chmSnwASXJ = true;}
      if(YuLYmnjnsp == xEbBnEAbfz){uCUNOxHntG = true;}
      else if(xEbBnEAbfz == YuLYmnjnsp){AgIYEXAfqu = true;}
      if(fwpRoPricI == KdbJdqKAhY){ZBPMBiKCrW = true;}
      else if(KdbJdqKAhY == fwpRoPricI){sfdFBMQLQk = true;}
      if(ccrZGeneSg == sOijgoUezC){pcjWETwkRH = true;}
      if(xnurOGFtGO == CHAkKXgqgZ){fgBVMtfwMo = true;}
      if(eypRQyCeky == SVFOIYrTTX){SWFzCAZJfG = true;}
      while(sOijgoUezC == ccrZGeneSg){uskGdTaWOH = true;}
      while(CHAkKXgqgZ == CHAkKXgqgZ){TFNKDLeeGx = true;}
      while(SVFOIYrTTX == SVFOIYrTTX){oQOLAwEhRa = true;}
      if(PbwAeiVqUy == true){PbwAeiVqUy = false;}
      if(jVcdxCcpyG == true){jVcdxCcpyG = false;}
      if(JSTHFXITbH == true){JSTHFXITbH = false;}
      if(wBKalZLzFb == true){wBKalZLzFb = false;}
      if(CoWhoxrbRF == true){CoWhoxrbRF = false;}
      if(uCUNOxHntG == true){uCUNOxHntG = false;}
      if(ZBPMBiKCrW == true){ZBPMBiKCrW = false;}
      if(pcjWETwkRH == true){pcjWETwkRH = false;}
      if(fgBVMtfwMo == true){fgBVMtfwMo = false;}
      if(SWFzCAZJfG == true){SWFzCAZJfG = false;}
      if(lpjuORRyJt == true){lpjuORRyJt = false;}
      if(AVWlarAsAH == true){AVWlarAsAH = false;}
      if(CNoDDTXkTD == true){CNoDDTXkTD = false;}
      if(smEKVpxGHt == true){smEKVpxGHt = false;}
      if(chmSnwASXJ == true){chmSnwASXJ = false;}
      if(AgIYEXAfqu == true){AgIYEXAfqu = false;}
      if(sfdFBMQLQk == true){sfdFBMQLQk = false;}
      if(uskGdTaWOH == true){uskGdTaWOH = false;}
      if(TFNKDLeeGx == true){TFNKDLeeGx = false;}
      if(oQOLAwEhRa == true){oQOLAwEhRa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZPLMAIBXV
{ 
  void QBbTwJuLGb()
  { 
      bool HEEZwtncLC = false;
      bool rYUkJXtIRJ = false;
      bool bMFhBkjPzr = false;
      bool EsWdjNffyP = false;
      bool jIzRdJyqaM = false;
      bool JmRggtyWYK = false;
      bool KYdSxzCqAw = false;
      bool qNKBZSMnEr = false;
      bool msnmiQaowo = false;
      bool OJHmFLegTd = false;
      bool GHpeUucPGO = false;
      bool gKSgXRjpif = false;
      bool YMtLghGXwN = false;
      bool mfTZkeCJRm = false;
      bool nLihIDqaOn = false;
      bool bnynFtMexm = false;
      bool oETraBqrur = false;
      bool OaYurNdLCc = false;
      bool qfIHlygfUp = false;
      bool SXLexjqpHG = false;
      string MUCzctWoUk;
      string cZDqjYzotd;
      string dGDdCePBlw;
      string PdhrroAALO;
      string rIPcDBkSuy;
      string AuedTFRXwx;
      string eVDYUzrLyu;
      string YydflUqZaA;
      string txFmuUyDXm;
      string WbENiVFqHD;
      string JZTAZCQzry;
      string OqxuDhQPcA;
      string AnmLXxsQwP;
      string PASWqTcENs;
      string DzLZXfeIJB;
      string FpNHDUlIcb;
      string IADbiOXZEi;
      string FLBjwAcNmq;
      string SkGtJYlLTV;
      string hTbkjDwiqJ;
      if(MUCzctWoUk == JZTAZCQzry){HEEZwtncLC = true;}
      else if(JZTAZCQzry == MUCzctWoUk){GHpeUucPGO = true;}
      if(cZDqjYzotd == OqxuDhQPcA){rYUkJXtIRJ = true;}
      else if(OqxuDhQPcA == cZDqjYzotd){gKSgXRjpif = true;}
      if(dGDdCePBlw == AnmLXxsQwP){bMFhBkjPzr = true;}
      else if(AnmLXxsQwP == dGDdCePBlw){YMtLghGXwN = true;}
      if(PdhrroAALO == PASWqTcENs){EsWdjNffyP = true;}
      else if(PASWqTcENs == PdhrroAALO){mfTZkeCJRm = true;}
      if(rIPcDBkSuy == DzLZXfeIJB){jIzRdJyqaM = true;}
      else if(DzLZXfeIJB == rIPcDBkSuy){nLihIDqaOn = true;}
      if(AuedTFRXwx == FpNHDUlIcb){JmRggtyWYK = true;}
      else if(FpNHDUlIcb == AuedTFRXwx){bnynFtMexm = true;}
      if(eVDYUzrLyu == IADbiOXZEi){KYdSxzCqAw = true;}
      else if(IADbiOXZEi == eVDYUzrLyu){oETraBqrur = true;}
      if(YydflUqZaA == FLBjwAcNmq){qNKBZSMnEr = true;}
      if(txFmuUyDXm == SkGtJYlLTV){msnmiQaowo = true;}
      if(WbENiVFqHD == hTbkjDwiqJ){OJHmFLegTd = true;}
      while(FLBjwAcNmq == YydflUqZaA){OaYurNdLCc = true;}
      while(SkGtJYlLTV == SkGtJYlLTV){qfIHlygfUp = true;}
      while(hTbkjDwiqJ == hTbkjDwiqJ){SXLexjqpHG = true;}
      if(HEEZwtncLC == true){HEEZwtncLC = false;}
      if(rYUkJXtIRJ == true){rYUkJXtIRJ = false;}
      if(bMFhBkjPzr == true){bMFhBkjPzr = false;}
      if(EsWdjNffyP == true){EsWdjNffyP = false;}
      if(jIzRdJyqaM == true){jIzRdJyqaM = false;}
      if(JmRggtyWYK == true){JmRggtyWYK = false;}
      if(KYdSxzCqAw == true){KYdSxzCqAw = false;}
      if(qNKBZSMnEr == true){qNKBZSMnEr = false;}
      if(msnmiQaowo == true){msnmiQaowo = false;}
      if(OJHmFLegTd == true){OJHmFLegTd = false;}
      if(GHpeUucPGO == true){GHpeUucPGO = false;}
      if(gKSgXRjpif == true){gKSgXRjpif = false;}
      if(YMtLghGXwN == true){YMtLghGXwN = false;}
      if(mfTZkeCJRm == true){mfTZkeCJRm = false;}
      if(nLihIDqaOn == true){nLihIDqaOn = false;}
      if(bnynFtMexm == true){bnynFtMexm = false;}
      if(oETraBqrur == true){oETraBqrur = false;}
      if(OaYurNdLCc == true){OaYurNdLCc = false;}
      if(qfIHlygfUp == true){qfIHlygfUp = false;}
      if(SXLexjqpHG == true){SXLexjqpHG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZJDYNYNVW
{ 
  void QDHKRfmdpB()
  { 
      bool eTwiozAzmK = false;
      bool RgCnDBaPfM = false;
      bool BWuUugAzGx = false;
      bool hTIJGBtUfK = false;
      bool DkdTsYxYgj = false;
      bool UthsoIYamH = false;
      bool zArpbyXrgC = false;
      bool HFiVJQraaV = false;
      bool iaSWcmkPUy = false;
      bool cSgXKCrnqt = false;
      bool AEqdbOKMiY = false;
      bool PxARXXhUNo = false;
      bool MIXiZnYLKG = false;
      bool XEifUeintN = false;
      bool cYfuheSPzl = false;
      bool UXaChrfIEm = false;
      bool ozCcBLNTws = false;
      bool otZzLnbcAt = false;
      bool VJLXlzcgyc = false;
      bool yZiGXdWDtW = false;
      string SmkOVFknxA;
      string AIKIEjqMcT;
      string pPDMceiPwl;
      string ptJyqpWFgd;
      string jWZHshsyuz;
      string xyZuXCiYlp;
      string WVqLJGyLRN;
      string MleyjTpwSt;
      string kkUworUOan;
      string HyTpHNeOym;
      string ihggmKSaLE;
      string MmFqFkBtWR;
      string kjkcGNSnqV;
      string nayfKDEmJd;
      string YsCVbUsbkV;
      string MkqfBzwDZY;
      string rdjoPkoYfC;
      string gNjrrqgOAl;
      string UpDUJDjRdL;
      string GANkluJNFq;
      if(SmkOVFknxA == ihggmKSaLE){eTwiozAzmK = true;}
      else if(ihggmKSaLE == SmkOVFknxA){AEqdbOKMiY = true;}
      if(AIKIEjqMcT == MmFqFkBtWR){RgCnDBaPfM = true;}
      else if(MmFqFkBtWR == AIKIEjqMcT){PxARXXhUNo = true;}
      if(pPDMceiPwl == kjkcGNSnqV){BWuUugAzGx = true;}
      else if(kjkcGNSnqV == pPDMceiPwl){MIXiZnYLKG = true;}
      if(ptJyqpWFgd == nayfKDEmJd){hTIJGBtUfK = true;}
      else if(nayfKDEmJd == ptJyqpWFgd){XEifUeintN = true;}
      if(jWZHshsyuz == YsCVbUsbkV){DkdTsYxYgj = true;}
      else if(YsCVbUsbkV == jWZHshsyuz){cYfuheSPzl = true;}
      if(xyZuXCiYlp == MkqfBzwDZY){UthsoIYamH = true;}
      else if(MkqfBzwDZY == xyZuXCiYlp){UXaChrfIEm = true;}
      if(WVqLJGyLRN == rdjoPkoYfC){zArpbyXrgC = true;}
      else if(rdjoPkoYfC == WVqLJGyLRN){ozCcBLNTws = true;}
      if(MleyjTpwSt == gNjrrqgOAl){HFiVJQraaV = true;}
      if(kkUworUOan == UpDUJDjRdL){iaSWcmkPUy = true;}
      if(HyTpHNeOym == GANkluJNFq){cSgXKCrnqt = true;}
      while(gNjrrqgOAl == MleyjTpwSt){otZzLnbcAt = true;}
      while(UpDUJDjRdL == UpDUJDjRdL){VJLXlzcgyc = true;}
      while(GANkluJNFq == GANkluJNFq){yZiGXdWDtW = true;}
      if(eTwiozAzmK == true){eTwiozAzmK = false;}
      if(RgCnDBaPfM == true){RgCnDBaPfM = false;}
      if(BWuUugAzGx == true){BWuUugAzGx = false;}
      if(hTIJGBtUfK == true){hTIJGBtUfK = false;}
      if(DkdTsYxYgj == true){DkdTsYxYgj = false;}
      if(UthsoIYamH == true){UthsoIYamH = false;}
      if(zArpbyXrgC == true){zArpbyXrgC = false;}
      if(HFiVJQraaV == true){HFiVJQraaV = false;}
      if(iaSWcmkPUy == true){iaSWcmkPUy = false;}
      if(cSgXKCrnqt == true){cSgXKCrnqt = false;}
      if(AEqdbOKMiY == true){AEqdbOKMiY = false;}
      if(PxARXXhUNo == true){PxARXXhUNo = false;}
      if(MIXiZnYLKG == true){MIXiZnYLKG = false;}
      if(XEifUeintN == true){XEifUeintN = false;}
      if(cYfuheSPzl == true){cYfuheSPzl = false;}
      if(UXaChrfIEm == true){UXaChrfIEm = false;}
      if(ozCcBLNTws == true){ozCcBLNTws = false;}
      if(otZzLnbcAt == true){otZzLnbcAt = false;}
      if(VJLXlzcgyc == true){VJLXlzcgyc = false;}
      if(yZiGXdWDtW == true){yZiGXdWDtW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWQUISGOSV
{ 
  void AnSMBpgXdp()
  { 
      bool bRiqxIwrVZ = false;
      bool WlBkdcnZED = false;
      bool yirCXToHVT = false;
      bool jCMSohQnCx = false;
      bool cskKakqJXj = false;
      bool PhyscrZgTd = false;
      bool ToWCpTYiuw = false;
      bool LAXHZFygam = false;
      bool beikECETow = false;
      bool HjTXdnViUH = false;
      bool LINaYPKqSX = false;
      bool trFgBoFkxn = false;
      bool OFsynafzdl = false;
      bool iOMTaTQIMn = false;
      bool rNARBPemWn = false;
      bool ikkgrGPPlx = false;
      bool iKNgneflFh = false;
      bool XxXIuBFawY = false;
      bool wscoDydeaU = false;
      bool DBVOEgAScW = false;
      string wRSSSMfIdN;
      string XIukllAfjP;
      string ZlilTEPOJE;
      string KdLZTrKIOL;
      string pwYrntDUfB;
      string DCJknJhfzO;
      string xQyYDtwVQs;
      string arRYZdMpyY;
      string AtiHBHTakJ;
      string JdJANZxzot;
      string ygElaLkkLK;
      string xqhZNDgpXu;
      string aVkHiwiRKz;
      string fMBEZSpxgo;
      string WhOaMRwilK;
      string rGatScwwCe;
      string cTZLdjpdzt;
      string MjJiXrGJuR;
      string AAeAGZkHkx;
      string WstCMDIDxb;
      if(wRSSSMfIdN == ygElaLkkLK){bRiqxIwrVZ = true;}
      else if(ygElaLkkLK == wRSSSMfIdN){LINaYPKqSX = true;}
      if(XIukllAfjP == xqhZNDgpXu){WlBkdcnZED = true;}
      else if(xqhZNDgpXu == XIukllAfjP){trFgBoFkxn = true;}
      if(ZlilTEPOJE == aVkHiwiRKz){yirCXToHVT = true;}
      else if(aVkHiwiRKz == ZlilTEPOJE){OFsynafzdl = true;}
      if(KdLZTrKIOL == fMBEZSpxgo){jCMSohQnCx = true;}
      else if(fMBEZSpxgo == KdLZTrKIOL){iOMTaTQIMn = true;}
      if(pwYrntDUfB == WhOaMRwilK){cskKakqJXj = true;}
      else if(WhOaMRwilK == pwYrntDUfB){rNARBPemWn = true;}
      if(DCJknJhfzO == rGatScwwCe){PhyscrZgTd = true;}
      else if(rGatScwwCe == DCJknJhfzO){ikkgrGPPlx = true;}
      if(xQyYDtwVQs == cTZLdjpdzt){ToWCpTYiuw = true;}
      else if(cTZLdjpdzt == xQyYDtwVQs){iKNgneflFh = true;}
      if(arRYZdMpyY == MjJiXrGJuR){LAXHZFygam = true;}
      if(AtiHBHTakJ == AAeAGZkHkx){beikECETow = true;}
      if(JdJANZxzot == WstCMDIDxb){HjTXdnViUH = true;}
      while(MjJiXrGJuR == arRYZdMpyY){XxXIuBFawY = true;}
      while(AAeAGZkHkx == AAeAGZkHkx){wscoDydeaU = true;}
      while(WstCMDIDxb == WstCMDIDxb){DBVOEgAScW = true;}
      if(bRiqxIwrVZ == true){bRiqxIwrVZ = false;}
      if(WlBkdcnZED == true){WlBkdcnZED = false;}
      if(yirCXToHVT == true){yirCXToHVT = false;}
      if(jCMSohQnCx == true){jCMSohQnCx = false;}
      if(cskKakqJXj == true){cskKakqJXj = false;}
      if(PhyscrZgTd == true){PhyscrZgTd = false;}
      if(ToWCpTYiuw == true){ToWCpTYiuw = false;}
      if(LAXHZFygam == true){LAXHZFygam = false;}
      if(beikECETow == true){beikECETow = false;}
      if(HjTXdnViUH == true){HjTXdnViUH = false;}
      if(LINaYPKqSX == true){LINaYPKqSX = false;}
      if(trFgBoFkxn == true){trFgBoFkxn = false;}
      if(OFsynafzdl == true){OFsynafzdl = false;}
      if(iOMTaTQIMn == true){iOMTaTQIMn = false;}
      if(rNARBPemWn == true){rNARBPemWn = false;}
      if(ikkgrGPPlx == true){ikkgrGPPlx = false;}
      if(iKNgneflFh == true){iKNgneflFh = false;}
      if(XxXIuBFawY == true){XxXIuBFawY = false;}
      if(wscoDydeaU == true){wscoDydeaU = false;}
      if(DBVOEgAScW == true){DBVOEgAScW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AREWXRBWNL
{ 
  void BwHCniDcno()
  { 
      bool YcVhpETbca = false;
      bool muPgreqPnL = false;
      bool OhkQZEAHjD = false;
      bool iwCllRoswV = false;
      bool AClxgVWDHe = false;
      bool UekOcqqFHk = false;
      bool DLqYqqrctZ = false;
      bool pxSSKLuniE = false;
      bool hxzEiEKmIt = false;
      bool ZilLRnLNGp = false;
      bool csIgoWLSER = false;
      bool uDVCDGMlpl = false;
      bool fFUzAHLHAV = false;
      bool AhhrbnoSPL = false;
      bool sriqzWMiHL = false;
      bool bYXUKWYIgh = false;
      bool LDRhQNVcZP = false;
      bool RsWdsmVcAd = false;
      bool tcAnsaJNhE = false;
      bool OglhAoaAZk = false;
      string MhgDBJzhRQ;
      string LmlsqcVpqb;
      string hwekrWwlhJ;
      string XPKVxfUgjS;
      string MTahbwYGkb;
      string yYwroQDuKe;
      string NMzHsucQwK;
      string HoGYOOUxJw;
      string xpBGKyTRgf;
      string cZVFEATTnf;
      string SIJZTJSWcZ;
      string uGlOgXLswu;
      string bKjPhhSATO;
      string tBIccofblB;
      string exoGkWmHYg;
      string nZWsEIYsrl;
      string pSCOfsxJkq;
      string qjGuPdVcdK;
      string tLamZTePXU;
      string QljzKMtZar;
      if(MhgDBJzhRQ == SIJZTJSWcZ){YcVhpETbca = true;}
      else if(SIJZTJSWcZ == MhgDBJzhRQ){csIgoWLSER = true;}
      if(LmlsqcVpqb == uGlOgXLswu){muPgreqPnL = true;}
      else if(uGlOgXLswu == LmlsqcVpqb){uDVCDGMlpl = true;}
      if(hwekrWwlhJ == bKjPhhSATO){OhkQZEAHjD = true;}
      else if(bKjPhhSATO == hwekrWwlhJ){fFUzAHLHAV = true;}
      if(XPKVxfUgjS == tBIccofblB){iwCllRoswV = true;}
      else if(tBIccofblB == XPKVxfUgjS){AhhrbnoSPL = true;}
      if(MTahbwYGkb == exoGkWmHYg){AClxgVWDHe = true;}
      else if(exoGkWmHYg == MTahbwYGkb){sriqzWMiHL = true;}
      if(yYwroQDuKe == nZWsEIYsrl){UekOcqqFHk = true;}
      else if(nZWsEIYsrl == yYwroQDuKe){bYXUKWYIgh = true;}
      if(NMzHsucQwK == pSCOfsxJkq){DLqYqqrctZ = true;}
      else if(pSCOfsxJkq == NMzHsucQwK){LDRhQNVcZP = true;}
      if(HoGYOOUxJw == qjGuPdVcdK){pxSSKLuniE = true;}
      if(xpBGKyTRgf == tLamZTePXU){hxzEiEKmIt = true;}
      if(cZVFEATTnf == QljzKMtZar){ZilLRnLNGp = true;}
      while(qjGuPdVcdK == HoGYOOUxJw){RsWdsmVcAd = true;}
      while(tLamZTePXU == tLamZTePXU){tcAnsaJNhE = true;}
      while(QljzKMtZar == QljzKMtZar){OglhAoaAZk = true;}
      if(YcVhpETbca == true){YcVhpETbca = false;}
      if(muPgreqPnL == true){muPgreqPnL = false;}
      if(OhkQZEAHjD == true){OhkQZEAHjD = false;}
      if(iwCllRoswV == true){iwCllRoswV = false;}
      if(AClxgVWDHe == true){AClxgVWDHe = false;}
      if(UekOcqqFHk == true){UekOcqqFHk = false;}
      if(DLqYqqrctZ == true){DLqYqqrctZ = false;}
      if(pxSSKLuniE == true){pxSSKLuniE = false;}
      if(hxzEiEKmIt == true){hxzEiEKmIt = false;}
      if(ZilLRnLNGp == true){ZilLRnLNGp = false;}
      if(csIgoWLSER == true){csIgoWLSER = false;}
      if(uDVCDGMlpl == true){uDVCDGMlpl = false;}
      if(fFUzAHLHAV == true){fFUzAHLHAV = false;}
      if(AhhrbnoSPL == true){AhhrbnoSPL = false;}
      if(sriqzWMiHL == true){sriqzWMiHL = false;}
      if(bYXUKWYIgh == true){bYXUKWYIgh = false;}
      if(LDRhQNVcZP == true){LDRhQNVcZP = false;}
      if(RsWdsmVcAd == true){RsWdsmVcAd = false;}
      if(tcAnsaJNhE == true){tcAnsaJNhE = false;}
      if(OglhAoaAZk == true){OglhAoaAZk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHKLCRUQZZ
{ 
  void gkBiBpJOuk()
  { 
      bool MXLGPPywVk = false;
      bool sTttEYUQeV = false;
      bool MUMzLDtsUq = false;
      bool KEuOAHlhGI = false;
      bool MHkpSwVQWW = false;
      bool UnJkkqLMuM = false;
      bool VFadanXetw = false;
      bool lmKVIFjWfP = false;
      bool gcVyWVuKdI = false;
      bool wYmslHfHOd = false;
      bool XpWajhdnbf = false;
      bool HofefsicHE = false;
      bool sMBkzNAQiB = false;
      bool YbHCrpFtNn = false;
      bool rHiyBHrHNs = false;
      bool XDzKjKokaW = false;
      bool hMEZGegdmo = false;
      bool moOSLldDjr = false;
      bool UrDodVcxRg = false;
      bool BTTqGeCJqV = false;
      string ylDDKPaLrE;
      string RFWVxFOgIq;
      string yBAyWxRWoA;
      string mSdjuQiNLZ;
      string AVmCJzyKrz;
      string rEdnmwlFgN;
      string yEVqQyamag;
      string VBVhpcNxnW;
      string yHeoIiopxy;
      string dcfxauzwlL;
      string XLiKcqhuyJ;
      string inQJOqZghh;
      string JkobCrUXGt;
      string dRLcylXTLR;
      string AsrmPoMWij;
      string VSNDBmWHHj;
      string VJnDfRcnKb;
      string TFUQhPsCMM;
      string fxoWYKEHaL;
      string PQLbupFnGy;
      if(ylDDKPaLrE == XLiKcqhuyJ){MXLGPPywVk = true;}
      else if(XLiKcqhuyJ == ylDDKPaLrE){XpWajhdnbf = true;}
      if(RFWVxFOgIq == inQJOqZghh){sTttEYUQeV = true;}
      else if(inQJOqZghh == RFWVxFOgIq){HofefsicHE = true;}
      if(yBAyWxRWoA == JkobCrUXGt){MUMzLDtsUq = true;}
      else if(JkobCrUXGt == yBAyWxRWoA){sMBkzNAQiB = true;}
      if(mSdjuQiNLZ == dRLcylXTLR){KEuOAHlhGI = true;}
      else if(dRLcylXTLR == mSdjuQiNLZ){YbHCrpFtNn = true;}
      if(AVmCJzyKrz == AsrmPoMWij){MHkpSwVQWW = true;}
      else if(AsrmPoMWij == AVmCJzyKrz){rHiyBHrHNs = true;}
      if(rEdnmwlFgN == VSNDBmWHHj){UnJkkqLMuM = true;}
      else if(VSNDBmWHHj == rEdnmwlFgN){XDzKjKokaW = true;}
      if(yEVqQyamag == VJnDfRcnKb){VFadanXetw = true;}
      else if(VJnDfRcnKb == yEVqQyamag){hMEZGegdmo = true;}
      if(VBVhpcNxnW == TFUQhPsCMM){lmKVIFjWfP = true;}
      if(yHeoIiopxy == fxoWYKEHaL){gcVyWVuKdI = true;}
      if(dcfxauzwlL == PQLbupFnGy){wYmslHfHOd = true;}
      while(TFUQhPsCMM == VBVhpcNxnW){moOSLldDjr = true;}
      while(fxoWYKEHaL == fxoWYKEHaL){UrDodVcxRg = true;}
      while(PQLbupFnGy == PQLbupFnGy){BTTqGeCJqV = true;}
      if(MXLGPPywVk == true){MXLGPPywVk = false;}
      if(sTttEYUQeV == true){sTttEYUQeV = false;}
      if(MUMzLDtsUq == true){MUMzLDtsUq = false;}
      if(KEuOAHlhGI == true){KEuOAHlhGI = false;}
      if(MHkpSwVQWW == true){MHkpSwVQWW = false;}
      if(UnJkkqLMuM == true){UnJkkqLMuM = false;}
      if(VFadanXetw == true){VFadanXetw = false;}
      if(lmKVIFjWfP == true){lmKVIFjWfP = false;}
      if(gcVyWVuKdI == true){gcVyWVuKdI = false;}
      if(wYmslHfHOd == true){wYmslHfHOd = false;}
      if(XpWajhdnbf == true){XpWajhdnbf = false;}
      if(HofefsicHE == true){HofefsicHE = false;}
      if(sMBkzNAQiB == true){sMBkzNAQiB = false;}
      if(YbHCrpFtNn == true){YbHCrpFtNn = false;}
      if(rHiyBHrHNs == true){rHiyBHrHNs = false;}
      if(XDzKjKokaW == true){XDzKjKokaW = false;}
      if(hMEZGegdmo == true){hMEZGegdmo = false;}
      if(moOSLldDjr == true){moOSLldDjr = false;}
      if(UrDodVcxRg == true){UrDodVcxRg = false;}
      if(BTTqGeCJqV == true){BTTqGeCJqV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HESXEOYIJF
{ 
  void YKcrNWgZcN()
  { 
      bool CWCeccRXCP = false;
      bool EpIAsfphNS = false;
      bool wtwJVpsbcb = false;
      bool nTyxmDnmDL = false;
      bool mLYGQhgLPB = false;
      bool QBCCqIarIl = false;
      bool iouZajqKMo = false;
      bool qDeCekVosn = false;
      bool IhMbKmQwFe = false;
      bool cudQbxQyef = false;
      bool pWzaJNWzWG = false;
      bool llzUdBcSPn = false;
      bool SuFgMwZOZg = false;
      bool UWJMxlikRx = false;
      bool PQYzspuIma = false;
      bool TxipNuQRNN = false;
      bool nIZpkObmXq = false;
      bool SrARYCVGnV = false;
      bool AQazMXnTzB = false;
      bool UQWEJHqiNd = false;
      string paPiuFIYHY;
      string redFJMLcic;
      string hbwLqOHnqr;
      string KRhoglZOhW;
      string MCMzmoKYdZ;
      string rtPoNNeEqf;
      string yThOOZwnYW;
      string mwtMPePwYC;
      string EiKQAPCrbS;
      string HVWCXrUxjM;
      string rVzGlwADZh;
      string yheobPJQOz;
      string XDMFPRYqoW;
      string JRMLJhiDdE;
      string PySsUYphZI;
      string iEikonJsqU;
      string WIOCXfVSet;
      string fFlKiYjTkp;
      string aqRfnFiaWU;
      string XoMJgHjQUn;
      if(paPiuFIYHY == rVzGlwADZh){CWCeccRXCP = true;}
      else if(rVzGlwADZh == paPiuFIYHY){pWzaJNWzWG = true;}
      if(redFJMLcic == yheobPJQOz){EpIAsfphNS = true;}
      else if(yheobPJQOz == redFJMLcic){llzUdBcSPn = true;}
      if(hbwLqOHnqr == XDMFPRYqoW){wtwJVpsbcb = true;}
      else if(XDMFPRYqoW == hbwLqOHnqr){SuFgMwZOZg = true;}
      if(KRhoglZOhW == JRMLJhiDdE){nTyxmDnmDL = true;}
      else if(JRMLJhiDdE == KRhoglZOhW){UWJMxlikRx = true;}
      if(MCMzmoKYdZ == PySsUYphZI){mLYGQhgLPB = true;}
      else if(PySsUYphZI == MCMzmoKYdZ){PQYzspuIma = true;}
      if(rtPoNNeEqf == iEikonJsqU){QBCCqIarIl = true;}
      else if(iEikonJsqU == rtPoNNeEqf){TxipNuQRNN = true;}
      if(yThOOZwnYW == WIOCXfVSet){iouZajqKMo = true;}
      else if(WIOCXfVSet == yThOOZwnYW){nIZpkObmXq = true;}
      if(mwtMPePwYC == fFlKiYjTkp){qDeCekVosn = true;}
      if(EiKQAPCrbS == aqRfnFiaWU){IhMbKmQwFe = true;}
      if(HVWCXrUxjM == XoMJgHjQUn){cudQbxQyef = true;}
      while(fFlKiYjTkp == mwtMPePwYC){SrARYCVGnV = true;}
      while(aqRfnFiaWU == aqRfnFiaWU){AQazMXnTzB = true;}
      while(XoMJgHjQUn == XoMJgHjQUn){UQWEJHqiNd = true;}
      if(CWCeccRXCP == true){CWCeccRXCP = false;}
      if(EpIAsfphNS == true){EpIAsfphNS = false;}
      if(wtwJVpsbcb == true){wtwJVpsbcb = false;}
      if(nTyxmDnmDL == true){nTyxmDnmDL = false;}
      if(mLYGQhgLPB == true){mLYGQhgLPB = false;}
      if(QBCCqIarIl == true){QBCCqIarIl = false;}
      if(iouZajqKMo == true){iouZajqKMo = false;}
      if(qDeCekVosn == true){qDeCekVosn = false;}
      if(IhMbKmQwFe == true){IhMbKmQwFe = false;}
      if(cudQbxQyef == true){cudQbxQyef = false;}
      if(pWzaJNWzWG == true){pWzaJNWzWG = false;}
      if(llzUdBcSPn == true){llzUdBcSPn = false;}
      if(SuFgMwZOZg == true){SuFgMwZOZg = false;}
      if(UWJMxlikRx == true){UWJMxlikRx = false;}
      if(PQYzspuIma == true){PQYzspuIma = false;}
      if(TxipNuQRNN == true){TxipNuQRNN = false;}
      if(nIZpkObmXq == true){nIZpkObmXq = false;}
      if(SrARYCVGnV == true){SrARYCVGnV = false;}
      if(AQazMXnTzB == true){AQazMXnTzB = false;}
      if(UQWEJHqiNd == true){UQWEJHqiNd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MLBUKNKGMH
{ 
  void XNRwlquncB()
  { 
      bool YWdMljPBrC = false;
      bool ukPMuJchFx = false;
      bool sToTVFpAKc = false;
      bool RkwWVYMUxi = false;
      bool bmHnUYrkTe = false;
      bool XZalrEhJpf = false;
      bool tPqPjJnsqV = false;
      bool wIkWUGMAzw = false;
      bool MEfeFrJKdQ = false;
      bool qCdQnMuqEK = false;
      bool kztxhPnEQl = false;
      bool rgKsToiLKr = false;
      bool AcOZetdUhI = false;
      bool KUwoLMKhxp = false;
      bool DFsqXJrjwz = false;
      bool cjgMKHkTRn = false;
      bool kTWIbWjUhH = false;
      bool dBOUntjWBV = false;
      bool CsYhfZmjeD = false;
      bool aqPIEiijPB = false;
      string DCjPGcHHFk;
      string UiETfudZtK;
      string qzcrpDDRoZ;
      string BypRxItzBS;
      string FTTuycHWSr;
      string hHZUiEYrZC;
      string ZpSeiWrmVX;
      string BdXaFWehsM;
      string ugzxqtXUis;
      string jBZzrOAoLa;
      string jUAtpDizPL;
      string YpyMGsqVmo;
      string yXDcnzEYhp;
      string WpWScafEGn;
      string KYFXUsDNrz;
      string WeBWbMQXGq;
      string zJQYnhTfjf;
      string NmOzdZRfIt;
      string wpgiSqozpP;
      string JIxOnAHgil;
      if(DCjPGcHHFk == jUAtpDizPL){YWdMljPBrC = true;}
      else if(jUAtpDizPL == DCjPGcHHFk){kztxhPnEQl = true;}
      if(UiETfudZtK == YpyMGsqVmo){ukPMuJchFx = true;}
      else if(YpyMGsqVmo == UiETfudZtK){rgKsToiLKr = true;}
      if(qzcrpDDRoZ == yXDcnzEYhp){sToTVFpAKc = true;}
      else if(yXDcnzEYhp == qzcrpDDRoZ){AcOZetdUhI = true;}
      if(BypRxItzBS == WpWScafEGn){RkwWVYMUxi = true;}
      else if(WpWScafEGn == BypRxItzBS){KUwoLMKhxp = true;}
      if(FTTuycHWSr == KYFXUsDNrz){bmHnUYrkTe = true;}
      else if(KYFXUsDNrz == FTTuycHWSr){DFsqXJrjwz = true;}
      if(hHZUiEYrZC == WeBWbMQXGq){XZalrEhJpf = true;}
      else if(WeBWbMQXGq == hHZUiEYrZC){cjgMKHkTRn = true;}
      if(ZpSeiWrmVX == zJQYnhTfjf){tPqPjJnsqV = true;}
      else if(zJQYnhTfjf == ZpSeiWrmVX){kTWIbWjUhH = true;}
      if(BdXaFWehsM == NmOzdZRfIt){wIkWUGMAzw = true;}
      if(ugzxqtXUis == wpgiSqozpP){MEfeFrJKdQ = true;}
      if(jBZzrOAoLa == JIxOnAHgil){qCdQnMuqEK = true;}
      while(NmOzdZRfIt == BdXaFWehsM){dBOUntjWBV = true;}
      while(wpgiSqozpP == wpgiSqozpP){CsYhfZmjeD = true;}
      while(JIxOnAHgil == JIxOnAHgil){aqPIEiijPB = true;}
      if(YWdMljPBrC == true){YWdMljPBrC = false;}
      if(ukPMuJchFx == true){ukPMuJchFx = false;}
      if(sToTVFpAKc == true){sToTVFpAKc = false;}
      if(RkwWVYMUxi == true){RkwWVYMUxi = false;}
      if(bmHnUYrkTe == true){bmHnUYrkTe = false;}
      if(XZalrEhJpf == true){XZalrEhJpf = false;}
      if(tPqPjJnsqV == true){tPqPjJnsqV = false;}
      if(wIkWUGMAzw == true){wIkWUGMAzw = false;}
      if(MEfeFrJKdQ == true){MEfeFrJKdQ = false;}
      if(qCdQnMuqEK == true){qCdQnMuqEK = false;}
      if(kztxhPnEQl == true){kztxhPnEQl = false;}
      if(rgKsToiLKr == true){rgKsToiLKr = false;}
      if(AcOZetdUhI == true){AcOZetdUhI = false;}
      if(KUwoLMKhxp == true){KUwoLMKhxp = false;}
      if(DFsqXJrjwz == true){DFsqXJrjwz = false;}
      if(cjgMKHkTRn == true){cjgMKHkTRn = false;}
      if(kTWIbWjUhH == true){kTWIbWjUhH = false;}
      if(dBOUntjWBV == true){dBOUntjWBV = false;}
      if(CsYhfZmjeD == true){CsYhfZmjeD = false;}
      if(aqPIEiijPB == true){aqPIEiijPB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJXZMGMJMX
{ 
  void iTxXZJLqXG()
  { 
      bool XPLNOtgyzT = false;
      bool RdaabJifPf = false;
      bool mfJOOuEkGf = false;
      bool ArahFgoCRg = false;
      bool oTZYlNKFya = false;
      bool soHXtqFxzT = false;
      bool purSTZCrUt = false;
      bool TgNhqSGjbA = false;
      bool kymemLkDmN = false;
      bool arCyqsaGFM = false;
      bool KRjDGMbYgb = false;
      bool kUUyiqINfI = false;
      bool ozEHSbdPqx = false;
      bool qzePpSOiXZ = false;
      bool iLWLcGWEOA = false;
      bool kNZxWLMcje = false;
      bool iLhijkpEIP = false;
      bool bYoGYcbseM = false;
      bool EYApLcYgsd = false;
      bool GlzsqXdmbq = false;
      string clhPBKGrUI;
      string hSKEMBLrWe;
      string MgUMIyblxx;
      string KAXCxkdrfn;
      string VwyrdICCnK;
      string KxZIfwRVGD;
      string iUuXyguHGa;
      string WSMiIPhchA;
      string uYyllMaPWB;
      string SHlbFBBZtx;
      string NtwMnqjqzQ;
      string NonGHJVJkk;
      string GfkEHPgkcH;
      string OHhjlBckyt;
      string biPFndSfUu;
      string eroIqhJqEX;
      string KzNrCFGDTG;
      string fkLpIWPeQd;
      string wBQgbVSZsE;
      string rkfZjcVXDh;
      if(clhPBKGrUI == NtwMnqjqzQ){XPLNOtgyzT = true;}
      else if(NtwMnqjqzQ == clhPBKGrUI){KRjDGMbYgb = true;}
      if(hSKEMBLrWe == NonGHJVJkk){RdaabJifPf = true;}
      else if(NonGHJVJkk == hSKEMBLrWe){kUUyiqINfI = true;}
      if(MgUMIyblxx == GfkEHPgkcH){mfJOOuEkGf = true;}
      else if(GfkEHPgkcH == MgUMIyblxx){ozEHSbdPqx = true;}
      if(KAXCxkdrfn == OHhjlBckyt){ArahFgoCRg = true;}
      else if(OHhjlBckyt == KAXCxkdrfn){qzePpSOiXZ = true;}
      if(VwyrdICCnK == biPFndSfUu){oTZYlNKFya = true;}
      else if(biPFndSfUu == VwyrdICCnK){iLWLcGWEOA = true;}
      if(KxZIfwRVGD == eroIqhJqEX){soHXtqFxzT = true;}
      else if(eroIqhJqEX == KxZIfwRVGD){kNZxWLMcje = true;}
      if(iUuXyguHGa == KzNrCFGDTG){purSTZCrUt = true;}
      else if(KzNrCFGDTG == iUuXyguHGa){iLhijkpEIP = true;}
      if(WSMiIPhchA == fkLpIWPeQd){TgNhqSGjbA = true;}
      if(uYyllMaPWB == wBQgbVSZsE){kymemLkDmN = true;}
      if(SHlbFBBZtx == rkfZjcVXDh){arCyqsaGFM = true;}
      while(fkLpIWPeQd == WSMiIPhchA){bYoGYcbseM = true;}
      while(wBQgbVSZsE == wBQgbVSZsE){EYApLcYgsd = true;}
      while(rkfZjcVXDh == rkfZjcVXDh){GlzsqXdmbq = true;}
      if(XPLNOtgyzT == true){XPLNOtgyzT = false;}
      if(RdaabJifPf == true){RdaabJifPf = false;}
      if(mfJOOuEkGf == true){mfJOOuEkGf = false;}
      if(ArahFgoCRg == true){ArahFgoCRg = false;}
      if(oTZYlNKFya == true){oTZYlNKFya = false;}
      if(soHXtqFxzT == true){soHXtqFxzT = false;}
      if(purSTZCrUt == true){purSTZCrUt = false;}
      if(TgNhqSGjbA == true){TgNhqSGjbA = false;}
      if(kymemLkDmN == true){kymemLkDmN = false;}
      if(arCyqsaGFM == true){arCyqsaGFM = false;}
      if(KRjDGMbYgb == true){KRjDGMbYgb = false;}
      if(kUUyiqINfI == true){kUUyiqINfI = false;}
      if(ozEHSbdPqx == true){ozEHSbdPqx = false;}
      if(qzePpSOiXZ == true){qzePpSOiXZ = false;}
      if(iLWLcGWEOA == true){iLWLcGWEOA = false;}
      if(kNZxWLMcje == true){kNZxWLMcje = false;}
      if(iLhijkpEIP == true){iLhijkpEIP = false;}
      if(bYoGYcbseM == true){bYoGYcbseM = false;}
      if(EYApLcYgsd == true){EYApLcYgsd = false;}
      if(GlzsqXdmbq == true){GlzsqXdmbq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQTKFENDFS
{ 
  void srxYUVFYVM()
  { 
      bool lKcLlxXIbn = false;
      bool BDgtZqLGkQ = false;
      bool ukEXtEmKWW = false;
      bool IVfKPdzGoq = false;
      bool lSnHzfByEy = false;
      bool WMhxNBGFRg = false;
      bool KNkFeeXWdw = false;
      bool rFRtecwxXN = false;
      bool CnGYzwmhxO = false;
      bool XsnHgXgibU = false;
      bool IeUHFRunSk = false;
      bool FIgDeVGMFi = false;
      bool qoYPYyQJMG = false;
      bool wMUDFXTySh = false;
      bool AzPMIOLkcL = false;
      bool RTdscSFEiH = false;
      bool BlaLosndxH = false;
      bool BIsXhrYMHJ = false;
      bool lefBobhbZm = false;
      bool RPPLfOXEWO = false;
      string VMlGwgCthC;
      string jcgCUQxgyX;
      string NMMSVVbAzC;
      string nSDIGnqBZB;
      string DrXOLCGtUo;
      string tqgOTIzSjZ;
      string ECteOQZXuf;
      string YuGxUVoyGT;
      string PheKIwlnnx;
      string oXRzwBxrzt;
      string bhynPyjjty;
      string SAMPKWWjWR;
      string ekjyqAdGBS;
      string XwyLqgiptJ;
      string LCtoenLBoY;
      string dNVhPqyAxP;
      string TciaaVBAXc;
      string mfoMFbptSC;
      string ocRboJaQuA;
      string iiseoiTTOI;
      if(VMlGwgCthC == bhynPyjjty){lKcLlxXIbn = true;}
      else if(bhynPyjjty == VMlGwgCthC){IeUHFRunSk = true;}
      if(jcgCUQxgyX == SAMPKWWjWR){BDgtZqLGkQ = true;}
      else if(SAMPKWWjWR == jcgCUQxgyX){FIgDeVGMFi = true;}
      if(NMMSVVbAzC == ekjyqAdGBS){ukEXtEmKWW = true;}
      else if(ekjyqAdGBS == NMMSVVbAzC){qoYPYyQJMG = true;}
      if(nSDIGnqBZB == XwyLqgiptJ){IVfKPdzGoq = true;}
      else if(XwyLqgiptJ == nSDIGnqBZB){wMUDFXTySh = true;}
      if(DrXOLCGtUo == LCtoenLBoY){lSnHzfByEy = true;}
      else if(LCtoenLBoY == DrXOLCGtUo){AzPMIOLkcL = true;}
      if(tqgOTIzSjZ == dNVhPqyAxP){WMhxNBGFRg = true;}
      else if(dNVhPqyAxP == tqgOTIzSjZ){RTdscSFEiH = true;}
      if(ECteOQZXuf == TciaaVBAXc){KNkFeeXWdw = true;}
      else if(TciaaVBAXc == ECteOQZXuf){BlaLosndxH = true;}
      if(YuGxUVoyGT == mfoMFbptSC){rFRtecwxXN = true;}
      if(PheKIwlnnx == ocRboJaQuA){CnGYzwmhxO = true;}
      if(oXRzwBxrzt == iiseoiTTOI){XsnHgXgibU = true;}
      while(mfoMFbptSC == YuGxUVoyGT){BIsXhrYMHJ = true;}
      while(ocRboJaQuA == ocRboJaQuA){lefBobhbZm = true;}
      while(iiseoiTTOI == iiseoiTTOI){RPPLfOXEWO = true;}
      if(lKcLlxXIbn == true){lKcLlxXIbn = false;}
      if(BDgtZqLGkQ == true){BDgtZqLGkQ = false;}
      if(ukEXtEmKWW == true){ukEXtEmKWW = false;}
      if(IVfKPdzGoq == true){IVfKPdzGoq = false;}
      if(lSnHzfByEy == true){lSnHzfByEy = false;}
      if(WMhxNBGFRg == true){WMhxNBGFRg = false;}
      if(KNkFeeXWdw == true){KNkFeeXWdw = false;}
      if(rFRtecwxXN == true){rFRtecwxXN = false;}
      if(CnGYzwmhxO == true){CnGYzwmhxO = false;}
      if(XsnHgXgibU == true){XsnHgXgibU = false;}
      if(IeUHFRunSk == true){IeUHFRunSk = false;}
      if(FIgDeVGMFi == true){FIgDeVGMFi = false;}
      if(qoYPYyQJMG == true){qoYPYyQJMG = false;}
      if(wMUDFXTySh == true){wMUDFXTySh = false;}
      if(AzPMIOLkcL == true){AzPMIOLkcL = false;}
      if(RTdscSFEiH == true){RTdscSFEiH = false;}
      if(BlaLosndxH == true){BlaLosndxH = false;}
      if(BIsXhrYMHJ == true){BIsXhrYMHJ = false;}
      if(lefBobhbZm == true){lefBobhbZm = false;}
      if(RPPLfOXEWO == true){RPPLfOXEWO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POBHTZFCPI
{ 
  void TXXkLPCMye()
  { 
      bool ezMBfqUltV = false;
      bool HRoJYsOAXx = false;
      bool dMeFlakKCu = false;
      bool ilCUOsXrAC = false;
      bool RlMVQEFmMm = false;
      bool etqgTRTGPE = false;
      bool GJjymUPUue = false;
      bool UVzUfrAJog = false;
      bool VyxPQntUBw = false;
      bool ZRcwwHCNhu = false;
      bool okqgRItVBb = false;
      bool QKQiiHMThy = false;
      bool atSzFDsDYY = false;
      bool omatqjGPxH = false;
      bool sXTYeOAsNn = false;
      bool uhejTuRrbO = false;
      bool PqxbldiWqy = false;
      bool AwWaECatTp = false;
      bool CzojdHIqZw = false;
      bool ROniqCZqmB = false;
      string goMyIbbCxh;
      string QiORwqEdpO;
      string dcIBQMWxPp;
      string XSgOBrtfjf;
      string mGUmEsurAd;
      string cGZNLEgKgu;
      string EemGJyCzQE;
      string xYsKbXHUxX;
      string RewkNQrSDx;
      string KiyobHTNdF;
      string qubwgDNPln;
      string wLNJdZhBss;
      string GiwTsOZEiT;
      string EsqqfVDAEJ;
      string DbgOAzVoKC;
      string ZRUjzIzIDR;
      string dIgRjCTWcI;
      string VhxipdBgSs;
      string sjtgtlYGqX;
      string WuwlftuPex;
      if(goMyIbbCxh == qubwgDNPln){ezMBfqUltV = true;}
      else if(qubwgDNPln == goMyIbbCxh){okqgRItVBb = true;}
      if(QiORwqEdpO == wLNJdZhBss){HRoJYsOAXx = true;}
      else if(wLNJdZhBss == QiORwqEdpO){QKQiiHMThy = true;}
      if(dcIBQMWxPp == GiwTsOZEiT){dMeFlakKCu = true;}
      else if(GiwTsOZEiT == dcIBQMWxPp){atSzFDsDYY = true;}
      if(XSgOBrtfjf == EsqqfVDAEJ){ilCUOsXrAC = true;}
      else if(EsqqfVDAEJ == XSgOBrtfjf){omatqjGPxH = true;}
      if(mGUmEsurAd == DbgOAzVoKC){RlMVQEFmMm = true;}
      else if(DbgOAzVoKC == mGUmEsurAd){sXTYeOAsNn = true;}
      if(cGZNLEgKgu == ZRUjzIzIDR){etqgTRTGPE = true;}
      else if(ZRUjzIzIDR == cGZNLEgKgu){uhejTuRrbO = true;}
      if(EemGJyCzQE == dIgRjCTWcI){GJjymUPUue = true;}
      else if(dIgRjCTWcI == EemGJyCzQE){PqxbldiWqy = true;}
      if(xYsKbXHUxX == VhxipdBgSs){UVzUfrAJog = true;}
      if(RewkNQrSDx == sjtgtlYGqX){VyxPQntUBw = true;}
      if(KiyobHTNdF == WuwlftuPex){ZRcwwHCNhu = true;}
      while(VhxipdBgSs == xYsKbXHUxX){AwWaECatTp = true;}
      while(sjtgtlYGqX == sjtgtlYGqX){CzojdHIqZw = true;}
      while(WuwlftuPex == WuwlftuPex){ROniqCZqmB = true;}
      if(ezMBfqUltV == true){ezMBfqUltV = false;}
      if(HRoJYsOAXx == true){HRoJYsOAXx = false;}
      if(dMeFlakKCu == true){dMeFlakKCu = false;}
      if(ilCUOsXrAC == true){ilCUOsXrAC = false;}
      if(RlMVQEFmMm == true){RlMVQEFmMm = false;}
      if(etqgTRTGPE == true){etqgTRTGPE = false;}
      if(GJjymUPUue == true){GJjymUPUue = false;}
      if(UVzUfrAJog == true){UVzUfrAJog = false;}
      if(VyxPQntUBw == true){VyxPQntUBw = false;}
      if(ZRcwwHCNhu == true){ZRcwwHCNhu = false;}
      if(okqgRItVBb == true){okqgRItVBb = false;}
      if(QKQiiHMThy == true){QKQiiHMThy = false;}
      if(atSzFDsDYY == true){atSzFDsDYY = false;}
      if(omatqjGPxH == true){omatqjGPxH = false;}
      if(sXTYeOAsNn == true){sXTYeOAsNn = false;}
      if(uhejTuRrbO == true){uhejTuRrbO = false;}
      if(PqxbldiWqy == true){PqxbldiWqy = false;}
      if(AwWaECatTp == true){AwWaECatTp = false;}
      if(CzojdHIqZw == true){CzojdHIqZw = false;}
      if(ROniqCZqmB == true){ROniqCZqmB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUDIAZONMB
{ 
  void BBlChxOwkC()
  { 
      bool MbWjBykafW = false;
      bool jhcucuYJCF = false;
      bool eDEjkHrLCD = false;
      bool hjtdzKaaUT = false;
      bool iOWDhQjfQK = false;
      bool rZEBKIXmzt = false;
      bool GYYcnzmywS = false;
      bool TxniWQfBCT = false;
      bool WMuqLIerTp = false;
      bool lnbaMJptOh = false;
      bool dljyptkVes = false;
      bool cWjfWsdgRf = false;
      bool TteFffVNVM = false;
      bool ZllTpkbwAQ = false;
      bool WJNZNPDwDS = false;
      bool fIbhNiGdSK = false;
      bool XXzRTpjPol = false;
      bool QgfAIKgFrP = false;
      bool bZJCfRJEGH = false;
      bool dydpsyJuGW = false;
      string nWFawQnJol;
      string jwWGaVtaMw;
      string KbjbpZAQYT;
      string yMsUSQbEIR;
      string qrLJrzWOwD;
      string FhVKCLlckV;
      string PWkVmWDCmJ;
      string spRuFRPajp;
      string DlUUOQphRH;
      string ezTlBUHpWU;
      string wUblKPPaFj;
      string uLsuSdCQGV;
      string gUjeetWetj;
      string KZEOsiJhKy;
      string BPchLTGYTW;
      string SqiAnbjwGQ;
      string sjgUZVGdBi;
      string UTFIUQrCTL;
      string mxLWRTpDZR;
      string yMatFQiHHp;
      if(nWFawQnJol == wUblKPPaFj){MbWjBykafW = true;}
      else if(wUblKPPaFj == nWFawQnJol){dljyptkVes = true;}
      if(jwWGaVtaMw == uLsuSdCQGV){jhcucuYJCF = true;}
      else if(uLsuSdCQGV == jwWGaVtaMw){cWjfWsdgRf = true;}
      if(KbjbpZAQYT == gUjeetWetj){eDEjkHrLCD = true;}
      else if(gUjeetWetj == KbjbpZAQYT){TteFffVNVM = true;}
      if(yMsUSQbEIR == KZEOsiJhKy){hjtdzKaaUT = true;}
      else if(KZEOsiJhKy == yMsUSQbEIR){ZllTpkbwAQ = true;}
      if(qrLJrzWOwD == BPchLTGYTW){iOWDhQjfQK = true;}
      else if(BPchLTGYTW == qrLJrzWOwD){WJNZNPDwDS = true;}
      if(FhVKCLlckV == SqiAnbjwGQ){rZEBKIXmzt = true;}
      else if(SqiAnbjwGQ == FhVKCLlckV){fIbhNiGdSK = true;}
      if(PWkVmWDCmJ == sjgUZVGdBi){GYYcnzmywS = true;}
      else if(sjgUZVGdBi == PWkVmWDCmJ){XXzRTpjPol = true;}
      if(spRuFRPajp == UTFIUQrCTL){TxniWQfBCT = true;}
      if(DlUUOQphRH == mxLWRTpDZR){WMuqLIerTp = true;}
      if(ezTlBUHpWU == yMatFQiHHp){lnbaMJptOh = true;}
      while(UTFIUQrCTL == spRuFRPajp){QgfAIKgFrP = true;}
      while(mxLWRTpDZR == mxLWRTpDZR){bZJCfRJEGH = true;}
      while(yMatFQiHHp == yMatFQiHHp){dydpsyJuGW = true;}
      if(MbWjBykafW == true){MbWjBykafW = false;}
      if(jhcucuYJCF == true){jhcucuYJCF = false;}
      if(eDEjkHrLCD == true){eDEjkHrLCD = false;}
      if(hjtdzKaaUT == true){hjtdzKaaUT = false;}
      if(iOWDhQjfQK == true){iOWDhQjfQK = false;}
      if(rZEBKIXmzt == true){rZEBKIXmzt = false;}
      if(GYYcnzmywS == true){GYYcnzmywS = false;}
      if(TxniWQfBCT == true){TxniWQfBCT = false;}
      if(WMuqLIerTp == true){WMuqLIerTp = false;}
      if(lnbaMJptOh == true){lnbaMJptOh = false;}
      if(dljyptkVes == true){dljyptkVes = false;}
      if(cWjfWsdgRf == true){cWjfWsdgRf = false;}
      if(TteFffVNVM == true){TteFffVNVM = false;}
      if(ZllTpkbwAQ == true){ZllTpkbwAQ = false;}
      if(WJNZNPDwDS == true){WJNZNPDwDS = false;}
      if(fIbhNiGdSK == true){fIbhNiGdSK = false;}
      if(XXzRTpjPol == true){XXzRTpjPol = false;}
      if(QgfAIKgFrP == true){QgfAIKgFrP = false;}
      if(bZJCfRJEGH == true){bZJCfRJEGH = false;}
      if(dydpsyJuGW == true){dydpsyJuGW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIEGZLVGAA
{ 
  void kgtqgSieZx()
  { 
      bool HqcHVtEcVo = false;
      bool ZPmRIjUhJD = false;
      bool LUaHYjCwNU = false;
      bool KbRBgfUELS = false;
      bool hHzVcEUimU = false;
      bool PuAMxlQVik = false;
      bool rIOBeyxkkb = false;
      bool OPWqVDVFdU = false;
      bool PTIsFOaFEt = false;
      bool PzVZaZsype = false;
      bool GjyKFzYJqs = false;
      bool QLqNVXAUuP = false;
      bool WqgpMPtwQu = false;
      bool JWOzNfUxnF = false;
      bool pQOKcEHHEC = false;
      bool ZXCaHOCHyo = false;
      bool Fbsuitwqzp = false;
      bool DCgpZGcVNH = false;
      bool IlrNVlTnrz = false;
      bool cNyyANXSai = false;
      string CsmnlpWolJ;
      string LIsleykyho;
      string HsRGRVaMGZ;
      string cWVRpKokaa;
      string TCMbCTPIMs;
      string TRREgIagWP;
      string PKiMfnlawU;
      string JzXGUEgpEx;
      string GRzMGKFRjg;
      string iHNKLJTAuN;
      string gnMriTtKic;
      string bkcZJxKVFV;
      string iUpOlClMuL;
      string kfupPRFHcm;
      string QthHExdmAN;
      string yxuZeMyxFg;
      string hgPWqwpmKr;
      string rDrSEolhKn;
      string XyMgNmjULC;
      string THBwEjdKQI;
      if(CsmnlpWolJ == gnMriTtKic){HqcHVtEcVo = true;}
      else if(gnMriTtKic == CsmnlpWolJ){GjyKFzYJqs = true;}
      if(LIsleykyho == bkcZJxKVFV){ZPmRIjUhJD = true;}
      else if(bkcZJxKVFV == LIsleykyho){QLqNVXAUuP = true;}
      if(HsRGRVaMGZ == iUpOlClMuL){LUaHYjCwNU = true;}
      else if(iUpOlClMuL == HsRGRVaMGZ){WqgpMPtwQu = true;}
      if(cWVRpKokaa == kfupPRFHcm){KbRBgfUELS = true;}
      else if(kfupPRFHcm == cWVRpKokaa){JWOzNfUxnF = true;}
      if(TCMbCTPIMs == QthHExdmAN){hHzVcEUimU = true;}
      else if(QthHExdmAN == TCMbCTPIMs){pQOKcEHHEC = true;}
      if(TRREgIagWP == yxuZeMyxFg){PuAMxlQVik = true;}
      else if(yxuZeMyxFg == TRREgIagWP){ZXCaHOCHyo = true;}
      if(PKiMfnlawU == hgPWqwpmKr){rIOBeyxkkb = true;}
      else if(hgPWqwpmKr == PKiMfnlawU){Fbsuitwqzp = true;}
      if(JzXGUEgpEx == rDrSEolhKn){OPWqVDVFdU = true;}
      if(GRzMGKFRjg == XyMgNmjULC){PTIsFOaFEt = true;}
      if(iHNKLJTAuN == THBwEjdKQI){PzVZaZsype = true;}
      while(rDrSEolhKn == JzXGUEgpEx){DCgpZGcVNH = true;}
      while(XyMgNmjULC == XyMgNmjULC){IlrNVlTnrz = true;}
      while(THBwEjdKQI == THBwEjdKQI){cNyyANXSai = true;}
      if(HqcHVtEcVo == true){HqcHVtEcVo = false;}
      if(ZPmRIjUhJD == true){ZPmRIjUhJD = false;}
      if(LUaHYjCwNU == true){LUaHYjCwNU = false;}
      if(KbRBgfUELS == true){KbRBgfUELS = false;}
      if(hHzVcEUimU == true){hHzVcEUimU = false;}
      if(PuAMxlQVik == true){PuAMxlQVik = false;}
      if(rIOBeyxkkb == true){rIOBeyxkkb = false;}
      if(OPWqVDVFdU == true){OPWqVDVFdU = false;}
      if(PTIsFOaFEt == true){PTIsFOaFEt = false;}
      if(PzVZaZsype == true){PzVZaZsype = false;}
      if(GjyKFzYJqs == true){GjyKFzYJqs = false;}
      if(QLqNVXAUuP == true){QLqNVXAUuP = false;}
      if(WqgpMPtwQu == true){WqgpMPtwQu = false;}
      if(JWOzNfUxnF == true){JWOzNfUxnF = false;}
      if(pQOKcEHHEC == true){pQOKcEHHEC = false;}
      if(ZXCaHOCHyo == true){ZXCaHOCHyo = false;}
      if(Fbsuitwqzp == true){Fbsuitwqzp = false;}
      if(DCgpZGcVNH == true){DCgpZGcVNH = false;}
      if(IlrNVlTnrz == true){IlrNVlTnrz = false;}
      if(cNyyANXSai == true){cNyyANXSai = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSCXZEPRFD
{ 
  void rxeltokcqf()
  { 
      bool ZrMKofHplQ = false;
      bool aBplLjRACi = false;
      bool qipnEiJHmm = false;
      bool zqnetlYwNE = false;
      bool hJhdSmDprY = false;
      bool VAUgzqBXFF = false;
      bool VzDzRiMKrY = false;
      bool KVmxAhBMVR = false;
      bool fTOOQyVHfC = false;
      bool jBpHihGhMi = false;
      bool ZryTNzNXfQ = false;
      bool poBnZCjnhS = false;
      bool MEeonJfeNS = false;
      bool bSAlqmVuAR = false;
      bool kybOLuzBhf = false;
      bool xRzsVUNIeE = false;
      bool ShJMoXoOwm = false;
      bool gomQhOcPcs = false;
      bool JdxgVJSGPV = false;
      bool ZMPwyCnOYn = false;
      string spPCeLTlbW;
      string sNrLwAUYWu;
      string FOWhmAHHkX;
      string kOmfriLbVD;
      string BYPmzoIjSo;
      string smokMdTgPe;
      string ELADldaLSN;
      string nrCSsfzihx;
      string qWoudxZBTN;
      string OdMqzoXLBV;
      string OxQFBAjVqf;
      string ekzRmhWFYn;
      string EYqEyKfKTE;
      string HmhMitFjtc;
      string NDKmidetEQ;
      string SSlNRoFLGp;
      string UYCmXrDlhs;
      string bmKwaAOEVU;
      string ekGCkoAUus;
      string nscDInAWPq;
      if(spPCeLTlbW == OxQFBAjVqf){ZrMKofHplQ = true;}
      else if(OxQFBAjVqf == spPCeLTlbW){ZryTNzNXfQ = true;}
      if(sNrLwAUYWu == ekzRmhWFYn){aBplLjRACi = true;}
      else if(ekzRmhWFYn == sNrLwAUYWu){poBnZCjnhS = true;}
      if(FOWhmAHHkX == EYqEyKfKTE){qipnEiJHmm = true;}
      else if(EYqEyKfKTE == FOWhmAHHkX){MEeonJfeNS = true;}
      if(kOmfriLbVD == HmhMitFjtc){zqnetlYwNE = true;}
      else if(HmhMitFjtc == kOmfriLbVD){bSAlqmVuAR = true;}
      if(BYPmzoIjSo == NDKmidetEQ){hJhdSmDprY = true;}
      else if(NDKmidetEQ == BYPmzoIjSo){kybOLuzBhf = true;}
      if(smokMdTgPe == SSlNRoFLGp){VAUgzqBXFF = true;}
      else if(SSlNRoFLGp == smokMdTgPe){xRzsVUNIeE = true;}
      if(ELADldaLSN == UYCmXrDlhs){VzDzRiMKrY = true;}
      else if(UYCmXrDlhs == ELADldaLSN){ShJMoXoOwm = true;}
      if(nrCSsfzihx == bmKwaAOEVU){KVmxAhBMVR = true;}
      if(qWoudxZBTN == ekGCkoAUus){fTOOQyVHfC = true;}
      if(OdMqzoXLBV == nscDInAWPq){jBpHihGhMi = true;}
      while(bmKwaAOEVU == nrCSsfzihx){gomQhOcPcs = true;}
      while(ekGCkoAUus == ekGCkoAUus){JdxgVJSGPV = true;}
      while(nscDInAWPq == nscDInAWPq){ZMPwyCnOYn = true;}
      if(ZrMKofHplQ == true){ZrMKofHplQ = false;}
      if(aBplLjRACi == true){aBplLjRACi = false;}
      if(qipnEiJHmm == true){qipnEiJHmm = false;}
      if(zqnetlYwNE == true){zqnetlYwNE = false;}
      if(hJhdSmDprY == true){hJhdSmDprY = false;}
      if(VAUgzqBXFF == true){VAUgzqBXFF = false;}
      if(VzDzRiMKrY == true){VzDzRiMKrY = false;}
      if(KVmxAhBMVR == true){KVmxAhBMVR = false;}
      if(fTOOQyVHfC == true){fTOOQyVHfC = false;}
      if(jBpHihGhMi == true){jBpHihGhMi = false;}
      if(ZryTNzNXfQ == true){ZryTNzNXfQ = false;}
      if(poBnZCjnhS == true){poBnZCjnhS = false;}
      if(MEeonJfeNS == true){MEeonJfeNS = false;}
      if(bSAlqmVuAR == true){bSAlqmVuAR = false;}
      if(kybOLuzBhf == true){kybOLuzBhf = false;}
      if(xRzsVUNIeE == true){xRzsVUNIeE = false;}
      if(ShJMoXoOwm == true){ShJMoXoOwm = false;}
      if(gomQhOcPcs == true){gomQhOcPcs = false;}
      if(JdxgVJSGPV == true){JdxgVJSGPV = false;}
      if(ZMPwyCnOYn == true){ZMPwyCnOYn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZNUSOUKKU
{ 
  void OMcaiPKTbz()
  { 
      bool mpPtKNKRCt = false;
      bool IKTRnmPuns = false;
      bool cMMCxdTaSc = false;
      bool MGmrNUmyOJ = false;
      bool ilXanYkNAN = false;
      bool hsyQDadNxg = false;
      bool sizYhBXaDT = false;
      bool AQfdJpnkNY = false;
      bool rGaEtSIWom = false;
      bool qYBhPzmzsl = false;
      bool AJJgNRMTGN = false;
      bool lrAYnmItdO = false;
      bool sBlQbaPyNK = false;
      bool CnrbXiwtqc = false;
      bool FoPbAzYbsc = false;
      bool prVdszXsEl = false;
      bool COFwKxzYBF = false;
      bool qODBIDkKPc = false;
      bool CmEkTKSNhX = false;
      bool LDoEZqiTRD = false;
      string LDDVJgRAFE;
      string hkMQPHjkWA;
      string LAwgdsabVq;
      string kbuNuXwEPe;
      string BKMfKkAzku;
      string ozexILGWqQ;
      string GoeNTFpyVq;
      string KeUryAnPVs;
      string raqZBkwxEj;
      string QZMzYLfyLE;
      string tBdskJdmyH;
      string WpAxXeyEMh;
      string JrskakSUSl;
      string UpDQyqxyor;
      string HIzwMZZObs;
      string NalcuCHrSz;
      string qIUMmgmiyg;
      string hzPTaAswYA;
      string LDsZXtEZVw;
      string iEfoBynlJf;
      if(LDDVJgRAFE == tBdskJdmyH){mpPtKNKRCt = true;}
      else if(tBdskJdmyH == LDDVJgRAFE){AJJgNRMTGN = true;}
      if(hkMQPHjkWA == WpAxXeyEMh){IKTRnmPuns = true;}
      else if(WpAxXeyEMh == hkMQPHjkWA){lrAYnmItdO = true;}
      if(LAwgdsabVq == JrskakSUSl){cMMCxdTaSc = true;}
      else if(JrskakSUSl == LAwgdsabVq){sBlQbaPyNK = true;}
      if(kbuNuXwEPe == UpDQyqxyor){MGmrNUmyOJ = true;}
      else if(UpDQyqxyor == kbuNuXwEPe){CnrbXiwtqc = true;}
      if(BKMfKkAzku == HIzwMZZObs){ilXanYkNAN = true;}
      else if(HIzwMZZObs == BKMfKkAzku){FoPbAzYbsc = true;}
      if(ozexILGWqQ == NalcuCHrSz){hsyQDadNxg = true;}
      else if(NalcuCHrSz == ozexILGWqQ){prVdszXsEl = true;}
      if(GoeNTFpyVq == qIUMmgmiyg){sizYhBXaDT = true;}
      else if(qIUMmgmiyg == GoeNTFpyVq){COFwKxzYBF = true;}
      if(KeUryAnPVs == hzPTaAswYA){AQfdJpnkNY = true;}
      if(raqZBkwxEj == LDsZXtEZVw){rGaEtSIWom = true;}
      if(QZMzYLfyLE == iEfoBynlJf){qYBhPzmzsl = true;}
      while(hzPTaAswYA == KeUryAnPVs){qODBIDkKPc = true;}
      while(LDsZXtEZVw == LDsZXtEZVw){CmEkTKSNhX = true;}
      while(iEfoBynlJf == iEfoBynlJf){LDoEZqiTRD = true;}
      if(mpPtKNKRCt == true){mpPtKNKRCt = false;}
      if(IKTRnmPuns == true){IKTRnmPuns = false;}
      if(cMMCxdTaSc == true){cMMCxdTaSc = false;}
      if(MGmrNUmyOJ == true){MGmrNUmyOJ = false;}
      if(ilXanYkNAN == true){ilXanYkNAN = false;}
      if(hsyQDadNxg == true){hsyQDadNxg = false;}
      if(sizYhBXaDT == true){sizYhBXaDT = false;}
      if(AQfdJpnkNY == true){AQfdJpnkNY = false;}
      if(rGaEtSIWom == true){rGaEtSIWom = false;}
      if(qYBhPzmzsl == true){qYBhPzmzsl = false;}
      if(AJJgNRMTGN == true){AJJgNRMTGN = false;}
      if(lrAYnmItdO == true){lrAYnmItdO = false;}
      if(sBlQbaPyNK == true){sBlQbaPyNK = false;}
      if(CnrbXiwtqc == true){CnrbXiwtqc = false;}
      if(FoPbAzYbsc == true){FoPbAzYbsc = false;}
      if(prVdszXsEl == true){prVdszXsEl = false;}
      if(COFwKxzYBF == true){COFwKxzYBF = false;}
      if(qODBIDkKPc == true){qODBIDkKPc = false;}
      if(CmEkTKSNhX == true){CmEkTKSNhX = false;}
      if(LDoEZqiTRD == true){LDoEZqiTRD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWPEPCRRAO
{ 
  void hwuQbKLoeQ()
  { 
      bool YsNkelQUdr = false;
      bool XrHpiXpDez = false;
      bool ryUVFlIEHw = false;
      bool iCiPhCpwoG = false;
      bool xLRwbNasaX = false;
      bool fwqPtZYqer = false;
      bool dLNgJVIqIg = false;
      bool gtOYCgfXtr = false;
      bool LPdiQmKTUH = false;
      bool dzRwckykmF = false;
      bool EijtqlgSMN = false;
      bool sAxmgOhdPV = false;
      bool KoWBChcSwR = false;
      bool huknmbejre = false;
      bool FrHGNcBdOO = false;
      bool CTUQuPMiqI = false;
      bool IOWteyPIzF = false;
      bool iykkQSgPmZ = false;
      bool fyDgPNZTsX = false;
      bool OwrjVpUMbO = false;
      string HTRWZTnDLy;
      string KTfdhYdXYH;
      string oWaxnxqJcu;
      string mpKUaAxlkq;
      string gLQWBZfaFH;
      string HpaUjjrUhc;
      string cdaPLUILDh;
      string bqmhadGEuO;
      string RPEVnxPojp;
      string HbDINDkALf;
      string QTXXePCrtG;
      string dnYTKNYFbN;
      string FTbNZzneUW;
      string sFsPxyrgpX;
      string tWtcLTDjxA;
      string deYxaxqJxf;
      string bXXXNYtJVM;
      string UrODThYzCG;
      string wEgTrNgwoA;
      string GhiKwWzWPm;
      if(HTRWZTnDLy == QTXXePCrtG){YsNkelQUdr = true;}
      else if(QTXXePCrtG == HTRWZTnDLy){EijtqlgSMN = true;}
      if(KTfdhYdXYH == dnYTKNYFbN){XrHpiXpDez = true;}
      else if(dnYTKNYFbN == KTfdhYdXYH){sAxmgOhdPV = true;}
      if(oWaxnxqJcu == FTbNZzneUW){ryUVFlIEHw = true;}
      else if(FTbNZzneUW == oWaxnxqJcu){KoWBChcSwR = true;}
      if(mpKUaAxlkq == sFsPxyrgpX){iCiPhCpwoG = true;}
      else if(sFsPxyrgpX == mpKUaAxlkq){huknmbejre = true;}
      if(gLQWBZfaFH == tWtcLTDjxA){xLRwbNasaX = true;}
      else if(tWtcLTDjxA == gLQWBZfaFH){FrHGNcBdOO = true;}
      if(HpaUjjrUhc == deYxaxqJxf){fwqPtZYqer = true;}
      else if(deYxaxqJxf == HpaUjjrUhc){CTUQuPMiqI = true;}
      if(cdaPLUILDh == bXXXNYtJVM){dLNgJVIqIg = true;}
      else if(bXXXNYtJVM == cdaPLUILDh){IOWteyPIzF = true;}
      if(bqmhadGEuO == UrODThYzCG){gtOYCgfXtr = true;}
      if(RPEVnxPojp == wEgTrNgwoA){LPdiQmKTUH = true;}
      if(HbDINDkALf == GhiKwWzWPm){dzRwckykmF = true;}
      while(UrODThYzCG == bqmhadGEuO){iykkQSgPmZ = true;}
      while(wEgTrNgwoA == wEgTrNgwoA){fyDgPNZTsX = true;}
      while(GhiKwWzWPm == GhiKwWzWPm){OwrjVpUMbO = true;}
      if(YsNkelQUdr == true){YsNkelQUdr = false;}
      if(XrHpiXpDez == true){XrHpiXpDez = false;}
      if(ryUVFlIEHw == true){ryUVFlIEHw = false;}
      if(iCiPhCpwoG == true){iCiPhCpwoG = false;}
      if(xLRwbNasaX == true){xLRwbNasaX = false;}
      if(fwqPtZYqer == true){fwqPtZYqer = false;}
      if(dLNgJVIqIg == true){dLNgJVIqIg = false;}
      if(gtOYCgfXtr == true){gtOYCgfXtr = false;}
      if(LPdiQmKTUH == true){LPdiQmKTUH = false;}
      if(dzRwckykmF == true){dzRwckykmF = false;}
      if(EijtqlgSMN == true){EijtqlgSMN = false;}
      if(sAxmgOhdPV == true){sAxmgOhdPV = false;}
      if(KoWBChcSwR == true){KoWBChcSwR = false;}
      if(huknmbejre == true){huknmbejre = false;}
      if(FrHGNcBdOO == true){FrHGNcBdOO = false;}
      if(CTUQuPMiqI == true){CTUQuPMiqI = false;}
      if(IOWteyPIzF == true){IOWteyPIzF = false;}
      if(iykkQSgPmZ == true){iykkQSgPmZ = false;}
      if(fyDgPNZTsX == true){fyDgPNZTsX = false;}
      if(OwrjVpUMbO == true){OwrjVpUMbO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJZTHUZJOZ
{ 
  void sLpVLePwTq()
  { 
      bool cSVyeBfkYw = false;
      bool adppIHyFnX = false;
      bool aSVplcshKr = false;
      bool iEQzPcuDnV = false;
      bool mZzqUKRxhK = false;
      bool bxWDUKweLC = false;
      bool IxZgNVMpae = false;
      bool MuQSjASdUa = false;
      bool KuzzPkhNdE = false;
      bool gPqkNoASdy = false;
      bool yaWDyggEST = false;
      bool qRJjqMyaQb = false;
      bool nzMVywEfEu = false;
      bool AAAWcjYwAh = false;
      bool EdtJMOGGtB = false;
      bool qYBBJyOAFC = false;
      bool cBzXTqRmHH = false;
      bool mBZhXKFCJi = false;
      bool pxlCEbyyMd = false;
      bool VYqyFDdVpV = false;
      string XyLFKwhbwS;
      string RjxsbmSoNL;
      string WBmMUZFHhm;
      string VTGBRmHPyj;
      string PVrjtGeslJ;
      string zRkPRVKykj;
      string patIxxdubo;
      string fCpcwBJDSN;
      string uLUYnDiqjw;
      string bIeOtobilw;
      string ciRxcwbHTQ;
      string MHfWndFVUt;
      string NlLeNXXbiH;
      string ZZQVkMtXwq;
      string abWSiUbHZP;
      string iFOrhpWliE;
      string YAYMqmqJlb;
      string jhZcSlPsws;
      string wQBSXTLXmu;
      string oHnqSaDKbw;
      if(XyLFKwhbwS == ciRxcwbHTQ){cSVyeBfkYw = true;}
      else if(ciRxcwbHTQ == XyLFKwhbwS){yaWDyggEST = true;}
      if(RjxsbmSoNL == MHfWndFVUt){adppIHyFnX = true;}
      else if(MHfWndFVUt == RjxsbmSoNL){qRJjqMyaQb = true;}
      if(WBmMUZFHhm == NlLeNXXbiH){aSVplcshKr = true;}
      else if(NlLeNXXbiH == WBmMUZFHhm){nzMVywEfEu = true;}
      if(VTGBRmHPyj == ZZQVkMtXwq){iEQzPcuDnV = true;}
      else if(ZZQVkMtXwq == VTGBRmHPyj){AAAWcjYwAh = true;}
      if(PVrjtGeslJ == abWSiUbHZP){mZzqUKRxhK = true;}
      else if(abWSiUbHZP == PVrjtGeslJ){EdtJMOGGtB = true;}
      if(zRkPRVKykj == iFOrhpWliE){bxWDUKweLC = true;}
      else if(iFOrhpWliE == zRkPRVKykj){qYBBJyOAFC = true;}
      if(patIxxdubo == YAYMqmqJlb){IxZgNVMpae = true;}
      else if(YAYMqmqJlb == patIxxdubo){cBzXTqRmHH = true;}
      if(fCpcwBJDSN == jhZcSlPsws){MuQSjASdUa = true;}
      if(uLUYnDiqjw == wQBSXTLXmu){KuzzPkhNdE = true;}
      if(bIeOtobilw == oHnqSaDKbw){gPqkNoASdy = true;}
      while(jhZcSlPsws == fCpcwBJDSN){mBZhXKFCJi = true;}
      while(wQBSXTLXmu == wQBSXTLXmu){pxlCEbyyMd = true;}
      while(oHnqSaDKbw == oHnqSaDKbw){VYqyFDdVpV = true;}
      if(cSVyeBfkYw == true){cSVyeBfkYw = false;}
      if(adppIHyFnX == true){adppIHyFnX = false;}
      if(aSVplcshKr == true){aSVplcshKr = false;}
      if(iEQzPcuDnV == true){iEQzPcuDnV = false;}
      if(mZzqUKRxhK == true){mZzqUKRxhK = false;}
      if(bxWDUKweLC == true){bxWDUKweLC = false;}
      if(IxZgNVMpae == true){IxZgNVMpae = false;}
      if(MuQSjASdUa == true){MuQSjASdUa = false;}
      if(KuzzPkhNdE == true){KuzzPkhNdE = false;}
      if(gPqkNoASdy == true){gPqkNoASdy = false;}
      if(yaWDyggEST == true){yaWDyggEST = false;}
      if(qRJjqMyaQb == true){qRJjqMyaQb = false;}
      if(nzMVywEfEu == true){nzMVywEfEu = false;}
      if(AAAWcjYwAh == true){AAAWcjYwAh = false;}
      if(EdtJMOGGtB == true){EdtJMOGGtB = false;}
      if(qYBBJyOAFC == true){qYBBJyOAFC = false;}
      if(cBzXTqRmHH == true){cBzXTqRmHH = false;}
      if(mBZhXKFCJi == true){mBZhXKFCJi = false;}
      if(pxlCEbyyMd == true){pxlCEbyyMd = false;}
      if(VYqyFDdVpV == true){VYqyFDdVpV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDCCVZQNZM
{ 
  void JqLBpmRnDc()
  { 
      bool ewbiNBoInJ = false;
      bool hWXyjokYCU = false;
      bool phZxDKqIpN = false;
      bool fpoxWyYgDG = false;
      bool HtgtpTlJTY = false;
      bool rGOzoxWdfC = false;
      bool KfSacrgaak = false;
      bool PDUuMuBeGi = false;
      bool YhnRUZbpIZ = false;
      bool btBAwbaFRy = false;
      bool mLhiInkSms = false;
      bool uqXwdcqBFD = false;
      bool QpRAIUCUzj = false;
      bool UuNHwMzFIg = false;
      bool oIDPdkWEWT = false;
      bool kZzNgwthZn = false;
      bool kPTCXAcPzR = false;
      bool cksYOHmCVX = false;
      bool xxyezuuAaz = false;
      bool SRfTuYoAqd = false;
      string xxpcfqFdNt;
      string KQOIPHuoeX;
      string lDrOATwErO;
      string BThRaqFMEM;
      string IlSrpJWiKE;
      string WdIkQsEacM;
      string uBlzrphwhY;
      string BijSPzjAXp;
      string wMtmqXKxBg;
      string mdjrRHATzz;
      string aaBlDnspUQ;
      string JEDlPhGyHU;
      string ektAkWyrAI;
      string zPAYPVLIjD;
      string dUckXiaybj;
      string ACMeTpfAAf;
      string oBoLQsDdWs;
      string VyNDpKHJbC;
      string uAPQIwDVEY;
      string pKHENceRTe;
      if(xxpcfqFdNt == aaBlDnspUQ){ewbiNBoInJ = true;}
      else if(aaBlDnspUQ == xxpcfqFdNt){mLhiInkSms = true;}
      if(KQOIPHuoeX == JEDlPhGyHU){hWXyjokYCU = true;}
      else if(JEDlPhGyHU == KQOIPHuoeX){uqXwdcqBFD = true;}
      if(lDrOATwErO == ektAkWyrAI){phZxDKqIpN = true;}
      else if(ektAkWyrAI == lDrOATwErO){QpRAIUCUzj = true;}
      if(BThRaqFMEM == zPAYPVLIjD){fpoxWyYgDG = true;}
      else if(zPAYPVLIjD == BThRaqFMEM){UuNHwMzFIg = true;}
      if(IlSrpJWiKE == dUckXiaybj){HtgtpTlJTY = true;}
      else if(dUckXiaybj == IlSrpJWiKE){oIDPdkWEWT = true;}
      if(WdIkQsEacM == ACMeTpfAAf){rGOzoxWdfC = true;}
      else if(ACMeTpfAAf == WdIkQsEacM){kZzNgwthZn = true;}
      if(uBlzrphwhY == oBoLQsDdWs){KfSacrgaak = true;}
      else if(oBoLQsDdWs == uBlzrphwhY){kPTCXAcPzR = true;}
      if(BijSPzjAXp == VyNDpKHJbC){PDUuMuBeGi = true;}
      if(wMtmqXKxBg == uAPQIwDVEY){YhnRUZbpIZ = true;}
      if(mdjrRHATzz == pKHENceRTe){btBAwbaFRy = true;}
      while(VyNDpKHJbC == BijSPzjAXp){cksYOHmCVX = true;}
      while(uAPQIwDVEY == uAPQIwDVEY){xxyezuuAaz = true;}
      while(pKHENceRTe == pKHENceRTe){SRfTuYoAqd = true;}
      if(ewbiNBoInJ == true){ewbiNBoInJ = false;}
      if(hWXyjokYCU == true){hWXyjokYCU = false;}
      if(phZxDKqIpN == true){phZxDKqIpN = false;}
      if(fpoxWyYgDG == true){fpoxWyYgDG = false;}
      if(HtgtpTlJTY == true){HtgtpTlJTY = false;}
      if(rGOzoxWdfC == true){rGOzoxWdfC = false;}
      if(KfSacrgaak == true){KfSacrgaak = false;}
      if(PDUuMuBeGi == true){PDUuMuBeGi = false;}
      if(YhnRUZbpIZ == true){YhnRUZbpIZ = false;}
      if(btBAwbaFRy == true){btBAwbaFRy = false;}
      if(mLhiInkSms == true){mLhiInkSms = false;}
      if(uqXwdcqBFD == true){uqXwdcqBFD = false;}
      if(QpRAIUCUzj == true){QpRAIUCUzj = false;}
      if(UuNHwMzFIg == true){UuNHwMzFIg = false;}
      if(oIDPdkWEWT == true){oIDPdkWEWT = false;}
      if(kZzNgwthZn == true){kZzNgwthZn = false;}
      if(kPTCXAcPzR == true){kPTCXAcPzR = false;}
      if(cksYOHmCVX == true){cksYOHmCVX = false;}
      if(xxyezuuAaz == true){xxyezuuAaz = false;}
      if(SRfTuYoAqd == true){SRfTuYoAqd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAGHWUMTOD
{ 
  void LOSMWsNGYp()
  { 
      bool dqpZFCRNlJ = false;
      bool hWCbpjRteX = false;
      bool nOGdftJbMV = false;
      bool BbpeFnUgMT = false;
      bool ugJTHOfZFb = false;
      bool SBTBlPjLtK = false;
      bool roAQHGfWWC = false;
      bool OkhLbHEmWQ = false;
      bool OjWkCAInso = false;
      bool DJlBaGfsLB = false;
      bool hIDDNgTHZd = false;
      bool LwocwHSPNH = false;
      bool xrdgyFyfjU = false;
      bool bLbUhFgSXU = false;
      bool fANOdGTIFT = false;
      bool nQeEDpdVEH = false;
      bool inWFCzUTup = false;
      bool azqrbxdOCq = false;
      bool kpZQfLfXRr = false;
      bool bKNPlqcIMe = false;
      string mGSTkPWNrf;
      string ODrgyZVbon;
      string AWIuWPfwbm;
      string gktVplUXzl;
      string PQXIsrhPxh;
      string OzOJXPyXwU;
      string jZkEydJWpM;
      string ExbCYizzBe;
      string hQztYgVjxZ;
      string mxbdCofSKP;
      string hKYkcQWMkn;
      string PzVRmTapfQ;
      string HZYPYHVxAj;
      string DgokxWqORH;
      string KJzJJnbJqh;
      string OplsIIkIMV;
      string uYMAjiJjTQ;
      string cMYYGyZOGj;
      string eLGRVMtuco;
      string khCwLkwyYa;
      if(mGSTkPWNrf == hKYkcQWMkn){dqpZFCRNlJ = true;}
      else if(hKYkcQWMkn == mGSTkPWNrf){hIDDNgTHZd = true;}
      if(ODrgyZVbon == PzVRmTapfQ){hWCbpjRteX = true;}
      else if(PzVRmTapfQ == ODrgyZVbon){LwocwHSPNH = true;}
      if(AWIuWPfwbm == HZYPYHVxAj){nOGdftJbMV = true;}
      else if(HZYPYHVxAj == AWIuWPfwbm){xrdgyFyfjU = true;}
      if(gktVplUXzl == DgokxWqORH){BbpeFnUgMT = true;}
      else if(DgokxWqORH == gktVplUXzl){bLbUhFgSXU = true;}
      if(PQXIsrhPxh == KJzJJnbJqh){ugJTHOfZFb = true;}
      else if(KJzJJnbJqh == PQXIsrhPxh){fANOdGTIFT = true;}
      if(OzOJXPyXwU == OplsIIkIMV){SBTBlPjLtK = true;}
      else if(OplsIIkIMV == OzOJXPyXwU){nQeEDpdVEH = true;}
      if(jZkEydJWpM == uYMAjiJjTQ){roAQHGfWWC = true;}
      else if(uYMAjiJjTQ == jZkEydJWpM){inWFCzUTup = true;}
      if(ExbCYizzBe == cMYYGyZOGj){OkhLbHEmWQ = true;}
      if(hQztYgVjxZ == eLGRVMtuco){OjWkCAInso = true;}
      if(mxbdCofSKP == khCwLkwyYa){DJlBaGfsLB = true;}
      while(cMYYGyZOGj == ExbCYizzBe){azqrbxdOCq = true;}
      while(eLGRVMtuco == eLGRVMtuco){kpZQfLfXRr = true;}
      while(khCwLkwyYa == khCwLkwyYa){bKNPlqcIMe = true;}
      if(dqpZFCRNlJ == true){dqpZFCRNlJ = false;}
      if(hWCbpjRteX == true){hWCbpjRteX = false;}
      if(nOGdftJbMV == true){nOGdftJbMV = false;}
      if(BbpeFnUgMT == true){BbpeFnUgMT = false;}
      if(ugJTHOfZFb == true){ugJTHOfZFb = false;}
      if(SBTBlPjLtK == true){SBTBlPjLtK = false;}
      if(roAQHGfWWC == true){roAQHGfWWC = false;}
      if(OkhLbHEmWQ == true){OkhLbHEmWQ = false;}
      if(OjWkCAInso == true){OjWkCAInso = false;}
      if(DJlBaGfsLB == true){DJlBaGfsLB = false;}
      if(hIDDNgTHZd == true){hIDDNgTHZd = false;}
      if(LwocwHSPNH == true){LwocwHSPNH = false;}
      if(xrdgyFyfjU == true){xrdgyFyfjU = false;}
      if(bLbUhFgSXU == true){bLbUhFgSXU = false;}
      if(fANOdGTIFT == true){fANOdGTIFT = false;}
      if(nQeEDpdVEH == true){nQeEDpdVEH = false;}
      if(inWFCzUTup == true){inWFCzUTup = false;}
      if(azqrbxdOCq == true){azqrbxdOCq = false;}
      if(kpZQfLfXRr == true){kpZQfLfXRr = false;}
      if(bKNPlqcIMe == true){bKNPlqcIMe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBYQHEBDWM
{ 
  void LaGXonnloq()
  { 
      bool zmdaEUeOIM = false;
      bool xeCiSyQVlz = false;
      bool OmiXSmZUOb = false;
      bool ZqhutrsyXA = false;
      bool bweQztDcSX = false;
      bool HweQOLDGIR = false;
      bool uKzflGwHnZ = false;
      bool FSylWRIRXX = false;
      bool jwBqUdMRfh = false;
      bool nmpGFQwydr = false;
      bool xunrSoyssx = false;
      bool DlhjgyIILI = false;
      bool tebGkRcqgF = false;
      bool VJmfanHIYf = false;
      bool eTXieCFFYG = false;
      bool ImmVyRThGA = false;
      bool LGMmasyBIr = false;
      bool qAjfcZGsbi = false;
      bool LWSZxiWRgI = false;
      bool UYBXTXHkHk = false;
      string JIuhjJbQjw;
      string BmiaTKdLcL;
      string AiKESoAKNU;
      string iGzqMxklGf;
      string AesmIaoQUB;
      string jlTsUZxqPt;
      string IRCOMumqNV;
      string YrEwKUoXwq;
      string AioMkwmGWm;
      string AtWMWibdZN;
      string mxCzcrhWhz;
      string jYuXtZbpdP;
      string IgUaVeVqZa;
      string sKxhDCgpjs;
      string OPXWCazySx;
      string GlAJFGcacy;
      string VpxGGYaMUq;
      string slGkBrIyYt;
      string eWYbUHKmcx;
      string YFMlWYRQPc;
      if(JIuhjJbQjw == mxCzcrhWhz){zmdaEUeOIM = true;}
      else if(mxCzcrhWhz == JIuhjJbQjw){xunrSoyssx = true;}
      if(BmiaTKdLcL == jYuXtZbpdP){xeCiSyQVlz = true;}
      else if(jYuXtZbpdP == BmiaTKdLcL){DlhjgyIILI = true;}
      if(AiKESoAKNU == IgUaVeVqZa){OmiXSmZUOb = true;}
      else if(IgUaVeVqZa == AiKESoAKNU){tebGkRcqgF = true;}
      if(iGzqMxklGf == sKxhDCgpjs){ZqhutrsyXA = true;}
      else if(sKxhDCgpjs == iGzqMxklGf){VJmfanHIYf = true;}
      if(AesmIaoQUB == OPXWCazySx){bweQztDcSX = true;}
      else if(OPXWCazySx == AesmIaoQUB){eTXieCFFYG = true;}
      if(jlTsUZxqPt == GlAJFGcacy){HweQOLDGIR = true;}
      else if(GlAJFGcacy == jlTsUZxqPt){ImmVyRThGA = true;}
      if(IRCOMumqNV == VpxGGYaMUq){uKzflGwHnZ = true;}
      else if(VpxGGYaMUq == IRCOMumqNV){LGMmasyBIr = true;}
      if(YrEwKUoXwq == slGkBrIyYt){FSylWRIRXX = true;}
      if(AioMkwmGWm == eWYbUHKmcx){jwBqUdMRfh = true;}
      if(AtWMWibdZN == YFMlWYRQPc){nmpGFQwydr = true;}
      while(slGkBrIyYt == YrEwKUoXwq){qAjfcZGsbi = true;}
      while(eWYbUHKmcx == eWYbUHKmcx){LWSZxiWRgI = true;}
      while(YFMlWYRQPc == YFMlWYRQPc){UYBXTXHkHk = true;}
      if(zmdaEUeOIM == true){zmdaEUeOIM = false;}
      if(xeCiSyQVlz == true){xeCiSyQVlz = false;}
      if(OmiXSmZUOb == true){OmiXSmZUOb = false;}
      if(ZqhutrsyXA == true){ZqhutrsyXA = false;}
      if(bweQztDcSX == true){bweQztDcSX = false;}
      if(HweQOLDGIR == true){HweQOLDGIR = false;}
      if(uKzflGwHnZ == true){uKzflGwHnZ = false;}
      if(FSylWRIRXX == true){FSylWRIRXX = false;}
      if(jwBqUdMRfh == true){jwBqUdMRfh = false;}
      if(nmpGFQwydr == true){nmpGFQwydr = false;}
      if(xunrSoyssx == true){xunrSoyssx = false;}
      if(DlhjgyIILI == true){DlhjgyIILI = false;}
      if(tebGkRcqgF == true){tebGkRcqgF = false;}
      if(VJmfanHIYf == true){VJmfanHIYf = false;}
      if(eTXieCFFYG == true){eTXieCFFYG = false;}
      if(ImmVyRThGA == true){ImmVyRThGA = false;}
      if(LGMmasyBIr == true){LGMmasyBIr = false;}
      if(qAjfcZGsbi == true){qAjfcZGsbi = false;}
      if(LWSZxiWRgI == true){LWSZxiWRgI = false;}
      if(UYBXTXHkHk == true){UYBXTXHkHk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEEIOJELAA
{ 
  void QOrsJucopz()
  { 
      bool UcyOpsTdim = false;
      bool crLrctOhXm = false;
      bool BJTBazzhUM = false;
      bool ZPOlXtsQtx = false;
      bool FDYQPNGooh = false;
      bool eilWhKIwmq = false;
      bool slIWNMcYTh = false;
      bool BxnZgyjDkN = false;
      bool rKrmgpdrEM = false;
      bool kwcCETtCDC = false;
      bool jgUGgguLoi = false;
      bool ZFKYyhsVoX = false;
      bool ikTHxEUkVM = false;
      bool DhAidKplFz = false;
      bool tRCVlfkDEV = false;
      bool aXMeTyNMJb = false;
      bool MKoberFbum = false;
      bool rHPocRhyUQ = false;
      bool SQgAlfUUOe = false;
      bool xcbcmjbapt = false;
      string RFbcEXKKTz;
      string DOpsgwiLam;
      string deKasSmfAX;
      string AbQRwyLRkJ;
      string AwifiyjRzJ;
      string msdPnmtAjl;
      string kdJwyayYxi;
      string jRZRlguert;
      string hUgqjGyBdJ;
      string DKhzXWmmgH;
      string zLUPYVTMcG;
      string qPIoDQxSLr;
      string cxunfYjasP;
      string tIxjuWzQRO;
      string lkXWRmCruH;
      string YTaoeCQgjz;
      string lsTNMiSYtg;
      string QfAxFqZXVr;
      string WqekpZgIEr;
      string FRgRbsRJJi;
      if(RFbcEXKKTz == zLUPYVTMcG){UcyOpsTdim = true;}
      else if(zLUPYVTMcG == RFbcEXKKTz){jgUGgguLoi = true;}
      if(DOpsgwiLam == qPIoDQxSLr){crLrctOhXm = true;}
      else if(qPIoDQxSLr == DOpsgwiLam){ZFKYyhsVoX = true;}
      if(deKasSmfAX == cxunfYjasP){BJTBazzhUM = true;}
      else if(cxunfYjasP == deKasSmfAX){ikTHxEUkVM = true;}
      if(AbQRwyLRkJ == tIxjuWzQRO){ZPOlXtsQtx = true;}
      else if(tIxjuWzQRO == AbQRwyLRkJ){DhAidKplFz = true;}
      if(AwifiyjRzJ == lkXWRmCruH){FDYQPNGooh = true;}
      else if(lkXWRmCruH == AwifiyjRzJ){tRCVlfkDEV = true;}
      if(msdPnmtAjl == YTaoeCQgjz){eilWhKIwmq = true;}
      else if(YTaoeCQgjz == msdPnmtAjl){aXMeTyNMJb = true;}
      if(kdJwyayYxi == lsTNMiSYtg){slIWNMcYTh = true;}
      else if(lsTNMiSYtg == kdJwyayYxi){MKoberFbum = true;}
      if(jRZRlguert == QfAxFqZXVr){BxnZgyjDkN = true;}
      if(hUgqjGyBdJ == WqekpZgIEr){rKrmgpdrEM = true;}
      if(DKhzXWmmgH == FRgRbsRJJi){kwcCETtCDC = true;}
      while(QfAxFqZXVr == jRZRlguert){rHPocRhyUQ = true;}
      while(WqekpZgIEr == WqekpZgIEr){SQgAlfUUOe = true;}
      while(FRgRbsRJJi == FRgRbsRJJi){xcbcmjbapt = true;}
      if(UcyOpsTdim == true){UcyOpsTdim = false;}
      if(crLrctOhXm == true){crLrctOhXm = false;}
      if(BJTBazzhUM == true){BJTBazzhUM = false;}
      if(ZPOlXtsQtx == true){ZPOlXtsQtx = false;}
      if(FDYQPNGooh == true){FDYQPNGooh = false;}
      if(eilWhKIwmq == true){eilWhKIwmq = false;}
      if(slIWNMcYTh == true){slIWNMcYTh = false;}
      if(BxnZgyjDkN == true){BxnZgyjDkN = false;}
      if(rKrmgpdrEM == true){rKrmgpdrEM = false;}
      if(kwcCETtCDC == true){kwcCETtCDC = false;}
      if(jgUGgguLoi == true){jgUGgguLoi = false;}
      if(ZFKYyhsVoX == true){ZFKYyhsVoX = false;}
      if(ikTHxEUkVM == true){ikTHxEUkVM = false;}
      if(DhAidKplFz == true){DhAidKplFz = false;}
      if(tRCVlfkDEV == true){tRCVlfkDEV = false;}
      if(aXMeTyNMJb == true){aXMeTyNMJb = false;}
      if(MKoberFbum == true){MKoberFbum = false;}
      if(rHPocRhyUQ == true){rHPocRhyUQ = false;}
      if(SQgAlfUUOe == true){SQgAlfUUOe = false;}
      if(xcbcmjbapt == true){xcbcmjbapt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEHZKIFJKH
{ 
  void NffDTBbyVc()
  { 
      bool WmoBdetWWP = false;
      bool pmAqhZKBqD = false;
      bool RqYkMpoMNK = false;
      bool jCYTRFSyHu = false;
      bool TySAyFyzFO = false;
      bool oxSnZeODnn = false;
      bool phJMemOfYc = false;
      bool HMsujSXXmH = false;
      bool qoHyUmjjtl = false;
      bool pOKTFloGVK = false;
      bool pRZbHbDXEG = false;
      bool GpQfwAZKqq = false;
      bool DdlmlrCZox = false;
      bool dRBbRYPeqr = false;
      bool iMemfAxdWF = false;
      bool LdPdGLfmpO = false;
      bool ZdhHconoOX = false;
      bool juTyIqyzGl = false;
      bool uYCjkABXUF = false;
      bool sbobSFdXJp = false;
      string PHppRsQoeM;
      string qxIwoWjOKG;
      string MncCpgaUMg;
      string NseppnUfwl;
      string IouCSIAKZz;
      string HjPABbemzk;
      string RwcxzyRRGB;
      string CDSYxWsZih;
      string fQtMZccdoO;
      string IggLTMMxDU;
      string phEXxDRqCd;
      string iEEREBBQXV;
      string VncqrVWGEk;
      string KuWOqyLVPV;
      string KlaLeEcPHS;
      string KwZgyCFMfa;
      string gKmRSmgoZF;
      string ofBCKiMRLn;
      string sHzkaOVpPn;
      string szpnnAzJrr;
      if(PHppRsQoeM == phEXxDRqCd){WmoBdetWWP = true;}
      else if(phEXxDRqCd == PHppRsQoeM){pRZbHbDXEG = true;}
      if(qxIwoWjOKG == iEEREBBQXV){pmAqhZKBqD = true;}
      else if(iEEREBBQXV == qxIwoWjOKG){GpQfwAZKqq = true;}
      if(MncCpgaUMg == VncqrVWGEk){RqYkMpoMNK = true;}
      else if(VncqrVWGEk == MncCpgaUMg){DdlmlrCZox = true;}
      if(NseppnUfwl == KuWOqyLVPV){jCYTRFSyHu = true;}
      else if(KuWOqyLVPV == NseppnUfwl){dRBbRYPeqr = true;}
      if(IouCSIAKZz == KlaLeEcPHS){TySAyFyzFO = true;}
      else if(KlaLeEcPHS == IouCSIAKZz){iMemfAxdWF = true;}
      if(HjPABbemzk == KwZgyCFMfa){oxSnZeODnn = true;}
      else if(KwZgyCFMfa == HjPABbemzk){LdPdGLfmpO = true;}
      if(RwcxzyRRGB == gKmRSmgoZF){phJMemOfYc = true;}
      else if(gKmRSmgoZF == RwcxzyRRGB){ZdhHconoOX = true;}
      if(CDSYxWsZih == ofBCKiMRLn){HMsujSXXmH = true;}
      if(fQtMZccdoO == sHzkaOVpPn){qoHyUmjjtl = true;}
      if(IggLTMMxDU == szpnnAzJrr){pOKTFloGVK = true;}
      while(ofBCKiMRLn == CDSYxWsZih){juTyIqyzGl = true;}
      while(sHzkaOVpPn == sHzkaOVpPn){uYCjkABXUF = true;}
      while(szpnnAzJrr == szpnnAzJrr){sbobSFdXJp = true;}
      if(WmoBdetWWP == true){WmoBdetWWP = false;}
      if(pmAqhZKBqD == true){pmAqhZKBqD = false;}
      if(RqYkMpoMNK == true){RqYkMpoMNK = false;}
      if(jCYTRFSyHu == true){jCYTRFSyHu = false;}
      if(TySAyFyzFO == true){TySAyFyzFO = false;}
      if(oxSnZeODnn == true){oxSnZeODnn = false;}
      if(phJMemOfYc == true){phJMemOfYc = false;}
      if(HMsujSXXmH == true){HMsujSXXmH = false;}
      if(qoHyUmjjtl == true){qoHyUmjjtl = false;}
      if(pOKTFloGVK == true){pOKTFloGVK = false;}
      if(pRZbHbDXEG == true){pRZbHbDXEG = false;}
      if(GpQfwAZKqq == true){GpQfwAZKqq = false;}
      if(DdlmlrCZox == true){DdlmlrCZox = false;}
      if(dRBbRYPeqr == true){dRBbRYPeqr = false;}
      if(iMemfAxdWF == true){iMemfAxdWF = false;}
      if(LdPdGLfmpO == true){LdPdGLfmpO = false;}
      if(ZdhHconoOX == true){ZdhHconoOX = false;}
      if(juTyIqyzGl == true){juTyIqyzGl = false;}
      if(uYCjkABXUF == true){uYCjkABXUF = false;}
      if(sbobSFdXJp == true){sbobSFdXJp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGNAEUEVFR
{ 
  void raddOyxIpJ()
  { 
      bool RPbhgykUCw = false;
      bool oSkQxhgXrh = false;
      bool PjAPsSxRfn = false;
      bool NBXeGLrezp = false;
      bool SfaBTDdIPJ = false;
      bool cnHCCgOLoO = false;
      bool AToNhntFKl = false;
      bool oBYCOiJzup = false;
      bool ooBWLYtVbZ = false;
      bool wfpjozqMSf = false;
      bool IXxcTbPEnT = false;
      bool WPQyZLRRCI = false;
      bool sYckpJKnMP = false;
      bool qwfOhQqXCi = false;
      bool JohICgOqJd = false;
      bool gYJKmiuMmJ = false;
      bool QbrXbZiCQJ = false;
      bool UsPTzEqThJ = false;
      bool tSdihSmUby = false;
      bool VdkrRgxJgb = false;
      string whExxpPDKJ;
      string LaEcdBTHUI;
      string IlFEybAZjf;
      string sEXrDBfYhh;
      string tDkVVZUnTi;
      string RgmCNKcAyV;
      string opTdQHCLZb;
      string UuYmNFAjhX;
      string HLFAOMQUes;
      string YfaMrEjHEN;
      string XIOrNVHzoH;
      string JsRZOdjSPD;
      string qgfgDoUMuI;
      string VseTAywNmr;
      string FQfWifNAyO;
      string UQrBWpbhnY;
      string BuEflQNyYP;
      string gWfWyaBIxX;
      string aTNgnEBdxJ;
      string VOYNqJMzkR;
      if(whExxpPDKJ == XIOrNVHzoH){RPbhgykUCw = true;}
      else if(XIOrNVHzoH == whExxpPDKJ){IXxcTbPEnT = true;}
      if(LaEcdBTHUI == JsRZOdjSPD){oSkQxhgXrh = true;}
      else if(JsRZOdjSPD == LaEcdBTHUI){WPQyZLRRCI = true;}
      if(IlFEybAZjf == qgfgDoUMuI){PjAPsSxRfn = true;}
      else if(qgfgDoUMuI == IlFEybAZjf){sYckpJKnMP = true;}
      if(sEXrDBfYhh == VseTAywNmr){NBXeGLrezp = true;}
      else if(VseTAywNmr == sEXrDBfYhh){qwfOhQqXCi = true;}
      if(tDkVVZUnTi == FQfWifNAyO){SfaBTDdIPJ = true;}
      else if(FQfWifNAyO == tDkVVZUnTi){JohICgOqJd = true;}
      if(RgmCNKcAyV == UQrBWpbhnY){cnHCCgOLoO = true;}
      else if(UQrBWpbhnY == RgmCNKcAyV){gYJKmiuMmJ = true;}
      if(opTdQHCLZb == BuEflQNyYP){AToNhntFKl = true;}
      else if(BuEflQNyYP == opTdQHCLZb){QbrXbZiCQJ = true;}
      if(UuYmNFAjhX == gWfWyaBIxX){oBYCOiJzup = true;}
      if(HLFAOMQUes == aTNgnEBdxJ){ooBWLYtVbZ = true;}
      if(YfaMrEjHEN == VOYNqJMzkR){wfpjozqMSf = true;}
      while(gWfWyaBIxX == UuYmNFAjhX){UsPTzEqThJ = true;}
      while(aTNgnEBdxJ == aTNgnEBdxJ){tSdihSmUby = true;}
      while(VOYNqJMzkR == VOYNqJMzkR){VdkrRgxJgb = true;}
      if(RPbhgykUCw == true){RPbhgykUCw = false;}
      if(oSkQxhgXrh == true){oSkQxhgXrh = false;}
      if(PjAPsSxRfn == true){PjAPsSxRfn = false;}
      if(NBXeGLrezp == true){NBXeGLrezp = false;}
      if(SfaBTDdIPJ == true){SfaBTDdIPJ = false;}
      if(cnHCCgOLoO == true){cnHCCgOLoO = false;}
      if(AToNhntFKl == true){AToNhntFKl = false;}
      if(oBYCOiJzup == true){oBYCOiJzup = false;}
      if(ooBWLYtVbZ == true){ooBWLYtVbZ = false;}
      if(wfpjozqMSf == true){wfpjozqMSf = false;}
      if(IXxcTbPEnT == true){IXxcTbPEnT = false;}
      if(WPQyZLRRCI == true){WPQyZLRRCI = false;}
      if(sYckpJKnMP == true){sYckpJKnMP = false;}
      if(qwfOhQqXCi == true){qwfOhQqXCi = false;}
      if(JohICgOqJd == true){JohICgOqJd = false;}
      if(gYJKmiuMmJ == true){gYJKmiuMmJ = false;}
      if(QbrXbZiCQJ == true){QbrXbZiCQJ = false;}
      if(UsPTzEqThJ == true){UsPTzEqThJ = false;}
      if(tSdihSmUby == true){tSdihSmUby = false;}
      if(VdkrRgxJgb == true){VdkrRgxJgb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTZSEERWKD
{ 
  void EoxVluGsLJ()
  { 
      bool cdgHcVjoPc = false;
      bool lbHeBjzdlZ = false;
      bool eIVbdgYxYt = false;
      bool UYteuTSCQP = false;
      bool XpSUpxQEtM = false;
      bool LMjuFUHEcu = false;
      bool xmQUHMgbjh = false;
      bool QxMVCnoAlg = false;
      bool PTDMhHnyYa = false;
      bool LOYVRkZyNc = false;
      bool PnULuOzNsQ = false;
      bool eHRuedjElA = false;
      bool XhDJWCXqEQ = false;
      bool OpmIQbzqQT = false;
      bool HaFHuDwcpm = false;
      bool BVLNEgkLor = false;
      bool pIJbCoUJdD = false;
      bool ermRrxcwNS = false;
      bool GtBQPsdZDj = false;
      bool pmCXdzQcEG = false;
      string VYVPpGLFML;
      string blxKQKcffw;
      string uRcMXpZheJ;
      string hhOABKMreS;
      string ErPaKsLsAq;
      string GgPfYDwIrz;
      string gcaDcsWxJF;
      string xkBNqDCBCe;
      string efhmCBRhax;
      string ODzfkaQLxQ;
      string VNjtsVfCnV;
      string BuFNUBumBb;
      string boVMqtkVcQ;
      string lpElIQwmtf;
      string VPsFwTxkKi;
      string edKVngrXDy;
      string jJYXiKqTED;
      string FIsUFLuQPX;
      string xAKtlIfixb;
      string YYjuwLqVVk;
      if(VYVPpGLFML == VNjtsVfCnV){cdgHcVjoPc = true;}
      else if(VNjtsVfCnV == VYVPpGLFML){PnULuOzNsQ = true;}
      if(blxKQKcffw == BuFNUBumBb){lbHeBjzdlZ = true;}
      else if(BuFNUBumBb == blxKQKcffw){eHRuedjElA = true;}
      if(uRcMXpZheJ == boVMqtkVcQ){eIVbdgYxYt = true;}
      else if(boVMqtkVcQ == uRcMXpZheJ){XhDJWCXqEQ = true;}
      if(hhOABKMreS == lpElIQwmtf){UYteuTSCQP = true;}
      else if(lpElIQwmtf == hhOABKMreS){OpmIQbzqQT = true;}
      if(ErPaKsLsAq == VPsFwTxkKi){XpSUpxQEtM = true;}
      else if(VPsFwTxkKi == ErPaKsLsAq){HaFHuDwcpm = true;}
      if(GgPfYDwIrz == edKVngrXDy){LMjuFUHEcu = true;}
      else if(edKVngrXDy == GgPfYDwIrz){BVLNEgkLor = true;}
      if(gcaDcsWxJF == jJYXiKqTED){xmQUHMgbjh = true;}
      else if(jJYXiKqTED == gcaDcsWxJF){pIJbCoUJdD = true;}
      if(xkBNqDCBCe == FIsUFLuQPX){QxMVCnoAlg = true;}
      if(efhmCBRhax == xAKtlIfixb){PTDMhHnyYa = true;}
      if(ODzfkaQLxQ == YYjuwLqVVk){LOYVRkZyNc = true;}
      while(FIsUFLuQPX == xkBNqDCBCe){ermRrxcwNS = true;}
      while(xAKtlIfixb == xAKtlIfixb){GtBQPsdZDj = true;}
      while(YYjuwLqVVk == YYjuwLqVVk){pmCXdzQcEG = true;}
      if(cdgHcVjoPc == true){cdgHcVjoPc = false;}
      if(lbHeBjzdlZ == true){lbHeBjzdlZ = false;}
      if(eIVbdgYxYt == true){eIVbdgYxYt = false;}
      if(UYteuTSCQP == true){UYteuTSCQP = false;}
      if(XpSUpxQEtM == true){XpSUpxQEtM = false;}
      if(LMjuFUHEcu == true){LMjuFUHEcu = false;}
      if(xmQUHMgbjh == true){xmQUHMgbjh = false;}
      if(QxMVCnoAlg == true){QxMVCnoAlg = false;}
      if(PTDMhHnyYa == true){PTDMhHnyYa = false;}
      if(LOYVRkZyNc == true){LOYVRkZyNc = false;}
      if(PnULuOzNsQ == true){PnULuOzNsQ = false;}
      if(eHRuedjElA == true){eHRuedjElA = false;}
      if(XhDJWCXqEQ == true){XhDJWCXqEQ = false;}
      if(OpmIQbzqQT == true){OpmIQbzqQT = false;}
      if(HaFHuDwcpm == true){HaFHuDwcpm = false;}
      if(BVLNEgkLor == true){BVLNEgkLor = false;}
      if(pIJbCoUJdD == true){pIJbCoUJdD = false;}
      if(ermRrxcwNS == true){ermRrxcwNS = false;}
      if(GtBQPsdZDj == true){GtBQPsdZDj = false;}
      if(pmCXdzQcEG == true){pmCXdzQcEG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJLOESMOTG
{ 
  void KRzVbJcLqs()
  { 
      bool DakqjkOJrI = false;
      bool EALUQWunEZ = false;
      bool xmaAwJWYko = false;
      bool msXBsSNAHI = false;
      bool lurcmpxNMq = false;
      bool RsRBOPzkta = false;
      bool NpXDVLcKay = false;
      bool IugunCtyNG = false;
      bool MJLtWtaWmc = false;
      bool ScFgtuWoHb = false;
      bool MllOhWLWML = false;
      bool VBWnOEddfa = false;
      bool jGXxefoAAs = false;
      bool eFqltZWxLz = false;
      bool hEJaHRFRSp = false;
      bool QrJfqGOoiC = false;
      bool gLVTfQKktn = false;
      bool ggSgsewxoN = false;
      bool ZXhKbmwLtm = false;
      bool KhOJRWiptq = false;
      string djLeMOxfMV;
      string rVFqdHNNpm;
      string wMxKKofwNt;
      string ETdJqUOCgo;
      string BYJQjuxyBj;
      string LrdXPQlATW;
      string iBSRQYquzI;
      string sLgBlWDgZP;
      string rgtdiMpGtZ;
      string hNhJFzFqzL;
      string DByspzKbkr;
      string NFaEdBHoiE;
      string hjBZZfcWul;
      string RMgOLqhBmj;
      string BNUCMcmdeD;
      string rQIucTAYSK;
      string VmfzaBYLrm;
      string TGByCUOzMx;
      string szrqtAEkkr;
      string pJicNNgVaL;
      if(djLeMOxfMV == DByspzKbkr){DakqjkOJrI = true;}
      else if(DByspzKbkr == djLeMOxfMV){MllOhWLWML = true;}
      if(rVFqdHNNpm == NFaEdBHoiE){EALUQWunEZ = true;}
      else if(NFaEdBHoiE == rVFqdHNNpm){VBWnOEddfa = true;}
      if(wMxKKofwNt == hjBZZfcWul){xmaAwJWYko = true;}
      else if(hjBZZfcWul == wMxKKofwNt){jGXxefoAAs = true;}
      if(ETdJqUOCgo == RMgOLqhBmj){msXBsSNAHI = true;}
      else if(RMgOLqhBmj == ETdJqUOCgo){eFqltZWxLz = true;}
      if(BYJQjuxyBj == BNUCMcmdeD){lurcmpxNMq = true;}
      else if(BNUCMcmdeD == BYJQjuxyBj){hEJaHRFRSp = true;}
      if(LrdXPQlATW == rQIucTAYSK){RsRBOPzkta = true;}
      else if(rQIucTAYSK == LrdXPQlATW){QrJfqGOoiC = true;}
      if(iBSRQYquzI == VmfzaBYLrm){NpXDVLcKay = true;}
      else if(VmfzaBYLrm == iBSRQYquzI){gLVTfQKktn = true;}
      if(sLgBlWDgZP == TGByCUOzMx){IugunCtyNG = true;}
      if(rgtdiMpGtZ == szrqtAEkkr){MJLtWtaWmc = true;}
      if(hNhJFzFqzL == pJicNNgVaL){ScFgtuWoHb = true;}
      while(TGByCUOzMx == sLgBlWDgZP){ggSgsewxoN = true;}
      while(szrqtAEkkr == szrqtAEkkr){ZXhKbmwLtm = true;}
      while(pJicNNgVaL == pJicNNgVaL){KhOJRWiptq = true;}
      if(DakqjkOJrI == true){DakqjkOJrI = false;}
      if(EALUQWunEZ == true){EALUQWunEZ = false;}
      if(xmaAwJWYko == true){xmaAwJWYko = false;}
      if(msXBsSNAHI == true){msXBsSNAHI = false;}
      if(lurcmpxNMq == true){lurcmpxNMq = false;}
      if(RsRBOPzkta == true){RsRBOPzkta = false;}
      if(NpXDVLcKay == true){NpXDVLcKay = false;}
      if(IugunCtyNG == true){IugunCtyNG = false;}
      if(MJLtWtaWmc == true){MJLtWtaWmc = false;}
      if(ScFgtuWoHb == true){ScFgtuWoHb = false;}
      if(MllOhWLWML == true){MllOhWLWML = false;}
      if(VBWnOEddfa == true){VBWnOEddfa = false;}
      if(jGXxefoAAs == true){jGXxefoAAs = false;}
      if(eFqltZWxLz == true){eFqltZWxLz = false;}
      if(hEJaHRFRSp == true){hEJaHRFRSp = false;}
      if(QrJfqGOoiC == true){QrJfqGOoiC = false;}
      if(gLVTfQKktn == true){gLVTfQKktn = false;}
      if(ggSgsewxoN == true){ggSgsewxoN = false;}
      if(ZXhKbmwLtm == true){ZXhKbmwLtm = false;}
      if(KhOJRWiptq == true){KhOJRWiptq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DPYKWPDMCC
{ 
  void pHZZfQCUnJ()
  { 
      bool zExXMYFEOx = false;
      bool jnILxgbqXq = false;
      bool OdRnDXFxym = false;
      bool kEVrNxmYet = false;
      bool DGjYTlsPlS = false;
      bool MZDLHUlJTn = false;
      bool SHFaMeRPxA = false;
      bool tCLcnIssTR = false;
      bool dpLfaKAKks = false;
      bool KdEpauAJLo = false;
      bool TdRkYKNZXy = false;
      bool asoCKcuZAB = false;
      bool eHdEoQxVCr = false;
      bool HjgexzXZGP = false;
      bool xZllRRnCey = false;
      bool AZJKJMzMwH = false;
      bool MrXfqqLJFK = false;
      bool FVSjEEVrmW = false;
      bool bupDrgaWUk = false;
      bool AKdyDEBFua = false;
      string CWSbRgLKIE;
      string ytjxVlduFC;
      string qffjeNcNTg;
      string dlNAFkmzZp;
      string mrwIMwdXyr;
      string WraexWpiwD;
      string EypbaLgiqj;
      string zdUPOyiWWi;
      string jEObKkKhDi;
      string uEDVkoCUgA;
      string OtfNsrXLPy;
      string nSLMTziOQp;
      string AyfIotazdY;
      string wOpWUoYAhR;
      string NzSFubspCl;
      string GmDqzPOWYy;
      string RYhpBYcord;
      string ZhgzcBfZNM;
      string BjwqSJKyWE;
      string aCbiAoQbDV;
      if(CWSbRgLKIE == OtfNsrXLPy){zExXMYFEOx = true;}
      else if(OtfNsrXLPy == CWSbRgLKIE){TdRkYKNZXy = true;}
      if(ytjxVlduFC == nSLMTziOQp){jnILxgbqXq = true;}
      else if(nSLMTziOQp == ytjxVlduFC){asoCKcuZAB = true;}
      if(qffjeNcNTg == AyfIotazdY){OdRnDXFxym = true;}
      else if(AyfIotazdY == qffjeNcNTg){eHdEoQxVCr = true;}
      if(dlNAFkmzZp == wOpWUoYAhR){kEVrNxmYet = true;}
      else if(wOpWUoYAhR == dlNAFkmzZp){HjgexzXZGP = true;}
      if(mrwIMwdXyr == NzSFubspCl){DGjYTlsPlS = true;}
      else if(NzSFubspCl == mrwIMwdXyr){xZllRRnCey = true;}
      if(WraexWpiwD == GmDqzPOWYy){MZDLHUlJTn = true;}
      else if(GmDqzPOWYy == WraexWpiwD){AZJKJMzMwH = true;}
      if(EypbaLgiqj == RYhpBYcord){SHFaMeRPxA = true;}
      else if(RYhpBYcord == EypbaLgiqj){MrXfqqLJFK = true;}
      if(zdUPOyiWWi == ZhgzcBfZNM){tCLcnIssTR = true;}
      if(jEObKkKhDi == BjwqSJKyWE){dpLfaKAKks = true;}
      if(uEDVkoCUgA == aCbiAoQbDV){KdEpauAJLo = true;}
      while(ZhgzcBfZNM == zdUPOyiWWi){FVSjEEVrmW = true;}
      while(BjwqSJKyWE == BjwqSJKyWE){bupDrgaWUk = true;}
      while(aCbiAoQbDV == aCbiAoQbDV){AKdyDEBFua = true;}
      if(zExXMYFEOx == true){zExXMYFEOx = false;}
      if(jnILxgbqXq == true){jnILxgbqXq = false;}
      if(OdRnDXFxym == true){OdRnDXFxym = false;}
      if(kEVrNxmYet == true){kEVrNxmYet = false;}
      if(DGjYTlsPlS == true){DGjYTlsPlS = false;}
      if(MZDLHUlJTn == true){MZDLHUlJTn = false;}
      if(SHFaMeRPxA == true){SHFaMeRPxA = false;}
      if(tCLcnIssTR == true){tCLcnIssTR = false;}
      if(dpLfaKAKks == true){dpLfaKAKks = false;}
      if(KdEpauAJLo == true){KdEpauAJLo = false;}
      if(TdRkYKNZXy == true){TdRkYKNZXy = false;}
      if(asoCKcuZAB == true){asoCKcuZAB = false;}
      if(eHdEoQxVCr == true){eHdEoQxVCr = false;}
      if(HjgexzXZGP == true){HjgexzXZGP = false;}
      if(xZllRRnCey == true){xZllRRnCey = false;}
      if(AZJKJMzMwH == true){AZJKJMzMwH = false;}
      if(MrXfqqLJFK == true){MrXfqqLJFK = false;}
      if(FVSjEEVrmW == true){FVSjEEVrmW = false;}
      if(bupDrgaWUk == true){bupDrgaWUk = false;}
      if(AKdyDEBFua == true){AKdyDEBFua = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MRWVZXENAV
{ 
  void bLOQPtpBrX()
  { 
      bool QJOROIpHYh = false;
      bool eNWbYbgYJz = false;
      bool xcxutmOTrT = false;
      bool naRmFLYowj = false;
      bool FmBWsnsqpc = false;
      bool owYRmnMTXa = false;
      bool sWPFsDuiWM = false;
      bool DrcYsKaaCF = false;
      bool tXcOerCzzQ = false;
      bool zEQUphWucp = false;
      bool sJUdZwTzYc = false;
      bool MlRSgVsBaA = false;
      bool BujFMyaHiK = false;
      bool mfxLMjCznh = false;
      bool YCaWENmymT = false;
      bool oVUcnxZPQa = false;
      bool VLQNognFGx = false;
      bool TsMsayUNBz = false;
      bool LbUOVRKUXO = false;
      bool KmiMLNkNgW = false;
      string orcWBJNkDh;
      string SHKRPwbcRi;
      string iWsguNjCGd;
      string LnoipLFpxG;
      string EwxmhAUZtT;
      string WoXRERywan;
      string YKdZWdRaaE;
      string qkeKemYFzu;
      string rKIlGVQXdX;
      string MIOJhtRXQD;
      string hsypclKMmR;
      string srxfuOBrSB;
      string MtwDqhVVck;
      string VAouMzLSJU;
      string KDjMdTLiNS;
      string rYFOqnxuzt;
      string PoiCusDBTw;
      string DiixpIJiYW;
      string VmHKswuZEX;
      string CPTOFVUhRk;
      if(orcWBJNkDh == hsypclKMmR){QJOROIpHYh = true;}
      else if(hsypclKMmR == orcWBJNkDh){sJUdZwTzYc = true;}
      if(SHKRPwbcRi == srxfuOBrSB){eNWbYbgYJz = true;}
      else if(srxfuOBrSB == SHKRPwbcRi){MlRSgVsBaA = true;}
      if(iWsguNjCGd == MtwDqhVVck){xcxutmOTrT = true;}
      else if(MtwDqhVVck == iWsguNjCGd){BujFMyaHiK = true;}
      if(LnoipLFpxG == VAouMzLSJU){naRmFLYowj = true;}
      else if(VAouMzLSJU == LnoipLFpxG){mfxLMjCznh = true;}
      if(EwxmhAUZtT == KDjMdTLiNS){FmBWsnsqpc = true;}
      else if(KDjMdTLiNS == EwxmhAUZtT){YCaWENmymT = true;}
      if(WoXRERywan == rYFOqnxuzt){owYRmnMTXa = true;}
      else if(rYFOqnxuzt == WoXRERywan){oVUcnxZPQa = true;}
      if(YKdZWdRaaE == PoiCusDBTw){sWPFsDuiWM = true;}
      else if(PoiCusDBTw == YKdZWdRaaE){VLQNognFGx = true;}
      if(qkeKemYFzu == DiixpIJiYW){DrcYsKaaCF = true;}
      if(rKIlGVQXdX == VmHKswuZEX){tXcOerCzzQ = true;}
      if(MIOJhtRXQD == CPTOFVUhRk){zEQUphWucp = true;}
      while(DiixpIJiYW == qkeKemYFzu){TsMsayUNBz = true;}
      while(VmHKswuZEX == VmHKswuZEX){LbUOVRKUXO = true;}
      while(CPTOFVUhRk == CPTOFVUhRk){KmiMLNkNgW = true;}
      if(QJOROIpHYh == true){QJOROIpHYh = false;}
      if(eNWbYbgYJz == true){eNWbYbgYJz = false;}
      if(xcxutmOTrT == true){xcxutmOTrT = false;}
      if(naRmFLYowj == true){naRmFLYowj = false;}
      if(FmBWsnsqpc == true){FmBWsnsqpc = false;}
      if(owYRmnMTXa == true){owYRmnMTXa = false;}
      if(sWPFsDuiWM == true){sWPFsDuiWM = false;}
      if(DrcYsKaaCF == true){DrcYsKaaCF = false;}
      if(tXcOerCzzQ == true){tXcOerCzzQ = false;}
      if(zEQUphWucp == true){zEQUphWucp = false;}
      if(sJUdZwTzYc == true){sJUdZwTzYc = false;}
      if(MlRSgVsBaA == true){MlRSgVsBaA = false;}
      if(BujFMyaHiK == true){BujFMyaHiK = false;}
      if(mfxLMjCznh == true){mfxLMjCznh = false;}
      if(YCaWENmymT == true){YCaWENmymT = false;}
      if(oVUcnxZPQa == true){oVUcnxZPQa = false;}
      if(VLQNognFGx == true){VLQNognFGx = false;}
      if(TsMsayUNBz == true){TsMsayUNBz = false;}
      if(LbUOVRKUXO == true){LbUOVRKUXO = false;}
      if(KmiMLNkNgW == true){KmiMLNkNgW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDQREAWINQ
{ 
  void cDloYLUpAN()
  { 
      bool NicCAJhaRc = false;
      bool tjWWpNWPwU = false;
      bool ZteOyzEDWw = false;
      bool Hpjinmifjq = false;
      bool FTONUhwQhb = false;
      bool rFNTwSDODA = false;
      bool FdDUVEzniC = false;
      bool epeFOGeRsP = false;
      bool DnVtEBbQmU = false;
      bool iTbilbPtqQ = false;
      bool iIgfxBaIFo = false;
      bool nlUnxRIJPU = false;
      bool bhBOTLOuSl = false;
      bool qkZcguGpxD = false;
      bool aTLxgwynlU = false;
      bool TFdVnAGSLk = false;
      bool leoSyCLqGC = false;
      bool LSMMtHWDgW = false;
      bool MaJySkGEog = false;
      bool nmdLQudsyd = false;
      string AeueCOkowu;
      string osCgknBSGF;
      string ZzdbgGfDGK;
      string qRadsXppGS;
      string qFBMaVBLaj;
      string CRrPaAASyw;
      string ihikEXSXnM;
      string xKLnNUyRAL;
      string ETbWIYZKCr;
      string WWrKiJWQHD;
      string CdXOlrFECG;
      string CiSlqPGMce;
      string xIUuoaRBEE;
      string yhJwIawNjP;
      string TUIwpmEGST;
      string CKmcFtIbYL;
      string ZEzyIUZVcQ;
      string TsbMLbAYEB;
      string VLhjBntfqO;
      string RTnXpOUJnV;
      if(AeueCOkowu == CdXOlrFECG){NicCAJhaRc = true;}
      else if(CdXOlrFECG == AeueCOkowu){iIgfxBaIFo = true;}
      if(osCgknBSGF == CiSlqPGMce){tjWWpNWPwU = true;}
      else if(CiSlqPGMce == osCgknBSGF){nlUnxRIJPU = true;}
      if(ZzdbgGfDGK == xIUuoaRBEE){ZteOyzEDWw = true;}
      else if(xIUuoaRBEE == ZzdbgGfDGK){bhBOTLOuSl = true;}
      if(qRadsXppGS == yhJwIawNjP){Hpjinmifjq = true;}
      else if(yhJwIawNjP == qRadsXppGS){qkZcguGpxD = true;}
      if(qFBMaVBLaj == TUIwpmEGST){FTONUhwQhb = true;}
      else if(TUIwpmEGST == qFBMaVBLaj){aTLxgwynlU = true;}
      if(CRrPaAASyw == CKmcFtIbYL){rFNTwSDODA = true;}
      else if(CKmcFtIbYL == CRrPaAASyw){TFdVnAGSLk = true;}
      if(ihikEXSXnM == ZEzyIUZVcQ){FdDUVEzniC = true;}
      else if(ZEzyIUZVcQ == ihikEXSXnM){leoSyCLqGC = true;}
      if(xKLnNUyRAL == TsbMLbAYEB){epeFOGeRsP = true;}
      if(ETbWIYZKCr == VLhjBntfqO){DnVtEBbQmU = true;}
      if(WWrKiJWQHD == RTnXpOUJnV){iTbilbPtqQ = true;}
      while(TsbMLbAYEB == xKLnNUyRAL){LSMMtHWDgW = true;}
      while(VLhjBntfqO == VLhjBntfqO){MaJySkGEog = true;}
      while(RTnXpOUJnV == RTnXpOUJnV){nmdLQudsyd = true;}
      if(NicCAJhaRc == true){NicCAJhaRc = false;}
      if(tjWWpNWPwU == true){tjWWpNWPwU = false;}
      if(ZteOyzEDWw == true){ZteOyzEDWw = false;}
      if(Hpjinmifjq == true){Hpjinmifjq = false;}
      if(FTONUhwQhb == true){FTONUhwQhb = false;}
      if(rFNTwSDODA == true){rFNTwSDODA = false;}
      if(FdDUVEzniC == true){FdDUVEzniC = false;}
      if(epeFOGeRsP == true){epeFOGeRsP = false;}
      if(DnVtEBbQmU == true){DnVtEBbQmU = false;}
      if(iTbilbPtqQ == true){iTbilbPtqQ = false;}
      if(iIgfxBaIFo == true){iIgfxBaIFo = false;}
      if(nlUnxRIJPU == true){nlUnxRIJPU = false;}
      if(bhBOTLOuSl == true){bhBOTLOuSl = false;}
      if(qkZcguGpxD == true){qkZcguGpxD = false;}
      if(aTLxgwynlU == true){aTLxgwynlU = false;}
      if(TFdVnAGSLk == true){TFdVnAGSLk = false;}
      if(leoSyCLqGC == true){leoSyCLqGC = false;}
      if(LSMMtHWDgW == true){LSMMtHWDgW = false;}
      if(MaJySkGEog == true){MaJySkGEog = false;}
      if(nmdLQudsyd == true){nmdLQudsyd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOVDIWMHLN
{ 
  void uecZCRWNqu()
  { 
      bool GcPUPrnlSW = false;
      bool kRWGziFAYa = false;
      bool JmMIIAITml = false;
      bool hQrZLRbySc = false;
      bool DXoPTsqGjg = false;
      bool ZOHtUTPGLO = false;
      bool jUyfoTYxuh = false;
      bool HHhwWkxxoP = false;
      bool JBiGMTIyEr = false;
      bool CUlDriZIaz = false;
      bool TtLCYSgLWi = false;
      bool VSQwFikqTU = false;
      bool KZrCfmUdDn = false;
      bool LnVpwOoggt = false;
      bool lxbUViDpxJ = false;
      bool xhoFnsBJWl = false;
      bool xCHhXhwazp = false;
      bool sEJZhNyWfw = false;
      bool ieftqczQCD = false;
      bool NfKuwjotxm = false;
      string SuHWaLXFVZ;
      string oUuCjVXkVV;
      string SKJdctfhYk;
      string UxrEcaNYeS;
      string NHWKHiWGBa;
      string wkAmNIldtg;
      string fofkFrcqZI;
      string IzFCIKmyWs;
      string WYfxnjwEpU;
      string ojdymXalFP;
      string GfgsSwfydC;
      string UnHAJHJhwV;
      string uXAETXUHOj;
      string jArGmpqmer;
      string DyamzBcdnf;
      string OrpjThebYt;
      string aYitSUuANT;
      string PVDERxxNFR;
      string uqSiVrKImE;
      string KONjQeOfUe;
      if(SuHWaLXFVZ == GfgsSwfydC){GcPUPrnlSW = true;}
      else if(GfgsSwfydC == SuHWaLXFVZ){TtLCYSgLWi = true;}
      if(oUuCjVXkVV == UnHAJHJhwV){kRWGziFAYa = true;}
      else if(UnHAJHJhwV == oUuCjVXkVV){VSQwFikqTU = true;}
      if(SKJdctfhYk == uXAETXUHOj){JmMIIAITml = true;}
      else if(uXAETXUHOj == SKJdctfhYk){KZrCfmUdDn = true;}
      if(UxrEcaNYeS == jArGmpqmer){hQrZLRbySc = true;}
      else if(jArGmpqmer == UxrEcaNYeS){LnVpwOoggt = true;}
      if(NHWKHiWGBa == DyamzBcdnf){DXoPTsqGjg = true;}
      else if(DyamzBcdnf == NHWKHiWGBa){lxbUViDpxJ = true;}
      if(wkAmNIldtg == OrpjThebYt){ZOHtUTPGLO = true;}
      else if(OrpjThebYt == wkAmNIldtg){xhoFnsBJWl = true;}
      if(fofkFrcqZI == aYitSUuANT){jUyfoTYxuh = true;}
      else if(aYitSUuANT == fofkFrcqZI){xCHhXhwazp = true;}
      if(IzFCIKmyWs == PVDERxxNFR){HHhwWkxxoP = true;}
      if(WYfxnjwEpU == uqSiVrKImE){JBiGMTIyEr = true;}
      if(ojdymXalFP == KONjQeOfUe){CUlDriZIaz = true;}
      while(PVDERxxNFR == IzFCIKmyWs){sEJZhNyWfw = true;}
      while(uqSiVrKImE == uqSiVrKImE){ieftqczQCD = true;}
      while(KONjQeOfUe == KONjQeOfUe){NfKuwjotxm = true;}
      if(GcPUPrnlSW == true){GcPUPrnlSW = false;}
      if(kRWGziFAYa == true){kRWGziFAYa = false;}
      if(JmMIIAITml == true){JmMIIAITml = false;}
      if(hQrZLRbySc == true){hQrZLRbySc = false;}
      if(DXoPTsqGjg == true){DXoPTsqGjg = false;}
      if(ZOHtUTPGLO == true){ZOHtUTPGLO = false;}
      if(jUyfoTYxuh == true){jUyfoTYxuh = false;}
      if(HHhwWkxxoP == true){HHhwWkxxoP = false;}
      if(JBiGMTIyEr == true){JBiGMTIyEr = false;}
      if(CUlDriZIaz == true){CUlDriZIaz = false;}
      if(TtLCYSgLWi == true){TtLCYSgLWi = false;}
      if(VSQwFikqTU == true){VSQwFikqTU = false;}
      if(KZrCfmUdDn == true){KZrCfmUdDn = false;}
      if(LnVpwOoggt == true){LnVpwOoggt = false;}
      if(lxbUViDpxJ == true){lxbUViDpxJ = false;}
      if(xhoFnsBJWl == true){xhoFnsBJWl = false;}
      if(xCHhXhwazp == true){xCHhXhwazp = false;}
      if(sEJZhNyWfw == true){sEJZhNyWfw = false;}
      if(ieftqczQCD == true){ieftqczQCD = false;}
      if(NfKuwjotxm == true){NfKuwjotxm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCENIWUXOJ
{ 
  void nIknMsIBEx()
  { 
      bool MlyPDhJQiz = false;
      bool lcMENNunUe = false;
      bool dQKpQVGYbN = false;
      bool VzgqYQSWNQ = false;
      bool nFTBAPGqbf = false;
      bool tGFFIuaIzg = false;
      bool bknUclwUex = false;
      bool tYZDpXxJpA = false;
      bool POwwTOsahc = false;
      bool pKXgoDRyXN = false;
      bool TkLelVfCPk = false;
      bool yRRyRNnrBO = false;
      bool rVmCHiAsOm = false;
      bool GzkcgdCRJy = false;
      bool hqLxeXsZOb = false;
      bool OYxJUyyJWC = false;
      bool UmmbeygoQm = false;
      bool KViCfBJoXi = false;
      bool padlXgCaHi = false;
      bool fstGduEiSf = false;
      string cjeIqsqMWw;
      string LgdRRYVQBJ;
      string JXSGsghKRa;
      string zfJiCIyUgB;
      string DqeMLITTRr;
      string aePJTEQXOK;
      string LfuuwfWtOJ;
      string aAjAGSsGuk;
      string MNsYzTPzOy;
      string qZGWpWuiPe;
      string kZFHRZuPDB;
      string KKbdxxmVuc;
      string PWePRAtMKi;
      string XKpPAmIkHZ;
      string YAwNmgxbZr;
      string jYmmONtooQ;
      string fiFUcATLcJ;
      string oBOVDPaQck;
      string CRmRzyWCAl;
      string sSuptptajl;
      if(cjeIqsqMWw == kZFHRZuPDB){MlyPDhJQiz = true;}
      else if(kZFHRZuPDB == cjeIqsqMWw){TkLelVfCPk = true;}
      if(LgdRRYVQBJ == KKbdxxmVuc){lcMENNunUe = true;}
      else if(KKbdxxmVuc == LgdRRYVQBJ){yRRyRNnrBO = true;}
      if(JXSGsghKRa == PWePRAtMKi){dQKpQVGYbN = true;}
      else if(PWePRAtMKi == JXSGsghKRa){rVmCHiAsOm = true;}
      if(zfJiCIyUgB == XKpPAmIkHZ){VzgqYQSWNQ = true;}
      else if(XKpPAmIkHZ == zfJiCIyUgB){GzkcgdCRJy = true;}
      if(DqeMLITTRr == YAwNmgxbZr){nFTBAPGqbf = true;}
      else if(YAwNmgxbZr == DqeMLITTRr){hqLxeXsZOb = true;}
      if(aePJTEQXOK == jYmmONtooQ){tGFFIuaIzg = true;}
      else if(jYmmONtooQ == aePJTEQXOK){OYxJUyyJWC = true;}
      if(LfuuwfWtOJ == fiFUcATLcJ){bknUclwUex = true;}
      else if(fiFUcATLcJ == LfuuwfWtOJ){UmmbeygoQm = true;}
      if(aAjAGSsGuk == oBOVDPaQck){tYZDpXxJpA = true;}
      if(MNsYzTPzOy == CRmRzyWCAl){POwwTOsahc = true;}
      if(qZGWpWuiPe == sSuptptajl){pKXgoDRyXN = true;}
      while(oBOVDPaQck == aAjAGSsGuk){KViCfBJoXi = true;}
      while(CRmRzyWCAl == CRmRzyWCAl){padlXgCaHi = true;}
      while(sSuptptajl == sSuptptajl){fstGduEiSf = true;}
      if(MlyPDhJQiz == true){MlyPDhJQiz = false;}
      if(lcMENNunUe == true){lcMENNunUe = false;}
      if(dQKpQVGYbN == true){dQKpQVGYbN = false;}
      if(VzgqYQSWNQ == true){VzgqYQSWNQ = false;}
      if(nFTBAPGqbf == true){nFTBAPGqbf = false;}
      if(tGFFIuaIzg == true){tGFFIuaIzg = false;}
      if(bknUclwUex == true){bknUclwUex = false;}
      if(tYZDpXxJpA == true){tYZDpXxJpA = false;}
      if(POwwTOsahc == true){POwwTOsahc = false;}
      if(pKXgoDRyXN == true){pKXgoDRyXN = false;}
      if(TkLelVfCPk == true){TkLelVfCPk = false;}
      if(yRRyRNnrBO == true){yRRyRNnrBO = false;}
      if(rVmCHiAsOm == true){rVmCHiAsOm = false;}
      if(GzkcgdCRJy == true){GzkcgdCRJy = false;}
      if(hqLxeXsZOb == true){hqLxeXsZOb = false;}
      if(OYxJUyyJWC == true){OYxJUyyJWC = false;}
      if(UmmbeygoQm == true){UmmbeygoQm = false;}
      if(KViCfBJoXi == true){KViCfBJoXi = false;}
      if(padlXgCaHi == true){padlXgCaHi = false;}
      if(fstGduEiSf == true){fstGduEiSf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LEPYZVNOXG
{ 
  void MuCkMFzWiH()
  { 
      bool fniRMgUqnJ = false;
      bool uDfkkLBKGk = false;
      bool kVXTTQWtQM = false;
      bool bOpBIBSSyl = false;
      bool MJxJAEXZcZ = false;
      bool cbPzQJPPxu = false;
      bool JZZagfNeci = false;
      bool riLUXaYOSP = false;
      bool swQqjzzpjy = false;
      bool lDUDbmjVbU = false;
      bool prxtgtQtap = false;
      bool kAwgCNIiqh = false;
      bool fWudxnNIrk = false;
      bool qDlyYAyWJo = false;
      bool iEPtNkHmAN = false;
      bool dAdtnTxSxs = false;
      bool fHBpyhOyHC = false;
      bool OlZBybHBQL = false;
      bool gaIdGpYrJF = false;
      bool DfYPJaCYuf = false;
      string iTKhKctswa;
      string bSIJiSawCO;
      string tImmuGDiMc;
      string jcfywskeKQ;
      string wHQfxCPosc;
      string LCCaQZfXlD;
      string YLgTpzmJNp;
      string huklSlrHor;
      string qOpiQhZEgV;
      string MNsGqkawox;
      string PFaDtQQQHd;
      string hYhsMJUxCI;
      string YhcqcUCdth;
      string LuRqcknlnA;
      string QJwCnnezth;
      string PdtfYgciaZ;
      string OlWZSlHqPb;
      string ViICrPlZDo;
      string oCjLShBkSw;
      string HELOlemWjC;
      if(iTKhKctswa == PFaDtQQQHd){fniRMgUqnJ = true;}
      else if(PFaDtQQQHd == iTKhKctswa){prxtgtQtap = true;}
      if(bSIJiSawCO == hYhsMJUxCI){uDfkkLBKGk = true;}
      else if(hYhsMJUxCI == bSIJiSawCO){kAwgCNIiqh = true;}
      if(tImmuGDiMc == YhcqcUCdth){kVXTTQWtQM = true;}
      else if(YhcqcUCdth == tImmuGDiMc){fWudxnNIrk = true;}
      if(jcfywskeKQ == LuRqcknlnA){bOpBIBSSyl = true;}
      else if(LuRqcknlnA == jcfywskeKQ){qDlyYAyWJo = true;}
      if(wHQfxCPosc == QJwCnnezth){MJxJAEXZcZ = true;}
      else if(QJwCnnezth == wHQfxCPosc){iEPtNkHmAN = true;}
      if(LCCaQZfXlD == PdtfYgciaZ){cbPzQJPPxu = true;}
      else if(PdtfYgciaZ == LCCaQZfXlD){dAdtnTxSxs = true;}
      if(YLgTpzmJNp == OlWZSlHqPb){JZZagfNeci = true;}
      else if(OlWZSlHqPb == YLgTpzmJNp){fHBpyhOyHC = true;}
      if(huklSlrHor == ViICrPlZDo){riLUXaYOSP = true;}
      if(qOpiQhZEgV == oCjLShBkSw){swQqjzzpjy = true;}
      if(MNsGqkawox == HELOlemWjC){lDUDbmjVbU = true;}
      while(ViICrPlZDo == huklSlrHor){OlZBybHBQL = true;}
      while(oCjLShBkSw == oCjLShBkSw){gaIdGpYrJF = true;}
      while(HELOlemWjC == HELOlemWjC){DfYPJaCYuf = true;}
      if(fniRMgUqnJ == true){fniRMgUqnJ = false;}
      if(uDfkkLBKGk == true){uDfkkLBKGk = false;}
      if(kVXTTQWtQM == true){kVXTTQWtQM = false;}
      if(bOpBIBSSyl == true){bOpBIBSSyl = false;}
      if(MJxJAEXZcZ == true){MJxJAEXZcZ = false;}
      if(cbPzQJPPxu == true){cbPzQJPPxu = false;}
      if(JZZagfNeci == true){JZZagfNeci = false;}
      if(riLUXaYOSP == true){riLUXaYOSP = false;}
      if(swQqjzzpjy == true){swQqjzzpjy = false;}
      if(lDUDbmjVbU == true){lDUDbmjVbU = false;}
      if(prxtgtQtap == true){prxtgtQtap = false;}
      if(kAwgCNIiqh == true){kAwgCNIiqh = false;}
      if(fWudxnNIrk == true){fWudxnNIrk = false;}
      if(qDlyYAyWJo == true){qDlyYAyWJo = false;}
      if(iEPtNkHmAN == true){iEPtNkHmAN = false;}
      if(dAdtnTxSxs == true){dAdtnTxSxs = false;}
      if(fHBpyhOyHC == true){fHBpyhOyHC = false;}
      if(OlZBybHBQL == true){OlZBybHBQL = false;}
      if(gaIdGpYrJF == true){gaIdGpYrJF = false;}
      if(DfYPJaCYuf == true){DfYPJaCYuf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWCUXTJTWV
{ 
  void UJhtNCIrAt()
  { 
      bool UjXPfyAMuP = false;
      bool aaKkuJlmwU = false;
      bool eBwtFqUZOM = false;
      bool SGxNTrIRlR = false;
      bool oxpSusZpAG = false;
      bool owKDkTmdKo = false;
      bool cayixUcxQD = false;
      bool BUBdfhKdyL = false;
      bool QdYHWVutbA = false;
      bool EeHwoOyHVa = false;
      bool PbYxFUugXD = false;
      bool IJeyXzBqLa = false;
      bool YiUQzVNFoR = false;
      bool iCIXuoFbCC = false;
      bool aOWXquAIXo = false;
      bool MHwtBgGHyi = false;
      bool HpqFUFAGDi = false;
      bool tZoIAKMwZD = false;
      bool VEgzFaGNWN = false;
      bool hxdSukWQDk = false;
      string oZmqqNkRdx;
      string ApMGglVsxQ;
      string OQboegKNpX;
      string clQCWQwepM;
      string OnjmawMJnG;
      string DrQYwYyxMK;
      string CWaGTOYKiQ;
      string ppCjCZfnOi;
      string TAZjUkVqFy;
      string SySfKqNdSM;
      string WCZXPNpfWW;
      string rJhcqCxqli;
      string rhFkyrWVZK;
      string MCVCLRZBUG;
      string uoTiGIPooI;
      string tWriToxoZX;
      string pTFMKomfRY;
      string bwVenDNVdo;
      string bggRQoKliW;
      string TkawQbjHYQ;
      if(oZmqqNkRdx == WCZXPNpfWW){UjXPfyAMuP = true;}
      else if(WCZXPNpfWW == oZmqqNkRdx){PbYxFUugXD = true;}
      if(ApMGglVsxQ == rJhcqCxqli){aaKkuJlmwU = true;}
      else if(rJhcqCxqli == ApMGglVsxQ){IJeyXzBqLa = true;}
      if(OQboegKNpX == rhFkyrWVZK){eBwtFqUZOM = true;}
      else if(rhFkyrWVZK == OQboegKNpX){YiUQzVNFoR = true;}
      if(clQCWQwepM == MCVCLRZBUG){SGxNTrIRlR = true;}
      else if(MCVCLRZBUG == clQCWQwepM){iCIXuoFbCC = true;}
      if(OnjmawMJnG == uoTiGIPooI){oxpSusZpAG = true;}
      else if(uoTiGIPooI == OnjmawMJnG){aOWXquAIXo = true;}
      if(DrQYwYyxMK == tWriToxoZX){owKDkTmdKo = true;}
      else if(tWriToxoZX == DrQYwYyxMK){MHwtBgGHyi = true;}
      if(CWaGTOYKiQ == pTFMKomfRY){cayixUcxQD = true;}
      else if(pTFMKomfRY == CWaGTOYKiQ){HpqFUFAGDi = true;}
      if(ppCjCZfnOi == bwVenDNVdo){BUBdfhKdyL = true;}
      if(TAZjUkVqFy == bggRQoKliW){QdYHWVutbA = true;}
      if(SySfKqNdSM == TkawQbjHYQ){EeHwoOyHVa = true;}
      while(bwVenDNVdo == ppCjCZfnOi){tZoIAKMwZD = true;}
      while(bggRQoKliW == bggRQoKliW){VEgzFaGNWN = true;}
      while(TkawQbjHYQ == TkawQbjHYQ){hxdSukWQDk = true;}
      if(UjXPfyAMuP == true){UjXPfyAMuP = false;}
      if(aaKkuJlmwU == true){aaKkuJlmwU = false;}
      if(eBwtFqUZOM == true){eBwtFqUZOM = false;}
      if(SGxNTrIRlR == true){SGxNTrIRlR = false;}
      if(oxpSusZpAG == true){oxpSusZpAG = false;}
      if(owKDkTmdKo == true){owKDkTmdKo = false;}
      if(cayixUcxQD == true){cayixUcxQD = false;}
      if(BUBdfhKdyL == true){BUBdfhKdyL = false;}
      if(QdYHWVutbA == true){QdYHWVutbA = false;}
      if(EeHwoOyHVa == true){EeHwoOyHVa = false;}
      if(PbYxFUugXD == true){PbYxFUugXD = false;}
      if(IJeyXzBqLa == true){IJeyXzBqLa = false;}
      if(YiUQzVNFoR == true){YiUQzVNFoR = false;}
      if(iCIXuoFbCC == true){iCIXuoFbCC = false;}
      if(aOWXquAIXo == true){aOWXquAIXo = false;}
      if(MHwtBgGHyi == true){MHwtBgGHyi = false;}
      if(HpqFUFAGDi == true){HpqFUFAGDi = false;}
      if(tZoIAKMwZD == true){tZoIAKMwZD = false;}
      if(VEgzFaGNWN == true){VEgzFaGNWN = false;}
      if(hxdSukWQDk == true){hxdSukWQDk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSLHXFOSIA
{ 
  void zKAfDGCaip()
  { 
      bool zDdOHkPHlf = false;
      bool YJuJHIllMi = false;
      bool IMbyeWNrBs = false;
      bool ROyUeknVKh = false;
      bool xGkjRzwXFi = false;
      bool qNPAelbeij = false;
      bool WWGrOJKaeW = false;
      bool TPbekBaqge = false;
      bool apmRBDzyor = false;
      bool JImaKZAsVH = false;
      bool oVshObljPd = false;
      bool LjyDIfjnpK = false;
      bool KMklNLbATK = false;
      bool AhVYpFxEDZ = false;
      bool ROiLgYKiRd = false;
      bool pMCKwcjGUD = false;
      bool zkQEdcNYMD = false;
      bool ifjQswdZFn = false;
      bool AsioUmfKbN = false;
      bool UpizZfxehD = false;
      string iySeZfUQbc;
      string ltWUkfcOfd;
      string DXXbQfDhLn;
      string wPKBGZsckK;
      string inyLrxakMU;
      string KmPZsKapOt;
      string clEnfWiVOL;
      string mzdVuPZLjT;
      string FSVpcJzkIu;
      string yCOpgwiKfV;
      string NFWAgLJsdc;
      string kPGunKQOKW;
      string XyNSMkkmoy;
      string gOfNFAuUJR;
      string AFHeKiwSCW;
      string fUAIxPqDmw;
      string ZWEeuWjron;
      string OuErWRphId;
      string nRjSSMOWPp;
      string IqgMqcAbim;
      if(iySeZfUQbc == NFWAgLJsdc){zDdOHkPHlf = true;}
      else if(NFWAgLJsdc == iySeZfUQbc){oVshObljPd = true;}
      if(ltWUkfcOfd == kPGunKQOKW){YJuJHIllMi = true;}
      else if(kPGunKQOKW == ltWUkfcOfd){LjyDIfjnpK = true;}
      if(DXXbQfDhLn == XyNSMkkmoy){IMbyeWNrBs = true;}
      else if(XyNSMkkmoy == DXXbQfDhLn){KMklNLbATK = true;}
      if(wPKBGZsckK == gOfNFAuUJR){ROyUeknVKh = true;}
      else if(gOfNFAuUJR == wPKBGZsckK){AhVYpFxEDZ = true;}
      if(inyLrxakMU == AFHeKiwSCW){xGkjRzwXFi = true;}
      else if(AFHeKiwSCW == inyLrxakMU){ROiLgYKiRd = true;}
      if(KmPZsKapOt == fUAIxPqDmw){qNPAelbeij = true;}
      else if(fUAIxPqDmw == KmPZsKapOt){pMCKwcjGUD = true;}
      if(clEnfWiVOL == ZWEeuWjron){WWGrOJKaeW = true;}
      else if(ZWEeuWjron == clEnfWiVOL){zkQEdcNYMD = true;}
      if(mzdVuPZLjT == OuErWRphId){TPbekBaqge = true;}
      if(FSVpcJzkIu == nRjSSMOWPp){apmRBDzyor = true;}
      if(yCOpgwiKfV == IqgMqcAbim){JImaKZAsVH = true;}
      while(OuErWRphId == mzdVuPZLjT){ifjQswdZFn = true;}
      while(nRjSSMOWPp == nRjSSMOWPp){AsioUmfKbN = true;}
      while(IqgMqcAbim == IqgMqcAbim){UpizZfxehD = true;}
      if(zDdOHkPHlf == true){zDdOHkPHlf = false;}
      if(YJuJHIllMi == true){YJuJHIllMi = false;}
      if(IMbyeWNrBs == true){IMbyeWNrBs = false;}
      if(ROyUeknVKh == true){ROyUeknVKh = false;}
      if(xGkjRzwXFi == true){xGkjRzwXFi = false;}
      if(qNPAelbeij == true){qNPAelbeij = false;}
      if(WWGrOJKaeW == true){WWGrOJKaeW = false;}
      if(TPbekBaqge == true){TPbekBaqge = false;}
      if(apmRBDzyor == true){apmRBDzyor = false;}
      if(JImaKZAsVH == true){JImaKZAsVH = false;}
      if(oVshObljPd == true){oVshObljPd = false;}
      if(LjyDIfjnpK == true){LjyDIfjnpK = false;}
      if(KMklNLbATK == true){KMklNLbATK = false;}
      if(AhVYpFxEDZ == true){AhVYpFxEDZ = false;}
      if(ROiLgYKiRd == true){ROiLgYKiRd = false;}
      if(pMCKwcjGUD == true){pMCKwcjGUD = false;}
      if(zkQEdcNYMD == true){zkQEdcNYMD = false;}
      if(ifjQswdZFn == true){ifjQswdZFn = false;}
      if(AsioUmfKbN == true){AsioUmfKbN = false;}
      if(UpizZfxehD == true){UpizZfxehD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXJWEQSDZU
{ 
  void gdRiWJGciO()
  { 
      bool VuCEHdJhqZ = false;
      bool UcmoQOhUUh = false;
      bool ssNIaAjepY = false;
      bool QrqqbyFycr = false;
      bool QUZBupbQNw = false;
      bool rDsjCchtcH = false;
      bool terSJclwMS = false;
      bool IiqcQYSLNk = false;
      bool XSQsfMyGoz = false;
      bool QLUVxlbHrR = false;
      bool DfEtmIMQTd = false;
      bool KVfriaNylx = false;
      bool eeGNCxNVed = false;
      bool wKTwgqOWGX = false;
      bool AgmLoteclW = false;
      bool XdVulYZprp = false;
      bool upkogzCjKr = false;
      bool MqrOwxruYI = false;
      bool SkjIGSoYJI = false;
      bool RXePcJwxdo = false;
      string pAYcrXNjyx;
      string HTKeNNXdbx;
      string GzVTbOQPIZ;
      string nuQuUfUtcm;
      string CsrLtrlRBf;
      string joCcQqeFAc;
      string HyaYJLCOJh;
      string rdBntMGKZi;
      string czNcoyrnec;
      string BPszfERTBi;
      string pWHTmGmNhD;
      string jTfRAHjyiK;
      string TNjffcjCIp;
      string tmIqrFqtoh;
      string LdGasgjbzX;
      string TTjqOblanK;
      string WkFqIxKoYt;
      string QpJBzoGJmy;
      string sIDjVaDRbQ;
      string SPGeKZYORw;
      if(pAYcrXNjyx == pWHTmGmNhD){VuCEHdJhqZ = true;}
      else if(pWHTmGmNhD == pAYcrXNjyx){DfEtmIMQTd = true;}
      if(HTKeNNXdbx == jTfRAHjyiK){UcmoQOhUUh = true;}
      else if(jTfRAHjyiK == HTKeNNXdbx){KVfriaNylx = true;}
      if(GzVTbOQPIZ == TNjffcjCIp){ssNIaAjepY = true;}
      else if(TNjffcjCIp == GzVTbOQPIZ){eeGNCxNVed = true;}
      if(nuQuUfUtcm == tmIqrFqtoh){QrqqbyFycr = true;}
      else if(tmIqrFqtoh == nuQuUfUtcm){wKTwgqOWGX = true;}
      if(CsrLtrlRBf == LdGasgjbzX){QUZBupbQNw = true;}
      else if(LdGasgjbzX == CsrLtrlRBf){AgmLoteclW = true;}
      if(joCcQqeFAc == TTjqOblanK){rDsjCchtcH = true;}
      else if(TTjqOblanK == joCcQqeFAc){XdVulYZprp = true;}
      if(HyaYJLCOJh == WkFqIxKoYt){terSJclwMS = true;}
      else if(WkFqIxKoYt == HyaYJLCOJh){upkogzCjKr = true;}
      if(rdBntMGKZi == QpJBzoGJmy){IiqcQYSLNk = true;}
      if(czNcoyrnec == sIDjVaDRbQ){XSQsfMyGoz = true;}
      if(BPszfERTBi == SPGeKZYORw){QLUVxlbHrR = true;}
      while(QpJBzoGJmy == rdBntMGKZi){MqrOwxruYI = true;}
      while(sIDjVaDRbQ == sIDjVaDRbQ){SkjIGSoYJI = true;}
      while(SPGeKZYORw == SPGeKZYORw){RXePcJwxdo = true;}
      if(VuCEHdJhqZ == true){VuCEHdJhqZ = false;}
      if(UcmoQOhUUh == true){UcmoQOhUUh = false;}
      if(ssNIaAjepY == true){ssNIaAjepY = false;}
      if(QrqqbyFycr == true){QrqqbyFycr = false;}
      if(QUZBupbQNw == true){QUZBupbQNw = false;}
      if(rDsjCchtcH == true){rDsjCchtcH = false;}
      if(terSJclwMS == true){terSJclwMS = false;}
      if(IiqcQYSLNk == true){IiqcQYSLNk = false;}
      if(XSQsfMyGoz == true){XSQsfMyGoz = false;}
      if(QLUVxlbHrR == true){QLUVxlbHrR = false;}
      if(DfEtmIMQTd == true){DfEtmIMQTd = false;}
      if(KVfriaNylx == true){KVfriaNylx = false;}
      if(eeGNCxNVed == true){eeGNCxNVed = false;}
      if(wKTwgqOWGX == true){wKTwgqOWGX = false;}
      if(AgmLoteclW == true){AgmLoteclW = false;}
      if(XdVulYZprp == true){XdVulYZprp = false;}
      if(upkogzCjKr == true){upkogzCjKr = false;}
      if(MqrOwxruYI == true){MqrOwxruYI = false;}
      if(SkjIGSoYJI == true){SkjIGSoYJI = false;}
      if(RXePcJwxdo == true){RXePcJwxdo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCJYTEIOXF
{ 
  void DKjINDkqUd()
  { 
      bool AgkuxeAYKP = false;
      bool NEdWCcVTVa = false;
      bool DJFeddslGW = false;
      bool oCJhECXmGs = false;
      bool JKqSmaiYQq = false;
      bool AhUhgqaGQT = false;
      bool lORmZLuuRz = false;
      bool FhMcRrRmqD = false;
      bool tUUPWHhbAM = false;
      bool aQWmHtrErb = false;
      bool fnGQlRUqPo = false;
      bool ZmONYRtCPS = false;
      bool dTtEXnLZUX = false;
      bool ANtPWGNDcF = false;
      bool lpLLmmCJOo = false;
      bool ApnZxLsBsy = false;
      bool FuWrnMsypR = false;
      bool DpYKfnHhQj = false;
      bool kCKeWKYTRL = false;
      bool MLKezpSSXa = false;
      string hlsKpRdsxL;
      string LslRPsFfaf;
      string ytrBhlTCoA;
      string WynbgWpeXo;
      string HTcNlpuWls;
      string kBENfmtrcE;
      string ybEwoMFJjs;
      string CaHkYeQdOq;
      string pwPuPUtaws;
      string byBTqfOgYZ;
      string klmspKsSnB;
      string WQclOBLJgU;
      string SeNpQEYnts;
      string PjFoGEJWEF;
      string aaltWLUPFo;
      string TFADHGXwbl;
      string kFYuklKneK;
      string qnEasqrSSF;
      string iIiEYJiBhA;
      string fMuSTVCpJj;
      if(hlsKpRdsxL == klmspKsSnB){AgkuxeAYKP = true;}
      else if(klmspKsSnB == hlsKpRdsxL){fnGQlRUqPo = true;}
      if(LslRPsFfaf == WQclOBLJgU){NEdWCcVTVa = true;}
      else if(WQclOBLJgU == LslRPsFfaf){ZmONYRtCPS = true;}
      if(ytrBhlTCoA == SeNpQEYnts){DJFeddslGW = true;}
      else if(SeNpQEYnts == ytrBhlTCoA){dTtEXnLZUX = true;}
      if(WynbgWpeXo == PjFoGEJWEF){oCJhECXmGs = true;}
      else if(PjFoGEJWEF == WynbgWpeXo){ANtPWGNDcF = true;}
      if(HTcNlpuWls == aaltWLUPFo){JKqSmaiYQq = true;}
      else if(aaltWLUPFo == HTcNlpuWls){lpLLmmCJOo = true;}
      if(kBENfmtrcE == TFADHGXwbl){AhUhgqaGQT = true;}
      else if(TFADHGXwbl == kBENfmtrcE){ApnZxLsBsy = true;}
      if(ybEwoMFJjs == kFYuklKneK){lORmZLuuRz = true;}
      else if(kFYuklKneK == ybEwoMFJjs){FuWrnMsypR = true;}
      if(CaHkYeQdOq == qnEasqrSSF){FhMcRrRmqD = true;}
      if(pwPuPUtaws == iIiEYJiBhA){tUUPWHhbAM = true;}
      if(byBTqfOgYZ == fMuSTVCpJj){aQWmHtrErb = true;}
      while(qnEasqrSSF == CaHkYeQdOq){DpYKfnHhQj = true;}
      while(iIiEYJiBhA == iIiEYJiBhA){kCKeWKYTRL = true;}
      while(fMuSTVCpJj == fMuSTVCpJj){MLKezpSSXa = true;}
      if(AgkuxeAYKP == true){AgkuxeAYKP = false;}
      if(NEdWCcVTVa == true){NEdWCcVTVa = false;}
      if(DJFeddslGW == true){DJFeddslGW = false;}
      if(oCJhECXmGs == true){oCJhECXmGs = false;}
      if(JKqSmaiYQq == true){JKqSmaiYQq = false;}
      if(AhUhgqaGQT == true){AhUhgqaGQT = false;}
      if(lORmZLuuRz == true){lORmZLuuRz = false;}
      if(FhMcRrRmqD == true){FhMcRrRmqD = false;}
      if(tUUPWHhbAM == true){tUUPWHhbAM = false;}
      if(aQWmHtrErb == true){aQWmHtrErb = false;}
      if(fnGQlRUqPo == true){fnGQlRUqPo = false;}
      if(ZmONYRtCPS == true){ZmONYRtCPS = false;}
      if(dTtEXnLZUX == true){dTtEXnLZUX = false;}
      if(ANtPWGNDcF == true){ANtPWGNDcF = false;}
      if(lpLLmmCJOo == true){lpLLmmCJOo = false;}
      if(ApnZxLsBsy == true){ApnZxLsBsy = false;}
      if(FuWrnMsypR == true){FuWrnMsypR = false;}
      if(DpYKfnHhQj == true){DpYKfnHhQj = false;}
      if(kCKeWKYTRL == true){kCKeWKYTRL = false;}
      if(MLKezpSSXa == true){MLKezpSSXa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BPSKASGUBI
{ 
  void YzYrtiyGiB()
  { 
      bool SyKRyQuZrf = false;
      bool VsWXKEAYjw = false;
      bool tWhiYbhsPN = false;
      bool MtdIGeQEUd = false;
      bool FMHlKfuXHm = false;
      bool rFNKcuPasV = false;
      bool hBKdSbPNRe = false;
      bool mwEGqhPuYr = false;
      bool gJlbVHfTeK = false;
      bool OpKyuDBdTi = false;
      bool QgGbzuAHTu = false;
      bool fTBAoXOhHL = false;
      bool uuiGPxkFLm = false;
      bool flbpbACJba = false;
      bool HYzjeuoJJW = false;
      bool oSVHmUxAMC = false;
      bool KtugOtqKYn = false;
      bool VEFgEVwybU = false;
      bool HawoxMPUCH = false;
      bool CCxZPMdSVj = false;
      string ahYkSBVGSo;
      string nAgielUCrG;
      string qnpDqohrQd;
      string qzdlrDNfwZ;
      string xNDUaIPbmq;
      string WQXeflrUtc;
      string TcpnxoVupa;
      string XnGSJcjVch;
      string ZFFYHabzFG;
      string LslTGTWPWl;
      string lUlLShKEUC;
      string BVrLDNXQgW;
      string NWojOeBmMp;
      string GUzpuFTsFY;
      string PWdDEpAZPr;
      string uFhzXPeCxn;
      string fXrewgWBPy;
      string teKHGqskfY;
      string dbWTtAlzSf;
      string ZRwRrrdyGW;
      if(ahYkSBVGSo == lUlLShKEUC){SyKRyQuZrf = true;}
      else if(lUlLShKEUC == ahYkSBVGSo){QgGbzuAHTu = true;}
      if(nAgielUCrG == BVrLDNXQgW){VsWXKEAYjw = true;}
      else if(BVrLDNXQgW == nAgielUCrG){fTBAoXOhHL = true;}
      if(qnpDqohrQd == NWojOeBmMp){tWhiYbhsPN = true;}
      else if(NWojOeBmMp == qnpDqohrQd){uuiGPxkFLm = true;}
      if(qzdlrDNfwZ == GUzpuFTsFY){MtdIGeQEUd = true;}
      else if(GUzpuFTsFY == qzdlrDNfwZ){flbpbACJba = true;}
      if(xNDUaIPbmq == PWdDEpAZPr){FMHlKfuXHm = true;}
      else if(PWdDEpAZPr == xNDUaIPbmq){HYzjeuoJJW = true;}
      if(WQXeflrUtc == uFhzXPeCxn){rFNKcuPasV = true;}
      else if(uFhzXPeCxn == WQXeflrUtc){oSVHmUxAMC = true;}
      if(TcpnxoVupa == fXrewgWBPy){hBKdSbPNRe = true;}
      else if(fXrewgWBPy == TcpnxoVupa){KtugOtqKYn = true;}
      if(XnGSJcjVch == teKHGqskfY){mwEGqhPuYr = true;}
      if(ZFFYHabzFG == dbWTtAlzSf){gJlbVHfTeK = true;}
      if(LslTGTWPWl == ZRwRrrdyGW){OpKyuDBdTi = true;}
      while(teKHGqskfY == XnGSJcjVch){VEFgEVwybU = true;}
      while(dbWTtAlzSf == dbWTtAlzSf){HawoxMPUCH = true;}
      while(ZRwRrrdyGW == ZRwRrrdyGW){CCxZPMdSVj = true;}
      if(SyKRyQuZrf == true){SyKRyQuZrf = false;}
      if(VsWXKEAYjw == true){VsWXKEAYjw = false;}
      if(tWhiYbhsPN == true){tWhiYbhsPN = false;}
      if(MtdIGeQEUd == true){MtdIGeQEUd = false;}
      if(FMHlKfuXHm == true){FMHlKfuXHm = false;}
      if(rFNKcuPasV == true){rFNKcuPasV = false;}
      if(hBKdSbPNRe == true){hBKdSbPNRe = false;}
      if(mwEGqhPuYr == true){mwEGqhPuYr = false;}
      if(gJlbVHfTeK == true){gJlbVHfTeK = false;}
      if(OpKyuDBdTi == true){OpKyuDBdTi = false;}
      if(QgGbzuAHTu == true){QgGbzuAHTu = false;}
      if(fTBAoXOhHL == true){fTBAoXOhHL = false;}
      if(uuiGPxkFLm == true){uuiGPxkFLm = false;}
      if(flbpbACJba == true){flbpbACJba = false;}
      if(HYzjeuoJJW == true){HYzjeuoJJW = false;}
      if(oSVHmUxAMC == true){oSVHmUxAMC = false;}
      if(KtugOtqKYn == true){KtugOtqKYn = false;}
      if(VEFgEVwybU == true){VEFgEVwybU = false;}
      if(HawoxMPUCH == true){HawoxMPUCH = false;}
      if(CCxZPMdSVj == true){CCxZPMdSVj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVNUKDAWCR
{ 
  void oencUwbAiQ()
  { 
      bool XhkUPqSDtm = false;
      bool ZixfBBGtHF = false;
      bool xWzCiHQCMT = false;
      bool hbZhNHoXgr = false;
      bool szhpBMOPJS = false;
      bool AIRHiBhhlH = false;
      bool aQqaFyIPRs = false;
      bool MhNOLyoJBW = false;
      bool sArsSZKRzM = false;
      bool YGlYRcIGkD = false;
      bool DzyQGRtCwk = false;
      bool LXgOOZYxHe = false;
      bool nqQETFwnxi = false;
      bool ohYySsCamB = false;
      bool eHUNABZWKq = false;
      bool EKyFPLhswA = false;
      bool VFFNuczhwU = false;
      bool WxKGAfVCES = false;
      bool fYdFdeiTiG = false;
      bool LJelfYBHRW = false;
      string EQBcwbBnQD;
      string HJpWlWGgRH;
      string rOYNCwBneU;
      string aGukIKdVtF;
      string oELbGHrUBj;
      string Edlxwormaz;
      string ZMJubAOFNa;
      string rkmMRmCwHt;
      string DfmtQwUxnS;
      string SqutecuPzF;
      string rmGZrSqYfJ;
      string muffutYPee;
      string fRRtIBprgn;
      string rmwCBQYMCx;
      string FuQdfWLPzj;
      string DfjUYaVMRq;
      string czqrQzzcdd;
      string UMNgZkAmOl;
      string oarwjLCbca;
      string uMuKUGDYMf;
      if(EQBcwbBnQD == rmGZrSqYfJ){XhkUPqSDtm = true;}
      else if(rmGZrSqYfJ == EQBcwbBnQD){DzyQGRtCwk = true;}
      if(HJpWlWGgRH == muffutYPee){ZixfBBGtHF = true;}
      else if(muffutYPee == HJpWlWGgRH){LXgOOZYxHe = true;}
      if(rOYNCwBneU == fRRtIBprgn){xWzCiHQCMT = true;}
      else if(fRRtIBprgn == rOYNCwBneU){nqQETFwnxi = true;}
      if(aGukIKdVtF == rmwCBQYMCx){hbZhNHoXgr = true;}
      else if(rmwCBQYMCx == aGukIKdVtF){ohYySsCamB = true;}
      if(oELbGHrUBj == FuQdfWLPzj){szhpBMOPJS = true;}
      else if(FuQdfWLPzj == oELbGHrUBj){eHUNABZWKq = true;}
      if(Edlxwormaz == DfjUYaVMRq){AIRHiBhhlH = true;}
      else if(DfjUYaVMRq == Edlxwormaz){EKyFPLhswA = true;}
      if(ZMJubAOFNa == czqrQzzcdd){aQqaFyIPRs = true;}
      else if(czqrQzzcdd == ZMJubAOFNa){VFFNuczhwU = true;}
      if(rkmMRmCwHt == UMNgZkAmOl){MhNOLyoJBW = true;}
      if(DfmtQwUxnS == oarwjLCbca){sArsSZKRzM = true;}
      if(SqutecuPzF == uMuKUGDYMf){YGlYRcIGkD = true;}
      while(UMNgZkAmOl == rkmMRmCwHt){WxKGAfVCES = true;}
      while(oarwjLCbca == oarwjLCbca){fYdFdeiTiG = true;}
      while(uMuKUGDYMf == uMuKUGDYMf){LJelfYBHRW = true;}
      if(XhkUPqSDtm == true){XhkUPqSDtm = false;}
      if(ZixfBBGtHF == true){ZixfBBGtHF = false;}
      if(xWzCiHQCMT == true){xWzCiHQCMT = false;}
      if(hbZhNHoXgr == true){hbZhNHoXgr = false;}
      if(szhpBMOPJS == true){szhpBMOPJS = false;}
      if(AIRHiBhhlH == true){AIRHiBhhlH = false;}
      if(aQqaFyIPRs == true){aQqaFyIPRs = false;}
      if(MhNOLyoJBW == true){MhNOLyoJBW = false;}
      if(sArsSZKRzM == true){sArsSZKRzM = false;}
      if(YGlYRcIGkD == true){YGlYRcIGkD = false;}
      if(DzyQGRtCwk == true){DzyQGRtCwk = false;}
      if(LXgOOZYxHe == true){LXgOOZYxHe = false;}
      if(nqQETFwnxi == true){nqQETFwnxi = false;}
      if(ohYySsCamB == true){ohYySsCamB = false;}
      if(eHUNABZWKq == true){eHUNABZWKq = false;}
      if(EKyFPLhswA == true){EKyFPLhswA = false;}
      if(VFFNuczhwU == true){VFFNuczhwU = false;}
      if(WxKGAfVCES == true){WxKGAfVCES = false;}
      if(fYdFdeiTiG == true){fYdFdeiTiG = false;}
      if(LJelfYBHRW == true){LJelfYBHRW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUPMVDFQWK
{ 
  void nUkiUJRUaj()
  { 
      bool xBEeVqJRWm = false;
      bool dwBQbffUmb = false;
      bool qRzEtbJGit = false;
      bool efKWYqxKIp = false;
      bool thucfyDstB = false;
      bool jbBqReBzjs = false;
      bool gDibIxkerj = false;
      bool iVLxgJVWYu = false;
      bool YQLhKCdSFs = false;
      bool pxZPIqyTTh = false;
      bool NXAKSOQEJH = false;
      bool JeZnUQrBQG = false;
      bool TRZzskuwnp = false;
      bool KCCqhAPAPu = false;
      bool lZJxjLXktr = false;
      bool yxCNOwyAQh = false;
      bool STQSxGbiGU = false;
      bool AqlUTtIcPh = false;
      bool MJCwrMAnbl = false;
      bool CPihcSIpzc = false;
      string cbeZPdHPXm;
      string OGsAyGHAqE;
      string sGPMQfMAZb;
      string dMEqwdgyNm;
      string iwJlpeFPLE;
      string LPjhUWMSIj;
      string QGouJBBBEU;
      string YJlDUxwcVl;
      string ZxoVQNcWWZ;
      string QOodVcGNco;
      string dELqeBcfMW;
      string ZjxWKTRTeu;
      string YeddDKTIgr;
      string qizgIUlxqO;
      string jwJzzgRSTC;
      string KligPyZgmU;
      string gUzUfqjQOo;
      string gTcQKbUdeV;
      string sBodgEARQJ;
      string tFKVgPxoTI;
      if(cbeZPdHPXm == dELqeBcfMW){xBEeVqJRWm = true;}
      else if(dELqeBcfMW == cbeZPdHPXm){NXAKSOQEJH = true;}
      if(OGsAyGHAqE == ZjxWKTRTeu){dwBQbffUmb = true;}
      else if(ZjxWKTRTeu == OGsAyGHAqE){JeZnUQrBQG = true;}
      if(sGPMQfMAZb == YeddDKTIgr){qRzEtbJGit = true;}
      else if(YeddDKTIgr == sGPMQfMAZb){TRZzskuwnp = true;}
      if(dMEqwdgyNm == qizgIUlxqO){efKWYqxKIp = true;}
      else if(qizgIUlxqO == dMEqwdgyNm){KCCqhAPAPu = true;}
      if(iwJlpeFPLE == jwJzzgRSTC){thucfyDstB = true;}
      else if(jwJzzgRSTC == iwJlpeFPLE){lZJxjLXktr = true;}
      if(LPjhUWMSIj == KligPyZgmU){jbBqReBzjs = true;}
      else if(KligPyZgmU == LPjhUWMSIj){yxCNOwyAQh = true;}
      if(QGouJBBBEU == gUzUfqjQOo){gDibIxkerj = true;}
      else if(gUzUfqjQOo == QGouJBBBEU){STQSxGbiGU = true;}
      if(YJlDUxwcVl == gTcQKbUdeV){iVLxgJVWYu = true;}
      if(ZxoVQNcWWZ == sBodgEARQJ){YQLhKCdSFs = true;}
      if(QOodVcGNco == tFKVgPxoTI){pxZPIqyTTh = true;}
      while(gTcQKbUdeV == YJlDUxwcVl){AqlUTtIcPh = true;}
      while(sBodgEARQJ == sBodgEARQJ){MJCwrMAnbl = true;}
      while(tFKVgPxoTI == tFKVgPxoTI){CPihcSIpzc = true;}
      if(xBEeVqJRWm == true){xBEeVqJRWm = false;}
      if(dwBQbffUmb == true){dwBQbffUmb = false;}
      if(qRzEtbJGit == true){qRzEtbJGit = false;}
      if(efKWYqxKIp == true){efKWYqxKIp = false;}
      if(thucfyDstB == true){thucfyDstB = false;}
      if(jbBqReBzjs == true){jbBqReBzjs = false;}
      if(gDibIxkerj == true){gDibIxkerj = false;}
      if(iVLxgJVWYu == true){iVLxgJVWYu = false;}
      if(YQLhKCdSFs == true){YQLhKCdSFs = false;}
      if(pxZPIqyTTh == true){pxZPIqyTTh = false;}
      if(NXAKSOQEJH == true){NXAKSOQEJH = false;}
      if(JeZnUQrBQG == true){JeZnUQrBQG = false;}
      if(TRZzskuwnp == true){TRZzskuwnp = false;}
      if(KCCqhAPAPu == true){KCCqhAPAPu = false;}
      if(lZJxjLXktr == true){lZJxjLXktr = false;}
      if(yxCNOwyAQh == true){yxCNOwyAQh = false;}
      if(STQSxGbiGU == true){STQSxGbiGU = false;}
      if(AqlUTtIcPh == true){AqlUTtIcPh = false;}
      if(MJCwrMAnbl == true){MJCwrMAnbl = false;}
      if(CPihcSIpzc == true){CPihcSIpzc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJQIVKDSFL
{ 
  void gCGHtLFYNk()
  { 
      bool sFNlXDzAOy = false;
      bool pERwELyeZI = false;
      bool GcnTugNRqJ = false;
      bool YfANOjJzTn = false;
      bool EnZohitYbH = false;
      bool OJoyWQQspq = false;
      bool phJEZKDDhU = false;
      bool BzLkDRCzlM = false;
      bool mnoiuPpBpx = false;
      bool TQIcyWeVPW = false;
      bool eqqHGOxDuF = false;
      bool NRGdDCrZIK = false;
      bool TBMjAkphmf = false;
      bool lgjPgwwhcf = false;
      bool RmGkjCJdYw = false;
      bool eFMEDcdHGU = false;
      bool XPQOSggqxH = false;
      bool FKxbsfuaAy = false;
      bool aMJqBgUeLD = false;
      bool RobHICWqSC = false;
      string xSwKLVONrA;
      string eNicBGLogp;
      string OctinnKBuN;
      string rOGWpcXbcq;
      string LoDNzTzNyB;
      string xDWbnUYMVX;
      string LNSeIPGLmY;
      string ijLpdYYfiU;
      string nwCsQnreiU;
      string EKGEfyWYFj;
      string MnaZSMqgxO;
      string urcAiOLYNT;
      string XbbRUXdHJe;
      string CAazIAUbaD;
      string xLgTZLhFVR;
      string mxKkLkMJFt;
      string ijWRMuRcri;
      string siyKWMtHrI;
      string oXkrrEoonX;
      string mLVgTMnOHd;
      if(xSwKLVONrA == MnaZSMqgxO){sFNlXDzAOy = true;}
      else if(MnaZSMqgxO == xSwKLVONrA){eqqHGOxDuF = true;}
      if(eNicBGLogp == urcAiOLYNT){pERwELyeZI = true;}
      else if(urcAiOLYNT == eNicBGLogp){NRGdDCrZIK = true;}
      if(OctinnKBuN == XbbRUXdHJe){GcnTugNRqJ = true;}
      else if(XbbRUXdHJe == OctinnKBuN){TBMjAkphmf = true;}
      if(rOGWpcXbcq == CAazIAUbaD){YfANOjJzTn = true;}
      else if(CAazIAUbaD == rOGWpcXbcq){lgjPgwwhcf = true;}
      if(LoDNzTzNyB == xLgTZLhFVR){EnZohitYbH = true;}
      else if(xLgTZLhFVR == LoDNzTzNyB){RmGkjCJdYw = true;}
      if(xDWbnUYMVX == mxKkLkMJFt){OJoyWQQspq = true;}
      else if(mxKkLkMJFt == xDWbnUYMVX){eFMEDcdHGU = true;}
      if(LNSeIPGLmY == ijWRMuRcri){phJEZKDDhU = true;}
      else if(ijWRMuRcri == LNSeIPGLmY){XPQOSggqxH = true;}
      if(ijLpdYYfiU == siyKWMtHrI){BzLkDRCzlM = true;}
      if(nwCsQnreiU == oXkrrEoonX){mnoiuPpBpx = true;}
      if(EKGEfyWYFj == mLVgTMnOHd){TQIcyWeVPW = true;}
      while(siyKWMtHrI == ijLpdYYfiU){FKxbsfuaAy = true;}
      while(oXkrrEoonX == oXkrrEoonX){aMJqBgUeLD = true;}
      while(mLVgTMnOHd == mLVgTMnOHd){RobHICWqSC = true;}
      if(sFNlXDzAOy == true){sFNlXDzAOy = false;}
      if(pERwELyeZI == true){pERwELyeZI = false;}
      if(GcnTugNRqJ == true){GcnTugNRqJ = false;}
      if(YfANOjJzTn == true){YfANOjJzTn = false;}
      if(EnZohitYbH == true){EnZohitYbH = false;}
      if(OJoyWQQspq == true){OJoyWQQspq = false;}
      if(phJEZKDDhU == true){phJEZKDDhU = false;}
      if(BzLkDRCzlM == true){BzLkDRCzlM = false;}
      if(mnoiuPpBpx == true){mnoiuPpBpx = false;}
      if(TQIcyWeVPW == true){TQIcyWeVPW = false;}
      if(eqqHGOxDuF == true){eqqHGOxDuF = false;}
      if(NRGdDCrZIK == true){NRGdDCrZIK = false;}
      if(TBMjAkphmf == true){TBMjAkphmf = false;}
      if(lgjPgwwhcf == true){lgjPgwwhcf = false;}
      if(RmGkjCJdYw == true){RmGkjCJdYw = false;}
      if(eFMEDcdHGU == true){eFMEDcdHGU = false;}
      if(XPQOSggqxH == true){XPQOSggqxH = false;}
      if(FKxbsfuaAy == true){FKxbsfuaAy = false;}
      if(aMJqBgUeLD == true){aMJqBgUeLD = false;}
      if(RobHICWqSC == true){RobHICWqSC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYSHHICNEN
{ 
  void iFiEZRiPQo()
  { 
      bool OYiIKDEhGX = false;
      bool iYOLVPLbNh = false;
      bool biQKDSSYcW = false;
      bool EChOuBlsBV = false;
      bool SeOjHLPrNs = false;
      bool SbwRZeIYFr = false;
      bool keEiTgpzPU = false;
      bool dSarPwUgCr = false;
      bool CaKjEbFQoP = false;
      bool rNnIjmZfPa = false;
      bool UPbrPAAECc = false;
      bool KbVNpKTUdq = false;
      bool aZKzcPeRHb = false;
      bool WoQbWlyRUE = false;
      bool aBNLFQqaSZ = false;
      bool SFBYAuFcPz = false;
      bool VhxZGUKtpD = false;
      bool LBzZPYLzsL = false;
      bool YDzgJQnqbb = false;
      bool gVBVirEnEj = false;
      string EscboITtYo;
      string nfJppVpWzH;
      string mygxrUFACI;
      string pomaTMnJwQ;
      string nxQBeyfIbB;
      string XloEeFMeiU;
      string CSrQyzriVd;
      string gfZhToheSt;
      string nwXBkEzhuO;
      string AJZbOUEACe;
      string GwmyTqLHko;
      string WgLofGuqft;
      string zJnHcXGyTy;
      string khcmmrJYgs;
      string rqxFqSxkwH;
      string ZNUHfwHeVw;
      string kNnmEoEXBm;
      string wVJlBHMiQK;
      string ZUBLYWNUHq;
      string jdDjIeDKAB;
      if(EscboITtYo == GwmyTqLHko){OYiIKDEhGX = true;}
      else if(GwmyTqLHko == EscboITtYo){UPbrPAAECc = true;}
      if(nfJppVpWzH == WgLofGuqft){iYOLVPLbNh = true;}
      else if(WgLofGuqft == nfJppVpWzH){KbVNpKTUdq = true;}
      if(mygxrUFACI == zJnHcXGyTy){biQKDSSYcW = true;}
      else if(zJnHcXGyTy == mygxrUFACI){aZKzcPeRHb = true;}
      if(pomaTMnJwQ == khcmmrJYgs){EChOuBlsBV = true;}
      else if(khcmmrJYgs == pomaTMnJwQ){WoQbWlyRUE = true;}
      if(nxQBeyfIbB == rqxFqSxkwH){SeOjHLPrNs = true;}
      else if(rqxFqSxkwH == nxQBeyfIbB){aBNLFQqaSZ = true;}
      if(XloEeFMeiU == ZNUHfwHeVw){SbwRZeIYFr = true;}
      else if(ZNUHfwHeVw == XloEeFMeiU){SFBYAuFcPz = true;}
      if(CSrQyzriVd == kNnmEoEXBm){keEiTgpzPU = true;}
      else if(kNnmEoEXBm == CSrQyzriVd){VhxZGUKtpD = true;}
      if(gfZhToheSt == wVJlBHMiQK){dSarPwUgCr = true;}
      if(nwXBkEzhuO == ZUBLYWNUHq){CaKjEbFQoP = true;}
      if(AJZbOUEACe == jdDjIeDKAB){rNnIjmZfPa = true;}
      while(wVJlBHMiQK == gfZhToheSt){LBzZPYLzsL = true;}
      while(ZUBLYWNUHq == ZUBLYWNUHq){YDzgJQnqbb = true;}
      while(jdDjIeDKAB == jdDjIeDKAB){gVBVirEnEj = true;}
      if(OYiIKDEhGX == true){OYiIKDEhGX = false;}
      if(iYOLVPLbNh == true){iYOLVPLbNh = false;}
      if(biQKDSSYcW == true){biQKDSSYcW = false;}
      if(EChOuBlsBV == true){EChOuBlsBV = false;}
      if(SeOjHLPrNs == true){SeOjHLPrNs = false;}
      if(SbwRZeIYFr == true){SbwRZeIYFr = false;}
      if(keEiTgpzPU == true){keEiTgpzPU = false;}
      if(dSarPwUgCr == true){dSarPwUgCr = false;}
      if(CaKjEbFQoP == true){CaKjEbFQoP = false;}
      if(rNnIjmZfPa == true){rNnIjmZfPa = false;}
      if(UPbrPAAECc == true){UPbrPAAECc = false;}
      if(KbVNpKTUdq == true){KbVNpKTUdq = false;}
      if(aZKzcPeRHb == true){aZKzcPeRHb = false;}
      if(WoQbWlyRUE == true){WoQbWlyRUE = false;}
      if(aBNLFQqaSZ == true){aBNLFQqaSZ = false;}
      if(SFBYAuFcPz == true){SFBYAuFcPz = false;}
      if(VhxZGUKtpD == true){VhxZGUKtpD = false;}
      if(LBzZPYLzsL == true){LBzZPYLzsL = false;}
      if(YDzgJQnqbb == true){YDzgJQnqbb = false;}
      if(gVBVirEnEj == true){gVBVirEnEj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLOTKDBSUV
{ 
  void uSDMbqMGDp()
  { 
      bool zrbjDzoWne = false;
      bool KBeFcjuLYY = false;
      bool iOtIrGTBpx = false;
      bool iHVQXTpHfX = false;
      bool bRcOKCVlrJ = false;
      bool NSiHgkxSrx = false;
      bool fmgpuCeNgJ = false;
      bool smfAwQkfxo = false;
      bool jgJgjQYOjm = false;
      bool VXPhqnkmTI = false;
      bool WHFiPZlhKP = false;
      bool zRUCMzdzGd = false;
      bool dPdtmVXxJI = false;
      bool fyMoScbaQJ = false;
      bool dpETmEDMVr = false;
      bool KkfodHcKut = false;
      bool CnYBjBEeji = false;
      bool WDiwzmLKGh = false;
      bool SKbRytRWLK = false;
      bool zQeWHpRCik = false;
      string nSExzgsGLi;
      string nkmBEFCUZt;
      string sfQIhQOMeG;
      string YhjbSaEwPy;
      string WWtGmsjQKj;
      string hQRCoHCwOh;
      string RgbFJFAKhc;
      string BFFaXWlJUn;
      string fxBtXHQhmK;
      string YHggfotnxh;
      string sZigibLpdR;
      string VraaBUehgC;
      string oSWWEsYXth;
      string cxMmuGNUKw;
      string wZDUofgGfL;
      string KLHtsZCMco;
      string CmuwoYfneu;
      string HKWjGOPBgX;
      string MSriXQoRsV;
      string DAqVtIeHfQ;
      if(nSExzgsGLi == sZigibLpdR){zrbjDzoWne = true;}
      else if(sZigibLpdR == nSExzgsGLi){WHFiPZlhKP = true;}
      if(nkmBEFCUZt == VraaBUehgC){KBeFcjuLYY = true;}
      else if(VraaBUehgC == nkmBEFCUZt){zRUCMzdzGd = true;}
      if(sfQIhQOMeG == oSWWEsYXth){iOtIrGTBpx = true;}
      else if(oSWWEsYXth == sfQIhQOMeG){dPdtmVXxJI = true;}
      if(YhjbSaEwPy == cxMmuGNUKw){iHVQXTpHfX = true;}
      else if(cxMmuGNUKw == YhjbSaEwPy){fyMoScbaQJ = true;}
      if(WWtGmsjQKj == wZDUofgGfL){bRcOKCVlrJ = true;}
      else if(wZDUofgGfL == WWtGmsjQKj){dpETmEDMVr = true;}
      if(hQRCoHCwOh == KLHtsZCMco){NSiHgkxSrx = true;}
      else if(KLHtsZCMco == hQRCoHCwOh){KkfodHcKut = true;}
      if(RgbFJFAKhc == CmuwoYfneu){fmgpuCeNgJ = true;}
      else if(CmuwoYfneu == RgbFJFAKhc){CnYBjBEeji = true;}
      if(BFFaXWlJUn == HKWjGOPBgX){smfAwQkfxo = true;}
      if(fxBtXHQhmK == MSriXQoRsV){jgJgjQYOjm = true;}
      if(YHggfotnxh == DAqVtIeHfQ){VXPhqnkmTI = true;}
      while(HKWjGOPBgX == BFFaXWlJUn){WDiwzmLKGh = true;}
      while(MSriXQoRsV == MSriXQoRsV){SKbRytRWLK = true;}
      while(DAqVtIeHfQ == DAqVtIeHfQ){zQeWHpRCik = true;}
      if(zrbjDzoWne == true){zrbjDzoWne = false;}
      if(KBeFcjuLYY == true){KBeFcjuLYY = false;}
      if(iOtIrGTBpx == true){iOtIrGTBpx = false;}
      if(iHVQXTpHfX == true){iHVQXTpHfX = false;}
      if(bRcOKCVlrJ == true){bRcOKCVlrJ = false;}
      if(NSiHgkxSrx == true){NSiHgkxSrx = false;}
      if(fmgpuCeNgJ == true){fmgpuCeNgJ = false;}
      if(smfAwQkfxo == true){smfAwQkfxo = false;}
      if(jgJgjQYOjm == true){jgJgjQYOjm = false;}
      if(VXPhqnkmTI == true){VXPhqnkmTI = false;}
      if(WHFiPZlhKP == true){WHFiPZlhKP = false;}
      if(zRUCMzdzGd == true){zRUCMzdzGd = false;}
      if(dPdtmVXxJI == true){dPdtmVXxJI = false;}
      if(fyMoScbaQJ == true){fyMoScbaQJ = false;}
      if(dpETmEDMVr == true){dpETmEDMVr = false;}
      if(KkfodHcKut == true){KkfodHcKut = false;}
      if(CnYBjBEeji == true){CnYBjBEeji = false;}
      if(WDiwzmLKGh == true){WDiwzmLKGh = false;}
      if(SKbRytRWLK == true){SKbRytRWLK = false;}
      if(zQeWHpRCik == true){zQeWHpRCik = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVLYKDJDIX
{ 
  void NWbHdsuViP()
  { 
      bool wyfqinxLcF = false;
      bool YwWUDaTPYJ = false;
      bool cOlMlFYFrW = false;
      bool uSmQoPbFnw = false;
      bool iwYfFkUiOM = false;
      bool hmgiPgLSEd = false;
      bool OqTFJFIGen = false;
      bool zNbcagpGGB = false;
      bool kpqfoIlEBI = false;
      bool EIBKgrcSWz = false;
      bool bODaNTLEIh = false;
      bool pEMCrYAnQB = false;
      bool TEFWipMQuh = false;
      bool DXjGZWlPRV = false;
      bool whuSRzwzSI = false;
      bool roCUfWIgqW = false;
      bool HtIZdSUFcU = false;
      bool ljVtElJlEj = false;
      bool sNympOUOaC = false;
      bool NFXtOCYVnz = false;
      string KpGpOZMAGq;
      string MysEjBxOTT;
      string GbXHIjOFGT;
      string JknCzBhZSM;
      string MYgZWtiXnU;
      string jTzQZhSyhd;
      string LGtlgbJqEh;
      string TWwGHguxkN;
      string ApRkjpkWbR;
      string iirnBGetsu;
      string jqSFBNXsJs;
      string mVNUcUoICq;
      string qlOmzjeHEB;
      string CAEocJWLjV;
      string RqNidNVWKg;
      string RVrCExbfGR;
      string hQnIplQXqT;
      string xcYfYzYfIl;
      string NHwXjfICke;
      string gqESmBDFrr;
      if(KpGpOZMAGq == jqSFBNXsJs){wyfqinxLcF = true;}
      else if(jqSFBNXsJs == KpGpOZMAGq){bODaNTLEIh = true;}
      if(MysEjBxOTT == mVNUcUoICq){YwWUDaTPYJ = true;}
      else if(mVNUcUoICq == MysEjBxOTT){pEMCrYAnQB = true;}
      if(GbXHIjOFGT == qlOmzjeHEB){cOlMlFYFrW = true;}
      else if(qlOmzjeHEB == GbXHIjOFGT){TEFWipMQuh = true;}
      if(JknCzBhZSM == CAEocJWLjV){uSmQoPbFnw = true;}
      else if(CAEocJWLjV == JknCzBhZSM){DXjGZWlPRV = true;}
      if(MYgZWtiXnU == RqNidNVWKg){iwYfFkUiOM = true;}
      else if(RqNidNVWKg == MYgZWtiXnU){whuSRzwzSI = true;}
      if(jTzQZhSyhd == RVrCExbfGR){hmgiPgLSEd = true;}
      else if(RVrCExbfGR == jTzQZhSyhd){roCUfWIgqW = true;}
      if(LGtlgbJqEh == hQnIplQXqT){OqTFJFIGen = true;}
      else if(hQnIplQXqT == LGtlgbJqEh){HtIZdSUFcU = true;}
      if(TWwGHguxkN == xcYfYzYfIl){zNbcagpGGB = true;}
      if(ApRkjpkWbR == NHwXjfICke){kpqfoIlEBI = true;}
      if(iirnBGetsu == gqESmBDFrr){EIBKgrcSWz = true;}
      while(xcYfYzYfIl == TWwGHguxkN){ljVtElJlEj = true;}
      while(NHwXjfICke == NHwXjfICke){sNympOUOaC = true;}
      while(gqESmBDFrr == gqESmBDFrr){NFXtOCYVnz = true;}
      if(wyfqinxLcF == true){wyfqinxLcF = false;}
      if(YwWUDaTPYJ == true){YwWUDaTPYJ = false;}
      if(cOlMlFYFrW == true){cOlMlFYFrW = false;}
      if(uSmQoPbFnw == true){uSmQoPbFnw = false;}
      if(iwYfFkUiOM == true){iwYfFkUiOM = false;}
      if(hmgiPgLSEd == true){hmgiPgLSEd = false;}
      if(OqTFJFIGen == true){OqTFJFIGen = false;}
      if(zNbcagpGGB == true){zNbcagpGGB = false;}
      if(kpqfoIlEBI == true){kpqfoIlEBI = false;}
      if(EIBKgrcSWz == true){EIBKgrcSWz = false;}
      if(bODaNTLEIh == true){bODaNTLEIh = false;}
      if(pEMCrYAnQB == true){pEMCrYAnQB = false;}
      if(TEFWipMQuh == true){TEFWipMQuh = false;}
      if(DXjGZWlPRV == true){DXjGZWlPRV = false;}
      if(whuSRzwzSI == true){whuSRzwzSI = false;}
      if(roCUfWIgqW == true){roCUfWIgqW = false;}
      if(HtIZdSUFcU == true){HtIZdSUFcU = false;}
      if(ljVtElJlEj == true){ljVtElJlEj = false;}
      if(sNympOUOaC == true){sNympOUOaC = false;}
      if(NFXtOCYVnz == true){NFXtOCYVnz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XEOXVPBOGZ
{ 
  void wRDxaqbPiQ()
  { 
      bool CVSMBpcSRi = false;
      bool juDUHIBMiq = false;
      bool JyAbQVjAkj = false;
      bool pKRMauHlbJ = false;
      bool CxkhUMMLOO = false;
      bool IMORREVque = false;
      bool FbggrYdqtM = false;
      bool APkZoMMSHE = false;
      bool JXlVbcwztW = false;
      bool YQpxDZPEow = false;
      bool hURCNrbncF = false;
      bool qDjqUhpKFO = false;
      bool bewWmjZnWO = false;
      bool wIcKVnFjIi = false;
      bool BHWofVgybU = false;
      bool jEyZTDYuOd = false;
      bool SnRNIiaYUg = false;
      bool cGCVNUHGqR = false;
      bool CaLBerJCqR = false;
      bool PJUdQMpIfx = false;
      string NFNqfRIgVJ;
      string fjYccczcUZ;
      string VLDgdUfyil;
      string IcWlUYBrBU;
      string OTbUjwOpkG;
      string SMGAEBBfMK;
      string kJxjBDMmIE;
      string aGazKCjixh;
      string GpMcSuWWgS;
      string WVepiEVrSg;
      string ibhgeLkGoC;
      string RSheEuxUQF;
      string gpFohFakQG;
      string fqQQyeIfxH;
      string KPgeBEmAln;
      string HBbMAsVryZ;
      string jAoiVZBQgZ;
      string mQXIuQJZnd;
      string RayczePDQE;
      string IQgWXKZyIb;
      if(NFNqfRIgVJ == ibhgeLkGoC){CVSMBpcSRi = true;}
      else if(ibhgeLkGoC == NFNqfRIgVJ){hURCNrbncF = true;}
      if(fjYccczcUZ == RSheEuxUQF){juDUHIBMiq = true;}
      else if(RSheEuxUQF == fjYccczcUZ){qDjqUhpKFO = true;}
      if(VLDgdUfyil == gpFohFakQG){JyAbQVjAkj = true;}
      else if(gpFohFakQG == VLDgdUfyil){bewWmjZnWO = true;}
      if(IcWlUYBrBU == fqQQyeIfxH){pKRMauHlbJ = true;}
      else if(fqQQyeIfxH == IcWlUYBrBU){wIcKVnFjIi = true;}
      if(OTbUjwOpkG == KPgeBEmAln){CxkhUMMLOO = true;}
      else if(KPgeBEmAln == OTbUjwOpkG){BHWofVgybU = true;}
      if(SMGAEBBfMK == HBbMAsVryZ){IMORREVque = true;}
      else if(HBbMAsVryZ == SMGAEBBfMK){jEyZTDYuOd = true;}
      if(kJxjBDMmIE == jAoiVZBQgZ){FbggrYdqtM = true;}
      else if(jAoiVZBQgZ == kJxjBDMmIE){SnRNIiaYUg = true;}
      if(aGazKCjixh == mQXIuQJZnd){APkZoMMSHE = true;}
      if(GpMcSuWWgS == RayczePDQE){JXlVbcwztW = true;}
      if(WVepiEVrSg == IQgWXKZyIb){YQpxDZPEow = true;}
      while(mQXIuQJZnd == aGazKCjixh){cGCVNUHGqR = true;}
      while(RayczePDQE == RayczePDQE){CaLBerJCqR = true;}
      while(IQgWXKZyIb == IQgWXKZyIb){PJUdQMpIfx = true;}
      if(CVSMBpcSRi == true){CVSMBpcSRi = false;}
      if(juDUHIBMiq == true){juDUHIBMiq = false;}
      if(JyAbQVjAkj == true){JyAbQVjAkj = false;}
      if(pKRMauHlbJ == true){pKRMauHlbJ = false;}
      if(CxkhUMMLOO == true){CxkhUMMLOO = false;}
      if(IMORREVque == true){IMORREVque = false;}
      if(FbggrYdqtM == true){FbggrYdqtM = false;}
      if(APkZoMMSHE == true){APkZoMMSHE = false;}
      if(JXlVbcwztW == true){JXlVbcwztW = false;}
      if(YQpxDZPEow == true){YQpxDZPEow = false;}
      if(hURCNrbncF == true){hURCNrbncF = false;}
      if(qDjqUhpKFO == true){qDjqUhpKFO = false;}
      if(bewWmjZnWO == true){bewWmjZnWO = false;}
      if(wIcKVnFjIi == true){wIcKVnFjIi = false;}
      if(BHWofVgybU == true){BHWofVgybU = false;}
      if(jEyZTDYuOd == true){jEyZTDYuOd = false;}
      if(SnRNIiaYUg == true){SnRNIiaYUg = false;}
      if(cGCVNUHGqR == true){cGCVNUHGqR = false;}
      if(CaLBerJCqR == true){CaLBerJCqR = false;}
      if(PJUdQMpIfx == true){PJUdQMpIfx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWQZUTAWZO
{ 
  void jABVTzSltW()
  { 
      bool rrBQONFdoW = false;
      bool aOUfjDxzHG = false;
      bool frYgFZGfCO = false;
      bool MOXUnNLeol = false;
      bool BtzEceNWAp = false;
      bool jThYnATULn = false;
      bool HZbaJLqArV = false;
      bool rSJUEksUDZ = false;
      bool MjeMdsgzfm = false;
      bool tpSBdbSYtR = false;
      bool nMddyRJMTD = false;
      bool HyRkaXtPwP = false;
      bool erUEbBzIpc = false;
      bool RTZllzFBNM = false;
      bool jTebfuYgZG = false;
      bool gDcemwrZCw = false;
      bool SBVplmYeza = false;
      bool SsBifKMrXf = false;
      bool cShjwOquzp = false;
      bool HfzRthyops = false;
      string RysBQqnbdi;
      string exJxOuwEkQ;
      string LlDkTcbjVy;
      string cdWXHbcoPl;
      string yTJQEFBMDG;
      string YudwketIhn;
      string OEGeGBakpl;
      string SHnzRqblfN;
      string bOfOZhAamb;
      string gTHbXtNdKD;
      string ePWRnQGeds;
      string CIbTLAXqEY;
      string BAxNFyAMaW;
      string dyaciMqOaJ;
      string aVwtYYrmQW;
      string WVYlCeRJLp;
      string QsDHOEgzkz;
      string IIPuxeDDnf;
      string GMwEAHYoaE;
      string thCjshSoeT;
      if(RysBQqnbdi == ePWRnQGeds){rrBQONFdoW = true;}
      else if(ePWRnQGeds == RysBQqnbdi){nMddyRJMTD = true;}
      if(exJxOuwEkQ == CIbTLAXqEY){aOUfjDxzHG = true;}
      else if(CIbTLAXqEY == exJxOuwEkQ){HyRkaXtPwP = true;}
      if(LlDkTcbjVy == BAxNFyAMaW){frYgFZGfCO = true;}
      else if(BAxNFyAMaW == LlDkTcbjVy){erUEbBzIpc = true;}
      if(cdWXHbcoPl == dyaciMqOaJ){MOXUnNLeol = true;}
      else if(dyaciMqOaJ == cdWXHbcoPl){RTZllzFBNM = true;}
      if(yTJQEFBMDG == aVwtYYrmQW){BtzEceNWAp = true;}
      else if(aVwtYYrmQW == yTJQEFBMDG){jTebfuYgZG = true;}
      if(YudwketIhn == WVYlCeRJLp){jThYnATULn = true;}
      else if(WVYlCeRJLp == YudwketIhn){gDcemwrZCw = true;}
      if(OEGeGBakpl == QsDHOEgzkz){HZbaJLqArV = true;}
      else if(QsDHOEgzkz == OEGeGBakpl){SBVplmYeza = true;}
      if(SHnzRqblfN == IIPuxeDDnf){rSJUEksUDZ = true;}
      if(bOfOZhAamb == GMwEAHYoaE){MjeMdsgzfm = true;}
      if(gTHbXtNdKD == thCjshSoeT){tpSBdbSYtR = true;}
      while(IIPuxeDDnf == SHnzRqblfN){SsBifKMrXf = true;}
      while(GMwEAHYoaE == GMwEAHYoaE){cShjwOquzp = true;}
      while(thCjshSoeT == thCjshSoeT){HfzRthyops = true;}
      if(rrBQONFdoW == true){rrBQONFdoW = false;}
      if(aOUfjDxzHG == true){aOUfjDxzHG = false;}
      if(frYgFZGfCO == true){frYgFZGfCO = false;}
      if(MOXUnNLeol == true){MOXUnNLeol = false;}
      if(BtzEceNWAp == true){BtzEceNWAp = false;}
      if(jThYnATULn == true){jThYnATULn = false;}
      if(HZbaJLqArV == true){HZbaJLqArV = false;}
      if(rSJUEksUDZ == true){rSJUEksUDZ = false;}
      if(MjeMdsgzfm == true){MjeMdsgzfm = false;}
      if(tpSBdbSYtR == true){tpSBdbSYtR = false;}
      if(nMddyRJMTD == true){nMddyRJMTD = false;}
      if(HyRkaXtPwP == true){HyRkaXtPwP = false;}
      if(erUEbBzIpc == true){erUEbBzIpc = false;}
      if(RTZllzFBNM == true){RTZllzFBNM = false;}
      if(jTebfuYgZG == true){jTebfuYgZG = false;}
      if(gDcemwrZCw == true){gDcemwrZCw = false;}
      if(SBVplmYeza == true){SBVplmYeza = false;}
      if(SsBifKMrXf == true){SsBifKMrXf = false;}
      if(cShjwOquzp == true){cShjwOquzp = false;}
      if(HfzRthyops == true){HfzRthyops = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOKVBGSYDE
{ 
  void YPFocrTqgX()
  { 
      bool rRuzLcoHNC = false;
      bool mVVdzBSXJg = false;
      bool MTDrYNITZc = false;
      bool cyhaIlYIQg = false;
      bool jSGqaqdcIk = false;
      bool YBfmlYNCay = false;
      bool UUgkYnmuVM = false;
      bool cKHcxtMLQg = false;
      bool ieLoDbSuni = false;
      bool XVgSLOlVSl = false;
      bool EhHuHNsCpr = false;
      bool LBltOpIqgx = false;
      bool VrHlnHdoQh = false;
      bool HqsdcBXQhp = false;
      bool hPEuXWjmDV = false;
      bool GtnVQLaUGA = false;
      bool jElIkUHHQN = false;
      bool RrJqOGmLOR = false;
      bool XqktbMCXNQ = false;
      bool ZCJgFddwKC = false;
      string PEGgEPXxar;
      string WrPaFaXVhz;
      string MuhYXszUgG;
      string MPJNqxtGTx;
      string zTJEpIEtUB;
      string HXmYoTWgJK;
      string PCQTeGiCjI;
      string fRCjAskdiO;
      string nFAeyocjXW;
      string ZNwIhwCpYi;
      string ZCJMUpUCYw;
      string isxuWJCkUo;
      string cydNhSUsBE;
      string puEzokwmJI;
      string TZKamgPBkY;
      string sQUiFaYweC;
      string VbAUGnnyGk;
      string NPbMVDnCZA;
      string DTIcKYaUtN;
      string MzHHlrZpUz;
      if(PEGgEPXxar == ZCJMUpUCYw){rRuzLcoHNC = true;}
      else if(ZCJMUpUCYw == PEGgEPXxar){EhHuHNsCpr = true;}
      if(WrPaFaXVhz == isxuWJCkUo){mVVdzBSXJg = true;}
      else if(isxuWJCkUo == WrPaFaXVhz){LBltOpIqgx = true;}
      if(MuhYXszUgG == cydNhSUsBE){MTDrYNITZc = true;}
      else if(cydNhSUsBE == MuhYXszUgG){VrHlnHdoQh = true;}
      if(MPJNqxtGTx == puEzokwmJI){cyhaIlYIQg = true;}
      else if(puEzokwmJI == MPJNqxtGTx){HqsdcBXQhp = true;}
      if(zTJEpIEtUB == TZKamgPBkY){jSGqaqdcIk = true;}
      else if(TZKamgPBkY == zTJEpIEtUB){hPEuXWjmDV = true;}
      if(HXmYoTWgJK == sQUiFaYweC){YBfmlYNCay = true;}
      else if(sQUiFaYweC == HXmYoTWgJK){GtnVQLaUGA = true;}
      if(PCQTeGiCjI == VbAUGnnyGk){UUgkYnmuVM = true;}
      else if(VbAUGnnyGk == PCQTeGiCjI){jElIkUHHQN = true;}
      if(fRCjAskdiO == NPbMVDnCZA){cKHcxtMLQg = true;}
      if(nFAeyocjXW == DTIcKYaUtN){ieLoDbSuni = true;}
      if(ZNwIhwCpYi == MzHHlrZpUz){XVgSLOlVSl = true;}
      while(NPbMVDnCZA == fRCjAskdiO){RrJqOGmLOR = true;}
      while(DTIcKYaUtN == DTIcKYaUtN){XqktbMCXNQ = true;}
      while(MzHHlrZpUz == MzHHlrZpUz){ZCJgFddwKC = true;}
      if(rRuzLcoHNC == true){rRuzLcoHNC = false;}
      if(mVVdzBSXJg == true){mVVdzBSXJg = false;}
      if(MTDrYNITZc == true){MTDrYNITZc = false;}
      if(cyhaIlYIQg == true){cyhaIlYIQg = false;}
      if(jSGqaqdcIk == true){jSGqaqdcIk = false;}
      if(YBfmlYNCay == true){YBfmlYNCay = false;}
      if(UUgkYnmuVM == true){UUgkYnmuVM = false;}
      if(cKHcxtMLQg == true){cKHcxtMLQg = false;}
      if(ieLoDbSuni == true){ieLoDbSuni = false;}
      if(XVgSLOlVSl == true){XVgSLOlVSl = false;}
      if(EhHuHNsCpr == true){EhHuHNsCpr = false;}
      if(LBltOpIqgx == true){LBltOpIqgx = false;}
      if(VrHlnHdoQh == true){VrHlnHdoQh = false;}
      if(HqsdcBXQhp == true){HqsdcBXQhp = false;}
      if(hPEuXWjmDV == true){hPEuXWjmDV = false;}
      if(GtnVQLaUGA == true){GtnVQLaUGA = false;}
      if(jElIkUHHQN == true){jElIkUHHQN = false;}
      if(RrJqOGmLOR == true){RrJqOGmLOR = false;}
      if(XqktbMCXNQ == true){XqktbMCXNQ = false;}
      if(ZCJgFddwKC == true){ZCJgFddwKC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBLIQZATZM
{ 
  void wPkFPbQkAh()
  { 
      bool rbMcJqNtKg = false;
      bool lFVFsLINBc = false;
      bool oCQdSwGNZO = false;
      bool hcMBaJCuqa = false;
      bool irfGxjYjPq = false;
      bool ohBjnpLiKM = false;
      bool jzTwzJsTdi = false;
      bool INVZtwVJfh = false;
      bool XWyhYAbcNk = false;
      bool ySjdpiYjHn = false;
      bool qFFfhaLaoq = false;
      bool TBDboNBkWz = false;
      bool gQFskpdriK = false;
      bool XlBrqRRSAx = false;
      bool nAmVRwOIoc = false;
      bool gmMIGZzMtq = false;
      bool xTqdThzLkW = false;
      bool wikYKgdjao = false;
      bool aVCGdkYskQ = false;
      bool SEXIAUIICi = false;
      string pAKZyObZrI;
      string uUethnJiyF;
      string MQMJnHtXgq;
      string rhXZRhlcHH;
      string BlcgLRuNdy;
      string xTHcgZnBlp;
      string TDrAQNxEcz;
      string CgbqDZmexW;
      string LgsitXZusr;
      string tjpQnxscQy;
      string TpkewQrQYG;
      string lIEPdmKJFs;
      string mBLkFRpKCF;
      string gJOzCUuOmc;
      string fJVlFlfalB;
      string mjWXKReAYd;
      string agOTZbsENI;
      string qwWcMcfYeT;
      string kPXARwmqnj;
      string ptoICyuCMc;
      if(pAKZyObZrI == TpkewQrQYG){rbMcJqNtKg = true;}
      else if(TpkewQrQYG == pAKZyObZrI){qFFfhaLaoq = true;}
      if(uUethnJiyF == lIEPdmKJFs){lFVFsLINBc = true;}
      else if(lIEPdmKJFs == uUethnJiyF){TBDboNBkWz = true;}
      if(MQMJnHtXgq == mBLkFRpKCF){oCQdSwGNZO = true;}
      else if(mBLkFRpKCF == MQMJnHtXgq){gQFskpdriK = true;}
      if(rhXZRhlcHH == gJOzCUuOmc){hcMBaJCuqa = true;}
      else if(gJOzCUuOmc == rhXZRhlcHH){XlBrqRRSAx = true;}
      if(BlcgLRuNdy == fJVlFlfalB){irfGxjYjPq = true;}
      else if(fJVlFlfalB == BlcgLRuNdy){nAmVRwOIoc = true;}
      if(xTHcgZnBlp == mjWXKReAYd){ohBjnpLiKM = true;}
      else if(mjWXKReAYd == xTHcgZnBlp){gmMIGZzMtq = true;}
      if(TDrAQNxEcz == agOTZbsENI){jzTwzJsTdi = true;}
      else if(agOTZbsENI == TDrAQNxEcz){xTqdThzLkW = true;}
      if(CgbqDZmexW == qwWcMcfYeT){INVZtwVJfh = true;}
      if(LgsitXZusr == kPXARwmqnj){XWyhYAbcNk = true;}
      if(tjpQnxscQy == ptoICyuCMc){ySjdpiYjHn = true;}
      while(qwWcMcfYeT == CgbqDZmexW){wikYKgdjao = true;}
      while(kPXARwmqnj == kPXARwmqnj){aVCGdkYskQ = true;}
      while(ptoICyuCMc == ptoICyuCMc){SEXIAUIICi = true;}
      if(rbMcJqNtKg == true){rbMcJqNtKg = false;}
      if(lFVFsLINBc == true){lFVFsLINBc = false;}
      if(oCQdSwGNZO == true){oCQdSwGNZO = false;}
      if(hcMBaJCuqa == true){hcMBaJCuqa = false;}
      if(irfGxjYjPq == true){irfGxjYjPq = false;}
      if(ohBjnpLiKM == true){ohBjnpLiKM = false;}
      if(jzTwzJsTdi == true){jzTwzJsTdi = false;}
      if(INVZtwVJfh == true){INVZtwVJfh = false;}
      if(XWyhYAbcNk == true){XWyhYAbcNk = false;}
      if(ySjdpiYjHn == true){ySjdpiYjHn = false;}
      if(qFFfhaLaoq == true){qFFfhaLaoq = false;}
      if(TBDboNBkWz == true){TBDboNBkWz = false;}
      if(gQFskpdriK == true){gQFskpdriK = false;}
      if(XlBrqRRSAx == true){XlBrqRRSAx = false;}
      if(nAmVRwOIoc == true){nAmVRwOIoc = false;}
      if(gmMIGZzMtq == true){gmMIGZzMtq = false;}
      if(xTqdThzLkW == true){xTqdThzLkW = false;}
      if(wikYKgdjao == true){wikYKgdjao = false;}
      if(aVCGdkYskQ == true){aVCGdkYskQ = false;}
      if(SEXIAUIICi == true){SEXIAUIICi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VAAZZRDJFJ
{ 
  void ldwiGWjmoJ()
  { 
      bool OgUGAIXHKF = false;
      bool RZPOSSrGUx = false;
      bool zOuEHjQqqS = false;
      bool hIpBRjpdkI = false;
      bool qTgjpIPIRQ = false;
      bool cfIlhAlQzP = false;
      bool qgPqXIiOxi = false;
      bool cOVMGfgKNy = false;
      bool UIYZpBzDTR = false;
      bool xZdURJDpMg = false;
      bool YAKinNKufB = false;
      bool SbCAuhHpAV = false;
      bool IetfkCjAuw = false;
      bool bqxfYTxokc = false;
      bool pEXRyVXcZi = false;
      bool BMpqXsGeyl = false;
      bool dKAjZbdVba = false;
      bool jRFXeEHchO = false;
      bool eGZMtPBGHf = false;
      bool NSqzzfEnrV = false;
      string ugmpgxFBkM;
      string HAumIQFocw;
      string seItuJlgOK;
      string RehFGpMDoS;
      string dhyfDZJUPY;
      string YJERjPYsuW;
      string KYlaubSpgS;
      string EBzJSKgbqU;
      string ARQokIaPUp;
      string RTISIEwXka;
      string HTnxUWJtzZ;
      string iwBZVrIwol;
      string BCUpBjsgBN;
      string NIpPMgcTUN;
      string yfPuHUShwP;
      string wzhyZEyyuj;
      string dcslLZFkMo;
      string PnbanUmYhf;
      string RKjlQOaqpI;
      string heXkjUmdig;
      if(ugmpgxFBkM == HTnxUWJtzZ){OgUGAIXHKF = true;}
      else if(HTnxUWJtzZ == ugmpgxFBkM){YAKinNKufB = true;}
      if(HAumIQFocw == iwBZVrIwol){RZPOSSrGUx = true;}
      else if(iwBZVrIwol == HAumIQFocw){SbCAuhHpAV = true;}
      if(seItuJlgOK == BCUpBjsgBN){zOuEHjQqqS = true;}
      else if(BCUpBjsgBN == seItuJlgOK){IetfkCjAuw = true;}
      if(RehFGpMDoS == NIpPMgcTUN){hIpBRjpdkI = true;}
      else if(NIpPMgcTUN == RehFGpMDoS){bqxfYTxokc = true;}
      if(dhyfDZJUPY == yfPuHUShwP){qTgjpIPIRQ = true;}
      else if(yfPuHUShwP == dhyfDZJUPY){pEXRyVXcZi = true;}
      if(YJERjPYsuW == wzhyZEyyuj){cfIlhAlQzP = true;}
      else if(wzhyZEyyuj == YJERjPYsuW){BMpqXsGeyl = true;}
      if(KYlaubSpgS == dcslLZFkMo){qgPqXIiOxi = true;}
      else if(dcslLZFkMo == KYlaubSpgS){dKAjZbdVba = true;}
      if(EBzJSKgbqU == PnbanUmYhf){cOVMGfgKNy = true;}
      if(ARQokIaPUp == RKjlQOaqpI){UIYZpBzDTR = true;}
      if(RTISIEwXka == heXkjUmdig){xZdURJDpMg = true;}
      while(PnbanUmYhf == EBzJSKgbqU){jRFXeEHchO = true;}
      while(RKjlQOaqpI == RKjlQOaqpI){eGZMtPBGHf = true;}
      while(heXkjUmdig == heXkjUmdig){NSqzzfEnrV = true;}
      if(OgUGAIXHKF == true){OgUGAIXHKF = false;}
      if(RZPOSSrGUx == true){RZPOSSrGUx = false;}
      if(zOuEHjQqqS == true){zOuEHjQqqS = false;}
      if(hIpBRjpdkI == true){hIpBRjpdkI = false;}
      if(qTgjpIPIRQ == true){qTgjpIPIRQ = false;}
      if(cfIlhAlQzP == true){cfIlhAlQzP = false;}
      if(qgPqXIiOxi == true){qgPqXIiOxi = false;}
      if(cOVMGfgKNy == true){cOVMGfgKNy = false;}
      if(UIYZpBzDTR == true){UIYZpBzDTR = false;}
      if(xZdURJDpMg == true){xZdURJDpMg = false;}
      if(YAKinNKufB == true){YAKinNKufB = false;}
      if(SbCAuhHpAV == true){SbCAuhHpAV = false;}
      if(IetfkCjAuw == true){IetfkCjAuw = false;}
      if(bqxfYTxokc == true){bqxfYTxokc = false;}
      if(pEXRyVXcZi == true){pEXRyVXcZi = false;}
      if(BMpqXsGeyl == true){BMpqXsGeyl = false;}
      if(dKAjZbdVba == true){dKAjZbdVba = false;}
      if(jRFXeEHchO == true){jRFXeEHchO = false;}
      if(eGZMtPBGHf == true){eGZMtPBGHf = false;}
      if(NSqzzfEnrV == true){NSqzzfEnrV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPAXRJJVYI
{ 
  void HHjPOAJkJs()
  { 
      bool EScDlwwiYP = false;
      bool AcmuwjhtpF = false;
      bool tlXOhrCXRK = false;
      bool djUVGNkDrG = false;
      bool cKcHgzPxjY = false;
      bool ckoOnRtNUs = false;
      bool sXQNkPHRoh = false;
      bool zeCicjIPhi = false;
      bool bFmshsuFhn = false;
      bool TXhyMEsPWQ = false;
      bool qyHCYxiFlE = false;
      bool IdelQmkXer = false;
      bool UBjBObwDWX = false;
      bool pssRqdykTk = false;
      bool JoTceprwgY = false;
      bool TVjewpOGnx = false;
      bool AfiNNPjNum = false;
      bool oADthehGVX = false;
      bool iAVxDUINVB = false;
      bool PqwVjdGFOO = false;
      string KNIAPpxuQs;
      string PenBImWVWT;
      string rSNdEFguDn;
      string LLftHclOfj;
      string mFVzrDBOnX;
      string tAWTqqzeuK;
      string JBrbhDzssf;
      string BHplgmxOkB;
      string DRHetKoLDQ;
      string cHTUZlNsRn;
      string DIUIWlKjmE;
      string skstGrtMhW;
      string OmocCtnULt;
      string YEwxxuwyIH;
      string AEXzXrNZOh;
      string rAKuZPSrFb;
      string yoYrennuwK;
      string wuEaVKPpEK;
      string fOGdCYtBWg;
      string cDrfILfeUi;
      if(KNIAPpxuQs == DIUIWlKjmE){EScDlwwiYP = true;}
      else if(DIUIWlKjmE == KNIAPpxuQs){qyHCYxiFlE = true;}
      if(PenBImWVWT == skstGrtMhW){AcmuwjhtpF = true;}
      else if(skstGrtMhW == PenBImWVWT){IdelQmkXer = true;}
      if(rSNdEFguDn == OmocCtnULt){tlXOhrCXRK = true;}
      else if(OmocCtnULt == rSNdEFguDn){UBjBObwDWX = true;}
      if(LLftHclOfj == YEwxxuwyIH){djUVGNkDrG = true;}
      else if(YEwxxuwyIH == LLftHclOfj){pssRqdykTk = true;}
      if(mFVzrDBOnX == AEXzXrNZOh){cKcHgzPxjY = true;}
      else if(AEXzXrNZOh == mFVzrDBOnX){JoTceprwgY = true;}
      if(tAWTqqzeuK == rAKuZPSrFb){ckoOnRtNUs = true;}
      else if(rAKuZPSrFb == tAWTqqzeuK){TVjewpOGnx = true;}
      if(JBrbhDzssf == yoYrennuwK){sXQNkPHRoh = true;}
      else if(yoYrennuwK == JBrbhDzssf){AfiNNPjNum = true;}
      if(BHplgmxOkB == wuEaVKPpEK){zeCicjIPhi = true;}
      if(DRHetKoLDQ == fOGdCYtBWg){bFmshsuFhn = true;}
      if(cHTUZlNsRn == cDrfILfeUi){TXhyMEsPWQ = true;}
      while(wuEaVKPpEK == BHplgmxOkB){oADthehGVX = true;}
      while(fOGdCYtBWg == fOGdCYtBWg){iAVxDUINVB = true;}
      while(cDrfILfeUi == cDrfILfeUi){PqwVjdGFOO = true;}
      if(EScDlwwiYP == true){EScDlwwiYP = false;}
      if(AcmuwjhtpF == true){AcmuwjhtpF = false;}
      if(tlXOhrCXRK == true){tlXOhrCXRK = false;}
      if(djUVGNkDrG == true){djUVGNkDrG = false;}
      if(cKcHgzPxjY == true){cKcHgzPxjY = false;}
      if(ckoOnRtNUs == true){ckoOnRtNUs = false;}
      if(sXQNkPHRoh == true){sXQNkPHRoh = false;}
      if(zeCicjIPhi == true){zeCicjIPhi = false;}
      if(bFmshsuFhn == true){bFmshsuFhn = false;}
      if(TXhyMEsPWQ == true){TXhyMEsPWQ = false;}
      if(qyHCYxiFlE == true){qyHCYxiFlE = false;}
      if(IdelQmkXer == true){IdelQmkXer = false;}
      if(UBjBObwDWX == true){UBjBObwDWX = false;}
      if(pssRqdykTk == true){pssRqdykTk = false;}
      if(JoTceprwgY == true){JoTceprwgY = false;}
      if(TVjewpOGnx == true){TVjewpOGnx = false;}
      if(AfiNNPjNum == true){AfiNNPjNum = false;}
      if(oADthehGVX == true){oADthehGVX = false;}
      if(iAVxDUINVB == true){iAVxDUINVB = false;}
      if(PqwVjdGFOO == true){PqwVjdGFOO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYYVKFYQAS
{ 
  void YnNcJehkbm()
  { 
      bool DmbbceWaAq = false;
      bool PKVPTluPPA = false;
      bool FtBTnQPKlF = false;
      bool YSXYoUtNtJ = false;
      bool EBaaTaEpik = false;
      bool cqMcAJkImL = false;
      bool PMntRxlwaz = false;
      bool rhUFwESazM = false;
      bool MYaBchFuYf = false;
      bool ilZisqMgIW = false;
      bool oHPjstWGfw = false;
      bool qJJZyqklQj = false;
      bool rpXuPFHlLF = false;
      bool qkScXFIqIh = false;
      bool KyPboYcAjC = false;
      bool FZPYdzjUTm = false;
      bool mjtaEFqfCs = false;
      bool htdhYsZuGp = false;
      bool cHBJzRUsyY = false;
      bool UnWVuaDoWi = false;
      string lJYDeeHFbA;
      string gBgSPjugfq;
      string mCKfWoQgpp;
      string chydRyGMPB;
      string OtMnuoXUqT;
      string wrJXhjyrgp;
      string OaPkWyCDAR;
      string ciQecroWkg;
      string RuoVtjYauh;
      string AOeZmmebQw;
      string lTTZpMbeto;
      string taHzXSlsqm;
      string ZbHSQODqqp;
      string MMFnuxaPeg;
      string IsgFmYGfBT;
      string BkkdWKLBIb;
      string JjmEbgVTDZ;
      string qVNJdftBer;
      string HWoXnbbbRj;
      string kZGDWXGbcF;
      if(lJYDeeHFbA == lTTZpMbeto){DmbbceWaAq = true;}
      else if(lTTZpMbeto == lJYDeeHFbA){oHPjstWGfw = true;}
      if(gBgSPjugfq == taHzXSlsqm){PKVPTluPPA = true;}
      else if(taHzXSlsqm == gBgSPjugfq){qJJZyqklQj = true;}
      if(mCKfWoQgpp == ZbHSQODqqp){FtBTnQPKlF = true;}
      else if(ZbHSQODqqp == mCKfWoQgpp){rpXuPFHlLF = true;}
      if(chydRyGMPB == MMFnuxaPeg){YSXYoUtNtJ = true;}
      else if(MMFnuxaPeg == chydRyGMPB){qkScXFIqIh = true;}
      if(OtMnuoXUqT == IsgFmYGfBT){EBaaTaEpik = true;}
      else if(IsgFmYGfBT == OtMnuoXUqT){KyPboYcAjC = true;}
      if(wrJXhjyrgp == BkkdWKLBIb){cqMcAJkImL = true;}
      else if(BkkdWKLBIb == wrJXhjyrgp){FZPYdzjUTm = true;}
      if(OaPkWyCDAR == JjmEbgVTDZ){PMntRxlwaz = true;}
      else if(JjmEbgVTDZ == OaPkWyCDAR){mjtaEFqfCs = true;}
      if(ciQecroWkg == qVNJdftBer){rhUFwESazM = true;}
      if(RuoVtjYauh == HWoXnbbbRj){MYaBchFuYf = true;}
      if(AOeZmmebQw == kZGDWXGbcF){ilZisqMgIW = true;}
      while(qVNJdftBer == ciQecroWkg){htdhYsZuGp = true;}
      while(HWoXnbbbRj == HWoXnbbbRj){cHBJzRUsyY = true;}
      while(kZGDWXGbcF == kZGDWXGbcF){UnWVuaDoWi = true;}
      if(DmbbceWaAq == true){DmbbceWaAq = false;}
      if(PKVPTluPPA == true){PKVPTluPPA = false;}
      if(FtBTnQPKlF == true){FtBTnQPKlF = false;}
      if(YSXYoUtNtJ == true){YSXYoUtNtJ = false;}
      if(EBaaTaEpik == true){EBaaTaEpik = false;}
      if(cqMcAJkImL == true){cqMcAJkImL = false;}
      if(PMntRxlwaz == true){PMntRxlwaz = false;}
      if(rhUFwESazM == true){rhUFwESazM = false;}
      if(MYaBchFuYf == true){MYaBchFuYf = false;}
      if(ilZisqMgIW == true){ilZisqMgIW = false;}
      if(oHPjstWGfw == true){oHPjstWGfw = false;}
      if(qJJZyqklQj == true){qJJZyqklQj = false;}
      if(rpXuPFHlLF == true){rpXuPFHlLF = false;}
      if(qkScXFIqIh == true){qkScXFIqIh = false;}
      if(KyPboYcAjC == true){KyPboYcAjC = false;}
      if(FZPYdzjUTm == true){FZPYdzjUTm = false;}
      if(mjtaEFqfCs == true){mjtaEFqfCs = false;}
      if(htdhYsZuGp == true){htdhYsZuGp = false;}
      if(cHBJzRUsyY == true){cHBJzRUsyY = false;}
      if(UnWVuaDoWi == true){UnWVuaDoWi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJXWBJIOUR
{ 
  void hfwkCXrgCn()
  { 
      bool GpkoBAdFaE = false;
      bool duHYSgQpFJ = false;
      bool VEIHKZftCp = false;
      bool yBTxiuofBy = false;
      bool TZwXJBQRNY = false;
      bool szaVlCgcda = false;
      bool UjDjGcbJoX = false;
      bool qjnHowHjyI = false;
      bool JOgcxyZxLg = false;
      bool NLCacjWMRg = false;
      bool ZHbogIKSgp = false;
      bool txeVRGDZlH = false;
      bool CdxIKfhNdF = false;
      bool YuSRiBlquo = false;
      bool mHQUlQggIW = false;
      bool fwZKduJSeB = false;
      bool ZxnaQzdNlP = false;
      bool TMexUuMcWs = false;
      bool yBEGYcUImm = false;
      bool rSLsPpSoDm = false;
      string luMZfQogYZ;
      string ZoZAqaqsXr;
      string DMxPuBPRRZ;
      string YSIjeHeHck;
      string WhhZaNYzXN;
      string yWjwiYywdd;
      string AWPyAHfoVi;
      string wjQmVVdXoh;
      string cPtDbChMBF;
      string JicyjzRjYS;
      string gidnROFxZM;
      string uaHwBjcMVx;
      string ZTnQYMGSDV;
      string EsyVAslFkN;
      string xklnJibgxz;
      string WFNasMuNOE;
      string HmtEIBbkuI;
      string yWaIAohzGp;
      string kZVDyyeWcn;
      string xXpgGKpgfI;
      if(luMZfQogYZ == gidnROFxZM){GpkoBAdFaE = true;}
      else if(gidnROFxZM == luMZfQogYZ){ZHbogIKSgp = true;}
      if(ZoZAqaqsXr == uaHwBjcMVx){duHYSgQpFJ = true;}
      else if(uaHwBjcMVx == ZoZAqaqsXr){txeVRGDZlH = true;}
      if(DMxPuBPRRZ == ZTnQYMGSDV){VEIHKZftCp = true;}
      else if(ZTnQYMGSDV == DMxPuBPRRZ){CdxIKfhNdF = true;}
      if(YSIjeHeHck == EsyVAslFkN){yBTxiuofBy = true;}
      else if(EsyVAslFkN == YSIjeHeHck){YuSRiBlquo = true;}
      if(WhhZaNYzXN == xklnJibgxz){TZwXJBQRNY = true;}
      else if(xklnJibgxz == WhhZaNYzXN){mHQUlQggIW = true;}
      if(yWjwiYywdd == WFNasMuNOE){szaVlCgcda = true;}
      else if(WFNasMuNOE == yWjwiYywdd){fwZKduJSeB = true;}
      if(AWPyAHfoVi == HmtEIBbkuI){UjDjGcbJoX = true;}
      else if(HmtEIBbkuI == AWPyAHfoVi){ZxnaQzdNlP = true;}
      if(wjQmVVdXoh == yWaIAohzGp){qjnHowHjyI = true;}
      if(cPtDbChMBF == kZVDyyeWcn){JOgcxyZxLg = true;}
      if(JicyjzRjYS == xXpgGKpgfI){NLCacjWMRg = true;}
      while(yWaIAohzGp == wjQmVVdXoh){TMexUuMcWs = true;}
      while(kZVDyyeWcn == kZVDyyeWcn){yBEGYcUImm = true;}
      while(xXpgGKpgfI == xXpgGKpgfI){rSLsPpSoDm = true;}
      if(GpkoBAdFaE == true){GpkoBAdFaE = false;}
      if(duHYSgQpFJ == true){duHYSgQpFJ = false;}
      if(VEIHKZftCp == true){VEIHKZftCp = false;}
      if(yBTxiuofBy == true){yBTxiuofBy = false;}
      if(TZwXJBQRNY == true){TZwXJBQRNY = false;}
      if(szaVlCgcda == true){szaVlCgcda = false;}
      if(UjDjGcbJoX == true){UjDjGcbJoX = false;}
      if(qjnHowHjyI == true){qjnHowHjyI = false;}
      if(JOgcxyZxLg == true){JOgcxyZxLg = false;}
      if(NLCacjWMRg == true){NLCacjWMRg = false;}
      if(ZHbogIKSgp == true){ZHbogIKSgp = false;}
      if(txeVRGDZlH == true){txeVRGDZlH = false;}
      if(CdxIKfhNdF == true){CdxIKfhNdF = false;}
      if(YuSRiBlquo == true){YuSRiBlquo = false;}
      if(mHQUlQggIW == true){mHQUlQggIW = false;}
      if(fwZKduJSeB == true){fwZKduJSeB = false;}
      if(ZxnaQzdNlP == true){ZxnaQzdNlP = false;}
      if(TMexUuMcWs == true){TMexUuMcWs = false;}
      if(yBEGYcUImm == true){yBEGYcUImm = false;}
      if(rSLsPpSoDm == true){rSLsPpSoDm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIASNRVHPM
{ 
  void hHLDihuZYs()
  { 
      bool drKCuzgKxj = false;
      bool VydmmzIBdS = false;
      bool MbyMDteFMu = false;
      bool idPgiIYkZX = false;
      bool qlpCjtEutD = false;
      bool hLUVtBsyzA = false;
      bool TaxBBqhwEd = false;
      bool ZWaGaakwbI = false;
      bool pjLIMWJsmg = false;
      bool PakYDPnoBs = false;
      bool MHpPcLkNtS = false;
      bool QxVpKjOnnd = false;
      bool hnJXOzlBDK = false;
      bool luuiwhswfB = false;
      bool luzTQREtOS = false;
      bool AzBWKXxSAc = false;
      bool YiKifUCmtc = false;
      bool qSIlqlopGx = false;
      bool tqmjJmtXXY = false;
      bool jZwCbDkPmw = false;
      string tBNTpjXPid;
      string jXRXmjPqln;
      string sPiaRRnkTu;
      string hELSYzWCNt;
      string wYQDrlkTtf;
      string KMFbDdSmBX;
      string wmwmueLyym;
      string NNcqrUzehe;
      string gUpnjVyiOu;
      string giApyJbcIN;
      string alUHSxiOji;
      string emFWqawICY;
      string fbjDGdNmri;
      string rVWTEuziUm;
      string mjzePtdczW;
      string MTZigyCRAn;
      string jwWAqIPkSw;
      string bNmPlwcEnM;
      string AjnUWXwnmF;
      string rhigDpNynG;
      if(tBNTpjXPid == alUHSxiOji){drKCuzgKxj = true;}
      else if(alUHSxiOji == tBNTpjXPid){MHpPcLkNtS = true;}
      if(jXRXmjPqln == emFWqawICY){VydmmzIBdS = true;}
      else if(emFWqawICY == jXRXmjPqln){QxVpKjOnnd = true;}
      if(sPiaRRnkTu == fbjDGdNmri){MbyMDteFMu = true;}
      else if(fbjDGdNmri == sPiaRRnkTu){hnJXOzlBDK = true;}
      if(hELSYzWCNt == rVWTEuziUm){idPgiIYkZX = true;}
      else if(rVWTEuziUm == hELSYzWCNt){luuiwhswfB = true;}
      if(wYQDrlkTtf == mjzePtdczW){qlpCjtEutD = true;}
      else if(mjzePtdczW == wYQDrlkTtf){luzTQREtOS = true;}
      if(KMFbDdSmBX == MTZigyCRAn){hLUVtBsyzA = true;}
      else if(MTZigyCRAn == KMFbDdSmBX){AzBWKXxSAc = true;}
      if(wmwmueLyym == jwWAqIPkSw){TaxBBqhwEd = true;}
      else if(jwWAqIPkSw == wmwmueLyym){YiKifUCmtc = true;}
      if(NNcqrUzehe == bNmPlwcEnM){ZWaGaakwbI = true;}
      if(gUpnjVyiOu == AjnUWXwnmF){pjLIMWJsmg = true;}
      if(giApyJbcIN == rhigDpNynG){PakYDPnoBs = true;}
      while(bNmPlwcEnM == NNcqrUzehe){qSIlqlopGx = true;}
      while(AjnUWXwnmF == AjnUWXwnmF){tqmjJmtXXY = true;}
      while(rhigDpNynG == rhigDpNynG){jZwCbDkPmw = true;}
      if(drKCuzgKxj == true){drKCuzgKxj = false;}
      if(VydmmzIBdS == true){VydmmzIBdS = false;}
      if(MbyMDteFMu == true){MbyMDteFMu = false;}
      if(idPgiIYkZX == true){idPgiIYkZX = false;}
      if(qlpCjtEutD == true){qlpCjtEutD = false;}
      if(hLUVtBsyzA == true){hLUVtBsyzA = false;}
      if(TaxBBqhwEd == true){TaxBBqhwEd = false;}
      if(ZWaGaakwbI == true){ZWaGaakwbI = false;}
      if(pjLIMWJsmg == true){pjLIMWJsmg = false;}
      if(PakYDPnoBs == true){PakYDPnoBs = false;}
      if(MHpPcLkNtS == true){MHpPcLkNtS = false;}
      if(QxVpKjOnnd == true){QxVpKjOnnd = false;}
      if(hnJXOzlBDK == true){hnJXOzlBDK = false;}
      if(luuiwhswfB == true){luuiwhswfB = false;}
      if(luzTQREtOS == true){luzTQREtOS = false;}
      if(AzBWKXxSAc == true){AzBWKXxSAc = false;}
      if(YiKifUCmtc == true){YiKifUCmtc = false;}
      if(qSIlqlopGx == true){qSIlqlopGx = false;}
      if(tqmjJmtXXY == true){tqmjJmtXXY = false;}
      if(jZwCbDkPmw == true){jZwCbDkPmw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WTVFPXPRQK
{ 
  void GEFguigVbG()
  { 
      bool eIFdPNdDEw = false;
      bool OUMNabRmqM = false;
      bool AHxriSzQOd = false;
      bool YSkAGTGxER = false;
      bool qegPOCEbDL = false;
      bool trVFiXKMtx = false;
      bool NNoZXujMHG = false;
      bool VThZVUahdg = false;
      bool NXNDjfwfQh = false;
      bool JsDHEcoGrS = false;
      bool RqTwoZJwiN = false;
      bool xciNiozlpq = false;
      bool yEuZxbQaUr = false;
      bool eTpKOVEQNJ = false;
      bool VAwDkfKpYP = false;
      bool cDPATNwtyM = false;
      bool JibphcmXyM = false;
      bool kiXgUyHroR = false;
      bool RZCFObEoqB = false;
      bool ZJRAAmXFUH = false;
      string uFuxDMuWgT;
      string UXohtHVIWe;
      string MwNONeDQNw;
      string NKOHomWIKF;
      string NNVtFYIqQh;
      string pDsWdyqgjY;
      string JeJkFKJgrG;
      string jMyQQzZTIn;
      string WLzfFKQqdp;
      string wpXlwhDknu;
      string OayJxcFcFd;
      string XXXwBxedet;
      string sSDCKtnLTh;
      string uoeNZuNohc;
      string FnkASXRbjz;
      string DZGsBwXwzD;
      string osIWhirJVG;
      string iouCoFgCil;
      string bMbUeUikMd;
      string WQoemLfNRi;
      if(uFuxDMuWgT == OayJxcFcFd){eIFdPNdDEw = true;}
      else if(OayJxcFcFd == uFuxDMuWgT){RqTwoZJwiN = true;}
      if(UXohtHVIWe == XXXwBxedet){OUMNabRmqM = true;}
      else if(XXXwBxedet == UXohtHVIWe){xciNiozlpq = true;}
      if(MwNONeDQNw == sSDCKtnLTh){AHxriSzQOd = true;}
      else if(sSDCKtnLTh == MwNONeDQNw){yEuZxbQaUr = true;}
      if(NKOHomWIKF == uoeNZuNohc){YSkAGTGxER = true;}
      else if(uoeNZuNohc == NKOHomWIKF){eTpKOVEQNJ = true;}
      if(NNVtFYIqQh == FnkASXRbjz){qegPOCEbDL = true;}
      else if(FnkASXRbjz == NNVtFYIqQh){VAwDkfKpYP = true;}
      if(pDsWdyqgjY == DZGsBwXwzD){trVFiXKMtx = true;}
      else if(DZGsBwXwzD == pDsWdyqgjY){cDPATNwtyM = true;}
      if(JeJkFKJgrG == osIWhirJVG){NNoZXujMHG = true;}
      else if(osIWhirJVG == JeJkFKJgrG){JibphcmXyM = true;}
      if(jMyQQzZTIn == iouCoFgCil){VThZVUahdg = true;}
      if(WLzfFKQqdp == bMbUeUikMd){NXNDjfwfQh = true;}
      if(wpXlwhDknu == WQoemLfNRi){JsDHEcoGrS = true;}
      while(iouCoFgCil == jMyQQzZTIn){kiXgUyHroR = true;}
      while(bMbUeUikMd == bMbUeUikMd){RZCFObEoqB = true;}
      while(WQoemLfNRi == WQoemLfNRi){ZJRAAmXFUH = true;}
      if(eIFdPNdDEw == true){eIFdPNdDEw = false;}
      if(OUMNabRmqM == true){OUMNabRmqM = false;}
      if(AHxriSzQOd == true){AHxriSzQOd = false;}
      if(YSkAGTGxER == true){YSkAGTGxER = false;}
      if(qegPOCEbDL == true){qegPOCEbDL = false;}
      if(trVFiXKMtx == true){trVFiXKMtx = false;}
      if(NNoZXujMHG == true){NNoZXujMHG = false;}
      if(VThZVUahdg == true){VThZVUahdg = false;}
      if(NXNDjfwfQh == true){NXNDjfwfQh = false;}
      if(JsDHEcoGrS == true){JsDHEcoGrS = false;}
      if(RqTwoZJwiN == true){RqTwoZJwiN = false;}
      if(xciNiozlpq == true){xciNiozlpq = false;}
      if(yEuZxbQaUr == true){yEuZxbQaUr = false;}
      if(eTpKOVEQNJ == true){eTpKOVEQNJ = false;}
      if(VAwDkfKpYP == true){VAwDkfKpYP = false;}
      if(cDPATNwtyM == true){cDPATNwtyM = false;}
      if(JibphcmXyM == true){JibphcmXyM = false;}
      if(kiXgUyHroR == true){kiXgUyHroR = false;}
      if(RZCFObEoqB == true){RZCFObEoqB = false;}
      if(ZJRAAmXFUH == true){ZJRAAmXFUH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IAGVVXNXXZ
{ 
  void qwcNXJJkFs()
  { 
      bool ZhrYNRjizD = false;
      bool ZPSMJlFXWA = false;
      bool DNPJcSBZFx = false;
      bool NqQlcZRlCm = false;
      bool qKPXgqPxTh = false;
      bool FrlpgLRiut = false;
      bool QKdCohygjj = false;
      bool TTVjIryrck = false;
      bool CEFWqVFaFQ = false;
      bool HipHWggMhz = false;
      bool siMiOlVBgo = false;
      bool MZGKqLEGLT = false;
      bool bXbTbjdNNb = false;
      bool KlJcrTrWHE = false;
      bool zEsQDhcfPK = false;
      bool bZAOWVHsHe = false;
      bool HImFdaQcRX = false;
      bool ThzGTXdKPt = false;
      bool GyyCzjktGV = false;
      bool LyOcxqQnlc = false;
      string ViIjstIgsu;
      string LpcQizYFIr;
      string UVPlrEybsW;
      string sJGufYtzMl;
      string uWVwPxdefB;
      string penImzTVro;
      string ufnWBCjhkK;
      string EZsVxxASWt;
      string ZTuqgOUxHf;
      string EXGXqOiyuN;
      string NwtVxPlRLp;
      string zBzxObkwpl;
      string gmZEGfTUei;
      string NBXIgdYZtQ;
      string cClRgDYIJP;
      string dlIIgaWpPQ;
      string wQmcbxcqQj;
      string CLCZIdAHWC;
      string HKKPFasOaG;
      string HiJcTLPJpj;
      if(ViIjstIgsu == NwtVxPlRLp){ZhrYNRjizD = true;}
      else if(NwtVxPlRLp == ViIjstIgsu){siMiOlVBgo = true;}
      if(LpcQizYFIr == zBzxObkwpl){ZPSMJlFXWA = true;}
      else if(zBzxObkwpl == LpcQizYFIr){MZGKqLEGLT = true;}
      if(UVPlrEybsW == gmZEGfTUei){DNPJcSBZFx = true;}
      else if(gmZEGfTUei == UVPlrEybsW){bXbTbjdNNb = true;}
      if(sJGufYtzMl == NBXIgdYZtQ){NqQlcZRlCm = true;}
      else if(NBXIgdYZtQ == sJGufYtzMl){KlJcrTrWHE = true;}
      if(uWVwPxdefB == cClRgDYIJP){qKPXgqPxTh = true;}
      else if(cClRgDYIJP == uWVwPxdefB){zEsQDhcfPK = true;}
      if(penImzTVro == dlIIgaWpPQ){FrlpgLRiut = true;}
      else if(dlIIgaWpPQ == penImzTVro){bZAOWVHsHe = true;}
      if(ufnWBCjhkK == wQmcbxcqQj){QKdCohygjj = true;}
      else if(wQmcbxcqQj == ufnWBCjhkK){HImFdaQcRX = true;}
      if(EZsVxxASWt == CLCZIdAHWC){TTVjIryrck = true;}
      if(ZTuqgOUxHf == HKKPFasOaG){CEFWqVFaFQ = true;}
      if(EXGXqOiyuN == HiJcTLPJpj){HipHWggMhz = true;}
      while(CLCZIdAHWC == EZsVxxASWt){ThzGTXdKPt = true;}
      while(HKKPFasOaG == HKKPFasOaG){GyyCzjktGV = true;}
      while(HiJcTLPJpj == HiJcTLPJpj){LyOcxqQnlc = true;}
      if(ZhrYNRjizD == true){ZhrYNRjizD = false;}
      if(ZPSMJlFXWA == true){ZPSMJlFXWA = false;}
      if(DNPJcSBZFx == true){DNPJcSBZFx = false;}
      if(NqQlcZRlCm == true){NqQlcZRlCm = false;}
      if(qKPXgqPxTh == true){qKPXgqPxTh = false;}
      if(FrlpgLRiut == true){FrlpgLRiut = false;}
      if(QKdCohygjj == true){QKdCohygjj = false;}
      if(TTVjIryrck == true){TTVjIryrck = false;}
      if(CEFWqVFaFQ == true){CEFWqVFaFQ = false;}
      if(HipHWggMhz == true){HipHWggMhz = false;}
      if(siMiOlVBgo == true){siMiOlVBgo = false;}
      if(MZGKqLEGLT == true){MZGKqLEGLT = false;}
      if(bXbTbjdNNb == true){bXbTbjdNNb = false;}
      if(KlJcrTrWHE == true){KlJcrTrWHE = false;}
      if(zEsQDhcfPK == true){zEsQDhcfPK = false;}
      if(bZAOWVHsHe == true){bZAOWVHsHe = false;}
      if(HImFdaQcRX == true){HImFdaQcRX = false;}
      if(ThzGTXdKPt == true){ThzGTXdKPt = false;}
      if(GyyCzjktGV == true){GyyCzjktGV = false;}
      if(LyOcxqQnlc == true){LyOcxqQnlc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KENNBCOKPT
{ 
  void LwhLxNmGEx()
  { 
      bool aDYchBaYAN = false;
      bool NXKUPcreMy = false;
      bool feDZtJCJCs = false;
      bool VDoQKyBznp = false;
      bool IUoUUWpalP = false;
      bool FRWrSuAziX = false;
      bool zRVGqJhsKR = false;
      bool bspWoLpiFW = false;
      bool SaWlmDgxyO = false;
      bool xCQPpqyhcK = false;
      bool nxPUnMbACH = false;
      bool ERsLFYtjTm = false;
      bool bkuuTZbZfx = false;
      bool MIFthVKByZ = false;
      bool bgtpJfIEKR = false;
      bool xOOphCBTAO = false;
      bool kBTFuwLycj = false;
      bool NrksKuqFln = false;
      bool QXONAxtPLe = false;
      bool TpBjoZMnuN = false;
      string JaGNNAAjHA;
      string MuMlRiMPKm;
      string YslsIKRIWE;
      string EdeafmCeLO;
      string shQzgtxXSq;
      string tUNrwQnMFC;
      string hqNDuhPlFe;
      string ghEwtqblMN;
      string MtpeJjPmeO;
      string yoYIgBUNEy;
      string dLRmJMQRyF;
      string oCzqpmBhsL;
      string RcGpgqIuPr;
      string WOhOiAbCVx;
      string TyoZZuogSs;
      string AmUrfBFaGS;
      string EUBFhaUkIo;
      string KyMurSngQk;
      string CacWrjtohh;
      string uBwCsyxjqz;
      if(JaGNNAAjHA == dLRmJMQRyF){aDYchBaYAN = true;}
      else if(dLRmJMQRyF == JaGNNAAjHA){nxPUnMbACH = true;}
      if(MuMlRiMPKm == oCzqpmBhsL){NXKUPcreMy = true;}
      else if(oCzqpmBhsL == MuMlRiMPKm){ERsLFYtjTm = true;}
      if(YslsIKRIWE == RcGpgqIuPr){feDZtJCJCs = true;}
      else if(RcGpgqIuPr == YslsIKRIWE){bkuuTZbZfx = true;}
      if(EdeafmCeLO == WOhOiAbCVx){VDoQKyBznp = true;}
      else if(WOhOiAbCVx == EdeafmCeLO){MIFthVKByZ = true;}
      if(shQzgtxXSq == TyoZZuogSs){IUoUUWpalP = true;}
      else if(TyoZZuogSs == shQzgtxXSq){bgtpJfIEKR = true;}
      if(tUNrwQnMFC == AmUrfBFaGS){FRWrSuAziX = true;}
      else if(AmUrfBFaGS == tUNrwQnMFC){xOOphCBTAO = true;}
      if(hqNDuhPlFe == EUBFhaUkIo){zRVGqJhsKR = true;}
      else if(EUBFhaUkIo == hqNDuhPlFe){kBTFuwLycj = true;}
      if(ghEwtqblMN == KyMurSngQk){bspWoLpiFW = true;}
      if(MtpeJjPmeO == CacWrjtohh){SaWlmDgxyO = true;}
      if(yoYIgBUNEy == uBwCsyxjqz){xCQPpqyhcK = true;}
      while(KyMurSngQk == ghEwtqblMN){NrksKuqFln = true;}
      while(CacWrjtohh == CacWrjtohh){QXONAxtPLe = true;}
      while(uBwCsyxjqz == uBwCsyxjqz){TpBjoZMnuN = true;}
      if(aDYchBaYAN == true){aDYchBaYAN = false;}
      if(NXKUPcreMy == true){NXKUPcreMy = false;}
      if(feDZtJCJCs == true){feDZtJCJCs = false;}
      if(VDoQKyBznp == true){VDoQKyBznp = false;}
      if(IUoUUWpalP == true){IUoUUWpalP = false;}
      if(FRWrSuAziX == true){FRWrSuAziX = false;}
      if(zRVGqJhsKR == true){zRVGqJhsKR = false;}
      if(bspWoLpiFW == true){bspWoLpiFW = false;}
      if(SaWlmDgxyO == true){SaWlmDgxyO = false;}
      if(xCQPpqyhcK == true){xCQPpqyhcK = false;}
      if(nxPUnMbACH == true){nxPUnMbACH = false;}
      if(ERsLFYtjTm == true){ERsLFYtjTm = false;}
      if(bkuuTZbZfx == true){bkuuTZbZfx = false;}
      if(MIFthVKByZ == true){MIFthVKByZ = false;}
      if(bgtpJfIEKR == true){bgtpJfIEKR = false;}
      if(xOOphCBTAO == true){xOOphCBTAO = false;}
      if(kBTFuwLycj == true){kBTFuwLycj = false;}
      if(NrksKuqFln == true){NrksKuqFln = false;}
      if(QXONAxtPLe == true){QXONAxtPLe = false;}
      if(TpBjoZMnuN == true){TpBjoZMnuN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMUHVMOLHJ
{ 
  void LzOKGampfN()
  { 
      bool tWKnTetNdh = false;
      bool GrypWxMUNU = false;
      bool thRyRuOrZZ = false;
      bool MHbsjFXWeR = false;
      bool KfZHcUWUGi = false;
      bool antAaMFLWX = false;
      bool QBnEVzQEGR = false;
      bool YppuKOIJVw = false;
      bool YtkpyXNaSW = false;
      bool zMzGBIqUkc = false;
      bool ERNoJkyypM = false;
      bool DuoazVPxFx = false;
      bool loliRMqitB = false;
      bool WmYrqGfwgN = false;
      bool ZOkFTEWXHe = false;
      bool rtOnqPfdWw = false;
      bool tPEnpQWxjs = false;
      bool oTQrXXDfPM = false;
      bool pSbOIbXkBa = false;
      bool aBYjSKJwPD = false;
      string PZRSbEpKPp;
      string PVKnuSjEOu;
      string jRZUWGlWcf;
      string zqIZGRecXz;
      string eyTJYOUSKt;
      string NjPchxAxwU;
      string RShipXMkgc;
      string nHgPPkxQuH;
      string lTMiRPafrJ;
      string RggChMPkTA;
      string CikgFGDANw;
      string AjCnhyGzRa;
      string wgsXLGaegD;
      string VMxtFDhfcL;
      string MaRwIgerTi;
      string FQSsDVoNUy;
      string eXSKZmmHhe;
      string PZWFOVOxOd;
      string bhLyxEsEpj;
      string NUKdfnIHVV;
      if(PZRSbEpKPp == CikgFGDANw){tWKnTetNdh = true;}
      else if(CikgFGDANw == PZRSbEpKPp){ERNoJkyypM = true;}
      if(PVKnuSjEOu == AjCnhyGzRa){GrypWxMUNU = true;}
      else if(AjCnhyGzRa == PVKnuSjEOu){DuoazVPxFx = true;}
      if(jRZUWGlWcf == wgsXLGaegD){thRyRuOrZZ = true;}
      else if(wgsXLGaegD == jRZUWGlWcf){loliRMqitB = true;}
      if(zqIZGRecXz == VMxtFDhfcL){MHbsjFXWeR = true;}
      else if(VMxtFDhfcL == zqIZGRecXz){WmYrqGfwgN = true;}
      if(eyTJYOUSKt == MaRwIgerTi){KfZHcUWUGi = true;}
      else if(MaRwIgerTi == eyTJYOUSKt){ZOkFTEWXHe = true;}
      if(NjPchxAxwU == FQSsDVoNUy){antAaMFLWX = true;}
      else if(FQSsDVoNUy == NjPchxAxwU){rtOnqPfdWw = true;}
      if(RShipXMkgc == eXSKZmmHhe){QBnEVzQEGR = true;}
      else if(eXSKZmmHhe == RShipXMkgc){tPEnpQWxjs = true;}
      if(nHgPPkxQuH == PZWFOVOxOd){YppuKOIJVw = true;}
      if(lTMiRPafrJ == bhLyxEsEpj){YtkpyXNaSW = true;}
      if(RggChMPkTA == NUKdfnIHVV){zMzGBIqUkc = true;}
      while(PZWFOVOxOd == nHgPPkxQuH){oTQrXXDfPM = true;}
      while(bhLyxEsEpj == bhLyxEsEpj){pSbOIbXkBa = true;}
      while(NUKdfnIHVV == NUKdfnIHVV){aBYjSKJwPD = true;}
      if(tWKnTetNdh == true){tWKnTetNdh = false;}
      if(GrypWxMUNU == true){GrypWxMUNU = false;}
      if(thRyRuOrZZ == true){thRyRuOrZZ = false;}
      if(MHbsjFXWeR == true){MHbsjFXWeR = false;}
      if(KfZHcUWUGi == true){KfZHcUWUGi = false;}
      if(antAaMFLWX == true){antAaMFLWX = false;}
      if(QBnEVzQEGR == true){QBnEVzQEGR = false;}
      if(YppuKOIJVw == true){YppuKOIJVw = false;}
      if(YtkpyXNaSW == true){YtkpyXNaSW = false;}
      if(zMzGBIqUkc == true){zMzGBIqUkc = false;}
      if(ERNoJkyypM == true){ERNoJkyypM = false;}
      if(DuoazVPxFx == true){DuoazVPxFx = false;}
      if(loliRMqitB == true){loliRMqitB = false;}
      if(WmYrqGfwgN == true){WmYrqGfwgN = false;}
      if(ZOkFTEWXHe == true){ZOkFTEWXHe = false;}
      if(rtOnqPfdWw == true){rtOnqPfdWw = false;}
      if(tPEnpQWxjs == true){tPEnpQWxjs = false;}
      if(oTQrXXDfPM == true){oTQrXXDfPM = false;}
      if(pSbOIbXkBa == true){pSbOIbXkBa = false;}
      if(aBYjSKJwPD == true){aBYjSKJwPD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGKFXXFAJR
{ 
  void epEuoaLnMU()
  { 
      bool AaIHTnaZOZ = false;
      bool oqOBXVhyhH = false;
      bool tPJKrmYEqK = false;
      bool UoUZJXaOaK = false;
      bool BJsdMzSVOq = false;
      bool IGeSejRyPg = false;
      bool PVhDFAVnqz = false;
      bool tTWWFjVexr = false;
      bool UCpzCNKCuY = false;
      bool FcytufapXM = false;
      bool cddOwojHMt = false;
      bool OlAWMMfiBq = false;
      bool oTsRsRUcbZ = false;
      bool IfGjPpYaCN = false;
      bool dCoAKTbbgi = false;
      bool ArngWJjLUe = false;
      bool THflkiePHV = false;
      bool mEfnNmdsHZ = false;
      bool orurZQqZNG = false;
      bool GMFXsWVCOb = false;
      string ccpgoAilis;
      string toYBypMwQb;
      string xUzylHZYTe;
      string mteeDxxaid;
      string ajFQXAlOuC;
      string zcRSpHdrtg;
      string ZJRDFAJsyB;
      string rlNmBMPhal;
      string VLdRfKbMnu;
      string SFfBDQRBKW;
      string prQtJMPdRd;
      string ruQILOfAXu;
      string XxFChmGLjj;
      string tNXDuctiIS;
      string tytJDXnWpn;
      string kRdPzrlNLV;
      string FDsgjdXNNh;
      string TwqEBYCuzK;
      string yjVuzbiIEC;
      string pgXlNpENZY;
      if(ccpgoAilis == prQtJMPdRd){AaIHTnaZOZ = true;}
      else if(prQtJMPdRd == ccpgoAilis){cddOwojHMt = true;}
      if(toYBypMwQb == ruQILOfAXu){oqOBXVhyhH = true;}
      else if(ruQILOfAXu == toYBypMwQb){OlAWMMfiBq = true;}
      if(xUzylHZYTe == XxFChmGLjj){tPJKrmYEqK = true;}
      else if(XxFChmGLjj == xUzylHZYTe){oTsRsRUcbZ = true;}
      if(mteeDxxaid == tNXDuctiIS){UoUZJXaOaK = true;}
      else if(tNXDuctiIS == mteeDxxaid){IfGjPpYaCN = true;}
      if(ajFQXAlOuC == tytJDXnWpn){BJsdMzSVOq = true;}
      else if(tytJDXnWpn == ajFQXAlOuC){dCoAKTbbgi = true;}
      if(zcRSpHdrtg == kRdPzrlNLV){IGeSejRyPg = true;}
      else if(kRdPzrlNLV == zcRSpHdrtg){ArngWJjLUe = true;}
      if(ZJRDFAJsyB == FDsgjdXNNh){PVhDFAVnqz = true;}
      else if(FDsgjdXNNh == ZJRDFAJsyB){THflkiePHV = true;}
      if(rlNmBMPhal == TwqEBYCuzK){tTWWFjVexr = true;}
      if(VLdRfKbMnu == yjVuzbiIEC){UCpzCNKCuY = true;}
      if(SFfBDQRBKW == pgXlNpENZY){FcytufapXM = true;}
      while(TwqEBYCuzK == rlNmBMPhal){mEfnNmdsHZ = true;}
      while(yjVuzbiIEC == yjVuzbiIEC){orurZQqZNG = true;}
      while(pgXlNpENZY == pgXlNpENZY){GMFXsWVCOb = true;}
      if(AaIHTnaZOZ == true){AaIHTnaZOZ = false;}
      if(oqOBXVhyhH == true){oqOBXVhyhH = false;}
      if(tPJKrmYEqK == true){tPJKrmYEqK = false;}
      if(UoUZJXaOaK == true){UoUZJXaOaK = false;}
      if(BJsdMzSVOq == true){BJsdMzSVOq = false;}
      if(IGeSejRyPg == true){IGeSejRyPg = false;}
      if(PVhDFAVnqz == true){PVhDFAVnqz = false;}
      if(tTWWFjVexr == true){tTWWFjVexr = false;}
      if(UCpzCNKCuY == true){UCpzCNKCuY = false;}
      if(FcytufapXM == true){FcytufapXM = false;}
      if(cddOwojHMt == true){cddOwojHMt = false;}
      if(OlAWMMfiBq == true){OlAWMMfiBq = false;}
      if(oTsRsRUcbZ == true){oTsRsRUcbZ = false;}
      if(IfGjPpYaCN == true){IfGjPpYaCN = false;}
      if(dCoAKTbbgi == true){dCoAKTbbgi = false;}
      if(ArngWJjLUe == true){ArngWJjLUe = false;}
      if(THflkiePHV == true){THflkiePHV = false;}
      if(mEfnNmdsHZ == true){mEfnNmdsHZ = false;}
      if(orurZQqZNG == true){orurZQqZNG = false;}
      if(GMFXsWVCOb == true){GMFXsWVCOb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBFCYQBJQS
{ 
  void QEYGpcONIG()
  { 
      bool qGVMPkJObE = false;
      bool BFPWHShsPS = false;
      bool UkynEMkkVX = false;
      bool UFYlcgKLSk = false;
      bool giZIFrRjbf = false;
      bool iDsKsGIhID = false;
      bool zYrEiwfcsZ = false;
      bool IWaelkKphM = false;
      bool tAIooRLNrW = false;
      bool YcCPkHpVZI = false;
      bool LoqCXLcOYI = false;
      bool uSzwIyQCPQ = false;
      bool jRjWBeUKsd = false;
      bool toPZAFJFRc = false;
      bool oxojaGcGHl = false;
      bool qmGIXsETBr = false;
      bool qRUuNGCZuC = false;
      bool oKklamcAut = false;
      bool CNDHlHiGBH = false;
      bool BoEYkXbtWT = false;
      string yQoRVDMimw;
      string FVGlkXYnxc;
      string KJIxFKLaCW;
      string SSjxWwEtfx;
      string HLVIAKGNhV;
      string aBWFeoHqMK;
      string rkgPdmlIPo;
      string TeHzUznzwt;
      string DxrguQudSh;
      string nMhVFVdFeN;
      string XyysBwsWje;
      string AItRGtrzUM;
      string qIpgAGxltz;
      string VhUiWFzzey;
      string XYtmgfSQOL;
      string cdjRVPHQru;
      string zGbkJSnLtB;
      string urUVoRNCAU;
      string nfXiVqxCMG;
      string xhHjzQwIdO;
      if(yQoRVDMimw == XyysBwsWje){qGVMPkJObE = true;}
      else if(XyysBwsWje == yQoRVDMimw){LoqCXLcOYI = true;}
      if(FVGlkXYnxc == AItRGtrzUM){BFPWHShsPS = true;}
      else if(AItRGtrzUM == FVGlkXYnxc){uSzwIyQCPQ = true;}
      if(KJIxFKLaCW == qIpgAGxltz){UkynEMkkVX = true;}
      else if(qIpgAGxltz == KJIxFKLaCW){jRjWBeUKsd = true;}
      if(SSjxWwEtfx == VhUiWFzzey){UFYlcgKLSk = true;}
      else if(VhUiWFzzey == SSjxWwEtfx){toPZAFJFRc = true;}
      if(HLVIAKGNhV == XYtmgfSQOL){giZIFrRjbf = true;}
      else if(XYtmgfSQOL == HLVIAKGNhV){oxojaGcGHl = true;}
      if(aBWFeoHqMK == cdjRVPHQru){iDsKsGIhID = true;}
      else if(cdjRVPHQru == aBWFeoHqMK){qmGIXsETBr = true;}
      if(rkgPdmlIPo == zGbkJSnLtB){zYrEiwfcsZ = true;}
      else if(zGbkJSnLtB == rkgPdmlIPo){qRUuNGCZuC = true;}
      if(TeHzUznzwt == urUVoRNCAU){IWaelkKphM = true;}
      if(DxrguQudSh == nfXiVqxCMG){tAIooRLNrW = true;}
      if(nMhVFVdFeN == xhHjzQwIdO){YcCPkHpVZI = true;}
      while(urUVoRNCAU == TeHzUznzwt){oKklamcAut = true;}
      while(nfXiVqxCMG == nfXiVqxCMG){CNDHlHiGBH = true;}
      while(xhHjzQwIdO == xhHjzQwIdO){BoEYkXbtWT = true;}
      if(qGVMPkJObE == true){qGVMPkJObE = false;}
      if(BFPWHShsPS == true){BFPWHShsPS = false;}
      if(UkynEMkkVX == true){UkynEMkkVX = false;}
      if(UFYlcgKLSk == true){UFYlcgKLSk = false;}
      if(giZIFrRjbf == true){giZIFrRjbf = false;}
      if(iDsKsGIhID == true){iDsKsGIhID = false;}
      if(zYrEiwfcsZ == true){zYrEiwfcsZ = false;}
      if(IWaelkKphM == true){IWaelkKphM = false;}
      if(tAIooRLNrW == true){tAIooRLNrW = false;}
      if(YcCPkHpVZI == true){YcCPkHpVZI = false;}
      if(LoqCXLcOYI == true){LoqCXLcOYI = false;}
      if(uSzwIyQCPQ == true){uSzwIyQCPQ = false;}
      if(jRjWBeUKsd == true){jRjWBeUKsd = false;}
      if(toPZAFJFRc == true){toPZAFJFRc = false;}
      if(oxojaGcGHl == true){oxojaGcGHl = false;}
      if(qmGIXsETBr == true){qmGIXsETBr = false;}
      if(qRUuNGCZuC == true){qRUuNGCZuC = false;}
      if(oKklamcAut == true){oKklamcAut = false;}
      if(CNDHlHiGBH == true){CNDHlHiGBH = false;}
      if(BoEYkXbtWT == true){BoEYkXbtWT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGQYGPJGMN
{ 
  void mHIPZnsZsd()
  { 
      bool gyNABKflTH = false;
      bool WzQCgQInqX = false;
      bool riyzwJpzoD = false;
      bool uoeseVKmmP = false;
      bool ujFMjnQxtA = false;
      bool sKoOtyzNEq = false;
      bool TgwQMgTXWK = false;
      bool GUBacIdlPI = false;
      bool ssEnJkAPyg = false;
      bool WwiuwNnoAD = false;
      bool TsaitYIOll = false;
      bool TNyuyacHGb = false;
      bool fEYonJlGeO = false;
      bool TokMozSVtk = false;
      bool blcMMIymwV = false;
      bool kfhYWOTktk = false;
      bool lCiXReblFy = false;
      bool HGNUAtbMbe = false;
      bool KyJJdnGMoa = false;
      bool fgaJzYCFth = false;
      string hUSwdxrViI;
      string BZXBopEgyd;
      string cfgefSMEAh;
      string krQyjmunjA;
      string uhIChUsyVi;
      string uRGadCmmPL;
      string knVAXIIYQC;
      string tPwxhuWewK;
      string YNhRlTloUg;
      string zIXXPHLHeZ;
      string LUhSnfUJrh;
      string eIpFmWGENE;
      string WTDiDlqYga;
      string iPzWzDfPcG;
      string ybxlCpRSjr;
      string BHsZCrQyPB;
      string owcQzOITFj;
      string qpaHFtVRgM;
      string UXnnZbVZUG;
      string mhzbRCzfmm;
      if(hUSwdxrViI == LUhSnfUJrh){gyNABKflTH = true;}
      else if(LUhSnfUJrh == hUSwdxrViI){TsaitYIOll = true;}
      if(BZXBopEgyd == eIpFmWGENE){WzQCgQInqX = true;}
      else if(eIpFmWGENE == BZXBopEgyd){TNyuyacHGb = true;}
      if(cfgefSMEAh == WTDiDlqYga){riyzwJpzoD = true;}
      else if(WTDiDlqYga == cfgefSMEAh){fEYonJlGeO = true;}
      if(krQyjmunjA == iPzWzDfPcG){uoeseVKmmP = true;}
      else if(iPzWzDfPcG == krQyjmunjA){TokMozSVtk = true;}
      if(uhIChUsyVi == ybxlCpRSjr){ujFMjnQxtA = true;}
      else if(ybxlCpRSjr == uhIChUsyVi){blcMMIymwV = true;}
      if(uRGadCmmPL == BHsZCrQyPB){sKoOtyzNEq = true;}
      else if(BHsZCrQyPB == uRGadCmmPL){kfhYWOTktk = true;}
      if(knVAXIIYQC == owcQzOITFj){TgwQMgTXWK = true;}
      else if(owcQzOITFj == knVAXIIYQC){lCiXReblFy = true;}
      if(tPwxhuWewK == qpaHFtVRgM){GUBacIdlPI = true;}
      if(YNhRlTloUg == UXnnZbVZUG){ssEnJkAPyg = true;}
      if(zIXXPHLHeZ == mhzbRCzfmm){WwiuwNnoAD = true;}
      while(qpaHFtVRgM == tPwxhuWewK){HGNUAtbMbe = true;}
      while(UXnnZbVZUG == UXnnZbVZUG){KyJJdnGMoa = true;}
      while(mhzbRCzfmm == mhzbRCzfmm){fgaJzYCFth = true;}
      if(gyNABKflTH == true){gyNABKflTH = false;}
      if(WzQCgQInqX == true){WzQCgQInqX = false;}
      if(riyzwJpzoD == true){riyzwJpzoD = false;}
      if(uoeseVKmmP == true){uoeseVKmmP = false;}
      if(ujFMjnQxtA == true){ujFMjnQxtA = false;}
      if(sKoOtyzNEq == true){sKoOtyzNEq = false;}
      if(TgwQMgTXWK == true){TgwQMgTXWK = false;}
      if(GUBacIdlPI == true){GUBacIdlPI = false;}
      if(ssEnJkAPyg == true){ssEnJkAPyg = false;}
      if(WwiuwNnoAD == true){WwiuwNnoAD = false;}
      if(TsaitYIOll == true){TsaitYIOll = false;}
      if(TNyuyacHGb == true){TNyuyacHGb = false;}
      if(fEYonJlGeO == true){fEYonJlGeO = false;}
      if(TokMozSVtk == true){TokMozSVtk = false;}
      if(blcMMIymwV == true){blcMMIymwV = false;}
      if(kfhYWOTktk == true){kfhYWOTktk = false;}
      if(lCiXReblFy == true){lCiXReblFy = false;}
      if(HGNUAtbMbe == true){HGNUAtbMbe = false;}
      if(KyJJdnGMoa == true){KyJJdnGMoa = false;}
      if(fgaJzYCFth == true){fgaJzYCFth = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUSYUVGAUI
{ 
  void hOqRSkZjjS()
  { 
      bool pYkAxKhAen = false;
      bool tFLBeuCuFy = false;
      bool wbPWyjGYbQ = false;
      bool mNIVXsfdpF = false;
      bool NQUnlgAAAt = false;
      bool NdcQcNIOCM = false;
      bool EJYNAgxocl = false;
      bool PYEzkfHbkQ = false;
      bool iGXhDJjqsK = false;
      bool kQbdBEqGmE = false;
      bool jLWOdoYcfw = false;
      bool FfdkcxkqKq = false;
      bool xGwRAzxZyg = false;
      bool oBofgXiIDN = false;
      bool jGKwEEmpBD = false;
      bool SAwuHdOENe = false;
      bool ryezHEqxEE = false;
      bool ObmwGpuAMw = false;
      bool MGYtOoEsYC = false;
      bool JduYVkaLoA = false;
      string SPlHmybFxa;
      string cGnaffVUeB;
      string QyYPTJWrNH;
      string yisSFuJCQl;
      string aNbUQFgLfD;
      string lCJgfTqVnd;
      string ajrobtNUUk;
      string WTDraDVDzO;
      string bKLJUwYLmk;
      string EmNmKqUlrV;
      string rLqufSyQGc;
      string xmVZBQXhTf;
      string UBhifiFQhj;
      string hiLcWPTQcC;
      string yIFKnRQnlt;
      string SmSMBpcHPx;
      string MgiWtNbrCk;
      string xHERhMwXuO;
      string RQemQuQzbf;
      string mMBfoQYiPZ;
      if(SPlHmybFxa == rLqufSyQGc){pYkAxKhAen = true;}
      else if(rLqufSyQGc == SPlHmybFxa){jLWOdoYcfw = true;}
      if(cGnaffVUeB == xmVZBQXhTf){tFLBeuCuFy = true;}
      else if(xmVZBQXhTf == cGnaffVUeB){FfdkcxkqKq = true;}
      if(QyYPTJWrNH == UBhifiFQhj){wbPWyjGYbQ = true;}
      else if(UBhifiFQhj == QyYPTJWrNH){xGwRAzxZyg = true;}
      if(yisSFuJCQl == hiLcWPTQcC){mNIVXsfdpF = true;}
      else if(hiLcWPTQcC == yisSFuJCQl){oBofgXiIDN = true;}
      if(aNbUQFgLfD == yIFKnRQnlt){NQUnlgAAAt = true;}
      else if(yIFKnRQnlt == aNbUQFgLfD){jGKwEEmpBD = true;}
      if(lCJgfTqVnd == SmSMBpcHPx){NdcQcNIOCM = true;}
      else if(SmSMBpcHPx == lCJgfTqVnd){SAwuHdOENe = true;}
      if(ajrobtNUUk == MgiWtNbrCk){EJYNAgxocl = true;}
      else if(MgiWtNbrCk == ajrobtNUUk){ryezHEqxEE = true;}
      if(WTDraDVDzO == xHERhMwXuO){PYEzkfHbkQ = true;}
      if(bKLJUwYLmk == RQemQuQzbf){iGXhDJjqsK = true;}
      if(EmNmKqUlrV == mMBfoQYiPZ){kQbdBEqGmE = true;}
      while(xHERhMwXuO == WTDraDVDzO){ObmwGpuAMw = true;}
      while(RQemQuQzbf == RQemQuQzbf){MGYtOoEsYC = true;}
      while(mMBfoQYiPZ == mMBfoQYiPZ){JduYVkaLoA = true;}
      if(pYkAxKhAen == true){pYkAxKhAen = false;}
      if(tFLBeuCuFy == true){tFLBeuCuFy = false;}
      if(wbPWyjGYbQ == true){wbPWyjGYbQ = false;}
      if(mNIVXsfdpF == true){mNIVXsfdpF = false;}
      if(NQUnlgAAAt == true){NQUnlgAAAt = false;}
      if(NdcQcNIOCM == true){NdcQcNIOCM = false;}
      if(EJYNAgxocl == true){EJYNAgxocl = false;}
      if(PYEzkfHbkQ == true){PYEzkfHbkQ = false;}
      if(iGXhDJjqsK == true){iGXhDJjqsK = false;}
      if(kQbdBEqGmE == true){kQbdBEqGmE = false;}
      if(jLWOdoYcfw == true){jLWOdoYcfw = false;}
      if(FfdkcxkqKq == true){FfdkcxkqKq = false;}
      if(xGwRAzxZyg == true){xGwRAzxZyg = false;}
      if(oBofgXiIDN == true){oBofgXiIDN = false;}
      if(jGKwEEmpBD == true){jGKwEEmpBD = false;}
      if(SAwuHdOENe == true){SAwuHdOENe = false;}
      if(ryezHEqxEE == true){ryezHEqxEE = false;}
      if(ObmwGpuAMw == true){ObmwGpuAMw = false;}
      if(MGYtOoEsYC == true){MGYtOoEsYC = false;}
      if(JduYVkaLoA == true){JduYVkaLoA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJYSHRZVWT
{ 
  void dDmIniLZsL()
  { 
      bool tYjEBZzyWC = false;
      bool bUPVudFgDN = false;
      bool cfRAymIbwo = false;
      bool oDFNpDCTtJ = false;
      bool CnwjbDhYRZ = false;
      bool QpSBBNHjGN = false;
      bool RXCgMYPBeq = false;
      bool blmtKoigYt = false;
      bool EiJWYzjDMc = false;
      bool wSNfqelOXD = false;
      bool mgsaydCXpM = false;
      bool dZKLJiOfIN = false;
      bool nLnCtIYGDf = false;
      bool DUJVGXohYt = false;
      bool wMNAyWHBWI = false;
      bool PFFKObrqfo = false;
      bool FwUJJJPnEk = false;
      bool sgHOQbxnEX = false;
      bool BWjuQxOzHe = false;
      bool fyBinAqEqo = false;
      string HcGTURjULH;
      string AztiMCWHaU;
      string KCgZUhbsfe;
      string QdFFApOwxR;
      string ZDykxeebHR;
      string RmTwPEwgzm;
      string oqogpWsohW;
      string nZJJuGDwbp;
      string CzlOMdJJou;
      string shxKbhORta;
      string kotjdrcKAI;
      string BAEIjpEZTM;
      string MiAldFbzgM;
      string rkBAENFBkT;
      string AzJftscoal;
      string doyhOBoHGX;
      string QdcmQPyDEW;
      string kDozLMZTrk;
      string cmXuiCmSlD;
      string XxuNDWWWOd;
      if(HcGTURjULH == kotjdrcKAI){tYjEBZzyWC = true;}
      else if(kotjdrcKAI == HcGTURjULH){mgsaydCXpM = true;}
      if(AztiMCWHaU == BAEIjpEZTM){bUPVudFgDN = true;}
      else if(BAEIjpEZTM == AztiMCWHaU){dZKLJiOfIN = true;}
      if(KCgZUhbsfe == MiAldFbzgM){cfRAymIbwo = true;}
      else if(MiAldFbzgM == KCgZUhbsfe){nLnCtIYGDf = true;}
      if(QdFFApOwxR == rkBAENFBkT){oDFNpDCTtJ = true;}
      else if(rkBAENFBkT == QdFFApOwxR){DUJVGXohYt = true;}
      if(ZDykxeebHR == AzJftscoal){CnwjbDhYRZ = true;}
      else if(AzJftscoal == ZDykxeebHR){wMNAyWHBWI = true;}
      if(RmTwPEwgzm == doyhOBoHGX){QpSBBNHjGN = true;}
      else if(doyhOBoHGX == RmTwPEwgzm){PFFKObrqfo = true;}
      if(oqogpWsohW == QdcmQPyDEW){RXCgMYPBeq = true;}
      else if(QdcmQPyDEW == oqogpWsohW){FwUJJJPnEk = true;}
      if(nZJJuGDwbp == kDozLMZTrk){blmtKoigYt = true;}
      if(CzlOMdJJou == cmXuiCmSlD){EiJWYzjDMc = true;}
      if(shxKbhORta == XxuNDWWWOd){wSNfqelOXD = true;}
      while(kDozLMZTrk == nZJJuGDwbp){sgHOQbxnEX = true;}
      while(cmXuiCmSlD == cmXuiCmSlD){BWjuQxOzHe = true;}
      while(XxuNDWWWOd == XxuNDWWWOd){fyBinAqEqo = true;}
      if(tYjEBZzyWC == true){tYjEBZzyWC = false;}
      if(bUPVudFgDN == true){bUPVudFgDN = false;}
      if(cfRAymIbwo == true){cfRAymIbwo = false;}
      if(oDFNpDCTtJ == true){oDFNpDCTtJ = false;}
      if(CnwjbDhYRZ == true){CnwjbDhYRZ = false;}
      if(QpSBBNHjGN == true){QpSBBNHjGN = false;}
      if(RXCgMYPBeq == true){RXCgMYPBeq = false;}
      if(blmtKoigYt == true){blmtKoigYt = false;}
      if(EiJWYzjDMc == true){EiJWYzjDMc = false;}
      if(wSNfqelOXD == true){wSNfqelOXD = false;}
      if(mgsaydCXpM == true){mgsaydCXpM = false;}
      if(dZKLJiOfIN == true){dZKLJiOfIN = false;}
      if(nLnCtIYGDf == true){nLnCtIYGDf = false;}
      if(DUJVGXohYt == true){DUJVGXohYt = false;}
      if(wMNAyWHBWI == true){wMNAyWHBWI = false;}
      if(PFFKObrqfo == true){PFFKObrqfo = false;}
      if(FwUJJJPnEk == true){FwUJJJPnEk = false;}
      if(sgHOQbxnEX == true){sgHOQbxnEX = false;}
      if(BWjuQxOzHe == true){BWjuQxOzHe = false;}
      if(fyBinAqEqo == true){fyBinAqEqo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYFTFDUYPA
{ 
  void RkGdIEULny()
  { 
      bool OpHJjSyAhk = false;
      bool HQpLgQjODx = false;
      bool OHYyoKFSpI = false;
      bool gfTbLQsDXo = false;
      bool kFTLxMBNch = false;
      bool mPrspHQJUY = false;
      bool NeKZDbwNAP = false;
      bool XfqNLInNAb = false;
      bool IqpIURmakE = false;
      bool AjiybGtsHV = false;
      bool PmNMJHXdgh = false;
      bool TCIrQWoCFk = false;
      bool nVcwPnwrlF = false;
      bool NtFeMVcdyM = false;
      bool sIsDjxaphE = false;
      bool RrnVgtKRwV = false;
      bool KerbTYxdft = false;
      bool sKDrrebZLS = false;
      bool MGKgnUFixS = false;
      bool KLgcCOQRiL = false;
      string AKKfDjhhux;
      string KAWBElXVLl;
      string tpFsfUXnDs;
      string lerXCErFgO;
      string mfxZoZHdmz;
      string xcMSGJFRzi;
      string LtdBKeHyzz;
      string sRowzNreDG;
      string MtBDwJRZQr;
      string zaFyDrBuOK;
      string RIemGenQSs;
      string RZOsVRsaFB;
      string NhhHASMpsH;
      string LwPsoDONxQ;
      string UBGXZYLLbl;
      string yapNwiaWmn;
      string RxWLgUJVER;
      string CfcofLaJga;
      string GANHIjGCwF;
      string cqZJyWeupF;
      if(AKKfDjhhux == RIemGenQSs){OpHJjSyAhk = true;}
      else if(RIemGenQSs == AKKfDjhhux){PmNMJHXdgh = true;}
      if(KAWBElXVLl == RZOsVRsaFB){HQpLgQjODx = true;}
      else if(RZOsVRsaFB == KAWBElXVLl){TCIrQWoCFk = true;}
      if(tpFsfUXnDs == NhhHASMpsH){OHYyoKFSpI = true;}
      else if(NhhHASMpsH == tpFsfUXnDs){nVcwPnwrlF = true;}
      if(lerXCErFgO == LwPsoDONxQ){gfTbLQsDXo = true;}
      else if(LwPsoDONxQ == lerXCErFgO){NtFeMVcdyM = true;}
      if(mfxZoZHdmz == UBGXZYLLbl){kFTLxMBNch = true;}
      else if(UBGXZYLLbl == mfxZoZHdmz){sIsDjxaphE = true;}
      if(xcMSGJFRzi == yapNwiaWmn){mPrspHQJUY = true;}
      else if(yapNwiaWmn == xcMSGJFRzi){RrnVgtKRwV = true;}
      if(LtdBKeHyzz == RxWLgUJVER){NeKZDbwNAP = true;}
      else if(RxWLgUJVER == LtdBKeHyzz){KerbTYxdft = true;}
      if(sRowzNreDG == CfcofLaJga){XfqNLInNAb = true;}
      if(MtBDwJRZQr == GANHIjGCwF){IqpIURmakE = true;}
      if(zaFyDrBuOK == cqZJyWeupF){AjiybGtsHV = true;}
      while(CfcofLaJga == sRowzNreDG){sKDrrebZLS = true;}
      while(GANHIjGCwF == GANHIjGCwF){MGKgnUFixS = true;}
      while(cqZJyWeupF == cqZJyWeupF){KLgcCOQRiL = true;}
      if(OpHJjSyAhk == true){OpHJjSyAhk = false;}
      if(HQpLgQjODx == true){HQpLgQjODx = false;}
      if(OHYyoKFSpI == true){OHYyoKFSpI = false;}
      if(gfTbLQsDXo == true){gfTbLQsDXo = false;}
      if(kFTLxMBNch == true){kFTLxMBNch = false;}
      if(mPrspHQJUY == true){mPrspHQJUY = false;}
      if(NeKZDbwNAP == true){NeKZDbwNAP = false;}
      if(XfqNLInNAb == true){XfqNLInNAb = false;}
      if(IqpIURmakE == true){IqpIURmakE = false;}
      if(AjiybGtsHV == true){AjiybGtsHV = false;}
      if(PmNMJHXdgh == true){PmNMJHXdgh = false;}
      if(TCIrQWoCFk == true){TCIrQWoCFk = false;}
      if(nVcwPnwrlF == true){nVcwPnwrlF = false;}
      if(NtFeMVcdyM == true){NtFeMVcdyM = false;}
      if(sIsDjxaphE == true){sIsDjxaphE = false;}
      if(RrnVgtKRwV == true){RrnVgtKRwV = false;}
      if(KerbTYxdft == true){KerbTYxdft = false;}
      if(sKDrrebZLS == true){sKDrrebZLS = false;}
      if(MGKgnUFixS == true){MGKgnUFixS = false;}
      if(KLgcCOQRiL == true){KLgcCOQRiL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXGHQZKVBZ
{ 
  void bNVUhdhrjr()
  { 
      bool sFSzybIQcu = false;
      bool OJhlsaXMNM = false;
      bool PjXbRmrwwD = false;
      bool oiopVDFBYi = false;
      bool OlDIzbIKpR = false;
      bool ekicSIgqhK = false;
      bool jLTZGfTqQo = false;
      bool VVmdydgPbo = false;
      bool egGeYDzMXM = false;
      bool WOTOzCRcCS = false;
      bool IRtAwIyFdo = false;
      bool bQOsfCFoBC = false;
      bool gHSDSGCYew = false;
      bool LDNJgMmFhP = false;
      bool FthijFAZhw = false;
      bool xbbzkAypho = false;
      bool GYahcYDFMT = false;
      bool OzHkwmYjTN = false;
      bool GbqhyjaNXf = false;
      bool OxXsIfSzGL = false;
      string OsoaqZZOFI;
      string HYGBUlDWYt;
      string aqgkWpQPOx;
      string VPCgzDzNiP;
      string OHuBuRTjqg;
      string XQufMWMEEB;
      string JKAHlqWYCQ;
      string mpmIfSwepE;
      string VfXgZFUVTb;
      string quIhGDHmPE;
      string uthZtgdlAt;
      string agNzeclShg;
      string VAFZYqgEBb;
      string KIPlJbyxmr;
      string aiUZBKgIDc;
      string QnFihtoHBD;
      string zYkYiSQbpD;
      string eofoFmefYO;
      string JXBXLWCgDO;
      string lqwisCxwph;
      if(OsoaqZZOFI == uthZtgdlAt){sFSzybIQcu = true;}
      else if(uthZtgdlAt == OsoaqZZOFI){IRtAwIyFdo = true;}
      if(HYGBUlDWYt == agNzeclShg){OJhlsaXMNM = true;}
      else if(agNzeclShg == HYGBUlDWYt){bQOsfCFoBC = true;}
      if(aqgkWpQPOx == VAFZYqgEBb){PjXbRmrwwD = true;}
      else if(VAFZYqgEBb == aqgkWpQPOx){gHSDSGCYew = true;}
      if(VPCgzDzNiP == KIPlJbyxmr){oiopVDFBYi = true;}
      else if(KIPlJbyxmr == VPCgzDzNiP){LDNJgMmFhP = true;}
      if(OHuBuRTjqg == aiUZBKgIDc){OlDIzbIKpR = true;}
      else if(aiUZBKgIDc == OHuBuRTjqg){FthijFAZhw = true;}
      if(XQufMWMEEB == QnFihtoHBD){ekicSIgqhK = true;}
      else if(QnFihtoHBD == XQufMWMEEB){xbbzkAypho = true;}
      if(JKAHlqWYCQ == zYkYiSQbpD){jLTZGfTqQo = true;}
      else if(zYkYiSQbpD == JKAHlqWYCQ){GYahcYDFMT = true;}
      if(mpmIfSwepE == eofoFmefYO){VVmdydgPbo = true;}
      if(VfXgZFUVTb == JXBXLWCgDO){egGeYDzMXM = true;}
      if(quIhGDHmPE == lqwisCxwph){WOTOzCRcCS = true;}
      while(eofoFmefYO == mpmIfSwepE){OzHkwmYjTN = true;}
      while(JXBXLWCgDO == JXBXLWCgDO){GbqhyjaNXf = true;}
      while(lqwisCxwph == lqwisCxwph){OxXsIfSzGL = true;}
      if(sFSzybIQcu == true){sFSzybIQcu = false;}
      if(OJhlsaXMNM == true){OJhlsaXMNM = false;}
      if(PjXbRmrwwD == true){PjXbRmrwwD = false;}
      if(oiopVDFBYi == true){oiopVDFBYi = false;}
      if(OlDIzbIKpR == true){OlDIzbIKpR = false;}
      if(ekicSIgqhK == true){ekicSIgqhK = false;}
      if(jLTZGfTqQo == true){jLTZGfTqQo = false;}
      if(VVmdydgPbo == true){VVmdydgPbo = false;}
      if(egGeYDzMXM == true){egGeYDzMXM = false;}
      if(WOTOzCRcCS == true){WOTOzCRcCS = false;}
      if(IRtAwIyFdo == true){IRtAwIyFdo = false;}
      if(bQOsfCFoBC == true){bQOsfCFoBC = false;}
      if(gHSDSGCYew == true){gHSDSGCYew = false;}
      if(LDNJgMmFhP == true){LDNJgMmFhP = false;}
      if(FthijFAZhw == true){FthijFAZhw = false;}
      if(xbbzkAypho == true){xbbzkAypho = false;}
      if(GYahcYDFMT == true){GYahcYDFMT = false;}
      if(OzHkwmYjTN == true){OzHkwmYjTN = false;}
      if(GbqhyjaNXf == true){GbqhyjaNXf = false;}
      if(OxXsIfSzGL == true){OxXsIfSzGL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOETTPMEVG
{ 
  void txILYTjFaC()
  { 
      bool LqhYaLXWDk = false;
      bool HVmFKqMkuy = false;
      bool pchFuLpAYE = false;
      bool JudNZiYNgC = false;
      bool KZKfJzCmWX = false;
      bool qyKZVhIcdO = false;
      bool VXyyaMrZea = false;
      bool RyDrnQSCuu = false;
      bool JCcANLjDqq = false;
      bool ZujSflaLFx = false;
      bool GcHwFstRlF = false;
      bool OGhhFTtykP = false;
      bool bohnBWNkMB = false;
      bool pHwxnftgtT = false;
      bool QSRkcSMCML = false;
      bool rbaoVRtTti = false;
      bool eJFjPHJjsY = false;
      bool ZNDQyJWxKh = false;
      bool JLYAJNgHbW = false;
      bool lZlLoHMgVU = false;
      string QeMHVogyRV;
      string VTPeujDKhN;
      string RCNVPlxBdt;
      string ftWjJldqiV;
      string rZiOZTLInI;
      string WBooLOQqqj;
      string qeUXpaxfVJ;
      string FMaMVrSzuw;
      string ZoNUWdFhXu;
      string UmAzdMELYz;
      string WfmeCKacST;
      string uRuuKCRzAL;
      string VPHZnRLbiJ;
      string mHauYtBiRM;
      string CcOEACqEoa;
      string tFKMdHYMpk;
      string yzsJfmqAVQ;
      string AhgmIsACZk;
      string aHlHOhxNRQ;
      string UorgODiFYM;
      if(QeMHVogyRV == WfmeCKacST){LqhYaLXWDk = true;}
      else if(WfmeCKacST == QeMHVogyRV){GcHwFstRlF = true;}
      if(VTPeujDKhN == uRuuKCRzAL){HVmFKqMkuy = true;}
      else if(uRuuKCRzAL == VTPeujDKhN){OGhhFTtykP = true;}
      if(RCNVPlxBdt == VPHZnRLbiJ){pchFuLpAYE = true;}
      else if(VPHZnRLbiJ == RCNVPlxBdt){bohnBWNkMB = true;}
      if(ftWjJldqiV == mHauYtBiRM){JudNZiYNgC = true;}
      else if(mHauYtBiRM == ftWjJldqiV){pHwxnftgtT = true;}
      if(rZiOZTLInI == CcOEACqEoa){KZKfJzCmWX = true;}
      else if(CcOEACqEoa == rZiOZTLInI){QSRkcSMCML = true;}
      if(WBooLOQqqj == tFKMdHYMpk){qyKZVhIcdO = true;}
      else if(tFKMdHYMpk == WBooLOQqqj){rbaoVRtTti = true;}
      if(qeUXpaxfVJ == yzsJfmqAVQ){VXyyaMrZea = true;}
      else if(yzsJfmqAVQ == qeUXpaxfVJ){eJFjPHJjsY = true;}
      if(FMaMVrSzuw == AhgmIsACZk){RyDrnQSCuu = true;}
      if(ZoNUWdFhXu == aHlHOhxNRQ){JCcANLjDqq = true;}
      if(UmAzdMELYz == UorgODiFYM){ZujSflaLFx = true;}
      while(AhgmIsACZk == FMaMVrSzuw){ZNDQyJWxKh = true;}
      while(aHlHOhxNRQ == aHlHOhxNRQ){JLYAJNgHbW = true;}
      while(UorgODiFYM == UorgODiFYM){lZlLoHMgVU = true;}
      if(LqhYaLXWDk == true){LqhYaLXWDk = false;}
      if(HVmFKqMkuy == true){HVmFKqMkuy = false;}
      if(pchFuLpAYE == true){pchFuLpAYE = false;}
      if(JudNZiYNgC == true){JudNZiYNgC = false;}
      if(KZKfJzCmWX == true){KZKfJzCmWX = false;}
      if(qyKZVhIcdO == true){qyKZVhIcdO = false;}
      if(VXyyaMrZea == true){VXyyaMrZea = false;}
      if(RyDrnQSCuu == true){RyDrnQSCuu = false;}
      if(JCcANLjDqq == true){JCcANLjDqq = false;}
      if(ZujSflaLFx == true){ZujSflaLFx = false;}
      if(GcHwFstRlF == true){GcHwFstRlF = false;}
      if(OGhhFTtykP == true){OGhhFTtykP = false;}
      if(bohnBWNkMB == true){bohnBWNkMB = false;}
      if(pHwxnftgtT == true){pHwxnftgtT = false;}
      if(QSRkcSMCML == true){QSRkcSMCML = false;}
      if(rbaoVRtTti == true){rbaoVRtTti = false;}
      if(eJFjPHJjsY == true){eJFjPHJjsY = false;}
      if(ZNDQyJWxKh == true){ZNDQyJWxKh = false;}
      if(JLYAJNgHbW == true){JLYAJNgHbW = false;}
      if(lZlLoHMgVU == true){lZlLoHMgVU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCTXDVMFBX
{ 
  void QQarLgVwAZ()
  { 
      bool RDXIeWLRgi = false;
      bool ubYTlzsCay = false;
      bool ADSRkiASTg = false;
      bool sPZAlmFCNR = false;
      bool nMGNDanTSl = false;
      bool ipejJNkGXw = false;
      bool WsyzofBYgz = false;
      bool sqoJJmxENK = false;
      bool ufAhyDjopX = false;
      bool BzdQtuOHXX = false;
      bool YOlSrrBVZW = false;
      bool QfrNBprPBl = false;
      bool wLiJxtNXOO = false;
      bool XpfpkftgpF = false;
      bool COOSHUHPPE = false;
      bool CyFlbMfcUy = false;
      bool edGLzazCcU = false;
      bool wKZujgwPBc = false;
      bool mxHKLYjtNX = false;
      bool zQMqaYHDTf = false;
      string DZtYjLQzcY;
      string micbJTVpfI;
      string oXmsPumXXu;
      string kIGWEREgLr;
      string BQaXbmgHcC;
      string jqDUGflAJn;
      string XsagmecGXr;
      string OodnGYxPQb;
      string OfuVKtEkPX;
      string eEWWTIosjx;
      string KaijnuMPOh;
      string iVjhZryFVs;
      string arpzMKRHTy;
      string iDeTRmwKhP;
      string hnVgoITnwa;
      string KiXqVRkiWc;
      string cEuPyeqPQm;
      string umXFKlVIKD;
      string pdLsnAemxz;
      string CMmElcrGiK;
      if(DZtYjLQzcY == KaijnuMPOh){RDXIeWLRgi = true;}
      else if(KaijnuMPOh == DZtYjLQzcY){YOlSrrBVZW = true;}
      if(micbJTVpfI == iVjhZryFVs){ubYTlzsCay = true;}
      else if(iVjhZryFVs == micbJTVpfI){QfrNBprPBl = true;}
      if(oXmsPumXXu == arpzMKRHTy){ADSRkiASTg = true;}
      else if(arpzMKRHTy == oXmsPumXXu){wLiJxtNXOO = true;}
      if(kIGWEREgLr == iDeTRmwKhP){sPZAlmFCNR = true;}
      else if(iDeTRmwKhP == kIGWEREgLr){XpfpkftgpF = true;}
      if(BQaXbmgHcC == hnVgoITnwa){nMGNDanTSl = true;}
      else if(hnVgoITnwa == BQaXbmgHcC){COOSHUHPPE = true;}
      if(jqDUGflAJn == KiXqVRkiWc){ipejJNkGXw = true;}
      else if(KiXqVRkiWc == jqDUGflAJn){CyFlbMfcUy = true;}
      if(XsagmecGXr == cEuPyeqPQm){WsyzofBYgz = true;}
      else if(cEuPyeqPQm == XsagmecGXr){edGLzazCcU = true;}
      if(OodnGYxPQb == umXFKlVIKD){sqoJJmxENK = true;}
      if(OfuVKtEkPX == pdLsnAemxz){ufAhyDjopX = true;}
      if(eEWWTIosjx == CMmElcrGiK){BzdQtuOHXX = true;}
      while(umXFKlVIKD == OodnGYxPQb){wKZujgwPBc = true;}
      while(pdLsnAemxz == pdLsnAemxz){mxHKLYjtNX = true;}
      while(CMmElcrGiK == CMmElcrGiK){zQMqaYHDTf = true;}
      if(RDXIeWLRgi == true){RDXIeWLRgi = false;}
      if(ubYTlzsCay == true){ubYTlzsCay = false;}
      if(ADSRkiASTg == true){ADSRkiASTg = false;}
      if(sPZAlmFCNR == true){sPZAlmFCNR = false;}
      if(nMGNDanTSl == true){nMGNDanTSl = false;}
      if(ipejJNkGXw == true){ipejJNkGXw = false;}
      if(WsyzofBYgz == true){WsyzofBYgz = false;}
      if(sqoJJmxENK == true){sqoJJmxENK = false;}
      if(ufAhyDjopX == true){ufAhyDjopX = false;}
      if(BzdQtuOHXX == true){BzdQtuOHXX = false;}
      if(YOlSrrBVZW == true){YOlSrrBVZW = false;}
      if(QfrNBprPBl == true){QfrNBprPBl = false;}
      if(wLiJxtNXOO == true){wLiJxtNXOO = false;}
      if(XpfpkftgpF == true){XpfpkftgpF = false;}
      if(COOSHUHPPE == true){COOSHUHPPE = false;}
      if(CyFlbMfcUy == true){CyFlbMfcUy = false;}
      if(edGLzazCcU == true){edGLzazCcU = false;}
      if(wKZujgwPBc == true){wKZujgwPBc = false;}
      if(mxHKLYjtNX == true){mxHKLYjtNX = false;}
      if(zQMqaYHDTf == true){zQMqaYHDTf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUCNXZESPU
{ 
  void BegQaUAMto()
  { 
      bool IaOzNwtZto = false;
      bool wDgnSbcxxK = false;
      bool uNToxpWdgd = false;
      bool BHeEzHIHGS = false;
      bool mlHXAdoaJQ = false;
      bool usxqNuGZBX = false;
      bool YQrPmoYbnL = false;
      bool SUpdWJFunT = false;
      bool AuTQiHJmqE = false;
      bool AiGisWsrkL = false;
      bool ENmxxZDTTE = false;
      bool oKkhWdwbge = false;
      bool fkkjLjOHkA = false;
      bool PNKcOlIVSI = false;
      bool EoSmOoxYLP = false;
      bool ZRKFeTcClN = false;
      bool LwhTnbAISk = false;
      bool UaIYapRyVV = false;
      bool mpuVZyDExu = false;
      bool JFiFxIHzyl = false;
      string YOnbZCYthE;
      string IgRsTPfXdz;
      string Ocyiosfkmz;
      string PkFSeCoWIb;
      string UsAtGjMnuR;
      string ikOnwuQFmf;
      string WnGioXayNR;
      string ZJOBdUcDcE;
      string groVQeVRVi;
      string kjjcFglRFh;
      string INZcqYVNJa;
      string SMbhyeykRJ;
      string BJbegpZlux;
      string iLxtwSRLdr;
      string IIHtQXHBea;
      string hBzugykuwB;
      string zjRMrHPgle;
      string MlGZBrCgNI;
      string hXHUOhLBNx;
      string hWPcrXquCJ;
      if(YOnbZCYthE == INZcqYVNJa){IaOzNwtZto = true;}
      else if(INZcqYVNJa == YOnbZCYthE){ENmxxZDTTE = true;}
      if(IgRsTPfXdz == SMbhyeykRJ){wDgnSbcxxK = true;}
      else if(SMbhyeykRJ == IgRsTPfXdz){oKkhWdwbge = true;}
      if(Ocyiosfkmz == BJbegpZlux){uNToxpWdgd = true;}
      else if(BJbegpZlux == Ocyiosfkmz){fkkjLjOHkA = true;}
      if(PkFSeCoWIb == iLxtwSRLdr){BHeEzHIHGS = true;}
      else if(iLxtwSRLdr == PkFSeCoWIb){PNKcOlIVSI = true;}
      if(UsAtGjMnuR == IIHtQXHBea){mlHXAdoaJQ = true;}
      else if(IIHtQXHBea == UsAtGjMnuR){EoSmOoxYLP = true;}
      if(ikOnwuQFmf == hBzugykuwB){usxqNuGZBX = true;}
      else if(hBzugykuwB == ikOnwuQFmf){ZRKFeTcClN = true;}
      if(WnGioXayNR == zjRMrHPgle){YQrPmoYbnL = true;}
      else if(zjRMrHPgle == WnGioXayNR){LwhTnbAISk = true;}
      if(ZJOBdUcDcE == MlGZBrCgNI){SUpdWJFunT = true;}
      if(groVQeVRVi == hXHUOhLBNx){AuTQiHJmqE = true;}
      if(kjjcFglRFh == hWPcrXquCJ){AiGisWsrkL = true;}
      while(MlGZBrCgNI == ZJOBdUcDcE){UaIYapRyVV = true;}
      while(hXHUOhLBNx == hXHUOhLBNx){mpuVZyDExu = true;}
      while(hWPcrXquCJ == hWPcrXquCJ){JFiFxIHzyl = true;}
      if(IaOzNwtZto == true){IaOzNwtZto = false;}
      if(wDgnSbcxxK == true){wDgnSbcxxK = false;}
      if(uNToxpWdgd == true){uNToxpWdgd = false;}
      if(BHeEzHIHGS == true){BHeEzHIHGS = false;}
      if(mlHXAdoaJQ == true){mlHXAdoaJQ = false;}
      if(usxqNuGZBX == true){usxqNuGZBX = false;}
      if(YQrPmoYbnL == true){YQrPmoYbnL = false;}
      if(SUpdWJFunT == true){SUpdWJFunT = false;}
      if(AuTQiHJmqE == true){AuTQiHJmqE = false;}
      if(AiGisWsrkL == true){AiGisWsrkL = false;}
      if(ENmxxZDTTE == true){ENmxxZDTTE = false;}
      if(oKkhWdwbge == true){oKkhWdwbge = false;}
      if(fkkjLjOHkA == true){fkkjLjOHkA = false;}
      if(PNKcOlIVSI == true){PNKcOlIVSI = false;}
      if(EoSmOoxYLP == true){EoSmOoxYLP = false;}
      if(ZRKFeTcClN == true){ZRKFeTcClN = false;}
      if(LwhTnbAISk == true){LwhTnbAISk = false;}
      if(UaIYapRyVV == true){UaIYapRyVV = false;}
      if(mpuVZyDExu == true){mpuVZyDExu = false;}
      if(JFiFxIHzyl == true){JFiFxIHzyl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGIUFDMHAR
{ 
  void VYMUAspIKR()
  { 
      bool JDXEJBjkZz = false;
      bool HVPUZHhZQl = false;
      bool xnfGpmXCid = false;
      bool gqSKaulZIU = false;
      bool DMdYPxFiJb = false;
      bool EVOniUXQOW = false;
      bool dhBwSPDEse = false;
      bool VHQuijKHqr = false;
      bool hnsHYLcebG = false;
      bool WUKlpULgGz = false;
      bool tAodFxESFy = false;
      bool JQZVnonsWG = false;
      bool mYcmHAweFN = false;
      bool YcArygzOBb = false;
      bool HKZdwGuoxA = false;
      bool gRKzLUXCVF = false;
      bool AYMqYgPgWH = false;
      bool pYruzbzzpB = false;
      bool FHhEgHSBfc = false;
      bool JwswahxhEP = false;
      string FSRjPGAckm;
      string PAbmBjZwdI;
      string cjeSieUQss;
      string QhFxtbNhso;
      string wBMdYNmSQD;
      string SJRzMUnzAk;
      string lijrWgtdrZ;
      string WrCnMbWBsU;
      string qBzoZGQFkZ;
      string nOgIDMQUGr;
      string TIZqgaHcmk;
      string xlFfsjjtRP;
      string PosSlHKtkz;
      string KBtBBibIIz;
      string zmSAbBIBOS;
      string cWDpbdOGFY;
      string QMrmZurEdJ;
      string IalRQbWsqj;
      string zJeSWnyDYW;
      string TUDiilueZf;
      if(FSRjPGAckm == TIZqgaHcmk){JDXEJBjkZz = true;}
      else if(TIZqgaHcmk == FSRjPGAckm){tAodFxESFy = true;}
      if(PAbmBjZwdI == xlFfsjjtRP){HVPUZHhZQl = true;}
      else if(xlFfsjjtRP == PAbmBjZwdI){JQZVnonsWG = true;}
      if(cjeSieUQss == PosSlHKtkz){xnfGpmXCid = true;}
      else if(PosSlHKtkz == cjeSieUQss){mYcmHAweFN = true;}
      if(QhFxtbNhso == KBtBBibIIz){gqSKaulZIU = true;}
      else if(KBtBBibIIz == QhFxtbNhso){YcArygzOBb = true;}
      if(wBMdYNmSQD == zmSAbBIBOS){DMdYPxFiJb = true;}
      else if(zmSAbBIBOS == wBMdYNmSQD){HKZdwGuoxA = true;}
      if(SJRzMUnzAk == cWDpbdOGFY){EVOniUXQOW = true;}
      else if(cWDpbdOGFY == SJRzMUnzAk){gRKzLUXCVF = true;}
      if(lijrWgtdrZ == QMrmZurEdJ){dhBwSPDEse = true;}
      else if(QMrmZurEdJ == lijrWgtdrZ){AYMqYgPgWH = true;}
      if(WrCnMbWBsU == IalRQbWsqj){VHQuijKHqr = true;}
      if(qBzoZGQFkZ == zJeSWnyDYW){hnsHYLcebG = true;}
      if(nOgIDMQUGr == TUDiilueZf){WUKlpULgGz = true;}
      while(IalRQbWsqj == WrCnMbWBsU){pYruzbzzpB = true;}
      while(zJeSWnyDYW == zJeSWnyDYW){FHhEgHSBfc = true;}
      while(TUDiilueZf == TUDiilueZf){JwswahxhEP = true;}
      if(JDXEJBjkZz == true){JDXEJBjkZz = false;}
      if(HVPUZHhZQl == true){HVPUZHhZQl = false;}
      if(xnfGpmXCid == true){xnfGpmXCid = false;}
      if(gqSKaulZIU == true){gqSKaulZIU = false;}
      if(DMdYPxFiJb == true){DMdYPxFiJb = false;}
      if(EVOniUXQOW == true){EVOniUXQOW = false;}
      if(dhBwSPDEse == true){dhBwSPDEse = false;}
      if(VHQuijKHqr == true){VHQuijKHqr = false;}
      if(hnsHYLcebG == true){hnsHYLcebG = false;}
      if(WUKlpULgGz == true){WUKlpULgGz = false;}
      if(tAodFxESFy == true){tAodFxESFy = false;}
      if(JQZVnonsWG == true){JQZVnonsWG = false;}
      if(mYcmHAweFN == true){mYcmHAweFN = false;}
      if(YcArygzOBb == true){YcArygzOBb = false;}
      if(HKZdwGuoxA == true){HKZdwGuoxA = false;}
      if(gRKzLUXCVF == true){gRKzLUXCVF = false;}
      if(AYMqYgPgWH == true){AYMqYgPgWH = false;}
      if(pYruzbzzpB == true){pYruzbzzpB = false;}
      if(FHhEgHSBfc == true){FHhEgHSBfc = false;}
      if(JwswahxhEP == true){JwswahxhEP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBAQLKUUWR
{ 
  void ulUFsVGIyy()
  { 
      bool teiNFYTBZm = false;
      bool VFnJfPgSrt = false;
      bool rNpetWTJsD = false;
      bool qZaAXyqfGn = false;
      bool jdXKEJgyke = false;
      bool UQCpYgoDSi = false;
      bool FKIVwwemlh = false;
      bool YALDKOoeak = false;
      bool oUXNiZXkap = false;
      bool ImMXiZUBOH = false;
      bool esMDFTEyfJ = false;
      bool qJbhsjltmV = false;
      bool YsMuYlnnTj = false;
      bool snPTFwIUHO = false;
      bool VYERzzKdey = false;
      bool maNsikgQeT = false;
      bool fQduQDtIbx = false;
      bool bRlXzzotwY = false;
      bool aJJVxRZVjU = false;
      bool OqoniEtIBw = false;
      string DkoZdxyxjp;
      string HKBIsOhiro;
      string bVFSboqBMT;
      string oOUYRasIDU;
      string KghOzArDRc;
      string dVLzrhfVxo;
      string FwkQAspcqS;
      string VYeXdtnqTa;
      string xmjipSCVgj;
      string tWKOOOwRNF;
      string KOMzHEqnVx;
      string toCVrRMBah;
      string pUwGXyOQIP;
      string yVcNQhajak;
      string bOAjoFUnWw;
      string BtqfOpSFbJ;
      string pZeFyXLoFJ;
      string qbaoFbTMRR;
      string dZsLNDexyZ;
      string PUIQuBjtkR;
      if(DkoZdxyxjp == KOMzHEqnVx){teiNFYTBZm = true;}
      else if(KOMzHEqnVx == DkoZdxyxjp){esMDFTEyfJ = true;}
      if(HKBIsOhiro == toCVrRMBah){VFnJfPgSrt = true;}
      else if(toCVrRMBah == HKBIsOhiro){qJbhsjltmV = true;}
      if(bVFSboqBMT == pUwGXyOQIP){rNpetWTJsD = true;}
      else if(pUwGXyOQIP == bVFSboqBMT){YsMuYlnnTj = true;}
      if(oOUYRasIDU == yVcNQhajak){qZaAXyqfGn = true;}
      else if(yVcNQhajak == oOUYRasIDU){snPTFwIUHO = true;}
      if(KghOzArDRc == bOAjoFUnWw){jdXKEJgyke = true;}
      else if(bOAjoFUnWw == KghOzArDRc){VYERzzKdey = true;}
      if(dVLzrhfVxo == BtqfOpSFbJ){UQCpYgoDSi = true;}
      else if(BtqfOpSFbJ == dVLzrhfVxo){maNsikgQeT = true;}
      if(FwkQAspcqS == pZeFyXLoFJ){FKIVwwemlh = true;}
      else if(pZeFyXLoFJ == FwkQAspcqS){fQduQDtIbx = true;}
      if(VYeXdtnqTa == qbaoFbTMRR){YALDKOoeak = true;}
      if(xmjipSCVgj == dZsLNDexyZ){oUXNiZXkap = true;}
      if(tWKOOOwRNF == PUIQuBjtkR){ImMXiZUBOH = true;}
      while(qbaoFbTMRR == VYeXdtnqTa){bRlXzzotwY = true;}
      while(dZsLNDexyZ == dZsLNDexyZ){aJJVxRZVjU = true;}
      while(PUIQuBjtkR == PUIQuBjtkR){OqoniEtIBw = true;}
      if(teiNFYTBZm == true){teiNFYTBZm = false;}
      if(VFnJfPgSrt == true){VFnJfPgSrt = false;}
      if(rNpetWTJsD == true){rNpetWTJsD = false;}
      if(qZaAXyqfGn == true){qZaAXyqfGn = false;}
      if(jdXKEJgyke == true){jdXKEJgyke = false;}
      if(UQCpYgoDSi == true){UQCpYgoDSi = false;}
      if(FKIVwwemlh == true){FKIVwwemlh = false;}
      if(YALDKOoeak == true){YALDKOoeak = false;}
      if(oUXNiZXkap == true){oUXNiZXkap = false;}
      if(ImMXiZUBOH == true){ImMXiZUBOH = false;}
      if(esMDFTEyfJ == true){esMDFTEyfJ = false;}
      if(qJbhsjltmV == true){qJbhsjltmV = false;}
      if(YsMuYlnnTj == true){YsMuYlnnTj = false;}
      if(snPTFwIUHO == true){snPTFwIUHO = false;}
      if(VYERzzKdey == true){VYERzzKdey = false;}
      if(maNsikgQeT == true){maNsikgQeT = false;}
      if(fQduQDtIbx == true){fQduQDtIbx = false;}
      if(bRlXzzotwY == true){bRlXzzotwY = false;}
      if(aJJVxRZVjU == true){aJJVxRZVjU = false;}
      if(OqoniEtIBw == true){OqoniEtIBw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZCWWCZJYV
{ 
  void tfkzkSNJhW()
  { 
      bool VkBKeaeVqM = false;
      bool wfGNWLPozf = false;
      bool lOCpwMLDdP = false;
      bool UIyuBKCgad = false;
      bool wosZICTXIP = false;
      bool fFzKxHiKNR = false;
      bool ObqbrmgKLL = false;
      bool JhOUjwUcht = false;
      bool rnuOiOInyt = false;
      bool bqSIPTxRgU = false;
      bool UILwFxqdaA = false;
      bool lGbTZZfcrd = false;
      bool dsMQiROFFP = false;
      bool zDuMZibyIl = false;
      bool XeMxHVOzip = false;
      bool mUYDpauuNn = false;
      bool hkYKBiKPsp = false;
      bool xhUGGzgPJN = false;
      bool CPWObddqWy = false;
      bool mgkUDlFBuX = false;
      string YbkIQtxAWH;
      string XdSmybdlPc;
      string FfjlgOkddV;
      string wMigJybcca;
      string JSWdqJxado;
      string QAGzjsrybB;
      string JTVALKtlcz;
      string zBJnSmIFuX;
      string QJAnFuGjwQ;
      string GcBaRpwWSf;
      string OLxdoOqRfx;
      string jlDEjzShuP;
      string EKoLrVAhWb;
      string plmOIFMVyp;
      string EoDygUZwpR;
      string XOaCbDWkkS;
      string OItEHxyoue;
      string mxiFLOHpeX;
      string wDrFEaLjlE;
      string hakeawtyqi;
      if(YbkIQtxAWH == OLxdoOqRfx){VkBKeaeVqM = true;}
      else if(OLxdoOqRfx == YbkIQtxAWH){UILwFxqdaA = true;}
      if(XdSmybdlPc == jlDEjzShuP){wfGNWLPozf = true;}
      else if(jlDEjzShuP == XdSmybdlPc){lGbTZZfcrd = true;}
      if(FfjlgOkddV == EKoLrVAhWb){lOCpwMLDdP = true;}
      else if(EKoLrVAhWb == FfjlgOkddV){dsMQiROFFP = true;}
      if(wMigJybcca == plmOIFMVyp){UIyuBKCgad = true;}
      else if(plmOIFMVyp == wMigJybcca){zDuMZibyIl = true;}
      if(JSWdqJxado == EoDygUZwpR){wosZICTXIP = true;}
      else if(EoDygUZwpR == JSWdqJxado){XeMxHVOzip = true;}
      if(QAGzjsrybB == XOaCbDWkkS){fFzKxHiKNR = true;}
      else if(XOaCbDWkkS == QAGzjsrybB){mUYDpauuNn = true;}
      if(JTVALKtlcz == OItEHxyoue){ObqbrmgKLL = true;}
      else if(OItEHxyoue == JTVALKtlcz){hkYKBiKPsp = true;}
      if(zBJnSmIFuX == mxiFLOHpeX){JhOUjwUcht = true;}
      if(QJAnFuGjwQ == wDrFEaLjlE){rnuOiOInyt = true;}
      if(GcBaRpwWSf == hakeawtyqi){bqSIPTxRgU = true;}
      while(mxiFLOHpeX == zBJnSmIFuX){xhUGGzgPJN = true;}
      while(wDrFEaLjlE == wDrFEaLjlE){CPWObddqWy = true;}
      while(hakeawtyqi == hakeawtyqi){mgkUDlFBuX = true;}
      if(VkBKeaeVqM == true){VkBKeaeVqM = false;}
      if(wfGNWLPozf == true){wfGNWLPozf = false;}
      if(lOCpwMLDdP == true){lOCpwMLDdP = false;}
      if(UIyuBKCgad == true){UIyuBKCgad = false;}
      if(wosZICTXIP == true){wosZICTXIP = false;}
      if(fFzKxHiKNR == true){fFzKxHiKNR = false;}
      if(ObqbrmgKLL == true){ObqbrmgKLL = false;}
      if(JhOUjwUcht == true){JhOUjwUcht = false;}
      if(rnuOiOInyt == true){rnuOiOInyt = false;}
      if(bqSIPTxRgU == true){bqSIPTxRgU = false;}
      if(UILwFxqdaA == true){UILwFxqdaA = false;}
      if(lGbTZZfcrd == true){lGbTZZfcrd = false;}
      if(dsMQiROFFP == true){dsMQiROFFP = false;}
      if(zDuMZibyIl == true){zDuMZibyIl = false;}
      if(XeMxHVOzip == true){XeMxHVOzip = false;}
      if(mUYDpauuNn == true){mUYDpauuNn = false;}
      if(hkYKBiKPsp == true){hkYKBiKPsp = false;}
      if(xhUGGzgPJN == true){xhUGGzgPJN = false;}
      if(CPWObddqWy == true){CPWObddqWy = false;}
      if(mgkUDlFBuX == true){mgkUDlFBuX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVZXHUUNRW
{ 
  void JAMGtSZoFM()
  { 
      bool WQUpgPqVTU = false;
      bool XLeZadakCA = false;
      bool jsmONktDsk = false;
      bool LRRtmDfxly = false;
      bool qcdCeYLKsi = false;
      bool jTGyydcGcu = false;
      bool VmbiIFtklX = false;
      bool xdyEJHOkjn = false;
      bool YiKJBrLTuJ = false;
      bool ZZUqcDAusY = false;
      bool eaYUlFUCoq = false;
      bool OrWnWlcRgQ = false;
      bool tZocyWJHbF = false;
      bool GSrKIyKoXu = false;
      bool WJeDthDfTp = false;
      bool aiNbdEluWO = false;
      bool wMZikwzLfX = false;
      bool bmslskukiQ = false;
      bool TdmkdXFPfD = false;
      bool MOSJzJiuSy = false;
      string EflpQsZjuZ;
      string EpDDWWgbVq;
      string BsZyOTSong;
      string llktjbgjyJ;
      string izpYdIhTGf;
      string SUtigKGmbx;
      string ZkuOmREJSu;
      string oxcMHBCAUG;
      string kzhHORqBMY;
      string UtIAiyDblL;
      string DYBLqUqhaf;
      string IGSULZCnzV;
      string aCwsZuoccJ;
      string xZOIDMyWPs;
      string ZJagQOamoI;
      string uPbPkAbHku;
      string fOEQhhqKRy;
      string bfXGwQbPcK;
      string TBmTNhyyWC;
      string kpkUNKEJyh;
      if(EflpQsZjuZ == DYBLqUqhaf){WQUpgPqVTU = true;}
      else if(DYBLqUqhaf == EflpQsZjuZ){eaYUlFUCoq = true;}
      if(EpDDWWgbVq == IGSULZCnzV){XLeZadakCA = true;}
      else if(IGSULZCnzV == EpDDWWgbVq){OrWnWlcRgQ = true;}
      if(BsZyOTSong == aCwsZuoccJ){jsmONktDsk = true;}
      else if(aCwsZuoccJ == BsZyOTSong){tZocyWJHbF = true;}
      if(llktjbgjyJ == xZOIDMyWPs){LRRtmDfxly = true;}
      else if(xZOIDMyWPs == llktjbgjyJ){GSrKIyKoXu = true;}
      if(izpYdIhTGf == ZJagQOamoI){qcdCeYLKsi = true;}
      else if(ZJagQOamoI == izpYdIhTGf){WJeDthDfTp = true;}
      if(SUtigKGmbx == uPbPkAbHku){jTGyydcGcu = true;}
      else if(uPbPkAbHku == SUtigKGmbx){aiNbdEluWO = true;}
      if(ZkuOmREJSu == fOEQhhqKRy){VmbiIFtklX = true;}
      else if(fOEQhhqKRy == ZkuOmREJSu){wMZikwzLfX = true;}
      if(oxcMHBCAUG == bfXGwQbPcK){xdyEJHOkjn = true;}
      if(kzhHORqBMY == TBmTNhyyWC){YiKJBrLTuJ = true;}
      if(UtIAiyDblL == kpkUNKEJyh){ZZUqcDAusY = true;}
      while(bfXGwQbPcK == oxcMHBCAUG){bmslskukiQ = true;}
      while(TBmTNhyyWC == TBmTNhyyWC){TdmkdXFPfD = true;}
      while(kpkUNKEJyh == kpkUNKEJyh){MOSJzJiuSy = true;}
      if(WQUpgPqVTU == true){WQUpgPqVTU = false;}
      if(XLeZadakCA == true){XLeZadakCA = false;}
      if(jsmONktDsk == true){jsmONktDsk = false;}
      if(LRRtmDfxly == true){LRRtmDfxly = false;}
      if(qcdCeYLKsi == true){qcdCeYLKsi = false;}
      if(jTGyydcGcu == true){jTGyydcGcu = false;}
      if(VmbiIFtklX == true){VmbiIFtklX = false;}
      if(xdyEJHOkjn == true){xdyEJHOkjn = false;}
      if(YiKJBrLTuJ == true){YiKJBrLTuJ = false;}
      if(ZZUqcDAusY == true){ZZUqcDAusY = false;}
      if(eaYUlFUCoq == true){eaYUlFUCoq = false;}
      if(OrWnWlcRgQ == true){OrWnWlcRgQ = false;}
      if(tZocyWJHbF == true){tZocyWJHbF = false;}
      if(GSrKIyKoXu == true){GSrKIyKoXu = false;}
      if(WJeDthDfTp == true){WJeDthDfTp = false;}
      if(aiNbdEluWO == true){aiNbdEluWO = false;}
      if(wMZikwzLfX == true){wMZikwzLfX = false;}
      if(bmslskukiQ == true){bmslskukiQ = false;}
      if(TdmkdXFPfD == true){TdmkdXFPfD = false;}
      if(MOSJzJiuSy == true){MOSJzJiuSy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQMYNHMHPE
{ 
  void BRHIGSVXuR()
  { 
      bool SOlTpAuiKe = false;
      bool QplHgFdagk = false;
      bool HgGYWzoxcl = false;
      bool jxDbwDJITb = false;
      bool dwzRukOMXi = false;
      bool KQTwokHMxq = false;
      bool KxGYtTmJLc = false;
      bool uVHEGLgodk = false;
      bool kbZtaScGlK = false;
      bool wxLbRfpZXb = false;
      bool yEBtmoJOod = false;
      bool DSiMGiXLya = false;
      bool pgXAgxKema = false;
      bool UGQCmfZeGk = false;
      bool JNQHGcOyVi = false;
      bool HdbwkRgBMp = false;
      bool edbOJwBgZZ = false;
      bool IrEMQbPPsE = false;
      bool iLIESqeUQV = false;
      bool zYSQGelCyJ = false;
      string SejITTnhxi;
      string mUgcOOCtLt;
      string cKjItKVBkh;
      string ONCgNrCzdD;
      string wBWdnrDlQw;
      string XQutIItbOJ;
      string ylwPUYSAPV;
      string LDPHxbnGTB;
      string GjkoJxRIXE;
      string xajUFKEHJO;
      string ZDWtjUBmwg;
      string TnIMCNAGGW;
      string HKbKXkStBm;
      string WgwEbDNpEo;
      string wdLqkJSWSq;
      string JxAlHPaLVz;
      string BGkJJmqDky;
      string AJCQacyjZO;
      string SwbKcYfKwL;
      string bBUEnorBgx;
      if(SejITTnhxi == ZDWtjUBmwg){SOlTpAuiKe = true;}
      else if(ZDWtjUBmwg == SejITTnhxi){yEBtmoJOod = true;}
      if(mUgcOOCtLt == TnIMCNAGGW){QplHgFdagk = true;}
      else if(TnIMCNAGGW == mUgcOOCtLt){DSiMGiXLya = true;}
      if(cKjItKVBkh == HKbKXkStBm){HgGYWzoxcl = true;}
      else if(HKbKXkStBm == cKjItKVBkh){pgXAgxKema = true;}
      if(ONCgNrCzdD == WgwEbDNpEo){jxDbwDJITb = true;}
      else if(WgwEbDNpEo == ONCgNrCzdD){UGQCmfZeGk = true;}
      if(wBWdnrDlQw == wdLqkJSWSq){dwzRukOMXi = true;}
      else if(wdLqkJSWSq == wBWdnrDlQw){JNQHGcOyVi = true;}
      if(XQutIItbOJ == JxAlHPaLVz){KQTwokHMxq = true;}
      else if(JxAlHPaLVz == XQutIItbOJ){HdbwkRgBMp = true;}
      if(ylwPUYSAPV == BGkJJmqDky){KxGYtTmJLc = true;}
      else if(BGkJJmqDky == ylwPUYSAPV){edbOJwBgZZ = true;}
      if(LDPHxbnGTB == AJCQacyjZO){uVHEGLgodk = true;}
      if(GjkoJxRIXE == SwbKcYfKwL){kbZtaScGlK = true;}
      if(xajUFKEHJO == bBUEnorBgx){wxLbRfpZXb = true;}
      while(AJCQacyjZO == LDPHxbnGTB){IrEMQbPPsE = true;}
      while(SwbKcYfKwL == SwbKcYfKwL){iLIESqeUQV = true;}
      while(bBUEnorBgx == bBUEnorBgx){zYSQGelCyJ = true;}
      if(SOlTpAuiKe == true){SOlTpAuiKe = false;}
      if(QplHgFdagk == true){QplHgFdagk = false;}
      if(HgGYWzoxcl == true){HgGYWzoxcl = false;}
      if(jxDbwDJITb == true){jxDbwDJITb = false;}
      if(dwzRukOMXi == true){dwzRukOMXi = false;}
      if(KQTwokHMxq == true){KQTwokHMxq = false;}
      if(KxGYtTmJLc == true){KxGYtTmJLc = false;}
      if(uVHEGLgodk == true){uVHEGLgodk = false;}
      if(kbZtaScGlK == true){kbZtaScGlK = false;}
      if(wxLbRfpZXb == true){wxLbRfpZXb = false;}
      if(yEBtmoJOod == true){yEBtmoJOod = false;}
      if(DSiMGiXLya == true){DSiMGiXLya = false;}
      if(pgXAgxKema == true){pgXAgxKema = false;}
      if(UGQCmfZeGk == true){UGQCmfZeGk = false;}
      if(JNQHGcOyVi == true){JNQHGcOyVi = false;}
      if(HdbwkRgBMp == true){HdbwkRgBMp = false;}
      if(edbOJwBgZZ == true){edbOJwBgZZ = false;}
      if(IrEMQbPPsE == true){IrEMQbPPsE = false;}
      if(iLIESqeUQV == true){iLIESqeUQV = false;}
      if(zYSQGelCyJ == true){zYSQGelCyJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RJYZXORPVM
{ 
  void cqgpPXnxhM()
  { 
      bool GaSuCPVTbM = false;
      bool BTtiNaqzks = false;
      bool ZkRHBzhbUA = false;
      bool eMKuVKxFhC = false;
      bool ZecVnWseMi = false;
      bool OxRdVUJLtC = false;
      bool htzahnJzND = false;
      bool dkRhTuIwSe = false;
      bool GCOklhugYA = false;
      bool AlKeUfeBnz = false;
      bool MtRIFceiJa = false;
      bool MNrPweeNoz = false;
      bool scZMCqZmNn = false;
      bool PGHSRMkGfI = false;
      bool CLWynmsuho = false;
      bool ARMnGjTFFN = false;
      bool CrVVLFFZxj = false;
      bool tXggxhGbXP = false;
      bool xeEYmytTMh = false;
      bool reASFJoAli = false;
      string NnGGQPTbEB;
      string YtJzTDfEQY;
      string kMoOAtdoLA;
      string UahwsWqcso;
      string MQiRtCHEfY;
      string aqkscAzrFV;
      string lePEgxMNFw;
      string MDLbLTcWTy;
      string lYJmYconTr;
      string XzWWCgAekw;
      string ptziMXfIhI;
      string XbXGjMVcfD;
      string IXsMXMfnZd;
      string TylWIrZZZB;
      string xfGLUwbQmo;
      string LXzgnSBlLz;
      string qqiDnYpAxq;
      string mwCeFbQgqb;
      string kPAjSuzEhp;
      string pmOaJFwDWw;
      if(NnGGQPTbEB == ptziMXfIhI){GaSuCPVTbM = true;}
      else if(ptziMXfIhI == NnGGQPTbEB){MtRIFceiJa = true;}
      if(YtJzTDfEQY == XbXGjMVcfD){BTtiNaqzks = true;}
      else if(XbXGjMVcfD == YtJzTDfEQY){MNrPweeNoz = true;}
      if(kMoOAtdoLA == IXsMXMfnZd){ZkRHBzhbUA = true;}
      else if(IXsMXMfnZd == kMoOAtdoLA){scZMCqZmNn = true;}
      if(UahwsWqcso == TylWIrZZZB){eMKuVKxFhC = true;}
      else if(TylWIrZZZB == UahwsWqcso){PGHSRMkGfI = true;}
      if(MQiRtCHEfY == xfGLUwbQmo){ZecVnWseMi = true;}
      else if(xfGLUwbQmo == MQiRtCHEfY){CLWynmsuho = true;}
      if(aqkscAzrFV == LXzgnSBlLz){OxRdVUJLtC = true;}
      else if(LXzgnSBlLz == aqkscAzrFV){ARMnGjTFFN = true;}
      if(lePEgxMNFw == qqiDnYpAxq){htzahnJzND = true;}
      else if(qqiDnYpAxq == lePEgxMNFw){CrVVLFFZxj = true;}
      if(MDLbLTcWTy == mwCeFbQgqb){dkRhTuIwSe = true;}
      if(lYJmYconTr == kPAjSuzEhp){GCOklhugYA = true;}
      if(XzWWCgAekw == pmOaJFwDWw){AlKeUfeBnz = true;}
      while(mwCeFbQgqb == MDLbLTcWTy){tXggxhGbXP = true;}
      while(kPAjSuzEhp == kPAjSuzEhp){xeEYmytTMh = true;}
      while(pmOaJFwDWw == pmOaJFwDWw){reASFJoAli = true;}
      if(GaSuCPVTbM == true){GaSuCPVTbM = false;}
      if(BTtiNaqzks == true){BTtiNaqzks = false;}
      if(ZkRHBzhbUA == true){ZkRHBzhbUA = false;}
      if(eMKuVKxFhC == true){eMKuVKxFhC = false;}
      if(ZecVnWseMi == true){ZecVnWseMi = false;}
      if(OxRdVUJLtC == true){OxRdVUJLtC = false;}
      if(htzahnJzND == true){htzahnJzND = false;}
      if(dkRhTuIwSe == true){dkRhTuIwSe = false;}
      if(GCOklhugYA == true){GCOklhugYA = false;}
      if(AlKeUfeBnz == true){AlKeUfeBnz = false;}
      if(MtRIFceiJa == true){MtRIFceiJa = false;}
      if(MNrPweeNoz == true){MNrPweeNoz = false;}
      if(scZMCqZmNn == true){scZMCqZmNn = false;}
      if(PGHSRMkGfI == true){PGHSRMkGfI = false;}
      if(CLWynmsuho == true){CLWynmsuho = false;}
      if(ARMnGjTFFN == true){ARMnGjTFFN = false;}
      if(CrVVLFFZxj == true){CrVVLFFZxj = false;}
      if(tXggxhGbXP == true){tXggxhGbXP = false;}
      if(xeEYmytTMh == true){xeEYmytTMh = false;}
      if(reASFJoAli == true){reASFJoAli = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWDPBSZXEB
{ 
  void KQBxnMkkEj()
  { 
      bool HzYiufgGEe = false;
      bool kWGCzjcMWq = false;
      bool LVMBJqmWhV = false;
      bool jUzEVJrGiK = false;
      bool PdYDnTefbN = false;
      bool RXDeNllWZD = false;
      bool rJXhuPWBfo = false;
      bool rWdLbgwJNp = false;
      bool MHtUEMRUpi = false;
      bool XVgeRGGqHY = false;
      bool xdAmVtsqDg = false;
      bool pcIjqkODci = false;
      bool xBKwRWoysU = false;
      bool ZFBoshHHyJ = false;
      bool SaQJstMxng = false;
      bool qDNYauSDUy = false;
      bool FuxhHjaTqI = false;
      bool dGESQWjBCX = false;
      bool KrKMdWrcNx = false;
      bool PDmAEXciBI = false;
      string bhAMpmEdhf;
      string KFzusLfIIe;
      string xNkrKuforh;
      string tscoEChhOf;
      string BCTlNqkZIr;
      string QmWiMOxIBt;
      string GPkzlRbKpp;
      string dysccuszdT;
      string KGfzRHVscp;
      string FYgTYkRUAu;
      string OajRORstFR;
      string UydgjAjkge;
      string whgzkEQZDr;
      string cYzhFjWOkz;
      string NbmKVHuAjY;
      string BfmVzfsjfJ;
      string BSqNnwzuaA;
      string dUzgQUuWdd;
      string JQpdqwkdhZ;
      string plhbytjZWY;
      if(bhAMpmEdhf == OajRORstFR){HzYiufgGEe = true;}
      else if(OajRORstFR == bhAMpmEdhf){xdAmVtsqDg = true;}
      if(KFzusLfIIe == UydgjAjkge){kWGCzjcMWq = true;}
      else if(UydgjAjkge == KFzusLfIIe){pcIjqkODci = true;}
      if(xNkrKuforh == whgzkEQZDr){LVMBJqmWhV = true;}
      else if(whgzkEQZDr == xNkrKuforh){xBKwRWoysU = true;}
      if(tscoEChhOf == cYzhFjWOkz){jUzEVJrGiK = true;}
      else if(cYzhFjWOkz == tscoEChhOf){ZFBoshHHyJ = true;}
      if(BCTlNqkZIr == NbmKVHuAjY){PdYDnTefbN = true;}
      else if(NbmKVHuAjY == BCTlNqkZIr){SaQJstMxng = true;}
      if(QmWiMOxIBt == BfmVzfsjfJ){RXDeNllWZD = true;}
      else if(BfmVzfsjfJ == QmWiMOxIBt){qDNYauSDUy = true;}
      if(GPkzlRbKpp == BSqNnwzuaA){rJXhuPWBfo = true;}
      else if(BSqNnwzuaA == GPkzlRbKpp){FuxhHjaTqI = true;}
      if(dysccuszdT == dUzgQUuWdd){rWdLbgwJNp = true;}
      if(KGfzRHVscp == JQpdqwkdhZ){MHtUEMRUpi = true;}
      if(FYgTYkRUAu == plhbytjZWY){XVgeRGGqHY = true;}
      while(dUzgQUuWdd == dysccuszdT){dGESQWjBCX = true;}
      while(JQpdqwkdhZ == JQpdqwkdhZ){KrKMdWrcNx = true;}
      while(plhbytjZWY == plhbytjZWY){PDmAEXciBI = true;}
      if(HzYiufgGEe == true){HzYiufgGEe = false;}
      if(kWGCzjcMWq == true){kWGCzjcMWq = false;}
      if(LVMBJqmWhV == true){LVMBJqmWhV = false;}
      if(jUzEVJrGiK == true){jUzEVJrGiK = false;}
      if(PdYDnTefbN == true){PdYDnTefbN = false;}
      if(RXDeNllWZD == true){RXDeNllWZD = false;}
      if(rJXhuPWBfo == true){rJXhuPWBfo = false;}
      if(rWdLbgwJNp == true){rWdLbgwJNp = false;}
      if(MHtUEMRUpi == true){MHtUEMRUpi = false;}
      if(XVgeRGGqHY == true){XVgeRGGqHY = false;}
      if(xdAmVtsqDg == true){xdAmVtsqDg = false;}
      if(pcIjqkODci == true){pcIjqkODci = false;}
      if(xBKwRWoysU == true){xBKwRWoysU = false;}
      if(ZFBoshHHyJ == true){ZFBoshHHyJ = false;}
      if(SaQJstMxng == true){SaQJstMxng = false;}
      if(qDNYauSDUy == true){qDNYauSDUy = false;}
      if(FuxhHjaTqI == true){FuxhHjaTqI = false;}
      if(dGESQWjBCX == true){dGESQWjBCX = false;}
      if(KrKMdWrcNx == true){KrKMdWrcNx = false;}
      if(PDmAEXciBI == true){PDmAEXciBI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SBVIANLMEJ
{ 
  void wrYTrigwCt()
  { 
      bool ySXgmyIckR = false;
      bool nQqwcjeleA = false;
      bool pQIVORiNOr = false;
      bool gFsLxKYBBi = false;
      bool UIGAqSAwcZ = false;
      bool oEIdhhKBRV = false;
      bool PuNsjhWfyS = false;
      bool KdkwehKHew = false;
      bool QljoDbwPcP = false;
      bool zXieSZtMPI = false;
      bool uUxKPLTMzA = false;
      bool WCVVEcLYpH = false;
      bool lHCiTltGcF = false;
      bool nxqWAwnYZq = false;
      bool IiPcswBMZo = false;
      bool NVWIVnROpc = false;
      bool QNjtLYLyVI = false;
      bool olyyzCqZpW = false;
      bool jgfmqRaiAM = false;
      bool eZiwauzVQT = false;
      string rzWjGJiuQD;
      string gDcfnzChCh;
      string FbWxgpxmUI;
      string AHmBefBqRn;
      string klYrGrxOEc;
      string NraRFQbYDP;
      string MwZICYPbAH;
      string yKQNxTCepo;
      string shhrtIgVuO;
      string EbnCbnLPph;
      string bUNwdDbNUl;
      string NwhOWdNhOs;
      string rtgkDWWNlI;
      string HlnIMXUlNp;
      string gSAIAHsYfx;
      string acBxphnbrG;
      string gNaMebIZBy;
      string JbTYLYsXkw;
      string dxhogdkqRe;
      string irsGJTqndY;
      if(rzWjGJiuQD == bUNwdDbNUl){ySXgmyIckR = true;}
      else if(bUNwdDbNUl == rzWjGJiuQD){uUxKPLTMzA = true;}
      if(gDcfnzChCh == NwhOWdNhOs){nQqwcjeleA = true;}
      else if(NwhOWdNhOs == gDcfnzChCh){WCVVEcLYpH = true;}
      if(FbWxgpxmUI == rtgkDWWNlI){pQIVORiNOr = true;}
      else if(rtgkDWWNlI == FbWxgpxmUI){lHCiTltGcF = true;}
      if(AHmBefBqRn == HlnIMXUlNp){gFsLxKYBBi = true;}
      else if(HlnIMXUlNp == AHmBefBqRn){nxqWAwnYZq = true;}
      if(klYrGrxOEc == gSAIAHsYfx){UIGAqSAwcZ = true;}
      else if(gSAIAHsYfx == klYrGrxOEc){IiPcswBMZo = true;}
      if(NraRFQbYDP == acBxphnbrG){oEIdhhKBRV = true;}
      else if(acBxphnbrG == NraRFQbYDP){NVWIVnROpc = true;}
      if(MwZICYPbAH == gNaMebIZBy){PuNsjhWfyS = true;}
      else if(gNaMebIZBy == MwZICYPbAH){QNjtLYLyVI = true;}
      if(yKQNxTCepo == JbTYLYsXkw){KdkwehKHew = true;}
      if(shhrtIgVuO == dxhogdkqRe){QljoDbwPcP = true;}
      if(EbnCbnLPph == irsGJTqndY){zXieSZtMPI = true;}
      while(JbTYLYsXkw == yKQNxTCepo){olyyzCqZpW = true;}
      while(dxhogdkqRe == dxhogdkqRe){jgfmqRaiAM = true;}
      while(irsGJTqndY == irsGJTqndY){eZiwauzVQT = true;}
      if(ySXgmyIckR == true){ySXgmyIckR = false;}
      if(nQqwcjeleA == true){nQqwcjeleA = false;}
      if(pQIVORiNOr == true){pQIVORiNOr = false;}
      if(gFsLxKYBBi == true){gFsLxKYBBi = false;}
      if(UIGAqSAwcZ == true){UIGAqSAwcZ = false;}
      if(oEIdhhKBRV == true){oEIdhhKBRV = false;}
      if(PuNsjhWfyS == true){PuNsjhWfyS = false;}
      if(KdkwehKHew == true){KdkwehKHew = false;}
      if(QljoDbwPcP == true){QljoDbwPcP = false;}
      if(zXieSZtMPI == true){zXieSZtMPI = false;}
      if(uUxKPLTMzA == true){uUxKPLTMzA = false;}
      if(WCVVEcLYpH == true){WCVVEcLYpH = false;}
      if(lHCiTltGcF == true){lHCiTltGcF = false;}
      if(nxqWAwnYZq == true){nxqWAwnYZq = false;}
      if(IiPcswBMZo == true){IiPcswBMZo = false;}
      if(NVWIVnROpc == true){NVWIVnROpc = false;}
      if(QNjtLYLyVI == true){QNjtLYLyVI = false;}
      if(olyyzCqZpW == true){olyyzCqZpW = false;}
      if(jgfmqRaiAM == true){jgfmqRaiAM = false;}
      if(eZiwauzVQT == true){eZiwauzVQT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDAMHFONBU
{ 
  void KCLgeKTTfn()
  { 
      bool kcTxBPPVCo = false;
      bool lcDJqVCZUX = false;
      bool MWewjMQRPz = false;
      bool MCgYVngtEA = false;
      bool sJMHVahGyM = false;
      bool wtOMpNyWNo = false;
      bool yyGCciwemD = false;
      bool nIVUeCJXaI = false;
      bool eKTDCSnThH = false;
      bool oKfPBuDKdl = false;
      bool eCSuXmYthm = false;
      bool EawEJndCzK = false;
      bool ucxfNdcFTi = false;
      bool zzsndcqYfP = false;
      bool stktDNObGM = false;
      bool QAKTqCFmgs = false;
      bool KSaynEhHZg = false;
      bool xFWjQBqCbz = false;
      bool OAzGSznYxb = false;
      bool XDrlEZSlGz = false;
      string YYdigOLSuu;
      string ZdURlxBiVc;
      string ZGMGeTgVhm;
      string lAyFGkYPjy;
      string BOgCfOrNuD;
      string iVKbYSLWDN;
      string hojHIYfOLB;
      string XkzWaLZJaQ;
      string bSadDPoWfn;
      string YBLWPMdYsG;
      string idCsfxWnAN;
      string sCwmlPOGEr;
      string iJiWcWZbHO;
      string gAPThyQgyG;
      string sBVRuWFYkA;
      string yXUBXZteQI;
      string XtglgrlbEm;
      string yhHyzhmRbG;
      string RBqGQJfOwI;
      string DkQohzUjkC;
      if(YYdigOLSuu == idCsfxWnAN){kcTxBPPVCo = true;}
      else if(idCsfxWnAN == YYdigOLSuu){eCSuXmYthm = true;}
      if(ZdURlxBiVc == sCwmlPOGEr){lcDJqVCZUX = true;}
      else if(sCwmlPOGEr == ZdURlxBiVc){EawEJndCzK = true;}
      if(ZGMGeTgVhm == iJiWcWZbHO){MWewjMQRPz = true;}
      else if(iJiWcWZbHO == ZGMGeTgVhm){ucxfNdcFTi = true;}
      if(lAyFGkYPjy == gAPThyQgyG){MCgYVngtEA = true;}
      else if(gAPThyQgyG == lAyFGkYPjy){zzsndcqYfP = true;}
      if(BOgCfOrNuD == sBVRuWFYkA){sJMHVahGyM = true;}
      else if(sBVRuWFYkA == BOgCfOrNuD){stktDNObGM = true;}
      if(iVKbYSLWDN == yXUBXZteQI){wtOMpNyWNo = true;}
      else if(yXUBXZteQI == iVKbYSLWDN){QAKTqCFmgs = true;}
      if(hojHIYfOLB == XtglgrlbEm){yyGCciwemD = true;}
      else if(XtglgrlbEm == hojHIYfOLB){KSaynEhHZg = true;}
      if(XkzWaLZJaQ == yhHyzhmRbG){nIVUeCJXaI = true;}
      if(bSadDPoWfn == RBqGQJfOwI){eKTDCSnThH = true;}
      if(YBLWPMdYsG == DkQohzUjkC){oKfPBuDKdl = true;}
      while(yhHyzhmRbG == XkzWaLZJaQ){xFWjQBqCbz = true;}
      while(RBqGQJfOwI == RBqGQJfOwI){OAzGSznYxb = true;}
      while(DkQohzUjkC == DkQohzUjkC){XDrlEZSlGz = true;}
      if(kcTxBPPVCo == true){kcTxBPPVCo = false;}
      if(lcDJqVCZUX == true){lcDJqVCZUX = false;}
      if(MWewjMQRPz == true){MWewjMQRPz = false;}
      if(MCgYVngtEA == true){MCgYVngtEA = false;}
      if(sJMHVahGyM == true){sJMHVahGyM = false;}
      if(wtOMpNyWNo == true){wtOMpNyWNo = false;}
      if(yyGCciwemD == true){yyGCciwemD = false;}
      if(nIVUeCJXaI == true){nIVUeCJXaI = false;}
      if(eKTDCSnThH == true){eKTDCSnThH = false;}
      if(oKfPBuDKdl == true){oKfPBuDKdl = false;}
      if(eCSuXmYthm == true){eCSuXmYthm = false;}
      if(EawEJndCzK == true){EawEJndCzK = false;}
      if(ucxfNdcFTi == true){ucxfNdcFTi = false;}
      if(zzsndcqYfP == true){zzsndcqYfP = false;}
      if(stktDNObGM == true){stktDNObGM = false;}
      if(QAKTqCFmgs == true){QAKTqCFmgs = false;}
      if(KSaynEhHZg == true){KSaynEhHZg = false;}
      if(xFWjQBqCbz == true){xFWjQBqCbz = false;}
      if(OAzGSznYxb == true){OAzGSznYxb = false;}
      if(XDrlEZSlGz == true){XDrlEZSlGz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZHAVKUAXC
{ 
  void CaCUySoLFV()
  { 
      bool KLAZwDjpFT = false;
      bool UonWhUWfTj = false;
      bool lraYosywnm = false;
      bool EoEoVCbbOF = false;
      bool SyCGnCIYaQ = false;
      bool bZggXRkajD = false;
      bool FmBSOejyBe = false;
      bool stQNRmoTkl = false;
      bool kZUXLeIXRD = false;
      bool RBqLAfwjrI = false;
      bool RJWwWgISOk = false;
      bool bQoySfRdGj = false;
      bool WMgxNrDFNl = false;
      bool pFbcTbCYAd = false;
      bool VpIgaALsrU = false;
      bool ORcIlFbYhe = false;
      bool cCEctWoMdq = false;
      bool crdcNgDAWN = false;
      bool gKNsXXbTqO = false;
      bool zdpUASkelE = false;
      string RLWTRKetxp;
      string ijWZRQiOEb;
      string oGKYRpdrCw;
      string enzKaNSmQs;
      string dtbKgQzWyW;
      string DcAiZKByCa;
      string gmrBKukLzD;
      string xuxKyteAqA;
      string qHsfrCmPjP;
      string MUjpMqCZAl;
      string fmWtZIepke;
      string fBGCjZsMJI;
      string HUbiqcKHyH;
      string rFAETDjzGi;
      string WxeEjLNhFl;
      string xpPqdLLmDw;
      string xXqdmaABhf;
      string otGZlKpWzf;
      string ObBLJCoIaI;
      string qwuJlyFARJ;
      if(RLWTRKetxp == fmWtZIepke){KLAZwDjpFT = true;}
      else if(fmWtZIepke == RLWTRKetxp){RJWwWgISOk = true;}
      if(ijWZRQiOEb == fBGCjZsMJI){UonWhUWfTj = true;}
      else if(fBGCjZsMJI == ijWZRQiOEb){bQoySfRdGj = true;}
      if(oGKYRpdrCw == HUbiqcKHyH){lraYosywnm = true;}
      else if(HUbiqcKHyH == oGKYRpdrCw){WMgxNrDFNl = true;}
      if(enzKaNSmQs == rFAETDjzGi){EoEoVCbbOF = true;}
      else if(rFAETDjzGi == enzKaNSmQs){pFbcTbCYAd = true;}
      if(dtbKgQzWyW == WxeEjLNhFl){SyCGnCIYaQ = true;}
      else if(WxeEjLNhFl == dtbKgQzWyW){VpIgaALsrU = true;}
      if(DcAiZKByCa == xpPqdLLmDw){bZggXRkajD = true;}
      else if(xpPqdLLmDw == DcAiZKByCa){ORcIlFbYhe = true;}
      if(gmrBKukLzD == xXqdmaABhf){FmBSOejyBe = true;}
      else if(xXqdmaABhf == gmrBKukLzD){cCEctWoMdq = true;}
      if(xuxKyteAqA == otGZlKpWzf){stQNRmoTkl = true;}
      if(qHsfrCmPjP == ObBLJCoIaI){kZUXLeIXRD = true;}
      if(MUjpMqCZAl == qwuJlyFARJ){RBqLAfwjrI = true;}
      while(otGZlKpWzf == xuxKyteAqA){crdcNgDAWN = true;}
      while(ObBLJCoIaI == ObBLJCoIaI){gKNsXXbTqO = true;}
      while(qwuJlyFARJ == qwuJlyFARJ){zdpUASkelE = true;}
      if(KLAZwDjpFT == true){KLAZwDjpFT = false;}
      if(UonWhUWfTj == true){UonWhUWfTj = false;}
      if(lraYosywnm == true){lraYosywnm = false;}
      if(EoEoVCbbOF == true){EoEoVCbbOF = false;}
      if(SyCGnCIYaQ == true){SyCGnCIYaQ = false;}
      if(bZggXRkajD == true){bZggXRkajD = false;}
      if(FmBSOejyBe == true){FmBSOejyBe = false;}
      if(stQNRmoTkl == true){stQNRmoTkl = false;}
      if(kZUXLeIXRD == true){kZUXLeIXRD = false;}
      if(RBqLAfwjrI == true){RBqLAfwjrI = false;}
      if(RJWwWgISOk == true){RJWwWgISOk = false;}
      if(bQoySfRdGj == true){bQoySfRdGj = false;}
      if(WMgxNrDFNl == true){WMgxNrDFNl = false;}
      if(pFbcTbCYAd == true){pFbcTbCYAd = false;}
      if(VpIgaALsrU == true){VpIgaALsrU = false;}
      if(ORcIlFbYhe == true){ORcIlFbYhe = false;}
      if(cCEctWoMdq == true){cCEctWoMdq = false;}
      if(crdcNgDAWN == true){crdcNgDAWN = false;}
      if(gKNsXXbTqO == true){gKNsXXbTqO = false;}
      if(zdpUASkelE == true){zdpUASkelE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYLWGVWVLT
{ 
  void gEnolJiJcq()
  { 
      bool uzKXXYRlVV = false;
      bool EEVtVMdZDj = false;
      bool IFHZpEWDbG = false;
      bool AoSIURylhU = false;
      bool UwCoVSOLAR = false;
      bool gAxLPorjhT = false;
      bool BNJOUPkNZE = false;
      bool NqriOLCSDW = false;
      bool oLDJYAqGse = false;
      bool ZNEOSGmmTG = false;
      bool gBlwDoHOwD = false;
      bool mYgKdpKzpU = false;
      bool XeTtdzmdQH = false;
      bool YPywomZGGi = false;
      bool scJprAgsjc = false;
      bool wmxzhChqSE = false;
      bool CcyodWajVp = false;
      bool PEsGbuVdCc = false;
      bool SstnLlSzNm = false;
      bool FhnCfPeUMU = false;
      string OLTyikdyes;
      string IJdGRgQOVA;
      string CVKGUqSTfi;
      string xSdcbOFMfK;
      string HtuxTOBeDz;
      string sQLlIsAMdr;
      string SKRwwofBeD;
      string bDhLsHZMlF;
      string onQgogHqTh;
      string NrimrwczBe;
      string izzAWohAsB;
      string SnZXCdtjGP;
      string hngwoiTtTw;
      string eaKHWpnQKz;
      string yGySPYRLkN;
      string CrrlwuSDKm;
      string UmfxWqdSBM;
      string ocZGQapOgP;
      string RIJFsliXKa;
      string WkFWdKaBwX;
      if(OLTyikdyes == izzAWohAsB){uzKXXYRlVV = true;}
      else if(izzAWohAsB == OLTyikdyes){gBlwDoHOwD = true;}
      if(IJdGRgQOVA == SnZXCdtjGP){EEVtVMdZDj = true;}
      else if(SnZXCdtjGP == IJdGRgQOVA){mYgKdpKzpU = true;}
      if(CVKGUqSTfi == hngwoiTtTw){IFHZpEWDbG = true;}
      else if(hngwoiTtTw == CVKGUqSTfi){XeTtdzmdQH = true;}
      if(xSdcbOFMfK == eaKHWpnQKz){AoSIURylhU = true;}
      else if(eaKHWpnQKz == xSdcbOFMfK){YPywomZGGi = true;}
      if(HtuxTOBeDz == yGySPYRLkN){UwCoVSOLAR = true;}
      else if(yGySPYRLkN == HtuxTOBeDz){scJprAgsjc = true;}
      if(sQLlIsAMdr == CrrlwuSDKm){gAxLPorjhT = true;}
      else if(CrrlwuSDKm == sQLlIsAMdr){wmxzhChqSE = true;}
      if(SKRwwofBeD == UmfxWqdSBM){BNJOUPkNZE = true;}
      else if(UmfxWqdSBM == SKRwwofBeD){CcyodWajVp = true;}
      if(bDhLsHZMlF == ocZGQapOgP){NqriOLCSDW = true;}
      if(onQgogHqTh == RIJFsliXKa){oLDJYAqGse = true;}
      if(NrimrwczBe == WkFWdKaBwX){ZNEOSGmmTG = true;}
      while(ocZGQapOgP == bDhLsHZMlF){PEsGbuVdCc = true;}
      while(RIJFsliXKa == RIJFsliXKa){SstnLlSzNm = true;}
      while(WkFWdKaBwX == WkFWdKaBwX){FhnCfPeUMU = true;}
      if(uzKXXYRlVV == true){uzKXXYRlVV = false;}
      if(EEVtVMdZDj == true){EEVtVMdZDj = false;}
      if(IFHZpEWDbG == true){IFHZpEWDbG = false;}
      if(AoSIURylhU == true){AoSIURylhU = false;}
      if(UwCoVSOLAR == true){UwCoVSOLAR = false;}
      if(gAxLPorjhT == true){gAxLPorjhT = false;}
      if(BNJOUPkNZE == true){BNJOUPkNZE = false;}
      if(NqriOLCSDW == true){NqriOLCSDW = false;}
      if(oLDJYAqGse == true){oLDJYAqGse = false;}
      if(ZNEOSGmmTG == true){ZNEOSGmmTG = false;}
      if(gBlwDoHOwD == true){gBlwDoHOwD = false;}
      if(mYgKdpKzpU == true){mYgKdpKzpU = false;}
      if(XeTtdzmdQH == true){XeTtdzmdQH = false;}
      if(YPywomZGGi == true){YPywomZGGi = false;}
      if(scJprAgsjc == true){scJprAgsjc = false;}
      if(wmxzhChqSE == true){wmxzhChqSE = false;}
      if(CcyodWajVp == true){CcyodWajVp = false;}
      if(PEsGbuVdCc == true){PEsGbuVdCc = false;}
      if(SstnLlSzNm == true){SstnLlSzNm = false;}
      if(FhnCfPeUMU == true){FhnCfPeUMU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVMDGDXADE
{ 
  void GeuSBEGXFh()
  { 
      bool IjcjtacYzE = false;
      bool sDVdILNlDC = false;
      bool jEnDcVzJkQ = false;
      bool gtpofxLDWB = false;
      bool qCImonKOqA = false;
      bool PTrTiDuYHY = false;
      bool aSmiWyNgxL = false;
      bool zKPBKgwBOo = false;
      bool LkRjANCWFb = false;
      bool BluyZXPYPp = false;
      bool adQfBFEpIC = false;
      bool GtKSMpBCiJ = false;
      bool wpaUJNORam = false;
      bool QXkYOhTlit = false;
      bool JLNDVGbckj = false;
      bool WNoGtjCuVm = false;
      bool plPVkiIkDe = false;
      bool WPSnAjcWzD = false;
      bool llfqPDhedd = false;
      bool eXPwEWwqRm = false;
      string VYecdzFWTs;
      string ucSzPuUORj;
      string LinqBYOMst;
      string tTCrZVTwnt;
      string QQFSQduoXP;
      string cUpxWlknbF;
      string krdZyaZZYt;
      string bYaXTtcVZW;
      string cYndQYcFUm;
      string jeUhIXmfTp;
      string EUPcmEtScc;
      string IOOEcLEAJZ;
      string yTElKxEsOw;
      string GxCiSHJLpL;
      string eKcrdVPPFx;
      string TmVtrjQcSp;
      string ABEfVLMflU;
      string CrJxtmqMHn;
      string gomRcTbHqh;
      string qfsALdGwVS;
      if(VYecdzFWTs == EUPcmEtScc){IjcjtacYzE = true;}
      else if(EUPcmEtScc == VYecdzFWTs){adQfBFEpIC = true;}
      if(ucSzPuUORj == IOOEcLEAJZ){sDVdILNlDC = true;}
      else if(IOOEcLEAJZ == ucSzPuUORj){GtKSMpBCiJ = true;}
      if(LinqBYOMst == yTElKxEsOw){jEnDcVzJkQ = true;}
      else if(yTElKxEsOw == LinqBYOMst){wpaUJNORam = true;}
      if(tTCrZVTwnt == GxCiSHJLpL){gtpofxLDWB = true;}
      else if(GxCiSHJLpL == tTCrZVTwnt){QXkYOhTlit = true;}
      if(QQFSQduoXP == eKcrdVPPFx){qCImonKOqA = true;}
      else if(eKcrdVPPFx == QQFSQduoXP){JLNDVGbckj = true;}
      if(cUpxWlknbF == TmVtrjQcSp){PTrTiDuYHY = true;}
      else if(TmVtrjQcSp == cUpxWlknbF){WNoGtjCuVm = true;}
      if(krdZyaZZYt == ABEfVLMflU){aSmiWyNgxL = true;}
      else if(ABEfVLMflU == krdZyaZZYt){plPVkiIkDe = true;}
      if(bYaXTtcVZW == CrJxtmqMHn){zKPBKgwBOo = true;}
      if(cYndQYcFUm == gomRcTbHqh){LkRjANCWFb = true;}
      if(jeUhIXmfTp == qfsALdGwVS){BluyZXPYPp = true;}
      while(CrJxtmqMHn == bYaXTtcVZW){WPSnAjcWzD = true;}
      while(gomRcTbHqh == gomRcTbHqh){llfqPDhedd = true;}
      while(qfsALdGwVS == qfsALdGwVS){eXPwEWwqRm = true;}
      if(IjcjtacYzE == true){IjcjtacYzE = false;}
      if(sDVdILNlDC == true){sDVdILNlDC = false;}
      if(jEnDcVzJkQ == true){jEnDcVzJkQ = false;}
      if(gtpofxLDWB == true){gtpofxLDWB = false;}
      if(qCImonKOqA == true){qCImonKOqA = false;}
      if(PTrTiDuYHY == true){PTrTiDuYHY = false;}
      if(aSmiWyNgxL == true){aSmiWyNgxL = false;}
      if(zKPBKgwBOo == true){zKPBKgwBOo = false;}
      if(LkRjANCWFb == true){LkRjANCWFb = false;}
      if(BluyZXPYPp == true){BluyZXPYPp = false;}
      if(adQfBFEpIC == true){adQfBFEpIC = false;}
      if(GtKSMpBCiJ == true){GtKSMpBCiJ = false;}
      if(wpaUJNORam == true){wpaUJNORam = false;}
      if(QXkYOhTlit == true){QXkYOhTlit = false;}
      if(JLNDVGbckj == true){JLNDVGbckj = false;}
      if(WNoGtjCuVm == true){WNoGtjCuVm = false;}
      if(plPVkiIkDe == true){plPVkiIkDe = false;}
      if(WPSnAjcWzD == true){WPSnAjcWzD = false;}
      if(llfqPDhedd == true){llfqPDhedd = false;}
      if(eXPwEWwqRm == true){eXPwEWwqRm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIWYWZRSZH
{ 
  void KnmOrndWBA()
  { 
      bool DTFdjkaQrh = false;
      bool DwuFhfwXpV = false;
      bool TgkPaHYQcV = false;
      bool AiMbhdSHZO = false;
      bool busoLdwHaj = false;
      bool yypzBWhpDb = false;
      bool LJnVgUiTXE = false;
      bool MnybtYmwDw = false;
      bool KQprWCrNZK = false;
      bool ubExCSGWHp = false;
      bool tbjWWKAOFb = false;
      bool illGRuTwze = false;
      bool bVsMIjjAYa = false;
      bool SQnMCifTUM = false;
      bool BcHybJpxeH = false;
      bool zKWcOYiXNm = false;
      bool azodISxYEi = false;
      bool OzamczNtkz = false;
      bool tlURbHsLyc = false;
      bool zIFhkCndoJ = false;
      string LhlOegpFyD;
      string QzSEjwGCmu;
      string COXrNOVuqC;
      string fMfUBrHzAc;
      string JfUajZDtqu;
      string UBjxyxJtBQ;
      string KuNwXDTxDq;
      string nGBKkWtxIn;
      string KbEwhdchVE;
      string iNyjROSXDf;
      string FGqzGNAYLb;
      string CMkNFiqQNt;
      string albyIZIRrW;
      string DVtciEjEpU;
      string dDVsBWbjei;
      string WBKIFTdrqf;
      string EhgoXfSIeA;
      string zlasQWPhxl;
      string xYlJzCLkWP;
      string ZqNJQuVgUV;
      if(LhlOegpFyD == FGqzGNAYLb){DTFdjkaQrh = true;}
      else if(FGqzGNAYLb == LhlOegpFyD){tbjWWKAOFb = true;}
      if(QzSEjwGCmu == CMkNFiqQNt){DwuFhfwXpV = true;}
      else if(CMkNFiqQNt == QzSEjwGCmu){illGRuTwze = true;}
      if(COXrNOVuqC == albyIZIRrW){TgkPaHYQcV = true;}
      else if(albyIZIRrW == COXrNOVuqC){bVsMIjjAYa = true;}
      if(fMfUBrHzAc == DVtciEjEpU){AiMbhdSHZO = true;}
      else if(DVtciEjEpU == fMfUBrHzAc){SQnMCifTUM = true;}
      if(JfUajZDtqu == dDVsBWbjei){busoLdwHaj = true;}
      else if(dDVsBWbjei == JfUajZDtqu){BcHybJpxeH = true;}
      if(UBjxyxJtBQ == WBKIFTdrqf){yypzBWhpDb = true;}
      else if(WBKIFTdrqf == UBjxyxJtBQ){zKWcOYiXNm = true;}
      if(KuNwXDTxDq == EhgoXfSIeA){LJnVgUiTXE = true;}
      else if(EhgoXfSIeA == KuNwXDTxDq){azodISxYEi = true;}
      if(nGBKkWtxIn == zlasQWPhxl){MnybtYmwDw = true;}
      if(KbEwhdchVE == xYlJzCLkWP){KQprWCrNZK = true;}
      if(iNyjROSXDf == ZqNJQuVgUV){ubExCSGWHp = true;}
      while(zlasQWPhxl == nGBKkWtxIn){OzamczNtkz = true;}
      while(xYlJzCLkWP == xYlJzCLkWP){tlURbHsLyc = true;}
      while(ZqNJQuVgUV == ZqNJQuVgUV){zIFhkCndoJ = true;}
      if(DTFdjkaQrh == true){DTFdjkaQrh = false;}
      if(DwuFhfwXpV == true){DwuFhfwXpV = false;}
      if(TgkPaHYQcV == true){TgkPaHYQcV = false;}
      if(AiMbhdSHZO == true){AiMbhdSHZO = false;}
      if(busoLdwHaj == true){busoLdwHaj = false;}
      if(yypzBWhpDb == true){yypzBWhpDb = false;}
      if(LJnVgUiTXE == true){LJnVgUiTXE = false;}
      if(MnybtYmwDw == true){MnybtYmwDw = false;}
      if(KQprWCrNZK == true){KQprWCrNZK = false;}
      if(ubExCSGWHp == true){ubExCSGWHp = false;}
      if(tbjWWKAOFb == true){tbjWWKAOFb = false;}
      if(illGRuTwze == true){illGRuTwze = false;}
      if(bVsMIjjAYa == true){bVsMIjjAYa = false;}
      if(SQnMCifTUM == true){SQnMCifTUM = false;}
      if(BcHybJpxeH == true){BcHybJpxeH = false;}
      if(zKWcOYiXNm == true){zKWcOYiXNm = false;}
      if(azodISxYEi == true){azodISxYEi = false;}
      if(OzamczNtkz == true){OzamczNtkz = false;}
      if(tlURbHsLyc == true){tlURbHsLyc = false;}
      if(zIFhkCndoJ == true){zIFhkCndoJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBXZMRCHUQ
{ 
  void wMkaEdbuzu()
  { 
      bool HXPbWpLnjh = false;
      bool bOalskjAIb = false;
      bool JMAcNHcaVt = false;
      bool uKWXBzPbeP = false;
      bool bzbZZFbfbT = false;
      bool UhdMuuXlOP = false;
      bool MkSplRrDjt = false;
      bool VHVrAKjaCH = false;
      bool exyCYMfKbG = false;
      bool acNODqgkmI = false;
      bool NYwhxMLkMk = false;
      bool LxjGjPlQRZ = false;
      bool kgacSstGoI = false;
      bool cynttGAPEL = false;
      bool AuxqudsGdn = false;
      bool EQTMXfxSPE = false;
      bool RFwDHMJoMd = false;
      bool OVLFYpijhn = false;
      bool AncBEMdaWN = false;
      bool JhAAsuytih = false;
      string yeRWjOkToi;
      string cBBzncdKpm;
      string SikBUQGcff;
      string xrxRRwVCHH;
      string BeUNJYbQda;
      string SDVqAOtQBS;
      string HHnJkkDihr;
      string HaCikmOXqu;
      string opzFMtWGRC;
      string CEAnztqLbY;
      string VrikSqBlFM;
      string AVZFdRIhwq;
      string NxRepCaNjq;
      string wCwRZwGNlV;
      string rjAFCgeuKh;
      string kIOjKXaDuQ;
      string QmCOPxYHeh;
      string KuwazcwLcJ;
      string WeDBFnnMHC;
      string UDRVEFhloE;
      if(yeRWjOkToi == VrikSqBlFM){HXPbWpLnjh = true;}
      else if(VrikSqBlFM == yeRWjOkToi){NYwhxMLkMk = true;}
      if(cBBzncdKpm == AVZFdRIhwq){bOalskjAIb = true;}
      else if(AVZFdRIhwq == cBBzncdKpm){LxjGjPlQRZ = true;}
      if(SikBUQGcff == NxRepCaNjq){JMAcNHcaVt = true;}
      else if(NxRepCaNjq == SikBUQGcff){kgacSstGoI = true;}
      if(xrxRRwVCHH == wCwRZwGNlV){uKWXBzPbeP = true;}
      else if(wCwRZwGNlV == xrxRRwVCHH){cynttGAPEL = true;}
      if(BeUNJYbQda == rjAFCgeuKh){bzbZZFbfbT = true;}
      else if(rjAFCgeuKh == BeUNJYbQda){AuxqudsGdn = true;}
      if(SDVqAOtQBS == kIOjKXaDuQ){UhdMuuXlOP = true;}
      else if(kIOjKXaDuQ == SDVqAOtQBS){EQTMXfxSPE = true;}
      if(HHnJkkDihr == QmCOPxYHeh){MkSplRrDjt = true;}
      else if(QmCOPxYHeh == HHnJkkDihr){RFwDHMJoMd = true;}
      if(HaCikmOXqu == KuwazcwLcJ){VHVrAKjaCH = true;}
      if(opzFMtWGRC == WeDBFnnMHC){exyCYMfKbG = true;}
      if(CEAnztqLbY == UDRVEFhloE){acNODqgkmI = true;}
      while(KuwazcwLcJ == HaCikmOXqu){OVLFYpijhn = true;}
      while(WeDBFnnMHC == WeDBFnnMHC){AncBEMdaWN = true;}
      while(UDRVEFhloE == UDRVEFhloE){JhAAsuytih = true;}
      if(HXPbWpLnjh == true){HXPbWpLnjh = false;}
      if(bOalskjAIb == true){bOalskjAIb = false;}
      if(JMAcNHcaVt == true){JMAcNHcaVt = false;}
      if(uKWXBzPbeP == true){uKWXBzPbeP = false;}
      if(bzbZZFbfbT == true){bzbZZFbfbT = false;}
      if(UhdMuuXlOP == true){UhdMuuXlOP = false;}
      if(MkSplRrDjt == true){MkSplRrDjt = false;}
      if(VHVrAKjaCH == true){VHVrAKjaCH = false;}
      if(exyCYMfKbG == true){exyCYMfKbG = false;}
      if(acNODqgkmI == true){acNODqgkmI = false;}
      if(NYwhxMLkMk == true){NYwhxMLkMk = false;}
      if(LxjGjPlQRZ == true){LxjGjPlQRZ = false;}
      if(kgacSstGoI == true){kgacSstGoI = false;}
      if(cynttGAPEL == true){cynttGAPEL = false;}
      if(AuxqudsGdn == true){AuxqudsGdn = false;}
      if(EQTMXfxSPE == true){EQTMXfxSPE = false;}
      if(RFwDHMJoMd == true){RFwDHMJoMd = false;}
      if(OVLFYpijhn == true){OVLFYpijhn = false;}
      if(AncBEMdaWN == true){AncBEMdaWN = false;}
      if(JhAAsuytih == true){JhAAsuytih = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZHZOJNDJOK
{ 
  void DsLgIjSHwE()
  { 
      bool ZcxMCwQNDT = false;
      bool LwthlGGVmG = false;
      bool qWaUJeLFIt = false;
      bool DYDgsLoUhK = false;
      bool wLAAkuWpHI = false;
      bool gTahdDBbCX = false;
      bool jLEJPlsNoa = false;
      bool QknbJeVajN = false;
      bool HVxANjyUDp = false;
      bool JNRKakGqjy = false;
      bool CJBfrufyXy = false;
      bool gaqoPONEuf = false;
      bool nXJyQCTdBY = false;
      bool XdpkLyURIS = false;
      bool EzwEIiVctL = false;
      bool WCwEJezCOo = false;
      bool aBxzZCjFcR = false;
      bool twucboaFph = false;
      bool gqioCVhlbf = false;
      bool ySCSqCCxdF = false;
      string izlUeCRgOG;
      string FieVMdJuTZ;
      string UdwVSZoKHe;
      string nZyTTWQdCX;
      string xIBMjdCnNA;
      string aclJLFCPBF;
      string MHZjSejLCp;
      string NesucMcjlo;
      string WBxGEKnoIN;
      string UBbwLpiRsE;
      string sqlWmwjqgy;
      string bRcMhLJSfI;
      string quCnVMCwjm;
      string dLphufOZTH;
      string axHJlCXPOz;
      string fPkkNynxBZ;
      string snGtUQbuRB;
      string wjyXgtmrCT;
      string nmgjGNZETw;
      string qRXsOmpNoU;
      if(izlUeCRgOG == sqlWmwjqgy){ZcxMCwQNDT = true;}
      else if(sqlWmwjqgy == izlUeCRgOG){CJBfrufyXy = true;}
      if(FieVMdJuTZ == bRcMhLJSfI){LwthlGGVmG = true;}
      else if(bRcMhLJSfI == FieVMdJuTZ){gaqoPONEuf = true;}
      if(UdwVSZoKHe == quCnVMCwjm){qWaUJeLFIt = true;}
      else if(quCnVMCwjm == UdwVSZoKHe){nXJyQCTdBY = true;}
      if(nZyTTWQdCX == dLphufOZTH){DYDgsLoUhK = true;}
      else if(dLphufOZTH == nZyTTWQdCX){XdpkLyURIS = true;}
      if(xIBMjdCnNA == axHJlCXPOz){wLAAkuWpHI = true;}
      else if(axHJlCXPOz == xIBMjdCnNA){EzwEIiVctL = true;}
      if(aclJLFCPBF == fPkkNynxBZ){gTahdDBbCX = true;}
      else if(fPkkNynxBZ == aclJLFCPBF){WCwEJezCOo = true;}
      if(MHZjSejLCp == snGtUQbuRB){jLEJPlsNoa = true;}
      else if(snGtUQbuRB == MHZjSejLCp){aBxzZCjFcR = true;}
      if(NesucMcjlo == wjyXgtmrCT){QknbJeVajN = true;}
      if(WBxGEKnoIN == nmgjGNZETw){HVxANjyUDp = true;}
      if(UBbwLpiRsE == qRXsOmpNoU){JNRKakGqjy = true;}
      while(wjyXgtmrCT == NesucMcjlo){twucboaFph = true;}
      while(nmgjGNZETw == nmgjGNZETw){gqioCVhlbf = true;}
      while(qRXsOmpNoU == qRXsOmpNoU){ySCSqCCxdF = true;}
      if(ZcxMCwQNDT == true){ZcxMCwQNDT = false;}
      if(LwthlGGVmG == true){LwthlGGVmG = false;}
      if(qWaUJeLFIt == true){qWaUJeLFIt = false;}
      if(DYDgsLoUhK == true){DYDgsLoUhK = false;}
      if(wLAAkuWpHI == true){wLAAkuWpHI = false;}
      if(gTahdDBbCX == true){gTahdDBbCX = false;}
      if(jLEJPlsNoa == true){jLEJPlsNoa = false;}
      if(QknbJeVajN == true){QknbJeVajN = false;}
      if(HVxANjyUDp == true){HVxANjyUDp = false;}
      if(JNRKakGqjy == true){JNRKakGqjy = false;}
      if(CJBfrufyXy == true){CJBfrufyXy = false;}
      if(gaqoPONEuf == true){gaqoPONEuf = false;}
      if(nXJyQCTdBY == true){nXJyQCTdBY = false;}
      if(XdpkLyURIS == true){XdpkLyURIS = false;}
      if(EzwEIiVctL == true){EzwEIiVctL = false;}
      if(WCwEJezCOo == true){WCwEJezCOo = false;}
      if(aBxzZCjFcR == true){aBxzZCjFcR = false;}
      if(twucboaFph == true){twucboaFph = false;}
      if(gqioCVhlbf == true){gqioCVhlbf = false;}
      if(ySCSqCCxdF == true){ySCSqCCxdF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFGKBYMYNJ
{ 
  void cfWjODGbQi()
  { 
      bool gZihHsBLOJ = false;
      bool WVTlmpoMwp = false;
      bool cDCQGMQfOq = false;
      bool BaFJdyeAcL = false;
      bool gSNtPyEhnc = false;
      bool PwelJcWSau = false;
      bool cUwXHwQJIo = false;
      bool LnikJKpIAI = false;
      bool IhrlbFuSAA = false;
      bool aMZhhLVolS = false;
      bool huZzRaMscy = false;
      bool mORSmtcJwC = false;
      bool AxIHNyOBCx = false;
      bool nAVhZMIrUA = false;
      bool rCoCMMuGun = false;
      bool hMsjRklRkS = false;
      bool MLpeKmsjsZ = false;
      bool kjnuJyHGuB = false;
      bool DIFOObGkPo = false;
      bool ZqHCnfLJqY = false;
      string NNwwOeHaXg;
      string OMlnbRjWgs;
      string xKXEQDMPem;
      string OKRhaWDhUj;
      string aAlBrzqSac;
      string ITZDODorfK;
      string SrwkSEtDNF;
      string OCCwSxYVMQ;
      string LsnBdtkOTX;
      string gLBJRiEAin;
      string EmFVOFRckR;
      string eTeOzYDtGX;
      string SfjoXDAsej;
      string rXmYLXnRlX;
      string cHcBsNflJs;
      string eJtKUYDPxK;
      string FXyBYGfGDa;
      string kkHhuLChwK;
      string XOikEidcDl;
      string TXUbSEJbcl;
      if(NNwwOeHaXg == EmFVOFRckR){gZihHsBLOJ = true;}
      else if(EmFVOFRckR == NNwwOeHaXg){huZzRaMscy = true;}
      if(OMlnbRjWgs == eTeOzYDtGX){WVTlmpoMwp = true;}
      else if(eTeOzYDtGX == OMlnbRjWgs){mORSmtcJwC = true;}
      if(xKXEQDMPem == SfjoXDAsej){cDCQGMQfOq = true;}
      else if(SfjoXDAsej == xKXEQDMPem){AxIHNyOBCx = true;}
      if(OKRhaWDhUj == rXmYLXnRlX){BaFJdyeAcL = true;}
      else if(rXmYLXnRlX == OKRhaWDhUj){nAVhZMIrUA = true;}
      if(aAlBrzqSac == cHcBsNflJs){gSNtPyEhnc = true;}
      else if(cHcBsNflJs == aAlBrzqSac){rCoCMMuGun = true;}
      if(ITZDODorfK == eJtKUYDPxK){PwelJcWSau = true;}
      else if(eJtKUYDPxK == ITZDODorfK){hMsjRklRkS = true;}
      if(SrwkSEtDNF == FXyBYGfGDa){cUwXHwQJIo = true;}
      else if(FXyBYGfGDa == SrwkSEtDNF){MLpeKmsjsZ = true;}
      if(OCCwSxYVMQ == kkHhuLChwK){LnikJKpIAI = true;}
      if(LsnBdtkOTX == XOikEidcDl){IhrlbFuSAA = true;}
      if(gLBJRiEAin == TXUbSEJbcl){aMZhhLVolS = true;}
      while(kkHhuLChwK == OCCwSxYVMQ){kjnuJyHGuB = true;}
      while(XOikEidcDl == XOikEidcDl){DIFOObGkPo = true;}
      while(TXUbSEJbcl == TXUbSEJbcl){ZqHCnfLJqY = true;}
      if(gZihHsBLOJ == true){gZihHsBLOJ = false;}
      if(WVTlmpoMwp == true){WVTlmpoMwp = false;}
      if(cDCQGMQfOq == true){cDCQGMQfOq = false;}
      if(BaFJdyeAcL == true){BaFJdyeAcL = false;}
      if(gSNtPyEhnc == true){gSNtPyEhnc = false;}
      if(PwelJcWSau == true){PwelJcWSau = false;}
      if(cUwXHwQJIo == true){cUwXHwQJIo = false;}
      if(LnikJKpIAI == true){LnikJKpIAI = false;}
      if(IhrlbFuSAA == true){IhrlbFuSAA = false;}
      if(aMZhhLVolS == true){aMZhhLVolS = false;}
      if(huZzRaMscy == true){huZzRaMscy = false;}
      if(mORSmtcJwC == true){mORSmtcJwC = false;}
      if(AxIHNyOBCx == true){AxIHNyOBCx = false;}
      if(nAVhZMIrUA == true){nAVhZMIrUA = false;}
      if(rCoCMMuGun == true){rCoCMMuGun = false;}
      if(hMsjRklRkS == true){hMsjRklRkS = false;}
      if(MLpeKmsjsZ == true){MLpeKmsjsZ = false;}
      if(kjnuJyHGuB == true){kjnuJyHGuB = false;}
      if(DIFOObGkPo == true){DIFOObGkPo = false;}
      if(ZqHCnfLJqY == true){ZqHCnfLJqY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIROTQFBAD
{ 
  void jGziadZDTY()
  { 
      bool iKTGTSlHNY = false;
      bool alPneBzYfx = false;
      bool XOIrdkoEZW = false;
      bool mGhQVEtcGw = false;
      bool OdxhyaIBgZ = false;
      bool PNwczUBabi = false;
      bool dghpkUDzRa = false;
      bool HVRjhsRZsD = false;
      bool bmXzHZKFRB = false;
      bool CSAXRhwGwd = false;
      bool WJiGSswMuF = false;
      bool CahYGqJhiL = false;
      bool KygQYnVsRA = false;
      bool xLdOfSERfN = false;
      bool cxJMyakbQa = false;
      bool XNWjTYbRge = false;
      bool XCtuHqxSrm = false;
      bool mqCUiMnUSx = false;
      bool DsbqbinsuH = false;
      bool qljBpaDOEH = false;
      string GJSPLSGQNQ;
      string UDRsdTkRZl;
      string KDffJYeDHM;
      string PROHnWiujE;
      string NhEkOGmdNT;
      string EzZgfCdmGl;
      string nCJBADnJFG;
      string kogVXcytQC;
      string lBpnHQqgbk;
      string rwoyQKYDjK;
      string RcXHiPREIC;
      string EjVDAlMVtj;
      string MHhUNoziEN;
      string EuKFkIchFr;
      string ylXYfIZlyd;
      string xCJzyKuDss;
      string PizuyJZPSq;
      string JdQBlZiInF;
      string ONjaPBkKGZ;
      string MYoLbOlbZW;
      if(GJSPLSGQNQ == RcXHiPREIC){iKTGTSlHNY = true;}
      else if(RcXHiPREIC == GJSPLSGQNQ){WJiGSswMuF = true;}
      if(UDRsdTkRZl == EjVDAlMVtj){alPneBzYfx = true;}
      else if(EjVDAlMVtj == UDRsdTkRZl){CahYGqJhiL = true;}
      if(KDffJYeDHM == MHhUNoziEN){XOIrdkoEZW = true;}
      else if(MHhUNoziEN == KDffJYeDHM){KygQYnVsRA = true;}
      if(PROHnWiujE == EuKFkIchFr){mGhQVEtcGw = true;}
      else if(EuKFkIchFr == PROHnWiujE){xLdOfSERfN = true;}
      if(NhEkOGmdNT == ylXYfIZlyd){OdxhyaIBgZ = true;}
      else if(ylXYfIZlyd == NhEkOGmdNT){cxJMyakbQa = true;}
      if(EzZgfCdmGl == xCJzyKuDss){PNwczUBabi = true;}
      else if(xCJzyKuDss == EzZgfCdmGl){XNWjTYbRge = true;}
      if(nCJBADnJFG == PizuyJZPSq){dghpkUDzRa = true;}
      else if(PizuyJZPSq == nCJBADnJFG){XCtuHqxSrm = true;}
      if(kogVXcytQC == JdQBlZiInF){HVRjhsRZsD = true;}
      if(lBpnHQqgbk == ONjaPBkKGZ){bmXzHZKFRB = true;}
      if(rwoyQKYDjK == MYoLbOlbZW){CSAXRhwGwd = true;}
      while(JdQBlZiInF == kogVXcytQC){mqCUiMnUSx = true;}
      while(ONjaPBkKGZ == ONjaPBkKGZ){DsbqbinsuH = true;}
      while(MYoLbOlbZW == MYoLbOlbZW){qljBpaDOEH = true;}
      if(iKTGTSlHNY == true){iKTGTSlHNY = false;}
      if(alPneBzYfx == true){alPneBzYfx = false;}
      if(XOIrdkoEZW == true){XOIrdkoEZW = false;}
      if(mGhQVEtcGw == true){mGhQVEtcGw = false;}
      if(OdxhyaIBgZ == true){OdxhyaIBgZ = false;}
      if(PNwczUBabi == true){PNwczUBabi = false;}
      if(dghpkUDzRa == true){dghpkUDzRa = false;}
      if(HVRjhsRZsD == true){HVRjhsRZsD = false;}
      if(bmXzHZKFRB == true){bmXzHZKFRB = false;}
      if(CSAXRhwGwd == true){CSAXRhwGwd = false;}
      if(WJiGSswMuF == true){WJiGSswMuF = false;}
      if(CahYGqJhiL == true){CahYGqJhiL = false;}
      if(KygQYnVsRA == true){KygQYnVsRA = false;}
      if(xLdOfSERfN == true){xLdOfSERfN = false;}
      if(cxJMyakbQa == true){cxJMyakbQa = false;}
      if(XNWjTYbRge == true){XNWjTYbRge = false;}
      if(XCtuHqxSrm == true){XCtuHqxSrm = false;}
      if(mqCUiMnUSx == true){mqCUiMnUSx = false;}
      if(DsbqbinsuH == true){DsbqbinsuH = false;}
      if(qljBpaDOEH == true){qljBpaDOEH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SURCVRHXTG
{ 
  void GquWgsLyzl()
  { 
      bool IXPgpeYpWk = false;
      bool IaGUgpXJZA = false;
      bool tWfzxZnstY = false;
      bool wnENCSomfz = false;
      bool uwAKGeYRDh = false;
      bool ETTGKlqPiQ = false;
      bool pfuynUWrSN = false;
      bool BjdaExWVsS = false;
      bool AVoMTcUyDP = false;
      bool bZDOIPACVk = false;
      bool HfzogTorCN = false;
      bool OVVPPTpidL = false;
      bool AYoClagORn = false;
      bool wUzIKUWzfA = false;
      bool mbwpAGDmzo = false;
      bool YRXKkiqxDF = false;
      bool maaNQtVNFu = false;
      bool xqCcXXbzBf = false;
      bool XsOcOewoWa = false;
      bool dZwZNMAhZF = false;
      string FoJNFXJQGj;
      string JYjDTifaVf;
      string OhPdQteHGR;
      string yWGckPMwpz;
      string zAndeoeuwj;
      string PgSUIWZfwK;
      string sCJoklRGRD;
      string WijVgOtlyb;
      string PiKWBQElUN;
      string pgzfFxpyrr;
      string WXdsNfwwns;
      string cmgUuKrmnU;
      string hflENpjEQi;
      string XwtFFqFRIU;
      string TIyakCzeju;
      string FDJWKplZeX;
      string wreEUfsbOD;
      string FZdTAZhKSK;
      string pFTVdUlWuO;
      string FelkYbcsGE;
      if(FoJNFXJQGj == WXdsNfwwns){IXPgpeYpWk = true;}
      else if(WXdsNfwwns == FoJNFXJQGj){HfzogTorCN = true;}
      if(JYjDTifaVf == cmgUuKrmnU){IaGUgpXJZA = true;}
      else if(cmgUuKrmnU == JYjDTifaVf){OVVPPTpidL = true;}
      if(OhPdQteHGR == hflENpjEQi){tWfzxZnstY = true;}
      else if(hflENpjEQi == OhPdQteHGR){AYoClagORn = true;}
      if(yWGckPMwpz == XwtFFqFRIU){wnENCSomfz = true;}
      else if(XwtFFqFRIU == yWGckPMwpz){wUzIKUWzfA = true;}
      if(zAndeoeuwj == TIyakCzeju){uwAKGeYRDh = true;}
      else if(TIyakCzeju == zAndeoeuwj){mbwpAGDmzo = true;}
      if(PgSUIWZfwK == FDJWKplZeX){ETTGKlqPiQ = true;}
      else if(FDJWKplZeX == PgSUIWZfwK){YRXKkiqxDF = true;}
      if(sCJoklRGRD == wreEUfsbOD){pfuynUWrSN = true;}
      else if(wreEUfsbOD == sCJoklRGRD){maaNQtVNFu = true;}
      if(WijVgOtlyb == FZdTAZhKSK){BjdaExWVsS = true;}
      if(PiKWBQElUN == pFTVdUlWuO){AVoMTcUyDP = true;}
      if(pgzfFxpyrr == FelkYbcsGE){bZDOIPACVk = true;}
      while(FZdTAZhKSK == WijVgOtlyb){xqCcXXbzBf = true;}
      while(pFTVdUlWuO == pFTVdUlWuO){XsOcOewoWa = true;}
      while(FelkYbcsGE == FelkYbcsGE){dZwZNMAhZF = true;}
      if(IXPgpeYpWk == true){IXPgpeYpWk = false;}
      if(IaGUgpXJZA == true){IaGUgpXJZA = false;}
      if(tWfzxZnstY == true){tWfzxZnstY = false;}
      if(wnENCSomfz == true){wnENCSomfz = false;}
      if(uwAKGeYRDh == true){uwAKGeYRDh = false;}
      if(ETTGKlqPiQ == true){ETTGKlqPiQ = false;}
      if(pfuynUWrSN == true){pfuynUWrSN = false;}
      if(BjdaExWVsS == true){BjdaExWVsS = false;}
      if(AVoMTcUyDP == true){AVoMTcUyDP = false;}
      if(bZDOIPACVk == true){bZDOIPACVk = false;}
      if(HfzogTorCN == true){HfzogTorCN = false;}
      if(OVVPPTpidL == true){OVVPPTpidL = false;}
      if(AYoClagORn == true){AYoClagORn = false;}
      if(wUzIKUWzfA == true){wUzIKUWzfA = false;}
      if(mbwpAGDmzo == true){mbwpAGDmzo = false;}
      if(YRXKkiqxDF == true){YRXKkiqxDF = false;}
      if(maaNQtVNFu == true){maaNQtVNFu = false;}
      if(xqCcXXbzBf == true){xqCcXXbzBf = false;}
      if(XsOcOewoWa == true){XsOcOewoWa = false;}
      if(dZwZNMAhZF == true){dZwZNMAhZF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRBLKKIQZF
{ 
  void lJzkBsEtTM()
  { 
      bool wEbzFAgKMR = false;
      bool MDbzDTuhhJ = false;
      bool pUxfrgwoKs = false;
      bool UaVcSOSshy = false;
      bool maixSIIKlX = false;
      bool IdcnmbHwGY = false;
      bool DrzSxkhygn = false;
      bool BCAiVOkAMj = false;
      bool XlClkpygpq = false;
      bool HWmJttbQzg = false;
      bool aJdxWGdtRX = false;
      bool pGiVARoMgG = false;
      bool mBIofdOqnb = false;
      bool mUBfJOIFPe = false;
      bool MEORAAmQIc = false;
      bool FOirsYAnQr = false;
      bool qlFpkVFDMl = false;
      bool IjxCsilqof = false;
      bool qyhKVXlIlj = false;
      bool OUnWnZyXfe = false;
      string NPUfpKUSig;
      string uYFahWecdf;
      string uOhSnyHXHQ;
      string KQPafSsTkK;
      string kNqYrjxqGl;
      string JdBipzgBrq;
      string CxLRWeJetO;
      string cKqTugXIaD;
      string BQQUGfPfjg;
      string lrbtImCYBN;
      string aRwrIylgnI;
      string aXZnokfpLq;
      string OctMckixKH;
      string ezHNcjTYMH;
      string shqaFNRmEW;
      string HLNKyxWiOW;
      string PoVgcbQMKF;
      string RGdDyfkTHP;
      string TusnzTkwOe;
      string MjJorELKxd;
      if(NPUfpKUSig == aRwrIylgnI){wEbzFAgKMR = true;}
      else if(aRwrIylgnI == NPUfpKUSig){aJdxWGdtRX = true;}
      if(uYFahWecdf == aXZnokfpLq){MDbzDTuhhJ = true;}
      else if(aXZnokfpLq == uYFahWecdf){pGiVARoMgG = true;}
      if(uOhSnyHXHQ == OctMckixKH){pUxfrgwoKs = true;}
      else if(OctMckixKH == uOhSnyHXHQ){mBIofdOqnb = true;}
      if(KQPafSsTkK == ezHNcjTYMH){UaVcSOSshy = true;}
      else if(ezHNcjTYMH == KQPafSsTkK){mUBfJOIFPe = true;}
      if(kNqYrjxqGl == shqaFNRmEW){maixSIIKlX = true;}
      else if(shqaFNRmEW == kNqYrjxqGl){MEORAAmQIc = true;}
      if(JdBipzgBrq == HLNKyxWiOW){IdcnmbHwGY = true;}
      else if(HLNKyxWiOW == JdBipzgBrq){FOirsYAnQr = true;}
      if(CxLRWeJetO == PoVgcbQMKF){DrzSxkhygn = true;}
      else if(PoVgcbQMKF == CxLRWeJetO){qlFpkVFDMl = true;}
      if(cKqTugXIaD == RGdDyfkTHP){BCAiVOkAMj = true;}
      if(BQQUGfPfjg == TusnzTkwOe){XlClkpygpq = true;}
      if(lrbtImCYBN == MjJorELKxd){HWmJttbQzg = true;}
      while(RGdDyfkTHP == cKqTugXIaD){IjxCsilqof = true;}
      while(TusnzTkwOe == TusnzTkwOe){qyhKVXlIlj = true;}
      while(MjJorELKxd == MjJorELKxd){OUnWnZyXfe = true;}
      if(wEbzFAgKMR == true){wEbzFAgKMR = false;}
      if(MDbzDTuhhJ == true){MDbzDTuhhJ = false;}
      if(pUxfrgwoKs == true){pUxfrgwoKs = false;}
      if(UaVcSOSshy == true){UaVcSOSshy = false;}
      if(maixSIIKlX == true){maixSIIKlX = false;}
      if(IdcnmbHwGY == true){IdcnmbHwGY = false;}
      if(DrzSxkhygn == true){DrzSxkhygn = false;}
      if(BCAiVOkAMj == true){BCAiVOkAMj = false;}
      if(XlClkpygpq == true){XlClkpygpq = false;}
      if(HWmJttbQzg == true){HWmJttbQzg = false;}
      if(aJdxWGdtRX == true){aJdxWGdtRX = false;}
      if(pGiVARoMgG == true){pGiVARoMgG = false;}
      if(mBIofdOqnb == true){mBIofdOqnb = false;}
      if(mUBfJOIFPe == true){mUBfJOIFPe = false;}
      if(MEORAAmQIc == true){MEORAAmQIc = false;}
      if(FOirsYAnQr == true){FOirsYAnQr = false;}
      if(qlFpkVFDMl == true){qlFpkVFDMl = false;}
      if(IjxCsilqof == true){IjxCsilqof = false;}
      if(qyhKVXlIlj == true){qyhKVXlIlj = false;}
      if(OUnWnZyXfe == true){OUnWnZyXfe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJUPAYHRZF
{ 
  void NAVuQcyREz()
  { 
      bool OqBaizboYw = false;
      bool utqIdWChSP = false;
      bool miuWgiLcol = false;
      bool ViKmPeJGBk = false;
      bool GBSQHpTLLe = false;
      bool hWLqnfwetz = false;
      bool nzzlZLiDrz = false;
      bool MufgIkPdPq = false;
      bool OzQKEzWTyj = false;
      bool heMBxHCgqu = false;
      bool GPSLRlpdhD = false;
      bool PRPDknhohZ = false;
      bool oPFIQhiejB = false;
      bool himTjzgFrR = false;
      bool IrkuUQOIQI = false;
      bool YMyQGqKKuj = false;
      bool DLsgUfduSk = false;
      bool HcxPRwdKnz = false;
      bool SZNbbVkWNs = false;
      bool nWJIOwzEZn = false;
      string rXeTOltPDE;
      string qEtKLBNnnE;
      string FNlgSSmrtY;
      string emGpkooNDm;
      string UYjMZCmydh;
      string UxhDJelyBu;
      string zCUdZDyDZW;
      string MzjBjgcYGP;
      string fnOLEhECgG;
      string CqMInSDGmW;
      string EiYHVUMgTb;
      string BMqkOKmIZq;
      string zuWTTUmbNQ;
      string dWljLxPHpi;
      string UXhFFozbsc;
      string ftfuWIMFmA;
      string hkSDydaHZR;
      string tfSqWaNRNe;
      string VLhjkiqqMC;
      string kKTpBjFeGa;
      if(rXeTOltPDE == EiYHVUMgTb){OqBaizboYw = true;}
      else if(EiYHVUMgTb == rXeTOltPDE){GPSLRlpdhD = true;}
      if(qEtKLBNnnE == BMqkOKmIZq){utqIdWChSP = true;}
      else if(BMqkOKmIZq == qEtKLBNnnE){PRPDknhohZ = true;}
      if(FNlgSSmrtY == zuWTTUmbNQ){miuWgiLcol = true;}
      else if(zuWTTUmbNQ == FNlgSSmrtY){oPFIQhiejB = true;}
      if(emGpkooNDm == dWljLxPHpi){ViKmPeJGBk = true;}
      else if(dWljLxPHpi == emGpkooNDm){himTjzgFrR = true;}
      if(UYjMZCmydh == UXhFFozbsc){GBSQHpTLLe = true;}
      else if(UXhFFozbsc == UYjMZCmydh){IrkuUQOIQI = true;}
      if(UxhDJelyBu == ftfuWIMFmA){hWLqnfwetz = true;}
      else if(ftfuWIMFmA == UxhDJelyBu){YMyQGqKKuj = true;}
      if(zCUdZDyDZW == hkSDydaHZR){nzzlZLiDrz = true;}
      else if(hkSDydaHZR == zCUdZDyDZW){DLsgUfduSk = true;}
      if(MzjBjgcYGP == tfSqWaNRNe){MufgIkPdPq = true;}
      if(fnOLEhECgG == VLhjkiqqMC){OzQKEzWTyj = true;}
      if(CqMInSDGmW == kKTpBjFeGa){heMBxHCgqu = true;}
      while(tfSqWaNRNe == MzjBjgcYGP){HcxPRwdKnz = true;}
      while(VLhjkiqqMC == VLhjkiqqMC){SZNbbVkWNs = true;}
      while(kKTpBjFeGa == kKTpBjFeGa){nWJIOwzEZn = true;}
      if(OqBaizboYw == true){OqBaizboYw = false;}
      if(utqIdWChSP == true){utqIdWChSP = false;}
      if(miuWgiLcol == true){miuWgiLcol = false;}
      if(ViKmPeJGBk == true){ViKmPeJGBk = false;}
      if(GBSQHpTLLe == true){GBSQHpTLLe = false;}
      if(hWLqnfwetz == true){hWLqnfwetz = false;}
      if(nzzlZLiDrz == true){nzzlZLiDrz = false;}
      if(MufgIkPdPq == true){MufgIkPdPq = false;}
      if(OzQKEzWTyj == true){OzQKEzWTyj = false;}
      if(heMBxHCgqu == true){heMBxHCgqu = false;}
      if(GPSLRlpdhD == true){GPSLRlpdhD = false;}
      if(PRPDknhohZ == true){PRPDknhohZ = false;}
      if(oPFIQhiejB == true){oPFIQhiejB = false;}
      if(himTjzgFrR == true){himTjzgFrR = false;}
      if(IrkuUQOIQI == true){IrkuUQOIQI = false;}
      if(YMyQGqKKuj == true){YMyQGqKKuj = false;}
      if(DLsgUfduSk == true){DLsgUfduSk = false;}
      if(HcxPRwdKnz == true){HcxPRwdKnz = false;}
      if(SZNbbVkWNs == true){SZNbbVkWNs = false;}
      if(nWJIOwzEZn == true){nWJIOwzEZn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJSLDYMOYU
{ 
  void JbXTyLhAcP()
  { 
      bool RLSyfNOtWA = false;
      bool ZVqzkNCLEj = false;
      bool xryiGbwVXJ = false;
      bool tnZXDrPxGH = false;
      bool AsUVwAfUts = false;
      bool wyQbEYMirE = false;
      bool RsVNGlwTus = false;
      bool xFFxjEXbmG = false;
      bool waaeMuXxSe = false;
      bool egFCoHWGPK = false;
      bool DLZBuqsSrA = false;
      bool AjukIqRqAK = false;
      bool NzBPNQzCIc = false;
      bool hQMcDjBZjV = false;
      bool CFERdtkTty = false;
      bool ofGEwEKJmd = false;
      bool qpKPRjXShX = false;
      bool prGeHItilT = false;
      bool efHJmCKHfy = false;
      bool YqlGdLtoAt = false;
      string fwzYWPtylZ;
      string YFaHPmoiTC;
      string UNaGOdEIhA;
      string yhdmGfXwaf;
      string UCsOKRthbo;
      string udGIxSUsKr;
      string KlPlapbnBi;
      string PrHnhRTLux;
      string jVgsETbVpm;
      string LeliUilGmT;
      string pFfrYCWSZe;
      string yIxNHoEVgG;
      string OFxOXjGXSz;
      string eNYbGdonUC;
      string xJuLnCgYbf;
      string dQZfFjIRUn;
      string uyzZzkjVGc;
      string zPBeIEJlZV;
      string DhwmVOnrWW;
      string VXTfGzKUMC;
      if(fwzYWPtylZ == pFfrYCWSZe){RLSyfNOtWA = true;}
      else if(pFfrYCWSZe == fwzYWPtylZ){DLZBuqsSrA = true;}
      if(YFaHPmoiTC == yIxNHoEVgG){ZVqzkNCLEj = true;}
      else if(yIxNHoEVgG == YFaHPmoiTC){AjukIqRqAK = true;}
      if(UNaGOdEIhA == OFxOXjGXSz){xryiGbwVXJ = true;}
      else if(OFxOXjGXSz == UNaGOdEIhA){NzBPNQzCIc = true;}
      if(yhdmGfXwaf == eNYbGdonUC){tnZXDrPxGH = true;}
      else if(eNYbGdonUC == yhdmGfXwaf){hQMcDjBZjV = true;}
      if(UCsOKRthbo == xJuLnCgYbf){AsUVwAfUts = true;}
      else if(xJuLnCgYbf == UCsOKRthbo){CFERdtkTty = true;}
      if(udGIxSUsKr == dQZfFjIRUn){wyQbEYMirE = true;}
      else if(dQZfFjIRUn == udGIxSUsKr){ofGEwEKJmd = true;}
      if(KlPlapbnBi == uyzZzkjVGc){RsVNGlwTus = true;}
      else if(uyzZzkjVGc == KlPlapbnBi){qpKPRjXShX = true;}
      if(PrHnhRTLux == zPBeIEJlZV){xFFxjEXbmG = true;}
      if(jVgsETbVpm == DhwmVOnrWW){waaeMuXxSe = true;}
      if(LeliUilGmT == VXTfGzKUMC){egFCoHWGPK = true;}
      while(zPBeIEJlZV == PrHnhRTLux){prGeHItilT = true;}
      while(DhwmVOnrWW == DhwmVOnrWW){efHJmCKHfy = true;}
      while(VXTfGzKUMC == VXTfGzKUMC){YqlGdLtoAt = true;}
      if(RLSyfNOtWA == true){RLSyfNOtWA = false;}
      if(ZVqzkNCLEj == true){ZVqzkNCLEj = false;}
      if(xryiGbwVXJ == true){xryiGbwVXJ = false;}
      if(tnZXDrPxGH == true){tnZXDrPxGH = false;}
      if(AsUVwAfUts == true){AsUVwAfUts = false;}
      if(wyQbEYMirE == true){wyQbEYMirE = false;}
      if(RsVNGlwTus == true){RsVNGlwTus = false;}
      if(xFFxjEXbmG == true){xFFxjEXbmG = false;}
      if(waaeMuXxSe == true){waaeMuXxSe = false;}
      if(egFCoHWGPK == true){egFCoHWGPK = false;}
      if(DLZBuqsSrA == true){DLZBuqsSrA = false;}
      if(AjukIqRqAK == true){AjukIqRqAK = false;}
      if(NzBPNQzCIc == true){NzBPNQzCIc = false;}
      if(hQMcDjBZjV == true){hQMcDjBZjV = false;}
      if(CFERdtkTty == true){CFERdtkTty = false;}
      if(ofGEwEKJmd == true){ofGEwEKJmd = false;}
      if(qpKPRjXShX == true){qpKPRjXShX = false;}
      if(prGeHItilT == true){prGeHItilT = false;}
      if(efHJmCKHfy == true){efHJmCKHfy = false;}
      if(YqlGdLtoAt == true){YqlGdLtoAt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKIGQZEBQC
{ 
  void tWGmcYDuFX()
  { 
      bool xlYTbLrQui = false;
      bool KhUaFkXrWp = false;
      bool LlrbqEusFR = false;
      bool tZLDQEWcwx = false;
      bool quoLHgMdTV = false;
      bool ZwXBpKswcX = false;
      bool PzLcokVRJB = false;
      bool OtuZzPxgUK = false;
      bool rRYjrxBJMG = false;
      bool LZAYgrjMVV = false;
      bool KtUSGeByCa = false;
      bool NMbReyZbkr = false;
      bool jLEDontVrH = false;
      bool fjKyzxwGcM = false;
      bool uCHlrzyhti = false;
      bool RHaclypQcS = false;
      bool keFuucBcSg = false;
      bool BTyXwgDSKp = false;
      bool oLbJoXIgMA = false;
      bool HecJbPxMpP = false;
      string VCzsiDWNtL;
      string KdMxaoFxNu;
      string UkocZWsLnI;
      string MKFDaCxesR;
      string SZPuHAPduE;
      string XyAdQjNVSM;
      string JLYkzAXIWX;
      string qaDucuUsUZ;
      string GPQjkOKbmp;
      string oaLfIHAdwH;
      string bGHWNwtEBU;
      string PTBrFttoAk;
      string owVfiQOXmU;
      string upwNyzHsVn;
      string TGaRaUZSZN;
      string MLdLSfkanw;
      string gVQfZYXntF;
      string lASMQiUDFN;
      string quxYIiMkuR;
      string OgFZGyourC;
      if(VCzsiDWNtL == bGHWNwtEBU){xlYTbLrQui = true;}
      else if(bGHWNwtEBU == VCzsiDWNtL){KtUSGeByCa = true;}
      if(KdMxaoFxNu == PTBrFttoAk){KhUaFkXrWp = true;}
      else if(PTBrFttoAk == KdMxaoFxNu){NMbReyZbkr = true;}
      if(UkocZWsLnI == owVfiQOXmU){LlrbqEusFR = true;}
      else if(owVfiQOXmU == UkocZWsLnI){jLEDontVrH = true;}
      if(MKFDaCxesR == upwNyzHsVn){tZLDQEWcwx = true;}
      else if(upwNyzHsVn == MKFDaCxesR){fjKyzxwGcM = true;}
      if(SZPuHAPduE == TGaRaUZSZN){quoLHgMdTV = true;}
      else if(TGaRaUZSZN == SZPuHAPduE){uCHlrzyhti = true;}
      if(XyAdQjNVSM == MLdLSfkanw){ZwXBpKswcX = true;}
      else if(MLdLSfkanw == XyAdQjNVSM){RHaclypQcS = true;}
      if(JLYkzAXIWX == gVQfZYXntF){PzLcokVRJB = true;}
      else if(gVQfZYXntF == JLYkzAXIWX){keFuucBcSg = true;}
      if(qaDucuUsUZ == lASMQiUDFN){OtuZzPxgUK = true;}
      if(GPQjkOKbmp == quxYIiMkuR){rRYjrxBJMG = true;}
      if(oaLfIHAdwH == OgFZGyourC){LZAYgrjMVV = true;}
      while(lASMQiUDFN == qaDucuUsUZ){BTyXwgDSKp = true;}
      while(quxYIiMkuR == quxYIiMkuR){oLbJoXIgMA = true;}
      while(OgFZGyourC == OgFZGyourC){HecJbPxMpP = true;}
      if(xlYTbLrQui == true){xlYTbLrQui = false;}
      if(KhUaFkXrWp == true){KhUaFkXrWp = false;}
      if(LlrbqEusFR == true){LlrbqEusFR = false;}
      if(tZLDQEWcwx == true){tZLDQEWcwx = false;}
      if(quoLHgMdTV == true){quoLHgMdTV = false;}
      if(ZwXBpKswcX == true){ZwXBpKswcX = false;}
      if(PzLcokVRJB == true){PzLcokVRJB = false;}
      if(OtuZzPxgUK == true){OtuZzPxgUK = false;}
      if(rRYjrxBJMG == true){rRYjrxBJMG = false;}
      if(LZAYgrjMVV == true){LZAYgrjMVV = false;}
      if(KtUSGeByCa == true){KtUSGeByCa = false;}
      if(NMbReyZbkr == true){NMbReyZbkr = false;}
      if(jLEDontVrH == true){jLEDontVrH = false;}
      if(fjKyzxwGcM == true){fjKyzxwGcM = false;}
      if(uCHlrzyhti == true){uCHlrzyhti = false;}
      if(RHaclypQcS == true){RHaclypQcS = false;}
      if(keFuucBcSg == true){keFuucBcSg = false;}
      if(BTyXwgDSKp == true){BTyXwgDSKp = false;}
      if(oLbJoXIgMA == true){oLbJoXIgMA = false;}
      if(HecJbPxMpP == true){HecJbPxMpP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVNMKSYBNT
{ 
  void xbVcBCKLip()
  { 
      bool doGZGNueXk = false;
      bool PcBKhYmOit = false;
      bool XGFAgirjQI = false;
      bool AoaPgcbIrr = false;
      bool DdbwzmjRli = false;
      bool ujLmJWiFrW = false;
      bool UKNPjaClcF = false;
      bool xeVppteJBs = false;
      bool zaygMQdmFK = false;
      bool sVPUXsPMLX = false;
      bool kyoglQOUwP = false;
      bool rZEzXtMgCS = false;
      bool xOfSLaOASx = false;
      bool dRxcIAlQtw = false;
      bool CIppRSRQxc = false;
      bool giKraVRVUL = false;
      bool BNBzkacapX = false;
      bool IulGQnXpAr = false;
      bool JyDoQuHECm = false;
      bool hPwitnHqEq = false;
      string HLwuNkZVJI;
      string YRiXLVSRFc;
      string nKNcireoft;
      string gIihDGyMqr;
      string lPHmNBVfYR;
      string SBEUQwxSLV;
      string GjoPaQhATF;
      string XGaNpYDaOh;
      string WyQObeDORH;
      string IeAVkBZqLx;
      string SUMSsMapdq;
      string rWDdzISZnw;
      string MTiMxsFEco;
      string yLPROBlyUP;
      string EMjZOkaWWc;
      string hADOkzkzVA;
      string HVNosgHlPx;
      string VUEYqziIxL;
      string RhhzGyIAgO;
      string QlbUIiytgh;
      if(HLwuNkZVJI == SUMSsMapdq){doGZGNueXk = true;}
      else if(SUMSsMapdq == HLwuNkZVJI){kyoglQOUwP = true;}
      if(YRiXLVSRFc == rWDdzISZnw){PcBKhYmOit = true;}
      else if(rWDdzISZnw == YRiXLVSRFc){rZEzXtMgCS = true;}
      if(nKNcireoft == MTiMxsFEco){XGFAgirjQI = true;}
      else if(MTiMxsFEco == nKNcireoft){xOfSLaOASx = true;}
      if(gIihDGyMqr == yLPROBlyUP){AoaPgcbIrr = true;}
      else if(yLPROBlyUP == gIihDGyMqr){dRxcIAlQtw = true;}
      if(lPHmNBVfYR == EMjZOkaWWc){DdbwzmjRli = true;}
      else if(EMjZOkaWWc == lPHmNBVfYR){CIppRSRQxc = true;}
      if(SBEUQwxSLV == hADOkzkzVA){ujLmJWiFrW = true;}
      else if(hADOkzkzVA == SBEUQwxSLV){giKraVRVUL = true;}
      if(GjoPaQhATF == HVNosgHlPx){UKNPjaClcF = true;}
      else if(HVNosgHlPx == GjoPaQhATF){BNBzkacapX = true;}
      if(XGaNpYDaOh == VUEYqziIxL){xeVppteJBs = true;}
      if(WyQObeDORH == RhhzGyIAgO){zaygMQdmFK = true;}
      if(IeAVkBZqLx == QlbUIiytgh){sVPUXsPMLX = true;}
      while(VUEYqziIxL == XGaNpYDaOh){IulGQnXpAr = true;}
      while(RhhzGyIAgO == RhhzGyIAgO){JyDoQuHECm = true;}
      while(QlbUIiytgh == QlbUIiytgh){hPwitnHqEq = true;}
      if(doGZGNueXk == true){doGZGNueXk = false;}
      if(PcBKhYmOit == true){PcBKhYmOit = false;}
      if(XGFAgirjQI == true){XGFAgirjQI = false;}
      if(AoaPgcbIrr == true){AoaPgcbIrr = false;}
      if(DdbwzmjRli == true){DdbwzmjRli = false;}
      if(ujLmJWiFrW == true){ujLmJWiFrW = false;}
      if(UKNPjaClcF == true){UKNPjaClcF = false;}
      if(xeVppteJBs == true){xeVppteJBs = false;}
      if(zaygMQdmFK == true){zaygMQdmFK = false;}
      if(sVPUXsPMLX == true){sVPUXsPMLX = false;}
      if(kyoglQOUwP == true){kyoglQOUwP = false;}
      if(rZEzXtMgCS == true){rZEzXtMgCS = false;}
      if(xOfSLaOASx == true){xOfSLaOASx = false;}
      if(dRxcIAlQtw == true){dRxcIAlQtw = false;}
      if(CIppRSRQxc == true){CIppRSRQxc = false;}
      if(giKraVRVUL == true){giKraVRVUL = false;}
      if(BNBzkacapX == true){BNBzkacapX = false;}
      if(IulGQnXpAr == true){IulGQnXpAr = false;}
      if(JyDoQuHECm == true){JyDoQuHECm = false;}
      if(hPwitnHqEq == true){hPwitnHqEq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQQILBTZOK
{ 
  void ZcpWzUjgPt()
  { 
      bool DhlInXQuzM = false;
      bool JOPJEXHwrf = false;
      bool GTVSteGhlh = false;
      bool eUWdBCyIbY = false;
      bool jgPxZoOuuN = false;
      bool phRAijLTOJ = false;
      bool QiJRhnrlHC = false;
      bool ZyTSwYDYrE = false;
      bool PLmXqxDWtQ = false;
      bool pdtSIAXyOl = false;
      bool xcmrnrNyDK = false;
      bool fmbJtFwkZk = false;
      bool kUqpLuEBKw = false;
      bool BFJFGmYtjz = false;
      bool iESjkCCkYD = false;
      bool EmXdAbkwfr = false;
      bool nMnHIZdVCH = false;
      bool fBAZBfCHFJ = false;
      bool rScGqNhfFd = false;
      bool BbNrLWPLaK = false;
      string nMIUkYzrnC;
      string ylRYtNQJON;
      string xUysFGNtpt;
      string ZemCZhodGe;
      string SYhOqQzYTM;
      string SCKQGTOOPd;
      string KEBtcTzOyM;
      string YmCitXliCo;
      string HnZdaXTVwG;
      string TZOcTNXnlW;
      string RkaHnfzbWh;
      string gfLZVWdXTF;
      string AcRrryXZOg;
      string AywfXWNSot;
      string XqzOYmNnHx;
      string izUgVnSiOo;
      string HZNogiifCy;
      string JLhYgIdDSF;
      string jjRQxBcPJj;
      string EeEAlydJgo;
      if(nMIUkYzrnC == RkaHnfzbWh){DhlInXQuzM = true;}
      else if(RkaHnfzbWh == nMIUkYzrnC){xcmrnrNyDK = true;}
      if(ylRYtNQJON == gfLZVWdXTF){JOPJEXHwrf = true;}
      else if(gfLZVWdXTF == ylRYtNQJON){fmbJtFwkZk = true;}
      if(xUysFGNtpt == AcRrryXZOg){GTVSteGhlh = true;}
      else if(AcRrryXZOg == xUysFGNtpt){kUqpLuEBKw = true;}
      if(ZemCZhodGe == AywfXWNSot){eUWdBCyIbY = true;}
      else if(AywfXWNSot == ZemCZhodGe){BFJFGmYtjz = true;}
      if(SYhOqQzYTM == XqzOYmNnHx){jgPxZoOuuN = true;}
      else if(XqzOYmNnHx == SYhOqQzYTM){iESjkCCkYD = true;}
      if(SCKQGTOOPd == izUgVnSiOo){phRAijLTOJ = true;}
      else if(izUgVnSiOo == SCKQGTOOPd){EmXdAbkwfr = true;}
      if(KEBtcTzOyM == HZNogiifCy){QiJRhnrlHC = true;}
      else if(HZNogiifCy == KEBtcTzOyM){nMnHIZdVCH = true;}
      if(YmCitXliCo == JLhYgIdDSF){ZyTSwYDYrE = true;}
      if(HnZdaXTVwG == jjRQxBcPJj){PLmXqxDWtQ = true;}
      if(TZOcTNXnlW == EeEAlydJgo){pdtSIAXyOl = true;}
      while(JLhYgIdDSF == YmCitXliCo){fBAZBfCHFJ = true;}
      while(jjRQxBcPJj == jjRQxBcPJj){rScGqNhfFd = true;}
      while(EeEAlydJgo == EeEAlydJgo){BbNrLWPLaK = true;}
      if(DhlInXQuzM == true){DhlInXQuzM = false;}
      if(JOPJEXHwrf == true){JOPJEXHwrf = false;}
      if(GTVSteGhlh == true){GTVSteGhlh = false;}
      if(eUWdBCyIbY == true){eUWdBCyIbY = false;}
      if(jgPxZoOuuN == true){jgPxZoOuuN = false;}
      if(phRAijLTOJ == true){phRAijLTOJ = false;}
      if(QiJRhnrlHC == true){QiJRhnrlHC = false;}
      if(ZyTSwYDYrE == true){ZyTSwYDYrE = false;}
      if(PLmXqxDWtQ == true){PLmXqxDWtQ = false;}
      if(pdtSIAXyOl == true){pdtSIAXyOl = false;}
      if(xcmrnrNyDK == true){xcmrnrNyDK = false;}
      if(fmbJtFwkZk == true){fmbJtFwkZk = false;}
      if(kUqpLuEBKw == true){kUqpLuEBKw = false;}
      if(BFJFGmYtjz == true){BFJFGmYtjz = false;}
      if(iESjkCCkYD == true){iESjkCCkYD = false;}
      if(EmXdAbkwfr == true){EmXdAbkwfr = false;}
      if(nMnHIZdVCH == true){nMnHIZdVCH = false;}
      if(fBAZBfCHFJ == true){fBAZBfCHFJ = false;}
      if(rScGqNhfFd == true){rScGqNhfFd = false;}
      if(BbNrLWPLaK == true){BbNrLWPLaK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TASNBMSFHM
{ 
  void WbVJKNbJxa()
  { 
      bool accHFtFiKR = false;
      bool oSutRnUQNp = false;
      bool GkcTZEDpkf = false;
      bool ifKJdnTjsw = false;
      bool nhgRAIqlRh = false;
      bool cGPYopzJhB = false;
      bool pPxdiIHkPc = false;
      bool TjXQBYEKSQ = false;
      bool NRXDCbQlUn = false;
      bool nJCrFXjDir = false;
      bool AFVnNshyXP = false;
      bool loqQmYqtaG = false;
      bool rVQaoKhfKc = false;
      bool oAbaQIujpJ = false;
      bool tRNECzSkEg = false;
      bool gocbzeotzC = false;
      bool KCntakMQAe = false;
      bool dHEQMZHMYo = false;
      bool rwadwzXAak = false;
      bool SAjmzqdTcQ = false;
      string xhlOGLdXLo;
      string fFAOHirXuR;
      string QGLnfuQXXU;
      string WlBPpjMVqW;
      string BVuyMxFBgO;
      string rukqFpWyiL;
      string tGApRtDkYX;
      string WWgYQuLMai;
      string oPpJcaAKKz;
      string NNlebtVEfR;
      string sUbJqVOMaJ;
      string eJWzVeQqNq;
      string ssaZJIjBwV;
      string YHgIpUnfRG;
      string LmiATEqmJx;
      string depoYzsBAi;
      string kNQFjXcNJB;
      string qjYGeGKaGF;
      string RxrzqtQqjp;
      string alfiVyWdPw;
      if(xhlOGLdXLo == sUbJqVOMaJ){accHFtFiKR = true;}
      else if(sUbJqVOMaJ == xhlOGLdXLo){AFVnNshyXP = true;}
      if(fFAOHirXuR == eJWzVeQqNq){oSutRnUQNp = true;}
      else if(eJWzVeQqNq == fFAOHirXuR){loqQmYqtaG = true;}
      if(QGLnfuQXXU == ssaZJIjBwV){GkcTZEDpkf = true;}
      else if(ssaZJIjBwV == QGLnfuQXXU){rVQaoKhfKc = true;}
      if(WlBPpjMVqW == YHgIpUnfRG){ifKJdnTjsw = true;}
      else if(YHgIpUnfRG == WlBPpjMVqW){oAbaQIujpJ = true;}
      if(BVuyMxFBgO == LmiATEqmJx){nhgRAIqlRh = true;}
      else if(LmiATEqmJx == BVuyMxFBgO){tRNECzSkEg = true;}
      if(rukqFpWyiL == depoYzsBAi){cGPYopzJhB = true;}
      else if(depoYzsBAi == rukqFpWyiL){gocbzeotzC = true;}
      if(tGApRtDkYX == kNQFjXcNJB){pPxdiIHkPc = true;}
      else if(kNQFjXcNJB == tGApRtDkYX){KCntakMQAe = true;}
      if(WWgYQuLMai == qjYGeGKaGF){TjXQBYEKSQ = true;}
      if(oPpJcaAKKz == RxrzqtQqjp){NRXDCbQlUn = true;}
      if(NNlebtVEfR == alfiVyWdPw){nJCrFXjDir = true;}
      while(qjYGeGKaGF == WWgYQuLMai){dHEQMZHMYo = true;}
      while(RxrzqtQqjp == RxrzqtQqjp){rwadwzXAak = true;}
      while(alfiVyWdPw == alfiVyWdPw){SAjmzqdTcQ = true;}
      if(accHFtFiKR == true){accHFtFiKR = false;}
      if(oSutRnUQNp == true){oSutRnUQNp = false;}
      if(GkcTZEDpkf == true){GkcTZEDpkf = false;}
      if(ifKJdnTjsw == true){ifKJdnTjsw = false;}
      if(nhgRAIqlRh == true){nhgRAIqlRh = false;}
      if(cGPYopzJhB == true){cGPYopzJhB = false;}
      if(pPxdiIHkPc == true){pPxdiIHkPc = false;}
      if(TjXQBYEKSQ == true){TjXQBYEKSQ = false;}
      if(NRXDCbQlUn == true){NRXDCbQlUn = false;}
      if(nJCrFXjDir == true){nJCrFXjDir = false;}
      if(AFVnNshyXP == true){AFVnNshyXP = false;}
      if(loqQmYqtaG == true){loqQmYqtaG = false;}
      if(rVQaoKhfKc == true){rVQaoKhfKc = false;}
      if(oAbaQIujpJ == true){oAbaQIujpJ = false;}
      if(tRNECzSkEg == true){tRNECzSkEg = false;}
      if(gocbzeotzC == true){gocbzeotzC = false;}
      if(KCntakMQAe == true){KCntakMQAe = false;}
      if(dHEQMZHMYo == true){dHEQMZHMYo = false;}
      if(rwadwzXAak == true){rwadwzXAak = false;}
      if(SAjmzqdTcQ == true){SAjmzqdTcQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUDBQNLMJU
{ 
  void IdocEGFmwm()
  { 
      bool lASHLUjjiZ = false;
      bool ZtOLViGeZp = false;
      bool LPxNlAANyl = false;
      bool iZhYTTrnHO = false;
      bool SLcOsWDEEE = false;
      bool LzLnGVCFVL = false;
      bool TVlwpzLoqB = false;
      bool qRXLXAmiTO = false;
      bool wuItajOtRx = false;
      bool QlSwtwZgXt = false;
      bool LNNCMsbzPG = false;
      bool iTkHOXNrUG = false;
      bool jQXskEzbQa = false;
      bool ZFKZCihFgg = false;
      bool IOdLOwBLgV = false;
      bool igMRJtpTRI = false;
      bool tzhofcJLEe = false;
      bool pHKmyVlLen = false;
      bool DnturrssPH = false;
      bool sOnYmIfoek = false;
      string kcQSjdniox;
      string BytIsaTdXK;
      string wBlygpqURk;
      string olNPmgSXhG;
      string EssXsfXtzE;
      string zHMlWjpSlt;
      string mTRDIPkdVL;
      string HuuRFCHOFA;
      string RwUMkhYbrC;
      string pAkmTjboOd;
      string usYmwDLufT;
      string bbNlbpyESa;
      string pIlSUGJIxV;
      string aSzaFYXhPg;
      string VcwXaOmzLd;
      string lXVnmlHFRp;
      string sDyKsIblgD;
      string RQnkFNMNqG;
      string TKwSjCwLnS;
      string QRPZmSdleS;
      if(kcQSjdniox == usYmwDLufT){lASHLUjjiZ = true;}
      else if(usYmwDLufT == kcQSjdniox){LNNCMsbzPG = true;}
      if(BytIsaTdXK == bbNlbpyESa){ZtOLViGeZp = true;}
      else if(bbNlbpyESa == BytIsaTdXK){iTkHOXNrUG = true;}
      if(wBlygpqURk == pIlSUGJIxV){LPxNlAANyl = true;}
      else if(pIlSUGJIxV == wBlygpqURk){jQXskEzbQa = true;}
      if(olNPmgSXhG == aSzaFYXhPg){iZhYTTrnHO = true;}
      else if(aSzaFYXhPg == olNPmgSXhG){ZFKZCihFgg = true;}
      if(EssXsfXtzE == VcwXaOmzLd){SLcOsWDEEE = true;}
      else if(VcwXaOmzLd == EssXsfXtzE){IOdLOwBLgV = true;}
      if(zHMlWjpSlt == lXVnmlHFRp){LzLnGVCFVL = true;}
      else if(lXVnmlHFRp == zHMlWjpSlt){igMRJtpTRI = true;}
      if(mTRDIPkdVL == sDyKsIblgD){TVlwpzLoqB = true;}
      else if(sDyKsIblgD == mTRDIPkdVL){tzhofcJLEe = true;}
      if(HuuRFCHOFA == RQnkFNMNqG){qRXLXAmiTO = true;}
      if(RwUMkhYbrC == TKwSjCwLnS){wuItajOtRx = true;}
      if(pAkmTjboOd == QRPZmSdleS){QlSwtwZgXt = true;}
      while(RQnkFNMNqG == HuuRFCHOFA){pHKmyVlLen = true;}
      while(TKwSjCwLnS == TKwSjCwLnS){DnturrssPH = true;}
      while(QRPZmSdleS == QRPZmSdleS){sOnYmIfoek = true;}
      if(lASHLUjjiZ == true){lASHLUjjiZ = false;}
      if(ZtOLViGeZp == true){ZtOLViGeZp = false;}
      if(LPxNlAANyl == true){LPxNlAANyl = false;}
      if(iZhYTTrnHO == true){iZhYTTrnHO = false;}
      if(SLcOsWDEEE == true){SLcOsWDEEE = false;}
      if(LzLnGVCFVL == true){LzLnGVCFVL = false;}
      if(TVlwpzLoqB == true){TVlwpzLoqB = false;}
      if(qRXLXAmiTO == true){qRXLXAmiTO = false;}
      if(wuItajOtRx == true){wuItajOtRx = false;}
      if(QlSwtwZgXt == true){QlSwtwZgXt = false;}
      if(LNNCMsbzPG == true){LNNCMsbzPG = false;}
      if(iTkHOXNrUG == true){iTkHOXNrUG = false;}
      if(jQXskEzbQa == true){jQXskEzbQa = false;}
      if(ZFKZCihFgg == true){ZFKZCihFgg = false;}
      if(IOdLOwBLgV == true){IOdLOwBLgV = false;}
      if(igMRJtpTRI == true){igMRJtpTRI = false;}
      if(tzhofcJLEe == true){tzhofcJLEe = false;}
      if(pHKmyVlLen == true){pHKmyVlLen = false;}
      if(DnturrssPH == true){DnturrssPH = false;}
      if(sOnYmIfoek == true){sOnYmIfoek = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVPRBKFEMW
{ 
  void QUZzssfbRK()
  { 
      bool kWPhfNoHXf = false;
      bool sWSyronqke = false;
      bool HztcjnRNfB = false;
      bool GmLfcOMnGI = false;
      bool eYnqLtMkza = false;
      bool eMkUnkcmyr = false;
      bool uaaVYFLmUd = false;
      bool czkcAhLDQo = false;
      bool agNEVsCprq = false;
      bool lYpOMDxRRF = false;
      bool iYPVyebIUF = false;
      bool ZYVIQNMWze = false;
      bool DUudqDJWPw = false;
      bool ktlLFCQrFq = false;
      bool RtVlRMCgxz = false;
      bool paRlCOcldt = false;
      bool UErXUfmKCO = false;
      bool wUQINJyILe = false;
      bool BbYQGJbzIq = false;
      bool YeOLVNByRl = false;
      string GdyrlXefro;
      string gUiPjosMwf;
      string RNXVBxzLai;
      string yqLOzPudXR;
      string gdseYAJUqy;
      string HFtpCrFbpn;
      string YSFIppIUQT;
      string sOoeznUrxA;
      string neTbbsxULG;
      string JTnisNYjoi;
      string qoEWEsPOqN;
      string XNepztycfx;
      string rnIJKZaFkk;
      string PjDNIyZwWi;
      string chcxiwnxiz;
      string PuEqpDgtMe;
      string RKdGymKRgB;
      string TCGxTKKKaO;
      string lcVlVTfLWE;
      string RfjrQSEWzu;
      if(GdyrlXefro == qoEWEsPOqN){kWPhfNoHXf = true;}
      else if(qoEWEsPOqN == GdyrlXefro){iYPVyebIUF = true;}
      if(gUiPjosMwf == XNepztycfx){sWSyronqke = true;}
      else if(XNepztycfx == gUiPjosMwf){ZYVIQNMWze = true;}
      if(RNXVBxzLai == rnIJKZaFkk){HztcjnRNfB = true;}
      else if(rnIJKZaFkk == RNXVBxzLai){DUudqDJWPw = true;}
      if(yqLOzPudXR == PjDNIyZwWi){GmLfcOMnGI = true;}
      else if(PjDNIyZwWi == yqLOzPudXR){ktlLFCQrFq = true;}
      if(gdseYAJUqy == chcxiwnxiz){eYnqLtMkza = true;}
      else if(chcxiwnxiz == gdseYAJUqy){RtVlRMCgxz = true;}
      if(HFtpCrFbpn == PuEqpDgtMe){eMkUnkcmyr = true;}
      else if(PuEqpDgtMe == HFtpCrFbpn){paRlCOcldt = true;}
      if(YSFIppIUQT == RKdGymKRgB){uaaVYFLmUd = true;}
      else if(RKdGymKRgB == YSFIppIUQT){UErXUfmKCO = true;}
      if(sOoeznUrxA == TCGxTKKKaO){czkcAhLDQo = true;}
      if(neTbbsxULG == lcVlVTfLWE){agNEVsCprq = true;}
      if(JTnisNYjoi == RfjrQSEWzu){lYpOMDxRRF = true;}
      while(TCGxTKKKaO == sOoeznUrxA){wUQINJyILe = true;}
      while(lcVlVTfLWE == lcVlVTfLWE){BbYQGJbzIq = true;}
      while(RfjrQSEWzu == RfjrQSEWzu){YeOLVNByRl = true;}
      if(kWPhfNoHXf == true){kWPhfNoHXf = false;}
      if(sWSyronqke == true){sWSyronqke = false;}
      if(HztcjnRNfB == true){HztcjnRNfB = false;}
      if(GmLfcOMnGI == true){GmLfcOMnGI = false;}
      if(eYnqLtMkza == true){eYnqLtMkza = false;}
      if(eMkUnkcmyr == true){eMkUnkcmyr = false;}
      if(uaaVYFLmUd == true){uaaVYFLmUd = false;}
      if(czkcAhLDQo == true){czkcAhLDQo = false;}
      if(agNEVsCprq == true){agNEVsCprq = false;}
      if(lYpOMDxRRF == true){lYpOMDxRRF = false;}
      if(iYPVyebIUF == true){iYPVyebIUF = false;}
      if(ZYVIQNMWze == true){ZYVIQNMWze = false;}
      if(DUudqDJWPw == true){DUudqDJWPw = false;}
      if(ktlLFCQrFq == true){ktlLFCQrFq = false;}
      if(RtVlRMCgxz == true){RtVlRMCgxz = false;}
      if(paRlCOcldt == true){paRlCOcldt = false;}
      if(UErXUfmKCO == true){UErXUfmKCO = false;}
      if(wUQINJyILe == true){wUQINJyILe = false;}
      if(BbYQGJbzIq == true){BbYQGJbzIq = false;}
      if(YeOLVNByRl == true){YeOLVNByRl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNDTHRLFFF
{ 
  void VcTfenKOwO()
  { 
      bool xWYcqKsNmQ = false;
      bool mDCULNuAaG = false;
      bool nHYxMBzeFc = false;
      bool OKpaendRLq = false;
      bool dJPsypHVpD = false;
      bool JOFHBpybPp = false;
      bool KOHKCbMaoW = false;
      bool icoibdqezV = false;
      bool sdnBTzFhYn = false;
      bool pCCVfPBFqV = false;
      bool dgfTTfZVeX = false;
      bool zTbsxgZGqC = false;
      bool WeCAfgaTDM = false;
      bool blmdrLxThm = false;
      bool ZiCBoWZIXz = false;
      bool puOnzydfnl = false;
      bool FFSSuNfyBk = false;
      bool iFXDcmbBLI = false;
      bool HRuDWgWyds = false;
      bool hRfugTPiGa = false;
      string MWMMBxhbSD;
      string RpsWawUiyL;
      string XyPXRiqhLE;
      string JnBZiyjCLz;
      string euCrWVZZLz;
      string tsJMEOGouR;
      string GAQNscoTmc;
      string LRXzgbuXAw;
      string IQVLJQenUU;
      string quGsrdenyt;
      string fGlimbUKeb;
      string SiozJpdEEc;
      string yAySkQLeGC;
      string xHYFQCdmXh;
      string uTJsBIFHjC;
      string AZjVueITxW;
      string QpEcdLKiiG;
      string LpfWhdqEQc;
      string LDuDBXWDKk;
      string tKpBQEPfOp;
      if(MWMMBxhbSD == fGlimbUKeb){xWYcqKsNmQ = true;}
      else if(fGlimbUKeb == MWMMBxhbSD){dgfTTfZVeX = true;}
      if(RpsWawUiyL == SiozJpdEEc){mDCULNuAaG = true;}
      else if(SiozJpdEEc == RpsWawUiyL){zTbsxgZGqC = true;}
      if(XyPXRiqhLE == yAySkQLeGC){nHYxMBzeFc = true;}
      else if(yAySkQLeGC == XyPXRiqhLE){WeCAfgaTDM = true;}
      if(JnBZiyjCLz == xHYFQCdmXh){OKpaendRLq = true;}
      else if(xHYFQCdmXh == JnBZiyjCLz){blmdrLxThm = true;}
      if(euCrWVZZLz == uTJsBIFHjC){dJPsypHVpD = true;}
      else if(uTJsBIFHjC == euCrWVZZLz){ZiCBoWZIXz = true;}
      if(tsJMEOGouR == AZjVueITxW){JOFHBpybPp = true;}
      else if(AZjVueITxW == tsJMEOGouR){puOnzydfnl = true;}
      if(GAQNscoTmc == QpEcdLKiiG){KOHKCbMaoW = true;}
      else if(QpEcdLKiiG == GAQNscoTmc){FFSSuNfyBk = true;}
      if(LRXzgbuXAw == LpfWhdqEQc){icoibdqezV = true;}
      if(IQVLJQenUU == LDuDBXWDKk){sdnBTzFhYn = true;}
      if(quGsrdenyt == tKpBQEPfOp){pCCVfPBFqV = true;}
      while(LpfWhdqEQc == LRXzgbuXAw){iFXDcmbBLI = true;}
      while(LDuDBXWDKk == LDuDBXWDKk){HRuDWgWyds = true;}
      while(tKpBQEPfOp == tKpBQEPfOp){hRfugTPiGa = true;}
      if(xWYcqKsNmQ == true){xWYcqKsNmQ = false;}
      if(mDCULNuAaG == true){mDCULNuAaG = false;}
      if(nHYxMBzeFc == true){nHYxMBzeFc = false;}
      if(OKpaendRLq == true){OKpaendRLq = false;}
      if(dJPsypHVpD == true){dJPsypHVpD = false;}
      if(JOFHBpybPp == true){JOFHBpybPp = false;}
      if(KOHKCbMaoW == true){KOHKCbMaoW = false;}
      if(icoibdqezV == true){icoibdqezV = false;}
      if(sdnBTzFhYn == true){sdnBTzFhYn = false;}
      if(pCCVfPBFqV == true){pCCVfPBFqV = false;}
      if(dgfTTfZVeX == true){dgfTTfZVeX = false;}
      if(zTbsxgZGqC == true){zTbsxgZGqC = false;}
      if(WeCAfgaTDM == true){WeCAfgaTDM = false;}
      if(blmdrLxThm == true){blmdrLxThm = false;}
      if(ZiCBoWZIXz == true){ZiCBoWZIXz = false;}
      if(puOnzydfnl == true){puOnzydfnl = false;}
      if(FFSSuNfyBk == true){FFSSuNfyBk = false;}
      if(iFXDcmbBLI == true){iFXDcmbBLI = false;}
      if(HRuDWgWyds == true){HRuDWgWyds = false;}
      if(hRfugTPiGa == true){hRfugTPiGa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KMDULOZASO
{ 
  void dQemQMXTrM()
  { 
      bool TOQEyltxLQ = false;
      bool mmxaOLxqcT = false;
      bool uFQzXFBMlT = false;
      bool nfpNsyynmM = false;
      bool BnIbUBSFtt = false;
      bool YIVGYOyQfs = false;
      bool khLrbGwjhQ = false;
      bool MIEPSHxneW = false;
      bool mwSqufKjne = false;
      bool zgHtbSbPAN = false;
      bool EiWcgPDFmQ = false;
      bool QJlJFoPTxu = false;
      bool uLuDQfAKmz = false;
      bool fhnQREYoKe = false;
      bool bFwXNptynm = false;
      bool DHSESsmTMB = false;
      bool OsSnkiUVqA = false;
      bool PaJRTpPWoZ = false;
      bool kCVzuXOjxY = false;
      bool QEbJPilIme = false;
      string gFnZwCifgD;
      string QgxHFWfIHi;
      string CglPtnYMdI;
      string qnGYLHEkcP;
      string sWoOyxjMtf;
      string KebkGASYeI;
      string dVCYMcZYux;
      string RterpfrWRx;
      string DMSxyLMVRK;
      string ofGUlWTQCU;
      string WLQxNPziua;
      string IuGhERDEZB;
      string QEHkHlnJGS;
      string LaUxZruVjh;
      string LcZpCtYXQU;
      string TPpBERDfob;
      string bpcbPgZJHM;
      string VhUroneQhN;
      string MPslzwkTrH;
      string nPfIGVzyZU;
      if(gFnZwCifgD == WLQxNPziua){TOQEyltxLQ = true;}
      else if(WLQxNPziua == gFnZwCifgD){EiWcgPDFmQ = true;}
      if(QgxHFWfIHi == IuGhERDEZB){mmxaOLxqcT = true;}
      else if(IuGhERDEZB == QgxHFWfIHi){QJlJFoPTxu = true;}
      if(CglPtnYMdI == QEHkHlnJGS){uFQzXFBMlT = true;}
      else if(QEHkHlnJGS == CglPtnYMdI){uLuDQfAKmz = true;}
      if(qnGYLHEkcP == LaUxZruVjh){nfpNsyynmM = true;}
      else if(LaUxZruVjh == qnGYLHEkcP){fhnQREYoKe = true;}
      if(sWoOyxjMtf == LcZpCtYXQU){BnIbUBSFtt = true;}
      else if(LcZpCtYXQU == sWoOyxjMtf){bFwXNptynm = true;}
      if(KebkGASYeI == TPpBERDfob){YIVGYOyQfs = true;}
      else if(TPpBERDfob == KebkGASYeI){DHSESsmTMB = true;}
      if(dVCYMcZYux == bpcbPgZJHM){khLrbGwjhQ = true;}
      else if(bpcbPgZJHM == dVCYMcZYux){OsSnkiUVqA = true;}
      if(RterpfrWRx == VhUroneQhN){MIEPSHxneW = true;}
      if(DMSxyLMVRK == MPslzwkTrH){mwSqufKjne = true;}
      if(ofGUlWTQCU == nPfIGVzyZU){zgHtbSbPAN = true;}
      while(VhUroneQhN == RterpfrWRx){PaJRTpPWoZ = true;}
      while(MPslzwkTrH == MPslzwkTrH){kCVzuXOjxY = true;}
      while(nPfIGVzyZU == nPfIGVzyZU){QEbJPilIme = true;}
      if(TOQEyltxLQ == true){TOQEyltxLQ = false;}
      if(mmxaOLxqcT == true){mmxaOLxqcT = false;}
      if(uFQzXFBMlT == true){uFQzXFBMlT = false;}
      if(nfpNsyynmM == true){nfpNsyynmM = false;}
      if(BnIbUBSFtt == true){BnIbUBSFtt = false;}
      if(YIVGYOyQfs == true){YIVGYOyQfs = false;}
      if(khLrbGwjhQ == true){khLrbGwjhQ = false;}
      if(MIEPSHxneW == true){MIEPSHxneW = false;}
      if(mwSqufKjne == true){mwSqufKjne = false;}
      if(zgHtbSbPAN == true){zgHtbSbPAN = false;}
      if(EiWcgPDFmQ == true){EiWcgPDFmQ = false;}
      if(QJlJFoPTxu == true){QJlJFoPTxu = false;}
      if(uLuDQfAKmz == true){uLuDQfAKmz = false;}
      if(fhnQREYoKe == true){fhnQREYoKe = false;}
      if(bFwXNptynm == true){bFwXNptynm = false;}
      if(DHSESsmTMB == true){DHSESsmTMB = false;}
      if(OsSnkiUVqA == true){OsSnkiUVqA = false;}
      if(PaJRTpPWoZ == true){PaJRTpPWoZ = false;}
      if(kCVzuXOjxY == true){kCVzuXOjxY = false;}
      if(QEbJPilIme == true){QEbJPilIme = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEPQEUJQOO
{ 
  void VCptwSPFjR()
  { 
      bool FjmYwISMWx = false;
      bool lZAbplrASy = false;
      bool AsROTtbzwX = false;
      bool KsCjxbhlSm = false;
      bool AKXiWeVKqK = false;
      bool EotzcLRXFB = false;
      bool gTPylrWQdN = false;
      bool EFgfyoVhqn = false;
      bool YQIlSVzDGk = false;
      bool JKgRGfuYxe = false;
      bool HEgcGzHOAm = false;
      bool ojfQbQLdfQ = false;
      bool sTKsEtXPYS = false;
      bool sxkMfUjeeS = false;
      bool NjCSwZdPop = false;
      bool URsfkmtmYM = false;
      bool aqohtryTkH = false;
      bool ffyMDIRqxd = false;
      bool PIaiybEFar = false;
      bool awGSrVuUYD = false;
      string LLxJyNsbmJ;
      string cMgzzbJeRq;
      string pbolEaBZhx;
      string dcQQjmWqWa;
      string VJtrDYGokC;
      string FSgEQiVKFW;
      string MTtpfAwQOL;
      string FRHpVghxhe;
      string ULoerKuLAB;
      string RLlzOCOELD;
      string cpaYwmKpij;
      string AYcaCBePyU;
      string FjPMttfHbT;
      string RckeCejQiE;
      string zEcPArhKwM;
      string WzFqxsZNdC;
      string HCOPRXmyXX;
      string QOfsUAGAMC;
      string LUKOwSWtgJ;
      string EWlgxxoNyc;
      if(LLxJyNsbmJ == cpaYwmKpij){FjmYwISMWx = true;}
      else if(cpaYwmKpij == LLxJyNsbmJ){HEgcGzHOAm = true;}
      if(cMgzzbJeRq == AYcaCBePyU){lZAbplrASy = true;}
      else if(AYcaCBePyU == cMgzzbJeRq){ojfQbQLdfQ = true;}
      if(pbolEaBZhx == FjPMttfHbT){AsROTtbzwX = true;}
      else if(FjPMttfHbT == pbolEaBZhx){sTKsEtXPYS = true;}
      if(dcQQjmWqWa == RckeCejQiE){KsCjxbhlSm = true;}
      else if(RckeCejQiE == dcQQjmWqWa){sxkMfUjeeS = true;}
      if(VJtrDYGokC == zEcPArhKwM){AKXiWeVKqK = true;}
      else if(zEcPArhKwM == VJtrDYGokC){NjCSwZdPop = true;}
      if(FSgEQiVKFW == WzFqxsZNdC){EotzcLRXFB = true;}
      else if(WzFqxsZNdC == FSgEQiVKFW){URsfkmtmYM = true;}
      if(MTtpfAwQOL == HCOPRXmyXX){gTPylrWQdN = true;}
      else if(HCOPRXmyXX == MTtpfAwQOL){aqohtryTkH = true;}
      if(FRHpVghxhe == QOfsUAGAMC){EFgfyoVhqn = true;}
      if(ULoerKuLAB == LUKOwSWtgJ){YQIlSVzDGk = true;}
      if(RLlzOCOELD == EWlgxxoNyc){JKgRGfuYxe = true;}
      while(QOfsUAGAMC == FRHpVghxhe){ffyMDIRqxd = true;}
      while(LUKOwSWtgJ == LUKOwSWtgJ){PIaiybEFar = true;}
      while(EWlgxxoNyc == EWlgxxoNyc){awGSrVuUYD = true;}
      if(FjmYwISMWx == true){FjmYwISMWx = false;}
      if(lZAbplrASy == true){lZAbplrASy = false;}
      if(AsROTtbzwX == true){AsROTtbzwX = false;}
      if(KsCjxbhlSm == true){KsCjxbhlSm = false;}
      if(AKXiWeVKqK == true){AKXiWeVKqK = false;}
      if(EotzcLRXFB == true){EotzcLRXFB = false;}
      if(gTPylrWQdN == true){gTPylrWQdN = false;}
      if(EFgfyoVhqn == true){EFgfyoVhqn = false;}
      if(YQIlSVzDGk == true){YQIlSVzDGk = false;}
      if(JKgRGfuYxe == true){JKgRGfuYxe = false;}
      if(HEgcGzHOAm == true){HEgcGzHOAm = false;}
      if(ojfQbQLdfQ == true){ojfQbQLdfQ = false;}
      if(sTKsEtXPYS == true){sTKsEtXPYS = false;}
      if(sxkMfUjeeS == true){sxkMfUjeeS = false;}
      if(NjCSwZdPop == true){NjCSwZdPop = false;}
      if(URsfkmtmYM == true){URsfkmtmYM = false;}
      if(aqohtryTkH == true){aqohtryTkH = false;}
      if(ffyMDIRqxd == true){ffyMDIRqxd = false;}
      if(PIaiybEFar == true){PIaiybEFar = false;}
      if(awGSrVuUYD == true){awGSrVuUYD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBIBGICZJU
{ 
  void dPSCKKTuhb()
  { 
      bool YapjGFQZUg = false;
      bool YieasoiKue = false;
      bool CYpWuxRkrr = false;
      bool LOeCUwJHnX = false;
      bool UUmgUdtnps = false;
      bool CCQixAkSnJ = false;
      bool mfhbUKEbFx = false;
      bool eaWXKhkICQ = false;
      bool DdtyoJxuFU = false;
      bool KpTeknmKLK = false;
      bool ZRhrNbesYO = false;
      bool ObQWFJlimL = false;
      bool MJVkloHrlV = false;
      bool uaxrqkuBjM = false;
      bool dDWpFiZwYa = false;
      bool BDXAxQuxGY = false;
      bool UmGCTndXfU = false;
      bool OkyZgIlfeD = false;
      bool OKSLUqCxtZ = false;
      bool oxuKrqwTWR = false;
      string TcnecjibWY;
      string qYjdLqQNFx;
      string cawBJlQMmy;
      string LEkpkWnnjZ;
      string bwaCjBtaIT;
      string anIKVsfmUq;
      string TVnYNmmsro;
      string CbdeVfztQI;
      string qoESXWwZUq;
      string pBTsGFICnx;
      string NBhTRyKcoo;
      string tlWLzdRVAp;
      string qMYAyBIkXQ;
      string XwFStpGjAY;
      string LSkexEdHsc;
      string mlByFAbhUQ;
      string pZFYQxfDQJ;
      string WhUbdYbsCt;
      string WAqtcltHNs;
      string NYPjilMMOA;
      if(TcnecjibWY == NBhTRyKcoo){YapjGFQZUg = true;}
      else if(NBhTRyKcoo == TcnecjibWY){ZRhrNbesYO = true;}
      if(qYjdLqQNFx == tlWLzdRVAp){YieasoiKue = true;}
      else if(tlWLzdRVAp == qYjdLqQNFx){ObQWFJlimL = true;}
      if(cawBJlQMmy == qMYAyBIkXQ){CYpWuxRkrr = true;}
      else if(qMYAyBIkXQ == cawBJlQMmy){MJVkloHrlV = true;}
      if(LEkpkWnnjZ == XwFStpGjAY){LOeCUwJHnX = true;}
      else if(XwFStpGjAY == LEkpkWnnjZ){uaxrqkuBjM = true;}
      if(bwaCjBtaIT == LSkexEdHsc){UUmgUdtnps = true;}
      else if(LSkexEdHsc == bwaCjBtaIT){dDWpFiZwYa = true;}
      if(anIKVsfmUq == mlByFAbhUQ){CCQixAkSnJ = true;}
      else if(mlByFAbhUQ == anIKVsfmUq){BDXAxQuxGY = true;}
      if(TVnYNmmsro == pZFYQxfDQJ){mfhbUKEbFx = true;}
      else if(pZFYQxfDQJ == TVnYNmmsro){UmGCTndXfU = true;}
      if(CbdeVfztQI == WhUbdYbsCt){eaWXKhkICQ = true;}
      if(qoESXWwZUq == WAqtcltHNs){DdtyoJxuFU = true;}
      if(pBTsGFICnx == NYPjilMMOA){KpTeknmKLK = true;}
      while(WhUbdYbsCt == CbdeVfztQI){OkyZgIlfeD = true;}
      while(WAqtcltHNs == WAqtcltHNs){OKSLUqCxtZ = true;}
      while(NYPjilMMOA == NYPjilMMOA){oxuKrqwTWR = true;}
      if(YapjGFQZUg == true){YapjGFQZUg = false;}
      if(YieasoiKue == true){YieasoiKue = false;}
      if(CYpWuxRkrr == true){CYpWuxRkrr = false;}
      if(LOeCUwJHnX == true){LOeCUwJHnX = false;}
      if(UUmgUdtnps == true){UUmgUdtnps = false;}
      if(CCQixAkSnJ == true){CCQixAkSnJ = false;}
      if(mfhbUKEbFx == true){mfhbUKEbFx = false;}
      if(eaWXKhkICQ == true){eaWXKhkICQ = false;}
      if(DdtyoJxuFU == true){DdtyoJxuFU = false;}
      if(KpTeknmKLK == true){KpTeknmKLK = false;}
      if(ZRhrNbesYO == true){ZRhrNbesYO = false;}
      if(ObQWFJlimL == true){ObQWFJlimL = false;}
      if(MJVkloHrlV == true){MJVkloHrlV = false;}
      if(uaxrqkuBjM == true){uaxrqkuBjM = false;}
      if(dDWpFiZwYa == true){dDWpFiZwYa = false;}
      if(BDXAxQuxGY == true){BDXAxQuxGY = false;}
      if(UmGCTndXfU == true){UmGCTndXfU = false;}
      if(OkyZgIlfeD == true){OkyZgIlfeD = false;}
      if(OKSLUqCxtZ == true){OKSLUqCxtZ = false;}
      if(oxuKrqwTWR == true){oxuKrqwTWR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXPHHKUMAM
{ 
  void OrZGEpBnZd()
  { 
      bool OSOaRcxVZE = false;
      bool yxxPTjKyoJ = false;
      bool VtScwphKVu = false;
      bool GNTjAEdMrx = false;
      bool DkPiXohQEd = false;
      bool KqgakUzleb = false;
      bool tlAdxjcMOP = false;
      bool GxGrGkdiFG = false;
      bool HRFrkPgrzf = false;
      bool EqhQDQkkkm = false;
      bool LUBoWMkoUA = false;
      bool pQgXTbfIrg = false;
      bool DjNiKOPpno = false;
      bool zsxRtmPQUY = false;
      bool eqXzpmKJwa = false;
      bool jcrEjbHSdI = false;
      bool wuAeAwSOdg = false;
      bool LPmTCLMOsX = false;
      bool EGsMFWAshS = false;
      bool fxmMbjprys = false;
      string NNNSwuuxkt;
      string sZfUPNCZsY;
      string nbnhFhOUzj;
      string rriqOnzduN;
      string qbhdxwpZSz;
      string IamODkZfMO;
      string gaxBCApnGb;
      string NXeehLtJkJ;
      string qoBAaQFTmc;
      string OSQggPdfbw;
      string FCSqkjwHgr;
      string qQtDWrYxak;
      string uWAcMuGxyR;
      string gNgoEnVKOq;
      string TylukyXNJn;
      string qfFqBhBodp;
      string cyIPKdiFyh;
      string WOiiQwjErO;
      string WsnKZAHomV;
      string lffXNUoWkH;
      if(NNNSwuuxkt == FCSqkjwHgr){OSOaRcxVZE = true;}
      else if(FCSqkjwHgr == NNNSwuuxkt){LUBoWMkoUA = true;}
      if(sZfUPNCZsY == qQtDWrYxak){yxxPTjKyoJ = true;}
      else if(qQtDWrYxak == sZfUPNCZsY){pQgXTbfIrg = true;}
      if(nbnhFhOUzj == uWAcMuGxyR){VtScwphKVu = true;}
      else if(uWAcMuGxyR == nbnhFhOUzj){DjNiKOPpno = true;}
      if(rriqOnzduN == gNgoEnVKOq){GNTjAEdMrx = true;}
      else if(gNgoEnVKOq == rriqOnzduN){zsxRtmPQUY = true;}
      if(qbhdxwpZSz == TylukyXNJn){DkPiXohQEd = true;}
      else if(TylukyXNJn == qbhdxwpZSz){eqXzpmKJwa = true;}
      if(IamODkZfMO == qfFqBhBodp){KqgakUzleb = true;}
      else if(qfFqBhBodp == IamODkZfMO){jcrEjbHSdI = true;}
      if(gaxBCApnGb == cyIPKdiFyh){tlAdxjcMOP = true;}
      else if(cyIPKdiFyh == gaxBCApnGb){wuAeAwSOdg = true;}
      if(NXeehLtJkJ == WOiiQwjErO){GxGrGkdiFG = true;}
      if(qoBAaQFTmc == WsnKZAHomV){HRFrkPgrzf = true;}
      if(OSQggPdfbw == lffXNUoWkH){EqhQDQkkkm = true;}
      while(WOiiQwjErO == NXeehLtJkJ){LPmTCLMOsX = true;}
      while(WsnKZAHomV == WsnKZAHomV){EGsMFWAshS = true;}
      while(lffXNUoWkH == lffXNUoWkH){fxmMbjprys = true;}
      if(OSOaRcxVZE == true){OSOaRcxVZE = false;}
      if(yxxPTjKyoJ == true){yxxPTjKyoJ = false;}
      if(VtScwphKVu == true){VtScwphKVu = false;}
      if(GNTjAEdMrx == true){GNTjAEdMrx = false;}
      if(DkPiXohQEd == true){DkPiXohQEd = false;}
      if(KqgakUzleb == true){KqgakUzleb = false;}
      if(tlAdxjcMOP == true){tlAdxjcMOP = false;}
      if(GxGrGkdiFG == true){GxGrGkdiFG = false;}
      if(HRFrkPgrzf == true){HRFrkPgrzf = false;}
      if(EqhQDQkkkm == true){EqhQDQkkkm = false;}
      if(LUBoWMkoUA == true){LUBoWMkoUA = false;}
      if(pQgXTbfIrg == true){pQgXTbfIrg = false;}
      if(DjNiKOPpno == true){DjNiKOPpno = false;}
      if(zsxRtmPQUY == true){zsxRtmPQUY = false;}
      if(eqXzpmKJwa == true){eqXzpmKJwa = false;}
      if(jcrEjbHSdI == true){jcrEjbHSdI = false;}
      if(wuAeAwSOdg == true){wuAeAwSOdg = false;}
      if(LPmTCLMOsX == true){LPmTCLMOsX = false;}
      if(EGsMFWAshS == true){EGsMFWAshS = false;}
      if(fxmMbjprys == true){fxmMbjprys = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDZQXNECVP
{ 
  void AwqieoqHbe()
  { 
      bool RcHzruwecp = false;
      bool mBGUPioZQH = false;
      bool rpbSUzdKlI = false;
      bool sJntZrwazy = false;
      bool xEnkOcAIpD = false;
      bool coKqXbBndr = false;
      bool RlsUwdMLtW = false;
      bool lNZRJnBpEq = false;
      bool zVTieDyxWx = false;
      bool pHwHgKKTnk = false;
      bool PnNSQPPsgj = false;
      bool aLjlswRKos = false;
      bool ePowgdRSkz = false;
      bool cgBTbLHARP = false;
      bool nFPmWdWJNj = false;
      bool rAduFzzQll = false;
      bool xwHhGsKQKh = false;
      bool nRrZEZzCYC = false;
      bool HIEAGbDFNb = false;
      bool MpOfRqxhfd = false;
      string cXuEbsdNsY;
      string LQiWZYnVWH;
      string dYQwmOWOdH;
      string xZxoLHKmeA;
      string MDklcPUewA;
      string RdgChDGzRN;
      string WOjkakSsKR;
      string NApVtameTW;
      string trScoTsuHH;
      string ALVRdxTAKr;
      string waTdlQmKHH;
      string PbetSeuGwH;
      string rXlCQCeYrw;
      string GmUbZTXopX;
      string ghmzrYgayz;
      string CMDDzYnQMj;
      string lOSLAbGDTz;
      string GGPXZJkmKr;
      string UDZrtsjQbB;
      string eGcFlRPbyP;
      if(cXuEbsdNsY == waTdlQmKHH){RcHzruwecp = true;}
      else if(waTdlQmKHH == cXuEbsdNsY){PnNSQPPsgj = true;}
      if(LQiWZYnVWH == PbetSeuGwH){mBGUPioZQH = true;}
      else if(PbetSeuGwH == LQiWZYnVWH){aLjlswRKos = true;}
      if(dYQwmOWOdH == rXlCQCeYrw){rpbSUzdKlI = true;}
      else if(rXlCQCeYrw == dYQwmOWOdH){ePowgdRSkz = true;}
      if(xZxoLHKmeA == GmUbZTXopX){sJntZrwazy = true;}
      else if(GmUbZTXopX == xZxoLHKmeA){cgBTbLHARP = true;}
      if(MDklcPUewA == ghmzrYgayz){xEnkOcAIpD = true;}
      else if(ghmzrYgayz == MDklcPUewA){nFPmWdWJNj = true;}
      if(RdgChDGzRN == CMDDzYnQMj){coKqXbBndr = true;}
      else if(CMDDzYnQMj == RdgChDGzRN){rAduFzzQll = true;}
      if(WOjkakSsKR == lOSLAbGDTz){RlsUwdMLtW = true;}
      else if(lOSLAbGDTz == WOjkakSsKR){xwHhGsKQKh = true;}
      if(NApVtameTW == GGPXZJkmKr){lNZRJnBpEq = true;}
      if(trScoTsuHH == UDZrtsjQbB){zVTieDyxWx = true;}
      if(ALVRdxTAKr == eGcFlRPbyP){pHwHgKKTnk = true;}
      while(GGPXZJkmKr == NApVtameTW){nRrZEZzCYC = true;}
      while(UDZrtsjQbB == UDZrtsjQbB){HIEAGbDFNb = true;}
      while(eGcFlRPbyP == eGcFlRPbyP){MpOfRqxhfd = true;}
      if(RcHzruwecp == true){RcHzruwecp = false;}
      if(mBGUPioZQH == true){mBGUPioZQH = false;}
      if(rpbSUzdKlI == true){rpbSUzdKlI = false;}
      if(sJntZrwazy == true){sJntZrwazy = false;}
      if(xEnkOcAIpD == true){xEnkOcAIpD = false;}
      if(coKqXbBndr == true){coKqXbBndr = false;}
      if(RlsUwdMLtW == true){RlsUwdMLtW = false;}
      if(lNZRJnBpEq == true){lNZRJnBpEq = false;}
      if(zVTieDyxWx == true){zVTieDyxWx = false;}
      if(pHwHgKKTnk == true){pHwHgKKTnk = false;}
      if(PnNSQPPsgj == true){PnNSQPPsgj = false;}
      if(aLjlswRKos == true){aLjlswRKos = false;}
      if(ePowgdRSkz == true){ePowgdRSkz = false;}
      if(cgBTbLHARP == true){cgBTbLHARP = false;}
      if(nFPmWdWJNj == true){nFPmWdWJNj = false;}
      if(rAduFzzQll == true){rAduFzzQll = false;}
      if(xwHhGsKQKh == true){xwHhGsKQKh = false;}
      if(nRrZEZzCYC == true){nRrZEZzCYC = false;}
      if(HIEAGbDFNb == true){HIEAGbDFNb = false;}
      if(MpOfRqxhfd == true){MpOfRqxhfd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGEQWSECED
{ 
  void BuZuOLeMxt()
  { 
      bool ckSNFSDUkk = false;
      bool MuQtglLaqu = false;
      bool zpSzHMMkyG = false;
      bool PrsaWIUCoi = false;
      bool oeMMsmouHQ = false;
      bool lTppRlSSGr = false;
      bool GSWeVUCpXX = false;
      bool QJlHGTcFGU = false;
      bool XRcgUwCCIk = false;
      bool oCwwcVIhqY = false;
      bool jyXiAbgijy = false;
      bool IMLlUoopKY = false;
      bool RAglhNNoej = false;
      bool LuOhjYtsfr = false;
      bool OTRKbcpKbn = false;
      bool fSXSGjRkAl = false;
      bool OrDAmNydBu = false;
      bool uuJSJyhVKF = false;
      bool XDMqDsWwaA = false;
      bool GIstcWPRXO = false;
      string IOxsoVAAet;
      string ziNepDoMBV;
      string gPdUMCCSXl;
      string rTpcgeqEoa;
      string ptrVDfPRWj;
      string WUOxuskcfl;
      string ThcrCfskyL;
      string LkXaflWHRg;
      string mjunOXErgn;
      string tOXCHHRzTW;
      string mdTLXlxnRI;
      string WcLzzilode;
      string aADJQxMUSX;
      string UWntsIPjPc;
      string ZQaYRRCYDX;
      string VcVowmZJta;
      string ZbVsmzoQGp;
      string SCYBEKZerz;
      string tmQtCrAyyG;
      string hGonCxtgkR;
      if(IOxsoVAAet == mdTLXlxnRI){ckSNFSDUkk = true;}
      else if(mdTLXlxnRI == IOxsoVAAet){jyXiAbgijy = true;}
      if(ziNepDoMBV == WcLzzilode){MuQtglLaqu = true;}
      else if(WcLzzilode == ziNepDoMBV){IMLlUoopKY = true;}
      if(gPdUMCCSXl == aADJQxMUSX){zpSzHMMkyG = true;}
      else if(aADJQxMUSX == gPdUMCCSXl){RAglhNNoej = true;}
      if(rTpcgeqEoa == UWntsIPjPc){PrsaWIUCoi = true;}
      else if(UWntsIPjPc == rTpcgeqEoa){LuOhjYtsfr = true;}
      if(ptrVDfPRWj == ZQaYRRCYDX){oeMMsmouHQ = true;}
      else if(ZQaYRRCYDX == ptrVDfPRWj){OTRKbcpKbn = true;}
      if(WUOxuskcfl == VcVowmZJta){lTppRlSSGr = true;}
      else if(VcVowmZJta == WUOxuskcfl){fSXSGjRkAl = true;}
      if(ThcrCfskyL == ZbVsmzoQGp){GSWeVUCpXX = true;}
      else if(ZbVsmzoQGp == ThcrCfskyL){OrDAmNydBu = true;}
      if(LkXaflWHRg == SCYBEKZerz){QJlHGTcFGU = true;}
      if(mjunOXErgn == tmQtCrAyyG){XRcgUwCCIk = true;}
      if(tOXCHHRzTW == hGonCxtgkR){oCwwcVIhqY = true;}
      while(SCYBEKZerz == LkXaflWHRg){uuJSJyhVKF = true;}
      while(tmQtCrAyyG == tmQtCrAyyG){XDMqDsWwaA = true;}
      while(hGonCxtgkR == hGonCxtgkR){GIstcWPRXO = true;}
      if(ckSNFSDUkk == true){ckSNFSDUkk = false;}
      if(MuQtglLaqu == true){MuQtglLaqu = false;}
      if(zpSzHMMkyG == true){zpSzHMMkyG = false;}
      if(PrsaWIUCoi == true){PrsaWIUCoi = false;}
      if(oeMMsmouHQ == true){oeMMsmouHQ = false;}
      if(lTppRlSSGr == true){lTppRlSSGr = false;}
      if(GSWeVUCpXX == true){GSWeVUCpXX = false;}
      if(QJlHGTcFGU == true){QJlHGTcFGU = false;}
      if(XRcgUwCCIk == true){XRcgUwCCIk = false;}
      if(oCwwcVIhqY == true){oCwwcVIhqY = false;}
      if(jyXiAbgijy == true){jyXiAbgijy = false;}
      if(IMLlUoopKY == true){IMLlUoopKY = false;}
      if(RAglhNNoej == true){RAglhNNoej = false;}
      if(LuOhjYtsfr == true){LuOhjYtsfr = false;}
      if(OTRKbcpKbn == true){OTRKbcpKbn = false;}
      if(fSXSGjRkAl == true){fSXSGjRkAl = false;}
      if(OrDAmNydBu == true){OrDAmNydBu = false;}
      if(uuJSJyhVKF == true){uuJSJyhVKF = false;}
      if(XDMqDsWwaA == true){XDMqDsWwaA = false;}
      if(GIstcWPRXO == true){GIstcWPRXO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APWNYVANZV
{ 
  void iKzEzrUTuK()
  { 
      bool nGLVaXlfSo = false;
      bool mpUHuZjjeb = false;
      bool KtqJCKJteh = false;
      bool CYROEkqSPf = false;
      bool zOHNMMGfGh = false;
      bool XtBISsPBTQ = false;
      bool NrBjmNYFDJ = false;
      bool hQUzbwmdxp = false;
      bool DcnwKHXIwL = false;
      bool VozzRHMXay = false;
      bool nBcwzHZBgV = false;
      bool GkEdNkEEZe = false;
      bool oPIqnrRUgU = false;
      bool jOCyBCAqxD = false;
      bool hVbaFjkUkg = false;
      bool DIxwJXrkIG = false;
      bool oETMlqhFbL = false;
      bool jMHWwSnhlD = false;
      bool HxiAQaRGod = false;
      bool JOipNcBOoN = false;
      string mJcawBnWDx;
      string sGaJwmgGkS;
      string JMoYQJxJQo;
      string DPMwdgYiOr;
      string lXFZnIWTRu;
      string AgaoSaTDKm;
      string DdFNscsdeO;
      string OxqsglGPjH;
      string mcqVoWoXdD;
      string NUXanHRrfK;
      string OroCgDogHg;
      string TETCzaljYW;
      string nVzbBsYQFY;
      string TNiYrunook;
      string gHPxiIBVaN;
      string UhTIWsrMAm;
      string dYbiMFUtJE;
      string lxumpgGCrr;
      string rDoqDktZCz;
      string CanBHHegjc;
      if(mJcawBnWDx == OroCgDogHg){nGLVaXlfSo = true;}
      else if(OroCgDogHg == mJcawBnWDx){nBcwzHZBgV = true;}
      if(sGaJwmgGkS == TETCzaljYW){mpUHuZjjeb = true;}
      else if(TETCzaljYW == sGaJwmgGkS){GkEdNkEEZe = true;}
      if(JMoYQJxJQo == nVzbBsYQFY){KtqJCKJteh = true;}
      else if(nVzbBsYQFY == JMoYQJxJQo){oPIqnrRUgU = true;}
      if(DPMwdgYiOr == TNiYrunook){CYROEkqSPf = true;}
      else if(TNiYrunook == DPMwdgYiOr){jOCyBCAqxD = true;}
      if(lXFZnIWTRu == gHPxiIBVaN){zOHNMMGfGh = true;}
      else if(gHPxiIBVaN == lXFZnIWTRu){hVbaFjkUkg = true;}
      if(AgaoSaTDKm == UhTIWsrMAm){XtBISsPBTQ = true;}
      else if(UhTIWsrMAm == AgaoSaTDKm){DIxwJXrkIG = true;}
      if(DdFNscsdeO == dYbiMFUtJE){NrBjmNYFDJ = true;}
      else if(dYbiMFUtJE == DdFNscsdeO){oETMlqhFbL = true;}
      if(OxqsglGPjH == lxumpgGCrr){hQUzbwmdxp = true;}
      if(mcqVoWoXdD == rDoqDktZCz){DcnwKHXIwL = true;}
      if(NUXanHRrfK == CanBHHegjc){VozzRHMXay = true;}
      while(lxumpgGCrr == OxqsglGPjH){jMHWwSnhlD = true;}
      while(rDoqDktZCz == rDoqDktZCz){HxiAQaRGod = true;}
      while(CanBHHegjc == CanBHHegjc){JOipNcBOoN = true;}
      if(nGLVaXlfSo == true){nGLVaXlfSo = false;}
      if(mpUHuZjjeb == true){mpUHuZjjeb = false;}
      if(KtqJCKJteh == true){KtqJCKJteh = false;}
      if(CYROEkqSPf == true){CYROEkqSPf = false;}
      if(zOHNMMGfGh == true){zOHNMMGfGh = false;}
      if(XtBISsPBTQ == true){XtBISsPBTQ = false;}
      if(NrBjmNYFDJ == true){NrBjmNYFDJ = false;}
      if(hQUzbwmdxp == true){hQUzbwmdxp = false;}
      if(DcnwKHXIwL == true){DcnwKHXIwL = false;}
      if(VozzRHMXay == true){VozzRHMXay = false;}
      if(nBcwzHZBgV == true){nBcwzHZBgV = false;}
      if(GkEdNkEEZe == true){GkEdNkEEZe = false;}
      if(oPIqnrRUgU == true){oPIqnrRUgU = false;}
      if(jOCyBCAqxD == true){jOCyBCAqxD = false;}
      if(hVbaFjkUkg == true){hVbaFjkUkg = false;}
      if(DIxwJXrkIG == true){DIxwJXrkIG = false;}
      if(oETMlqhFbL == true){oETMlqhFbL = false;}
      if(jMHWwSnhlD == true){jMHWwSnhlD = false;}
      if(HxiAQaRGod == true){HxiAQaRGod = false;}
      if(JOipNcBOoN == true){JOipNcBOoN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKTEFYUTOX
{ 
  void DWGNfBnXWa()
  { 
      bool feDhFRoQYI = false;
      bool qXsZoApkAL = false;
      bool HOPyBteQVH = false;
      bool tKNcQCmASB = false;
      bool gsfdgutUlM = false;
      bool ocFhGROFgK = false;
      bool lYtQNgJPJl = false;
      bool NoRzeOhlQF = false;
      bool AKdJSREeWz = false;
      bool nhTHOHyPPA = false;
      bool keLAyAKFDr = false;
      bool jcnaKatkyw = false;
      bool besJyfVJkW = false;
      bool PRWQUVzdKR = false;
      bool GybdPKssxm = false;
      bool NNRSXGkBBS = false;
      bool dAUfcRGXFo = false;
      bool bPZfpdCOtn = false;
      bool lcMxJBzDrO = false;
      bool jycrnFcuBx = false;
      string TtoLFKSNSj;
      string CbeQaEGEoL;
      string nqkebZWmgQ;
      string cYegjtyLzi;
      string PHqNbwMoBs;
      string COdZSbIJie;
      string negCHcwyfg;
      string FtEGufzXDf;
      string NglnNOuFOI;
      string kocTtkaoFz;
      string zOITnIJWel;
      string bkGCRGrrns;
      string gqiXwQQjMK;
      string EKREfyYSzE;
      string EYZbfzhZBm;
      string rhAMRHekWX;
      string qYKThRTCWT;
      string hZsjnIQHqw;
      string hpiYSVJFlX;
      string SmubNfOGtO;
      if(TtoLFKSNSj == zOITnIJWel){feDhFRoQYI = true;}
      else if(zOITnIJWel == TtoLFKSNSj){keLAyAKFDr = true;}
      if(CbeQaEGEoL == bkGCRGrrns){qXsZoApkAL = true;}
      else if(bkGCRGrrns == CbeQaEGEoL){jcnaKatkyw = true;}
      if(nqkebZWmgQ == gqiXwQQjMK){HOPyBteQVH = true;}
      else if(gqiXwQQjMK == nqkebZWmgQ){besJyfVJkW = true;}
      if(cYegjtyLzi == EKREfyYSzE){tKNcQCmASB = true;}
      else if(EKREfyYSzE == cYegjtyLzi){PRWQUVzdKR = true;}
      if(PHqNbwMoBs == EYZbfzhZBm){gsfdgutUlM = true;}
      else if(EYZbfzhZBm == PHqNbwMoBs){GybdPKssxm = true;}
      if(COdZSbIJie == rhAMRHekWX){ocFhGROFgK = true;}
      else if(rhAMRHekWX == COdZSbIJie){NNRSXGkBBS = true;}
      if(negCHcwyfg == qYKThRTCWT){lYtQNgJPJl = true;}
      else if(qYKThRTCWT == negCHcwyfg){dAUfcRGXFo = true;}
      if(FtEGufzXDf == hZsjnIQHqw){NoRzeOhlQF = true;}
      if(NglnNOuFOI == hpiYSVJFlX){AKdJSREeWz = true;}
      if(kocTtkaoFz == SmubNfOGtO){nhTHOHyPPA = true;}
      while(hZsjnIQHqw == FtEGufzXDf){bPZfpdCOtn = true;}
      while(hpiYSVJFlX == hpiYSVJFlX){lcMxJBzDrO = true;}
      while(SmubNfOGtO == SmubNfOGtO){jycrnFcuBx = true;}
      if(feDhFRoQYI == true){feDhFRoQYI = false;}
      if(qXsZoApkAL == true){qXsZoApkAL = false;}
      if(HOPyBteQVH == true){HOPyBteQVH = false;}
      if(tKNcQCmASB == true){tKNcQCmASB = false;}
      if(gsfdgutUlM == true){gsfdgutUlM = false;}
      if(ocFhGROFgK == true){ocFhGROFgK = false;}
      if(lYtQNgJPJl == true){lYtQNgJPJl = false;}
      if(NoRzeOhlQF == true){NoRzeOhlQF = false;}
      if(AKdJSREeWz == true){AKdJSREeWz = false;}
      if(nhTHOHyPPA == true){nhTHOHyPPA = false;}
      if(keLAyAKFDr == true){keLAyAKFDr = false;}
      if(jcnaKatkyw == true){jcnaKatkyw = false;}
      if(besJyfVJkW == true){besJyfVJkW = false;}
      if(PRWQUVzdKR == true){PRWQUVzdKR = false;}
      if(GybdPKssxm == true){GybdPKssxm = false;}
      if(NNRSXGkBBS == true){NNRSXGkBBS = false;}
      if(dAUfcRGXFo == true){dAUfcRGXFo = false;}
      if(bPZfpdCOtn == true){bPZfpdCOtn = false;}
      if(lcMxJBzDrO == true){lcMxJBzDrO = false;}
      if(jycrnFcuBx == true){jycrnFcuBx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOBMTFHVUA
{ 
  void VMLZZuhHVR()
  { 
      bool uxJOlPxbCe = false;
      bool MBoplfzUsI = false;
      bool pJGjEaBjmg = false;
      bool VUsFhDcWhO = false;
      bool JnRETpXlZe = false;
      bool ijugGkpYJK = false;
      bool OMoVIqHjIi = false;
      bool DbmeyBrCQN = false;
      bool DOKHxkZMzx = false;
      bool NDNWAwzuub = false;
      bool hndqbGxQhE = false;
      bool rmIuHzChXX = false;
      bool RukLVzOPeC = false;
      bool CxGofPkTeq = false;
      bool nJdtEZuRPA = false;
      bool sRWXJmCSUc = false;
      bool rgleCugSPr = false;
      bool NhCgiIQpGu = false;
      bool DwzdIjZies = false;
      bool MSyByGWyqI = false;
      string rXxwMAXaAF;
      string ldlCkXbyhC;
      string BwVybjEgGH;
      string UixcwrRQOR;
      string KKzjfbhCOg;
      string sRCnHuCyUc;
      string wqUsjDgIFs;
      string GKiQqqxkSz;
      string CBRYNCfJUA;
      string pSwlVTpFzc;
      string uYwVZhikwQ;
      string yQfUZtZueh;
      string WXmECmOxuX;
      string BqloEcFuyf;
      string TuMECZmaLa;
      string staRGXkqSl;
      string TkoXOGepQx;
      string odwzOaKiBc;
      string AmlTdGQUif;
      string rNcLLhFoow;
      if(rXxwMAXaAF == uYwVZhikwQ){uxJOlPxbCe = true;}
      else if(uYwVZhikwQ == rXxwMAXaAF){hndqbGxQhE = true;}
      if(ldlCkXbyhC == yQfUZtZueh){MBoplfzUsI = true;}
      else if(yQfUZtZueh == ldlCkXbyhC){rmIuHzChXX = true;}
      if(BwVybjEgGH == WXmECmOxuX){pJGjEaBjmg = true;}
      else if(WXmECmOxuX == BwVybjEgGH){RukLVzOPeC = true;}
      if(UixcwrRQOR == BqloEcFuyf){VUsFhDcWhO = true;}
      else if(BqloEcFuyf == UixcwrRQOR){CxGofPkTeq = true;}
      if(KKzjfbhCOg == TuMECZmaLa){JnRETpXlZe = true;}
      else if(TuMECZmaLa == KKzjfbhCOg){nJdtEZuRPA = true;}
      if(sRCnHuCyUc == staRGXkqSl){ijugGkpYJK = true;}
      else if(staRGXkqSl == sRCnHuCyUc){sRWXJmCSUc = true;}
      if(wqUsjDgIFs == TkoXOGepQx){OMoVIqHjIi = true;}
      else if(TkoXOGepQx == wqUsjDgIFs){rgleCugSPr = true;}
      if(GKiQqqxkSz == odwzOaKiBc){DbmeyBrCQN = true;}
      if(CBRYNCfJUA == AmlTdGQUif){DOKHxkZMzx = true;}
      if(pSwlVTpFzc == rNcLLhFoow){NDNWAwzuub = true;}
      while(odwzOaKiBc == GKiQqqxkSz){NhCgiIQpGu = true;}
      while(AmlTdGQUif == AmlTdGQUif){DwzdIjZies = true;}
      while(rNcLLhFoow == rNcLLhFoow){MSyByGWyqI = true;}
      if(uxJOlPxbCe == true){uxJOlPxbCe = false;}
      if(MBoplfzUsI == true){MBoplfzUsI = false;}
      if(pJGjEaBjmg == true){pJGjEaBjmg = false;}
      if(VUsFhDcWhO == true){VUsFhDcWhO = false;}
      if(JnRETpXlZe == true){JnRETpXlZe = false;}
      if(ijugGkpYJK == true){ijugGkpYJK = false;}
      if(OMoVIqHjIi == true){OMoVIqHjIi = false;}
      if(DbmeyBrCQN == true){DbmeyBrCQN = false;}
      if(DOKHxkZMzx == true){DOKHxkZMzx = false;}
      if(NDNWAwzuub == true){NDNWAwzuub = false;}
      if(hndqbGxQhE == true){hndqbGxQhE = false;}
      if(rmIuHzChXX == true){rmIuHzChXX = false;}
      if(RukLVzOPeC == true){RukLVzOPeC = false;}
      if(CxGofPkTeq == true){CxGofPkTeq = false;}
      if(nJdtEZuRPA == true){nJdtEZuRPA = false;}
      if(sRWXJmCSUc == true){sRWXJmCSUc = false;}
      if(rgleCugSPr == true){rgleCugSPr = false;}
      if(NhCgiIQpGu == true){NhCgiIQpGu = false;}
      if(DwzdIjZies == true){DwzdIjZies = false;}
      if(MSyByGWyqI == true){MSyByGWyqI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHJSHFZKPI
{ 
  void nxosbBIxap()
  { 
      bool ZnAmKUqqUM = false;
      bool gLyWCFEtab = false;
      bool QkDMkHldQo = false;
      bool weJKpnEnDt = false;
      bool qaxdpgRelz = false;
      bool fukNTojnBD = false;
      bool iMaeQBBnfO = false;
      bool BPqgjomZVE = false;
      bool oGrQJBtwqB = false;
      bool DQmALdASMn = false;
      bool fdyWyPEEcd = false;
      bool BKRwNbUJUP = false;
      bool HEweLkcpUG = false;
      bool oUMgYLHUSs = false;
      bool wpSMzrzpli = false;
      bool JpxxgagTLN = false;
      bool mNiWogxjXB = false;
      bool TzqbSQljeS = false;
      bool llElwyXPAy = false;
      bool enIEFiHuXS = false;
      string biGfPlxYXm;
      string QBugtCPfkF;
      string lfTymWgsbV;
      string EarufHZJpV;
      string ruBUYZJLUR;
      string GOVbsuOIss;
      string EDxBhpIAAl;
      string bGoONqezYM;
      string MVYJPpFPBk;
      string rRQxRoyzli;
      string QJKhoAYGOC;
      string PPiffiemlq;
      string jsyPtKorxY;
      string rfMouCKpTP;
      string RyBzUchjQi;
      string JKNuyXKtne;
      string KfIpJjCtjd;
      string XnTVZlqzuQ;
      string bEbOOhSRpX;
      string rQCoFkoLoj;
      if(biGfPlxYXm == QJKhoAYGOC){ZnAmKUqqUM = true;}
      else if(QJKhoAYGOC == biGfPlxYXm){fdyWyPEEcd = true;}
      if(QBugtCPfkF == PPiffiemlq){gLyWCFEtab = true;}
      else if(PPiffiemlq == QBugtCPfkF){BKRwNbUJUP = true;}
      if(lfTymWgsbV == jsyPtKorxY){QkDMkHldQo = true;}
      else if(jsyPtKorxY == lfTymWgsbV){HEweLkcpUG = true;}
      if(EarufHZJpV == rfMouCKpTP){weJKpnEnDt = true;}
      else if(rfMouCKpTP == EarufHZJpV){oUMgYLHUSs = true;}
      if(ruBUYZJLUR == RyBzUchjQi){qaxdpgRelz = true;}
      else if(RyBzUchjQi == ruBUYZJLUR){wpSMzrzpli = true;}
      if(GOVbsuOIss == JKNuyXKtne){fukNTojnBD = true;}
      else if(JKNuyXKtne == GOVbsuOIss){JpxxgagTLN = true;}
      if(EDxBhpIAAl == KfIpJjCtjd){iMaeQBBnfO = true;}
      else if(KfIpJjCtjd == EDxBhpIAAl){mNiWogxjXB = true;}
      if(bGoONqezYM == XnTVZlqzuQ){BPqgjomZVE = true;}
      if(MVYJPpFPBk == bEbOOhSRpX){oGrQJBtwqB = true;}
      if(rRQxRoyzli == rQCoFkoLoj){DQmALdASMn = true;}
      while(XnTVZlqzuQ == bGoONqezYM){TzqbSQljeS = true;}
      while(bEbOOhSRpX == bEbOOhSRpX){llElwyXPAy = true;}
      while(rQCoFkoLoj == rQCoFkoLoj){enIEFiHuXS = true;}
      if(ZnAmKUqqUM == true){ZnAmKUqqUM = false;}
      if(gLyWCFEtab == true){gLyWCFEtab = false;}
      if(QkDMkHldQo == true){QkDMkHldQo = false;}
      if(weJKpnEnDt == true){weJKpnEnDt = false;}
      if(qaxdpgRelz == true){qaxdpgRelz = false;}
      if(fukNTojnBD == true){fukNTojnBD = false;}
      if(iMaeQBBnfO == true){iMaeQBBnfO = false;}
      if(BPqgjomZVE == true){BPqgjomZVE = false;}
      if(oGrQJBtwqB == true){oGrQJBtwqB = false;}
      if(DQmALdASMn == true){DQmALdASMn = false;}
      if(fdyWyPEEcd == true){fdyWyPEEcd = false;}
      if(BKRwNbUJUP == true){BKRwNbUJUP = false;}
      if(HEweLkcpUG == true){HEweLkcpUG = false;}
      if(oUMgYLHUSs == true){oUMgYLHUSs = false;}
      if(wpSMzrzpli == true){wpSMzrzpli = false;}
      if(JpxxgagTLN == true){JpxxgagTLN = false;}
      if(mNiWogxjXB == true){mNiWogxjXB = false;}
      if(TzqbSQljeS == true){TzqbSQljeS = false;}
      if(llElwyXPAy == true){llElwyXPAy = false;}
      if(enIEFiHuXS == true){enIEFiHuXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBFSCNEXUI
{ 
  void mkKnnKMuMk()
  { 
      bool ihagZxEWRn = false;
      bool BbhpbutnSc = false;
      bool mrgJzCJTlV = false;
      bool LFAGfGauVq = false;
      bool MhhjlqZCoL = false;
      bool pQskVqBQgX = false;
      bool mjjwbwbaKU = false;
      bool TzSaQFKwWI = false;
      bool cGeZftLPjo = false;
      bool EJOyDbxlHp = false;
      bool PyrUrpyRTQ = false;
      bool gFtYufFKPg = false;
      bool jLpUPJkUWo = false;
      bool IXnfsdOKho = false;
      bool wsuTIzPpCX = false;
      bool WlVaGDHWEh = false;
      bool FdueHIRNeQ = false;
      bool RucakpQWMQ = false;
      bool tuRzRVBNZo = false;
      bool VqFAiSyPLz = false;
      string DtsWeIdVXk;
      string TCIiCzqpVt;
      string UNSSKZUeYA;
      string OFDZDSyojo;
      string CFhIaByxgu;
      string ZGynQpaaMF;
      string nzwWVOzhfi;
      string ACGgrPeKqI;
      string aXxcaHHOJM;
      string rXbdACILlM;
      string CPQxtWzQwA;
      string LQiDdQCTwO;
      string HjXSqcZbfo;
      string GSXdGKGzhD;
      string HpSIBbnYAj;
      string AoOXFRqyGQ;
      string wWjHtrrFxS;
      string JDkrGQQPQP;
      string oBbwnQEzYn;
      string THsQGjFLOJ;
      if(DtsWeIdVXk == CPQxtWzQwA){ihagZxEWRn = true;}
      else if(CPQxtWzQwA == DtsWeIdVXk){PyrUrpyRTQ = true;}
      if(TCIiCzqpVt == LQiDdQCTwO){BbhpbutnSc = true;}
      else if(LQiDdQCTwO == TCIiCzqpVt){gFtYufFKPg = true;}
      if(UNSSKZUeYA == HjXSqcZbfo){mrgJzCJTlV = true;}
      else if(HjXSqcZbfo == UNSSKZUeYA){jLpUPJkUWo = true;}
      if(OFDZDSyojo == GSXdGKGzhD){LFAGfGauVq = true;}
      else if(GSXdGKGzhD == OFDZDSyojo){IXnfsdOKho = true;}
      if(CFhIaByxgu == HpSIBbnYAj){MhhjlqZCoL = true;}
      else if(HpSIBbnYAj == CFhIaByxgu){wsuTIzPpCX = true;}
      if(ZGynQpaaMF == AoOXFRqyGQ){pQskVqBQgX = true;}
      else if(AoOXFRqyGQ == ZGynQpaaMF){WlVaGDHWEh = true;}
      if(nzwWVOzhfi == wWjHtrrFxS){mjjwbwbaKU = true;}
      else if(wWjHtrrFxS == nzwWVOzhfi){FdueHIRNeQ = true;}
      if(ACGgrPeKqI == JDkrGQQPQP){TzSaQFKwWI = true;}
      if(aXxcaHHOJM == oBbwnQEzYn){cGeZftLPjo = true;}
      if(rXbdACILlM == THsQGjFLOJ){EJOyDbxlHp = true;}
      while(JDkrGQQPQP == ACGgrPeKqI){RucakpQWMQ = true;}
      while(oBbwnQEzYn == oBbwnQEzYn){tuRzRVBNZo = true;}
      while(THsQGjFLOJ == THsQGjFLOJ){VqFAiSyPLz = true;}
      if(ihagZxEWRn == true){ihagZxEWRn = false;}
      if(BbhpbutnSc == true){BbhpbutnSc = false;}
      if(mrgJzCJTlV == true){mrgJzCJTlV = false;}
      if(LFAGfGauVq == true){LFAGfGauVq = false;}
      if(MhhjlqZCoL == true){MhhjlqZCoL = false;}
      if(pQskVqBQgX == true){pQskVqBQgX = false;}
      if(mjjwbwbaKU == true){mjjwbwbaKU = false;}
      if(TzSaQFKwWI == true){TzSaQFKwWI = false;}
      if(cGeZftLPjo == true){cGeZftLPjo = false;}
      if(EJOyDbxlHp == true){EJOyDbxlHp = false;}
      if(PyrUrpyRTQ == true){PyrUrpyRTQ = false;}
      if(gFtYufFKPg == true){gFtYufFKPg = false;}
      if(jLpUPJkUWo == true){jLpUPJkUWo = false;}
      if(IXnfsdOKho == true){IXnfsdOKho = false;}
      if(wsuTIzPpCX == true){wsuTIzPpCX = false;}
      if(WlVaGDHWEh == true){WlVaGDHWEh = false;}
      if(FdueHIRNeQ == true){FdueHIRNeQ = false;}
      if(RucakpQWMQ == true){RucakpQWMQ = false;}
      if(tuRzRVBNZo == true){tuRzRVBNZo = false;}
      if(VqFAiSyPLz == true){VqFAiSyPLz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMHZGVEAVG
{ 
  void zFPDwcdeFI()
  { 
      bool fkqrVRBJXJ = false;
      bool GxIUzaAzHC = false;
      bool nwwPbnGdeD = false;
      bool oUGpenSByb = false;
      bool DeoeYcIXJg = false;
      bool jlySUinaPh = false;
      bool KXeTUlqSpL = false;
      bool IzAezJHRqy = false;
      bool ehTxSCWnUw = false;
      bool zqkPQezUJm = false;
      bool lphyYklSSL = false;
      bool bWjRDbEhAR = false;
      bool ODxsLQNjOT = false;
      bool KlHDMozUYh = false;
      bool QDUJUbGSMn = false;
      bool aRTrYhrnmH = false;
      bool WBEyBoPgFN = false;
      bool biISALimYi = false;
      bool KtWZsrROed = false;
      bool wLhRKPzVIe = false;
      string gIHohzEWXV;
      string lmXRqJobIh;
      string lDSGyxATzM;
      string nlklePgpkF;
      string dhnNQSQfKw;
      string iZRRGdoApk;
      string zjXKhACklb;
      string bypCEEPFpe;
      string fTJCdOUTfA;
      string ZgzAGsKcfQ;
      string QetiTjiPMC;
      string OjKLEeaUfT;
      string fhFkBuyouL;
      string tlZZOBZahs;
      string eEHdlpVnwa;
      string RoxMkhZIgY;
      string ktTBHcJkwD;
      string FAmmnaabzL;
      string YKsUsFoMof;
      string aRsJHkkFVI;
      if(gIHohzEWXV == QetiTjiPMC){fkqrVRBJXJ = true;}
      else if(QetiTjiPMC == gIHohzEWXV){lphyYklSSL = true;}
      if(lmXRqJobIh == OjKLEeaUfT){GxIUzaAzHC = true;}
      else if(OjKLEeaUfT == lmXRqJobIh){bWjRDbEhAR = true;}
      if(lDSGyxATzM == fhFkBuyouL){nwwPbnGdeD = true;}
      else if(fhFkBuyouL == lDSGyxATzM){ODxsLQNjOT = true;}
      if(nlklePgpkF == tlZZOBZahs){oUGpenSByb = true;}
      else if(tlZZOBZahs == nlklePgpkF){KlHDMozUYh = true;}
      if(dhnNQSQfKw == eEHdlpVnwa){DeoeYcIXJg = true;}
      else if(eEHdlpVnwa == dhnNQSQfKw){QDUJUbGSMn = true;}
      if(iZRRGdoApk == RoxMkhZIgY){jlySUinaPh = true;}
      else if(RoxMkhZIgY == iZRRGdoApk){aRTrYhrnmH = true;}
      if(zjXKhACklb == ktTBHcJkwD){KXeTUlqSpL = true;}
      else if(ktTBHcJkwD == zjXKhACklb){WBEyBoPgFN = true;}
      if(bypCEEPFpe == FAmmnaabzL){IzAezJHRqy = true;}
      if(fTJCdOUTfA == YKsUsFoMof){ehTxSCWnUw = true;}
      if(ZgzAGsKcfQ == aRsJHkkFVI){zqkPQezUJm = true;}
      while(FAmmnaabzL == bypCEEPFpe){biISALimYi = true;}
      while(YKsUsFoMof == YKsUsFoMof){KtWZsrROed = true;}
      while(aRsJHkkFVI == aRsJHkkFVI){wLhRKPzVIe = true;}
      if(fkqrVRBJXJ == true){fkqrVRBJXJ = false;}
      if(GxIUzaAzHC == true){GxIUzaAzHC = false;}
      if(nwwPbnGdeD == true){nwwPbnGdeD = false;}
      if(oUGpenSByb == true){oUGpenSByb = false;}
      if(DeoeYcIXJg == true){DeoeYcIXJg = false;}
      if(jlySUinaPh == true){jlySUinaPh = false;}
      if(KXeTUlqSpL == true){KXeTUlqSpL = false;}
      if(IzAezJHRqy == true){IzAezJHRqy = false;}
      if(ehTxSCWnUw == true){ehTxSCWnUw = false;}
      if(zqkPQezUJm == true){zqkPQezUJm = false;}
      if(lphyYklSSL == true){lphyYklSSL = false;}
      if(bWjRDbEhAR == true){bWjRDbEhAR = false;}
      if(ODxsLQNjOT == true){ODxsLQNjOT = false;}
      if(KlHDMozUYh == true){KlHDMozUYh = false;}
      if(QDUJUbGSMn == true){QDUJUbGSMn = false;}
      if(aRTrYhrnmH == true){aRTrYhrnmH = false;}
      if(WBEyBoPgFN == true){WBEyBoPgFN = false;}
      if(biISALimYi == true){biISALimYi = false;}
      if(KtWZsrROed == true){KtWZsrROed = false;}
      if(wLhRKPzVIe == true){wLhRKPzVIe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MERKVTPWTU
{ 
  void gzIwGJoRaP()
  { 
      bool kJRdsXZQYl = false;
      bool RNujcIPtxd = false;
      bool ljfYBLmfyi = false;
      bool ZHCrEDtRGj = false;
      bool cVXywpGgsM = false;
      bool CKoilBdscg = false;
      bool ktRoLKKCfZ = false;
      bool OxnNAQMgbK = false;
      bool EFllgPRSGC = false;
      bool ZAoYyiDhml = false;
      bool fEBTyEWbiU = false;
      bool oxQScfHfIw = false;
      bool squczNIOOR = false;
      bool NdtpeADSmb = false;
      bool sojlNciVwS = false;
      bool aWZpsnIXTj = false;
      bool wHNQGKCanb = false;
      bool borgDDGJOW = false;
      bool dlRuppEDxp = false;
      bool qfzCfkbTeD = false;
      string SZAdEpRKlY;
      string dGPTluospO;
      string VCpgrnYqDy;
      string UulsKGNFnA;
      string ByiLfSNjOL;
      string VxsDjPiTlP;
      string QZHmDiUVIe;
      string gjEpMWTeAY;
      string aobqbWChJt;
      string WsSYiaquHx;
      string yqaidlrCpN;
      string wESNobyPKg;
      string flMOInRfHk;
      string eXWCZiNsNp;
      string eAruxSZFjH;
      string cbkaRLeLap;
      string ULuFhYgQmF;
      string NFCTBetQQp;
      string NMwAHDlwkO;
      string EBRWVSFmNY;
      if(SZAdEpRKlY == yqaidlrCpN){kJRdsXZQYl = true;}
      else if(yqaidlrCpN == SZAdEpRKlY){fEBTyEWbiU = true;}
      if(dGPTluospO == wESNobyPKg){RNujcIPtxd = true;}
      else if(wESNobyPKg == dGPTluospO){oxQScfHfIw = true;}
      if(VCpgrnYqDy == flMOInRfHk){ljfYBLmfyi = true;}
      else if(flMOInRfHk == VCpgrnYqDy){squczNIOOR = true;}
      if(UulsKGNFnA == eXWCZiNsNp){ZHCrEDtRGj = true;}
      else if(eXWCZiNsNp == UulsKGNFnA){NdtpeADSmb = true;}
      if(ByiLfSNjOL == eAruxSZFjH){cVXywpGgsM = true;}
      else if(eAruxSZFjH == ByiLfSNjOL){sojlNciVwS = true;}
      if(VxsDjPiTlP == cbkaRLeLap){CKoilBdscg = true;}
      else if(cbkaRLeLap == VxsDjPiTlP){aWZpsnIXTj = true;}
      if(QZHmDiUVIe == ULuFhYgQmF){ktRoLKKCfZ = true;}
      else if(ULuFhYgQmF == QZHmDiUVIe){wHNQGKCanb = true;}
      if(gjEpMWTeAY == NFCTBetQQp){OxnNAQMgbK = true;}
      if(aobqbWChJt == NMwAHDlwkO){EFllgPRSGC = true;}
      if(WsSYiaquHx == EBRWVSFmNY){ZAoYyiDhml = true;}
      while(NFCTBetQQp == gjEpMWTeAY){borgDDGJOW = true;}
      while(NMwAHDlwkO == NMwAHDlwkO){dlRuppEDxp = true;}
      while(EBRWVSFmNY == EBRWVSFmNY){qfzCfkbTeD = true;}
      if(kJRdsXZQYl == true){kJRdsXZQYl = false;}
      if(RNujcIPtxd == true){RNujcIPtxd = false;}
      if(ljfYBLmfyi == true){ljfYBLmfyi = false;}
      if(ZHCrEDtRGj == true){ZHCrEDtRGj = false;}
      if(cVXywpGgsM == true){cVXywpGgsM = false;}
      if(CKoilBdscg == true){CKoilBdscg = false;}
      if(ktRoLKKCfZ == true){ktRoLKKCfZ = false;}
      if(OxnNAQMgbK == true){OxnNAQMgbK = false;}
      if(EFllgPRSGC == true){EFllgPRSGC = false;}
      if(ZAoYyiDhml == true){ZAoYyiDhml = false;}
      if(fEBTyEWbiU == true){fEBTyEWbiU = false;}
      if(oxQScfHfIw == true){oxQScfHfIw = false;}
      if(squczNIOOR == true){squczNIOOR = false;}
      if(NdtpeADSmb == true){NdtpeADSmb = false;}
      if(sojlNciVwS == true){sojlNciVwS = false;}
      if(aWZpsnIXTj == true){aWZpsnIXTj = false;}
      if(wHNQGKCanb == true){wHNQGKCanb = false;}
      if(borgDDGJOW == true){borgDDGJOW = false;}
      if(dlRuppEDxp == true){dlRuppEDxp = false;}
      if(qfzCfkbTeD == true){qfzCfkbTeD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQGDTFHLRG
{ 
  void afhtGjMmMk()
  { 
      bool kCmufdWKXl = false;
      bool VwTReJjryb = false;
      bool dSQuTifSWh = false;
      bool XskUAKHAqq = false;
      bool OZdYPHkRdc = false;
      bool edOefSlraw = false;
      bool yDnpOcKyRU = false;
      bool BjAGMDoqeM = false;
      bool xOnsDsdGog = false;
      bool XPYurLlnKm = false;
      bool wlzJaucHRb = false;
      bool duMOzjOtlV = false;
      bool yEJjwlKFOB = false;
      bool RBfqQKOdRH = false;
      bool PVnMDcDKuI = false;
      bool wqBooqcONo = false;
      bool jWsQKcOUxn = false;
      bool UjbeFbQxgT = false;
      bool hAKFEZzqCY = false;
      bool hzQcWrbWBa = false;
      string FTgTpuCdfU;
      string eLFfXaXyGn;
      string zLlBtcATPQ;
      string kCIalggpyF;
      string dokyrRgule;
      string DuHsItgeYM;
      string uiNPicCetq;
      string tgABKKanIc;
      string uEgkNptPRq;
      string zBQkKuaVPP;
      string OCBujVuGix;
      string TsVwRqBcBs;
      string hmMCqrQOpP;
      string jEYsOsDlAr;
      string umgUXGeUTS;
      string syTVgboyDq;
      string FfPTNOUcgX;
      string mObJytGrek;
      string MuuXVkkCLl;
      string DEiImPWMGJ;
      if(FTgTpuCdfU == OCBujVuGix){kCmufdWKXl = true;}
      else if(OCBujVuGix == FTgTpuCdfU){wlzJaucHRb = true;}
      if(eLFfXaXyGn == TsVwRqBcBs){VwTReJjryb = true;}
      else if(TsVwRqBcBs == eLFfXaXyGn){duMOzjOtlV = true;}
      if(zLlBtcATPQ == hmMCqrQOpP){dSQuTifSWh = true;}
      else if(hmMCqrQOpP == zLlBtcATPQ){yEJjwlKFOB = true;}
      if(kCIalggpyF == jEYsOsDlAr){XskUAKHAqq = true;}
      else if(jEYsOsDlAr == kCIalggpyF){RBfqQKOdRH = true;}
      if(dokyrRgule == umgUXGeUTS){OZdYPHkRdc = true;}
      else if(umgUXGeUTS == dokyrRgule){PVnMDcDKuI = true;}
      if(DuHsItgeYM == syTVgboyDq){edOefSlraw = true;}
      else if(syTVgboyDq == DuHsItgeYM){wqBooqcONo = true;}
      if(uiNPicCetq == FfPTNOUcgX){yDnpOcKyRU = true;}
      else if(FfPTNOUcgX == uiNPicCetq){jWsQKcOUxn = true;}
      if(tgABKKanIc == mObJytGrek){BjAGMDoqeM = true;}
      if(uEgkNptPRq == MuuXVkkCLl){xOnsDsdGog = true;}
      if(zBQkKuaVPP == DEiImPWMGJ){XPYurLlnKm = true;}
      while(mObJytGrek == tgABKKanIc){UjbeFbQxgT = true;}
      while(MuuXVkkCLl == MuuXVkkCLl){hAKFEZzqCY = true;}
      while(DEiImPWMGJ == DEiImPWMGJ){hzQcWrbWBa = true;}
      if(kCmufdWKXl == true){kCmufdWKXl = false;}
      if(VwTReJjryb == true){VwTReJjryb = false;}
      if(dSQuTifSWh == true){dSQuTifSWh = false;}
      if(XskUAKHAqq == true){XskUAKHAqq = false;}
      if(OZdYPHkRdc == true){OZdYPHkRdc = false;}
      if(edOefSlraw == true){edOefSlraw = false;}
      if(yDnpOcKyRU == true){yDnpOcKyRU = false;}
      if(BjAGMDoqeM == true){BjAGMDoqeM = false;}
      if(xOnsDsdGog == true){xOnsDsdGog = false;}
      if(XPYurLlnKm == true){XPYurLlnKm = false;}
      if(wlzJaucHRb == true){wlzJaucHRb = false;}
      if(duMOzjOtlV == true){duMOzjOtlV = false;}
      if(yEJjwlKFOB == true){yEJjwlKFOB = false;}
      if(RBfqQKOdRH == true){RBfqQKOdRH = false;}
      if(PVnMDcDKuI == true){PVnMDcDKuI = false;}
      if(wqBooqcONo == true){wqBooqcONo = false;}
      if(jWsQKcOUxn == true){jWsQKcOUxn = false;}
      if(UjbeFbQxgT == true){UjbeFbQxgT = false;}
      if(hAKFEZzqCY == true){hAKFEZzqCY = false;}
      if(hzQcWrbWBa == true){hzQcWrbWBa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XUZJUYVZRB
{ 
  void wtthprTFql()
  { 
      bool FaDCmtpHCG = false;
      bool HJlIlVHanZ = false;
      bool rJBUucrelK = false;
      bool CYjFSiAQhU = false;
      bool WAWeaomLUt = false;
      bool rudSBwZiGJ = false;
      bool BLVqDiZgpD = false;
      bool VqrTCqlVtG = false;
      bool ogJrSGuQDW = false;
      bool IQJXSLeebr = false;
      bool OGURXADJQJ = false;
      bool KDoAUUCdYx = false;
      bool mJcTtFhTBq = false;
      bool MGtBqiLqTR = false;
      bool ClAtLEbIDx = false;
      bool IBGdEFcBXS = false;
      bool RjIYxDJmJk = false;
      bool JKJHtBJiHo = false;
      bool cZPDhLAQwk = false;
      bool FJTAzScawI = false;
      string tBTtLYgAtI;
      string SPQLuBgmXZ;
      string qBrbNwWTkV;
      string EAIyGUJarG;
      string ihcEoSOiVM;
      string rkYOnrJqgO;
      string CNOXESGSFZ;
      string qGtQpJYmmt;
      string hnyYdSasJN;
      string LStdEVSFzW;
      string MucwUlqIXd;
      string TWDlgNOptl;
      string qMIrNYLPLU;
      string pTmQhlKCDq;
      string aSVfsoOHxp;
      string GcKNezmkhw;
      string ZawDmAimDt;
      string DMlDKYqcyY;
      string JESVONIZli;
      string zZUHQAWRrs;
      if(tBTtLYgAtI == MucwUlqIXd){FaDCmtpHCG = true;}
      else if(MucwUlqIXd == tBTtLYgAtI){OGURXADJQJ = true;}
      if(SPQLuBgmXZ == TWDlgNOptl){HJlIlVHanZ = true;}
      else if(TWDlgNOptl == SPQLuBgmXZ){KDoAUUCdYx = true;}
      if(qBrbNwWTkV == qMIrNYLPLU){rJBUucrelK = true;}
      else if(qMIrNYLPLU == qBrbNwWTkV){mJcTtFhTBq = true;}
      if(EAIyGUJarG == pTmQhlKCDq){CYjFSiAQhU = true;}
      else if(pTmQhlKCDq == EAIyGUJarG){MGtBqiLqTR = true;}
      if(ihcEoSOiVM == aSVfsoOHxp){WAWeaomLUt = true;}
      else if(aSVfsoOHxp == ihcEoSOiVM){ClAtLEbIDx = true;}
      if(rkYOnrJqgO == GcKNezmkhw){rudSBwZiGJ = true;}
      else if(GcKNezmkhw == rkYOnrJqgO){IBGdEFcBXS = true;}
      if(CNOXESGSFZ == ZawDmAimDt){BLVqDiZgpD = true;}
      else if(ZawDmAimDt == CNOXESGSFZ){RjIYxDJmJk = true;}
      if(qGtQpJYmmt == DMlDKYqcyY){VqrTCqlVtG = true;}
      if(hnyYdSasJN == JESVONIZli){ogJrSGuQDW = true;}
      if(LStdEVSFzW == zZUHQAWRrs){IQJXSLeebr = true;}
      while(DMlDKYqcyY == qGtQpJYmmt){JKJHtBJiHo = true;}
      while(JESVONIZli == JESVONIZli){cZPDhLAQwk = true;}
      while(zZUHQAWRrs == zZUHQAWRrs){FJTAzScawI = true;}
      if(FaDCmtpHCG == true){FaDCmtpHCG = false;}
      if(HJlIlVHanZ == true){HJlIlVHanZ = false;}
      if(rJBUucrelK == true){rJBUucrelK = false;}
      if(CYjFSiAQhU == true){CYjFSiAQhU = false;}
      if(WAWeaomLUt == true){WAWeaomLUt = false;}
      if(rudSBwZiGJ == true){rudSBwZiGJ = false;}
      if(BLVqDiZgpD == true){BLVqDiZgpD = false;}
      if(VqrTCqlVtG == true){VqrTCqlVtG = false;}
      if(ogJrSGuQDW == true){ogJrSGuQDW = false;}
      if(IQJXSLeebr == true){IQJXSLeebr = false;}
      if(OGURXADJQJ == true){OGURXADJQJ = false;}
      if(KDoAUUCdYx == true){KDoAUUCdYx = false;}
      if(mJcTtFhTBq == true){mJcTtFhTBq = false;}
      if(MGtBqiLqTR == true){MGtBqiLqTR = false;}
      if(ClAtLEbIDx == true){ClAtLEbIDx = false;}
      if(IBGdEFcBXS == true){IBGdEFcBXS = false;}
      if(RjIYxDJmJk == true){RjIYxDJmJk = false;}
      if(JKJHtBJiHo == true){JKJHtBJiHo = false;}
      if(cZPDhLAQwk == true){cZPDhLAQwk = false;}
      if(FJTAzScawI == true){FJTAzScawI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSIVKBIECS
{ 
  void jIuJLktUQG()
  { 
      bool amdtkPQfMZ = false;
      bool HiwauBkzCS = false;
      bool WZeBpAHZNY = false;
      bool IuOkpRgUiF = false;
      bool zZHyUVLRsE = false;
      bool SuiJgAIbEk = false;
      bool HqRmRLTKkd = false;
      bool UPQwTwRffU = false;
      bool nofJFNMEEo = false;
      bool JEQxxHHUfI = false;
      bool BBgPiCdlpj = false;
      bool ibuiwSKIgE = false;
      bool zPGuTQzSyL = false;
      bool nxAXSmIPZD = false;
      bool iZNTFhJgAe = false;
      bool xzmaJltkwS = false;
      bool DLnewlaXQJ = false;
      bool JthdVYClpl = false;
      bool GSRSOoJYNg = false;
      bool rWTHzWlhXT = false;
      string nlAgGmBRed;
      string xdxUXnPOGn;
      string MOyznalCau;
      string klSEmMwutx;
      string AdWQEqUmnn;
      string yZqyNZmArf;
      string ByqjrLLsgL;
      string rUTJnirhux;
      string GzNlxKuTpM;
      string ZwCOwBllXs;
      string fbFcwdFgKe;
      string hEFuYCkFmh;
      string PqCTkuRFNl;
      string wFKBQdsjpS;
      string ENJKeUpHos;
      string QfzpcoZkqA;
      string MATXhbtDdu;
      string IAPTcCgqoQ;
      string EKPTVPFUYb;
      string EIsoGEtkcD;
      if(nlAgGmBRed == fbFcwdFgKe){amdtkPQfMZ = true;}
      else if(fbFcwdFgKe == nlAgGmBRed){BBgPiCdlpj = true;}
      if(xdxUXnPOGn == hEFuYCkFmh){HiwauBkzCS = true;}
      else if(hEFuYCkFmh == xdxUXnPOGn){ibuiwSKIgE = true;}
      if(MOyznalCau == PqCTkuRFNl){WZeBpAHZNY = true;}
      else if(PqCTkuRFNl == MOyznalCau){zPGuTQzSyL = true;}
      if(klSEmMwutx == wFKBQdsjpS){IuOkpRgUiF = true;}
      else if(wFKBQdsjpS == klSEmMwutx){nxAXSmIPZD = true;}
      if(AdWQEqUmnn == ENJKeUpHos){zZHyUVLRsE = true;}
      else if(ENJKeUpHos == AdWQEqUmnn){iZNTFhJgAe = true;}
      if(yZqyNZmArf == QfzpcoZkqA){SuiJgAIbEk = true;}
      else if(QfzpcoZkqA == yZqyNZmArf){xzmaJltkwS = true;}
      if(ByqjrLLsgL == MATXhbtDdu){HqRmRLTKkd = true;}
      else if(MATXhbtDdu == ByqjrLLsgL){DLnewlaXQJ = true;}
      if(rUTJnirhux == IAPTcCgqoQ){UPQwTwRffU = true;}
      if(GzNlxKuTpM == EKPTVPFUYb){nofJFNMEEo = true;}
      if(ZwCOwBllXs == EIsoGEtkcD){JEQxxHHUfI = true;}
      while(IAPTcCgqoQ == rUTJnirhux){JthdVYClpl = true;}
      while(EKPTVPFUYb == EKPTVPFUYb){GSRSOoJYNg = true;}
      while(EIsoGEtkcD == EIsoGEtkcD){rWTHzWlhXT = true;}
      if(amdtkPQfMZ == true){amdtkPQfMZ = false;}
      if(HiwauBkzCS == true){HiwauBkzCS = false;}
      if(WZeBpAHZNY == true){WZeBpAHZNY = false;}
      if(IuOkpRgUiF == true){IuOkpRgUiF = false;}
      if(zZHyUVLRsE == true){zZHyUVLRsE = false;}
      if(SuiJgAIbEk == true){SuiJgAIbEk = false;}
      if(HqRmRLTKkd == true){HqRmRLTKkd = false;}
      if(UPQwTwRffU == true){UPQwTwRffU = false;}
      if(nofJFNMEEo == true){nofJFNMEEo = false;}
      if(JEQxxHHUfI == true){JEQxxHHUfI = false;}
      if(BBgPiCdlpj == true){BBgPiCdlpj = false;}
      if(ibuiwSKIgE == true){ibuiwSKIgE = false;}
      if(zPGuTQzSyL == true){zPGuTQzSyL = false;}
      if(nxAXSmIPZD == true){nxAXSmIPZD = false;}
      if(iZNTFhJgAe == true){iZNTFhJgAe = false;}
      if(xzmaJltkwS == true){xzmaJltkwS = false;}
      if(DLnewlaXQJ == true){DLnewlaXQJ = false;}
      if(JthdVYClpl == true){JthdVYClpl = false;}
      if(GSRSOoJYNg == true){GSRSOoJYNg = false;}
      if(rWTHzWlhXT == true){rWTHzWlhXT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZZOJRTSWU
{ 
  void JDDHHWZFFL()
  { 
      bool fnepjwMNAN = false;
      bool sVUsnRJcca = false;
      bool KTRQOZVFXm = false;
      bool DUhBALLAHD = false;
      bool urUMlAydiP = false;
      bool rdcNoMVNbJ = false;
      bool aGoMKYnTrb = false;
      bool FJVYeSyFeO = false;
      bool arVIuYrTLn = false;
      bool pxXxcoCHBM = false;
      bool LekGJhIDhW = false;
      bool NQhNihkgRl = false;
      bool fTHDlIkYwp = false;
      bool PqDRCwHOyM = false;
      bool PnlnaYOKOt = false;
      bool DUoOgqWgUB = false;
      bool xjHrGVMQLl = false;
      bool aViEWqhTcM = false;
      bool sZJBltBokK = false;
      bool ZZtwPegthE = false;
      string rZSnoDmbku;
      string eLLIbZdWBW;
      string gOkSSmqVEa;
      string hexNjHWqdW;
      string yDZtJqkMwW;
      string MMQsKdoAVC;
      string MQWKNzNxXT;
      string CmsdYdnpIa;
      string CdZgOVNEDG;
      string SWVaKgfOgJ;
      string cmnbTYSmUf;
      string oyqtAhqpuq;
      string kJtRBfRRTq;
      string xYJzyPoxMo;
      string CaiWQUfaab;
      string ppToYTsWan;
      string HATdiPnrwk;
      string rsdFoKZWBg;
      string zpqqAHFUZe;
      string VSWXgBHFnA;
      if(rZSnoDmbku == cmnbTYSmUf){fnepjwMNAN = true;}
      else if(cmnbTYSmUf == rZSnoDmbku){LekGJhIDhW = true;}
      if(eLLIbZdWBW == oyqtAhqpuq){sVUsnRJcca = true;}
      else if(oyqtAhqpuq == eLLIbZdWBW){NQhNihkgRl = true;}
      if(gOkSSmqVEa == kJtRBfRRTq){KTRQOZVFXm = true;}
      else if(kJtRBfRRTq == gOkSSmqVEa){fTHDlIkYwp = true;}
      if(hexNjHWqdW == xYJzyPoxMo){DUhBALLAHD = true;}
      else if(xYJzyPoxMo == hexNjHWqdW){PqDRCwHOyM = true;}
      if(yDZtJqkMwW == CaiWQUfaab){urUMlAydiP = true;}
      else if(CaiWQUfaab == yDZtJqkMwW){PnlnaYOKOt = true;}
      if(MMQsKdoAVC == ppToYTsWan){rdcNoMVNbJ = true;}
      else if(ppToYTsWan == MMQsKdoAVC){DUoOgqWgUB = true;}
      if(MQWKNzNxXT == HATdiPnrwk){aGoMKYnTrb = true;}
      else if(HATdiPnrwk == MQWKNzNxXT){xjHrGVMQLl = true;}
      if(CmsdYdnpIa == rsdFoKZWBg){FJVYeSyFeO = true;}
      if(CdZgOVNEDG == zpqqAHFUZe){arVIuYrTLn = true;}
      if(SWVaKgfOgJ == VSWXgBHFnA){pxXxcoCHBM = true;}
      while(rsdFoKZWBg == CmsdYdnpIa){aViEWqhTcM = true;}
      while(zpqqAHFUZe == zpqqAHFUZe){sZJBltBokK = true;}
      while(VSWXgBHFnA == VSWXgBHFnA){ZZtwPegthE = true;}
      if(fnepjwMNAN == true){fnepjwMNAN = false;}
      if(sVUsnRJcca == true){sVUsnRJcca = false;}
      if(KTRQOZVFXm == true){KTRQOZVFXm = false;}
      if(DUhBALLAHD == true){DUhBALLAHD = false;}
      if(urUMlAydiP == true){urUMlAydiP = false;}
      if(rdcNoMVNbJ == true){rdcNoMVNbJ = false;}
      if(aGoMKYnTrb == true){aGoMKYnTrb = false;}
      if(FJVYeSyFeO == true){FJVYeSyFeO = false;}
      if(arVIuYrTLn == true){arVIuYrTLn = false;}
      if(pxXxcoCHBM == true){pxXxcoCHBM = false;}
      if(LekGJhIDhW == true){LekGJhIDhW = false;}
      if(NQhNihkgRl == true){NQhNihkgRl = false;}
      if(fTHDlIkYwp == true){fTHDlIkYwp = false;}
      if(PqDRCwHOyM == true){PqDRCwHOyM = false;}
      if(PnlnaYOKOt == true){PnlnaYOKOt = false;}
      if(DUoOgqWgUB == true){DUoOgqWgUB = false;}
      if(xjHrGVMQLl == true){xjHrGVMQLl = false;}
      if(aViEWqhTcM == true){aViEWqhTcM = false;}
      if(sZJBltBokK == true){sZJBltBokK = false;}
      if(ZZtwPegthE == true){ZZtwPegthE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSGRBMUMTI
{ 
  void XcgpsPJStF()
  { 
      bool bPHEpdVJeU = false;
      bool IOQBWmwKIn = false;
      bool CTPrVQYnPC = false;
      bool baDwCHWgBP = false;
      bool lUnsAXDRko = false;
      bool BROUxHzOiY = false;
      bool EhtbrhKTyO = false;
      bool PPJrChfWqx = false;
      bool NGCaAKLiyu = false;
      bool IHybKDZMAS = false;
      bool MjTVYlHVSP = false;
      bool abWkLxeTah = false;
      bool VbUDGIRghy = false;
      bool ITWYkdmgBO = false;
      bool CoPiTfjMQM = false;
      bool YGkSwjOQPQ = false;
      bool TZnTGHFyAg = false;
      bool KyRLefLkiZ = false;
      bool XEQUZBhEbA = false;
      bool PWQktcBwbM = false;
      string SRFAcwJNAR;
      string TDnEtDDpFJ;
      string QlSqnzzsCS;
      string XjnqbzZnKq;
      string eaUHssqWTn;
      string UKjxNfyOMc;
      string wQLhtjOwcu;
      string cOeNepRLxt;
      string HcYNyMAqdw;
      string BLaguOPlMJ;
      string dttYLFfVRX;
      string NlRRUTrxjg;
      string jXSfsRnxSP;
      string ZfymPNhzBs;
      string feYGhOsJLb;
      string WRBfZGaNft;
      string QhCBxgmdBH;
      string kruqAEyMxd;
      string XdkqsIeSNJ;
      string lTTHbybWJA;
      if(SRFAcwJNAR == dttYLFfVRX){bPHEpdVJeU = true;}
      else if(dttYLFfVRX == SRFAcwJNAR){MjTVYlHVSP = true;}
      if(TDnEtDDpFJ == NlRRUTrxjg){IOQBWmwKIn = true;}
      else if(NlRRUTrxjg == TDnEtDDpFJ){abWkLxeTah = true;}
      if(QlSqnzzsCS == jXSfsRnxSP){CTPrVQYnPC = true;}
      else if(jXSfsRnxSP == QlSqnzzsCS){VbUDGIRghy = true;}
      if(XjnqbzZnKq == ZfymPNhzBs){baDwCHWgBP = true;}
      else if(ZfymPNhzBs == XjnqbzZnKq){ITWYkdmgBO = true;}
      if(eaUHssqWTn == feYGhOsJLb){lUnsAXDRko = true;}
      else if(feYGhOsJLb == eaUHssqWTn){CoPiTfjMQM = true;}
      if(UKjxNfyOMc == WRBfZGaNft){BROUxHzOiY = true;}
      else if(WRBfZGaNft == UKjxNfyOMc){YGkSwjOQPQ = true;}
      if(wQLhtjOwcu == QhCBxgmdBH){EhtbrhKTyO = true;}
      else if(QhCBxgmdBH == wQLhtjOwcu){TZnTGHFyAg = true;}
      if(cOeNepRLxt == kruqAEyMxd){PPJrChfWqx = true;}
      if(HcYNyMAqdw == XdkqsIeSNJ){NGCaAKLiyu = true;}
      if(BLaguOPlMJ == lTTHbybWJA){IHybKDZMAS = true;}
      while(kruqAEyMxd == cOeNepRLxt){KyRLefLkiZ = true;}
      while(XdkqsIeSNJ == XdkqsIeSNJ){XEQUZBhEbA = true;}
      while(lTTHbybWJA == lTTHbybWJA){PWQktcBwbM = true;}
      if(bPHEpdVJeU == true){bPHEpdVJeU = false;}
      if(IOQBWmwKIn == true){IOQBWmwKIn = false;}
      if(CTPrVQYnPC == true){CTPrVQYnPC = false;}
      if(baDwCHWgBP == true){baDwCHWgBP = false;}
      if(lUnsAXDRko == true){lUnsAXDRko = false;}
      if(BROUxHzOiY == true){BROUxHzOiY = false;}
      if(EhtbrhKTyO == true){EhtbrhKTyO = false;}
      if(PPJrChfWqx == true){PPJrChfWqx = false;}
      if(NGCaAKLiyu == true){NGCaAKLiyu = false;}
      if(IHybKDZMAS == true){IHybKDZMAS = false;}
      if(MjTVYlHVSP == true){MjTVYlHVSP = false;}
      if(abWkLxeTah == true){abWkLxeTah = false;}
      if(VbUDGIRghy == true){VbUDGIRghy = false;}
      if(ITWYkdmgBO == true){ITWYkdmgBO = false;}
      if(CoPiTfjMQM == true){CoPiTfjMQM = false;}
      if(YGkSwjOQPQ == true){YGkSwjOQPQ = false;}
      if(TZnTGHFyAg == true){TZnTGHFyAg = false;}
      if(KyRLefLkiZ == true){KyRLefLkiZ = false;}
      if(XEQUZBhEbA == true){XEQUZBhEbA = false;}
      if(PWQktcBwbM == true){PWQktcBwbM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPZVEHFAUP
{ 
  void lOAJfNtPnP()
  { 
      bool xjpBRxFofM = false;
      bool nbtfhLsGtI = false;
      bool NCYyNYqrSD = false;
      bool GztiedYbLY = false;
      bool oggDnurSEZ = false;
      bool SoDpHtKqns = false;
      bool GMVcGnhLAD = false;
      bool lQtUTgVVKR = false;
      bool fYmsjQwDbk = false;
      bool ShnRSbKDwz = false;
      bool NgSAnBthVZ = false;
      bool YogVMhYcro = false;
      bool rdjOkEcbBr = false;
      bool VRYKEzFlFi = false;
      bool WOgBLdAREk = false;
      bool ChLHHixDPi = false;
      bool YRfdEHPVRN = false;
      bool bmXJScxiCG = false;
      bool DKXQonGRDU = false;
      bool BCWVKEiCxE = false;
      string tmeVEJgNDM;
      string zbXolbAsBm;
      string CVMfSLQdiR;
      string suUqbKsLKT;
      string obwLCFzVYQ;
      string xWYbHXZzDr;
      string rCekTEGfMa;
      string hoihyaZBdN;
      string MtERUVVsjD;
      string ktHSalxKrx;
      string ySIxiImpdg;
      string yYUpexxMQx;
      string hMwJomgQGL;
      string dOIfOtlHhM;
      string hfPCEMYRmc;
      string njsuPlVzIu;
      string aWjRDiPobk;
      string LpeEOCxtEb;
      string NPdcWtVNPc;
      string XmylkLuxzV;
      if(tmeVEJgNDM == ySIxiImpdg){xjpBRxFofM = true;}
      else if(ySIxiImpdg == tmeVEJgNDM){NgSAnBthVZ = true;}
      if(zbXolbAsBm == yYUpexxMQx){nbtfhLsGtI = true;}
      else if(yYUpexxMQx == zbXolbAsBm){YogVMhYcro = true;}
      if(CVMfSLQdiR == hMwJomgQGL){NCYyNYqrSD = true;}
      else if(hMwJomgQGL == CVMfSLQdiR){rdjOkEcbBr = true;}
      if(suUqbKsLKT == dOIfOtlHhM){GztiedYbLY = true;}
      else if(dOIfOtlHhM == suUqbKsLKT){VRYKEzFlFi = true;}
      if(obwLCFzVYQ == hfPCEMYRmc){oggDnurSEZ = true;}
      else if(hfPCEMYRmc == obwLCFzVYQ){WOgBLdAREk = true;}
      if(xWYbHXZzDr == njsuPlVzIu){SoDpHtKqns = true;}
      else if(njsuPlVzIu == xWYbHXZzDr){ChLHHixDPi = true;}
      if(rCekTEGfMa == aWjRDiPobk){GMVcGnhLAD = true;}
      else if(aWjRDiPobk == rCekTEGfMa){YRfdEHPVRN = true;}
      if(hoihyaZBdN == LpeEOCxtEb){lQtUTgVVKR = true;}
      if(MtERUVVsjD == NPdcWtVNPc){fYmsjQwDbk = true;}
      if(ktHSalxKrx == XmylkLuxzV){ShnRSbKDwz = true;}
      while(LpeEOCxtEb == hoihyaZBdN){bmXJScxiCG = true;}
      while(NPdcWtVNPc == NPdcWtVNPc){DKXQonGRDU = true;}
      while(XmylkLuxzV == XmylkLuxzV){BCWVKEiCxE = true;}
      if(xjpBRxFofM == true){xjpBRxFofM = false;}
      if(nbtfhLsGtI == true){nbtfhLsGtI = false;}
      if(NCYyNYqrSD == true){NCYyNYqrSD = false;}
      if(GztiedYbLY == true){GztiedYbLY = false;}
      if(oggDnurSEZ == true){oggDnurSEZ = false;}
      if(SoDpHtKqns == true){SoDpHtKqns = false;}
      if(GMVcGnhLAD == true){GMVcGnhLAD = false;}
      if(lQtUTgVVKR == true){lQtUTgVVKR = false;}
      if(fYmsjQwDbk == true){fYmsjQwDbk = false;}
      if(ShnRSbKDwz == true){ShnRSbKDwz = false;}
      if(NgSAnBthVZ == true){NgSAnBthVZ = false;}
      if(YogVMhYcro == true){YogVMhYcro = false;}
      if(rdjOkEcbBr == true){rdjOkEcbBr = false;}
      if(VRYKEzFlFi == true){VRYKEzFlFi = false;}
      if(WOgBLdAREk == true){WOgBLdAREk = false;}
      if(ChLHHixDPi == true){ChLHHixDPi = false;}
      if(YRfdEHPVRN == true){YRfdEHPVRN = false;}
      if(bmXJScxiCG == true){bmXJScxiCG = false;}
      if(DKXQonGRDU == true){DKXQonGRDU = false;}
      if(BCWVKEiCxE == true){BCWVKEiCxE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKZDBVGZDZ
{ 
  void VljCDsFsYI()
  { 
      bool ucwMdBPTUu = false;
      bool uSyVenbfqX = false;
      bool mzeobSDOxS = false;
      bool TlzBqSPuDm = false;
      bool XmdYNjDIUf = false;
      bool CFnNUwyGkL = false;
      bool xBWCbITwdL = false;
      bool YgbEzAVGbq = false;
      bool OusQQOykfu = false;
      bool UIKroWPbxE = false;
      bool PGeIHVciOT = false;
      bool ZreswBIGkN = false;
      bool KhQhqPWjOb = false;
      bool jsJWaIQjJu = false;
      bool kOVLUccQwn = false;
      bool OJpjthpwQq = false;
      bool ysUmjghIRn = false;
      bool jXwpbuLEMO = false;
      bool mFnaNaDZcs = false;
      bool RTSSwqtibn = false;
      string thaZXQNSHL;
      string ohFzJSQlse;
      string aradrqGNAy;
      string FsqusRuwKl;
      string DmehCfxaiX;
      string ZKAdSCHxgf;
      string JzSIFwpKFr;
      string XUbHanNrbM;
      string tfdbYurNbq;
      string JyOdbEUVbF;
      string plVqAFhsCe;
      string nPVUldUpjK;
      string EchNhYFyfW;
      string SrQVWHJmbT;
      string NyKxDtctqy;
      string iekRBNEHJa;
      string ziNeLuyzye;
      string ThOQwFRkJm;
      string wLHgnnHyUI;
      string DBdATdkekI;
      if(thaZXQNSHL == plVqAFhsCe){ucwMdBPTUu = true;}
      else if(plVqAFhsCe == thaZXQNSHL){PGeIHVciOT = true;}
      if(ohFzJSQlse == nPVUldUpjK){uSyVenbfqX = true;}
      else if(nPVUldUpjK == ohFzJSQlse){ZreswBIGkN = true;}
      if(aradrqGNAy == EchNhYFyfW){mzeobSDOxS = true;}
      else if(EchNhYFyfW == aradrqGNAy){KhQhqPWjOb = true;}
      if(FsqusRuwKl == SrQVWHJmbT){TlzBqSPuDm = true;}
      else if(SrQVWHJmbT == FsqusRuwKl){jsJWaIQjJu = true;}
      if(DmehCfxaiX == NyKxDtctqy){XmdYNjDIUf = true;}
      else if(NyKxDtctqy == DmehCfxaiX){kOVLUccQwn = true;}
      if(ZKAdSCHxgf == iekRBNEHJa){CFnNUwyGkL = true;}
      else if(iekRBNEHJa == ZKAdSCHxgf){OJpjthpwQq = true;}
      if(JzSIFwpKFr == ziNeLuyzye){xBWCbITwdL = true;}
      else if(ziNeLuyzye == JzSIFwpKFr){ysUmjghIRn = true;}
      if(XUbHanNrbM == ThOQwFRkJm){YgbEzAVGbq = true;}
      if(tfdbYurNbq == wLHgnnHyUI){OusQQOykfu = true;}
      if(JyOdbEUVbF == DBdATdkekI){UIKroWPbxE = true;}
      while(ThOQwFRkJm == XUbHanNrbM){jXwpbuLEMO = true;}
      while(wLHgnnHyUI == wLHgnnHyUI){mFnaNaDZcs = true;}
      while(DBdATdkekI == DBdATdkekI){RTSSwqtibn = true;}
      if(ucwMdBPTUu == true){ucwMdBPTUu = false;}
      if(uSyVenbfqX == true){uSyVenbfqX = false;}
      if(mzeobSDOxS == true){mzeobSDOxS = false;}
      if(TlzBqSPuDm == true){TlzBqSPuDm = false;}
      if(XmdYNjDIUf == true){XmdYNjDIUf = false;}
      if(CFnNUwyGkL == true){CFnNUwyGkL = false;}
      if(xBWCbITwdL == true){xBWCbITwdL = false;}
      if(YgbEzAVGbq == true){YgbEzAVGbq = false;}
      if(OusQQOykfu == true){OusQQOykfu = false;}
      if(UIKroWPbxE == true){UIKroWPbxE = false;}
      if(PGeIHVciOT == true){PGeIHVciOT = false;}
      if(ZreswBIGkN == true){ZreswBIGkN = false;}
      if(KhQhqPWjOb == true){KhQhqPWjOb = false;}
      if(jsJWaIQjJu == true){jsJWaIQjJu = false;}
      if(kOVLUccQwn == true){kOVLUccQwn = false;}
      if(OJpjthpwQq == true){OJpjthpwQq = false;}
      if(ysUmjghIRn == true){ysUmjghIRn = false;}
      if(jXwpbuLEMO == true){jXwpbuLEMO = false;}
      if(mFnaNaDZcs == true){mFnaNaDZcs = false;}
      if(RTSSwqtibn == true){RTSSwqtibn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJLTYXROPS
{ 
  void ORgDuRTlGz()
  { 
      bool ssdfsTjrnN = false;
      bool ATtJhVXBWF = false;
      bool uEVjMwgiaB = false;
      bool eOoHGbfNoE = false;
      bool RFygEmxYsW = false;
      bool FaSlUnXtSx = false;
      bool lBRlikdmDF = false;
      bool pKMSnpFneY = false;
      bool zIoDuEwDmR = false;
      bool DltqRPnLyT = false;
      bool JJVmguOAxd = false;
      bool iiOtxdLNqd = false;
      bool oZAkCEPUAX = false;
      bool CspLPomCWz = false;
      bool pwFIhUWAtm = false;
      bool EZUTeiJjkc = false;
      bool fszZbosDdH = false;
      bool qIqqnrTqDh = false;
      bool hOZMSbYVff = false;
      bool fCQsTwwfgs = false;
      string SmIiNFgOPZ;
      string jPQXAAVIib;
      string LykVdzyrPn;
      string nGmifidYnm;
      string eghhRXMpJE;
      string FfuzhTBlFN;
      string GozbkdcgrQ;
      string WwTwxdQDEF;
      string mIiLhIKmBL;
      string hqTafohGwn;
      string ueyrhILzCD;
      string DxgAayGnsc;
      string SoefiecsPH;
      string wKGQKHJpdY;
      string wLjyIjKSzh;
      string itMTUFARIC;
      string fRiuHsqQoT;
      string nPKTfHEgWz;
      string UJshXBxluF;
      string GrhasdboqP;
      if(SmIiNFgOPZ == ueyrhILzCD){ssdfsTjrnN = true;}
      else if(ueyrhILzCD == SmIiNFgOPZ){JJVmguOAxd = true;}
      if(jPQXAAVIib == DxgAayGnsc){ATtJhVXBWF = true;}
      else if(DxgAayGnsc == jPQXAAVIib){iiOtxdLNqd = true;}
      if(LykVdzyrPn == SoefiecsPH){uEVjMwgiaB = true;}
      else if(SoefiecsPH == LykVdzyrPn){oZAkCEPUAX = true;}
      if(nGmifidYnm == wKGQKHJpdY){eOoHGbfNoE = true;}
      else if(wKGQKHJpdY == nGmifidYnm){CspLPomCWz = true;}
      if(eghhRXMpJE == wLjyIjKSzh){RFygEmxYsW = true;}
      else if(wLjyIjKSzh == eghhRXMpJE){pwFIhUWAtm = true;}
      if(FfuzhTBlFN == itMTUFARIC){FaSlUnXtSx = true;}
      else if(itMTUFARIC == FfuzhTBlFN){EZUTeiJjkc = true;}
      if(GozbkdcgrQ == fRiuHsqQoT){lBRlikdmDF = true;}
      else if(fRiuHsqQoT == GozbkdcgrQ){fszZbosDdH = true;}
      if(WwTwxdQDEF == nPKTfHEgWz){pKMSnpFneY = true;}
      if(mIiLhIKmBL == UJshXBxluF){zIoDuEwDmR = true;}
      if(hqTafohGwn == GrhasdboqP){DltqRPnLyT = true;}
      while(nPKTfHEgWz == WwTwxdQDEF){qIqqnrTqDh = true;}
      while(UJshXBxluF == UJshXBxluF){hOZMSbYVff = true;}
      while(GrhasdboqP == GrhasdboqP){fCQsTwwfgs = true;}
      if(ssdfsTjrnN == true){ssdfsTjrnN = false;}
      if(ATtJhVXBWF == true){ATtJhVXBWF = false;}
      if(uEVjMwgiaB == true){uEVjMwgiaB = false;}
      if(eOoHGbfNoE == true){eOoHGbfNoE = false;}
      if(RFygEmxYsW == true){RFygEmxYsW = false;}
      if(FaSlUnXtSx == true){FaSlUnXtSx = false;}
      if(lBRlikdmDF == true){lBRlikdmDF = false;}
      if(pKMSnpFneY == true){pKMSnpFneY = false;}
      if(zIoDuEwDmR == true){zIoDuEwDmR = false;}
      if(DltqRPnLyT == true){DltqRPnLyT = false;}
      if(JJVmguOAxd == true){JJVmguOAxd = false;}
      if(iiOtxdLNqd == true){iiOtxdLNqd = false;}
      if(oZAkCEPUAX == true){oZAkCEPUAX = false;}
      if(CspLPomCWz == true){CspLPomCWz = false;}
      if(pwFIhUWAtm == true){pwFIhUWAtm = false;}
      if(EZUTeiJjkc == true){EZUTeiJjkc = false;}
      if(fszZbosDdH == true){fszZbosDdH = false;}
      if(qIqqnrTqDh == true){qIqqnrTqDh = false;}
      if(hOZMSbYVff == true){hOZMSbYVff = false;}
      if(fCQsTwwfgs == true){fCQsTwwfgs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EONRFPVUDE
{ 
  void pRMeJGfNZT()
  { 
      bool bftsShDcld = false;
      bool mmGFAPCYjB = false;
      bool BUgGxZSlrZ = false;
      bool DXVnJfxzSM = false;
      bool uuJkKLZozX = false;
      bool QRYjTHzmur = false;
      bool OQjLaOQSuT = false;
      bool RDGWGFKuwk = false;
      bool AdmTJkykUC = false;
      bool fKDZxdLyKu = false;
      bool tHseGNLBdN = false;
      bool wEqJrkdQCo = false;
      bool QfysnHzfZb = false;
      bool tMkAqsjINu = false;
      bool ZwHGFbSshL = false;
      bool AtuUdOJAqy = false;
      bool NebBTjTpSz = false;
      bool BVDGOUYqmL = false;
      bool nGyNbzQPVb = false;
      bool jiQOhuUFmV = false;
      string DGgxdHIXed;
      string uxNjKEIXgw;
      string UczpVAoxOH;
      string feTpcsDwJt;
      string HuJkjQOZnC;
      string LpIKNaHpac;
      string RKJXxQcXGQ;
      string BMNmnYSOGE;
      string lPJMupVJbC;
      string lMUfbxkkmS;
      string nqTWBzbUVn;
      string HrjVqCAwcH;
      string tTuEenqgKq;
      string mgbmQtulLw;
      string NAmmusbzoZ;
      string woIeXTuPqM;
      string HtKdAZQwEw;
      string GOkfstgIIl;
      string LrrktyYwPx;
      string zfuznTpIlU;
      if(DGgxdHIXed == nqTWBzbUVn){bftsShDcld = true;}
      else if(nqTWBzbUVn == DGgxdHIXed){tHseGNLBdN = true;}
      if(uxNjKEIXgw == HrjVqCAwcH){mmGFAPCYjB = true;}
      else if(HrjVqCAwcH == uxNjKEIXgw){wEqJrkdQCo = true;}
      if(UczpVAoxOH == tTuEenqgKq){BUgGxZSlrZ = true;}
      else if(tTuEenqgKq == UczpVAoxOH){QfysnHzfZb = true;}
      if(feTpcsDwJt == mgbmQtulLw){DXVnJfxzSM = true;}
      else if(mgbmQtulLw == feTpcsDwJt){tMkAqsjINu = true;}
      if(HuJkjQOZnC == NAmmusbzoZ){uuJkKLZozX = true;}
      else if(NAmmusbzoZ == HuJkjQOZnC){ZwHGFbSshL = true;}
      if(LpIKNaHpac == woIeXTuPqM){QRYjTHzmur = true;}
      else if(woIeXTuPqM == LpIKNaHpac){AtuUdOJAqy = true;}
      if(RKJXxQcXGQ == HtKdAZQwEw){OQjLaOQSuT = true;}
      else if(HtKdAZQwEw == RKJXxQcXGQ){NebBTjTpSz = true;}
      if(BMNmnYSOGE == GOkfstgIIl){RDGWGFKuwk = true;}
      if(lPJMupVJbC == LrrktyYwPx){AdmTJkykUC = true;}
      if(lMUfbxkkmS == zfuznTpIlU){fKDZxdLyKu = true;}
      while(GOkfstgIIl == BMNmnYSOGE){BVDGOUYqmL = true;}
      while(LrrktyYwPx == LrrktyYwPx){nGyNbzQPVb = true;}
      while(zfuznTpIlU == zfuznTpIlU){jiQOhuUFmV = true;}
      if(bftsShDcld == true){bftsShDcld = false;}
      if(mmGFAPCYjB == true){mmGFAPCYjB = false;}
      if(BUgGxZSlrZ == true){BUgGxZSlrZ = false;}
      if(DXVnJfxzSM == true){DXVnJfxzSM = false;}
      if(uuJkKLZozX == true){uuJkKLZozX = false;}
      if(QRYjTHzmur == true){QRYjTHzmur = false;}
      if(OQjLaOQSuT == true){OQjLaOQSuT = false;}
      if(RDGWGFKuwk == true){RDGWGFKuwk = false;}
      if(AdmTJkykUC == true){AdmTJkykUC = false;}
      if(fKDZxdLyKu == true){fKDZxdLyKu = false;}
      if(tHseGNLBdN == true){tHseGNLBdN = false;}
      if(wEqJrkdQCo == true){wEqJrkdQCo = false;}
      if(QfysnHzfZb == true){QfysnHzfZb = false;}
      if(tMkAqsjINu == true){tMkAqsjINu = false;}
      if(ZwHGFbSshL == true){ZwHGFbSshL = false;}
      if(AtuUdOJAqy == true){AtuUdOJAqy = false;}
      if(NebBTjTpSz == true){NebBTjTpSz = false;}
      if(BVDGOUYqmL == true){BVDGOUYqmL = false;}
      if(nGyNbzQPVb == true){nGyNbzQPVb = false;}
      if(jiQOhuUFmV == true){jiQOhuUFmV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWAYEMTPSW
{ 
  void RnYoezEEBt()
  { 
      bool EtUtMcPmDz = false;
      bool LpoSaHzCRz = false;
      bool rouuYYZzoq = false;
      bool jEQOoBAuWR = false;
      bool SgyUUHPMeU = false;
      bool qTFlAPyYVm = false;
      bool DQxLOGYadZ = false;
      bool HDezgLpZaR = false;
      bool JMTUAPzeNY = false;
      bool CaZjNCjmGN = false;
      bool hniFNmoFFo = false;
      bool YXyEdqwbKy = false;
      bool HtMEWfdule = false;
      bool aDTMiUcOHN = false;
      bool asYYzdcUFV = false;
      bool FHbIGmbdhg = false;
      bool ItTZNVEkUI = false;
      bool NhUwWNUmFs = false;
      bool CIoPYSaLGw = false;
      bool szfZFgZzLc = false;
      string kfjSZYAiTk;
      string KTmnCwMeOl;
      string FwRyFFeIsz;
      string BcfGgnnExR;
      string ZuugCmxROl;
      string BcJExnOlMT;
      string srpUjhmfGN;
      string IIhxMKBjuS;
      string HMsGyYTbIs;
      string ZBqcXhFaxU;
      string zQKAdstLqm;
      string mdqtMgyiVL;
      string OLXNnGQFZe;
      string EZmaSpCrcE;
      string dHjUGuKwPp;
      string iVEkFmsxMW;
      string bnkMiNqQbV;
      string dFFRhGbCHs;
      string uUoiuiUCUf;
      string xFfGbpVWls;
      if(kfjSZYAiTk == zQKAdstLqm){EtUtMcPmDz = true;}
      else if(zQKAdstLqm == kfjSZYAiTk){hniFNmoFFo = true;}
      if(KTmnCwMeOl == mdqtMgyiVL){LpoSaHzCRz = true;}
      else if(mdqtMgyiVL == KTmnCwMeOl){YXyEdqwbKy = true;}
      if(FwRyFFeIsz == OLXNnGQFZe){rouuYYZzoq = true;}
      else if(OLXNnGQFZe == FwRyFFeIsz){HtMEWfdule = true;}
      if(BcfGgnnExR == EZmaSpCrcE){jEQOoBAuWR = true;}
      else if(EZmaSpCrcE == BcfGgnnExR){aDTMiUcOHN = true;}
      if(ZuugCmxROl == dHjUGuKwPp){SgyUUHPMeU = true;}
      else if(dHjUGuKwPp == ZuugCmxROl){asYYzdcUFV = true;}
      if(BcJExnOlMT == iVEkFmsxMW){qTFlAPyYVm = true;}
      else if(iVEkFmsxMW == BcJExnOlMT){FHbIGmbdhg = true;}
      if(srpUjhmfGN == bnkMiNqQbV){DQxLOGYadZ = true;}
      else if(bnkMiNqQbV == srpUjhmfGN){ItTZNVEkUI = true;}
      if(IIhxMKBjuS == dFFRhGbCHs){HDezgLpZaR = true;}
      if(HMsGyYTbIs == uUoiuiUCUf){JMTUAPzeNY = true;}
      if(ZBqcXhFaxU == xFfGbpVWls){CaZjNCjmGN = true;}
      while(dFFRhGbCHs == IIhxMKBjuS){NhUwWNUmFs = true;}
      while(uUoiuiUCUf == uUoiuiUCUf){CIoPYSaLGw = true;}
      while(xFfGbpVWls == xFfGbpVWls){szfZFgZzLc = true;}
      if(EtUtMcPmDz == true){EtUtMcPmDz = false;}
      if(LpoSaHzCRz == true){LpoSaHzCRz = false;}
      if(rouuYYZzoq == true){rouuYYZzoq = false;}
      if(jEQOoBAuWR == true){jEQOoBAuWR = false;}
      if(SgyUUHPMeU == true){SgyUUHPMeU = false;}
      if(qTFlAPyYVm == true){qTFlAPyYVm = false;}
      if(DQxLOGYadZ == true){DQxLOGYadZ = false;}
      if(HDezgLpZaR == true){HDezgLpZaR = false;}
      if(JMTUAPzeNY == true){JMTUAPzeNY = false;}
      if(CaZjNCjmGN == true){CaZjNCjmGN = false;}
      if(hniFNmoFFo == true){hniFNmoFFo = false;}
      if(YXyEdqwbKy == true){YXyEdqwbKy = false;}
      if(HtMEWfdule == true){HtMEWfdule = false;}
      if(aDTMiUcOHN == true){aDTMiUcOHN = false;}
      if(asYYzdcUFV == true){asYYzdcUFV = false;}
      if(FHbIGmbdhg == true){FHbIGmbdhg = false;}
      if(ItTZNVEkUI == true){ItTZNVEkUI = false;}
      if(NhUwWNUmFs == true){NhUwWNUmFs = false;}
      if(CIoPYSaLGw == true){CIoPYSaLGw = false;}
      if(szfZFgZzLc == true){szfZFgZzLc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXCKBSABAI
{ 
  void oKjgxzWEYa()
  { 
      bool DOljQSQXfX = false;
      bool RWVmlBNuzE = false;
      bool UXnnYMzMQb = false;
      bool VJAhJlmCRP = false;
      bool CyKJrocwyW = false;
      bool ikcWeeayKD = false;
      bool SDGEBIWncA = false;
      bool NKciBWNdui = false;
      bool jDOsrjfdCe = false;
      bool KoqNxyqGHj = false;
      bool SnSxIXHtUI = false;
      bool QwCbTOoNLR = false;
      bool bslyoYTPlC = false;
      bool fHWLQujQkU = false;
      bool blIsNOlPth = false;
      bool JctpHYCUHj = false;
      bool ErIScJZpKY = false;
      bool eXcqopjrja = false;
      bool lEUDsCMfEq = false;
      bool rPJBQidpQD = false;
      string GAJVSxfprJ;
      string uXEKShiXsA;
      string VATmrlAAWX;
      string jmxaVKibyp;
      string xETytaCSmX;
      string pgpUWFgVdf;
      string xeTUYIZdoI;
      string yGZDCRgVsQ;
      string jgNyhDwcDP;
      string cMxRrSjzZl;
      string BYdeZiHmRF;
      string YKcNwPRVmU;
      string LxZYekIHKj;
      string ghuHOLDhYy;
      string wJKyqRjjUc;
      string BNLEZEyEzn;
      string ZzchXpOUyk;
      string MixnYClahM;
      string BYlhiTVqgK;
      string MzijXwfcaA;
      if(GAJVSxfprJ == BYdeZiHmRF){DOljQSQXfX = true;}
      else if(BYdeZiHmRF == GAJVSxfprJ){SnSxIXHtUI = true;}
      if(uXEKShiXsA == YKcNwPRVmU){RWVmlBNuzE = true;}
      else if(YKcNwPRVmU == uXEKShiXsA){QwCbTOoNLR = true;}
      if(VATmrlAAWX == LxZYekIHKj){UXnnYMzMQb = true;}
      else if(LxZYekIHKj == VATmrlAAWX){bslyoYTPlC = true;}
      if(jmxaVKibyp == ghuHOLDhYy){VJAhJlmCRP = true;}
      else if(ghuHOLDhYy == jmxaVKibyp){fHWLQujQkU = true;}
      if(xETytaCSmX == wJKyqRjjUc){CyKJrocwyW = true;}
      else if(wJKyqRjjUc == xETytaCSmX){blIsNOlPth = true;}
      if(pgpUWFgVdf == BNLEZEyEzn){ikcWeeayKD = true;}
      else if(BNLEZEyEzn == pgpUWFgVdf){JctpHYCUHj = true;}
      if(xeTUYIZdoI == ZzchXpOUyk){SDGEBIWncA = true;}
      else if(ZzchXpOUyk == xeTUYIZdoI){ErIScJZpKY = true;}
      if(yGZDCRgVsQ == MixnYClahM){NKciBWNdui = true;}
      if(jgNyhDwcDP == BYlhiTVqgK){jDOsrjfdCe = true;}
      if(cMxRrSjzZl == MzijXwfcaA){KoqNxyqGHj = true;}
      while(MixnYClahM == yGZDCRgVsQ){eXcqopjrja = true;}
      while(BYlhiTVqgK == BYlhiTVqgK){lEUDsCMfEq = true;}
      while(MzijXwfcaA == MzijXwfcaA){rPJBQidpQD = true;}
      if(DOljQSQXfX == true){DOljQSQXfX = false;}
      if(RWVmlBNuzE == true){RWVmlBNuzE = false;}
      if(UXnnYMzMQb == true){UXnnYMzMQb = false;}
      if(VJAhJlmCRP == true){VJAhJlmCRP = false;}
      if(CyKJrocwyW == true){CyKJrocwyW = false;}
      if(ikcWeeayKD == true){ikcWeeayKD = false;}
      if(SDGEBIWncA == true){SDGEBIWncA = false;}
      if(NKciBWNdui == true){NKciBWNdui = false;}
      if(jDOsrjfdCe == true){jDOsrjfdCe = false;}
      if(KoqNxyqGHj == true){KoqNxyqGHj = false;}
      if(SnSxIXHtUI == true){SnSxIXHtUI = false;}
      if(QwCbTOoNLR == true){QwCbTOoNLR = false;}
      if(bslyoYTPlC == true){bslyoYTPlC = false;}
      if(fHWLQujQkU == true){fHWLQujQkU = false;}
      if(blIsNOlPth == true){blIsNOlPth = false;}
      if(JctpHYCUHj == true){JctpHYCUHj = false;}
      if(ErIScJZpKY == true){ErIScJZpKY = false;}
      if(eXcqopjrja == true){eXcqopjrja = false;}
      if(lEUDsCMfEq == true){lEUDsCMfEq = false;}
      if(rPJBQidpQD == true){rPJBQidpQD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BINHUIPYJH
{ 
  void HhZKayKFeE()
  { 
      bool bqbLCpdDWq = false;
      bool BKgzKMAVQT = false;
      bool WUeXbledOx = false;
      bool ymPugicife = false;
      bool EDdtVUdQzJ = false;
      bool euDiyGLDiQ = false;
      bool KAnYsNulSa = false;
      bool jRplOTqjCG = false;
      bool HNdFRCifxZ = false;
      bool WYzPTDPEBH = false;
      bool ZryXZNFRTe = false;
      bool PaBcIwWhGp = false;
      bool eOnrEKSaRK = false;
      bool DlitgPPGfE = false;
      bool xRLSKuWVGW = false;
      bool ggyKbKDGTO = false;
      bool tdzIacrGwr = false;
      bool gPCBrNDUgI = false;
      bool nwTtdWnXSV = false;
      bool LIlQJSRCrh = false;
      string bfaLqNieHe;
      string kLIGWOtReX;
      string AnCdjJgbhx;
      string pnAUPxOXTn;
      string MyZuqhsHnT;
      string PGdCHncxbh;
      string gHxJowKmqZ;
      string AWypLCNGmC;
      string PZmOhjKxMa;
      string TRukHFAQFt;
      string WFPOSsImqF;
      string aVJZRHTiaF;
      string lNaQGhaMhF;
      string BwAseKJYuo;
      string aWFHzxHVSz;
      string kRoAHIdyIk;
      string RuEkDdVQtH;
      string xumldPHTQI;
      string ZEthUiGAkW;
      string fLQJWfRUDV;
      if(bfaLqNieHe == WFPOSsImqF){bqbLCpdDWq = true;}
      else if(WFPOSsImqF == bfaLqNieHe){ZryXZNFRTe = true;}
      if(kLIGWOtReX == aVJZRHTiaF){BKgzKMAVQT = true;}
      else if(aVJZRHTiaF == kLIGWOtReX){PaBcIwWhGp = true;}
      if(AnCdjJgbhx == lNaQGhaMhF){WUeXbledOx = true;}
      else if(lNaQGhaMhF == AnCdjJgbhx){eOnrEKSaRK = true;}
      if(pnAUPxOXTn == BwAseKJYuo){ymPugicife = true;}
      else if(BwAseKJYuo == pnAUPxOXTn){DlitgPPGfE = true;}
      if(MyZuqhsHnT == aWFHzxHVSz){EDdtVUdQzJ = true;}
      else if(aWFHzxHVSz == MyZuqhsHnT){xRLSKuWVGW = true;}
      if(PGdCHncxbh == kRoAHIdyIk){euDiyGLDiQ = true;}
      else if(kRoAHIdyIk == PGdCHncxbh){ggyKbKDGTO = true;}
      if(gHxJowKmqZ == RuEkDdVQtH){KAnYsNulSa = true;}
      else if(RuEkDdVQtH == gHxJowKmqZ){tdzIacrGwr = true;}
      if(AWypLCNGmC == xumldPHTQI){jRplOTqjCG = true;}
      if(PZmOhjKxMa == ZEthUiGAkW){HNdFRCifxZ = true;}
      if(TRukHFAQFt == fLQJWfRUDV){WYzPTDPEBH = true;}
      while(xumldPHTQI == AWypLCNGmC){gPCBrNDUgI = true;}
      while(ZEthUiGAkW == ZEthUiGAkW){nwTtdWnXSV = true;}
      while(fLQJWfRUDV == fLQJWfRUDV){LIlQJSRCrh = true;}
      if(bqbLCpdDWq == true){bqbLCpdDWq = false;}
      if(BKgzKMAVQT == true){BKgzKMAVQT = false;}
      if(WUeXbledOx == true){WUeXbledOx = false;}
      if(ymPugicife == true){ymPugicife = false;}
      if(EDdtVUdQzJ == true){EDdtVUdQzJ = false;}
      if(euDiyGLDiQ == true){euDiyGLDiQ = false;}
      if(KAnYsNulSa == true){KAnYsNulSa = false;}
      if(jRplOTqjCG == true){jRplOTqjCG = false;}
      if(HNdFRCifxZ == true){HNdFRCifxZ = false;}
      if(WYzPTDPEBH == true){WYzPTDPEBH = false;}
      if(ZryXZNFRTe == true){ZryXZNFRTe = false;}
      if(PaBcIwWhGp == true){PaBcIwWhGp = false;}
      if(eOnrEKSaRK == true){eOnrEKSaRK = false;}
      if(DlitgPPGfE == true){DlitgPPGfE = false;}
      if(xRLSKuWVGW == true){xRLSKuWVGW = false;}
      if(ggyKbKDGTO == true){ggyKbKDGTO = false;}
      if(tdzIacrGwr == true){tdzIacrGwr = false;}
      if(gPCBrNDUgI == true){gPCBrNDUgI = false;}
      if(nwTtdWnXSV == true){nwTtdWnXSV = false;}
      if(LIlQJSRCrh == true){LIlQJSRCrh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCVYXQINMV
{ 
  void MrNGyVRBgH()
  { 
      bool wUKBFEyOIe = false;
      bool qWJcifQusk = false;
      bool hYKwoIjqew = false;
      bool WBxxYfFsSi = false;
      bool szNMXPRjRl = false;
      bool cnGdEXKNLw = false;
      bool THiMIoYLEC = false;
      bool ZWbJqiKxYY = false;
      bool qAYsShtTsB = false;
      bool UrhWOlPBEh = false;
      bool qFfOLFLwmU = false;
      bool MNolFThpsa = false;
      bool uFSDhhoFtE = false;
      bool TJrqhkTKgM = false;
      bool VyfXnHDuQu = false;
      bool EZHdmkmcgd = false;
      bool PGBhBDUyEU = false;
      bool zWIfEwYtOZ = false;
      bool etnzAtBOEw = false;
      bool xqdDxPwyVk = false;
      string ATdlUCyxLB;
      string TYfxLtEhkI;
      string nfnTqLRLdC;
      string TYlTYnPgjd;
      string BlharLAjkl;
      string FgmfOUeJuI;
      string klTJhumLXX;
      string dXyGGByNbe;
      string LgaqxmkFFE;
      string JFlasPSYrw;
      string YoMNHhhgYM;
      string VQhQxELbMt;
      string KgFSNYkWNq;
      string iZUeFVUMjO;
      string EDgsirXUco;
      string DpLylqiszi;
      string wKTgdwuCKb;
      string jyrxoGAMjV;
      string AQtXnrNWrO;
      string laNARsjzPm;
      if(ATdlUCyxLB == YoMNHhhgYM){wUKBFEyOIe = true;}
      else if(YoMNHhhgYM == ATdlUCyxLB){qFfOLFLwmU = true;}
      if(TYfxLtEhkI == VQhQxELbMt){qWJcifQusk = true;}
      else if(VQhQxELbMt == TYfxLtEhkI){MNolFThpsa = true;}
      if(nfnTqLRLdC == KgFSNYkWNq){hYKwoIjqew = true;}
      else if(KgFSNYkWNq == nfnTqLRLdC){uFSDhhoFtE = true;}
      if(TYlTYnPgjd == iZUeFVUMjO){WBxxYfFsSi = true;}
      else if(iZUeFVUMjO == TYlTYnPgjd){TJrqhkTKgM = true;}
      if(BlharLAjkl == EDgsirXUco){szNMXPRjRl = true;}
      else if(EDgsirXUco == BlharLAjkl){VyfXnHDuQu = true;}
      if(FgmfOUeJuI == DpLylqiszi){cnGdEXKNLw = true;}
      else if(DpLylqiszi == FgmfOUeJuI){EZHdmkmcgd = true;}
      if(klTJhumLXX == wKTgdwuCKb){THiMIoYLEC = true;}
      else if(wKTgdwuCKb == klTJhumLXX){PGBhBDUyEU = true;}
      if(dXyGGByNbe == jyrxoGAMjV){ZWbJqiKxYY = true;}
      if(LgaqxmkFFE == AQtXnrNWrO){qAYsShtTsB = true;}
      if(JFlasPSYrw == laNARsjzPm){UrhWOlPBEh = true;}
      while(jyrxoGAMjV == dXyGGByNbe){zWIfEwYtOZ = true;}
      while(AQtXnrNWrO == AQtXnrNWrO){etnzAtBOEw = true;}
      while(laNARsjzPm == laNARsjzPm){xqdDxPwyVk = true;}
      if(wUKBFEyOIe == true){wUKBFEyOIe = false;}
      if(qWJcifQusk == true){qWJcifQusk = false;}
      if(hYKwoIjqew == true){hYKwoIjqew = false;}
      if(WBxxYfFsSi == true){WBxxYfFsSi = false;}
      if(szNMXPRjRl == true){szNMXPRjRl = false;}
      if(cnGdEXKNLw == true){cnGdEXKNLw = false;}
      if(THiMIoYLEC == true){THiMIoYLEC = false;}
      if(ZWbJqiKxYY == true){ZWbJqiKxYY = false;}
      if(qAYsShtTsB == true){qAYsShtTsB = false;}
      if(UrhWOlPBEh == true){UrhWOlPBEh = false;}
      if(qFfOLFLwmU == true){qFfOLFLwmU = false;}
      if(MNolFThpsa == true){MNolFThpsa = false;}
      if(uFSDhhoFtE == true){uFSDhhoFtE = false;}
      if(TJrqhkTKgM == true){TJrqhkTKgM = false;}
      if(VyfXnHDuQu == true){VyfXnHDuQu = false;}
      if(EZHdmkmcgd == true){EZHdmkmcgd = false;}
      if(PGBhBDUyEU == true){PGBhBDUyEU = false;}
      if(zWIfEwYtOZ == true){zWIfEwYtOZ = false;}
      if(etnzAtBOEw == true){etnzAtBOEw = false;}
      if(xqdDxPwyVk == true){xqdDxPwyVk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASECLSBJXM
{ 
  void MyyhxlsOtk()
  { 
      bool RQIGkONwHW = false;
      bool ntnyJHPuRY = false;
      bool nbrEKeuhjV = false;
      bool GikkzYoXUb = false;
      bool aKEyORWiVM = false;
      bool hYRVNoYEwG = false;
      bool SfLkQEICyk = false;
      bool SqZpxdXtos = false;
      bool HMMXmgQOXJ = false;
      bool zjbOIuySgJ = false;
      bool IUjjspzbXj = false;
      bool ReOCyGSmyi = false;
      bool mseokhOKhC = false;
      bool eEMfkmbbdx = false;
      bool goqmrTUZQB = false;
      bool bLUyVOpuzL = false;
      bool antUEMSiRL = false;
      bool eqIBCyCqxR = false;
      bool NotfaTjOJV = false;
      bool xgcSVsuVie = false;
      string YXBBAakfhJ;
      string iYcXlaiqVb;
      string plXKAqxbrL;
      string yebAmhzjuh;
      string aGAyySqxru;
      string SAXqNmApAI;
      string cJnWKDxbkE;
      string byunAikZLg;
      string AzjwsyGjmz;
      string gIjlFRSdmt;
      string VOMmSTEjqd;
      string CaeSIcZqcM;
      string xMokXTOJhh;
      string QHlRLkmwdY;
      string sVsIxGdQdb;
      string raAaxIZbPz;
      string FuBINunMHW;
      string pcMETaTfnQ;
      string oyeGpoGLUD;
      string LKgeTxUjtC;
      if(YXBBAakfhJ == VOMmSTEjqd){RQIGkONwHW = true;}
      else if(VOMmSTEjqd == YXBBAakfhJ){IUjjspzbXj = true;}
      if(iYcXlaiqVb == CaeSIcZqcM){ntnyJHPuRY = true;}
      else if(CaeSIcZqcM == iYcXlaiqVb){ReOCyGSmyi = true;}
      if(plXKAqxbrL == xMokXTOJhh){nbrEKeuhjV = true;}
      else if(xMokXTOJhh == plXKAqxbrL){mseokhOKhC = true;}
      if(yebAmhzjuh == QHlRLkmwdY){GikkzYoXUb = true;}
      else if(QHlRLkmwdY == yebAmhzjuh){eEMfkmbbdx = true;}
      if(aGAyySqxru == sVsIxGdQdb){aKEyORWiVM = true;}
      else if(sVsIxGdQdb == aGAyySqxru){goqmrTUZQB = true;}
      if(SAXqNmApAI == raAaxIZbPz){hYRVNoYEwG = true;}
      else if(raAaxIZbPz == SAXqNmApAI){bLUyVOpuzL = true;}
      if(cJnWKDxbkE == FuBINunMHW){SfLkQEICyk = true;}
      else if(FuBINunMHW == cJnWKDxbkE){antUEMSiRL = true;}
      if(byunAikZLg == pcMETaTfnQ){SqZpxdXtos = true;}
      if(AzjwsyGjmz == oyeGpoGLUD){HMMXmgQOXJ = true;}
      if(gIjlFRSdmt == LKgeTxUjtC){zjbOIuySgJ = true;}
      while(pcMETaTfnQ == byunAikZLg){eqIBCyCqxR = true;}
      while(oyeGpoGLUD == oyeGpoGLUD){NotfaTjOJV = true;}
      while(LKgeTxUjtC == LKgeTxUjtC){xgcSVsuVie = true;}
      if(RQIGkONwHW == true){RQIGkONwHW = false;}
      if(ntnyJHPuRY == true){ntnyJHPuRY = false;}
      if(nbrEKeuhjV == true){nbrEKeuhjV = false;}
      if(GikkzYoXUb == true){GikkzYoXUb = false;}
      if(aKEyORWiVM == true){aKEyORWiVM = false;}
      if(hYRVNoYEwG == true){hYRVNoYEwG = false;}
      if(SfLkQEICyk == true){SfLkQEICyk = false;}
      if(SqZpxdXtos == true){SqZpxdXtos = false;}
      if(HMMXmgQOXJ == true){HMMXmgQOXJ = false;}
      if(zjbOIuySgJ == true){zjbOIuySgJ = false;}
      if(IUjjspzbXj == true){IUjjspzbXj = false;}
      if(ReOCyGSmyi == true){ReOCyGSmyi = false;}
      if(mseokhOKhC == true){mseokhOKhC = false;}
      if(eEMfkmbbdx == true){eEMfkmbbdx = false;}
      if(goqmrTUZQB == true){goqmrTUZQB = false;}
      if(bLUyVOpuzL == true){bLUyVOpuzL = false;}
      if(antUEMSiRL == true){antUEMSiRL = false;}
      if(eqIBCyCqxR == true){eqIBCyCqxR = false;}
      if(NotfaTjOJV == true){NotfaTjOJV = false;}
      if(xgcSVsuVie == true){xgcSVsuVie = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSLNTVNNYL
{ 
  void MWfAUhRMmY()
  { 
      bool gZUsQzuMeL = false;
      bool RuVdJdxiez = false;
      bool dYtKPCkOrY = false;
      bool FcDnSxbkXh = false;
      bool ZaASVekSkr = false;
      bool kVpgjHeJcO = false;
      bool OgTFFnqgLL = false;
      bool BLLwYDYbok = false;
      bool QScAnjlWEK = false;
      bool RRIITsGtNg = false;
      bool mEGYpYKtHf = false;
      bool iDTrxuDTQU = false;
      bool BUcBsjDCce = false;
      bool wdNIyMLEJO = false;
      bool YrOXaOxQLX = false;
      bool plcreSaFfG = false;
      bool UIQcjFpLtj = false;
      bool jzKCuJFEZe = false;
      bool lmpEoKAUce = false;
      bool kFYCsQalnV = false;
      string bxLznVpAPP;
      string slgtoJKygt;
      string RqDZtTqriP;
      string rosByzLZBx;
      string nEneOrwDDC;
      string bnXhGktkEU;
      string eyQAXEsewp;
      string xkwiFNDYKC;
      string WnofnDQKtN;
      string FZUgSpnnGJ;
      string yQHNEprnbs;
      string gUZCxqIjLT;
      string mhkhjXPOQP;
      string YPRADGfabx;
      string LciAfjzSjb;
      string gDbmVQfYdg;
      string acXMURDYyp;
      string KhIOIKzjCz;
      string XweohUmeem;
      string aHxtViEVfN;
      if(bxLznVpAPP == yQHNEprnbs){gZUsQzuMeL = true;}
      else if(yQHNEprnbs == bxLznVpAPP){mEGYpYKtHf = true;}
      if(slgtoJKygt == gUZCxqIjLT){RuVdJdxiez = true;}
      else if(gUZCxqIjLT == slgtoJKygt){iDTrxuDTQU = true;}
      if(RqDZtTqriP == mhkhjXPOQP){dYtKPCkOrY = true;}
      else if(mhkhjXPOQP == RqDZtTqriP){BUcBsjDCce = true;}
      if(rosByzLZBx == YPRADGfabx){FcDnSxbkXh = true;}
      else if(YPRADGfabx == rosByzLZBx){wdNIyMLEJO = true;}
      if(nEneOrwDDC == LciAfjzSjb){ZaASVekSkr = true;}
      else if(LciAfjzSjb == nEneOrwDDC){YrOXaOxQLX = true;}
      if(bnXhGktkEU == gDbmVQfYdg){kVpgjHeJcO = true;}
      else if(gDbmVQfYdg == bnXhGktkEU){plcreSaFfG = true;}
      if(eyQAXEsewp == acXMURDYyp){OgTFFnqgLL = true;}
      else if(acXMURDYyp == eyQAXEsewp){UIQcjFpLtj = true;}
      if(xkwiFNDYKC == KhIOIKzjCz){BLLwYDYbok = true;}
      if(WnofnDQKtN == XweohUmeem){QScAnjlWEK = true;}
      if(FZUgSpnnGJ == aHxtViEVfN){RRIITsGtNg = true;}
      while(KhIOIKzjCz == xkwiFNDYKC){jzKCuJFEZe = true;}
      while(XweohUmeem == XweohUmeem){lmpEoKAUce = true;}
      while(aHxtViEVfN == aHxtViEVfN){kFYCsQalnV = true;}
      if(gZUsQzuMeL == true){gZUsQzuMeL = false;}
      if(RuVdJdxiez == true){RuVdJdxiez = false;}
      if(dYtKPCkOrY == true){dYtKPCkOrY = false;}
      if(FcDnSxbkXh == true){FcDnSxbkXh = false;}
      if(ZaASVekSkr == true){ZaASVekSkr = false;}
      if(kVpgjHeJcO == true){kVpgjHeJcO = false;}
      if(OgTFFnqgLL == true){OgTFFnqgLL = false;}
      if(BLLwYDYbok == true){BLLwYDYbok = false;}
      if(QScAnjlWEK == true){QScAnjlWEK = false;}
      if(RRIITsGtNg == true){RRIITsGtNg = false;}
      if(mEGYpYKtHf == true){mEGYpYKtHf = false;}
      if(iDTrxuDTQU == true){iDTrxuDTQU = false;}
      if(BUcBsjDCce == true){BUcBsjDCce = false;}
      if(wdNIyMLEJO == true){wdNIyMLEJO = false;}
      if(YrOXaOxQLX == true){YrOXaOxQLX = false;}
      if(plcreSaFfG == true){plcreSaFfG = false;}
      if(UIQcjFpLtj == true){UIQcjFpLtj = false;}
      if(jzKCuJFEZe == true){jzKCuJFEZe = false;}
      if(lmpEoKAUce == true){lmpEoKAUce = false;}
      if(kFYCsQalnV == true){kFYCsQalnV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFASUHWKGG
{ 
  void rZBmhHnDSa()
  { 
      bool XmQJcyaPBz = false;
      bool xRydWRzUMT = false;
      bool URNAtZVlyY = false;
      bool VXTWRuqnwl = false;
      bool RSAqOSMxFL = false;
      bool GUFxHGYQPD = false;
      bool coRcdZyaMb = false;
      bool ZKXZBBQWka = false;
      bool MYflRBRVPK = false;
      bool VaYsJcBWNo = false;
      bool UljdkwweuF = false;
      bool pCfoqEIeLb = false;
      bool HbLCFzleQY = false;
      bool AsIuGanBBV = false;
      bool EmaKUTuiCF = false;
      bool UVLkgsahYl = false;
      bool JROWEwsjiQ = false;
      bool PGdpXUAAgk = false;
      bool ECcKDdhXNM = false;
      bool zFcOLmXEFY = false;
      string mtzrlbQYBs;
      string TylSdnVXjy;
      string SOphnOyaPF;
      string UCwufAPtdl;
      string cwSpYuJNeD;
      string negATYEQEX;
      string doIwYRBqld;
      string YbsxVWuAJr;
      string FjwLQoUubH;
      string wzoGInmVQH;
      string sRbBeMkjew;
      string cDGLRsrwei;
      string wFPdgZlmog;
      string iYjBzmIugD;
      string EkQeerrcnO;
      string wpqgKmCxTE;
      string ayuyNDTEMe;
      string kxOaeLokzo;
      string hIyZkshCqM;
      string jLaccGoRQb;
      if(mtzrlbQYBs == sRbBeMkjew){XmQJcyaPBz = true;}
      else if(sRbBeMkjew == mtzrlbQYBs){UljdkwweuF = true;}
      if(TylSdnVXjy == cDGLRsrwei){xRydWRzUMT = true;}
      else if(cDGLRsrwei == TylSdnVXjy){pCfoqEIeLb = true;}
      if(SOphnOyaPF == wFPdgZlmog){URNAtZVlyY = true;}
      else if(wFPdgZlmog == SOphnOyaPF){HbLCFzleQY = true;}
      if(UCwufAPtdl == iYjBzmIugD){VXTWRuqnwl = true;}
      else if(iYjBzmIugD == UCwufAPtdl){AsIuGanBBV = true;}
      if(cwSpYuJNeD == EkQeerrcnO){RSAqOSMxFL = true;}
      else if(EkQeerrcnO == cwSpYuJNeD){EmaKUTuiCF = true;}
      if(negATYEQEX == wpqgKmCxTE){GUFxHGYQPD = true;}
      else if(wpqgKmCxTE == negATYEQEX){UVLkgsahYl = true;}
      if(doIwYRBqld == ayuyNDTEMe){coRcdZyaMb = true;}
      else if(ayuyNDTEMe == doIwYRBqld){JROWEwsjiQ = true;}
      if(YbsxVWuAJr == kxOaeLokzo){ZKXZBBQWka = true;}
      if(FjwLQoUubH == hIyZkshCqM){MYflRBRVPK = true;}
      if(wzoGInmVQH == jLaccGoRQb){VaYsJcBWNo = true;}
      while(kxOaeLokzo == YbsxVWuAJr){PGdpXUAAgk = true;}
      while(hIyZkshCqM == hIyZkshCqM){ECcKDdhXNM = true;}
      while(jLaccGoRQb == jLaccGoRQb){zFcOLmXEFY = true;}
      if(XmQJcyaPBz == true){XmQJcyaPBz = false;}
      if(xRydWRzUMT == true){xRydWRzUMT = false;}
      if(URNAtZVlyY == true){URNAtZVlyY = false;}
      if(VXTWRuqnwl == true){VXTWRuqnwl = false;}
      if(RSAqOSMxFL == true){RSAqOSMxFL = false;}
      if(GUFxHGYQPD == true){GUFxHGYQPD = false;}
      if(coRcdZyaMb == true){coRcdZyaMb = false;}
      if(ZKXZBBQWka == true){ZKXZBBQWka = false;}
      if(MYflRBRVPK == true){MYflRBRVPK = false;}
      if(VaYsJcBWNo == true){VaYsJcBWNo = false;}
      if(UljdkwweuF == true){UljdkwweuF = false;}
      if(pCfoqEIeLb == true){pCfoqEIeLb = false;}
      if(HbLCFzleQY == true){HbLCFzleQY = false;}
      if(AsIuGanBBV == true){AsIuGanBBV = false;}
      if(EmaKUTuiCF == true){EmaKUTuiCF = false;}
      if(UVLkgsahYl == true){UVLkgsahYl = false;}
      if(JROWEwsjiQ == true){JROWEwsjiQ = false;}
      if(PGdpXUAAgk == true){PGdpXUAAgk = false;}
      if(ECcKDdhXNM == true){ECcKDdhXNM = false;}
      if(zFcOLmXEFY == true){zFcOLmXEFY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKOVIXUCRE
{ 
  void hHNHIiyIlF()
  { 
      bool LuPGpiQwso = false;
      bool OEoMgcAutQ = false;
      bool gTJBpLxxCy = false;
      bool KwAWXOzRGc = false;
      bool ykluoStuBl = false;
      bool TyVXzqkNPd = false;
      bool lTtueRERnS = false;
      bool dhnQRwhOLX = false;
      bool RBuPeMZcXg = false;
      bool clCbpeppQX = false;
      bool NbGhIkJEFD = false;
      bool JWCrMjXdPR = false;
      bool rbtHprfMam = false;
      bool FqxnKouMHt = false;
      bool DUXTWFiKOF = false;
      bool GMZyelhyrQ = false;
      bool EwdSyRYOgX = false;
      bool oKWVOWDZkj = false;
      bool IVxUfrQyIX = false;
      bool HwUpoGqEVE = false;
      string dYagyytnQy;
      string YzrxIKSsmI;
      string kkPrJxJlSE;
      string YZmUwLxcAw;
      string HWAygVbqoD;
      string SLPIGsIiXA;
      string oHUMZzMXBx;
      string MospBNjQLn;
      string VRxPlMKdND;
      string CNFzHzCnYg;
      string IEprpcSZHr;
      string JqXjeWKFZM;
      string nhJxuzjshB;
      string LurdeRbFZI;
      string tkVUtKoUUk;
      string owNMsatrwq;
      string rZqGfNztFN;
      string uFfRSDLoDj;
      string JPYwMPgfjE;
      string WiIiPTsPnf;
      if(dYagyytnQy == IEprpcSZHr){LuPGpiQwso = true;}
      else if(IEprpcSZHr == dYagyytnQy){NbGhIkJEFD = true;}
      if(YzrxIKSsmI == JqXjeWKFZM){OEoMgcAutQ = true;}
      else if(JqXjeWKFZM == YzrxIKSsmI){JWCrMjXdPR = true;}
      if(kkPrJxJlSE == nhJxuzjshB){gTJBpLxxCy = true;}
      else if(nhJxuzjshB == kkPrJxJlSE){rbtHprfMam = true;}
      if(YZmUwLxcAw == LurdeRbFZI){KwAWXOzRGc = true;}
      else if(LurdeRbFZI == YZmUwLxcAw){FqxnKouMHt = true;}
      if(HWAygVbqoD == tkVUtKoUUk){ykluoStuBl = true;}
      else if(tkVUtKoUUk == HWAygVbqoD){DUXTWFiKOF = true;}
      if(SLPIGsIiXA == owNMsatrwq){TyVXzqkNPd = true;}
      else if(owNMsatrwq == SLPIGsIiXA){GMZyelhyrQ = true;}
      if(oHUMZzMXBx == rZqGfNztFN){lTtueRERnS = true;}
      else if(rZqGfNztFN == oHUMZzMXBx){EwdSyRYOgX = true;}
      if(MospBNjQLn == uFfRSDLoDj){dhnQRwhOLX = true;}
      if(VRxPlMKdND == JPYwMPgfjE){RBuPeMZcXg = true;}
      if(CNFzHzCnYg == WiIiPTsPnf){clCbpeppQX = true;}
      while(uFfRSDLoDj == MospBNjQLn){oKWVOWDZkj = true;}
      while(JPYwMPgfjE == JPYwMPgfjE){IVxUfrQyIX = true;}
      while(WiIiPTsPnf == WiIiPTsPnf){HwUpoGqEVE = true;}
      if(LuPGpiQwso == true){LuPGpiQwso = false;}
      if(OEoMgcAutQ == true){OEoMgcAutQ = false;}
      if(gTJBpLxxCy == true){gTJBpLxxCy = false;}
      if(KwAWXOzRGc == true){KwAWXOzRGc = false;}
      if(ykluoStuBl == true){ykluoStuBl = false;}
      if(TyVXzqkNPd == true){TyVXzqkNPd = false;}
      if(lTtueRERnS == true){lTtueRERnS = false;}
      if(dhnQRwhOLX == true){dhnQRwhOLX = false;}
      if(RBuPeMZcXg == true){RBuPeMZcXg = false;}
      if(clCbpeppQX == true){clCbpeppQX = false;}
      if(NbGhIkJEFD == true){NbGhIkJEFD = false;}
      if(JWCrMjXdPR == true){JWCrMjXdPR = false;}
      if(rbtHprfMam == true){rbtHprfMam = false;}
      if(FqxnKouMHt == true){FqxnKouMHt = false;}
      if(DUXTWFiKOF == true){DUXTWFiKOF = false;}
      if(GMZyelhyrQ == true){GMZyelhyrQ = false;}
      if(EwdSyRYOgX == true){EwdSyRYOgX = false;}
      if(oKWVOWDZkj == true){oKWVOWDZkj = false;}
      if(IVxUfrQyIX == true){IVxUfrQyIX = false;}
      if(HwUpoGqEVE == true){HwUpoGqEVE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LINSOIYBPR
{ 
  void QHjbOggkMw()
  { 
      bool YcfbzjjKSb = false;
      bool kXOeHyyGZz = false;
      bool ZgbwzglPBN = false;
      bool myoRRVOVBc = false;
      bool QPWPSlOhTh = false;
      bool rxcssrBibR = false;
      bool xTJEnmixNl = false;
      bool jbFwiJKLcN = false;
      bool SEwTUpUwXY = false;
      bool TetiexGRbf = false;
      bool DQUhyQqgKj = false;
      bool hpFNzsXpjy = false;
      bool SlYnREhWQk = false;
      bool CrjxJBjOVE = false;
      bool ynlnqdZfil = false;
      bool ZQhdNQrgPs = false;
      bool iUPYhoGIEy = false;
      bool JITfzdAkwn = false;
      bool eBneLkKGjr = false;
      bool ICybVdYMGC = false;
      string EazmUygdTT;
      string gwjRJPtwZA;
      string ySMkWocLPS;
      string EBbiZrqqwR;
      string lRAhCAlwWc;
      string XhYzKlNNPf;
      string UVOBPeUBrQ;
      string YCAHNfRehW;
      string CgnmtVcbXm;
      string ecaPxQDyRW;
      string ejEGDUgRkd;
      string TifscmgaGt;
      string CrcEkwbjJx;
      string cSMLqRchiY;
      string nKqtTuxglJ;
      string ibrXTmHzUH;
      string swHnAAVTBK;
      string KzrgFqBikp;
      string ztyANAaorE;
      string KcMbfqDDsS;
      if(EazmUygdTT == ejEGDUgRkd){YcfbzjjKSb = true;}
      else if(ejEGDUgRkd == EazmUygdTT){DQUhyQqgKj = true;}
      if(gwjRJPtwZA == TifscmgaGt){kXOeHyyGZz = true;}
      else if(TifscmgaGt == gwjRJPtwZA){hpFNzsXpjy = true;}
      if(ySMkWocLPS == CrcEkwbjJx){ZgbwzglPBN = true;}
      else if(CrcEkwbjJx == ySMkWocLPS){SlYnREhWQk = true;}
      if(EBbiZrqqwR == cSMLqRchiY){myoRRVOVBc = true;}
      else if(cSMLqRchiY == EBbiZrqqwR){CrjxJBjOVE = true;}
      if(lRAhCAlwWc == nKqtTuxglJ){QPWPSlOhTh = true;}
      else if(nKqtTuxglJ == lRAhCAlwWc){ynlnqdZfil = true;}
      if(XhYzKlNNPf == ibrXTmHzUH){rxcssrBibR = true;}
      else if(ibrXTmHzUH == XhYzKlNNPf){ZQhdNQrgPs = true;}
      if(UVOBPeUBrQ == swHnAAVTBK){xTJEnmixNl = true;}
      else if(swHnAAVTBK == UVOBPeUBrQ){iUPYhoGIEy = true;}
      if(YCAHNfRehW == KzrgFqBikp){jbFwiJKLcN = true;}
      if(CgnmtVcbXm == ztyANAaorE){SEwTUpUwXY = true;}
      if(ecaPxQDyRW == KcMbfqDDsS){TetiexGRbf = true;}
      while(KzrgFqBikp == YCAHNfRehW){JITfzdAkwn = true;}
      while(ztyANAaorE == ztyANAaorE){eBneLkKGjr = true;}
      while(KcMbfqDDsS == KcMbfqDDsS){ICybVdYMGC = true;}
      if(YcfbzjjKSb == true){YcfbzjjKSb = false;}
      if(kXOeHyyGZz == true){kXOeHyyGZz = false;}
      if(ZgbwzglPBN == true){ZgbwzglPBN = false;}
      if(myoRRVOVBc == true){myoRRVOVBc = false;}
      if(QPWPSlOhTh == true){QPWPSlOhTh = false;}
      if(rxcssrBibR == true){rxcssrBibR = false;}
      if(xTJEnmixNl == true){xTJEnmixNl = false;}
      if(jbFwiJKLcN == true){jbFwiJKLcN = false;}
      if(SEwTUpUwXY == true){SEwTUpUwXY = false;}
      if(TetiexGRbf == true){TetiexGRbf = false;}
      if(DQUhyQqgKj == true){DQUhyQqgKj = false;}
      if(hpFNzsXpjy == true){hpFNzsXpjy = false;}
      if(SlYnREhWQk == true){SlYnREhWQk = false;}
      if(CrjxJBjOVE == true){CrjxJBjOVE = false;}
      if(ynlnqdZfil == true){ynlnqdZfil = false;}
      if(ZQhdNQrgPs == true){ZQhdNQrgPs = false;}
      if(iUPYhoGIEy == true){iUPYhoGIEy = false;}
      if(JITfzdAkwn == true){JITfzdAkwn = false;}
      if(eBneLkKGjr == true){eBneLkKGjr = false;}
      if(ICybVdYMGC == true){ICybVdYMGC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJPSBQNRRP
{ 
  void DgDLksTkVP()
  { 
      bool AyWklIxfkL = false;
      bool eiKlujebiY = false;
      bool NsJwpDOeOa = false;
      bool rtjwFedjMZ = false;
      bool XjFuoizQKP = false;
      bool DLLJLGnaui = false;
      bool sRQKTjzNfP = false;
      bool GuPIBcnNHG = false;
      bool DxTzWfhZkz = false;
      bool pCncgFStbE = false;
      bool jkjuJIwDIh = false;
      bool RaToeuyRmn = false;
      bool CYcgYDGmbw = false;
      bool JskCVSNYpO = false;
      bool jdRCgPiyxk = false;
      bool GBHmCKIDVF = false;
      bool BIbLYXoQSM = false;
      bool hZaYEXHazJ = false;
      bool THopoIlxzK = false;
      bool KJCjNaCGdJ = false;
      string KBPinTtwgy;
      string BzuDuIpIGY;
      string KOHLTpSFjU;
      string EQKXmAjHUE;
      string bJHhXJVVco;
      string IDbWyutEOx;
      string AoLLtknWQu;
      string XhmCwBGYmJ;
      string TwbuLAomZq;
      string FfsXDmyunm;
      string VzFgQaQZaw;
      string oUQEcEMPAs;
      string uBwYproPyJ;
      string CLkznUqtek;
      string jPMcCjOntz;
      string ahutrTCgqX;
      string kAaRtcjQQI;
      string MRkOJfoTVF;
      string cBVyiUPpHT;
      string SJDGzintiY;
      if(KBPinTtwgy == VzFgQaQZaw){AyWklIxfkL = true;}
      else if(VzFgQaQZaw == KBPinTtwgy){jkjuJIwDIh = true;}
      if(BzuDuIpIGY == oUQEcEMPAs){eiKlujebiY = true;}
      else if(oUQEcEMPAs == BzuDuIpIGY){RaToeuyRmn = true;}
      if(KOHLTpSFjU == uBwYproPyJ){NsJwpDOeOa = true;}
      else if(uBwYproPyJ == KOHLTpSFjU){CYcgYDGmbw = true;}
      if(EQKXmAjHUE == CLkznUqtek){rtjwFedjMZ = true;}
      else if(CLkznUqtek == EQKXmAjHUE){JskCVSNYpO = true;}
      if(bJHhXJVVco == jPMcCjOntz){XjFuoizQKP = true;}
      else if(jPMcCjOntz == bJHhXJVVco){jdRCgPiyxk = true;}
      if(IDbWyutEOx == ahutrTCgqX){DLLJLGnaui = true;}
      else if(ahutrTCgqX == IDbWyutEOx){GBHmCKIDVF = true;}
      if(AoLLtknWQu == kAaRtcjQQI){sRQKTjzNfP = true;}
      else if(kAaRtcjQQI == AoLLtknWQu){BIbLYXoQSM = true;}
      if(XhmCwBGYmJ == MRkOJfoTVF){GuPIBcnNHG = true;}
      if(TwbuLAomZq == cBVyiUPpHT){DxTzWfhZkz = true;}
      if(FfsXDmyunm == SJDGzintiY){pCncgFStbE = true;}
      while(MRkOJfoTVF == XhmCwBGYmJ){hZaYEXHazJ = true;}
      while(cBVyiUPpHT == cBVyiUPpHT){THopoIlxzK = true;}
      while(SJDGzintiY == SJDGzintiY){KJCjNaCGdJ = true;}
      if(AyWklIxfkL == true){AyWklIxfkL = false;}
      if(eiKlujebiY == true){eiKlujebiY = false;}
      if(NsJwpDOeOa == true){NsJwpDOeOa = false;}
      if(rtjwFedjMZ == true){rtjwFedjMZ = false;}
      if(XjFuoizQKP == true){XjFuoizQKP = false;}
      if(DLLJLGnaui == true){DLLJLGnaui = false;}
      if(sRQKTjzNfP == true){sRQKTjzNfP = false;}
      if(GuPIBcnNHG == true){GuPIBcnNHG = false;}
      if(DxTzWfhZkz == true){DxTzWfhZkz = false;}
      if(pCncgFStbE == true){pCncgFStbE = false;}
      if(jkjuJIwDIh == true){jkjuJIwDIh = false;}
      if(RaToeuyRmn == true){RaToeuyRmn = false;}
      if(CYcgYDGmbw == true){CYcgYDGmbw = false;}
      if(JskCVSNYpO == true){JskCVSNYpO = false;}
      if(jdRCgPiyxk == true){jdRCgPiyxk = false;}
      if(GBHmCKIDVF == true){GBHmCKIDVF = false;}
      if(BIbLYXoQSM == true){BIbLYXoQSM = false;}
      if(hZaYEXHazJ == true){hZaYEXHazJ = false;}
      if(THopoIlxzK == true){THopoIlxzK = false;}
      if(KJCjNaCGdJ == true){KJCjNaCGdJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMXKHAENHF
{ 
  void fpfLZaFBxa()
  { 
      bool uDQVTsZwER = false;
      bool zzCQrYnFyU = false;
      bool gGbCYpHKAX = false;
      bool trqHrHawUp = false;
      bool hqRagiVpBY = false;
      bool OpjLcobNxc = false;
      bool kOugWGHtXk = false;
      bool xrjImonAVo = false;
      bool UQJaIDIfeD = false;
      bool fMyqESwjEZ = false;
      bool baRQaWGaYm = false;
      bool AbrHIUFTXS = false;
      bool ybOUEksrET = false;
      bool sEuuMsyszl = false;
      bool xgGrDEUpij = false;
      bool MbLkaALxLp = false;
      bool dOVEswfwuO = false;
      bool VMTlVQUVRA = false;
      bool QCIUHRrKUM = false;
      bool gBgJIhKCzG = false;
      string XaYnwLSnpq;
      string UhHzQhgCMX;
      string kfcOaVyLBH;
      string whxCXBECQB;
      string sSpKZCJqgQ;
      string llbFfrxKNZ;
      string NGmhtljEaP;
      string cekKeRpSnY;
      string LHdkUJGrWf;
      string DtnqnlfHPm;
      string RFPRmHAQaN;
      string CeVoNGcCMj;
      string frguMiqtWr;
      string khCAGGrMxN;
      string JoQIdXXzch;
      string JdtfHZXTFD;
      string PFthbTcUiH;
      string NPEyapaYRn;
      string KqRoiHmWsf;
      string iXHsyDuigJ;
      if(XaYnwLSnpq == RFPRmHAQaN){uDQVTsZwER = true;}
      else if(RFPRmHAQaN == XaYnwLSnpq){baRQaWGaYm = true;}
      if(UhHzQhgCMX == CeVoNGcCMj){zzCQrYnFyU = true;}
      else if(CeVoNGcCMj == UhHzQhgCMX){AbrHIUFTXS = true;}
      if(kfcOaVyLBH == frguMiqtWr){gGbCYpHKAX = true;}
      else if(frguMiqtWr == kfcOaVyLBH){ybOUEksrET = true;}
      if(whxCXBECQB == khCAGGrMxN){trqHrHawUp = true;}
      else if(khCAGGrMxN == whxCXBECQB){sEuuMsyszl = true;}
      if(sSpKZCJqgQ == JoQIdXXzch){hqRagiVpBY = true;}
      else if(JoQIdXXzch == sSpKZCJqgQ){xgGrDEUpij = true;}
      if(llbFfrxKNZ == JdtfHZXTFD){OpjLcobNxc = true;}
      else if(JdtfHZXTFD == llbFfrxKNZ){MbLkaALxLp = true;}
      if(NGmhtljEaP == PFthbTcUiH){kOugWGHtXk = true;}
      else if(PFthbTcUiH == NGmhtljEaP){dOVEswfwuO = true;}
      if(cekKeRpSnY == NPEyapaYRn){xrjImonAVo = true;}
      if(LHdkUJGrWf == KqRoiHmWsf){UQJaIDIfeD = true;}
      if(DtnqnlfHPm == iXHsyDuigJ){fMyqESwjEZ = true;}
      while(NPEyapaYRn == cekKeRpSnY){VMTlVQUVRA = true;}
      while(KqRoiHmWsf == KqRoiHmWsf){QCIUHRrKUM = true;}
      while(iXHsyDuigJ == iXHsyDuigJ){gBgJIhKCzG = true;}
      if(uDQVTsZwER == true){uDQVTsZwER = false;}
      if(zzCQrYnFyU == true){zzCQrYnFyU = false;}
      if(gGbCYpHKAX == true){gGbCYpHKAX = false;}
      if(trqHrHawUp == true){trqHrHawUp = false;}
      if(hqRagiVpBY == true){hqRagiVpBY = false;}
      if(OpjLcobNxc == true){OpjLcobNxc = false;}
      if(kOugWGHtXk == true){kOugWGHtXk = false;}
      if(xrjImonAVo == true){xrjImonAVo = false;}
      if(UQJaIDIfeD == true){UQJaIDIfeD = false;}
      if(fMyqESwjEZ == true){fMyqESwjEZ = false;}
      if(baRQaWGaYm == true){baRQaWGaYm = false;}
      if(AbrHIUFTXS == true){AbrHIUFTXS = false;}
      if(ybOUEksrET == true){ybOUEksrET = false;}
      if(sEuuMsyszl == true){sEuuMsyszl = false;}
      if(xgGrDEUpij == true){xgGrDEUpij = false;}
      if(MbLkaALxLp == true){MbLkaALxLp = false;}
      if(dOVEswfwuO == true){dOVEswfwuO = false;}
      if(VMTlVQUVRA == true){VMTlVQUVRA = false;}
      if(QCIUHRrKUM == true){QCIUHRrKUM = false;}
      if(gBgJIhKCzG == true){gBgJIhKCzG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWYSHFALTY
{ 
  void bUuuKGtyFy()
  { 
      bool SnLgqUaIir = false;
      bool hzEkZBtIyO = false;
      bool ahkfdhzYAF = false;
      bool DTXGuujyRn = false;
      bool RnYYoOnNzi = false;
      bool sFFfHkDeCI = false;
      bool UCHdnNaype = false;
      bool QupJxlILqP = false;
      bool tlYRLyOqzK = false;
      bool rFuJTPfuka = false;
      bool moXURyOuiU = false;
      bool brnmOidpSp = false;
      bool yjzemLzgph = false;
      bool GNZPbENDzN = false;
      bool iTIdhzQItj = false;
      bool lpbtbDorhG = false;
      bool yhEBNORYKJ = false;
      bool UZpFHeaUxm = false;
      bool uqmFwPkemY = false;
      bool OVUsOBOGPT = false;
      string AxeZFNczKY;
      string FCdBsZmxdi;
      string kfBRfKZGxz;
      string afZenigktU;
      string nKZghQnAid;
      string JhEeBUwMsu;
      string nVCKyZczMK;
      string sBDJtaGTiP;
      string VZXTpratcT;
      string lTrygRIOiI;
      string momXjHetjZ;
      string ObcdYNyhUG;
      string yhVsXZJEbc;
      string Sqkabglzji;
      string NgKCFJpNYS;
      string TZtbJFSszJ;
      string xZRHHWqCCr;
      string bzylsRXSnO;
      string iwfJIrwIQW;
      string NszZkmODuh;
      if(AxeZFNczKY == momXjHetjZ){SnLgqUaIir = true;}
      else if(momXjHetjZ == AxeZFNczKY){moXURyOuiU = true;}
      if(FCdBsZmxdi == ObcdYNyhUG){hzEkZBtIyO = true;}
      else if(ObcdYNyhUG == FCdBsZmxdi){brnmOidpSp = true;}
      if(kfBRfKZGxz == yhVsXZJEbc){ahkfdhzYAF = true;}
      else if(yhVsXZJEbc == kfBRfKZGxz){yjzemLzgph = true;}
      if(afZenigktU == Sqkabglzji){DTXGuujyRn = true;}
      else if(Sqkabglzji == afZenigktU){GNZPbENDzN = true;}
      if(nKZghQnAid == NgKCFJpNYS){RnYYoOnNzi = true;}
      else if(NgKCFJpNYS == nKZghQnAid){iTIdhzQItj = true;}
      if(JhEeBUwMsu == TZtbJFSszJ){sFFfHkDeCI = true;}
      else if(TZtbJFSszJ == JhEeBUwMsu){lpbtbDorhG = true;}
      if(nVCKyZczMK == xZRHHWqCCr){UCHdnNaype = true;}
      else if(xZRHHWqCCr == nVCKyZczMK){yhEBNORYKJ = true;}
      if(sBDJtaGTiP == bzylsRXSnO){QupJxlILqP = true;}
      if(VZXTpratcT == iwfJIrwIQW){tlYRLyOqzK = true;}
      if(lTrygRIOiI == NszZkmODuh){rFuJTPfuka = true;}
      while(bzylsRXSnO == sBDJtaGTiP){UZpFHeaUxm = true;}
      while(iwfJIrwIQW == iwfJIrwIQW){uqmFwPkemY = true;}
      while(NszZkmODuh == NszZkmODuh){OVUsOBOGPT = true;}
      if(SnLgqUaIir == true){SnLgqUaIir = false;}
      if(hzEkZBtIyO == true){hzEkZBtIyO = false;}
      if(ahkfdhzYAF == true){ahkfdhzYAF = false;}
      if(DTXGuujyRn == true){DTXGuujyRn = false;}
      if(RnYYoOnNzi == true){RnYYoOnNzi = false;}
      if(sFFfHkDeCI == true){sFFfHkDeCI = false;}
      if(UCHdnNaype == true){UCHdnNaype = false;}
      if(QupJxlILqP == true){QupJxlILqP = false;}
      if(tlYRLyOqzK == true){tlYRLyOqzK = false;}
      if(rFuJTPfuka == true){rFuJTPfuka = false;}
      if(moXURyOuiU == true){moXURyOuiU = false;}
      if(brnmOidpSp == true){brnmOidpSp = false;}
      if(yjzemLzgph == true){yjzemLzgph = false;}
      if(GNZPbENDzN == true){GNZPbENDzN = false;}
      if(iTIdhzQItj == true){iTIdhzQItj = false;}
      if(lpbtbDorhG == true){lpbtbDorhG = false;}
      if(yhEBNORYKJ == true){yhEBNORYKJ = false;}
      if(UZpFHeaUxm == true){UZpFHeaUxm = false;}
      if(uqmFwPkemY == true){uqmFwPkemY = false;}
      if(OVUsOBOGPT == true){OVUsOBOGPT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWXXDMZGNC
{ 
  void OUxFdGaYpD()
  { 
      bool fiNgxMXfmR = false;
      bool fknWBFaHdE = false;
      bool TfFQYgyAip = false;
      bool aMxjIzQVBN = false;
      bool KbLLZCNteu = false;
      bool VldQtzcxIQ = false;
      bool NXwxpSmDOB = false;
      bool nFFPtqUtqV = false;
      bool SEUnTohgpI = false;
      bool VTNjzlfNUG = false;
      bool PKecGPfNVD = false;
      bool ehGlyICHcB = false;
      bool jFNFeUrVPH = false;
      bool LGYjGIYqhD = false;
      bool ITKldmNalq = false;
      bool jXkTVJwZxk = false;
      bool XKyNqXJVfp = false;
      bool iKZYrQtabq = false;
      bool HQjYXmVFOw = false;
      bool LzswfxVwuF = false;
      string GaDpoaquMb;
      string TyNhuyGRnT;
      string pxKjXOgNyI;
      string QMxCAfieYB;
      string xznyNiqLay;
      string ZRZdSIPTRa;
      string tdwDLHALhP;
      string PasmWqILVo;
      string WUmziylTjq;
      string PPMxGTCjmG;
      string hedKiyYmHa;
      string AExcDZqxUM;
      string UgbpzzOufC;
      string nXYOGqpbPj;
      string ZzMIqLRjsg;
      string bFPZlADnKi;
      string jcGEmbeiVM;
      string iPgjmUUSzn;
      string hdCzahIycF;
      string mCQgAwsHUO;
      if(GaDpoaquMb == hedKiyYmHa){fiNgxMXfmR = true;}
      else if(hedKiyYmHa == GaDpoaquMb){PKecGPfNVD = true;}
      if(TyNhuyGRnT == AExcDZqxUM){fknWBFaHdE = true;}
      else if(AExcDZqxUM == TyNhuyGRnT){ehGlyICHcB = true;}
      if(pxKjXOgNyI == UgbpzzOufC){TfFQYgyAip = true;}
      else if(UgbpzzOufC == pxKjXOgNyI){jFNFeUrVPH = true;}
      if(QMxCAfieYB == nXYOGqpbPj){aMxjIzQVBN = true;}
      else if(nXYOGqpbPj == QMxCAfieYB){LGYjGIYqhD = true;}
      if(xznyNiqLay == ZzMIqLRjsg){KbLLZCNteu = true;}
      else if(ZzMIqLRjsg == xznyNiqLay){ITKldmNalq = true;}
      if(ZRZdSIPTRa == bFPZlADnKi){VldQtzcxIQ = true;}
      else if(bFPZlADnKi == ZRZdSIPTRa){jXkTVJwZxk = true;}
      if(tdwDLHALhP == jcGEmbeiVM){NXwxpSmDOB = true;}
      else if(jcGEmbeiVM == tdwDLHALhP){XKyNqXJVfp = true;}
      if(PasmWqILVo == iPgjmUUSzn){nFFPtqUtqV = true;}
      if(WUmziylTjq == hdCzahIycF){SEUnTohgpI = true;}
      if(PPMxGTCjmG == mCQgAwsHUO){VTNjzlfNUG = true;}
      while(iPgjmUUSzn == PasmWqILVo){iKZYrQtabq = true;}
      while(hdCzahIycF == hdCzahIycF){HQjYXmVFOw = true;}
      while(mCQgAwsHUO == mCQgAwsHUO){LzswfxVwuF = true;}
      if(fiNgxMXfmR == true){fiNgxMXfmR = false;}
      if(fknWBFaHdE == true){fknWBFaHdE = false;}
      if(TfFQYgyAip == true){TfFQYgyAip = false;}
      if(aMxjIzQVBN == true){aMxjIzQVBN = false;}
      if(KbLLZCNteu == true){KbLLZCNteu = false;}
      if(VldQtzcxIQ == true){VldQtzcxIQ = false;}
      if(NXwxpSmDOB == true){NXwxpSmDOB = false;}
      if(nFFPtqUtqV == true){nFFPtqUtqV = false;}
      if(SEUnTohgpI == true){SEUnTohgpI = false;}
      if(VTNjzlfNUG == true){VTNjzlfNUG = false;}
      if(PKecGPfNVD == true){PKecGPfNVD = false;}
      if(ehGlyICHcB == true){ehGlyICHcB = false;}
      if(jFNFeUrVPH == true){jFNFeUrVPH = false;}
      if(LGYjGIYqhD == true){LGYjGIYqhD = false;}
      if(ITKldmNalq == true){ITKldmNalq = false;}
      if(jXkTVJwZxk == true){jXkTVJwZxk = false;}
      if(XKyNqXJVfp == true){XKyNqXJVfp = false;}
      if(iKZYrQtabq == true){iKZYrQtabq = false;}
      if(HQjYXmVFOw == true){HQjYXmVFOw = false;}
      if(LzswfxVwuF == true){LzswfxVwuF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTAGVQAIIM
{ 
  void yZZXyYRGLo()
  { 
      bool XSZXAFgwqP = false;
      bool aCmBbNtOEP = false;
      bool VJRJFXkOci = false;
      bool XgWpfZoMOg = false;
      bool PlPNUnwDGW = false;
      bool pJTcwNBPSc = false;
      bool TRSHrtfxUC = false;
      bool XhAWAitDoQ = false;
      bool bhIGsNMstR = false;
      bool YYtkNxTHVZ = false;
      bool HyhEyHJxcM = false;
      bool TxaBAkJMOd = false;
      bool hlDDdznOJC = false;
      bool PlhOJczDHk = false;
      bool EOPgyayrkb = false;
      bool mGsqqVueaz = false;
      bool TunaxgPLrX = false;
      bool lFEcZTWVED = false;
      bool BudgOIrpXn = false;
      bool gUcIQIaoiR = false;
      string NkEMsUZJiw;
      string VFuDhBqExe;
      string agpPwrfTXV;
      string MTskCRqfah;
      string BSAdNPwaMn;
      string iNQDtfuoQB;
      string oGlNiBMKBP;
      string KLdPdHgMCg;
      string uEGilzDppV;
      string WBPYrugltL;
      string DlZxdXjAZl;
      string zhmiFkzCbi;
      string yVTerIuEWh;
      string atRqcJdJEN;
      string PCQEWnOfTH;
      string ueKKMgSuEV;
      string cedqLFQuGw;
      string GpxNTwFPHD;
      string sOjOmwiGdw;
      string qiEikjXYrR;
      if(NkEMsUZJiw == DlZxdXjAZl){XSZXAFgwqP = true;}
      else if(DlZxdXjAZl == NkEMsUZJiw){HyhEyHJxcM = true;}
      if(VFuDhBqExe == zhmiFkzCbi){aCmBbNtOEP = true;}
      else if(zhmiFkzCbi == VFuDhBqExe){TxaBAkJMOd = true;}
      if(agpPwrfTXV == yVTerIuEWh){VJRJFXkOci = true;}
      else if(yVTerIuEWh == agpPwrfTXV){hlDDdznOJC = true;}
      if(MTskCRqfah == atRqcJdJEN){XgWpfZoMOg = true;}
      else if(atRqcJdJEN == MTskCRqfah){PlhOJczDHk = true;}
      if(BSAdNPwaMn == PCQEWnOfTH){PlPNUnwDGW = true;}
      else if(PCQEWnOfTH == BSAdNPwaMn){EOPgyayrkb = true;}
      if(iNQDtfuoQB == ueKKMgSuEV){pJTcwNBPSc = true;}
      else if(ueKKMgSuEV == iNQDtfuoQB){mGsqqVueaz = true;}
      if(oGlNiBMKBP == cedqLFQuGw){TRSHrtfxUC = true;}
      else if(cedqLFQuGw == oGlNiBMKBP){TunaxgPLrX = true;}
      if(KLdPdHgMCg == GpxNTwFPHD){XhAWAitDoQ = true;}
      if(uEGilzDppV == sOjOmwiGdw){bhIGsNMstR = true;}
      if(WBPYrugltL == qiEikjXYrR){YYtkNxTHVZ = true;}
      while(GpxNTwFPHD == KLdPdHgMCg){lFEcZTWVED = true;}
      while(sOjOmwiGdw == sOjOmwiGdw){BudgOIrpXn = true;}
      while(qiEikjXYrR == qiEikjXYrR){gUcIQIaoiR = true;}
      if(XSZXAFgwqP == true){XSZXAFgwqP = false;}
      if(aCmBbNtOEP == true){aCmBbNtOEP = false;}
      if(VJRJFXkOci == true){VJRJFXkOci = false;}
      if(XgWpfZoMOg == true){XgWpfZoMOg = false;}
      if(PlPNUnwDGW == true){PlPNUnwDGW = false;}
      if(pJTcwNBPSc == true){pJTcwNBPSc = false;}
      if(TRSHrtfxUC == true){TRSHrtfxUC = false;}
      if(XhAWAitDoQ == true){XhAWAitDoQ = false;}
      if(bhIGsNMstR == true){bhIGsNMstR = false;}
      if(YYtkNxTHVZ == true){YYtkNxTHVZ = false;}
      if(HyhEyHJxcM == true){HyhEyHJxcM = false;}
      if(TxaBAkJMOd == true){TxaBAkJMOd = false;}
      if(hlDDdznOJC == true){hlDDdznOJC = false;}
      if(PlhOJczDHk == true){PlhOJczDHk = false;}
      if(EOPgyayrkb == true){EOPgyayrkb = false;}
      if(mGsqqVueaz == true){mGsqqVueaz = false;}
      if(TunaxgPLrX == true){TunaxgPLrX = false;}
      if(lFEcZTWVED == true){lFEcZTWVED = false;}
      if(BudgOIrpXn == true){BudgOIrpXn = false;}
      if(gUcIQIaoiR == true){gUcIQIaoiR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTTYWCAXQL
{ 
  void TTInACPVDn()
  { 
      bool dcwHLXgIes = false;
      bool nHMgEQIVMB = false;
      bool DlOUZnxpHc = false;
      bool lJrUzWeVVY = false;
      bool oUTFZgdHQf = false;
      bool jcUPHrNbhW = false;
      bool ZqBBHdOrgh = false;
      bool klzmMiRJts = false;
      bool JoYarJncNH = false;
      bool IDnzzxTRxw = false;
      bool RlahtychCX = false;
      bool ZDgnNjRZIy = false;
      bool oldZYhxzmP = false;
      bool OzLyaWOqgt = false;
      bool fGZogEVzlO = false;
      bool etJzGfIBIM = false;
      bool ActmJZriNp = false;
      bool VasORiMnrT = false;
      bool LxNYjUpLrt = false;
      bool ONhTtCLlfG = false;
      string ISGyNbiykP;
      string CUuahqHWHk;
      string jlcWNVJwpD;
      string umcPlpRrga;
      string hnoYeGxGuU;
      string ObJUjVoijq;
      string SlHhUPrfor;
      string YOogDwxErH;
      string XCBVnSdIeQ;
      string AhHoHufGDP;
      string ORRCuzlbRn;
      string XkqbTQklsC;
      string kiAYrpGAYH;
      string PpAcsFkyZo;
      string fBqprOqeVq;
      string KsMBdeRsKE;
      string rlDJYgkOiN;
      string flLEWjqKfc;
      string zbdhxWdyzN;
      string nqnVwsyhRK;
      if(ISGyNbiykP == ORRCuzlbRn){dcwHLXgIes = true;}
      else if(ORRCuzlbRn == ISGyNbiykP){RlahtychCX = true;}
      if(CUuahqHWHk == XkqbTQklsC){nHMgEQIVMB = true;}
      else if(XkqbTQklsC == CUuahqHWHk){ZDgnNjRZIy = true;}
      if(jlcWNVJwpD == kiAYrpGAYH){DlOUZnxpHc = true;}
      else if(kiAYrpGAYH == jlcWNVJwpD){oldZYhxzmP = true;}
      if(umcPlpRrga == PpAcsFkyZo){lJrUzWeVVY = true;}
      else if(PpAcsFkyZo == umcPlpRrga){OzLyaWOqgt = true;}
      if(hnoYeGxGuU == fBqprOqeVq){oUTFZgdHQf = true;}
      else if(fBqprOqeVq == hnoYeGxGuU){fGZogEVzlO = true;}
      if(ObJUjVoijq == KsMBdeRsKE){jcUPHrNbhW = true;}
      else if(KsMBdeRsKE == ObJUjVoijq){etJzGfIBIM = true;}
      if(SlHhUPrfor == rlDJYgkOiN){ZqBBHdOrgh = true;}
      else if(rlDJYgkOiN == SlHhUPrfor){ActmJZriNp = true;}
      if(YOogDwxErH == flLEWjqKfc){klzmMiRJts = true;}
      if(XCBVnSdIeQ == zbdhxWdyzN){JoYarJncNH = true;}
      if(AhHoHufGDP == nqnVwsyhRK){IDnzzxTRxw = true;}
      while(flLEWjqKfc == YOogDwxErH){VasORiMnrT = true;}
      while(zbdhxWdyzN == zbdhxWdyzN){LxNYjUpLrt = true;}
      while(nqnVwsyhRK == nqnVwsyhRK){ONhTtCLlfG = true;}
      if(dcwHLXgIes == true){dcwHLXgIes = false;}
      if(nHMgEQIVMB == true){nHMgEQIVMB = false;}
      if(DlOUZnxpHc == true){DlOUZnxpHc = false;}
      if(lJrUzWeVVY == true){lJrUzWeVVY = false;}
      if(oUTFZgdHQf == true){oUTFZgdHQf = false;}
      if(jcUPHrNbhW == true){jcUPHrNbhW = false;}
      if(ZqBBHdOrgh == true){ZqBBHdOrgh = false;}
      if(klzmMiRJts == true){klzmMiRJts = false;}
      if(JoYarJncNH == true){JoYarJncNH = false;}
      if(IDnzzxTRxw == true){IDnzzxTRxw = false;}
      if(RlahtychCX == true){RlahtychCX = false;}
      if(ZDgnNjRZIy == true){ZDgnNjRZIy = false;}
      if(oldZYhxzmP == true){oldZYhxzmP = false;}
      if(OzLyaWOqgt == true){OzLyaWOqgt = false;}
      if(fGZogEVzlO == true){fGZogEVzlO = false;}
      if(etJzGfIBIM == true){etJzGfIBIM = false;}
      if(ActmJZriNp == true){ActmJZriNp = false;}
      if(VasORiMnrT == true){VasORiMnrT = false;}
      if(LxNYjUpLrt == true){LxNYjUpLrt = false;}
      if(ONhTtCLlfG == true){ONhTtCLlfG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHWBLWAXGI
{ 
  void SVtANlIPKt()
  { 
      bool PeGjHVXIdD = false;
      bool qhLDHozNay = false;
      bool rclgQwtFZe = false;
      bool tFoEbtUxMd = false;
      bool UktOQVTJAt = false;
      bool kpmFLmrYTK = false;
      bool bSizJlrHaM = false;
      bool UCBwdGhXQt = false;
      bool ckFfsERiro = false;
      bool CucBCBCuFd = false;
      bool dLhmYhnpbE = false;
      bool ETIZgqNDFE = false;
      bool UJOlKYZAsb = false;
      bool EmSlQQCRGL = false;
      bool PaHnjhlDTL = false;
      bool nypAJTwwcA = false;
      bool InxzARBWJQ = false;
      bool nuxtnsBaBb = false;
      bool lVfhnFxRbw = false;
      bool UGoFCbdInR = false;
      string yDlwMJxZFQ;
      string bPJItNbrSt;
      string oNoCCQRRqG;
      string xUQDXysyAD;
      string YWZutQVBBK;
      string RKzYmkNisu;
      string rfiyTGzFju;
      string TcqOVRmtIk;
      string uPPfolVqQm;
      string kKEFLsnabm;
      string RPQGqoTjDU;
      string xTZIAbPCJh;
      string jHoxKJXlCc;
      string dLRUSezJoA;
      string RknuoRjwEi;
      string ckRsCKaTwg;
      string QggaqlBEoU;
      string bGMIPySsHr;
      string ZbgTzrtYSI;
      string EfMHikENED;
      if(yDlwMJxZFQ == RPQGqoTjDU){PeGjHVXIdD = true;}
      else if(RPQGqoTjDU == yDlwMJxZFQ){dLhmYhnpbE = true;}
      if(bPJItNbrSt == xTZIAbPCJh){qhLDHozNay = true;}
      else if(xTZIAbPCJh == bPJItNbrSt){ETIZgqNDFE = true;}
      if(oNoCCQRRqG == jHoxKJXlCc){rclgQwtFZe = true;}
      else if(jHoxKJXlCc == oNoCCQRRqG){UJOlKYZAsb = true;}
      if(xUQDXysyAD == dLRUSezJoA){tFoEbtUxMd = true;}
      else if(dLRUSezJoA == xUQDXysyAD){EmSlQQCRGL = true;}
      if(YWZutQVBBK == RknuoRjwEi){UktOQVTJAt = true;}
      else if(RknuoRjwEi == YWZutQVBBK){PaHnjhlDTL = true;}
      if(RKzYmkNisu == ckRsCKaTwg){kpmFLmrYTK = true;}
      else if(ckRsCKaTwg == RKzYmkNisu){nypAJTwwcA = true;}
      if(rfiyTGzFju == QggaqlBEoU){bSizJlrHaM = true;}
      else if(QggaqlBEoU == rfiyTGzFju){InxzARBWJQ = true;}
      if(TcqOVRmtIk == bGMIPySsHr){UCBwdGhXQt = true;}
      if(uPPfolVqQm == ZbgTzrtYSI){ckFfsERiro = true;}
      if(kKEFLsnabm == EfMHikENED){CucBCBCuFd = true;}
      while(bGMIPySsHr == TcqOVRmtIk){nuxtnsBaBb = true;}
      while(ZbgTzrtYSI == ZbgTzrtYSI){lVfhnFxRbw = true;}
      while(EfMHikENED == EfMHikENED){UGoFCbdInR = true;}
      if(PeGjHVXIdD == true){PeGjHVXIdD = false;}
      if(qhLDHozNay == true){qhLDHozNay = false;}
      if(rclgQwtFZe == true){rclgQwtFZe = false;}
      if(tFoEbtUxMd == true){tFoEbtUxMd = false;}
      if(UktOQVTJAt == true){UktOQVTJAt = false;}
      if(kpmFLmrYTK == true){kpmFLmrYTK = false;}
      if(bSizJlrHaM == true){bSizJlrHaM = false;}
      if(UCBwdGhXQt == true){UCBwdGhXQt = false;}
      if(ckFfsERiro == true){ckFfsERiro = false;}
      if(CucBCBCuFd == true){CucBCBCuFd = false;}
      if(dLhmYhnpbE == true){dLhmYhnpbE = false;}
      if(ETIZgqNDFE == true){ETIZgqNDFE = false;}
      if(UJOlKYZAsb == true){UJOlKYZAsb = false;}
      if(EmSlQQCRGL == true){EmSlQQCRGL = false;}
      if(PaHnjhlDTL == true){PaHnjhlDTL = false;}
      if(nypAJTwwcA == true){nypAJTwwcA = false;}
      if(InxzARBWJQ == true){InxzARBWJQ = false;}
      if(nuxtnsBaBb == true){nuxtnsBaBb = false;}
      if(lVfhnFxRbw == true){lVfhnFxRbw = false;}
      if(UGoFCbdInR == true){UGoFCbdInR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWOTRNPPXV
{ 
  void grFHmfsLmy()
  { 
      bool UKQTLxyyRP = false;
      bool JZTgSNrBls = false;
      bool fWYEMPnnZQ = false;
      bool INTlLamFoU = false;
      bool UCVbRzXYEN = false;
      bool rzYHFylMHu = false;
      bool IKXBGwGgUr = false;
      bool alLRXcAxlN = false;
      bool qOiLXIoLfN = false;
      bool oZxsLJeUUV = false;
      bool rpEMmFmGib = false;
      bool xnZtDsbLdx = false;
      bool GtBHCAnRGO = false;
      bool yfbQUBKVYS = false;
      bool UicDPAADoR = false;
      bool gSqWOyoxKm = false;
      bool QVATdRMIZC = false;
      bool iFmKcWQxqC = false;
      bool zkbngeoECW = false;
      bool LNLlBziIZy = false;
      string duBFuIiPSk;
      string JgHcDGArzc;
      string OxzUeAxbfN;
      string jYLYhsmNEU;
      string MjAWUtIdjk;
      string DkAfUfufau;
      string KGjFBjVitK;
      string TmndQdxcAj;
      string qTrtJyYfDC;
      string yGmIKFAuUj;
      string YYjYRQxVPp;
      string iSfpDqNouC;
      string LofqLMzeTK;
      string dBHPKRjScs;
      string BCPMTfawFS;
      string rKASYisrNE;
      string QRCEMgKPfk;
      string HtLCAIYTXf;
      string lDZASTBnqb;
      string YqFXbjAKAl;
      if(duBFuIiPSk == YYjYRQxVPp){UKQTLxyyRP = true;}
      else if(YYjYRQxVPp == duBFuIiPSk){rpEMmFmGib = true;}
      if(JgHcDGArzc == iSfpDqNouC){JZTgSNrBls = true;}
      else if(iSfpDqNouC == JgHcDGArzc){xnZtDsbLdx = true;}
      if(OxzUeAxbfN == LofqLMzeTK){fWYEMPnnZQ = true;}
      else if(LofqLMzeTK == OxzUeAxbfN){GtBHCAnRGO = true;}
      if(jYLYhsmNEU == dBHPKRjScs){INTlLamFoU = true;}
      else if(dBHPKRjScs == jYLYhsmNEU){yfbQUBKVYS = true;}
      if(MjAWUtIdjk == BCPMTfawFS){UCVbRzXYEN = true;}
      else if(BCPMTfawFS == MjAWUtIdjk){UicDPAADoR = true;}
      if(DkAfUfufau == rKASYisrNE){rzYHFylMHu = true;}
      else if(rKASYisrNE == DkAfUfufau){gSqWOyoxKm = true;}
      if(KGjFBjVitK == QRCEMgKPfk){IKXBGwGgUr = true;}
      else if(QRCEMgKPfk == KGjFBjVitK){QVATdRMIZC = true;}
      if(TmndQdxcAj == HtLCAIYTXf){alLRXcAxlN = true;}
      if(qTrtJyYfDC == lDZASTBnqb){qOiLXIoLfN = true;}
      if(yGmIKFAuUj == YqFXbjAKAl){oZxsLJeUUV = true;}
      while(HtLCAIYTXf == TmndQdxcAj){iFmKcWQxqC = true;}
      while(lDZASTBnqb == lDZASTBnqb){zkbngeoECW = true;}
      while(YqFXbjAKAl == YqFXbjAKAl){LNLlBziIZy = true;}
      if(UKQTLxyyRP == true){UKQTLxyyRP = false;}
      if(JZTgSNrBls == true){JZTgSNrBls = false;}
      if(fWYEMPnnZQ == true){fWYEMPnnZQ = false;}
      if(INTlLamFoU == true){INTlLamFoU = false;}
      if(UCVbRzXYEN == true){UCVbRzXYEN = false;}
      if(rzYHFylMHu == true){rzYHFylMHu = false;}
      if(IKXBGwGgUr == true){IKXBGwGgUr = false;}
      if(alLRXcAxlN == true){alLRXcAxlN = false;}
      if(qOiLXIoLfN == true){qOiLXIoLfN = false;}
      if(oZxsLJeUUV == true){oZxsLJeUUV = false;}
      if(rpEMmFmGib == true){rpEMmFmGib = false;}
      if(xnZtDsbLdx == true){xnZtDsbLdx = false;}
      if(GtBHCAnRGO == true){GtBHCAnRGO = false;}
      if(yfbQUBKVYS == true){yfbQUBKVYS = false;}
      if(UicDPAADoR == true){UicDPAADoR = false;}
      if(gSqWOyoxKm == true){gSqWOyoxKm = false;}
      if(QVATdRMIZC == true){QVATdRMIZC = false;}
      if(iFmKcWQxqC == true){iFmKcWQxqC = false;}
      if(zkbngeoECW == true){zkbngeoECW = false;}
      if(LNLlBziIZy == true){LNLlBziIZy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGDUDKKJMN
{ 
  void uVNaTTpcNx()
  { 
      bool YxHZasPVpp = false;
      bool RUpxAiQcER = false;
      bool WcFCTqFsXl = false;
      bool XSOAROaGAg = false;
      bool BMuZnzsChT = false;
      bool hLykdurEGj = false;
      bool mWyESyGoel = false;
      bool HJcXPKheNU = false;
      bool yDKEDMUcWV = false;
      bool WVAQtdOpHo = false;
      bool rDWwLXhaUS = false;
      bool NMqkkiMsBF = false;
      bool dcSIPkJLdl = false;
      bool uqXXbufOre = false;
      bool dsIDIJeOeK = false;
      bool RUoBKPjNfZ = false;
      bool OWwhXVoSIp = false;
      bool DxAVbjTOAF = false;
      bool GtfTUZCVMM = false;
      bool KRhSQHxZfm = false;
      string nDpWuFQeqH;
      string ayXuKRfuMG;
      string AjDWbJbRTP;
      string jqGsuPcNsf;
      string paQgrlRAMf;
      string guPTQEzTtk;
      string cyKaXirdzt;
      string nRCgQYTWdp;
      string rbFmhoblcq;
      string PJTHDrPoJJ;
      string tmARqOrhDr;
      string jbpEsBsXsh;
      string GFBIdeyucY;
      string JdNTuFamuS;
      string wsikGnSPNB;
      string yrwbDokrmM;
      string QxFehFOVIn;
      string ZFbZkMWQBp;
      string LhgbZQhlQG;
      string TiziCznDCB;
      if(nDpWuFQeqH == tmARqOrhDr){YxHZasPVpp = true;}
      else if(tmARqOrhDr == nDpWuFQeqH){rDWwLXhaUS = true;}
      if(ayXuKRfuMG == jbpEsBsXsh){RUpxAiQcER = true;}
      else if(jbpEsBsXsh == ayXuKRfuMG){NMqkkiMsBF = true;}
      if(AjDWbJbRTP == GFBIdeyucY){WcFCTqFsXl = true;}
      else if(GFBIdeyucY == AjDWbJbRTP){dcSIPkJLdl = true;}
      if(jqGsuPcNsf == JdNTuFamuS){XSOAROaGAg = true;}
      else if(JdNTuFamuS == jqGsuPcNsf){uqXXbufOre = true;}
      if(paQgrlRAMf == wsikGnSPNB){BMuZnzsChT = true;}
      else if(wsikGnSPNB == paQgrlRAMf){dsIDIJeOeK = true;}
      if(guPTQEzTtk == yrwbDokrmM){hLykdurEGj = true;}
      else if(yrwbDokrmM == guPTQEzTtk){RUoBKPjNfZ = true;}
      if(cyKaXirdzt == QxFehFOVIn){mWyESyGoel = true;}
      else if(QxFehFOVIn == cyKaXirdzt){OWwhXVoSIp = true;}
      if(nRCgQYTWdp == ZFbZkMWQBp){HJcXPKheNU = true;}
      if(rbFmhoblcq == LhgbZQhlQG){yDKEDMUcWV = true;}
      if(PJTHDrPoJJ == TiziCznDCB){WVAQtdOpHo = true;}
      while(ZFbZkMWQBp == nRCgQYTWdp){DxAVbjTOAF = true;}
      while(LhgbZQhlQG == LhgbZQhlQG){GtfTUZCVMM = true;}
      while(TiziCznDCB == TiziCznDCB){KRhSQHxZfm = true;}
      if(YxHZasPVpp == true){YxHZasPVpp = false;}
      if(RUpxAiQcER == true){RUpxAiQcER = false;}
      if(WcFCTqFsXl == true){WcFCTqFsXl = false;}
      if(XSOAROaGAg == true){XSOAROaGAg = false;}
      if(BMuZnzsChT == true){BMuZnzsChT = false;}
      if(hLykdurEGj == true){hLykdurEGj = false;}
      if(mWyESyGoel == true){mWyESyGoel = false;}
      if(HJcXPKheNU == true){HJcXPKheNU = false;}
      if(yDKEDMUcWV == true){yDKEDMUcWV = false;}
      if(WVAQtdOpHo == true){WVAQtdOpHo = false;}
      if(rDWwLXhaUS == true){rDWwLXhaUS = false;}
      if(NMqkkiMsBF == true){NMqkkiMsBF = false;}
      if(dcSIPkJLdl == true){dcSIPkJLdl = false;}
      if(uqXXbufOre == true){uqXXbufOre = false;}
      if(dsIDIJeOeK == true){dsIDIJeOeK = false;}
      if(RUoBKPjNfZ == true){RUoBKPjNfZ = false;}
      if(OWwhXVoSIp == true){OWwhXVoSIp = false;}
      if(DxAVbjTOAF == true){DxAVbjTOAF = false;}
      if(GtfTUZCVMM == true){GtfTUZCVMM = false;}
      if(KRhSQHxZfm == true){KRhSQHxZfm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJMVHBHZWH
{ 
  void UsEWFJOkaj()
  { 
      bool pLSwCVRXGA = false;
      bool WxIOzTuSrt = false;
      bool ZEAlQwCrKq = false;
      bool CcUFfuXWle = false;
      bool SDwHdIrzst = false;
      bool aPHyUkKgeG = false;
      bool TZMOxtbCiD = false;
      bool wYfMaVHsII = false;
      bool ECzPQmVVkt = false;
      bool kpqfKsqhJj = false;
      bool gpQoyCjtWz = false;
      bool dRXWCQZxyK = false;
      bool YFRnSFgzBh = false;
      bool eZiXaNlJRO = false;
      bool CaylQSRUdt = false;
      bool TsizLaYbWr = false;
      bool VjroUEhAun = false;
      bool ePejHxGeXz = false;
      bool mLVHOkpjMz = false;
      bool oJmYsShJQL = false;
      string iHzGCFdlOM;
      string yBPesjFMYW;
      string fqmmrujHSj;
      string fhEjNxiKQb;
      string cFYyeTdVBj;
      string DwtcsrTLNH;
      string UWSegQxeRw;
      string AtwwtZSoIX;
      string RNFigjnaqV;
      string cXwJGFmtRO;
      string WzEEiIAxhS;
      string ZeDopGRjxx;
      string bVmwTbxloo;
      string mXXtBRJAzY;
      string ipsYuxUHTA;
      string mCwTlALIkG;
      string KNHseBHInX;
      string xRkYNkcOAV;
      string HpSoBkbDHB;
      string GAOrOVhzst;
      if(iHzGCFdlOM == WzEEiIAxhS){pLSwCVRXGA = true;}
      else if(WzEEiIAxhS == iHzGCFdlOM){gpQoyCjtWz = true;}
      if(yBPesjFMYW == ZeDopGRjxx){WxIOzTuSrt = true;}
      else if(ZeDopGRjxx == yBPesjFMYW){dRXWCQZxyK = true;}
      if(fqmmrujHSj == bVmwTbxloo){ZEAlQwCrKq = true;}
      else if(bVmwTbxloo == fqmmrujHSj){YFRnSFgzBh = true;}
      if(fhEjNxiKQb == mXXtBRJAzY){CcUFfuXWle = true;}
      else if(mXXtBRJAzY == fhEjNxiKQb){eZiXaNlJRO = true;}
      if(cFYyeTdVBj == ipsYuxUHTA){SDwHdIrzst = true;}
      else if(ipsYuxUHTA == cFYyeTdVBj){CaylQSRUdt = true;}
      if(DwtcsrTLNH == mCwTlALIkG){aPHyUkKgeG = true;}
      else if(mCwTlALIkG == DwtcsrTLNH){TsizLaYbWr = true;}
      if(UWSegQxeRw == KNHseBHInX){TZMOxtbCiD = true;}
      else if(KNHseBHInX == UWSegQxeRw){VjroUEhAun = true;}
      if(AtwwtZSoIX == xRkYNkcOAV){wYfMaVHsII = true;}
      if(RNFigjnaqV == HpSoBkbDHB){ECzPQmVVkt = true;}
      if(cXwJGFmtRO == GAOrOVhzst){kpqfKsqhJj = true;}
      while(xRkYNkcOAV == AtwwtZSoIX){ePejHxGeXz = true;}
      while(HpSoBkbDHB == HpSoBkbDHB){mLVHOkpjMz = true;}
      while(GAOrOVhzst == GAOrOVhzst){oJmYsShJQL = true;}
      if(pLSwCVRXGA == true){pLSwCVRXGA = false;}
      if(WxIOzTuSrt == true){WxIOzTuSrt = false;}
      if(ZEAlQwCrKq == true){ZEAlQwCrKq = false;}
      if(CcUFfuXWle == true){CcUFfuXWle = false;}
      if(SDwHdIrzst == true){SDwHdIrzst = false;}
      if(aPHyUkKgeG == true){aPHyUkKgeG = false;}
      if(TZMOxtbCiD == true){TZMOxtbCiD = false;}
      if(wYfMaVHsII == true){wYfMaVHsII = false;}
      if(ECzPQmVVkt == true){ECzPQmVVkt = false;}
      if(kpqfKsqhJj == true){kpqfKsqhJj = false;}
      if(gpQoyCjtWz == true){gpQoyCjtWz = false;}
      if(dRXWCQZxyK == true){dRXWCQZxyK = false;}
      if(YFRnSFgzBh == true){YFRnSFgzBh = false;}
      if(eZiXaNlJRO == true){eZiXaNlJRO = false;}
      if(CaylQSRUdt == true){CaylQSRUdt = false;}
      if(TsizLaYbWr == true){TsizLaYbWr = false;}
      if(VjroUEhAun == true){VjroUEhAun = false;}
      if(ePejHxGeXz == true){ePejHxGeXz = false;}
      if(mLVHOkpjMz == true){mLVHOkpjMz = false;}
      if(oJmYsShJQL == true){oJmYsShJQL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARPSXTJTLT
{ 
  void wewdUdtRAU()
  { 
      bool QiuHZlzyFq = false;
      bool wZSGqEadci = false;
      bool HMgZfbyVBz = false;
      bool CAtKqkzeCO = false;
      bool gBtpFyDPGz = false;
      bool wimMWECVax = false;
      bool ndxFoueHOF = false;
      bool EubNCGRpTg = false;
      bool YhOBDTNhml = false;
      bool idEFZDEoBK = false;
      bool SwBAuBHYKQ = false;
      bool mLBsYFOuCU = false;
      bool gxTbWaqWmz = false;
      bool CboIObgNGC = false;
      bool LoXWzWbKfU = false;
      bool nImfdVbYdT = false;
      bool JjkLOKWrew = false;
      bool YBozIqZxcA = false;
      bool yfpSKsoIer = false;
      bool AHjlrbELIn = false;
      string hJgWDSdDuT;
      string tVIzZQULtU;
      string FGFquBannR;
      string NhhgYVtoHs;
      string BLpqGJsLDA;
      string xPHEIaDpaB;
      string roPdGMnaaD;
      string VfDAStPOkk;
      string HPjmUxadYx;
      string SDNFALuMkt;
      string VSkzdQLGkN;
      string KoFpscFcII;
      string kJBckSRyAH;
      string yDcpOodjJD;
      string kUsKmcyWLX;
      string GSDcIMQIOL;
      string zNGcPHMObE;
      string yUSFWQQppI;
      string UtlbAfzAhB;
      string YVVxEXNPue;
      if(hJgWDSdDuT == VSkzdQLGkN){QiuHZlzyFq = true;}
      else if(VSkzdQLGkN == hJgWDSdDuT){SwBAuBHYKQ = true;}
      if(tVIzZQULtU == KoFpscFcII){wZSGqEadci = true;}
      else if(KoFpscFcII == tVIzZQULtU){mLBsYFOuCU = true;}
      if(FGFquBannR == kJBckSRyAH){HMgZfbyVBz = true;}
      else if(kJBckSRyAH == FGFquBannR){gxTbWaqWmz = true;}
      if(NhhgYVtoHs == yDcpOodjJD){CAtKqkzeCO = true;}
      else if(yDcpOodjJD == NhhgYVtoHs){CboIObgNGC = true;}
      if(BLpqGJsLDA == kUsKmcyWLX){gBtpFyDPGz = true;}
      else if(kUsKmcyWLX == BLpqGJsLDA){LoXWzWbKfU = true;}
      if(xPHEIaDpaB == GSDcIMQIOL){wimMWECVax = true;}
      else if(GSDcIMQIOL == xPHEIaDpaB){nImfdVbYdT = true;}
      if(roPdGMnaaD == zNGcPHMObE){ndxFoueHOF = true;}
      else if(zNGcPHMObE == roPdGMnaaD){JjkLOKWrew = true;}
      if(VfDAStPOkk == yUSFWQQppI){EubNCGRpTg = true;}
      if(HPjmUxadYx == UtlbAfzAhB){YhOBDTNhml = true;}
      if(SDNFALuMkt == YVVxEXNPue){idEFZDEoBK = true;}
      while(yUSFWQQppI == VfDAStPOkk){YBozIqZxcA = true;}
      while(UtlbAfzAhB == UtlbAfzAhB){yfpSKsoIer = true;}
      while(YVVxEXNPue == YVVxEXNPue){AHjlrbELIn = true;}
      if(QiuHZlzyFq == true){QiuHZlzyFq = false;}
      if(wZSGqEadci == true){wZSGqEadci = false;}
      if(HMgZfbyVBz == true){HMgZfbyVBz = false;}
      if(CAtKqkzeCO == true){CAtKqkzeCO = false;}
      if(gBtpFyDPGz == true){gBtpFyDPGz = false;}
      if(wimMWECVax == true){wimMWECVax = false;}
      if(ndxFoueHOF == true){ndxFoueHOF = false;}
      if(EubNCGRpTg == true){EubNCGRpTg = false;}
      if(YhOBDTNhml == true){YhOBDTNhml = false;}
      if(idEFZDEoBK == true){idEFZDEoBK = false;}
      if(SwBAuBHYKQ == true){SwBAuBHYKQ = false;}
      if(mLBsYFOuCU == true){mLBsYFOuCU = false;}
      if(gxTbWaqWmz == true){gxTbWaqWmz = false;}
      if(CboIObgNGC == true){CboIObgNGC = false;}
      if(LoXWzWbKfU == true){LoXWzWbKfU = false;}
      if(nImfdVbYdT == true){nImfdVbYdT = false;}
      if(JjkLOKWrew == true){JjkLOKWrew = false;}
      if(YBozIqZxcA == true){YBozIqZxcA = false;}
      if(yfpSKsoIer == true){yfpSKsoIer = false;}
      if(AHjlrbELIn == true){AHjlrbELIn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRSUVAZTWZ
{ 
  void bPaQUZxgfQ()
  { 
      bool VVJLFWqJLZ = false;
      bool TceIPLsKDZ = false;
      bool tiGRlwBHVx = false;
      bool zWPZMPswWg = false;
      bool rhDSwPmupm = false;
      bool EVYUYmPqYJ = false;
      bool UinOaxMEuz = false;
      bool RxmVgMemVW = false;
      bool IGRiscyuBZ = false;
      bool ABWNMIsorz = false;
      bool DizpUGhCmM = false;
      bool IbUCANREUx = false;
      bool yRDUyQaZJY = false;
      bool SouWSZGaOl = false;
      bool uwHnRXgUNy = false;
      bool poUuAledqE = false;
      bool fIrNtTgxiZ = false;
      bool GpphCBJPDa = false;
      bool iFLLhcTAWg = false;
      bool uciKGlDssy = false;
      string iQesnRWijt;
      string bWTMgASyVd;
      string UtUYptxfyi;
      string ASSHBlZNww;
      string UIMuQENioi;
      string NBLwIouGDs;
      string UqjBsIDMLt;
      string aFCYJLgYHk;
      string gOpPUyHVzM;
      string pTKDacYKBI;
      string BAWuIIzlmw;
      string HVySLGATgt;
      string BhNyDGtyyf;
      string mVXzjfquGM;
      string zUiCEUUrqU;
      string bEdHGTmYqB;
      string NBnGIkyzhf;
      string OFMUufzKsi;
      string lCHcDiqPsQ;
      string sSDFyxgbtS;
      if(iQesnRWijt == BAWuIIzlmw){VVJLFWqJLZ = true;}
      else if(BAWuIIzlmw == iQesnRWijt){DizpUGhCmM = true;}
      if(bWTMgASyVd == HVySLGATgt){TceIPLsKDZ = true;}
      else if(HVySLGATgt == bWTMgASyVd){IbUCANREUx = true;}
      if(UtUYptxfyi == BhNyDGtyyf){tiGRlwBHVx = true;}
      else if(BhNyDGtyyf == UtUYptxfyi){yRDUyQaZJY = true;}
      if(ASSHBlZNww == mVXzjfquGM){zWPZMPswWg = true;}
      else if(mVXzjfquGM == ASSHBlZNww){SouWSZGaOl = true;}
      if(UIMuQENioi == zUiCEUUrqU){rhDSwPmupm = true;}
      else if(zUiCEUUrqU == UIMuQENioi){uwHnRXgUNy = true;}
      if(NBLwIouGDs == bEdHGTmYqB){EVYUYmPqYJ = true;}
      else if(bEdHGTmYqB == NBLwIouGDs){poUuAledqE = true;}
      if(UqjBsIDMLt == NBnGIkyzhf){UinOaxMEuz = true;}
      else if(NBnGIkyzhf == UqjBsIDMLt){fIrNtTgxiZ = true;}
      if(aFCYJLgYHk == OFMUufzKsi){RxmVgMemVW = true;}
      if(gOpPUyHVzM == lCHcDiqPsQ){IGRiscyuBZ = true;}
      if(pTKDacYKBI == sSDFyxgbtS){ABWNMIsorz = true;}
      while(OFMUufzKsi == aFCYJLgYHk){GpphCBJPDa = true;}
      while(lCHcDiqPsQ == lCHcDiqPsQ){iFLLhcTAWg = true;}
      while(sSDFyxgbtS == sSDFyxgbtS){uciKGlDssy = true;}
      if(VVJLFWqJLZ == true){VVJLFWqJLZ = false;}
      if(TceIPLsKDZ == true){TceIPLsKDZ = false;}
      if(tiGRlwBHVx == true){tiGRlwBHVx = false;}
      if(zWPZMPswWg == true){zWPZMPswWg = false;}
      if(rhDSwPmupm == true){rhDSwPmupm = false;}
      if(EVYUYmPqYJ == true){EVYUYmPqYJ = false;}
      if(UinOaxMEuz == true){UinOaxMEuz = false;}
      if(RxmVgMemVW == true){RxmVgMemVW = false;}
      if(IGRiscyuBZ == true){IGRiscyuBZ = false;}
      if(ABWNMIsorz == true){ABWNMIsorz = false;}
      if(DizpUGhCmM == true){DizpUGhCmM = false;}
      if(IbUCANREUx == true){IbUCANREUx = false;}
      if(yRDUyQaZJY == true){yRDUyQaZJY = false;}
      if(SouWSZGaOl == true){SouWSZGaOl = false;}
      if(uwHnRXgUNy == true){uwHnRXgUNy = false;}
      if(poUuAledqE == true){poUuAledqE = false;}
      if(fIrNtTgxiZ == true){fIrNtTgxiZ = false;}
      if(GpphCBJPDa == true){GpphCBJPDa = false;}
      if(iFLLhcTAWg == true){iFLLhcTAWg = false;}
      if(uciKGlDssy == true){uciKGlDssy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MBYYNTWJAI
{ 
  void pLPCPCIgUr()
  { 
      bool JjnFUCRGFH = false;
      bool tfHmIfbxOt = false;
      bool ocnXSjjHIU = false;
      bool qiHwfUHJYt = false;
      bool phtxWhiguX = false;
      bool lzXlVfuQlk = false;
      bool RKxjPLXLGm = false;
      bool XRYUDGiqBk = false;
      bool ADLjhrLUZz = false;
      bool ZqXmcfjJgK = false;
      bool JXaIATaChO = false;
      bool xEPAjOyNCX = false;
      bool ADkGMftkrX = false;
      bool WYJpbcbDiN = false;
      bool QImKCUbWDN = false;
      bool gWHIJGlTuT = false;
      bool ZpKKrYuYYG = false;
      bool ltdoGrQZEr = false;
      bool EWgdpzRAgU = false;
      bool pIIPmaxbSc = false;
      string HVVXnoDAdk;
      string QZnwWAKlpi;
      string dElyiDstNE;
      string uSrwbntmjX;
      string TpkTWRgdoB;
      string XuyeaDjWnj;
      string uImYoxhqTh;
      string FXBROmSRbR;
      string VPFLfzUNVY;
      string EXzAbKDLdZ;
      string joJHuAsfPm;
      string jRuVNfDaro;
      string cTVudhYBoE;
      string jHnBggFyQf;
      string Gnyinmcclw;
      string HbSnwQSOcN;
      string bqqLCccsog;
      string aFKMioVmGp;
      string FwPswInzEQ;
      string NpUDEOxlfK;
      if(HVVXnoDAdk == joJHuAsfPm){JjnFUCRGFH = true;}
      else if(joJHuAsfPm == HVVXnoDAdk){JXaIATaChO = true;}
      if(QZnwWAKlpi == jRuVNfDaro){tfHmIfbxOt = true;}
      else if(jRuVNfDaro == QZnwWAKlpi){xEPAjOyNCX = true;}
      if(dElyiDstNE == cTVudhYBoE){ocnXSjjHIU = true;}
      else if(cTVudhYBoE == dElyiDstNE){ADkGMftkrX = true;}
      if(uSrwbntmjX == jHnBggFyQf){qiHwfUHJYt = true;}
      else if(jHnBggFyQf == uSrwbntmjX){WYJpbcbDiN = true;}
      if(TpkTWRgdoB == Gnyinmcclw){phtxWhiguX = true;}
      else if(Gnyinmcclw == TpkTWRgdoB){QImKCUbWDN = true;}
      if(XuyeaDjWnj == HbSnwQSOcN){lzXlVfuQlk = true;}
      else if(HbSnwQSOcN == XuyeaDjWnj){gWHIJGlTuT = true;}
      if(uImYoxhqTh == bqqLCccsog){RKxjPLXLGm = true;}
      else if(bqqLCccsog == uImYoxhqTh){ZpKKrYuYYG = true;}
      if(FXBROmSRbR == aFKMioVmGp){XRYUDGiqBk = true;}
      if(VPFLfzUNVY == FwPswInzEQ){ADLjhrLUZz = true;}
      if(EXzAbKDLdZ == NpUDEOxlfK){ZqXmcfjJgK = true;}
      while(aFKMioVmGp == FXBROmSRbR){ltdoGrQZEr = true;}
      while(FwPswInzEQ == FwPswInzEQ){EWgdpzRAgU = true;}
      while(NpUDEOxlfK == NpUDEOxlfK){pIIPmaxbSc = true;}
      if(JjnFUCRGFH == true){JjnFUCRGFH = false;}
      if(tfHmIfbxOt == true){tfHmIfbxOt = false;}
      if(ocnXSjjHIU == true){ocnXSjjHIU = false;}
      if(qiHwfUHJYt == true){qiHwfUHJYt = false;}
      if(phtxWhiguX == true){phtxWhiguX = false;}
      if(lzXlVfuQlk == true){lzXlVfuQlk = false;}
      if(RKxjPLXLGm == true){RKxjPLXLGm = false;}
      if(XRYUDGiqBk == true){XRYUDGiqBk = false;}
      if(ADLjhrLUZz == true){ADLjhrLUZz = false;}
      if(ZqXmcfjJgK == true){ZqXmcfjJgK = false;}
      if(JXaIATaChO == true){JXaIATaChO = false;}
      if(xEPAjOyNCX == true){xEPAjOyNCX = false;}
      if(ADkGMftkrX == true){ADkGMftkrX = false;}
      if(WYJpbcbDiN == true){WYJpbcbDiN = false;}
      if(QImKCUbWDN == true){QImKCUbWDN = false;}
      if(gWHIJGlTuT == true){gWHIJGlTuT = false;}
      if(ZpKKrYuYYG == true){ZpKKrYuYYG = false;}
      if(ltdoGrQZEr == true){ltdoGrQZEr = false;}
      if(EWgdpzRAgU == true){EWgdpzRAgU = false;}
      if(pIIPmaxbSc == true){pIIPmaxbSc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MDAOVUGXDE
{ 
  void CYhKohyIxz()
  { 
      bool pYPLWMXrDL = false;
      bool pjWcpZziDQ = false;
      bool mzEWnHWlHE = false;
      bool wcLGrrzVKc = false;
      bool awHjxYsejT = false;
      bool akNgipTsWP = false;
      bool okjzPNXPjy = false;
      bool acYZpqqTYP = false;
      bool NrCmcKOeXB = false;
      bool XFzunoMHTi = false;
      bool AculsxMnqr = false;
      bool zAUGBxhwVF = false;
      bool zsrhZUddkA = false;
      bool djAoPkxQsf = false;
      bool yZnfCXkrsq = false;
      bool HQkOjHkMLY = false;
      bool TiCpNPzeqQ = false;
      bool zRCpGZFLeB = false;
      bool iljtsNylFH = false;
      bool zjEULPWxSm = false;
      string RaotqsOrxZ;
      string JZIVSPPidc;
      string WrFMtUJBRx;
      string GfjZicaMgS;
      string EHenIeAPll;
      string iaCzOYVcAV;
      string iNazSdpimp;
      string nDCKXPNQDO;
      string UtOfOfckLK;
      string GyMKipfeVe;
      string oQcuxeYray;
      string LFYkBoyukl;
      string BEWbjppqbh;
      string iitYZDQThi;
      string HkKMzBYbJt;
      string qkticktALH;
      string ogPsObKALx;
      string XeNCeQtJci;
      string QOhgpynLwn;
      string JQHataURxW;
      if(RaotqsOrxZ == oQcuxeYray){pYPLWMXrDL = true;}
      else if(oQcuxeYray == RaotqsOrxZ){AculsxMnqr = true;}
      if(JZIVSPPidc == LFYkBoyukl){pjWcpZziDQ = true;}
      else if(LFYkBoyukl == JZIVSPPidc){zAUGBxhwVF = true;}
      if(WrFMtUJBRx == BEWbjppqbh){mzEWnHWlHE = true;}
      else if(BEWbjppqbh == WrFMtUJBRx){zsrhZUddkA = true;}
      if(GfjZicaMgS == iitYZDQThi){wcLGrrzVKc = true;}
      else if(iitYZDQThi == GfjZicaMgS){djAoPkxQsf = true;}
      if(EHenIeAPll == HkKMzBYbJt){awHjxYsejT = true;}
      else if(HkKMzBYbJt == EHenIeAPll){yZnfCXkrsq = true;}
      if(iaCzOYVcAV == qkticktALH){akNgipTsWP = true;}
      else if(qkticktALH == iaCzOYVcAV){HQkOjHkMLY = true;}
      if(iNazSdpimp == ogPsObKALx){okjzPNXPjy = true;}
      else if(ogPsObKALx == iNazSdpimp){TiCpNPzeqQ = true;}
      if(nDCKXPNQDO == XeNCeQtJci){acYZpqqTYP = true;}
      if(UtOfOfckLK == QOhgpynLwn){NrCmcKOeXB = true;}
      if(GyMKipfeVe == JQHataURxW){XFzunoMHTi = true;}
      while(XeNCeQtJci == nDCKXPNQDO){zRCpGZFLeB = true;}
      while(QOhgpynLwn == QOhgpynLwn){iljtsNylFH = true;}
      while(JQHataURxW == JQHataURxW){zjEULPWxSm = true;}
      if(pYPLWMXrDL == true){pYPLWMXrDL = false;}
      if(pjWcpZziDQ == true){pjWcpZziDQ = false;}
      if(mzEWnHWlHE == true){mzEWnHWlHE = false;}
      if(wcLGrrzVKc == true){wcLGrrzVKc = false;}
      if(awHjxYsejT == true){awHjxYsejT = false;}
      if(akNgipTsWP == true){akNgipTsWP = false;}
      if(okjzPNXPjy == true){okjzPNXPjy = false;}
      if(acYZpqqTYP == true){acYZpqqTYP = false;}
      if(NrCmcKOeXB == true){NrCmcKOeXB = false;}
      if(XFzunoMHTi == true){XFzunoMHTi = false;}
      if(AculsxMnqr == true){AculsxMnqr = false;}
      if(zAUGBxhwVF == true){zAUGBxhwVF = false;}
      if(zsrhZUddkA == true){zsrhZUddkA = false;}
      if(djAoPkxQsf == true){djAoPkxQsf = false;}
      if(yZnfCXkrsq == true){yZnfCXkrsq = false;}
      if(HQkOjHkMLY == true){HQkOjHkMLY = false;}
      if(TiCpNPzeqQ == true){TiCpNPzeqQ = false;}
      if(zRCpGZFLeB == true){zRCpGZFLeB = false;}
      if(iljtsNylFH == true){iljtsNylFH = false;}
      if(zjEULPWxSm == true){zjEULPWxSm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFIHZNIUAG
{ 
  void VNEKbXDXgl()
  { 
      bool VPlCpXEFHd = false;
      bool UXCrFhZKnQ = false;
      bool ZbEteuptco = false;
      bool NPVKstlAkj = false;
      bool KOdnKNcCmk = false;
      bool UmVCtsLqXu = false;
      bool hJcRQEBqzL = false;
      bool uYZDGLyQjQ = false;
      bool RmHqUZtTPz = false;
      bool iuboCAlLWG = false;
      bool MkCaouNRui = false;
      bool utHHctCkxq = false;
      bool KhbAbAwkBG = false;
      bool YltdEgkfBY = false;
      bool MbYfDnnULI = false;
      bool yAOfweJByo = false;
      bool zcQoKJAdDw = false;
      bool JWjYdhIuwn = false;
      bool MbYsIXWNhZ = false;
      bool WigMYjKiVt = false;
      string fgMyyhfXEO;
      string BEreSHVIgE;
      string CPMopfCjCM;
      string gqyRzupVBj;
      string qIRiujdKce;
      string rHbbfPUXHR;
      string euUqhKFafX;
      string QzGxNtxdsF;
      string CrHXTYOWki;
      string ZSOiEwnZAk;
      string eCeFOrAeOl;
      string SqeBPmmwXI;
      string uiowxykWrR;
      string GWcHazMCJa;
      string XjHzQimMTQ;
      string IqCqouNhHQ;
      string HdlxfuNWZQ;
      string ZkmwjLaofO;
      string KYDbIOUkRe;
      string leurTtyKTU;
      if(fgMyyhfXEO == eCeFOrAeOl){VPlCpXEFHd = true;}
      else if(eCeFOrAeOl == fgMyyhfXEO){MkCaouNRui = true;}
      if(BEreSHVIgE == SqeBPmmwXI){UXCrFhZKnQ = true;}
      else if(SqeBPmmwXI == BEreSHVIgE){utHHctCkxq = true;}
      if(CPMopfCjCM == uiowxykWrR){ZbEteuptco = true;}
      else if(uiowxykWrR == CPMopfCjCM){KhbAbAwkBG = true;}
      if(gqyRzupVBj == GWcHazMCJa){NPVKstlAkj = true;}
      else if(GWcHazMCJa == gqyRzupVBj){YltdEgkfBY = true;}
      if(qIRiujdKce == XjHzQimMTQ){KOdnKNcCmk = true;}
      else if(XjHzQimMTQ == qIRiujdKce){MbYfDnnULI = true;}
      if(rHbbfPUXHR == IqCqouNhHQ){UmVCtsLqXu = true;}
      else if(IqCqouNhHQ == rHbbfPUXHR){yAOfweJByo = true;}
      if(euUqhKFafX == HdlxfuNWZQ){hJcRQEBqzL = true;}
      else if(HdlxfuNWZQ == euUqhKFafX){zcQoKJAdDw = true;}
      if(QzGxNtxdsF == ZkmwjLaofO){uYZDGLyQjQ = true;}
      if(CrHXTYOWki == KYDbIOUkRe){RmHqUZtTPz = true;}
      if(ZSOiEwnZAk == leurTtyKTU){iuboCAlLWG = true;}
      while(ZkmwjLaofO == QzGxNtxdsF){JWjYdhIuwn = true;}
      while(KYDbIOUkRe == KYDbIOUkRe){MbYsIXWNhZ = true;}
      while(leurTtyKTU == leurTtyKTU){WigMYjKiVt = true;}
      if(VPlCpXEFHd == true){VPlCpXEFHd = false;}
      if(UXCrFhZKnQ == true){UXCrFhZKnQ = false;}
      if(ZbEteuptco == true){ZbEteuptco = false;}
      if(NPVKstlAkj == true){NPVKstlAkj = false;}
      if(KOdnKNcCmk == true){KOdnKNcCmk = false;}
      if(UmVCtsLqXu == true){UmVCtsLqXu = false;}
      if(hJcRQEBqzL == true){hJcRQEBqzL = false;}
      if(uYZDGLyQjQ == true){uYZDGLyQjQ = false;}
      if(RmHqUZtTPz == true){RmHqUZtTPz = false;}
      if(iuboCAlLWG == true){iuboCAlLWG = false;}
      if(MkCaouNRui == true){MkCaouNRui = false;}
      if(utHHctCkxq == true){utHHctCkxq = false;}
      if(KhbAbAwkBG == true){KhbAbAwkBG = false;}
      if(YltdEgkfBY == true){YltdEgkfBY = false;}
      if(MbYfDnnULI == true){MbYfDnnULI = false;}
      if(yAOfweJByo == true){yAOfweJByo = false;}
      if(zcQoKJAdDw == true){zcQoKJAdDw = false;}
      if(JWjYdhIuwn == true){JWjYdhIuwn = false;}
      if(MbYsIXWNhZ == true){MbYsIXWNhZ = false;}
      if(WigMYjKiVt == true){WigMYjKiVt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKMJDIAFVA
{ 
  void WVKFdbUHxp()
  { 
      bool ZFyYnRqfji = false;
      bool MPhrkgWbPX = false;
      bool SCZzcVInoS = false;
      bool YrAdtJPgjQ = false;
      bool WUcYdegnWH = false;
      bool pdYdIXezwS = false;
      bool JDqQKUODya = false;
      bool QprzAyZBUy = false;
      bool nTQgbtTVUW = false;
      bool eQkQHTdLNJ = false;
      bool PcoupAlZcK = false;
      bool xcdxeolJnP = false;
      bool AsibwzFbrg = false;
      bool TOnLiKdVpb = false;
      bool IssKYCmmlR = false;
      bool hTWxIVtNzp = false;
      bool tKhwpioROT = false;
      bool KPSLHHzXCs = false;
      bool MRoZzAqpDM = false;
      bool QQWAgyLxTp = false;
      string GCDshVgfxX;
      string JnaAgVRHuW;
      string KyuWNjufMC;
      string fOsLeoZwbk;
      string qNRexLTHOz;
      string TKISkIHfex;
      string ZBSurtuOVq;
      string wUfJewfPZC;
      string PnRMhUGZaW;
      string gsRdLptVmC;
      string PElWDyeymn;
      string brFchliGMW;
      string mUnzJCDBxo;
      string CJcWlKBtJj;
      string pHmmtomowY;
      string GnIPPuQmMA;
      string ucBykSOhpW;
      string jowcffhBEU;
      string OOFYhNAMHq;
      string tOgInNGoBa;
      if(GCDshVgfxX == PElWDyeymn){ZFyYnRqfji = true;}
      else if(PElWDyeymn == GCDshVgfxX){PcoupAlZcK = true;}
      if(JnaAgVRHuW == brFchliGMW){MPhrkgWbPX = true;}
      else if(brFchliGMW == JnaAgVRHuW){xcdxeolJnP = true;}
      if(KyuWNjufMC == mUnzJCDBxo){SCZzcVInoS = true;}
      else if(mUnzJCDBxo == KyuWNjufMC){AsibwzFbrg = true;}
      if(fOsLeoZwbk == CJcWlKBtJj){YrAdtJPgjQ = true;}
      else if(CJcWlKBtJj == fOsLeoZwbk){TOnLiKdVpb = true;}
      if(qNRexLTHOz == pHmmtomowY){WUcYdegnWH = true;}
      else if(pHmmtomowY == qNRexLTHOz){IssKYCmmlR = true;}
      if(TKISkIHfex == GnIPPuQmMA){pdYdIXezwS = true;}
      else if(GnIPPuQmMA == TKISkIHfex){hTWxIVtNzp = true;}
      if(ZBSurtuOVq == ucBykSOhpW){JDqQKUODya = true;}
      else if(ucBykSOhpW == ZBSurtuOVq){tKhwpioROT = true;}
      if(wUfJewfPZC == jowcffhBEU){QprzAyZBUy = true;}
      if(PnRMhUGZaW == OOFYhNAMHq){nTQgbtTVUW = true;}
      if(gsRdLptVmC == tOgInNGoBa){eQkQHTdLNJ = true;}
      while(jowcffhBEU == wUfJewfPZC){KPSLHHzXCs = true;}
      while(OOFYhNAMHq == OOFYhNAMHq){MRoZzAqpDM = true;}
      while(tOgInNGoBa == tOgInNGoBa){QQWAgyLxTp = true;}
      if(ZFyYnRqfji == true){ZFyYnRqfji = false;}
      if(MPhrkgWbPX == true){MPhrkgWbPX = false;}
      if(SCZzcVInoS == true){SCZzcVInoS = false;}
      if(YrAdtJPgjQ == true){YrAdtJPgjQ = false;}
      if(WUcYdegnWH == true){WUcYdegnWH = false;}
      if(pdYdIXezwS == true){pdYdIXezwS = false;}
      if(JDqQKUODya == true){JDqQKUODya = false;}
      if(QprzAyZBUy == true){QprzAyZBUy = false;}
      if(nTQgbtTVUW == true){nTQgbtTVUW = false;}
      if(eQkQHTdLNJ == true){eQkQHTdLNJ = false;}
      if(PcoupAlZcK == true){PcoupAlZcK = false;}
      if(xcdxeolJnP == true){xcdxeolJnP = false;}
      if(AsibwzFbrg == true){AsibwzFbrg = false;}
      if(TOnLiKdVpb == true){TOnLiKdVpb = false;}
      if(IssKYCmmlR == true){IssKYCmmlR = false;}
      if(hTWxIVtNzp == true){hTWxIVtNzp = false;}
      if(tKhwpioROT == true){tKhwpioROT = false;}
      if(KPSLHHzXCs == true){KPSLHHzXCs = false;}
      if(MRoZzAqpDM == true){MRoZzAqpDM = false;}
      if(QQWAgyLxTp == true){QQWAgyLxTp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVHXHKAPMZ
{ 
  void eVsaobfBdl()
  { 
      bool QmVGteTeIn = false;
      bool HufTMjBtzS = false;
      bool CgBUcWMaTd = false;
      bool MtuFdIFMdo = false;
      bool jMPhVYpzqQ = false;
      bool SuUQMjlBcW = false;
      bool SsKdaMAZoD = false;
      bool eoPKipQSzD = false;
      bool gMjCKQZers = false;
      bool WEiHWqBkGJ = false;
      bool YPJmldeKgW = false;
      bool SSBYoFJITJ = false;
      bool lVhugZFImr = false;
      bool neLoeRDwPg = false;
      bool lPxVaDCJRR = false;
      bool grRxWDhNFM = false;
      bool XWWohmGMtX = false;
      bool CMrlXWXLUd = false;
      bool WwpUKuNOSb = false;
      bool joqDIOrInm = false;
      string eyEZqUmFMK;
      string boHblqQSkC;
      string qTnIynDMoD;
      string pftpEPpxzU;
      string yCsOwVdBAP;
      string dKsELLJubC;
      string RZPJTwtQWV;
      string ASTPEnaZMb;
      string JBMZYflods;
      string FtUxDXmjtA;
      string aNdeOKqdAX;
      string jjizsPNojm;
      string JEldQGxWLf;
      string BqeLAuWgLO;
      string oHoGIVKVDm;
      string KxzGpWaAOI;
      string MUSUWsEWzx;
      string sfdUyCOeUt;
      string ubSXUDqXVd;
      string UVSDBUoUjO;
      if(eyEZqUmFMK == aNdeOKqdAX){QmVGteTeIn = true;}
      else if(aNdeOKqdAX == eyEZqUmFMK){YPJmldeKgW = true;}
      if(boHblqQSkC == jjizsPNojm){HufTMjBtzS = true;}
      else if(jjizsPNojm == boHblqQSkC){SSBYoFJITJ = true;}
      if(qTnIynDMoD == JEldQGxWLf){CgBUcWMaTd = true;}
      else if(JEldQGxWLf == qTnIynDMoD){lVhugZFImr = true;}
      if(pftpEPpxzU == BqeLAuWgLO){MtuFdIFMdo = true;}
      else if(BqeLAuWgLO == pftpEPpxzU){neLoeRDwPg = true;}
      if(yCsOwVdBAP == oHoGIVKVDm){jMPhVYpzqQ = true;}
      else if(oHoGIVKVDm == yCsOwVdBAP){lPxVaDCJRR = true;}
      if(dKsELLJubC == KxzGpWaAOI){SuUQMjlBcW = true;}
      else if(KxzGpWaAOI == dKsELLJubC){grRxWDhNFM = true;}
      if(RZPJTwtQWV == MUSUWsEWzx){SsKdaMAZoD = true;}
      else if(MUSUWsEWzx == RZPJTwtQWV){XWWohmGMtX = true;}
      if(ASTPEnaZMb == sfdUyCOeUt){eoPKipQSzD = true;}
      if(JBMZYflods == ubSXUDqXVd){gMjCKQZers = true;}
      if(FtUxDXmjtA == UVSDBUoUjO){WEiHWqBkGJ = true;}
      while(sfdUyCOeUt == ASTPEnaZMb){CMrlXWXLUd = true;}
      while(ubSXUDqXVd == ubSXUDqXVd){WwpUKuNOSb = true;}
      while(UVSDBUoUjO == UVSDBUoUjO){joqDIOrInm = true;}
      if(QmVGteTeIn == true){QmVGteTeIn = false;}
      if(HufTMjBtzS == true){HufTMjBtzS = false;}
      if(CgBUcWMaTd == true){CgBUcWMaTd = false;}
      if(MtuFdIFMdo == true){MtuFdIFMdo = false;}
      if(jMPhVYpzqQ == true){jMPhVYpzqQ = false;}
      if(SuUQMjlBcW == true){SuUQMjlBcW = false;}
      if(SsKdaMAZoD == true){SsKdaMAZoD = false;}
      if(eoPKipQSzD == true){eoPKipQSzD = false;}
      if(gMjCKQZers == true){gMjCKQZers = false;}
      if(WEiHWqBkGJ == true){WEiHWqBkGJ = false;}
      if(YPJmldeKgW == true){YPJmldeKgW = false;}
      if(SSBYoFJITJ == true){SSBYoFJITJ = false;}
      if(lVhugZFImr == true){lVhugZFImr = false;}
      if(neLoeRDwPg == true){neLoeRDwPg = false;}
      if(lPxVaDCJRR == true){lPxVaDCJRR = false;}
      if(grRxWDhNFM == true){grRxWDhNFM = false;}
      if(XWWohmGMtX == true){XWWohmGMtX = false;}
      if(CMrlXWXLUd == true){CMrlXWXLUd = false;}
      if(WwpUKuNOSb == true){WwpUKuNOSb = false;}
      if(joqDIOrInm == true){joqDIOrInm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMSWUGPKBK
{ 
  void DSnZJuJywD()
  { 
      bool ibcwaBrGQQ = false;
      bool AtqaPLzfpd = false;
      bool dxkakMlpbI = false;
      bool CelcswXaQm = false;
      bool HswxxFuyTl = false;
      bool AsOcBlqCLO = false;
      bool PCdHNVHNhS = false;
      bool mXPCVjAnde = false;
      bool RmVpIIQJbH = false;
      bool FUPCXEPoib = false;
      bool xgQAycdMGQ = false;
      bool kCYfwcgnzF = false;
      bool FylZNSIMdR = false;
      bool ULEBgkVVqe = false;
      bool eDCKWCwiFu = false;
      bool XaodWztqlf = false;
      bool TQhowYxWyL = false;
      bool GKwTZBwbDL = false;
      bool WYHissWaeh = false;
      bool pejKKNUMNy = false;
      string jkdeUBzaQd;
      string UAYNJiWCiM;
      string xanChnJBWF;
      string tHLLcqGInE;
      string DRcqesgDtO;
      string erTrcIwbxg;
      string ryEKjMnNkS;
      string cONdJfywXn;
      string HFGIZCmThT;
      string tdLHMFNRHR;
      string FSSblPdoiw;
      string KzEIZlqujg;
      string ZTeRXyDGRD;
      string SgnFinmeWK;
      string XxjkItZChZ;
      string ORgarknAEm;
      string MXXeddLyYk;
      string zMYZJbjsIc;
      string XBXqoAzNNy;
      string AlZixAZEGe;
      if(jkdeUBzaQd == FSSblPdoiw){ibcwaBrGQQ = true;}
      else if(FSSblPdoiw == jkdeUBzaQd){xgQAycdMGQ = true;}
      if(UAYNJiWCiM == KzEIZlqujg){AtqaPLzfpd = true;}
      else if(KzEIZlqujg == UAYNJiWCiM){kCYfwcgnzF = true;}
      if(xanChnJBWF == ZTeRXyDGRD){dxkakMlpbI = true;}
      else if(ZTeRXyDGRD == xanChnJBWF){FylZNSIMdR = true;}
      if(tHLLcqGInE == SgnFinmeWK){CelcswXaQm = true;}
      else if(SgnFinmeWK == tHLLcqGInE){ULEBgkVVqe = true;}
      if(DRcqesgDtO == XxjkItZChZ){HswxxFuyTl = true;}
      else if(XxjkItZChZ == DRcqesgDtO){eDCKWCwiFu = true;}
      if(erTrcIwbxg == ORgarknAEm){AsOcBlqCLO = true;}
      else if(ORgarknAEm == erTrcIwbxg){XaodWztqlf = true;}
      if(ryEKjMnNkS == MXXeddLyYk){PCdHNVHNhS = true;}
      else if(MXXeddLyYk == ryEKjMnNkS){TQhowYxWyL = true;}
      if(cONdJfywXn == zMYZJbjsIc){mXPCVjAnde = true;}
      if(HFGIZCmThT == XBXqoAzNNy){RmVpIIQJbH = true;}
      if(tdLHMFNRHR == AlZixAZEGe){FUPCXEPoib = true;}
      while(zMYZJbjsIc == cONdJfywXn){GKwTZBwbDL = true;}
      while(XBXqoAzNNy == XBXqoAzNNy){WYHissWaeh = true;}
      while(AlZixAZEGe == AlZixAZEGe){pejKKNUMNy = true;}
      if(ibcwaBrGQQ == true){ibcwaBrGQQ = false;}
      if(AtqaPLzfpd == true){AtqaPLzfpd = false;}
      if(dxkakMlpbI == true){dxkakMlpbI = false;}
      if(CelcswXaQm == true){CelcswXaQm = false;}
      if(HswxxFuyTl == true){HswxxFuyTl = false;}
      if(AsOcBlqCLO == true){AsOcBlqCLO = false;}
      if(PCdHNVHNhS == true){PCdHNVHNhS = false;}
      if(mXPCVjAnde == true){mXPCVjAnde = false;}
      if(RmVpIIQJbH == true){RmVpIIQJbH = false;}
      if(FUPCXEPoib == true){FUPCXEPoib = false;}
      if(xgQAycdMGQ == true){xgQAycdMGQ = false;}
      if(kCYfwcgnzF == true){kCYfwcgnzF = false;}
      if(FylZNSIMdR == true){FylZNSIMdR = false;}
      if(ULEBgkVVqe == true){ULEBgkVVqe = false;}
      if(eDCKWCwiFu == true){eDCKWCwiFu = false;}
      if(XaodWztqlf == true){XaodWztqlf = false;}
      if(TQhowYxWyL == true){TQhowYxWyL = false;}
      if(GKwTZBwbDL == true){GKwTZBwbDL = false;}
      if(WYHissWaeh == true){WYHissWaeh = false;}
      if(pejKKNUMNy == true){pejKKNUMNy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRGCRPRNHI
{ 
  void UCWxtJgwdh()
  { 
      bool HXAwpweSEl = false;
      bool rQnLrFFNaw = false;
      bool rOXUkAdZWx = false;
      bool ZkrBtihWrG = false;
      bool JGkQgCnfMs = false;
      bool EQFUdrzeKp = false;
      bool REwGMGXmQJ = false;
      bool WiUTmkcHni = false;
      bool LxMdrJeXXB = false;
      bool jDLCoEKeEZ = false;
      bool dBODVVulhr = false;
      bool OqqbdTqRNC = false;
      bool azPOYTXSeh = false;
      bool ayDNEKiJIW = false;
      bool OspelrMiXU = false;
      bool MrQBzdlzdC = false;
      bool xbGzQQncWT = false;
      bool khJpmgJjcg = false;
      bool HnuKUigBOa = false;
      bool XieGZmmqNV = false;
      string WAZElCGsuO;
      string RRNxRifrLX;
      string rcknBKUuue;
      string qOcRPiGbZV;
      string GuPcYdgGLi;
      string XMoQgtPkCa;
      string hLyQWDowgi;
      string bESpQwNIPX;
      string dOiMHdYLkU;
      string TUZymuxyFU;
      string nkYcGTtyAj;
      string gHVdxTclJs;
      string ddKLOGeTCV;
      string zOCtjspGFm;
      string jZLBnMzuAT;
      string SLoMqKZMNz;
      string oZwdjREbtE;
      string dVfVIESJXC;
      string HiThDnZpDY;
      string ScrFyKdgQV;
      if(WAZElCGsuO == nkYcGTtyAj){HXAwpweSEl = true;}
      else if(nkYcGTtyAj == WAZElCGsuO){dBODVVulhr = true;}
      if(RRNxRifrLX == gHVdxTclJs){rQnLrFFNaw = true;}
      else if(gHVdxTclJs == RRNxRifrLX){OqqbdTqRNC = true;}
      if(rcknBKUuue == ddKLOGeTCV){rOXUkAdZWx = true;}
      else if(ddKLOGeTCV == rcknBKUuue){azPOYTXSeh = true;}
      if(qOcRPiGbZV == zOCtjspGFm){ZkrBtihWrG = true;}
      else if(zOCtjspGFm == qOcRPiGbZV){ayDNEKiJIW = true;}
      if(GuPcYdgGLi == jZLBnMzuAT){JGkQgCnfMs = true;}
      else if(jZLBnMzuAT == GuPcYdgGLi){OspelrMiXU = true;}
      if(XMoQgtPkCa == SLoMqKZMNz){EQFUdrzeKp = true;}
      else if(SLoMqKZMNz == XMoQgtPkCa){MrQBzdlzdC = true;}
      if(hLyQWDowgi == oZwdjREbtE){REwGMGXmQJ = true;}
      else if(oZwdjREbtE == hLyQWDowgi){xbGzQQncWT = true;}
      if(bESpQwNIPX == dVfVIESJXC){WiUTmkcHni = true;}
      if(dOiMHdYLkU == HiThDnZpDY){LxMdrJeXXB = true;}
      if(TUZymuxyFU == ScrFyKdgQV){jDLCoEKeEZ = true;}
      while(dVfVIESJXC == bESpQwNIPX){khJpmgJjcg = true;}
      while(HiThDnZpDY == HiThDnZpDY){HnuKUigBOa = true;}
      while(ScrFyKdgQV == ScrFyKdgQV){XieGZmmqNV = true;}
      if(HXAwpweSEl == true){HXAwpweSEl = false;}
      if(rQnLrFFNaw == true){rQnLrFFNaw = false;}
      if(rOXUkAdZWx == true){rOXUkAdZWx = false;}
      if(ZkrBtihWrG == true){ZkrBtihWrG = false;}
      if(JGkQgCnfMs == true){JGkQgCnfMs = false;}
      if(EQFUdrzeKp == true){EQFUdrzeKp = false;}
      if(REwGMGXmQJ == true){REwGMGXmQJ = false;}
      if(WiUTmkcHni == true){WiUTmkcHni = false;}
      if(LxMdrJeXXB == true){LxMdrJeXXB = false;}
      if(jDLCoEKeEZ == true){jDLCoEKeEZ = false;}
      if(dBODVVulhr == true){dBODVVulhr = false;}
      if(OqqbdTqRNC == true){OqqbdTqRNC = false;}
      if(azPOYTXSeh == true){azPOYTXSeh = false;}
      if(ayDNEKiJIW == true){ayDNEKiJIW = false;}
      if(OspelrMiXU == true){OspelrMiXU = false;}
      if(MrQBzdlzdC == true){MrQBzdlzdC = false;}
      if(xbGzQQncWT == true){xbGzQQncWT = false;}
      if(khJpmgJjcg == true){khJpmgJjcg = false;}
      if(HnuKUigBOa == true){HnuKUigBOa = false;}
      if(XieGZmmqNV == true){XieGZmmqNV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCNKJVLTRF
{ 
  void EsIMrsLnxH()
  { 
      bool RkyKErVsab = false;
      bool BbxxSSMsyi = false;
      bool eksuUQWAYd = false;
      bool puuNFMLUmq = false;
      bool GaMtxDWRPr = false;
      bool CUQFrfrDon = false;
      bool VUUxkGfiqF = false;
      bool HqFHbEYyyQ = false;
      bool tFjfaVepVZ = false;
      bool UIfzUlFOJq = false;
      bool XmZJkKPIcn = false;
      bool HtEYsQjoVP = false;
      bool apNRkyLFlp = false;
      bool yJnGsHeatQ = false;
      bool FVMhRZDGGE = false;
      bool BQrsPhYIXm = false;
      bool yKVloxFxfk = false;
      bool kJtFJEcfzL = false;
      bool tEyhohRuqK = false;
      bool hVCHRuAZrT = false;
      string CBGsBPgHyN;
      string aJmIUAnghI;
      string KAqxFSbpFD;
      string UCGIZidllT;
      string royNIXccVm;
      string hdiMNBKImh;
      string nqBurXCeil;
      string VBtOPUCcog;
      string pyTSVqTttX;
      string XVyDeBnDUk;
      string VxtjRfiUws;
      string zgTFroWiYA;
      string DIkKOACpiN;
      string gzIDLrDjAo;
      string HzxAYpBrKp;
      string eEdTgMMjUR;
      string crkhLAYPtA;
      string klijsEKjlX;
      string yKfricUnWy;
      string fTPiLONPoX;
      if(CBGsBPgHyN == VxtjRfiUws){RkyKErVsab = true;}
      else if(VxtjRfiUws == CBGsBPgHyN){XmZJkKPIcn = true;}
      if(aJmIUAnghI == zgTFroWiYA){BbxxSSMsyi = true;}
      else if(zgTFroWiYA == aJmIUAnghI){HtEYsQjoVP = true;}
      if(KAqxFSbpFD == DIkKOACpiN){eksuUQWAYd = true;}
      else if(DIkKOACpiN == KAqxFSbpFD){apNRkyLFlp = true;}
      if(UCGIZidllT == gzIDLrDjAo){puuNFMLUmq = true;}
      else if(gzIDLrDjAo == UCGIZidllT){yJnGsHeatQ = true;}
      if(royNIXccVm == HzxAYpBrKp){GaMtxDWRPr = true;}
      else if(HzxAYpBrKp == royNIXccVm){FVMhRZDGGE = true;}
      if(hdiMNBKImh == eEdTgMMjUR){CUQFrfrDon = true;}
      else if(eEdTgMMjUR == hdiMNBKImh){BQrsPhYIXm = true;}
      if(nqBurXCeil == crkhLAYPtA){VUUxkGfiqF = true;}
      else if(crkhLAYPtA == nqBurXCeil){yKVloxFxfk = true;}
      if(VBtOPUCcog == klijsEKjlX){HqFHbEYyyQ = true;}
      if(pyTSVqTttX == yKfricUnWy){tFjfaVepVZ = true;}
      if(XVyDeBnDUk == fTPiLONPoX){UIfzUlFOJq = true;}
      while(klijsEKjlX == VBtOPUCcog){kJtFJEcfzL = true;}
      while(yKfricUnWy == yKfricUnWy){tEyhohRuqK = true;}
      while(fTPiLONPoX == fTPiLONPoX){hVCHRuAZrT = true;}
      if(RkyKErVsab == true){RkyKErVsab = false;}
      if(BbxxSSMsyi == true){BbxxSSMsyi = false;}
      if(eksuUQWAYd == true){eksuUQWAYd = false;}
      if(puuNFMLUmq == true){puuNFMLUmq = false;}
      if(GaMtxDWRPr == true){GaMtxDWRPr = false;}
      if(CUQFrfrDon == true){CUQFrfrDon = false;}
      if(VUUxkGfiqF == true){VUUxkGfiqF = false;}
      if(HqFHbEYyyQ == true){HqFHbEYyyQ = false;}
      if(tFjfaVepVZ == true){tFjfaVepVZ = false;}
      if(UIfzUlFOJq == true){UIfzUlFOJq = false;}
      if(XmZJkKPIcn == true){XmZJkKPIcn = false;}
      if(HtEYsQjoVP == true){HtEYsQjoVP = false;}
      if(apNRkyLFlp == true){apNRkyLFlp = false;}
      if(yJnGsHeatQ == true){yJnGsHeatQ = false;}
      if(FVMhRZDGGE == true){FVMhRZDGGE = false;}
      if(BQrsPhYIXm == true){BQrsPhYIXm = false;}
      if(yKVloxFxfk == true){yKVloxFxfk = false;}
      if(kJtFJEcfzL == true){kJtFJEcfzL = false;}
      if(tEyhohRuqK == true){tEyhohRuqK = false;}
      if(hVCHRuAZrT == true){hVCHRuAZrT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBSCUNUDTE
{ 
  void XPSoBrAxZe()
  { 
      bool lwDdYQUpjA = false;
      bool BLXTIwnqXQ = false;
      bool tjCWZCVLML = false;
      bool qLsXVPGQhw = false;
      bool OmpFqQqIxx = false;
      bool RHFGnBsfDW = false;
      bool tIcYIpRzxr = false;
      bool pXIbBHtxfJ = false;
      bool KNOPsjFmjU = false;
      bool WZMKBGJRwB = false;
      bool yqLFHtydEf = false;
      bool HwAtMgtNeX = false;
      bool jePcUPKyZu = false;
      bool ybAdLTBJHz = false;
      bool lbhDMaYSyT = false;
      bool LumYQTbijq = false;
      bool jADJheuVhs = false;
      bool ekGelHwLPt = false;
      bool pqAGiCoaMq = false;
      bool qSYQPlXYVg = false;
      string hsOzzwzfxp;
      string bKOnJQCcHq;
      string qLOjOXwMZL;
      string dtcbXQoFOE;
      string BmlYKeDIaN;
      string eaABdVeeka;
      string AmGkMgglPr;
      string axOCoEZpZi;
      string UmlMgCtaxC;
      string lJUmEOgAMc;
      string yQrhlhLxLY;
      string woFBGMBsEJ;
      string mFoMGQbbya;
      string XYdwkDuDay;
      string pwPXGxESgq;
      string NmwCprbebU;
      string FjykBXLIPC;
      string RxRFSppQGI;
      string MJuHMjcaFs;
      string bPbFsGydWi;
      if(hsOzzwzfxp == yQrhlhLxLY){lwDdYQUpjA = true;}
      else if(yQrhlhLxLY == hsOzzwzfxp){yqLFHtydEf = true;}
      if(bKOnJQCcHq == woFBGMBsEJ){BLXTIwnqXQ = true;}
      else if(woFBGMBsEJ == bKOnJQCcHq){HwAtMgtNeX = true;}
      if(qLOjOXwMZL == mFoMGQbbya){tjCWZCVLML = true;}
      else if(mFoMGQbbya == qLOjOXwMZL){jePcUPKyZu = true;}
      if(dtcbXQoFOE == XYdwkDuDay){qLsXVPGQhw = true;}
      else if(XYdwkDuDay == dtcbXQoFOE){ybAdLTBJHz = true;}
      if(BmlYKeDIaN == pwPXGxESgq){OmpFqQqIxx = true;}
      else if(pwPXGxESgq == BmlYKeDIaN){lbhDMaYSyT = true;}
      if(eaABdVeeka == NmwCprbebU){RHFGnBsfDW = true;}
      else if(NmwCprbebU == eaABdVeeka){LumYQTbijq = true;}
      if(AmGkMgglPr == FjykBXLIPC){tIcYIpRzxr = true;}
      else if(FjykBXLIPC == AmGkMgglPr){jADJheuVhs = true;}
      if(axOCoEZpZi == RxRFSppQGI){pXIbBHtxfJ = true;}
      if(UmlMgCtaxC == MJuHMjcaFs){KNOPsjFmjU = true;}
      if(lJUmEOgAMc == bPbFsGydWi){WZMKBGJRwB = true;}
      while(RxRFSppQGI == axOCoEZpZi){ekGelHwLPt = true;}
      while(MJuHMjcaFs == MJuHMjcaFs){pqAGiCoaMq = true;}
      while(bPbFsGydWi == bPbFsGydWi){qSYQPlXYVg = true;}
      if(lwDdYQUpjA == true){lwDdYQUpjA = false;}
      if(BLXTIwnqXQ == true){BLXTIwnqXQ = false;}
      if(tjCWZCVLML == true){tjCWZCVLML = false;}
      if(qLsXVPGQhw == true){qLsXVPGQhw = false;}
      if(OmpFqQqIxx == true){OmpFqQqIxx = false;}
      if(RHFGnBsfDW == true){RHFGnBsfDW = false;}
      if(tIcYIpRzxr == true){tIcYIpRzxr = false;}
      if(pXIbBHtxfJ == true){pXIbBHtxfJ = false;}
      if(KNOPsjFmjU == true){KNOPsjFmjU = false;}
      if(WZMKBGJRwB == true){WZMKBGJRwB = false;}
      if(yqLFHtydEf == true){yqLFHtydEf = false;}
      if(HwAtMgtNeX == true){HwAtMgtNeX = false;}
      if(jePcUPKyZu == true){jePcUPKyZu = false;}
      if(ybAdLTBJHz == true){ybAdLTBJHz = false;}
      if(lbhDMaYSyT == true){lbhDMaYSyT = false;}
      if(LumYQTbijq == true){LumYQTbijq = false;}
      if(jADJheuVhs == true){jADJheuVhs = false;}
      if(ekGelHwLPt == true){ekGelHwLPt = false;}
      if(pqAGiCoaMq == true){pqAGiCoaMq = false;}
      if(qSYQPlXYVg == true){qSYQPlXYVg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QRNRVDLIYD
{ 
  void SDGpQCSodU()
  { 
      bool PoodlrEBut = false;
      bool PQyLSJEhNw = false;
      bool EkQZVtIGKd = false;
      bool tIgeEuyGlC = false;
      bool DxEjaNUwlK = false;
      bool FqwUOdYPIq = false;
      bool jxqRAHjTGW = false;
      bool KywLsGgfzI = false;
      bool ZLUzXCMMQa = false;
      bool VixtRFFmjT = false;
      bool cBoOAHujaH = false;
      bool xrPARXcqsx = false;
      bool tXCfAaBCtm = false;
      bool AtueeYWGzQ = false;
      bool HbkIcdTxbs = false;
      bool cOsmYFyJNY = false;
      bool GrpnGDxkUs = false;
      bool BWqboSltCW = false;
      bool HEZAKlAIGZ = false;
      bool aMraKOkxCZ = false;
      string nJMXKbipIq;
      string odARxFfmkb;
      string ixdVjjSmtz;
      string xiLftDNlyl;
      string JdmTRnEmwP;
      string mraegqfpnZ;
      string JuwJtGRTWs;
      string rsnzSEJJDw;
      string efqeLEHfyD;
      string XWyYbNgdZL;
      string VkPCXsEbMb;
      string hVmqtcERxo;
      string ylUTVUuOWE;
      string WejqZtPnGS;
      string AeSWVBjGdz;
      string JPfjNiPwfC;
      string yoFIECkuQA;
      string NQKeoSSyyU;
      string jnjXuHyAdq;
      string dSHEUKYKRS;
      if(nJMXKbipIq == VkPCXsEbMb){PoodlrEBut = true;}
      else if(VkPCXsEbMb == nJMXKbipIq){cBoOAHujaH = true;}
      if(odARxFfmkb == hVmqtcERxo){PQyLSJEhNw = true;}
      else if(hVmqtcERxo == odARxFfmkb){xrPARXcqsx = true;}
      if(ixdVjjSmtz == ylUTVUuOWE){EkQZVtIGKd = true;}
      else if(ylUTVUuOWE == ixdVjjSmtz){tXCfAaBCtm = true;}
      if(xiLftDNlyl == WejqZtPnGS){tIgeEuyGlC = true;}
      else if(WejqZtPnGS == xiLftDNlyl){AtueeYWGzQ = true;}
      if(JdmTRnEmwP == AeSWVBjGdz){DxEjaNUwlK = true;}
      else if(AeSWVBjGdz == JdmTRnEmwP){HbkIcdTxbs = true;}
      if(mraegqfpnZ == JPfjNiPwfC){FqwUOdYPIq = true;}
      else if(JPfjNiPwfC == mraegqfpnZ){cOsmYFyJNY = true;}
      if(JuwJtGRTWs == yoFIECkuQA){jxqRAHjTGW = true;}
      else if(yoFIECkuQA == JuwJtGRTWs){GrpnGDxkUs = true;}
      if(rsnzSEJJDw == NQKeoSSyyU){KywLsGgfzI = true;}
      if(efqeLEHfyD == jnjXuHyAdq){ZLUzXCMMQa = true;}
      if(XWyYbNgdZL == dSHEUKYKRS){VixtRFFmjT = true;}
      while(NQKeoSSyyU == rsnzSEJJDw){BWqboSltCW = true;}
      while(jnjXuHyAdq == jnjXuHyAdq){HEZAKlAIGZ = true;}
      while(dSHEUKYKRS == dSHEUKYKRS){aMraKOkxCZ = true;}
      if(PoodlrEBut == true){PoodlrEBut = false;}
      if(PQyLSJEhNw == true){PQyLSJEhNw = false;}
      if(EkQZVtIGKd == true){EkQZVtIGKd = false;}
      if(tIgeEuyGlC == true){tIgeEuyGlC = false;}
      if(DxEjaNUwlK == true){DxEjaNUwlK = false;}
      if(FqwUOdYPIq == true){FqwUOdYPIq = false;}
      if(jxqRAHjTGW == true){jxqRAHjTGW = false;}
      if(KywLsGgfzI == true){KywLsGgfzI = false;}
      if(ZLUzXCMMQa == true){ZLUzXCMMQa = false;}
      if(VixtRFFmjT == true){VixtRFFmjT = false;}
      if(cBoOAHujaH == true){cBoOAHujaH = false;}
      if(xrPARXcqsx == true){xrPARXcqsx = false;}
      if(tXCfAaBCtm == true){tXCfAaBCtm = false;}
      if(AtueeYWGzQ == true){AtueeYWGzQ = false;}
      if(HbkIcdTxbs == true){HbkIcdTxbs = false;}
      if(cOsmYFyJNY == true){cOsmYFyJNY = false;}
      if(GrpnGDxkUs == true){GrpnGDxkUs = false;}
      if(BWqboSltCW == true){BWqboSltCW = false;}
      if(HEZAKlAIGZ == true){HEZAKlAIGZ = false;}
      if(aMraKOkxCZ == true){aMraKOkxCZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MCLJXCYDPT
{ 
  void IKrYVquQpM()
  { 
      bool VrMtnDiUOj = false;
      bool KKrHSiBqUQ = false;
      bool IfikuLhfWb = false;
      bool iisRCYQgqt = false;
      bool qJCtEEAjdA = false;
      bool IQqAEpIayb = false;
      bool VCylAaQZFt = false;
      bool SUzZZzcogp = false;
      bool LxCVSSrrNL = false;
      bool PohPYnLQsd = false;
      bool nZeignQQZF = false;
      bool MStHQXAbTh = false;
      bool iYMsdcljBk = false;
      bool nMuDCkSSod = false;
      bool BaRIzxuayB = false;
      bool mixLtONlFD = false;
      bool CgPnQAXqEe = false;
      bool FhmofIGDtg = false;
      bool hKkzxEPjIm = false;
      bool WfMkbUKcqy = false;
      string nnCQshrjcx;
      string tgeqRliBlb;
      string XNgjqWtwnb;
      string fCcWTppJVB;
      string XQepkmwaAB;
      string cmeBjaGRZV;
      string nuuBRqEHXb;
      string uZfkEGiqzD;
      string ZTwlysXbmr;
      string iYiANbUcYt;
      string hoDXGCHtwc;
      string rPSVuUyJCX;
      string TbTerWpeXb;
      string lFREVjQXfw;
      string lcfJATFNEr;
      string dLaAZGUXfi;
      string MbVTqmxNAK;
      string EZcGlpwKeY;
      string QcaeyZdRdO;
      string OrrwiKHMRM;
      if(nnCQshrjcx == hoDXGCHtwc){VrMtnDiUOj = true;}
      else if(hoDXGCHtwc == nnCQshrjcx){nZeignQQZF = true;}
      if(tgeqRliBlb == rPSVuUyJCX){KKrHSiBqUQ = true;}
      else if(rPSVuUyJCX == tgeqRliBlb){MStHQXAbTh = true;}
      if(XNgjqWtwnb == TbTerWpeXb){IfikuLhfWb = true;}
      else if(TbTerWpeXb == XNgjqWtwnb){iYMsdcljBk = true;}
      if(fCcWTppJVB == lFREVjQXfw){iisRCYQgqt = true;}
      else if(lFREVjQXfw == fCcWTppJVB){nMuDCkSSod = true;}
      if(XQepkmwaAB == lcfJATFNEr){qJCtEEAjdA = true;}
      else if(lcfJATFNEr == XQepkmwaAB){BaRIzxuayB = true;}
      if(cmeBjaGRZV == dLaAZGUXfi){IQqAEpIayb = true;}
      else if(dLaAZGUXfi == cmeBjaGRZV){mixLtONlFD = true;}
      if(nuuBRqEHXb == MbVTqmxNAK){VCylAaQZFt = true;}
      else if(MbVTqmxNAK == nuuBRqEHXb){CgPnQAXqEe = true;}
      if(uZfkEGiqzD == EZcGlpwKeY){SUzZZzcogp = true;}
      if(ZTwlysXbmr == QcaeyZdRdO){LxCVSSrrNL = true;}
      if(iYiANbUcYt == OrrwiKHMRM){PohPYnLQsd = true;}
      while(EZcGlpwKeY == uZfkEGiqzD){FhmofIGDtg = true;}
      while(QcaeyZdRdO == QcaeyZdRdO){hKkzxEPjIm = true;}
      while(OrrwiKHMRM == OrrwiKHMRM){WfMkbUKcqy = true;}
      if(VrMtnDiUOj == true){VrMtnDiUOj = false;}
      if(KKrHSiBqUQ == true){KKrHSiBqUQ = false;}
      if(IfikuLhfWb == true){IfikuLhfWb = false;}
      if(iisRCYQgqt == true){iisRCYQgqt = false;}
      if(qJCtEEAjdA == true){qJCtEEAjdA = false;}
      if(IQqAEpIayb == true){IQqAEpIayb = false;}
      if(VCylAaQZFt == true){VCylAaQZFt = false;}
      if(SUzZZzcogp == true){SUzZZzcogp = false;}
      if(LxCVSSrrNL == true){LxCVSSrrNL = false;}
      if(PohPYnLQsd == true){PohPYnLQsd = false;}
      if(nZeignQQZF == true){nZeignQQZF = false;}
      if(MStHQXAbTh == true){MStHQXAbTh = false;}
      if(iYMsdcljBk == true){iYMsdcljBk = false;}
      if(nMuDCkSSod == true){nMuDCkSSod = false;}
      if(BaRIzxuayB == true){BaRIzxuayB = false;}
      if(mixLtONlFD == true){mixLtONlFD = false;}
      if(CgPnQAXqEe == true){CgPnQAXqEe = false;}
      if(FhmofIGDtg == true){FhmofIGDtg = false;}
      if(hKkzxEPjIm == true){hKkzxEPjIm = false;}
      if(WfMkbUKcqy == true){WfMkbUKcqy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFADRRPUCS
{ 
  void NfiramDIUy()
  { 
      bool QhhLQDYVZF = false;
      bool cxLuknMRLO = false;
      bool mlarcQtrYx = false;
      bool DtYJfRsfOB = false;
      bool jGSQTiPjOO = false;
      bool fRHAwdGoiz = false;
      bool IfwbChYCPT = false;
      bool tgCJefSKYs = false;
      bool BJdKRlmXMB = false;
      bool KExOrDKqNk = false;
      bool KNUtTyOxUQ = false;
      bool KuQoyzCkKP = false;
      bool uAoNIpinQa = false;
      bool VbwmhmoiqS = false;
      bool XoDwqOmHQs = false;
      bool BYfypKYGld = false;
      bool OaftthycGK = false;
      bool JStqrFxrWs = false;
      bool CaWXZwwyxW = false;
      bool OhxNDxIICI = false;
      string rgCHHLhRUE;
      string CcHaVBFSIy;
      string mkaQAAHZns;
      string xVuxtqdHFl;
      string lVTLqWVcPn;
      string MfGLOGFkGG;
      string DIcaGggJfe;
      string XyMVMRRPYd;
      string ddJAfRPiim;
      string lrAyhcrrFK;
      string oLxkQNTjzw;
      string ooMccYzbto;
      string RyarseyNni;
      string YZJOnSgYjS;
      string yejlywfWVI;
      string dQxQrqkFrk;
      string PFwQXOfxoJ;
      string rarbplNnsw;
      string zareEIbsVw;
      string gbfzCsiSOj;
      if(rgCHHLhRUE == oLxkQNTjzw){QhhLQDYVZF = true;}
      else if(oLxkQNTjzw == rgCHHLhRUE){KNUtTyOxUQ = true;}
      if(CcHaVBFSIy == ooMccYzbto){cxLuknMRLO = true;}
      else if(ooMccYzbto == CcHaVBFSIy){KuQoyzCkKP = true;}
      if(mkaQAAHZns == RyarseyNni){mlarcQtrYx = true;}
      else if(RyarseyNni == mkaQAAHZns){uAoNIpinQa = true;}
      if(xVuxtqdHFl == YZJOnSgYjS){DtYJfRsfOB = true;}
      else if(YZJOnSgYjS == xVuxtqdHFl){VbwmhmoiqS = true;}
      if(lVTLqWVcPn == yejlywfWVI){jGSQTiPjOO = true;}
      else if(yejlywfWVI == lVTLqWVcPn){XoDwqOmHQs = true;}
      if(MfGLOGFkGG == dQxQrqkFrk){fRHAwdGoiz = true;}
      else if(dQxQrqkFrk == MfGLOGFkGG){BYfypKYGld = true;}
      if(DIcaGggJfe == PFwQXOfxoJ){IfwbChYCPT = true;}
      else if(PFwQXOfxoJ == DIcaGggJfe){OaftthycGK = true;}
      if(XyMVMRRPYd == rarbplNnsw){tgCJefSKYs = true;}
      if(ddJAfRPiim == zareEIbsVw){BJdKRlmXMB = true;}
      if(lrAyhcrrFK == gbfzCsiSOj){KExOrDKqNk = true;}
      while(rarbplNnsw == XyMVMRRPYd){JStqrFxrWs = true;}
      while(zareEIbsVw == zareEIbsVw){CaWXZwwyxW = true;}
      while(gbfzCsiSOj == gbfzCsiSOj){OhxNDxIICI = true;}
      if(QhhLQDYVZF == true){QhhLQDYVZF = false;}
      if(cxLuknMRLO == true){cxLuknMRLO = false;}
      if(mlarcQtrYx == true){mlarcQtrYx = false;}
      if(DtYJfRsfOB == true){DtYJfRsfOB = false;}
      if(jGSQTiPjOO == true){jGSQTiPjOO = false;}
      if(fRHAwdGoiz == true){fRHAwdGoiz = false;}
      if(IfwbChYCPT == true){IfwbChYCPT = false;}
      if(tgCJefSKYs == true){tgCJefSKYs = false;}
      if(BJdKRlmXMB == true){BJdKRlmXMB = false;}
      if(KExOrDKqNk == true){KExOrDKqNk = false;}
      if(KNUtTyOxUQ == true){KNUtTyOxUQ = false;}
      if(KuQoyzCkKP == true){KuQoyzCkKP = false;}
      if(uAoNIpinQa == true){uAoNIpinQa = false;}
      if(VbwmhmoiqS == true){VbwmhmoiqS = false;}
      if(XoDwqOmHQs == true){XoDwqOmHQs = false;}
      if(BYfypKYGld == true){BYfypKYGld = false;}
      if(OaftthycGK == true){OaftthycGK = false;}
      if(JStqrFxrWs == true){JStqrFxrWs = false;}
      if(CaWXZwwyxW == true){CaWXZwwyxW = false;}
      if(OhxNDxIICI == true){OhxNDxIICI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GELQKBZULC
{ 
  void UupfwBbUNa()
  { 
      bool RuPEKXPBRG = false;
      bool EuMGQAoqOT = false;
      bool BpCxOKoMNw = false;
      bool eogsebcUTV = false;
      bool LbMrGwiLfH = false;
      bool rNsiJbrRoA = false;
      bool iDmVaOOTbo = false;
      bool WUXsHYcKqS = false;
      bool acfGDQwxjC = false;
      bool iKeSmIoqQq = false;
      bool gPjqjXpzak = false;
      bool yhZWYFWfRK = false;
      bool RQiYFMoEGz = false;
      bool ilszkLsoWf = false;
      bool awWzDAjItg = false;
      bool kIZGZPfKkX = false;
      bool hlsbBMnakN = false;
      bool LhJkjVtjUF = false;
      bool bgJYNZMmZV = false;
      bool ehDyynCuxq = false;
      string xzcPtxQkPy;
      string mstLFaFhNt;
      string UWAtPeCXBg;
      string YlbOuiUtGg;
      string GBczCjsbKL;
      string VbwYRZyhAP;
      string usihZARePV;
      string FKafnTtBqe;
      string kZMpLxpCxV;
      string kmsplMRtYB;
      string RNMoFKAPjx;
      string expVeUfsWb;
      string KPhtkSQkta;
      string BAboMXNXjB;
      string xZRzpmwXLQ;
      string gYWxqCeREm;
      string sOUJweUAIH;
      string GIIVejyiEx;
      string WrYdtbceyK;
      string rwSwHhFICK;
      if(xzcPtxQkPy == RNMoFKAPjx){RuPEKXPBRG = true;}
      else if(RNMoFKAPjx == xzcPtxQkPy){gPjqjXpzak = true;}
      if(mstLFaFhNt == expVeUfsWb){EuMGQAoqOT = true;}
      else if(expVeUfsWb == mstLFaFhNt){yhZWYFWfRK = true;}
      if(UWAtPeCXBg == KPhtkSQkta){BpCxOKoMNw = true;}
      else if(KPhtkSQkta == UWAtPeCXBg){RQiYFMoEGz = true;}
      if(YlbOuiUtGg == BAboMXNXjB){eogsebcUTV = true;}
      else if(BAboMXNXjB == YlbOuiUtGg){ilszkLsoWf = true;}
      if(GBczCjsbKL == xZRzpmwXLQ){LbMrGwiLfH = true;}
      else if(xZRzpmwXLQ == GBczCjsbKL){awWzDAjItg = true;}
      if(VbwYRZyhAP == gYWxqCeREm){rNsiJbrRoA = true;}
      else if(gYWxqCeREm == VbwYRZyhAP){kIZGZPfKkX = true;}
      if(usihZARePV == sOUJweUAIH){iDmVaOOTbo = true;}
      else if(sOUJweUAIH == usihZARePV){hlsbBMnakN = true;}
      if(FKafnTtBqe == GIIVejyiEx){WUXsHYcKqS = true;}
      if(kZMpLxpCxV == WrYdtbceyK){acfGDQwxjC = true;}
      if(kmsplMRtYB == rwSwHhFICK){iKeSmIoqQq = true;}
      while(GIIVejyiEx == FKafnTtBqe){LhJkjVtjUF = true;}
      while(WrYdtbceyK == WrYdtbceyK){bgJYNZMmZV = true;}
      while(rwSwHhFICK == rwSwHhFICK){ehDyynCuxq = true;}
      if(RuPEKXPBRG == true){RuPEKXPBRG = false;}
      if(EuMGQAoqOT == true){EuMGQAoqOT = false;}
      if(BpCxOKoMNw == true){BpCxOKoMNw = false;}
      if(eogsebcUTV == true){eogsebcUTV = false;}
      if(LbMrGwiLfH == true){LbMrGwiLfH = false;}
      if(rNsiJbrRoA == true){rNsiJbrRoA = false;}
      if(iDmVaOOTbo == true){iDmVaOOTbo = false;}
      if(WUXsHYcKqS == true){WUXsHYcKqS = false;}
      if(acfGDQwxjC == true){acfGDQwxjC = false;}
      if(iKeSmIoqQq == true){iKeSmIoqQq = false;}
      if(gPjqjXpzak == true){gPjqjXpzak = false;}
      if(yhZWYFWfRK == true){yhZWYFWfRK = false;}
      if(RQiYFMoEGz == true){RQiYFMoEGz = false;}
      if(ilszkLsoWf == true){ilszkLsoWf = false;}
      if(awWzDAjItg == true){awWzDAjItg = false;}
      if(kIZGZPfKkX == true){kIZGZPfKkX = false;}
      if(hlsbBMnakN == true){hlsbBMnakN = false;}
      if(LhJkjVtjUF == true){LhJkjVtjUF = false;}
      if(bgJYNZMmZV == true){bgJYNZMmZV = false;}
      if(ehDyynCuxq == true){ehDyynCuxq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVVMTTTCEC
{ 
  void FoEedMqHpQ()
  { 
      bool FNPqAzaXtl = false;
      bool jSeQDCNuji = false;
      bool hYSbuTSKAT = false;
      bool edlziQycJg = false;
      bool tDEBupgJGO = false;
      bool QLqjtgumwg = false;
      bool gQWaHFgfhl = false;
      bool DjkDndURgE = false;
      bool lJDlCSmBEB = false;
      bool VKgczcgdto = false;
      bool JBbTKfZmuP = false;
      bool MdFrtWMkXn = false;
      bool ReafQrDIDL = false;
      bool xpWqtjgiaW = false;
      bool rAGnorFnhc = false;
      bool QwGFXdauDR = false;
      bool bRijRVGOxJ = false;
      bool pcJAuRYlqY = false;
      bool mOZatBjRTP = false;
      bool JlfItaQVVS = false;
      string HaOQZeKZDd;
      string uhKSLPdAzY;
      string WaSPbEmkmW;
      string IjEorAhpCZ;
      string mwVYhRWxiO;
      string nwYYwfIynU;
      string qYlgVKcVaL;
      string hmyZkaFshK;
      string hpCYhLLesM;
      string rjBhhNJnCW;
      string nAVXfByymV;
      string ZOQdlAWNyK;
      string zycOSykQrW;
      string QQqKVgTerg;
      string MNrWldSXug;
      string qworXpXHFh;
      string PhGQEJXFIE;
      string frURylFFbo;
      string eNUKfUaymf;
      string JMZKQdHbSc;
      if(HaOQZeKZDd == nAVXfByymV){FNPqAzaXtl = true;}
      else if(nAVXfByymV == HaOQZeKZDd){JBbTKfZmuP = true;}
      if(uhKSLPdAzY == ZOQdlAWNyK){jSeQDCNuji = true;}
      else if(ZOQdlAWNyK == uhKSLPdAzY){MdFrtWMkXn = true;}
      if(WaSPbEmkmW == zycOSykQrW){hYSbuTSKAT = true;}
      else if(zycOSykQrW == WaSPbEmkmW){ReafQrDIDL = true;}
      if(IjEorAhpCZ == QQqKVgTerg){edlziQycJg = true;}
      else if(QQqKVgTerg == IjEorAhpCZ){xpWqtjgiaW = true;}
      if(mwVYhRWxiO == MNrWldSXug){tDEBupgJGO = true;}
      else if(MNrWldSXug == mwVYhRWxiO){rAGnorFnhc = true;}
      if(nwYYwfIynU == qworXpXHFh){QLqjtgumwg = true;}
      else if(qworXpXHFh == nwYYwfIynU){QwGFXdauDR = true;}
      if(qYlgVKcVaL == PhGQEJXFIE){gQWaHFgfhl = true;}
      else if(PhGQEJXFIE == qYlgVKcVaL){bRijRVGOxJ = true;}
      if(hmyZkaFshK == frURylFFbo){DjkDndURgE = true;}
      if(hpCYhLLesM == eNUKfUaymf){lJDlCSmBEB = true;}
      if(rjBhhNJnCW == JMZKQdHbSc){VKgczcgdto = true;}
      while(frURylFFbo == hmyZkaFshK){pcJAuRYlqY = true;}
      while(eNUKfUaymf == eNUKfUaymf){mOZatBjRTP = true;}
      while(JMZKQdHbSc == JMZKQdHbSc){JlfItaQVVS = true;}
      if(FNPqAzaXtl == true){FNPqAzaXtl = false;}
      if(jSeQDCNuji == true){jSeQDCNuji = false;}
      if(hYSbuTSKAT == true){hYSbuTSKAT = false;}
      if(edlziQycJg == true){edlziQycJg = false;}
      if(tDEBupgJGO == true){tDEBupgJGO = false;}
      if(QLqjtgumwg == true){QLqjtgumwg = false;}
      if(gQWaHFgfhl == true){gQWaHFgfhl = false;}
      if(DjkDndURgE == true){DjkDndURgE = false;}
      if(lJDlCSmBEB == true){lJDlCSmBEB = false;}
      if(VKgczcgdto == true){VKgczcgdto = false;}
      if(JBbTKfZmuP == true){JBbTKfZmuP = false;}
      if(MdFrtWMkXn == true){MdFrtWMkXn = false;}
      if(ReafQrDIDL == true){ReafQrDIDL = false;}
      if(xpWqtjgiaW == true){xpWqtjgiaW = false;}
      if(rAGnorFnhc == true){rAGnorFnhc = false;}
      if(QwGFXdauDR == true){QwGFXdauDR = false;}
      if(bRijRVGOxJ == true){bRijRVGOxJ = false;}
      if(pcJAuRYlqY == true){pcJAuRYlqY = false;}
      if(mOZatBjRTP == true){mOZatBjRTP = false;}
      if(JlfItaQVVS == true){JlfItaQVVS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUFTISDWSE
{ 
  void dSmjXMoFfa()
  { 
      bool YauNUVEdti = false;
      bool ZBQgerBhUs = false;
      bool njYGsQtnjH = false;
      bool FtgfjQJozP = false;
      bool TgefMShZpI = false;
      bool bbNMCnBoTE = false;
      bool bQsldeTkxN = false;
      bool hLhFYHFssa = false;
      bool hUxbecgTdw = false;
      bool OUVtnDmrCh = false;
      bool yxcbZQsImt = false;
      bool iIusWHSRHA = false;
      bool yAGBzNpnRV = false;
      bool UMqLbkrUCO = false;
      bool jXfiMGYbXg = false;
      bool jVkBiypacM = false;
      bool aFqRZVRjQk = false;
      bool OyOrQaTWns = false;
      bool nNPklzaobd = false;
      bool tQqpndgOJq = false;
      string KLAVnNinoU;
      string UmkzEaALZm;
      string qHrLTFVDRK;
      string hXIrUPFcgf;
      string ElemXCtgWy;
      string QOCALDToCh;
      string rfVdmxdsen;
      string VWdthEbEnQ;
      string KofTsSUIfR;
      string wPaznXQAAZ;
      string YBBhbtjIRG;
      string aOBkWDzBkT;
      string bUMNqFueFK;
      string naENqJmyrz;
      string iMqYphOobk;
      string XOPfyEonpV;
      string yECHSzJntN;
      string PBJkkOdmWJ;
      string qFDUlYLYOm;
      string TzHVAdJiGp;
      if(KLAVnNinoU == YBBhbtjIRG){YauNUVEdti = true;}
      else if(YBBhbtjIRG == KLAVnNinoU){yxcbZQsImt = true;}
      if(UmkzEaALZm == aOBkWDzBkT){ZBQgerBhUs = true;}
      else if(aOBkWDzBkT == UmkzEaALZm){iIusWHSRHA = true;}
      if(qHrLTFVDRK == bUMNqFueFK){njYGsQtnjH = true;}
      else if(bUMNqFueFK == qHrLTFVDRK){yAGBzNpnRV = true;}
      if(hXIrUPFcgf == naENqJmyrz){FtgfjQJozP = true;}
      else if(naENqJmyrz == hXIrUPFcgf){UMqLbkrUCO = true;}
      if(ElemXCtgWy == iMqYphOobk){TgefMShZpI = true;}
      else if(iMqYphOobk == ElemXCtgWy){jXfiMGYbXg = true;}
      if(QOCALDToCh == XOPfyEonpV){bbNMCnBoTE = true;}
      else if(XOPfyEonpV == QOCALDToCh){jVkBiypacM = true;}
      if(rfVdmxdsen == yECHSzJntN){bQsldeTkxN = true;}
      else if(yECHSzJntN == rfVdmxdsen){aFqRZVRjQk = true;}
      if(VWdthEbEnQ == PBJkkOdmWJ){hLhFYHFssa = true;}
      if(KofTsSUIfR == qFDUlYLYOm){hUxbecgTdw = true;}
      if(wPaznXQAAZ == TzHVAdJiGp){OUVtnDmrCh = true;}
      while(PBJkkOdmWJ == VWdthEbEnQ){OyOrQaTWns = true;}
      while(qFDUlYLYOm == qFDUlYLYOm){nNPklzaobd = true;}
      while(TzHVAdJiGp == TzHVAdJiGp){tQqpndgOJq = true;}
      if(YauNUVEdti == true){YauNUVEdti = false;}
      if(ZBQgerBhUs == true){ZBQgerBhUs = false;}
      if(njYGsQtnjH == true){njYGsQtnjH = false;}
      if(FtgfjQJozP == true){FtgfjQJozP = false;}
      if(TgefMShZpI == true){TgefMShZpI = false;}
      if(bbNMCnBoTE == true){bbNMCnBoTE = false;}
      if(bQsldeTkxN == true){bQsldeTkxN = false;}
      if(hLhFYHFssa == true){hLhFYHFssa = false;}
      if(hUxbecgTdw == true){hUxbecgTdw = false;}
      if(OUVtnDmrCh == true){OUVtnDmrCh = false;}
      if(yxcbZQsImt == true){yxcbZQsImt = false;}
      if(iIusWHSRHA == true){iIusWHSRHA = false;}
      if(yAGBzNpnRV == true){yAGBzNpnRV = false;}
      if(UMqLbkrUCO == true){UMqLbkrUCO = false;}
      if(jXfiMGYbXg == true){jXfiMGYbXg = false;}
      if(jVkBiypacM == true){jVkBiypacM = false;}
      if(aFqRZVRjQk == true){aFqRZVRjQk = false;}
      if(OyOrQaTWns == true){OyOrQaTWns = false;}
      if(nNPklzaobd == true){nNPklzaobd = false;}
      if(tQqpndgOJq == true){tQqpndgOJq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKWIHCRZDG
{ 
  void kpwHryezYW()
  { 
      bool CDaOGZyJoI = false;
      bool kbnHZahXAE = false;
      bool aDnGfjRxad = false;
      bool gLMgKONpZZ = false;
      bool rSWBHbbWXS = false;
      bool fahKRzPThV = false;
      bool HAiKbYPGxL = false;
      bool MqyZMIfmzE = false;
      bool IuZHyFdBOL = false;
      bool ysHDSqjMYh = false;
      bool LUZLGncIyJ = false;
      bool SbUdNMZaLW = false;
      bool uOrkMSjtHU = false;
      bool XTNQrnUNBK = false;
      bool bUDFsVYdpF = false;
      bool QJAClwcnym = false;
      bool EhAckyODkY = false;
      bool qLZBtZLlrp = false;
      bool tFDBEOTLdu = false;
      bool KfOOFtUZTt = false;
      string QVDnPbteqi;
      string lIQVEwSnzH;
      string pnqefUiynb;
      string qHWnmCZGnc;
      string PYXVEwUTAi;
      string ptMPxcdYHt;
      string ruqOrekchC;
      string VMAVqRQVZi;
      string AOyElwtHpK;
      string XBytjTgIcZ;
      string KqkyNctpXe;
      string MHyXsdxmcu;
      string jdmXdUOFlW;
      string jHszYIdzqI;
      string CDiKxQCZAG;
      string WtehofENUr;
      string OnEAuEOyzk;
      string AxwUsfubZM;
      string RnFfApcLKr;
      string EPeysOziPs;
      if(QVDnPbteqi == KqkyNctpXe){CDaOGZyJoI = true;}
      else if(KqkyNctpXe == QVDnPbteqi){LUZLGncIyJ = true;}
      if(lIQVEwSnzH == MHyXsdxmcu){kbnHZahXAE = true;}
      else if(MHyXsdxmcu == lIQVEwSnzH){SbUdNMZaLW = true;}
      if(pnqefUiynb == jdmXdUOFlW){aDnGfjRxad = true;}
      else if(jdmXdUOFlW == pnqefUiynb){uOrkMSjtHU = true;}
      if(qHWnmCZGnc == jHszYIdzqI){gLMgKONpZZ = true;}
      else if(jHszYIdzqI == qHWnmCZGnc){XTNQrnUNBK = true;}
      if(PYXVEwUTAi == CDiKxQCZAG){rSWBHbbWXS = true;}
      else if(CDiKxQCZAG == PYXVEwUTAi){bUDFsVYdpF = true;}
      if(ptMPxcdYHt == WtehofENUr){fahKRzPThV = true;}
      else if(WtehofENUr == ptMPxcdYHt){QJAClwcnym = true;}
      if(ruqOrekchC == OnEAuEOyzk){HAiKbYPGxL = true;}
      else if(OnEAuEOyzk == ruqOrekchC){EhAckyODkY = true;}
      if(VMAVqRQVZi == AxwUsfubZM){MqyZMIfmzE = true;}
      if(AOyElwtHpK == RnFfApcLKr){IuZHyFdBOL = true;}
      if(XBytjTgIcZ == EPeysOziPs){ysHDSqjMYh = true;}
      while(AxwUsfubZM == VMAVqRQVZi){qLZBtZLlrp = true;}
      while(RnFfApcLKr == RnFfApcLKr){tFDBEOTLdu = true;}
      while(EPeysOziPs == EPeysOziPs){KfOOFtUZTt = true;}
      if(CDaOGZyJoI == true){CDaOGZyJoI = false;}
      if(kbnHZahXAE == true){kbnHZahXAE = false;}
      if(aDnGfjRxad == true){aDnGfjRxad = false;}
      if(gLMgKONpZZ == true){gLMgKONpZZ = false;}
      if(rSWBHbbWXS == true){rSWBHbbWXS = false;}
      if(fahKRzPThV == true){fahKRzPThV = false;}
      if(HAiKbYPGxL == true){HAiKbYPGxL = false;}
      if(MqyZMIfmzE == true){MqyZMIfmzE = false;}
      if(IuZHyFdBOL == true){IuZHyFdBOL = false;}
      if(ysHDSqjMYh == true){ysHDSqjMYh = false;}
      if(LUZLGncIyJ == true){LUZLGncIyJ = false;}
      if(SbUdNMZaLW == true){SbUdNMZaLW = false;}
      if(uOrkMSjtHU == true){uOrkMSjtHU = false;}
      if(XTNQrnUNBK == true){XTNQrnUNBK = false;}
      if(bUDFsVYdpF == true){bUDFsVYdpF = false;}
      if(QJAClwcnym == true){QJAClwcnym = false;}
      if(EhAckyODkY == true){EhAckyODkY = false;}
      if(qLZBtZLlrp == true){qLZBtZLlrp = false;}
      if(tFDBEOTLdu == true){tFDBEOTLdu = false;}
      if(KfOOFtUZTt == true){KfOOFtUZTt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSNETNSSMC
{ 
  void EAYNhgAfef()
  { 
      bool skoVoIzGrV = false;
      bool cwcweFUlZR = false;
      bool FJyKyXuXKo = false;
      bool eEWIPGTceb = false;
      bool GEoEaNPrXL = false;
      bool bnoDIjmdXR = false;
      bool NbuCpYYTgY = false;
      bool kqGxLBUsjj = false;
      bool IDzyNqOSAf = false;
      bool TpFNOdIlNB = false;
      bool ouKzajgrrG = false;
      bool PssmJKbxoz = false;
      bool JFTBFtkrhg = false;
      bool sheiuMrAWc = false;
      bool JWasPZwSEE = false;
      bool BLxOriaJsf = false;
      bool zoJKNgOKqw = false;
      bool SbZLoldake = false;
      bool ySncegkPpM = false;
      bool khGqdUMQei = false;
      string nnfsTqjRky;
      string pDFaJYGjIi;
      string rsskmmmROT;
      string emxSjfiYSS;
      string lfIARwNraO;
      string KOXjSutuFg;
      string DSCRSCGlqd;
      string pgQpwLksSp;
      string YtpAIPPNAo;
      string kmTlOTdqhP;
      string paBxYcyhmG;
      string KBcPHJbCID;
      string mslBrCNdac;
      string hsLDAyrsaf;
      string QgZtejKEeF;
      string qbidbwnAEW;
      string OTHKXQpZOI;
      string QibblFTrWI;
      string qJzUkGKgaD;
      string KrnDRwZOVN;
      if(nnfsTqjRky == paBxYcyhmG){skoVoIzGrV = true;}
      else if(paBxYcyhmG == nnfsTqjRky){ouKzajgrrG = true;}
      if(pDFaJYGjIi == KBcPHJbCID){cwcweFUlZR = true;}
      else if(KBcPHJbCID == pDFaJYGjIi){PssmJKbxoz = true;}
      if(rsskmmmROT == mslBrCNdac){FJyKyXuXKo = true;}
      else if(mslBrCNdac == rsskmmmROT){JFTBFtkrhg = true;}
      if(emxSjfiYSS == hsLDAyrsaf){eEWIPGTceb = true;}
      else if(hsLDAyrsaf == emxSjfiYSS){sheiuMrAWc = true;}
      if(lfIARwNraO == QgZtejKEeF){GEoEaNPrXL = true;}
      else if(QgZtejKEeF == lfIARwNraO){JWasPZwSEE = true;}
      if(KOXjSutuFg == qbidbwnAEW){bnoDIjmdXR = true;}
      else if(qbidbwnAEW == KOXjSutuFg){BLxOriaJsf = true;}
      if(DSCRSCGlqd == OTHKXQpZOI){NbuCpYYTgY = true;}
      else if(OTHKXQpZOI == DSCRSCGlqd){zoJKNgOKqw = true;}
      if(pgQpwLksSp == QibblFTrWI){kqGxLBUsjj = true;}
      if(YtpAIPPNAo == qJzUkGKgaD){IDzyNqOSAf = true;}
      if(kmTlOTdqhP == KrnDRwZOVN){TpFNOdIlNB = true;}
      while(QibblFTrWI == pgQpwLksSp){SbZLoldake = true;}
      while(qJzUkGKgaD == qJzUkGKgaD){ySncegkPpM = true;}
      while(KrnDRwZOVN == KrnDRwZOVN){khGqdUMQei = true;}
      if(skoVoIzGrV == true){skoVoIzGrV = false;}
      if(cwcweFUlZR == true){cwcweFUlZR = false;}
      if(FJyKyXuXKo == true){FJyKyXuXKo = false;}
      if(eEWIPGTceb == true){eEWIPGTceb = false;}
      if(GEoEaNPrXL == true){GEoEaNPrXL = false;}
      if(bnoDIjmdXR == true){bnoDIjmdXR = false;}
      if(NbuCpYYTgY == true){NbuCpYYTgY = false;}
      if(kqGxLBUsjj == true){kqGxLBUsjj = false;}
      if(IDzyNqOSAf == true){IDzyNqOSAf = false;}
      if(TpFNOdIlNB == true){TpFNOdIlNB = false;}
      if(ouKzajgrrG == true){ouKzajgrrG = false;}
      if(PssmJKbxoz == true){PssmJKbxoz = false;}
      if(JFTBFtkrhg == true){JFTBFtkrhg = false;}
      if(sheiuMrAWc == true){sheiuMrAWc = false;}
      if(JWasPZwSEE == true){JWasPZwSEE = false;}
      if(BLxOriaJsf == true){BLxOriaJsf = false;}
      if(zoJKNgOKqw == true){zoJKNgOKqw = false;}
      if(SbZLoldake == true){SbZLoldake = false;}
      if(ySncegkPpM == true){ySncegkPpM = false;}
      if(khGqdUMQei == true){khGqdUMQei = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRVACZZBUH
{ 
  void lfBlRYzFaY()
  { 
      bool lEeunVcCEN = false;
      bool eHBmQxROZu = false;
      bool RfYYPSMLFr = false;
      bool JSGblaYBpS = false;
      bool xUwDbRBggq = false;
      bool mNWLgFfGeU = false;
      bool IQxMEMBYBo = false;
      bool XPXGywjUxy = false;
      bool QfeNFuwuuf = false;
      bool tSWUKgWizO = false;
      bool QbfqSWoQNj = false;
      bool ULIgEckiHI = false;
      bool PFdUtFsDwQ = false;
      bool YBUhhoAnth = false;
      bool FehLLiJoQg = false;
      bool wmaqzKyKxN = false;
      bool clUwKTqazP = false;
      bool cxoYDkXRJK = false;
      bool uElOUlZciW = false;
      bool popgFSKkAq = false;
      string nTSwBremXr;
      string sYpRAJJHhW;
      string JbPnnNUhSf;
      string MifqHGgBHh;
      string OIZwQOJzyB;
      string YxfOhLDeHm;
      string WxTreJrzJt;
      string cIAzIACTXY;
      string EVjRGPCQJw;
      string CCsTLQnhQG;
      string WKpDXQwgGg;
      string JiGhiBNCkP;
      string HaoNqaOgnr;
      string LUCQCtefsp;
      string TVKbmTuKjJ;
      string DlxBzuUbLw;
      string BOsOVngpfo;
      string VgJtwlPMaX;
      string fEwdnZWARG;
      string YDUxoEcwGy;
      if(nTSwBremXr == WKpDXQwgGg){lEeunVcCEN = true;}
      else if(WKpDXQwgGg == nTSwBremXr){QbfqSWoQNj = true;}
      if(sYpRAJJHhW == JiGhiBNCkP){eHBmQxROZu = true;}
      else if(JiGhiBNCkP == sYpRAJJHhW){ULIgEckiHI = true;}
      if(JbPnnNUhSf == HaoNqaOgnr){RfYYPSMLFr = true;}
      else if(HaoNqaOgnr == JbPnnNUhSf){PFdUtFsDwQ = true;}
      if(MifqHGgBHh == LUCQCtefsp){JSGblaYBpS = true;}
      else if(LUCQCtefsp == MifqHGgBHh){YBUhhoAnth = true;}
      if(OIZwQOJzyB == TVKbmTuKjJ){xUwDbRBggq = true;}
      else if(TVKbmTuKjJ == OIZwQOJzyB){FehLLiJoQg = true;}
      if(YxfOhLDeHm == DlxBzuUbLw){mNWLgFfGeU = true;}
      else if(DlxBzuUbLw == YxfOhLDeHm){wmaqzKyKxN = true;}
      if(WxTreJrzJt == BOsOVngpfo){IQxMEMBYBo = true;}
      else if(BOsOVngpfo == WxTreJrzJt){clUwKTqazP = true;}
      if(cIAzIACTXY == VgJtwlPMaX){XPXGywjUxy = true;}
      if(EVjRGPCQJw == fEwdnZWARG){QfeNFuwuuf = true;}
      if(CCsTLQnhQG == YDUxoEcwGy){tSWUKgWizO = true;}
      while(VgJtwlPMaX == cIAzIACTXY){cxoYDkXRJK = true;}
      while(fEwdnZWARG == fEwdnZWARG){uElOUlZciW = true;}
      while(YDUxoEcwGy == YDUxoEcwGy){popgFSKkAq = true;}
      if(lEeunVcCEN == true){lEeunVcCEN = false;}
      if(eHBmQxROZu == true){eHBmQxROZu = false;}
      if(RfYYPSMLFr == true){RfYYPSMLFr = false;}
      if(JSGblaYBpS == true){JSGblaYBpS = false;}
      if(xUwDbRBggq == true){xUwDbRBggq = false;}
      if(mNWLgFfGeU == true){mNWLgFfGeU = false;}
      if(IQxMEMBYBo == true){IQxMEMBYBo = false;}
      if(XPXGywjUxy == true){XPXGywjUxy = false;}
      if(QfeNFuwuuf == true){QfeNFuwuuf = false;}
      if(tSWUKgWizO == true){tSWUKgWizO = false;}
      if(QbfqSWoQNj == true){QbfqSWoQNj = false;}
      if(ULIgEckiHI == true){ULIgEckiHI = false;}
      if(PFdUtFsDwQ == true){PFdUtFsDwQ = false;}
      if(YBUhhoAnth == true){YBUhhoAnth = false;}
      if(FehLLiJoQg == true){FehLLiJoQg = false;}
      if(wmaqzKyKxN == true){wmaqzKyKxN = false;}
      if(clUwKTqazP == true){clUwKTqazP = false;}
      if(cxoYDkXRJK == true){cxoYDkXRJK = false;}
      if(uElOUlZciW == true){uElOUlZciW = false;}
      if(popgFSKkAq == true){popgFSKkAq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFKPHJDLET
{ 
  void ttIIlsRACM()
  { 
      bool AtftPTOBSz = false;
      bool GTUHppAjcF = false;
      bool mVbyLOqYLt = false;
      bool nTaTzbTMjG = false;
      bool tMVnLdLxyj = false;
      bool ZQJlldRgiA = false;
      bool bopYLmsAIO = false;
      bool WmAVLaAnlg = false;
      bool CsaaTXJogV = false;
      bool KmcidEWxcY = false;
      bool kKojNlPnZL = false;
      bool cdtByiNOEm = false;
      bool cDSmDjKRqG = false;
      bool DDKNuqDqNh = false;
      bool HUPVrfraku = false;
      bool pIrouhrCfd = false;
      bool bywSHYSfGG = false;
      bool fWBVfHnxtX = false;
      bool qigwQuKVRN = false;
      bool zALiFIYwNS = false;
      string dJCPhlopmk;
      string mXSVHfVIga;
      string klHOdnPCdg;
      string hhrmWzsetW;
      string LFuqUoqjYg;
      string cgDIfrCnks;
      string VlMGCEffzH;
      string mpNKOepPsn;
      string xfdwDAdiGd;
      string xFsBAYsonP;
      string JLjQtmTssA;
      string CltwwpIPCB;
      string ZwYVKgwMJp;
      string lAbdekuMBQ;
      string gkpGbKKxFK;
      string PcmmoMmOGM;
      string pHiDOBKQQK;
      string uwNlToGStz;
      string WzHzZINnnS;
      string yfFnaZBmqZ;
      if(dJCPhlopmk == JLjQtmTssA){AtftPTOBSz = true;}
      else if(JLjQtmTssA == dJCPhlopmk){kKojNlPnZL = true;}
      if(mXSVHfVIga == CltwwpIPCB){GTUHppAjcF = true;}
      else if(CltwwpIPCB == mXSVHfVIga){cdtByiNOEm = true;}
      if(klHOdnPCdg == ZwYVKgwMJp){mVbyLOqYLt = true;}
      else if(ZwYVKgwMJp == klHOdnPCdg){cDSmDjKRqG = true;}
      if(hhrmWzsetW == lAbdekuMBQ){nTaTzbTMjG = true;}
      else if(lAbdekuMBQ == hhrmWzsetW){DDKNuqDqNh = true;}
      if(LFuqUoqjYg == gkpGbKKxFK){tMVnLdLxyj = true;}
      else if(gkpGbKKxFK == LFuqUoqjYg){HUPVrfraku = true;}
      if(cgDIfrCnks == PcmmoMmOGM){ZQJlldRgiA = true;}
      else if(PcmmoMmOGM == cgDIfrCnks){pIrouhrCfd = true;}
      if(VlMGCEffzH == pHiDOBKQQK){bopYLmsAIO = true;}
      else if(pHiDOBKQQK == VlMGCEffzH){bywSHYSfGG = true;}
      if(mpNKOepPsn == uwNlToGStz){WmAVLaAnlg = true;}
      if(xfdwDAdiGd == WzHzZINnnS){CsaaTXJogV = true;}
      if(xFsBAYsonP == yfFnaZBmqZ){KmcidEWxcY = true;}
      while(uwNlToGStz == mpNKOepPsn){fWBVfHnxtX = true;}
      while(WzHzZINnnS == WzHzZINnnS){qigwQuKVRN = true;}
      while(yfFnaZBmqZ == yfFnaZBmqZ){zALiFIYwNS = true;}
      if(AtftPTOBSz == true){AtftPTOBSz = false;}
      if(GTUHppAjcF == true){GTUHppAjcF = false;}
      if(mVbyLOqYLt == true){mVbyLOqYLt = false;}
      if(nTaTzbTMjG == true){nTaTzbTMjG = false;}
      if(tMVnLdLxyj == true){tMVnLdLxyj = false;}
      if(ZQJlldRgiA == true){ZQJlldRgiA = false;}
      if(bopYLmsAIO == true){bopYLmsAIO = false;}
      if(WmAVLaAnlg == true){WmAVLaAnlg = false;}
      if(CsaaTXJogV == true){CsaaTXJogV = false;}
      if(KmcidEWxcY == true){KmcidEWxcY = false;}
      if(kKojNlPnZL == true){kKojNlPnZL = false;}
      if(cdtByiNOEm == true){cdtByiNOEm = false;}
      if(cDSmDjKRqG == true){cDSmDjKRqG = false;}
      if(DDKNuqDqNh == true){DDKNuqDqNh = false;}
      if(HUPVrfraku == true){HUPVrfraku = false;}
      if(pIrouhrCfd == true){pIrouhrCfd = false;}
      if(bywSHYSfGG == true){bywSHYSfGG = false;}
      if(fWBVfHnxtX == true){fWBVfHnxtX = false;}
      if(qigwQuKVRN == true){qigwQuKVRN = false;}
      if(zALiFIYwNS == true){zALiFIYwNS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSHQPXOBZT
{ 
  void DVbesgFzTl()
  { 
      bool VAORbAyzoq = false;
      bool uGepgDuEYE = false;
      bool HAXZaJwyTl = false;
      bool LqrEQdHjhR = false;
      bool aUaWHwMLGB = false;
      bool wxyopUboqS = false;
      bool DAeDeDOaZC = false;
      bool uKVHdmYBRd = false;
      bool wkqSpOsDNu = false;
      bool CRrONZoXqE = false;
      bool hlkDGkapKD = false;
      bool uZXNWRJMMQ = false;
      bool KKMeAcRHsE = false;
      bool xBJNwKAnMF = false;
      bool nCrJAbterw = false;
      bool QcLatWYGCc = false;
      bool TTwGGtPKQM = false;
      bool RUAHbHSDdX = false;
      bool ilOxmToiSZ = false;
      bool ktkilTFlDF = false;
      string KekTHcHbUE;
      string KRJFcJLVNd;
      string QTHdgeQyOy;
      string COTjjNzSzS;
      string liymcidfRl;
      string fRxzVpXGmb;
      string MJNVBuxYVP;
      string JsVtrgVUBy;
      string BjfbRjRUNt;
      string prfWGbVckh;
      string lEJCcmwCGo;
      string TCFnabckER;
      string cbKbYQNynQ;
      string KrjSMwZdze;
      string nPNYZmlqwd;
      string ykYSEJshcL;
      string ZxNpebRlbd;
      string BylYcNOlCl;
      string dVCJRZTQOC;
      string DrBnEqBWty;
      if(KekTHcHbUE == lEJCcmwCGo){VAORbAyzoq = true;}
      else if(lEJCcmwCGo == KekTHcHbUE){hlkDGkapKD = true;}
      if(KRJFcJLVNd == TCFnabckER){uGepgDuEYE = true;}
      else if(TCFnabckER == KRJFcJLVNd){uZXNWRJMMQ = true;}
      if(QTHdgeQyOy == cbKbYQNynQ){HAXZaJwyTl = true;}
      else if(cbKbYQNynQ == QTHdgeQyOy){KKMeAcRHsE = true;}
      if(COTjjNzSzS == KrjSMwZdze){LqrEQdHjhR = true;}
      else if(KrjSMwZdze == COTjjNzSzS){xBJNwKAnMF = true;}
      if(liymcidfRl == nPNYZmlqwd){aUaWHwMLGB = true;}
      else if(nPNYZmlqwd == liymcidfRl){nCrJAbterw = true;}
      if(fRxzVpXGmb == ykYSEJshcL){wxyopUboqS = true;}
      else if(ykYSEJshcL == fRxzVpXGmb){QcLatWYGCc = true;}
      if(MJNVBuxYVP == ZxNpebRlbd){DAeDeDOaZC = true;}
      else if(ZxNpebRlbd == MJNVBuxYVP){TTwGGtPKQM = true;}
      if(JsVtrgVUBy == BylYcNOlCl){uKVHdmYBRd = true;}
      if(BjfbRjRUNt == dVCJRZTQOC){wkqSpOsDNu = true;}
      if(prfWGbVckh == DrBnEqBWty){CRrONZoXqE = true;}
      while(BylYcNOlCl == JsVtrgVUBy){RUAHbHSDdX = true;}
      while(dVCJRZTQOC == dVCJRZTQOC){ilOxmToiSZ = true;}
      while(DrBnEqBWty == DrBnEqBWty){ktkilTFlDF = true;}
      if(VAORbAyzoq == true){VAORbAyzoq = false;}
      if(uGepgDuEYE == true){uGepgDuEYE = false;}
      if(HAXZaJwyTl == true){HAXZaJwyTl = false;}
      if(LqrEQdHjhR == true){LqrEQdHjhR = false;}
      if(aUaWHwMLGB == true){aUaWHwMLGB = false;}
      if(wxyopUboqS == true){wxyopUboqS = false;}
      if(DAeDeDOaZC == true){DAeDeDOaZC = false;}
      if(uKVHdmYBRd == true){uKVHdmYBRd = false;}
      if(wkqSpOsDNu == true){wkqSpOsDNu = false;}
      if(CRrONZoXqE == true){CRrONZoXqE = false;}
      if(hlkDGkapKD == true){hlkDGkapKD = false;}
      if(uZXNWRJMMQ == true){uZXNWRJMMQ = false;}
      if(KKMeAcRHsE == true){KKMeAcRHsE = false;}
      if(xBJNwKAnMF == true){xBJNwKAnMF = false;}
      if(nCrJAbterw == true){nCrJAbterw = false;}
      if(QcLatWYGCc == true){QcLatWYGCc = false;}
      if(TTwGGtPKQM == true){TTwGGtPKQM = false;}
      if(RUAHbHSDdX == true){RUAHbHSDdX = false;}
      if(ilOxmToiSZ == true){ilOxmToiSZ = false;}
      if(ktkilTFlDF == true){ktkilTFlDF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWXOYZOIYE
{ 
  void HcmFwhNeET()
  { 
      bool yQVxnbTITT = false;
      bool frhinQQATa = false;
      bool ohnTPmCEgI = false;
      bool XBskORgoqq = false;
      bool eOHCqkrlrh = false;
      bool oYSCOPcCgA = false;
      bool YPbLueywUV = false;
      bool iaJbwZakbe = false;
      bool tPLySyhqWz = false;
      bool oeHpRPlwGL = false;
      bool luRVzOPqFn = false;
      bool nqaCGJDdrw = false;
      bool xHZUgDSSJg = false;
      bool neePsyxpzE = false;
      bool iqkhLyEFjI = false;
      bool LIDJOdVxou = false;
      bool uwgYAJLKJH = false;
      bool LNemMFVrJi = false;
      bool zNhBUfaUBO = false;
      bool cABDImKMgB = false;
      string NbIKBseXMm;
      string GoJIRNZADc;
      string JpnCAgCCAI;
      string YguCMReIwF;
      string SPqVtaxZRP;
      string DjLPWXnFKU;
      string pbXENYsGuz;
      string iQDxJtzSIZ;
      string ickjFoUffo;
      string dYyaPqqmHU;
      string hpdRglfOFb;
      string YVxjkMqmyX;
      string DNaGVJRbhS;
      string CLKmrrySDS;
      string JGZDQIaNoC;
      string zDniQTPXwW;
      string UDgmZMKKqr;
      string NXjeOxnWoM;
      string iDmfSyXbVX;
      string caVfyGZldD;
      if(NbIKBseXMm == hpdRglfOFb){yQVxnbTITT = true;}
      else if(hpdRglfOFb == NbIKBseXMm){luRVzOPqFn = true;}
      if(GoJIRNZADc == YVxjkMqmyX){frhinQQATa = true;}
      else if(YVxjkMqmyX == GoJIRNZADc){nqaCGJDdrw = true;}
      if(JpnCAgCCAI == DNaGVJRbhS){ohnTPmCEgI = true;}
      else if(DNaGVJRbhS == JpnCAgCCAI){xHZUgDSSJg = true;}
      if(YguCMReIwF == CLKmrrySDS){XBskORgoqq = true;}
      else if(CLKmrrySDS == YguCMReIwF){neePsyxpzE = true;}
      if(SPqVtaxZRP == JGZDQIaNoC){eOHCqkrlrh = true;}
      else if(JGZDQIaNoC == SPqVtaxZRP){iqkhLyEFjI = true;}
      if(DjLPWXnFKU == zDniQTPXwW){oYSCOPcCgA = true;}
      else if(zDniQTPXwW == DjLPWXnFKU){LIDJOdVxou = true;}
      if(pbXENYsGuz == UDgmZMKKqr){YPbLueywUV = true;}
      else if(UDgmZMKKqr == pbXENYsGuz){uwgYAJLKJH = true;}
      if(iQDxJtzSIZ == NXjeOxnWoM){iaJbwZakbe = true;}
      if(ickjFoUffo == iDmfSyXbVX){tPLySyhqWz = true;}
      if(dYyaPqqmHU == caVfyGZldD){oeHpRPlwGL = true;}
      while(NXjeOxnWoM == iQDxJtzSIZ){LNemMFVrJi = true;}
      while(iDmfSyXbVX == iDmfSyXbVX){zNhBUfaUBO = true;}
      while(caVfyGZldD == caVfyGZldD){cABDImKMgB = true;}
      if(yQVxnbTITT == true){yQVxnbTITT = false;}
      if(frhinQQATa == true){frhinQQATa = false;}
      if(ohnTPmCEgI == true){ohnTPmCEgI = false;}
      if(XBskORgoqq == true){XBskORgoqq = false;}
      if(eOHCqkrlrh == true){eOHCqkrlrh = false;}
      if(oYSCOPcCgA == true){oYSCOPcCgA = false;}
      if(YPbLueywUV == true){YPbLueywUV = false;}
      if(iaJbwZakbe == true){iaJbwZakbe = false;}
      if(tPLySyhqWz == true){tPLySyhqWz = false;}
      if(oeHpRPlwGL == true){oeHpRPlwGL = false;}
      if(luRVzOPqFn == true){luRVzOPqFn = false;}
      if(nqaCGJDdrw == true){nqaCGJDdrw = false;}
      if(xHZUgDSSJg == true){xHZUgDSSJg = false;}
      if(neePsyxpzE == true){neePsyxpzE = false;}
      if(iqkhLyEFjI == true){iqkhLyEFjI = false;}
      if(LIDJOdVxou == true){LIDJOdVxou = false;}
      if(uwgYAJLKJH == true){uwgYAJLKJH = false;}
      if(LNemMFVrJi == true){LNemMFVrJi = false;}
      if(zNhBUfaUBO == true){zNhBUfaUBO = false;}
      if(cABDImKMgB == true){cABDImKMgB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAUOWUYDRU
{ 
  void EECpzUbjoZ()
  { 
      bool BOkdioYOPR = false;
      bool ZIfBpSFCUn = false;
      bool EqxdwXNBKw = false;
      bool qMJZWWFNAS = false;
      bool LVCSIcpdTb = false;
      bool SuFutKRGhL = false;
      bool aXDSaMyFeS = false;
      bool MqCBcindUS = false;
      bool gihiduHOfL = false;
      bool EyfnqnRjru = false;
      bool ejyBObsDSL = false;
      bool VnlPdroUof = false;
      bool FjZSNOLNJn = false;
      bool QElYnxjfTC = false;
      bool BDuUoQMQKz = false;
      bool yxtLptKfmA = false;
      bool PftetRBMbg = false;
      bool HJAmdBoFdw = false;
      bool BuDJpTJZis = false;
      bool lEsSlVJQZW = false;
      string yOFMgZyJFZ;
      string yQSEeXJsdQ;
      string nVUJGMHjNu;
      string MrHIJUSNER;
      string tgmolJQMTP;
      string tpKnDbtwGU;
      string RNwKNGIJtK;
      string EwnMVGhfWx;
      string wuPxBWhTFg;
      string ZVHjAfjcbf;
      string BGSJKxBxRw;
      string sOYIXWyyIp;
      string YnDMjioEMo;
      string WEEquobFlD;
      string UjBJmLwyMc;
      string hkUkGMDFZb;
      string IxkbYoJhNh;
      string tsLFUoltYX;
      string lpqiHkjSki;
      string lWfKtXyZjy;
      if(yOFMgZyJFZ == BGSJKxBxRw){BOkdioYOPR = true;}
      else if(BGSJKxBxRw == yOFMgZyJFZ){ejyBObsDSL = true;}
      if(yQSEeXJsdQ == sOYIXWyyIp){ZIfBpSFCUn = true;}
      else if(sOYIXWyyIp == yQSEeXJsdQ){VnlPdroUof = true;}
      if(nVUJGMHjNu == YnDMjioEMo){EqxdwXNBKw = true;}
      else if(YnDMjioEMo == nVUJGMHjNu){FjZSNOLNJn = true;}
      if(MrHIJUSNER == WEEquobFlD){qMJZWWFNAS = true;}
      else if(WEEquobFlD == MrHIJUSNER){QElYnxjfTC = true;}
      if(tgmolJQMTP == UjBJmLwyMc){LVCSIcpdTb = true;}
      else if(UjBJmLwyMc == tgmolJQMTP){BDuUoQMQKz = true;}
      if(tpKnDbtwGU == hkUkGMDFZb){SuFutKRGhL = true;}
      else if(hkUkGMDFZb == tpKnDbtwGU){yxtLptKfmA = true;}
      if(RNwKNGIJtK == IxkbYoJhNh){aXDSaMyFeS = true;}
      else if(IxkbYoJhNh == RNwKNGIJtK){PftetRBMbg = true;}
      if(EwnMVGhfWx == tsLFUoltYX){MqCBcindUS = true;}
      if(wuPxBWhTFg == lpqiHkjSki){gihiduHOfL = true;}
      if(ZVHjAfjcbf == lWfKtXyZjy){EyfnqnRjru = true;}
      while(tsLFUoltYX == EwnMVGhfWx){HJAmdBoFdw = true;}
      while(lpqiHkjSki == lpqiHkjSki){BuDJpTJZis = true;}
      while(lWfKtXyZjy == lWfKtXyZjy){lEsSlVJQZW = true;}
      if(BOkdioYOPR == true){BOkdioYOPR = false;}
      if(ZIfBpSFCUn == true){ZIfBpSFCUn = false;}
      if(EqxdwXNBKw == true){EqxdwXNBKw = false;}
      if(qMJZWWFNAS == true){qMJZWWFNAS = false;}
      if(LVCSIcpdTb == true){LVCSIcpdTb = false;}
      if(SuFutKRGhL == true){SuFutKRGhL = false;}
      if(aXDSaMyFeS == true){aXDSaMyFeS = false;}
      if(MqCBcindUS == true){MqCBcindUS = false;}
      if(gihiduHOfL == true){gihiduHOfL = false;}
      if(EyfnqnRjru == true){EyfnqnRjru = false;}
      if(ejyBObsDSL == true){ejyBObsDSL = false;}
      if(VnlPdroUof == true){VnlPdroUof = false;}
      if(FjZSNOLNJn == true){FjZSNOLNJn = false;}
      if(QElYnxjfTC == true){QElYnxjfTC = false;}
      if(BDuUoQMQKz == true){BDuUoQMQKz = false;}
      if(yxtLptKfmA == true){yxtLptKfmA = false;}
      if(PftetRBMbg == true){PftetRBMbg = false;}
      if(HJAmdBoFdw == true){HJAmdBoFdw = false;}
      if(BuDJpTJZis == true){BuDJpTJZis = false;}
      if(lEsSlVJQZW == true){lEsSlVJQZW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMEXKIXKGJ
{ 
  void CyOgKFBPwY()
  { 
      bool JaKJsNAnoG = false;
      bool aiHGuFybUx = false;
      bool qAifOCRhQR = false;
      bool PVBrGjPLbH = false;
      bool DeyWzKhZLb = false;
      bool MTXPUIqeuq = false;
      bool uRWWqEgOzK = false;
      bool pmAMsLCMfE = false;
      bool UqWoEuylXy = false;
      bool sjQjLkHaet = false;
      bool cSZBkZTKVI = false;
      bool FdyqVDuhSw = false;
      bool GuqBRGWPBH = false;
      bool EbhlaCQVDe = false;
      bool bmPOrOkYOH = false;
      bool pZHhmhaYie = false;
      bool DDINDduMQS = false;
      bool mYdmUSecJC = false;
      bool UxBsReTAzr = false;
      bool brlXbYeBKN = false;
      string gUfwrTWrit;
      string xReaOYcjxD;
      string DHyBecmdVj;
      string zqTrMLcBfL;
      string HPzUegLznC;
      string yLqQiYVeRP;
      string frWyuGxlND;
      string waDlunIdVx;
      string QmoSkmzCJm;
      string oxjQeOsBZY;
      string iZlkFWHFVu;
      string QrJTysCDNH;
      string GtbZNzqmHf;
      string tGEwOpBENN;
      string etgNVxnQRl;
      string LpmRSnxLWG;
      string fTxoBKmMFH;
      string ryozcLNOEQ;
      string LZVVUDSmcZ;
      string sogGhKwrML;
      if(gUfwrTWrit == iZlkFWHFVu){JaKJsNAnoG = true;}
      else if(iZlkFWHFVu == gUfwrTWrit){cSZBkZTKVI = true;}
      if(xReaOYcjxD == QrJTysCDNH){aiHGuFybUx = true;}
      else if(QrJTysCDNH == xReaOYcjxD){FdyqVDuhSw = true;}
      if(DHyBecmdVj == GtbZNzqmHf){qAifOCRhQR = true;}
      else if(GtbZNzqmHf == DHyBecmdVj){GuqBRGWPBH = true;}
      if(zqTrMLcBfL == tGEwOpBENN){PVBrGjPLbH = true;}
      else if(tGEwOpBENN == zqTrMLcBfL){EbhlaCQVDe = true;}
      if(HPzUegLznC == etgNVxnQRl){DeyWzKhZLb = true;}
      else if(etgNVxnQRl == HPzUegLznC){bmPOrOkYOH = true;}
      if(yLqQiYVeRP == LpmRSnxLWG){MTXPUIqeuq = true;}
      else if(LpmRSnxLWG == yLqQiYVeRP){pZHhmhaYie = true;}
      if(frWyuGxlND == fTxoBKmMFH){uRWWqEgOzK = true;}
      else if(fTxoBKmMFH == frWyuGxlND){DDINDduMQS = true;}
      if(waDlunIdVx == ryozcLNOEQ){pmAMsLCMfE = true;}
      if(QmoSkmzCJm == LZVVUDSmcZ){UqWoEuylXy = true;}
      if(oxjQeOsBZY == sogGhKwrML){sjQjLkHaet = true;}
      while(ryozcLNOEQ == waDlunIdVx){mYdmUSecJC = true;}
      while(LZVVUDSmcZ == LZVVUDSmcZ){UxBsReTAzr = true;}
      while(sogGhKwrML == sogGhKwrML){brlXbYeBKN = true;}
      if(JaKJsNAnoG == true){JaKJsNAnoG = false;}
      if(aiHGuFybUx == true){aiHGuFybUx = false;}
      if(qAifOCRhQR == true){qAifOCRhQR = false;}
      if(PVBrGjPLbH == true){PVBrGjPLbH = false;}
      if(DeyWzKhZLb == true){DeyWzKhZLb = false;}
      if(MTXPUIqeuq == true){MTXPUIqeuq = false;}
      if(uRWWqEgOzK == true){uRWWqEgOzK = false;}
      if(pmAMsLCMfE == true){pmAMsLCMfE = false;}
      if(UqWoEuylXy == true){UqWoEuylXy = false;}
      if(sjQjLkHaet == true){sjQjLkHaet = false;}
      if(cSZBkZTKVI == true){cSZBkZTKVI = false;}
      if(FdyqVDuhSw == true){FdyqVDuhSw = false;}
      if(GuqBRGWPBH == true){GuqBRGWPBH = false;}
      if(EbhlaCQVDe == true){EbhlaCQVDe = false;}
      if(bmPOrOkYOH == true){bmPOrOkYOH = false;}
      if(pZHhmhaYie == true){pZHhmhaYie = false;}
      if(DDINDduMQS == true){DDINDduMQS = false;}
      if(mYdmUSecJC == true){mYdmUSecJC = false;}
      if(UxBsReTAzr == true){UxBsReTAzr = false;}
      if(brlXbYeBKN == true){brlXbYeBKN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPJGWOHXPX
{ 
  void FYKHHLqmpw()
  { 
      bool ufWzMIGhcW = false;
      bool eaOfUBppFw = false;
      bool IcOlfefEnm = false;
      bool HaAtCHTzZI = false;
      bool FHfKYkTNlb = false;
      bool SexkrRRkSh = false;
      bool bBtoPEaUdN = false;
      bool hqPxpAwEMt = false;
      bool LSRMUbcOCj = false;
      bool pifrfDNqtU = false;
      bool KzjYtaPAuq = false;
      bool UMXYVJihUn = false;
      bool aMSsWyLWQl = false;
      bool mFJqjMhsSs = false;
      bool McTKOcKHVV = false;
      bool TeVFsyfpBu = false;
      bool PriIEPDgoJ = false;
      bool bpPabyrHet = false;
      bool nEAuRHjDxl = false;
      bool frqWdUsKGz = false;
      string kktHEgIIol;
      string qwonYVMYXr;
      string mTFFflgdoj;
      string KZynFlxraf;
      string LNqytIhkwy;
      string ReiDLQeoaS;
      string AeSFbRxAhm;
      string YUyrgYbHKX;
      string DugpRepucn;
      string GHQHegtlWb;
      string KgDJZwfqVl;
      string oXeDPFxbmw;
      string bCXtfQEqNA;
      string dpjhMVqWQV;
      string zzYpzicNrZ;
      string iRzaAIJJcI;
      string rocVIzmwps;
      string NZLQxcchtx;
      string npymQLpJhE;
      string MhtHcJVChA;
      if(kktHEgIIol == KgDJZwfqVl){ufWzMIGhcW = true;}
      else if(KgDJZwfqVl == kktHEgIIol){KzjYtaPAuq = true;}
      if(qwonYVMYXr == oXeDPFxbmw){eaOfUBppFw = true;}
      else if(oXeDPFxbmw == qwonYVMYXr){UMXYVJihUn = true;}
      if(mTFFflgdoj == bCXtfQEqNA){IcOlfefEnm = true;}
      else if(bCXtfQEqNA == mTFFflgdoj){aMSsWyLWQl = true;}
      if(KZynFlxraf == dpjhMVqWQV){HaAtCHTzZI = true;}
      else if(dpjhMVqWQV == KZynFlxraf){mFJqjMhsSs = true;}
      if(LNqytIhkwy == zzYpzicNrZ){FHfKYkTNlb = true;}
      else if(zzYpzicNrZ == LNqytIhkwy){McTKOcKHVV = true;}
      if(ReiDLQeoaS == iRzaAIJJcI){SexkrRRkSh = true;}
      else if(iRzaAIJJcI == ReiDLQeoaS){TeVFsyfpBu = true;}
      if(AeSFbRxAhm == rocVIzmwps){bBtoPEaUdN = true;}
      else if(rocVIzmwps == AeSFbRxAhm){PriIEPDgoJ = true;}
      if(YUyrgYbHKX == NZLQxcchtx){hqPxpAwEMt = true;}
      if(DugpRepucn == npymQLpJhE){LSRMUbcOCj = true;}
      if(GHQHegtlWb == MhtHcJVChA){pifrfDNqtU = true;}
      while(NZLQxcchtx == YUyrgYbHKX){bpPabyrHet = true;}
      while(npymQLpJhE == npymQLpJhE){nEAuRHjDxl = true;}
      while(MhtHcJVChA == MhtHcJVChA){frqWdUsKGz = true;}
      if(ufWzMIGhcW == true){ufWzMIGhcW = false;}
      if(eaOfUBppFw == true){eaOfUBppFw = false;}
      if(IcOlfefEnm == true){IcOlfefEnm = false;}
      if(HaAtCHTzZI == true){HaAtCHTzZI = false;}
      if(FHfKYkTNlb == true){FHfKYkTNlb = false;}
      if(SexkrRRkSh == true){SexkrRRkSh = false;}
      if(bBtoPEaUdN == true){bBtoPEaUdN = false;}
      if(hqPxpAwEMt == true){hqPxpAwEMt = false;}
      if(LSRMUbcOCj == true){LSRMUbcOCj = false;}
      if(pifrfDNqtU == true){pifrfDNqtU = false;}
      if(KzjYtaPAuq == true){KzjYtaPAuq = false;}
      if(UMXYVJihUn == true){UMXYVJihUn = false;}
      if(aMSsWyLWQl == true){aMSsWyLWQl = false;}
      if(mFJqjMhsSs == true){mFJqjMhsSs = false;}
      if(McTKOcKHVV == true){McTKOcKHVV = false;}
      if(TeVFsyfpBu == true){TeVFsyfpBu = false;}
      if(PriIEPDgoJ == true){PriIEPDgoJ = false;}
      if(bpPabyrHet == true){bpPabyrHet = false;}
      if(nEAuRHjDxl == true){nEAuRHjDxl = false;}
      if(frqWdUsKGz == true){frqWdUsKGz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMUIBXIMXY
{ 
  void UWJRDWjIxQ()
  { 
      bool dsEABszUdX = false;
      bool VONaPXfFfo = false;
      bool hJGWcpJRRE = false;
      bool TeeNchZJiw = false;
      bool SQgdQRCQox = false;
      bool rAROJTlgXK = false;
      bool ihDZDqjzxh = false;
      bool yWWiWQbcGK = false;
      bool nscULSMQEJ = false;
      bool urkYMjNHaZ = false;
      bool hCTGyUdhqr = false;
      bool rJaMWpFiNj = false;
      bool dSummGkxWl = false;
      bool DTCgckYVVq = false;
      bool oeYLRkRYBV = false;
      bool detpuOGfTr = false;
      bool ifKFoXHsjk = false;
      bool RjMWuztjVB = false;
      bool nMwBIXZLkN = false;
      bool drCcHITTVt = false;
      string ztfLbOoNxU;
      string NJmAqkfaGX;
      string ESlyoRBydQ;
      string CJojHwteIN;
      string OZBSaMuejL;
      string wbbPafHgWK;
      string NqjfSETCsu;
      string qBRsIdQSWc;
      string WVORTZgYIa;
      string nMIyzXoVAW;
      string rrloUuKiGw;
      string PnJsnqbSMr;
      string XttRGdrTsk;
      string ouSAjdjZwY;
      string PxSLLzCOJI;
      string uWIHyxxThq;
      string CppUHTVJJJ;
      string GBWncabiFH;
      string adJjoSlLCl;
      string gQrEVYGxDq;
      if(ztfLbOoNxU == rrloUuKiGw){dsEABszUdX = true;}
      else if(rrloUuKiGw == ztfLbOoNxU){hCTGyUdhqr = true;}
      if(NJmAqkfaGX == PnJsnqbSMr){VONaPXfFfo = true;}
      else if(PnJsnqbSMr == NJmAqkfaGX){rJaMWpFiNj = true;}
      if(ESlyoRBydQ == XttRGdrTsk){hJGWcpJRRE = true;}
      else if(XttRGdrTsk == ESlyoRBydQ){dSummGkxWl = true;}
      if(CJojHwteIN == ouSAjdjZwY){TeeNchZJiw = true;}
      else if(ouSAjdjZwY == CJojHwteIN){DTCgckYVVq = true;}
      if(OZBSaMuejL == PxSLLzCOJI){SQgdQRCQox = true;}
      else if(PxSLLzCOJI == OZBSaMuejL){oeYLRkRYBV = true;}
      if(wbbPafHgWK == uWIHyxxThq){rAROJTlgXK = true;}
      else if(uWIHyxxThq == wbbPafHgWK){detpuOGfTr = true;}
      if(NqjfSETCsu == CppUHTVJJJ){ihDZDqjzxh = true;}
      else if(CppUHTVJJJ == NqjfSETCsu){ifKFoXHsjk = true;}
      if(qBRsIdQSWc == GBWncabiFH){yWWiWQbcGK = true;}
      if(WVORTZgYIa == adJjoSlLCl){nscULSMQEJ = true;}
      if(nMIyzXoVAW == gQrEVYGxDq){urkYMjNHaZ = true;}
      while(GBWncabiFH == qBRsIdQSWc){RjMWuztjVB = true;}
      while(adJjoSlLCl == adJjoSlLCl){nMwBIXZLkN = true;}
      while(gQrEVYGxDq == gQrEVYGxDq){drCcHITTVt = true;}
      if(dsEABszUdX == true){dsEABszUdX = false;}
      if(VONaPXfFfo == true){VONaPXfFfo = false;}
      if(hJGWcpJRRE == true){hJGWcpJRRE = false;}
      if(TeeNchZJiw == true){TeeNchZJiw = false;}
      if(SQgdQRCQox == true){SQgdQRCQox = false;}
      if(rAROJTlgXK == true){rAROJTlgXK = false;}
      if(ihDZDqjzxh == true){ihDZDqjzxh = false;}
      if(yWWiWQbcGK == true){yWWiWQbcGK = false;}
      if(nscULSMQEJ == true){nscULSMQEJ = false;}
      if(urkYMjNHaZ == true){urkYMjNHaZ = false;}
      if(hCTGyUdhqr == true){hCTGyUdhqr = false;}
      if(rJaMWpFiNj == true){rJaMWpFiNj = false;}
      if(dSummGkxWl == true){dSummGkxWl = false;}
      if(DTCgckYVVq == true){DTCgckYVVq = false;}
      if(oeYLRkRYBV == true){oeYLRkRYBV = false;}
      if(detpuOGfTr == true){detpuOGfTr = false;}
      if(ifKFoXHsjk == true){ifKFoXHsjk = false;}
      if(RjMWuztjVB == true){RjMWuztjVB = false;}
      if(nMwBIXZLkN == true){nMwBIXZLkN = false;}
      if(drCcHITTVt == true){drCcHITTVt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUINOUGLPW
{ 
  void wJNGJxuSAK()
  { 
      bool uaDrBVuDsi = false;
      bool xtcDAXAGiH = false;
      bool LWxCXakyyi = false;
      bool BqdksuqIQn = false;
      bool ZfHhcdirkI = false;
      bool lZjAjYdBUZ = false;
      bool kxEKhFQqKF = false;
      bool frptgePPZs = false;
      bool qrMpwaHcBT = false;
      bool QpmqDbbwAW = false;
      bool NrhfbsjoSE = false;
      bool JNbahrjONG = false;
      bool ymopnpEyqE = false;
      bool DSPCfzJgOC = false;
      bool qSKwKDNMJK = false;
      bool rMhsYZDrqk = false;
      bool okyNBpyYui = false;
      bool hDALPecsek = false;
      bool brofMpkVdG = false;
      bool wRocNFTwtU = false;
      string ZbBRCoJHwo;
      string tNElzUqgUT;
      string jbzQpsXBXR;
      string CVSTEjWUAP;
      string fIsLdalROg;
      string TXjwExbjaI;
      string QHjdmYtjgO;
      string yVgFmahnmP;
      string GGmqydkWOH;
      string HlsqyYYPXF;
      string fBjzhxqeJd;
      string OnwLBJUsfI;
      string nXVZHLcoGO;
      string BSPhiFWmIA;
      string mFNjrSogon;
      string DfiOQIfKqW;
      string TBYtcwXOcw;
      string mgjeUhKkhn;
      string VuARKVjBQa;
      string YLwlglgSHw;
      if(ZbBRCoJHwo == fBjzhxqeJd){uaDrBVuDsi = true;}
      else if(fBjzhxqeJd == ZbBRCoJHwo){NrhfbsjoSE = true;}
      if(tNElzUqgUT == OnwLBJUsfI){xtcDAXAGiH = true;}
      else if(OnwLBJUsfI == tNElzUqgUT){JNbahrjONG = true;}
      if(jbzQpsXBXR == nXVZHLcoGO){LWxCXakyyi = true;}
      else if(nXVZHLcoGO == jbzQpsXBXR){ymopnpEyqE = true;}
      if(CVSTEjWUAP == BSPhiFWmIA){BqdksuqIQn = true;}
      else if(BSPhiFWmIA == CVSTEjWUAP){DSPCfzJgOC = true;}
      if(fIsLdalROg == mFNjrSogon){ZfHhcdirkI = true;}
      else if(mFNjrSogon == fIsLdalROg){qSKwKDNMJK = true;}
      if(TXjwExbjaI == DfiOQIfKqW){lZjAjYdBUZ = true;}
      else if(DfiOQIfKqW == TXjwExbjaI){rMhsYZDrqk = true;}
      if(QHjdmYtjgO == TBYtcwXOcw){kxEKhFQqKF = true;}
      else if(TBYtcwXOcw == QHjdmYtjgO){okyNBpyYui = true;}
      if(yVgFmahnmP == mgjeUhKkhn){frptgePPZs = true;}
      if(GGmqydkWOH == VuARKVjBQa){qrMpwaHcBT = true;}
      if(HlsqyYYPXF == YLwlglgSHw){QpmqDbbwAW = true;}
      while(mgjeUhKkhn == yVgFmahnmP){hDALPecsek = true;}
      while(VuARKVjBQa == VuARKVjBQa){brofMpkVdG = true;}
      while(YLwlglgSHw == YLwlglgSHw){wRocNFTwtU = true;}
      if(uaDrBVuDsi == true){uaDrBVuDsi = false;}
      if(xtcDAXAGiH == true){xtcDAXAGiH = false;}
      if(LWxCXakyyi == true){LWxCXakyyi = false;}
      if(BqdksuqIQn == true){BqdksuqIQn = false;}
      if(ZfHhcdirkI == true){ZfHhcdirkI = false;}
      if(lZjAjYdBUZ == true){lZjAjYdBUZ = false;}
      if(kxEKhFQqKF == true){kxEKhFQqKF = false;}
      if(frptgePPZs == true){frptgePPZs = false;}
      if(qrMpwaHcBT == true){qrMpwaHcBT = false;}
      if(QpmqDbbwAW == true){QpmqDbbwAW = false;}
      if(NrhfbsjoSE == true){NrhfbsjoSE = false;}
      if(JNbahrjONG == true){JNbahrjONG = false;}
      if(ymopnpEyqE == true){ymopnpEyqE = false;}
      if(DSPCfzJgOC == true){DSPCfzJgOC = false;}
      if(qSKwKDNMJK == true){qSKwKDNMJK = false;}
      if(rMhsYZDrqk == true){rMhsYZDrqk = false;}
      if(okyNBpyYui == true){okyNBpyYui = false;}
      if(hDALPecsek == true){hDALPecsek = false;}
      if(brofMpkVdG == true){brofMpkVdG = false;}
      if(wRocNFTwtU == true){wRocNFTwtU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEXCJQBHLZ
{ 
  void nuBtCPEFCQ()
  { 
      bool xCsrpWIeJQ = false;
      bool kRzCdeXGYV = false;
      bool aEIByDyGeT = false;
      bool qNIGbElcRR = false;
      bool STYyGAnlSA = false;
      bool yEJdwrsrtl = false;
      bool YCAoYXIsZY = false;
      bool suoHDGeKtx = false;
      bool OLmeVmEeJi = false;
      bool LshesQTjYi = false;
      bool quLsGDPCap = false;
      bool MixwWMOUTl = false;
      bool SdipNzMJNl = false;
      bool lukKGTAsYR = false;
      bool XCETWbukHf = false;
      bool BzQlPNLUfH = false;
      bool qGnnDRympD = false;
      bool MUuCOQZPTk = false;
      bool EaBhkldytr = false;
      bool IeNRZROPPF = false;
      string iCZLXpNSju;
      string PnqzomGoub;
      string QloklrNIhT;
      string CJhCKVXgwR;
      string RgGzDhUsFh;
      string CQgXTwNoYf;
      string cFkQrGFnoS;
      string PZsdKifpgE;
      string XUCAQlcKhN;
      string IhHPoLwoGx;
      string cfDlSbWDMk;
      string QWHUHHCjzG;
      string ctFaKgRdny;
      string mpijarQPho;
      string PZxxxkZmIg;
      string JLpAThZcbk;
      string JsOOxanXsP;
      string qlCKqDxIcZ;
      string GeUHobziPr;
      string RnnweWLizW;
      if(iCZLXpNSju == cfDlSbWDMk){xCsrpWIeJQ = true;}
      else if(cfDlSbWDMk == iCZLXpNSju){quLsGDPCap = true;}
      if(PnqzomGoub == QWHUHHCjzG){kRzCdeXGYV = true;}
      else if(QWHUHHCjzG == PnqzomGoub){MixwWMOUTl = true;}
      if(QloklrNIhT == ctFaKgRdny){aEIByDyGeT = true;}
      else if(ctFaKgRdny == QloklrNIhT){SdipNzMJNl = true;}
      if(CJhCKVXgwR == mpijarQPho){qNIGbElcRR = true;}
      else if(mpijarQPho == CJhCKVXgwR){lukKGTAsYR = true;}
      if(RgGzDhUsFh == PZxxxkZmIg){STYyGAnlSA = true;}
      else if(PZxxxkZmIg == RgGzDhUsFh){XCETWbukHf = true;}
      if(CQgXTwNoYf == JLpAThZcbk){yEJdwrsrtl = true;}
      else if(JLpAThZcbk == CQgXTwNoYf){BzQlPNLUfH = true;}
      if(cFkQrGFnoS == JsOOxanXsP){YCAoYXIsZY = true;}
      else if(JsOOxanXsP == cFkQrGFnoS){qGnnDRympD = true;}
      if(PZsdKifpgE == qlCKqDxIcZ){suoHDGeKtx = true;}
      if(XUCAQlcKhN == GeUHobziPr){OLmeVmEeJi = true;}
      if(IhHPoLwoGx == RnnweWLizW){LshesQTjYi = true;}
      while(qlCKqDxIcZ == PZsdKifpgE){MUuCOQZPTk = true;}
      while(GeUHobziPr == GeUHobziPr){EaBhkldytr = true;}
      while(RnnweWLizW == RnnweWLizW){IeNRZROPPF = true;}
      if(xCsrpWIeJQ == true){xCsrpWIeJQ = false;}
      if(kRzCdeXGYV == true){kRzCdeXGYV = false;}
      if(aEIByDyGeT == true){aEIByDyGeT = false;}
      if(qNIGbElcRR == true){qNIGbElcRR = false;}
      if(STYyGAnlSA == true){STYyGAnlSA = false;}
      if(yEJdwrsrtl == true){yEJdwrsrtl = false;}
      if(YCAoYXIsZY == true){YCAoYXIsZY = false;}
      if(suoHDGeKtx == true){suoHDGeKtx = false;}
      if(OLmeVmEeJi == true){OLmeVmEeJi = false;}
      if(LshesQTjYi == true){LshesQTjYi = false;}
      if(quLsGDPCap == true){quLsGDPCap = false;}
      if(MixwWMOUTl == true){MixwWMOUTl = false;}
      if(SdipNzMJNl == true){SdipNzMJNl = false;}
      if(lukKGTAsYR == true){lukKGTAsYR = false;}
      if(XCETWbukHf == true){XCETWbukHf = false;}
      if(BzQlPNLUfH == true){BzQlPNLUfH = false;}
      if(qGnnDRympD == true){qGnnDRympD = false;}
      if(MUuCOQZPTk == true){MUuCOQZPTk = false;}
      if(EaBhkldytr == true){EaBhkldytr = false;}
      if(IeNRZROPPF == true){IeNRZROPPF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEPHTALTUA
{ 
  void LSHkLQjTdK()
  { 
      bool qyMgUDOgpW = false;
      bool yjPqftUVyB = false;
      bool fFPqSCHPNj = false;
      bool yWMTkdbetY = false;
      bool HRPqCjiTPY = false;
      bool NbPjlkhUNR = false;
      bool uySGXbWwFC = false;
      bool RoaYtOpYni = false;
      bool TnAnWWGcgz = false;
      bool uGRccIyJTZ = false;
      bool MlOMHYAqoW = false;
      bool uJfexHyeiB = false;
      bool UtOFGKXywk = false;
      bool PgFNWhYmgx = false;
      bool WPmKEkZleV = false;
      bool KTZRFSWIGw = false;
      bool BCtEGNERHP = false;
      bool hKxldEGEBU = false;
      bool kkSaZwHmIE = false;
      bool KQgkwUUiDp = false;
      string azPSTubUtC;
      string eyeTbjgufa;
      string SXPUseCuhf;
      string nqKosPlGAT;
      string EdMGlyhNNN;
      string CJjwJDjuYn;
      string sglNOmnoZL;
      string xatMWnLIhu;
      string xogUdeHNfp;
      string eqhMaWqyrz;
      string JsmBPbPXZU;
      string rbNcqDzQji;
      string fZJjgGrhlz;
      string xMPhkDBfFC;
      string PinKxDdEUW;
      string WaOJTjiCUJ;
      string igkZXeLerm;
      string BTLgSwkzlc;
      string cnMPbVyFOB;
      string TzLuThxOlS;
      if(azPSTubUtC == JsmBPbPXZU){qyMgUDOgpW = true;}
      else if(JsmBPbPXZU == azPSTubUtC){MlOMHYAqoW = true;}
      if(eyeTbjgufa == rbNcqDzQji){yjPqftUVyB = true;}
      else if(rbNcqDzQji == eyeTbjgufa){uJfexHyeiB = true;}
      if(SXPUseCuhf == fZJjgGrhlz){fFPqSCHPNj = true;}
      else if(fZJjgGrhlz == SXPUseCuhf){UtOFGKXywk = true;}
      if(nqKosPlGAT == xMPhkDBfFC){yWMTkdbetY = true;}
      else if(xMPhkDBfFC == nqKosPlGAT){PgFNWhYmgx = true;}
      if(EdMGlyhNNN == PinKxDdEUW){HRPqCjiTPY = true;}
      else if(PinKxDdEUW == EdMGlyhNNN){WPmKEkZleV = true;}
      if(CJjwJDjuYn == WaOJTjiCUJ){NbPjlkhUNR = true;}
      else if(WaOJTjiCUJ == CJjwJDjuYn){KTZRFSWIGw = true;}
      if(sglNOmnoZL == igkZXeLerm){uySGXbWwFC = true;}
      else if(igkZXeLerm == sglNOmnoZL){BCtEGNERHP = true;}
      if(xatMWnLIhu == BTLgSwkzlc){RoaYtOpYni = true;}
      if(xogUdeHNfp == cnMPbVyFOB){TnAnWWGcgz = true;}
      if(eqhMaWqyrz == TzLuThxOlS){uGRccIyJTZ = true;}
      while(BTLgSwkzlc == xatMWnLIhu){hKxldEGEBU = true;}
      while(cnMPbVyFOB == cnMPbVyFOB){kkSaZwHmIE = true;}
      while(TzLuThxOlS == TzLuThxOlS){KQgkwUUiDp = true;}
      if(qyMgUDOgpW == true){qyMgUDOgpW = false;}
      if(yjPqftUVyB == true){yjPqftUVyB = false;}
      if(fFPqSCHPNj == true){fFPqSCHPNj = false;}
      if(yWMTkdbetY == true){yWMTkdbetY = false;}
      if(HRPqCjiTPY == true){HRPqCjiTPY = false;}
      if(NbPjlkhUNR == true){NbPjlkhUNR = false;}
      if(uySGXbWwFC == true){uySGXbWwFC = false;}
      if(RoaYtOpYni == true){RoaYtOpYni = false;}
      if(TnAnWWGcgz == true){TnAnWWGcgz = false;}
      if(uGRccIyJTZ == true){uGRccIyJTZ = false;}
      if(MlOMHYAqoW == true){MlOMHYAqoW = false;}
      if(uJfexHyeiB == true){uJfexHyeiB = false;}
      if(UtOFGKXywk == true){UtOFGKXywk = false;}
      if(PgFNWhYmgx == true){PgFNWhYmgx = false;}
      if(WPmKEkZleV == true){WPmKEkZleV = false;}
      if(KTZRFSWIGw == true){KTZRFSWIGw = false;}
      if(BCtEGNERHP == true){BCtEGNERHP = false;}
      if(hKxldEGEBU == true){hKxldEGEBU = false;}
      if(kkSaZwHmIE == true){kkSaZwHmIE = false;}
      if(KQgkwUUiDp == true){KQgkwUUiDp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOYROXTSFW
{ 
  void LGJDAGAJbI()
  { 
      bool jPgrQBGAIh = false;
      bool uCgFwWJbbA = false;
      bool rWqEatgScZ = false;
      bool IiaWnYSFeb = false;
      bool juljudsNnH = false;
      bool UrrteNYbRW = false;
      bool UmXhZMbKRX = false;
      bool DDxAQwjGIx = false;
      bool ATeVEPqfrZ = false;
      bool ApnHGwXDJi = false;
      bool BiwPDQtqdh = false;
      bool cRSTVAHBcJ = false;
      bool UwSqWNPosU = false;
      bool XgxYuRXORn = false;
      bool VACJwiWUlF = false;
      bool nWZzOFPErp = false;
      bool BExIJwTtXD = false;
      bool csjonUtItn = false;
      bool ptDnfBGxKp = false;
      bool CSVamRCszz = false;
      string WnJrHhDiHw;
      string QQwoIkSTGe;
      string KCDLkIcEqw;
      string KwbHaJKXKO;
      string zadqAQVtCX;
      string tQxRbTjyHy;
      string FzqLlTnnNz;
      string ZtJqfjYMKT;
      string lhBSBtyKeH;
      string YMQLJAiSEf;
      string chgDyAGGkr;
      string uXmmLWxYJr;
      string UcIFZNcyhf;
      string AFHdqEBxUB;
      string mrZmMBYczl;
      string CKIMLzYadj;
      string WIXFqoQJwH;
      string UADIEcDVsY;
      string nzyucpwtSq;
      string faSjeeTTuW;
      if(WnJrHhDiHw == chgDyAGGkr){jPgrQBGAIh = true;}
      else if(chgDyAGGkr == WnJrHhDiHw){BiwPDQtqdh = true;}
      if(QQwoIkSTGe == uXmmLWxYJr){uCgFwWJbbA = true;}
      else if(uXmmLWxYJr == QQwoIkSTGe){cRSTVAHBcJ = true;}
      if(KCDLkIcEqw == UcIFZNcyhf){rWqEatgScZ = true;}
      else if(UcIFZNcyhf == KCDLkIcEqw){UwSqWNPosU = true;}
      if(KwbHaJKXKO == AFHdqEBxUB){IiaWnYSFeb = true;}
      else if(AFHdqEBxUB == KwbHaJKXKO){XgxYuRXORn = true;}
      if(zadqAQVtCX == mrZmMBYczl){juljudsNnH = true;}
      else if(mrZmMBYczl == zadqAQVtCX){VACJwiWUlF = true;}
      if(tQxRbTjyHy == CKIMLzYadj){UrrteNYbRW = true;}
      else if(CKIMLzYadj == tQxRbTjyHy){nWZzOFPErp = true;}
      if(FzqLlTnnNz == WIXFqoQJwH){UmXhZMbKRX = true;}
      else if(WIXFqoQJwH == FzqLlTnnNz){BExIJwTtXD = true;}
      if(ZtJqfjYMKT == UADIEcDVsY){DDxAQwjGIx = true;}
      if(lhBSBtyKeH == nzyucpwtSq){ATeVEPqfrZ = true;}
      if(YMQLJAiSEf == faSjeeTTuW){ApnHGwXDJi = true;}
      while(UADIEcDVsY == ZtJqfjYMKT){csjonUtItn = true;}
      while(nzyucpwtSq == nzyucpwtSq){ptDnfBGxKp = true;}
      while(faSjeeTTuW == faSjeeTTuW){CSVamRCszz = true;}
      if(jPgrQBGAIh == true){jPgrQBGAIh = false;}
      if(uCgFwWJbbA == true){uCgFwWJbbA = false;}
      if(rWqEatgScZ == true){rWqEatgScZ = false;}
      if(IiaWnYSFeb == true){IiaWnYSFeb = false;}
      if(juljudsNnH == true){juljudsNnH = false;}
      if(UrrteNYbRW == true){UrrteNYbRW = false;}
      if(UmXhZMbKRX == true){UmXhZMbKRX = false;}
      if(DDxAQwjGIx == true){DDxAQwjGIx = false;}
      if(ATeVEPqfrZ == true){ATeVEPqfrZ = false;}
      if(ApnHGwXDJi == true){ApnHGwXDJi = false;}
      if(BiwPDQtqdh == true){BiwPDQtqdh = false;}
      if(cRSTVAHBcJ == true){cRSTVAHBcJ = false;}
      if(UwSqWNPosU == true){UwSqWNPosU = false;}
      if(XgxYuRXORn == true){XgxYuRXORn = false;}
      if(VACJwiWUlF == true){VACJwiWUlF = false;}
      if(nWZzOFPErp == true){nWZzOFPErp = false;}
      if(BExIJwTtXD == true){BExIJwTtXD = false;}
      if(csjonUtItn == true){csjonUtItn = false;}
      if(ptDnfBGxKp == true){ptDnfBGxKp = false;}
      if(CSVamRCszz == true){CSVamRCszz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPXKEBNRGL
{ 
  void KbUZMCRuDK()
  { 
      bool xaZSfzXLxW = false;
      bool NXGfdZXPEx = false;
      bool AWWTMWmIJV = false;
      bool xgzTBdkwEF = false;
      bool tFqHTKpary = false;
      bool RsMUaaEGGI = false;
      bool MOBbZfXmdA = false;
      bool oaLyCufOAB = false;
      bool gMPLEDUdra = false;
      bool YeouseDPhm = false;
      bool lDwrIpgNSe = false;
      bool uoGEbzzoWV = false;
      bool LttDaKlQFX = false;
      bool qPfMOcPXCN = false;
      bool WGLNejXjSs = false;
      bool fOrMarIsQy = false;
      bool DPHuneJspy = false;
      bool jbmJyFhgXq = false;
      bool lByMrcXTkV = false;
      bool UWGEJGyQYA = false;
      string pTalwHsRut;
      string EWfJuVyTpE;
      string JORMQRunIR;
      string QpPNxTBpKh;
      string eyQZIoGDOl;
      string hYshuaBNUe;
      string MFIcdNGRLa;
      string UIJHYKyrDb;
      string LqYWjqwhSW;
      string SmUfVZomuu;
      string inqmQZPlIk;
      string cIKsSUflsm;
      string QXzoIgmckz;
      string VKxIrXzkGK;
      string bKZgsJcbNB;
      string tDtIdLoCei;
      string llAJORLBBt;
      string UtfhKGxRuz;
      string ELOjERQneg;
      string hxGWYoJQRb;
      if(pTalwHsRut == inqmQZPlIk){xaZSfzXLxW = true;}
      else if(inqmQZPlIk == pTalwHsRut){lDwrIpgNSe = true;}
      if(EWfJuVyTpE == cIKsSUflsm){NXGfdZXPEx = true;}
      else if(cIKsSUflsm == EWfJuVyTpE){uoGEbzzoWV = true;}
      if(JORMQRunIR == QXzoIgmckz){AWWTMWmIJV = true;}
      else if(QXzoIgmckz == JORMQRunIR){LttDaKlQFX = true;}
      if(QpPNxTBpKh == VKxIrXzkGK){xgzTBdkwEF = true;}
      else if(VKxIrXzkGK == QpPNxTBpKh){qPfMOcPXCN = true;}
      if(eyQZIoGDOl == bKZgsJcbNB){tFqHTKpary = true;}
      else if(bKZgsJcbNB == eyQZIoGDOl){WGLNejXjSs = true;}
      if(hYshuaBNUe == tDtIdLoCei){RsMUaaEGGI = true;}
      else if(tDtIdLoCei == hYshuaBNUe){fOrMarIsQy = true;}
      if(MFIcdNGRLa == llAJORLBBt){MOBbZfXmdA = true;}
      else if(llAJORLBBt == MFIcdNGRLa){DPHuneJspy = true;}
      if(UIJHYKyrDb == UtfhKGxRuz){oaLyCufOAB = true;}
      if(LqYWjqwhSW == ELOjERQneg){gMPLEDUdra = true;}
      if(SmUfVZomuu == hxGWYoJQRb){YeouseDPhm = true;}
      while(UtfhKGxRuz == UIJHYKyrDb){jbmJyFhgXq = true;}
      while(ELOjERQneg == ELOjERQneg){lByMrcXTkV = true;}
      while(hxGWYoJQRb == hxGWYoJQRb){UWGEJGyQYA = true;}
      if(xaZSfzXLxW == true){xaZSfzXLxW = false;}
      if(NXGfdZXPEx == true){NXGfdZXPEx = false;}
      if(AWWTMWmIJV == true){AWWTMWmIJV = false;}
      if(xgzTBdkwEF == true){xgzTBdkwEF = false;}
      if(tFqHTKpary == true){tFqHTKpary = false;}
      if(RsMUaaEGGI == true){RsMUaaEGGI = false;}
      if(MOBbZfXmdA == true){MOBbZfXmdA = false;}
      if(oaLyCufOAB == true){oaLyCufOAB = false;}
      if(gMPLEDUdra == true){gMPLEDUdra = false;}
      if(YeouseDPhm == true){YeouseDPhm = false;}
      if(lDwrIpgNSe == true){lDwrIpgNSe = false;}
      if(uoGEbzzoWV == true){uoGEbzzoWV = false;}
      if(LttDaKlQFX == true){LttDaKlQFX = false;}
      if(qPfMOcPXCN == true){qPfMOcPXCN = false;}
      if(WGLNejXjSs == true){WGLNejXjSs = false;}
      if(fOrMarIsQy == true){fOrMarIsQy = false;}
      if(DPHuneJspy == true){DPHuneJspy = false;}
      if(jbmJyFhgXq == true){jbmJyFhgXq = false;}
      if(lByMrcXTkV == true){lByMrcXTkV = false;}
      if(UWGEJGyQYA == true){UWGEJGyQYA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGJFUZQPBQ
{ 
  void hkuEpJXPoV()
  { 
      bool qhqVlolgZo = false;
      bool pVgCKddqYD = false;
      bool nKxQMKKkcH = false;
      bool NKFgpnHXSq = false;
      bool BIEolUabhE = false;
      bool zRTpdfjZIb = false;
      bool dAESbfPAMW = false;
      bool VFYgCeGIdq = false;
      bool iiDXHupPCJ = false;
      bool EgOpMAElMG = false;
      bool FaPLisslmy = false;
      bool ZauQsuxfKf = false;
      bool ozxCSoqiTB = false;
      bool ZUuXlHSqoO = false;
      bool CDcEjckxwR = false;
      bool DYafRFcNss = false;
      bool CKRlXEfXek = false;
      bool bFqwdkWrSo = false;
      bool DslCxBsOFg = false;
      bool dFyuLqkpfe = false;
      string RPSQULHHNR;
      string inPWwqZjCw;
      string rGDQfkqmMU;
      string qqXBTWgnZf;
      string CRIUhMTcYY;
      string yAcJVKMCki;
      string UTtsaqPODY;
      string KlKVtayihT;
      string RNOnWpNOeI;
      string KdCqLiWPtp;
      string wEZzNLpHPt;
      string MdTRQGEFWj;
      string dBitOfiSKK;
      string EinqWMnPaK;
      string zGyjwgKkZF;
      string dQrJMtVfjg;
      string bWwFpdobtE;
      string SoeLjWDzyh;
      string VysFfmpdec;
      string qIesicJssR;
      if(RPSQULHHNR == wEZzNLpHPt){qhqVlolgZo = true;}
      else if(wEZzNLpHPt == RPSQULHHNR){FaPLisslmy = true;}
      if(inPWwqZjCw == MdTRQGEFWj){pVgCKddqYD = true;}
      else if(MdTRQGEFWj == inPWwqZjCw){ZauQsuxfKf = true;}
      if(rGDQfkqmMU == dBitOfiSKK){nKxQMKKkcH = true;}
      else if(dBitOfiSKK == rGDQfkqmMU){ozxCSoqiTB = true;}
      if(qqXBTWgnZf == EinqWMnPaK){NKFgpnHXSq = true;}
      else if(EinqWMnPaK == qqXBTWgnZf){ZUuXlHSqoO = true;}
      if(CRIUhMTcYY == zGyjwgKkZF){BIEolUabhE = true;}
      else if(zGyjwgKkZF == CRIUhMTcYY){CDcEjckxwR = true;}
      if(yAcJVKMCki == dQrJMtVfjg){zRTpdfjZIb = true;}
      else if(dQrJMtVfjg == yAcJVKMCki){DYafRFcNss = true;}
      if(UTtsaqPODY == bWwFpdobtE){dAESbfPAMW = true;}
      else if(bWwFpdobtE == UTtsaqPODY){CKRlXEfXek = true;}
      if(KlKVtayihT == SoeLjWDzyh){VFYgCeGIdq = true;}
      if(RNOnWpNOeI == VysFfmpdec){iiDXHupPCJ = true;}
      if(KdCqLiWPtp == qIesicJssR){EgOpMAElMG = true;}
      while(SoeLjWDzyh == KlKVtayihT){bFqwdkWrSo = true;}
      while(VysFfmpdec == VysFfmpdec){DslCxBsOFg = true;}
      while(qIesicJssR == qIesicJssR){dFyuLqkpfe = true;}
      if(qhqVlolgZo == true){qhqVlolgZo = false;}
      if(pVgCKddqYD == true){pVgCKddqYD = false;}
      if(nKxQMKKkcH == true){nKxQMKKkcH = false;}
      if(NKFgpnHXSq == true){NKFgpnHXSq = false;}
      if(BIEolUabhE == true){BIEolUabhE = false;}
      if(zRTpdfjZIb == true){zRTpdfjZIb = false;}
      if(dAESbfPAMW == true){dAESbfPAMW = false;}
      if(VFYgCeGIdq == true){VFYgCeGIdq = false;}
      if(iiDXHupPCJ == true){iiDXHupPCJ = false;}
      if(EgOpMAElMG == true){EgOpMAElMG = false;}
      if(FaPLisslmy == true){FaPLisslmy = false;}
      if(ZauQsuxfKf == true){ZauQsuxfKf = false;}
      if(ozxCSoqiTB == true){ozxCSoqiTB = false;}
      if(ZUuXlHSqoO == true){ZUuXlHSqoO = false;}
      if(CDcEjckxwR == true){CDcEjckxwR = false;}
      if(DYafRFcNss == true){DYafRFcNss = false;}
      if(CKRlXEfXek == true){CKRlXEfXek = false;}
      if(bFqwdkWrSo == true){bFqwdkWrSo = false;}
      if(DslCxBsOFg == true){DslCxBsOFg = false;}
      if(dFyuLqkpfe == true){dFyuLqkpfe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABQGEEMSYN
{ 
  void YKiASYSWwQ()
  { 
      bool raYqNBcesK = false;
      bool TmuNugsDuJ = false;
      bool KEOCzmBkAH = false;
      bool fYZfQIFbrM = false;
      bool FkbYkwhBpA = false;
      bool EXhPznLVqa = false;
      bool AqdldtNOwl = false;
      bool bRLhEYbpRD = false;
      bool FztzCHqJgc = false;
      bool wikQMNGptp = false;
      bool hSEEYmMALZ = false;
      bool LVEmVAxdjV = false;
      bool DDhTorftUp = false;
      bool SlubUlupaO = false;
      bool uqxHRaeyuM = false;
      bool QbFXmekkOf = false;
      bool HReVGYabRi = false;
      bool EHCUaLFZCO = false;
      bool NhyHYpfWop = false;
      bool AKauHdLbAr = false;
      string YPXpVAObLa;
      string yjBSjdOhGH;
      string FDiGSpwZgQ;
      string tVRpHtrmKM;
      string HikxpePWoZ;
      string zcnoxUgRWe;
      string DnutgbRKLo;
      string kaXszWSkQn;
      string ZYkGRQgbsl;
      string NaPeITnpPN;
      string MEKzoXFuoa;
      string CuBiEeCncQ;
      string toRZbJLsjf;
      string hcUCbVOlRt;
      string KlmSiSZgZd;
      string RzMzSWlkWe;
      string LMKJrZZyHi;
      string PPWhFICzpJ;
      string jeSGOhPViE;
      string icOlhybcZJ;
      if(YPXpVAObLa == MEKzoXFuoa){raYqNBcesK = true;}
      else if(MEKzoXFuoa == YPXpVAObLa){hSEEYmMALZ = true;}
      if(yjBSjdOhGH == CuBiEeCncQ){TmuNugsDuJ = true;}
      else if(CuBiEeCncQ == yjBSjdOhGH){LVEmVAxdjV = true;}
      if(FDiGSpwZgQ == toRZbJLsjf){KEOCzmBkAH = true;}
      else if(toRZbJLsjf == FDiGSpwZgQ){DDhTorftUp = true;}
      if(tVRpHtrmKM == hcUCbVOlRt){fYZfQIFbrM = true;}
      else if(hcUCbVOlRt == tVRpHtrmKM){SlubUlupaO = true;}
      if(HikxpePWoZ == KlmSiSZgZd){FkbYkwhBpA = true;}
      else if(KlmSiSZgZd == HikxpePWoZ){uqxHRaeyuM = true;}
      if(zcnoxUgRWe == RzMzSWlkWe){EXhPznLVqa = true;}
      else if(RzMzSWlkWe == zcnoxUgRWe){QbFXmekkOf = true;}
      if(DnutgbRKLo == LMKJrZZyHi){AqdldtNOwl = true;}
      else if(LMKJrZZyHi == DnutgbRKLo){HReVGYabRi = true;}
      if(kaXszWSkQn == PPWhFICzpJ){bRLhEYbpRD = true;}
      if(ZYkGRQgbsl == jeSGOhPViE){FztzCHqJgc = true;}
      if(NaPeITnpPN == icOlhybcZJ){wikQMNGptp = true;}
      while(PPWhFICzpJ == kaXszWSkQn){EHCUaLFZCO = true;}
      while(jeSGOhPViE == jeSGOhPViE){NhyHYpfWop = true;}
      while(icOlhybcZJ == icOlhybcZJ){AKauHdLbAr = true;}
      if(raYqNBcesK == true){raYqNBcesK = false;}
      if(TmuNugsDuJ == true){TmuNugsDuJ = false;}
      if(KEOCzmBkAH == true){KEOCzmBkAH = false;}
      if(fYZfQIFbrM == true){fYZfQIFbrM = false;}
      if(FkbYkwhBpA == true){FkbYkwhBpA = false;}
      if(EXhPznLVqa == true){EXhPznLVqa = false;}
      if(AqdldtNOwl == true){AqdldtNOwl = false;}
      if(bRLhEYbpRD == true){bRLhEYbpRD = false;}
      if(FztzCHqJgc == true){FztzCHqJgc = false;}
      if(wikQMNGptp == true){wikQMNGptp = false;}
      if(hSEEYmMALZ == true){hSEEYmMALZ = false;}
      if(LVEmVAxdjV == true){LVEmVAxdjV = false;}
      if(DDhTorftUp == true){DDhTorftUp = false;}
      if(SlubUlupaO == true){SlubUlupaO = false;}
      if(uqxHRaeyuM == true){uqxHRaeyuM = false;}
      if(QbFXmekkOf == true){QbFXmekkOf = false;}
      if(HReVGYabRi == true){HReVGYabRi = false;}
      if(EHCUaLFZCO == true){EHCUaLFZCO = false;}
      if(NhyHYpfWop == true){NhyHYpfWop = false;}
      if(AKauHdLbAr == true){AKauHdLbAr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUTWEHNOMI
{ 
  void QhSweyYiNg()
  { 
      bool MAJzyUUQrl = false;
      bool NYaUUAxZdZ = false;
      bool HtrgbxqLfc = false;
      bool mGBLEybeOu = false;
      bool hCHLCsSlMx = false;
      bool VpEbtSIbXB = false;
      bool cIjPzHWPPV = false;
      bool YRLirFmgdh = false;
      bool dFziGxCZQl = false;
      bool pAGNRYSrLu = false;
      bool WDVpYEeUjo = false;
      bool eaxpWWJAIC = false;
      bool FxydeYLxQS = false;
      bool muUiLZjIKC = false;
      bool SgobGPDQpu = false;
      bool PRiJoYEqLA = false;
      bool rgEQCjGNdw = false;
      bool lApGjYHWXP = false;
      bool UtHVDULLtl = false;
      bool VsxKJkbXYV = false;
      string fCCdVIbwuw;
      string GrsxREzndu;
      string jPtkYYOgoP;
      string HEXmjzoefK;
      string DNpWymSudb;
      string zJKTPPHREw;
      string stGeoBTGMR;
      string PTITqWZWll;
      string GSDNPxtEXT;
      string rXaiQIGKhx;
      string SLhLLeBpbr;
      string pjfSoapsPr;
      string HPirZqsYCh;
      string POonTujrBj;
      string uDbedHrHto;
      string SMuopCcolT;
      string lbmscatqyt;
      string qyrewDnDOR;
      string zkeNPCSAyQ;
      string StGgyTPhCC;
      if(fCCdVIbwuw == SLhLLeBpbr){MAJzyUUQrl = true;}
      else if(SLhLLeBpbr == fCCdVIbwuw){WDVpYEeUjo = true;}
      if(GrsxREzndu == pjfSoapsPr){NYaUUAxZdZ = true;}
      else if(pjfSoapsPr == GrsxREzndu){eaxpWWJAIC = true;}
      if(jPtkYYOgoP == HPirZqsYCh){HtrgbxqLfc = true;}
      else if(HPirZqsYCh == jPtkYYOgoP){FxydeYLxQS = true;}
      if(HEXmjzoefK == POonTujrBj){mGBLEybeOu = true;}
      else if(POonTujrBj == HEXmjzoefK){muUiLZjIKC = true;}
      if(DNpWymSudb == uDbedHrHto){hCHLCsSlMx = true;}
      else if(uDbedHrHto == DNpWymSudb){SgobGPDQpu = true;}
      if(zJKTPPHREw == SMuopCcolT){VpEbtSIbXB = true;}
      else if(SMuopCcolT == zJKTPPHREw){PRiJoYEqLA = true;}
      if(stGeoBTGMR == lbmscatqyt){cIjPzHWPPV = true;}
      else if(lbmscatqyt == stGeoBTGMR){rgEQCjGNdw = true;}
      if(PTITqWZWll == qyrewDnDOR){YRLirFmgdh = true;}
      if(GSDNPxtEXT == zkeNPCSAyQ){dFziGxCZQl = true;}
      if(rXaiQIGKhx == StGgyTPhCC){pAGNRYSrLu = true;}
      while(qyrewDnDOR == PTITqWZWll){lApGjYHWXP = true;}
      while(zkeNPCSAyQ == zkeNPCSAyQ){UtHVDULLtl = true;}
      while(StGgyTPhCC == StGgyTPhCC){VsxKJkbXYV = true;}
      if(MAJzyUUQrl == true){MAJzyUUQrl = false;}
      if(NYaUUAxZdZ == true){NYaUUAxZdZ = false;}
      if(HtrgbxqLfc == true){HtrgbxqLfc = false;}
      if(mGBLEybeOu == true){mGBLEybeOu = false;}
      if(hCHLCsSlMx == true){hCHLCsSlMx = false;}
      if(VpEbtSIbXB == true){VpEbtSIbXB = false;}
      if(cIjPzHWPPV == true){cIjPzHWPPV = false;}
      if(YRLirFmgdh == true){YRLirFmgdh = false;}
      if(dFziGxCZQl == true){dFziGxCZQl = false;}
      if(pAGNRYSrLu == true){pAGNRYSrLu = false;}
      if(WDVpYEeUjo == true){WDVpYEeUjo = false;}
      if(eaxpWWJAIC == true){eaxpWWJAIC = false;}
      if(FxydeYLxQS == true){FxydeYLxQS = false;}
      if(muUiLZjIKC == true){muUiLZjIKC = false;}
      if(SgobGPDQpu == true){SgobGPDQpu = false;}
      if(PRiJoYEqLA == true){PRiJoYEqLA = false;}
      if(rgEQCjGNdw == true){rgEQCjGNdw = false;}
      if(lApGjYHWXP == true){lApGjYHWXP = false;}
      if(UtHVDULLtl == true){UtHVDULLtl = false;}
      if(VsxKJkbXYV == true){VsxKJkbXYV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEUQTLUEDM
{ 
  void ZbuGgzREPe()
  { 
      bool nGoZficYzH = false;
      bool szIhKCBzCh = false;
      bool MMInKGBSXm = false;
      bool HahVHOTlxb = false;
      bool FjmEKMmfoz = false;
      bool sEJpkaxAPY = false;
      bool gJALASRlZw = false;
      bool hOBacbYEdx = false;
      bool TVdYtCRrkf = false;
      bool QSWYtujbEr = false;
      bool uBFrQeDhNI = false;
      bool CrWRFLebRx = false;
      bool AZAtePrcfg = false;
      bool rxAkCSPlIO = false;
      bool yidcdXuESi = false;
      bool QIKGqVALNA = false;
      bool maCfPEqlPl = false;
      bool wsSCyRuXPG = false;
      bool TmJxQjlttg = false;
      bool SEXHbXgxMY = false;
      string tEHuFAbJJY;
      string uFbDNmPsqo;
      string UZpQnwmNFL;
      string BgqzSVQQwV;
      string WxhxaIcAGy;
      string zUKqQUNpHI;
      string MOEyXONckr;
      string WyxUSWqspe;
      string SmGGMfVzhx;
      string HaJmIHsjYL;
      string tAPObAXoYt;
      string dTzbpZIxkq;
      string rNtmjwoJMK;
      string dHUejSXreL;
      string IganTnagxh;
      string zuyhSfFbde;
      string KNcOPVzUrW;
      string CPSZiLmGTw;
      string UIMdLhJlLD;
      string MuNzBuDMXx;
      if(tEHuFAbJJY == tAPObAXoYt){nGoZficYzH = true;}
      else if(tAPObAXoYt == tEHuFAbJJY){uBFrQeDhNI = true;}
      if(uFbDNmPsqo == dTzbpZIxkq){szIhKCBzCh = true;}
      else if(dTzbpZIxkq == uFbDNmPsqo){CrWRFLebRx = true;}
      if(UZpQnwmNFL == rNtmjwoJMK){MMInKGBSXm = true;}
      else if(rNtmjwoJMK == UZpQnwmNFL){AZAtePrcfg = true;}
      if(BgqzSVQQwV == dHUejSXreL){HahVHOTlxb = true;}
      else if(dHUejSXreL == BgqzSVQQwV){rxAkCSPlIO = true;}
      if(WxhxaIcAGy == IganTnagxh){FjmEKMmfoz = true;}
      else if(IganTnagxh == WxhxaIcAGy){yidcdXuESi = true;}
      if(zUKqQUNpHI == zuyhSfFbde){sEJpkaxAPY = true;}
      else if(zuyhSfFbde == zUKqQUNpHI){QIKGqVALNA = true;}
      if(MOEyXONckr == KNcOPVzUrW){gJALASRlZw = true;}
      else if(KNcOPVzUrW == MOEyXONckr){maCfPEqlPl = true;}
      if(WyxUSWqspe == CPSZiLmGTw){hOBacbYEdx = true;}
      if(SmGGMfVzhx == UIMdLhJlLD){TVdYtCRrkf = true;}
      if(HaJmIHsjYL == MuNzBuDMXx){QSWYtujbEr = true;}
      while(CPSZiLmGTw == WyxUSWqspe){wsSCyRuXPG = true;}
      while(UIMdLhJlLD == UIMdLhJlLD){TmJxQjlttg = true;}
      while(MuNzBuDMXx == MuNzBuDMXx){SEXHbXgxMY = true;}
      if(nGoZficYzH == true){nGoZficYzH = false;}
      if(szIhKCBzCh == true){szIhKCBzCh = false;}
      if(MMInKGBSXm == true){MMInKGBSXm = false;}
      if(HahVHOTlxb == true){HahVHOTlxb = false;}
      if(FjmEKMmfoz == true){FjmEKMmfoz = false;}
      if(sEJpkaxAPY == true){sEJpkaxAPY = false;}
      if(gJALASRlZw == true){gJALASRlZw = false;}
      if(hOBacbYEdx == true){hOBacbYEdx = false;}
      if(TVdYtCRrkf == true){TVdYtCRrkf = false;}
      if(QSWYtujbEr == true){QSWYtujbEr = false;}
      if(uBFrQeDhNI == true){uBFrQeDhNI = false;}
      if(CrWRFLebRx == true){CrWRFLebRx = false;}
      if(AZAtePrcfg == true){AZAtePrcfg = false;}
      if(rxAkCSPlIO == true){rxAkCSPlIO = false;}
      if(yidcdXuESi == true){yidcdXuESi = false;}
      if(QIKGqVALNA == true){QIKGqVALNA = false;}
      if(maCfPEqlPl == true){maCfPEqlPl = false;}
      if(wsSCyRuXPG == true){wsSCyRuXPG = false;}
      if(TmJxQjlttg == true){TmJxQjlttg = false;}
      if(SEXHbXgxMY == true){SEXHbXgxMY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDKZOGGZJK
{ 
  void xRZUbfiQaN()
  { 
      bool mjJXOqaZGp = false;
      bool XoZPiEFRyF = false;
      bool SsXHgrtDyO = false;
      bool bsngFbTCye = false;
      bool kcDVOaBaGq = false;
      bool roAPwtLCqW = false;
      bool xWbrNeBsKH = false;
      bool kCTSTopBrF = false;
      bool pSxGVlrXjL = false;
      bool PRKbhOBLHj = false;
      bool ZIQzGoVhuH = false;
      bool DKJkfdYUVb = false;
      bool lcJzrSqqkF = false;
      bool mdtIfhCxAf = false;
      bool PKcbHEHZwE = false;
      bool ogoexxzRHm = false;
      bool xewpTZQBFx = false;
      bool abToMbAgqm = false;
      bool KRufPGoOLi = false;
      bool ikoNhkNlIh = false;
      string kOLwAwUkMI;
      string ZUrEBFTbXx;
      string ObtLOhYsyt;
      string LoSMormizY;
      string mjLHffZTBp;
      string zEZdbJTAgS;
      string WblSxjBfOI;
      string RjbyKdPmfh;
      string HEqItGOnjf;
      string XmCfBLyrJu;
      string dsFrYPbbTx;
      string sgTyKSjdYp;
      string VNuijdgwwy;
      string fXckENyzjd;
      string dmUllqSDUi;
      string bTTSYQyWIt;
      string hfeURVDitw;
      string TjstMirIws;
      string LcaNWLDJLm;
      string PbpowyHzUP;
      if(kOLwAwUkMI == dsFrYPbbTx){mjJXOqaZGp = true;}
      else if(dsFrYPbbTx == kOLwAwUkMI){ZIQzGoVhuH = true;}
      if(ZUrEBFTbXx == sgTyKSjdYp){XoZPiEFRyF = true;}
      else if(sgTyKSjdYp == ZUrEBFTbXx){DKJkfdYUVb = true;}
      if(ObtLOhYsyt == VNuijdgwwy){SsXHgrtDyO = true;}
      else if(VNuijdgwwy == ObtLOhYsyt){lcJzrSqqkF = true;}
      if(LoSMormizY == fXckENyzjd){bsngFbTCye = true;}
      else if(fXckENyzjd == LoSMormizY){mdtIfhCxAf = true;}
      if(mjLHffZTBp == dmUllqSDUi){kcDVOaBaGq = true;}
      else if(dmUllqSDUi == mjLHffZTBp){PKcbHEHZwE = true;}
      if(zEZdbJTAgS == bTTSYQyWIt){roAPwtLCqW = true;}
      else if(bTTSYQyWIt == zEZdbJTAgS){ogoexxzRHm = true;}
      if(WblSxjBfOI == hfeURVDitw){xWbrNeBsKH = true;}
      else if(hfeURVDitw == WblSxjBfOI){xewpTZQBFx = true;}
      if(RjbyKdPmfh == TjstMirIws){kCTSTopBrF = true;}
      if(HEqItGOnjf == LcaNWLDJLm){pSxGVlrXjL = true;}
      if(XmCfBLyrJu == PbpowyHzUP){PRKbhOBLHj = true;}
      while(TjstMirIws == RjbyKdPmfh){abToMbAgqm = true;}
      while(LcaNWLDJLm == LcaNWLDJLm){KRufPGoOLi = true;}
      while(PbpowyHzUP == PbpowyHzUP){ikoNhkNlIh = true;}
      if(mjJXOqaZGp == true){mjJXOqaZGp = false;}
      if(XoZPiEFRyF == true){XoZPiEFRyF = false;}
      if(SsXHgrtDyO == true){SsXHgrtDyO = false;}
      if(bsngFbTCye == true){bsngFbTCye = false;}
      if(kcDVOaBaGq == true){kcDVOaBaGq = false;}
      if(roAPwtLCqW == true){roAPwtLCqW = false;}
      if(xWbrNeBsKH == true){xWbrNeBsKH = false;}
      if(kCTSTopBrF == true){kCTSTopBrF = false;}
      if(pSxGVlrXjL == true){pSxGVlrXjL = false;}
      if(PRKbhOBLHj == true){PRKbhOBLHj = false;}
      if(ZIQzGoVhuH == true){ZIQzGoVhuH = false;}
      if(DKJkfdYUVb == true){DKJkfdYUVb = false;}
      if(lcJzrSqqkF == true){lcJzrSqqkF = false;}
      if(mdtIfhCxAf == true){mdtIfhCxAf = false;}
      if(PKcbHEHZwE == true){PKcbHEHZwE = false;}
      if(ogoexxzRHm == true){ogoexxzRHm = false;}
      if(xewpTZQBFx == true){xewpTZQBFx = false;}
      if(abToMbAgqm == true){abToMbAgqm = false;}
      if(KRufPGoOLi == true){KRufPGoOLi = false;}
      if(ikoNhkNlIh == true){ikoNhkNlIh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FYKFFYEOIE
{ 
  void IjYBadAHQq()
  { 
      bool cnzHIDcpFH = false;
      bool ZnFxdKExTE = false;
      bool jPoNilXJlz = false;
      bool cRxrKEbxoo = false;
      bool btTXeYiLsF = false;
      bool uogcHMzkYW = false;
      bool eSDFeHqMmY = false;
      bool hHIdcowQiJ = false;
      bool CLPgEmjUjx = false;
      bool EpXSKIqOsW = false;
      bool hWYUWmgDAS = false;
      bool QhCOTTDVBq = false;
      bool WWbpUrioTT = false;
      bool ygXLbfmuKQ = false;
      bool FfTRfVnIyq = false;
      bool EUMBzLthze = false;
      bool EqjfUiKpmn = false;
      bool fILjkpCKJy = false;
      bool DZpbPcUVMP = false;
      bool kEueMOwnxw = false;
      string iBNWgSiQiX;
      string iXMlnLCRdS;
      string bKqOhkBUXu;
      string lSlfgwdXbG;
      string bdjznKSniF;
      string LIDhUXKynu;
      string ROsmlPkfEr;
      string gdoXqyZqaX;
      string SMlRicPELJ;
      string lfifnNjwNX;
      string ZljqXgSfpV;
      string xSWQbEbaEI;
      string AgTuGBuIid;
      string NcdCxfcttB;
      string JjNoLSISEj;
      string kJrEXsSnkW;
      string lJwMIUoTSw;
      string aggCzPSdim;
      string rbEysEkYeE;
      string NnJXPzmBgq;
      if(iBNWgSiQiX == ZljqXgSfpV){cnzHIDcpFH = true;}
      else if(ZljqXgSfpV == iBNWgSiQiX){hWYUWmgDAS = true;}
      if(iXMlnLCRdS == xSWQbEbaEI){ZnFxdKExTE = true;}
      else if(xSWQbEbaEI == iXMlnLCRdS){QhCOTTDVBq = true;}
      if(bKqOhkBUXu == AgTuGBuIid){jPoNilXJlz = true;}
      else if(AgTuGBuIid == bKqOhkBUXu){WWbpUrioTT = true;}
      if(lSlfgwdXbG == NcdCxfcttB){cRxrKEbxoo = true;}
      else if(NcdCxfcttB == lSlfgwdXbG){ygXLbfmuKQ = true;}
      if(bdjznKSniF == JjNoLSISEj){btTXeYiLsF = true;}
      else if(JjNoLSISEj == bdjznKSniF){FfTRfVnIyq = true;}
      if(LIDhUXKynu == kJrEXsSnkW){uogcHMzkYW = true;}
      else if(kJrEXsSnkW == LIDhUXKynu){EUMBzLthze = true;}
      if(ROsmlPkfEr == lJwMIUoTSw){eSDFeHqMmY = true;}
      else if(lJwMIUoTSw == ROsmlPkfEr){EqjfUiKpmn = true;}
      if(gdoXqyZqaX == aggCzPSdim){hHIdcowQiJ = true;}
      if(SMlRicPELJ == rbEysEkYeE){CLPgEmjUjx = true;}
      if(lfifnNjwNX == NnJXPzmBgq){EpXSKIqOsW = true;}
      while(aggCzPSdim == gdoXqyZqaX){fILjkpCKJy = true;}
      while(rbEysEkYeE == rbEysEkYeE){DZpbPcUVMP = true;}
      while(NnJXPzmBgq == NnJXPzmBgq){kEueMOwnxw = true;}
      if(cnzHIDcpFH == true){cnzHIDcpFH = false;}
      if(ZnFxdKExTE == true){ZnFxdKExTE = false;}
      if(jPoNilXJlz == true){jPoNilXJlz = false;}
      if(cRxrKEbxoo == true){cRxrKEbxoo = false;}
      if(btTXeYiLsF == true){btTXeYiLsF = false;}
      if(uogcHMzkYW == true){uogcHMzkYW = false;}
      if(eSDFeHqMmY == true){eSDFeHqMmY = false;}
      if(hHIdcowQiJ == true){hHIdcowQiJ = false;}
      if(CLPgEmjUjx == true){CLPgEmjUjx = false;}
      if(EpXSKIqOsW == true){EpXSKIqOsW = false;}
      if(hWYUWmgDAS == true){hWYUWmgDAS = false;}
      if(QhCOTTDVBq == true){QhCOTTDVBq = false;}
      if(WWbpUrioTT == true){WWbpUrioTT = false;}
      if(ygXLbfmuKQ == true){ygXLbfmuKQ = false;}
      if(FfTRfVnIyq == true){FfTRfVnIyq = false;}
      if(EUMBzLthze == true){EUMBzLthze = false;}
      if(EqjfUiKpmn == true){EqjfUiKpmn = false;}
      if(fILjkpCKJy == true){fILjkpCKJy = false;}
      if(DZpbPcUVMP == true){DZpbPcUVMP = false;}
      if(kEueMOwnxw == true){kEueMOwnxw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDPUERGXZG
{ 
  void qJNhMyFXbS()
  { 
      bool KMLCayVstl = false;
      bool ylUETyJoeD = false;
      bool RMWjxrhRRe = false;
      bool chYFllcysH = false;
      bool USVIpplEPA = false;
      bool upzeAxpaEi = false;
      bool PDaPJQNOSg = false;
      bool UKwWizqNtH = false;
      bool GcCRjlhtFo = false;
      bool wBsKrRqFzZ = false;
      bool cWliejtcuA = false;
      bool FbgxbmAIeW = false;
      bool iSIdjTQkeR = false;
      bool HkOUeiqTmz = false;
      bool rEzEiUUwhF = false;
      bool QhacpJNIyL = false;
      bool SIycrUNMRr = false;
      bool ugVfddSEuP = false;
      bool zUCZBZKldU = false;
      bool VhUbgjGVLN = false;
      string frJDCxXQBA;
      string OlArrrHfDg;
      string UxATsCmYMz;
      string xUQfcAbVai;
      string rfOelHzacN;
      string zsZUwhqoKA;
      string KyECCsVTOr;
      string PkEToohVhk;
      string CLuzzEuuju;
      string IlKaYsbMbr;
      string keMjxNoFfH;
      string zVHYxyDECy;
      string yajTidaduu;
      string NVsozWzKCl;
      string OpOcumekcZ;
      string pWJdtKtrBS;
      string mKKjtccRZZ;
      string zrBQiILHXw;
      string zoBUFpLPuo;
      string cGJiyEedhR;
      if(frJDCxXQBA == keMjxNoFfH){KMLCayVstl = true;}
      else if(keMjxNoFfH == frJDCxXQBA){cWliejtcuA = true;}
      if(OlArrrHfDg == zVHYxyDECy){ylUETyJoeD = true;}
      else if(zVHYxyDECy == OlArrrHfDg){FbgxbmAIeW = true;}
      if(UxATsCmYMz == yajTidaduu){RMWjxrhRRe = true;}
      else if(yajTidaduu == UxATsCmYMz){iSIdjTQkeR = true;}
      if(xUQfcAbVai == NVsozWzKCl){chYFllcysH = true;}
      else if(NVsozWzKCl == xUQfcAbVai){HkOUeiqTmz = true;}
      if(rfOelHzacN == OpOcumekcZ){USVIpplEPA = true;}
      else if(OpOcumekcZ == rfOelHzacN){rEzEiUUwhF = true;}
      if(zsZUwhqoKA == pWJdtKtrBS){upzeAxpaEi = true;}
      else if(pWJdtKtrBS == zsZUwhqoKA){QhacpJNIyL = true;}
      if(KyECCsVTOr == mKKjtccRZZ){PDaPJQNOSg = true;}
      else if(mKKjtccRZZ == KyECCsVTOr){SIycrUNMRr = true;}
      if(PkEToohVhk == zrBQiILHXw){UKwWizqNtH = true;}
      if(CLuzzEuuju == zoBUFpLPuo){GcCRjlhtFo = true;}
      if(IlKaYsbMbr == cGJiyEedhR){wBsKrRqFzZ = true;}
      while(zrBQiILHXw == PkEToohVhk){ugVfddSEuP = true;}
      while(zoBUFpLPuo == zoBUFpLPuo){zUCZBZKldU = true;}
      while(cGJiyEedhR == cGJiyEedhR){VhUbgjGVLN = true;}
      if(KMLCayVstl == true){KMLCayVstl = false;}
      if(ylUETyJoeD == true){ylUETyJoeD = false;}
      if(RMWjxrhRRe == true){RMWjxrhRRe = false;}
      if(chYFllcysH == true){chYFllcysH = false;}
      if(USVIpplEPA == true){USVIpplEPA = false;}
      if(upzeAxpaEi == true){upzeAxpaEi = false;}
      if(PDaPJQNOSg == true){PDaPJQNOSg = false;}
      if(UKwWizqNtH == true){UKwWizqNtH = false;}
      if(GcCRjlhtFo == true){GcCRjlhtFo = false;}
      if(wBsKrRqFzZ == true){wBsKrRqFzZ = false;}
      if(cWliejtcuA == true){cWliejtcuA = false;}
      if(FbgxbmAIeW == true){FbgxbmAIeW = false;}
      if(iSIdjTQkeR == true){iSIdjTQkeR = false;}
      if(HkOUeiqTmz == true){HkOUeiqTmz = false;}
      if(rEzEiUUwhF == true){rEzEiUUwhF = false;}
      if(QhacpJNIyL == true){QhacpJNIyL = false;}
      if(SIycrUNMRr == true){SIycrUNMRr = false;}
      if(ugVfddSEuP == true){ugVfddSEuP = false;}
      if(zUCZBZKldU == true){zUCZBZKldU = false;}
      if(VhUbgjGVLN == true){VhUbgjGVLN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUVEWBSEWT
{ 
  void DCDKFAQRdM()
  { 
      bool AiAVTQULOK = false;
      bool mJPMkUffWo = false;
      bool mrgFRchJWy = false;
      bool ksbzhYaQZY = false;
      bool nidsDLWOyj = false;
      bool HWCxsHCuEq = false;
      bool hKoQYthQeM = false;
      bool sOGxBDOmCF = false;
      bool FSLlpNpdGZ = false;
      bool VfMhpctMTI = false;
      bool cGjlprQFwo = false;
      bool sPrzlPzCaL = false;
      bool DEKFpMCXHX = false;
      bool JBSsbyiYux = false;
      bool wkhQfFnMua = false;
      bool dqlIFYudud = false;
      bool psyXerwzWm = false;
      bool gZGcPRVsZk = false;
      bool YobftRPKnC = false;
      bool CEdRHDmKln = false;
      string bIjnHMFWIh;
      string yjsTTtHhUB;
      string LNqflDolCI;
      string VzQjtiKruG;
      string bEPEOdiPzE;
      string kBRCcOREBD;
      string XTTALySIZj;
      string iPmNYHxlRI;
      string UYlyWUgOHe;
      string QGpqiIjPrP;
      string KZpOUVOEcV;
      string QelshyhVcq;
      string QEAtTbYudQ;
      string WhtCxuiWcB;
      string FcllOkTwIj;
      string aNmAyGYuus;
      string wSZMyhkjwm;
      string PKsaknSOeh;
      string HbltoIusDp;
      string VmbiEmDYmf;
      if(bIjnHMFWIh == KZpOUVOEcV){AiAVTQULOK = true;}
      else if(KZpOUVOEcV == bIjnHMFWIh){cGjlprQFwo = true;}
      if(yjsTTtHhUB == QelshyhVcq){mJPMkUffWo = true;}
      else if(QelshyhVcq == yjsTTtHhUB){sPrzlPzCaL = true;}
      if(LNqflDolCI == QEAtTbYudQ){mrgFRchJWy = true;}
      else if(QEAtTbYudQ == LNqflDolCI){DEKFpMCXHX = true;}
      if(VzQjtiKruG == WhtCxuiWcB){ksbzhYaQZY = true;}
      else if(WhtCxuiWcB == VzQjtiKruG){JBSsbyiYux = true;}
      if(bEPEOdiPzE == FcllOkTwIj){nidsDLWOyj = true;}
      else if(FcllOkTwIj == bEPEOdiPzE){wkhQfFnMua = true;}
      if(kBRCcOREBD == aNmAyGYuus){HWCxsHCuEq = true;}
      else if(aNmAyGYuus == kBRCcOREBD){dqlIFYudud = true;}
      if(XTTALySIZj == wSZMyhkjwm){hKoQYthQeM = true;}
      else if(wSZMyhkjwm == XTTALySIZj){psyXerwzWm = true;}
      if(iPmNYHxlRI == PKsaknSOeh){sOGxBDOmCF = true;}
      if(UYlyWUgOHe == HbltoIusDp){FSLlpNpdGZ = true;}
      if(QGpqiIjPrP == VmbiEmDYmf){VfMhpctMTI = true;}
      while(PKsaknSOeh == iPmNYHxlRI){gZGcPRVsZk = true;}
      while(HbltoIusDp == HbltoIusDp){YobftRPKnC = true;}
      while(VmbiEmDYmf == VmbiEmDYmf){CEdRHDmKln = true;}
      if(AiAVTQULOK == true){AiAVTQULOK = false;}
      if(mJPMkUffWo == true){mJPMkUffWo = false;}
      if(mrgFRchJWy == true){mrgFRchJWy = false;}
      if(ksbzhYaQZY == true){ksbzhYaQZY = false;}
      if(nidsDLWOyj == true){nidsDLWOyj = false;}
      if(HWCxsHCuEq == true){HWCxsHCuEq = false;}
      if(hKoQYthQeM == true){hKoQYthQeM = false;}
      if(sOGxBDOmCF == true){sOGxBDOmCF = false;}
      if(FSLlpNpdGZ == true){FSLlpNpdGZ = false;}
      if(VfMhpctMTI == true){VfMhpctMTI = false;}
      if(cGjlprQFwo == true){cGjlprQFwo = false;}
      if(sPrzlPzCaL == true){sPrzlPzCaL = false;}
      if(DEKFpMCXHX == true){DEKFpMCXHX = false;}
      if(JBSsbyiYux == true){JBSsbyiYux = false;}
      if(wkhQfFnMua == true){wkhQfFnMua = false;}
      if(dqlIFYudud == true){dqlIFYudud = false;}
      if(psyXerwzWm == true){psyXerwzWm = false;}
      if(gZGcPRVsZk == true){gZGcPRVsZk = false;}
      if(YobftRPKnC == true){YobftRPKnC = false;}
      if(CEdRHDmKln == true){CEdRHDmKln = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIMDDHKLGC
{ 
  void TABKxlCaNd()
  { 
      bool ciOGjiqgKF = false;
      bool PeLyDldtxM = false;
      bool IHtjLPmSsT = false;
      bool JCHzgrCyOu = false;
      bool yHCJdyBhhK = false;
      bool yRYMcUneuU = false;
      bool wXmpuMWMRK = false;
      bool jefBNBFkGM = false;
      bool NFkiUrdtVL = false;
      bool DWDtzaTLNQ = false;
      bool bnPWZSlWzb = false;
      bool PCYhGpmEUD = false;
      bool ibpFGNblCm = false;
      bool gsWpkZoNJC = false;
      bool FGuswAyVmI = false;
      bool nPpKgAyKQM = false;
      bool qAUMuVfhxg = false;
      bool BZtSxbfxJG = false;
      bool OFysyQCMIk = false;
      bool aexxKEliyZ = false;
      string mlmCyfTKsN;
      string QBiEKBYoZL;
      string FyKqtIPLZn;
      string HbQIkPoLPP;
      string SBUXtyxlJL;
      string ZJPErobwHp;
      string QIjFGojaSt;
      string MMZKrDclww;
      string LdBONxLLQw;
      string nrDYzJRPQF;
      string NVTOyMjFLn;
      string LpALdlGUqJ;
      string cYJVGTJALh;
      string lNUqhoKmQA;
      string MGzbjxrruM;
      string DwXHboMxHe;
      string DjscCyUJcn;
      string bTEpwWYhkJ;
      string aQFzepoNOs;
      string cMfkxcMWZl;
      if(mlmCyfTKsN == NVTOyMjFLn){ciOGjiqgKF = true;}
      else if(NVTOyMjFLn == mlmCyfTKsN){bnPWZSlWzb = true;}
      if(QBiEKBYoZL == LpALdlGUqJ){PeLyDldtxM = true;}
      else if(LpALdlGUqJ == QBiEKBYoZL){PCYhGpmEUD = true;}
      if(FyKqtIPLZn == cYJVGTJALh){IHtjLPmSsT = true;}
      else if(cYJVGTJALh == FyKqtIPLZn){ibpFGNblCm = true;}
      if(HbQIkPoLPP == lNUqhoKmQA){JCHzgrCyOu = true;}
      else if(lNUqhoKmQA == HbQIkPoLPP){gsWpkZoNJC = true;}
      if(SBUXtyxlJL == MGzbjxrruM){yHCJdyBhhK = true;}
      else if(MGzbjxrruM == SBUXtyxlJL){FGuswAyVmI = true;}
      if(ZJPErobwHp == DwXHboMxHe){yRYMcUneuU = true;}
      else if(DwXHboMxHe == ZJPErobwHp){nPpKgAyKQM = true;}
      if(QIjFGojaSt == DjscCyUJcn){wXmpuMWMRK = true;}
      else if(DjscCyUJcn == QIjFGojaSt){qAUMuVfhxg = true;}
      if(MMZKrDclww == bTEpwWYhkJ){jefBNBFkGM = true;}
      if(LdBONxLLQw == aQFzepoNOs){NFkiUrdtVL = true;}
      if(nrDYzJRPQF == cMfkxcMWZl){DWDtzaTLNQ = true;}
      while(bTEpwWYhkJ == MMZKrDclww){BZtSxbfxJG = true;}
      while(aQFzepoNOs == aQFzepoNOs){OFysyQCMIk = true;}
      while(cMfkxcMWZl == cMfkxcMWZl){aexxKEliyZ = true;}
      if(ciOGjiqgKF == true){ciOGjiqgKF = false;}
      if(PeLyDldtxM == true){PeLyDldtxM = false;}
      if(IHtjLPmSsT == true){IHtjLPmSsT = false;}
      if(JCHzgrCyOu == true){JCHzgrCyOu = false;}
      if(yHCJdyBhhK == true){yHCJdyBhhK = false;}
      if(yRYMcUneuU == true){yRYMcUneuU = false;}
      if(wXmpuMWMRK == true){wXmpuMWMRK = false;}
      if(jefBNBFkGM == true){jefBNBFkGM = false;}
      if(NFkiUrdtVL == true){NFkiUrdtVL = false;}
      if(DWDtzaTLNQ == true){DWDtzaTLNQ = false;}
      if(bnPWZSlWzb == true){bnPWZSlWzb = false;}
      if(PCYhGpmEUD == true){PCYhGpmEUD = false;}
      if(ibpFGNblCm == true){ibpFGNblCm = false;}
      if(gsWpkZoNJC == true){gsWpkZoNJC = false;}
      if(FGuswAyVmI == true){FGuswAyVmI = false;}
      if(nPpKgAyKQM == true){nPpKgAyKQM = false;}
      if(qAUMuVfhxg == true){qAUMuVfhxg = false;}
      if(BZtSxbfxJG == true){BZtSxbfxJG = false;}
      if(OFysyQCMIk == true){OFysyQCMIk = false;}
      if(aexxKEliyZ == true){aexxKEliyZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNEMJFFBYU
{ 
  void OkOksliioN()
  { 
      bool FfXCkHNnTh = false;
      bool EkBxTRFudg = false;
      bool GAgmYFWgKH = false;
      bool gWclirNIxB = false;
      bool DWaYgkQBeD = false;
      bool aRjpIFzjce = false;
      bool kgdMAhHOOb = false;
      bool EwycdjYIGm = false;
      bool nVBHfPlmdd = false;
      bool rceRPWsNXz = false;
      bool dCmCyeTHMX = false;
      bool fqdppPeVfk = false;
      bool uUkkibQfMH = false;
      bool pKkGJlizJB = false;
      bool ueaFxByobA = false;
      bool qWhlEIQCSW = false;
      bool NmuFgUGWfD = false;
      bool gfMdoPtfmh = false;
      bool caEMPScyCA = false;
      bool VfflnIjUXb = false;
      string AtWKHHiyxN;
      string TifDhsthtP;
      string wuyDAkIVyg;
      string FYUYmtJKXB;
      string uSoBHsRCMU;
      string ViNsoFuSJW;
      string zNAPHuOHQm;
      string jjJsTdFxwH;
      string SFIcKWKaig;
      string zqABChRYsM;
      string dKkZklYUYL;
      string zyWCDsEXEk;
      string jmXinriIql;
      string LfDicIUiqY;
      string xpBWhATxxJ;
      string ctUIbplCkr;
      string DQcmzSumZu;
      string XUffntlBBn;
      string YkLhIRLuGl;
      string WRyzUfMOXO;
      if(AtWKHHiyxN == dKkZklYUYL){FfXCkHNnTh = true;}
      else if(dKkZklYUYL == AtWKHHiyxN){dCmCyeTHMX = true;}
      if(TifDhsthtP == zyWCDsEXEk){EkBxTRFudg = true;}
      else if(zyWCDsEXEk == TifDhsthtP){fqdppPeVfk = true;}
      if(wuyDAkIVyg == jmXinriIql){GAgmYFWgKH = true;}
      else if(jmXinriIql == wuyDAkIVyg){uUkkibQfMH = true;}
      if(FYUYmtJKXB == LfDicIUiqY){gWclirNIxB = true;}
      else if(LfDicIUiqY == FYUYmtJKXB){pKkGJlizJB = true;}
      if(uSoBHsRCMU == xpBWhATxxJ){DWaYgkQBeD = true;}
      else if(xpBWhATxxJ == uSoBHsRCMU){ueaFxByobA = true;}
      if(ViNsoFuSJW == ctUIbplCkr){aRjpIFzjce = true;}
      else if(ctUIbplCkr == ViNsoFuSJW){qWhlEIQCSW = true;}
      if(zNAPHuOHQm == DQcmzSumZu){kgdMAhHOOb = true;}
      else if(DQcmzSumZu == zNAPHuOHQm){NmuFgUGWfD = true;}
      if(jjJsTdFxwH == XUffntlBBn){EwycdjYIGm = true;}
      if(SFIcKWKaig == YkLhIRLuGl){nVBHfPlmdd = true;}
      if(zqABChRYsM == WRyzUfMOXO){rceRPWsNXz = true;}
      while(XUffntlBBn == jjJsTdFxwH){gfMdoPtfmh = true;}
      while(YkLhIRLuGl == YkLhIRLuGl){caEMPScyCA = true;}
      while(WRyzUfMOXO == WRyzUfMOXO){VfflnIjUXb = true;}
      if(FfXCkHNnTh == true){FfXCkHNnTh = false;}
      if(EkBxTRFudg == true){EkBxTRFudg = false;}
      if(GAgmYFWgKH == true){GAgmYFWgKH = false;}
      if(gWclirNIxB == true){gWclirNIxB = false;}
      if(DWaYgkQBeD == true){DWaYgkQBeD = false;}
      if(aRjpIFzjce == true){aRjpIFzjce = false;}
      if(kgdMAhHOOb == true){kgdMAhHOOb = false;}
      if(EwycdjYIGm == true){EwycdjYIGm = false;}
      if(nVBHfPlmdd == true){nVBHfPlmdd = false;}
      if(rceRPWsNXz == true){rceRPWsNXz = false;}
      if(dCmCyeTHMX == true){dCmCyeTHMX = false;}
      if(fqdppPeVfk == true){fqdppPeVfk = false;}
      if(uUkkibQfMH == true){uUkkibQfMH = false;}
      if(pKkGJlizJB == true){pKkGJlizJB = false;}
      if(ueaFxByobA == true){ueaFxByobA = false;}
      if(qWhlEIQCSW == true){qWhlEIQCSW = false;}
      if(NmuFgUGWfD == true){NmuFgUGWfD = false;}
      if(gfMdoPtfmh == true){gfMdoPtfmh = false;}
      if(caEMPScyCA == true){caEMPScyCA = false;}
      if(VfflnIjUXb == true){VfflnIjUXb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOMPYYPFBO
{ 
  void KcHtOwpXjp()
  { 
      bool JxBktrnSqm = false;
      bool gRDJGMXety = false;
      bool bENntMLegL = false;
      bool bxZmJyPnDR = false;
      bool ZpSeARsOZX = false;
      bool VajHRFjMph = false;
      bool gIlfKjrQAH = false;
      bool xjbbXlkinc = false;
      bool SwEIoBNSVE = false;
      bool OCxUjREmTQ = false;
      bool ZcORalyHie = false;
      bool TAYNPkDcpJ = false;
      bool VYuustlGqG = false;
      bool hyOXCogmgD = false;
      bool DFipjNcjFz = false;
      bool NaxKtAhSYf = false;
      bool zqPcxVlBLZ = false;
      bool DQumGQpELe = false;
      bool QCArsHAEcB = false;
      bool HONBDLpFsO = false;
      string ZHlpufsaeN;
      string WMMWMTcfXa;
      string NkfqTIFiRT;
      string iqXYzXsFOY;
      string YEaaRIgWKD;
      string nDduhnbtWm;
      string aJJKdenmXn;
      string ZWQzCIJEZK;
      string ahXNeeNcqK;
      string wyibxOuPwl;
      string UtzVdQmesZ;
      string eWULLslufz;
      string QLwNranoBm;
      string NsHnpgiCjN;
      string rijRfYdWPE;
      string czjxUIxkcD;
      string cxcFLkOfVe;
      string JjLRGhbehT;
      string wQYxKNIKSg;
      string jxYgktFdFt;
      if(ZHlpufsaeN == UtzVdQmesZ){JxBktrnSqm = true;}
      else if(UtzVdQmesZ == ZHlpufsaeN){ZcORalyHie = true;}
      if(WMMWMTcfXa == eWULLslufz){gRDJGMXety = true;}
      else if(eWULLslufz == WMMWMTcfXa){TAYNPkDcpJ = true;}
      if(NkfqTIFiRT == QLwNranoBm){bENntMLegL = true;}
      else if(QLwNranoBm == NkfqTIFiRT){VYuustlGqG = true;}
      if(iqXYzXsFOY == NsHnpgiCjN){bxZmJyPnDR = true;}
      else if(NsHnpgiCjN == iqXYzXsFOY){hyOXCogmgD = true;}
      if(YEaaRIgWKD == rijRfYdWPE){ZpSeARsOZX = true;}
      else if(rijRfYdWPE == YEaaRIgWKD){DFipjNcjFz = true;}
      if(nDduhnbtWm == czjxUIxkcD){VajHRFjMph = true;}
      else if(czjxUIxkcD == nDduhnbtWm){NaxKtAhSYf = true;}
      if(aJJKdenmXn == cxcFLkOfVe){gIlfKjrQAH = true;}
      else if(cxcFLkOfVe == aJJKdenmXn){zqPcxVlBLZ = true;}
      if(ZWQzCIJEZK == JjLRGhbehT){xjbbXlkinc = true;}
      if(ahXNeeNcqK == wQYxKNIKSg){SwEIoBNSVE = true;}
      if(wyibxOuPwl == jxYgktFdFt){OCxUjREmTQ = true;}
      while(JjLRGhbehT == ZWQzCIJEZK){DQumGQpELe = true;}
      while(wQYxKNIKSg == wQYxKNIKSg){QCArsHAEcB = true;}
      while(jxYgktFdFt == jxYgktFdFt){HONBDLpFsO = true;}
      if(JxBktrnSqm == true){JxBktrnSqm = false;}
      if(gRDJGMXety == true){gRDJGMXety = false;}
      if(bENntMLegL == true){bENntMLegL = false;}
      if(bxZmJyPnDR == true){bxZmJyPnDR = false;}
      if(ZpSeARsOZX == true){ZpSeARsOZX = false;}
      if(VajHRFjMph == true){VajHRFjMph = false;}
      if(gIlfKjrQAH == true){gIlfKjrQAH = false;}
      if(xjbbXlkinc == true){xjbbXlkinc = false;}
      if(SwEIoBNSVE == true){SwEIoBNSVE = false;}
      if(OCxUjREmTQ == true){OCxUjREmTQ = false;}
      if(ZcORalyHie == true){ZcORalyHie = false;}
      if(TAYNPkDcpJ == true){TAYNPkDcpJ = false;}
      if(VYuustlGqG == true){VYuustlGqG = false;}
      if(hyOXCogmgD == true){hyOXCogmgD = false;}
      if(DFipjNcjFz == true){DFipjNcjFz = false;}
      if(NaxKtAhSYf == true){NaxKtAhSYf = false;}
      if(zqPcxVlBLZ == true){zqPcxVlBLZ = false;}
      if(DQumGQpELe == true){DQumGQpELe = false;}
      if(QCArsHAEcB == true){QCArsHAEcB = false;}
      if(HONBDLpFsO == true){HONBDLpFsO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YFWRAYHDVV
{ 
  void VejydDpMrm()
  { 
      bool MuFAXlJBZF = false;
      bool nCNekRkozW = false;
      bool sPyOMDicAx = false;
      bool WbzaGtAaPF = false;
      bool KzUuroRfXZ = false;
      bool gLjRzxxqmU = false;
      bool CgBchMDlXp = false;
      bool RJYsLsuCVW = false;
      bool kDFaPLqgbI = false;
      bool xImtDdyqNf = false;
      bool leIgHXmpGG = false;
      bool CtUPizbaNW = false;
      bool UVKOrIVdph = false;
      bool uDopkGuXSr = false;
      bool XBaVGCnXLD = false;
      bool BXcpKQTsnz = false;
      bool BIzYKyFdec = false;
      bool DEHVyTtoIp = false;
      bool UySmfWazfU = false;
      bool lBiTpPBCKH = false;
      string lgqXDZApAF;
      string jroupdwEGt;
      string UzSzfRZyVA;
      string odOfNgRQeF;
      string llCzmOVWzY;
      string HSZXqlOqqk;
      string ACTAPGcJhJ;
      string LeZBIixTMR;
      string wDyxrWDpna;
      string RaZsEjRCig;
      string lMooMcrYPI;
      string oteZoxDVHs;
      string ClUGqkFfwX;
      string QujfejNJjP;
      string ddaflWuzEH;
      string fwtodzqhya;
      string XLcqqtKztE;
      string itlrOXLnTT;
      string pFanrUAtBf;
      string rfKIrRAjnr;
      if(lgqXDZApAF == lMooMcrYPI){MuFAXlJBZF = true;}
      else if(lMooMcrYPI == lgqXDZApAF){leIgHXmpGG = true;}
      if(jroupdwEGt == oteZoxDVHs){nCNekRkozW = true;}
      else if(oteZoxDVHs == jroupdwEGt){CtUPizbaNW = true;}
      if(UzSzfRZyVA == ClUGqkFfwX){sPyOMDicAx = true;}
      else if(ClUGqkFfwX == UzSzfRZyVA){UVKOrIVdph = true;}
      if(odOfNgRQeF == QujfejNJjP){WbzaGtAaPF = true;}
      else if(QujfejNJjP == odOfNgRQeF){uDopkGuXSr = true;}
      if(llCzmOVWzY == ddaflWuzEH){KzUuroRfXZ = true;}
      else if(ddaflWuzEH == llCzmOVWzY){XBaVGCnXLD = true;}
      if(HSZXqlOqqk == fwtodzqhya){gLjRzxxqmU = true;}
      else if(fwtodzqhya == HSZXqlOqqk){BXcpKQTsnz = true;}
      if(ACTAPGcJhJ == XLcqqtKztE){CgBchMDlXp = true;}
      else if(XLcqqtKztE == ACTAPGcJhJ){BIzYKyFdec = true;}
      if(LeZBIixTMR == itlrOXLnTT){RJYsLsuCVW = true;}
      if(wDyxrWDpna == pFanrUAtBf){kDFaPLqgbI = true;}
      if(RaZsEjRCig == rfKIrRAjnr){xImtDdyqNf = true;}
      while(itlrOXLnTT == LeZBIixTMR){DEHVyTtoIp = true;}
      while(pFanrUAtBf == pFanrUAtBf){UySmfWazfU = true;}
      while(rfKIrRAjnr == rfKIrRAjnr){lBiTpPBCKH = true;}
      if(MuFAXlJBZF == true){MuFAXlJBZF = false;}
      if(nCNekRkozW == true){nCNekRkozW = false;}
      if(sPyOMDicAx == true){sPyOMDicAx = false;}
      if(WbzaGtAaPF == true){WbzaGtAaPF = false;}
      if(KzUuroRfXZ == true){KzUuroRfXZ = false;}
      if(gLjRzxxqmU == true){gLjRzxxqmU = false;}
      if(CgBchMDlXp == true){CgBchMDlXp = false;}
      if(RJYsLsuCVW == true){RJYsLsuCVW = false;}
      if(kDFaPLqgbI == true){kDFaPLqgbI = false;}
      if(xImtDdyqNf == true){xImtDdyqNf = false;}
      if(leIgHXmpGG == true){leIgHXmpGG = false;}
      if(CtUPizbaNW == true){CtUPizbaNW = false;}
      if(UVKOrIVdph == true){UVKOrIVdph = false;}
      if(uDopkGuXSr == true){uDopkGuXSr = false;}
      if(XBaVGCnXLD == true){XBaVGCnXLD = false;}
      if(BXcpKQTsnz == true){BXcpKQTsnz = false;}
      if(BIzYKyFdec == true){BIzYKyFdec = false;}
      if(DEHVyTtoIp == true){DEHVyTtoIp = false;}
      if(UySmfWazfU == true){UySmfWazfU = false;}
      if(lBiTpPBCKH == true){lBiTpPBCKH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSPXXRCQCS
{ 
  void ruYgZDOcax()
  { 
      bool FDpuhlqUKJ = false;
      bool xGDJMzNarJ = false;
      bool IrmxdZeksR = false;
      bool hpxafUXVDw = false;
      bool LSLDoWxlcy = false;
      bool YWNxWMPsQH = false;
      bool HFaraGJcdr = false;
      bool aqWwxogiIH = false;
      bool crIusKbzES = false;
      bool EeFunGqSbh = false;
      bool NUIkWgARzg = false;
      bool fgjJeOxezQ = false;
      bool dKXKmwlaHq = false;
      bool xNGZsIjXYL = false;
      bool KJzXlXtuQY = false;
      bool JLTLEDwxxa = false;
      bool tYKIiSZKPV = false;
      bool eZGmGTKAXP = false;
      bool BqKhhlsuVp = false;
      bool MlZxQkzpnT = false;
      string AGVsJpahPW;
      string qqFmJfytfO;
      string IqnhUlARnz;
      string kaEdgkuQXl;
      string nPdUxNMxZy;
      string kUEyaJSnYW;
      string oJsPkPlbFY;
      string jhVsZrMTkH;
      string ZCrpOQWGCX;
      string SHrBwdWNih;
      string ajrBNDzKXh;
      string wyDQxlRDBU;
      string rfYhFboUww;
      string VzjCgoKqbK;
      string QMhUbTEaDK;
      string MSLNotLJuk;
      string NeNbMwOAjI;
      string bZbpDfxEGk;
      string XOQliCnVMl;
      string dBupxlyGHe;
      if(AGVsJpahPW == ajrBNDzKXh){FDpuhlqUKJ = true;}
      else if(ajrBNDzKXh == AGVsJpahPW){NUIkWgARzg = true;}
      if(qqFmJfytfO == wyDQxlRDBU){xGDJMzNarJ = true;}
      else if(wyDQxlRDBU == qqFmJfytfO){fgjJeOxezQ = true;}
      if(IqnhUlARnz == rfYhFboUww){IrmxdZeksR = true;}
      else if(rfYhFboUww == IqnhUlARnz){dKXKmwlaHq = true;}
      if(kaEdgkuQXl == VzjCgoKqbK){hpxafUXVDw = true;}
      else if(VzjCgoKqbK == kaEdgkuQXl){xNGZsIjXYL = true;}
      if(nPdUxNMxZy == QMhUbTEaDK){LSLDoWxlcy = true;}
      else if(QMhUbTEaDK == nPdUxNMxZy){KJzXlXtuQY = true;}
      if(kUEyaJSnYW == MSLNotLJuk){YWNxWMPsQH = true;}
      else if(MSLNotLJuk == kUEyaJSnYW){JLTLEDwxxa = true;}
      if(oJsPkPlbFY == NeNbMwOAjI){HFaraGJcdr = true;}
      else if(NeNbMwOAjI == oJsPkPlbFY){tYKIiSZKPV = true;}
      if(jhVsZrMTkH == bZbpDfxEGk){aqWwxogiIH = true;}
      if(ZCrpOQWGCX == XOQliCnVMl){crIusKbzES = true;}
      if(SHrBwdWNih == dBupxlyGHe){EeFunGqSbh = true;}
      while(bZbpDfxEGk == jhVsZrMTkH){eZGmGTKAXP = true;}
      while(XOQliCnVMl == XOQliCnVMl){BqKhhlsuVp = true;}
      while(dBupxlyGHe == dBupxlyGHe){MlZxQkzpnT = true;}
      if(FDpuhlqUKJ == true){FDpuhlqUKJ = false;}
      if(xGDJMzNarJ == true){xGDJMzNarJ = false;}
      if(IrmxdZeksR == true){IrmxdZeksR = false;}
      if(hpxafUXVDw == true){hpxafUXVDw = false;}
      if(LSLDoWxlcy == true){LSLDoWxlcy = false;}
      if(YWNxWMPsQH == true){YWNxWMPsQH = false;}
      if(HFaraGJcdr == true){HFaraGJcdr = false;}
      if(aqWwxogiIH == true){aqWwxogiIH = false;}
      if(crIusKbzES == true){crIusKbzES = false;}
      if(EeFunGqSbh == true){EeFunGqSbh = false;}
      if(NUIkWgARzg == true){NUIkWgARzg = false;}
      if(fgjJeOxezQ == true){fgjJeOxezQ = false;}
      if(dKXKmwlaHq == true){dKXKmwlaHq = false;}
      if(xNGZsIjXYL == true){xNGZsIjXYL = false;}
      if(KJzXlXtuQY == true){KJzXlXtuQY = false;}
      if(JLTLEDwxxa == true){JLTLEDwxxa = false;}
      if(tYKIiSZKPV == true){tYKIiSZKPV = false;}
      if(eZGmGTKAXP == true){eZGmGTKAXP = false;}
      if(BqKhhlsuVp == true){BqKhhlsuVp = false;}
      if(MlZxQkzpnT == true){MlZxQkzpnT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVUFZDSTWO
{ 
  void DcHULhCrOY()
  { 
      bool RjLhJbzuhA = false;
      bool uzUBjlrpnL = false;
      bool RlLugfFkSl = false;
      bool RhDjUGKrYH = false;
      bool cVakFKbyEh = false;
      bool oorDXeYPBc = false;
      bool VNbwiMwjgc = false;
      bool bARfiwLapW = false;
      bool EHgjwbpALp = false;
      bool htpukOseCr = false;
      bool OqQaGoXLTb = false;
      bool SyZeYOfrzG = false;
      bool WuYpugJVuT = false;
      bool CfXxIMpFcH = false;
      bool DdfiWiTLWW = false;
      bool iAeuVSSafZ = false;
      bool fCQzZlZbVM = false;
      bool XaPrCsPoSL = false;
      bool NxzXkBBcbo = false;
      bool sPYDbBMfIj = false;
      string CgEdNAMKVU;
      string WpOtiWCews;
      string jXplhZqoEr;
      string hWbylMhKiR;
      string zTaIArGDLo;
      string dOXhFepSwn;
      string JXFdmANQHW;
      string nrudsPwhko;
      string SmcPNSyssH;
      string VPOuIbOxVA;
      string dpuoAkStoo;
      string hIgGUVtoPT;
      string BTWAAYdAVQ;
      string BzLjKcrnPb;
      string AEEDZNhHZm;
      string hYhCyKSuna;
      string HSXXniwxuq;
      string cFZmTxPSal;
      string qVZhibQJlA;
      string KwznUgfgPp;
      if(CgEdNAMKVU == dpuoAkStoo){RjLhJbzuhA = true;}
      else if(dpuoAkStoo == CgEdNAMKVU){OqQaGoXLTb = true;}
      if(WpOtiWCews == hIgGUVtoPT){uzUBjlrpnL = true;}
      else if(hIgGUVtoPT == WpOtiWCews){SyZeYOfrzG = true;}
      if(jXplhZqoEr == BTWAAYdAVQ){RlLugfFkSl = true;}
      else if(BTWAAYdAVQ == jXplhZqoEr){WuYpugJVuT = true;}
      if(hWbylMhKiR == BzLjKcrnPb){RhDjUGKrYH = true;}
      else if(BzLjKcrnPb == hWbylMhKiR){CfXxIMpFcH = true;}
      if(zTaIArGDLo == AEEDZNhHZm){cVakFKbyEh = true;}
      else if(AEEDZNhHZm == zTaIArGDLo){DdfiWiTLWW = true;}
      if(dOXhFepSwn == hYhCyKSuna){oorDXeYPBc = true;}
      else if(hYhCyKSuna == dOXhFepSwn){iAeuVSSafZ = true;}
      if(JXFdmANQHW == HSXXniwxuq){VNbwiMwjgc = true;}
      else if(HSXXniwxuq == JXFdmANQHW){fCQzZlZbVM = true;}
      if(nrudsPwhko == cFZmTxPSal){bARfiwLapW = true;}
      if(SmcPNSyssH == qVZhibQJlA){EHgjwbpALp = true;}
      if(VPOuIbOxVA == KwznUgfgPp){htpukOseCr = true;}
      while(cFZmTxPSal == nrudsPwhko){XaPrCsPoSL = true;}
      while(qVZhibQJlA == qVZhibQJlA){NxzXkBBcbo = true;}
      while(KwznUgfgPp == KwznUgfgPp){sPYDbBMfIj = true;}
      if(RjLhJbzuhA == true){RjLhJbzuhA = false;}
      if(uzUBjlrpnL == true){uzUBjlrpnL = false;}
      if(RlLugfFkSl == true){RlLugfFkSl = false;}
      if(RhDjUGKrYH == true){RhDjUGKrYH = false;}
      if(cVakFKbyEh == true){cVakFKbyEh = false;}
      if(oorDXeYPBc == true){oorDXeYPBc = false;}
      if(VNbwiMwjgc == true){VNbwiMwjgc = false;}
      if(bARfiwLapW == true){bARfiwLapW = false;}
      if(EHgjwbpALp == true){EHgjwbpALp = false;}
      if(htpukOseCr == true){htpukOseCr = false;}
      if(OqQaGoXLTb == true){OqQaGoXLTb = false;}
      if(SyZeYOfrzG == true){SyZeYOfrzG = false;}
      if(WuYpugJVuT == true){WuYpugJVuT = false;}
      if(CfXxIMpFcH == true){CfXxIMpFcH = false;}
      if(DdfiWiTLWW == true){DdfiWiTLWW = false;}
      if(iAeuVSSafZ == true){iAeuVSSafZ = false;}
      if(fCQzZlZbVM == true){fCQzZlZbVM = false;}
      if(XaPrCsPoSL == true){XaPrCsPoSL = false;}
      if(NxzXkBBcbo == true){NxzXkBBcbo = false;}
      if(sPYDbBMfIj == true){sPYDbBMfIj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HVNWNOXLEH
{ 
  void BdIVYxargk()
  { 
      bool bMkthmYcrT = false;
      bool nSNmblCuKC = false;
      bool MNksgDJrUD = false;
      bool ONLrIDNHBX = false;
      bool qNzrayNFrG = false;
      bool dapSNNaqNd = false;
      bool cfInFZGUdX = false;
      bool YuslLzOrSi = false;
      bool pEzNYmWseu = false;
      bool bVtXuKFKmA = false;
      bool qsbThihEGO = false;
      bool ziYemXgtOR = false;
      bool CNohwDAVqB = false;
      bool sDFRqxcefp = false;
      bool FSlQwsxOjW = false;
      bool dKwUycDsXe = false;
      bool hLMEUucGmp = false;
      bool tBOYMiaYkC = false;
      bool FkkUXiHjTN = false;
      bool tiHBHsGgwA = false;
      string DcxueHqGAE;
      string VqJhbBKKYi;
      string aAgWRegTBz;
      string rDQiTCAxHa;
      string cPjMLNtsOU;
      string qEYacCuZdz;
      string aWFALSaaOZ;
      string BMDxFKQUKD;
      string kmFfIndpFQ;
      string HZTHAGKiAs;
      string lTeoTdBbUS;
      string lZPZOmRYrX;
      string njUyRasuwz;
      string AhURQQIPMd;
      string mCVmegKtsM;
      string okqcFCzgXr;
      string kFeURDFxIy;
      string eBMNkkOgSk;
      string QyCjKPqqMO;
      string QarUsgWAUa;
      if(DcxueHqGAE == lTeoTdBbUS){bMkthmYcrT = true;}
      else if(lTeoTdBbUS == DcxueHqGAE){qsbThihEGO = true;}
      if(VqJhbBKKYi == lZPZOmRYrX){nSNmblCuKC = true;}
      else if(lZPZOmRYrX == VqJhbBKKYi){ziYemXgtOR = true;}
      if(aAgWRegTBz == njUyRasuwz){MNksgDJrUD = true;}
      else if(njUyRasuwz == aAgWRegTBz){CNohwDAVqB = true;}
      if(rDQiTCAxHa == AhURQQIPMd){ONLrIDNHBX = true;}
      else if(AhURQQIPMd == rDQiTCAxHa){sDFRqxcefp = true;}
      if(cPjMLNtsOU == mCVmegKtsM){qNzrayNFrG = true;}
      else if(mCVmegKtsM == cPjMLNtsOU){FSlQwsxOjW = true;}
      if(qEYacCuZdz == okqcFCzgXr){dapSNNaqNd = true;}
      else if(okqcFCzgXr == qEYacCuZdz){dKwUycDsXe = true;}
      if(aWFALSaaOZ == kFeURDFxIy){cfInFZGUdX = true;}
      else if(kFeURDFxIy == aWFALSaaOZ){hLMEUucGmp = true;}
      if(BMDxFKQUKD == eBMNkkOgSk){YuslLzOrSi = true;}
      if(kmFfIndpFQ == QyCjKPqqMO){pEzNYmWseu = true;}
      if(HZTHAGKiAs == QarUsgWAUa){bVtXuKFKmA = true;}
      while(eBMNkkOgSk == BMDxFKQUKD){tBOYMiaYkC = true;}
      while(QyCjKPqqMO == QyCjKPqqMO){FkkUXiHjTN = true;}
      while(QarUsgWAUa == QarUsgWAUa){tiHBHsGgwA = true;}
      if(bMkthmYcrT == true){bMkthmYcrT = false;}
      if(nSNmblCuKC == true){nSNmblCuKC = false;}
      if(MNksgDJrUD == true){MNksgDJrUD = false;}
      if(ONLrIDNHBX == true){ONLrIDNHBX = false;}
      if(qNzrayNFrG == true){qNzrayNFrG = false;}
      if(dapSNNaqNd == true){dapSNNaqNd = false;}
      if(cfInFZGUdX == true){cfInFZGUdX = false;}
      if(YuslLzOrSi == true){YuslLzOrSi = false;}
      if(pEzNYmWseu == true){pEzNYmWseu = false;}
      if(bVtXuKFKmA == true){bVtXuKFKmA = false;}
      if(qsbThihEGO == true){qsbThihEGO = false;}
      if(ziYemXgtOR == true){ziYemXgtOR = false;}
      if(CNohwDAVqB == true){CNohwDAVqB = false;}
      if(sDFRqxcefp == true){sDFRqxcefp = false;}
      if(FSlQwsxOjW == true){FSlQwsxOjW = false;}
      if(dKwUycDsXe == true){dKwUycDsXe = false;}
      if(hLMEUucGmp == true){hLMEUucGmp = false;}
      if(tBOYMiaYkC == true){tBOYMiaYkC = false;}
      if(FkkUXiHjTN == true){FkkUXiHjTN = false;}
      if(tiHBHsGgwA == true){tiHBHsGgwA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDQLQPRNAM
{ 
  void hKQMSinUcc()
  { 
      bool bXLerVtcXm = false;
      bool MssjdNCnLr = false;
      bool IVMXnhCdJG = false;
      bool DqKmnetRFS = false;
      bool fXxmdDouju = false;
      bool TTPobGLmpJ = false;
      bool TPSRiUiGwy = false;
      bool TkirMkXZtk = false;
      bool sHsOliaUKg = false;
      bool THauyPEfDI = false;
      bool ThylbhkWcp = false;
      bool iksFQMVEeA = false;
      bool sOwPdLKmtw = false;
      bool grVkRKIHmE = false;
      bool yDrTxiOUdl = false;
      bool sAADPEliIP = false;
      bool XxcfJqPHnG = false;
      bool EOQaCoWbRu = false;
      bool xoJHCgqSVM = false;
      bool XZzWfAaLKG = false;
      string LfYLwqyCuW;
      string JrRXfzbRIM;
      string pMyhhOpSXT;
      string rOcuBPOlSa;
      string zEUdCnBFBg;
      string oKZHQzhqch;
      string BfdaeuPWVQ;
      string koygMlqUfs;
      string NjQqdgnVeC;
      string gWIkZTZsyG;
      string YdjjuALstd;
      string HNLiUQOmxx;
      string HtrSjOfMGs;
      string LxVYUiAfud;
      string UuaAuTKZQI;
      string ElwAzelRAg;
      string UzlARJqmOk;
      string QhrTbMSrXP;
      string DGwxoZAVZp;
      string xifNJVIahk;
      if(LfYLwqyCuW == YdjjuALstd){bXLerVtcXm = true;}
      else if(YdjjuALstd == LfYLwqyCuW){ThylbhkWcp = true;}
      if(JrRXfzbRIM == HNLiUQOmxx){MssjdNCnLr = true;}
      else if(HNLiUQOmxx == JrRXfzbRIM){iksFQMVEeA = true;}
      if(pMyhhOpSXT == HtrSjOfMGs){IVMXnhCdJG = true;}
      else if(HtrSjOfMGs == pMyhhOpSXT){sOwPdLKmtw = true;}
      if(rOcuBPOlSa == LxVYUiAfud){DqKmnetRFS = true;}
      else if(LxVYUiAfud == rOcuBPOlSa){grVkRKIHmE = true;}
      if(zEUdCnBFBg == UuaAuTKZQI){fXxmdDouju = true;}
      else if(UuaAuTKZQI == zEUdCnBFBg){yDrTxiOUdl = true;}
      if(oKZHQzhqch == ElwAzelRAg){TTPobGLmpJ = true;}
      else if(ElwAzelRAg == oKZHQzhqch){sAADPEliIP = true;}
      if(BfdaeuPWVQ == UzlARJqmOk){TPSRiUiGwy = true;}
      else if(UzlARJqmOk == BfdaeuPWVQ){XxcfJqPHnG = true;}
      if(koygMlqUfs == QhrTbMSrXP){TkirMkXZtk = true;}
      if(NjQqdgnVeC == DGwxoZAVZp){sHsOliaUKg = true;}
      if(gWIkZTZsyG == xifNJVIahk){THauyPEfDI = true;}
      while(QhrTbMSrXP == koygMlqUfs){EOQaCoWbRu = true;}
      while(DGwxoZAVZp == DGwxoZAVZp){xoJHCgqSVM = true;}
      while(xifNJVIahk == xifNJVIahk){XZzWfAaLKG = true;}
      if(bXLerVtcXm == true){bXLerVtcXm = false;}
      if(MssjdNCnLr == true){MssjdNCnLr = false;}
      if(IVMXnhCdJG == true){IVMXnhCdJG = false;}
      if(DqKmnetRFS == true){DqKmnetRFS = false;}
      if(fXxmdDouju == true){fXxmdDouju = false;}
      if(TTPobGLmpJ == true){TTPobGLmpJ = false;}
      if(TPSRiUiGwy == true){TPSRiUiGwy = false;}
      if(TkirMkXZtk == true){TkirMkXZtk = false;}
      if(sHsOliaUKg == true){sHsOliaUKg = false;}
      if(THauyPEfDI == true){THauyPEfDI = false;}
      if(ThylbhkWcp == true){ThylbhkWcp = false;}
      if(iksFQMVEeA == true){iksFQMVEeA = false;}
      if(sOwPdLKmtw == true){sOwPdLKmtw = false;}
      if(grVkRKIHmE == true){grVkRKIHmE = false;}
      if(yDrTxiOUdl == true){yDrTxiOUdl = false;}
      if(sAADPEliIP == true){sAADPEliIP = false;}
      if(XxcfJqPHnG == true){XxcfJqPHnG = false;}
      if(EOQaCoWbRu == true){EOQaCoWbRu = false;}
      if(xoJHCgqSVM == true){xoJHCgqSVM = false;}
      if(XZzWfAaLKG == true){XZzWfAaLKG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGMWRWOPTS
{ 
  void XjTkOWVDzi()
  { 
      bool sDKJTArAAO = false;
      bool PzNmCOpCWD = false;
      bool gjkoOqmyHt = false;
      bool uqexoZhGoA = false;
      bool yJaeMcbXKO = false;
      bool ziAKBISVtb = false;
      bool MtrGSXUQyc = false;
      bool fjNWEWIFbl = false;
      bool OPmruLpUuf = false;
      bool GMLNnDQUMn = false;
      bool ILZhhOVdFd = false;
      bool ANsHMxHzKH = false;
      bool hzVSVTXAhA = false;
      bool GmsmdDpEKf = false;
      bool pLOQesSDAp = false;
      bool wRKEGIoGMO = false;
      bool pVuEXMTGdI = false;
      bool HDoeQVjFmb = false;
      bool ATzrEocngU = false;
      bool OiquoUQKrS = false;
      string sBatsxmtyb;
      string MMzRAMpbzi;
      string IBxnXOwQBL;
      string aQcxChsVtU;
      string CCwSWZxNaM;
      string xFyGwqDmVe;
      string BVslBwiCPR;
      string STgdgFFdQy;
      string QhpnOURWAK;
      string dFzPTfJJRa;
      string quyItcXUZq;
      string lYVXNSfFXg;
      string dMCEmNURJA;
      string wuMpGVjgtl;
      string wwxIYFibBB;
      string zElkwessVf;
      string HGKYupLeQr;
      string hzLljgPsfh;
      string dsPIBqJbtb;
      string cpLNdplXNh;
      if(sBatsxmtyb == quyItcXUZq){sDKJTArAAO = true;}
      else if(quyItcXUZq == sBatsxmtyb){ILZhhOVdFd = true;}
      if(MMzRAMpbzi == lYVXNSfFXg){PzNmCOpCWD = true;}
      else if(lYVXNSfFXg == MMzRAMpbzi){ANsHMxHzKH = true;}
      if(IBxnXOwQBL == dMCEmNURJA){gjkoOqmyHt = true;}
      else if(dMCEmNURJA == IBxnXOwQBL){hzVSVTXAhA = true;}
      if(aQcxChsVtU == wuMpGVjgtl){uqexoZhGoA = true;}
      else if(wuMpGVjgtl == aQcxChsVtU){GmsmdDpEKf = true;}
      if(CCwSWZxNaM == wwxIYFibBB){yJaeMcbXKO = true;}
      else if(wwxIYFibBB == CCwSWZxNaM){pLOQesSDAp = true;}
      if(xFyGwqDmVe == zElkwessVf){ziAKBISVtb = true;}
      else if(zElkwessVf == xFyGwqDmVe){wRKEGIoGMO = true;}
      if(BVslBwiCPR == HGKYupLeQr){MtrGSXUQyc = true;}
      else if(HGKYupLeQr == BVslBwiCPR){pVuEXMTGdI = true;}
      if(STgdgFFdQy == hzLljgPsfh){fjNWEWIFbl = true;}
      if(QhpnOURWAK == dsPIBqJbtb){OPmruLpUuf = true;}
      if(dFzPTfJJRa == cpLNdplXNh){GMLNnDQUMn = true;}
      while(hzLljgPsfh == STgdgFFdQy){HDoeQVjFmb = true;}
      while(dsPIBqJbtb == dsPIBqJbtb){ATzrEocngU = true;}
      while(cpLNdplXNh == cpLNdplXNh){OiquoUQKrS = true;}
      if(sDKJTArAAO == true){sDKJTArAAO = false;}
      if(PzNmCOpCWD == true){PzNmCOpCWD = false;}
      if(gjkoOqmyHt == true){gjkoOqmyHt = false;}
      if(uqexoZhGoA == true){uqexoZhGoA = false;}
      if(yJaeMcbXKO == true){yJaeMcbXKO = false;}
      if(ziAKBISVtb == true){ziAKBISVtb = false;}
      if(MtrGSXUQyc == true){MtrGSXUQyc = false;}
      if(fjNWEWIFbl == true){fjNWEWIFbl = false;}
      if(OPmruLpUuf == true){OPmruLpUuf = false;}
      if(GMLNnDQUMn == true){GMLNnDQUMn = false;}
      if(ILZhhOVdFd == true){ILZhhOVdFd = false;}
      if(ANsHMxHzKH == true){ANsHMxHzKH = false;}
      if(hzVSVTXAhA == true){hzVSVTXAhA = false;}
      if(GmsmdDpEKf == true){GmsmdDpEKf = false;}
      if(pLOQesSDAp == true){pLOQesSDAp = false;}
      if(wRKEGIoGMO == true){wRKEGIoGMO = false;}
      if(pVuEXMTGdI == true){pVuEXMTGdI = false;}
      if(HDoeQVjFmb == true){HDoeQVjFmb = false;}
      if(ATzrEocngU == true){ATzrEocngU = false;}
      if(OiquoUQKrS == true){OiquoUQKrS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCDHUQOEGJ
{ 
  void UfphBUJtsR()
  { 
      bool fnYTaYsrsc = false;
      bool SzaVsSXJfo = false;
      bool kZJyraFcjq = false;
      bool caiDhlwJHj = false;
      bool AzghARKjof = false;
      bool NbhjCFeZbA = false;
      bool TQICAqQWmH = false;
      bool VNBunksaya = false;
      bool PUmEcBszBb = false;
      bool GVhHQjqdhI = false;
      bool AnxhJzZlwR = false;
      bool MEbAjzdEYy = false;
      bool yRVKAAfteE = false;
      bool sOroZbWEuc = false;
      bool aGCjPCsgWQ = false;
      bool GmEjKiRlgI = false;
      bool TfHqXxLmaI = false;
      bool bYIuWqOluy = false;
      bool HyWNyGJIdp = false;
      bool JkXlJuyLLR = false;
      string VRhldbmxZn;
      string nnFueRwUnm;
      string EKkSPpcSdY;
      string ZwFtYIyEAH;
      string GlwBcknwzW;
      string odzQBLgOVm;
      string zUTBNqiLVV;
      string TrUgfRNjpd;
      string CfSGiwxnrN;
      string bihNIlStml;
      string CbacDxIRji;
      string xwYrjSBNSQ;
      string stSHsjKGYt;
      string zTwDaaFpCk;
      string neEJQfJoco;
      string jEaWrIJSiT;
      string mBspjczUQJ;
      string NLLhcOpJqN;
      string ZUdiJtrZLS;
      string RlGiylkOZm;
      if(VRhldbmxZn == CbacDxIRji){fnYTaYsrsc = true;}
      else if(CbacDxIRji == VRhldbmxZn){AnxhJzZlwR = true;}
      if(nnFueRwUnm == xwYrjSBNSQ){SzaVsSXJfo = true;}
      else if(xwYrjSBNSQ == nnFueRwUnm){MEbAjzdEYy = true;}
      if(EKkSPpcSdY == stSHsjKGYt){kZJyraFcjq = true;}
      else if(stSHsjKGYt == EKkSPpcSdY){yRVKAAfteE = true;}
      if(ZwFtYIyEAH == zTwDaaFpCk){caiDhlwJHj = true;}
      else if(zTwDaaFpCk == ZwFtYIyEAH){sOroZbWEuc = true;}
      if(GlwBcknwzW == neEJQfJoco){AzghARKjof = true;}
      else if(neEJQfJoco == GlwBcknwzW){aGCjPCsgWQ = true;}
      if(odzQBLgOVm == jEaWrIJSiT){NbhjCFeZbA = true;}
      else if(jEaWrIJSiT == odzQBLgOVm){GmEjKiRlgI = true;}
      if(zUTBNqiLVV == mBspjczUQJ){TQICAqQWmH = true;}
      else if(mBspjczUQJ == zUTBNqiLVV){TfHqXxLmaI = true;}
      if(TrUgfRNjpd == NLLhcOpJqN){VNBunksaya = true;}
      if(CfSGiwxnrN == ZUdiJtrZLS){PUmEcBszBb = true;}
      if(bihNIlStml == RlGiylkOZm){GVhHQjqdhI = true;}
      while(NLLhcOpJqN == TrUgfRNjpd){bYIuWqOluy = true;}
      while(ZUdiJtrZLS == ZUdiJtrZLS){HyWNyGJIdp = true;}
      while(RlGiylkOZm == RlGiylkOZm){JkXlJuyLLR = true;}
      if(fnYTaYsrsc == true){fnYTaYsrsc = false;}
      if(SzaVsSXJfo == true){SzaVsSXJfo = false;}
      if(kZJyraFcjq == true){kZJyraFcjq = false;}
      if(caiDhlwJHj == true){caiDhlwJHj = false;}
      if(AzghARKjof == true){AzghARKjof = false;}
      if(NbhjCFeZbA == true){NbhjCFeZbA = false;}
      if(TQICAqQWmH == true){TQICAqQWmH = false;}
      if(VNBunksaya == true){VNBunksaya = false;}
      if(PUmEcBszBb == true){PUmEcBszBb = false;}
      if(GVhHQjqdhI == true){GVhHQjqdhI = false;}
      if(AnxhJzZlwR == true){AnxhJzZlwR = false;}
      if(MEbAjzdEYy == true){MEbAjzdEYy = false;}
      if(yRVKAAfteE == true){yRVKAAfteE = false;}
      if(sOroZbWEuc == true){sOroZbWEuc = false;}
      if(aGCjPCsgWQ == true){aGCjPCsgWQ = false;}
      if(GmEjKiRlgI == true){GmEjKiRlgI = false;}
      if(TfHqXxLmaI == true){TfHqXxLmaI = false;}
      if(bYIuWqOluy == true){bYIuWqOluy = false;}
      if(HyWNyGJIdp == true){HyWNyGJIdp = false;}
      if(JkXlJuyLLR == true){JkXlJuyLLR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIXNCYHWPE
{ 
  void jtkAlSknXP()
  { 
      bool NTxWgCKCwU = false;
      bool asrOWEgIOC = false;
      bool VUsLjVHuAP = false;
      bool GihfiWHuBV = false;
      bool rrVQbBqwJS = false;
      bool ESWyuraklL = false;
      bool tOBfNqKMez = false;
      bool xlHrKczbji = false;
      bool dLkhLmMjkq = false;
      bool wVIpbcpoDk = false;
      bool peQKUSLdmR = false;
      bool szBDghcTUZ = false;
      bool eabnDacRQh = false;
      bool lJXyrzuaMs = false;
      bool bhwSxwTFIs = false;
      bool zWUcGODbHt = false;
      bool osMFejaCKg = false;
      bool mCHaywdIqG = false;
      bool HWIXhPnurc = false;
      bool wSTSDhVqmN = false;
      string UmHnsrLfnz;
      string PwtAFxaUho;
      string dlinhCPoLc;
      string DfuABFmgut;
      string idnhqrMUIN;
      string UuAnwhDSFq;
      string bWTLwjBtyz;
      string KtYmGzxBxp;
      string oufxHHfGDS;
      string CTbESLJclH;
      string qSVIDaVMgw;
      string kCUOBfpVDn;
      string DtpexpRUUt;
      string pTPpzWZWtf;
      string lTYHhAyMCl;
      string VmYxEwbpLN;
      string JAqmGQlePe;
      string FSbWBiUixx;
      string qEShYDtRlD;
      string tjKfWlblBQ;
      if(UmHnsrLfnz == qSVIDaVMgw){NTxWgCKCwU = true;}
      else if(qSVIDaVMgw == UmHnsrLfnz){peQKUSLdmR = true;}
      if(PwtAFxaUho == kCUOBfpVDn){asrOWEgIOC = true;}
      else if(kCUOBfpVDn == PwtAFxaUho){szBDghcTUZ = true;}
      if(dlinhCPoLc == DtpexpRUUt){VUsLjVHuAP = true;}
      else if(DtpexpRUUt == dlinhCPoLc){eabnDacRQh = true;}
      if(DfuABFmgut == pTPpzWZWtf){GihfiWHuBV = true;}
      else if(pTPpzWZWtf == DfuABFmgut){lJXyrzuaMs = true;}
      if(idnhqrMUIN == lTYHhAyMCl){rrVQbBqwJS = true;}
      else if(lTYHhAyMCl == idnhqrMUIN){bhwSxwTFIs = true;}
      if(UuAnwhDSFq == VmYxEwbpLN){ESWyuraklL = true;}
      else if(VmYxEwbpLN == UuAnwhDSFq){zWUcGODbHt = true;}
      if(bWTLwjBtyz == JAqmGQlePe){tOBfNqKMez = true;}
      else if(JAqmGQlePe == bWTLwjBtyz){osMFejaCKg = true;}
      if(KtYmGzxBxp == FSbWBiUixx){xlHrKczbji = true;}
      if(oufxHHfGDS == qEShYDtRlD){dLkhLmMjkq = true;}
      if(CTbESLJclH == tjKfWlblBQ){wVIpbcpoDk = true;}
      while(FSbWBiUixx == KtYmGzxBxp){mCHaywdIqG = true;}
      while(qEShYDtRlD == qEShYDtRlD){HWIXhPnurc = true;}
      while(tjKfWlblBQ == tjKfWlblBQ){wSTSDhVqmN = true;}
      if(NTxWgCKCwU == true){NTxWgCKCwU = false;}
      if(asrOWEgIOC == true){asrOWEgIOC = false;}
      if(VUsLjVHuAP == true){VUsLjVHuAP = false;}
      if(GihfiWHuBV == true){GihfiWHuBV = false;}
      if(rrVQbBqwJS == true){rrVQbBqwJS = false;}
      if(ESWyuraklL == true){ESWyuraklL = false;}
      if(tOBfNqKMez == true){tOBfNqKMez = false;}
      if(xlHrKczbji == true){xlHrKczbji = false;}
      if(dLkhLmMjkq == true){dLkhLmMjkq = false;}
      if(wVIpbcpoDk == true){wVIpbcpoDk = false;}
      if(peQKUSLdmR == true){peQKUSLdmR = false;}
      if(szBDghcTUZ == true){szBDghcTUZ = false;}
      if(eabnDacRQh == true){eabnDacRQh = false;}
      if(lJXyrzuaMs == true){lJXyrzuaMs = false;}
      if(bhwSxwTFIs == true){bhwSxwTFIs = false;}
      if(zWUcGODbHt == true){zWUcGODbHt = false;}
      if(osMFejaCKg == true){osMFejaCKg = false;}
      if(mCHaywdIqG == true){mCHaywdIqG = false;}
      if(HWIXhPnurc == true){HWIXhPnurc = false;}
      if(wSTSDhVqmN == true){wSTSDhVqmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGPFBVDTAR
{ 
  void IyAmtTaQYI()
  { 
      bool yDtgZiLklX = false;
      bool IMsznPzYCC = false;
      bool qkwOmfleYF = false;
      bool dtkyouaKFi = false;
      bool wYoITJNOXK = false;
      bool DTlVYMHfts = false;
      bool xgLftObtJs = false;
      bool nnSSGSwmtd = false;
      bool SWGNBJHOZb = false;
      bool muQMlPMIOF = false;
      bool hSFeWOBSOF = false;
      bool QTlQZZZydk = false;
      bool GMThFsXGgp = false;
      bool FmYnuzRapl = false;
      bool HozTKTJAlL = false;
      bool pNddzVyWZd = false;
      bool qulYAduxUa = false;
      bool IyHqcQMzWl = false;
      bool iXTUAqIuoZ = false;
      bool AtBMuLDaTg = false;
      string nIOLbyCSRG;
      string UMkpqxFanN;
      string ODCTCUnOGA;
      string cFpkxzfDzb;
      string ZHNedDOhcl;
      string uDJKdkGtIH;
      string JnMRdPVAsq;
      string RCbLnGpWpz;
      string GFlTFYufGM;
      string sktqRkuwAO;
      string gOokTsbyWW;
      string uiEJAEBrLF;
      string TpsfyfHjsC;
      string LsVaSqPBAM;
      string wxIjRKgkqN;
      string jDjutpVIlm;
      string krEULBMcpJ;
      string nAqzJWhJOm;
      string zVrfSIJagb;
      string VHOMaDsnYP;
      if(nIOLbyCSRG == gOokTsbyWW){yDtgZiLklX = true;}
      else if(gOokTsbyWW == nIOLbyCSRG){hSFeWOBSOF = true;}
      if(UMkpqxFanN == uiEJAEBrLF){IMsznPzYCC = true;}
      else if(uiEJAEBrLF == UMkpqxFanN){QTlQZZZydk = true;}
      if(ODCTCUnOGA == TpsfyfHjsC){qkwOmfleYF = true;}
      else if(TpsfyfHjsC == ODCTCUnOGA){GMThFsXGgp = true;}
      if(cFpkxzfDzb == LsVaSqPBAM){dtkyouaKFi = true;}
      else if(LsVaSqPBAM == cFpkxzfDzb){FmYnuzRapl = true;}
      if(ZHNedDOhcl == wxIjRKgkqN){wYoITJNOXK = true;}
      else if(wxIjRKgkqN == ZHNedDOhcl){HozTKTJAlL = true;}
      if(uDJKdkGtIH == jDjutpVIlm){DTlVYMHfts = true;}
      else if(jDjutpVIlm == uDJKdkGtIH){pNddzVyWZd = true;}
      if(JnMRdPVAsq == krEULBMcpJ){xgLftObtJs = true;}
      else if(krEULBMcpJ == JnMRdPVAsq){qulYAduxUa = true;}
      if(RCbLnGpWpz == nAqzJWhJOm){nnSSGSwmtd = true;}
      if(GFlTFYufGM == zVrfSIJagb){SWGNBJHOZb = true;}
      if(sktqRkuwAO == VHOMaDsnYP){muQMlPMIOF = true;}
      while(nAqzJWhJOm == RCbLnGpWpz){IyHqcQMzWl = true;}
      while(zVrfSIJagb == zVrfSIJagb){iXTUAqIuoZ = true;}
      while(VHOMaDsnYP == VHOMaDsnYP){AtBMuLDaTg = true;}
      if(yDtgZiLklX == true){yDtgZiLklX = false;}
      if(IMsznPzYCC == true){IMsznPzYCC = false;}
      if(qkwOmfleYF == true){qkwOmfleYF = false;}
      if(dtkyouaKFi == true){dtkyouaKFi = false;}
      if(wYoITJNOXK == true){wYoITJNOXK = false;}
      if(DTlVYMHfts == true){DTlVYMHfts = false;}
      if(xgLftObtJs == true){xgLftObtJs = false;}
      if(nnSSGSwmtd == true){nnSSGSwmtd = false;}
      if(SWGNBJHOZb == true){SWGNBJHOZb = false;}
      if(muQMlPMIOF == true){muQMlPMIOF = false;}
      if(hSFeWOBSOF == true){hSFeWOBSOF = false;}
      if(QTlQZZZydk == true){QTlQZZZydk = false;}
      if(GMThFsXGgp == true){GMThFsXGgp = false;}
      if(FmYnuzRapl == true){FmYnuzRapl = false;}
      if(HozTKTJAlL == true){HozTKTJAlL = false;}
      if(pNddzVyWZd == true){pNddzVyWZd = false;}
      if(qulYAduxUa == true){qulYAduxUa = false;}
      if(IyHqcQMzWl == true){IyHqcQMzWl = false;}
      if(iXTUAqIuoZ == true){iXTUAqIuoZ = false;}
      if(AtBMuLDaTg == true){AtBMuLDaTg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYVWBGEVAZ
{ 
  void ezKuSDuLgs()
  { 
      bool AfdXwmKqXn = false;
      bool mZsedbfCXA = false;
      bool NkbxkqCxfh = false;
      bool xBPaYpNYjH = false;
      bool ubDQZwedsW = false;
      bool NzxKKOEflF = false;
      bool jNLoqkJRFm = false;
      bool NHRPFlhLWn = false;
      bool MYDIUxEFPK = false;
      bool lgleXgPOYo = false;
      bool mMXFIGhgFY = false;
      bool frJysKJDTs = false;
      bool fEBuBgUlqX = false;
      bool VSlhBzByzO = false;
      bool PWApdsXmlM = false;
      bool XMufIhKbDb = false;
      bool kupgDMGaxs = false;
      bool JLEEdJDKRI = false;
      bool JgAeAJXGZS = false;
      bool nYtWdTgSmQ = false;
      string XzisTmGMll;
      string anPlwzzzUQ;
      string drorUTseNV;
      string PadLFKcwLk;
      string zViSZdzdbG;
      string DpLdAeJqYA;
      string tbzPVAJEfl;
      string VDmjRHIWRq;
      string TOCHSYOzKa;
      string AlWLqXWTwZ;
      string TuypjzDbMr;
      string VmYhffYqxx;
      string lJsFljfart;
      string koZrWYQMWS;
      string UlmRFMMoeL;
      string yeVznJBrDA;
      string TbjSGfMgKH;
      string OLTebzWazY;
      string WqwguGSaEN;
      string WXIWzsCUKY;
      if(XzisTmGMll == TuypjzDbMr){AfdXwmKqXn = true;}
      else if(TuypjzDbMr == XzisTmGMll){mMXFIGhgFY = true;}
      if(anPlwzzzUQ == VmYhffYqxx){mZsedbfCXA = true;}
      else if(VmYhffYqxx == anPlwzzzUQ){frJysKJDTs = true;}
      if(drorUTseNV == lJsFljfart){NkbxkqCxfh = true;}
      else if(lJsFljfart == drorUTseNV){fEBuBgUlqX = true;}
      if(PadLFKcwLk == koZrWYQMWS){xBPaYpNYjH = true;}
      else if(koZrWYQMWS == PadLFKcwLk){VSlhBzByzO = true;}
      if(zViSZdzdbG == UlmRFMMoeL){ubDQZwedsW = true;}
      else if(UlmRFMMoeL == zViSZdzdbG){PWApdsXmlM = true;}
      if(DpLdAeJqYA == yeVznJBrDA){NzxKKOEflF = true;}
      else if(yeVznJBrDA == DpLdAeJqYA){XMufIhKbDb = true;}
      if(tbzPVAJEfl == TbjSGfMgKH){jNLoqkJRFm = true;}
      else if(TbjSGfMgKH == tbzPVAJEfl){kupgDMGaxs = true;}
      if(VDmjRHIWRq == OLTebzWazY){NHRPFlhLWn = true;}
      if(TOCHSYOzKa == WqwguGSaEN){MYDIUxEFPK = true;}
      if(AlWLqXWTwZ == WXIWzsCUKY){lgleXgPOYo = true;}
      while(OLTebzWazY == VDmjRHIWRq){JLEEdJDKRI = true;}
      while(WqwguGSaEN == WqwguGSaEN){JgAeAJXGZS = true;}
      while(WXIWzsCUKY == WXIWzsCUKY){nYtWdTgSmQ = true;}
      if(AfdXwmKqXn == true){AfdXwmKqXn = false;}
      if(mZsedbfCXA == true){mZsedbfCXA = false;}
      if(NkbxkqCxfh == true){NkbxkqCxfh = false;}
      if(xBPaYpNYjH == true){xBPaYpNYjH = false;}
      if(ubDQZwedsW == true){ubDQZwedsW = false;}
      if(NzxKKOEflF == true){NzxKKOEflF = false;}
      if(jNLoqkJRFm == true){jNLoqkJRFm = false;}
      if(NHRPFlhLWn == true){NHRPFlhLWn = false;}
      if(MYDIUxEFPK == true){MYDIUxEFPK = false;}
      if(lgleXgPOYo == true){lgleXgPOYo = false;}
      if(mMXFIGhgFY == true){mMXFIGhgFY = false;}
      if(frJysKJDTs == true){frJysKJDTs = false;}
      if(fEBuBgUlqX == true){fEBuBgUlqX = false;}
      if(VSlhBzByzO == true){VSlhBzByzO = false;}
      if(PWApdsXmlM == true){PWApdsXmlM = false;}
      if(XMufIhKbDb == true){XMufIhKbDb = false;}
      if(kupgDMGaxs == true){kupgDMGaxs = false;}
      if(JLEEdJDKRI == true){JLEEdJDKRI = false;}
      if(JgAeAJXGZS == true){JgAeAJXGZS = false;}
      if(nYtWdTgSmQ == true){nYtWdTgSmQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIINHPWWKT
{ 
  void UpaKhJhmOO()
  { 
      bool BsWJgRbdws = false;
      bool hdPGAKWxEA = false;
      bool PUwDaqbVmH = false;
      bool HmqFCcUsqk = false;
      bool ifuHmxhjsF = false;
      bool VazCDgxTio = false;
      bool oFpnltlJEW = false;
      bool pdFSQiYnPc = false;
      bool JrchkfnoCV = false;
      bool fBKBwdpGVs = false;
      bool KXeWOrVfkT = false;
      bool HIDFfwcHDF = false;
      bool GxHiqoTEWl = false;
      bool sRSWSkMGTs = false;
      bool KHDhNWxEUz = false;
      bool BhDPlNPweZ = false;
      bool YQJzZopgmt = false;
      bool jWnKtzsYUT = false;
      bool qOiWjLOCjE = false;
      bool VQasUsxEHX = false;
      string xMKBOxeDhu;
      string BGBDEuFJJt;
      string mhCKKnciSB;
      string SRwSZYQEkR;
      string BKktimLiGP;
      string rLHnqOJApa;
      string UwjfbiKhcf;
      string eBXrscxHaW;
      string bsbCJHJHbK;
      string OQNKxFZESz;
      string cdGakpmPuO;
      string RBYSzaUhWU;
      string ZDGRQNmNtn;
      string DroatylBQS;
      string TsLNsNquKV;
      string krhxZYWnKW;
      string CZVHKZLxXB;
      string oSQDBfqsYD;
      string WrCXDKKqBU;
      string axqtPsXECS;
      if(xMKBOxeDhu == cdGakpmPuO){BsWJgRbdws = true;}
      else if(cdGakpmPuO == xMKBOxeDhu){KXeWOrVfkT = true;}
      if(BGBDEuFJJt == RBYSzaUhWU){hdPGAKWxEA = true;}
      else if(RBYSzaUhWU == BGBDEuFJJt){HIDFfwcHDF = true;}
      if(mhCKKnciSB == ZDGRQNmNtn){PUwDaqbVmH = true;}
      else if(ZDGRQNmNtn == mhCKKnciSB){GxHiqoTEWl = true;}
      if(SRwSZYQEkR == DroatylBQS){HmqFCcUsqk = true;}
      else if(DroatylBQS == SRwSZYQEkR){sRSWSkMGTs = true;}
      if(BKktimLiGP == TsLNsNquKV){ifuHmxhjsF = true;}
      else if(TsLNsNquKV == BKktimLiGP){KHDhNWxEUz = true;}
      if(rLHnqOJApa == krhxZYWnKW){VazCDgxTio = true;}
      else if(krhxZYWnKW == rLHnqOJApa){BhDPlNPweZ = true;}
      if(UwjfbiKhcf == CZVHKZLxXB){oFpnltlJEW = true;}
      else if(CZVHKZLxXB == UwjfbiKhcf){YQJzZopgmt = true;}
      if(eBXrscxHaW == oSQDBfqsYD){pdFSQiYnPc = true;}
      if(bsbCJHJHbK == WrCXDKKqBU){JrchkfnoCV = true;}
      if(OQNKxFZESz == axqtPsXECS){fBKBwdpGVs = true;}
      while(oSQDBfqsYD == eBXrscxHaW){jWnKtzsYUT = true;}
      while(WrCXDKKqBU == WrCXDKKqBU){qOiWjLOCjE = true;}
      while(axqtPsXECS == axqtPsXECS){VQasUsxEHX = true;}
      if(BsWJgRbdws == true){BsWJgRbdws = false;}
      if(hdPGAKWxEA == true){hdPGAKWxEA = false;}
      if(PUwDaqbVmH == true){PUwDaqbVmH = false;}
      if(HmqFCcUsqk == true){HmqFCcUsqk = false;}
      if(ifuHmxhjsF == true){ifuHmxhjsF = false;}
      if(VazCDgxTio == true){VazCDgxTio = false;}
      if(oFpnltlJEW == true){oFpnltlJEW = false;}
      if(pdFSQiYnPc == true){pdFSQiYnPc = false;}
      if(JrchkfnoCV == true){JrchkfnoCV = false;}
      if(fBKBwdpGVs == true){fBKBwdpGVs = false;}
      if(KXeWOrVfkT == true){KXeWOrVfkT = false;}
      if(HIDFfwcHDF == true){HIDFfwcHDF = false;}
      if(GxHiqoTEWl == true){GxHiqoTEWl = false;}
      if(sRSWSkMGTs == true){sRSWSkMGTs = false;}
      if(KHDhNWxEUz == true){KHDhNWxEUz = false;}
      if(BhDPlNPweZ == true){BhDPlNPweZ = false;}
      if(YQJzZopgmt == true){YQJzZopgmt = false;}
      if(jWnKtzsYUT == true){jWnKtzsYUT = false;}
      if(qOiWjLOCjE == true){qOiWjLOCjE = false;}
      if(VQasUsxEHX == true){VQasUsxEHX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDCVICVHSI
{ 
  void sDVkRnSfsV()
  { 
      bool jWrardSrdE = false;
      bool OzETPQdZSz = false;
      bool okFWDZHUkM = false;
      bool KzOreHEuHw = false;
      bool ZHMkEemTkD = false;
      bool SdDApyRUWR = false;
      bool VxGQtPjLoI = false;
      bool MiRVZgYTRX = false;
      bool mmigtfuOCg = false;
      bool piYpZbAwqo = false;
      bool ubecqiLgaI = false;
      bool ZxCyeiOZVN = false;
      bool TUIIRcKbwx = false;
      bool gccccKIFpL = false;
      bool UOnsHrfZKq = false;
      bool NaZdVZSWLO = false;
      bool YjkcbwUZVT = false;
      bool ZIjKsFgOBZ = false;
      bool wkQEjFCyHC = false;
      bool rktaljdKRK = false;
      string QjWRFldCEI;
      string IpGioVSrYi;
      string BqEssNLfxl;
      string XBughxBFcU;
      string pMFeUQxWAK;
      string IumlOYedYr;
      string ZxESjHtZBr;
      string TNPErokYXb;
      string QoeldcNJRI;
      string RXfjtrHmuN;
      string WWVIqteisZ;
      string mFFwbkSSoH;
      string skHsZwgeJA;
      string gydKFsTWui;
      string xdPrULRjIJ;
      string ZoymTkObht;
      string NAZsrobuqh;
      string RuWFJOVPXO;
      string dxVzZrAppT;
      string dqnBUwEVAe;
      if(QjWRFldCEI == WWVIqteisZ){jWrardSrdE = true;}
      else if(WWVIqteisZ == QjWRFldCEI){ubecqiLgaI = true;}
      if(IpGioVSrYi == mFFwbkSSoH){OzETPQdZSz = true;}
      else if(mFFwbkSSoH == IpGioVSrYi){ZxCyeiOZVN = true;}
      if(BqEssNLfxl == skHsZwgeJA){okFWDZHUkM = true;}
      else if(skHsZwgeJA == BqEssNLfxl){TUIIRcKbwx = true;}
      if(XBughxBFcU == gydKFsTWui){KzOreHEuHw = true;}
      else if(gydKFsTWui == XBughxBFcU){gccccKIFpL = true;}
      if(pMFeUQxWAK == xdPrULRjIJ){ZHMkEemTkD = true;}
      else if(xdPrULRjIJ == pMFeUQxWAK){UOnsHrfZKq = true;}
      if(IumlOYedYr == ZoymTkObht){SdDApyRUWR = true;}
      else if(ZoymTkObht == IumlOYedYr){NaZdVZSWLO = true;}
      if(ZxESjHtZBr == NAZsrobuqh){VxGQtPjLoI = true;}
      else if(NAZsrobuqh == ZxESjHtZBr){YjkcbwUZVT = true;}
      if(TNPErokYXb == RuWFJOVPXO){MiRVZgYTRX = true;}
      if(QoeldcNJRI == dxVzZrAppT){mmigtfuOCg = true;}
      if(RXfjtrHmuN == dqnBUwEVAe){piYpZbAwqo = true;}
      while(RuWFJOVPXO == TNPErokYXb){ZIjKsFgOBZ = true;}
      while(dxVzZrAppT == dxVzZrAppT){wkQEjFCyHC = true;}
      while(dqnBUwEVAe == dqnBUwEVAe){rktaljdKRK = true;}
      if(jWrardSrdE == true){jWrardSrdE = false;}
      if(OzETPQdZSz == true){OzETPQdZSz = false;}
      if(okFWDZHUkM == true){okFWDZHUkM = false;}
      if(KzOreHEuHw == true){KzOreHEuHw = false;}
      if(ZHMkEemTkD == true){ZHMkEemTkD = false;}
      if(SdDApyRUWR == true){SdDApyRUWR = false;}
      if(VxGQtPjLoI == true){VxGQtPjLoI = false;}
      if(MiRVZgYTRX == true){MiRVZgYTRX = false;}
      if(mmigtfuOCg == true){mmigtfuOCg = false;}
      if(piYpZbAwqo == true){piYpZbAwqo = false;}
      if(ubecqiLgaI == true){ubecqiLgaI = false;}
      if(ZxCyeiOZVN == true){ZxCyeiOZVN = false;}
      if(TUIIRcKbwx == true){TUIIRcKbwx = false;}
      if(gccccKIFpL == true){gccccKIFpL = false;}
      if(UOnsHrfZKq == true){UOnsHrfZKq = false;}
      if(NaZdVZSWLO == true){NaZdVZSWLO = false;}
      if(YjkcbwUZVT == true){YjkcbwUZVT = false;}
      if(ZIjKsFgOBZ == true){ZIjKsFgOBZ = false;}
      if(wkQEjFCyHC == true){wkQEjFCyHC = false;}
      if(rktaljdKRK == true){rktaljdKRK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXOVUVIZDO
{ 
  void wLnFaomhcF()
  { 
      bool hiEPkEOeyy = false;
      bool MIMOizdfXA = false;
      bool NMTNmjEpTJ = false;
      bool GdLWIAZsZc = false;
      bool xwwdgYTBXH = false;
      bool LSiSrVOqcB = false;
      bool AXKoqixoGi = false;
      bool YkGuCQPofO = false;
      bool QCSLynusel = false;
      bool kiQYcYlHly = false;
      bool aduoiaMnPb = false;
      bool FYKNjxFzpD = false;
      bool nDKTxpTgRc = false;
      bool dIDhmmHdcX = false;
      bool aHcDfLXCne = false;
      bool TlQiKWSaqr = false;
      bool GeVlxxVcZx = false;
      bool obVSbgaHml = false;
      bool RQrmJrrTXP = false;
      bool TgljRwkpFi = false;
      string TIyAAJRpHI;
      string EkpelzDHQh;
      string VtliLrlTNj;
      string SIKNpNZAkM;
      string MMrRyXZCLG;
      string ZGJiuYWOnI;
      string WycXowabnX;
      string ZDWDUJCUjn;
      string SjIGJMybSQ;
      string qKLboOiUbC;
      string wxNmgWiGNl;
      string WBdzpmoWNc;
      string xzJWgOquNG;
      string ZhshqUWVYl;
      string cqNftpfMkC;
      string YMGyExmpFR;
      string enrGMoHwHU;
      string QTxbzGkdcq;
      string ieJLhMbuct;
      string hfPGHozHSF;
      if(TIyAAJRpHI == wxNmgWiGNl){hiEPkEOeyy = true;}
      else if(wxNmgWiGNl == TIyAAJRpHI){aduoiaMnPb = true;}
      if(EkpelzDHQh == WBdzpmoWNc){MIMOizdfXA = true;}
      else if(WBdzpmoWNc == EkpelzDHQh){FYKNjxFzpD = true;}
      if(VtliLrlTNj == xzJWgOquNG){NMTNmjEpTJ = true;}
      else if(xzJWgOquNG == VtliLrlTNj){nDKTxpTgRc = true;}
      if(SIKNpNZAkM == ZhshqUWVYl){GdLWIAZsZc = true;}
      else if(ZhshqUWVYl == SIKNpNZAkM){dIDhmmHdcX = true;}
      if(MMrRyXZCLG == cqNftpfMkC){xwwdgYTBXH = true;}
      else if(cqNftpfMkC == MMrRyXZCLG){aHcDfLXCne = true;}
      if(ZGJiuYWOnI == YMGyExmpFR){LSiSrVOqcB = true;}
      else if(YMGyExmpFR == ZGJiuYWOnI){TlQiKWSaqr = true;}
      if(WycXowabnX == enrGMoHwHU){AXKoqixoGi = true;}
      else if(enrGMoHwHU == WycXowabnX){GeVlxxVcZx = true;}
      if(ZDWDUJCUjn == QTxbzGkdcq){YkGuCQPofO = true;}
      if(SjIGJMybSQ == ieJLhMbuct){QCSLynusel = true;}
      if(qKLboOiUbC == hfPGHozHSF){kiQYcYlHly = true;}
      while(QTxbzGkdcq == ZDWDUJCUjn){obVSbgaHml = true;}
      while(ieJLhMbuct == ieJLhMbuct){RQrmJrrTXP = true;}
      while(hfPGHozHSF == hfPGHozHSF){TgljRwkpFi = true;}
      if(hiEPkEOeyy == true){hiEPkEOeyy = false;}
      if(MIMOizdfXA == true){MIMOizdfXA = false;}
      if(NMTNmjEpTJ == true){NMTNmjEpTJ = false;}
      if(GdLWIAZsZc == true){GdLWIAZsZc = false;}
      if(xwwdgYTBXH == true){xwwdgYTBXH = false;}
      if(LSiSrVOqcB == true){LSiSrVOqcB = false;}
      if(AXKoqixoGi == true){AXKoqixoGi = false;}
      if(YkGuCQPofO == true){YkGuCQPofO = false;}
      if(QCSLynusel == true){QCSLynusel = false;}
      if(kiQYcYlHly == true){kiQYcYlHly = false;}
      if(aduoiaMnPb == true){aduoiaMnPb = false;}
      if(FYKNjxFzpD == true){FYKNjxFzpD = false;}
      if(nDKTxpTgRc == true){nDKTxpTgRc = false;}
      if(dIDhmmHdcX == true){dIDhmmHdcX = false;}
      if(aHcDfLXCne == true){aHcDfLXCne = false;}
      if(TlQiKWSaqr == true){TlQiKWSaqr = false;}
      if(GeVlxxVcZx == true){GeVlxxVcZx = false;}
      if(obVSbgaHml == true){obVSbgaHml = false;}
      if(RQrmJrrTXP == true){RQrmJrrTXP = false;}
      if(TgljRwkpFi == true){TgljRwkpFi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EECVEDSQHT
{ 
  void GFYFLoLESp()
  { 
      bool NDShKSSYGn = false;
      bool UYJcIiagWw = false;
      bool jKTlkDWWqG = false;
      bool rABNpAOKlE = false;
      bool uBgkjkwCgC = false;
      bool uBOegDifwG = false;
      bool wuhAwUWwmI = false;
      bool UQtSBiciBz = false;
      bool HUpnKplWgl = false;
      bool QhNfHzSfoO = false;
      bool OzOYheGucx = false;
      bool ZAexybFsoF = false;
      bool iAOBqlCOKC = false;
      bool PwslkHFRFf = false;
      bool jpsiLPCPge = false;
      bool sYqjfNkNgu = false;
      bool brjagcGsLp = false;
      bool WmmJVrHeob = false;
      bool jlgfIqFJGX = false;
      bool WqkKDqGRCh = false;
      string kHwjhCggKP;
      string dZgmTeGYHr;
      string CkQbuyIFGU;
      string VmnbPWyCTS;
      string NRYsoKURts;
      string LshTmAqTnj;
      string taaosplEWw;
      string fEFoejLWmk;
      string cpLNJcFUoP;
      string feNjXlqiAz;
      string XQuxMGnsnD;
      string nUgDGEPMfQ;
      string kROGPBpUQs;
      string rcWmMLtNAC;
      string nLflbLxJcT;
      string VeCiNGBnhL;
      string PSctKKxsqu;
      string JCLcbZkceE;
      string DgrwXNZmZF;
      string JFfolVhkbQ;
      if(kHwjhCggKP == XQuxMGnsnD){NDShKSSYGn = true;}
      else if(XQuxMGnsnD == kHwjhCggKP){OzOYheGucx = true;}
      if(dZgmTeGYHr == nUgDGEPMfQ){UYJcIiagWw = true;}
      else if(nUgDGEPMfQ == dZgmTeGYHr){ZAexybFsoF = true;}
      if(CkQbuyIFGU == kROGPBpUQs){jKTlkDWWqG = true;}
      else if(kROGPBpUQs == CkQbuyIFGU){iAOBqlCOKC = true;}
      if(VmnbPWyCTS == rcWmMLtNAC){rABNpAOKlE = true;}
      else if(rcWmMLtNAC == VmnbPWyCTS){PwslkHFRFf = true;}
      if(NRYsoKURts == nLflbLxJcT){uBgkjkwCgC = true;}
      else if(nLflbLxJcT == NRYsoKURts){jpsiLPCPge = true;}
      if(LshTmAqTnj == VeCiNGBnhL){uBOegDifwG = true;}
      else if(VeCiNGBnhL == LshTmAqTnj){sYqjfNkNgu = true;}
      if(taaosplEWw == PSctKKxsqu){wuhAwUWwmI = true;}
      else if(PSctKKxsqu == taaosplEWw){brjagcGsLp = true;}
      if(fEFoejLWmk == JCLcbZkceE){UQtSBiciBz = true;}
      if(cpLNJcFUoP == DgrwXNZmZF){HUpnKplWgl = true;}
      if(feNjXlqiAz == JFfolVhkbQ){QhNfHzSfoO = true;}
      while(JCLcbZkceE == fEFoejLWmk){WmmJVrHeob = true;}
      while(DgrwXNZmZF == DgrwXNZmZF){jlgfIqFJGX = true;}
      while(JFfolVhkbQ == JFfolVhkbQ){WqkKDqGRCh = true;}
      if(NDShKSSYGn == true){NDShKSSYGn = false;}
      if(UYJcIiagWw == true){UYJcIiagWw = false;}
      if(jKTlkDWWqG == true){jKTlkDWWqG = false;}
      if(rABNpAOKlE == true){rABNpAOKlE = false;}
      if(uBgkjkwCgC == true){uBgkjkwCgC = false;}
      if(uBOegDifwG == true){uBOegDifwG = false;}
      if(wuhAwUWwmI == true){wuhAwUWwmI = false;}
      if(UQtSBiciBz == true){UQtSBiciBz = false;}
      if(HUpnKplWgl == true){HUpnKplWgl = false;}
      if(QhNfHzSfoO == true){QhNfHzSfoO = false;}
      if(OzOYheGucx == true){OzOYheGucx = false;}
      if(ZAexybFsoF == true){ZAexybFsoF = false;}
      if(iAOBqlCOKC == true){iAOBqlCOKC = false;}
      if(PwslkHFRFf == true){PwslkHFRFf = false;}
      if(jpsiLPCPge == true){jpsiLPCPge = false;}
      if(sYqjfNkNgu == true){sYqjfNkNgu = false;}
      if(brjagcGsLp == true){brjagcGsLp = false;}
      if(WmmJVrHeob == true){WmmJVrHeob = false;}
      if(jlgfIqFJGX == true){jlgfIqFJGX = false;}
      if(WqkKDqGRCh == true){WqkKDqGRCh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGNDCVBOXB
{ 
  void wDWweyAPBH()
  { 
      bool kBuqUASLUi = false;
      bool axDrutHcNu = false;
      bool MarIzEnkZM = false;
      bool hogzqTrzcU = false;
      bool zSxMTcxLYU = false;
      bool WcFGfJJmqQ = false;
      bool MglIBlQEBa = false;
      bool CIArutdenW = false;
      bool HbLEoEjZSg = false;
      bool KFHLIRfoKh = false;
      bool MrKxSNcMKk = false;
      bool fdzUJkUhTw = false;
      bool BpkTQxBojc = false;
      bool OnTFJOROka = false;
      bool bXPhAfFmBW = false;
      bool xyUOgWHpgV = false;
      bool MmcgWqKsKu = false;
      bool SGwrUdZDSj = false;
      bool qNmMfPSFYm = false;
      bool HagPNnthKJ = false;
      string HjonpDKDax;
      string oopeygPPEJ;
      string URzQebeozQ;
      string rjcZunWrLC;
      string gRylAFsIml;
      string uJBaHokYIO;
      string YUDJEFLQiK;
      string JXDBbDTMPY;
      string iVCNVihBSG;
      string DyiwcLNnhu;
      string tcYbbWFAzD;
      string VXIifCSpnU;
      string WKxcHLnHYP;
      string peeUeFxZky;
      string dhCOjeoAQa;
      string sXAMXiewUQ;
      string iyaiNqsnEZ;
      string FrFoqoHhrc;
      string VnpyVRdSwu;
      string ZAETPeGSBs;
      if(HjonpDKDax == tcYbbWFAzD){kBuqUASLUi = true;}
      else if(tcYbbWFAzD == HjonpDKDax){MrKxSNcMKk = true;}
      if(oopeygPPEJ == VXIifCSpnU){axDrutHcNu = true;}
      else if(VXIifCSpnU == oopeygPPEJ){fdzUJkUhTw = true;}
      if(URzQebeozQ == WKxcHLnHYP){MarIzEnkZM = true;}
      else if(WKxcHLnHYP == URzQebeozQ){BpkTQxBojc = true;}
      if(rjcZunWrLC == peeUeFxZky){hogzqTrzcU = true;}
      else if(peeUeFxZky == rjcZunWrLC){OnTFJOROka = true;}
      if(gRylAFsIml == dhCOjeoAQa){zSxMTcxLYU = true;}
      else if(dhCOjeoAQa == gRylAFsIml){bXPhAfFmBW = true;}
      if(uJBaHokYIO == sXAMXiewUQ){WcFGfJJmqQ = true;}
      else if(sXAMXiewUQ == uJBaHokYIO){xyUOgWHpgV = true;}
      if(YUDJEFLQiK == iyaiNqsnEZ){MglIBlQEBa = true;}
      else if(iyaiNqsnEZ == YUDJEFLQiK){MmcgWqKsKu = true;}
      if(JXDBbDTMPY == FrFoqoHhrc){CIArutdenW = true;}
      if(iVCNVihBSG == VnpyVRdSwu){HbLEoEjZSg = true;}
      if(DyiwcLNnhu == ZAETPeGSBs){KFHLIRfoKh = true;}
      while(FrFoqoHhrc == JXDBbDTMPY){SGwrUdZDSj = true;}
      while(VnpyVRdSwu == VnpyVRdSwu){qNmMfPSFYm = true;}
      while(ZAETPeGSBs == ZAETPeGSBs){HagPNnthKJ = true;}
      if(kBuqUASLUi == true){kBuqUASLUi = false;}
      if(axDrutHcNu == true){axDrutHcNu = false;}
      if(MarIzEnkZM == true){MarIzEnkZM = false;}
      if(hogzqTrzcU == true){hogzqTrzcU = false;}
      if(zSxMTcxLYU == true){zSxMTcxLYU = false;}
      if(WcFGfJJmqQ == true){WcFGfJJmqQ = false;}
      if(MglIBlQEBa == true){MglIBlQEBa = false;}
      if(CIArutdenW == true){CIArutdenW = false;}
      if(HbLEoEjZSg == true){HbLEoEjZSg = false;}
      if(KFHLIRfoKh == true){KFHLIRfoKh = false;}
      if(MrKxSNcMKk == true){MrKxSNcMKk = false;}
      if(fdzUJkUhTw == true){fdzUJkUhTw = false;}
      if(BpkTQxBojc == true){BpkTQxBojc = false;}
      if(OnTFJOROka == true){OnTFJOROka = false;}
      if(bXPhAfFmBW == true){bXPhAfFmBW = false;}
      if(xyUOgWHpgV == true){xyUOgWHpgV = false;}
      if(MmcgWqKsKu == true){MmcgWqKsKu = false;}
      if(SGwrUdZDSj == true){SGwrUdZDSj = false;}
      if(qNmMfPSFYm == true){qNmMfPSFYm = false;}
      if(HagPNnthKJ == true){HagPNnthKJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZANUGZWRA
{ 
  void wHOVnmLNAI()
  { 
      bool xDUucrlZJl = false;
      bool YXzymkbNyM = false;
      bool UziwoNPHuY = false;
      bool ihzTxAUiZl = false;
      bool yUkLHcTDni = false;
      bool aOkrHyTYFO = false;
      bool bedkCqYeAm = false;
      bool QsnMNANWnM = false;
      bool tMSMyTxGLz = false;
      bool fudLJTpAIQ = false;
      bool EoCBSgaXeH = false;
      bool jwjrUPLRli = false;
      bool tRSBHUPcCs = false;
      bool KNOXIFJQsQ = false;
      bool sYbEOiLkpt = false;
      bool IXNZWlVBtx = false;
      bool RyVkwWhLjP = false;
      bool FtYVoUpOlX = false;
      bool JelIkmzoBV = false;
      bool iIWuzuDpIr = false;
      string pfFAhVxUhr;
      string wFxKIjYHYP;
      string xGxeMDWLWM;
      string YTBlcBlmkF;
      string GTVqfWrUla;
      string BswYgjhane;
      string ykxUSbELhG;
      string ylWTIcjGyo;
      string KBZuKfWbFr;
      string TLyGGUWAYD;
      string SglfcPWcPD;
      string zbbzTwLBKl;
      string FcFpllnPMm;
      string GjguWcPtSu;
      string JsLBrqiylJ;
      string JUolxpbwsp;
      string aGQbxPtfcq;
      string gRiPbLQDxu;
      string DpdCdktuxf;
      string BSBbTDciEc;
      if(pfFAhVxUhr == SglfcPWcPD){xDUucrlZJl = true;}
      else if(SglfcPWcPD == pfFAhVxUhr){EoCBSgaXeH = true;}
      if(wFxKIjYHYP == zbbzTwLBKl){YXzymkbNyM = true;}
      else if(zbbzTwLBKl == wFxKIjYHYP){jwjrUPLRli = true;}
      if(xGxeMDWLWM == FcFpllnPMm){UziwoNPHuY = true;}
      else if(FcFpllnPMm == xGxeMDWLWM){tRSBHUPcCs = true;}
      if(YTBlcBlmkF == GjguWcPtSu){ihzTxAUiZl = true;}
      else if(GjguWcPtSu == YTBlcBlmkF){KNOXIFJQsQ = true;}
      if(GTVqfWrUla == JsLBrqiylJ){yUkLHcTDni = true;}
      else if(JsLBrqiylJ == GTVqfWrUla){sYbEOiLkpt = true;}
      if(BswYgjhane == JUolxpbwsp){aOkrHyTYFO = true;}
      else if(JUolxpbwsp == BswYgjhane){IXNZWlVBtx = true;}
      if(ykxUSbELhG == aGQbxPtfcq){bedkCqYeAm = true;}
      else if(aGQbxPtfcq == ykxUSbELhG){RyVkwWhLjP = true;}
      if(ylWTIcjGyo == gRiPbLQDxu){QsnMNANWnM = true;}
      if(KBZuKfWbFr == DpdCdktuxf){tMSMyTxGLz = true;}
      if(TLyGGUWAYD == BSBbTDciEc){fudLJTpAIQ = true;}
      while(gRiPbLQDxu == ylWTIcjGyo){FtYVoUpOlX = true;}
      while(DpdCdktuxf == DpdCdktuxf){JelIkmzoBV = true;}
      while(BSBbTDciEc == BSBbTDciEc){iIWuzuDpIr = true;}
      if(xDUucrlZJl == true){xDUucrlZJl = false;}
      if(YXzymkbNyM == true){YXzymkbNyM = false;}
      if(UziwoNPHuY == true){UziwoNPHuY = false;}
      if(ihzTxAUiZl == true){ihzTxAUiZl = false;}
      if(yUkLHcTDni == true){yUkLHcTDni = false;}
      if(aOkrHyTYFO == true){aOkrHyTYFO = false;}
      if(bedkCqYeAm == true){bedkCqYeAm = false;}
      if(QsnMNANWnM == true){QsnMNANWnM = false;}
      if(tMSMyTxGLz == true){tMSMyTxGLz = false;}
      if(fudLJTpAIQ == true){fudLJTpAIQ = false;}
      if(EoCBSgaXeH == true){EoCBSgaXeH = false;}
      if(jwjrUPLRli == true){jwjrUPLRli = false;}
      if(tRSBHUPcCs == true){tRSBHUPcCs = false;}
      if(KNOXIFJQsQ == true){KNOXIFJQsQ = false;}
      if(sYbEOiLkpt == true){sYbEOiLkpt = false;}
      if(IXNZWlVBtx == true){IXNZWlVBtx = false;}
      if(RyVkwWhLjP == true){RyVkwWhLjP = false;}
      if(FtYVoUpOlX == true){FtYVoUpOlX = false;}
      if(JelIkmzoBV == true){JelIkmzoBV = false;}
      if(iIWuzuDpIr == true){iIWuzuDpIr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWZAKAALRF
{ 
  void kqCyKEqcrG()
  { 
      bool xEorjpTWYR = false;
      bool dhjzrYrcQF = false;
      bool JpByIQtuyo = false;
      bool yKQdfKqdHy = false;
      bool ydUCJDNWYI = false;
      bool tGxsSHCpjT = false;
      bool wYYjTTQFSg = false;
      bool gNVSHfUznE = false;
      bool CWWouqMXLY = false;
      bool IAsnCZFkhp = false;
      bool lHEqafkell = false;
      bool lCCfQYCinb = false;
      bool GsttYgUhPh = false;
      bool aiRxRtReOO = false;
      bool GhlYmFxNWc = false;
      bool WVxFjsNJSt = false;
      bool LCPDLCkENW = false;
      bool HWUYVYHVGT = false;
      bool iHKlKElLNY = false;
      bool gIMUDDRhMj = false;
      string CIiLuaXjnX;
      string NHSkAOauPE;
      string tNCoxsBNZV;
      string XNrjpVJRTZ;
      string ibndkKVdVD;
      string VzAWonFtOC;
      string YKJSAzOiud;
      string FJapURZYEl;
      string XWrWzYNVtB;
      string QPCRAYSVck;
      string umiqxMXJBW;
      string OgobeCRlSb;
      string ksnsNoGJou;
      string yDuTpjnAYm;
      string ADTXmiZamy;
      string GgCAzCypdH;
      string FOTFXKkVlt;
      string OQMfbhYQGd;
      string PfWqoRAtTn;
      string lxWRhljOzb;
      if(CIiLuaXjnX == umiqxMXJBW){xEorjpTWYR = true;}
      else if(umiqxMXJBW == CIiLuaXjnX){lHEqafkell = true;}
      if(NHSkAOauPE == OgobeCRlSb){dhjzrYrcQF = true;}
      else if(OgobeCRlSb == NHSkAOauPE){lCCfQYCinb = true;}
      if(tNCoxsBNZV == ksnsNoGJou){JpByIQtuyo = true;}
      else if(ksnsNoGJou == tNCoxsBNZV){GsttYgUhPh = true;}
      if(XNrjpVJRTZ == yDuTpjnAYm){yKQdfKqdHy = true;}
      else if(yDuTpjnAYm == XNrjpVJRTZ){aiRxRtReOO = true;}
      if(ibndkKVdVD == ADTXmiZamy){ydUCJDNWYI = true;}
      else if(ADTXmiZamy == ibndkKVdVD){GhlYmFxNWc = true;}
      if(VzAWonFtOC == GgCAzCypdH){tGxsSHCpjT = true;}
      else if(GgCAzCypdH == VzAWonFtOC){WVxFjsNJSt = true;}
      if(YKJSAzOiud == FOTFXKkVlt){wYYjTTQFSg = true;}
      else if(FOTFXKkVlt == YKJSAzOiud){LCPDLCkENW = true;}
      if(FJapURZYEl == OQMfbhYQGd){gNVSHfUznE = true;}
      if(XWrWzYNVtB == PfWqoRAtTn){CWWouqMXLY = true;}
      if(QPCRAYSVck == lxWRhljOzb){IAsnCZFkhp = true;}
      while(OQMfbhYQGd == FJapURZYEl){HWUYVYHVGT = true;}
      while(PfWqoRAtTn == PfWqoRAtTn){iHKlKElLNY = true;}
      while(lxWRhljOzb == lxWRhljOzb){gIMUDDRhMj = true;}
      if(xEorjpTWYR == true){xEorjpTWYR = false;}
      if(dhjzrYrcQF == true){dhjzrYrcQF = false;}
      if(JpByIQtuyo == true){JpByIQtuyo = false;}
      if(yKQdfKqdHy == true){yKQdfKqdHy = false;}
      if(ydUCJDNWYI == true){ydUCJDNWYI = false;}
      if(tGxsSHCpjT == true){tGxsSHCpjT = false;}
      if(wYYjTTQFSg == true){wYYjTTQFSg = false;}
      if(gNVSHfUznE == true){gNVSHfUznE = false;}
      if(CWWouqMXLY == true){CWWouqMXLY = false;}
      if(IAsnCZFkhp == true){IAsnCZFkhp = false;}
      if(lHEqafkell == true){lHEqafkell = false;}
      if(lCCfQYCinb == true){lCCfQYCinb = false;}
      if(GsttYgUhPh == true){GsttYgUhPh = false;}
      if(aiRxRtReOO == true){aiRxRtReOO = false;}
      if(GhlYmFxNWc == true){GhlYmFxNWc = false;}
      if(WVxFjsNJSt == true){WVxFjsNJSt = false;}
      if(LCPDLCkENW == true){LCPDLCkENW = false;}
      if(HWUYVYHVGT == true){HWUYVYHVGT = false;}
      if(iHKlKElLNY == true){iHKlKElLNY = false;}
      if(gIMUDDRhMj == true){gIMUDDRhMj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLKHVTDVXE
{ 
  void jOuKshqgxF()
  { 
      bool CFyHxPbleO = false;
      bool znPIOyLoZU = false;
      bool AoOSuyJYED = false;
      bool cVMhjfcMmP = false;
      bool lLPxzranLX = false;
      bool mITmlNpeLy = false;
      bool GDgbkdahXh = false;
      bool UzBJioYRSD = false;
      bool WUMgPUBZuW = false;
      bool pxAnJidmMV = false;
      bool RrQcCmGJEx = false;
      bool nYLIbkpALP = false;
      bool bBmBrXyNAz = false;
      bool KkFxkdEjdc = false;
      bool OqUxhRkrMX = false;
      bool rcawsPFOke = false;
      bool nrJEmDTOWx = false;
      bool gGViBjfpTa = false;
      bool lGBbGgJIDU = false;
      bool YoyznWhPKe = false;
      string eCJREuRJMy;
      string HIQBbJKqTE;
      string HYzprWJFqX;
      string DrliBCeVkq;
      string gRaICAGpsx;
      string HpYePGDSYh;
      string kLSotPVhzY;
      string eoGcXoxpnr;
      string PSMsPNSGSt;
      string zLwCFUzlNl;
      string dYpUSSiwHZ;
      string JMdfSSyYYf;
      string wOOFYSrDWC;
      string pLcCOpbrZx;
      string eVzsklgQjm;
      string WaNgoOJkuA;
      string afYFjyjbRb;
      string pGyaBaPVUm;
      string kbTjfOxuMz;
      string gqxZWyxsIm;
      if(eCJREuRJMy == dYpUSSiwHZ){CFyHxPbleO = true;}
      else if(dYpUSSiwHZ == eCJREuRJMy){RrQcCmGJEx = true;}
      if(HIQBbJKqTE == JMdfSSyYYf){znPIOyLoZU = true;}
      else if(JMdfSSyYYf == HIQBbJKqTE){nYLIbkpALP = true;}
      if(HYzprWJFqX == wOOFYSrDWC){AoOSuyJYED = true;}
      else if(wOOFYSrDWC == HYzprWJFqX){bBmBrXyNAz = true;}
      if(DrliBCeVkq == pLcCOpbrZx){cVMhjfcMmP = true;}
      else if(pLcCOpbrZx == DrliBCeVkq){KkFxkdEjdc = true;}
      if(gRaICAGpsx == eVzsklgQjm){lLPxzranLX = true;}
      else if(eVzsklgQjm == gRaICAGpsx){OqUxhRkrMX = true;}
      if(HpYePGDSYh == WaNgoOJkuA){mITmlNpeLy = true;}
      else if(WaNgoOJkuA == HpYePGDSYh){rcawsPFOke = true;}
      if(kLSotPVhzY == afYFjyjbRb){GDgbkdahXh = true;}
      else if(afYFjyjbRb == kLSotPVhzY){nrJEmDTOWx = true;}
      if(eoGcXoxpnr == pGyaBaPVUm){UzBJioYRSD = true;}
      if(PSMsPNSGSt == kbTjfOxuMz){WUMgPUBZuW = true;}
      if(zLwCFUzlNl == gqxZWyxsIm){pxAnJidmMV = true;}
      while(pGyaBaPVUm == eoGcXoxpnr){gGViBjfpTa = true;}
      while(kbTjfOxuMz == kbTjfOxuMz){lGBbGgJIDU = true;}
      while(gqxZWyxsIm == gqxZWyxsIm){YoyznWhPKe = true;}
      if(CFyHxPbleO == true){CFyHxPbleO = false;}
      if(znPIOyLoZU == true){znPIOyLoZU = false;}
      if(AoOSuyJYED == true){AoOSuyJYED = false;}
      if(cVMhjfcMmP == true){cVMhjfcMmP = false;}
      if(lLPxzranLX == true){lLPxzranLX = false;}
      if(mITmlNpeLy == true){mITmlNpeLy = false;}
      if(GDgbkdahXh == true){GDgbkdahXh = false;}
      if(UzBJioYRSD == true){UzBJioYRSD = false;}
      if(WUMgPUBZuW == true){WUMgPUBZuW = false;}
      if(pxAnJidmMV == true){pxAnJidmMV = false;}
      if(RrQcCmGJEx == true){RrQcCmGJEx = false;}
      if(nYLIbkpALP == true){nYLIbkpALP = false;}
      if(bBmBrXyNAz == true){bBmBrXyNAz = false;}
      if(KkFxkdEjdc == true){KkFxkdEjdc = false;}
      if(OqUxhRkrMX == true){OqUxhRkrMX = false;}
      if(rcawsPFOke == true){rcawsPFOke = false;}
      if(nrJEmDTOWx == true){nrJEmDTOWx = false;}
      if(gGViBjfpTa == true){gGViBjfpTa = false;}
      if(lGBbGgJIDU == true){lGBbGgJIDU = false;}
      if(YoyznWhPKe == true){YoyznWhPKe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QUNPCBDZHZ
{ 
  void xgkRtumKUu()
  { 
      bool qQKWJHOmQf = false;
      bool uzLXAMAjhr = false;
      bool OyuMzjOZrg = false;
      bool htoLWkVofY = false;
      bool VqETrbuuKd = false;
      bool bPWKFrUyWY = false;
      bool snujyAJzAP = false;
      bool pLEJVWtaTX = false;
      bool oTONERXeGe = false;
      bool PXRGegwTVr = false;
      bool RuuunPLMoh = false;
      bool yteyjZYgeg = false;
      bool besUzStxdn = false;
      bool aZFaFsYTZo = false;
      bool FKpXgVrSVF = false;
      bool IOooPmBZuU = false;
      bool VNiAHXnDsp = false;
      bool AFHpaRoUnc = false;
      bool ZaaXfLkPLS = false;
      bool qyXESrboQI = false;
      string SqNKnHhMrt;
      string rEKEPLOVEb;
      string RcEMeMdegz;
      string jqitzOYaTV;
      string eejiYieqND;
      string aYzfAolAea;
      string dDerJAVQEB;
      string mnCiwlsVnw;
      string glQdXLqCsJ;
      string bYurrbAqYX;
      string NOmLPmWQiN;
      string wQMitqlATy;
      string ISWtZNsJpU;
      string kCwPiSzENk;
      string oaSeNLMLyB;
      string oAWaOtqrlC;
      string tMZOctUwAa;
      string qgliJhzrfO;
      string BgLofkeVAn;
      string aHSLqcAECT;
      if(SqNKnHhMrt == NOmLPmWQiN){qQKWJHOmQf = true;}
      else if(NOmLPmWQiN == SqNKnHhMrt){RuuunPLMoh = true;}
      if(rEKEPLOVEb == wQMitqlATy){uzLXAMAjhr = true;}
      else if(wQMitqlATy == rEKEPLOVEb){yteyjZYgeg = true;}
      if(RcEMeMdegz == ISWtZNsJpU){OyuMzjOZrg = true;}
      else if(ISWtZNsJpU == RcEMeMdegz){besUzStxdn = true;}
      if(jqitzOYaTV == kCwPiSzENk){htoLWkVofY = true;}
      else if(kCwPiSzENk == jqitzOYaTV){aZFaFsYTZo = true;}
      if(eejiYieqND == oaSeNLMLyB){VqETrbuuKd = true;}
      else if(oaSeNLMLyB == eejiYieqND){FKpXgVrSVF = true;}
      if(aYzfAolAea == oAWaOtqrlC){bPWKFrUyWY = true;}
      else if(oAWaOtqrlC == aYzfAolAea){IOooPmBZuU = true;}
      if(dDerJAVQEB == tMZOctUwAa){snujyAJzAP = true;}
      else if(tMZOctUwAa == dDerJAVQEB){VNiAHXnDsp = true;}
      if(mnCiwlsVnw == qgliJhzrfO){pLEJVWtaTX = true;}
      if(glQdXLqCsJ == BgLofkeVAn){oTONERXeGe = true;}
      if(bYurrbAqYX == aHSLqcAECT){PXRGegwTVr = true;}
      while(qgliJhzrfO == mnCiwlsVnw){AFHpaRoUnc = true;}
      while(BgLofkeVAn == BgLofkeVAn){ZaaXfLkPLS = true;}
      while(aHSLqcAECT == aHSLqcAECT){qyXESrboQI = true;}
      if(qQKWJHOmQf == true){qQKWJHOmQf = false;}
      if(uzLXAMAjhr == true){uzLXAMAjhr = false;}
      if(OyuMzjOZrg == true){OyuMzjOZrg = false;}
      if(htoLWkVofY == true){htoLWkVofY = false;}
      if(VqETrbuuKd == true){VqETrbuuKd = false;}
      if(bPWKFrUyWY == true){bPWKFrUyWY = false;}
      if(snujyAJzAP == true){snujyAJzAP = false;}
      if(pLEJVWtaTX == true){pLEJVWtaTX = false;}
      if(oTONERXeGe == true){oTONERXeGe = false;}
      if(PXRGegwTVr == true){PXRGegwTVr = false;}
      if(RuuunPLMoh == true){RuuunPLMoh = false;}
      if(yteyjZYgeg == true){yteyjZYgeg = false;}
      if(besUzStxdn == true){besUzStxdn = false;}
      if(aZFaFsYTZo == true){aZFaFsYTZo = false;}
      if(FKpXgVrSVF == true){FKpXgVrSVF = false;}
      if(IOooPmBZuU == true){IOooPmBZuU = false;}
      if(VNiAHXnDsp == true){VNiAHXnDsp = false;}
      if(AFHpaRoUnc == true){AFHpaRoUnc = false;}
      if(ZaaXfLkPLS == true){ZaaXfLkPLS = false;}
      if(qyXESrboQI == true){qyXESrboQI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUFBDTXMTP
{ 
  void sabHhkLGAS()
  { 
      bool cLfiTuiwrA = false;
      bool CGSjSBfYuE = false;
      bool xYRrSaGEJQ = false;
      bool EjAnhOenSs = false;
      bool QsGbskYkPJ = false;
      bool YrQquEsmPr = false;
      bool ndlawSFdCE = false;
      bool VqGCmDSpzh = false;
      bool CVoArMSJsd = false;
      bool UrYZElGefZ = false;
      bool ethKmglODq = false;
      bool kDnhoSnlii = false;
      bool zwkYjdSfxA = false;
      bool wmKZCIndMK = false;
      bool aEFBrQDpkl = false;
      bool yUwwZiJIaI = false;
      bool NGRCtxsNeg = false;
      bool eJZXIupifS = false;
      bool acuKCbqNzT = false;
      bool zeDEwUlCGt = false;
      string DJYwOUwTHd;
      string gTabayLOfS;
      string EpQHYPGcFu;
      string RTcFndRayK;
      string lyXHjjUBEF;
      string clFffNsRXz;
      string OSOMMNqVnw;
      string fjQUgFSIWn;
      string tEYASeNwZa;
      string kADzwSjLuW;
      string szNHYsVjzZ;
      string tjtiFJtOtg;
      string ztwNLffRYN;
      string VHMAutqRaY;
      string JcxzfAFUsl;
      string YVROWzDAus;
      string NELkDmWtnK;
      string ScmUWVwwgK;
      string ZLXlozpycu;
      string qqVhLFRMur;
      if(DJYwOUwTHd == szNHYsVjzZ){cLfiTuiwrA = true;}
      else if(szNHYsVjzZ == DJYwOUwTHd){ethKmglODq = true;}
      if(gTabayLOfS == tjtiFJtOtg){CGSjSBfYuE = true;}
      else if(tjtiFJtOtg == gTabayLOfS){kDnhoSnlii = true;}
      if(EpQHYPGcFu == ztwNLffRYN){xYRrSaGEJQ = true;}
      else if(ztwNLffRYN == EpQHYPGcFu){zwkYjdSfxA = true;}
      if(RTcFndRayK == VHMAutqRaY){EjAnhOenSs = true;}
      else if(VHMAutqRaY == RTcFndRayK){wmKZCIndMK = true;}
      if(lyXHjjUBEF == JcxzfAFUsl){QsGbskYkPJ = true;}
      else if(JcxzfAFUsl == lyXHjjUBEF){aEFBrQDpkl = true;}
      if(clFffNsRXz == YVROWzDAus){YrQquEsmPr = true;}
      else if(YVROWzDAus == clFffNsRXz){yUwwZiJIaI = true;}
      if(OSOMMNqVnw == NELkDmWtnK){ndlawSFdCE = true;}
      else if(NELkDmWtnK == OSOMMNqVnw){NGRCtxsNeg = true;}
      if(fjQUgFSIWn == ScmUWVwwgK){VqGCmDSpzh = true;}
      if(tEYASeNwZa == ZLXlozpycu){CVoArMSJsd = true;}
      if(kADzwSjLuW == qqVhLFRMur){UrYZElGefZ = true;}
      while(ScmUWVwwgK == fjQUgFSIWn){eJZXIupifS = true;}
      while(ZLXlozpycu == ZLXlozpycu){acuKCbqNzT = true;}
      while(qqVhLFRMur == qqVhLFRMur){zeDEwUlCGt = true;}
      if(cLfiTuiwrA == true){cLfiTuiwrA = false;}
      if(CGSjSBfYuE == true){CGSjSBfYuE = false;}
      if(xYRrSaGEJQ == true){xYRrSaGEJQ = false;}
      if(EjAnhOenSs == true){EjAnhOenSs = false;}
      if(QsGbskYkPJ == true){QsGbskYkPJ = false;}
      if(YrQquEsmPr == true){YrQquEsmPr = false;}
      if(ndlawSFdCE == true){ndlawSFdCE = false;}
      if(VqGCmDSpzh == true){VqGCmDSpzh = false;}
      if(CVoArMSJsd == true){CVoArMSJsd = false;}
      if(UrYZElGefZ == true){UrYZElGefZ = false;}
      if(ethKmglODq == true){ethKmglODq = false;}
      if(kDnhoSnlii == true){kDnhoSnlii = false;}
      if(zwkYjdSfxA == true){zwkYjdSfxA = false;}
      if(wmKZCIndMK == true){wmKZCIndMK = false;}
      if(aEFBrQDpkl == true){aEFBrQDpkl = false;}
      if(yUwwZiJIaI == true){yUwwZiJIaI = false;}
      if(NGRCtxsNeg == true){NGRCtxsNeg = false;}
      if(eJZXIupifS == true){eJZXIupifS = false;}
      if(acuKCbqNzT == true){acuKCbqNzT = false;}
      if(zeDEwUlCGt == true){zeDEwUlCGt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTNGQSYORR
{ 
  void VNDZsZemuk()
  { 
      bool tSnpzHgJpe = false;
      bool XMsFrJYDNC = false;
      bool ywhpyNGqWh = false;
      bool yXyMoHeRfI = false;
      bool uTesRsUAMO = false;
      bool HJbIHxkyrl = false;
      bool BpmIfAOgPk = false;
      bool eGXEGdRoXE = false;
      bool sFdIZowpFr = false;
      bool WfZtGFgVMR = false;
      bool enkbiAkXCc = false;
      bool fwZmswLdiq = false;
      bool DYaWNygdxA = false;
      bool xubGZETCYY = false;
      bool DYmcMZGmAK = false;
      bool tCmVNGMNNk = false;
      bool THZBfkUTMn = false;
      bool cIFKmekyKm = false;
      bool rsclFtHFrT = false;
      bool rFnnEuylxa = false;
      string AjsjWqNdXD;
      string SfxlSYEoNh;
      string cDcKeryXLG;
      string WVOWpOcjHY;
      string STSQwiuJpQ;
      string lTfeuwGiEd;
      string spSQgxQauE;
      string uTgnOIkMNu;
      string xohuTCojbt;
      string HtecfcBBjz;
      string SUNlUSmrPl;
      string LtUJgDIWwe;
      string IgyBwBoEIl;
      string HibObbauZB;
      string PwTohMZVub;
      string UdFFplVMoT;
      string chjdebSGgE;
      string bMxuOLNISj;
      string aTIfQcdVXp;
      string GOGFXgMoKF;
      if(AjsjWqNdXD == SUNlUSmrPl){tSnpzHgJpe = true;}
      else if(SUNlUSmrPl == AjsjWqNdXD){enkbiAkXCc = true;}
      if(SfxlSYEoNh == LtUJgDIWwe){XMsFrJYDNC = true;}
      else if(LtUJgDIWwe == SfxlSYEoNh){fwZmswLdiq = true;}
      if(cDcKeryXLG == IgyBwBoEIl){ywhpyNGqWh = true;}
      else if(IgyBwBoEIl == cDcKeryXLG){DYaWNygdxA = true;}
      if(WVOWpOcjHY == HibObbauZB){yXyMoHeRfI = true;}
      else if(HibObbauZB == WVOWpOcjHY){xubGZETCYY = true;}
      if(STSQwiuJpQ == PwTohMZVub){uTesRsUAMO = true;}
      else if(PwTohMZVub == STSQwiuJpQ){DYmcMZGmAK = true;}
      if(lTfeuwGiEd == UdFFplVMoT){HJbIHxkyrl = true;}
      else if(UdFFplVMoT == lTfeuwGiEd){tCmVNGMNNk = true;}
      if(spSQgxQauE == chjdebSGgE){BpmIfAOgPk = true;}
      else if(chjdebSGgE == spSQgxQauE){THZBfkUTMn = true;}
      if(uTgnOIkMNu == bMxuOLNISj){eGXEGdRoXE = true;}
      if(xohuTCojbt == aTIfQcdVXp){sFdIZowpFr = true;}
      if(HtecfcBBjz == GOGFXgMoKF){WfZtGFgVMR = true;}
      while(bMxuOLNISj == uTgnOIkMNu){cIFKmekyKm = true;}
      while(aTIfQcdVXp == aTIfQcdVXp){rsclFtHFrT = true;}
      while(GOGFXgMoKF == GOGFXgMoKF){rFnnEuylxa = true;}
      if(tSnpzHgJpe == true){tSnpzHgJpe = false;}
      if(XMsFrJYDNC == true){XMsFrJYDNC = false;}
      if(ywhpyNGqWh == true){ywhpyNGqWh = false;}
      if(yXyMoHeRfI == true){yXyMoHeRfI = false;}
      if(uTesRsUAMO == true){uTesRsUAMO = false;}
      if(HJbIHxkyrl == true){HJbIHxkyrl = false;}
      if(BpmIfAOgPk == true){BpmIfAOgPk = false;}
      if(eGXEGdRoXE == true){eGXEGdRoXE = false;}
      if(sFdIZowpFr == true){sFdIZowpFr = false;}
      if(WfZtGFgVMR == true){WfZtGFgVMR = false;}
      if(enkbiAkXCc == true){enkbiAkXCc = false;}
      if(fwZmswLdiq == true){fwZmswLdiq = false;}
      if(DYaWNygdxA == true){DYaWNygdxA = false;}
      if(xubGZETCYY == true){xubGZETCYY = false;}
      if(DYmcMZGmAK == true){DYmcMZGmAK = false;}
      if(tCmVNGMNNk == true){tCmVNGMNNk = false;}
      if(THZBfkUTMn == true){THZBfkUTMn = false;}
      if(cIFKmekyKm == true){cIFKmekyKm = false;}
      if(rsclFtHFrT == true){rsclFtHFrT = false;}
      if(rFnnEuylxa == true){rFnnEuylxa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAXTXLBAZH
{ 
  void nkgAcDenDs()
  { 
      bool GywABEEaTo = false;
      bool yBbWTxhNnJ = false;
      bool WELQbQaaZf = false;
      bool VdhOqnWcXP = false;
      bool xriUzbWklx = false;
      bool dfiWfCmfYk = false;
      bool cdAmSUTMff = false;
      bool aEpXLeVqRz = false;
      bool soncCpuKio = false;
      bool BpEmlTquCe = false;
      bool IKFGVYoLKB = false;
      bool guOZqnoXkb = false;
      bool ZJcpejACkr = false;
      bool mZnmqhihHc = false;
      bool AizgIFbeuy = false;
      bool dSJZEygPak = false;
      bool YmaRNGHbiI = false;
      bool EGQIapJwhZ = false;
      bool IVHlOTQOhr = false;
      bool BTHVENIgSB = false;
      string KCcguZQXAo;
      string RAFIkQXNyp;
      string aLucneRoAK;
      string HHXKxpESWg;
      string dFTHLIPRcY;
      string BmubUyHAsP;
      string HbWphJbuLt;
      string LEqQLVrmQe;
      string OzMbITMupz;
      string hEZGZChcZC;
      string gUGhNwweQy;
      string FUjNAIOugO;
      string xfFLMGejqI;
      string nPNOytseNL;
      string WgeqsNTLGQ;
      string nlwKEAPtVG;
      string RLnHKpGVOF;
      string PjhUqPBNSy;
      string lTdZTBSCJy;
      string dyIGtLsWfD;
      if(KCcguZQXAo == gUGhNwweQy){GywABEEaTo = true;}
      else if(gUGhNwweQy == KCcguZQXAo){IKFGVYoLKB = true;}
      if(RAFIkQXNyp == FUjNAIOugO){yBbWTxhNnJ = true;}
      else if(FUjNAIOugO == RAFIkQXNyp){guOZqnoXkb = true;}
      if(aLucneRoAK == xfFLMGejqI){WELQbQaaZf = true;}
      else if(xfFLMGejqI == aLucneRoAK){ZJcpejACkr = true;}
      if(HHXKxpESWg == nPNOytseNL){VdhOqnWcXP = true;}
      else if(nPNOytseNL == HHXKxpESWg){mZnmqhihHc = true;}
      if(dFTHLIPRcY == WgeqsNTLGQ){xriUzbWklx = true;}
      else if(WgeqsNTLGQ == dFTHLIPRcY){AizgIFbeuy = true;}
      if(BmubUyHAsP == nlwKEAPtVG){dfiWfCmfYk = true;}
      else if(nlwKEAPtVG == BmubUyHAsP){dSJZEygPak = true;}
      if(HbWphJbuLt == RLnHKpGVOF){cdAmSUTMff = true;}
      else if(RLnHKpGVOF == HbWphJbuLt){YmaRNGHbiI = true;}
      if(LEqQLVrmQe == PjhUqPBNSy){aEpXLeVqRz = true;}
      if(OzMbITMupz == lTdZTBSCJy){soncCpuKio = true;}
      if(hEZGZChcZC == dyIGtLsWfD){BpEmlTquCe = true;}
      while(PjhUqPBNSy == LEqQLVrmQe){EGQIapJwhZ = true;}
      while(lTdZTBSCJy == lTdZTBSCJy){IVHlOTQOhr = true;}
      while(dyIGtLsWfD == dyIGtLsWfD){BTHVENIgSB = true;}
      if(GywABEEaTo == true){GywABEEaTo = false;}
      if(yBbWTxhNnJ == true){yBbWTxhNnJ = false;}
      if(WELQbQaaZf == true){WELQbQaaZf = false;}
      if(VdhOqnWcXP == true){VdhOqnWcXP = false;}
      if(xriUzbWklx == true){xriUzbWklx = false;}
      if(dfiWfCmfYk == true){dfiWfCmfYk = false;}
      if(cdAmSUTMff == true){cdAmSUTMff = false;}
      if(aEpXLeVqRz == true){aEpXLeVqRz = false;}
      if(soncCpuKio == true){soncCpuKio = false;}
      if(BpEmlTquCe == true){BpEmlTquCe = false;}
      if(IKFGVYoLKB == true){IKFGVYoLKB = false;}
      if(guOZqnoXkb == true){guOZqnoXkb = false;}
      if(ZJcpejACkr == true){ZJcpejACkr = false;}
      if(mZnmqhihHc == true){mZnmqhihHc = false;}
      if(AizgIFbeuy == true){AizgIFbeuy = false;}
      if(dSJZEygPak == true){dSJZEygPak = false;}
      if(YmaRNGHbiI == true){YmaRNGHbiI = false;}
      if(EGQIapJwhZ == true){EGQIapJwhZ = false;}
      if(IVHlOTQOhr == true){IVHlOTQOhr = false;}
      if(BTHVENIgSB == true){BTHVENIgSB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPRBPIMUHU
{ 
  void LiBLADCDOf()
  { 
      bool zxNmePHBoW = false;
      bool orrSAhKqbM = false;
      bool CBqRATCdHt = false;
      bool ueRPaaKCqx = false;
      bool mhrWNwXgMR = false;
      bool PddWexGwlL = false;
      bool McttbJZcqY = false;
      bool WIAeZTITDE = false;
      bool wURoeQBujc = false;
      bool UOPejJmxuD = false;
      bool VtpmtHczwK = false;
      bool nmrhOrLEPK = false;
      bool IerOEIrVtP = false;
      bool gLYAiCeduX = false;
      bool nCyZngVhQr = false;
      bool xigktqBbil = false;
      bool OHEgdcNrzM = false;
      bool MgJrVGfSZW = false;
      bool lKEBRxdnFq = false;
      bool ADuIIfxRuL = false;
      string GGheqfyHBU;
      string LaCCtuGUys;
      string zOktsudKJV;
      string gacQodnRyG;
      string BbBpYGYSRo;
      string BnqMYqUmkw;
      string BnyfmjykNQ;
      string HnVqrWNuVl;
      string WLsTTsjQrx;
      string IAgCFMcUDn;
      string ImFAgNSzTB;
      string dZRyYpudMt;
      string AhrPIHHSle;
      string srqgdiFrmF;
      string ZjwqShhhcP;
      string RzIJmatorZ;
      string GANoHlijUp;
      string jCqGTQlBwZ;
      string YYoVMtjhsC;
      string oPAMzZVGig;
      if(GGheqfyHBU == ImFAgNSzTB){zxNmePHBoW = true;}
      else if(ImFAgNSzTB == GGheqfyHBU){VtpmtHczwK = true;}
      if(LaCCtuGUys == dZRyYpudMt){orrSAhKqbM = true;}
      else if(dZRyYpudMt == LaCCtuGUys){nmrhOrLEPK = true;}
      if(zOktsudKJV == AhrPIHHSle){CBqRATCdHt = true;}
      else if(AhrPIHHSle == zOktsudKJV){IerOEIrVtP = true;}
      if(gacQodnRyG == srqgdiFrmF){ueRPaaKCqx = true;}
      else if(srqgdiFrmF == gacQodnRyG){gLYAiCeduX = true;}
      if(BbBpYGYSRo == ZjwqShhhcP){mhrWNwXgMR = true;}
      else if(ZjwqShhhcP == BbBpYGYSRo){nCyZngVhQr = true;}
      if(BnqMYqUmkw == RzIJmatorZ){PddWexGwlL = true;}
      else if(RzIJmatorZ == BnqMYqUmkw){xigktqBbil = true;}
      if(BnyfmjykNQ == GANoHlijUp){McttbJZcqY = true;}
      else if(GANoHlijUp == BnyfmjykNQ){OHEgdcNrzM = true;}
      if(HnVqrWNuVl == jCqGTQlBwZ){WIAeZTITDE = true;}
      if(WLsTTsjQrx == YYoVMtjhsC){wURoeQBujc = true;}
      if(IAgCFMcUDn == oPAMzZVGig){UOPejJmxuD = true;}
      while(jCqGTQlBwZ == HnVqrWNuVl){MgJrVGfSZW = true;}
      while(YYoVMtjhsC == YYoVMtjhsC){lKEBRxdnFq = true;}
      while(oPAMzZVGig == oPAMzZVGig){ADuIIfxRuL = true;}
      if(zxNmePHBoW == true){zxNmePHBoW = false;}
      if(orrSAhKqbM == true){orrSAhKqbM = false;}
      if(CBqRATCdHt == true){CBqRATCdHt = false;}
      if(ueRPaaKCqx == true){ueRPaaKCqx = false;}
      if(mhrWNwXgMR == true){mhrWNwXgMR = false;}
      if(PddWexGwlL == true){PddWexGwlL = false;}
      if(McttbJZcqY == true){McttbJZcqY = false;}
      if(WIAeZTITDE == true){WIAeZTITDE = false;}
      if(wURoeQBujc == true){wURoeQBujc = false;}
      if(UOPejJmxuD == true){UOPejJmxuD = false;}
      if(VtpmtHczwK == true){VtpmtHczwK = false;}
      if(nmrhOrLEPK == true){nmrhOrLEPK = false;}
      if(IerOEIrVtP == true){IerOEIrVtP = false;}
      if(gLYAiCeduX == true){gLYAiCeduX = false;}
      if(nCyZngVhQr == true){nCyZngVhQr = false;}
      if(xigktqBbil == true){xigktqBbil = false;}
      if(OHEgdcNrzM == true){OHEgdcNrzM = false;}
      if(MgJrVGfSZW == true){MgJrVGfSZW = false;}
      if(lKEBRxdnFq == true){lKEBRxdnFq = false;}
      if(ADuIIfxRuL == true){ADuIIfxRuL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRVRYJBBEH
{ 
  void KETJcASLYC()
  { 
      bool WxPoqcWlcH = false;
      bool DWoDVeTeUj = false;
      bool maBSDxfoTW = false;
      bool WYSjWymosm = false;
      bool BzesZmGfHl = false;
      bool BigOHuwwls = false;
      bool wgRFkdDFgW = false;
      bool relghnwHsP = false;
      bool qzhhVnrEcb = false;
      bool CpCzpUgYIu = false;
      bool jAzjsWwzfS = false;
      bool ynCVCwzjjw = false;
      bool lycEUBbmqN = false;
      bool GXyyfpzxoz = false;
      bool rrYJcNmgws = false;
      bool UxnMIkXuPq = false;
      bool uJIRMapEpM = false;
      bool xBukEtZTaG = false;
      bool OupxrJikou = false;
      bool REgxDhiGxC = false;
      string PZqbDBcmFc;
      string BOUKMspfLX;
      string oLApceFyQW;
      string UVXQHsyNlr;
      string WYromfRVRI;
      string ZXFsmDYAzX;
      string ueVhHepDCT;
      string tctTAQTLCw;
      string MjfIwwQddE;
      string TyONxrCJgI;
      string pOSxNxdlrW;
      string jNxCLKyNkL;
      string OLZyAwOfWI;
      string NKdtGyQhtz;
      string SdkHTGALCl;
      string soXVsdnTxR;
      string hxPjIZiCwM;
      string tQSkrkaRdt;
      string wCdjPYlIBc;
      string JwjcRUNByt;
      if(PZqbDBcmFc == pOSxNxdlrW){WxPoqcWlcH = true;}
      else if(pOSxNxdlrW == PZqbDBcmFc){jAzjsWwzfS = true;}
      if(BOUKMspfLX == jNxCLKyNkL){DWoDVeTeUj = true;}
      else if(jNxCLKyNkL == BOUKMspfLX){ynCVCwzjjw = true;}
      if(oLApceFyQW == OLZyAwOfWI){maBSDxfoTW = true;}
      else if(OLZyAwOfWI == oLApceFyQW){lycEUBbmqN = true;}
      if(UVXQHsyNlr == NKdtGyQhtz){WYSjWymosm = true;}
      else if(NKdtGyQhtz == UVXQHsyNlr){GXyyfpzxoz = true;}
      if(WYromfRVRI == SdkHTGALCl){BzesZmGfHl = true;}
      else if(SdkHTGALCl == WYromfRVRI){rrYJcNmgws = true;}
      if(ZXFsmDYAzX == soXVsdnTxR){BigOHuwwls = true;}
      else if(soXVsdnTxR == ZXFsmDYAzX){UxnMIkXuPq = true;}
      if(ueVhHepDCT == hxPjIZiCwM){wgRFkdDFgW = true;}
      else if(hxPjIZiCwM == ueVhHepDCT){uJIRMapEpM = true;}
      if(tctTAQTLCw == tQSkrkaRdt){relghnwHsP = true;}
      if(MjfIwwQddE == wCdjPYlIBc){qzhhVnrEcb = true;}
      if(TyONxrCJgI == JwjcRUNByt){CpCzpUgYIu = true;}
      while(tQSkrkaRdt == tctTAQTLCw){xBukEtZTaG = true;}
      while(wCdjPYlIBc == wCdjPYlIBc){OupxrJikou = true;}
      while(JwjcRUNByt == JwjcRUNByt){REgxDhiGxC = true;}
      if(WxPoqcWlcH == true){WxPoqcWlcH = false;}
      if(DWoDVeTeUj == true){DWoDVeTeUj = false;}
      if(maBSDxfoTW == true){maBSDxfoTW = false;}
      if(WYSjWymosm == true){WYSjWymosm = false;}
      if(BzesZmGfHl == true){BzesZmGfHl = false;}
      if(BigOHuwwls == true){BigOHuwwls = false;}
      if(wgRFkdDFgW == true){wgRFkdDFgW = false;}
      if(relghnwHsP == true){relghnwHsP = false;}
      if(qzhhVnrEcb == true){qzhhVnrEcb = false;}
      if(CpCzpUgYIu == true){CpCzpUgYIu = false;}
      if(jAzjsWwzfS == true){jAzjsWwzfS = false;}
      if(ynCVCwzjjw == true){ynCVCwzjjw = false;}
      if(lycEUBbmqN == true){lycEUBbmqN = false;}
      if(GXyyfpzxoz == true){GXyyfpzxoz = false;}
      if(rrYJcNmgws == true){rrYJcNmgws = false;}
      if(UxnMIkXuPq == true){UxnMIkXuPq = false;}
      if(uJIRMapEpM == true){uJIRMapEpM = false;}
      if(xBukEtZTaG == true){xBukEtZTaG = false;}
      if(OupxrJikou == true){OupxrJikou = false;}
      if(REgxDhiGxC == true){REgxDhiGxC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCUZIIQYZR
{ 
  void gMirzHoqNa()
  { 
      bool sTcaBEqbpB = false;
      bool QQPpyOKWVk = false;
      bool fsCZXDTMmO = false;
      bool UkdNNPqCqr = false;
      bool tTcfhPPOoO = false;
      bool aHkAmzQDCx = false;
      bool kenafflBch = false;
      bool WHecqLPWqH = false;
      bool mFWYnMAdaN = false;
      bool zmztHOeBzC = false;
      bool cNkGqScHJa = false;
      bool jtLuKfHPmS = false;
      bool fIaPijHkVb = false;
      bool gNWodZTQgU = false;
      bool jrUAcEbEib = false;
      bool HOOgWUmVWH = false;
      bool KqkgsVWWQj = false;
      bool LqhRhmnZld = false;
      bool HCBsTRypSJ = false;
      bool lysZKsHmGG = false;
      string wzRHqRsoPd;
      string tUiVVfCpeN;
      string YVxQrFHJYX;
      string dIkBkfVyiF;
      string lfMSjJlIyf;
      string IFSTsZCAPk;
      string KjQqzligkp;
      string JEHYbsJdgh;
      string SzKsPYoRIK;
      string dViyuCPUSy;
      string ZFWIVEysrA;
      string QXSgRKZWba;
      string wRXaLmVJcY;
      string cnLiHNbBWL;
      string ZuZItFDBfj;
      string brrqBIgwwi;
      string hnQSWbMjYE;
      string iXAQAArPfG;
      string jTdswkuTgz;
      string gfEnckeGkS;
      if(wzRHqRsoPd == ZFWIVEysrA){sTcaBEqbpB = true;}
      else if(ZFWIVEysrA == wzRHqRsoPd){cNkGqScHJa = true;}
      if(tUiVVfCpeN == QXSgRKZWba){QQPpyOKWVk = true;}
      else if(QXSgRKZWba == tUiVVfCpeN){jtLuKfHPmS = true;}
      if(YVxQrFHJYX == wRXaLmVJcY){fsCZXDTMmO = true;}
      else if(wRXaLmVJcY == YVxQrFHJYX){fIaPijHkVb = true;}
      if(dIkBkfVyiF == cnLiHNbBWL){UkdNNPqCqr = true;}
      else if(cnLiHNbBWL == dIkBkfVyiF){gNWodZTQgU = true;}
      if(lfMSjJlIyf == ZuZItFDBfj){tTcfhPPOoO = true;}
      else if(ZuZItFDBfj == lfMSjJlIyf){jrUAcEbEib = true;}
      if(IFSTsZCAPk == brrqBIgwwi){aHkAmzQDCx = true;}
      else if(brrqBIgwwi == IFSTsZCAPk){HOOgWUmVWH = true;}
      if(KjQqzligkp == hnQSWbMjYE){kenafflBch = true;}
      else if(hnQSWbMjYE == KjQqzligkp){KqkgsVWWQj = true;}
      if(JEHYbsJdgh == iXAQAArPfG){WHecqLPWqH = true;}
      if(SzKsPYoRIK == jTdswkuTgz){mFWYnMAdaN = true;}
      if(dViyuCPUSy == gfEnckeGkS){zmztHOeBzC = true;}
      while(iXAQAArPfG == JEHYbsJdgh){LqhRhmnZld = true;}
      while(jTdswkuTgz == jTdswkuTgz){HCBsTRypSJ = true;}
      while(gfEnckeGkS == gfEnckeGkS){lysZKsHmGG = true;}
      if(sTcaBEqbpB == true){sTcaBEqbpB = false;}
      if(QQPpyOKWVk == true){QQPpyOKWVk = false;}
      if(fsCZXDTMmO == true){fsCZXDTMmO = false;}
      if(UkdNNPqCqr == true){UkdNNPqCqr = false;}
      if(tTcfhPPOoO == true){tTcfhPPOoO = false;}
      if(aHkAmzQDCx == true){aHkAmzQDCx = false;}
      if(kenafflBch == true){kenafflBch = false;}
      if(WHecqLPWqH == true){WHecqLPWqH = false;}
      if(mFWYnMAdaN == true){mFWYnMAdaN = false;}
      if(zmztHOeBzC == true){zmztHOeBzC = false;}
      if(cNkGqScHJa == true){cNkGqScHJa = false;}
      if(jtLuKfHPmS == true){jtLuKfHPmS = false;}
      if(fIaPijHkVb == true){fIaPijHkVb = false;}
      if(gNWodZTQgU == true){gNWodZTQgU = false;}
      if(jrUAcEbEib == true){jrUAcEbEib = false;}
      if(HOOgWUmVWH == true){HOOgWUmVWH = false;}
      if(KqkgsVWWQj == true){KqkgsVWWQj = false;}
      if(LqhRhmnZld == true){LqhRhmnZld = false;}
      if(HCBsTRypSJ == true){HCBsTRypSJ = false;}
      if(lysZKsHmGG == true){lysZKsHmGG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AAFXMETBYX
{ 
  void yKlcDPQIDi()
  { 
      bool hQclWfSrfC = false;
      bool CAHpByFmkc = false;
      bool nWegAERdBf = false;
      bool EicwanCueT = false;
      bool GitqTnBRIG = false;
      bool kSIgNKkwkS = false;
      bool OnpAxTWLPN = false;
      bool uJIRWEcmMM = false;
      bool DAVuulZuiQ = false;
      bool CGKMESsttA = false;
      bool QoCuKaKqKI = false;
      bool hxiXOORuFL = false;
      bool saczLozuMD = false;
      bool LisMwNyajT = false;
      bool ahjZhEWmxp = false;
      bool AxnhGoMCiV = false;
      bool aOeGwyDVaB = false;
      bool QqLkkKpCQG = false;
      bool SLyVDNtLGG = false;
      bool AuqOrMDccj = false;
      string mJVEpyPKer;
      string XsVxHsYbaO;
      string daERLGjjmM;
      string TxLXVLacbb;
      string TkIZsVnylT;
      string luambLFEsi;
      string OfXRXagyaw;
      string RuAzusSdXo;
      string RkxSaYVXwK;
      string GWirMnMqBR;
      string npWoBpuari;
      string rafDQchFqz;
      string FIBQouLIlG;
      string fbcGBbOIQj;
      string cufNSfpfaj;
      string GHzCMenFAG;
      string emolCQxZCo;
      string NZnHVKcnyJ;
      string EfgBAYbZtV;
      string nIHKFpFtKB;
      if(mJVEpyPKer == npWoBpuari){hQclWfSrfC = true;}
      else if(npWoBpuari == mJVEpyPKer){QoCuKaKqKI = true;}
      if(XsVxHsYbaO == rafDQchFqz){CAHpByFmkc = true;}
      else if(rafDQchFqz == XsVxHsYbaO){hxiXOORuFL = true;}
      if(daERLGjjmM == FIBQouLIlG){nWegAERdBf = true;}
      else if(FIBQouLIlG == daERLGjjmM){saczLozuMD = true;}
      if(TxLXVLacbb == fbcGBbOIQj){EicwanCueT = true;}
      else if(fbcGBbOIQj == TxLXVLacbb){LisMwNyajT = true;}
      if(TkIZsVnylT == cufNSfpfaj){GitqTnBRIG = true;}
      else if(cufNSfpfaj == TkIZsVnylT){ahjZhEWmxp = true;}
      if(luambLFEsi == GHzCMenFAG){kSIgNKkwkS = true;}
      else if(GHzCMenFAG == luambLFEsi){AxnhGoMCiV = true;}
      if(OfXRXagyaw == emolCQxZCo){OnpAxTWLPN = true;}
      else if(emolCQxZCo == OfXRXagyaw){aOeGwyDVaB = true;}
      if(RuAzusSdXo == NZnHVKcnyJ){uJIRWEcmMM = true;}
      if(RkxSaYVXwK == EfgBAYbZtV){DAVuulZuiQ = true;}
      if(GWirMnMqBR == nIHKFpFtKB){CGKMESsttA = true;}
      while(NZnHVKcnyJ == RuAzusSdXo){QqLkkKpCQG = true;}
      while(EfgBAYbZtV == EfgBAYbZtV){SLyVDNtLGG = true;}
      while(nIHKFpFtKB == nIHKFpFtKB){AuqOrMDccj = true;}
      if(hQclWfSrfC == true){hQclWfSrfC = false;}
      if(CAHpByFmkc == true){CAHpByFmkc = false;}
      if(nWegAERdBf == true){nWegAERdBf = false;}
      if(EicwanCueT == true){EicwanCueT = false;}
      if(GitqTnBRIG == true){GitqTnBRIG = false;}
      if(kSIgNKkwkS == true){kSIgNKkwkS = false;}
      if(OnpAxTWLPN == true){OnpAxTWLPN = false;}
      if(uJIRWEcmMM == true){uJIRWEcmMM = false;}
      if(DAVuulZuiQ == true){DAVuulZuiQ = false;}
      if(CGKMESsttA == true){CGKMESsttA = false;}
      if(QoCuKaKqKI == true){QoCuKaKqKI = false;}
      if(hxiXOORuFL == true){hxiXOORuFL = false;}
      if(saczLozuMD == true){saczLozuMD = false;}
      if(LisMwNyajT == true){LisMwNyajT = false;}
      if(ahjZhEWmxp == true){ahjZhEWmxp = false;}
      if(AxnhGoMCiV == true){AxnhGoMCiV = false;}
      if(aOeGwyDVaB == true){aOeGwyDVaB = false;}
      if(QqLkkKpCQG == true){QqLkkKpCQG = false;}
      if(SLyVDNtLGG == true){SLyVDNtLGG = false;}
      if(AuqOrMDccj == true){AuqOrMDccj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOYFVIEOCG
{ 
  void aWpdgGAemc()
  { 
      bool JaPsTVlAXS = false;
      bool jTugjBuqRa = false;
      bool eqKpuUOnLD = false;
      bool mCuEjJZcls = false;
      bool qMklhMUsTY = false;
      bool gDZiNSQYyz = false;
      bool GxoTehYqwa = false;
      bool aREYiRFXIi = false;
      bool zVUmWjbMpR = false;
      bool rAelltXQHz = false;
      bool mcwsxPyBzu = false;
      bool MrQOzkbCxt = false;
      bool GMAehZmRlo = false;
      bool tnQJuWZboG = false;
      bool laMuEAjQmB = false;
      bool RVTMsabQKW = false;
      bool cfPKBXbGSc = false;
      bool LAMpIezFag = false;
      bool pVejWYUDQU = false;
      bool tIQSdFLCsf = false;
      string rZewZuJqEy;
      string tQjVRxdljw;
      string kJNftpToEb;
      string PTPoLmKhnZ;
      string UhSQAyokJi;
      string CISiOhMzCj;
      string bUlciaAtKe;
      string luxJaCpweu;
      string AieUYGBgZc;
      string aKfEyAupgZ;
      string ytZewHLIHL;
      string rPUGisoQDb;
      string ZTThEaPrLZ;
      string HzOExGIAYR;
      string urYOkKpYVE;
      string KdlFAeZraU;
      string qSxgErAPJb;
      string jorlghtFws;
      string kpWGPcNJES;
      string fPZDZctrJr;
      if(rZewZuJqEy == ytZewHLIHL){JaPsTVlAXS = true;}
      else if(ytZewHLIHL == rZewZuJqEy){mcwsxPyBzu = true;}
      if(tQjVRxdljw == rPUGisoQDb){jTugjBuqRa = true;}
      else if(rPUGisoQDb == tQjVRxdljw){MrQOzkbCxt = true;}
      if(kJNftpToEb == ZTThEaPrLZ){eqKpuUOnLD = true;}
      else if(ZTThEaPrLZ == kJNftpToEb){GMAehZmRlo = true;}
      if(PTPoLmKhnZ == HzOExGIAYR){mCuEjJZcls = true;}
      else if(HzOExGIAYR == PTPoLmKhnZ){tnQJuWZboG = true;}
      if(UhSQAyokJi == urYOkKpYVE){qMklhMUsTY = true;}
      else if(urYOkKpYVE == UhSQAyokJi){laMuEAjQmB = true;}
      if(CISiOhMzCj == KdlFAeZraU){gDZiNSQYyz = true;}
      else if(KdlFAeZraU == CISiOhMzCj){RVTMsabQKW = true;}
      if(bUlciaAtKe == qSxgErAPJb){GxoTehYqwa = true;}
      else if(qSxgErAPJb == bUlciaAtKe){cfPKBXbGSc = true;}
      if(luxJaCpweu == jorlghtFws){aREYiRFXIi = true;}
      if(AieUYGBgZc == kpWGPcNJES){zVUmWjbMpR = true;}
      if(aKfEyAupgZ == fPZDZctrJr){rAelltXQHz = true;}
      while(jorlghtFws == luxJaCpweu){LAMpIezFag = true;}
      while(kpWGPcNJES == kpWGPcNJES){pVejWYUDQU = true;}
      while(fPZDZctrJr == fPZDZctrJr){tIQSdFLCsf = true;}
      if(JaPsTVlAXS == true){JaPsTVlAXS = false;}
      if(jTugjBuqRa == true){jTugjBuqRa = false;}
      if(eqKpuUOnLD == true){eqKpuUOnLD = false;}
      if(mCuEjJZcls == true){mCuEjJZcls = false;}
      if(qMklhMUsTY == true){qMklhMUsTY = false;}
      if(gDZiNSQYyz == true){gDZiNSQYyz = false;}
      if(GxoTehYqwa == true){GxoTehYqwa = false;}
      if(aREYiRFXIi == true){aREYiRFXIi = false;}
      if(zVUmWjbMpR == true){zVUmWjbMpR = false;}
      if(rAelltXQHz == true){rAelltXQHz = false;}
      if(mcwsxPyBzu == true){mcwsxPyBzu = false;}
      if(MrQOzkbCxt == true){MrQOzkbCxt = false;}
      if(GMAehZmRlo == true){GMAehZmRlo = false;}
      if(tnQJuWZboG == true){tnQJuWZboG = false;}
      if(laMuEAjQmB == true){laMuEAjQmB = false;}
      if(RVTMsabQKW == true){RVTMsabQKW = false;}
      if(cfPKBXbGSc == true){cfPKBXbGSc = false;}
      if(LAMpIezFag == true){LAMpIezFag = false;}
      if(pVejWYUDQU == true){pVejWYUDQU = false;}
      if(tIQSdFLCsf == true){tIQSdFLCsf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MXRTAFCQTM
{ 
  void dZxGPCizza()
  { 
      bool treqiYFWWM = false;
      bool sEaOHJUKPI = false;
      bool RWsjcXFnqc = false;
      bool saTIRQBrSC = false;
      bool ngOKyWwOue = false;
      bool CWORtWztNK = false;
      bool SRftTSjSwp = false;
      bool IbrMUjHhlF = false;
      bool bprMZVLCOu = false;
      bool QGeHiWBUqe = false;
      bool mdSFWZeCxJ = false;
      bool OQIHicYSTx = false;
      bool HgEBYCxjdx = false;
      bool hmqGSxXmpz = false;
      bool qJFEgAxWXF = false;
      bool xhBtXGYRfT = false;
      bool ctXzabZCok = false;
      bool FlcTGybzUY = false;
      bool EZLXAAkxiM = false;
      bool YGHVWwkFcE = false;
      string ISVwrAGHal;
      string IRPXfaeHsJ;
      string cHseKPXWpF;
      string zCxTLuZNCU;
      string ebjlNtSIbk;
      string unQDwAZqkb;
      string ciRVmGUwMk;
      string BQFXdBWHQQ;
      string xOuEJKltXK;
      string VibZruJOyH;
      string ZWwpjdirYt;
      string dRZUeNnMLb;
      string TZXBPSnefi;
      string qHIJqZSEUe;
      string bsUcgDIHud;
      string HxDWmzyuaR;
      string pEMpCVJPcE;
      string uiqfAaFtTL;
      string JfiBatElWr;
      string aXdDoXgeZL;
      if(ISVwrAGHal == ZWwpjdirYt){treqiYFWWM = true;}
      else if(ZWwpjdirYt == ISVwrAGHal){mdSFWZeCxJ = true;}
      if(IRPXfaeHsJ == dRZUeNnMLb){sEaOHJUKPI = true;}
      else if(dRZUeNnMLb == IRPXfaeHsJ){OQIHicYSTx = true;}
      if(cHseKPXWpF == TZXBPSnefi){RWsjcXFnqc = true;}
      else if(TZXBPSnefi == cHseKPXWpF){HgEBYCxjdx = true;}
      if(zCxTLuZNCU == qHIJqZSEUe){saTIRQBrSC = true;}
      else if(qHIJqZSEUe == zCxTLuZNCU){hmqGSxXmpz = true;}
      if(ebjlNtSIbk == bsUcgDIHud){ngOKyWwOue = true;}
      else if(bsUcgDIHud == ebjlNtSIbk){qJFEgAxWXF = true;}
      if(unQDwAZqkb == HxDWmzyuaR){CWORtWztNK = true;}
      else if(HxDWmzyuaR == unQDwAZqkb){xhBtXGYRfT = true;}
      if(ciRVmGUwMk == pEMpCVJPcE){SRftTSjSwp = true;}
      else if(pEMpCVJPcE == ciRVmGUwMk){ctXzabZCok = true;}
      if(BQFXdBWHQQ == uiqfAaFtTL){IbrMUjHhlF = true;}
      if(xOuEJKltXK == JfiBatElWr){bprMZVLCOu = true;}
      if(VibZruJOyH == aXdDoXgeZL){QGeHiWBUqe = true;}
      while(uiqfAaFtTL == BQFXdBWHQQ){FlcTGybzUY = true;}
      while(JfiBatElWr == JfiBatElWr){EZLXAAkxiM = true;}
      while(aXdDoXgeZL == aXdDoXgeZL){YGHVWwkFcE = true;}
      if(treqiYFWWM == true){treqiYFWWM = false;}
      if(sEaOHJUKPI == true){sEaOHJUKPI = false;}
      if(RWsjcXFnqc == true){RWsjcXFnqc = false;}
      if(saTIRQBrSC == true){saTIRQBrSC = false;}
      if(ngOKyWwOue == true){ngOKyWwOue = false;}
      if(CWORtWztNK == true){CWORtWztNK = false;}
      if(SRftTSjSwp == true){SRftTSjSwp = false;}
      if(IbrMUjHhlF == true){IbrMUjHhlF = false;}
      if(bprMZVLCOu == true){bprMZVLCOu = false;}
      if(QGeHiWBUqe == true){QGeHiWBUqe = false;}
      if(mdSFWZeCxJ == true){mdSFWZeCxJ = false;}
      if(OQIHicYSTx == true){OQIHicYSTx = false;}
      if(HgEBYCxjdx == true){HgEBYCxjdx = false;}
      if(hmqGSxXmpz == true){hmqGSxXmpz = false;}
      if(qJFEgAxWXF == true){qJFEgAxWXF = false;}
      if(xhBtXGYRfT == true){xhBtXGYRfT = false;}
      if(ctXzabZCok == true){ctXzabZCok = false;}
      if(FlcTGybzUY == true){FlcTGybzUY = false;}
      if(EZLXAAkxiM == true){EZLXAAkxiM = false;}
      if(YGHVWwkFcE == true){YGHVWwkFcE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZQWSSLSNY
{ 
  void LerzGJVGmT()
  { 
      bool lCbPkErpkr = false;
      bool AbTnGxkylF = false;
      bool yMZbnodFdR = false;
      bool mQbrTnsrFc = false;
      bool aaBYCYRfpP = false;
      bool BwCfpYbzaw = false;
      bool ZlLSFjzaUR = false;
      bool ErrJeXKBYO = false;
      bool XyPNPpOuCu = false;
      bool MsQJCnOhSS = false;
      bool ZqLYLIDsBS = false;
      bool NZZMXbWxDO = false;
      bool UDXZFLbiGp = false;
      bool IbhGofmqCH = false;
      bool mUtjglSEka = false;
      bool RReDxVSkSz = false;
      bool gTlLKlrTWq = false;
      bool ofuubzJnsT = false;
      bool rWyfYqxeIS = false;
      bool NBXCaSihYt = false;
      string YdfhqFHlkU;
      string rsUoszedqk;
      string UGBQSARqQn;
      string uzTukooJdN;
      string hNCzjqqrpp;
      string OHWHuRcOOp;
      string mPVxYsYZED;
      string JVAdDGDCga;
      string IZBZYnbLzS;
      string MZtmZRqFZp;
      string SQmlfsHrEn;
      string NagmgNOwXk;
      string QMZlqiaNDk;
      string OybpIrlPsf;
      string giHLEksGFM;
      string DugoZFpBtw;
      string RsoTYPzqeo;
      string azCqEgFOhF;
      string pUIqgTQlQD;
      string BkUwNmtnlo;
      if(YdfhqFHlkU == SQmlfsHrEn){lCbPkErpkr = true;}
      else if(SQmlfsHrEn == YdfhqFHlkU){ZqLYLIDsBS = true;}
      if(rsUoszedqk == NagmgNOwXk){AbTnGxkylF = true;}
      else if(NagmgNOwXk == rsUoszedqk){NZZMXbWxDO = true;}
      if(UGBQSARqQn == QMZlqiaNDk){yMZbnodFdR = true;}
      else if(QMZlqiaNDk == UGBQSARqQn){UDXZFLbiGp = true;}
      if(uzTukooJdN == OybpIrlPsf){mQbrTnsrFc = true;}
      else if(OybpIrlPsf == uzTukooJdN){IbhGofmqCH = true;}
      if(hNCzjqqrpp == giHLEksGFM){aaBYCYRfpP = true;}
      else if(giHLEksGFM == hNCzjqqrpp){mUtjglSEka = true;}
      if(OHWHuRcOOp == DugoZFpBtw){BwCfpYbzaw = true;}
      else if(DugoZFpBtw == OHWHuRcOOp){RReDxVSkSz = true;}
      if(mPVxYsYZED == RsoTYPzqeo){ZlLSFjzaUR = true;}
      else if(RsoTYPzqeo == mPVxYsYZED){gTlLKlrTWq = true;}
      if(JVAdDGDCga == azCqEgFOhF){ErrJeXKBYO = true;}
      if(IZBZYnbLzS == pUIqgTQlQD){XyPNPpOuCu = true;}
      if(MZtmZRqFZp == BkUwNmtnlo){MsQJCnOhSS = true;}
      while(azCqEgFOhF == JVAdDGDCga){ofuubzJnsT = true;}
      while(pUIqgTQlQD == pUIqgTQlQD){rWyfYqxeIS = true;}
      while(BkUwNmtnlo == BkUwNmtnlo){NBXCaSihYt = true;}
      if(lCbPkErpkr == true){lCbPkErpkr = false;}
      if(AbTnGxkylF == true){AbTnGxkylF = false;}
      if(yMZbnodFdR == true){yMZbnodFdR = false;}
      if(mQbrTnsrFc == true){mQbrTnsrFc = false;}
      if(aaBYCYRfpP == true){aaBYCYRfpP = false;}
      if(BwCfpYbzaw == true){BwCfpYbzaw = false;}
      if(ZlLSFjzaUR == true){ZlLSFjzaUR = false;}
      if(ErrJeXKBYO == true){ErrJeXKBYO = false;}
      if(XyPNPpOuCu == true){XyPNPpOuCu = false;}
      if(MsQJCnOhSS == true){MsQJCnOhSS = false;}
      if(ZqLYLIDsBS == true){ZqLYLIDsBS = false;}
      if(NZZMXbWxDO == true){NZZMXbWxDO = false;}
      if(UDXZFLbiGp == true){UDXZFLbiGp = false;}
      if(IbhGofmqCH == true){IbhGofmqCH = false;}
      if(mUtjglSEka == true){mUtjglSEka = false;}
      if(RReDxVSkSz == true){RReDxVSkSz = false;}
      if(gTlLKlrTWq == true){gTlLKlrTWq = false;}
      if(ofuubzJnsT == true){ofuubzJnsT = false;}
      if(rWyfYqxeIS == true){rWyfYqxeIS = false;}
      if(NBXCaSihYt == true){NBXCaSihYt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XIANNIJJNS
{ 
  void HITqxsBTmi()
  { 
      bool CQCTsMYLur = false;
      bool ZdmoslWWNn = false;
      bool dHlWKWDocI = false;
      bool HIkNDfTTux = false;
      bool GYwXMdXkqB = false;
      bool yjqHiteeJW = false;
      bool JjhmjRsYkM = false;
      bool RCbQhFLNKg = false;
      bool ySxaKWQcdI = false;
      bool BnKXnVpJmt = false;
      bool kyzdjuIZZd = false;
      bool iQTcYplHcN = false;
      bool APucLcrDbL = false;
      bool OCaQuzSTqO = false;
      bool OpCAZjUhzx = false;
      bool jigYtUDWSG = false;
      bool DFyOOgpDgY = false;
      bool XSPNzJNuCa = false;
      bool IJDdafUBWa = false;
      bool uwAkKIrnkr = false;
      string VYDOFQeWFQ;
      string pGGqRcLZdx;
      string IqGVauRHpG;
      string sQNshmXheg;
      string JeoGMXVZiK;
      string TdXLcdSgmJ;
      string yWfzXZsNId;
      string FctxmdCAJD;
      string ZqYflOrCPE;
      string UpuVhmyohm;
      string dHREFpiaXz;
      string bRXijGxzMI;
      string gqxDJPhYPz;
      string eMRVZRYUZw;
      string eRdQcCSLka;
      string ozbZGmKNup;
      string IJKYTOABJR;
      string hcZQdONgaG;
      string xVmnKfjrPl;
      string HLZjnUGFwN;
      if(VYDOFQeWFQ == dHREFpiaXz){CQCTsMYLur = true;}
      else if(dHREFpiaXz == VYDOFQeWFQ){kyzdjuIZZd = true;}
      if(pGGqRcLZdx == bRXijGxzMI){ZdmoslWWNn = true;}
      else if(bRXijGxzMI == pGGqRcLZdx){iQTcYplHcN = true;}
      if(IqGVauRHpG == gqxDJPhYPz){dHlWKWDocI = true;}
      else if(gqxDJPhYPz == IqGVauRHpG){APucLcrDbL = true;}
      if(sQNshmXheg == eMRVZRYUZw){HIkNDfTTux = true;}
      else if(eMRVZRYUZw == sQNshmXheg){OCaQuzSTqO = true;}
      if(JeoGMXVZiK == eRdQcCSLka){GYwXMdXkqB = true;}
      else if(eRdQcCSLka == JeoGMXVZiK){OpCAZjUhzx = true;}
      if(TdXLcdSgmJ == ozbZGmKNup){yjqHiteeJW = true;}
      else if(ozbZGmKNup == TdXLcdSgmJ){jigYtUDWSG = true;}
      if(yWfzXZsNId == IJKYTOABJR){JjhmjRsYkM = true;}
      else if(IJKYTOABJR == yWfzXZsNId){DFyOOgpDgY = true;}
      if(FctxmdCAJD == hcZQdONgaG){RCbQhFLNKg = true;}
      if(ZqYflOrCPE == xVmnKfjrPl){ySxaKWQcdI = true;}
      if(UpuVhmyohm == HLZjnUGFwN){BnKXnVpJmt = true;}
      while(hcZQdONgaG == FctxmdCAJD){XSPNzJNuCa = true;}
      while(xVmnKfjrPl == xVmnKfjrPl){IJDdafUBWa = true;}
      while(HLZjnUGFwN == HLZjnUGFwN){uwAkKIrnkr = true;}
      if(CQCTsMYLur == true){CQCTsMYLur = false;}
      if(ZdmoslWWNn == true){ZdmoslWWNn = false;}
      if(dHlWKWDocI == true){dHlWKWDocI = false;}
      if(HIkNDfTTux == true){HIkNDfTTux = false;}
      if(GYwXMdXkqB == true){GYwXMdXkqB = false;}
      if(yjqHiteeJW == true){yjqHiteeJW = false;}
      if(JjhmjRsYkM == true){JjhmjRsYkM = false;}
      if(RCbQhFLNKg == true){RCbQhFLNKg = false;}
      if(ySxaKWQcdI == true){ySxaKWQcdI = false;}
      if(BnKXnVpJmt == true){BnKXnVpJmt = false;}
      if(kyzdjuIZZd == true){kyzdjuIZZd = false;}
      if(iQTcYplHcN == true){iQTcYplHcN = false;}
      if(APucLcrDbL == true){APucLcrDbL = false;}
      if(OCaQuzSTqO == true){OCaQuzSTqO = false;}
      if(OpCAZjUhzx == true){OpCAZjUhzx = false;}
      if(jigYtUDWSG == true){jigYtUDWSG = false;}
      if(DFyOOgpDgY == true){DFyOOgpDgY = false;}
      if(XSPNzJNuCa == true){XSPNzJNuCa = false;}
      if(IJDdafUBWa == true){IJDdafUBWa = false;}
      if(uwAkKIrnkr == true){uwAkKIrnkr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMNFDSZHVW
{ 
  void EmNNuWgoqO()
  { 
      bool pgEOXCRzwp = false;
      bool DxMFGkcSDs = false;
      bool nXQujRUyEL = false;
      bool sgpkUmlkzZ = false;
      bool hrnYlIlqaF = false;
      bool kjAdGRPIeG = false;
      bool gStjxVGajT = false;
      bool yrScLujrJb = false;
      bool edWzZIfMeD = false;
      bool WdFrrOxDbP = false;
      bool BLGHGsQWSK = false;
      bool hXzCaDwuKn = false;
      bool ptwgwUlakw = false;
      bool yfPsaTWOrg = false;
      bool rIsUUzdDRn = false;
      bool RBsmZGOZLk = false;
      bool GplVLBHFbG = false;
      bool ggCdwgBbLx = false;
      bool piIwdwmcST = false;
      bool ExDGZBWXIT = false;
      string qjwwhZJFJI;
      string odLrugFhzX;
      string ciZlmXemzW;
      string SFsexXEQTq;
      string XsreJwUqyi;
      string xtKdZHKJIJ;
      string tVFlpikgtW;
      string boNIAjqubq;
      string DmoPZXuOEp;
      string NtHKwCmGna;
      string LmwaHIfCdo;
      string QOhRFHgoLR;
      string nVcEJggDMy;
      string xkGBeQpOIR;
      string qrjOYyMpEo;
      string UytWloKrQa;
      string acpfreIflo;
      string QSftaukNeL;
      string TpzXczqjPp;
      string FyxhpOCEWt;
      if(qjwwhZJFJI == LmwaHIfCdo){pgEOXCRzwp = true;}
      else if(LmwaHIfCdo == qjwwhZJFJI){BLGHGsQWSK = true;}
      if(odLrugFhzX == QOhRFHgoLR){DxMFGkcSDs = true;}
      else if(QOhRFHgoLR == odLrugFhzX){hXzCaDwuKn = true;}
      if(ciZlmXemzW == nVcEJggDMy){nXQujRUyEL = true;}
      else if(nVcEJggDMy == ciZlmXemzW){ptwgwUlakw = true;}
      if(SFsexXEQTq == xkGBeQpOIR){sgpkUmlkzZ = true;}
      else if(xkGBeQpOIR == SFsexXEQTq){yfPsaTWOrg = true;}
      if(XsreJwUqyi == qrjOYyMpEo){hrnYlIlqaF = true;}
      else if(qrjOYyMpEo == XsreJwUqyi){rIsUUzdDRn = true;}
      if(xtKdZHKJIJ == UytWloKrQa){kjAdGRPIeG = true;}
      else if(UytWloKrQa == xtKdZHKJIJ){RBsmZGOZLk = true;}
      if(tVFlpikgtW == acpfreIflo){gStjxVGajT = true;}
      else if(acpfreIflo == tVFlpikgtW){GplVLBHFbG = true;}
      if(boNIAjqubq == QSftaukNeL){yrScLujrJb = true;}
      if(DmoPZXuOEp == TpzXczqjPp){edWzZIfMeD = true;}
      if(NtHKwCmGna == FyxhpOCEWt){WdFrrOxDbP = true;}
      while(QSftaukNeL == boNIAjqubq){ggCdwgBbLx = true;}
      while(TpzXczqjPp == TpzXczqjPp){piIwdwmcST = true;}
      while(FyxhpOCEWt == FyxhpOCEWt){ExDGZBWXIT = true;}
      if(pgEOXCRzwp == true){pgEOXCRzwp = false;}
      if(DxMFGkcSDs == true){DxMFGkcSDs = false;}
      if(nXQujRUyEL == true){nXQujRUyEL = false;}
      if(sgpkUmlkzZ == true){sgpkUmlkzZ = false;}
      if(hrnYlIlqaF == true){hrnYlIlqaF = false;}
      if(kjAdGRPIeG == true){kjAdGRPIeG = false;}
      if(gStjxVGajT == true){gStjxVGajT = false;}
      if(yrScLujrJb == true){yrScLujrJb = false;}
      if(edWzZIfMeD == true){edWzZIfMeD = false;}
      if(WdFrrOxDbP == true){WdFrrOxDbP = false;}
      if(BLGHGsQWSK == true){BLGHGsQWSK = false;}
      if(hXzCaDwuKn == true){hXzCaDwuKn = false;}
      if(ptwgwUlakw == true){ptwgwUlakw = false;}
      if(yfPsaTWOrg == true){yfPsaTWOrg = false;}
      if(rIsUUzdDRn == true){rIsUUzdDRn = false;}
      if(RBsmZGOZLk == true){RBsmZGOZLk = false;}
      if(GplVLBHFbG == true){GplVLBHFbG = false;}
      if(ggCdwgBbLx == true){ggCdwgBbLx = false;}
      if(piIwdwmcST == true){piIwdwmcST = false;}
      if(ExDGZBWXIT == true){ExDGZBWXIT = false;}
    } 
}; 
