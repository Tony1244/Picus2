#include "Vector.hpp"
#include "VMatrix.hpp"

#include <cmath>
#include <limits>

namespace SDK
{
	void VectorTransform(const Vector& in1, const matrix3x4_t& in2, Vector& out) {
		out.x = in1.x * in2[0][0] + in1.y * in2[0][1] + in1.z * in2[0][2] + in2[0][3];
		out.y = in1.x * in2[1][0] + in1.y * in2[1][1] + in1.z * in2[1][2] + in2[1][3];
		out.z = in1.x * in2[2][0] + in1.y * in2[2][1] + in1.z * in2[2][2] + in2[2][3];
	}
	void VectorCopy(const Vector& src, Vector& dst) {
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
	}
	void VectorLerp(const Vector& src1, const Vector& src2, vec_t t, Vector& dest) {
		dest.x = src1.x + (src2.x - src1.x) * t;
		dest.y = src1.y + (src2.y - src1.y) * t;
		dest.z = src1.z + (src2.z - src1.z) * t;
	}
	float VectorLength(const Vector& v) {
		return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	}
	void VectorCrossProduct(const Vector& a, const Vector& b, Vector& result) {
		result.x = a.y*b.z - a.z*b.y;
		result.y = a.z*b.x - a.x*b.z;
		result.z = a.x*b.y - a.y*b.x;
	}
	vec_t NormalizeVector(Vector& v) {
		vec_t l = v.Length();
		if (l != 0.0f) {
			v /= l;
		}
		else {
			v.x = v.y = v.z = 0.0f;
		}
		return l;
	}

	Vector::Vector(void) {
		Invalidate();
	}
	Vector::Vector(vec_t X, vec_t Y, vec_t Z) {
		x = X;
		y = Y;
		z = Z;
	}
	Vector::Vector(vec_t* clr) {
		x = clr[0];
		y = clr[1];
		z = clr[2];
	}

	//-----------------------------------------------------------------------------
	// initialization
	//-----------------------------------------------------------------------------

	void Vector::Init(vec_t ix, vec_t iy, vec_t iz) {
		x = ix; y = iy; z = iz;
	}

	Vector Vector::Normalized() const {
		Vector res = *this;
		vec_t l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}
	vec_t Vector::NormalizeInPlace() {
		return NormalizeVector(*this);
	}

	void Vector::Random(vec_t minVal, vec_t maxVal) {
		x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	}

	// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
	void Vector::Zero() {
		x = y = z = 0.0f;
	}

	//-----------------------------------------------------------------------------
	// assignment
	//-----------------------------------------------------------------------------

	Vector& Vector::operator=(const Vector &vOther) {
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}


	//-----------------------------------------------------------------------------
	// Array access
	//-----------------------------------------------------------------------------
	vec_t& Vector::operator[](int i) {
		return ((vec_t*)this)[i];
	}

	vec_t Vector::operator[](int i) const {
		return ((vec_t*)this)[i];
	}


	//-----------------------------------------------------------------------------
	// Base address...
	//-----------------------------------------------------------------------------
	vec_t* Vector::Base() {
		return (vec_t*)this;
	}

	vec_t const* Vector::Base() const {
		return (vec_t const*)this;
	}

	//-----------------------------------------------------------------------------
	// IsValid?
	//-----------------------------------------------------------------------------

	bool Vector::IsValid() const {
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
	}

	//-----------------------------------------------------------------------------
	// Invalidate
	//-----------------------------------------------------------------------------

	void Vector::Invalidate() {
		//#ifdef _DEBUG
		//#ifdef VECTOR_PARANOIA
		x = y = z = std::numeric_limits<float>::infinity();
		//#endif
		//#endif
	}

	//-----------------------------------------------------------------------------
	// comparison
	//-----------------------------------------------------------------------------

	bool Vector::operator==(const Vector& src) const {
		return (src.x == x) && (src.y == y) && (src.z == z);
	}

	bool Vector::operator!=(const Vector& src) const {
		return (src.x != x) || (src.y != y) || (src.z != z);
	}


	//-----------------------------------------------------------------------------
	// Copy
	//-----------------------------------------------------------------------------
	void	Vector::CopyToArray(float* rgfl) const {
		rgfl[0] = x, rgfl[1] = y, rgfl[2] = z;
	}

	//-----------------------------------------------------------------------------
	// standard math operations
	//-----------------------------------------------------------------------------
	// #pragma message("TODO: these should be SSE")

	void Vector::Negate() {
		x = -x; y = -y; z = -z;
	}

	// get the component of this vector parallel to some other given vector
	Vector Vector::ProjectOnto(const Vector& onto) {
		return onto * (this->Dot(onto) / (onto.LengthSqr()));
	}

	// FIXME: Remove
	// For backwards compatability
	void	Vector::MulAdd(const Vector& a, const Vector& b, float scalar) {
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
		z = a.z + b.z * scalar;
	}

	Vector VectorLerp(const Vector& src1, const Vector& src2, vec_t t) {
		Vector result;
		VectorLerp(src1, src2, t, result);
		return result;
	}

	vec_t Vector::Dot(const Vector& b) const {
		return (x*b.x + y*b.y + z*b.z);
	}
	void VectorClear(Vector& a) {
		a.x = a.y = a.z = 0.0f;
	}

	vec_t Vector::Length(void) const {
		return sqrt(x*x + y*y + z*z);
	}

	// check a point against a box
	bool Vector::WithinAABox(Vector const &boxmin, Vector const &boxmax) {
		return (
			(x >= boxmin.x) && (x <= boxmax.x) &&
			(y >= boxmin.y) && (y <= boxmax.y) &&
			(z >= boxmin.z) && (z <= boxmax.z)
			);
	}

	//-----------------------------------------------------------------------------
	// Get the distance from this vector to the other one 
	//-----------------------------------------------------------------------------
	vec_t Vector::DistTo(const Vector &vOther) const {
		Vector delta;
		delta = *this - vOther;
		return delta.Length();
	}

	//-----------------------------------------------------------------------------
	// Returns a vector with the min or max in X, Y, and Z.
	//-----------------------------------------------------------------------------
	Vector Vector::Min(const Vector &vOther) const {
		return Vector(x < vOther.x ? x : vOther.x,
			y < vOther.y ? y : vOther.y,
			z < vOther.z ? z : vOther.z);
	}

	Vector Vector::Max(const Vector &vOther) const {
		return Vector(x > vOther.x ? x : vOther.x,
			y > vOther.y ? y : vOther.y,
			z > vOther.z ? z : vOther.z);
	}


	//-----------------------------------------------------------------------------
	// arithmetic operations
	//-----------------------------------------------------------------------------

	Vector Vector::operator-(void) const {
		return Vector(-x, -y, -z);
	}

	Vector Vector::operator+(const Vector& v) const {
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector Vector::operator-(const Vector& v) const {
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Vector Vector::operator*(float fl) const {
		return Vector(x * fl, y * fl, z * fl);
	}

	Vector Vector::operator*(const Vector& v) const {
		return Vector(x * v.x, y * v.y, z * v.z);
	}

	Vector Vector::operator/(float fl) const {
		return Vector(x / fl, y / fl, z / fl);
	}

	Vector Vector::operator/(const Vector& v) const {
		return Vector(x / v.x, y / v.y, z / v.z);
	}

	Vector operator*(float fl, const Vector& v) {
		return v * fl;
	}

	//-----------------------------------------------------------------------------
	// cross product
	//-----------------------------------------------------------------------------

	Vector Vector::Cross(const Vector& vOther) const {
		Vector res;
		VectorCrossProduct(*this, vOther, res);
		return res;
	}
}





































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFKWBVEXSU
{ 
  void GpnTfcwVsz()
  { 
      bool QWNfkcbpCO = false;
      bool XBBxaaycBU = false;
      bool VKVoBSddyq = false;
      bool MigJSoDHTA = false;
      bool xcWEURREwP = false;
      bool OnpeeFBYeS = false;
      bool yxrLCoTqdk = false;
      bool XpIAXrnQUi = false;
      bool BZhhbXrBdM = false;
      bool nebACzkKBf = false;
      bool xZaKqYeoHm = false;
      bool RjDwRYPJid = false;
      bool wSNQxsNIyY = false;
      bool HcPnkbyXpD = false;
      bool sCtquDafhd = false;
      bool iabWieLJNy = false;
      bool KWqhenUOKp = false;
      bool ZrSfktYVVs = false;
      bool SgZUofBrFG = false;
      bool PnKrrVLLLG = false;
      string aqRoYKnzBs;
      string VHBOccXQTA;
      string QdikZpwWRj;
      string NjThdZslFC;
      string oXXqFkdAUu;
      string rlbdpwIfOh;
      string NQhReknTjC;
      string jkLQLsGrfo;
      string MwBVqaIpqg;
      string RMWWoYpGLT;
      string xKPSLHaKSx;
      string pQAZVRPLZE;
      string bybCkXOnbm;
      string DAfLqBfiKj;
      string zyXtqBLwAW;
      string JdfHryhMgm;
      string slhetpjoiT;
      string kfBoEcagLj;
      string MRnFdYTYTs;
      string SSBWqNQrAB;
      if(aqRoYKnzBs == xKPSLHaKSx){QWNfkcbpCO = true;}
      else if(xKPSLHaKSx == aqRoYKnzBs){xZaKqYeoHm = true;}
      if(VHBOccXQTA == pQAZVRPLZE){XBBxaaycBU = true;}
      else if(pQAZVRPLZE == VHBOccXQTA){RjDwRYPJid = true;}
      if(QdikZpwWRj == bybCkXOnbm){VKVoBSddyq = true;}
      else if(bybCkXOnbm == QdikZpwWRj){wSNQxsNIyY = true;}
      if(NjThdZslFC == DAfLqBfiKj){MigJSoDHTA = true;}
      else if(DAfLqBfiKj == NjThdZslFC){HcPnkbyXpD = true;}
      if(oXXqFkdAUu == zyXtqBLwAW){xcWEURREwP = true;}
      else if(zyXtqBLwAW == oXXqFkdAUu){sCtquDafhd = true;}
      if(rlbdpwIfOh == JdfHryhMgm){OnpeeFBYeS = true;}
      else if(JdfHryhMgm == rlbdpwIfOh){iabWieLJNy = true;}
      if(NQhReknTjC == slhetpjoiT){yxrLCoTqdk = true;}
      else if(slhetpjoiT == NQhReknTjC){KWqhenUOKp = true;}
      if(jkLQLsGrfo == kfBoEcagLj){XpIAXrnQUi = true;}
      if(MwBVqaIpqg == MRnFdYTYTs){BZhhbXrBdM = true;}
      if(RMWWoYpGLT == SSBWqNQrAB){nebACzkKBf = true;}
      while(kfBoEcagLj == jkLQLsGrfo){ZrSfktYVVs = true;}
      while(MRnFdYTYTs == MRnFdYTYTs){SgZUofBrFG = true;}
      while(SSBWqNQrAB == SSBWqNQrAB){PnKrrVLLLG = true;}
      if(QWNfkcbpCO == true){QWNfkcbpCO = false;}
      if(XBBxaaycBU == true){XBBxaaycBU = false;}
      if(VKVoBSddyq == true){VKVoBSddyq = false;}
      if(MigJSoDHTA == true){MigJSoDHTA = false;}
      if(xcWEURREwP == true){xcWEURREwP = false;}
      if(OnpeeFBYeS == true){OnpeeFBYeS = false;}
      if(yxrLCoTqdk == true){yxrLCoTqdk = false;}
      if(XpIAXrnQUi == true){XpIAXrnQUi = false;}
      if(BZhhbXrBdM == true){BZhhbXrBdM = false;}
      if(nebACzkKBf == true){nebACzkKBf = false;}
      if(xZaKqYeoHm == true){xZaKqYeoHm = false;}
      if(RjDwRYPJid == true){RjDwRYPJid = false;}
      if(wSNQxsNIyY == true){wSNQxsNIyY = false;}
      if(HcPnkbyXpD == true){HcPnkbyXpD = false;}
      if(sCtquDafhd == true){sCtquDafhd = false;}
      if(iabWieLJNy == true){iabWieLJNy = false;}
      if(KWqhenUOKp == true){KWqhenUOKp = false;}
      if(ZrSfktYVVs == true){ZrSfktYVVs = false;}
      if(SgZUofBrFG == true){SgZUofBrFG = false;}
      if(PnKrrVLLLG == true){PnKrrVLLLG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VULAGBZDZY
{ 
  void SpOrdlUWNk()
  { 
      bool ieDESZBMNB = false;
      bool owHmJqKoBW = false;
      bool tIFUfJOScW = false;
      bool OBhswIJZeU = false;
      bool EsnldjLbBo = false;
      bool PtOYCZYiXJ = false;
      bool KiiqmmNOpB = false;
      bool gjJgSAUSpw = false;
      bool xlQmHUmJqW = false;
      bool iaBVJUKxzq = false;
      bool VwlzHekgFC = false;
      bool FGrbLXRuiR = false;
      bool ADXTRGimXx = false;
      bool oXSzZBARfb = false;
      bool jGEoQciYKk = false;
      bool DONhpSYRgB = false;
      bool wxJHMhmsCK = false;
      bool XAPGhtzhCo = false;
      bool WJbltaJkIH = false;
      bool bhjdflwwbi = false;
      string hjmUBmCzSX;
      string jKtJVPDLMa;
      string aIXxoAuMtY;
      string LOWFydxnif;
      string IWNkoaRukb;
      string aMMNRYLpeA;
      string rpEtLVnoLr;
      string SOcgRDumHO;
      string hzbRyzBImZ;
      string SGIhmSSSYT;
      string mbirJLjfuO;
      string cYhQRrNmwM;
      string TeClZLGtsz;
      string kcNnbGQiIl;
      string PVMYwsYrPu;
      string EfWLzHZxSx;
      string FomwcAKtnL;
      string bedJxxRdof;
      string mNdytFGCnT;
      string fSPLgZiQuw;
      if(hjmUBmCzSX == mbirJLjfuO){ieDESZBMNB = true;}
      else if(mbirJLjfuO == hjmUBmCzSX){VwlzHekgFC = true;}
      if(jKtJVPDLMa == cYhQRrNmwM){owHmJqKoBW = true;}
      else if(cYhQRrNmwM == jKtJVPDLMa){FGrbLXRuiR = true;}
      if(aIXxoAuMtY == TeClZLGtsz){tIFUfJOScW = true;}
      else if(TeClZLGtsz == aIXxoAuMtY){ADXTRGimXx = true;}
      if(LOWFydxnif == kcNnbGQiIl){OBhswIJZeU = true;}
      else if(kcNnbGQiIl == LOWFydxnif){oXSzZBARfb = true;}
      if(IWNkoaRukb == PVMYwsYrPu){EsnldjLbBo = true;}
      else if(PVMYwsYrPu == IWNkoaRukb){jGEoQciYKk = true;}
      if(aMMNRYLpeA == EfWLzHZxSx){PtOYCZYiXJ = true;}
      else if(EfWLzHZxSx == aMMNRYLpeA){DONhpSYRgB = true;}
      if(rpEtLVnoLr == FomwcAKtnL){KiiqmmNOpB = true;}
      else if(FomwcAKtnL == rpEtLVnoLr){wxJHMhmsCK = true;}
      if(SOcgRDumHO == bedJxxRdof){gjJgSAUSpw = true;}
      if(hzbRyzBImZ == mNdytFGCnT){xlQmHUmJqW = true;}
      if(SGIhmSSSYT == fSPLgZiQuw){iaBVJUKxzq = true;}
      while(bedJxxRdof == SOcgRDumHO){XAPGhtzhCo = true;}
      while(mNdytFGCnT == mNdytFGCnT){WJbltaJkIH = true;}
      while(fSPLgZiQuw == fSPLgZiQuw){bhjdflwwbi = true;}
      if(ieDESZBMNB == true){ieDESZBMNB = false;}
      if(owHmJqKoBW == true){owHmJqKoBW = false;}
      if(tIFUfJOScW == true){tIFUfJOScW = false;}
      if(OBhswIJZeU == true){OBhswIJZeU = false;}
      if(EsnldjLbBo == true){EsnldjLbBo = false;}
      if(PtOYCZYiXJ == true){PtOYCZYiXJ = false;}
      if(KiiqmmNOpB == true){KiiqmmNOpB = false;}
      if(gjJgSAUSpw == true){gjJgSAUSpw = false;}
      if(xlQmHUmJqW == true){xlQmHUmJqW = false;}
      if(iaBVJUKxzq == true){iaBVJUKxzq = false;}
      if(VwlzHekgFC == true){VwlzHekgFC = false;}
      if(FGrbLXRuiR == true){FGrbLXRuiR = false;}
      if(ADXTRGimXx == true){ADXTRGimXx = false;}
      if(oXSzZBARfb == true){oXSzZBARfb = false;}
      if(jGEoQciYKk == true){jGEoQciYKk = false;}
      if(DONhpSYRgB == true){DONhpSYRgB = false;}
      if(wxJHMhmsCK == true){wxJHMhmsCK = false;}
      if(XAPGhtzhCo == true){XAPGhtzhCo = false;}
      if(WJbltaJkIH == true){WJbltaJkIH = false;}
      if(bhjdflwwbi == true){bhjdflwwbi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTYKUTJXCT
{ 
  void DumgbWnCIH()
  { 
      bool RqKIEssGjR = false;
      bool KVoRhYbkJA = false;
      bool JgeusrEBea = false;
      bool UVehgzonCY = false;
      bool zxfSVrIqSt = false;
      bool fqdBNkLOPL = false;
      bool nraIxnqGkh = false;
      bool inhjBLALYB = false;
      bool iMiktcrdUw = false;
      bool mZYqjGWWVg = false;
      bool ABFjKrIszC = false;
      bool jzpNbbJoOT = false;
      bool wNlouJPqzt = false;
      bool ndprAhGyaB = false;
      bool UydSLmjKOI = false;
      bool xgHCkmPQoB = false;
      bool bQsFNFJxNt = false;
      bool UKOMyyiTcH = false;
      bool YFcqwGWmHM = false;
      bool SpJYZDEXEG = false;
      string ZmuKoRkSJo;
      string SibfyxnAQK;
      string HxowkZHptO;
      string EloXjrYmBm;
      string puqVOngfkw;
      string LjWWtcyzYO;
      string JtXukgsEwG;
      string YAzdULFThw;
      string rbFxDTOScG;
      string sZOlcuWwjg;
      string ucieXKksBh;
      string WeQcWhnaqR;
      string SaaoNzlMBY;
      string oJiABPraYr;
      string hUQujNIlPt;
      string GuFSOUBtQY;
      string YYrbsNwQaG;
      string pNByixJfEz;
      string qzwGSsEPkf;
      string NxJATIcnBW;
      if(ZmuKoRkSJo == ucieXKksBh){RqKIEssGjR = true;}
      else if(ucieXKksBh == ZmuKoRkSJo){ABFjKrIszC = true;}
      if(SibfyxnAQK == WeQcWhnaqR){KVoRhYbkJA = true;}
      else if(WeQcWhnaqR == SibfyxnAQK){jzpNbbJoOT = true;}
      if(HxowkZHptO == SaaoNzlMBY){JgeusrEBea = true;}
      else if(SaaoNzlMBY == HxowkZHptO){wNlouJPqzt = true;}
      if(EloXjrYmBm == oJiABPraYr){UVehgzonCY = true;}
      else if(oJiABPraYr == EloXjrYmBm){ndprAhGyaB = true;}
      if(puqVOngfkw == hUQujNIlPt){zxfSVrIqSt = true;}
      else if(hUQujNIlPt == puqVOngfkw){UydSLmjKOI = true;}
      if(LjWWtcyzYO == GuFSOUBtQY){fqdBNkLOPL = true;}
      else if(GuFSOUBtQY == LjWWtcyzYO){xgHCkmPQoB = true;}
      if(JtXukgsEwG == YYrbsNwQaG){nraIxnqGkh = true;}
      else if(YYrbsNwQaG == JtXukgsEwG){bQsFNFJxNt = true;}
      if(YAzdULFThw == pNByixJfEz){inhjBLALYB = true;}
      if(rbFxDTOScG == qzwGSsEPkf){iMiktcrdUw = true;}
      if(sZOlcuWwjg == NxJATIcnBW){mZYqjGWWVg = true;}
      while(pNByixJfEz == YAzdULFThw){UKOMyyiTcH = true;}
      while(qzwGSsEPkf == qzwGSsEPkf){YFcqwGWmHM = true;}
      while(NxJATIcnBW == NxJATIcnBW){SpJYZDEXEG = true;}
      if(RqKIEssGjR == true){RqKIEssGjR = false;}
      if(KVoRhYbkJA == true){KVoRhYbkJA = false;}
      if(JgeusrEBea == true){JgeusrEBea = false;}
      if(UVehgzonCY == true){UVehgzonCY = false;}
      if(zxfSVrIqSt == true){zxfSVrIqSt = false;}
      if(fqdBNkLOPL == true){fqdBNkLOPL = false;}
      if(nraIxnqGkh == true){nraIxnqGkh = false;}
      if(inhjBLALYB == true){inhjBLALYB = false;}
      if(iMiktcrdUw == true){iMiktcrdUw = false;}
      if(mZYqjGWWVg == true){mZYqjGWWVg = false;}
      if(ABFjKrIszC == true){ABFjKrIszC = false;}
      if(jzpNbbJoOT == true){jzpNbbJoOT = false;}
      if(wNlouJPqzt == true){wNlouJPqzt = false;}
      if(ndprAhGyaB == true){ndprAhGyaB = false;}
      if(UydSLmjKOI == true){UydSLmjKOI = false;}
      if(xgHCkmPQoB == true){xgHCkmPQoB = false;}
      if(bQsFNFJxNt == true){bQsFNFJxNt = false;}
      if(UKOMyyiTcH == true){UKOMyyiTcH = false;}
      if(YFcqwGWmHM == true){YFcqwGWmHM = false;}
      if(SpJYZDEXEG == true){SpJYZDEXEG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKKLSIZYLU
{ 
  void jFGgupBhxh()
  { 
      bool FpQLGDDcQW = false;
      bool MeWUzOECjO = false;
      bool aUWeGXjOAj = false;
      bool pOdiwdeiGj = false;
      bool ElxIwqXEWX = false;
      bool ICaZXjTkFh = false;
      bool TncfgyBnXV = false;
      bool jUwzJnWNhO = false;
      bool zercbmmEKL = false;
      bool KscXPQJRby = false;
      bool pjgAnmGaPi = false;
      bool NFDphouzEs = false;
      bool KxcMLqrXjs = false;
      bool eFkiYPyqon = false;
      bool gMnbyEolpa = false;
      bool UJMimsGUox = false;
      bool uiqVDHUTRS = false;
      bool qDKQLyIBNH = false;
      bool BFgIYVsCwf = false;
      bool IdCrryVSXp = false;
      string MuhhUdhTwI;
      string oPSjJmNCWD;
      string jPgzDbgQQH;
      string CDzLFQdVep;
      string iUleSKgFGq;
      string CGhrhxOhdr;
      string wQCnFkPGds;
      string JrWgTPcCgr;
      string ubKYFuVHdI;
      string BuqmtSSyYh;
      string uaaNhJiBYS;
      string UMBlxUFchJ;
      string PIcVqNAjlA;
      string wecyxUAwqu;
      string MTiKnosFoZ;
      string MoPOSmxFWT;
      string JzOXVoiDoc;
      string TJllxuZRhC;
      string TuuMmHOOfJ;
      string WuZWlMEKny;
      if(MuhhUdhTwI == uaaNhJiBYS){FpQLGDDcQW = true;}
      else if(uaaNhJiBYS == MuhhUdhTwI){pjgAnmGaPi = true;}
      if(oPSjJmNCWD == UMBlxUFchJ){MeWUzOECjO = true;}
      else if(UMBlxUFchJ == oPSjJmNCWD){NFDphouzEs = true;}
      if(jPgzDbgQQH == PIcVqNAjlA){aUWeGXjOAj = true;}
      else if(PIcVqNAjlA == jPgzDbgQQH){KxcMLqrXjs = true;}
      if(CDzLFQdVep == wecyxUAwqu){pOdiwdeiGj = true;}
      else if(wecyxUAwqu == CDzLFQdVep){eFkiYPyqon = true;}
      if(iUleSKgFGq == MTiKnosFoZ){ElxIwqXEWX = true;}
      else if(MTiKnosFoZ == iUleSKgFGq){gMnbyEolpa = true;}
      if(CGhrhxOhdr == MoPOSmxFWT){ICaZXjTkFh = true;}
      else if(MoPOSmxFWT == CGhrhxOhdr){UJMimsGUox = true;}
      if(wQCnFkPGds == JzOXVoiDoc){TncfgyBnXV = true;}
      else if(JzOXVoiDoc == wQCnFkPGds){uiqVDHUTRS = true;}
      if(JrWgTPcCgr == TJllxuZRhC){jUwzJnWNhO = true;}
      if(ubKYFuVHdI == TuuMmHOOfJ){zercbmmEKL = true;}
      if(BuqmtSSyYh == WuZWlMEKny){KscXPQJRby = true;}
      while(TJllxuZRhC == JrWgTPcCgr){qDKQLyIBNH = true;}
      while(TuuMmHOOfJ == TuuMmHOOfJ){BFgIYVsCwf = true;}
      while(WuZWlMEKny == WuZWlMEKny){IdCrryVSXp = true;}
      if(FpQLGDDcQW == true){FpQLGDDcQW = false;}
      if(MeWUzOECjO == true){MeWUzOECjO = false;}
      if(aUWeGXjOAj == true){aUWeGXjOAj = false;}
      if(pOdiwdeiGj == true){pOdiwdeiGj = false;}
      if(ElxIwqXEWX == true){ElxIwqXEWX = false;}
      if(ICaZXjTkFh == true){ICaZXjTkFh = false;}
      if(TncfgyBnXV == true){TncfgyBnXV = false;}
      if(jUwzJnWNhO == true){jUwzJnWNhO = false;}
      if(zercbmmEKL == true){zercbmmEKL = false;}
      if(KscXPQJRby == true){KscXPQJRby = false;}
      if(pjgAnmGaPi == true){pjgAnmGaPi = false;}
      if(NFDphouzEs == true){NFDphouzEs = false;}
      if(KxcMLqrXjs == true){KxcMLqrXjs = false;}
      if(eFkiYPyqon == true){eFkiYPyqon = false;}
      if(gMnbyEolpa == true){gMnbyEolpa = false;}
      if(UJMimsGUox == true){UJMimsGUox = false;}
      if(uiqVDHUTRS == true){uiqVDHUTRS = false;}
      if(qDKQLyIBNH == true){qDKQLyIBNH = false;}
      if(BFgIYVsCwf == true){BFgIYVsCwf = false;}
      if(IdCrryVSXp == true){IdCrryVSXp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTFUJQSFCV
{ 
  void lSVBinWGYb()
  { 
      bool mGEOWQGiYF = false;
      bool YfKNqywbPn = false;
      bool TYEMfAjJVd = false;
      bool sUYcZTfTYz = false;
      bool CmYBoBmUTk = false;
      bool WlPaVOCqiW = false;
      bool gxMuLDGhnW = false;
      bool RcDPlfADXd = false;
      bool MOojGHEyGK = false;
      bool QnjBSFacok = false;
      bool tEfxTthzoo = false;
      bool NzTEJRHcoE = false;
      bool zIadGcrBxf = false;
      bool FWNljHirPM = false;
      bool YEJQwQUfrA = false;
      bool xynjlldCpq = false;
      bool BfCIjqkgUC = false;
      bool iPMcftzKgo = false;
      bool HMJwiHidAy = false;
      bool dfBXKrCAgF = false;
      string CZAqZDUVMM;
      string tqlsHleYqO;
      string UbsxJoUgkW;
      string bamoJhxXZe;
      string AKDEYmSNXy;
      string EnBusafChj;
      string hmkpkSDxiY;
      string nGzMOKXnYV;
      string WHJmRnZrwi;
      string BupowNYMTF;
      string jVdyKyongi;
      string CqdLNacxXw;
      string sLBAXrPJQA;
      string kLUSlBcKcS;
      string zlLMgKReaU;
      string jbnWMYTdaR;
      string ieXfxpWKZM;
      string ySUFxHznSM;
      string akhuQJWxGN;
      string gyiLjTNeOp;
      if(CZAqZDUVMM == jVdyKyongi){mGEOWQGiYF = true;}
      else if(jVdyKyongi == CZAqZDUVMM){tEfxTthzoo = true;}
      if(tqlsHleYqO == CqdLNacxXw){YfKNqywbPn = true;}
      else if(CqdLNacxXw == tqlsHleYqO){NzTEJRHcoE = true;}
      if(UbsxJoUgkW == sLBAXrPJQA){TYEMfAjJVd = true;}
      else if(sLBAXrPJQA == UbsxJoUgkW){zIadGcrBxf = true;}
      if(bamoJhxXZe == kLUSlBcKcS){sUYcZTfTYz = true;}
      else if(kLUSlBcKcS == bamoJhxXZe){FWNljHirPM = true;}
      if(AKDEYmSNXy == zlLMgKReaU){CmYBoBmUTk = true;}
      else if(zlLMgKReaU == AKDEYmSNXy){YEJQwQUfrA = true;}
      if(EnBusafChj == jbnWMYTdaR){WlPaVOCqiW = true;}
      else if(jbnWMYTdaR == EnBusafChj){xynjlldCpq = true;}
      if(hmkpkSDxiY == ieXfxpWKZM){gxMuLDGhnW = true;}
      else if(ieXfxpWKZM == hmkpkSDxiY){BfCIjqkgUC = true;}
      if(nGzMOKXnYV == ySUFxHznSM){RcDPlfADXd = true;}
      if(WHJmRnZrwi == akhuQJWxGN){MOojGHEyGK = true;}
      if(BupowNYMTF == gyiLjTNeOp){QnjBSFacok = true;}
      while(ySUFxHznSM == nGzMOKXnYV){iPMcftzKgo = true;}
      while(akhuQJWxGN == akhuQJWxGN){HMJwiHidAy = true;}
      while(gyiLjTNeOp == gyiLjTNeOp){dfBXKrCAgF = true;}
      if(mGEOWQGiYF == true){mGEOWQGiYF = false;}
      if(YfKNqywbPn == true){YfKNqywbPn = false;}
      if(TYEMfAjJVd == true){TYEMfAjJVd = false;}
      if(sUYcZTfTYz == true){sUYcZTfTYz = false;}
      if(CmYBoBmUTk == true){CmYBoBmUTk = false;}
      if(WlPaVOCqiW == true){WlPaVOCqiW = false;}
      if(gxMuLDGhnW == true){gxMuLDGhnW = false;}
      if(RcDPlfADXd == true){RcDPlfADXd = false;}
      if(MOojGHEyGK == true){MOojGHEyGK = false;}
      if(QnjBSFacok == true){QnjBSFacok = false;}
      if(tEfxTthzoo == true){tEfxTthzoo = false;}
      if(NzTEJRHcoE == true){NzTEJRHcoE = false;}
      if(zIadGcrBxf == true){zIadGcrBxf = false;}
      if(FWNljHirPM == true){FWNljHirPM = false;}
      if(YEJQwQUfrA == true){YEJQwQUfrA = false;}
      if(xynjlldCpq == true){xynjlldCpq = false;}
      if(BfCIjqkgUC == true){BfCIjqkgUC = false;}
      if(iPMcftzKgo == true){iPMcftzKgo = false;}
      if(HMJwiHidAy == true){HMJwiHidAy = false;}
      if(dfBXKrCAgF == true){dfBXKrCAgF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIECKEPKLV
{ 
  void GDyiYjiHqR()
  { 
      bool AsgpcyqUSC = false;
      bool UtNkRwdNWL = false;
      bool dbFYJcTpTA = false;
      bool XBWEbxgcwO = false;
      bool VOgeIShsam = false;
      bool oAfnuXmIgA = false;
      bool dABSeTWIJT = false;
      bool OAQIpPuaQp = false;
      bool taPfKWViID = false;
      bool JYuujUMOzn = false;
      bool wZiGXniWxf = false;
      bool cMrpFDjUHH = false;
      bool ymzFJpEUXU = false;
      bool CgabtUqJHV = false;
      bool mylcaxgFpg = false;
      bool jqGqpIZdwh = false;
      bool jNybcwlPwk = false;
      bool MaNkUzBWeM = false;
      bool JzeqjKZill = false;
      bool tNMYlZzJAd = false;
      string EXdinpQsJC;
      string VpZdzKFMSd;
      string WGFXIqeSbE;
      string YUSrFHwQNa;
      string jabzanwgJt;
      string ycGmHySGax;
      string KyQEdAWgXr;
      string NnyrtwdFwU;
      string txIgFuOfjG;
      string nppQPkJWUZ;
      string QOIQfKeOsL;
      string TMJFCNojyi;
      string lqwQDXyhbI;
      string lHkVDfnqAu;
      string PAmYmbgjNC;
      string wZXknZRrNI;
      string LxljYMbmCW;
      string YyiDSkEXdb;
      string qOTYMMizhd;
      string NwdrjSNCAZ;
      if(EXdinpQsJC == QOIQfKeOsL){AsgpcyqUSC = true;}
      else if(QOIQfKeOsL == EXdinpQsJC){wZiGXniWxf = true;}
      if(VpZdzKFMSd == TMJFCNojyi){UtNkRwdNWL = true;}
      else if(TMJFCNojyi == VpZdzKFMSd){cMrpFDjUHH = true;}
      if(WGFXIqeSbE == lqwQDXyhbI){dbFYJcTpTA = true;}
      else if(lqwQDXyhbI == WGFXIqeSbE){ymzFJpEUXU = true;}
      if(YUSrFHwQNa == lHkVDfnqAu){XBWEbxgcwO = true;}
      else if(lHkVDfnqAu == YUSrFHwQNa){CgabtUqJHV = true;}
      if(jabzanwgJt == PAmYmbgjNC){VOgeIShsam = true;}
      else if(PAmYmbgjNC == jabzanwgJt){mylcaxgFpg = true;}
      if(ycGmHySGax == wZXknZRrNI){oAfnuXmIgA = true;}
      else if(wZXknZRrNI == ycGmHySGax){jqGqpIZdwh = true;}
      if(KyQEdAWgXr == LxljYMbmCW){dABSeTWIJT = true;}
      else if(LxljYMbmCW == KyQEdAWgXr){jNybcwlPwk = true;}
      if(NnyrtwdFwU == YyiDSkEXdb){OAQIpPuaQp = true;}
      if(txIgFuOfjG == qOTYMMizhd){taPfKWViID = true;}
      if(nppQPkJWUZ == NwdrjSNCAZ){JYuujUMOzn = true;}
      while(YyiDSkEXdb == NnyrtwdFwU){MaNkUzBWeM = true;}
      while(qOTYMMizhd == qOTYMMizhd){JzeqjKZill = true;}
      while(NwdrjSNCAZ == NwdrjSNCAZ){tNMYlZzJAd = true;}
      if(AsgpcyqUSC == true){AsgpcyqUSC = false;}
      if(UtNkRwdNWL == true){UtNkRwdNWL = false;}
      if(dbFYJcTpTA == true){dbFYJcTpTA = false;}
      if(XBWEbxgcwO == true){XBWEbxgcwO = false;}
      if(VOgeIShsam == true){VOgeIShsam = false;}
      if(oAfnuXmIgA == true){oAfnuXmIgA = false;}
      if(dABSeTWIJT == true){dABSeTWIJT = false;}
      if(OAQIpPuaQp == true){OAQIpPuaQp = false;}
      if(taPfKWViID == true){taPfKWViID = false;}
      if(JYuujUMOzn == true){JYuujUMOzn = false;}
      if(wZiGXniWxf == true){wZiGXniWxf = false;}
      if(cMrpFDjUHH == true){cMrpFDjUHH = false;}
      if(ymzFJpEUXU == true){ymzFJpEUXU = false;}
      if(CgabtUqJHV == true){CgabtUqJHV = false;}
      if(mylcaxgFpg == true){mylcaxgFpg = false;}
      if(jqGqpIZdwh == true){jqGqpIZdwh = false;}
      if(jNybcwlPwk == true){jNybcwlPwk = false;}
      if(MaNkUzBWeM == true){MaNkUzBWeM = false;}
      if(JzeqjKZill == true){JzeqjKZill = false;}
      if(tNMYlZzJAd == true){tNMYlZzJAd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LECDKRYTVS
{ 
  void hYeDADIreq()
  { 
      bool WmWVuMTHMl = false;
      bool ZPQOUaqOLZ = false;
      bool XQBhHKSaXS = false;
      bool zQGnYClhIu = false;
      bool utjPeraWHO = false;
      bool UEhhQGlnNj = false;
      bool trislIIbpR = false;
      bool oJFPdcfkDP = false;
      bool iwSJyuhYWS = false;
      bool QxTYBCLqdV = false;
      bool izgpYLzREn = false;
      bool ZAkxAxYYuq = false;
      bool ajEWBrogOa = false;
      bool RoHggjPckl = false;
      bool uPTirPLWXD = false;
      bool dluluytJog = false;
      bool WRDcWksDQQ = false;
      bool hunIuKPVek = false;
      bool fSJLxesUli = false;
      bool oGnDPcMqLG = false;
      string pJJSjYwZyk;
      string RemAoJSygC;
      string oIiiqEOFDh;
      string FJxDtQbNUu;
      string JlZLRraqQY;
      string GNEnegaabf;
      string KpWPfIhjFX;
      string gEcksDiWQz;
      string dWoebrEIXN;
      string pBlnjSPKfJ;
      string JplrqBjStb;
      string yEKcCmBrnm;
      string EYLrhfRoAZ;
      string mYpHomkwmZ;
      string HkOwOkpJkx;
      string RXVrEkesKK;
      string juRTnZODmP;
      string CEEOfSKOcw;
      string pIDDIOCxCE;
      string HqkcpMStHo;
      if(pJJSjYwZyk == JplrqBjStb){WmWVuMTHMl = true;}
      else if(JplrqBjStb == pJJSjYwZyk){izgpYLzREn = true;}
      if(RemAoJSygC == yEKcCmBrnm){ZPQOUaqOLZ = true;}
      else if(yEKcCmBrnm == RemAoJSygC){ZAkxAxYYuq = true;}
      if(oIiiqEOFDh == EYLrhfRoAZ){XQBhHKSaXS = true;}
      else if(EYLrhfRoAZ == oIiiqEOFDh){ajEWBrogOa = true;}
      if(FJxDtQbNUu == mYpHomkwmZ){zQGnYClhIu = true;}
      else if(mYpHomkwmZ == FJxDtQbNUu){RoHggjPckl = true;}
      if(JlZLRraqQY == HkOwOkpJkx){utjPeraWHO = true;}
      else if(HkOwOkpJkx == JlZLRraqQY){uPTirPLWXD = true;}
      if(GNEnegaabf == RXVrEkesKK){UEhhQGlnNj = true;}
      else if(RXVrEkesKK == GNEnegaabf){dluluytJog = true;}
      if(KpWPfIhjFX == juRTnZODmP){trislIIbpR = true;}
      else if(juRTnZODmP == KpWPfIhjFX){WRDcWksDQQ = true;}
      if(gEcksDiWQz == CEEOfSKOcw){oJFPdcfkDP = true;}
      if(dWoebrEIXN == pIDDIOCxCE){iwSJyuhYWS = true;}
      if(pBlnjSPKfJ == HqkcpMStHo){QxTYBCLqdV = true;}
      while(CEEOfSKOcw == gEcksDiWQz){hunIuKPVek = true;}
      while(pIDDIOCxCE == pIDDIOCxCE){fSJLxesUli = true;}
      while(HqkcpMStHo == HqkcpMStHo){oGnDPcMqLG = true;}
      if(WmWVuMTHMl == true){WmWVuMTHMl = false;}
      if(ZPQOUaqOLZ == true){ZPQOUaqOLZ = false;}
      if(XQBhHKSaXS == true){XQBhHKSaXS = false;}
      if(zQGnYClhIu == true){zQGnYClhIu = false;}
      if(utjPeraWHO == true){utjPeraWHO = false;}
      if(UEhhQGlnNj == true){UEhhQGlnNj = false;}
      if(trislIIbpR == true){trislIIbpR = false;}
      if(oJFPdcfkDP == true){oJFPdcfkDP = false;}
      if(iwSJyuhYWS == true){iwSJyuhYWS = false;}
      if(QxTYBCLqdV == true){QxTYBCLqdV = false;}
      if(izgpYLzREn == true){izgpYLzREn = false;}
      if(ZAkxAxYYuq == true){ZAkxAxYYuq = false;}
      if(ajEWBrogOa == true){ajEWBrogOa = false;}
      if(RoHggjPckl == true){RoHggjPckl = false;}
      if(uPTirPLWXD == true){uPTirPLWXD = false;}
      if(dluluytJog == true){dluluytJog = false;}
      if(WRDcWksDQQ == true){WRDcWksDQQ = false;}
      if(hunIuKPVek == true){hunIuKPVek = false;}
      if(fSJLxesUli == true){fSJLxesUli = false;}
      if(oGnDPcMqLG == true){oGnDPcMqLG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIREADOQGF
{ 
  void qfHVsAguAa()
  { 
      bool HtkhVkakoA = false;
      bool gVUrQXJmgY = false;
      bool ONjuaIjolZ = false;
      bool qRDyEjIHxP = false;
      bool lDtlEzkOFm = false;
      bool lpdNzsKpGN = false;
      bool AlzPIPRVmg = false;
      bool PCpQlLSxpa = false;
      bool WViynAmpyK = false;
      bool YRAiPADedo = false;
      bool gPaYWiANbn = false;
      bool ZNAfqdCAaH = false;
      bool bbWbHxBGBl = false;
      bool HnTAsGuKaE = false;
      bool AZNKjLRUrk = false;
      bool xCDVNFryQZ = false;
      bool gtLoflszlj = false;
      bool iqZVHCNMqu = false;
      bool fgNPnFkymn = false;
      bool OwtBXFNYey = false;
      string SGLyzjwaVw;
      string jEqRhxMZcS;
      string VPlApLhPoq;
      string NoaQuSGEwn;
      string KDlLTLBijg;
      string lxxUFDTLHn;
      string BglehudaWP;
      string pIcoHScZfd;
      string JzeHFPqGLq;
      string yuwIldRGdY;
      string haMUpcTIMm;
      string ZseddCBdYR;
      string DXOeQuLUCd;
      string AWwHwhmKRb;
      string uitYREQSej;
      string bmhLUKMgDu;
      string RzFhlDxWgw;
      string OqLwVUcpML;
      string dsoSBNnjml;
      string VGGWKwcLlO;
      if(SGLyzjwaVw == haMUpcTIMm){HtkhVkakoA = true;}
      else if(haMUpcTIMm == SGLyzjwaVw){gPaYWiANbn = true;}
      if(jEqRhxMZcS == ZseddCBdYR){gVUrQXJmgY = true;}
      else if(ZseddCBdYR == jEqRhxMZcS){ZNAfqdCAaH = true;}
      if(VPlApLhPoq == DXOeQuLUCd){ONjuaIjolZ = true;}
      else if(DXOeQuLUCd == VPlApLhPoq){bbWbHxBGBl = true;}
      if(NoaQuSGEwn == AWwHwhmKRb){qRDyEjIHxP = true;}
      else if(AWwHwhmKRb == NoaQuSGEwn){HnTAsGuKaE = true;}
      if(KDlLTLBijg == uitYREQSej){lDtlEzkOFm = true;}
      else if(uitYREQSej == KDlLTLBijg){AZNKjLRUrk = true;}
      if(lxxUFDTLHn == bmhLUKMgDu){lpdNzsKpGN = true;}
      else if(bmhLUKMgDu == lxxUFDTLHn){xCDVNFryQZ = true;}
      if(BglehudaWP == RzFhlDxWgw){AlzPIPRVmg = true;}
      else if(RzFhlDxWgw == BglehudaWP){gtLoflszlj = true;}
      if(pIcoHScZfd == OqLwVUcpML){PCpQlLSxpa = true;}
      if(JzeHFPqGLq == dsoSBNnjml){WViynAmpyK = true;}
      if(yuwIldRGdY == VGGWKwcLlO){YRAiPADedo = true;}
      while(OqLwVUcpML == pIcoHScZfd){iqZVHCNMqu = true;}
      while(dsoSBNnjml == dsoSBNnjml){fgNPnFkymn = true;}
      while(VGGWKwcLlO == VGGWKwcLlO){OwtBXFNYey = true;}
      if(HtkhVkakoA == true){HtkhVkakoA = false;}
      if(gVUrQXJmgY == true){gVUrQXJmgY = false;}
      if(ONjuaIjolZ == true){ONjuaIjolZ = false;}
      if(qRDyEjIHxP == true){qRDyEjIHxP = false;}
      if(lDtlEzkOFm == true){lDtlEzkOFm = false;}
      if(lpdNzsKpGN == true){lpdNzsKpGN = false;}
      if(AlzPIPRVmg == true){AlzPIPRVmg = false;}
      if(PCpQlLSxpa == true){PCpQlLSxpa = false;}
      if(WViynAmpyK == true){WViynAmpyK = false;}
      if(YRAiPADedo == true){YRAiPADedo = false;}
      if(gPaYWiANbn == true){gPaYWiANbn = false;}
      if(ZNAfqdCAaH == true){ZNAfqdCAaH = false;}
      if(bbWbHxBGBl == true){bbWbHxBGBl = false;}
      if(HnTAsGuKaE == true){HnTAsGuKaE = false;}
      if(AZNKjLRUrk == true){AZNKjLRUrk = false;}
      if(xCDVNFryQZ == true){xCDVNFryQZ = false;}
      if(gtLoflszlj == true){gtLoflszlj = false;}
      if(iqZVHCNMqu == true){iqZVHCNMqu = false;}
      if(fgNPnFkymn == true){fgNPnFkymn = false;}
      if(OwtBXFNYey == true){OwtBXFNYey = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNRPMBGPZA
{ 
  void UeDKAKYUtY()
  { 
      bool RmKePyUOIE = false;
      bool SfteCJHEts = false;
      bool kofBegNWQT = false;
      bool icrslnjJSr = false;
      bool XgrigaVlOm = false;
      bool aDLWFcGJzi = false;
      bool jxynUonBrN = false;
      bool ZylCVEwwUD = false;
      bool LbIdsfQVnJ = false;
      bool haJiHZhEOq = false;
      bool lTsAMbRJBB = false;
      bool gKnwXIoTto = false;
      bool YSNifzoCtu = false;
      bool VqhcQqiIRQ = false;
      bool NGTlcWlMLz = false;
      bool jOJYSTGJTN = false;
      bool mPPFfobLeg = false;
      bool YgBdaRyaGI = false;
      bool MbpuLGgIKx = false;
      bool jYnEdyqOGm = false;
      string PWxQWfkLfG;
      string lyelldakiK;
      string mqOYftFKQA;
      string pRbdBQjCdg;
      string ioXJDzzWPH;
      string lJlfmYHYkc;
      string aZtePTVBkU;
      string tYGCbxSFUf;
      string thuJOgfuqc;
      string JLRAGIussj;
      string cyltNMCjEo;
      string FBEEirekPh;
      string naJHLiHGwT;
      string CYLjCwuAwB;
      string ewqCWHGMRN;
      string cJcLwCneie;
      string FwmjlgoTBm;
      string xeoNDrjHjD;
      string bunipsuAnA;
      string HQQRwiIGPp;
      if(PWxQWfkLfG == cyltNMCjEo){RmKePyUOIE = true;}
      else if(cyltNMCjEo == PWxQWfkLfG){lTsAMbRJBB = true;}
      if(lyelldakiK == FBEEirekPh){SfteCJHEts = true;}
      else if(FBEEirekPh == lyelldakiK){gKnwXIoTto = true;}
      if(mqOYftFKQA == naJHLiHGwT){kofBegNWQT = true;}
      else if(naJHLiHGwT == mqOYftFKQA){YSNifzoCtu = true;}
      if(pRbdBQjCdg == CYLjCwuAwB){icrslnjJSr = true;}
      else if(CYLjCwuAwB == pRbdBQjCdg){VqhcQqiIRQ = true;}
      if(ioXJDzzWPH == ewqCWHGMRN){XgrigaVlOm = true;}
      else if(ewqCWHGMRN == ioXJDzzWPH){NGTlcWlMLz = true;}
      if(lJlfmYHYkc == cJcLwCneie){aDLWFcGJzi = true;}
      else if(cJcLwCneie == lJlfmYHYkc){jOJYSTGJTN = true;}
      if(aZtePTVBkU == FwmjlgoTBm){jxynUonBrN = true;}
      else if(FwmjlgoTBm == aZtePTVBkU){mPPFfobLeg = true;}
      if(tYGCbxSFUf == xeoNDrjHjD){ZylCVEwwUD = true;}
      if(thuJOgfuqc == bunipsuAnA){LbIdsfQVnJ = true;}
      if(JLRAGIussj == HQQRwiIGPp){haJiHZhEOq = true;}
      while(xeoNDrjHjD == tYGCbxSFUf){YgBdaRyaGI = true;}
      while(bunipsuAnA == bunipsuAnA){MbpuLGgIKx = true;}
      while(HQQRwiIGPp == HQQRwiIGPp){jYnEdyqOGm = true;}
      if(RmKePyUOIE == true){RmKePyUOIE = false;}
      if(SfteCJHEts == true){SfteCJHEts = false;}
      if(kofBegNWQT == true){kofBegNWQT = false;}
      if(icrslnjJSr == true){icrslnjJSr = false;}
      if(XgrigaVlOm == true){XgrigaVlOm = false;}
      if(aDLWFcGJzi == true){aDLWFcGJzi = false;}
      if(jxynUonBrN == true){jxynUonBrN = false;}
      if(ZylCVEwwUD == true){ZylCVEwwUD = false;}
      if(LbIdsfQVnJ == true){LbIdsfQVnJ = false;}
      if(haJiHZhEOq == true){haJiHZhEOq = false;}
      if(lTsAMbRJBB == true){lTsAMbRJBB = false;}
      if(gKnwXIoTto == true){gKnwXIoTto = false;}
      if(YSNifzoCtu == true){YSNifzoCtu = false;}
      if(VqhcQqiIRQ == true){VqhcQqiIRQ = false;}
      if(NGTlcWlMLz == true){NGTlcWlMLz = false;}
      if(jOJYSTGJTN == true){jOJYSTGJTN = false;}
      if(mPPFfobLeg == true){mPPFfobLeg = false;}
      if(YgBdaRyaGI == true){YgBdaRyaGI = false;}
      if(MbpuLGgIKx == true){MbpuLGgIKx = false;}
      if(jYnEdyqOGm == true){jYnEdyqOGm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYWRJWABPC
{ 
  void jIJrlHUlkL()
  { 
      bool EHlALNDVpY = false;
      bool eLDTnuLUhe = false;
      bool jNXlgtJEPx = false;
      bool PKhtmXbjtQ = false;
      bool lSHIcCOytE = false;
      bool YsprVqizSQ = false;
      bool DyFrIUdIfP = false;
      bool TaZQsRGPJd = false;
      bool fKKLYWUoYw = false;
      bool nbQdMmMOzI = false;
      bool XFSdjySYyD = false;
      bool jTpojsmtTl = false;
      bool zoijbrJuDG = false;
      bool FqPAGZrgbZ = false;
      bool DupVLTlbsT = false;
      bool zSuMIiWhBq = false;
      bool oWVrysDoiK = false;
      bool AGRshEyNXI = false;
      bool FgCiGmwCrW = false;
      bool DKfjkfZyWS = false;
      string TKlxVieKyM;
      string wKmXqrPxaX;
      string fiToazwXNL;
      string niWxOlyVsq;
      string EYyLiWErYD;
      string yeoCGjpwWW;
      string lGwmXMnoJE;
      string ssDjTHkIGE;
      string uEzKNItTqd;
      string wCzWFxbKmV;
      string hOiTJEbFiz;
      string zgpRahHlYO;
      string STxeIqtfdV;
      string eZVjWfUeAJ;
      string fokrePMguX;
      string polXDNRDLS;
      string JwaNUYKFuu;
      string MblPhdiFAr;
      string eNkGeonxgI;
      string ORShAjNXXF;
      if(TKlxVieKyM == hOiTJEbFiz){EHlALNDVpY = true;}
      else if(hOiTJEbFiz == TKlxVieKyM){XFSdjySYyD = true;}
      if(wKmXqrPxaX == zgpRahHlYO){eLDTnuLUhe = true;}
      else if(zgpRahHlYO == wKmXqrPxaX){jTpojsmtTl = true;}
      if(fiToazwXNL == STxeIqtfdV){jNXlgtJEPx = true;}
      else if(STxeIqtfdV == fiToazwXNL){zoijbrJuDG = true;}
      if(niWxOlyVsq == eZVjWfUeAJ){PKhtmXbjtQ = true;}
      else if(eZVjWfUeAJ == niWxOlyVsq){FqPAGZrgbZ = true;}
      if(EYyLiWErYD == fokrePMguX){lSHIcCOytE = true;}
      else if(fokrePMguX == EYyLiWErYD){DupVLTlbsT = true;}
      if(yeoCGjpwWW == polXDNRDLS){YsprVqizSQ = true;}
      else if(polXDNRDLS == yeoCGjpwWW){zSuMIiWhBq = true;}
      if(lGwmXMnoJE == JwaNUYKFuu){DyFrIUdIfP = true;}
      else if(JwaNUYKFuu == lGwmXMnoJE){oWVrysDoiK = true;}
      if(ssDjTHkIGE == MblPhdiFAr){TaZQsRGPJd = true;}
      if(uEzKNItTqd == eNkGeonxgI){fKKLYWUoYw = true;}
      if(wCzWFxbKmV == ORShAjNXXF){nbQdMmMOzI = true;}
      while(MblPhdiFAr == ssDjTHkIGE){AGRshEyNXI = true;}
      while(eNkGeonxgI == eNkGeonxgI){FgCiGmwCrW = true;}
      while(ORShAjNXXF == ORShAjNXXF){DKfjkfZyWS = true;}
      if(EHlALNDVpY == true){EHlALNDVpY = false;}
      if(eLDTnuLUhe == true){eLDTnuLUhe = false;}
      if(jNXlgtJEPx == true){jNXlgtJEPx = false;}
      if(PKhtmXbjtQ == true){PKhtmXbjtQ = false;}
      if(lSHIcCOytE == true){lSHIcCOytE = false;}
      if(YsprVqizSQ == true){YsprVqizSQ = false;}
      if(DyFrIUdIfP == true){DyFrIUdIfP = false;}
      if(TaZQsRGPJd == true){TaZQsRGPJd = false;}
      if(fKKLYWUoYw == true){fKKLYWUoYw = false;}
      if(nbQdMmMOzI == true){nbQdMmMOzI = false;}
      if(XFSdjySYyD == true){XFSdjySYyD = false;}
      if(jTpojsmtTl == true){jTpojsmtTl = false;}
      if(zoijbrJuDG == true){zoijbrJuDG = false;}
      if(FqPAGZrgbZ == true){FqPAGZrgbZ = false;}
      if(DupVLTlbsT == true){DupVLTlbsT = false;}
      if(zSuMIiWhBq == true){zSuMIiWhBq = false;}
      if(oWVrysDoiK == true){oWVrysDoiK = false;}
      if(AGRshEyNXI == true){AGRshEyNXI = false;}
      if(FgCiGmwCrW == true){FgCiGmwCrW = false;}
      if(DKfjkfZyWS == true){DKfjkfZyWS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDFVVPJDBI
{ 
  void QIRcLPKPAE()
  { 
      bool khKFBwANBn = false;
      bool ZsQMoaoAxg = false;
      bool QITkpkaVSF = false;
      bool OTfetPJSDc = false;
      bool eqqOLYPeMC = false;
      bool VfZcQbOYPQ = false;
      bool VetwZGNkSZ = false;
      bool QWwTCYQEZQ = false;
      bool VwJPihsCOR = false;
      bool AkCmHAwuoE = false;
      bool LdMllzjFaq = false;
      bool LKzytYVdMr = false;
      bool NKWAZfTIMC = false;
      bool bVPUFriWdj = false;
      bool ymaXGpkEsh = false;
      bool dSiwqAHLMF = false;
      bool easYOotdrC = false;
      bool pyAbsZjyti = false;
      bool tPPdXJlScE = false;
      bool kWJXFXtCJQ = false;
      string sqlgNdLiVI;
      string NUDVHABwqS;
      string TOEVADASpe;
      string oObyRofpjX;
      string LdVeQtDxaK;
      string JNxUHdmPgK;
      string dsrqTzrEDS;
      string TLLSHpsYFF;
      string ACqfVbQHpn;
      string BQIYtRkeLR;
      string CysIqxBdMR;
      string kOKaKaBMUr;
      string hkOPQDCmYp;
      string EOMmDBJioY;
      string ZltXDlFhOS;
      string PYJTjQicqm;
      string uNFWNVBWXI;
      string RSXwRuppMe;
      string xTYFZfEsDl;
      string RfqBcLgWKg;
      if(sqlgNdLiVI == CysIqxBdMR){khKFBwANBn = true;}
      else if(CysIqxBdMR == sqlgNdLiVI){LdMllzjFaq = true;}
      if(NUDVHABwqS == kOKaKaBMUr){ZsQMoaoAxg = true;}
      else if(kOKaKaBMUr == NUDVHABwqS){LKzytYVdMr = true;}
      if(TOEVADASpe == hkOPQDCmYp){QITkpkaVSF = true;}
      else if(hkOPQDCmYp == TOEVADASpe){NKWAZfTIMC = true;}
      if(oObyRofpjX == EOMmDBJioY){OTfetPJSDc = true;}
      else if(EOMmDBJioY == oObyRofpjX){bVPUFriWdj = true;}
      if(LdVeQtDxaK == ZltXDlFhOS){eqqOLYPeMC = true;}
      else if(ZltXDlFhOS == LdVeQtDxaK){ymaXGpkEsh = true;}
      if(JNxUHdmPgK == PYJTjQicqm){VfZcQbOYPQ = true;}
      else if(PYJTjQicqm == JNxUHdmPgK){dSiwqAHLMF = true;}
      if(dsrqTzrEDS == uNFWNVBWXI){VetwZGNkSZ = true;}
      else if(uNFWNVBWXI == dsrqTzrEDS){easYOotdrC = true;}
      if(TLLSHpsYFF == RSXwRuppMe){QWwTCYQEZQ = true;}
      if(ACqfVbQHpn == xTYFZfEsDl){VwJPihsCOR = true;}
      if(BQIYtRkeLR == RfqBcLgWKg){AkCmHAwuoE = true;}
      while(RSXwRuppMe == TLLSHpsYFF){pyAbsZjyti = true;}
      while(xTYFZfEsDl == xTYFZfEsDl){tPPdXJlScE = true;}
      while(RfqBcLgWKg == RfqBcLgWKg){kWJXFXtCJQ = true;}
      if(khKFBwANBn == true){khKFBwANBn = false;}
      if(ZsQMoaoAxg == true){ZsQMoaoAxg = false;}
      if(QITkpkaVSF == true){QITkpkaVSF = false;}
      if(OTfetPJSDc == true){OTfetPJSDc = false;}
      if(eqqOLYPeMC == true){eqqOLYPeMC = false;}
      if(VfZcQbOYPQ == true){VfZcQbOYPQ = false;}
      if(VetwZGNkSZ == true){VetwZGNkSZ = false;}
      if(QWwTCYQEZQ == true){QWwTCYQEZQ = false;}
      if(VwJPihsCOR == true){VwJPihsCOR = false;}
      if(AkCmHAwuoE == true){AkCmHAwuoE = false;}
      if(LdMllzjFaq == true){LdMllzjFaq = false;}
      if(LKzytYVdMr == true){LKzytYVdMr = false;}
      if(NKWAZfTIMC == true){NKWAZfTIMC = false;}
      if(bVPUFriWdj == true){bVPUFriWdj = false;}
      if(ymaXGpkEsh == true){ymaXGpkEsh = false;}
      if(dSiwqAHLMF == true){dSiwqAHLMF = false;}
      if(easYOotdrC == true){easYOotdrC = false;}
      if(pyAbsZjyti == true){pyAbsZjyti = false;}
      if(tPPdXJlScE == true){tPPdXJlScE = false;}
      if(kWJXFXtCJQ == true){kWJXFXtCJQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POWNKTEVFV
{ 
  void kAYAkIVyYd()
  { 
      bool YPqeZgIfjW = false;
      bool CVybaajkHq = false;
      bool YKqPuWmNXG = false;
      bool YTnNplUyDl = false;
      bool taEOYrsHaE = false;
      bool IqCTFNYajC = false;
      bool ttIdxigkko = false;
      bool FlhVwxGbqC = false;
      bool demSyhQUHc = false;
      bool NtOAqASaRo = false;
      bool KHVlyVJgWI = false;
      bool HwigXPGoeP = false;
      bool RLcIbLXheu = false;
      bool deKBrVIBTb = false;
      bool YjyyUQKgba = false;
      bool scuBXyeNKl = false;
      bool yaCaeckgnB = false;
      bool HFUDqgNdnK = false;
      bool BpFDCAiIds = false;
      bool quphcxhWTq = false;
      string tUaFHneqcF;
      string aJMtNUPhUj;
      string FXmKBGMXwI;
      string QKJkGcumiO;
      string JMZciwziPw;
      string JelYNWgPEA;
      string bGtUoQzanj;
      string ZczFasxKbE;
      string HdHAzkXjXj;
      string ufhhmCRFmR;
      string wXtfVgegyU;
      string YWmzsyytVE;
      string sPCDnttRSX;
      string arWKIiibdR;
      string FqkDLYrhno;
      string EXjhYgUqrb;
      string lNOasgzcqJ;
      string OWPDyBdzrP;
      string BLccSCHnka;
      string OqjBercKKe;
      if(tUaFHneqcF == wXtfVgegyU){YPqeZgIfjW = true;}
      else if(wXtfVgegyU == tUaFHneqcF){KHVlyVJgWI = true;}
      if(aJMtNUPhUj == YWmzsyytVE){CVybaajkHq = true;}
      else if(YWmzsyytVE == aJMtNUPhUj){HwigXPGoeP = true;}
      if(FXmKBGMXwI == sPCDnttRSX){YKqPuWmNXG = true;}
      else if(sPCDnttRSX == FXmKBGMXwI){RLcIbLXheu = true;}
      if(QKJkGcumiO == arWKIiibdR){YTnNplUyDl = true;}
      else if(arWKIiibdR == QKJkGcumiO){deKBrVIBTb = true;}
      if(JMZciwziPw == FqkDLYrhno){taEOYrsHaE = true;}
      else if(FqkDLYrhno == JMZciwziPw){YjyyUQKgba = true;}
      if(JelYNWgPEA == EXjhYgUqrb){IqCTFNYajC = true;}
      else if(EXjhYgUqrb == JelYNWgPEA){scuBXyeNKl = true;}
      if(bGtUoQzanj == lNOasgzcqJ){ttIdxigkko = true;}
      else if(lNOasgzcqJ == bGtUoQzanj){yaCaeckgnB = true;}
      if(ZczFasxKbE == OWPDyBdzrP){FlhVwxGbqC = true;}
      if(HdHAzkXjXj == BLccSCHnka){demSyhQUHc = true;}
      if(ufhhmCRFmR == OqjBercKKe){NtOAqASaRo = true;}
      while(OWPDyBdzrP == ZczFasxKbE){HFUDqgNdnK = true;}
      while(BLccSCHnka == BLccSCHnka){BpFDCAiIds = true;}
      while(OqjBercKKe == OqjBercKKe){quphcxhWTq = true;}
      if(YPqeZgIfjW == true){YPqeZgIfjW = false;}
      if(CVybaajkHq == true){CVybaajkHq = false;}
      if(YKqPuWmNXG == true){YKqPuWmNXG = false;}
      if(YTnNplUyDl == true){YTnNplUyDl = false;}
      if(taEOYrsHaE == true){taEOYrsHaE = false;}
      if(IqCTFNYajC == true){IqCTFNYajC = false;}
      if(ttIdxigkko == true){ttIdxigkko = false;}
      if(FlhVwxGbqC == true){FlhVwxGbqC = false;}
      if(demSyhQUHc == true){demSyhQUHc = false;}
      if(NtOAqASaRo == true){NtOAqASaRo = false;}
      if(KHVlyVJgWI == true){KHVlyVJgWI = false;}
      if(HwigXPGoeP == true){HwigXPGoeP = false;}
      if(RLcIbLXheu == true){RLcIbLXheu = false;}
      if(deKBrVIBTb == true){deKBrVIBTb = false;}
      if(YjyyUQKgba == true){YjyyUQKgba = false;}
      if(scuBXyeNKl == true){scuBXyeNKl = false;}
      if(yaCaeckgnB == true){yaCaeckgnB = false;}
      if(HFUDqgNdnK == true){HFUDqgNdnK = false;}
      if(BpFDCAiIds == true){BpFDCAiIds = false;}
      if(quphcxhWTq == true){quphcxhWTq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGDRPGYURP
{ 
  void cTrJpGQTNh()
  { 
      bool rSxKILxPmd = false;
      bool KhDpiMrgCr = false;
      bool OOxgmNDyYU = false;
      bool UbdtiUlbmo = false;
      bool lhlwOEQBWC = false;
      bool fXUoWdUQWu = false;
      bool IzqSIhDIHO = false;
      bool aQtNFfbBSh = false;
      bool wCbWoxHnXF = false;
      bool zVEqgmqTmf = false;
      bool BHsHbOdHjp = false;
      bool BTxoyFWUcL = false;
      bool aOkCOELCgS = false;
      bool oHNlgoJTtZ = false;
      bool SAEhDfXPra = false;
      bool PWqbFmWqsW = false;
      bool CaZRAsFLHJ = false;
      bool wDZCraJCyi = false;
      bool gwKFDSQlgs = false;
      bool SRaXWqZmhJ = false;
      string XCusIjhLBZ;
      string doFfwCoGxV;
      string TBTEdGdtzI;
      string VZWKkKhIsh;
      string AwwhPFKJKV;
      string OPdhlVhpOC;
      string FnLrDDRttk;
      string UfNOUWFloY;
      string wTidsGwoYP;
      string cqspcMjDeL;
      string nPPZAhCOMO;
      string PwBpGlEhzx;
      string HcVeHdlWlI;
      string mCHdjfEJcK;
      string DgbJzgpDjp;
      string HCEgDLtjRW;
      string wecDbNnXFZ;
      string guEnsZALfa;
      string miluBjyZZY;
      string lTqGOYEXhk;
      if(XCusIjhLBZ == nPPZAhCOMO){rSxKILxPmd = true;}
      else if(nPPZAhCOMO == XCusIjhLBZ){BHsHbOdHjp = true;}
      if(doFfwCoGxV == PwBpGlEhzx){KhDpiMrgCr = true;}
      else if(PwBpGlEhzx == doFfwCoGxV){BTxoyFWUcL = true;}
      if(TBTEdGdtzI == HcVeHdlWlI){OOxgmNDyYU = true;}
      else if(HcVeHdlWlI == TBTEdGdtzI){aOkCOELCgS = true;}
      if(VZWKkKhIsh == mCHdjfEJcK){UbdtiUlbmo = true;}
      else if(mCHdjfEJcK == VZWKkKhIsh){oHNlgoJTtZ = true;}
      if(AwwhPFKJKV == DgbJzgpDjp){lhlwOEQBWC = true;}
      else if(DgbJzgpDjp == AwwhPFKJKV){SAEhDfXPra = true;}
      if(OPdhlVhpOC == HCEgDLtjRW){fXUoWdUQWu = true;}
      else if(HCEgDLtjRW == OPdhlVhpOC){PWqbFmWqsW = true;}
      if(FnLrDDRttk == wecDbNnXFZ){IzqSIhDIHO = true;}
      else if(wecDbNnXFZ == FnLrDDRttk){CaZRAsFLHJ = true;}
      if(UfNOUWFloY == guEnsZALfa){aQtNFfbBSh = true;}
      if(wTidsGwoYP == miluBjyZZY){wCbWoxHnXF = true;}
      if(cqspcMjDeL == lTqGOYEXhk){zVEqgmqTmf = true;}
      while(guEnsZALfa == UfNOUWFloY){wDZCraJCyi = true;}
      while(miluBjyZZY == miluBjyZZY){gwKFDSQlgs = true;}
      while(lTqGOYEXhk == lTqGOYEXhk){SRaXWqZmhJ = true;}
      if(rSxKILxPmd == true){rSxKILxPmd = false;}
      if(KhDpiMrgCr == true){KhDpiMrgCr = false;}
      if(OOxgmNDyYU == true){OOxgmNDyYU = false;}
      if(UbdtiUlbmo == true){UbdtiUlbmo = false;}
      if(lhlwOEQBWC == true){lhlwOEQBWC = false;}
      if(fXUoWdUQWu == true){fXUoWdUQWu = false;}
      if(IzqSIhDIHO == true){IzqSIhDIHO = false;}
      if(aQtNFfbBSh == true){aQtNFfbBSh = false;}
      if(wCbWoxHnXF == true){wCbWoxHnXF = false;}
      if(zVEqgmqTmf == true){zVEqgmqTmf = false;}
      if(BHsHbOdHjp == true){BHsHbOdHjp = false;}
      if(BTxoyFWUcL == true){BTxoyFWUcL = false;}
      if(aOkCOELCgS == true){aOkCOELCgS = false;}
      if(oHNlgoJTtZ == true){oHNlgoJTtZ = false;}
      if(SAEhDfXPra == true){SAEhDfXPra = false;}
      if(PWqbFmWqsW == true){PWqbFmWqsW = false;}
      if(CaZRAsFLHJ == true){CaZRAsFLHJ = false;}
      if(wDZCraJCyi == true){wDZCraJCyi = false;}
      if(gwKFDSQlgs == true){gwKFDSQlgs = false;}
      if(SRaXWqZmhJ == true){SRaXWqZmhJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUTPABPRGJ
{ 
  void nNzeLIYArc()
  { 
      bool CDZLcpJigO = false;
      bool PeoVdxabgP = false;
      bool WjOYUuWAEY = false;
      bool imVIngwAaj = false;
      bool YpaOMPdtkV = false;
      bool pPfNhRoBph = false;
      bool SJeIfbJfhx = false;
      bool BZBwpfJzLF = false;
      bool QcOhhSHHaV = false;
      bool rtJrQPLRik = false;
      bool GyLmUPOjWC = false;
      bool IopkQptwZN = false;
      bool UBEMFGPIeZ = false;
      bool TqQZzSQaNR = false;
      bool DWjYMCEYba = false;
      bool VOqVQEsyhN = false;
      bool AFExhQYPkx = false;
      bool YSiIJxQfzC = false;
      bool CqfEEFztJt = false;
      bool YRszRyRmpw = false;
      string NzSsCZZdBR;
      string DzbFrPKYcp;
      string RhfyUnAfJl;
      string yDuSKmbsZD;
      string oohjppNMDi;
      string hWCNjeTTYN;
      string YsUPTADJtF;
      string nRyZAcAuIe;
      string anbZEaAhif;
      string THUMduTSPo;
      string lDRyuQXbMG;
      string eXLslkRtLr;
      string zVaOlfxlwF;
      string IheSrWVcem;
      string DYUbBuuaZr;
      string dZHWoPcCMO;
      string TlfHywrrAO;
      string OnPXoaAyNp;
      string jVLDaiZIcb;
      string tTQPTQrMcE;
      if(NzSsCZZdBR == lDRyuQXbMG){CDZLcpJigO = true;}
      else if(lDRyuQXbMG == NzSsCZZdBR){GyLmUPOjWC = true;}
      if(DzbFrPKYcp == eXLslkRtLr){PeoVdxabgP = true;}
      else if(eXLslkRtLr == DzbFrPKYcp){IopkQptwZN = true;}
      if(RhfyUnAfJl == zVaOlfxlwF){WjOYUuWAEY = true;}
      else if(zVaOlfxlwF == RhfyUnAfJl){UBEMFGPIeZ = true;}
      if(yDuSKmbsZD == IheSrWVcem){imVIngwAaj = true;}
      else if(IheSrWVcem == yDuSKmbsZD){TqQZzSQaNR = true;}
      if(oohjppNMDi == DYUbBuuaZr){YpaOMPdtkV = true;}
      else if(DYUbBuuaZr == oohjppNMDi){DWjYMCEYba = true;}
      if(hWCNjeTTYN == dZHWoPcCMO){pPfNhRoBph = true;}
      else if(dZHWoPcCMO == hWCNjeTTYN){VOqVQEsyhN = true;}
      if(YsUPTADJtF == TlfHywrrAO){SJeIfbJfhx = true;}
      else if(TlfHywrrAO == YsUPTADJtF){AFExhQYPkx = true;}
      if(nRyZAcAuIe == OnPXoaAyNp){BZBwpfJzLF = true;}
      if(anbZEaAhif == jVLDaiZIcb){QcOhhSHHaV = true;}
      if(THUMduTSPo == tTQPTQrMcE){rtJrQPLRik = true;}
      while(OnPXoaAyNp == nRyZAcAuIe){YSiIJxQfzC = true;}
      while(jVLDaiZIcb == jVLDaiZIcb){CqfEEFztJt = true;}
      while(tTQPTQrMcE == tTQPTQrMcE){YRszRyRmpw = true;}
      if(CDZLcpJigO == true){CDZLcpJigO = false;}
      if(PeoVdxabgP == true){PeoVdxabgP = false;}
      if(WjOYUuWAEY == true){WjOYUuWAEY = false;}
      if(imVIngwAaj == true){imVIngwAaj = false;}
      if(YpaOMPdtkV == true){YpaOMPdtkV = false;}
      if(pPfNhRoBph == true){pPfNhRoBph = false;}
      if(SJeIfbJfhx == true){SJeIfbJfhx = false;}
      if(BZBwpfJzLF == true){BZBwpfJzLF = false;}
      if(QcOhhSHHaV == true){QcOhhSHHaV = false;}
      if(rtJrQPLRik == true){rtJrQPLRik = false;}
      if(GyLmUPOjWC == true){GyLmUPOjWC = false;}
      if(IopkQptwZN == true){IopkQptwZN = false;}
      if(UBEMFGPIeZ == true){UBEMFGPIeZ = false;}
      if(TqQZzSQaNR == true){TqQZzSQaNR = false;}
      if(DWjYMCEYba == true){DWjYMCEYba = false;}
      if(VOqVQEsyhN == true){VOqVQEsyhN = false;}
      if(AFExhQYPkx == true){AFExhQYPkx = false;}
      if(YSiIJxQfzC == true){YSiIJxQfzC = false;}
      if(CqfEEFztJt == true){CqfEEFztJt = false;}
      if(YRszRyRmpw == true){YRszRyRmpw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGPQIMVPXU
{ 
  void JYHjajqLRU()
  { 
      bool KEGmMtbrNq = false;
      bool mTPHlsRYcw = false;
      bool horRmiTJVW = false;
      bool enIiENpOJZ = false;
      bool uTMjPBtLFV = false;
      bool TclwkUMoAc = false;
      bool ZSVpLzKfDX = false;
      bool DDOCANcHCk = false;
      bool oIEACCBLyi = false;
      bool BBNgzcyVYQ = false;
      bool pNHgRQNiwW = false;
      bool rFmOmRNUnJ = false;
      bool xyhUWCphCW = false;
      bool PHhkubAWhl = false;
      bool nRPapuNzsh = false;
      bool PcgPSrfmKO = false;
      bool affYHkWBTL = false;
      bool QplBUeiGea = false;
      bool nqnUHlZSSD = false;
      bool uNLTLIkpTE = false;
      string moXujgGNGL;
      string qqgIwzRHFs;
      string rqzBgKEfXu;
      string bsQhtZOERD;
      string jPfTzfiugf;
      string bFZHywpVOY;
      string caoKjxZyNW;
      string jNoCJcLfCA;
      string aIzrTVTJiy;
      string irosZIaUjC;
      string GkgJwOPWxV;
      string kKTOyUbxqN;
      string dPOPmqXwbA;
      string BpuAspaouF;
      string FwMNNYYauF;
      string gddVXpVRVE;
      string pTuxTtOTUH;
      string smBkIgDBCO;
      string SwBVTXMZbC;
      string UJSqPlBPsS;
      if(moXujgGNGL == GkgJwOPWxV){KEGmMtbrNq = true;}
      else if(GkgJwOPWxV == moXujgGNGL){pNHgRQNiwW = true;}
      if(qqgIwzRHFs == kKTOyUbxqN){mTPHlsRYcw = true;}
      else if(kKTOyUbxqN == qqgIwzRHFs){rFmOmRNUnJ = true;}
      if(rqzBgKEfXu == dPOPmqXwbA){horRmiTJVW = true;}
      else if(dPOPmqXwbA == rqzBgKEfXu){xyhUWCphCW = true;}
      if(bsQhtZOERD == BpuAspaouF){enIiENpOJZ = true;}
      else if(BpuAspaouF == bsQhtZOERD){PHhkubAWhl = true;}
      if(jPfTzfiugf == FwMNNYYauF){uTMjPBtLFV = true;}
      else if(FwMNNYYauF == jPfTzfiugf){nRPapuNzsh = true;}
      if(bFZHywpVOY == gddVXpVRVE){TclwkUMoAc = true;}
      else if(gddVXpVRVE == bFZHywpVOY){PcgPSrfmKO = true;}
      if(caoKjxZyNW == pTuxTtOTUH){ZSVpLzKfDX = true;}
      else if(pTuxTtOTUH == caoKjxZyNW){affYHkWBTL = true;}
      if(jNoCJcLfCA == smBkIgDBCO){DDOCANcHCk = true;}
      if(aIzrTVTJiy == SwBVTXMZbC){oIEACCBLyi = true;}
      if(irosZIaUjC == UJSqPlBPsS){BBNgzcyVYQ = true;}
      while(smBkIgDBCO == jNoCJcLfCA){QplBUeiGea = true;}
      while(SwBVTXMZbC == SwBVTXMZbC){nqnUHlZSSD = true;}
      while(UJSqPlBPsS == UJSqPlBPsS){uNLTLIkpTE = true;}
      if(KEGmMtbrNq == true){KEGmMtbrNq = false;}
      if(mTPHlsRYcw == true){mTPHlsRYcw = false;}
      if(horRmiTJVW == true){horRmiTJVW = false;}
      if(enIiENpOJZ == true){enIiENpOJZ = false;}
      if(uTMjPBtLFV == true){uTMjPBtLFV = false;}
      if(TclwkUMoAc == true){TclwkUMoAc = false;}
      if(ZSVpLzKfDX == true){ZSVpLzKfDX = false;}
      if(DDOCANcHCk == true){DDOCANcHCk = false;}
      if(oIEACCBLyi == true){oIEACCBLyi = false;}
      if(BBNgzcyVYQ == true){BBNgzcyVYQ = false;}
      if(pNHgRQNiwW == true){pNHgRQNiwW = false;}
      if(rFmOmRNUnJ == true){rFmOmRNUnJ = false;}
      if(xyhUWCphCW == true){xyhUWCphCW = false;}
      if(PHhkubAWhl == true){PHhkubAWhl = false;}
      if(nRPapuNzsh == true){nRPapuNzsh = false;}
      if(PcgPSrfmKO == true){PcgPSrfmKO = false;}
      if(affYHkWBTL == true){affYHkWBTL = false;}
      if(QplBUeiGea == true){QplBUeiGea = false;}
      if(nqnUHlZSSD == true){nqnUHlZSSD = false;}
      if(uNLTLIkpTE == true){uNLTLIkpTE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYVALAAOKL
{ 
  void hRjJySAfAt()
  { 
      bool desUCzObAO = false;
      bool FzMGFZJTNk = false;
      bool JkwrBVFbYk = false;
      bool sysgFEkLpq = false;
      bool rDBerTXOQO = false;
      bool UoEkEshATf = false;
      bool tlCPUGGfBA = false;
      bool oycWrGiQAh = false;
      bool yqLKPEsIcM = false;
      bool VjrJxGAlKl = false;
      bool MrMPYWLhrx = false;
      bool KRAkhCarAQ = false;
      bool MxCoeFFTYl = false;
      bool FwGOUFdukr = false;
      bool rLQeBEiGbu = false;
      bool fIlsYPoXkT = false;
      bool RrJGrNKlQb = false;
      bool YeHHXBgWma = false;
      bool VyrdGxKNoF = false;
      bool QFKQaABJmm = false;
      string JfubDRMhFt;
      string Ssetbxuqbo;
      string YiBtjXPUVl;
      string TMFblCWmZN;
      string GiQduBwPQS;
      string agcHCadArf;
      string CqMTZGnDIY;
      string ZIROhpRXzh;
      string bADDLlixZK;
      string XVttLPVxDn;
      string NsGqrRPOYL;
      string IGBKDBnJHm;
      string WpcxAENXCS;
      string TUTKUitMKs;
      string WUYNCRUjpK;
      string aMoQQWPIpn;
      string EqLFrnmppU;
      string HbyNPCRPui;
      string idgrqGeCsx;
      string SkVVoeISVN;
      if(JfubDRMhFt == NsGqrRPOYL){desUCzObAO = true;}
      else if(NsGqrRPOYL == JfubDRMhFt){MrMPYWLhrx = true;}
      if(Ssetbxuqbo == IGBKDBnJHm){FzMGFZJTNk = true;}
      else if(IGBKDBnJHm == Ssetbxuqbo){KRAkhCarAQ = true;}
      if(YiBtjXPUVl == WpcxAENXCS){JkwrBVFbYk = true;}
      else if(WpcxAENXCS == YiBtjXPUVl){MxCoeFFTYl = true;}
      if(TMFblCWmZN == TUTKUitMKs){sysgFEkLpq = true;}
      else if(TUTKUitMKs == TMFblCWmZN){FwGOUFdukr = true;}
      if(GiQduBwPQS == WUYNCRUjpK){rDBerTXOQO = true;}
      else if(WUYNCRUjpK == GiQduBwPQS){rLQeBEiGbu = true;}
      if(agcHCadArf == aMoQQWPIpn){UoEkEshATf = true;}
      else if(aMoQQWPIpn == agcHCadArf){fIlsYPoXkT = true;}
      if(CqMTZGnDIY == EqLFrnmppU){tlCPUGGfBA = true;}
      else if(EqLFrnmppU == CqMTZGnDIY){RrJGrNKlQb = true;}
      if(ZIROhpRXzh == HbyNPCRPui){oycWrGiQAh = true;}
      if(bADDLlixZK == idgrqGeCsx){yqLKPEsIcM = true;}
      if(XVttLPVxDn == SkVVoeISVN){VjrJxGAlKl = true;}
      while(HbyNPCRPui == ZIROhpRXzh){YeHHXBgWma = true;}
      while(idgrqGeCsx == idgrqGeCsx){VyrdGxKNoF = true;}
      while(SkVVoeISVN == SkVVoeISVN){QFKQaABJmm = true;}
      if(desUCzObAO == true){desUCzObAO = false;}
      if(FzMGFZJTNk == true){FzMGFZJTNk = false;}
      if(JkwrBVFbYk == true){JkwrBVFbYk = false;}
      if(sysgFEkLpq == true){sysgFEkLpq = false;}
      if(rDBerTXOQO == true){rDBerTXOQO = false;}
      if(UoEkEshATf == true){UoEkEshATf = false;}
      if(tlCPUGGfBA == true){tlCPUGGfBA = false;}
      if(oycWrGiQAh == true){oycWrGiQAh = false;}
      if(yqLKPEsIcM == true){yqLKPEsIcM = false;}
      if(VjrJxGAlKl == true){VjrJxGAlKl = false;}
      if(MrMPYWLhrx == true){MrMPYWLhrx = false;}
      if(KRAkhCarAQ == true){KRAkhCarAQ = false;}
      if(MxCoeFFTYl == true){MxCoeFFTYl = false;}
      if(FwGOUFdukr == true){FwGOUFdukr = false;}
      if(rLQeBEiGbu == true){rLQeBEiGbu = false;}
      if(fIlsYPoXkT == true){fIlsYPoXkT = false;}
      if(RrJGrNKlQb == true){RrJGrNKlQb = false;}
      if(YeHHXBgWma == true){YeHHXBgWma = false;}
      if(VyrdGxKNoF == true){VyrdGxKNoF = false;}
      if(QFKQaABJmm == true){QFKQaABJmm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYHUMONUQZ
{ 
  void zxYSrhomiH()
  { 
      bool FMlzRHnkLB = false;
      bool VyMwfnWLtc = false;
      bool mYLQZOQDLt = false;
      bool zrYxXOuMdy = false;
      bool KdrwDGiSOB = false;
      bool zkxGkgAUYD = false;
      bool qjYQBdYPXR = false;
      bool rJhwSJfPMT = false;
      bool eyoJuOtSMq = false;
      bool NanZHaEbuZ = false;
      bool gStwJpCBmb = false;
      bool AkIFXruOVl = false;
      bool iGDfDRUHnr = false;
      bool EEUllLDrAF = false;
      bool LrejqcRhBO = false;
      bool eoFIqaPOsr = false;
      bool UuMuWwPVTL = false;
      bool oCOQaqbSoZ = false;
      bool zmGZMOzMuK = false;
      bool wozIjQeiNt = false;
      string EFeACJPBdc;
      string xJNDZzmbHN;
      string bBXfQRLRpa;
      string aKpQeXZgKQ;
      string IABxlCaCof;
      string ktXBoChyjk;
      string yyLCBmSwXC;
      string ZGRqFaAZtO;
      string qIcJpgloab;
      string oaxYRJozuy;
      string iddmGebgwO;
      string CHEUsoVBMU;
      string BcVuMyJrYu;
      string lBeueNeoDK;
      string EEsMZhWbfc;
      string nmlaxFHiaI;
      string ViHBcBcJpf;
      string KfyBPwjJVd;
      string bgMwGzODxY;
      string FwOuoVwrjX;
      if(EFeACJPBdc == iddmGebgwO){FMlzRHnkLB = true;}
      else if(iddmGebgwO == EFeACJPBdc){gStwJpCBmb = true;}
      if(xJNDZzmbHN == CHEUsoVBMU){VyMwfnWLtc = true;}
      else if(CHEUsoVBMU == xJNDZzmbHN){AkIFXruOVl = true;}
      if(bBXfQRLRpa == BcVuMyJrYu){mYLQZOQDLt = true;}
      else if(BcVuMyJrYu == bBXfQRLRpa){iGDfDRUHnr = true;}
      if(aKpQeXZgKQ == lBeueNeoDK){zrYxXOuMdy = true;}
      else if(lBeueNeoDK == aKpQeXZgKQ){EEUllLDrAF = true;}
      if(IABxlCaCof == EEsMZhWbfc){KdrwDGiSOB = true;}
      else if(EEsMZhWbfc == IABxlCaCof){LrejqcRhBO = true;}
      if(ktXBoChyjk == nmlaxFHiaI){zkxGkgAUYD = true;}
      else if(nmlaxFHiaI == ktXBoChyjk){eoFIqaPOsr = true;}
      if(yyLCBmSwXC == ViHBcBcJpf){qjYQBdYPXR = true;}
      else if(ViHBcBcJpf == yyLCBmSwXC){UuMuWwPVTL = true;}
      if(ZGRqFaAZtO == KfyBPwjJVd){rJhwSJfPMT = true;}
      if(qIcJpgloab == bgMwGzODxY){eyoJuOtSMq = true;}
      if(oaxYRJozuy == FwOuoVwrjX){NanZHaEbuZ = true;}
      while(KfyBPwjJVd == ZGRqFaAZtO){oCOQaqbSoZ = true;}
      while(bgMwGzODxY == bgMwGzODxY){zmGZMOzMuK = true;}
      while(FwOuoVwrjX == FwOuoVwrjX){wozIjQeiNt = true;}
      if(FMlzRHnkLB == true){FMlzRHnkLB = false;}
      if(VyMwfnWLtc == true){VyMwfnWLtc = false;}
      if(mYLQZOQDLt == true){mYLQZOQDLt = false;}
      if(zrYxXOuMdy == true){zrYxXOuMdy = false;}
      if(KdrwDGiSOB == true){KdrwDGiSOB = false;}
      if(zkxGkgAUYD == true){zkxGkgAUYD = false;}
      if(qjYQBdYPXR == true){qjYQBdYPXR = false;}
      if(rJhwSJfPMT == true){rJhwSJfPMT = false;}
      if(eyoJuOtSMq == true){eyoJuOtSMq = false;}
      if(NanZHaEbuZ == true){NanZHaEbuZ = false;}
      if(gStwJpCBmb == true){gStwJpCBmb = false;}
      if(AkIFXruOVl == true){AkIFXruOVl = false;}
      if(iGDfDRUHnr == true){iGDfDRUHnr = false;}
      if(EEUllLDrAF == true){EEUllLDrAF = false;}
      if(LrejqcRhBO == true){LrejqcRhBO = false;}
      if(eoFIqaPOsr == true){eoFIqaPOsr = false;}
      if(UuMuWwPVTL == true){UuMuWwPVTL = false;}
      if(oCOQaqbSoZ == true){oCOQaqbSoZ = false;}
      if(zmGZMOzMuK == true){zmGZMOzMuK = false;}
      if(wozIjQeiNt == true){wozIjQeiNt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQFHXCVUBO
{ 
  void asQejaEiSF()
  { 
      bool yjJTeVoeMj = false;
      bool spQgFajeuA = false;
      bool iuDLUzeptz = false;
      bool cTFOCaPcNy = false;
      bool ROAPydOMeD = false;
      bool SyazUDfyzf = false;
      bool qyjNGYjBde = false;
      bool KGQwhUtmMq = false;
      bool kRLqfesGtz = false;
      bool tQdhHSdlJY = false;
      bool sNhzrMhdQA = false;
      bool IslIuYmshb = false;
      bool fdGdkschoO = false;
      bool pIdmxWiMyT = false;
      bool wPotqBeUmi = false;
      bool fkEhsPGENy = false;
      bool iznBJAOyKX = false;
      bool oZtOeQnMmi = false;
      bool NHuFiEDusg = false;
      bool QeyAjwamjp = false;
      string GKONDrezFq;
      string xAiyOxqJGU;
      string DcscucxMHk;
      string fLFjmLSLoy;
      string MlZNlHFwtr;
      string TIhmxdRkSa;
      string uSrTKluyKC;
      string dfUHIRCeqn;
      string WASORXcRmJ;
      string sgrNDssFCA;
      string MHkqNmnaef;
      string alteEtzcCm;
      string IcLBIxmGDO;
      string XxcqaPOaBd;
      string jBmGhHmNJJ;
      string tQDPqiujhQ;
      string AgXQHdIDDo;
      string eXaXCHpETB;
      string KZxsUHtNzr;
      string TeskdDdVzE;
      if(GKONDrezFq == MHkqNmnaef){yjJTeVoeMj = true;}
      else if(MHkqNmnaef == GKONDrezFq){sNhzrMhdQA = true;}
      if(xAiyOxqJGU == alteEtzcCm){spQgFajeuA = true;}
      else if(alteEtzcCm == xAiyOxqJGU){IslIuYmshb = true;}
      if(DcscucxMHk == IcLBIxmGDO){iuDLUzeptz = true;}
      else if(IcLBIxmGDO == DcscucxMHk){fdGdkschoO = true;}
      if(fLFjmLSLoy == XxcqaPOaBd){cTFOCaPcNy = true;}
      else if(XxcqaPOaBd == fLFjmLSLoy){pIdmxWiMyT = true;}
      if(MlZNlHFwtr == jBmGhHmNJJ){ROAPydOMeD = true;}
      else if(jBmGhHmNJJ == MlZNlHFwtr){wPotqBeUmi = true;}
      if(TIhmxdRkSa == tQDPqiujhQ){SyazUDfyzf = true;}
      else if(tQDPqiujhQ == TIhmxdRkSa){fkEhsPGENy = true;}
      if(uSrTKluyKC == AgXQHdIDDo){qyjNGYjBde = true;}
      else if(AgXQHdIDDo == uSrTKluyKC){iznBJAOyKX = true;}
      if(dfUHIRCeqn == eXaXCHpETB){KGQwhUtmMq = true;}
      if(WASORXcRmJ == KZxsUHtNzr){kRLqfesGtz = true;}
      if(sgrNDssFCA == TeskdDdVzE){tQdhHSdlJY = true;}
      while(eXaXCHpETB == dfUHIRCeqn){oZtOeQnMmi = true;}
      while(KZxsUHtNzr == KZxsUHtNzr){NHuFiEDusg = true;}
      while(TeskdDdVzE == TeskdDdVzE){QeyAjwamjp = true;}
      if(yjJTeVoeMj == true){yjJTeVoeMj = false;}
      if(spQgFajeuA == true){spQgFajeuA = false;}
      if(iuDLUzeptz == true){iuDLUzeptz = false;}
      if(cTFOCaPcNy == true){cTFOCaPcNy = false;}
      if(ROAPydOMeD == true){ROAPydOMeD = false;}
      if(SyazUDfyzf == true){SyazUDfyzf = false;}
      if(qyjNGYjBde == true){qyjNGYjBde = false;}
      if(KGQwhUtmMq == true){KGQwhUtmMq = false;}
      if(kRLqfesGtz == true){kRLqfesGtz = false;}
      if(tQdhHSdlJY == true){tQdhHSdlJY = false;}
      if(sNhzrMhdQA == true){sNhzrMhdQA = false;}
      if(IslIuYmshb == true){IslIuYmshb = false;}
      if(fdGdkschoO == true){fdGdkschoO = false;}
      if(pIdmxWiMyT == true){pIdmxWiMyT = false;}
      if(wPotqBeUmi == true){wPotqBeUmi = false;}
      if(fkEhsPGENy == true){fkEhsPGENy = false;}
      if(iznBJAOyKX == true){iznBJAOyKX = false;}
      if(oZtOeQnMmi == true){oZtOeQnMmi = false;}
      if(NHuFiEDusg == true){NHuFiEDusg = false;}
      if(QeyAjwamjp == true){QeyAjwamjp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PULNZRDCSZ
{ 
  void lqyOXfnsJe()
  { 
      bool xcbAaLeVzV = false;
      bool RYeFhdfCoz = false;
      bool rmbkllkAJi = false;
      bool ymIEYPVktn = false;
      bool mrCiLmwZhV = false;
      bool MwWkKJApNo = false;
      bool aeMPWePZgS = false;
      bool HuIAMzkrYz = false;
      bool oKRmVCQXsO = false;
      bool OeXFNHflMg = false;
      bool XVsPNRnVYL = false;
      bool YIQNzPNYsU = false;
      bool OrfRDbWCmE = false;
      bool TyfrbTQBYE = false;
      bool OuzhoGNJGy = false;
      bool tGsqSeoaLl = false;
      bool tkhTrabYle = false;
      bool yLznGTsycx = false;
      bool NNwoJMFoZw = false;
      bool dppmKdMepO = false;
      string XIyfOCHDmX;
      string osRDaGWMou;
      string HKAdFpEqWG;
      string ZOUkYMkcAO;
      string QmyKPqwjzz;
      string LNIyBNHUZX;
      string xPgfxaYfdO;
      string UsMadUMoNO;
      string tUrWtLFWjL;
      string EQDcQAFRMo;
      string SPFkeSBhTg;
      string BRGLdbXJll;
      string UBwSJDpjJc;
      string OtcYueOHrb;
      string KXCCJmKryn;
      string cwfaTQSmba;
      string bRXpRGogPy;
      string NQQJbxztIV;
      string sykUASOBFd;
      string LaeQAszLkD;
      if(XIyfOCHDmX == SPFkeSBhTg){xcbAaLeVzV = true;}
      else if(SPFkeSBhTg == XIyfOCHDmX){XVsPNRnVYL = true;}
      if(osRDaGWMou == BRGLdbXJll){RYeFhdfCoz = true;}
      else if(BRGLdbXJll == osRDaGWMou){YIQNzPNYsU = true;}
      if(HKAdFpEqWG == UBwSJDpjJc){rmbkllkAJi = true;}
      else if(UBwSJDpjJc == HKAdFpEqWG){OrfRDbWCmE = true;}
      if(ZOUkYMkcAO == OtcYueOHrb){ymIEYPVktn = true;}
      else if(OtcYueOHrb == ZOUkYMkcAO){TyfrbTQBYE = true;}
      if(QmyKPqwjzz == KXCCJmKryn){mrCiLmwZhV = true;}
      else if(KXCCJmKryn == QmyKPqwjzz){OuzhoGNJGy = true;}
      if(LNIyBNHUZX == cwfaTQSmba){MwWkKJApNo = true;}
      else if(cwfaTQSmba == LNIyBNHUZX){tGsqSeoaLl = true;}
      if(xPgfxaYfdO == bRXpRGogPy){aeMPWePZgS = true;}
      else if(bRXpRGogPy == xPgfxaYfdO){tkhTrabYle = true;}
      if(UsMadUMoNO == NQQJbxztIV){HuIAMzkrYz = true;}
      if(tUrWtLFWjL == sykUASOBFd){oKRmVCQXsO = true;}
      if(EQDcQAFRMo == LaeQAszLkD){OeXFNHflMg = true;}
      while(NQQJbxztIV == UsMadUMoNO){yLznGTsycx = true;}
      while(sykUASOBFd == sykUASOBFd){NNwoJMFoZw = true;}
      while(LaeQAszLkD == LaeQAszLkD){dppmKdMepO = true;}
      if(xcbAaLeVzV == true){xcbAaLeVzV = false;}
      if(RYeFhdfCoz == true){RYeFhdfCoz = false;}
      if(rmbkllkAJi == true){rmbkllkAJi = false;}
      if(ymIEYPVktn == true){ymIEYPVktn = false;}
      if(mrCiLmwZhV == true){mrCiLmwZhV = false;}
      if(MwWkKJApNo == true){MwWkKJApNo = false;}
      if(aeMPWePZgS == true){aeMPWePZgS = false;}
      if(HuIAMzkrYz == true){HuIAMzkrYz = false;}
      if(oKRmVCQXsO == true){oKRmVCQXsO = false;}
      if(OeXFNHflMg == true){OeXFNHflMg = false;}
      if(XVsPNRnVYL == true){XVsPNRnVYL = false;}
      if(YIQNzPNYsU == true){YIQNzPNYsU = false;}
      if(OrfRDbWCmE == true){OrfRDbWCmE = false;}
      if(TyfrbTQBYE == true){TyfrbTQBYE = false;}
      if(OuzhoGNJGy == true){OuzhoGNJGy = false;}
      if(tGsqSeoaLl == true){tGsqSeoaLl = false;}
      if(tkhTrabYle == true){tkhTrabYle = false;}
      if(yLznGTsycx == true){yLznGTsycx = false;}
      if(NNwoJMFoZw == true){NNwoJMFoZw = false;}
      if(dppmKdMepO == true){dppmKdMepO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYIAHEHDCX
{ 
  void MHrCdJohaX()
  { 
      bool BwLGrqytic = false;
      bool sEhxBWIomf = false;
      bool GaOkneQJSI = false;
      bool UKpYTzqbOr = false;
      bool tLgoCwThLN = false;
      bool AMJMZagZRM = false;
      bool ZoaaIhOJdB = false;
      bool ffZulusZiq = false;
      bool LixFHIBcyr = false;
      bool RQJBREjGgT = false;
      bool hJDKhTlNae = false;
      bool gHqaBqqVTz = false;
      bool fkKkiOWYcg = false;
      bool KmrOICemXm = false;
      bool WmBTLKZiAa = false;
      bool NOmgnwyRaS = false;
      bool xNjtTsObRz = false;
      bool LEyfcrjqZY = false;
      bool nnYCTwzKaL = false;
      bool DMLEoIDHzR = false;
      string KdckVeNNLa;
      string ZADHPKhhaV;
      string aakukQdjCP;
      string pfMBuwJTex;
      string ONICLOozCW;
      string jWGAzjrhzF;
      string BdLujsmBLS;
      string AOCcHNRiiW;
      string bdhffTZMCL;
      string DbTYwjBNRR;
      string amniVUTcsk;
      string RJybdWwfPQ;
      string SazzPYtdgW;
      string MERQunpzJL;
      string zxSQttcruZ;
      string nUyAyAmnSw;
      string ZpwVXMrgfo;
      string gxWDRVHiFV;
      string uChHirGQRu;
      string BBfMkIBwsg;
      if(KdckVeNNLa == amniVUTcsk){BwLGrqytic = true;}
      else if(amniVUTcsk == KdckVeNNLa){hJDKhTlNae = true;}
      if(ZADHPKhhaV == RJybdWwfPQ){sEhxBWIomf = true;}
      else if(RJybdWwfPQ == ZADHPKhhaV){gHqaBqqVTz = true;}
      if(aakukQdjCP == SazzPYtdgW){GaOkneQJSI = true;}
      else if(SazzPYtdgW == aakukQdjCP){fkKkiOWYcg = true;}
      if(pfMBuwJTex == MERQunpzJL){UKpYTzqbOr = true;}
      else if(MERQunpzJL == pfMBuwJTex){KmrOICemXm = true;}
      if(ONICLOozCW == zxSQttcruZ){tLgoCwThLN = true;}
      else if(zxSQttcruZ == ONICLOozCW){WmBTLKZiAa = true;}
      if(jWGAzjrhzF == nUyAyAmnSw){AMJMZagZRM = true;}
      else if(nUyAyAmnSw == jWGAzjrhzF){NOmgnwyRaS = true;}
      if(BdLujsmBLS == ZpwVXMrgfo){ZoaaIhOJdB = true;}
      else if(ZpwVXMrgfo == BdLujsmBLS){xNjtTsObRz = true;}
      if(AOCcHNRiiW == gxWDRVHiFV){ffZulusZiq = true;}
      if(bdhffTZMCL == uChHirGQRu){LixFHIBcyr = true;}
      if(DbTYwjBNRR == BBfMkIBwsg){RQJBREjGgT = true;}
      while(gxWDRVHiFV == AOCcHNRiiW){LEyfcrjqZY = true;}
      while(uChHirGQRu == uChHirGQRu){nnYCTwzKaL = true;}
      while(BBfMkIBwsg == BBfMkIBwsg){DMLEoIDHzR = true;}
      if(BwLGrqytic == true){BwLGrqytic = false;}
      if(sEhxBWIomf == true){sEhxBWIomf = false;}
      if(GaOkneQJSI == true){GaOkneQJSI = false;}
      if(UKpYTzqbOr == true){UKpYTzqbOr = false;}
      if(tLgoCwThLN == true){tLgoCwThLN = false;}
      if(AMJMZagZRM == true){AMJMZagZRM = false;}
      if(ZoaaIhOJdB == true){ZoaaIhOJdB = false;}
      if(ffZulusZiq == true){ffZulusZiq = false;}
      if(LixFHIBcyr == true){LixFHIBcyr = false;}
      if(RQJBREjGgT == true){RQJBREjGgT = false;}
      if(hJDKhTlNae == true){hJDKhTlNae = false;}
      if(gHqaBqqVTz == true){gHqaBqqVTz = false;}
      if(fkKkiOWYcg == true){fkKkiOWYcg = false;}
      if(KmrOICemXm == true){KmrOICemXm = false;}
      if(WmBTLKZiAa == true){WmBTLKZiAa = false;}
      if(NOmgnwyRaS == true){NOmgnwyRaS = false;}
      if(xNjtTsObRz == true){xNjtTsObRz = false;}
      if(LEyfcrjqZY == true){LEyfcrjqZY = false;}
      if(nnYCTwzKaL == true){nnYCTwzKaL = false;}
      if(DMLEoIDHzR == true){DMLEoIDHzR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXBPLDQCVI
{ 
  void tntlfaMyJN()
  { 
      bool oSQEmcoEEQ = false;
      bool FOFHXWEoOn = false;
      bool bCPjDZuyhf = false;
      bool ozCaRVtDOa = false;
      bool yeZKQFZhqo = false;
      bool WwFrFlDgBN = false;
      bool hqWYaFMdpC = false;
      bool cAZnpwcETy = false;
      bool zMHrIstJUf = false;
      bool RMCBrHIAjK = false;
      bool rurnMWVRCJ = false;
      bool IyNCNUidQh = false;
      bool KCJKjPxXuh = false;
      bool mcUIFEUSfk = false;
      bool WcHLWSzAnX = false;
      bool XejBzolhDw = false;
      bool YxVTVfdExI = false;
      bool AQxeKhuxmQ = false;
      bool QxjXKIrSIP = false;
      bool SmOiMZGmpp = false;
      string gUqYOPyrgi;
      string sSDxnGJYZO;
      string JMwUtQLLOg;
      string wdjiHRoDRr;
      string qXnwIQJEOb;
      string WGRJGTXVex;
      string DmczmOhToW;
      string RGGgWlYAMd;
      string HHwmKoMZcn;
      string sSXTnEtoJs;
      string hoOrKPAjlT;
      string uXJBpwppox;
      string CIqBcyhlsS;
      string qipSuRrEbt;
      string obnIsVJWcq;
      string ODzMqZxNOM;
      string hNqTbLgqFY;
      string EkOtHZUhIG;
      string nLIBEnjdbV;
      string UepPMbkUfg;
      if(gUqYOPyrgi == hoOrKPAjlT){oSQEmcoEEQ = true;}
      else if(hoOrKPAjlT == gUqYOPyrgi){rurnMWVRCJ = true;}
      if(sSDxnGJYZO == uXJBpwppox){FOFHXWEoOn = true;}
      else if(uXJBpwppox == sSDxnGJYZO){IyNCNUidQh = true;}
      if(JMwUtQLLOg == CIqBcyhlsS){bCPjDZuyhf = true;}
      else if(CIqBcyhlsS == JMwUtQLLOg){KCJKjPxXuh = true;}
      if(wdjiHRoDRr == qipSuRrEbt){ozCaRVtDOa = true;}
      else if(qipSuRrEbt == wdjiHRoDRr){mcUIFEUSfk = true;}
      if(qXnwIQJEOb == obnIsVJWcq){yeZKQFZhqo = true;}
      else if(obnIsVJWcq == qXnwIQJEOb){WcHLWSzAnX = true;}
      if(WGRJGTXVex == ODzMqZxNOM){WwFrFlDgBN = true;}
      else if(ODzMqZxNOM == WGRJGTXVex){XejBzolhDw = true;}
      if(DmczmOhToW == hNqTbLgqFY){hqWYaFMdpC = true;}
      else if(hNqTbLgqFY == DmczmOhToW){YxVTVfdExI = true;}
      if(RGGgWlYAMd == EkOtHZUhIG){cAZnpwcETy = true;}
      if(HHwmKoMZcn == nLIBEnjdbV){zMHrIstJUf = true;}
      if(sSXTnEtoJs == UepPMbkUfg){RMCBrHIAjK = true;}
      while(EkOtHZUhIG == RGGgWlYAMd){AQxeKhuxmQ = true;}
      while(nLIBEnjdbV == nLIBEnjdbV){QxjXKIrSIP = true;}
      while(UepPMbkUfg == UepPMbkUfg){SmOiMZGmpp = true;}
      if(oSQEmcoEEQ == true){oSQEmcoEEQ = false;}
      if(FOFHXWEoOn == true){FOFHXWEoOn = false;}
      if(bCPjDZuyhf == true){bCPjDZuyhf = false;}
      if(ozCaRVtDOa == true){ozCaRVtDOa = false;}
      if(yeZKQFZhqo == true){yeZKQFZhqo = false;}
      if(WwFrFlDgBN == true){WwFrFlDgBN = false;}
      if(hqWYaFMdpC == true){hqWYaFMdpC = false;}
      if(cAZnpwcETy == true){cAZnpwcETy = false;}
      if(zMHrIstJUf == true){zMHrIstJUf = false;}
      if(RMCBrHIAjK == true){RMCBrHIAjK = false;}
      if(rurnMWVRCJ == true){rurnMWVRCJ = false;}
      if(IyNCNUidQh == true){IyNCNUidQh = false;}
      if(KCJKjPxXuh == true){KCJKjPxXuh = false;}
      if(mcUIFEUSfk == true){mcUIFEUSfk = false;}
      if(WcHLWSzAnX == true){WcHLWSzAnX = false;}
      if(XejBzolhDw == true){XejBzolhDw = false;}
      if(YxVTVfdExI == true){YxVTVfdExI = false;}
      if(AQxeKhuxmQ == true){AQxeKhuxmQ = false;}
      if(QxjXKIrSIP == true){QxjXKIrSIP = false;}
      if(SmOiMZGmpp == true){SmOiMZGmpp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQETGFICPF
{ 
  void VSZiOagkRB()
  { 
      bool QxrEozANfl = false;
      bool TmQaQTmwqW = false;
      bool tSNNMxHxQc = false;
      bool JSnjxUpSxn = false;
      bool fLJWcFOzMI = false;
      bool mVrYxxjdqr = false;
      bool rDwCcBzfcw = false;
      bool cTzDpiJpkH = false;
      bool hHjIpmZPlz = false;
      bool jMbFucOGtb = false;
      bool GhVQeSWohO = false;
      bool nssjJjSnMo = false;
      bool aisdLQrsHN = false;
      bool TCwIAAkTdW = false;
      bool QkgXKpSrwL = false;
      bool KatEAWnrEN = false;
      bool adhUtlwkiI = false;
      bool yyKpYpBVSU = false;
      bool yzwwCsHrHc = false;
      bool LsPPulCMdY = false;
      string CVrFUxxTbD;
      string UslXgZiotQ;
      string wppgWapKBe;
      string jzOpXmZPaY;
      string QdcqPQDiUV;
      string JGIAeLfLis;
      string HlRwSVewAs;
      string ASOVASMyRF;
      string XGpfVcpOLL;
      string GNggRdLgYs;
      string lHhaUprmAL;
      string zhtdVAwkZo;
      string eQjomllhDV;
      string HfYXSPXOLf;
      string kCNALYTDKQ;
      string hZGjOVWsnh;
      string DKjeETIWKG;
      string bhZsDbCjcN;
      string RiWmmgYoIw;
      string seZccaSiur;
      if(CVrFUxxTbD == lHhaUprmAL){QxrEozANfl = true;}
      else if(lHhaUprmAL == CVrFUxxTbD){GhVQeSWohO = true;}
      if(UslXgZiotQ == zhtdVAwkZo){TmQaQTmwqW = true;}
      else if(zhtdVAwkZo == UslXgZiotQ){nssjJjSnMo = true;}
      if(wppgWapKBe == eQjomllhDV){tSNNMxHxQc = true;}
      else if(eQjomllhDV == wppgWapKBe){aisdLQrsHN = true;}
      if(jzOpXmZPaY == HfYXSPXOLf){JSnjxUpSxn = true;}
      else if(HfYXSPXOLf == jzOpXmZPaY){TCwIAAkTdW = true;}
      if(QdcqPQDiUV == kCNALYTDKQ){fLJWcFOzMI = true;}
      else if(kCNALYTDKQ == QdcqPQDiUV){QkgXKpSrwL = true;}
      if(JGIAeLfLis == hZGjOVWsnh){mVrYxxjdqr = true;}
      else if(hZGjOVWsnh == JGIAeLfLis){KatEAWnrEN = true;}
      if(HlRwSVewAs == DKjeETIWKG){rDwCcBzfcw = true;}
      else if(DKjeETIWKG == HlRwSVewAs){adhUtlwkiI = true;}
      if(ASOVASMyRF == bhZsDbCjcN){cTzDpiJpkH = true;}
      if(XGpfVcpOLL == RiWmmgYoIw){hHjIpmZPlz = true;}
      if(GNggRdLgYs == seZccaSiur){jMbFucOGtb = true;}
      while(bhZsDbCjcN == ASOVASMyRF){yyKpYpBVSU = true;}
      while(RiWmmgYoIw == RiWmmgYoIw){yzwwCsHrHc = true;}
      while(seZccaSiur == seZccaSiur){LsPPulCMdY = true;}
      if(QxrEozANfl == true){QxrEozANfl = false;}
      if(TmQaQTmwqW == true){TmQaQTmwqW = false;}
      if(tSNNMxHxQc == true){tSNNMxHxQc = false;}
      if(JSnjxUpSxn == true){JSnjxUpSxn = false;}
      if(fLJWcFOzMI == true){fLJWcFOzMI = false;}
      if(mVrYxxjdqr == true){mVrYxxjdqr = false;}
      if(rDwCcBzfcw == true){rDwCcBzfcw = false;}
      if(cTzDpiJpkH == true){cTzDpiJpkH = false;}
      if(hHjIpmZPlz == true){hHjIpmZPlz = false;}
      if(jMbFucOGtb == true){jMbFucOGtb = false;}
      if(GhVQeSWohO == true){GhVQeSWohO = false;}
      if(nssjJjSnMo == true){nssjJjSnMo = false;}
      if(aisdLQrsHN == true){aisdLQrsHN = false;}
      if(TCwIAAkTdW == true){TCwIAAkTdW = false;}
      if(QkgXKpSrwL == true){QkgXKpSrwL = false;}
      if(KatEAWnrEN == true){KatEAWnrEN = false;}
      if(adhUtlwkiI == true){adhUtlwkiI = false;}
      if(yyKpYpBVSU == true){yyKpYpBVSU = false;}
      if(yzwwCsHrHc == true){yzwwCsHrHc = false;}
      if(LsPPulCMdY == true){LsPPulCMdY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPGPQXDRRX
{ 
  void KaiKDtWAzS()
  { 
      bool LcyOgBZjKY = false;
      bool wsgJSGHJof = false;
      bool TWAjaCgnDW = false;
      bool jQfgsKqdGi = false;
      bool BlpunKLaEc = false;
      bool jmnuCocNnd = false;
      bool UlfmneNAPH = false;
      bool OdCFdggFuQ = false;
      bool pGialwbjdE = false;
      bool hdobOOFCGJ = false;
      bool xLKxNGjiQV = false;
      bool IXRXnODFAq = false;
      bool DcVLYknaqO = false;
      bool adylTeukMf = false;
      bool MsTIwKLRnz = false;
      bool LACOFToyYc = false;
      bool RJrCteYfEJ = false;
      bool SRrTeJJNPO = false;
      bool ZWlqDaaifz = false;
      bool pwMjODBQNR = false;
      string KiPzByAJVY;
      string RlAiGTzRYu;
      string bleRmZsduP;
      string ikDJVkpbDG;
      string GnyWMWfNZX;
      string cCdTHXEyMa;
      string EVNGoghqMV;
      string dXORommHEP;
      string seEXlgGiCx;
      string fqPbBjarhf;
      string ooAEsFnMeT;
      string kxswhZRoTI;
      string ayoPolImPE;
      string MtZYaDdzdf;
      string ssEhMixSsb;
      string SkXYFpAkPG;
      string wAxaHpWUUd;
      string uRKnOgtGDF;
      string nosmkaWATk;
      string DsjWjrwdaW;
      if(KiPzByAJVY == ooAEsFnMeT){LcyOgBZjKY = true;}
      else if(ooAEsFnMeT == KiPzByAJVY){xLKxNGjiQV = true;}
      if(RlAiGTzRYu == kxswhZRoTI){wsgJSGHJof = true;}
      else if(kxswhZRoTI == RlAiGTzRYu){IXRXnODFAq = true;}
      if(bleRmZsduP == ayoPolImPE){TWAjaCgnDW = true;}
      else if(ayoPolImPE == bleRmZsduP){DcVLYknaqO = true;}
      if(ikDJVkpbDG == MtZYaDdzdf){jQfgsKqdGi = true;}
      else if(MtZYaDdzdf == ikDJVkpbDG){adylTeukMf = true;}
      if(GnyWMWfNZX == ssEhMixSsb){BlpunKLaEc = true;}
      else if(ssEhMixSsb == GnyWMWfNZX){MsTIwKLRnz = true;}
      if(cCdTHXEyMa == SkXYFpAkPG){jmnuCocNnd = true;}
      else if(SkXYFpAkPG == cCdTHXEyMa){LACOFToyYc = true;}
      if(EVNGoghqMV == wAxaHpWUUd){UlfmneNAPH = true;}
      else if(wAxaHpWUUd == EVNGoghqMV){RJrCteYfEJ = true;}
      if(dXORommHEP == uRKnOgtGDF){OdCFdggFuQ = true;}
      if(seEXlgGiCx == nosmkaWATk){pGialwbjdE = true;}
      if(fqPbBjarhf == DsjWjrwdaW){hdobOOFCGJ = true;}
      while(uRKnOgtGDF == dXORommHEP){SRrTeJJNPO = true;}
      while(nosmkaWATk == nosmkaWATk){ZWlqDaaifz = true;}
      while(DsjWjrwdaW == DsjWjrwdaW){pwMjODBQNR = true;}
      if(LcyOgBZjKY == true){LcyOgBZjKY = false;}
      if(wsgJSGHJof == true){wsgJSGHJof = false;}
      if(TWAjaCgnDW == true){TWAjaCgnDW = false;}
      if(jQfgsKqdGi == true){jQfgsKqdGi = false;}
      if(BlpunKLaEc == true){BlpunKLaEc = false;}
      if(jmnuCocNnd == true){jmnuCocNnd = false;}
      if(UlfmneNAPH == true){UlfmneNAPH = false;}
      if(OdCFdggFuQ == true){OdCFdggFuQ = false;}
      if(pGialwbjdE == true){pGialwbjdE = false;}
      if(hdobOOFCGJ == true){hdobOOFCGJ = false;}
      if(xLKxNGjiQV == true){xLKxNGjiQV = false;}
      if(IXRXnODFAq == true){IXRXnODFAq = false;}
      if(DcVLYknaqO == true){DcVLYknaqO = false;}
      if(adylTeukMf == true){adylTeukMf = false;}
      if(MsTIwKLRnz == true){MsTIwKLRnz = false;}
      if(LACOFToyYc == true){LACOFToyYc = false;}
      if(RJrCteYfEJ == true){RJrCteYfEJ = false;}
      if(SRrTeJJNPO == true){SRrTeJJNPO = false;}
      if(ZWlqDaaifz == true){ZWlqDaaifz = false;}
      if(pwMjODBQNR == true){pwMjODBQNR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IMLUXICVCM
{ 
  void DCGmDBIwcU()
  { 
      bool hYzkLjbLSL = false;
      bool FNZyLFOcoY = false;
      bool bmQXiadCGq = false;
      bool bdFzNizzyT = false;
      bool WYDgWUATRg = false;
      bool rVUcGtHbCk = false;
      bool GYFbjaIZkc = false;
      bool GPeVCDiiAO = false;
      bool ZJjYyGJcsS = false;
      bool aWxNMySbxw = false;
      bool MaioacpyaD = false;
      bool LXamLwngcd = false;
      bool QegRCiRRID = false;
      bool jHlEByauyV = false;
      bool PKBoHCuJCP = false;
      bool JlzTegtQmq = false;
      bool KYoWSDlWlM = false;
      bool VrhHNFcqJz = false;
      bool nIPssyISYU = false;
      bool EJIHKqUeWD = false;
      string jDNGkqMauK;
      string iVTMcQUbSZ;
      string WArpaClGmQ;
      string FYrfiAyBKA;
      string xbUeJQrQKd;
      string VHbIZiKXfh;
      string EFneFJcndc;
      string RTRScufNfJ;
      string KUuJtywjFz;
      string oaUbuqmpYA;
      string mEmhLCoJfe;
      string DxqVXiJejH;
      string NshemqyoWk;
      string HpnfVFhNxq;
      string IlEZwqjzEM;
      string gIFRmtVItT;
      string EAmtXMJKzS;
      string AwgszaoIiu;
      string HykJEykVsb;
      string iZSdmHzKCi;
      if(jDNGkqMauK == mEmhLCoJfe){hYzkLjbLSL = true;}
      else if(mEmhLCoJfe == jDNGkqMauK){MaioacpyaD = true;}
      if(iVTMcQUbSZ == DxqVXiJejH){FNZyLFOcoY = true;}
      else if(DxqVXiJejH == iVTMcQUbSZ){LXamLwngcd = true;}
      if(WArpaClGmQ == NshemqyoWk){bmQXiadCGq = true;}
      else if(NshemqyoWk == WArpaClGmQ){QegRCiRRID = true;}
      if(FYrfiAyBKA == HpnfVFhNxq){bdFzNizzyT = true;}
      else if(HpnfVFhNxq == FYrfiAyBKA){jHlEByauyV = true;}
      if(xbUeJQrQKd == IlEZwqjzEM){WYDgWUATRg = true;}
      else if(IlEZwqjzEM == xbUeJQrQKd){PKBoHCuJCP = true;}
      if(VHbIZiKXfh == gIFRmtVItT){rVUcGtHbCk = true;}
      else if(gIFRmtVItT == VHbIZiKXfh){JlzTegtQmq = true;}
      if(EFneFJcndc == EAmtXMJKzS){GYFbjaIZkc = true;}
      else if(EAmtXMJKzS == EFneFJcndc){KYoWSDlWlM = true;}
      if(RTRScufNfJ == AwgszaoIiu){GPeVCDiiAO = true;}
      if(KUuJtywjFz == HykJEykVsb){ZJjYyGJcsS = true;}
      if(oaUbuqmpYA == iZSdmHzKCi){aWxNMySbxw = true;}
      while(AwgszaoIiu == RTRScufNfJ){VrhHNFcqJz = true;}
      while(HykJEykVsb == HykJEykVsb){nIPssyISYU = true;}
      while(iZSdmHzKCi == iZSdmHzKCi){EJIHKqUeWD = true;}
      if(hYzkLjbLSL == true){hYzkLjbLSL = false;}
      if(FNZyLFOcoY == true){FNZyLFOcoY = false;}
      if(bmQXiadCGq == true){bmQXiadCGq = false;}
      if(bdFzNizzyT == true){bdFzNizzyT = false;}
      if(WYDgWUATRg == true){WYDgWUATRg = false;}
      if(rVUcGtHbCk == true){rVUcGtHbCk = false;}
      if(GYFbjaIZkc == true){GYFbjaIZkc = false;}
      if(GPeVCDiiAO == true){GPeVCDiiAO = false;}
      if(ZJjYyGJcsS == true){ZJjYyGJcsS = false;}
      if(aWxNMySbxw == true){aWxNMySbxw = false;}
      if(MaioacpyaD == true){MaioacpyaD = false;}
      if(LXamLwngcd == true){LXamLwngcd = false;}
      if(QegRCiRRID == true){QegRCiRRID = false;}
      if(jHlEByauyV == true){jHlEByauyV = false;}
      if(PKBoHCuJCP == true){PKBoHCuJCP = false;}
      if(JlzTegtQmq == true){JlzTegtQmq = false;}
      if(KYoWSDlWlM == true){KYoWSDlWlM = false;}
      if(VrhHNFcqJz == true){VrhHNFcqJz = false;}
      if(nIPssyISYU == true){nIPssyISYU = false;}
      if(EJIHKqUeWD == true){EJIHKqUeWD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITVSWHMSEX
{ 
  void ejftupdbPQ()
  { 
      bool woHUJDsrcF = false;
      bool cgewOPEsfY = false;
      bool nDDtFHUTCQ = false;
      bool FixZwdYCfk = false;
      bool ffBptRQOww = false;
      bool HpdezslMOC = false;
      bool hZpMzsiEAk = false;
      bool qCMtsHBMAn = false;
      bool pGXGIPFRZD = false;
      bool rLndCGpoqA = false;
      bool iLOLEFcilr = false;
      bool qYMaLaBiDj = false;
      bool mRewreOiqm = false;
      bool QMVAEdrMBC = false;
      bool lVfhLTzMSa = false;
      bool EHkGMQgRSZ = false;
      bool qtryadCMVg = false;
      bool iogAxRlxkX = false;
      bool eBQPiJaOmn = false;
      bool xasaKrdgGg = false;
      string koIWcDwjtW;
      string bHHKxLUcHE;
      string KeLTaTNzWI;
      string rJKyBaVeUw;
      string NMSCXpxQji;
      string tfAlwGcnuI;
      string owNldSwIJV;
      string ppILqxMJwk;
      string WwOmNLIYCt;
      string ygiLGRzfXE;
      string soHNrEXoty;
      string sSqJlsgZYR;
      string JXGOXJGwEZ;
      string yfkqrgoAtJ;
      string nTeEBeoYYN;
      string jYHGuVirpi;
      string xbjUzMhzRE;
      string DfeOcorCNs;
      string TgWpoZYdwW;
      string ywKLLMjJEn;
      if(koIWcDwjtW == soHNrEXoty){woHUJDsrcF = true;}
      else if(soHNrEXoty == koIWcDwjtW){iLOLEFcilr = true;}
      if(bHHKxLUcHE == sSqJlsgZYR){cgewOPEsfY = true;}
      else if(sSqJlsgZYR == bHHKxLUcHE){qYMaLaBiDj = true;}
      if(KeLTaTNzWI == JXGOXJGwEZ){nDDtFHUTCQ = true;}
      else if(JXGOXJGwEZ == KeLTaTNzWI){mRewreOiqm = true;}
      if(rJKyBaVeUw == yfkqrgoAtJ){FixZwdYCfk = true;}
      else if(yfkqrgoAtJ == rJKyBaVeUw){QMVAEdrMBC = true;}
      if(NMSCXpxQji == nTeEBeoYYN){ffBptRQOww = true;}
      else if(nTeEBeoYYN == NMSCXpxQji){lVfhLTzMSa = true;}
      if(tfAlwGcnuI == jYHGuVirpi){HpdezslMOC = true;}
      else if(jYHGuVirpi == tfAlwGcnuI){EHkGMQgRSZ = true;}
      if(owNldSwIJV == xbjUzMhzRE){hZpMzsiEAk = true;}
      else if(xbjUzMhzRE == owNldSwIJV){qtryadCMVg = true;}
      if(ppILqxMJwk == DfeOcorCNs){qCMtsHBMAn = true;}
      if(WwOmNLIYCt == TgWpoZYdwW){pGXGIPFRZD = true;}
      if(ygiLGRzfXE == ywKLLMjJEn){rLndCGpoqA = true;}
      while(DfeOcorCNs == ppILqxMJwk){iogAxRlxkX = true;}
      while(TgWpoZYdwW == TgWpoZYdwW){eBQPiJaOmn = true;}
      while(ywKLLMjJEn == ywKLLMjJEn){xasaKrdgGg = true;}
      if(woHUJDsrcF == true){woHUJDsrcF = false;}
      if(cgewOPEsfY == true){cgewOPEsfY = false;}
      if(nDDtFHUTCQ == true){nDDtFHUTCQ = false;}
      if(FixZwdYCfk == true){FixZwdYCfk = false;}
      if(ffBptRQOww == true){ffBptRQOww = false;}
      if(HpdezslMOC == true){HpdezslMOC = false;}
      if(hZpMzsiEAk == true){hZpMzsiEAk = false;}
      if(qCMtsHBMAn == true){qCMtsHBMAn = false;}
      if(pGXGIPFRZD == true){pGXGIPFRZD = false;}
      if(rLndCGpoqA == true){rLndCGpoqA = false;}
      if(iLOLEFcilr == true){iLOLEFcilr = false;}
      if(qYMaLaBiDj == true){qYMaLaBiDj = false;}
      if(mRewreOiqm == true){mRewreOiqm = false;}
      if(QMVAEdrMBC == true){QMVAEdrMBC = false;}
      if(lVfhLTzMSa == true){lVfhLTzMSa = false;}
      if(EHkGMQgRSZ == true){EHkGMQgRSZ = false;}
      if(qtryadCMVg == true){qtryadCMVg = false;}
      if(iogAxRlxkX == true){iogAxRlxkX = false;}
      if(eBQPiJaOmn == true){eBQPiJaOmn = false;}
      if(xasaKrdgGg == true){xasaKrdgGg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNHDXOQPGY
{ 
  void MXaFEwoDBd()
  { 
      bool TFaDXfoQAD = false;
      bool ECVORGBnSd = false;
      bool ONCqyJaxmn = false;
      bool BLMZPNHcqb = false;
      bool kDUAyueKgZ = false;
      bool yizXAGCjFO = false;
      bool FqcMBrowzD = false;
      bool yXxprLrBrC = false;
      bool ePPNpRMnYI = false;
      bool LXXbWtZIzF = false;
      bool GhLdaalIfo = false;
      bool NAqCioaPVi = false;
      bool fBWprazUSy = false;
      bool kiClwwDllO = false;
      bool fDIiuKfUsg = false;
      bool SKlPZELVlz = false;
      bool aQogEdxEGm = false;
      bool locHCcrmug = false;
      bool udblfZwmMq = false;
      bool kgzlnPNbeQ = false;
      string ZHEnJINaSZ;
      string GpOauWbbjb;
      string bItKUpdftO;
      string HeNSCKrVfh;
      string kydaCfkUWt;
      string zKCGtRMtTS;
      string dgfDRacuXk;
      string dGuBqdeSHn;
      string FIJAOxbGXk;
      string xyBNDDRZJb;
      string DoxlPsPBOQ;
      string mslfMVXfoU;
      string zVWmmeEgxn;
      string LEJfkQLXjU;
      string garHxDLVAh;
      string fkknbhRKyk;
      string ohDaEhjGtw;
      string JAwTmYcPoi;
      string ThgOHaTVDD;
      string yAZzfzWRCO;
      if(ZHEnJINaSZ == DoxlPsPBOQ){TFaDXfoQAD = true;}
      else if(DoxlPsPBOQ == ZHEnJINaSZ){GhLdaalIfo = true;}
      if(GpOauWbbjb == mslfMVXfoU){ECVORGBnSd = true;}
      else if(mslfMVXfoU == GpOauWbbjb){NAqCioaPVi = true;}
      if(bItKUpdftO == zVWmmeEgxn){ONCqyJaxmn = true;}
      else if(zVWmmeEgxn == bItKUpdftO){fBWprazUSy = true;}
      if(HeNSCKrVfh == LEJfkQLXjU){BLMZPNHcqb = true;}
      else if(LEJfkQLXjU == HeNSCKrVfh){kiClwwDllO = true;}
      if(kydaCfkUWt == garHxDLVAh){kDUAyueKgZ = true;}
      else if(garHxDLVAh == kydaCfkUWt){fDIiuKfUsg = true;}
      if(zKCGtRMtTS == fkknbhRKyk){yizXAGCjFO = true;}
      else if(fkknbhRKyk == zKCGtRMtTS){SKlPZELVlz = true;}
      if(dgfDRacuXk == ohDaEhjGtw){FqcMBrowzD = true;}
      else if(ohDaEhjGtw == dgfDRacuXk){aQogEdxEGm = true;}
      if(dGuBqdeSHn == JAwTmYcPoi){yXxprLrBrC = true;}
      if(FIJAOxbGXk == ThgOHaTVDD){ePPNpRMnYI = true;}
      if(xyBNDDRZJb == yAZzfzWRCO){LXXbWtZIzF = true;}
      while(JAwTmYcPoi == dGuBqdeSHn){locHCcrmug = true;}
      while(ThgOHaTVDD == ThgOHaTVDD){udblfZwmMq = true;}
      while(yAZzfzWRCO == yAZzfzWRCO){kgzlnPNbeQ = true;}
      if(TFaDXfoQAD == true){TFaDXfoQAD = false;}
      if(ECVORGBnSd == true){ECVORGBnSd = false;}
      if(ONCqyJaxmn == true){ONCqyJaxmn = false;}
      if(BLMZPNHcqb == true){BLMZPNHcqb = false;}
      if(kDUAyueKgZ == true){kDUAyueKgZ = false;}
      if(yizXAGCjFO == true){yizXAGCjFO = false;}
      if(FqcMBrowzD == true){FqcMBrowzD = false;}
      if(yXxprLrBrC == true){yXxprLrBrC = false;}
      if(ePPNpRMnYI == true){ePPNpRMnYI = false;}
      if(LXXbWtZIzF == true){LXXbWtZIzF = false;}
      if(GhLdaalIfo == true){GhLdaalIfo = false;}
      if(NAqCioaPVi == true){NAqCioaPVi = false;}
      if(fBWprazUSy == true){fBWprazUSy = false;}
      if(kiClwwDllO == true){kiClwwDllO = false;}
      if(fDIiuKfUsg == true){fDIiuKfUsg = false;}
      if(SKlPZELVlz == true){SKlPZELVlz = false;}
      if(aQogEdxEGm == true){aQogEdxEGm = false;}
      if(locHCcrmug == true){locHCcrmug = false;}
      if(udblfZwmMq == true){udblfZwmMq = false;}
      if(kgzlnPNbeQ == true){kgzlnPNbeQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RBPQMWFYCX
{ 
  void XGzlLwZBlY()
  { 
      bool ruZZRVhgmU = false;
      bool PxLVeDZsOI = false;
      bool SwyfVXheZP = false;
      bool NcYmeywpAP = false;
      bool WgzsXWHQXI = false;
      bool qMmjuuxsDs = false;
      bool nCGXHlXXpg = false;
      bool GirylkwEIz = false;
      bool QQHRYAporj = false;
      bool AClGbTZblk = false;
      bool yiapBHUoyJ = false;
      bool zrkEcWuoyG = false;
      bool wifGfDwlWR = false;
      bool KTSWAgpQPR = false;
      bool fBqhkHRhcF = false;
      bool YkdeoPDUKx = false;
      bool KiSfyeZODw = false;
      bool fdYgaurxUX = false;
      bool lOIQsZpmgk = false;
      bool dVGSGxiKiG = false;
      string mCUPTFNAUo;
      string brcuxbWFnq;
      string WEsiBYylsZ;
      string WpePqcGKjk;
      string UejbJpBLMs;
      string ArnzZiJlOu;
      string HbHuSlMNDT;
      string ULUDVrUQYL;
      string WlZzYdBeoI;
      string TTwncsXnIX;
      string cnHsYnWkch;
      string NrNCYUBHVn;
      string jgYuzAPfZc;
      string TgIBiiegaj;
      string HQCGtbGsPH;
      string qPSUmuOLsX;
      string YpKANgjLTp;
      string pUgkgSeRAX;
      string sVQRlEOmNm;
      string TSmCLQFBsN;
      if(mCUPTFNAUo == cnHsYnWkch){ruZZRVhgmU = true;}
      else if(cnHsYnWkch == mCUPTFNAUo){yiapBHUoyJ = true;}
      if(brcuxbWFnq == NrNCYUBHVn){PxLVeDZsOI = true;}
      else if(NrNCYUBHVn == brcuxbWFnq){zrkEcWuoyG = true;}
      if(WEsiBYylsZ == jgYuzAPfZc){SwyfVXheZP = true;}
      else if(jgYuzAPfZc == WEsiBYylsZ){wifGfDwlWR = true;}
      if(WpePqcGKjk == TgIBiiegaj){NcYmeywpAP = true;}
      else if(TgIBiiegaj == WpePqcGKjk){KTSWAgpQPR = true;}
      if(UejbJpBLMs == HQCGtbGsPH){WgzsXWHQXI = true;}
      else if(HQCGtbGsPH == UejbJpBLMs){fBqhkHRhcF = true;}
      if(ArnzZiJlOu == qPSUmuOLsX){qMmjuuxsDs = true;}
      else if(qPSUmuOLsX == ArnzZiJlOu){YkdeoPDUKx = true;}
      if(HbHuSlMNDT == YpKANgjLTp){nCGXHlXXpg = true;}
      else if(YpKANgjLTp == HbHuSlMNDT){KiSfyeZODw = true;}
      if(ULUDVrUQYL == pUgkgSeRAX){GirylkwEIz = true;}
      if(WlZzYdBeoI == sVQRlEOmNm){QQHRYAporj = true;}
      if(TTwncsXnIX == TSmCLQFBsN){AClGbTZblk = true;}
      while(pUgkgSeRAX == ULUDVrUQYL){fdYgaurxUX = true;}
      while(sVQRlEOmNm == sVQRlEOmNm){lOIQsZpmgk = true;}
      while(TSmCLQFBsN == TSmCLQFBsN){dVGSGxiKiG = true;}
      if(ruZZRVhgmU == true){ruZZRVhgmU = false;}
      if(PxLVeDZsOI == true){PxLVeDZsOI = false;}
      if(SwyfVXheZP == true){SwyfVXheZP = false;}
      if(NcYmeywpAP == true){NcYmeywpAP = false;}
      if(WgzsXWHQXI == true){WgzsXWHQXI = false;}
      if(qMmjuuxsDs == true){qMmjuuxsDs = false;}
      if(nCGXHlXXpg == true){nCGXHlXXpg = false;}
      if(GirylkwEIz == true){GirylkwEIz = false;}
      if(QQHRYAporj == true){QQHRYAporj = false;}
      if(AClGbTZblk == true){AClGbTZblk = false;}
      if(yiapBHUoyJ == true){yiapBHUoyJ = false;}
      if(zrkEcWuoyG == true){zrkEcWuoyG = false;}
      if(wifGfDwlWR == true){wifGfDwlWR = false;}
      if(KTSWAgpQPR == true){KTSWAgpQPR = false;}
      if(fBqhkHRhcF == true){fBqhkHRhcF = false;}
      if(YkdeoPDUKx == true){YkdeoPDUKx = false;}
      if(KiSfyeZODw == true){KiSfyeZODw = false;}
      if(fdYgaurxUX == true){fdYgaurxUX = false;}
      if(lOIQsZpmgk == true){lOIQsZpmgk = false;}
      if(dVGSGxiKiG == true){dVGSGxiKiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOIMUJYWSX
{ 
  void cakSoZEyWB()
  { 
      bool ddgMAoLnXQ = false;
      bool VNeBcDNDuZ = false;
      bool XFDsDJhytj = false;
      bool rCysgMemoJ = false;
      bool nmeFURBRkD = false;
      bool mjqGiXZnIq = false;
      bool GNtmYSOkTQ = false;
      bool YZOllkayXk = false;
      bool HQMpwILqKI = false;
      bool lpdyCZrqfC = false;
      bool CPxTeMVFUx = false;
      bool xbQXipADpQ = false;
      bool GXaLehwPiL = false;
      bool riRUirTsLj = false;
      bool lGVMKJZGPM = false;
      bool ZoAPwenlnx = false;
      bool QFVJEOJwop = false;
      bool WHqGdABNAV = false;
      bool HpAWlDiCYD = false;
      bool DhENSgjMIw = false;
      string rnhXsfXrms;
      string ZzqEBPDMaF;
      string AryJDfYCCt;
      string YFMxXxWWPB;
      string rIKcdTaVNG;
      string aEzwpzpYTM;
      string GUpsTTmtgE;
      string rfxZMqhUei;
      string FDouSUGQGX;
      string HyCCtWSQIK;
      string ggoJNtHYiz;
      string QUtkHDftZz;
      string NVmIxtdtfo;
      string YRMTBYNehX;
      string NggHGlDQup;
      string pYpJxKsgMT;
      string QMstZzIZii;
      string pBMCkfofBK;
      string pMzoyAaCWp;
      string egSOHAnlgH;
      if(rnhXsfXrms == ggoJNtHYiz){ddgMAoLnXQ = true;}
      else if(ggoJNtHYiz == rnhXsfXrms){CPxTeMVFUx = true;}
      if(ZzqEBPDMaF == QUtkHDftZz){VNeBcDNDuZ = true;}
      else if(QUtkHDftZz == ZzqEBPDMaF){xbQXipADpQ = true;}
      if(AryJDfYCCt == NVmIxtdtfo){XFDsDJhytj = true;}
      else if(NVmIxtdtfo == AryJDfYCCt){GXaLehwPiL = true;}
      if(YFMxXxWWPB == YRMTBYNehX){rCysgMemoJ = true;}
      else if(YRMTBYNehX == YFMxXxWWPB){riRUirTsLj = true;}
      if(rIKcdTaVNG == NggHGlDQup){nmeFURBRkD = true;}
      else if(NggHGlDQup == rIKcdTaVNG){lGVMKJZGPM = true;}
      if(aEzwpzpYTM == pYpJxKsgMT){mjqGiXZnIq = true;}
      else if(pYpJxKsgMT == aEzwpzpYTM){ZoAPwenlnx = true;}
      if(GUpsTTmtgE == QMstZzIZii){GNtmYSOkTQ = true;}
      else if(QMstZzIZii == GUpsTTmtgE){QFVJEOJwop = true;}
      if(rfxZMqhUei == pBMCkfofBK){YZOllkayXk = true;}
      if(FDouSUGQGX == pMzoyAaCWp){HQMpwILqKI = true;}
      if(HyCCtWSQIK == egSOHAnlgH){lpdyCZrqfC = true;}
      while(pBMCkfofBK == rfxZMqhUei){WHqGdABNAV = true;}
      while(pMzoyAaCWp == pMzoyAaCWp){HpAWlDiCYD = true;}
      while(egSOHAnlgH == egSOHAnlgH){DhENSgjMIw = true;}
      if(ddgMAoLnXQ == true){ddgMAoLnXQ = false;}
      if(VNeBcDNDuZ == true){VNeBcDNDuZ = false;}
      if(XFDsDJhytj == true){XFDsDJhytj = false;}
      if(rCysgMemoJ == true){rCysgMemoJ = false;}
      if(nmeFURBRkD == true){nmeFURBRkD = false;}
      if(mjqGiXZnIq == true){mjqGiXZnIq = false;}
      if(GNtmYSOkTQ == true){GNtmYSOkTQ = false;}
      if(YZOllkayXk == true){YZOllkayXk = false;}
      if(HQMpwILqKI == true){HQMpwILqKI = false;}
      if(lpdyCZrqfC == true){lpdyCZrqfC = false;}
      if(CPxTeMVFUx == true){CPxTeMVFUx = false;}
      if(xbQXipADpQ == true){xbQXipADpQ = false;}
      if(GXaLehwPiL == true){GXaLehwPiL = false;}
      if(riRUirTsLj == true){riRUirTsLj = false;}
      if(lGVMKJZGPM == true){lGVMKJZGPM = false;}
      if(ZoAPwenlnx == true){ZoAPwenlnx = false;}
      if(QFVJEOJwop == true){QFVJEOJwop = false;}
      if(WHqGdABNAV == true){WHqGdABNAV = false;}
      if(HpAWlDiCYD == true){HpAWlDiCYD = false;}
      if(DhENSgjMIw == true){DhENSgjMIw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQDFNIQPWI
{ 
  void VfimkmxlrS()
  { 
      bool VCLcOznXKD = false;
      bool EVQnJRzCnf = false;
      bool lEFREFMcbk = false;
      bool qiTccVOLbV = false;
      bool zJBVfLXwss = false;
      bool YyFsWQxtYJ = false;
      bool lKuYMVBmLm = false;
      bool DnZRfbDilr = false;
      bool gQjiMsdaFL = false;
      bool YUlRjoNcJJ = false;
      bool KjjFpkXmNu = false;
      bool NNHgbUaMMS = false;
      bool qagzOiBIhq = false;
      bool OZYbhxfdra = false;
      bool UpMKyKMFpO = false;
      bool NBPpRjCjqH = false;
      bool iPFVfmofye = false;
      bool nwUkyBNWBE = false;
      bool VwRScNKhJy = false;
      bool tumkrFkqdL = false;
      string bKMAtfziHc;
      string xAwzWZBgoP;
      string NUpICLhkwi;
      string AZpnuClfft;
      string fVZTEXLWpZ;
      string AtnKSGTDyh;
      string yOlYcXKIDT;
      string mUBuiqtWDe;
      string zLtWhFleUn;
      string ihgxuQiBqg;
      string MDSWlerrbb;
      string LwAThmUPpW;
      string kfmOjFnEzR;
      string HrfVRwrWjC;
      string MsDsclgNOI;
      string wTLTugPDlg;
      string qnrJTSQeCk;
      string txfmJrctly;
      string XZopUngLZj;
      string gojCKYAsZJ;
      if(bKMAtfziHc == MDSWlerrbb){VCLcOznXKD = true;}
      else if(MDSWlerrbb == bKMAtfziHc){KjjFpkXmNu = true;}
      if(xAwzWZBgoP == LwAThmUPpW){EVQnJRzCnf = true;}
      else if(LwAThmUPpW == xAwzWZBgoP){NNHgbUaMMS = true;}
      if(NUpICLhkwi == kfmOjFnEzR){lEFREFMcbk = true;}
      else if(kfmOjFnEzR == NUpICLhkwi){qagzOiBIhq = true;}
      if(AZpnuClfft == HrfVRwrWjC){qiTccVOLbV = true;}
      else if(HrfVRwrWjC == AZpnuClfft){OZYbhxfdra = true;}
      if(fVZTEXLWpZ == MsDsclgNOI){zJBVfLXwss = true;}
      else if(MsDsclgNOI == fVZTEXLWpZ){UpMKyKMFpO = true;}
      if(AtnKSGTDyh == wTLTugPDlg){YyFsWQxtYJ = true;}
      else if(wTLTugPDlg == AtnKSGTDyh){NBPpRjCjqH = true;}
      if(yOlYcXKIDT == qnrJTSQeCk){lKuYMVBmLm = true;}
      else if(qnrJTSQeCk == yOlYcXKIDT){iPFVfmofye = true;}
      if(mUBuiqtWDe == txfmJrctly){DnZRfbDilr = true;}
      if(zLtWhFleUn == XZopUngLZj){gQjiMsdaFL = true;}
      if(ihgxuQiBqg == gojCKYAsZJ){YUlRjoNcJJ = true;}
      while(txfmJrctly == mUBuiqtWDe){nwUkyBNWBE = true;}
      while(XZopUngLZj == XZopUngLZj){VwRScNKhJy = true;}
      while(gojCKYAsZJ == gojCKYAsZJ){tumkrFkqdL = true;}
      if(VCLcOznXKD == true){VCLcOznXKD = false;}
      if(EVQnJRzCnf == true){EVQnJRzCnf = false;}
      if(lEFREFMcbk == true){lEFREFMcbk = false;}
      if(qiTccVOLbV == true){qiTccVOLbV = false;}
      if(zJBVfLXwss == true){zJBVfLXwss = false;}
      if(YyFsWQxtYJ == true){YyFsWQxtYJ = false;}
      if(lKuYMVBmLm == true){lKuYMVBmLm = false;}
      if(DnZRfbDilr == true){DnZRfbDilr = false;}
      if(gQjiMsdaFL == true){gQjiMsdaFL = false;}
      if(YUlRjoNcJJ == true){YUlRjoNcJJ = false;}
      if(KjjFpkXmNu == true){KjjFpkXmNu = false;}
      if(NNHgbUaMMS == true){NNHgbUaMMS = false;}
      if(qagzOiBIhq == true){qagzOiBIhq = false;}
      if(OZYbhxfdra == true){OZYbhxfdra = false;}
      if(UpMKyKMFpO == true){UpMKyKMFpO = false;}
      if(NBPpRjCjqH == true){NBPpRjCjqH = false;}
      if(iPFVfmofye == true){iPFVfmofye = false;}
      if(nwUkyBNWBE == true){nwUkyBNWBE = false;}
      if(VwRScNKhJy == true){VwRScNKhJy = false;}
      if(tumkrFkqdL == true){tumkrFkqdL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHBAPNMXIB
{ 
  void NOjwxpezkJ()
  { 
      bool QiDtFOOACC = false;
      bool rpnCijZtot = false;
      bool CDFgjaMPbj = false;
      bool yEumeWVbXI = false;
      bool KtkxTkCtYy = false;
      bool wWLOOMcVKe = false;
      bool CyYSDnuAWM = false;
      bool OxWgjISIMz = false;
      bool XRqdmbrfXR = false;
      bool szQsGLVRse = false;
      bool pBWLjyAeeG = false;
      bool tUJLGkHueb = false;
      bool uObFTOgcaY = false;
      bool lAOgIWteso = false;
      bool bNBRWXpFlU = false;
      bool DalRjaYRrV = false;
      bool RWEFUtFbCj = false;
      bool pbBpAhNKhu = false;
      bool XaqFUKOxxh = false;
      bool xcmXXEJuxc = false;
      string ngIWyxoZxk;
      string nCFkGkxeru;
      string hNSqqTArXV;
      string ZQHMuJddRT;
      string XMqqyNUDxp;
      string ykzgCaORfe;
      string xxCbLXurox;
      string HTNYWVVbsc;
      string ywtgXnQZJU;
      string tMylWaJPeZ;
      string ScNAieWaKg;
      string EmXCgACVDW;
      string GUhUCtUbBw;
      string MGwSJVitxs;
      string RpPcPHnuFW;
      string XmLISytrxo;
      string JuYNTyqFrK;
      string QIYKFQFEEu;
      string FYVdXYumzL;
      string apwIiVRBJR;
      if(ngIWyxoZxk == ScNAieWaKg){QiDtFOOACC = true;}
      else if(ScNAieWaKg == ngIWyxoZxk){pBWLjyAeeG = true;}
      if(nCFkGkxeru == EmXCgACVDW){rpnCijZtot = true;}
      else if(EmXCgACVDW == nCFkGkxeru){tUJLGkHueb = true;}
      if(hNSqqTArXV == GUhUCtUbBw){CDFgjaMPbj = true;}
      else if(GUhUCtUbBw == hNSqqTArXV){uObFTOgcaY = true;}
      if(ZQHMuJddRT == MGwSJVitxs){yEumeWVbXI = true;}
      else if(MGwSJVitxs == ZQHMuJddRT){lAOgIWteso = true;}
      if(XMqqyNUDxp == RpPcPHnuFW){KtkxTkCtYy = true;}
      else if(RpPcPHnuFW == XMqqyNUDxp){bNBRWXpFlU = true;}
      if(ykzgCaORfe == XmLISytrxo){wWLOOMcVKe = true;}
      else if(XmLISytrxo == ykzgCaORfe){DalRjaYRrV = true;}
      if(xxCbLXurox == JuYNTyqFrK){CyYSDnuAWM = true;}
      else if(JuYNTyqFrK == xxCbLXurox){RWEFUtFbCj = true;}
      if(HTNYWVVbsc == QIYKFQFEEu){OxWgjISIMz = true;}
      if(ywtgXnQZJU == FYVdXYumzL){XRqdmbrfXR = true;}
      if(tMylWaJPeZ == apwIiVRBJR){szQsGLVRse = true;}
      while(QIYKFQFEEu == HTNYWVVbsc){pbBpAhNKhu = true;}
      while(FYVdXYumzL == FYVdXYumzL){XaqFUKOxxh = true;}
      while(apwIiVRBJR == apwIiVRBJR){xcmXXEJuxc = true;}
      if(QiDtFOOACC == true){QiDtFOOACC = false;}
      if(rpnCijZtot == true){rpnCijZtot = false;}
      if(CDFgjaMPbj == true){CDFgjaMPbj = false;}
      if(yEumeWVbXI == true){yEumeWVbXI = false;}
      if(KtkxTkCtYy == true){KtkxTkCtYy = false;}
      if(wWLOOMcVKe == true){wWLOOMcVKe = false;}
      if(CyYSDnuAWM == true){CyYSDnuAWM = false;}
      if(OxWgjISIMz == true){OxWgjISIMz = false;}
      if(XRqdmbrfXR == true){XRqdmbrfXR = false;}
      if(szQsGLVRse == true){szQsGLVRse = false;}
      if(pBWLjyAeeG == true){pBWLjyAeeG = false;}
      if(tUJLGkHueb == true){tUJLGkHueb = false;}
      if(uObFTOgcaY == true){uObFTOgcaY = false;}
      if(lAOgIWteso == true){lAOgIWteso = false;}
      if(bNBRWXpFlU == true){bNBRWXpFlU = false;}
      if(DalRjaYRrV == true){DalRjaYRrV = false;}
      if(RWEFUtFbCj == true){RWEFUtFbCj = false;}
      if(pbBpAhNKhu == true){pbBpAhNKhu = false;}
      if(XaqFUKOxxh == true){XaqFUKOxxh = false;}
      if(xcmXXEJuxc == true){xcmXXEJuxc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZMWZPLBZB
{ 
  void HezEMXCCed()
  { 
      bool OpLbrdDPIU = false;
      bool TOLGdtojiC = false;
      bool pidobrVMfa = false;
      bool UZbFuOkdAS = false;
      bool KOweifkeBK = false;
      bool WskihfLWzz = false;
      bool HqigzsmFLO = false;
      bool ILiQrbmyGu = false;
      bool HqLVEborWP = false;
      bool DOdAKSePeo = false;
      bool seTlBLKTpG = false;
      bool rNQErQfNbX = false;
      bool DthuLtghFY = false;
      bool wXSQCbWYTr = false;
      bool QVCQWpyZIs = false;
      bool mQmGkzwXaH = false;
      bool ebOQJUtABP = false;
      bool tHtiHhqRYV = false;
      bool uGZLlfjLeD = false;
      bool eyyLNnGkGB = false;
      string mXIXJsFCgH;
      string BJKTcwStIP;
      string pZpWnBWOYG;
      string DpDPFYEAzc;
      string meKxhOmZhB;
      string NuhplNgljH;
      string WqdaELGtND;
      string rSufcKOsoZ;
      string OxgXrHHMdq;
      string qRPqGuBirV;
      string HrLdJuzCNa;
      string znxKsZKFiw;
      string DsQWMZCEYh;
      string JeASRWkCOx;
      string IFzCrCUEyf;
      string kuAwSOboQi;
      string ruceQTmdsW;
      string nHqknxtNdK;
      string FxFswOdEAD;
      string twkeFMcTlX;
      if(mXIXJsFCgH == HrLdJuzCNa){OpLbrdDPIU = true;}
      else if(HrLdJuzCNa == mXIXJsFCgH){seTlBLKTpG = true;}
      if(BJKTcwStIP == znxKsZKFiw){TOLGdtojiC = true;}
      else if(znxKsZKFiw == BJKTcwStIP){rNQErQfNbX = true;}
      if(pZpWnBWOYG == DsQWMZCEYh){pidobrVMfa = true;}
      else if(DsQWMZCEYh == pZpWnBWOYG){DthuLtghFY = true;}
      if(DpDPFYEAzc == JeASRWkCOx){UZbFuOkdAS = true;}
      else if(JeASRWkCOx == DpDPFYEAzc){wXSQCbWYTr = true;}
      if(meKxhOmZhB == IFzCrCUEyf){KOweifkeBK = true;}
      else if(IFzCrCUEyf == meKxhOmZhB){QVCQWpyZIs = true;}
      if(NuhplNgljH == kuAwSOboQi){WskihfLWzz = true;}
      else if(kuAwSOboQi == NuhplNgljH){mQmGkzwXaH = true;}
      if(WqdaELGtND == ruceQTmdsW){HqigzsmFLO = true;}
      else if(ruceQTmdsW == WqdaELGtND){ebOQJUtABP = true;}
      if(rSufcKOsoZ == nHqknxtNdK){ILiQrbmyGu = true;}
      if(OxgXrHHMdq == FxFswOdEAD){HqLVEborWP = true;}
      if(qRPqGuBirV == twkeFMcTlX){DOdAKSePeo = true;}
      while(nHqknxtNdK == rSufcKOsoZ){tHtiHhqRYV = true;}
      while(FxFswOdEAD == FxFswOdEAD){uGZLlfjLeD = true;}
      while(twkeFMcTlX == twkeFMcTlX){eyyLNnGkGB = true;}
      if(OpLbrdDPIU == true){OpLbrdDPIU = false;}
      if(TOLGdtojiC == true){TOLGdtojiC = false;}
      if(pidobrVMfa == true){pidobrVMfa = false;}
      if(UZbFuOkdAS == true){UZbFuOkdAS = false;}
      if(KOweifkeBK == true){KOweifkeBK = false;}
      if(WskihfLWzz == true){WskihfLWzz = false;}
      if(HqigzsmFLO == true){HqigzsmFLO = false;}
      if(ILiQrbmyGu == true){ILiQrbmyGu = false;}
      if(HqLVEborWP == true){HqLVEborWP = false;}
      if(DOdAKSePeo == true){DOdAKSePeo = false;}
      if(seTlBLKTpG == true){seTlBLKTpG = false;}
      if(rNQErQfNbX == true){rNQErQfNbX = false;}
      if(DthuLtghFY == true){DthuLtghFY = false;}
      if(wXSQCbWYTr == true){wXSQCbWYTr = false;}
      if(QVCQWpyZIs == true){QVCQWpyZIs = false;}
      if(mQmGkzwXaH == true){mQmGkzwXaH = false;}
      if(ebOQJUtABP == true){ebOQJUtABP = false;}
      if(tHtiHhqRYV == true){tHtiHhqRYV = false;}
      if(uGZLlfjLeD == true){uGZLlfjLeD = false;}
      if(eyyLNnGkGB == true){eyyLNnGkGB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OAUZFCVBKL
{ 
  void TiJpyIQbPI()
  { 
      bool qHpozpoKie = false;
      bool owjfLTtOTE = false;
      bool mPuZjZgJAW = false;
      bool NpiHEbJgTj = false;
      bool zImFIyAEQz = false;
      bool gSkMJbLQEY = false;
      bool JfJLQyMcai = false;
      bool KMuiEdbpQk = false;
      bool ZcrAouEWyc = false;
      bool QrbtZSyanJ = false;
      bool lWcgoUWCHe = false;
      bool zUzTzgmJVV = false;
      bool tpdySRjAJl = false;
      bool fBCHzCzLLU = false;
      bool XCOTcusIur = false;
      bool foERPuseOW = false;
      bool jVrVzySrUw = false;
      bool hbxBxrbKUX = false;
      bool YbFQGpxjrD = false;
      bool JUxnjBJrTe = false;
      string qCxbJdwPLa;
      string muIESRLrUz;
      string nCnMLlZENh;
      string kFZdsdPgMy;
      string emRNRAlFpV;
      string MlfxKnNkPW;
      string ErBdohVdKn;
      string CefVUBkatL;
      string ATOqVyYbTE;
      string PeRpslkmXj;
      string dHtBTgGJcJ;
      string DmpEWjdJIp;
      string JtKFYXNoci;
      string PxCKgrYMXn;
      string rOzKBbnNSJ;
      string HaegZjxncu;
      string TQgtsFkfWd;
      string KQlUyuuAEw;
      string jzVSaoSVjx;
      string tjjbTbgEQw;
      if(qCxbJdwPLa == dHtBTgGJcJ){qHpozpoKie = true;}
      else if(dHtBTgGJcJ == qCxbJdwPLa){lWcgoUWCHe = true;}
      if(muIESRLrUz == DmpEWjdJIp){owjfLTtOTE = true;}
      else if(DmpEWjdJIp == muIESRLrUz){zUzTzgmJVV = true;}
      if(nCnMLlZENh == JtKFYXNoci){mPuZjZgJAW = true;}
      else if(JtKFYXNoci == nCnMLlZENh){tpdySRjAJl = true;}
      if(kFZdsdPgMy == PxCKgrYMXn){NpiHEbJgTj = true;}
      else if(PxCKgrYMXn == kFZdsdPgMy){fBCHzCzLLU = true;}
      if(emRNRAlFpV == rOzKBbnNSJ){zImFIyAEQz = true;}
      else if(rOzKBbnNSJ == emRNRAlFpV){XCOTcusIur = true;}
      if(MlfxKnNkPW == HaegZjxncu){gSkMJbLQEY = true;}
      else if(HaegZjxncu == MlfxKnNkPW){foERPuseOW = true;}
      if(ErBdohVdKn == TQgtsFkfWd){JfJLQyMcai = true;}
      else if(TQgtsFkfWd == ErBdohVdKn){jVrVzySrUw = true;}
      if(CefVUBkatL == KQlUyuuAEw){KMuiEdbpQk = true;}
      if(ATOqVyYbTE == jzVSaoSVjx){ZcrAouEWyc = true;}
      if(PeRpslkmXj == tjjbTbgEQw){QrbtZSyanJ = true;}
      while(KQlUyuuAEw == CefVUBkatL){hbxBxrbKUX = true;}
      while(jzVSaoSVjx == jzVSaoSVjx){YbFQGpxjrD = true;}
      while(tjjbTbgEQw == tjjbTbgEQw){JUxnjBJrTe = true;}
      if(qHpozpoKie == true){qHpozpoKie = false;}
      if(owjfLTtOTE == true){owjfLTtOTE = false;}
      if(mPuZjZgJAW == true){mPuZjZgJAW = false;}
      if(NpiHEbJgTj == true){NpiHEbJgTj = false;}
      if(zImFIyAEQz == true){zImFIyAEQz = false;}
      if(gSkMJbLQEY == true){gSkMJbLQEY = false;}
      if(JfJLQyMcai == true){JfJLQyMcai = false;}
      if(KMuiEdbpQk == true){KMuiEdbpQk = false;}
      if(ZcrAouEWyc == true){ZcrAouEWyc = false;}
      if(QrbtZSyanJ == true){QrbtZSyanJ = false;}
      if(lWcgoUWCHe == true){lWcgoUWCHe = false;}
      if(zUzTzgmJVV == true){zUzTzgmJVV = false;}
      if(tpdySRjAJl == true){tpdySRjAJl = false;}
      if(fBCHzCzLLU == true){fBCHzCzLLU = false;}
      if(XCOTcusIur == true){XCOTcusIur = false;}
      if(foERPuseOW == true){foERPuseOW = false;}
      if(jVrVzySrUw == true){jVrVzySrUw = false;}
      if(hbxBxrbKUX == true){hbxBxrbKUX = false;}
      if(YbFQGpxjrD == true){YbFQGpxjrD = false;}
      if(JUxnjBJrTe == true){JUxnjBJrTe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRYQQFUYSS
{ 
  void ohYRzWGUFW()
  { 
      bool pIdYJmKeDf = false;
      bool BugftkJfeK = false;
      bool SRkuySWaIN = false;
      bool yGygisrLlF = false;
      bool GdHakhVxSX = false;
      bool TwOaFYWiZq = false;
      bool QiWpguwAwA = false;
      bool sysYDoKJKQ = false;
      bool wZHksCrXaK = false;
      bool VJkuoWHQto = false;
      bool kVAReUCoWQ = false;
      bool NNXJtqalwe = false;
      bool DXYleiMyif = false;
      bool hsPUeaYpFY = false;
      bool ACBJwIlaAy = false;
      bool uUUOlMxOmu = false;
      bool IDGpiTxCeT = false;
      bool RkfXdBWOoV = false;
      bool wlxkkMYAiR = false;
      bool dKCKPwwKab = false;
      string rBilRXBSRa;
      string bTwCHUcSMs;
      string GTydKCZiOV;
      string FkfAJHLKyq;
      string oxdfcFVmAH;
      string LAZJyYCFbO;
      string ySDuUpmwrz;
      string ISUUEIoRAF;
      string fliHKEKWBk;
      string FGiirWthLm;
      string RYuAyrfFFo;
      string ijFVhMiwjP;
      string fQuHtCjkbg;
      string OHGNmGqiIS;
      string YFQLBUAMAf;
      string mxxuGBdmFw;
      string IucXabdrha;
      string VAmRqaziGZ;
      string BWkwsQJLGl;
      string cDcMJdbskY;
      if(rBilRXBSRa == RYuAyrfFFo){pIdYJmKeDf = true;}
      else if(RYuAyrfFFo == rBilRXBSRa){kVAReUCoWQ = true;}
      if(bTwCHUcSMs == ijFVhMiwjP){BugftkJfeK = true;}
      else if(ijFVhMiwjP == bTwCHUcSMs){NNXJtqalwe = true;}
      if(GTydKCZiOV == fQuHtCjkbg){SRkuySWaIN = true;}
      else if(fQuHtCjkbg == GTydKCZiOV){DXYleiMyif = true;}
      if(FkfAJHLKyq == OHGNmGqiIS){yGygisrLlF = true;}
      else if(OHGNmGqiIS == FkfAJHLKyq){hsPUeaYpFY = true;}
      if(oxdfcFVmAH == YFQLBUAMAf){GdHakhVxSX = true;}
      else if(YFQLBUAMAf == oxdfcFVmAH){ACBJwIlaAy = true;}
      if(LAZJyYCFbO == mxxuGBdmFw){TwOaFYWiZq = true;}
      else if(mxxuGBdmFw == LAZJyYCFbO){uUUOlMxOmu = true;}
      if(ySDuUpmwrz == IucXabdrha){QiWpguwAwA = true;}
      else if(IucXabdrha == ySDuUpmwrz){IDGpiTxCeT = true;}
      if(ISUUEIoRAF == VAmRqaziGZ){sysYDoKJKQ = true;}
      if(fliHKEKWBk == BWkwsQJLGl){wZHksCrXaK = true;}
      if(FGiirWthLm == cDcMJdbskY){VJkuoWHQto = true;}
      while(VAmRqaziGZ == ISUUEIoRAF){RkfXdBWOoV = true;}
      while(BWkwsQJLGl == BWkwsQJLGl){wlxkkMYAiR = true;}
      while(cDcMJdbskY == cDcMJdbskY){dKCKPwwKab = true;}
      if(pIdYJmKeDf == true){pIdYJmKeDf = false;}
      if(BugftkJfeK == true){BugftkJfeK = false;}
      if(SRkuySWaIN == true){SRkuySWaIN = false;}
      if(yGygisrLlF == true){yGygisrLlF = false;}
      if(GdHakhVxSX == true){GdHakhVxSX = false;}
      if(TwOaFYWiZq == true){TwOaFYWiZq = false;}
      if(QiWpguwAwA == true){QiWpguwAwA = false;}
      if(sysYDoKJKQ == true){sysYDoKJKQ = false;}
      if(wZHksCrXaK == true){wZHksCrXaK = false;}
      if(VJkuoWHQto == true){VJkuoWHQto = false;}
      if(kVAReUCoWQ == true){kVAReUCoWQ = false;}
      if(NNXJtqalwe == true){NNXJtqalwe = false;}
      if(DXYleiMyif == true){DXYleiMyif = false;}
      if(hsPUeaYpFY == true){hsPUeaYpFY = false;}
      if(ACBJwIlaAy == true){ACBJwIlaAy = false;}
      if(uUUOlMxOmu == true){uUUOlMxOmu = false;}
      if(IDGpiTxCeT == true){IDGpiTxCeT = false;}
      if(RkfXdBWOoV == true){RkfXdBWOoV = false;}
      if(wlxkkMYAiR == true){wlxkkMYAiR = false;}
      if(dKCKPwwKab == true){dKCKPwwKab = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIYCCCMMIT
{ 
  void oRzudAmwiL()
  { 
      bool ZYVgExVkVU = false;
      bool HzzCnYouJh = false;
      bool YqSEiLWPFC = false;
      bool pVrxoanXPS = false;
      bool AqyDTkdEJt = false;
      bool XaswthFQxs = false;
      bool ZFeSdlHCMM = false;
      bool jQephhrPky = false;
      bool hSGKdPbwCH = false;
      bool VXZVstLfYh = false;
      bool daqwKGuDNL = false;
      bool ooezLHzToO = false;
      bool JLzFpMpJwm = false;
      bool VMpDUGaJAW = false;
      bool UYhqRfraKl = false;
      bool urqKXRalFy = false;
      bool QlGapczbeE = false;
      bool fpSRskcImK = false;
      bool TPyKrdVfeC = false;
      bool fnDCGiRGAo = false;
      string yeRwVLLQVU;
      string tgsLmhWWrx;
      string OlzfSKjQau;
      string qgksThBTnC;
      string ZYMlsdaqXj;
      string xiSpAMeldK;
      string aupZdMwzqE;
      string fCioWoYNmo;
      string isrpxHOusH;
      string DPpcbeimHf;
      string gbzTEuAcSK;
      string mRznbhCzbW;
      string yBFjBQLGNr;
      string FlFGHHsYlC;
      string HkciTlQCBs;
      string bjKkhfVPRn;
      string itPZEALrfT;
      string ndNZPMXWPP;
      string zJETQVbTYb;
      string kcGxTMVCdS;
      if(yeRwVLLQVU == gbzTEuAcSK){ZYVgExVkVU = true;}
      else if(gbzTEuAcSK == yeRwVLLQVU){daqwKGuDNL = true;}
      if(tgsLmhWWrx == mRznbhCzbW){HzzCnYouJh = true;}
      else if(mRznbhCzbW == tgsLmhWWrx){ooezLHzToO = true;}
      if(OlzfSKjQau == yBFjBQLGNr){YqSEiLWPFC = true;}
      else if(yBFjBQLGNr == OlzfSKjQau){JLzFpMpJwm = true;}
      if(qgksThBTnC == FlFGHHsYlC){pVrxoanXPS = true;}
      else if(FlFGHHsYlC == qgksThBTnC){VMpDUGaJAW = true;}
      if(ZYMlsdaqXj == HkciTlQCBs){AqyDTkdEJt = true;}
      else if(HkciTlQCBs == ZYMlsdaqXj){UYhqRfraKl = true;}
      if(xiSpAMeldK == bjKkhfVPRn){XaswthFQxs = true;}
      else if(bjKkhfVPRn == xiSpAMeldK){urqKXRalFy = true;}
      if(aupZdMwzqE == itPZEALrfT){ZFeSdlHCMM = true;}
      else if(itPZEALrfT == aupZdMwzqE){QlGapczbeE = true;}
      if(fCioWoYNmo == ndNZPMXWPP){jQephhrPky = true;}
      if(isrpxHOusH == zJETQVbTYb){hSGKdPbwCH = true;}
      if(DPpcbeimHf == kcGxTMVCdS){VXZVstLfYh = true;}
      while(ndNZPMXWPP == fCioWoYNmo){fpSRskcImK = true;}
      while(zJETQVbTYb == zJETQVbTYb){TPyKrdVfeC = true;}
      while(kcGxTMVCdS == kcGxTMVCdS){fnDCGiRGAo = true;}
      if(ZYVgExVkVU == true){ZYVgExVkVU = false;}
      if(HzzCnYouJh == true){HzzCnYouJh = false;}
      if(YqSEiLWPFC == true){YqSEiLWPFC = false;}
      if(pVrxoanXPS == true){pVrxoanXPS = false;}
      if(AqyDTkdEJt == true){AqyDTkdEJt = false;}
      if(XaswthFQxs == true){XaswthFQxs = false;}
      if(ZFeSdlHCMM == true){ZFeSdlHCMM = false;}
      if(jQephhrPky == true){jQephhrPky = false;}
      if(hSGKdPbwCH == true){hSGKdPbwCH = false;}
      if(VXZVstLfYh == true){VXZVstLfYh = false;}
      if(daqwKGuDNL == true){daqwKGuDNL = false;}
      if(ooezLHzToO == true){ooezLHzToO = false;}
      if(JLzFpMpJwm == true){JLzFpMpJwm = false;}
      if(VMpDUGaJAW == true){VMpDUGaJAW = false;}
      if(UYhqRfraKl == true){UYhqRfraKl = false;}
      if(urqKXRalFy == true){urqKXRalFy = false;}
      if(QlGapczbeE == true){QlGapczbeE = false;}
      if(fpSRskcImK == true){fpSRskcImK = false;}
      if(TPyKrdVfeC == true){TPyKrdVfeC = false;}
      if(fnDCGiRGAo == true){fnDCGiRGAo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQSMOSZYKK
{ 
  void rHzwOczXRT()
  { 
      bool rCytPsAtjj = false;
      bool OweEtLsxAU = false;
      bool xcJcfILrap = false;
      bool WdwRySCpeI = false;
      bool cECYgbTGGW = false;
      bool MywDEPsUNG = false;
      bool gHSsNjANGa = false;
      bool JCRrrsakwE = false;
      bool oFlEdXgrNi = false;
      bool ZgbXbUkIKx = false;
      bool bFAfNKfELK = false;
      bool oHYJQbVOPp = false;
      bool CHAWAcZtPW = false;
      bool HRazciEGpT = false;
      bool qcfCsRHSGz = false;
      bool zWsUtTFcej = false;
      bool jlnoDWgZgg = false;
      bool WOXwyZbxch = false;
      bool UHmQWjYFEI = false;
      bool dabGiEopyW = false;
      string ZigYtFYHPT;
      string KBmUqqCNsw;
      string QMWgMAmoXa;
      string oGFxICztkw;
      string gnyqMLAakz;
      string spHkBMMzLs;
      string RjineEupLo;
      string rHbxPcNeUB;
      string AMEYhyyUwu;
      string oAirdwEKMI;
      string PKOwHlOKUX;
      string ygeKsFfKGf;
      string FasPzqYjSS;
      string YDSLkoxIQu;
      string jmzXxHVXyX;
      string QtEfCoQywP;
      string MdqCzuOSYE;
      string IXsKwRaUSq;
      string VAktBdylIu;
      string XzLAiFuxYB;
      if(ZigYtFYHPT == PKOwHlOKUX){rCytPsAtjj = true;}
      else if(PKOwHlOKUX == ZigYtFYHPT){bFAfNKfELK = true;}
      if(KBmUqqCNsw == ygeKsFfKGf){OweEtLsxAU = true;}
      else if(ygeKsFfKGf == KBmUqqCNsw){oHYJQbVOPp = true;}
      if(QMWgMAmoXa == FasPzqYjSS){xcJcfILrap = true;}
      else if(FasPzqYjSS == QMWgMAmoXa){CHAWAcZtPW = true;}
      if(oGFxICztkw == YDSLkoxIQu){WdwRySCpeI = true;}
      else if(YDSLkoxIQu == oGFxICztkw){HRazciEGpT = true;}
      if(gnyqMLAakz == jmzXxHVXyX){cECYgbTGGW = true;}
      else if(jmzXxHVXyX == gnyqMLAakz){qcfCsRHSGz = true;}
      if(spHkBMMzLs == QtEfCoQywP){MywDEPsUNG = true;}
      else if(QtEfCoQywP == spHkBMMzLs){zWsUtTFcej = true;}
      if(RjineEupLo == MdqCzuOSYE){gHSsNjANGa = true;}
      else if(MdqCzuOSYE == RjineEupLo){jlnoDWgZgg = true;}
      if(rHbxPcNeUB == IXsKwRaUSq){JCRrrsakwE = true;}
      if(AMEYhyyUwu == VAktBdylIu){oFlEdXgrNi = true;}
      if(oAirdwEKMI == XzLAiFuxYB){ZgbXbUkIKx = true;}
      while(IXsKwRaUSq == rHbxPcNeUB){WOXwyZbxch = true;}
      while(VAktBdylIu == VAktBdylIu){UHmQWjYFEI = true;}
      while(XzLAiFuxYB == XzLAiFuxYB){dabGiEopyW = true;}
      if(rCytPsAtjj == true){rCytPsAtjj = false;}
      if(OweEtLsxAU == true){OweEtLsxAU = false;}
      if(xcJcfILrap == true){xcJcfILrap = false;}
      if(WdwRySCpeI == true){WdwRySCpeI = false;}
      if(cECYgbTGGW == true){cECYgbTGGW = false;}
      if(MywDEPsUNG == true){MywDEPsUNG = false;}
      if(gHSsNjANGa == true){gHSsNjANGa = false;}
      if(JCRrrsakwE == true){JCRrrsakwE = false;}
      if(oFlEdXgrNi == true){oFlEdXgrNi = false;}
      if(ZgbXbUkIKx == true){ZgbXbUkIKx = false;}
      if(bFAfNKfELK == true){bFAfNKfELK = false;}
      if(oHYJQbVOPp == true){oHYJQbVOPp = false;}
      if(CHAWAcZtPW == true){CHAWAcZtPW = false;}
      if(HRazciEGpT == true){HRazciEGpT = false;}
      if(qcfCsRHSGz == true){qcfCsRHSGz = false;}
      if(zWsUtTFcej == true){zWsUtTFcej = false;}
      if(jlnoDWgZgg == true){jlnoDWgZgg = false;}
      if(WOXwyZbxch == true){WOXwyZbxch = false;}
      if(UHmQWjYFEI == true){UHmQWjYFEI = false;}
      if(dabGiEopyW == true){dabGiEopyW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THSKAZCKSE
{ 
  void xnqEYthGqb()
  { 
      bool wrBeJmNWaw = false;
      bool qqUMnpZxuR = false;
      bool YhfTdjPAaH = false;
      bool cqNoDEgmIp = false;
      bool ozKXHdZskX = false;
      bool xNUpjOLhAZ = false;
      bool XMwTTzdeJj = false;
      bool ImnFcZWHMA = false;
      bool KVPCJPWWFo = false;
      bool rzliSbDqEH = false;
      bool AtjAOKYPNK = false;
      bool qEUAPBwsKE = false;
      bool cGZUrJAFmA = false;
      bool VfDFzPlPny = false;
      bool pHJtxndkTQ = false;
      bool eJfzdtTOIE = false;
      bool JTbMnKAPAz = false;
      bool PgELNUwfWD = false;
      bool eOkVULADaF = false;
      bool wWGjoWexFm = false;
      string rIlQSkKYaH;
      string bGGRgExsKa;
      string MwAXzsBWCj;
      string FNERelOFkS;
      string mubFPBzLYQ;
      string UyOAcwHOQZ;
      string imWpCOCnmu;
      string prIqmQTuHy;
      string soxkPGyDoh;
      string dAnLizYlCB;
      string yLYdacpXNL;
      string cMHSgtpkaw;
      string PyyEQoDxHm;
      string qgrGzgPTKl;
      string QapcFQsUdo;
      string JnKGkAMUMk;
      string YrPZUuUASz;
      string eVZnenIVzz;
      string wiSSdCVlUz;
      string UuGYNXLQIJ;
      if(rIlQSkKYaH == yLYdacpXNL){wrBeJmNWaw = true;}
      else if(yLYdacpXNL == rIlQSkKYaH){AtjAOKYPNK = true;}
      if(bGGRgExsKa == cMHSgtpkaw){qqUMnpZxuR = true;}
      else if(cMHSgtpkaw == bGGRgExsKa){qEUAPBwsKE = true;}
      if(MwAXzsBWCj == PyyEQoDxHm){YhfTdjPAaH = true;}
      else if(PyyEQoDxHm == MwAXzsBWCj){cGZUrJAFmA = true;}
      if(FNERelOFkS == qgrGzgPTKl){cqNoDEgmIp = true;}
      else if(qgrGzgPTKl == FNERelOFkS){VfDFzPlPny = true;}
      if(mubFPBzLYQ == QapcFQsUdo){ozKXHdZskX = true;}
      else if(QapcFQsUdo == mubFPBzLYQ){pHJtxndkTQ = true;}
      if(UyOAcwHOQZ == JnKGkAMUMk){xNUpjOLhAZ = true;}
      else if(JnKGkAMUMk == UyOAcwHOQZ){eJfzdtTOIE = true;}
      if(imWpCOCnmu == YrPZUuUASz){XMwTTzdeJj = true;}
      else if(YrPZUuUASz == imWpCOCnmu){JTbMnKAPAz = true;}
      if(prIqmQTuHy == eVZnenIVzz){ImnFcZWHMA = true;}
      if(soxkPGyDoh == wiSSdCVlUz){KVPCJPWWFo = true;}
      if(dAnLizYlCB == UuGYNXLQIJ){rzliSbDqEH = true;}
      while(eVZnenIVzz == prIqmQTuHy){PgELNUwfWD = true;}
      while(wiSSdCVlUz == wiSSdCVlUz){eOkVULADaF = true;}
      while(UuGYNXLQIJ == UuGYNXLQIJ){wWGjoWexFm = true;}
      if(wrBeJmNWaw == true){wrBeJmNWaw = false;}
      if(qqUMnpZxuR == true){qqUMnpZxuR = false;}
      if(YhfTdjPAaH == true){YhfTdjPAaH = false;}
      if(cqNoDEgmIp == true){cqNoDEgmIp = false;}
      if(ozKXHdZskX == true){ozKXHdZskX = false;}
      if(xNUpjOLhAZ == true){xNUpjOLhAZ = false;}
      if(XMwTTzdeJj == true){XMwTTzdeJj = false;}
      if(ImnFcZWHMA == true){ImnFcZWHMA = false;}
      if(KVPCJPWWFo == true){KVPCJPWWFo = false;}
      if(rzliSbDqEH == true){rzliSbDqEH = false;}
      if(AtjAOKYPNK == true){AtjAOKYPNK = false;}
      if(qEUAPBwsKE == true){qEUAPBwsKE = false;}
      if(cGZUrJAFmA == true){cGZUrJAFmA = false;}
      if(VfDFzPlPny == true){VfDFzPlPny = false;}
      if(pHJtxndkTQ == true){pHJtxndkTQ = false;}
      if(eJfzdtTOIE == true){eJfzdtTOIE = false;}
      if(JTbMnKAPAz == true){JTbMnKAPAz = false;}
      if(PgELNUwfWD == true){PgELNUwfWD = false;}
      if(eOkVULADaF == true){eOkVULADaF = false;}
      if(wWGjoWexFm == true){wWGjoWexFm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LLFZATMMMV
{ 
  void gSCALgMncL()
  { 
      bool uqXGgTJSiB = false;
      bool WfItrpaXtE = false;
      bool WJCTCcHVZC = false;
      bool WfrghUIbtY = false;
      bool XcASGmLeah = false;
      bool xNBNnlnDDD = false;
      bool MmsgdqmaMW = false;
      bool gydUgsIjNP = false;
      bool RbtqFJeesu = false;
      bool gFXpLjjTnP = false;
      bool zjREByifft = false;
      bool cDpnljsBaU = false;
      bool LIhQpbamJw = false;
      bool IowyPgKppH = false;
      bool ZyyyScOjEb = false;
      bool pirSDpCANY = false;
      bool XwWiknGrXF = false;
      bool ZDKTtNJiyN = false;
      bool MpihGZwctZ = false;
      bool eJbRidbOMd = false;
      string NjAZnRBbHo;
      string cyGHchyKLe;
      string JEjSQxEfPq;
      string huYYWduCuJ;
      string DUcYkgkJpP;
      string UhFJFJzgIp;
      string MVLQHhZgky;
      string mwOBbnaLgj;
      string MtpzVAoPTM;
      string dNtFwgJMQD;
      string HDYrcYSEgQ;
      string hnAYdSfLuH;
      string sJNXTYBJEt;
      string eOtdbIUyWw;
      string gkhDepNUad;
      string ByRJJypBXD;
      string WJzmkTtWxU;
      string xgnyZIaKrc;
      string LghasgwjTc;
      string STZSYXkuRL;
      if(NjAZnRBbHo == HDYrcYSEgQ){uqXGgTJSiB = true;}
      else if(HDYrcYSEgQ == NjAZnRBbHo){zjREByifft = true;}
      if(cyGHchyKLe == hnAYdSfLuH){WfItrpaXtE = true;}
      else if(hnAYdSfLuH == cyGHchyKLe){cDpnljsBaU = true;}
      if(JEjSQxEfPq == sJNXTYBJEt){WJCTCcHVZC = true;}
      else if(sJNXTYBJEt == JEjSQxEfPq){LIhQpbamJw = true;}
      if(huYYWduCuJ == eOtdbIUyWw){WfrghUIbtY = true;}
      else if(eOtdbIUyWw == huYYWduCuJ){IowyPgKppH = true;}
      if(DUcYkgkJpP == gkhDepNUad){XcASGmLeah = true;}
      else if(gkhDepNUad == DUcYkgkJpP){ZyyyScOjEb = true;}
      if(UhFJFJzgIp == ByRJJypBXD){xNBNnlnDDD = true;}
      else if(ByRJJypBXD == UhFJFJzgIp){pirSDpCANY = true;}
      if(MVLQHhZgky == WJzmkTtWxU){MmsgdqmaMW = true;}
      else if(WJzmkTtWxU == MVLQHhZgky){XwWiknGrXF = true;}
      if(mwOBbnaLgj == xgnyZIaKrc){gydUgsIjNP = true;}
      if(MtpzVAoPTM == LghasgwjTc){RbtqFJeesu = true;}
      if(dNtFwgJMQD == STZSYXkuRL){gFXpLjjTnP = true;}
      while(xgnyZIaKrc == mwOBbnaLgj){ZDKTtNJiyN = true;}
      while(LghasgwjTc == LghasgwjTc){MpihGZwctZ = true;}
      while(STZSYXkuRL == STZSYXkuRL){eJbRidbOMd = true;}
      if(uqXGgTJSiB == true){uqXGgTJSiB = false;}
      if(WfItrpaXtE == true){WfItrpaXtE = false;}
      if(WJCTCcHVZC == true){WJCTCcHVZC = false;}
      if(WfrghUIbtY == true){WfrghUIbtY = false;}
      if(XcASGmLeah == true){XcASGmLeah = false;}
      if(xNBNnlnDDD == true){xNBNnlnDDD = false;}
      if(MmsgdqmaMW == true){MmsgdqmaMW = false;}
      if(gydUgsIjNP == true){gydUgsIjNP = false;}
      if(RbtqFJeesu == true){RbtqFJeesu = false;}
      if(gFXpLjjTnP == true){gFXpLjjTnP = false;}
      if(zjREByifft == true){zjREByifft = false;}
      if(cDpnljsBaU == true){cDpnljsBaU = false;}
      if(LIhQpbamJw == true){LIhQpbamJw = false;}
      if(IowyPgKppH == true){IowyPgKppH = false;}
      if(ZyyyScOjEb == true){ZyyyScOjEb = false;}
      if(pirSDpCANY == true){pirSDpCANY = false;}
      if(XwWiknGrXF == true){XwWiknGrXF = false;}
      if(ZDKTtNJiyN == true){ZDKTtNJiyN = false;}
      if(MpihGZwctZ == true){MpihGZwctZ = false;}
      if(eJbRidbOMd == true){eJbRidbOMd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBJLHNOQGM
{ 
  void RlqRCVBpCW()
  { 
      bool rVihUKAyiz = false;
      bool MeenWjnWnZ = false;
      bool TNgdcaTGWN = false;
      bool QaMXkeRPdV = false;
      bool EVOxsIoKal = false;
      bool ugmzZdoEFs = false;
      bool qtbUhlRGDq = false;
      bool RXrSUyzikU = false;
      bool kIekRimNxG = false;
      bool pMKjeJtsOG = false;
      bool piHjTXnUdb = false;
      bool eFTkHhPqDz = false;
      bool zDIwBENHmL = false;
      bool EGTddCAuQt = false;
      bool uRiVbjsZcw = false;
      bool tDoPGlZLiO = false;
      bool JggSXYloGE = false;
      bool gTZIDhUmTR = false;
      bool LneqQBQDXq = false;
      bool coMCjOjQyD = false;
      string LJaUgphpZO;
      string FOFYdSJIOn;
      string pItBdCGiTL;
      string txkVmGUPwQ;
      string NBFSVrpmUW;
      string zrkGcDPZqe;
      string iyVNTHcilW;
      string xsLxZnDbek;
      string LTOwMBMdri;
      string quYQgOeqyO;
      string OHAxZFgmgn;
      string AntFTPjZAR;
      string tzpCfBTuQL;
      string JLcQVDSQVH;
      string UZxEiCASxR;
      string dEqfTPQyRX;
      string kkVUenKdjP;
      string wTDsxUClSc;
      string BBxzgETxxG;
      string mUzxViDbYt;
      if(LJaUgphpZO == OHAxZFgmgn){rVihUKAyiz = true;}
      else if(OHAxZFgmgn == LJaUgphpZO){piHjTXnUdb = true;}
      if(FOFYdSJIOn == AntFTPjZAR){MeenWjnWnZ = true;}
      else if(AntFTPjZAR == FOFYdSJIOn){eFTkHhPqDz = true;}
      if(pItBdCGiTL == tzpCfBTuQL){TNgdcaTGWN = true;}
      else if(tzpCfBTuQL == pItBdCGiTL){zDIwBENHmL = true;}
      if(txkVmGUPwQ == JLcQVDSQVH){QaMXkeRPdV = true;}
      else if(JLcQVDSQVH == txkVmGUPwQ){EGTddCAuQt = true;}
      if(NBFSVrpmUW == UZxEiCASxR){EVOxsIoKal = true;}
      else if(UZxEiCASxR == NBFSVrpmUW){uRiVbjsZcw = true;}
      if(zrkGcDPZqe == dEqfTPQyRX){ugmzZdoEFs = true;}
      else if(dEqfTPQyRX == zrkGcDPZqe){tDoPGlZLiO = true;}
      if(iyVNTHcilW == kkVUenKdjP){qtbUhlRGDq = true;}
      else if(kkVUenKdjP == iyVNTHcilW){JggSXYloGE = true;}
      if(xsLxZnDbek == wTDsxUClSc){RXrSUyzikU = true;}
      if(LTOwMBMdri == BBxzgETxxG){kIekRimNxG = true;}
      if(quYQgOeqyO == mUzxViDbYt){pMKjeJtsOG = true;}
      while(wTDsxUClSc == xsLxZnDbek){gTZIDhUmTR = true;}
      while(BBxzgETxxG == BBxzgETxxG){LneqQBQDXq = true;}
      while(mUzxViDbYt == mUzxViDbYt){coMCjOjQyD = true;}
      if(rVihUKAyiz == true){rVihUKAyiz = false;}
      if(MeenWjnWnZ == true){MeenWjnWnZ = false;}
      if(TNgdcaTGWN == true){TNgdcaTGWN = false;}
      if(QaMXkeRPdV == true){QaMXkeRPdV = false;}
      if(EVOxsIoKal == true){EVOxsIoKal = false;}
      if(ugmzZdoEFs == true){ugmzZdoEFs = false;}
      if(qtbUhlRGDq == true){qtbUhlRGDq = false;}
      if(RXrSUyzikU == true){RXrSUyzikU = false;}
      if(kIekRimNxG == true){kIekRimNxG = false;}
      if(pMKjeJtsOG == true){pMKjeJtsOG = false;}
      if(piHjTXnUdb == true){piHjTXnUdb = false;}
      if(eFTkHhPqDz == true){eFTkHhPqDz = false;}
      if(zDIwBENHmL == true){zDIwBENHmL = false;}
      if(EGTddCAuQt == true){EGTddCAuQt = false;}
      if(uRiVbjsZcw == true){uRiVbjsZcw = false;}
      if(tDoPGlZLiO == true){tDoPGlZLiO = false;}
      if(JggSXYloGE == true){JggSXYloGE = false;}
      if(gTZIDhUmTR == true){gTZIDhUmTR = false;}
      if(LneqQBQDXq == true){LneqQBQDXq = false;}
      if(coMCjOjQyD == true){coMCjOjQyD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZJFPAGQCN
{ 
  void yrRAeUqKVA()
  { 
      bool CPhYitdZYm = false;
      bool qQQkRRFZNJ = false;
      bool LBsCUXzzcY = false;
      bool bhVMtVxEHO = false;
      bool oCLwRHiWKm = false;
      bool NbPoUBVfDK = false;
      bool uexzLJtDpu = false;
      bool UBSyTJoxjM = false;
      bool nbnoKARgrs = false;
      bool AQAwTKFLkI = false;
      bool NffPSMJRVL = false;
      bool LYwpWSqHnL = false;
      bool qNKxuDAVdJ = false;
      bool EcMazHwYWy = false;
      bool pALggaUJZB = false;
      bool TxWZRAVhTO = false;
      bool LmmLHiMUqO = false;
      bool VRjpUpBdPT = false;
      bool ipwbpGFlJy = false;
      bool lNEIlDNzZy = false;
      string XSRlxaAbwN;
      string VOCwDcNksK;
      string dZLSkBKtDn;
      string hmVZplXURF;
      string DnyszIKcjn;
      string PzDntyHzBu;
      string PGYHeisbFQ;
      string EsSnHpaRSb;
      string qhJPYijgfr;
      string eYTWoxPqNQ;
      string PhXTiWfPgD;
      string XpfYDhwIiw;
      string yLwNleZwyJ;
      string ajDCMJJofB;
      string DTAbTostSH;
      string AGHRRDkJhD;
      string xiRWcnldLs;
      string XGbgseLUsw;
      string ledqJTbkjJ;
      string YAHcETCcyf;
      if(XSRlxaAbwN == PhXTiWfPgD){CPhYitdZYm = true;}
      else if(PhXTiWfPgD == XSRlxaAbwN){NffPSMJRVL = true;}
      if(VOCwDcNksK == XpfYDhwIiw){qQQkRRFZNJ = true;}
      else if(XpfYDhwIiw == VOCwDcNksK){LYwpWSqHnL = true;}
      if(dZLSkBKtDn == yLwNleZwyJ){LBsCUXzzcY = true;}
      else if(yLwNleZwyJ == dZLSkBKtDn){qNKxuDAVdJ = true;}
      if(hmVZplXURF == ajDCMJJofB){bhVMtVxEHO = true;}
      else if(ajDCMJJofB == hmVZplXURF){EcMazHwYWy = true;}
      if(DnyszIKcjn == DTAbTostSH){oCLwRHiWKm = true;}
      else if(DTAbTostSH == DnyszIKcjn){pALggaUJZB = true;}
      if(PzDntyHzBu == AGHRRDkJhD){NbPoUBVfDK = true;}
      else if(AGHRRDkJhD == PzDntyHzBu){TxWZRAVhTO = true;}
      if(PGYHeisbFQ == xiRWcnldLs){uexzLJtDpu = true;}
      else if(xiRWcnldLs == PGYHeisbFQ){LmmLHiMUqO = true;}
      if(EsSnHpaRSb == XGbgseLUsw){UBSyTJoxjM = true;}
      if(qhJPYijgfr == ledqJTbkjJ){nbnoKARgrs = true;}
      if(eYTWoxPqNQ == YAHcETCcyf){AQAwTKFLkI = true;}
      while(XGbgseLUsw == EsSnHpaRSb){VRjpUpBdPT = true;}
      while(ledqJTbkjJ == ledqJTbkjJ){ipwbpGFlJy = true;}
      while(YAHcETCcyf == YAHcETCcyf){lNEIlDNzZy = true;}
      if(CPhYitdZYm == true){CPhYitdZYm = false;}
      if(qQQkRRFZNJ == true){qQQkRRFZNJ = false;}
      if(LBsCUXzzcY == true){LBsCUXzzcY = false;}
      if(bhVMtVxEHO == true){bhVMtVxEHO = false;}
      if(oCLwRHiWKm == true){oCLwRHiWKm = false;}
      if(NbPoUBVfDK == true){NbPoUBVfDK = false;}
      if(uexzLJtDpu == true){uexzLJtDpu = false;}
      if(UBSyTJoxjM == true){UBSyTJoxjM = false;}
      if(nbnoKARgrs == true){nbnoKARgrs = false;}
      if(AQAwTKFLkI == true){AQAwTKFLkI = false;}
      if(NffPSMJRVL == true){NffPSMJRVL = false;}
      if(LYwpWSqHnL == true){LYwpWSqHnL = false;}
      if(qNKxuDAVdJ == true){qNKxuDAVdJ = false;}
      if(EcMazHwYWy == true){EcMazHwYWy = false;}
      if(pALggaUJZB == true){pALggaUJZB = false;}
      if(TxWZRAVhTO == true){TxWZRAVhTO = false;}
      if(LmmLHiMUqO == true){LmmLHiMUqO = false;}
      if(VRjpUpBdPT == true){VRjpUpBdPT = false;}
      if(ipwbpGFlJy == true){ipwbpGFlJy = false;}
      if(lNEIlDNzZy == true){lNEIlDNzZy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCCVUZQROJ
{ 
  void hCxZBeKzxQ()
  { 
      bool juKffqoUOY = false;
      bool OMUkGTytZS = false;
      bool xxZeKSuSzL = false;
      bool oYXdedluTK = false;
      bool zAFJrLjfqW = false;
      bool mrjMKlVeVM = false;
      bool wWUCjpopGc = false;
      bool gCZPSwqPly = false;
      bool iOacXwnLSr = false;
      bool HGZHNceDYC = false;
      bool WsZOojRUsO = false;
      bool tFsXcgurdm = false;
      bool BcXNUacSBo = false;
      bool RnqiaooMmn = false;
      bool eTRExCNBdg = false;
      bool hlYlBsVMsO = false;
      bool HzTEwGOJxm = false;
      bool riEpIhLSPS = false;
      bool MbnUHePEhg = false;
      bool TbSYfeAMIq = false;
      string HRcyqxmzVU;
      string EqQEQFiirt;
      string fQRqiajURH;
      string dRymRAhCDB;
      string CjYNwLhFif;
      string pynbzqAlOQ;
      string NRhOqlrclQ;
      string XfeqrwqDtX;
      string sdklQfdWnZ;
      string zummmkBJWK;
      string SESSHJSxjC;
      string zxrqXifuyK;
      string IVoMRbsrDH;
      string ugfjEnLSdH;
      string MfmlZBDwPD;
      string EGLLBxPGBf;
      string QascHSRHli;
      string XMQpxbiClP;
      string YwbzCoVThH;
      string YERyplmJeH;
      if(HRcyqxmzVU == SESSHJSxjC){juKffqoUOY = true;}
      else if(SESSHJSxjC == HRcyqxmzVU){WsZOojRUsO = true;}
      if(EqQEQFiirt == zxrqXifuyK){OMUkGTytZS = true;}
      else if(zxrqXifuyK == EqQEQFiirt){tFsXcgurdm = true;}
      if(fQRqiajURH == IVoMRbsrDH){xxZeKSuSzL = true;}
      else if(IVoMRbsrDH == fQRqiajURH){BcXNUacSBo = true;}
      if(dRymRAhCDB == ugfjEnLSdH){oYXdedluTK = true;}
      else if(ugfjEnLSdH == dRymRAhCDB){RnqiaooMmn = true;}
      if(CjYNwLhFif == MfmlZBDwPD){zAFJrLjfqW = true;}
      else if(MfmlZBDwPD == CjYNwLhFif){eTRExCNBdg = true;}
      if(pynbzqAlOQ == EGLLBxPGBf){mrjMKlVeVM = true;}
      else if(EGLLBxPGBf == pynbzqAlOQ){hlYlBsVMsO = true;}
      if(NRhOqlrclQ == QascHSRHli){wWUCjpopGc = true;}
      else if(QascHSRHli == NRhOqlrclQ){HzTEwGOJxm = true;}
      if(XfeqrwqDtX == XMQpxbiClP){gCZPSwqPly = true;}
      if(sdklQfdWnZ == YwbzCoVThH){iOacXwnLSr = true;}
      if(zummmkBJWK == YERyplmJeH){HGZHNceDYC = true;}
      while(XMQpxbiClP == XfeqrwqDtX){riEpIhLSPS = true;}
      while(YwbzCoVThH == YwbzCoVThH){MbnUHePEhg = true;}
      while(YERyplmJeH == YERyplmJeH){TbSYfeAMIq = true;}
      if(juKffqoUOY == true){juKffqoUOY = false;}
      if(OMUkGTytZS == true){OMUkGTytZS = false;}
      if(xxZeKSuSzL == true){xxZeKSuSzL = false;}
      if(oYXdedluTK == true){oYXdedluTK = false;}
      if(zAFJrLjfqW == true){zAFJrLjfqW = false;}
      if(mrjMKlVeVM == true){mrjMKlVeVM = false;}
      if(wWUCjpopGc == true){wWUCjpopGc = false;}
      if(gCZPSwqPly == true){gCZPSwqPly = false;}
      if(iOacXwnLSr == true){iOacXwnLSr = false;}
      if(HGZHNceDYC == true){HGZHNceDYC = false;}
      if(WsZOojRUsO == true){WsZOojRUsO = false;}
      if(tFsXcgurdm == true){tFsXcgurdm = false;}
      if(BcXNUacSBo == true){BcXNUacSBo = false;}
      if(RnqiaooMmn == true){RnqiaooMmn = false;}
      if(eTRExCNBdg == true){eTRExCNBdg = false;}
      if(hlYlBsVMsO == true){hlYlBsVMsO = false;}
      if(HzTEwGOJxm == true){HzTEwGOJxm = false;}
      if(riEpIhLSPS == true){riEpIhLSPS = false;}
      if(MbnUHePEhg == true){MbnUHePEhg = false;}
      if(TbSYfeAMIq == true){TbSYfeAMIq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URJFOGNDIH
{ 
  void qPGZMriUeK()
  { 
      bool ezljXqkUCJ = false;
      bool YYPuHhKXLN = false;
      bool khjjPtnOKJ = false;
      bool YGGEHPqpiG = false;
      bool SpbFSgJfgB = false;
      bool WYTMEwPCTc = false;
      bool CVKsjRSLmq = false;
      bool pTnEutFeQh = false;
      bool kHhJmAmszK = false;
      bool AoWGDxfiUB = false;
      bool OyrpKCjORJ = false;
      bool qjkkqtnBGj = false;
      bool eYLcpBxhBy = false;
      bool OWJPTmOqyj = false;
      bool PXaoTQEkOI = false;
      bool IecjVolPAJ = false;
      bool FCNTuUaURE = false;
      bool fwCVTGyVJZ = false;
      bool wMSrojsYsd = false;
      bool AzqoeNJHty = false;
      string ZeTYaslCSL;
      string khnHzMrlZQ;
      string RVSDFzMpog;
      string UgELOpHKPd;
      string cSprgQHjUq;
      string jlZBIDMPSa;
      string guNlpEdbrI;
      string FhVwmyeZWo;
      string rbVxwhGCCL;
      string dqqoxgFEBc;
      string lerLkBQdOK;
      string XlsdiEZPoH;
      string xaYgdOpfzF;
      string saYtCMjJLu;
      string RbnrmryMGr;
      string HoPseLFKhW;
      string LjeIRxMzaW;
      string UQEtpVlgtl;
      string PcZGxDLeOq;
      string GZboigweap;
      if(ZeTYaslCSL == lerLkBQdOK){ezljXqkUCJ = true;}
      else if(lerLkBQdOK == ZeTYaslCSL){OyrpKCjORJ = true;}
      if(khnHzMrlZQ == XlsdiEZPoH){YYPuHhKXLN = true;}
      else if(XlsdiEZPoH == khnHzMrlZQ){qjkkqtnBGj = true;}
      if(RVSDFzMpog == xaYgdOpfzF){khjjPtnOKJ = true;}
      else if(xaYgdOpfzF == RVSDFzMpog){eYLcpBxhBy = true;}
      if(UgELOpHKPd == saYtCMjJLu){YGGEHPqpiG = true;}
      else if(saYtCMjJLu == UgELOpHKPd){OWJPTmOqyj = true;}
      if(cSprgQHjUq == RbnrmryMGr){SpbFSgJfgB = true;}
      else if(RbnrmryMGr == cSprgQHjUq){PXaoTQEkOI = true;}
      if(jlZBIDMPSa == HoPseLFKhW){WYTMEwPCTc = true;}
      else if(HoPseLFKhW == jlZBIDMPSa){IecjVolPAJ = true;}
      if(guNlpEdbrI == LjeIRxMzaW){CVKsjRSLmq = true;}
      else if(LjeIRxMzaW == guNlpEdbrI){FCNTuUaURE = true;}
      if(FhVwmyeZWo == UQEtpVlgtl){pTnEutFeQh = true;}
      if(rbVxwhGCCL == PcZGxDLeOq){kHhJmAmszK = true;}
      if(dqqoxgFEBc == GZboigweap){AoWGDxfiUB = true;}
      while(UQEtpVlgtl == FhVwmyeZWo){fwCVTGyVJZ = true;}
      while(PcZGxDLeOq == PcZGxDLeOq){wMSrojsYsd = true;}
      while(GZboigweap == GZboigweap){AzqoeNJHty = true;}
      if(ezljXqkUCJ == true){ezljXqkUCJ = false;}
      if(YYPuHhKXLN == true){YYPuHhKXLN = false;}
      if(khjjPtnOKJ == true){khjjPtnOKJ = false;}
      if(YGGEHPqpiG == true){YGGEHPqpiG = false;}
      if(SpbFSgJfgB == true){SpbFSgJfgB = false;}
      if(WYTMEwPCTc == true){WYTMEwPCTc = false;}
      if(CVKsjRSLmq == true){CVKsjRSLmq = false;}
      if(pTnEutFeQh == true){pTnEutFeQh = false;}
      if(kHhJmAmszK == true){kHhJmAmszK = false;}
      if(AoWGDxfiUB == true){AoWGDxfiUB = false;}
      if(OyrpKCjORJ == true){OyrpKCjORJ = false;}
      if(qjkkqtnBGj == true){qjkkqtnBGj = false;}
      if(eYLcpBxhBy == true){eYLcpBxhBy = false;}
      if(OWJPTmOqyj == true){OWJPTmOqyj = false;}
      if(PXaoTQEkOI == true){PXaoTQEkOI = false;}
      if(IecjVolPAJ == true){IecjVolPAJ = false;}
      if(FCNTuUaURE == true){FCNTuUaURE = false;}
      if(fwCVTGyVJZ == true){fwCVTGyVJZ = false;}
      if(wMSrojsYsd == true){wMSrojsYsd = false;}
      if(AzqoeNJHty == true){AzqoeNJHty = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQSPRTTRWD
{ 
  void wrfESppQlD()
  { 
      bool zonUDYycUz = false;
      bool UINhEDMQeL = false;
      bool BTpKHrmDnn = false;
      bool kAqfCNswJg = false;
      bool dHRLSDbjCs = false;
      bool rJAcfezdML = false;
      bool kuogOTRhep = false;
      bool KPGxhtBeqE = false;
      bool QDBtwazNzW = false;
      bool OOjywiRkxz = false;
      bool ktELibDDtk = false;
      bool dUmItgsukn = false;
      bool TEhIaufIAz = false;
      bool cQgrSWzpLT = false;
      bool XwTOstbaDP = false;
      bool pWAJegLukm = false;
      bool utCuINmtoX = false;
      bool gCjQPXkTPf = false;
      bool TFEkJFQXNl = false;
      bool KDFXXctXFf = false;
      string IjmGjJCVDR;
      string tOQXnsxwAA;
      string tihScOfEeq;
      string UxbBfRiCfP;
      string gZxnWmNCNN;
      string AAOowYCTcV;
      string cxqMwxlOqW;
      string KtQkTUkswp;
      string AcqRpThmFH;
      string OOZKljhkqZ;
      string AyLpDGjdVa;
      string mIXmVzFYVc;
      string PzJiHuUFzj;
      string lABVoBRAOj;
      string iERdUGqlnl;
      string dJPOKBobiH;
      string lddkolGBxT;
      string hFKlsKgfOB;
      string DhRNGckmLm;
      string MoRGxFZfoh;
      if(IjmGjJCVDR == AyLpDGjdVa){zonUDYycUz = true;}
      else if(AyLpDGjdVa == IjmGjJCVDR){ktELibDDtk = true;}
      if(tOQXnsxwAA == mIXmVzFYVc){UINhEDMQeL = true;}
      else if(mIXmVzFYVc == tOQXnsxwAA){dUmItgsukn = true;}
      if(tihScOfEeq == PzJiHuUFzj){BTpKHrmDnn = true;}
      else if(PzJiHuUFzj == tihScOfEeq){TEhIaufIAz = true;}
      if(UxbBfRiCfP == lABVoBRAOj){kAqfCNswJg = true;}
      else if(lABVoBRAOj == UxbBfRiCfP){cQgrSWzpLT = true;}
      if(gZxnWmNCNN == iERdUGqlnl){dHRLSDbjCs = true;}
      else if(iERdUGqlnl == gZxnWmNCNN){XwTOstbaDP = true;}
      if(AAOowYCTcV == dJPOKBobiH){rJAcfezdML = true;}
      else if(dJPOKBobiH == AAOowYCTcV){pWAJegLukm = true;}
      if(cxqMwxlOqW == lddkolGBxT){kuogOTRhep = true;}
      else if(lddkolGBxT == cxqMwxlOqW){utCuINmtoX = true;}
      if(KtQkTUkswp == hFKlsKgfOB){KPGxhtBeqE = true;}
      if(AcqRpThmFH == DhRNGckmLm){QDBtwazNzW = true;}
      if(OOZKljhkqZ == MoRGxFZfoh){OOjywiRkxz = true;}
      while(hFKlsKgfOB == KtQkTUkswp){gCjQPXkTPf = true;}
      while(DhRNGckmLm == DhRNGckmLm){TFEkJFQXNl = true;}
      while(MoRGxFZfoh == MoRGxFZfoh){KDFXXctXFf = true;}
      if(zonUDYycUz == true){zonUDYycUz = false;}
      if(UINhEDMQeL == true){UINhEDMQeL = false;}
      if(BTpKHrmDnn == true){BTpKHrmDnn = false;}
      if(kAqfCNswJg == true){kAqfCNswJg = false;}
      if(dHRLSDbjCs == true){dHRLSDbjCs = false;}
      if(rJAcfezdML == true){rJAcfezdML = false;}
      if(kuogOTRhep == true){kuogOTRhep = false;}
      if(KPGxhtBeqE == true){KPGxhtBeqE = false;}
      if(QDBtwazNzW == true){QDBtwazNzW = false;}
      if(OOjywiRkxz == true){OOjywiRkxz = false;}
      if(ktELibDDtk == true){ktELibDDtk = false;}
      if(dUmItgsukn == true){dUmItgsukn = false;}
      if(TEhIaufIAz == true){TEhIaufIAz = false;}
      if(cQgrSWzpLT == true){cQgrSWzpLT = false;}
      if(XwTOstbaDP == true){XwTOstbaDP = false;}
      if(pWAJegLukm == true){pWAJegLukm = false;}
      if(utCuINmtoX == true){utCuINmtoX = false;}
      if(gCjQPXkTPf == true){gCjQPXkTPf = false;}
      if(TFEkJFQXNl == true){TFEkJFQXNl = false;}
      if(KDFXXctXFf == true){KDFXXctXFf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYXHYZCJNP
{ 
  void TCPYhfSVPH()
  { 
      bool xzOgwjqbej = false;
      bool WJwsytfYEa = false;
      bool tLFJiDMxnS = false;
      bool jZEgiJriFJ = false;
      bool ilTkaaJxVw = false;
      bool EiGldksFxr = false;
      bool XsmLzwEOKo = false;
      bool BxSuqHrThI = false;
      bool tParNBSSCx = false;
      bool PmkMkoyHle = false;
      bool VtlgtHPLuV = false;
      bool sZWnyIRuxy = false;
      bool dlLNYOLFJB = false;
      bool IjhDmzctxG = false;
      bool kHWgDpPwOc = false;
      bool XDJmAihYIf = false;
      bool uJCsNIqTBy = false;
      bool fXyqMWOeJi = false;
      bool yPqgdFatCE = false;
      bool RDlQLaEdTt = false;
      string WkTWAkVGbk;
      string NpFtXNcaDn;
      string DmusxDcata;
      string GXGZwlbLcb;
      string BOixrmljxb;
      string zLIRZjoaYw;
      string HuLBepjexk;
      string kRxamnEyAK;
      string RscRbtPozM;
      string xBlfTFDhRC;
      string DGlMqhNgel;
      string epZOeOSsZj;
      string ZuekmjeRGg;
      string jWfyGKGPas;
      string ghJNgHaWBE;
      string mJHhbIaAZG;
      string CwayBIJbHT;
      string ICRfDrkREf;
      string IHPBsaOyVy;
      string jFpUqjHLMX;
      if(WkTWAkVGbk == DGlMqhNgel){xzOgwjqbej = true;}
      else if(DGlMqhNgel == WkTWAkVGbk){VtlgtHPLuV = true;}
      if(NpFtXNcaDn == epZOeOSsZj){WJwsytfYEa = true;}
      else if(epZOeOSsZj == NpFtXNcaDn){sZWnyIRuxy = true;}
      if(DmusxDcata == ZuekmjeRGg){tLFJiDMxnS = true;}
      else if(ZuekmjeRGg == DmusxDcata){dlLNYOLFJB = true;}
      if(GXGZwlbLcb == jWfyGKGPas){jZEgiJriFJ = true;}
      else if(jWfyGKGPas == GXGZwlbLcb){IjhDmzctxG = true;}
      if(BOixrmljxb == ghJNgHaWBE){ilTkaaJxVw = true;}
      else if(ghJNgHaWBE == BOixrmljxb){kHWgDpPwOc = true;}
      if(zLIRZjoaYw == mJHhbIaAZG){EiGldksFxr = true;}
      else if(mJHhbIaAZG == zLIRZjoaYw){XDJmAihYIf = true;}
      if(HuLBepjexk == CwayBIJbHT){XsmLzwEOKo = true;}
      else if(CwayBIJbHT == HuLBepjexk){uJCsNIqTBy = true;}
      if(kRxamnEyAK == ICRfDrkREf){BxSuqHrThI = true;}
      if(RscRbtPozM == IHPBsaOyVy){tParNBSSCx = true;}
      if(xBlfTFDhRC == jFpUqjHLMX){PmkMkoyHle = true;}
      while(ICRfDrkREf == kRxamnEyAK){fXyqMWOeJi = true;}
      while(IHPBsaOyVy == IHPBsaOyVy){yPqgdFatCE = true;}
      while(jFpUqjHLMX == jFpUqjHLMX){RDlQLaEdTt = true;}
      if(xzOgwjqbej == true){xzOgwjqbej = false;}
      if(WJwsytfYEa == true){WJwsytfYEa = false;}
      if(tLFJiDMxnS == true){tLFJiDMxnS = false;}
      if(jZEgiJriFJ == true){jZEgiJriFJ = false;}
      if(ilTkaaJxVw == true){ilTkaaJxVw = false;}
      if(EiGldksFxr == true){EiGldksFxr = false;}
      if(XsmLzwEOKo == true){XsmLzwEOKo = false;}
      if(BxSuqHrThI == true){BxSuqHrThI = false;}
      if(tParNBSSCx == true){tParNBSSCx = false;}
      if(PmkMkoyHle == true){PmkMkoyHle = false;}
      if(VtlgtHPLuV == true){VtlgtHPLuV = false;}
      if(sZWnyIRuxy == true){sZWnyIRuxy = false;}
      if(dlLNYOLFJB == true){dlLNYOLFJB = false;}
      if(IjhDmzctxG == true){IjhDmzctxG = false;}
      if(kHWgDpPwOc == true){kHWgDpPwOc = false;}
      if(XDJmAihYIf == true){XDJmAihYIf = false;}
      if(uJCsNIqTBy == true){uJCsNIqTBy = false;}
      if(fXyqMWOeJi == true){fXyqMWOeJi = false;}
      if(yPqgdFatCE == true){yPqgdFatCE = false;}
      if(RDlQLaEdTt == true){RDlQLaEdTt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIUNHPMIIY
{ 
  void ZwSCYniftP()
  { 
      bool YCQiCutPsr = false;
      bool HzkxnRmprk = false;
      bool CFgyAQRMyw = false;
      bool YVIMRmVxjM = false;
      bool LtjLVmfMFp = false;
      bool oEpJOSVRik = false;
      bool chQwSkqYfA = false;
      bool upFeZIUUcN = false;
      bool kFGIHUfyxy = false;
      bool RDOyjdcmrj = false;
      bool wHgEtzyKjG = false;
      bool yAoVAWaIoy = false;
      bool FragirbGuw = false;
      bool fgcrQdYCNI = false;
      bool VVOqAQOryM = false;
      bool CTyseDfzUC = false;
      bool XrOmaQXxEW = false;
      bool xXtgcicjfS = false;
      bool ciIisLiiMN = false;
      bool xZgLjdHaPj = false;
      string rUFpWnPLoi;
      string IOGZicLSth;
      string cbIjiJQGDZ;
      string utQbpyKSNW;
      string GnEZQuYJWY;
      string cbXFnQMUGN;
      string WJIPnNxeij;
      string SrEXanWhTn;
      string jHjdwTWLmY;
      string loLAAwfolC;
      string xtZlGjXAdA;
      string teBScPZdSU;
      string plqJycfDWd;
      string HguQppgxXL;
      string wWgmeHmsWj;
      string WBWRLLDPnd;
      string ETczrMikcm;
      string hbGGYTEDep;
      string olgmHGKdEd;
      string mQJtHbthuR;
      if(rUFpWnPLoi == xtZlGjXAdA){YCQiCutPsr = true;}
      else if(xtZlGjXAdA == rUFpWnPLoi){wHgEtzyKjG = true;}
      if(IOGZicLSth == teBScPZdSU){HzkxnRmprk = true;}
      else if(teBScPZdSU == IOGZicLSth){yAoVAWaIoy = true;}
      if(cbIjiJQGDZ == plqJycfDWd){CFgyAQRMyw = true;}
      else if(plqJycfDWd == cbIjiJQGDZ){FragirbGuw = true;}
      if(utQbpyKSNW == HguQppgxXL){YVIMRmVxjM = true;}
      else if(HguQppgxXL == utQbpyKSNW){fgcrQdYCNI = true;}
      if(GnEZQuYJWY == wWgmeHmsWj){LtjLVmfMFp = true;}
      else if(wWgmeHmsWj == GnEZQuYJWY){VVOqAQOryM = true;}
      if(cbXFnQMUGN == WBWRLLDPnd){oEpJOSVRik = true;}
      else if(WBWRLLDPnd == cbXFnQMUGN){CTyseDfzUC = true;}
      if(WJIPnNxeij == ETczrMikcm){chQwSkqYfA = true;}
      else if(ETczrMikcm == WJIPnNxeij){XrOmaQXxEW = true;}
      if(SrEXanWhTn == hbGGYTEDep){upFeZIUUcN = true;}
      if(jHjdwTWLmY == olgmHGKdEd){kFGIHUfyxy = true;}
      if(loLAAwfolC == mQJtHbthuR){RDOyjdcmrj = true;}
      while(hbGGYTEDep == SrEXanWhTn){xXtgcicjfS = true;}
      while(olgmHGKdEd == olgmHGKdEd){ciIisLiiMN = true;}
      while(mQJtHbthuR == mQJtHbthuR){xZgLjdHaPj = true;}
      if(YCQiCutPsr == true){YCQiCutPsr = false;}
      if(HzkxnRmprk == true){HzkxnRmprk = false;}
      if(CFgyAQRMyw == true){CFgyAQRMyw = false;}
      if(YVIMRmVxjM == true){YVIMRmVxjM = false;}
      if(LtjLVmfMFp == true){LtjLVmfMFp = false;}
      if(oEpJOSVRik == true){oEpJOSVRik = false;}
      if(chQwSkqYfA == true){chQwSkqYfA = false;}
      if(upFeZIUUcN == true){upFeZIUUcN = false;}
      if(kFGIHUfyxy == true){kFGIHUfyxy = false;}
      if(RDOyjdcmrj == true){RDOyjdcmrj = false;}
      if(wHgEtzyKjG == true){wHgEtzyKjG = false;}
      if(yAoVAWaIoy == true){yAoVAWaIoy = false;}
      if(FragirbGuw == true){FragirbGuw = false;}
      if(fgcrQdYCNI == true){fgcrQdYCNI = false;}
      if(VVOqAQOryM == true){VVOqAQOryM = false;}
      if(CTyseDfzUC == true){CTyseDfzUC = false;}
      if(XrOmaQXxEW == true){XrOmaQXxEW = false;}
      if(xXtgcicjfS == true){xXtgcicjfS = false;}
      if(ciIisLiiMN == true){ciIisLiiMN = false;}
      if(xZgLjdHaPj == true){xZgLjdHaPj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGXVZNYOZP
{ 
  void jKCRJZehVe()
  { 
      bool ozUWOHTtkl = false;
      bool eGUpcCTmsO = false;
      bool PSQgoiQIhA = false;
      bool AwgYnroNKt = false;
      bool XNGtkqFSGk = false;
      bool gdLStWimhf = false;
      bool pKLjlhYwBj = false;
      bool NFczqCLWwy = false;
      bool cxCxSWjOdR = false;
      bool JBfdDMCWHC = false;
      bool RJQVXbAMar = false;
      bool KLqiDrIORO = false;
      bool xKSjaLYyue = false;
      bool AoOtfSggYp = false;
      bool VXmkGxKwaK = false;
      bool DmErEHqfuL = false;
      bool CCRwrVxxCj = false;
      bool LboasZWgdc = false;
      bool BbWjaMjVoY = false;
      bool bAlNnSFpsk = false;
      string IltaKRGEVX;
      string CFZkPTcRUW;
      string iCaZzQZirN;
      string MPYWlzzoIG;
      string FVsEmQZWLd;
      string aIZtXGLUbt;
      string rXMHLlgCzQ;
      string TnINQNJWlh;
      string pCWOlEpdzf;
      string neMOOhJksA;
      string jXXuJmzLdK;
      string wnhtEoBxUG;
      string wCDSbnatyh;
      string DXdkxRebEz;
      string FdAnizwRJY;
      string gLPlEgUESU;
      string LEMuGXKxxl;
      string JZrVBRCOic;
      string rJkZBqIqgP;
      string xaIimAQFhK;
      if(IltaKRGEVX == jXXuJmzLdK){ozUWOHTtkl = true;}
      else if(jXXuJmzLdK == IltaKRGEVX){RJQVXbAMar = true;}
      if(CFZkPTcRUW == wnhtEoBxUG){eGUpcCTmsO = true;}
      else if(wnhtEoBxUG == CFZkPTcRUW){KLqiDrIORO = true;}
      if(iCaZzQZirN == wCDSbnatyh){PSQgoiQIhA = true;}
      else if(wCDSbnatyh == iCaZzQZirN){xKSjaLYyue = true;}
      if(MPYWlzzoIG == DXdkxRebEz){AwgYnroNKt = true;}
      else if(DXdkxRebEz == MPYWlzzoIG){AoOtfSggYp = true;}
      if(FVsEmQZWLd == FdAnizwRJY){XNGtkqFSGk = true;}
      else if(FdAnizwRJY == FVsEmQZWLd){VXmkGxKwaK = true;}
      if(aIZtXGLUbt == gLPlEgUESU){gdLStWimhf = true;}
      else if(gLPlEgUESU == aIZtXGLUbt){DmErEHqfuL = true;}
      if(rXMHLlgCzQ == LEMuGXKxxl){pKLjlhYwBj = true;}
      else if(LEMuGXKxxl == rXMHLlgCzQ){CCRwrVxxCj = true;}
      if(TnINQNJWlh == JZrVBRCOic){NFczqCLWwy = true;}
      if(pCWOlEpdzf == rJkZBqIqgP){cxCxSWjOdR = true;}
      if(neMOOhJksA == xaIimAQFhK){JBfdDMCWHC = true;}
      while(JZrVBRCOic == TnINQNJWlh){LboasZWgdc = true;}
      while(rJkZBqIqgP == rJkZBqIqgP){BbWjaMjVoY = true;}
      while(xaIimAQFhK == xaIimAQFhK){bAlNnSFpsk = true;}
      if(ozUWOHTtkl == true){ozUWOHTtkl = false;}
      if(eGUpcCTmsO == true){eGUpcCTmsO = false;}
      if(PSQgoiQIhA == true){PSQgoiQIhA = false;}
      if(AwgYnroNKt == true){AwgYnroNKt = false;}
      if(XNGtkqFSGk == true){XNGtkqFSGk = false;}
      if(gdLStWimhf == true){gdLStWimhf = false;}
      if(pKLjlhYwBj == true){pKLjlhYwBj = false;}
      if(NFczqCLWwy == true){NFczqCLWwy = false;}
      if(cxCxSWjOdR == true){cxCxSWjOdR = false;}
      if(JBfdDMCWHC == true){JBfdDMCWHC = false;}
      if(RJQVXbAMar == true){RJQVXbAMar = false;}
      if(KLqiDrIORO == true){KLqiDrIORO = false;}
      if(xKSjaLYyue == true){xKSjaLYyue = false;}
      if(AoOtfSggYp == true){AoOtfSggYp = false;}
      if(VXmkGxKwaK == true){VXmkGxKwaK = false;}
      if(DmErEHqfuL == true){DmErEHqfuL = false;}
      if(CCRwrVxxCj == true){CCRwrVxxCj = false;}
      if(LboasZWgdc == true){LboasZWgdc = false;}
      if(BbWjaMjVoY == true){BbWjaMjVoY = false;}
      if(bAlNnSFpsk == true){bAlNnSFpsk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXUMXSBVOF
{ 
  void YBxQGtehMs()
  { 
      bool KonifeLhXs = false;
      bool tDooWtkmmt = false;
      bool gpeZejaxtE = false;
      bool OkNiTBsheF = false;
      bool wCJDKcgzhS = false;
      bool TwCFyUJODw = false;
      bool DNmTeJpGUU = false;
      bool ADHhxdfaPB = false;
      bool DbObjRhIkz = false;
      bool qedhBiOpYA = false;
      bool mZdNRQnTHT = false;
      bool nizCsbzKiM = false;
      bool bgUVcVYYfO = false;
      bool PpCONcxAJT = false;
      bool cOARKIfboZ = false;
      bool iEGLYFFIjw = false;
      bool qOnrEyfjnQ = false;
      bool eyBPiNfDKT = false;
      bool oxjGfKippI = false;
      bool XnPNbOZIMM = false;
      string VQVrwVZEms;
      string HiwoTsoRFm;
      string xQIuCEAKwW;
      string EtaFrgGOyn;
      string krDpjRXLUI;
      string DhOHdEHapq;
      string UPIPoMIqxm;
      string mZSRCFNRLj;
      string fnpmSWfTam;
      string YfYGSUimBX;
      string JgOgUcOxFY;
      string qpOFLfYUxS;
      string gnPKNHBLyg;
      string VZQmazZISo;
      string HhNCwiQTul;
      string wNphqURDTN;
      string bCyYCQYbeM;
      string GQCHKyZNOd;
      string qhQLkIjhwF;
      string gVoFMFjoze;
      if(VQVrwVZEms == JgOgUcOxFY){KonifeLhXs = true;}
      else if(JgOgUcOxFY == VQVrwVZEms){mZdNRQnTHT = true;}
      if(HiwoTsoRFm == qpOFLfYUxS){tDooWtkmmt = true;}
      else if(qpOFLfYUxS == HiwoTsoRFm){nizCsbzKiM = true;}
      if(xQIuCEAKwW == gnPKNHBLyg){gpeZejaxtE = true;}
      else if(gnPKNHBLyg == xQIuCEAKwW){bgUVcVYYfO = true;}
      if(EtaFrgGOyn == VZQmazZISo){OkNiTBsheF = true;}
      else if(VZQmazZISo == EtaFrgGOyn){PpCONcxAJT = true;}
      if(krDpjRXLUI == HhNCwiQTul){wCJDKcgzhS = true;}
      else if(HhNCwiQTul == krDpjRXLUI){cOARKIfboZ = true;}
      if(DhOHdEHapq == wNphqURDTN){TwCFyUJODw = true;}
      else if(wNphqURDTN == DhOHdEHapq){iEGLYFFIjw = true;}
      if(UPIPoMIqxm == bCyYCQYbeM){DNmTeJpGUU = true;}
      else if(bCyYCQYbeM == UPIPoMIqxm){qOnrEyfjnQ = true;}
      if(mZSRCFNRLj == GQCHKyZNOd){ADHhxdfaPB = true;}
      if(fnpmSWfTam == qhQLkIjhwF){DbObjRhIkz = true;}
      if(YfYGSUimBX == gVoFMFjoze){qedhBiOpYA = true;}
      while(GQCHKyZNOd == mZSRCFNRLj){eyBPiNfDKT = true;}
      while(qhQLkIjhwF == qhQLkIjhwF){oxjGfKippI = true;}
      while(gVoFMFjoze == gVoFMFjoze){XnPNbOZIMM = true;}
      if(KonifeLhXs == true){KonifeLhXs = false;}
      if(tDooWtkmmt == true){tDooWtkmmt = false;}
      if(gpeZejaxtE == true){gpeZejaxtE = false;}
      if(OkNiTBsheF == true){OkNiTBsheF = false;}
      if(wCJDKcgzhS == true){wCJDKcgzhS = false;}
      if(TwCFyUJODw == true){TwCFyUJODw = false;}
      if(DNmTeJpGUU == true){DNmTeJpGUU = false;}
      if(ADHhxdfaPB == true){ADHhxdfaPB = false;}
      if(DbObjRhIkz == true){DbObjRhIkz = false;}
      if(qedhBiOpYA == true){qedhBiOpYA = false;}
      if(mZdNRQnTHT == true){mZdNRQnTHT = false;}
      if(nizCsbzKiM == true){nizCsbzKiM = false;}
      if(bgUVcVYYfO == true){bgUVcVYYfO = false;}
      if(PpCONcxAJT == true){PpCONcxAJT = false;}
      if(cOARKIfboZ == true){cOARKIfboZ = false;}
      if(iEGLYFFIjw == true){iEGLYFFIjw = false;}
      if(qOnrEyfjnQ == true){qOnrEyfjnQ = false;}
      if(eyBPiNfDKT == true){eyBPiNfDKT = false;}
      if(oxjGfKippI == true){oxjGfKippI = false;}
      if(XnPNbOZIMM == true){XnPNbOZIMM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFSTASLPHY
{ 
  void ougkpWKqxy()
  { 
      bool GpboLLIVVp = false;
      bool sZfUpVVOBb = false;
      bool mdljyFKrEj = false;
      bool cynLsoppAP = false;
      bool xCowOqtFyG = false;
      bool wKDKPcDqpG = false;
      bool AQQlMtkUbB = false;
      bool eeNldjnpVH = false;
      bool KFtynStdwP = false;
      bool kyAtOgkDjT = false;
      bool FZcwaQxRfe = false;
      bool oNViwuWSxt = false;
      bool zGXLQgeSWw = false;
      bool zjFCBjbxXX = false;
      bool UcyRaWcRyT = false;
      bool KSFoTyCRes = false;
      bool ketifEHSgL = false;
      bool SYuZZWIGkt = false;
      bool DNUDlgdQiD = false;
      bool hKRdlphOlV = false;
      string gHkyzhtfWn;
      string qOumwTWFla;
      string aTBEFDnzMe;
      string NJoCMcCNhm;
      string YzrVcLowlj;
      string lIdEENGfrw;
      string stTqahYsaT;
      string RIWyCaafas;
      string OqNcsFekxz;
      string WVUltdfAuu;
      string lwVRRckeBc;
      string lZFzhBgqxV;
      string CnuawwnjEY;
      string uakfGRVuKQ;
      string TAiUNwQUEr;
      string xoCYryAtUV;
      string nBachKoZrP;
      string fkfgCCEaNA;
      string eSeMaGXLmH;
      string QaZnbRYFlC;
      if(gHkyzhtfWn == lwVRRckeBc){GpboLLIVVp = true;}
      else if(lwVRRckeBc == gHkyzhtfWn){FZcwaQxRfe = true;}
      if(qOumwTWFla == lZFzhBgqxV){sZfUpVVOBb = true;}
      else if(lZFzhBgqxV == qOumwTWFla){oNViwuWSxt = true;}
      if(aTBEFDnzMe == CnuawwnjEY){mdljyFKrEj = true;}
      else if(CnuawwnjEY == aTBEFDnzMe){zGXLQgeSWw = true;}
      if(NJoCMcCNhm == uakfGRVuKQ){cynLsoppAP = true;}
      else if(uakfGRVuKQ == NJoCMcCNhm){zjFCBjbxXX = true;}
      if(YzrVcLowlj == TAiUNwQUEr){xCowOqtFyG = true;}
      else if(TAiUNwQUEr == YzrVcLowlj){UcyRaWcRyT = true;}
      if(lIdEENGfrw == xoCYryAtUV){wKDKPcDqpG = true;}
      else if(xoCYryAtUV == lIdEENGfrw){KSFoTyCRes = true;}
      if(stTqahYsaT == nBachKoZrP){AQQlMtkUbB = true;}
      else if(nBachKoZrP == stTqahYsaT){ketifEHSgL = true;}
      if(RIWyCaafas == fkfgCCEaNA){eeNldjnpVH = true;}
      if(OqNcsFekxz == eSeMaGXLmH){KFtynStdwP = true;}
      if(WVUltdfAuu == QaZnbRYFlC){kyAtOgkDjT = true;}
      while(fkfgCCEaNA == RIWyCaafas){SYuZZWIGkt = true;}
      while(eSeMaGXLmH == eSeMaGXLmH){DNUDlgdQiD = true;}
      while(QaZnbRYFlC == QaZnbRYFlC){hKRdlphOlV = true;}
      if(GpboLLIVVp == true){GpboLLIVVp = false;}
      if(sZfUpVVOBb == true){sZfUpVVOBb = false;}
      if(mdljyFKrEj == true){mdljyFKrEj = false;}
      if(cynLsoppAP == true){cynLsoppAP = false;}
      if(xCowOqtFyG == true){xCowOqtFyG = false;}
      if(wKDKPcDqpG == true){wKDKPcDqpG = false;}
      if(AQQlMtkUbB == true){AQQlMtkUbB = false;}
      if(eeNldjnpVH == true){eeNldjnpVH = false;}
      if(KFtynStdwP == true){KFtynStdwP = false;}
      if(kyAtOgkDjT == true){kyAtOgkDjT = false;}
      if(FZcwaQxRfe == true){FZcwaQxRfe = false;}
      if(oNViwuWSxt == true){oNViwuWSxt = false;}
      if(zGXLQgeSWw == true){zGXLQgeSWw = false;}
      if(zjFCBjbxXX == true){zjFCBjbxXX = false;}
      if(UcyRaWcRyT == true){UcyRaWcRyT = false;}
      if(KSFoTyCRes == true){KSFoTyCRes = false;}
      if(ketifEHSgL == true){ketifEHSgL = false;}
      if(SYuZZWIGkt == true){SYuZZWIGkt = false;}
      if(DNUDlgdQiD == true){DNUDlgdQiD = false;}
      if(hKRdlphOlV == true){hKRdlphOlV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMGILTGATB
{ 
  void CfxOjLsuSm()
  { 
      bool AgfBplXmBc = false;
      bool WQHhNpPlbp = false;
      bool BTJWnBQQSP = false;
      bool LkJTkHCwla = false;
      bool CzjsnqYVms = false;
      bool jJJVxfXIMn = false;
      bool UGTkRkGmwG = false;
      bool mTzBmCiQiw = false;
      bool ctdZeBbmWE = false;
      bool isixFueybD = false;
      bool kkZfFQKIiu = false;
      bool xHZQLacsGP = false;
      bool JSQrWtkBuq = false;
      bool WjofLqTxUO = false;
      bool qTEaHbTRld = false;
      bool SkrLsRUhJK = false;
      bool eIMrXMRtFT = false;
      bool GfYrYpOojt = false;
      bool aSPQYkrclt = false;
      bool WlmJihGMCt = false;
      string pyqNxxSeXO;
      string srQoXljxAm;
      string CErzbYVuFo;
      string OCJKkTnmNm;
      string VffuscrjNA;
      string PrbZBlFqlX;
      string aXYhAqiGEE;
      string xwjMQWXxGy;
      string glgFZVZjIz;
      string NwBoMyHxtB;
      string skeJCSIOIe;
      string NIjmqnqSId;
      string RzyEpAuuAS;
      string OaCFFuGWCG;
      string NKaclFMNxX;
      string GnoQjtlaSC;
      string XNOoQmFehw;
      string hUQCPHXVSk;
      string nhxcMZlkVK;
      string IfEAiAulMy;
      if(pyqNxxSeXO == skeJCSIOIe){AgfBplXmBc = true;}
      else if(skeJCSIOIe == pyqNxxSeXO){kkZfFQKIiu = true;}
      if(srQoXljxAm == NIjmqnqSId){WQHhNpPlbp = true;}
      else if(NIjmqnqSId == srQoXljxAm){xHZQLacsGP = true;}
      if(CErzbYVuFo == RzyEpAuuAS){BTJWnBQQSP = true;}
      else if(RzyEpAuuAS == CErzbYVuFo){JSQrWtkBuq = true;}
      if(OCJKkTnmNm == OaCFFuGWCG){LkJTkHCwla = true;}
      else if(OaCFFuGWCG == OCJKkTnmNm){WjofLqTxUO = true;}
      if(VffuscrjNA == NKaclFMNxX){CzjsnqYVms = true;}
      else if(NKaclFMNxX == VffuscrjNA){qTEaHbTRld = true;}
      if(PrbZBlFqlX == GnoQjtlaSC){jJJVxfXIMn = true;}
      else if(GnoQjtlaSC == PrbZBlFqlX){SkrLsRUhJK = true;}
      if(aXYhAqiGEE == XNOoQmFehw){UGTkRkGmwG = true;}
      else if(XNOoQmFehw == aXYhAqiGEE){eIMrXMRtFT = true;}
      if(xwjMQWXxGy == hUQCPHXVSk){mTzBmCiQiw = true;}
      if(glgFZVZjIz == nhxcMZlkVK){ctdZeBbmWE = true;}
      if(NwBoMyHxtB == IfEAiAulMy){isixFueybD = true;}
      while(hUQCPHXVSk == xwjMQWXxGy){GfYrYpOojt = true;}
      while(nhxcMZlkVK == nhxcMZlkVK){aSPQYkrclt = true;}
      while(IfEAiAulMy == IfEAiAulMy){WlmJihGMCt = true;}
      if(AgfBplXmBc == true){AgfBplXmBc = false;}
      if(WQHhNpPlbp == true){WQHhNpPlbp = false;}
      if(BTJWnBQQSP == true){BTJWnBQQSP = false;}
      if(LkJTkHCwla == true){LkJTkHCwla = false;}
      if(CzjsnqYVms == true){CzjsnqYVms = false;}
      if(jJJVxfXIMn == true){jJJVxfXIMn = false;}
      if(UGTkRkGmwG == true){UGTkRkGmwG = false;}
      if(mTzBmCiQiw == true){mTzBmCiQiw = false;}
      if(ctdZeBbmWE == true){ctdZeBbmWE = false;}
      if(isixFueybD == true){isixFueybD = false;}
      if(kkZfFQKIiu == true){kkZfFQKIiu = false;}
      if(xHZQLacsGP == true){xHZQLacsGP = false;}
      if(JSQrWtkBuq == true){JSQrWtkBuq = false;}
      if(WjofLqTxUO == true){WjofLqTxUO = false;}
      if(qTEaHbTRld == true){qTEaHbTRld = false;}
      if(SkrLsRUhJK == true){SkrLsRUhJK = false;}
      if(eIMrXMRtFT == true){eIMrXMRtFT = false;}
      if(GfYrYpOojt == true){GfYrYpOojt = false;}
      if(aSPQYkrclt == true){aSPQYkrclt = false;}
      if(WlmJihGMCt == true){WlmJihGMCt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKLNIFDYRF
{ 
  void gxgCbKgThX()
  { 
      bool dDNOEqZjSb = false;
      bool piyNDDApqr = false;
      bool gQyqkgoYKC = false;
      bool wflwdikHSB = false;
      bool KwoCInsUjd = false;
      bool kxZPEMFWdW = false;
      bool BAYQfKxBiU = false;
      bool SsXphjbwhx = false;
      bool nTofQzFWrQ = false;
      bool dNcuzJWYVy = false;
      bool qrlOLrZjgU = false;
      bool kInghhLszf = false;
      bool EZISpEPbpX = false;
      bool MCZjGwhZUX = false;
      bool ZVpXfUZwMR = false;
      bool xdYosQiSXG = false;
      bool cxsIHhhEZl = false;
      bool zlXaGijklV = false;
      bool eSPYaidjpo = false;
      bool NOBOubbgQx = false;
      string TCxKJfssxg;
      string FhuFLdTegJ;
      string AjrnImzcQe;
      string MEmeEEJiEG;
      string JDWXzhZOod;
      string ooosuiKICW;
      string gQbRTBtPBG;
      string TjZZAwNToZ;
      string MjmmoWPtjU;
      string tAggZraEEy;
      string mKMhJFOOry;
      string VpTcKwcobw;
      string kzfgMTDsAH;
      string VIPqlBXEcj;
      string HBCkyEgEWc;
      string PkbHMmdfVp;
      string CVNjcMZcpI;
      string YXLrnjxthI;
      string lyVWrjfIdy;
      string XqimglmRIk;
      if(TCxKJfssxg == mKMhJFOOry){dDNOEqZjSb = true;}
      else if(mKMhJFOOry == TCxKJfssxg){qrlOLrZjgU = true;}
      if(FhuFLdTegJ == VpTcKwcobw){piyNDDApqr = true;}
      else if(VpTcKwcobw == FhuFLdTegJ){kInghhLszf = true;}
      if(AjrnImzcQe == kzfgMTDsAH){gQyqkgoYKC = true;}
      else if(kzfgMTDsAH == AjrnImzcQe){EZISpEPbpX = true;}
      if(MEmeEEJiEG == VIPqlBXEcj){wflwdikHSB = true;}
      else if(VIPqlBXEcj == MEmeEEJiEG){MCZjGwhZUX = true;}
      if(JDWXzhZOod == HBCkyEgEWc){KwoCInsUjd = true;}
      else if(HBCkyEgEWc == JDWXzhZOod){ZVpXfUZwMR = true;}
      if(ooosuiKICW == PkbHMmdfVp){kxZPEMFWdW = true;}
      else if(PkbHMmdfVp == ooosuiKICW){xdYosQiSXG = true;}
      if(gQbRTBtPBG == CVNjcMZcpI){BAYQfKxBiU = true;}
      else if(CVNjcMZcpI == gQbRTBtPBG){cxsIHhhEZl = true;}
      if(TjZZAwNToZ == YXLrnjxthI){SsXphjbwhx = true;}
      if(MjmmoWPtjU == lyVWrjfIdy){nTofQzFWrQ = true;}
      if(tAggZraEEy == XqimglmRIk){dNcuzJWYVy = true;}
      while(YXLrnjxthI == TjZZAwNToZ){zlXaGijklV = true;}
      while(lyVWrjfIdy == lyVWrjfIdy){eSPYaidjpo = true;}
      while(XqimglmRIk == XqimglmRIk){NOBOubbgQx = true;}
      if(dDNOEqZjSb == true){dDNOEqZjSb = false;}
      if(piyNDDApqr == true){piyNDDApqr = false;}
      if(gQyqkgoYKC == true){gQyqkgoYKC = false;}
      if(wflwdikHSB == true){wflwdikHSB = false;}
      if(KwoCInsUjd == true){KwoCInsUjd = false;}
      if(kxZPEMFWdW == true){kxZPEMFWdW = false;}
      if(BAYQfKxBiU == true){BAYQfKxBiU = false;}
      if(SsXphjbwhx == true){SsXphjbwhx = false;}
      if(nTofQzFWrQ == true){nTofQzFWrQ = false;}
      if(dNcuzJWYVy == true){dNcuzJWYVy = false;}
      if(qrlOLrZjgU == true){qrlOLrZjgU = false;}
      if(kInghhLszf == true){kInghhLszf = false;}
      if(EZISpEPbpX == true){EZISpEPbpX = false;}
      if(MCZjGwhZUX == true){MCZjGwhZUX = false;}
      if(ZVpXfUZwMR == true){ZVpXfUZwMR = false;}
      if(xdYosQiSXG == true){xdYosQiSXG = false;}
      if(cxsIHhhEZl == true){cxsIHhhEZl = false;}
      if(zlXaGijklV == true){zlXaGijklV = false;}
      if(eSPYaidjpo == true){eSPYaidjpo = false;}
      if(NOBOubbgQx == true){NOBOubbgQx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVBUDUSJGS
{ 
  void ewEeZFquPL()
  { 
      bool fUzbisBtwi = false;
      bool WtyfGoBgSM = false;
      bool ncyuWJeJxc = false;
      bool RemdeJAHnu = false;
      bool XIZOtCSWuD = false;
      bool TMXOVCWDFZ = false;
      bool NqwTQqGTAw = false;
      bool otrWnfDiAT = false;
      bool qINsIEGYIc = false;
      bool mxBOggMGyC = false;
      bool uyVzOZUBZo = false;
      bool ymCkiFcCKL = false;
      bool khKXJqrdpG = false;
      bool TxkyXrlOdh = false;
      bool jFySdztQea = false;
      bool EJumRNmyoW = false;
      bool gpKSVBBENp = false;
      bool TNXcafiqsJ = false;
      bool wbzOCJByfJ = false;
      bool EnYGBttfxc = false;
      string rfELOdCPkZ;
      string xyabOxTuLb;
      string cPyNUtYwyc;
      string tuJLHcwZqr;
      string IcRgKzBuTf;
      string tUHoYbgqqT;
      string FFQHeBnPTk;
      string AtDTSzxRCU;
      string sccShYnUme;
      string uFhXlDLKBJ;
      string LlahfARmWZ;
      string dPoVabbyYG;
      string NTbopuLfhP;
      string mmQsJGCtlh;
      string HAxNAeQLwJ;
      string aNkturJlqj;
      string okFGlqzuMT;
      string ZhLqyMVOnL;
      string dziXnZCVxQ;
      string xQCCsVtqaJ;
      if(rfELOdCPkZ == LlahfARmWZ){fUzbisBtwi = true;}
      else if(LlahfARmWZ == rfELOdCPkZ){uyVzOZUBZo = true;}
      if(xyabOxTuLb == dPoVabbyYG){WtyfGoBgSM = true;}
      else if(dPoVabbyYG == xyabOxTuLb){ymCkiFcCKL = true;}
      if(cPyNUtYwyc == NTbopuLfhP){ncyuWJeJxc = true;}
      else if(NTbopuLfhP == cPyNUtYwyc){khKXJqrdpG = true;}
      if(tuJLHcwZqr == mmQsJGCtlh){RemdeJAHnu = true;}
      else if(mmQsJGCtlh == tuJLHcwZqr){TxkyXrlOdh = true;}
      if(IcRgKzBuTf == HAxNAeQLwJ){XIZOtCSWuD = true;}
      else if(HAxNAeQLwJ == IcRgKzBuTf){jFySdztQea = true;}
      if(tUHoYbgqqT == aNkturJlqj){TMXOVCWDFZ = true;}
      else if(aNkturJlqj == tUHoYbgqqT){EJumRNmyoW = true;}
      if(FFQHeBnPTk == okFGlqzuMT){NqwTQqGTAw = true;}
      else if(okFGlqzuMT == FFQHeBnPTk){gpKSVBBENp = true;}
      if(AtDTSzxRCU == ZhLqyMVOnL){otrWnfDiAT = true;}
      if(sccShYnUme == dziXnZCVxQ){qINsIEGYIc = true;}
      if(uFhXlDLKBJ == xQCCsVtqaJ){mxBOggMGyC = true;}
      while(ZhLqyMVOnL == AtDTSzxRCU){TNXcafiqsJ = true;}
      while(dziXnZCVxQ == dziXnZCVxQ){wbzOCJByfJ = true;}
      while(xQCCsVtqaJ == xQCCsVtqaJ){EnYGBttfxc = true;}
      if(fUzbisBtwi == true){fUzbisBtwi = false;}
      if(WtyfGoBgSM == true){WtyfGoBgSM = false;}
      if(ncyuWJeJxc == true){ncyuWJeJxc = false;}
      if(RemdeJAHnu == true){RemdeJAHnu = false;}
      if(XIZOtCSWuD == true){XIZOtCSWuD = false;}
      if(TMXOVCWDFZ == true){TMXOVCWDFZ = false;}
      if(NqwTQqGTAw == true){NqwTQqGTAw = false;}
      if(otrWnfDiAT == true){otrWnfDiAT = false;}
      if(qINsIEGYIc == true){qINsIEGYIc = false;}
      if(mxBOggMGyC == true){mxBOggMGyC = false;}
      if(uyVzOZUBZo == true){uyVzOZUBZo = false;}
      if(ymCkiFcCKL == true){ymCkiFcCKL = false;}
      if(khKXJqrdpG == true){khKXJqrdpG = false;}
      if(TxkyXrlOdh == true){TxkyXrlOdh = false;}
      if(jFySdztQea == true){jFySdztQea = false;}
      if(EJumRNmyoW == true){EJumRNmyoW = false;}
      if(gpKSVBBENp == true){gpKSVBBENp = false;}
      if(TNXcafiqsJ == true){TNXcafiqsJ = false;}
      if(wbzOCJByfJ == true){wbzOCJByfJ = false;}
      if(EnYGBttfxc == true){EnYGBttfxc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUXYHYTBBA
{ 
  void tECQOSsXVh()
  { 
      bool VkguDAFbef = false;
      bool jaLfgDoEGQ = false;
      bool eejWefmsAK = false;
      bool WpCwZPYDRp = false;
      bool IeWeqFoBTk = false;
      bool GAMnhqBJQX = false;
      bool NLbUJsYOGQ = false;
      bool dklPHzHEeY = false;
      bool qkZPDVdNOi = false;
      bool OPltcwDCVx = false;
      bool gZuCGVOwfi = false;
      bool iwdrfbkMQm = false;
      bool PKAWBOyqmK = false;
      bool uFigrQoXIh = false;
      bool HhheASltNB = false;
      bool LpkhhWZYAq = false;
      bool WWIUmcNwAP = false;
      bool lNDifhbUVi = false;
      bool cDdkzFTAzV = false;
      bool pQWQLjYMqW = false;
      string EAQdnEPRHh;
      string BLcWjXBeis;
      string rOORQbBrqa;
      string LjHKBKtOrp;
      string aCkyhZpADs;
      string hgYdipkzML;
      string DWafVRERUY;
      string cmlsRpdPjq;
      string lAoyseKcbL;
      string YuBfmEbEbP;
      string UXedPutfLr;
      string LUOVZChbmq;
      string HapJAhlFFN;
      string NYmTVOVLhy;
      string jeRizDffGj;
      string WzRkIthUch;
      string JnZyelguzL;
      string gVtoGbJGJw;
      string BFzVqOHCLb;
      string gAhAnwFSEM;
      if(EAQdnEPRHh == UXedPutfLr){VkguDAFbef = true;}
      else if(UXedPutfLr == EAQdnEPRHh){gZuCGVOwfi = true;}
      if(BLcWjXBeis == LUOVZChbmq){jaLfgDoEGQ = true;}
      else if(LUOVZChbmq == BLcWjXBeis){iwdrfbkMQm = true;}
      if(rOORQbBrqa == HapJAhlFFN){eejWefmsAK = true;}
      else if(HapJAhlFFN == rOORQbBrqa){PKAWBOyqmK = true;}
      if(LjHKBKtOrp == NYmTVOVLhy){WpCwZPYDRp = true;}
      else if(NYmTVOVLhy == LjHKBKtOrp){uFigrQoXIh = true;}
      if(aCkyhZpADs == jeRizDffGj){IeWeqFoBTk = true;}
      else if(jeRizDffGj == aCkyhZpADs){HhheASltNB = true;}
      if(hgYdipkzML == WzRkIthUch){GAMnhqBJQX = true;}
      else if(WzRkIthUch == hgYdipkzML){LpkhhWZYAq = true;}
      if(DWafVRERUY == JnZyelguzL){NLbUJsYOGQ = true;}
      else if(JnZyelguzL == DWafVRERUY){WWIUmcNwAP = true;}
      if(cmlsRpdPjq == gVtoGbJGJw){dklPHzHEeY = true;}
      if(lAoyseKcbL == BFzVqOHCLb){qkZPDVdNOi = true;}
      if(YuBfmEbEbP == gAhAnwFSEM){OPltcwDCVx = true;}
      while(gVtoGbJGJw == cmlsRpdPjq){lNDifhbUVi = true;}
      while(BFzVqOHCLb == BFzVqOHCLb){cDdkzFTAzV = true;}
      while(gAhAnwFSEM == gAhAnwFSEM){pQWQLjYMqW = true;}
      if(VkguDAFbef == true){VkguDAFbef = false;}
      if(jaLfgDoEGQ == true){jaLfgDoEGQ = false;}
      if(eejWefmsAK == true){eejWefmsAK = false;}
      if(WpCwZPYDRp == true){WpCwZPYDRp = false;}
      if(IeWeqFoBTk == true){IeWeqFoBTk = false;}
      if(GAMnhqBJQX == true){GAMnhqBJQX = false;}
      if(NLbUJsYOGQ == true){NLbUJsYOGQ = false;}
      if(dklPHzHEeY == true){dklPHzHEeY = false;}
      if(qkZPDVdNOi == true){qkZPDVdNOi = false;}
      if(OPltcwDCVx == true){OPltcwDCVx = false;}
      if(gZuCGVOwfi == true){gZuCGVOwfi = false;}
      if(iwdrfbkMQm == true){iwdrfbkMQm = false;}
      if(PKAWBOyqmK == true){PKAWBOyqmK = false;}
      if(uFigrQoXIh == true){uFigrQoXIh = false;}
      if(HhheASltNB == true){HhheASltNB = false;}
      if(LpkhhWZYAq == true){LpkhhWZYAq = false;}
      if(WWIUmcNwAP == true){WWIUmcNwAP = false;}
      if(lNDifhbUVi == true){lNDifhbUVi = false;}
      if(cDdkzFTAzV == true){cDdkzFTAzV = false;}
      if(pQWQLjYMqW == true){pQWQLjYMqW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMKFVGPIOI
{ 
  void BjSOJpuapA()
  { 
      bool UeYNQeWfKH = false;
      bool eaUbCanKWH = false;
      bool lloWTQupUX = false;
      bool NbsPSmjjVK = false;
      bool TepZgFdbnq = false;
      bool JKzTuioCsA = false;
      bool jfLmtChFIO = false;
      bool pDnLnGuPpN = false;
      bool mSCcOCbZUj = false;
      bool yhpVanTDfd = false;
      bool XYTYBFWnen = false;
      bool mYLeMRchXq = false;
      bool ZHjYQHMRkz = false;
      bool lqjMpOzdbI = false;
      bool fntfwYWKJJ = false;
      bool LlfnDPntHt = false;
      bool rECeBuoyoy = false;
      bool SyGOLkNDbr = false;
      bool jBIbnALuIa = false;
      bool aEWgQalOeA = false;
      string IeDgHVYlCL;
      string ZLKAuSCclR;
      string WsptIQgWyG;
      string alOyUTEEdD;
      string zhFWeIAXoB;
      string AuAyfOoIXp;
      string oBnwkmxLfb;
      string OxyhRnmSOA;
      string PIhxFfkPRF;
      string dufmNytJkr;
      string KorNmCwRgr;
      string aVtXagTqpE;
      string BhtZxSRKUT;
      string sdhWoaQUJD;
      string iSiZdIBHMg;
      string dDSfpcuRPT;
      string jlxMyxmWiz;
      string PzgmViyTwn;
      string RJxmppKBgL;
      string fyEpSxVWag;
      if(IeDgHVYlCL == KorNmCwRgr){UeYNQeWfKH = true;}
      else if(KorNmCwRgr == IeDgHVYlCL){XYTYBFWnen = true;}
      if(ZLKAuSCclR == aVtXagTqpE){eaUbCanKWH = true;}
      else if(aVtXagTqpE == ZLKAuSCclR){mYLeMRchXq = true;}
      if(WsptIQgWyG == BhtZxSRKUT){lloWTQupUX = true;}
      else if(BhtZxSRKUT == WsptIQgWyG){ZHjYQHMRkz = true;}
      if(alOyUTEEdD == sdhWoaQUJD){NbsPSmjjVK = true;}
      else if(sdhWoaQUJD == alOyUTEEdD){lqjMpOzdbI = true;}
      if(zhFWeIAXoB == iSiZdIBHMg){TepZgFdbnq = true;}
      else if(iSiZdIBHMg == zhFWeIAXoB){fntfwYWKJJ = true;}
      if(AuAyfOoIXp == dDSfpcuRPT){JKzTuioCsA = true;}
      else if(dDSfpcuRPT == AuAyfOoIXp){LlfnDPntHt = true;}
      if(oBnwkmxLfb == jlxMyxmWiz){jfLmtChFIO = true;}
      else if(jlxMyxmWiz == oBnwkmxLfb){rECeBuoyoy = true;}
      if(OxyhRnmSOA == PzgmViyTwn){pDnLnGuPpN = true;}
      if(PIhxFfkPRF == RJxmppKBgL){mSCcOCbZUj = true;}
      if(dufmNytJkr == fyEpSxVWag){yhpVanTDfd = true;}
      while(PzgmViyTwn == OxyhRnmSOA){SyGOLkNDbr = true;}
      while(RJxmppKBgL == RJxmppKBgL){jBIbnALuIa = true;}
      while(fyEpSxVWag == fyEpSxVWag){aEWgQalOeA = true;}
      if(UeYNQeWfKH == true){UeYNQeWfKH = false;}
      if(eaUbCanKWH == true){eaUbCanKWH = false;}
      if(lloWTQupUX == true){lloWTQupUX = false;}
      if(NbsPSmjjVK == true){NbsPSmjjVK = false;}
      if(TepZgFdbnq == true){TepZgFdbnq = false;}
      if(JKzTuioCsA == true){JKzTuioCsA = false;}
      if(jfLmtChFIO == true){jfLmtChFIO = false;}
      if(pDnLnGuPpN == true){pDnLnGuPpN = false;}
      if(mSCcOCbZUj == true){mSCcOCbZUj = false;}
      if(yhpVanTDfd == true){yhpVanTDfd = false;}
      if(XYTYBFWnen == true){XYTYBFWnen = false;}
      if(mYLeMRchXq == true){mYLeMRchXq = false;}
      if(ZHjYQHMRkz == true){ZHjYQHMRkz = false;}
      if(lqjMpOzdbI == true){lqjMpOzdbI = false;}
      if(fntfwYWKJJ == true){fntfwYWKJJ = false;}
      if(LlfnDPntHt == true){LlfnDPntHt = false;}
      if(rECeBuoyoy == true){rECeBuoyoy = false;}
      if(SyGOLkNDbr == true){SyGOLkNDbr = false;}
      if(jBIbnALuIa == true){jBIbnALuIa = false;}
      if(aEWgQalOeA == true){aEWgQalOeA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJDBQNYFYQ
{ 
  void HawsoHOqss()
  { 
      bool XxryZynyEW = false;
      bool XfVqCjJThs = false;
      bool ABjrLwYttg = false;
      bool DDtWhWHkhe = false;
      bool GJbHJWVnpQ = false;
      bool dMVGaWMzlc = false;
      bool YsDXSTlzJe = false;
      bool cXlClqZcin = false;
      bool ZjDdCphmwK = false;
      bool JHzEFMGEnp = false;
      bool kWeLnFaSUi = false;
      bool wjQyCooZUc = false;
      bool lyDyVUYgwY = false;
      bool kVnsDDFrox = false;
      bool OOSMNYqACQ = false;
      bool XfiLDmSfoS = false;
      bool ftWuxawXtz = false;
      bool ixjXNXeqjw = false;
      bool dXeeBElboQ = false;
      bool kYCWQUrXOm = false;
      string OSkzANhtkw;
      string CAmLiAelYd;
      string EaruxWuKVO;
      string SyUIhXEHij;
      string JDxGGhleVA;
      string asnMKnapBc;
      string RXXVcEfdcK;
      string wXCoTBcknO;
      string kPoUnYJIxt;
      string xOFFRlebdC;
      string CHCKECqzsJ;
      string KpBmrCiDgD;
      string tWghNhSxWg;
      string VBHlMcMdPk;
      string hJPmjHMSMO;
      string DatZHeZTxW;
      string jtbLmIiPZO;
      string oFmwVkHtyG;
      string UzjHdtHgeg;
      string DrfsBngDzb;
      if(OSkzANhtkw == CHCKECqzsJ){XxryZynyEW = true;}
      else if(CHCKECqzsJ == OSkzANhtkw){kWeLnFaSUi = true;}
      if(CAmLiAelYd == KpBmrCiDgD){XfVqCjJThs = true;}
      else if(KpBmrCiDgD == CAmLiAelYd){wjQyCooZUc = true;}
      if(EaruxWuKVO == tWghNhSxWg){ABjrLwYttg = true;}
      else if(tWghNhSxWg == EaruxWuKVO){lyDyVUYgwY = true;}
      if(SyUIhXEHij == VBHlMcMdPk){DDtWhWHkhe = true;}
      else if(VBHlMcMdPk == SyUIhXEHij){kVnsDDFrox = true;}
      if(JDxGGhleVA == hJPmjHMSMO){GJbHJWVnpQ = true;}
      else if(hJPmjHMSMO == JDxGGhleVA){OOSMNYqACQ = true;}
      if(asnMKnapBc == DatZHeZTxW){dMVGaWMzlc = true;}
      else if(DatZHeZTxW == asnMKnapBc){XfiLDmSfoS = true;}
      if(RXXVcEfdcK == jtbLmIiPZO){YsDXSTlzJe = true;}
      else if(jtbLmIiPZO == RXXVcEfdcK){ftWuxawXtz = true;}
      if(wXCoTBcknO == oFmwVkHtyG){cXlClqZcin = true;}
      if(kPoUnYJIxt == UzjHdtHgeg){ZjDdCphmwK = true;}
      if(xOFFRlebdC == DrfsBngDzb){JHzEFMGEnp = true;}
      while(oFmwVkHtyG == wXCoTBcknO){ixjXNXeqjw = true;}
      while(UzjHdtHgeg == UzjHdtHgeg){dXeeBElboQ = true;}
      while(DrfsBngDzb == DrfsBngDzb){kYCWQUrXOm = true;}
      if(XxryZynyEW == true){XxryZynyEW = false;}
      if(XfVqCjJThs == true){XfVqCjJThs = false;}
      if(ABjrLwYttg == true){ABjrLwYttg = false;}
      if(DDtWhWHkhe == true){DDtWhWHkhe = false;}
      if(GJbHJWVnpQ == true){GJbHJWVnpQ = false;}
      if(dMVGaWMzlc == true){dMVGaWMzlc = false;}
      if(YsDXSTlzJe == true){YsDXSTlzJe = false;}
      if(cXlClqZcin == true){cXlClqZcin = false;}
      if(ZjDdCphmwK == true){ZjDdCphmwK = false;}
      if(JHzEFMGEnp == true){JHzEFMGEnp = false;}
      if(kWeLnFaSUi == true){kWeLnFaSUi = false;}
      if(wjQyCooZUc == true){wjQyCooZUc = false;}
      if(lyDyVUYgwY == true){lyDyVUYgwY = false;}
      if(kVnsDDFrox == true){kVnsDDFrox = false;}
      if(OOSMNYqACQ == true){OOSMNYqACQ = false;}
      if(XfiLDmSfoS == true){XfiLDmSfoS = false;}
      if(ftWuxawXtz == true){ftWuxawXtz = false;}
      if(ixjXNXeqjw == true){ixjXNXeqjw = false;}
      if(dXeeBElboQ == true){dXeeBElboQ = false;}
      if(kYCWQUrXOm == true){kYCWQUrXOm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNRGEHQGVS
{ 
  void jKNXRHssgz()
  { 
      bool KufpOdhSUx = false;
      bool bHelAtwLJk = false;
      bool rZtEmBctPq = false;
      bool GnloZEMCiq = false;
      bool JZDspXttCQ = false;
      bool gSspmjBaDM = false;
      bool BmCcqnUoMw = false;
      bool htcSaSVBOO = false;
      bool HiqzKmtuBo = false;
      bool DlzWpWXaBC = false;
      bool DFhGimoZPU = false;
      bool NzLnFRwDRD = false;
      bool sZnXsuuGcE = false;
      bool uuzMLBBjPX = false;
      bool yTfgaDZKQY = false;
      bool aUIxIcRKNm = false;
      bool rixKZSAzbD = false;
      bool PLmtFYsGwo = false;
      bool VjoEdZmBDh = false;
      bool jqWbfOVUGI = false;
      string SWpRTpVZij;
      string XbmxiEJYjp;
      string YlUzbHbrnZ;
      string jMaMUWhBqF;
      string eTecSuPPaD;
      string qYbBGfCqoM;
      string OdlJzKAZbM;
      string WIgdKFHqgf;
      string qMRjhKkZGo;
      string TpMeqAgVdH;
      string tomOgirxpB;
      string XLJIUBMBan;
      string YaTmrfwCmK;
      string XlNYlBZCDz;
      string SniFRIfDJp;
      string nftohTVAVA;
      string moJfckxkWS;
      string aJxbUkqOVj;
      string zrsxVrrXpR;
      string fYfDLceDbf;
      if(SWpRTpVZij == tomOgirxpB){KufpOdhSUx = true;}
      else if(tomOgirxpB == SWpRTpVZij){DFhGimoZPU = true;}
      if(XbmxiEJYjp == XLJIUBMBan){bHelAtwLJk = true;}
      else if(XLJIUBMBan == XbmxiEJYjp){NzLnFRwDRD = true;}
      if(YlUzbHbrnZ == YaTmrfwCmK){rZtEmBctPq = true;}
      else if(YaTmrfwCmK == YlUzbHbrnZ){sZnXsuuGcE = true;}
      if(jMaMUWhBqF == XlNYlBZCDz){GnloZEMCiq = true;}
      else if(XlNYlBZCDz == jMaMUWhBqF){uuzMLBBjPX = true;}
      if(eTecSuPPaD == SniFRIfDJp){JZDspXttCQ = true;}
      else if(SniFRIfDJp == eTecSuPPaD){yTfgaDZKQY = true;}
      if(qYbBGfCqoM == nftohTVAVA){gSspmjBaDM = true;}
      else if(nftohTVAVA == qYbBGfCqoM){aUIxIcRKNm = true;}
      if(OdlJzKAZbM == moJfckxkWS){BmCcqnUoMw = true;}
      else if(moJfckxkWS == OdlJzKAZbM){rixKZSAzbD = true;}
      if(WIgdKFHqgf == aJxbUkqOVj){htcSaSVBOO = true;}
      if(qMRjhKkZGo == zrsxVrrXpR){HiqzKmtuBo = true;}
      if(TpMeqAgVdH == fYfDLceDbf){DlzWpWXaBC = true;}
      while(aJxbUkqOVj == WIgdKFHqgf){PLmtFYsGwo = true;}
      while(zrsxVrrXpR == zrsxVrrXpR){VjoEdZmBDh = true;}
      while(fYfDLceDbf == fYfDLceDbf){jqWbfOVUGI = true;}
      if(KufpOdhSUx == true){KufpOdhSUx = false;}
      if(bHelAtwLJk == true){bHelAtwLJk = false;}
      if(rZtEmBctPq == true){rZtEmBctPq = false;}
      if(GnloZEMCiq == true){GnloZEMCiq = false;}
      if(JZDspXttCQ == true){JZDspXttCQ = false;}
      if(gSspmjBaDM == true){gSspmjBaDM = false;}
      if(BmCcqnUoMw == true){BmCcqnUoMw = false;}
      if(htcSaSVBOO == true){htcSaSVBOO = false;}
      if(HiqzKmtuBo == true){HiqzKmtuBo = false;}
      if(DlzWpWXaBC == true){DlzWpWXaBC = false;}
      if(DFhGimoZPU == true){DFhGimoZPU = false;}
      if(NzLnFRwDRD == true){NzLnFRwDRD = false;}
      if(sZnXsuuGcE == true){sZnXsuuGcE = false;}
      if(uuzMLBBjPX == true){uuzMLBBjPX = false;}
      if(yTfgaDZKQY == true){yTfgaDZKQY = false;}
      if(aUIxIcRKNm == true){aUIxIcRKNm = false;}
      if(rixKZSAzbD == true){rixKZSAzbD = false;}
      if(PLmtFYsGwo == true){PLmtFYsGwo = false;}
      if(VjoEdZmBDh == true){VjoEdZmBDh = false;}
      if(jqWbfOVUGI == true){jqWbfOVUGI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNJYSHORJQ
{ 
  void SRhOrBrdtR()
  { 
      bool hxtYulLGuL = false;
      bool oxOWzPDMwY = false;
      bool xzppozoCJT = false;
      bool EpkuxWEbYs = false;
      bool TcJOjwnCdY = false;
      bool tGHNshGDju = false;
      bool wIwbHyMSYb = false;
      bool LamDFTpbGr = false;
      bool KlYjYyhWCP = false;
      bool QArdwKfgGk = false;
      bool jVcBMSSEIY = false;
      bool qexqkKjMCJ = false;
      bool QoPJLLiJGt = false;
      bool mIUVIoIXWG = false;
      bool edOcXkCBsl = false;
      bool aTdxTtFToB = false;
      bool iIxNkiJahu = false;
      bool BLpwdmamkZ = false;
      bool IhQTTTdWBO = false;
      bool johVWVfAqo = false;
      string IhGUfwnGYe;
      string tcfQJPKeqG;
      string tnMHhbbycr;
      string wTRsMfoTMW;
      string hzpOkSYNzc;
      string OgTeXTVylD;
      string TpdgiaLlDd;
      string ZpSUXtyyWP;
      string DOyAcPAlVs;
      string KpgICrVJfK;
      string HmKVCXNzGc;
      string VXbWAFqdDS;
      string ZYQJSiIJRf;
      string XoRLHQDcxE;
      string BBerWmNKIx;
      string ArFMkiVACT;
      string OEgaFgFQPi;
      string COfzQYsXlf;
      string UyAUefiFaY;
      string tCZcoxTDmp;
      if(IhGUfwnGYe == HmKVCXNzGc){hxtYulLGuL = true;}
      else if(HmKVCXNzGc == IhGUfwnGYe){jVcBMSSEIY = true;}
      if(tcfQJPKeqG == VXbWAFqdDS){oxOWzPDMwY = true;}
      else if(VXbWAFqdDS == tcfQJPKeqG){qexqkKjMCJ = true;}
      if(tnMHhbbycr == ZYQJSiIJRf){xzppozoCJT = true;}
      else if(ZYQJSiIJRf == tnMHhbbycr){QoPJLLiJGt = true;}
      if(wTRsMfoTMW == XoRLHQDcxE){EpkuxWEbYs = true;}
      else if(XoRLHQDcxE == wTRsMfoTMW){mIUVIoIXWG = true;}
      if(hzpOkSYNzc == BBerWmNKIx){TcJOjwnCdY = true;}
      else if(BBerWmNKIx == hzpOkSYNzc){edOcXkCBsl = true;}
      if(OgTeXTVylD == ArFMkiVACT){tGHNshGDju = true;}
      else if(ArFMkiVACT == OgTeXTVylD){aTdxTtFToB = true;}
      if(TpdgiaLlDd == OEgaFgFQPi){wIwbHyMSYb = true;}
      else if(OEgaFgFQPi == TpdgiaLlDd){iIxNkiJahu = true;}
      if(ZpSUXtyyWP == COfzQYsXlf){LamDFTpbGr = true;}
      if(DOyAcPAlVs == UyAUefiFaY){KlYjYyhWCP = true;}
      if(KpgICrVJfK == tCZcoxTDmp){QArdwKfgGk = true;}
      while(COfzQYsXlf == ZpSUXtyyWP){BLpwdmamkZ = true;}
      while(UyAUefiFaY == UyAUefiFaY){IhQTTTdWBO = true;}
      while(tCZcoxTDmp == tCZcoxTDmp){johVWVfAqo = true;}
      if(hxtYulLGuL == true){hxtYulLGuL = false;}
      if(oxOWzPDMwY == true){oxOWzPDMwY = false;}
      if(xzppozoCJT == true){xzppozoCJT = false;}
      if(EpkuxWEbYs == true){EpkuxWEbYs = false;}
      if(TcJOjwnCdY == true){TcJOjwnCdY = false;}
      if(tGHNshGDju == true){tGHNshGDju = false;}
      if(wIwbHyMSYb == true){wIwbHyMSYb = false;}
      if(LamDFTpbGr == true){LamDFTpbGr = false;}
      if(KlYjYyhWCP == true){KlYjYyhWCP = false;}
      if(QArdwKfgGk == true){QArdwKfgGk = false;}
      if(jVcBMSSEIY == true){jVcBMSSEIY = false;}
      if(qexqkKjMCJ == true){qexqkKjMCJ = false;}
      if(QoPJLLiJGt == true){QoPJLLiJGt = false;}
      if(mIUVIoIXWG == true){mIUVIoIXWG = false;}
      if(edOcXkCBsl == true){edOcXkCBsl = false;}
      if(aTdxTtFToB == true){aTdxTtFToB = false;}
      if(iIxNkiJahu == true){iIxNkiJahu = false;}
      if(BLpwdmamkZ == true){BLpwdmamkZ = false;}
      if(IhQTTTdWBO == true){IhQTTTdWBO = false;}
      if(johVWVfAqo == true){johVWVfAqo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYQTJXLSBQ
{ 
  void dRzckKrgeq()
  { 
      bool IdATZrZASM = false;
      bool tjbauaHaYt = false;
      bool csWwpzfQkZ = false;
      bool nhpDJZSbor = false;
      bool AAOSbUYzlA = false;
      bool NMKSsPGEca = false;
      bool MJOsXLtYQU = false;
      bool HflftbeDTV = false;
      bool ZfdkLbWWKt = false;
      bool SOyOfqlVtQ = false;
      bool ZAhQrhZeYQ = false;
      bool kDjGAfedgw = false;
      bool nWNVBsgXzC = false;
      bool pIJDuZyMrd = false;
      bool BrxtJPdqNA = false;
      bool LHnycDlLPz = false;
      bool ACfVZbtgLa = false;
      bool gRlDtwYTMl = false;
      bool OoJzpiUKar = false;
      bool nlxrczMbUh = false;
      string KYJkgPQkrY;
      string ZjHYTZoWhV;
      string DCWYbbeYnA;
      string PJlVCJmeIO;
      string OBoqKVKzHW;
      string tbzzVHCjIF;
      string jqxqIPxkVK;
      string mKNTGCNeOG;
      string RfRRGmKlAu;
      string HCVDdXEyit;
      string XYcxjjOfrS;
      string tWVBnDZfjU;
      string FLkaDjnKoi;
      string yPwTirDTgW;
      string YdsgAjfTOZ;
      string yXNOnMmCtz;
      string uDpJTeaCSu;
      string AFyNubRDZS;
      string ETuOkZBheW;
      string EBZhbVmjNV;
      if(KYJkgPQkrY == XYcxjjOfrS){IdATZrZASM = true;}
      else if(XYcxjjOfrS == KYJkgPQkrY){ZAhQrhZeYQ = true;}
      if(ZjHYTZoWhV == tWVBnDZfjU){tjbauaHaYt = true;}
      else if(tWVBnDZfjU == ZjHYTZoWhV){kDjGAfedgw = true;}
      if(DCWYbbeYnA == FLkaDjnKoi){csWwpzfQkZ = true;}
      else if(FLkaDjnKoi == DCWYbbeYnA){nWNVBsgXzC = true;}
      if(PJlVCJmeIO == yPwTirDTgW){nhpDJZSbor = true;}
      else if(yPwTirDTgW == PJlVCJmeIO){pIJDuZyMrd = true;}
      if(OBoqKVKzHW == YdsgAjfTOZ){AAOSbUYzlA = true;}
      else if(YdsgAjfTOZ == OBoqKVKzHW){BrxtJPdqNA = true;}
      if(tbzzVHCjIF == yXNOnMmCtz){NMKSsPGEca = true;}
      else if(yXNOnMmCtz == tbzzVHCjIF){LHnycDlLPz = true;}
      if(jqxqIPxkVK == uDpJTeaCSu){MJOsXLtYQU = true;}
      else if(uDpJTeaCSu == jqxqIPxkVK){ACfVZbtgLa = true;}
      if(mKNTGCNeOG == AFyNubRDZS){HflftbeDTV = true;}
      if(RfRRGmKlAu == ETuOkZBheW){ZfdkLbWWKt = true;}
      if(HCVDdXEyit == EBZhbVmjNV){SOyOfqlVtQ = true;}
      while(AFyNubRDZS == mKNTGCNeOG){gRlDtwYTMl = true;}
      while(ETuOkZBheW == ETuOkZBheW){OoJzpiUKar = true;}
      while(EBZhbVmjNV == EBZhbVmjNV){nlxrczMbUh = true;}
      if(IdATZrZASM == true){IdATZrZASM = false;}
      if(tjbauaHaYt == true){tjbauaHaYt = false;}
      if(csWwpzfQkZ == true){csWwpzfQkZ = false;}
      if(nhpDJZSbor == true){nhpDJZSbor = false;}
      if(AAOSbUYzlA == true){AAOSbUYzlA = false;}
      if(NMKSsPGEca == true){NMKSsPGEca = false;}
      if(MJOsXLtYQU == true){MJOsXLtYQU = false;}
      if(HflftbeDTV == true){HflftbeDTV = false;}
      if(ZfdkLbWWKt == true){ZfdkLbWWKt = false;}
      if(SOyOfqlVtQ == true){SOyOfqlVtQ = false;}
      if(ZAhQrhZeYQ == true){ZAhQrhZeYQ = false;}
      if(kDjGAfedgw == true){kDjGAfedgw = false;}
      if(nWNVBsgXzC == true){nWNVBsgXzC = false;}
      if(pIJDuZyMrd == true){pIJDuZyMrd = false;}
      if(BrxtJPdqNA == true){BrxtJPdqNA = false;}
      if(LHnycDlLPz == true){LHnycDlLPz = false;}
      if(ACfVZbtgLa == true){ACfVZbtgLa = false;}
      if(gRlDtwYTMl == true){gRlDtwYTMl = false;}
      if(OoJzpiUKar == true){OoJzpiUKar = false;}
      if(nlxrczMbUh == true){nlxrczMbUh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXFWLHSVKU
{ 
  void zmULIDrfwI()
  { 
      bool QmoFHXetUn = false;
      bool PgDabEoEGi = false;
      bool VCjnDiuBtp = false;
      bool jUncqPIFHj = false;
      bool UkEFSxeAiH = false;
      bool uFGZWNDBCX = false;
      bool bcAdEurZiL = false;
      bool wjxWOkyeVF = false;
      bool DtRmtdOOGd = false;
      bool MGCiHqkZAW = false;
      bool EFQXLLHjLl = false;
      bool PYewUhLNia = false;
      bool gdTFzogOOW = false;
      bool AXdyAydtbi = false;
      bool VeCUOmbFNZ = false;
      bool fWqZpakLXV = false;
      bool esUnlquguV = false;
      bool DQlAECaypL = false;
      bool MaBoqcfDHZ = false;
      bool MRVFEcJOiW = false;
      string uNuwXuxkKP;
      string oqnxDJnYEi;
      string hNmDBFZTmP;
      string PenfHOPLwS;
      string FtOJSLbdYt;
      string ocsuNgZqtS;
      string UcxtAKCHpo;
      string sbcldnzdkp;
      string cuusalkrRa;
      string nXRcybwTJH;
      string ITnjBMAHQZ;
      string gwGEpYhETN;
      string YKoPAUKzmC;
      string qfUcgIHKqN;
      string ldbrsrRMmY;
      string trAuiydYif;
      string CBTOiBbdWg;
      string RWMFathxVI;
      string DxLOHzeYsi;
      string dhbLLkKNJr;
      if(uNuwXuxkKP == ITnjBMAHQZ){QmoFHXetUn = true;}
      else if(ITnjBMAHQZ == uNuwXuxkKP){EFQXLLHjLl = true;}
      if(oqnxDJnYEi == gwGEpYhETN){PgDabEoEGi = true;}
      else if(gwGEpYhETN == oqnxDJnYEi){PYewUhLNia = true;}
      if(hNmDBFZTmP == YKoPAUKzmC){VCjnDiuBtp = true;}
      else if(YKoPAUKzmC == hNmDBFZTmP){gdTFzogOOW = true;}
      if(PenfHOPLwS == qfUcgIHKqN){jUncqPIFHj = true;}
      else if(qfUcgIHKqN == PenfHOPLwS){AXdyAydtbi = true;}
      if(FtOJSLbdYt == ldbrsrRMmY){UkEFSxeAiH = true;}
      else if(ldbrsrRMmY == FtOJSLbdYt){VeCUOmbFNZ = true;}
      if(ocsuNgZqtS == trAuiydYif){uFGZWNDBCX = true;}
      else if(trAuiydYif == ocsuNgZqtS){fWqZpakLXV = true;}
      if(UcxtAKCHpo == CBTOiBbdWg){bcAdEurZiL = true;}
      else if(CBTOiBbdWg == UcxtAKCHpo){esUnlquguV = true;}
      if(sbcldnzdkp == RWMFathxVI){wjxWOkyeVF = true;}
      if(cuusalkrRa == DxLOHzeYsi){DtRmtdOOGd = true;}
      if(nXRcybwTJH == dhbLLkKNJr){MGCiHqkZAW = true;}
      while(RWMFathxVI == sbcldnzdkp){DQlAECaypL = true;}
      while(DxLOHzeYsi == DxLOHzeYsi){MaBoqcfDHZ = true;}
      while(dhbLLkKNJr == dhbLLkKNJr){MRVFEcJOiW = true;}
      if(QmoFHXetUn == true){QmoFHXetUn = false;}
      if(PgDabEoEGi == true){PgDabEoEGi = false;}
      if(VCjnDiuBtp == true){VCjnDiuBtp = false;}
      if(jUncqPIFHj == true){jUncqPIFHj = false;}
      if(UkEFSxeAiH == true){UkEFSxeAiH = false;}
      if(uFGZWNDBCX == true){uFGZWNDBCX = false;}
      if(bcAdEurZiL == true){bcAdEurZiL = false;}
      if(wjxWOkyeVF == true){wjxWOkyeVF = false;}
      if(DtRmtdOOGd == true){DtRmtdOOGd = false;}
      if(MGCiHqkZAW == true){MGCiHqkZAW = false;}
      if(EFQXLLHjLl == true){EFQXLLHjLl = false;}
      if(PYewUhLNia == true){PYewUhLNia = false;}
      if(gdTFzogOOW == true){gdTFzogOOW = false;}
      if(AXdyAydtbi == true){AXdyAydtbi = false;}
      if(VeCUOmbFNZ == true){VeCUOmbFNZ = false;}
      if(fWqZpakLXV == true){fWqZpakLXV = false;}
      if(esUnlquguV == true){esUnlquguV = false;}
      if(DQlAECaypL == true){DQlAECaypL = false;}
      if(MaBoqcfDHZ == true){MaBoqcfDHZ = false;}
      if(MRVFEcJOiW == true){MRVFEcJOiW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXDUZWUGUV
{ 
  void AYOhZkNWQa()
  { 
      bool nZizRxnoGO = false;
      bool dIwDXtoIEb = false;
      bool ldOcOLfIhL = false;
      bool rbfTYaZirg = false;
      bool EHZYYjZNxd = false;
      bool QPueNKKGkF = false;
      bool RfGuWBbcdx = false;
      bool TGPXWdEpDd = false;
      bool lRKEtbgBFO = false;
      bool PTymPYBdBW = false;
      bool IxiAJKzWIi = false;
      bool FUCGSzUCAt = false;
      bool UaWOgAIcIy = false;
      bool cZngVoiKtj = false;
      bool bJrVIuQqTP = false;
      bool EydHBhZUTJ = false;
      bool BWOKFffVkd = false;
      bool QKIQSLhAFk = false;
      bool iQJrteugem = false;
      bool ONqjhFthQb = false;
      string whoEYUwyww;
      string CqGfdtqucG;
      string QtpQpdrJaH;
      string EbqlOETQAx;
      string KOUOMQekAc;
      string CKHCfCqXNu;
      string bmXnrazTQY;
      string ZaueuBYbDZ;
      string zHIyEtToFM;
      string NwCEUXqfWl;
      string QKUbDbOcGe;
      string cPTnwUdYjx;
      string HKODLcXpJX;
      string KsFRInmguc;
      string eqiajybOHA;
      string sRwYeFuQQZ;
      string DXSiTiJCeH;
      string hwdGSQbmTM;
      string BJiJdrxfmC;
      string sVQVYGXzGA;
      if(whoEYUwyww == QKUbDbOcGe){nZizRxnoGO = true;}
      else if(QKUbDbOcGe == whoEYUwyww){IxiAJKzWIi = true;}
      if(CqGfdtqucG == cPTnwUdYjx){dIwDXtoIEb = true;}
      else if(cPTnwUdYjx == CqGfdtqucG){FUCGSzUCAt = true;}
      if(QtpQpdrJaH == HKODLcXpJX){ldOcOLfIhL = true;}
      else if(HKODLcXpJX == QtpQpdrJaH){UaWOgAIcIy = true;}
      if(EbqlOETQAx == KsFRInmguc){rbfTYaZirg = true;}
      else if(KsFRInmguc == EbqlOETQAx){cZngVoiKtj = true;}
      if(KOUOMQekAc == eqiajybOHA){EHZYYjZNxd = true;}
      else if(eqiajybOHA == KOUOMQekAc){bJrVIuQqTP = true;}
      if(CKHCfCqXNu == sRwYeFuQQZ){QPueNKKGkF = true;}
      else if(sRwYeFuQQZ == CKHCfCqXNu){EydHBhZUTJ = true;}
      if(bmXnrazTQY == DXSiTiJCeH){RfGuWBbcdx = true;}
      else if(DXSiTiJCeH == bmXnrazTQY){BWOKFffVkd = true;}
      if(ZaueuBYbDZ == hwdGSQbmTM){TGPXWdEpDd = true;}
      if(zHIyEtToFM == BJiJdrxfmC){lRKEtbgBFO = true;}
      if(NwCEUXqfWl == sVQVYGXzGA){PTymPYBdBW = true;}
      while(hwdGSQbmTM == ZaueuBYbDZ){QKIQSLhAFk = true;}
      while(BJiJdrxfmC == BJiJdrxfmC){iQJrteugem = true;}
      while(sVQVYGXzGA == sVQVYGXzGA){ONqjhFthQb = true;}
      if(nZizRxnoGO == true){nZizRxnoGO = false;}
      if(dIwDXtoIEb == true){dIwDXtoIEb = false;}
      if(ldOcOLfIhL == true){ldOcOLfIhL = false;}
      if(rbfTYaZirg == true){rbfTYaZirg = false;}
      if(EHZYYjZNxd == true){EHZYYjZNxd = false;}
      if(QPueNKKGkF == true){QPueNKKGkF = false;}
      if(RfGuWBbcdx == true){RfGuWBbcdx = false;}
      if(TGPXWdEpDd == true){TGPXWdEpDd = false;}
      if(lRKEtbgBFO == true){lRKEtbgBFO = false;}
      if(PTymPYBdBW == true){PTymPYBdBW = false;}
      if(IxiAJKzWIi == true){IxiAJKzWIi = false;}
      if(FUCGSzUCAt == true){FUCGSzUCAt = false;}
      if(UaWOgAIcIy == true){UaWOgAIcIy = false;}
      if(cZngVoiKtj == true){cZngVoiKtj = false;}
      if(bJrVIuQqTP == true){bJrVIuQqTP = false;}
      if(EydHBhZUTJ == true){EydHBhZUTJ = false;}
      if(BWOKFffVkd == true){BWOKFffVkd = false;}
      if(QKIQSLhAFk == true){QKIQSLhAFk = false;}
      if(iQJrteugem == true){iQJrteugem = false;}
      if(ONqjhFthQb == true){ONqjhFthQb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCDFIIYOFE
{ 
  void WhiTHJPuWZ()
  { 
      bool tiKPhFgYCW = false;
      bool YMcfzByLKF = false;
      bool qRyAWbSwrX = false;
      bool IcFEHduROL = false;
      bool aSpRbaiPDC = false;
      bool gwDhdckJsG = false;
      bool lkfdOuHYXU = false;
      bool GgwyeYagXw = false;
      bool rDsoqMZXZe = false;
      bool skXIZplLCf = false;
      bool TKrhwzzECE = false;
      bool CElxOirpmC = false;
      bool ViysbUInYo = false;
      bool mOdqcgKKrq = false;
      bool MVUUcnzasp = false;
      bool yuYAKjLyGb = false;
      bool qKeNRmatUg = false;
      bool XgywoANcPm = false;
      bool Uhuipqodgr = false;
      bool VLDPzCpHDo = false;
      string FgEfzRrEyr;
      string wNfTJTCTce;
      string xRFsAxNdeD;
      string bUYhnoxIgf;
      string cRZkwlAOJS;
      string SaZRfnbLfC;
      string ENZtPaoxeT;
      string VtmwCfrTwN;
      string xzTLkAtGCA;
      string MkcebOreUU;
      string xCioxYndPA;
      string uIOREEtNJP;
      string ghueGjQHUm;
      string mMybQtQeOM;
      string LQqBEEVLZW;
      string UeVFmPGDhM;
      string HfIcNiJmBK;
      string nPyxDPqsZC;
      string NFhxRHqroA;
      string mMwCEfHNnV;
      if(FgEfzRrEyr == xCioxYndPA){tiKPhFgYCW = true;}
      else if(xCioxYndPA == FgEfzRrEyr){TKrhwzzECE = true;}
      if(wNfTJTCTce == uIOREEtNJP){YMcfzByLKF = true;}
      else if(uIOREEtNJP == wNfTJTCTce){CElxOirpmC = true;}
      if(xRFsAxNdeD == ghueGjQHUm){qRyAWbSwrX = true;}
      else if(ghueGjQHUm == xRFsAxNdeD){ViysbUInYo = true;}
      if(bUYhnoxIgf == mMybQtQeOM){IcFEHduROL = true;}
      else if(mMybQtQeOM == bUYhnoxIgf){mOdqcgKKrq = true;}
      if(cRZkwlAOJS == LQqBEEVLZW){aSpRbaiPDC = true;}
      else if(LQqBEEVLZW == cRZkwlAOJS){MVUUcnzasp = true;}
      if(SaZRfnbLfC == UeVFmPGDhM){gwDhdckJsG = true;}
      else if(UeVFmPGDhM == SaZRfnbLfC){yuYAKjLyGb = true;}
      if(ENZtPaoxeT == HfIcNiJmBK){lkfdOuHYXU = true;}
      else if(HfIcNiJmBK == ENZtPaoxeT){qKeNRmatUg = true;}
      if(VtmwCfrTwN == nPyxDPqsZC){GgwyeYagXw = true;}
      if(xzTLkAtGCA == NFhxRHqroA){rDsoqMZXZe = true;}
      if(MkcebOreUU == mMwCEfHNnV){skXIZplLCf = true;}
      while(nPyxDPqsZC == VtmwCfrTwN){XgywoANcPm = true;}
      while(NFhxRHqroA == NFhxRHqroA){Uhuipqodgr = true;}
      while(mMwCEfHNnV == mMwCEfHNnV){VLDPzCpHDo = true;}
      if(tiKPhFgYCW == true){tiKPhFgYCW = false;}
      if(YMcfzByLKF == true){YMcfzByLKF = false;}
      if(qRyAWbSwrX == true){qRyAWbSwrX = false;}
      if(IcFEHduROL == true){IcFEHduROL = false;}
      if(aSpRbaiPDC == true){aSpRbaiPDC = false;}
      if(gwDhdckJsG == true){gwDhdckJsG = false;}
      if(lkfdOuHYXU == true){lkfdOuHYXU = false;}
      if(GgwyeYagXw == true){GgwyeYagXw = false;}
      if(rDsoqMZXZe == true){rDsoqMZXZe = false;}
      if(skXIZplLCf == true){skXIZplLCf = false;}
      if(TKrhwzzECE == true){TKrhwzzECE = false;}
      if(CElxOirpmC == true){CElxOirpmC = false;}
      if(ViysbUInYo == true){ViysbUInYo = false;}
      if(mOdqcgKKrq == true){mOdqcgKKrq = false;}
      if(MVUUcnzasp == true){MVUUcnzasp = false;}
      if(yuYAKjLyGb == true){yuYAKjLyGb = false;}
      if(qKeNRmatUg == true){qKeNRmatUg = false;}
      if(XgywoANcPm == true){XgywoANcPm = false;}
      if(Uhuipqodgr == true){Uhuipqodgr = false;}
      if(VLDPzCpHDo == true){VLDPzCpHDo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKLUEVCKAY
{ 
  void ahdGoIdhIO()
  { 
      bool KwuQXhcsyG = false;
      bool mhkIjtWXIN = false;
      bool kBOUBhRkYl = false;
      bool LVVjmfbPZa = false;
      bool MhZiccDkaP = false;
      bool VgfhsJhZPp = false;
      bool PqTMuRLBUE = false;
      bool RHyhACaerX = false;
      bool efJJPdomqd = false;
      bool yCAiLUNMnK = false;
      bool RCQWxOiygp = false;
      bool hCgqLihKwQ = false;
      bool cXKqGOGOVf = false;
      bool oOqhGbPlMB = false;
      bool uqFAuuUIXb = false;
      bool mDPWhsrYQi = false;
      bool HUbBATKzki = false;
      bool SuxtVkRJuK = false;
      bool syqsrlyUzN = false;
      bool jpVctaPDza = false;
      string ricKQTtuLc;
      string pAYbwUtKNg;
      string rkzdhTMjIE;
      string nHIsOxTIyN;
      string ThtrzFtSpr;
      string HbPhcHjybw;
      string GJlHniqfMy;
      string AkMAMKqGec;
      string YttQxMqaPH;
      string NVgBGJulEP;
      string OOFrqVPPUR;
      string QcTzWLOVJa;
      string rQPFjeEKsD;
      string OECOOKoCYa;
      string xaGypkBgdu;
      string tZccXxzAHM;
      string REVRCMZFkM;
      string WMwidQKQOy;
      string cXgyIobYpQ;
      string LotLJrFnud;
      if(ricKQTtuLc == OOFrqVPPUR){KwuQXhcsyG = true;}
      else if(OOFrqVPPUR == ricKQTtuLc){RCQWxOiygp = true;}
      if(pAYbwUtKNg == QcTzWLOVJa){mhkIjtWXIN = true;}
      else if(QcTzWLOVJa == pAYbwUtKNg){hCgqLihKwQ = true;}
      if(rkzdhTMjIE == rQPFjeEKsD){kBOUBhRkYl = true;}
      else if(rQPFjeEKsD == rkzdhTMjIE){cXKqGOGOVf = true;}
      if(nHIsOxTIyN == OECOOKoCYa){LVVjmfbPZa = true;}
      else if(OECOOKoCYa == nHIsOxTIyN){oOqhGbPlMB = true;}
      if(ThtrzFtSpr == xaGypkBgdu){MhZiccDkaP = true;}
      else if(xaGypkBgdu == ThtrzFtSpr){uqFAuuUIXb = true;}
      if(HbPhcHjybw == tZccXxzAHM){VgfhsJhZPp = true;}
      else if(tZccXxzAHM == HbPhcHjybw){mDPWhsrYQi = true;}
      if(GJlHniqfMy == REVRCMZFkM){PqTMuRLBUE = true;}
      else if(REVRCMZFkM == GJlHniqfMy){HUbBATKzki = true;}
      if(AkMAMKqGec == WMwidQKQOy){RHyhACaerX = true;}
      if(YttQxMqaPH == cXgyIobYpQ){efJJPdomqd = true;}
      if(NVgBGJulEP == LotLJrFnud){yCAiLUNMnK = true;}
      while(WMwidQKQOy == AkMAMKqGec){SuxtVkRJuK = true;}
      while(cXgyIobYpQ == cXgyIobYpQ){syqsrlyUzN = true;}
      while(LotLJrFnud == LotLJrFnud){jpVctaPDza = true;}
      if(KwuQXhcsyG == true){KwuQXhcsyG = false;}
      if(mhkIjtWXIN == true){mhkIjtWXIN = false;}
      if(kBOUBhRkYl == true){kBOUBhRkYl = false;}
      if(LVVjmfbPZa == true){LVVjmfbPZa = false;}
      if(MhZiccDkaP == true){MhZiccDkaP = false;}
      if(VgfhsJhZPp == true){VgfhsJhZPp = false;}
      if(PqTMuRLBUE == true){PqTMuRLBUE = false;}
      if(RHyhACaerX == true){RHyhACaerX = false;}
      if(efJJPdomqd == true){efJJPdomqd = false;}
      if(yCAiLUNMnK == true){yCAiLUNMnK = false;}
      if(RCQWxOiygp == true){RCQWxOiygp = false;}
      if(hCgqLihKwQ == true){hCgqLihKwQ = false;}
      if(cXKqGOGOVf == true){cXKqGOGOVf = false;}
      if(oOqhGbPlMB == true){oOqhGbPlMB = false;}
      if(uqFAuuUIXb == true){uqFAuuUIXb = false;}
      if(mDPWhsrYQi == true){mDPWhsrYQi = false;}
      if(HUbBATKzki == true){HUbBATKzki = false;}
      if(SuxtVkRJuK == true){SuxtVkRJuK = false;}
      if(syqsrlyUzN == true){syqsrlyUzN = false;}
      if(jpVctaPDza == true){jpVctaPDza = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IEYATJBNDJ
{ 
  void VxMIBmQJqX()
  { 
      bool NRsdRYUdrV = false;
      bool hMgLrnOuTj = false;
      bool EzwyfbUQko = false;
      bool LQfIXIVQlg = false;
      bool wiuhyldIzT = false;
      bool gwdOoNUtyp = false;
      bool DDsDKQfXni = false;
      bool SxImmUEOAs = false;
      bool xMQQIOlRTJ = false;
      bool nbSucrpqWg = false;
      bool GFUQBinqaT = false;
      bool JGsEspmbuu = false;
      bool dNEdtqeMJt = false;
      bool eNqTmqrzPY = false;
      bool auqAAghNCl = false;
      bool FOwbCrBpVJ = false;
      bool DahfnwPYRB = false;
      bool ymLVUiWEdN = false;
      bool IQJXnQQPRt = false;
      bool pCdFUzNLLE = false;
      string TsmZwCkQZX;
      string ByRMhOcuNO;
      string gBHLBNYdZQ;
      string PGunhpYGMQ;
      string bnmZOlAdbC;
      string MwGfpRlbXh;
      string cHqJHtCder;
      string pVhxmsOhxO;
      string MtBWDSAPxP;
      string EwhdmTxcRT;
      string jWzjMqNIrx;
      string DDdJUhGTFo;
      string tlfOmsmEJS;
      string ukPcdpuQKM;
      string EqWAMBSYJF;
      string NdXcYxqjxS;
      string DJzYBRmAee;
      string moIsjDPeCk;
      string aOuEFRNmEf;
      string yLTrIuqyyt;
      if(TsmZwCkQZX == jWzjMqNIrx){NRsdRYUdrV = true;}
      else if(jWzjMqNIrx == TsmZwCkQZX){GFUQBinqaT = true;}
      if(ByRMhOcuNO == DDdJUhGTFo){hMgLrnOuTj = true;}
      else if(DDdJUhGTFo == ByRMhOcuNO){JGsEspmbuu = true;}
      if(gBHLBNYdZQ == tlfOmsmEJS){EzwyfbUQko = true;}
      else if(tlfOmsmEJS == gBHLBNYdZQ){dNEdtqeMJt = true;}
      if(PGunhpYGMQ == ukPcdpuQKM){LQfIXIVQlg = true;}
      else if(ukPcdpuQKM == PGunhpYGMQ){eNqTmqrzPY = true;}
      if(bnmZOlAdbC == EqWAMBSYJF){wiuhyldIzT = true;}
      else if(EqWAMBSYJF == bnmZOlAdbC){auqAAghNCl = true;}
      if(MwGfpRlbXh == NdXcYxqjxS){gwdOoNUtyp = true;}
      else if(NdXcYxqjxS == MwGfpRlbXh){FOwbCrBpVJ = true;}
      if(cHqJHtCder == DJzYBRmAee){DDsDKQfXni = true;}
      else if(DJzYBRmAee == cHqJHtCder){DahfnwPYRB = true;}
      if(pVhxmsOhxO == moIsjDPeCk){SxImmUEOAs = true;}
      if(MtBWDSAPxP == aOuEFRNmEf){xMQQIOlRTJ = true;}
      if(EwhdmTxcRT == yLTrIuqyyt){nbSucrpqWg = true;}
      while(moIsjDPeCk == pVhxmsOhxO){ymLVUiWEdN = true;}
      while(aOuEFRNmEf == aOuEFRNmEf){IQJXnQQPRt = true;}
      while(yLTrIuqyyt == yLTrIuqyyt){pCdFUzNLLE = true;}
      if(NRsdRYUdrV == true){NRsdRYUdrV = false;}
      if(hMgLrnOuTj == true){hMgLrnOuTj = false;}
      if(EzwyfbUQko == true){EzwyfbUQko = false;}
      if(LQfIXIVQlg == true){LQfIXIVQlg = false;}
      if(wiuhyldIzT == true){wiuhyldIzT = false;}
      if(gwdOoNUtyp == true){gwdOoNUtyp = false;}
      if(DDsDKQfXni == true){DDsDKQfXni = false;}
      if(SxImmUEOAs == true){SxImmUEOAs = false;}
      if(xMQQIOlRTJ == true){xMQQIOlRTJ = false;}
      if(nbSucrpqWg == true){nbSucrpqWg = false;}
      if(GFUQBinqaT == true){GFUQBinqaT = false;}
      if(JGsEspmbuu == true){JGsEspmbuu = false;}
      if(dNEdtqeMJt == true){dNEdtqeMJt = false;}
      if(eNqTmqrzPY == true){eNqTmqrzPY = false;}
      if(auqAAghNCl == true){auqAAghNCl = false;}
      if(FOwbCrBpVJ == true){FOwbCrBpVJ = false;}
      if(DahfnwPYRB == true){DahfnwPYRB = false;}
      if(ymLVUiWEdN == true){ymLVUiWEdN = false;}
      if(IQJXnQQPRt == true){IQJXnQQPRt = false;}
      if(pCdFUzNLLE == true){pCdFUzNLLE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCEVKISDOK
{ 
  void OxibPmNWUI()
  { 
      bool YmtRiurYTO = false;
      bool nEKVcFhzbj = false;
      bool ohwKgsNrdP = false;
      bool qfKZdAqVuJ = false;
      bool FRqnFkAsML = false;
      bool HFGMkppjjo = false;
      bool gztDXHskrb = false;
      bool NMEReWqIEu = false;
      bool sTfRHlZxnn = false;
      bool JHkFbFWmQx = false;
      bool qPBjyuBnhN = false;
      bool zheowMScwk = false;
      bool hwwDRFbypZ = false;
      bool zDqHDcSwTM = false;
      bool jlPZobcuIO = false;
      bool ltqePuSxRr = false;
      bool SCyIOupWlS = false;
      bool tWJjBufVOp = false;
      bool cfoamFLMqH = false;
      bool KUdasgnHLs = false;
      string eFYDtXByxS;
      string PXyaYxXVKV;
      string gDxEUWIyPE;
      string qGPaXFVjid;
      string xwSTzoVTNS;
      string QhblpaIThX;
      string ODisaIHXCS;
      string bmlgYkkcFe;
      string AnjwmIdcjw;
      string xBBLOsMZrp;
      string hyRtqdwuNF;
      string peOCXaTmFS;
      string edmGVakaRf;
      string XKkOxBWoFJ;
      string MhPeFSmzmm;
      string ZZTZLDLKYP;
      string rVchheszEV;
      string EdhuGwOHAC;
      string mlmdFxpLDt;
      string oLPoRpEhxZ;
      if(eFYDtXByxS == hyRtqdwuNF){YmtRiurYTO = true;}
      else if(hyRtqdwuNF == eFYDtXByxS){qPBjyuBnhN = true;}
      if(PXyaYxXVKV == peOCXaTmFS){nEKVcFhzbj = true;}
      else if(peOCXaTmFS == PXyaYxXVKV){zheowMScwk = true;}
      if(gDxEUWIyPE == edmGVakaRf){ohwKgsNrdP = true;}
      else if(edmGVakaRf == gDxEUWIyPE){hwwDRFbypZ = true;}
      if(qGPaXFVjid == XKkOxBWoFJ){qfKZdAqVuJ = true;}
      else if(XKkOxBWoFJ == qGPaXFVjid){zDqHDcSwTM = true;}
      if(xwSTzoVTNS == MhPeFSmzmm){FRqnFkAsML = true;}
      else if(MhPeFSmzmm == xwSTzoVTNS){jlPZobcuIO = true;}
      if(QhblpaIThX == ZZTZLDLKYP){HFGMkppjjo = true;}
      else if(ZZTZLDLKYP == QhblpaIThX){ltqePuSxRr = true;}
      if(ODisaIHXCS == rVchheszEV){gztDXHskrb = true;}
      else if(rVchheszEV == ODisaIHXCS){SCyIOupWlS = true;}
      if(bmlgYkkcFe == EdhuGwOHAC){NMEReWqIEu = true;}
      if(AnjwmIdcjw == mlmdFxpLDt){sTfRHlZxnn = true;}
      if(xBBLOsMZrp == oLPoRpEhxZ){JHkFbFWmQx = true;}
      while(EdhuGwOHAC == bmlgYkkcFe){tWJjBufVOp = true;}
      while(mlmdFxpLDt == mlmdFxpLDt){cfoamFLMqH = true;}
      while(oLPoRpEhxZ == oLPoRpEhxZ){KUdasgnHLs = true;}
      if(YmtRiurYTO == true){YmtRiurYTO = false;}
      if(nEKVcFhzbj == true){nEKVcFhzbj = false;}
      if(ohwKgsNrdP == true){ohwKgsNrdP = false;}
      if(qfKZdAqVuJ == true){qfKZdAqVuJ = false;}
      if(FRqnFkAsML == true){FRqnFkAsML = false;}
      if(HFGMkppjjo == true){HFGMkppjjo = false;}
      if(gztDXHskrb == true){gztDXHskrb = false;}
      if(NMEReWqIEu == true){NMEReWqIEu = false;}
      if(sTfRHlZxnn == true){sTfRHlZxnn = false;}
      if(JHkFbFWmQx == true){JHkFbFWmQx = false;}
      if(qPBjyuBnhN == true){qPBjyuBnhN = false;}
      if(zheowMScwk == true){zheowMScwk = false;}
      if(hwwDRFbypZ == true){hwwDRFbypZ = false;}
      if(zDqHDcSwTM == true){zDqHDcSwTM = false;}
      if(jlPZobcuIO == true){jlPZobcuIO = false;}
      if(ltqePuSxRr == true){ltqePuSxRr = false;}
      if(SCyIOupWlS == true){SCyIOupWlS = false;}
      if(tWJjBufVOp == true){tWJjBufVOp = false;}
      if(cfoamFLMqH == true){cfoamFLMqH = false;}
      if(KUdasgnHLs == true){KUdasgnHLs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CXRHRMWVMC
{ 
  void FnYaLLQAiu()
  { 
      bool IjrhnnWZAs = false;
      bool kQqjxOhYud = false;
      bool lJtlXrmGQi = false;
      bool NCGCOLWBcj = false;
      bool ZGBZnQkiot = false;
      bool lyaOdyoFKu = false;
      bool APJQfhJoVk = false;
      bool rfwKDeITyG = false;
      bool GERWxObrYP = false;
      bool WRpgiKxjtF = false;
      bool GuMEBFCPKy = false;
      bool pVHEowylSQ = false;
      bool GRQGOZpOas = false;
      bool gYZrAKqMUr = false;
      bool MMhZYBKlrm = false;
      bool LLQdzoeGob = false;
      bool OmnQRRuOEd = false;
      bool EkRZDtipgN = false;
      bool PDWnhVHwrK = false;
      bool fkXscZXQIH = false;
      string ygfaeoOFAy;
      string NrjImHZlHa;
      string qFNnVumHLC;
      string eiEGaHDFYR;
      string hkLMJMNqfr;
      string RDEdwsTrFi;
      string CHtySdndhf;
      string ETMorFtAeI;
      string guaTkbdZKh;
      string nKAoPaqMte;
      string XjJAmxpPkp;
      string zSNwCGgZNp;
      string ANTArsSXZR;
      string OgGzjxlafm;
      string lOoThUxEmI;
      string tQzEeKPJHs;
      string dSpSbSLNME;
      string UGtZDkYzRW;
      string uOjQXxgCTZ;
      string gcSmJTXVrP;
      if(ygfaeoOFAy == XjJAmxpPkp){IjrhnnWZAs = true;}
      else if(XjJAmxpPkp == ygfaeoOFAy){GuMEBFCPKy = true;}
      if(NrjImHZlHa == zSNwCGgZNp){kQqjxOhYud = true;}
      else if(zSNwCGgZNp == NrjImHZlHa){pVHEowylSQ = true;}
      if(qFNnVumHLC == ANTArsSXZR){lJtlXrmGQi = true;}
      else if(ANTArsSXZR == qFNnVumHLC){GRQGOZpOas = true;}
      if(eiEGaHDFYR == OgGzjxlafm){NCGCOLWBcj = true;}
      else if(OgGzjxlafm == eiEGaHDFYR){gYZrAKqMUr = true;}
      if(hkLMJMNqfr == lOoThUxEmI){ZGBZnQkiot = true;}
      else if(lOoThUxEmI == hkLMJMNqfr){MMhZYBKlrm = true;}
      if(RDEdwsTrFi == tQzEeKPJHs){lyaOdyoFKu = true;}
      else if(tQzEeKPJHs == RDEdwsTrFi){LLQdzoeGob = true;}
      if(CHtySdndhf == dSpSbSLNME){APJQfhJoVk = true;}
      else if(dSpSbSLNME == CHtySdndhf){OmnQRRuOEd = true;}
      if(ETMorFtAeI == UGtZDkYzRW){rfwKDeITyG = true;}
      if(guaTkbdZKh == uOjQXxgCTZ){GERWxObrYP = true;}
      if(nKAoPaqMte == gcSmJTXVrP){WRpgiKxjtF = true;}
      while(UGtZDkYzRW == ETMorFtAeI){EkRZDtipgN = true;}
      while(uOjQXxgCTZ == uOjQXxgCTZ){PDWnhVHwrK = true;}
      while(gcSmJTXVrP == gcSmJTXVrP){fkXscZXQIH = true;}
      if(IjrhnnWZAs == true){IjrhnnWZAs = false;}
      if(kQqjxOhYud == true){kQqjxOhYud = false;}
      if(lJtlXrmGQi == true){lJtlXrmGQi = false;}
      if(NCGCOLWBcj == true){NCGCOLWBcj = false;}
      if(ZGBZnQkiot == true){ZGBZnQkiot = false;}
      if(lyaOdyoFKu == true){lyaOdyoFKu = false;}
      if(APJQfhJoVk == true){APJQfhJoVk = false;}
      if(rfwKDeITyG == true){rfwKDeITyG = false;}
      if(GERWxObrYP == true){GERWxObrYP = false;}
      if(WRpgiKxjtF == true){WRpgiKxjtF = false;}
      if(GuMEBFCPKy == true){GuMEBFCPKy = false;}
      if(pVHEowylSQ == true){pVHEowylSQ = false;}
      if(GRQGOZpOas == true){GRQGOZpOas = false;}
      if(gYZrAKqMUr == true){gYZrAKqMUr = false;}
      if(MMhZYBKlrm == true){MMhZYBKlrm = false;}
      if(LLQdzoeGob == true){LLQdzoeGob = false;}
      if(OmnQRRuOEd == true){OmnQRRuOEd = false;}
      if(EkRZDtipgN == true){EkRZDtipgN = false;}
      if(PDWnhVHwrK == true){PDWnhVHwrK = false;}
      if(fkXscZXQIH == true){fkXscZXQIH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YMEQJOSSAG
{ 
  void rLXXApjTip()
  { 
      bool fbbUuragNN = false;
      bool bBZMBgxfyc = false;
      bool inpoBwZGaw = false;
      bool fJbVIQFJRu = false;
      bool kpAdaFgnNy = false;
      bool KIXpqqlmTz = false;
      bool RUFRhRZEEk = false;
      bool anODrrnMNu = false;
      bool OlsckWkleQ = false;
      bool eSpSdQkhwI = false;
      bool fcjcWVtUxy = false;
      bool CYYXkfacfL = false;
      bool fnYmFIywYb = false;
      bool HGQFPkBPFP = false;
      bool bQnfNFsRgx = false;
      bool oHBkbrEwWO = false;
      bool WyuVpwITIz = false;
      bool eKXQiPzrYz = false;
      bool OfObmAEecW = false;
      bool gErprcURpR = false;
      string MUONteuUPL;
      string jDLsZLGOuN;
      string HxzsCYOneC;
      string DpIxOlngOz;
      string GTzNfsQgMV;
      string pjBDnPUVKV;
      string QGoMHsuOdn;
      string WYAuHnxlMI;
      string HhbJLToFJz;
      string QSVrizdmFm;
      string yCCYyRjFuA;
      string RiICOiefAn;
      string EpEeWDCHMI;
      string JKfZKFeDKt;
      string jiJJhhKTdz;
      string TxmRiHxXBu;
      string PbsmpHChqI;
      string DbVFEUfuxn;
      string shdMnMXNqC;
      string HHBPeHoWTa;
      if(MUONteuUPL == yCCYyRjFuA){fbbUuragNN = true;}
      else if(yCCYyRjFuA == MUONteuUPL){fcjcWVtUxy = true;}
      if(jDLsZLGOuN == RiICOiefAn){bBZMBgxfyc = true;}
      else if(RiICOiefAn == jDLsZLGOuN){CYYXkfacfL = true;}
      if(HxzsCYOneC == EpEeWDCHMI){inpoBwZGaw = true;}
      else if(EpEeWDCHMI == HxzsCYOneC){fnYmFIywYb = true;}
      if(DpIxOlngOz == JKfZKFeDKt){fJbVIQFJRu = true;}
      else if(JKfZKFeDKt == DpIxOlngOz){HGQFPkBPFP = true;}
      if(GTzNfsQgMV == jiJJhhKTdz){kpAdaFgnNy = true;}
      else if(jiJJhhKTdz == GTzNfsQgMV){bQnfNFsRgx = true;}
      if(pjBDnPUVKV == TxmRiHxXBu){KIXpqqlmTz = true;}
      else if(TxmRiHxXBu == pjBDnPUVKV){oHBkbrEwWO = true;}
      if(QGoMHsuOdn == PbsmpHChqI){RUFRhRZEEk = true;}
      else if(PbsmpHChqI == QGoMHsuOdn){WyuVpwITIz = true;}
      if(WYAuHnxlMI == DbVFEUfuxn){anODrrnMNu = true;}
      if(HhbJLToFJz == shdMnMXNqC){OlsckWkleQ = true;}
      if(QSVrizdmFm == HHBPeHoWTa){eSpSdQkhwI = true;}
      while(DbVFEUfuxn == WYAuHnxlMI){eKXQiPzrYz = true;}
      while(shdMnMXNqC == shdMnMXNqC){OfObmAEecW = true;}
      while(HHBPeHoWTa == HHBPeHoWTa){gErprcURpR = true;}
      if(fbbUuragNN == true){fbbUuragNN = false;}
      if(bBZMBgxfyc == true){bBZMBgxfyc = false;}
      if(inpoBwZGaw == true){inpoBwZGaw = false;}
      if(fJbVIQFJRu == true){fJbVIQFJRu = false;}
      if(kpAdaFgnNy == true){kpAdaFgnNy = false;}
      if(KIXpqqlmTz == true){KIXpqqlmTz = false;}
      if(RUFRhRZEEk == true){RUFRhRZEEk = false;}
      if(anODrrnMNu == true){anODrrnMNu = false;}
      if(OlsckWkleQ == true){OlsckWkleQ = false;}
      if(eSpSdQkhwI == true){eSpSdQkhwI = false;}
      if(fcjcWVtUxy == true){fcjcWVtUxy = false;}
      if(CYYXkfacfL == true){CYYXkfacfL = false;}
      if(fnYmFIywYb == true){fnYmFIywYb = false;}
      if(HGQFPkBPFP == true){HGQFPkBPFP = false;}
      if(bQnfNFsRgx == true){bQnfNFsRgx = false;}
      if(oHBkbrEwWO == true){oHBkbrEwWO = false;}
      if(WyuVpwITIz == true){WyuVpwITIz = false;}
      if(eKXQiPzrYz == true){eKXQiPzrYz = false;}
      if(OfObmAEecW == true){OfObmAEecW = false;}
      if(gErprcURpR == true){gErprcURpR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGTXOPEOYO
{ 
  void iWjUMrcWwo()
  { 
      bool CRUuylAEeU = false;
      bool ohWgDRhfAJ = false;
      bool LhrmQnklcb = false;
      bool ZijrCKUile = false;
      bool laUhHOOiFr = false;
      bool CRwcqUYheK = false;
      bool BNbDuGyeer = false;
      bool wysUXkMKeC = false;
      bool YBgkYImGAh = false;
      bool kmEadXzRmB = false;
      bool PiEMuEXaFF = false;
      bool HOCbkzgpdm = false;
      bool SqdwHJtSqz = false;
      bool luWdlpxUpU = false;
      bool jMBuZWkbpe = false;
      bool pImAiYFHFk = false;
      bool JFiFSLqYpu = false;
      bool BMzJCGohWj = false;
      bool YRcLIdIWuN = false;
      bool kpOEKdcwcN = false;
      string hjAbHKwVJa;
      string xwZxlWFGBc;
      string owMfmjULbh;
      string OXMHwiaztq;
      string dZZPEBaIeR;
      string KNjXtlXToW;
      string oksbMZjSAC;
      string wGLKzOVwak;
      string JLfJWAmnNK;
      string LGJWBsfyDe;
      string RIIcVECYYe;
      string ParDNcEjFL;
      string luEpppwnIF;
      string iXrwSADDnR;
      string yNPhukNGJX;
      string nwrrsVDRle;
      string INQSwqhwkN;
      string ZBumMXfVuF;
      string bpekRmeADx;
      string wkQIJkxwlD;
      if(hjAbHKwVJa == RIIcVECYYe){CRUuylAEeU = true;}
      else if(RIIcVECYYe == hjAbHKwVJa){PiEMuEXaFF = true;}
      if(xwZxlWFGBc == ParDNcEjFL){ohWgDRhfAJ = true;}
      else if(ParDNcEjFL == xwZxlWFGBc){HOCbkzgpdm = true;}
      if(owMfmjULbh == luEpppwnIF){LhrmQnklcb = true;}
      else if(luEpppwnIF == owMfmjULbh){SqdwHJtSqz = true;}
      if(OXMHwiaztq == iXrwSADDnR){ZijrCKUile = true;}
      else if(iXrwSADDnR == OXMHwiaztq){luWdlpxUpU = true;}
      if(dZZPEBaIeR == yNPhukNGJX){laUhHOOiFr = true;}
      else if(yNPhukNGJX == dZZPEBaIeR){jMBuZWkbpe = true;}
      if(KNjXtlXToW == nwrrsVDRle){CRwcqUYheK = true;}
      else if(nwrrsVDRle == KNjXtlXToW){pImAiYFHFk = true;}
      if(oksbMZjSAC == INQSwqhwkN){BNbDuGyeer = true;}
      else if(INQSwqhwkN == oksbMZjSAC){JFiFSLqYpu = true;}
      if(wGLKzOVwak == ZBumMXfVuF){wysUXkMKeC = true;}
      if(JLfJWAmnNK == bpekRmeADx){YBgkYImGAh = true;}
      if(LGJWBsfyDe == wkQIJkxwlD){kmEadXzRmB = true;}
      while(ZBumMXfVuF == wGLKzOVwak){BMzJCGohWj = true;}
      while(bpekRmeADx == bpekRmeADx){YRcLIdIWuN = true;}
      while(wkQIJkxwlD == wkQIJkxwlD){kpOEKdcwcN = true;}
      if(CRUuylAEeU == true){CRUuylAEeU = false;}
      if(ohWgDRhfAJ == true){ohWgDRhfAJ = false;}
      if(LhrmQnklcb == true){LhrmQnklcb = false;}
      if(ZijrCKUile == true){ZijrCKUile = false;}
      if(laUhHOOiFr == true){laUhHOOiFr = false;}
      if(CRwcqUYheK == true){CRwcqUYheK = false;}
      if(BNbDuGyeer == true){BNbDuGyeer = false;}
      if(wysUXkMKeC == true){wysUXkMKeC = false;}
      if(YBgkYImGAh == true){YBgkYImGAh = false;}
      if(kmEadXzRmB == true){kmEadXzRmB = false;}
      if(PiEMuEXaFF == true){PiEMuEXaFF = false;}
      if(HOCbkzgpdm == true){HOCbkzgpdm = false;}
      if(SqdwHJtSqz == true){SqdwHJtSqz = false;}
      if(luWdlpxUpU == true){luWdlpxUpU = false;}
      if(jMBuZWkbpe == true){jMBuZWkbpe = false;}
      if(pImAiYFHFk == true){pImAiYFHFk = false;}
      if(JFiFSLqYpu == true){JFiFSLqYpu = false;}
      if(BMzJCGohWj == true){BMzJCGohWj = false;}
      if(YRcLIdIWuN == true){YRcLIdIWuN = false;}
      if(kpOEKdcwcN == true){kpOEKdcwcN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PARWHCRBTO
{ 
  void iKHCKrCcaX()
  { 
      bool POWBBfmLTD = false;
      bool LXTVUzXzcF = false;
      bool hsTwPJxocz = false;
      bool hdlcesrcNa = false;
      bool AOjOwqcXZF = false;
      bool RMQRzWualr = false;
      bool ixiTVgkqqa = false;
      bool GulBFTIFzY = false;
      bool fYPWhUNUdH = false;
      bool yRqUqCfPsP = false;
      bool GlgzyWaOLe = false;
      bool NpaNLJgLlA = false;
      bool SPMiboDQJC = false;
      bool nsLjStrQYK = false;
      bool tzIytIqdJh = false;
      bool UUdrwpYxWI = false;
      bool SJFIqUdpuQ = false;
      bool RQlaGTGNoT = false;
      bool yZHbhSPTmb = false;
      bool VusPrjtAHY = false;
      string SCZYexTkNa;
      string pCFZMKGArO;
      string pemkCCHiQp;
      string kJKMGjtsif;
      string KzRhAbzzAE;
      string RdxSsnOnVc;
      string pkTXogrsSc;
      string PMQMEpMFka;
      string CHiLXGLqTR;
      string VFWGoZesrT;
      string iGfXnENkOD;
      string bJDuZhCIAi;
      string UAZBGKpKWe;
      string KSMQqubKXS;
      string sacPpLBafH;
      string WWsJyigeQc;
      string OCOjsIwlEd;
      string GqjgptXJKt;
      string IOeOHmZDSH;
      string OwttEpMsWh;
      if(SCZYexTkNa == iGfXnENkOD){POWBBfmLTD = true;}
      else if(iGfXnENkOD == SCZYexTkNa){GlgzyWaOLe = true;}
      if(pCFZMKGArO == bJDuZhCIAi){LXTVUzXzcF = true;}
      else if(bJDuZhCIAi == pCFZMKGArO){NpaNLJgLlA = true;}
      if(pemkCCHiQp == UAZBGKpKWe){hsTwPJxocz = true;}
      else if(UAZBGKpKWe == pemkCCHiQp){SPMiboDQJC = true;}
      if(kJKMGjtsif == KSMQqubKXS){hdlcesrcNa = true;}
      else if(KSMQqubKXS == kJKMGjtsif){nsLjStrQYK = true;}
      if(KzRhAbzzAE == sacPpLBafH){AOjOwqcXZF = true;}
      else if(sacPpLBafH == KzRhAbzzAE){tzIytIqdJh = true;}
      if(RdxSsnOnVc == WWsJyigeQc){RMQRzWualr = true;}
      else if(WWsJyigeQc == RdxSsnOnVc){UUdrwpYxWI = true;}
      if(pkTXogrsSc == OCOjsIwlEd){ixiTVgkqqa = true;}
      else if(OCOjsIwlEd == pkTXogrsSc){SJFIqUdpuQ = true;}
      if(PMQMEpMFka == GqjgptXJKt){GulBFTIFzY = true;}
      if(CHiLXGLqTR == IOeOHmZDSH){fYPWhUNUdH = true;}
      if(VFWGoZesrT == OwttEpMsWh){yRqUqCfPsP = true;}
      while(GqjgptXJKt == PMQMEpMFka){RQlaGTGNoT = true;}
      while(IOeOHmZDSH == IOeOHmZDSH){yZHbhSPTmb = true;}
      while(OwttEpMsWh == OwttEpMsWh){VusPrjtAHY = true;}
      if(POWBBfmLTD == true){POWBBfmLTD = false;}
      if(LXTVUzXzcF == true){LXTVUzXzcF = false;}
      if(hsTwPJxocz == true){hsTwPJxocz = false;}
      if(hdlcesrcNa == true){hdlcesrcNa = false;}
      if(AOjOwqcXZF == true){AOjOwqcXZF = false;}
      if(RMQRzWualr == true){RMQRzWualr = false;}
      if(ixiTVgkqqa == true){ixiTVgkqqa = false;}
      if(GulBFTIFzY == true){GulBFTIFzY = false;}
      if(fYPWhUNUdH == true){fYPWhUNUdH = false;}
      if(yRqUqCfPsP == true){yRqUqCfPsP = false;}
      if(GlgzyWaOLe == true){GlgzyWaOLe = false;}
      if(NpaNLJgLlA == true){NpaNLJgLlA = false;}
      if(SPMiboDQJC == true){SPMiboDQJC = false;}
      if(nsLjStrQYK == true){nsLjStrQYK = false;}
      if(tzIytIqdJh == true){tzIytIqdJh = false;}
      if(UUdrwpYxWI == true){UUdrwpYxWI = false;}
      if(SJFIqUdpuQ == true){SJFIqUdpuQ = false;}
      if(RQlaGTGNoT == true){RQlaGTGNoT = false;}
      if(yZHbhSPTmb == true){yZHbhSPTmb = false;}
      if(VusPrjtAHY == true){VusPrjtAHY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIBICDXBIM
{ 
  void DDNYCObBxB()
  { 
      bool ZnoETMACXi = false;
      bool jtsSEQWeLa = false;
      bool ofgLKJQApB = false;
      bool qLlOnfZeiU = false;
      bool hCVpuulBmx = false;
      bool NegSGsGcsJ = false;
      bool uALVrXIeeY = false;
      bool prwpsmKqQO = false;
      bool WONsnMdTIt = false;
      bool YwkYZhqAyX = false;
      bool mHWOGVipYT = false;
      bool iPMelfmRhf = false;
      bool soVjzsGWQL = false;
      bool uKrsbPrzmR = false;
      bool cntnLIjGms = false;
      bool tYRSdyklOM = false;
      bool OLYNXYXTCW = false;
      bool nmePCFthYp = false;
      bool JAjXQWrZOc = false;
      bool dFjZCQOfQm = false;
      string QNzWyJRbIG;
      string yteRnrkWso;
      string nrstRHsgQm;
      string qVyFTxRwMz;
      string WLaCFXiDkN;
      string QFlpOXUFEp;
      string PjKUObwYxp;
      string anKtRcRqnt;
      string YpwCWliIpw;
      string cLqVimAFmd;
      string aJFtmcurXl;
      string GcRKQZnHyc;
      string rniBNOwnKe;
      string bLDKSPjBPt;
      string qqjDpztgFI;
      string ysGJkmZEgX;
      string fGgrKtZGqA;
      string olrElBDeKN;
      string TPiCgiEsZe;
      string pfUqNjJrsw;
      if(QNzWyJRbIG == aJFtmcurXl){ZnoETMACXi = true;}
      else if(aJFtmcurXl == QNzWyJRbIG){mHWOGVipYT = true;}
      if(yteRnrkWso == GcRKQZnHyc){jtsSEQWeLa = true;}
      else if(GcRKQZnHyc == yteRnrkWso){iPMelfmRhf = true;}
      if(nrstRHsgQm == rniBNOwnKe){ofgLKJQApB = true;}
      else if(rniBNOwnKe == nrstRHsgQm){soVjzsGWQL = true;}
      if(qVyFTxRwMz == bLDKSPjBPt){qLlOnfZeiU = true;}
      else if(bLDKSPjBPt == qVyFTxRwMz){uKrsbPrzmR = true;}
      if(WLaCFXiDkN == qqjDpztgFI){hCVpuulBmx = true;}
      else if(qqjDpztgFI == WLaCFXiDkN){cntnLIjGms = true;}
      if(QFlpOXUFEp == ysGJkmZEgX){NegSGsGcsJ = true;}
      else if(ysGJkmZEgX == QFlpOXUFEp){tYRSdyklOM = true;}
      if(PjKUObwYxp == fGgrKtZGqA){uALVrXIeeY = true;}
      else if(fGgrKtZGqA == PjKUObwYxp){OLYNXYXTCW = true;}
      if(anKtRcRqnt == olrElBDeKN){prwpsmKqQO = true;}
      if(YpwCWliIpw == TPiCgiEsZe){WONsnMdTIt = true;}
      if(cLqVimAFmd == pfUqNjJrsw){YwkYZhqAyX = true;}
      while(olrElBDeKN == anKtRcRqnt){nmePCFthYp = true;}
      while(TPiCgiEsZe == TPiCgiEsZe){JAjXQWrZOc = true;}
      while(pfUqNjJrsw == pfUqNjJrsw){dFjZCQOfQm = true;}
      if(ZnoETMACXi == true){ZnoETMACXi = false;}
      if(jtsSEQWeLa == true){jtsSEQWeLa = false;}
      if(ofgLKJQApB == true){ofgLKJQApB = false;}
      if(qLlOnfZeiU == true){qLlOnfZeiU = false;}
      if(hCVpuulBmx == true){hCVpuulBmx = false;}
      if(NegSGsGcsJ == true){NegSGsGcsJ = false;}
      if(uALVrXIeeY == true){uALVrXIeeY = false;}
      if(prwpsmKqQO == true){prwpsmKqQO = false;}
      if(WONsnMdTIt == true){WONsnMdTIt = false;}
      if(YwkYZhqAyX == true){YwkYZhqAyX = false;}
      if(mHWOGVipYT == true){mHWOGVipYT = false;}
      if(iPMelfmRhf == true){iPMelfmRhf = false;}
      if(soVjzsGWQL == true){soVjzsGWQL = false;}
      if(uKrsbPrzmR == true){uKrsbPrzmR = false;}
      if(cntnLIjGms == true){cntnLIjGms = false;}
      if(tYRSdyklOM == true){tYRSdyklOM = false;}
      if(OLYNXYXTCW == true){OLYNXYXTCW = false;}
      if(nmePCFthYp == true){nmePCFthYp = false;}
      if(JAjXQWrZOc == true){JAjXQWrZOc = false;}
      if(dFjZCQOfQm == true){dFjZCQOfQm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVVBUVAULQ
{ 
  void rBTuQfYiCp()
  { 
      bool jfBJIeDgce = false;
      bool rtZlHQGXzw = false;
      bool BDPXopMnzq = false;
      bool fnPUtSedEc = false;
      bool yAiZSgfPdx = false;
      bool wepySgPdUS = false;
      bool SPglyDdFqo = false;
      bool lbTVxBToEI = false;
      bool JwJCtAyQBN = false;
      bool DBJlJiSxbO = false;
      bool CaYoKULTBR = false;
      bool MZYMIVFeqx = false;
      bool FMEckkShMN = false;
      bool hWNoFiXTqZ = false;
      bool odPiBcbwcn = false;
      bool cnFdJoWuDZ = false;
      bool BdHmjoMjGZ = false;
      bool ykmQIbwUbI = false;
      bool JVEXjsQifQ = false;
      bool LcPRYKVczL = false;
      string XTRCSjlSMC;
      string KRSXkgTuLt;
      string yRQSGfnqyK;
      string CpmmSDpzJT;
      string TSVPJapLcx;
      string iuwiMGCzwm;
      string utTBzTefEg;
      string qTkqafwBJe;
      string pcOAaHtEaM;
      string BqCWYYyUQo;
      string wJGwGPJEHf;
      string JBoRwSfTZr;
      string ZZEqeAROSB;
      string gbkUhfVRsL;
      string xowtCABkZF;
      string sdtXOVFOQG;
      string xtkGzhPUiP;
      string xNaNtjdKoe;
      string yfnNHCgMFL;
      string aGBlOCDouU;
      if(XTRCSjlSMC == wJGwGPJEHf){jfBJIeDgce = true;}
      else if(wJGwGPJEHf == XTRCSjlSMC){CaYoKULTBR = true;}
      if(KRSXkgTuLt == JBoRwSfTZr){rtZlHQGXzw = true;}
      else if(JBoRwSfTZr == KRSXkgTuLt){MZYMIVFeqx = true;}
      if(yRQSGfnqyK == ZZEqeAROSB){BDPXopMnzq = true;}
      else if(ZZEqeAROSB == yRQSGfnqyK){FMEckkShMN = true;}
      if(CpmmSDpzJT == gbkUhfVRsL){fnPUtSedEc = true;}
      else if(gbkUhfVRsL == CpmmSDpzJT){hWNoFiXTqZ = true;}
      if(TSVPJapLcx == xowtCABkZF){yAiZSgfPdx = true;}
      else if(xowtCABkZF == TSVPJapLcx){odPiBcbwcn = true;}
      if(iuwiMGCzwm == sdtXOVFOQG){wepySgPdUS = true;}
      else if(sdtXOVFOQG == iuwiMGCzwm){cnFdJoWuDZ = true;}
      if(utTBzTefEg == xtkGzhPUiP){SPglyDdFqo = true;}
      else if(xtkGzhPUiP == utTBzTefEg){BdHmjoMjGZ = true;}
      if(qTkqafwBJe == xNaNtjdKoe){lbTVxBToEI = true;}
      if(pcOAaHtEaM == yfnNHCgMFL){JwJCtAyQBN = true;}
      if(BqCWYYyUQo == aGBlOCDouU){DBJlJiSxbO = true;}
      while(xNaNtjdKoe == qTkqafwBJe){ykmQIbwUbI = true;}
      while(yfnNHCgMFL == yfnNHCgMFL){JVEXjsQifQ = true;}
      while(aGBlOCDouU == aGBlOCDouU){LcPRYKVczL = true;}
      if(jfBJIeDgce == true){jfBJIeDgce = false;}
      if(rtZlHQGXzw == true){rtZlHQGXzw = false;}
      if(BDPXopMnzq == true){BDPXopMnzq = false;}
      if(fnPUtSedEc == true){fnPUtSedEc = false;}
      if(yAiZSgfPdx == true){yAiZSgfPdx = false;}
      if(wepySgPdUS == true){wepySgPdUS = false;}
      if(SPglyDdFqo == true){SPglyDdFqo = false;}
      if(lbTVxBToEI == true){lbTVxBToEI = false;}
      if(JwJCtAyQBN == true){JwJCtAyQBN = false;}
      if(DBJlJiSxbO == true){DBJlJiSxbO = false;}
      if(CaYoKULTBR == true){CaYoKULTBR = false;}
      if(MZYMIVFeqx == true){MZYMIVFeqx = false;}
      if(FMEckkShMN == true){FMEckkShMN = false;}
      if(hWNoFiXTqZ == true){hWNoFiXTqZ = false;}
      if(odPiBcbwcn == true){odPiBcbwcn = false;}
      if(cnFdJoWuDZ == true){cnFdJoWuDZ = false;}
      if(BdHmjoMjGZ == true){BdHmjoMjGZ = false;}
      if(ykmQIbwUbI == true){ykmQIbwUbI = false;}
      if(JVEXjsQifQ == true){JVEXjsQifQ = false;}
      if(LcPRYKVczL == true){LcPRYKVczL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEGCOMJHQL
{ 
  void kMlGZJXiqP()
  { 
      bool MaWPclnkFD = false;
      bool diuGNHJEya = false;
      bool jJWUphWSqr = false;
      bool yxeBFhzmao = false;
      bool ByXuHfhwmu = false;
      bool FGWLHCDBZt = false;
      bool OUsMEgEtBf = false;
      bool IWcIYllbNJ = false;
      bool AaewmrZStD = false;
      bool dxMgZfEKqZ = false;
      bool bnuHmhcOlV = false;
      bool QbnQtnpxZL = false;
      bool HkzxBLKwis = false;
      bool gajmgLeXIE = false;
      bool OLfYlCJwmk = false;
      bool pHkeSpnxGb = false;
      bool XgfsnpqAih = false;
      bool ISnUxwEaLz = false;
      bool BNIxCYpFUp = false;
      bool XhRgggemjw = false;
      string eCsSHDTIpO;
      string suXJmCXQbf;
      string yUkEgyKBNE;
      string PoWiHsSFAN;
      string fxuxykLxiL;
      string tBQNPKRnlJ;
      string sSulzEYnCs;
      string iRPNAAZnGw;
      string mNRBJOXJSw;
      string bdTqUMCJxt;
      string MWtpbbkCNO;
      string jchpVeBsbk;
      string fOVFQFyXsm;
      string yQpMiQSbYg;
      string cUwDLzwcVo;
      string LIgMNxBoYW;
      string cMJZQTmVGF;
      string MZUuHKSRsR;
      string IVCEbojcyl;
      string PdCBDPLVmr;
      if(eCsSHDTIpO == MWtpbbkCNO){MaWPclnkFD = true;}
      else if(MWtpbbkCNO == eCsSHDTIpO){bnuHmhcOlV = true;}
      if(suXJmCXQbf == jchpVeBsbk){diuGNHJEya = true;}
      else if(jchpVeBsbk == suXJmCXQbf){QbnQtnpxZL = true;}
      if(yUkEgyKBNE == fOVFQFyXsm){jJWUphWSqr = true;}
      else if(fOVFQFyXsm == yUkEgyKBNE){HkzxBLKwis = true;}
      if(PoWiHsSFAN == yQpMiQSbYg){yxeBFhzmao = true;}
      else if(yQpMiQSbYg == PoWiHsSFAN){gajmgLeXIE = true;}
      if(fxuxykLxiL == cUwDLzwcVo){ByXuHfhwmu = true;}
      else if(cUwDLzwcVo == fxuxykLxiL){OLfYlCJwmk = true;}
      if(tBQNPKRnlJ == LIgMNxBoYW){FGWLHCDBZt = true;}
      else if(LIgMNxBoYW == tBQNPKRnlJ){pHkeSpnxGb = true;}
      if(sSulzEYnCs == cMJZQTmVGF){OUsMEgEtBf = true;}
      else if(cMJZQTmVGF == sSulzEYnCs){XgfsnpqAih = true;}
      if(iRPNAAZnGw == MZUuHKSRsR){IWcIYllbNJ = true;}
      if(mNRBJOXJSw == IVCEbojcyl){AaewmrZStD = true;}
      if(bdTqUMCJxt == PdCBDPLVmr){dxMgZfEKqZ = true;}
      while(MZUuHKSRsR == iRPNAAZnGw){ISnUxwEaLz = true;}
      while(IVCEbojcyl == IVCEbojcyl){BNIxCYpFUp = true;}
      while(PdCBDPLVmr == PdCBDPLVmr){XhRgggemjw = true;}
      if(MaWPclnkFD == true){MaWPclnkFD = false;}
      if(diuGNHJEya == true){diuGNHJEya = false;}
      if(jJWUphWSqr == true){jJWUphWSqr = false;}
      if(yxeBFhzmao == true){yxeBFhzmao = false;}
      if(ByXuHfhwmu == true){ByXuHfhwmu = false;}
      if(FGWLHCDBZt == true){FGWLHCDBZt = false;}
      if(OUsMEgEtBf == true){OUsMEgEtBf = false;}
      if(IWcIYllbNJ == true){IWcIYllbNJ = false;}
      if(AaewmrZStD == true){AaewmrZStD = false;}
      if(dxMgZfEKqZ == true){dxMgZfEKqZ = false;}
      if(bnuHmhcOlV == true){bnuHmhcOlV = false;}
      if(QbnQtnpxZL == true){QbnQtnpxZL = false;}
      if(HkzxBLKwis == true){HkzxBLKwis = false;}
      if(gajmgLeXIE == true){gajmgLeXIE = false;}
      if(OLfYlCJwmk == true){OLfYlCJwmk = false;}
      if(pHkeSpnxGb == true){pHkeSpnxGb = false;}
      if(XgfsnpqAih == true){XgfsnpqAih = false;}
      if(ISnUxwEaLz == true){ISnUxwEaLz = false;}
      if(BNIxCYpFUp == true){BNIxCYpFUp = false;}
      if(XhRgggemjw == true){XhRgggemjw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSCSRGCOJL
{ 
  void RNeoannWOf()
  { 
      bool RVXZoomRwn = false;
      bool FgVhyhSixm = false;
      bool eiPPsdKeue = false;
      bool BNRteyooKU = false;
      bool OTgmeiahrf = false;
      bool SWmmghFHfL = false;
      bool eHWQlqOaDA = false;
      bool rcYcYLBckJ = false;
      bool CbmOMeaeMw = false;
      bool rgIyoGwPAm = false;
      bool UzdqmpyJOV = false;
      bool gcWWICUIEH = false;
      bool QiOHILTZmS = false;
      bool OlbxnDxwaW = false;
      bool gQPqPPJlpm = false;
      bool kmKsWkkWhb = false;
      bool VXWwHtBYhE = false;
      bool EYhhZzTWrs = false;
      bool BgjAgaahaD = false;
      bool SaNyAItTiU = false;
      string DQVOwgjznC;
      string JjhriJnolV;
      string aOXsqYtNMb;
      string RXUMxaDlGE;
      string IaGidICHNE;
      string jQhuynrcXW;
      string mVmLklPVtI;
      string GBihNzIoOh;
      string WlAHrAoZNJ;
      string hZOjQlnuxr;
      string sgMFyhgAhz;
      string eDNozAVeSj;
      string woHjafmzQa;
      string KNqWnpYuJJ;
      string ToqOddMYjQ;
      string QJbNuDYbdS;
      string uhiHnRMqAJ;
      string aaVJQHyrGw;
      string TNPAJBldak;
      string QwQqOkFjZM;
      if(DQVOwgjznC == sgMFyhgAhz){RVXZoomRwn = true;}
      else if(sgMFyhgAhz == DQVOwgjznC){UzdqmpyJOV = true;}
      if(JjhriJnolV == eDNozAVeSj){FgVhyhSixm = true;}
      else if(eDNozAVeSj == JjhriJnolV){gcWWICUIEH = true;}
      if(aOXsqYtNMb == woHjafmzQa){eiPPsdKeue = true;}
      else if(woHjafmzQa == aOXsqYtNMb){QiOHILTZmS = true;}
      if(RXUMxaDlGE == KNqWnpYuJJ){BNRteyooKU = true;}
      else if(KNqWnpYuJJ == RXUMxaDlGE){OlbxnDxwaW = true;}
      if(IaGidICHNE == ToqOddMYjQ){OTgmeiahrf = true;}
      else if(ToqOddMYjQ == IaGidICHNE){gQPqPPJlpm = true;}
      if(jQhuynrcXW == QJbNuDYbdS){SWmmghFHfL = true;}
      else if(QJbNuDYbdS == jQhuynrcXW){kmKsWkkWhb = true;}
      if(mVmLklPVtI == uhiHnRMqAJ){eHWQlqOaDA = true;}
      else if(uhiHnRMqAJ == mVmLklPVtI){VXWwHtBYhE = true;}
      if(GBihNzIoOh == aaVJQHyrGw){rcYcYLBckJ = true;}
      if(WlAHrAoZNJ == TNPAJBldak){CbmOMeaeMw = true;}
      if(hZOjQlnuxr == QwQqOkFjZM){rgIyoGwPAm = true;}
      while(aaVJQHyrGw == GBihNzIoOh){EYhhZzTWrs = true;}
      while(TNPAJBldak == TNPAJBldak){BgjAgaahaD = true;}
      while(QwQqOkFjZM == QwQqOkFjZM){SaNyAItTiU = true;}
      if(RVXZoomRwn == true){RVXZoomRwn = false;}
      if(FgVhyhSixm == true){FgVhyhSixm = false;}
      if(eiPPsdKeue == true){eiPPsdKeue = false;}
      if(BNRteyooKU == true){BNRteyooKU = false;}
      if(OTgmeiahrf == true){OTgmeiahrf = false;}
      if(SWmmghFHfL == true){SWmmghFHfL = false;}
      if(eHWQlqOaDA == true){eHWQlqOaDA = false;}
      if(rcYcYLBckJ == true){rcYcYLBckJ = false;}
      if(CbmOMeaeMw == true){CbmOMeaeMw = false;}
      if(rgIyoGwPAm == true){rgIyoGwPAm = false;}
      if(UzdqmpyJOV == true){UzdqmpyJOV = false;}
      if(gcWWICUIEH == true){gcWWICUIEH = false;}
      if(QiOHILTZmS == true){QiOHILTZmS = false;}
      if(OlbxnDxwaW == true){OlbxnDxwaW = false;}
      if(gQPqPPJlpm == true){gQPqPPJlpm = false;}
      if(kmKsWkkWhb == true){kmKsWkkWhb = false;}
      if(VXWwHtBYhE == true){VXWwHtBYhE = false;}
      if(EYhhZzTWrs == true){EYhhZzTWrs = false;}
      if(BgjAgaahaD == true){BgjAgaahaD = false;}
      if(SaNyAItTiU == true){SaNyAItTiU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLYPJSVJNQ
{ 
  void LrHPMxGCXW()
  { 
      bool YofSltkMBt = false;
      bool AMdQBnNyyL = false;
      bool bIIKeBxWnZ = false;
      bool VkTQVrpRfi = false;
      bool dMyAAwpcfD = false;
      bool FwMzrPgVmj = false;
      bool xOYbXOrNtI = false;
      bool xwSOhPKIJh = false;
      bool KUpkUZXUXG = false;
      bool LUdulPmVbl = false;
      bool DchXFIdxRc = false;
      bool EYLFYcYnHy = false;
      bool pXpnxbRWcR = false;
      bool bnfXdhmSeL = false;
      bool uZDuBmJYVJ = false;
      bool qzOdufmsZd = false;
      bool qHUzAQrmaq = false;
      bool pGJwCPUtlJ = false;
      bool RsASacZCby = false;
      bool usrATnFDuk = false;
      string kbbQHumXiz;
      string YjKxFsJfbU;
      string gaWUbIdwWX;
      string hpTWAqMqti;
      string XNjWXxyVDr;
      string talnBJEHnz;
      string QpBKRhPnxO;
      string gSlswSqAwe;
      string KIsddGEfVp;
      string lECuRgMYFo;
      string gJXnLaorqh;
      string SEKJnIwWgK;
      string cjSHbbPqbP;
      string FRuHxAkFRC;
      string RLnmWhsrGJ;
      string kprtLwqPLj;
      string LyQbbBJDLn;
      string WqEesRwekt;
      string hWjSdPZAuA;
      string IUshqSuLLU;
      if(kbbQHumXiz == gJXnLaorqh){YofSltkMBt = true;}
      else if(gJXnLaorqh == kbbQHumXiz){DchXFIdxRc = true;}
      if(YjKxFsJfbU == SEKJnIwWgK){AMdQBnNyyL = true;}
      else if(SEKJnIwWgK == YjKxFsJfbU){EYLFYcYnHy = true;}
      if(gaWUbIdwWX == cjSHbbPqbP){bIIKeBxWnZ = true;}
      else if(cjSHbbPqbP == gaWUbIdwWX){pXpnxbRWcR = true;}
      if(hpTWAqMqti == FRuHxAkFRC){VkTQVrpRfi = true;}
      else if(FRuHxAkFRC == hpTWAqMqti){bnfXdhmSeL = true;}
      if(XNjWXxyVDr == RLnmWhsrGJ){dMyAAwpcfD = true;}
      else if(RLnmWhsrGJ == XNjWXxyVDr){uZDuBmJYVJ = true;}
      if(talnBJEHnz == kprtLwqPLj){FwMzrPgVmj = true;}
      else if(kprtLwqPLj == talnBJEHnz){qzOdufmsZd = true;}
      if(QpBKRhPnxO == LyQbbBJDLn){xOYbXOrNtI = true;}
      else if(LyQbbBJDLn == QpBKRhPnxO){qHUzAQrmaq = true;}
      if(gSlswSqAwe == WqEesRwekt){xwSOhPKIJh = true;}
      if(KIsddGEfVp == hWjSdPZAuA){KUpkUZXUXG = true;}
      if(lECuRgMYFo == IUshqSuLLU){LUdulPmVbl = true;}
      while(WqEesRwekt == gSlswSqAwe){pGJwCPUtlJ = true;}
      while(hWjSdPZAuA == hWjSdPZAuA){RsASacZCby = true;}
      while(IUshqSuLLU == IUshqSuLLU){usrATnFDuk = true;}
      if(YofSltkMBt == true){YofSltkMBt = false;}
      if(AMdQBnNyyL == true){AMdQBnNyyL = false;}
      if(bIIKeBxWnZ == true){bIIKeBxWnZ = false;}
      if(VkTQVrpRfi == true){VkTQVrpRfi = false;}
      if(dMyAAwpcfD == true){dMyAAwpcfD = false;}
      if(FwMzrPgVmj == true){FwMzrPgVmj = false;}
      if(xOYbXOrNtI == true){xOYbXOrNtI = false;}
      if(xwSOhPKIJh == true){xwSOhPKIJh = false;}
      if(KUpkUZXUXG == true){KUpkUZXUXG = false;}
      if(LUdulPmVbl == true){LUdulPmVbl = false;}
      if(DchXFIdxRc == true){DchXFIdxRc = false;}
      if(EYLFYcYnHy == true){EYLFYcYnHy = false;}
      if(pXpnxbRWcR == true){pXpnxbRWcR = false;}
      if(bnfXdhmSeL == true){bnfXdhmSeL = false;}
      if(uZDuBmJYVJ == true){uZDuBmJYVJ = false;}
      if(qzOdufmsZd == true){qzOdufmsZd = false;}
      if(qHUzAQrmaq == true){qHUzAQrmaq = false;}
      if(pGJwCPUtlJ == true){pGJwCPUtlJ = false;}
      if(RsASacZCby == true){RsASacZCby = false;}
      if(usrATnFDuk == true){usrATnFDuk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMETDFIQJH
{ 
  void SXmWqrghiI()
  { 
      bool HgFnqjTmuu = false;
      bool hQHhcOVlKL = false;
      bool RGXExFMbpI = false;
      bool GNFdmkZxaf = false;
      bool GwEXISSJXm = false;
      bool CqOxRBIApk = false;
      bool XrwloTKctr = false;
      bool nXKdFVBAwe = false;
      bool lDEDFPzIMl = false;
      bool cZHpINzRin = false;
      bool HpPfydfjqu = false;
      bool zHELzTnsfY = false;
      bool UCQHOOQUVq = false;
      bool WjRHXwmXEb = false;
      bool iOQQmUVwpn = false;
      bool ZFkJTEYHQj = false;
      bool NKOAYOpwnC = false;
      bool fPoEoFlAUs = false;
      bool rUdgQQzInS = false;
      bool XfHUOXAQqX = false;
      string WDUWXVcdBm;
      string CHjEpzXtaW;
      string aUIkuTguVn;
      string gImPEnxiVm;
      string zeitpbLSmn;
      string PmgFHCujaE;
      string ohHNGsUTAB;
      string CoYmXwkOuT;
      string HNHhXtbhIC;
      string sMIRyQWVnw;
      string HrSlkaNthL;
      string QfoHwaaZoM;
      string RlLyIpfGoG;
      string YPayLPuVww;
      string fhzwkMXAUW;
      string pxfaeUfUcu;
      string tHEamBFqug;
      string fFcrfjlOMu;
      string RekRQaizSq;
      string iarBCXcYJi;
      if(WDUWXVcdBm == HrSlkaNthL){HgFnqjTmuu = true;}
      else if(HrSlkaNthL == WDUWXVcdBm){HpPfydfjqu = true;}
      if(CHjEpzXtaW == QfoHwaaZoM){hQHhcOVlKL = true;}
      else if(QfoHwaaZoM == CHjEpzXtaW){zHELzTnsfY = true;}
      if(aUIkuTguVn == RlLyIpfGoG){RGXExFMbpI = true;}
      else if(RlLyIpfGoG == aUIkuTguVn){UCQHOOQUVq = true;}
      if(gImPEnxiVm == YPayLPuVww){GNFdmkZxaf = true;}
      else if(YPayLPuVww == gImPEnxiVm){WjRHXwmXEb = true;}
      if(zeitpbLSmn == fhzwkMXAUW){GwEXISSJXm = true;}
      else if(fhzwkMXAUW == zeitpbLSmn){iOQQmUVwpn = true;}
      if(PmgFHCujaE == pxfaeUfUcu){CqOxRBIApk = true;}
      else if(pxfaeUfUcu == PmgFHCujaE){ZFkJTEYHQj = true;}
      if(ohHNGsUTAB == tHEamBFqug){XrwloTKctr = true;}
      else if(tHEamBFqug == ohHNGsUTAB){NKOAYOpwnC = true;}
      if(CoYmXwkOuT == fFcrfjlOMu){nXKdFVBAwe = true;}
      if(HNHhXtbhIC == RekRQaizSq){lDEDFPzIMl = true;}
      if(sMIRyQWVnw == iarBCXcYJi){cZHpINzRin = true;}
      while(fFcrfjlOMu == CoYmXwkOuT){fPoEoFlAUs = true;}
      while(RekRQaizSq == RekRQaizSq){rUdgQQzInS = true;}
      while(iarBCXcYJi == iarBCXcYJi){XfHUOXAQqX = true;}
      if(HgFnqjTmuu == true){HgFnqjTmuu = false;}
      if(hQHhcOVlKL == true){hQHhcOVlKL = false;}
      if(RGXExFMbpI == true){RGXExFMbpI = false;}
      if(GNFdmkZxaf == true){GNFdmkZxaf = false;}
      if(GwEXISSJXm == true){GwEXISSJXm = false;}
      if(CqOxRBIApk == true){CqOxRBIApk = false;}
      if(XrwloTKctr == true){XrwloTKctr = false;}
      if(nXKdFVBAwe == true){nXKdFVBAwe = false;}
      if(lDEDFPzIMl == true){lDEDFPzIMl = false;}
      if(cZHpINzRin == true){cZHpINzRin = false;}
      if(HpPfydfjqu == true){HpPfydfjqu = false;}
      if(zHELzTnsfY == true){zHELzTnsfY = false;}
      if(UCQHOOQUVq == true){UCQHOOQUVq = false;}
      if(WjRHXwmXEb == true){WjRHXwmXEb = false;}
      if(iOQQmUVwpn == true){iOQQmUVwpn = false;}
      if(ZFkJTEYHQj == true){ZFkJTEYHQj = false;}
      if(NKOAYOpwnC == true){NKOAYOpwnC = false;}
      if(fPoEoFlAUs == true){fPoEoFlAUs = false;}
      if(rUdgQQzInS == true){rUdgQQzInS = false;}
      if(XfHUOXAQqX == true){XfHUOXAQqX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOVLARLEKD
{ 
  void AitCLqQmZd()
  { 
      bool KAEJLgHJQx = false;
      bool ymZTHpmYsb = false;
      bool RHLAiicDOQ = false;
      bool NzqUHggryA = false;
      bool ZQRuyFmidD = false;
      bool aJjzzDoDac = false;
      bool DEtziyuFMa = false;
      bool JuZsCApPCd = false;
      bool wsZLpDPrUD = false;
      bool qdRVxVVRMA = false;
      bool JgWCtfiqwz = false;
      bool NZBxgJeiJf = false;
      bool iCjIifdEug = false;
      bool dXDBTOWWRK = false;
      bool TXwVpRcTom = false;
      bool qmHfRHxNTO = false;
      bool BeuPUoWzdS = false;
      bool mHQzLKGOSQ = false;
      bool DJOIopPWjL = false;
      bool QJCDInbfAA = false;
      string WnWPiYOnZa;
      string uygGoQpuQr;
      string YyIkJzZsRL;
      string JMkDRAhewY;
      string JiKxpYouuM;
      string absHdXfkGj;
      string yVVORhMdno;
      string iLzripnKtj;
      string JexFkgTcYs;
      string UwXLZmMufH;
      string LLGGcPcBXm;
      string jUqVZTYQdj;
      string OiEuTmmmRw;
      string drelYyXqbV;
      string ESFkJAFBkG;
      string OwRwsbGLmp;
      string boiaJroExa;
      string ugoIfwdSlS;
      string hkCKhgZhsw;
      string rMDksOidbR;
      if(WnWPiYOnZa == LLGGcPcBXm){KAEJLgHJQx = true;}
      else if(LLGGcPcBXm == WnWPiYOnZa){JgWCtfiqwz = true;}
      if(uygGoQpuQr == jUqVZTYQdj){ymZTHpmYsb = true;}
      else if(jUqVZTYQdj == uygGoQpuQr){NZBxgJeiJf = true;}
      if(YyIkJzZsRL == OiEuTmmmRw){RHLAiicDOQ = true;}
      else if(OiEuTmmmRw == YyIkJzZsRL){iCjIifdEug = true;}
      if(JMkDRAhewY == drelYyXqbV){NzqUHggryA = true;}
      else if(drelYyXqbV == JMkDRAhewY){dXDBTOWWRK = true;}
      if(JiKxpYouuM == ESFkJAFBkG){ZQRuyFmidD = true;}
      else if(ESFkJAFBkG == JiKxpYouuM){TXwVpRcTom = true;}
      if(absHdXfkGj == OwRwsbGLmp){aJjzzDoDac = true;}
      else if(OwRwsbGLmp == absHdXfkGj){qmHfRHxNTO = true;}
      if(yVVORhMdno == boiaJroExa){DEtziyuFMa = true;}
      else if(boiaJroExa == yVVORhMdno){BeuPUoWzdS = true;}
      if(iLzripnKtj == ugoIfwdSlS){JuZsCApPCd = true;}
      if(JexFkgTcYs == hkCKhgZhsw){wsZLpDPrUD = true;}
      if(UwXLZmMufH == rMDksOidbR){qdRVxVVRMA = true;}
      while(ugoIfwdSlS == iLzripnKtj){mHQzLKGOSQ = true;}
      while(hkCKhgZhsw == hkCKhgZhsw){DJOIopPWjL = true;}
      while(rMDksOidbR == rMDksOidbR){QJCDInbfAA = true;}
      if(KAEJLgHJQx == true){KAEJLgHJQx = false;}
      if(ymZTHpmYsb == true){ymZTHpmYsb = false;}
      if(RHLAiicDOQ == true){RHLAiicDOQ = false;}
      if(NzqUHggryA == true){NzqUHggryA = false;}
      if(ZQRuyFmidD == true){ZQRuyFmidD = false;}
      if(aJjzzDoDac == true){aJjzzDoDac = false;}
      if(DEtziyuFMa == true){DEtziyuFMa = false;}
      if(JuZsCApPCd == true){JuZsCApPCd = false;}
      if(wsZLpDPrUD == true){wsZLpDPrUD = false;}
      if(qdRVxVVRMA == true){qdRVxVVRMA = false;}
      if(JgWCtfiqwz == true){JgWCtfiqwz = false;}
      if(NZBxgJeiJf == true){NZBxgJeiJf = false;}
      if(iCjIifdEug == true){iCjIifdEug = false;}
      if(dXDBTOWWRK == true){dXDBTOWWRK = false;}
      if(TXwVpRcTom == true){TXwVpRcTom = false;}
      if(qmHfRHxNTO == true){qmHfRHxNTO = false;}
      if(BeuPUoWzdS == true){BeuPUoWzdS = false;}
      if(mHQzLKGOSQ == true){mHQzLKGOSQ = false;}
      if(DJOIopPWjL == true){DJOIopPWjL = false;}
      if(QJCDInbfAA == true){QJCDInbfAA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAXTNHENBV
{ 
  void hsNZrQhjoV()
  { 
      bool YFqYMFzRwZ = false;
      bool SyalqouMWn = false;
      bool WoZckdibNF = false;
      bool uiLyYXJXPK = false;
      bool kktcUCXVlJ = false;
      bool hEKyfjeOmi = false;
      bool VXEqejmcMT = false;
      bool fXwLDktwHi = false;
      bool FMoEWpYMRo = false;
      bool rtjgoMgDyk = false;
      bool PtJScKIytu = false;
      bool ohHEcIizTn = false;
      bool KZLXakmOWq = false;
      bool DqyVTLDVaL = false;
      bool haRVzKlfEf = false;
      bool chiJaoikqq = false;
      bool XsaDrxjljR = false;
      bool FNYIGjHpXQ = false;
      bool zGKqOVIntd = false;
      bool bSeinnzOdC = false;
      string HnEQtxwIlF;
      string UnfabkqnxC;
      string qkbleDIdZu;
      string albrJSVjkj;
      string CqVRoiwYwu;
      string HDWCPWLRkp;
      string nShpdiLnRJ;
      string PHCNzzOJxu;
      string GigdnXPYbl;
      string GDytujJfmG;
      string WIHmfzAIDP;
      string ICUojElDBG;
      string TmLeCLJHSO;
      string phWpYxbsyo;
      string WGVMdEiIKp;
      string yFefmjxcjT;
      string pronYZedQl;
      string crFMjMQyBy;
      string cAxcQkDpDn;
      string AzIdydRhmD;
      if(HnEQtxwIlF == WIHmfzAIDP){YFqYMFzRwZ = true;}
      else if(WIHmfzAIDP == HnEQtxwIlF){PtJScKIytu = true;}
      if(UnfabkqnxC == ICUojElDBG){SyalqouMWn = true;}
      else if(ICUojElDBG == UnfabkqnxC){ohHEcIizTn = true;}
      if(qkbleDIdZu == TmLeCLJHSO){WoZckdibNF = true;}
      else if(TmLeCLJHSO == qkbleDIdZu){KZLXakmOWq = true;}
      if(albrJSVjkj == phWpYxbsyo){uiLyYXJXPK = true;}
      else if(phWpYxbsyo == albrJSVjkj){DqyVTLDVaL = true;}
      if(CqVRoiwYwu == WGVMdEiIKp){kktcUCXVlJ = true;}
      else if(WGVMdEiIKp == CqVRoiwYwu){haRVzKlfEf = true;}
      if(HDWCPWLRkp == yFefmjxcjT){hEKyfjeOmi = true;}
      else if(yFefmjxcjT == HDWCPWLRkp){chiJaoikqq = true;}
      if(nShpdiLnRJ == pronYZedQl){VXEqejmcMT = true;}
      else if(pronYZedQl == nShpdiLnRJ){XsaDrxjljR = true;}
      if(PHCNzzOJxu == crFMjMQyBy){fXwLDktwHi = true;}
      if(GigdnXPYbl == cAxcQkDpDn){FMoEWpYMRo = true;}
      if(GDytujJfmG == AzIdydRhmD){rtjgoMgDyk = true;}
      while(crFMjMQyBy == PHCNzzOJxu){FNYIGjHpXQ = true;}
      while(cAxcQkDpDn == cAxcQkDpDn){zGKqOVIntd = true;}
      while(AzIdydRhmD == AzIdydRhmD){bSeinnzOdC = true;}
      if(YFqYMFzRwZ == true){YFqYMFzRwZ = false;}
      if(SyalqouMWn == true){SyalqouMWn = false;}
      if(WoZckdibNF == true){WoZckdibNF = false;}
      if(uiLyYXJXPK == true){uiLyYXJXPK = false;}
      if(kktcUCXVlJ == true){kktcUCXVlJ = false;}
      if(hEKyfjeOmi == true){hEKyfjeOmi = false;}
      if(VXEqejmcMT == true){VXEqejmcMT = false;}
      if(fXwLDktwHi == true){fXwLDktwHi = false;}
      if(FMoEWpYMRo == true){FMoEWpYMRo = false;}
      if(rtjgoMgDyk == true){rtjgoMgDyk = false;}
      if(PtJScKIytu == true){PtJScKIytu = false;}
      if(ohHEcIizTn == true){ohHEcIizTn = false;}
      if(KZLXakmOWq == true){KZLXakmOWq = false;}
      if(DqyVTLDVaL == true){DqyVTLDVaL = false;}
      if(haRVzKlfEf == true){haRVzKlfEf = false;}
      if(chiJaoikqq == true){chiJaoikqq = false;}
      if(XsaDrxjljR == true){XsaDrxjljR = false;}
      if(FNYIGjHpXQ == true){FNYIGjHpXQ = false;}
      if(zGKqOVIntd == true){zGKqOVIntd = false;}
      if(bSeinnzOdC == true){bSeinnzOdC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTTOLKJCES
{ 
  void caLVupNCqi()
  { 
      bool wLMsVNrGjn = false;
      bool yYDQVqInTc = false;
      bool twNgdlqGVx = false;
      bool dKmfLEESEh = false;
      bool PRnhncOfRX = false;
      bool OQoqKzxfOi = false;
      bool WljmKmlXEQ = false;
      bool lpikMcIerB = false;
      bool XKnxiNVwVM = false;
      bool GYEULdgBXB = false;
      bool qqaBlXhDdh = false;
      bool qSnNLLymDx = false;
      bool QpCrJNlOZi = false;
      bool wHHqJfjmLL = false;
      bool eRRmVnjpIz = false;
      bool etxajAoiqX = false;
      bool lSculiKxDe = false;
      bool bLbrRzXOWV = false;
      bool cuFaDCJgGI = false;
      bool qBumYMnWBl = false;
      string BbhFVujDZs;
      string gqXRIRyMGq;
      string yDdgNaXJMl;
      string gtIVCQbwkN;
      string jxnfMuwOpn;
      string IhJUixyAqu;
      string WaqmMmhBOr;
      string oCasGBPyUS;
      string eISXdyjnmF;
      string RbEppJFASZ;
      string MuzyyGGQNg;
      string gAfYQOISIN;
      string CtNJZMxkCx;
      string uPetFiIUYX;
      string rSZGXRwfZb;
      string BlqFXSgpXl;
      string IUOQlRVkSg;
      string FmskUiUHlH;
      string QRLawIXYWl;
      string CSwmPWEJTF;
      if(BbhFVujDZs == MuzyyGGQNg){wLMsVNrGjn = true;}
      else if(MuzyyGGQNg == BbhFVujDZs){qqaBlXhDdh = true;}
      if(gqXRIRyMGq == gAfYQOISIN){yYDQVqInTc = true;}
      else if(gAfYQOISIN == gqXRIRyMGq){qSnNLLymDx = true;}
      if(yDdgNaXJMl == CtNJZMxkCx){twNgdlqGVx = true;}
      else if(CtNJZMxkCx == yDdgNaXJMl){QpCrJNlOZi = true;}
      if(gtIVCQbwkN == uPetFiIUYX){dKmfLEESEh = true;}
      else if(uPetFiIUYX == gtIVCQbwkN){wHHqJfjmLL = true;}
      if(jxnfMuwOpn == rSZGXRwfZb){PRnhncOfRX = true;}
      else if(rSZGXRwfZb == jxnfMuwOpn){eRRmVnjpIz = true;}
      if(IhJUixyAqu == BlqFXSgpXl){OQoqKzxfOi = true;}
      else if(BlqFXSgpXl == IhJUixyAqu){etxajAoiqX = true;}
      if(WaqmMmhBOr == IUOQlRVkSg){WljmKmlXEQ = true;}
      else if(IUOQlRVkSg == WaqmMmhBOr){lSculiKxDe = true;}
      if(oCasGBPyUS == FmskUiUHlH){lpikMcIerB = true;}
      if(eISXdyjnmF == QRLawIXYWl){XKnxiNVwVM = true;}
      if(RbEppJFASZ == CSwmPWEJTF){GYEULdgBXB = true;}
      while(FmskUiUHlH == oCasGBPyUS){bLbrRzXOWV = true;}
      while(QRLawIXYWl == QRLawIXYWl){cuFaDCJgGI = true;}
      while(CSwmPWEJTF == CSwmPWEJTF){qBumYMnWBl = true;}
      if(wLMsVNrGjn == true){wLMsVNrGjn = false;}
      if(yYDQVqInTc == true){yYDQVqInTc = false;}
      if(twNgdlqGVx == true){twNgdlqGVx = false;}
      if(dKmfLEESEh == true){dKmfLEESEh = false;}
      if(PRnhncOfRX == true){PRnhncOfRX = false;}
      if(OQoqKzxfOi == true){OQoqKzxfOi = false;}
      if(WljmKmlXEQ == true){WljmKmlXEQ = false;}
      if(lpikMcIerB == true){lpikMcIerB = false;}
      if(XKnxiNVwVM == true){XKnxiNVwVM = false;}
      if(GYEULdgBXB == true){GYEULdgBXB = false;}
      if(qqaBlXhDdh == true){qqaBlXhDdh = false;}
      if(qSnNLLymDx == true){qSnNLLymDx = false;}
      if(QpCrJNlOZi == true){QpCrJNlOZi = false;}
      if(wHHqJfjmLL == true){wHHqJfjmLL = false;}
      if(eRRmVnjpIz == true){eRRmVnjpIz = false;}
      if(etxajAoiqX == true){etxajAoiqX = false;}
      if(lSculiKxDe == true){lSculiKxDe = false;}
      if(bLbrRzXOWV == true){bLbrRzXOWV = false;}
      if(cuFaDCJgGI == true){cuFaDCJgGI = false;}
      if(qBumYMnWBl == true){qBumYMnWBl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNFVENUOVH
{ 
  void MQoIUfEigx()
  { 
      bool LAUVDLaaVu = false;
      bool nbKBuAHIeO = false;
      bool TzHNVYqgKM = false;
      bool YrpEmpFTqQ = false;
      bool QbLljBjXCp = false;
      bool VEeanLsHAd = false;
      bool TsQIVwkFOE = false;
      bool tmQNyrmUcT = false;
      bool nTeTqTMPPb = false;
      bool xxSMxWKDPn = false;
      bool QdJxwhnRbw = false;
      bool XXefpzOwRC = false;
      bool iVplHwUDPb = false;
      bool gjFnDKKgXJ = false;
      bool etmSEYSmWx = false;
      bool HOkNEunWpz = false;
      bool NkBAPmSpbe = false;
      bool ogYHWohWhh = false;
      bool dgfSTRzrjI = false;
      bool VmpXwtrmDQ = false;
      string zsjGyVoHYI;
      string eSDbhZWjxJ;
      string BVuegnIcsb;
      string KmTYHTzfQV;
      string hitZcIQfIr;
      string zbynWcxFYJ;
      string NMOwyryeUO;
      string ZpSbaSbVBY;
      string XcUAbhneBe;
      string VtHHIUTxak;
      string JlLsRJIWNE;
      string BbEAkkrNUP;
      string DTcorfhLSF;
      string yetPOlQaiS;
      string ZQRwdsoHVX;
      string cGcLhpIVAk;
      string axDHGVholz;
      string TReBolCfLz;
      string papucqChgY;
      string dtZxqcNJpH;
      if(zsjGyVoHYI == JlLsRJIWNE){LAUVDLaaVu = true;}
      else if(JlLsRJIWNE == zsjGyVoHYI){QdJxwhnRbw = true;}
      if(eSDbhZWjxJ == BbEAkkrNUP){nbKBuAHIeO = true;}
      else if(BbEAkkrNUP == eSDbhZWjxJ){XXefpzOwRC = true;}
      if(BVuegnIcsb == DTcorfhLSF){TzHNVYqgKM = true;}
      else if(DTcorfhLSF == BVuegnIcsb){iVplHwUDPb = true;}
      if(KmTYHTzfQV == yetPOlQaiS){YrpEmpFTqQ = true;}
      else if(yetPOlQaiS == KmTYHTzfQV){gjFnDKKgXJ = true;}
      if(hitZcIQfIr == ZQRwdsoHVX){QbLljBjXCp = true;}
      else if(ZQRwdsoHVX == hitZcIQfIr){etmSEYSmWx = true;}
      if(zbynWcxFYJ == cGcLhpIVAk){VEeanLsHAd = true;}
      else if(cGcLhpIVAk == zbynWcxFYJ){HOkNEunWpz = true;}
      if(NMOwyryeUO == axDHGVholz){TsQIVwkFOE = true;}
      else if(axDHGVholz == NMOwyryeUO){NkBAPmSpbe = true;}
      if(ZpSbaSbVBY == TReBolCfLz){tmQNyrmUcT = true;}
      if(XcUAbhneBe == papucqChgY){nTeTqTMPPb = true;}
      if(VtHHIUTxak == dtZxqcNJpH){xxSMxWKDPn = true;}
      while(TReBolCfLz == ZpSbaSbVBY){ogYHWohWhh = true;}
      while(papucqChgY == papucqChgY){dgfSTRzrjI = true;}
      while(dtZxqcNJpH == dtZxqcNJpH){VmpXwtrmDQ = true;}
      if(LAUVDLaaVu == true){LAUVDLaaVu = false;}
      if(nbKBuAHIeO == true){nbKBuAHIeO = false;}
      if(TzHNVYqgKM == true){TzHNVYqgKM = false;}
      if(YrpEmpFTqQ == true){YrpEmpFTqQ = false;}
      if(QbLljBjXCp == true){QbLljBjXCp = false;}
      if(VEeanLsHAd == true){VEeanLsHAd = false;}
      if(TsQIVwkFOE == true){TsQIVwkFOE = false;}
      if(tmQNyrmUcT == true){tmQNyrmUcT = false;}
      if(nTeTqTMPPb == true){nTeTqTMPPb = false;}
      if(xxSMxWKDPn == true){xxSMxWKDPn = false;}
      if(QdJxwhnRbw == true){QdJxwhnRbw = false;}
      if(XXefpzOwRC == true){XXefpzOwRC = false;}
      if(iVplHwUDPb == true){iVplHwUDPb = false;}
      if(gjFnDKKgXJ == true){gjFnDKKgXJ = false;}
      if(etmSEYSmWx == true){etmSEYSmWx = false;}
      if(HOkNEunWpz == true){HOkNEunWpz = false;}
      if(NkBAPmSpbe == true){NkBAPmSpbe = false;}
      if(ogYHWohWhh == true){ogYHWohWhh = false;}
      if(dgfSTRzrjI == true){dgfSTRzrjI = false;}
      if(VmpXwtrmDQ == true){VmpXwtrmDQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWXMFUSCPY
{ 
  void HUJHzuwPrb()
  { 
      bool IUUHczwTPo = false;
      bool JdctBGJIbG = false;
      bool gptTtjzNpN = false;
      bool wxqoGouBtr = false;
      bool oiEBEJiqnk = false;
      bool jYlidSaBNr = false;
      bool AhdCsMlmnM = false;
      bool LINjRxlrOk = false;
      bool AHZEcWKIKm = false;
      bool NtmBqGFBIr = false;
      bool XuDaZbKBRg = false;
      bool gilcqrIZYV = false;
      bool BccAzRUMrL = false;
      bool rjjWNFEzeB = false;
      bool MIqdGeIKKz = false;
      bool yfcmptSDbI = false;
      bool GyJFowyOOl = false;
      bool nJuXIslysU = false;
      bool JKBsNMHxgT = false;
      bool lBWVuOzkoK = false;
      string NVMIpftCuS;
      string KwJUNUcyeX;
      string dOgDqhadTo;
      string ReVfkKGndS;
      string fmHtmqFJsp;
      string glooTyoIRH;
      string EPiGAfaciD;
      string NoULrpHlPz;
      string bQkdHepfMm;
      string VyVVNPEBsH;
      string PcZpbqRcxd;
      string qCrRfneFyV;
      string ptQwhPTyxc;
      string kGrIjyptBP;
      string NMiiuSFDoZ;
      string jzCXRULdIL;
      string XSfTrjKjhg;
      string xkDhIcLhAO;
      string KQIWrkDTpO;
      string mMkortgOpL;
      if(NVMIpftCuS == PcZpbqRcxd){IUUHczwTPo = true;}
      else if(PcZpbqRcxd == NVMIpftCuS){XuDaZbKBRg = true;}
      if(KwJUNUcyeX == qCrRfneFyV){JdctBGJIbG = true;}
      else if(qCrRfneFyV == KwJUNUcyeX){gilcqrIZYV = true;}
      if(dOgDqhadTo == ptQwhPTyxc){gptTtjzNpN = true;}
      else if(ptQwhPTyxc == dOgDqhadTo){BccAzRUMrL = true;}
      if(ReVfkKGndS == kGrIjyptBP){wxqoGouBtr = true;}
      else if(kGrIjyptBP == ReVfkKGndS){rjjWNFEzeB = true;}
      if(fmHtmqFJsp == NMiiuSFDoZ){oiEBEJiqnk = true;}
      else if(NMiiuSFDoZ == fmHtmqFJsp){MIqdGeIKKz = true;}
      if(glooTyoIRH == jzCXRULdIL){jYlidSaBNr = true;}
      else if(jzCXRULdIL == glooTyoIRH){yfcmptSDbI = true;}
      if(EPiGAfaciD == XSfTrjKjhg){AhdCsMlmnM = true;}
      else if(XSfTrjKjhg == EPiGAfaciD){GyJFowyOOl = true;}
      if(NoULrpHlPz == xkDhIcLhAO){LINjRxlrOk = true;}
      if(bQkdHepfMm == KQIWrkDTpO){AHZEcWKIKm = true;}
      if(VyVVNPEBsH == mMkortgOpL){NtmBqGFBIr = true;}
      while(xkDhIcLhAO == NoULrpHlPz){nJuXIslysU = true;}
      while(KQIWrkDTpO == KQIWrkDTpO){JKBsNMHxgT = true;}
      while(mMkortgOpL == mMkortgOpL){lBWVuOzkoK = true;}
      if(IUUHczwTPo == true){IUUHczwTPo = false;}
      if(JdctBGJIbG == true){JdctBGJIbG = false;}
      if(gptTtjzNpN == true){gptTtjzNpN = false;}
      if(wxqoGouBtr == true){wxqoGouBtr = false;}
      if(oiEBEJiqnk == true){oiEBEJiqnk = false;}
      if(jYlidSaBNr == true){jYlidSaBNr = false;}
      if(AhdCsMlmnM == true){AhdCsMlmnM = false;}
      if(LINjRxlrOk == true){LINjRxlrOk = false;}
      if(AHZEcWKIKm == true){AHZEcWKIKm = false;}
      if(NtmBqGFBIr == true){NtmBqGFBIr = false;}
      if(XuDaZbKBRg == true){XuDaZbKBRg = false;}
      if(gilcqrIZYV == true){gilcqrIZYV = false;}
      if(BccAzRUMrL == true){BccAzRUMrL = false;}
      if(rjjWNFEzeB == true){rjjWNFEzeB = false;}
      if(MIqdGeIKKz == true){MIqdGeIKKz = false;}
      if(yfcmptSDbI == true){yfcmptSDbI = false;}
      if(GyJFowyOOl == true){GyJFowyOOl = false;}
      if(nJuXIslysU == true){nJuXIslysU = false;}
      if(JKBsNMHxgT == true){JKBsNMHxgT = false;}
      if(lBWVuOzkoK == true){lBWVuOzkoK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVNWBCXUPO
{ 
  void QRLFMjhLsb()
  { 
      bool XQpVXjkMFy = false;
      bool GDgaoFHEcO = false;
      bool tSCCtyULgp = false;
      bool VbeGJZaBaI = false;
      bool oJoyAbtWbY = false;
      bool igJOOENnaY = false;
      bool PZePbdXZRP = false;
      bool dGcUZjdEBS = false;
      bool DyiHHnSQrE = false;
      bool LmaCsPeYVW = false;
      bool DUFLucEnoe = false;
      bool ZJmHVRpXHm = false;
      bool LHhMEqeabJ = false;
      bool FEieOisWMe = false;
      bool jdbMeBzSfa = false;
      bool YGRhKwmsHD = false;
      bool xcMeZUaHrm = false;
      bool YTKbDgeUgC = false;
      bool qMtAkymATS = false;
      bool uAPIhHRwmK = false;
      string XBuVreKuqS;
      string XSlGBkuozB;
      string echrOuVHlj;
      string xkSKfBRrJF;
      string dztKosPLaE;
      string rdupLtSDGw;
      string IDJGVmAaZA;
      string TDftWfiWDU;
      string fJfhrSpbzk;
      string hOkMwapmoB;
      string snkakoyASf;
      string LwzkQyXaOC;
      string wXboSERSxw;
      string puhBbqYFxC;
      string UoJTYlOzuy;
      string DOYmFULwHf;
      string XeDWpQNyJZ;
      string ZScLgHOIPg;
      string pRWzsaWtwH;
      string ebxRepklcI;
      if(XBuVreKuqS == snkakoyASf){XQpVXjkMFy = true;}
      else if(snkakoyASf == XBuVreKuqS){DUFLucEnoe = true;}
      if(XSlGBkuozB == LwzkQyXaOC){GDgaoFHEcO = true;}
      else if(LwzkQyXaOC == XSlGBkuozB){ZJmHVRpXHm = true;}
      if(echrOuVHlj == wXboSERSxw){tSCCtyULgp = true;}
      else if(wXboSERSxw == echrOuVHlj){LHhMEqeabJ = true;}
      if(xkSKfBRrJF == puhBbqYFxC){VbeGJZaBaI = true;}
      else if(puhBbqYFxC == xkSKfBRrJF){FEieOisWMe = true;}
      if(dztKosPLaE == UoJTYlOzuy){oJoyAbtWbY = true;}
      else if(UoJTYlOzuy == dztKosPLaE){jdbMeBzSfa = true;}
      if(rdupLtSDGw == DOYmFULwHf){igJOOENnaY = true;}
      else if(DOYmFULwHf == rdupLtSDGw){YGRhKwmsHD = true;}
      if(IDJGVmAaZA == XeDWpQNyJZ){PZePbdXZRP = true;}
      else if(XeDWpQNyJZ == IDJGVmAaZA){xcMeZUaHrm = true;}
      if(TDftWfiWDU == ZScLgHOIPg){dGcUZjdEBS = true;}
      if(fJfhrSpbzk == pRWzsaWtwH){DyiHHnSQrE = true;}
      if(hOkMwapmoB == ebxRepklcI){LmaCsPeYVW = true;}
      while(ZScLgHOIPg == TDftWfiWDU){YTKbDgeUgC = true;}
      while(pRWzsaWtwH == pRWzsaWtwH){qMtAkymATS = true;}
      while(ebxRepklcI == ebxRepklcI){uAPIhHRwmK = true;}
      if(XQpVXjkMFy == true){XQpVXjkMFy = false;}
      if(GDgaoFHEcO == true){GDgaoFHEcO = false;}
      if(tSCCtyULgp == true){tSCCtyULgp = false;}
      if(VbeGJZaBaI == true){VbeGJZaBaI = false;}
      if(oJoyAbtWbY == true){oJoyAbtWbY = false;}
      if(igJOOENnaY == true){igJOOENnaY = false;}
      if(PZePbdXZRP == true){PZePbdXZRP = false;}
      if(dGcUZjdEBS == true){dGcUZjdEBS = false;}
      if(DyiHHnSQrE == true){DyiHHnSQrE = false;}
      if(LmaCsPeYVW == true){LmaCsPeYVW = false;}
      if(DUFLucEnoe == true){DUFLucEnoe = false;}
      if(ZJmHVRpXHm == true){ZJmHVRpXHm = false;}
      if(LHhMEqeabJ == true){LHhMEqeabJ = false;}
      if(FEieOisWMe == true){FEieOisWMe = false;}
      if(jdbMeBzSfa == true){jdbMeBzSfa = false;}
      if(YGRhKwmsHD == true){YGRhKwmsHD = false;}
      if(xcMeZUaHrm == true){xcMeZUaHrm = false;}
      if(YTKbDgeUgC == true){YTKbDgeUgC = false;}
      if(qMtAkymATS == true){qMtAkymATS = false;}
      if(uAPIhHRwmK == true){uAPIhHRwmK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTESZUVTLH
{ 
  void lJgKPFqiAI()
  { 
      bool XgBqajaWbV = false;
      bool qwVhiQIOBK = false;
      bool PCKPebVtyh = false;
      bool AUuNfjiRML = false;
      bool iRjTapRJuU = false;
      bool oxLERUVlMz = false;
      bool NfYsUWAICz = false;
      bool hqBoaxRqon = false;
      bool KLycsDJquK = false;
      bool OwENxCsqyD = false;
      bool pJHwmyuVcU = false;
      bool DdxXnBhuzR = false;
      bool NIMqkklnqY = false;
      bool EZrkyBECpu = false;
      bool HmOaHjzgYw = false;
      bool UxqgogwQLB = false;
      bool LGdEPckLYm = false;
      bool xeFEJatliA = false;
      bool lFPuDHhLwR = false;
      bool EnqniAIKKe = false;
      string irFuCyBOuQ;
      string oTNwuGSDaf;
      string BzgFOAZzeK;
      string STcGYhEoTi;
      string tmTEbHHWqA;
      string zSYbriLAgC;
      string XCikyUqHXN;
      string CciqkNfbcH;
      string rDIdKAuANo;
      string VDIRLqEhGG;
      string PAzdyVihpd;
      string CjWYJTsEZy;
      string ZqshqyTRes;
      string JxUWqrEeen;
      string QNJimlgiIq;
      string yzIIgYGQlA;
      string CRCwUEOAhQ;
      string POYkgLgKuE;
      string QkInuJoLoS;
      string lmrelyLMOh;
      if(irFuCyBOuQ == PAzdyVihpd){XgBqajaWbV = true;}
      else if(PAzdyVihpd == irFuCyBOuQ){pJHwmyuVcU = true;}
      if(oTNwuGSDaf == CjWYJTsEZy){qwVhiQIOBK = true;}
      else if(CjWYJTsEZy == oTNwuGSDaf){DdxXnBhuzR = true;}
      if(BzgFOAZzeK == ZqshqyTRes){PCKPebVtyh = true;}
      else if(ZqshqyTRes == BzgFOAZzeK){NIMqkklnqY = true;}
      if(STcGYhEoTi == JxUWqrEeen){AUuNfjiRML = true;}
      else if(JxUWqrEeen == STcGYhEoTi){EZrkyBECpu = true;}
      if(tmTEbHHWqA == QNJimlgiIq){iRjTapRJuU = true;}
      else if(QNJimlgiIq == tmTEbHHWqA){HmOaHjzgYw = true;}
      if(zSYbriLAgC == yzIIgYGQlA){oxLERUVlMz = true;}
      else if(yzIIgYGQlA == zSYbriLAgC){UxqgogwQLB = true;}
      if(XCikyUqHXN == CRCwUEOAhQ){NfYsUWAICz = true;}
      else if(CRCwUEOAhQ == XCikyUqHXN){LGdEPckLYm = true;}
      if(CciqkNfbcH == POYkgLgKuE){hqBoaxRqon = true;}
      if(rDIdKAuANo == QkInuJoLoS){KLycsDJquK = true;}
      if(VDIRLqEhGG == lmrelyLMOh){OwENxCsqyD = true;}
      while(POYkgLgKuE == CciqkNfbcH){xeFEJatliA = true;}
      while(QkInuJoLoS == QkInuJoLoS){lFPuDHhLwR = true;}
      while(lmrelyLMOh == lmrelyLMOh){EnqniAIKKe = true;}
      if(XgBqajaWbV == true){XgBqajaWbV = false;}
      if(qwVhiQIOBK == true){qwVhiQIOBK = false;}
      if(PCKPebVtyh == true){PCKPebVtyh = false;}
      if(AUuNfjiRML == true){AUuNfjiRML = false;}
      if(iRjTapRJuU == true){iRjTapRJuU = false;}
      if(oxLERUVlMz == true){oxLERUVlMz = false;}
      if(NfYsUWAICz == true){NfYsUWAICz = false;}
      if(hqBoaxRqon == true){hqBoaxRqon = false;}
      if(KLycsDJquK == true){KLycsDJquK = false;}
      if(OwENxCsqyD == true){OwENxCsqyD = false;}
      if(pJHwmyuVcU == true){pJHwmyuVcU = false;}
      if(DdxXnBhuzR == true){DdxXnBhuzR = false;}
      if(NIMqkklnqY == true){NIMqkklnqY = false;}
      if(EZrkyBECpu == true){EZrkyBECpu = false;}
      if(HmOaHjzgYw == true){HmOaHjzgYw = false;}
      if(UxqgogwQLB == true){UxqgogwQLB = false;}
      if(LGdEPckLYm == true){LGdEPckLYm = false;}
      if(xeFEJatliA == true){xeFEJatliA = false;}
      if(lFPuDHhLwR == true){lFPuDHhLwR = false;}
      if(EnqniAIKKe == true){EnqniAIKKe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSOVUCIRWZ
{ 
  void SmGNxRsBxU()
  { 
      bool EEbtbOyBMP = false;
      bool BqxYAEegaM = false;
      bool iALkIcaCyX = false;
      bool qtnKBIEHyo = false;
      bool ZEJQOZguug = false;
      bool YCQNkErqkz = false;
      bool nwCoXGDlWr = false;
      bool AXikmdptVi = false;
      bool ueHRyncaZx = false;
      bool PMVyAdCTrH = false;
      bool WtXCgBTfaH = false;
      bool NxUCEJokqj = false;
      bool dbMZcmBjjI = false;
      bool bVCNLAHEkx = false;
      bool TxARiRrTtq = false;
      bool oQcIdthxZs = false;
      bool ziuRfquGpD = false;
      bool CjAsPfbtpL = false;
      bool uhpsTKssjQ = false;
      bool SJeqxjChlq = false;
      string mNYyAHTOpl;
      string TJCtyguVra;
      string SPRakqVOZM;
      string jmeEOGKzdj;
      string IrZDrehxDs;
      string ruaMiWwyNI;
      string lEndBgdyfq;
      string VwqHRZoNhG;
      string IXLgUoLSVq;
      string JMkUxDEwCL;
      string AjQMWwDStI;
      string hhPHzNsHJM;
      string ULcngJKWKO;
      string VsLWFYGzJX;
      string ksXMJaxdUi;
      string JxmopoHceN;
      string kgIfloWrBa;
      string GtykbamPeF;
      string MgBaEYGWfQ;
      string RdTulEjraT;
      if(mNYyAHTOpl == AjQMWwDStI){EEbtbOyBMP = true;}
      else if(AjQMWwDStI == mNYyAHTOpl){WtXCgBTfaH = true;}
      if(TJCtyguVra == hhPHzNsHJM){BqxYAEegaM = true;}
      else if(hhPHzNsHJM == TJCtyguVra){NxUCEJokqj = true;}
      if(SPRakqVOZM == ULcngJKWKO){iALkIcaCyX = true;}
      else if(ULcngJKWKO == SPRakqVOZM){dbMZcmBjjI = true;}
      if(jmeEOGKzdj == VsLWFYGzJX){qtnKBIEHyo = true;}
      else if(VsLWFYGzJX == jmeEOGKzdj){bVCNLAHEkx = true;}
      if(IrZDrehxDs == ksXMJaxdUi){ZEJQOZguug = true;}
      else if(ksXMJaxdUi == IrZDrehxDs){TxARiRrTtq = true;}
      if(ruaMiWwyNI == JxmopoHceN){YCQNkErqkz = true;}
      else if(JxmopoHceN == ruaMiWwyNI){oQcIdthxZs = true;}
      if(lEndBgdyfq == kgIfloWrBa){nwCoXGDlWr = true;}
      else if(kgIfloWrBa == lEndBgdyfq){ziuRfquGpD = true;}
      if(VwqHRZoNhG == GtykbamPeF){AXikmdptVi = true;}
      if(IXLgUoLSVq == MgBaEYGWfQ){ueHRyncaZx = true;}
      if(JMkUxDEwCL == RdTulEjraT){PMVyAdCTrH = true;}
      while(GtykbamPeF == VwqHRZoNhG){CjAsPfbtpL = true;}
      while(MgBaEYGWfQ == MgBaEYGWfQ){uhpsTKssjQ = true;}
      while(RdTulEjraT == RdTulEjraT){SJeqxjChlq = true;}
      if(EEbtbOyBMP == true){EEbtbOyBMP = false;}
      if(BqxYAEegaM == true){BqxYAEegaM = false;}
      if(iALkIcaCyX == true){iALkIcaCyX = false;}
      if(qtnKBIEHyo == true){qtnKBIEHyo = false;}
      if(ZEJQOZguug == true){ZEJQOZguug = false;}
      if(YCQNkErqkz == true){YCQNkErqkz = false;}
      if(nwCoXGDlWr == true){nwCoXGDlWr = false;}
      if(AXikmdptVi == true){AXikmdptVi = false;}
      if(ueHRyncaZx == true){ueHRyncaZx = false;}
      if(PMVyAdCTrH == true){PMVyAdCTrH = false;}
      if(WtXCgBTfaH == true){WtXCgBTfaH = false;}
      if(NxUCEJokqj == true){NxUCEJokqj = false;}
      if(dbMZcmBjjI == true){dbMZcmBjjI = false;}
      if(bVCNLAHEkx == true){bVCNLAHEkx = false;}
      if(TxARiRrTtq == true){TxARiRrTtq = false;}
      if(oQcIdthxZs == true){oQcIdthxZs = false;}
      if(ziuRfquGpD == true){ziuRfquGpD = false;}
      if(CjAsPfbtpL == true){CjAsPfbtpL = false;}
      if(uhpsTKssjQ == true){uhpsTKssjQ = false;}
      if(SJeqxjChlq == true){SJeqxjChlq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOLUZKMLZT
{ 
  void QMTHALMQxL()
  { 
      bool WNYGcfTyCm = false;
      bool XjVIXqgGBT = false;
      bool zfJWOrdFTf = false;
      bool jBPnGSASiH = false;
      bool fxWnNHMJKU = false;
      bool KoPdspEBrk = false;
      bool CNeVCVUgBE = false;
      bool pNWsnBJUIG = false;
      bool fTtyUulkuQ = false;
      bool OyayFRSBkr = false;
      bool mfHGexRWpq = false;
      bool gislEiSgAH = false;
      bool jikkormYnV = false;
      bool iIjQTALnTX = false;
      bool cOuDieFnsV = false;
      bool zlAcHEtVQm = false;
      bool JshTIYybRE = false;
      bool WeMceUmgCJ = false;
      bool lyfRWwHHIO = false;
      bool GoWgOjgbuK = false;
      string zQFirhlUID;
      string AJoZZgXWNg;
      string aONPCaNiUx;
      string kJTNtkVzZi;
      string ijzPFHGDiw;
      string wqMETjCpfQ;
      string TDzKRqpaeo;
      string LYwdxqOxJu;
      string UJAXBtwOtJ;
      string heSIOfjnyO;
      string ReYtkWthHb;
      string VFfkwKCbJX;
      string tagVGfGmPR;
      string HZzucpkGmd;
      string zNHSncygMD;
      string cHdZTqyCmE;
      string QHSpTuFkIF;
      string ZwnfXfTNgd;
      string gYZMnzuYbk;
      string qhShMruRyr;
      if(zQFirhlUID == ReYtkWthHb){WNYGcfTyCm = true;}
      else if(ReYtkWthHb == zQFirhlUID){mfHGexRWpq = true;}
      if(AJoZZgXWNg == VFfkwKCbJX){XjVIXqgGBT = true;}
      else if(VFfkwKCbJX == AJoZZgXWNg){gislEiSgAH = true;}
      if(aONPCaNiUx == tagVGfGmPR){zfJWOrdFTf = true;}
      else if(tagVGfGmPR == aONPCaNiUx){jikkormYnV = true;}
      if(kJTNtkVzZi == HZzucpkGmd){jBPnGSASiH = true;}
      else if(HZzucpkGmd == kJTNtkVzZi){iIjQTALnTX = true;}
      if(ijzPFHGDiw == zNHSncygMD){fxWnNHMJKU = true;}
      else if(zNHSncygMD == ijzPFHGDiw){cOuDieFnsV = true;}
      if(wqMETjCpfQ == cHdZTqyCmE){KoPdspEBrk = true;}
      else if(cHdZTqyCmE == wqMETjCpfQ){zlAcHEtVQm = true;}
      if(TDzKRqpaeo == QHSpTuFkIF){CNeVCVUgBE = true;}
      else if(QHSpTuFkIF == TDzKRqpaeo){JshTIYybRE = true;}
      if(LYwdxqOxJu == ZwnfXfTNgd){pNWsnBJUIG = true;}
      if(UJAXBtwOtJ == gYZMnzuYbk){fTtyUulkuQ = true;}
      if(heSIOfjnyO == qhShMruRyr){OyayFRSBkr = true;}
      while(ZwnfXfTNgd == LYwdxqOxJu){WeMceUmgCJ = true;}
      while(gYZMnzuYbk == gYZMnzuYbk){lyfRWwHHIO = true;}
      while(qhShMruRyr == qhShMruRyr){GoWgOjgbuK = true;}
      if(WNYGcfTyCm == true){WNYGcfTyCm = false;}
      if(XjVIXqgGBT == true){XjVIXqgGBT = false;}
      if(zfJWOrdFTf == true){zfJWOrdFTf = false;}
      if(jBPnGSASiH == true){jBPnGSASiH = false;}
      if(fxWnNHMJKU == true){fxWnNHMJKU = false;}
      if(KoPdspEBrk == true){KoPdspEBrk = false;}
      if(CNeVCVUgBE == true){CNeVCVUgBE = false;}
      if(pNWsnBJUIG == true){pNWsnBJUIG = false;}
      if(fTtyUulkuQ == true){fTtyUulkuQ = false;}
      if(OyayFRSBkr == true){OyayFRSBkr = false;}
      if(mfHGexRWpq == true){mfHGexRWpq = false;}
      if(gislEiSgAH == true){gislEiSgAH = false;}
      if(jikkormYnV == true){jikkormYnV = false;}
      if(iIjQTALnTX == true){iIjQTALnTX = false;}
      if(cOuDieFnsV == true){cOuDieFnsV = false;}
      if(zlAcHEtVQm == true){zlAcHEtVQm = false;}
      if(JshTIYybRE == true){JshTIYybRE = false;}
      if(WeMceUmgCJ == true){WeMceUmgCJ = false;}
      if(lyfRWwHHIO == true){lyfRWwHHIO = false;}
      if(GoWgOjgbuK == true){GoWgOjgbuK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKYAKPKZSA
{ 
  void kIlzchVJGO()
  { 
      bool bLDueKSGDD = false;
      bool iOxuWjnaxQ = false;
      bool WdztqWYSbn = false;
      bool sdCFCmuyzT = false;
      bool IbqohTHOej = false;
      bool BVWPwxMJDI = false;
      bool lAdOJEMqsj = false;
      bool noacHumKLW = false;
      bool OKnrmXHlJE = false;
      bool ZltphIxbfd = false;
      bool GPUtuLtsHA = false;
      bool JCygsbLlbl = false;
      bool wZhnJCukuy = false;
      bool yLdgPyoswa = false;
      bool cOeItXmNwG = false;
      bool xKzshghgkr = false;
      bool PJyICyXRQt = false;
      bool lSoAJhuYtk = false;
      bool PhnnBmLkzi = false;
      bool QIIDKSPVFw = false;
      string qQBiZeiIBV;
      string KegRocBKzI;
      string cGIwxggaOt;
      string DalqBJoLUG;
      string VcNzWVukkO;
      string okinIjIElr;
      string yItHRjspPf;
      string nopslzrIZa;
      string lwozERqyhQ;
      string AjZbINiGgl;
      string cFUFazupBJ;
      string rzeKGBStCA;
      string ruHyeDPNkY;
      string QlamygajYF;
      string WBwYYAEPUG;
      string tnDgtgxWZW;
      string jgEbrFYrLZ;
      string aiVxdpyhZd;
      string zzsdebhtsR;
      string iEJCUowTfT;
      if(qQBiZeiIBV == cFUFazupBJ){bLDueKSGDD = true;}
      else if(cFUFazupBJ == qQBiZeiIBV){GPUtuLtsHA = true;}
      if(KegRocBKzI == rzeKGBStCA){iOxuWjnaxQ = true;}
      else if(rzeKGBStCA == KegRocBKzI){JCygsbLlbl = true;}
      if(cGIwxggaOt == ruHyeDPNkY){WdztqWYSbn = true;}
      else if(ruHyeDPNkY == cGIwxggaOt){wZhnJCukuy = true;}
      if(DalqBJoLUG == QlamygajYF){sdCFCmuyzT = true;}
      else if(QlamygajYF == DalqBJoLUG){yLdgPyoswa = true;}
      if(VcNzWVukkO == WBwYYAEPUG){IbqohTHOej = true;}
      else if(WBwYYAEPUG == VcNzWVukkO){cOeItXmNwG = true;}
      if(okinIjIElr == tnDgtgxWZW){BVWPwxMJDI = true;}
      else if(tnDgtgxWZW == okinIjIElr){xKzshghgkr = true;}
      if(yItHRjspPf == jgEbrFYrLZ){lAdOJEMqsj = true;}
      else if(jgEbrFYrLZ == yItHRjspPf){PJyICyXRQt = true;}
      if(nopslzrIZa == aiVxdpyhZd){noacHumKLW = true;}
      if(lwozERqyhQ == zzsdebhtsR){OKnrmXHlJE = true;}
      if(AjZbINiGgl == iEJCUowTfT){ZltphIxbfd = true;}
      while(aiVxdpyhZd == nopslzrIZa){lSoAJhuYtk = true;}
      while(zzsdebhtsR == zzsdebhtsR){PhnnBmLkzi = true;}
      while(iEJCUowTfT == iEJCUowTfT){QIIDKSPVFw = true;}
      if(bLDueKSGDD == true){bLDueKSGDD = false;}
      if(iOxuWjnaxQ == true){iOxuWjnaxQ = false;}
      if(WdztqWYSbn == true){WdztqWYSbn = false;}
      if(sdCFCmuyzT == true){sdCFCmuyzT = false;}
      if(IbqohTHOej == true){IbqohTHOej = false;}
      if(BVWPwxMJDI == true){BVWPwxMJDI = false;}
      if(lAdOJEMqsj == true){lAdOJEMqsj = false;}
      if(noacHumKLW == true){noacHumKLW = false;}
      if(OKnrmXHlJE == true){OKnrmXHlJE = false;}
      if(ZltphIxbfd == true){ZltphIxbfd = false;}
      if(GPUtuLtsHA == true){GPUtuLtsHA = false;}
      if(JCygsbLlbl == true){JCygsbLlbl = false;}
      if(wZhnJCukuy == true){wZhnJCukuy = false;}
      if(yLdgPyoswa == true){yLdgPyoswa = false;}
      if(cOeItXmNwG == true){cOeItXmNwG = false;}
      if(xKzshghgkr == true){xKzshghgkr = false;}
      if(PJyICyXRQt == true){PJyICyXRQt = false;}
      if(lSoAJhuYtk == true){lSoAJhuYtk = false;}
      if(PhnnBmLkzi == true){PhnnBmLkzi = false;}
      if(QIIDKSPVFw == true){QIIDKSPVFw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZNCJNCKDW
{ 
  void uSVwCIURBg()
  { 
      bool KWVhCwWXeX = false;
      bool XFoEHAEMtZ = false;
      bool aiYMVIkWMT = false;
      bool BQrTYWyMiN = false;
      bool SNeepgjmjc = false;
      bool GKPhrayJMt = false;
      bool KALLWGNVej = false;
      bool BrdgGNEsVo = false;
      bool XxliMqBKay = false;
      bool YoAnCSBTIj = false;
      bool SOHAaOgiae = false;
      bool WEnWWMObyf = false;
      bool EDugLMqodn = false;
      bool LkklVJplHy = false;
      bool KSiubTAcRp = false;
      bool EZUcePSanO = false;
      bool WqFlTlTCBM = false;
      bool WbTzUlTzFq = false;
      bool LOWmjlPHHF = false;
      bool pOxsbSNwbo = false;
      string ktYYRpFrCA;
      string etRNHIjxxP;
      string IZKJgrFnyc;
      string MyEcCCoeSG;
      string ymZnUdTGgL;
      string rPKDMLjPrZ;
      string jQtYmfonKF;
      string SFdqQUAVnC;
      string XzHlkwmAPq;
      string RZmrVhsBBo;
      string newbsmkSmq;
      string LNaoBkIHmp;
      string roYSmrRkVi;
      string byUzOsCfsy;
      string LUNXfDyxpj;
      string YlNKwzGcnA;
      string UzxEPMsbaI;
      string hcOoeXaAmi;
      string sUukJpkJDO;
      string mZqrcLWJHT;
      if(ktYYRpFrCA == newbsmkSmq){KWVhCwWXeX = true;}
      else if(newbsmkSmq == ktYYRpFrCA){SOHAaOgiae = true;}
      if(etRNHIjxxP == LNaoBkIHmp){XFoEHAEMtZ = true;}
      else if(LNaoBkIHmp == etRNHIjxxP){WEnWWMObyf = true;}
      if(IZKJgrFnyc == roYSmrRkVi){aiYMVIkWMT = true;}
      else if(roYSmrRkVi == IZKJgrFnyc){EDugLMqodn = true;}
      if(MyEcCCoeSG == byUzOsCfsy){BQrTYWyMiN = true;}
      else if(byUzOsCfsy == MyEcCCoeSG){LkklVJplHy = true;}
      if(ymZnUdTGgL == LUNXfDyxpj){SNeepgjmjc = true;}
      else if(LUNXfDyxpj == ymZnUdTGgL){KSiubTAcRp = true;}
      if(rPKDMLjPrZ == YlNKwzGcnA){GKPhrayJMt = true;}
      else if(YlNKwzGcnA == rPKDMLjPrZ){EZUcePSanO = true;}
      if(jQtYmfonKF == UzxEPMsbaI){KALLWGNVej = true;}
      else if(UzxEPMsbaI == jQtYmfonKF){WqFlTlTCBM = true;}
      if(SFdqQUAVnC == hcOoeXaAmi){BrdgGNEsVo = true;}
      if(XzHlkwmAPq == sUukJpkJDO){XxliMqBKay = true;}
      if(RZmrVhsBBo == mZqrcLWJHT){YoAnCSBTIj = true;}
      while(hcOoeXaAmi == SFdqQUAVnC){WbTzUlTzFq = true;}
      while(sUukJpkJDO == sUukJpkJDO){LOWmjlPHHF = true;}
      while(mZqrcLWJHT == mZqrcLWJHT){pOxsbSNwbo = true;}
      if(KWVhCwWXeX == true){KWVhCwWXeX = false;}
      if(XFoEHAEMtZ == true){XFoEHAEMtZ = false;}
      if(aiYMVIkWMT == true){aiYMVIkWMT = false;}
      if(BQrTYWyMiN == true){BQrTYWyMiN = false;}
      if(SNeepgjmjc == true){SNeepgjmjc = false;}
      if(GKPhrayJMt == true){GKPhrayJMt = false;}
      if(KALLWGNVej == true){KALLWGNVej = false;}
      if(BrdgGNEsVo == true){BrdgGNEsVo = false;}
      if(XxliMqBKay == true){XxliMqBKay = false;}
      if(YoAnCSBTIj == true){YoAnCSBTIj = false;}
      if(SOHAaOgiae == true){SOHAaOgiae = false;}
      if(WEnWWMObyf == true){WEnWWMObyf = false;}
      if(EDugLMqodn == true){EDugLMqodn = false;}
      if(LkklVJplHy == true){LkklVJplHy = false;}
      if(KSiubTAcRp == true){KSiubTAcRp = false;}
      if(EZUcePSanO == true){EZUcePSanO = false;}
      if(WqFlTlTCBM == true){WqFlTlTCBM = false;}
      if(WbTzUlTzFq == true){WbTzUlTzFq = false;}
      if(LOWmjlPHHF == true){LOWmjlPHHF = false;}
      if(pOxsbSNwbo == true){pOxsbSNwbo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDJPAQGTLV
{ 
  void mXGtZubKTk()
  { 
      bool LGdmabyVKR = false;
      bool aIiTykBbBo = false;
      bool BERdyQPFkw = false;
      bool SoAkqnSMcY = false;
      bool PMSnVTcChR = false;
      bool ErEuoHnzoK = false;
      bool LrkOzkIxbJ = false;
      bool SnzcYnkdHd = false;
      bool mMXSrZjEwj = false;
      bool zSWSMWbEnj = false;
      bool LfaXyQsbVA = false;
      bool VKqLWyURVY = false;
      bool BDBqJzQfPC = false;
      bool MgoWSHlzTa = false;
      bool fIiuOoaLuO = false;
      bool CJhPiHdjNz = false;
      bool ANLTnoUUsP = false;
      bool MUxurrUGcT = false;
      bool YEkBzDzZnK = false;
      bool cCkUaSwOGY = false;
      string NNcBAftAFD;
      string ceqLarzazt;
      string rHXlHPyAxJ;
      string StzfHJFwyl;
      string myeIdJaPlF;
      string ntCYsFoqtk;
      string hsDujhfKDR;
      string mDbMHscPHy;
      string nhNqVYrZmC;
      string TNBMDsujXw;
      string cQLURjRpQA;
      string cZiwxzeLZK;
      string pFXBxYCPIO;
      string xsqLUWWsYk;
      string HCJlZtdFOE;
      string NjKNFXsKWs;
      string hBgCCjhXaa;
      string cllnCnwkaD;
      string twAEANidFx;
      string cMVfDFUGjp;
      if(NNcBAftAFD == cQLURjRpQA){LGdmabyVKR = true;}
      else if(cQLURjRpQA == NNcBAftAFD){LfaXyQsbVA = true;}
      if(ceqLarzazt == cZiwxzeLZK){aIiTykBbBo = true;}
      else if(cZiwxzeLZK == ceqLarzazt){VKqLWyURVY = true;}
      if(rHXlHPyAxJ == pFXBxYCPIO){BERdyQPFkw = true;}
      else if(pFXBxYCPIO == rHXlHPyAxJ){BDBqJzQfPC = true;}
      if(StzfHJFwyl == xsqLUWWsYk){SoAkqnSMcY = true;}
      else if(xsqLUWWsYk == StzfHJFwyl){MgoWSHlzTa = true;}
      if(myeIdJaPlF == HCJlZtdFOE){PMSnVTcChR = true;}
      else if(HCJlZtdFOE == myeIdJaPlF){fIiuOoaLuO = true;}
      if(ntCYsFoqtk == NjKNFXsKWs){ErEuoHnzoK = true;}
      else if(NjKNFXsKWs == ntCYsFoqtk){CJhPiHdjNz = true;}
      if(hsDujhfKDR == hBgCCjhXaa){LrkOzkIxbJ = true;}
      else if(hBgCCjhXaa == hsDujhfKDR){ANLTnoUUsP = true;}
      if(mDbMHscPHy == cllnCnwkaD){SnzcYnkdHd = true;}
      if(nhNqVYrZmC == twAEANidFx){mMXSrZjEwj = true;}
      if(TNBMDsujXw == cMVfDFUGjp){zSWSMWbEnj = true;}
      while(cllnCnwkaD == mDbMHscPHy){MUxurrUGcT = true;}
      while(twAEANidFx == twAEANidFx){YEkBzDzZnK = true;}
      while(cMVfDFUGjp == cMVfDFUGjp){cCkUaSwOGY = true;}
      if(LGdmabyVKR == true){LGdmabyVKR = false;}
      if(aIiTykBbBo == true){aIiTykBbBo = false;}
      if(BERdyQPFkw == true){BERdyQPFkw = false;}
      if(SoAkqnSMcY == true){SoAkqnSMcY = false;}
      if(PMSnVTcChR == true){PMSnVTcChR = false;}
      if(ErEuoHnzoK == true){ErEuoHnzoK = false;}
      if(LrkOzkIxbJ == true){LrkOzkIxbJ = false;}
      if(SnzcYnkdHd == true){SnzcYnkdHd = false;}
      if(mMXSrZjEwj == true){mMXSrZjEwj = false;}
      if(zSWSMWbEnj == true){zSWSMWbEnj = false;}
      if(LfaXyQsbVA == true){LfaXyQsbVA = false;}
      if(VKqLWyURVY == true){VKqLWyURVY = false;}
      if(BDBqJzQfPC == true){BDBqJzQfPC = false;}
      if(MgoWSHlzTa == true){MgoWSHlzTa = false;}
      if(fIiuOoaLuO == true){fIiuOoaLuO = false;}
      if(CJhPiHdjNz == true){CJhPiHdjNz = false;}
      if(ANLTnoUUsP == true){ANLTnoUUsP = false;}
      if(MUxurrUGcT == true){MUxurrUGcT = false;}
      if(YEkBzDzZnK == true){YEkBzDzZnK = false;}
      if(cCkUaSwOGY == true){cCkUaSwOGY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMYAADGJZZ
{ 
  void CnbKtdryxL()
  { 
      bool LczLwptYru = false;
      bool gNweAZLnFb = false;
      bool SVCjYXdXzD = false;
      bool tDXTilrGJG = false;
      bool UHZOBPwaHl = false;
      bool NTTdKoaPmX = false;
      bool LWZoBdpcwN = false;
      bool gEezGKwmhJ = false;
      bool bDPMpaisIt = false;
      bool KcTktygkNX = false;
      bool YTesFIoUWz = false;
      bool rngdwIGNzZ = false;
      bool twTCCDjsEI = false;
      bool dKYJjIXWGg = false;
      bool kOWIBWwpol = false;
      bool qSlndbzcpB = false;
      bool YuQOVgPXsm = false;
      bool jjGRneZLAf = false;
      bool HtDRQKYkeH = false;
      bool IufEIpyIlT = false;
      string SQfmhsPaNt;
      string fylSYVeVAd;
      string kKtrXSnugS;
      string wJsdAABrBT;
      string MUTCbSckto;
      string NfsqyHVmPO;
      string FTstyWFISY;
      string TlTgQQqrPF;
      string pDBrFQPBfs;
      string dNbmNsaZDF;
      string MURUUaLMZg;
      string QdXKYBRBoh;
      string GDbYuFJgSX;
      string oRnKrVkgWd;
      string EDaybApROM;
      string aYjVzJrsZP;
      string RetCrzoNSC;
      string QkeLcDbdwt;
      string PrSFwPgSKi;
      string drGHLZIYGc;
      if(SQfmhsPaNt == MURUUaLMZg){LczLwptYru = true;}
      else if(MURUUaLMZg == SQfmhsPaNt){YTesFIoUWz = true;}
      if(fylSYVeVAd == QdXKYBRBoh){gNweAZLnFb = true;}
      else if(QdXKYBRBoh == fylSYVeVAd){rngdwIGNzZ = true;}
      if(kKtrXSnugS == GDbYuFJgSX){SVCjYXdXzD = true;}
      else if(GDbYuFJgSX == kKtrXSnugS){twTCCDjsEI = true;}
      if(wJsdAABrBT == oRnKrVkgWd){tDXTilrGJG = true;}
      else if(oRnKrVkgWd == wJsdAABrBT){dKYJjIXWGg = true;}
      if(MUTCbSckto == EDaybApROM){UHZOBPwaHl = true;}
      else if(EDaybApROM == MUTCbSckto){kOWIBWwpol = true;}
      if(NfsqyHVmPO == aYjVzJrsZP){NTTdKoaPmX = true;}
      else if(aYjVzJrsZP == NfsqyHVmPO){qSlndbzcpB = true;}
      if(FTstyWFISY == RetCrzoNSC){LWZoBdpcwN = true;}
      else if(RetCrzoNSC == FTstyWFISY){YuQOVgPXsm = true;}
      if(TlTgQQqrPF == QkeLcDbdwt){gEezGKwmhJ = true;}
      if(pDBrFQPBfs == PrSFwPgSKi){bDPMpaisIt = true;}
      if(dNbmNsaZDF == drGHLZIYGc){KcTktygkNX = true;}
      while(QkeLcDbdwt == TlTgQQqrPF){jjGRneZLAf = true;}
      while(PrSFwPgSKi == PrSFwPgSKi){HtDRQKYkeH = true;}
      while(drGHLZIYGc == drGHLZIYGc){IufEIpyIlT = true;}
      if(LczLwptYru == true){LczLwptYru = false;}
      if(gNweAZLnFb == true){gNweAZLnFb = false;}
      if(SVCjYXdXzD == true){SVCjYXdXzD = false;}
      if(tDXTilrGJG == true){tDXTilrGJG = false;}
      if(UHZOBPwaHl == true){UHZOBPwaHl = false;}
      if(NTTdKoaPmX == true){NTTdKoaPmX = false;}
      if(LWZoBdpcwN == true){LWZoBdpcwN = false;}
      if(gEezGKwmhJ == true){gEezGKwmhJ = false;}
      if(bDPMpaisIt == true){bDPMpaisIt = false;}
      if(KcTktygkNX == true){KcTktygkNX = false;}
      if(YTesFIoUWz == true){YTesFIoUWz = false;}
      if(rngdwIGNzZ == true){rngdwIGNzZ = false;}
      if(twTCCDjsEI == true){twTCCDjsEI = false;}
      if(dKYJjIXWGg == true){dKYJjIXWGg = false;}
      if(kOWIBWwpol == true){kOWIBWwpol = false;}
      if(qSlndbzcpB == true){qSlndbzcpB = false;}
      if(YuQOVgPXsm == true){YuQOVgPXsm = false;}
      if(jjGRneZLAf == true){jjGRneZLAf = false;}
      if(HtDRQKYkeH == true){HtDRQKYkeH = false;}
      if(IufEIpyIlT == true){IufEIpyIlT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKGJQXEZHS
{ 
  void IbFuRBIbbc()
  { 
      bool YAiplfCSBJ = false;
      bool cVuAknNWGN = false;
      bool xpFDHceCuY = false;
      bool LEeZwWdshs = false;
      bool tJDSMYxaSt = false;
      bool ciiMFhufhJ = false;
      bool AzXcxXpUEO = false;
      bool KToNSnllqi = false;
      bool eEjAwcVRTN = false;
      bool axKYrulaUn = false;
      bool hbVEjItVsR = false;
      bool wIozdwPWgT = false;
      bool BYBqmMJPUX = false;
      bool CLRCACheQm = false;
      bool iAXCRSILtw = false;
      bool ePsAmJaeQW = false;
      bool zdAVPjqmza = false;
      bool OjFskBAzZU = false;
      bool ExVYsmRQOp = false;
      bool bCOtnEzClg = false;
      string huEbYBRHlH;
      string orKDfZLbBJ;
      string MtiWVJQCMr;
      string mHLLRBBnge;
      string GZGpZUTRrl;
      string PVpwGmMhGO;
      string kOusUhfyle;
      string YWuVDmmrwB;
      string pyKacQRPFd;
      string nThRtqeNVr;
      string nUfMNraTsS;
      string ATkFYmEUPE;
      string PQsHpEocbM;
      string HZWEMVRxMk;
      string oxVmdUhbsH;
      string lKxQbWbYVI;
      string CyqgLZwgrC;
      string UGHdPStFdU;
      string WNjUZxbFbo;
      string trbEipGoaD;
      if(huEbYBRHlH == nUfMNraTsS){YAiplfCSBJ = true;}
      else if(nUfMNraTsS == huEbYBRHlH){hbVEjItVsR = true;}
      if(orKDfZLbBJ == ATkFYmEUPE){cVuAknNWGN = true;}
      else if(ATkFYmEUPE == orKDfZLbBJ){wIozdwPWgT = true;}
      if(MtiWVJQCMr == PQsHpEocbM){xpFDHceCuY = true;}
      else if(PQsHpEocbM == MtiWVJQCMr){BYBqmMJPUX = true;}
      if(mHLLRBBnge == HZWEMVRxMk){LEeZwWdshs = true;}
      else if(HZWEMVRxMk == mHLLRBBnge){CLRCACheQm = true;}
      if(GZGpZUTRrl == oxVmdUhbsH){tJDSMYxaSt = true;}
      else if(oxVmdUhbsH == GZGpZUTRrl){iAXCRSILtw = true;}
      if(PVpwGmMhGO == lKxQbWbYVI){ciiMFhufhJ = true;}
      else if(lKxQbWbYVI == PVpwGmMhGO){ePsAmJaeQW = true;}
      if(kOusUhfyle == CyqgLZwgrC){AzXcxXpUEO = true;}
      else if(CyqgLZwgrC == kOusUhfyle){zdAVPjqmza = true;}
      if(YWuVDmmrwB == UGHdPStFdU){KToNSnllqi = true;}
      if(pyKacQRPFd == WNjUZxbFbo){eEjAwcVRTN = true;}
      if(nThRtqeNVr == trbEipGoaD){axKYrulaUn = true;}
      while(UGHdPStFdU == YWuVDmmrwB){OjFskBAzZU = true;}
      while(WNjUZxbFbo == WNjUZxbFbo){ExVYsmRQOp = true;}
      while(trbEipGoaD == trbEipGoaD){bCOtnEzClg = true;}
      if(YAiplfCSBJ == true){YAiplfCSBJ = false;}
      if(cVuAknNWGN == true){cVuAknNWGN = false;}
      if(xpFDHceCuY == true){xpFDHceCuY = false;}
      if(LEeZwWdshs == true){LEeZwWdshs = false;}
      if(tJDSMYxaSt == true){tJDSMYxaSt = false;}
      if(ciiMFhufhJ == true){ciiMFhufhJ = false;}
      if(AzXcxXpUEO == true){AzXcxXpUEO = false;}
      if(KToNSnllqi == true){KToNSnllqi = false;}
      if(eEjAwcVRTN == true){eEjAwcVRTN = false;}
      if(axKYrulaUn == true){axKYrulaUn = false;}
      if(hbVEjItVsR == true){hbVEjItVsR = false;}
      if(wIozdwPWgT == true){wIozdwPWgT = false;}
      if(BYBqmMJPUX == true){BYBqmMJPUX = false;}
      if(CLRCACheQm == true){CLRCACheQm = false;}
      if(iAXCRSILtw == true){iAXCRSILtw = false;}
      if(ePsAmJaeQW == true){ePsAmJaeQW = false;}
      if(zdAVPjqmza == true){zdAVPjqmza = false;}
      if(OjFskBAzZU == true){OjFskBAzZU = false;}
      if(ExVYsmRQOp == true){ExVYsmRQOp = false;}
      if(bCOtnEzClg == true){bCOtnEzClg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEQVHODPFM
{ 
  void KAifgaYCgz()
  { 
      bool YkJeXugMWe = false;
      bool HIXqSrUUEy = false;
      bool TPoMfOMELw = false;
      bool LJinprlGNh = false;
      bool opHYTyqorf = false;
      bool NYZghIuwyJ = false;
      bool hbAaTyYjBZ = false;
      bool GNHVIcIQsg = false;
      bool WXMfhljCFh = false;
      bool xpHDANogEU = false;
      bool YHnSZzQDYF = false;
      bool zeCRmKPUrg = false;
      bool OWdTbPGEVt = false;
      bool mbLXHOjtGh = false;
      bool UfdAhSmoPo = false;
      bool yUnXGCdUpJ = false;
      bool rMhdRXTdJY = false;
      bool aUOJLhrckJ = false;
      bool cQnfwSmnRE = false;
      bool jPDwpIxzhK = false;
      string KIhFpNAVhI;
      string rTUcsxpHbV;
      string opiUbGwqmk;
      string sqFQQSamTb;
      string fBripJpoOb;
      string mwuqbUZMci;
      string QJhwPBNDLa;
      string WDmApmxzdS;
      string QHbLxwuNow;
      string rNJjLWTwTo;
      string ulcnEjIuBo;
      string XZhKRIgWyS;
      string FAOOhItDnS;
      string TAfnWedmGN;
      string nAMAYSeyRC;
      string owxBjuWOGw;
      string oFGhUWttnm;
      string dtPjeEnOpO;
      string dwkkdWDdEa;
      string HPgKYhsdeB;
      if(KIhFpNAVhI == ulcnEjIuBo){YkJeXugMWe = true;}
      else if(ulcnEjIuBo == KIhFpNAVhI){YHnSZzQDYF = true;}
      if(rTUcsxpHbV == XZhKRIgWyS){HIXqSrUUEy = true;}
      else if(XZhKRIgWyS == rTUcsxpHbV){zeCRmKPUrg = true;}
      if(opiUbGwqmk == FAOOhItDnS){TPoMfOMELw = true;}
      else if(FAOOhItDnS == opiUbGwqmk){OWdTbPGEVt = true;}
      if(sqFQQSamTb == TAfnWedmGN){LJinprlGNh = true;}
      else if(TAfnWedmGN == sqFQQSamTb){mbLXHOjtGh = true;}
      if(fBripJpoOb == nAMAYSeyRC){opHYTyqorf = true;}
      else if(nAMAYSeyRC == fBripJpoOb){UfdAhSmoPo = true;}
      if(mwuqbUZMci == owxBjuWOGw){NYZghIuwyJ = true;}
      else if(owxBjuWOGw == mwuqbUZMci){yUnXGCdUpJ = true;}
      if(QJhwPBNDLa == oFGhUWttnm){hbAaTyYjBZ = true;}
      else if(oFGhUWttnm == QJhwPBNDLa){rMhdRXTdJY = true;}
      if(WDmApmxzdS == dtPjeEnOpO){GNHVIcIQsg = true;}
      if(QHbLxwuNow == dwkkdWDdEa){WXMfhljCFh = true;}
      if(rNJjLWTwTo == HPgKYhsdeB){xpHDANogEU = true;}
      while(dtPjeEnOpO == WDmApmxzdS){aUOJLhrckJ = true;}
      while(dwkkdWDdEa == dwkkdWDdEa){cQnfwSmnRE = true;}
      while(HPgKYhsdeB == HPgKYhsdeB){jPDwpIxzhK = true;}
      if(YkJeXugMWe == true){YkJeXugMWe = false;}
      if(HIXqSrUUEy == true){HIXqSrUUEy = false;}
      if(TPoMfOMELw == true){TPoMfOMELw = false;}
      if(LJinprlGNh == true){LJinprlGNh = false;}
      if(opHYTyqorf == true){opHYTyqorf = false;}
      if(NYZghIuwyJ == true){NYZghIuwyJ = false;}
      if(hbAaTyYjBZ == true){hbAaTyYjBZ = false;}
      if(GNHVIcIQsg == true){GNHVIcIQsg = false;}
      if(WXMfhljCFh == true){WXMfhljCFh = false;}
      if(xpHDANogEU == true){xpHDANogEU = false;}
      if(YHnSZzQDYF == true){YHnSZzQDYF = false;}
      if(zeCRmKPUrg == true){zeCRmKPUrg = false;}
      if(OWdTbPGEVt == true){OWdTbPGEVt = false;}
      if(mbLXHOjtGh == true){mbLXHOjtGh = false;}
      if(UfdAhSmoPo == true){UfdAhSmoPo = false;}
      if(yUnXGCdUpJ == true){yUnXGCdUpJ = false;}
      if(rMhdRXTdJY == true){rMhdRXTdJY = false;}
      if(aUOJLhrckJ == true){aUOJLhrckJ = false;}
      if(cQnfwSmnRE == true){cQnfwSmnRE = false;}
      if(jPDwpIxzhK == true){jPDwpIxzhK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTBLQRWPVP
{ 
  void rhVLzPeBoB()
  { 
      bool BLBEOAjnec = false;
      bool qaePGAWlPq = false;
      bool ePHtRQOAFW = false;
      bool wgdFHdhXMU = false;
      bool WOpzRbEtPB = false;
      bool ztAlhlDGmy = false;
      bool ljhIgJxYIc = false;
      bool RyYtTPZHbp = false;
      bool LTjDWCgqXU = false;
      bool ZbkOilggSI = false;
      bool delmiAVGRR = false;
      bool LudwlSAdld = false;
      bool bFBmCpMJKg = false;
      bool isoSLfhwTV = false;
      bool fZZFJdxncQ = false;
      bool lCunfXdyjs = false;
      bool nLujhRGKkF = false;
      bool jDJPxCfucY = false;
      bool sXgtugyAmn = false;
      bool CiMahUdoXq = false;
      string LLuoylAlkj;
      string VVmurHmPZT;
      string BmBMDqEose;
      string AyoOBcBrjg;
      string rpxVASoHkp;
      string TeyHYXKhkG;
      string gLsGiWfYsO;
      string GteraLpfMj;
      string BxECLVAgod;
      string SSGdAfxqlc;
      string mQNVjYAGfN;
      string heVBFjHptN;
      string WyiPwmnBru;
      string OzsjxkiiSl;
      string UtBbumxEYP;
      string YHwXGnhyYw;
      string jzNkyhkkDT;
      string BXWIrcxGTJ;
      string pibbVHDUcI;
      string CjJWCVfPcN;
      if(LLuoylAlkj == mQNVjYAGfN){BLBEOAjnec = true;}
      else if(mQNVjYAGfN == LLuoylAlkj){delmiAVGRR = true;}
      if(VVmurHmPZT == heVBFjHptN){qaePGAWlPq = true;}
      else if(heVBFjHptN == VVmurHmPZT){LudwlSAdld = true;}
      if(BmBMDqEose == WyiPwmnBru){ePHtRQOAFW = true;}
      else if(WyiPwmnBru == BmBMDqEose){bFBmCpMJKg = true;}
      if(AyoOBcBrjg == OzsjxkiiSl){wgdFHdhXMU = true;}
      else if(OzsjxkiiSl == AyoOBcBrjg){isoSLfhwTV = true;}
      if(rpxVASoHkp == UtBbumxEYP){WOpzRbEtPB = true;}
      else if(UtBbumxEYP == rpxVASoHkp){fZZFJdxncQ = true;}
      if(TeyHYXKhkG == YHwXGnhyYw){ztAlhlDGmy = true;}
      else if(YHwXGnhyYw == TeyHYXKhkG){lCunfXdyjs = true;}
      if(gLsGiWfYsO == jzNkyhkkDT){ljhIgJxYIc = true;}
      else if(jzNkyhkkDT == gLsGiWfYsO){nLujhRGKkF = true;}
      if(GteraLpfMj == BXWIrcxGTJ){RyYtTPZHbp = true;}
      if(BxECLVAgod == pibbVHDUcI){LTjDWCgqXU = true;}
      if(SSGdAfxqlc == CjJWCVfPcN){ZbkOilggSI = true;}
      while(BXWIrcxGTJ == GteraLpfMj){jDJPxCfucY = true;}
      while(pibbVHDUcI == pibbVHDUcI){sXgtugyAmn = true;}
      while(CjJWCVfPcN == CjJWCVfPcN){CiMahUdoXq = true;}
      if(BLBEOAjnec == true){BLBEOAjnec = false;}
      if(qaePGAWlPq == true){qaePGAWlPq = false;}
      if(ePHtRQOAFW == true){ePHtRQOAFW = false;}
      if(wgdFHdhXMU == true){wgdFHdhXMU = false;}
      if(WOpzRbEtPB == true){WOpzRbEtPB = false;}
      if(ztAlhlDGmy == true){ztAlhlDGmy = false;}
      if(ljhIgJxYIc == true){ljhIgJxYIc = false;}
      if(RyYtTPZHbp == true){RyYtTPZHbp = false;}
      if(LTjDWCgqXU == true){LTjDWCgqXU = false;}
      if(ZbkOilggSI == true){ZbkOilggSI = false;}
      if(delmiAVGRR == true){delmiAVGRR = false;}
      if(LudwlSAdld == true){LudwlSAdld = false;}
      if(bFBmCpMJKg == true){bFBmCpMJKg = false;}
      if(isoSLfhwTV == true){isoSLfhwTV = false;}
      if(fZZFJdxncQ == true){fZZFJdxncQ = false;}
      if(lCunfXdyjs == true){lCunfXdyjs = false;}
      if(nLujhRGKkF == true){nLujhRGKkF = false;}
      if(jDJPxCfucY == true){jDJPxCfucY = false;}
      if(sXgtugyAmn == true){sXgtugyAmn = false;}
      if(CiMahUdoXq == true){CiMahUdoXq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUZQQAOMJQ
{ 
  void mQSYGYMBuG()
  { 
      bool PnZquSZpLa = false;
      bool uDVGDoUzXT = false;
      bool daMBZXLHGd = false;
      bool pJXukeEEdF = false;
      bool JTKYVDSOZK = false;
      bool xYTnSnbYQX = false;
      bool GRihkkeZVY = false;
      bool jPVSKJPmeW = false;
      bool EwgufRojcw = false;
      bool DfnGyqjcnj = false;
      bool XrsBahDBcI = false;
      bool XnstSKknBS = false;
      bool uuxYUDbOTT = false;
      bool YmytyMDfTy = false;
      bool OnGTXOmtmn = false;
      bool FwaVobtTfX = false;
      bool GngJikpyuG = false;
      bool GFTDDHocBG = false;
      bool QgbfNcLcFW = false;
      bool RizwraHxkm = false;
      string LFMNinbtlU;
      string bDzLrdEBWu;
      string WmIOgtlVMA;
      string VKHyEnDGkV;
      string OeInThbuYS;
      string oBGAoYxyfo;
      string CGgkzQwAGE;
      string axQAfrdTtz;
      string RpwtLTEHIe;
      string pFZwTIxWnD;
      string kaoUrqkGTx;
      string ucEgXMJmZf;
      string MorbNUXUgX;
      string tGfqNpBbBT;
      string ixmLjMBsXG;
      string zKwIpwiMGX;
      string TQZwDnxMSg;
      string LgkGwOBfqA;
      string TewZXiJWAR;
      string GnVdASXqIw;
      if(LFMNinbtlU == kaoUrqkGTx){PnZquSZpLa = true;}
      else if(kaoUrqkGTx == LFMNinbtlU){XrsBahDBcI = true;}
      if(bDzLrdEBWu == ucEgXMJmZf){uDVGDoUzXT = true;}
      else if(ucEgXMJmZf == bDzLrdEBWu){XnstSKknBS = true;}
      if(WmIOgtlVMA == MorbNUXUgX){daMBZXLHGd = true;}
      else if(MorbNUXUgX == WmIOgtlVMA){uuxYUDbOTT = true;}
      if(VKHyEnDGkV == tGfqNpBbBT){pJXukeEEdF = true;}
      else if(tGfqNpBbBT == VKHyEnDGkV){YmytyMDfTy = true;}
      if(OeInThbuYS == ixmLjMBsXG){JTKYVDSOZK = true;}
      else if(ixmLjMBsXG == OeInThbuYS){OnGTXOmtmn = true;}
      if(oBGAoYxyfo == zKwIpwiMGX){xYTnSnbYQX = true;}
      else if(zKwIpwiMGX == oBGAoYxyfo){FwaVobtTfX = true;}
      if(CGgkzQwAGE == TQZwDnxMSg){GRihkkeZVY = true;}
      else if(TQZwDnxMSg == CGgkzQwAGE){GngJikpyuG = true;}
      if(axQAfrdTtz == LgkGwOBfqA){jPVSKJPmeW = true;}
      if(RpwtLTEHIe == TewZXiJWAR){EwgufRojcw = true;}
      if(pFZwTIxWnD == GnVdASXqIw){DfnGyqjcnj = true;}
      while(LgkGwOBfqA == axQAfrdTtz){GFTDDHocBG = true;}
      while(TewZXiJWAR == TewZXiJWAR){QgbfNcLcFW = true;}
      while(GnVdASXqIw == GnVdASXqIw){RizwraHxkm = true;}
      if(PnZquSZpLa == true){PnZquSZpLa = false;}
      if(uDVGDoUzXT == true){uDVGDoUzXT = false;}
      if(daMBZXLHGd == true){daMBZXLHGd = false;}
      if(pJXukeEEdF == true){pJXukeEEdF = false;}
      if(JTKYVDSOZK == true){JTKYVDSOZK = false;}
      if(xYTnSnbYQX == true){xYTnSnbYQX = false;}
      if(GRihkkeZVY == true){GRihkkeZVY = false;}
      if(jPVSKJPmeW == true){jPVSKJPmeW = false;}
      if(EwgufRojcw == true){EwgufRojcw = false;}
      if(DfnGyqjcnj == true){DfnGyqjcnj = false;}
      if(XrsBahDBcI == true){XrsBahDBcI = false;}
      if(XnstSKknBS == true){XnstSKknBS = false;}
      if(uuxYUDbOTT == true){uuxYUDbOTT = false;}
      if(YmytyMDfTy == true){YmytyMDfTy = false;}
      if(OnGTXOmtmn == true){OnGTXOmtmn = false;}
      if(FwaVobtTfX == true){FwaVobtTfX = false;}
      if(GngJikpyuG == true){GngJikpyuG = false;}
      if(GFTDDHocBG == true){GFTDDHocBG = false;}
      if(QgbfNcLcFW == true){QgbfNcLcFW = false;}
      if(RizwraHxkm == true){RizwraHxkm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLYHHCPZMJ
{ 
  void bMXFSuRhtJ()
  { 
      bool RzcGNqUJXB = false;
      bool rkSBiYUjqA = false;
      bool UdmIITYAGp = false;
      bool iDRNzYWuZe = false;
      bool iVgiBliiHa = false;
      bool IRJeYmMTyt = false;
      bool SUCgRoTFCK = false;
      bool BZKLQzxDGW = false;
      bool jorfhRsloL = false;
      bool MDweMOSzRM = false;
      bool RdgxYiHxNY = false;
      bool oIMbKcbWzA = false;
      bool ugQpxydezC = false;
      bool fyltEFIuGy = false;
      bool JwYPWEpTUj = false;
      bool lwzQRjNqza = false;
      bool EbyKsqVSXE = false;
      bool TgQAqyIATs = false;
      bool IJKPPjyVbT = false;
      bool qRufshyNVe = false;
      string FEFknVTQHS;
      string Eqqdbresmy;
      string VLKsleVUVs;
      string jXYBlbdYgg;
      string MzOxbgHTiS;
      string MXBXsttLyI;
      string AyuOhfSprz;
      string OGMFlVwMRE;
      string WClDfMVAHq;
      string hRZXgNEzOu;
      string OQaiEFLwlW;
      string xgttkxMqhV;
      string JRhBRwfnXX;
      string RxyVpGbCzZ;
      string BZOktAXflj;
      string BMRskwiZRH;
      string ZWXNFAiXDe;
      string VJrHUjDxGQ;
      string YABnWEeEkt;
      string WCkqAdBAfs;
      if(FEFknVTQHS == OQaiEFLwlW){RzcGNqUJXB = true;}
      else if(OQaiEFLwlW == FEFknVTQHS){RdgxYiHxNY = true;}
      if(Eqqdbresmy == xgttkxMqhV){rkSBiYUjqA = true;}
      else if(xgttkxMqhV == Eqqdbresmy){oIMbKcbWzA = true;}
      if(VLKsleVUVs == JRhBRwfnXX){UdmIITYAGp = true;}
      else if(JRhBRwfnXX == VLKsleVUVs){ugQpxydezC = true;}
      if(jXYBlbdYgg == RxyVpGbCzZ){iDRNzYWuZe = true;}
      else if(RxyVpGbCzZ == jXYBlbdYgg){fyltEFIuGy = true;}
      if(MzOxbgHTiS == BZOktAXflj){iVgiBliiHa = true;}
      else if(BZOktAXflj == MzOxbgHTiS){JwYPWEpTUj = true;}
      if(MXBXsttLyI == BMRskwiZRH){IRJeYmMTyt = true;}
      else if(BMRskwiZRH == MXBXsttLyI){lwzQRjNqza = true;}
      if(AyuOhfSprz == ZWXNFAiXDe){SUCgRoTFCK = true;}
      else if(ZWXNFAiXDe == AyuOhfSprz){EbyKsqVSXE = true;}
      if(OGMFlVwMRE == VJrHUjDxGQ){BZKLQzxDGW = true;}
      if(WClDfMVAHq == YABnWEeEkt){jorfhRsloL = true;}
      if(hRZXgNEzOu == WCkqAdBAfs){MDweMOSzRM = true;}
      while(VJrHUjDxGQ == OGMFlVwMRE){TgQAqyIATs = true;}
      while(YABnWEeEkt == YABnWEeEkt){IJKPPjyVbT = true;}
      while(WCkqAdBAfs == WCkqAdBAfs){qRufshyNVe = true;}
      if(RzcGNqUJXB == true){RzcGNqUJXB = false;}
      if(rkSBiYUjqA == true){rkSBiYUjqA = false;}
      if(UdmIITYAGp == true){UdmIITYAGp = false;}
      if(iDRNzYWuZe == true){iDRNzYWuZe = false;}
      if(iVgiBliiHa == true){iVgiBliiHa = false;}
      if(IRJeYmMTyt == true){IRJeYmMTyt = false;}
      if(SUCgRoTFCK == true){SUCgRoTFCK = false;}
      if(BZKLQzxDGW == true){BZKLQzxDGW = false;}
      if(jorfhRsloL == true){jorfhRsloL = false;}
      if(MDweMOSzRM == true){MDweMOSzRM = false;}
      if(RdgxYiHxNY == true){RdgxYiHxNY = false;}
      if(oIMbKcbWzA == true){oIMbKcbWzA = false;}
      if(ugQpxydezC == true){ugQpxydezC = false;}
      if(fyltEFIuGy == true){fyltEFIuGy = false;}
      if(JwYPWEpTUj == true){JwYPWEpTUj = false;}
      if(lwzQRjNqza == true){lwzQRjNqza = false;}
      if(EbyKsqVSXE == true){EbyKsqVSXE = false;}
      if(TgQAqyIATs == true){TgQAqyIATs = false;}
      if(IJKPPjyVbT == true){IJKPPjyVbT = false;}
      if(qRufshyNVe == true){qRufshyNVe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYYUVOFYZK
{ 
  void VYomGVisin()
  { 
      bool RJmlPlKkbo = false;
      bool BPMyPsZRrz = false;
      bool jhgTRfnlGg = false;
      bool YnrbLxUwnr = false;
      bool kwtJVQGQpx = false;
      bool wQgRYicTTi = false;
      bool xYduPMWkmS = false;
      bool YddzNnnWyB = false;
      bool ZXuJjHGZDb = false;
      bool TAbEuMRzsI = false;
      bool sVcXYRmgEj = false;
      bool uGVSJYcUKH = false;
      bool GwhKzXCYEB = false;
      bool VocoHDtXjS = false;
      bool UYVSgNdItV = false;
      bool iwnlBwnSYA = false;
      bool PNbCOFcfLF = false;
      bool dFkrmgaOck = false;
      bool tseiSZAqmL = false;
      bool PbziCGxTEb = false;
      string IhPLfsgBeR;
      string zVDBbWjwdy;
      string RjLdZaBUhK;
      string gpbZhzFrrZ;
      string ursxUQYbDk;
      string fctrSYVlkF;
      string qLSUkJscTc;
      string QrEDCYpOIJ;
      string BZRxeDwjGI;
      string cTGmhiYYML;
      string XwHaTmYqot;
      string iGcbDRtVog;
      string NIVKzxlQUS;
      string zQBxlFRpcq;
      string dEuMZWpdiQ;
      string oDiexOZxaW;
      string BHVVuREfpx;
      string ADrxDINJjc;
      string GHhEdwhWzW;
      string fTOGpViYRI;
      if(IhPLfsgBeR == XwHaTmYqot){RJmlPlKkbo = true;}
      else if(XwHaTmYqot == IhPLfsgBeR){sVcXYRmgEj = true;}
      if(zVDBbWjwdy == iGcbDRtVog){BPMyPsZRrz = true;}
      else if(iGcbDRtVog == zVDBbWjwdy){uGVSJYcUKH = true;}
      if(RjLdZaBUhK == NIVKzxlQUS){jhgTRfnlGg = true;}
      else if(NIVKzxlQUS == RjLdZaBUhK){GwhKzXCYEB = true;}
      if(gpbZhzFrrZ == zQBxlFRpcq){YnrbLxUwnr = true;}
      else if(zQBxlFRpcq == gpbZhzFrrZ){VocoHDtXjS = true;}
      if(ursxUQYbDk == dEuMZWpdiQ){kwtJVQGQpx = true;}
      else if(dEuMZWpdiQ == ursxUQYbDk){UYVSgNdItV = true;}
      if(fctrSYVlkF == oDiexOZxaW){wQgRYicTTi = true;}
      else if(oDiexOZxaW == fctrSYVlkF){iwnlBwnSYA = true;}
      if(qLSUkJscTc == BHVVuREfpx){xYduPMWkmS = true;}
      else if(BHVVuREfpx == qLSUkJscTc){PNbCOFcfLF = true;}
      if(QrEDCYpOIJ == ADrxDINJjc){YddzNnnWyB = true;}
      if(BZRxeDwjGI == GHhEdwhWzW){ZXuJjHGZDb = true;}
      if(cTGmhiYYML == fTOGpViYRI){TAbEuMRzsI = true;}
      while(ADrxDINJjc == QrEDCYpOIJ){dFkrmgaOck = true;}
      while(GHhEdwhWzW == GHhEdwhWzW){tseiSZAqmL = true;}
      while(fTOGpViYRI == fTOGpViYRI){PbziCGxTEb = true;}
      if(RJmlPlKkbo == true){RJmlPlKkbo = false;}
      if(BPMyPsZRrz == true){BPMyPsZRrz = false;}
      if(jhgTRfnlGg == true){jhgTRfnlGg = false;}
      if(YnrbLxUwnr == true){YnrbLxUwnr = false;}
      if(kwtJVQGQpx == true){kwtJVQGQpx = false;}
      if(wQgRYicTTi == true){wQgRYicTTi = false;}
      if(xYduPMWkmS == true){xYduPMWkmS = false;}
      if(YddzNnnWyB == true){YddzNnnWyB = false;}
      if(ZXuJjHGZDb == true){ZXuJjHGZDb = false;}
      if(TAbEuMRzsI == true){TAbEuMRzsI = false;}
      if(sVcXYRmgEj == true){sVcXYRmgEj = false;}
      if(uGVSJYcUKH == true){uGVSJYcUKH = false;}
      if(GwhKzXCYEB == true){GwhKzXCYEB = false;}
      if(VocoHDtXjS == true){VocoHDtXjS = false;}
      if(UYVSgNdItV == true){UYVSgNdItV = false;}
      if(iwnlBwnSYA == true){iwnlBwnSYA = false;}
      if(PNbCOFcfLF == true){PNbCOFcfLF = false;}
      if(dFkrmgaOck == true){dFkrmgaOck = false;}
      if(tseiSZAqmL == true){tseiSZAqmL = false;}
      if(PbziCGxTEb == true){PbziCGxTEb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDIWUHYPMA
{ 
  void HEIWumgXQM()
  { 
      bool qZYUaxjwoe = false;
      bool PLpthVlNtg = false;
      bool XMjTslYeiH = false;
      bool hflMoUMFHl = false;
      bool CkpCVQIBgD = false;
      bool rKETkepEbo = false;
      bool XFMgwiZdFN = false;
      bool IfGHdmWgyb = false;
      bool dXyfPWbSbK = false;
      bool eHdROxXIGl = false;
      bool qewStLExoy = false;
      bool HJGzLAHfQZ = false;
      bool HGBtiABnsg = false;
      bool ONaMjyaekE = false;
      bool SddcCVBeGN = false;
      bool prqfdkcBjt = false;
      bool JPDHishsOM = false;
      bool YbtMHccYrN = false;
      bool yWhepWVthz = false;
      bool VZuqtCaVsI = false;
      string jSwguqSeGB;
      string ugyJkFWcMq;
      string uQLgKLnHkM;
      string DGMfWnqnXK;
      string ZLlBBYahpc;
      string HitAWTGPWi;
      string CLtsxnURmx;
      string NhFCRidJek;
      string kGQHFUMLID;
      string gbQnHNQrDM;
      string EIurPYdqhm;
      string pxjlyutlnc;
      string bIJiQlQQtD;
      string RkFSgbKYrf;
      string qUcVNiqepL;
      string TeEakuzLbc;
      string HMwdUEqRFV;
      string kVtIlGemVg;
      string tlahjmgegk;
      string cywOYdYzAI;
      if(jSwguqSeGB == EIurPYdqhm){qZYUaxjwoe = true;}
      else if(EIurPYdqhm == jSwguqSeGB){qewStLExoy = true;}
      if(ugyJkFWcMq == pxjlyutlnc){PLpthVlNtg = true;}
      else if(pxjlyutlnc == ugyJkFWcMq){HJGzLAHfQZ = true;}
      if(uQLgKLnHkM == bIJiQlQQtD){XMjTslYeiH = true;}
      else if(bIJiQlQQtD == uQLgKLnHkM){HGBtiABnsg = true;}
      if(DGMfWnqnXK == RkFSgbKYrf){hflMoUMFHl = true;}
      else if(RkFSgbKYrf == DGMfWnqnXK){ONaMjyaekE = true;}
      if(ZLlBBYahpc == qUcVNiqepL){CkpCVQIBgD = true;}
      else if(qUcVNiqepL == ZLlBBYahpc){SddcCVBeGN = true;}
      if(HitAWTGPWi == TeEakuzLbc){rKETkepEbo = true;}
      else if(TeEakuzLbc == HitAWTGPWi){prqfdkcBjt = true;}
      if(CLtsxnURmx == HMwdUEqRFV){XFMgwiZdFN = true;}
      else if(HMwdUEqRFV == CLtsxnURmx){JPDHishsOM = true;}
      if(NhFCRidJek == kVtIlGemVg){IfGHdmWgyb = true;}
      if(kGQHFUMLID == tlahjmgegk){dXyfPWbSbK = true;}
      if(gbQnHNQrDM == cywOYdYzAI){eHdROxXIGl = true;}
      while(kVtIlGemVg == NhFCRidJek){YbtMHccYrN = true;}
      while(tlahjmgegk == tlahjmgegk){yWhepWVthz = true;}
      while(cywOYdYzAI == cywOYdYzAI){VZuqtCaVsI = true;}
      if(qZYUaxjwoe == true){qZYUaxjwoe = false;}
      if(PLpthVlNtg == true){PLpthVlNtg = false;}
      if(XMjTslYeiH == true){XMjTslYeiH = false;}
      if(hflMoUMFHl == true){hflMoUMFHl = false;}
      if(CkpCVQIBgD == true){CkpCVQIBgD = false;}
      if(rKETkepEbo == true){rKETkepEbo = false;}
      if(XFMgwiZdFN == true){XFMgwiZdFN = false;}
      if(IfGHdmWgyb == true){IfGHdmWgyb = false;}
      if(dXyfPWbSbK == true){dXyfPWbSbK = false;}
      if(eHdROxXIGl == true){eHdROxXIGl = false;}
      if(qewStLExoy == true){qewStLExoy = false;}
      if(HJGzLAHfQZ == true){HJGzLAHfQZ = false;}
      if(HGBtiABnsg == true){HGBtiABnsg = false;}
      if(ONaMjyaekE == true){ONaMjyaekE = false;}
      if(SddcCVBeGN == true){SddcCVBeGN = false;}
      if(prqfdkcBjt == true){prqfdkcBjt = false;}
      if(JPDHishsOM == true){JPDHishsOM = false;}
      if(YbtMHccYrN == true){YbtMHccYrN = false;}
      if(yWhepWVthz == true){yWhepWVthz = false;}
      if(VZuqtCaVsI == true){VZuqtCaVsI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCCKTQSBZX
{ 
  void bqsWqCPSci()
  { 
      bool kwwdskJHNU = false;
      bool CuzZRqGrGn = false;
      bool sCDPWcLFDC = false;
      bool qsfadEyOWD = false;
      bool eodcaRcFqL = false;
      bool KVKMyirfGQ = false;
      bool YDELdIOYuM = false;
      bool srUDIDXZnF = false;
      bool zFOqqUiTbu = false;
      bool MRHGdakSzS = false;
      bool DEKdSSBGEt = false;
      bool KRrBQToMTJ = false;
      bool ZuxAAakNYg = false;
      bool RFaVBuukYY = false;
      bool TbOgjtZFpK = false;
      bool lYyosIGJcq = false;
      bool hmgXcFpVzU = false;
      bool XEmupxfPPG = false;
      bool AeXOtsGlcs = false;
      bool nlHgpftqEe = false;
      string MeBQDiGXLl;
      string MoSqFywolP;
      string bpTAGzSmlA;
      string bnrlGKZjsS;
      string JAVbZfUDfq;
      string kDrTRWLBKE;
      string QTkLJXwfku;
      string YLwSGbUqaZ;
      string dOGuOYwYUj;
      string zYZoCoOJSC;
      string jnSkSYHYMp;
      string BTajZCMpwk;
      string bWLAuzlHQQ;
      string MKYYpouVbp;
      string QWMdhfypOA;
      string cXNgZMcRoS;
      string mzIucptBsj;
      string GqOGTFKhSP;
      string BusQnoxryd;
      string McfIDRNQBq;
      if(MeBQDiGXLl == jnSkSYHYMp){kwwdskJHNU = true;}
      else if(jnSkSYHYMp == MeBQDiGXLl){DEKdSSBGEt = true;}
      if(MoSqFywolP == BTajZCMpwk){CuzZRqGrGn = true;}
      else if(BTajZCMpwk == MoSqFywolP){KRrBQToMTJ = true;}
      if(bpTAGzSmlA == bWLAuzlHQQ){sCDPWcLFDC = true;}
      else if(bWLAuzlHQQ == bpTAGzSmlA){ZuxAAakNYg = true;}
      if(bnrlGKZjsS == MKYYpouVbp){qsfadEyOWD = true;}
      else if(MKYYpouVbp == bnrlGKZjsS){RFaVBuukYY = true;}
      if(JAVbZfUDfq == QWMdhfypOA){eodcaRcFqL = true;}
      else if(QWMdhfypOA == JAVbZfUDfq){TbOgjtZFpK = true;}
      if(kDrTRWLBKE == cXNgZMcRoS){KVKMyirfGQ = true;}
      else if(cXNgZMcRoS == kDrTRWLBKE){lYyosIGJcq = true;}
      if(QTkLJXwfku == mzIucptBsj){YDELdIOYuM = true;}
      else if(mzIucptBsj == QTkLJXwfku){hmgXcFpVzU = true;}
      if(YLwSGbUqaZ == GqOGTFKhSP){srUDIDXZnF = true;}
      if(dOGuOYwYUj == BusQnoxryd){zFOqqUiTbu = true;}
      if(zYZoCoOJSC == McfIDRNQBq){MRHGdakSzS = true;}
      while(GqOGTFKhSP == YLwSGbUqaZ){XEmupxfPPG = true;}
      while(BusQnoxryd == BusQnoxryd){AeXOtsGlcs = true;}
      while(McfIDRNQBq == McfIDRNQBq){nlHgpftqEe = true;}
      if(kwwdskJHNU == true){kwwdskJHNU = false;}
      if(CuzZRqGrGn == true){CuzZRqGrGn = false;}
      if(sCDPWcLFDC == true){sCDPWcLFDC = false;}
      if(qsfadEyOWD == true){qsfadEyOWD = false;}
      if(eodcaRcFqL == true){eodcaRcFqL = false;}
      if(KVKMyirfGQ == true){KVKMyirfGQ = false;}
      if(YDELdIOYuM == true){YDELdIOYuM = false;}
      if(srUDIDXZnF == true){srUDIDXZnF = false;}
      if(zFOqqUiTbu == true){zFOqqUiTbu = false;}
      if(MRHGdakSzS == true){MRHGdakSzS = false;}
      if(DEKdSSBGEt == true){DEKdSSBGEt = false;}
      if(KRrBQToMTJ == true){KRrBQToMTJ = false;}
      if(ZuxAAakNYg == true){ZuxAAakNYg = false;}
      if(RFaVBuukYY == true){RFaVBuukYY = false;}
      if(TbOgjtZFpK == true){TbOgjtZFpK = false;}
      if(lYyosIGJcq == true){lYyosIGJcq = false;}
      if(hmgXcFpVzU == true){hmgXcFpVzU = false;}
      if(XEmupxfPPG == true){XEmupxfPPG = false;}
      if(AeXOtsGlcs == true){AeXOtsGlcs = false;}
      if(nlHgpftqEe == true){nlHgpftqEe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WKUDJIYRMK
{ 
  void EwxrkLkgnP()
  { 
      bool YwlAqnfZey = false;
      bool dorpUtLTZa = false;
      bool zBiOlsbqdJ = false;
      bool JCEyotzxRG = false;
      bool HcbAIqkuGG = false;
      bool SXhpGXMWNx = false;
      bool MnuVnbjsAa = false;
      bool uOCSSVYhGu = false;
      bool IfkXqlTOrR = false;
      bool gbiUtSgFMg = false;
      bool GqufLDVPXj = false;
      bool yeQSofDXeC = false;
      bool HVBitSehXz = false;
      bool oTVZoQjELm = false;
      bool QEpHTBLQeN = false;
      bool PJaKYjpMkr = false;
      bool YmqXueIpcX = false;
      bool uyLrkDftPr = false;
      bool HNCJjerLBE = false;
      bool aXTTNcMSLn = false;
      string IJuqZxpQbd;
      string EwXScBkrbx;
      string jfHpMIRylf;
      string mJNkrRSuwq;
      string wmKlSKBiJQ;
      string uWlSAcCFeR;
      string erdwquhmaK;
      string ipujBxUUWC;
      string GhoVkPWtjO;
      string OMPdLEIOtX;
      string bOIzhFaBRD;
      string HhhbKxDIKb;
      string XmCLuVZRXw;
      string nGZzarZonf;
      string nVcfHgenSO;
      string BAESAnLwDL;
      string eJdUOBIhBS;
      string WNTemBKVEN;
      string pkyJunCGzl;
      string fckbAdrIRF;
      if(IJuqZxpQbd == bOIzhFaBRD){YwlAqnfZey = true;}
      else if(bOIzhFaBRD == IJuqZxpQbd){GqufLDVPXj = true;}
      if(EwXScBkrbx == HhhbKxDIKb){dorpUtLTZa = true;}
      else if(HhhbKxDIKb == EwXScBkrbx){yeQSofDXeC = true;}
      if(jfHpMIRylf == XmCLuVZRXw){zBiOlsbqdJ = true;}
      else if(XmCLuVZRXw == jfHpMIRylf){HVBitSehXz = true;}
      if(mJNkrRSuwq == nGZzarZonf){JCEyotzxRG = true;}
      else if(nGZzarZonf == mJNkrRSuwq){oTVZoQjELm = true;}
      if(wmKlSKBiJQ == nVcfHgenSO){HcbAIqkuGG = true;}
      else if(nVcfHgenSO == wmKlSKBiJQ){QEpHTBLQeN = true;}
      if(uWlSAcCFeR == BAESAnLwDL){SXhpGXMWNx = true;}
      else if(BAESAnLwDL == uWlSAcCFeR){PJaKYjpMkr = true;}
      if(erdwquhmaK == eJdUOBIhBS){MnuVnbjsAa = true;}
      else if(eJdUOBIhBS == erdwquhmaK){YmqXueIpcX = true;}
      if(ipujBxUUWC == WNTemBKVEN){uOCSSVYhGu = true;}
      if(GhoVkPWtjO == pkyJunCGzl){IfkXqlTOrR = true;}
      if(OMPdLEIOtX == fckbAdrIRF){gbiUtSgFMg = true;}
      while(WNTemBKVEN == ipujBxUUWC){uyLrkDftPr = true;}
      while(pkyJunCGzl == pkyJunCGzl){HNCJjerLBE = true;}
      while(fckbAdrIRF == fckbAdrIRF){aXTTNcMSLn = true;}
      if(YwlAqnfZey == true){YwlAqnfZey = false;}
      if(dorpUtLTZa == true){dorpUtLTZa = false;}
      if(zBiOlsbqdJ == true){zBiOlsbqdJ = false;}
      if(JCEyotzxRG == true){JCEyotzxRG = false;}
      if(HcbAIqkuGG == true){HcbAIqkuGG = false;}
      if(SXhpGXMWNx == true){SXhpGXMWNx = false;}
      if(MnuVnbjsAa == true){MnuVnbjsAa = false;}
      if(uOCSSVYhGu == true){uOCSSVYhGu = false;}
      if(IfkXqlTOrR == true){IfkXqlTOrR = false;}
      if(gbiUtSgFMg == true){gbiUtSgFMg = false;}
      if(GqufLDVPXj == true){GqufLDVPXj = false;}
      if(yeQSofDXeC == true){yeQSofDXeC = false;}
      if(HVBitSehXz == true){HVBitSehXz = false;}
      if(oTVZoQjELm == true){oTVZoQjELm = false;}
      if(QEpHTBLQeN == true){QEpHTBLQeN = false;}
      if(PJaKYjpMkr == true){PJaKYjpMkr = false;}
      if(YmqXueIpcX == true){YmqXueIpcX = false;}
      if(uyLrkDftPr == true){uyLrkDftPr = false;}
      if(HNCJjerLBE == true){HNCJjerLBE = false;}
      if(aXTTNcMSLn == true){aXTTNcMSLn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBJYQYNFLH
{ 
  void upjKNdPAFp()
  { 
      bool pIWWwgJUff = false;
      bool PkLLegKWIw = false;
      bool WKVorWNwmx = false;
      bool uumJqPrVAx = false;
      bool IUAbtWZeTl = false;
      bool ebeVPemheY = false;
      bool SNhikTyBUP = false;
      bool nnWKnCJstU = false;
      bool xhbARSPRsL = false;
      bool bKqbdtmRqZ = false;
      bool XYKExqFTgN = false;
      bool UtmJakkgQR = false;
      bool DfHImdwtfs = false;
      bool OrBTwXXXCa = false;
      bool NujfqgWgAs = false;
      bool JGAZVrRCQT = false;
      bool tKnnzcrSNC = false;
      bool MNdpDHwbRF = false;
      bool GPtmiIqbxE = false;
      bool GVGhfDHufN = false;
      string erjKeohNfT;
      string QemxMqhjXM;
      string DlyDdEjutG;
      string XRjjVUfNwN;
      string QYXwjHeiAa;
      string EIeBRrtfgZ;
      string FlSYwytDbq;
      string LTnJwdOBTW;
      string ZBuTBOmhSd;
      string azgWIdFyAk;
      string MaHJPkUUFm;
      string crMJzDqzWg;
      string LMkyPLmQBR;
      string XQAhKztkDQ;
      string sRbfAhmWXE;
      string mGaTZApIsD;
      string xDSnOMrdzA;
      string IFwGmsjExh;
      string YPsweRogIK;
      string IkqzToynRm;
      if(erjKeohNfT == MaHJPkUUFm){pIWWwgJUff = true;}
      else if(MaHJPkUUFm == erjKeohNfT){XYKExqFTgN = true;}
      if(QemxMqhjXM == crMJzDqzWg){PkLLegKWIw = true;}
      else if(crMJzDqzWg == QemxMqhjXM){UtmJakkgQR = true;}
      if(DlyDdEjutG == LMkyPLmQBR){WKVorWNwmx = true;}
      else if(LMkyPLmQBR == DlyDdEjutG){DfHImdwtfs = true;}
      if(XRjjVUfNwN == XQAhKztkDQ){uumJqPrVAx = true;}
      else if(XQAhKztkDQ == XRjjVUfNwN){OrBTwXXXCa = true;}
      if(QYXwjHeiAa == sRbfAhmWXE){IUAbtWZeTl = true;}
      else if(sRbfAhmWXE == QYXwjHeiAa){NujfqgWgAs = true;}
      if(EIeBRrtfgZ == mGaTZApIsD){ebeVPemheY = true;}
      else if(mGaTZApIsD == EIeBRrtfgZ){JGAZVrRCQT = true;}
      if(FlSYwytDbq == xDSnOMrdzA){SNhikTyBUP = true;}
      else if(xDSnOMrdzA == FlSYwytDbq){tKnnzcrSNC = true;}
      if(LTnJwdOBTW == IFwGmsjExh){nnWKnCJstU = true;}
      if(ZBuTBOmhSd == YPsweRogIK){xhbARSPRsL = true;}
      if(azgWIdFyAk == IkqzToynRm){bKqbdtmRqZ = true;}
      while(IFwGmsjExh == LTnJwdOBTW){MNdpDHwbRF = true;}
      while(YPsweRogIK == YPsweRogIK){GPtmiIqbxE = true;}
      while(IkqzToynRm == IkqzToynRm){GVGhfDHufN = true;}
      if(pIWWwgJUff == true){pIWWwgJUff = false;}
      if(PkLLegKWIw == true){PkLLegKWIw = false;}
      if(WKVorWNwmx == true){WKVorWNwmx = false;}
      if(uumJqPrVAx == true){uumJqPrVAx = false;}
      if(IUAbtWZeTl == true){IUAbtWZeTl = false;}
      if(ebeVPemheY == true){ebeVPemheY = false;}
      if(SNhikTyBUP == true){SNhikTyBUP = false;}
      if(nnWKnCJstU == true){nnWKnCJstU = false;}
      if(xhbARSPRsL == true){xhbARSPRsL = false;}
      if(bKqbdtmRqZ == true){bKqbdtmRqZ = false;}
      if(XYKExqFTgN == true){XYKExqFTgN = false;}
      if(UtmJakkgQR == true){UtmJakkgQR = false;}
      if(DfHImdwtfs == true){DfHImdwtfs = false;}
      if(OrBTwXXXCa == true){OrBTwXXXCa = false;}
      if(NujfqgWgAs == true){NujfqgWgAs = false;}
      if(JGAZVrRCQT == true){JGAZVrRCQT = false;}
      if(tKnnzcrSNC == true){tKnnzcrSNC = false;}
      if(MNdpDHwbRF == true){MNdpDHwbRF = false;}
      if(GPtmiIqbxE == true){GPtmiIqbxE = false;}
      if(GVGhfDHufN == true){GVGhfDHufN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOSREVNJBN
{ 
  void abgIBBWkpu()
  { 
      bool agDNaMJZUL = false;
      bool UDKgSLYcIV = false;
      bool WFdpXOaRhU = false;
      bool FZwemLJaar = false;
      bool iNlEOyHLfD = false;
      bool GnlfWUCNpM = false;
      bool lrqAFtHfsG = false;
      bool ByBQlJTYaY = false;
      bool GOkeNRnPHR = false;
      bool JwkOGqVkzT = false;
      bool pbSYCIlVtM = false;
      bool BcmQFWGMln = false;
      bool GrXaxENlJt = false;
      bool mhZGhewMcF = false;
      bool eSUuQfJTJj = false;
      bool kJyLNyEqax = false;
      bool tzLzYTDfhZ = false;
      bool asigImWbKR = false;
      bool uscZJdiOsj = false;
      bool aEkfKfHVVx = false;
      string LMsBuWEjku;
      string cRLSlBzJjE;
      string qVhCExbMPs;
      string SYezPHLcPj;
      string fVBqDHbOaW;
      string minWBpeqxy;
      string urUqcDlMCd;
      string oWszXUUpyw;
      string UMkrFikHxZ;
      string bUeRomBJOA;
      string UPLxgQpoyg;
      string VorBdhHbls;
      string SdOcBUqbJk;
      string SKbyaEBnLn;
      string swIQEmbdmH;
      string fZXUhpBiuM;
      string YNeNOKMtZZ;
      string gTQxAWVxYO;
      string sNnCEsmGPj;
      string CRrzOeQuBs;
      if(LMsBuWEjku == UPLxgQpoyg){agDNaMJZUL = true;}
      else if(UPLxgQpoyg == LMsBuWEjku){pbSYCIlVtM = true;}
      if(cRLSlBzJjE == VorBdhHbls){UDKgSLYcIV = true;}
      else if(VorBdhHbls == cRLSlBzJjE){BcmQFWGMln = true;}
      if(qVhCExbMPs == SdOcBUqbJk){WFdpXOaRhU = true;}
      else if(SdOcBUqbJk == qVhCExbMPs){GrXaxENlJt = true;}
      if(SYezPHLcPj == SKbyaEBnLn){FZwemLJaar = true;}
      else if(SKbyaEBnLn == SYezPHLcPj){mhZGhewMcF = true;}
      if(fVBqDHbOaW == swIQEmbdmH){iNlEOyHLfD = true;}
      else if(swIQEmbdmH == fVBqDHbOaW){eSUuQfJTJj = true;}
      if(minWBpeqxy == fZXUhpBiuM){GnlfWUCNpM = true;}
      else if(fZXUhpBiuM == minWBpeqxy){kJyLNyEqax = true;}
      if(urUqcDlMCd == YNeNOKMtZZ){lrqAFtHfsG = true;}
      else if(YNeNOKMtZZ == urUqcDlMCd){tzLzYTDfhZ = true;}
      if(oWszXUUpyw == gTQxAWVxYO){ByBQlJTYaY = true;}
      if(UMkrFikHxZ == sNnCEsmGPj){GOkeNRnPHR = true;}
      if(bUeRomBJOA == CRrzOeQuBs){JwkOGqVkzT = true;}
      while(gTQxAWVxYO == oWszXUUpyw){asigImWbKR = true;}
      while(sNnCEsmGPj == sNnCEsmGPj){uscZJdiOsj = true;}
      while(CRrzOeQuBs == CRrzOeQuBs){aEkfKfHVVx = true;}
      if(agDNaMJZUL == true){agDNaMJZUL = false;}
      if(UDKgSLYcIV == true){UDKgSLYcIV = false;}
      if(WFdpXOaRhU == true){WFdpXOaRhU = false;}
      if(FZwemLJaar == true){FZwemLJaar = false;}
      if(iNlEOyHLfD == true){iNlEOyHLfD = false;}
      if(GnlfWUCNpM == true){GnlfWUCNpM = false;}
      if(lrqAFtHfsG == true){lrqAFtHfsG = false;}
      if(ByBQlJTYaY == true){ByBQlJTYaY = false;}
      if(GOkeNRnPHR == true){GOkeNRnPHR = false;}
      if(JwkOGqVkzT == true){JwkOGqVkzT = false;}
      if(pbSYCIlVtM == true){pbSYCIlVtM = false;}
      if(BcmQFWGMln == true){BcmQFWGMln = false;}
      if(GrXaxENlJt == true){GrXaxENlJt = false;}
      if(mhZGhewMcF == true){mhZGhewMcF = false;}
      if(eSUuQfJTJj == true){eSUuQfJTJj = false;}
      if(kJyLNyEqax == true){kJyLNyEqax = false;}
      if(tzLzYTDfhZ == true){tzLzYTDfhZ = false;}
      if(asigImWbKR == true){asigImWbKR = false;}
      if(uscZJdiOsj == true){uscZJdiOsj = false;}
      if(aEkfKfHVVx == true){aEkfKfHVVx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEMWTZTFUQ
{ 
  void xEdXnmuzhl()
  { 
      bool lPnmhOpeqY = false;
      bool LighlxlEjc = false;
      bool XHlTuUZJqz = false;
      bool kQLyWgrOzY = false;
      bool nxmQsFcnhg = false;
      bool rTidKdcUqM = false;
      bool ofnrntWiKE = false;
      bool FXELnZUUZo = false;
      bool qlbKHRghms = false;
      bool EWWliIJtcy = false;
      bool htccaTOXok = false;
      bool IHtCUCEckV = false;
      bool NouRAhASbf = false;
      bool PZqbGxIzim = false;
      bool DJrBjwcUQg = false;
      bool DgJHksyLcs = false;
      bool TwuJViQSwX = false;
      bool tEsxSDwtgE = false;
      bool FfBubiPjpM = false;
      bool zxWpTGOifA = false;
      string GTFoLYDwDw;
      string ltfuKzTYdl;
      string QLNgoJRGkn;
      string SdDeMQRmBV;
      string SNxuIOjOSH;
      string FlnpJuFYzB;
      string GxLOcIpBis;
      string hgXITCNRXZ;
      string ZDmchgoNUQ;
      string LrmzOUChRA;
      string YheYYYNeVH;
      string gmAZbCKhfw;
      string SbfRhotYsy;
      string zfAXBqXNDJ;
      string SJqNjYrMWM;
      string KUCUhwBNqj;
      string enlXHBmcYj;
      string ewdWdIkSgJ;
      string xgBgmecepE;
      string oJVTeeXTGi;
      if(GTFoLYDwDw == YheYYYNeVH){lPnmhOpeqY = true;}
      else if(YheYYYNeVH == GTFoLYDwDw){htccaTOXok = true;}
      if(ltfuKzTYdl == gmAZbCKhfw){LighlxlEjc = true;}
      else if(gmAZbCKhfw == ltfuKzTYdl){IHtCUCEckV = true;}
      if(QLNgoJRGkn == SbfRhotYsy){XHlTuUZJqz = true;}
      else if(SbfRhotYsy == QLNgoJRGkn){NouRAhASbf = true;}
      if(SdDeMQRmBV == zfAXBqXNDJ){kQLyWgrOzY = true;}
      else if(zfAXBqXNDJ == SdDeMQRmBV){PZqbGxIzim = true;}
      if(SNxuIOjOSH == SJqNjYrMWM){nxmQsFcnhg = true;}
      else if(SJqNjYrMWM == SNxuIOjOSH){DJrBjwcUQg = true;}
      if(FlnpJuFYzB == KUCUhwBNqj){rTidKdcUqM = true;}
      else if(KUCUhwBNqj == FlnpJuFYzB){DgJHksyLcs = true;}
      if(GxLOcIpBis == enlXHBmcYj){ofnrntWiKE = true;}
      else if(enlXHBmcYj == GxLOcIpBis){TwuJViQSwX = true;}
      if(hgXITCNRXZ == ewdWdIkSgJ){FXELnZUUZo = true;}
      if(ZDmchgoNUQ == xgBgmecepE){qlbKHRghms = true;}
      if(LrmzOUChRA == oJVTeeXTGi){EWWliIJtcy = true;}
      while(ewdWdIkSgJ == hgXITCNRXZ){tEsxSDwtgE = true;}
      while(xgBgmecepE == xgBgmecepE){FfBubiPjpM = true;}
      while(oJVTeeXTGi == oJVTeeXTGi){zxWpTGOifA = true;}
      if(lPnmhOpeqY == true){lPnmhOpeqY = false;}
      if(LighlxlEjc == true){LighlxlEjc = false;}
      if(XHlTuUZJqz == true){XHlTuUZJqz = false;}
      if(kQLyWgrOzY == true){kQLyWgrOzY = false;}
      if(nxmQsFcnhg == true){nxmQsFcnhg = false;}
      if(rTidKdcUqM == true){rTidKdcUqM = false;}
      if(ofnrntWiKE == true){ofnrntWiKE = false;}
      if(FXELnZUUZo == true){FXELnZUUZo = false;}
      if(qlbKHRghms == true){qlbKHRghms = false;}
      if(EWWliIJtcy == true){EWWliIJtcy = false;}
      if(htccaTOXok == true){htccaTOXok = false;}
      if(IHtCUCEckV == true){IHtCUCEckV = false;}
      if(NouRAhASbf == true){NouRAhASbf = false;}
      if(PZqbGxIzim == true){PZqbGxIzim = false;}
      if(DJrBjwcUQg == true){DJrBjwcUQg = false;}
      if(DgJHksyLcs == true){DgJHksyLcs = false;}
      if(TwuJViQSwX == true){TwuJViQSwX = false;}
      if(tEsxSDwtgE == true){tEsxSDwtgE = false;}
      if(FfBubiPjpM == true){FfBubiPjpM = false;}
      if(zxWpTGOifA == true){zxWpTGOifA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSRREHWDVQ
{ 
  void RRkNxdTrna()
  { 
      bool kORTMusIKT = false;
      bool oOEyuTisDP = false;
      bool BBtABiLcpr = false;
      bool hdVTnnOFRB = false;
      bool CzzFxQwhIh = false;
      bool kTEMwiURSc = false;
      bool jQRSlLrjKG = false;
      bool EcaBNCCoDj = false;
      bool mcUIGNYJXE = false;
      bool SxmoRlggSk = false;
      bool XMXBdHrCzs = false;
      bool gfOhpGuJLX = false;
      bool mhMFmHplja = false;
      bool UVVRLZETez = false;
      bool VWKdXmhEzK = false;
      bool qXUtyoASNW = false;
      bool QGRXXKJwVP = false;
      bool CbeMCQXhgA = false;
      bool YllZjxBbTV = false;
      bool ZlFHhOEmFM = false;
      string GBiXiryYDB;
      string ikFxtIgwNz;
      string OjMsoMQEBT;
      string xSzqxgfnug;
      string dgeQKGQwHN;
      string ejgGQWopiV;
      string bsWiDQlOAN;
      string crAgUgEuhh;
      string uTxnoNksZZ;
      string qpFZEjJuNt;
      string TCwskmiAkj;
      string StHAZHwitp;
      string esoZVllZbk;
      string WIhnNsWDCC;
      string dkHoHxiFAx;
      string naBWOaNWWz;
      string AJXAMJMTmf;
      string jrgrMtkzSY;
      string DgZexwHKYm;
      string eAgDBUMHcy;
      if(GBiXiryYDB == TCwskmiAkj){kORTMusIKT = true;}
      else if(TCwskmiAkj == GBiXiryYDB){XMXBdHrCzs = true;}
      if(ikFxtIgwNz == StHAZHwitp){oOEyuTisDP = true;}
      else if(StHAZHwitp == ikFxtIgwNz){gfOhpGuJLX = true;}
      if(OjMsoMQEBT == esoZVllZbk){BBtABiLcpr = true;}
      else if(esoZVllZbk == OjMsoMQEBT){mhMFmHplja = true;}
      if(xSzqxgfnug == WIhnNsWDCC){hdVTnnOFRB = true;}
      else if(WIhnNsWDCC == xSzqxgfnug){UVVRLZETez = true;}
      if(dgeQKGQwHN == dkHoHxiFAx){CzzFxQwhIh = true;}
      else if(dkHoHxiFAx == dgeQKGQwHN){VWKdXmhEzK = true;}
      if(ejgGQWopiV == naBWOaNWWz){kTEMwiURSc = true;}
      else if(naBWOaNWWz == ejgGQWopiV){qXUtyoASNW = true;}
      if(bsWiDQlOAN == AJXAMJMTmf){jQRSlLrjKG = true;}
      else if(AJXAMJMTmf == bsWiDQlOAN){QGRXXKJwVP = true;}
      if(crAgUgEuhh == jrgrMtkzSY){EcaBNCCoDj = true;}
      if(uTxnoNksZZ == DgZexwHKYm){mcUIGNYJXE = true;}
      if(qpFZEjJuNt == eAgDBUMHcy){SxmoRlggSk = true;}
      while(jrgrMtkzSY == crAgUgEuhh){CbeMCQXhgA = true;}
      while(DgZexwHKYm == DgZexwHKYm){YllZjxBbTV = true;}
      while(eAgDBUMHcy == eAgDBUMHcy){ZlFHhOEmFM = true;}
      if(kORTMusIKT == true){kORTMusIKT = false;}
      if(oOEyuTisDP == true){oOEyuTisDP = false;}
      if(BBtABiLcpr == true){BBtABiLcpr = false;}
      if(hdVTnnOFRB == true){hdVTnnOFRB = false;}
      if(CzzFxQwhIh == true){CzzFxQwhIh = false;}
      if(kTEMwiURSc == true){kTEMwiURSc = false;}
      if(jQRSlLrjKG == true){jQRSlLrjKG = false;}
      if(EcaBNCCoDj == true){EcaBNCCoDj = false;}
      if(mcUIGNYJXE == true){mcUIGNYJXE = false;}
      if(SxmoRlggSk == true){SxmoRlggSk = false;}
      if(XMXBdHrCzs == true){XMXBdHrCzs = false;}
      if(gfOhpGuJLX == true){gfOhpGuJLX = false;}
      if(mhMFmHplja == true){mhMFmHplja = false;}
      if(UVVRLZETez == true){UVVRLZETez = false;}
      if(VWKdXmhEzK == true){VWKdXmhEzK = false;}
      if(qXUtyoASNW == true){qXUtyoASNW = false;}
      if(QGRXXKJwVP == true){QGRXXKJwVP = false;}
      if(CbeMCQXhgA == true){CbeMCQXhgA = false;}
      if(YllZjxBbTV == true){YllZjxBbTV = false;}
      if(ZlFHhOEmFM == true){ZlFHhOEmFM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTMDWTNEUG
{ 
  void HbnuoeWkij()
  { 
      bool cgAKuwhwGh = false;
      bool tYSmAmNRZG = false;
      bool jCiXjcPNTc = false;
      bool HMnEwDyWww = false;
      bool GprTgQUMyh = false;
      bool SMweOZxcZS = false;
      bool fUcdZhjOpw = false;
      bool nqVczsKPpT = false;
      bool HDOlJuPJoV = false;
      bool GVxcQlNOsz = false;
      bool fGWCsbpTeV = false;
      bool PhlFLcFpTe = false;
      bool RaYToStrLN = false;
      bool ewVpnAfMsh = false;
      bool EwdTGYiqRn = false;
      bool fXtOhEgCMZ = false;
      bool hxIQqSMuRK = false;
      bool wsxlZUxFNQ = false;
      bool jCZWhGBGIi = false;
      bool SdzSAHnMcm = false;
      string kqPRYQBOiC;
      string hRXLlhieHo;
      string jgDozNlwtq;
      string XFfJVjCZLQ;
      string tLZiWoTiSU;
      string wgDSBDmaRK;
      string dFUqdblOpB;
      string fJSptYHURK;
      string tDcYtqBMIR;
      string xbIAmophEu;
      string DFsQomNNXc;
      string wRIHPacwwm;
      string aYFXEDASDF;
      string hYPWGoJMjH;
      string cnofVeSBkM;
      string MtkQUdzVMk;
      string luJStWClAa;
      string QQMoKljZCY;
      string kzgqsnmzCb;
      string pnAyUgeWky;
      if(kqPRYQBOiC == DFsQomNNXc){cgAKuwhwGh = true;}
      else if(DFsQomNNXc == kqPRYQBOiC){fGWCsbpTeV = true;}
      if(hRXLlhieHo == wRIHPacwwm){tYSmAmNRZG = true;}
      else if(wRIHPacwwm == hRXLlhieHo){PhlFLcFpTe = true;}
      if(jgDozNlwtq == aYFXEDASDF){jCiXjcPNTc = true;}
      else if(aYFXEDASDF == jgDozNlwtq){RaYToStrLN = true;}
      if(XFfJVjCZLQ == hYPWGoJMjH){HMnEwDyWww = true;}
      else if(hYPWGoJMjH == XFfJVjCZLQ){ewVpnAfMsh = true;}
      if(tLZiWoTiSU == cnofVeSBkM){GprTgQUMyh = true;}
      else if(cnofVeSBkM == tLZiWoTiSU){EwdTGYiqRn = true;}
      if(wgDSBDmaRK == MtkQUdzVMk){SMweOZxcZS = true;}
      else if(MtkQUdzVMk == wgDSBDmaRK){fXtOhEgCMZ = true;}
      if(dFUqdblOpB == luJStWClAa){fUcdZhjOpw = true;}
      else if(luJStWClAa == dFUqdblOpB){hxIQqSMuRK = true;}
      if(fJSptYHURK == QQMoKljZCY){nqVczsKPpT = true;}
      if(tDcYtqBMIR == kzgqsnmzCb){HDOlJuPJoV = true;}
      if(xbIAmophEu == pnAyUgeWky){GVxcQlNOsz = true;}
      while(QQMoKljZCY == fJSptYHURK){wsxlZUxFNQ = true;}
      while(kzgqsnmzCb == kzgqsnmzCb){jCZWhGBGIi = true;}
      while(pnAyUgeWky == pnAyUgeWky){SdzSAHnMcm = true;}
      if(cgAKuwhwGh == true){cgAKuwhwGh = false;}
      if(tYSmAmNRZG == true){tYSmAmNRZG = false;}
      if(jCiXjcPNTc == true){jCiXjcPNTc = false;}
      if(HMnEwDyWww == true){HMnEwDyWww = false;}
      if(GprTgQUMyh == true){GprTgQUMyh = false;}
      if(SMweOZxcZS == true){SMweOZxcZS = false;}
      if(fUcdZhjOpw == true){fUcdZhjOpw = false;}
      if(nqVczsKPpT == true){nqVczsKPpT = false;}
      if(HDOlJuPJoV == true){HDOlJuPJoV = false;}
      if(GVxcQlNOsz == true){GVxcQlNOsz = false;}
      if(fGWCsbpTeV == true){fGWCsbpTeV = false;}
      if(PhlFLcFpTe == true){PhlFLcFpTe = false;}
      if(RaYToStrLN == true){RaYToStrLN = false;}
      if(ewVpnAfMsh == true){ewVpnAfMsh = false;}
      if(EwdTGYiqRn == true){EwdTGYiqRn = false;}
      if(fXtOhEgCMZ == true){fXtOhEgCMZ = false;}
      if(hxIQqSMuRK == true){hxIQqSMuRK = false;}
      if(wsxlZUxFNQ == true){wsxlZUxFNQ = false;}
      if(jCZWhGBGIi == true){jCZWhGBGIi = false;}
      if(SdzSAHnMcm == true){SdzSAHnMcm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZUUPPDHHO
{ 
  void AcaNxstPaw()
  { 
      bool WOCNeCVKBG = false;
      bool uVjNABZqbb = false;
      bool QlaDCEszJJ = false;
      bool KBkjlEOcNG = false;
      bool fMRBEZDOUR = false;
      bool MoRfhjnzKZ = false;
      bool JWAqwtjAaw = false;
      bool mwdVwEUZyc = false;
      bool BeeqwVjFBB = false;
      bool PPSmxILZFK = false;
      bool oCmXeQLujc = false;
      bool POBhYerIuZ = false;
      bool KeyYfXdpYm = false;
      bool rtUmmzqGMf = false;
      bool KnUYlBNjOR = false;
      bool QDeezKDNrH = false;
      bool mUWxkUtNuY = false;
      bool mkwOPVJZmd = false;
      bool JsaGVoPomc = false;
      bool udNEsoRXmR = false;
      string jSkEEmVBym;
      string bJTLSoiEDk;
      string fTimzqrxQA;
      string PDlcCikHgQ;
      string OkDUcolxro;
      string TqmnRPjyFM;
      string tYkyXXXqIj;
      string DaWlWtQNJJ;
      string EuFafXQxKl;
      string ylCTVpAFxE;
      string RunHlrTARX;
      string zVnuIzSJRz;
      string HafVkRYDPf;
      string sKQFrJGyon;
      string DQemmcyGLW;
      string WqnxxqOSVT;
      string TQjkenFiDy;
      string rUUdwpushI;
      string TRqrICWSHA;
      string umbUTlfsIy;
      if(jSkEEmVBym == RunHlrTARX){WOCNeCVKBG = true;}
      else if(RunHlrTARX == jSkEEmVBym){oCmXeQLujc = true;}
      if(bJTLSoiEDk == zVnuIzSJRz){uVjNABZqbb = true;}
      else if(zVnuIzSJRz == bJTLSoiEDk){POBhYerIuZ = true;}
      if(fTimzqrxQA == HafVkRYDPf){QlaDCEszJJ = true;}
      else if(HafVkRYDPf == fTimzqrxQA){KeyYfXdpYm = true;}
      if(PDlcCikHgQ == sKQFrJGyon){KBkjlEOcNG = true;}
      else if(sKQFrJGyon == PDlcCikHgQ){rtUmmzqGMf = true;}
      if(OkDUcolxro == DQemmcyGLW){fMRBEZDOUR = true;}
      else if(DQemmcyGLW == OkDUcolxro){KnUYlBNjOR = true;}
      if(TqmnRPjyFM == WqnxxqOSVT){MoRfhjnzKZ = true;}
      else if(WqnxxqOSVT == TqmnRPjyFM){QDeezKDNrH = true;}
      if(tYkyXXXqIj == TQjkenFiDy){JWAqwtjAaw = true;}
      else if(TQjkenFiDy == tYkyXXXqIj){mUWxkUtNuY = true;}
      if(DaWlWtQNJJ == rUUdwpushI){mwdVwEUZyc = true;}
      if(EuFafXQxKl == TRqrICWSHA){BeeqwVjFBB = true;}
      if(ylCTVpAFxE == umbUTlfsIy){PPSmxILZFK = true;}
      while(rUUdwpushI == DaWlWtQNJJ){mkwOPVJZmd = true;}
      while(TRqrICWSHA == TRqrICWSHA){JsaGVoPomc = true;}
      while(umbUTlfsIy == umbUTlfsIy){udNEsoRXmR = true;}
      if(WOCNeCVKBG == true){WOCNeCVKBG = false;}
      if(uVjNABZqbb == true){uVjNABZqbb = false;}
      if(QlaDCEszJJ == true){QlaDCEszJJ = false;}
      if(KBkjlEOcNG == true){KBkjlEOcNG = false;}
      if(fMRBEZDOUR == true){fMRBEZDOUR = false;}
      if(MoRfhjnzKZ == true){MoRfhjnzKZ = false;}
      if(JWAqwtjAaw == true){JWAqwtjAaw = false;}
      if(mwdVwEUZyc == true){mwdVwEUZyc = false;}
      if(BeeqwVjFBB == true){BeeqwVjFBB = false;}
      if(PPSmxILZFK == true){PPSmxILZFK = false;}
      if(oCmXeQLujc == true){oCmXeQLujc = false;}
      if(POBhYerIuZ == true){POBhYerIuZ = false;}
      if(KeyYfXdpYm == true){KeyYfXdpYm = false;}
      if(rtUmmzqGMf == true){rtUmmzqGMf = false;}
      if(KnUYlBNjOR == true){KnUYlBNjOR = false;}
      if(QDeezKDNrH == true){QDeezKDNrH = false;}
      if(mUWxkUtNuY == true){mUWxkUtNuY = false;}
      if(mkwOPVJZmd == true){mkwOPVJZmd = false;}
      if(JsaGVoPomc == true){JsaGVoPomc = false;}
      if(udNEsoRXmR == true){udNEsoRXmR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMHOSZKHIN
{ 
  void dyFoltIRYz()
  { 
      bool lqKkzSTkja = false;
      bool iOTmjQyTlH = false;
      bool GRXYubJPgp = false;
      bool XbHEzNmUfR = false;
      bool czUEVsiFWy = false;
      bool eWHyDUTkpW = false;
      bool IDDtCGGOnW = false;
      bool ccmUeGxSDB = false;
      bool sDsiKBUIBd = false;
      bool tCeJIZuaCP = false;
      bool mTRAUCilTw = false;
      bool XAhocFJUiB = false;
      bool kyNJbaycLF = false;
      bool LWQmOYlsOI = false;
      bool RhnFGsTogD = false;
      bool PaqAdnGIXs = false;
      bool DFaOjAjtaD = false;
      bool SQGaiCJICi = false;
      bool HIwIokeQIZ = false;
      bool SdVUEMHYUF = false;
      string huBNxwuDJh;
      string RpeUVZiZsk;
      string TuANXVAqwA;
      string AMLzxjGSDp;
      string rTSlyViTFJ;
      string SUNTtmtmpa;
      string wEHIgEdfXk;
      string TQVDrAcOOB;
      string mfkmgfzrFK;
      string oScbtnLJFt;
      string qCuTpCyJas;
      string JfXnmPSUaB;
      string ElZNuAmtJE;
      string nSIUJjjRxe;
      string gpQLAJtond;
      string UqhDoEbhYp;
      string PEzWFqWDdD;
      string eBXwTOVNNl;
      string FyFejxkFfE;
      string HCrHOcpsGJ;
      if(huBNxwuDJh == qCuTpCyJas){lqKkzSTkja = true;}
      else if(qCuTpCyJas == huBNxwuDJh){mTRAUCilTw = true;}
      if(RpeUVZiZsk == JfXnmPSUaB){iOTmjQyTlH = true;}
      else if(JfXnmPSUaB == RpeUVZiZsk){XAhocFJUiB = true;}
      if(TuANXVAqwA == ElZNuAmtJE){GRXYubJPgp = true;}
      else if(ElZNuAmtJE == TuANXVAqwA){kyNJbaycLF = true;}
      if(AMLzxjGSDp == nSIUJjjRxe){XbHEzNmUfR = true;}
      else if(nSIUJjjRxe == AMLzxjGSDp){LWQmOYlsOI = true;}
      if(rTSlyViTFJ == gpQLAJtond){czUEVsiFWy = true;}
      else if(gpQLAJtond == rTSlyViTFJ){RhnFGsTogD = true;}
      if(SUNTtmtmpa == UqhDoEbhYp){eWHyDUTkpW = true;}
      else if(UqhDoEbhYp == SUNTtmtmpa){PaqAdnGIXs = true;}
      if(wEHIgEdfXk == PEzWFqWDdD){IDDtCGGOnW = true;}
      else if(PEzWFqWDdD == wEHIgEdfXk){DFaOjAjtaD = true;}
      if(TQVDrAcOOB == eBXwTOVNNl){ccmUeGxSDB = true;}
      if(mfkmgfzrFK == FyFejxkFfE){sDsiKBUIBd = true;}
      if(oScbtnLJFt == HCrHOcpsGJ){tCeJIZuaCP = true;}
      while(eBXwTOVNNl == TQVDrAcOOB){SQGaiCJICi = true;}
      while(FyFejxkFfE == FyFejxkFfE){HIwIokeQIZ = true;}
      while(HCrHOcpsGJ == HCrHOcpsGJ){SdVUEMHYUF = true;}
      if(lqKkzSTkja == true){lqKkzSTkja = false;}
      if(iOTmjQyTlH == true){iOTmjQyTlH = false;}
      if(GRXYubJPgp == true){GRXYubJPgp = false;}
      if(XbHEzNmUfR == true){XbHEzNmUfR = false;}
      if(czUEVsiFWy == true){czUEVsiFWy = false;}
      if(eWHyDUTkpW == true){eWHyDUTkpW = false;}
      if(IDDtCGGOnW == true){IDDtCGGOnW = false;}
      if(ccmUeGxSDB == true){ccmUeGxSDB = false;}
      if(sDsiKBUIBd == true){sDsiKBUIBd = false;}
      if(tCeJIZuaCP == true){tCeJIZuaCP = false;}
      if(mTRAUCilTw == true){mTRAUCilTw = false;}
      if(XAhocFJUiB == true){XAhocFJUiB = false;}
      if(kyNJbaycLF == true){kyNJbaycLF = false;}
      if(LWQmOYlsOI == true){LWQmOYlsOI = false;}
      if(RhnFGsTogD == true){RhnFGsTogD = false;}
      if(PaqAdnGIXs == true){PaqAdnGIXs = false;}
      if(DFaOjAjtaD == true){DFaOjAjtaD = false;}
      if(SQGaiCJICi == true){SQGaiCJICi = false;}
      if(HIwIokeQIZ == true){HIwIokeQIZ = false;}
      if(SdVUEMHYUF == true){SdVUEMHYUF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJQQSMMYEM
{ 
  void JfMNDyBHib()
  { 
      bool zsjCoYfVGk = false;
      bool nuppVNalEV = false;
      bool FrCVxUWqEu = false;
      bool YFjHUlxYHY = false;
      bool wNBHHHDDdE = false;
      bool PcULiHqOFT = false;
      bool CnRLMhKiVj = false;
      bool QCdfZrquNo = false;
      bool RSNAeujYXM = false;
      bool thTmVHuptZ = false;
      bool wThtnMyolp = false;
      bool QwBPCjaRfR = false;
      bool xlKIohiqJR = false;
      bool wBAmsxjSLR = false;
      bool wulgwyfDkk = false;
      bool gdJcbJJYEF = false;
      bool dHfTtPuNWE = false;
      bool AHFNUCzcMq = false;
      bool CeFXkRqXLi = false;
      bool nKOGnoPRmf = false;
      string tbyaKCcfWU;
      string fmUrkMfPaK;
      string xSFIzQUaOr;
      string LMJrWTqLPd;
      string MgJgeGnesq;
      string yieoNaWpbt;
      string hBQdITcbUQ;
      string VTAwyPIXcs;
      string bogXscgTdw;
      string xBjUwKQeXL;
      string cLKcVehiqy;
      string SyMhRsUskf;
      string lIyYSTieAn;
      string zczRQQeEBN;
      string tycfcynCDD;
      string pWsrYTNkJB;
      string uDiCyozuRA;
      string NQqWlnfRuT;
      string fgbwybjHrw;
      string DstASqPZhn;
      if(tbyaKCcfWU == cLKcVehiqy){zsjCoYfVGk = true;}
      else if(cLKcVehiqy == tbyaKCcfWU){wThtnMyolp = true;}
      if(fmUrkMfPaK == SyMhRsUskf){nuppVNalEV = true;}
      else if(SyMhRsUskf == fmUrkMfPaK){QwBPCjaRfR = true;}
      if(xSFIzQUaOr == lIyYSTieAn){FrCVxUWqEu = true;}
      else if(lIyYSTieAn == xSFIzQUaOr){xlKIohiqJR = true;}
      if(LMJrWTqLPd == zczRQQeEBN){YFjHUlxYHY = true;}
      else if(zczRQQeEBN == LMJrWTqLPd){wBAmsxjSLR = true;}
      if(MgJgeGnesq == tycfcynCDD){wNBHHHDDdE = true;}
      else if(tycfcynCDD == MgJgeGnesq){wulgwyfDkk = true;}
      if(yieoNaWpbt == pWsrYTNkJB){PcULiHqOFT = true;}
      else if(pWsrYTNkJB == yieoNaWpbt){gdJcbJJYEF = true;}
      if(hBQdITcbUQ == uDiCyozuRA){CnRLMhKiVj = true;}
      else if(uDiCyozuRA == hBQdITcbUQ){dHfTtPuNWE = true;}
      if(VTAwyPIXcs == NQqWlnfRuT){QCdfZrquNo = true;}
      if(bogXscgTdw == fgbwybjHrw){RSNAeujYXM = true;}
      if(xBjUwKQeXL == DstASqPZhn){thTmVHuptZ = true;}
      while(NQqWlnfRuT == VTAwyPIXcs){AHFNUCzcMq = true;}
      while(fgbwybjHrw == fgbwybjHrw){CeFXkRqXLi = true;}
      while(DstASqPZhn == DstASqPZhn){nKOGnoPRmf = true;}
      if(zsjCoYfVGk == true){zsjCoYfVGk = false;}
      if(nuppVNalEV == true){nuppVNalEV = false;}
      if(FrCVxUWqEu == true){FrCVxUWqEu = false;}
      if(YFjHUlxYHY == true){YFjHUlxYHY = false;}
      if(wNBHHHDDdE == true){wNBHHHDDdE = false;}
      if(PcULiHqOFT == true){PcULiHqOFT = false;}
      if(CnRLMhKiVj == true){CnRLMhKiVj = false;}
      if(QCdfZrquNo == true){QCdfZrquNo = false;}
      if(RSNAeujYXM == true){RSNAeujYXM = false;}
      if(thTmVHuptZ == true){thTmVHuptZ = false;}
      if(wThtnMyolp == true){wThtnMyolp = false;}
      if(QwBPCjaRfR == true){QwBPCjaRfR = false;}
      if(xlKIohiqJR == true){xlKIohiqJR = false;}
      if(wBAmsxjSLR == true){wBAmsxjSLR = false;}
      if(wulgwyfDkk == true){wulgwyfDkk = false;}
      if(gdJcbJJYEF == true){gdJcbJJYEF = false;}
      if(dHfTtPuNWE == true){dHfTtPuNWE = false;}
      if(AHFNUCzcMq == true){AHFNUCzcMq = false;}
      if(CeFXkRqXLi == true){CeFXkRqXLi = false;}
      if(nKOGnoPRmf == true){nKOGnoPRmf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRDSJVVOSI
{ 
  void NAIasetNCM()
  { 
      bool gQiojLCofQ = false;
      bool DtObigkoFW = false;
      bool SnidTEUlNf = false;
      bool WtcaCYJCOx = false;
      bool gOqaAbxwDa = false;
      bool KmmJDrhFUe = false;
      bool qQbzsIQnYJ = false;
      bool WhZHpDxIcq = false;
      bool HXilUjHSWK = false;
      bool qEhjFPlrgq = false;
      bool LJXsDcNeTz = false;
      bool uZccXTgodJ = false;
      bool ByQORSAoBZ = false;
      bool REbkfxApir = false;
      bool WbzXORaELl = false;
      bool iwOWpMrIak = false;
      bool bXcshqxqxZ = false;
      bool SqGkmYzrAA = false;
      bool qwcPqUpEuS = false;
      bool EqOyQzzFpX = false;
      string XUSAeFkpje;
      string LjrJmJLTyi;
      string mLjsrhqgkN;
      string AoHqqXAEwF;
      string mQiqDMDSGR;
      string sYhYmMkYIx;
      string NEEWeWcBSP;
      string JHWrwVbroe;
      string dXaTTbGiDd;
      string lauzqhLMLg;
      string jCApHlBobQ;
      string kridSodjCD;
      string PsxodhLXBN;
      string KOfIubXjLh;
      string ZQGmrsqRfB;
      string EaKIQpELLZ;
      string ZcnOGWLahq;
      string RsYUczmKwj;
      string psrzIiEXqE;
      string WMYlHwbrgV;
      if(XUSAeFkpje == jCApHlBobQ){gQiojLCofQ = true;}
      else if(jCApHlBobQ == XUSAeFkpje){LJXsDcNeTz = true;}
      if(LjrJmJLTyi == kridSodjCD){DtObigkoFW = true;}
      else if(kridSodjCD == LjrJmJLTyi){uZccXTgodJ = true;}
      if(mLjsrhqgkN == PsxodhLXBN){SnidTEUlNf = true;}
      else if(PsxodhLXBN == mLjsrhqgkN){ByQORSAoBZ = true;}
      if(AoHqqXAEwF == KOfIubXjLh){WtcaCYJCOx = true;}
      else if(KOfIubXjLh == AoHqqXAEwF){REbkfxApir = true;}
      if(mQiqDMDSGR == ZQGmrsqRfB){gOqaAbxwDa = true;}
      else if(ZQGmrsqRfB == mQiqDMDSGR){WbzXORaELl = true;}
      if(sYhYmMkYIx == EaKIQpELLZ){KmmJDrhFUe = true;}
      else if(EaKIQpELLZ == sYhYmMkYIx){iwOWpMrIak = true;}
      if(NEEWeWcBSP == ZcnOGWLahq){qQbzsIQnYJ = true;}
      else if(ZcnOGWLahq == NEEWeWcBSP){bXcshqxqxZ = true;}
      if(JHWrwVbroe == RsYUczmKwj){WhZHpDxIcq = true;}
      if(dXaTTbGiDd == psrzIiEXqE){HXilUjHSWK = true;}
      if(lauzqhLMLg == WMYlHwbrgV){qEhjFPlrgq = true;}
      while(RsYUczmKwj == JHWrwVbroe){SqGkmYzrAA = true;}
      while(psrzIiEXqE == psrzIiEXqE){qwcPqUpEuS = true;}
      while(WMYlHwbrgV == WMYlHwbrgV){EqOyQzzFpX = true;}
      if(gQiojLCofQ == true){gQiojLCofQ = false;}
      if(DtObigkoFW == true){DtObigkoFW = false;}
      if(SnidTEUlNf == true){SnidTEUlNf = false;}
      if(WtcaCYJCOx == true){WtcaCYJCOx = false;}
      if(gOqaAbxwDa == true){gOqaAbxwDa = false;}
      if(KmmJDrhFUe == true){KmmJDrhFUe = false;}
      if(qQbzsIQnYJ == true){qQbzsIQnYJ = false;}
      if(WhZHpDxIcq == true){WhZHpDxIcq = false;}
      if(HXilUjHSWK == true){HXilUjHSWK = false;}
      if(qEhjFPlrgq == true){qEhjFPlrgq = false;}
      if(LJXsDcNeTz == true){LJXsDcNeTz = false;}
      if(uZccXTgodJ == true){uZccXTgodJ = false;}
      if(ByQORSAoBZ == true){ByQORSAoBZ = false;}
      if(REbkfxApir == true){REbkfxApir = false;}
      if(WbzXORaELl == true){WbzXORaELl = false;}
      if(iwOWpMrIak == true){iwOWpMrIak = false;}
      if(bXcshqxqxZ == true){bXcshqxqxZ = false;}
      if(SqGkmYzrAA == true){SqGkmYzrAA = false;}
      if(qwcPqUpEuS == true){qwcPqUpEuS = false;}
      if(EqOyQzzFpX == true){EqOyQzzFpX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GLTXBVZIPW
{ 
  void jKsAXncmad()
  { 
      bool buwgWIfbBR = false;
      bool ljNRpuffPt = false;
      bool uczJVxpTJy = false;
      bool RpCbGZlrgG = false;
      bool CCmsgexIzJ = false;
      bool ZciYZywmKZ = false;
      bool RLSCAuglKP = false;
      bool ImyJrspGcq = false;
      bool zgTAYnHcBI = false;
      bool dzhHnpikrl = false;
      bool xLyjAleZgg = false;
      bool IoJTajrRcL = false;
      bool mEkClJFqUC = false;
      bool JENqsnijzl = false;
      bool JhwUznoNgD = false;
      bool yRHgyrawyq = false;
      bool fmEeWDbSZl = false;
      bool AHRpCFIPCx = false;
      bool TrKQDrxgrB = false;
      bool NmlIFVcQyu = false;
      string SotIfnHheo;
      string MZpjPENfYL;
      string fOLMwhaNeN;
      string QeMYxhEITa;
      string JFFutHotKn;
      string rIRSbEchLx;
      string NtCRYgMQmh;
      string zFMyCZIQRo;
      string sfDqUHMtxr;
      string FWwVNOCmWN;
      string tYHcolwTQB;
      string uLPWEgpLwQ;
      string TSSubcIpjm;
      string XUtEtTYZBh;
      string LscwwsGZQf;
      string YppFsbFMAL;
      string dFjdcZRKcj;
      string IQJOEaoVyi;
      string ViYEOhdnLS;
      string OLZpEFIzTV;
      if(SotIfnHheo == tYHcolwTQB){buwgWIfbBR = true;}
      else if(tYHcolwTQB == SotIfnHheo){xLyjAleZgg = true;}
      if(MZpjPENfYL == uLPWEgpLwQ){ljNRpuffPt = true;}
      else if(uLPWEgpLwQ == MZpjPENfYL){IoJTajrRcL = true;}
      if(fOLMwhaNeN == TSSubcIpjm){uczJVxpTJy = true;}
      else if(TSSubcIpjm == fOLMwhaNeN){mEkClJFqUC = true;}
      if(QeMYxhEITa == XUtEtTYZBh){RpCbGZlrgG = true;}
      else if(XUtEtTYZBh == QeMYxhEITa){JENqsnijzl = true;}
      if(JFFutHotKn == LscwwsGZQf){CCmsgexIzJ = true;}
      else if(LscwwsGZQf == JFFutHotKn){JhwUznoNgD = true;}
      if(rIRSbEchLx == YppFsbFMAL){ZciYZywmKZ = true;}
      else if(YppFsbFMAL == rIRSbEchLx){yRHgyrawyq = true;}
      if(NtCRYgMQmh == dFjdcZRKcj){RLSCAuglKP = true;}
      else if(dFjdcZRKcj == NtCRYgMQmh){fmEeWDbSZl = true;}
      if(zFMyCZIQRo == IQJOEaoVyi){ImyJrspGcq = true;}
      if(sfDqUHMtxr == ViYEOhdnLS){zgTAYnHcBI = true;}
      if(FWwVNOCmWN == OLZpEFIzTV){dzhHnpikrl = true;}
      while(IQJOEaoVyi == zFMyCZIQRo){AHRpCFIPCx = true;}
      while(ViYEOhdnLS == ViYEOhdnLS){TrKQDrxgrB = true;}
      while(OLZpEFIzTV == OLZpEFIzTV){NmlIFVcQyu = true;}
      if(buwgWIfbBR == true){buwgWIfbBR = false;}
      if(ljNRpuffPt == true){ljNRpuffPt = false;}
      if(uczJVxpTJy == true){uczJVxpTJy = false;}
      if(RpCbGZlrgG == true){RpCbGZlrgG = false;}
      if(CCmsgexIzJ == true){CCmsgexIzJ = false;}
      if(ZciYZywmKZ == true){ZciYZywmKZ = false;}
      if(RLSCAuglKP == true){RLSCAuglKP = false;}
      if(ImyJrspGcq == true){ImyJrspGcq = false;}
      if(zgTAYnHcBI == true){zgTAYnHcBI = false;}
      if(dzhHnpikrl == true){dzhHnpikrl = false;}
      if(xLyjAleZgg == true){xLyjAleZgg = false;}
      if(IoJTajrRcL == true){IoJTajrRcL = false;}
      if(mEkClJFqUC == true){mEkClJFqUC = false;}
      if(JENqsnijzl == true){JENqsnijzl = false;}
      if(JhwUznoNgD == true){JhwUznoNgD = false;}
      if(yRHgyrawyq == true){yRHgyrawyq = false;}
      if(fmEeWDbSZl == true){fmEeWDbSZl = false;}
      if(AHRpCFIPCx == true){AHRpCFIPCx = false;}
      if(TrKQDrxgrB == true){TrKQDrxgrB = false;}
      if(NmlIFVcQyu == true){NmlIFVcQyu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRAGZLMMQX
{ 
  void GfmiLHqkVf()
  { 
      bool apbLujbKWt = false;
      bool UfHyWehsjO = false;
      bool KOKbRfuIDj = false;
      bool ZCAPYXlqsO = false;
      bool ILatALrCNG = false;
      bool VgUrUMfzsP = false;
      bool oTGlURerZy = false;
      bool spzVFymQaG = false;
      bool mrtxNsgHuL = false;
      bool rlydZoFnYh = false;
      bool fAbPMegzmV = false;
      bool YOXlbwYIYb = false;
      bool jWwNFHrVuQ = false;
      bool szrsamQekh = false;
      bool LhUYmdNMBd = false;
      bool PwPxxIDNKF = false;
      bool mLDVcZWeLo = false;
      bool ftWpPCCXaa = false;
      bool sfTRAwituR = false;
      bool iCUftAdywM = false;
      string mZTjmntNjQ;
      string mhtfPYHOdQ;
      string JrKzKPrNjD;
      string oadPJVsxfF;
      string IPBONghfdV;
      string qqVXAtPUZW;
      string ufdfaLEdVs;
      string eKhYIsqukc;
      string hMjNLyEFOO;
      string GYWJJblUmC;
      string cDJkqgJxPH;
      string DTixniuPUc;
      string HyPGlFmXPf;
      string HWHizeCzWe;
      string oHpHLmpZUa;
      string gVAKtdnCyl;
      string skgjAgLzxJ;
      string fwsonzIHuz;
      string ONDnzkVxnV;
      string qABjkDZFHe;
      if(mZTjmntNjQ == cDJkqgJxPH){apbLujbKWt = true;}
      else if(cDJkqgJxPH == mZTjmntNjQ){fAbPMegzmV = true;}
      if(mhtfPYHOdQ == DTixniuPUc){UfHyWehsjO = true;}
      else if(DTixniuPUc == mhtfPYHOdQ){YOXlbwYIYb = true;}
      if(JrKzKPrNjD == HyPGlFmXPf){KOKbRfuIDj = true;}
      else if(HyPGlFmXPf == JrKzKPrNjD){jWwNFHrVuQ = true;}
      if(oadPJVsxfF == HWHizeCzWe){ZCAPYXlqsO = true;}
      else if(HWHizeCzWe == oadPJVsxfF){szrsamQekh = true;}
      if(IPBONghfdV == oHpHLmpZUa){ILatALrCNG = true;}
      else if(oHpHLmpZUa == IPBONghfdV){LhUYmdNMBd = true;}
      if(qqVXAtPUZW == gVAKtdnCyl){VgUrUMfzsP = true;}
      else if(gVAKtdnCyl == qqVXAtPUZW){PwPxxIDNKF = true;}
      if(ufdfaLEdVs == skgjAgLzxJ){oTGlURerZy = true;}
      else if(skgjAgLzxJ == ufdfaLEdVs){mLDVcZWeLo = true;}
      if(eKhYIsqukc == fwsonzIHuz){spzVFymQaG = true;}
      if(hMjNLyEFOO == ONDnzkVxnV){mrtxNsgHuL = true;}
      if(GYWJJblUmC == qABjkDZFHe){rlydZoFnYh = true;}
      while(fwsonzIHuz == eKhYIsqukc){ftWpPCCXaa = true;}
      while(ONDnzkVxnV == ONDnzkVxnV){sfTRAwituR = true;}
      while(qABjkDZFHe == qABjkDZFHe){iCUftAdywM = true;}
      if(apbLujbKWt == true){apbLujbKWt = false;}
      if(UfHyWehsjO == true){UfHyWehsjO = false;}
      if(KOKbRfuIDj == true){KOKbRfuIDj = false;}
      if(ZCAPYXlqsO == true){ZCAPYXlqsO = false;}
      if(ILatALrCNG == true){ILatALrCNG = false;}
      if(VgUrUMfzsP == true){VgUrUMfzsP = false;}
      if(oTGlURerZy == true){oTGlURerZy = false;}
      if(spzVFymQaG == true){spzVFymQaG = false;}
      if(mrtxNsgHuL == true){mrtxNsgHuL = false;}
      if(rlydZoFnYh == true){rlydZoFnYh = false;}
      if(fAbPMegzmV == true){fAbPMegzmV = false;}
      if(YOXlbwYIYb == true){YOXlbwYIYb = false;}
      if(jWwNFHrVuQ == true){jWwNFHrVuQ = false;}
      if(szrsamQekh == true){szrsamQekh = false;}
      if(LhUYmdNMBd == true){LhUYmdNMBd = false;}
      if(PwPxxIDNKF == true){PwPxxIDNKF = false;}
      if(mLDVcZWeLo == true){mLDVcZWeLo = false;}
      if(ftWpPCCXaa == true){ftWpPCCXaa = false;}
      if(sfTRAwituR == true){sfTRAwituR = false;}
      if(iCUftAdywM == true){iCUftAdywM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LANORVUXPF
{ 
  void iLTJsfHEDd()
  { 
      bool PJKSlTuNWH = false;
      bool wkpezCcIMo = false;
      bool rLgLxRVFDq = false;
      bool LfMsOCNPym = false;
      bool XLCjdlCiFj = false;
      bool nDWwPEcyUT = false;
      bool ypKeuQYxQw = false;
      bool oMKZQgIxhL = false;
      bool OlzSDIIQcJ = false;
      bool ZOuenhAWoN = false;
      bool NFSJuasxei = false;
      bool weQJEMprbl = false;
      bool HHTGWZQfki = false;
      bool glITxISpXb = false;
      bool OKktNtylZb = false;
      bool qIuCGFlMlU = false;
      bool KNMuCJWwLu = false;
      bool sATzWwWZrb = false;
      bool bdFIrXpFNq = false;
      bool WGDDRBxoqD = false;
      string nioKsPDyPZ;
      string ABqAQfTPQT;
      string mHbKLhSbAC;
      string eluUCwIXbp;
      string qfVIaoyPLd;
      string rVCJqgHeyL;
      string xayNtOGWxU;
      string XumacHkSiW;
      string iCQWJJikdV;
      string ocZQrPhHOL;
      string hbSpFwhbgi;
      string unubbuKaDj;
      string fUraftVWhM;
      string ZdDWnGjZQN;
      string bGEtZAhxnx;
      string FGEefNiqKL;
      string aLtTIRjXmV;
      string KkKpHYQyBe;
      string MXikHTYYqa;
      string XsOEmQMjkI;
      if(nioKsPDyPZ == hbSpFwhbgi){PJKSlTuNWH = true;}
      else if(hbSpFwhbgi == nioKsPDyPZ){NFSJuasxei = true;}
      if(ABqAQfTPQT == unubbuKaDj){wkpezCcIMo = true;}
      else if(unubbuKaDj == ABqAQfTPQT){weQJEMprbl = true;}
      if(mHbKLhSbAC == fUraftVWhM){rLgLxRVFDq = true;}
      else if(fUraftVWhM == mHbKLhSbAC){HHTGWZQfki = true;}
      if(eluUCwIXbp == ZdDWnGjZQN){LfMsOCNPym = true;}
      else if(ZdDWnGjZQN == eluUCwIXbp){glITxISpXb = true;}
      if(qfVIaoyPLd == bGEtZAhxnx){XLCjdlCiFj = true;}
      else if(bGEtZAhxnx == qfVIaoyPLd){OKktNtylZb = true;}
      if(rVCJqgHeyL == FGEefNiqKL){nDWwPEcyUT = true;}
      else if(FGEefNiqKL == rVCJqgHeyL){qIuCGFlMlU = true;}
      if(xayNtOGWxU == aLtTIRjXmV){ypKeuQYxQw = true;}
      else if(aLtTIRjXmV == xayNtOGWxU){KNMuCJWwLu = true;}
      if(XumacHkSiW == KkKpHYQyBe){oMKZQgIxhL = true;}
      if(iCQWJJikdV == MXikHTYYqa){OlzSDIIQcJ = true;}
      if(ocZQrPhHOL == XsOEmQMjkI){ZOuenhAWoN = true;}
      while(KkKpHYQyBe == XumacHkSiW){sATzWwWZrb = true;}
      while(MXikHTYYqa == MXikHTYYqa){bdFIrXpFNq = true;}
      while(XsOEmQMjkI == XsOEmQMjkI){WGDDRBxoqD = true;}
      if(PJKSlTuNWH == true){PJKSlTuNWH = false;}
      if(wkpezCcIMo == true){wkpezCcIMo = false;}
      if(rLgLxRVFDq == true){rLgLxRVFDq = false;}
      if(LfMsOCNPym == true){LfMsOCNPym = false;}
      if(XLCjdlCiFj == true){XLCjdlCiFj = false;}
      if(nDWwPEcyUT == true){nDWwPEcyUT = false;}
      if(ypKeuQYxQw == true){ypKeuQYxQw = false;}
      if(oMKZQgIxhL == true){oMKZQgIxhL = false;}
      if(OlzSDIIQcJ == true){OlzSDIIQcJ = false;}
      if(ZOuenhAWoN == true){ZOuenhAWoN = false;}
      if(NFSJuasxei == true){NFSJuasxei = false;}
      if(weQJEMprbl == true){weQJEMprbl = false;}
      if(HHTGWZQfki == true){HHTGWZQfki = false;}
      if(glITxISpXb == true){glITxISpXb = false;}
      if(OKktNtylZb == true){OKktNtylZb = false;}
      if(qIuCGFlMlU == true){qIuCGFlMlU = false;}
      if(KNMuCJWwLu == true){KNMuCJWwLu = false;}
      if(sATzWwWZrb == true){sATzWwWZrb = false;}
      if(bdFIrXpFNq == true){bdFIrXpFNq = false;}
      if(WGDDRBxoqD == true){WGDDRBxoqD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEAOZHAZUE
{ 
  void YDGyuZJMWK()
  { 
      bool EZWEYpICaE = false;
      bool WPpZORfjBu = false;
      bool oJcWNxhKYb = false;
      bool TkqDgWhkbI = false;
      bool HUILTfASfx = false;
      bool iHmZquxAqa = false;
      bool IxczkkYlrr = false;
      bool itHrnTARCh = false;
      bool xOearLxRMl = false;
      bool ZhtBzKrJZh = false;
      bool HNanNoztlX = false;
      bool tfxJctSBGY = false;
      bool nGZFRBAGsc = false;
      bool bqqUainpMD = false;
      bool MCfortjjXF = false;
      bool qpCAtAnUWM = false;
      bool orBIuCnbit = false;
      bool FcnDMkakNX = false;
      bool QPinlkopZZ = false;
      bool uTTANTBWso = false;
      string SitTSoSQHf;
      string NBwQbzFbUr;
      string lPlqXnQjRj;
      string oChbVssfap;
      string ecmlLbrxgh;
      string lbcdBCxDud;
      string XiyWpKSUuh;
      string GZAeMJczfu;
      string wSDjxMYEZS;
      string wpjwRwdPwA;
      string JXCybMaxQr;
      string ZxXzhEeOYc;
      string lNtclPoENQ;
      string fNDelYQEHk;
      string lanhrzSjNM;
      string QPpSOucZMM;
      string WWjALMtrNJ;
      string nZGnqKYMjl;
      string xFpAzQWjPp;
      string upruOPqnVf;
      if(SitTSoSQHf == JXCybMaxQr){EZWEYpICaE = true;}
      else if(JXCybMaxQr == SitTSoSQHf){HNanNoztlX = true;}
      if(NBwQbzFbUr == ZxXzhEeOYc){WPpZORfjBu = true;}
      else if(ZxXzhEeOYc == NBwQbzFbUr){tfxJctSBGY = true;}
      if(lPlqXnQjRj == lNtclPoENQ){oJcWNxhKYb = true;}
      else if(lNtclPoENQ == lPlqXnQjRj){nGZFRBAGsc = true;}
      if(oChbVssfap == fNDelYQEHk){TkqDgWhkbI = true;}
      else if(fNDelYQEHk == oChbVssfap){bqqUainpMD = true;}
      if(ecmlLbrxgh == lanhrzSjNM){HUILTfASfx = true;}
      else if(lanhrzSjNM == ecmlLbrxgh){MCfortjjXF = true;}
      if(lbcdBCxDud == QPpSOucZMM){iHmZquxAqa = true;}
      else if(QPpSOucZMM == lbcdBCxDud){qpCAtAnUWM = true;}
      if(XiyWpKSUuh == WWjALMtrNJ){IxczkkYlrr = true;}
      else if(WWjALMtrNJ == XiyWpKSUuh){orBIuCnbit = true;}
      if(GZAeMJczfu == nZGnqKYMjl){itHrnTARCh = true;}
      if(wSDjxMYEZS == xFpAzQWjPp){xOearLxRMl = true;}
      if(wpjwRwdPwA == upruOPqnVf){ZhtBzKrJZh = true;}
      while(nZGnqKYMjl == GZAeMJczfu){FcnDMkakNX = true;}
      while(xFpAzQWjPp == xFpAzQWjPp){QPinlkopZZ = true;}
      while(upruOPqnVf == upruOPqnVf){uTTANTBWso = true;}
      if(EZWEYpICaE == true){EZWEYpICaE = false;}
      if(WPpZORfjBu == true){WPpZORfjBu = false;}
      if(oJcWNxhKYb == true){oJcWNxhKYb = false;}
      if(TkqDgWhkbI == true){TkqDgWhkbI = false;}
      if(HUILTfASfx == true){HUILTfASfx = false;}
      if(iHmZquxAqa == true){iHmZquxAqa = false;}
      if(IxczkkYlrr == true){IxczkkYlrr = false;}
      if(itHrnTARCh == true){itHrnTARCh = false;}
      if(xOearLxRMl == true){xOearLxRMl = false;}
      if(ZhtBzKrJZh == true){ZhtBzKrJZh = false;}
      if(HNanNoztlX == true){HNanNoztlX = false;}
      if(tfxJctSBGY == true){tfxJctSBGY = false;}
      if(nGZFRBAGsc == true){nGZFRBAGsc = false;}
      if(bqqUainpMD == true){bqqUainpMD = false;}
      if(MCfortjjXF == true){MCfortjjXF = false;}
      if(qpCAtAnUWM == true){qpCAtAnUWM = false;}
      if(orBIuCnbit == true){orBIuCnbit = false;}
      if(FcnDMkakNX == true){FcnDMkakNX = false;}
      if(QPinlkopZZ == true){QPinlkopZZ = false;}
      if(uTTANTBWso == true){uTTANTBWso = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SCGMANQZBU
{ 
  void TxRmUTnuky()
  { 
      bool KJSDdooKEA = false;
      bool WxhzRbgKkl = false;
      bool ReTCafXiiz = false;
      bool WHtZQbWgim = false;
      bool YWNoXSdXGE = false;
      bool YKnxteoQby = false;
      bool QFbFdPCIio = false;
      bool FAbxNtRedI = false;
      bool CAceZLSxfk = false;
      bool lGEjWSuHLH = false;
      bool PVoQyYiqiz = false;
      bool NKlSwQbxeR = false;
      bool xFbxDyuqat = false;
      bool zJTVsfKMfB = false;
      bool caNfXbTlnG = false;
      bool pxcsKKsqNz = false;
      bool dqPoADpPZP = false;
      bool FPQdoVquYa = false;
      bool eJDTEBgaLh = false;
      bool mSyfXkLYfU = false;
      string YelHsqfYDQ;
      string eUCjgaGzqa;
      string qVshjdYdFR;
      string WojuVRNkrM;
      string gAZfUKxdWV;
      string tDmUBDlDWO;
      string SBTktokHNO;
      string NUHdsqwMMZ;
      string guGjXSCPsR;
      string fJNctfgnke;
      string ZoPIHYuIbK;
      string HYpxhXtjNb;
      string mUNwhEGejN;
      string KHbhzqeyby;
      string WtniKHSQtW;
      string kwZJrEbTZD;
      string RQXNzzxIxq;
      string rwHOErgdka;
      string kpjNbNhRou;
      string PLXXfFVZjL;
      if(YelHsqfYDQ == ZoPIHYuIbK){KJSDdooKEA = true;}
      else if(ZoPIHYuIbK == YelHsqfYDQ){PVoQyYiqiz = true;}
      if(eUCjgaGzqa == HYpxhXtjNb){WxhzRbgKkl = true;}
      else if(HYpxhXtjNb == eUCjgaGzqa){NKlSwQbxeR = true;}
      if(qVshjdYdFR == mUNwhEGejN){ReTCafXiiz = true;}
      else if(mUNwhEGejN == qVshjdYdFR){xFbxDyuqat = true;}
      if(WojuVRNkrM == KHbhzqeyby){WHtZQbWgim = true;}
      else if(KHbhzqeyby == WojuVRNkrM){zJTVsfKMfB = true;}
      if(gAZfUKxdWV == WtniKHSQtW){YWNoXSdXGE = true;}
      else if(WtniKHSQtW == gAZfUKxdWV){caNfXbTlnG = true;}
      if(tDmUBDlDWO == kwZJrEbTZD){YKnxteoQby = true;}
      else if(kwZJrEbTZD == tDmUBDlDWO){pxcsKKsqNz = true;}
      if(SBTktokHNO == RQXNzzxIxq){QFbFdPCIio = true;}
      else if(RQXNzzxIxq == SBTktokHNO){dqPoADpPZP = true;}
      if(NUHdsqwMMZ == rwHOErgdka){FAbxNtRedI = true;}
      if(guGjXSCPsR == kpjNbNhRou){CAceZLSxfk = true;}
      if(fJNctfgnke == PLXXfFVZjL){lGEjWSuHLH = true;}
      while(rwHOErgdka == NUHdsqwMMZ){FPQdoVquYa = true;}
      while(kpjNbNhRou == kpjNbNhRou){eJDTEBgaLh = true;}
      while(PLXXfFVZjL == PLXXfFVZjL){mSyfXkLYfU = true;}
      if(KJSDdooKEA == true){KJSDdooKEA = false;}
      if(WxhzRbgKkl == true){WxhzRbgKkl = false;}
      if(ReTCafXiiz == true){ReTCafXiiz = false;}
      if(WHtZQbWgim == true){WHtZQbWgim = false;}
      if(YWNoXSdXGE == true){YWNoXSdXGE = false;}
      if(YKnxteoQby == true){YKnxteoQby = false;}
      if(QFbFdPCIio == true){QFbFdPCIio = false;}
      if(FAbxNtRedI == true){FAbxNtRedI = false;}
      if(CAceZLSxfk == true){CAceZLSxfk = false;}
      if(lGEjWSuHLH == true){lGEjWSuHLH = false;}
      if(PVoQyYiqiz == true){PVoQyYiqiz = false;}
      if(NKlSwQbxeR == true){NKlSwQbxeR = false;}
      if(xFbxDyuqat == true){xFbxDyuqat = false;}
      if(zJTVsfKMfB == true){zJTVsfKMfB = false;}
      if(caNfXbTlnG == true){caNfXbTlnG = false;}
      if(pxcsKKsqNz == true){pxcsKKsqNz = false;}
      if(dqPoADpPZP == true){dqPoADpPZP = false;}
      if(FPQdoVquYa == true){FPQdoVquYa = false;}
      if(eJDTEBgaLh == true){eJDTEBgaLh = false;}
      if(mSyfXkLYfU == true){mSyfXkLYfU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEJJEVNTAJ
{ 
  void MAqkIkPoAg()
  { 
      bool DVngnFXijT = false;
      bool tgPFsrLMta = false;
      bool AOAideRznF = false;
      bool ffRbQxaYOg = false;
      bool JazIQzzAXl = false;
      bool GVQpJnUFCI = false;
      bool mXudmNOnnw = false;
      bool RlyNRZPqRd = false;
      bool eRaByKPbRb = false;
      bool bUVFtkeUVD = false;
      bool jLLbTTXDYj = false;
      bool YdmXcVwsfc = false;
      bool ymWLTwQrTf = false;
      bool ttVOsTFzhd = false;
      bool lLDhDyhybX = false;
      bool nlorFxnzHW = false;
      bool DfjrodHYdJ = false;
      bool PxLCqljnIV = false;
      bool ORPurIFdIw = false;
      bool eFrKZFbKrY = false;
      string NZKoYYPCZR;
      string nUyezqTURN;
      string AYdNZzjjua;
      string KdpnfmkrYj;
      string NsFWFCgHIk;
      string hLgylowwPZ;
      string nfGyGJdJyM;
      string GawgzHSGHW;
      string SbaKszxrCq;
      string qncyuhlHPu;
      string YWJueGOzyd;
      string VoosGMEwFH;
      string MlHHVRyxkQ;
      string VLqLywRfel;
      string jxsYUBziri;
      string doBHilPCZM;
      string HROhHKycuK;
      string uXRSXOrhlT;
      string SOFCmgJicL;
      string gPFReSiLQK;
      if(NZKoYYPCZR == YWJueGOzyd){DVngnFXijT = true;}
      else if(YWJueGOzyd == NZKoYYPCZR){jLLbTTXDYj = true;}
      if(nUyezqTURN == VoosGMEwFH){tgPFsrLMta = true;}
      else if(VoosGMEwFH == nUyezqTURN){YdmXcVwsfc = true;}
      if(AYdNZzjjua == MlHHVRyxkQ){AOAideRznF = true;}
      else if(MlHHVRyxkQ == AYdNZzjjua){ymWLTwQrTf = true;}
      if(KdpnfmkrYj == VLqLywRfel){ffRbQxaYOg = true;}
      else if(VLqLywRfel == KdpnfmkrYj){ttVOsTFzhd = true;}
      if(NsFWFCgHIk == jxsYUBziri){JazIQzzAXl = true;}
      else if(jxsYUBziri == NsFWFCgHIk){lLDhDyhybX = true;}
      if(hLgylowwPZ == doBHilPCZM){GVQpJnUFCI = true;}
      else if(doBHilPCZM == hLgylowwPZ){nlorFxnzHW = true;}
      if(nfGyGJdJyM == HROhHKycuK){mXudmNOnnw = true;}
      else if(HROhHKycuK == nfGyGJdJyM){DfjrodHYdJ = true;}
      if(GawgzHSGHW == uXRSXOrhlT){RlyNRZPqRd = true;}
      if(SbaKszxrCq == SOFCmgJicL){eRaByKPbRb = true;}
      if(qncyuhlHPu == gPFReSiLQK){bUVFtkeUVD = true;}
      while(uXRSXOrhlT == GawgzHSGHW){PxLCqljnIV = true;}
      while(SOFCmgJicL == SOFCmgJicL){ORPurIFdIw = true;}
      while(gPFReSiLQK == gPFReSiLQK){eFrKZFbKrY = true;}
      if(DVngnFXijT == true){DVngnFXijT = false;}
      if(tgPFsrLMta == true){tgPFsrLMta = false;}
      if(AOAideRznF == true){AOAideRznF = false;}
      if(ffRbQxaYOg == true){ffRbQxaYOg = false;}
      if(JazIQzzAXl == true){JazIQzzAXl = false;}
      if(GVQpJnUFCI == true){GVQpJnUFCI = false;}
      if(mXudmNOnnw == true){mXudmNOnnw = false;}
      if(RlyNRZPqRd == true){RlyNRZPqRd = false;}
      if(eRaByKPbRb == true){eRaByKPbRb = false;}
      if(bUVFtkeUVD == true){bUVFtkeUVD = false;}
      if(jLLbTTXDYj == true){jLLbTTXDYj = false;}
      if(YdmXcVwsfc == true){YdmXcVwsfc = false;}
      if(ymWLTwQrTf == true){ymWLTwQrTf = false;}
      if(ttVOsTFzhd == true){ttVOsTFzhd = false;}
      if(lLDhDyhybX == true){lLDhDyhybX = false;}
      if(nlorFxnzHW == true){nlorFxnzHW = false;}
      if(DfjrodHYdJ == true){DfjrodHYdJ = false;}
      if(PxLCqljnIV == true){PxLCqljnIV = false;}
      if(ORPurIFdIw == true){ORPurIFdIw = false;}
      if(eFrKZFbKrY == true){eFrKZFbKrY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VLSQKJMZAU
{ 
  void pZmYTmdQft()
  { 
      bool FYZAqOXCQY = false;
      bool aMeyOxqxTe = false;
      bool SecqDDPchd = false;
      bool PIjthJubuO = false;
      bool zbqRqXkCjY = false;
      bool IjTHHawhwn = false;
      bool ytTlIScjQE = false;
      bool CPBEeqmKAf = false;
      bool RNsIUfnblH = false;
      bool NMeHPFHFJY = false;
      bool tAleVshObQ = false;
      bool nlhPVkAKQc = false;
      bool dByIqpjtnZ = false;
      bool ihAalQaOmb = false;
      bool xYzUTadOke = false;
      bool EwngtrCcnf = false;
      bool ImaCgFkGdE = false;
      bool JlXoeEBcoP = false;
      bool MUJJVmtTgs = false;
      bool OyZGTJyxmN = false;
      string RilHIrEuZJ;
      string tYFXjPEjjz;
      string KwwDTjzpBS;
      string EdzfZUKUVo;
      string BQJyCcUphe;
      string GzdFRUminX;
      string sOtHEPZYxO;
      string EjOuxsmxAq;
      string PIHVMFAsNF;
      string hbfxwmWCtl;
      string CurTZWkiIY;
      string hohxIjGXtz;
      string PfLrfcDQyK;
      string WkCOnTPnwo;
      string URkoXrsinL;
      string gzHuWVizmx;
      string STjxCwmTIn;
      string TRbEdxuWUn;
      string iUbmdWdHqR;
      string kPByWAgmma;
      if(RilHIrEuZJ == CurTZWkiIY){FYZAqOXCQY = true;}
      else if(CurTZWkiIY == RilHIrEuZJ){tAleVshObQ = true;}
      if(tYFXjPEjjz == hohxIjGXtz){aMeyOxqxTe = true;}
      else if(hohxIjGXtz == tYFXjPEjjz){nlhPVkAKQc = true;}
      if(KwwDTjzpBS == PfLrfcDQyK){SecqDDPchd = true;}
      else if(PfLrfcDQyK == KwwDTjzpBS){dByIqpjtnZ = true;}
      if(EdzfZUKUVo == WkCOnTPnwo){PIjthJubuO = true;}
      else if(WkCOnTPnwo == EdzfZUKUVo){ihAalQaOmb = true;}
      if(BQJyCcUphe == URkoXrsinL){zbqRqXkCjY = true;}
      else if(URkoXrsinL == BQJyCcUphe){xYzUTadOke = true;}
      if(GzdFRUminX == gzHuWVizmx){IjTHHawhwn = true;}
      else if(gzHuWVizmx == GzdFRUminX){EwngtrCcnf = true;}
      if(sOtHEPZYxO == STjxCwmTIn){ytTlIScjQE = true;}
      else if(STjxCwmTIn == sOtHEPZYxO){ImaCgFkGdE = true;}
      if(EjOuxsmxAq == TRbEdxuWUn){CPBEeqmKAf = true;}
      if(PIHVMFAsNF == iUbmdWdHqR){RNsIUfnblH = true;}
      if(hbfxwmWCtl == kPByWAgmma){NMeHPFHFJY = true;}
      while(TRbEdxuWUn == EjOuxsmxAq){JlXoeEBcoP = true;}
      while(iUbmdWdHqR == iUbmdWdHqR){MUJJVmtTgs = true;}
      while(kPByWAgmma == kPByWAgmma){OyZGTJyxmN = true;}
      if(FYZAqOXCQY == true){FYZAqOXCQY = false;}
      if(aMeyOxqxTe == true){aMeyOxqxTe = false;}
      if(SecqDDPchd == true){SecqDDPchd = false;}
      if(PIjthJubuO == true){PIjthJubuO = false;}
      if(zbqRqXkCjY == true){zbqRqXkCjY = false;}
      if(IjTHHawhwn == true){IjTHHawhwn = false;}
      if(ytTlIScjQE == true){ytTlIScjQE = false;}
      if(CPBEeqmKAf == true){CPBEeqmKAf = false;}
      if(RNsIUfnblH == true){RNsIUfnblH = false;}
      if(NMeHPFHFJY == true){NMeHPFHFJY = false;}
      if(tAleVshObQ == true){tAleVshObQ = false;}
      if(nlhPVkAKQc == true){nlhPVkAKQc = false;}
      if(dByIqpjtnZ == true){dByIqpjtnZ = false;}
      if(ihAalQaOmb == true){ihAalQaOmb = false;}
      if(xYzUTadOke == true){xYzUTadOke = false;}
      if(EwngtrCcnf == true){EwngtrCcnf = false;}
      if(ImaCgFkGdE == true){ImaCgFkGdE = false;}
      if(JlXoeEBcoP == true){JlXoeEBcoP = false;}
      if(MUJJVmtTgs == true){MUJJVmtTgs = false;}
      if(OyZGTJyxmN == true){OyZGTJyxmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNNJCOIRRV
{ 
  void jRUINFWzCU()
  { 
      bool BrwzzFHxTj = false;
      bool bkBjjsDOja = false;
      bool DJPOdjnpXX = false;
      bool THCfnPKmjQ = false;
      bool qUUJNfYSaI = false;
      bool UEBjrqcgUO = false;
      bool QQYwQThUwU = false;
      bool iPeSjhoGBy = false;
      bool KUOPCPGSmx = false;
      bool mdRUzZuXss = false;
      bool xDWGZEZhAJ = false;
      bool BVeVEwCJsA = false;
      bool MPhygExJSK = false;
      bool mQMHAGxIpx = false;
      bool pYRcuQywQD = false;
      bool XkerfgVXYU = false;
      bool HPOoWkJXUx = false;
      bool ysTuKnxEDQ = false;
      bool GBsPmBlTbS = false;
      bool jZiUpaJbGK = false;
      string PeAtVGQQWm;
      string fYylbqMclT;
      string DUxeRpPBCl;
      string tTZcTjAqnR;
      string heiSlDWnHt;
      string cKLKHthUcf;
      string qPOkrLyVRr;
      string pVoUkYlesO;
      string SasHJiHPUY;
      string CeOIaSPyZa;
      string EBWPDHVqYi;
      string IDbONPVGbJ;
      string DiAroLGgsS;
      string InERJREdEB;
      string NQplQzCAtK;
      string xJWPXUAdZr;
      string AoxFZUyKEu;
      string LqCZwmrObo;
      string IGliVyRnto;
      string QaDLBXSkLu;
      if(PeAtVGQQWm == EBWPDHVqYi){BrwzzFHxTj = true;}
      else if(EBWPDHVqYi == PeAtVGQQWm){xDWGZEZhAJ = true;}
      if(fYylbqMclT == IDbONPVGbJ){bkBjjsDOja = true;}
      else if(IDbONPVGbJ == fYylbqMclT){BVeVEwCJsA = true;}
      if(DUxeRpPBCl == DiAroLGgsS){DJPOdjnpXX = true;}
      else if(DiAroLGgsS == DUxeRpPBCl){MPhygExJSK = true;}
      if(tTZcTjAqnR == InERJREdEB){THCfnPKmjQ = true;}
      else if(InERJREdEB == tTZcTjAqnR){mQMHAGxIpx = true;}
      if(heiSlDWnHt == NQplQzCAtK){qUUJNfYSaI = true;}
      else if(NQplQzCAtK == heiSlDWnHt){pYRcuQywQD = true;}
      if(cKLKHthUcf == xJWPXUAdZr){UEBjrqcgUO = true;}
      else if(xJWPXUAdZr == cKLKHthUcf){XkerfgVXYU = true;}
      if(qPOkrLyVRr == AoxFZUyKEu){QQYwQThUwU = true;}
      else if(AoxFZUyKEu == qPOkrLyVRr){HPOoWkJXUx = true;}
      if(pVoUkYlesO == LqCZwmrObo){iPeSjhoGBy = true;}
      if(SasHJiHPUY == IGliVyRnto){KUOPCPGSmx = true;}
      if(CeOIaSPyZa == QaDLBXSkLu){mdRUzZuXss = true;}
      while(LqCZwmrObo == pVoUkYlesO){ysTuKnxEDQ = true;}
      while(IGliVyRnto == IGliVyRnto){GBsPmBlTbS = true;}
      while(QaDLBXSkLu == QaDLBXSkLu){jZiUpaJbGK = true;}
      if(BrwzzFHxTj == true){BrwzzFHxTj = false;}
      if(bkBjjsDOja == true){bkBjjsDOja = false;}
      if(DJPOdjnpXX == true){DJPOdjnpXX = false;}
      if(THCfnPKmjQ == true){THCfnPKmjQ = false;}
      if(qUUJNfYSaI == true){qUUJNfYSaI = false;}
      if(UEBjrqcgUO == true){UEBjrqcgUO = false;}
      if(QQYwQThUwU == true){QQYwQThUwU = false;}
      if(iPeSjhoGBy == true){iPeSjhoGBy = false;}
      if(KUOPCPGSmx == true){KUOPCPGSmx = false;}
      if(mdRUzZuXss == true){mdRUzZuXss = false;}
      if(xDWGZEZhAJ == true){xDWGZEZhAJ = false;}
      if(BVeVEwCJsA == true){BVeVEwCJsA = false;}
      if(MPhygExJSK == true){MPhygExJSK = false;}
      if(mQMHAGxIpx == true){mQMHAGxIpx = false;}
      if(pYRcuQywQD == true){pYRcuQywQD = false;}
      if(XkerfgVXYU == true){XkerfgVXYU = false;}
      if(HPOoWkJXUx == true){HPOoWkJXUx = false;}
      if(ysTuKnxEDQ == true){ysTuKnxEDQ = false;}
      if(GBsPmBlTbS == true){GBsPmBlTbS = false;}
      if(jZiUpaJbGK == true){jZiUpaJbGK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWBXCINBET
{ 
  void SBkDVUlZIH()
  { 
      bool dWuyIUwgff = false;
      bool bbuxbkzBIH = false;
      bool UDUtWLLHkD = false;
      bool DPHwiDKLJn = false;
      bool EonCPqmOEo = false;
      bool aDBKOaCBax = false;
      bool InubcMUyNX = false;
      bool ZnrTDeORef = false;
      bool XxDuczNxgI = false;
      bool BJjMfPtMZC = false;
      bool WoAfOmLhGj = false;
      bool LjVuZLkAzc = false;
      bool yWRFWPDfnn = false;
      bool kCrbJiwXfo = false;
      bool nfpwwQmnlT = false;
      bool dsNxEzWuIz = false;
      bool jftSzJqtlp = false;
      bool PNTJnRgUJF = false;
      bool cOsTJqouWJ = false;
      bool LBOgFIlXxl = false;
      string gBoYhHlAIM;
      string iGXPgaokda;
      string FmrSxxMrrf;
      string CjJDbNXnlB;
      string iOAlWBXVtG;
      string gISMjsJWbk;
      string ttIcKzxUnT;
      string CAzcrqmGuw;
      string YpylytQwTh;
      string EBMAGoGWaX;
      string DDgaDfIpUs;
      string GCaeLDwVdQ;
      string iBAGOBnyVC;
      string kPeXsVJXhS;
      string kZbaaBZgnD;
      string sjrKoBCaLC;
      string rJURIqWDlp;
      string tXmLeIZZfN;
      string aGKSJAWThq;
      string TiMfaaFJRi;
      if(gBoYhHlAIM == DDgaDfIpUs){dWuyIUwgff = true;}
      else if(DDgaDfIpUs == gBoYhHlAIM){WoAfOmLhGj = true;}
      if(iGXPgaokda == GCaeLDwVdQ){bbuxbkzBIH = true;}
      else if(GCaeLDwVdQ == iGXPgaokda){LjVuZLkAzc = true;}
      if(FmrSxxMrrf == iBAGOBnyVC){UDUtWLLHkD = true;}
      else if(iBAGOBnyVC == FmrSxxMrrf){yWRFWPDfnn = true;}
      if(CjJDbNXnlB == kPeXsVJXhS){DPHwiDKLJn = true;}
      else if(kPeXsVJXhS == CjJDbNXnlB){kCrbJiwXfo = true;}
      if(iOAlWBXVtG == kZbaaBZgnD){EonCPqmOEo = true;}
      else if(kZbaaBZgnD == iOAlWBXVtG){nfpwwQmnlT = true;}
      if(gISMjsJWbk == sjrKoBCaLC){aDBKOaCBax = true;}
      else if(sjrKoBCaLC == gISMjsJWbk){dsNxEzWuIz = true;}
      if(ttIcKzxUnT == rJURIqWDlp){InubcMUyNX = true;}
      else if(rJURIqWDlp == ttIcKzxUnT){jftSzJqtlp = true;}
      if(CAzcrqmGuw == tXmLeIZZfN){ZnrTDeORef = true;}
      if(YpylytQwTh == aGKSJAWThq){XxDuczNxgI = true;}
      if(EBMAGoGWaX == TiMfaaFJRi){BJjMfPtMZC = true;}
      while(tXmLeIZZfN == CAzcrqmGuw){PNTJnRgUJF = true;}
      while(aGKSJAWThq == aGKSJAWThq){cOsTJqouWJ = true;}
      while(TiMfaaFJRi == TiMfaaFJRi){LBOgFIlXxl = true;}
      if(dWuyIUwgff == true){dWuyIUwgff = false;}
      if(bbuxbkzBIH == true){bbuxbkzBIH = false;}
      if(UDUtWLLHkD == true){UDUtWLLHkD = false;}
      if(DPHwiDKLJn == true){DPHwiDKLJn = false;}
      if(EonCPqmOEo == true){EonCPqmOEo = false;}
      if(aDBKOaCBax == true){aDBKOaCBax = false;}
      if(InubcMUyNX == true){InubcMUyNX = false;}
      if(ZnrTDeORef == true){ZnrTDeORef = false;}
      if(XxDuczNxgI == true){XxDuczNxgI = false;}
      if(BJjMfPtMZC == true){BJjMfPtMZC = false;}
      if(WoAfOmLhGj == true){WoAfOmLhGj = false;}
      if(LjVuZLkAzc == true){LjVuZLkAzc = false;}
      if(yWRFWPDfnn == true){yWRFWPDfnn = false;}
      if(kCrbJiwXfo == true){kCrbJiwXfo = false;}
      if(nfpwwQmnlT == true){nfpwwQmnlT = false;}
      if(dsNxEzWuIz == true){dsNxEzWuIz = false;}
      if(jftSzJqtlp == true){jftSzJqtlp = false;}
      if(PNTJnRgUJF == true){PNTJnRgUJF = false;}
      if(cOsTJqouWJ == true){cOsTJqouWJ = false;}
      if(LBOgFIlXxl == true){LBOgFIlXxl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJMBIODKBN
{ 
  void hzddlAnlUL()
  { 
      bool YebjOKwBtI = false;
      bool LKZEOniJbR = false;
      bool obEckEmxoN = false;
      bool xyzgEYaSoR = false;
      bool dhjaNqRMwf = false;
      bool rabpWwZzyJ = false;
      bool WyLgKMKsAo = false;
      bool NQTJmHqdOt = false;
      bool maAIUWWIJH = false;
      bool zbUfueVCPB = false;
      bool fXMHSbGRDP = false;
      bool FwjEVwyDMn = false;
      bool pCirplwnOH = false;
      bool koNMNOOspr = false;
      bool PEFtCCqPJy = false;
      bool gSoaLdnTRg = false;
      bool fSCudPhWqG = false;
      bool hEMUYkwopm = false;
      bool tfdQZSzlBi = false;
      bool atbJMxCKPl = false;
      string GyoZmHdWLU;
      string noxklEebOU;
      string VLXaQqqmQH;
      string oiSTAcxcYh;
      string JxjTczBhzw;
      string YOIJuuaNIw;
      string PqGDeFWdjJ;
      string GBCgLXaEyR;
      string pInTiaZIXF;
      string BiUcRSqfnW;
      string cWyopWLbyX;
      string TWPqFHClUE;
      string fNGeIXfZOr;
      string ftPanSKydL;
      string OxKzkeTdWK;
      string PFLjqOQSgS;
      string qlNFrYGnCm;
      string wEIJohDGsc;
      string DCCDcaiejZ;
      string BqQKUbjEHM;
      if(GyoZmHdWLU == cWyopWLbyX){YebjOKwBtI = true;}
      else if(cWyopWLbyX == GyoZmHdWLU){fXMHSbGRDP = true;}
      if(noxklEebOU == TWPqFHClUE){LKZEOniJbR = true;}
      else if(TWPqFHClUE == noxklEebOU){FwjEVwyDMn = true;}
      if(VLXaQqqmQH == fNGeIXfZOr){obEckEmxoN = true;}
      else if(fNGeIXfZOr == VLXaQqqmQH){pCirplwnOH = true;}
      if(oiSTAcxcYh == ftPanSKydL){xyzgEYaSoR = true;}
      else if(ftPanSKydL == oiSTAcxcYh){koNMNOOspr = true;}
      if(JxjTczBhzw == OxKzkeTdWK){dhjaNqRMwf = true;}
      else if(OxKzkeTdWK == JxjTczBhzw){PEFtCCqPJy = true;}
      if(YOIJuuaNIw == PFLjqOQSgS){rabpWwZzyJ = true;}
      else if(PFLjqOQSgS == YOIJuuaNIw){gSoaLdnTRg = true;}
      if(PqGDeFWdjJ == qlNFrYGnCm){WyLgKMKsAo = true;}
      else if(qlNFrYGnCm == PqGDeFWdjJ){fSCudPhWqG = true;}
      if(GBCgLXaEyR == wEIJohDGsc){NQTJmHqdOt = true;}
      if(pInTiaZIXF == DCCDcaiejZ){maAIUWWIJH = true;}
      if(BiUcRSqfnW == BqQKUbjEHM){zbUfueVCPB = true;}
      while(wEIJohDGsc == GBCgLXaEyR){hEMUYkwopm = true;}
      while(DCCDcaiejZ == DCCDcaiejZ){tfdQZSzlBi = true;}
      while(BqQKUbjEHM == BqQKUbjEHM){atbJMxCKPl = true;}
      if(YebjOKwBtI == true){YebjOKwBtI = false;}
      if(LKZEOniJbR == true){LKZEOniJbR = false;}
      if(obEckEmxoN == true){obEckEmxoN = false;}
      if(xyzgEYaSoR == true){xyzgEYaSoR = false;}
      if(dhjaNqRMwf == true){dhjaNqRMwf = false;}
      if(rabpWwZzyJ == true){rabpWwZzyJ = false;}
      if(WyLgKMKsAo == true){WyLgKMKsAo = false;}
      if(NQTJmHqdOt == true){NQTJmHqdOt = false;}
      if(maAIUWWIJH == true){maAIUWWIJH = false;}
      if(zbUfueVCPB == true){zbUfueVCPB = false;}
      if(fXMHSbGRDP == true){fXMHSbGRDP = false;}
      if(FwjEVwyDMn == true){FwjEVwyDMn = false;}
      if(pCirplwnOH == true){pCirplwnOH = false;}
      if(koNMNOOspr == true){koNMNOOspr = false;}
      if(PEFtCCqPJy == true){PEFtCCqPJy = false;}
      if(gSoaLdnTRg == true){gSoaLdnTRg = false;}
      if(fSCudPhWqG == true){fSCudPhWqG = false;}
      if(hEMUYkwopm == true){hEMUYkwopm = false;}
      if(tfdQZSzlBi == true){tfdQZSzlBi = false;}
      if(atbJMxCKPl == true){atbJMxCKPl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDZJNFIFPU
{ 
  void zBUkNFPbII()
  { 
      bool rZOPAgZqUC = false;
      bool mrbSqyNrNZ = false;
      bool rkoaOBTedZ = false;
      bool wRrBewRPUT = false;
      bool xQChynVmJh = false;
      bool hlYLsHjnBy = false;
      bool MuMtGUAamt = false;
      bool gxWtcbhHbZ = false;
      bool egVwrJsgIX = false;
      bool MdOVGBDHbc = false;
      bool nuAOAjOdhQ = false;
      bool YcLaSfYQCw = false;
      bool bTSOgCiAna = false;
      bool XZezljfGuH = false;
      bool uPyqyjSnDZ = false;
      bool cmFfBUckhx = false;
      bool ANoHszxLni = false;
      bool zSVtBLUaPx = false;
      bool juxNykUzyR = false;
      bool GuYxHgZqxz = false;
      string TksWebHhgq;
      string lzmKGsIsKq;
      string TbzxDsMYpL;
      string HsXOnJijtb;
      string JptkoaHKMs;
      string LiRBEqkwSk;
      string OhqVisbXVx;
      string JYzigchOIc;
      string lBMxzYaVKw;
      string XmQJNbzXBu;
      string yinPimiiTa;
      string JWmpyMVsWK;
      string SGMZYVHpVF;
      string dJNNdDNwNM;
      string orBilBzaKA;
      string FFBpcrVOpN;
      string fsNOxAIZLu;
      string zYfKVZFdmX;
      string VgeUAXHXjk;
      string gyFAfudmkk;
      if(TksWebHhgq == yinPimiiTa){rZOPAgZqUC = true;}
      else if(yinPimiiTa == TksWebHhgq){nuAOAjOdhQ = true;}
      if(lzmKGsIsKq == JWmpyMVsWK){mrbSqyNrNZ = true;}
      else if(JWmpyMVsWK == lzmKGsIsKq){YcLaSfYQCw = true;}
      if(TbzxDsMYpL == SGMZYVHpVF){rkoaOBTedZ = true;}
      else if(SGMZYVHpVF == TbzxDsMYpL){bTSOgCiAna = true;}
      if(HsXOnJijtb == dJNNdDNwNM){wRrBewRPUT = true;}
      else if(dJNNdDNwNM == HsXOnJijtb){XZezljfGuH = true;}
      if(JptkoaHKMs == orBilBzaKA){xQChynVmJh = true;}
      else if(orBilBzaKA == JptkoaHKMs){uPyqyjSnDZ = true;}
      if(LiRBEqkwSk == FFBpcrVOpN){hlYLsHjnBy = true;}
      else if(FFBpcrVOpN == LiRBEqkwSk){cmFfBUckhx = true;}
      if(OhqVisbXVx == fsNOxAIZLu){MuMtGUAamt = true;}
      else if(fsNOxAIZLu == OhqVisbXVx){ANoHszxLni = true;}
      if(JYzigchOIc == zYfKVZFdmX){gxWtcbhHbZ = true;}
      if(lBMxzYaVKw == VgeUAXHXjk){egVwrJsgIX = true;}
      if(XmQJNbzXBu == gyFAfudmkk){MdOVGBDHbc = true;}
      while(zYfKVZFdmX == JYzigchOIc){zSVtBLUaPx = true;}
      while(VgeUAXHXjk == VgeUAXHXjk){juxNykUzyR = true;}
      while(gyFAfudmkk == gyFAfudmkk){GuYxHgZqxz = true;}
      if(rZOPAgZqUC == true){rZOPAgZqUC = false;}
      if(mrbSqyNrNZ == true){mrbSqyNrNZ = false;}
      if(rkoaOBTedZ == true){rkoaOBTedZ = false;}
      if(wRrBewRPUT == true){wRrBewRPUT = false;}
      if(xQChynVmJh == true){xQChynVmJh = false;}
      if(hlYLsHjnBy == true){hlYLsHjnBy = false;}
      if(MuMtGUAamt == true){MuMtGUAamt = false;}
      if(gxWtcbhHbZ == true){gxWtcbhHbZ = false;}
      if(egVwrJsgIX == true){egVwrJsgIX = false;}
      if(MdOVGBDHbc == true){MdOVGBDHbc = false;}
      if(nuAOAjOdhQ == true){nuAOAjOdhQ = false;}
      if(YcLaSfYQCw == true){YcLaSfYQCw = false;}
      if(bTSOgCiAna == true){bTSOgCiAna = false;}
      if(XZezljfGuH == true){XZezljfGuH = false;}
      if(uPyqyjSnDZ == true){uPyqyjSnDZ = false;}
      if(cmFfBUckhx == true){cmFfBUckhx = false;}
      if(ANoHszxLni == true){ANoHszxLni = false;}
      if(zSVtBLUaPx == true){zSVtBLUaPx = false;}
      if(juxNykUzyR == true){juxNykUzyR = false;}
      if(GuYxHgZqxz == true){GuYxHgZqxz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWXJXDVNSR
{ 
  void xWjrnEncir()
  { 
      bool duwSbFWFbm = false;
      bool qmeOdIHWqe = false;
      bool wpZRzzixlH = false;
      bool NFVqYtpZkZ = false;
      bool kAjFlxFbVI = false;
      bool BFfaWmUeTb = false;
      bool VYSTYlRnoi = false;
      bool RhlRsuFUeC = false;
      bool sHbdFHYtTl = false;
      bool ZLFIEMgPfz = false;
      bool eRmlpTTOgb = false;
      bool gAzRhOxoNR = false;
      bool NWTDJGbcNg = false;
      bool NoofWbToml = false;
      bool mKMrEYLnZo = false;
      bool PrBNlHxicj = false;
      bool qpAANrLTtG = false;
      bool tHBbdCJayj = false;
      bool umCXRUmasO = false;
      bool dkMDtwJMeM = false;
      string KMuRSkpZST;
      string urNICterWs;
      string GHcFixfrRU;
      string lXpjpapRIa;
      string PsUBDsNlea;
      string kfDMbDjohU;
      string EyHxgWBcRb;
      string DMiucMlaBo;
      string jtNpiGUdHm;
      string pAimWRkWUf;
      string rjTDWXwHiO;
      string RJmrjKkQOa;
      string CXUekCcuYL;
      string bOFVxAZJTL;
      string JMtsUgMqDL;
      string fTIscTPoST;
      string tAiWmCDRtj;
      string jaxDQpcbJD;
      string plrMeHGMrc;
      string kkqzQJcXFS;
      if(KMuRSkpZST == rjTDWXwHiO){duwSbFWFbm = true;}
      else if(rjTDWXwHiO == KMuRSkpZST){eRmlpTTOgb = true;}
      if(urNICterWs == RJmrjKkQOa){qmeOdIHWqe = true;}
      else if(RJmrjKkQOa == urNICterWs){gAzRhOxoNR = true;}
      if(GHcFixfrRU == CXUekCcuYL){wpZRzzixlH = true;}
      else if(CXUekCcuYL == GHcFixfrRU){NWTDJGbcNg = true;}
      if(lXpjpapRIa == bOFVxAZJTL){NFVqYtpZkZ = true;}
      else if(bOFVxAZJTL == lXpjpapRIa){NoofWbToml = true;}
      if(PsUBDsNlea == JMtsUgMqDL){kAjFlxFbVI = true;}
      else if(JMtsUgMqDL == PsUBDsNlea){mKMrEYLnZo = true;}
      if(kfDMbDjohU == fTIscTPoST){BFfaWmUeTb = true;}
      else if(fTIscTPoST == kfDMbDjohU){PrBNlHxicj = true;}
      if(EyHxgWBcRb == tAiWmCDRtj){VYSTYlRnoi = true;}
      else if(tAiWmCDRtj == EyHxgWBcRb){qpAANrLTtG = true;}
      if(DMiucMlaBo == jaxDQpcbJD){RhlRsuFUeC = true;}
      if(jtNpiGUdHm == plrMeHGMrc){sHbdFHYtTl = true;}
      if(pAimWRkWUf == kkqzQJcXFS){ZLFIEMgPfz = true;}
      while(jaxDQpcbJD == DMiucMlaBo){tHBbdCJayj = true;}
      while(plrMeHGMrc == plrMeHGMrc){umCXRUmasO = true;}
      while(kkqzQJcXFS == kkqzQJcXFS){dkMDtwJMeM = true;}
      if(duwSbFWFbm == true){duwSbFWFbm = false;}
      if(qmeOdIHWqe == true){qmeOdIHWqe = false;}
      if(wpZRzzixlH == true){wpZRzzixlH = false;}
      if(NFVqYtpZkZ == true){NFVqYtpZkZ = false;}
      if(kAjFlxFbVI == true){kAjFlxFbVI = false;}
      if(BFfaWmUeTb == true){BFfaWmUeTb = false;}
      if(VYSTYlRnoi == true){VYSTYlRnoi = false;}
      if(RhlRsuFUeC == true){RhlRsuFUeC = false;}
      if(sHbdFHYtTl == true){sHbdFHYtTl = false;}
      if(ZLFIEMgPfz == true){ZLFIEMgPfz = false;}
      if(eRmlpTTOgb == true){eRmlpTTOgb = false;}
      if(gAzRhOxoNR == true){gAzRhOxoNR = false;}
      if(NWTDJGbcNg == true){NWTDJGbcNg = false;}
      if(NoofWbToml == true){NoofWbToml = false;}
      if(mKMrEYLnZo == true){mKMrEYLnZo = false;}
      if(PrBNlHxicj == true){PrBNlHxicj = false;}
      if(qpAANrLTtG == true){qpAANrLTtG = false;}
      if(tHBbdCJayj == true){tHBbdCJayj = false;}
      if(umCXRUmasO == true){umCXRUmasO = false;}
      if(dkMDtwJMeM == true){dkMDtwJMeM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSQHWTEUGJ
{ 
  void SoMbohymDn()
  { 
      bool zLNeFFPwbM = false;
      bool OIyXApXitn = false;
      bool loyuVSAAxm = false;
      bool IamgpsVSou = false;
      bool mxUInjWFcB = false;
      bool uNVeRJNSJl = false;
      bool EPznEmUQhG = false;
      bool UEsyAoUoGk = false;
      bool wuWwrtFIPf = false;
      bool fDICqXyfEA = false;
      bool OFXWgpTWdb = false;
      bool nYLYoJrCwJ = false;
      bool hMBBaRuqHc = false;
      bool qojGVqWAPB = false;
      bool aidmqHqjMg = false;
      bool euiuSBDWuP = false;
      bool tcOBjznFCy = false;
      bool mrmtiyiNJT = false;
      bool ZLdaxwGomT = false;
      bool mAEzHxTcDr = false;
      string JLxLGiJpcc;
      string EbNFFHPoLL;
      string IUlEhrhDxd;
      string chaulagyfl;
      string PCsdTMAYTT;
      string nYpeuoYsdO;
      string BGsyAVASTd;
      string aQJYuGbIkV;
      string qIidpEqwAx;
      string CnUQkIIudx;
      string LhEpsWOQin;
      string MQHIWrXOIu;
      string eESVblwrnm;
      string xfdnJIErkS;
      string oZMLjkfMts;
      string ktlhRGPiOG;
      string aWcwqflTyO;
      string nedpGFrGkp;
      string FjytBDtwVD;
      string sUddrSwQTE;
      if(JLxLGiJpcc == LhEpsWOQin){zLNeFFPwbM = true;}
      else if(LhEpsWOQin == JLxLGiJpcc){OFXWgpTWdb = true;}
      if(EbNFFHPoLL == MQHIWrXOIu){OIyXApXitn = true;}
      else if(MQHIWrXOIu == EbNFFHPoLL){nYLYoJrCwJ = true;}
      if(IUlEhrhDxd == eESVblwrnm){loyuVSAAxm = true;}
      else if(eESVblwrnm == IUlEhrhDxd){hMBBaRuqHc = true;}
      if(chaulagyfl == xfdnJIErkS){IamgpsVSou = true;}
      else if(xfdnJIErkS == chaulagyfl){qojGVqWAPB = true;}
      if(PCsdTMAYTT == oZMLjkfMts){mxUInjWFcB = true;}
      else if(oZMLjkfMts == PCsdTMAYTT){aidmqHqjMg = true;}
      if(nYpeuoYsdO == ktlhRGPiOG){uNVeRJNSJl = true;}
      else if(ktlhRGPiOG == nYpeuoYsdO){euiuSBDWuP = true;}
      if(BGsyAVASTd == aWcwqflTyO){EPznEmUQhG = true;}
      else if(aWcwqflTyO == BGsyAVASTd){tcOBjznFCy = true;}
      if(aQJYuGbIkV == nedpGFrGkp){UEsyAoUoGk = true;}
      if(qIidpEqwAx == FjytBDtwVD){wuWwrtFIPf = true;}
      if(CnUQkIIudx == sUddrSwQTE){fDICqXyfEA = true;}
      while(nedpGFrGkp == aQJYuGbIkV){mrmtiyiNJT = true;}
      while(FjytBDtwVD == FjytBDtwVD){ZLdaxwGomT = true;}
      while(sUddrSwQTE == sUddrSwQTE){mAEzHxTcDr = true;}
      if(zLNeFFPwbM == true){zLNeFFPwbM = false;}
      if(OIyXApXitn == true){OIyXApXitn = false;}
      if(loyuVSAAxm == true){loyuVSAAxm = false;}
      if(IamgpsVSou == true){IamgpsVSou = false;}
      if(mxUInjWFcB == true){mxUInjWFcB = false;}
      if(uNVeRJNSJl == true){uNVeRJNSJl = false;}
      if(EPznEmUQhG == true){EPznEmUQhG = false;}
      if(UEsyAoUoGk == true){UEsyAoUoGk = false;}
      if(wuWwrtFIPf == true){wuWwrtFIPf = false;}
      if(fDICqXyfEA == true){fDICqXyfEA = false;}
      if(OFXWgpTWdb == true){OFXWgpTWdb = false;}
      if(nYLYoJrCwJ == true){nYLYoJrCwJ = false;}
      if(hMBBaRuqHc == true){hMBBaRuqHc = false;}
      if(qojGVqWAPB == true){qojGVqWAPB = false;}
      if(aidmqHqjMg == true){aidmqHqjMg = false;}
      if(euiuSBDWuP == true){euiuSBDWuP = false;}
      if(tcOBjznFCy == true){tcOBjznFCy = false;}
      if(mrmtiyiNJT == true){mrmtiyiNJT = false;}
      if(ZLdaxwGomT == true){ZLdaxwGomT = false;}
      if(mAEzHxTcDr == true){mAEzHxTcDr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTQLSZAWZZ
{ 
  void DnJZnYQXQV()
  { 
      bool hsDAxzVnPM = false;
      bool UIsZZGkSTy = false;
      bool xrrjJAKHeu = false;
      bool ddjuIcPPrp = false;
      bool OjgaRdTiWW = false;
      bool WXPxioBTpx = false;
      bool oOIThpYyRw = false;
      bool pUZciNLQSf = false;
      bool fajHYGOlLS = false;
      bool awZuBzaMsa = false;
      bool EVRafBxmOU = false;
      bool ckAJRNeBua = false;
      bool bllyVtuebi = false;
      bool lzXraKJJbX = false;
      bool JaXpopwPdn = false;
      bool UZRRySjSEl = false;
      bool FSLeidMIiG = false;
      bool DUZXRAOuIe = false;
      bool yfBmNMhGsI = false;
      bool apEoRqPrHK = false;
      string KChuOlYpEA;
      string OipsPduExm;
      string sjEHkNGZFN;
      string ShJETZDeVm;
      string NICLiTkYUT;
      string lwVseZxaKA;
      string ezjphfZkYp;
      string ZPhKYjhsXQ;
      string bhElbVLPZt;
      string bcUVHOXLdC;
      string tAzesVNLUt;
      string qECsYwtxOL;
      string UJLdNxuMCK;
      string LVPVWbiZsF;
      string IzueCXZaxL;
      string TaxShjoUQw;
      string aAJKiVofWw;
      string NTEJCUOfbp;
      string WTPppkXwnl;
      string mNJxdHpjwg;
      if(KChuOlYpEA == tAzesVNLUt){hsDAxzVnPM = true;}
      else if(tAzesVNLUt == KChuOlYpEA){EVRafBxmOU = true;}
      if(OipsPduExm == qECsYwtxOL){UIsZZGkSTy = true;}
      else if(qECsYwtxOL == OipsPduExm){ckAJRNeBua = true;}
      if(sjEHkNGZFN == UJLdNxuMCK){xrrjJAKHeu = true;}
      else if(UJLdNxuMCK == sjEHkNGZFN){bllyVtuebi = true;}
      if(ShJETZDeVm == LVPVWbiZsF){ddjuIcPPrp = true;}
      else if(LVPVWbiZsF == ShJETZDeVm){lzXraKJJbX = true;}
      if(NICLiTkYUT == IzueCXZaxL){OjgaRdTiWW = true;}
      else if(IzueCXZaxL == NICLiTkYUT){JaXpopwPdn = true;}
      if(lwVseZxaKA == TaxShjoUQw){WXPxioBTpx = true;}
      else if(TaxShjoUQw == lwVseZxaKA){UZRRySjSEl = true;}
      if(ezjphfZkYp == aAJKiVofWw){oOIThpYyRw = true;}
      else if(aAJKiVofWw == ezjphfZkYp){FSLeidMIiG = true;}
      if(ZPhKYjhsXQ == NTEJCUOfbp){pUZciNLQSf = true;}
      if(bhElbVLPZt == WTPppkXwnl){fajHYGOlLS = true;}
      if(bcUVHOXLdC == mNJxdHpjwg){awZuBzaMsa = true;}
      while(NTEJCUOfbp == ZPhKYjhsXQ){DUZXRAOuIe = true;}
      while(WTPppkXwnl == WTPppkXwnl){yfBmNMhGsI = true;}
      while(mNJxdHpjwg == mNJxdHpjwg){apEoRqPrHK = true;}
      if(hsDAxzVnPM == true){hsDAxzVnPM = false;}
      if(UIsZZGkSTy == true){UIsZZGkSTy = false;}
      if(xrrjJAKHeu == true){xrrjJAKHeu = false;}
      if(ddjuIcPPrp == true){ddjuIcPPrp = false;}
      if(OjgaRdTiWW == true){OjgaRdTiWW = false;}
      if(WXPxioBTpx == true){WXPxioBTpx = false;}
      if(oOIThpYyRw == true){oOIThpYyRw = false;}
      if(pUZciNLQSf == true){pUZciNLQSf = false;}
      if(fajHYGOlLS == true){fajHYGOlLS = false;}
      if(awZuBzaMsa == true){awZuBzaMsa = false;}
      if(EVRafBxmOU == true){EVRafBxmOU = false;}
      if(ckAJRNeBua == true){ckAJRNeBua = false;}
      if(bllyVtuebi == true){bllyVtuebi = false;}
      if(lzXraKJJbX == true){lzXraKJJbX = false;}
      if(JaXpopwPdn == true){JaXpopwPdn = false;}
      if(UZRRySjSEl == true){UZRRySjSEl = false;}
      if(FSLeidMIiG == true){FSLeidMIiG = false;}
      if(DUZXRAOuIe == true){DUZXRAOuIe = false;}
      if(yfBmNMhGsI == true){yfBmNMhGsI = false;}
      if(apEoRqPrHK == true){apEoRqPrHK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHSLYMPQZK
{ 
  void XVdrrKgxCQ()
  { 
      bool pqfIbWIRUq = false;
      bool gPqyWjHcCJ = false;
      bool fVqPEJxmCU = false;
      bool JCdYbzVRwZ = false;
      bool hzhnVEdEIl = false;
      bool AZMiCUAPES = false;
      bool YVOAhdlRWW = false;
      bool OpfcafmCsz = false;
      bool erdPUipuWH = false;
      bool zGMdAMkhFr = false;
      bool SMhlXJtiHV = false;
      bool gxVEmfqyfy = false;
      bool npuPXHdBcN = false;
      bool uFwBgSKrrL = false;
      bool oGmAaBjIqT = false;
      bool VlCHDbQSNP = false;
      bool frGtaaATXT = false;
      bool VyGUIhDuoV = false;
      bool XUKIqJDoyE = false;
      bool CrebfxzrZz = false;
      string VWnWUTdbii;
      string KURwEEqOxs;
      string UifcUjOoDF;
      string kHJoXgfVwK;
      string gMCNXocJVr;
      string IGUdblqLBk;
      string EnXdxDLbYX;
      string YVRmLHgREf;
      string GFSLwelfNk;
      string oUULGrnYQU;
      string dAkySmnhRT;
      string FZGUdyUMhS;
      string QeOmhEBGfT;
      string TIAjBFTUsI;
      string pENsfPNzgH;
      string WbpxEykyQN;
      string lhByAxYWTY;
      string eASYcMRVHR;
      string qBZYwqRDfD;
      string TUDfWICOrh;
      if(VWnWUTdbii == dAkySmnhRT){pqfIbWIRUq = true;}
      else if(dAkySmnhRT == VWnWUTdbii){SMhlXJtiHV = true;}
      if(KURwEEqOxs == FZGUdyUMhS){gPqyWjHcCJ = true;}
      else if(FZGUdyUMhS == KURwEEqOxs){gxVEmfqyfy = true;}
      if(UifcUjOoDF == QeOmhEBGfT){fVqPEJxmCU = true;}
      else if(QeOmhEBGfT == UifcUjOoDF){npuPXHdBcN = true;}
      if(kHJoXgfVwK == TIAjBFTUsI){JCdYbzVRwZ = true;}
      else if(TIAjBFTUsI == kHJoXgfVwK){uFwBgSKrrL = true;}
      if(gMCNXocJVr == pENsfPNzgH){hzhnVEdEIl = true;}
      else if(pENsfPNzgH == gMCNXocJVr){oGmAaBjIqT = true;}
      if(IGUdblqLBk == WbpxEykyQN){AZMiCUAPES = true;}
      else if(WbpxEykyQN == IGUdblqLBk){VlCHDbQSNP = true;}
      if(EnXdxDLbYX == lhByAxYWTY){YVOAhdlRWW = true;}
      else if(lhByAxYWTY == EnXdxDLbYX){frGtaaATXT = true;}
      if(YVRmLHgREf == eASYcMRVHR){OpfcafmCsz = true;}
      if(GFSLwelfNk == qBZYwqRDfD){erdPUipuWH = true;}
      if(oUULGrnYQU == TUDfWICOrh){zGMdAMkhFr = true;}
      while(eASYcMRVHR == YVRmLHgREf){VyGUIhDuoV = true;}
      while(qBZYwqRDfD == qBZYwqRDfD){XUKIqJDoyE = true;}
      while(TUDfWICOrh == TUDfWICOrh){CrebfxzrZz = true;}
      if(pqfIbWIRUq == true){pqfIbWIRUq = false;}
      if(gPqyWjHcCJ == true){gPqyWjHcCJ = false;}
      if(fVqPEJxmCU == true){fVqPEJxmCU = false;}
      if(JCdYbzVRwZ == true){JCdYbzVRwZ = false;}
      if(hzhnVEdEIl == true){hzhnVEdEIl = false;}
      if(AZMiCUAPES == true){AZMiCUAPES = false;}
      if(YVOAhdlRWW == true){YVOAhdlRWW = false;}
      if(OpfcafmCsz == true){OpfcafmCsz = false;}
      if(erdPUipuWH == true){erdPUipuWH = false;}
      if(zGMdAMkhFr == true){zGMdAMkhFr = false;}
      if(SMhlXJtiHV == true){SMhlXJtiHV = false;}
      if(gxVEmfqyfy == true){gxVEmfqyfy = false;}
      if(npuPXHdBcN == true){npuPXHdBcN = false;}
      if(uFwBgSKrrL == true){uFwBgSKrrL = false;}
      if(oGmAaBjIqT == true){oGmAaBjIqT = false;}
      if(VlCHDbQSNP == true){VlCHDbQSNP = false;}
      if(frGtaaATXT == true){frGtaaATXT = false;}
      if(VyGUIhDuoV == true){VyGUIhDuoV = false;}
      if(XUKIqJDoyE == true){XUKIqJDoyE = false;}
      if(CrebfxzrZz == true){CrebfxzrZz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIMFZQIDJE
{ 
  void YucVzdXtZk()
  { 
      bool KMGFNiGAbn = false;
      bool GMBnhINgMm = false;
      bool KPWdbGQbhP = false;
      bool IFaWScIJMS = false;
      bool FkzCMRUurQ = false;
      bool OjbkHtpccG = false;
      bool SdSLeBldUE = false;
      bool zDUtgZQTRK = false;
      bool lUiRBYcoPY = false;
      bool mffFzbSmWK = false;
      bool fqZmQLPhEh = false;
      bool cVLSUxuBKG = false;
      bool YwOwRSWOuF = false;
      bool GdxGdtuuAp = false;
      bool ItkgwRUNkB = false;
      bool fQcQljbdVy = false;
      bool nAmzayYEoZ = false;
      bool CzBUxdKgAz = false;
      bool yJcsYoBgTt = false;
      bool SQYCBHHlGx = false;
      string udDJyTyTKI;
      string KYHKxcxVfu;
      string cChVWZSEfT;
      string BQWrygXIih;
      string byAXFCzIKs;
      string fqUSzruglX;
      string BsnpGsCPLP;
      string FolxTeCKPU;
      string ZKtlmJuDrF;
      string lpVKghJJQL;
      string AiwtmqEWzU;
      string pkQRxpzBCx;
      string yyWFdPTbQk;
      string UstEUqNzyw;
      string EXDXPBYDMp;
      string iIGTNBLqQX;
      string XcGOzxqMxG;
      string czCGrZtzpc;
      string pPPZBMlapS;
      string eViaYbQoXS;
      if(udDJyTyTKI == AiwtmqEWzU){KMGFNiGAbn = true;}
      else if(AiwtmqEWzU == udDJyTyTKI){fqZmQLPhEh = true;}
      if(KYHKxcxVfu == pkQRxpzBCx){GMBnhINgMm = true;}
      else if(pkQRxpzBCx == KYHKxcxVfu){cVLSUxuBKG = true;}
      if(cChVWZSEfT == yyWFdPTbQk){KPWdbGQbhP = true;}
      else if(yyWFdPTbQk == cChVWZSEfT){YwOwRSWOuF = true;}
      if(BQWrygXIih == UstEUqNzyw){IFaWScIJMS = true;}
      else if(UstEUqNzyw == BQWrygXIih){GdxGdtuuAp = true;}
      if(byAXFCzIKs == EXDXPBYDMp){FkzCMRUurQ = true;}
      else if(EXDXPBYDMp == byAXFCzIKs){ItkgwRUNkB = true;}
      if(fqUSzruglX == iIGTNBLqQX){OjbkHtpccG = true;}
      else if(iIGTNBLqQX == fqUSzruglX){fQcQljbdVy = true;}
      if(BsnpGsCPLP == XcGOzxqMxG){SdSLeBldUE = true;}
      else if(XcGOzxqMxG == BsnpGsCPLP){nAmzayYEoZ = true;}
      if(FolxTeCKPU == czCGrZtzpc){zDUtgZQTRK = true;}
      if(ZKtlmJuDrF == pPPZBMlapS){lUiRBYcoPY = true;}
      if(lpVKghJJQL == eViaYbQoXS){mffFzbSmWK = true;}
      while(czCGrZtzpc == FolxTeCKPU){CzBUxdKgAz = true;}
      while(pPPZBMlapS == pPPZBMlapS){yJcsYoBgTt = true;}
      while(eViaYbQoXS == eViaYbQoXS){SQYCBHHlGx = true;}
      if(KMGFNiGAbn == true){KMGFNiGAbn = false;}
      if(GMBnhINgMm == true){GMBnhINgMm = false;}
      if(KPWdbGQbhP == true){KPWdbGQbhP = false;}
      if(IFaWScIJMS == true){IFaWScIJMS = false;}
      if(FkzCMRUurQ == true){FkzCMRUurQ = false;}
      if(OjbkHtpccG == true){OjbkHtpccG = false;}
      if(SdSLeBldUE == true){SdSLeBldUE = false;}
      if(zDUtgZQTRK == true){zDUtgZQTRK = false;}
      if(lUiRBYcoPY == true){lUiRBYcoPY = false;}
      if(mffFzbSmWK == true){mffFzbSmWK = false;}
      if(fqZmQLPhEh == true){fqZmQLPhEh = false;}
      if(cVLSUxuBKG == true){cVLSUxuBKG = false;}
      if(YwOwRSWOuF == true){YwOwRSWOuF = false;}
      if(GdxGdtuuAp == true){GdxGdtuuAp = false;}
      if(ItkgwRUNkB == true){ItkgwRUNkB = false;}
      if(fQcQljbdVy == true){fQcQljbdVy = false;}
      if(nAmzayYEoZ == true){nAmzayYEoZ = false;}
      if(CzBUxdKgAz == true){CzBUxdKgAz = false;}
      if(yJcsYoBgTt == true){yJcsYoBgTt = false;}
      if(SQYCBHHlGx == true){SQYCBHHlGx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PKHZPSTNFX
{ 
  void qsVQnwqFqW()
  { 
      bool tNqKHcxZpp = false;
      bool MxhDiVFZIs = false;
      bool BIAKfmWIfo = false;
      bool VBOqatGpSe = false;
      bool jKbLjpdtMM = false;
      bool wcwZTlNfeU = false;
      bool GnsAULiqcn = false;
      bool POGcJpfnap = false;
      bool JcwSssEnWn = false;
      bool gZLyYuRbqX = false;
      bool GmRXxgVSPc = false;
      bool GYEoKcqZGb = false;
      bool GtTnHoDIEO = false;
      bool YDxCiWLXVM = false;
      bool XlYtgHVVmw = false;
      bool DqUOQMScQI = false;
      bool dMNBEDbBGn = false;
      bool QTEtEUVZHz = false;
      bool TgVIKhhhlV = false;
      bool DiHNiKXWod = false;
      string wDbOkkTfcU;
      string XoZkiQXddS;
      string WKAEfUNogx;
      string cMQrCxHFhj;
      string UsiWzTquBa;
      string gicVnkCXiQ;
      string WeyfrKXhik;
      string JSwtxdbdEL;
      string cRmFPsjuEQ;
      string tiWRMptDen;
      string wJMQROlhYJ;
      string JYSXmFqrPy;
      string ZccSqZwehG;
      string iXyQPTFWnB;
      string HCWtGUQydH;
      string yCnfNSfsYr;
      string SGARakZCHS;
      string zUEOpXGhLV;
      string IxBaIgjRCw;
      string mLxuhBCFTU;
      if(wDbOkkTfcU == wJMQROlhYJ){tNqKHcxZpp = true;}
      else if(wJMQROlhYJ == wDbOkkTfcU){GmRXxgVSPc = true;}
      if(XoZkiQXddS == JYSXmFqrPy){MxhDiVFZIs = true;}
      else if(JYSXmFqrPy == XoZkiQXddS){GYEoKcqZGb = true;}
      if(WKAEfUNogx == ZccSqZwehG){BIAKfmWIfo = true;}
      else if(ZccSqZwehG == WKAEfUNogx){GtTnHoDIEO = true;}
      if(cMQrCxHFhj == iXyQPTFWnB){VBOqatGpSe = true;}
      else if(iXyQPTFWnB == cMQrCxHFhj){YDxCiWLXVM = true;}
      if(UsiWzTquBa == HCWtGUQydH){jKbLjpdtMM = true;}
      else if(HCWtGUQydH == UsiWzTquBa){XlYtgHVVmw = true;}
      if(gicVnkCXiQ == yCnfNSfsYr){wcwZTlNfeU = true;}
      else if(yCnfNSfsYr == gicVnkCXiQ){DqUOQMScQI = true;}
      if(WeyfrKXhik == SGARakZCHS){GnsAULiqcn = true;}
      else if(SGARakZCHS == WeyfrKXhik){dMNBEDbBGn = true;}
      if(JSwtxdbdEL == zUEOpXGhLV){POGcJpfnap = true;}
      if(cRmFPsjuEQ == IxBaIgjRCw){JcwSssEnWn = true;}
      if(tiWRMptDen == mLxuhBCFTU){gZLyYuRbqX = true;}
      while(zUEOpXGhLV == JSwtxdbdEL){QTEtEUVZHz = true;}
      while(IxBaIgjRCw == IxBaIgjRCw){TgVIKhhhlV = true;}
      while(mLxuhBCFTU == mLxuhBCFTU){DiHNiKXWod = true;}
      if(tNqKHcxZpp == true){tNqKHcxZpp = false;}
      if(MxhDiVFZIs == true){MxhDiVFZIs = false;}
      if(BIAKfmWIfo == true){BIAKfmWIfo = false;}
      if(VBOqatGpSe == true){VBOqatGpSe = false;}
      if(jKbLjpdtMM == true){jKbLjpdtMM = false;}
      if(wcwZTlNfeU == true){wcwZTlNfeU = false;}
      if(GnsAULiqcn == true){GnsAULiqcn = false;}
      if(POGcJpfnap == true){POGcJpfnap = false;}
      if(JcwSssEnWn == true){JcwSssEnWn = false;}
      if(gZLyYuRbqX == true){gZLyYuRbqX = false;}
      if(GmRXxgVSPc == true){GmRXxgVSPc = false;}
      if(GYEoKcqZGb == true){GYEoKcqZGb = false;}
      if(GtTnHoDIEO == true){GtTnHoDIEO = false;}
      if(YDxCiWLXVM == true){YDxCiWLXVM = false;}
      if(XlYtgHVVmw == true){XlYtgHVVmw = false;}
      if(DqUOQMScQI == true){DqUOQMScQI = false;}
      if(dMNBEDbBGn == true){dMNBEDbBGn = false;}
      if(QTEtEUVZHz == true){QTEtEUVZHz = false;}
      if(TgVIKhhhlV == true){TgVIKhhhlV = false;}
      if(DiHNiKXWod == true){DiHNiKXWod = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRUFKACCEB
{ 
  void syNheBfWoT()
  { 
      bool MwopqgGNnx = false;
      bool HgDSaiHzVY = false;
      bool VKxanqzZoG = false;
      bool wCxguIJjFs = false;
      bool wPeAryXYLw = false;
      bool eecsoCzNBz = false;
      bool hfXhBEiWXS = false;
      bool ZXtbbGewip = false;
      bool TZOsbQZEqr = false;
      bool JuiFLPrxym = false;
      bool OABsWHkAQi = false;
      bool WCeKfHReGk = false;
      bool eeeeIdooQM = false;
      bool NhywbSYUVT = false;
      bool fYmIVGQXYD = false;
      bool xNqNIjUWjr = false;
      bool SujDUoDiiM = false;
      bool iwIlEFqVIB = false;
      bool NQPMOAqjmq = false;
      bool yCkdBjoing = false;
      string kZCBIzswOr;
      string EtElbZMRLN;
      string nsuqChpqYT;
      string qeKGNDUydH;
      string iUNwxnCVyf;
      string JFEXQqeLyZ;
      string JCWtAZiyYX;
      string FNnEeSfysO;
      string eTrrKlZmpV;
      string YJzEygxSwX;
      string FExZawRAsx;
      string LgRjtoJdjN;
      string zuICzwNjFx;
      string VMCVJaWSRN;
      string UYtsKqqPJJ;
      string XSihXJwuae;
      string hhuuazeuaT;
      string SqMVsZBPqH;
      string EyZwZCcTyz;
      string earlfmdyRK;
      if(kZCBIzswOr == FExZawRAsx){MwopqgGNnx = true;}
      else if(FExZawRAsx == kZCBIzswOr){OABsWHkAQi = true;}
      if(EtElbZMRLN == LgRjtoJdjN){HgDSaiHzVY = true;}
      else if(LgRjtoJdjN == EtElbZMRLN){WCeKfHReGk = true;}
      if(nsuqChpqYT == zuICzwNjFx){VKxanqzZoG = true;}
      else if(zuICzwNjFx == nsuqChpqYT){eeeeIdooQM = true;}
      if(qeKGNDUydH == VMCVJaWSRN){wCxguIJjFs = true;}
      else if(VMCVJaWSRN == qeKGNDUydH){NhywbSYUVT = true;}
      if(iUNwxnCVyf == UYtsKqqPJJ){wPeAryXYLw = true;}
      else if(UYtsKqqPJJ == iUNwxnCVyf){fYmIVGQXYD = true;}
      if(JFEXQqeLyZ == XSihXJwuae){eecsoCzNBz = true;}
      else if(XSihXJwuae == JFEXQqeLyZ){xNqNIjUWjr = true;}
      if(JCWtAZiyYX == hhuuazeuaT){hfXhBEiWXS = true;}
      else if(hhuuazeuaT == JCWtAZiyYX){SujDUoDiiM = true;}
      if(FNnEeSfysO == SqMVsZBPqH){ZXtbbGewip = true;}
      if(eTrrKlZmpV == EyZwZCcTyz){TZOsbQZEqr = true;}
      if(YJzEygxSwX == earlfmdyRK){JuiFLPrxym = true;}
      while(SqMVsZBPqH == FNnEeSfysO){iwIlEFqVIB = true;}
      while(EyZwZCcTyz == EyZwZCcTyz){NQPMOAqjmq = true;}
      while(earlfmdyRK == earlfmdyRK){yCkdBjoing = true;}
      if(MwopqgGNnx == true){MwopqgGNnx = false;}
      if(HgDSaiHzVY == true){HgDSaiHzVY = false;}
      if(VKxanqzZoG == true){VKxanqzZoG = false;}
      if(wCxguIJjFs == true){wCxguIJjFs = false;}
      if(wPeAryXYLw == true){wPeAryXYLw = false;}
      if(eecsoCzNBz == true){eecsoCzNBz = false;}
      if(hfXhBEiWXS == true){hfXhBEiWXS = false;}
      if(ZXtbbGewip == true){ZXtbbGewip = false;}
      if(TZOsbQZEqr == true){TZOsbQZEqr = false;}
      if(JuiFLPrxym == true){JuiFLPrxym = false;}
      if(OABsWHkAQi == true){OABsWHkAQi = false;}
      if(WCeKfHReGk == true){WCeKfHReGk = false;}
      if(eeeeIdooQM == true){eeeeIdooQM = false;}
      if(NhywbSYUVT == true){NhywbSYUVT = false;}
      if(fYmIVGQXYD == true){fYmIVGQXYD = false;}
      if(xNqNIjUWjr == true){xNqNIjUWjr = false;}
      if(SujDUoDiiM == true){SujDUoDiiM = false;}
      if(iwIlEFqVIB == true){iwIlEFqVIB = false;}
      if(NQPMOAqjmq == true){NQPMOAqjmq = false;}
      if(yCkdBjoing == true){yCkdBjoing = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDCTWEFFPO
{ 
  void aRgDNMhGTe()
  { 
      bool tbirdlRniQ = false;
      bool WVZpPHxrVl = false;
      bool uieMuMmofz = false;
      bool imLsINVSMW = false;
      bool tIHNReKTsA = false;
      bool SENaRLxWxR = false;
      bool zbIigiJfgC = false;
      bool leeyrlaQtQ = false;
      bool BSuegeZkbx = false;
      bool QzVtXRAXfi = false;
      bool VemqOnYOif = false;
      bool jfbfPffcCC = false;
      bool IXEillIkZZ = false;
      bool lCkLuWfEQr = false;
      bool FLBwNjWoer = false;
      bool kWUcZxZDFc = false;
      bool ennItguQkr = false;
      bool zbMJxxVIVB = false;
      bool OSFhoOgHkx = false;
      bool wcznNQWsBf = false;
      string VmOFzJEpSA;
      string fKsrgwTfQe;
      string ymspLfmldi;
      string ammVHbwLzK;
      string BpXODAEdTg;
      string KpGBihsYsT;
      string WRLjZsWXkE;
      string zHgFcHOdlK;
      string bJRxYjfllY;
      string hXRfnjenoK;
      string dfrOhCJAXa;
      string TOlhqMAOKp;
      string MjkMVboARs;
      string caobguQCPV;
      string ZfNLFTljna;
      string iQcyxsufrF;
      string NJieyrZJAw;
      string wxynPfWZGC;
      string pFLpJLxpen;
      string AjJJIQxiNM;
      if(VmOFzJEpSA == dfrOhCJAXa){tbirdlRniQ = true;}
      else if(dfrOhCJAXa == VmOFzJEpSA){VemqOnYOif = true;}
      if(fKsrgwTfQe == TOlhqMAOKp){WVZpPHxrVl = true;}
      else if(TOlhqMAOKp == fKsrgwTfQe){jfbfPffcCC = true;}
      if(ymspLfmldi == MjkMVboARs){uieMuMmofz = true;}
      else if(MjkMVboARs == ymspLfmldi){IXEillIkZZ = true;}
      if(ammVHbwLzK == caobguQCPV){imLsINVSMW = true;}
      else if(caobguQCPV == ammVHbwLzK){lCkLuWfEQr = true;}
      if(BpXODAEdTg == ZfNLFTljna){tIHNReKTsA = true;}
      else if(ZfNLFTljna == BpXODAEdTg){FLBwNjWoer = true;}
      if(KpGBihsYsT == iQcyxsufrF){SENaRLxWxR = true;}
      else if(iQcyxsufrF == KpGBihsYsT){kWUcZxZDFc = true;}
      if(WRLjZsWXkE == NJieyrZJAw){zbIigiJfgC = true;}
      else if(NJieyrZJAw == WRLjZsWXkE){ennItguQkr = true;}
      if(zHgFcHOdlK == wxynPfWZGC){leeyrlaQtQ = true;}
      if(bJRxYjfllY == pFLpJLxpen){BSuegeZkbx = true;}
      if(hXRfnjenoK == AjJJIQxiNM){QzVtXRAXfi = true;}
      while(wxynPfWZGC == zHgFcHOdlK){zbMJxxVIVB = true;}
      while(pFLpJLxpen == pFLpJLxpen){OSFhoOgHkx = true;}
      while(AjJJIQxiNM == AjJJIQxiNM){wcznNQWsBf = true;}
      if(tbirdlRniQ == true){tbirdlRniQ = false;}
      if(WVZpPHxrVl == true){WVZpPHxrVl = false;}
      if(uieMuMmofz == true){uieMuMmofz = false;}
      if(imLsINVSMW == true){imLsINVSMW = false;}
      if(tIHNReKTsA == true){tIHNReKTsA = false;}
      if(SENaRLxWxR == true){SENaRLxWxR = false;}
      if(zbIigiJfgC == true){zbIigiJfgC = false;}
      if(leeyrlaQtQ == true){leeyrlaQtQ = false;}
      if(BSuegeZkbx == true){BSuegeZkbx = false;}
      if(QzVtXRAXfi == true){QzVtXRAXfi = false;}
      if(VemqOnYOif == true){VemqOnYOif = false;}
      if(jfbfPffcCC == true){jfbfPffcCC = false;}
      if(IXEillIkZZ == true){IXEillIkZZ = false;}
      if(lCkLuWfEQr == true){lCkLuWfEQr = false;}
      if(FLBwNjWoer == true){FLBwNjWoer = false;}
      if(kWUcZxZDFc == true){kWUcZxZDFc = false;}
      if(ennItguQkr == true){ennItguQkr = false;}
      if(zbMJxxVIVB == true){zbMJxxVIVB = false;}
      if(OSFhoOgHkx == true){OSFhoOgHkx = false;}
      if(wcznNQWsBf == true){wcznNQWsBf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JOZKDNJMZA
{ 
  void JebSMIIXPL()
  { 
      bool eZOQJPbXcQ = false;
      bool cngNAkyciB = false;
      bool dLmsLDEUqj = false;
      bool SHZEgJMtlJ = false;
      bool wcNxTTjDaD = false;
      bool RZOYVSmUFF = false;
      bool KHgsyUObgq = false;
      bool YEpZFBypZq = false;
      bool TAtmSssAhN = false;
      bool VqnfyouUzy = false;
      bool FHWieNinTU = false;
      bool UxuNlKMsZE = false;
      bool bNtTUgPKbQ = false;
      bool FcqalMdKIF = false;
      bool KEfMsYwatm = false;
      bool bCttWqMCOx = false;
      bool xYMDOqGTaY = false;
      bool gCjUtWggZw = false;
      bool koPnnDixEu = false;
      bool AawLHkrcyC = false;
      string mfpDMpCLcm;
      string gnHuCLcBWi;
      string fJiAHHucty;
      string gFCetCUVFu;
      string YzRJNgTXSl;
      string BBbcFcwpuE;
      string tYQeFblbBz;
      string pHwbKgrYmZ;
      string nXKHwecYZQ;
      string FeZAAzhmEk;
      string uqVSwtFASY;
      string kXDUPVNIhZ;
      string yMCjsLguaK;
      string yFUBexBqLC;
      string ZcGBfhbEjd;
      string lYEdmiokZj;
      string NJZIZeCBpS;
      string TVxfAVFAEL;
      string jbLwYYBqOw;
      string HQRboPCyaA;
      if(mfpDMpCLcm == uqVSwtFASY){eZOQJPbXcQ = true;}
      else if(uqVSwtFASY == mfpDMpCLcm){FHWieNinTU = true;}
      if(gnHuCLcBWi == kXDUPVNIhZ){cngNAkyciB = true;}
      else if(kXDUPVNIhZ == gnHuCLcBWi){UxuNlKMsZE = true;}
      if(fJiAHHucty == yMCjsLguaK){dLmsLDEUqj = true;}
      else if(yMCjsLguaK == fJiAHHucty){bNtTUgPKbQ = true;}
      if(gFCetCUVFu == yFUBexBqLC){SHZEgJMtlJ = true;}
      else if(yFUBexBqLC == gFCetCUVFu){FcqalMdKIF = true;}
      if(YzRJNgTXSl == ZcGBfhbEjd){wcNxTTjDaD = true;}
      else if(ZcGBfhbEjd == YzRJNgTXSl){KEfMsYwatm = true;}
      if(BBbcFcwpuE == lYEdmiokZj){RZOYVSmUFF = true;}
      else if(lYEdmiokZj == BBbcFcwpuE){bCttWqMCOx = true;}
      if(tYQeFblbBz == NJZIZeCBpS){KHgsyUObgq = true;}
      else if(NJZIZeCBpS == tYQeFblbBz){xYMDOqGTaY = true;}
      if(pHwbKgrYmZ == TVxfAVFAEL){YEpZFBypZq = true;}
      if(nXKHwecYZQ == jbLwYYBqOw){TAtmSssAhN = true;}
      if(FeZAAzhmEk == HQRboPCyaA){VqnfyouUzy = true;}
      while(TVxfAVFAEL == pHwbKgrYmZ){gCjUtWggZw = true;}
      while(jbLwYYBqOw == jbLwYYBqOw){koPnnDixEu = true;}
      while(HQRboPCyaA == HQRboPCyaA){AawLHkrcyC = true;}
      if(eZOQJPbXcQ == true){eZOQJPbXcQ = false;}
      if(cngNAkyciB == true){cngNAkyciB = false;}
      if(dLmsLDEUqj == true){dLmsLDEUqj = false;}
      if(SHZEgJMtlJ == true){SHZEgJMtlJ = false;}
      if(wcNxTTjDaD == true){wcNxTTjDaD = false;}
      if(RZOYVSmUFF == true){RZOYVSmUFF = false;}
      if(KHgsyUObgq == true){KHgsyUObgq = false;}
      if(YEpZFBypZq == true){YEpZFBypZq = false;}
      if(TAtmSssAhN == true){TAtmSssAhN = false;}
      if(VqnfyouUzy == true){VqnfyouUzy = false;}
      if(FHWieNinTU == true){FHWieNinTU = false;}
      if(UxuNlKMsZE == true){UxuNlKMsZE = false;}
      if(bNtTUgPKbQ == true){bNtTUgPKbQ = false;}
      if(FcqalMdKIF == true){FcqalMdKIF = false;}
      if(KEfMsYwatm == true){KEfMsYwatm = false;}
      if(bCttWqMCOx == true){bCttWqMCOx = false;}
      if(xYMDOqGTaY == true){xYMDOqGTaY = false;}
      if(gCjUtWggZw == true){gCjUtWggZw = false;}
      if(koPnnDixEu == true){koPnnDixEu = false;}
      if(AawLHkrcyC == true){AawLHkrcyC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEYBETJCYN
{ 
  void wubnDlQJaB()
  { 
      bool YDPzoNaTiR = false;
      bool mGVOSeOutf = false;
      bool SReOIwnxCW = false;
      bool IdWYhDXzOU = false;
      bool ZpQDDxSwow = false;
      bool oIceUGXApr = false;
      bool ZdQMJIixfP = false;
      bool GPfYGbBbLL = false;
      bool drIFhzBqDa = false;
      bool eWIWuuZEst = false;
      bool NVPZoYbDXr = false;
      bool FwoeOhVKdJ = false;
      bool HrsEjjHJdL = false;
      bool CxhQyIbhPJ = false;
      bool XxSLVigcIN = false;
      bool ZOZjlUbKoF = false;
      bool QRZMoINXfF = false;
      bool FmuUlKYgiA = false;
      bool CdBQlnWydc = false;
      bool fQsKrFXGVM = false;
      string zldEMzKQwV;
      string TXzlXMazcJ;
      string QmxjwCNgOF;
      string nWrSLHyNYR;
      string USKkqYwiiy;
      string myoPLLnsIJ;
      string kcBphxfgaQ;
      string ONZKnybMsX;
      string GdyQSphcGz;
      string SEFPgqRUCs;
      string rOISjZXdaN;
      string jbAjDGekWr;
      string PDaaxKHKdw;
      string gHJzeqVfgs;
      string RDBrPpDULZ;
      string MfxJdongUY;
      string RNzdgbRAFL;
      string kyEdaLBhLG;
      string GmyEiAJAVp;
      string DnKHaDDXLm;
      if(zldEMzKQwV == rOISjZXdaN){YDPzoNaTiR = true;}
      else if(rOISjZXdaN == zldEMzKQwV){NVPZoYbDXr = true;}
      if(TXzlXMazcJ == jbAjDGekWr){mGVOSeOutf = true;}
      else if(jbAjDGekWr == TXzlXMazcJ){FwoeOhVKdJ = true;}
      if(QmxjwCNgOF == PDaaxKHKdw){SReOIwnxCW = true;}
      else if(PDaaxKHKdw == QmxjwCNgOF){HrsEjjHJdL = true;}
      if(nWrSLHyNYR == gHJzeqVfgs){IdWYhDXzOU = true;}
      else if(gHJzeqVfgs == nWrSLHyNYR){CxhQyIbhPJ = true;}
      if(USKkqYwiiy == RDBrPpDULZ){ZpQDDxSwow = true;}
      else if(RDBrPpDULZ == USKkqYwiiy){XxSLVigcIN = true;}
      if(myoPLLnsIJ == MfxJdongUY){oIceUGXApr = true;}
      else if(MfxJdongUY == myoPLLnsIJ){ZOZjlUbKoF = true;}
      if(kcBphxfgaQ == RNzdgbRAFL){ZdQMJIixfP = true;}
      else if(RNzdgbRAFL == kcBphxfgaQ){QRZMoINXfF = true;}
      if(ONZKnybMsX == kyEdaLBhLG){GPfYGbBbLL = true;}
      if(GdyQSphcGz == GmyEiAJAVp){drIFhzBqDa = true;}
      if(SEFPgqRUCs == DnKHaDDXLm){eWIWuuZEst = true;}
      while(kyEdaLBhLG == ONZKnybMsX){FmuUlKYgiA = true;}
      while(GmyEiAJAVp == GmyEiAJAVp){CdBQlnWydc = true;}
      while(DnKHaDDXLm == DnKHaDDXLm){fQsKrFXGVM = true;}
      if(YDPzoNaTiR == true){YDPzoNaTiR = false;}
      if(mGVOSeOutf == true){mGVOSeOutf = false;}
      if(SReOIwnxCW == true){SReOIwnxCW = false;}
      if(IdWYhDXzOU == true){IdWYhDXzOU = false;}
      if(ZpQDDxSwow == true){ZpQDDxSwow = false;}
      if(oIceUGXApr == true){oIceUGXApr = false;}
      if(ZdQMJIixfP == true){ZdQMJIixfP = false;}
      if(GPfYGbBbLL == true){GPfYGbBbLL = false;}
      if(drIFhzBqDa == true){drIFhzBqDa = false;}
      if(eWIWuuZEst == true){eWIWuuZEst = false;}
      if(NVPZoYbDXr == true){NVPZoYbDXr = false;}
      if(FwoeOhVKdJ == true){FwoeOhVKdJ = false;}
      if(HrsEjjHJdL == true){HrsEjjHJdL = false;}
      if(CxhQyIbhPJ == true){CxhQyIbhPJ = false;}
      if(XxSLVigcIN == true){XxSLVigcIN = false;}
      if(ZOZjlUbKoF == true){ZOZjlUbKoF = false;}
      if(QRZMoINXfF == true){QRZMoINXfF = false;}
      if(FmuUlKYgiA == true){FmuUlKYgiA = false;}
      if(CdBQlnWydc == true){CdBQlnWydc = false;}
      if(fQsKrFXGVM == true){fQsKrFXGVM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFPTIANTZV
{ 
  void QppeFnLMfY()
  { 
      bool CYkVRcrRlf = false;
      bool nIyZOsxIIs = false;
      bool MOrmKRBhhm = false;
      bool SptAuAjLZZ = false;
      bool BeJTLyJqVo = false;
      bool segdbmfxLz = false;
      bool bKiyNyNyeN = false;
      bool IkihqhFYbM = false;
      bool IKMssmIPXH = false;
      bool TmAZyquKGM = false;
      bool jLLHfHuyms = false;
      bool hHVyqQxpEZ = false;
      bool pxZXtVkJjA = false;
      bool mtSObwzFMk = false;
      bool rJceZMRBhh = false;
      bool sEGgWllnMK = false;
      bool WlOmGmoGWu = false;
      bool RrdSgfUuxh = false;
      bool EiaBGhnkqp = false;
      bool KKrCNFupXl = false;
      string nYTFwadHAC;
      string hekWdboSOn;
      string BdXWYQczPk;
      string cMgEwjrOON;
      string jtHsDAhDbN;
      string hElRAJBxge;
      string xerOZVxfas;
      string jaEAEHWeTX;
      string hZWBDXZPDl;
      string itgiPEBsSg;
      string CCchcHAkMs;
      string mVdIwXHpLC;
      string uhbnKpsUjA;
      string FdLlUfwoXu;
      string WnCKyMQYlr;
      string wLgQlUZnXm;
      string NfAMmJKrnQ;
      string aSSPeGfRox;
      string YUhrDtwuzA;
      string GIQjhqnpWo;
      if(nYTFwadHAC == CCchcHAkMs){CYkVRcrRlf = true;}
      else if(CCchcHAkMs == nYTFwadHAC){jLLHfHuyms = true;}
      if(hekWdboSOn == mVdIwXHpLC){nIyZOsxIIs = true;}
      else if(mVdIwXHpLC == hekWdboSOn){hHVyqQxpEZ = true;}
      if(BdXWYQczPk == uhbnKpsUjA){MOrmKRBhhm = true;}
      else if(uhbnKpsUjA == BdXWYQczPk){pxZXtVkJjA = true;}
      if(cMgEwjrOON == FdLlUfwoXu){SptAuAjLZZ = true;}
      else if(FdLlUfwoXu == cMgEwjrOON){mtSObwzFMk = true;}
      if(jtHsDAhDbN == WnCKyMQYlr){BeJTLyJqVo = true;}
      else if(WnCKyMQYlr == jtHsDAhDbN){rJceZMRBhh = true;}
      if(hElRAJBxge == wLgQlUZnXm){segdbmfxLz = true;}
      else if(wLgQlUZnXm == hElRAJBxge){sEGgWllnMK = true;}
      if(xerOZVxfas == NfAMmJKrnQ){bKiyNyNyeN = true;}
      else if(NfAMmJKrnQ == xerOZVxfas){WlOmGmoGWu = true;}
      if(jaEAEHWeTX == aSSPeGfRox){IkihqhFYbM = true;}
      if(hZWBDXZPDl == YUhrDtwuzA){IKMssmIPXH = true;}
      if(itgiPEBsSg == GIQjhqnpWo){TmAZyquKGM = true;}
      while(aSSPeGfRox == jaEAEHWeTX){RrdSgfUuxh = true;}
      while(YUhrDtwuzA == YUhrDtwuzA){EiaBGhnkqp = true;}
      while(GIQjhqnpWo == GIQjhqnpWo){KKrCNFupXl = true;}
      if(CYkVRcrRlf == true){CYkVRcrRlf = false;}
      if(nIyZOsxIIs == true){nIyZOsxIIs = false;}
      if(MOrmKRBhhm == true){MOrmKRBhhm = false;}
      if(SptAuAjLZZ == true){SptAuAjLZZ = false;}
      if(BeJTLyJqVo == true){BeJTLyJqVo = false;}
      if(segdbmfxLz == true){segdbmfxLz = false;}
      if(bKiyNyNyeN == true){bKiyNyNyeN = false;}
      if(IkihqhFYbM == true){IkihqhFYbM = false;}
      if(IKMssmIPXH == true){IKMssmIPXH = false;}
      if(TmAZyquKGM == true){TmAZyquKGM = false;}
      if(jLLHfHuyms == true){jLLHfHuyms = false;}
      if(hHVyqQxpEZ == true){hHVyqQxpEZ = false;}
      if(pxZXtVkJjA == true){pxZXtVkJjA = false;}
      if(mtSObwzFMk == true){mtSObwzFMk = false;}
      if(rJceZMRBhh == true){rJceZMRBhh = false;}
      if(sEGgWllnMK == true){sEGgWllnMK = false;}
      if(WlOmGmoGWu == true){WlOmGmoGWu = false;}
      if(RrdSgfUuxh == true){RrdSgfUuxh = false;}
      if(EiaBGhnkqp == true){EiaBGhnkqp = false;}
      if(KKrCNFupXl == true){KKrCNFupXl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UALKRLVHQY
{ 
  void CAlyyusMxY()
  { 
      bool ZyTcuUtkXM = false;
      bool dRjcpltsbu = false;
      bool XKznsdCYIi = false;
      bool oLlTIlPFkW = false;
      bool bjyQoxRPRo = false;
      bool nMtwePzeiQ = false;
      bool SUcoWRePTE = false;
      bool WnHFSnMhzu = false;
      bool LmGTucQpos = false;
      bool ljVUEGGItW = false;
      bool SCwNRzEocp = false;
      bool CRfnEfOIts = false;
      bool AnZZRlSmAM = false;
      bool gEmbcJprBu = false;
      bool YbMypUEhPY = false;
      bool ryNBVdbVwf = false;
      bool fQnQIyeDKt = false;
      bool oVHyUYbajx = false;
      bool gkXbTiplFz = false;
      bool hTwUPHmwpq = false;
      string klUyOsIypA;
      string DSyQJWorOB;
      string XGTnuyRAKf;
      string VQYhMSVQUq;
      string ZfMsUeBfsn;
      string DREEHeSgDQ;
      string aImJdmsPDp;
      string BXWWaqsZSQ;
      string xlHWcEMUah;
      string zoNEPRrCOh;
      string kkcCmftgdQ;
      string krNmToAQgZ;
      string aYoUpLJSHJ;
      string yqLkeLJEix;
      string JepKxHaaka;
      string QbVoHMwHLa;
      string VbZTRtgcHI;
      string fugjQuheXi;
      string kihfrWVWcS;
      string OBsIahFWrD;
      if(klUyOsIypA == kkcCmftgdQ){ZyTcuUtkXM = true;}
      else if(kkcCmftgdQ == klUyOsIypA){SCwNRzEocp = true;}
      if(DSyQJWorOB == krNmToAQgZ){dRjcpltsbu = true;}
      else if(krNmToAQgZ == DSyQJWorOB){CRfnEfOIts = true;}
      if(XGTnuyRAKf == aYoUpLJSHJ){XKznsdCYIi = true;}
      else if(aYoUpLJSHJ == XGTnuyRAKf){AnZZRlSmAM = true;}
      if(VQYhMSVQUq == yqLkeLJEix){oLlTIlPFkW = true;}
      else if(yqLkeLJEix == VQYhMSVQUq){gEmbcJprBu = true;}
      if(ZfMsUeBfsn == JepKxHaaka){bjyQoxRPRo = true;}
      else if(JepKxHaaka == ZfMsUeBfsn){YbMypUEhPY = true;}
      if(DREEHeSgDQ == QbVoHMwHLa){nMtwePzeiQ = true;}
      else if(QbVoHMwHLa == DREEHeSgDQ){ryNBVdbVwf = true;}
      if(aImJdmsPDp == VbZTRtgcHI){SUcoWRePTE = true;}
      else if(VbZTRtgcHI == aImJdmsPDp){fQnQIyeDKt = true;}
      if(BXWWaqsZSQ == fugjQuheXi){WnHFSnMhzu = true;}
      if(xlHWcEMUah == kihfrWVWcS){LmGTucQpos = true;}
      if(zoNEPRrCOh == OBsIahFWrD){ljVUEGGItW = true;}
      while(fugjQuheXi == BXWWaqsZSQ){oVHyUYbajx = true;}
      while(kihfrWVWcS == kihfrWVWcS){gkXbTiplFz = true;}
      while(OBsIahFWrD == OBsIahFWrD){hTwUPHmwpq = true;}
      if(ZyTcuUtkXM == true){ZyTcuUtkXM = false;}
      if(dRjcpltsbu == true){dRjcpltsbu = false;}
      if(XKznsdCYIi == true){XKznsdCYIi = false;}
      if(oLlTIlPFkW == true){oLlTIlPFkW = false;}
      if(bjyQoxRPRo == true){bjyQoxRPRo = false;}
      if(nMtwePzeiQ == true){nMtwePzeiQ = false;}
      if(SUcoWRePTE == true){SUcoWRePTE = false;}
      if(WnHFSnMhzu == true){WnHFSnMhzu = false;}
      if(LmGTucQpos == true){LmGTucQpos = false;}
      if(ljVUEGGItW == true){ljVUEGGItW = false;}
      if(SCwNRzEocp == true){SCwNRzEocp = false;}
      if(CRfnEfOIts == true){CRfnEfOIts = false;}
      if(AnZZRlSmAM == true){AnZZRlSmAM = false;}
      if(gEmbcJprBu == true){gEmbcJprBu = false;}
      if(YbMypUEhPY == true){YbMypUEhPY = false;}
      if(ryNBVdbVwf == true){ryNBVdbVwf = false;}
      if(fQnQIyeDKt == true){fQnQIyeDKt = false;}
      if(oVHyUYbajx == true){oVHyUYbajx = false;}
      if(gkXbTiplFz == true){gkXbTiplFz = false;}
      if(hTwUPHmwpq == true){hTwUPHmwpq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVFHEKLSLV
{ 
  void DJICkMAHzs()
  { 
      bool joinecErdM = false;
      bool oBQlUMHHsy = false;
      bool kgaMtlwlgf = false;
      bool BLzpbzEazQ = false;
      bool jxouQQXdjm = false;
      bool imzEMDNVtr = false;
      bool fSKyLdBZKU = false;
      bool IgIcNmqfwc = false;
      bool OSBtxNLtdY = false;
      bool lhfGjRmqil = false;
      bool OxSOdBdWqY = false;
      bool LgZRdNRQBx = false;
      bool RHwkiZBCrw = false;
      bool AzxJNQzlQu = false;
      bool ioDFMFHNbW = false;
      bool AVpkUHBgfD = false;
      bool AbduXLjQDN = false;
      bool NezFOcEqXc = false;
      bool SmaVudJLnF = false;
      bool PRGMtHKHgB = false;
      string SLdDewulIa;
      string WNoQnOclXE;
      string hCgZDbNItl;
      string noYejkcUlK;
      string DtdYUVIAyI;
      string xmjVNQdEAC;
      string hlrWlhoKgD;
      string kIzMAnXHEg;
      string TMKkoBECQS;
      string GYTibRCHlm;
      string gxSuWnmWVZ;
      string rVASiUbGgk;
      string dlsOwMnPki;
      string lQUQAVsOOA;
      string NggqZjXBAG;
      string owZBJtDEyJ;
      string AWlmnbAiSM;
      string aMqgWwFCnL;
      string nmOdsopTHF;
      string RoQFzqusDx;
      if(SLdDewulIa == gxSuWnmWVZ){joinecErdM = true;}
      else if(gxSuWnmWVZ == SLdDewulIa){OxSOdBdWqY = true;}
      if(WNoQnOclXE == rVASiUbGgk){oBQlUMHHsy = true;}
      else if(rVASiUbGgk == WNoQnOclXE){LgZRdNRQBx = true;}
      if(hCgZDbNItl == dlsOwMnPki){kgaMtlwlgf = true;}
      else if(dlsOwMnPki == hCgZDbNItl){RHwkiZBCrw = true;}
      if(noYejkcUlK == lQUQAVsOOA){BLzpbzEazQ = true;}
      else if(lQUQAVsOOA == noYejkcUlK){AzxJNQzlQu = true;}
      if(DtdYUVIAyI == NggqZjXBAG){jxouQQXdjm = true;}
      else if(NggqZjXBAG == DtdYUVIAyI){ioDFMFHNbW = true;}
      if(xmjVNQdEAC == owZBJtDEyJ){imzEMDNVtr = true;}
      else if(owZBJtDEyJ == xmjVNQdEAC){AVpkUHBgfD = true;}
      if(hlrWlhoKgD == AWlmnbAiSM){fSKyLdBZKU = true;}
      else if(AWlmnbAiSM == hlrWlhoKgD){AbduXLjQDN = true;}
      if(kIzMAnXHEg == aMqgWwFCnL){IgIcNmqfwc = true;}
      if(TMKkoBECQS == nmOdsopTHF){OSBtxNLtdY = true;}
      if(GYTibRCHlm == RoQFzqusDx){lhfGjRmqil = true;}
      while(aMqgWwFCnL == kIzMAnXHEg){NezFOcEqXc = true;}
      while(nmOdsopTHF == nmOdsopTHF){SmaVudJLnF = true;}
      while(RoQFzqusDx == RoQFzqusDx){PRGMtHKHgB = true;}
      if(joinecErdM == true){joinecErdM = false;}
      if(oBQlUMHHsy == true){oBQlUMHHsy = false;}
      if(kgaMtlwlgf == true){kgaMtlwlgf = false;}
      if(BLzpbzEazQ == true){BLzpbzEazQ = false;}
      if(jxouQQXdjm == true){jxouQQXdjm = false;}
      if(imzEMDNVtr == true){imzEMDNVtr = false;}
      if(fSKyLdBZKU == true){fSKyLdBZKU = false;}
      if(IgIcNmqfwc == true){IgIcNmqfwc = false;}
      if(OSBtxNLtdY == true){OSBtxNLtdY = false;}
      if(lhfGjRmqil == true){lhfGjRmqil = false;}
      if(OxSOdBdWqY == true){OxSOdBdWqY = false;}
      if(LgZRdNRQBx == true){LgZRdNRQBx = false;}
      if(RHwkiZBCrw == true){RHwkiZBCrw = false;}
      if(AzxJNQzlQu == true){AzxJNQzlQu = false;}
      if(ioDFMFHNbW == true){ioDFMFHNbW = false;}
      if(AVpkUHBgfD == true){AVpkUHBgfD = false;}
      if(AbduXLjQDN == true){AbduXLjQDN = false;}
      if(NezFOcEqXc == true){NezFOcEqXc = false;}
      if(SmaVudJLnF == true){SmaVudJLnF = false;}
      if(PRGMtHKHgB == true){PRGMtHKHgB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPUUGPDKPU
{ 
  void fHSUBgcSgV()
  { 
      bool QEIVbfgwmT = false;
      bool gHCiWzIXYS = false;
      bool DLhwKkzgcN = false;
      bool yxRXHKisoo = false;
      bool xziNxkdOsw = false;
      bool LMuNbEWMKp = false;
      bool gATYVipdaM = false;
      bool POhjUEcTyY = false;
      bool HjmfCkBDuC = false;
      bool nWhzHxfJrN = false;
      bool uAngfxdLrX = false;
      bool bCOliwMmWj = false;
      bool gmhXXsfibX = false;
      bool XSajdHwGAF = false;
      bool GpKXakIwQL = false;
      bool kslIgIRPIm = false;
      bool QuiUAJbdHa = false;
      bool zFmRcqbKxm = false;
      bool kiSQmefSDV = false;
      bool ofyNnLHpWR = false;
      string NOrCYptJJI;
      string KZpuaYQjmw;
      string cyFrmjGIrp;
      string gdhaMfUCRf;
      string RsBUtazbYW;
      string hdFXpOIzPn;
      string ilRTbgrOit;
      string DORGdjxjyL;
      string jeiUHDXJkx;
      string WVmcwfagsM;
      string hjreTTLysG;
      string QYBDDECxMY;
      string IidkWhbnJy;
      string IQpkdAmEAn;
      string qZPegyTiYr;
      string cdUUDzGGHk;
      string rWotxAhPZD;
      string QxwXgiSyEY;
      string OrOQUewVhd;
      string sfxPuTkUgf;
      if(NOrCYptJJI == hjreTTLysG){QEIVbfgwmT = true;}
      else if(hjreTTLysG == NOrCYptJJI){uAngfxdLrX = true;}
      if(KZpuaYQjmw == QYBDDECxMY){gHCiWzIXYS = true;}
      else if(QYBDDECxMY == KZpuaYQjmw){bCOliwMmWj = true;}
      if(cyFrmjGIrp == IidkWhbnJy){DLhwKkzgcN = true;}
      else if(IidkWhbnJy == cyFrmjGIrp){gmhXXsfibX = true;}
      if(gdhaMfUCRf == IQpkdAmEAn){yxRXHKisoo = true;}
      else if(IQpkdAmEAn == gdhaMfUCRf){XSajdHwGAF = true;}
      if(RsBUtazbYW == qZPegyTiYr){xziNxkdOsw = true;}
      else if(qZPegyTiYr == RsBUtazbYW){GpKXakIwQL = true;}
      if(hdFXpOIzPn == cdUUDzGGHk){LMuNbEWMKp = true;}
      else if(cdUUDzGGHk == hdFXpOIzPn){kslIgIRPIm = true;}
      if(ilRTbgrOit == rWotxAhPZD){gATYVipdaM = true;}
      else if(rWotxAhPZD == ilRTbgrOit){QuiUAJbdHa = true;}
      if(DORGdjxjyL == QxwXgiSyEY){POhjUEcTyY = true;}
      if(jeiUHDXJkx == OrOQUewVhd){HjmfCkBDuC = true;}
      if(WVmcwfagsM == sfxPuTkUgf){nWhzHxfJrN = true;}
      while(QxwXgiSyEY == DORGdjxjyL){zFmRcqbKxm = true;}
      while(OrOQUewVhd == OrOQUewVhd){kiSQmefSDV = true;}
      while(sfxPuTkUgf == sfxPuTkUgf){ofyNnLHpWR = true;}
      if(QEIVbfgwmT == true){QEIVbfgwmT = false;}
      if(gHCiWzIXYS == true){gHCiWzIXYS = false;}
      if(DLhwKkzgcN == true){DLhwKkzgcN = false;}
      if(yxRXHKisoo == true){yxRXHKisoo = false;}
      if(xziNxkdOsw == true){xziNxkdOsw = false;}
      if(LMuNbEWMKp == true){LMuNbEWMKp = false;}
      if(gATYVipdaM == true){gATYVipdaM = false;}
      if(POhjUEcTyY == true){POhjUEcTyY = false;}
      if(HjmfCkBDuC == true){HjmfCkBDuC = false;}
      if(nWhzHxfJrN == true){nWhzHxfJrN = false;}
      if(uAngfxdLrX == true){uAngfxdLrX = false;}
      if(bCOliwMmWj == true){bCOliwMmWj = false;}
      if(gmhXXsfibX == true){gmhXXsfibX = false;}
      if(XSajdHwGAF == true){XSajdHwGAF = false;}
      if(GpKXakIwQL == true){GpKXakIwQL = false;}
      if(kslIgIRPIm == true){kslIgIRPIm = false;}
      if(QuiUAJbdHa == true){QuiUAJbdHa = false;}
      if(zFmRcqbKxm == true){zFmRcqbKxm = false;}
      if(kiSQmefSDV == true){kiSQmefSDV = false;}
      if(ofyNnLHpWR == true){ofyNnLHpWR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGJRCFGWSJ
{ 
  void YbFboySBmU()
  { 
      bool BWgGFGwTwN = false;
      bool XIllOqhVYj = false;
      bool rACEhIKTfZ = false;
      bool JmOXkYEyAY = false;
      bool jZIKoApPJg = false;
      bool PDTjCBTbXx = false;
      bool wcmVDksNBp = false;
      bool liVzASqrPh = false;
      bool RtJyKGSeUj = false;
      bool EbZCcHlmGE = false;
      bool GbOTughTji = false;
      bool JaMpeCSnLx = false;
      bool ROsRkKISWr = false;
      bool gEkKapfoDd = false;
      bool XytlZdOiWZ = false;
      bool nyaJlrixik = false;
      bool XOxqCFoCPo = false;
      bool VdjhYSTGqG = false;
      bool uYwwEhcbXh = false;
      bool GhFSGIBDiU = false;
      string tCBkjggBUq;
      string UstRLhgsUu;
      string YuQBGaaziy;
      string IHNzhatMAO;
      string okAMwKKnEs;
      string iifLZykAeJ;
      string FhSViNeuij;
      string nTsGGmuEEu;
      string QmtoPZaCYi;
      string oshpJGRddi;
      string eOFTFOoYEl;
      string CguisSmcFI;
      string lcVzutlCxz;
      string VQaUPBgajB;
      string jBxlgIxzxq;
      string ToXUxCrFYL;
      string cmbFQkGaSq;
      string kMrEXjejSm;
      string wlEGffsFXN;
      string IbBYXxZrUu;
      if(tCBkjggBUq == eOFTFOoYEl){BWgGFGwTwN = true;}
      else if(eOFTFOoYEl == tCBkjggBUq){GbOTughTji = true;}
      if(UstRLhgsUu == CguisSmcFI){XIllOqhVYj = true;}
      else if(CguisSmcFI == UstRLhgsUu){JaMpeCSnLx = true;}
      if(YuQBGaaziy == lcVzutlCxz){rACEhIKTfZ = true;}
      else if(lcVzutlCxz == YuQBGaaziy){ROsRkKISWr = true;}
      if(IHNzhatMAO == VQaUPBgajB){JmOXkYEyAY = true;}
      else if(VQaUPBgajB == IHNzhatMAO){gEkKapfoDd = true;}
      if(okAMwKKnEs == jBxlgIxzxq){jZIKoApPJg = true;}
      else if(jBxlgIxzxq == okAMwKKnEs){XytlZdOiWZ = true;}
      if(iifLZykAeJ == ToXUxCrFYL){PDTjCBTbXx = true;}
      else if(ToXUxCrFYL == iifLZykAeJ){nyaJlrixik = true;}
      if(FhSViNeuij == cmbFQkGaSq){wcmVDksNBp = true;}
      else if(cmbFQkGaSq == FhSViNeuij){XOxqCFoCPo = true;}
      if(nTsGGmuEEu == kMrEXjejSm){liVzASqrPh = true;}
      if(QmtoPZaCYi == wlEGffsFXN){RtJyKGSeUj = true;}
      if(oshpJGRddi == IbBYXxZrUu){EbZCcHlmGE = true;}
      while(kMrEXjejSm == nTsGGmuEEu){VdjhYSTGqG = true;}
      while(wlEGffsFXN == wlEGffsFXN){uYwwEhcbXh = true;}
      while(IbBYXxZrUu == IbBYXxZrUu){GhFSGIBDiU = true;}
      if(BWgGFGwTwN == true){BWgGFGwTwN = false;}
      if(XIllOqhVYj == true){XIllOqhVYj = false;}
      if(rACEhIKTfZ == true){rACEhIKTfZ = false;}
      if(JmOXkYEyAY == true){JmOXkYEyAY = false;}
      if(jZIKoApPJg == true){jZIKoApPJg = false;}
      if(PDTjCBTbXx == true){PDTjCBTbXx = false;}
      if(wcmVDksNBp == true){wcmVDksNBp = false;}
      if(liVzASqrPh == true){liVzASqrPh = false;}
      if(RtJyKGSeUj == true){RtJyKGSeUj = false;}
      if(EbZCcHlmGE == true){EbZCcHlmGE = false;}
      if(GbOTughTji == true){GbOTughTji = false;}
      if(JaMpeCSnLx == true){JaMpeCSnLx = false;}
      if(ROsRkKISWr == true){ROsRkKISWr = false;}
      if(gEkKapfoDd == true){gEkKapfoDd = false;}
      if(XytlZdOiWZ == true){XytlZdOiWZ = false;}
      if(nyaJlrixik == true){nyaJlrixik = false;}
      if(XOxqCFoCPo == true){XOxqCFoCPo = false;}
      if(VdjhYSTGqG == true){VdjhYSTGqG = false;}
      if(uYwwEhcbXh == true){uYwwEhcbXh = false;}
      if(GhFSGIBDiU == true){GhFSGIBDiU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBIKEQTRWG
{ 
  void YbDrCtbBVc()
  { 
      bool gRtsjKmdIh = false;
      bool dnnMrQYRPL = false;
      bool pecxxptzLz = false;
      bool zcWjmpjYNY = false;
      bool AlNRwTwHab = false;
      bool agagRCowwt = false;
      bool PnRIiBQDZC = false;
      bool fzEpKDRKAc = false;
      bool smYiYSBpSk = false;
      bool AmcTIMTEht = false;
      bool DsgYwbbjVN = false;
      bool jduSAcPiiP = false;
      bool zZkoBrVjgy = false;
      bool jMcGYAFzlw = false;
      bool pRUEAWqJTf = false;
      bool xjVRtdHrXD = false;
      bool GrCWcXBosz = false;
      bool WPxlZhFfoe = false;
      bool BLQBBAqKLu = false;
      bool sNbipyOxbb = false;
      string xYPNWDdxCl;
      string qLTKfztqSm;
      string wVSdofHeke;
      string tkFXpSqkHB;
      string nGypBLHFuM;
      string zssHjaGlYp;
      string uzMXqGGuTN;
      string IIiQyoXbbc;
      string YCiYeArymP;
      string LEMQFotayu;
      string FMkhEqJbIt;
      string CdJuRsPmrp;
      string NIIEBDwSKJ;
      string uxdgXLRBUn;
      string qPorMguRzM;
      string ZGhHgxDfgA;
      string uqQzzFAcXF;
      string bOSEzySPrT;
      string IdSyjnPVAa;
      string IkTTszyprH;
      if(xYPNWDdxCl == FMkhEqJbIt){gRtsjKmdIh = true;}
      else if(FMkhEqJbIt == xYPNWDdxCl){DsgYwbbjVN = true;}
      if(qLTKfztqSm == CdJuRsPmrp){dnnMrQYRPL = true;}
      else if(CdJuRsPmrp == qLTKfztqSm){jduSAcPiiP = true;}
      if(wVSdofHeke == NIIEBDwSKJ){pecxxptzLz = true;}
      else if(NIIEBDwSKJ == wVSdofHeke){zZkoBrVjgy = true;}
      if(tkFXpSqkHB == uxdgXLRBUn){zcWjmpjYNY = true;}
      else if(uxdgXLRBUn == tkFXpSqkHB){jMcGYAFzlw = true;}
      if(nGypBLHFuM == qPorMguRzM){AlNRwTwHab = true;}
      else if(qPorMguRzM == nGypBLHFuM){pRUEAWqJTf = true;}
      if(zssHjaGlYp == ZGhHgxDfgA){agagRCowwt = true;}
      else if(ZGhHgxDfgA == zssHjaGlYp){xjVRtdHrXD = true;}
      if(uzMXqGGuTN == uqQzzFAcXF){PnRIiBQDZC = true;}
      else if(uqQzzFAcXF == uzMXqGGuTN){GrCWcXBosz = true;}
      if(IIiQyoXbbc == bOSEzySPrT){fzEpKDRKAc = true;}
      if(YCiYeArymP == IdSyjnPVAa){smYiYSBpSk = true;}
      if(LEMQFotayu == IkTTszyprH){AmcTIMTEht = true;}
      while(bOSEzySPrT == IIiQyoXbbc){WPxlZhFfoe = true;}
      while(IdSyjnPVAa == IdSyjnPVAa){BLQBBAqKLu = true;}
      while(IkTTszyprH == IkTTszyprH){sNbipyOxbb = true;}
      if(gRtsjKmdIh == true){gRtsjKmdIh = false;}
      if(dnnMrQYRPL == true){dnnMrQYRPL = false;}
      if(pecxxptzLz == true){pecxxptzLz = false;}
      if(zcWjmpjYNY == true){zcWjmpjYNY = false;}
      if(AlNRwTwHab == true){AlNRwTwHab = false;}
      if(agagRCowwt == true){agagRCowwt = false;}
      if(PnRIiBQDZC == true){PnRIiBQDZC = false;}
      if(fzEpKDRKAc == true){fzEpKDRKAc = false;}
      if(smYiYSBpSk == true){smYiYSBpSk = false;}
      if(AmcTIMTEht == true){AmcTIMTEht = false;}
      if(DsgYwbbjVN == true){DsgYwbbjVN = false;}
      if(jduSAcPiiP == true){jduSAcPiiP = false;}
      if(zZkoBrVjgy == true){zZkoBrVjgy = false;}
      if(jMcGYAFzlw == true){jMcGYAFzlw = false;}
      if(pRUEAWqJTf == true){pRUEAWqJTf = false;}
      if(xjVRtdHrXD == true){xjVRtdHrXD = false;}
      if(GrCWcXBosz == true){GrCWcXBosz = false;}
      if(WPxlZhFfoe == true){WPxlZhFfoe = false;}
      if(BLQBBAqKLu == true){BLQBBAqKLu = false;}
      if(sNbipyOxbb == true){sNbipyOxbb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STIJPDPRVO
{ 
  void cHZxnUQJyB()
  { 
      bool GZyWUaDioE = false;
      bool UmEuIFUmZH = false;
      bool IowipRGrZd = false;
      bool KzEtXkTFEQ = false;
      bool mExZcMxrzo = false;
      bool uqyqzQcOgD = false;
      bool TLILtViKXX = false;
      bool kOhITErWGc = false;
      bool UNrjhTANtH = false;
      bool HFYBxbulfH = false;
      bool dmUbDfIpXu = false;
      bool XGIDhFSXcZ = false;
      bool UVPPPfpfLq = false;
      bool IGpyzgrQfC = false;
      bool KKozjBxUSq = false;
      bool JWJGmIWFLX = false;
      bool pcdflRPJEB = false;
      bool MBrZOJfPfO = false;
      bool iUMTgkxjLp = false;
      bool JmEIMhfJMR = false;
      string cJWKafsrlf;
      string WeFRcVcwrn;
      string uEDVnMhgGK;
      string ZYuORkEaJN;
      string sSTtWpfMey;
      string WZGZXYFAWN;
      string xMkbGxipzr;
      string QBleucjIyy;
      string fUBImARUqs;
      string eDEuQggrnZ;
      string GoMmgUmaet;
      string nwBYhbKcnF;
      string eNzGMMxpON;
      string wrUYqpIObS;
      string MpowEhCeNn;
      string WEEhtspGZT;
      string XxMQywbbgq;
      string TuAUsoXCCd;
      string KRbZqqmley;
      string ABnIuPdXyH;
      if(cJWKafsrlf == GoMmgUmaet){GZyWUaDioE = true;}
      else if(GoMmgUmaet == cJWKafsrlf){dmUbDfIpXu = true;}
      if(WeFRcVcwrn == nwBYhbKcnF){UmEuIFUmZH = true;}
      else if(nwBYhbKcnF == WeFRcVcwrn){XGIDhFSXcZ = true;}
      if(uEDVnMhgGK == eNzGMMxpON){IowipRGrZd = true;}
      else if(eNzGMMxpON == uEDVnMhgGK){UVPPPfpfLq = true;}
      if(ZYuORkEaJN == wrUYqpIObS){KzEtXkTFEQ = true;}
      else if(wrUYqpIObS == ZYuORkEaJN){IGpyzgrQfC = true;}
      if(sSTtWpfMey == MpowEhCeNn){mExZcMxrzo = true;}
      else if(MpowEhCeNn == sSTtWpfMey){KKozjBxUSq = true;}
      if(WZGZXYFAWN == WEEhtspGZT){uqyqzQcOgD = true;}
      else if(WEEhtspGZT == WZGZXYFAWN){JWJGmIWFLX = true;}
      if(xMkbGxipzr == XxMQywbbgq){TLILtViKXX = true;}
      else if(XxMQywbbgq == xMkbGxipzr){pcdflRPJEB = true;}
      if(QBleucjIyy == TuAUsoXCCd){kOhITErWGc = true;}
      if(fUBImARUqs == KRbZqqmley){UNrjhTANtH = true;}
      if(eDEuQggrnZ == ABnIuPdXyH){HFYBxbulfH = true;}
      while(TuAUsoXCCd == QBleucjIyy){MBrZOJfPfO = true;}
      while(KRbZqqmley == KRbZqqmley){iUMTgkxjLp = true;}
      while(ABnIuPdXyH == ABnIuPdXyH){JmEIMhfJMR = true;}
      if(GZyWUaDioE == true){GZyWUaDioE = false;}
      if(UmEuIFUmZH == true){UmEuIFUmZH = false;}
      if(IowipRGrZd == true){IowipRGrZd = false;}
      if(KzEtXkTFEQ == true){KzEtXkTFEQ = false;}
      if(mExZcMxrzo == true){mExZcMxrzo = false;}
      if(uqyqzQcOgD == true){uqyqzQcOgD = false;}
      if(TLILtViKXX == true){TLILtViKXX = false;}
      if(kOhITErWGc == true){kOhITErWGc = false;}
      if(UNrjhTANtH == true){UNrjhTANtH = false;}
      if(HFYBxbulfH == true){HFYBxbulfH = false;}
      if(dmUbDfIpXu == true){dmUbDfIpXu = false;}
      if(XGIDhFSXcZ == true){XGIDhFSXcZ = false;}
      if(UVPPPfpfLq == true){UVPPPfpfLq = false;}
      if(IGpyzgrQfC == true){IGpyzgrQfC = false;}
      if(KKozjBxUSq == true){KKozjBxUSq = false;}
      if(JWJGmIWFLX == true){JWJGmIWFLX = false;}
      if(pcdflRPJEB == true){pcdflRPJEB = false;}
      if(MBrZOJfPfO == true){MBrZOJfPfO = false;}
      if(iUMTgkxjLp == true){iUMTgkxjLp = false;}
      if(JmEIMhfJMR == true){JmEIMhfJMR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDFOHYXDNJ
{ 
  void DrIxBSMjLF()
  { 
      bool BwTdsqeygR = false;
      bool yhjQipNHXK = false;
      bool dkgxlVLRem = false;
      bool WTgHjhEQtI = false;
      bool ohZHBxJDoo = false;
      bool lsRcaQPWqX = false;
      bool fMSsudAbgB = false;
      bool lwMOVuKYwn = false;
      bool LHcoBdCEgS = false;
      bool RgYWcbPfMW = false;
      bool xhWnCofDHf = false;
      bool GqZCLYjdrQ = false;
      bool buuNiEWoks = false;
      bool fdLYqdjolL = false;
      bool xyxBMaHWKD = false;
      bool rknuuBlJEy = false;
      bool SpRNAbeBLh = false;
      bool ouqgTcxtAH = false;
      bool xAdhBtpQco = false;
      bool qZjnrGfjBk = false;
      string aKkqJxkCUt;
      string BpPJJfWKwj;
      string zWDpAkccoP;
      string ssHrSSWLVj;
      string jLSOQNMOXF;
      string PmEwHDGupY;
      string UIMEAHhXpp;
      string JKnMznDoYl;
      string XOEizGnKkO;
      string LaUxPayONI;
      string eoXgwEzrwT;
      string ARWEAGDcFt;
      string TXlaehoqxY;
      string ooaPGipWlt;
      string HwNROsDQwI;
      string XVIToHCwCN;
      string OHuXdKqHxR;
      string PfpKmWJUMl;
      string eYtnATgGZz;
      string ftUYfzAomE;
      if(aKkqJxkCUt == eoXgwEzrwT){BwTdsqeygR = true;}
      else if(eoXgwEzrwT == aKkqJxkCUt){xhWnCofDHf = true;}
      if(BpPJJfWKwj == ARWEAGDcFt){yhjQipNHXK = true;}
      else if(ARWEAGDcFt == BpPJJfWKwj){GqZCLYjdrQ = true;}
      if(zWDpAkccoP == TXlaehoqxY){dkgxlVLRem = true;}
      else if(TXlaehoqxY == zWDpAkccoP){buuNiEWoks = true;}
      if(ssHrSSWLVj == ooaPGipWlt){WTgHjhEQtI = true;}
      else if(ooaPGipWlt == ssHrSSWLVj){fdLYqdjolL = true;}
      if(jLSOQNMOXF == HwNROsDQwI){ohZHBxJDoo = true;}
      else if(HwNROsDQwI == jLSOQNMOXF){xyxBMaHWKD = true;}
      if(PmEwHDGupY == XVIToHCwCN){lsRcaQPWqX = true;}
      else if(XVIToHCwCN == PmEwHDGupY){rknuuBlJEy = true;}
      if(UIMEAHhXpp == OHuXdKqHxR){fMSsudAbgB = true;}
      else if(OHuXdKqHxR == UIMEAHhXpp){SpRNAbeBLh = true;}
      if(JKnMznDoYl == PfpKmWJUMl){lwMOVuKYwn = true;}
      if(XOEizGnKkO == eYtnATgGZz){LHcoBdCEgS = true;}
      if(LaUxPayONI == ftUYfzAomE){RgYWcbPfMW = true;}
      while(PfpKmWJUMl == JKnMznDoYl){ouqgTcxtAH = true;}
      while(eYtnATgGZz == eYtnATgGZz){xAdhBtpQco = true;}
      while(ftUYfzAomE == ftUYfzAomE){qZjnrGfjBk = true;}
      if(BwTdsqeygR == true){BwTdsqeygR = false;}
      if(yhjQipNHXK == true){yhjQipNHXK = false;}
      if(dkgxlVLRem == true){dkgxlVLRem = false;}
      if(WTgHjhEQtI == true){WTgHjhEQtI = false;}
      if(ohZHBxJDoo == true){ohZHBxJDoo = false;}
      if(lsRcaQPWqX == true){lsRcaQPWqX = false;}
      if(fMSsudAbgB == true){fMSsudAbgB = false;}
      if(lwMOVuKYwn == true){lwMOVuKYwn = false;}
      if(LHcoBdCEgS == true){LHcoBdCEgS = false;}
      if(RgYWcbPfMW == true){RgYWcbPfMW = false;}
      if(xhWnCofDHf == true){xhWnCofDHf = false;}
      if(GqZCLYjdrQ == true){GqZCLYjdrQ = false;}
      if(buuNiEWoks == true){buuNiEWoks = false;}
      if(fdLYqdjolL == true){fdLYqdjolL = false;}
      if(xyxBMaHWKD == true){xyxBMaHWKD = false;}
      if(rknuuBlJEy == true){rknuuBlJEy = false;}
      if(SpRNAbeBLh == true){SpRNAbeBLh = false;}
      if(ouqgTcxtAH == true){ouqgTcxtAH = false;}
      if(xAdhBtpQco == true){xAdhBtpQco = false;}
      if(qZjnrGfjBk == true){qZjnrGfjBk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCRCQJSUTY
{ 
  void hfqfufWwUH()
  { 
      bool ZLlOxdKAIX = false;
      bool UppelJQjtO = false;
      bool TCYUhNBytn = false;
      bool HYXzsbbrsS = false;
      bool jttpturzuC = false;
      bool IebBbWmQfi = false;
      bool bMFUQwRqkJ = false;
      bool hXqbdYIhZm = false;
      bool VCCrecxVWW = false;
      bool oKLJpWnZZy = false;
      bool cANkUknAXC = false;
      bool OEqsMYKNpm = false;
      bool ywUOUWLgkH = false;
      bool khIbJUoQXt = false;
      bool owyTHjTSxQ = false;
      bool MajlzffyQx = false;
      bool YGPPRfuOiq = false;
      bool jsouyCyAHj = false;
      bool CsjTtKyWbc = false;
      bool npAZVhghCa = false;
      string BBoTSyYPIt;
      string LwJTUkgKZa;
      string wjKexdaoKY;
      string aBdcpFEJFg;
      string ChiCQqXSNr;
      string fRCUIQpKWn;
      string XjEjTKRgdO;
      string fWFsXOAIOF;
      string FHaSsIyJTZ;
      string OtmQJScyhF;
      string ZqoyLILJwt;
      string PhuQhPIlqK;
      string LIMEAljnjF;
      string kBaIfOScGj;
      string xoMYJgyVhs;
      string JpHWtQdkyZ;
      string XWZpJNGmjT;
      string wfeGNWuntS;
      string mNGpwutDNP;
      string khdgMZOVPu;
      if(BBoTSyYPIt == ZqoyLILJwt){ZLlOxdKAIX = true;}
      else if(ZqoyLILJwt == BBoTSyYPIt){cANkUknAXC = true;}
      if(LwJTUkgKZa == PhuQhPIlqK){UppelJQjtO = true;}
      else if(PhuQhPIlqK == LwJTUkgKZa){OEqsMYKNpm = true;}
      if(wjKexdaoKY == LIMEAljnjF){TCYUhNBytn = true;}
      else if(LIMEAljnjF == wjKexdaoKY){ywUOUWLgkH = true;}
      if(aBdcpFEJFg == kBaIfOScGj){HYXzsbbrsS = true;}
      else if(kBaIfOScGj == aBdcpFEJFg){khIbJUoQXt = true;}
      if(ChiCQqXSNr == xoMYJgyVhs){jttpturzuC = true;}
      else if(xoMYJgyVhs == ChiCQqXSNr){owyTHjTSxQ = true;}
      if(fRCUIQpKWn == JpHWtQdkyZ){IebBbWmQfi = true;}
      else if(JpHWtQdkyZ == fRCUIQpKWn){MajlzffyQx = true;}
      if(XjEjTKRgdO == XWZpJNGmjT){bMFUQwRqkJ = true;}
      else if(XWZpJNGmjT == XjEjTKRgdO){YGPPRfuOiq = true;}
      if(fWFsXOAIOF == wfeGNWuntS){hXqbdYIhZm = true;}
      if(FHaSsIyJTZ == mNGpwutDNP){VCCrecxVWW = true;}
      if(OtmQJScyhF == khdgMZOVPu){oKLJpWnZZy = true;}
      while(wfeGNWuntS == fWFsXOAIOF){jsouyCyAHj = true;}
      while(mNGpwutDNP == mNGpwutDNP){CsjTtKyWbc = true;}
      while(khdgMZOVPu == khdgMZOVPu){npAZVhghCa = true;}
      if(ZLlOxdKAIX == true){ZLlOxdKAIX = false;}
      if(UppelJQjtO == true){UppelJQjtO = false;}
      if(TCYUhNBytn == true){TCYUhNBytn = false;}
      if(HYXzsbbrsS == true){HYXzsbbrsS = false;}
      if(jttpturzuC == true){jttpturzuC = false;}
      if(IebBbWmQfi == true){IebBbWmQfi = false;}
      if(bMFUQwRqkJ == true){bMFUQwRqkJ = false;}
      if(hXqbdYIhZm == true){hXqbdYIhZm = false;}
      if(VCCrecxVWW == true){VCCrecxVWW = false;}
      if(oKLJpWnZZy == true){oKLJpWnZZy = false;}
      if(cANkUknAXC == true){cANkUknAXC = false;}
      if(OEqsMYKNpm == true){OEqsMYKNpm = false;}
      if(ywUOUWLgkH == true){ywUOUWLgkH = false;}
      if(khIbJUoQXt == true){khIbJUoQXt = false;}
      if(owyTHjTSxQ == true){owyTHjTSxQ = false;}
      if(MajlzffyQx == true){MajlzffyQx = false;}
      if(YGPPRfuOiq == true){YGPPRfuOiq = false;}
      if(jsouyCyAHj == true){jsouyCyAHj = false;}
      if(CsjTtKyWbc == true){CsjTtKyWbc = false;}
      if(npAZVhghCa == true){npAZVhghCa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNNNDMHBZC
{ 
  void qmwQErRbAZ()
  { 
      bool snzwKAtlwD = false;
      bool VEoUaYZlNH = false;
      bool syfzRbxUSr = false;
      bool VauUPYmoie = false;
      bool KpTHNVOOGO = false;
      bool EuVwhuIAeh = false;
      bool DYTEguJTEB = false;
      bool kkCixCdYku = false;
      bool MhODnaFymU = false;
      bool QmKAakWOaS = false;
      bool MuKEcSrlzf = false;
      bool QiOiVVKQQF = false;
      bool pKgijyaCHM = false;
      bool fOxSiRXJZU = false;
      bool iSzGEgXaeF = false;
      bool ZGyVbBNaTe = false;
      bool rodlABlwAD = false;
      bool xBpuVXKZdD = false;
      bool ZzXClZPbpg = false;
      bool EwoubtnMGD = false;
      string cJuwnfXqFw;
      string irGpsQOcHN;
      string OMrAQOlXQQ;
      string EqZMGWiMmH;
      string asoZNiOPQO;
      string ibPrhPRufY;
      string sAZnqqStjV;
      string gCozmUWSmg;
      string AVGCgcbgdp;
      string FngOOaTAhV;
      string QUftgglPFN;
      string ryIyYWsWHN;
      string PkPsQsUakM;
      string BWjQPfpMUA;
      string pLbQxHfhoq;
      string gwsTGfEldn;
      string LLerMVNqis;
      string gfBGWDJzwJ;
      string NmkseEcPKj;
      string aEignegiEa;
      if(cJuwnfXqFw == QUftgglPFN){snzwKAtlwD = true;}
      else if(QUftgglPFN == cJuwnfXqFw){MuKEcSrlzf = true;}
      if(irGpsQOcHN == ryIyYWsWHN){VEoUaYZlNH = true;}
      else if(ryIyYWsWHN == irGpsQOcHN){QiOiVVKQQF = true;}
      if(OMrAQOlXQQ == PkPsQsUakM){syfzRbxUSr = true;}
      else if(PkPsQsUakM == OMrAQOlXQQ){pKgijyaCHM = true;}
      if(EqZMGWiMmH == BWjQPfpMUA){VauUPYmoie = true;}
      else if(BWjQPfpMUA == EqZMGWiMmH){fOxSiRXJZU = true;}
      if(asoZNiOPQO == pLbQxHfhoq){KpTHNVOOGO = true;}
      else if(pLbQxHfhoq == asoZNiOPQO){iSzGEgXaeF = true;}
      if(ibPrhPRufY == gwsTGfEldn){EuVwhuIAeh = true;}
      else if(gwsTGfEldn == ibPrhPRufY){ZGyVbBNaTe = true;}
      if(sAZnqqStjV == LLerMVNqis){DYTEguJTEB = true;}
      else if(LLerMVNqis == sAZnqqStjV){rodlABlwAD = true;}
      if(gCozmUWSmg == gfBGWDJzwJ){kkCixCdYku = true;}
      if(AVGCgcbgdp == NmkseEcPKj){MhODnaFymU = true;}
      if(FngOOaTAhV == aEignegiEa){QmKAakWOaS = true;}
      while(gfBGWDJzwJ == gCozmUWSmg){xBpuVXKZdD = true;}
      while(NmkseEcPKj == NmkseEcPKj){ZzXClZPbpg = true;}
      while(aEignegiEa == aEignegiEa){EwoubtnMGD = true;}
      if(snzwKAtlwD == true){snzwKAtlwD = false;}
      if(VEoUaYZlNH == true){VEoUaYZlNH = false;}
      if(syfzRbxUSr == true){syfzRbxUSr = false;}
      if(VauUPYmoie == true){VauUPYmoie = false;}
      if(KpTHNVOOGO == true){KpTHNVOOGO = false;}
      if(EuVwhuIAeh == true){EuVwhuIAeh = false;}
      if(DYTEguJTEB == true){DYTEguJTEB = false;}
      if(kkCixCdYku == true){kkCixCdYku = false;}
      if(MhODnaFymU == true){MhODnaFymU = false;}
      if(QmKAakWOaS == true){QmKAakWOaS = false;}
      if(MuKEcSrlzf == true){MuKEcSrlzf = false;}
      if(QiOiVVKQQF == true){QiOiVVKQQF = false;}
      if(pKgijyaCHM == true){pKgijyaCHM = false;}
      if(fOxSiRXJZU == true){fOxSiRXJZU = false;}
      if(iSzGEgXaeF == true){iSzGEgXaeF = false;}
      if(ZGyVbBNaTe == true){ZGyVbBNaTe = false;}
      if(rodlABlwAD == true){rodlABlwAD = false;}
      if(xBpuVXKZdD == true){xBpuVXKZdD = false;}
      if(ZzXClZPbpg == true){ZzXClZPbpg = false;}
      if(EwoubtnMGD == true){EwoubtnMGD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGZHMJVLCV
{ 
  void jSwGDLchjj()
  { 
      bool ArsgfgWWXB = false;
      bool osUouDTMSm = false;
      bool wmcZpkhXQQ = false;
      bool NfPGFmifsz = false;
      bool QoRWlODPUz = false;
      bool cCUpsNPTqu = false;
      bool zyGHnIdNjI = false;
      bool TnTTVGVGma = false;
      bool hRDRmKKZNr = false;
      bool XOnyASiJic = false;
      bool kpfMeniBTl = false;
      bool rIfPMguoTc = false;
      bool yDzrjEAUSD = false;
      bool XLXKpqlplz = false;
      bool bJGbAOiXkT = false;
      bool XspFegpnbZ = false;
      bool nNhQNgkVZV = false;
      bool tECUBnxXrV = false;
      bool VbjzfdUReI = false;
      bool ByOMKNaoNT = false;
      string iGDAXLjsgz;
      string fsfSNdUTnd;
      string ObqrNwNVRs;
      string zCwBPxHRBl;
      string VUggjMPNsX;
      string GtCIUGPKla;
      string yOanzdweCQ;
      string WDSCHsuJIB;
      string gzbslFAnfI;
      string hwfZmGsrgG;
      string QkKcBDaAAa;
      string LFCktylgBt;
      string cHyshZWsOA;
      string ACcBjuozri;
      string eAnExcstfo;
      string TLpmdImQtb;
      string fgkzaIcBAy;
      string JmoSObTswF;
      string fcMYfnMoXa;
      string IXEQCxOnco;
      if(iGDAXLjsgz == QkKcBDaAAa){ArsgfgWWXB = true;}
      else if(QkKcBDaAAa == iGDAXLjsgz){kpfMeniBTl = true;}
      if(fsfSNdUTnd == LFCktylgBt){osUouDTMSm = true;}
      else if(LFCktylgBt == fsfSNdUTnd){rIfPMguoTc = true;}
      if(ObqrNwNVRs == cHyshZWsOA){wmcZpkhXQQ = true;}
      else if(cHyshZWsOA == ObqrNwNVRs){yDzrjEAUSD = true;}
      if(zCwBPxHRBl == ACcBjuozri){NfPGFmifsz = true;}
      else if(ACcBjuozri == zCwBPxHRBl){XLXKpqlplz = true;}
      if(VUggjMPNsX == eAnExcstfo){QoRWlODPUz = true;}
      else if(eAnExcstfo == VUggjMPNsX){bJGbAOiXkT = true;}
      if(GtCIUGPKla == TLpmdImQtb){cCUpsNPTqu = true;}
      else if(TLpmdImQtb == GtCIUGPKla){XspFegpnbZ = true;}
      if(yOanzdweCQ == fgkzaIcBAy){zyGHnIdNjI = true;}
      else if(fgkzaIcBAy == yOanzdweCQ){nNhQNgkVZV = true;}
      if(WDSCHsuJIB == JmoSObTswF){TnTTVGVGma = true;}
      if(gzbslFAnfI == fcMYfnMoXa){hRDRmKKZNr = true;}
      if(hwfZmGsrgG == IXEQCxOnco){XOnyASiJic = true;}
      while(JmoSObTswF == WDSCHsuJIB){tECUBnxXrV = true;}
      while(fcMYfnMoXa == fcMYfnMoXa){VbjzfdUReI = true;}
      while(IXEQCxOnco == IXEQCxOnco){ByOMKNaoNT = true;}
      if(ArsgfgWWXB == true){ArsgfgWWXB = false;}
      if(osUouDTMSm == true){osUouDTMSm = false;}
      if(wmcZpkhXQQ == true){wmcZpkhXQQ = false;}
      if(NfPGFmifsz == true){NfPGFmifsz = false;}
      if(QoRWlODPUz == true){QoRWlODPUz = false;}
      if(cCUpsNPTqu == true){cCUpsNPTqu = false;}
      if(zyGHnIdNjI == true){zyGHnIdNjI = false;}
      if(TnTTVGVGma == true){TnTTVGVGma = false;}
      if(hRDRmKKZNr == true){hRDRmKKZNr = false;}
      if(XOnyASiJic == true){XOnyASiJic = false;}
      if(kpfMeniBTl == true){kpfMeniBTl = false;}
      if(rIfPMguoTc == true){rIfPMguoTc = false;}
      if(yDzrjEAUSD == true){yDzrjEAUSD = false;}
      if(XLXKpqlplz == true){XLXKpqlplz = false;}
      if(bJGbAOiXkT == true){bJGbAOiXkT = false;}
      if(XspFegpnbZ == true){XspFegpnbZ = false;}
      if(nNhQNgkVZV == true){nNhQNgkVZV = false;}
      if(tECUBnxXrV == true){tECUBnxXrV = false;}
      if(VbjzfdUReI == true){VbjzfdUReI = false;}
      if(ByOMKNaoNT == true){ByOMKNaoNT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKYNROFZWH
{ 
  void BstnGVIJXa()
  { 
      bool LNtExKsGBF = false;
      bool rKxLBcuwOY = false;
      bool FaMxmyqkrY = false;
      bool DxdJShDOjb = false;
      bool cVwaUQkbMf = false;
      bool RYAnJjAwQz = false;
      bool SINcCufnrT = false;
      bool ZgMmwjdlcW = false;
      bool MPXLGdxpzi = false;
      bool gGxkITHTXZ = false;
      bool jxisGkMMrY = false;
      bool FOTtlDjBVY = false;
      bool xpnJlSiadb = false;
      bool bKNDmPgdFV = false;
      bool RjyZdSlDyF = false;
      bool iGyzbsIZHm = false;
      bool BkiPxuAQGW = false;
      bool WGuAGNrOeS = false;
      bool gfcYrVLOas = false;
      bool HGWRTgBhch = false;
      string iqDeFKtAjY;
      string dVFBLxxWbT;
      string sioiCnbBcf;
      string dMzqPzgLZy;
      string qaByUCNdRQ;
      string QyUFaACUcQ;
      string irXDuQVOlM;
      string PlwcbRhpOz;
      string axiLPersPP;
      string xMhJPzDxDD;
      string gzrFAeCqdI;
      string RLFcpkILnP;
      string YbyVPDDmMc;
      string OklLSbEdLk;
      string cAPHxkHFSd;
      string prIndEBVpx;
      string aPeBtgZtKO;
      string gezClYLqYd;
      string uxThlVbygN;
      string ahmOJNVOMP;
      if(iqDeFKtAjY == gzrFAeCqdI){LNtExKsGBF = true;}
      else if(gzrFAeCqdI == iqDeFKtAjY){jxisGkMMrY = true;}
      if(dVFBLxxWbT == RLFcpkILnP){rKxLBcuwOY = true;}
      else if(RLFcpkILnP == dVFBLxxWbT){FOTtlDjBVY = true;}
      if(sioiCnbBcf == YbyVPDDmMc){FaMxmyqkrY = true;}
      else if(YbyVPDDmMc == sioiCnbBcf){xpnJlSiadb = true;}
      if(dMzqPzgLZy == OklLSbEdLk){DxdJShDOjb = true;}
      else if(OklLSbEdLk == dMzqPzgLZy){bKNDmPgdFV = true;}
      if(qaByUCNdRQ == cAPHxkHFSd){cVwaUQkbMf = true;}
      else if(cAPHxkHFSd == qaByUCNdRQ){RjyZdSlDyF = true;}
      if(QyUFaACUcQ == prIndEBVpx){RYAnJjAwQz = true;}
      else if(prIndEBVpx == QyUFaACUcQ){iGyzbsIZHm = true;}
      if(irXDuQVOlM == aPeBtgZtKO){SINcCufnrT = true;}
      else if(aPeBtgZtKO == irXDuQVOlM){BkiPxuAQGW = true;}
      if(PlwcbRhpOz == gezClYLqYd){ZgMmwjdlcW = true;}
      if(axiLPersPP == uxThlVbygN){MPXLGdxpzi = true;}
      if(xMhJPzDxDD == ahmOJNVOMP){gGxkITHTXZ = true;}
      while(gezClYLqYd == PlwcbRhpOz){WGuAGNrOeS = true;}
      while(uxThlVbygN == uxThlVbygN){gfcYrVLOas = true;}
      while(ahmOJNVOMP == ahmOJNVOMP){HGWRTgBhch = true;}
      if(LNtExKsGBF == true){LNtExKsGBF = false;}
      if(rKxLBcuwOY == true){rKxLBcuwOY = false;}
      if(FaMxmyqkrY == true){FaMxmyqkrY = false;}
      if(DxdJShDOjb == true){DxdJShDOjb = false;}
      if(cVwaUQkbMf == true){cVwaUQkbMf = false;}
      if(RYAnJjAwQz == true){RYAnJjAwQz = false;}
      if(SINcCufnrT == true){SINcCufnrT = false;}
      if(ZgMmwjdlcW == true){ZgMmwjdlcW = false;}
      if(MPXLGdxpzi == true){MPXLGdxpzi = false;}
      if(gGxkITHTXZ == true){gGxkITHTXZ = false;}
      if(jxisGkMMrY == true){jxisGkMMrY = false;}
      if(FOTtlDjBVY == true){FOTtlDjBVY = false;}
      if(xpnJlSiadb == true){xpnJlSiadb = false;}
      if(bKNDmPgdFV == true){bKNDmPgdFV = false;}
      if(RjyZdSlDyF == true){RjyZdSlDyF = false;}
      if(iGyzbsIZHm == true){iGyzbsIZHm = false;}
      if(BkiPxuAQGW == true){BkiPxuAQGW = false;}
      if(WGuAGNrOeS == true){WGuAGNrOeS = false;}
      if(gfcYrVLOas == true){gfcYrVLOas = false;}
      if(HGWRTgBhch == true){HGWRTgBhch = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FUCBEUMYXD
{ 
  void oWhBJzZVlR()
  { 
      bool hjfAgcppAF = false;
      bool orbFilNHrS = false;
      bool fmGLpXjjuT = false;
      bool dHyWFRpGiL = false;
      bool EnuQpKIIeb = false;
      bool EMWmtudTJI = false;
      bool rGugbhtEAR = false;
      bool uGYfOrqoVf = false;
      bool PbFSPQkLbJ = false;
      bool mWxaTyrNnH = false;
      bool QDIMgynpXC = false;
      bool DoxdrPAbRL = false;
      bool xhcpeXIyMQ = false;
      bool AdANOMTrlR = false;
      bool ctnZFyYThD = false;
      bool xPwcKiaRhI = false;
      bool oodGCZnjOf = false;
      bool uHpziCsDjf = false;
      bool zoPITjgWCf = false;
      bool lBKdbmQhWe = false;
      string ltFTDTIgez;
      string UwWgiZSzEq;
      string GoidMjjuhc;
      string TJlhXtsPIq;
      string tkgpHoLRng;
      string EMnsRxKaHT;
      string jNyCfLKoJn;
      string gCpMwUIsWW;
      string XRHAXHUrPZ;
      string iRIoHgldKu;
      string eWIzACVbww;
      string oREjuRGyeX;
      string qSYiFOtBEP;
      string idiarBJHzV;
      string lrwTkRMXto;
      string anzlELxYtk;
      string HUWgNKicrt;
      string IyyIkyWExn;
      string BVGPntewWf;
      string DjNONRUOGa;
      if(ltFTDTIgez == eWIzACVbww){hjfAgcppAF = true;}
      else if(eWIzACVbww == ltFTDTIgez){QDIMgynpXC = true;}
      if(UwWgiZSzEq == oREjuRGyeX){orbFilNHrS = true;}
      else if(oREjuRGyeX == UwWgiZSzEq){DoxdrPAbRL = true;}
      if(GoidMjjuhc == qSYiFOtBEP){fmGLpXjjuT = true;}
      else if(qSYiFOtBEP == GoidMjjuhc){xhcpeXIyMQ = true;}
      if(TJlhXtsPIq == idiarBJHzV){dHyWFRpGiL = true;}
      else if(idiarBJHzV == TJlhXtsPIq){AdANOMTrlR = true;}
      if(tkgpHoLRng == lrwTkRMXto){EnuQpKIIeb = true;}
      else if(lrwTkRMXto == tkgpHoLRng){ctnZFyYThD = true;}
      if(EMnsRxKaHT == anzlELxYtk){EMWmtudTJI = true;}
      else if(anzlELxYtk == EMnsRxKaHT){xPwcKiaRhI = true;}
      if(jNyCfLKoJn == HUWgNKicrt){rGugbhtEAR = true;}
      else if(HUWgNKicrt == jNyCfLKoJn){oodGCZnjOf = true;}
      if(gCpMwUIsWW == IyyIkyWExn){uGYfOrqoVf = true;}
      if(XRHAXHUrPZ == BVGPntewWf){PbFSPQkLbJ = true;}
      if(iRIoHgldKu == DjNONRUOGa){mWxaTyrNnH = true;}
      while(IyyIkyWExn == gCpMwUIsWW){uHpziCsDjf = true;}
      while(BVGPntewWf == BVGPntewWf){zoPITjgWCf = true;}
      while(DjNONRUOGa == DjNONRUOGa){lBKdbmQhWe = true;}
      if(hjfAgcppAF == true){hjfAgcppAF = false;}
      if(orbFilNHrS == true){orbFilNHrS = false;}
      if(fmGLpXjjuT == true){fmGLpXjjuT = false;}
      if(dHyWFRpGiL == true){dHyWFRpGiL = false;}
      if(EnuQpKIIeb == true){EnuQpKIIeb = false;}
      if(EMWmtudTJI == true){EMWmtudTJI = false;}
      if(rGugbhtEAR == true){rGugbhtEAR = false;}
      if(uGYfOrqoVf == true){uGYfOrqoVf = false;}
      if(PbFSPQkLbJ == true){PbFSPQkLbJ = false;}
      if(mWxaTyrNnH == true){mWxaTyrNnH = false;}
      if(QDIMgynpXC == true){QDIMgynpXC = false;}
      if(DoxdrPAbRL == true){DoxdrPAbRL = false;}
      if(xhcpeXIyMQ == true){xhcpeXIyMQ = false;}
      if(AdANOMTrlR == true){AdANOMTrlR = false;}
      if(ctnZFyYThD == true){ctnZFyYThD = false;}
      if(xPwcKiaRhI == true){xPwcKiaRhI = false;}
      if(oodGCZnjOf == true){oodGCZnjOf = false;}
      if(uHpziCsDjf == true){uHpziCsDjf = false;}
      if(zoPITjgWCf == true){zoPITjgWCf = false;}
      if(lBKdbmQhWe == true){lBKdbmQhWe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSHLJNIVZE
{ 
  void EgKaOJxgdP()
  { 
      bool kLlKrHwujA = false;
      bool bIoXmVhUpU = false;
      bool RDOHcEjVFh = false;
      bool aScSVOLQYG = false;
      bool EHyEqrsgjL = false;
      bool EAzYphxdgm = false;
      bool WZpBZIfVCY = false;
      bool JQuiPKEJPk = false;
      bool LCkscZTEcn = false;
      bool RgiljeRxei = false;
      bool MWdLBmFPJf = false;
      bool cnOwaUowXz = false;
      bool nasOHchJzk = false;
      bool rGefYoXYro = false;
      bool TDuwKdSlKP = false;
      bool pUYetkdPEY = false;
      bool FwQXmWIhXl = false;
      bool wPDhekfwEd = false;
      bool JuzjtXhAlm = false;
      bool LIUTjXlWJn = false;
      string MDUZrSrfnF;
      string iYTaFhXggX;
      string eATxzfQZnR;
      string RoJFrfYSNS;
      string oPsJuFgAhe;
      string jtxycLiXZL;
      string BSqVntPOiZ;
      string IETOhPHJCt;
      string zPrJgWqKbf;
      string wBsCQWXWVA;
      string oRRHVeaiPM;
      string EZVfLkZhoQ;
      string DElCcHLRxL;
      string qjnBEgxjmB;
      string wHuObWfMpf;
      string xphEwkfPeO;
      string TJlEVTlTae;
      string motmUwJWaG;
      string aybROBCiFT;
      string BhFXhlUpsH;
      if(MDUZrSrfnF == oRRHVeaiPM){kLlKrHwujA = true;}
      else if(oRRHVeaiPM == MDUZrSrfnF){MWdLBmFPJf = true;}
      if(iYTaFhXggX == EZVfLkZhoQ){bIoXmVhUpU = true;}
      else if(EZVfLkZhoQ == iYTaFhXggX){cnOwaUowXz = true;}
      if(eATxzfQZnR == DElCcHLRxL){RDOHcEjVFh = true;}
      else if(DElCcHLRxL == eATxzfQZnR){nasOHchJzk = true;}
      if(RoJFrfYSNS == qjnBEgxjmB){aScSVOLQYG = true;}
      else if(qjnBEgxjmB == RoJFrfYSNS){rGefYoXYro = true;}
      if(oPsJuFgAhe == wHuObWfMpf){EHyEqrsgjL = true;}
      else if(wHuObWfMpf == oPsJuFgAhe){TDuwKdSlKP = true;}
      if(jtxycLiXZL == xphEwkfPeO){EAzYphxdgm = true;}
      else if(xphEwkfPeO == jtxycLiXZL){pUYetkdPEY = true;}
      if(BSqVntPOiZ == TJlEVTlTae){WZpBZIfVCY = true;}
      else if(TJlEVTlTae == BSqVntPOiZ){FwQXmWIhXl = true;}
      if(IETOhPHJCt == motmUwJWaG){JQuiPKEJPk = true;}
      if(zPrJgWqKbf == aybROBCiFT){LCkscZTEcn = true;}
      if(wBsCQWXWVA == BhFXhlUpsH){RgiljeRxei = true;}
      while(motmUwJWaG == IETOhPHJCt){wPDhekfwEd = true;}
      while(aybROBCiFT == aybROBCiFT){JuzjtXhAlm = true;}
      while(BhFXhlUpsH == BhFXhlUpsH){LIUTjXlWJn = true;}
      if(kLlKrHwujA == true){kLlKrHwujA = false;}
      if(bIoXmVhUpU == true){bIoXmVhUpU = false;}
      if(RDOHcEjVFh == true){RDOHcEjVFh = false;}
      if(aScSVOLQYG == true){aScSVOLQYG = false;}
      if(EHyEqrsgjL == true){EHyEqrsgjL = false;}
      if(EAzYphxdgm == true){EAzYphxdgm = false;}
      if(WZpBZIfVCY == true){WZpBZIfVCY = false;}
      if(JQuiPKEJPk == true){JQuiPKEJPk = false;}
      if(LCkscZTEcn == true){LCkscZTEcn = false;}
      if(RgiljeRxei == true){RgiljeRxei = false;}
      if(MWdLBmFPJf == true){MWdLBmFPJf = false;}
      if(cnOwaUowXz == true){cnOwaUowXz = false;}
      if(nasOHchJzk == true){nasOHchJzk = false;}
      if(rGefYoXYro == true){rGefYoXYro = false;}
      if(TDuwKdSlKP == true){TDuwKdSlKP = false;}
      if(pUYetkdPEY == true){pUYetkdPEY = false;}
      if(FwQXmWIhXl == true){FwQXmWIhXl = false;}
      if(wPDhekfwEd == true){wPDhekfwEd = false;}
      if(JuzjtXhAlm == true){JuzjtXhAlm = false;}
      if(LIUTjXlWJn == true){LIUTjXlWJn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYSZDJNKRL
{ 
  void KMprgJmnJz()
  { 
      bool VkkPePLMFA = false;
      bool yRhGaFVqET = false;
      bool zJlOnfUxPK = false;
      bool tQRJXirPlT = false;
      bool GYgGBdBqgQ = false;
      bool dLrUrMyWaz = false;
      bool uOxtFgAXhq = false;
      bool NGFjMZbfNJ = false;
      bool dcPzfhYwQL = false;
      bool jVnmXqbmAU = false;
      bool dcIoDXGHHR = false;
      bool jSIRUSzxNW = false;
      bool HDHWHqSSMU = false;
      bool yoerfBTZuI = false;
      bool bRnzaRMWRF = false;
      bool rdYdMZVlhL = false;
      bool EnumTtmPkS = false;
      bool yYCEupOIwo = false;
      bool euAGcTPBfF = false;
      bool fhriDmWBeg = false;
      string ulUGDsPXww;
      string VANrUPReYm;
      string moGJOSerSh;
      string BhMeJtnQrn;
      string WdIZwuoyjV;
      string OSDWfGeLrj;
      string NXENunmhiZ;
      string bBmkQIggMS;
      string cgHxThdpzD;
      string OcXHZyYtdI;
      string IHOKtMfSFW;
      string YyyYGgPHtN;
      string JxifKzceKR;
      string jmCEKVRxCG;
      string BLjbdQezAs;
      string hQAQyLYizu;
      string jAInmlusNk;
      string OSEmLyMGBs;
      string UdeQjSllGz;
      string wixHWADwor;
      if(ulUGDsPXww == IHOKtMfSFW){VkkPePLMFA = true;}
      else if(IHOKtMfSFW == ulUGDsPXww){dcIoDXGHHR = true;}
      if(VANrUPReYm == YyyYGgPHtN){yRhGaFVqET = true;}
      else if(YyyYGgPHtN == VANrUPReYm){jSIRUSzxNW = true;}
      if(moGJOSerSh == JxifKzceKR){zJlOnfUxPK = true;}
      else if(JxifKzceKR == moGJOSerSh){HDHWHqSSMU = true;}
      if(BhMeJtnQrn == jmCEKVRxCG){tQRJXirPlT = true;}
      else if(jmCEKVRxCG == BhMeJtnQrn){yoerfBTZuI = true;}
      if(WdIZwuoyjV == BLjbdQezAs){GYgGBdBqgQ = true;}
      else if(BLjbdQezAs == WdIZwuoyjV){bRnzaRMWRF = true;}
      if(OSDWfGeLrj == hQAQyLYizu){dLrUrMyWaz = true;}
      else if(hQAQyLYizu == OSDWfGeLrj){rdYdMZVlhL = true;}
      if(NXENunmhiZ == jAInmlusNk){uOxtFgAXhq = true;}
      else if(jAInmlusNk == NXENunmhiZ){EnumTtmPkS = true;}
      if(bBmkQIggMS == OSEmLyMGBs){NGFjMZbfNJ = true;}
      if(cgHxThdpzD == UdeQjSllGz){dcPzfhYwQL = true;}
      if(OcXHZyYtdI == wixHWADwor){jVnmXqbmAU = true;}
      while(OSEmLyMGBs == bBmkQIggMS){yYCEupOIwo = true;}
      while(UdeQjSllGz == UdeQjSllGz){euAGcTPBfF = true;}
      while(wixHWADwor == wixHWADwor){fhriDmWBeg = true;}
      if(VkkPePLMFA == true){VkkPePLMFA = false;}
      if(yRhGaFVqET == true){yRhGaFVqET = false;}
      if(zJlOnfUxPK == true){zJlOnfUxPK = false;}
      if(tQRJXirPlT == true){tQRJXirPlT = false;}
      if(GYgGBdBqgQ == true){GYgGBdBqgQ = false;}
      if(dLrUrMyWaz == true){dLrUrMyWaz = false;}
      if(uOxtFgAXhq == true){uOxtFgAXhq = false;}
      if(NGFjMZbfNJ == true){NGFjMZbfNJ = false;}
      if(dcPzfhYwQL == true){dcPzfhYwQL = false;}
      if(jVnmXqbmAU == true){jVnmXqbmAU = false;}
      if(dcIoDXGHHR == true){dcIoDXGHHR = false;}
      if(jSIRUSzxNW == true){jSIRUSzxNW = false;}
      if(HDHWHqSSMU == true){HDHWHqSSMU = false;}
      if(yoerfBTZuI == true){yoerfBTZuI = false;}
      if(bRnzaRMWRF == true){bRnzaRMWRF = false;}
      if(rdYdMZVlhL == true){rdYdMZVlhL = false;}
      if(EnumTtmPkS == true){EnumTtmPkS = false;}
      if(yYCEupOIwo == true){yYCEupOIwo = false;}
      if(euAGcTPBfF == true){euAGcTPBfF = false;}
      if(fhriDmWBeg == true){fhriDmWBeg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTJDTOJYSL
{ 
  void TRTofyDOFL()
  { 
      bool CmOCGiifSF = false;
      bool XjewgcAZnj = false;
      bool VdlVwaKizO = false;
      bool aKCynaYuPW = false;
      bool ckIsHwHAof = false;
      bool znlxTXAsFe = false;
      bool YzgDeNhgIG = false;
      bool DEJRHjUsNA = false;
      bool TJtSPlYEeP = false;
      bool ZfojxcDEOt = false;
      bool NZrhbtdTpi = false;
      bool CGfELOFNnr = false;
      bool ndCrfXPZTd = false;
      bool fQeTmsRLqV = false;
      bool HENuMSAjYi = false;
      bool WoPVFjXzCE = false;
      bool dEzMClbMRS = false;
      bool wtWSjiPGfM = false;
      bool XfAjHqAIND = false;
      bool URJmqDFBra = false;
      string FsEmPIkqQa;
      string GJMcBTRLQi;
      string ihehpCEWXi;
      string pJparibEWo;
      string zbEdrjTSCZ;
      string kQMbCWOVwM;
      string ENSgkwTlkR;
      string rNnaiHdBpF;
      string ilUyyZwNXU;
      string UFHKkkIXru;
      string PhhjgWblrt;
      string sNfqdRsUiL;
      string AGNPxmFdoy;
      string zFItoAEjQa;
      string xKUdbHYQfT;
      string rmnguJTRmt;
      string RywtumFlBc;
      string MIEHNokjmp;
      string NnxVFLRazf;
      string flxVIzOZho;
      if(FsEmPIkqQa == PhhjgWblrt){CmOCGiifSF = true;}
      else if(PhhjgWblrt == FsEmPIkqQa){NZrhbtdTpi = true;}
      if(GJMcBTRLQi == sNfqdRsUiL){XjewgcAZnj = true;}
      else if(sNfqdRsUiL == GJMcBTRLQi){CGfELOFNnr = true;}
      if(ihehpCEWXi == AGNPxmFdoy){VdlVwaKizO = true;}
      else if(AGNPxmFdoy == ihehpCEWXi){ndCrfXPZTd = true;}
      if(pJparibEWo == zFItoAEjQa){aKCynaYuPW = true;}
      else if(zFItoAEjQa == pJparibEWo){fQeTmsRLqV = true;}
      if(zbEdrjTSCZ == xKUdbHYQfT){ckIsHwHAof = true;}
      else if(xKUdbHYQfT == zbEdrjTSCZ){HENuMSAjYi = true;}
      if(kQMbCWOVwM == rmnguJTRmt){znlxTXAsFe = true;}
      else if(rmnguJTRmt == kQMbCWOVwM){WoPVFjXzCE = true;}
      if(ENSgkwTlkR == RywtumFlBc){YzgDeNhgIG = true;}
      else if(RywtumFlBc == ENSgkwTlkR){dEzMClbMRS = true;}
      if(rNnaiHdBpF == MIEHNokjmp){DEJRHjUsNA = true;}
      if(ilUyyZwNXU == NnxVFLRazf){TJtSPlYEeP = true;}
      if(UFHKkkIXru == flxVIzOZho){ZfojxcDEOt = true;}
      while(MIEHNokjmp == rNnaiHdBpF){wtWSjiPGfM = true;}
      while(NnxVFLRazf == NnxVFLRazf){XfAjHqAIND = true;}
      while(flxVIzOZho == flxVIzOZho){URJmqDFBra = true;}
      if(CmOCGiifSF == true){CmOCGiifSF = false;}
      if(XjewgcAZnj == true){XjewgcAZnj = false;}
      if(VdlVwaKizO == true){VdlVwaKizO = false;}
      if(aKCynaYuPW == true){aKCynaYuPW = false;}
      if(ckIsHwHAof == true){ckIsHwHAof = false;}
      if(znlxTXAsFe == true){znlxTXAsFe = false;}
      if(YzgDeNhgIG == true){YzgDeNhgIG = false;}
      if(DEJRHjUsNA == true){DEJRHjUsNA = false;}
      if(TJtSPlYEeP == true){TJtSPlYEeP = false;}
      if(ZfojxcDEOt == true){ZfojxcDEOt = false;}
      if(NZrhbtdTpi == true){NZrhbtdTpi = false;}
      if(CGfELOFNnr == true){CGfELOFNnr = false;}
      if(ndCrfXPZTd == true){ndCrfXPZTd = false;}
      if(fQeTmsRLqV == true){fQeTmsRLqV = false;}
      if(HENuMSAjYi == true){HENuMSAjYi = false;}
      if(WoPVFjXzCE == true){WoPVFjXzCE = false;}
      if(dEzMClbMRS == true){dEzMClbMRS = false;}
      if(wtWSjiPGfM == true){wtWSjiPGfM = false;}
      if(XfAjHqAIND == true){XfAjHqAIND = false;}
      if(URJmqDFBra == true){URJmqDFBra = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTQIAZUECS
{ 
  void gthAfWwnEo()
  { 
      bool YyOhKLkzPI = false;
      bool VbbJKEFMkD = false;
      bool uEWCWVUPbW = false;
      bool ekgZuKBSCY = false;
      bool gDwyrqhFDU = false;
      bool onFwlTbLLn = false;
      bool qVWsdjuCNA = false;
      bool ClKMVqIYJf = false;
      bool mOLHhpfjmb = false;
      bool ipHNgKfCTI = false;
      bool ufqDRCdsZu = false;
      bool LCCeBbJPLn = false;
      bool ELOlRMdweL = false;
      bool LFEBkGXHoe = false;
      bool LmJrPfmbLF = false;
      bool BQqfDiQElF = false;
      bool YgNOiGxAtu = false;
      bool EBagbRCWWk = false;
      bool YBkZJtOYxB = false;
      bool oSViFeYtII = false;
      string CqXVfBFikk;
      string NgRDPLtSbD;
      string qBpDqZJnhf;
      string kBcpiDWozI;
      string seByJqlrDt;
      string VBxNQBBTeG;
      string qQBFAMEaUM;
      string nFTTKMzqsA;
      string mRknJiEPZg;
      string BCJrQcdwyx;
      string mKWpFPhcDE;
      string BKZdSZfMuR;
      string HnBmLkuaDg;
      string iDswMctths;
      string AaMUfpcfYp;
      string xQAfoyIieT;
      string UGZVVyRdQp;
      string fkeBQfbfHU;
      string IPBMjSCMGO;
      string TKPOYtBpzh;
      if(CqXVfBFikk == mKWpFPhcDE){YyOhKLkzPI = true;}
      else if(mKWpFPhcDE == CqXVfBFikk){ufqDRCdsZu = true;}
      if(NgRDPLtSbD == BKZdSZfMuR){VbbJKEFMkD = true;}
      else if(BKZdSZfMuR == NgRDPLtSbD){LCCeBbJPLn = true;}
      if(qBpDqZJnhf == HnBmLkuaDg){uEWCWVUPbW = true;}
      else if(HnBmLkuaDg == qBpDqZJnhf){ELOlRMdweL = true;}
      if(kBcpiDWozI == iDswMctths){ekgZuKBSCY = true;}
      else if(iDswMctths == kBcpiDWozI){LFEBkGXHoe = true;}
      if(seByJqlrDt == AaMUfpcfYp){gDwyrqhFDU = true;}
      else if(AaMUfpcfYp == seByJqlrDt){LmJrPfmbLF = true;}
      if(VBxNQBBTeG == xQAfoyIieT){onFwlTbLLn = true;}
      else if(xQAfoyIieT == VBxNQBBTeG){BQqfDiQElF = true;}
      if(qQBFAMEaUM == UGZVVyRdQp){qVWsdjuCNA = true;}
      else if(UGZVVyRdQp == qQBFAMEaUM){YgNOiGxAtu = true;}
      if(nFTTKMzqsA == fkeBQfbfHU){ClKMVqIYJf = true;}
      if(mRknJiEPZg == IPBMjSCMGO){mOLHhpfjmb = true;}
      if(BCJrQcdwyx == TKPOYtBpzh){ipHNgKfCTI = true;}
      while(fkeBQfbfHU == nFTTKMzqsA){EBagbRCWWk = true;}
      while(IPBMjSCMGO == IPBMjSCMGO){YBkZJtOYxB = true;}
      while(TKPOYtBpzh == TKPOYtBpzh){oSViFeYtII = true;}
      if(YyOhKLkzPI == true){YyOhKLkzPI = false;}
      if(VbbJKEFMkD == true){VbbJKEFMkD = false;}
      if(uEWCWVUPbW == true){uEWCWVUPbW = false;}
      if(ekgZuKBSCY == true){ekgZuKBSCY = false;}
      if(gDwyrqhFDU == true){gDwyrqhFDU = false;}
      if(onFwlTbLLn == true){onFwlTbLLn = false;}
      if(qVWsdjuCNA == true){qVWsdjuCNA = false;}
      if(ClKMVqIYJf == true){ClKMVqIYJf = false;}
      if(mOLHhpfjmb == true){mOLHhpfjmb = false;}
      if(ipHNgKfCTI == true){ipHNgKfCTI = false;}
      if(ufqDRCdsZu == true){ufqDRCdsZu = false;}
      if(LCCeBbJPLn == true){LCCeBbJPLn = false;}
      if(ELOlRMdweL == true){ELOlRMdweL = false;}
      if(LFEBkGXHoe == true){LFEBkGXHoe = false;}
      if(LmJrPfmbLF == true){LmJrPfmbLF = false;}
      if(BQqfDiQElF == true){BQqfDiQElF = false;}
      if(YgNOiGxAtu == true){YgNOiGxAtu = false;}
      if(EBagbRCWWk == true){EBagbRCWWk = false;}
      if(YBkZJtOYxB == true){YBkZJtOYxB = false;}
      if(oSViFeYtII == true){oSViFeYtII = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDSQRZIADH
{ 
  void xzlIrsecPa()
  { 
      bool ZmeFSxDMGo = false;
      bool IjBqCbYAIQ = false;
      bool hJSJymMtpC = false;
      bool CKqITqmoBw = false;
      bool lLUbyRhQBX = false;
      bool ZpUkZPUVHf = false;
      bool kJVDlxrsWK = false;
      bool ojyMeWoqLf = false;
      bool EusScLoFhE = false;
      bool WQhULcoQoA = false;
      bool YospiprIGD = false;
      bool adKaboPDaa = false;
      bool ImKSnXBcAB = false;
      bool gYBKGOBCil = false;
      bool TfyedsFGsV = false;
      bool MlpOqleaCK = false;
      bool nOHEVCbzUM = false;
      bool mNTnGbneot = false;
      bool RujdouhmSU = false;
      bool jazYxEXtIb = false;
      string xwwzxMNRcH;
      string AVDdHggOVZ;
      string ZwIaJFiOLm;
      string wBDpzUaFct;
      string gsermlsedp;
      string jGIHfAmVpq;
      string dzFoLzRMel;
      string GbkasfRQmW;
      string LDkUDoswJy;
      string gEOkPgmofn;
      string TfAqiIUgOA;
      string iVhSeZOjlW;
      string FVDgFBNALL;
      string sbkzDeDtlt;
      string TMgJPLWuFp;
      string RCDJhxcSkh;
      string tUVCHGkiPA;
      string WUyqCsosRt;
      string eSuUspXaQG;
      string BjIDAzqdCI;
      if(xwwzxMNRcH == TfAqiIUgOA){ZmeFSxDMGo = true;}
      else if(TfAqiIUgOA == xwwzxMNRcH){YospiprIGD = true;}
      if(AVDdHggOVZ == iVhSeZOjlW){IjBqCbYAIQ = true;}
      else if(iVhSeZOjlW == AVDdHggOVZ){adKaboPDaa = true;}
      if(ZwIaJFiOLm == FVDgFBNALL){hJSJymMtpC = true;}
      else if(FVDgFBNALL == ZwIaJFiOLm){ImKSnXBcAB = true;}
      if(wBDpzUaFct == sbkzDeDtlt){CKqITqmoBw = true;}
      else if(sbkzDeDtlt == wBDpzUaFct){gYBKGOBCil = true;}
      if(gsermlsedp == TMgJPLWuFp){lLUbyRhQBX = true;}
      else if(TMgJPLWuFp == gsermlsedp){TfyedsFGsV = true;}
      if(jGIHfAmVpq == RCDJhxcSkh){ZpUkZPUVHf = true;}
      else if(RCDJhxcSkh == jGIHfAmVpq){MlpOqleaCK = true;}
      if(dzFoLzRMel == tUVCHGkiPA){kJVDlxrsWK = true;}
      else if(tUVCHGkiPA == dzFoLzRMel){nOHEVCbzUM = true;}
      if(GbkasfRQmW == WUyqCsosRt){ojyMeWoqLf = true;}
      if(LDkUDoswJy == eSuUspXaQG){EusScLoFhE = true;}
      if(gEOkPgmofn == BjIDAzqdCI){WQhULcoQoA = true;}
      while(WUyqCsosRt == GbkasfRQmW){mNTnGbneot = true;}
      while(eSuUspXaQG == eSuUspXaQG){RujdouhmSU = true;}
      while(BjIDAzqdCI == BjIDAzqdCI){jazYxEXtIb = true;}
      if(ZmeFSxDMGo == true){ZmeFSxDMGo = false;}
      if(IjBqCbYAIQ == true){IjBqCbYAIQ = false;}
      if(hJSJymMtpC == true){hJSJymMtpC = false;}
      if(CKqITqmoBw == true){CKqITqmoBw = false;}
      if(lLUbyRhQBX == true){lLUbyRhQBX = false;}
      if(ZpUkZPUVHf == true){ZpUkZPUVHf = false;}
      if(kJVDlxrsWK == true){kJVDlxrsWK = false;}
      if(ojyMeWoqLf == true){ojyMeWoqLf = false;}
      if(EusScLoFhE == true){EusScLoFhE = false;}
      if(WQhULcoQoA == true){WQhULcoQoA = false;}
      if(YospiprIGD == true){YospiprIGD = false;}
      if(adKaboPDaa == true){adKaboPDaa = false;}
      if(ImKSnXBcAB == true){ImKSnXBcAB = false;}
      if(gYBKGOBCil == true){gYBKGOBCil = false;}
      if(TfyedsFGsV == true){TfyedsFGsV = false;}
      if(MlpOqleaCK == true){MlpOqleaCK = false;}
      if(nOHEVCbzUM == true){nOHEVCbzUM = false;}
      if(mNTnGbneot == true){mNTnGbneot = false;}
      if(RujdouhmSU == true){RujdouhmSU = false;}
      if(jazYxEXtIb == true){jazYxEXtIb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCZJYKERBM
{ 
  void YDVAdhQfOY()
  { 
      bool PKCLTdwzJD = false;
      bool kLjEGEMERF = false;
      bool xBmneZPXFQ = false;
      bool aHuCYpXnwP = false;
      bool MuXJEMBNna = false;
      bool uCrRpNXOgs = false;
      bool NYsrbcQgeQ = false;
      bool fXIBrCdciR = false;
      bool YBidVXPcML = false;
      bool SJHCBnBegb = false;
      bool uThXtWtpYn = false;
      bool jtfOULoOWE = false;
      bool NmUTyWQFzE = false;
      bool AywHVETLjy = false;
      bool dYEYaYdrho = false;
      bool ymIcOIzOZX = false;
      bool GnpUmlxXrP = false;
      bool rdeYZniwrZ = false;
      bool sXWKFNoSsN = false;
      bool FFlLqohjko = false;
      string dBVKCLIDwE;
      string wxJLhSTHbJ;
      string nsJgEGeSLy;
      string OyUblrxITg;
      string wdfRqURVXn;
      string yQJfzjrnFw;
      string forxpxchYo;
      string UKnuNKNqpj;
      string nIuWAxoobC;
      string AICXBGkhas;
      string qjxiTncNSo;
      string WAxVHWtVxs;
      string InFWoLHPtG;
      string YeQxrDLLCL;
      string TaVmfzKgPd;
      string MPkhjCeasH;
      string fMTLPqjAdD;
      string KhSlYgRSqo;
      string AaAPtJthMo;
      string YkSufHGKXn;
      if(dBVKCLIDwE == qjxiTncNSo){PKCLTdwzJD = true;}
      else if(qjxiTncNSo == dBVKCLIDwE){uThXtWtpYn = true;}
      if(wxJLhSTHbJ == WAxVHWtVxs){kLjEGEMERF = true;}
      else if(WAxVHWtVxs == wxJLhSTHbJ){jtfOULoOWE = true;}
      if(nsJgEGeSLy == InFWoLHPtG){xBmneZPXFQ = true;}
      else if(InFWoLHPtG == nsJgEGeSLy){NmUTyWQFzE = true;}
      if(OyUblrxITg == YeQxrDLLCL){aHuCYpXnwP = true;}
      else if(YeQxrDLLCL == OyUblrxITg){AywHVETLjy = true;}
      if(wdfRqURVXn == TaVmfzKgPd){MuXJEMBNna = true;}
      else if(TaVmfzKgPd == wdfRqURVXn){dYEYaYdrho = true;}
      if(yQJfzjrnFw == MPkhjCeasH){uCrRpNXOgs = true;}
      else if(MPkhjCeasH == yQJfzjrnFw){ymIcOIzOZX = true;}
      if(forxpxchYo == fMTLPqjAdD){NYsrbcQgeQ = true;}
      else if(fMTLPqjAdD == forxpxchYo){GnpUmlxXrP = true;}
      if(UKnuNKNqpj == KhSlYgRSqo){fXIBrCdciR = true;}
      if(nIuWAxoobC == AaAPtJthMo){YBidVXPcML = true;}
      if(AICXBGkhas == YkSufHGKXn){SJHCBnBegb = true;}
      while(KhSlYgRSqo == UKnuNKNqpj){rdeYZniwrZ = true;}
      while(AaAPtJthMo == AaAPtJthMo){sXWKFNoSsN = true;}
      while(YkSufHGKXn == YkSufHGKXn){FFlLqohjko = true;}
      if(PKCLTdwzJD == true){PKCLTdwzJD = false;}
      if(kLjEGEMERF == true){kLjEGEMERF = false;}
      if(xBmneZPXFQ == true){xBmneZPXFQ = false;}
      if(aHuCYpXnwP == true){aHuCYpXnwP = false;}
      if(MuXJEMBNna == true){MuXJEMBNna = false;}
      if(uCrRpNXOgs == true){uCrRpNXOgs = false;}
      if(NYsrbcQgeQ == true){NYsrbcQgeQ = false;}
      if(fXIBrCdciR == true){fXIBrCdciR = false;}
      if(YBidVXPcML == true){YBidVXPcML = false;}
      if(SJHCBnBegb == true){SJHCBnBegb = false;}
      if(uThXtWtpYn == true){uThXtWtpYn = false;}
      if(jtfOULoOWE == true){jtfOULoOWE = false;}
      if(NmUTyWQFzE == true){NmUTyWQFzE = false;}
      if(AywHVETLjy == true){AywHVETLjy = false;}
      if(dYEYaYdrho == true){dYEYaYdrho = false;}
      if(ymIcOIzOZX == true){ymIcOIzOZX = false;}
      if(GnpUmlxXrP == true){GnpUmlxXrP = false;}
      if(rdeYZniwrZ == true){rdeYZniwrZ = false;}
      if(sXWKFNoSsN == true){sXWKFNoSsN = false;}
      if(FFlLqohjko == true){FFlLqohjko = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESQMREEQJD
{ 
  void hNytIgxMEO()
  { 
      bool qKcSwzaJjC = false;
      bool EOcoEIjDXg = false;
      bool yoiySVwBGl = false;
      bool VcuWezzdXY = false;
      bool JCRXAeWUJD = false;
      bool bZXAABbdAa = false;
      bool DYCygbTGJF = false;
      bool JGeyXuXKyn = false;
      bool yaqCKuEuVd = false;
      bool WVcxVjASpY = false;
      bool LQKEtVtZbE = false;
      bool dQeLcbgznl = false;
      bool XXjfhnchcm = false;
      bool uEUZcgPmIo = false;
      bool BeSRAGpQTs = false;
      bool DAeEAmfeWG = false;
      bool rLwoJYwFiu = false;
      bool LtqzkrFSfb = false;
      bool xLOijtZPYo = false;
      bool BkQBwohdHa = false;
      string NNWRJnrfTN;
      string VseZPQItOS;
      string ahbCECpYJM;
      string TFJGnxcfll;
      string DJARUctOji;
      string VRopLflUNH;
      string xSVHsQiXlR;
      string nbHcPQgJga;
      string IboZqCPSuH;
      string LISenjnsYD;
      string sVcSusJMau;
      string ybmlzVduQp;
      string BQcdFfIcne;
      string cnjchlzWex;
      string rCrAIiUgfS;
      string GrbhCcryMP;
      string kgYwRKrJDM;
      string VGQSxzXcUW;
      string KbwUYjLCaE;
      string sAKOMLduhy;
      if(NNWRJnrfTN == sVcSusJMau){qKcSwzaJjC = true;}
      else if(sVcSusJMau == NNWRJnrfTN){LQKEtVtZbE = true;}
      if(VseZPQItOS == ybmlzVduQp){EOcoEIjDXg = true;}
      else if(ybmlzVduQp == VseZPQItOS){dQeLcbgznl = true;}
      if(ahbCECpYJM == BQcdFfIcne){yoiySVwBGl = true;}
      else if(BQcdFfIcne == ahbCECpYJM){XXjfhnchcm = true;}
      if(TFJGnxcfll == cnjchlzWex){VcuWezzdXY = true;}
      else if(cnjchlzWex == TFJGnxcfll){uEUZcgPmIo = true;}
      if(DJARUctOji == rCrAIiUgfS){JCRXAeWUJD = true;}
      else if(rCrAIiUgfS == DJARUctOji){BeSRAGpQTs = true;}
      if(VRopLflUNH == GrbhCcryMP){bZXAABbdAa = true;}
      else if(GrbhCcryMP == VRopLflUNH){DAeEAmfeWG = true;}
      if(xSVHsQiXlR == kgYwRKrJDM){DYCygbTGJF = true;}
      else if(kgYwRKrJDM == xSVHsQiXlR){rLwoJYwFiu = true;}
      if(nbHcPQgJga == VGQSxzXcUW){JGeyXuXKyn = true;}
      if(IboZqCPSuH == KbwUYjLCaE){yaqCKuEuVd = true;}
      if(LISenjnsYD == sAKOMLduhy){WVcxVjASpY = true;}
      while(VGQSxzXcUW == nbHcPQgJga){LtqzkrFSfb = true;}
      while(KbwUYjLCaE == KbwUYjLCaE){xLOijtZPYo = true;}
      while(sAKOMLduhy == sAKOMLduhy){BkQBwohdHa = true;}
      if(qKcSwzaJjC == true){qKcSwzaJjC = false;}
      if(EOcoEIjDXg == true){EOcoEIjDXg = false;}
      if(yoiySVwBGl == true){yoiySVwBGl = false;}
      if(VcuWezzdXY == true){VcuWezzdXY = false;}
      if(JCRXAeWUJD == true){JCRXAeWUJD = false;}
      if(bZXAABbdAa == true){bZXAABbdAa = false;}
      if(DYCygbTGJF == true){DYCygbTGJF = false;}
      if(JGeyXuXKyn == true){JGeyXuXKyn = false;}
      if(yaqCKuEuVd == true){yaqCKuEuVd = false;}
      if(WVcxVjASpY == true){WVcxVjASpY = false;}
      if(LQKEtVtZbE == true){LQKEtVtZbE = false;}
      if(dQeLcbgznl == true){dQeLcbgznl = false;}
      if(XXjfhnchcm == true){XXjfhnchcm = false;}
      if(uEUZcgPmIo == true){uEUZcgPmIo = false;}
      if(BeSRAGpQTs == true){BeSRAGpQTs = false;}
      if(DAeEAmfeWG == true){DAeEAmfeWG = false;}
      if(rLwoJYwFiu == true){rLwoJYwFiu = false;}
      if(LtqzkrFSfb == true){LtqzkrFSfb = false;}
      if(xLOijtZPYo == true){xLOijtZPYo = false;}
      if(BkQBwohdHa == true){BkQBwohdHa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFUGMUUKBL
{ 
  void zAXPnjGngJ()
  { 
      bool JpqEpqoMpc = false;
      bool FeyWWbwTMq = false;
      bool iBAOCiBhVu = false;
      bool tczWWqmFSr = false;
      bool owOjQLPzaI = false;
      bool JRcsjIocCH = false;
      bool pHqthceazf = false;
      bool opBTCllQyp = false;
      bool SBGMkczGmO = false;
      bool BJDKCgFTBm = false;
      bool fnAuTTPJqx = false;
      bool VYeLnnBdIF = false;
      bool cXnjdempRU = false;
      bool gSPKJdAKsR = false;
      bool MpPorceqWN = false;
      bool faKwKHAPQn = false;
      bool fZrVPDJUBK = false;
      bool npkprmIzrB = false;
      bool AuTDoGHTzB = false;
      bool dktElmxsYn = false;
      string XURzKLOsgn;
      string gfjWyXbRYu;
      string sLIItwPqNe;
      string uAqLqgxNMl;
      string ilSBjTgVRR;
      string aTMHfMLIFO;
      string uWeBrgoXfR;
      string aOFmLHsHYZ;
      string OtZuDbmife;
      string UnHxpMGQIC;
      string eIpAqMOZwX;
      string TEjfzBxjxP;
      string sFrBwlGHxz;
      string BbyVuGDZDq;
      string NNmHKPEbxn;
      string OVSsIYPoDF;
      string GGcwWqGNjs;
      string xXfGCfSkpg;
      string hdKIjeIFMV;
      string pOVykGkpkS;
      if(XURzKLOsgn == eIpAqMOZwX){JpqEpqoMpc = true;}
      else if(eIpAqMOZwX == XURzKLOsgn){fnAuTTPJqx = true;}
      if(gfjWyXbRYu == TEjfzBxjxP){FeyWWbwTMq = true;}
      else if(TEjfzBxjxP == gfjWyXbRYu){VYeLnnBdIF = true;}
      if(sLIItwPqNe == sFrBwlGHxz){iBAOCiBhVu = true;}
      else if(sFrBwlGHxz == sLIItwPqNe){cXnjdempRU = true;}
      if(uAqLqgxNMl == BbyVuGDZDq){tczWWqmFSr = true;}
      else if(BbyVuGDZDq == uAqLqgxNMl){gSPKJdAKsR = true;}
      if(ilSBjTgVRR == NNmHKPEbxn){owOjQLPzaI = true;}
      else if(NNmHKPEbxn == ilSBjTgVRR){MpPorceqWN = true;}
      if(aTMHfMLIFO == OVSsIYPoDF){JRcsjIocCH = true;}
      else if(OVSsIYPoDF == aTMHfMLIFO){faKwKHAPQn = true;}
      if(uWeBrgoXfR == GGcwWqGNjs){pHqthceazf = true;}
      else if(GGcwWqGNjs == uWeBrgoXfR){fZrVPDJUBK = true;}
      if(aOFmLHsHYZ == xXfGCfSkpg){opBTCllQyp = true;}
      if(OtZuDbmife == hdKIjeIFMV){SBGMkczGmO = true;}
      if(UnHxpMGQIC == pOVykGkpkS){BJDKCgFTBm = true;}
      while(xXfGCfSkpg == aOFmLHsHYZ){npkprmIzrB = true;}
      while(hdKIjeIFMV == hdKIjeIFMV){AuTDoGHTzB = true;}
      while(pOVykGkpkS == pOVykGkpkS){dktElmxsYn = true;}
      if(JpqEpqoMpc == true){JpqEpqoMpc = false;}
      if(FeyWWbwTMq == true){FeyWWbwTMq = false;}
      if(iBAOCiBhVu == true){iBAOCiBhVu = false;}
      if(tczWWqmFSr == true){tczWWqmFSr = false;}
      if(owOjQLPzaI == true){owOjQLPzaI = false;}
      if(JRcsjIocCH == true){JRcsjIocCH = false;}
      if(pHqthceazf == true){pHqthceazf = false;}
      if(opBTCllQyp == true){opBTCllQyp = false;}
      if(SBGMkczGmO == true){SBGMkczGmO = false;}
      if(BJDKCgFTBm == true){BJDKCgFTBm = false;}
      if(fnAuTTPJqx == true){fnAuTTPJqx = false;}
      if(VYeLnnBdIF == true){VYeLnnBdIF = false;}
      if(cXnjdempRU == true){cXnjdempRU = false;}
      if(gSPKJdAKsR == true){gSPKJdAKsR = false;}
      if(MpPorceqWN == true){MpPorceqWN = false;}
      if(faKwKHAPQn == true){faKwKHAPQn = false;}
      if(fZrVPDJUBK == true){fZrVPDJUBK = false;}
      if(npkprmIzrB == true){npkprmIzrB = false;}
      if(AuTDoGHTzB == true){AuTDoGHTzB = false;}
      if(dktElmxsYn == true){dktElmxsYn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YETCRGVHIV
{ 
  void ONcchrDeaT()
  { 
      bool pLFAYXHxto = false;
      bool AkBMfPPFAP = false;
      bool PHEscCVIGG = false;
      bool siWaVpBeDx = false;
      bool ghnHaFdCKA = false;
      bool dIjZZhHLWW = false;
      bool CypmwQNapp = false;
      bool OkBChhSwSW = false;
      bool XSyGcjywAm = false;
      bool ioHguirBLK = false;
      bool qDLTlrHhrr = false;
      bool PKszyiAjKL = false;
      bool RQZDHYdTHz = false;
      bool pRjIfTHdTj = false;
      bool cQEIXXuHiL = false;
      bool hHpzrZdIMM = false;
      bool OmarBxakTd = false;
      bool bVPZiBLQei = false;
      bool dVjuQhajPF = false;
      bool pyQHVopMGZ = false;
      string oPEkRkosee;
      string kEcojXeMcR;
      string EPcOZKdOwZ;
      string FQTXFoyDjy;
      string GcjLUgMGLX;
      string gVyLbZmoKG;
      string GaxEZUjFjt;
      string ZabdKaeQss;
      string xWDXsiRIwf;
      string CJscrfeflA;
      string wHWQyFtUAA;
      string tVuRJiWYLp;
      string DbIDrPhyld;
      string uzeswoAmYn;
      string owHukgNaTI;
      string IGUuwUyTXi;
      string WuiVEupBUT;
      string ijzXBGUNRL;
      string CHecVoeixb;
      string qfOpQtNkpp;
      if(oPEkRkosee == wHWQyFtUAA){pLFAYXHxto = true;}
      else if(wHWQyFtUAA == oPEkRkosee){qDLTlrHhrr = true;}
      if(kEcojXeMcR == tVuRJiWYLp){AkBMfPPFAP = true;}
      else if(tVuRJiWYLp == kEcojXeMcR){PKszyiAjKL = true;}
      if(EPcOZKdOwZ == DbIDrPhyld){PHEscCVIGG = true;}
      else if(DbIDrPhyld == EPcOZKdOwZ){RQZDHYdTHz = true;}
      if(FQTXFoyDjy == uzeswoAmYn){siWaVpBeDx = true;}
      else if(uzeswoAmYn == FQTXFoyDjy){pRjIfTHdTj = true;}
      if(GcjLUgMGLX == owHukgNaTI){ghnHaFdCKA = true;}
      else if(owHukgNaTI == GcjLUgMGLX){cQEIXXuHiL = true;}
      if(gVyLbZmoKG == IGUuwUyTXi){dIjZZhHLWW = true;}
      else if(IGUuwUyTXi == gVyLbZmoKG){hHpzrZdIMM = true;}
      if(GaxEZUjFjt == WuiVEupBUT){CypmwQNapp = true;}
      else if(WuiVEupBUT == GaxEZUjFjt){OmarBxakTd = true;}
      if(ZabdKaeQss == ijzXBGUNRL){OkBChhSwSW = true;}
      if(xWDXsiRIwf == CHecVoeixb){XSyGcjywAm = true;}
      if(CJscrfeflA == qfOpQtNkpp){ioHguirBLK = true;}
      while(ijzXBGUNRL == ZabdKaeQss){bVPZiBLQei = true;}
      while(CHecVoeixb == CHecVoeixb){dVjuQhajPF = true;}
      while(qfOpQtNkpp == qfOpQtNkpp){pyQHVopMGZ = true;}
      if(pLFAYXHxto == true){pLFAYXHxto = false;}
      if(AkBMfPPFAP == true){AkBMfPPFAP = false;}
      if(PHEscCVIGG == true){PHEscCVIGG = false;}
      if(siWaVpBeDx == true){siWaVpBeDx = false;}
      if(ghnHaFdCKA == true){ghnHaFdCKA = false;}
      if(dIjZZhHLWW == true){dIjZZhHLWW = false;}
      if(CypmwQNapp == true){CypmwQNapp = false;}
      if(OkBChhSwSW == true){OkBChhSwSW = false;}
      if(XSyGcjywAm == true){XSyGcjywAm = false;}
      if(ioHguirBLK == true){ioHguirBLK = false;}
      if(qDLTlrHhrr == true){qDLTlrHhrr = false;}
      if(PKszyiAjKL == true){PKszyiAjKL = false;}
      if(RQZDHYdTHz == true){RQZDHYdTHz = false;}
      if(pRjIfTHdTj == true){pRjIfTHdTj = false;}
      if(cQEIXXuHiL == true){cQEIXXuHiL = false;}
      if(hHpzrZdIMM == true){hHpzrZdIMM = false;}
      if(OmarBxakTd == true){OmarBxakTd = false;}
      if(bVPZiBLQei == true){bVPZiBLQei = false;}
      if(dVjuQhajPF == true){dVjuQhajPF = false;}
      if(pyQHVopMGZ == true){pyQHVopMGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBUFVSJPMY
{ 
  void InYcBLrTdH()
  { 
      bool IldfrGdBrH = false;
      bool mSErBUNcTh = false;
      bool mSPtSzESiO = false;
      bool HxgDtpGVxX = false;
      bool YkuXsIoVfI = false;
      bool RAQlCoVjMr = false;
      bool CKRcAokBxK = false;
      bool NrfwICXqAJ = false;
      bool JhmaxHfuAE = false;
      bool TWIFUOSRXD = false;
      bool XnXUtYUUcz = false;
      bool ReiDhTXqfs = false;
      bool IpAspqiZat = false;
      bool jFTxlVJRgX = false;
      bool lLRBmonFXA = false;
      bool pbletgmedD = false;
      bool pushPMKkQL = false;
      bool KGJIGxXzFB = false;
      bool CdCZEHSnDF = false;
      bool hemchqRjlZ = false;
      string WsZCdoJJLA;
      string LAiYtmSNIQ;
      string PmJCiUEEAo;
      string VlwGZeZzWI;
      string IweHBrBFdB;
      string NhtKjiiWSI;
      string jEIVdZEbzO;
      string NTpAISICBp;
      string TyZyanqlVp;
      string uDfOXDmIcb;
      string nYGPnsrtCQ;
      string ZfUbnldJtp;
      string hRFISKnbbE;
      string fAZZCtrKKh;
      string uwiFPPhDZl;
      string ZcNlsVSxwd;
      string FPSykZGuZt;
      string tSzMtkiAsD;
      string bjBodClmff;
      string atOgcfdkTp;
      if(WsZCdoJJLA == nYGPnsrtCQ){IldfrGdBrH = true;}
      else if(nYGPnsrtCQ == WsZCdoJJLA){XnXUtYUUcz = true;}
      if(LAiYtmSNIQ == ZfUbnldJtp){mSErBUNcTh = true;}
      else if(ZfUbnldJtp == LAiYtmSNIQ){ReiDhTXqfs = true;}
      if(PmJCiUEEAo == hRFISKnbbE){mSPtSzESiO = true;}
      else if(hRFISKnbbE == PmJCiUEEAo){IpAspqiZat = true;}
      if(VlwGZeZzWI == fAZZCtrKKh){HxgDtpGVxX = true;}
      else if(fAZZCtrKKh == VlwGZeZzWI){jFTxlVJRgX = true;}
      if(IweHBrBFdB == uwiFPPhDZl){YkuXsIoVfI = true;}
      else if(uwiFPPhDZl == IweHBrBFdB){lLRBmonFXA = true;}
      if(NhtKjiiWSI == ZcNlsVSxwd){RAQlCoVjMr = true;}
      else if(ZcNlsVSxwd == NhtKjiiWSI){pbletgmedD = true;}
      if(jEIVdZEbzO == FPSykZGuZt){CKRcAokBxK = true;}
      else if(FPSykZGuZt == jEIVdZEbzO){pushPMKkQL = true;}
      if(NTpAISICBp == tSzMtkiAsD){NrfwICXqAJ = true;}
      if(TyZyanqlVp == bjBodClmff){JhmaxHfuAE = true;}
      if(uDfOXDmIcb == atOgcfdkTp){TWIFUOSRXD = true;}
      while(tSzMtkiAsD == NTpAISICBp){KGJIGxXzFB = true;}
      while(bjBodClmff == bjBodClmff){CdCZEHSnDF = true;}
      while(atOgcfdkTp == atOgcfdkTp){hemchqRjlZ = true;}
      if(IldfrGdBrH == true){IldfrGdBrH = false;}
      if(mSErBUNcTh == true){mSErBUNcTh = false;}
      if(mSPtSzESiO == true){mSPtSzESiO = false;}
      if(HxgDtpGVxX == true){HxgDtpGVxX = false;}
      if(YkuXsIoVfI == true){YkuXsIoVfI = false;}
      if(RAQlCoVjMr == true){RAQlCoVjMr = false;}
      if(CKRcAokBxK == true){CKRcAokBxK = false;}
      if(NrfwICXqAJ == true){NrfwICXqAJ = false;}
      if(JhmaxHfuAE == true){JhmaxHfuAE = false;}
      if(TWIFUOSRXD == true){TWIFUOSRXD = false;}
      if(XnXUtYUUcz == true){XnXUtYUUcz = false;}
      if(ReiDhTXqfs == true){ReiDhTXqfs = false;}
      if(IpAspqiZat == true){IpAspqiZat = false;}
      if(jFTxlVJRgX == true){jFTxlVJRgX = false;}
      if(lLRBmonFXA == true){lLRBmonFXA = false;}
      if(pbletgmedD == true){pbletgmedD = false;}
      if(pushPMKkQL == true){pushPMKkQL = false;}
      if(KGJIGxXzFB == true){KGJIGxXzFB = false;}
      if(CdCZEHSnDF == true){CdCZEHSnDF = false;}
      if(hemchqRjlZ == true){hemchqRjlZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUOACENCIV
{ 
  void HMBKYMCLws()
  { 
      bool FEfGApMoVh = false;
      bool ExMrUVWGFX = false;
      bool PbFAkkSiuW = false;
      bool ZuAjtLAWLZ = false;
      bool DLrbHxNnSO = false;
      bool onmqTdyfUO = false;
      bool WdtyIJxcxJ = false;
      bool UAtfUDidsn = false;
      bool XeQfhkHIQQ = false;
      bool NUBwCZQsTx = false;
      bool zkqJsnsHWP = false;
      bool tUmfqrMNQW = false;
      bool CnMfuAyyct = false;
      bool lpKunlmHms = false;
      bool rzkAWsgUFK = false;
      bool NCcwtLXLNr = false;
      bool pudccDKqrE = false;
      bool EEaWeCDLJC = false;
      bool ScsSgiNNAc = false;
      bool ObttDwUIXS = false;
      string cXFRTtkuMQ;
      string tnjxeNQyOW;
      string GeubxoSzCd;
      string oEqTmfcfFI;
      string AYVbbtyKmG;
      string NKyzXybdUe;
      string bkrhaowPJz;
      string jkrFVhJTAC;
      string pHMuPeGruo;
      string DzKagOgmAl;
      string xhAnWcRrcp;
      string nIdRnTYwRu;
      string iDUTukZQYG;
      string BWSNFHHYYm;
      string MNPEBuUsmM;
      string pjUEDsNfrk;
      string CASVoRoQMf;
      string MzWeiUnPSA;
      string PgdMQQBNKL;
      string tafmjLusPi;
      if(cXFRTtkuMQ == xhAnWcRrcp){FEfGApMoVh = true;}
      else if(xhAnWcRrcp == cXFRTtkuMQ){zkqJsnsHWP = true;}
      if(tnjxeNQyOW == nIdRnTYwRu){ExMrUVWGFX = true;}
      else if(nIdRnTYwRu == tnjxeNQyOW){tUmfqrMNQW = true;}
      if(GeubxoSzCd == iDUTukZQYG){PbFAkkSiuW = true;}
      else if(iDUTukZQYG == GeubxoSzCd){CnMfuAyyct = true;}
      if(oEqTmfcfFI == BWSNFHHYYm){ZuAjtLAWLZ = true;}
      else if(BWSNFHHYYm == oEqTmfcfFI){lpKunlmHms = true;}
      if(AYVbbtyKmG == MNPEBuUsmM){DLrbHxNnSO = true;}
      else if(MNPEBuUsmM == AYVbbtyKmG){rzkAWsgUFK = true;}
      if(NKyzXybdUe == pjUEDsNfrk){onmqTdyfUO = true;}
      else if(pjUEDsNfrk == NKyzXybdUe){NCcwtLXLNr = true;}
      if(bkrhaowPJz == CASVoRoQMf){WdtyIJxcxJ = true;}
      else if(CASVoRoQMf == bkrhaowPJz){pudccDKqrE = true;}
      if(jkrFVhJTAC == MzWeiUnPSA){UAtfUDidsn = true;}
      if(pHMuPeGruo == PgdMQQBNKL){XeQfhkHIQQ = true;}
      if(DzKagOgmAl == tafmjLusPi){NUBwCZQsTx = true;}
      while(MzWeiUnPSA == jkrFVhJTAC){EEaWeCDLJC = true;}
      while(PgdMQQBNKL == PgdMQQBNKL){ScsSgiNNAc = true;}
      while(tafmjLusPi == tafmjLusPi){ObttDwUIXS = true;}
      if(FEfGApMoVh == true){FEfGApMoVh = false;}
      if(ExMrUVWGFX == true){ExMrUVWGFX = false;}
      if(PbFAkkSiuW == true){PbFAkkSiuW = false;}
      if(ZuAjtLAWLZ == true){ZuAjtLAWLZ = false;}
      if(DLrbHxNnSO == true){DLrbHxNnSO = false;}
      if(onmqTdyfUO == true){onmqTdyfUO = false;}
      if(WdtyIJxcxJ == true){WdtyIJxcxJ = false;}
      if(UAtfUDidsn == true){UAtfUDidsn = false;}
      if(XeQfhkHIQQ == true){XeQfhkHIQQ = false;}
      if(NUBwCZQsTx == true){NUBwCZQsTx = false;}
      if(zkqJsnsHWP == true){zkqJsnsHWP = false;}
      if(tUmfqrMNQW == true){tUmfqrMNQW = false;}
      if(CnMfuAyyct == true){CnMfuAyyct = false;}
      if(lpKunlmHms == true){lpKunlmHms = false;}
      if(rzkAWsgUFK == true){rzkAWsgUFK = false;}
      if(NCcwtLXLNr == true){NCcwtLXLNr = false;}
      if(pudccDKqrE == true){pudccDKqrE = false;}
      if(EEaWeCDLJC == true){EEaWeCDLJC = false;}
      if(ScsSgiNNAc == true){ScsSgiNNAc = false;}
      if(ObttDwUIXS == true){ObttDwUIXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRDALKYAHT
{ 
  void yAliqmDEBf()
  { 
      bool HxbhjnbuTr = false;
      bool rKawiOBeIU = false;
      bool JGqnMnZXmY = false;
      bool pRaLdtnGoB = false;
      bool eYQohouVoy = false;
      bool LuTPEBFnVw = false;
      bool NDHuBaiPSo = false;
      bool ZtoHpjpCFX = false;
      bool sEioMtxLGb = false;
      bool nAksnaRUmH = false;
      bool GeCzXRGMYT = false;
      bool LDhxDIUShG = false;
      bool cWIpAZIwSO = false;
      bool SUOyRNCiQu = false;
      bool nklmQkSmpe = false;
      bool GymfdiVLyy = false;
      bool IJsJAqojfo = false;
      bool GkClSqjVZP = false;
      bool HUGnIUghTh = false;
      bool qpkSmerclZ = false;
      string WkQALdRLfy;
      string ZgdlZACwwg;
      string GXMDzJHFbD;
      string ZZNhjGAWfz;
      string kFSWGbqSln;
      string UrVQKzYNAB;
      string VMjcYASwBS;
      string AePxuBFoxW;
      string RnTmigDxWk;
      string hlVecYUoyF;
      string IuQSnobYUJ;
      string siQdihrwtq;
      string wVYQkNJkTV;
      string fPqqNVWAzs;
      string EebNqzVruu;
      string fYuGJmWAha;
      string fqEzcdqYPM;
      string KrwAlQtLYk;
      string qQoYpHTkga;
      string zWRYNNacjN;
      if(WkQALdRLfy == IuQSnobYUJ){HxbhjnbuTr = true;}
      else if(IuQSnobYUJ == WkQALdRLfy){GeCzXRGMYT = true;}
      if(ZgdlZACwwg == siQdihrwtq){rKawiOBeIU = true;}
      else if(siQdihrwtq == ZgdlZACwwg){LDhxDIUShG = true;}
      if(GXMDzJHFbD == wVYQkNJkTV){JGqnMnZXmY = true;}
      else if(wVYQkNJkTV == GXMDzJHFbD){cWIpAZIwSO = true;}
      if(ZZNhjGAWfz == fPqqNVWAzs){pRaLdtnGoB = true;}
      else if(fPqqNVWAzs == ZZNhjGAWfz){SUOyRNCiQu = true;}
      if(kFSWGbqSln == EebNqzVruu){eYQohouVoy = true;}
      else if(EebNqzVruu == kFSWGbqSln){nklmQkSmpe = true;}
      if(UrVQKzYNAB == fYuGJmWAha){LuTPEBFnVw = true;}
      else if(fYuGJmWAha == UrVQKzYNAB){GymfdiVLyy = true;}
      if(VMjcYASwBS == fqEzcdqYPM){NDHuBaiPSo = true;}
      else if(fqEzcdqYPM == VMjcYASwBS){IJsJAqojfo = true;}
      if(AePxuBFoxW == KrwAlQtLYk){ZtoHpjpCFX = true;}
      if(RnTmigDxWk == qQoYpHTkga){sEioMtxLGb = true;}
      if(hlVecYUoyF == zWRYNNacjN){nAksnaRUmH = true;}
      while(KrwAlQtLYk == AePxuBFoxW){GkClSqjVZP = true;}
      while(qQoYpHTkga == qQoYpHTkga){HUGnIUghTh = true;}
      while(zWRYNNacjN == zWRYNNacjN){qpkSmerclZ = true;}
      if(HxbhjnbuTr == true){HxbhjnbuTr = false;}
      if(rKawiOBeIU == true){rKawiOBeIU = false;}
      if(JGqnMnZXmY == true){JGqnMnZXmY = false;}
      if(pRaLdtnGoB == true){pRaLdtnGoB = false;}
      if(eYQohouVoy == true){eYQohouVoy = false;}
      if(LuTPEBFnVw == true){LuTPEBFnVw = false;}
      if(NDHuBaiPSo == true){NDHuBaiPSo = false;}
      if(ZtoHpjpCFX == true){ZtoHpjpCFX = false;}
      if(sEioMtxLGb == true){sEioMtxLGb = false;}
      if(nAksnaRUmH == true){nAksnaRUmH = false;}
      if(GeCzXRGMYT == true){GeCzXRGMYT = false;}
      if(LDhxDIUShG == true){LDhxDIUShG = false;}
      if(cWIpAZIwSO == true){cWIpAZIwSO = false;}
      if(SUOyRNCiQu == true){SUOyRNCiQu = false;}
      if(nklmQkSmpe == true){nklmQkSmpe = false;}
      if(GymfdiVLyy == true){GymfdiVLyy = false;}
      if(IJsJAqojfo == true){IJsJAqojfo = false;}
      if(GkClSqjVZP == true){GkClSqjVZP = false;}
      if(HUGnIUghTh == true){HUGnIUghTh = false;}
      if(qpkSmerclZ == true){qpkSmerclZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CXCVRIPGTP
{ 
  void LVDbIZGsuA()
  { 
      bool zzpPoGbPQA = false;
      bool HbUCWoexpV = false;
      bool JLJCEnjGIL = false;
      bool gOatLsqJBs = false;
      bool gcLQUVzyzz = false;
      bool WDArdnonLB = false;
      bool WVGFTrAaqd = false;
      bool xVuwnfzshh = false;
      bool nlGIodOhQX = false;
      bool DDyAWLVGxb = false;
      bool UYHVBAHEEx = false;
      bool nwGcMjOyQp = false;
      bool dSKTZtXtYc = false;
      bool JsuFNPejGn = false;
      bool VJcSiGwUnm = false;
      bool wXpHyBNmuG = false;
      bool cMebmuAAPx = false;
      bool FerbTTorjT = false;
      bool yCGlflDnGL = false;
      bool BqozLIeBem = false;
      string WegKGVpKrr;
      string QtaxUCnijA;
      string lobBzcpSZz;
      string VYmJdlgyKL;
      string PEOVxIQssE;
      string OTDUYgCeKc;
      string eXksWrGRTh;
      string VpXXjgZGEq;
      string MxYVjCVSjw;
      string jBnggqTUyE;
      string ByZLiYufjq;
      string HwaTPgzPIT;
      string WnhWyTBpps;
      string NEHzoOXNlL;
      string GohromaUQz;
      string rEMehNQCMP;
      string WEoqdCnadB;
      string JkcxNgGogK;
      string rgYqAIrcRb;
      string xUAWoBAqOm;
      if(WegKGVpKrr == ByZLiYufjq){zzpPoGbPQA = true;}
      else if(ByZLiYufjq == WegKGVpKrr){UYHVBAHEEx = true;}
      if(QtaxUCnijA == HwaTPgzPIT){HbUCWoexpV = true;}
      else if(HwaTPgzPIT == QtaxUCnijA){nwGcMjOyQp = true;}
      if(lobBzcpSZz == WnhWyTBpps){JLJCEnjGIL = true;}
      else if(WnhWyTBpps == lobBzcpSZz){dSKTZtXtYc = true;}
      if(VYmJdlgyKL == NEHzoOXNlL){gOatLsqJBs = true;}
      else if(NEHzoOXNlL == VYmJdlgyKL){JsuFNPejGn = true;}
      if(PEOVxIQssE == GohromaUQz){gcLQUVzyzz = true;}
      else if(GohromaUQz == PEOVxIQssE){VJcSiGwUnm = true;}
      if(OTDUYgCeKc == rEMehNQCMP){WDArdnonLB = true;}
      else if(rEMehNQCMP == OTDUYgCeKc){wXpHyBNmuG = true;}
      if(eXksWrGRTh == WEoqdCnadB){WVGFTrAaqd = true;}
      else if(WEoqdCnadB == eXksWrGRTh){cMebmuAAPx = true;}
      if(VpXXjgZGEq == JkcxNgGogK){xVuwnfzshh = true;}
      if(MxYVjCVSjw == rgYqAIrcRb){nlGIodOhQX = true;}
      if(jBnggqTUyE == xUAWoBAqOm){DDyAWLVGxb = true;}
      while(JkcxNgGogK == VpXXjgZGEq){FerbTTorjT = true;}
      while(rgYqAIrcRb == rgYqAIrcRb){yCGlflDnGL = true;}
      while(xUAWoBAqOm == xUAWoBAqOm){BqozLIeBem = true;}
      if(zzpPoGbPQA == true){zzpPoGbPQA = false;}
      if(HbUCWoexpV == true){HbUCWoexpV = false;}
      if(JLJCEnjGIL == true){JLJCEnjGIL = false;}
      if(gOatLsqJBs == true){gOatLsqJBs = false;}
      if(gcLQUVzyzz == true){gcLQUVzyzz = false;}
      if(WDArdnonLB == true){WDArdnonLB = false;}
      if(WVGFTrAaqd == true){WVGFTrAaqd = false;}
      if(xVuwnfzshh == true){xVuwnfzshh = false;}
      if(nlGIodOhQX == true){nlGIodOhQX = false;}
      if(DDyAWLVGxb == true){DDyAWLVGxb = false;}
      if(UYHVBAHEEx == true){UYHVBAHEEx = false;}
      if(nwGcMjOyQp == true){nwGcMjOyQp = false;}
      if(dSKTZtXtYc == true){dSKTZtXtYc = false;}
      if(JsuFNPejGn == true){JsuFNPejGn = false;}
      if(VJcSiGwUnm == true){VJcSiGwUnm = false;}
      if(wXpHyBNmuG == true){wXpHyBNmuG = false;}
      if(cMebmuAAPx == true){cMebmuAAPx = false;}
      if(FerbTTorjT == true){FerbTTorjT = false;}
      if(yCGlflDnGL == true){yCGlflDnGL = false;}
      if(BqozLIeBem == true){BqozLIeBem = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWEDBTDRBJ
{ 
  void mZtzlaCLNk()
  { 
      bool AhdAnwZTTf = false;
      bool yPiQxyWYCm = false;
      bool FCfkhuOuQH = false;
      bool UwRUYLITAe = false;
      bool TrfQkNdQRE = false;
      bool idTzuxCsSr = false;
      bool gdDMLByOqk = false;
      bool oDYXTMVPzU = false;
      bool RxdMXpcRYb = false;
      bool JPAHyooTEj = false;
      bool OOZgOfEwfh = false;
      bool amsyajApnU = false;
      bool XfpPbZDRZd = false;
      bool XBKPFCXwyr = false;
      bool lfkqAVWBfO = false;
      bool oyejLhYJFn = false;
      bool bmWCKYccsY = false;
      bool LDrwhruyPF = false;
      bool CBkLnYVZDW = false;
      bool cNqJPyJifa = false;
      string gYUJqekIPh;
      string uCZjWCoWhG;
      string zOJyypmapt;
      string xkfVFEJgVS;
      string YTRfDJyYjn;
      string gZRfpRPWLA;
      string qKSVjJVEdR;
      string rIBPhexdto;
      string rOpCMWTAen;
      string omVUbNBwut;
      string mtuSwYYCyK;
      string TlcVIcUQIM;
      string pVYpcElfmT;
      string dBhABySXGn;
      string yRBTTDKzLy;
      string rjnhERUFpq;
      string lrOdgSDbUK;
      string JwKTNXTEVY;
      string tmUoasMAwi;
      string cNhOCGDWmB;
      if(gYUJqekIPh == mtuSwYYCyK){AhdAnwZTTf = true;}
      else if(mtuSwYYCyK == gYUJqekIPh){OOZgOfEwfh = true;}
      if(uCZjWCoWhG == TlcVIcUQIM){yPiQxyWYCm = true;}
      else if(TlcVIcUQIM == uCZjWCoWhG){amsyajApnU = true;}
      if(zOJyypmapt == pVYpcElfmT){FCfkhuOuQH = true;}
      else if(pVYpcElfmT == zOJyypmapt){XfpPbZDRZd = true;}
      if(xkfVFEJgVS == dBhABySXGn){UwRUYLITAe = true;}
      else if(dBhABySXGn == xkfVFEJgVS){XBKPFCXwyr = true;}
      if(YTRfDJyYjn == yRBTTDKzLy){TrfQkNdQRE = true;}
      else if(yRBTTDKzLy == YTRfDJyYjn){lfkqAVWBfO = true;}
      if(gZRfpRPWLA == rjnhERUFpq){idTzuxCsSr = true;}
      else if(rjnhERUFpq == gZRfpRPWLA){oyejLhYJFn = true;}
      if(qKSVjJVEdR == lrOdgSDbUK){gdDMLByOqk = true;}
      else if(lrOdgSDbUK == qKSVjJVEdR){bmWCKYccsY = true;}
      if(rIBPhexdto == JwKTNXTEVY){oDYXTMVPzU = true;}
      if(rOpCMWTAen == tmUoasMAwi){RxdMXpcRYb = true;}
      if(omVUbNBwut == cNhOCGDWmB){JPAHyooTEj = true;}
      while(JwKTNXTEVY == rIBPhexdto){LDrwhruyPF = true;}
      while(tmUoasMAwi == tmUoasMAwi){CBkLnYVZDW = true;}
      while(cNhOCGDWmB == cNhOCGDWmB){cNqJPyJifa = true;}
      if(AhdAnwZTTf == true){AhdAnwZTTf = false;}
      if(yPiQxyWYCm == true){yPiQxyWYCm = false;}
      if(FCfkhuOuQH == true){FCfkhuOuQH = false;}
      if(UwRUYLITAe == true){UwRUYLITAe = false;}
      if(TrfQkNdQRE == true){TrfQkNdQRE = false;}
      if(idTzuxCsSr == true){idTzuxCsSr = false;}
      if(gdDMLByOqk == true){gdDMLByOqk = false;}
      if(oDYXTMVPzU == true){oDYXTMVPzU = false;}
      if(RxdMXpcRYb == true){RxdMXpcRYb = false;}
      if(JPAHyooTEj == true){JPAHyooTEj = false;}
      if(OOZgOfEwfh == true){OOZgOfEwfh = false;}
      if(amsyajApnU == true){amsyajApnU = false;}
      if(XfpPbZDRZd == true){XfpPbZDRZd = false;}
      if(XBKPFCXwyr == true){XBKPFCXwyr = false;}
      if(lfkqAVWBfO == true){lfkqAVWBfO = false;}
      if(oyejLhYJFn == true){oyejLhYJFn = false;}
      if(bmWCKYccsY == true){bmWCKYccsY = false;}
      if(LDrwhruyPF == true){LDrwhruyPF = false;}
      if(CBkLnYVZDW == true){CBkLnYVZDW = false;}
      if(cNqJPyJifa == true){cNqJPyJifa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPLSXEHEQN
{ 
  void OcVgpAEGzH()
  { 
      bool YKHKDSkbEV = false;
      bool ttMysXFjOB = false;
      bool YBmmqkfAlY = false;
      bool lneSYXDWmG = false;
      bool eEEuIHzQVl = false;
      bool cRxpQWWUTR = false;
      bool mkpejFOsZV = false;
      bool ThwIWTxrei = false;
      bool kOdzwUpoCB = false;
      bool BiCUTsNYLC = false;
      bool sGqARtUoTw = false;
      bool ZepjgXHpiP = false;
      bool OZqXUjfboc = false;
      bool GXgbpeXdhC = false;
      bool zBUFaVsRmu = false;
      bool lXpunSOSeg = false;
      bool NsAppCxNtC = false;
      bool zcHgPMEkxy = false;
      bool qNnsqhgknW = false;
      bool PFyAnGBePX = false;
      string bxUfVITKDp;
      string lbceybGzdZ;
      string GDMkEqbVla;
      string VdECazgLwJ;
      string TfnGiPYZdU;
      string nbkfJXjjae;
      string fyXbUIWZEy;
      string utDTGZPFCo;
      string RCqRmsrYsC;
      string PxjQdUHLlZ;
      string ryVfZsYQZi;
      string IeglMcGGoa;
      string PygBiyJlpl;
      string RDTbwTfLqs;
      string UbzJtjPyEA;
      string NBWKKsRTwb;
      string jmZmREKFps;
      string xuPuGnzWHy;
      string hLhpYQfIRC;
      string CMOPJhBLro;
      if(bxUfVITKDp == ryVfZsYQZi){YKHKDSkbEV = true;}
      else if(ryVfZsYQZi == bxUfVITKDp){sGqARtUoTw = true;}
      if(lbceybGzdZ == IeglMcGGoa){ttMysXFjOB = true;}
      else if(IeglMcGGoa == lbceybGzdZ){ZepjgXHpiP = true;}
      if(GDMkEqbVla == PygBiyJlpl){YBmmqkfAlY = true;}
      else if(PygBiyJlpl == GDMkEqbVla){OZqXUjfboc = true;}
      if(VdECazgLwJ == RDTbwTfLqs){lneSYXDWmG = true;}
      else if(RDTbwTfLqs == VdECazgLwJ){GXgbpeXdhC = true;}
      if(TfnGiPYZdU == UbzJtjPyEA){eEEuIHzQVl = true;}
      else if(UbzJtjPyEA == TfnGiPYZdU){zBUFaVsRmu = true;}
      if(nbkfJXjjae == NBWKKsRTwb){cRxpQWWUTR = true;}
      else if(NBWKKsRTwb == nbkfJXjjae){lXpunSOSeg = true;}
      if(fyXbUIWZEy == jmZmREKFps){mkpejFOsZV = true;}
      else if(jmZmREKFps == fyXbUIWZEy){NsAppCxNtC = true;}
      if(utDTGZPFCo == xuPuGnzWHy){ThwIWTxrei = true;}
      if(RCqRmsrYsC == hLhpYQfIRC){kOdzwUpoCB = true;}
      if(PxjQdUHLlZ == CMOPJhBLro){BiCUTsNYLC = true;}
      while(xuPuGnzWHy == utDTGZPFCo){zcHgPMEkxy = true;}
      while(hLhpYQfIRC == hLhpYQfIRC){qNnsqhgknW = true;}
      while(CMOPJhBLro == CMOPJhBLro){PFyAnGBePX = true;}
      if(YKHKDSkbEV == true){YKHKDSkbEV = false;}
      if(ttMysXFjOB == true){ttMysXFjOB = false;}
      if(YBmmqkfAlY == true){YBmmqkfAlY = false;}
      if(lneSYXDWmG == true){lneSYXDWmG = false;}
      if(eEEuIHzQVl == true){eEEuIHzQVl = false;}
      if(cRxpQWWUTR == true){cRxpQWWUTR = false;}
      if(mkpejFOsZV == true){mkpejFOsZV = false;}
      if(ThwIWTxrei == true){ThwIWTxrei = false;}
      if(kOdzwUpoCB == true){kOdzwUpoCB = false;}
      if(BiCUTsNYLC == true){BiCUTsNYLC = false;}
      if(sGqARtUoTw == true){sGqARtUoTw = false;}
      if(ZepjgXHpiP == true){ZepjgXHpiP = false;}
      if(OZqXUjfboc == true){OZqXUjfboc = false;}
      if(GXgbpeXdhC == true){GXgbpeXdhC = false;}
      if(zBUFaVsRmu == true){zBUFaVsRmu = false;}
      if(lXpunSOSeg == true){lXpunSOSeg = false;}
      if(NsAppCxNtC == true){NsAppCxNtC = false;}
      if(zcHgPMEkxy == true){zcHgPMEkxy = false;}
      if(qNnsqhgknW == true){qNnsqhgknW = false;}
      if(PFyAnGBePX == true){PFyAnGBePX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDGPBZUZVZ
{ 
  void VRVhUPBKVt()
  { 
      bool MVfJZEmENU = false;
      bool JOcrZJHwhw = false;
      bool lKnHbLEndV = false;
      bool WrXjXtWbbh = false;
      bool hcxTJiJDuI = false;
      bool PeJSTBgXhN = false;
      bool AzarxQpsUe = false;
      bool meUzOINUyr = false;
      bool CBrUFrhEQW = false;
      bool NzsNhiCEVr = false;
      bool sQiPVjKKEK = false;
      bool mMYpKyGGmF = false;
      bool ikbxRmlGRe = false;
      bool GIyFylScyU = false;
      bool gXAFiBZDDi = false;
      bool buRPJHnkyh = false;
      bool yErYEdNTqY = false;
      bool fdHRYKkWOQ = false;
      bool NhChDKqhwq = false;
      bool xgePWbeaBE = false;
      string iFrBlDOFGE;
      string nlfjnUlkWF;
      string lSiHNmMPUc;
      string SVOpruUhHT;
      string fCGAJMOYqE;
      string apZnVPWjny;
      string qzkdkSWpqs;
      string zEdCZjMhyB;
      string YmXPBcuaTc;
      string XktIcgRcPp;
      string oXgyEWMWOk;
      string DokmZEaUbI;
      string WwVOUOJUZs;
      string SiSILAFZKe;
      string PYMhYizGiY;
      string FwBGSsCSdp;
      string MrxUSTWcaZ;
      string yAJwsyimok;
      string PCkBmVhLoS;
      string ylwUSWaqPF;
      if(iFrBlDOFGE == oXgyEWMWOk){MVfJZEmENU = true;}
      else if(oXgyEWMWOk == iFrBlDOFGE){sQiPVjKKEK = true;}
      if(nlfjnUlkWF == DokmZEaUbI){JOcrZJHwhw = true;}
      else if(DokmZEaUbI == nlfjnUlkWF){mMYpKyGGmF = true;}
      if(lSiHNmMPUc == WwVOUOJUZs){lKnHbLEndV = true;}
      else if(WwVOUOJUZs == lSiHNmMPUc){ikbxRmlGRe = true;}
      if(SVOpruUhHT == SiSILAFZKe){WrXjXtWbbh = true;}
      else if(SiSILAFZKe == SVOpruUhHT){GIyFylScyU = true;}
      if(fCGAJMOYqE == PYMhYizGiY){hcxTJiJDuI = true;}
      else if(PYMhYizGiY == fCGAJMOYqE){gXAFiBZDDi = true;}
      if(apZnVPWjny == FwBGSsCSdp){PeJSTBgXhN = true;}
      else if(FwBGSsCSdp == apZnVPWjny){buRPJHnkyh = true;}
      if(qzkdkSWpqs == MrxUSTWcaZ){AzarxQpsUe = true;}
      else if(MrxUSTWcaZ == qzkdkSWpqs){yErYEdNTqY = true;}
      if(zEdCZjMhyB == yAJwsyimok){meUzOINUyr = true;}
      if(YmXPBcuaTc == PCkBmVhLoS){CBrUFrhEQW = true;}
      if(XktIcgRcPp == ylwUSWaqPF){NzsNhiCEVr = true;}
      while(yAJwsyimok == zEdCZjMhyB){fdHRYKkWOQ = true;}
      while(PCkBmVhLoS == PCkBmVhLoS){NhChDKqhwq = true;}
      while(ylwUSWaqPF == ylwUSWaqPF){xgePWbeaBE = true;}
      if(MVfJZEmENU == true){MVfJZEmENU = false;}
      if(JOcrZJHwhw == true){JOcrZJHwhw = false;}
      if(lKnHbLEndV == true){lKnHbLEndV = false;}
      if(WrXjXtWbbh == true){WrXjXtWbbh = false;}
      if(hcxTJiJDuI == true){hcxTJiJDuI = false;}
      if(PeJSTBgXhN == true){PeJSTBgXhN = false;}
      if(AzarxQpsUe == true){AzarxQpsUe = false;}
      if(meUzOINUyr == true){meUzOINUyr = false;}
      if(CBrUFrhEQW == true){CBrUFrhEQW = false;}
      if(NzsNhiCEVr == true){NzsNhiCEVr = false;}
      if(sQiPVjKKEK == true){sQiPVjKKEK = false;}
      if(mMYpKyGGmF == true){mMYpKyGGmF = false;}
      if(ikbxRmlGRe == true){ikbxRmlGRe = false;}
      if(GIyFylScyU == true){GIyFylScyU = false;}
      if(gXAFiBZDDi == true){gXAFiBZDDi = false;}
      if(buRPJHnkyh == true){buRPJHnkyh = false;}
      if(yErYEdNTqY == true){yErYEdNTqY = false;}
      if(fdHRYKkWOQ == true){fdHRYKkWOQ = false;}
      if(NhChDKqhwq == true){NhChDKqhwq = false;}
      if(xgePWbeaBE == true){xgePWbeaBE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFOEVPHEDO
{ 
  void kPiVibZkgh()
  { 
      bool JHtQKAhPud = false;
      bool SzqFXVKxBw = false;
      bool RXoDPlCdOp = false;
      bool VCPYCWmGwC = false;
      bool uukIHaXtxn = false;
      bool jXKjmlSqAX = false;
      bool xEAFHPiRCB = false;
      bool hEBzBWlfwn = false;
      bool NIfaGxrflQ = false;
      bool EwFXEqtfAq = false;
      bool rGqwGfWKhQ = false;
      bool AluLKoXZyK = false;
      bool XCflwlydtK = false;
      bool bFfEwGQiUa = false;
      bool agyUPSAsMP = false;
      bool SThpSoaFzT = false;
      bool grQXotFpPD = false;
      bool XnFXipEKVd = false;
      bool kFReqHXpkG = false;
      bool fLjAsiQZeV = false;
      string TmgeonyFAw;
      string tJpxbfWwSb;
      string tMHAdJgSoq;
      string ufHxVPzJzE;
      string BZjwDMpMHy;
      string VHjiGHegBf;
      string GfQIBOBrbM;
      string gNwOaUcKxQ;
      string TULqVmuXqN;
      string jSHSxVIbun;
      string KxjtQIKVIk;
      string eUjjMlTZlN;
      string SdBObNFcRE;
      string LAOIGVkRZM;
      string bZPFiPiXGL;
      string CiogVguVRD;
      string DgEDZdFacp;
      string ABAYkrNweM;
      string egWGCcLglZ;
      string aOzVJuVLfF;
      if(TmgeonyFAw == KxjtQIKVIk){JHtQKAhPud = true;}
      else if(KxjtQIKVIk == TmgeonyFAw){rGqwGfWKhQ = true;}
      if(tJpxbfWwSb == eUjjMlTZlN){SzqFXVKxBw = true;}
      else if(eUjjMlTZlN == tJpxbfWwSb){AluLKoXZyK = true;}
      if(tMHAdJgSoq == SdBObNFcRE){RXoDPlCdOp = true;}
      else if(SdBObNFcRE == tMHAdJgSoq){XCflwlydtK = true;}
      if(ufHxVPzJzE == LAOIGVkRZM){VCPYCWmGwC = true;}
      else if(LAOIGVkRZM == ufHxVPzJzE){bFfEwGQiUa = true;}
      if(BZjwDMpMHy == bZPFiPiXGL){uukIHaXtxn = true;}
      else if(bZPFiPiXGL == BZjwDMpMHy){agyUPSAsMP = true;}
      if(VHjiGHegBf == CiogVguVRD){jXKjmlSqAX = true;}
      else if(CiogVguVRD == VHjiGHegBf){SThpSoaFzT = true;}
      if(GfQIBOBrbM == DgEDZdFacp){xEAFHPiRCB = true;}
      else if(DgEDZdFacp == GfQIBOBrbM){grQXotFpPD = true;}
      if(gNwOaUcKxQ == ABAYkrNweM){hEBzBWlfwn = true;}
      if(TULqVmuXqN == egWGCcLglZ){NIfaGxrflQ = true;}
      if(jSHSxVIbun == aOzVJuVLfF){EwFXEqtfAq = true;}
      while(ABAYkrNweM == gNwOaUcKxQ){XnFXipEKVd = true;}
      while(egWGCcLglZ == egWGCcLglZ){kFReqHXpkG = true;}
      while(aOzVJuVLfF == aOzVJuVLfF){fLjAsiQZeV = true;}
      if(JHtQKAhPud == true){JHtQKAhPud = false;}
      if(SzqFXVKxBw == true){SzqFXVKxBw = false;}
      if(RXoDPlCdOp == true){RXoDPlCdOp = false;}
      if(VCPYCWmGwC == true){VCPYCWmGwC = false;}
      if(uukIHaXtxn == true){uukIHaXtxn = false;}
      if(jXKjmlSqAX == true){jXKjmlSqAX = false;}
      if(xEAFHPiRCB == true){xEAFHPiRCB = false;}
      if(hEBzBWlfwn == true){hEBzBWlfwn = false;}
      if(NIfaGxrflQ == true){NIfaGxrflQ = false;}
      if(EwFXEqtfAq == true){EwFXEqtfAq = false;}
      if(rGqwGfWKhQ == true){rGqwGfWKhQ = false;}
      if(AluLKoXZyK == true){AluLKoXZyK = false;}
      if(XCflwlydtK == true){XCflwlydtK = false;}
      if(bFfEwGQiUa == true){bFfEwGQiUa = false;}
      if(agyUPSAsMP == true){agyUPSAsMP = false;}
      if(SThpSoaFzT == true){SThpSoaFzT = false;}
      if(grQXotFpPD == true){grQXotFpPD = false;}
      if(XnFXipEKVd == true){XnFXipEKVd = false;}
      if(kFReqHXpkG == true){kFReqHXpkG = false;}
      if(fLjAsiQZeV == true){fLjAsiQZeV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTAUDRODZR
{ 
  void fipGaTirEp()
  { 
      bool XaqaYVCuIt = false;
      bool QZnhRgsPZQ = false;
      bool UcNSNptldq = false;
      bool DfYxfNwutl = false;
      bool OohggYEizw = false;
      bool lKrprtNXNh = false;
      bool aPQQpkBpBD = false;
      bool jxVnBeufko = false;
      bool kKmhErmhFl = false;
      bool AYhLKyXQpw = false;
      bool XOhuLooEoN = false;
      bool zgmYxPciMx = false;
      bool xSkPDLPJcC = false;
      bool GdonQWcqWP = false;
      bool DhsqmSlIOt = false;
      bool VoEryFcRqA = false;
      bool ZealHUqyHZ = false;
      bool mkLxtOYtbj = false;
      bool ZGuigQZwoL = false;
      bool sKzWoXHHjS = false;
      string QXnLhkzzkI;
      string zsanYNacth;
      string pbLkGemxtP;
      string RpaIztGrKi;
      string xkeoXfwQLP;
      string ztVGLoMCFC;
      string yBEVpJSSnd;
      string GiSLkEwVNa;
      string iVlePWTUwK;
      string hDmHjwfJzN;
      string McchIQbJUG;
      string rpneSbPZGS;
      string oxVcuDuLan;
      string YmWANGsDVy;
      string uKzoRqOHnI;
      string gGCfYOGzlF;
      string UPighETnQM;
      string iLDHWeyfKE;
      string nnWSHRjpay;
      string zsRQcfaSHM;
      if(QXnLhkzzkI == McchIQbJUG){XaqaYVCuIt = true;}
      else if(McchIQbJUG == QXnLhkzzkI){XOhuLooEoN = true;}
      if(zsanYNacth == rpneSbPZGS){QZnhRgsPZQ = true;}
      else if(rpneSbPZGS == zsanYNacth){zgmYxPciMx = true;}
      if(pbLkGemxtP == oxVcuDuLan){UcNSNptldq = true;}
      else if(oxVcuDuLan == pbLkGemxtP){xSkPDLPJcC = true;}
      if(RpaIztGrKi == YmWANGsDVy){DfYxfNwutl = true;}
      else if(YmWANGsDVy == RpaIztGrKi){GdonQWcqWP = true;}
      if(xkeoXfwQLP == uKzoRqOHnI){OohggYEizw = true;}
      else if(uKzoRqOHnI == xkeoXfwQLP){DhsqmSlIOt = true;}
      if(ztVGLoMCFC == gGCfYOGzlF){lKrprtNXNh = true;}
      else if(gGCfYOGzlF == ztVGLoMCFC){VoEryFcRqA = true;}
      if(yBEVpJSSnd == UPighETnQM){aPQQpkBpBD = true;}
      else if(UPighETnQM == yBEVpJSSnd){ZealHUqyHZ = true;}
      if(GiSLkEwVNa == iLDHWeyfKE){jxVnBeufko = true;}
      if(iVlePWTUwK == nnWSHRjpay){kKmhErmhFl = true;}
      if(hDmHjwfJzN == zsRQcfaSHM){AYhLKyXQpw = true;}
      while(iLDHWeyfKE == GiSLkEwVNa){mkLxtOYtbj = true;}
      while(nnWSHRjpay == nnWSHRjpay){ZGuigQZwoL = true;}
      while(zsRQcfaSHM == zsRQcfaSHM){sKzWoXHHjS = true;}
      if(XaqaYVCuIt == true){XaqaYVCuIt = false;}
      if(QZnhRgsPZQ == true){QZnhRgsPZQ = false;}
      if(UcNSNptldq == true){UcNSNptldq = false;}
      if(DfYxfNwutl == true){DfYxfNwutl = false;}
      if(OohggYEizw == true){OohggYEizw = false;}
      if(lKrprtNXNh == true){lKrprtNXNh = false;}
      if(aPQQpkBpBD == true){aPQQpkBpBD = false;}
      if(jxVnBeufko == true){jxVnBeufko = false;}
      if(kKmhErmhFl == true){kKmhErmhFl = false;}
      if(AYhLKyXQpw == true){AYhLKyXQpw = false;}
      if(XOhuLooEoN == true){XOhuLooEoN = false;}
      if(zgmYxPciMx == true){zgmYxPciMx = false;}
      if(xSkPDLPJcC == true){xSkPDLPJcC = false;}
      if(GdonQWcqWP == true){GdonQWcqWP = false;}
      if(DhsqmSlIOt == true){DhsqmSlIOt = false;}
      if(VoEryFcRqA == true){VoEryFcRqA = false;}
      if(ZealHUqyHZ == true){ZealHUqyHZ = false;}
      if(mkLxtOYtbj == true){mkLxtOYtbj = false;}
      if(ZGuigQZwoL == true){ZGuigQZwoL = false;}
      if(sKzWoXHHjS == true){sKzWoXHHjS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNITEPLFLC
{ 
  void PKKeLTuAxQ()
  { 
      bool iycqFGROtx = false;
      bool QJqqBkTnRn = false;
      bool oqAhUTRcNF = false;
      bool gIMocfiFNe = false;
      bool jOSMhugRxt = false;
      bool EpdgorxtVl = false;
      bool nnBnQIxCOU = false;
      bool BOZlEaXnAY = false;
      bool mAeSApeezj = false;
      bool inibpuMduZ = false;
      bool xdDcrpPqcN = false;
      bool UItxznJhnZ = false;
      bool dRCdlNeywI = false;
      bool NsrZbIwCaJ = false;
      bool amBkPatlcB = false;
      bool lepVufbYpe = false;
      bool LQuTAaPTUp = false;
      bool qGHeypQRNL = false;
      bool SrVtWiDWdu = false;
      bool gWLuxKrgko = false;
      string OmnnZmFqIp;
      string mLeeeHosyU;
      string DAQnrSCzlt;
      string zcljNAjHsI;
      string cFojQzhrho;
      string AePOjNWzuG;
      string jGENpKZuQd;
      string WhApqxLfXs;
      string jJQxtUMWzz;
      string djLlXWBatF;
      string YmaDRRdZXm;
      string CpbCVZoHTU;
      string xDuQAlVNRT;
      string wjlRUxhNeb;
      string plzMxmIJQx;
      string htGYIVrKDf;
      string wQIDpSEKgY;
      string qbbreKEhTM;
      string dLxTlCcMJz;
      string EXJzeYduVe;
      if(OmnnZmFqIp == YmaDRRdZXm){iycqFGROtx = true;}
      else if(YmaDRRdZXm == OmnnZmFqIp){xdDcrpPqcN = true;}
      if(mLeeeHosyU == CpbCVZoHTU){QJqqBkTnRn = true;}
      else if(CpbCVZoHTU == mLeeeHosyU){UItxznJhnZ = true;}
      if(DAQnrSCzlt == xDuQAlVNRT){oqAhUTRcNF = true;}
      else if(xDuQAlVNRT == DAQnrSCzlt){dRCdlNeywI = true;}
      if(zcljNAjHsI == wjlRUxhNeb){gIMocfiFNe = true;}
      else if(wjlRUxhNeb == zcljNAjHsI){NsrZbIwCaJ = true;}
      if(cFojQzhrho == plzMxmIJQx){jOSMhugRxt = true;}
      else if(plzMxmIJQx == cFojQzhrho){amBkPatlcB = true;}
      if(AePOjNWzuG == htGYIVrKDf){EpdgorxtVl = true;}
      else if(htGYIVrKDf == AePOjNWzuG){lepVufbYpe = true;}
      if(jGENpKZuQd == wQIDpSEKgY){nnBnQIxCOU = true;}
      else if(wQIDpSEKgY == jGENpKZuQd){LQuTAaPTUp = true;}
      if(WhApqxLfXs == qbbreKEhTM){BOZlEaXnAY = true;}
      if(jJQxtUMWzz == dLxTlCcMJz){mAeSApeezj = true;}
      if(djLlXWBatF == EXJzeYduVe){inibpuMduZ = true;}
      while(qbbreKEhTM == WhApqxLfXs){qGHeypQRNL = true;}
      while(dLxTlCcMJz == dLxTlCcMJz){SrVtWiDWdu = true;}
      while(EXJzeYduVe == EXJzeYduVe){gWLuxKrgko = true;}
      if(iycqFGROtx == true){iycqFGROtx = false;}
      if(QJqqBkTnRn == true){QJqqBkTnRn = false;}
      if(oqAhUTRcNF == true){oqAhUTRcNF = false;}
      if(gIMocfiFNe == true){gIMocfiFNe = false;}
      if(jOSMhugRxt == true){jOSMhugRxt = false;}
      if(EpdgorxtVl == true){EpdgorxtVl = false;}
      if(nnBnQIxCOU == true){nnBnQIxCOU = false;}
      if(BOZlEaXnAY == true){BOZlEaXnAY = false;}
      if(mAeSApeezj == true){mAeSApeezj = false;}
      if(inibpuMduZ == true){inibpuMduZ = false;}
      if(xdDcrpPqcN == true){xdDcrpPqcN = false;}
      if(UItxznJhnZ == true){UItxznJhnZ = false;}
      if(dRCdlNeywI == true){dRCdlNeywI = false;}
      if(NsrZbIwCaJ == true){NsrZbIwCaJ = false;}
      if(amBkPatlcB == true){amBkPatlcB = false;}
      if(lepVufbYpe == true){lepVufbYpe = false;}
      if(LQuTAaPTUp == true){LQuTAaPTUp = false;}
      if(qGHeypQRNL == true){qGHeypQRNL = false;}
      if(SrVtWiDWdu == true){SrVtWiDWdu = false;}
      if(gWLuxKrgko == true){gWLuxKrgko = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDHTOZJVTK
{ 
  void ptXOboTeYi()
  { 
      bool QpgbqhuYTL = false;
      bool VyLPUtwAYW = false;
      bool HBsjSoYeQz = false;
      bool DCIDyTEPLn = false;
      bool SsGFUFYsPK = false;
      bool IyWfUPxxIC = false;
      bool IQIUISpIQB = false;
      bool pgojDNumPN = false;
      bool QeOGpFfcih = false;
      bool VHHJfCkkxB = false;
      bool PQcOUbIlbG = false;
      bool UKgukcBCdD = false;
      bool mMYifiYfEB = false;
      bool cJpNxACAkN = false;
      bool wsAcNLZMXC = false;
      bool AiGsOCqsik = false;
      bool CcgZcKTSxk = false;
      bool ZAQQHsMwVT = false;
      bool JMICAtDwzt = false;
      bool IJQALTMazC = false;
      string ABrzZynnzs;
      string TpVVmpsNKK;
      string wsHAqVwpBd;
      string ZmcZyMkDmV;
      string kdZnAVBwOu;
      string QDMGcHsrHE;
      string CylVTfMuXa;
      string EoZnYRSTAU;
      string TAbGMWaWxp;
      string SsuiTmrEUT;
      string JGXmpadXgK;
      string nZqljBWfIw;
      string FoxgILtpUl;
      string ZOyfLMbnPl;
      string rCpmBrBIzR;
      string PLwXOUIqee;
      string fmDtjZaKaW;
      string ZhPWECyKeP;
      string JlqCVNSZRp;
      string DjJkFEzuCb;
      if(ABrzZynnzs == JGXmpadXgK){QpgbqhuYTL = true;}
      else if(JGXmpadXgK == ABrzZynnzs){PQcOUbIlbG = true;}
      if(TpVVmpsNKK == nZqljBWfIw){VyLPUtwAYW = true;}
      else if(nZqljBWfIw == TpVVmpsNKK){UKgukcBCdD = true;}
      if(wsHAqVwpBd == FoxgILtpUl){HBsjSoYeQz = true;}
      else if(FoxgILtpUl == wsHAqVwpBd){mMYifiYfEB = true;}
      if(ZmcZyMkDmV == ZOyfLMbnPl){DCIDyTEPLn = true;}
      else if(ZOyfLMbnPl == ZmcZyMkDmV){cJpNxACAkN = true;}
      if(kdZnAVBwOu == rCpmBrBIzR){SsGFUFYsPK = true;}
      else if(rCpmBrBIzR == kdZnAVBwOu){wsAcNLZMXC = true;}
      if(QDMGcHsrHE == PLwXOUIqee){IyWfUPxxIC = true;}
      else if(PLwXOUIqee == QDMGcHsrHE){AiGsOCqsik = true;}
      if(CylVTfMuXa == fmDtjZaKaW){IQIUISpIQB = true;}
      else if(fmDtjZaKaW == CylVTfMuXa){CcgZcKTSxk = true;}
      if(EoZnYRSTAU == ZhPWECyKeP){pgojDNumPN = true;}
      if(TAbGMWaWxp == JlqCVNSZRp){QeOGpFfcih = true;}
      if(SsuiTmrEUT == DjJkFEzuCb){VHHJfCkkxB = true;}
      while(ZhPWECyKeP == EoZnYRSTAU){ZAQQHsMwVT = true;}
      while(JlqCVNSZRp == JlqCVNSZRp){JMICAtDwzt = true;}
      while(DjJkFEzuCb == DjJkFEzuCb){IJQALTMazC = true;}
      if(QpgbqhuYTL == true){QpgbqhuYTL = false;}
      if(VyLPUtwAYW == true){VyLPUtwAYW = false;}
      if(HBsjSoYeQz == true){HBsjSoYeQz = false;}
      if(DCIDyTEPLn == true){DCIDyTEPLn = false;}
      if(SsGFUFYsPK == true){SsGFUFYsPK = false;}
      if(IyWfUPxxIC == true){IyWfUPxxIC = false;}
      if(IQIUISpIQB == true){IQIUISpIQB = false;}
      if(pgojDNumPN == true){pgojDNumPN = false;}
      if(QeOGpFfcih == true){QeOGpFfcih = false;}
      if(VHHJfCkkxB == true){VHHJfCkkxB = false;}
      if(PQcOUbIlbG == true){PQcOUbIlbG = false;}
      if(UKgukcBCdD == true){UKgukcBCdD = false;}
      if(mMYifiYfEB == true){mMYifiYfEB = false;}
      if(cJpNxACAkN == true){cJpNxACAkN = false;}
      if(wsAcNLZMXC == true){wsAcNLZMXC = false;}
      if(AiGsOCqsik == true){AiGsOCqsik = false;}
      if(CcgZcKTSxk == true){CcgZcKTSxk = false;}
      if(ZAQQHsMwVT == true){ZAQQHsMwVT = false;}
      if(JMICAtDwzt == true){JMICAtDwzt = false;}
      if(IJQALTMazC == true){IJQALTMazC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOEVVUIOCT
{ 
  void CSehfNDFxQ()
  { 
      bool NCWAcZSqRs = false;
      bool utofwJVUYV = false;
      bool fENfPHnPuY = false;
      bool leFzOHzcVg = false;
      bool RyHdBMUdBy = false;
      bool qdaDDJnpjU = false;
      bool kCurGPnoRo = false;
      bool KryrDgwidD = false;
      bool mKOxhIECwE = false;
      bool SIsBuPCPWk = false;
      bool YfLMmzehzV = false;
      bool MEMghanyKy = false;
      bool KlsMVBzxxn = false;
      bool egMrdHyCJh = false;
      bool cWCZrNwMST = false;
      bool aEFYallzpk = false;
      bool AhjLqerTCa = false;
      bool clnbUnjSTH = false;
      bool FlddNZbmRr = false;
      bool UyLXhumqiN = false;
      string WmaHwxKItE;
      string OcNoJdccab;
      string kryByXEukM;
      string qfZtpoCIzm;
      string FVUQQoEKyd;
      string WdBhneoZIX;
      string sOXhMhDSzU;
      string aUcnVPXgkJ;
      string SsxGpNerGL;
      string AczbtpxmDh;
      string llLdDBAMLY;
      string GHozEzRQqz;
      string DLMmUxVBse;
      string RkdCWghSDn;
      string MRfgErnzXt;
      string YfuEeZZXIF;
      string fzTfHVdlcW;
      string RyNDmkeeic;
      string JVdzGkpYXw;
      string HJKxHNyzZi;
      if(WmaHwxKItE == llLdDBAMLY){NCWAcZSqRs = true;}
      else if(llLdDBAMLY == WmaHwxKItE){YfLMmzehzV = true;}
      if(OcNoJdccab == GHozEzRQqz){utofwJVUYV = true;}
      else if(GHozEzRQqz == OcNoJdccab){MEMghanyKy = true;}
      if(kryByXEukM == DLMmUxVBse){fENfPHnPuY = true;}
      else if(DLMmUxVBse == kryByXEukM){KlsMVBzxxn = true;}
      if(qfZtpoCIzm == RkdCWghSDn){leFzOHzcVg = true;}
      else if(RkdCWghSDn == qfZtpoCIzm){egMrdHyCJh = true;}
      if(FVUQQoEKyd == MRfgErnzXt){RyHdBMUdBy = true;}
      else if(MRfgErnzXt == FVUQQoEKyd){cWCZrNwMST = true;}
      if(WdBhneoZIX == YfuEeZZXIF){qdaDDJnpjU = true;}
      else if(YfuEeZZXIF == WdBhneoZIX){aEFYallzpk = true;}
      if(sOXhMhDSzU == fzTfHVdlcW){kCurGPnoRo = true;}
      else if(fzTfHVdlcW == sOXhMhDSzU){AhjLqerTCa = true;}
      if(aUcnVPXgkJ == RyNDmkeeic){KryrDgwidD = true;}
      if(SsxGpNerGL == JVdzGkpYXw){mKOxhIECwE = true;}
      if(AczbtpxmDh == HJKxHNyzZi){SIsBuPCPWk = true;}
      while(RyNDmkeeic == aUcnVPXgkJ){clnbUnjSTH = true;}
      while(JVdzGkpYXw == JVdzGkpYXw){FlddNZbmRr = true;}
      while(HJKxHNyzZi == HJKxHNyzZi){UyLXhumqiN = true;}
      if(NCWAcZSqRs == true){NCWAcZSqRs = false;}
      if(utofwJVUYV == true){utofwJVUYV = false;}
      if(fENfPHnPuY == true){fENfPHnPuY = false;}
      if(leFzOHzcVg == true){leFzOHzcVg = false;}
      if(RyHdBMUdBy == true){RyHdBMUdBy = false;}
      if(qdaDDJnpjU == true){qdaDDJnpjU = false;}
      if(kCurGPnoRo == true){kCurGPnoRo = false;}
      if(KryrDgwidD == true){KryrDgwidD = false;}
      if(mKOxhIECwE == true){mKOxhIECwE = false;}
      if(SIsBuPCPWk == true){SIsBuPCPWk = false;}
      if(YfLMmzehzV == true){YfLMmzehzV = false;}
      if(MEMghanyKy == true){MEMghanyKy = false;}
      if(KlsMVBzxxn == true){KlsMVBzxxn = false;}
      if(egMrdHyCJh == true){egMrdHyCJh = false;}
      if(cWCZrNwMST == true){cWCZrNwMST = false;}
      if(aEFYallzpk == true){aEFYallzpk = false;}
      if(AhjLqerTCa == true){AhjLqerTCa = false;}
      if(clnbUnjSTH == true){clnbUnjSTH = false;}
      if(FlddNZbmRr == true){FlddNZbmRr = false;}
      if(UyLXhumqiN == true){UyLXhumqiN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWNFRJJOMR
{ 
  void ZhhSJsZSoL()
  { 
      bool yChhmZNwrN = false;
      bool SGJNXMsjGs = false;
      bool RglRaxJymc = false;
      bool frRrBIqioB = false;
      bool mJZMHnFcWz = false;
      bool MGHaCRPPGo = false;
      bool POJOhZnRMO = false;
      bool VKuEGHGZKm = false;
      bool rgbmQYjppi = false;
      bool sabAkXAKeg = false;
      bool znPHdBLDUt = false;
      bool KpFTwimVyI = false;
      bool oxacVuhtSh = false;
      bool GwucmEQTJO = false;
      bool MgVwXCVIDB = false;
      bool keMVrCMmkh = false;
      bool SQjlmOubfr = false;
      bool SSLiwIbeFS = false;
      bool YZpQxbiYkk = false;
      bool qciauuxiII = false;
      string DLxwqYkNbK;
      string cSQRrqDrld;
      string TdxCewMPFq;
      string MIozsEfjIK;
      string zjfafEMAzT;
      string FPPLjZOtRt;
      string LUHjyTdRYm;
      string LSiadiyWWZ;
      string jMQklxrcPT;
      string plSOydbucL;
      string auaLIlfngA;
      string arWqKyEVyA;
      string aBBExZAUbA;
      string GCsKznlEcz;
      string QEuOrxOaDz;
      string ZGwbkYsVNi;
      string lKMgtYyMrV;
      string MzsziWGmMA;
      string KYQbaAGRZZ;
      string tPptMGqNUT;
      if(DLxwqYkNbK == auaLIlfngA){yChhmZNwrN = true;}
      else if(auaLIlfngA == DLxwqYkNbK){znPHdBLDUt = true;}
      if(cSQRrqDrld == arWqKyEVyA){SGJNXMsjGs = true;}
      else if(arWqKyEVyA == cSQRrqDrld){KpFTwimVyI = true;}
      if(TdxCewMPFq == aBBExZAUbA){RglRaxJymc = true;}
      else if(aBBExZAUbA == TdxCewMPFq){oxacVuhtSh = true;}
      if(MIozsEfjIK == GCsKznlEcz){frRrBIqioB = true;}
      else if(GCsKznlEcz == MIozsEfjIK){GwucmEQTJO = true;}
      if(zjfafEMAzT == QEuOrxOaDz){mJZMHnFcWz = true;}
      else if(QEuOrxOaDz == zjfafEMAzT){MgVwXCVIDB = true;}
      if(FPPLjZOtRt == ZGwbkYsVNi){MGHaCRPPGo = true;}
      else if(ZGwbkYsVNi == FPPLjZOtRt){keMVrCMmkh = true;}
      if(LUHjyTdRYm == lKMgtYyMrV){POJOhZnRMO = true;}
      else if(lKMgtYyMrV == LUHjyTdRYm){SQjlmOubfr = true;}
      if(LSiadiyWWZ == MzsziWGmMA){VKuEGHGZKm = true;}
      if(jMQklxrcPT == KYQbaAGRZZ){rgbmQYjppi = true;}
      if(plSOydbucL == tPptMGqNUT){sabAkXAKeg = true;}
      while(MzsziWGmMA == LSiadiyWWZ){SSLiwIbeFS = true;}
      while(KYQbaAGRZZ == KYQbaAGRZZ){YZpQxbiYkk = true;}
      while(tPptMGqNUT == tPptMGqNUT){qciauuxiII = true;}
      if(yChhmZNwrN == true){yChhmZNwrN = false;}
      if(SGJNXMsjGs == true){SGJNXMsjGs = false;}
      if(RglRaxJymc == true){RglRaxJymc = false;}
      if(frRrBIqioB == true){frRrBIqioB = false;}
      if(mJZMHnFcWz == true){mJZMHnFcWz = false;}
      if(MGHaCRPPGo == true){MGHaCRPPGo = false;}
      if(POJOhZnRMO == true){POJOhZnRMO = false;}
      if(VKuEGHGZKm == true){VKuEGHGZKm = false;}
      if(rgbmQYjppi == true){rgbmQYjppi = false;}
      if(sabAkXAKeg == true){sabAkXAKeg = false;}
      if(znPHdBLDUt == true){znPHdBLDUt = false;}
      if(KpFTwimVyI == true){KpFTwimVyI = false;}
      if(oxacVuhtSh == true){oxacVuhtSh = false;}
      if(GwucmEQTJO == true){GwucmEQTJO = false;}
      if(MgVwXCVIDB == true){MgVwXCVIDB = false;}
      if(keMVrCMmkh == true){keMVrCMmkh = false;}
      if(SQjlmOubfr == true){SQjlmOubfr = false;}
      if(SSLiwIbeFS == true){SSLiwIbeFS = false;}
      if(YZpQxbiYkk == true){YZpQxbiYkk = false;}
      if(qciauuxiII == true){qciauuxiII = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RAUATQTEJD
{ 
  void bDnGzIgLgw()
  { 
      bool RpgBnmzupN = false;
      bool HhKkuOqebG = false;
      bool rsAeKphnFw = false;
      bool iGDbLLZaoL = false;
      bool mNtxBSMVgc = false;
      bool BufIfXoCqy = false;
      bool FKptdBdhYi = false;
      bool oPoQTezDcr = false;
      bool dMHctnZuwn = false;
      bool VWiqGbXASz = false;
      bool ndwxmlGPoA = false;
      bool YlYzTrCNzp = false;
      bool aikkNSfyJq = false;
      bool HykdDzPKoI = false;
      bool hJFwOixjWO = false;
      bool ZJAbYErKjU = false;
      bool FIGysaBuuU = false;
      bool brXqIQcoWd = false;
      bool UwauRxyIEy = false;
      bool GFZUDYDHCn = false;
      string xwdrhjskFL;
      string NsexIqlhEY;
      string UkBhRnOWXf;
      string pwFAqnqRTV;
      string JPdChLHrKz;
      string SWXRyMuuas;
      string UWMYVQndFT;
      string zTOhOEHyAF;
      string fWLXMTXmCe;
      string swqZBmDEgQ;
      string XdlpAzHoDt;
      string EwtVNyKnLB;
      string rAbaaDcngb;
      string BCRigCjVXN;
      string LijIZxBVMD;
      string bOsfXXBLOw;
      string VSIbrBeLnK;
      string OoPxoJPTAd;
      string BHbdzlJkKJ;
      string AXGbrrZIPX;
      if(xwdrhjskFL == XdlpAzHoDt){RpgBnmzupN = true;}
      else if(XdlpAzHoDt == xwdrhjskFL){ndwxmlGPoA = true;}
      if(NsexIqlhEY == EwtVNyKnLB){HhKkuOqebG = true;}
      else if(EwtVNyKnLB == NsexIqlhEY){YlYzTrCNzp = true;}
      if(UkBhRnOWXf == rAbaaDcngb){rsAeKphnFw = true;}
      else if(rAbaaDcngb == UkBhRnOWXf){aikkNSfyJq = true;}
      if(pwFAqnqRTV == BCRigCjVXN){iGDbLLZaoL = true;}
      else if(BCRigCjVXN == pwFAqnqRTV){HykdDzPKoI = true;}
      if(JPdChLHrKz == LijIZxBVMD){mNtxBSMVgc = true;}
      else if(LijIZxBVMD == JPdChLHrKz){hJFwOixjWO = true;}
      if(SWXRyMuuas == bOsfXXBLOw){BufIfXoCqy = true;}
      else if(bOsfXXBLOw == SWXRyMuuas){ZJAbYErKjU = true;}
      if(UWMYVQndFT == VSIbrBeLnK){FKptdBdhYi = true;}
      else if(VSIbrBeLnK == UWMYVQndFT){FIGysaBuuU = true;}
      if(zTOhOEHyAF == OoPxoJPTAd){oPoQTezDcr = true;}
      if(fWLXMTXmCe == BHbdzlJkKJ){dMHctnZuwn = true;}
      if(swqZBmDEgQ == AXGbrrZIPX){VWiqGbXASz = true;}
      while(OoPxoJPTAd == zTOhOEHyAF){brXqIQcoWd = true;}
      while(BHbdzlJkKJ == BHbdzlJkKJ){UwauRxyIEy = true;}
      while(AXGbrrZIPX == AXGbrrZIPX){GFZUDYDHCn = true;}
      if(RpgBnmzupN == true){RpgBnmzupN = false;}
      if(HhKkuOqebG == true){HhKkuOqebG = false;}
      if(rsAeKphnFw == true){rsAeKphnFw = false;}
      if(iGDbLLZaoL == true){iGDbLLZaoL = false;}
      if(mNtxBSMVgc == true){mNtxBSMVgc = false;}
      if(BufIfXoCqy == true){BufIfXoCqy = false;}
      if(FKptdBdhYi == true){FKptdBdhYi = false;}
      if(oPoQTezDcr == true){oPoQTezDcr = false;}
      if(dMHctnZuwn == true){dMHctnZuwn = false;}
      if(VWiqGbXASz == true){VWiqGbXASz = false;}
      if(ndwxmlGPoA == true){ndwxmlGPoA = false;}
      if(YlYzTrCNzp == true){YlYzTrCNzp = false;}
      if(aikkNSfyJq == true){aikkNSfyJq = false;}
      if(HykdDzPKoI == true){HykdDzPKoI = false;}
      if(hJFwOixjWO == true){hJFwOixjWO = false;}
      if(ZJAbYErKjU == true){ZJAbYErKjU = false;}
      if(FIGysaBuuU == true){FIGysaBuuU = false;}
      if(brXqIQcoWd == true){brXqIQcoWd = false;}
      if(UwauRxyIEy == true){UwauRxyIEy = false;}
      if(GFZUDYDHCn == true){GFZUDYDHCn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKNCSCQVBB
{ 
  void GGTNliowTE()
  { 
      bool cdKykuGLhg = false;
      bool JDoUwVmKXC = false;
      bool BXWWYDEVVe = false;
      bool YGcZfMbbNF = false;
      bool uYJWcGJzIt = false;
      bool OcndDFGmZg = false;
      bool pjpDICZOoj = false;
      bool sKxRGcNAtS = false;
      bool tENbPuSzWa = false;
      bool FoCfPKhGNa = false;
      bool ftKYADeWWZ = false;
      bool qGsGmlWOmM = false;
      bool iarNeEIRCu = false;
      bool uHlSlzsnbL = false;
      bool Pwbwjyuurc = false;
      bool nTSAqFCxsu = false;
      bool uNUbeiUZUm = false;
      bool rhlaxmyucf = false;
      bool JMYYHaokbg = false;
      bool xwtfQBaARA = false;
      string PRiUwdyfEA;
      string mTVOgfHboT;
      string kBXIEIsokE;
      string MjmBbLFIcs;
      string EyJCGLbfEJ;
      string OWqJbNsaQm;
      string jJuAnCgTlV;
      string ZzyuPmrVBs;
      string fNjboosdZN;
      string RdroJtCJND;
      string eIsiiPXuso;
      string VXYXHVZTKy;
      string JCtXDuGJlU;
      string jiHyNXTArY;
      string QxjkrsFThm;
      string ThyPsbNUem;
      string IOJXEmQaJi;
      string CYblgMSJfJ;
      string pmayACkrEl;
      string KyUFPCnLfF;
      if(PRiUwdyfEA == eIsiiPXuso){cdKykuGLhg = true;}
      else if(eIsiiPXuso == PRiUwdyfEA){ftKYADeWWZ = true;}
      if(mTVOgfHboT == VXYXHVZTKy){JDoUwVmKXC = true;}
      else if(VXYXHVZTKy == mTVOgfHboT){qGsGmlWOmM = true;}
      if(kBXIEIsokE == JCtXDuGJlU){BXWWYDEVVe = true;}
      else if(JCtXDuGJlU == kBXIEIsokE){iarNeEIRCu = true;}
      if(MjmBbLFIcs == jiHyNXTArY){YGcZfMbbNF = true;}
      else if(jiHyNXTArY == MjmBbLFIcs){uHlSlzsnbL = true;}
      if(EyJCGLbfEJ == QxjkrsFThm){uYJWcGJzIt = true;}
      else if(QxjkrsFThm == EyJCGLbfEJ){Pwbwjyuurc = true;}
      if(OWqJbNsaQm == ThyPsbNUem){OcndDFGmZg = true;}
      else if(ThyPsbNUem == OWqJbNsaQm){nTSAqFCxsu = true;}
      if(jJuAnCgTlV == IOJXEmQaJi){pjpDICZOoj = true;}
      else if(IOJXEmQaJi == jJuAnCgTlV){uNUbeiUZUm = true;}
      if(ZzyuPmrVBs == CYblgMSJfJ){sKxRGcNAtS = true;}
      if(fNjboosdZN == pmayACkrEl){tENbPuSzWa = true;}
      if(RdroJtCJND == KyUFPCnLfF){FoCfPKhGNa = true;}
      while(CYblgMSJfJ == ZzyuPmrVBs){rhlaxmyucf = true;}
      while(pmayACkrEl == pmayACkrEl){JMYYHaokbg = true;}
      while(KyUFPCnLfF == KyUFPCnLfF){xwtfQBaARA = true;}
      if(cdKykuGLhg == true){cdKykuGLhg = false;}
      if(JDoUwVmKXC == true){JDoUwVmKXC = false;}
      if(BXWWYDEVVe == true){BXWWYDEVVe = false;}
      if(YGcZfMbbNF == true){YGcZfMbbNF = false;}
      if(uYJWcGJzIt == true){uYJWcGJzIt = false;}
      if(OcndDFGmZg == true){OcndDFGmZg = false;}
      if(pjpDICZOoj == true){pjpDICZOoj = false;}
      if(sKxRGcNAtS == true){sKxRGcNAtS = false;}
      if(tENbPuSzWa == true){tENbPuSzWa = false;}
      if(FoCfPKhGNa == true){FoCfPKhGNa = false;}
      if(ftKYADeWWZ == true){ftKYADeWWZ = false;}
      if(qGsGmlWOmM == true){qGsGmlWOmM = false;}
      if(iarNeEIRCu == true){iarNeEIRCu = false;}
      if(uHlSlzsnbL == true){uHlSlzsnbL = false;}
      if(Pwbwjyuurc == true){Pwbwjyuurc = false;}
      if(nTSAqFCxsu == true){nTSAqFCxsu = false;}
      if(uNUbeiUZUm == true){uNUbeiUZUm = false;}
      if(rhlaxmyucf == true){rhlaxmyucf = false;}
      if(JMYYHaokbg == true){JMYYHaokbg = false;}
      if(xwtfQBaARA == true){xwtfQBaARA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGJPLSJGWM
{ 
  void irZFuUQQVA()
  { 
      bool SLaqMWCgXL = false;
      bool QmIiyisnXX = false;
      bool TyCSWUdGDc = false;
      bool HzzRplSEls = false;
      bool hmrtahIGKb = false;
      bool SRUeSUJHUq = false;
      bool rudtDQnqrM = false;
      bool QoBdpfFIro = false;
      bool LXuaKpdTyV = false;
      bool cKitBlJxqJ = false;
      bool tRNyLcPpom = false;
      bool OAPfeUACiM = false;
      bool mTrWjFFHcD = false;
      bool WIQhutJxPg = false;
      bool andLGbtDPg = false;
      bool lGNdWZYqNF = false;
      bool WINlQGjhjk = false;
      bool KCmClzpgQI = false;
      bool KCqwQPtmKV = false;
      bool USiJJRaquA = false;
      string beVylbeJad;
      string OVUPNgOeeK;
      string cHEXJPhNOe;
      string NeWeByFlKM;
      string KjsVNexIxq;
      string joCuFTZxoW;
      string sRtwPizpNO;
      string abTRzsOiKe;
      string SZPWtXcbYg;
      string XIwnSrpxFe;
      string eGthPHVkuM;
      string FqmKDTBWBr;
      string FXQfpSffyH;
      string DQcezLfgGm;
      string CrfMbgUljz;
      string qSwNYHpNrx;
      string bolnInNIKr;
      string mTPOpNqDEJ;
      string yswyQjUPFq;
      string URoJKMFrDm;
      if(beVylbeJad == eGthPHVkuM){SLaqMWCgXL = true;}
      else if(eGthPHVkuM == beVylbeJad){tRNyLcPpom = true;}
      if(OVUPNgOeeK == FqmKDTBWBr){QmIiyisnXX = true;}
      else if(FqmKDTBWBr == OVUPNgOeeK){OAPfeUACiM = true;}
      if(cHEXJPhNOe == FXQfpSffyH){TyCSWUdGDc = true;}
      else if(FXQfpSffyH == cHEXJPhNOe){mTrWjFFHcD = true;}
      if(NeWeByFlKM == DQcezLfgGm){HzzRplSEls = true;}
      else if(DQcezLfgGm == NeWeByFlKM){WIQhutJxPg = true;}
      if(KjsVNexIxq == CrfMbgUljz){hmrtahIGKb = true;}
      else if(CrfMbgUljz == KjsVNexIxq){andLGbtDPg = true;}
      if(joCuFTZxoW == qSwNYHpNrx){SRUeSUJHUq = true;}
      else if(qSwNYHpNrx == joCuFTZxoW){lGNdWZYqNF = true;}
      if(sRtwPizpNO == bolnInNIKr){rudtDQnqrM = true;}
      else if(bolnInNIKr == sRtwPizpNO){WINlQGjhjk = true;}
      if(abTRzsOiKe == mTPOpNqDEJ){QoBdpfFIro = true;}
      if(SZPWtXcbYg == yswyQjUPFq){LXuaKpdTyV = true;}
      if(XIwnSrpxFe == URoJKMFrDm){cKitBlJxqJ = true;}
      while(mTPOpNqDEJ == abTRzsOiKe){KCmClzpgQI = true;}
      while(yswyQjUPFq == yswyQjUPFq){KCqwQPtmKV = true;}
      while(URoJKMFrDm == URoJKMFrDm){USiJJRaquA = true;}
      if(SLaqMWCgXL == true){SLaqMWCgXL = false;}
      if(QmIiyisnXX == true){QmIiyisnXX = false;}
      if(TyCSWUdGDc == true){TyCSWUdGDc = false;}
      if(HzzRplSEls == true){HzzRplSEls = false;}
      if(hmrtahIGKb == true){hmrtahIGKb = false;}
      if(SRUeSUJHUq == true){SRUeSUJHUq = false;}
      if(rudtDQnqrM == true){rudtDQnqrM = false;}
      if(QoBdpfFIro == true){QoBdpfFIro = false;}
      if(LXuaKpdTyV == true){LXuaKpdTyV = false;}
      if(cKitBlJxqJ == true){cKitBlJxqJ = false;}
      if(tRNyLcPpom == true){tRNyLcPpom = false;}
      if(OAPfeUACiM == true){OAPfeUACiM = false;}
      if(mTrWjFFHcD == true){mTrWjFFHcD = false;}
      if(WIQhutJxPg == true){WIQhutJxPg = false;}
      if(andLGbtDPg == true){andLGbtDPg = false;}
      if(lGNdWZYqNF == true){lGNdWZYqNF = false;}
      if(WINlQGjhjk == true){WINlQGjhjk = false;}
      if(KCmClzpgQI == true){KCmClzpgQI = false;}
      if(KCqwQPtmKV == true){KCqwQPtmKV = false;}
      if(USiJJRaquA == true){USiJJRaquA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PDHWSAWOEB
{ 
  void gdYWLUgFan()
  { 
      bool OqqJCSjTzO = false;
      bool dJNjUwrawY = false;
      bool gnXoNhgXXu = false;
      bool EhRCafhooJ = false;
      bool McmFVfYSIu = false;
      bool JpRJTZTCuT = false;
      bool kLuDKuqKIo = false;
      bool OCllMDBRSh = false;
      bool IOOclNQIiB = false;
      bool LfsUYAgiua = false;
      bool nOKTfGEewQ = false;
      bool YBiMLVxSRx = false;
      bool eiaHciIQNM = false;
      bool VSWrttEuwe = false;
      bool IkLScKxgJC = false;
      bool COQxwEmCpx = false;
      bool xnQjuFepSQ = false;
      bool RCWmnsXIdS = false;
      bool kbGLJGCYwo = false;
      bool HBEygUTaXW = false;
      string cXJRHzRFgI;
      string kPSOKTrGjL;
      string xYrNTqXUKO;
      string XLpEredsfY;
      string OEeWQicUkn;
      string ZcsAwEfwyQ;
      string bxtRjYYNVe;
      string ozaLwrsVxj;
      string OCiVntSpIn;
      string zhtOwRKMlq;
      string JOyFzaChDD;
      string KKyOCYNYdo;
      string GiFgfGELOe;
      string hgiFZzEcWN;
      string rjlEdojfMW;
      string DliwkaJQZr;
      string VpSXVdarnD;
      string UkBPxVwADp;
      string WYyqbwxlUz;
      string omDdrBROiA;
      if(cXJRHzRFgI == JOyFzaChDD){OqqJCSjTzO = true;}
      else if(JOyFzaChDD == cXJRHzRFgI){nOKTfGEewQ = true;}
      if(kPSOKTrGjL == KKyOCYNYdo){dJNjUwrawY = true;}
      else if(KKyOCYNYdo == kPSOKTrGjL){YBiMLVxSRx = true;}
      if(xYrNTqXUKO == GiFgfGELOe){gnXoNhgXXu = true;}
      else if(GiFgfGELOe == xYrNTqXUKO){eiaHciIQNM = true;}
      if(XLpEredsfY == hgiFZzEcWN){EhRCafhooJ = true;}
      else if(hgiFZzEcWN == XLpEredsfY){VSWrttEuwe = true;}
      if(OEeWQicUkn == rjlEdojfMW){McmFVfYSIu = true;}
      else if(rjlEdojfMW == OEeWQicUkn){IkLScKxgJC = true;}
      if(ZcsAwEfwyQ == DliwkaJQZr){JpRJTZTCuT = true;}
      else if(DliwkaJQZr == ZcsAwEfwyQ){COQxwEmCpx = true;}
      if(bxtRjYYNVe == VpSXVdarnD){kLuDKuqKIo = true;}
      else if(VpSXVdarnD == bxtRjYYNVe){xnQjuFepSQ = true;}
      if(ozaLwrsVxj == UkBPxVwADp){OCllMDBRSh = true;}
      if(OCiVntSpIn == WYyqbwxlUz){IOOclNQIiB = true;}
      if(zhtOwRKMlq == omDdrBROiA){LfsUYAgiua = true;}
      while(UkBPxVwADp == ozaLwrsVxj){RCWmnsXIdS = true;}
      while(WYyqbwxlUz == WYyqbwxlUz){kbGLJGCYwo = true;}
      while(omDdrBROiA == omDdrBROiA){HBEygUTaXW = true;}
      if(OqqJCSjTzO == true){OqqJCSjTzO = false;}
      if(dJNjUwrawY == true){dJNjUwrawY = false;}
      if(gnXoNhgXXu == true){gnXoNhgXXu = false;}
      if(EhRCafhooJ == true){EhRCafhooJ = false;}
      if(McmFVfYSIu == true){McmFVfYSIu = false;}
      if(JpRJTZTCuT == true){JpRJTZTCuT = false;}
      if(kLuDKuqKIo == true){kLuDKuqKIo = false;}
      if(OCllMDBRSh == true){OCllMDBRSh = false;}
      if(IOOclNQIiB == true){IOOclNQIiB = false;}
      if(LfsUYAgiua == true){LfsUYAgiua = false;}
      if(nOKTfGEewQ == true){nOKTfGEewQ = false;}
      if(YBiMLVxSRx == true){YBiMLVxSRx = false;}
      if(eiaHciIQNM == true){eiaHciIQNM = false;}
      if(VSWrttEuwe == true){VSWrttEuwe = false;}
      if(IkLScKxgJC == true){IkLScKxgJC = false;}
      if(COQxwEmCpx == true){COQxwEmCpx = false;}
      if(xnQjuFepSQ == true){xnQjuFepSQ = false;}
      if(RCWmnsXIdS == true){RCWmnsXIdS = false;}
      if(kbGLJGCYwo == true){kbGLJGCYwo = false;}
      if(HBEygUTaXW == true){HBEygUTaXW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUCNOGSKVJ
{ 
  void snHthaMIIO()
  { 
      bool cVfpiUAPmH = false;
      bool eERjWJhLGg = false;
      bool mHebOwBTBE = false;
      bool yhZdCWdJbm = false;
      bool pWdKNldyWt = false;
      bool ySSrsUpEam = false;
      bool SgNiIwdngz = false;
      bool fYiSqPdUNb = false;
      bool RDwGFePgjh = false;
      bool fYhnUIItBQ = false;
      bool HoQWOZizBc = false;
      bool qVqyUOjHcc = false;
      bool gxDzSHquyh = false;
      bool HiSwTcmZqf = false;
      bool wPfHpKhiTF = false;
      bool XAQXjKkQDH = false;
      bool hnBSVIDter = false;
      bool bKPxgQRwJI = false;
      bool YHasJGRtMI = false;
      bool qWVjxHOMlh = false;
      string hFViZkdwkJ;
      string bKQatHjuyW;
      string fscJQYGwoA;
      string RruratdVzV;
      string UqkPuzaqyE;
      string uYjdRocMSA;
      string egGjrjOXAA;
      string cOucBoINNQ;
      string yOxjFrHRZk;
      string RRDzqnjAXL;
      string jCqyafdHcc;
      string fOyBCPiVez;
      string bxxOhLLwlN;
      string EHpBfwXzJY;
      string OzoxFCSBwa;
      string ENVXimEbQP;
      string ThVPXYYxUG;
      string rjMGkbHAJf;
      string rKzKIqlRRs;
      string qwhsEgdZZf;
      if(hFViZkdwkJ == jCqyafdHcc){cVfpiUAPmH = true;}
      else if(jCqyafdHcc == hFViZkdwkJ){HoQWOZizBc = true;}
      if(bKQatHjuyW == fOyBCPiVez){eERjWJhLGg = true;}
      else if(fOyBCPiVez == bKQatHjuyW){qVqyUOjHcc = true;}
      if(fscJQYGwoA == bxxOhLLwlN){mHebOwBTBE = true;}
      else if(bxxOhLLwlN == fscJQYGwoA){gxDzSHquyh = true;}
      if(RruratdVzV == EHpBfwXzJY){yhZdCWdJbm = true;}
      else if(EHpBfwXzJY == RruratdVzV){HiSwTcmZqf = true;}
      if(UqkPuzaqyE == OzoxFCSBwa){pWdKNldyWt = true;}
      else if(OzoxFCSBwa == UqkPuzaqyE){wPfHpKhiTF = true;}
      if(uYjdRocMSA == ENVXimEbQP){ySSrsUpEam = true;}
      else if(ENVXimEbQP == uYjdRocMSA){XAQXjKkQDH = true;}
      if(egGjrjOXAA == ThVPXYYxUG){SgNiIwdngz = true;}
      else if(ThVPXYYxUG == egGjrjOXAA){hnBSVIDter = true;}
      if(cOucBoINNQ == rjMGkbHAJf){fYiSqPdUNb = true;}
      if(yOxjFrHRZk == rKzKIqlRRs){RDwGFePgjh = true;}
      if(RRDzqnjAXL == qwhsEgdZZf){fYhnUIItBQ = true;}
      while(rjMGkbHAJf == cOucBoINNQ){bKPxgQRwJI = true;}
      while(rKzKIqlRRs == rKzKIqlRRs){YHasJGRtMI = true;}
      while(qwhsEgdZZf == qwhsEgdZZf){qWVjxHOMlh = true;}
      if(cVfpiUAPmH == true){cVfpiUAPmH = false;}
      if(eERjWJhLGg == true){eERjWJhLGg = false;}
      if(mHebOwBTBE == true){mHebOwBTBE = false;}
      if(yhZdCWdJbm == true){yhZdCWdJbm = false;}
      if(pWdKNldyWt == true){pWdKNldyWt = false;}
      if(ySSrsUpEam == true){ySSrsUpEam = false;}
      if(SgNiIwdngz == true){SgNiIwdngz = false;}
      if(fYiSqPdUNb == true){fYiSqPdUNb = false;}
      if(RDwGFePgjh == true){RDwGFePgjh = false;}
      if(fYhnUIItBQ == true){fYhnUIItBQ = false;}
      if(HoQWOZizBc == true){HoQWOZizBc = false;}
      if(qVqyUOjHcc == true){qVqyUOjHcc = false;}
      if(gxDzSHquyh == true){gxDzSHquyh = false;}
      if(HiSwTcmZqf == true){HiSwTcmZqf = false;}
      if(wPfHpKhiTF == true){wPfHpKhiTF = false;}
      if(XAQXjKkQDH == true){XAQXjKkQDH = false;}
      if(hnBSVIDter == true){hnBSVIDter = false;}
      if(bKPxgQRwJI == true){bKPxgQRwJI = false;}
      if(YHasJGRtMI == true){YHasJGRtMI = false;}
      if(qWVjxHOMlh == true){qWVjxHOMlh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARXICBYUHP
{ 
  void uTEaAReogn()
  { 
      bool hUBqeliOcp = false;
      bool gsPhDzVFPd = false;
      bool TUyAeBpGIS = false;
      bool RfAFSXHGBV = false;
      bool uysHfBDPpl = false;
      bool LGVpLMVBMc = false;
      bool wbGJYBrJOf = false;
      bool qOEtiVbqUc = false;
      bool xZQVHKJJtG = false;
      bool CGtXYSqjid = false;
      bool ItBKuwCbGp = false;
      bool kegifWKjCO = false;
      bool qiPIcjUgUQ = false;
      bool dqHpTDYGZK = false;
      bool IhDEUXZKrC = false;
      bool HGgTmZdrgK = false;
      bool bUGpLsWpPb = false;
      bool xEKrFIeKmF = false;
      bool KJoRIWJnCs = false;
      bool YgZOhmaMsb = false;
      string CcEWhpzkrg;
      string MuKtgRQTch;
      string CgERJeepyZ;
      string oNBLhoWCDD;
      string ENOXyUJKAC;
      string xBtjLUXlND;
      string LJmRqysyLq;
      string uOQZcoSfTn;
      string UTowcnTRAN;
      string RjoArtZxgz;
      string bLzIGhkTGW;
      string BqRZhqTpnD;
      string dbyxZKYPhi;
      string OUzTMIUfot;
      string CzKcLZSPRB;
      string ZjIcVzNBhw;
      string IUlXIfrxNZ;
      string VnAsAeRUkA;
      string rJyfIdMWyM;
      string tTxskhMlUe;
      if(CcEWhpzkrg == bLzIGhkTGW){hUBqeliOcp = true;}
      else if(bLzIGhkTGW == CcEWhpzkrg){ItBKuwCbGp = true;}
      if(MuKtgRQTch == BqRZhqTpnD){gsPhDzVFPd = true;}
      else if(BqRZhqTpnD == MuKtgRQTch){kegifWKjCO = true;}
      if(CgERJeepyZ == dbyxZKYPhi){TUyAeBpGIS = true;}
      else if(dbyxZKYPhi == CgERJeepyZ){qiPIcjUgUQ = true;}
      if(oNBLhoWCDD == OUzTMIUfot){RfAFSXHGBV = true;}
      else if(OUzTMIUfot == oNBLhoWCDD){dqHpTDYGZK = true;}
      if(ENOXyUJKAC == CzKcLZSPRB){uysHfBDPpl = true;}
      else if(CzKcLZSPRB == ENOXyUJKAC){IhDEUXZKrC = true;}
      if(xBtjLUXlND == ZjIcVzNBhw){LGVpLMVBMc = true;}
      else if(ZjIcVzNBhw == xBtjLUXlND){HGgTmZdrgK = true;}
      if(LJmRqysyLq == IUlXIfrxNZ){wbGJYBrJOf = true;}
      else if(IUlXIfrxNZ == LJmRqysyLq){bUGpLsWpPb = true;}
      if(uOQZcoSfTn == VnAsAeRUkA){qOEtiVbqUc = true;}
      if(UTowcnTRAN == rJyfIdMWyM){xZQVHKJJtG = true;}
      if(RjoArtZxgz == tTxskhMlUe){CGtXYSqjid = true;}
      while(VnAsAeRUkA == uOQZcoSfTn){xEKrFIeKmF = true;}
      while(rJyfIdMWyM == rJyfIdMWyM){KJoRIWJnCs = true;}
      while(tTxskhMlUe == tTxskhMlUe){YgZOhmaMsb = true;}
      if(hUBqeliOcp == true){hUBqeliOcp = false;}
      if(gsPhDzVFPd == true){gsPhDzVFPd = false;}
      if(TUyAeBpGIS == true){TUyAeBpGIS = false;}
      if(RfAFSXHGBV == true){RfAFSXHGBV = false;}
      if(uysHfBDPpl == true){uysHfBDPpl = false;}
      if(LGVpLMVBMc == true){LGVpLMVBMc = false;}
      if(wbGJYBrJOf == true){wbGJYBrJOf = false;}
      if(qOEtiVbqUc == true){qOEtiVbqUc = false;}
      if(xZQVHKJJtG == true){xZQVHKJJtG = false;}
      if(CGtXYSqjid == true){CGtXYSqjid = false;}
      if(ItBKuwCbGp == true){ItBKuwCbGp = false;}
      if(kegifWKjCO == true){kegifWKjCO = false;}
      if(qiPIcjUgUQ == true){qiPIcjUgUQ = false;}
      if(dqHpTDYGZK == true){dqHpTDYGZK = false;}
      if(IhDEUXZKrC == true){IhDEUXZKrC = false;}
      if(HGgTmZdrgK == true){HGgTmZdrgK = false;}
      if(bUGpLsWpPb == true){bUGpLsWpPb = false;}
      if(xEKrFIeKmF == true){xEKrFIeKmF = false;}
      if(KJoRIWJnCs == true){KJoRIWJnCs = false;}
      if(YgZOhmaMsb == true){YgZOhmaMsb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFLQPYWPVK
{ 
  void zDrmgdYNEs()
  { 
      bool ywMGoUGjcB = false;
      bool LxoMSLRRFY = false;
      bool DUCOEOARcN = false;
      bool WEVewoafkF = false;
      bool zScMrYGWqf = false;
      bool TGpHZctyBa = false;
      bool TnHPeGbJQd = false;
      bool jkfzYjroWf = false;
      bool HdaxsPNNFS = false;
      bool ucdKlKLMhk = false;
      bool wxFNuiZqio = false;
      bool jEaVTpNJVP = false;
      bool sNEyhHGVMN = false;
      bool YfHkjJXNBK = false;
      bool oVePipBIqw = false;
      bool xBpRqhrHem = false;
      bool bEdUQExpkJ = false;
      bool RzILZWioPq = false;
      bool GxeQQXoosB = false;
      bool RPiNikqJzd = false;
      string zWRocJoTUn;
      string bdQdpVXOco;
      string EKPWGtStIC;
      string lgNUmnitOx;
      string bljRDDJgcp;
      string tYyZmoGuii;
      string qtKSCtPupB;
      string lcAfNRZxTC;
      string kkRSHNingy;
      string hnLfFgbQPI;
      string nNpaDQXRLV;
      string OIagyFbrLn;
      string LbNrTyRUZf;
      string pIhKOWtqPp;
      string oQbLiYMehA;
      string FiFbwLAyHE;
      string yDrfeGaQRa;
      string KkcUyuACIt;
      string lmlZaGDFOD;
      string WwjKqkYwfc;
      if(zWRocJoTUn == nNpaDQXRLV){ywMGoUGjcB = true;}
      else if(nNpaDQXRLV == zWRocJoTUn){wxFNuiZqio = true;}
      if(bdQdpVXOco == OIagyFbrLn){LxoMSLRRFY = true;}
      else if(OIagyFbrLn == bdQdpVXOco){jEaVTpNJVP = true;}
      if(EKPWGtStIC == LbNrTyRUZf){DUCOEOARcN = true;}
      else if(LbNrTyRUZf == EKPWGtStIC){sNEyhHGVMN = true;}
      if(lgNUmnitOx == pIhKOWtqPp){WEVewoafkF = true;}
      else if(pIhKOWtqPp == lgNUmnitOx){YfHkjJXNBK = true;}
      if(bljRDDJgcp == oQbLiYMehA){zScMrYGWqf = true;}
      else if(oQbLiYMehA == bljRDDJgcp){oVePipBIqw = true;}
      if(tYyZmoGuii == FiFbwLAyHE){TGpHZctyBa = true;}
      else if(FiFbwLAyHE == tYyZmoGuii){xBpRqhrHem = true;}
      if(qtKSCtPupB == yDrfeGaQRa){TnHPeGbJQd = true;}
      else if(yDrfeGaQRa == qtKSCtPupB){bEdUQExpkJ = true;}
      if(lcAfNRZxTC == KkcUyuACIt){jkfzYjroWf = true;}
      if(kkRSHNingy == lmlZaGDFOD){HdaxsPNNFS = true;}
      if(hnLfFgbQPI == WwjKqkYwfc){ucdKlKLMhk = true;}
      while(KkcUyuACIt == lcAfNRZxTC){RzILZWioPq = true;}
      while(lmlZaGDFOD == lmlZaGDFOD){GxeQQXoosB = true;}
      while(WwjKqkYwfc == WwjKqkYwfc){RPiNikqJzd = true;}
      if(ywMGoUGjcB == true){ywMGoUGjcB = false;}
      if(LxoMSLRRFY == true){LxoMSLRRFY = false;}
      if(DUCOEOARcN == true){DUCOEOARcN = false;}
      if(WEVewoafkF == true){WEVewoafkF = false;}
      if(zScMrYGWqf == true){zScMrYGWqf = false;}
      if(TGpHZctyBa == true){TGpHZctyBa = false;}
      if(TnHPeGbJQd == true){TnHPeGbJQd = false;}
      if(jkfzYjroWf == true){jkfzYjroWf = false;}
      if(HdaxsPNNFS == true){HdaxsPNNFS = false;}
      if(ucdKlKLMhk == true){ucdKlKLMhk = false;}
      if(wxFNuiZqio == true){wxFNuiZqio = false;}
      if(jEaVTpNJVP == true){jEaVTpNJVP = false;}
      if(sNEyhHGVMN == true){sNEyhHGVMN = false;}
      if(YfHkjJXNBK == true){YfHkjJXNBK = false;}
      if(oVePipBIqw == true){oVePipBIqw = false;}
      if(xBpRqhrHem == true){xBpRqhrHem = false;}
      if(bEdUQExpkJ == true){bEdUQExpkJ = false;}
      if(RzILZWioPq == true){RzILZWioPq = false;}
      if(GxeQQXoosB == true){GxeQQXoosB = false;}
      if(RPiNikqJzd == true){RPiNikqJzd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDNEAGHGQH
{ 
  void kAZqAcPduw()
  { 
      bool IYgRKtKGZx = false;
      bool uzubkqksuU = false;
      bool BtPxlgIFxr = false;
      bool ydeylfQflG = false;
      bool UOWfEKVPRW = false;
      bool yadNcOJifc = false;
      bool lEJhzRUwoF = false;
      bool aFGnzlXisa = false;
      bool KrnZsWzQUX = false;
      bool WgzIUQEngm = false;
      bool pYaMwsToNq = false;
      bool pZpFSsPjnb = false;
      bool RDbQhsFxTi = false;
      bool hiCGkkRbdA = false;
      bool DKCdgwqtpb = false;
      bool AUAEVlxJdC = false;
      bool nVVeIHXiTg = false;
      bool anGnYHBxjl = false;
      bool CKGqiMixjy = false;
      bool mHxaLgnXUZ = false;
      string cFhTMRmQcT;
      string lFYoWKIWcN;
      string CsNKsPloEq;
      string GDOxxieDda;
      string HhUNYRjtHu;
      string WoxzRjqXZx;
      string exMkNhqbqn;
      string eFsBGTYAkb;
      string erhJUQGPfM;
      string qGcfwJVizq;
      string aICSPQwwsx;
      string LqmySmOCPw;
      string baudwYbMFw;
      string yoAsAWoOtD;
      string TJWhBASeNI;
      string tSTDPAMXWq;
      string ojpwzWqtyu;
      string yAIMcRENcu;
      string FxyxBeVxdA;
      string JQqCOjTZhe;
      if(cFhTMRmQcT == aICSPQwwsx){IYgRKtKGZx = true;}
      else if(aICSPQwwsx == cFhTMRmQcT){pYaMwsToNq = true;}
      if(lFYoWKIWcN == LqmySmOCPw){uzubkqksuU = true;}
      else if(LqmySmOCPw == lFYoWKIWcN){pZpFSsPjnb = true;}
      if(CsNKsPloEq == baudwYbMFw){BtPxlgIFxr = true;}
      else if(baudwYbMFw == CsNKsPloEq){RDbQhsFxTi = true;}
      if(GDOxxieDda == yoAsAWoOtD){ydeylfQflG = true;}
      else if(yoAsAWoOtD == GDOxxieDda){hiCGkkRbdA = true;}
      if(HhUNYRjtHu == TJWhBASeNI){UOWfEKVPRW = true;}
      else if(TJWhBASeNI == HhUNYRjtHu){DKCdgwqtpb = true;}
      if(WoxzRjqXZx == tSTDPAMXWq){yadNcOJifc = true;}
      else if(tSTDPAMXWq == WoxzRjqXZx){AUAEVlxJdC = true;}
      if(exMkNhqbqn == ojpwzWqtyu){lEJhzRUwoF = true;}
      else if(ojpwzWqtyu == exMkNhqbqn){nVVeIHXiTg = true;}
      if(eFsBGTYAkb == yAIMcRENcu){aFGnzlXisa = true;}
      if(erhJUQGPfM == FxyxBeVxdA){KrnZsWzQUX = true;}
      if(qGcfwJVizq == JQqCOjTZhe){WgzIUQEngm = true;}
      while(yAIMcRENcu == eFsBGTYAkb){anGnYHBxjl = true;}
      while(FxyxBeVxdA == FxyxBeVxdA){CKGqiMixjy = true;}
      while(JQqCOjTZhe == JQqCOjTZhe){mHxaLgnXUZ = true;}
      if(IYgRKtKGZx == true){IYgRKtKGZx = false;}
      if(uzubkqksuU == true){uzubkqksuU = false;}
      if(BtPxlgIFxr == true){BtPxlgIFxr = false;}
      if(ydeylfQflG == true){ydeylfQflG = false;}
      if(UOWfEKVPRW == true){UOWfEKVPRW = false;}
      if(yadNcOJifc == true){yadNcOJifc = false;}
      if(lEJhzRUwoF == true){lEJhzRUwoF = false;}
      if(aFGnzlXisa == true){aFGnzlXisa = false;}
      if(KrnZsWzQUX == true){KrnZsWzQUX = false;}
      if(WgzIUQEngm == true){WgzIUQEngm = false;}
      if(pYaMwsToNq == true){pYaMwsToNq = false;}
      if(pZpFSsPjnb == true){pZpFSsPjnb = false;}
      if(RDbQhsFxTi == true){RDbQhsFxTi = false;}
      if(hiCGkkRbdA == true){hiCGkkRbdA = false;}
      if(DKCdgwqtpb == true){DKCdgwqtpb = false;}
      if(AUAEVlxJdC == true){AUAEVlxJdC = false;}
      if(nVVeIHXiTg == true){nVVeIHXiTg = false;}
      if(anGnYHBxjl == true){anGnYHBxjl = false;}
      if(CKGqiMixjy == true){CKGqiMixjy = false;}
      if(mHxaLgnXUZ == true){mHxaLgnXUZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOIZGNEDAC
{ 
  void GkdxRcuxhJ()
  { 
      bool OxrDzudfkr = false;
      bool haMbfkclNi = false;
      bool sfHlMUCVtB = false;
      bool joJyzPJLAU = false;
      bool uDzjdFVPgk = false;
      bool DaBDHhoGqe = false;
      bool sHliHrROcP = false;
      bool aRlrnogXHG = false;
      bool yloIyJmFpQ = false;
      bool aCUUbmRPbk = false;
      bool nHlQJloJPR = false;
      bool AQyjfGScjy = false;
      bool ELXMnXwQQB = false;
      bool XRuVRpzXyL = false;
      bool UdoYPJEjnU = false;
      bool UnedgcjZcl = false;
      bool oXsOsiVbRo = false;
      bool HteYdaVywe = false;
      bool TMbufjlRoo = false;
      bool GZuMWwkaef = false;
      string CGdimcnBTn;
      string WRPVtTFUsl;
      string hoDYAUssPE;
      string wloeCCoXMm;
      string MpkUVOBIbT;
      string OOxKmNCFiR;
      string jtlPqkckSr;
      string ehHGYqDhDk;
      string TjRupgodro;
      string zjotCSEVdk;
      string lPoinfGpku;
      string KUCxxzcpZJ;
      string wysdsusNDG;
      string mgERzDuhGJ;
      string ayswdehqxD;
      string pNwTomWLps;
      string msldIdQjys;
      string DtiPixEwzN;
      string NCPzQYjjbL;
      string firNVgMPmA;
      if(CGdimcnBTn == lPoinfGpku){OxrDzudfkr = true;}
      else if(lPoinfGpku == CGdimcnBTn){nHlQJloJPR = true;}
      if(WRPVtTFUsl == KUCxxzcpZJ){haMbfkclNi = true;}
      else if(KUCxxzcpZJ == WRPVtTFUsl){AQyjfGScjy = true;}
      if(hoDYAUssPE == wysdsusNDG){sfHlMUCVtB = true;}
      else if(wysdsusNDG == hoDYAUssPE){ELXMnXwQQB = true;}
      if(wloeCCoXMm == mgERzDuhGJ){joJyzPJLAU = true;}
      else if(mgERzDuhGJ == wloeCCoXMm){XRuVRpzXyL = true;}
      if(MpkUVOBIbT == ayswdehqxD){uDzjdFVPgk = true;}
      else if(ayswdehqxD == MpkUVOBIbT){UdoYPJEjnU = true;}
      if(OOxKmNCFiR == pNwTomWLps){DaBDHhoGqe = true;}
      else if(pNwTomWLps == OOxKmNCFiR){UnedgcjZcl = true;}
      if(jtlPqkckSr == msldIdQjys){sHliHrROcP = true;}
      else if(msldIdQjys == jtlPqkckSr){oXsOsiVbRo = true;}
      if(ehHGYqDhDk == DtiPixEwzN){aRlrnogXHG = true;}
      if(TjRupgodro == NCPzQYjjbL){yloIyJmFpQ = true;}
      if(zjotCSEVdk == firNVgMPmA){aCUUbmRPbk = true;}
      while(DtiPixEwzN == ehHGYqDhDk){HteYdaVywe = true;}
      while(NCPzQYjjbL == NCPzQYjjbL){TMbufjlRoo = true;}
      while(firNVgMPmA == firNVgMPmA){GZuMWwkaef = true;}
      if(OxrDzudfkr == true){OxrDzudfkr = false;}
      if(haMbfkclNi == true){haMbfkclNi = false;}
      if(sfHlMUCVtB == true){sfHlMUCVtB = false;}
      if(joJyzPJLAU == true){joJyzPJLAU = false;}
      if(uDzjdFVPgk == true){uDzjdFVPgk = false;}
      if(DaBDHhoGqe == true){DaBDHhoGqe = false;}
      if(sHliHrROcP == true){sHliHrROcP = false;}
      if(aRlrnogXHG == true){aRlrnogXHG = false;}
      if(yloIyJmFpQ == true){yloIyJmFpQ = false;}
      if(aCUUbmRPbk == true){aCUUbmRPbk = false;}
      if(nHlQJloJPR == true){nHlQJloJPR = false;}
      if(AQyjfGScjy == true){AQyjfGScjy = false;}
      if(ELXMnXwQQB == true){ELXMnXwQQB = false;}
      if(XRuVRpzXyL == true){XRuVRpzXyL = false;}
      if(UdoYPJEjnU == true){UdoYPJEjnU = false;}
      if(UnedgcjZcl == true){UnedgcjZcl = false;}
      if(oXsOsiVbRo == true){oXsOsiVbRo = false;}
      if(HteYdaVywe == true){HteYdaVywe = false;}
      if(TMbufjlRoo == true){TMbufjlRoo = false;}
      if(GZuMWwkaef == true){GZuMWwkaef = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTCUDHKEJF
{ 
  void CTLnGVxtBM()
  { 
      bool WyVcbVhdWP = false;
      bool YTGCjippNK = false;
      bool aPDyyGTfYs = false;
      bool FUiqxPeDRy = false;
      bool VYieGxZZEc = false;
      bool oSBiWGtWdV = false;
      bool BBFcJEjPET = false;
      bool EmYOoBgYrA = false;
      bool gtbuEmSAUq = false;
      bool VHYwxUSFUC = false;
      bool NKUjYCtmsU = false;
      bool ZVedoHYKYW = false;
      bool kitNyxNbRT = false;
      bool iaDomWYrWB = false;
      bool reGzQzbuGp = false;
      bool wIgxQdPHlb = false;
      bool nRVZlyRopS = false;
      bool hgmWeFbuwy = false;
      bool USUbXZsFYI = false;
      bool GQFuMZJgNR = false;
      string xTtPUKdxrF;
      string ShflxAZmdn;
      string dfUCTwBzrd;
      string iViPrRPLto;
      string pONtlozIQu;
      string xmhRkRzquY;
      string JdEOWwzQtf;
      string kOsnyPSZQd;
      string wrixfumRda;
      string RYPUfMJyXo;
      string piOjKitsTU;
      string yYaQcQtHha;
      string JhlSNLzXIl;
      string GTCanNcylx;
      string BtxIcsxyrO;
      string RCPwfIwwWy;
      string jVjhOeVzcO;
      string mwUkYPjcoU;
      string OAftTDDGue;
      string QgbnMfJPsy;
      if(xTtPUKdxrF == piOjKitsTU){WyVcbVhdWP = true;}
      else if(piOjKitsTU == xTtPUKdxrF){NKUjYCtmsU = true;}
      if(ShflxAZmdn == yYaQcQtHha){YTGCjippNK = true;}
      else if(yYaQcQtHha == ShflxAZmdn){ZVedoHYKYW = true;}
      if(dfUCTwBzrd == JhlSNLzXIl){aPDyyGTfYs = true;}
      else if(JhlSNLzXIl == dfUCTwBzrd){kitNyxNbRT = true;}
      if(iViPrRPLto == GTCanNcylx){FUiqxPeDRy = true;}
      else if(GTCanNcylx == iViPrRPLto){iaDomWYrWB = true;}
      if(pONtlozIQu == BtxIcsxyrO){VYieGxZZEc = true;}
      else if(BtxIcsxyrO == pONtlozIQu){reGzQzbuGp = true;}
      if(xmhRkRzquY == RCPwfIwwWy){oSBiWGtWdV = true;}
      else if(RCPwfIwwWy == xmhRkRzquY){wIgxQdPHlb = true;}
      if(JdEOWwzQtf == jVjhOeVzcO){BBFcJEjPET = true;}
      else if(jVjhOeVzcO == JdEOWwzQtf){nRVZlyRopS = true;}
      if(kOsnyPSZQd == mwUkYPjcoU){EmYOoBgYrA = true;}
      if(wrixfumRda == OAftTDDGue){gtbuEmSAUq = true;}
      if(RYPUfMJyXo == QgbnMfJPsy){VHYwxUSFUC = true;}
      while(mwUkYPjcoU == kOsnyPSZQd){hgmWeFbuwy = true;}
      while(OAftTDDGue == OAftTDDGue){USUbXZsFYI = true;}
      while(QgbnMfJPsy == QgbnMfJPsy){GQFuMZJgNR = true;}
      if(WyVcbVhdWP == true){WyVcbVhdWP = false;}
      if(YTGCjippNK == true){YTGCjippNK = false;}
      if(aPDyyGTfYs == true){aPDyyGTfYs = false;}
      if(FUiqxPeDRy == true){FUiqxPeDRy = false;}
      if(VYieGxZZEc == true){VYieGxZZEc = false;}
      if(oSBiWGtWdV == true){oSBiWGtWdV = false;}
      if(BBFcJEjPET == true){BBFcJEjPET = false;}
      if(EmYOoBgYrA == true){EmYOoBgYrA = false;}
      if(gtbuEmSAUq == true){gtbuEmSAUq = false;}
      if(VHYwxUSFUC == true){VHYwxUSFUC = false;}
      if(NKUjYCtmsU == true){NKUjYCtmsU = false;}
      if(ZVedoHYKYW == true){ZVedoHYKYW = false;}
      if(kitNyxNbRT == true){kitNyxNbRT = false;}
      if(iaDomWYrWB == true){iaDomWYrWB = false;}
      if(reGzQzbuGp == true){reGzQzbuGp = false;}
      if(wIgxQdPHlb == true){wIgxQdPHlb = false;}
      if(nRVZlyRopS == true){nRVZlyRopS = false;}
      if(hgmWeFbuwy == true){hgmWeFbuwy = false;}
      if(USUbXZsFYI == true){USUbXZsFYI = false;}
      if(GQFuMZJgNR == true){GQFuMZJgNR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PULAFCCUEG
{ 
  void MEzngRPNpD()
  { 
      bool XWSLuCYhdH = false;
      bool nieingEqKX = false;
      bool uUZFcDKILf = false;
      bool WgsceEmMzb = false;
      bool qXCLIdwTzH = false;
      bool mBNPjDwNhq = false;
      bool rPWyjGpCEi = false;
      bool tqqigWROxy = false;
      bool GqIDrVSdrb = false;
      bool HZdHiaBEbB = false;
      bool ntOQNwKdhM = false;
      bool khPijAGSFO = false;
      bool nLKcaUMiAF = false;
      bool VNluKMbrpw = false;
      bool KnuepZJuXi = false;
      bool ThyMMcjlor = false;
      bool iadcqXuUYX = false;
      bool XOcJDzPelB = false;
      bool LRLQlnOYhg = false;
      bool bpDxMjJSmR = false;
      string dzzpAYKNPm;
      string SargEkBmEu;
      string ljmGrfkCFu;
      string WlEjSUsMpL;
      string ddgKykeryx;
      string DzADhsMsyU;
      string nIHUPfVIOj;
      string qowsRICcIG;
      string ArDIqXlABY;
      string IANVWVVMtR;
      string PWcNFOCHlZ;
      string qijrTuEzcr;
      string tUHobqaZVw;
      string lohqpcPpCc;
      string UdOagYPUCa;
      string RViBXtPmlO;
      string mckonBBsBp;
      string fOwAXPGfIC;
      string aFXtdPGfSw;
      string NbDnorrYmf;
      if(dzzpAYKNPm == PWcNFOCHlZ){XWSLuCYhdH = true;}
      else if(PWcNFOCHlZ == dzzpAYKNPm){ntOQNwKdhM = true;}
      if(SargEkBmEu == qijrTuEzcr){nieingEqKX = true;}
      else if(qijrTuEzcr == SargEkBmEu){khPijAGSFO = true;}
      if(ljmGrfkCFu == tUHobqaZVw){uUZFcDKILf = true;}
      else if(tUHobqaZVw == ljmGrfkCFu){nLKcaUMiAF = true;}
      if(WlEjSUsMpL == lohqpcPpCc){WgsceEmMzb = true;}
      else if(lohqpcPpCc == WlEjSUsMpL){VNluKMbrpw = true;}
      if(ddgKykeryx == UdOagYPUCa){qXCLIdwTzH = true;}
      else if(UdOagYPUCa == ddgKykeryx){KnuepZJuXi = true;}
      if(DzADhsMsyU == RViBXtPmlO){mBNPjDwNhq = true;}
      else if(RViBXtPmlO == DzADhsMsyU){ThyMMcjlor = true;}
      if(nIHUPfVIOj == mckonBBsBp){rPWyjGpCEi = true;}
      else if(mckonBBsBp == nIHUPfVIOj){iadcqXuUYX = true;}
      if(qowsRICcIG == fOwAXPGfIC){tqqigWROxy = true;}
      if(ArDIqXlABY == aFXtdPGfSw){GqIDrVSdrb = true;}
      if(IANVWVVMtR == NbDnorrYmf){HZdHiaBEbB = true;}
      while(fOwAXPGfIC == qowsRICcIG){XOcJDzPelB = true;}
      while(aFXtdPGfSw == aFXtdPGfSw){LRLQlnOYhg = true;}
      while(NbDnorrYmf == NbDnorrYmf){bpDxMjJSmR = true;}
      if(XWSLuCYhdH == true){XWSLuCYhdH = false;}
      if(nieingEqKX == true){nieingEqKX = false;}
      if(uUZFcDKILf == true){uUZFcDKILf = false;}
      if(WgsceEmMzb == true){WgsceEmMzb = false;}
      if(qXCLIdwTzH == true){qXCLIdwTzH = false;}
      if(mBNPjDwNhq == true){mBNPjDwNhq = false;}
      if(rPWyjGpCEi == true){rPWyjGpCEi = false;}
      if(tqqigWROxy == true){tqqigWROxy = false;}
      if(GqIDrVSdrb == true){GqIDrVSdrb = false;}
      if(HZdHiaBEbB == true){HZdHiaBEbB = false;}
      if(ntOQNwKdhM == true){ntOQNwKdhM = false;}
      if(khPijAGSFO == true){khPijAGSFO = false;}
      if(nLKcaUMiAF == true){nLKcaUMiAF = false;}
      if(VNluKMbrpw == true){VNluKMbrpw = false;}
      if(KnuepZJuXi == true){KnuepZJuXi = false;}
      if(ThyMMcjlor == true){ThyMMcjlor = false;}
      if(iadcqXuUYX == true){iadcqXuUYX = false;}
      if(XOcJDzPelB == true){XOcJDzPelB = false;}
      if(LRLQlnOYhg == true){LRLQlnOYhg = false;}
      if(bpDxMjJSmR == true){bpDxMjJSmR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQTOOLDTYY
{ 
  void msJfEApBFi()
  { 
      bool qZddHdmPWE = false;
      bool tjzUGbGgUQ = false;
      bool bddkkkKADp = false;
      bool TZiWcxWeOK = false;
      bool GQyzXTaaVK = false;
      bool qemjTNurrW = false;
      bool SlMfkUBbrJ = false;
      bool FbSJKKedNR = false;
      bool JjeszomyDP = false;
      bool BemrqTESND = false;
      bool SyhMEPLcYJ = false;
      bool hQdZMiHSgw = false;
      bool hCYcHZnZSp = false;
      bool FMPJzKCRni = false;
      bool cJYshjAMeI = false;
      bool MkkRVQYEEe = false;
      bool alKiDUATaB = false;
      bool foexTXceuX = false;
      bool ZauJcTayni = false;
      bool lxNJHqzppM = false;
      string ppzdgWopmO;
      string RxoOXpVpQK;
      string MuQFGfnMoE;
      string FNsMtsbFhF;
      string GBuWjgrIcY;
      string bAEofuYtXB;
      string ibAiIEEbUd;
      string NQILEKztVY;
      string mejQbFIDgz;
      string UhgfWdAMOf;
      string cPmyKLqskU;
      string ueYzNDrjGC;
      string uAuVJfiboa;
      string KmfouXrkGP;
      string NPSLDoJhSS;
      string kQGLjcTRod;
      string cPDKKIyiEo;
      string LGdpofhjRT;
      string WAIVosgUES;
      string DZwcmyLIBu;
      if(ppzdgWopmO == cPmyKLqskU){qZddHdmPWE = true;}
      else if(cPmyKLqskU == ppzdgWopmO){SyhMEPLcYJ = true;}
      if(RxoOXpVpQK == ueYzNDrjGC){tjzUGbGgUQ = true;}
      else if(ueYzNDrjGC == RxoOXpVpQK){hQdZMiHSgw = true;}
      if(MuQFGfnMoE == uAuVJfiboa){bddkkkKADp = true;}
      else if(uAuVJfiboa == MuQFGfnMoE){hCYcHZnZSp = true;}
      if(FNsMtsbFhF == KmfouXrkGP){TZiWcxWeOK = true;}
      else if(KmfouXrkGP == FNsMtsbFhF){FMPJzKCRni = true;}
      if(GBuWjgrIcY == NPSLDoJhSS){GQyzXTaaVK = true;}
      else if(NPSLDoJhSS == GBuWjgrIcY){cJYshjAMeI = true;}
      if(bAEofuYtXB == kQGLjcTRod){qemjTNurrW = true;}
      else if(kQGLjcTRod == bAEofuYtXB){MkkRVQYEEe = true;}
      if(ibAiIEEbUd == cPDKKIyiEo){SlMfkUBbrJ = true;}
      else if(cPDKKIyiEo == ibAiIEEbUd){alKiDUATaB = true;}
      if(NQILEKztVY == LGdpofhjRT){FbSJKKedNR = true;}
      if(mejQbFIDgz == WAIVosgUES){JjeszomyDP = true;}
      if(UhgfWdAMOf == DZwcmyLIBu){BemrqTESND = true;}
      while(LGdpofhjRT == NQILEKztVY){foexTXceuX = true;}
      while(WAIVosgUES == WAIVosgUES){ZauJcTayni = true;}
      while(DZwcmyLIBu == DZwcmyLIBu){lxNJHqzppM = true;}
      if(qZddHdmPWE == true){qZddHdmPWE = false;}
      if(tjzUGbGgUQ == true){tjzUGbGgUQ = false;}
      if(bddkkkKADp == true){bddkkkKADp = false;}
      if(TZiWcxWeOK == true){TZiWcxWeOK = false;}
      if(GQyzXTaaVK == true){GQyzXTaaVK = false;}
      if(qemjTNurrW == true){qemjTNurrW = false;}
      if(SlMfkUBbrJ == true){SlMfkUBbrJ = false;}
      if(FbSJKKedNR == true){FbSJKKedNR = false;}
      if(JjeszomyDP == true){JjeszomyDP = false;}
      if(BemrqTESND == true){BemrqTESND = false;}
      if(SyhMEPLcYJ == true){SyhMEPLcYJ = false;}
      if(hQdZMiHSgw == true){hQdZMiHSgw = false;}
      if(hCYcHZnZSp == true){hCYcHZnZSp = false;}
      if(FMPJzKCRni == true){FMPJzKCRni = false;}
      if(cJYshjAMeI == true){cJYshjAMeI = false;}
      if(MkkRVQYEEe == true){MkkRVQYEEe = false;}
      if(alKiDUATaB == true){alKiDUATaB = false;}
      if(foexTXceuX == true){foexTXceuX = false;}
      if(ZauJcTayni == true){ZauJcTayni = false;}
      if(lxNJHqzppM == true){lxNJHqzppM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPIAQUJNEM
{ 
  void qQIutyykKr()
  { 
      bool gifCKBxcKG = false;
      bool JckIYFKOjb = false;
      bool siWAQHbtRd = false;
      bool tUoPkdXIWq = false;
      bool ykSajFoyud = false;
      bool JBLLQxLfkC = false;
      bool YDLfMnmVXu = false;
      bool gBrscIPwPL = false;
      bool SdzmUrIczm = false;
      bool RrWTRuYmOu = false;
      bool RSZzwIJShI = false;
      bool hOPZiuDXLT = false;
      bool fKWkdodXbh = false;
      bool ichTtzEApL = false;
      bool hptqFDbxjW = false;
      bool qBatPHwnVH = false;
      bool elpAYEgwfi = false;
      bool pDgzkpPefZ = false;
      bool NfmFpgBmEl = false;
      bool DPdigwztRA = false;
      string hYUWXnsiXQ;
      string upwfbWIFzT;
      string lSqeXFlIVt;
      string FpTPcYfnFN;
      string nuDIsmYCnc;
      string KhHmXOgozS;
      string CkNdLFWfDC;
      string qUzkfqPilk;
      string fjTriXhfrO;
      string rqomLChYwn;
      string QszllohVGg;
      string yyDOlSRUtn;
      string WpnoKAeMZd;
      string IqlyTmjhGs;
      string oMYLPsmaBs;
      string kMdIQZFKal;
      string KVwcXGMEty;
      string hiOByKQbYR;
      string MELgrwNcgs;
      string hZGUiTQwmJ;
      if(hYUWXnsiXQ == QszllohVGg){gifCKBxcKG = true;}
      else if(QszllohVGg == hYUWXnsiXQ){RSZzwIJShI = true;}
      if(upwfbWIFzT == yyDOlSRUtn){JckIYFKOjb = true;}
      else if(yyDOlSRUtn == upwfbWIFzT){hOPZiuDXLT = true;}
      if(lSqeXFlIVt == WpnoKAeMZd){siWAQHbtRd = true;}
      else if(WpnoKAeMZd == lSqeXFlIVt){fKWkdodXbh = true;}
      if(FpTPcYfnFN == IqlyTmjhGs){tUoPkdXIWq = true;}
      else if(IqlyTmjhGs == FpTPcYfnFN){ichTtzEApL = true;}
      if(nuDIsmYCnc == oMYLPsmaBs){ykSajFoyud = true;}
      else if(oMYLPsmaBs == nuDIsmYCnc){hptqFDbxjW = true;}
      if(KhHmXOgozS == kMdIQZFKal){JBLLQxLfkC = true;}
      else if(kMdIQZFKal == KhHmXOgozS){qBatPHwnVH = true;}
      if(CkNdLFWfDC == KVwcXGMEty){YDLfMnmVXu = true;}
      else if(KVwcXGMEty == CkNdLFWfDC){elpAYEgwfi = true;}
      if(qUzkfqPilk == hiOByKQbYR){gBrscIPwPL = true;}
      if(fjTriXhfrO == MELgrwNcgs){SdzmUrIczm = true;}
      if(rqomLChYwn == hZGUiTQwmJ){RrWTRuYmOu = true;}
      while(hiOByKQbYR == qUzkfqPilk){pDgzkpPefZ = true;}
      while(MELgrwNcgs == MELgrwNcgs){NfmFpgBmEl = true;}
      while(hZGUiTQwmJ == hZGUiTQwmJ){DPdigwztRA = true;}
      if(gifCKBxcKG == true){gifCKBxcKG = false;}
      if(JckIYFKOjb == true){JckIYFKOjb = false;}
      if(siWAQHbtRd == true){siWAQHbtRd = false;}
      if(tUoPkdXIWq == true){tUoPkdXIWq = false;}
      if(ykSajFoyud == true){ykSajFoyud = false;}
      if(JBLLQxLfkC == true){JBLLQxLfkC = false;}
      if(YDLfMnmVXu == true){YDLfMnmVXu = false;}
      if(gBrscIPwPL == true){gBrscIPwPL = false;}
      if(SdzmUrIczm == true){SdzmUrIczm = false;}
      if(RrWTRuYmOu == true){RrWTRuYmOu = false;}
      if(RSZzwIJShI == true){RSZzwIJShI = false;}
      if(hOPZiuDXLT == true){hOPZiuDXLT = false;}
      if(fKWkdodXbh == true){fKWkdodXbh = false;}
      if(ichTtzEApL == true){ichTtzEApL = false;}
      if(hptqFDbxjW == true){hptqFDbxjW = false;}
      if(qBatPHwnVH == true){qBatPHwnVH = false;}
      if(elpAYEgwfi == true){elpAYEgwfi = false;}
      if(pDgzkpPefZ == true){pDgzkpPefZ = false;}
      if(NfmFpgBmEl == true){NfmFpgBmEl = false;}
      if(DPdigwztRA == true){DPdigwztRA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHFSPWPUEW
{ 
  void VSYwCtMLNJ()
  { 
      bool WUCaiDxLOz = false;
      bool FzldNdZLJg = false;
      bool DyNthXKQMR = false;
      bool wZUmWjwztd = false;
      bool NVgKrWKBBo = false;
      bool hLdjXXHHrL = false;
      bool sfzwDeeyGc = false;
      bool haReShRDBL = false;
      bool MJPWjjwjPz = false;
      bool cnHhkhVkGN = false;
      bool rLuXHHtzRp = false;
      bool GDGgzjQcMT = false;
      bool htiHAsTitj = false;
      bool MfwnSANqPb = false;
      bool oxSZsYhZiA = false;
      bool RsYmexbmXN = false;
      bool nLEgcZHSNy = false;
      bool VYNjdkbJOb = false;
      bool LszsSTHIIU = false;
      bool XaTBncrkwS = false;
      string DfnOOEDZab;
      string hXrbtekzZf;
      string kBnCcKHZMi;
      string ZOgFaminyT;
      string QEJcVBUeoN;
      string RIciNCqkkE;
      string wdMqCSpmBG;
      string wwBFOgqLgb;
      string pckzQQkyqY;
      string wxDtXmqRaC;
      string KgdhRVHXTg;
      string KeDINTrNak;
      string hrucKzsGhb;
      string oYkeQIyCgu;
      string JNeJNQttfE;
      string tdqoTSkBXS;
      string bAoqrktYrF;
      string UpfeaTNlOs;
      string EyZdhLhuKx;
      string WxeOSIXmRb;
      if(DfnOOEDZab == KgdhRVHXTg){WUCaiDxLOz = true;}
      else if(KgdhRVHXTg == DfnOOEDZab){rLuXHHtzRp = true;}
      if(hXrbtekzZf == KeDINTrNak){FzldNdZLJg = true;}
      else if(KeDINTrNak == hXrbtekzZf){GDGgzjQcMT = true;}
      if(kBnCcKHZMi == hrucKzsGhb){DyNthXKQMR = true;}
      else if(hrucKzsGhb == kBnCcKHZMi){htiHAsTitj = true;}
      if(ZOgFaminyT == oYkeQIyCgu){wZUmWjwztd = true;}
      else if(oYkeQIyCgu == ZOgFaminyT){MfwnSANqPb = true;}
      if(QEJcVBUeoN == JNeJNQttfE){NVgKrWKBBo = true;}
      else if(JNeJNQttfE == QEJcVBUeoN){oxSZsYhZiA = true;}
      if(RIciNCqkkE == tdqoTSkBXS){hLdjXXHHrL = true;}
      else if(tdqoTSkBXS == RIciNCqkkE){RsYmexbmXN = true;}
      if(wdMqCSpmBG == bAoqrktYrF){sfzwDeeyGc = true;}
      else if(bAoqrktYrF == wdMqCSpmBG){nLEgcZHSNy = true;}
      if(wwBFOgqLgb == UpfeaTNlOs){haReShRDBL = true;}
      if(pckzQQkyqY == EyZdhLhuKx){MJPWjjwjPz = true;}
      if(wxDtXmqRaC == WxeOSIXmRb){cnHhkhVkGN = true;}
      while(UpfeaTNlOs == wwBFOgqLgb){VYNjdkbJOb = true;}
      while(EyZdhLhuKx == EyZdhLhuKx){LszsSTHIIU = true;}
      while(WxeOSIXmRb == WxeOSIXmRb){XaTBncrkwS = true;}
      if(WUCaiDxLOz == true){WUCaiDxLOz = false;}
      if(FzldNdZLJg == true){FzldNdZLJg = false;}
      if(DyNthXKQMR == true){DyNthXKQMR = false;}
      if(wZUmWjwztd == true){wZUmWjwztd = false;}
      if(NVgKrWKBBo == true){NVgKrWKBBo = false;}
      if(hLdjXXHHrL == true){hLdjXXHHrL = false;}
      if(sfzwDeeyGc == true){sfzwDeeyGc = false;}
      if(haReShRDBL == true){haReShRDBL = false;}
      if(MJPWjjwjPz == true){MJPWjjwjPz = false;}
      if(cnHhkhVkGN == true){cnHhkhVkGN = false;}
      if(rLuXHHtzRp == true){rLuXHHtzRp = false;}
      if(GDGgzjQcMT == true){GDGgzjQcMT = false;}
      if(htiHAsTitj == true){htiHAsTitj = false;}
      if(MfwnSANqPb == true){MfwnSANqPb = false;}
      if(oxSZsYhZiA == true){oxSZsYhZiA = false;}
      if(RsYmexbmXN == true){RsYmexbmXN = false;}
      if(nLEgcZHSNy == true){nLEgcZHSNy = false;}
      if(VYNjdkbJOb == true){VYNjdkbJOb = false;}
      if(LszsSTHIIU == true){LszsSTHIIU = false;}
      if(XaTBncrkwS == true){XaTBncrkwS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCRMQSGOKE
{ 
  void ltUlXWJfSm()
  { 
      bool MqLZSExjTL = false;
      bool kPLiDmcLAZ = false;
      bool fhTBgBCJHC = false;
      bool cyoAGknqjw = false;
      bool BWDbzZTXYl = false;
      bool RQhBmeWJrQ = false;
      bool BmcRilZLbR = false;
      bool ykaEYJdrCH = false;
      bool gdkUjLQnMa = false;
      bool OeyTtNtlrN = false;
      bool zIuHmgodcd = false;
      bool AeHkjXCHgW = false;
      bool VlyACTlHJK = false;
      bool OrzoHYichD = false;
      bool WlKiaiXNjW = false;
      bool LmFVqNJtET = false;
      bool ugTROIfRdK = false;
      bool oZYcAiaPZS = false;
      bool wYXmzbmdxt = false;
      bool OnXNIoSsTR = false;
      string YTUYHREWFp;
      string YlxzyjBDsy;
      string uffmutKkNQ;
      string HTRXJzuQBz;
      string BkymTGYumx;
      string TJLOQrmhdN;
      string HSJoiFUZpy;
      string ojCtxJhsTn;
      string UPyPwxICHQ;
      string MMmnqhbJDN;
      string kzEnHjHQQG;
      string KtNorrTssl;
      string wSRZlbxNCP;
      string gXoFDVKJHL;
      string oqkAGRzxwz;
      string OiQRRSgeCf;
      string ltOBYmFIlV;
      string gJkgxFhRTT;
      string czRCAyGXnj;
      string ofHbYtcibS;
      if(YTUYHREWFp == kzEnHjHQQG){MqLZSExjTL = true;}
      else if(kzEnHjHQQG == YTUYHREWFp){zIuHmgodcd = true;}
      if(YlxzyjBDsy == KtNorrTssl){kPLiDmcLAZ = true;}
      else if(KtNorrTssl == YlxzyjBDsy){AeHkjXCHgW = true;}
      if(uffmutKkNQ == wSRZlbxNCP){fhTBgBCJHC = true;}
      else if(wSRZlbxNCP == uffmutKkNQ){VlyACTlHJK = true;}
      if(HTRXJzuQBz == gXoFDVKJHL){cyoAGknqjw = true;}
      else if(gXoFDVKJHL == HTRXJzuQBz){OrzoHYichD = true;}
      if(BkymTGYumx == oqkAGRzxwz){BWDbzZTXYl = true;}
      else if(oqkAGRzxwz == BkymTGYumx){WlKiaiXNjW = true;}
      if(TJLOQrmhdN == OiQRRSgeCf){RQhBmeWJrQ = true;}
      else if(OiQRRSgeCf == TJLOQrmhdN){LmFVqNJtET = true;}
      if(HSJoiFUZpy == ltOBYmFIlV){BmcRilZLbR = true;}
      else if(ltOBYmFIlV == HSJoiFUZpy){ugTROIfRdK = true;}
      if(ojCtxJhsTn == gJkgxFhRTT){ykaEYJdrCH = true;}
      if(UPyPwxICHQ == czRCAyGXnj){gdkUjLQnMa = true;}
      if(MMmnqhbJDN == ofHbYtcibS){OeyTtNtlrN = true;}
      while(gJkgxFhRTT == ojCtxJhsTn){oZYcAiaPZS = true;}
      while(czRCAyGXnj == czRCAyGXnj){wYXmzbmdxt = true;}
      while(ofHbYtcibS == ofHbYtcibS){OnXNIoSsTR = true;}
      if(MqLZSExjTL == true){MqLZSExjTL = false;}
      if(kPLiDmcLAZ == true){kPLiDmcLAZ = false;}
      if(fhTBgBCJHC == true){fhTBgBCJHC = false;}
      if(cyoAGknqjw == true){cyoAGknqjw = false;}
      if(BWDbzZTXYl == true){BWDbzZTXYl = false;}
      if(RQhBmeWJrQ == true){RQhBmeWJrQ = false;}
      if(BmcRilZLbR == true){BmcRilZLbR = false;}
      if(ykaEYJdrCH == true){ykaEYJdrCH = false;}
      if(gdkUjLQnMa == true){gdkUjLQnMa = false;}
      if(OeyTtNtlrN == true){OeyTtNtlrN = false;}
      if(zIuHmgodcd == true){zIuHmgodcd = false;}
      if(AeHkjXCHgW == true){AeHkjXCHgW = false;}
      if(VlyACTlHJK == true){VlyACTlHJK = false;}
      if(OrzoHYichD == true){OrzoHYichD = false;}
      if(WlKiaiXNjW == true){WlKiaiXNjW = false;}
      if(LmFVqNJtET == true){LmFVqNJtET = false;}
      if(ugTROIfRdK == true){ugTROIfRdK = false;}
      if(oZYcAiaPZS == true){oZYcAiaPZS = false;}
      if(wYXmzbmdxt == true){wYXmzbmdxt = false;}
      if(OnXNIoSsTR == true){OnXNIoSsTR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJHTAECZXE
{ 
  void YxZinomtSy()
  { 
      bool iMqHdwnNij = false;
      bool oGKyXfPgOo = false;
      bool nGKxmGPrfW = false;
      bool RJhZzzbtbf = false;
      bool zwhkZCGImX = false;
      bool JLWXEbBsTW = false;
      bool fwgLReYjyY = false;
      bool DUFipqYZXk = false;
      bool zHEINFlJUW = false;
      bool yhZEzCOVTt = false;
      bool cWJOTnGnhN = false;
      bool DbViXYrYyL = false;
      bool rPPaaVuAjm = false;
      bool bCFcHcyonZ = false;
      bool zyaGSVLqga = false;
      bool KpXHCNGhny = false;
      bool sGDukBVsau = false;
      bool ZCkYMsnIIE = false;
      bool JDSJbldyZt = false;
      bool WPBpfstfVR = false;
      string ZRQpmaTBeF;
      string WZZzdkVmuW;
      string CehOSdazQY;
      string EBflrLqlUT;
      string xcoSJGctog;
      string DpXNjuiBXI;
      string zTjGBVsnGS;
      string siRbZZoOEM;
      string AgJjVOcSBx;
      string boNLTcshRn;
      string MomWnTXunK;
      string FUxLHRJAkl;
      string ralJpEUGHw;
      string gHwQzLtmuB;
      string pgdqqHrCEB;
      string TsxeukCcgj;
      string yRnrcyXfLw;
      string XWEiwLwuSi;
      string LSCGcnJRUO;
      string IRGLDYslNs;
      if(ZRQpmaTBeF == MomWnTXunK){iMqHdwnNij = true;}
      else if(MomWnTXunK == ZRQpmaTBeF){cWJOTnGnhN = true;}
      if(WZZzdkVmuW == FUxLHRJAkl){oGKyXfPgOo = true;}
      else if(FUxLHRJAkl == WZZzdkVmuW){DbViXYrYyL = true;}
      if(CehOSdazQY == ralJpEUGHw){nGKxmGPrfW = true;}
      else if(ralJpEUGHw == CehOSdazQY){rPPaaVuAjm = true;}
      if(EBflrLqlUT == gHwQzLtmuB){RJhZzzbtbf = true;}
      else if(gHwQzLtmuB == EBflrLqlUT){bCFcHcyonZ = true;}
      if(xcoSJGctog == pgdqqHrCEB){zwhkZCGImX = true;}
      else if(pgdqqHrCEB == xcoSJGctog){zyaGSVLqga = true;}
      if(DpXNjuiBXI == TsxeukCcgj){JLWXEbBsTW = true;}
      else if(TsxeukCcgj == DpXNjuiBXI){KpXHCNGhny = true;}
      if(zTjGBVsnGS == yRnrcyXfLw){fwgLReYjyY = true;}
      else if(yRnrcyXfLw == zTjGBVsnGS){sGDukBVsau = true;}
      if(siRbZZoOEM == XWEiwLwuSi){DUFipqYZXk = true;}
      if(AgJjVOcSBx == LSCGcnJRUO){zHEINFlJUW = true;}
      if(boNLTcshRn == IRGLDYslNs){yhZEzCOVTt = true;}
      while(XWEiwLwuSi == siRbZZoOEM){ZCkYMsnIIE = true;}
      while(LSCGcnJRUO == LSCGcnJRUO){JDSJbldyZt = true;}
      while(IRGLDYslNs == IRGLDYslNs){WPBpfstfVR = true;}
      if(iMqHdwnNij == true){iMqHdwnNij = false;}
      if(oGKyXfPgOo == true){oGKyXfPgOo = false;}
      if(nGKxmGPrfW == true){nGKxmGPrfW = false;}
      if(RJhZzzbtbf == true){RJhZzzbtbf = false;}
      if(zwhkZCGImX == true){zwhkZCGImX = false;}
      if(JLWXEbBsTW == true){JLWXEbBsTW = false;}
      if(fwgLReYjyY == true){fwgLReYjyY = false;}
      if(DUFipqYZXk == true){DUFipqYZXk = false;}
      if(zHEINFlJUW == true){zHEINFlJUW = false;}
      if(yhZEzCOVTt == true){yhZEzCOVTt = false;}
      if(cWJOTnGnhN == true){cWJOTnGnhN = false;}
      if(DbViXYrYyL == true){DbViXYrYyL = false;}
      if(rPPaaVuAjm == true){rPPaaVuAjm = false;}
      if(bCFcHcyonZ == true){bCFcHcyonZ = false;}
      if(zyaGSVLqga == true){zyaGSVLqga = false;}
      if(KpXHCNGhny == true){KpXHCNGhny = false;}
      if(sGDukBVsau == true){sGDukBVsau = false;}
      if(ZCkYMsnIIE == true){ZCkYMsnIIE = false;}
      if(JDSJbldyZt == true){JDSJbldyZt = false;}
      if(WPBpfstfVR == true){WPBpfstfVR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKVNCKKHGD
{ 
  void paPgIaTqte()
  { 
      bool VjQAVJquTs = false;
      bool HlaJizbQhf = false;
      bool WuusXyoOii = false;
      bool cOhdGSzqfA = false;
      bool HSGdWXHORc = false;
      bool SjoxhZoWbX = false;
      bool UbMkQsEwCP = false;
      bool zkkgXEoQWz = false;
      bool qZxFPsYjug = false;
      bool dbOHffGVNc = false;
      bool SKLBchzHZc = false;
      bool kXAcgtdGUX = false;
      bool TTAVlXWcBq = false;
      bool yTDsgfNwbh = false;
      bool tQKSuFalak = false;
      bool CzBpIzJpOF = false;
      bool KVGieRUGuA = false;
      bool fgdlcCIhZg = false;
      bool wjCPnzSNjg = false;
      bool WXhWWXKbnd = false;
      string YTBkUkXabz;
      string cuDuCRsmHU;
      string FtIXQEifsQ;
      string ypzrZwtEoc;
      string oqSrHtdGNO;
      string HpAHzeKdTQ;
      string BrgLAmuLUG;
      string WnxdfOaPPW;
      string ZcSeJHorru;
      string lQkYaxJHqU;
      string yRkGrSrVbj;
      string EtNwpYYCBs;
      string xDTZUFDYDh;
      string FTYuYIrLmq;
      string OSQHpqCnhC;
      string XGFyXtyKll;
      string OTSsekVSXh;
      string fNPKddlLjc;
      string CPqBKyNZXd;
      string KhYAbuAXcF;
      if(YTBkUkXabz == yRkGrSrVbj){VjQAVJquTs = true;}
      else if(yRkGrSrVbj == YTBkUkXabz){SKLBchzHZc = true;}
      if(cuDuCRsmHU == EtNwpYYCBs){HlaJizbQhf = true;}
      else if(EtNwpYYCBs == cuDuCRsmHU){kXAcgtdGUX = true;}
      if(FtIXQEifsQ == xDTZUFDYDh){WuusXyoOii = true;}
      else if(xDTZUFDYDh == FtIXQEifsQ){TTAVlXWcBq = true;}
      if(ypzrZwtEoc == FTYuYIrLmq){cOhdGSzqfA = true;}
      else if(FTYuYIrLmq == ypzrZwtEoc){yTDsgfNwbh = true;}
      if(oqSrHtdGNO == OSQHpqCnhC){HSGdWXHORc = true;}
      else if(OSQHpqCnhC == oqSrHtdGNO){tQKSuFalak = true;}
      if(HpAHzeKdTQ == XGFyXtyKll){SjoxhZoWbX = true;}
      else if(XGFyXtyKll == HpAHzeKdTQ){CzBpIzJpOF = true;}
      if(BrgLAmuLUG == OTSsekVSXh){UbMkQsEwCP = true;}
      else if(OTSsekVSXh == BrgLAmuLUG){KVGieRUGuA = true;}
      if(WnxdfOaPPW == fNPKddlLjc){zkkgXEoQWz = true;}
      if(ZcSeJHorru == CPqBKyNZXd){qZxFPsYjug = true;}
      if(lQkYaxJHqU == KhYAbuAXcF){dbOHffGVNc = true;}
      while(fNPKddlLjc == WnxdfOaPPW){fgdlcCIhZg = true;}
      while(CPqBKyNZXd == CPqBKyNZXd){wjCPnzSNjg = true;}
      while(KhYAbuAXcF == KhYAbuAXcF){WXhWWXKbnd = true;}
      if(VjQAVJquTs == true){VjQAVJquTs = false;}
      if(HlaJizbQhf == true){HlaJizbQhf = false;}
      if(WuusXyoOii == true){WuusXyoOii = false;}
      if(cOhdGSzqfA == true){cOhdGSzqfA = false;}
      if(HSGdWXHORc == true){HSGdWXHORc = false;}
      if(SjoxhZoWbX == true){SjoxhZoWbX = false;}
      if(UbMkQsEwCP == true){UbMkQsEwCP = false;}
      if(zkkgXEoQWz == true){zkkgXEoQWz = false;}
      if(qZxFPsYjug == true){qZxFPsYjug = false;}
      if(dbOHffGVNc == true){dbOHffGVNc = false;}
      if(SKLBchzHZc == true){SKLBchzHZc = false;}
      if(kXAcgtdGUX == true){kXAcgtdGUX = false;}
      if(TTAVlXWcBq == true){TTAVlXWcBq = false;}
      if(yTDsgfNwbh == true){yTDsgfNwbh = false;}
      if(tQKSuFalak == true){tQKSuFalak = false;}
      if(CzBpIzJpOF == true){CzBpIzJpOF = false;}
      if(KVGieRUGuA == true){KVGieRUGuA = false;}
      if(fgdlcCIhZg == true){fgdlcCIhZg = false;}
      if(wjCPnzSNjg == true){wjCPnzSNjg = false;}
      if(WXhWWXKbnd == true){WXhWWXKbnd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WTTBPCONSE
{ 
  void UHwBBYMfeU()
  { 
      bool peuxlyEmkZ = false;
      bool KKmPTIblII = false;
      bool jYxDQDStBj = false;
      bool ynfeIigQku = false;
      bool aCBcZPMiPY = false;
      bool iCUHZRhqgi = false;
      bool eJkBaVeIGk = false;
      bool aKBNggWTdA = false;
      bool piebAwSXEq = false;
      bool BojBPQRACE = false;
      bool kDcexXBHZr = false;
      bool tNNfrweJAe = false;
      bool CGEOilazxQ = false;
      bool PVRYPlGzdb = false;
      bool tLxLwnbDJT = false;
      bool kHzWBdzOwL = false;
      bool xCKJcYunQF = false;
      bool ofeYkqJrRt = false;
      bool KXpdeHWuXl = false;
      bool lqDSeqAmiX = false;
      string IlHuLmmRgo;
      string cKIxpcWpLQ;
      string WhLWHzdcWM;
      string AWQCzHiZZd;
      string HbtQFTLzyY;
      string uIDWwaajnM;
      string JKuTnFsFyh;
      string txPhItmuRm;
      string mddxQrTtFX;
      string gzkNUxfZbz;
      string aGBQdxrVNC;
      string meSBYefxDu;
      string lyzZBuMCML;
      string OMTRMgbNSS;
      string AyfDkBfjoo;
      string QiWfNbGbOi;
      string koICmZLBnq;
      string DRdjunRuoz;
      string OcNWtepmDj;
      string aAzjhKodPK;
      if(IlHuLmmRgo == aGBQdxrVNC){peuxlyEmkZ = true;}
      else if(aGBQdxrVNC == IlHuLmmRgo){kDcexXBHZr = true;}
      if(cKIxpcWpLQ == meSBYefxDu){KKmPTIblII = true;}
      else if(meSBYefxDu == cKIxpcWpLQ){tNNfrweJAe = true;}
      if(WhLWHzdcWM == lyzZBuMCML){jYxDQDStBj = true;}
      else if(lyzZBuMCML == WhLWHzdcWM){CGEOilazxQ = true;}
      if(AWQCzHiZZd == OMTRMgbNSS){ynfeIigQku = true;}
      else if(OMTRMgbNSS == AWQCzHiZZd){PVRYPlGzdb = true;}
      if(HbtQFTLzyY == AyfDkBfjoo){aCBcZPMiPY = true;}
      else if(AyfDkBfjoo == HbtQFTLzyY){tLxLwnbDJT = true;}
      if(uIDWwaajnM == QiWfNbGbOi){iCUHZRhqgi = true;}
      else if(QiWfNbGbOi == uIDWwaajnM){kHzWBdzOwL = true;}
      if(JKuTnFsFyh == koICmZLBnq){eJkBaVeIGk = true;}
      else if(koICmZLBnq == JKuTnFsFyh){xCKJcYunQF = true;}
      if(txPhItmuRm == DRdjunRuoz){aKBNggWTdA = true;}
      if(mddxQrTtFX == OcNWtepmDj){piebAwSXEq = true;}
      if(gzkNUxfZbz == aAzjhKodPK){BojBPQRACE = true;}
      while(DRdjunRuoz == txPhItmuRm){ofeYkqJrRt = true;}
      while(OcNWtepmDj == OcNWtepmDj){KXpdeHWuXl = true;}
      while(aAzjhKodPK == aAzjhKodPK){lqDSeqAmiX = true;}
      if(peuxlyEmkZ == true){peuxlyEmkZ = false;}
      if(KKmPTIblII == true){KKmPTIblII = false;}
      if(jYxDQDStBj == true){jYxDQDStBj = false;}
      if(ynfeIigQku == true){ynfeIigQku = false;}
      if(aCBcZPMiPY == true){aCBcZPMiPY = false;}
      if(iCUHZRhqgi == true){iCUHZRhqgi = false;}
      if(eJkBaVeIGk == true){eJkBaVeIGk = false;}
      if(aKBNggWTdA == true){aKBNggWTdA = false;}
      if(piebAwSXEq == true){piebAwSXEq = false;}
      if(BojBPQRACE == true){BojBPQRACE = false;}
      if(kDcexXBHZr == true){kDcexXBHZr = false;}
      if(tNNfrweJAe == true){tNNfrweJAe = false;}
      if(CGEOilazxQ == true){CGEOilazxQ = false;}
      if(PVRYPlGzdb == true){PVRYPlGzdb = false;}
      if(tLxLwnbDJT == true){tLxLwnbDJT = false;}
      if(kHzWBdzOwL == true){kHzWBdzOwL = false;}
      if(xCKJcYunQF == true){xCKJcYunQF = false;}
      if(ofeYkqJrRt == true){ofeYkqJrRt = false;}
      if(KXpdeHWuXl == true){KXpdeHWuXl = false;}
      if(lqDSeqAmiX == true){lqDSeqAmiX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DGQTFNHRVI
{ 
  void HurwQPfgTh()
  { 
      bool CoxDEdhUTV = false;
      bool duITiMkYre = false;
      bool rwcSQxEPXY = false;
      bool hrjQKDQNhB = false;
      bool JTUVbtcjOg = false;
      bool XOfUtFLemG = false;
      bool ZRwunkLqJe = false;
      bool wXqqUYbHqW = false;
      bool UUBpATMPVE = false;
      bool rlZabrWYhp = false;
      bool ikZjkAWozV = false;
      bool cEmQlFQGuT = false;
      bool YuUEmJxQOc = false;
      bool BCYAmitQEz = false;
      bool wXPAamyJoW = false;
      bool aQdNRmPVwb = false;
      bool DGZVTaflcC = false;
      bool LzBuXBfUdA = false;
      bool KmarBkYKiA = false;
      bool SXTcuoytgA = false;
      string OdUxRLTLuP;
      string TYJfqrDhTf;
      string JDQQRiDLNX;
      string fOXUkbVZUa;
      string kizeSJbauE;
      string oqdklLMDfi;
      string HHxWiFAouO;
      string WdMrtZDlxI;
      string HbPIhojmiZ;
      string ORslSckbuN;
      string IlffhLdkpL;
      string HaGXbeqoos;
      string UNGUAFjaZR;
      string napjzUwjaV;
      string LzxWRmLVJm;
      string lwmBrteKfc;
      string bCLXWfkVXG;
      string iHOShVQjCM;
      string sOQlfrnnrF;
      string okDytJnYzl;
      if(OdUxRLTLuP == IlffhLdkpL){CoxDEdhUTV = true;}
      else if(IlffhLdkpL == OdUxRLTLuP){ikZjkAWozV = true;}
      if(TYJfqrDhTf == HaGXbeqoos){duITiMkYre = true;}
      else if(HaGXbeqoos == TYJfqrDhTf){cEmQlFQGuT = true;}
      if(JDQQRiDLNX == UNGUAFjaZR){rwcSQxEPXY = true;}
      else if(UNGUAFjaZR == JDQQRiDLNX){YuUEmJxQOc = true;}
      if(fOXUkbVZUa == napjzUwjaV){hrjQKDQNhB = true;}
      else if(napjzUwjaV == fOXUkbVZUa){BCYAmitQEz = true;}
      if(kizeSJbauE == LzxWRmLVJm){JTUVbtcjOg = true;}
      else if(LzxWRmLVJm == kizeSJbauE){wXPAamyJoW = true;}
      if(oqdklLMDfi == lwmBrteKfc){XOfUtFLemG = true;}
      else if(lwmBrteKfc == oqdklLMDfi){aQdNRmPVwb = true;}
      if(HHxWiFAouO == bCLXWfkVXG){ZRwunkLqJe = true;}
      else if(bCLXWfkVXG == HHxWiFAouO){DGZVTaflcC = true;}
      if(WdMrtZDlxI == iHOShVQjCM){wXqqUYbHqW = true;}
      if(HbPIhojmiZ == sOQlfrnnrF){UUBpATMPVE = true;}
      if(ORslSckbuN == okDytJnYzl){rlZabrWYhp = true;}
      while(iHOShVQjCM == WdMrtZDlxI){LzBuXBfUdA = true;}
      while(sOQlfrnnrF == sOQlfrnnrF){KmarBkYKiA = true;}
      while(okDytJnYzl == okDytJnYzl){SXTcuoytgA = true;}
      if(CoxDEdhUTV == true){CoxDEdhUTV = false;}
      if(duITiMkYre == true){duITiMkYre = false;}
      if(rwcSQxEPXY == true){rwcSQxEPXY = false;}
      if(hrjQKDQNhB == true){hrjQKDQNhB = false;}
      if(JTUVbtcjOg == true){JTUVbtcjOg = false;}
      if(XOfUtFLemG == true){XOfUtFLemG = false;}
      if(ZRwunkLqJe == true){ZRwunkLqJe = false;}
      if(wXqqUYbHqW == true){wXqqUYbHqW = false;}
      if(UUBpATMPVE == true){UUBpATMPVE = false;}
      if(rlZabrWYhp == true){rlZabrWYhp = false;}
      if(ikZjkAWozV == true){ikZjkAWozV = false;}
      if(cEmQlFQGuT == true){cEmQlFQGuT = false;}
      if(YuUEmJxQOc == true){YuUEmJxQOc = false;}
      if(BCYAmitQEz == true){BCYAmitQEz = false;}
      if(wXPAamyJoW == true){wXPAamyJoW = false;}
      if(aQdNRmPVwb == true){aQdNRmPVwb = false;}
      if(DGZVTaflcC == true){DGZVTaflcC = false;}
      if(LzBuXBfUdA == true){LzBuXBfUdA = false;}
      if(KmarBkYKiA == true){KmarBkYKiA = false;}
      if(SXTcuoytgA == true){SXTcuoytgA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIUTOWPUDN
{ 
  void DrOHgBBkQV()
  { 
      bool GziGYnqZMk = false;
      bool LmMsXFgTWs = false;
      bool qmifVqsmKL = false;
      bool NTygGzutQQ = false;
      bool iXaYZMWSek = false;
      bool NXKAnTPDkg = false;
      bool tDOBXqnelX = false;
      bool KmDGKSLKFI = false;
      bool UaIZxpJysm = false;
      bool jqJiVfJZBi = false;
      bool YqgGZaTDoU = false;
      bool HFybMTtoDh = false;
      bool golynSdUje = false;
      bool JlJWjdsCzW = false;
      bool VFJYeesgVC = false;
      bool kUVSBiFhRG = false;
      bool xzSKKVubqi = false;
      bool ZrogMafNTJ = false;
      bool ZwyhsoPpUB = false;
      bool XLjrYVmyNJ = false;
      string AefcVnczch;
      string SRUsVHCJEY;
      string RGlqoAnjoG;
      string JQXYcJaFAh;
      string JJbbxRhXOx;
      string NUToissnmU;
      string zrKVYCtuQM;
      string fxIWOHeKtW;
      string SQUrroxioi;
      string QmRehQzFCt;
      string XlHCQQLxZb;
      string OhsQCiXRdi;
      string EKGhusfdnx;
      string HYHzyfISab;
      string cAJNUhsBcz;
      string shbTpMfZGX;
      string khIbToasRV;
      string ZFpBGEBrMN;
      string zeAoEZxnJk;
      string AiLDquqgse;
      if(AefcVnczch == XlHCQQLxZb){GziGYnqZMk = true;}
      else if(XlHCQQLxZb == AefcVnczch){YqgGZaTDoU = true;}
      if(SRUsVHCJEY == OhsQCiXRdi){LmMsXFgTWs = true;}
      else if(OhsQCiXRdi == SRUsVHCJEY){HFybMTtoDh = true;}
      if(RGlqoAnjoG == EKGhusfdnx){qmifVqsmKL = true;}
      else if(EKGhusfdnx == RGlqoAnjoG){golynSdUje = true;}
      if(JQXYcJaFAh == HYHzyfISab){NTygGzutQQ = true;}
      else if(HYHzyfISab == JQXYcJaFAh){JlJWjdsCzW = true;}
      if(JJbbxRhXOx == cAJNUhsBcz){iXaYZMWSek = true;}
      else if(cAJNUhsBcz == JJbbxRhXOx){VFJYeesgVC = true;}
      if(NUToissnmU == shbTpMfZGX){NXKAnTPDkg = true;}
      else if(shbTpMfZGX == NUToissnmU){kUVSBiFhRG = true;}
      if(zrKVYCtuQM == khIbToasRV){tDOBXqnelX = true;}
      else if(khIbToasRV == zrKVYCtuQM){xzSKKVubqi = true;}
      if(fxIWOHeKtW == ZFpBGEBrMN){KmDGKSLKFI = true;}
      if(SQUrroxioi == zeAoEZxnJk){UaIZxpJysm = true;}
      if(QmRehQzFCt == AiLDquqgse){jqJiVfJZBi = true;}
      while(ZFpBGEBrMN == fxIWOHeKtW){ZrogMafNTJ = true;}
      while(zeAoEZxnJk == zeAoEZxnJk){ZwyhsoPpUB = true;}
      while(AiLDquqgse == AiLDquqgse){XLjrYVmyNJ = true;}
      if(GziGYnqZMk == true){GziGYnqZMk = false;}
      if(LmMsXFgTWs == true){LmMsXFgTWs = false;}
      if(qmifVqsmKL == true){qmifVqsmKL = false;}
      if(NTygGzutQQ == true){NTygGzutQQ = false;}
      if(iXaYZMWSek == true){iXaYZMWSek = false;}
      if(NXKAnTPDkg == true){NXKAnTPDkg = false;}
      if(tDOBXqnelX == true){tDOBXqnelX = false;}
      if(KmDGKSLKFI == true){KmDGKSLKFI = false;}
      if(UaIZxpJysm == true){UaIZxpJysm = false;}
      if(jqJiVfJZBi == true){jqJiVfJZBi = false;}
      if(YqgGZaTDoU == true){YqgGZaTDoU = false;}
      if(HFybMTtoDh == true){HFybMTtoDh = false;}
      if(golynSdUje == true){golynSdUje = false;}
      if(JlJWjdsCzW == true){JlJWjdsCzW = false;}
      if(VFJYeesgVC == true){VFJYeesgVC = false;}
      if(kUVSBiFhRG == true){kUVSBiFhRG = false;}
      if(xzSKKVubqi == true){xzSKKVubqi = false;}
      if(ZrogMafNTJ == true){ZrogMafNTJ = false;}
      if(ZwyhsoPpUB == true){ZwyhsoPpUB = false;}
      if(XLjrYVmyNJ == true){XLjrYVmyNJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIVNWQWMTU
{ 
  void aRmnOByKsY()
  { 
      bool adRfLUhZcj = false;
      bool KxQirjbkbx = false;
      bool lOxwObCGJV = false;
      bool oYOVjsKTqt = false;
      bool jDQCbAWakR = false;
      bool XkVIdLgVRj = false;
      bool RaPGtkhtyz = false;
      bool YIshMhyuUO = false;
      bool FaVrxECGqY = false;
      bool MoBHbJnJHp = false;
      bool RbblsPrnuw = false;
      bool MkADdqFXIp = false;
      bool haCZliGkGD = false;
      bool tnndwcyizh = false;
      bool LOKuLanyck = false;
      bool DQARIqZCzJ = false;
      bool JGgrCYxVHB = false;
      bool rVXadSPHOL = false;
      bool uIIVzdmWVF = false;
      bool DwipXFhSsl = false;
      string ajpYgaUzIZ;
      string LDMzOSEZGz;
      string MSnWFkKMUc;
      string dJLDUhAWOu;
      string FcquUnPAUV;
      string XfehiHuTTw;
      string PHeewBqIeg;
      string SgLKtibrBQ;
      string UKqyExedTM;
      string lfDSfxyLzS;
      string wGUnDpUTmz;
      string fCRCaEPfZz;
      string WNoStldrew;
      string kPshUOoDuO;
      string cKpUfjNAra;
      string gSlzwhRCsQ;
      string MbnqOPIjhL;
      string OMkLWLXUlK;
      string XcADORdtll;
      string xmJdBAVyFP;
      if(ajpYgaUzIZ == wGUnDpUTmz){adRfLUhZcj = true;}
      else if(wGUnDpUTmz == ajpYgaUzIZ){RbblsPrnuw = true;}
      if(LDMzOSEZGz == fCRCaEPfZz){KxQirjbkbx = true;}
      else if(fCRCaEPfZz == LDMzOSEZGz){MkADdqFXIp = true;}
      if(MSnWFkKMUc == WNoStldrew){lOxwObCGJV = true;}
      else if(WNoStldrew == MSnWFkKMUc){haCZliGkGD = true;}
      if(dJLDUhAWOu == kPshUOoDuO){oYOVjsKTqt = true;}
      else if(kPshUOoDuO == dJLDUhAWOu){tnndwcyizh = true;}
      if(FcquUnPAUV == cKpUfjNAra){jDQCbAWakR = true;}
      else if(cKpUfjNAra == FcquUnPAUV){LOKuLanyck = true;}
      if(XfehiHuTTw == gSlzwhRCsQ){XkVIdLgVRj = true;}
      else if(gSlzwhRCsQ == XfehiHuTTw){DQARIqZCzJ = true;}
      if(PHeewBqIeg == MbnqOPIjhL){RaPGtkhtyz = true;}
      else if(MbnqOPIjhL == PHeewBqIeg){JGgrCYxVHB = true;}
      if(SgLKtibrBQ == OMkLWLXUlK){YIshMhyuUO = true;}
      if(UKqyExedTM == XcADORdtll){FaVrxECGqY = true;}
      if(lfDSfxyLzS == xmJdBAVyFP){MoBHbJnJHp = true;}
      while(OMkLWLXUlK == SgLKtibrBQ){rVXadSPHOL = true;}
      while(XcADORdtll == XcADORdtll){uIIVzdmWVF = true;}
      while(xmJdBAVyFP == xmJdBAVyFP){DwipXFhSsl = true;}
      if(adRfLUhZcj == true){adRfLUhZcj = false;}
      if(KxQirjbkbx == true){KxQirjbkbx = false;}
      if(lOxwObCGJV == true){lOxwObCGJV = false;}
      if(oYOVjsKTqt == true){oYOVjsKTqt = false;}
      if(jDQCbAWakR == true){jDQCbAWakR = false;}
      if(XkVIdLgVRj == true){XkVIdLgVRj = false;}
      if(RaPGtkhtyz == true){RaPGtkhtyz = false;}
      if(YIshMhyuUO == true){YIshMhyuUO = false;}
      if(FaVrxECGqY == true){FaVrxECGqY = false;}
      if(MoBHbJnJHp == true){MoBHbJnJHp = false;}
      if(RbblsPrnuw == true){RbblsPrnuw = false;}
      if(MkADdqFXIp == true){MkADdqFXIp = false;}
      if(haCZliGkGD == true){haCZliGkGD = false;}
      if(tnndwcyizh == true){tnndwcyizh = false;}
      if(LOKuLanyck == true){LOKuLanyck = false;}
      if(DQARIqZCzJ == true){DQARIqZCzJ = false;}
      if(JGgrCYxVHB == true){JGgrCYxVHB = false;}
      if(rVXadSPHOL == true){rVXadSPHOL = false;}
      if(uIIVzdmWVF == true){uIIVzdmWVF = false;}
      if(DwipXFhSsl == true){DwipXFhSsl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REZTBUMIJJ
{ 
  void dHoxbCBzZA()
  { 
      bool MJAmPuGnQs = false;
      bool ApFQWfoTPj = false;
      bool BhRjGDYAbJ = false;
      bool pAziGXOysk = false;
      bool XXQRCQAAqP = false;
      bool MwqGBdqQfM = false;
      bool VGLGDzpWKy = false;
      bool QpaeMdRAgo = false;
      bool DXILxsJsgb = false;
      bool fySfPRLJOD = false;
      bool acprzWVMtX = false;
      bool MqipJxxAJJ = false;
      bool pxohRSXuOt = false;
      bool RHldOZhQMZ = false;
      bool XxyJPoObWR = false;
      bool ULAEMdnHZf = false;
      bool yZxAGEFFbj = false;
      bool PfmilszfSc = false;
      bool EwYxZFHgQj = false;
      bool kZqgbxzyCL = false;
      string NabIkxrwdY;
      string lMCwzeEQsJ;
      string jcZYeNwNTa;
      string sdhknCfPaf;
      string KgdxJzuDdY;
      string lDYORkBDdW;
      string AdcDeHeQHx;
      string ynpNzDybOe;
      string SsjtnpFSTD;
      string BclEffDaRC;
      string TdugaxMKON;
      string lYoyDGthOo;
      string BLwDuVClhS;
      string zXJLLoxDTq;
      string ctDFRbmmAY;
      string lULcAIgrkF;
      string uacwONPcmN;
      string IqOXMHHqlT;
      string hOkIfdMgKD;
      string HFROuCQHqD;
      if(NabIkxrwdY == TdugaxMKON){MJAmPuGnQs = true;}
      else if(TdugaxMKON == NabIkxrwdY){acprzWVMtX = true;}
      if(lMCwzeEQsJ == lYoyDGthOo){ApFQWfoTPj = true;}
      else if(lYoyDGthOo == lMCwzeEQsJ){MqipJxxAJJ = true;}
      if(jcZYeNwNTa == BLwDuVClhS){BhRjGDYAbJ = true;}
      else if(BLwDuVClhS == jcZYeNwNTa){pxohRSXuOt = true;}
      if(sdhknCfPaf == zXJLLoxDTq){pAziGXOysk = true;}
      else if(zXJLLoxDTq == sdhknCfPaf){RHldOZhQMZ = true;}
      if(KgdxJzuDdY == ctDFRbmmAY){XXQRCQAAqP = true;}
      else if(ctDFRbmmAY == KgdxJzuDdY){XxyJPoObWR = true;}
      if(lDYORkBDdW == lULcAIgrkF){MwqGBdqQfM = true;}
      else if(lULcAIgrkF == lDYORkBDdW){ULAEMdnHZf = true;}
      if(AdcDeHeQHx == uacwONPcmN){VGLGDzpWKy = true;}
      else if(uacwONPcmN == AdcDeHeQHx){yZxAGEFFbj = true;}
      if(ynpNzDybOe == IqOXMHHqlT){QpaeMdRAgo = true;}
      if(SsjtnpFSTD == hOkIfdMgKD){DXILxsJsgb = true;}
      if(BclEffDaRC == HFROuCQHqD){fySfPRLJOD = true;}
      while(IqOXMHHqlT == ynpNzDybOe){PfmilszfSc = true;}
      while(hOkIfdMgKD == hOkIfdMgKD){EwYxZFHgQj = true;}
      while(HFROuCQHqD == HFROuCQHqD){kZqgbxzyCL = true;}
      if(MJAmPuGnQs == true){MJAmPuGnQs = false;}
      if(ApFQWfoTPj == true){ApFQWfoTPj = false;}
      if(BhRjGDYAbJ == true){BhRjGDYAbJ = false;}
      if(pAziGXOysk == true){pAziGXOysk = false;}
      if(XXQRCQAAqP == true){XXQRCQAAqP = false;}
      if(MwqGBdqQfM == true){MwqGBdqQfM = false;}
      if(VGLGDzpWKy == true){VGLGDzpWKy = false;}
      if(QpaeMdRAgo == true){QpaeMdRAgo = false;}
      if(DXILxsJsgb == true){DXILxsJsgb = false;}
      if(fySfPRLJOD == true){fySfPRLJOD = false;}
      if(acprzWVMtX == true){acprzWVMtX = false;}
      if(MqipJxxAJJ == true){MqipJxxAJJ = false;}
      if(pxohRSXuOt == true){pxohRSXuOt = false;}
      if(RHldOZhQMZ == true){RHldOZhQMZ = false;}
      if(XxyJPoObWR == true){XxyJPoObWR = false;}
      if(ULAEMdnHZf == true){ULAEMdnHZf = false;}
      if(yZxAGEFFbj == true){yZxAGEFFbj = false;}
      if(PfmilszfSc == true){PfmilszfSc = false;}
      if(EwYxZFHgQj == true){EwYxZFHgQj = false;}
      if(kZqgbxzyCL == true){kZqgbxzyCL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHUWLHHNLV
{ 
  void rgJwEIRJnq()
  { 
      bool IfNTNgDNGj = false;
      bool XCZWObTQlN = false;
      bool KqKwkWDFSb = false;
      bool AWNQeQSqzC = false;
      bool sUuYLNaMmI = false;
      bool WqdpaQURhq = false;
      bool cytejBoJry = false;
      bool JbQjTpwlkX = false;
      bool uqSJEIrXoO = false;
      bool uBJHYuZQoJ = false;
      bool YRUnztZtVj = false;
      bool ThfJwlekZa = false;
      bool IQTcCHSJLY = false;
      bool QfxazdVdKJ = false;
      bool iyBEtMUzKl = false;
      bool QnpNAHxqlq = false;
      bool bQhxTnkFKS = false;
      bool PAZPrKOPho = false;
      bool mSyYIboiZq = false;
      bool gdrThRPEkG = false;
      string LfzKoxlktD;
      string qZKfqEccWl;
      string HGWlCLEHwP;
      string hhorbfjemg;
      string fTrhwVVOMb;
      string jBSdIFJMIc;
      string rdndUJkSEL;
      string TypoFnNnpf;
      string oouUfgOKjW;
      string WWWJoCeONm;
      string kDKAHkLcYT;
      string qUWbnChTyn;
      string tZhhowbgzD;
      string IyaCuleuMt;
      string VklPeBAtVl;
      string TLQYsLUcKK;
      string JedVLssUfC;
      string XmHDSImSCm;
      string wgKNixhBJj;
      string QBjBkpHQEl;
      if(LfzKoxlktD == kDKAHkLcYT){IfNTNgDNGj = true;}
      else if(kDKAHkLcYT == LfzKoxlktD){YRUnztZtVj = true;}
      if(qZKfqEccWl == qUWbnChTyn){XCZWObTQlN = true;}
      else if(qUWbnChTyn == qZKfqEccWl){ThfJwlekZa = true;}
      if(HGWlCLEHwP == tZhhowbgzD){KqKwkWDFSb = true;}
      else if(tZhhowbgzD == HGWlCLEHwP){IQTcCHSJLY = true;}
      if(hhorbfjemg == IyaCuleuMt){AWNQeQSqzC = true;}
      else if(IyaCuleuMt == hhorbfjemg){QfxazdVdKJ = true;}
      if(fTrhwVVOMb == VklPeBAtVl){sUuYLNaMmI = true;}
      else if(VklPeBAtVl == fTrhwVVOMb){iyBEtMUzKl = true;}
      if(jBSdIFJMIc == TLQYsLUcKK){WqdpaQURhq = true;}
      else if(TLQYsLUcKK == jBSdIFJMIc){QnpNAHxqlq = true;}
      if(rdndUJkSEL == JedVLssUfC){cytejBoJry = true;}
      else if(JedVLssUfC == rdndUJkSEL){bQhxTnkFKS = true;}
      if(TypoFnNnpf == XmHDSImSCm){JbQjTpwlkX = true;}
      if(oouUfgOKjW == wgKNixhBJj){uqSJEIrXoO = true;}
      if(WWWJoCeONm == QBjBkpHQEl){uBJHYuZQoJ = true;}
      while(XmHDSImSCm == TypoFnNnpf){PAZPrKOPho = true;}
      while(wgKNixhBJj == wgKNixhBJj){mSyYIboiZq = true;}
      while(QBjBkpHQEl == QBjBkpHQEl){gdrThRPEkG = true;}
      if(IfNTNgDNGj == true){IfNTNgDNGj = false;}
      if(XCZWObTQlN == true){XCZWObTQlN = false;}
      if(KqKwkWDFSb == true){KqKwkWDFSb = false;}
      if(AWNQeQSqzC == true){AWNQeQSqzC = false;}
      if(sUuYLNaMmI == true){sUuYLNaMmI = false;}
      if(WqdpaQURhq == true){WqdpaQURhq = false;}
      if(cytejBoJry == true){cytejBoJry = false;}
      if(JbQjTpwlkX == true){JbQjTpwlkX = false;}
      if(uqSJEIrXoO == true){uqSJEIrXoO = false;}
      if(uBJHYuZQoJ == true){uBJHYuZQoJ = false;}
      if(YRUnztZtVj == true){YRUnztZtVj = false;}
      if(ThfJwlekZa == true){ThfJwlekZa = false;}
      if(IQTcCHSJLY == true){IQTcCHSJLY = false;}
      if(QfxazdVdKJ == true){QfxazdVdKJ = false;}
      if(iyBEtMUzKl == true){iyBEtMUzKl = false;}
      if(QnpNAHxqlq == true){QnpNAHxqlq = false;}
      if(bQhxTnkFKS == true){bQhxTnkFKS = false;}
      if(PAZPrKOPho == true){PAZPrKOPho = false;}
      if(mSyYIboiZq == true){mSyYIboiZq = false;}
      if(gdrThRPEkG == true){gdrThRPEkG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPHZSORMCX
{ 
  void EubqxWppXK()
  { 
      bool WBnqRAfQBp = false;
      bool bsZIUsFxmH = false;
      bool gIpQGXOfTF = false;
      bool AFrmfckoNk = false;
      bool nHCQPXjQzA = false;
      bool FteccOKWjt = false;
      bool kzwwpWAmbr = false;
      bool HQjBSYFZBi = false;
      bool nygTzGZPJR = false;
      bool SOFSAoLGar = false;
      bool WwnHroKdKD = false;
      bool IkVAGmScwi = false;
      bool xkcKYsKQAd = false;
      bool NzyILqJYbK = false;
      bool wuEFIhrEMN = false;
      bool ViKrukSdhy = false;
      bool dtcfpJmMoO = false;
      bool csAklBfXBq = false;
      bool AGDmHeoFMa = false;
      bool XfpdgCRYPy = false;
      string IFzeRozUpg;
      string bhCkEjYWDM;
      string apXXYzBoyN;
      string nkdUtAQDwF;
      string XXhWlSueEz;
      string KIHmeShaGS;
      string mKVcrpEgqE;
      string TUZxnCIAlF;
      string EWkzCedpob;
      string RoxdRNCEeu;
      string OOnzephJzc;
      string KhoANQZVZM;
      string MOqPmeWwfZ;
      string ADVpqoikUM;
      string xUqMRiAxPA;
      string nfdRizXXLA;
      string SlcYbGMyIY;
      string hnANPrXdxD;
      string eZfflTYEHq;
      string RKYUsKqRkK;
      if(IFzeRozUpg == OOnzephJzc){WBnqRAfQBp = true;}
      else if(OOnzephJzc == IFzeRozUpg){WwnHroKdKD = true;}
      if(bhCkEjYWDM == KhoANQZVZM){bsZIUsFxmH = true;}
      else if(KhoANQZVZM == bhCkEjYWDM){IkVAGmScwi = true;}
      if(apXXYzBoyN == MOqPmeWwfZ){gIpQGXOfTF = true;}
      else if(MOqPmeWwfZ == apXXYzBoyN){xkcKYsKQAd = true;}
      if(nkdUtAQDwF == ADVpqoikUM){AFrmfckoNk = true;}
      else if(ADVpqoikUM == nkdUtAQDwF){NzyILqJYbK = true;}
      if(XXhWlSueEz == xUqMRiAxPA){nHCQPXjQzA = true;}
      else if(xUqMRiAxPA == XXhWlSueEz){wuEFIhrEMN = true;}
      if(KIHmeShaGS == nfdRizXXLA){FteccOKWjt = true;}
      else if(nfdRizXXLA == KIHmeShaGS){ViKrukSdhy = true;}
      if(mKVcrpEgqE == SlcYbGMyIY){kzwwpWAmbr = true;}
      else if(SlcYbGMyIY == mKVcrpEgqE){dtcfpJmMoO = true;}
      if(TUZxnCIAlF == hnANPrXdxD){HQjBSYFZBi = true;}
      if(EWkzCedpob == eZfflTYEHq){nygTzGZPJR = true;}
      if(RoxdRNCEeu == RKYUsKqRkK){SOFSAoLGar = true;}
      while(hnANPrXdxD == TUZxnCIAlF){csAklBfXBq = true;}
      while(eZfflTYEHq == eZfflTYEHq){AGDmHeoFMa = true;}
      while(RKYUsKqRkK == RKYUsKqRkK){XfpdgCRYPy = true;}
      if(WBnqRAfQBp == true){WBnqRAfQBp = false;}
      if(bsZIUsFxmH == true){bsZIUsFxmH = false;}
      if(gIpQGXOfTF == true){gIpQGXOfTF = false;}
      if(AFrmfckoNk == true){AFrmfckoNk = false;}
      if(nHCQPXjQzA == true){nHCQPXjQzA = false;}
      if(FteccOKWjt == true){FteccOKWjt = false;}
      if(kzwwpWAmbr == true){kzwwpWAmbr = false;}
      if(HQjBSYFZBi == true){HQjBSYFZBi = false;}
      if(nygTzGZPJR == true){nygTzGZPJR = false;}
      if(SOFSAoLGar == true){SOFSAoLGar = false;}
      if(WwnHroKdKD == true){WwnHroKdKD = false;}
      if(IkVAGmScwi == true){IkVAGmScwi = false;}
      if(xkcKYsKQAd == true){xkcKYsKQAd = false;}
      if(NzyILqJYbK == true){NzyILqJYbK = false;}
      if(wuEFIhrEMN == true){wuEFIhrEMN = false;}
      if(ViKrukSdhy == true){ViKrukSdhy = false;}
      if(dtcfpJmMoO == true){dtcfpJmMoO = false;}
      if(csAklBfXBq == true){csAklBfXBq = false;}
      if(AGDmHeoFMa == true){AGDmHeoFMa = false;}
      if(XfpdgCRYPy == true){XfpdgCRYPy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUCEBVSSAO
{ 
  void bAAPkaVLEE()
  { 
      bool kEwWpYUYpY = false;
      bool tYwIegDPtl = false;
      bool SpoHZgALpo = false;
      bool ARPpmwNKRH = false;
      bool DAcfnzVPao = false;
      bool moEsltPoxJ = false;
      bool XIhBXcJFVh = false;
      bool SsyliSNISa = false;
      bool LkkBBKNWEr = false;
      bool gYNIjtSaIL = false;
      bool oPssVtqRKS = false;
      bool fHVWxlXgzM = false;
      bool OmAcBtepCn = false;
      bool AlzHkuqreH = false;
      bool TuMlMZDqKy = false;
      bool WlbuwCOQqb = false;
      bool OBPVSsHOkB = false;
      bool tfBqsSaOQb = false;
      bool pneDROKEKi = false;
      bool gaACsRfpSS = false;
      string ylaItgnryz;
      string xJgXRmfVzH;
      string HUVwXDbJZQ;
      string YPmidHJJED;
      string EHuEwZEfHJ;
      string MHQIVcPejp;
      string FdSgZhVytJ;
      string dWRwDAZRzy;
      string zwBQERyeMA;
      string rdYNyZoOdO;
      string DFkxeooUEV;
      string DxelqJcCbH;
      string iqksRzxDxd;
      string KKnkusKDkO;
      string bcZpxtymVo;
      string xllVeLUrfe;
      string rlXaKrJtpy;
      string zYRNeGQuuX;
      string AKhHfYYSFi;
      string YRXFWpFzeF;
      if(ylaItgnryz == DFkxeooUEV){kEwWpYUYpY = true;}
      else if(DFkxeooUEV == ylaItgnryz){oPssVtqRKS = true;}
      if(xJgXRmfVzH == DxelqJcCbH){tYwIegDPtl = true;}
      else if(DxelqJcCbH == xJgXRmfVzH){fHVWxlXgzM = true;}
      if(HUVwXDbJZQ == iqksRzxDxd){SpoHZgALpo = true;}
      else if(iqksRzxDxd == HUVwXDbJZQ){OmAcBtepCn = true;}
      if(YPmidHJJED == KKnkusKDkO){ARPpmwNKRH = true;}
      else if(KKnkusKDkO == YPmidHJJED){AlzHkuqreH = true;}
      if(EHuEwZEfHJ == bcZpxtymVo){DAcfnzVPao = true;}
      else if(bcZpxtymVo == EHuEwZEfHJ){TuMlMZDqKy = true;}
      if(MHQIVcPejp == xllVeLUrfe){moEsltPoxJ = true;}
      else if(xllVeLUrfe == MHQIVcPejp){WlbuwCOQqb = true;}
      if(FdSgZhVytJ == rlXaKrJtpy){XIhBXcJFVh = true;}
      else if(rlXaKrJtpy == FdSgZhVytJ){OBPVSsHOkB = true;}
      if(dWRwDAZRzy == zYRNeGQuuX){SsyliSNISa = true;}
      if(zwBQERyeMA == AKhHfYYSFi){LkkBBKNWEr = true;}
      if(rdYNyZoOdO == YRXFWpFzeF){gYNIjtSaIL = true;}
      while(zYRNeGQuuX == dWRwDAZRzy){tfBqsSaOQb = true;}
      while(AKhHfYYSFi == AKhHfYYSFi){pneDROKEKi = true;}
      while(YRXFWpFzeF == YRXFWpFzeF){gaACsRfpSS = true;}
      if(kEwWpYUYpY == true){kEwWpYUYpY = false;}
      if(tYwIegDPtl == true){tYwIegDPtl = false;}
      if(SpoHZgALpo == true){SpoHZgALpo = false;}
      if(ARPpmwNKRH == true){ARPpmwNKRH = false;}
      if(DAcfnzVPao == true){DAcfnzVPao = false;}
      if(moEsltPoxJ == true){moEsltPoxJ = false;}
      if(XIhBXcJFVh == true){XIhBXcJFVh = false;}
      if(SsyliSNISa == true){SsyliSNISa = false;}
      if(LkkBBKNWEr == true){LkkBBKNWEr = false;}
      if(gYNIjtSaIL == true){gYNIjtSaIL = false;}
      if(oPssVtqRKS == true){oPssVtqRKS = false;}
      if(fHVWxlXgzM == true){fHVWxlXgzM = false;}
      if(OmAcBtepCn == true){OmAcBtepCn = false;}
      if(AlzHkuqreH == true){AlzHkuqreH = false;}
      if(TuMlMZDqKy == true){TuMlMZDqKy = false;}
      if(WlbuwCOQqb == true){WlbuwCOQqb = false;}
      if(OBPVSsHOkB == true){OBPVSsHOkB = false;}
      if(tfBqsSaOQb == true){tfBqsSaOQb = false;}
      if(pneDROKEKi == true){pneDROKEKi = false;}
      if(gaACsRfpSS == true){gaACsRfpSS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIIBELKXTZ
{ 
  void axzuXcxmFW()
  { 
      bool opwUDPrsTc = false;
      bool fFlsfJeSSR = false;
      bool bFJhAtJxGW = false;
      bool BgOsDaecRU = false;
      bool XfjdRlcbcM = false;
      bool RRQfUigNTJ = false;
      bool GulwayprpE = false;
      bool eCAysuVePO = false;
      bool QgUsFjPhYT = false;
      bool tQIINbsmCS = false;
      bool uklXhOQSlY = false;
      bool NBxFrZarqq = false;
      bool iITVKOtqjR = false;
      bool BhbxSftwLp = false;
      bool SxuzGrSDPn = false;
      bool BBwLjmRPNT = false;
      bool UYiUXeYAlM = false;
      bool edgAXkMTPR = false;
      bool uqbuPAlQMf = false;
      bool OehrVsOZba = false;
      string gCEmaGlCQi;
      string MtbYarbKKY;
      string biWWTDBKOm;
      string ZIUEqgaVkQ;
      string JzisbZiwXm;
      string sLOyZxfgTW;
      string EandIDZWgs;
      string RFYsObActs;
      string UFmatNsWdt;
      string BsCOLiLFjY;
      string zLOdUmmViy;
      string wClZBznMiu;
      string JDsmqXDKhf;
      string PusVtJpIFG;
      string ZXmfxzGbMM;
      string uzVoOwSalx;
      string jcnDhBJQfr;
      string IeGcUlQMor;
      string QaxUjQZDHx;
      string qOVIVxjiyw;
      if(gCEmaGlCQi == zLOdUmmViy){opwUDPrsTc = true;}
      else if(zLOdUmmViy == gCEmaGlCQi){uklXhOQSlY = true;}
      if(MtbYarbKKY == wClZBznMiu){fFlsfJeSSR = true;}
      else if(wClZBznMiu == MtbYarbKKY){NBxFrZarqq = true;}
      if(biWWTDBKOm == JDsmqXDKhf){bFJhAtJxGW = true;}
      else if(JDsmqXDKhf == biWWTDBKOm){iITVKOtqjR = true;}
      if(ZIUEqgaVkQ == PusVtJpIFG){BgOsDaecRU = true;}
      else if(PusVtJpIFG == ZIUEqgaVkQ){BhbxSftwLp = true;}
      if(JzisbZiwXm == ZXmfxzGbMM){XfjdRlcbcM = true;}
      else if(ZXmfxzGbMM == JzisbZiwXm){SxuzGrSDPn = true;}
      if(sLOyZxfgTW == uzVoOwSalx){RRQfUigNTJ = true;}
      else if(uzVoOwSalx == sLOyZxfgTW){BBwLjmRPNT = true;}
      if(EandIDZWgs == jcnDhBJQfr){GulwayprpE = true;}
      else if(jcnDhBJQfr == EandIDZWgs){UYiUXeYAlM = true;}
      if(RFYsObActs == IeGcUlQMor){eCAysuVePO = true;}
      if(UFmatNsWdt == QaxUjQZDHx){QgUsFjPhYT = true;}
      if(BsCOLiLFjY == qOVIVxjiyw){tQIINbsmCS = true;}
      while(IeGcUlQMor == RFYsObActs){edgAXkMTPR = true;}
      while(QaxUjQZDHx == QaxUjQZDHx){uqbuPAlQMf = true;}
      while(qOVIVxjiyw == qOVIVxjiyw){OehrVsOZba = true;}
      if(opwUDPrsTc == true){opwUDPrsTc = false;}
      if(fFlsfJeSSR == true){fFlsfJeSSR = false;}
      if(bFJhAtJxGW == true){bFJhAtJxGW = false;}
      if(BgOsDaecRU == true){BgOsDaecRU = false;}
      if(XfjdRlcbcM == true){XfjdRlcbcM = false;}
      if(RRQfUigNTJ == true){RRQfUigNTJ = false;}
      if(GulwayprpE == true){GulwayprpE = false;}
      if(eCAysuVePO == true){eCAysuVePO = false;}
      if(QgUsFjPhYT == true){QgUsFjPhYT = false;}
      if(tQIINbsmCS == true){tQIINbsmCS = false;}
      if(uklXhOQSlY == true){uklXhOQSlY = false;}
      if(NBxFrZarqq == true){NBxFrZarqq = false;}
      if(iITVKOtqjR == true){iITVKOtqjR = false;}
      if(BhbxSftwLp == true){BhbxSftwLp = false;}
      if(SxuzGrSDPn == true){SxuzGrSDPn = false;}
      if(BBwLjmRPNT == true){BBwLjmRPNT = false;}
      if(UYiUXeYAlM == true){UYiUXeYAlM = false;}
      if(edgAXkMTPR == true){edgAXkMTPR = false;}
      if(uqbuPAlQMf == true){uqbuPAlQMf = false;}
      if(OehrVsOZba == true){OehrVsOZba = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGBQKHEGWE
{ 
  void TtubgkKiVq()
  { 
      bool npmuPMNXBT = false;
      bool szCHzSzxCY = false;
      bool CfaSintmPc = false;
      bool nslJhjFDjJ = false;
      bool yZdbWUuyWm = false;
      bool tFJlHHOUMb = false;
      bool RZIXezMrZP = false;
      bool NuMsacBzuO = false;
      bool rwQcihizCZ = false;
      bool VkqIqXQGwW = false;
      bool HDYGZzsQLd = false;
      bool FOYxiVJfow = false;
      bool QNpzscDDBC = false;
      bool MuDYGoWJCj = false;
      bool oRnXUHLsYU = false;
      bool OkRAGtNZNx = false;
      bool uoPJRKLzps = false;
      bool zzcFHyZSel = false;
      bool QJefnadDRM = false;
      bool bwuFnzCdFJ = false;
      string DuquttrObN;
      string wgGKMFKTrF;
      string CjlDnNPWzz;
      string HFqtXZcbAk;
      string UqKttgDqmp;
      string IRGudSImGf;
      string dUPcFqoLlm;
      string ciTHjKZrJH;
      string KYjJppzwQF;
      string QpUUGzbgnD;
      string rrEzNYxyKT;
      string sQcyVFkFmP;
      string rrugVmOyBk;
      string hrEGPRUjwQ;
      string rAlwLAMVzA;
      string OWtYKzxWdZ;
      string KyxYkALWiD;
      string kBJVWqGyUV;
      string ZrzAWLxfuP;
      string TxGVFsDMLK;
      if(DuquttrObN == rrEzNYxyKT){npmuPMNXBT = true;}
      else if(rrEzNYxyKT == DuquttrObN){HDYGZzsQLd = true;}
      if(wgGKMFKTrF == sQcyVFkFmP){szCHzSzxCY = true;}
      else if(sQcyVFkFmP == wgGKMFKTrF){FOYxiVJfow = true;}
      if(CjlDnNPWzz == rrugVmOyBk){CfaSintmPc = true;}
      else if(rrugVmOyBk == CjlDnNPWzz){QNpzscDDBC = true;}
      if(HFqtXZcbAk == hrEGPRUjwQ){nslJhjFDjJ = true;}
      else if(hrEGPRUjwQ == HFqtXZcbAk){MuDYGoWJCj = true;}
      if(UqKttgDqmp == rAlwLAMVzA){yZdbWUuyWm = true;}
      else if(rAlwLAMVzA == UqKttgDqmp){oRnXUHLsYU = true;}
      if(IRGudSImGf == OWtYKzxWdZ){tFJlHHOUMb = true;}
      else if(OWtYKzxWdZ == IRGudSImGf){OkRAGtNZNx = true;}
      if(dUPcFqoLlm == KyxYkALWiD){RZIXezMrZP = true;}
      else if(KyxYkALWiD == dUPcFqoLlm){uoPJRKLzps = true;}
      if(ciTHjKZrJH == kBJVWqGyUV){NuMsacBzuO = true;}
      if(KYjJppzwQF == ZrzAWLxfuP){rwQcihizCZ = true;}
      if(QpUUGzbgnD == TxGVFsDMLK){VkqIqXQGwW = true;}
      while(kBJVWqGyUV == ciTHjKZrJH){zzcFHyZSel = true;}
      while(ZrzAWLxfuP == ZrzAWLxfuP){QJefnadDRM = true;}
      while(TxGVFsDMLK == TxGVFsDMLK){bwuFnzCdFJ = true;}
      if(npmuPMNXBT == true){npmuPMNXBT = false;}
      if(szCHzSzxCY == true){szCHzSzxCY = false;}
      if(CfaSintmPc == true){CfaSintmPc = false;}
      if(nslJhjFDjJ == true){nslJhjFDjJ = false;}
      if(yZdbWUuyWm == true){yZdbWUuyWm = false;}
      if(tFJlHHOUMb == true){tFJlHHOUMb = false;}
      if(RZIXezMrZP == true){RZIXezMrZP = false;}
      if(NuMsacBzuO == true){NuMsacBzuO = false;}
      if(rwQcihizCZ == true){rwQcihizCZ = false;}
      if(VkqIqXQGwW == true){VkqIqXQGwW = false;}
      if(HDYGZzsQLd == true){HDYGZzsQLd = false;}
      if(FOYxiVJfow == true){FOYxiVJfow = false;}
      if(QNpzscDDBC == true){QNpzscDDBC = false;}
      if(MuDYGoWJCj == true){MuDYGoWJCj = false;}
      if(oRnXUHLsYU == true){oRnXUHLsYU = false;}
      if(OkRAGtNZNx == true){OkRAGtNZNx = false;}
      if(uoPJRKLzps == true){uoPJRKLzps = false;}
      if(zzcFHyZSel == true){zzcFHyZSel = false;}
      if(QJefnadDRM == true){QJefnadDRM = false;}
      if(bwuFnzCdFJ == true){bwuFnzCdFJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIMRFTGSQQ
{ 
  void nplqcAehNx()
  { 
      bool XSpcBWpTTh = false;
      bool MLDCKikwqV = false;
      bool KxsPXWXuCB = false;
      bool BJUnowdOIO = false;
      bool DFMTIiEWUC = false;
      bool AURMKZZaEd = false;
      bool yuQSgDpPNO = false;
      bool EVncSFjYGn = false;
      bool RAZABfqHdO = false;
      bool VDJdPIotlE = false;
      bool soJFxdgotE = false;
      bool oATPMyUPQB = false;
      bool MilyrBLJMJ = false;
      bool QpmBucqTDW = false;
      bool yBMYZVitRR = false;
      bool mYdjrKDKNu = false;
      bool RWbjnzMRUj = false;
      bool HALsCKVMYV = false;
      bool SRrtWqLCJk = false;
      bool YfGIEaYbja = false;
      string tuAcoNorCg;
      string FxylWzsrIZ;
      string uNfEDhMiDo;
      string ErTPCkIlfj;
      string MmxjHPCMPt;
      string EaVwlfOwZH;
      string BFoNcNchjk;
      string pGLYNIPuxm;
      string ezSJkcVWdV;
      string VMMYiHxjHs;
      string lUcdDxPxic;
      string PTylcClfbA;
      string rGEOPctmpF;
      string LfnDBKWoFn;
      string NYmAFCNaug;
      string UQHGBfPNOZ;
      string CbGcQjeujS;
      string exZnmSSEJM;
      string PTqJktYgBU;
      string tIZekkRJiU;
      if(tuAcoNorCg == lUcdDxPxic){XSpcBWpTTh = true;}
      else if(lUcdDxPxic == tuAcoNorCg){soJFxdgotE = true;}
      if(FxylWzsrIZ == PTylcClfbA){MLDCKikwqV = true;}
      else if(PTylcClfbA == FxylWzsrIZ){oATPMyUPQB = true;}
      if(uNfEDhMiDo == rGEOPctmpF){KxsPXWXuCB = true;}
      else if(rGEOPctmpF == uNfEDhMiDo){MilyrBLJMJ = true;}
      if(ErTPCkIlfj == LfnDBKWoFn){BJUnowdOIO = true;}
      else if(LfnDBKWoFn == ErTPCkIlfj){QpmBucqTDW = true;}
      if(MmxjHPCMPt == NYmAFCNaug){DFMTIiEWUC = true;}
      else if(NYmAFCNaug == MmxjHPCMPt){yBMYZVitRR = true;}
      if(EaVwlfOwZH == UQHGBfPNOZ){AURMKZZaEd = true;}
      else if(UQHGBfPNOZ == EaVwlfOwZH){mYdjrKDKNu = true;}
      if(BFoNcNchjk == CbGcQjeujS){yuQSgDpPNO = true;}
      else if(CbGcQjeujS == BFoNcNchjk){RWbjnzMRUj = true;}
      if(pGLYNIPuxm == exZnmSSEJM){EVncSFjYGn = true;}
      if(ezSJkcVWdV == PTqJktYgBU){RAZABfqHdO = true;}
      if(VMMYiHxjHs == tIZekkRJiU){VDJdPIotlE = true;}
      while(exZnmSSEJM == pGLYNIPuxm){HALsCKVMYV = true;}
      while(PTqJktYgBU == PTqJktYgBU){SRrtWqLCJk = true;}
      while(tIZekkRJiU == tIZekkRJiU){YfGIEaYbja = true;}
      if(XSpcBWpTTh == true){XSpcBWpTTh = false;}
      if(MLDCKikwqV == true){MLDCKikwqV = false;}
      if(KxsPXWXuCB == true){KxsPXWXuCB = false;}
      if(BJUnowdOIO == true){BJUnowdOIO = false;}
      if(DFMTIiEWUC == true){DFMTIiEWUC = false;}
      if(AURMKZZaEd == true){AURMKZZaEd = false;}
      if(yuQSgDpPNO == true){yuQSgDpPNO = false;}
      if(EVncSFjYGn == true){EVncSFjYGn = false;}
      if(RAZABfqHdO == true){RAZABfqHdO = false;}
      if(VDJdPIotlE == true){VDJdPIotlE = false;}
      if(soJFxdgotE == true){soJFxdgotE = false;}
      if(oATPMyUPQB == true){oATPMyUPQB = false;}
      if(MilyrBLJMJ == true){MilyrBLJMJ = false;}
      if(QpmBucqTDW == true){QpmBucqTDW = false;}
      if(yBMYZVitRR == true){yBMYZVitRR = false;}
      if(mYdjrKDKNu == true){mYdjrKDKNu = false;}
      if(RWbjnzMRUj == true){RWbjnzMRUj = false;}
      if(HALsCKVMYV == true){HALsCKVMYV = false;}
      if(SRrtWqLCJk == true){SRrtWqLCJk = false;}
      if(YfGIEaYbja == true){YfGIEaYbja = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHHZMMZCVI
{ 
  void wXRJFtmKXB()
  { 
      bool rkpgRWBJgH = false;
      bool lTTYTJttMN = false;
      bool itGtOFmLcj = false;
      bool BHFRNnKDEk = false;
      bool CNoyFYxurN = false;
      bool iiapjyeuRL = false;
      bool jofxFdNCKe = false;
      bool ypoaLVEHop = false;
      bool IqSPARgOgP = false;
      bool JOlrBMgqsb = false;
      bool KtjNOsszeN = false;
      bool sWGbDrWQwm = false;
      bool wzUuViExYy = false;
      bool nNONfNGFAH = false;
      bool YgjTWlIKnJ = false;
      bool pQtFeLYorf = false;
      bool nwafZfHsup = false;
      bool kQQoOOOBXi = false;
      bool ZtIPIXSJhU = false;
      bool nQNTSbGDtq = false;
      string YEQloxwRUA;
      string tZfnKmTSOS;
      string gPnISgRsQT;
      string NyDlUGKFZQ;
      string qDrEFIChys;
      string AybkWJQHTH;
      string eDBAluWtTE;
      string bNrybdWiCJ;
      string djtXTOWROK;
      string oDkSkmBqRK;
      string lINtRlFcJs;
      string lgEJctIcgW;
      string XEeIOXbZMn;
      string bfQrXVWAFg;
      string JsIVYIybop;
      string eYJulgcEes;
      string JeQUQFPMkH;
      string XHXANeuJjG;
      string ZAkWIDWVGq;
      string rRULWdcmES;
      if(YEQloxwRUA == lINtRlFcJs){rkpgRWBJgH = true;}
      else if(lINtRlFcJs == YEQloxwRUA){KtjNOsszeN = true;}
      if(tZfnKmTSOS == lgEJctIcgW){lTTYTJttMN = true;}
      else if(lgEJctIcgW == tZfnKmTSOS){sWGbDrWQwm = true;}
      if(gPnISgRsQT == XEeIOXbZMn){itGtOFmLcj = true;}
      else if(XEeIOXbZMn == gPnISgRsQT){wzUuViExYy = true;}
      if(NyDlUGKFZQ == bfQrXVWAFg){BHFRNnKDEk = true;}
      else if(bfQrXVWAFg == NyDlUGKFZQ){nNONfNGFAH = true;}
      if(qDrEFIChys == JsIVYIybop){CNoyFYxurN = true;}
      else if(JsIVYIybop == qDrEFIChys){YgjTWlIKnJ = true;}
      if(AybkWJQHTH == eYJulgcEes){iiapjyeuRL = true;}
      else if(eYJulgcEes == AybkWJQHTH){pQtFeLYorf = true;}
      if(eDBAluWtTE == JeQUQFPMkH){jofxFdNCKe = true;}
      else if(JeQUQFPMkH == eDBAluWtTE){nwafZfHsup = true;}
      if(bNrybdWiCJ == XHXANeuJjG){ypoaLVEHop = true;}
      if(djtXTOWROK == ZAkWIDWVGq){IqSPARgOgP = true;}
      if(oDkSkmBqRK == rRULWdcmES){JOlrBMgqsb = true;}
      while(XHXANeuJjG == bNrybdWiCJ){kQQoOOOBXi = true;}
      while(ZAkWIDWVGq == ZAkWIDWVGq){ZtIPIXSJhU = true;}
      while(rRULWdcmES == rRULWdcmES){nQNTSbGDtq = true;}
      if(rkpgRWBJgH == true){rkpgRWBJgH = false;}
      if(lTTYTJttMN == true){lTTYTJttMN = false;}
      if(itGtOFmLcj == true){itGtOFmLcj = false;}
      if(BHFRNnKDEk == true){BHFRNnKDEk = false;}
      if(CNoyFYxurN == true){CNoyFYxurN = false;}
      if(iiapjyeuRL == true){iiapjyeuRL = false;}
      if(jofxFdNCKe == true){jofxFdNCKe = false;}
      if(ypoaLVEHop == true){ypoaLVEHop = false;}
      if(IqSPARgOgP == true){IqSPARgOgP = false;}
      if(JOlrBMgqsb == true){JOlrBMgqsb = false;}
      if(KtjNOsszeN == true){KtjNOsszeN = false;}
      if(sWGbDrWQwm == true){sWGbDrWQwm = false;}
      if(wzUuViExYy == true){wzUuViExYy = false;}
      if(nNONfNGFAH == true){nNONfNGFAH = false;}
      if(YgjTWlIKnJ == true){YgjTWlIKnJ = false;}
      if(pQtFeLYorf == true){pQtFeLYorf = false;}
      if(nwafZfHsup == true){nwafZfHsup = false;}
      if(kQQoOOOBXi == true){kQQoOOOBXi = false;}
      if(ZtIPIXSJhU == true){ZtIPIXSJhU = false;}
      if(nQNTSbGDtq == true){nQNTSbGDtq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIHVIDISQL
{ 
  void pOwGMVrFYi()
  { 
      bool BnUSUXHIaz = false;
      bool QMwyHkRFUn = false;
      bool HMZRAxJPyE = false;
      bool ygTfklAikQ = false;
      bool oOMwcpVmem = false;
      bool cHAgyoNDRW = false;
      bool NqJVBirQMU = false;
      bool jhTDyrzcoK = false;
      bool aWjLbqfmgu = false;
      bool YxQNCyEqus = false;
      bool xFZKCtmwiF = false;
      bool pkNHuqHysJ = false;
      bool DFiRwlQGBA = false;
      bool nHgwMVwYIg = false;
      bool EjDaEmiJRL = false;
      bool pFxkorWIOP = false;
      bool cfuiRiDRtZ = false;
      bool uipLFSBHMI = false;
      bool DHnpJhJwGU = false;
      bool zmKrDXnUJV = false;
      string WcXYEQwjrV;
      string YbTTphusNs;
      string cGLxnsufaC;
      string BRBbgiMopV;
      string BpWIzapqhn;
      string OusHdQRakL;
      string UQJpTGZrmH;
      string VFCqrmjCyN;
      string CEylmGYsxQ;
      string RlEeBkfgnr;
      string AxDaRIrBPq;
      string fObXIQRWCN;
      string hguVojBXpG;
      string GCOGMFAWUe;
      string OWdFjCJfVk;
      string SJeZJTChkh;
      string GTKIkdAVKD;
      string PuCWzKColm;
      string ZVCFnxWnws;
      string CSkmXtMUUF;
      if(WcXYEQwjrV == AxDaRIrBPq){BnUSUXHIaz = true;}
      else if(AxDaRIrBPq == WcXYEQwjrV){xFZKCtmwiF = true;}
      if(YbTTphusNs == fObXIQRWCN){QMwyHkRFUn = true;}
      else if(fObXIQRWCN == YbTTphusNs){pkNHuqHysJ = true;}
      if(cGLxnsufaC == hguVojBXpG){HMZRAxJPyE = true;}
      else if(hguVojBXpG == cGLxnsufaC){DFiRwlQGBA = true;}
      if(BRBbgiMopV == GCOGMFAWUe){ygTfklAikQ = true;}
      else if(GCOGMFAWUe == BRBbgiMopV){nHgwMVwYIg = true;}
      if(BpWIzapqhn == OWdFjCJfVk){oOMwcpVmem = true;}
      else if(OWdFjCJfVk == BpWIzapqhn){EjDaEmiJRL = true;}
      if(OusHdQRakL == SJeZJTChkh){cHAgyoNDRW = true;}
      else if(SJeZJTChkh == OusHdQRakL){pFxkorWIOP = true;}
      if(UQJpTGZrmH == GTKIkdAVKD){NqJVBirQMU = true;}
      else if(GTKIkdAVKD == UQJpTGZrmH){cfuiRiDRtZ = true;}
      if(VFCqrmjCyN == PuCWzKColm){jhTDyrzcoK = true;}
      if(CEylmGYsxQ == ZVCFnxWnws){aWjLbqfmgu = true;}
      if(RlEeBkfgnr == CSkmXtMUUF){YxQNCyEqus = true;}
      while(PuCWzKColm == VFCqrmjCyN){uipLFSBHMI = true;}
      while(ZVCFnxWnws == ZVCFnxWnws){DHnpJhJwGU = true;}
      while(CSkmXtMUUF == CSkmXtMUUF){zmKrDXnUJV = true;}
      if(BnUSUXHIaz == true){BnUSUXHIaz = false;}
      if(QMwyHkRFUn == true){QMwyHkRFUn = false;}
      if(HMZRAxJPyE == true){HMZRAxJPyE = false;}
      if(ygTfklAikQ == true){ygTfklAikQ = false;}
      if(oOMwcpVmem == true){oOMwcpVmem = false;}
      if(cHAgyoNDRW == true){cHAgyoNDRW = false;}
      if(NqJVBirQMU == true){NqJVBirQMU = false;}
      if(jhTDyrzcoK == true){jhTDyrzcoK = false;}
      if(aWjLbqfmgu == true){aWjLbqfmgu = false;}
      if(YxQNCyEqus == true){YxQNCyEqus = false;}
      if(xFZKCtmwiF == true){xFZKCtmwiF = false;}
      if(pkNHuqHysJ == true){pkNHuqHysJ = false;}
      if(DFiRwlQGBA == true){DFiRwlQGBA = false;}
      if(nHgwMVwYIg == true){nHgwMVwYIg = false;}
      if(EjDaEmiJRL == true){EjDaEmiJRL = false;}
      if(pFxkorWIOP == true){pFxkorWIOP = false;}
      if(cfuiRiDRtZ == true){cfuiRiDRtZ = false;}
      if(uipLFSBHMI == true){uipLFSBHMI = false;}
      if(DHnpJhJwGU == true){DHnpJhJwGU = false;}
      if(zmKrDXnUJV == true){zmKrDXnUJV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCULEUTCPX
{ 
  void ANoUyRdKuC()
  { 
      bool RdBAzEfXVg = false;
      bool fSQEXKqdTX = false;
      bool hXYPjmFpJP = false;
      bool qEGibuApdB = false;
      bool HohyoSEVLz = false;
      bool oGXEKsFlPL = false;
      bool zpOFpaLgbc = false;
      bool KAASQrpZaR = false;
      bool iieJakfCYi = false;
      bool pNaRCQZbIN = false;
      bool GWtionFFnR = false;
      bool CeLycQLEeE = false;
      bool uJIrlwZhQz = false;
      bool RORMLLnuUl = false;
      bool eZNHgKCbnk = false;
      bool FVxDRwOBwr = false;
      bool OXonzmMymR = false;
      bool bPirYVuALa = false;
      bool sxseswRNuO = false;
      bool xmzcXHjYIs = false;
      string FdUrMXqdiI;
      string CYZWHerfnn;
      string TWmFXxeZhZ;
      string qudJUfslrX;
      string HKnrkknJNs;
      string FiJwOhpPTP;
      string sRwIRGuQBb;
      string lFnPfIiuUm;
      string IVLnUIlgtl;
      string odSbepOeae;
      string pWHlGztsPG;
      string zutgGWFHnJ;
      string UNWOmImMkp;
      string tETpwlNZhV;
      string NrRnmsilUH;
      string jGpQJbAryy;
      string LhHYLubEjU;
      string IfZSubwhbt;
      string ZBqcFnNDfU;
      string kVajJfjrbr;
      if(FdUrMXqdiI == pWHlGztsPG){RdBAzEfXVg = true;}
      else if(pWHlGztsPG == FdUrMXqdiI){GWtionFFnR = true;}
      if(CYZWHerfnn == zutgGWFHnJ){fSQEXKqdTX = true;}
      else if(zutgGWFHnJ == CYZWHerfnn){CeLycQLEeE = true;}
      if(TWmFXxeZhZ == UNWOmImMkp){hXYPjmFpJP = true;}
      else if(UNWOmImMkp == TWmFXxeZhZ){uJIrlwZhQz = true;}
      if(qudJUfslrX == tETpwlNZhV){qEGibuApdB = true;}
      else if(tETpwlNZhV == qudJUfslrX){RORMLLnuUl = true;}
      if(HKnrkknJNs == NrRnmsilUH){HohyoSEVLz = true;}
      else if(NrRnmsilUH == HKnrkknJNs){eZNHgKCbnk = true;}
      if(FiJwOhpPTP == jGpQJbAryy){oGXEKsFlPL = true;}
      else if(jGpQJbAryy == FiJwOhpPTP){FVxDRwOBwr = true;}
      if(sRwIRGuQBb == LhHYLubEjU){zpOFpaLgbc = true;}
      else if(LhHYLubEjU == sRwIRGuQBb){OXonzmMymR = true;}
      if(lFnPfIiuUm == IfZSubwhbt){KAASQrpZaR = true;}
      if(IVLnUIlgtl == ZBqcFnNDfU){iieJakfCYi = true;}
      if(odSbepOeae == kVajJfjrbr){pNaRCQZbIN = true;}
      while(IfZSubwhbt == lFnPfIiuUm){bPirYVuALa = true;}
      while(ZBqcFnNDfU == ZBqcFnNDfU){sxseswRNuO = true;}
      while(kVajJfjrbr == kVajJfjrbr){xmzcXHjYIs = true;}
      if(RdBAzEfXVg == true){RdBAzEfXVg = false;}
      if(fSQEXKqdTX == true){fSQEXKqdTX = false;}
      if(hXYPjmFpJP == true){hXYPjmFpJP = false;}
      if(qEGibuApdB == true){qEGibuApdB = false;}
      if(HohyoSEVLz == true){HohyoSEVLz = false;}
      if(oGXEKsFlPL == true){oGXEKsFlPL = false;}
      if(zpOFpaLgbc == true){zpOFpaLgbc = false;}
      if(KAASQrpZaR == true){KAASQrpZaR = false;}
      if(iieJakfCYi == true){iieJakfCYi = false;}
      if(pNaRCQZbIN == true){pNaRCQZbIN = false;}
      if(GWtionFFnR == true){GWtionFFnR = false;}
      if(CeLycQLEeE == true){CeLycQLEeE = false;}
      if(uJIrlwZhQz == true){uJIrlwZhQz = false;}
      if(RORMLLnuUl == true){RORMLLnuUl = false;}
      if(eZNHgKCbnk == true){eZNHgKCbnk = false;}
      if(FVxDRwOBwr == true){FVxDRwOBwr = false;}
      if(OXonzmMymR == true){OXonzmMymR = false;}
      if(bPirYVuALa == true){bPirYVuALa = false;}
      if(sxseswRNuO == true){sxseswRNuO = false;}
      if(xmzcXHjYIs == true){xmzcXHjYIs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAUCMIKVSP
{ 
  void VyHsaDBTAC()
  { 
      bool IfhdyLPyJL = false;
      bool ucnmNMSTlp = false;
      bool NhIBhOsPiP = false;
      bool WwTqdYhgLP = false;
      bool hqdNxcLsno = false;
      bool uVIyEZXfwi = false;
      bool SzOtnyJwJo = false;
      bool ekHVIVEtDE = false;
      bool DzbsTAnUlE = false;
      bool ABkcxhbiYy = false;
      bool SOjyJJNmph = false;
      bool UdcqfTXVam = false;
      bool KnKFndAeXZ = false;
      bool sVUElnPciJ = false;
      bool lBeDiWYtwd = false;
      bool KGIkneEdKf = false;
      bool JiOPozIXFr = false;
      bool DtlQAIJGWQ = false;
      bool FFhtOlMiQG = false;
      bool jkSDzDmOOi = false;
      string yqVlAMLqnA;
      string GbngzbzPze;
      string LtKtpJdfzV;
      string gKrKDHSBoF;
      string yMSaxWxFit;
      string ThrIREfauq;
      string ierSSuicdr;
      string JyasgzaixT;
      string LXxFByRjsz;
      string aqFxWSUAHB;
      string mUbpjVGzbR;
      string cxdbeKgmQU;
      string dzieQRscVN;
      string eZawgqwGUe;
      string qSIbVdNcRM;
      string lhjmWmkwZS;
      string cdcNmDVgun;
      string OZRkcLqHIl;
      string EPKJbxpmYs;
      string GzgCCNotnR;
      if(yqVlAMLqnA == mUbpjVGzbR){IfhdyLPyJL = true;}
      else if(mUbpjVGzbR == yqVlAMLqnA){SOjyJJNmph = true;}
      if(GbngzbzPze == cxdbeKgmQU){ucnmNMSTlp = true;}
      else if(cxdbeKgmQU == GbngzbzPze){UdcqfTXVam = true;}
      if(LtKtpJdfzV == dzieQRscVN){NhIBhOsPiP = true;}
      else if(dzieQRscVN == LtKtpJdfzV){KnKFndAeXZ = true;}
      if(gKrKDHSBoF == eZawgqwGUe){WwTqdYhgLP = true;}
      else if(eZawgqwGUe == gKrKDHSBoF){sVUElnPciJ = true;}
      if(yMSaxWxFit == qSIbVdNcRM){hqdNxcLsno = true;}
      else if(qSIbVdNcRM == yMSaxWxFit){lBeDiWYtwd = true;}
      if(ThrIREfauq == lhjmWmkwZS){uVIyEZXfwi = true;}
      else if(lhjmWmkwZS == ThrIREfauq){KGIkneEdKf = true;}
      if(ierSSuicdr == cdcNmDVgun){SzOtnyJwJo = true;}
      else if(cdcNmDVgun == ierSSuicdr){JiOPozIXFr = true;}
      if(JyasgzaixT == OZRkcLqHIl){ekHVIVEtDE = true;}
      if(LXxFByRjsz == EPKJbxpmYs){DzbsTAnUlE = true;}
      if(aqFxWSUAHB == GzgCCNotnR){ABkcxhbiYy = true;}
      while(OZRkcLqHIl == JyasgzaixT){DtlQAIJGWQ = true;}
      while(EPKJbxpmYs == EPKJbxpmYs){FFhtOlMiQG = true;}
      while(GzgCCNotnR == GzgCCNotnR){jkSDzDmOOi = true;}
      if(IfhdyLPyJL == true){IfhdyLPyJL = false;}
      if(ucnmNMSTlp == true){ucnmNMSTlp = false;}
      if(NhIBhOsPiP == true){NhIBhOsPiP = false;}
      if(WwTqdYhgLP == true){WwTqdYhgLP = false;}
      if(hqdNxcLsno == true){hqdNxcLsno = false;}
      if(uVIyEZXfwi == true){uVIyEZXfwi = false;}
      if(SzOtnyJwJo == true){SzOtnyJwJo = false;}
      if(ekHVIVEtDE == true){ekHVIVEtDE = false;}
      if(DzbsTAnUlE == true){DzbsTAnUlE = false;}
      if(ABkcxhbiYy == true){ABkcxhbiYy = false;}
      if(SOjyJJNmph == true){SOjyJJNmph = false;}
      if(UdcqfTXVam == true){UdcqfTXVam = false;}
      if(KnKFndAeXZ == true){KnKFndAeXZ = false;}
      if(sVUElnPciJ == true){sVUElnPciJ = false;}
      if(lBeDiWYtwd == true){lBeDiWYtwd = false;}
      if(KGIkneEdKf == true){KGIkneEdKf = false;}
      if(JiOPozIXFr == true){JiOPozIXFr = false;}
      if(DtlQAIJGWQ == true){DtlQAIJGWQ = false;}
      if(FFhtOlMiQG == true){FFhtOlMiQG = false;}
      if(jkSDzDmOOi == true){jkSDzDmOOi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWXJPXWRBY
{ 
  void UeENJwRajy()
  { 
      bool GyUmThfFSw = false;
      bool cjKeYOlrDo = false;
      bool dzVrAKddfG = false;
      bool InyQqCXgHU = false;
      bool ZSQldoKnuJ = false;
      bool FhpeBHbcmI = false;
      bool DCYLmoltmV = false;
      bool pEjiPLhjOK = false;
      bool ApiWAaxSOj = false;
      bool ZutyQWtFyo = false;
      bool DPAYTAyHPp = false;
      bool YrNcHNSCKM = false;
      bool qSeDwuKkRr = false;
      bool RckZGkoKCA = false;
      bool cpCYKggQpD = false;
      bool DqtlxkkxcX = false;
      bool oMpXYwHnVW = false;
      bool YIzKjBPFsO = false;
      bool OstOnZhybV = false;
      bool zqgeKQzeAN = false;
      string cIrPwcwyJO;
      string qJGleuVlUn;
      string pMLzhcDohX;
      string dXkdlTQUki;
      string gkhybTNnbJ;
      string VphwjQwrgT;
      string YHPlkSYbAL;
      string dBAlHFeNXO;
      string OPMYBnpotU;
      string XYmRJZUuNI;
      string ukmQeUowne;
      string lhUSEJtqkw;
      string cihemFNhbh;
      string jiAOSdcwsf;
      string ytAOioEUNA;
      string edKQfLDHcZ;
      string HGTGtChFzZ;
      string fxxEyiiSwy;
      string BsUbCFYiiG;
      string ZUSTXqZtTf;
      if(cIrPwcwyJO == ukmQeUowne){GyUmThfFSw = true;}
      else if(ukmQeUowne == cIrPwcwyJO){DPAYTAyHPp = true;}
      if(qJGleuVlUn == lhUSEJtqkw){cjKeYOlrDo = true;}
      else if(lhUSEJtqkw == qJGleuVlUn){YrNcHNSCKM = true;}
      if(pMLzhcDohX == cihemFNhbh){dzVrAKddfG = true;}
      else if(cihemFNhbh == pMLzhcDohX){qSeDwuKkRr = true;}
      if(dXkdlTQUki == jiAOSdcwsf){InyQqCXgHU = true;}
      else if(jiAOSdcwsf == dXkdlTQUki){RckZGkoKCA = true;}
      if(gkhybTNnbJ == ytAOioEUNA){ZSQldoKnuJ = true;}
      else if(ytAOioEUNA == gkhybTNnbJ){cpCYKggQpD = true;}
      if(VphwjQwrgT == edKQfLDHcZ){FhpeBHbcmI = true;}
      else if(edKQfLDHcZ == VphwjQwrgT){DqtlxkkxcX = true;}
      if(YHPlkSYbAL == HGTGtChFzZ){DCYLmoltmV = true;}
      else if(HGTGtChFzZ == YHPlkSYbAL){oMpXYwHnVW = true;}
      if(dBAlHFeNXO == fxxEyiiSwy){pEjiPLhjOK = true;}
      if(OPMYBnpotU == BsUbCFYiiG){ApiWAaxSOj = true;}
      if(XYmRJZUuNI == ZUSTXqZtTf){ZutyQWtFyo = true;}
      while(fxxEyiiSwy == dBAlHFeNXO){YIzKjBPFsO = true;}
      while(BsUbCFYiiG == BsUbCFYiiG){OstOnZhybV = true;}
      while(ZUSTXqZtTf == ZUSTXqZtTf){zqgeKQzeAN = true;}
      if(GyUmThfFSw == true){GyUmThfFSw = false;}
      if(cjKeYOlrDo == true){cjKeYOlrDo = false;}
      if(dzVrAKddfG == true){dzVrAKddfG = false;}
      if(InyQqCXgHU == true){InyQqCXgHU = false;}
      if(ZSQldoKnuJ == true){ZSQldoKnuJ = false;}
      if(FhpeBHbcmI == true){FhpeBHbcmI = false;}
      if(DCYLmoltmV == true){DCYLmoltmV = false;}
      if(pEjiPLhjOK == true){pEjiPLhjOK = false;}
      if(ApiWAaxSOj == true){ApiWAaxSOj = false;}
      if(ZutyQWtFyo == true){ZutyQWtFyo = false;}
      if(DPAYTAyHPp == true){DPAYTAyHPp = false;}
      if(YrNcHNSCKM == true){YrNcHNSCKM = false;}
      if(qSeDwuKkRr == true){qSeDwuKkRr = false;}
      if(RckZGkoKCA == true){RckZGkoKCA = false;}
      if(cpCYKggQpD == true){cpCYKggQpD = false;}
      if(DqtlxkkxcX == true){DqtlxkkxcX = false;}
      if(oMpXYwHnVW == true){oMpXYwHnVW = false;}
      if(YIzKjBPFsO == true){YIzKjBPFsO = false;}
      if(OstOnZhybV == true){OstOnZhybV = false;}
      if(zqgeKQzeAN == true){zqgeKQzeAN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYPPYELVWA
{ 
  void hnHkpqSiRP()
  { 
      bool TGxEmXNhFn = false;
      bool yrZsLIihWe = false;
      bool THFeCnVkfh = false;
      bool limNAytsTr = false;
      bool zetfYReYHP = false;
      bool GoDpiMBSBy = false;
      bool CbBWBOFMsN = false;
      bool OpNdfoNYFj = false;
      bool IwdPbxfwem = false;
      bool xbqUpWdWeK = false;
      bool MSetBQaYKt = false;
      bool ybMRpFykuE = false;
      bool iIgFPmzsmI = false;
      bool LptuWoRiOL = false;
      bool WGlkoVOYek = false;
      bool YrbZbEkYeO = false;
      bool QgkBhHgRtA = false;
      bool nOVjhbVwQs = false;
      bool XZOCjSOUSS = false;
      bool ErEAtoUkCg = false;
      string qYuuNjRstf;
      string mJFnDRIAND;
      string kpmQzIDGJr;
      string SbFzTwEfuD;
      string stVlekaNPS;
      string WAmaOBkewF;
      string fLiBNKDFTG;
      string NcEKJqTBlN;
      string gppqURoejR;
      string LZipWgKTYT;
      string gVsJFtucQX;
      string gjriXpUqfu;
      string VYUBumsOmc;
      string fAcRfKwgla;
      string WMOMjagARf;
      string LTmcxIAqNR;
      string BgonqgHZCM;
      string snFFXJKIQT;
      string FrxGQMMzUX;
      string KFSTYpWaUD;
      if(qYuuNjRstf == gVsJFtucQX){TGxEmXNhFn = true;}
      else if(gVsJFtucQX == qYuuNjRstf){MSetBQaYKt = true;}
      if(mJFnDRIAND == gjriXpUqfu){yrZsLIihWe = true;}
      else if(gjriXpUqfu == mJFnDRIAND){ybMRpFykuE = true;}
      if(kpmQzIDGJr == VYUBumsOmc){THFeCnVkfh = true;}
      else if(VYUBumsOmc == kpmQzIDGJr){iIgFPmzsmI = true;}
      if(SbFzTwEfuD == fAcRfKwgla){limNAytsTr = true;}
      else if(fAcRfKwgla == SbFzTwEfuD){LptuWoRiOL = true;}
      if(stVlekaNPS == WMOMjagARf){zetfYReYHP = true;}
      else if(WMOMjagARf == stVlekaNPS){WGlkoVOYek = true;}
      if(WAmaOBkewF == LTmcxIAqNR){GoDpiMBSBy = true;}
      else if(LTmcxIAqNR == WAmaOBkewF){YrbZbEkYeO = true;}
      if(fLiBNKDFTG == BgonqgHZCM){CbBWBOFMsN = true;}
      else if(BgonqgHZCM == fLiBNKDFTG){QgkBhHgRtA = true;}
      if(NcEKJqTBlN == snFFXJKIQT){OpNdfoNYFj = true;}
      if(gppqURoejR == FrxGQMMzUX){IwdPbxfwem = true;}
      if(LZipWgKTYT == KFSTYpWaUD){xbqUpWdWeK = true;}
      while(snFFXJKIQT == NcEKJqTBlN){nOVjhbVwQs = true;}
      while(FrxGQMMzUX == FrxGQMMzUX){XZOCjSOUSS = true;}
      while(KFSTYpWaUD == KFSTYpWaUD){ErEAtoUkCg = true;}
      if(TGxEmXNhFn == true){TGxEmXNhFn = false;}
      if(yrZsLIihWe == true){yrZsLIihWe = false;}
      if(THFeCnVkfh == true){THFeCnVkfh = false;}
      if(limNAytsTr == true){limNAytsTr = false;}
      if(zetfYReYHP == true){zetfYReYHP = false;}
      if(GoDpiMBSBy == true){GoDpiMBSBy = false;}
      if(CbBWBOFMsN == true){CbBWBOFMsN = false;}
      if(OpNdfoNYFj == true){OpNdfoNYFj = false;}
      if(IwdPbxfwem == true){IwdPbxfwem = false;}
      if(xbqUpWdWeK == true){xbqUpWdWeK = false;}
      if(MSetBQaYKt == true){MSetBQaYKt = false;}
      if(ybMRpFykuE == true){ybMRpFykuE = false;}
      if(iIgFPmzsmI == true){iIgFPmzsmI = false;}
      if(LptuWoRiOL == true){LptuWoRiOL = false;}
      if(WGlkoVOYek == true){WGlkoVOYek = false;}
      if(YrbZbEkYeO == true){YrbZbEkYeO = false;}
      if(QgkBhHgRtA == true){QgkBhHgRtA = false;}
      if(nOVjhbVwQs == true){nOVjhbVwQs = false;}
      if(XZOCjSOUSS == true){XZOCjSOUSS = false;}
      if(ErEAtoUkCg == true){ErEAtoUkCg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVGPMKYLWE
{ 
  void wVLHyWBnoG()
  { 
      bool ljdIoRatul = false;
      bool rgWUowjKcT = false;
      bool OBdicrgRVu = false;
      bool UKqmkRHdjY = false;
      bool yzWqpzgSGi = false;
      bool ywEgIkFufw = false;
      bool kJXzQhojiW = false;
      bool nGZDVPdmrd = false;
      bool KNLmxYFJdA = false;
      bool MMynnoaWaI = false;
      bool JwjitqWBLs = false;
      bool GSCCkWxkCr = false;
      bool bfGiKbIkOg = false;
      bool nGLjTOdbrF = false;
      bool CEykssJuCR = false;
      bool qoUhfdpAYR = false;
      bool ikleEzGSiW = false;
      bool sVsxpXgUoQ = false;
      bool SMixpyldEo = false;
      bool XcDaVRSSft = false;
      string jtjKLoYgqX;
      string PBCldJjMqD;
      string WqfKXYyVED;
      string ELJMUgTUWL;
      string nSudkXDoTc;
      string cTZKKrNZll;
      string qCcmTDroRw;
      string oOpeODwBYz;
      string UICbZjkyBb;
      string SshjTlpHJg;
      string eNWWmNdtwG;
      string wLAlQhABMj;
      string StnpdugGKc;
      string NnrrUGlfnL;
      string FpBteGsuSk;
      string lntZOkZgrr;
      string gXjTsITIRJ;
      string wTNAdbrsKX;
      string CkmYqYsSdi;
      string gEmuehGhBW;
      if(jtjKLoYgqX == eNWWmNdtwG){ljdIoRatul = true;}
      else if(eNWWmNdtwG == jtjKLoYgqX){JwjitqWBLs = true;}
      if(PBCldJjMqD == wLAlQhABMj){rgWUowjKcT = true;}
      else if(wLAlQhABMj == PBCldJjMqD){GSCCkWxkCr = true;}
      if(WqfKXYyVED == StnpdugGKc){OBdicrgRVu = true;}
      else if(StnpdugGKc == WqfKXYyVED){bfGiKbIkOg = true;}
      if(ELJMUgTUWL == NnrrUGlfnL){UKqmkRHdjY = true;}
      else if(NnrrUGlfnL == ELJMUgTUWL){nGLjTOdbrF = true;}
      if(nSudkXDoTc == FpBteGsuSk){yzWqpzgSGi = true;}
      else if(FpBteGsuSk == nSudkXDoTc){CEykssJuCR = true;}
      if(cTZKKrNZll == lntZOkZgrr){ywEgIkFufw = true;}
      else if(lntZOkZgrr == cTZKKrNZll){qoUhfdpAYR = true;}
      if(qCcmTDroRw == gXjTsITIRJ){kJXzQhojiW = true;}
      else if(gXjTsITIRJ == qCcmTDroRw){ikleEzGSiW = true;}
      if(oOpeODwBYz == wTNAdbrsKX){nGZDVPdmrd = true;}
      if(UICbZjkyBb == CkmYqYsSdi){KNLmxYFJdA = true;}
      if(SshjTlpHJg == gEmuehGhBW){MMynnoaWaI = true;}
      while(wTNAdbrsKX == oOpeODwBYz){sVsxpXgUoQ = true;}
      while(CkmYqYsSdi == CkmYqYsSdi){SMixpyldEo = true;}
      while(gEmuehGhBW == gEmuehGhBW){XcDaVRSSft = true;}
      if(ljdIoRatul == true){ljdIoRatul = false;}
      if(rgWUowjKcT == true){rgWUowjKcT = false;}
      if(OBdicrgRVu == true){OBdicrgRVu = false;}
      if(UKqmkRHdjY == true){UKqmkRHdjY = false;}
      if(yzWqpzgSGi == true){yzWqpzgSGi = false;}
      if(ywEgIkFufw == true){ywEgIkFufw = false;}
      if(kJXzQhojiW == true){kJXzQhojiW = false;}
      if(nGZDVPdmrd == true){nGZDVPdmrd = false;}
      if(KNLmxYFJdA == true){KNLmxYFJdA = false;}
      if(MMynnoaWaI == true){MMynnoaWaI = false;}
      if(JwjitqWBLs == true){JwjitqWBLs = false;}
      if(GSCCkWxkCr == true){GSCCkWxkCr = false;}
      if(bfGiKbIkOg == true){bfGiKbIkOg = false;}
      if(nGLjTOdbrF == true){nGLjTOdbrF = false;}
      if(CEykssJuCR == true){CEykssJuCR = false;}
      if(qoUhfdpAYR == true){qoUhfdpAYR = false;}
      if(ikleEzGSiW == true){ikleEzGSiW = false;}
      if(sVsxpXgUoQ == true){sVsxpXgUoQ = false;}
      if(SMixpyldEo == true){SMixpyldEo = false;}
      if(XcDaVRSSft == true){XcDaVRSSft = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJKPSRKSFB
{ 
  void lUaWZOXlTS()
  { 
      bool OeHFDMQGTz = false;
      bool QOznIiAoIg = false;
      bool aouPjQbYJA = false;
      bool IUZwsAmQFj = false;
      bool FltFhtQesm = false;
      bool KIsXqYirVm = false;
      bool jrwSpwoCtI = false;
      bool wiiXaoupgo = false;
      bool zweVpAaCET = false;
      bool QuuSAMoaOl = false;
      bool FOkjqaYUwC = false;
      bool dsKfmmMZco = false;
      bool UlxZrAnQXN = false;
      bool zUatjkLueP = false;
      bool aGFBpWjPfM = false;
      bool APyYRSQKrp = false;
      bool mIxhDIRQuB = false;
      bool bRuMONgujU = false;
      bool QXkKNjWCbR = false;
      bool UACncSIXyh = false;
      string nmjYVxLiLM;
      string MufNfIWAtu;
      string gsTLRkrJfi;
      string oXzQdlLfgC;
      string WKwxuMyyTs;
      string lMjiouTYHj;
      string FCCcWouPit;
      string wpTqYVxVPE;
      string lsolwbnQbi;
      string RmYxxTHSaG;
      string RiOYxusrJS;
      string xyICxLMPgt;
      string BdnAbJRVtE;
      string OdtJmDeQoA;
      string huHIkSdWzk;
      string HqlfEntOxm;
      string dXyFDSDzOs;
      string guafLFWeOI;
      string euWJwWrOEz;
      string JQTBWKxBES;
      if(nmjYVxLiLM == RiOYxusrJS){OeHFDMQGTz = true;}
      else if(RiOYxusrJS == nmjYVxLiLM){FOkjqaYUwC = true;}
      if(MufNfIWAtu == xyICxLMPgt){QOznIiAoIg = true;}
      else if(xyICxLMPgt == MufNfIWAtu){dsKfmmMZco = true;}
      if(gsTLRkrJfi == BdnAbJRVtE){aouPjQbYJA = true;}
      else if(BdnAbJRVtE == gsTLRkrJfi){UlxZrAnQXN = true;}
      if(oXzQdlLfgC == OdtJmDeQoA){IUZwsAmQFj = true;}
      else if(OdtJmDeQoA == oXzQdlLfgC){zUatjkLueP = true;}
      if(WKwxuMyyTs == huHIkSdWzk){FltFhtQesm = true;}
      else if(huHIkSdWzk == WKwxuMyyTs){aGFBpWjPfM = true;}
      if(lMjiouTYHj == HqlfEntOxm){KIsXqYirVm = true;}
      else if(HqlfEntOxm == lMjiouTYHj){APyYRSQKrp = true;}
      if(FCCcWouPit == dXyFDSDzOs){jrwSpwoCtI = true;}
      else if(dXyFDSDzOs == FCCcWouPit){mIxhDIRQuB = true;}
      if(wpTqYVxVPE == guafLFWeOI){wiiXaoupgo = true;}
      if(lsolwbnQbi == euWJwWrOEz){zweVpAaCET = true;}
      if(RmYxxTHSaG == JQTBWKxBES){QuuSAMoaOl = true;}
      while(guafLFWeOI == wpTqYVxVPE){bRuMONgujU = true;}
      while(euWJwWrOEz == euWJwWrOEz){QXkKNjWCbR = true;}
      while(JQTBWKxBES == JQTBWKxBES){UACncSIXyh = true;}
      if(OeHFDMQGTz == true){OeHFDMQGTz = false;}
      if(QOznIiAoIg == true){QOznIiAoIg = false;}
      if(aouPjQbYJA == true){aouPjQbYJA = false;}
      if(IUZwsAmQFj == true){IUZwsAmQFj = false;}
      if(FltFhtQesm == true){FltFhtQesm = false;}
      if(KIsXqYirVm == true){KIsXqYirVm = false;}
      if(jrwSpwoCtI == true){jrwSpwoCtI = false;}
      if(wiiXaoupgo == true){wiiXaoupgo = false;}
      if(zweVpAaCET == true){zweVpAaCET = false;}
      if(QuuSAMoaOl == true){QuuSAMoaOl = false;}
      if(FOkjqaYUwC == true){FOkjqaYUwC = false;}
      if(dsKfmmMZco == true){dsKfmmMZco = false;}
      if(UlxZrAnQXN == true){UlxZrAnQXN = false;}
      if(zUatjkLueP == true){zUatjkLueP = false;}
      if(aGFBpWjPfM == true){aGFBpWjPfM = false;}
      if(APyYRSQKrp == true){APyYRSQKrp = false;}
      if(mIxhDIRQuB == true){mIxhDIRQuB = false;}
      if(bRuMONgujU == true){bRuMONgujU = false;}
      if(QXkKNjWCbR == true){QXkKNjWCbR = false;}
      if(UACncSIXyh == true){UACncSIXyh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCJSFIYNEV
{ 
  void wyqqokewYB()
  { 
      bool AecqrFaKTg = false;
      bool bcbPAbPjNI = false;
      bool tSRjqyzNuT = false;
      bool ABJEyLrmCh = false;
      bool ANGyKcmRFL = false;
      bool qhgoehMrzt = false;
      bool GNOAfZTWQn = false;
      bool jbgfHgLTZN = false;
      bool KgHjcSTTZP = false;
      bool yzmIbmyGRj = false;
      bool JQAQbOBBhx = false;
      bool VsRliYGeWN = false;
      bool FzxBojoXDU = false;
      bool hEBoEtgpIO = false;
      bool QSkbsFgBYC = false;
      bool gTjEdKTzaq = false;
      bool YdxNPRqcgo = false;
      bool rPWIwmNUHj = false;
      bool CnyAnOUwKt = false;
      bool ahOQomVXMb = false;
      string PFYdbApOnL;
      string sDLhUuAgMb;
      string YFzCQVUMnV;
      string XAkglRYxjV;
      string pncIIkEXKf;
      string UKWMqKGVNF;
      string fcaSmsSewD;
      string VDxpljbqte;
      string QxCIAMcXoa;
      string KDidoMNKUP;
      string SZaHJQMfaG;
      string iPbiniaSRZ;
      string PtoVsSUTBY;
      string WQVeLqVuyi;
      string zxxhqtbAoF;
      string kurtzYjFNq;
      string wseBjStwWx;
      string NfThZSxHdy;
      string pUdumbXael;
      string GPgGmGRuyY;
      if(PFYdbApOnL == SZaHJQMfaG){AecqrFaKTg = true;}
      else if(SZaHJQMfaG == PFYdbApOnL){JQAQbOBBhx = true;}
      if(sDLhUuAgMb == iPbiniaSRZ){bcbPAbPjNI = true;}
      else if(iPbiniaSRZ == sDLhUuAgMb){VsRliYGeWN = true;}
      if(YFzCQVUMnV == PtoVsSUTBY){tSRjqyzNuT = true;}
      else if(PtoVsSUTBY == YFzCQVUMnV){FzxBojoXDU = true;}
      if(XAkglRYxjV == WQVeLqVuyi){ABJEyLrmCh = true;}
      else if(WQVeLqVuyi == XAkglRYxjV){hEBoEtgpIO = true;}
      if(pncIIkEXKf == zxxhqtbAoF){ANGyKcmRFL = true;}
      else if(zxxhqtbAoF == pncIIkEXKf){QSkbsFgBYC = true;}
      if(UKWMqKGVNF == kurtzYjFNq){qhgoehMrzt = true;}
      else if(kurtzYjFNq == UKWMqKGVNF){gTjEdKTzaq = true;}
      if(fcaSmsSewD == wseBjStwWx){GNOAfZTWQn = true;}
      else if(wseBjStwWx == fcaSmsSewD){YdxNPRqcgo = true;}
      if(VDxpljbqte == NfThZSxHdy){jbgfHgLTZN = true;}
      if(QxCIAMcXoa == pUdumbXael){KgHjcSTTZP = true;}
      if(KDidoMNKUP == GPgGmGRuyY){yzmIbmyGRj = true;}
      while(NfThZSxHdy == VDxpljbqte){rPWIwmNUHj = true;}
      while(pUdumbXael == pUdumbXael){CnyAnOUwKt = true;}
      while(GPgGmGRuyY == GPgGmGRuyY){ahOQomVXMb = true;}
      if(AecqrFaKTg == true){AecqrFaKTg = false;}
      if(bcbPAbPjNI == true){bcbPAbPjNI = false;}
      if(tSRjqyzNuT == true){tSRjqyzNuT = false;}
      if(ABJEyLrmCh == true){ABJEyLrmCh = false;}
      if(ANGyKcmRFL == true){ANGyKcmRFL = false;}
      if(qhgoehMrzt == true){qhgoehMrzt = false;}
      if(GNOAfZTWQn == true){GNOAfZTWQn = false;}
      if(jbgfHgLTZN == true){jbgfHgLTZN = false;}
      if(KgHjcSTTZP == true){KgHjcSTTZP = false;}
      if(yzmIbmyGRj == true){yzmIbmyGRj = false;}
      if(JQAQbOBBhx == true){JQAQbOBBhx = false;}
      if(VsRliYGeWN == true){VsRliYGeWN = false;}
      if(FzxBojoXDU == true){FzxBojoXDU = false;}
      if(hEBoEtgpIO == true){hEBoEtgpIO = false;}
      if(QSkbsFgBYC == true){QSkbsFgBYC = false;}
      if(gTjEdKTzaq == true){gTjEdKTzaq = false;}
      if(YdxNPRqcgo == true){YdxNPRqcgo = false;}
      if(rPWIwmNUHj == true){rPWIwmNUHj = false;}
      if(CnyAnOUwKt == true){CnyAnOUwKt = false;}
      if(ahOQomVXMb == true){ahOQomVXMb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDBGBBIPNH
{ 
  void bgxWbOSpeL()
  { 
      bool AzziuHdEmA = false;
      bool AGEirPWWhN = false;
      bool TTmdVESPtV = false;
      bool PElHWDtCiA = false;
      bool EkYXOyByLY = false;
      bool sscuUgMVMq = false;
      bool oOJRkuTxLn = false;
      bool VUnhIitOOX = false;
      bool CTEVbVbqlo = false;
      bool qYorKpbHmT = false;
      bool dEmWDYFtll = false;
      bool mxGonUKnpO = false;
      bool ScLVxweuWS = false;
      bool HlbusyggRC = false;
      bool QhEzCsRzDp = false;
      bool emRYAArQZH = false;
      bool tJWSeAVKwp = false;
      bool mcWmykYLTD = false;
      bool eeqgmTUCur = false;
      bool FPHKIGKkTB = false;
      string DkaGmVBojL;
      string LwuUpXMXPs;
      string sKwXSusNLC;
      string WGXLhmfFiD;
      string itGZlFlkOB;
      string EszQbsnDmq;
      string bmchoFXjlD;
      string qGnMKyDWkN;
      string IHzJxdGGio;
      string ycSrauRYkf;
      string gCzLKyEmFd;
      string oRRZhTnSjL;
      string zQAxEOnwkP;
      string gelFfGInzz;
      string YSBFzgLsKG;
      string HyoYgQBCGu;
      string KICpwKfLsa;
      string LzTjlfPuxX;
      string DtkeHipMYP;
      string FGgDoQQKIo;
      if(DkaGmVBojL == gCzLKyEmFd){AzziuHdEmA = true;}
      else if(gCzLKyEmFd == DkaGmVBojL){dEmWDYFtll = true;}
      if(LwuUpXMXPs == oRRZhTnSjL){AGEirPWWhN = true;}
      else if(oRRZhTnSjL == LwuUpXMXPs){mxGonUKnpO = true;}
      if(sKwXSusNLC == zQAxEOnwkP){TTmdVESPtV = true;}
      else if(zQAxEOnwkP == sKwXSusNLC){ScLVxweuWS = true;}
      if(WGXLhmfFiD == gelFfGInzz){PElHWDtCiA = true;}
      else if(gelFfGInzz == WGXLhmfFiD){HlbusyggRC = true;}
      if(itGZlFlkOB == YSBFzgLsKG){EkYXOyByLY = true;}
      else if(YSBFzgLsKG == itGZlFlkOB){QhEzCsRzDp = true;}
      if(EszQbsnDmq == HyoYgQBCGu){sscuUgMVMq = true;}
      else if(HyoYgQBCGu == EszQbsnDmq){emRYAArQZH = true;}
      if(bmchoFXjlD == KICpwKfLsa){oOJRkuTxLn = true;}
      else if(KICpwKfLsa == bmchoFXjlD){tJWSeAVKwp = true;}
      if(qGnMKyDWkN == LzTjlfPuxX){VUnhIitOOX = true;}
      if(IHzJxdGGio == DtkeHipMYP){CTEVbVbqlo = true;}
      if(ycSrauRYkf == FGgDoQQKIo){qYorKpbHmT = true;}
      while(LzTjlfPuxX == qGnMKyDWkN){mcWmykYLTD = true;}
      while(DtkeHipMYP == DtkeHipMYP){eeqgmTUCur = true;}
      while(FGgDoQQKIo == FGgDoQQKIo){FPHKIGKkTB = true;}
      if(AzziuHdEmA == true){AzziuHdEmA = false;}
      if(AGEirPWWhN == true){AGEirPWWhN = false;}
      if(TTmdVESPtV == true){TTmdVESPtV = false;}
      if(PElHWDtCiA == true){PElHWDtCiA = false;}
      if(EkYXOyByLY == true){EkYXOyByLY = false;}
      if(sscuUgMVMq == true){sscuUgMVMq = false;}
      if(oOJRkuTxLn == true){oOJRkuTxLn = false;}
      if(VUnhIitOOX == true){VUnhIitOOX = false;}
      if(CTEVbVbqlo == true){CTEVbVbqlo = false;}
      if(qYorKpbHmT == true){qYorKpbHmT = false;}
      if(dEmWDYFtll == true){dEmWDYFtll = false;}
      if(mxGonUKnpO == true){mxGonUKnpO = false;}
      if(ScLVxweuWS == true){ScLVxweuWS = false;}
      if(HlbusyggRC == true){HlbusyggRC = false;}
      if(QhEzCsRzDp == true){QhEzCsRzDp = false;}
      if(emRYAArQZH == true){emRYAArQZH = false;}
      if(tJWSeAVKwp == true){tJWSeAVKwp = false;}
      if(mcWmykYLTD == true){mcWmykYLTD = false;}
      if(eeqgmTUCur == true){eeqgmTUCur = false;}
      if(FPHKIGKkTB == true){FPHKIGKkTB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVKBGYQPBD
{ 
  void LfnkNreRcU()
  { 
      bool MBIASrOVLA = false;
      bool ZzssRiPmxf = false;
      bool fZSSISYlzl = false;
      bool JeqziqEifr = false;
      bool PkzfWRTnfF = false;
      bool JKtfllhpqA = false;
      bool SbVYptHtKZ = false;
      bool dfGFPtamup = false;
      bool zjGtczkKMw = false;
      bool IOqeYnPZoc = false;
      bool KZdFadDnPq = false;
      bool LttBBiVawq = false;
      bool IwgNQPnafb = false;
      bool eBxSfZFBTy = false;
      bool uwuUkOTpdp = false;
      bool RncyTNrQnK = false;
      bool obHmLJxbUb = false;
      bool cUHxuMBLcC = false;
      bool wxxpJqXzyS = false;
      bool goMIITnHJa = false;
      string oTRRJiiARu;
      string LDxDgwzyKW;
      string HgNrUOYzyW;
      string bCQMSWNfQL;
      string LqeZHgOSsl;
      string DriaDHGYxt;
      string JjCtSJmjjJ;
      string hTgzKQCnkn;
      string zGGLTiSpJL;
      string PohVBbnjGx;
      string sdiiDiKjQl;
      string FSmJuDdqZj;
      string pwaXsslLxh;
      string bRgntUXWHk;
      string YiZWGxBYay;
      string yxKWHxDKoK;
      string wzlhKmkzPZ;
      string eGinKGWDRw;
      string rNjzjdHKfx;
      string RMhxnYxqMS;
      if(oTRRJiiARu == sdiiDiKjQl){MBIASrOVLA = true;}
      else if(sdiiDiKjQl == oTRRJiiARu){KZdFadDnPq = true;}
      if(LDxDgwzyKW == FSmJuDdqZj){ZzssRiPmxf = true;}
      else if(FSmJuDdqZj == LDxDgwzyKW){LttBBiVawq = true;}
      if(HgNrUOYzyW == pwaXsslLxh){fZSSISYlzl = true;}
      else if(pwaXsslLxh == HgNrUOYzyW){IwgNQPnafb = true;}
      if(bCQMSWNfQL == bRgntUXWHk){JeqziqEifr = true;}
      else if(bRgntUXWHk == bCQMSWNfQL){eBxSfZFBTy = true;}
      if(LqeZHgOSsl == YiZWGxBYay){PkzfWRTnfF = true;}
      else if(YiZWGxBYay == LqeZHgOSsl){uwuUkOTpdp = true;}
      if(DriaDHGYxt == yxKWHxDKoK){JKtfllhpqA = true;}
      else if(yxKWHxDKoK == DriaDHGYxt){RncyTNrQnK = true;}
      if(JjCtSJmjjJ == wzlhKmkzPZ){SbVYptHtKZ = true;}
      else if(wzlhKmkzPZ == JjCtSJmjjJ){obHmLJxbUb = true;}
      if(hTgzKQCnkn == eGinKGWDRw){dfGFPtamup = true;}
      if(zGGLTiSpJL == rNjzjdHKfx){zjGtczkKMw = true;}
      if(PohVBbnjGx == RMhxnYxqMS){IOqeYnPZoc = true;}
      while(eGinKGWDRw == hTgzKQCnkn){cUHxuMBLcC = true;}
      while(rNjzjdHKfx == rNjzjdHKfx){wxxpJqXzyS = true;}
      while(RMhxnYxqMS == RMhxnYxqMS){goMIITnHJa = true;}
      if(MBIASrOVLA == true){MBIASrOVLA = false;}
      if(ZzssRiPmxf == true){ZzssRiPmxf = false;}
      if(fZSSISYlzl == true){fZSSISYlzl = false;}
      if(JeqziqEifr == true){JeqziqEifr = false;}
      if(PkzfWRTnfF == true){PkzfWRTnfF = false;}
      if(JKtfllhpqA == true){JKtfllhpqA = false;}
      if(SbVYptHtKZ == true){SbVYptHtKZ = false;}
      if(dfGFPtamup == true){dfGFPtamup = false;}
      if(zjGtczkKMw == true){zjGtczkKMw = false;}
      if(IOqeYnPZoc == true){IOqeYnPZoc = false;}
      if(KZdFadDnPq == true){KZdFadDnPq = false;}
      if(LttBBiVawq == true){LttBBiVawq = false;}
      if(IwgNQPnafb == true){IwgNQPnafb = false;}
      if(eBxSfZFBTy == true){eBxSfZFBTy = false;}
      if(uwuUkOTpdp == true){uwuUkOTpdp = false;}
      if(RncyTNrQnK == true){RncyTNrQnK = false;}
      if(obHmLJxbUb == true){obHmLJxbUb = false;}
      if(cUHxuMBLcC == true){cUHxuMBLcC = false;}
      if(wxxpJqXzyS == true){wxxpJqXzyS = false;}
      if(goMIITnHJa == true){goMIITnHJa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JORJASHYVN
{ 
  void GJiRNWSRqb()
  { 
      bool CQmGDYUDaW = false;
      bool utQESzFhhG = false;
      bool BZXSqtukFK = false;
      bool BsEOKURPTf = false;
      bool KggPWNCGTr = false;
      bool btGYYcsTPJ = false;
      bool cjyQVCpCty = false;
      bool hoNCwUrHwc = false;
      bool rnQMiGmeog = false;
      bool bxAKCahPtU = false;
      bool XzMUJlfDbE = false;
      bool jkXlRoSkhO = false;
      bool OKNMWjoDzV = false;
      bool lcNaFrbuDw = false;
      bool ZiDkxpYOsN = false;
      bool HxhfFMlzyY = false;
      bool xcDFRHWxfY = false;
      bool MWgknfGcPf = false;
      bool KZKlOothUr = false;
      bool GbxdzwfxSo = false;
      string swozexakVO;
      string whtVrFMSOs;
      string NsntgacyMy;
      string tKXRiBTZwX;
      string shPqwxIuGC;
      string UcjXpzHuSE;
      string UcYWUkJclq;
      string klVqAfcxxj;
      string RhrJdRazbi;
      string sYHrCPIsVK;
      string mfIORhGsXJ;
      string WJxhlljPrC;
      string KJBCxMdcnj;
      string XjamwlYcru;
      string KgbRMjaYGQ;
      string frATAcdGRE;
      string EcFmllhKlz;
      string MHXwrchjoM;
      string kEWXEejHlS;
      string ISLmqhbofa;
      if(swozexakVO == mfIORhGsXJ){CQmGDYUDaW = true;}
      else if(mfIORhGsXJ == swozexakVO){XzMUJlfDbE = true;}
      if(whtVrFMSOs == WJxhlljPrC){utQESzFhhG = true;}
      else if(WJxhlljPrC == whtVrFMSOs){jkXlRoSkhO = true;}
      if(NsntgacyMy == KJBCxMdcnj){BZXSqtukFK = true;}
      else if(KJBCxMdcnj == NsntgacyMy){OKNMWjoDzV = true;}
      if(tKXRiBTZwX == XjamwlYcru){BsEOKURPTf = true;}
      else if(XjamwlYcru == tKXRiBTZwX){lcNaFrbuDw = true;}
      if(shPqwxIuGC == KgbRMjaYGQ){KggPWNCGTr = true;}
      else if(KgbRMjaYGQ == shPqwxIuGC){ZiDkxpYOsN = true;}
      if(UcjXpzHuSE == frATAcdGRE){btGYYcsTPJ = true;}
      else if(frATAcdGRE == UcjXpzHuSE){HxhfFMlzyY = true;}
      if(UcYWUkJclq == EcFmllhKlz){cjyQVCpCty = true;}
      else if(EcFmllhKlz == UcYWUkJclq){xcDFRHWxfY = true;}
      if(klVqAfcxxj == MHXwrchjoM){hoNCwUrHwc = true;}
      if(RhrJdRazbi == kEWXEejHlS){rnQMiGmeog = true;}
      if(sYHrCPIsVK == ISLmqhbofa){bxAKCahPtU = true;}
      while(MHXwrchjoM == klVqAfcxxj){MWgknfGcPf = true;}
      while(kEWXEejHlS == kEWXEejHlS){KZKlOothUr = true;}
      while(ISLmqhbofa == ISLmqhbofa){GbxdzwfxSo = true;}
      if(CQmGDYUDaW == true){CQmGDYUDaW = false;}
      if(utQESzFhhG == true){utQESzFhhG = false;}
      if(BZXSqtukFK == true){BZXSqtukFK = false;}
      if(BsEOKURPTf == true){BsEOKURPTf = false;}
      if(KggPWNCGTr == true){KggPWNCGTr = false;}
      if(btGYYcsTPJ == true){btGYYcsTPJ = false;}
      if(cjyQVCpCty == true){cjyQVCpCty = false;}
      if(hoNCwUrHwc == true){hoNCwUrHwc = false;}
      if(rnQMiGmeog == true){rnQMiGmeog = false;}
      if(bxAKCahPtU == true){bxAKCahPtU = false;}
      if(XzMUJlfDbE == true){XzMUJlfDbE = false;}
      if(jkXlRoSkhO == true){jkXlRoSkhO = false;}
      if(OKNMWjoDzV == true){OKNMWjoDzV = false;}
      if(lcNaFrbuDw == true){lcNaFrbuDw = false;}
      if(ZiDkxpYOsN == true){ZiDkxpYOsN = false;}
      if(HxhfFMlzyY == true){HxhfFMlzyY = false;}
      if(xcDFRHWxfY == true){xcDFRHWxfY = false;}
      if(MWgknfGcPf == true){MWgknfGcPf = false;}
      if(KZKlOothUr == true){KZKlOothUr = false;}
      if(GbxdzwfxSo == true){GbxdzwfxSo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSBGTNYELH
{ 
  void QCzwQxoSbT()
  { 
      bool SNJbSyJBul = false;
      bool VSHpWVTdBy = false;
      bool IuDYIOHBSY = false;
      bool YgXAiBzWhb = false;
      bool BmrerVCKUq = false;
      bool IigIYXJjSD = false;
      bool qHiWNouHHV = false;
      bool WwwYwUCYfm = false;
      bool MwgaPozOaK = false;
      bool qPDdjtEURD = false;
      bool ZtDyUMmHME = false;
      bool UjDfquaHHX = false;
      bool pfgwdHsRoB = false;
      bool QhHcMRshGD = false;
      bool BrCWpGLWmo = false;
      bool SwNsNtNGTM = false;
      bool TUSKmmcaTY = false;
      bool CsAEVxcKGX = false;
      bool wVeziTUOPS = false;
      bool EmNsjgYriC = false;
      string ftoYRjyWPh;
      string jWhxpmiAyr;
      string xlylWEKImL;
      string DrZzoRwoUp;
      string AJKVtJZITZ;
      string fUdDLswCCM;
      string ZpiEdrxhHY;
      string qseHrnbbrM;
      string dBnMeiNWnu;
      string VsmHPJZGqC;
      string MrBuiloVLX;
      string RTKoiYCWYu;
      string datLDxGWqi;
      string NUkoAlzscs;
      string tqKPdBixYq;
      string HCgwYlxorl;
      string eRdbJwiUnx;
      string YIsfAlPdhB;
      string OIyAaLnnQO;
      string nJBqNbNhGg;
      if(ftoYRjyWPh == MrBuiloVLX){SNJbSyJBul = true;}
      else if(MrBuiloVLX == ftoYRjyWPh){ZtDyUMmHME = true;}
      if(jWhxpmiAyr == RTKoiYCWYu){VSHpWVTdBy = true;}
      else if(RTKoiYCWYu == jWhxpmiAyr){UjDfquaHHX = true;}
      if(xlylWEKImL == datLDxGWqi){IuDYIOHBSY = true;}
      else if(datLDxGWqi == xlylWEKImL){pfgwdHsRoB = true;}
      if(DrZzoRwoUp == NUkoAlzscs){YgXAiBzWhb = true;}
      else if(NUkoAlzscs == DrZzoRwoUp){QhHcMRshGD = true;}
      if(AJKVtJZITZ == tqKPdBixYq){BmrerVCKUq = true;}
      else if(tqKPdBixYq == AJKVtJZITZ){BrCWpGLWmo = true;}
      if(fUdDLswCCM == HCgwYlxorl){IigIYXJjSD = true;}
      else if(HCgwYlxorl == fUdDLswCCM){SwNsNtNGTM = true;}
      if(ZpiEdrxhHY == eRdbJwiUnx){qHiWNouHHV = true;}
      else if(eRdbJwiUnx == ZpiEdrxhHY){TUSKmmcaTY = true;}
      if(qseHrnbbrM == YIsfAlPdhB){WwwYwUCYfm = true;}
      if(dBnMeiNWnu == OIyAaLnnQO){MwgaPozOaK = true;}
      if(VsmHPJZGqC == nJBqNbNhGg){qPDdjtEURD = true;}
      while(YIsfAlPdhB == qseHrnbbrM){CsAEVxcKGX = true;}
      while(OIyAaLnnQO == OIyAaLnnQO){wVeziTUOPS = true;}
      while(nJBqNbNhGg == nJBqNbNhGg){EmNsjgYriC = true;}
      if(SNJbSyJBul == true){SNJbSyJBul = false;}
      if(VSHpWVTdBy == true){VSHpWVTdBy = false;}
      if(IuDYIOHBSY == true){IuDYIOHBSY = false;}
      if(YgXAiBzWhb == true){YgXAiBzWhb = false;}
      if(BmrerVCKUq == true){BmrerVCKUq = false;}
      if(IigIYXJjSD == true){IigIYXJjSD = false;}
      if(qHiWNouHHV == true){qHiWNouHHV = false;}
      if(WwwYwUCYfm == true){WwwYwUCYfm = false;}
      if(MwgaPozOaK == true){MwgaPozOaK = false;}
      if(qPDdjtEURD == true){qPDdjtEURD = false;}
      if(ZtDyUMmHME == true){ZtDyUMmHME = false;}
      if(UjDfquaHHX == true){UjDfquaHHX = false;}
      if(pfgwdHsRoB == true){pfgwdHsRoB = false;}
      if(QhHcMRshGD == true){QhHcMRshGD = false;}
      if(BrCWpGLWmo == true){BrCWpGLWmo = false;}
      if(SwNsNtNGTM == true){SwNsNtNGTM = false;}
      if(TUSKmmcaTY == true){TUSKmmcaTY = false;}
      if(CsAEVxcKGX == true){CsAEVxcKGX = false;}
      if(wVeziTUOPS == true){wVeziTUOPS = false;}
      if(EmNsjgYriC == true){EmNsjgYriC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHLFUQSZUA
{ 
  void NUSVVUrYae()
  { 
      bool nIcojFrQLT = false;
      bool tsMJVZsYRZ = false;
      bool skYNBCVSWD = false;
      bool ZfjfafXcye = false;
      bool FttMpNHIXy = false;
      bool zKUZwCiPng = false;
      bool jZtItNIfho = false;
      bool BPalUyqLWm = false;
      bool uNtYEOLKjX = false;
      bool wHoQuezlSc = false;
      bool FaahwiihFx = false;
      bool LWsAlWeVEe = false;
      bool CywJstaKqo = false;
      bool yEsshTmMcU = false;
      bool ecElMYOndY = false;
      bool AdhnaGeQoB = false;
      bool HYqPzGdzRS = false;
      bool iSrizYsJxT = false;
      bool fmfSoTWFRa = false;
      bool oVWaMGkomF = false;
      string aqWygMJoAu;
      string FuEIBQuMiU;
      string YYMPeRjRIG;
      string OMMwXRksGK;
      string QBxoYHtiFr;
      string FhWmxCdHTP;
      string bqgsfriHkj;
      string eBGYEWaXqW;
      string WBMQBfpYzU;
      string mdYphYUDIf;
      string XlyVMDbyia;
      string bGPxraeQrA;
      string CKIPwBcPpe;
      string CWOKyjDqEx;
      string ErpYsgNbxH;
      string tELIdNciYK;
      string ZLHDXErFyI;
      string WnLtwJTjVP;
      string nAShkxLGfk;
      string GURsXrjmAo;
      if(aqWygMJoAu == XlyVMDbyia){nIcojFrQLT = true;}
      else if(XlyVMDbyia == aqWygMJoAu){FaahwiihFx = true;}
      if(FuEIBQuMiU == bGPxraeQrA){tsMJVZsYRZ = true;}
      else if(bGPxraeQrA == FuEIBQuMiU){LWsAlWeVEe = true;}
      if(YYMPeRjRIG == CKIPwBcPpe){skYNBCVSWD = true;}
      else if(CKIPwBcPpe == YYMPeRjRIG){CywJstaKqo = true;}
      if(OMMwXRksGK == CWOKyjDqEx){ZfjfafXcye = true;}
      else if(CWOKyjDqEx == OMMwXRksGK){yEsshTmMcU = true;}
      if(QBxoYHtiFr == ErpYsgNbxH){FttMpNHIXy = true;}
      else if(ErpYsgNbxH == QBxoYHtiFr){ecElMYOndY = true;}
      if(FhWmxCdHTP == tELIdNciYK){zKUZwCiPng = true;}
      else if(tELIdNciYK == FhWmxCdHTP){AdhnaGeQoB = true;}
      if(bqgsfriHkj == ZLHDXErFyI){jZtItNIfho = true;}
      else if(ZLHDXErFyI == bqgsfriHkj){HYqPzGdzRS = true;}
      if(eBGYEWaXqW == WnLtwJTjVP){BPalUyqLWm = true;}
      if(WBMQBfpYzU == nAShkxLGfk){uNtYEOLKjX = true;}
      if(mdYphYUDIf == GURsXrjmAo){wHoQuezlSc = true;}
      while(WnLtwJTjVP == eBGYEWaXqW){iSrizYsJxT = true;}
      while(nAShkxLGfk == nAShkxLGfk){fmfSoTWFRa = true;}
      while(GURsXrjmAo == GURsXrjmAo){oVWaMGkomF = true;}
      if(nIcojFrQLT == true){nIcojFrQLT = false;}
      if(tsMJVZsYRZ == true){tsMJVZsYRZ = false;}
      if(skYNBCVSWD == true){skYNBCVSWD = false;}
      if(ZfjfafXcye == true){ZfjfafXcye = false;}
      if(FttMpNHIXy == true){FttMpNHIXy = false;}
      if(zKUZwCiPng == true){zKUZwCiPng = false;}
      if(jZtItNIfho == true){jZtItNIfho = false;}
      if(BPalUyqLWm == true){BPalUyqLWm = false;}
      if(uNtYEOLKjX == true){uNtYEOLKjX = false;}
      if(wHoQuezlSc == true){wHoQuezlSc = false;}
      if(FaahwiihFx == true){FaahwiihFx = false;}
      if(LWsAlWeVEe == true){LWsAlWeVEe = false;}
      if(CywJstaKqo == true){CywJstaKqo = false;}
      if(yEsshTmMcU == true){yEsshTmMcU = false;}
      if(ecElMYOndY == true){ecElMYOndY = false;}
      if(AdhnaGeQoB == true){AdhnaGeQoB = false;}
      if(HYqPzGdzRS == true){HYqPzGdzRS = false;}
      if(iSrizYsJxT == true){iSrizYsJxT = false;}
      if(fmfSoTWFRa == true){fmfSoTWFRa = false;}
      if(oVWaMGkomF == true){oVWaMGkomF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNCRJBHQSX
{ 
  void FPASKjAWzF()
  { 
      bool SYmFkajndF = false;
      bool FORuOYwryP = false;
      bool KAYzoDxrGw = false;
      bool MqwyzcaOmj = false;
      bool zJTazlwfwd = false;
      bool DaAVeRzmQh = false;
      bool cqggsOSTwl = false;
      bool xhFNQBgxzC = false;
      bool HRwcslqaSg = false;
      bool cmxFHHclhk = false;
      bool TbjJfVUlFd = false;
      bool kBmNaLuEnH = false;
      bool WqAPIKjzGI = false;
      bool XtPOiehlwW = false;
      bool QEUnuaziew = false;
      bool MXyaNbbTAV = false;
      bool kUfwFplYeu = false;
      bool dIIQpSVLTh = false;
      bool KBUJwAwoAH = false;
      bool CNkakuXYiF = false;
      string OxILRAAJLt;
      string atypqfCtCo;
      string QTOPLKABEe;
      string hiVWyVwyrn;
      string OYcBtRslQf;
      string xjGtOuisAG;
      string AzEgMrYbqU;
      string iECOZrqNUt;
      string QOkYhybbHD;
      string mDylnOTuoC;
      string rRtuwrgrTW;
      string EVYGokOfyN;
      string QxTnhfFQaL;
      string XuXSBzTobo;
      string QjHkzQerwC;
      string AnxaluyGNQ;
      string lQQIzIxFEp;
      string QZDJxfoinR;
      string BNUXKixxgF;
      string BNbLCASylp;
      if(OxILRAAJLt == rRtuwrgrTW){SYmFkajndF = true;}
      else if(rRtuwrgrTW == OxILRAAJLt){TbjJfVUlFd = true;}
      if(atypqfCtCo == EVYGokOfyN){FORuOYwryP = true;}
      else if(EVYGokOfyN == atypqfCtCo){kBmNaLuEnH = true;}
      if(QTOPLKABEe == QxTnhfFQaL){KAYzoDxrGw = true;}
      else if(QxTnhfFQaL == QTOPLKABEe){WqAPIKjzGI = true;}
      if(hiVWyVwyrn == XuXSBzTobo){MqwyzcaOmj = true;}
      else if(XuXSBzTobo == hiVWyVwyrn){XtPOiehlwW = true;}
      if(OYcBtRslQf == QjHkzQerwC){zJTazlwfwd = true;}
      else if(QjHkzQerwC == OYcBtRslQf){QEUnuaziew = true;}
      if(xjGtOuisAG == AnxaluyGNQ){DaAVeRzmQh = true;}
      else if(AnxaluyGNQ == xjGtOuisAG){MXyaNbbTAV = true;}
      if(AzEgMrYbqU == lQQIzIxFEp){cqggsOSTwl = true;}
      else if(lQQIzIxFEp == AzEgMrYbqU){kUfwFplYeu = true;}
      if(iECOZrqNUt == QZDJxfoinR){xhFNQBgxzC = true;}
      if(QOkYhybbHD == BNUXKixxgF){HRwcslqaSg = true;}
      if(mDylnOTuoC == BNbLCASylp){cmxFHHclhk = true;}
      while(QZDJxfoinR == iECOZrqNUt){dIIQpSVLTh = true;}
      while(BNUXKixxgF == BNUXKixxgF){KBUJwAwoAH = true;}
      while(BNbLCASylp == BNbLCASylp){CNkakuXYiF = true;}
      if(SYmFkajndF == true){SYmFkajndF = false;}
      if(FORuOYwryP == true){FORuOYwryP = false;}
      if(KAYzoDxrGw == true){KAYzoDxrGw = false;}
      if(MqwyzcaOmj == true){MqwyzcaOmj = false;}
      if(zJTazlwfwd == true){zJTazlwfwd = false;}
      if(DaAVeRzmQh == true){DaAVeRzmQh = false;}
      if(cqggsOSTwl == true){cqggsOSTwl = false;}
      if(xhFNQBgxzC == true){xhFNQBgxzC = false;}
      if(HRwcslqaSg == true){HRwcslqaSg = false;}
      if(cmxFHHclhk == true){cmxFHHclhk = false;}
      if(TbjJfVUlFd == true){TbjJfVUlFd = false;}
      if(kBmNaLuEnH == true){kBmNaLuEnH = false;}
      if(WqAPIKjzGI == true){WqAPIKjzGI = false;}
      if(XtPOiehlwW == true){XtPOiehlwW = false;}
      if(QEUnuaziew == true){QEUnuaziew = false;}
      if(MXyaNbbTAV == true){MXyaNbbTAV = false;}
      if(kUfwFplYeu == true){kUfwFplYeu = false;}
      if(dIIQpSVLTh == true){dIIQpSVLTh = false;}
      if(KBUJwAwoAH == true){KBUJwAwoAH = false;}
      if(CNkakuXYiF == true){CNkakuXYiF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JRCOZRJAAS
{ 
  void OwhDymHzNr()
  { 
      bool AJrRxuQSFr = false;
      bool yoOhEqsgOU = false;
      bool YiCIcXIXAW = false;
      bool TCmQRiFJfA = false;
      bool uCTGwtzhrS = false;
      bool elLogRGjnY = false;
      bool msRhXuCxQU = false;
      bool kiANYVPwLi = false;
      bool Yaehqhqxiz = false;
      bool bVVHNCkkhA = false;
      bool qBRWgukxQL = false;
      bool CKYEALNjpo = false;
      bool EEOQrPNrAV = false;
      bool jdNKrWJHBw = false;
      bool xsgWxRxRHB = false;
      bool nBtrwlmAeQ = false;
      bool hrxubXxNLc = false;
      bool CGitrKXqSa = false;
      bool SukygijUOF = false;
      bool iIcjNEukuZ = false;
      string ASlULdOFhZ;
      string VtKlGoaLCP;
      string KVShgggisl;
      string PGQAWouJrS;
      string oMiBJTjXrw;
      string BtGDdezEne;
      string wfLuKOcKPQ;
      string tQSjaylQYN;
      string wIqwkUzNVr;
      string ppVNWJAmqt;
      string pZIaBjaWbe;
      string rheZimoOKp;
      string POnWaEtFMQ;
      string yyZdWVAPtA;
      string tckqAIKudj;
      string UkcBebllAx;
      string pUJLgtHBDM;
      string lYUKumcwWR;
      string syacwMVYyu;
      string iOPxJYSZJF;
      if(ASlULdOFhZ == pZIaBjaWbe){AJrRxuQSFr = true;}
      else if(pZIaBjaWbe == ASlULdOFhZ){qBRWgukxQL = true;}
      if(VtKlGoaLCP == rheZimoOKp){yoOhEqsgOU = true;}
      else if(rheZimoOKp == VtKlGoaLCP){CKYEALNjpo = true;}
      if(KVShgggisl == POnWaEtFMQ){YiCIcXIXAW = true;}
      else if(POnWaEtFMQ == KVShgggisl){EEOQrPNrAV = true;}
      if(PGQAWouJrS == yyZdWVAPtA){TCmQRiFJfA = true;}
      else if(yyZdWVAPtA == PGQAWouJrS){jdNKrWJHBw = true;}
      if(oMiBJTjXrw == tckqAIKudj){uCTGwtzhrS = true;}
      else if(tckqAIKudj == oMiBJTjXrw){xsgWxRxRHB = true;}
      if(BtGDdezEne == UkcBebllAx){elLogRGjnY = true;}
      else if(UkcBebllAx == BtGDdezEne){nBtrwlmAeQ = true;}
      if(wfLuKOcKPQ == pUJLgtHBDM){msRhXuCxQU = true;}
      else if(pUJLgtHBDM == wfLuKOcKPQ){hrxubXxNLc = true;}
      if(tQSjaylQYN == lYUKumcwWR){kiANYVPwLi = true;}
      if(wIqwkUzNVr == syacwMVYyu){Yaehqhqxiz = true;}
      if(ppVNWJAmqt == iOPxJYSZJF){bVVHNCkkhA = true;}
      while(lYUKumcwWR == tQSjaylQYN){CGitrKXqSa = true;}
      while(syacwMVYyu == syacwMVYyu){SukygijUOF = true;}
      while(iOPxJYSZJF == iOPxJYSZJF){iIcjNEukuZ = true;}
      if(AJrRxuQSFr == true){AJrRxuQSFr = false;}
      if(yoOhEqsgOU == true){yoOhEqsgOU = false;}
      if(YiCIcXIXAW == true){YiCIcXIXAW = false;}
      if(TCmQRiFJfA == true){TCmQRiFJfA = false;}
      if(uCTGwtzhrS == true){uCTGwtzhrS = false;}
      if(elLogRGjnY == true){elLogRGjnY = false;}
      if(msRhXuCxQU == true){msRhXuCxQU = false;}
      if(kiANYVPwLi == true){kiANYVPwLi = false;}
      if(Yaehqhqxiz == true){Yaehqhqxiz = false;}
      if(bVVHNCkkhA == true){bVVHNCkkhA = false;}
      if(qBRWgukxQL == true){qBRWgukxQL = false;}
      if(CKYEALNjpo == true){CKYEALNjpo = false;}
      if(EEOQrPNrAV == true){EEOQrPNrAV = false;}
      if(jdNKrWJHBw == true){jdNKrWJHBw = false;}
      if(xsgWxRxRHB == true){xsgWxRxRHB = false;}
      if(nBtrwlmAeQ == true){nBtrwlmAeQ = false;}
      if(hrxubXxNLc == true){hrxubXxNLc = false;}
      if(CGitrKXqSa == true){CGitrKXqSa = false;}
      if(SukygijUOF == true){SukygijUOF = false;}
      if(iIcjNEukuZ == true){iIcjNEukuZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDGTWGDAGS
{ 
  void YNXJyoPIuG()
  { 
      bool tmUogfzwFm = false;
      bool jUzxBjsJgS = false;
      bool kAuLEnGYio = false;
      bool dmTrArQniP = false;
      bool NQrRciKdAK = false;
      bool EjhFssrJjr = false;
      bool YaMPJxBHwI = false;
      bool TEaQFTIchV = false;
      bool ccXXktFOzG = false;
      bool zHEpplDbHf = false;
      bool hDgqqAIQzY = false;
      bool kPaOOwCneP = false;
      bool qlHoIMAjaT = false;
      bool QfVCmZuggj = false;
      bool koPZVjfobs = false;
      bool iOwqnuuqhe = false;
      bool AYpfIFsYao = false;
      bool AVHueCWhTX = false;
      bool fKIgjBidNr = false;
      bool dDyCjMyiRP = false;
      string xyohEOJKut;
      string BAgRnQbYAl;
      string DBREcDgHOb;
      string STgNHPpZYs;
      string PfpajxceGb;
      string FzcGpufkFA;
      string gCwSahSTKY;
      string ZCAHVWKpTe;
      string aBBlVTpaWL;
      string iFUXLNjXAC;
      string eJUhCDzVjS;
      string koQZZfAJwH;
      string qrwyoUgbuI;
      string mmpQAQgTjR;
      string UTpEasntye;
      string MZarLlMWrh;
      string WWZbfxzAZI;
      string ygZemXBrWu;
      string fldPuMMyFN;
      string EKaBuxsOXd;
      if(xyohEOJKut == eJUhCDzVjS){tmUogfzwFm = true;}
      else if(eJUhCDzVjS == xyohEOJKut){hDgqqAIQzY = true;}
      if(BAgRnQbYAl == koQZZfAJwH){jUzxBjsJgS = true;}
      else if(koQZZfAJwH == BAgRnQbYAl){kPaOOwCneP = true;}
      if(DBREcDgHOb == qrwyoUgbuI){kAuLEnGYio = true;}
      else if(qrwyoUgbuI == DBREcDgHOb){qlHoIMAjaT = true;}
      if(STgNHPpZYs == mmpQAQgTjR){dmTrArQniP = true;}
      else if(mmpQAQgTjR == STgNHPpZYs){QfVCmZuggj = true;}
      if(PfpajxceGb == UTpEasntye){NQrRciKdAK = true;}
      else if(UTpEasntye == PfpajxceGb){koPZVjfobs = true;}
      if(FzcGpufkFA == MZarLlMWrh){EjhFssrJjr = true;}
      else if(MZarLlMWrh == FzcGpufkFA){iOwqnuuqhe = true;}
      if(gCwSahSTKY == WWZbfxzAZI){YaMPJxBHwI = true;}
      else if(WWZbfxzAZI == gCwSahSTKY){AYpfIFsYao = true;}
      if(ZCAHVWKpTe == ygZemXBrWu){TEaQFTIchV = true;}
      if(aBBlVTpaWL == fldPuMMyFN){ccXXktFOzG = true;}
      if(iFUXLNjXAC == EKaBuxsOXd){zHEpplDbHf = true;}
      while(ygZemXBrWu == ZCAHVWKpTe){AVHueCWhTX = true;}
      while(fldPuMMyFN == fldPuMMyFN){fKIgjBidNr = true;}
      while(EKaBuxsOXd == EKaBuxsOXd){dDyCjMyiRP = true;}
      if(tmUogfzwFm == true){tmUogfzwFm = false;}
      if(jUzxBjsJgS == true){jUzxBjsJgS = false;}
      if(kAuLEnGYio == true){kAuLEnGYio = false;}
      if(dmTrArQniP == true){dmTrArQniP = false;}
      if(NQrRciKdAK == true){NQrRciKdAK = false;}
      if(EjhFssrJjr == true){EjhFssrJjr = false;}
      if(YaMPJxBHwI == true){YaMPJxBHwI = false;}
      if(TEaQFTIchV == true){TEaQFTIchV = false;}
      if(ccXXktFOzG == true){ccXXktFOzG = false;}
      if(zHEpplDbHf == true){zHEpplDbHf = false;}
      if(hDgqqAIQzY == true){hDgqqAIQzY = false;}
      if(kPaOOwCneP == true){kPaOOwCneP = false;}
      if(qlHoIMAjaT == true){qlHoIMAjaT = false;}
      if(QfVCmZuggj == true){QfVCmZuggj = false;}
      if(koPZVjfobs == true){koPZVjfobs = false;}
      if(iOwqnuuqhe == true){iOwqnuuqhe = false;}
      if(AYpfIFsYao == true){AYpfIFsYao = false;}
      if(AVHueCWhTX == true){AVHueCWhTX = false;}
      if(fKIgjBidNr == true){fKIgjBidNr = false;}
      if(dDyCjMyiRP == true){dDyCjMyiRP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQQYNYCTAQ
{ 
  void MouPfiwWuW()
  { 
      bool uKyDWhIwAI = false;
      bool VNLuVqaXBD = false;
      bool lVMVBdRknX = false;
      bool ofYmqRNEPE = false;
      bool OqwuAPzIDP = false;
      bool ERKYlZycBs = false;
      bool QWHbSonYDE = false;
      bool cVHxntYQVk = false;
      bool dIgYSXVzAQ = false;
      bool SkCWmrjUcK = false;
      bool aaFzliJMjq = false;
      bool BgGQOIoiIt = false;
      bool SoXlkrSkKw = false;
      bool KDnKKDDhlj = false;
      bool NJPJPkdlHe = false;
      bool DBLhqlDSOt = false;
      bool PYCnfxswFK = false;
      bool EHwXgJZNWz = false;
      bool OgcerJqGTX = false;
      bool AkSrUoGacR = false;
      string irkzwsOWLM;
      string wnMFHiJjBm;
      string IyBUcLJmMo;
      string GENjpYyooS;
      string lNTcKixuRl;
      string ZTsgNkqQVj;
      string jbKVGqacOi;
      string kUthBudXJs;
      string NNUZPmLgWF;
      string ggSEhKDyWS;
      string IUfiBFYKfS;
      string GTGcWVGjGS;
      string ftFJBDCpzp;
      string qfBqkrgkYK;
      string OABEyNaphM;
      string DTrEmOOWhy;
      string DiLoaZRPqd;
      string oULuDerBKm;
      string cLHmmWnwDV;
      string cKDZGfoLcX;
      if(irkzwsOWLM == IUfiBFYKfS){uKyDWhIwAI = true;}
      else if(IUfiBFYKfS == irkzwsOWLM){aaFzliJMjq = true;}
      if(wnMFHiJjBm == GTGcWVGjGS){VNLuVqaXBD = true;}
      else if(GTGcWVGjGS == wnMFHiJjBm){BgGQOIoiIt = true;}
      if(IyBUcLJmMo == ftFJBDCpzp){lVMVBdRknX = true;}
      else if(ftFJBDCpzp == IyBUcLJmMo){SoXlkrSkKw = true;}
      if(GENjpYyooS == qfBqkrgkYK){ofYmqRNEPE = true;}
      else if(qfBqkrgkYK == GENjpYyooS){KDnKKDDhlj = true;}
      if(lNTcKixuRl == OABEyNaphM){OqwuAPzIDP = true;}
      else if(OABEyNaphM == lNTcKixuRl){NJPJPkdlHe = true;}
      if(ZTsgNkqQVj == DTrEmOOWhy){ERKYlZycBs = true;}
      else if(DTrEmOOWhy == ZTsgNkqQVj){DBLhqlDSOt = true;}
      if(jbKVGqacOi == DiLoaZRPqd){QWHbSonYDE = true;}
      else if(DiLoaZRPqd == jbKVGqacOi){PYCnfxswFK = true;}
      if(kUthBudXJs == oULuDerBKm){cVHxntYQVk = true;}
      if(NNUZPmLgWF == cLHmmWnwDV){dIgYSXVzAQ = true;}
      if(ggSEhKDyWS == cKDZGfoLcX){SkCWmrjUcK = true;}
      while(oULuDerBKm == kUthBudXJs){EHwXgJZNWz = true;}
      while(cLHmmWnwDV == cLHmmWnwDV){OgcerJqGTX = true;}
      while(cKDZGfoLcX == cKDZGfoLcX){AkSrUoGacR = true;}
      if(uKyDWhIwAI == true){uKyDWhIwAI = false;}
      if(VNLuVqaXBD == true){VNLuVqaXBD = false;}
      if(lVMVBdRknX == true){lVMVBdRknX = false;}
      if(ofYmqRNEPE == true){ofYmqRNEPE = false;}
      if(OqwuAPzIDP == true){OqwuAPzIDP = false;}
      if(ERKYlZycBs == true){ERKYlZycBs = false;}
      if(QWHbSonYDE == true){QWHbSonYDE = false;}
      if(cVHxntYQVk == true){cVHxntYQVk = false;}
      if(dIgYSXVzAQ == true){dIgYSXVzAQ = false;}
      if(SkCWmrjUcK == true){SkCWmrjUcK = false;}
      if(aaFzliJMjq == true){aaFzliJMjq = false;}
      if(BgGQOIoiIt == true){BgGQOIoiIt = false;}
      if(SoXlkrSkKw == true){SoXlkrSkKw = false;}
      if(KDnKKDDhlj == true){KDnKKDDhlj = false;}
      if(NJPJPkdlHe == true){NJPJPkdlHe = false;}
      if(DBLhqlDSOt == true){DBLhqlDSOt = false;}
      if(PYCnfxswFK == true){PYCnfxswFK = false;}
      if(EHwXgJZNWz == true){EHwXgJZNWz = false;}
      if(OgcerJqGTX == true){OgcerJqGTX = false;}
      if(AkSrUoGacR == true){AkSrUoGacR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SECRNQBYZM
{ 
  void XuGILqqIgB()
  { 
      bool YRnbdkjDeb = false;
      bool VNQwfVdmpd = false;
      bool JVXIsMZcGa = false;
      bool ejYfxxrXVF = false;
      bool JiZYmXDesW = false;
      bool ziyFdDtfhQ = false;
      bool KGwExkokyh = false;
      bool dFRkUauzUV = false;
      bool JtjjbukSBs = false;
      bool DMpFtClUaB = false;
      bool iRfKssRNkD = false;
      bool HuKMGQWMcC = false;
      bool AVjFeQPMqR = false;
      bool naXSmqOYph = false;
      bool cXgxkHBdyd = false;
      bool eZqYBMhafb = false;
      bool cFWTPgXqYO = false;
      bool CxVuYbolTW = false;
      bool PlNNlNizRZ = false;
      bool JmsOFXBNgE = false;
      string DVMWkzkZbb;
      string iRaeueHZnS;
      string rZZiGEQHfr;
      string aNtBBJZrZf;
      string JDisMMLUZH;
      string FjFQqcucPf;
      string ictiAUWYdk;
      string EPAIInpgWs;
      string swhXmpIcJX;
      string OxbsxgIArq;
      string olpnDpjxIC;
      string mOFVlltWwJ;
      string MtPFVHmGKb;
      string fpnfEHFsUw;
      string GKUGkzqFGK;
      string llDieuVkSu;
      string DdmfWwaYRe;
      string gBCADCYITV;
      string PgzzpsmFBJ;
      string kTaYscWojn;
      if(DVMWkzkZbb == olpnDpjxIC){YRnbdkjDeb = true;}
      else if(olpnDpjxIC == DVMWkzkZbb){iRfKssRNkD = true;}
      if(iRaeueHZnS == mOFVlltWwJ){VNQwfVdmpd = true;}
      else if(mOFVlltWwJ == iRaeueHZnS){HuKMGQWMcC = true;}
      if(rZZiGEQHfr == MtPFVHmGKb){JVXIsMZcGa = true;}
      else if(MtPFVHmGKb == rZZiGEQHfr){AVjFeQPMqR = true;}
      if(aNtBBJZrZf == fpnfEHFsUw){ejYfxxrXVF = true;}
      else if(fpnfEHFsUw == aNtBBJZrZf){naXSmqOYph = true;}
      if(JDisMMLUZH == GKUGkzqFGK){JiZYmXDesW = true;}
      else if(GKUGkzqFGK == JDisMMLUZH){cXgxkHBdyd = true;}
      if(FjFQqcucPf == llDieuVkSu){ziyFdDtfhQ = true;}
      else if(llDieuVkSu == FjFQqcucPf){eZqYBMhafb = true;}
      if(ictiAUWYdk == DdmfWwaYRe){KGwExkokyh = true;}
      else if(DdmfWwaYRe == ictiAUWYdk){cFWTPgXqYO = true;}
      if(EPAIInpgWs == gBCADCYITV){dFRkUauzUV = true;}
      if(swhXmpIcJX == PgzzpsmFBJ){JtjjbukSBs = true;}
      if(OxbsxgIArq == kTaYscWojn){DMpFtClUaB = true;}
      while(gBCADCYITV == EPAIInpgWs){CxVuYbolTW = true;}
      while(PgzzpsmFBJ == PgzzpsmFBJ){PlNNlNizRZ = true;}
      while(kTaYscWojn == kTaYscWojn){JmsOFXBNgE = true;}
      if(YRnbdkjDeb == true){YRnbdkjDeb = false;}
      if(VNQwfVdmpd == true){VNQwfVdmpd = false;}
      if(JVXIsMZcGa == true){JVXIsMZcGa = false;}
      if(ejYfxxrXVF == true){ejYfxxrXVF = false;}
      if(JiZYmXDesW == true){JiZYmXDesW = false;}
      if(ziyFdDtfhQ == true){ziyFdDtfhQ = false;}
      if(KGwExkokyh == true){KGwExkokyh = false;}
      if(dFRkUauzUV == true){dFRkUauzUV = false;}
      if(JtjjbukSBs == true){JtjjbukSBs = false;}
      if(DMpFtClUaB == true){DMpFtClUaB = false;}
      if(iRfKssRNkD == true){iRfKssRNkD = false;}
      if(HuKMGQWMcC == true){HuKMGQWMcC = false;}
      if(AVjFeQPMqR == true){AVjFeQPMqR = false;}
      if(naXSmqOYph == true){naXSmqOYph = false;}
      if(cXgxkHBdyd == true){cXgxkHBdyd = false;}
      if(eZqYBMhafb == true){eZqYBMhafb = false;}
      if(cFWTPgXqYO == true){cFWTPgXqYO = false;}
      if(CxVuYbolTW == true){CxVuYbolTW = false;}
      if(PlNNlNizRZ == true){PlNNlNizRZ = false;}
      if(JmsOFXBNgE == true){JmsOFXBNgE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCABLJBLPI
{ 
  void FqQJHcHaGj()
  { 
      bool lRlQKWMDjn = false;
      bool CyeRXgsUZI = false;
      bool NUcIyiTYnp = false;
      bool LolTXMmFap = false;
      bool LikYWPoPCy = false;
      bool KWRunQncRa = false;
      bool DnOscNMKtK = false;
      bool smtjwdiEli = false;
      bool tDWoenWqfG = false;
      bool YKnzmXTqwJ = false;
      bool DdUrFXchyJ = false;
      bool hjqifzRZNn = false;
      bool pUdnliztxY = false;
      bool JrIcePieiH = false;
      bool LosVYoSESm = false;
      bool GtcHShzfFW = false;
      bool XhkYAoaODQ = false;
      bool QlpGcBbIPw = false;
      bool PtaJRPOAJx = false;
      bool QCYMicDTVi = false;
      string IgBbuQTwrH;
      string wUbsGyXZhm;
      string HKuCZMBlCx;
      string DpBwJDFPcz;
      string RhXzARtIPj;
      string JOmurxkyBh;
      string PgttEFTejC;
      string sIwhVYmuBI;
      string RrWSnnDFEL;
      string RGNtjjncuu;
      string yOYMpBSEZS;
      string JpxsPWKbGQ;
      string CNaXkmtByl;
      string kJAGKCTJbl;
      string UyfkCbIUeN;
      string YMWerjnAbC;
      string GQGmhAoqiN;
      string CBzTuDgoVJ;
      string eZWkNYlUNZ;
      string OThZfErrDB;
      if(IgBbuQTwrH == yOYMpBSEZS){lRlQKWMDjn = true;}
      else if(yOYMpBSEZS == IgBbuQTwrH){DdUrFXchyJ = true;}
      if(wUbsGyXZhm == JpxsPWKbGQ){CyeRXgsUZI = true;}
      else if(JpxsPWKbGQ == wUbsGyXZhm){hjqifzRZNn = true;}
      if(HKuCZMBlCx == CNaXkmtByl){NUcIyiTYnp = true;}
      else if(CNaXkmtByl == HKuCZMBlCx){pUdnliztxY = true;}
      if(DpBwJDFPcz == kJAGKCTJbl){LolTXMmFap = true;}
      else if(kJAGKCTJbl == DpBwJDFPcz){JrIcePieiH = true;}
      if(RhXzARtIPj == UyfkCbIUeN){LikYWPoPCy = true;}
      else if(UyfkCbIUeN == RhXzARtIPj){LosVYoSESm = true;}
      if(JOmurxkyBh == YMWerjnAbC){KWRunQncRa = true;}
      else if(YMWerjnAbC == JOmurxkyBh){GtcHShzfFW = true;}
      if(PgttEFTejC == GQGmhAoqiN){DnOscNMKtK = true;}
      else if(GQGmhAoqiN == PgttEFTejC){XhkYAoaODQ = true;}
      if(sIwhVYmuBI == CBzTuDgoVJ){smtjwdiEli = true;}
      if(RrWSnnDFEL == eZWkNYlUNZ){tDWoenWqfG = true;}
      if(RGNtjjncuu == OThZfErrDB){YKnzmXTqwJ = true;}
      while(CBzTuDgoVJ == sIwhVYmuBI){QlpGcBbIPw = true;}
      while(eZWkNYlUNZ == eZWkNYlUNZ){PtaJRPOAJx = true;}
      while(OThZfErrDB == OThZfErrDB){QCYMicDTVi = true;}
      if(lRlQKWMDjn == true){lRlQKWMDjn = false;}
      if(CyeRXgsUZI == true){CyeRXgsUZI = false;}
      if(NUcIyiTYnp == true){NUcIyiTYnp = false;}
      if(LolTXMmFap == true){LolTXMmFap = false;}
      if(LikYWPoPCy == true){LikYWPoPCy = false;}
      if(KWRunQncRa == true){KWRunQncRa = false;}
      if(DnOscNMKtK == true){DnOscNMKtK = false;}
      if(smtjwdiEli == true){smtjwdiEli = false;}
      if(tDWoenWqfG == true){tDWoenWqfG = false;}
      if(YKnzmXTqwJ == true){YKnzmXTqwJ = false;}
      if(DdUrFXchyJ == true){DdUrFXchyJ = false;}
      if(hjqifzRZNn == true){hjqifzRZNn = false;}
      if(pUdnliztxY == true){pUdnliztxY = false;}
      if(JrIcePieiH == true){JrIcePieiH = false;}
      if(LosVYoSESm == true){LosVYoSESm = false;}
      if(GtcHShzfFW == true){GtcHShzfFW = false;}
      if(XhkYAoaODQ == true){XhkYAoaODQ = false;}
      if(QlpGcBbIPw == true){QlpGcBbIPw = false;}
      if(PtaJRPOAJx == true){PtaJRPOAJx = false;}
      if(QCYMicDTVi == true){QCYMicDTVi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPCIRUDEKY
{ 
  void hyFEyIqSmI()
  { 
      bool SHcqCiSCzh = false;
      bool WneYywECol = false;
      bool rkuxBkpZfp = false;
      bool YkgrPkaXNZ = false;
      bool AaWfuOkyRD = false;
      bool JlPKrgMfpQ = false;
      bool rrWJIlHlJM = false;
      bool VgoOlROOBl = false;
      bool AqHbflVVzi = false;
      bool YuhwhHDMXJ = false;
      bool HyoFhcxAYa = false;
      bool RydDQAkucV = false;
      bool QklamZzrgd = false;
      bool NBpreBBBsC = false;
      bool oUxYQZQdfg = false;
      bool WIjBsVMORH = false;
      bool dETtNQHlYO = false;
      bool yiBagunNJM = false;
      bool JVMAGERozI = false;
      bool omjkYkBCLA = false;
      string kEQJpOQSMb;
      string lHZXQnxFHi;
      string AZHOhqcYKf;
      string aXKFzDoNWN;
      string jPxqiATOcB;
      string gNeDTKxBay;
      string lqHfAOxTXN;
      string yiitzjcQfg;
      string WNuJyNrGln;
      string FnlXarHQqT;
      string DAqPCxekEi;
      string hfVsbXuygm;
      string WqgiHKwLSG;
      string cMZLdWWfHB;
      string hHCDGYRrwD;
      string xJiDxLSHHq;
      string ATRxFVGJPE;
      string AOpfEOodch;
      string sEOPITcVOR;
      string DPXQAOoExj;
      if(kEQJpOQSMb == DAqPCxekEi){SHcqCiSCzh = true;}
      else if(DAqPCxekEi == kEQJpOQSMb){HyoFhcxAYa = true;}
      if(lHZXQnxFHi == hfVsbXuygm){WneYywECol = true;}
      else if(hfVsbXuygm == lHZXQnxFHi){RydDQAkucV = true;}
      if(AZHOhqcYKf == WqgiHKwLSG){rkuxBkpZfp = true;}
      else if(WqgiHKwLSG == AZHOhqcYKf){QklamZzrgd = true;}
      if(aXKFzDoNWN == cMZLdWWfHB){YkgrPkaXNZ = true;}
      else if(cMZLdWWfHB == aXKFzDoNWN){NBpreBBBsC = true;}
      if(jPxqiATOcB == hHCDGYRrwD){AaWfuOkyRD = true;}
      else if(hHCDGYRrwD == jPxqiATOcB){oUxYQZQdfg = true;}
      if(gNeDTKxBay == xJiDxLSHHq){JlPKrgMfpQ = true;}
      else if(xJiDxLSHHq == gNeDTKxBay){WIjBsVMORH = true;}
      if(lqHfAOxTXN == ATRxFVGJPE){rrWJIlHlJM = true;}
      else if(ATRxFVGJPE == lqHfAOxTXN){dETtNQHlYO = true;}
      if(yiitzjcQfg == AOpfEOodch){VgoOlROOBl = true;}
      if(WNuJyNrGln == sEOPITcVOR){AqHbflVVzi = true;}
      if(FnlXarHQqT == DPXQAOoExj){YuhwhHDMXJ = true;}
      while(AOpfEOodch == yiitzjcQfg){yiBagunNJM = true;}
      while(sEOPITcVOR == sEOPITcVOR){JVMAGERozI = true;}
      while(DPXQAOoExj == DPXQAOoExj){omjkYkBCLA = true;}
      if(SHcqCiSCzh == true){SHcqCiSCzh = false;}
      if(WneYywECol == true){WneYywECol = false;}
      if(rkuxBkpZfp == true){rkuxBkpZfp = false;}
      if(YkgrPkaXNZ == true){YkgrPkaXNZ = false;}
      if(AaWfuOkyRD == true){AaWfuOkyRD = false;}
      if(JlPKrgMfpQ == true){JlPKrgMfpQ = false;}
      if(rrWJIlHlJM == true){rrWJIlHlJM = false;}
      if(VgoOlROOBl == true){VgoOlROOBl = false;}
      if(AqHbflVVzi == true){AqHbflVVzi = false;}
      if(YuhwhHDMXJ == true){YuhwhHDMXJ = false;}
      if(HyoFhcxAYa == true){HyoFhcxAYa = false;}
      if(RydDQAkucV == true){RydDQAkucV = false;}
      if(QklamZzrgd == true){QklamZzrgd = false;}
      if(NBpreBBBsC == true){NBpreBBBsC = false;}
      if(oUxYQZQdfg == true){oUxYQZQdfg = false;}
      if(WIjBsVMORH == true){WIjBsVMORH = false;}
      if(dETtNQHlYO == true){dETtNQHlYO = false;}
      if(yiBagunNJM == true){yiBagunNJM = false;}
      if(JVMAGERozI == true){JVMAGERozI = false;}
      if(omjkYkBCLA == true){omjkYkBCLA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PALJSCDIPA
{ 
  void lfYgzfooaQ()
  { 
      bool BasIwcBmsH = false;
      bool sLiXSPnFwt = false;
      bool NcEODLpaYu = false;
      bool OgLlfJAeEc = false;
      bool KMmRcbCMda = false;
      bool GMaBkYWeEk = false;
      bool laNxrMAwqI = false;
      bool OIASiAplkb = false;
      bool IdxyoBFKBH = false;
      bool mUaTqjzpYQ = false;
      bool aFUULyLHRj = false;
      bool ijtbbHcPHq = false;
      bool GpujVshgay = false;
      bool BzMUBCIblq = false;
      bool oxrQYCayqi = false;
      bool GihhJjKkzR = false;
      bool PegSiiWZaY = false;
      bool yBcQBIyeLS = false;
      bool RjpqrRReKQ = false;
      bool rXbUaKQYhp = false;
      string JrplwragTs;
      string yqefyjwTQH;
      string udHmkPPTSY;
      string rRbZHUzmfY;
      string bLLwbogqdb;
      string qErqdfjCBg;
      string bHNuAgOEYd;
      string kJnqejRLKu;
      string hYppgmZkwa;
      string jwkzwUxQwu;
      string abSzqhQALs;
      string OYrGyDRWOM;
      string GcIxsnYotJ;
      string lBPOUGGpzz;
      string WYYCLLEeAs;
      string DZBioxSUFC;
      string IbGCGMJdkq;
      string xaXOpgDGkh;
      string jsnAFMzfZW;
      string mkjwptSWuy;
      if(JrplwragTs == abSzqhQALs){BasIwcBmsH = true;}
      else if(abSzqhQALs == JrplwragTs){aFUULyLHRj = true;}
      if(yqefyjwTQH == OYrGyDRWOM){sLiXSPnFwt = true;}
      else if(OYrGyDRWOM == yqefyjwTQH){ijtbbHcPHq = true;}
      if(udHmkPPTSY == GcIxsnYotJ){NcEODLpaYu = true;}
      else if(GcIxsnYotJ == udHmkPPTSY){GpujVshgay = true;}
      if(rRbZHUzmfY == lBPOUGGpzz){OgLlfJAeEc = true;}
      else if(lBPOUGGpzz == rRbZHUzmfY){BzMUBCIblq = true;}
      if(bLLwbogqdb == WYYCLLEeAs){KMmRcbCMda = true;}
      else if(WYYCLLEeAs == bLLwbogqdb){oxrQYCayqi = true;}
      if(qErqdfjCBg == DZBioxSUFC){GMaBkYWeEk = true;}
      else if(DZBioxSUFC == qErqdfjCBg){GihhJjKkzR = true;}
      if(bHNuAgOEYd == IbGCGMJdkq){laNxrMAwqI = true;}
      else if(IbGCGMJdkq == bHNuAgOEYd){PegSiiWZaY = true;}
      if(kJnqejRLKu == xaXOpgDGkh){OIASiAplkb = true;}
      if(hYppgmZkwa == jsnAFMzfZW){IdxyoBFKBH = true;}
      if(jwkzwUxQwu == mkjwptSWuy){mUaTqjzpYQ = true;}
      while(xaXOpgDGkh == kJnqejRLKu){yBcQBIyeLS = true;}
      while(jsnAFMzfZW == jsnAFMzfZW){RjpqrRReKQ = true;}
      while(mkjwptSWuy == mkjwptSWuy){rXbUaKQYhp = true;}
      if(BasIwcBmsH == true){BasIwcBmsH = false;}
      if(sLiXSPnFwt == true){sLiXSPnFwt = false;}
      if(NcEODLpaYu == true){NcEODLpaYu = false;}
      if(OgLlfJAeEc == true){OgLlfJAeEc = false;}
      if(KMmRcbCMda == true){KMmRcbCMda = false;}
      if(GMaBkYWeEk == true){GMaBkYWeEk = false;}
      if(laNxrMAwqI == true){laNxrMAwqI = false;}
      if(OIASiAplkb == true){OIASiAplkb = false;}
      if(IdxyoBFKBH == true){IdxyoBFKBH = false;}
      if(mUaTqjzpYQ == true){mUaTqjzpYQ = false;}
      if(aFUULyLHRj == true){aFUULyLHRj = false;}
      if(ijtbbHcPHq == true){ijtbbHcPHq = false;}
      if(GpujVshgay == true){GpujVshgay = false;}
      if(BzMUBCIblq == true){BzMUBCIblq = false;}
      if(oxrQYCayqi == true){oxrQYCayqi = false;}
      if(GihhJjKkzR == true){GihhJjKkzR = false;}
      if(PegSiiWZaY == true){PegSiiWZaY = false;}
      if(yBcQBIyeLS == true){yBcQBIyeLS = false;}
      if(RjpqrRReKQ == true){RjpqrRReKQ = false;}
      if(rXbUaKQYhp == true){rXbUaKQYhp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RBMHVREIFC
{ 
  void bboZIpqJio()
  { 
      bool ZlZHFEQKyV = false;
      bool YjYHqfiObe = false;
      bool PuBGnkEFkT = false;
      bool gJVqKWALEB = false;
      bool isjtgDSEAz = false;
      bool QShLkdjTST = false;
      bool zLZdoPOgwT = false;
      bool fXKauVLHZk = false;
      bool SzElDOaKGf = false;
      bool lgrjBWTFFQ = false;
      bool okIfSrIHPO = false;
      bool ScshAAGnaa = false;
      bool oDZPhyfZZX = false;
      bool CFCJwgqYSL = false;
      bool FStqNJmKiA = false;
      bool QeeebkLrxT = false;
      bool MhhqMMajlT = false;
      bool IhVOUVJiCX = false;
      bool KVqYHWZXhL = false;
      bool VzayyXkDeA = false;
      string MgmlXjJrxr;
      string xoaVeiZaKW;
      string MzLKVtIyAm;
      string NDbbjFzNax;
      string DuoUBRdSJw;
      string fFeaLMVcPc;
      string bLrKetMylZ;
      string iLzNSRKpIE;
      string PooEGHXAQW;
      string jWyxUrCeoH;
      string FefiMUFRIt;
      string BeTLNlWnDW;
      string VLhOpMNCra;
      string OfABzkIFql;
      string CGrVVEDlji;
      string UNaSkswRsA;
      string HCYhfUdRMb;
      string cQwQUOTMrk;
      string IaSJFAEhPF;
      string nqMqeAhKpB;
      if(MgmlXjJrxr == FefiMUFRIt){ZlZHFEQKyV = true;}
      else if(FefiMUFRIt == MgmlXjJrxr){okIfSrIHPO = true;}
      if(xoaVeiZaKW == BeTLNlWnDW){YjYHqfiObe = true;}
      else if(BeTLNlWnDW == xoaVeiZaKW){ScshAAGnaa = true;}
      if(MzLKVtIyAm == VLhOpMNCra){PuBGnkEFkT = true;}
      else if(VLhOpMNCra == MzLKVtIyAm){oDZPhyfZZX = true;}
      if(NDbbjFzNax == OfABzkIFql){gJVqKWALEB = true;}
      else if(OfABzkIFql == NDbbjFzNax){CFCJwgqYSL = true;}
      if(DuoUBRdSJw == CGrVVEDlji){isjtgDSEAz = true;}
      else if(CGrVVEDlji == DuoUBRdSJw){FStqNJmKiA = true;}
      if(fFeaLMVcPc == UNaSkswRsA){QShLkdjTST = true;}
      else if(UNaSkswRsA == fFeaLMVcPc){QeeebkLrxT = true;}
      if(bLrKetMylZ == HCYhfUdRMb){zLZdoPOgwT = true;}
      else if(HCYhfUdRMb == bLrKetMylZ){MhhqMMajlT = true;}
      if(iLzNSRKpIE == cQwQUOTMrk){fXKauVLHZk = true;}
      if(PooEGHXAQW == IaSJFAEhPF){SzElDOaKGf = true;}
      if(jWyxUrCeoH == nqMqeAhKpB){lgrjBWTFFQ = true;}
      while(cQwQUOTMrk == iLzNSRKpIE){IhVOUVJiCX = true;}
      while(IaSJFAEhPF == IaSJFAEhPF){KVqYHWZXhL = true;}
      while(nqMqeAhKpB == nqMqeAhKpB){VzayyXkDeA = true;}
      if(ZlZHFEQKyV == true){ZlZHFEQKyV = false;}
      if(YjYHqfiObe == true){YjYHqfiObe = false;}
      if(PuBGnkEFkT == true){PuBGnkEFkT = false;}
      if(gJVqKWALEB == true){gJVqKWALEB = false;}
      if(isjtgDSEAz == true){isjtgDSEAz = false;}
      if(QShLkdjTST == true){QShLkdjTST = false;}
      if(zLZdoPOgwT == true){zLZdoPOgwT = false;}
      if(fXKauVLHZk == true){fXKauVLHZk = false;}
      if(SzElDOaKGf == true){SzElDOaKGf = false;}
      if(lgrjBWTFFQ == true){lgrjBWTFFQ = false;}
      if(okIfSrIHPO == true){okIfSrIHPO = false;}
      if(ScshAAGnaa == true){ScshAAGnaa = false;}
      if(oDZPhyfZZX == true){oDZPhyfZZX = false;}
      if(CFCJwgqYSL == true){CFCJwgqYSL = false;}
      if(FStqNJmKiA == true){FStqNJmKiA = false;}
      if(QeeebkLrxT == true){QeeebkLrxT = false;}
      if(MhhqMMajlT == true){MhhqMMajlT = false;}
      if(IhVOUVJiCX == true){IhVOUVJiCX = false;}
      if(KVqYHWZXhL == true){KVqYHWZXhL = false;}
      if(VzayyXkDeA == true){VzayyXkDeA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEZZRLGIKB
{ 
  void juAMKQPksp()
  { 
      bool wfMmMKJLzP = false;
      bool qszxjytSHw = false;
      bool MWGZGMMOoz = false;
      bool qZtjIhxlqh = false;
      bool mQSeqpxhsp = false;
      bool oJXNPYZmfA = false;
      bool ytVAYQyOnC = false;
      bool BIbZIwDaiQ = false;
      bool OeUzJgCgUj = false;
      bool IJFpjrtSFa = false;
      bool qhtqoghyET = false;
      bool VyEPkSZVpr = false;
      bool NRtDtqCkoP = false;
      bool BkVHYfkdJc = false;
      bool zDbBNJEoEQ = false;
      bool SYcNMZnpwx = false;
      bool dwJoSkcwpF = false;
      bool huLMrJospj = false;
      bool mMgXwbHIuz = false;
      bool rtgMzDtlic = false;
      string uAOUsDgZUN;
      string dOLGtmxLZx;
      string pItARmkheJ;
      string CNxKIdbKGI;
      string aSacSBDmIG;
      string ZbPTPmFNCG;
      string RzuKLQQAyP;
      string KlERWWgQgP;
      string iyZYjZxdtU;
      string YNHApbXQRC;
      string kCorumXywr;
      string FnfmWTYVak;
      string SmFcpweDau;
      string zQzeefJgcw;
      string CzgCPkhUdW;
      string CCogixwLCz;
      string ITWAsnoBHp;
      string JqrdhTGDMF;
      string OJZDsxbRuh;
      string ixednibfJb;
      if(uAOUsDgZUN == kCorumXywr){wfMmMKJLzP = true;}
      else if(kCorumXywr == uAOUsDgZUN){qhtqoghyET = true;}
      if(dOLGtmxLZx == FnfmWTYVak){qszxjytSHw = true;}
      else if(FnfmWTYVak == dOLGtmxLZx){VyEPkSZVpr = true;}
      if(pItARmkheJ == SmFcpweDau){MWGZGMMOoz = true;}
      else if(SmFcpweDau == pItARmkheJ){NRtDtqCkoP = true;}
      if(CNxKIdbKGI == zQzeefJgcw){qZtjIhxlqh = true;}
      else if(zQzeefJgcw == CNxKIdbKGI){BkVHYfkdJc = true;}
      if(aSacSBDmIG == CzgCPkhUdW){mQSeqpxhsp = true;}
      else if(CzgCPkhUdW == aSacSBDmIG){zDbBNJEoEQ = true;}
      if(ZbPTPmFNCG == CCogixwLCz){oJXNPYZmfA = true;}
      else if(CCogixwLCz == ZbPTPmFNCG){SYcNMZnpwx = true;}
      if(RzuKLQQAyP == ITWAsnoBHp){ytVAYQyOnC = true;}
      else if(ITWAsnoBHp == RzuKLQQAyP){dwJoSkcwpF = true;}
      if(KlERWWgQgP == JqrdhTGDMF){BIbZIwDaiQ = true;}
      if(iyZYjZxdtU == OJZDsxbRuh){OeUzJgCgUj = true;}
      if(YNHApbXQRC == ixednibfJb){IJFpjrtSFa = true;}
      while(JqrdhTGDMF == KlERWWgQgP){huLMrJospj = true;}
      while(OJZDsxbRuh == OJZDsxbRuh){mMgXwbHIuz = true;}
      while(ixednibfJb == ixednibfJb){rtgMzDtlic = true;}
      if(wfMmMKJLzP == true){wfMmMKJLzP = false;}
      if(qszxjytSHw == true){qszxjytSHw = false;}
      if(MWGZGMMOoz == true){MWGZGMMOoz = false;}
      if(qZtjIhxlqh == true){qZtjIhxlqh = false;}
      if(mQSeqpxhsp == true){mQSeqpxhsp = false;}
      if(oJXNPYZmfA == true){oJXNPYZmfA = false;}
      if(ytVAYQyOnC == true){ytVAYQyOnC = false;}
      if(BIbZIwDaiQ == true){BIbZIwDaiQ = false;}
      if(OeUzJgCgUj == true){OeUzJgCgUj = false;}
      if(IJFpjrtSFa == true){IJFpjrtSFa = false;}
      if(qhtqoghyET == true){qhtqoghyET = false;}
      if(VyEPkSZVpr == true){VyEPkSZVpr = false;}
      if(NRtDtqCkoP == true){NRtDtqCkoP = false;}
      if(BkVHYfkdJc == true){BkVHYfkdJc = false;}
      if(zDbBNJEoEQ == true){zDbBNJEoEQ = false;}
      if(SYcNMZnpwx == true){SYcNMZnpwx = false;}
      if(dwJoSkcwpF == true){dwJoSkcwpF = false;}
      if(huLMrJospj == true){huLMrJospj = false;}
      if(mMgXwbHIuz == true){mMgXwbHIuz = false;}
      if(rtgMzDtlic == true){rtgMzDtlic = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JRPIRMNULB
{ 
  void ypzIAxsZqR()
  { 
      bool lJXKrZIZcK = false;
      bool apnWQacKau = false;
      bool qwjBphAlSw = false;
      bool XGDHsetxTw = false;
      bool WaVhQrAqTQ = false;
      bool bONQMpZWTJ = false;
      bool ZWHfmTmgdk = false;
      bool ffpdXPZCjy = false;
      bool gIRCTJrltC = false;
      bool FWcJWATptw = false;
      bool ETNijwXirw = false;
      bool PWmVcQEFMd = false;
      bool bAmaeJDfHX = false;
      bool wjHmsNtiRW = false;
      bool kItxlijGgF = false;
      bool uOdQUEfmEa = false;
      bool srbTAfOAbP = false;
      bool WVmosSGpnu = false;
      bool ZwzBchGqRo = false;
      bool gHeqdrgZwG = false;
      string sIHjoEYbHC;
      string iPqyycIxxF;
      string bBjhHfpOsy;
      string oyiOQenAGq;
      string bZmjjmjqiW;
      string kUElnqYZbI;
      string NJiIMkfchT;
      string oIpFcCOAxU;
      string uzfWNUswZY;
      string GNYxdSqdWy;
      string GHJPgcdyJl;
      string cYbHNNdLtr;
      string qiCINajrbK;
      string KjczOnpPoj;
      string pummwhlQjP;
      string nejdGWFACF;
      string skWyarucrY;
      string XNVJBwwOLe;
      string oSILWfAyrq;
      string hoNjqFYoLE;
      if(sIHjoEYbHC == GHJPgcdyJl){lJXKrZIZcK = true;}
      else if(GHJPgcdyJl == sIHjoEYbHC){ETNijwXirw = true;}
      if(iPqyycIxxF == cYbHNNdLtr){apnWQacKau = true;}
      else if(cYbHNNdLtr == iPqyycIxxF){PWmVcQEFMd = true;}
      if(bBjhHfpOsy == qiCINajrbK){qwjBphAlSw = true;}
      else if(qiCINajrbK == bBjhHfpOsy){bAmaeJDfHX = true;}
      if(oyiOQenAGq == KjczOnpPoj){XGDHsetxTw = true;}
      else if(KjczOnpPoj == oyiOQenAGq){wjHmsNtiRW = true;}
      if(bZmjjmjqiW == pummwhlQjP){WaVhQrAqTQ = true;}
      else if(pummwhlQjP == bZmjjmjqiW){kItxlijGgF = true;}
      if(kUElnqYZbI == nejdGWFACF){bONQMpZWTJ = true;}
      else if(nejdGWFACF == kUElnqYZbI){uOdQUEfmEa = true;}
      if(NJiIMkfchT == skWyarucrY){ZWHfmTmgdk = true;}
      else if(skWyarucrY == NJiIMkfchT){srbTAfOAbP = true;}
      if(oIpFcCOAxU == XNVJBwwOLe){ffpdXPZCjy = true;}
      if(uzfWNUswZY == oSILWfAyrq){gIRCTJrltC = true;}
      if(GNYxdSqdWy == hoNjqFYoLE){FWcJWATptw = true;}
      while(XNVJBwwOLe == oIpFcCOAxU){WVmosSGpnu = true;}
      while(oSILWfAyrq == oSILWfAyrq){ZwzBchGqRo = true;}
      while(hoNjqFYoLE == hoNjqFYoLE){gHeqdrgZwG = true;}
      if(lJXKrZIZcK == true){lJXKrZIZcK = false;}
      if(apnWQacKau == true){apnWQacKau = false;}
      if(qwjBphAlSw == true){qwjBphAlSw = false;}
      if(XGDHsetxTw == true){XGDHsetxTw = false;}
      if(WaVhQrAqTQ == true){WaVhQrAqTQ = false;}
      if(bONQMpZWTJ == true){bONQMpZWTJ = false;}
      if(ZWHfmTmgdk == true){ZWHfmTmgdk = false;}
      if(ffpdXPZCjy == true){ffpdXPZCjy = false;}
      if(gIRCTJrltC == true){gIRCTJrltC = false;}
      if(FWcJWATptw == true){FWcJWATptw = false;}
      if(ETNijwXirw == true){ETNijwXirw = false;}
      if(PWmVcQEFMd == true){PWmVcQEFMd = false;}
      if(bAmaeJDfHX == true){bAmaeJDfHX = false;}
      if(wjHmsNtiRW == true){wjHmsNtiRW = false;}
      if(kItxlijGgF == true){kItxlijGgF = false;}
      if(uOdQUEfmEa == true){uOdQUEfmEa = false;}
      if(srbTAfOAbP == true){srbTAfOAbP = false;}
      if(WVmosSGpnu == true){WVmosSGpnu = false;}
      if(ZwzBchGqRo == true){ZwzBchGqRo = false;}
      if(gHeqdrgZwG == true){gHeqdrgZwG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROSNIHIDVX
{ 
  void uaJXCfgeHB()
  { 
      bool DKYDkhVOTN = false;
      bool BYqSOxjIuf = false;
      bool gmOKxUDOVV = false;
      bool PWtaCVGjax = false;
      bool SlFWZNGdeY = false;
      bool REafBQuNGQ = false;
      bool eGsxxeeQPr = false;
      bool pAhxNthqki = false;
      bool NYixDLwNYl = false;
      bool asdJSMsHZt = false;
      bool ipOmhRVcSH = false;
      bool iEcWCFWusl = false;
      bool iQqdRxWXeA = false;
      bool BZQpAWKwOl = false;
      bool oStRDVPHHM = false;
      bool oxOnKRzjUj = false;
      bool uyxSFImlVf = false;
      bool uZfGwPWYZw = false;
      bool hOQSKDLceh = false;
      bool WZbeqqVbMt = false;
      string QUKTJlQQQS;
      string XHYlwMsuMJ;
      string JTfHHTnbnD;
      string qtlMEhlgeW;
      string rIMUeDgKKL;
      string hPaDoxnCMo;
      string yncNadVLhO;
      string ZMQpQAHKcD;
      string mdRbVaShWG;
      string sjUoYEfzsB;
      string hUculVzklo;
      string pcZICUWArA;
      string KmoaVpraQM;
      string TIRaVSAVpz;
      string ahuhQPJLmE;
      string hfGsptfBYu;
      string dXUZUhLzlj;
      string TAJrYcrGJG;
      string ffmLenBYjb;
      string lyxtVCNVMi;
      if(QUKTJlQQQS == hUculVzklo){DKYDkhVOTN = true;}
      else if(hUculVzklo == QUKTJlQQQS){ipOmhRVcSH = true;}
      if(XHYlwMsuMJ == pcZICUWArA){BYqSOxjIuf = true;}
      else if(pcZICUWArA == XHYlwMsuMJ){iEcWCFWusl = true;}
      if(JTfHHTnbnD == KmoaVpraQM){gmOKxUDOVV = true;}
      else if(KmoaVpraQM == JTfHHTnbnD){iQqdRxWXeA = true;}
      if(qtlMEhlgeW == TIRaVSAVpz){PWtaCVGjax = true;}
      else if(TIRaVSAVpz == qtlMEhlgeW){BZQpAWKwOl = true;}
      if(rIMUeDgKKL == ahuhQPJLmE){SlFWZNGdeY = true;}
      else if(ahuhQPJLmE == rIMUeDgKKL){oStRDVPHHM = true;}
      if(hPaDoxnCMo == hfGsptfBYu){REafBQuNGQ = true;}
      else if(hfGsptfBYu == hPaDoxnCMo){oxOnKRzjUj = true;}
      if(yncNadVLhO == dXUZUhLzlj){eGsxxeeQPr = true;}
      else if(dXUZUhLzlj == yncNadVLhO){uyxSFImlVf = true;}
      if(ZMQpQAHKcD == TAJrYcrGJG){pAhxNthqki = true;}
      if(mdRbVaShWG == ffmLenBYjb){NYixDLwNYl = true;}
      if(sjUoYEfzsB == lyxtVCNVMi){asdJSMsHZt = true;}
      while(TAJrYcrGJG == ZMQpQAHKcD){uZfGwPWYZw = true;}
      while(ffmLenBYjb == ffmLenBYjb){hOQSKDLceh = true;}
      while(lyxtVCNVMi == lyxtVCNVMi){WZbeqqVbMt = true;}
      if(DKYDkhVOTN == true){DKYDkhVOTN = false;}
      if(BYqSOxjIuf == true){BYqSOxjIuf = false;}
      if(gmOKxUDOVV == true){gmOKxUDOVV = false;}
      if(PWtaCVGjax == true){PWtaCVGjax = false;}
      if(SlFWZNGdeY == true){SlFWZNGdeY = false;}
      if(REafBQuNGQ == true){REafBQuNGQ = false;}
      if(eGsxxeeQPr == true){eGsxxeeQPr = false;}
      if(pAhxNthqki == true){pAhxNthqki = false;}
      if(NYixDLwNYl == true){NYixDLwNYl = false;}
      if(asdJSMsHZt == true){asdJSMsHZt = false;}
      if(ipOmhRVcSH == true){ipOmhRVcSH = false;}
      if(iEcWCFWusl == true){iEcWCFWusl = false;}
      if(iQqdRxWXeA == true){iQqdRxWXeA = false;}
      if(BZQpAWKwOl == true){BZQpAWKwOl = false;}
      if(oStRDVPHHM == true){oStRDVPHHM = false;}
      if(oxOnKRzjUj == true){oxOnKRzjUj = false;}
      if(uyxSFImlVf == true){uyxSFImlVf = false;}
      if(uZfGwPWYZw == true){uZfGwPWYZw = false;}
      if(hOQSKDLceh == true){hOQSKDLceh = false;}
      if(WZbeqqVbMt == true){WZbeqqVbMt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NRAOJFJCDZ
{ 
  void HtModmhcoA()
  { 
      bool JFnfXlCFyj = false;
      bool VCHrLxArtg = false;
      bool tbLBtlbsiC = false;
      bool LKJlXFtugp = false;
      bool UwuBDdHyGD = false;
      bool qebIOgslkk = false;
      bool JIWuXLsVTG = false;
      bool CEKDLyfKxQ = false;
      bool ecmeLgiBWp = false;
      bool MHKwfMYAcr = false;
      bool kkdAAlUXwQ = false;
      bool BinTGfUrjq = false;
      bool bqyctutOWz = false;
      bool YfgFeszmdZ = false;
      bool LLFGocSpoA = false;
      bool qgPkPsmAFF = false;
      bool qGAwrVCioM = false;
      bool ggNKfQlrnQ = false;
      bool bEYWHqPuok = false;
      bool GygYhFKINS = false;
      string SsbIzcdEmh;
      string zsNjquwMOy;
      string xfqzBIhqaL;
      string qyXgjpfbKo;
      string cthyXxcHmA;
      string zMBaumCcHq;
      string umcbqAVfzA;
      string PTCYVDxsaD;
      string fZDaLdxxlw;
      string nCUStoQFGW;
      string awHljeKbEq;
      string oIBELUjCPN;
      string DYtDMMzieg;
      string lrmEbiSQpg;
      string SUrtHeBQHY;
      string EOorSCCDZX;
      string fbxWExVwbb;
      string BSMitifzwg;
      string LiaFbXCtkZ;
      string gOqSAqWVoJ;
      if(SsbIzcdEmh == awHljeKbEq){JFnfXlCFyj = true;}
      else if(awHljeKbEq == SsbIzcdEmh){kkdAAlUXwQ = true;}
      if(zsNjquwMOy == oIBELUjCPN){VCHrLxArtg = true;}
      else if(oIBELUjCPN == zsNjquwMOy){BinTGfUrjq = true;}
      if(xfqzBIhqaL == DYtDMMzieg){tbLBtlbsiC = true;}
      else if(DYtDMMzieg == xfqzBIhqaL){bqyctutOWz = true;}
      if(qyXgjpfbKo == lrmEbiSQpg){LKJlXFtugp = true;}
      else if(lrmEbiSQpg == qyXgjpfbKo){YfgFeszmdZ = true;}
      if(cthyXxcHmA == SUrtHeBQHY){UwuBDdHyGD = true;}
      else if(SUrtHeBQHY == cthyXxcHmA){LLFGocSpoA = true;}
      if(zMBaumCcHq == EOorSCCDZX){qebIOgslkk = true;}
      else if(EOorSCCDZX == zMBaumCcHq){qgPkPsmAFF = true;}
      if(umcbqAVfzA == fbxWExVwbb){JIWuXLsVTG = true;}
      else if(fbxWExVwbb == umcbqAVfzA){qGAwrVCioM = true;}
      if(PTCYVDxsaD == BSMitifzwg){CEKDLyfKxQ = true;}
      if(fZDaLdxxlw == LiaFbXCtkZ){ecmeLgiBWp = true;}
      if(nCUStoQFGW == gOqSAqWVoJ){MHKwfMYAcr = true;}
      while(BSMitifzwg == PTCYVDxsaD){ggNKfQlrnQ = true;}
      while(LiaFbXCtkZ == LiaFbXCtkZ){bEYWHqPuok = true;}
      while(gOqSAqWVoJ == gOqSAqWVoJ){GygYhFKINS = true;}
      if(JFnfXlCFyj == true){JFnfXlCFyj = false;}
      if(VCHrLxArtg == true){VCHrLxArtg = false;}
      if(tbLBtlbsiC == true){tbLBtlbsiC = false;}
      if(LKJlXFtugp == true){LKJlXFtugp = false;}
      if(UwuBDdHyGD == true){UwuBDdHyGD = false;}
      if(qebIOgslkk == true){qebIOgslkk = false;}
      if(JIWuXLsVTG == true){JIWuXLsVTG = false;}
      if(CEKDLyfKxQ == true){CEKDLyfKxQ = false;}
      if(ecmeLgiBWp == true){ecmeLgiBWp = false;}
      if(MHKwfMYAcr == true){MHKwfMYAcr = false;}
      if(kkdAAlUXwQ == true){kkdAAlUXwQ = false;}
      if(BinTGfUrjq == true){BinTGfUrjq = false;}
      if(bqyctutOWz == true){bqyctutOWz = false;}
      if(YfgFeszmdZ == true){YfgFeszmdZ = false;}
      if(LLFGocSpoA == true){LLFGocSpoA = false;}
      if(qgPkPsmAFF == true){qgPkPsmAFF = false;}
      if(qGAwrVCioM == true){qGAwrVCioM = false;}
      if(ggNKfQlrnQ == true){ggNKfQlrnQ = false;}
      if(bEYWHqPuok == true){bEYWHqPuok = false;}
      if(GygYhFKINS == true){GygYhFKINS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQMUBTAUOG
{ 
  void IIDEEygpsb()
  { 
      bool MsdEXDOkHn = false;
      bool POeNCPqeYD = false;
      bool lmHqVxEOuy = false;
      bool ONWDasexDw = false;
      bool JlNQCgBLGi = false;
      bool jImpSYkmia = false;
      bool zzpJZBqbmJ = false;
      bool ktbctAZqnn = false;
      bool wrILOGZgjB = false;
      bool HqOcxJuEqB = false;
      bool pZYwypgKuS = false;
      bool ztzteGqdtT = false;
      bool bJqkCsfyfj = false;
      bool EVzmyVTLNY = false;
      bool YPlRCMrTxp = false;
      bool RRJXYfhmtE = false;
      bool JheLOctLuI = false;
      bool mfPVtLXZio = false;
      bool ALAoRlMbNS = false;
      bool ngQIOqjZCZ = false;
      string JiEBxVmfVT;
      string ggLcTanlRI;
      string cBpHWKnrcN;
      string mBZOgbOlAj;
      string kKDJUJQHEu;
      string WBTfFIsxem;
      string guDHffGxur;
      string LCkgXSxglM;
      string tgngqkgtJY;
      string hRGNCoHuco;
      string DSLLiTQlHm;
      string KMKSrAGVQu;
      string yMmWJtwWeh;
      string KBDwJaVbyW;
      string UulVNVHmVC;
      string hlehqpfnCo;
      string XsHYbIINJQ;
      string deXsZCaQIn;
      string lIBbAYWUFS;
      string ugZIybnMsF;
      if(JiEBxVmfVT == DSLLiTQlHm){MsdEXDOkHn = true;}
      else if(DSLLiTQlHm == JiEBxVmfVT){pZYwypgKuS = true;}
      if(ggLcTanlRI == KMKSrAGVQu){POeNCPqeYD = true;}
      else if(KMKSrAGVQu == ggLcTanlRI){ztzteGqdtT = true;}
      if(cBpHWKnrcN == yMmWJtwWeh){lmHqVxEOuy = true;}
      else if(yMmWJtwWeh == cBpHWKnrcN){bJqkCsfyfj = true;}
      if(mBZOgbOlAj == KBDwJaVbyW){ONWDasexDw = true;}
      else if(KBDwJaVbyW == mBZOgbOlAj){EVzmyVTLNY = true;}
      if(kKDJUJQHEu == UulVNVHmVC){JlNQCgBLGi = true;}
      else if(UulVNVHmVC == kKDJUJQHEu){YPlRCMrTxp = true;}
      if(WBTfFIsxem == hlehqpfnCo){jImpSYkmia = true;}
      else if(hlehqpfnCo == WBTfFIsxem){RRJXYfhmtE = true;}
      if(guDHffGxur == XsHYbIINJQ){zzpJZBqbmJ = true;}
      else if(XsHYbIINJQ == guDHffGxur){JheLOctLuI = true;}
      if(LCkgXSxglM == deXsZCaQIn){ktbctAZqnn = true;}
      if(tgngqkgtJY == lIBbAYWUFS){wrILOGZgjB = true;}
      if(hRGNCoHuco == ugZIybnMsF){HqOcxJuEqB = true;}
      while(deXsZCaQIn == LCkgXSxglM){mfPVtLXZio = true;}
      while(lIBbAYWUFS == lIBbAYWUFS){ALAoRlMbNS = true;}
      while(ugZIybnMsF == ugZIybnMsF){ngQIOqjZCZ = true;}
      if(MsdEXDOkHn == true){MsdEXDOkHn = false;}
      if(POeNCPqeYD == true){POeNCPqeYD = false;}
      if(lmHqVxEOuy == true){lmHqVxEOuy = false;}
      if(ONWDasexDw == true){ONWDasexDw = false;}
      if(JlNQCgBLGi == true){JlNQCgBLGi = false;}
      if(jImpSYkmia == true){jImpSYkmia = false;}
      if(zzpJZBqbmJ == true){zzpJZBqbmJ = false;}
      if(ktbctAZqnn == true){ktbctAZqnn = false;}
      if(wrILOGZgjB == true){wrILOGZgjB = false;}
      if(HqOcxJuEqB == true){HqOcxJuEqB = false;}
      if(pZYwypgKuS == true){pZYwypgKuS = false;}
      if(ztzteGqdtT == true){ztzteGqdtT = false;}
      if(bJqkCsfyfj == true){bJqkCsfyfj = false;}
      if(EVzmyVTLNY == true){EVzmyVTLNY = false;}
      if(YPlRCMrTxp == true){YPlRCMrTxp = false;}
      if(RRJXYfhmtE == true){RRJXYfhmtE = false;}
      if(JheLOctLuI == true){JheLOctLuI = false;}
      if(mfPVtLXZio == true){mfPVtLXZio = false;}
      if(ALAoRlMbNS == true){ALAoRlMbNS = false;}
      if(ngQIOqjZCZ == true){ngQIOqjZCZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVNOKUUBYY
{ 
  void KwiHPWAAVJ()
  { 
      bool YEHJykrjIs = false;
      bool XHDumOgrUm = false;
      bool zNHhQacLVM = false;
      bool yqkrVNmAII = false;
      bool dVVNnQAsnh = false;
      bool loHPsKxYrW = false;
      bool IgNwtgVLZY = false;
      bool bgiLJcqstz = false;
      bool ZjXnZIiVyL = false;
      bool POHlAxIZSG = false;
      bool uoTOGFGwGQ = false;
      bool SDerwYIZVl = false;
      bool yAMOJNYxLL = false;
      bool URamEkQJgU = false;
      bool CmPgrLiOob = false;
      bool nhDgIubFEs = false;
      bool gIjtwBcrnL = false;
      bool HzrBiLjeVx = false;
      bool dJIiXlNtdI = false;
      bool ILEnmsCVkq = false;
      string KwpqSgGDMd;
      string VfMPmUOEma;
      string pHhffpncMX;
      string crOkRtWNkw;
      string dpTgOVYVuo;
      string ISaJMDOKKb;
      string rdqoAcRaxr;
      string xASpwAnAQK;
      string RRgXOKQEYO;
      string fMDJEzydfk;
      string ExXCqHAkML;
      string PNsAJZwTZp;
      string LMBiMkxJlx;
      string BJUfFUsegH;
      string KfrMyRSCze;
      string CeDoYruopF;
      string JpzOJFsNuo;
      string fRlSffTnkt;
      string SuJGtWGeGM;
      string YEnaxTgcDr;
      if(KwpqSgGDMd == ExXCqHAkML){YEHJykrjIs = true;}
      else if(ExXCqHAkML == KwpqSgGDMd){uoTOGFGwGQ = true;}
      if(VfMPmUOEma == PNsAJZwTZp){XHDumOgrUm = true;}
      else if(PNsAJZwTZp == VfMPmUOEma){SDerwYIZVl = true;}
      if(pHhffpncMX == LMBiMkxJlx){zNHhQacLVM = true;}
      else if(LMBiMkxJlx == pHhffpncMX){yAMOJNYxLL = true;}
      if(crOkRtWNkw == BJUfFUsegH){yqkrVNmAII = true;}
      else if(BJUfFUsegH == crOkRtWNkw){URamEkQJgU = true;}
      if(dpTgOVYVuo == KfrMyRSCze){dVVNnQAsnh = true;}
      else if(KfrMyRSCze == dpTgOVYVuo){CmPgrLiOob = true;}
      if(ISaJMDOKKb == CeDoYruopF){loHPsKxYrW = true;}
      else if(CeDoYruopF == ISaJMDOKKb){nhDgIubFEs = true;}
      if(rdqoAcRaxr == JpzOJFsNuo){IgNwtgVLZY = true;}
      else if(JpzOJFsNuo == rdqoAcRaxr){gIjtwBcrnL = true;}
      if(xASpwAnAQK == fRlSffTnkt){bgiLJcqstz = true;}
      if(RRgXOKQEYO == SuJGtWGeGM){ZjXnZIiVyL = true;}
      if(fMDJEzydfk == YEnaxTgcDr){POHlAxIZSG = true;}
      while(fRlSffTnkt == xASpwAnAQK){HzrBiLjeVx = true;}
      while(SuJGtWGeGM == SuJGtWGeGM){dJIiXlNtdI = true;}
      while(YEnaxTgcDr == YEnaxTgcDr){ILEnmsCVkq = true;}
      if(YEHJykrjIs == true){YEHJykrjIs = false;}
      if(XHDumOgrUm == true){XHDumOgrUm = false;}
      if(zNHhQacLVM == true){zNHhQacLVM = false;}
      if(yqkrVNmAII == true){yqkrVNmAII = false;}
      if(dVVNnQAsnh == true){dVVNnQAsnh = false;}
      if(loHPsKxYrW == true){loHPsKxYrW = false;}
      if(IgNwtgVLZY == true){IgNwtgVLZY = false;}
      if(bgiLJcqstz == true){bgiLJcqstz = false;}
      if(ZjXnZIiVyL == true){ZjXnZIiVyL = false;}
      if(POHlAxIZSG == true){POHlAxIZSG = false;}
      if(uoTOGFGwGQ == true){uoTOGFGwGQ = false;}
      if(SDerwYIZVl == true){SDerwYIZVl = false;}
      if(yAMOJNYxLL == true){yAMOJNYxLL = false;}
      if(URamEkQJgU == true){URamEkQJgU = false;}
      if(CmPgrLiOob == true){CmPgrLiOob = false;}
      if(nhDgIubFEs == true){nhDgIubFEs = false;}
      if(gIjtwBcrnL == true){gIjtwBcrnL = false;}
      if(HzrBiLjeVx == true){HzrBiLjeVx = false;}
      if(dJIiXlNtdI == true){dJIiXlNtdI = false;}
      if(ILEnmsCVkq == true){ILEnmsCVkq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZGXAOFHTE
{ 
  void wNLqNmlxrS()
  { 
      bool kjrfHDXyRQ = false;
      bool AdFtZfHpXy = false;
      bool WargYjfClI = false;
      bool aRAKtePsTm = false;
      bool ngXhQPNQAo = false;
      bool RTKkwKrLGX = false;
      bool WVMJpiduzu = false;
      bool PNWjJpCJQI = false;
      bool VPCwpHGOOi = false;
      bool lEluQSTNrh = false;
      bool lSQEYDwaaG = false;
      bool IhtyBGSPSi = false;
      bool bOgPIKbbTq = false;
      bool VnRiWCyxWm = false;
      bool LfmHaEJnsJ = false;
      bool zEuJFXlAuO = false;
      bool bUGjjTQLbz = false;
      bool IVrfXwaYnE = false;
      bool AnhJqRsHdy = false;
      bool QyBILpYDXH = false;
      string rhnHSrRhTA;
      string tEuVauLwfE;
      string ouDcSqqsrC;
      string GxHxHkgzAV;
      string uimdLypAyu;
      string CyPJewdKnb;
      string AXoQswxxNo;
      string NMuJIGHYRU;
      string BquxAHhySL;
      string GVLYVXsWkP;
      string BslIgpDFAX;
      string nEsSaJcrQl;
      string NzeBhqBWmk;
      string NknBTHElPJ;
      string EbytWBcryM;
      string tAFyCBNkao;
      string ofROKDQrzS;
      string EqcGgkAjef;
      string OIYapMfozR;
      string sTKZUYKijT;
      if(rhnHSrRhTA == BslIgpDFAX){kjrfHDXyRQ = true;}
      else if(BslIgpDFAX == rhnHSrRhTA){lSQEYDwaaG = true;}
      if(tEuVauLwfE == nEsSaJcrQl){AdFtZfHpXy = true;}
      else if(nEsSaJcrQl == tEuVauLwfE){IhtyBGSPSi = true;}
      if(ouDcSqqsrC == NzeBhqBWmk){WargYjfClI = true;}
      else if(NzeBhqBWmk == ouDcSqqsrC){bOgPIKbbTq = true;}
      if(GxHxHkgzAV == NknBTHElPJ){aRAKtePsTm = true;}
      else if(NknBTHElPJ == GxHxHkgzAV){VnRiWCyxWm = true;}
      if(uimdLypAyu == EbytWBcryM){ngXhQPNQAo = true;}
      else if(EbytWBcryM == uimdLypAyu){LfmHaEJnsJ = true;}
      if(CyPJewdKnb == tAFyCBNkao){RTKkwKrLGX = true;}
      else if(tAFyCBNkao == CyPJewdKnb){zEuJFXlAuO = true;}
      if(AXoQswxxNo == ofROKDQrzS){WVMJpiduzu = true;}
      else if(ofROKDQrzS == AXoQswxxNo){bUGjjTQLbz = true;}
      if(NMuJIGHYRU == EqcGgkAjef){PNWjJpCJQI = true;}
      if(BquxAHhySL == OIYapMfozR){VPCwpHGOOi = true;}
      if(GVLYVXsWkP == sTKZUYKijT){lEluQSTNrh = true;}
      while(EqcGgkAjef == NMuJIGHYRU){IVrfXwaYnE = true;}
      while(OIYapMfozR == OIYapMfozR){AnhJqRsHdy = true;}
      while(sTKZUYKijT == sTKZUYKijT){QyBILpYDXH = true;}
      if(kjrfHDXyRQ == true){kjrfHDXyRQ = false;}
      if(AdFtZfHpXy == true){AdFtZfHpXy = false;}
      if(WargYjfClI == true){WargYjfClI = false;}
      if(aRAKtePsTm == true){aRAKtePsTm = false;}
      if(ngXhQPNQAo == true){ngXhQPNQAo = false;}
      if(RTKkwKrLGX == true){RTKkwKrLGX = false;}
      if(WVMJpiduzu == true){WVMJpiduzu = false;}
      if(PNWjJpCJQI == true){PNWjJpCJQI = false;}
      if(VPCwpHGOOi == true){VPCwpHGOOi = false;}
      if(lEluQSTNrh == true){lEluQSTNrh = false;}
      if(lSQEYDwaaG == true){lSQEYDwaaG = false;}
      if(IhtyBGSPSi == true){IhtyBGSPSi = false;}
      if(bOgPIKbbTq == true){bOgPIKbbTq = false;}
      if(VnRiWCyxWm == true){VnRiWCyxWm = false;}
      if(LfmHaEJnsJ == true){LfmHaEJnsJ = false;}
      if(zEuJFXlAuO == true){zEuJFXlAuO = false;}
      if(bUGjjTQLbz == true){bUGjjTQLbz = false;}
      if(IVrfXwaYnE == true){IVrfXwaYnE = false;}
      if(AnhJqRsHdy == true){AnhJqRsHdy = false;}
      if(QyBILpYDXH == true){QyBILpYDXH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTDNDNVQDX
{ 
  void sDIotBaZIm()
  { 
      bool YBIXQfYGcO = false;
      bool JEKLajWiJm = false;
      bool ysJIUpAwoG = false;
      bool arzUmxZUFx = false;
      bool HytWuEdsRi = false;
      bool rnjGEfrzCa = false;
      bool fbRVmREoYd = false;
      bool JBdMfAzmNP = false;
      bool MGeGOlHrQG = false;
      bool EZRdQefXid = false;
      bool znTnYpJXaE = false;
      bool gFlmNYxLHB = false;
      bool JMYSYijzuA = false;
      bool TaEjPXlpgX = false;
      bool bjRMYzneQr = false;
      bool hUQgTmPBOo = false;
      bool GKcZkGBBWp = false;
      bool lGdiZZtLsZ = false;
      bool uEiCRyJWPc = false;
      bool IjbqQRGqbS = false;
      string rJkJgAqiaM;
      string TWiqGBGGHr;
      string hpEFeoKEnX;
      string ZpUEgeSPbp;
      string HRMkSPgXBB;
      string OmoldCEedr;
      string pltDlcBeJb;
      string hpdRjQdTmP;
      string IlDlJmBhZe;
      string ZnkjzUWIyo;
      string OCNZTXIXBN;
      string YkrOiDiIsz;
      string bSFeBtFsRP;
      string tUUxAFXcSk;
      string dcfMGouWBw;
      string lOOyMuxiXZ;
      string SOFlSDPtNc;
      string eFoIVylrXM;
      string yirVcfFWkE;
      string IoFsSOXssC;
      if(rJkJgAqiaM == OCNZTXIXBN){YBIXQfYGcO = true;}
      else if(OCNZTXIXBN == rJkJgAqiaM){znTnYpJXaE = true;}
      if(TWiqGBGGHr == YkrOiDiIsz){JEKLajWiJm = true;}
      else if(YkrOiDiIsz == TWiqGBGGHr){gFlmNYxLHB = true;}
      if(hpEFeoKEnX == bSFeBtFsRP){ysJIUpAwoG = true;}
      else if(bSFeBtFsRP == hpEFeoKEnX){JMYSYijzuA = true;}
      if(ZpUEgeSPbp == tUUxAFXcSk){arzUmxZUFx = true;}
      else if(tUUxAFXcSk == ZpUEgeSPbp){TaEjPXlpgX = true;}
      if(HRMkSPgXBB == dcfMGouWBw){HytWuEdsRi = true;}
      else if(dcfMGouWBw == HRMkSPgXBB){bjRMYzneQr = true;}
      if(OmoldCEedr == lOOyMuxiXZ){rnjGEfrzCa = true;}
      else if(lOOyMuxiXZ == OmoldCEedr){hUQgTmPBOo = true;}
      if(pltDlcBeJb == SOFlSDPtNc){fbRVmREoYd = true;}
      else if(SOFlSDPtNc == pltDlcBeJb){GKcZkGBBWp = true;}
      if(hpdRjQdTmP == eFoIVylrXM){JBdMfAzmNP = true;}
      if(IlDlJmBhZe == yirVcfFWkE){MGeGOlHrQG = true;}
      if(ZnkjzUWIyo == IoFsSOXssC){EZRdQefXid = true;}
      while(eFoIVylrXM == hpdRjQdTmP){lGdiZZtLsZ = true;}
      while(yirVcfFWkE == yirVcfFWkE){uEiCRyJWPc = true;}
      while(IoFsSOXssC == IoFsSOXssC){IjbqQRGqbS = true;}
      if(YBIXQfYGcO == true){YBIXQfYGcO = false;}
      if(JEKLajWiJm == true){JEKLajWiJm = false;}
      if(ysJIUpAwoG == true){ysJIUpAwoG = false;}
      if(arzUmxZUFx == true){arzUmxZUFx = false;}
      if(HytWuEdsRi == true){HytWuEdsRi = false;}
      if(rnjGEfrzCa == true){rnjGEfrzCa = false;}
      if(fbRVmREoYd == true){fbRVmREoYd = false;}
      if(JBdMfAzmNP == true){JBdMfAzmNP = false;}
      if(MGeGOlHrQG == true){MGeGOlHrQG = false;}
      if(EZRdQefXid == true){EZRdQefXid = false;}
      if(znTnYpJXaE == true){znTnYpJXaE = false;}
      if(gFlmNYxLHB == true){gFlmNYxLHB = false;}
      if(JMYSYijzuA == true){JMYSYijzuA = false;}
      if(TaEjPXlpgX == true){TaEjPXlpgX = false;}
      if(bjRMYzneQr == true){bjRMYzneQr = false;}
      if(hUQgTmPBOo == true){hUQgTmPBOo = false;}
      if(GKcZkGBBWp == true){GKcZkGBBWp = false;}
      if(lGdiZZtLsZ == true){lGdiZZtLsZ = false;}
      if(uEiCRyJWPc == true){uEiCRyJWPc = false;}
      if(IjbqQRGqbS == true){IjbqQRGqbS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYRMBYFWTT
{ 
  void LuKwnSyjjO()
  { 
      bool UceQdOUXmf = false;
      bool kXAdFMTecJ = false;
      bool PtktkVCCDc = false;
      bool aloGAiukkz = false;
      bool JbwFGaLzxI = false;
      bool WtPUkZqkfI = false;
      bool LRUKEyisdV = false;
      bool RhsdznxfnK = false;
      bool JDFtFgVTVZ = false;
      bool qJFcmqGkAH = false;
      bool qRVapnAlUw = false;
      bool cLwUyIMZEW = false;
      bool bOXDeHcQpI = false;
      bool gLefSrgeDR = false;
      bool fjyYweMjed = false;
      bool eggcectRwi = false;
      bool KjwMPQgQCG = false;
      bool bgVmqrQyHz = false;
      bool trlLcAeBAp = false;
      bool yPiUGwnlJe = false;
      string DodTgjElsN;
      string EFyIMkFwHQ;
      string WUnYfogCRY;
      string sxADJWoARS;
      string ETxIHnWeIW;
      string kEJMthBEmq;
      string DCUUUHEtyo;
      string uFdoLDXeRr;
      string RBtunnmmJa;
      string VkMZOCzbnA;
      string icfSaeaUBq;
      string KVmuYCHYfg;
      string TRkXTKrDaJ;
      string DuqQIoUbTI;
      string NSkRPzyRBL;
      string tZwGfRqIyQ;
      string mWsrmOeVlj;
      string hfFXSAfTHU;
      string LaCOOdzjkq;
      string yMcCUpYsdA;
      if(DodTgjElsN == icfSaeaUBq){UceQdOUXmf = true;}
      else if(icfSaeaUBq == DodTgjElsN){qRVapnAlUw = true;}
      if(EFyIMkFwHQ == KVmuYCHYfg){kXAdFMTecJ = true;}
      else if(KVmuYCHYfg == EFyIMkFwHQ){cLwUyIMZEW = true;}
      if(WUnYfogCRY == TRkXTKrDaJ){PtktkVCCDc = true;}
      else if(TRkXTKrDaJ == WUnYfogCRY){bOXDeHcQpI = true;}
      if(sxADJWoARS == DuqQIoUbTI){aloGAiukkz = true;}
      else if(DuqQIoUbTI == sxADJWoARS){gLefSrgeDR = true;}
      if(ETxIHnWeIW == NSkRPzyRBL){JbwFGaLzxI = true;}
      else if(NSkRPzyRBL == ETxIHnWeIW){fjyYweMjed = true;}
      if(kEJMthBEmq == tZwGfRqIyQ){WtPUkZqkfI = true;}
      else if(tZwGfRqIyQ == kEJMthBEmq){eggcectRwi = true;}
      if(DCUUUHEtyo == mWsrmOeVlj){LRUKEyisdV = true;}
      else if(mWsrmOeVlj == DCUUUHEtyo){KjwMPQgQCG = true;}
      if(uFdoLDXeRr == hfFXSAfTHU){RhsdznxfnK = true;}
      if(RBtunnmmJa == LaCOOdzjkq){JDFtFgVTVZ = true;}
      if(VkMZOCzbnA == yMcCUpYsdA){qJFcmqGkAH = true;}
      while(hfFXSAfTHU == uFdoLDXeRr){bgVmqrQyHz = true;}
      while(LaCOOdzjkq == LaCOOdzjkq){trlLcAeBAp = true;}
      while(yMcCUpYsdA == yMcCUpYsdA){yPiUGwnlJe = true;}
      if(UceQdOUXmf == true){UceQdOUXmf = false;}
      if(kXAdFMTecJ == true){kXAdFMTecJ = false;}
      if(PtktkVCCDc == true){PtktkVCCDc = false;}
      if(aloGAiukkz == true){aloGAiukkz = false;}
      if(JbwFGaLzxI == true){JbwFGaLzxI = false;}
      if(WtPUkZqkfI == true){WtPUkZqkfI = false;}
      if(LRUKEyisdV == true){LRUKEyisdV = false;}
      if(RhsdznxfnK == true){RhsdznxfnK = false;}
      if(JDFtFgVTVZ == true){JDFtFgVTVZ = false;}
      if(qJFcmqGkAH == true){qJFcmqGkAH = false;}
      if(qRVapnAlUw == true){qRVapnAlUw = false;}
      if(cLwUyIMZEW == true){cLwUyIMZEW = false;}
      if(bOXDeHcQpI == true){bOXDeHcQpI = false;}
      if(gLefSrgeDR == true){gLefSrgeDR = false;}
      if(fjyYweMjed == true){fjyYweMjed = false;}
      if(eggcectRwi == true){eggcectRwi = false;}
      if(KjwMPQgQCG == true){KjwMPQgQCG = false;}
      if(bgVmqrQyHz == true){bgVmqrQyHz = false;}
      if(trlLcAeBAp == true){trlLcAeBAp = false;}
      if(yPiUGwnlJe == true){yPiUGwnlJe = false;}
    } 
}; 
