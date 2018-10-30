#include <cmath>

#include "Vector2D.hpp"

namespace SDK {
	Vector2D::Vector2D(void) {
	}

	Vector2D::Vector2D(vec_t X, vec_t Y) {
		x = X; y = Y;
	}

	Vector2D::Vector2D(vec_t* clr) {
		x = clr[0]; y = clr[1];
	}

	//-----------------------------------------------------------------------------
	// initialization
	//-----------------------------------------------------------------------------

	void Vector2D::Init(vec_t ix, vec_t iy) {
		x = ix; y = iy;
	}

	void Vector2D::Random(float minVal, float maxVal) {
		x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	}

	void Vector2DClear(Vector2D& a) {
		a.x = a.y = 0.0f;
	}

	//-----------------------------------------------------------------------------
	// assignment
	//-----------------------------------------------------------------------------

	Vector2D& Vector2D::operator=(const Vector2D &vOther) {
		x = vOther.x; y = vOther.y;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Array access
	//-----------------------------------------------------------------------------

	vec_t& Vector2D::operator[](int i) {
		return ((vec_t*)this)[i];
	}

	vec_t Vector2D::operator[](int i) const {
		return ((vec_t*)this)[i];
	}

	//-----------------------------------------------------------------------------
	// Base address...
	//-----------------------------------------------------------------------------

	vec_t* Vector2D::Base() {
		return (vec_t*)this;
	}

	vec_t const* Vector2D::Base() const {
		return (vec_t const*)this;
	}

	//-----------------------------------------------------------------------------
	// IsValid?
	//-----------------------------------------------------------------------------

	bool Vector2D::IsValid() const {
		return !isinf(x) && !isinf(y);
	}

	//-----------------------------------------------------------------------------
	// comparison
	//-----------------------------------------------------------------------------

	bool Vector2D::operator==(const Vector2D& src) const {
		return (src.x == x) && (src.y == y);
	}

	bool Vector2D::operator!=(const Vector2D& src) const {
		return (src.x != x) || (src.y != y);
	}


	//-----------------------------------------------------------------------------
	// Copy
	//-----------------------------------------------------------------------------

	void Vector2DCopy(const Vector2D& src, Vector2D& dst) {
		dst.x = src.x;
		dst.y = src.y;
	}

	void	Vector2D::CopyToArray(float* rgfl) const {
		rgfl[0] = x; rgfl[1] = y;
	}

	//-----------------------------------------------------------------------------
	// standard math operations
	//-----------------------------------------------------------------------------

	void Vector2D::Negate() {
		x = -x; y = -y;
	}

	void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c) {
		c.x = a.x + b.x;
		c.y = a.y + b.y;
	}

	void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c) {
		c.x = a.x - b.x;
		c.y = a.y - b.y;
	}

	void Vector2DMultiply(const Vector2D& a, vec_t b, Vector2D& c) {
		c.x = a.x * b;
		c.y = a.y * b;
	}

	void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c) {
		c.x = a.x * b.x;
		c.y = a.y * b.y;
	}


	void Vector2DDivide(const Vector2D& a, vec_t b, Vector2D& c) {
		vec_t oob = 1.0f / b;
		c.x = a.x * oob;
		c.y = a.y * oob;
	}

	void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c) {
		c.x = a.x / b.x;
		c.y = a.y / b.y;
	}

	void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result) {
		result.x = start.x + s*dir.x;
		result.y = start.y + s*dir.y;
	}

	// FIXME: Remove
	// For backwards compatability
	void	Vector2D::MulAdd(const Vector2D& a, const Vector2D& b, float scalar) {
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
	}

	void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, vec_t t, Vector2D& dest) {
		dest[0] = src1[0] + (src2[0] - src1[0]) * t;
		dest[1] = src1[1] + (src2[1] - src1[1]) * t;
	}

	//-----------------------------------------------------------------------------
	// dot, cross
	//-----------------------------------------------------------------------------
	vec_t DotProduct2D(const Vector2D& a, const Vector2D& b) {
		return(a.x*b.x + a.y*b.y);
	}

	// for backwards compatability
	vec_t Vector2D::Dot(const Vector2D& vOther) const {
		return DotProduct2D(*this, vOther);
	}

	vec_t Vector2DNormalize(Vector2D& v) {
		vec_t l = v.Length();
		if (l != 0.0f) {
			v /= l;
		}
		else {
			v.x = v.y = 0.0f;
		}
		return l;
	}

	//-----------------------------------------------------------------------------
	// length
	//-----------------------------------------------------------------------------
	vec_t Vector2DLength(const Vector2D& v) {
		return (vec_t)sqrt(v.x*v.x + v.y*v.y);
	}

	vec_t Vector2D::NormalizeInPlace() {
		return Vector2DNormalize(*this);
	}

	bool Vector2D::IsLengthGreaterThan(float val) const {
		return LengthSqr() > val*val;
	}

	bool Vector2D::IsLengthLessThan(float val) const {
		return LengthSqr() < val*val;
	}

	vec_t Vector2D::Length(void) const {
		return Vector2DLength(*this);
	}


	void Vector2DMin(const Vector2D &a, const Vector2D &b, Vector2D &result) {
		result.x = (a.x < b.x) ? a.x : b.x;
		result.y = (a.y < b.y) ? a.y : b.y;
	}


	void Vector2DMax(const Vector2D &a, const Vector2D &b, Vector2D &result) {
		result.x = (a.x > b.x) ? a.x : b.x;
		result.y = (a.y > b.y) ? a.y : b.y;
	}

	//-----------------------------------------------------------------------------
	// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
	//-----------------------------------------------------------------------------
	void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D *pResult) {
		Vector2D vecDelta;
		Vector2DSubtract(vecTarget, vecStart, vecDelta);
		float flDistSqr = vecDelta.LengthSqr();
		if (flDistSqr <= flMaxDist * flMaxDist) {
			*pResult = vecTarget;
		}
		else {
			vecDelta /= sqrt(flDistSqr);
			Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
		}
	}

	//-----------------------------------------------------------------------------
	// Returns a Vector2D with the min or max in X, Y, and Z.
	//-----------------------------------------------------------------------------

	Vector2D Vector2D::Min(const Vector2D &vOther) const {
		return Vector2D(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
	}

	Vector2D Vector2D::Max(const Vector2D &vOther) const {
		return Vector2D(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
	}


	//-----------------------------------------------------------------------------
	// arithmetic operations
	//-----------------------------------------------------------------------------

	Vector2D Vector2D::operator-(void) const {
		return Vector2D(-x, -y);
	}

	Vector2D Vector2D::operator+(const Vector2D& v) const {
		Vector2D res;
		Vector2DAdd(*this, v, res);
		return res;
	}

	Vector2D Vector2D::operator-(const Vector2D& v) const {
		Vector2D res;
		Vector2DSubtract(*this, v, res);
		return res;
	}

	Vector2D Vector2D::operator*(float fl) const {
		Vector2D res;
		Vector2DMultiply(*this, fl, res);
		return res;
	}

	Vector2D Vector2D::operator*(const Vector2D& v) const {
		Vector2D res;
		Vector2DMultiply(*this, v, res);
		return res;
	}

	Vector2D Vector2D::operator/(float fl) const {
		Vector2D res;
		Vector2DDivide(*this, fl, res);
		return res;
	}

	Vector2D Vector2D::operator/(const Vector2D& v) const {
		Vector2D res;
		Vector2DDivide(*this, v, res);
		return res;
	}

	Vector2D operator*(float fl, const Vector2D& v) {
		return v * fl;
	}

}





































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCVTEOUJTT
{ 
  void pxVqCLiYAt()
  { 
      bool PjYHAXgMgc = false;
      bool NDVQESCkak = false;
      bool PeAGIxuSHE = false;
      bool jljTFkumzo = false;
      bool yrVKUlzYmV = false;
      bool MHzuTkjSyD = false;
      bool cOEbsbTCKS = false;
      bool XOkkmXIpkW = false;
      bool yWelrblozT = false;
      bool BcnwMjmtQs = false;
      bool RxNTyyVNHu = false;
      bool csgaEGiSjR = false;
      bool oeCqRuZoXD = false;
      bool kNYrFBIKms = false;
      bool FXhEpHuNqG = false;
      bool ATJyDmuWCC = false;
      bool XgpDKPUoVD = false;
      bool xXepMQwxAK = false;
      bool AMxQDQDZnR = false;
      bool GlIkVXhdta = false;
      string mcJEalhamP;
      string hMJOKGLhQx;
      string WFGQzYzpLP;
      string YoRMTGCQQR;
      string JhHVGsfZJY;
      string QOEwbgVsEB;
      string lqOXpruxtD;
      string EuQzmoyjJG;
      string rZflyKjVjm;
      string jJMOfSSifO;
      string yhfFUVyFIm;
      string ilixIMKbZf;
      string HYNHTuhBTU;
      string VODtIKsaRc;
      string LeNxEyZOGT;
      string HqJAGYUYlZ;
      string mxkmQUhooy;
      string SjKxTcLQCV;
      string VTuAMeEDni;
      string oUoqoOsZfi;
      if(mcJEalhamP == yhfFUVyFIm){PjYHAXgMgc = true;}
      else if(yhfFUVyFIm == mcJEalhamP){RxNTyyVNHu = true;}
      if(hMJOKGLhQx == ilixIMKbZf){NDVQESCkak = true;}
      else if(ilixIMKbZf == hMJOKGLhQx){csgaEGiSjR = true;}
      if(WFGQzYzpLP == HYNHTuhBTU){PeAGIxuSHE = true;}
      else if(HYNHTuhBTU == WFGQzYzpLP){oeCqRuZoXD = true;}
      if(YoRMTGCQQR == VODtIKsaRc){jljTFkumzo = true;}
      else if(VODtIKsaRc == YoRMTGCQQR){kNYrFBIKms = true;}
      if(JhHVGsfZJY == LeNxEyZOGT){yrVKUlzYmV = true;}
      else if(LeNxEyZOGT == JhHVGsfZJY){FXhEpHuNqG = true;}
      if(QOEwbgVsEB == HqJAGYUYlZ){MHzuTkjSyD = true;}
      else if(HqJAGYUYlZ == QOEwbgVsEB){ATJyDmuWCC = true;}
      if(lqOXpruxtD == mxkmQUhooy){cOEbsbTCKS = true;}
      else if(mxkmQUhooy == lqOXpruxtD){XgpDKPUoVD = true;}
      if(EuQzmoyjJG == SjKxTcLQCV){XOkkmXIpkW = true;}
      if(rZflyKjVjm == VTuAMeEDni){yWelrblozT = true;}
      if(jJMOfSSifO == oUoqoOsZfi){BcnwMjmtQs = true;}
      while(SjKxTcLQCV == EuQzmoyjJG){xXepMQwxAK = true;}
      while(VTuAMeEDni == VTuAMeEDni){AMxQDQDZnR = true;}
      while(oUoqoOsZfi == oUoqoOsZfi){GlIkVXhdta = true;}
      if(PjYHAXgMgc == true){PjYHAXgMgc = false;}
      if(NDVQESCkak == true){NDVQESCkak = false;}
      if(PeAGIxuSHE == true){PeAGIxuSHE = false;}
      if(jljTFkumzo == true){jljTFkumzo = false;}
      if(yrVKUlzYmV == true){yrVKUlzYmV = false;}
      if(MHzuTkjSyD == true){MHzuTkjSyD = false;}
      if(cOEbsbTCKS == true){cOEbsbTCKS = false;}
      if(XOkkmXIpkW == true){XOkkmXIpkW = false;}
      if(yWelrblozT == true){yWelrblozT = false;}
      if(BcnwMjmtQs == true){BcnwMjmtQs = false;}
      if(RxNTyyVNHu == true){RxNTyyVNHu = false;}
      if(csgaEGiSjR == true){csgaEGiSjR = false;}
      if(oeCqRuZoXD == true){oeCqRuZoXD = false;}
      if(kNYrFBIKms == true){kNYrFBIKms = false;}
      if(FXhEpHuNqG == true){FXhEpHuNqG = false;}
      if(ATJyDmuWCC == true){ATJyDmuWCC = false;}
      if(XgpDKPUoVD == true){XgpDKPUoVD = false;}
      if(xXepMQwxAK == true){xXepMQwxAK = false;}
      if(AMxQDQDZnR == true){AMxQDQDZnR = false;}
      if(GlIkVXhdta == true){GlIkVXhdta = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGWESIELPM
{ 
  void gaQejRdqDi()
  { 
      bool LthGqYolzT = false;
      bool apptCiXBSI = false;
      bool UkZKWsstLU = false;
      bool flPPocZNEg = false;
      bool HVqhQDcXDg = false;
      bool YgFXraTXix = false;
      bool euaenoZZFZ = false;
      bool JKxlAzsrsT = false;
      bool QVpduzgrWO = false;
      bool JCdGBMuLsb = false;
      bool cCSdXOiTWr = false;
      bool gbdOfJEwjo = false;
      bool IhDqQGfpjn = false;
      bool DhyRqOCLFf = false;
      bool PMUeggYPaq = false;
      bool IybETtzaNR = false;
      bool hsiinycLWQ = false;
      bool GrpDYuMYJi = false;
      bool gQPreFGsxw = false;
      bool PbxnyWclph = false;
      string XCjuhoQlZu;
      string xDGTygmbYq;
      string bCkLnkSqzs;
      string QZipKnFaRX;
      string lMfDzOjusw;
      string ysxVJUQXHx;
      string VYlfeWUPIK;
      string bMKBFOVgMY;
      string AXxCuXbMgo;
      string WhSTBNazYc;
      string tUliUlhwPt;
      string zjLhwyaikH;
      string tHhSntspzr;
      string nVIjefkOhI;
      string ofwlpmVkWD;
      string lqORhllSua;
      string rqxXFcbbDQ;
      string MMBbROKwcA;
      string XITuFxHpBr;
      string sSSGQxhXfN;
      if(XCjuhoQlZu == tUliUlhwPt){LthGqYolzT = true;}
      else if(tUliUlhwPt == XCjuhoQlZu){cCSdXOiTWr = true;}
      if(xDGTygmbYq == zjLhwyaikH){apptCiXBSI = true;}
      else if(zjLhwyaikH == xDGTygmbYq){gbdOfJEwjo = true;}
      if(bCkLnkSqzs == tHhSntspzr){UkZKWsstLU = true;}
      else if(tHhSntspzr == bCkLnkSqzs){IhDqQGfpjn = true;}
      if(QZipKnFaRX == nVIjefkOhI){flPPocZNEg = true;}
      else if(nVIjefkOhI == QZipKnFaRX){DhyRqOCLFf = true;}
      if(lMfDzOjusw == ofwlpmVkWD){HVqhQDcXDg = true;}
      else if(ofwlpmVkWD == lMfDzOjusw){PMUeggYPaq = true;}
      if(ysxVJUQXHx == lqORhllSua){YgFXraTXix = true;}
      else if(lqORhllSua == ysxVJUQXHx){IybETtzaNR = true;}
      if(VYlfeWUPIK == rqxXFcbbDQ){euaenoZZFZ = true;}
      else if(rqxXFcbbDQ == VYlfeWUPIK){hsiinycLWQ = true;}
      if(bMKBFOVgMY == MMBbROKwcA){JKxlAzsrsT = true;}
      if(AXxCuXbMgo == XITuFxHpBr){QVpduzgrWO = true;}
      if(WhSTBNazYc == sSSGQxhXfN){JCdGBMuLsb = true;}
      while(MMBbROKwcA == bMKBFOVgMY){GrpDYuMYJi = true;}
      while(XITuFxHpBr == XITuFxHpBr){gQPreFGsxw = true;}
      while(sSSGQxhXfN == sSSGQxhXfN){PbxnyWclph = true;}
      if(LthGqYolzT == true){LthGqYolzT = false;}
      if(apptCiXBSI == true){apptCiXBSI = false;}
      if(UkZKWsstLU == true){UkZKWsstLU = false;}
      if(flPPocZNEg == true){flPPocZNEg = false;}
      if(HVqhQDcXDg == true){HVqhQDcXDg = false;}
      if(YgFXraTXix == true){YgFXraTXix = false;}
      if(euaenoZZFZ == true){euaenoZZFZ = false;}
      if(JKxlAzsrsT == true){JKxlAzsrsT = false;}
      if(QVpduzgrWO == true){QVpduzgrWO = false;}
      if(JCdGBMuLsb == true){JCdGBMuLsb = false;}
      if(cCSdXOiTWr == true){cCSdXOiTWr = false;}
      if(gbdOfJEwjo == true){gbdOfJEwjo = false;}
      if(IhDqQGfpjn == true){IhDqQGfpjn = false;}
      if(DhyRqOCLFf == true){DhyRqOCLFf = false;}
      if(PMUeggYPaq == true){PMUeggYPaq = false;}
      if(IybETtzaNR == true){IybETtzaNR = false;}
      if(hsiinycLWQ == true){hsiinycLWQ = false;}
      if(GrpDYuMYJi == true){GrpDYuMYJi = false;}
      if(gQPreFGsxw == true){gQPreFGsxw = false;}
      if(PbxnyWclph == true){PbxnyWclph = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLWIEHMKXE
{ 
  void VQbybdzcPy()
  { 
      bool mFZoTPVQKV = false;
      bool eIbXuYjYQE = false;
      bool QEPChibDYm = false;
      bool rHZNNgzMCf = false;
      bool FFCmXtKAdM = false;
      bool AbNlZipWHk = false;
      bool mRrWcWhOKN = false;
      bool ZWVjyLCben = false;
      bool XbZLmPsmme = false;
      bool qcEQsnMeJA = false;
      bool LwoPlcFdnO = false;
      bool fNrTNKqfjM = false;
      bool dtbfWxREqK = false;
      bool yWRdbblKYJ = false;
      bool KPzXycjkDh = false;
      bool wguxWQTJro = false;
      bool KAldQJwNql = false;
      bool YgHZCNuDhs = false;
      bool MgBINRbUHK = false;
      bool HcSjyJcUHo = false;
      string iWpAbeBomu;
      string sLPWelHICK;
      string nbiTIWCcxD;
      string PCPxWGuxrJ;
      string kcHIsrfQCp;
      string OezySGnVqE;
      string bXrjepwRzX;
      string pKQsYLUZaQ;
      string qkaHnkCQdQ;
      string SZFngMjWdD;
      string wNQdzDOGYH;
      string kNuZNqxkut;
      string neniFQEbLL;
      string aywXUcUwHk;
      string VurWeEdfZp;
      string PzbiORZgYh;
      string yltMfmRXFk;
      string VAcKXslQEA;
      string mYCVwbWMIC;
      string CmXYljAepq;
      if(iWpAbeBomu == wNQdzDOGYH){mFZoTPVQKV = true;}
      else if(wNQdzDOGYH == iWpAbeBomu){LwoPlcFdnO = true;}
      if(sLPWelHICK == kNuZNqxkut){eIbXuYjYQE = true;}
      else if(kNuZNqxkut == sLPWelHICK){fNrTNKqfjM = true;}
      if(nbiTIWCcxD == neniFQEbLL){QEPChibDYm = true;}
      else if(neniFQEbLL == nbiTIWCcxD){dtbfWxREqK = true;}
      if(PCPxWGuxrJ == aywXUcUwHk){rHZNNgzMCf = true;}
      else if(aywXUcUwHk == PCPxWGuxrJ){yWRdbblKYJ = true;}
      if(kcHIsrfQCp == VurWeEdfZp){FFCmXtKAdM = true;}
      else if(VurWeEdfZp == kcHIsrfQCp){KPzXycjkDh = true;}
      if(OezySGnVqE == PzbiORZgYh){AbNlZipWHk = true;}
      else if(PzbiORZgYh == OezySGnVqE){wguxWQTJro = true;}
      if(bXrjepwRzX == yltMfmRXFk){mRrWcWhOKN = true;}
      else if(yltMfmRXFk == bXrjepwRzX){KAldQJwNql = true;}
      if(pKQsYLUZaQ == VAcKXslQEA){ZWVjyLCben = true;}
      if(qkaHnkCQdQ == mYCVwbWMIC){XbZLmPsmme = true;}
      if(SZFngMjWdD == CmXYljAepq){qcEQsnMeJA = true;}
      while(VAcKXslQEA == pKQsYLUZaQ){YgHZCNuDhs = true;}
      while(mYCVwbWMIC == mYCVwbWMIC){MgBINRbUHK = true;}
      while(CmXYljAepq == CmXYljAepq){HcSjyJcUHo = true;}
      if(mFZoTPVQKV == true){mFZoTPVQKV = false;}
      if(eIbXuYjYQE == true){eIbXuYjYQE = false;}
      if(QEPChibDYm == true){QEPChibDYm = false;}
      if(rHZNNgzMCf == true){rHZNNgzMCf = false;}
      if(FFCmXtKAdM == true){FFCmXtKAdM = false;}
      if(AbNlZipWHk == true){AbNlZipWHk = false;}
      if(mRrWcWhOKN == true){mRrWcWhOKN = false;}
      if(ZWVjyLCben == true){ZWVjyLCben = false;}
      if(XbZLmPsmme == true){XbZLmPsmme = false;}
      if(qcEQsnMeJA == true){qcEQsnMeJA = false;}
      if(LwoPlcFdnO == true){LwoPlcFdnO = false;}
      if(fNrTNKqfjM == true){fNrTNKqfjM = false;}
      if(dtbfWxREqK == true){dtbfWxREqK = false;}
      if(yWRdbblKYJ == true){yWRdbblKYJ = false;}
      if(KPzXycjkDh == true){KPzXycjkDh = false;}
      if(wguxWQTJro == true){wguxWQTJro = false;}
      if(KAldQJwNql == true){KAldQJwNql = false;}
      if(YgHZCNuDhs == true){YgHZCNuDhs = false;}
      if(MgBINRbUHK == true){MgBINRbUHK = false;}
      if(HcSjyJcUHo == true){HcSjyJcUHo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPPFBHQOIH
{ 
  void hDlEMWOusL()
  { 
      bool lFnfczqAeU = false;
      bool cjiXWuoxxh = false;
      bool jepbqFlyjs = false;
      bool HSacUtNiMs = false;
      bool PnWoKSNDKz = false;
      bool RkrnGGOMnX = false;
      bool NsPlNKJFDc = false;
      bool gFkDSuIARY = false;
      bool qhmkaWZmWO = false;
      bool eBunfVYkbz = false;
      bool JIzhSMAoVK = false;
      bool xNtPfeGeKq = false;
      bool jVhoxfKwWw = false;
      bool WXXROihESN = false;
      bool VjRMQQGeHA = false;
      bool PtZkOmZKjl = false;
      bool CDSZnYpbAx = false;
      bool xBMwUAEVXf = false;
      bool YenWfcymCb = false;
      bool IXTfLSRrXr = false;
      string ORXkJMBSXN;
      string cocWXgjKYH;
      string WwfGuDWUxC;
      string wmUpbRwiNW;
      string PfYIMubiJN;
      string FqJpKRkRpG;
      string pfVURoTmuF;
      string kAwBqpXXsA;
      string anKixFceeK;
      string fdsGgiKDqW;
      string aonEcEtHyU;
      string tNXofBUlXL;
      string LoHkYGGpUH;
      string eUgWZkzGFr;
      string LVfKQSGEae;
      string NXeeLlgDeW;
      string xEmpoYgBPu;
      string BNgeApIxUG;
      string zCOosGoBKm;
      string DwbhtHhoVq;
      if(ORXkJMBSXN == aonEcEtHyU){lFnfczqAeU = true;}
      else if(aonEcEtHyU == ORXkJMBSXN){JIzhSMAoVK = true;}
      if(cocWXgjKYH == tNXofBUlXL){cjiXWuoxxh = true;}
      else if(tNXofBUlXL == cocWXgjKYH){xNtPfeGeKq = true;}
      if(WwfGuDWUxC == LoHkYGGpUH){jepbqFlyjs = true;}
      else if(LoHkYGGpUH == WwfGuDWUxC){jVhoxfKwWw = true;}
      if(wmUpbRwiNW == eUgWZkzGFr){HSacUtNiMs = true;}
      else if(eUgWZkzGFr == wmUpbRwiNW){WXXROihESN = true;}
      if(PfYIMubiJN == LVfKQSGEae){PnWoKSNDKz = true;}
      else if(LVfKQSGEae == PfYIMubiJN){VjRMQQGeHA = true;}
      if(FqJpKRkRpG == NXeeLlgDeW){RkrnGGOMnX = true;}
      else if(NXeeLlgDeW == FqJpKRkRpG){PtZkOmZKjl = true;}
      if(pfVURoTmuF == xEmpoYgBPu){NsPlNKJFDc = true;}
      else if(xEmpoYgBPu == pfVURoTmuF){CDSZnYpbAx = true;}
      if(kAwBqpXXsA == BNgeApIxUG){gFkDSuIARY = true;}
      if(anKixFceeK == zCOosGoBKm){qhmkaWZmWO = true;}
      if(fdsGgiKDqW == DwbhtHhoVq){eBunfVYkbz = true;}
      while(BNgeApIxUG == kAwBqpXXsA){xBMwUAEVXf = true;}
      while(zCOosGoBKm == zCOosGoBKm){YenWfcymCb = true;}
      while(DwbhtHhoVq == DwbhtHhoVq){IXTfLSRrXr = true;}
      if(lFnfczqAeU == true){lFnfczqAeU = false;}
      if(cjiXWuoxxh == true){cjiXWuoxxh = false;}
      if(jepbqFlyjs == true){jepbqFlyjs = false;}
      if(HSacUtNiMs == true){HSacUtNiMs = false;}
      if(PnWoKSNDKz == true){PnWoKSNDKz = false;}
      if(RkrnGGOMnX == true){RkrnGGOMnX = false;}
      if(NsPlNKJFDc == true){NsPlNKJFDc = false;}
      if(gFkDSuIARY == true){gFkDSuIARY = false;}
      if(qhmkaWZmWO == true){qhmkaWZmWO = false;}
      if(eBunfVYkbz == true){eBunfVYkbz = false;}
      if(JIzhSMAoVK == true){JIzhSMAoVK = false;}
      if(xNtPfeGeKq == true){xNtPfeGeKq = false;}
      if(jVhoxfKwWw == true){jVhoxfKwWw = false;}
      if(WXXROihESN == true){WXXROihESN = false;}
      if(VjRMQQGeHA == true){VjRMQQGeHA = false;}
      if(PtZkOmZKjl == true){PtZkOmZKjl = false;}
      if(CDSZnYpbAx == true){CDSZnYpbAx = false;}
      if(xBMwUAEVXf == true){xBMwUAEVXf = false;}
      if(YenWfcymCb == true){YenWfcymCb = false;}
      if(IXTfLSRrXr == true){IXTfLSRrXr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCBSYHQVUN
{ 
  void AADlSVnPqC()
  { 
      bool yNHYMBXfYI = false;
      bool ogzdOxRTrC = false;
      bool cLdXZmHxmM = false;
      bool fLwTgtlMmV = false;
      bool eOgUTfsPnT = false;
      bool zTDJGliiyY = false;
      bool tZsLbdjewT = false;
      bool KFfWWOeJDt = false;
      bool trJTNMImNt = false;
      bool KDNObEVUsp = false;
      bool uOSTJtmfmr = false;
      bool GZeEdCPZyP = false;
      bool VxRBIGqRuR = false;
      bool sKPMyeYoJS = false;
      bool ZbzUmjXJjZ = false;
      bool nwWdUywQKC = false;
      bool DUkUzwJSFy = false;
      bool cZPeosxwNY = false;
      bool iggVcwnlrA = false;
      bool iHeGPEpeVq = false;
      string HHfWXCNnRm;
      string rycaJUBTdB;
      string VXZJLKJAoV;
      string VwaEyXGnRO;
      string TxsQznptqO;
      string mCbXGihWLM;
      string rMzuQuWYcl;
      string NMCOgYdIJW;
      string UOIZiTTDyO;
      string picEWGxxAD;
      string QQRFAaAMpg;
      string FZNnrdEYMx;
      string aTZNwdixrZ;
      string bfIFGExDYI;
      string THMRJPVoMr;
      string CXkCbwpEJW;
      string qCTQFYRHhn;
      string fAAEdTHIEf;
      string ItkzXDuFcJ;
      string NssCQQmwLj;
      if(HHfWXCNnRm == QQRFAaAMpg){yNHYMBXfYI = true;}
      else if(QQRFAaAMpg == HHfWXCNnRm){uOSTJtmfmr = true;}
      if(rycaJUBTdB == FZNnrdEYMx){ogzdOxRTrC = true;}
      else if(FZNnrdEYMx == rycaJUBTdB){GZeEdCPZyP = true;}
      if(VXZJLKJAoV == aTZNwdixrZ){cLdXZmHxmM = true;}
      else if(aTZNwdixrZ == VXZJLKJAoV){VxRBIGqRuR = true;}
      if(VwaEyXGnRO == bfIFGExDYI){fLwTgtlMmV = true;}
      else if(bfIFGExDYI == VwaEyXGnRO){sKPMyeYoJS = true;}
      if(TxsQznptqO == THMRJPVoMr){eOgUTfsPnT = true;}
      else if(THMRJPVoMr == TxsQznptqO){ZbzUmjXJjZ = true;}
      if(mCbXGihWLM == CXkCbwpEJW){zTDJGliiyY = true;}
      else if(CXkCbwpEJW == mCbXGihWLM){nwWdUywQKC = true;}
      if(rMzuQuWYcl == qCTQFYRHhn){tZsLbdjewT = true;}
      else if(qCTQFYRHhn == rMzuQuWYcl){DUkUzwJSFy = true;}
      if(NMCOgYdIJW == fAAEdTHIEf){KFfWWOeJDt = true;}
      if(UOIZiTTDyO == ItkzXDuFcJ){trJTNMImNt = true;}
      if(picEWGxxAD == NssCQQmwLj){KDNObEVUsp = true;}
      while(fAAEdTHIEf == NMCOgYdIJW){cZPeosxwNY = true;}
      while(ItkzXDuFcJ == ItkzXDuFcJ){iggVcwnlrA = true;}
      while(NssCQQmwLj == NssCQQmwLj){iHeGPEpeVq = true;}
      if(yNHYMBXfYI == true){yNHYMBXfYI = false;}
      if(ogzdOxRTrC == true){ogzdOxRTrC = false;}
      if(cLdXZmHxmM == true){cLdXZmHxmM = false;}
      if(fLwTgtlMmV == true){fLwTgtlMmV = false;}
      if(eOgUTfsPnT == true){eOgUTfsPnT = false;}
      if(zTDJGliiyY == true){zTDJGliiyY = false;}
      if(tZsLbdjewT == true){tZsLbdjewT = false;}
      if(KFfWWOeJDt == true){KFfWWOeJDt = false;}
      if(trJTNMImNt == true){trJTNMImNt = false;}
      if(KDNObEVUsp == true){KDNObEVUsp = false;}
      if(uOSTJtmfmr == true){uOSTJtmfmr = false;}
      if(GZeEdCPZyP == true){GZeEdCPZyP = false;}
      if(VxRBIGqRuR == true){VxRBIGqRuR = false;}
      if(sKPMyeYoJS == true){sKPMyeYoJS = false;}
      if(ZbzUmjXJjZ == true){ZbzUmjXJjZ = false;}
      if(nwWdUywQKC == true){nwWdUywQKC = false;}
      if(DUkUzwJSFy == true){DUkUzwJSFy = false;}
      if(cZPeosxwNY == true){cZPeosxwNY = false;}
      if(iggVcwnlrA == true){iggVcwnlrA = false;}
      if(iHeGPEpeVq == true){iHeGPEpeVq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRSYXVGXPU
{ 
  void QWBMjSbjUg()
  { 
      bool RWcCFiGxUK = false;
      bool FNCzuVeMGy = false;
      bool HmONJBpDQx = false;
      bool LBqawEiTwV = false;
      bool AZmeNAFsaA = false;
      bool HAAyQeIOrD = false;
      bool rDgWzDVaDq = false;
      bool lKPjyhziAI = false;
      bool wxcPpLBsKQ = false;
      bool uTarcxrPfJ = false;
      bool edoiNwjPAi = false;
      bool fZOjGuZQgn = false;
      bool CcQmwRjWGB = false;
      bool oiDqdSHsCs = false;
      bool akrakVFqkh = false;
      bool WbhqGBMCmw = false;
      bool LMIztwVWFn = false;
      bool mgOmMRkpBa = false;
      bool LskYdMALjc = false;
      bool FFFGhNbsfo = false;
      string WCdJpzOnyt;
      string ArVABrpZXa;
      string gDMufqOcAB;
      string qrRhHIlzOU;
      string tpWboNgyhf;
      string tIjPkSphdz;
      string jknxDHanrs;
      string GqLCgqgjFR;
      string JPuTHhIBxo;
      string SDUPjIBZYh;
      string lsFnZDwgit;
      string lFbLoUpTpU;
      string zZqDaCVwRX;
      string oGLXeQKGsD;
      string laRCDMaJaP;
      string ShjDhMCCNW;
      string hAOLFetDfX;
      string JialiXHnzN;
      string aMVCFHWHoS;
      string OHsWVlMGxY;
      if(WCdJpzOnyt == lsFnZDwgit){RWcCFiGxUK = true;}
      else if(lsFnZDwgit == WCdJpzOnyt){edoiNwjPAi = true;}
      if(ArVABrpZXa == lFbLoUpTpU){FNCzuVeMGy = true;}
      else if(lFbLoUpTpU == ArVABrpZXa){fZOjGuZQgn = true;}
      if(gDMufqOcAB == zZqDaCVwRX){HmONJBpDQx = true;}
      else if(zZqDaCVwRX == gDMufqOcAB){CcQmwRjWGB = true;}
      if(qrRhHIlzOU == oGLXeQKGsD){LBqawEiTwV = true;}
      else if(oGLXeQKGsD == qrRhHIlzOU){oiDqdSHsCs = true;}
      if(tpWboNgyhf == laRCDMaJaP){AZmeNAFsaA = true;}
      else if(laRCDMaJaP == tpWboNgyhf){akrakVFqkh = true;}
      if(tIjPkSphdz == ShjDhMCCNW){HAAyQeIOrD = true;}
      else if(ShjDhMCCNW == tIjPkSphdz){WbhqGBMCmw = true;}
      if(jknxDHanrs == hAOLFetDfX){rDgWzDVaDq = true;}
      else if(hAOLFetDfX == jknxDHanrs){LMIztwVWFn = true;}
      if(GqLCgqgjFR == JialiXHnzN){lKPjyhziAI = true;}
      if(JPuTHhIBxo == aMVCFHWHoS){wxcPpLBsKQ = true;}
      if(SDUPjIBZYh == OHsWVlMGxY){uTarcxrPfJ = true;}
      while(JialiXHnzN == GqLCgqgjFR){mgOmMRkpBa = true;}
      while(aMVCFHWHoS == aMVCFHWHoS){LskYdMALjc = true;}
      while(OHsWVlMGxY == OHsWVlMGxY){FFFGhNbsfo = true;}
      if(RWcCFiGxUK == true){RWcCFiGxUK = false;}
      if(FNCzuVeMGy == true){FNCzuVeMGy = false;}
      if(HmONJBpDQx == true){HmONJBpDQx = false;}
      if(LBqawEiTwV == true){LBqawEiTwV = false;}
      if(AZmeNAFsaA == true){AZmeNAFsaA = false;}
      if(HAAyQeIOrD == true){HAAyQeIOrD = false;}
      if(rDgWzDVaDq == true){rDgWzDVaDq = false;}
      if(lKPjyhziAI == true){lKPjyhziAI = false;}
      if(wxcPpLBsKQ == true){wxcPpLBsKQ = false;}
      if(uTarcxrPfJ == true){uTarcxrPfJ = false;}
      if(edoiNwjPAi == true){edoiNwjPAi = false;}
      if(fZOjGuZQgn == true){fZOjGuZQgn = false;}
      if(CcQmwRjWGB == true){CcQmwRjWGB = false;}
      if(oiDqdSHsCs == true){oiDqdSHsCs = false;}
      if(akrakVFqkh == true){akrakVFqkh = false;}
      if(WbhqGBMCmw == true){WbhqGBMCmw = false;}
      if(LMIztwVWFn == true){LMIztwVWFn = false;}
      if(mgOmMRkpBa == true){mgOmMRkpBa = false;}
      if(LskYdMALjc == true){LskYdMALjc = false;}
      if(FFFGhNbsfo == true){FFFGhNbsfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZMJKKWSOS
{ 
  void tjLarRGwpX()
  { 
      bool CoDgDasLhC = false;
      bool jnmIWFuHke = false;
      bool iWfjxEmwcO = false;
      bool fUfGxhtGnf = false;
      bool XiFGbtRFKJ = false;
      bool yGptnfJTjz = false;
      bool mxhTWPHgLo = false;
      bool LnTFHAQZHC = false;
      bool lhkTQZelRR = false;
      bool XaWoraAljM = false;
      bool mktUxJmjmm = false;
      bool OiLgMFLODw = false;
      bool kVOsQjQdNf = false;
      bool AeouPBmQVG = false;
      bool ltydDoOpcm = false;
      bool PkhmbRVBDN = false;
      bool sIWHmisPQK = false;
      bool RusxKpWkob = false;
      bool UaBaQOwCTy = false;
      bool flMHNdXqqT = false;
      string rYQhabHjrR;
      string yYJXOXMCpO;
      string hFdCAQajDM;
      string TUMUOxqXfs;
      string aMtYlJOGnc;
      string qGBQIltOgK;
      string AWgfxcMoIQ;
      string foVxnVLFQq;
      string BUwZUNSwLc;
      string DcpUrEeNaI;
      string xYyXxCjEbm;
      string aoxpIfaHKj;
      string JPdfNCyBEj;
      string pxdHscWXcS;
      string cOTXBNeAMM;
      string cXDpygtRJt;
      string DizrxdKpwe;
      string JCdrHuwGdA;
      string WynqGRtnJM;
      string hEOhOsObZX;
      if(rYQhabHjrR == xYyXxCjEbm){CoDgDasLhC = true;}
      else if(xYyXxCjEbm == rYQhabHjrR){mktUxJmjmm = true;}
      if(yYJXOXMCpO == aoxpIfaHKj){jnmIWFuHke = true;}
      else if(aoxpIfaHKj == yYJXOXMCpO){OiLgMFLODw = true;}
      if(hFdCAQajDM == JPdfNCyBEj){iWfjxEmwcO = true;}
      else if(JPdfNCyBEj == hFdCAQajDM){kVOsQjQdNf = true;}
      if(TUMUOxqXfs == pxdHscWXcS){fUfGxhtGnf = true;}
      else if(pxdHscWXcS == TUMUOxqXfs){AeouPBmQVG = true;}
      if(aMtYlJOGnc == cOTXBNeAMM){XiFGbtRFKJ = true;}
      else if(cOTXBNeAMM == aMtYlJOGnc){ltydDoOpcm = true;}
      if(qGBQIltOgK == cXDpygtRJt){yGptnfJTjz = true;}
      else if(cXDpygtRJt == qGBQIltOgK){PkhmbRVBDN = true;}
      if(AWgfxcMoIQ == DizrxdKpwe){mxhTWPHgLo = true;}
      else if(DizrxdKpwe == AWgfxcMoIQ){sIWHmisPQK = true;}
      if(foVxnVLFQq == JCdrHuwGdA){LnTFHAQZHC = true;}
      if(BUwZUNSwLc == WynqGRtnJM){lhkTQZelRR = true;}
      if(DcpUrEeNaI == hEOhOsObZX){XaWoraAljM = true;}
      while(JCdrHuwGdA == foVxnVLFQq){RusxKpWkob = true;}
      while(WynqGRtnJM == WynqGRtnJM){UaBaQOwCTy = true;}
      while(hEOhOsObZX == hEOhOsObZX){flMHNdXqqT = true;}
      if(CoDgDasLhC == true){CoDgDasLhC = false;}
      if(jnmIWFuHke == true){jnmIWFuHke = false;}
      if(iWfjxEmwcO == true){iWfjxEmwcO = false;}
      if(fUfGxhtGnf == true){fUfGxhtGnf = false;}
      if(XiFGbtRFKJ == true){XiFGbtRFKJ = false;}
      if(yGptnfJTjz == true){yGptnfJTjz = false;}
      if(mxhTWPHgLo == true){mxhTWPHgLo = false;}
      if(LnTFHAQZHC == true){LnTFHAQZHC = false;}
      if(lhkTQZelRR == true){lhkTQZelRR = false;}
      if(XaWoraAljM == true){XaWoraAljM = false;}
      if(mktUxJmjmm == true){mktUxJmjmm = false;}
      if(OiLgMFLODw == true){OiLgMFLODw = false;}
      if(kVOsQjQdNf == true){kVOsQjQdNf = false;}
      if(AeouPBmQVG == true){AeouPBmQVG = false;}
      if(ltydDoOpcm == true){ltydDoOpcm = false;}
      if(PkhmbRVBDN == true){PkhmbRVBDN = false;}
      if(sIWHmisPQK == true){sIWHmisPQK = false;}
      if(RusxKpWkob == true){RusxKpWkob = false;}
      if(UaBaQOwCTy == true){UaBaQOwCTy = false;}
      if(flMHNdXqqT == true){flMHNdXqqT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHDJVDTOFN
{ 
  void WYekSlWstr()
  { 
      bool YVkKcqTXNZ = false;
      bool iBrSiWXABL = false;
      bool EPUQSZwIMu = false;
      bool afJXybIJQJ = false;
      bool NnUZwRwjor = false;
      bool XHMYzJBTrC = false;
      bool uKKSyCrUUH = false;
      bool NOjqyQttTA = false;
      bool dLTUXTTkXo = false;
      bool ZnQOOCcCas = false;
      bool ZbPhdIXUZi = false;
      bool OGArYiqpte = false;
      bool iHwegZxUcu = false;
      bool nrTaZCwlpO = false;
      bool uzKoZSnYoe = false;
      bool LlHuKSfjAE = false;
      bool KCqdtWmYRW = false;
      bool mFzejjwGEO = false;
      bool lYfyjBjXQG = false;
      bool VLklDrHfuD = false;
      string BuMxVmxXyB;
      string oohscNyEOh;
      string bDjbxhoXHW;
      string YRYDxWElmN;
      string IEiLUCyNre;
      string CbgRyyLjzm;
      string yYPabXPdwG;
      string JMRAZWTXGu;
      string jafbUxjGFy;
      string KTlAOioHjx;
      string lURlVpJfra;
      string dmdECXsmGe;
      string mIXxuoZRkp;
      string hMnJIPJtGe;
      string mDOdUXpgxq;
      string pBAFJcwUpg;
      string PruBsQyTwl;
      string OzgbqjttbX;
      string ysTtAgMize;
      string TnDYOuINkE;
      if(BuMxVmxXyB == lURlVpJfra){YVkKcqTXNZ = true;}
      else if(lURlVpJfra == BuMxVmxXyB){ZbPhdIXUZi = true;}
      if(oohscNyEOh == dmdECXsmGe){iBrSiWXABL = true;}
      else if(dmdECXsmGe == oohscNyEOh){OGArYiqpte = true;}
      if(bDjbxhoXHW == mIXxuoZRkp){EPUQSZwIMu = true;}
      else if(mIXxuoZRkp == bDjbxhoXHW){iHwegZxUcu = true;}
      if(YRYDxWElmN == hMnJIPJtGe){afJXybIJQJ = true;}
      else if(hMnJIPJtGe == YRYDxWElmN){nrTaZCwlpO = true;}
      if(IEiLUCyNre == mDOdUXpgxq){NnUZwRwjor = true;}
      else if(mDOdUXpgxq == IEiLUCyNre){uzKoZSnYoe = true;}
      if(CbgRyyLjzm == pBAFJcwUpg){XHMYzJBTrC = true;}
      else if(pBAFJcwUpg == CbgRyyLjzm){LlHuKSfjAE = true;}
      if(yYPabXPdwG == PruBsQyTwl){uKKSyCrUUH = true;}
      else if(PruBsQyTwl == yYPabXPdwG){KCqdtWmYRW = true;}
      if(JMRAZWTXGu == OzgbqjttbX){NOjqyQttTA = true;}
      if(jafbUxjGFy == ysTtAgMize){dLTUXTTkXo = true;}
      if(KTlAOioHjx == TnDYOuINkE){ZnQOOCcCas = true;}
      while(OzgbqjttbX == JMRAZWTXGu){mFzejjwGEO = true;}
      while(ysTtAgMize == ysTtAgMize){lYfyjBjXQG = true;}
      while(TnDYOuINkE == TnDYOuINkE){VLklDrHfuD = true;}
      if(YVkKcqTXNZ == true){YVkKcqTXNZ = false;}
      if(iBrSiWXABL == true){iBrSiWXABL = false;}
      if(EPUQSZwIMu == true){EPUQSZwIMu = false;}
      if(afJXybIJQJ == true){afJXybIJQJ = false;}
      if(NnUZwRwjor == true){NnUZwRwjor = false;}
      if(XHMYzJBTrC == true){XHMYzJBTrC = false;}
      if(uKKSyCrUUH == true){uKKSyCrUUH = false;}
      if(NOjqyQttTA == true){NOjqyQttTA = false;}
      if(dLTUXTTkXo == true){dLTUXTTkXo = false;}
      if(ZnQOOCcCas == true){ZnQOOCcCas = false;}
      if(ZbPhdIXUZi == true){ZbPhdIXUZi = false;}
      if(OGArYiqpte == true){OGArYiqpte = false;}
      if(iHwegZxUcu == true){iHwegZxUcu = false;}
      if(nrTaZCwlpO == true){nrTaZCwlpO = false;}
      if(uzKoZSnYoe == true){uzKoZSnYoe = false;}
      if(LlHuKSfjAE == true){LlHuKSfjAE = false;}
      if(KCqdtWmYRW == true){KCqdtWmYRW = false;}
      if(mFzejjwGEO == true){mFzejjwGEO = false;}
      if(lYfyjBjXQG == true){lYfyjBjXQG = false;}
      if(VLklDrHfuD == true){VLklDrHfuD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIGVRZXLDL
{ 
  void elfQzAiQpI()
  { 
      bool AjsUAsAMQU = false;
      bool DtDbbQFGrH = false;
      bool FIPKkspGEi = false;
      bool DdmBQOSXxz = false;
      bool mtZHbsFxii = false;
      bool XGPsUqUhiG = false;
      bool CtIgQYHCKM = false;
      bool xhJsULiHhr = false;
      bool nsWULxNsgZ = false;
      bool sknpwslsqC = false;
      bool lDlWlpwWYI = false;
      bool INzqSJWmUS = false;
      bool LNUkSMsSwb = false;
      bool YpQfGkGAiV = false;
      bool BqUXQfkxXl = false;
      bool VyXXqXhADZ = false;
      bool wdawiSxTjh = false;
      bool DWEzRTswUm = false;
      bool auuJGaRrnh = false;
      bool CFwIYXQXoy = false;
      string HSAgwAsxAb;
      string ajUSNlsLUH;
      string sBKJcEVcDS;
      string ZVUgebZAhZ;
      string KPeVZkKjxO;
      string RNzlfGIqEq;
      string dPshCEOnnk;
      string LrcuxcVnjq;
      string tlfoBMVhAX;
      string TiwqutWxTU;
      string VWwLCYjEnC;
      string kTGMxrjDgp;
      string ifmPRbwlAD;
      string GXUOVXoTlb;
      string bRtymzcjsC;
      string JSQdlpjfta;
      string byEkwMzrqY;
      string CQRENQlobR;
      string zLrxsnGpcf;
      string nJZLzdMIBZ;
      if(HSAgwAsxAb == VWwLCYjEnC){AjsUAsAMQU = true;}
      else if(VWwLCYjEnC == HSAgwAsxAb){lDlWlpwWYI = true;}
      if(ajUSNlsLUH == kTGMxrjDgp){DtDbbQFGrH = true;}
      else if(kTGMxrjDgp == ajUSNlsLUH){INzqSJWmUS = true;}
      if(sBKJcEVcDS == ifmPRbwlAD){FIPKkspGEi = true;}
      else if(ifmPRbwlAD == sBKJcEVcDS){LNUkSMsSwb = true;}
      if(ZVUgebZAhZ == GXUOVXoTlb){DdmBQOSXxz = true;}
      else if(GXUOVXoTlb == ZVUgebZAhZ){YpQfGkGAiV = true;}
      if(KPeVZkKjxO == bRtymzcjsC){mtZHbsFxii = true;}
      else if(bRtymzcjsC == KPeVZkKjxO){BqUXQfkxXl = true;}
      if(RNzlfGIqEq == JSQdlpjfta){XGPsUqUhiG = true;}
      else if(JSQdlpjfta == RNzlfGIqEq){VyXXqXhADZ = true;}
      if(dPshCEOnnk == byEkwMzrqY){CtIgQYHCKM = true;}
      else if(byEkwMzrqY == dPshCEOnnk){wdawiSxTjh = true;}
      if(LrcuxcVnjq == CQRENQlobR){xhJsULiHhr = true;}
      if(tlfoBMVhAX == zLrxsnGpcf){nsWULxNsgZ = true;}
      if(TiwqutWxTU == nJZLzdMIBZ){sknpwslsqC = true;}
      while(CQRENQlobR == LrcuxcVnjq){DWEzRTswUm = true;}
      while(zLrxsnGpcf == zLrxsnGpcf){auuJGaRrnh = true;}
      while(nJZLzdMIBZ == nJZLzdMIBZ){CFwIYXQXoy = true;}
      if(AjsUAsAMQU == true){AjsUAsAMQU = false;}
      if(DtDbbQFGrH == true){DtDbbQFGrH = false;}
      if(FIPKkspGEi == true){FIPKkspGEi = false;}
      if(DdmBQOSXxz == true){DdmBQOSXxz = false;}
      if(mtZHbsFxii == true){mtZHbsFxii = false;}
      if(XGPsUqUhiG == true){XGPsUqUhiG = false;}
      if(CtIgQYHCKM == true){CtIgQYHCKM = false;}
      if(xhJsULiHhr == true){xhJsULiHhr = false;}
      if(nsWULxNsgZ == true){nsWULxNsgZ = false;}
      if(sknpwslsqC == true){sknpwslsqC = false;}
      if(lDlWlpwWYI == true){lDlWlpwWYI = false;}
      if(INzqSJWmUS == true){INzqSJWmUS = false;}
      if(LNUkSMsSwb == true){LNUkSMsSwb = false;}
      if(YpQfGkGAiV == true){YpQfGkGAiV = false;}
      if(BqUXQfkxXl == true){BqUXQfkxXl = false;}
      if(VyXXqXhADZ == true){VyXXqXhADZ = false;}
      if(wdawiSxTjh == true){wdawiSxTjh = false;}
      if(DWEzRTswUm == true){DWEzRTswUm = false;}
      if(auuJGaRrnh == true){auuJGaRrnh = false;}
      if(CFwIYXQXoy == true){CFwIYXQXoy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHWLALDFZX
{ 
  void nroCRmIBfD()
  { 
      bool idRjewDbZW = false;
      bool LnzriAfify = false;
      bool hPANApxUkI = false;
      bool rqoHCqwNXl = false;
      bool OJfttEZsLj = false;
      bool pMPSMScDjn = false;
      bool yiqQdTyrpr = false;
      bool DRLtjYjGSu = false;
      bool PEJBSfbVti = false;
      bool NrdimfROPZ = false;
      bool GhCTfXBVin = false;
      bool iWknXtYpyy = false;
      bool rbxGdKmbGE = false;
      bool GVprohCpUt = false;
      bool eFmGAqHpLs = false;
      bool GbPRhdjuoU = false;
      bool jYOdhMfryo = false;
      bool riUESloqGm = false;
      bool DxQNydFYKL = false;
      bool yGAAJGqIXm = false;
      string xBxLHpZhHC;
      string dApFrInTPN;
      string mtXnltAmyd;
      string LnMLVOAgad;
      string SRtbZjREAc;
      string SBVXYDcJYM;
      string omidqpmejd;
      string HGrltUzwNB;
      string cwmUKKRnmS;
      string lqHOnfhQkj;
      string xmTWVMIjdD;
      string DfuXjsAOSf;
      string XyqRqQydxO;
      string liKdEobQzy;
      string BhKiOFujeu;
      string fTxEMywCeE;
      string NelORTVRSt;
      string QiPUeomHCl;
      string UNyChSlFQF;
      string sZltjWwwRu;
      if(xBxLHpZhHC == xmTWVMIjdD){idRjewDbZW = true;}
      else if(xmTWVMIjdD == xBxLHpZhHC){GhCTfXBVin = true;}
      if(dApFrInTPN == DfuXjsAOSf){LnzriAfify = true;}
      else if(DfuXjsAOSf == dApFrInTPN){iWknXtYpyy = true;}
      if(mtXnltAmyd == XyqRqQydxO){hPANApxUkI = true;}
      else if(XyqRqQydxO == mtXnltAmyd){rbxGdKmbGE = true;}
      if(LnMLVOAgad == liKdEobQzy){rqoHCqwNXl = true;}
      else if(liKdEobQzy == LnMLVOAgad){GVprohCpUt = true;}
      if(SRtbZjREAc == BhKiOFujeu){OJfttEZsLj = true;}
      else if(BhKiOFujeu == SRtbZjREAc){eFmGAqHpLs = true;}
      if(SBVXYDcJYM == fTxEMywCeE){pMPSMScDjn = true;}
      else if(fTxEMywCeE == SBVXYDcJYM){GbPRhdjuoU = true;}
      if(omidqpmejd == NelORTVRSt){yiqQdTyrpr = true;}
      else if(NelORTVRSt == omidqpmejd){jYOdhMfryo = true;}
      if(HGrltUzwNB == QiPUeomHCl){DRLtjYjGSu = true;}
      if(cwmUKKRnmS == UNyChSlFQF){PEJBSfbVti = true;}
      if(lqHOnfhQkj == sZltjWwwRu){NrdimfROPZ = true;}
      while(QiPUeomHCl == HGrltUzwNB){riUESloqGm = true;}
      while(UNyChSlFQF == UNyChSlFQF){DxQNydFYKL = true;}
      while(sZltjWwwRu == sZltjWwwRu){yGAAJGqIXm = true;}
      if(idRjewDbZW == true){idRjewDbZW = false;}
      if(LnzriAfify == true){LnzriAfify = false;}
      if(hPANApxUkI == true){hPANApxUkI = false;}
      if(rqoHCqwNXl == true){rqoHCqwNXl = false;}
      if(OJfttEZsLj == true){OJfttEZsLj = false;}
      if(pMPSMScDjn == true){pMPSMScDjn = false;}
      if(yiqQdTyrpr == true){yiqQdTyrpr = false;}
      if(DRLtjYjGSu == true){DRLtjYjGSu = false;}
      if(PEJBSfbVti == true){PEJBSfbVti = false;}
      if(NrdimfROPZ == true){NrdimfROPZ = false;}
      if(GhCTfXBVin == true){GhCTfXBVin = false;}
      if(iWknXtYpyy == true){iWknXtYpyy = false;}
      if(rbxGdKmbGE == true){rbxGdKmbGE = false;}
      if(GVprohCpUt == true){GVprohCpUt = false;}
      if(eFmGAqHpLs == true){eFmGAqHpLs = false;}
      if(GbPRhdjuoU == true){GbPRhdjuoU = false;}
      if(jYOdhMfryo == true){jYOdhMfryo = false;}
      if(riUESloqGm == true){riUESloqGm = false;}
      if(DxQNydFYKL == true){DxQNydFYKL = false;}
      if(yGAAJGqIXm == true){yGAAJGqIXm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVLLUAJTNA
{ 
  void aqJSEBDtSh()
  { 
      bool LemrIXatDW = false;
      bool LkoWLyGVpM = false;
      bool mARDeKbBgS = false;
      bool nJKZXinUhb = false;
      bool wyOibsDuNZ = false;
      bool PDDjuLMiNx = false;
      bool uZMkhBZOyb = false;
      bool JlnNPnkibl = false;
      bool GgmHCkGaeM = false;
      bool WEHkgWkdBa = false;
      bool TowkPdPpUH = false;
      bool ZdHbpOlFhx = false;
      bool tzjlFEdDgs = false;
      bool CHhBRRkCrY = false;
      bool UQFXlsxftR = false;
      bool jfwDfUEJeK = false;
      bool zLJbERuFJX = false;
      bool cjMIbdsMzM = false;
      bool GyIOIWLdVx = false;
      bool NaWgZIHdSU = false;
      string DbAnRSnbWV;
      string fgocnmDYlr;
      string rfPLnbFfMp;
      string NeBFNSFXYY;
      string qpigkiTnoX;
      string LkcIMWLozo;
      string NIOgIBfiPU;
      string heANABwiaF;
      string HQqodbBrsp;
      string HQYjKibCYj;
      string CjXTpfkPIK;
      string acOtgxQZCf;
      string zmpYNQGPDR;
      string ZsKpCXrWzx;
      string qljhPdCeCM;
      string RBzrjOsyFZ;
      string ZUMpkgSXqJ;
      string EsaFoNDIJi;
      string NbNpAXsRFm;
      string dsRYXWZsxi;
      if(DbAnRSnbWV == CjXTpfkPIK){LemrIXatDW = true;}
      else if(CjXTpfkPIK == DbAnRSnbWV){TowkPdPpUH = true;}
      if(fgocnmDYlr == acOtgxQZCf){LkoWLyGVpM = true;}
      else if(acOtgxQZCf == fgocnmDYlr){ZdHbpOlFhx = true;}
      if(rfPLnbFfMp == zmpYNQGPDR){mARDeKbBgS = true;}
      else if(zmpYNQGPDR == rfPLnbFfMp){tzjlFEdDgs = true;}
      if(NeBFNSFXYY == ZsKpCXrWzx){nJKZXinUhb = true;}
      else if(ZsKpCXrWzx == NeBFNSFXYY){CHhBRRkCrY = true;}
      if(qpigkiTnoX == qljhPdCeCM){wyOibsDuNZ = true;}
      else if(qljhPdCeCM == qpigkiTnoX){UQFXlsxftR = true;}
      if(LkcIMWLozo == RBzrjOsyFZ){PDDjuLMiNx = true;}
      else if(RBzrjOsyFZ == LkcIMWLozo){jfwDfUEJeK = true;}
      if(NIOgIBfiPU == ZUMpkgSXqJ){uZMkhBZOyb = true;}
      else if(ZUMpkgSXqJ == NIOgIBfiPU){zLJbERuFJX = true;}
      if(heANABwiaF == EsaFoNDIJi){JlnNPnkibl = true;}
      if(HQqodbBrsp == NbNpAXsRFm){GgmHCkGaeM = true;}
      if(HQYjKibCYj == dsRYXWZsxi){WEHkgWkdBa = true;}
      while(EsaFoNDIJi == heANABwiaF){cjMIbdsMzM = true;}
      while(NbNpAXsRFm == NbNpAXsRFm){GyIOIWLdVx = true;}
      while(dsRYXWZsxi == dsRYXWZsxi){NaWgZIHdSU = true;}
      if(LemrIXatDW == true){LemrIXatDW = false;}
      if(LkoWLyGVpM == true){LkoWLyGVpM = false;}
      if(mARDeKbBgS == true){mARDeKbBgS = false;}
      if(nJKZXinUhb == true){nJKZXinUhb = false;}
      if(wyOibsDuNZ == true){wyOibsDuNZ = false;}
      if(PDDjuLMiNx == true){PDDjuLMiNx = false;}
      if(uZMkhBZOyb == true){uZMkhBZOyb = false;}
      if(JlnNPnkibl == true){JlnNPnkibl = false;}
      if(GgmHCkGaeM == true){GgmHCkGaeM = false;}
      if(WEHkgWkdBa == true){WEHkgWkdBa = false;}
      if(TowkPdPpUH == true){TowkPdPpUH = false;}
      if(ZdHbpOlFhx == true){ZdHbpOlFhx = false;}
      if(tzjlFEdDgs == true){tzjlFEdDgs = false;}
      if(CHhBRRkCrY == true){CHhBRRkCrY = false;}
      if(UQFXlsxftR == true){UQFXlsxftR = false;}
      if(jfwDfUEJeK == true){jfwDfUEJeK = false;}
      if(zLJbERuFJX == true){zLJbERuFJX = false;}
      if(cjMIbdsMzM == true){cjMIbdsMzM = false;}
      if(GyIOIWLdVx == true){GyIOIWLdVx = false;}
      if(NaWgZIHdSU == true){NaWgZIHdSU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APJVGVJXRZ
{ 
  void IywiLwFqQp()
  { 
      bool NyepoVgJsI = false;
      bool LotSlbWulu = false;
      bool CxArTsrBdX = false;
      bool WusULtRwwW = false;
      bool pwXkFerPBu = false;
      bool cBDeJPxlVw = false;
      bool cffUlPuZGr = false;
      bool JZzOEGZPmo = false;
      bool AbAhuUrOLw = false;
      bool xfZztKQCyp = false;
      bool iSJIlDBnZC = false;
      bool ogzguAexZQ = false;
      bool WgOJtcAzUt = false;
      bool pWQxGhSqwq = false;
      bool TDnIGPfsDs = false;
      bool eTcgSCEzNI = false;
      bool DBSfMSPBaN = false;
      bool gnAhxSsFDe = false;
      bool xGubPWtjeD = false;
      bool cScmnRkHun = false;
      string sbCtJLOmas;
      string zpJweXxeiO;
      string rqynIqVpwT;
      string aiypyDayPI;
      string YUQQptpcUN;
      string LpPKkBdOlS;
      string oXpGRQrSya;
      string xzOapXagxO;
      string AsUiIkSnFw;
      string YLMxSAdJyZ;
      string BWdtQMaoTM;
      string axRWRwCHyg;
      string xENCBkmRHo;
      string tRhWNdPaSw;
      string JdTsUbsoeW;
      string xVLQcwJbre;
      string YJgdSIOuJn;
      string gboBXTkTgZ;
      string rxmkrXGQtQ;
      string TmimWzwoZL;
      if(sbCtJLOmas == BWdtQMaoTM){NyepoVgJsI = true;}
      else if(BWdtQMaoTM == sbCtJLOmas){iSJIlDBnZC = true;}
      if(zpJweXxeiO == axRWRwCHyg){LotSlbWulu = true;}
      else if(axRWRwCHyg == zpJweXxeiO){ogzguAexZQ = true;}
      if(rqynIqVpwT == xENCBkmRHo){CxArTsrBdX = true;}
      else if(xENCBkmRHo == rqynIqVpwT){WgOJtcAzUt = true;}
      if(aiypyDayPI == tRhWNdPaSw){WusULtRwwW = true;}
      else if(tRhWNdPaSw == aiypyDayPI){pWQxGhSqwq = true;}
      if(YUQQptpcUN == JdTsUbsoeW){pwXkFerPBu = true;}
      else if(JdTsUbsoeW == YUQQptpcUN){TDnIGPfsDs = true;}
      if(LpPKkBdOlS == xVLQcwJbre){cBDeJPxlVw = true;}
      else if(xVLQcwJbre == LpPKkBdOlS){eTcgSCEzNI = true;}
      if(oXpGRQrSya == YJgdSIOuJn){cffUlPuZGr = true;}
      else if(YJgdSIOuJn == oXpGRQrSya){DBSfMSPBaN = true;}
      if(xzOapXagxO == gboBXTkTgZ){JZzOEGZPmo = true;}
      if(AsUiIkSnFw == rxmkrXGQtQ){AbAhuUrOLw = true;}
      if(YLMxSAdJyZ == TmimWzwoZL){xfZztKQCyp = true;}
      while(gboBXTkTgZ == xzOapXagxO){gnAhxSsFDe = true;}
      while(rxmkrXGQtQ == rxmkrXGQtQ){xGubPWtjeD = true;}
      while(TmimWzwoZL == TmimWzwoZL){cScmnRkHun = true;}
      if(NyepoVgJsI == true){NyepoVgJsI = false;}
      if(LotSlbWulu == true){LotSlbWulu = false;}
      if(CxArTsrBdX == true){CxArTsrBdX = false;}
      if(WusULtRwwW == true){WusULtRwwW = false;}
      if(pwXkFerPBu == true){pwXkFerPBu = false;}
      if(cBDeJPxlVw == true){cBDeJPxlVw = false;}
      if(cffUlPuZGr == true){cffUlPuZGr = false;}
      if(JZzOEGZPmo == true){JZzOEGZPmo = false;}
      if(AbAhuUrOLw == true){AbAhuUrOLw = false;}
      if(xfZztKQCyp == true){xfZztKQCyp = false;}
      if(iSJIlDBnZC == true){iSJIlDBnZC = false;}
      if(ogzguAexZQ == true){ogzguAexZQ = false;}
      if(WgOJtcAzUt == true){WgOJtcAzUt = false;}
      if(pWQxGhSqwq == true){pWQxGhSqwq = false;}
      if(TDnIGPfsDs == true){TDnIGPfsDs = false;}
      if(eTcgSCEzNI == true){eTcgSCEzNI = false;}
      if(DBSfMSPBaN == true){DBSfMSPBaN = false;}
      if(gnAhxSsFDe == true){gnAhxSsFDe = false;}
      if(xGubPWtjeD == true){xGubPWtjeD = false;}
      if(cScmnRkHun == true){cScmnRkHun = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPDCWMUJUH
{ 
  void wXksaGdSDW()
  { 
      bool CpSlHzomGH = false;
      bool DVxOVeFhbC = false;
      bool LxVADFzznL = false;
      bool sEKfUoZjDF = false;
      bool sJjhjyFPIX = false;
      bool uQcPgETSiC = false;
      bool zoyuNyKQtf = false;
      bool EVdVJCNmPE = false;
      bool zjqPPcbuyP = false;
      bool UGAAGEKnUl = false;
      bool nnUbSZlGGe = false;
      bool qfCeDOxifk = false;
      bool VPRdLyUcPE = false;
      bool rYSdPKPPxo = false;
      bool qVnTYoEVxq = false;
      bool GaIiPXVqQU = false;
      bool FJpBmSNYOr = false;
      bool zhlpsAayFW = false;
      bool szeXyQPiNr = false;
      bool nYzbjgfmfG = false;
      string cTeOpdbCeA;
      string AWUnIUnaZq;
      string VbCCPzZQhQ;
      string aFYAgGgssB;
      string jtIidGzDBU;
      string SpsWLARbyq;
      string DKTOZuxTHB;
      string muhYHaTSYJ;
      string zVPMyjLBng;
      string oFuBxYZtIi;
      string IewzhXHUPk;
      string gyCnqhuHQo;
      string iufZMgzfah;
      string AYKpATZQdZ;
      string cqlCApCGJP;
      string dScTzMzWlA;
      string XbsgjHnMnX;
      string HddpMqJcYW;
      string esVLEhwqpm;
      string UCedCByERs;
      if(cTeOpdbCeA == IewzhXHUPk){CpSlHzomGH = true;}
      else if(IewzhXHUPk == cTeOpdbCeA){nnUbSZlGGe = true;}
      if(AWUnIUnaZq == gyCnqhuHQo){DVxOVeFhbC = true;}
      else if(gyCnqhuHQo == AWUnIUnaZq){qfCeDOxifk = true;}
      if(VbCCPzZQhQ == iufZMgzfah){LxVADFzznL = true;}
      else if(iufZMgzfah == VbCCPzZQhQ){VPRdLyUcPE = true;}
      if(aFYAgGgssB == AYKpATZQdZ){sEKfUoZjDF = true;}
      else if(AYKpATZQdZ == aFYAgGgssB){rYSdPKPPxo = true;}
      if(jtIidGzDBU == cqlCApCGJP){sJjhjyFPIX = true;}
      else if(cqlCApCGJP == jtIidGzDBU){qVnTYoEVxq = true;}
      if(SpsWLARbyq == dScTzMzWlA){uQcPgETSiC = true;}
      else if(dScTzMzWlA == SpsWLARbyq){GaIiPXVqQU = true;}
      if(DKTOZuxTHB == XbsgjHnMnX){zoyuNyKQtf = true;}
      else if(XbsgjHnMnX == DKTOZuxTHB){FJpBmSNYOr = true;}
      if(muhYHaTSYJ == HddpMqJcYW){EVdVJCNmPE = true;}
      if(zVPMyjLBng == esVLEhwqpm){zjqPPcbuyP = true;}
      if(oFuBxYZtIi == UCedCByERs){UGAAGEKnUl = true;}
      while(HddpMqJcYW == muhYHaTSYJ){zhlpsAayFW = true;}
      while(esVLEhwqpm == esVLEhwqpm){szeXyQPiNr = true;}
      while(UCedCByERs == UCedCByERs){nYzbjgfmfG = true;}
      if(CpSlHzomGH == true){CpSlHzomGH = false;}
      if(DVxOVeFhbC == true){DVxOVeFhbC = false;}
      if(LxVADFzznL == true){LxVADFzznL = false;}
      if(sEKfUoZjDF == true){sEKfUoZjDF = false;}
      if(sJjhjyFPIX == true){sJjhjyFPIX = false;}
      if(uQcPgETSiC == true){uQcPgETSiC = false;}
      if(zoyuNyKQtf == true){zoyuNyKQtf = false;}
      if(EVdVJCNmPE == true){EVdVJCNmPE = false;}
      if(zjqPPcbuyP == true){zjqPPcbuyP = false;}
      if(UGAAGEKnUl == true){UGAAGEKnUl = false;}
      if(nnUbSZlGGe == true){nnUbSZlGGe = false;}
      if(qfCeDOxifk == true){qfCeDOxifk = false;}
      if(VPRdLyUcPE == true){VPRdLyUcPE = false;}
      if(rYSdPKPPxo == true){rYSdPKPPxo = false;}
      if(qVnTYoEVxq == true){qVnTYoEVxq = false;}
      if(GaIiPXVqQU == true){GaIiPXVqQU = false;}
      if(FJpBmSNYOr == true){FJpBmSNYOr = false;}
      if(zhlpsAayFW == true){zhlpsAayFW = false;}
      if(szeXyQPiNr == true){szeXyQPiNr = false;}
      if(nYzbjgfmfG == true){nYzbjgfmfG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPYRLLUIYB
{ 
  void fzZCAJafZO()
  { 
      bool oMCjXdNMVR = false;
      bool KChfpcrWHO = false;
      bool rMtzbrUMSI = false;
      bool VGoNqzVxpU = false;
      bool TOQbJFpfea = false;
      bool IVZancSCHf = false;
      bool IBsMuEMTnp = false;
      bool GtgmtcuRpV = false;
      bool CohqzzgOZO = false;
      bool gToJMRVEgE = false;
      bool sVqnTOomfK = false;
      bool gAMkdTTBMw = false;
      bool XxsZImEWZb = false;
      bool HqkkcfxsWk = false;
      bool JthPggGEfs = false;
      bool yTqjgucReg = false;
      bool KSMECoObHy = false;
      bool VZdaldOdrb = false;
      bool gAqgdnABEh = false;
      bool CeOpaqgdMr = false;
      string QdGqXHZipK;
      string ecoDYNDBCC;
      string ZPhpGLSNnI;
      string YRuNezhwGt;
      string cwsBnKYuGx;
      string FWxpDAwQjM;
      string nMuglNhaYY;
      string fHuIZdWfBw;
      string mXGpDBTFKd;
      string DQLsFPAMPa;
      string bxWhRxaoQY;
      string dPPnZQFFcj;
      string tcPtUOuBDJ;
      string cKQaToAYXF;
      string ZeokznBWTo;
      string KuiegzgbMD;
      string BZkGwTynUj;
      string QggWJOnetg;
      string MYhOyhaltU;
      string HXLUEAshof;
      if(QdGqXHZipK == bxWhRxaoQY){oMCjXdNMVR = true;}
      else if(bxWhRxaoQY == QdGqXHZipK){sVqnTOomfK = true;}
      if(ecoDYNDBCC == dPPnZQFFcj){KChfpcrWHO = true;}
      else if(dPPnZQFFcj == ecoDYNDBCC){gAMkdTTBMw = true;}
      if(ZPhpGLSNnI == tcPtUOuBDJ){rMtzbrUMSI = true;}
      else if(tcPtUOuBDJ == ZPhpGLSNnI){XxsZImEWZb = true;}
      if(YRuNezhwGt == cKQaToAYXF){VGoNqzVxpU = true;}
      else if(cKQaToAYXF == YRuNezhwGt){HqkkcfxsWk = true;}
      if(cwsBnKYuGx == ZeokznBWTo){TOQbJFpfea = true;}
      else if(ZeokznBWTo == cwsBnKYuGx){JthPggGEfs = true;}
      if(FWxpDAwQjM == KuiegzgbMD){IVZancSCHf = true;}
      else if(KuiegzgbMD == FWxpDAwQjM){yTqjgucReg = true;}
      if(nMuglNhaYY == BZkGwTynUj){IBsMuEMTnp = true;}
      else if(BZkGwTynUj == nMuglNhaYY){KSMECoObHy = true;}
      if(fHuIZdWfBw == QggWJOnetg){GtgmtcuRpV = true;}
      if(mXGpDBTFKd == MYhOyhaltU){CohqzzgOZO = true;}
      if(DQLsFPAMPa == HXLUEAshof){gToJMRVEgE = true;}
      while(QggWJOnetg == fHuIZdWfBw){VZdaldOdrb = true;}
      while(MYhOyhaltU == MYhOyhaltU){gAqgdnABEh = true;}
      while(HXLUEAshof == HXLUEAshof){CeOpaqgdMr = true;}
      if(oMCjXdNMVR == true){oMCjXdNMVR = false;}
      if(KChfpcrWHO == true){KChfpcrWHO = false;}
      if(rMtzbrUMSI == true){rMtzbrUMSI = false;}
      if(VGoNqzVxpU == true){VGoNqzVxpU = false;}
      if(TOQbJFpfea == true){TOQbJFpfea = false;}
      if(IVZancSCHf == true){IVZancSCHf = false;}
      if(IBsMuEMTnp == true){IBsMuEMTnp = false;}
      if(GtgmtcuRpV == true){GtgmtcuRpV = false;}
      if(CohqzzgOZO == true){CohqzzgOZO = false;}
      if(gToJMRVEgE == true){gToJMRVEgE = false;}
      if(sVqnTOomfK == true){sVqnTOomfK = false;}
      if(gAMkdTTBMw == true){gAMkdTTBMw = false;}
      if(XxsZImEWZb == true){XxsZImEWZb = false;}
      if(HqkkcfxsWk == true){HqkkcfxsWk = false;}
      if(JthPggGEfs == true){JthPggGEfs = false;}
      if(yTqjgucReg == true){yTqjgucReg = false;}
      if(KSMECoObHy == true){KSMECoObHy = false;}
      if(VZdaldOdrb == true){VZdaldOdrb = false;}
      if(gAqgdnABEh == true){gAqgdnABEh = false;}
      if(CeOpaqgdMr == true){CeOpaqgdMr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORESJHNHDS
{ 
  void DaFOhwQGZx()
  { 
      bool FrhrrWXhEQ = false;
      bool roHLKPbViG = false;
      bool TWaIPaXcbS = false;
      bool JdmGoaYKkp = false;
      bool qeQUOQTcCo = false;
      bool dbRwNhRYcR = false;
      bool ztFkGNCAWi = false;
      bool qRkrPoGFty = false;
      bool GtZlnhMqsG = false;
      bool IzhTpxYfNA = false;
      bool OTGTyMqYgX = false;
      bool bLedKFTTwY = false;
      bool BKGParjRCR = false;
      bool ParsimmGnb = false;
      bool qmKUdwUDIk = false;
      bool cFiozEMqsF = false;
      bool cZWOHBTktX = false;
      bool RNeUhOAkkd = false;
      bool XfIQnKrCte = false;
      bool ZwNizQPuMc = false;
      string LDiQPCeSpL;
      string srmZCaLGCi;
      string wtXdtVFbrb;
      string RZYysUdORO;
      string tWoitQlhgz;
      string XjIhYQfEWs;
      string wCaNsTSogh;
      string xwnnoYFojc;
      string jXtsDgQpYb;
      string oYrXRqwapa;
      string ywBzBauUsz;
      string LqUtJYHhKL;
      string DbPEsXEQVx;
      string cdyIdmWuqb;
      string lwxYPxEyOs;
      string jNQdXWfwGd;
      string WeywVhrLPV;
      string BMphZHepou;
      string TGCcNONUkG;
      string GanNFGxADh;
      if(LDiQPCeSpL == ywBzBauUsz){FrhrrWXhEQ = true;}
      else if(ywBzBauUsz == LDiQPCeSpL){OTGTyMqYgX = true;}
      if(srmZCaLGCi == LqUtJYHhKL){roHLKPbViG = true;}
      else if(LqUtJYHhKL == srmZCaLGCi){bLedKFTTwY = true;}
      if(wtXdtVFbrb == DbPEsXEQVx){TWaIPaXcbS = true;}
      else if(DbPEsXEQVx == wtXdtVFbrb){BKGParjRCR = true;}
      if(RZYysUdORO == cdyIdmWuqb){JdmGoaYKkp = true;}
      else if(cdyIdmWuqb == RZYysUdORO){ParsimmGnb = true;}
      if(tWoitQlhgz == lwxYPxEyOs){qeQUOQTcCo = true;}
      else if(lwxYPxEyOs == tWoitQlhgz){qmKUdwUDIk = true;}
      if(XjIhYQfEWs == jNQdXWfwGd){dbRwNhRYcR = true;}
      else if(jNQdXWfwGd == XjIhYQfEWs){cFiozEMqsF = true;}
      if(wCaNsTSogh == WeywVhrLPV){ztFkGNCAWi = true;}
      else if(WeywVhrLPV == wCaNsTSogh){cZWOHBTktX = true;}
      if(xwnnoYFojc == BMphZHepou){qRkrPoGFty = true;}
      if(jXtsDgQpYb == TGCcNONUkG){GtZlnhMqsG = true;}
      if(oYrXRqwapa == GanNFGxADh){IzhTpxYfNA = true;}
      while(BMphZHepou == xwnnoYFojc){RNeUhOAkkd = true;}
      while(TGCcNONUkG == TGCcNONUkG){XfIQnKrCte = true;}
      while(GanNFGxADh == GanNFGxADh){ZwNizQPuMc = true;}
      if(FrhrrWXhEQ == true){FrhrrWXhEQ = false;}
      if(roHLKPbViG == true){roHLKPbViG = false;}
      if(TWaIPaXcbS == true){TWaIPaXcbS = false;}
      if(JdmGoaYKkp == true){JdmGoaYKkp = false;}
      if(qeQUOQTcCo == true){qeQUOQTcCo = false;}
      if(dbRwNhRYcR == true){dbRwNhRYcR = false;}
      if(ztFkGNCAWi == true){ztFkGNCAWi = false;}
      if(qRkrPoGFty == true){qRkrPoGFty = false;}
      if(GtZlnhMqsG == true){GtZlnhMqsG = false;}
      if(IzhTpxYfNA == true){IzhTpxYfNA = false;}
      if(OTGTyMqYgX == true){OTGTyMqYgX = false;}
      if(bLedKFTTwY == true){bLedKFTTwY = false;}
      if(BKGParjRCR == true){BKGParjRCR = false;}
      if(ParsimmGnb == true){ParsimmGnb = false;}
      if(qmKUdwUDIk == true){qmKUdwUDIk = false;}
      if(cFiozEMqsF == true){cFiozEMqsF = false;}
      if(cZWOHBTktX == true){cZWOHBTktX = false;}
      if(RNeUhOAkkd == true){RNeUhOAkkd = false;}
      if(XfIQnKrCte == true){XfIQnKrCte = false;}
      if(ZwNizQPuMc == true){ZwNizQPuMc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LXAPWYCJSS
{ 
  void ulMQtnKEFp()
  { 
      bool uNzFuzXeuG = false;
      bool uhwpsZgUOa = false;
      bool DGjCuEmxun = false;
      bool zUsTOtWqHu = false;
      bool PojlQwxnur = false;
      bool ZjUsAodxKq = false;
      bool MajHHanbby = false;
      bool DoMSLOVxky = false;
      bool GyBDNPzzTY = false;
      bool QYgQioEcdp = false;
      bool HVMwojXChl = false;
      bool TfMLkNYgsr = false;
      bool anIChdIwiV = false;
      bool JsTtqjkENd = false;
      bool qwRgFjMUfU = false;
      bool PXilOSNJOL = false;
      bool bbTLbZMRTA = false;
      bool bTSPAeWaxy = false;
      bool QmQOFlJgfY = false;
      bool WbpCBPcFFe = false;
      string DxwKLSTpgX;
      string AWjzgXIqHF;
      string wgrSWyUASH;
      string zVJsjwBeoD;
      string fKwwWLhkcZ;
      string KIXtxVEcnN;
      string xTWZXdMqOj;
      string WcCDYkjuwL;
      string PjXswqxOuN;
      string qXqbGMnWXr;
      string yqVrChFUVM;
      string lJgbxMwdcg;
      string gxwArzkaxL;
      string xNWENYOeqO;
      string kbsibhpOds;
      string QJsqLAuUAC;
      string wdXJOXlcOY;
      string yQlNuEENYK;
      string IWxDumTfsM;
      string dtdoSHEiTE;
      if(DxwKLSTpgX == yqVrChFUVM){uNzFuzXeuG = true;}
      else if(yqVrChFUVM == DxwKLSTpgX){HVMwojXChl = true;}
      if(AWjzgXIqHF == lJgbxMwdcg){uhwpsZgUOa = true;}
      else if(lJgbxMwdcg == AWjzgXIqHF){TfMLkNYgsr = true;}
      if(wgrSWyUASH == gxwArzkaxL){DGjCuEmxun = true;}
      else if(gxwArzkaxL == wgrSWyUASH){anIChdIwiV = true;}
      if(zVJsjwBeoD == xNWENYOeqO){zUsTOtWqHu = true;}
      else if(xNWENYOeqO == zVJsjwBeoD){JsTtqjkENd = true;}
      if(fKwwWLhkcZ == kbsibhpOds){PojlQwxnur = true;}
      else if(kbsibhpOds == fKwwWLhkcZ){qwRgFjMUfU = true;}
      if(KIXtxVEcnN == QJsqLAuUAC){ZjUsAodxKq = true;}
      else if(QJsqLAuUAC == KIXtxVEcnN){PXilOSNJOL = true;}
      if(xTWZXdMqOj == wdXJOXlcOY){MajHHanbby = true;}
      else if(wdXJOXlcOY == xTWZXdMqOj){bbTLbZMRTA = true;}
      if(WcCDYkjuwL == yQlNuEENYK){DoMSLOVxky = true;}
      if(PjXswqxOuN == IWxDumTfsM){GyBDNPzzTY = true;}
      if(qXqbGMnWXr == dtdoSHEiTE){QYgQioEcdp = true;}
      while(yQlNuEENYK == WcCDYkjuwL){bTSPAeWaxy = true;}
      while(IWxDumTfsM == IWxDumTfsM){QmQOFlJgfY = true;}
      while(dtdoSHEiTE == dtdoSHEiTE){WbpCBPcFFe = true;}
      if(uNzFuzXeuG == true){uNzFuzXeuG = false;}
      if(uhwpsZgUOa == true){uhwpsZgUOa = false;}
      if(DGjCuEmxun == true){DGjCuEmxun = false;}
      if(zUsTOtWqHu == true){zUsTOtWqHu = false;}
      if(PojlQwxnur == true){PojlQwxnur = false;}
      if(ZjUsAodxKq == true){ZjUsAodxKq = false;}
      if(MajHHanbby == true){MajHHanbby = false;}
      if(DoMSLOVxky == true){DoMSLOVxky = false;}
      if(GyBDNPzzTY == true){GyBDNPzzTY = false;}
      if(QYgQioEcdp == true){QYgQioEcdp = false;}
      if(HVMwojXChl == true){HVMwojXChl = false;}
      if(TfMLkNYgsr == true){TfMLkNYgsr = false;}
      if(anIChdIwiV == true){anIChdIwiV = false;}
      if(JsTtqjkENd == true){JsTtqjkENd = false;}
      if(qwRgFjMUfU == true){qwRgFjMUfU = false;}
      if(PXilOSNJOL == true){PXilOSNJOL = false;}
      if(bbTLbZMRTA == true){bbTLbZMRTA = false;}
      if(bTSPAeWaxy == true){bTSPAeWaxy = false;}
      if(QmQOFlJgfY == true){QmQOFlJgfY = false;}
      if(WbpCBPcFFe == true){WbpCBPcFFe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYDAWBJPGH
{ 
  void EbqTwMXgwG()
  { 
      bool OjPzCnPKFg = false;
      bool rDmersJonk = false;
      bool izzlOjbuRg = false;
      bool IFBumnanlH = false;
      bool JSxBXeUNKX = false;
      bool PYknePkcjR = false;
      bool MUrYYmBqqE = false;
      bool SVCfaQBxNi = false;
      bool OOktQjTNPX = false;
      bool CxDUuoZYck = false;
      bool dcVGEtVFMN = false;
      bool NmOACxiyHn = false;
      bool SmbTBURhkl = false;
      bool qcUcEkreoW = false;
      bool NOABJPhCRx = false;
      bool GbQnSqBBEj = false;
      bool bnTaWkRlwQ = false;
      bool EDIkaDlZKk = false;
      bool mOPmePMfKN = false;
      bool jqZFuYuZeY = false;
      string wDaIPzCFfJ;
      string LrFtNDXQAi;
      string nKduLyQgPC;
      string brAFxJUGYZ;
      string ZUIXnGrdFo;
      string JXmzTlYewR;
      string iVpchTqzwD;
      string hRqZJSCGHE;
      string GlaZsDEAlL;
      string jpJHqDeepT;
      string PrhBHrgMpA;
      string jSWrLwtQjd;
      string OpNkTqHiiF;
      string nXPnoNEZSB;
      string WrKkaRSRwt;
      string INtMEYewgP;
      string jxdkLMCiCx;
      string rUyiGWfbJC;
      string XpmnwZcDiQ;
      string iHrCQZNZZO;
      if(wDaIPzCFfJ == PrhBHrgMpA){OjPzCnPKFg = true;}
      else if(PrhBHrgMpA == wDaIPzCFfJ){dcVGEtVFMN = true;}
      if(LrFtNDXQAi == jSWrLwtQjd){rDmersJonk = true;}
      else if(jSWrLwtQjd == LrFtNDXQAi){NmOACxiyHn = true;}
      if(nKduLyQgPC == OpNkTqHiiF){izzlOjbuRg = true;}
      else if(OpNkTqHiiF == nKduLyQgPC){SmbTBURhkl = true;}
      if(brAFxJUGYZ == nXPnoNEZSB){IFBumnanlH = true;}
      else if(nXPnoNEZSB == brAFxJUGYZ){qcUcEkreoW = true;}
      if(ZUIXnGrdFo == WrKkaRSRwt){JSxBXeUNKX = true;}
      else if(WrKkaRSRwt == ZUIXnGrdFo){NOABJPhCRx = true;}
      if(JXmzTlYewR == INtMEYewgP){PYknePkcjR = true;}
      else if(INtMEYewgP == JXmzTlYewR){GbQnSqBBEj = true;}
      if(iVpchTqzwD == jxdkLMCiCx){MUrYYmBqqE = true;}
      else if(jxdkLMCiCx == iVpchTqzwD){bnTaWkRlwQ = true;}
      if(hRqZJSCGHE == rUyiGWfbJC){SVCfaQBxNi = true;}
      if(GlaZsDEAlL == XpmnwZcDiQ){OOktQjTNPX = true;}
      if(jpJHqDeepT == iHrCQZNZZO){CxDUuoZYck = true;}
      while(rUyiGWfbJC == hRqZJSCGHE){EDIkaDlZKk = true;}
      while(XpmnwZcDiQ == XpmnwZcDiQ){mOPmePMfKN = true;}
      while(iHrCQZNZZO == iHrCQZNZZO){jqZFuYuZeY = true;}
      if(OjPzCnPKFg == true){OjPzCnPKFg = false;}
      if(rDmersJonk == true){rDmersJonk = false;}
      if(izzlOjbuRg == true){izzlOjbuRg = false;}
      if(IFBumnanlH == true){IFBumnanlH = false;}
      if(JSxBXeUNKX == true){JSxBXeUNKX = false;}
      if(PYknePkcjR == true){PYknePkcjR = false;}
      if(MUrYYmBqqE == true){MUrYYmBqqE = false;}
      if(SVCfaQBxNi == true){SVCfaQBxNi = false;}
      if(OOktQjTNPX == true){OOktQjTNPX = false;}
      if(CxDUuoZYck == true){CxDUuoZYck = false;}
      if(dcVGEtVFMN == true){dcVGEtVFMN = false;}
      if(NmOACxiyHn == true){NmOACxiyHn = false;}
      if(SmbTBURhkl == true){SmbTBURhkl = false;}
      if(qcUcEkreoW == true){qcUcEkreoW = false;}
      if(NOABJPhCRx == true){NOABJPhCRx = false;}
      if(GbQnSqBBEj == true){GbQnSqBBEj = false;}
      if(bnTaWkRlwQ == true){bnTaWkRlwQ = false;}
      if(EDIkaDlZKk == true){EDIkaDlZKk = false;}
      if(mOPmePMfKN == true){mOPmePMfKN = false;}
      if(jqZFuYuZeY == true){jqZFuYuZeY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMJNNXURFI
{ 
  void AHixKhLtgR()
  { 
      bool kHJJVOsauA = false;
      bool ZOPTtLLWjU = false;
      bool EOsLJRQYJE = false;
      bool DrBxJfhmVO = false;
      bool JmubUPmAkC = false;
      bool sinXIVNyzE = false;
      bool xTQpxhMSJO = false;
      bool dXAUKQTQpt = false;
      bool dPnHKUEdnn = false;
      bool RinRQpWEel = false;
      bool CUpWXUiSMr = false;
      bool CwHFZhfIec = false;
      bool didVxtjhDU = false;
      bool tOlEqJZQjp = false;
      bool kkQwkUbhri = false;
      bool JNYCITpTZc = false;
      bool jBOrxmKDOQ = false;
      bool HOYoqrShkb = false;
      bool SCoTLfoiuX = false;
      bool SFqGFjWYyx = false;
      string wTEdGJbtdh;
      string oAcwxgxeKc;
      string ONsQFXOTPI;
      string rqTetSbfJk;
      string dwLTmZQTgD;
      string dZXpphZnXi;
      string tIeVpxgxCe;
      string EQVZySCYce;
      string GulLeRSdnL;
      string rnIZpVQoco;
      string sSQCyMDyqX;
      string fBKrbzVSpX;
      string eCJplQIuic;
      string BMunlmdjNS;
      string OUlPfqdQyq;
      string zyyFKqIaPg;
      string EIONWSFWGn;
      string UkFXJJQtKu;
      string mrxrdCNpcu;
      string eDUfNFFXrN;
      if(wTEdGJbtdh == sSQCyMDyqX){kHJJVOsauA = true;}
      else if(sSQCyMDyqX == wTEdGJbtdh){CUpWXUiSMr = true;}
      if(oAcwxgxeKc == fBKrbzVSpX){ZOPTtLLWjU = true;}
      else if(fBKrbzVSpX == oAcwxgxeKc){CwHFZhfIec = true;}
      if(ONsQFXOTPI == eCJplQIuic){EOsLJRQYJE = true;}
      else if(eCJplQIuic == ONsQFXOTPI){didVxtjhDU = true;}
      if(rqTetSbfJk == BMunlmdjNS){DrBxJfhmVO = true;}
      else if(BMunlmdjNS == rqTetSbfJk){tOlEqJZQjp = true;}
      if(dwLTmZQTgD == OUlPfqdQyq){JmubUPmAkC = true;}
      else if(OUlPfqdQyq == dwLTmZQTgD){kkQwkUbhri = true;}
      if(dZXpphZnXi == zyyFKqIaPg){sinXIVNyzE = true;}
      else if(zyyFKqIaPg == dZXpphZnXi){JNYCITpTZc = true;}
      if(tIeVpxgxCe == EIONWSFWGn){xTQpxhMSJO = true;}
      else if(EIONWSFWGn == tIeVpxgxCe){jBOrxmKDOQ = true;}
      if(EQVZySCYce == UkFXJJQtKu){dXAUKQTQpt = true;}
      if(GulLeRSdnL == mrxrdCNpcu){dPnHKUEdnn = true;}
      if(rnIZpVQoco == eDUfNFFXrN){RinRQpWEel = true;}
      while(UkFXJJQtKu == EQVZySCYce){HOYoqrShkb = true;}
      while(mrxrdCNpcu == mrxrdCNpcu){SCoTLfoiuX = true;}
      while(eDUfNFFXrN == eDUfNFFXrN){SFqGFjWYyx = true;}
      if(kHJJVOsauA == true){kHJJVOsauA = false;}
      if(ZOPTtLLWjU == true){ZOPTtLLWjU = false;}
      if(EOsLJRQYJE == true){EOsLJRQYJE = false;}
      if(DrBxJfhmVO == true){DrBxJfhmVO = false;}
      if(JmubUPmAkC == true){JmubUPmAkC = false;}
      if(sinXIVNyzE == true){sinXIVNyzE = false;}
      if(xTQpxhMSJO == true){xTQpxhMSJO = false;}
      if(dXAUKQTQpt == true){dXAUKQTQpt = false;}
      if(dPnHKUEdnn == true){dPnHKUEdnn = false;}
      if(RinRQpWEel == true){RinRQpWEel = false;}
      if(CUpWXUiSMr == true){CUpWXUiSMr = false;}
      if(CwHFZhfIec == true){CwHFZhfIec = false;}
      if(didVxtjhDU == true){didVxtjhDU = false;}
      if(tOlEqJZQjp == true){tOlEqJZQjp = false;}
      if(kkQwkUbhri == true){kkQwkUbhri = false;}
      if(JNYCITpTZc == true){JNYCITpTZc = false;}
      if(jBOrxmKDOQ == true){jBOrxmKDOQ = false;}
      if(HOYoqrShkb == true){HOYoqrShkb = false;}
      if(SCoTLfoiuX == true){SCoTLfoiuX = false;}
      if(SFqGFjWYyx == true){SFqGFjWYyx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSGYJNETXP
{ 
  void bLGTUonHpH()
  { 
      bool JYUHoCoKqK = false;
      bool jjJDQdDVeK = false;
      bool NpCDDHpdbz = false;
      bool qrYdmKcaVp = false;
      bool CWdszFGHiy = false;
      bool KEPGVTVQDh = false;
      bool LLiqSqKeQG = false;
      bool AbzoHqMIEx = false;
      bool AitcnlbRHS = false;
      bool nMWndqnmaH = false;
      bool ubpcxhFaye = false;
      bool GNLGgbQFCf = false;
      bool OsWxRnFLKQ = false;
      bool DZhxCYsReG = false;
      bool gBScMaAQGC = false;
      bool ZhjtsBFrKJ = false;
      bool csPhbgfODI = false;
      bool izZwzMZskq = false;
      bool nnFIqUomEA = false;
      bool SAHVcmkkAe = false;
      string UmypBIVMdc;
      string HNHNSYpVoa;
      string FAEaJmqaPd;
      string oSUKtqphZq;
      string MtaHqXikuy;
      string pREhZTiXfN;
      string RtwzmnswTb;
      string hHuyOKZwjl;
      string DFfRnWNlkZ;
      string ISBLYSybUC;
      string elRTPhVGTP;
      string tlmtKLOeKP;
      string ZGLtSOFjYw;
      string LyagGQnMBF;
      string BHSUeVeHBN;
      string ETQFcXaXAA;
      string blgWDuLGms;
      string XBdFORnpOw;
      string jyiLrrhUEi;
      string pQLAcOauRj;
      if(UmypBIVMdc == elRTPhVGTP){JYUHoCoKqK = true;}
      else if(elRTPhVGTP == UmypBIVMdc){ubpcxhFaye = true;}
      if(HNHNSYpVoa == tlmtKLOeKP){jjJDQdDVeK = true;}
      else if(tlmtKLOeKP == HNHNSYpVoa){GNLGgbQFCf = true;}
      if(FAEaJmqaPd == ZGLtSOFjYw){NpCDDHpdbz = true;}
      else if(ZGLtSOFjYw == FAEaJmqaPd){OsWxRnFLKQ = true;}
      if(oSUKtqphZq == LyagGQnMBF){qrYdmKcaVp = true;}
      else if(LyagGQnMBF == oSUKtqphZq){DZhxCYsReG = true;}
      if(MtaHqXikuy == BHSUeVeHBN){CWdszFGHiy = true;}
      else if(BHSUeVeHBN == MtaHqXikuy){gBScMaAQGC = true;}
      if(pREhZTiXfN == ETQFcXaXAA){KEPGVTVQDh = true;}
      else if(ETQFcXaXAA == pREhZTiXfN){ZhjtsBFrKJ = true;}
      if(RtwzmnswTb == blgWDuLGms){LLiqSqKeQG = true;}
      else if(blgWDuLGms == RtwzmnswTb){csPhbgfODI = true;}
      if(hHuyOKZwjl == XBdFORnpOw){AbzoHqMIEx = true;}
      if(DFfRnWNlkZ == jyiLrrhUEi){AitcnlbRHS = true;}
      if(ISBLYSybUC == pQLAcOauRj){nMWndqnmaH = true;}
      while(XBdFORnpOw == hHuyOKZwjl){izZwzMZskq = true;}
      while(jyiLrrhUEi == jyiLrrhUEi){nnFIqUomEA = true;}
      while(pQLAcOauRj == pQLAcOauRj){SAHVcmkkAe = true;}
      if(JYUHoCoKqK == true){JYUHoCoKqK = false;}
      if(jjJDQdDVeK == true){jjJDQdDVeK = false;}
      if(NpCDDHpdbz == true){NpCDDHpdbz = false;}
      if(qrYdmKcaVp == true){qrYdmKcaVp = false;}
      if(CWdszFGHiy == true){CWdszFGHiy = false;}
      if(KEPGVTVQDh == true){KEPGVTVQDh = false;}
      if(LLiqSqKeQG == true){LLiqSqKeQG = false;}
      if(AbzoHqMIEx == true){AbzoHqMIEx = false;}
      if(AitcnlbRHS == true){AitcnlbRHS = false;}
      if(nMWndqnmaH == true){nMWndqnmaH = false;}
      if(ubpcxhFaye == true){ubpcxhFaye = false;}
      if(GNLGgbQFCf == true){GNLGgbQFCf = false;}
      if(OsWxRnFLKQ == true){OsWxRnFLKQ = false;}
      if(DZhxCYsReG == true){DZhxCYsReG = false;}
      if(gBScMaAQGC == true){gBScMaAQGC = false;}
      if(ZhjtsBFrKJ == true){ZhjtsBFrKJ = false;}
      if(csPhbgfODI == true){csPhbgfODI = false;}
      if(izZwzMZskq == true){izZwzMZskq = false;}
      if(nnFIqUomEA == true){nnFIqUomEA = false;}
      if(SAHVcmkkAe == true){SAHVcmkkAe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMSEHNCZED
{ 
  void PmCUsNaTwz()
  { 
      bool bWmxiahpux = false;
      bool fxdVeNJASf = false;
      bool QqHJfQENqY = false;
      bool hkoLxUNeGJ = false;
      bool HsCBfLPdsq = false;
      bool JKbDijPdRR = false;
      bool VTyWPtIRXK = false;
      bool zdtIYXoFcT = false;
      bool BZUAOWJkcM = false;
      bool FiNnmmtelk = false;
      bool CyGiqeQSeL = false;
      bool uJBxQwzyHr = false;
      bool kWnKEQQGUk = false;
      bool dKTqRCTlIi = false;
      bool GpGQRuhQWq = false;
      bool nuWtAfJuda = false;
      bool OJxshkpJeN = false;
      bool bMpYktPWsJ = false;
      bool hAidxhmYpl = false;
      bool sYHgUwsNig = false;
      string sEBGuystpT;
      string obqHcqWXmK;
      string gsGfywUJZf;
      string TUgbXquKEQ;
      string PUPjFkPjZm;
      string lQuPqAxVHz;
      string djTKzUuPik;
      string uMSVuLcVZN;
      string fjimsDZRkX;
      string sZCFmeBFjk;
      string oABnrYyYTf;
      string XawsTsAgRw;
      string tddLrVKNiP;
      string JXloXeiutT;
      string EBxFzRdIks;
      string eUnnpLWouW;
      string OkpDVAoGVn;
      string KElxrsfYLZ;
      string qBbokoixyL;
      string IszXFSLtjz;
      if(sEBGuystpT == oABnrYyYTf){bWmxiahpux = true;}
      else if(oABnrYyYTf == sEBGuystpT){CyGiqeQSeL = true;}
      if(obqHcqWXmK == XawsTsAgRw){fxdVeNJASf = true;}
      else if(XawsTsAgRw == obqHcqWXmK){uJBxQwzyHr = true;}
      if(gsGfywUJZf == tddLrVKNiP){QqHJfQENqY = true;}
      else if(tddLrVKNiP == gsGfywUJZf){kWnKEQQGUk = true;}
      if(TUgbXquKEQ == JXloXeiutT){hkoLxUNeGJ = true;}
      else if(JXloXeiutT == TUgbXquKEQ){dKTqRCTlIi = true;}
      if(PUPjFkPjZm == EBxFzRdIks){HsCBfLPdsq = true;}
      else if(EBxFzRdIks == PUPjFkPjZm){GpGQRuhQWq = true;}
      if(lQuPqAxVHz == eUnnpLWouW){JKbDijPdRR = true;}
      else if(eUnnpLWouW == lQuPqAxVHz){nuWtAfJuda = true;}
      if(djTKzUuPik == OkpDVAoGVn){VTyWPtIRXK = true;}
      else if(OkpDVAoGVn == djTKzUuPik){OJxshkpJeN = true;}
      if(uMSVuLcVZN == KElxrsfYLZ){zdtIYXoFcT = true;}
      if(fjimsDZRkX == qBbokoixyL){BZUAOWJkcM = true;}
      if(sZCFmeBFjk == IszXFSLtjz){FiNnmmtelk = true;}
      while(KElxrsfYLZ == uMSVuLcVZN){bMpYktPWsJ = true;}
      while(qBbokoixyL == qBbokoixyL){hAidxhmYpl = true;}
      while(IszXFSLtjz == IszXFSLtjz){sYHgUwsNig = true;}
      if(bWmxiahpux == true){bWmxiahpux = false;}
      if(fxdVeNJASf == true){fxdVeNJASf = false;}
      if(QqHJfQENqY == true){QqHJfQENqY = false;}
      if(hkoLxUNeGJ == true){hkoLxUNeGJ = false;}
      if(HsCBfLPdsq == true){HsCBfLPdsq = false;}
      if(JKbDijPdRR == true){JKbDijPdRR = false;}
      if(VTyWPtIRXK == true){VTyWPtIRXK = false;}
      if(zdtIYXoFcT == true){zdtIYXoFcT = false;}
      if(BZUAOWJkcM == true){BZUAOWJkcM = false;}
      if(FiNnmmtelk == true){FiNnmmtelk = false;}
      if(CyGiqeQSeL == true){CyGiqeQSeL = false;}
      if(uJBxQwzyHr == true){uJBxQwzyHr = false;}
      if(kWnKEQQGUk == true){kWnKEQQGUk = false;}
      if(dKTqRCTlIi == true){dKTqRCTlIi = false;}
      if(GpGQRuhQWq == true){GpGQRuhQWq = false;}
      if(nuWtAfJuda == true){nuWtAfJuda = false;}
      if(OJxshkpJeN == true){OJxshkpJeN = false;}
      if(bMpYktPWsJ == true){bMpYktPWsJ = false;}
      if(hAidxhmYpl == true){hAidxhmYpl = false;}
      if(sYHgUwsNig == true){sYHgUwsNig = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RATVNWEGCF
{ 
  void HLGAfaGomY()
  { 
      bool QSbtpalxDF = false;
      bool JjUmQFbcIU = false;
      bool olEgirAzYw = false;
      bool NbssDUJfoL = false;
      bool VSdNMAPLoB = false;
      bool iQINHeNuLx = false;
      bool amYGqgpaju = false;
      bool uumwzVIqTi = false;
      bool cnJXNxTflX = false;
      bool GOTqkitWWe = false;
      bool JnbsFmcLOk = false;
      bool WWacUlcArs = false;
      bool NJoLnfbwKQ = false;
      bool bkUnYnMQRa = false;
      bool UHRBBjmpVz = false;
      bool FsdcRzzPEY = false;
      bool LgByIkBmEf = false;
      bool YMiRYGrnJE = false;
      bool skZLKiGqWY = false;
      bool owLrOnGTrQ = false;
      string mLwhpMBORk;
      string bHHxbWtFAC;
      string amcqUdsbDk;
      string MHdbCdyUnK;
      string GSmEplfwKI;
      string gHyGlAiEMM;
      string TYKgYTcety;
      string YZQpwIAXBi;
      string xwRtEEJXpC;
      string tsIbphHGfV;
      string IBCLjHqHKd;
      string AKCcOWGPcU;
      string JForDeQnzO;
      string AtreZwtGKx;
      string NBMMCjpeNT;
      string arcKMCMJHE;
      string pCIwdFSXDS;
      string czFeHHscoT;
      string nkafmIQgSW;
      string jjzFGKsQiw;
      if(mLwhpMBORk == IBCLjHqHKd){QSbtpalxDF = true;}
      else if(IBCLjHqHKd == mLwhpMBORk){JnbsFmcLOk = true;}
      if(bHHxbWtFAC == AKCcOWGPcU){JjUmQFbcIU = true;}
      else if(AKCcOWGPcU == bHHxbWtFAC){WWacUlcArs = true;}
      if(amcqUdsbDk == JForDeQnzO){olEgirAzYw = true;}
      else if(JForDeQnzO == amcqUdsbDk){NJoLnfbwKQ = true;}
      if(MHdbCdyUnK == AtreZwtGKx){NbssDUJfoL = true;}
      else if(AtreZwtGKx == MHdbCdyUnK){bkUnYnMQRa = true;}
      if(GSmEplfwKI == NBMMCjpeNT){VSdNMAPLoB = true;}
      else if(NBMMCjpeNT == GSmEplfwKI){UHRBBjmpVz = true;}
      if(gHyGlAiEMM == arcKMCMJHE){iQINHeNuLx = true;}
      else if(arcKMCMJHE == gHyGlAiEMM){FsdcRzzPEY = true;}
      if(TYKgYTcety == pCIwdFSXDS){amYGqgpaju = true;}
      else if(pCIwdFSXDS == TYKgYTcety){LgByIkBmEf = true;}
      if(YZQpwIAXBi == czFeHHscoT){uumwzVIqTi = true;}
      if(xwRtEEJXpC == nkafmIQgSW){cnJXNxTflX = true;}
      if(tsIbphHGfV == jjzFGKsQiw){GOTqkitWWe = true;}
      while(czFeHHscoT == YZQpwIAXBi){YMiRYGrnJE = true;}
      while(nkafmIQgSW == nkafmIQgSW){skZLKiGqWY = true;}
      while(jjzFGKsQiw == jjzFGKsQiw){owLrOnGTrQ = true;}
      if(QSbtpalxDF == true){QSbtpalxDF = false;}
      if(JjUmQFbcIU == true){JjUmQFbcIU = false;}
      if(olEgirAzYw == true){olEgirAzYw = false;}
      if(NbssDUJfoL == true){NbssDUJfoL = false;}
      if(VSdNMAPLoB == true){VSdNMAPLoB = false;}
      if(iQINHeNuLx == true){iQINHeNuLx = false;}
      if(amYGqgpaju == true){amYGqgpaju = false;}
      if(uumwzVIqTi == true){uumwzVIqTi = false;}
      if(cnJXNxTflX == true){cnJXNxTflX = false;}
      if(GOTqkitWWe == true){GOTqkitWWe = false;}
      if(JnbsFmcLOk == true){JnbsFmcLOk = false;}
      if(WWacUlcArs == true){WWacUlcArs = false;}
      if(NJoLnfbwKQ == true){NJoLnfbwKQ = false;}
      if(bkUnYnMQRa == true){bkUnYnMQRa = false;}
      if(UHRBBjmpVz == true){UHRBBjmpVz = false;}
      if(FsdcRzzPEY == true){FsdcRzzPEY = false;}
      if(LgByIkBmEf == true){LgByIkBmEf = false;}
      if(YMiRYGrnJE == true){YMiRYGrnJE = false;}
      if(skZLKiGqWY == true){skZLKiGqWY = false;}
      if(owLrOnGTrQ == true){owLrOnGTrQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFFJLEZYPN
{ 
  void myqlbXfqTz()
  { 
      bool IirWcPVppe = false;
      bool wWJUUBygdH = false;
      bool HWGMVoLrVW = false;
      bool rikeEpPFHe = false;
      bool OZDxcksyGe = false;
      bool CpEjGlbfBm = false;
      bool EdTSlMlePe = false;
      bool krZzrgTJjk = false;
      bool wNkqUCeBXS = false;
      bool NiETZjFjKP = false;
      bool zNhasJPFqY = false;
      bool RSwPqpscyi = false;
      bool gkGwRCmGYH = false;
      bool ajyTlheJyK = false;
      bool mZJzBtmnci = false;
      bool qckaiOGlJp = false;
      bool WJfjxgUcdI = false;
      bool LidnwHaHtW = false;
      bool OydoQyyXkX = false;
      bool bsAHncsYBT = false;
      string dEcGwFittl;
      string mnrsaRqIip;
      string bDMxHsTfBT;
      string FRucuoDCqH;
      string cWJsWgafIx;
      string jXBaYaqfzD;
      string lDrafVsPyl;
      string NoRbNFsTZZ;
      string SmXEjhPTDT;
      string xXCmUZdiMB;
      string mKgWiuGZMT;
      string hXGYkyenpy;
      string GYLenpleHn;
      string aJGXmHFBUn;
      string apHjlZQdBV;
      string torNuNzChs;
      string IaSYrXQhkd;
      string sdSCWPRbrN;
      string YHcktkQsbY;
      string HDSafAWhqN;
      if(dEcGwFittl == mKgWiuGZMT){IirWcPVppe = true;}
      else if(mKgWiuGZMT == dEcGwFittl){zNhasJPFqY = true;}
      if(mnrsaRqIip == hXGYkyenpy){wWJUUBygdH = true;}
      else if(hXGYkyenpy == mnrsaRqIip){RSwPqpscyi = true;}
      if(bDMxHsTfBT == GYLenpleHn){HWGMVoLrVW = true;}
      else if(GYLenpleHn == bDMxHsTfBT){gkGwRCmGYH = true;}
      if(FRucuoDCqH == aJGXmHFBUn){rikeEpPFHe = true;}
      else if(aJGXmHFBUn == FRucuoDCqH){ajyTlheJyK = true;}
      if(cWJsWgafIx == apHjlZQdBV){OZDxcksyGe = true;}
      else if(apHjlZQdBV == cWJsWgafIx){mZJzBtmnci = true;}
      if(jXBaYaqfzD == torNuNzChs){CpEjGlbfBm = true;}
      else if(torNuNzChs == jXBaYaqfzD){qckaiOGlJp = true;}
      if(lDrafVsPyl == IaSYrXQhkd){EdTSlMlePe = true;}
      else if(IaSYrXQhkd == lDrafVsPyl){WJfjxgUcdI = true;}
      if(NoRbNFsTZZ == sdSCWPRbrN){krZzrgTJjk = true;}
      if(SmXEjhPTDT == YHcktkQsbY){wNkqUCeBXS = true;}
      if(xXCmUZdiMB == HDSafAWhqN){NiETZjFjKP = true;}
      while(sdSCWPRbrN == NoRbNFsTZZ){LidnwHaHtW = true;}
      while(YHcktkQsbY == YHcktkQsbY){OydoQyyXkX = true;}
      while(HDSafAWhqN == HDSafAWhqN){bsAHncsYBT = true;}
      if(IirWcPVppe == true){IirWcPVppe = false;}
      if(wWJUUBygdH == true){wWJUUBygdH = false;}
      if(HWGMVoLrVW == true){HWGMVoLrVW = false;}
      if(rikeEpPFHe == true){rikeEpPFHe = false;}
      if(OZDxcksyGe == true){OZDxcksyGe = false;}
      if(CpEjGlbfBm == true){CpEjGlbfBm = false;}
      if(EdTSlMlePe == true){EdTSlMlePe = false;}
      if(krZzrgTJjk == true){krZzrgTJjk = false;}
      if(wNkqUCeBXS == true){wNkqUCeBXS = false;}
      if(NiETZjFjKP == true){NiETZjFjKP = false;}
      if(zNhasJPFqY == true){zNhasJPFqY = false;}
      if(RSwPqpscyi == true){RSwPqpscyi = false;}
      if(gkGwRCmGYH == true){gkGwRCmGYH = false;}
      if(ajyTlheJyK == true){ajyTlheJyK = false;}
      if(mZJzBtmnci == true){mZJzBtmnci = false;}
      if(qckaiOGlJp == true){qckaiOGlJp = false;}
      if(WJfjxgUcdI == true){WJfjxgUcdI = false;}
      if(LidnwHaHtW == true){LidnwHaHtW = false;}
      if(OydoQyyXkX == true){OydoQyyXkX = false;}
      if(bsAHncsYBT == true){bsAHncsYBT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOBJGLKCNA
{ 
  void HgmOuxNuhf()
  { 
      bool kxdtOrwpBD = false;
      bool DQAAsHgKJM = false;
      bool iXMkpzNqTN = false;
      bool xYQckDkDPk = false;
      bool csuidpFxnW = false;
      bool lUIRIMksDP = false;
      bool dEVmFezWPo = false;
      bool WduXioccHA = false;
      bool sQCwbcPzUX = false;
      bool RrzAHXXHcy = false;
      bool phhzAIZjhS = false;
      bool jIlDVNBYKc = false;
      bool OACqWedtQL = false;
      bool RUzIJKhDwT = false;
      bool DeRCnJFwds = false;
      bool VywAipfpbU = false;
      bool eeTWAOJctK = false;
      bool eybqZihzDN = false;
      bool YgQXoTYzYS = false;
      bool eraboXLtCZ = false;
      string DpAFSWFHFb;
      string IrAyctKHKI;
      string SszjnONCgT;
      string fARuNueHLJ;
      string ozbImSakgI;
      string jPppzJpPQE;
      string ICakuIZFjg;
      string OCwATTQqxV;
      string nbUXjQKbuE;
      string FPqHBlYqMd;
      string sVBzthSoVf;
      string szSuPghCBd;
      string yxJfbzKnzh;
      string tZdScSaVcC;
      string xUGOKFxwqU;
      string EVohfuLUWu;
      string WepmkTUzRx;
      string FLZzgcqtUW;
      string BOxedYjwmg;
      string GFyheSeSdq;
      if(DpAFSWFHFb == sVBzthSoVf){kxdtOrwpBD = true;}
      else if(sVBzthSoVf == DpAFSWFHFb){phhzAIZjhS = true;}
      if(IrAyctKHKI == szSuPghCBd){DQAAsHgKJM = true;}
      else if(szSuPghCBd == IrAyctKHKI){jIlDVNBYKc = true;}
      if(SszjnONCgT == yxJfbzKnzh){iXMkpzNqTN = true;}
      else if(yxJfbzKnzh == SszjnONCgT){OACqWedtQL = true;}
      if(fARuNueHLJ == tZdScSaVcC){xYQckDkDPk = true;}
      else if(tZdScSaVcC == fARuNueHLJ){RUzIJKhDwT = true;}
      if(ozbImSakgI == xUGOKFxwqU){csuidpFxnW = true;}
      else if(xUGOKFxwqU == ozbImSakgI){DeRCnJFwds = true;}
      if(jPppzJpPQE == EVohfuLUWu){lUIRIMksDP = true;}
      else if(EVohfuLUWu == jPppzJpPQE){VywAipfpbU = true;}
      if(ICakuIZFjg == WepmkTUzRx){dEVmFezWPo = true;}
      else if(WepmkTUzRx == ICakuIZFjg){eeTWAOJctK = true;}
      if(OCwATTQqxV == FLZzgcqtUW){WduXioccHA = true;}
      if(nbUXjQKbuE == BOxedYjwmg){sQCwbcPzUX = true;}
      if(FPqHBlYqMd == GFyheSeSdq){RrzAHXXHcy = true;}
      while(FLZzgcqtUW == OCwATTQqxV){eybqZihzDN = true;}
      while(BOxedYjwmg == BOxedYjwmg){YgQXoTYzYS = true;}
      while(GFyheSeSdq == GFyheSeSdq){eraboXLtCZ = true;}
      if(kxdtOrwpBD == true){kxdtOrwpBD = false;}
      if(DQAAsHgKJM == true){DQAAsHgKJM = false;}
      if(iXMkpzNqTN == true){iXMkpzNqTN = false;}
      if(xYQckDkDPk == true){xYQckDkDPk = false;}
      if(csuidpFxnW == true){csuidpFxnW = false;}
      if(lUIRIMksDP == true){lUIRIMksDP = false;}
      if(dEVmFezWPo == true){dEVmFezWPo = false;}
      if(WduXioccHA == true){WduXioccHA = false;}
      if(sQCwbcPzUX == true){sQCwbcPzUX = false;}
      if(RrzAHXXHcy == true){RrzAHXXHcy = false;}
      if(phhzAIZjhS == true){phhzAIZjhS = false;}
      if(jIlDVNBYKc == true){jIlDVNBYKc = false;}
      if(OACqWedtQL == true){OACqWedtQL = false;}
      if(RUzIJKhDwT == true){RUzIJKhDwT = false;}
      if(DeRCnJFwds == true){DeRCnJFwds = false;}
      if(VywAipfpbU == true){VywAipfpbU = false;}
      if(eeTWAOJctK == true){eeTWAOJctK = false;}
      if(eybqZihzDN == true){eybqZihzDN = false;}
      if(YgQXoTYzYS == true){YgQXoTYzYS = false;}
      if(eraboXLtCZ == true){eraboXLtCZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJOCBPOWQP
{ 
  void rdDOuSUAPn()
  { 
      bool ZogGGbKVYx = false;
      bool IynnSJxKan = false;
      bool pJHrCwPKzw = false;
      bool lmGSGeXUVb = false;
      bool zgHwigYqKg = false;
      bool lunelPgoEK = false;
      bool MzVcLUrVhn = false;
      bool kboynJCLIU = false;
      bool XXASJqzagp = false;
      bool xiQKPAKdkN = false;
      bool oDJVuJFoqc = false;
      bool NVfimnzCSU = false;
      bool VQnqqBLdhn = false;
      bool yXaueTOdXA = false;
      bool kJjEbaDgXb = false;
      bool AILQrXORes = false;
      bool xaHCdpujES = false;
      bool ZUeSiLfjOQ = false;
      bool ydFGmpMJCH = false;
      bool FwzdCJChZl = false;
      string uTxQHMjawW;
      string kyUGiPkZyb;
      string tQNAQBCVDI;
      string hXBBIwaGhh;
      string hcuhnFhADm;
      string QixAZdFxAG;
      string JNWmnMxSxl;
      string ndrQtQVeLL;
      string TBRQrzaAae;
      string pcGbXTGHsb;
      string HPDQylpgGJ;
      string HalnlHwGuo;
      string lwqSwLXQsa;
      string KOkjDEyARF;
      string JstRWPqRoQ;
      string WzLEpLXkUm;
      string OZmeyspBkh;
      string JuopfrCYwf;
      string TFbcEKCftr;
      string fNfdpjFOSc;
      if(uTxQHMjawW == HPDQylpgGJ){ZogGGbKVYx = true;}
      else if(HPDQylpgGJ == uTxQHMjawW){oDJVuJFoqc = true;}
      if(kyUGiPkZyb == HalnlHwGuo){IynnSJxKan = true;}
      else if(HalnlHwGuo == kyUGiPkZyb){NVfimnzCSU = true;}
      if(tQNAQBCVDI == lwqSwLXQsa){pJHrCwPKzw = true;}
      else if(lwqSwLXQsa == tQNAQBCVDI){VQnqqBLdhn = true;}
      if(hXBBIwaGhh == KOkjDEyARF){lmGSGeXUVb = true;}
      else if(KOkjDEyARF == hXBBIwaGhh){yXaueTOdXA = true;}
      if(hcuhnFhADm == JstRWPqRoQ){zgHwigYqKg = true;}
      else if(JstRWPqRoQ == hcuhnFhADm){kJjEbaDgXb = true;}
      if(QixAZdFxAG == WzLEpLXkUm){lunelPgoEK = true;}
      else if(WzLEpLXkUm == QixAZdFxAG){AILQrXORes = true;}
      if(JNWmnMxSxl == OZmeyspBkh){MzVcLUrVhn = true;}
      else if(OZmeyspBkh == JNWmnMxSxl){xaHCdpujES = true;}
      if(ndrQtQVeLL == JuopfrCYwf){kboynJCLIU = true;}
      if(TBRQrzaAae == TFbcEKCftr){XXASJqzagp = true;}
      if(pcGbXTGHsb == fNfdpjFOSc){xiQKPAKdkN = true;}
      while(JuopfrCYwf == ndrQtQVeLL){ZUeSiLfjOQ = true;}
      while(TFbcEKCftr == TFbcEKCftr){ydFGmpMJCH = true;}
      while(fNfdpjFOSc == fNfdpjFOSc){FwzdCJChZl = true;}
      if(ZogGGbKVYx == true){ZogGGbKVYx = false;}
      if(IynnSJxKan == true){IynnSJxKan = false;}
      if(pJHrCwPKzw == true){pJHrCwPKzw = false;}
      if(lmGSGeXUVb == true){lmGSGeXUVb = false;}
      if(zgHwigYqKg == true){zgHwigYqKg = false;}
      if(lunelPgoEK == true){lunelPgoEK = false;}
      if(MzVcLUrVhn == true){MzVcLUrVhn = false;}
      if(kboynJCLIU == true){kboynJCLIU = false;}
      if(XXASJqzagp == true){XXASJqzagp = false;}
      if(xiQKPAKdkN == true){xiQKPAKdkN = false;}
      if(oDJVuJFoqc == true){oDJVuJFoqc = false;}
      if(NVfimnzCSU == true){NVfimnzCSU = false;}
      if(VQnqqBLdhn == true){VQnqqBLdhn = false;}
      if(yXaueTOdXA == true){yXaueTOdXA = false;}
      if(kJjEbaDgXb == true){kJjEbaDgXb = false;}
      if(AILQrXORes == true){AILQrXORes = false;}
      if(xaHCdpujES == true){xaHCdpujES = false;}
      if(ZUeSiLfjOQ == true){ZUeSiLfjOQ = false;}
      if(ydFGmpMJCH == true){ydFGmpMJCH = false;}
      if(FwzdCJChZl == true){FwzdCJChZl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFKRTFEZPO
{ 
  void auaUlwPEcF()
  { 
      bool QCKtxszWLR = false;
      bool YEnNSBoUOO = false;
      bool XByEGMUXfz = false;
      bool pdwFAJEgmE = false;
      bool cCjRJSeFEo = false;
      bool nCylePDFnj = false;
      bool XapLbtHhMJ = false;
      bool wHgKlUQfum = false;
      bool hPSpKmfKZk = false;
      bool FysDfCLXpO = false;
      bool LwrusgVnAK = false;
      bool yXKACIHzBn = false;
      bool OxIbExOddi = false;
      bool IrpgbkXXxd = false;
      bool RqKPlhnsBX = false;
      bool tLWBANnQqu = false;
      bool RrKQBFgdXR = false;
      bool kjCWWWmroW = false;
      bool IUcFnwVogO = false;
      bool wHfBLZgsNg = false;
      string DmYgjHwGoE;
      string mFpDGqJeWT;
      string jpFrJMtyfU;
      string OBQpddOJAk;
      string SSuFHYscnD;
      string fyFugMhgXW;
      string MxZUplnAYb;
      string cAelBQuzjj;
      string SRKbnPwUIR;
      string wglcXUsaOV;
      string jsDLZfTStP;
      string RhwmDtmxfZ;
      string pSqHfwOBNf;
      string XTkOzZOyBI;
      string wcaszOjyYc;
      string hutoeQCued;
      string RRFNrxxhmd;
      string fnuXdNrxHR;
      string LPbjycZuih;
      string XSSXqdWNBC;
      if(DmYgjHwGoE == jsDLZfTStP){QCKtxszWLR = true;}
      else if(jsDLZfTStP == DmYgjHwGoE){LwrusgVnAK = true;}
      if(mFpDGqJeWT == RhwmDtmxfZ){YEnNSBoUOO = true;}
      else if(RhwmDtmxfZ == mFpDGqJeWT){yXKACIHzBn = true;}
      if(jpFrJMtyfU == pSqHfwOBNf){XByEGMUXfz = true;}
      else if(pSqHfwOBNf == jpFrJMtyfU){OxIbExOddi = true;}
      if(OBQpddOJAk == XTkOzZOyBI){pdwFAJEgmE = true;}
      else if(XTkOzZOyBI == OBQpddOJAk){IrpgbkXXxd = true;}
      if(SSuFHYscnD == wcaszOjyYc){cCjRJSeFEo = true;}
      else if(wcaszOjyYc == SSuFHYscnD){RqKPlhnsBX = true;}
      if(fyFugMhgXW == hutoeQCued){nCylePDFnj = true;}
      else if(hutoeQCued == fyFugMhgXW){tLWBANnQqu = true;}
      if(MxZUplnAYb == RRFNrxxhmd){XapLbtHhMJ = true;}
      else if(RRFNrxxhmd == MxZUplnAYb){RrKQBFgdXR = true;}
      if(cAelBQuzjj == fnuXdNrxHR){wHgKlUQfum = true;}
      if(SRKbnPwUIR == LPbjycZuih){hPSpKmfKZk = true;}
      if(wglcXUsaOV == XSSXqdWNBC){FysDfCLXpO = true;}
      while(fnuXdNrxHR == cAelBQuzjj){kjCWWWmroW = true;}
      while(LPbjycZuih == LPbjycZuih){IUcFnwVogO = true;}
      while(XSSXqdWNBC == XSSXqdWNBC){wHfBLZgsNg = true;}
      if(QCKtxszWLR == true){QCKtxszWLR = false;}
      if(YEnNSBoUOO == true){YEnNSBoUOO = false;}
      if(XByEGMUXfz == true){XByEGMUXfz = false;}
      if(pdwFAJEgmE == true){pdwFAJEgmE = false;}
      if(cCjRJSeFEo == true){cCjRJSeFEo = false;}
      if(nCylePDFnj == true){nCylePDFnj = false;}
      if(XapLbtHhMJ == true){XapLbtHhMJ = false;}
      if(wHgKlUQfum == true){wHgKlUQfum = false;}
      if(hPSpKmfKZk == true){hPSpKmfKZk = false;}
      if(FysDfCLXpO == true){FysDfCLXpO = false;}
      if(LwrusgVnAK == true){LwrusgVnAK = false;}
      if(yXKACIHzBn == true){yXKACIHzBn = false;}
      if(OxIbExOddi == true){OxIbExOddi = false;}
      if(IrpgbkXXxd == true){IrpgbkXXxd = false;}
      if(RqKPlhnsBX == true){RqKPlhnsBX = false;}
      if(tLWBANnQqu == true){tLWBANnQqu = false;}
      if(RrKQBFgdXR == true){RrKQBFgdXR = false;}
      if(kjCWWWmroW == true){kjCWWWmroW = false;}
      if(IUcFnwVogO == true){IUcFnwVogO = false;}
      if(wHfBLZgsNg == true){wHfBLZgsNg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFSJSPUWJM
{ 
  void fEEDRRICBP()
  { 
      bool penbbGCrGF = false;
      bool ayAFZjaxoZ = false;
      bool oKGsXncHDu = false;
      bool ghHGYawxcN = false;
      bool rIbaFcnOmm = false;
      bool cnthZeYuDn = false;
      bool dtoLXrqsgy = false;
      bool ncUbhgiemu = false;
      bool ANUQRsnZfs = false;
      bool CBtnjxTPCN = false;
      bool lthnyATSzs = false;
      bool wsHImPZXte = false;
      bool EQNmwmifrk = false;
      bool MSbZIFfgRR = false;
      bool ZUalxIskBU = false;
      bool XuVXIUftqL = false;
      bool QmaOgcRhzh = false;
      bool irGcFjoaon = false;
      bool tyeXMQxEQn = false;
      bool YkoFAltMFU = false;
      string hKqOBEppSm;
      string OQIeTSOVqC;
      string rRZQeNGthq;
      string ZKaAiCkAEp;
      string mqMYhwPwkl;
      string gSMylQjajn;
      string yuIbMEoHwR;
      string hORBPAEBih;
      string yKIuJHycOS;
      string SJPQrqijLd;
      string GHATDSBKhl;
      string LirBommMRF;
      string FMscyXyAJY;
      string QToEapKorq;
      string FmtcGjROaE;
      string EWSGXtOWUf;
      string TABJUqsmZz;
      string bxUazSSPVO;
      string FjZETtBhgg;
      string bnUMWEkjHP;
      if(hKqOBEppSm == GHATDSBKhl){penbbGCrGF = true;}
      else if(GHATDSBKhl == hKqOBEppSm){lthnyATSzs = true;}
      if(OQIeTSOVqC == LirBommMRF){ayAFZjaxoZ = true;}
      else if(LirBommMRF == OQIeTSOVqC){wsHImPZXte = true;}
      if(rRZQeNGthq == FMscyXyAJY){oKGsXncHDu = true;}
      else if(FMscyXyAJY == rRZQeNGthq){EQNmwmifrk = true;}
      if(ZKaAiCkAEp == QToEapKorq){ghHGYawxcN = true;}
      else if(QToEapKorq == ZKaAiCkAEp){MSbZIFfgRR = true;}
      if(mqMYhwPwkl == FmtcGjROaE){rIbaFcnOmm = true;}
      else if(FmtcGjROaE == mqMYhwPwkl){ZUalxIskBU = true;}
      if(gSMylQjajn == EWSGXtOWUf){cnthZeYuDn = true;}
      else if(EWSGXtOWUf == gSMylQjajn){XuVXIUftqL = true;}
      if(yuIbMEoHwR == TABJUqsmZz){dtoLXrqsgy = true;}
      else if(TABJUqsmZz == yuIbMEoHwR){QmaOgcRhzh = true;}
      if(hORBPAEBih == bxUazSSPVO){ncUbhgiemu = true;}
      if(yKIuJHycOS == FjZETtBhgg){ANUQRsnZfs = true;}
      if(SJPQrqijLd == bnUMWEkjHP){CBtnjxTPCN = true;}
      while(bxUazSSPVO == hORBPAEBih){irGcFjoaon = true;}
      while(FjZETtBhgg == FjZETtBhgg){tyeXMQxEQn = true;}
      while(bnUMWEkjHP == bnUMWEkjHP){YkoFAltMFU = true;}
      if(penbbGCrGF == true){penbbGCrGF = false;}
      if(ayAFZjaxoZ == true){ayAFZjaxoZ = false;}
      if(oKGsXncHDu == true){oKGsXncHDu = false;}
      if(ghHGYawxcN == true){ghHGYawxcN = false;}
      if(rIbaFcnOmm == true){rIbaFcnOmm = false;}
      if(cnthZeYuDn == true){cnthZeYuDn = false;}
      if(dtoLXrqsgy == true){dtoLXrqsgy = false;}
      if(ncUbhgiemu == true){ncUbhgiemu = false;}
      if(ANUQRsnZfs == true){ANUQRsnZfs = false;}
      if(CBtnjxTPCN == true){CBtnjxTPCN = false;}
      if(lthnyATSzs == true){lthnyATSzs = false;}
      if(wsHImPZXte == true){wsHImPZXte = false;}
      if(EQNmwmifrk == true){EQNmwmifrk = false;}
      if(MSbZIFfgRR == true){MSbZIFfgRR = false;}
      if(ZUalxIskBU == true){ZUalxIskBU = false;}
      if(XuVXIUftqL == true){XuVXIUftqL = false;}
      if(QmaOgcRhzh == true){QmaOgcRhzh = false;}
      if(irGcFjoaon == true){irGcFjoaon = false;}
      if(tyeXMQxEQn == true){tyeXMQxEQn = false;}
      if(YkoFAltMFU == true){YkoFAltMFU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYBLEUKEZZ
{ 
  void FrVznhbxQY()
  { 
      bool rEbdWhafkj = false;
      bool MglwobJsch = false;
      bool gBcPXOgeXL = false;
      bool qUHiKnTIJn = false;
      bool puRWSUBcnI = false;
      bool dayOKpbLFI = false;
      bool AwHZrqYCkB = false;
      bool IAjorljFwC = false;
      bool MEqPgPVsYT = false;
      bool MHCAmtnrdb = false;
      bool wyqmzdpJWX = false;
      bool GVPDuuEqsb = false;
      bool UfcRoBxjBx = false;
      bool xqbUGNNDQD = false;
      bool YMVAMpqzEq = false;
      bool owzCGPVZyy = false;
      bool fGHYaPtuxg = false;
      bool hBapCIJcEy = false;
      bool JyeJIBrZNp = false;
      bool rmFRWREwZx = false;
      string nlgSRKXGZd;
      string MgNOphiarz;
      string NsimMXWUGK;
      string WgXKRuWLON;
      string VFWagprjuc;
      string MzImKtCsFt;
      string nDzPGeICxt;
      string LXLdcIWIFV;
      string elYdxXYkzW;
      string rcFTZSGGTC;
      string gomBRomdJC;
      string XtmiPBdVRi;
      string GXCZBiRqEK;
      string CPnDnozXMI;
      string jtaxzyoVEY;
      string njokwJlMzh;
      string XwZzAHFjta;
      string BGJJzLxFaD;
      string sumfVRaDHe;
      string CmYdkmUbxq;
      if(nlgSRKXGZd == gomBRomdJC){rEbdWhafkj = true;}
      else if(gomBRomdJC == nlgSRKXGZd){wyqmzdpJWX = true;}
      if(MgNOphiarz == XtmiPBdVRi){MglwobJsch = true;}
      else if(XtmiPBdVRi == MgNOphiarz){GVPDuuEqsb = true;}
      if(NsimMXWUGK == GXCZBiRqEK){gBcPXOgeXL = true;}
      else if(GXCZBiRqEK == NsimMXWUGK){UfcRoBxjBx = true;}
      if(WgXKRuWLON == CPnDnozXMI){qUHiKnTIJn = true;}
      else if(CPnDnozXMI == WgXKRuWLON){xqbUGNNDQD = true;}
      if(VFWagprjuc == jtaxzyoVEY){puRWSUBcnI = true;}
      else if(jtaxzyoVEY == VFWagprjuc){YMVAMpqzEq = true;}
      if(MzImKtCsFt == njokwJlMzh){dayOKpbLFI = true;}
      else if(njokwJlMzh == MzImKtCsFt){owzCGPVZyy = true;}
      if(nDzPGeICxt == XwZzAHFjta){AwHZrqYCkB = true;}
      else if(XwZzAHFjta == nDzPGeICxt){fGHYaPtuxg = true;}
      if(LXLdcIWIFV == BGJJzLxFaD){IAjorljFwC = true;}
      if(elYdxXYkzW == sumfVRaDHe){MEqPgPVsYT = true;}
      if(rcFTZSGGTC == CmYdkmUbxq){MHCAmtnrdb = true;}
      while(BGJJzLxFaD == LXLdcIWIFV){hBapCIJcEy = true;}
      while(sumfVRaDHe == sumfVRaDHe){JyeJIBrZNp = true;}
      while(CmYdkmUbxq == CmYdkmUbxq){rmFRWREwZx = true;}
      if(rEbdWhafkj == true){rEbdWhafkj = false;}
      if(MglwobJsch == true){MglwobJsch = false;}
      if(gBcPXOgeXL == true){gBcPXOgeXL = false;}
      if(qUHiKnTIJn == true){qUHiKnTIJn = false;}
      if(puRWSUBcnI == true){puRWSUBcnI = false;}
      if(dayOKpbLFI == true){dayOKpbLFI = false;}
      if(AwHZrqYCkB == true){AwHZrqYCkB = false;}
      if(IAjorljFwC == true){IAjorljFwC = false;}
      if(MEqPgPVsYT == true){MEqPgPVsYT = false;}
      if(MHCAmtnrdb == true){MHCAmtnrdb = false;}
      if(wyqmzdpJWX == true){wyqmzdpJWX = false;}
      if(GVPDuuEqsb == true){GVPDuuEqsb = false;}
      if(UfcRoBxjBx == true){UfcRoBxjBx = false;}
      if(xqbUGNNDQD == true){xqbUGNNDQD = false;}
      if(YMVAMpqzEq == true){YMVAMpqzEq = false;}
      if(owzCGPVZyy == true){owzCGPVZyy = false;}
      if(fGHYaPtuxg == true){fGHYaPtuxg = false;}
      if(hBapCIJcEy == true){hBapCIJcEy = false;}
      if(JyeJIBrZNp == true){JyeJIBrZNp = false;}
      if(rmFRWREwZx == true){rmFRWREwZx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJSQTEIOOT
{ 
  void IgniGDyeOc()
  { 
      bool YMYKZSBnoT = false;
      bool zwqqiQpQLm = false;
      bool QBBCPPUaZY = false;
      bool yhZBWixZSP = false;
      bool ybShWEyrKc = false;
      bool uJgYWXLWuK = false;
      bool xaNPVRVpUA = false;
      bool TPxunoiTeK = false;
      bool RcPwdoABdy = false;
      bool XaeISXNCLF = false;
      bool hIWJJeLkjh = false;
      bool nqqksTKRlf = false;
      bool QULVcskncQ = false;
      bool afHZbJGGly = false;
      bool cOQuJfisPz = false;
      bool MwQfnNwAgQ = false;
      bool tWISHIjQIi = false;
      bool MEemDCEPLx = false;
      bool JqYdEdPakO = false;
      bool MFYVEFGxnB = false;
      string eHWkloCdmw;
      string PoFEVdYbgT;
      string FoPcacwlXs;
      string bloGQqGglA;
      string PTFofnUfwL;
      string BcQDwoqtJJ;
      string rQFtUdzyme;
      string WrogEkjawl;
      string HPoMqzUlKa;
      string zMWcHyOLTC;
      string nWsRnJmjzK;
      string FQxXBbbrCV;
      string JNmLeKVMYF;
      string WYGtxkWWXh;
      string LjlAViOzaf;
      string WVIyraigmd;
      string maKsngJCZQ;
      string FEUUJYampu;
      string uWkshAPHBW;
      string BoistkZsMn;
      if(eHWkloCdmw == nWsRnJmjzK){YMYKZSBnoT = true;}
      else if(nWsRnJmjzK == eHWkloCdmw){hIWJJeLkjh = true;}
      if(PoFEVdYbgT == FQxXBbbrCV){zwqqiQpQLm = true;}
      else if(FQxXBbbrCV == PoFEVdYbgT){nqqksTKRlf = true;}
      if(FoPcacwlXs == JNmLeKVMYF){QBBCPPUaZY = true;}
      else if(JNmLeKVMYF == FoPcacwlXs){QULVcskncQ = true;}
      if(bloGQqGglA == WYGtxkWWXh){yhZBWixZSP = true;}
      else if(WYGtxkWWXh == bloGQqGglA){afHZbJGGly = true;}
      if(PTFofnUfwL == LjlAViOzaf){ybShWEyrKc = true;}
      else if(LjlAViOzaf == PTFofnUfwL){cOQuJfisPz = true;}
      if(BcQDwoqtJJ == WVIyraigmd){uJgYWXLWuK = true;}
      else if(WVIyraigmd == BcQDwoqtJJ){MwQfnNwAgQ = true;}
      if(rQFtUdzyme == maKsngJCZQ){xaNPVRVpUA = true;}
      else if(maKsngJCZQ == rQFtUdzyme){tWISHIjQIi = true;}
      if(WrogEkjawl == FEUUJYampu){TPxunoiTeK = true;}
      if(HPoMqzUlKa == uWkshAPHBW){RcPwdoABdy = true;}
      if(zMWcHyOLTC == BoistkZsMn){XaeISXNCLF = true;}
      while(FEUUJYampu == WrogEkjawl){MEemDCEPLx = true;}
      while(uWkshAPHBW == uWkshAPHBW){JqYdEdPakO = true;}
      while(BoistkZsMn == BoistkZsMn){MFYVEFGxnB = true;}
      if(YMYKZSBnoT == true){YMYKZSBnoT = false;}
      if(zwqqiQpQLm == true){zwqqiQpQLm = false;}
      if(QBBCPPUaZY == true){QBBCPPUaZY = false;}
      if(yhZBWixZSP == true){yhZBWixZSP = false;}
      if(ybShWEyrKc == true){ybShWEyrKc = false;}
      if(uJgYWXLWuK == true){uJgYWXLWuK = false;}
      if(xaNPVRVpUA == true){xaNPVRVpUA = false;}
      if(TPxunoiTeK == true){TPxunoiTeK = false;}
      if(RcPwdoABdy == true){RcPwdoABdy = false;}
      if(XaeISXNCLF == true){XaeISXNCLF = false;}
      if(hIWJJeLkjh == true){hIWJJeLkjh = false;}
      if(nqqksTKRlf == true){nqqksTKRlf = false;}
      if(QULVcskncQ == true){QULVcskncQ = false;}
      if(afHZbJGGly == true){afHZbJGGly = false;}
      if(cOQuJfisPz == true){cOQuJfisPz = false;}
      if(MwQfnNwAgQ == true){MwQfnNwAgQ = false;}
      if(tWISHIjQIi == true){tWISHIjQIi = false;}
      if(MEemDCEPLx == true){MEemDCEPLx = false;}
      if(JqYdEdPakO == true){JqYdEdPakO = false;}
      if(MFYVEFGxnB == true){MFYVEFGxnB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WBBBXLBLTW
{ 
  void ygYDTeZfrr()
  { 
      bool VSokHijcak = false;
      bool BOYUQBdANi = false;
      bool aUrTGMLZKE = false;
      bool kLqOaiXZOe = false;
      bool JBEybFsXDa = false;
      bool jAtKzBZUet = false;
      bool XKSVAoWKtg = false;
      bool dDkhZZPtrA = false;
      bool TmWiUjQgOY = false;
      bool ICuTGyiiyl = false;
      bool ihdWxfPMjZ = false;
      bool lfceajmiAP = false;
      bool YpuUXaIRaa = false;
      bool pgwGRkJAlo = false;
      bool UEwolcZPsW = false;
      bool KzhhNrmIyV = false;
      bool XykIiFiWNo = false;
      bool amxLuTtGit = false;
      bool BrXEQqyNrY = false;
      bool yBBQRWTmGf = false;
      string cGVAjrIjsr;
      string PVrphooGsL;
      string georbOMAzF;
      string HzyKhPKGbg;
      string IwkAAAnsEu;
      string xqsglxQcXU;
      string fIjnkQXgHS;
      string ehdLCjtorb;
      string aSuDHPFQYk;
      string ygiGBALxOi;
      string cHklQOMgeB;
      string DakwtNMgfU;
      string KGHWTyzXKC;
      string YwZIzTgJmr;
      string CXlWgWulMm;
      string meQtXVzORS;
      string PoWccGAcxa;
      string fDtnSmUkox;
      string CNLWOsefjc;
      string USrTcNBIsa;
      if(cGVAjrIjsr == cHklQOMgeB){VSokHijcak = true;}
      else if(cHklQOMgeB == cGVAjrIjsr){ihdWxfPMjZ = true;}
      if(PVrphooGsL == DakwtNMgfU){BOYUQBdANi = true;}
      else if(DakwtNMgfU == PVrphooGsL){lfceajmiAP = true;}
      if(georbOMAzF == KGHWTyzXKC){aUrTGMLZKE = true;}
      else if(KGHWTyzXKC == georbOMAzF){YpuUXaIRaa = true;}
      if(HzyKhPKGbg == YwZIzTgJmr){kLqOaiXZOe = true;}
      else if(YwZIzTgJmr == HzyKhPKGbg){pgwGRkJAlo = true;}
      if(IwkAAAnsEu == CXlWgWulMm){JBEybFsXDa = true;}
      else if(CXlWgWulMm == IwkAAAnsEu){UEwolcZPsW = true;}
      if(xqsglxQcXU == meQtXVzORS){jAtKzBZUet = true;}
      else if(meQtXVzORS == xqsglxQcXU){KzhhNrmIyV = true;}
      if(fIjnkQXgHS == PoWccGAcxa){XKSVAoWKtg = true;}
      else if(PoWccGAcxa == fIjnkQXgHS){XykIiFiWNo = true;}
      if(ehdLCjtorb == fDtnSmUkox){dDkhZZPtrA = true;}
      if(aSuDHPFQYk == CNLWOsefjc){TmWiUjQgOY = true;}
      if(ygiGBALxOi == USrTcNBIsa){ICuTGyiiyl = true;}
      while(fDtnSmUkox == ehdLCjtorb){amxLuTtGit = true;}
      while(CNLWOsefjc == CNLWOsefjc){BrXEQqyNrY = true;}
      while(USrTcNBIsa == USrTcNBIsa){yBBQRWTmGf = true;}
      if(VSokHijcak == true){VSokHijcak = false;}
      if(BOYUQBdANi == true){BOYUQBdANi = false;}
      if(aUrTGMLZKE == true){aUrTGMLZKE = false;}
      if(kLqOaiXZOe == true){kLqOaiXZOe = false;}
      if(JBEybFsXDa == true){JBEybFsXDa = false;}
      if(jAtKzBZUet == true){jAtKzBZUet = false;}
      if(XKSVAoWKtg == true){XKSVAoWKtg = false;}
      if(dDkhZZPtrA == true){dDkhZZPtrA = false;}
      if(TmWiUjQgOY == true){TmWiUjQgOY = false;}
      if(ICuTGyiiyl == true){ICuTGyiiyl = false;}
      if(ihdWxfPMjZ == true){ihdWxfPMjZ = false;}
      if(lfceajmiAP == true){lfceajmiAP = false;}
      if(YpuUXaIRaa == true){YpuUXaIRaa = false;}
      if(pgwGRkJAlo == true){pgwGRkJAlo = false;}
      if(UEwolcZPsW == true){UEwolcZPsW = false;}
      if(KzhhNrmIyV == true){KzhhNrmIyV = false;}
      if(XykIiFiWNo == true){XykIiFiWNo = false;}
      if(amxLuTtGit == true){amxLuTtGit = false;}
      if(BrXEQqyNrY == true){BrXEQqyNrY = false;}
      if(yBBQRWTmGf == true){yBBQRWTmGf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWTTBNALAJ
{ 
  void Kjewlrjzfn()
  { 
      bool HUSTbMjoyf = false;
      bool oennHZMiRa = false;
      bool zLCCZVmPRm = false;
      bool qyxXPQdNsp = false;
      bool ekxgxMEZVp = false;
      bool OgsKnwRPtF = false;
      bool ZUXKoqhQXp = false;
      bool uypauONUFM = false;
      bool QNtaXJEljT = false;
      bool yOTmPKNmrG = false;
      bool enBeuQqSPY = false;
      bool hxKgoMZwle = false;
      bool mugErfeCLj = false;
      bool BZbyhcLPfH = false;
      bool SkWKkBElyD = false;
      bool kQANTiHxmO = false;
      bool knHfXIULzL = false;
      bool AJPdLBYWSp = false;
      bool bsDHzjYOdy = false;
      bool VNcRWddqlc = false;
      string fIdTmNocSu;
      string XRNFdJXpZs;
      string kSfuUhrpah;
      string YKKmxJkiNR;
      string mwcVduBdSn;
      string RoYrYMbizE;
      string UyCkVNHZHT;
      string XobIFnoKQY;
      string gNXlPjkRNj;
      string gCiIwntrAP;
      string naWyPcNQlk;
      string WRRaXGZPUl;
      string boMXmVFSLR;
      string txKBkGqYWm;
      string WUfcMPkIkp;
      string NdWNmyOyLs;
      string WtEUqZHPoR;
      string OBshPHJiKX;
      string kxhUDPZwNl;
      string qsNcPbQLlm;
      if(fIdTmNocSu == naWyPcNQlk){HUSTbMjoyf = true;}
      else if(naWyPcNQlk == fIdTmNocSu){enBeuQqSPY = true;}
      if(XRNFdJXpZs == WRRaXGZPUl){oennHZMiRa = true;}
      else if(WRRaXGZPUl == XRNFdJXpZs){hxKgoMZwle = true;}
      if(kSfuUhrpah == boMXmVFSLR){zLCCZVmPRm = true;}
      else if(boMXmVFSLR == kSfuUhrpah){mugErfeCLj = true;}
      if(YKKmxJkiNR == txKBkGqYWm){qyxXPQdNsp = true;}
      else if(txKBkGqYWm == YKKmxJkiNR){BZbyhcLPfH = true;}
      if(mwcVduBdSn == WUfcMPkIkp){ekxgxMEZVp = true;}
      else if(WUfcMPkIkp == mwcVduBdSn){SkWKkBElyD = true;}
      if(RoYrYMbizE == NdWNmyOyLs){OgsKnwRPtF = true;}
      else if(NdWNmyOyLs == RoYrYMbizE){kQANTiHxmO = true;}
      if(UyCkVNHZHT == WtEUqZHPoR){ZUXKoqhQXp = true;}
      else if(WtEUqZHPoR == UyCkVNHZHT){knHfXIULzL = true;}
      if(XobIFnoKQY == OBshPHJiKX){uypauONUFM = true;}
      if(gNXlPjkRNj == kxhUDPZwNl){QNtaXJEljT = true;}
      if(gCiIwntrAP == qsNcPbQLlm){yOTmPKNmrG = true;}
      while(OBshPHJiKX == XobIFnoKQY){AJPdLBYWSp = true;}
      while(kxhUDPZwNl == kxhUDPZwNl){bsDHzjYOdy = true;}
      while(qsNcPbQLlm == qsNcPbQLlm){VNcRWddqlc = true;}
      if(HUSTbMjoyf == true){HUSTbMjoyf = false;}
      if(oennHZMiRa == true){oennHZMiRa = false;}
      if(zLCCZVmPRm == true){zLCCZVmPRm = false;}
      if(qyxXPQdNsp == true){qyxXPQdNsp = false;}
      if(ekxgxMEZVp == true){ekxgxMEZVp = false;}
      if(OgsKnwRPtF == true){OgsKnwRPtF = false;}
      if(ZUXKoqhQXp == true){ZUXKoqhQXp = false;}
      if(uypauONUFM == true){uypauONUFM = false;}
      if(QNtaXJEljT == true){QNtaXJEljT = false;}
      if(yOTmPKNmrG == true){yOTmPKNmrG = false;}
      if(enBeuQqSPY == true){enBeuQqSPY = false;}
      if(hxKgoMZwle == true){hxKgoMZwle = false;}
      if(mugErfeCLj == true){mugErfeCLj = false;}
      if(BZbyhcLPfH == true){BZbyhcLPfH = false;}
      if(SkWKkBElyD == true){SkWKkBElyD = false;}
      if(kQANTiHxmO == true){kQANTiHxmO = false;}
      if(knHfXIULzL == true){knHfXIULzL = false;}
      if(AJPdLBYWSp == true){AJPdLBYWSp = false;}
      if(bsDHzjYOdy == true){bsDHzjYOdy = false;}
      if(VNcRWddqlc == true){VNcRWddqlc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFZBZNWUWF
{ 
  void mTuTtIRXkn()
  { 
      bool nsBJGDyMpN = false;
      bool MzsdSaIUnY = false;
      bool qSuCcJEfpR = false;
      bool mkjrezUYJS = false;
      bool JIDnygYUJu = false;
      bool TXwECUyzgw = false;
      bool zSVYabPBzS = false;
      bool FiKVPiPGDu = false;
      bool kiVuxPneoJ = false;
      bool BVrMSpmeNW = false;
      bool RWVqokMZoT = false;
      bool FqukLPwZaL = false;
      bool mjMoQjqyCY = false;
      bool wksgdNMdGM = false;
      bool COpVDJZGBD = false;
      bool sMDCigKfZE = false;
      bool sOXQXUyOHx = false;
      bool DSTOIYtpkG = false;
      bool Kjwzeihqxx = false;
      bool DfDBSmpZxi = false;
      string khUyjuIhUS;
      string bGKWZwhgLG;
      string JfMbuAzszp;
      string lEGcQNcZHE;
      string WnigaATceP;
      string pUpXTEVsCj;
      string wPhefWAhFM;
      string THZHjVxeAu;
      string fVOjAQNiIM;
      string rjWWIHFDAD;
      string AlXRuhuimx;
      string GpsHDZAxeP;
      string JRYrUjkCyc;
      string QtdwttywoS;
      string VduKGBpOTh;
      string GHYktiNexL;
      string wrkKgMMxNJ;
      string bDIMtfVNlT;
      string sViPVIUsCL;
      string gSzcVcrkdt;
      if(khUyjuIhUS == AlXRuhuimx){nsBJGDyMpN = true;}
      else if(AlXRuhuimx == khUyjuIhUS){RWVqokMZoT = true;}
      if(bGKWZwhgLG == GpsHDZAxeP){MzsdSaIUnY = true;}
      else if(GpsHDZAxeP == bGKWZwhgLG){FqukLPwZaL = true;}
      if(JfMbuAzszp == JRYrUjkCyc){qSuCcJEfpR = true;}
      else if(JRYrUjkCyc == JfMbuAzszp){mjMoQjqyCY = true;}
      if(lEGcQNcZHE == QtdwttywoS){mkjrezUYJS = true;}
      else if(QtdwttywoS == lEGcQNcZHE){wksgdNMdGM = true;}
      if(WnigaATceP == VduKGBpOTh){JIDnygYUJu = true;}
      else if(VduKGBpOTh == WnigaATceP){COpVDJZGBD = true;}
      if(pUpXTEVsCj == GHYktiNexL){TXwECUyzgw = true;}
      else if(GHYktiNexL == pUpXTEVsCj){sMDCigKfZE = true;}
      if(wPhefWAhFM == wrkKgMMxNJ){zSVYabPBzS = true;}
      else if(wrkKgMMxNJ == wPhefWAhFM){sOXQXUyOHx = true;}
      if(THZHjVxeAu == bDIMtfVNlT){FiKVPiPGDu = true;}
      if(fVOjAQNiIM == sViPVIUsCL){kiVuxPneoJ = true;}
      if(rjWWIHFDAD == gSzcVcrkdt){BVrMSpmeNW = true;}
      while(bDIMtfVNlT == THZHjVxeAu){DSTOIYtpkG = true;}
      while(sViPVIUsCL == sViPVIUsCL){Kjwzeihqxx = true;}
      while(gSzcVcrkdt == gSzcVcrkdt){DfDBSmpZxi = true;}
      if(nsBJGDyMpN == true){nsBJGDyMpN = false;}
      if(MzsdSaIUnY == true){MzsdSaIUnY = false;}
      if(qSuCcJEfpR == true){qSuCcJEfpR = false;}
      if(mkjrezUYJS == true){mkjrezUYJS = false;}
      if(JIDnygYUJu == true){JIDnygYUJu = false;}
      if(TXwECUyzgw == true){TXwECUyzgw = false;}
      if(zSVYabPBzS == true){zSVYabPBzS = false;}
      if(FiKVPiPGDu == true){FiKVPiPGDu = false;}
      if(kiVuxPneoJ == true){kiVuxPneoJ = false;}
      if(BVrMSpmeNW == true){BVrMSpmeNW = false;}
      if(RWVqokMZoT == true){RWVqokMZoT = false;}
      if(FqukLPwZaL == true){FqukLPwZaL = false;}
      if(mjMoQjqyCY == true){mjMoQjqyCY = false;}
      if(wksgdNMdGM == true){wksgdNMdGM = false;}
      if(COpVDJZGBD == true){COpVDJZGBD = false;}
      if(sMDCigKfZE == true){sMDCigKfZE = false;}
      if(sOXQXUyOHx == true){sOXQXUyOHx = false;}
      if(DSTOIYtpkG == true){DSTOIYtpkG = false;}
      if(Kjwzeihqxx == true){Kjwzeihqxx = false;}
      if(DfDBSmpZxi == true){DfDBSmpZxi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPOEQEXMOD
{ 
  void RmCisoVFlL()
  { 
      bool FLEGOsLhOF = false;
      bool SQBuWTehYr = false;
      bool twRRdGzoMM = false;
      bool CxAhSTIaIs = false;
      bool kMjlWRQBiB = false;
      bool YItbnItlcH = false;
      bool sVUCCUQSbD = false;
      bool KEYeGgMetL = false;
      bool pxFLnsDXtJ = false;
      bool ZWyAzPrhjB = false;
      bool AxYfpTjOVG = false;
      bool wOrQRuQJOI = false;
      bool RrYRdnGYfq = false;
      bool odusLrYZUT = false;
      bool JoCmNKdhiD = false;
      bool yiTajHYGCC = false;
      bool NKhdRSTyEZ = false;
      bool WpntycpkES = false;
      bool JYobrGKTID = false;
      bool SRWRGyGXUu = false;
      string AhAQmMdJQw;
      string hjppuXmHFC;
      string ytPUjZLGob;
      string kgbLdsAXKy;
      string ZhlXojrSua;
      string UIWNJGSefM;
      string BXUoKAHeLB;
      string WPwHbQHreA;
      string grKOGcKOBW;
      string aVqxwBMxNn;
      string bNHtEFLOkr;
      string zZAfeJMFhh;
      string oscoZBYzKa;
      string DJepYTjQJB;
      string QucIXBULRm;
      string oHOfzikSTD;
      string gMEKnouJHL;
      string YwwgQsPTQY;
      string fNgWlwuzqo;
      string hRwGUEqSTh;
      if(AhAQmMdJQw == bNHtEFLOkr){FLEGOsLhOF = true;}
      else if(bNHtEFLOkr == AhAQmMdJQw){AxYfpTjOVG = true;}
      if(hjppuXmHFC == zZAfeJMFhh){SQBuWTehYr = true;}
      else if(zZAfeJMFhh == hjppuXmHFC){wOrQRuQJOI = true;}
      if(ytPUjZLGob == oscoZBYzKa){twRRdGzoMM = true;}
      else if(oscoZBYzKa == ytPUjZLGob){RrYRdnGYfq = true;}
      if(kgbLdsAXKy == DJepYTjQJB){CxAhSTIaIs = true;}
      else if(DJepYTjQJB == kgbLdsAXKy){odusLrYZUT = true;}
      if(ZhlXojrSua == QucIXBULRm){kMjlWRQBiB = true;}
      else if(QucIXBULRm == ZhlXojrSua){JoCmNKdhiD = true;}
      if(UIWNJGSefM == oHOfzikSTD){YItbnItlcH = true;}
      else if(oHOfzikSTD == UIWNJGSefM){yiTajHYGCC = true;}
      if(BXUoKAHeLB == gMEKnouJHL){sVUCCUQSbD = true;}
      else if(gMEKnouJHL == BXUoKAHeLB){NKhdRSTyEZ = true;}
      if(WPwHbQHreA == YwwgQsPTQY){KEYeGgMetL = true;}
      if(grKOGcKOBW == fNgWlwuzqo){pxFLnsDXtJ = true;}
      if(aVqxwBMxNn == hRwGUEqSTh){ZWyAzPrhjB = true;}
      while(YwwgQsPTQY == WPwHbQHreA){WpntycpkES = true;}
      while(fNgWlwuzqo == fNgWlwuzqo){JYobrGKTID = true;}
      while(hRwGUEqSTh == hRwGUEqSTh){SRWRGyGXUu = true;}
      if(FLEGOsLhOF == true){FLEGOsLhOF = false;}
      if(SQBuWTehYr == true){SQBuWTehYr = false;}
      if(twRRdGzoMM == true){twRRdGzoMM = false;}
      if(CxAhSTIaIs == true){CxAhSTIaIs = false;}
      if(kMjlWRQBiB == true){kMjlWRQBiB = false;}
      if(YItbnItlcH == true){YItbnItlcH = false;}
      if(sVUCCUQSbD == true){sVUCCUQSbD = false;}
      if(KEYeGgMetL == true){KEYeGgMetL = false;}
      if(pxFLnsDXtJ == true){pxFLnsDXtJ = false;}
      if(ZWyAzPrhjB == true){ZWyAzPrhjB = false;}
      if(AxYfpTjOVG == true){AxYfpTjOVG = false;}
      if(wOrQRuQJOI == true){wOrQRuQJOI = false;}
      if(RrYRdnGYfq == true){RrYRdnGYfq = false;}
      if(odusLrYZUT == true){odusLrYZUT = false;}
      if(JoCmNKdhiD == true){JoCmNKdhiD = false;}
      if(yiTajHYGCC == true){yiTajHYGCC = false;}
      if(NKhdRSTyEZ == true){NKhdRSTyEZ = false;}
      if(WpntycpkES == true){WpntycpkES = false;}
      if(JYobrGKTID == true){JYobrGKTID = false;}
      if(SRWRGyGXUu == true){SRWRGyGXUu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWTEEJZRJI
{ 
  void yzstVkqrBa()
  { 
      bool CHKGEGTHFq = false;
      bool yCZFjjbnsh = false;
      bool ibFMkWjLGY = false;
      bool ZAXcqxdLPH = false;
      bool BdfosMFMHa = false;
      bool KdsUaaCyVh = false;
      bool WIAgRydxNl = false;
      bool FQXlfFwQSY = false;
      bool QWDfOuHDCQ = false;
      bool ufphksdzWu = false;
      bool iIzUUtGHnU = false;
      bool dlewQzEURW = false;
      bool pZuwqZapAm = false;
      bool bxsWpIWiKU = false;
      bool oAPgmIAsRk = false;
      bool nIgAFINCcu = false;
      bool SPGBsfsIGH = false;
      bool cVKxgoKNJh = false;
      bool YgYOzSQrQg = false;
      bool tTFOBYtOmG = false;
      string uwSMoHiVHh;
      string EMnMKMoPEa;
      string WbQybukkKs;
      string paEDgOQjrY;
      string aToCfctMGl;
      string gpPeATfUjs;
      string VyKNrdHjfu;
      string wEXfzCmNSz;
      string BYdYMzKZDM;
      string iwAyDcJaKC;
      string UJfLpcSjex;
      string gRCjrwTlBr;
      string ShgSLzEYbW;
      string sLDPeqsRhi;
      string gatGfRtPGH;
      string IXZRilcNzp;
      string XtIHDVOlFA;
      string CCDRLrmamt;
      string FnRUOVllfr;
      string OfRrKlRlCK;
      if(uwSMoHiVHh == UJfLpcSjex){CHKGEGTHFq = true;}
      else if(UJfLpcSjex == uwSMoHiVHh){iIzUUtGHnU = true;}
      if(EMnMKMoPEa == gRCjrwTlBr){yCZFjjbnsh = true;}
      else if(gRCjrwTlBr == EMnMKMoPEa){dlewQzEURW = true;}
      if(WbQybukkKs == ShgSLzEYbW){ibFMkWjLGY = true;}
      else if(ShgSLzEYbW == WbQybukkKs){pZuwqZapAm = true;}
      if(paEDgOQjrY == sLDPeqsRhi){ZAXcqxdLPH = true;}
      else if(sLDPeqsRhi == paEDgOQjrY){bxsWpIWiKU = true;}
      if(aToCfctMGl == gatGfRtPGH){BdfosMFMHa = true;}
      else if(gatGfRtPGH == aToCfctMGl){oAPgmIAsRk = true;}
      if(gpPeATfUjs == IXZRilcNzp){KdsUaaCyVh = true;}
      else if(IXZRilcNzp == gpPeATfUjs){nIgAFINCcu = true;}
      if(VyKNrdHjfu == XtIHDVOlFA){WIAgRydxNl = true;}
      else if(XtIHDVOlFA == VyKNrdHjfu){SPGBsfsIGH = true;}
      if(wEXfzCmNSz == CCDRLrmamt){FQXlfFwQSY = true;}
      if(BYdYMzKZDM == FnRUOVllfr){QWDfOuHDCQ = true;}
      if(iwAyDcJaKC == OfRrKlRlCK){ufphksdzWu = true;}
      while(CCDRLrmamt == wEXfzCmNSz){cVKxgoKNJh = true;}
      while(FnRUOVllfr == FnRUOVllfr){YgYOzSQrQg = true;}
      while(OfRrKlRlCK == OfRrKlRlCK){tTFOBYtOmG = true;}
      if(CHKGEGTHFq == true){CHKGEGTHFq = false;}
      if(yCZFjjbnsh == true){yCZFjjbnsh = false;}
      if(ibFMkWjLGY == true){ibFMkWjLGY = false;}
      if(ZAXcqxdLPH == true){ZAXcqxdLPH = false;}
      if(BdfosMFMHa == true){BdfosMFMHa = false;}
      if(KdsUaaCyVh == true){KdsUaaCyVh = false;}
      if(WIAgRydxNl == true){WIAgRydxNl = false;}
      if(FQXlfFwQSY == true){FQXlfFwQSY = false;}
      if(QWDfOuHDCQ == true){QWDfOuHDCQ = false;}
      if(ufphksdzWu == true){ufphksdzWu = false;}
      if(iIzUUtGHnU == true){iIzUUtGHnU = false;}
      if(dlewQzEURW == true){dlewQzEURW = false;}
      if(pZuwqZapAm == true){pZuwqZapAm = false;}
      if(bxsWpIWiKU == true){bxsWpIWiKU = false;}
      if(oAPgmIAsRk == true){oAPgmIAsRk = false;}
      if(nIgAFINCcu == true){nIgAFINCcu = false;}
      if(SPGBsfsIGH == true){SPGBsfsIGH = false;}
      if(cVKxgoKNJh == true){cVKxgoKNJh = false;}
      if(YgYOzSQrQg == true){YgYOzSQrQg = false;}
      if(tTFOBYtOmG == true){tTFOBYtOmG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LECZIIOKBD
{ 
  void irytAHiKfR()
  { 
      bool eorRlshniQ = false;
      bool cBzISeRlQP = false;
      bool FzrRrAUukX = false;
      bool dSHyMIQJul = false;
      bool cHAbyBKaYX = false;
      bool GXlkofxZYl = false;
      bool YmCKlJtAwK = false;
      bool NHpdlyyPTq = false;
      bool psWMRGgWIg = false;
      bool KqjJNpEopn = false;
      bool GJeOKzgIyq = false;
      bool ggGhweQosf = false;
      bool cXrPzWWfPu = false;
      bool tJZejfOHCS = false;
      bool YYXRzdjCNh = false;
      bool ZOwKKiROPm = false;
      bool bBrCxWHaxP = false;
      bool QIlZGEAZPU = false;
      bool lURhVeNPTB = false;
      bool NzrPpXfUUc = false;
      string GSxbYqlQKJ;
      string SVHycDTrEm;
      string FwOqNNoHXG;
      string uVXohOSTgN;
      string SINHUSJASa;
      string guqwFJEGOL;
      string CdrEOxySPO;
      string kzLqTxiHVu;
      string DnoxYAdbjY;
      string JLFVLnPJsX;
      string UqkEohiAbI;
      string awjTHNotfN;
      string SViqEYtpfe;
      string gYOyZLDjHq;
      string RdzaxMakNx;
      string yVceFyIsAQ;
      string msUxaBhlsu;
      string KFmownVHtq;
      string xIbhfLwisa;
      string CJjqDXJCAu;
      if(GSxbYqlQKJ == UqkEohiAbI){eorRlshniQ = true;}
      else if(UqkEohiAbI == GSxbYqlQKJ){GJeOKzgIyq = true;}
      if(SVHycDTrEm == awjTHNotfN){cBzISeRlQP = true;}
      else if(awjTHNotfN == SVHycDTrEm){ggGhweQosf = true;}
      if(FwOqNNoHXG == SViqEYtpfe){FzrRrAUukX = true;}
      else if(SViqEYtpfe == FwOqNNoHXG){cXrPzWWfPu = true;}
      if(uVXohOSTgN == gYOyZLDjHq){dSHyMIQJul = true;}
      else if(gYOyZLDjHq == uVXohOSTgN){tJZejfOHCS = true;}
      if(SINHUSJASa == RdzaxMakNx){cHAbyBKaYX = true;}
      else if(RdzaxMakNx == SINHUSJASa){YYXRzdjCNh = true;}
      if(guqwFJEGOL == yVceFyIsAQ){GXlkofxZYl = true;}
      else if(yVceFyIsAQ == guqwFJEGOL){ZOwKKiROPm = true;}
      if(CdrEOxySPO == msUxaBhlsu){YmCKlJtAwK = true;}
      else if(msUxaBhlsu == CdrEOxySPO){bBrCxWHaxP = true;}
      if(kzLqTxiHVu == KFmownVHtq){NHpdlyyPTq = true;}
      if(DnoxYAdbjY == xIbhfLwisa){psWMRGgWIg = true;}
      if(JLFVLnPJsX == CJjqDXJCAu){KqjJNpEopn = true;}
      while(KFmownVHtq == kzLqTxiHVu){QIlZGEAZPU = true;}
      while(xIbhfLwisa == xIbhfLwisa){lURhVeNPTB = true;}
      while(CJjqDXJCAu == CJjqDXJCAu){NzrPpXfUUc = true;}
      if(eorRlshniQ == true){eorRlshniQ = false;}
      if(cBzISeRlQP == true){cBzISeRlQP = false;}
      if(FzrRrAUukX == true){FzrRrAUukX = false;}
      if(dSHyMIQJul == true){dSHyMIQJul = false;}
      if(cHAbyBKaYX == true){cHAbyBKaYX = false;}
      if(GXlkofxZYl == true){GXlkofxZYl = false;}
      if(YmCKlJtAwK == true){YmCKlJtAwK = false;}
      if(NHpdlyyPTq == true){NHpdlyyPTq = false;}
      if(psWMRGgWIg == true){psWMRGgWIg = false;}
      if(KqjJNpEopn == true){KqjJNpEopn = false;}
      if(GJeOKzgIyq == true){GJeOKzgIyq = false;}
      if(ggGhweQosf == true){ggGhweQosf = false;}
      if(cXrPzWWfPu == true){cXrPzWWfPu = false;}
      if(tJZejfOHCS == true){tJZejfOHCS = false;}
      if(YYXRzdjCNh == true){YYXRzdjCNh = false;}
      if(ZOwKKiROPm == true){ZOwKKiROPm = false;}
      if(bBrCxWHaxP == true){bBrCxWHaxP = false;}
      if(QIlZGEAZPU == true){QIlZGEAZPU = false;}
      if(lURhVeNPTB == true){lURhVeNPTB = false;}
      if(NzrPpXfUUc == true){NzrPpXfUUc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDRAEDYFYU
{ 
  void qsSJHsplmO()
  { 
      bool RpWUPJELgs = false;
      bool RNRzoEyTwl = false;
      bool VSszrQTbIx = false;
      bool QqWDVTWSBe = false;
      bool sgQNSrdjbu = false;
      bool szXwkzxWcy = false;
      bool obDjcapOcV = false;
      bool hfSRsoBegA = false;
      bool ljAMDQSZSW = false;
      bool VzoCoQdgjr = false;
      bool BPGFNNgGDw = false;
      bool xRpcLFbpfL = false;
      bool HQwGzhpPbb = false;
      bool KUunyWctzp = false;
      bool jMWVYEJMpj = false;
      bool nnAXkkSAFf = false;
      bool WQdakcWCdo = false;
      bool bgpobusZgu = false;
      bool YcZqnVTXDN = false;
      bool DcoSTThwkw = false;
      string yaUXDumRMs;
      string kkzGxnUOmm;
      string kbjjQVbeqG;
      string FQYeXJMNUg;
      string whjbjHIsya;
      string HjjehWqkHh;
      string THZGnTLTin;
      string aHsGqDrHAI;
      string MigPyUgtxB;
      string RaGmNnHcnP;
      string uoJJzzqdne;
      string dijyUkaJHS;
      string mRWgWABFsC;
      string uOTjNXYWQy;
      string dDGRWhpHRb;
      string NxUVccRcmz;
      string yljkiPPAjx;
      string MDsJoiLEKn;
      string JsmQnxsxHk;
      string FwiQAqSUhH;
      if(yaUXDumRMs == uoJJzzqdne){RpWUPJELgs = true;}
      else if(uoJJzzqdne == yaUXDumRMs){BPGFNNgGDw = true;}
      if(kkzGxnUOmm == dijyUkaJHS){RNRzoEyTwl = true;}
      else if(dijyUkaJHS == kkzGxnUOmm){xRpcLFbpfL = true;}
      if(kbjjQVbeqG == mRWgWABFsC){VSszrQTbIx = true;}
      else if(mRWgWABFsC == kbjjQVbeqG){HQwGzhpPbb = true;}
      if(FQYeXJMNUg == uOTjNXYWQy){QqWDVTWSBe = true;}
      else if(uOTjNXYWQy == FQYeXJMNUg){KUunyWctzp = true;}
      if(whjbjHIsya == dDGRWhpHRb){sgQNSrdjbu = true;}
      else if(dDGRWhpHRb == whjbjHIsya){jMWVYEJMpj = true;}
      if(HjjehWqkHh == NxUVccRcmz){szXwkzxWcy = true;}
      else if(NxUVccRcmz == HjjehWqkHh){nnAXkkSAFf = true;}
      if(THZGnTLTin == yljkiPPAjx){obDjcapOcV = true;}
      else if(yljkiPPAjx == THZGnTLTin){WQdakcWCdo = true;}
      if(aHsGqDrHAI == MDsJoiLEKn){hfSRsoBegA = true;}
      if(MigPyUgtxB == JsmQnxsxHk){ljAMDQSZSW = true;}
      if(RaGmNnHcnP == FwiQAqSUhH){VzoCoQdgjr = true;}
      while(MDsJoiLEKn == aHsGqDrHAI){bgpobusZgu = true;}
      while(JsmQnxsxHk == JsmQnxsxHk){YcZqnVTXDN = true;}
      while(FwiQAqSUhH == FwiQAqSUhH){DcoSTThwkw = true;}
      if(RpWUPJELgs == true){RpWUPJELgs = false;}
      if(RNRzoEyTwl == true){RNRzoEyTwl = false;}
      if(VSszrQTbIx == true){VSszrQTbIx = false;}
      if(QqWDVTWSBe == true){QqWDVTWSBe = false;}
      if(sgQNSrdjbu == true){sgQNSrdjbu = false;}
      if(szXwkzxWcy == true){szXwkzxWcy = false;}
      if(obDjcapOcV == true){obDjcapOcV = false;}
      if(hfSRsoBegA == true){hfSRsoBegA = false;}
      if(ljAMDQSZSW == true){ljAMDQSZSW = false;}
      if(VzoCoQdgjr == true){VzoCoQdgjr = false;}
      if(BPGFNNgGDw == true){BPGFNNgGDw = false;}
      if(xRpcLFbpfL == true){xRpcLFbpfL = false;}
      if(HQwGzhpPbb == true){HQwGzhpPbb = false;}
      if(KUunyWctzp == true){KUunyWctzp = false;}
      if(jMWVYEJMpj == true){jMWVYEJMpj = false;}
      if(nnAXkkSAFf == true){nnAXkkSAFf = false;}
      if(WQdakcWCdo == true){WQdakcWCdo = false;}
      if(bgpobusZgu == true){bgpobusZgu = false;}
      if(YcZqnVTXDN == true){YcZqnVTXDN = false;}
      if(DcoSTThwkw == true){DcoSTThwkw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CWXGCWEJLI
{ 
  void VtfccRkttM()
  { 
      bool ZuLqndrVqL = false;
      bool ABgpLpduQW = false;
      bool wNJFhlOOtD = false;
      bool EDXwjSsSWc = false;
      bool mTXJMsyGyP = false;
      bool oNZjQMlFIC = false;
      bool PdbnHxdjGr = false;
      bool wKXmjbozso = false;
      bool mHQeNqcmeW = false;
      bool gnJTNIqjCP = false;
      bool ONzFSeomAo = false;
      bool XlLTPHNxZQ = false;
      bool TpFiLIBEYa = false;
      bool kExdZYHKLi = false;
      bool BpmpztboEF = false;
      bool usJluYIQtK = false;
      bool ckNZDSohtq = false;
      bool zCkqOdCOjQ = false;
      bool gLzTeqtKhB = false;
      bool PqQBFQbNlf = false;
      string KwotDrZUWq;
      string pzZjPQdQUW;
      string GeRQIHfCKt;
      string oYFdcpYpRI;
      string XjytTxOHnI;
      string QQkUVeeXlu;
      string MXKcCQtuGZ;
      string qmzMyVgWxK;
      string sXNBcXnkIx;
      string LBEVuAZUrC;
      string DSAOQcQXVz;
      string yHZaCoKIzd;
      string cImJNpicRx;
      string wLduHZWyjz;
      string GPOJzDadTG;
      string pQVOYteqBa;
      string tmGXClceSb;
      string RLXzWNtdJK;
      string OEJLHfpPVM;
      string tfxJFTIpGN;
      if(KwotDrZUWq == DSAOQcQXVz){ZuLqndrVqL = true;}
      else if(DSAOQcQXVz == KwotDrZUWq){ONzFSeomAo = true;}
      if(pzZjPQdQUW == yHZaCoKIzd){ABgpLpduQW = true;}
      else if(yHZaCoKIzd == pzZjPQdQUW){XlLTPHNxZQ = true;}
      if(GeRQIHfCKt == cImJNpicRx){wNJFhlOOtD = true;}
      else if(cImJNpicRx == GeRQIHfCKt){TpFiLIBEYa = true;}
      if(oYFdcpYpRI == wLduHZWyjz){EDXwjSsSWc = true;}
      else if(wLduHZWyjz == oYFdcpYpRI){kExdZYHKLi = true;}
      if(XjytTxOHnI == GPOJzDadTG){mTXJMsyGyP = true;}
      else if(GPOJzDadTG == XjytTxOHnI){BpmpztboEF = true;}
      if(QQkUVeeXlu == pQVOYteqBa){oNZjQMlFIC = true;}
      else if(pQVOYteqBa == QQkUVeeXlu){usJluYIQtK = true;}
      if(MXKcCQtuGZ == tmGXClceSb){PdbnHxdjGr = true;}
      else if(tmGXClceSb == MXKcCQtuGZ){ckNZDSohtq = true;}
      if(qmzMyVgWxK == RLXzWNtdJK){wKXmjbozso = true;}
      if(sXNBcXnkIx == OEJLHfpPVM){mHQeNqcmeW = true;}
      if(LBEVuAZUrC == tfxJFTIpGN){gnJTNIqjCP = true;}
      while(RLXzWNtdJK == qmzMyVgWxK){zCkqOdCOjQ = true;}
      while(OEJLHfpPVM == OEJLHfpPVM){gLzTeqtKhB = true;}
      while(tfxJFTIpGN == tfxJFTIpGN){PqQBFQbNlf = true;}
      if(ZuLqndrVqL == true){ZuLqndrVqL = false;}
      if(ABgpLpduQW == true){ABgpLpduQW = false;}
      if(wNJFhlOOtD == true){wNJFhlOOtD = false;}
      if(EDXwjSsSWc == true){EDXwjSsSWc = false;}
      if(mTXJMsyGyP == true){mTXJMsyGyP = false;}
      if(oNZjQMlFIC == true){oNZjQMlFIC = false;}
      if(PdbnHxdjGr == true){PdbnHxdjGr = false;}
      if(wKXmjbozso == true){wKXmjbozso = false;}
      if(mHQeNqcmeW == true){mHQeNqcmeW = false;}
      if(gnJTNIqjCP == true){gnJTNIqjCP = false;}
      if(ONzFSeomAo == true){ONzFSeomAo = false;}
      if(XlLTPHNxZQ == true){XlLTPHNxZQ = false;}
      if(TpFiLIBEYa == true){TpFiLIBEYa = false;}
      if(kExdZYHKLi == true){kExdZYHKLi = false;}
      if(BpmpztboEF == true){BpmpztboEF = false;}
      if(usJluYIQtK == true){usJluYIQtK = false;}
      if(ckNZDSohtq == true){ckNZDSohtq = false;}
      if(zCkqOdCOjQ == true){zCkqOdCOjQ = false;}
      if(gLzTeqtKhB == true){gLzTeqtKhB = false;}
      if(PqQBFQbNlf == true){PqQBFQbNlf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TAASHJSYGA
{ 
  void CKcKgobNgp()
  { 
      bool GhpCaGLFBn = false;
      bool rOFpSYaRjT = false;
      bool xnBjNetPam = false;
      bool ddqDgSKlBM = false;
      bool eCuMpgdnrR = false;
      bool cFoTeSfFow = false;
      bool LweNKOWBIA = false;
      bool NoPXnurntf = false;
      bool AGXIKXoWYO = false;
      bool lFwEAiXgCb = false;
      bool JceqEmoQej = false;
      bool arLJwFXVDl = false;
      bool ZzctNIrKXF = false;
      bool XKlSVXafEW = false;
      bool iYqnmtsmIt = false;
      bool LBdQCKzjdw = false;
      bool udrZMPGsmY = false;
      bool eqRgDAHnGT = false;
      bool OFCdsVfVQL = false;
      bool XqCIbEfRbX = false;
      string rdxyZQaskQ;
      string kuWTqpejfT;
      string AXEEsLGbFC;
      string QmlAlrYMYk;
      string LemHFkwiIV;
      string BcIIKTYsFO;
      string JznhAxIVgz;
      string QRLuIVjxzH;
      string PXSiAmecoR;
      string SeHKbLqFGH;
      string bZBJEjRNAo;
      string jbtyykgEhN;
      string RffOfkKBSx;
      string depqeoWIdQ;
      string URcAhqkJLp;
      string elWsowtldT;
      string ZQtDLFkDSI;
      string OXaRrADfgn;
      string ABocSqHxBi;
      string ujdKpEWZnc;
      if(rdxyZQaskQ == bZBJEjRNAo){GhpCaGLFBn = true;}
      else if(bZBJEjRNAo == rdxyZQaskQ){JceqEmoQej = true;}
      if(kuWTqpejfT == jbtyykgEhN){rOFpSYaRjT = true;}
      else if(jbtyykgEhN == kuWTqpejfT){arLJwFXVDl = true;}
      if(AXEEsLGbFC == RffOfkKBSx){xnBjNetPam = true;}
      else if(RffOfkKBSx == AXEEsLGbFC){ZzctNIrKXF = true;}
      if(QmlAlrYMYk == depqeoWIdQ){ddqDgSKlBM = true;}
      else if(depqeoWIdQ == QmlAlrYMYk){XKlSVXafEW = true;}
      if(LemHFkwiIV == URcAhqkJLp){eCuMpgdnrR = true;}
      else if(URcAhqkJLp == LemHFkwiIV){iYqnmtsmIt = true;}
      if(BcIIKTYsFO == elWsowtldT){cFoTeSfFow = true;}
      else if(elWsowtldT == BcIIKTYsFO){LBdQCKzjdw = true;}
      if(JznhAxIVgz == ZQtDLFkDSI){LweNKOWBIA = true;}
      else if(ZQtDLFkDSI == JznhAxIVgz){udrZMPGsmY = true;}
      if(QRLuIVjxzH == OXaRrADfgn){NoPXnurntf = true;}
      if(PXSiAmecoR == ABocSqHxBi){AGXIKXoWYO = true;}
      if(SeHKbLqFGH == ujdKpEWZnc){lFwEAiXgCb = true;}
      while(OXaRrADfgn == QRLuIVjxzH){eqRgDAHnGT = true;}
      while(ABocSqHxBi == ABocSqHxBi){OFCdsVfVQL = true;}
      while(ujdKpEWZnc == ujdKpEWZnc){XqCIbEfRbX = true;}
      if(GhpCaGLFBn == true){GhpCaGLFBn = false;}
      if(rOFpSYaRjT == true){rOFpSYaRjT = false;}
      if(xnBjNetPam == true){xnBjNetPam = false;}
      if(ddqDgSKlBM == true){ddqDgSKlBM = false;}
      if(eCuMpgdnrR == true){eCuMpgdnrR = false;}
      if(cFoTeSfFow == true){cFoTeSfFow = false;}
      if(LweNKOWBIA == true){LweNKOWBIA = false;}
      if(NoPXnurntf == true){NoPXnurntf = false;}
      if(AGXIKXoWYO == true){AGXIKXoWYO = false;}
      if(lFwEAiXgCb == true){lFwEAiXgCb = false;}
      if(JceqEmoQej == true){JceqEmoQej = false;}
      if(arLJwFXVDl == true){arLJwFXVDl = false;}
      if(ZzctNIrKXF == true){ZzctNIrKXF = false;}
      if(XKlSVXafEW == true){XKlSVXafEW = false;}
      if(iYqnmtsmIt == true){iYqnmtsmIt = false;}
      if(LBdQCKzjdw == true){LBdQCKzjdw = false;}
      if(udrZMPGsmY == true){udrZMPGsmY = false;}
      if(eqRgDAHnGT == true){eqRgDAHnGT = false;}
      if(OFCdsVfVQL == true){OFCdsVfVQL = false;}
      if(XqCIbEfRbX == true){XqCIbEfRbX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZHTZUKHAP
{ 
  void PZUbxHUQQr()
  { 
      bool JcqixcbhKx = false;
      bool OOnpmIzFtX = false;
      bool oDrrbzZYSW = false;
      bool JeiKPDdzby = false;
      bool tueFksSwZq = false;
      bool DlxeUFkzHx = false;
      bool DDOnmiedZj = false;
      bool ezdwcsYlGh = false;
      bool gcybSWhEoK = false;
      bool SerdtqfqRB = false;
      bool OoWpMDHACb = false;
      bool gyrYQaFmVQ = false;
      bool BZnPQAHzCk = false;
      bool NhUFTqGIPO = false;
      bool PgBNcTlSMT = false;
      bool lrUBAnAHYL = false;
      bool wHyQNzdmEZ = false;
      bool TwXGBUXalx = false;
      bool NnmhzUMTEf = false;
      bool qziDSHhkzc = false;
      string HhRPbrHXYo;
      string xDoQTIUHbp;
      string XjqyZpxuzN;
      string MsObuPkDuW;
      string SFIWaNxaxt;
      string AtNLyXpSpk;
      string tMXKcEoMUD;
      string WRLFXSbUXL;
      string sWxENSfCcX;
      string ZSNKbFgxtW;
      string YjFtXihInf;
      string wUudrXPSxJ;
      string XljwdDEAcR;
      string kdaAlIQCgd;
      string jWOxbEWiSE;
      string pNAjylAJPT;
      string dgeVtRttqi;
      string GMlSYBXlUZ;
      string fVhYbWcpCz;
      string HHmNzCrrCJ;
      if(HhRPbrHXYo == YjFtXihInf){JcqixcbhKx = true;}
      else if(YjFtXihInf == HhRPbrHXYo){OoWpMDHACb = true;}
      if(xDoQTIUHbp == wUudrXPSxJ){OOnpmIzFtX = true;}
      else if(wUudrXPSxJ == xDoQTIUHbp){gyrYQaFmVQ = true;}
      if(XjqyZpxuzN == XljwdDEAcR){oDrrbzZYSW = true;}
      else if(XljwdDEAcR == XjqyZpxuzN){BZnPQAHzCk = true;}
      if(MsObuPkDuW == kdaAlIQCgd){JeiKPDdzby = true;}
      else if(kdaAlIQCgd == MsObuPkDuW){NhUFTqGIPO = true;}
      if(SFIWaNxaxt == jWOxbEWiSE){tueFksSwZq = true;}
      else if(jWOxbEWiSE == SFIWaNxaxt){PgBNcTlSMT = true;}
      if(AtNLyXpSpk == pNAjylAJPT){DlxeUFkzHx = true;}
      else if(pNAjylAJPT == AtNLyXpSpk){lrUBAnAHYL = true;}
      if(tMXKcEoMUD == dgeVtRttqi){DDOnmiedZj = true;}
      else if(dgeVtRttqi == tMXKcEoMUD){wHyQNzdmEZ = true;}
      if(WRLFXSbUXL == GMlSYBXlUZ){ezdwcsYlGh = true;}
      if(sWxENSfCcX == fVhYbWcpCz){gcybSWhEoK = true;}
      if(ZSNKbFgxtW == HHmNzCrrCJ){SerdtqfqRB = true;}
      while(GMlSYBXlUZ == WRLFXSbUXL){TwXGBUXalx = true;}
      while(fVhYbWcpCz == fVhYbWcpCz){NnmhzUMTEf = true;}
      while(HHmNzCrrCJ == HHmNzCrrCJ){qziDSHhkzc = true;}
      if(JcqixcbhKx == true){JcqixcbhKx = false;}
      if(OOnpmIzFtX == true){OOnpmIzFtX = false;}
      if(oDrrbzZYSW == true){oDrrbzZYSW = false;}
      if(JeiKPDdzby == true){JeiKPDdzby = false;}
      if(tueFksSwZq == true){tueFksSwZq = false;}
      if(DlxeUFkzHx == true){DlxeUFkzHx = false;}
      if(DDOnmiedZj == true){DDOnmiedZj = false;}
      if(ezdwcsYlGh == true){ezdwcsYlGh = false;}
      if(gcybSWhEoK == true){gcybSWhEoK = false;}
      if(SerdtqfqRB == true){SerdtqfqRB = false;}
      if(OoWpMDHACb == true){OoWpMDHACb = false;}
      if(gyrYQaFmVQ == true){gyrYQaFmVQ = false;}
      if(BZnPQAHzCk == true){BZnPQAHzCk = false;}
      if(NhUFTqGIPO == true){NhUFTqGIPO = false;}
      if(PgBNcTlSMT == true){PgBNcTlSMT = false;}
      if(lrUBAnAHYL == true){lrUBAnAHYL = false;}
      if(wHyQNzdmEZ == true){wHyQNzdmEZ = false;}
      if(TwXGBUXalx == true){TwXGBUXalx = false;}
      if(NnmhzUMTEf == true){NnmhzUMTEf = false;}
      if(qziDSHhkzc == true){qziDSHhkzc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJXMBHOOZQ
{ 
  void lYUUJwVhQq()
  { 
      bool JsqnWKiYku = false;
      bool aCBkKPNKQd = false;
      bool TIBLhEwaNp = false;
      bool UKEQNQbuug = false;
      bool QKsgRuRlzU = false;
      bool rJnKlBqfFR = false;
      bool OHKtZPxjWs = false;
      bool mRPjMJOTtl = false;
      bool mJasxLWteM = false;
      bool ZwpdSIzzHB = false;
      bool xhPGgasDyc = false;
      bool mXkSeEgRwN = false;
      bool sDFJTqakRE = false;
      bool JPMsoEtUMW = false;
      bool SSuBYCKXzN = false;
      bool bhCsHtcFlo = false;
      bool zHlsSXKrdZ = false;
      bool KLFYuaHDkR = false;
      bool fClDcbMSku = false;
      bool bnhWXKfCiB = false;
      string cZKrcHNbDR;
      string cCDRFiXkwn;
      string sYgiAtuEcQ;
      string LCcYUnoZhX;
      string mkcmyunAtw;
      string xFOgHErbri;
      string LJymFaZewQ;
      string txDYBHuskE;
      string FuJgTFmuRQ;
      string uNhyLdlpgX;
      string VJDdBzCpfz;
      string IzqmcQzRSA;
      string meMeUgPEMW;
      string UFLMiurfeU;
      string DxOSIwWuUu;
      string eUWgjqxXIU;
      string jxcJdCmdDg;
      string YTlywoPtWX;
      string JTiRrAiebr;
      string yTWKjGTFoF;
      if(cZKrcHNbDR == VJDdBzCpfz){JsqnWKiYku = true;}
      else if(VJDdBzCpfz == cZKrcHNbDR){xhPGgasDyc = true;}
      if(cCDRFiXkwn == IzqmcQzRSA){aCBkKPNKQd = true;}
      else if(IzqmcQzRSA == cCDRFiXkwn){mXkSeEgRwN = true;}
      if(sYgiAtuEcQ == meMeUgPEMW){TIBLhEwaNp = true;}
      else if(meMeUgPEMW == sYgiAtuEcQ){sDFJTqakRE = true;}
      if(LCcYUnoZhX == UFLMiurfeU){UKEQNQbuug = true;}
      else if(UFLMiurfeU == LCcYUnoZhX){JPMsoEtUMW = true;}
      if(mkcmyunAtw == DxOSIwWuUu){QKsgRuRlzU = true;}
      else if(DxOSIwWuUu == mkcmyunAtw){SSuBYCKXzN = true;}
      if(xFOgHErbri == eUWgjqxXIU){rJnKlBqfFR = true;}
      else if(eUWgjqxXIU == xFOgHErbri){bhCsHtcFlo = true;}
      if(LJymFaZewQ == jxcJdCmdDg){OHKtZPxjWs = true;}
      else if(jxcJdCmdDg == LJymFaZewQ){zHlsSXKrdZ = true;}
      if(txDYBHuskE == YTlywoPtWX){mRPjMJOTtl = true;}
      if(FuJgTFmuRQ == JTiRrAiebr){mJasxLWteM = true;}
      if(uNhyLdlpgX == yTWKjGTFoF){ZwpdSIzzHB = true;}
      while(YTlywoPtWX == txDYBHuskE){KLFYuaHDkR = true;}
      while(JTiRrAiebr == JTiRrAiebr){fClDcbMSku = true;}
      while(yTWKjGTFoF == yTWKjGTFoF){bnhWXKfCiB = true;}
      if(JsqnWKiYku == true){JsqnWKiYku = false;}
      if(aCBkKPNKQd == true){aCBkKPNKQd = false;}
      if(TIBLhEwaNp == true){TIBLhEwaNp = false;}
      if(UKEQNQbuug == true){UKEQNQbuug = false;}
      if(QKsgRuRlzU == true){QKsgRuRlzU = false;}
      if(rJnKlBqfFR == true){rJnKlBqfFR = false;}
      if(OHKtZPxjWs == true){OHKtZPxjWs = false;}
      if(mRPjMJOTtl == true){mRPjMJOTtl = false;}
      if(mJasxLWteM == true){mJasxLWteM = false;}
      if(ZwpdSIzzHB == true){ZwpdSIzzHB = false;}
      if(xhPGgasDyc == true){xhPGgasDyc = false;}
      if(mXkSeEgRwN == true){mXkSeEgRwN = false;}
      if(sDFJTqakRE == true){sDFJTqakRE = false;}
      if(JPMsoEtUMW == true){JPMsoEtUMW = false;}
      if(SSuBYCKXzN == true){SSuBYCKXzN = false;}
      if(bhCsHtcFlo == true){bhCsHtcFlo = false;}
      if(zHlsSXKrdZ == true){zHlsSXKrdZ = false;}
      if(KLFYuaHDkR == true){KLFYuaHDkR = false;}
      if(fClDcbMSku == true){fClDcbMSku = false;}
      if(bnhWXKfCiB == true){bnhWXKfCiB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOGKWSENHL
{ 
  void oeFOiacDrT()
  { 
      bool PVrZfQtDRf = false;
      bool ClnaShZeTT = false;
      bool MkuKwzIAtl = false;
      bool uYCxzKqhfM = false;
      bool BpWiUnnlyU = false;
      bool PAxTZdZgdf = false;
      bool HsJejdiqaH = false;
      bool qrzHSWOLpH = false;
      bool KWCZWuaiXV = false;
      bool jJDzEHgqyq = false;
      bool FxKpcWApAD = false;
      bool PNpWVkqiHo = false;
      bool CzSFXgnACL = false;
      bool pWMzBNLLwA = false;
      bool tjiTFVTgdS = false;
      bool PxiJnFdFRw = false;
      bool hzmnMrAqUH = false;
      bool ZemHuRQyzC = false;
      bool NHWiwsnDKu = false;
      bool iFtzRtxtHN = false;
      string pJaPSPPfJc;
      string gyKXeIWyfI;
      string ygaOzResWB;
      string UBPqBdcoXX;
      string hAXAliqZus;
      string IMSnSIhLPB;
      string kWJIHfiTVA;
      string fhaHaxIacQ;
      string aFycsIhbYr;
      string wQYWmLqPrF;
      string AXDtNZlLMU;
      string zHizZeYfPz;
      string yGtdEOIETP;
      string FshWQDCDPS;
      string WWPDsohZwI;
      string lKAsHscYpz;
      string QhqxPGYLhW;
      string cVQwbaqqjP;
      string fiHLcusnPW;
      string acMQCofRnm;
      if(pJaPSPPfJc == AXDtNZlLMU){PVrZfQtDRf = true;}
      else if(AXDtNZlLMU == pJaPSPPfJc){FxKpcWApAD = true;}
      if(gyKXeIWyfI == zHizZeYfPz){ClnaShZeTT = true;}
      else if(zHizZeYfPz == gyKXeIWyfI){PNpWVkqiHo = true;}
      if(ygaOzResWB == yGtdEOIETP){MkuKwzIAtl = true;}
      else if(yGtdEOIETP == ygaOzResWB){CzSFXgnACL = true;}
      if(UBPqBdcoXX == FshWQDCDPS){uYCxzKqhfM = true;}
      else if(FshWQDCDPS == UBPqBdcoXX){pWMzBNLLwA = true;}
      if(hAXAliqZus == WWPDsohZwI){BpWiUnnlyU = true;}
      else if(WWPDsohZwI == hAXAliqZus){tjiTFVTgdS = true;}
      if(IMSnSIhLPB == lKAsHscYpz){PAxTZdZgdf = true;}
      else if(lKAsHscYpz == IMSnSIhLPB){PxiJnFdFRw = true;}
      if(kWJIHfiTVA == QhqxPGYLhW){HsJejdiqaH = true;}
      else if(QhqxPGYLhW == kWJIHfiTVA){hzmnMrAqUH = true;}
      if(fhaHaxIacQ == cVQwbaqqjP){qrzHSWOLpH = true;}
      if(aFycsIhbYr == fiHLcusnPW){KWCZWuaiXV = true;}
      if(wQYWmLqPrF == acMQCofRnm){jJDzEHgqyq = true;}
      while(cVQwbaqqjP == fhaHaxIacQ){ZemHuRQyzC = true;}
      while(fiHLcusnPW == fiHLcusnPW){NHWiwsnDKu = true;}
      while(acMQCofRnm == acMQCofRnm){iFtzRtxtHN = true;}
      if(PVrZfQtDRf == true){PVrZfQtDRf = false;}
      if(ClnaShZeTT == true){ClnaShZeTT = false;}
      if(MkuKwzIAtl == true){MkuKwzIAtl = false;}
      if(uYCxzKqhfM == true){uYCxzKqhfM = false;}
      if(BpWiUnnlyU == true){BpWiUnnlyU = false;}
      if(PAxTZdZgdf == true){PAxTZdZgdf = false;}
      if(HsJejdiqaH == true){HsJejdiqaH = false;}
      if(qrzHSWOLpH == true){qrzHSWOLpH = false;}
      if(KWCZWuaiXV == true){KWCZWuaiXV = false;}
      if(jJDzEHgqyq == true){jJDzEHgqyq = false;}
      if(FxKpcWApAD == true){FxKpcWApAD = false;}
      if(PNpWVkqiHo == true){PNpWVkqiHo = false;}
      if(CzSFXgnACL == true){CzSFXgnACL = false;}
      if(pWMzBNLLwA == true){pWMzBNLLwA = false;}
      if(tjiTFVTgdS == true){tjiTFVTgdS = false;}
      if(PxiJnFdFRw == true){PxiJnFdFRw = false;}
      if(hzmnMrAqUH == true){hzmnMrAqUH = false;}
      if(ZemHuRQyzC == true){ZemHuRQyzC = false;}
      if(NHWiwsnDKu == true){NHWiwsnDKu = false;}
      if(iFtzRtxtHN == true){iFtzRtxtHN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKVLMNWTPI
{ 
  void VPXaZmYKSy()
  { 
      bool WjFwTUwVPH = false;
      bool LuUsRsNkXr = false;
      bool YXUOEMtfbZ = false;
      bool JSIMcqHAWf = false;
      bool CDpImVStYy = false;
      bool FhxnwyOpqH = false;
      bool aPsoxrmHPa = false;
      bool lMOrpUgMbi = false;
      bool szGcUbVUPe = false;
      bool bQJPFlKBLu = false;
      bool iKeyMsTFxa = false;
      bool QCOINaJQUU = false;
      bool WRrjyUDylD = false;
      bool KfAgziUHQa = false;
      bool IPWnNYCACd = false;
      bool csfpYQStAr = false;
      bool oUSsPjBgId = false;
      bool GBAsLGuDVY = false;
      bool RCwIaQAKHi = false;
      bool QZHXlnwcYc = false;
      string aBbmDfFNqG;
      string wpbKjNsIPc;
      string HmIdmksQbl;
      string dnciWnGfGw;
      string GNOKSAnupy;
      string zaFBCmryzS;
      string molFbINrnw;
      string GMBSWtYyLl;
      string wxaclDiafj;
      string uIfmIRbJhK;
      string mwHtrmYmeI;
      string OtlMVoOISY;
      string YlLDAyfOJE;
      string RPPBzApfkz;
      string dwwWUAVSRS;
      string DTpJkAjDss;
      string GKcZqzdkNV;
      string zhWTtconiA;
      string bMwqByZGPy;
      string QmmqrTSVfV;
      if(aBbmDfFNqG == mwHtrmYmeI){WjFwTUwVPH = true;}
      else if(mwHtrmYmeI == aBbmDfFNqG){iKeyMsTFxa = true;}
      if(wpbKjNsIPc == OtlMVoOISY){LuUsRsNkXr = true;}
      else if(OtlMVoOISY == wpbKjNsIPc){QCOINaJQUU = true;}
      if(HmIdmksQbl == YlLDAyfOJE){YXUOEMtfbZ = true;}
      else if(YlLDAyfOJE == HmIdmksQbl){WRrjyUDylD = true;}
      if(dnciWnGfGw == RPPBzApfkz){JSIMcqHAWf = true;}
      else if(RPPBzApfkz == dnciWnGfGw){KfAgziUHQa = true;}
      if(GNOKSAnupy == dwwWUAVSRS){CDpImVStYy = true;}
      else if(dwwWUAVSRS == GNOKSAnupy){IPWnNYCACd = true;}
      if(zaFBCmryzS == DTpJkAjDss){FhxnwyOpqH = true;}
      else if(DTpJkAjDss == zaFBCmryzS){csfpYQStAr = true;}
      if(molFbINrnw == GKcZqzdkNV){aPsoxrmHPa = true;}
      else if(GKcZqzdkNV == molFbINrnw){oUSsPjBgId = true;}
      if(GMBSWtYyLl == zhWTtconiA){lMOrpUgMbi = true;}
      if(wxaclDiafj == bMwqByZGPy){szGcUbVUPe = true;}
      if(uIfmIRbJhK == QmmqrTSVfV){bQJPFlKBLu = true;}
      while(zhWTtconiA == GMBSWtYyLl){GBAsLGuDVY = true;}
      while(bMwqByZGPy == bMwqByZGPy){RCwIaQAKHi = true;}
      while(QmmqrTSVfV == QmmqrTSVfV){QZHXlnwcYc = true;}
      if(WjFwTUwVPH == true){WjFwTUwVPH = false;}
      if(LuUsRsNkXr == true){LuUsRsNkXr = false;}
      if(YXUOEMtfbZ == true){YXUOEMtfbZ = false;}
      if(JSIMcqHAWf == true){JSIMcqHAWf = false;}
      if(CDpImVStYy == true){CDpImVStYy = false;}
      if(FhxnwyOpqH == true){FhxnwyOpqH = false;}
      if(aPsoxrmHPa == true){aPsoxrmHPa = false;}
      if(lMOrpUgMbi == true){lMOrpUgMbi = false;}
      if(szGcUbVUPe == true){szGcUbVUPe = false;}
      if(bQJPFlKBLu == true){bQJPFlKBLu = false;}
      if(iKeyMsTFxa == true){iKeyMsTFxa = false;}
      if(QCOINaJQUU == true){QCOINaJQUU = false;}
      if(WRrjyUDylD == true){WRrjyUDylD = false;}
      if(KfAgziUHQa == true){KfAgziUHQa = false;}
      if(IPWnNYCACd == true){IPWnNYCACd = false;}
      if(csfpYQStAr == true){csfpYQStAr = false;}
      if(oUSsPjBgId == true){oUSsPjBgId = false;}
      if(GBAsLGuDVY == true){GBAsLGuDVY = false;}
      if(RCwIaQAKHi == true){RCwIaQAKHi = false;}
      if(QZHXlnwcYc == true){QZHXlnwcYc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLZLSANQCR
{ 
  void lBRyeHgccY()
  { 
      bool FUEZZJhKID = false;
      bool rCYKkMHuVk = false;
      bool jFxRtbTALk = false;
      bool ORVHQWzuzO = false;
      bool DTfByrucRx = false;
      bool aeZOwzXlex = false;
      bool ohzWnZgQtN = false;
      bool NMuHhPYwTC = false;
      bool gqhNKirGLQ = false;
      bool zNPBYVUINY = false;
      bool LeiDjOiSff = false;
      bool abScQyzlLE = false;
      bool hZEcOAwshM = false;
      bool uQhtpBHdcw = false;
      bool AYZfpXtlka = false;
      bool ViwIqkZFoj = false;
      bool RojTkKsXlO = false;
      bool pUIPEIzYmq = false;
      bool FKIHpMTZDF = false;
      bool aCordKnGtf = false;
      string wOgDNcxLrl;
      string cMNjXmTYCW;
      string SgeFpRXAEh;
      string mclCiszhSF;
      string oapGdiewff;
      string VROPkPibMu;
      string FwHKzzZLBe;
      string mlGwgqpXbG;
      string mbUXLVOWRS;
      string JXUWArTfGd;
      string JSuBriLRhs;
      string YKzGIcbiyd;
      string kDthUPRiwn;
      string WKRxxTgTfb;
      string KwoXtyXNOW;
      string QkgcrGYMfc;
      string RbVsWNsCJo;
      string wHDVToNWnV;
      string rEUZXkdnEq;
      string tTmCKhauAf;
      if(wOgDNcxLrl == JSuBriLRhs){FUEZZJhKID = true;}
      else if(JSuBriLRhs == wOgDNcxLrl){LeiDjOiSff = true;}
      if(cMNjXmTYCW == YKzGIcbiyd){rCYKkMHuVk = true;}
      else if(YKzGIcbiyd == cMNjXmTYCW){abScQyzlLE = true;}
      if(SgeFpRXAEh == kDthUPRiwn){jFxRtbTALk = true;}
      else if(kDthUPRiwn == SgeFpRXAEh){hZEcOAwshM = true;}
      if(mclCiszhSF == WKRxxTgTfb){ORVHQWzuzO = true;}
      else if(WKRxxTgTfb == mclCiszhSF){uQhtpBHdcw = true;}
      if(oapGdiewff == KwoXtyXNOW){DTfByrucRx = true;}
      else if(KwoXtyXNOW == oapGdiewff){AYZfpXtlka = true;}
      if(VROPkPibMu == QkgcrGYMfc){aeZOwzXlex = true;}
      else if(QkgcrGYMfc == VROPkPibMu){ViwIqkZFoj = true;}
      if(FwHKzzZLBe == RbVsWNsCJo){ohzWnZgQtN = true;}
      else if(RbVsWNsCJo == FwHKzzZLBe){RojTkKsXlO = true;}
      if(mlGwgqpXbG == wHDVToNWnV){NMuHhPYwTC = true;}
      if(mbUXLVOWRS == rEUZXkdnEq){gqhNKirGLQ = true;}
      if(JXUWArTfGd == tTmCKhauAf){zNPBYVUINY = true;}
      while(wHDVToNWnV == mlGwgqpXbG){pUIPEIzYmq = true;}
      while(rEUZXkdnEq == rEUZXkdnEq){FKIHpMTZDF = true;}
      while(tTmCKhauAf == tTmCKhauAf){aCordKnGtf = true;}
      if(FUEZZJhKID == true){FUEZZJhKID = false;}
      if(rCYKkMHuVk == true){rCYKkMHuVk = false;}
      if(jFxRtbTALk == true){jFxRtbTALk = false;}
      if(ORVHQWzuzO == true){ORVHQWzuzO = false;}
      if(DTfByrucRx == true){DTfByrucRx = false;}
      if(aeZOwzXlex == true){aeZOwzXlex = false;}
      if(ohzWnZgQtN == true){ohzWnZgQtN = false;}
      if(NMuHhPYwTC == true){NMuHhPYwTC = false;}
      if(gqhNKirGLQ == true){gqhNKirGLQ = false;}
      if(zNPBYVUINY == true){zNPBYVUINY = false;}
      if(LeiDjOiSff == true){LeiDjOiSff = false;}
      if(abScQyzlLE == true){abScQyzlLE = false;}
      if(hZEcOAwshM == true){hZEcOAwshM = false;}
      if(uQhtpBHdcw == true){uQhtpBHdcw = false;}
      if(AYZfpXtlka == true){AYZfpXtlka = false;}
      if(ViwIqkZFoj == true){ViwIqkZFoj = false;}
      if(RojTkKsXlO == true){RojTkKsXlO = false;}
      if(pUIPEIzYmq == true){pUIPEIzYmq = false;}
      if(FKIHpMTZDF == true){FKIHpMTZDF = false;}
      if(aCordKnGtf == true){aCordKnGtf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYIJWJORKQ
{ 
  void TngGwDooTc()
  { 
      bool uDKJZBgAJj = false;
      bool fdqUlCPptw = false;
      bool xQMqbxSUjt = false;
      bool XONiietwYr = false;
      bool taFDuGTxoQ = false;
      bool hubIHepThb = false;
      bool hLPOMQQIkH = false;
      bool ITQBCVKJwU = false;
      bool dVeTMclFbE = false;
      bool oaNxJhKqpd = false;
      bool pKLhIOdaFk = false;
      bool TfXNyMfwCj = false;
      bool eKggShFTqT = false;
      bool LTTRdSJxKx = false;
      bool yLzqjIDAzw = false;
      bool COnGzeddPa = false;
      bool IKilZzMFie = false;
      bool DikEkSLowJ = false;
      bool dFUtRwfMSy = false;
      bool nfgjnnbNRk = false;
      string hwQwgblgfk;
      string RkLOjCTbje;
      string AHTXjOnMie;
      string IiNLLCeyhU;
      string MWmoMhqAne;
      string LqkkGabsLR;
      string mZyAchXzCh;
      string XUsORdTdLC;
      string XnXESQxcFk;
      string ZkmQgmYmMd;
      string KqxGHpyWSc;
      string GxhJszBtgL;
      string jttRHlhcge;
      string FgQgqgpQxb;
      string SaJbdbDcWh;
      string kdFBsQwezU;
      string IVonXYfARM;
      string IjxErJjSne;
      string hFFysabPma;
      string kLRbTxkVEE;
      if(hwQwgblgfk == KqxGHpyWSc){uDKJZBgAJj = true;}
      else if(KqxGHpyWSc == hwQwgblgfk){pKLhIOdaFk = true;}
      if(RkLOjCTbje == GxhJszBtgL){fdqUlCPptw = true;}
      else if(GxhJszBtgL == RkLOjCTbje){TfXNyMfwCj = true;}
      if(AHTXjOnMie == jttRHlhcge){xQMqbxSUjt = true;}
      else if(jttRHlhcge == AHTXjOnMie){eKggShFTqT = true;}
      if(IiNLLCeyhU == FgQgqgpQxb){XONiietwYr = true;}
      else if(FgQgqgpQxb == IiNLLCeyhU){LTTRdSJxKx = true;}
      if(MWmoMhqAne == SaJbdbDcWh){taFDuGTxoQ = true;}
      else if(SaJbdbDcWh == MWmoMhqAne){yLzqjIDAzw = true;}
      if(LqkkGabsLR == kdFBsQwezU){hubIHepThb = true;}
      else if(kdFBsQwezU == LqkkGabsLR){COnGzeddPa = true;}
      if(mZyAchXzCh == IVonXYfARM){hLPOMQQIkH = true;}
      else if(IVonXYfARM == mZyAchXzCh){IKilZzMFie = true;}
      if(XUsORdTdLC == IjxErJjSne){ITQBCVKJwU = true;}
      if(XnXESQxcFk == hFFysabPma){dVeTMclFbE = true;}
      if(ZkmQgmYmMd == kLRbTxkVEE){oaNxJhKqpd = true;}
      while(IjxErJjSne == XUsORdTdLC){DikEkSLowJ = true;}
      while(hFFysabPma == hFFysabPma){dFUtRwfMSy = true;}
      while(kLRbTxkVEE == kLRbTxkVEE){nfgjnnbNRk = true;}
      if(uDKJZBgAJj == true){uDKJZBgAJj = false;}
      if(fdqUlCPptw == true){fdqUlCPptw = false;}
      if(xQMqbxSUjt == true){xQMqbxSUjt = false;}
      if(XONiietwYr == true){XONiietwYr = false;}
      if(taFDuGTxoQ == true){taFDuGTxoQ = false;}
      if(hubIHepThb == true){hubIHepThb = false;}
      if(hLPOMQQIkH == true){hLPOMQQIkH = false;}
      if(ITQBCVKJwU == true){ITQBCVKJwU = false;}
      if(dVeTMclFbE == true){dVeTMclFbE = false;}
      if(oaNxJhKqpd == true){oaNxJhKqpd = false;}
      if(pKLhIOdaFk == true){pKLhIOdaFk = false;}
      if(TfXNyMfwCj == true){TfXNyMfwCj = false;}
      if(eKggShFTqT == true){eKggShFTqT = false;}
      if(LTTRdSJxKx == true){LTTRdSJxKx = false;}
      if(yLzqjIDAzw == true){yLzqjIDAzw = false;}
      if(COnGzeddPa == true){COnGzeddPa = false;}
      if(IKilZzMFie == true){IKilZzMFie = false;}
      if(DikEkSLowJ == true){DikEkSLowJ = false;}
      if(dFUtRwfMSy == true){dFUtRwfMSy = false;}
      if(nfgjnnbNRk == true){nfgjnnbNRk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAHWYGKDGG
{ 
  void FUmeJnAKBS()
  { 
      bool huZlUpoZQd = false;
      bool JIhwosjbMy = false;
      bool eqEAojBEjY = false;
      bool LewEqfYrmz = false;
      bool rhVMTqGXlQ = false;
      bool aRfLCppZxj = false;
      bool ojpqSdLdFJ = false;
      bool UqoNFwUqfx = false;
      bool dcSSyszjBA = false;
      bool oyuCKIreto = false;
      bool ebRcwicSGF = false;
      bool UytzGLRWsY = false;
      bool ebbFTVulDx = false;
      bool EpxpSBKoWO = false;
      bool QgduepEwwy = false;
      bool pUkVKDAMJa = false;
      bool npOIBeBDgE = false;
      bool BcAdHxxfZd = false;
      bool QzpEGiEafP = false;
      bool BxfwaZRVtA = false;
      string gojqZXqiwz;
      string bCTwYMthSO;
      string lRSQmAGdlu;
      string tbgACEgxBq;
      string mpUQUXcVdM;
      string tAMfcOVSDY;
      string QNxAEzUStU;
      string exgaauxBwO;
      string XjAYBtPAWm;
      string hNsbZZsTMU;
      string CJbIgxTkEh;
      string RUWoBgNXzK;
      string jUuHmRDEBB;
      string CdoaLNIqqE;
      string ZdwoVNpDZs;
      string LUUBjhOTVP;
      string sOjCeneudn;
      string YVftjGYGlY;
      string azeHogImqc;
      string znUbKKtsJg;
      if(gojqZXqiwz == CJbIgxTkEh){huZlUpoZQd = true;}
      else if(CJbIgxTkEh == gojqZXqiwz){ebRcwicSGF = true;}
      if(bCTwYMthSO == RUWoBgNXzK){JIhwosjbMy = true;}
      else if(RUWoBgNXzK == bCTwYMthSO){UytzGLRWsY = true;}
      if(lRSQmAGdlu == jUuHmRDEBB){eqEAojBEjY = true;}
      else if(jUuHmRDEBB == lRSQmAGdlu){ebbFTVulDx = true;}
      if(tbgACEgxBq == CdoaLNIqqE){LewEqfYrmz = true;}
      else if(CdoaLNIqqE == tbgACEgxBq){EpxpSBKoWO = true;}
      if(mpUQUXcVdM == ZdwoVNpDZs){rhVMTqGXlQ = true;}
      else if(ZdwoVNpDZs == mpUQUXcVdM){QgduepEwwy = true;}
      if(tAMfcOVSDY == LUUBjhOTVP){aRfLCppZxj = true;}
      else if(LUUBjhOTVP == tAMfcOVSDY){pUkVKDAMJa = true;}
      if(QNxAEzUStU == sOjCeneudn){ojpqSdLdFJ = true;}
      else if(sOjCeneudn == QNxAEzUStU){npOIBeBDgE = true;}
      if(exgaauxBwO == YVftjGYGlY){UqoNFwUqfx = true;}
      if(XjAYBtPAWm == azeHogImqc){dcSSyszjBA = true;}
      if(hNsbZZsTMU == znUbKKtsJg){oyuCKIreto = true;}
      while(YVftjGYGlY == exgaauxBwO){BcAdHxxfZd = true;}
      while(azeHogImqc == azeHogImqc){QzpEGiEafP = true;}
      while(znUbKKtsJg == znUbKKtsJg){BxfwaZRVtA = true;}
      if(huZlUpoZQd == true){huZlUpoZQd = false;}
      if(JIhwosjbMy == true){JIhwosjbMy = false;}
      if(eqEAojBEjY == true){eqEAojBEjY = false;}
      if(LewEqfYrmz == true){LewEqfYrmz = false;}
      if(rhVMTqGXlQ == true){rhVMTqGXlQ = false;}
      if(aRfLCppZxj == true){aRfLCppZxj = false;}
      if(ojpqSdLdFJ == true){ojpqSdLdFJ = false;}
      if(UqoNFwUqfx == true){UqoNFwUqfx = false;}
      if(dcSSyszjBA == true){dcSSyszjBA = false;}
      if(oyuCKIreto == true){oyuCKIreto = false;}
      if(ebRcwicSGF == true){ebRcwicSGF = false;}
      if(UytzGLRWsY == true){UytzGLRWsY = false;}
      if(ebbFTVulDx == true){ebbFTVulDx = false;}
      if(EpxpSBKoWO == true){EpxpSBKoWO = false;}
      if(QgduepEwwy == true){QgduepEwwy = false;}
      if(pUkVKDAMJa == true){pUkVKDAMJa = false;}
      if(npOIBeBDgE == true){npOIBeBDgE = false;}
      if(BcAdHxxfZd == true){BcAdHxxfZd = false;}
      if(QzpEGiEafP == true){QzpEGiEafP = false;}
      if(BxfwaZRVtA == true){BxfwaZRVtA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFAHFKYSDF
{ 
  void DNueixcrgN()
  { 
      bool QGSAFXQAbt = false;
      bool GLfaATkNgr = false;
      bool UXKpNREHzU = false;
      bool CpJOIExJME = false;
      bool UouCKWARjp = false;
      bool FfADcrwcmm = false;
      bool SJAHrQCQSu = false;
      bool WaBcWecIep = false;
      bool RlWJOVpGkQ = false;
      bool HTWYkKnmJs = false;
      bool UjznSddXfx = false;
      bool OnxwVflqsW = false;
      bool aueCnDDcqL = false;
      bool poylVgmiqj = false;
      bool qSZnBSWaDE = false;
      bool YxtlSYEwAP = false;
      bool aBfTGYoLZn = false;
      bool sDAIeIUqBU = false;
      bool fcYmmsuMTx = false;
      bool bpiaJolGgb = false;
      string kbHdIKpbmZ;
      string Ugnscnhfjz;
      string OHWKoRyTDN;
      string mXUNzXFQhn;
      string kVpYJCVIoU;
      string rzxVQdEwnq;
      string MWXZlwLasE;
      string iRxwNrQxBl;
      string uodiUnaywV;
      string TJbqaOyPlM;
      string quPklZBAIX;
      string MHuCuXroEy;
      string VMdWkZpFUz;
      string tBLnuzYswt;
      string lZpYJLNZuD;
      string WIKnqdRsAL;
      string jueJcLuGGu;
      string yyrKLwWFNY;
      string LPJRbkpXwQ;
      string hfskKqtguy;
      if(kbHdIKpbmZ == quPklZBAIX){QGSAFXQAbt = true;}
      else if(quPklZBAIX == kbHdIKpbmZ){UjznSddXfx = true;}
      if(Ugnscnhfjz == MHuCuXroEy){GLfaATkNgr = true;}
      else if(MHuCuXroEy == Ugnscnhfjz){OnxwVflqsW = true;}
      if(OHWKoRyTDN == VMdWkZpFUz){UXKpNREHzU = true;}
      else if(VMdWkZpFUz == OHWKoRyTDN){aueCnDDcqL = true;}
      if(mXUNzXFQhn == tBLnuzYswt){CpJOIExJME = true;}
      else if(tBLnuzYswt == mXUNzXFQhn){poylVgmiqj = true;}
      if(kVpYJCVIoU == lZpYJLNZuD){UouCKWARjp = true;}
      else if(lZpYJLNZuD == kVpYJCVIoU){qSZnBSWaDE = true;}
      if(rzxVQdEwnq == WIKnqdRsAL){FfADcrwcmm = true;}
      else if(WIKnqdRsAL == rzxVQdEwnq){YxtlSYEwAP = true;}
      if(MWXZlwLasE == jueJcLuGGu){SJAHrQCQSu = true;}
      else if(jueJcLuGGu == MWXZlwLasE){aBfTGYoLZn = true;}
      if(iRxwNrQxBl == yyrKLwWFNY){WaBcWecIep = true;}
      if(uodiUnaywV == LPJRbkpXwQ){RlWJOVpGkQ = true;}
      if(TJbqaOyPlM == hfskKqtguy){HTWYkKnmJs = true;}
      while(yyrKLwWFNY == iRxwNrQxBl){sDAIeIUqBU = true;}
      while(LPJRbkpXwQ == LPJRbkpXwQ){fcYmmsuMTx = true;}
      while(hfskKqtguy == hfskKqtguy){bpiaJolGgb = true;}
      if(QGSAFXQAbt == true){QGSAFXQAbt = false;}
      if(GLfaATkNgr == true){GLfaATkNgr = false;}
      if(UXKpNREHzU == true){UXKpNREHzU = false;}
      if(CpJOIExJME == true){CpJOIExJME = false;}
      if(UouCKWARjp == true){UouCKWARjp = false;}
      if(FfADcrwcmm == true){FfADcrwcmm = false;}
      if(SJAHrQCQSu == true){SJAHrQCQSu = false;}
      if(WaBcWecIep == true){WaBcWecIep = false;}
      if(RlWJOVpGkQ == true){RlWJOVpGkQ = false;}
      if(HTWYkKnmJs == true){HTWYkKnmJs = false;}
      if(UjznSddXfx == true){UjznSddXfx = false;}
      if(OnxwVflqsW == true){OnxwVflqsW = false;}
      if(aueCnDDcqL == true){aueCnDDcqL = false;}
      if(poylVgmiqj == true){poylVgmiqj = false;}
      if(qSZnBSWaDE == true){qSZnBSWaDE = false;}
      if(YxtlSYEwAP == true){YxtlSYEwAP = false;}
      if(aBfTGYoLZn == true){aBfTGYoLZn = false;}
      if(sDAIeIUqBU == true){sDAIeIUqBU = false;}
      if(fcYmmsuMTx == true){fcYmmsuMTx = false;}
      if(bpiaJolGgb == true){bpiaJolGgb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIPDASBGVP
{ 
  void gDLIgjpAJy()
  { 
      bool CzuHcNdpHp = false;
      bool dBqRoIrBmR = false;
      bool rCHQSAPHli = false;
      bool QophEasRfy = false;
      bool lJbhHVZQSD = false;
      bool SxRpHArdoc = false;
      bool xWEXYoKJNO = false;
      bool PZVofhZZJx = false;
      bool ZzohQTXAaD = false;
      bool iOcCAOEEIS = false;
      bool KQCDnrabJY = false;
      bool aRUrCyhWHE = false;
      bool QKhKfAwSnQ = false;
      bool dUQqlIwksX = false;
      bool rupCcQtkzC = false;
      bool ggwDBAirXn = false;
      bool uImstFBdFs = false;
      bool BwdjMVTegO = false;
      bool GLSljwYMpl = false;
      bool ZDNFbjIxHX = false;
      string OpsesphmmU;
      string mXpyqtILLu;
      string HrNeiVpzGh;
      string iruTxlBIfD;
      string CPDHXAKzYM;
      string lTVRkWbOwW;
      string zhgFktcWAF;
      string rAeHsrnGGh;
      string KpaswPWdha;
      string KmMIEThyVc;
      string XnzTUknNYr;
      string hVINLJGnIV;
      string XznZtEmWDY;
      string KpjcKWqHXK;
      string bIEprneywt;
      string MtoAFYzZYP;
      string xRKzhrleDo;
      string RzPysPtyhG;
      string ZoZILQAiXl;
      string WRiIMKyFHz;
      if(OpsesphmmU == XnzTUknNYr){CzuHcNdpHp = true;}
      else if(XnzTUknNYr == OpsesphmmU){KQCDnrabJY = true;}
      if(mXpyqtILLu == hVINLJGnIV){dBqRoIrBmR = true;}
      else if(hVINLJGnIV == mXpyqtILLu){aRUrCyhWHE = true;}
      if(HrNeiVpzGh == XznZtEmWDY){rCHQSAPHli = true;}
      else if(XznZtEmWDY == HrNeiVpzGh){QKhKfAwSnQ = true;}
      if(iruTxlBIfD == KpjcKWqHXK){QophEasRfy = true;}
      else if(KpjcKWqHXK == iruTxlBIfD){dUQqlIwksX = true;}
      if(CPDHXAKzYM == bIEprneywt){lJbhHVZQSD = true;}
      else if(bIEprneywt == CPDHXAKzYM){rupCcQtkzC = true;}
      if(lTVRkWbOwW == MtoAFYzZYP){SxRpHArdoc = true;}
      else if(MtoAFYzZYP == lTVRkWbOwW){ggwDBAirXn = true;}
      if(zhgFktcWAF == xRKzhrleDo){xWEXYoKJNO = true;}
      else if(xRKzhrleDo == zhgFktcWAF){uImstFBdFs = true;}
      if(rAeHsrnGGh == RzPysPtyhG){PZVofhZZJx = true;}
      if(KpaswPWdha == ZoZILQAiXl){ZzohQTXAaD = true;}
      if(KmMIEThyVc == WRiIMKyFHz){iOcCAOEEIS = true;}
      while(RzPysPtyhG == rAeHsrnGGh){BwdjMVTegO = true;}
      while(ZoZILQAiXl == ZoZILQAiXl){GLSljwYMpl = true;}
      while(WRiIMKyFHz == WRiIMKyFHz){ZDNFbjIxHX = true;}
      if(CzuHcNdpHp == true){CzuHcNdpHp = false;}
      if(dBqRoIrBmR == true){dBqRoIrBmR = false;}
      if(rCHQSAPHli == true){rCHQSAPHli = false;}
      if(QophEasRfy == true){QophEasRfy = false;}
      if(lJbhHVZQSD == true){lJbhHVZQSD = false;}
      if(SxRpHArdoc == true){SxRpHArdoc = false;}
      if(xWEXYoKJNO == true){xWEXYoKJNO = false;}
      if(PZVofhZZJx == true){PZVofhZZJx = false;}
      if(ZzohQTXAaD == true){ZzohQTXAaD = false;}
      if(iOcCAOEEIS == true){iOcCAOEEIS = false;}
      if(KQCDnrabJY == true){KQCDnrabJY = false;}
      if(aRUrCyhWHE == true){aRUrCyhWHE = false;}
      if(QKhKfAwSnQ == true){QKhKfAwSnQ = false;}
      if(dUQqlIwksX == true){dUQqlIwksX = false;}
      if(rupCcQtkzC == true){rupCcQtkzC = false;}
      if(ggwDBAirXn == true){ggwDBAirXn = false;}
      if(uImstFBdFs == true){uImstFBdFs = false;}
      if(BwdjMVTegO == true){BwdjMVTegO = false;}
      if(GLSljwYMpl == true){GLSljwYMpl = false;}
      if(ZDNFbjIxHX == true){ZDNFbjIxHX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UWMAWLCPPS
{ 
  void dadlHSxrke()
  { 
      bool kSrTgfQFcn = false;
      bool zoEMPHUVBW = false;
      bool EKjRLBWCDr = false;
      bool dhScaHrEbd = false;
      bool VVnVjPDoGw = false;
      bool kYegQahaIe = false;
      bool JNBkJRVbkI = false;
      bool PPtXAhVOhu = false;
      bool xgwHGFDlMA = false;
      bool ZQwwTHTDMR = false;
      bool sbDygUeGfh = false;
      bool ETsMhbRtdE = false;
      bool OjPkiyTxDr = false;
      bool OSCPBVdyak = false;
      bool awFdwFXjNr = false;
      bool pYYHDJMSOh = false;
      bool BgDmTkQdLM = false;
      bool yTTsdReknc = false;
      bool aijLCottLr = false;
      bool IKirisrSKK = false;
      string ZqicdIGRni;
      string osTOeschCA;
      string JyBmNlcgnO;
      string fpRmwXaHIq;
      string eFqfHwaSGw;
      string tbnxoapwPq;
      string fZdYDybgSH;
      string RVZLUDGUeR;
      string KKZqUDBUyU;
      string hdqQLEbRbI;
      string UtAzdXCcbk;
      string UUQxgUzlEA;
      string wGixZmeIzP;
      string bosVxQKaMx;
      string BXrMAMNsjq;
      string FoNbMNLCYp;
      string stdMIebtAQ;
      string JYYHzXNVxM;
      string ZkYIKlaQJi;
      string FIBWDGtfDU;
      if(ZqicdIGRni == UtAzdXCcbk){kSrTgfQFcn = true;}
      else if(UtAzdXCcbk == ZqicdIGRni){sbDygUeGfh = true;}
      if(osTOeschCA == UUQxgUzlEA){zoEMPHUVBW = true;}
      else if(UUQxgUzlEA == osTOeschCA){ETsMhbRtdE = true;}
      if(JyBmNlcgnO == wGixZmeIzP){EKjRLBWCDr = true;}
      else if(wGixZmeIzP == JyBmNlcgnO){OjPkiyTxDr = true;}
      if(fpRmwXaHIq == bosVxQKaMx){dhScaHrEbd = true;}
      else if(bosVxQKaMx == fpRmwXaHIq){OSCPBVdyak = true;}
      if(eFqfHwaSGw == BXrMAMNsjq){VVnVjPDoGw = true;}
      else if(BXrMAMNsjq == eFqfHwaSGw){awFdwFXjNr = true;}
      if(tbnxoapwPq == FoNbMNLCYp){kYegQahaIe = true;}
      else if(FoNbMNLCYp == tbnxoapwPq){pYYHDJMSOh = true;}
      if(fZdYDybgSH == stdMIebtAQ){JNBkJRVbkI = true;}
      else if(stdMIebtAQ == fZdYDybgSH){BgDmTkQdLM = true;}
      if(RVZLUDGUeR == JYYHzXNVxM){PPtXAhVOhu = true;}
      if(KKZqUDBUyU == ZkYIKlaQJi){xgwHGFDlMA = true;}
      if(hdqQLEbRbI == FIBWDGtfDU){ZQwwTHTDMR = true;}
      while(JYYHzXNVxM == RVZLUDGUeR){yTTsdReknc = true;}
      while(ZkYIKlaQJi == ZkYIKlaQJi){aijLCottLr = true;}
      while(FIBWDGtfDU == FIBWDGtfDU){IKirisrSKK = true;}
      if(kSrTgfQFcn == true){kSrTgfQFcn = false;}
      if(zoEMPHUVBW == true){zoEMPHUVBW = false;}
      if(EKjRLBWCDr == true){EKjRLBWCDr = false;}
      if(dhScaHrEbd == true){dhScaHrEbd = false;}
      if(VVnVjPDoGw == true){VVnVjPDoGw = false;}
      if(kYegQahaIe == true){kYegQahaIe = false;}
      if(JNBkJRVbkI == true){JNBkJRVbkI = false;}
      if(PPtXAhVOhu == true){PPtXAhVOhu = false;}
      if(xgwHGFDlMA == true){xgwHGFDlMA = false;}
      if(ZQwwTHTDMR == true){ZQwwTHTDMR = false;}
      if(sbDygUeGfh == true){sbDygUeGfh = false;}
      if(ETsMhbRtdE == true){ETsMhbRtdE = false;}
      if(OjPkiyTxDr == true){OjPkiyTxDr = false;}
      if(OSCPBVdyak == true){OSCPBVdyak = false;}
      if(awFdwFXjNr == true){awFdwFXjNr = false;}
      if(pYYHDJMSOh == true){pYYHDJMSOh = false;}
      if(BgDmTkQdLM == true){BgDmTkQdLM = false;}
      if(yTTsdReknc == true){yTTsdReknc = false;}
      if(aijLCottLr == true){aijLCottLr = false;}
      if(IKirisrSKK == true){IKirisrSKK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWTMPOXLSD
{ 
  void qmxFShawOr()
  { 
      bool JlaUOEqoNU = false;
      bool YxZwtGlzCt = false;
      bool dBLYKwobGy = false;
      bool HSDORZsreN = false;
      bool bPrMfanKnl = false;
      bool qHAGGIZBJR = false;
      bool OOiPNFtLeT = false;
      bool MtUnSOIzsj = false;
      bool IenTHASwIJ = false;
      bool ArhMzMfcya = false;
      bool fbeTZxmLnr = false;
      bool zaIZJjaPHN = false;
      bool lyCVTULHoF = false;
      bool heASDfzTtK = false;
      bool MGHQJZiIDO = false;
      bool kQUknhZJAE = false;
      bool keWiJTZoVc = false;
      bool jHUxAfqlLt = false;
      bool kDEZTQKOeV = false;
      bool GpSoYhjXGo = false;
      string UoILxTrPIp;
      string iClojBGysl;
      string YqphqqoYYX;
      string oLsPZUQBTD;
      string twqwTAsIei;
      string EuBfNcyZTG;
      string eTqkAXIVPO;
      string jFdprbAsNq;
      string xgsoStKMBw;
      string WqgMXZFGww;
      string qWrPzzQKnk;
      string cFLcJyZBRF;
      string NwUSrrYQSS;
      string WsxRzZndpT;
      string dzYPTRfEDY;
      string ADnpiuCZWG;
      string azrUOiHtci;
      string KwLybNWEza;
      string MUNsSTFGhE;
      string XOGirdGDBj;
      if(UoILxTrPIp == qWrPzzQKnk){JlaUOEqoNU = true;}
      else if(qWrPzzQKnk == UoILxTrPIp){fbeTZxmLnr = true;}
      if(iClojBGysl == cFLcJyZBRF){YxZwtGlzCt = true;}
      else if(cFLcJyZBRF == iClojBGysl){zaIZJjaPHN = true;}
      if(YqphqqoYYX == NwUSrrYQSS){dBLYKwobGy = true;}
      else if(NwUSrrYQSS == YqphqqoYYX){lyCVTULHoF = true;}
      if(oLsPZUQBTD == WsxRzZndpT){HSDORZsreN = true;}
      else if(WsxRzZndpT == oLsPZUQBTD){heASDfzTtK = true;}
      if(twqwTAsIei == dzYPTRfEDY){bPrMfanKnl = true;}
      else if(dzYPTRfEDY == twqwTAsIei){MGHQJZiIDO = true;}
      if(EuBfNcyZTG == ADnpiuCZWG){qHAGGIZBJR = true;}
      else if(ADnpiuCZWG == EuBfNcyZTG){kQUknhZJAE = true;}
      if(eTqkAXIVPO == azrUOiHtci){OOiPNFtLeT = true;}
      else if(azrUOiHtci == eTqkAXIVPO){keWiJTZoVc = true;}
      if(jFdprbAsNq == KwLybNWEza){MtUnSOIzsj = true;}
      if(xgsoStKMBw == MUNsSTFGhE){IenTHASwIJ = true;}
      if(WqgMXZFGww == XOGirdGDBj){ArhMzMfcya = true;}
      while(KwLybNWEza == jFdprbAsNq){jHUxAfqlLt = true;}
      while(MUNsSTFGhE == MUNsSTFGhE){kDEZTQKOeV = true;}
      while(XOGirdGDBj == XOGirdGDBj){GpSoYhjXGo = true;}
      if(JlaUOEqoNU == true){JlaUOEqoNU = false;}
      if(YxZwtGlzCt == true){YxZwtGlzCt = false;}
      if(dBLYKwobGy == true){dBLYKwobGy = false;}
      if(HSDORZsreN == true){HSDORZsreN = false;}
      if(bPrMfanKnl == true){bPrMfanKnl = false;}
      if(qHAGGIZBJR == true){qHAGGIZBJR = false;}
      if(OOiPNFtLeT == true){OOiPNFtLeT = false;}
      if(MtUnSOIzsj == true){MtUnSOIzsj = false;}
      if(IenTHASwIJ == true){IenTHASwIJ = false;}
      if(ArhMzMfcya == true){ArhMzMfcya = false;}
      if(fbeTZxmLnr == true){fbeTZxmLnr = false;}
      if(zaIZJjaPHN == true){zaIZJjaPHN = false;}
      if(lyCVTULHoF == true){lyCVTULHoF = false;}
      if(heASDfzTtK == true){heASDfzTtK = false;}
      if(MGHQJZiIDO == true){MGHQJZiIDO = false;}
      if(kQUknhZJAE == true){kQUknhZJAE = false;}
      if(keWiJTZoVc == true){keWiJTZoVc = false;}
      if(jHUxAfqlLt == true){jHUxAfqlLt = false;}
      if(kDEZTQKOeV == true){kDEZTQKOeV = false;}
      if(GpSoYhjXGo == true){GpSoYhjXGo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEDRMXZJCM
{ 
  void kbkymGmKsh()
  { 
      bool YdOryeZmGK = false;
      bool YWHSaFuJPY = false;
      bool PgWnPtXfnx = false;
      bool YHYRhhfYgl = false;
      bool JLhFgtQMqN = false;
      bool nKCzgqHZcD = false;
      bool GtzIkQyojs = false;
      bool YWcdPDzQGU = false;
      bool dLnZJOEYkp = false;
      bool aFwcePMYTQ = false;
      bool wabynRhYjc = false;
      bool rpTHYuFZzW = false;
      bool LZDtRTZzzA = false;
      bool qZwpYDjpkq = false;
      bool ffoIyjloEi = false;
      bool JmZwEVXgfU = false;
      bool qiZilRschV = false;
      bool LOnHqfkuwh = false;
      bool hkuPpEAzkC = false;
      bool fCKQzxFFWf = false;
      string ExNkXkjJfe;
      string GDUoiJwoHO;
      string cfBeHPhylj;
      string uIyrsoHkCg;
      string awQDEdcrTR;
      string NrMTuXwhcH;
      string ClWwiyEbus;
      string CKlanfOxad;
      string mpeUVDuewU;
      string rYHtdoZUUG;
      string YAwZPDFleO;
      string JyHzUMHCZf;
      string CZeZAcDqwy;
      string GtcUEmsEES;
      string xJzhLtQIZQ;
      string hWtnDzUVYm;
      string zNogIOVmth;
      string SCxHhsaxOG;
      string LtRfQiznQF;
      string RXeRSjTSYw;
      if(ExNkXkjJfe == YAwZPDFleO){YdOryeZmGK = true;}
      else if(YAwZPDFleO == ExNkXkjJfe){wabynRhYjc = true;}
      if(GDUoiJwoHO == JyHzUMHCZf){YWHSaFuJPY = true;}
      else if(JyHzUMHCZf == GDUoiJwoHO){rpTHYuFZzW = true;}
      if(cfBeHPhylj == CZeZAcDqwy){PgWnPtXfnx = true;}
      else if(CZeZAcDqwy == cfBeHPhylj){LZDtRTZzzA = true;}
      if(uIyrsoHkCg == GtcUEmsEES){YHYRhhfYgl = true;}
      else if(GtcUEmsEES == uIyrsoHkCg){qZwpYDjpkq = true;}
      if(awQDEdcrTR == xJzhLtQIZQ){JLhFgtQMqN = true;}
      else if(xJzhLtQIZQ == awQDEdcrTR){ffoIyjloEi = true;}
      if(NrMTuXwhcH == hWtnDzUVYm){nKCzgqHZcD = true;}
      else if(hWtnDzUVYm == NrMTuXwhcH){JmZwEVXgfU = true;}
      if(ClWwiyEbus == zNogIOVmth){GtzIkQyojs = true;}
      else if(zNogIOVmth == ClWwiyEbus){qiZilRschV = true;}
      if(CKlanfOxad == SCxHhsaxOG){YWcdPDzQGU = true;}
      if(mpeUVDuewU == LtRfQiznQF){dLnZJOEYkp = true;}
      if(rYHtdoZUUG == RXeRSjTSYw){aFwcePMYTQ = true;}
      while(SCxHhsaxOG == CKlanfOxad){LOnHqfkuwh = true;}
      while(LtRfQiznQF == LtRfQiznQF){hkuPpEAzkC = true;}
      while(RXeRSjTSYw == RXeRSjTSYw){fCKQzxFFWf = true;}
      if(YdOryeZmGK == true){YdOryeZmGK = false;}
      if(YWHSaFuJPY == true){YWHSaFuJPY = false;}
      if(PgWnPtXfnx == true){PgWnPtXfnx = false;}
      if(YHYRhhfYgl == true){YHYRhhfYgl = false;}
      if(JLhFgtQMqN == true){JLhFgtQMqN = false;}
      if(nKCzgqHZcD == true){nKCzgqHZcD = false;}
      if(GtzIkQyojs == true){GtzIkQyojs = false;}
      if(YWcdPDzQGU == true){YWcdPDzQGU = false;}
      if(dLnZJOEYkp == true){dLnZJOEYkp = false;}
      if(aFwcePMYTQ == true){aFwcePMYTQ = false;}
      if(wabynRhYjc == true){wabynRhYjc = false;}
      if(rpTHYuFZzW == true){rpTHYuFZzW = false;}
      if(LZDtRTZzzA == true){LZDtRTZzzA = false;}
      if(qZwpYDjpkq == true){qZwpYDjpkq = false;}
      if(ffoIyjloEi == true){ffoIyjloEi = false;}
      if(JmZwEVXgfU == true){JmZwEVXgfU = false;}
      if(qiZilRschV == true){qiZilRschV = false;}
      if(LOnHqfkuwh == true){LOnHqfkuwh = false;}
      if(hkuPpEAzkC == true){hkuPpEAzkC = false;}
      if(fCKQzxFFWf == true){fCKQzxFFWf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFCSRAXYAQ
{ 
  void wcWsPpTtxx()
  { 
      bool IAwxZsSnqQ = false;
      bool DillmGIjTA = false;
      bool HDMDViesAx = false;
      bool XZrqPsBiuY = false;
      bool swOazAibLy = false;
      bool ANNDnFnsap = false;
      bool OYnssdquWs = false;
      bool FZouHKnlDU = false;
      bool AChCwKMnDJ = false;
      bool FHHEKTIUhV = false;
      bool JnFRsZYRwd = false;
      bool QBoGpMqkxi = false;
      bool RCrNnxSjkn = false;
      bool BTEhLMxPJV = false;
      bool ktrZrDRAOy = false;
      bool bWXzDGuqdu = false;
      bool HogIbxxHud = false;
      bool OabaxXKSUj = false;
      bool eRUmLewEdE = false;
      bool QFlNNwMjxu = false;
      string zDXDlfnQaf;
      string kDtQMGYKHM;
      string YilteIitfu;
      string DzPkctSyCb;
      string BTqfAbBnST;
      string ffmDmQRdYc;
      string wtkfclnJmR;
      string naIfLFqGsC;
      string HuaMPWLLxM;
      string coZYeGiLDO;
      string mqAAfFXGqh;
      string YLjVVATXQF;
      string abLaoyAiAF;
      string VfCeOPuZfJ;
      string yETPnQEDDe;
      string mKuxmLeZKg;
      string EoGlLrIEGF;
      string EsrGGVHwmX;
      string txfVRLkFrD;
      string jVOyFJyhDu;
      if(zDXDlfnQaf == mqAAfFXGqh){IAwxZsSnqQ = true;}
      else if(mqAAfFXGqh == zDXDlfnQaf){JnFRsZYRwd = true;}
      if(kDtQMGYKHM == YLjVVATXQF){DillmGIjTA = true;}
      else if(YLjVVATXQF == kDtQMGYKHM){QBoGpMqkxi = true;}
      if(YilteIitfu == abLaoyAiAF){HDMDViesAx = true;}
      else if(abLaoyAiAF == YilteIitfu){RCrNnxSjkn = true;}
      if(DzPkctSyCb == VfCeOPuZfJ){XZrqPsBiuY = true;}
      else if(VfCeOPuZfJ == DzPkctSyCb){BTEhLMxPJV = true;}
      if(BTqfAbBnST == yETPnQEDDe){swOazAibLy = true;}
      else if(yETPnQEDDe == BTqfAbBnST){ktrZrDRAOy = true;}
      if(ffmDmQRdYc == mKuxmLeZKg){ANNDnFnsap = true;}
      else if(mKuxmLeZKg == ffmDmQRdYc){bWXzDGuqdu = true;}
      if(wtkfclnJmR == EoGlLrIEGF){OYnssdquWs = true;}
      else if(EoGlLrIEGF == wtkfclnJmR){HogIbxxHud = true;}
      if(naIfLFqGsC == EsrGGVHwmX){FZouHKnlDU = true;}
      if(HuaMPWLLxM == txfVRLkFrD){AChCwKMnDJ = true;}
      if(coZYeGiLDO == jVOyFJyhDu){FHHEKTIUhV = true;}
      while(EsrGGVHwmX == naIfLFqGsC){OabaxXKSUj = true;}
      while(txfVRLkFrD == txfVRLkFrD){eRUmLewEdE = true;}
      while(jVOyFJyhDu == jVOyFJyhDu){QFlNNwMjxu = true;}
      if(IAwxZsSnqQ == true){IAwxZsSnqQ = false;}
      if(DillmGIjTA == true){DillmGIjTA = false;}
      if(HDMDViesAx == true){HDMDViesAx = false;}
      if(XZrqPsBiuY == true){XZrqPsBiuY = false;}
      if(swOazAibLy == true){swOazAibLy = false;}
      if(ANNDnFnsap == true){ANNDnFnsap = false;}
      if(OYnssdquWs == true){OYnssdquWs = false;}
      if(FZouHKnlDU == true){FZouHKnlDU = false;}
      if(AChCwKMnDJ == true){AChCwKMnDJ = false;}
      if(FHHEKTIUhV == true){FHHEKTIUhV = false;}
      if(JnFRsZYRwd == true){JnFRsZYRwd = false;}
      if(QBoGpMqkxi == true){QBoGpMqkxi = false;}
      if(RCrNnxSjkn == true){RCrNnxSjkn = false;}
      if(BTEhLMxPJV == true){BTEhLMxPJV = false;}
      if(ktrZrDRAOy == true){ktrZrDRAOy = false;}
      if(bWXzDGuqdu == true){bWXzDGuqdu = false;}
      if(HogIbxxHud == true){HogIbxxHud = false;}
      if(OabaxXKSUj == true){OabaxXKSUj = false;}
      if(eRUmLewEdE == true){eRUmLewEdE = false;}
      if(QFlNNwMjxu == true){QFlNNwMjxu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJBQENVEFU
{ 
  void uHIzGfrfNM()
  { 
      bool VpqjiGsaZs = false;
      bool FDGllIWeax = false;
      bool eVQdDPUxqM = false;
      bool nwbshDicTP = false;
      bool DJlFfRipdc = false;
      bool ROcEXAZNfT = false;
      bool kwjNEJbMEi = false;
      bool YtKKtViKxk = false;
      bool fdTOtYSXVg = false;
      bool dVwzeHYYAV = false;
      bool pWluEXDSJC = false;
      bool ROPtnGbVSf = false;
      bool qEqWECxLfm = false;
      bool wJJauJrYJV = false;
      bool VANSPOGBLX = false;
      bool eCFUekePpB = false;
      bool armVFHFnze = false;
      bool ODLxJppXGp = false;
      bool uuzHIsEnwJ = false;
      bool dbhIudNqMI = false;
      string JMweYVqmXu;
      string JPczdmJfVC;
      string RRxzalNFCr;
      string qBqJNrrPYs;
      string GzdGqdaDla;
      string JMBSPqOxDm;
      string HkjeEHYTkl;
      string usHcuSmqIx;
      string KKTbidzXsW;
      string cuMkkVPzCi;
      string FHRAfPFYWx;
      string DXoGbxRIuZ;
      string IAZOJzgVqZ;
      string DnoYqDrTuT;
      string YaAwSFFGIn;
      string EGDbZFgCpf;
      string ijgwtPiPOY;
      string EyMbBgzdwE;
      string saMCVwkMzk;
      string VocPkosDBC;
      if(JMweYVqmXu == FHRAfPFYWx){VpqjiGsaZs = true;}
      else if(FHRAfPFYWx == JMweYVqmXu){pWluEXDSJC = true;}
      if(JPczdmJfVC == DXoGbxRIuZ){FDGllIWeax = true;}
      else if(DXoGbxRIuZ == JPczdmJfVC){ROPtnGbVSf = true;}
      if(RRxzalNFCr == IAZOJzgVqZ){eVQdDPUxqM = true;}
      else if(IAZOJzgVqZ == RRxzalNFCr){qEqWECxLfm = true;}
      if(qBqJNrrPYs == DnoYqDrTuT){nwbshDicTP = true;}
      else if(DnoYqDrTuT == qBqJNrrPYs){wJJauJrYJV = true;}
      if(GzdGqdaDla == YaAwSFFGIn){DJlFfRipdc = true;}
      else if(YaAwSFFGIn == GzdGqdaDla){VANSPOGBLX = true;}
      if(JMBSPqOxDm == EGDbZFgCpf){ROcEXAZNfT = true;}
      else if(EGDbZFgCpf == JMBSPqOxDm){eCFUekePpB = true;}
      if(HkjeEHYTkl == ijgwtPiPOY){kwjNEJbMEi = true;}
      else if(ijgwtPiPOY == HkjeEHYTkl){armVFHFnze = true;}
      if(usHcuSmqIx == EyMbBgzdwE){YtKKtViKxk = true;}
      if(KKTbidzXsW == saMCVwkMzk){fdTOtYSXVg = true;}
      if(cuMkkVPzCi == VocPkosDBC){dVwzeHYYAV = true;}
      while(EyMbBgzdwE == usHcuSmqIx){ODLxJppXGp = true;}
      while(saMCVwkMzk == saMCVwkMzk){uuzHIsEnwJ = true;}
      while(VocPkosDBC == VocPkosDBC){dbhIudNqMI = true;}
      if(VpqjiGsaZs == true){VpqjiGsaZs = false;}
      if(FDGllIWeax == true){FDGllIWeax = false;}
      if(eVQdDPUxqM == true){eVQdDPUxqM = false;}
      if(nwbshDicTP == true){nwbshDicTP = false;}
      if(DJlFfRipdc == true){DJlFfRipdc = false;}
      if(ROcEXAZNfT == true){ROcEXAZNfT = false;}
      if(kwjNEJbMEi == true){kwjNEJbMEi = false;}
      if(YtKKtViKxk == true){YtKKtViKxk = false;}
      if(fdTOtYSXVg == true){fdTOtYSXVg = false;}
      if(dVwzeHYYAV == true){dVwzeHYYAV = false;}
      if(pWluEXDSJC == true){pWluEXDSJC = false;}
      if(ROPtnGbVSf == true){ROPtnGbVSf = false;}
      if(qEqWECxLfm == true){qEqWECxLfm = false;}
      if(wJJauJrYJV == true){wJJauJrYJV = false;}
      if(VANSPOGBLX == true){VANSPOGBLX = false;}
      if(eCFUekePpB == true){eCFUekePpB = false;}
      if(armVFHFnze == true){armVFHFnze = false;}
      if(ODLxJppXGp == true){ODLxJppXGp = false;}
      if(uuzHIsEnwJ == true){uuzHIsEnwJ = false;}
      if(dbhIudNqMI == true){dbhIudNqMI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDHCMDQIMU
{ 
  void pcNUDOlton()
  { 
      bool IfbTtsNFjX = false;
      bool cJhwlVpjQZ = false;
      bool bgnjrJXgeW = false;
      bool YngbeEfcwj = false;
      bool RspQJjeiyc = false;
      bool QaZEMarrak = false;
      bool UfaNznbGQg = false;
      bool pNnfIiqWZH = false;
      bool eniBGxNcPE = false;
      bool MnBKPkScRV = false;
      bool IYSRmDmsuc = false;
      bool jUSSFfxYHB = false;
      bool ZzpMTCLcQW = false;
      bool QNFDzGVQOC = false;
      bool KUglTqUhFi = false;
      bool nsVPuIhFxk = false;
      bool rJbYMVPOTz = false;
      bool JfKEqFSErc = false;
      bool gcXhiXqpIp = false;
      bool YPTcKArHZy = false;
      string jspOWNbYyk;
      string zzYaIMfxkb;
      string VuSqYpkHXZ;
      string fKXdQohHnc;
      string jGRqRCKqGx;
      string KxpOenZyog;
      string cTAYFoatKS;
      string dYJHqPcbYW;
      string esBaPhTJzb;
      string OiRHAPFslc;
      string aQgmSknhWP;
      string LyZSBiSZIX;
      string URuhDuGCHb;
      string KjpwuOMOId;
      string skljQQJyFQ;
      string xejOHIUziX;
      string dlauFbIcWl;
      string WDRedifLQm;
      string kHwpdezaom;
      string tMejzGKqeo;
      if(jspOWNbYyk == aQgmSknhWP){IfbTtsNFjX = true;}
      else if(aQgmSknhWP == jspOWNbYyk){IYSRmDmsuc = true;}
      if(zzYaIMfxkb == LyZSBiSZIX){cJhwlVpjQZ = true;}
      else if(LyZSBiSZIX == zzYaIMfxkb){jUSSFfxYHB = true;}
      if(VuSqYpkHXZ == URuhDuGCHb){bgnjrJXgeW = true;}
      else if(URuhDuGCHb == VuSqYpkHXZ){ZzpMTCLcQW = true;}
      if(fKXdQohHnc == KjpwuOMOId){YngbeEfcwj = true;}
      else if(KjpwuOMOId == fKXdQohHnc){QNFDzGVQOC = true;}
      if(jGRqRCKqGx == skljQQJyFQ){RspQJjeiyc = true;}
      else if(skljQQJyFQ == jGRqRCKqGx){KUglTqUhFi = true;}
      if(KxpOenZyog == xejOHIUziX){QaZEMarrak = true;}
      else if(xejOHIUziX == KxpOenZyog){nsVPuIhFxk = true;}
      if(cTAYFoatKS == dlauFbIcWl){UfaNznbGQg = true;}
      else if(dlauFbIcWl == cTAYFoatKS){rJbYMVPOTz = true;}
      if(dYJHqPcbYW == WDRedifLQm){pNnfIiqWZH = true;}
      if(esBaPhTJzb == kHwpdezaom){eniBGxNcPE = true;}
      if(OiRHAPFslc == tMejzGKqeo){MnBKPkScRV = true;}
      while(WDRedifLQm == dYJHqPcbYW){JfKEqFSErc = true;}
      while(kHwpdezaom == kHwpdezaom){gcXhiXqpIp = true;}
      while(tMejzGKqeo == tMejzGKqeo){YPTcKArHZy = true;}
      if(IfbTtsNFjX == true){IfbTtsNFjX = false;}
      if(cJhwlVpjQZ == true){cJhwlVpjQZ = false;}
      if(bgnjrJXgeW == true){bgnjrJXgeW = false;}
      if(YngbeEfcwj == true){YngbeEfcwj = false;}
      if(RspQJjeiyc == true){RspQJjeiyc = false;}
      if(QaZEMarrak == true){QaZEMarrak = false;}
      if(UfaNznbGQg == true){UfaNznbGQg = false;}
      if(pNnfIiqWZH == true){pNnfIiqWZH = false;}
      if(eniBGxNcPE == true){eniBGxNcPE = false;}
      if(MnBKPkScRV == true){MnBKPkScRV = false;}
      if(IYSRmDmsuc == true){IYSRmDmsuc = false;}
      if(jUSSFfxYHB == true){jUSSFfxYHB = false;}
      if(ZzpMTCLcQW == true){ZzpMTCLcQW = false;}
      if(QNFDzGVQOC == true){QNFDzGVQOC = false;}
      if(KUglTqUhFi == true){KUglTqUhFi = false;}
      if(nsVPuIhFxk == true){nsVPuIhFxk = false;}
      if(rJbYMVPOTz == true){rJbYMVPOTz = false;}
      if(JfKEqFSErc == true){JfKEqFSErc = false;}
      if(gcXhiXqpIp == true){gcXhiXqpIp = false;}
      if(YPTcKArHZy == true){YPTcKArHZy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGZKTATKCI
{ 
  void kWlprIrhiF()
  { 
      bool ANSMMOCPsO = false;
      bool ZYNnOXnmUD = false;
      bool lrqsjfkLGj = false;
      bool fOUGjJYyjn = false;
      bool mZSYHTfGAg = false;
      bool eQuYdIWYcf = false;
      bool dqJIiLEHEF = false;
      bool zoCfQMYRkQ = false;
      bool AdLYFPTuba = false;
      bool lzUEKuPJpu = false;
      bool OXBthoOOIR = false;
      bool iEnLezfjDS = false;
      bool rIfdSAUxVU = false;
      bool wOboBbcQqQ = false;
      bool AEmJqgKIYK = false;
      bool PfGWDGrXbg = false;
      bool UQsmVUcyKD = false;
      bool WOrlSmVVlk = false;
      bool oLYKEQHFlu = false;
      bool iEoJwiKznW = false;
      string oTidNKtMGs;
      string eHbxSKRbxa;
      string HaeIIJcJhI;
      string FAdVyIjboX;
      string fjEEAAzzZd;
      string omsSkNoZVE;
      string gjeymecGzK;
      string aplZuXVaII;
      string JdjDSSHLjj;
      string TKGkpuEGQV;
      string WszPCzATXN;
      string qORMtDAaeU;
      string WRVOpQjBjz;
      string SPJllQdTBT;
      string RmnWrFsspl;
      string ucawyEXjYl;
      string OzjXtaEeac;
      string ZfZLDjdyWj;
      string XqLxDpoMnh;
      string ssuOESDPcQ;
      if(oTidNKtMGs == WszPCzATXN){ANSMMOCPsO = true;}
      else if(WszPCzATXN == oTidNKtMGs){OXBthoOOIR = true;}
      if(eHbxSKRbxa == qORMtDAaeU){ZYNnOXnmUD = true;}
      else if(qORMtDAaeU == eHbxSKRbxa){iEnLezfjDS = true;}
      if(HaeIIJcJhI == WRVOpQjBjz){lrqsjfkLGj = true;}
      else if(WRVOpQjBjz == HaeIIJcJhI){rIfdSAUxVU = true;}
      if(FAdVyIjboX == SPJllQdTBT){fOUGjJYyjn = true;}
      else if(SPJllQdTBT == FAdVyIjboX){wOboBbcQqQ = true;}
      if(fjEEAAzzZd == RmnWrFsspl){mZSYHTfGAg = true;}
      else if(RmnWrFsspl == fjEEAAzzZd){AEmJqgKIYK = true;}
      if(omsSkNoZVE == ucawyEXjYl){eQuYdIWYcf = true;}
      else if(ucawyEXjYl == omsSkNoZVE){PfGWDGrXbg = true;}
      if(gjeymecGzK == OzjXtaEeac){dqJIiLEHEF = true;}
      else if(OzjXtaEeac == gjeymecGzK){UQsmVUcyKD = true;}
      if(aplZuXVaII == ZfZLDjdyWj){zoCfQMYRkQ = true;}
      if(JdjDSSHLjj == XqLxDpoMnh){AdLYFPTuba = true;}
      if(TKGkpuEGQV == ssuOESDPcQ){lzUEKuPJpu = true;}
      while(ZfZLDjdyWj == aplZuXVaII){WOrlSmVVlk = true;}
      while(XqLxDpoMnh == XqLxDpoMnh){oLYKEQHFlu = true;}
      while(ssuOESDPcQ == ssuOESDPcQ){iEoJwiKznW = true;}
      if(ANSMMOCPsO == true){ANSMMOCPsO = false;}
      if(ZYNnOXnmUD == true){ZYNnOXnmUD = false;}
      if(lrqsjfkLGj == true){lrqsjfkLGj = false;}
      if(fOUGjJYyjn == true){fOUGjJYyjn = false;}
      if(mZSYHTfGAg == true){mZSYHTfGAg = false;}
      if(eQuYdIWYcf == true){eQuYdIWYcf = false;}
      if(dqJIiLEHEF == true){dqJIiLEHEF = false;}
      if(zoCfQMYRkQ == true){zoCfQMYRkQ = false;}
      if(AdLYFPTuba == true){AdLYFPTuba = false;}
      if(lzUEKuPJpu == true){lzUEKuPJpu = false;}
      if(OXBthoOOIR == true){OXBthoOOIR = false;}
      if(iEnLezfjDS == true){iEnLezfjDS = false;}
      if(rIfdSAUxVU == true){rIfdSAUxVU = false;}
      if(wOboBbcQqQ == true){wOboBbcQqQ = false;}
      if(AEmJqgKIYK == true){AEmJqgKIYK = false;}
      if(PfGWDGrXbg == true){PfGWDGrXbg = false;}
      if(UQsmVUcyKD == true){UQsmVUcyKD = false;}
      if(WOrlSmVVlk == true){WOrlSmVVlk = false;}
      if(oLYKEQHFlu == true){oLYKEQHFlu = false;}
      if(iEoJwiKznW == true){iEoJwiKznW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSFJXXVYKU
{ 
  void TracDPccdm()
  { 
      bool ftlqypggMK = false;
      bool jwkxcouofg = false;
      bool amyxElnZDm = false;
      bool XNnGENySZF = false;
      bool PDCFPdbeWI = false;
      bool RnfFJrwolM = false;
      bool BGcZmWHesO = false;
      bool qcPZQWkrhZ = false;
      bool JJCuUigixL = false;
      bool RJfMEJabSr = false;
      bool WxkIQoYFnl = false;
      bool HDGLCqEgFE = false;
      bool oYhgwhwCVH = false;
      bool wIZoDMXtde = false;
      bool JatKEOCTJN = false;
      bool FsWODxPELi = false;
      bool rVjfpycRIp = false;
      bool SJCZtNdXch = false;
      bool fcrHCCkLlF = false;
      bool wThulnqNTF = false;
      string eywtSYoLOp;
      string CXAnmwBbuN;
      string sZJSyZdyKX;
      string UcnGdEdnti;
      string aUyBhLKYkU;
      string GRxSGEocus;
      string tpBpVZjsKi;
      string RMgLmXaIkl;
      string PENoQDeUAY;
      string OArAojTHfH;
      string aQOCCsklei;
      string dfqIdpcMYR;
      string uPslTRTfWD;
      string ESccLypLlX;
      string RsoRuiIjWy;
      string HHiNMLXbhk;
      string ZEObdKDOxe;
      string zRZBACaaqj;
      string IjJYuxjPQA;
      string aNcAxNdMmj;
      if(eywtSYoLOp == aQOCCsklei){ftlqypggMK = true;}
      else if(aQOCCsklei == eywtSYoLOp){WxkIQoYFnl = true;}
      if(CXAnmwBbuN == dfqIdpcMYR){jwkxcouofg = true;}
      else if(dfqIdpcMYR == CXAnmwBbuN){HDGLCqEgFE = true;}
      if(sZJSyZdyKX == uPslTRTfWD){amyxElnZDm = true;}
      else if(uPslTRTfWD == sZJSyZdyKX){oYhgwhwCVH = true;}
      if(UcnGdEdnti == ESccLypLlX){XNnGENySZF = true;}
      else if(ESccLypLlX == UcnGdEdnti){wIZoDMXtde = true;}
      if(aUyBhLKYkU == RsoRuiIjWy){PDCFPdbeWI = true;}
      else if(RsoRuiIjWy == aUyBhLKYkU){JatKEOCTJN = true;}
      if(GRxSGEocus == HHiNMLXbhk){RnfFJrwolM = true;}
      else if(HHiNMLXbhk == GRxSGEocus){FsWODxPELi = true;}
      if(tpBpVZjsKi == ZEObdKDOxe){BGcZmWHesO = true;}
      else if(ZEObdKDOxe == tpBpVZjsKi){rVjfpycRIp = true;}
      if(RMgLmXaIkl == zRZBACaaqj){qcPZQWkrhZ = true;}
      if(PENoQDeUAY == IjJYuxjPQA){JJCuUigixL = true;}
      if(OArAojTHfH == aNcAxNdMmj){RJfMEJabSr = true;}
      while(zRZBACaaqj == RMgLmXaIkl){SJCZtNdXch = true;}
      while(IjJYuxjPQA == IjJYuxjPQA){fcrHCCkLlF = true;}
      while(aNcAxNdMmj == aNcAxNdMmj){wThulnqNTF = true;}
      if(ftlqypggMK == true){ftlqypggMK = false;}
      if(jwkxcouofg == true){jwkxcouofg = false;}
      if(amyxElnZDm == true){amyxElnZDm = false;}
      if(XNnGENySZF == true){XNnGENySZF = false;}
      if(PDCFPdbeWI == true){PDCFPdbeWI = false;}
      if(RnfFJrwolM == true){RnfFJrwolM = false;}
      if(BGcZmWHesO == true){BGcZmWHesO = false;}
      if(qcPZQWkrhZ == true){qcPZQWkrhZ = false;}
      if(JJCuUigixL == true){JJCuUigixL = false;}
      if(RJfMEJabSr == true){RJfMEJabSr = false;}
      if(WxkIQoYFnl == true){WxkIQoYFnl = false;}
      if(HDGLCqEgFE == true){HDGLCqEgFE = false;}
      if(oYhgwhwCVH == true){oYhgwhwCVH = false;}
      if(wIZoDMXtde == true){wIZoDMXtde = false;}
      if(JatKEOCTJN == true){JatKEOCTJN = false;}
      if(FsWODxPELi == true){FsWODxPELi = false;}
      if(rVjfpycRIp == true){rVjfpycRIp = false;}
      if(SJCZtNdXch == true){SJCZtNdXch = false;}
      if(fcrHCCkLlF == true){fcrHCCkLlF = false;}
      if(wThulnqNTF == true){wThulnqNTF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDVTPCJLLY
{ 
  void ZhgKIdcaRq()
  { 
      bool muXruLJeuz = false;
      bool KOLIrONlGJ = false;
      bool rVmbpgJojC = false;
      bool ttoIDFAyKM = false;
      bool LQLAAztpBI = false;
      bool urIRbQHwCO = false;
      bool BTtsFQYDEm = false;
      bool OPatxbKlaq = false;
      bool lTnbHBkXgm = false;
      bool xEwwLqVSuj = false;
      bool ZqkNteROTz = false;
      bool GVULbgfSlD = false;
      bool eBVRoKSdiG = false;
      bool FrqqQthZhb = false;
      bool jWDgfbikUd = false;
      bool LDgqEXVSYi = false;
      bool MmfMtOdctg = false;
      bool zFjJTIynlN = false;
      bool ahJEuCLzms = false;
      bool YPByPwqpmQ = false;
      string EmZSKLcUYI;
      string HauwzgOTiE;
      string pwDTwRGScV;
      string dCGZjnBAmY;
      string kIIKZrWkPK;
      string lXtoaIiFWs;
      string FKqDeETUMK;
      string fNgKSgmssD;
      string uUDSjFHQzb;
      string FudsTaRFfU;
      string XBYEdXqjWs;
      string UpLSxjGXTY;
      string xDVjFjjmpr;
      string OgNYfswynL;
      string NXtFHOiLwj;
      string TtlGXUeozt;
      string nEsedmbmmE;
      string nIjHLYJQcp;
      string BYpGXUuGAL;
      string NGytXIePaT;
      if(EmZSKLcUYI == XBYEdXqjWs){muXruLJeuz = true;}
      else if(XBYEdXqjWs == EmZSKLcUYI){ZqkNteROTz = true;}
      if(HauwzgOTiE == UpLSxjGXTY){KOLIrONlGJ = true;}
      else if(UpLSxjGXTY == HauwzgOTiE){GVULbgfSlD = true;}
      if(pwDTwRGScV == xDVjFjjmpr){rVmbpgJojC = true;}
      else if(xDVjFjjmpr == pwDTwRGScV){eBVRoKSdiG = true;}
      if(dCGZjnBAmY == OgNYfswynL){ttoIDFAyKM = true;}
      else if(OgNYfswynL == dCGZjnBAmY){FrqqQthZhb = true;}
      if(kIIKZrWkPK == NXtFHOiLwj){LQLAAztpBI = true;}
      else if(NXtFHOiLwj == kIIKZrWkPK){jWDgfbikUd = true;}
      if(lXtoaIiFWs == TtlGXUeozt){urIRbQHwCO = true;}
      else if(TtlGXUeozt == lXtoaIiFWs){LDgqEXVSYi = true;}
      if(FKqDeETUMK == nEsedmbmmE){BTtsFQYDEm = true;}
      else if(nEsedmbmmE == FKqDeETUMK){MmfMtOdctg = true;}
      if(fNgKSgmssD == nIjHLYJQcp){OPatxbKlaq = true;}
      if(uUDSjFHQzb == BYpGXUuGAL){lTnbHBkXgm = true;}
      if(FudsTaRFfU == NGytXIePaT){xEwwLqVSuj = true;}
      while(nIjHLYJQcp == fNgKSgmssD){zFjJTIynlN = true;}
      while(BYpGXUuGAL == BYpGXUuGAL){ahJEuCLzms = true;}
      while(NGytXIePaT == NGytXIePaT){YPByPwqpmQ = true;}
      if(muXruLJeuz == true){muXruLJeuz = false;}
      if(KOLIrONlGJ == true){KOLIrONlGJ = false;}
      if(rVmbpgJojC == true){rVmbpgJojC = false;}
      if(ttoIDFAyKM == true){ttoIDFAyKM = false;}
      if(LQLAAztpBI == true){LQLAAztpBI = false;}
      if(urIRbQHwCO == true){urIRbQHwCO = false;}
      if(BTtsFQYDEm == true){BTtsFQYDEm = false;}
      if(OPatxbKlaq == true){OPatxbKlaq = false;}
      if(lTnbHBkXgm == true){lTnbHBkXgm = false;}
      if(xEwwLqVSuj == true){xEwwLqVSuj = false;}
      if(ZqkNteROTz == true){ZqkNteROTz = false;}
      if(GVULbgfSlD == true){GVULbgfSlD = false;}
      if(eBVRoKSdiG == true){eBVRoKSdiG = false;}
      if(FrqqQthZhb == true){FrqqQthZhb = false;}
      if(jWDgfbikUd == true){jWDgfbikUd = false;}
      if(LDgqEXVSYi == true){LDgqEXVSYi = false;}
      if(MmfMtOdctg == true){MmfMtOdctg = false;}
      if(zFjJTIynlN == true){zFjJTIynlN = false;}
      if(ahJEuCLzms == true){ahJEuCLzms = false;}
      if(YPByPwqpmQ == true){YPByPwqpmQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYLZDNUCBI
{ 
  void ZlKWXFHJRC()
  { 
      bool mEOLmMlYzh = false;
      bool zKelNLueJu = false;
      bool whYJdCTFms = false;
      bool xMIssdpFfx = false;
      bool RxODLTFPli = false;
      bool cJTLxFeEhj = false;
      bool sgkGjmBksi = false;
      bool VozLdySVxK = false;
      bool xDTEPnrxum = false;
      bool ykXuEjLISX = false;
      bool RTVCMmJIgy = false;
      bool mIGWmoNgpw = false;
      bool uDoFkjQEGs = false;
      bool mJDYrdgQqb = false;
      bool diPxApeAIP = false;
      bool WdSVcNdPRc = false;
      bool VEBnLcFgeI = false;
      bool HwoNRLnrFt = false;
      bool FQwqVIqgwd = false;
      bool zQzNFZhbkW = false;
      string GiGSluTsau;
      string jxzePRJWfw;
      string MkHtNVmUGR;
      string GewdampMAX;
      string abIIwgSTNT;
      string BVAidVaMFQ;
      string HzlJnEBVDc;
      string awVIUjbzxg;
      string CSGmPkeMzF;
      string LdHiPapzTr;
      string exQjrEzqNs;
      string tbOXOorzsC;
      string YoVyQxnlss;
      string tbeECFCVtK;
      string kmyFLjOjUZ;
      string ipGQTpaRTu;
      string QMyUzRwKVI;
      string mVEhRlpPmg;
      string hERSKDVOkL;
      string ejCztXndGs;
      if(GiGSluTsau == exQjrEzqNs){mEOLmMlYzh = true;}
      else if(exQjrEzqNs == GiGSluTsau){RTVCMmJIgy = true;}
      if(jxzePRJWfw == tbOXOorzsC){zKelNLueJu = true;}
      else if(tbOXOorzsC == jxzePRJWfw){mIGWmoNgpw = true;}
      if(MkHtNVmUGR == YoVyQxnlss){whYJdCTFms = true;}
      else if(YoVyQxnlss == MkHtNVmUGR){uDoFkjQEGs = true;}
      if(GewdampMAX == tbeECFCVtK){xMIssdpFfx = true;}
      else if(tbeECFCVtK == GewdampMAX){mJDYrdgQqb = true;}
      if(abIIwgSTNT == kmyFLjOjUZ){RxODLTFPli = true;}
      else if(kmyFLjOjUZ == abIIwgSTNT){diPxApeAIP = true;}
      if(BVAidVaMFQ == ipGQTpaRTu){cJTLxFeEhj = true;}
      else if(ipGQTpaRTu == BVAidVaMFQ){WdSVcNdPRc = true;}
      if(HzlJnEBVDc == QMyUzRwKVI){sgkGjmBksi = true;}
      else if(QMyUzRwKVI == HzlJnEBVDc){VEBnLcFgeI = true;}
      if(awVIUjbzxg == mVEhRlpPmg){VozLdySVxK = true;}
      if(CSGmPkeMzF == hERSKDVOkL){xDTEPnrxum = true;}
      if(LdHiPapzTr == ejCztXndGs){ykXuEjLISX = true;}
      while(mVEhRlpPmg == awVIUjbzxg){HwoNRLnrFt = true;}
      while(hERSKDVOkL == hERSKDVOkL){FQwqVIqgwd = true;}
      while(ejCztXndGs == ejCztXndGs){zQzNFZhbkW = true;}
      if(mEOLmMlYzh == true){mEOLmMlYzh = false;}
      if(zKelNLueJu == true){zKelNLueJu = false;}
      if(whYJdCTFms == true){whYJdCTFms = false;}
      if(xMIssdpFfx == true){xMIssdpFfx = false;}
      if(RxODLTFPli == true){RxODLTFPli = false;}
      if(cJTLxFeEhj == true){cJTLxFeEhj = false;}
      if(sgkGjmBksi == true){sgkGjmBksi = false;}
      if(VozLdySVxK == true){VozLdySVxK = false;}
      if(xDTEPnrxum == true){xDTEPnrxum = false;}
      if(ykXuEjLISX == true){ykXuEjLISX = false;}
      if(RTVCMmJIgy == true){RTVCMmJIgy = false;}
      if(mIGWmoNgpw == true){mIGWmoNgpw = false;}
      if(uDoFkjQEGs == true){uDoFkjQEGs = false;}
      if(mJDYrdgQqb == true){mJDYrdgQqb = false;}
      if(diPxApeAIP == true){diPxApeAIP = false;}
      if(WdSVcNdPRc == true){WdSVcNdPRc = false;}
      if(VEBnLcFgeI == true){VEBnLcFgeI = false;}
      if(HwoNRLnrFt == true){HwoNRLnrFt = false;}
      if(FQwqVIqgwd == true){FQwqVIqgwd = false;}
      if(zQzNFZhbkW == true){zQzNFZhbkW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVQYELTYRW
{ 
  void elBxRRZuxC()
  { 
      bool opUNJsViTZ = false;
      bool tqVsVbgCZo = false;
      bool ALoVjMaaGl = false;
      bool OyuUOEdpdP = false;
      bool EuDczgHDXy = false;
      bool btfVhdAzcx = false;
      bool RubhLwwBeQ = false;
      bool xpYKkFIMVD = false;
      bool FXDIJURYlk = false;
      bool EeMfxJSVRD = false;
      bool jFYGAlUUjc = false;
      bool UncZqtqTXq = false;
      bool dWOsMRdrNb = false;
      bool lmuSSzzwHW = false;
      bool zxnJPPBmoC = false;
      bool RyxZYNqeti = false;
      bool IcGIphsKGq = false;
      bool tuMBqghEdw = false;
      bool QpCLKmoUsF = false;
      bool IUCYOVpfTg = false;
      string KqYVIltfub;
      string rMPTTRQISc;
      string qohTZZwKwA;
      string kdSZLAVnij;
      string TFuswmWArq;
      string miNSRVIEuh;
      string ojjupNspIS;
      string ubZiJltoWm;
      string DuSFMCQzHp;
      string qQrAtiUzDh;
      string sgrYuKIdJf;
      string aThIesRein;
      string xthSadiYnZ;
      string QuknsWDtJB;
      string sloaOXijVA;
      string RpQOkzyZxQ;
      string ajpiPfhsPI;
      string pXUguKEGDD;
      string uzDmIZeWDt;
      string XcwsZJwGLi;
      if(KqYVIltfub == sgrYuKIdJf){opUNJsViTZ = true;}
      else if(sgrYuKIdJf == KqYVIltfub){jFYGAlUUjc = true;}
      if(rMPTTRQISc == aThIesRein){tqVsVbgCZo = true;}
      else if(aThIesRein == rMPTTRQISc){UncZqtqTXq = true;}
      if(qohTZZwKwA == xthSadiYnZ){ALoVjMaaGl = true;}
      else if(xthSadiYnZ == qohTZZwKwA){dWOsMRdrNb = true;}
      if(kdSZLAVnij == QuknsWDtJB){OyuUOEdpdP = true;}
      else if(QuknsWDtJB == kdSZLAVnij){lmuSSzzwHW = true;}
      if(TFuswmWArq == sloaOXijVA){EuDczgHDXy = true;}
      else if(sloaOXijVA == TFuswmWArq){zxnJPPBmoC = true;}
      if(miNSRVIEuh == RpQOkzyZxQ){btfVhdAzcx = true;}
      else if(RpQOkzyZxQ == miNSRVIEuh){RyxZYNqeti = true;}
      if(ojjupNspIS == ajpiPfhsPI){RubhLwwBeQ = true;}
      else if(ajpiPfhsPI == ojjupNspIS){IcGIphsKGq = true;}
      if(ubZiJltoWm == pXUguKEGDD){xpYKkFIMVD = true;}
      if(DuSFMCQzHp == uzDmIZeWDt){FXDIJURYlk = true;}
      if(qQrAtiUzDh == XcwsZJwGLi){EeMfxJSVRD = true;}
      while(pXUguKEGDD == ubZiJltoWm){tuMBqghEdw = true;}
      while(uzDmIZeWDt == uzDmIZeWDt){QpCLKmoUsF = true;}
      while(XcwsZJwGLi == XcwsZJwGLi){IUCYOVpfTg = true;}
      if(opUNJsViTZ == true){opUNJsViTZ = false;}
      if(tqVsVbgCZo == true){tqVsVbgCZo = false;}
      if(ALoVjMaaGl == true){ALoVjMaaGl = false;}
      if(OyuUOEdpdP == true){OyuUOEdpdP = false;}
      if(EuDczgHDXy == true){EuDczgHDXy = false;}
      if(btfVhdAzcx == true){btfVhdAzcx = false;}
      if(RubhLwwBeQ == true){RubhLwwBeQ = false;}
      if(xpYKkFIMVD == true){xpYKkFIMVD = false;}
      if(FXDIJURYlk == true){FXDIJURYlk = false;}
      if(EeMfxJSVRD == true){EeMfxJSVRD = false;}
      if(jFYGAlUUjc == true){jFYGAlUUjc = false;}
      if(UncZqtqTXq == true){UncZqtqTXq = false;}
      if(dWOsMRdrNb == true){dWOsMRdrNb = false;}
      if(lmuSSzzwHW == true){lmuSSzzwHW = false;}
      if(zxnJPPBmoC == true){zxnJPPBmoC = false;}
      if(RyxZYNqeti == true){RyxZYNqeti = false;}
      if(IcGIphsKGq == true){IcGIphsKGq = false;}
      if(tuMBqghEdw == true){tuMBqghEdw = false;}
      if(QpCLKmoUsF == true){QpCLKmoUsF = false;}
      if(IUCYOVpfTg == true){IUCYOVpfTg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TZIFJLACVL
{ 
  void GlSWmNaMfO()
  { 
      bool lOTLidtIHr = false;
      bool TDxfDuApUj = false;
      bool DFyaPKoPuq = false;
      bool MmAzqBIzJe = false;
      bool MaTLKyPAzc = false;
      bool jlLOCfQrwX = false;
      bool oeMQegDyoC = false;
      bool lAfpWclmPR = false;
      bool unPSGaalxK = false;
      bool kQDlphNCfd = false;
      bool uQLxqjFVrZ = false;
      bool tcbecAOtJE = false;
      bool FQBeQVxtzo = false;
      bool OiHlWecSbW = false;
      bool UFtXQHnYJp = false;
      bool STraXdPgfU = false;
      bool lLVCKKVpHx = false;
      bool WwSmiAWdNJ = false;
      bool hYjJWuqfNr = false;
      bool OwmGjIiqMG = false;
      string kypxOCTXiM;
      string QzjdVnJTrA;
      string ohrompzIKw;
      string qXRoqQEIax;
      string ZQdbYAokLk;
      string atdPkCGBKY;
      string CKNlUsgtlF;
      string jAruZXEPPl;
      string AOxYVxsBDo;
      string JCyCtOCrGf;
      string TtzFBZBipM;
      string xplYXnNoPX;
      string zfpwwgCpAK;
      string ULJjSFPqWu;
      string wKLqqSQZdG;
      string BNcigmDCJT;
      string XLierlgBGR;
      string XWSTanTzEc;
      string QcLsJHiaDe;
      string CMgCXjbgyF;
      if(kypxOCTXiM == TtzFBZBipM){lOTLidtIHr = true;}
      else if(TtzFBZBipM == kypxOCTXiM){uQLxqjFVrZ = true;}
      if(QzjdVnJTrA == xplYXnNoPX){TDxfDuApUj = true;}
      else if(xplYXnNoPX == QzjdVnJTrA){tcbecAOtJE = true;}
      if(ohrompzIKw == zfpwwgCpAK){DFyaPKoPuq = true;}
      else if(zfpwwgCpAK == ohrompzIKw){FQBeQVxtzo = true;}
      if(qXRoqQEIax == ULJjSFPqWu){MmAzqBIzJe = true;}
      else if(ULJjSFPqWu == qXRoqQEIax){OiHlWecSbW = true;}
      if(ZQdbYAokLk == wKLqqSQZdG){MaTLKyPAzc = true;}
      else if(wKLqqSQZdG == ZQdbYAokLk){UFtXQHnYJp = true;}
      if(atdPkCGBKY == BNcigmDCJT){jlLOCfQrwX = true;}
      else if(BNcigmDCJT == atdPkCGBKY){STraXdPgfU = true;}
      if(CKNlUsgtlF == XLierlgBGR){oeMQegDyoC = true;}
      else if(XLierlgBGR == CKNlUsgtlF){lLVCKKVpHx = true;}
      if(jAruZXEPPl == XWSTanTzEc){lAfpWclmPR = true;}
      if(AOxYVxsBDo == QcLsJHiaDe){unPSGaalxK = true;}
      if(JCyCtOCrGf == CMgCXjbgyF){kQDlphNCfd = true;}
      while(XWSTanTzEc == jAruZXEPPl){WwSmiAWdNJ = true;}
      while(QcLsJHiaDe == QcLsJHiaDe){hYjJWuqfNr = true;}
      while(CMgCXjbgyF == CMgCXjbgyF){OwmGjIiqMG = true;}
      if(lOTLidtIHr == true){lOTLidtIHr = false;}
      if(TDxfDuApUj == true){TDxfDuApUj = false;}
      if(DFyaPKoPuq == true){DFyaPKoPuq = false;}
      if(MmAzqBIzJe == true){MmAzqBIzJe = false;}
      if(MaTLKyPAzc == true){MaTLKyPAzc = false;}
      if(jlLOCfQrwX == true){jlLOCfQrwX = false;}
      if(oeMQegDyoC == true){oeMQegDyoC = false;}
      if(lAfpWclmPR == true){lAfpWclmPR = false;}
      if(unPSGaalxK == true){unPSGaalxK = false;}
      if(kQDlphNCfd == true){kQDlphNCfd = false;}
      if(uQLxqjFVrZ == true){uQLxqjFVrZ = false;}
      if(tcbecAOtJE == true){tcbecAOtJE = false;}
      if(FQBeQVxtzo == true){FQBeQVxtzo = false;}
      if(OiHlWecSbW == true){OiHlWecSbW = false;}
      if(UFtXQHnYJp == true){UFtXQHnYJp = false;}
      if(STraXdPgfU == true){STraXdPgfU = false;}
      if(lLVCKKVpHx == true){lLVCKKVpHx = false;}
      if(WwSmiAWdNJ == true){WwSmiAWdNJ = false;}
      if(hYjJWuqfNr == true){hYjJWuqfNr = false;}
      if(OwmGjIiqMG == true){OwmGjIiqMG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JLQTDNHMVB
{ 
  void bQaaExPIlP()
  { 
      bool zFcLolSEli = false;
      bool IOaDVAVxGB = false;
      bool VHdtTXOWHX = false;
      bool ioLSNbdJqV = false;
      bool oXMRopUhVP = false;
      bool sVIliraiqR = false;
      bool WwxOzTDHpt = false;
      bool WMFkLxtMEd = false;
      bool CgAqdNfYjV = false;
      bool AtRZysaxRU = false;
      bool lMrbrgPXak = false;
      bool xOdNOpwFkl = false;
      bool meWUsbtflS = false;
      bool VwtjqpnYyw = false;
      bool xHyyXlQELI = false;
      bool xVMfhHoXhP = false;
      bool mjlHPATtWY = false;
      bool BWGnnffYwH = false;
      bool LpTdVAiOBi = false;
      bool AQqhINVpiW = false;
      string xwMcLLdhwm;
      string JGZZYObiQZ;
      string tMSWVncjIp;
      string ltjdrQscAF;
      string lOfWAQIItr;
      string hfexejcoGX;
      string itYFBPVwhI;
      string VyiLmefwWF;
      string eUoQIFPmyH;
      string nDWcWroaVk;
      string tLZlVixSJz;
      string EgRBrNEIxu;
      string zhxaUSbFou;
      string oFZlKStDtY;
      string HxdyDGkUjI;
      string mgcakMOzRD;
      string HqdOKyGfqY;
      string TBNYnCEzXN;
      string gGVfHIczBx;
      string EulqQPSPnE;
      if(xwMcLLdhwm == tLZlVixSJz){zFcLolSEli = true;}
      else if(tLZlVixSJz == xwMcLLdhwm){lMrbrgPXak = true;}
      if(JGZZYObiQZ == EgRBrNEIxu){IOaDVAVxGB = true;}
      else if(EgRBrNEIxu == JGZZYObiQZ){xOdNOpwFkl = true;}
      if(tMSWVncjIp == zhxaUSbFou){VHdtTXOWHX = true;}
      else if(zhxaUSbFou == tMSWVncjIp){meWUsbtflS = true;}
      if(ltjdrQscAF == oFZlKStDtY){ioLSNbdJqV = true;}
      else if(oFZlKStDtY == ltjdrQscAF){VwtjqpnYyw = true;}
      if(lOfWAQIItr == HxdyDGkUjI){oXMRopUhVP = true;}
      else if(HxdyDGkUjI == lOfWAQIItr){xHyyXlQELI = true;}
      if(hfexejcoGX == mgcakMOzRD){sVIliraiqR = true;}
      else if(mgcakMOzRD == hfexejcoGX){xVMfhHoXhP = true;}
      if(itYFBPVwhI == HqdOKyGfqY){WwxOzTDHpt = true;}
      else if(HqdOKyGfqY == itYFBPVwhI){mjlHPATtWY = true;}
      if(VyiLmefwWF == TBNYnCEzXN){WMFkLxtMEd = true;}
      if(eUoQIFPmyH == gGVfHIczBx){CgAqdNfYjV = true;}
      if(nDWcWroaVk == EulqQPSPnE){AtRZysaxRU = true;}
      while(TBNYnCEzXN == VyiLmefwWF){BWGnnffYwH = true;}
      while(gGVfHIczBx == gGVfHIczBx){LpTdVAiOBi = true;}
      while(EulqQPSPnE == EulqQPSPnE){AQqhINVpiW = true;}
      if(zFcLolSEli == true){zFcLolSEli = false;}
      if(IOaDVAVxGB == true){IOaDVAVxGB = false;}
      if(VHdtTXOWHX == true){VHdtTXOWHX = false;}
      if(ioLSNbdJqV == true){ioLSNbdJqV = false;}
      if(oXMRopUhVP == true){oXMRopUhVP = false;}
      if(sVIliraiqR == true){sVIliraiqR = false;}
      if(WwxOzTDHpt == true){WwxOzTDHpt = false;}
      if(WMFkLxtMEd == true){WMFkLxtMEd = false;}
      if(CgAqdNfYjV == true){CgAqdNfYjV = false;}
      if(AtRZysaxRU == true){AtRZysaxRU = false;}
      if(lMrbrgPXak == true){lMrbrgPXak = false;}
      if(xOdNOpwFkl == true){xOdNOpwFkl = false;}
      if(meWUsbtflS == true){meWUsbtflS = false;}
      if(VwtjqpnYyw == true){VwtjqpnYyw = false;}
      if(xHyyXlQELI == true){xHyyXlQELI = false;}
      if(xVMfhHoXhP == true){xVMfhHoXhP = false;}
      if(mjlHPATtWY == true){mjlHPATtWY = false;}
      if(BWGnnffYwH == true){BWGnnffYwH = false;}
      if(LpTdVAiOBi == true){LpTdVAiOBi = false;}
      if(AQqhINVpiW == true){AQqhINVpiW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCBNIBYFJW
{ 
  void nwIRKElwcn()
  { 
      bool UUdsDjwlHU = false;
      bool xTSGFnCdsy = false;
      bool fSbHakHWGH = false;
      bool hqigSHbxaO = false;
      bool zQXkWnxfWP = false;
      bool KBdYMCsVSR = false;
      bool cZfzlGjlmx = false;
      bool MEDeyOtqkm = false;
      bool nbAqxfNKTQ = false;
      bool NFeIkZkXyP = false;
      bool DLrYCFyzZy = false;
      bool HCkfdBYnCG = false;
      bool rZSWiGZusY = false;
      bool cWrUibibnr = false;
      bool hNjVJLUydj = false;
      bool AxVrWcsUow = false;
      bool eDFBUkJPwC = false;
      bool RxzJYdoxMW = false;
      bool kaQJXfAAxF = false;
      bool iNlrMdHiAY = false;
      string VpAWybZUAu;
      string VNKTZXaCjB;
      string gcTCmCMPnl;
      string wgujFtUzog;
      string QkUFaMWJfQ;
      string gaxHhrVxjw;
      string OKfNynSZOe;
      string DaMDjwHOba;
      string eDiXEVjmCM;
      string YXPsRGEGGm;
      string sxtBNGNtWl;
      string jGVJQLbIJc;
      string DfWBGeLTkd;
      string qBInghJhJy;
      string HoQQbSCFbG;
      string euxciMZruh;
      string ttJstixgbi;
      string CtyKVOOGZn;
      string cFqezwDeFU;
      string HQmbDNfXWs;
      if(VpAWybZUAu == sxtBNGNtWl){UUdsDjwlHU = true;}
      else if(sxtBNGNtWl == VpAWybZUAu){DLrYCFyzZy = true;}
      if(VNKTZXaCjB == jGVJQLbIJc){xTSGFnCdsy = true;}
      else if(jGVJQLbIJc == VNKTZXaCjB){HCkfdBYnCG = true;}
      if(gcTCmCMPnl == DfWBGeLTkd){fSbHakHWGH = true;}
      else if(DfWBGeLTkd == gcTCmCMPnl){rZSWiGZusY = true;}
      if(wgujFtUzog == qBInghJhJy){hqigSHbxaO = true;}
      else if(qBInghJhJy == wgujFtUzog){cWrUibibnr = true;}
      if(QkUFaMWJfQ == HoQQbSCFbG){zQXkWnxfWP = true;}
      else if(HoQQbSCFbG == QkUFaMWJfQ){hNjVJLUydj = true;}
      if(gaxHhrVxjw == euxciMZruh){KBdYMCsVSR = true;}
      else if(euxciMZruh == gaxHhrVxjw){AxVrWcsUow = true;}
      if(OKfNynSZOe == ttJstixgbi){cZfzlGjlmx = true;}
      else if(ttJstixgbi == OKfNynSZOe){eDFBUkJPwC = true;}
      if(DaMDjwHOba == CtyKVOOGZn){MEDeyOtqkm = true;}
      if(eDiXEVjmCM == cFqezwDeFU){nbAqxfNKTQ = true;}
      if(YXPsRGEGGm == HQmbDNfXWs){NFeIkZkXyP = true;}
      while(CtyKVOOGZn == DaMDjwHOba){RxzJYdoxMW = true;}
      while(cFqezwDeFU == cFqezwDeFU){kaQJXfAAxF = true;}
      while(HQmbDNfXWs == HQmbDNfXWs){iNlrMdHiAY = true;}
      if(UUdsDjwlHU == true){UUdsDjwlHU = false;}
      if(xTSGFnCdsy == true){xTSGFnCdsy = false;}
      if(fSbHakHWGH == true){fSbHakHWGH = false;}
      if(hqigSHbxaO == true){hqigSHbxaO = false;}
      if(zQXkWnxfWP == true){zQXkWnxfWP = false;}
      if(KBdYMCsVSR == true){KBdYMCsVSR = false;}
      if(cZfzlGjlmx == true){cZfzlGjlmx = false;}
      if(MEDeyOtqkm == true){MEDeyOtqkm = false;}
      if(nbAqxfNKTQ == true){nbAqxfNKTQ = false;}
      if(NFeIkZkXyP == true){NFeIkZkXyP = false;}
      if(DLrYCFyzZy == true){DLrYCFyzZy = false;}
      if(HCkfdBYnCG == true){HCkfdBYnCG = false;}
      if(rZSWiGZusY == true){rZSWiGZusY = false;}
      if(cWrUibibnr == true){cWrUibibnr = false;}
      if(hNjVJLUydj == true){hNjVJLUydj = false;}
      if(AxVrWcsUow == true){AxVrWcsUow = false;}
      if(eDFBUkJPwC == true){eDFBUkJPwC = false;}
      if(RxzJYdoxMW == true){RxzJYdoxMW = false;}
      if(kaQJXfAAxF == true){kaQJXfAAxF = false;}
      if(iNlrMdHiAY == true){iNlrMdHiAY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUSVNQHJDW
{ 
  void ozGmgWHDbY()
  { 
      bool NCxBxgwuQr = false;
      bool WfXnbXgEUu = false;
      bool HKyYVsSxUX = false;
      bool cjawgRhGZR = false;
      bool cISqwmUCZQ = false;
      bool RNzUtCEXeD = false;
      bool OzarPlEbHJ = false;
      bool oaeCRyqGci = false;
      bool XPWDGPjGBd = false;
      bool NKaVDdhZbJ = false;
      bool hstPbphxCw = false;
      bool LxtweybXlA = false;
      bool ByZcwezIzn = false;
      bool QQeSAeVHbQ = false;
      bool gmDFSPPepE = false;
      bool BKnaIjSRTw = false;
      bool qZyOetSbuA = false;
      bool cUuUTOtTKf = false;
      bool OTRtlFbDKQ = false;
      bool MDmeYGooZX = false;
      string ezHWLwIFAU;
      string VLsZuzUJjV;
      string NqIyXrpUEh;
      string iDTmYRBZor;
      string JwZkwKElNB;
      string SHZVJnqIyS;
      string FnBRlSqFAc;
      string yuTrLRRXCN;
      string nDHCPacyck;
      string araVlVuHzd;
      string TyljDXmhJr;
      string VSGkeCfyCK;
      string prbOCGTyFo;
      string WJXXsoQXzr;
      string ntnkOHkopi;
      string pwFnnaWXhx;
      string DobTVMthro;
      string lIzJWuEpzt;
      string UeHWzZEjjS;
      string SspCoySTPC;
      if(ezHWLwIFAU == TyljDXmhJr){NCxBxgwuQr = true;}
      else if(TyljDXmhJr == ezHWLwIFAU){hstPbphxCw = true;}
      if(VLsZuzUJjV == VSGkeCfyCK){WfXnbXgEUu = true;}
      else if(VSGkeCfyCK == VLsZuzUJjV){LxtweybXlA = true;}
      if(NqIyXrpUEh == prbOCGTyFo){HKyYVsSxUX = true;}
      else if(prbOCGTyFo == NqIyXrpUEh){ByZcwezIzn = true;}
      if(iDTmYRBZor == WJXXsoQXzr){cjawgRhGZR = true;}
      else if(WJXXsoQXzr == iDTmYRBZor){QQeSAeVHbQ = true;}
      if(JwZkwKElNB == ntnkOHkopi){cISqwmUCZQ = true;}
      else if(ntnkOHkopi == JwZkwKElNB){gmDFSPPepE = true;}
      if(SHZVJnqIyS == pwFnnaWXhx){RNzUtCEXeD = true;}
      else if(pwFnnaWXhx == SHZVJnqIyS){BKnaIjSRTw = true;}
      if(FnBRlSqFAc == DobTVMthro){OzarPlEbHJ = true;}
      else if(DobTVMthro == FnBRlSqFAc){qZyOetSbuA = true;}
      if(yuTrLRRXCN == lIzJWuEpzt){oaeCRyqGci = true;}
      if(nDHCPacyck == UeHWzZEjjS){XPWDGPjGBd = true;}
      if(araVlVuHzd == SspCoySTPC){NKaVDdhZbJ = true;}
      while(lIzJWuEpzt == yuTrLRRXCN){cUuUTOtTKf = true;}
      while(UeHWzZEjjS == UeHWzZEjjS){OTRtlFbDKQ = true;}
      while(SspCoySTPC == SspCoySTPC){MDmeYGooZX = true;}
      if(NCxBxgwuQr == true){NCxBxgwuQr = false;}
      if(WfXnbXgEUu == true){WfXnbXgEUu = false;}
      if(HKyYVsSxUX == true){HKyYVsSxUX = false;}
      if(cjawgRhGZR == true){cjawgRhGZR = false;}
      if(cISqwmUCZQ == true){cISqwmUCZQ = false;}
      if(RNzUtCEXeD == true){RNzUtCEXeD = false;}
      if(OzarPlEbHJ == true){OzarPlEbHJ = false;}
      if(oaeCRyqGci == true){oaeCRyqGci = false;}
      if(XPWDGPjGBd == true){XPWDGPjGBd = false;}
      if(NKaVDdhZbJ == true){NKaVDdhZbJ = false;}
      if(hstPbphxCw == true){hstPbphxCw = false;}
      if(LxtweybXlA == true){LxtweybXlA = false;}
      if(ByZcwezIzn == true){ByZcwezIzn = false;}
      if(QQeSAeVHbQ == true){QQeSAeVHbQ = false;}
      if(gmDFSPPepE == true){gmDFSPPepE = false;}
      if(BKnaIjSRTw == true){BKnaIjSRTw = false;}
      if(qZyOetSbuA == true){qZyOetSbuA = false;}
      if(cUuUTOtTKf == true){cUuUTOtTKf = false;}
      if(OTRtlFbDKQ == true){OTRtlFbDKQ = false;}
      if(MDmeYGooZX == true){MDmeYGooZX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYTPETETRV
{ 
  void FniCdqwzba()
  { 
      bool oCclCIsEco = false;
      bool ssQKCuzmmY = false;
      bool NDMoZfJcur = false;
      bool yGkzxLGeJm = false;
      bool QSYLAJrrBp = false;
      bool tHRlllomMW = false;
      bool zQIjqlHRMq = false;
      bool nTdAHueAoP = false;
      bool mQaFyqoyNL = false;
      bool VSRlnAKnUN = false;
      bool CafKBZcRep = false;
      bool GnywjhoClz = false;
      bool xIEAUVBqLH = false;
      bool kpfaMMkQEX = false;
      bool NXTWEhUVCG = false;
      bool LHBUQtVepf = false;
      bool XkFXFPIXiX = false;
      bool wYyNkZngum = false;
      bool BfoFwdoKJS = false;
      bool pGZYAbRwRn = false;
      string jcfdIZrhpT;
      string GYJVDWWzGW;
      string UEiWsMlCLF;
      string TRlDIIZfgt;
      string XCQJNpmMYs;
      string QNQymftIku;
      string npWkAolGMu;
      string wpRLyRmYJC;
      string ZYdSoFAmPc;
      string OQtkGhffJX;
      string DgzcwZwFzU;
      string rUzhVOMEut;
      string ozqjfeufEQ;
      string lHPkysYAVO;
      string IumtksQMPr;
      string UbjOiEoPxQ;
      string dPAiikEOic;
      string oMhfksLwyl;
      string NiQMuKWBBt;
      string DJCEksuEKz;
      if(jcfdIZrhpT == DgzcwZwFzU){oCclCIsEco = true;}
      else if(DgzcwZwFzU == jcfdIZrhpT){CafKBZcRep = true;}
      if(GYJVDWWzGW == rUzhVOMEut){ssQKCuzmmY = true;}
      else if(rUzhVOMEut == GYJVDWWzGW){GnywjhoClz = true;}
      if(UEiWsMlCLF == ozqjfeufEQ){NDMoZfJcur = true;}
      else if(ozqjfeufEQ == UEiWsMlCLF){xIEAUVBqLH = true;}
      if(TRlDIIZfgt == lHPkysYAVO){yGkzxLGeJm = true;}
      else if(lHPkysYAVO == TRlDIIZfgt){kpfaMMkQEX = true;}
      if(XCQJNpmMYs == IumtksQMPr){QSYLAJrrBp = true;}
      else if(IumtksQMPr == XCQJNpmMYs){NXTWEhUVCG = true;}
      if(QNQymftIku == UbjOiEoPxQ){tHRlllomMW = true;}
      else if(UbjOiEoPxQ == QNQymftIku){LHBUQtVepf = true;}
      if(npWkAolGMu == dPAiikEOic){zQIjqlHRMq = true;}
      else if(dPAiikEOic == npWkAolGMu){XkFXFPIXiX = true;}
      if(wpRLyRmYJC == oMhfksLwyl){nTdAHueAoP = true;}
      if(ZYdSoFAmPc == NiQMuKWBBt){mQaFyqoyNL = true;}
      if(OQtkGhffJX == DJCEksuEKz){VSRlnAKnUN = true;}
      while(oMhfksLwyl == wpRLyRmYJC){wYyNkZngum = true;}
      while(NiQMuKWBBt == NiQMuKWBBt){BfoFwdoKJS = true;}
      while(DJCEksuEKz == DJCEksuEKz){pGZYAbRwRn = true;}
      if(oCclCIsEco == true){oCclCIsEco = false;}
      if(ssQKCuzmmY == true){ssQKCuzmmY = false;}
      if(NDMoZfJcur == true){NDMoZfJcur = false;}
      if(yGkzxLGeJm == true){yGkzxLGeJm = false;}
      if(QSYLAJrrBp == true){QSYLAJrrBp = false;}
      if(tHRlllomMW == true){tHRlllomMW = false;}
      if(zQIjqlHRMq == true){zQIjqlHRMq = false;}
      if(nTdAHueAoP == true){nTdAHueAoP = false;}
      if(mQaFyqoyNL == true){mQaFyqoyNL = false;}
      if(VSRlnAKnUN == true){VSRlnAKnUN = false;}
      if(CafKBZcRep == true){CafKBZcRep = false;}
      if(GnywjhoClz == true){GnywjhoClz = false;}
      if(xIEAUVBqLH == true){xIEAUVBqLH = false;}
      if(kpfaMMkQEX == true){kpfaMMkQEX = false;}
      if(NXTWEhUVCG == true){NXTWEhUVCG = false;}
      if(LHBUQtVepf == true){LHBUQtVepf = false;}
      if(XkFXFPIXiX == true){XkFXFPIXiX = false;}
      if(wYyNkZngum == true){wYyNkZngum = false;}
      if(BfoFwdoKJS == true){BfoFwdoKJS = false;}
      if(pGZYAbRwRn == true){pGZYAbRwRn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYADBRREFU
{ 
  void clyIXCkQOP()
  { 
      bool WCRWEjWUQG = false;
      bool WRKquZuEne = false;
      bool OIzTcUBADr = false;
      bool JFpVcrmSQG = false;
      bool eddDSYbfJL = false;
      bool AqHWFOCxsi = false;
      bool hWQYxQbnND = false;
      bool lbmhAjduBD = false;
      bool rVqrqRySQO = false;
      bool ooYhXINFGB = false;
      bool wnRFYXDYVU = false;
      bool jHwopMeYge = false;
      bool SIXzOxCFJr = false;
      bool WYnzHEDkTS = false;
      bool NYxudgsiqL = false;
      bool cnXbinPSpb = false;
      bool VyOdyLTwhk = false;
      bool ItFOQsLcUh = false;
      bool DSNyPhAMQS = false;
      bool ojtqxPJSxS = false;
      string KzVsxSNYxd;
      string VShYIUUHEH;
      string bQVmEqLwgR;
      string IWhMxFYoQP;
      string MUswimFASq;
      string qIuaSscioF;
      string HQqeUzkUbC;
      string ufqouHWZEQ;
      string kLdpazaGtE;
      string cpzKHucOai;
      string CkXPuKRGeK;
      string VCdXTulAEV;
      string YdaXZFffgz;
      string dIzUOAmNuP;
      string hTbihZLbpM;
      string IcJEKYJApo;
      string dkYegNDJJT;
      string IYFonECrpz;
      string tEpUpBzuKo;
      string pmWFkwuwBT;
      if(KzVsxSNYxd == CkXPuKRGeK){WCRWEjWUQG = true;}
      else if(CkXPuKRGeK == KzVsxSNYxd){wnRFYXDYVU = true;}
      if(VShYIUUHEH == VCdXTulAEV){WRKquZuEne = true;}
      else if(VCdXTulAEV == VShYIUUHEH){jHwopMeYge = true;}
      if(bQVmEqLwgR == YdaXZFffgz){OIzTcUBADr = true;}
      else if(YdaXZFffgz == bQVmEqLwgR){SIXzOxCFJr = true;}
      if(IWhMxFYoQP == dIzUOAmNuP){JFpVcrmSQG = true;}
      else if(dIzUOAmNuP == IWhMxFYoQP){WYnzHEDkTS = true;}
      if(MUswimFASq == hTbihZLbpM){eddDSYbfJL = true;}
      else if(hTbihZLbpM == MUswimFASq){NYxudgsiqL = true;}
      if(qIuaSscioF == IcJEKYJApo){AqHWFOCxsi = true;}
      else if(IcJEKYJApo == qIuaSscioF){cnXbinPSpb = true;}
      if(HQqeUzkUbC == dkYegNDJJT){hWQYxQbnND = true;}
      else if(dkYegNDJJT == HQqeUzkUbC){VyOdyLTwhk = true;}
      if(ufqouHWZEQ == IYFonECrpz){lbmhAjduBD = true;}
      if(kLdpazaGtE == tEpUpBzuKo){rVqrqRySQO = true;}
      if(cpzKHucOai == pmWFkwuwBT){ooYhXINFGB = true;}
      while(IYFonECrpz == ufqouHWZEQ){ItFOQsLcUh = true;}
      while(tEpUpBzuKo == tEpUpBzuKo){DSNyPhAMQS = true;}
      while(pmWFkwuwBT == pmWFkwuwBT){ojtqxPJSxS = true;}
      if(WCRWEjWUQG == true){WCRWEjWUQG = false;}
      if(WRKquZuEne == true){WRKquZuEne = false;}
      if(OIzTcUBADr == true){OIzTcUBADr = false;}
      if(JFpVcrmSQG == true){JFpVcrmSQG = false;}
      if(eddDSYbfJL == true){eddDSYbfJL = false;}
      if(AqHWFOCxsi == true){AqHWFOCxsi = false;}
      if(hWQYxQbnND == true){hWQYxQbnND = false;}
      if(lbmhAjduBD == true){lbmhAjduBD = false;}
      if(rVqrqRySQO == true){rVqrqRySQO = false;}
      if(ooYhXINFGB == true){ooYhXINFGB = false;}
      if(wnRFYXDYVU == true){wnRFYXDYVU = false;}
      if(jHwopMeYge == true){jHwopMeYge = false;}
      if(SIXzOxCFJr == true){SIXzOxCFJr = false;}
      if(WYnzHEDkTS == true){WYnzHEDkTS = false;}
      if(NYxudgsiqL == true){NYxudgsiqL = false;}
      if(cnXbinPSpb == true){cnXbinPSpb = false;}
      if(VyOdyLTwhk == true){VyOdyLTwhk = false;}
      if(ItFOQsLcUh == true){ItFOQsLcUh = false;}
      if(DSNyPhAMQS == true){DSNyPhAMQS = false;}
      if(ojtqxPJSxS == true){ojtqxPJSxS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAKRYWYIEC
{ 
  void IUZGOdUhLc()
  { 
      bool oYICddPVuQ = false;
      bool GJGOgtQkZO = false;
      bool faChALyNJu = false;
      bool mZUIUxmROp = false;
      bool iwskjUaXoZ = false;
      bool EgLiGNWZCS = false;
      bool eCMzcfnxtj = false;
      bool HzWjejhRxe = false;
      bool jZXjqGOkCG = false;
      bool aMPuKgjsHD = false;
      bool fdcEREKbEV = false;
      bool fFbWiFdbHW = false;
      bool RCtnJtjaZy = false;
      bool AnJsyFwTRm = false;
      bool ulgfZVjrMF = false;
      bool CHkjldinuX = false;
      bool UiCGVruiXc = false;
      bool IKKUbfUOOn = false;
      bool JqOTurCYHU = false;
      bool WIXsRLiaKh = false;
      string rcqkSZRgYG;
      string thCHCoWgII;
      string PTdPeUgUpB;
      string sBhzZThYOr;
      string LDMuRJIPVK;
      string TCKZZXzaFx;
      string sxpWMszChh;
      string GyRPxMHixU;
      string MQzegppHYB;
      string UGSRzNMohY;
      string KFhmDVktcN;
      string QPcjkbyLoV;
      string CqdfNAeAQi;
      string ARAYKGiMaL;
      string FweLkEdhgX;
      string PAzLWSbBYD;
      string qjdsNyPEZd;
      string slkdQFLSuJ;
      string VwTsTzRnBq;
      string dgmWUUSlxl;
      if(rcqkSZRgYG == KFhmDVktcN){oYICddPVuQ = true;}
      else if(KFhmDVktcN == rcqkSZRgYG){fdcEREKbEV = true;}
      if(thCHCoWgII == QPcjkbyLoV){GJGOgtQkZO = true;}
      else if(QPcjkbyLoV == thCHCoWgII){fFbWiFdbHW = true;}
      if(PTdPeUgUpB == CqdfNAeAQi){faChALyNJu = true;}
      else if(CqdfNAeAQi == PTdPeUgUpB){RCtnJtjaZy = true;}
      if(sBhzZThYOr == ARAYKGiMaL){mZUIUxmROp = true;}
      else if(ARAYKGiMaL == sBhzZThYOr){AnJsyFwTRm = true;}
      if(LDMuRJIPVK == FweLkEdhgX){iwskjUaXoZ = true;}
      else if(FweLkEdhgX == LDMuRJIPVK){ulgfZVjrMF = true;}
      if(TCKZZXzaFx == PAzLWSbBYD){EgLiGNWZCS = true;}
      else if(PAzLWSbBYD == TCKZZXzaFx){CHkjldinuX = true;}
      if(sxpWMszChh == qjdsNyPEZd){eCMzcfnxtj = true;}
      else if(qjdsNyPEZd == sxpWMszChh){UiCGVruiXc = true;}
      if(GyRPxMHixU == slkdQFLSuJ){HzWjejhRxe = true;}
      if(MQzegppHYB == VwTsTzRnBq){jZXjqGOkCG = true;}
      if(UGSRzNMohY == dgmWUUSlxl){aMPuKgjsHD = true;}
      while(slkdQFLSuJ == GyRPxMHixU){IKKUbfUOOn = true;}
      while(VwTsTzRnBq == VwTsTzRnBq){JqOTurCYHU = true;}
      while(dgmWUUSlxl == dgmWUUSlxl){WIXsRLiaKh = true;}
      if(oYICddPVuQ == true){oYICddPVuQ = false;}
      if(GJGOgtQkZO == true){GJGOgtQkZO = false;}
      if(faChALyNJu == true){faChALyNJu = false;}
      if(mZUIUxmROp == true){mZUIUxmROp = false;}
      if(iwskjUaXoZ == true){iwskjUaXoZ = false;}
      if(EgLiGNWZCS == true){EgLiGNWZCS = false;}
      if(eCMzcfnxtj == true){eCMzcfnxtj = false;}
      if(HzWjejhRxe == true){HzWjejhRxe = false;}
      if(jZXjqGOkCG == true){jZXjqGOkCG = false;}
      if(aMPuKgjsHD == true){aMPuKgjsHD = false;}
      if(fdcEREKbEV == true){fdcEREKbEV = false;}
      if(fFbWiFdbHW == true){fFbWiFdbHW = false;}
      if(RCtnJtjaZy == true){RCtnJtjaZy = false;}
      if(AnJsyFwTRm == true){AnJsyFwTRm = false;}
      if(ulgfZVjrMF == true){ulgfZVjrMF = false;}
      if(CHkjldinuX == true){CHkjldinuX = false;}
      if(UiCGVruiXc == true){UiCGVruiXc = false;}
      if(IKKUbfUOOn == true){IKKUbfUOOn = false;}
      if(JqOTurCYHU == true){JqOTurCYHU = false;}
      if(WIXsRLiaKh == true){WIXsRLiaKh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OERSKKPLBG
{ 
  void OWxbunQhre()
  { 
      bool afgmGkTJbI = false;
      bool pHNglUPqai = false;
      bool ueaLEnyagj = false;
      bool gZMNhuehRi = false;
      bool TTmPQnYlWL = false;
      bool GnsxruEUiR = false;
      bool lrbraPuzyq = false;
      bool phYrObrLuP = false;
      bool PMDVcsgOVl = false;
      bool pJzAwaqtnA = false;
      bool sZmfVYOBhP = false;
      bool DrYSCZoGOg = false;
      bool ifdMAfhXun = false;
      bool jxXuVpYXzE = false;
      bool defFixkfxW = false;
      bool lkfGQNuaeo = false;
      bool pqGteFUcxM = false;
      bool ARGJDEzXcD = false;
      bool tCZYBzQQeI = false;
      bool tyrJNmYlac = false;
      string DUdcKLxtyY;
      string csFIFMehie;
      string TeZSdOFsrR;
      string BFznJKhJjQ;
      string fOeYzpQaPz;
      string NunQUYuKyw;
      string GDBfWXsRzt;
      string dVyRyFzATn;
      string xddsEGQhTk;
      string PWKmKbMzBa;
      string wzbUUqwWRP;
      string YtqKycZIaQ;
      string GKyNeGLKGW;
      string rAzrrxBIXM;
      string JtPEMVeznh;
      string CEXjUkBOpN;
      string flPuWYtzSB;
      string aQkNHLtsBJ;
      string bLVYUmcPXG;
      string wlSJgWeUgm;
      if(DUdcKLxtyY == wzbUUqwWRP){afgmGkTJbI = true;}
      else if(wzbUUqwWRP == DUdcKLxtyY){sZmfVYOBhP = true;}
      if(csFIFMehie == YtqKycZIaQ){pHNglUPqai = true;}
      else if(YtqKycZIaQ == csFIFMehie){DrYSCZoGOg = true;}
      if(TeZSdOFsrR == GKyNeGLKGW){ueaLEnyagj = true;}
      else if(GKyNeGLKGW == TeZSdOFsrR){ifdMAfhXun = true;}
      if(BFznJKhJjQ == rAzrrxBIXM){gZMNhuehRi = true;}
      else if(rAzrrxBIXM == BFznJKhJjQ){jxXuVpYXzE = true;}
      if(fOeYzpQaPz == JtPEMVeznh){TTmPQnYlWL = true;}
      else if(JtPEMVeznh == fOeYzpQaPz){defFixkfxW = true;}
      if(NunQUYuKyw == CEXjUkBOpN){GnsxruEUiR = true;}
      else if(CEXjUkBOpN == NunQUYuKyw){lkfGQNuaeo = true;}
      if(GDBfWXsRzt == flPuWYtzSB){lrbraPuzyq = true;}
      else if(flPuWYtzSB == GDBfWXsRzt){pqGteFUcxM = true;}
      if(dVyRyFzATn == aQkNHLtsBJ){phYrObrLuP = true;}
      if(xddsEGQhTk == bLVYUmcPXG){PMDVcsgOVl = true;}
      if(PWKmKbMzBa == wlSJgWeUgm){pJzAwaqtnA = true;}
      while(aQkNHLtsBJ == dVyRyFzATn){ARGJDEzXcD = true;}
      while(bLVYUmcPXG == bLVYUmcPXG){tCZYBzQQeI = true;}
      while(wlSJgWeUgm == wlSJgWeUgm){tyrJNmYlac = true;}
      if(afgmGkTJbI == true){afgmGkTJbI = false;}
      if(pHNglUPqai == true){pHNglUPqai = false;}
      if(ueaLEnyagj == true){ueaLEnyagj = false;}
      if(gZMNhuehRi == true){gZMNhuehRi = false;}
      if(TTmPQnYlWL == true){TTmPQnYlWL = false;}
      if(GnsxruEUiR == true){GnsxruEUiR = false;}
      if(lrbraPuzyq == true){lrbraPuzyq = false;}
      if(phYrObrLuP == true){phYrObrLuP = false;}
      if(PMDVcsgOVl == true){PMDVcsgOVl = false;}
      if(pJzAwaqtnA == true){pJzAwaqtnA = false;}
      if(sZmfVYOBhP == true){sZmfVYOBhP = false;}
      if(DrYSCZoGOg == true){DrYSCZoGOg = false;}
      if(ifdMAfhXun == true){ifdMAfhXun = false;}
      if(jxXuVpYXzE == true){jxXuVpYXzE = false;}
      if(defFixkfxW == true){defFixkfxW = false;}
      if(lkfGQNuaeo == true){lkfGQNuaeo = false;}
      if(pqGteFUcxM == true){pqGteFUcxM = false;}
      if(ARGJDEzXcD == true){ARGJDEzXcD = false;}
      if(tCZYBzQQeI == true){tCZYBzQQeI = false;}
      if(tyrJNmYlac == true){tyrJNmYlac = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQRAYLHCJI
{ 
  void FXWyVXnxcr()
  { 
      bool JxwecheiQd = false;
      bool HPmKsmozDi = false;
      bool YMxDlUmgfC = false;
      bool uIxxqbGrMQ = false;
      bool YdqwaCiRRt = false;
      bool ZMSLTwzrsI = false;
      bool txDOizRpSR = false;
      bool gwmmJtVAbj = false;
      bool kVOkbhokcu = false;
      bool bNzDWaZcNb = false;
      bool jsyAMcZfCY = false;
      bool ZzQIWYiSlB = false;
      bool JgMXoTxiQh = false;
      bool TrlAArXNYz = false;
      bool HIiEUcxpfx = false;
      bool rHqMRDfZLs = false;
      bool epPTEhMPId = false;
      bool AVslsBxIDM = false;
      bool WGCSpMBZix = false;
      bool LxCfTQsPzm = false;
      string FKCSuWWViV;
      string ZGGPoxqPLd;
      string kNgKsKmqFz;
      string hQYjTTxPws;
      string fMSPDbErMM;
      string BlQxmrcrYj;
      string jfQjnIhWwV;
      string zaSSxXtRHQ;
      string Gtdryuzawb;
      string pFpMJAwiat;
      string tgwqMZTyAO;
      string xLjIcoCXks;
      string IGZTetjGJx;
      string bLpMWYymeX;
      string bBahdeUhiT;
      string xXxhlmHbLS;
      string pMoDmlVXlD;
      string pPsNRHfroA;
      string YCXozENIai;
      string RVbLhOMWtr;
      if(FKCSuWWViV == tgwqMZTyAO){JxwecheiQd = true;}
      else if(tgwqMZTyAO == FKCSuWWViV){jsyAMcZfCY = true;}
      if(ZGGPoxqPLd == xLjIcoCXks){HPmKsmozDi = true;}
      else if(xLjIcoCXks == ZGGPoxqPLd){ZzQIWYiSlB = true;}
      if(kNgKsKmqFz == IGZTetjGJx){YMxDlUmgfC = true;}
      else if(IGZTetjGJx == kNgKsKmqFz){JgMXoTxiQh = true;}
      if(hQYjTTxPws == bLpMWYymeX){uIxxqbGrMQ = true;}
      else if(bLpMWYymeX == hQYjTTxPws){TrlAArXNYz = true;}
      if(fMSPDbErMM == bBahdeUhiT){YdqwaCiRRt = true;}
      else if(bBahdeUhiT == fMSPDbErMM){HIiEUcxpfx = true;}
      if(BlQxmrcrYj == xXxhlmHbLS){ZMSLTwzrsI = true;}
      else if(xXxhlmHbLS == BlQxmrcrYj){rHqMRDfZLs = true;}
      if(jfQjnIhWwV == pMoDmlVXlD){txDOizRpSR = true;}
      else if(pMoDmlVXlD == jfQjnIhWwV){epPTEhMPId = true;}
      if(zaSSxXtRHQ == pPsNRHfroA){gwmmJtVAbj = true;}
      if(Gtdryuzawb == YCXozENIai){kVOkbhokcu = true;}
      if(pFpMJAwiat == RVbLhOMWtr){bNzDWaZcNb = true;}
      while(pPsNRHfroA == zaSSxXtRHQ){AVslsBxIDM = true;}
      while(YCXozENIai == YCXozENIai){WGCSpMBZix = true;}
      while(RVbLhOMWtr == RVbLhOMWtr){LxCfTQsPzm = true;}
      if(JxwecheiQd == true){JxwecheiQd = false;}
      if(HPmKsmozDi == true){HPmKsmozDi = false;}
      if(YMxDlUmgfC == true){YMxDlUmgfC = false;}
      if(uIxxqbGrMQ == true){uIxxqbGrMQ = false;}
      if(YdqwaCiRRt == true){YdqwaCiRRt = false;}
      if(ZMSLTwzrsI == true){ZMSLTwzrsI = false;}
      if(txDOizRpSR == true){txDOizRpSR = false;}
      if(gwmmJtVAbj == true){gwmmJtVAbj = false;}
      if(kVOkbhokcu == true){kVOkbhokcu = false;}
      if(bNzDWaZcNb == true){bNzDWaZcNb = false;}
      if(jsyAMcZfCY == true){jsyAMcZfCY = false;}
      if(ZzQIWYiSlB == true){ZzQIWYiSlB = false;}
      if(JgMXoTxiQh == true){JgMXoTxiQh = false;}
      if(TrlAArXNYz == true){TrlAArXNYz = false;}
      if(HIiEUcxpfx == true){HIiEUcxpfx = false;}
      if(rHqMRDfZLs == true){rHqMRDfZLs = false;}
      if(epPTEhMPId == true){epPTEhMPId = false;}
      if(AVslsBxIDM == true){AVslsBxIDM = false;}
      if(WGCSpMBZix == true){WGCSpMBZix = false;}
      if(LxCfTQsPzm == true){LxCfTQsPzm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWGXAAYTPA
{ 
  void WyljpbKgKF()
  { 
      bool YrYFuCEdZt = false;
      bool uRlKykROJL = false;
      bool lqAjtUHlZB = false;
      bool tGHdCABCOc = false;
      bool oqyEIMBrxX = false;
      bool bBKnchqoLa = false;
      bool uSEYAnJHIx = false;
      bool jOzgVtswbg = false;
      bool SOnCYrwTAT = false;
      bool IMpnhWmZET = false;
      bool CtiAmMCdRh = false;
      bool ouMdIfdCzH = false;
      bool rpGnoXYLzz = false;
      bool HSqHeYenOM = false;
      bool pSBReNzMeB = false;
      bool rkZwbLmuKP = false;
      bool npdRaVDFzi = false;
      bool ApmmRZooIa = false;
      bool YMfxHVrufS = false;
      bool ljczXzniqJ = false;
      string gxEZrhDEMk;
      string pOQlEswTRJ;
      string boJpYaqLWn;
      string oNhOFnLdYW;
      string DooeholbTJ;
      string SIinYqnNAQ;
      string qqhYucfBfQ;
      string hSuuFmzdIj;
      string nPrNUgdtpO;
      string zxdHfMGQjE;
      string IjwCaANnik;
      string qKEPcbzUDO;
      string zlLQQknmOs;
      string fitEaDSolU;
      string ToKEXorNeE;
      string MlMUEWYelp;
      string LZYpFIPAnY;
      string IKhiuKaGsa;
      string rZIKfsVYzE;
      string enCwIsPUzP;
      if(gxEZrhDEMk == IjwCaANnik){YrYFuCEdZt = true;}
      else if(IjwCaANnik == gxEZrhDEMk){CtiAmMCdRh = true;}
      if(pOQlEswTRJ == qKEPcbzUDO){uRlKykROJL = true;}
      else if(qKEPcbzUDO == pOQlEswTRJ){ouMdIfdCzH = true;}
      if(boJpYaqLWn == zlLQQknmOs){lqAjtUHlZB = true;}
      else if(zlLQQknmOs == boJpYaqLWn){rpGnoXYLzz = true;}
      if(oNhOFnLdYW == fitEaDSolU){tGHdCABCOc = true;}
      else if(fitEaDSolU == oNhOFnLdYW){HSqHeYenOM = true;}
      if(DooeholbTJ == ToKEXorNeE){oqyEIMBrxX = true;}
      else if(ToKEXorNeE == DooeholbTJ){pSBReNzMeB = true;}
      if(SIinYqnNAQ == MlMUEWYelp){bBKnchqoLa = true;}
      else if(MlMUEWYelp == SIinYqnNAQ){rkZwbLmuKP = true;}
      if(qqhYucfBfQ == LZYpFIPAnY){uSEYAnJHIx = true;}
      else if(LZYpFIPAnY == qqhYucfBfQ){npdRaVDFzi = true;}
      if(hSuuFmzdIj == IKhiuKaGsa){jOzgVtswbg = true;}
      if(nPrNUgdtpO == rZIKfsVYzE){SOnCYrwTAT = true;}
      if(zxdHfMGQjE == enCwIsPUzP){IMpnhWmZET = true;}
      while(IKhiuKaGsa == hSuuFmzdIj){ApmmRZooIa = true;}
      while(rZIKfsVYzE == rZIKfsVYzE){YMfxHVrufS = true;}
      while(enCwIsPUzP == enCwIsPUzP){ljczXzniqJ = true;}
      if(YrYFuCEdZt == true){YrYFuCEdZt = false;}
      if(uRlKykROJL == true){uRlKykROJL = false;}
      if(lqAjtUHlZB == true){lqAjtUHlZB = false;}
      if(tGHdCABCOc == true){tGHdCABCOc = false;}
      if(oqyEIMBrxX == true){oqyEIMBrxX = false;}
      if(bBKnchqoLa == true){bBKnchqoLa = false;}
      if(uSEYAnJHIx == true){uSEYAnJHIx = false;}
      if(jOzgVtswbg == true){jOzgVtswbg = false;}
      if(SOnCYrwTAT == true){SOnCYrwTAT = false;}
      if(IMpnhWmZET == true){IMpnhWmZET = false;}
      if(CtiAmMCdRh == true){CtiAmMCdRh = false;}
      if(ouMdIfdCzH == true){ouMdIfdCzH = false;}
      if(rpGnoXYLzz == true){rpGnoXYLzz = false;}
      if(HSqHeYenOM == true){HSqHeYenOM = false;}
      if(pSBReNzMeB == true){pSBReNzMeB = false;}
      if(rkZwbLmuKP == true){rkZwbLmuKP = false;}
      if(npdRaVDFzi == true){npdRaVDFzi = false;}
      if(ApmmRZooIa == true){ApmmRZooIa = false;}
      if(YMfxHVrufS == true){YMfxHVrufS = false;}
      if(ljczXzniqJ == true){ljczXzniqJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LIRCQKAETB
{ 
  void aVOIWiIpPL()
  { 
      bool xfMxaTOJUq = false;
      bool JjflUnUbXi = false;
      bool rmboSlVRfb = false;
      bool OEwQjSVRdt = false;
      bool ofqyCKIJtN = false;
      bool xqTAAJDXdn = false;
      bool xxdrcEnPCB = false;
      bool RCyctLwdlI = false;
      bool dMWSeWjuPZ = false;
      bool PynoxqBzVy = false;
      bool WsHrutspFo = false;
      bool NZkVKkZLNF = false;
      bool UrzblSOIfD = false;
      bool JxInlkFeWj = false;
      bool csoaMoMReM = false;
      bool QplPcdseFc = false;
      bool fkKCeQRxiY = false;
      bool euoccaDXPw = false;
      bool FwcTmTKrKH = false;
      bool qZZsDqimwu = false;
      string XcEpNUVUrx;
      string FTVPqRfBir;
      string rbNyXKJUBs;
      string llaImnmAoT;
      string VfwYaYfDDy;
      string zXAJywPFRD;
      string LATzLTrMbD;
      string eeMOVLenXy;
      string dFQDsNlRJq;
      string XghkIVMxMH;
      string gSaASULlmm;
      string QahTZGiQFx;
      string haCkeyxaGA;
      string zhaPRKeQjY;
      string CzdWaxyOLB;
      string luqPZFPpUU;
      string WjflmhzSBO;
      string aSfguhwfJh;
      string ziPEODpLpM;
      string uowOBSTrjr;
      if(XcEpNUVUrx == gSaASULlmm){xfMxaTOJUq = true;}
      else if(gSaASULlmm == XcEpNUVUrx){WsHrutspFo = true;}
      if(FTVPqRfBir == QahTZGiQFx){JjflUnUbXi = true;}
      else if(QahTZGiQFx == FTVPqRfBir){NZkVKkZLNF = true;}
      if(rbNyXKJUBs == haCkeyxaGA){rmboSlVRfb = true;}
      else if(haCkeyxaGA == rbNyXKJUBs){UrzblSOIfD = true;}
      if(llaImnmAoT == zhaPRKeQjY){OEwQjSVRdt = true;}
      else if(zhaPRKeQjY == llaImnmAoT){JxInlkFeWj = true;}
      if(VfwYaYfDDy == CzdWaxyOLB){ofqyCKIJtN = true;}
      else if(CzdWaxyOLB == VfwYaYfDDy){csoaMoMReM = true;}
      if(zXAJywPFRD == luqPZFPpUU){xqTAAJDXdn = true;}
      else if(luqPZFPpUU == zXAJywPFRD){QplPcdseFc = true;}
      if(LATzLTrMbD == WjflmhzSBO){xxdrcEnPCB = true;}
      else if(WjflmhzSBO == LATzLTrMbD){fkKCeQRxiY = true;}
      if(eeMOVLenXy == aSfguhwfJh){RCyctLwdlI = true;}
      if(dFQDsNlRJq == ziPEODpLpM){dMWSeWjuPZ = true;}
      if(XghkIVMxMH == uowOBSTrjr){PynoxqBzVy = true;}
      while(aSfguhwfJh == eeMOVLenXy){euoccaDXPw = true;}
      while(ziPEODpLpM == ziPEODpLpM){FwcTmTKrKH = true;}
      while(uowOBSTrjr == uowOBSTrjr){qZZsDqimwu = true;}
      if(xfMxaTOJUq == true){xfMxaTOJUq = false;}
      if(JjflUnUbXi == true){JjflUnUbXi = false;}
      if(rmboSlVRfb == true){rmboSlVRfb = false;}
      if(OEwQjSVRdt == true){OEwQjSVRdt = false;}
      if(ofqyCKIJtN == true){ofqyCKIJtN = false;}
      if(xqTAAJDXdn == true){xqTAAJDXdn = false;}
      if(xxdrcEnPCB == true){xxdrcEnPCB = false;}
      if(RCyctLwdlI == true){RCyctLwdlI = false;}
      if(dMWSeWjuPZ == true){dMWSeWjuPZ = false;}
      if(PynoxqBzVy == true){PynoxqBzVy = false;}
      if(WsHrutspFo == true){WsHrutspFo = false;}
      if(NZkVKkZLNF == true){NZkVKkZLNF = false;}
      if(UrzblSOIfD == true){UrzblSOIfD = false;}
      if(JxInlkFeWj == true){JxInlkFeWj = false;}
      if(csoaMoMReM == true){csoaMoMReM = false;}
      if(QplPcdseFc == true){QplPcdseFc = false;}
      if(fkKCeQRxiY == true){fkKCeQRxiY = false;}
      if(euoccaDXPw == true){euoccaDXPw = false;}
      if(FwcTmTKrKH == true){FwcTmTKrKH = false;}
      if(qZZsDqimwu == true){qZZsDqimwu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IETZLOTGNL
{ 
  void EloafFsxjO()
  { 
      bool jgROiXTrLB = false;
      bool yUJmoFOWkh = false;
      bool CRUhOXOEBz = false;
      bool KMBnXaEQsU = false;
      bool dolGgjBHVH = false;
      bool VPMhHSLiAK = false;
      bool JOqLqlTVPN = false;
      bool BxcPDNeNAd = false;
      bool WHisctzSfF = false;
      bool OUQiLOxZOu = false;
      bool QfrHGYlxdt = false;
      bool myiVnCfyix = false;
      bool mAoJzfgtEn = false;
      bool PEyFNqPalE = false;
      bool HBnkRQltuJ = false;
      bool izqRIQphIa = false;
      bool qrrpeizcIw = false;
      bool lELdpkLDrh = false;
      bool tlzuFPMgxx = false;
      bool AhSLMOJyGh = false;
      string zlerKaBHnP;
      string QRqOnsBDUd;
      string FZXzEKwKGW;
      string JwuTwXcTtB;
      string WLaRFTUWSg;
      string ITNMJZOfmA;
      string dpARFTWWRP;
      string PgJSHtzFtk;
      string oZqZOpiiKW;
      string IxgtXfKJLk;
      string xyECQaJuFO;
      string aJlBKEyZCP;
      string knMuHSAPua;
      string iosInqUoJn;
      string fmcuwzKeiS;
      string gkHuzIkJux;
      string atzefkPdNT;
      string jJQOjxKQzH;
      string IVfcsyhyIe;
      string FLtLMkmyPK;
      if(zlerKaBHnP == xyECQaJuFO){jgROiXTrLB = true;}
      else if(xyECQaJuFO == zlerKaBHnP){QfrHGYlxdt = true;}
      if(QRqOnsBDUd == aJlBKEyZCP){yUJmoFOWkh = true;}
      else if(aJlBKEyZCP == QRqOnsBDUd){myiVnCfyix = true;}
      if(FZXzEKwKGW == knMuHSAPua){CRUhOXOEBz = true;}
      else if(knMuHSAPua == FZXzEKwKGW){mAoJzfgtEn = true;}
      if(JwuTwXcTtB == iosInqUoJn){KMBnXaEQsU = true;}
      else if(iosInqUoJn == JwuTwXcTtB){PEyFNqPalE = true;}
      if(WLaRFTUWSg == fmcuwzKeiS){dolGgjBHVH = true;}
      else if(fmcuwzKeiS == WLaRFTUWSg){HBnkRQltuJ = true;}
      if(ITNMJZOfmA == gkHuzIkJux){VPMhHSLiAK = true;}
      else if(gkHuzIkJux == ITNMJZOfmA){izqRIQphIa = true;}
      if(dpARFTWWRP == atzefkPdNT){JOqLqlTVPN = true;}
      else if(atzefkPdNT == dpARFTWWRP){qrrpeizcIw = true;}
      if(PgJSHtzFtk == jJQOjxKQzH){BxcPDNeNAd = true;}
      if(oZqZOpiiKW == IVfcsyhyIe){WHisctzSfF = true;}
      if(IxgtXfKJLk == FLtLMkmyPK){OUQiLOxZOu = true;}
      while(jJQOjxKQzH == PgJSHtzFtk){lELdpkLDrh = true;}
      while(IVfcsyhyIe == IVfcsyhyIe){tlzuFPMgxx = true;}
      while(FLtLMkmyPK == FLtLMkmyPK){AhSLMOJyGh = true;}
      if(jgROiXTrLB == true){jgROiXTrLB = false;}
      if(yUJmoFOWkh == true){yUJmoFOWkh = false;}
      if(CRUhOXOEBz == true){CRUhOXOEBz = false;}
      if(KMBnXaEQsU == true){KMBnXaEQsU = false;}
      if(dolGgjBHVH == true){dolGgjBHVH = false;}
      if(VPMhHSLiAK == true){VPMhHSLiAK = false;}
      if(JOqLqlTVPN == true){JOqLqlTVPN = false;}
      if(BxcPDNeNAd == true){BxcPDNeNAd = false;}
      if(WHisctzSfF == true){WHisctzSfF = false;}
      if(OUQiLOxZOu == true){OUQiLOxZOu = false;}
      if(QfrHGYlxdt == true){QfrHGYlxdt = false;}
      if(myiVnCfyix == true){myiVnCfyix = false;}
      if(mAoJzfgtEn == true){mAoJzfgtEn = false;}
      if(PEyFNqPalE == true){PEyFNqPalE = false;}
      if(HBnkRQltuJ == true){HBnkRQltuJ = false;}
      if(izqRIQphIa == true){izqRIQphIa = false;}
      if(qrrpeizcIw == true){qrrpeizcIw = false;}
      if(lELdpkLDrh == true){lELdpkLDrh = false;}
      if(tlzuFPMgxx == true){tlzuFPMgxx = false;}
      if(AhSLMOJyGh == true){AhSLMOJyGh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMXCKISGOG
{ 
  void IytgtPRiKh()
  { 
      bool UaazkDtYKa = false;
      bool lkYurWjrKs = false;
      bool MLXYUnkeZs = false;
      bool XqBxTbnVZJ = false;
      bool hBLITHeFtg = false;
      bool ybzQOJCCex = false;
      bool RPzQDuiabP = false;
      bool iNSBKLzPEM = false;
      bool IfkrturkhK = false;
      bool YlqcqSCtEY = false;
      bool YEcdyjJxFD = false;
      bool JmxRnldGVH = false;
      bool CxrRqwWpJr = false;
      bool IEKfnECHtK = false;
      bool lteeAloYnF = false;
      bool nwYxVaLLlB = false;
      bool NTmNtEbQci = false;
      bool iWLLUIRMQF = false;
      bool HxBEDMfNJM = false;
      bool sqUswSGRjw = false;
      string SSydldKihR;
      string FzmWeQcyRU;
      string UyODkEuXXL;
      string UWEDBumZyE;
      string BVuBRSZHKK;
      string LoFtKUDtsh;
      string hlLVwhtjUi;
      string dCAMSzDNkS;
      string enNNAeRKrg;
      string rrgQWOJYEi;
      string XolbgIosbL;
      string RpJZDsYyVR;
      string QjrnqkVioD;
      string odIBtoBlgq;
      string oYhfOCiGNd;
      string pLDmSnwxku;
      string mGDXVmgHeN;
      string rmQdcrBLYo;
      string CPVLMcaViG;
      string rDBlEiUKJb;
      if(SSydldKihR == XolbgIosbL){UaazkDtYKa = true;}
      else if(XolbgIosbL == SSydldKihR){YEcdyjJxFD = true;}
      if(FzmWeQcyRU == RpJZDsYyVR){lkYurWjrKs = true;}
      else if(RpJZDsYyVR == FzmWeQcyRU){JmxRnldGVH = true;}
      if(UyODkEuXXL == QjrnqkVioD){MLXYUnkeZs = true;}
      else if(QjrnqkVioD == UyODkEuXXL){CxrRqwWpJr = true;}
      if(UWEDBumZyE == odIBtoBlgq){XqBxTbnVZJ = true;}
      else if(odIBtoBlgq == UWEDBumZyE){IEKfnECHtK = true;}
      if(BVuBRSZHKK == oYhfOCiGNd){hBLITHeFtg = true;}
      else if(oYhfOCiGNd == BVuBRSZHKK){lteeAloYnF = true;}
      if(LoFtKUDtsh == pLDmSnwxku){ybzQOJCCex = true;}
      else if(pLDmSnwxku == LoFtKUDtsh){nwYxVaLLlB = true;}
      if(hlLVwhtjUi == mGDXVmgHeN){RPzQDuiabP = true;}
      else if(mGDXVmgHeN == hlLVwhtjUi){NTmNtEbQci = true;}
      if(dCAMSzDNkS == rmQdcrBLYo){iNSBKLzPEM = true;}
      if(enNNAeRKrg == CPVLMcaViG){IfkrturkhK = true;}
      if(rrgQWOJYEi == rDBlEiUKJb){YlqcqSCtEY = true;}
      while(rmQdcrBLYo == dCAMSzDNkS){iWLLUIRMQF = true;}
      while(CPVLMcaViG == CPVLMcaViG){HxBEDMfNJM = true;}
      while(rDBlEiUKJb == rDBlEiUKJb){sqUswSGRjw = true;}
      if(UaazkDtYKa == true){UaazkDtYKa = false;}
      if(lkYurWjrKs == true){lkYurWjrKs = false;}
      if(MLXYUnkeZs == true){MLXYUnkeZs = false;}
      if(XqBxTbnVZJ == true){XqBxTbnVZJ = false;}
      if(hBLITHeFtg == true){hBLITHeFtg = false;}
      if(ybzQOJCCex == true){ybzQOJCCex = false;}
      if(RPzQDuiabP == true){RPzQDuiabP = false;}
      if(iNSBKLzPEM == true){iNSBKLzPEM = false;}
      if(IfkrturkhK == true){IfkrturkhK = false;}
      if(YlqcqSCtEY == true){YlqcqSCtEY = false;}
      if(YEcdyjJxFD == true){YEcdyjJxFD = false;}
      if(JmxRnldGVH == true){JmxRnldGVH = false;}
      if(CxrRqwWpJr == true){CxrRqwWpJr = false;}
      if(IEKfnECHtK == true){IEKfnECHtK = false;}
      if(lteeAloYnF == true){lteeAloYnF = false;}
      if(nwYxVaLLlB == true){nwYxVaLLlB = false;}
      if(NTmNtEbQci == true){NTmNtEbQci = false;}
      if(iWLLUIRMQF == true){iWLLUIRMQF = false;}
      if(HxBEDMfNJM == true){HxBEDMfNJM = false;}
      if(sqUswSGRjw == true){sqUswSGRjw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CAVGENYSLL
{ 
  void myggSamdLA()
  { 
      bool ZdPNizGKGW = false;
      bool RtzzKFKcWI = false;
      bool FeUBaVQLTu = false;
      bool UyLxADDdyH = false;
      bool WVfjuVcKlP = false;
      bool hkgMAuIOmN = false;
      bool iupKCTiCyG = false;
      bool CgdPliykFE = false;
      bool rFYEMiQyxE = false;
      bool uopkYbeUgb = false;
      bool laMfNBHRaQ = false;
      bool wXIiUdWlyT = false;
      bool CkEsLMprqJ = false;
      bool EcEdRRsrqL = false;
      bool bzWfIXfHQt = false;
      bool ErWNYBVSUA = false;
      bool KOaQMTSeQD = false;
      bool kdulqCNXkn = false;
      bool gibwFLFpEQ = false;
      bool uZWpBMYFTn = false;
      string qoLcwwNIbN;
      string KQzBOuwUzp;
      string mHaumClbnV;
      string gCeXtFKTiW;
      string WgpMUtsGBQ;
      string BlChjiNPps;
      string KkUFgHkbGJ;
      string jblbTFQOZr;
      string JfaWUuzxmK;
      string qucoMkMjfN;
      string IQzqgYzaNe;
      string SzoyjeKxkk;
      string HmowRnzwPh;
      string rfhMirfiou;
      string wYjHrqGeFg;
      string aOzuFVbDYr;
      string ZCKellRbOq;
      string yaIoohDgDZ;
      string hTqhHdfmGN;
      string QcJxVsNEVF;
      if(qoLcwwNIbN == IQzqgYzaNe){ZdPNizGKGW = true;}
      else if(IQzqgYzaNe == qoLcwwNIbN){laMfNBHRaQ = true;}
      if(KQzBOuwUzp == SzoyjeKxkk){RtzzKFKcWI = true;}
      else if(SzoyjeKxkk == KQzBOuwUzp){wXIiUdWlyT = true;}
      if(mHaumClbnV == HmowRnzwPh){FeUBaVQLTu = true;}
      else if(HmowRnzwPh == mHaumClbnV){CkEsLMprqJ = true;}
      if(gCeXtFKTiW == rfhMirfiou){UyLxADDdyH = true;}
      else if(rfhMirfiou == gCeXtFKTiW){EcEdRRsrqL = true;}
      if(WgpMUtsGBQ == wYjHrqGeFg){WVfjuVcKlP = true;}
      else if(wYjHrqGeFg == WgpMUtsGBQ){bzWfIXfHQt = true;}
      if(BlChjiNPps == aOzuFVbDYr){hkgMAuIOmN = true;}
      else if(aOzuFVbDYr == BlChjiNPps){ErWNYBVSUA = true;}
      if(KkUFgHkbGJ == ZCKellRbOq){iupKCTiCyG = true;}
      else if(ZCKellRbOq == KkUFgHkbGJ){KOaQMTSeQD = true;}
      if(jblbTFQOZr == yaIoohDgDZ){CgdPliykFE = true;}
      if(JfaWUuzxmK == hTqhHdfmGN){rFYEMiQyxE = true;}
      if(qucoMkMjfN == QcJxVsNEVF){uopkYbeUgb = true;}
      while(yaIoohDgDZ == jblbTFQOZr){kdulqCNXkn = true;}
      while(hTqhHdfmGN == hTqhHdfmGN){gibwFLFpEQ = true;}
      while(QcJxVsNEVF == QcJxVsNEVF){uZWpBMYFTn = true;}
      if(ZdPNizGKGW == true){ZdPNizGKGW = false;}
      if(RtzzKFKcWI == true){RtzzKFKcWI = false;}
      if(FeUBaVQLTu == true){FeUBaVQLTu = false;}
      if(UyLxADDdyH == true){UyLxADDdyH = false;}
      if(WVfjuVcKlP == true){WVfjuVcKlP = false;}
      if(hkgMAuIOmN == true){hkgMAuIOmN = false;}
      if(iupKCTiCyG == true){iupKCTiCyG = false;}
      if(CgdPliykFE == true){CgdPliykFE = false;}
      if(rFYEMiQyxE == true){rFYEMiQyxE = false;}
      if(uopkYbeUgb == true){uopkYbeUgb = false;}
      if(laMfNBHRaQ == true){laMfNBHRaQ = false;}
      if(wXIiUdWlyT == true){wXIiUdWlyT = false;}
      if(CkEsLMprqJ == true){CkEsLMprqJ = false;}
      if(EcEdRRsrqL == true){EcEdRRsrqL = false;}
      if(bzWfIXfHQt == true){bzWfIXfHQt = false;}
      if(ErWNYBVSUA == true){ErWNYBVSUA = false;}
      if(KOaQMTSeQD == true){KOaQMTSeQD = false;}
      if(kdulqCNXkn == true){kdulqCNXkn = false;}
      if(gibwFLFpEQ == true){gibwFLFpEQ = false;}
      if(uZWpBMYFTn == true){uZWpBMYFTn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYBCECGTRQ
{ 
  void UxjexMjYHb()
  { 
      bool ytWisSRzVm = false;
      bool fJgPEoiDti = false;
      bool CsYNsWHYGw = false;
      bool NEVPQFlmbe = false;
      bool JNjKhwypYx = false;
      bool CqyZWEUIoV = false;
      bool KrsYZbmQyy = false;
      bool CwaOZoJOfx = false;
      bool YRAIsVFusL = false;
      bool kcxGUQTKkF = false;
      bool IgqauFQjAh = false;
      bool uGcrwsrjeD = false;
      bool WqXlMYzUsI = false;
      bool UzcanrZYNn = false;
      bool FVuLQdAFJb = false;
      bool YjeghQJFNV = false;
      bool GupqMwcCDE = false;
      bool STVqxBwLUh = false;
      bool YsKRjkTurW = false;
      bool hTKqgJeDyU = false;
      string PgIUeAITpQ;
      string EUIwOSMpYH;
      string zSnZzzsjcV;
      string qShiHxRmIH;
      string BxpCJxOpIX;
      string fqIbIxshUe;
      string HYpTZlmZoQ;
      string BZgRFCbkQB;
      string jDbFpAKFZK;
      string EiRcAcGVcW;
      string KoBqWFJpVG;
      string UHRStExkcY;
      string bgzdMRHERc;
      string wFIsquBjhj;
      string qTjToxRyhu;
      string eUrDucoWeE;
      string yFYrKPyXbz;
      string CMDshHwfoP;
      string AJVVyaMFyN;
      string FeFdlltrJY;
      if(PgIUeAITpQ == KoBqWFJpVG){ytWisSRzVm = true;}
      else if(KoBqWFJpVG == PgIUeAITpQ){IgqauFQjAh = true;}
      if(EUIwOSMpYH == UHRStExkcY){fJgPEoiDti = true;}
      else if(UHRStExkcY == EUIwOSMpYH){uGcrwsrjeD = true;}
      if(zSnZzzsjcV == bgzdMRHERc){CsYNsWHYGw = true;}
      else if(bgzdMRHERc == zSnZzzsjcV){WqXlMYzUsI = true;}
      if(qShiHxRmIH == wFIsquBjhj){NEVPQFlmbe = true;}
      else if(wFIsquBjhj == qShiHxRmIH){UzcanrZYNn = true;}
      if(BxpCJxOpIX == qTjToxRyhu){JNjKhwypYx = true;}
      else if(qTjToxRyhu == BxpCJxOpIX){FVuLQdAFJb = true;}
      if(fqIbIxshUe == eUrDucoWeE){CqyZWEUIoV = true;}
      else if(eUrDucoWeE == fqIbIxshUe){YjeghQJFNV = true;}
      if(HYpTZlmZoQ == yFYrKPyXbz){KrsYZbmQyy = true;}
      else if(yFYrKPyXbz == HYpTZlmZoQ){GupqMwcCDE = true;}
      if(BZgRFCbkQB == CMDshHwfoP){CwaOZoJOfx = true;}
      if(jDbFpAKFZK == AJVVyaMFyN){YRAIsVFusL = true;}
      if(EiRcAcGVcW == FeFdlltrJY){kcxGUQTKkF = true;}
      while(CMDshHwfoP == BZgRFCbkQB){STVqxBwLUh = true;}
      while(AJVVyaMFyN == AJVVyaMFyN){YsKRjkTurW = true;}
      while(FeFdlltrJY == FeFdlltrJY){hTKqgJeDyU = true;}
      if(ytWisSRzVm == true){ytWisSRzVm = false;}
      if(fJgPEoiDti == true){fJgPEoiDti = false;}
      if(CsYNsWHYGw == true){CsYNsWHYGw = false;}
      if(NEVPQFlmbe == true){NEVPQFlmbe = false;}
      if(JNjKhwypYx == true){JNjKhwypYx = false;}
      if(CqyZWEUIoV == true){CqyZWEUIoV = false;}
      if(KrsYZbmQyy == true){KrsYZbmQyy = false;}
      if(CwaOZoJOfx == true){CwaOZoJOfx = false;}
      if(YRAIsVFusL == true){YRAIsVFusL = false;}
      if(kcxGUQTKkF == true){kcxGUQTKkF = false;}
      if(IgqauFQjAh == true){IgqauFQjAh = false;}
      if(uGcrwsrjeD == true){uGcrwsrjeD = false;}
      if(WqXlMYzUsI == true){WqXlMYzUsI = false;}
      if(UzcanrZYNn == true){UzcanrZYNn = false;}
      if(FVuLQdAFJb == true){FVuLQdAFJb = false;}
      if(YjeghQJFNV == true){YjeghQJFNV = false;}
      if(GupqMwcCDE == true){GupqMwcCDE = false;}
      if(STVqxBwLUh == true){STVqxBwLUh = false;}
      if(YsKRjkTurW == true){YsKRjkTurW = false;}
      if(hTKqgJeDyU == true){hTKqgJeDyU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZNYGYFTALB
{ 
  void eZVFybrjKe()
  { 
      bool MtHaHNnszd = false;
      bool hjxELWKQaa = false;
      bool ulXflUryFi = false;
      bool NjcDMnVuoA = false;
      bool KqDCazFcZo = false;
      bool GlcLDZWbol = false;
      bool VpmPQxHsrX = false;
      bool APbZPEiVEm = false;
      bool PPYQcaHQzl = false;
      bool QtFCeUDmkd = false;
      bool rLkBnpKCwz = false;
      bool qBWBWGQWmo = false;
      bool ppsFGGJYut = false;
      bool AujauDdWbm = false;
      bool QEUAuPXEfX = false;
      bool EgAunBSfuh = false;
      bool gkHByuQuGT = false;
      bool bttzYkVsJp = false;
      bool iFsWpTtomt = false;
      bool kyatFexTBz = false;
      string YzORBcENpW;
      string iaNSVZSrIG;
      string THBdLhOArQ;
      string XoFWauOYVW;
      string dIRyXZUbgk;
      string YXdTJRykGS;
      string OEVZysUqrZ;
      string KtWlbLoDFk;
      string NmSGrzKlMI;
      string xdSCHZmrzd;
      string FdjGadBrry;
      string cteUFblOgy;
      string iidicgbTdC;
      string XwEafiDLeO;
      string yRtNfCyxxf;
      string nXLAuWAAdt;
      string BgOoafpDoV;
      string XZjSAQoPDZ;
      string hdWxOzjDfI;
      string iCgkMQDEmz;
      if(YzORBcENpW == FdjGadBrry){MtHaHNnszd = true;}
      else if(FdjGadBrry == YzORBcENpW){rLkBnpKCwz = true;}
      if(iaNSVZSrIG == cteUFblOgy){hjxELWKQaa = true;}
      else if(cteUFblOgy == iaNSVZSrIG){qBWBWGQWmo = true;}
      if(THBdLhOArQ == iidicgbTdC){ulXflUryFi = true;}
      else if(iidicgbTdC == THBdLhOArQ){ppsFGGJYut = true;}
      if(XoFWauOYVW == XwEafiDLeO){NjcDMnVuoA = true;}
      else if(XwEafiDLeO == XoFWauOYVW){AujauDdWbm = true;}
      if(dIRyXZUbgk == yRtNfCyxxf){KqDCazFcZo = true;}
      else if(yRtNfCyxxf == dIRyXZUbgk){QEUAuPXEfX = true;}
      if(YXdTJRykGS == nXLAuWAAdt){GlcLDZWbol = true;}
      else if(nXLAuWAAdt == YXdTJRykGS){EgAunBSfuh = true;}
      if(OEVZysUqrZ == BgOoafpDoV){VpmPQxHsrX = true;}
      else if(BgOoafpDoV == OEVZysUqrZ){gkHByuQuGT = true;}
      if(KtWlbLoDFk == XZjSAQoPDZ){APbZPEiVEm = true;}
      if(NmSGrzKlMI == hdWxOzjDfI){PPYQcaHQzl = true;}
      if(xdSCHZmrzd == iCgkMQDEmz){QtFCeUDmkd = true;}
      while(XZjSAQoPDZ == KtWlbLoDFk){bttzYkVsJp = true;}
      while(hdWxOzjDfI == hdWxOzjDfI){iFsWpTtomt = true;}
      while(iCgkMQDEmz == iCgkMQDEmz){kyatFexTBz = true;}
      if(MtHaHNnszd == true){MtHaHNnszd = false;}
      if(hjxELWKQaa == true){hjxELWKQaa = false;}
      if(ulXflUryFi == true){ulXflUryFi = false;}
      if(NjcDMnVuoA == true){NjcDMnVuoA = false;}
      if(KqDCazFcZo == true){KqDCazFcZo = false;}
      if(GlcLDZWbol == true){GlcLDZWbol = false;}
      if(VpmPQxHsrX == true){VpmPQxHsrX = false;}
      if(APbZPEiVEm == true){APbZPEiVEm = false;}
      if(PPYQcaHQzl == true){PPYQcaHQzl = false;}
      if(QtFCeUDmkd == true){QtFCeUDmkd = false;}
      if(rLkBnpKCwz == true){rLkBnpKCwz = false;}
      if(qBWBWGQWmo == true){qBWBWGQWmo = false;}
      if(ppsFGGJYut == true){ppsFGGJYut = false;}
      if(AujauDdWbm == true){AujauDdWbm = false;}
      if(QEUAuPXEfX == true){QEUAuPXEfX = false;}
      if(EgAunBSfuh == true){EgAunBSfuh = false;}
      if(gkHByuQuGT == true){gkHByuQuGT = false;}
      if(bttzYkVsJp == true){bttzYkVsJp = false;}
      if(iFsWpTtomt == true){iFsWpTtomt = false;}
      if(kyatFexTBz == true){kyatFexTBz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDZQOKLZTE
{ 
  void EeLNBqmjUJ()
  { 
      bool bGEKshDhBh = false;
      bool SxHuBZKnlh = false;
      bool aOTbaxpJDz = false;
      bool uShOFdLhon = false;
      bool EFRXaFmYBR = false;
      bool wpRHkNmcjw = false;
      bool rsdClAPrpX = false;
      bool NcyxdUwuBU = false;
      bool JQIkCFAZcq = false;
      bool pixsuLaOlZ = false;
      bool ouhcDTqTdP = false;
      bool RraOmajrzf = false;
      bool zpOygeeFCR = false;
      bool tgJafOhfhi = false;
      bool NguMZyHhFU = false;
      bool ahPFazgjuY = false;
      bool nlRMVjiziY = false;
      bool rEKPSStBXh = false;
      bool WxzgqLRDAg = false;
      bool hyjIubOiqp = false;
      string ouqGolioTR;
      string krLVqyLXPy;
      string MhkDwiEEpW;
      string FOZHNdJoxn;
      string gTGkFpgrit;
      string FKUpJHKmKF;
      string hdzxLVREHM;
      string oWZbRsaAyG;
      string CMUuRutjyG;
      string TVerGCTJYj;
      string XcjWFikrXP;
      string fJoEDUJDeQ;
      string bhGBrSqgUP;
      string YRbOhZcypi;
      string KBLhZKgaok;
      string sQdHHoVhdm;
      string qDXIqNhZVd;
      string qKMwGZVYah;
      string kQriWImTGs;
      string DtUDrGdDpL;
      if(ouqGolioTR == XcjWFikrXP){bGEKshDhBh = true;}
      else if(XcjWFikrXP == ouqGolioTR){ouhcDTqTdP = true;}
      if(krLVqyLXPy == fJoEDUJDeQ){SxHuBZKnlh = true;}
      else if(fJoEDUJDeQ == krLVqyLXPy){RraOmajrzf = true;}
      if(MhkDwiEEpW == bhGBrSqgUP){aOTbaxpJDz = true;}
      else if(bhGBrSqgUP == MhkDwiEEpW){zpOygeeFCR = true;}
      if(FOZHNdJoxn == YRbOhZcypi){uShOFdLhon = true;}
      else if(YRbOhZcypi == FOZHNdJoxn){tgJafOhfhi = true;}
      if(gTGkFpgrit == KBLhZKgaok){EFRXaFmYBR = true;}
      else if(KBLhZKgaok == gTGkFpgrit){NguMZyHhFU = true;}
      if(FKUpJHKmKF == sQdHHoVhdm){wpRHkNmcjw = true;}
      else if(sQdHHoVhdm == FKUpJHKmKF){ahPFazgjuY = true;}
      if(hdzxLVREHM == qDXIqNhZVd){rsdClAPrpX = true;}
      else if(qDXIqNhZVd == hdzxLVREHM){nlRMVjiziY = true;}
      if(oWZbRsaAyG == qKMwGZVYah){NcyxdUwuBU = true;}
      if(CMUuRutjyG == kQriWImTGs){JQIkCFAZcq = true;}
      if(TVerGCTJYj == DtUDrGdDpL){pixsuLaOlZ = true;}
      while(qKMwGZVYah == oWZbRsaAyG){rEKPSStBXh = true;}
      while(kQriWImTGs == kQriWImTGs){WxzgqLRDAg = true;}
      while(DtUDrGdDpL == DtUDrGdDpL){hyjIubOiqp = true;}
      if(bGEKshDhBh == true){bGEKshDhBh = false;}
      if(SxHuBZKnlh == true){SxHuBZKnlh = false;}
      if(aOTbaxpJDz == true){aOTbaxpJDz = false;}
      if(uShOFdLhon == true){uShOFdLhon = false;}
      if(EFRXaFmYBR == true){EFRXaFmYBR = false;}
      if(wpRHkNmcjw == true){wpRHkNmcjw = false;}
      if(rsdClAPrpX == true){rsdClAPrpX = false;}
      if(NcyxdUwuBU == true){NcyxdUwuBU = false;}
      if(JQIkCFAZcq == true){JQIkCFAZcq = false;}
      if(pixsuLaOlZ == true){pixsuLaOlZ = false;}
      if(ouhcDTqTdP == true){ouhcDTqTdP = false;}
      if(RraOmajrzf == true){RraOmajrzf = false;}
      if(zpOygeeFCR == true){zpOygeeFCR = false;}
      if(tgJafOhfhi == true){tgJafOhfhi = false;}
      if(NguMZyHhFU == true){NguMZyHhFU = false;}
      if(ahPFazgjuY == true){ahPFazgjuY = false;}
      if(nlRMVjiziY == true){nlRMVjiziY = false;}
      if(rEKPSStBXh == true){rEKPSStBXh = false;}
      if(WxzgqLRDAg == true){WxzgqLRDAg = false;}
      if(hyjIubOiqp == true){hyjIubOiqp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODLHAHTAQD
{ 
  void cuiTrxpNcJ()
  { 
      bool sUIJZhlPTX = false;
      bool AmRrlKDiNU = false;
      bool prFStRKLwy = false;
      bool sYBEyqKQlQ = false;
      bool OiBDqEcgmt = false;
      bool ePSgEAPoOI = false;
      bool WZTVeblMsu = false;
      bool AmxxGHqBbo = false;
      bool ndXCScFTAy = false;
      bool bUBdsnOfYO = false;
      bool SPmrtrSUax = false;
      bool JNNZTrCRCB = false;
      bool VRMuSekTDR = false;
      bool rKbMVYqeHZ = false;
      bool KksDnNHbKB = false;
      bool lxcWrBDqYO = false;
      bool HzQIEykAEt = false;
      bool BWJbqkYIHE = false;
      bool WJICfuhETU = false;
      bool UAGrSLTjyo = false;
      string ZdptnaPnSF;
      string KBMkroIbDi;
      string jDXVfQoYrh;
      string yleRLzxrow;
      string EdlDabNadF;
      string hlzIzWFUOX;
      string lpwkGXVtYs;
      string rQmHeFRTtE;
      string CNulAMlWSo;
      string scdQJNgBwC;
      string FSBkNQzrct;
      string ElZJVXuJjt;
      string lzbjzOmVxQ;
      string XPXryiLKYi;
      string MtsXjHCTuk;
      string SXQBPGqRky;
      string ddtMVoNhKl;
      string LjkBhrFDzr;
      string MSZLyAyVbr;
      string rtZZEizgCu;
      if(ZdptnaPnSF == FSBkNQzrct){sUIJZhlPTX = true;}
      else if(FSBkNQzrct == ZdptnaPnSF){SPmrtrSUax = true;}
      if(KBMkroIbDi == ElZJVXuJjt){AmRrlKDiNU = true;}
      else if(ElZJVXuJjt == KBMkroIbDi){JNNZTrCRCB = true;}
      if(jDXVfQoYrh == lzbjzOmVxQ){prFStRKLwy = true;}
      else if(lzbjzOmVxQ == jDXVfQoYrh){VRMuSekTDR = true;}
      if(yleRLzxrow == XPXryiLKYi){sYBEyqKQlQ = true;}
      else if(XPXryiLKYi == yleRLzxrow){rKbMVYqeHZ = true;}
      if(EdlDabNadF == MtsXjHCTuk){OiBDqEcgmt = true;}
      else if(MtsXjHCTuk == EdlDabNadF){KksDnNHbKB = true;}
      if(hlzIzWFUOX == SXQBPGqRky){ePSgEAPoOI = true;}
      else if(SXQBPGqRky == hlzIzWFUOX){lxcWrBDqYO = true;}
      if(lpwkGXVtYs == ddtMVoNhKl){WZTVeblMsu = true;}
      else if(ddtMVoNhKl == lpwkGXVtYs){HzQIEykAEt = true;}
      if(rQmHeFRTtE == LjkBhrFDzr){AmxxGHqBbo = true;}
      if(CNulAMlWSo == MSZLyAyVbr){ndXCScFTAy = true;}
      if(scdQJNgBwC == rtZZEizgCu){bUBdsnOfYO = true;}
      while(LjkBhrFDzr == rQmHeFRTtE){BWJbqkYIHE = true;}
      while(MSZLyAyVbr == MSZLyAyVbr){WJICfuhETU = true;}
      while(rtZZEizgCu == rtZZEizgCu){UAGrSLTjyo = true;}
      if(sUIJZhlPTX == true){sUIJZhlPTX = false;}
      if(AmRrlKDiNU == true){AmRrlKDiNU = false;}
      if(prFStRKLwy == true){prFStRKLwy = false;}
      if(sYBEyqKQlQ == true){sYBEyqKQlQ = false;}
      if(OiBDqEcgmt == true){OiBDqEcgmt = false;}
      if(ePSgEAPoOI == true){ePSgEAPoOI = false;}
      if(WZTVeblMsu == true){WZTVeblMsu = false;}
      if(AmxxGHqBbo == true){AmxxGHqBbo = false;}
      if(ndXCScFTAy == true){ndXCScFTAy = false;}
      if(bUBdsnOfYO == true){bUBdsnOfYO = false;}
      if(SPmrtrSUax == true){SPmrtrSUax = false;}
      if(JNNZTrCRCB == true){JNNZTrCRCB = false;}
      if(VRMuSekTDR == true){VRMuSekTDR = false;}
      if(rKbMVYqeHZ == true){rKbMVYqeHZ = false;}
      if(KksDnNHbKB == true){KksDnNHbKB = false;}
      if(lxcWrBDqYO == true){lxcWrBDqYO = false;}
      if(HzQIEykAEt == true){HzQIEykAEt = false;}
      if(BWJbqkYIHE == true){BWJbqkYIHE = false;}
      if(WJICfuhETU == true){WJICfuhETU = false;}
      if(UAGrSLTjyo == true){UAGrSLTjyo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCIEZXEVGE
{ 
  void DGEHFBcOwp()
  { 
      bool sliJeVSPOo = false;
      bool XkZiosomkT = false;
      bool jdSBILlBQS = false;
      bool nuCWXLwjzq = false;
      bool yihETeFbVG = false;
      bool pLCBbOThBT = false;
      bool jRyuBchDKd = false;
      bool xFmtVAwNgc = false;
      bool GJeKccsBuI = false;
      bool rOhfGfjlDq = false;
      bool wCQrJkXHfa = false;
      bool SFAYNZlnSX = false;
      bool igHBkiWGmo = false;
      bool QKKpfDsmBq = false;
      bool EkUTplNJSg = false;
      bool twSeHPtOGZ = false;
      bool OQUqKHuJrJ = false;
      bool gymbSyLmKy = false;
      bool UMnGtUreiQ = false;
      bool IdgabmQdJi = false;
      string nZGSJBpALb;
      string wtTQaCVnKr;
      string cUBUwFxhDP;
      string oJGFcfUrhG;
      string joROSRxYhS;
      string KQYnUSYlWE;
      string EIxulmnNmt;
      string gcFEInDmBd;
      string HYzkFYjRkK;
      string HiVdBbqWbe;
      string djknkgKUef;
      string PljsweILoN;
      string CVbcmxHbCf;
      string wfKWzXmLzY;
      string OPlEtUzbhW;
      string SegNbHHIBn;
      string YiRzjiaMsX;
      string qwMQzliWhR;
      string yeseNQzwtr;
      string PeKLzfymUL;
      if(nZGSJBpALb == djknkgKUef){sliJeVSPOo = true;}
      else if(djknkgKUef == nZGSJBpALb){wCQrJkXHfa = true;}
      if(wtTQaCVnKr == PljsweILoN){XkZiosomkT = true;}
      else if(PljsweILoN == wtTQaCVnKr){SFAYNZlnSX = true;}
      if(cUBUwFxhDP == CVbcmxHbCf){jdSBILlBQS = true;}
      else if(CVbcmxHbCf == cUBUwFxhDP){igHBkiWGmo = true;}
      if(oJGFcfUrhG == wfKWzXmLzY){nuCWXLwjzq = true;}
      else if(wfKWzXmLzY == oJGFcfUrhG){QKKpfDsmBq = true;}
      if(joROSRxYhS == OPlEtUzbhW){yihETeFbVG = true;}
      else if(OPlEtUzbhW == joROSRxYhS){EkUTplNJSg = true;}
      if(KQYnUSYlWE == SegNbHHIBn){pLCBbOThBT = true;}
      else if(SegNbHHIBn == KQYnUSYlWE){twSeHPtOGZ = true;}
      if(EIxulmnNmt == YiRzjiaMsX){jRyuBchDKd = true;}
      else if(YiRzjiaMsX == EIxulmnNmt){OQUqKHuJrJ = true;}
      if(gcFEInDmBd == qwMQzliWhR){xFmtVAwNgc = true;}
      if(HYzkFYjRkK == yeseNQzwtr){GJeKccsBuI = true;}
      if(HiVdBbqWbe == PeKLzfymUL){rOhfGfjlDq = true;}
      while(qwMQzliWhR == gcFEInDmBd){gymbSyLmKy = true;}
      while(yeseNQzwtr == yeseNQzwtr){UMnGtUreiQ = true;}
      while(PeKLzfymUL == PeKLzfymUL){IdgabmQdJi = true;}
      if(sliJeVSPOo == true){sliJeVSPOo = false;}
      if(XkZiosomkT == true){XkZiosomkT = false;}
      if(jdSBILlBQS == true){jdSBILlBQS = false;}
      if(nuCWXLwjzq == true){nuCWXLwjzq = false;}
      if(yihETeFbVG == true){yihETeFbVG = false;}
      if(pLCBbOThBT == true){pLCBbOThBT = false;}
      if(jRyuBchDKd == true){jRyuBchDKd = false;}
      if(xFmtVAwNgc == true){xFmtVAwNgc = false;}
      if(GJeKccsBuI == true){GJeKccsBuI = false;}
      if(rOhfGfjlDq == true){rOhfGfjlDq = false;}
      if(wCQrJkXHfa == true){wCQrJkXHfa = false;}
      if(SFAYNZlnSX == true){SFAYNZlnSX = false;}
      if(igHBkiWGmo == true){igHBkiWGmo = false;}
      if(QKKpfDsmBq == true){QKKpfDsmBq = false;}
      if(EkUTplNJSg == true){EkUTplNJSg = false;}
      if(twSeHPtOGZ == true){twSeHPtOGZ = false;}
      if(OQUqKHuJrJ == true){OQUqKHuJrJ = false;}
      if(gymbSyLmKy == true){gymbSyLmKy = false;}
      if(UMnGtUreiQ == true){UMnGtUreiQ = false;}
      if(IdgabmQdJi == true){IdgabmQdJi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JURIUIGDPG
{ 
  void XLaAyKHRbA()
  { 
      bool YHNVXTrZnP = false;
      bool EUXkgHoFZW = false;
      bool tendcDzchC = false;
      bool hpOVntzkKO = false;
      bool PPFeopyCsW = false;
      bool zkrYssSisU = false;
      bool UPqlhNGCxm = false;
      bool IDtLGdZIol = false;
      bool EwjLCwyoct = false;
      bool aPrpsAYSxa = false;
      bool iwEGNuqgSO = false;
      bool TJtGPXfeil = false;
      bool PQYCLrLERF = false;
      bool EGLNDHrcxG = false;
      bool FQWNaQVlZU = false;
      bool UtiLLRWCuV = false;
      bool jlOMKMyfCH = false;
      bool fCgcgztLat = false;
      bool WYdxkKWzBk = false;
      bool kohbWSBJDO = false;
      string oAhuAmlYcs;
      string sBJinPOchY;
      string bCSiLQqPWz;
      string RjrMUeKAXX;
      string CLbjEGLaSi;
      string gSgTAlhzji;
      string uVBdbIIwNI;
      string FOFKVPaheF;
      string FQwnRzDYLh;
      string xLPncfKyIu;
      string xOMKdSNWxk;
      string LzTeddYNLc;
      string FjjeLtyQgo;
      string FbZjHpElKy;
      string kfaaWyqkJy;
      string GwlfoNegyj;
      string UwoIeiYjXn;
      string ZmDMqYJJIN;
      string CMGihIotus;
      string LWmadoqSum;
      if(oAhuAmlYcs == xOMKdSNWxk){YHNVXTrZnP = true;}
      else if(xOMKdSNWxk == oAhuAmlYcs){iwEGNuqgSO = true;}
      if(sBJinPOchY == LzTeddYNLc){EUXkgHoFZW = true;}
      else if(LzTeddYNLc == sBJinPOchY){TJtGPXfeil = true;}
      if(bCSiLQqPWz == FjjeLtyQgo){tendcDzchC = true;}
      else if(FjjeLtyQgo == bCSiLQqPWz){PQYCLrLERF = true;}
      if(RjrMUeKAXX == FbZjHpElKy){hpOVntzkKO = true;}
      else if(FbZjHpElKy == RjrMUeKAXX){EGLNDHrcxG = true;}
      if(CLbjEGLaSi == kfaaWyqkJy){PPFeopyCsW = true;}
      else if(kfaaWyqkJy == CLbjEGLaSi){FQWNaQVlZU = true;}
      if(gSgTAlhzji == GwlfoNegyj){zkrYssSisU = true;}
      else if(GwlfoNegyj == gSgTAlhzji){UtiLLRWCuV = true;}
      if(uVBdbIIwNI == UwoIeiYjXn){UPqlhNGCxm = true;}
      else if(UwoIeiYjXn == uVBdbIIwNI){jlOMKMyfCH = true;}
      if(FOFKVPaheF == ZmDMqYJJIN){IDtLGdZIol = true;}
      if(FQwnRzDYLh == CMGihIotus){EwjLCwyoct = true;}
      if(xLPncfKyIu == LWmadoqSum){aPrpsAYSxa = true;}
      while(ZmDMqYJJIN == FOFKVPaheF){fCgcgztLat = true;}
      while(CMGihIotus == CMGihIotus){WYdxkKWzBk = true;}
      while(LWmadoqSum == LWmadoqSum){kohbWSBJDO = true;}
      if(YHNVXTrZnP == true){YHNVXTrZnP = false;}
      if(EUXkgHoFZW == true){EUXkgHoFZW = false;}
      if(tendcDzchC == true){tendcDzchC = false;}
      if(hpOVntzkKO == true){hpOVntzkKO = false;}
      if(PPFeopyCsW == true){PPFeopyCsW = false;}
      if(zkrYssSisU == true){zkrYssSisU = false;}
      if(UPqlhNGCxm == true){UPqlhNGCxm = false;}
      if(IDtLGdZIol == true){IDtLGdZIol = false;}
      if(EwjLCwyoct == true){EwjLCwyoct = false;}
      if(aPrpsAYSxa == true){aPrpsAYSxa = false;}
      if(iwEGNuqgSO == true){iwEGNuqgSO = false;}
      if(TJtGPXfeil == true){TJtGPXfeil = false;}
      if(PQYCLrLERF == true){PQYCLrLERF = false;}
      if(EGLNDHrcxG == true){EGLNDHrcxG = false;}
      if(FQWNaQVlZU == true){FQWNaQVlZU = false;}
      if(UtiLLRWCuV == true){UtiLLRWCuV = false;}
      if(jlOMKMyfCH == true){jlOMKMyfCH = false;}
      if(fCgcgztLat == true){fCgcgztLat = false;}
      if(WYdxkKWzBk == true){WYdxkKWzBk = false;}
      if(kohbWSBJDO == true){kohbWSBJDO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSTNPHBMBV
{ 
  void XeWEuUYQMp()
  { 
      bool qsfYaJQzPL = false;
      bool dRyaWJZAhu = false;
      bool muzmwVeIOZ = false;
      bool sopUGJIUrT = false;
      bool kwdhXdMdWg = false;
      bool RdLblwtsbE = false;
      bool dHkoSoadTM = false;
      bool AFINJpQROS = false;
      bool JBlgIOcNiK = false;
      bool PPrmpcKoOi = false;
      bool ChJJgLUxRu = false;
      bool ebeJtbVEfD = false;
      bool LMuJwkMUXg = false;
      bool fbCePbqbzw = false;
      bool tfumfmjhsO = false;
      bool HGILXpmANw = false;
      bool zAZkPDZAtS = false;
      bool jsEiJfRHcI = false;
      bool AdbIYYSpHZ = false;
      bool oqODxsFKXb = false;
      string hZnZqYDCsw;
      string PhgWbzmByf;
      string CxVpBcnJwy;
      string YFDLcADzBd;
      string BswiMhkodM;
      string xfNNZkDxYN;
      string jtFuWKeVta;
      string wmzTdIBmcS;
      string rzfjArqolr;
      string wGansHnALC;
      string DPuCQKftiQ;
      string jQTFVkNVud;
      string ToiCdpLLaW;
      string TAbaPcDcTp;
      string LxGUHflVRH;
      string sSEhhNfsYZ;
      string zTSLxioros;
      string gjBFRWiOty;
      string DotSdBussC;
      string wKEsqqdtXY;
      if(hZnZqYDCsw == DPuCQKftiQ){qsfYaJQzPL = true;}
      else if(DPuCQKftiQ == hZnZqYDCsw){ChJJgLUxRu = true;}
      if(PhgWbzmByf == jQTFVkNVud){dRyaWJZAhu = true;}
      else if(jQTFVkNVud == PhgWbzmByf){ebeJtbVEfD = true;}
      if(CxVpBcnJwy == ToiCdpLLaW){muzmwVeIOZ = true;}
      else if(ToiCdpLLaW == CxVpBcnJwy){LMuJwkMUXg = true;}
      if(YFDLcADzBd == TAbaPcDcTp){sopUGJIUrT = true;}
      else if(TAbaPcDcTp == YFDLcADzBd){fbCePbqbzw = true;}
      if(BswiMhkodM == LxGUHflVRH){kwdhXdMdWg = true;}
      else if(LxGUHflVRH == BswiMhkodM){tfumfmjhsO = true;}
      if(xfNNZkDxYN == sSEhhNfsYZ){RdLblwtsbE = true;}
      else if(sSEhhNfsYZ == xfNNZkDxYN){HGILXpmANw = true;}
      if(jtFuWKeVta == zTSLxioros){dHkoSoadTM = true;}
      else if(zTSLxioros == jtFuWKeVta){zAZkPDZAtS = true;}
      if(wmzTdIBmcS == gjBFRWiOty){AFINJpQROS = true;}
      if(rzfjArqolr == DotSdBussC){JBlgIOcNiK = true;}
      if(wGansHnALC == wKEsqqdtXY){PPrmpcKoOi = true;}
      while(gjBFRWiOty == wmzTdIBmcS){jsEiJfRHcI = true;}
      while(DotSdBussC == DotSdBussC){AdbIYYSpHZ = true;}
      while(wKEsqqdtXY == wKEsqqdtXY){oqODxsFKXb = true;}
      if(qsfYaJQzPL == true){qsfYaJQzPL = false;}
      if(dRyaWJZAhu == true){dRyaWJZAhu = false;}
      if(muzmwVeIOZ == true){muzmwVeIOZ = false;}
      if(sopUGJIUrT == true){sopUGJIUrT = false;}
      if(kwdhXdMdWg == true){kwdhXdMdWg = false;}
      if(RdLblwtsbE == true){RdLblwtsbE = false;}
      if(dHkoSoadTM == true){dHkoSoadTM = false;}
      if(AFINJpQROS == true){AFINJpQROS = false;}
      if(JBlgIOcNiK == true){JBlgIOcNiK = false;}
      if(PPrmpcKoOi == true){PPrmpcKoOi = false;}
      if(ChJJgLUxRu == true){ChJJgLUxRu = false;}
      if(ebeJtbVEfD == true){ebeJtbVEfD = false;}
      if(LMuJwkMUXg == true){LMuJwkMUXg = false;}
      if(fbCePbqbzw == true){fbCePbqbzw = false;}
      if(tfumfmjhsO == true){tfumfmjhsO = false;}
      if(HGILXpmANw == true){HGILXpmANw = false;}
      if(zAZkPDZAtS == true){zAZkPDZAtS = false;}
      if(jsEiJfRHcI == true){jsEiJfRHcI = false;}
      if(AdbIYYSpHZ == true){AdbIYYSpHZ = false;}
      if(oqODxsFKXb == true){oqODxsFKXb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKIMPEYVAR
{ 
  void YGwAmWGOJj()
  { 
      bool kddWJQikNK = false;
      bool TjFnSyOyzu = false;
      bool PsmUJFyHCU = false;
      bool nODTUKPtzq = false;
      bool UPoSIaqGpP = false;
      bool NFpKirqJMD = false;
      bool RahrVEgkSI = false;
      bool hTyIZzDTMi = false;
      bool OrRmHiYrkc = false;
      bool TGguYtgxxD = false;
      bool sGmhgsGgki = false;
      bool nWwcoYJujl = false;
      bool fnApobmCif = false;
      bool SFVIoHEiFO = false;
      bool bqHBowJDFA = false;
      bool jlMKXFFxrF = false;
      bool FDyFQhBnmg = false;
      bool TZoVKngyAr = false;
      bool RixiufsLjj = false;
      bool CHpAIXsBkG = false;
      string tYPGhJnQUI;
      string RjbEBywcxN;
      string PuoheuGgYc;
      string JZJCjZXBDo;
      string BaRNwChcJQ;
      string JNklrzjgbl;
      string CHqqzqZYUb;
      string ZuZHMndakc;
      string NdWITunXJk;
      string oqZQltiZOF;
      string bIHgqNndZE;
      string UIwyYYjiWE;
      string CCOiliVIVR;
      string EDMfBEVpRG;
      string HKxFPftaqM;
      string KACKCYsYtH;
      string reHHzQuQxU;
      string CtRQwrFJSF;
      string ntQJHEBCcb;
      string KxuJNbDpGy;
      if(tYPGhJnQUI == bIHgqNndZE){kddWJQikNK = true;}
      else if(bIHgqNndZE == tYPGhJnQUI){sGmhgsGgki = true;}
      if(RjbEBywcxN == UIwyYYjiWE){TjFnSyOyzu = true;}
      else if(UIwyYYjiWE == RjbEBywcxN){nWwcoYJujl = true;}
      if(PuoheuGgYc == CCOiliVIVR){PsmUJFyHCU = true;}
      else if(CCOiliVIVR == PuoheuGgYc){fnApobmCif = true;}
      if(JZJCjZXBDo == EDMfBEVpRG){nODTUKPtzq = true;}
      else if(EDMfBEVpRG == JZJCjZXBDo){SFVIoHEiFO = true;}
      if(BaRNwChcJQ == HKxFPftaqM){UPoSIaqGpP = true;}
      else if(HKxFPftaqM == BaRNwChcJQ){bqHBowJDFA = true;}
      if(JNklrzjgbl == KACKCYsYtH){NFpKirqJMD = true;}
      else if(KACKCYsYtH == JNklrzjgbl){jlMKXFFxrF = true;}
      if(CHqqzqZYUb == reHHzQuQxU){RahrVEgkSI = true;}
      else if(reHHzQuQxU == CHqqzqZYUb){FDyFQhBnmg = true;}
      if(ZuZHMndakc == CtRQwrFJSF){hTyIZzDTMi = true;}
      if(NdWITunXJk == ntQJHEBCcb){OrRmHiYrkc = true;}
      if(oqZQltiZOF == KxuJNbDpGy){TGguYtgxxD = true;}
      while(CtRQwrFJSF == ZuZHMndakc){TZoVKngyAr = true;}
      while(ntQJHEBCcb == ntQJHEBCcb){RixiufsLjj = true;}
      while(KxuJNbDpGy == KxuJNbDpGy){CHpAIXsBkG = true;}
      if(kddWJQikNK == true){kddWJQikNK = false;}
      if(TjFnSyOyzu == true){TjFnSyOyzu = false;}
      if(PsmUJFyHCU == true){PsmUJFyHCU = false;}
      if(nODTUKPtzq == true){nODTUKPtzq = false;}
      if(UPoSIaqGpP == true){UPoSIaqGpP = false;}
      if(NFpKirqJMD == true){NFpKirqJMD = false;}
      if(RahrVEgkSI == true){RahrVEgkSI = false;}
      if(hTyIZzDTMi == true){hTyIZzDTMi = false;}
      if(OrRmHiYrkc == true){OrRmHiYrkc = false;}
      if(TGguYtgxxD == true){TGguYtgxxD = false;}
      if(sGmhgsGgki == true){sGmhgsGgki = false;}
      if(nWwcoYJujl == true){nWwcoYJujl = false;}
      if(fnApobmCif == true){fnApobmCif = false;}
      if(SFVIoHEiFO == true){SFVIoHEiFO = false;}
      if(bqHBowJDFA == true){bqHBowJDFA = false;}
      if(jlMKXFFxrF == true){jlMKXFFxrF = false;}
      if(FDyFQhBnmg == true){FDyFQhBnmg = false;}
      if(TZoVKngyAr == true){TZoVKngyAr = false;}
      if(RixiufsLjj == true){RixiufsLjj = false;}
      if(CHpAIXsBkG == true){CHpAIXsBkG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMCQDKQVJU
{ 
  void akJKhysFWe()
  { 
      bool EHdMEHrnpH = false;
      bool tlgzHkVwVn = false;
      bool CUwzNMRxQH = false;
      bool oqxGuFVcmh = false;
      bool QfotBnKoml = false;
      bool QZEOJiKeyr = false;
      bool puXhSCoZEB = false;
      bool OrJmXVfCxY = false;
      bool BbJeqOmhwL = false;
      bool updurVIGby = false;
      bool zjklWXQQqn = false;
      bool CHhZpNkrqD = false;
      bool PHdrGYONuC = false;
      bool MZayZRqXIS = false;
      bool yVpIJmIEEd = false;
      bool jQOXirGrey = false;
      bool ICVoacgizY = false;
      bool WNjXEtQUiT = false;
      bool PKJQRwLCPh = false;
      bool KyrJKuzAgf = false;
      string yCWZjsFIue;
      string csIyoKEzDP;
      string sIAkyfCQsf;
      string qAkRsTNDGw;
      string zHnNVYeHYm;
      string MsygaoBkbD;
      string pnOPnbIqFV;
      string wBrHQkUmPY;
      string BtrGTxCDpD;
      string RbbCFKrXYs;
      string QnCDpKApQo;
      string TNVCCwwIwp;
      string YEACDUZpBF;
      string sxNWHNroQI;
      string wMlAiEGYAJ;
      string OjbiUMmzzV;
      string kKoLwWzytn;
      string EHrmsMRASz;
      string NAorpIUeBu;
      string arouWlWaDL;
      if(yCWZjsFIue == QnCDpKApQo){EHdMEHrnpH = true;}
      else if(QnCDpKApQo == yCWZjsFIue){zjklWXQQqn = true;}
      if(csIyoKEzDP == TNVCCwwIwp){tlgzHkVwVn = true;}
      else if(TNVCCwwIwp == csIyoKEzDP){CHhZpNkrqD = true;}
      if(sIAkyfCQsf == YEACDUZpBF){CUwzNMRxQH = true;}
      else if(YEACDUZpBF == sIAkyfCQsf){PHdrGYONuC = true;}
      if(qAkRsTNDGw == sxNWHNroQI){oqxGuFVcmh = true;}
      else if(sxNWHNroQI == qAkRsTNDGw){MZayZRqXIS = true;}
      if(zHnNVYeHYm == wMlAiEGYAJ){QfotBnKoml = true;}
      else if(wMlAiEGYAJ == zHnNVYeHYm){yVpIJmIEEd = true;}
      if(MsygaoBkbD == OjbiUMmzzV){QZEOJiKeyr = true;}
      else if(OjbiUMmzzV == MsygaoBkbD){jQOXirGrey = true;}
      if(pnOPnbIqFV == kKoLwWzytn){puXhSCoZEB = true;}
      else if(kKoLwWzytn == pnOPnbIqFV){ICVoacgizY = true;}
      if(wBrHQkUmPY == EHrmsMRASz){OrJmXVfCxY = true;}
      if(BtrGTxCDpD == NAorpIUeBu){BbJeqOmhwL = true;}
      if(RbbCFKrXYs == arouWlWaDL){updurVIGby = true;}
      while(EHrmsMRASz == wBrHQkUmPY){WNjXEtQUiT = true;}
      while(NAorpIUeBu == NAorpIUeBu){PKJQRwLCPh = true;}
      while(arouWlWaDL == arouWlWaDL){KyrJKuzAgf = true;}
      if(EHdMEHrnpH == true){EHdMEHrnpH = false;}
      if(tlgzHkVwVn == true){tlgzHkVwVn = false;}
      if(CUwzNMRxQH == true){CUwzNMRxQH = false;}
      if(oqxGuFVcmh == true){oqxGuFVcmh = false;}
      if(QfotBnKoml == true){QfotBnKoml = false;}
      if(QZEOJiKeyr == true){QZEOJiKeyr = false;}
      if(puXhSCoZEB == true){puXhSCoZEB = false;}
      if(OrJmXVfCxY == true){OrJmXVfCxY = false;}
      if(BbJeqOmhwL == true){BbJeqOmhwL = false;}
      if(updurVIGby == true){updurVIGby = false;}
      if(zjklWXQQqn == true){zjklWXQQqn = false;}
      if(CHhZpNkrqD == true){CHhZpNkrqD = false;}
      if(PHdrGYONuC == true){PHdrGYONuC = false;}
      if(MZayZRqXIS == true){MZayZRqXIS = false;}
      if(yVpIJmIEEd == true){yVpIJmIEEd = false;}
      if(jQOXirGrey == true){jQOXirGrey = false;}
      if(ICVoacgizY == true){ICVoacgizY = false;}
      if(WNjXEtQUiT == true){WNjXEtQUiT = false;}
      if(PKJQRwLCPh == true){PKJQRwLCPh = false;}
      if(KyrJKuzAgf == true){KyrJKuzAgf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGZFVQPSHM
{ 
  void sQmLcnNpgy()
  { 
      bool eBMJkFHGOo = false;
      bool IwOEIonsbL = false;
      bool CdLuKcTokP = false;
      bool NUCwYzeGWB = false;
      bool CQGgkiKkXX = false;
      bool maUGdApQyH = false;
      bool kSVzansReJ = false;
      bool JhWZIlXdJa = false;
      bool SiQNcmzuRX = false;
      bool JNHOQjuGGx = false;
      bool prFONEDtxr = false;
      bool bLGXoBCHWm = false;
      bool nxAGAwZIJY = false;
      bool pQXMkadBzX = false;
      bool iFyYuyGjZO = false;
      bool gmjSIrryNR = false;
      bool eukYBLmtlN = false;
      bool XAIyEizaLC = false;
      bool ophtqCgEEs = false;
      bool iemhsmTZXj = false;
      string QqTDygHfOu;
      string nLlrcHbqSC;
      string XjJUysVPfC;
      string WQdisoKSpR;
      string MrICzFZbds;
      string iVxtnfhyEE;
      string LrALYWgCyn;
      string xIBApeaGVs;
      string SslmTASjuM;
      string GMOkFUqxdb;
      string XXcouZUwEI;
      string EbbLkSFNqX;
      string ExHkhktPuV;
      string mdbsUuQwqs;
      string fVfmIdjCzm;
      string OdFGXaQqHJ;
      string fEBiUazhpp;
      string BJVyqhRTcD;
      string BqPHGJXVVt;
      string eYogMaUwRg;
      if(QqTDygHfOu == XXcouZUwEI){eBMJkFHGOo = true;}
      else if(XXcouZUwEI == QqTDygHfOu){prFONEDtxr = true;}
      if(nLlrcHbqSC == EbbLkSFNqX){IwOEIonsbL = true;}
      else if(EbbLkSFNqX == nLlrcHbqSC){bLGXoBCHWm = true;}
      if(XjJUysVPfC == ExHkhktPuV){CdLuKcTokP = true;}
      else if(ExHkhktPuV == XjJUysVPfC){nxAGAwZIJY = true;}
      if(WQdisoKSpR == mdbsUuQwqs){NUCwYzeGWB = true;}
      else if(mdbsUuQwqs == WQdisoKSpR){pQXMkadBzX = true;}
      if(MrICzFZbds == fVfmIdjCzm){CQGgkiKkXX = true;}
      else if(fVfmIdjCzm == MrICzFZbds){iFyYuyGjZO = true;}
      if(iVxtnfhyEE == OdFGXaQqHJ){maUGdApQyH = true;}
      else if(OdFGXaQqHJ == iVxtnfhyEE){gmjSIrryNR = true;}
      if(LrALYWgCyn == fEBiUazhpp){kSVzansReJ = true;}
      else if(fEBiUazhpp == LrALYWgCyn){eukYBLmtlN = true;}
      if(xIBApeaGVs == BJVyqhRTcD){JhWZIlXdJa = true;}
      if(SslmTASjuM == BqPHGJXVVt){SiQNcmzuRX = true;}
      if(GMOkFUqxdb == eYogMaUwRg){JNHOQjuGGx = true;}
      while(BJVyqhRTcD == xIBApeaGVs){XAIyEizaLC = true;}
      while(BqPHGJXVVt == BqPHGJXVVt){ophtqCgEEs = true;}
      while(eYogMaUwRg == eYogMaUwRg){iemhsmTZXj = true;}
      if(eBMJkFHGOo == true){eBMJkFHGOo = false;}
      if(IwOEIonsbL == true){IwOEIonsbL = false;}
      if(CdLuKcTokP == true){CdLuKcTokP = false;}
      if(NUCwYzeGWB == true){NUCwYzeGWB = false;}
      if(CQGgkiKkXX == true){CQGgkiKkXX = false;}
      if(maUGdApQyH == true){maUGdApQyH = false;}
      if(kSVzansReJ == true){kSVzansReJ = false;}
      if(JhWZIlXdJa == true){JhWZIlXdJa = false;}
      if(SiQNcmzuRX == true){SiQNcmzuRX = false;}
      if(JNHOQjuGGx == true){JNHOQjuGGx = false;}
      if(prFONEDtxr == true){prFONEDtxr = false;}
      if(bLGXoBCHWm == true){bLGXoBCHWm = false;}
      if(nxAGAwZIJY == true){nxAGAwZIJY = false;}
      if(pQXMkadBzX == true){pQXMkadBzX = false;}
      if(iFyYuyGjZO == true){iFyYuyGjZO = false;}
      if(gmjSIrryNR == true){gmjSIrryNR = false;}
      if(eukYBLmtlN == true){eukYBLmtlN = false;}
      if(XAIyEizaLC == true){XAIyEizaLC = false;}
      if(ophtqCgEEs == true){ophtqCgEEs = false;}
      if(iemhsmTZXj == true){iemhsmTZXj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MLOBZYKDCT
{ 
  void swdTBnWHly()
  { 
      bool TYduHMhlfk = false;
      bool kUKnPjnTaI = false;
      bool cnolXRmOOC = false;
      bool ygprjzYWlI = false;
      bool SDFhjGUZse = false;
      bool wXZITfirWo = false;
      bool ZSWdlDeRDP = false;
      bool LRhSpZhHCQ = false;
      bool wMViFZHgYE = false;
      bool Qgzwhzfbuf = false;
      bool bDVcTepHSt = false;
      bool xboFsNxnXM = false;
      bool wyszzeRkjq = false;
      bool sGLVosqrPa = false;
      bool izOeGnqsDU = false;
      bool BrDijcJWdn = false;
      bool MFWbAqPTQA = false;
      bool VEXwcwjNrK = false;
      bool mXhPoBCckL = false;
      bool iTNaOdcleP = false;
      string lmSgddJkop;
      string RZTxksklTW;
      string RMAzyHVIac;
      string xFOpKMDPXo;
      string UjJshKooNj;
      string xioixZmTiW;
      string IAKMsLLcmX;
      string pUOeCgCGQm;
      string RfupeNPesk;
      string ZjgAgTZxAW;
      string zMBotbUKgQ;
      string WfCuFbFTgf;
      string ufjCxFnNxi;
      string GFGtnEeFwD;
      string rFybNtgkuE;
      string NFPTaSczqn;
      string mGMxJRZIHA;
      string xAXdmphHnD;
      string YDSsVBolSU;
      string bfNIPkrBRw;
      if(lmSgddJkop == zMBotbUKgQ){TYduHMhlfk = true;}
      else if(zMBotbUKgQ == lmSgddJkop){bDVcTepHSt = true;}
      if(RZTxksklTW == WfCuFbFTgf){kUKnPjnTaI = true;}
      else if(WfCuFbFTgf == RZTxksklTW){xboFsNxnXM = true;}
      if(RMAzyHVIac == ufjCxFnNxi){cnolXRmOOC = true;}
      else if(ufjCxFnNxi == RMAzyHVIac){wyszzeRkjq = true;}
      if(xFOpKMDPXo == GFGtnEeFwD){ygprjzYWlI = true;}
      else if(GFGtnEeFwD == xFOpKMDPXo){sGLVosqrPa = true;}
      if(UjJshKooNj == rFybNtgkuE){SDFhjGUZse = true;}
      else if(rFybNtgkuE == UjJshKooNj){izOeGnqsDU = true;}
      if(xioixZmTiW == NFPTaSczqn){wXZITfirWo = true;}
      else if(NFPTaSczqn == xioixZmTiW){BrDijcJWdn = true;}
      if(IAKMsLLcmX == mGMxJRZIHA){ZSWdlDeRDP = true;}
      else if(mGMxJRZIHA == IAKMsLLcmX){MFWbAqPTQA = true;}
      if(pUOeCgCGQm == xAXdmphHnD){LRhSpZhHCQ = true;}
      if(RfupeNPesk == YDSsVBolSU){wMViFZHgYE = true;}
      if(ZjgAgTZxAW == bfNIPkrBRw){Qgzwhzfbuf = true;}
      while(xAXdmphHnD == pUOeCgCGQm){VEXwcwjNrK = true;}
      while(YDSsVBolSU == YDSsVBolSU){mXhPoBCckL = true;}
      while(bfNIPkrBRw == bfNIPkrBRw){iTNaOdcleP = true;}
      if(TYduHMhlfk == true){TYduHMhlfk = false;}
      if(kUKnPjnTaI == true){kUKnPjnTaI = false;}
      if(cnolXRmOOC == true){cnolXRmOOC = false;}
      if(ygprjzYWlI == true){ygprjzYWlI = false;}
      if(SDFhjGUZse == true){SDFhjGUZse = false;}
      if(wXZITfirWo == true){wXZITfirWo = false;}
      if(ZSWdlDeRDP == true){ZSWdlDeRDP = false;}
      if(LRhSpZhHCQ == true){LRhSpZhHCQ = false;}
      if(wMViFZHgYE == true){wMViFZHgYE = false;}
      if(Qgzwhzfbuf == true){Qgzwhzfbuf = false;}
      if(bDVcTepHSt == true){bDVcTepHSt = false;}
      if(xboFsNxnXM == true){xboFsNxnXM = false;}
      if(wyszzeRkjq == true){wyszzeRkjq = false;}
      if(sGLVosqrPa == true){sGLVosqrPa = false;}
      if(izOeGnqsDU == true){izOeGnqsDU = false;}
      if(BrDijcJWdn == true){BrDijcJWdn = false;}
      if(MFWbAqPTQA == true){MFWbAqPTQA = false;}
      if(VEXwcwjNrK == true){VEXwcwjNrK = false;}
      if(mXhPoBCckL == true){mXhPoBCckL = false;}
      if(iTNaOdcleP == true){iTNaOdcleP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AIVBVHOQZF
{ 
  void cUKTlWPXHU()
  { 
      bool uwhzUwCRHw = false;
      bool PpJTmbcjex = false;
      bool KNEqhZYdfY = false;
      bool mYmLOHnpXM = false;
      bool rzxmDmPusM = false;
      bool fwBFYgrpQt = false;
      bool WYkiIqCxEf = false;
      bool mmLSFKPQmt = false;
      bool KdjTspWhmg = false;
      bool OxZdoSOOdL = false;
      bool kRpMYskhAN = false;
      bool RaDVjsnQpR = false;
      bool UUKXQpMgcl = false;
      bool uBmaJsmXuz = false;
      bool FnhYPnsDtw = false;
      bool exXLqPGSwh = false;
      bool fDEORPmbLp = false;
      bool FQUpMfmlIb = false;
      bool wJmgHxcbjs = false;
      bool lTbNTBiSGA = false;
      string VLuwWIeaXC;
      string XWXPqNmRTI;
      string ftAOJWsAqS;
      string xwutSoDehL;
      string wexEUXuFFn;
      string UCxsAbKflz;
      string OdjEEabdwC;
      string KIiILBwusk;
      string bmuCyuyBsq;
      string dWsiwStrAs;
      string wQJCdMSogz;
      string fOmAWbhhGJ;
      string cZjFYmOAMs;
      string HDuzoKcsXl;
      string bIUtKOjsLT;
      string kMlpQVgEdq;
      string xScnqbSmKM;
      string zoKUhTFptJ;
      string DVosItRFiT;
      string dYPfnIfgCi;
      if(VLuwWIeaXC == wQJCdMSogz){uwhzUwCRHw = true;}
      else if(wQJCdMSogz == VLuwWIeaXC){kRpMYskhAN = true;}
      if(XWXPqNmRTI == fOmAWbhhGJ){PpJTmbcjex = true;}
      else if(fOmAWbhhGJ == XWXPqNmRTI){RaDVjsnQpR = true;}
      if(ftAOJWsAqS == cZjFYmOAMs){KNEqhZYdfY = true;}
      else if(cZjFYmOAMs == ftAOJWsAqS){UUKXQpMgcl = true;}
      if(xwutSoDehL == HDuzoKcsXl){mYmLOHnpXM = true;}
      else if(HDuzoKcsXl == xwutSoDehL){uBmaJsmXuz = true;}
      if(wexEUXuFFn == bIUtKOjsLT){rzxmDmPusM = true;}
      else if(bIUtKOjsLT == wexEUXuFFn){FnhYPnsDtw = true;}
      if(UCxsAbKflz == kMlpQVgEdq){fwBFYgrpQt = true;}
      else if(kMlpQVgEdq == UCxsAbKflz){exXLqPGSwh = true;}
      if(OdjEEabdwC == xScnqbSmKM){WYkiIqCxEf = true;}
      else if(xScnqbSmKM == OdjEEabdwC){fDEORPmbLp = true;}
      if(KIiILBwusk == zoKUhTFptJ){mmLSFKPQmt = true;}
      if(bmuCyuyBsq == DVosItRFiT){KdjTspWhmg = true;}
      if(dWsiwStrAs == dYPfnIfgCi){OxZdoSOOdL = true;}
      while(zoKUhTFptJ == KIiILBwusk){FQUpMfmlIb = true;}
      while(DVosItRFiT == DVosItRFiT){wJmgHxcbjs = true;}
      while(dYPfnIfgCi == dYPfnIfgCi){lTbNTBiSGA = true;}
      if(uwhzUwCRHw == true){uwhzUwCRHw = false;}
      if(PpJTmbcjex == true){PpJTmbcjex = false;}
      if(KNEqhZYdfY == true){KNEqhZYdfY = false;}
      if(mYmLOHnpXM == true){mYmLOHnpXM = false;}
      if(rzxmDmPusM == true){rzxmDmPusM = false;}
      if(fwBFYgrpQt == true){fwBFYgrpQt = false;}
      if(WYkiIqCxEf == true){WYkiIqCxEf = false;}
      if(mmLSFKPQmt == true){mmLSFKPQmt = false;}
      if(KdjTspWhmg == true){KdjTspWhmg = false;}
      if(OxZdoSOOdL == true){OxZdoSOOdL = false;}
      if(kRpMYskhAN == true){kRpMYskhAN = false;}
      if(RaDVjsnQpR == true){RaDVjsnQpR = false;}
      if(UUKXQpMgcl == true){UUKXQpMgcl = false;}
      if(uBmaJsmXuz == true){uBmaJsmXuz = false;}
      if(FnhYPnsDtw == true){FnhYPnsDtw = false;}
      if(exXLqPGSwh == true){exXLqPGSwh = false;}
      if(fDEORPmbLp == true){fDEORPmbLp = false;}
      if(FQUpMfmlIb == true){FQUpMfmlIb = false;}
      if(wJmgHxcbjs == true){wJmgHxcbjs = false;}
      if(lTbNTBiSGA == true){lTbNTBiSGA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDIUHNUIPL
{ 
  void qteaoukWek()
  { 
      bool zzFDtsiFpo = false;
      bool uhedaIbtWh = false;
      bool IBrjRWQQUL = false;
      bool GWCjxoRgfG = false;
      bool OCCeUKJWfa = false;
      bool TJPZxyHUkW = false;
      bool cRkehXfufk = false;
      bool ptOPTGzMPH = false;
      bool NtksqxHblz = false;
      bool hxwJdxRXxw = false;
      bool eOqtjYuzGp = false;
      bool ztEdJifrmj = false;
      bool QEIfDsyElV = false;
      bool oaPTbyDqIS = false;
      bool CIUwAnrSAu = false;
      bool QYkMfaGKpq = false;
      bool apNjBXdkBK = false;
      bool eoiUhIiLeP = false;
      bool BfEpFPpDmB = false;
      bool rrARqMtjuc = false;
      string oufhlKibUZ;
      string wFzDzRlFzR;
      string qMCxXFuque;
      string pkuViZZjsq;
      string yiRxtgXCtH;
      string JWKCtcriKf;
      string OrgoiKKcTZ;
      string qBLISHtFDp;
      string hrxmVSarbG;
      string gqZMbGBcNi;
      string WtiTPHLBil;
      string ilfTyVttSP;
      string jRBNrAbygM;
      string FRqTTmJcWO;
      string HYIoXtLFOG;
      string LHJyzEsUbP;
      string eMUWgQuLAL;
      string LRXEHKILpx;
      string oWjZAyHsTP;
      string snAGjuDlIG;
      if(oufhlKibUZ == WtiTPHLBil){zzFDtsiFpo = true;}
      else if(WtiTPHLBil == oufhlKibUZ){eOqtjYuzGp = true;}
      if(wFzDzRlFzR == ilfTyVttSP){uhedaIbtWh = true;}
      else if(ilfTyVttSP == wFzDzRlFzR){ztEdJifrmj = true;}
      if(qMCxXFuque == jRBNrAbygM){IBrjRWQQUL = true;}
      else if(jRBNrAbygM == qMCxXFuque){QEIfDsyElV = true;}
      if(pkuViZZjsq == FRqTTmJcWO){GWCjxoRgfG = true;}
      else if(FRqTTmJcWO == pkuViZZjsq){oaPTbyDqIS = true;}
      if(yiRxtgXCtH == HYIoXtLFOG){OCCeUKJWfa = true;}
      else if(HYIoXtLFOG == yiRxtgXCtH){CIUwAnrSAu = true;}
      if(JWKCtcriKf == LHJyzEsUbP){TJPZxyHUkW = true;}
      else if(LHJyzEsUbP == JWKCtcriKf){QYkMfaGKpq = true;}
      if(OrgoiKKcTZ == eMUWgQuLAL){cRkehXfufk = true;}
      else if(eMUWgQuLAL == OrgoiKKcTZ){apNjBXdkBK = true;}
      if(qBLISHtFDp == LRXEHKILpx){ptOPTGzMPH = true;}
      if(hrxmVSarbG == oWjZAyHsTP){NtksqxHblz = true;}
      if(gqZMbGBcNi == snAGjuDlIG){hxwJdxRXxw = true;}
      while(LRXEHKILpx == qBLISHtFDp){eoiUhIiLeP = true;}
      while(oWjZAyHsTP == oWjZAyHsTP){BfEpFPpDmB = true;}
      while(snAGjuDlIG == snAGjuDlIG){rrARqMtjuc = true;}
      if(zzFDtsiFpo == true){zzFDtsiFpo = false;}
      if(uhedaIbtWh == true){uhedaIbtWh = false;}
      if(IBrjRWQQUL == true){IBrjRWQQUL = false;}
      if(GWCjxoRgfG == true){GWCjxoRgfG = false;}
      if(OCCeUKJWfa == true){OCCeUKJWfa = false;}
      if(TJPZxyHUkW == true){TJPZxyHUkW = false;}
      if(cRkehXfufk == true){cRkehXfufk = false;}
      if(ptOPTGzMPH == true){ptOPTGzMPH = false;}
      if(NtksqxHblz == true){NtksqxHblz = false;}
      if(hxwJdxRXxw == true){hxwJdxRXxw = false;}
      if(eOqtjYuzGp == true){eOqtjYuzGp = false;}
      if(ztEdJifrmj == true){ztEdJifrmj = false;}
      if(QEIfDsyElV == true){QEIfDsyElV = false;}
      if(oaPTbyDqIS == true){oaPTbyDqIS = false;}
      if(CIUwAnrSAu == true){CIUwAnrSAu = false;}
      if(QYkMfaGKpq == true){QYkMfaGKpq = false;}
      if(apNjBXdkBK == true){apNjBXdkBK = false;}
      if(eoiUhIiLeP == true){eoiUhIiLeP = false;}
      if(BfEpFPpDmB == true){BfEpFPpDmB = false;}
      if(rrARqMtjuc == true){rrARqMtjuc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRENSWPXOS
{ 
  void BUsuRlVLJJ()
  { 
      bool IDDooLYJJx = false;
      bool InzzOIiuTG = false;
      bool TnNXOSwibs = false;
      bool BiHFXHeUfJ = false;
      bool WNVIlPiLDz = false;
      bool ScjfmTpfZW = false;
      bool OpgPuYgtaH = false;
      bool dOOJjGSEky = false;
      bool ijecZYzaRE = false;
      bool QzuItffFMM = false;
      bool iokwVENZwg = false;
      bool BktaneKEpW = false;
      bool ZFbWpeSGOD = false;
      bool ZMrYPsziGU = false;
      bool KYdjCfETUP = false;
      bool UbPolcMNFq = false;
      bool lHKrHosULt = false;
      bool ebxUMAbqUK = false;
      bool ZzkziywCmm = false;
      bool glcPiCOlcM = false;
      string IdrkeoECJy;
      string gRYgXiwBQK;
      string yElfFUSUKd;
      string xALaLcfLWM;
      string CJJARjPulK;
      string gphlMDrLeK;
      string ViqfAgGxUu;
      string CkeDHnukOV;
      string EWizwHSYNH;
      string jUfMpSRdzk;
      string dRaqHwLddY;
      string IGxJFyzrjs;
      string NhiMKhERNo;
      string VQlcqlwrqz;
      string wntozcXVHq;
      string SZsGWwhNfZ;
      string qsQoCqUTSS;
      string BHAjwZmtNg;
      string KiJVVwWfGt;
      string EiLRICXEmH;
      if(IdrkeoECJy == dRaqHwLddY){IDDooLYJJx = true;}
      else if(dRaqHwLddY == IdrkeoECJy){iokwVENZwg = true;}
      if(gRYgXiwBQK == IGxJFyzrjs){InzzOIiuTG = true;}
      else if(IGxJFyzrjs == gRYgXiwBQK){BktaneKEpW = true;}
      if(yElfFUSUKd == NhiMKhERNo){TnNXOSwibs = true;}
      else if(NhiMKhERNo == yElfFUSUKd){ZFbWpeSGOD = true;}
      if(xALaLcfLWM == VQlcqlwrqz){BiHFXHeUfJ = true;}
      else if(VQlcqlwrqz == xALaLcfLWM){ZMrYPsziGU = true;}
      if(CJJARjPulK == wntozcXVHq){WNVIlPiLDz = true;}
      else if(wntozcXVHq == CJJARjPulK){KYdjCfETUP = true;}
      if(gphlMDrLeK == SZsGWwhNfZ){ScjfmTpfZW = true;}
      else if(SZsGWwhNfZ == gphlMDrLeK){UbPolcMNFq = true;}
      if(ViqfAgGxUu == qsQoCqUTSS){OpgPuYgtaH = true;}
      else if(qsQoCqUTSS == ViqfAgGxUu){lHKrHosULt = true;}
      if(CkeDHnukOV == BHAjwZmtNg){dOOJjGSEky = true;}
      if(EWizwHSYNH == KiJVVwWfGt){ijecZYzaRE = true;}
      if(jUfMpSRdzk == EiLRICXEmH){QzuItffFMM = true;}
      while(BHAjwZmtNg == CkeDHnukOV){ebxUMAbqUK = true;}
      while(KiJVVwWfGt == KiJVVwWfGt){ZzkziywCmm = true;}
      while(EiLRICXEmH == EiLRICXEmH){glcPiCOlcM = true;}
      if(IDDooLYJJx == true){IDDooLYJJx = false;}
      if(InzzOIiuTG == true){InzzOIiuTG = false;}
      if(TnNXOSwibs == true){TnNXOSwibs = false;}
      if(BiHFXHeUfJ == true){BiHFXHeUfJ = false;}
      if(WNVIlPiLDz == true){WNVIlPiLDz = false;}
      if(ScjfmTpfZW == true){ScjfmTpfZW = false;}
      if(OpgPuYgtaH == true){OpgPuYgtaH = false;}
      if(dOOJjGSEky == true){dOOJjGSEky = false;}
      if(ijecZYzaRE == true){ijecZYzaRE = false;}
      if(QzuItffFMM == true){QzuItffFMM = false;}
      if(iokwVENZwg == true){iokwVENZwg = false;}
      if(BktaneKEpW == true){BktaneKEpW = false;}
      if(ZFbWpeSGOD == true){ZFbWpeSGOD = false;}
      if(ZMrYPsziGU == true){ZMrYPsziGU = false;}
      if(KYdjCfETUP == true){KYdjCfETUP = false;}
      if(UbPolcMNFq == true){UbPolcMNFq = false;}
      if(lHKrHosULt == true){lHKrHosULt = false;}
      if(ebxUMAbqUK == true){ebxUMAbqUK = false;}
      if(ZzkziywCmm == true){ZzkziywCmm = false;}
      if(glcPiCOlcM == true){glcPiCOlcM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REGKYDTNKH
{ 
  void utZuwWGdet()
  { 
      bool kkJQoIcbXz = false;
      bool eMrygBAuiN = false;
      bool VRtqiBOPwU = false;
      bool imVWJxTrHI = false;
      bool OjuWtsmPzH = false;
      bool HlKViSpRhm = false;
      bool sNeCPrqUnj = false;
      bool hImaylWWxo = false;
      bool OzPoMxbznq = false;
      bool GCKTOBErGC = false;
      bool CRaOZzyiWw = false;
      bool wTTrYtxpoR = false;
      bool PqgxcfxTMx = false;
      bool hdPulxXBON = false;
      bool zrbqtmhRuT = false;
      bool DNCnlKjckt = false;
      bool CeWYOSDYFa = false;
      bool WwbbSXOoDp = false;
      bool xeXssTaaIb = false;
      bool NtPUKUVDbb = false;
      string RZXIzMVLEg;
      string ByMrsikCqy;
      string cSBchAwTbm;
      string uXZJOBxDTT;
      string YyuhjKOMCi;
      string PGjczzYtZz;
      string QCiRkdXDdr;
      string kgiXZeXSrX;
      string kiQrWomxJO;
      string bCcTDWOcxG;
      string lLiJxiXMDU;
      string bGBCOgkptu;
      string qasOQiDOTC;
      string PtUlkYzHun;
      string RZtnmVAaFW;
      string lXhBPLRUsO;
      string eIrAEhkPRo;
      string gcuGdQfFbt;
      string hcIxQqLSVZ;
      string GeOfJIgsiE;
      if(RZXIzMVLEg == lLiJxiXMDU){kkJQoIcbXz = true;}
      else if(lLiJxiXMDU == RZXIzMVLEg){CRaOZzyiWw = true;}
      if(ByMrsikCqy == bGBCOgkptu){eMrygBAuiN = true;}
      else if(bGBCOgkptu == ByMrsikCqy){wTTrYtxpoR = true;}
      if(cSBchAwTbm == qasOQiDOTC){VRtqiBOPwU = true;}
      else if(qasOQiDOTC == cSBchAwTbm){PqgxcfxTMx = true;}
      if(uXZJOBxDTT == PtUlkYzHun){imVWJxTrHI = true;}
      else if(PtUlkYzHun == uXZJOBxDTT){hdPulxXBON = true;}
      if(YyuhjKOMCi == RZtnmVAaFW){OjuWtsmPzH = true;}
      else if(RZtnmVAaFW == YyuhjKOMCi){zrbqtmhRuT = true;}
      if(PGjczzYtZz == lXhBPLRUsO){HlKViSpRhm = true;}
      else if(lXhBPLRUsO == PGjczzYtZz){DNCnlKjckt = true;}
      if(QCiRkdXDdr == eIrAEhkPRo){sNeCPrqUnj = true;}
      else if(eIrAEhkPRo == QCiRkdXDdr){CeWYOSDYFa = true;}
      if(kgiXZeXSrX == gcuGdQfFbt){hImaylWWxo = true;}
      if(kiQrWomxJO == hcIxQqLSVZ){OzPoMxbznq = true;}
      if(bCcTDWOcxG == GeOfJIgsiE){GCKTOBErGC = true;}
      while(gcuGdQfFbt == kgiXZeXSrX){WwbbSXOoDp = true;}
      while(hcIxQqLSVZ == hcIxQqLSVZ){xeXssTaaIb = true;}
      while(GeOfJIgsiE == GeOfJIgsiE){NtPUKUVDbb = true;}
      if(kkJQoIcbXz == true){kkJQoIcbXz = false;}
      if(eMrygBAuiN == true){eMrygBAuiN = false;}
      if(VRtqiBOPwU == true){VRtqiBOPwU = false;}
      if(imVWJxTrHI == true){imVWJxTrHI = false;}
      if(OjuWtsmPzH == true){OjuWtsmPzH = false;}
      if(HlKViSpRhm == true){HlKViSpRhm = false;}
      if(sNeCPrqUnj == true){sNeCPrqUnj = false;}
      if(hImaylWWxo == true){hImaylWWxo = false;}
      if(OzPoMxbznq == true){OzPoMxbznq = false;}
      if(GCKTOBErGC == true){GCKTOBErGC = false;}
      if(CRaOZzyiWw == true){CRaOZzyiWw = false;}
      if(wTTrYtxpoR == true){wTTrYtxpoR = false;}
      if(PqgxcfxTMx == true){PqgxcfxTMx = false;}
      if(hdPulxXBON == true){hdPulxXBON = false;}
      if(zrbqtmhRuT == true){zrbqtmhRuT = false;}
      if(DNCnlKjckt == true){DNCnlKjckt = false;}
      if(CeWYOSDYFa == true){CeWYOSDYFa = false;}
      if(WwbbSXOoDp == true){WwbbSXOoDp = false;}
      if(xeXssTaaIb == true){xeXssTaaIb = false;}
      if(NtPUKUVDbb == true){NtPUKUVDbb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGZALYITQZ
{ 
  void LUuKKEJuZA()
  { 
      bool gJocdIAisS = false;
      bool xsXLKfJSCa = false;
      bool QyKeldwQkt = false;
      bool zpdyKXSypF = false;
      bool AkJaSMnKJX = false;
      bool fdedRhyKpz = false;
      bool LiyySGPZAl = false;
      bool NKcwafojLY = false;
      bool plGMOULzfb = false;
      bool ZIHpsQmLIL = false;
      bool xNJWKUBhDl = false;
      bool sNyRJZblix = false;
      bool uQsXMFDlDJ = false;
      bool sdbAbbcjBt = false;
      bool TcusiLJpgT = false;
      bool oBbKQfUkKF = false;
      bool ROetsPlypg = false;
      bool xrjodRUzoA = false;
      bool uMFjUrCQiu = false;
      bool HqYucExBAS = false;
      string jeMEnKQRTD;
      string kruaKTkwQT;
      string MIcstifXPO;
      string juSiZTuaCE;
      string LnKHmRFIUM;
      string pblNmbCTJF;
      string dsCFTpZMAq;
      string XJtMHYxUFc;
      string cXCCXIIEuy;
      string QbRxZRkFnw;
      string qsHdofhYGO;
      string dhNgbGqzgK;
      string gVQCawrwmo;
      string mrfJkiQYNr;
      string ajygUiNjUS;
      string alXcPVcFDs;
      string mklQbkBEur;
      string oRlojxXigr;
      string hHaTOATCsP;
      string GLVUEoxgFi;
      if(jeMEnKQRTD == qsHdofhYGO){gJocdIAisS = true;}
      else if(qsHdofhYGO == jeMEnKQRTD){xNJWKUBhDl = true;}
      if(kruaKTkwQT == dhNgbGqzgK){xsXLKfJSCa = true;}
      else if(dhNgbGqzgK == kruaKTkwQT){sNyRJZblix = true;}
      if(MIcstifXPO == gVQCawrwmo){QyKeldwQkt = true;}
      else if(gVQCawrwmo == MIcstifXPO){uQsXMFDlDJ = true;}
      if(juSiZTuaCE == mrfJkiQYNr){zpdyKXSypF = true;}
      else if(mrfJkiQYNr == juSiZTuaCE){sdbAbbcjBt = true;}
      if(LnKHmRFIUM == ajygUiNjUS){AkJaSMnKJX = true;}
      else if(ajygUiNjUS == LnKHmRFIUM){TcusiLJpgT = true;}
      if(pblNmbCTJF == alXcPVcFDs){fdedRhyKpz = true;}
      else if(alXcPVcFDs == pblNmbCTJF){oBbKQfUkKF = true;}
      if(dsCFTpZMAq == mklQbkBEur){LiyySGPZAl = true;}
      else if(mklQbkBEur == dsCFTpZMAq){ROetsPlypg = true;}
      if(XJtMHYxUFc == oRlojxXigr){NKcwafojLY = true;}
      if(cXCCXIIEuy == hHaTOATCsP){plGMOULzfb = true;}
      if(QbRxZRkFnw == GLVUEoxgFi){ZIHpsQmLIL = true;}
      while(oRlojxXigr == XJtMHYxUFc){xrjodRUzoA = true;}
      while(hHaTOATCsP == hHaTOATCsP){uMFjUrCQiu = true;}
      while(GLVUEoxgFi == GLVUEoxgFi){HqYucExBAS = true;}
      if(gJocdIAisS == true){gJocdIAisS = false;}
      if(xsXLKfJSCa == true){xsXLKfJSCa = false;}
      if(QyKeldwQkt == true){QyKeldwQkt = false;}
      if(zpdyKXSypF == true){zpdyKXSypF = false;}
      if(AkJaSMnKJX == true){AkJaSMnKJX = false;}
      if(fdedRhyKpz == true){fdedRhyKpz = false;}
      if(LiyySGPZAl == true){LiyySGPZAl = false;}
      if(NKcwafojLY == true){NKcwafojLY = false;}
      if(plGMOULzfb == true){plGMOULzfb = false;}
      if(ZIHpsQmLIL == true){ZIHpsQmLIL = false;}
      if(xNJWKUBhDl == true){xNJWKUBhDl = false;}
      if(sNyRJZblix == true){sNyRJZblix = false;}
      if(uQsXMFDlDJ == true){uQsXMFDlDJ = false;}
      if(sdbAbbcjBt == true){sdbAbbcjBt = false;}
      if(TcusiLJpgT == true){TcusiLJpgT = false;}
      if(oBbKQfUkKF == true){oBbKQfUkKF = false;}
      if(ROetsPlypg == true){ROetsPlypg = false;}
      if(xrjodRUzoA == true){xrjodRUzoA = false;}
      if(uMFjUrCQiu == true){uMFjUrCQiu = false;}
      if(HqYucExBAS == true){HqYucExBAS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WURQBDLBXB
{ 
  void XVNolCqABc()
  { 
      bool qMWjcWiueh = false;
      bool yAaKxKcwSB = false;
      bool JMknqWUReI = false;
      bool xQqKFwoKkw = false;
      bool SskDmhEAcI = false;
      bool pbOXhdbhsG = false;
      bool CRPVjhJQEB = false;
      bool USLVhPbgBJ = false;
      bool STnVSUBTcb = false;
      bool UHQdtBcOTF = false;
      bool XmubnWQroS = false;
      bool CtgjnhctDO = false;
      bool foncgNBgbf = false;
      bool lMNukeYLhu = false;
      bool EJdKYZagoL = false;
      bool YiLFZizRuZ = false;
      bool ViPJfogkyJ = false;
      bool JQLHKWKdEG = false;
      bool mTrPHCBIVC = false;
      bool eGPIYUsUdi = false;
      string TGXxDBqigc;
      string XpXlBGUKNM;
      string nSJIuTNBaS;
      string obAVXQNGTd;
      string qJyMGBKiJs;
      string uUnbMBwPBi;
      string npHNmuoBOk;
      string rOpiVeTwBt;
      string JdqhXUnYJW;
      string TyEjpABkYL;
      string MJUYAgdEGg;
      string gANHZKyZpS;
      string GQrqQtJFsU;
      string diWpgzISgq;
      string qjSboTjxKe;
      string CbtGEwQcHG;
      string WXKkDycWZZ;
      string BfrzbWxPCw;
      string JMuOSCnPlk;
      string ieLaTSYgYq;
      if(TGXxDBqigc == MJUYAgdEGg){qMWjcWiueh = true;}
      else if(MJUYAgdEGg == TGXxDBqigc){XmubnWQroS = true;}
      if(XpXlBGUKNM == gANHZKyZpS){yAaKxKcwSB = true;}
      else if(gANHZKyZpS == XpXlBGUKNM){CtgjnhctDO = true;}
      if(nSJIuTNBaS == GQrqQtJFsU){JMknqWUReI = true;}
      else if(GQrqQtJFsU == nSJIuTNBaS){foncgNBgbf = true;}
      if(obAVXQNGTd == diWpgzISgq){xQqKFwoKkw = true;}
      else if(diWpgzISgq == obAVXQNGTd){lMNukeYLhu = true;}
      if(qJyMGBKiJs == qjSboTjxKe){SskDmhEAcI = true;}
      else if(qjSboTjxKe == qJyMGBKiJs){EJdKYZagoL = true;}
      if(uUnbMBwPBi == CbtGEwQcHG){pbOXhdbhsG = true;}
      else if(CbtGEwQcHG == uUnbMBwPBi){YiLFZizRuZ = true;}
      if(npHNmuoBOk == WXKkDycWZZ){CRPVjhJQEB = true;}
      else if(WXKkDycWZZ == npHNmuoBOk){ViPJfogkyJ = true;}
      if(rOpiVeTwBt == BfrzbWxPCw){USLVhPbgBJ = true;}
      if(JdqhXUnYJW == JMuOSCnPlk){STnVSUBTcb = true;}
      if(TyEjpABkYL == ieLaTSYgYq){UHQdtBcOTF = true;}
      while(BfrzbWxPCw == rOpiVeTwBt){JQLHKWKdEG = true;}
      while(JMuOSCnPlk == JMuOSCnPlk){mTrPHCBIVC = true;}
      while(ieLaTSYgYq == ieLaTSYgYq){eGPIYUsUdi = true;}
      if(qMWjcWiueh == true){qMWjcWiueh = false;}
      if(yAaKxKcwSB == true){yAaKxKcwSB = false;}
      if(JMknqWUReI == true){JMknqWUReI = false;}
      if(xQqKFwoKkw == true){xQqKFwoKkw = false;}
      if(SskDmhEAcI == true){SskDmhEAcI = false;}
      if(pbOXhdbhsG == true){pbOXhdbhsG = false;}
      if(CRPVjhJQEB == true){CRPVjhJQEB = false;}
      if(USLVhPbgBJ == true){USLVhPbgBJ = false;}
      if(STnVSUBTcb == true){STnVSUBTcb = false;}
      if(UHQdtBcOTF == true){UHQdtBcOTF = false;}
      if(XmubnWQroS == true){XmubnWQroS = false;}
      if(CtgjnhctDO == true){CtgjnhctDO = false;}
      if(foncgNBgbf == true){foncgNBgbf = false;}
      if(lMNukeYLhu == true){lMNukeYLhu = false;}
      if(EJdKYZagoL == true){EJdKYZagoL = false;}
      if(YiLFZizRuZ == true){YiLFZizRuZ = false;}
      if(ViPJfogkyJ == true){ViPJfogkyJ = false;}
      if(JQLHKWKdEG == true){JQLHKWKdEG = false;}
      if(mTrPHCBIVC == true){mTrPHCBIVC = false;}
      if(eGPIYUsUdi == true){eGPIYUsUdi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPILDMENZY
{ 
  void QistwhfwdJ()
  { 
      bool nTLyOhylVu = false;
      bool SqXVZSPpXa = false;
      bool FBSZyOcdgZ = false;
      bool jXJwxseFTE = false;
      bool SMPMcEDjBS = false;
      bool waUsFmAkzA = false;
      bool FTEuLuhbXf = false;
      bool nJVTHrkGxs = false;
      bool KrcNdICPpK = false;
      bool ssGTyzIUBh = false;
      bool WbLVemFBlM = false;
      bool BtnFpMppRC = false;
      bool rRkNmtCBVI = false;
      bool jQFOVigGip = false;
      bool DBccJyFAdl = false;
      bool IRCyoFpyik = false;
      bool jDfdcjnYiG = false;
      bool fjHazqnHEn = false;
      bool oCXizSOGZQ = false;
      bool riXxGzVzAZ = false;
      string YMsYnXFWKc;
      string AqrNhcityN;
      string AmKXiAPZpS;
      string NFBdNLtZrJ;
      string tFMogwYEqd;
      string pRChGkCUon;
      string HfgrOtoNAV;
      string hIBoStaUpm;
      string bKiLcwDTXb;
      string IYjEBOYUam;
      string GKEUwgQMOM;
      string KgdCLwxUOS;
      string qVoYNIXwnE;
      string UFtDfQGNOu;
      string fpELQbtgsE;
      string RDFIwjUeHm;
      string JTYKqFmaVt;
      string oiFTlARdHl;
      string NpDilQzkHw;
      string waGblMQsUL;
      if(YMsYnXFWKc == GKEUwgQMOM){nTLyOhylVu = true;}
      else if(GKEUwgQMOM == YMsYnXFWKc){WbLVemFBlM = true;}
      if(AqrNhcityN == KgdCLwxUOS){SqXVZSPpXa = true;}
      else if(KgdCLwxUOS == AqrNhcityN){BtnFpMppRC = true;}
      if(AmKXiAPZpS == qVoYNIXwnE){FBSZyOcdgZ = true;}
      else if(qVoYNIXwnE == AmKXiAPZpS){rRkNmtCBVI = true;}
      if(NFBdNLtZrJ == UFtDfQGNOu){jXJwxseFTE = true;}
      else if(UFtDfQGNOu == NFBdNLtZrJ){jQFOVigGip = true;}
      if(tFMogwYEqd == fpELQbtgsE){SMPMcEDjBS = true;}
      else if(fpELQbtgsE == tFMogwYEqd){DBccJyFAdl = true;}
      if(pRChGkCUon == RDFIwjUeHm){waUsFmAkzA = true;}
      else if(RDFIwjUeHm == pRChGkCUon){IRCyoFpyik = true;}
      if(HfgrOtoNAV == JTYKqFmaVt){FTEuLuhbXf = true;}
      else if(JTYKqFmaVt == HfgrOtoNAV){jDfdcjnYiG = true;}
      if(hIBoStaUpm == oiFTlARdHl){nJVTHrkGxs = true;}
      if(bKiLcwDTXb == NpDilQzkHw){KrcNdICPpK = true;}
      if(IYjEBOYUam == waGblMQsUL){ssGTyzIUBh = true;}
      while(oiFTlARdHl == hIBoStaUpm){fjHazqnHEn = true;}
      while(NpDilQzkHw == NpDilQzkHw){oCXizSOGZQ = true;}
      while(waGblMQsUL == waGblMQsUL){riXxGzVzAZ = true;}
      if(nTLyOhylVu == true){nTLyOhylVu = false;}
      if(SqXVZSPpXa == true){SqXVZSPpXa = false;}
      if(FBSZyOcdgZ == true){FBSZyOcdgZ = false;}
      if(jXJwxseFTE == true){jXJwxseFTE = false;}
      if(SMPMcEDjBS == true){SMPMcEDjBS = false;}
      if(waUsFmAkzA == true){waUsFmAkzA = false;}
      if(FTEuLuhbXf == true){FTEuLuhbXf = false;}
      if(nJVTHrkGxs == true){nJVTHrkGxs = false;}
      if(KrcNdICPpK == true){KrcNdICPpK = false;}
      if(ssGTyzIUBh == true){ssGTyzIUBh = false;}
      if(WbLVemFBlM == true){WbLVemFBlM = false;}
      if(BtnFpMppRC == true){BtnFpMppRC = false;}
      if(rRkNmtCBVI == true){rRkNmtCBVI = false;}
      if(jQFOVigGip == true){jQFOVigGip = false;}
      if(DBccJyFAdl == true){DBccJyFAdl = false;}
      if(IRCyoFpyik == true){IRCyoFpyik = false;}
      if(jDfdcjnYiG == true){jDfdcjnYiG = false;}
      if(fjHazqnHEn == true){fjHazqnHEn = false;}
      if(oCXizSOGZQ == true){oCXizSOGZQ = false;}
      if(riXxGzVzAZ == true){riXxGzVzAZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DESBKBZKDE
{ 
  void VnoLORxDmn()
  { 
      bool phrbfAuEgJ = false;
      bool GBiUcXRfdK = false;
      bool ZctubaGFIj = false;
      bool soGpFLKNAu = false;
      bool HdEXpbNtDG = false;
      bool mtjkcMmxzE = false;
      bool towxQQtsPQ = false;
      bool MDeiDwYWFA = false;
      bool MMBBxyFVMr = false;
      bool YMNuBRgGHY = false;
      bool gUemsiOAgg = false;
      bool nQryrgnuAS = false;
      bool KYfWqApjhl = false;
      bool PROfTqhOIN = false;
      bool jFnfEIUOCT = false;
      bool clGoNHnHus = false;
      bool seSuQVBLeA = false;
      bool zZllhFkARi = false;
      bool eagOIcKZRM = false;
      bool DZSOUElrOh = false;
      string rApDMCkjHI;
      string AuenLkNtzK;
      string DAwJresoNy;
      string PPSMmgfsCM;
      string TuqQRghjtg;
      string gXijFrDgKh;
      string JwWIskbSAd;
      string EUrmpIIfrL;
      string wJufQrghGu;
      string dzhTDXXiWg;
      string EPiPbMfusx;
      string iXnylzApqB;
      string EsLFAFlXjS;
      string jZILHgaeEE;
      string MkoJLFKihD;
      string WgqVcKDcPW;
      string ZHLaNIPcqF;
      string XVllnSECsu;
      string tCpfwCilhw;
      string cxOgdEZOwD;
      if(rApDMCkjHI == EPiPbMfusx){phrbfAuEgJ = true;}
      else if(EPiPbMfusx == rApDMCkjHI){gUemsiOAgg = true;}
      if(AuenLkNtzK == iXnylzApqB){GBiUcXRfdK = true;}
      else if(iXnylzApqB == AuenLkNtzK){nQryrgnuAS = true;}
      if(DAwJresoNy == EsLFAFlXjS){ZctubaGFIj = true;}
      else if(EsLFAFlXjS == DAwJresoNy){KYfWqApjhl = true;}
      if(PPSMmgfsCM == jZILHgaeEE){soGpFLKNAu = true;}
      else if(jZILHgaeEE == PPSMmgfsCM){PROfTqhOIN = true;}
      if(TuqQRghjtg == MkoJLFKihD){HdEXpbNtDG = true;}
      else if(MkoJLFKihD == TuqQRghjtg){jFnfEIUOCT = true;}
      if(gXijFrDgKh == WgqVcKDcPW){mtjkcMmxzE = true;}
      else if(WgqVcKDcPW == gXijFrDgKh){clGoNHnHus = true;}
      if(JwWIskbSAd == ZHLaNIPcqF){towxQQtsPQ = true;}
      else if(ZHLaNIPcqF == JwWIskbSAd){seSuQVBLeA = true;}
      if(EUrmpIIfrL == XVllnSECsu){MDeiDwYWFA = true;}
      if(wJufQrghGu == tCpfwCilhw){MMBBxyFVMr = true;}
      if(dzhTDXXiWg == cxOgdEZOwD){YMNuBRgGHY = true;}
      while(XVllnSECsu == EUrmpIIfrL){zZllhFkARi = true;}
      while(tCpfwCilhw == tCpfwCilhw){eagOIcKZRM = true;}
      while(cxOgdEZOwD == cxOgdEZOwD){DZSOUElrOh = true;}
      if(phrbfAuEgJ == true){phrbfAuEgJ = false;}
      if(GBiUcXRfdK == true){GBiUcXRfdK = false;}
      if(ZctubaGFIj == true){ZctubaGFIj = false;}
      if(soGpFLKNAu == true){soGpFLKNAu = false;}
      if(HdEXpbNtDG == true){HdEXpbNtDG = false;}
      if(mtjkcMmxzE == true){mtjkcMmxzE = false;}
      if(towxQQtsPQ == true){towxQQtsPQ = false;}
      if(MDeiDwYWFA == true){MDeiDwYWFA = false;}
      if(MMBBxyFVMr == true){MMBBxyFVMr = false;}
      if(YMNuBRgGHY == true){YMNuBRgGHY = false;}
      if(gUemsiOAgg == true){gUemsiOAgg = false;}
      if(nQryrgnuAS == true){nQryrgnuAS = false;}
      if(KYfWqApjhl == true){KYfWqApjhl = false;}
      if(PROfTqhOIN == true){PROfTqhOIN = false;}
      if(jFnfEIUOCT == true){jFnfEIUOCT = false;}
      if(clGoNHnHus == true){clGoNHnHus = false;}
      if(seSuQVBLeA == true){seSuQVBLeA = false;}
      if(zZllhFkARi == true){zZllhFkARi = false;}
      if(eagOIcKZRM == true){eagOIcKZRM = false;}
      if(DZSOUElrOh == true){DZSOUElrOh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNVVZQOMJA
{ 
  void zXCEFEfuUD()
  { 
      bool hUERalYccs = false;
      bool rYLTbEuzNO = false;
      bool yPMaOpPIzh = false;
      bool BtYWfHDxwo = false;
      bool PaJJeXboUP = false;
      bool YeKzTSIcCk = false;
      bool VQcuryznmT = false;
      bool BxCYzWFCwq = false;
      bool NZmiJWjZDN = false;
      bool zZuKSyxORg = false;
      bool YnBAOabkAx = false;
      bool NFgKWwctkV = false;
      bool OZkZUaCqGA = false;
      bool YpkPRZXmTh = false;
      bool tyZGAsrjnW = false;
      bool VDcuRzDbfm = false;
      bool XjezXWTRrx = false;
      bool XpZDaPzeZa = false;
      bool hSDidUNpxS = false;
      bool WwGgKKSZhc = false;
      string FlszpCFBof;
      string jGKBBwwpqo;
      string NErSpqlMcg;
      string XDjPWxExyo;
      string XJGRkONnkJ;
      string YsCtaAsZJy;
      string QsYIIfWueD;
      string rzqCRDyZga;
      string cxaSHdApoV;
      string EdmzYdkxIE;
      string rSJhRZBAbW;
      string CTsiVSSGBe;
      string ffGIzNMrcm;
      string SAQciJnrAh;
      string cANRTjkEdF;
      string LdwdYLMAiE;
      string MJWoDBCQzL;
      string dZFTBeSnoO;
      string bIOXanDmDX;
      string xnJwUTdXOR;
      if(FlszpCFBof == rSJhRZBAbW){hUERalYccs = true;}
      else if(rSJhRZBAbW == FlszpCFBof){YnBAOabkAx = true;}
      if(jGKBBwwpqo == CTsiVSSGBe){rYLTbEuzNO = true;}
      else if(CTsiVSSGBe == jGKBBwwpqo){NFgKWwctkV = true;}
      if(NErSpqlMcg == ffGIzNMrcm){yPMaOpPIzh = true;}
      else if(ffGIzNMrcm == NErSpqlMcg){OZkZUaCqGA = true;}
      if(XDjPWxExyo == SAQciJnrAh){BtYWfHDxwo = true;}
      else if(SAQciJnrAh == XDjPWxExyo){YpkPRZXmTh = true;}
      if(XJGRkONnkJ == cANRTjkEdF){PaJJeXboUP = true;}
      else if(cANRTjkEdF == XJGRkONnkJ){tyZGAsrjnW = true;}
      if(YsCtaAsZJy == LdwdYLMAiE){YeKzTSIcCk = true;}
      else if(LdwdYLMAiE == YsCtaAsZJy){VDcuRzDbfm = true;}
      if(QsYIIfWueD == MJWoDBCQzL){VQcuryznmT = true;}
      else if(MJWoDBCQzL == QsYIIfWueD){XjezXWTRrx = true;}
      if(rzqCRDyZga == dZFTBeSnoO){BxCYzWFCwq = true;}
      if(cxaSHdApoV == bIOXanDmDX){NZmiJWjZDN = true;}
      if(EdmzYdkxIE == xnJwUTdXOR){zZuKSyxORg = true;}
      while(dZFTBeSnoO == rzqCRDyZga){XpZDaPzeZa = true;}
      while(bIOXanDmDX == bIOXanDmDX){hSDidUNpxS = true;}
      while(xnJwUTdXOR == xnJwUTdXOR){WwGgKKSZhc = true;}
      if(hUERalYccs == true){hUERalYccs = false;}
      if(rYLTbEuzNO == true){rYLTbEuzNO = false;}
      if(yPMaOpPIzh == true){yPMaOpPIzh = false;}
      if(BtYWfHDxwo == true){BtYWfHDxwo = false;}
      if(PaJJeXboUP == true){PaJJeXboUP = false;}
      if(YeKzTSIcCk == true){YeKzTSIcCk = false;}
      if(VQcuryznmT == true){VQcuryznmT = false;}
      if(BxCYzWFCwq == true){BxCYzWFCwq = false;}
      if(NZmiJWjZDN == true){NZmiJWjZDN = false;}
      if(zZuKSyxORg == true){zZuKSyxORg = false;}
      if(YnBAOabkAx == true){YnBAOabkAx = false;}
      if(NFgKWwctkV == true){NFgKWwctkV = false;}
      if(OZkZUaCqGA == true){OZkZUaCqGA = false;}
      if(YpkPRZXmTh == true){YpkPRZXmTh = false;}
      if(tyZGAsrjnW == true){tyZGAsrjnW = false;}
      if(VDcuRzDbfm == true){VDcuRzDbfm = false;}
      if(XjezXWTRrx == true){XjezXWTRrx = false;}
      if(XpZDaPzeZa == true){XpZDaPzeZa = false;}
      if(hSDidUNpxS == true){hSDidUNpxS = false;}
      if(WwGgKKSZhc == true){WwGgKKSZhc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRDQZINESU
{ 
  void utFztaRYSR()
  { 
      bool PGHjpTtYtb = false;
      bool txuwXSrJtD = false;
      bool BQxIQtrdnP = false;
      bool nTIDNCXXmJ = false;
      bool Vtonkzkjdg = false;
      bool bsCLizJyTu = false;
      bool bPjenaoqhU = false;
      bool tUWkgGaJWR = false;
      bool IHzHnuQxUO = false;
      bool sZDqhGKKzK = false;
      bool KtBJlHVRdb = false;
      bool XzaClTPcqs = false;
      bool JqWTbUQeDa = false;
      bool wPJMGOFpVf = false;
      bool YySrpsyBEN = false;
      bool pgTGASXhhQ = false;
      bool pqODfIpOuX = false;
      bool OZHKULXdch = false;
      bool VOZpjOuDLm = false;
      bool pWIEpgjPMh = false;
      string XnLOpzgCSE;
      string CGeiaqGnqb;
      string YqVgqRQXwG;
      string VCEfkzwADo;
      string gtLUyBYZwE;
      string grgonfReWY;
      string hIGMiACyya;
      string tFkBudeBhp;
      string rqbrZcUPrF;
      string gRcdHYnzky;
      string yabUJaHftJ;
      string AQxgfpfOmF;
      string emFrtcbGsV;
      string pfPiqRPHhy;
      string UoVhEQTwyQ;
      string rZMeSLUiZf;
      string yAlXTUANoN;
      string aYfnkpQWnd;
      string IfIccPSjQf;
      string xggBzUCxOj;
      if(XnLOpzgCSE == yabUJaHftJ){PGHjpTtYtb = true;}
      else if(yabUJaHftJ == XnLOpzgCSE){KtBJlHVRdb = true;}
      if(CGeiaqGnqb == AQxgfpfOmF){txuwXSrJtD = true;}
      else if(AQxgfpfOmF == CGeiaqGnqb){XzaClTPcqs = true;}
      if(YqVgqRQXwG == emFrtcbGsV){BQxIQtrdnP = true;}
      else if(emFrtcbGsV == YqVgqRQXwG){JqWTbUQeDa = true;}
      if(VCEfkzwADo == pfPiqRPHhy){nTIDNCXXmJ = true;}
      else if(pfPiqRPHhy == VCEfkzwADo){wPJMGOFpVf = true;}
      if(gtLUyBYZwE == UoVhEQTwyQ){Vtonkzkjdg = true;}
      else if(UoVhEQTwyQ == gtLUyBYZwE){YySrpsyBEN = true;}
      if(grgonfReWY == rZMeSLUiZf){bsCLizJyTu = true;}
      else if(rZMeSLUiZf == grgonfReWY){pgTGASXhhQ = true;}
      if(hIGMiACyya == yAlXTUANoN){bPjenaoqhU = true;}
      else if(yAlXTUANoN == hIGMiACyya){pqODfIpOuX = true;}
      if(tFkBudeBhp == aYfnkpQWnd){tUWkgGaJWR = true;}
      if(rqbrZcUPrF == IfIccPSjQf){IHzHnuQxUO = true;}
      if(gRcdHYnzky == xggBzUCxOj){sZDqhGKKzK = true;}
      while(aYfnkpQWnd == tFkBudeBhp){OZHKULXdch = true;}
      while(IfIccPSjQf == IfIccPSjQf){VOZpjOuDLm = true;}
      while(xggBzUCxOj == xggBzUCxOj){pWIEpgjPMh = true;}
      if(PGHjpTtYtb == true){PGHjpTtYtb = false;}
      if(txuwXSrJtD == true){txuwXSrJtD = false;}
      if(BQxIQtrdnP == true){BQxIQtrdnP = false;}
      if(nTIDNCXXmJ == true){nTIDNCXXmJ = false;}
      if(Vtonkzkjdg == true){Vtonkzkjdg = false;}
      if(bsCLizJyTu == true){bsCLizJyTu = false;}
      if(bPjenaoqhU == true){bPjenaoqhU = false;}
      if(tUWkgGaJWR == true){tUWkgGaJWR = false;}
      if(IHzHnuQxUO == true){IHzHnuQxUO = false;}
      if(sZDqhGKKzK == true){sZDqhGKKzK = false;}
      if(KtBJlHVRdb == true){KtBJlHVRdb = false;}
      if(XzaClTPcqs == true){XzaClTPcqs = false;}
      if(JqWTbUQeDa == true){JqWTbUQeDa = false;}
      if(wPJMGOFpVf == true){wPJMGOFpVf = false;}
      if(YySrpsyBEN == true){YySrpsyBEN = false;}
      if(pgTGASXhhQ == true){pgTGASXhhQ = false;}
      if(pqODfIpOuX == true){pqODfIpOuX = false;}
      if(OZHKULXdch == true){OZHKULXdch = false;}
      if(VOZpjOuDLm == true){VOZpjOuDLm = false;}
      if(pWIEpgjPMh == true){pWIEpgjPMh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QUNHKDVUIG
{ 
  void ffnCuiuqit()
  { 
      bool kXztThMVXL = false;
      bool RxLXIQYYIT = false;
      bool LfKQQfgRgX = false;
      bool rrooeoUYDs = false;
      bool EfTfNeknHD = false;
      bool mBRoVFMicm = false;
      bool BunzSZHWsT = false;
      bool uzVOPfLeCk = false;
      bool urJdjpazSZ = false;
      bool cluQrIqUMm = false;
      bool WNunImfCZp = false;
      bool tgfqqJlKOc = false;
      bool zIESpJEEWG = false;
      bool nqROOhwUUx = false;
      bool JXZbeuFDYh = false;
      bool WfFjnOIbxz = false;
      bool iafSCCPQcJ = false;
      bool MQpRSaibnu = false;
      bool DAfnjHkhaA = false;
      bool YTWVNirGZc = false;
      string yEsGflxFFJ;
      string CoKkDwYCbM;
      string HDlgQxrjpm;
      string QbOVfyKyoA;
      string kexpsmgITt;
      string dMpPatSLpi;
      string sMPRsZaoFE;
      string lZNabbGwnc;
      string QiQuJDkytk;
      string eyIGHXPfwS;
      string MqDOIDzPny;
      string nWXMSJuUHo;
      string nbtTZmRGTD;
      string MZzVQYfClG;
      string EVJuwIZwmx;
      string buXHdjwioV;
      string lrujlOWCws;
      string dshBjSRzWQ;
      string MUTWbRCqqf;
      string bxMQUMaZJh;
      if(yEsGflxFFJ == MqDOIDzPny){kXztThMVXL = true;}
      else if(MqDOIDzPny == yEsGflxFFJ){WNunImfCZp = true;}
      if(CoKkDwYCbM == nWXMSJuUHo){RxLXIQYYIT = true;}
      else if(nWXMSJuUHo == CoKkDwYCbM){tgfqqJlKOc = true;}
      if(HDlgQxrjpm == nbtTZmRGTD){LfKQQfgRgX = true;}
      else if(nbtTZmRGTD == HDlgQxrjpm){zIESpJEEWG = true;}
      if(QbOVfyKyoA == MZzVQYfClG){rrooeoUYDs = true;}
      else if(MZzVQYfClG == QbOVfyKyoA){nqROOhwUUx = true;}
      if(kexpsmgITt == EVJuwIZwmx){EfTfNeknHD = true;}
      else if(EVJuwIZwmx == kexpsmgITt){JXZbeuFDYh = true;}
      if(dMpPatSLpi == buXHdjwioV){mBRoVFMicm = true;}
      else if(buXHdjwioV == dMpPatSLpi){WfFjnOIbxz = true;}
      if(sMPRsZaoFE == lrujlOWCws){BunzSZHWsT = true;}
      else if(lrujlOWCws == sMPRsZaoFE){iafSCCPQcJ = true;}
      if(lZNabbGwnc == dshBjSRzWQ){uzVOPfLeCk = true;}
      if(QiQuJDkytk == MUTWbRCqqf){urJdjpazSZ = true;}
      if(eyIGHXPfwS == bxMQUMaZJh){cluQrIqUMm = true;}
      while(dshBjSRzWQ == lZNabbGwnc){MQpRSaibnu = true;}
      while(MUTWbRCqqf == MUTWbRCqqf){DAfnjHkhaA = true;}
      while(bxMQUMaZJh == bxMQUMaZJh){YTWVNirGZc = true;}
      if(kXztThMVXL == true){kXztThMVXL = false;}
      if(RxLXIQYYIT == true){RxLXIQYYIT = false;}
      if(LfKQQfgRgX == true){LfKQQfgRgX = false;}
      if(rrooeoUYDs == true){rrooeoUYDs = false;}
      if(EfTfNeknHD == true){EfTfNeknHD = false;}
      if(mBRoVFMicm == true){mBRoVFMicm = false;}
      if(BunzSZHWsT == true){BunzSZHWsT = false;}
      if(uzVOPfLeCk == true){uzVOPfLeCk = false;}
      if(urJdjpazSZ == true){urJdjpazSZ = false;}
      if(cluQrIqUMm == true){cluQrIqUMm = false;}
      if(WNunImfCZp == true){WNunImfCZp = false;}
      if(tgfqqJlKOc == true){tgfqqJlKOc = false;}
      if(zIESpJEEWG == true){zIESpJEEWG = false;}
      if(nqROOhwUUx == true){nqROOhwUUx = false;}
      if(JXZbeuFDYh == true){JXZbeuFDYh = false;}
      if(WfFjnOIbxz == true){WfFjnOIbxz = false;}
      if(iafSCCPQcJ == true){iafSCCPQcJ = false;}
      if(MQpRSaibnu == true){MQpRSaibnu = false;}
      if(DAfnjHkhaA == true){DAfnjHkhaA = false;}
      if(YTWVNirGZc == true){YTWVNirGZc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOTRRRYKAZ
{ 
  void obgyDPTCXT()
  { 
      bool XEOXTlkmTW = false;
      bool jpxtCWzxCI = false;
      bool ilazebCEAb = false;
      bool SQawCFZjay = false;
      bool cZOSesLcbE = false;
      bool oHgeUldOsr = false;
      bool jflrESPBrw = false;
      bool wPVEfIWHTl = false;
      bool PZbwlKiwbP = false;
      bool bLqiOwnVOL = false;
      bool dKjfHZlczL = false;
      bool OVtGcKEpGs = false;
      bool iSYcTkXloi = false;
      bool UBrHIEownL = false;
      bool YGxPBFQkGE = false;
      bool rxPUbKkHMW = false;
      bool CzmPqNdmxX = false;
      bool UIBtUcVJaN = false;
      bool TmfkqWkWey = false;
      bool SgiQJYSgYn = false;
      string lxnXxXerdI;
      string qMhazlYuqT;
      string hJlgAdabhB;
      string qeewCugPJt;
      string lEEQcqNVsy;
      string lpoThcLHXS;
      string xDJcQLhlYD;
      string FJlxhcEUDI;
      string QEhjOBpKNY;
      string jYrpxhtbAR;
      string IbxoscErlE;
      string YpDOCrUZNO;
      string VXXzTfRuzz;
      string hbUlAnHsql;
      string xxXJAsVcmE;
      string NUOkukExUM;
      string LIrmVwVQOO;
      string kaiaQXANzZ;
      string KnIukNNipP;
      string iJXdaoFjmD;
      if(lxnXxXerdI == IbxoscErlE){XEOXTlkmTW = true;}
      else if(IbxoscErlE == lxnXxXerdI){dKjfHZlczL = true;}
      if(qMhazlYuqT == YpDOCrUZNO){jpxtCWzxCI = true;}
      else if(YpDOCrUZNO == qMhazlYuqT){OVtGcKEpGs = true;}
      if(hJlgAdabhB == VXXzTfRuzz){ilazebCEAb = true;}
      else if(VXXzTfRuzz == hJlgAdabhB){iSYcTkXloi = true;}
      if(qeewCugPJt == hbUlAnHsql){SQawCFZjay = true;}
      else if(hbUlAnHsql == qeewCugPJt){UBrHIEownL = true;}
      if(lEEQcqNVsy == xxXJAsVcmE){cZOSesLcbE = true;}
      else if(xxXJAsVcmE == lEEQcqNVsy){YGxPBFQkGE = true;}
      if(lpoThcLHXS == NUOkukExUM){oHgeUldOsr = true;}
      else if(NUOkukExUM == lpoThcLHXS){rxPUbKkHMW = true;}
      if(xDJcQLhlYD == LIrmVwVQOO){jflrESPBrw = true;}
      else if(LIrmVwVQOO == xDJcQLhlYD){CzmPqNdmxX = true;}
      if(FJlxhcEUDI == kaiaQXANzZ){wPVEfIWHTl = true;}
      if(QEhjOBpKNY == KnIukNNipP){PZbwlKiwbP = true;}
      if(jYrpxhtbAR == iJXdaoFjmD){bLqiOwnVOL = true;}
      while(kaiaQXANzZ == FJlxhcEUDI){UIBtUcVJaN = true;}
      while(KnIukNNipP == KnIukNNipP){TmfkqWkWey = true;}
      while(iJXdaoFjmD == iJXdaoFjmD){SgiQJYSgYn = true;}
      if(XEOXTlkmTW == true){XEOXTlkmTW = false;}
      if(jpxtCWzxCI == true){jpxtCWzxCI = false;}
      if(ilazebCEAb == true){ilazebCEAb = false;}
      if(SQawCFZjay == true){SQawCFZjay = false;}
      if(cZOSesLcbE == true){cZOSesLcbE = false;}
      if(oHgeUldOsr == true){oHgeUldOsr = false;}
      if(jflrESPBrw == true){jflrESPBrw = false;}
      if(wPVEfIWHTl == true){wPVEfIWHTl = false;}
      if(PZbwlKiwbP == true){PZbwlKiwbP = false;}
      if(bLqiOwnVOL == true){bLqiOwnVOL = false;}
      if(dKjfHZlczL == true){dKjfHZlczL = false;}
      if(OVtGcKEpGs == true){OVtGcKEpGs = false;}
      if(iSYcTkXloi == true){iSYcTkXloi = false;}
      if(UBrHIEownL == true){UBrHIEownL = false;}
      if(YGxPBFQkGE == true){YGxPBFQkGE = false;}
      if(rxPUbKkHMW == true){rxPUbKkHMW = false;}
      if(CzmPqNdmxX == true){CzmPqNdmxX = false;}
      if(UIBtUcVJaN == true){UIBtUcVJaN = false;}
      if(TmfkqWkWey == true){TmfkqWkWey = false;}
      if(SgiQJYSgYn == true){SgiQJYSgYn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKQDSBCEWW
{ 
  void NsKWrQmAUO()
  { 
      bool iQQkcNtqZq = false;
      bool NMzYcUksGG = false;
      bool KtEdKHasOq = false;
      bool JkstLYjaYi = false;
      bool LmgUQEuHXg = false;
      bool PtrCynMmaU = false;
      bool lAbhgbTFND = false;
      bool jKTWuXNjMG = false;
      bool MTVgbOspuW = false;
      bool MxzDxLKzmn = false;
      bool kptTwFZVHZ = false;
      bool abZTISeuGR = false;
      bool icJpqmKQZi = false;
      bool NNwXVVYBkV = false;
      bool nWiUwjWftd = false;
      bool fPsVFHgEcI = false;
      bool uJwXMMfBym = false;
      bool tdKjcLsnsG = false;
      bool QeVuDyUaSN = false;
      bool nUXbaeaKIi = false;
      string kQUIwqGwJA;
      string AAuDQCwxGl;
      string gfFiIQkuUB;
      string mGpocXiKBo;
      string ofBVNutgsK;
      string hStSJEKkze;
      string GKaHMsJFas;
      string TkuQxAeiUN;
      string VEBKTUMXfX;
      string MxKVheFtJU;
      string koFApwWcVI;
      string ZbPkIBJPmq;
      string flZCfWaZhS;
      string ukZAcgyBUX;
      string yiBWykgYNf;
      string VoGSnyPDTS;
      string VxuDMoBPIb;
      string DHuPsxjCDu;
      string pBLBxGdGLe;
      string QugBBBnyJJ;
      if(kQUIwqGwJA == koFApwWcVI){iQQkcNtqZq = true;}
      else if(koFApwWcVI == kQUIwqGwJA){kptTwFZVHZ = true;}
      if(AAuDQCwxGl == ZbPkIBJPmq){NMzYcUksGG = true;}
      else if(ZbPkIBJPmq == AAuDQCwxGl){abZTISeuGR = true;}
      if(gfFiIQkuUB == flZCfWaZhS){KtEdKHasOq = true;}
      else if(flZCfWaZhS == gfFiIQkuUB){icJpqmKQZi = true;}
      if(mGpocXiKBo == ukZAcgyBUX){JkstLYjaYi = true;}
      else if(ukZAcgyBUX == mGpocXiKBo){NNwXVVYBkV = true;}
      if(ofBVNutgsK == yiBWykgYNf){LmgUQEuHXg = true;}
      else if(yiBWykgYNf == ofBVNutgsK){nWiUwjWftd = true;}
      if(hStSJEKkze == VoGSnyPDTS){PtrCynMmaU = true;}
      else if(VoGSnyPDTS == hStSJEKkze){fPsVFHgEcI = true;}
      if(GKaHMsJFas == VxuDMoBPIb){lAbhgbTFND = true;}
      else if(VxuDMoBPIb == GKaHMsJFas){uJwXMMfBym = true;}
      if(TkuQxAeiUN == DHuPsxjCDu){jKTWuXNjMG = true;}
      if(VEBKTUMXfX == pBLBxGdGLe){MTVgbOspuW = true;}
      if(MxKVheFtJU == QugBBBnyJJ){MxzDxLKzmn = true;}
      while(DHuPsxjCDu == TkuQxAeiUN){tdKjcLsnsG = true;}
      while(pBLBxGdGLe == pBLBxGdGLe){QeVuDyUaSN = true;}
      while(QugBBBnyJJ == QugBBBnyJJ){nUXbaeaKIi = true;}
      if(iQQkcNtqZq == true){iQQkcNtqZq = false;}
      if(NMzYcUksGG == true){NMzYcUksGG = false;}
      if(KtEdKHasOq == true){KtEdKHasOq = false;}
      if(JkstLYjaYi == true){JkstLYjaYi = false;}
      if(LmgUQEuHXg == true){LmgUQEuHXg = false;}
      if(PtrCynMmaU == true){PtrCynMmaU = false;}
      if(lAbhgbTFND == true){lAbhgbTFND = false;}
      if(jKTWuXNjMG == true){jKTWuXNjMG = false;}
      if(MTVgbOspuW == true){MTVgbOspuW = false;}
      if(MxzDxLKzmn == true){MxzDxLKzmn = false;}
      if(kptTwFZVHZ == true){kptTwFZVHZ = false;}
      if(abZTISeuGR == true){abZTISeuGR = false;}
      if(icJpqmKQZi == true){icJpqmKQZi = false;}
      if(NNwXVVYBkV == true){NNwXVVYBkV = false;}
      if(nWiUwjWftd == true){nWiUwjWftd = false;}
      if(fPsVFHgEcI == true){fPsVFHgEcI = false;}
      if(uJwXMMfBym == true){uJwXMMfBym = false;}
      if(tdKjcLsnsG == true){tdKjcLsnsG = false;}
      if(QeVuDyUaSN == true){QeVuDyUaSN = false;}
      if(nUXbaeaKIi == true){nUXbaeaKIi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOMBQUZKBP
{ 
  void yUnJclKHMa()
  { 
      bool CXUenEaitd = false;
      bool yQztccdLMP = false;
      bool SCplkhHLRC = false;
      bool njigaCFhCr = false;
      bool nMQjneZbDJ = false;
      bool rwxcNzhhsF = false;
      bool xOQrpOhSSa = false;
      bool WuJTbFlFyG = false;
      bool IeHHJrmFTb = false;
      bool UXowuYuYtZ = false;
      bool xHIcmxlcBH = false;
      bool NbjmxSHJhx = false;
      bool bbzqFyGNYC = false;
      bool JMLXJBVeUM = false;
      bool FJELNrnByc = false;
      bool QlqwxUIRWn = false;
      bool pYDyyAPLdw = false;
      bool wcnVrRWmcM = false;
      bool KEOwkWVPan = false;
      bool rEHgVfGGNM = false;
      string jomxzVHDVc;
      string fBGNpRHtQR;
      string DQLSJzXcdJ;
      string IVfaMmpmjm;
      string iWwZsZUTSj;
      string scTXrTdTnA;
      string xeYLTJUfAC;
      string aTKcifUkYi;
      string dEJtPfBIhs;
      string JWzipDyjGi;
      string EoSQIYSpoL;
      string yrtEVsVdwm;
      string IMxHsDUame;
      string hjepenkslq;
      string NLTVtQctMw;
      string hTnSarrLWE;
      string DqCJdONEZh;
      string HcrEYwsaMc;
      string aaNqxOwLOm;
      string wYVgmWIJrf;
      if(jomxzVHDVc == EoSQIYSpoL){CXUenEaitd = true;}
      else if(EoSQIYSpoL == jomxzVHDVc){xHIcmxlcBH = true;}
      if(fBGNpRHtQR == yrtEVsVdwm){yQztccdLMP = true;}
      else if(yrtEVsVdwm == fBGNpRHtQR){NbjmxSHJhx = true;}
      if(DQLSJzXcdJ == IMxHsDUame){SCplkhHLRC = true;}
      else if(IMxHsDUame == DQLSJzXcdJ){bbzqFyGNYC = true;}
      if(IVfaMmpmjm == hjepenkslq){njigaCFhCr = true;}
      else if(hjepenkslq == IVfaMmpmjm){JMLXJBVeUM = true;}
      if(iWwZsZUTSj == NLTVtQctMw){nMQjneZbDJ = true;}
      else if(NLTVtQctMw == iWwZsZUTSj){FJELNrnByc = true;}
      if(scTXrTdTnA == hTnSarrLWE){rwxcNzhhsF = true;}
      else if(hTnSarrLWE == scTXrTdTnA){QlqwxUIRWn = true;}
      if(xeYLTJUfAC == DqCJdONEZh){xOQrpOhSSa = true;}
      else if(DqCJdONEZh == xeYLTJUfAC){pYDyyAPLdw = true;}
      if(aTKcifUkYi == HcrEYwsaMc){WuJTbFlFyG = true;}
      if(dEJtPfBIhs == aaNqxOwLOm){IeHHJrmFTb = true;}
      if(JWzipDyjGi == wYVgmWIJrf){UXowuYuYtZ = true;}
      while(HcrEYwsaMc == aTKcifUkYi){wcnVrRWmcM = true;}
      while(aaNqxOwLOm == aaNqxOwLOm){KEOwkWVPan = true;}
      while(wYVgmWIJrf == wYVgmWIJrf){rEHgVfGGNM = true;}
      if(CXUenEaitd == true){CXUenEaitd = false;}
      if(yQztccdLMP == true){yQztccdLMP = false;}
      if(SCplkhHLRC == true){SCplkhHLRC = false;}
      if(njigaCFhCr == true){njigaCFhCr = false;}
      if(nMQjneZbDJ == true){nMQjneZbDJ = false;}
      if(rwxcNzhhsF == true){rwxcNzhhsF = false;}
      if(xOQrpOhSSa == true){xOQrpOhSSa = false;}
      if(WuJTbFlFyG == true){WuJTbFlFyG = false;}
      if(IeHHJrmFTb == true){IeHHJrmFTb = false;}
      if(UXowuYuYtZ == true){UXowuYuYtZ = false;}
      if(xHIcmxlcBH == true){xHIcmxlcBH = false;}
      if(NbjmxSHJhx == true){NbjmxSHJhx = false;}
      if(bbzqFyGNYC == true){bbzqFyGNYC = false;}
      if(JMLXJBVeUM == true){JMLXJBVeUM = false;}
      if(FJELNrnByc == true){FJELNrnByc = false;}
      if(QlqwxUIRWn == true){QlqwxUIRWn = false;}
      if(pYDyyAPLdw == true){pYDyyAPLdw = false;}
      if(wcnVrRWmcM == true){wcnVrRWmcM = false;}
      if(KEOwkWVPan == true){KEOwkWVPan = false;}
      if(rEHgVfGGNM == true){rEHgVfGGNM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCSFTINSTB
{ 
  void onIYbwxIwJ()
  { 
      bool bEKcSehewR = false;
      bool pJPKkJgNbR = false;
      bool HhYVLiLGnn = false;
      bool OYYifmyxjF = false;
      bool CSsOOTmsSK = false;
      bool iXNDMtenRj = false;
      bool TbqICRjfdy = false;
      bool KidVPonJGq = false;
      bool uRmcFqKVWk = false;
      bool HKezlZbkMx = false;
      bool jHOTAzsrnX = false;
      bool GVganBnOCL = false;
      bool GOIrpAEdjo = false;
      bool NCxJHnDTbG = false;
      bool xShyelcELj = false;
      bool lMhBqUyVdz = false;
      bool uPIyKDXXSA = false;
      bool yUlwNmfKNE = false;
      bool XzSzCAUwSl = false;
      bool ohocKhKinb = false;
      string SfciXwhDdL;
      string oNNfXuHHIc;
      string uEwIPuSyCf;
      string LOAshzgoUp;
      string QjhbripxAr;
      string empFqOjTSc;
      string cjAxzZMTyY;
      string ORlSMLWTQg;
      string EVyKBYYuCS;
      string PNWrMfijbS;
      string VVzadNBWre;
      string rPDkYHlpwa;
      string BRReIBttGf;
      string clqxKhVWfm;
      string WBCWaAJkTE;
      string trnBQEETSc;
      string SHPMCFXFap;
      string kOJIEzOtEI;
      string qIaCkjypfF;
      string dCDDUPkoUU;
      if(SfciXwhDdL == VVzadNBWre){bEKcSehewR = true;}
      else if(VVzadNBWre == SfciXwhDdL){jHOTAzsrnX = true;}
      if(oNNfXuHHIc == rPDkYHlpwa){pJPKkJgNbR = true;}
      else if(rPDkYHlpwa == oNNfXuHHIc){GVganBnOCL = true;}
      if(uEwIPuSyCf == BRReIBttGf){HhYVLiLGnn = true;}
      else if(BRReIBttGf == uEwIPuSyCf){GOIrpAEdjo = true;}
      if(LOAshzgoUp == clqxKhVWfm){OYYifmyxjF = true;}
      else if(clqxKhVWfm == LOAshzgoUp){NCxJHnDTbG = true;}
      if(QjhbripxAr == WBCWaAJkTE){CSsOOTmsSK = true;}
      else if(WBCWaAJkTE == QjhbripxAr){xShyelcELj = true;}
      if(empFqOjTSc == trnBQEETSc){iXNDMtenRj = true;}
      else if(trnBQEETSc == empFqOjTSc){lMhBqUyVdz = true;}
      if(cjAxzZMTyY == SHPMCFXFap){TbqICRjfdy = true;}
      else if(SHPMCFXFap == cjAxzZMTyY){uPIyKDXXSA = true;}
      if(ORlSMLWTQg == kOJIEzOtEI){KidVPonJGq = true;}
      if(EVyKBYYuCS == qIaCkjypfF){uRmcFqKVWk = true;}
      if(PNWrMfijbS == dCDDUPkoUU){HKezlZbkMx = true;}
      while(kOJIEzOtEI == ORlSMLWTQg){yUlwNmfKNE = true;}
      while(qIaCkjypfF == qIaCkjypfF){XzSzCAUwSl = true;}
      while(dCDDUPkoUU == dCDDUPkoUU){ohocKhKinb = true;}
      if(bEKcSehewR == true){bEKcSehewR = false;}
      if(pJPKkJgNbR == true){pJPKkJgNbR = false;}
      if(HhYVLiLGnn == true){HhYVLiLGnn = false;}
      if(OYYifmyxjF == true){OYYifmyxjF = false;}
      if(CSsOOTmsSK == true){CSsOOTmsSK = false;}
      if(iXNDMtenRj == true){iXNDMtenRj = false;}
      if(TbqICRjfdy == true){TbqICRjfdy = false;}
      if(KidVPonJGq == true){KidVPonJGq = false;}
      if(uRmcFqKVWk == true){uRmcFqKVWk = false;}
      if(HKezlZbkMx == true){HKezlZbkMx = false;}
      if(jHOTAzsrnX == true){jHOTAzsrnX = false;}
      if(GVganBnOCL == true){GVganBnOCL = false;}
      if(GOIrpAEdjo == true){GOIrpAEdjo = false;}
      if(NCxJHnDTbG == true){NCxJHnDTbG = false;}
      if(xShyelcELj == true){xShyelcELj = false;}
      if(lMhBqUyVdz == true){lMhBqUyVdz = false;}
      if(uPIyKDXXSA == true){uPIyKDXXSA = false;}
      if(yUlwNmfKNE == true){yUlwNmfKNE = false;}
      if(XzSzCAUwSl == true){XzSzCAUwSl = false;}
      if(ohocKhKinb == true){ohocKhKinb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXDGZYPWKE
{ 
  void ouqsEGDVRK()
  { 
      bool kSQJzzHeFY = false;
      bool TZesGyGEPt = false;
      bool YYlJJissTb = false;
      bool CRZmKwEsAT = false;
      bool QfRRSDiDrF = false;
      bool IYmEeLgGzQ = false;
      bool GNLdVCzqiK = false;
      bool sMDucsGTqF = false;
      bool AoBOTdeUIy = false;
      bool PysjNCTnwP = false;
      bool EqUgLuVqbk = false;
      bool FNOtPRMwJq = false;
      bool XdikuuTShZ = false;
      bool YRWaBJTTDX = false;
      bool HnsWrBizUw = false;
      bool pXdErZHjlQ = false;
      bool aCIBMmpmrG = false;
      bool xssljikLrs = false;
      bool LUyljBnRia = false;
      bool BigmwFeqKE = false;
      string JhbzpPVWem;
      string LkcTWmEDRU;
      string EsjlEHArKD;
      string uLydDwJhsr;
      string tWcDVgoQqJ;
      string ZQaTWPxouh;
      string PcLarAlyQa;
      string dVJYZgQfQW;
      string SiBAcdjeHm;
      string yTlLbQKBLU;
      string upAQfEGBso;
      string zQYYOfaLxO;
      string PGqdbKiywJ;
      string WOUwbbikTY;
      string WilRmguNww;
      string oyDwFnzVnV;
      string UIEiSjwbxm;
      string wpqYqgTYpu;
      string OVCATXKXpm;
      string cNxyEOdCzD;
      if(JhbzpPVWem == upAQfEGBso){kSQJzzHeFY = true;}
      else if(upAQfEGBso == JhbzpPVWem){EqUgLuVqbk = true;}
      if(LkcTWmEDRU == zQYYOfaLxO){TZesGyGEPt = true;}
      else if(zQYYOfaLxO == LkcTWmEDRU){FNOtPRMwJq = true;}
      if(EsjlEHArKD == PGqdbKiywJ){YYlJJissTb = true;}
      else if(PGqdbKiywJ == EsjlEHArKD){XdikuuTShZ = true;}
      if(uLydDwJhsr == WOUwbbikTY){CRZmKwEsAT = true;}
      else if(WOUwbbikTY == uLydDwJhsr){YRWaBJTTDX = true;}
      if(tWcDVgoQqJ == WilRmguNww){QfRRSDiDrF = true;}
      else if(WilRmguNww == tWcDVgoQqJ){HnsWrBizUw = true;}
      if(ZQaTWPxouh == oyDwFnzVnV){IYmEeLgGzQ = true;}
      else if(oyDwFnzVnV == ZQaTWPxouh){pXdErZHjlQ = true;}
      if(PcLarAlyQa == UIEiSjwbxm){GNLdVCzqiK = true;}
      else if(UIEiSjwbxm == PcLarAlyQa){aCIBMmpmrG = true;}
      if(dVJYZgQfQW == wpqYqgTYpu){sMDucsGTqF = true;}
      if(SiBAcdjeHm == OVCATXKXpm){AoBOTdeUIy = true;}
      if(yTlLbQKBLU == cNxyEOdCzD){PysjNCTnwP = true;}
      while(wpqYqgTYpu == dVJYZgQfQW){xssljikLrs = true;}
      while(OVCATXKXpm == OVCATXKXpm){LUyljBnRia = true;}
      while(cNxyEOdCzD == cNxyEOdCzD){BigmwFeqKE = true;}
      if(kSQJzzHeFY == true){kSQJzzHeFY = false;}
      if(TZesGyGEPt == true){TZesGyGEPt = false;}
      if(YYlJJissTb == true){YYlJJissTb = false;}
      if(CRZmKwEsAT == true){CRZmKwEsAT = false;}
      if(QfRRSDiDrF == true){QfRRSDiDrF = false;}
      if(IYmEeLgGzQ == true){IYmEeLgGzQ = false;}
      if(GNLdVCzqiK == true){GNLdVCzqiK = false;}
      if(sMDucsGTqF == true){sMDucsGTqF = false;}
      if(AoBOTdeUIy == true){AoBOTdeUIy = false;}
      if(PysjNCTnwP == true){PysjNCTnwP = false;}
      if(EqUgLuVqbk == true){EqUgLuVqbk = false;}
      if(FNOtPRMwJq == true){FNOtPRMwJq = false;}
      if(XdikuuTShZ == true){XdikuuTShZ = false;}
      if(YRWaBJTTDX == true){YRWaBJTTDX = false;}
      if(HnsWrBizUw == true){HnsWrBizUw = false;}
      if(pXdErZHjlQ == true){pXdErZHjlQ = false;}
      if(aCIBMmpmrG == true){aCIBMmpmrG = false;}
      if(xssljikLrs == true){xssljikLrs = false;}
      if(LUyljBnRia == true){LUyljBnRia = false;}
      if(BigmwFeqKE == true){BigmwFeqKE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRAACTLGTS
{ 
  void SmDeJYDszy()
  { 
      bool wSMPJUFMNi = false;
      bool oytPzpYgRb = false;
      bool VIShlYCtEC = false;
      bool fwmsCoKVBB = false;
      bool zyLLuBRpfz = false;
      bool uWxKsnzdck = false;
      bool SKHKCrLBMK = false;
      bool fCeQbWwHmj = false;
      bool HLNFHJzczO = false;
      bool pfsQioqAIC = false;
      bool pPcVTrrfhW = false;
      bool qrqrdGwCCs = false;
      bool riCyTzJNhm = false;
      bool fwyjtqhrkP = false;
      bool QStcWxoAmb = false;
      bool rnyPJHMeCT = false;
      bool hdytputGyl = false;
      bool XEQlcZnZbW = false;
      bool KJaFuqxiam = false;
      bool dDpQglUzla = false;
      string RFmiqRsdlS;
      string gjbZEwcSeu;
      string fsSuapoEdU;
      string jCdsVGAqPZ;
      string swVVfXAOps;
      string BEFnDXmrHB;
      string coAQhdGiEx;
      string wlDFBiXwPD;
      string paNkSfxpox;
      string TIiOxDwEmB;
      string RRKswPAAlU;
      string ApbELBbPxC;
      string gPsGdnCoHx;
      string lSJOkXQUnD;
      string ewDUxdfeCu;
      string bgHjTBXDOH;
      string NLrnhggNSm;
      string kHatWjMYIz;
      string HWlLVFLYtj;
      string AMFfoTDPlP;
      if(RFmiqRsdlS == RRKswPAAlU){wSMPJUFMNi = true;}
      else if(RRKswPAAlU == RFmiqRsdlS){pPcVTrrfhW = true;}
      if(gjbZEwcSeu == ApbELBbPxC){oytPzpYgRb = true;}
      else if(ApbELBbPxC == gjbZEwcSeu){qrqrdGwCCs = true;}
      if(fsSuapoEdU == gPsGdnCoHx){VIShlYCtEC = true;}
      else if(gPsGdnCoHx == fsSuapoEdU){riCyTzJNhm = true;}
      if(jCdsVGAqPZ == lSJOkXQUnD){fwmsCoKVBB = true;}
      else if(lSJOkXQUnD == jCdsVGAqPZ){fwyjtqhrkP = true;}
      if(swVVfXAOps == ewDUxdfeCu){zyLLuBRpfz = true;}
      else if(ewDUxdfeCu == swVVfXAOps){QStcWxoAmb = true;}
      if(BEFnDXmrHB == bgHjTBXDOH){uWxKsnzdck = true;}
      else if(bgHjTBXDOH == BEFnDXmrHB){rnyPJHMeCT = true;}
      if(coAQhdGiEx == NLrnhggNSm){SKHKCrLBMK = true;}
      else if(NLrnhggNSm == coAQhdGiEx){hdytputGyl = true;}
      if(wlDFBiXwPD == kHatWjMYIz){fCeQbWwHmj = true;}
      if(paNkSfxpox == HWlLVFLYtj){HLNFHJzczO = true;}
      if(TIiOxDwEmB == AMFfoTDPlP){pfsQioqAIC = true;}
      while(kHatWjMYIz == wlDFBiXwPD){XEQlcZnZbW = true;}
      while(HWlLVFLYtj == HWlLVFLYtj){KJaFuqxiam = true;}
      while(AMFfoTDPlP == AMFfoTDPlP){dDpQglUzla = true;}
      if(wSMPJUFMNi == true){wSMPJUFMNi = false;}
      if(oytPzpYgRb == true){oytPzpYgRb = false;}
      if(VIShlYCtEC == true){VIShlYCtEC = false;}
      if(fwmsCoKVBB == true){fwmsCoKVBB = false;}
      if(zyLLuBRpfz == true){zyLLuBRpfz = false;}
      if(uWxKsnzdck == true){uWxKsnzdck = false;}
      if(SKHKCrLBMK == true){SKHKCrLBMK = false;}
      if(fCeQbWwHmj == true){fCeQbWwHmj = false;}
      if(HLNFHJzczO == true){HLNFHJzczO = false;}
      if(pfsQioqAIC == true){pfsQioqAIC = false;}
      if(pPcVTrrfhW == true){pPcVTrrfhW = false;}
      if(qrqrdGwCCs == true){qrqrdGwCCs = false;}
      if(riCyTzJNhm == true){riCyTzJNhm = false;}
      if(fwyjtqhrkP == true){fwyjtqhrkP = false;}
      if(QStcWxoAmb == true){QStcWxoAmb = false;}
      if(rnyPJHMeCT == true){rnyPJHMeCT = false;}
      if(hdytputGyl == true){hdytputGyl = false;}
      if(XEQlcZnZbW == true){XEQlcZnZbW = false;}
      if(KJaFuqxiam == true){KJaFuqxiam = false;}
      if(dDpQglUzla == true){dDpQglUzla = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULNITYLIYN
{ 
  void iZPqirBxmA()
  { 
      bool YLRSzpIJRU = false;
      bool fqQTWIKNZT = false;
      bool xrgtsNXIEI = false;
      bool ZIBpkodkfl = false;
      bool YIANLPemVq = false;
      bool aWhOxgdXYl = false;
      bool RAEJuWpahh = false;
      bool dYhmtnrThd = false;
      bool hkmNgDZlsE = false;
      bool KGLsTYEpSo = false;
      bool YEEmMCnuTI = false;
      bool oKouDgNqbr = false;
      bool wDgcXXMnSV = false;
      bool jBAsFdfzBe = false;
      bool OeSjPzRQpm = false;
      bool LNOarUWbOo = false;
      bool ozbxXmKupY = false;
      bool ANoxcRkxMX = false;
      bool FwyeKWlZAj = false;
      bool HEjMpOCULb = false;
      string EEaScIWrVa;
      string ElmUWKEkbp;
      string hAaJbSDzGA;
      string tBxqNDYWMV;
      string HNtnYNpFqm;
      string nJnjNEcQpK;
      string FXkVfDowGT;
      string khXFiTFmkN;
      string bxISLkNMcJ;
      string ZIgBQjcYHV;
      string YtzXBGkhBs;
      string ypfbhHOSJt;
      string pbSxtcBWny;
      string qgeOohyjQE;
      string AeLjLibESJ;
      string UJOMfwaCdX;
      string FOsCBQKQmA;
      string JeBEtKQikK;
      string AwDechSSir;
      string GuGszlkIhu;
      if(EEaScIWrVa == YtzXBGkhBs){YLRSzpIJRU = true;}
      else if(YtzXBGkhBs == EEaScIWrVa){YEEmMCnuTI = true;}
      if(ElmUWKEkbp == ypfbhHOSJt){fqQTWIKNZT = true;}
      else if(ypfbhHOSJt == ElmUWKEkbp){oKouDgNqbr = true;}
      if(hAaJbSDzGA == pbSxtcBWny){xrgtsNXIEI = true;}
      else if(pbSxtcBWny == hAaJbSDzGA){wDgcXXMnSV = true;}
      if(tBxqNDYWMV == qgeOohyjQE){ZIBpkodkfl = true;}
      else if(qgeOohyjQE == tBxqNDYWMV){jBAsFdfzBe = true;}
      if(HNtnYNpFqm == AeLjLibESJ){YIANLPemVq = true;}
      else if(AeLjLibESJ == HNtnYNpFqm){OeSjPzRQpm = true;}
      if(nJnjNEcQpK == UJOMfwaCdX){aWhOxgdXYl = true;}
      else if(UJOMfwaCdX == nJnjNEcQpK){LNOarUWbOo = true;}
      if(FXkVfDowGT == FOsCBQKQmA){RAEJuWpahh = true;}
      else if(FOsCBQKQmA == FXkVfDowGT){ozbxXmKupY = true;}
      if(khXFiTFmkN == JeBEtKQikK){dYhmtnrThd = true;}
      if(bxISLkNMcJ == AwDechSSir){hkmNgDZlsE = true;}
      if(ZIgBQjcYHV == GuGszlkIhu){KGLsTYEpSo = true;}
      while(JeBEtKQikK == khXFiTFmkN){ANoxcRkxMX = true;}
      while(AwDechSSir == AwDechSSir){FwyeKWlZAj = true;}
      while(GuGszlkIhu == GuGszlkIhu){HEjMpOCULb = true;}
      if(YLRSzpIJRU == true){YLRSzpIJRU = false;}
      if(fqQTWIKNZT == true){fqQTWIKNZT = false;}
      if(xrgtsNXIEI == true){xrgtsNXIEI = false;}
      if(ZIBpkodkfl == true){ZIBpkodkfl = false;}
      if(YIANLPemVq == true){YIANLPemVq = false;}
      if(aWhOxgdXYl == true){aWhOxgdXYl = false;}
      if(RAEJuWpahh == true){RAEJuWpahh = false;}
      if(dYhmtnrThd == true){dYhmtnrThd = false;}
      if(hkmNgDZlsE == true){hkmNgDZlsE = false;}
      if(KGLsTYEpSo == true){KGLsTYEpSo = false;}
      if(YEEmMCnuTI == true){YEEmMCnuTI = false;}
      if(oKouDgNqbr == true){oKouDgNqbr = false;}
      if(wDgcXXMnSV == true){wDgcXXMnSV = false;}
      if(jBAsFdfzBe == true){jBAsFdfzBe = false;}
      if(OeSjPzRQpm == true){OeSjPzRQpm = false;}
      if(LNOarUWbOo == true){LNOarUWbOo = false;}
      if(ozbxXmKupY == true){ozbxXmKupY = false;}
      if(ANoxcRkxMX == true){ANoxcRkxMX = false;}
      if(FwyeKWlZAj == true){FwyeKWlZAj = false;}
      if(HEjMpOCULb == true){HEjMpOCULb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPOTHMKVZM
{ 
  void KlNQkcjPTV()
  { 
      bool WurgsdBNUm = false;
      bool rWgOKehCuC = false;
      bool hbcJmkzdZK = false;
      bool XcEihoZxZZ = false;
      bool tymRJeRzPK = false;
      bool IFZjSuRisH = false;
      bool eXnJOORxfU = false;
      bool FjcVHjnLAI = false;
      bool SzOOCSDUPm = false;
      bool XqDRtWKcCu = false;
      bool MUTtFXcDci = false;
      bool GGikofJZHw = false;
      bool LxhsxOgKak = false;
      bool YLIEuyfTId = false;
      bool ozrggRIScO = false;
      bool NkVGjPmZwq = false;
      bool qRcqKuxdop = false;
      bool AoQdGLFAMf = false;
      bool GNhMXnoCUf = false;
      bool LFWQlXWAWl = false;
      string UTlAkntkVW;
      string tjmwYhtTXp;
      string QPzguUXghJ;
      string DoAVkpmNqu;
      string EistgtKJPD;
      string AntiiFTEFP;
      string QNDMSEjRLi;
      string ufbblgVFzB;
      string JOQdIOuQme;
      string VhIbepegab;
      string JsxgIUMRwB;
      string iOFDFBxZDE;
      string JSdfMNWAww;
      string CoeWrQQiUn;
      string CcUluHcEVd;
      string rFcWSpORUu;
      string xLUzytjhLo;
      string jNEPBfyrjF;
      string jSdSEwLHEB;
      string BzOZppHUmB;
      if(UTlAkntkVW == JsxgIUMRwB){WurgsdBNUm = true;}
      else if(JsxgIUMRwB == UTlAkntkVW){MUTtFXcDci = true;}
      if(tjmwYhtTXp == iOFDFBxZDE){rWgOKehCuC = true;}
      else if(iOFDFBxZDE == tjmwYhtTXp){GGikofJZHw = true;}
      if(QPzguUXghJ == JSdfMNWAww){hbcJmkzdZK = true;}
      else if(JSdfMNWAww == QPzguUXghJ){LxhsxOgKak = true;}
      if(DoAVkpmNqu == CoeWrQQiUn){XcEihoZxZZ = true;}
      else if(CoeWrQQiUn == DoAVkpmNqu){YLIEuyfTId = true;}
      if(EistgtKJPD == CcUluHcEVd){tymRJeRzPK = true;}
      else if(CcUluHcEVd == EistgtKJPD){ozrggRIScO = true;}
      if(AntiiFTEFP == rFcWSpORUu){IFZjSuRisH = true;}
      else if(rFcWSpORUu == AntiiFTEFP){NkVGjPmZwq = true;}
      if(QNDMSEjRLi == xLUzytjhLo){eXnJOORxfU = true;}
      else if(xLUzytjhLo == QNDMSEjRLi){qRcqKuxdop = true;}
      if(ufbblgVFzB == jNEPBfyrjF){FjcVHjnLAI = true;}
      if(JOQdIOuQme == jSdSEwLHEB){SzOOCSDUPm = true;}
      if(VhIbepegab == BzOZppHUmB){XqDRtWKcCu = true;}
      while(jNEPBfyrjF == ufbblgVFzB){AoQdGLFAMf = true;}
      while(jSdSEwLHEB == jSdSEwLHEB){GNhMXnoCUf = true;}
      while(BzOZppHUmB == BzOZppHUmB){LFWQlXWAWl = true;}
      if(WurgsdBNUm == true){WurgsdBNUm = false;}
      if(rWgOKehCuC == true){rWgOKehCuC = false;}
      if(hbcJmkzdZK == true){hbcJmkzdZK = false;}
      if(XcEihoZxZZ == true){XcEihoZxZZ = false;}
      if(tymRJeRzPK == true){tymRJeRzPK = false;}
      if(IFZjSuRisH == true){IFZjSuRisH = false;}
      if(eXnJOORxfU == true){eXnJOORxfU = false;}
      if(FjcVHjnLAI == true){FjcVHjnLAI = false;}
      if(SzOOCSDUPm == true){SzOOCSDUPm = false;}
      if(XqDRtWKcCu == true){XqDRtWKcCu = false;}
      if(MUTtFXcDci == true){MUTtFXcDci = false;}
      if(GGikofJZHw == true){GGikofJZHw = false;}
      if(LxhsxOgKak == true){LxhsxOgKak = false;}
      if(YLIEuyfTId == true){YLIEuyfTId = false;}
      if(ozrggRIScO == true){ozrggRIScO = false;}
      if(NkVGjPmZwq == true){NkVGjPmZwq = false;}
      if(qRcqKuxdop == true){qRcqKuxdop = false;}
      if(AoQdGLFAMf == true){AoQdGLFAMf = false;}
      if(GNhMXnoCUf == true){GNhMXnoCUf = false;}
      if(LFWQlXWAWl == true){LFWQlXWAWl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYFYHAUMWG
{ 
  void kBuXdrRlyp()
  { 
      bool hLKeQQrmGe = false;
      bool UWrpoApkdD = false;
      bool TPqWsQXSZb = false;
      bool RAzMEbHBoE = false;
      bool dKuBIVEqRa = false;
      bool bepjnRTmkA = false;
      bool sZMdMTXflN = false;
      bool snwZZJTpOW = false;
      bool LgAzAlKOXm = false;
      bool HTPnKDxRnn = false;
      bool yYEEgmiQKe = false;
      bool xdYOoLYNcZ = false;
      bool JIHzFYXIOV = false;
      bool LCBaYmbuSN = false;
      bool DsDsocuBzy = false;
      bool djnOdpQFzH = false;
      bool OaCoSucypB = false;
      bool jduPVPEOKb = false;
      bool dWIPqbNmwi = false;
      bool WWuKycqOas = false;
      string XXCnPosyZf;
      string mhofnjyYlL;
      string suOlYHyADo;
      string mHiLHePrQw;
      string fZVblbqfZT;
      string AcUXhcIQOH;
      string qrukrezdYI;
      string UFHpfTYmAw;
      string QRajnJmKcd;
      string VycIEmdkiG;
      string cMHQytVdqO;
      string EVQSqYQLwi;
      string rnBtmVbylr;
      string omDsSEKKkt;
      string nISNZAhKRf;
      string WSoANoKMcc;
      string SWrzZRSWAm;
      string OFZBtiUmUl;
      string mRgGVVxCfc;
      string sxhHbRQTnH;
      if(XXCnPosyZf == cMHQytVdqO){hLKeQQrmGe = true;}
      else if(cMHQytVdqO == XXCnPosyZf){yYEEgmiQKe = true;}
      if(mhofnjyYlL == EVQSqYQLwi){UWrpoApkdD = true;}
      else if(EVQSqYQLwi == mhofnjyYlL){xdYOoLYNcZ = true;}
      if(suOlYHyADo == rnBtmVbylr){TPqWsQXSZb = true;}
      else if(rnBtmVbylr == suOlYHyADo){JIHzFYXIOV = true;}
      if(mHiLHePrQw == omDsSEKKkt){RAzMEbHBoE = true;}
      else if(omDsSEKKkt == mHiLHePrQw){LCBaYmbuSN = true;}
      if(fZVblbqfZT == nISNZAhKRf){dKuBIVEqRa = true;}
      else if(nISNZAhKRf == fZVblbqfZT){DsDsocuBzy = true;}
      if(AcUXhcIQOH == WSoANoKMcc){bepjnRTmkA = true;}
      else if(WSoANoKMcc == AcUXhcIQOH){djnOdpQFzH = true;}
      if(qrukrezdYI == SWrzZRSWAm){sZMdMTXflN = true;}
      else if(SWrzZRSWAm == qrukrezdYI){OaCoSucypB = true;}
      if(UFHpfTYmAw == OFZBtiUmUl){snwZZJTpOW = true;}
      if(QRajnJmKcd == mRgGVVxCfc){LgAzAlKOXm = true;}
      if(VycIEmdkiG == sxhHbRQTnH){HTPnKDxRnn = true;}
      while(OFZBtiUmUl == UFHpfTYmAw){jduPVPEOKb = true;}
      while(mRgGVVxCfc == mRgGVVxCfc){dWIPqbNmwi = true;}
      while(sxhHbRQTnH == sxhHbRQTnH){WWuKycqOas = true;}
      if(hLKeQQrmGe == true){hLKeQQrmGe = false;}
      if(UWrpoApkdD == true){UWrpoApkdD = false;}
      if(TPqWsQXSZb == true){TPqWsQXSZb = false;}
      if(RAzMEbHBoE == true){RAzMEbHBoE = false;}
      if(dKuBIVEqRa == true){dKuBIVEqRa = false;}
      if(bepjnRTmkA == true){bepjnRTmkA = false;}
      if(sZMdMTXflN == true){sZMdMTXflN = false;}
      if(snwZZJTpOW == true){snwZZJTpOW = false;}
      if(LgAzAlKOXm == true){LgAzAlKOXm = false;}
      if(HTPnKDxRnn == true){HTPnKDxRnn = false;}
      if(yYEEgmiQKe == true){yYEEgmiQKe = false;}
      if(xdYOoLYNcZ == true){xdYOoLYNcZ = false;}
      if(JIHzFYXIOV == true){JIHzFYXIOV = false;}
      if(LCBaYmbuSN == true){LCBaYmbuSN = false;}
      if(DsDsocuBzy == true){DsDsocuBzy = false;}
      if(djnOdpQFzH == true){djnOdpQFzH = false;}
      if(OaCoSucypB == true){OaCoSucypB = false;}
      if(jduPVPEOKb == true){jduPVPEOKb = false;}
      if(dWIPqbNmwi == true){dWIPqbNmwi = false;}
      if(WWuKycqOas == true){WWuKycqOas = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYXFGLZRSC
{ 
  void Wgirixntdg()
  { 
      bool KBiNomNPbV = false;
      bool ccikOZOBYz = false;
      bool HMlKpsaBXd = false;
      bool GecWpDKWMs = false;
      bool HeBhrIneRW = false;
      bool MCDppyOXXw = false;
      bool LLqyPyzMuL = false;
      bool PqoeqcLERh = false;
      bool EujAQDamfr = false;
      bool omzPgwnCSt = false;
      bool IajGHVNYyN = false;
      bool lKGoqQapgL = false;
      bool WMfDVcqYxt = false;
      bool oIkWZcLcsu = false;
      bool oCnRFdfKXQ = false;
      bool UxVGXuufje = false;
      bool dnaDYcYiPN = false;
      bool EyxlVTXOxq = false;
      bool wgAgZqmezd = false;
      bool hesNQBbjsc = false;
      string AswdUbcHUn;
      string ZsCbfHoqwz;
      string eNUeEEhnFk;
      string EkCdWamcQq;
      string OhIwpTxftl;
      string pCQChmYRYQ;
      string snCiinqYFE;
      string TMaFkwEXnk;
      string GCsSuCUzui;
      string CVDzxZeYNB;
      string cYaoRcaLQk;
      string hAcnJquinf;
      string TqcVCxIaHL;
      string QfKlHhaDBR;
      string aIiJBBrOpF;
      string eukghlwEmT;
      string TzDFUCpqfb;
      string PqhVFLISUB;
      string FskCgUtcEV;
      string kWQgxaEcoy;
      if(AswdUbcHUn == cYaoRcaLQk){KBiNomNPbV = true;}
      else if(cYaoRcaLQk == AswdUbcHUn){IajGHVNYyN = true;}
      if(ZsCbfHoqwz == hAcnJquinf){ccikOZOBYz = true;}
      else if(hAcnJquinf == ZsCbfHoqwz){lKGoqQapgL = true;}
      if(eNUeEEhnFk == TqcVCxIaHL){HMlKpsaBXd = true;}
      else if(TqcVCxIaHL == eNUeEEhnFk){WMfDVcqYxt = true;}
      if(EkCdWamcQq == QfKlHhaDBR){GecWpDKWMs = true;}
      else if(QfKlHhaDBR == EkCdWamcQq){oIkWZcLcsu = true;}
      if(OhIwpTxftl == aIiJBBrOpF){HeBhrIneRW = true;}
      else if(aIiJBBrOpF == OhIwpTxftl){oCnRFdfKXQ = true;}
      if(pCQChmYRYQ == eukghlwEmT){MCDppyOXXw = true;}
      else if(eukghlwEmT == pCQChmYRYQ){UxVGXuufje = true;}
      if(snCiinqYFE == TzDFUCpqfb){LLqyPyzMuL = true;}
      else if(TzDFUCpqfb == snCiinqYFE){dnaDYcYiPN = true;}
      if(TMaFkwEXnk == PqhVFLISUB){PqoeqcLERh = true;}
      if(GCsSuCUzui == FskCgUtcEV){EujAQDamfr = true;}
      if(CVDzxZeYNB == kWQgxaEcoy){omzPgwnCSt = true;}
      while(PqhVFLISUB == TMaFkwEXnk){EyxlVTXOxq = true;}
      while(FskCgUtcEV == FskCgUtcEV){wgAgZqmezd = true;}
      while(kWQgxaEcoy == kWQgxaEcoy){hesNQBbjsc = true;}
      if(KBiNomNPbV == true){KBiNomNPbV = false;}
      if(ccikOZOBYz == true){ccikOZOBYz = false;}
      if(HMlKpsaBXd == true){HMlKpsaBXd = false;}
      if(GecWpDKWMs == true){GecWpDKWMs = false;}
      if(HeBhrIneRW == true){HeBhrIneRW = false;}
      if(MCDppyOXXw == true){MCDppyOXXw = false;}
      if(LLqyPyzMuL == true){LLqyPyzMuL = false;}
      if(PqoeqcLERh == true){PqoeqcLERh = false;}
      if(EujAQDamfr == true){EujAQDamfr = false;}
      if(omzPgwnCSt == true){omzPgwnCSt = false;}
      if(IajGHVNYyN == true){IajGHVNYyN = false;}
      if(lKGoqQapgL == true){lKGoqQapgL = false;}
      if(WMfDVcqYxt == true){WMfDVcqYxt = false;}
      if(oIkWZcLcsu == true){oIkWZcLcsu = false;}
      if(oCnRFdfKXQ == true){oCnRFdfKXQ = false;}
      if(UxVGXuufje == true){UxVGXuufje = false;}
      if(dnaDYcYiPN == true){dnaDYcYiPN = false;}
      if(EyxlVTXOxq == true){EyxlVTXOxq = false;}
      if(wgAgZqmezd == true){wgAgZqmezd = false;}
      if(hesNQBbjsc == true){hesNQBbjsc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCQYXNIQLU
{ 
  void YqbTRzPgwG()
  { 
      bool nyVlgiVfJB = false;
      bool yZJqEyHAgG = false;
      bool aFhlSJQxQy = false;
      bool kduFWwpZOA = false;
      bool OegyQFIfeg = false;
      bool lSIFdiPiSW = false;
      bool RYOKPUeDUH = false;
      bool HhlgqwXiVN = false;
      bool BkSjLRUoan = false;
      bool fHGqhpPViw = false;
      bool aELWYDgbNh = false;
      bool KgNFVfFdyx = false;
      bool zocfaAbtyB = false;
      bool fCAYlwZuLI = false;
      bool jrardztAVB = false;
      bool jkWkwlbeuY = false;
      bool amdMCHfnSZ = false;
      bool GJSpNGNjCb = false;
      bool GbXwQueOcA = false;
      bool UuAlgwOOpV = false;
      string GuZYYNVJkf;
      string cqRGkwEQNM;
      string sgCAQCskkR;
      string rppToRxOUo;
      string UofyPrslPa;
      string iMYNjZsZHW;
      string TjYSmmBxQS;
      string zpuYqEADjY;
      string JGVJhfQbjP;
      string YWGyUkQMKc;
      string quUwbsQAVf;
      string YopiMMNOkH;
      string VYMBtbixDG;
      string mmsHgNlYhn;
      string OQFEqigXkH;
      string XCbCGRhTCz;
      string JTwPrkuiBy;
      string anfwsFTIKK;
      string uLLuikKpAO;
      string fRWietTpMF;
      if(GuZYYNVJkf == quUwbsQAVf){nyVlgiVfJB = true;}
      else if(quUwbsQAVf == GuZYYNVJkf){aELWYDgbNh = true;}
      if(cqRGkwEQNM == YopiMMNOkH){yZJqEyHAgG = true;}
      else if(YopiMMNOkH == cqRGkwEQNM){KgNFVfFdyx = true;}
      if(sgCAQCskkR == VYMBtbixDG){aFhlSJQxQy = true;}
      else if(VYMBtbixDG == sgCAQCskkR){zocfaAbtyB = true;}
      if(rppToRxOUo == mmsHgNlYhn){kduFWwpZOA = true;}
      else if(mmsHgNlYhn == rppToRxOUo){fCAYlwZuLI = true;}
      if(UofyPrslPa == OQFEqigXkH){OegyQFIfeg = true;}
      else if(OQFEqigXkH == UofyPrslPa){jrardztAVB = true;}
      if(iMYNjZsZHW == XCbCGRhTCz){lSIFdiPiSW = true;}
      else if(XCbCGRhTCz == iMYNjZsZHW){jkWkwlbeuY = true;}
      if(TjYSmmBxQS == JTwPrkuiBy){RYOKPUeDUH = true;}
      else if(JTwPrkuiBy == TjYSmmBxQS){amdMCHfnSZ = true;}
      if(zpuYqEADjY == anfwsFTIKK){HhlgqwXiVN = true;}
      if(JGVJhfQbjP == uLLuikKpAO){BkSjLRUoan = true;}
      if(YWGyUkQMKc == fRWietTpMF){fHGqhpPViw = true;}
      while(anfwsFTIKK == zpuYqEADjY){GJSpNGNjCb = true;}
      while(uLLuikKpAO == uLLuikKpAO){GbXwQueOcA = true;}
      while(fRWietTpMF == fRWietTpMF){UuAlgwOOpV = true;}
      if(nyVlgiVfJB == true){nyVlgiVfJB = false;}
      if(yZJqEyHAgG == true){yZJqEyHAgG = false;}
      if(aFhlSJQxQy == true){aFhlSJQxQy = false;}
      if(kduFWwpZOA == true){kduFWwpZOA = false;}
      if(OegyQFIfeg == true){OegyQFIfeg = false;}
      if(lSIFdiPiSW == true){lSIFdiPiSW = false;}
      if(RYOKPUeDUH == true){RYOKPUeDUH = false;}
      if(HhlgqwXiVN == true){HhlgqwXiVN = false;}
      if(BkSjLRUoan == true){BkSjLRUoan = false;}
      if(fHGqhpPViw == true){fHGqhpPViw = false;}
      if(aELWYDgbNh == true){aELWYDgbNh = false;}
      if(KgNFVfFdyx == true){KgNFVfFdyx = false;}
      if(zocfaAbtyB == true){zocfaAbtyB = false;}
      if(fCAYlwZuLI == true){fCAYlwZuLI = false;}
      if(jrardztAVB == true){jrardztAVB = false;}
      if(jkWkwlbeuY == true){jkWkwlbeuY = false;}
      if(amdMCHfnSZ == true){amdMCHfnSZ = false;}
      if(GJSpNGNjCb == true){GJSpNGNjCb = false;}
      if(GbXwQueOcA == true){GbXwQueOcA = false;}
      if(UuAlgwOOpV == true){UuAlgwOOpV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSWDRMVAUW
{ 
  void RrZwQVqMay()
  { 
      bool EmBBXSldpo = false;
      bool TUVUyBpSEV = false;
      bool ClTAgjdesl = false;
      bool NdXIaCBujP = false;
      bool iILKawHYsx = false;
      bool NPiYzSTBTm = false;
      bool nGkDbpwMsu = false;
      bool AuinlsaIZj = false;
      bool bFkuXxtzJI = false;
      bool izawabXHhj = false;
      bool AteyxSgtmF = false;
      bool qLbiLiVofe = false;
      bool uxCkMBTmMJ = false;
      bool USZojhZmyF = false;
      bool QzLDQWWqkr = false;
      bool GhbDnDqsku = false;
      bool yshdkYlmzc = false;
      bool IhqZOukzTo = false;
      bool dbCUClqVAg = false;
      bool pfBCGWRhSr = false;
      string pbjsFcYquP;
      string YDaNTLeHTd;
      string WKMAKDPkTm;
      string JrcPWeyGGU;
      string whdSWCEYPA;
      string cjRrJfPjiC;
      string NnWIFfaLqn;
      string MXAzgoftcH;
      string yqVTJZajGp;
      string OOXEHIKVMp;
      string bsgamEiRKU;
      string zVGaEWSCyf;
      string EpFAZyzwrX;
      string dKglfFJtfE;
      string pIZlpsHwAj;
      string pIWflknfBo;
      string ElZlqonTuy;
      string MXVspwQSKf;
      string pDwHhVmBAt;
      string RcsqzDimtB;
      if(pbjsFcYquP == bsgamEiRKU){EmBBXSldpo = true;}
      else if(bsgamEiRKU == pbjsFcYquP){AteyxSgtmF = true;}
      if(YDaNTLeHTd == zVGaEWSCyf){TUVUyBpSEV = true;}
      else if(zVGaEWSCyf == YDaNTLeHTd){qLbiLiVofe = true;}
      if(WKMAKDPkTm == EpFAZyzwrX){ClTAgjdesl = true;}
      else if(EpFAZyzwrX == WKMAKDPkTm){uxCkMBTmMJ = true;}
      if(JrcPWeyGGU == dKglfFJtfE){NdXIaCBujP = true;}
      else if(dKglfFJtfE == JrcPWeyGGU){USZojhZmyF = true;}
      if(whdSWCEYPA == pIZlpsHwAj){iILKawHYsx = true;}
      else if(pIZlpsHwAj == whdSWCEYPA){QzLDQWWqkr = true;}
      if(cjRrJfPjiC == pIWflknfBo){NPiYzSTBTm = true;}
      else if(pIWflknfBo == cjRrJfPjiC){GhbDnDqsku = true;}
      if(NnWIFfaLqn == ElZlqonTuy){nGkDbpwMsu = true;}
      else if(ElZlqonTuy == NnWIFfaLqn){yshdkYlmzc = true;}
      if(MXAzgoftcH == MXVspwQSKf){AuinlsaIZj = true;}
      if(yqVTJZajGp == pDwHhVmBAt){bFkuXxtzJI = true;}
      if(OOXEHIKVMp == RcsqzDimtB){izawabXHhj = true;}
      while(MXVspwQSKf == MXAzgoftcH){IhqZOukzTo = true;}
      while(pDwHhVmBAt == pDwHhVmBAt){dbCUClqVAg = true;}
      while(RcsqzDimtB == RcsqzDimtB){pfBCGWRhSr = true;}
      if(EmBBXSldpo == true){EmBBXSldpo = false;}
      if(TUVUyBpSEV == true){TUVUyBpSEV = false;}
      if(ClTAgjdesl == true){ClTAgjdesl = false;}
      if(NdXIaCBujP == true){NdXIaCBujP = false;}
      if(iILKawHYsx == true){iILKawHYsx = false;}
      if(NPiYzSTBTm == true){NPiYzSTBTm = false;}
      if(nGkDbpwMsu == true){nGkDbpwMsu = false;}
      if(AuinlsaIZj == true){AuinlsaIZj = false;}
      if(bFkuXxtzJI == true){bFkuXxtzJI = false;}
      if(izawabXHhj == true){izawabXHhj = false;}
      if(AteyxSgtmF == true){AteyxSgtmF = false;}
      if(qLbiLiVofe == true){qLbiLiVofe = false;}
      if(uxCkMBTmMJ == true){uxCkMBTmMJ = false;}
      if(USZojhZmyF == true){USZojhZmyF = false;}
      if(QzLDQWWqkr == true){QzLDQWWqkr = false;}
      if(GhbDnDqsku == true){GhbDnDqsku = false;}
      if(yshdkYlmzc == true){yshdkYlmzc = false;}
      if(IhqZOukzTo == true){IhqZOukzTo = false;}
      if(dbCUClqVAg == true){dbCUClqVAg = false;}
      if(pfBCGWRhSr == true){pfBCGWRhSr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAFPVFXOGW
{ 
  void YITutHKFcJ()
  { 
      bool CugEnwQeQg = false;
      bool ZuMcSGJqpt = false;
      bool xbdCrSQutb = false;
      bool qLPfobjPoq = false;
      bool bBwqdThkWB = false;
      bool TxTDsaReLV = false;
      bool fUjooNffmp = false;
      bool WtCyRwelYX = false;
      bool jeYrHtqLmO = false;
      bool JFDSLHQHCP = false;
      bool nCxfeZuVlw = false;
      bool ufGnkAurgt = false;
      bool WTrYgRqimK = false;
      bool fXiIjhgsNh = false;
      bool zVZqTdzPhK = false;
      bool LYaHsTJYyM = false;
      bool iLhbQWwxEC = false;
      bool SCdyuAtBFD = false;
      bool SaBbyGxaPP = false;
      bool YItAzmmxaw = false;
      string TQiUYlwQgV;
      string yghnFZEbYB;
      string juaDIKlsJl;
      string tslNjFRFFw;
      string tXNJLBcfES;
      string beeCtXpfMN;
      string ADGuaFuTDz;
      string HyWcGLgRrG;
      string hGnpKONjTL;
      string PlsqwpRShF;
      string GJbELcICuh;
      string qXnFfsOPkL;
      string rKAqjVEegQ;
      string tNilzXeieg;
      string GKolUqxmLC;
      string bBhVNuJjUp;
      string XcVemdoCGH;
      string NekDFgVNWr;
      string XQTdnsfMXD;
      string OuOoIcoKyp;
      if(TQiUYlwQgV == GJbELcICuh){CugEnwQeQg = true;}
      else if(GJbELcICuh == TQiUYlwQgV){nCxfeZuVlw = true;}
      if(yghnFZEbYB == qXnFfsOPkL){ZuMcSGJqpt = true;}
      else if(qXnFfsOPkL == yghnFZEbYB){ufGnkAurgt = true;}
      if(juaDIKlsJl == rKAqjVEegQ){xbdCrSQutb = true;}
      else if(rKAqjVEegQ == juaDIKlsJl){WTrYgRqimK = true;}
      if(tslNjFRFFw == tNilzXeieg){qLPfobjPoq = true;}
      else if(tNilzXeieg == tslNjFRFFw){fXiIjhgsNh = true;}
      if(tXNJLBcfES == GKolUqxmLC){bBwqdThkWB = true;}
      else if(GKolUqxmLC == tXNJLBcfES){zVZqTdzPhK = true;}
      if(beeCtXpfMN == bBhVNuJjUp){TxTDsaReLV = true;}
      else if(bBhVNuJjUp == beeCtXpfMN){LYaHsTJYyM = true;}
      if(ADGuaFuTDz == XcVemdoCGH){fUjooNffmp = true;}
      else if(XcVemdoCGH == ADGuaFuTDz){iLhbQWwxEC = true;}
      if(HyWcGLgRrG == NekDFgVNWr){WtCyRwelYX = true;}
      if(hGnpKONjTL == XQTdnsfMXD){jeYrHtqLmO = true;}
      if(PlsqwpRShF == OuOoIcoKyp){JFDSLHQHCP = true;}
      while(NekDFgVNWr == HyWcGLgRrG){SCdyuAtBFD = true;}
      while(XQTdnsfMXD == XQTdnsfMXD){SaBbyGxaPP = true;}
      while(OuOoIcoKyp == OuOoIcoKyp){YItAzmmxaw = true;}
      if(CugEnwQeQg == true){CugEnwQeQg = false;}
      if(ZuMcSGJqpt == true){ZuMcSGJqpt = false;}
      if(xbdCrSQutb == true){xbdCrSQutb = false;}
      if(qLPfobjPoq == true){qLPfobjPoq = false;}
      if(bBwqdThkWB == true){bBwqdThkWB = false;}
      if(TxTDsaReLV == true){TxTDsaReLV = false;}
      if(fUjooNffmp == true){fUjooNffmp = false;}
      if(WtCyRwelYX == true){WtCyRwelYX = false;}
      if(jeYrHtqLmO == true){jeYrHtqLmO = false;}
      if(JFDSLHQHCP == true){JFDSLHQHCP = false;}
      if(nCxfeZuVlw == true){nCxfeZuVlw = false;}
      if(ufGnkAurgt == true){ufGnkAurgt = false;}
      if(WTrYgRqimK == true){WTrYgRqimK = false;}
      if(fXiIjhgsNh == true){fXiIjhgsNh = false;}
      if(zVZqTdzPhK == true){zVZqTdzPhK = false;}
      if(LYaHsTJYyM == true){LYaHsTJYyM = false;}
      if(iLhbQWwxEC == true){iLhbQWwxEC = false;}
      if(SCdyuAtBFD == true){SCdyuAtBFD = false;}
      if(SaBbyGxaPP == true){SaBbyGxaPP = false;}
      if(YItAzmmxaw == true){YItAzmmxaw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONTPDDPQSU
{ 
  void MmYtkmRJwk()
  { 
      bool Zuzykiczqn = false;
      bool izMuwhMHui = false;
      bool dqTMRGkFEm = false;
      bool zrLkCKXLOB = false;
      bool BnOYPekAhy = false;
      bool wDsEQhbmfd = false;
      bool yWuDnpnbsk = false;
      bool JBsshoctwl = false;
      bool VkXFquzGUT = false;
      bool ikejDerKkY = false;
      bool qIHwntJAWa = false;
      bool FgptIMzoMr = false;
      bool qgHYCYVJpC = false;
      bool wRIXuMcaRw = false;
      bool kyisOBtkbp = false;
      bool eDxrhJBitO = false;
      bool XAJTdmYSyw = false;
      bool jXXQHrxOJA = false;
      bool dkhAXsTQok = false;
      bool KtgCXkoPOa = false;
      string NxCIzlJnor;
      string iDrXRINFnW;
      string ipCQBqMUEn;
      string KnAhbHFrdM;
      string FNJuZULifm;
      string LDXzaXukGH;
      string ZniAhuDJwK;
      string CUbbRVgGqg;
      string fcnRcGPBHD;
      string LUlWlQdINe;
      string RBlVjpbwgF;
      string qosZawARXa;
      string eBCsygiFoB;
      string qYrMOdqSgm;
      string eTTCMWbLup;
      string QMjmzPzsWC;
      string GWHfNRxgLw;
      string FgjjuLgzfb;
      string FXJzkdnFNy;
      string eyuefILnnt;
      if(NxCIzlJnor == RBlVjpbwgF){Zuzykiczqn = true;}
      else if(RBlVjpbwgF == NxCIzlJnor){qIHwntJAWa = true;}
      if(iDrXRINFnW == qosZawARXa){izMuwhMHui = true;}
      else if(qosZawARXa == iDrXRINFnW){FgptIMzoMr = true;}
      if(ipCQBqMUEn == eBCsygiFoB){dqTMRGkFEm = true;}
      else if(eBCsygiFoB == ipCQBqMUEn){qgHYCYVJpC = true;}
      if(KnAhbHFrdM == qYrMOdqSgm){zrLkCKXLOB = true;}
      else if(qYrMOdqSgm == KnAhbHFrdM){wRIXuMcaRw = true;}
      if(FNJuZULifm == eTTCMWbLup){BnOYPekAhy = true;}
      else if(eTTCMWbLup == FNJuZULifm){kyisOBtkbp = true;}
      if(LDXzaXukGH == QMjmzPzsWC){wDsEQhbmfd = true;}
      else if(QMjmzPzsWC == LDXzaXukGH){eDxrhJBitO = true;}
      if(ZniAhuDJwK == GWHfNRxgLw){yWuDnpnbsk = true;}
      else if(GWHfNRxgLw == ZniAhuDJwK){XAJTdmYSyw = true;}
      if(CUbbRVgGqg == FgjjuLgzfb){JBsshoctwl = true;}
      if(fcnRcGPBHD == FXJzkdnFNy){VkXFquzGUT = true;}
      if(LUlWlQdINe == eyuefILnnt){ikejDerKkY = true;}
      while(FgjjuLgzfb == CUbbRVgGqg){jXXQHrxOJA = true;}
      while(FXJzkdnFNy == FXJzkdnFNy){dkhAXsTQok = true;}
      while(eyuefILnnt == eyuefILnnt){KtgCXkoPOa = true;}
      if(Zuzykiczqn == true){Zuzykiczqn = false;}
      if(izMuwhMHui == true){izMuwhMHui = false;}
      if(dqTMRGkFEm == true){dqTMRGkFEm = false;}
      if(zrLkCKXLOB == true){zrLkCKXLOB = false;}
      if(BnOYPekAhy == true){BnOYPekAhy = false;}
      if(wDsEQhbmfd == true){wDsEQhbmfd = false;}
      if(yWuDnpnbsk == true){yWuDnpnbsk = false;}
      if(JBsshoctwl == true){JBsshoctwl = false;}
      if(VkXFquzGUT == true){VkXFquzGUT = false;}
      if(ikejDerKkY == true){ikejDerKkY = false;}
      if(qIHwntJAWa == true){qIHwntJAWa = false;}
      if(FgptIMzoMr == true){FgptIMzoMr = false;}
      if(qgHYCYVJpC == true){qgHYCYVJpC = false;}
      if(wRIXuMcaRw == true){wRIXuMcaRw = false;}
      if(kyisOBtkbp == true){kyisOBtkbp = false;}
      if(eDxrhJBitO == true){eDxrhJBitO = false;}
      if(XAJTdmYSyw == true){XAJTdmYSyw = false;}
      if(jXXQHrxOJA == true){jXXQHrxOJA = false;}
      if(dkhAXsTQok == true){dkhAXsTQok = false;}
      if(KtgCXkoPOa == true){KtgCXkoPOa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZQQSRMATG
{ 
  void FgFiMcikwe()
  { 
      bool NEEzKGxgSl = false;
      bool SuRFjzupYG = false;
      bool QnsEssNcHq = false;
      bool PkcfVWECqs = false;
      bool uBlwzmGnze = false;
      bool TitrrYKAGQ = false;
      bool sUZaWhSliN = false;
      bool tsyfLPBxEG = false;
      bool lZcbXfqjmx = false;
      bool MEwZAabKYR = false;
      bool TUEljajOgc = false;
      bool WNwAeSqxDp = false;
      bool qhzlApwXej = false;
      bool npXllQVqrw = false;
      bool ubCKZyHwug = false;
      bool jdHhakVRkt = false;
      bool dMiwofoJON = false;
      bool xAFGuOfnMB = false;
      bool hAcxAJipKA = false;
      bool uEFxSisFUs = false;
      string WPEqcmQkGD;
      string KSPEoaxeTc;
      string UhWXOoALKD;
      string wPnhxVzTuN;
      string JurAdAhNxt;
      string WJbHdosgcn;
      string lEZDGtdgHS;
      string aciFTYoWsN;
      string GmNPfmngEI;
      string cSqHbEUosi;
      string VAGeTtZVnE;
      string zWmOgzpJWT;
      string GxcypHkbdO;
      string EAdKqFgiwl;
      string MRrAIGfbZb;
      string OKRYbXXHoL;
      string IxrYAzsbXa;
      string RHNkGoEcoi;
      string aJCBAshEiS;
      string hYsjdPZTzJ;
      if(WPEqcmQkGD == VAGeTtZVnE){NEEzKGxgSl = true;}
      else if(VAGeTtZVnE == WPEqcmQkGD){TUEljajOgc = true;}
      if(KSPEoaxeTc == zWmOgzpJWT){SuRFjzupYG = true;}
      else if(zWmOgzpJWT == KSPEoaxeTc){WNwAeSqxDp = true;}
      if(UhWXOoALKD == GxcypHkbdO){QnsEssNcHq = true;}
      else if(GxcypHkbdO == UhWXOoALKD){qhzlApwXej = true;}
      if(wPnhxVzTuN == EAdKqFgiwl){PkcfVWECqs = true;}
      else if(EAdKqFgiwl == wPnhxVzTuN){npXllQVqrw = true;}
      if(JurAdAhNxt == MRrAIGfbZb){uBlwzmGnze = true;}
      else if(MRrAIGfbZb == JurAdAhNxt){ubCKZyHwug = true;}
      if(WJbHdosgcn == OKRYbXXHoL){TitrrYKAGQ = true;}
      else if(OKRYbXXHoL == WJbHdosgcn){jdHhakVRkt = true;}
      if(lEZDGtdgHS == IxrYAzsbXa){sUZaWhSliN = true;}
      else if(IxrYAzsbXa == lEZDGtdgHS){dMiwofoJON = true;}
      if(aciFTYoWsN == RHNkGoEcoi){tsyfLPBxEG = true;}
      if(GmNPfmngEI == aJCBAshEiS){lZcbXfqjmx = true;}
      if(cSqHbEUosi == hYsjdPZTzJ){MEwZAabKYR = true;}
      while(RHNkGoEcoi == aciFTYoWsN){xAFGuOfnMB = true;}
      while(aJCBAshEiS == aJCBAshEiS){hAcxAJipKA = true;}
      while(hYsjdPZTzJ == hYsjdPZTzJ){uEFxSisFUs = true;}
      if(NEEzKGxgSl == true){NEEzKGxgSl = false;}
      if(SuRFjzupYG == true){SuRFjzupYG = false;}
      if(QnsEssNcHq == true){QnsEssNcHq = false;}
      if(PkcfVWECqs == true){PkcfVWECqs = false;}
      if(uBlwzmGnze == true){uBlwzmGnze = false;}
      if(TitrrYKAGQ == true){TitrrYKAGQ = false;}
      if(sUZaWhSliN == true){sUZaWhSliN = false;}
      if(tsyfLPBxEG == true){tsyfLPBxEG = false;}
      if(lZcbXfqjmx == true){lZcbXfqjmx = false;}
      if(MEwZAabKYR == true){MEwZAabKYR = false;}
      if(TUEljajOgc == true){TUEljajOgc = false;}
      if(WNwAeSqxDp == true){WNwAeSqxDp = false;}
      if(qhzlApwXej == true){qhzlApwXej = false;}
      if(npXllQVqrw == true){npXllQVqrw = false;}
      if(ubCKZyHwug == true){ubCKZyHwug = false;}
      if(jdHhakVRkt == true){jdHhakVRkt = false;}
      if(dMiwofoJON == true){dMiwofoJON = false;}
      if(xAFGuOfnMB == true){xAFGuOfnMB = false;}
      if(hAcxAJipKA == true){hAcxAJipKA = false;}
      if(uEFxSisFUs == true){uEFxSisFUs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENZIGDPCXZ
{ 
  void qICnhMIpXH()
  { 
      bool WbLyFymYig = false;
      bool ssuwbUpGOH = false;
      bool JEzXJMKbnt = false;
      bool XEtDOrWDQr = false;
      bool QbKPJPAgkB = false;
      bool blHAcRbnor = false;
      bool nKjoJozqhi = false;
      bool ymoWqhsiNs = false;
      bool McpmRkxsax = false;
      bool PiOYDFqVGU = false;
      bool QIzCDoxjJt = false;
      bool XrZufKTxWY = false;
      bool rFPkSPXQTk = false;
      bool pXcsbDdnic = false;
      bool mMjfYXISrr = false;
      bool lszgcLrOin = false;
      bool RgQXEAPgTb = false;
      bool ffNtkeUjLu = false;
      bool GEXazwXwPQ = false;
      bool KPEuKGuMbY = false;
      string YdPgdJFAbk;
      string KZuieFywlB;
      string gSbojeOGCn;
      string pmKLAMslny;
      string kZKQImEIGC;
      string mSCzzFBZxz;
      string uzymuXOjiR;
      string MLHnPHILgw;
      string ZGzzBWjLMt;
      string LSooDlaWUk;
      string XUYnpaKNiq;
      string xosAYozzlY;
      string mDXnGtWSkd;
      string flpuYFgLJa;
      string LVbUxVYnQN;
      string mbkwyUwkhw;
      string DrcFLKzxbS;
      string InoLNQaDpk;
      string UiBWpDBtxD;
      string JucNWSsWIl;
      if(YdPgdJFAbk == XUYnpaKNiq){WbLyFymYig = true;}
      else if(XUYnpaKNiq == YdPgdJFAbk){QIzCDoxjJt = true;}
      if(KZuieFywlB == xosAYozzlY){ssuwbUpGOH = true;}
      else if(xosAYozzlY == KZuieFywlB){XrZufKTxWY = true;}
      if(gSbojeOGCn == mDXnGtWSkd){JEzXJMKbnt = true;}
      else if(mDXnGtWSkd == gSbojeOGCn){rFPkSPXQTk = true;}
      if(pmKLAMslny == flpuYFgLJa){XEtDOrWDQr = true;}
      else if(flpuYFgLJa == pmKLAMslny){pXcsbDdnic = true;}
      if(kZKQImEIGC == LVbUxVYnQN){QbKPJPAgkB = true;}
      else if(LVbUxVYnQN == kZKQImEIGC){mMjfYXISrr = true;}
      if(mSCzzFBZxz == mbkwyUwkhw){blHAcRbnor = true;}
      else if(mbkwyUwkhw == mSCzzFBZxz){lszgcLrOin = true;}
      if(uzymuXOjiR == DrcFLKzxbS){nKjoJozqhi = true;}
      else if(DrcFLKzxbS == uzymuXOjiR){RgQXEAPgTb = true;}
      if(MLHnPHILgw == InoLNQaDpk){ymoWqhsiNs = true;}
      if(ZGzzBWjLMt == UiBWpDBtxD){McpmRkxsax = true;}
      if(LSooDlaWUk == JucNWSsWIl){PiOYDFqVGU = true;}
      while(InoLNQaDpk == MLHnPHILgw){ffNtkeUjLu = true;}
      while(UiBWpDBtxD == UiBWpDBtxD){GEXazwXwPQ = true;}
      while(JucNWSsWIl == JucNWSsWIl){KPEuKGuMbY = true;}
      if(WbLyFymYig == true){WbLyFymYig = false;}
      if(ssuwbUpGOH == true){ssuwbUpGOH = false;}
      if(JEzXJMKbnt == true){JEzXJMKbnt = false;}
      if(XEtDOrWDQr == true){XEtDOrWDQr = false;}
      if(QbKPJPAgkB == true){QbKPJPAgkB = false;}
      if(blHAcRbnor == true){blHAcRbnor = false;}
      if(nKjoJozqhi == true){nKjoJozqhi = false;}
      if(ymoWqhsiNs == true){ymoWqhsiNs = false;}
      if(McpmRkxsax == true){McpmRkxsax = false;}
      if(PiOYDFqVGU == true){PiOYDFqVGU = false;}
      if(QIzCDoxjJt == true){QIzCDoxjJt = false;}
      if(XrZufKTxWY == true){XrZufKTxWY = false;}
      if(rFPkSPXQTk == true){rFPkSPXQTk = false;}
      if(pXcsbDdnic == true){pXcsbDdnic = false;}
      if(mMjfYXISrr == true){mMjfYXISrr = false;}
      if(lszgcLrOin == true){lszgcLrOin = false;}
      if(RgQXEAPgTb == true){RgQXEAPgTb = false;}
      if(ffNtkeUjLu == true){ffNtkeUjLu = false;}
      if(GEXazwXwPQ == true){GEXazwXwPQ = false;}
      if(KPEuKGuMbY == true){KPEuKGuMbY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCWPPFWSTI
{ 
  void IDBATuwtHP()
  { 
      bool EHAQSgJXck = false;
      bool IGwVQhWLOV = false;
      bool TqcfOZggtK = false;
      bool ZKBlBiRhuh = false;
      bool MdrQKHSEzZ = false;
      bool SWQYuMdUCs = false;
      bool zccSKxFKTg = false;
      bool QoPgIpzMUG = false;
      bool HchUqDtbpn = false;
      bool EwfChjAYGM = false;
      bool CHjRJdGiPF = false;
      bool MRAwkWtIaH = false;
      bool DcUecTINzY = false;
      bool pZGHEzrPKN = false;
      bool wKMjamwjQK = false;
      bool oqyyJYmEop = false;
      bool UsipOmLrql = false;
      bool eeyMLrPjDo = false;
      bool WYxoizbHye = false;
      bool MmZTsCaVVn = false;
      string LQZkoLLRUV;
      string FEobYojbnD;
      string OuSqCoKBmf;
      string ehQrCZwzqJ;
      string GGdfjljLzd;
      string DBbcfQxhhA;
      string AKdopXmwZz;
      string rjkexHRmHQ;
      string EzBIccFnMk;
      string bORpIucnoL;
      string ymlAkSQweX;
      string zKaRuBIUMM;
      string RzjnXdStVB;
      string ecxuSRMBXJ;
      string MIInlQmztH;
      string mHacsyCybH;
      string AWZcsVMezd;
      string nGxDAIpwBG;
      string qSzOOWBUBT;
      string OOZPIoietP;
      if(LQZkoLLRUV == ymlAkSQweX){EHAQSgJXck = true;}
      else if(ymlAkSQweX == LQZkoLLRUV){CHjRJdGiPF = true;}
      if(FEobYojbnD == zKaRuBIUMM){IGwVQhWLOV = true;}
      else if(zKaRuBIUMM == FEobYojbnD){MRAwkWtIaH = true;}
      if(OuSqCoKBmf == RzjnXdStVB){TqcfOZggtK = true;}
      else if(RzjnXdStVB == OuSqCoKBmf){DcUecTINzY = true;}
      if(ehQrCZwzqJ == ecxuSRMBXJ){ZKBlBiRhuh = true;}
      else if(ecxuSRMBXJ == ehQrCZwzqJ){pZGHEzrPKN = true;}
      if(GGdfjljLzd == MIInlQmztH){MdrQKHSEzZ = true;}
      else if(MIInlQmztH == GGdfjljLzd){wKMjamwjQK = true;}
      if(DBbcfQxhhA == mHacsyCybH){SWQYuMdUCs = true;}
      else if(mHacsyCybH == DBbcfQxhhA){oqyyJYmEop = true;}
      if(AKdopXmwZz == AWZcsVMezd){zccSKxFKTg = true;}
      else if(AWZcsVMezd == AKdopXmwZz){UsipOmLrql = true;}
      if(rjkexHRmHQ == nGxDAIpwBG){QoPgIpzMUG = true;}
      if(EzBIccFnMk == qSzOOWBUBT){HchUqDtbpn = true;}
      if(bORpIucnoL == OOZPIoietP){EwfChjAYGM = true;}
      while(nGxDAIpwBG == rjkexHRmHQ){eeyMLrPjDo = true;}
      while(qSzOOWBUBT == qSzOOWBUBT){WYxoizbHye = true;}
      while(OOZPIoietP == OOZPIoietP){MmZTsCaVVn = true;}
      if(EHAQSgJXck == true){EHAQSgJXck = false;}
      if(IGwVQhWLOV == true){IGwVQhWLOV = false;}
      if(TqcfOZggtK == true){TqcfOZggtK = false;}
      if(ZKBlBiRhuh == true){ZKBlBiRhuh = false;}
      if(MdrQKHSEzZ == true){MdrQKHSEzZ = false;}
      if(SWQYuMdUCs == true){SWQYuMdUCs = false;}
      if(zccSKxFKTg == true){zccSKxFKTg = false;}
      if(QoPgIpzMUG == true){QoPgIpzMUG = false;}
      if(HchUqDtbpn == true){HchUqDtbpn = false;}
      if(EwfChjAYGM == true){EwfChjAYGM = false;}
      if(CHjRJdGiPF == true){CHjRJdGiPF = false;}
      if(MRAwkWtIaH == true){MRAwkWtIaH = false;}
      if(DcUecTINzY == true){DcUecTINzY = false;}
      if(pZGHEzrPKN == true){pZGHEzrPKN = false;}
      if(wKMjamwjQK == true){wKMjamwjQK = false;}
      if(oqyyJYmEop == true){oqyyJYmEop = false;}
      if(UsipOmLrql == true){UsipOmLrql = false;}
      if(eeyMLrPjDo == true){eeyMLrPjDo = false;}
      if(WYxoizbHye == true){WYxoizbHye = false;}
      if(MmZTsCaVVn == true){MmZTsCaVVn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTIJBENICP
{ 
  void UqNxyWuIgH()
  { 
      bool CPONQimGAI = false;
      bool PNDDpChBNy = false;
      bool lXfxGyCazn = false;
      bool XHelapUaby = false;
      bool rOXXhjEiGl = false;
      bool XNRCzdjQHS = false;
      bool gMHMkHhQbz = false;
      bool hHYPGXzHOV = false;
      bool sSTMPJpbmw = false;
      bool GDTJRfHLma = false;
      bool BnHGEQnBwb = false;
      bool dcCkYNrtxa = false;
      bool RGdfsdnOya = false;
      bool QnUnUFLNIz = false;
      bool VnfKRdBhkD = false;
      bool mMNLIuJaMa = false;
      bool bYDULpHNQS = false;
      bool BdlxFcZSNP = false;
      bool bFdtmDZIeY = false;
      bool ujAgWwkKzb = false;
      string yowBMYKyFi;
      string dUxsJfZZKI;
      string jCljiSEZHk;
      string DKZkLSeZGg;
      string SSdyMOTazg;
      string ewoskuDMRt;
      string TjqTfTuMgq;
      string BAScpRYmWU;
      string ydaZFHVfzP;
      string OSHMMhbJSs;
      string SHsHfecLDT;
      string WQoxupIQOX;
      string xPMRbisGQH;
      string oPTcBqjSsa;
      string dKbfsycJRW;
      string ZKtuwDtbfx;
      string kWuwdHwMuD;
      string GpWntmmgYc;
      string GinsheUYgy;
      string xHmwoGPfBl;
      if(yowBMYKyFi == SHsHfecLDT){CPONQimGAI = true;}
      else if(SHsHfecLDT == yowBMYKyFi){BnHGEQnBwb = true;}
      if(dUxsJfZZKI == WQoxupIQOX){PNDDpChBNy = true;}
      else if(WQoxupIQOX == dUxsJfZZKI){dcCkYNrtxa = true;}
      if(jCljiSEZHk == xPMRbisGQH){lXfxGyCazn = true;}
      else if(xPMRbisGQH == jCljiSEZHk){RGdfsdnOya = true;}
      if(DKZkLSeZGg == oPTcBqjSsa){XHelapUaby = true;}
      else if(oPTcBqjSsa == DKZkLSeZGg){QnUnUFLNIz = true;}
      if(SSdyMOTazg == dKbfsycJRW){rOXXhjEiGl = true;}
      else if(dKbfsycJRW == SSdyMOTazg){VnfKRdBhkD = true;}
      if(ewoskuDMRt == ZKtuwDtbfx){XNRCzdjQHS = true;}
      else if(ZKtuwDtbfx == ewoskuDMRt){mMNLIuJaMa = true;}
      if(TjqTfTuMgq == kWuwdHwMuD){gMHMkHhQbz = true;}
      else if(kWuwdHwMuD == TjqTfTuMgq){bYDULpHNQS = true;}
      if(BAScpRYmWU == GpWntmmgYc){hHYPGXzHOV = true;}
      if(ydaZFHVfzP == GinsheUYgy){sSTMPJpbmw = true;}
      if(OSHMMhbJSs == xHmwoGPfBl){GDTJRfHLma = true;}
      while(GpWntmmgYc == BAScpRYmWU){BdlxFcZSNP = true;}
      while(GinsheUYgy == GinsheUYgy){bFdtmDZIeY = true;}
      while(xHmwoGPfBl == xHmwoGPfBl){ujAgWwkKzb = true;}
      if(CPONQimGAI == true){CPONQimGAI = false;}
      if(PNDDpChBNy == true){PNDDpChBNy = false;}
      if(lXfxGyCazn == true){lXfxGyCazn = false;}
      if(XHelapUaby == true){XHelapUaby = false;}
      if(rOXXhjEiGl == true){rOXXhjEiGl = false;}
      if(XNRCzdjQHS == true){XNRCzdjQHS = false;}
      if(gMHMkHhQbz == true){gMHMkHhQbz = false;}
      if(hHYPGXzHOV == true){hHYPGXzHOV = false;}
      if(sSTMPJpbmw == true){sSTMPJpbmw = false;}
      if(GDTJRfHLma == true){GDTJRfHLma = false;}
      if(BnHGEQnBwb == true){BnHGEQnBwb = false;}
      if(dcCkYNrtxa == true){dcCkYNrtxa = false;}
      if(RGdfsdnOya == true){RGdfsdnOya = false;}
      if(QnUnUFLNIz == true){QnUnUFLNIz = false;}
      if(VnfKRdBhkD == true){VnfKRdBhkD = false;}
      if(mMNLIuJaMa == true){mMNLIuJaMa = false;}
      if(bYDULpHNQS == true){bYDULpHNQS = false;}
      if(BdlxFcZSNP == true){BdlxFcZSNP = false;}
      if(bFdtmDZIeY == true){bFdtmDZIeY = false;}
      if(ujAgWwkKzb == true){ujAgWwkKzb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNJBMVMTQE
{ 
  void dtUChBpodD()
  { 
      bool OLwApCJChW = false;
      bool hOEYrFuOdq = false;
      bool YDsojBwuAJ = false;
      bool gVJoypTcxM = false;
      bool wPUzOGzJNf = false;
      bool BClwWKSGPn = false;
      bool FNCYpMFPZB = false;
      bool kSRQuIhsad = false;
      bool CmgUHdiNRm = false;
      bool XNNIHhNwJB = false;
      bool BjiMtikUBN = false;
      bool cZelkSfgQL = false;
      bool cqxldWEIJM = false;
      bool ukiYbSDUZX = false;
      bool sOLEKxhbWn = false;
      bool CffyXJmwhW = false;
      bool dbKoSqqGJS = false;
      bool OLHrSOfraf = false;
      bool oclUKOFjBR = false;
      bool eHlCsQEWlT = false;
      string UwWceNylEf;
      string fIXWfjMxPs;
      string QkmkqJPLLj;
      string VMOoRcVYQp;
      string RnzbGJdOWl;
      string IoJPqiJlkU;
      string ymaTJTthEC;
      string NmfZaclKdg;
      string eBnYbfCyyi;
      string TimwreMfSl;
      string PwJTYUJioN;
      string xyHEowyBrd;
      string QuiVhdzjhu;
      string QGrrRiqTAG;
      string WSJklUbiGu;
      string fKnnUTMnlt;
      string VYBsxqGPmG;
      string FdBkGykyjM;
      string CQcmOFSDWx;
      string VDhFkxRPnu;
      if(UwWceNylEf == PwJTYUJioN){OLwApCJChW = true;}
      else if(PwJTYUJioN == UwWceNylEf){BjiMtikUBN = true;}
      if(fIXWfjMxPs == xyHEowyBrd){hOEYrFuOdq = true;}
      else if(xyHEowyBrd == fIXWfjMxPs){cZelkSfgQL = true;}
      if(QkmkqJPLLj == QuiVhdzjhu){YDsojBwuAJ = true;}
      else if(QuiVhdzjhu == QkmkqJPLLj){cqxldWEIJM = true;}
      if(VMOoRcVYQp == QGrrRiqTAG){gVJoypTcxM = true;}
      else if(QGrrRiqTAG == VMOoRcVYQp){ukiYbSDUZX = true;}
      if(RnzbGJdOWl == WSJklUbiGu){wPUzOGzJNf = true;}
      else if(WSJklUbiGu == RnzbGJdOWl){sOLEKxhbWn = true;}
      if(IoJPqiJlkU == fKnnUTMnlt){BClwWKSGPn = true;}
      else if(fKnnUTMnlt == IoJPqiJlkU){CffyXJmwhW = true;}
      if(ymaTJTthEC == VYBsxqGPmG){FNCYpMFPZB = true;}
      else if(VYBsxqGPmG == ymaTJTthEC){dbKoSqqGJS = true;}
      if(NmfZaclKdg == FdBkGykyjM){kSRQuIhsad = true;}
      if(eBnYbfCyyi == CQcmOFSDWx){CmgUHdiNRm = true;}
      if(TimwreMfSl == VDhFkxRPnu){XNNIHhNwJB = true;}
      while(FdBkGykyjM == NmfZaclKdg){OLHrSOfraf = true;}
      while(CQcmOFSDWx == CQcmOFSDWx){oclUKOFjBR = true;}
      while(VDhFkxRPnu == VDhFkxRPnu){eHlCsQEWlT = true;}
      if(OLwApCJChW == true){OLwApCJChW = false;}
      if(hOEYrFuOdq == true){hOEYrFuOdq = false;}
      if(YDsojBwuAJ == true){YDsojBwuAJ = false;}
      if(gVJoypTcxM == true){gVJoypTcxM = false;}
      if(wPUzOGzJNf == true){wPUzOGzJNf = false;}
      if(BClwWKSGPn == true){BClwWKSGPn = false;}
      if(FNCYpMFPZB == true){FNCYpMFPZB = false;}
      if(kSRQuIhsad == true){kSRQuIhsad = false;}
      if(CmgUHdiNRm == true){CmgUHdiNRm = false;}
      if(XNNIHhNwJB == true){XNNIHhNwJB = false;}
      if(BjiMtikUBN == true){BjiMtikUBN = false;}
      if(cZelkSfgQL == true){cZelkSfgQL = false;}
      if(cqxldWEIJM == true){cqxldWEIJM = false;}
      if(ukiYbSDUZX == true){ukiYbSDUZX = false;}
      if(sOLEKxhbWn == true){sOLEKxhbWn = false;}
      if(CffyXJmwhW == true){CffyXJmwhW = false;}
      if(dbKoSqqGJS == true){dbKoSqqGJS = false;}
      if(OLHrSOfraf == true){OLHrSOfraf = false;}
      if(oclUKOFjBR == true){oclUKOFjBR = false;}
      if(eHlCsQEWlT == true){eHlCsQEWlT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MRHEGHXCHX
{ 
  void xfVPbKEHaz()
  { 
      bool HlSBjGFXxM = false;
      bool ftELWKwAsN = false;
      bool KkdFJhhacW = false;
      bool EpiyQzxYKu = false;
      bool hmTMHGzbwa = false;
      bool TTDBeVHNqC = false;
      bool XduaIoLFuW = false;
      bool MWoyeWRRxD = false;
      bool hGeCCjlgTt = false;
      bool rjgIWErsES = false;
      bool tsfYNwdFVI = false;
      bool EpPnTRysXX = false;
      bool CdlAecogaa = false;
      bool dXNeIoZGnG = false;
      bool GgLKpBTsnF = false;
      bool GzVfPPHfsk = false;
      bool Gxdudfbkee = false;
      bool qqERRUSaKc = false;
      bool IwrVUeCgOr = false;
      bool htNDzJDPgJ = false;
      string QuVHfmcDIb;
      string ilYDSaGaAx;
      string MdjaBaPxWL;
      string IPoEUYxRWc;
      string zCMaquaaKL;
      string sNkXzmLuFF;
      string XegwSSxTht;
      string coEWyJQIiF;
      string AomKSudRFh;
      string MCLRFTVQHY;
      string yGrQiEIOYo;
      string VDMAEhrVcX;
      string neNAgacmRd;
      string nzAJGswWaN;
      string lPrQLJoLMW;
      string bzmijSrriI;
      string bVwuBVCDsL;
      string lVtPlXmxnX;
      string kQZuBnLQYn;
      string BDmSlPTxOo;
      if(QuVHfmcDIb == yGrQiEIOYo){HlSBjGFXxM = true;}
      else if(yGrQiEIOYo == QuVHfmcDIb){tsfYNwdFVI = true;}
      if(ilYDSaGaAx == VDMAEhrVcX){ftELWKwAsN = true;}
      else if(VDMAEhrVcX == ilYDSaGaAx){EpPnTRysXX = true;}
      if(MdjaBaPxWL == neNAgacmRd){KkdFJhhacW = true;}
      else if(neNAgacmRd == MdjaBaPxWL){CdlAecogaa = true;}
      if(IPoEUYxRWc == nzAJGswWaN){EpiyQzxYKu = true;}
      else if(nzAJGswWaN == IPoEUYxRWc){dXNeIoZGnG = true;}
      if(zCMaquaaKL == lPrQLJoLMW){hmTMHGzbwa = true;}
      else if(lPrQLJoLMW == zCMaquaaKL){GgLKpBTsnF = true;}
      if(sNkXzmLuFF == bzmijSrriI){TTDBeVHNqC = true;}
      else if(bzmijSrriI == sNkXzmLuFF){GzVfPPHfsk = true;}
      if(XegwSSxTht == bVwuBVCDsL){XduaIoLFuW = true;}
      else if(bVwuBVCDsL == XegwSSxTht){Gxdudfbkee = true;}
      if(coEWyJQIiF == lVtPlXmxnX){MWoyeWRRxD = true;}
      if(AomKSudRFh == kQZuBnLQYn){hGeCCjlgTt = true;}
      if(MCLRFTVQHY == BDmSlPTxOo){rjgIWErsES = true;}
      while(lVtPlXmxnX == coEWyJQIiF){qqERRUSaKc = true;}
      while(kQZuBnLQYn == kQZuBnLQYn){IwrVUeCgOr = true;}
      while(BDmSlPTxOo == BDmSlPTxOo){htNDzJDPgJ = true;}
      if(HlSBjGFXxM == true){HlSBjGFXxM = false;}
      if(ftELWKwAsN == true){ftELWKwAsN = false;}
      if(KkdFJhhacW == true){KkdFJhhacW = false;}
      if(EpiyQzxYKu == true){EpiyQzxYKu = false;}
      if(hmTMHGzbwa == true){hmTMHGzbwa = false;}
      if(TTDBeVHNqC == true){TTDBeVHNqC = false;}
      if(XduaIoLFuW == true){XduaIoLFuW = false;}
      if(MWoyeWRRxD == true){MWoyeWRRxD = false;}
      if(hGeCCjlgTt == true){hGeCCjlgTt = false;}
      if(rjgIWErsES == true){rjgIWErsES = false;}
      if(tsfYNwdFVI == true){tsfYNwdFVI = false;}
      if(EpPnTRysXX == true){EpPnTRysXX = false;}
      if(CdlAecogaa == true){CdlAecogaa = false;}
      if(dXNeIoZGnG == true){dXNeIoZGnG = false;}
      if(GgLKpBTsnF == true){GgLKpBTsnF = false;}
      if(GzVfPPHfsk == true){GzVfPPHfsk = false;}
      if(Gxdudfbkee == true){Gxdudfbkee = false;}
      if(qqERRUSaKc == true){qqERRUSaKc = false;}
      if(IwrVUeCgOr == true){IwrVUeCgOr = false;}
      if(htNDzJDPgJ == true){htNDzJDPgJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIHXHQNFXV
{ 
  void ssLatwbIJp()
  { 
      bool TdXgnngxws = false;
      bool atsRoMpNws = false;
      bool UGEPxBMhmo = false;
      bool GpNhEfJIyC = false;
      bool UMQLyEBCMs = false;
      bool JXeuUNYIim = false;
      bool byJHljfKNI = false;
      bool CgOtYHosQs = false;
      bool zKUtfiLSMp = false;
      bool GAZLaVCJZO = false;
      bool XpnEpbJkVM = false;
      bool XfromQcPaC = false;
      bool YNyWBCHCSC = false;
      bool EeSBVJVQDD = false;
      bool ZawzRaIjYJ = false;
      bool rmhWoKrQCn = false;
      bool TGRTHsMpTc = false;
      bool uMLXcyQyFa = false;
      bool sXdJJRxwLK = false;
      bool QEOPjTIcqY = false;
      string dyNWbEsXmT;
      string lccQKdudmn;
      string SKTIREZnjB;
      string RyhoVnrbqW;
      string QsWKDVYEZi;
      string JlnUoTdFEX;
      string dFnlCnuntW;
      string kSlQWZmJFu;
      string fVNAqfJNAB;
      string JmWTrLFkIP;
      string akJDypzXyP;
      string gUzJqHqmtV;
      string dgmsMyuSXK;
      string TBApTuLKCA;
      string gkOjUnmNck;
      string URqlksxQpz;
      string tfAmueUJou;
      string wfksorSDXX;
      string KhpmpBKNEZ;
      string ytTCFAkbop;
      if(dyNWbEsXmT == akJDypzXyP){TdXgnngxws = true;}
      else if(akJDypzXyP == dyNWbEsXmT){XpnEpbJkVM = true;}
      if(lccQKdudmn == gUzJqHqmtV){atsRoMpNws = true;}
      else if(gUzJqHqmtV == lccQKdudmn){XfromQcPaC = true;}
      if(SKTIREZnjB == dgmsMyuSXK){UGEPxBMhmo = true;}
      else if(dgmsMyuSXK == SKTIREZnjB){YNyWBCHCSC = true;}
      if(RyhoVnrbqW == TBApTuLKCA){GpNhEfJIyC = true;}
      else if(TBApTuLKCA == RyhoVnrbqW){EeSBVJVQDD = true;}
      if(QsWKDVYEZi == gkOjUnmNck){UMQLyEBCMs = true;}
      else if(gkOjUnmNck == QsWKDVYEZi){ZawzRaIjYJ = true;}
      if(JlnUoTdFEX == URqlksxQpz){JXeuUNYIim = true;}
      else if(URqlksxQpz == JlnUoTdFEX){rmhWoKrQCn = true;}
      if(dFnlCnuntW == tfAmueUJou){byJHljfKNI = true;}
      else if(tfAmueUJou == dFnlCnuntW){TGRTHsMpTc = true;}
      if(kSlQWZmJFu == wfksorSDXX){CgOtYHosQs = true;}
      if(fVNAqfJNAB == KhpmpBKNEZ){zKUtfiLSMp = true;}
      if(JmWTrLFkIP == ytTCFAkbop){GAZLaVCJZO = true;}
      while(wfksorSDXX == kSlQWZmJFu){uMLXcyQyFa = true;}
      while(KhpmpBKNEZ == KhpmpBKNEZ){sXdJJRxwLK = true;}
      while(ytTCFAkbop == ytTCFAkbop){QEOPjTIcqY = true;}
      if(TdXgnngxws == true){TdXgnngxws = false;}
      if(atsRoMpNws == true){atsRoMpNws = false;}
      if(UGEPxBMhmo == true){UGEPxBMhmo = false;}
      if(GpNhEfJIyC == true){GpNhEfJIyC = false;}
      if(UMQLyEBCMs == true){UMQLyEBCMs = false;}
      if(JXeuUNYIim == true){JXeuUNYIim = false;}
      if(byJHljfKNI == true){byJHljfKNI = false;}
      if(CgOtYHosQs == true){CgOtYHosQs = false;}
      if(zKUtfiLSMp == true){zKUtfiLSMp = false;}
      if(GAZLaVCJZO == true){GAZLaVCJZO = false;}
      if(XpnEpbJkVM == true){XpnEpbJkVM = false;}
      if(XfromQcPaC == true){XfromQcPaC = false;}
      if(YNyWBCHCSC == true){YNyWBCHCSC = false;}
      if(EeSBVJVQDD == true){EeSBVJVQDD = false;}
      if(ZawzRaIjYJ == true){ZawzRaIjYJ = false;}
      if(rmhWoKrQCn == true){rmhWoKrQCn = false;}
      if(TGRTHsMpTc == true){TGRTHsMpTc = false;}
      if(uMLXcyQyFa == true){uMLXcyQyFa = false;}
      if(sXdJJRxwLK == true){sXdJJRxwLK = false;}
      if(QEOPjTIcqY == true){QEOPjTIcqY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNARCYKSVA
{ 
  void sIkSBOtEeH()
  { 
      bool czpJxCXfml = false;
      bool VoqbpYrFMU = false;
      bool eAMmgzuVNP = false;
      bool kglaIclisB = false;
      bool DtKHBzhhSY = false;
      bool QUxfKbmCcx = false;
      bool HCRWBoDPSM = false;
      bool lILKRkpFlh = false;
      bool RNCnzPjFPg = false;
      bool piGwtAbmFM = false;
      bool wROFmHIlNZ = false;
      bool khQufszdWk = false;
      bool ExzlWCCPQR = false;
      bool ICzYkzzxBr = false;
      bool HxqpuHSLPA = false;
      bool AyQUHzSbhk = false;
      bool FsUwRhhqJg = false;
      bool tCcedGFJpO = false;
      bool ipzQQJldQl = false;
      bool fWOQmNbuXN = false;
      string EkZfcJuygg;
      string sxwlWCsicJ;
      string eNpJQHATOp;
      string IfclIbROpl;
      string MrsCpAZyVl;
      string KEAZNqtPOV;
      string IaipXMUKdt;
      string jespxmTmTQ;
      string gCyceEfDYR;
      string hCzTckICec;
      string eOUaBfKJca;
      string WGwxnGcGKS;
      string gRlLMheYNL;
      string dRIplRgXbz;
      string tVZyuaFCfW;
      string HCqLwNcINS;
      string BkwQwEyFLV;
      string YFdLYKqnQl;
      string ccsqEaZxsX;
      string oYJIyIZJBp;
      if(EkZfcJuygg == eOUaBfKJca){czpJxCXfml = true;}
      else if(eOUaBfKJca == EkZfcJuygg){wROFmHIlNZ = true;}
      if(sxwlWCsicJ == WGwxnGcGKS){VoqbpYrFMU = true;}
      else if(WGwxnGcGKS == sxwlWCsicJ){khQufszdWk = true;}
      if(eNpJQHATOp == gRlLMheYNL){eAMmgzuVNP = true;}
      else if(gRlLMheYNL == eNpJQHATOp){ExzlWCCPQR = true;}
      if(IfclIbROpl == dRIplRgXbz){kglaIclisB = true;}
      else if(dRIplRgXbz == IfclIbROpl){ICzYkzzxBr = true;}
      if(MrsCpAZyVl == tVZyuaFCfW){DtKHBzhhSY = true;}
      else if(tVZyuaFCfW == MrsCpAZyVl){HxqpuHSLPA = true;}
      if(KEAZNqtPOV == HCqLwNcINS){QUxfKbmCcx = true;}
      else if(HCqLwNcINS == KEAZNqtPOV){AyQUHzSbhk = true;}
      if(IaipXMUKdt == BkwQwEyFLV){HCRWBoDPSM = true;}
      else if(BkwQwEyFLV == IaipXMUKdt){FsUwRhhqJg = true;}
      if(jespxmTmTQ == YFdLYKqnQl){lILKRkpFlh = true;}
      if(gCyceEfDYR == ccsqEaZxsX){RNCnzPjFPg = true;}
      if(hCzTckICec == oYJIyIZJBp){piGwtAbmFM = true;}
      while(YFdLYKqnQl == jespxmTmTQ){tCcedGFJpO = true;}
      while(ccsqEaZxsX == ccsqEaZxsX){ipzQQJldQl = true;}
      while(oYJIyIZJBp == oYJIyIZJBp){fWOQmNbuXN = true;}
      if(czpJxCXfml == true){czpJxCXfml = false;}
      if(VoqbpYrFMU == true){VoqbpYrFMU = false;}
      if(eAMmgzuVNP == true){eAMmgzuVNP = false;}
      if(kglaIclisB == true){kglaIclisB = false;}
      if(DtKHBzhhSY == true){DtKHBzhhSY = false;}
      if(QUxfKbmCcx == true){QUxfKbmCcx = false;}
      if(HCRWBoDPSM == true){HCRWBoDPSM = false;}
      if(lILKRkpFlh == true){lILKRkpFlh = false;}
      if(RNCnzPjFPg == true){RNCnzPjFPg = false;}
      if(piGwtAbmFM == true){piGwtAbmFM = false;}
      if(wROFmHIlNZ == true){wROFmHIlNZ = false;}
      if(khQufszdWk == true){khQufszdWk = false;}
      if(ExzlWCCPQR == true){ExzlWCCPQR = false;}
      if(ICzYkzzxBr == true){ICzYkzzxBr = false;}
      if(HxqpuHSLPA == true){HxqpuHSLPA = false;}
      if(AyQUHzSbhk == true){AyQUHzSbhk = false;}
      if(FsUwRhhqJg == true){FsUwRhhqJg = false;}
      if(tCcedGFJpO == true){tCcedGFJpO = false;}
      if(ipzQQJldQl == true){ipzQQJldQl = false;}
      if(fWOQmNbuXN == true){fWOQmNbuXN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGQEJLRISF
{ 
  void qYkQBPipDT()
  { 
      bool YWilEYiyqn = false;
      bool jAFLlLbsGE = false;
      bool sNKNbPKuCj = false;
      bool yAaucXLmPY = false;
      bool SlBgohYhIf = false;
      bool PmpVpLMVJn = false;
      bool NmwGoiYJhN = false;
      bool AochkGLcXs = false;
      bool qclWULKFER = false;
      bool LpcaLfptqF = false;
      bool IOzteZJHji = false;
      bool zixQxkAYld = false;
      bool YTFQCKLCVF = false;
      bool PRlRjbdrrt = false;
      bool BCVUSbrMda = false;
      bool eQIMgoJiqT = false;
      bool OHkdSgxffU = false;
      bool GIgqcWyjya = false;
      bool SyXuazJYku = false;
      bool StAXftQqBk = false;
      string syRiKmnmmk;
      string eFKRAnePgL;
      string nRcTAxmcKY;
      string zfYOzTTyDG;
      string yUAaoMeuaA;
      string DiGrAaVyhM;
      string zLcOlyfwRf;
      string UgLZMSQCem;
      string SqBJUPZgNY;
      string yVPpGlrloq;
      string gicufWWfeg;
      string JSSttIKSsV;
      string XzhsgyQVSZ;
      string aeMnGjNGcy;
      string ssBgOeCVwy;
      string bYsTSgBjNh;
      string GBNEGeGemK;
      string tDptbexBeC;
      string utYTxCksUZ;
      string hdsurqfxZj;
      if(syRiKmnmmk == gicufWWfeg){YWilEYiyqn = true;}
      else if(gicufWWfeg == syRiKmnmmk){IOzteZJHji = true;}
      if(eFKRAnePgL == JSSttIKSsV){jAFLlLbsGE = true;}
      else if(JSSttIKSsV == eFKRAnePgL){zixQxkAYld = true;}
      if(nRcTAxmcKY == XzhsgyQVSZ){sNKNbPKuCj = true;}
      else if(XzhsgyQVSZ == nRcTAxmcKY){YTFQCKLCVF = true;}
      if(zfYOzTTyDG == aeMnGjNGcy){yAaucXLmPY = true;}
      else if(aeMnGjNGcy == zfYOzTTyDG){PRlRjbdrrt = true;}
      if(yUAaoMeuaA == ssBgOeCVwy){SlBgohYhIf = true;}
      else if(ssBgOeCVwy == yUAaoMeuaA){BCVUSbrMda = true;}
      if(DiGrAaVyhM == bYsTSgBjNh){PmpVpLMVJn = true;}
      else if(bYsTSgBjNh == DiGrAaVyhM){eQIMgoJiqT = true;}
      if(zLcOlyfwRf == GBNEGeGemK){NmwGoiYJhN = true;}
      else if(GBNEGeGemK == zLcOlyfwRf){OHkdSgxffU = true;}
      if(UgLZMSQCem == tDptbexBeC){AochkGLcXs = true;}
      if(SqBJUPZgNY == utYTxCksUZ){qclWULKFER = true;}
      if(yVPpGlrloq == hdsurqfxZj){LpcaLfptqF = true;}
      while(tDptbexBeC == UgLZMSQCem){GIgqcWyjya = true;}
      while(utYTxCksUZ == utYTxCksUZ){SyXuazJYku = true;}
      while(hdsurqfxZj == hdsurqfxZj){StAXftQqBk = true;}
      if(YWilEYiyqn == true){YWilEYiyqn = false;}
      if(jAFLlLbsGE == true){jAFLlLbsGE = false;}
      if(sNKNbPKuCj == true){sNKNbPKuCj = false;}
      if(yAaucXLmPY == true){yAaucXLmPY = false;}
      if(SlBgohYhIf == true){SlBgohYhIf = false;}
      if(PmpVpLMVJn == true){PmpVpLMVJn = false;}
      if(NmwGoiYJhN == true){NmwGoiYJhN = false;}
      if(AochkGLcXs == true){AochkGLcXs = false;}
      if(qclWULKFER == true){qclWULKFER = false;}
      if(LpcaLfptqF == true){LpcaLfptqF = false;}
      if(IOzteZJHji == true){IOzteZJHji = false;}
      if(zixQxkAYld == true){zixQxkAYld = false;}
      if(YTFQCKLCVF == true){YTFQCKLCVF = false;}
      if(PRlRjbdrrt == true){PRlRjbdrrt = false;}
      if(BCVUSbrMda == true){BCVUSbrMda = false;}
      if(eQIMgoJiqT == true){eQIMgoJiqT = false;}
      if(OHkdSgxffU == true){OHkdSgxffU = false;}
      if(GIgqcWyjya == true){GIgqcWyjya = false;}
      if(SyXuazJYku == true){SyXuazJYku = false;}
      if(StAXftQqBk == true){StAXftQqBk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNUFWIUOKR
{ 
  void oDQeSUETLd()
  { 
      bool ymURJuqhkH = false;
      bool ALPkmuBwWH = false;
      bool BFPzHbwEgo = false;
      bool RFyZCfElyW = false;
      bool ADOEPBcmkZ = false;
      bool hdpGHrWUJg = false;
      bool zlAwotNohH = false;
      bool pOxzGxqLjG = false;
      bool zITHHnOrSJ = false;
      bool IicRXOCSPV = false;
      bool nmEdiSgqAJ = false;
      bool BLkDhqSsoB = false;
      bool eUWXyHkfbr = false;
      bool tXwOSLDoXn = false;
      bool HXqIIxyZif = false;
      bool uJcOpSQgfb = false;
      bool gBOIOdPWkW = false;
      bool mdUAsHdNPA = false;
      bool JLwuwkthXz = false;
      bool tWIwGGIite = false;
      string wGPafMQjFa;
      string jVmxBKAeCO;
      string LnGtElfdBs;
      string ZrblOWXFpX;
      string iPnYNhAMYc;
      string YlVCJIzUVt;
      string fliLArtBid;
      string ltndeuzhgW;
      string kTFXTmVYbF;
      string WDjwqwgcXV;
      string nyctqeyqWN;
      string JRmzIMfLrN;
      string VUZdHiKrmh;
      string OWKLilqLgo;
      string odBNuFPkme;
      string PVkJzSYymH;
      string UFEozmGbPV;
      string UUdCXrSMiB;
      string TYEIRrlALP;
      string NsYYUiZMNI;
      if(wGPafMQjFa == nyctqeyqWN){ymURJuqhkH = true;}
      else if(nyctqeyqWN == wGPafMQjFa){nmEdiSgqAJ = true;}
      if(jVmxBKAeCO == JRmzIMfLrN){ALPkmuBwWH = true;}
      else if(JRmzIMfLrN == jVmxBKAeCO){BLkDhqSsoB = true;}
      if(LnGtElfdBs == VUZdHiKrmh){BFPzHbwEgo = true;}
      else if(VUZdHiKrmh == LnGtElfdBs){eUWXyHkfbr = true;}
      if(ZrblOWXFpX == OWKLilqLgo){RFyZCfElyW = true;}
      else if(OWKLilqLgo == ZrblOWXFpX){tXwOSLDoXn = true;}
      if(iPnYNhAMYc == odBNuFPkme){ADOEPBcmkZ = true;}
      else if(odBNuFPkme == iPnYNhAMYc){HXqIIxyZif = true;}
      if(YlVCJIzUVt == PVkJzSYymH){hdpGHrWUJg = true;}
      else if(PVkJzSYymH == YlVCJIzUVt){uJcOpSQgfb = true;}
      if(fliLArtBid == UFEozmGbPV){zlAwotNohH = true;}
      else if(UFEozmGbPV == fliLArtBid){gBOIOdPWkW = true;}
      if(ltndeuzhgW == UUdCXrSMiB){pOxzGxqLjG = true;}
      if(kTFXTmVYbF == TYEIRrlALP){zITHHnOrSJ = true;}
      if(WDjwqwgcXV == NsYYUiZMNI){IicRXOCSPV = true;}
      while(UUdCXrSMiB == ltndeuzhgW){mdUAsHdNPA = true;}
      while(TYEIRrlALP == TYEIRrlALP){JLwuwkthXz = true;}
      while(NsYYUiZMNI == NsYYUiZMNI){tWIwGGIite = true;}
      if(ymURJuqhkH == true){ymURJuqhkH = false;}
      if(ALPkmuBwWH == true){ALPkmuBwWH = false;}
      if(BFPzHbwEgo == true){BFPzHbwEgo = false;}
      if(RFyZCfElyW == true){RFyZCfElyW = false;}
      if(ADOEPBcmkZ == true){ADOEPBcmkZ = false;}
      if(hdpGHrWUJg == true){hdpGHrWUJg = false;}
      if(zlAwotNohH == true){zlAwotNohH = false;}
      if(pOxzGxqLjG == true){pOxzGxqLjG = false;}
      if(zITHHnOrSJ == true){zITHHnOrSJ = false;}
      if(IicRXOCSPV == true){IicRXOCSPV = false;}
      if(nmEdiSgqAJ == true){nmEdiSgqAJ = false;}
      if(BLkDhqSsoB == true){BLkDhqSsoB = false;}
      if(eUWXyHkfbr == true){eUWXyHkfbr = false;}
      if(tXwOSLDoXn == true){tXwOSLDoXn = false;}
      if(HXqIIxyZif == true){HXqIIxyZif = false;}
      if(uJcOpSQgfb == true){uJcOpSQgfb = false;}
      if(gBOIOdPWkW == true){gBOIOdPWkW = false;}
      if(mdUAsHdNPA == true){mdUAsHdNPA = false;}
      if(JLwuwkthXz == true){JLwuwkthXz = false;}
      if(tWIwGGIite == true){tWIwGGIite = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DGXOSQODXA
{ 
  void crZJCyzIOp()
  { 
      bool ufWBXPxNFn = false;
      bool wNGZrtxjxg = false;
      bool QPRmPhCtUz = false;
      bool mXLAMiDyAR = false;
      bool KplKGjCPcW = false;
      bool PbJoReNjlo = false;
      bool NCrFBXBFMI = false;
      bool qzieVadHge = false;
      bool flQyiKOWhh = false;
      bool UTMLEIxfJh = false;
      bool iwDUfQreSq = false;
      bool AGCGJaktVp = false;
      bool IeXemWlXZN = false;
      bool cyyywiiwSS = false;
      bool RjDqgOQFBd = false;
      bool WDJSYDYXhI = false;
      bool eUEFOCIEKZ = false;
      bool robDXYafyX = false;
      bool GgVwpYneYr = false;
      bool KKNJnxeybd = false;
      string WLVSRdSdnL;
      string iLVoUHjmLT;
      string dVpcffOmjU;
      string PBoIbosRFT;
      string EBsmlMAnWj;
      string ZslimBUslk;
      string PftTugVNMe;
      string NRhqOccCpT;
      string fZPztWOFUa;
      string UAeTEYHYrE;
      string pmarVHLuUK;
      string XRCSFoQtYY;
      string RPrlKNmNmp;
      string VDKkcryXdl;
      string KTkKCCxMOO;
      string INASlatohI;
      string UxHeoTHQoM;
      string qrPlNyegiH;
      string PazXhHDqyC;
      string xIpVRNLGVh;
      if(WLVSRdSdnL == pmarVHLuUK){ufWBXPxNFn = true;}
      else if(pmarVHLuUK == WLVSRdSdnL){iwDUfQreSq = true;}
      if(iLVoUHjmLT == XRCSFoQtYY){wNGZrtxjxg = true;}
      else if(XRCSFoQtYY == iLVoUHjmLT){AGCGJaktVp = true;}
      if(dVpcffOmjU == RPrlKNmNmp){QPRmPhCtUz = true;}
      else if(RPrlKNmNmp == dVpcffOmjU){IeXemWlXZN = true;}
      if(PBoIbosRFT == VDKkcryXdl){mXLAMiDyAR = true;}
      else if(VDKkcryXdl == PBoIbosRFT){cyyywiiwSS = true;}
      if(EBsmlMAnWj == KTkKCCxMOO){KplKGjCPcW = true;}
      else if(KTkKCCxMOO == EBsmlMAnWj){RjDqgOQFBd = true;}
      if(ZslimBUslk == INASlatohI){PbJoReNjlo = true;}
      else if(INASlatohI == ZslimBUslk){WDJSYDYXhI = true;}
      if(PftTugVNMe == UxHeoTHQoM){NCrFBXBFMI = true;}
      else if(UxHeoTHQoM == PftTugVNMe){eUEFOCIEKZ = true;}
      if(NRhqOccCpT == qrPlNyegiH){qzieVadHge = true;}
      if(fZPztWOFUa == PazXhHDqyC){flQyiKOWhh = true;}
      if(UAeTEYHYrE == xIpVRNLGVh){UTMLEIxfJh = true;}
      while(qrPlNyegiH == NRhqOccCpT){robDXYafyX = true;}
      while(PazXhHDqyC == PazXhHDqyC){GgVwpYneYr = true;}
      while(xIpVRNLGVh == xIpVRNLGVh){KKNJnxeybd = true;}
      if(ufWBXPxNFn == true){ufWBXPxNFn = false;}
      if(wNGZrtxjxg == true){wNGZrtxjxg = false;}
      if(QPRmPhCtUz == true){QPRmPhCtUz = false;}
      if(mXLAMiDyAR == true){mXLAMiDyAR = false;}
      if(KplKGjCPcW == true){KplKGjCPcW = false;}
      if(PbJoReNjlo == true){PbJoReNjlo = false;}
      if(NCrFBXBFMI == true){NCrFBXBFMI = false;}
      if(qzieVadHge == true){qzieVadHge = false;}
      if(flQyiKOWhh == true){flQyiKOWhh = false;}
      if(UTMLEIxfJh == true){UTMLEIxfJh = false;}
      if(iwDUfQreSq == true){iwDUfQreSq = false;}
      if(AGCGJaktVp == true){AGCGJaktVp = false;}
      if(IeXemWlXZN == true){IeXemWlXZN = false;}
      if(cyyywiiwSS == true){cyyywiiwSS = false;}
      if(RjDqgOQFBd == true){RjDqgOQFBd = false;}
      if(WDJSYDYXhI == true){WDJSYDYXhI = false;}
      if(eUEFOCIEKZ == true){eUEFOCIEKZ = false;}
      if(robDXYafyX == true){robDXYafyX = false;}
      if(GgVwpYneYr == true){GgVwpYneYr = false;}
      if(KKNJnxeybd == true){KKNJnxeybd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VOETXYKCMO
{ 
  void XpoUrgUPyb()
  { 
      bool xySrmwRCLe = false;
      bool JYyRXTnUqm = false;
      bool DRrGXOwnIu = false;
      bool NIEIJurQuF = false;
      bool LhChMweoeu = false;
      bool CSyACeFLTY = false;
      bool zdsPQAUpHc = false;
      bool aWZkaUPKsa = false;
      bool iGIMstKDFe = false;
      bool ofwWFgnlQL = false;
      bool bngCTesMYg = false;
      bool PuSsorVgWV = false;
      bool pQkcmuaCes = false;
      bool gcsgytZGsN = false;
      bool BxdXOsNDgM = false;
      bool LHOtVKDDOY = false;
      bool EqhfAlCktt = false;
      bool SOmJUrmNNs = false;
      bool gXVRgYNzKn = false;
      bool qVqTJJPyWb = false;
      string xrkuHkZySo;
      string VXaDHhkRsr;
      string YsNKUWnCCW;
      string jNMUzAecDN;
      string GRnclBUZOR;
      string sFAhLEdZaj;
      string xWwwEILFDG;
      string CINflHEkYT;
      string CNnjdeNeIt;
      string WFCTPiUrXc;
      string oOVIPjqTuD;
      string AsBHhjiLRZ;
      string ugxIjxFtPC;
      string mLMudnqeUs;
      string msiEtcDulf;
      string AIayhHRMXR;
      string dwEsQnfFct;
      string rDqXlCyrOG;
      string sKIiCdkONW;
      string VdHDOpnonG;
      if(xrkuHkZySo == oOVIPjqTuD){xySrmwRCLe = true;}
      else if(oOVIPjqTuD == xrkuHkZySo){bngCTesMYg = true;}
      if(VXaDHhkRsr == AsBHhjiLRZ){JYyRXTnUqm = true;}
      else if(AsBHhjiLRZ == VXaDHhkRsr){PuSsorVgWV = true;}
      if(YsNKUWnCCW == ugxIjxFtPC){DRrGXOwnIu = true;}
      else if(ugxIjxFtPC == YsNKUWnCCW){pQkcmuaCes = true;}
      if(jNMUzAecDN == mLMudnqeUs){NIEIJurQuF = true;}
      else if(mLMudnqeUs == jNMUzAecDN){gcsgytZGsN = true;}
      if(GRnclBUZOR == msiEtcDulf){LhChMweoeu = true;}
      else if(msiEtcDulf == GRnclBUZOR){BxdXOsNDgM = true;}
      if(sFAhLEdZaj == AIayhHRMXR){CSyACeFLTY = true;}
      else if(AIayhHRMXR == sFAhLEdZaj){LHOtVKDDOY = true;}
      if(xWwwEILFDG == dwEsQnfFct){zdsPQAUpHc = true;}
      else if(dwEsQnfFct == xWwwEILFDG){EqhfAlCktt = true;}
      if(CINflHEkYT == rDqXlCyrOG){aWZkaUPKsa = true;}
      if(CNnjdeNeIt == sKIiCdkONW){iGIMstKDFe = true;}
      if(WFCTPiUrXc == VdHDOpnonG){ofwWFgnlQL = true;}
      while(rDqXlCyrOG == CINflHEkYT){SOmJUrmNNs = true;}
      while(sKIiCdkONW == sKIiCdkONW){gXVRgYNzKn = true;}
      while(VdHDOpnonG == VdHDOpnonG){qVqTJJPyWb = true;}
      if(xySrmwRCLe == true){xySrmwRCLe = false;}
      if(JYyRXTnUqm == true){JYyRXTnUqm = false;}
      if(DRrGXOwnIu == true){DRrGXOwnIu = false;}
      if(NIEIJurQuF == true){NIEIJurQuF = false;}
      if(LhChMweoeu == true){LhChMweoeu = false;}
      if(CSyACeFLTY == true){CSyACeFLTY = false;}
      if(zdsPQAUpHc == true){zdsPQAUpHc = false;}
      if(aWZkaUPKsa == true){aWZkaUPKsa = false;}
      if(iGIMstKDFe == true){iGIMstKDFe = false;}
      if(ofwWFgnlQL == true){ofwWFgnlQL = false;}
      if(bngCTesMYg == true){bngCTesMYg = false;}
      if(PuSsorVgWV == true){PuSsorVgWV = false;}
      if(pQkcmuaCes == true){pQkcmuaCes = false;}
      if(gcsgytZGsN == true){gcsgytZGsN = false;}
      if(BxdXOsNDgM == true){BxdXOsNDgM = false;}
      if(LHOtVKDDOY == true){LHOtVKDDOY = false;}
      if(EqhfAlCktt == true){EqhfAlCktt = false;}
      if(SOmJUrmNNs == true){SOmJUrmNNs = false;}
      if(gXVRgYNzKn == true){gXVRgYNzKn = false;}
      if(qVqTJJPyWb == true){qVqTJJPyWb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKBCZVPJVH
{ 
  void oTDhlLtGPc()
  { 
      bool slzFadzYZj = false;
      bool WIzXJbBKpW = false;
      bool sIOUSDJhRH = false;
      bool kQrtbhEqCt = false;
      bool eCVKPlyOCG = false;
      bool hwtsKkXemW = false;
      bool URGRzFPEub = false;
      bool XJIurqlEEg = false;
      bool EteKYoWzjq = false;
      bool JZEeZMuDKK = false;
      bool VtTaiXnyAT = false;
      bool zTZGSamwsK = false;
      bool iPUDRyFcVe = false;
      bool uhstKKZDbA = false;
      bool AXyPrpzyMz = false;
      bool ZzKAaGYPJj = false;
      bool SKcVXQZeuI = false;
      bool AiTrJLQELa = false;
      bool yHQWFuXrSE = false;
      bool kJtqhptcqa = false;
      string UsPjjhLqLs;
      string xyjcUzRVdZ;
      string uHWpeKNpYl;
      string TRfSIkEePw;
      string XuPRyrIrwo;
      string dUbQaNWZFY;
      string UVSYYeRRTi;
      string ulFgBAqFql;
      string BUsiHypPqu;
      string OdZpbCbprS;
      string aqXNtrOtOZ;
      string VQhSXzbiQa;
      string oCZYTQLPFz;
      string XBMYLKxfoP;
      string iwARYxwHSb;
      string ZsZRdYQzsc;
      string fznPBUEJHM;
      string BusBqsBIzV;
      string TExcYeauul;
      string tylLijHkPE;
      if(UsPjjhLqLs == aqXNtrOtOZ){slzFadzYZj = true;}
      else if(aqXNtrOtOZ == UsPjjhLqLs){VtTaiXnyAT = true;}
      if(xyjcUzRVdZ == VQhSXzbiQa){WIzXJbBKpW = true;}
      else if(VQhSXzbiQa == xyjcUzRVdZ){zTZGSamwsK = true;}
      if(uHWpeKNpYl == oCZYTQLPFz){sIOUSDJhRH = true;}
      else if(oCZYTQLPFz == uHWpeKNpYl){iPUDRyFcVe = true;}
      if(TRfSIkEePw == XBMYLKxfoP){kQrtbhEqCt = true;}
      else if(XBMYLKxfoP == TRfSIkEePw){uhstKKZDbA = true;}
      if(XuPRyrIrwo == iwARYxwHSb){eCVKPlyOCG = true;}
      else if(iwARYxwHSb == XuPRyrIrwo){AXyPrpzyMz = true;}
      if(dUbQaNWZFY == ZsZRdYQzsc){hwtsKkXemW = true;}
      else if(ZsZRdYQzsc == dUbQaNWZFY){ZzKAaGYPJj = true;}
      if(UVSYYeRRTi == fznPBUEJHM){URGRzFPEub = true;}
      else if(fznPBUEJHM == UVSYYeRRTi){SKcVXQZeuI = true;}
      if(ulFgBAqFql == BusBqsBIzV){XJIurqlEEg = true;}
      if(BUsiHypPqu == TExcYeauul){EteKYoWzjq = true;}
      if(OdZpbCbprS == tylLijHkPE){JZEeZMuDKK = true;}
      while(BusBqsBIzV == ulFgBAqFql){AiTrJLQELa = true;}
      while(TExcYeauul == TExcYeauul){yHQWFuXrSE = true;}
      while(tylLijHkPE == tylLijHkPE){kJtqhptcqa = true;}
      if(slzFadzYZj == true){slzFadzYZj = false;}
      if(WIzXJbBKpW == true){WIzXJbBKpW = false;}
      if(sIOUSDJhRH == true){sIOUSDJhRH = false;}
      if(kQrtbhEqCt == true){kQrtbhEqCt = false;}
      if(eCVKPlyOCG == true){eCVKPlyOCG = false;}
      if(hwtsKkXemW == true){hwtsKkXemW = false;}
      if(URGRzFPEub == true){URGRzFPEub = false;}
      if(XJIurqlEEg == true){XJIurqlEEg = false;}
      if(EteKYoWzjq == true){EteKYoWzjq = false;}
      if(JZEeZMuDKK == true){JZEeZMuDKK = false;}
      if(VtTaiXnyAT == true){VtTaiXnyAT = false;}
      if(zTZGSamwsK == true){zTZGSamwsK = false;}
      if(iPUDRyFcVe == true){iPUDRyFcVe = false;}
      if(uhstKKZDbA == true){uhstKKZDbA = false;}
      if(AXyPrpzyMz == true){AXyPrpzyMz = false;}
      if(ZzKAaGYPJj == true){ZzKAaGYPJj = false;}
      if(SKcVXQZeuI == true){SKcVXQZeuI = false;}
      if(AiTrJLQELa == true){AiTrJLQELa = false;}
      if(yHQWFuXrSE == true){yHQWFuXrSE = false;}
      if(kJtqhptcqa == true){kJtqhptcqa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKWPAVZHMO
{ 
  void ZuyzekVYrL()
  { 
      bool oQkwbxYjIa = false;
      bool zJcKxgTNHR = false;
      bool rYRfImprlS = false;
      bool GZMUxeJebF = false;
      bool meOHKkMqAR = false;
      bool sgwwePzEno = false;
      bool HfxoUYwHMR = false;
      bool WnkCdMKJUW = false;
      bool ZyrTZYcPph = false;
      bool eEqmxHgYml = false;
      bool nFehtEutSR = false;
      bool FpjQOImcPu = false;
      bool ufRdlRxyFW = false;
      bool elWihUTKYU = false;
      bool dixYcoUaXo = false;
      bool TEIqpInAwc = false;
      bool HwoulSSAhs = false;
      bool ncEtRMhrBw = false;
      bool xVaPDacesZ = false;
      bool gTOwNgtClJ = false;
      string yTuqOgLdkT;
      string QHhbyeaDrN;
      string ulakyznCyz;
      string ERtTijmywm;
      string oZTolkQkiz;
      string abebYLrJrP;
      string rJekOyMNsO;
      string qcGEXUSkyM;
      string hDSzYblSuW;
      string qcGgufthan;
      string YDqUIyUaDD;
      string rGLehopfMl;
      string LtSWXOVZJr;
      string ZkKKneLyqa;
      string HLPqdkRayF;
      string oNVnbdjUxs;
      string btQKcHuApC;
      string dqokeAearl;
      string wtaDCLPWiK;
      string tpBxzMtENW;
      if(yTuqOgLdkT == YDqUIyUaDD){oQkwbxYjIa = true;}
      else if(YDqUIyUaDD == yTuqOgLdkT){nFehtEutSR = true;}
      if(QHhbyeaDrN == rGLehopfMl){zJcKxgTNHR = true;}
      else if(rGLehopfMl == QHhbyeaDrN){FpjQOImcPu = true;}
      if(ulakyznCyz == LtSWXOVZJr){rYRfImprlS = true;}
      else if(LtSWXOVZJr == ulakyznCyz){ufRdlRxyFW = true;}
      if(ERtTijmywm == ZkKKneLyqa){GZMUxeJebF = true;}
      else if(ZkKKneLyqa == ERtTijmywm){elWihUTKYU = true;}
      if(oZTolkQkiz == HLPqdkRayF){meOHKkMqAR = true;}
      else if(HLPqdkRayF == oZTolkQkiz){dixYcoUaXo = true;}
      if(abebYLrJrP == oNVnbdjUxs){sgwwePzEno = true;}
      else if(oNVnbdjUxs == abebYLrJrP){TEIqpInAwc = true;}
      if(rJekOyMNsO == btQKcHuApC){HfxoUYwHMR = true;}
      else if(btQKcHuApC == rJekOyMNsO){HwoulSSAhs = true;}
      if(qcGEXUSkyM == dqokeAearl){WnkCdMKJUW = true;}
      if(hDSzYblSuW == wtaDCLPWiK){ZyrTZYcPph = true;}
      if(qcGgufthan == tpBxzMtENW){eEqmxHgYml = true;}
      while(dqokeAearl == qcGEXUSkyM){ncEtRMhrBw = true;}
      while(wtaDCLPWiK == wtaDCLPWiK){xVaPDacesZ = true;}
      while(tpBxzMtENW == tpBxzMtENW){gTOwNgtClJ = true;}
      if(oQkwbxYjIa == true){oQkwbxYjIa = false;}
      if(zJcKxgTNHR == true){zJcKxgTNHR = false;}
      if(rYRfImprlS == true){rYRfImprlS = false;}
      if(GZMUxeJebF == true){GZMUxeJebF = false;}
      if(meOHKkMqAR == true){meOHKkMqAR = false;}
      if(sgwwePzEno == true){sgwwePzEno = false;}
      if(HfxoUYwHMR == true){HfxoUYwHMR = false;}
      if(WnkCdMKJUW == true){WnkCdMKJUW = false;}
      if(ZyrTZYcPph == true){ZyrTZYcPph = false;}
      if(eEqmxHgYml == true){eEqmxHgYml = false;}
      if(nFehtEutSR == true){nFehtEutSR = false;}
      if(FpjQOImcPu == true){FpjQOImcPu = false;}
      if(ufRdlRxyFW == true){ufRdlRxyFW = false;}
      if(elWihUTKYU == true){elWihUTKYU = false;}
      if(dixYcoUaXo == true){dixYcoUaXo = false;}
      if(TEIqpInAwc == true){TEIqpInAwc = false;}
      if(HwoulSSAhs == true){HwoulSSAhs = false;}
      if(ncEtRMhrBw == true){ncEtRMhrBw = false;}
      if(xVaPDacesZ == true){xVaPDacesZ = false;}
      if(gTOwNgtClJ == true){gTOwNgtClJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIIVFXSVSN
{ 
  void QaBgbdmDDn()
  { 
      bool EttRUJajcX = false;
      bool OoAJQMCOBG = false;
      bool QCMOHDFlpr = false;
      bool YBnXCmuMkZ = false;
      bool teaMkKwtem = false;
      bool ATMEkBgfJQ = false;
      bool DotjzNBcGd = false;
      bool RocbLlbAdx = false;
      bool HLGDrEnimA = false;
      bool GODUVFjqMX = false;
      bool JTmBUKqksy = false;
      bool ZfCMIqhqqt = false;
      bool YRpGWClHFG = false;
      bool BknGmnXFhh = false;
      bool MDpnaZMqLe = false;
      bool WszSyqcgdR = false;
      bool YielxoruYU = false;
      bool ScIJgVaBex = false;
      bool puuaiIkVHu = false;
      bool KqbQIdYEql = false;
      string zmemuWcYwf;
      string acGpLIOTpf;
      string EWbJWeuuZA;
      string hPZWfCbQpU;
      string fkOzBxLqrF;
      string yOQmacKVQQ;
      string bhyuxKCiJJ;
      string fxcUASHcHY;
      string SDDUCTzmwC;
      string rGAYsymSBq;
      string ucghYAkwmH;
      string UgNqyXedrd;
      string KPmHRZxEaC;
      string eoaQdpWUuC;
      string iDznhKrIZV;
      string SJZXfeoZQz;
      string CfUkcfGxNI;
      string AJhpuHPzYG;
      string hodFiVODjz;
      string AwDwACiOLB;
      if(zmemuWcYwf == ucghYAkwmH){EttRUJajcX = true;}
      else if(ucghYAkwmH == zmemuWcYwf){JTmBUKqksy = true;}
      if(acGpLIOTpf == UgNqyXedrd){OoAJQMCOBG = true;}
      else if(UgNqyXedrd == acGpLIOTpf){ZfCMIqhqqt = true;}
      if(EWbJWeuuZA == KPmHRZxEaC){QCMOHDFlpr = true;}
      else if(KPmHRZxEaC == EWbJWeuuZA){YRpGWClHFG = true;}
      if(hPZWfCbQpU == eoaQdpWUuC){YBnXCmuMkZ = true;}
      else if(eoaQdpWUuC == hPZWfCbQpU){BknGmnXFhh = true;}
      if(fkOzBxLqrF == iDznhKrIZV){teaMkKwtem = true;}
      else if(iDznhKrIZV == fkOzBxLqrF){MDpnaZMqLe = true;}
      if(yOQmacKVQQ == SJZXfeoZQz){ATMEkBgfJQ = true;}
      else if(SJZXfeoZQz == yOQmacKVQQ){WszSyqcgdR = true;}
      if(bhyuxKCiJJ == CfUkcfGxNI){DotjzNBcGd = true;}
      else if(CfUkcfGxNI == bhyuxKCiJJ){YielxoruYU = true;}
      if(fxcUASHcHY == AJhpuHPzYG){RocbLlbAdx = true;}
      if(SDDUCTzmwC == hodFiVODjz){HLGDrEnimA = true;}
      if(rGAYsymSBq == AwDwACiOLB){GODUVFjqMX = true;}
      while(AJhpuHPzYG == fxcUASHcHY){ScIJgVaBex = true;}
      while(hodFiVODjz == hodFiVODjz){puuaiIkVHu = true;}
      while(AwDwACiOLB == AwDwACiOLB){KqbQIdYEql = true;}
      if(EttRUJajcX == true){EttRUJajcX = false;}
      if(OoAJQMCOBG == true){OoAJQMCOBG = false;}
      if(QCMOHDFlpr == true){QCMOHDFlpr = false;}
      if(YBnXCmuMkZ == true){YBnXCmuMkZ = false;}
      if(teaMkKwtem == true){teaMkKwtem = false;}
      if(ATMEkBgfJQ == true){ATMEkBgfJQ = false;}
      if(DotjzNBcGd == true){DotjzNBcGd = false;}
      if(RocbLlbAdx == true){RocbLlbAdx = false;}
      if(HLGDrEnimA == true){HLGDrEnimA = false;}
      if(GODUVFjqMX == true){GODUVFjqMX = false;}
      if(JTmBUKqksy == true){JTmBUKqksy = false;}
      if(ZfCMIqhqqt == true){ZfCMIqhqqt = false;}
      if(YRpGWClHFG == true){YRpGWClHFG = false;}
      if(BknGmnXFhh == true){BknGmnXFhh = false;}
      if(MDpnaZMqLe == true){MDpnaZMqLe = false;}
      if(WszSyqcgdR == true){WszSyqcgdR = false;}
      if(YielxoruYU == true){YielxoruYU = false;}
      if(ScIJgVaBex == true){ScIJgVaBex = false;}
      if(puuaiIkVHu == true){puuaiIkVHu = false;}
      if(KqbQIdYEql == true){KqbQIdYEql = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQKJFKRNJQ
{ 
  void ugZGmNGNII()
  { 
      bool lORJklyWZa = false;
      bool KHxUoQVJJb = false;
      bool dCWMsOxPLg = false;
      bool EZnHqIQfYK = false;
      bool iGdLWDfAkT = false;
      bool PtopGirFPW = false;
      bool niKrVjSpdg = false;
      bool zpkysWXLop = false;
      bool iwerQKkyBH = false;
      bool QLPCVAulol = false;
      bool jpWETZIpxi = false;
      bool KgQZmrDSaL = false;
      bool zUnWQnZicr = false;
      bool blVCFrYaXq = false;
      bool BtBSwiuoOc = false;
      bool wcKdmPCAmf = false;
      bool zZNEHYKNUu = false;
      bool SctiJFTUag = false;
      bool rkTzuybrPo = false;
      bool pYmqragwLX = false;
      string HJPfYGFYMI;
      string dEiXcIpthN;
      string kIxElUydzz;
      string cUNltJMTwA;
      string TsMpVFwEoD;
      string SNpBZzLLsD;
      string HbZNfJpwdT;
      string wVxgsquHhg;
      string YtougOeMLt;
      string xBZsrrTzKM;
      string OzZUHwQIHh;
      string DEdMdNmdgQ;
      string ddjiWuwEoB;
      string XwxURZTTmj;
      string yWEcqsXMOe;
      string EoSshjOpyM;
      string ALSFKHGItE;
      string sSpwSHYHrc;
      string WipJwhcElh;
      string KdVajlDySj;
      if(HJPfYGFYMI == OzZUHwQIHh){lORJklyWZa = true;}
      else if(OzZUHwQIHh == HJPfYGFYMI){jpWETZIpxi = true;}
      if(dEiXcIpthN == DEdMdNmdgQ){KHxUoQVJJb = true;}
      else if(DEdMdNmdgQ == dEiXcIpthN){KgQZmrDSaL = true;}
      if(kIxElUydzz == ddjiWuwEoB){dCWMsOxPLg = true;}
      else if(ddjiWuwEoB == kIxElUydzz){zUnWQnZicr = true;}
      if(cUNltJMTwA == XwxURZTTmj){EZnHqIQfYK = true;}
      else if(XwxURZTTmj == cUNltJMTwA){blVCFrYaXq = true;}
      if(TsMpVFwEoD == yWEcqsXMOe){iGdLWDfAkT = true;}
      else if(yWEcqsXMOe == TsMpVFwEoD){BtBSwiuoOc = true;}
      if(SNpBZzLLsD == EoSshjOpyM){PtopGirFPW = true;}
      else if(EoSshjOpyM == SNpBZzLLsD){wcKdmPCAmf = true;}
      if(HbZNfJpwdT == ALSFKHGItE){niKrVjSpdg = true;}
      else if(ALSFKHGItE == HbZNfJpwdT){zZNEHYKNUu = true;}
      if(wVxgsquHhg == sSpwSHYHrc){zpkysWXLop = true;}
      if(YtougOeMLt == WipJwhcElh){iwerQKkyBH = true;}
      if(xBZsrrTzKM == KdVajlDySj){QLPCVAulol = true;}
      while(sSpwSHYHrc == wVxgsquHhg){SctiJFTUag = true;}
      while(WipJwhcElh == WipJwhcElh){rkTzuybrPo = true;}
      while(KdVajlDySj == KdVajlDySj){pYmqragwLX = true;}
      if(lORJklyWZa == true){lORJklyWZa = false;}
      if(KHxUoQVJJb == true){KHxUoQVJJb = false;}
      if(dCWMsOxPLg == true){dCWMsOxPLg = false;}
      if(EZnHqIQfYK == true){EZnHqIQfYK = false;}
      if(iGdLWDfAkT == true){iGdLWDfAkT = false;}
      if(PtopGirFPW == true){PtopGirFPW = false;}
      if(niKrVjSpdg == true){niKrVjSpdg = false;}
      if(zpkysWXLop == true){zpkysWXLop = false;}
      if(iwerQKkyBH == true){iwerQKkyBH = false;}
      if(QLPCVAulol == true){QLPCVAulol = false;}
      if(jpWETZIpxi == true){jpWETZIpxi = false;}
      if(KgQZmrDSaL == true){KgQZmrDSaL = false;}
      if(zUnWQnZicr == true){zUnWQnZicr = false;}
      if(blVCFrYaXq == true){blVCFrYaXq = false;}
      if(BtBSwiuoOc == true){BtBSwiuoOc = false;}
      if(wcKdmPCAmf == true){wcKdmPCAmf = false;}
      if(zZNEHYKNUu == true){zZNEHYKNUu = false;}
      if(SctiJFTUag == true){SctiJFTUag = false;}
      if(rkTzuybrPo == true){rkTzuybrPo = false;}
      if(pYmqragwLX == true){pYmqragwLX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQBGOJKFSR
{ 
  void FeGszqPPIw()
  { 
      bool iMzWRcMwMu = false;
      bool GaGRMthdRL = false;
      bool CXoyIhMUKh = false;
      bool BdmntzJJuT = false;
      bool rAnxztzAfi = false;
      bool ceDOWLXBOi = false;
      bool QqldscnRXM = false;
      bool kYhxTCiqzO = false;
      bool iLoaEWZYRi = false;
      bool bIuMDAOKDW = false;
      bool GhcTyEwGtU = false;
      bool bfBzAECKZW = false;
      bool DOznkcdVtS = false;
      bool nYncHBiVbA = false;
      bool ZTdwGuGuLy = false;
      bool yDjgSqhnhV = false;
      bool ZZLbfDrYqy = false;
      bool VfhZwjkDho = false;
      bool ViJuTjnHJQ = false;
      bool TtmGZAHBQD = false;
      string lPtCZntjbf;
      string mSLVfsgyIz;
      string UQACgkoEHF;
      string oOeTaEOtcT;
      string ricRodiFIJ;
      string FRBagUPqVn;
      string yocWqYmqua;
      string dmVnHknhND;
      string BjuxAWNDmG;
      string oXXnUCFGaQ;
      string prJgfSwMTw;
      string ggdSmOtfVT;
      string LiEnlGOgTF;
      string egHxMJaORh;
      string ZAjqZIsFBG;
      string IZjGFGnUuY;
      string DOrOQzYgFd;
      string neNnsKzMOc;
      string MJfNwEwBrG;
      string UFSrdLIVZZ;
      if(lPtCZntjbf == prJgfSwMTw){iMzWRcMwMu = true;}
      else if(prJgfSwMTw == lPtCZntjbf){GhcTyEwGtU = true;}
      if(mSLVfsgyIz == ggdSmOtfVT){GaGRMthdRL = true;}
      else if(ggdSmOtfVT == mSLVfsgyIz){bfBzAECKZW = true;}
      if(UQACgkoEHF == LiEnlGOgTF){CXoyIhMUKh = true;}
      else if(LiEnlGOgTF == UQACgkoEHF){DOznkcdVtS = true;}
      if(oOeTaEOtcT == egHxMJaORh){BdmntzJJuT = true;}
      else if(egHxMJaORh == oOeTaEOtcT){nYncHBiVbA = true;}
      if(ricRodiFIJ == ZAjqZIsFBG){rAnxztzAfi = true;}
      else if(ZAjqZIsFBG == ricRodiFIJ){ZTdwGuGuLy = true;}
      if(FRBagUPqVn == IZjGFGnUuY){ceDOWLXBOi = true;}
      else if(IZjGFGnUuY == FRBagUPqVn){yDjgSqhnhV = true;}
      if(yocWqYmqua == DOrOQzYgFd){QqldscnRXM = true;}
      else if(DOrOQzYgFd == yocWqYmqua){ZZLbfDrYqy = true;}
      if(dmVnHknhND == neNnsKzMOc){kYhxTCiqzO = true;}
      if(BjuxAWNDmG == MJfNwEwBrG){iLoaEWZYRi = true;}
      if(oXXnUCFGaQ == UFSrdLIVZZ){bIuMDAOKDW = true;}
      while(neNnsKzMOc == dmVnHknhND){VfhZwjkDho = true;}
      while(MJfNwEwBrG == MJfNwEwBrG){ViJuTjnHJQ = true;}
      while(UFSrdLIVZZ == UFSrdLIVZZ){TtmGZAHBQD = true;}
      if(iMzWRcMwMu == true){iMzWRcMwMu = false;}
      if(GaGRMthdRL == true){GaGRMthdRL = false;}
      if(CXoyIhMUKh == true){CXoyIhMUKh = false;}
      if(BdmntzJJuT == true){BdmntzJJuT = false;}
      if(rAnxztzAfi == true){rAnxztzAfi = false;}
      if(ceDOWLXBOi == true){ceDOWLXBOi = false;}
      if(QqldscnRXM == true){QqldscnRXM = false;}
      if(kYhxTCiqzO == true){kYhxTCiqzO = false;}
      if(iLoaEWZYRi == true){iLoaEWZYRi = false;}
      if(bIuMDAOKDW == true){bIuMDAOKDW = false;}
      if(GhcTyEwGtU == true){GhcTyEwGtU = false;}
      if(bfBzAECKZW == true){bfBzAECKZW = false;}
      if(DOznkcdVtS == true){DOznkcdVtS = false;}
      if(nYncHBiVbA == true){nYncHBiVbA = false;}
      if(ZTdwGuGuLy == true){ZTdwGuGuLy = false;}
      if(yDjgSqhnhV == true){yDjgSqhnhV = false;}
      if(ZZLbfDrYqy == true){ZZLbfDrYqy = false;}
      if(VfhZwjkDho == true){VfhZwjkDho = false;}
      if(ViJuTjnHJQ == true){ViJuTjnHJQ = false;}
      if(TtmGZAHBQD == true){TtmGZAHBQD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMPRMPLWPW
{ 
  void ZnMNzmqHgs()
  { 
      bool WcZOLhHdER = false;
      bool DctAidORwU = false;
      bool KizEEBHosf = false;
      bool fmhhQgPKSw = false;
      bool zZpOobSZwK = false;
      bool fqoVhncUKJ = false;
      bool aSjXlQtLiB = false;
      bool NDzAUkskOb = false;
      bool igrhAnxLAc = false;
      bool EtAIVgoRcY = false;
      bool gGquwbroAx = false;
      bool uqFhasZCXx = false;
      bool TiKFxSDqen = false;
      bool uaHpubpxlX = false;
      bool wHKDgMoRhb = false;
      bool HmsfFxukyc = false;
      bool YAKMBTiPmy = false;
      bool DcPzALXHXj = false;
      bool dkJCfHhbkx = false;
      bool fEyIzwxxBN = false;
      string zDPfjGAaEb;
      string jeWLKtDmkF;
      string GAlAYTTMwZ;
      string thJymTtzCJ;
      string zAhWGlSeUL;
      string kXbaSyQPHP;
      string lndegCVYYq;
      string zEkaFFSOsm;
      string AorkoWGhfn;
      string CeqmWLVCpE;
      string QtGcMfmAUM;
      string eCVTOxwspK;
      string wmrjoTMxEt;
      string jPYoWGiOXI;
      string jFNTIAJWXZ;
      string PcLeIcBVnr;
      string TowabPcgxI;
      string OgUhapZYbn;
      string JoZddHEtgs;
      string EMZfotJlqs;
      if(zDPfjGAaEb == QtGcMfmAUM){WcZOLhHdER = true;}
      else if(QtGcMfmAUM == zDPfjGAaEb){gGquwbroAx = true;}
      if(jeWLKtDmkF == eCVTOxwspK){DctAidORwU = true;}
      else if(eCVTOxwspK == jeWLKtDmkF){uqFhasZCXx = true;}
      if(GAlAYTTMwZ == wmrjoTMxEt){KizEEBHosf = true;}
      else if(wmrjoTMxEt == GAlAYTTMwZ){TiKFxSDqen = true;}
      if(thJymTtzCJ == jPYoWGiOXI){fmhhQgPKSw = true;}
      else if(jPYoWGiOXI == thJymTtzCJ){uaHpubpxlX = true;}
      if(zAhWGlSeUL == jFNTIAJWXZ){zZpOobSZwK = true;}
      else if(jFNTIAJWXZ == zAhWGlSeUL){wHKDgMoRhb = true;}
      if(kXbaSyQPHP == PcLeIcBVnr){fqoVhncUKJ = true;}
      else if(PcLeIcBVnr == kXbaSyQPHP){HmsfFxukyc = true;}
      if(lndegCVYYq == TowabPcgxI){aSjXlQtLiB = true;}
      else if(TowabPcgxI == lndegCVYYq){YAKMBTiPmy = true;}
      if(zEkaFFSOsm == OgUhapZYbn){NDzAUkskOb = true;}
      if(AorkoWGhfn == JoZddHEtgs){igrhAnxLAc = true;}
      if(CeqmWLVCpE == EMZfotJlqs){EtAIVgoRcY = true;}
      while(OgUhapZYbn == zEkaFFSOsm){DcPzALXHXj = true;}
      while(JoZddHEtgs == JoZddHEtgs){dkJCfHhbkx = true;}
      while(EMZfotJlqs == EMZfotJlqs){fEyIzwxxBN = true;}
      if(WcZOLhHdER == true){WcZOLhHdER = false;}
      if(DctAidORwU == true){DctAidORwU = false;}
      if(KizEEBHosf == true){KizEEBHosf = false;}
      if(fmhhQgPKSw == true){fmhhQgPKSw = false;}
      if(zZpOobSZwK == true){zZpOobSZwK = false;}
      if(fqoVhncUKJ == true){fqoVhncUKJ = false;}
      if(aSjXlQtLiB == true){aSjXlQtLiB = false;}
      if(NDzAUkskOb == true){NDzAUkskOb = false;}
      if(igrhAnxLAc == true){igrhAnxLAc = false;}
      if(EtAIVgoRcY == true){EtAIVgoRcY = false;}
      if(gGquwbroAx == true){gGquwbroAx = false;}
      if(uqFhasZCXx == true){uqFhasZCXx = false;}
      if(TiKFxSDqen == true){TiKFxSDqen = false;}
      if(uaHpubpxlX == true){uaHpubpxlX = false;}
      if(wHKDgMoRhb == true){wHKDgMoRhb = false;}
      if(HmsfFxukyc == true){HmsfFxukyc = false;}
      if(YAKMBTiPmy == true){YAKMBTiPmy = false;}
      if(DcPzALXHXj == true){DcPzALXHXj = false;}
      if(dkJCfHhbkx == true){dkJCfHhbkx = false;}
      if(fEyIzwxxBN == true){fEyIzwxxBN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYYSHZGIFP
{ 
  void CcTWzIsLRz()
  { 
      bool VdHabFjNxI = false;
      bool aWmjbkZGrU = false;
      bool KPobcZyxxx = false;
      bool FFmeYPjbBY = false;
      bool lfXtzokMTp = false;
      bool YZkhAFnexC = false;
      bool GmQACVjILL = false;
      bool AyFSidrucn = false;
      bool olcGXfUFdS = false;
      bool aEezRyPXqd = false;
      bool FcAIoaTRyV = false;
      bool NsCINUKJbV = false;
      bool AedrjwTFBj = false;
      bool OUDyiLkTQx = false;
      bool LCGIEhCVkx = false;
      bool nGuUcazHXs = false;
      bool GNPNHsoEZB = false;
      bool ipreJxXVnB = false;
      bool txUDwHYhUI = false;
      bool McuXpxmrAK = false;
      string IsyKMUYliM;
      string lekrHgNCrx;
      string saFIxghxWT;
      string OazQiwCLHN;
      string xEeTKWOtqR;
      string hpTAfgmoNe;
      string mbPPyLfTIK;
      string eBueznwkya;
      string SmGElXGzkB;
      string JNycaVnPUz;
      string pukfmguoAq;
      string kBpmMAUKdZ;
      string EgiHBQDSEd;
      string AfQyjXCZRF;
      string cRysQHWKPZ;
      string AdluuJLddV;
      string cckVqEkrDo;
      string ytsYxmhopt;
      string trCddVtVCa;
      string LXwwbzgcCL;
      if(IsyKMUYliM == pukfmguoAq){VdHabFjNxI = true;}
      else if(pukfmguoAq == IsyKMUYliM){FcAIoaTRyV = true;}
      if(lekrHgNCrx == kBpmMAUKdZ){aWmjbkZGrU = true;}
      else if(kBpmMAUKdZ == lekrHgNCrx){NsCINUKJbV = true;}
      if(saFIxghxWT == EgiHBQDSEd){KPobcZyxxx = true;}
      else if(EgiHBQDSEd == saFIxghxWT){AedrjwTFBj = true;}
      if(OazQiwCLHN == AfQyjXCZRF){FFmeYPjbBY = true;}
      else if(AfQyjXCZRF == OazQiwCLHN){OUDyiLkTQx = true;}
      if(xEeTKWOtqR == cRysQHWKPZ){lfXtzokMTp = true;}
      else if(cRysQHWKPZ == xEeTKWOtqR){LCGIEhCVkx = true;}
      if(hpTAfgmoNe == AdluuJLddV){YZkhAFnexC = true;}
      else if(AdluuJLddV == hpTAfgmoNe){nGuUcazHXs = true;}
      if(mbPPyLfTIK == cckVqEkrDo){GmQACVjILL = true;}
      else if(cckVqEkrDo == mbPPyLfTIK){GNPNHsoEZB = true;}
      if(eBueznwkya == ytsYxmhopt){AyFSidrucn = true;}
      if(SmGElXGzkB == trCddVtVCa){olcGXfUFdS = true;}
      if(JNycaVnPUz == LXwwbzgcCL){aEezRyPXqd = true;}
      while(ytsYxmhopt == eBueznwkya){ipreJxXVnB = true;}
      while(trCddVtVCa == trCddVtVCa){txUDwHYhUI = true;}
      while(LXwwbzgcCL == LXwwbzgcCL){McuXpxmrAK = true;}
      if(VdHabFjNxI == true){VdHabFjNxI = false;}
      if(aWmjbkZGrU == true){aWmjbkZGrU = false;}
      if(KPobcZyxxx == true){KPobcZyxxx = false;}
      if(FFmeYPjbBY == true){FFmeYPjbBY = false;}
      if(lfXtzokMTp == true){lfXtzokMTp = false;}
      if(YZkhAFnexC == true){YZkhAFnexC = false;}
      if(GmQACVjILL == true){GmQACVjILL = false;}
      if(AyFSidrucn == true){AyFSidrucn = false;}
      if(olcGXfUFdS == true){olcGXfUFdS = false;}
      if(aEezRyPXqd == true){aEezRyPXqd = false;}
      if(FcAIoaTRyV == true){FcAIoaTRyV = false;}
      if(NsCINUKJbV == true){NsCINUKJbV = false;}
      if(AedrjwTFBj == true){AedrjwTFBj = false;}
      if(OUDyiLkTQx == true){OUDyiLkTQx = false;}
      if(LCGIEhCVkx == true){LCGIEhCVkx = false;}
      if(nGuUcazHXs == true){nGuUcazHXs = false;}
      if(GNPNHsoEZB == true){GNPNHsoEZB = false;}
      if(ipreJxXVnB == true){ipreJxXVnB = false;}
      if(txUDwHYhUI == true){txUDwHYhUI = false;}
      if(McuXpxmrAK == true){McuXpxmrAK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQWXTPZCFL
{ 
  void xghXzKcbsj()
  { 
      bool AkrXHYEMfE = false;
      bool xiHrQncMAl = false;
      bool fedJxHCUwt = false;
      bool JSwfsPoQDR = false;
      bool TcrIRfoslS = false;
      bool gZxtsVGhaz = false;
      bool VjPkuembzB = false;
      bool zLJhRDmUrQ = false;
      bool SJidNiUBmX = false;
      bool IGpEwiMHNm = false;
      bool sNtkSVQPbo = false;
      bool hlpJgLBlWL = false;
      bool JknarrVFlh = false;
      bool pfHFWEOxKr = false;
      bool SFZxoWQfWj = false;
      bool hajCcIYSsa = false;
      bool AKcszCejmb = false;
      bool xDaerEKqkU = false;
      bool bohBAPwEcO = false;
      bool fuEjrIbfxl = false;
      string CXbxyuYmKG;
      string SwJWHbcMMa;
      string HZoxCFJDah;
      string GCHnzxOMPN;
      string wiYPYHAltJ;
      string jnuYkbieur;
      string lVLczPnVXK;
      string NPwzdYAYXu;
      string FXIRxSHiCW;
      string NiRWaaWuQJ;
      string SdNjwUqwtM;
      string aKGAmONtff;
      string HFSAxdyYXD;
      string BFHObaJYVc;
      string bLnpuDcQjM;
      string NcPjBNLMlR;
      string VRXpKVCqXM;
      string EoXDEwQbFt;
      string BgoKpYoXNO;
      string PwlDGJmyfY;
      if(CXbxyuYmKG == SdNjwUqwtM){AkrXHYEMfE = true;}
      else if(SdNjwUqwtM == CXbxyuYmKG){sNtkSVQPbo = true;}
      if(SwJWHbcMMa == aKGAmONtff){xiHrQncMAl = true;}
      else if(aKGAmONtff == SwJWHbcMMa){hlpJgLBlWL = true;}
      if(HZoxCFJDah == HFSAxdyYXD){fedJxHCUwt = true;}
      else if(HFSAxdyYXD == HZoxCFJDah){JknarrVFlh = true;}
      if(GCHnzxOMPN == BFHObaJYVc){JSwfsPoQDR = true;}
      else if(BFHObaJYVc == GCHnzxOMPN){pfHFWEOxKr = true;}
      if(wiYPYHAltJ == bLnpuDcQjM){TcrIRfoslS = true;}
      else if(bLnpuDcQjM == wiYPYHAltJ){SFZxoWQfWj = true;}
      if(jnuYkbieur == NcPjBNLMlR){gZxtsVGhaz = true;}
      else if(NcPjBNLMlR == jnuYkbieur){hajCcIYSsa = true;}
      if(lVLczPnVXK == VRXpKVCqXM){VjPkuembzB = true;}
      else if(VRXpKVCqXM == lVLczPnVXK){AKcszCejmb = true;}
      if(NPwzdYAYXu == EoXDEwQbFt){zLJhRDmUrQ = true;}
      if(FXIRxSHiCW == BgoKpYoXNO){SJidNiUBmX = true;}
      if(NiRWaaWuQJ == PwlDGJmyfY){IGpEwiMHNm = true;}
      while(EoXDEwQbFt == NPwzdYAYXu){xDaerEKqkU = true;}
      while(BgoKpYoXNO == BgoKpYoXNO){bohBAPwEcO = true;}
      while(PwlDGJmyfY == PwlDGJmyfY){fuEjrIbfxl = true;}
      if(AkrXHYEMfE == true){AkrXHYEMfE = false;}
      if(xiHrQncMAl == true){xiHrQncMAl = false;}
      if(fedJxHCUwt == true){fedJxHCUwt = false;}
      if(JSwfsPoQDR == true){JSwfsPoQDR = false;}
      if(TcrIRfoslS == true){TcrIRfoslS = false;}
      if(gZxtsVGhaz == true){gZxtsVGhaz = false;}
      if(VjPkuembzB == true){VjPkuembzB = false;}
      if(zLJhRDmUrQ == true){zLJhRDmUrQ = false;}
      if(SJidNiUBmX == true){SJidNiUBmX = false;}
      if(IGpEwiMHNm == true){IGpEwiMHNm = false;}
      if(sNtkSVQPbo == true){sNtkSVQPbo = false;}
      if(hlpJgLBlWL == true){hlpJgLBlWL = false;}
      if(JknarrVFlh == true){JknarrVFlh = false;}
      if(pfHFWEOxKr == true){pfHFWEOxKr = false;}
      if(SFZxoWQfWj == true){SFZxoWQfWj = false;}
      if(hajCcIYSsa == true){hajCcIYSsa = false;}
      if(AKcszCejmb == true){AKcszCejmb = false;}
      if(xDaerEKqkU == true){xDaerEKqkU = false;}
      if(bohBAPwEcO == true){bohBAPwEcO = false;}
      if(fuEjrIbfxl == true){fuEjrIbfxl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYJZVSYCIP
{ 
  void YMLQbuVXHg()
  { 
      bool aYfrFcxpry = false;
      bool VMeozSbKyg = false;
      bool OqILixIbEa = false;
      bool zxYSuEFbMS = false;
      bool DrTDnRXWuD = false;
      bool kjCgNiPUJH = false;
      bool TVkRyYnMtu = false;
      bool MzyfcWXEWQ = false;
      bool YkgBpPtrFL = false;
      bool nkSEyhGCFP = false;
      bool dLcAqklWDq = false;
      bool LLxsihnjai = false;
      bool dwGhGagsgt = false;
      bool PUzHmMIfJF = false;
      bool cXnOAcnYVP = false;
      bool sVaWkgFttP = false;
      bool DsoIapLpGW = false;
      bool ZIZVFGHrhc = false;
      bool mIXRAstcVF = false;
      bool HOltBjhfmJ = false;
      string cJallTHYdR;
      string ilmfdGucEI;
      string XLmNogNcLG;
      string ioIBnzDBDr;
      string WgqNGsUmqu;
      string lzNYxRWMxE;
      string GeNWhtdlqd;
      string DsZLkqTYHu;
      string MZkQUjaiDW;
      string cpEylrSTeL;
      string PhuMqsYCmG;
      string xxFBrfsxCy;
      string StiUBNnbYs;
      string XAsufdeXYa;
      string KYuwYejCGG;
      string yVRgsUzaLc;
      string ExctixEKVN;
      string BUXantzluV;
      string dlUSuBhMCK;
      string eDMuVMuBNb;
      if(cJallTHYdR == PhuMqsYCmG){aYfrFcxpry = true;}
      else if(PhuMqsYCmG == cJallTHYdR){dLcAqklWDq = true;}
      if(ilmfdGucEI == xxFBrfsxCy){VMeozSbKyg = true;}
      else if(xxFBrfsxCy == ilmfdGucEI){LLxsihnjai = true;}
      if(XLmNogNcLG == StiUBNnbYs){OqILixIbEa = true;}
      else if(StiUBNnbYs == XLmNogNcLG){dwGhGagsgt = true;}
      if(ioIBnzDBDr == XAsufdeXYa){zxYSuEFbMS = true;}
      else if(XAsufdeXYa == ioIBnzDBDr){PUzHmMIfJF = true;}
      if(WgqNGsUmqu == KYuwYejCGG){DrTDnRXWuD = true;}
      else if(KYuwYejCGG == WgqNGsUmqu){cXnOAcnYVP = true;}
      if(lzNYxRWMxE == yVRgsUzaLc){kjCgNiPUJH = true;}
      else if(yVRgsUzaLc == lzNYxRWMxE){sVaWkgFttP = true;}
      if(GeNWhtdlqd == ExctixEKVN){TVkRyYnMtu = true;}
      else if(ExctixEKVN == GeNWhtdlqd){DsoIapLpGW = true;}
      if(DsZLkqTYHu == BUXantzluV){MzyfcWXEWQ = true;}
      if(MZkQUjaiDW == dlUSuBhMCK){YkgBpPtrFL = true;}
      if(cpEylrSTeL == eDMuVMuBNb){nkSEyhGCFP = true;}
      while(BUXantzluV == DsZLkqTYHu){ZIZVFGHrhc = true;}
      while(dlUSuBhMCK == dlUSuBhMCK){mIXRAstcVF = true;}
      while(eDMuVMuBNb == eDMuVMuBNb){HOltBjhfmJ = true;}
      if(aYfrFcxpry == true){aYfrFcxpry = false;}
      if(VMeozSbKyg == true){VMeozSbKyg = false;}
      if(OqILixIbEa == true){OqILixIbEa = false;}
      if(zxYSuEFbMS == true){zxYSuEFbMS = false;}
      if(DrTDnRXWuD == true){DrTDnRXWuD = false;}
      if(kjCgNiPUJH == true){kjCgNiPUJH = false;}
      if(TVkRyYnMtu == true){TVkRyYnMtu = false;}
      if(MzyfcWXEWQ == true){MzyfcWXEWQ = false;}
      if(YkgBpPtrFL == true){YkgBpPtrFL = false;}
      if(nkSEyhGCFP == true){nkSEyhGCFP = false;}
      if(dLcAqklWDq == true){dLcAqklWDq = false;}
      if(LLxsihnjai == true){LLxsihnjai = false;}
      if(dwGhGagsgt == true){dwGhGagsgt = false;}
      if(PUzHmMIfJF == true){PUzHmMIfJF = false;}
      if(cXnOAcnYVP == true){cXnOAcnYVP = false;}
      if(sVaWkgFttP == true){sVaWkgFttP = false;}
      if(DsoIapLpGW == true){DsoIapLpGW = false;}
      if(ZIZVFGHrhc == true){ZIZVFGHrhc = false;}
      if(mIXRAstcVF == true){mIXRAstcVF = false;}
      if(HOltBjhfmJ == true){HOltBjhfmJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEJXAYTZGD
{ 
  void AGANPGjmBX()
  { 
      bool WlLZKtjjOo = false;
      bool npVlNDdZgj = false;
      bool mLmUNPwInY = false;
      bool RlhoRRDVYz = false;
      bool qlCYVqroiT = false;
      bool pZZpcLypLu = false;
      bool ybuoWBHfTw = false;
      bool AIBhsAJOyW = false;
      bool WGYThrLrLG = false;
      bool SNJdAPpMBT = false;
      bool iLVlThXrwb = false;
      bool BjqoXqCbHd = false;
      bool pPTMdmyWgd = false;
      bool JwMdmLjmAz = false;
      bool TTwjEhWUGJ = false;
      bool MOFWdTqJIf = false;
      bool jBKSSFXMBL = false;
      bool HPaHKVSjIu = false;
      bool QdQXQtqoAT = false;
      bool UadTPSIdQz = false;
      string bNdhhnXRaP;
      string RPXWShFNrs;
      string UipEJecccI;
      string pzQOrZhlAP;
      string mwRUBIDiJH;
      string rEIsArWYXC;
      string KtnSYSzJdr;
      string zTNbFXQUDA;
      string asTVPkpWOA;
      string CINxEsHzwi;
      string JtEQHYqgnb;
      string aCVWbRaSDn;
      string bbudppFQWM;
      string PRYUqgnCNq;
      string tJilYAmqUm;
      string SowHGgzaaQ;
      string SZJaLIcBeu;
      string cXELsRsIFo;
      string DOuitaVQNK;
      string gNbwXUzHZP;
      if(bNdhhnXRaP == JtEQHYqgnb){WlLZKtjjOo = true;}
      else if(JtEQHYqgnb == bNdhhnXRaP){iLVlThXrwb = true;}
      if(RPXWShFNrs == aCVWbRaSDn){npVlNDdZgj = true;}
      else if(aCVWbRaSDn == RPXWShFNrs){BjqoXqCbHd = true;}
      if(UipEJecccI == bbudppFQWM){mLmUNPwInY = true;}
      else if(bbudppFQWM == UipEJecccI){pPTMdmyWgd = true;}
      if(pzQOrZhlAP == PRYUqgnCNq){RlhoRRDVYz = true;}
      else if(PRYUqgnCNq == pzQOrZhlAP){JwMdmLjmAz = true;}
      if(mwRUBIDiJH == tJilYAmqUm){qlCYVqroiT = true;}
      else if(tJilYAmqUm == mwRUBIDiJH){TTwjEhWUGJ = true;}
      if(rEIsArWYXC == SowHGgzaaQ){pZZpcLypLu = true;}
      else if(SowHGgzaaQ == rEIsArWYXC){MOFWdTqJIf = true;}
      if(KtnSYSzJdr == SZJaLIcBeu){ybuoWBHfTw = true;}
      else if(SZJaLIcBeu == KtnSYSzJdr){jBKSSFXMBL = true;}
      if(zTNbFXQUDA == cXELsRsIFo){AIBhsAJOyW = true;}
      if(asTVPkpWOA == DOuitaVQNK){WGYThrLrLG = true;}
      if(CINxEsHzwi == gNbwXUzHZP){SNJdAPpMBT = true;}
      while(cXELsRsIFo == zTNbFXQUDA){HPaHKVSjIu = true;}
      while(DOuitaVQNK == DOuitaVQNK){QdQXQtqoAT = true;}
      while(gNbwXUzHZP == gNbwXUzHZP){UadTPSIdQz = true;}
      if(WlLZKtjjOo == true){WlLZKtjjOo = false;}
      if(npVlNDdZgj == true){npVlNDdZgj = false;}
      if(mLmUNPwInY == true){mLmUNPwInY = false;}
      if(RlhoRRDVYz == true){RlhoRRDVYz = false;}
      if(qlCYVqroiT == true){qlCYVqroiT = false;}
      if(pZZpcLypLu == true){pZZpcLypLu = false;}
      if(ybuoWBHfTw == true){ybuoWBHfTw = false;}
      if(AIBhsAJOyW == true){AIBhsAJOyW = false;}
      if(WGYThrLrLG == true){WGYThrLrLG = false;}
      if(SNJdAPpMBT == true){SNJdAPpMBT = false;}
      if(iLVlThXrwb == true){iLVlThXrwb = false;}
      if(BjqoXqCbHd == true){BjqoXqCbHd = false;}
      if(pPTMdmyWgd == true){pPTMdmyWgd = false;}
      if(JwMdmLjmAz == true){JwMdmLjmAz = false;}
      if(TTwjEhWUGJ == true){TTwjEhWUGJ = false;}
      if(MOFWdTqJIf == true){MOFWdTqJIf = false;}
      if(jBKSSFXMBL == true){jBKSSFXMBL = false;}
      if(HPaHKVSjIu == true){HPaHKVSjIu = false;}
      if(QdQXQtqoAT == true){QdQXQtqoAT = false;}
      if(UadTPSIdQz == true){UadTPSIdQz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFARNPFGHI
{ 
  void uksbuHHgDB()
  { 
      bool DVTNjegIbe = false;
      bool dfzmmPKmkR = false;
      bool VmQMgQkBgR = false;
      bool boiflnyPrW = false;
      bool dpRFKDSgPd = false;
      bool rpbNaQEHfS = false;
      bool seaJCnxSBz = false;
      bool RuuOmfVLCd = false;
      bool yEkDYlMUFV = false;
      bool ipiZdyOHCV = false;
      bool GAeQMxtNat = false;
      bool urFCUntXkP = false;
      bool bbMfPaLVkn = false;
      bool RNIfXxZUqa = false;
      bool qzsLZqkgEo = false;
      bool EqWmtdmzAk = false;
      bool lYcmbgiYeW = false;
      bool OYfJYbhBFY = false;
      bool pdQuiaqVls = false;
      bool KZTFnSWGis = false;
      string gpdyGJnNwb;
      string THEMJyuwsU;
      string NHSzWRKifw;
      string WNbyudXRNy;
      string sYlQrQWphD;
      string zfHBPYXdbo;
      string zEhzEGeFRf;
      string adhuanUBHG;
      string tTAcxpFaiV;
      string FtpYznqmLl;
      string kQYCcVxLZa;
      string DVWVteDECO;
      string AEWuZfmIwl;
      string xhpVUcuxzb;
      string rtBIRjWUeT;
      string kljxkgtccw;
      string hoPmcUfBAQ;
      string jFEaVGDOcp;
      string JSdbBLysjn;
      string iSTDsDdNex;
      if(gpdyGJnNwb == kQYCcVxLZa){DVTNjegIbe = true;}
      else if(kQYCcVxLZa == gpdyGJnNwb){GAeQMxtNat = true;}
      if(THEMJyuwsU == DVWVteDECO){dfzmmPKmkR = true;}
      else if(DVWVteDECO == THEMJyuwsU){urFCUntXkP = true;}
      if(NHSzWRKifw == AEWuZfmIwl){VmQMgQkBgR = true;}
      else if(AEWuZfmIwl == NHSzWRKifw){bbMfPaLVkn = true;}
      if(WNbyudXRNy == xhpVUcuxzb){boiflnyPrW = true;}
      else if(xhpVUcuxzb == WNbyudXRNy){RNIfXxZUqa = true;}
      if(sYlQrQWphD == rtBIRjWUeT){dpRFKDSgPd = true;}
      else if(rtBIRjWUeT == sYlQrQWphD){qzsLZqkgEo = true;}
      if(zfHBPYXdbo == kljxkgtccw){rpbNaQEHfS = true;}
      else if(kljxkgtccw == zfHBPYXdbo){EqWmtdmzAk = true;}
      if(zEhzEGeFRf == hoPmcUfBAQ){seaJCnxSBz = true;}
      else if(hoPmcUfBAQ == zEhzEGeFRf){lYcmbgiYeW = true;}
      if(adhuanUBHG == jFEaVGDOcp){RuuOmfVLCd = true;}
      if(tTAcxpFaiV == JSdbBLysjn){yEkDYlMUFV = true;}
      if(FtpYznqmLl == iSTDsDdNex){ipiZdyOHCV = true;}
      while(jFEaVGDOcp == adhuanUBHG){OYfJYbhBFY = true;}
      while(JSdbBLysjn == JSdbBLysjn){pdQuiaqVls = true;}
      while(iSTDsDdNex == iSTDsDdNex){KZTFnSWGis = true;}
      if(DVTNjegIbe == true){DVTNjegIbe = false;}
      if(dfzmmPKmkR == true){dfzmmPKmkR = false;}
      if(VmQMgQkBgR == true){VmQMgQkBgR = false;}
      if(boiflnyPrW == true){boiflnyPrW = false;}
      if(dpRFKDSgPd == true){dpRFKDSgPd = false;}
      if(rpbNaQEHfS == true){rpbNaQEHfS = false;}
      if(seaJCnxSBz == true){seaJCnxSBz = false;}
      if(RuuOmfVLCd == true){RuuOmfVLCd = false;}
      if(yEkDYlMUFV == true){yEkDYlMUFV = false;}
      if(ipiZdyOHCV == true){ipiZdyOHCV = false;}
      if(GAeQMxtNat == true){GAeQMxtNat = false;}
      if(urFCUntXkP == true){urFCUntXkP = false;}
      if(bbMfPaLVkn == true){bbMfPaLVkn = false;}
      if(RNIfXxZUqa == true){RNIfXxZUqa = false;}
      if(qzsLZqkgEo == true){qzsLZqkgEo = false;}
      if(EqWmtdmzAk == true){EqWmtdmzAk = false;}
      if(lYcmbgiYeW == true){lYcmbgiYeW = false;}
      if(OYfJYbhBFY == true){OYfJYbhBFY = false;}
      if(pdQuiaqVls == true){pdQuiaqVls = false;}
      if(KZTFnSWGis == true){KZTFnSWGis = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHUDKTXLPH
{ 
  void cROebDIgXe()
  { 
      bool yCbnfDsRwD = false;
      bool UmWwXcghiZ = false;
      bool cxqoHQMTsD = false;
      bool KkdougNycb = false;
      bool oYUwWLPEHO = false;
      bool qreteALlgO = false;
      bool qZXrsjJhAp = false;
      bool PiEGjDctRw = false;
      bool BHMeMRGjJt = false;
      bool VaQOkPBbDm = false;
      bool CgEQzHnXJb = false;
      bool XRUkNiMsfb = false;
      bool cYYGUnRpVU = false;
      bool CApdtTDweE = false;
      bool diZhWEFfBB = false;
      bool CIwbJcIxuK = false;
      bool oxBoYWapps = false;
      bool fQNaytzpiQ = false;
      bool hkoTRtDNTR = false;
      bool LFATPfgkIz = false;
      string UfxNqZxiNg;
      string cVCNcuDtoZ;
      string FNrhNCNGTq;
      string QWKLxEpDaE;
      string KwUJzGELUs;
      string QVTYuGmOAn;
      string LpOVPGLqQX;
      string FATkPJrihG;
      string xBlaZuCkPp;
      string RaClsTgyss;
      string tNtwmQCiJl;
      string NEfsqJDmuU;
      string EabZGeyhru;
      string ctooMjGpnJ;
      string sSbccMtIui;
      string QsDXoTkUoI;
      string RTqNJTOqgG;
      string DMzkbkyyxs;
      string jomIeipQAr;
      string ylAerYaNTI;
      if(UfxNqZxiNg == tNtwmQCiJl){yCbnfDsRwD = true;}
      else if(tNtwmQCiJl == UfxNqZxiNg){CgEQzHnXJb = true;}
      if(cVCNcuDtoZ == NEfsqJDmuU){UmWwXcghiZ = true;}
      else if(NEfsqJDmuU == cVCNcuDtoZ){XRUkNiMsfb = true;}
      if(FNrhNCNGTq == EabZGeyhru){cxqoHQMTsD = true;}
      else if(EabZGeyhru == FNrhNCNGTq){cYYGUnRpVU = true;}
      if(QWKLxEpDaE == ctooMjGpnJ){KkdougNycb = true;}
      else if(ctooMjGpnJ == QWKLxEpDaE){CApdtTDweE = true;}
      if(KwUJzGELUs == sSbccMtIui){oYUwWLPEHO = true;}
      else if(sSbccMtIui == KwUJzGELUs){diZhWEFfBB = true;}
      if(QVTYuGmOAn == QsDXoTkUoI){qreteALlgO = true;}
      else if(QsDXoTkUoI == QVTYuGmOAn){CIwbJcIxuK = true;}
      if(LpOVPGLqQX == RTqNJTOqgG){qZXrsjJhAp = true;}
      else if(RTqNJTOqgG == LpOVPGLqQX){oxBoYWapps = true;}
      if(FATkPJrihG == DMzkbkyyxs){PiEGjDctRw = true;}
      if(xBlaZuCkPp == jomIeipQAr){BHMeMRGjJt = true;}
      if(RaClsTgyss == ylAerYaNTI){VaQOkPBbDm = true;}
      while(DMzkbkyyxs == FATkPJrihG){fQNaytzpiQ = true;}
      while(jomIeipQAr == jomIeipQAr){hkoTRtDNTR = true;}
      while(ylAerYaNTI == ylAerYaNTI){LFATPfgkIz = true;}
      if(yCbnfDsRwD == true){yCbnfDsRwD = false;}
      if(UmWwXcghiZ == true){UmWwXcghiZ = false;}
      if(cxqoHQMTsD == true){cxqoHQMTsD = false;}
      if(KkdougNycb == true){KkdougNycb = false;}
      if(oYUwWLPEHO == true){oYUwWLPEHO = false;}
      if(qreteALlgO == true){qreteALlgO = false;}
      if(qZXrsjJhAp == true){qZXrsjJhAp = false;}
      if(PiEGjDctRw == true){PiEGjDctRw = false;}
      if(BHMeMRGjJt == true){BHMeMRGjJt = false;}
      if(VaQOkPBbDm == true){VaQOkPBbDm = false;}
      if(CgEQzHnXJb == true){CgEQzHnXJb = false;}
      if(XRUkNiMsfb == true){XRUkNiMsfb = false;}
      if(cYYGUnRpVU == true){cYYGUnRpVU = false;}
      if(CApdtTDweE == true){CApdtTDweE = false;}
      if(diZhWEFfBB == true){diZhWEFfBB = false;}
      if(CIwbJcIxuK == true){CIwbJcIxuK = false;}
      if(oxBoYWapps == true){oxBoYWapps = false;}
      if(fQNaytzpiQ == true){fQNaytzpiQ = false;}
      if(hkoTRtDNTR == true){hkoTRtDNTR = false;}
      if(LFATPfgkIz == true){LFATPfgkIz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQJHTWYSKE
{ 
  void SjtzmIhHki()
  { 
      bool iwUKAIarRH = false;
      bool eWtYaDJxRZ = false;
      bool OIdajpdBNh = false;
      bool sBwneqJGkI = false;
      bool QZxPmkrdjf = false;
      bool CzbxLaRtaJ = false;
      bool dZejNdaGtj = false;
      bool sDLJJnKOmz = false;
      bool xARhetYzbE = false;
      bool YPfbdpuNCJ = false;
      bool JlizlzmSnW = false;
      bool PDGaLdIxET = false;
      bool EadoKdXjfS = false;
      bool sxLdoKQRuf = false;
      bool GGLFoUJEPA = false;
      bool hyIhFhItoI = false;
      bool aDlUdRqckA = false;
      bool MpBXNxPXAo = false;
      bool USUejtndXG = false;
      bool CVcmEDUpaW = false;
      string lOXVpOKCnM;
      string xNsPKqoBSE;
      string zhnKkzRlmZ;
      string twXuzhholA;
      string lqTOUpzslK;
      string cKRHGDZMjq;
      string xXPNSAoyQc;
      string IzOSSHOYou;
      string AXAcwieQnu;
      string HVEtCNbGwT;
      string AAcJBduyny;
      string oAWoqYXmQi;
      string VYJUUltUPF;
      string fIcUtzuqaS;
      string nfcoGGyPDd;
      string onpNxbqInP;
      string iaihRgXBtr;
      string dgMxupwTNO;
      string neQkQrRPWS;
      string HmDKjMwtXZ;
      if(lOXVpOKCnM == AAcJBduyny){iwUKAIarRH = true;}
      else if(AAcJBduyny == lOXVpOKCnM){JlizlzmSnW = true;}
      if(xNsPKqoBSE == oAWoqYXmQi){eWtYaDJxRZ = true;}
      else if(oAWoqYXmQi == xNsPKqoBSE){PDGaLdIxET = true;}
      if(zhnKkzRlmZ == VYJUUltUPF){OIdajpdBNh = true;}
      else if(VYJUUltUPF == zhnKkzRlmZ){EadoKdXjfS = true;}
      if(twXuzhholA == fIcUtzuqaS){sBwneqJGkI = true;}
      else if(fIcUtzuqaS == twXuzhholA){sxLdoKQRuf = true;}
      if(lqTOUpzslK == nfcoGGyPDd){QZxPmkrdjf = true;}
      else if(nfcoGGyPDd == lqTOUpzslK){GGLFoUJEPA = true;}
      if(cKRHGDZMjq == onpNxbqInP){CzbxLaRtaJ = true;}
      else if(onpNxbqInP == cKRHGDZMjq){hyIhFhItoI = true;}
      if(xXPNSAoyQc == iaihRgXBtr){dZejNdaGtj = true;}
      else if(iaihRgXBtr == xXPNSAoyQc){aDlUdRqckA = true;}
      if(IzOSSHOYou == dgMxupwTNO){sDLJJnKOmz = true;}
      if(AXAcwieQnu == neQkQrRPWS){xARhetYzbE = true;}
      if(HVEtCNbGwT == HmDKjMwtXZ){YPfbdpuNCJ = true;}
      while(dgMxupwTNO == IzOSSHOYou){MpBXNxPXAo = true;}
      while(neQkQrRPWS == neQkQrRPWS){USUejtndXG = true;}
      while(HmDKjMwtXZ == HmDKjMwtXZ){CVcmEDUpaW = true;}
      if(iwUKAIarRH == true){iwUKAIarRH = false;}
      if(eWtYaDJxRZ == true){eWtYaDJxRZ = false;}
      if(OIdajpdBNh == true){OIdajpdBNh = false;}
      if(sBwneqJGkI == true){sBwneqJGkI = false;}
      if(QZxPmkrdjf == true){QZxPmkrdjf = false;}
      if(CzbxLaRtaJ == true){CzbxLaRtaJ = false;}
      if(dZejNdaGtj == true){dZejNdaGtj = false;}
      if(sDLJJnKOmz == true){sDLJJnKOmz = false;}
      if(xARhetYzbE == true){xARhetYzbE = false;}
      if(YPfbdpuNCJ == true){YPfbdpuNCJ = false;}
      if(JlizlzmSnW == true){JlizlzmSnW = false;}
      if(PDGaLdIxET == true){PDGaLdIxET = false;}
      if(EadoKdXjfS == true){EadoKdXjfS = false;}
      if(sxLdoKQRuf == true){sxLdoKQRuf = false;}
      if(GGLFoUJEPA == true){GGLFoUJEPA = false;}
      if(hyIhFhItoI == true){hyIhFhItoI = false;}
      if(aDlUdRqckA == true){aDlUdRqckA = false;}
      if(MpBXNxPXAo == true){MpBXNxPXAo = false;}
      if(USUejtndXG == true){USUejtndXG = false;}
      if(CVcmEDUpaW == true){CVcmEDUpaW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCFBXCMPPA
{ 
  void UdIaaqFgMC()
  { 
      bool TJSPwBtatq = false;
      bool VjgAiCSiDb = false;
      bool HRSjTghYlf = false;
      bool dahshFIPWm = false;
      bool ocUkNUbafy = false;
      bool ldeuYCqiuP = false;
      bool SVnNMuBmSd = false;
      bool tCMPmewhWz = false;
      bool FGrntzumUe = false;
      bool NYTHUTnGXS = false;
      bool SnICDiROHt = false;
      bool FIMuKLcATN = false;
      bool zOSmPUhEuS = false;
      bool ppKDgQypjL = false;
      bool hfeaZFMYxI = false;
      bool qnmKSEVVli = false;
      bool AMToEPyINs = false;
      bool NlPHeSiqMK = false;
      bool HJHlbBDzjc = false;
      bool ubEBLUMpWK = false;
      string hXlFCssPZQ;
      string UPxfuxJdla;
      string YJjeuIzTep;
      string LkMusQSdCm;
      string ZVOWbRhKjx;
      string VrJshXnHKt;
      string tYjjEjDCle;
      string efbzBDuMCc;
      string ZnjgTSaSNU;
      string bKSIrAkdRr;
      string OeYFSpQJrd;
      string cbFgTFoCQl;
      string IjoRCTMTGA;
      string RRtKNtPdOd;
      string BQairAElnm;
      string LiNeiepGCy;
      string cxDrLLgtSY;
      string pKnmkqJFZC;
      string OaeTniDPbi;
      string EIbPAENhXf;
      if(hXlFCssPZQ == OeYFSpQJrd){TJSPwBtatq = true;}
      else if(OeYFSpQJrd == hXlFCssPZQ){SnICDiROHt = true;}
      if(UPxfuxJdla == cbFgTFoCQl){VjgAiCSiDb = true;}
      else if(cbFgTFoCQl == UPxfuxJdla){FIMuKLcATN = true;}
      if(YJjeuIzTep == IjoRCTMTGA){HRSjTghYlf = true;}
      else if(IjoRCTMTGA == YJjeuIzTep){zOSmPUhEuS = true;}
      if(LkMusQSdCm == RRtKNtPdOd){dahshFIPWm = true;}
      else if(RRtKNtPdOd == LkMusQSdCm){ppKDgQypjL = true;}
      if(ZVOWbRhKjx == BQairAElnm){ocUkNUbafy = true;}
      else if(BQairAElnm == ZVOWbRhKjx){hfeaZFMYxI = true;}
      if(VrJshXnHKt == LiNeiepGCy){ldeuYCqiuP = true;}
      else if(LiNeiepGCy == VrJshXnHKt){qnmKSEVVli = true;}
      if(tYjjEjDCle == cxDrLLgtSY){SVnNMuBmSd = true;}
      else if(cxDrLLgtSY == tYjjEjDCle){AMToEPyINs = true;}
      if(efbzBDuMCc == pKnmkqJFZC){tCMPmewhWz = true;}
      if(ZnjgTSaSNU == OaeTniDPbi){FGrntzumUe = true;}
      if(bKSIrAkdRr == EIbPAENhXf){NYTHUTnGXS = true;}
      while(pKnmkqJFZC == efbzBDuMCc){NlPHeSiqMK = true;}
      while(OaeTniDPbi == OaeTniDPbi){HJHlbBDzjc = true;}
      while(EIbPAENhXf == EIbPAENhXf){ubEBLUMpWK = true;}
      if(TJSPwBtatq == true){TJSPwBtatq = false;}
      if(VjgAiCSiDb == true){VjgAiCSiDb = false;}
      if(HRSjTghYlf == true){HRSjTghYlf = false;}
      if(dahshFIPWm == true){dahshFIPWm = false;}
      if(ocUkNUbafy == true){ocUkNUbafy = false;}
      if(ldeuYCqiuP == true){ldeuYCqiuP = false;}
      if(SVnNMuBmSd == true){SVnNMuBmSd = false;}
      if(tCMPmewhWz == true){tCMPmewhWz = false;}
      if(FGrntzumUe == true){FGrntzumUe = false;}
      if(NYTHUTnGXS == true){NYTHUTnGXS = false;}
      if(SnICDiROHt == true){SnICDiROHt = false;}
      if(FIMuKLcATN == true){FIMuKLcATN = false;}
      if(zOSmPUhEuS == true){zOSmPUhEuS = false;}
      if(ppKDgQypjL == true){ppKDgQypjL = false;}
      if(hfeaZFMYxI == true){hfeaZFMYxI = false;}
      if(qnmKSEVVli == true){qnmKSEVVli = false;}
      if(AMToEPyINs == true){AMToEPyINs = false;}
      if(NlPHeSiqMK == true){NlPHeSiqMK = false;}
      if(HJHlbBDzjc == true){HJHlbBDzjc = false;}
      if(ubEBLUMpWK == true){ubEBLUMpWK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPCOHAOMSP
{ 
  void RbxGkgYIrP()
  { 
      bool iPEkWFegqE = false;
      bool ZcfjbREumZ = false;
      bool aqVzRmrNxF = false;
      bool PuxmDMoikS = false;
      bool xLKJSboTZm = false;
      bool cpnKCqsFSj = false;
      bool MRilneergO = false;
      bool cVKTbPfMfp = false;
      bool xXmJbZGmjL = false;
      bool SjPAFfbXUn = false;
      bool wwlLKGfThm = false;
      bool KfYblndZKO = false;
      bool XrIUurGKNw = false;
      bool mIqrtBlbzV = false;
      bool tlEwAlLmNQ = false;
      bool CCNGPEnRPR = false;
      bool AUFlACofhk = false;
      bool CBZnUkmLTI = false;
      bool gSwwsjtkbo = false;
      bool NTMgVYgSwy = false;
      string kJFTzBLuSb;
      string iySaHyYwuN;
      string JMclpQzXpj;
      string bLMgRlVGbF;
      string NUjXUsTVJG;
      string SUflQXgTdh;
      string CmEizWklJV;
      string bSUpAncEQx;
      string wdOiQGfZPs;
      string FBcsDZQBXx;
      string HgMmdAAplb;
      string ubCgkYXURs;
      string qKWPPaoblZ;
      string XbgToORbFP;
      string GonnydywHd;
      string BuidFwKwWD;
      string LYDLDTtiqV;
      string HwPCmBWhQl;
      string bsTHYcrCNr;
      string EUEBEglbkd;
      if(kJFTzBLuSb == HgMmdAAplb){iPEkWFegqE = true;}
      else if(HgMmdAAplb == kJFTzBLuSb){wwlLKGfThm = true;}
      if(iySaHyYwuN == ubCgkYXURs){ZcfjbREumZ = true;}
      else if(ubCgkYXURs == iySaHyYwuN){KfYblndZKO = true;}
      if(JMclpQzXpj == qKWPPaoblZ){aqVzRmrNxF = true;}
      else if(qKWPPaoblZ == JMclpQzXpj){XrIUurGKNw = true;}
      if(bLMgRlVGbF == XbgToORbFP){PuxmDMoikS = true;}
      else if(XbgToORbFP == bLMgRlVGbF){mIqrtBlbzV = true;}
      if(NUjXUsTVJG == GonnydywHd){xLKJSboTZm = true;}
      else if(GonnydywHd == NUjXUsTVJG){tlEwAlLmNQ = true;}
      if(SUflQXgTdh == BuidFwKwWD){cpnKCqsFSj = true;}
      else if(BuidFwKwWD == SUflQXgTdh){CCNGPEnRPR = true;}
      if(CmEizWklJV == LYDLDTtiqV){MRilneergO = true;}
      else if(LYDLDTtiqV == CmEizWklJV){AUFlACofhk = true;}
      if(bSUpAncEQx == HwPCmBWhQl){cVKTbPfMfp = true;}
      if(wdOiQGfZPs == bsTHYcrCNr){xXmJbZGmjL = true;}
      if(FBcsDZQBXx == EUEBEglbkd){SjPAFfbXUn = true;}
      while(HwPCmBWhQl == bSUpAncEQx){CBZnUkmLTI = true;}
      while(bsTHYcrCNr == bsTHYcrCNr){gSwwsjtkbo = true;}
      while(EUEBEglbkd == EUEBEglbkd){NTMgVYgSwy = true;}
      if(iPEkWFegqE == true){iPEkWFegqE = false;}
      if(ZcfjbREumZ == true){ZcfjbREumZ = false;}
      if(aqVzRmrNxF == true){aqVzRmrNxF = false;}
      if(PuxmDMoikS == true){PuxmDMoikS = false;}
      if(xLKJSboTZm == true){xLKJSboTZm = false;}
      if(cpnKCqsFSj == true){cpnKCqsFSj = false;}
      if(MRilneergO == true){MRilneergO = false;}
      if(cVKTbPfMfp == true){cVKTbPfMfp = false;}
      if(xXmJbZGmjL == true){xXmJbZGmjL = false;}
      if(SjPAFfbXUn == true){SjPAFfbXUn = false;}
      if(wwlLKGfThm == true){wwlLKGfThm = false;}
      if(KfYblndZKO == true){KfYblndZKO = false;}
      if(XrIUurGKNw == true){XrIUurGKNw = false;}
      if(mIqrtBlbzV == true){mIqrtBlbzV = false;}
      if(tlEwAlLmNQ == true){tlEwAlLmNQ = false;}
      if(CCNGPEnRPR == true){CCNGPEnRPR = false;}
      if(AUFlACofhk == true){AUFlACofhk = false;}
      if(CBZnUkmLTI == true){CBZnUkmLTI = false;}
      if(gSwwsjtkbo == true){gSwwsjtkbo = false;}
      if(NTMgVYgSwy == true){NTMgVYgSwy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZVBGWTPRS
{ 
  void GSlcAZHJdJ()
  { 
      bool WyXdfclyMR = false;
      bool eBbaMTtCNj = false;
      bool VgEEAyXGKw = false;
      bool ZcGhHimqMG = false;
      bool aYfNmPNdwh = false;
      bool leimCptSdg = false;
      bool EenPqBtsSc = false;
      bool fCoGIwBpRk = false;
      bool jsJbKusSfR = false;
      bool oUNfCukPVk = false;
      bool UTLTCjobdG = false;
      bool oDBswLVLFw = false;
      bool IbNBnKoIEM = false;
      bool KkUfPQhpZa = false;
      bool FQnZckTUiq = false;
      bool ZYKYcsGJeq = false;
      bool tgXRuDhVcf = false;
      bool cflepqmnXC = false;
      bool qUYNmlZuCV = false;
      bool JXKifYsWdY = false;
      string LSpQTwpoJm;
      string NHJYqIdUaM;
      string lyNoYhCHIz;
      string ksFdHKWhuc;
      string cCMQcbIWOu;
      string hHHWxNFAql;
      string shgJCUCfQg;
      string kwZxjjkxMw;
      string YesNRckhgs;
      string FVpIitUCOH;
      string ZcGhJkgJmM;
      string bIntMOoTrY;
      string iUyXbPGROo;
      string OihEWuYLDf;
      string wbtURwhuuU;
      string FBKoYEehFt;
      string ePuxxsZiXQ;
      string ocPLcGZdGe;
      string gLVsiMXreS;
      string QpFJBfgxWX;
      if(LSpQTwpoJm == ZcGhJkgJmM){WyXdfclyMR = true;}
      else if(ZcGhJkgJmM == LSpQTwpoJm){UTLTCjobdG = true;}
      if(NHJYqIdUaM == bIntMOoTrY){eBbaMTtCNj = true;}
      else if(bIntMOoTrY == NHJYqIdUaM){oDBswLVLFw = true;}
      if(lyNoYhCHIz == iUyXbPGROo){VgEEAyXGKw = true;}
      else if(iUyXbPGROo == lyNoYhCHIz){IbNBnKoIEM = true;}
      if(ksFdHKWhuc == OihEWuYLDf){ZcGhHimqMG = true;}
      else if(OihEWuYLDf == ksFdHKWhuc){KkUfPQhpZa = true;}
      if(cCMQcbIWOu == wbtURwhuuU){aYfNmPNdwh = true;}
      else if(wbtURwhuuU == cCMQcbIWOu){FQnZckTUiq = true;}
      if(hHHWxNFAql == FBKoYEehFt){leimCptSdg = true;}
      else if(FBKoYEehFt == hHHWxNFAql){ZYKYcsGJeq = true;}
      if(shgJCUCfQg == ePuxxsZiXQ){EenPqBtsSc = true;}
      else if(ePuxxsZiXQ == shgJCUCfQg){tgXRuDhVcf = true;}
      if(kwZxjjkxMw == ocPLcGZdGe){fCoGIwBpRk = true;}
      if(YesNRckhgs == gLVsiMXreS){jsJbKusSfR = true;}
      if(FVpIitUCOH == QpFJBfgxWX){oUNfCukPVk = true;}
      while(ocPLcGZdGe == kwZxjjkxMw){cflepqmnXC = true;}
      while(gLVsiMXreS == gLVsiMXreS){qUYNmlZuCV = true;}
      while(QpFJBfgxWX == QpFJBfgxWX){JXKifYsWdY = true;}
      if(WyXdfclyMR == true){WyXdfclyMR = false;}
      if(eBbaMTtCNj == true){eBbaMTtCNj = false;}
      if(VgEEAyXGKw == true){VgEEAyXGKw = false;}
      if(ZcGhHimqMG == true){ZcGhHimqMG = false;}
      if(aYfNmPNdwh == true){aYfNmPNdwh = false;}
      if(leimCptSdg == true){leimCptSdg = false;}
      if(EenPqBtsSc == true){EenPqBtsSc = false;}
      if(fCoGIwBpRk == true){fCoGIwBpRk = false;}
      if(jsJbKusSfR == true){jsJbKusSfR = false;}
      if(oUNfCukPVk == true){oUNfCukPVk = false;}
      if(UTLTCjobdG == true){UTLTCjobdG = false;}
      if(oDBswLVLFw == true){oDBswLVLFw = false;}
      if(IbNBnKoIEM == true){IbNBnKoIEM = false;}
      if(KkUfPQhpZa == true){KkUfPQhpZa = false;}
      if(FQnZckTUiq == true){FQnZckTUiq = false;}
      if(ZYKYcsGJeq == true){ZYKYcsGJeq = false;}
      if(tgXRuDhVcf == true){tgXRuDhVcf = false;}
      if(cflepqmnXC == true){cflepqmnXC = false;}
      if(qUYNmlZuCV == true){qUYNmlZuCV = false;}
      if(JXKifYsWdY == true){JXKifYsWdY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGJGVIGBYT
{ 
  void mIDABkqPcR()
  { 
      bool ezgCDNCQxU = false;
      bool FUOVAHWGcN = false;
      bool OVwtynSxYX = false;
      bool ZlZZRoMMbW = false;
      bool FhHVLrUnHP = false;
      bool ojVNaJDlEO = false;
      bool tEqZuTtnDL = false;
      bool uKdGIgNZiF = false;
      bool TeoIhoQLzH = false;
      bool kZINbApgaq = false;
      bool yfjuTdFOFs = false;
      bool udCytPOhqG = false;
      bool ChowaUBQeH = false;
      bool qgzqHnutnD = false;
      bool iBGGLHXKSL = false;
      bool lHoUoPpmUz = false;
      bool coiyBOeKqF = false;
      bool UUsmWBbhjT = false;
      bool xqxTUjqeCq = false;
      bool xHYoasRHEx = false;
      string ikoNPPidfZ;
      string LKlwAKiBpO;
      string KNVNqNMiKy;
      string YqJBzgfiLS;
      string tgRSBqHxmu;
      string lGSIQVPbVB;
      string CzThBTAkxT;
      string ezoXUduDLA;
      string GOuOLRYBkc;
      string RDNKPtNjQg;
      string qWzTQmRtnl;
      string ZLQUunEEVj;
      string uzATBaleHZ;
      string QLldJjPbyY;
      string zdMyDFmrOb;
      string pINglrWfRo;
      string BmmNVNZmLL;
      string YbGxjQlCQw;
      string nsPfjHyEqQ;
      string MjJIXMqzbp;
      if(ikoNPPidfZ == qWzTQmRtnl){ezgCDNCQxU = true;}
      else if(qWzTQmRtnl == ikoNPPidfZ){yfjuTdFOFs = true;}
      if(LKlwAKiBpO == ZLQUunEEVj){FUOVAHWGcN = true;}
      else if(ZLQUunEEVj == LKlwAKiBpO){udCytPOhqG = true;}
      if(KNVNqNMiKy == uzATBaleHZ){OVwtynSxYX = true;}
      else if(uzATBaleHZ == KNVNqNMiKy){ChowaUBQeH = true;}
      if(YqJBzgfiLS == QLldJjPbyY){ZlZZRoMMbW = true;}
      else if(QLldJjPbyY == YqJBzgfiLS){qgzqHnutnD = true;}
      if(tgRSBqHxmu == zdMyDFmrOb){FhHVLrUnHP = true;}
      else if(zdMyDFmrOb == tgRSBqHxmu){iBGGLHXKSL = true;}
      if(lGSIQVPbVB == pINglrWfRo){ojVNaJDlEO = true;}
      else if(pINglrWfRo == lGSIQVPbVB){lHoUoPpmUz = true;}
      if(CzThBTAkxT == BmmNVNZmLL){tEqZuTtnDL = true;}
      else if(BmmNVNZmLL == CzThBTAkxT){coiyBOeKqF = true;}
      if(ezoXUduDLA == YbGxjQlCQw){uKdGIgNZiF = true;}
      if(GOuOLRYBkc == nsPfjHyEqQ){TeoIhoQLzH = true;}
      if(RDNKPtNjQg == MjJIXMqzbp){kZINbApgaq = true;}
      while(YbGxjQlCQw == ezoXUduDLA){UUsmWBbhjT = true;}
      while(nsPfjHyEqQ == nsPfjHyEqQ){xqxTUjqeCq = true;}
      while(MjJIXMqzbp == MjJIXMqzbp){xHYoasRHEx = true;}
      if(ezgCDNCQxU == true){ezgCDNCQxU = false;}
      if(FUOVAHWGcN == true){FUOVAHWGcN = false;}
      if(OVwtynSxYX == true){OVwtynSxYX = false;}
      if(ZlZZRoMMbW == true){ZlZZRoMMbW = false;}
      if(FhHVLrUnHP == true){FhHVLrUnHP = false;}
      if(ojVNaJDlEO == true){ojVNaJDlEO = false;}
      if(tEqZuTtnDL == true){tEqZuTtnDL = false;}
      if(uKdGIgNZiF == true){uKdGIgNZiF = false;}
      if(TeoIhoQLzH == true){TeoIhoQLzH = false;}
      if(kZINbApgaq == true){kZINbApgaq = false;}
      if(yfjuTdFOFs == true){yfjuTdFOFs = false;}
      if(udCytPOhqG == true){udCytPOhqG = false;}
      if(ChowaUBQeH == true){ChowaUBQeH = false;}
      if(qgzqHnutnD == true){qgzqHnutnD = false;}
      if(iBGGLHXKSL == true){iBGGLHXKSL = false;}
      if(lHoUoPpmUz == true){lHoUoPpmUz = false;}
      if(coiyBOeKqF == true){coiyBOeKqF = false;}
      if(UUsmWBbhjT == true){UUsmWBbhjT = false;}
      if(xqxTUjqeCq == true){xqxTUjqeCq = false;}
      if(xHYoasRHEx == true){xHYoasRHEx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVTSUOZYLD
{ 
  void uLnXawJFBu()
  { 
      bool ApMUwQDbth = false;
      bool bBLAtVaoGM = false;
      bool dOhXiygrRZ = false;
      bool YiitbgdkzS = false;
      bool TIkAiPuyLf = false;
      bool lPVpjlHnkx = false;
      bool jLKTJsRQYM = false;
      bool qpomsVchoT = false;
      bool ChflnIMsKp = false;
      bool ZozChHyQqo = false;
      bool xeZzowZhxO = false;
      bool IZzRtBfYfB = false;
      bool fYGimBplEk = false;
      bool WLpzVXIgxr = false;
      bool hewugzphHg = false;
      bool bZkpIXXpLm = false;
      bool FncLrwizuV = false;
      bool rybmSBcLBm = false;
      bool LIdXJwaAqx = false;
      bool ASUJmtBkCj = false;
      string sQgistwLXu;
      string lLfEVJkNAd;
      string KjctpOTJUb;
      string NtuFlsHUIN;
      string rNYyVdqdez;
      string OLVHGInlre;
      string ampuhqPZRc;
      string BPEllwLdYL;
      string XodUNBYmyc;
      string EVccmFWdPd;
      string OQLBxzHiVK;
      string xJMgHkIVhg;
      string SbboXfmayf;
      string YgOuxGdcXN;
      string soRneuIwVC;
      string wBwhLloVcR;
      string MfkokPtRiB;
      string GfxTmcKmJc;
      string XqFwiXkfiK;
      string RHzFBMEbDO;
      if(sQgistwLXu == OQLBxzHiVK){ApMUwQDbth = true;}
      else if(OQLBxzHiVK == sQgistwLXu){xeZzowZhxO = true;}
      if(lLfEVJkNAd == xJMgHkIVhg){bBLAtVaoGM = true;}
      else if(xJMgHkIVhg == lLfEVJkNAd){IZzRtBfYfB = true;}
      if(KjctpOTJUb == SbboXfmayf){dOhXiygrRZ = true;}
      else if(SbboXfmayf == KjctpOTJUb){fYGimBplEk = true;}
      if(NtuFlsHUIN == YgOuxGdcXN){YiitbgdkzS = true;}
      else if(YgOuxGdcXN == NtuFlsHUIN){WLpzVXIgxr = true;}
      if(rNYyVdqdez == soRneuIwVC){TIkAiPuyLf = true;}
      else if(soRneuIwVC == rNYyVdqdez){hewugzphHg = true;}
      if(OLVHGInlre == wBwhLloVcR){lPVpjlHnkx = true;}
      else if(wBwhLloVcR == OLVHGInlre){bZkpIXXpLm = true;}
      if(ampuhqPZRc == MfkokPtRiB){jLKTJsRQYM = true;}
      else if(MfkokPtRiB == ampuhqPZRc){FncLrwizuV = true;}
      if(BPEllwLdYL == GfxTmcKmJc){qpomsVchoT = true;}
      if(XodUNBYmyc == XqFwiXkfiK){ChflnIMsKp = true;}
      if(EVccmFWdPd == RHzFBMEbDO){ZozChHyQqo = true;}
      while(GfxTmcKmJc == BPEllwLdYL){rybmSBcLBm = true;}
      while(XqFwiXkfiK == XqFwiXkfiK){LIdXJwaAqx = true;}
      while(RHzFBMEbDO == RHzFBMEbDO){ASUJmtBkCj = true;}
      if(ApMUwQDbth == true){ApMUwQDbth = false;}
      if(bBLAtVaoGM == true){bBLAtVaoGM = false;}
      if(dOhXiygrRZ == true){dOhXiygrRZ = false;}
      if(YiitbgdkzS == true){YiitbgdkzS = false;}
      if(TIkAiPuyLf == true){TIkAiPuyLf = false;}
      if(lPVpjlHnkx == true){lPVpjlHnkx = false;}
      if(jLKTJsRQYM == true){jLKTJsRQYM = false;}
      if(qpomsVchoT == true){qpomsVchoT = false;}
      if(ChflnIMsKp == true){ChflnIMsKp = false;}
      if(ZozChHyQqo == true){ZozChHyQqo = false;}
      if(xeZzowZhxO == true){xeZzowZhxO = false;}
      if(IZzRtBfYfB == true){IZzRtBfYfB = false;}
      if(fYGimBplEk == true){fYGimBplEk = false;}
      if(WLpzVXIgxr == true){WLpzVXIgxr = false;}
      if(hewugzphHg == true){hewugzphHg = false;}
      if(bZkpIXXpLm == true){bZkpIXXpLm = false;}
      if(FncLrwizuV == true){FncLrwizuV = false;}
      if(rybmSBcLBm == true){rybmSBcLBm = false;}
      if(LIdXJwaAqx == true){LIdXJwaAqx = false;}
      if(ASUJmtBkCj == true){ASUJmtBkCj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEVNQDKYMS
{ 
  void KzHIETPIFK()
  { 
      bool ARNJtebpWX = false;
      bool gmBpuyTuzV = false;
      bool irRrmxwplL = false;
      bool RJPalcqhud = false;
      bool MsnLeDLjWT = false;
      bool geHUAIAVWw = false;
      bool ikELGWWaDS = false;
      bool GlzVIpEFMj = false;
      bool kMSSdmCuZd = false;
      bool cVLytbnbFI = false;
      bool fkfEMuelLK = false;
      bool EtImLWRlgT = false;
      bool TbAZokZAag = false;
      bool BbAEEzfOFi = false;
      bool HQiPZiNYmX = false;
      bool JCulnDkGOb = false;
      bool UdKdJbsDhL = false;
      bool pDfxLCrkzG = false;
      bool WBNCXzgOPA = false;
      bool OYAdNdFFFx = false;
      string nIwjamujyH;
      string yJmQIYgaQU;
      string GqAcidxsEa;
      string aFstzMnewf;
      string egrrKuttSp;
      string cVPJIxHTAx;
      string oBfXfrQrRw;
      string jBekoZzIRn;
      string jDaOxEpjkB;
      string EUdzpcAULR;
      string dBcVFaqeTi;
      string yzBMMlaQZa;
      string CgHPrOWetL;
      string YdwzJiaEIV;
      string NKPBDETRmE;
      string CjtkPxsNdp;
      string ELkIKTDBDc;
      string KWIDNqQGLm;
      string uFroJnjLjL;
      string pNZRRBZGpj;
      if(nIwjamujyH == dBcVFaqeTi){ARNJtebpWX = true;}
      else if(dBcVFaqeTi == nIwjamujyH){fkfEMuelLK = true;}
      if(yJmQIYgaQU == yzBMMlaQZa){gmBpuyTuzV = true;}
      else if(yzBMMlaQZa == yJmQIYgaQU){EtImLWRlgT = true;}
      if(GqAcidxsEa == CgHPrOWetL){irRrmxwplL = true;}
      else if(CgHPrOWetL == GqAcidxsEa){TbAZokZAag = true;}
      if(aFstzMnewf == YdwzJiaEIV){RJPalcqhud = true;}
      else if(YdwzJiaEIV == aFstzMnewf){BbAEEzfOFi = true;}
      if(egrrKuttSp == NKPBDETRmE){MsnLeDLjWT = true;}
      else if(NKPBDETRmE == egrrKuttSp){HQiPZiNYmX = true;}
      if(cVPJIxHTAx == CjtkPxsNdp){geHUAIAVWw = true;}
      else if(CjtkPxsNdp == cVPJIxHTAx){JCulnDkGOb = true;}
      if(oBfXfrQrRw == ELkIKTDBDc){ikELGWWaDS = true;}
      else if(ELkIKTDBDc == oBfXfrQrRw){UdKdJbsDhL = true;}
      if(jBekoZzIRn == KWIDNqQGLm){GlzVIpEFMj = true;}
      if(jDaOxEpjkB == uFroJnjLjL){kMSSdmCuZd = true;}
      if(EUdzpcAULR == pNZRRBZGpj){cVLytbnbFI = true;}
      while(KWIDNqQGLm == jBekoZzIRn){pDfxLCrkzG = true;}
      while(uFroJnjLjL == uFroJnjLjL){WBNCXzgOPA = true;}
      while(pNZRRBZGpj == pNZRRBZGpj){OYAdNdFFFx = true;}
      if(ARNJtebpWX == true){ARNJtebpWX = false;}
      if(gmBpuyTuzV == true){gmBpuyTuzV = false;}
      if(irRrmxwplL == true){irRrmxwplL = false;}
      if(RJPalcqhud == true){RJPalcqhud = false;}
      if(MsnLeDLjWT == true){MsnLeDLjWT = false;}
      if(geHUAIAVWw == true){geHUAIAVWw = false;}
      if(ikELGWWaDS == true){ikELGWWaDS = false;}
      if(GlzVIpEFMj == true){GlzVIpEFMj = false;}
      if(kMSSdmCuZd == true){kMSSdmCuZd = false;}
      if(cVLytbnbFI == true){cVLytbnbFI = false;}
      if(fkfEMuelLK == true){fkfEMuelLK = false;}
      if(EtImLWRlgT == true){EtImLWRlgT = false;}
      if(TbAZokZAag == true){TbAZokZAag = false;}
      if(BbAEEzfOFi == true){BbAEEzfOFi = false;}
      if(HQiPZiNYmX == true){HQiPZiNYmX = false;}
      if(JCulnDkGOb == true){JCulnDkGOb = false;}
      if(UdKdJbsDhL == true){UdKdJbsDhL = false;}
      if(pDfxLCrkzG == true){pDfxLCrkzG = false;}
      if(WBNCXzgOPA == true){WBNCXzgOPA = false;}
      if(OYAdNdFFFx == true){OYAdNdFFFx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUISYGVJDB
{ 
  void JPrIRCLbbR()
  { 
      bool FpIMEfstyA = false;
      bool hnmidAxGoX = false;
      bool jsOAKWfFOA = false;
      bool zRIPiYyjbr = false;
      bool RPFNmruwCs = false;
      bool bUJsgLbICh = false;
      bool AmfxAPfWzE = false;
      bool BMdxGUnAMR = false;
      bool bjCUXdHPhX = false;
      bool xphtqdjHNW = false;
      bool MXwyrOqMlM = false;
      bool WaujGQjKYW = false;
      bool HPobGKejFb = false;
      bool jgmoEEmEbJ = false;
      bool lucUAWtxmZ = false;
      bool sYhqOxiTrh = false;
      bool jHGKcpnGfC = false;
      bool cfhPjMmTbi = false;
      bool PgwehKywZH = false;
      bool UTMtYenSrK = false;
      string dkjfmQgSAH;
      string TMcOKhKBzJ;
      string ruTJtSqzCt;
      string zirfCsMFKp;
      string mITZCxjagy;
      string yknAHiRZlU;
      string YgQGHkUxMR;
      string VFqJViasHw;
      string hQSDuOtqXT;
      string alTpRFrNRR;
      string cmNOcstedY;
      string HYSolHOMKs;
      string pdYsqilAqP;
      string pNaoTuCDZB;
      string TPMzLCTdDJ;
      string qfDXayNUXs;
      string HtmNhtxcUq;
      string EKlIZaQZgn;
      string PHwgYKJDOU;
      string ghegtZbzQR;
      if(dkjfmQgSAH == cmNOcstedY){FpIMEfstyA = true;}
      else if(cmNOcstedY == dkjfmQgSAH){MXwyrOqMlM = true;}
      if(TMcOKhKBzJ == HYSolHOMKs){hnmidAxGoX = true;}
      else if(HYSolHOMKs == TMcOKhKBzJ){WaujGQjKYW = true;}
      if(ruTJtSqzCt == pdYsqilAqP){jsOAKWfFOA = true;}
      else if(pdYsqilAqP == ruTJtSqzCt){HPobGKejFb = true;}
      if(zirfCsMFKp == pNaoTuCDZB){zRIPiYyjbr = true;}
      else if(pNaoTuCDZB == zirfCsMFKp){jgmoEEmEbJ = true;}
      if(mITZCxjagy == TPMzLCTdDJ){RPFNmruwCs = true;}
      else if(TPMzLCTdDJ == mITZCxjagy){lucUAWtxmZ = true;}
      if(yknAHiRZlU == qfDXayNUXs){bUJsgLbICh = true;}
      else if(qfDXayNUXs == yknAHiRZlU){sYhqOxiTrh = true;}
      if(YgQGHkUxMR == HtmNhtxcUq){AmfxAPfWzE = true;}
      else if(HtmNhtxcUq == YgQGHkUxMR){jHGKcpnGfC = true;}
      if(VFqJViasHw == EKlIZaQZgn){BMdxGUnAMR = true;}
      if(hQSDuOtqXT == PHwgYKJDOU){bjCUXdHPhX = true;}
      if(alTpRFrNRR == ghegtZbzQR){xphtqdjHNW = true;}
      while(EKlIZaQZgn == VFqJViasHw){cfhPjMmTbi = true;}
      while(PHwgYKJDOU == PHwgYKJDOU){PgwehKywZH = true;}
      while(ghegtZbzQR == ghegtZbzQR){UTMtYenSrK = true;}
      if(FpIMEfstyA == true){FpIMEfstyA = false;}
      if(hnmidAxGoX == true){hnmidAxGoX = false;}
      if(jsOAKWfFOA == true){jsOAKWfFOA = false;}
      if(zRIPiYyjbr == true){zRIPiYyjbr = false;}
      if(RPFNmruwCs == true){RPFNmruwCs = false;}
      if(bUJsgLbICh == true){bUJsgLbICh = false;}
      if(AmfxAPfWzE == true){AmfxAPfWzE = false;}
      if(BMdxGUnAMR == true){BMdxGUnAMR = false;}
      if(bjCUXdHPhX == true){bjCUXdHPhX = false;}
      if(xphtqdjHNW == true){xphtqdjHNW = false;}
      if(MXwyrOqMlM == true){MXwyrOqMlM = false;}
      if(WaujGQjKYW == true){WaujGQjKYW = false;}
      if(HPobGKejFb == true){HPobGKejFb = false;}
      if(jgmoEEmEbJ == true){jgmoEEmEbJ = false;}
      if(lucUAWtxmZ == true){lucUAWtxmZ = false;}
      if(sYhqOxiTrh == true){sYhqOxiTrh = false;}
      if(jHGKcpnGfC == true){jHGKcpnGfC = false;}
      if(cfhPjMmTbi == true){cfhPjMmTbi = false;}
      if(PgwehKywZH == true){PgwehKywZH = false;}
      if(UTMtYenSrK == true){UTMtYenSrK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFFJINICVU
{ 
  void IAIIaOpZAs()
  { 
      bool MFIxYbZPHY = false;
      bool dqkQwWpfUP = false;
      bool RSMNbIsrBB = false;
      bool eDKzQlJKHa = false;
      bool XWIeUANWWV = false;
      bool fFoRlsstUQ = false;
      bool ihNFsZglzK = false;
      bool MfXsruKgsb = false;
      bool uVVfVZNrNX = false;
      bool rOoqrpIClt = false;
      bool SaXLIAhuZp = false;
      bool iLAsVMMhjT = false;
      bool MnYbRypgAB = false;
      bool lHuyITyJWV = false;
      bool qRSWngNuVf = false;
      bool daSShdCusK = false;
      bool JBuXEbQCjB = false;
      bool NCKObtVCmk = false;
      bool jtKUXKnbQe = false;
      bool QCPLLpWuRM = false;
      string kTyOxekjbg;
      string dONFVjNtye;
      string XDWpiCyTGr;
      string zpwgoWoDIH;
      string qiUErFDNSw;
      string kIQamhwIfu;
      string fQcihnRgQz;
      string tKlpmohRyc;
      string ykBJHpYVsG;
      string ZgXNbZFlWE;
      string mWxSCaWamy;
      string zeKCwuPTbq;
      string OwmJYNlYNN;
      string jwusobmhHg;
      string TyiuGuWURg;
      string JlKeoqjntn;
      string nxMYNDiQMT;
      string HgLtXQNrCc;
      string qRHgDylPEy;
      string rznTrVkJgD;
      if(kTyOxekjbg == mWxSCaWamy){MFIxYbZPHY = true;}
      else if(mWxSCaWamy == kTyOxekjbg){SaXLIAhuZp = true;}
      if(dONFVjNtye == zeKCwuPTbq){dqkQwWpfUP = true;}
      else if(zeKCwuPTbq == dONFVjNtye){iLAsVMMhjT = true;}
      if(XDWpiCyTGr == OwmJYNlYNN){RSMNbIsrBB = true;}
      else if(OwmJYNlYNN == XDWpiCyTGr){MnYbRypgAB = true;}
      if(zpwgoWoDIH == jwusobmhHg){eDKzQlJKHa = true;}
      else if(jwusobmhHg == zpwgoWoDIH){lHuyITyJWV = true;}
      if(qiUErFDNSw == TyiuGuWURg){XWIeUANWWV = true;}
      else if(TyiuGuWURg == qiUErFDNSw){qRSWngNuVf = true;}
      if(kIQamhwIfu == JlKeoqjntn){fFoRlsstUQ = true;}
      else if(JlKeoqjntn == kIQamhwIfu){daSShdCusK = true;}
      if(fQcihnRgQz == nxMYNDiQMT){ihNFsZglzK = true;}
      else if(nxMYNDiQMT == fQcihnRgQz){JBuXEbQCjB = true;}
      if(tKlpmohRyc == HgLtXQNrCc){MfXsruKgsb = true;}
      if(ykBJHpYVsG == qRHgDylPEy){uVVfVZNrNX = true;}
      if(ZgXNbZFlWE == rznTrVkJgD){rOoqrpIClt = true;}
      while(HgLtXQNrCc == tKlpmohRyc){NCKObtVCmk = true;}
      while(qRHgDylPEy == qRHgDylPEy){jtKUXKnbQe = true;}
      while(rznTrVkJgD == rznTrVkJgD){QCPLLpWuRM = true;}
      if(MFIxYbZPHY == true){MFIxYbZPHY = false;}
      if(dqkQwWpfUP == true){dqkQwWpfUP = false;}
      if(RSMNbIsrBB == true){RSMNbIsrBB = false;}
      if(eDKzQlJKHa == true){eDKzQlJKHa = false;}
      if(XWIeUANWWV == true){XWIeUANWWV = false;}
      if(fFoRlsstUQ == true){fFoRlsstUQ = false;}
      if(ihNFsZglzK == true){ihNFsZglzK = false;}
      if(MfXsruKgsb == true){MfXsruKgsb = false;}
      if(uVVfVZNrNX == true){uVVfVZNrNX = false;}
      if(rOoqrpIClt == true){rOoqrpIClt = false;}
      if(SaXLIAhuZp == true){SaXLIAhuZp = false;}
      if(iLAsVMMhjT == true){iLAsVMMhjT = false;}
      if(MnYbRypgAB == true){MnYbRypgAB = false;}
      if(lHuyITyJWV == true){lHuyITyJWV = false;}
      if(qRSWngNuVf == true){qRSWngNuVf = false;}
      if(daSShdCusK == true){daSShdCusK = false;}
      if(JBuXEbQCjB == true){JBuXEbQCjB = false;}
      if(NCKObtVCmk == true){NCKObtVCmk = false;}
      if(jtKUXKnbQe == true){jtKUXKnbQe = false;}
      if(QCPLLpWuRM == true){QCPLLpWuRM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZKFTVHLQQ
{ 
  void AFeILejhsE()
  { 
      bool xctkmFSYKU = false;
      bool JVxoofEwIS = false;
      bool eeErPzIbEw = false;
      bool bEfaaOgUcG = false;
      bool wecRofsRwS = false;
      bool WCPFASXCUm = false;
      bool wqTOrEpWOZ = false;
      bool zjTBVzBmDi = false;
      bool GpelYZoZaH = false;
      bool qezpJELOZj = false;
      bool pWCVTliNiA = false;
      bool QkzkgFLhoR = false;
      bool PPuHiTkdrR = false;
      bool mmMSsinJRm = false;
      bool qbpZpFfNID = false;
      bool rdYHUZaulz = false;
      bool BFVRNdXfry = false;
      bool RCPCamZVQd = false;
      bool nWUnYJNFxT = false;
      bool HrWSklGXMM = false;
      string rYDsFlfqax;
      string sHONDlTTXK;
      string EEULUtjUDi;
      string hjpTQJioKP;
      string TyhGsZfTwt;
      string CcPtjmDqXK;
      string BKnrOIRtxt;
      string CeIIqGWNSt;
      string OQXJfFTujd;
      string FrQzOIKorj;
      string IkWCqXTHDd;
      string PoYdwjleMJ;
      string nVKTnKOJth;
      string ugVhlctVRI;
      string lMrGNQSlDd;
      string VfchwmaDNg;
      string IKNUhiSpqS;
      string pQMEXbcEFX;
      string qbFQLPEnlz;
      string CqHkzbzXXe;
      if(rYDsFlfqax == IkWCqXTHDd){xctkmFSYKU = true;}
      else if(IkWCqXTHDd == rYDsFlfqax){pWCVTliNiA = true;}
      if(sHONDlTTXK == PoYdwjleMJ){JVxoofEwIS = true;}
      else if(PoYdwjleMJ == sHONDlTTXK){QkzkgFLhoR = true;}
      if(EEULUtjUDi == nVKTnKOJth){eeErPzIbEw = true;}
      else if(nVKTnKOJth == EEULUtjUDi){PPuHiTkdrR = true;}
      if(hjpTQJioKP == ugVhlctVRI){bEfaaOgUcG = true;}
      else if(ugVhlctVRI == hjpTQJioKP){mmMSsinJRm = true;}
      if(TyhGsZfTwt == lMrGNQSlDd){wecRofsRwS = true;}
      else if(lMrGNQSlDd == TyhGsZfTwt){qbpZpFfNID = true;}
      if(CcPtjmDqXK == VfchwmaDNg){WCPFASXCUm = true;}
      else if(VfchwmaDNg == CcPtjmDqXK){rdYHUZaulz = true;}
      if(BKnrOIRtxt == IKNUhiSpqS){wqTOrEpWOZ = true;}
      else if(IKNUhiSpqS == BKnrOIRtxt){BFVRNdXfry = true;}
      if(CeIIqGWNSt == pQMEXbcEFX){zjTBVzBmDi = true;}
      if(OQXJfFTujd == qbFQLPEnlz){GpelYZoZaH = true;}
      if(FrQzOIKorj == CqHkzbzXXe){qezpJELOZj = true;}
      while(pQMEXbcEFX == CeIIqGWNSt){RCPCamZVQd = true;}
      while(qbFQLPEnlz == qbFQLPEnlz){nWUnYJNFxT = true;}
      while(CqHkzbzXXe == CqHkzbzXXe){HrWSklGXMM = true;}
      if(xctkmFSYKU == true){xctkmFSYKU = false;}
      if(JVxoofEwIS == true){JVxoofEwIS = false;}
      if(eeErPzIbEw == true){eeErPzIbEw = false;}
      if(bEfaaOgUcG == true){bEfaaOgUcG = false;}
      if(wecRofsRwS == true){wecRofsRwS = false;}
      if(WCPFASXCUm == true){WCPFASXCUm = false;}
      if(wqTOrEpWOZ == true){wqTOrEpWOZ = false;}
      if(zjTBVzBmDi == true){zjTBVzBmDi = false;}
      if(GpelYZoZaH == true){GpelYZoZaH = false;}
      if(qezpJELOZj == true){qezpJELOZj = false;}
      if(pWCVTliNiA == true){pWCVTliNiA = false;}
      if(QkzkgFLhoR == true){QkzkgFLhoR = false;}
      if(PPuHiTkdrR == true){PPuHiTkdrR = false;}
      if(mmMSsinJRm == true){mmMSsinJRm = false;}
      if(qbpZpFfNID == true){qbpZpFfNID = false;}
      if(rdYHUZaulz == true){rdYHUZaulz = false;}
      if(BFVRNdXfry == true){BFVRNdXfry = false;}
      if(RCPCamZVQd == true){RCPCamZVQd = false;}
      if(nWUnYJNFxT == true){nWUnYJNFxT = false;}
      if(HrWSklGXMM == true){HrWSklGXMM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WKRDRENDSW
{ 
  void tnxTSJwTRk()
  { 
      bool uPQOhZkusR = false;
      bool xQFwaeXuun = false;
      bool cqOcVtrGBT = false;
      bool QdPqENByDM = false;
      bool StDPEZInZe = false;
      bool NdFKJDBnrm = false;
      bool getZBTBOrN = false;
      bool cZrhUimzXw = false;
      bool lEfWFlXEhA = false;
      bool LNFPenAdNk = false;
      bool YswMBnlWpZ = false;
      bool QBPwAbyXTO = false;
      bool wwfqBPTbDg = false;
      bool iJkmWrHSUR = false;
      bool AAOHjKxIPC = false;
      bool obJynbMELk = false;
      bool UJTJqGQbZI = false;
      bool UfCCOuhYHq = false;
      bool RKMAqGAlyu = false;
      bool eDHjxpfFPd = false;
      string TofAcMNupC;
      string DtWNcLIDuo;
      string cgeDWkoqfE;
      string ZudgIbZkDV;
      string kWKFLDbXef;
      string jahZxlJcdr;
      string XWOlbIPpFA;
      string lXAZDGVZrS;
      string IQLATyNDiV;
      string SwHLyOHYcC;
      string nlSdtMaHVq;
      string PjkKiGKORd;
      string uLGihoPobo;
      string yxwoeWxgGG;
      string XFgrFhLxbq;
      string DsGzHbeiwE;
      string xkfgsSmwfM;
      string IdIKFpdOdz;
      string cSNklEpwgC;
      string qOkBJlYAzl;
      if(TofAcMNupC == nlSdtMaHVq){uPQOhZkusR = true;}
      else if(nlSdtMaHVq == TofAcMNupC){YswMBnlWpZ = true;}
      if(DtWNcLIDuo == PjkKiGKORd){xQFwaeXuun = true;}
      else if(PjkKiGKORd == DtWNcLIDuo){QBPwAbyXTO = true;}
      if(cgeDWkoqfE == uLGihoPobo){cqOcVtrGBT = true;}
      else if(uLGihoPobo == cgeDWkoqfE){wwfqBPTbDg = true;}
      if(ZudgIbZkDV == yxwoeWxgGG){QdPqENByDM = true;}
      else if(yxwoeWxgGG == ZudgIbZkDV){iJkmWrHSUR = true;}
      if(kWKFLDbXef == XFgrFhLxbq){StDPEZInZe = true;}
      else if(XFgrFhLxbq == kWKFLDbXef){AAOHjKxIPC = true;}
      if(jahZxlJcdr == DsGzHbeiwE){NdFKJDBnrm = true;}
      else if(DsGzHbeiwE == jahZxlJcdr){obJynbMELk = true;}
      if(XWOlbIPpFA == xkfgsSmwfM){getZBTBOrN = true;}
      else if(xkfgsSmwfM == XWOlbIPpFA){UJTJqGQbZI = true;}
      if(lXAZDGVZrS == IdIKFpdOdz){cZrhUimzXw = true;}
      if(IQLATyNDiV == cSNklEpwgC){lEfWFlXEhA = true;}
      if(SwHLyOHYcC == qOkBJlYAzl){LNFPenAdNk = true;}
      while(IdIKFpdOdz == lXAZDGVZrS){UfCCOuhYHq = true;}
      while(cSNklEpwgC == cSNklEpwgC){RKMAqGAlyu = true;}
      while(qOkBJlYAzl == qOkBJlYAzl){eDHjxpfFPd = true;}
      if(uPQOhZkusR == true){uPQOhZkusR = false;}
      if(xQFwaeXuun == true){xQFwaeXuun = false;}
      if(cqOcVtrGBT == true){cqOcVtrGBT = false;}
      if(QdPqENByDM == true){QdPqENByDM = false;}
      if(StDPEZInZe == true){StDPEZInZe = false;}
      if(NdFKJDBnrm == true){NdFKJDBnrm = false;}
      if(getZBTBOrN == true){getZBTBOrN = false;}
      if(cZrhUimzXw == true){cZrhUimzXw = false;}
      if(lEfWFlXEhA == true){lEfWFlXEhA = false;}
      if(LNFPenAdNk == true){LNFPenAdNk = false;}
      if(YswMBnlWpZ == true){YswMBnlWpZ = false;}
      if(QBPwAbyXTO == true){QBPwAbyXTO = false;}
      if(wwfqBPTbDg == true){wwfqBPTbDg = false;}
      if(iJkmWrHSUR == true){iJkmWrHSUR = false;}
      if(AAOHjKxIPC == true){AAOHjKxIPC = false;}
      if(obJynbMELk == true){obJynbMELk = false;}
      if(UJTJqGQbZI == true){UJTJqGQbZI = false;}
      if(UfCCOuhYHq == true){UfCCOuhYHq = false;}
      if(RKMAqGAlyu == true){RKMAqGAlyu = false;}
      if(eDHjxpfFPd == true){eDHjxpfFPd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYPIAAHITT
{ 
  void PaBASusERc()
  { 
      bool pWtSrWcaCr = false;
      bool mdFXeLVnOl = false;
      bool rmpzKMYwTW = false;
      bool CtKmPbabkG = false;
      bool ZriuVsIkFz = false;
      bool JLMPLCfuHe = false;
      bool xgHeprTRHC = false;
      bool ksCIMADucR = false;
      bool EnpTMphtbM = false;
      bool wfUFIrjEEc = false;
      bool YqcCOPIDDL = false;
      bool yjRpaJpnRz = false;
      bool KZpuGEYxzT = false;
      bool PzqArNKnFx = false;
      bool hdpPOLOdez = false;
      bool BwlESzAhuJ = false;
      bool pLEiuysRyN = false;
      bool zBhURfiZft = false;
      bool puRARSNlgs = false;
      bool MbsuGVZGTP = false;
      string weeeKmqSgj;
      string FzKDynXFMj;
      string FGPSnCilgJ;
      string XCUMrwZUHJ;
      string doCSTZrRBp;
      string JLSeSpOLpH;
      string DFkXMDdxLC;
      string NDxDGQExzO;
      string JRkqzLipsC;
      string gNeAFYDdFP;
      string wtGycGOPYC;
      string lRMaylTtXA;
      string UmDIVzYxxg;
      string MZqiSOLlNs;
      string xSRqQPADBT;
      string EJGFuIqxcd;
      string gRSqoLZdIi;
      string ahfeCCUMrF;
      string yVudcDTlmJ;
      string XNIjLfAaCE;
      if(weeeKmqSgj == wtGycGOPYC){pWtSrWcaCr = true;}
      else if(wtGycGOPYC == weeeKmqSgj){YqcCOPIDDL = true;}
      if(FzKDynXFMj == lRMaylTtXA){mdFXeLVnOl = true;}
      else if(lRMaylTtXA == FzKDynXFMj){yjRpaJpnRz = true;}
      if(FGPSnCilgJ == UmDIVzYxxg){rmpzKMYwTW = true;}
      else if(UmDIVzYxxg == FGPSnCilgJ){KZpuGEYxzT = true;}
      if(XCUMrwZUHJ == MZqiSOLlNs){CtKmPbabkG = true;}
      else if(MZqiSOLlNs == XCUMrwZUHJ){PzqArNKnFx = true;}
      if(doCSTZrRBp == xSRqQPADBT){ZriuVsIkFz = true;}
      else if(xSRqQPADBT == doCSTZrRBp){hdpPOLOdez = true;}
      if(JLSeSpOLpH == EJGFuIqxcd){JLMPLCfuHe = true;}
      else if(EJGFuIqxcd == JLSeSpOLpH){BwlESzAhuJ = true;}
      if(DFkXMDdxLC == gRSqoLZdIi){xgHeprTRHC = true;}
      else if(gRSqoLZdIi == DFkXMDdxLC){pLEiuysRyN = true;}
      if(NDxDGQExzO == ahfeCCUMrF){ksCIMADucR = true;}
      if(JRkqzLipsC == yVudcDTlmJ){EnpTMphtbM = true;}
      if(gNeAFYDdFP == XNIjLfAaCE){wfUFIrjEEc = true;}
      while(ahfeCCUMrF == NDxDGQExzO){zBhURfiZft = true;}
      while(yVudcDTlmJ == yVudcDTlmJ){puRARSNlgs = true;}
      while(XNIjLfAaCE == XNIjLfAaCE){MbsuGVZGTP = true;}
      if(pWtSrWcaCr == true){pWtSrWcaCr = false;}
      if(mdFXeLVnOl == true){mdFXeLVnOl = false;}
      if(rmpzKMYwTW == true){rmpzKMYwTW = false;}
      if(CtKmPbabkG == true){CtKmPbabkG = false;}
      if(ZriuVsIkFz == true){ZriuVsIkFz = false;}
      if(JLMPLCfuHe == true){JLMPLCfuHe = false;}
      if(xgHeprTRHC == true){xgHeprTRHC = false;}
      if(ksCIMADucR == true){ksCIMADucR = false;}
      if(EnpTMphtbM == true){EnpTMphtbM = false;}
      if(wfUFIrjEEc == true){wfUFIrjEEc = false;}
      if(YqcCOPIDDL == true){YqcCOPIDDL = false;}
      if(yjRpaJpnRz == true){yjRpaJpnRz = false;}
      if(KZpuGEYxzT == true){KZpuGEYxzT = false;}
      if(PzqArNKnFx == true){PzqArNKnFx = false;}
      if(hdpPOLOdez == true){hdpPOLOdez = false;}
      if(BwlESzAhuJ == true){BwlESzAhuJ = false;}
      if(pLEiuysRyN == true){pLEiuysRyN = false;}
      if(zBhURfiZft == true){zBhURfiZft = false;}
      if(puRARSNlgs == true){puRARSNlgs = false;}
      if(MbsuGVZGTP == true){MbsuGVZGTP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NILWFERXOQ
{ 
  void BTXOVmOLTT()
  { 
      bool ZLYiIyYpVl = false;
      bool GpmdyAbsxe = false;
      bool EEzwFAxHyB = false;
      bool qqyEnLzzqP = false;
      bool GTgxnZcina = false;
      bool CDEQOUMccH = false;
      bool BRrUtPqiol = false;
      bool AbCgXkXBHe = false;
      bool XOSWznlgpT = false;
      bool zWViNobMDY = false;
      bool htsBaZAWsd = false;
      bool xLUxjlyUUG = false;
      bool cKsVmcFSTh = false;
      bool IKyixcUQwY = false;
      bool mPnLVnCXzb = false;
      bool qHqwuXBXOx = false;
      bool UhDKUlMkAG = false;
      bool QgYuTNVgzz = false;
      bool agSqqBTBmY = false;
      bool bxCyEELcqi = false;
      string zffstZcpCu;
      string KaKERMdoBa;
      string lswQHnmVrP;
      string rUYsbcEneH;
      string fScXxGCscw;
      string CHLdcFjOlF;
      string mHymDoBRco;
      string IpKsuSQXTA;
      string ksrwMjIuQW;
      string spBYTXUpTH;
      string FkQnnMwShJ;
      string oLulUtOBZS;
      string fFBFuRnlYW;
      string yZELtzbEHA;
      string npMGhgtPDZ;
      string ISPBbzjLrV;
      string YKsLKOHiqU;
      string RJsZeostXO;
      string XXhzNfJCju;
      string PQMlbdxBwS;
      if(zffstZcpCu == FkQnnMwShJ){ZLYiIyYpVl = true;}
      else if(FkQnnMwShJ == zffstZcpCu){htsBaZAWsd = true;}
      if(KaKERMdoBa == oLulUtOBZS){GpmdyAbsxe = true;}
      else if(oLulUtOBZS == KaKERMdoBa){xLUxjlyUUG = true;}
      if(lswQHnmVrP == fFBFuRnlYW){EEzwFAxHyB = true;}
      else if(fFBFuRnlYW == lswQHnmVrP){cKsVmcFSTh = true;}
      if(rUYsbcEneH == yZELtzbEHA){qqyEnLzzqP = true;}
      else if(yZELtzbEHA == rUYsbcEneH){IKyixcUQwY = true;}
      if(fScXxGCscw == npMGhgtPDZ){GTgxnZcina = true;}
      else if(npMGhgtPDZ == fScXxGCscw){mPnLVnCXzb = true;}
      if(CHLdcFjOlF == ISPBbzjLrV){CDEQOUMccH = true;}
      else if(ISPBbzjLrV == CHLdcFjOlF){qHqwuXBXOx = true;}
      if(mHymDoBRco == YKsLKOHiqU){BRrUtPqiol = true;}
      else if(YKsLKOHiqU == mHymDoBRco){UhDKUlMkAG = true;}
      if(IpKsuSQXTA == RJsZeostXO){AbCgXkXBHe = true;}
      if(ksrwMjIuQW == XXhzNfJCju){XOSWznlgpT = true;}
      if(spBYTXUpTH == PQMlbdxBwS){zWViNobMDY = true;}
      while(RJsZeostXO == IpKsuSQXTA){QgYuTNVgzz = true;}
      while(XXhzNfJCju == XXhzNfJCju){agSqqBTBmY = true;}
      while(PQMlbdxBwS == PQMlbdxBwS){bxCyEELcqi = true;}
      if(ZLYiIyYpVl == true){ZLYiIyYpVl = false;}
      if(GpmdyAbsxe == true){GpmdyAbsxe = false;}
      if(EEzwFAxHyB == true){EEzwFAxHyB = false;}
      if(qqyEnLzzqP == true){qqyEnLzzqP = false;}
      if(GTgxnZcina == true){GTgxnZcina = false;}
      if(CDEQOUMccH == true){CDEQOUMccH = false;}
      if(BRrUtPqiol == true){BRrUtPqiol = false;}
      if(AbCgXkXBHe == true){AbCgXkXBHe = false;}
      if(XOSWznlgpT == true){XOSWznlgpT = false;}
      if(zWViNobMDY == true){zWViNobMDY = false;}
      if(htsBaZAWsd == true){htsBaZAWsd = false;}
      if(xLUxjlyUUG == true){xLUxjlyUUG = false;}
      if(cKsVmcFSTh == true){cKsVmcFSTh = false;}
      if(IKyixcUQwY == true){IKyixcUQwY = false;}
      if(mPnLVnCXzb == true){mPnLVnCXzb = false;}
      if(qHqwuXBXOx == true){qHqwuXBXOx = false;}
      if(UhDKUlMkAG == true){UhDKUlMkAG = false;}
      if(QgYuTNVgzz == true){QgYuTNVgzz = false;}
      if(agSqqBTBmY == true){agSqqBTBmY = false;}
      if(bxCyEELcqi == true){bxCyEELcqi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVLAXVMINW
{ 
  void xMbBzFRbyl()
  { 
      bool hkTKTAYMwl = false;
      bool naEXdfuiUE = false;
      bool yzpPFMOoBw = false;
      bool PMlGWZpQYZ = false;
      bool rPRgoixQEn = false;
      bool rlmKXhtEEG = false;
      bool ljKAWanxBD = false;
      bool oeKuLigIaW = false;
      bool PyjNEcZahn = false;
      bool flLRmIERKN = false;
      bool tzOByNaqyo = false;
      bool BkchpnAxus = false;
      bool BMPMXDSrHD = false;
      bool eOyMbQiiPq = false;
      bool ChcsmuIdaz = false;
      bool HHWQMhiBdt = false;
      bool tijtJllQGZ = false;
      bool ERhEqSjWZb = false;
      bool uoQIuXrgzs = false;
      bool ggEUwSxhiB = false;
      string wpUzgDwgEF;
      string oPZDhpFHdz;
      string QmPbCcMdQB;
      string fJMPrcooeW;
      string sIPxijaUhx;
      string dzKgrIZsxD;
      string pRPCZfCKKE;
      string BPbHGHXRsS;
      string CrwTXgzeWi;
      string DurafasMXC;
      string gPJduNWCak;
      string kHAeBxVwes;
      string fXmbAGXAae;
      string OKspkliRXJ;
      string JwDlyuuNZh;
      string ExheVIbhco;
      string pVbuVaNKsP;
      string ODXUijUBcE;
      string KKaraRbOTc;
      string JBoiTmUHPW;
      if(wpUzgDwgEF == gPJduNWCak){hkTKTAYMwl = true;}
      else if(gPJduNWCak == wpUzgDwgEF){tzOByNaqyo = true;}
      if(oPZDhpFHdz == kHAeBxVwes){naEXdfuiUE = true;}
      else if(kHAeBxVwes == oPZDhpFHdz){BkchpnAxus = true;}
      if(QmPbCcMdQB == fXmbAGXAae){yzpPFMOoBw = true;}
      else if(fXmbAGXAae == QmPbCcMdQB){BMPMXDSrHD = true;}
      if(fJMPrcooeW == OKspkliRXJ){PMlGWZpQYZ = true;}
      else if(OKspkliRXJ == fJMPrcooeW){eOyMbQiiPq = true;}
      if(sIPxijaUhx == JwDlyuuNZh){rPRgoixQEn = true;}
      else if(JwDlyuuNZh == sIPxijaUhx){ChcsmuIdaz = true;}
      if(dzKgrIZsxD == ExheVIbhco){rlmKXhtEEG = true;}
      else if(ExheVIbhco == dzKgrIZsxD){HHWQMhiBdt = true;}
      if(pRPCZfCKKE == pVbuVaNKsP){ljKAWanxBD = true;}
      else if(pVbuVaNKsP == pRPCZfCKKE){tijtJllQGZ = true;}
      if(BPbHGHXRsS == ODXUijUBcE){oeKuLigIaW = true;}
      if(CrwTXgzeWi == KKaraRbOTc){PyjNEcZahn = true;}
      if(DurafasMXC == JBoiTmUHPW){flLRmIERKN = true;}
      while(ODXUijUBcE == BPbHGHXRsS){ERhEqSjWZb = true;}
      while(KKaraRbOTc == KKaraRbOTc){uoQIuXrgzs = true;}
      while(JBoiTmUHPW == JBoiTmUHPW){ggEUwSxhiB = true;}
      if(hkTKTAYMwl == true){hkTKTAYMwl = false;}
      if(naEXdfuiUE == true){naEXdfuiUE = false;}
      if(yzpPFMOoBw == true){yzpPFMOoBw = false;}
      if(PMlGWZpQYZ == true){PMlGWZpQYZ = false;}
      if(rPRgoixQEn == true){rPRgoixQEn = false;}
      if(rlmKXhtEEG == true){rlmKXhtEEG = false;}
      if(ljKAWanxBD == true){ljKAWanxBD = false;}
      if(oeKuLigIaW == true){oeKuLigIaW = false;}
      if(PyjNEcZahn == true){PyjNEcZahn = false;}
      if(flLRmIERKN == true){flLRmIERKN = false;}
      if(tzOByNaqyo == true){tzOByNaqyo = false;}
      if(BkchpnAxus == true){BkchpnAxus = false;}
      if(BMPMXDSrHD == true){BMPMXDSrHD = false;}
      if(eOyMbQiiPq == true){eOyMbQiiPq = false;}
      if(ChcsmuIdaz == true){ChcsmuIdaz = false;}
      if(HHWQMhiBdt == true){HHWQMhiBdt = false;}
      if(tijtJllQGZ == true){tijtJllQGZ = false;}
      if(ERhEqSjWZb == true){ERhEqSjWZb = false;}
      if(uoQIuXrgzs == true){uoQIuXrgzs = false;}
      if(ggEUwSxhiB == true){ggEUwSxhiB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYSKTCBHKK
{ 
  void gmynVmaAjL()
  { 
      bool WEiVFjdjbs = false;
      bool tzgiAmNkbi = false;
      bool DZwwbNRQPr = false;
      bool FgxoLpUSOD = false;
      bool BGnxdVlien = false;
      bool kmypjwIlsr = false;
      bool SMUimMBqXK = false;
      bool RtVYhwlySG = false;
      bool ahlaGSiHEO = false;
      bool hiYWkolEJR = false;
      bool TuLUWqRZHn = false;
      bool JJTmQjascU = false;
      bool cslIbhUymr = false;
      bool KgoAlfWQEP = false;
      bool BJzQEXPlGB = false;
      bool NrbnnaICrn = false;
      bool VSlOdbTSAk = false;
      bool NJoMTTsVDE = false;
      bool SiqleRFAML = false;
      bool WUYPthWjmc = false;
      string WpUOndFIEt;
      string KzJFlTheLE;
      string pLTZqbUmYc;
      string lLkmDGnYRF;
      string GiKWeODWqO;
      string JXTVcKVuXL;
      string IRibIzNVCe;
      string fJNFxGAxtb;
      string XxwKSNqOKr;
      string ksAFxoAiOf;
      string BhULiAKNXV;
      string KYBwmKUYIt;
      string HyLKtmIHHI;
      string GQiOapcjbS;
      string CdpngMqESm;
      string UaZTXCVJRw;
      string qDFPOsomVw;
      string gjxprdHWch;
      string uEoUnfpPpY;
      string UTSfazXaYm;
      if(WpUOndFIEt == BhULiAKNXV){WEiVFjdjbs = true;}
      else if(BhULiAKNXV == WpUOndFIEt){TuLUWqRZHn = true;}
      if(KzJFlTheLE == KYBwmKUYIt){tzgiAmNkbi = true;}
      else if(KYBwmKUYIt == KzJFlTheLE){JJTmQjascU = true;}
      if(pLTZqbUmYc == HyLKtmIHHI){DZwwbNRQPr = true;}
      else if(HyLKtmIHHI == pLTZqbUmYc){cslIbhUymr = true;}
      if(lLkmDGnYRF == GQiOapcjbS){FgxoLpUSOD = true;}
      else if(GQiOapcjbS == lLkmDGnYRF){KgoAlfWQEP = true;}
      if(GiKWeODWqO == CdpngMqESm){BGnxdVlien = true;}
      else if(CdpngMqESm == GiKWeODWqO){BJzQEXPlGB = true;}
      if(JXTVcKVuXL == UaZTXCVJRw){kmypjwIlsr = true;}
      else if(UaZTXCVJRw == JXTVcKVuXL){NrbnnaICrn = true;}
      if(IRibIzNVCe == qDFPOsomVw){SMUimMBqXK = true;}
      else if(qDFPOsomVw == IRibIzNVCe){VSlOdbTSAk = true;}
      if(fJNFxGAxtb == gjxprdHWch){RtVYhwlySG = true;}
      if(XxwKSNqOKr == uEoUnfpPpY){ahlaGSiHEO = true;}
      if(ksAFxoAiOf == UTSfazXaYm){hiYWkolEJR = true;}
      while(gjxprdHWch == fJNFxGAxtb){NJoMTTsVDE = true;}
      while(uEoUnfpPpY == uEoUnfpPpY){SiqleRFAML = true;}
      while(UTSfazXaYm == UTSfazXaYm){WUYPthWjmc = true;}
      if(WEiVFjdjbs == true){WEiVFjdjbs = false;}
      if(tzgiAmNkbi == true){tzgiAmNkbi = false;}
      if(DZwwbNRQPr == true){DZwwbNRQPr = false;}
      if(FgxoLpUSOD == true){FgxoLpUSOD = false;}
      if(BGnxdVlien == true){BGnxdVlien = false;}
      if(kmypjwIlsr == true){kmypjwIlsr = false;}
      if(SMUimMBqXK == true){SMUimMBqXK = false;}
      if(RtVYhwlySG == true){RtVYhwlySG = false;}
      if(ahlaGSiHEO == true){ahlaGSiHEO = false;}
      if(hiYWkolEJR == true){hiYWkolEJR = false;}
      if(TuLUWqRZHn == true){TuLUWqRZHn = false;}
      if(JJTmQjascU == true){JJTmQjascU = false;}
      if(cslIbhUymr == true){cslIbhUymr = false;}
      if(KgoAlfWQEP == true){KgoAlfWQEP = false;}
      if(BJzQEXPlGB == true){BJzQEXPlGB = false;}
      if(NrbnnaICrn == true){NrbnnaICrn = false;}
      if(VSlOdbTSAk == true){VSlOdbTSAk = false;}
      if(NJoMTTsVDE == true){NJoMTTsVDE = false;}
      if(SiqleRFAML == true){SiqleRFAML = false;}
      if(WUYPthWjmc == true){WUYPthWjmc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTOTHQGZKZ
{ 
  void QBRfkEaSEC()
  { 
      bool TdZoZUaZGA = false;
      bool zuHOPlEGfV = false;
      bool mopIlAyOpw = false;
      bool kbSmqwAorO = false;
      bool sTmnpKnZxp = false;
      bool QYrkoemQDY = false;
      bool WLjKPXcTWS = false;
      bool kPOQcSCBSb = false;
      bool MXRAfMigxM = false;
      bool IilSqgicYS = false;
      bool hTCdEAKaHV = false;
      bool ckybMztidC = false;
      bool nuWKKCduZu = false;
      bool iZczsrVnwe = false;
      bool CIZajWkKGr = false;
      bool mAyVelxrTC = false;
      bool WOAMlDIyhT = false;
      bool cFmzAeVuam = false;
      bool QSnhHiaGUH = false;
      bool ucTtHmHNof = false;
      string sWhLdfSgZP;
      string fnMfWzopiT;
      string ooQGwsFKbV;
      string yyFdfHVchK;
      string RkDIQUasFB;
      string WBjJREGaPj;
      string ZHEEQghizP;
      string dMIXCEkHoa;
      string SLFZywOuLb;
      string BtNyjKgyqj;
      string lrtoXKsLHN;
      string SyknROCdGT;
      string SmXXOiyKmr;
      string WlPFoZRPBm;
      string DCmxICIYfV;
      string HCrWQzUVao;
      string LhXPpfhezq;
      string wlbSQPzZOL;
      string ZZdRjTssop;
      string FunMbUeXHb;
      if(sWhLdfSgZP == lrtoXKsLHN){TdZoZUaZGA = true;}
      else if(lrtoXKsLHN == sWhLdfSgZP){hTCdEAKaHV = true;}
      if(fnMfWzopiT == SyknROCdGT){zuHOPlEGfV = true;}
      else if(SyknROCdGT == fnMfWzopiT){ckybMztidC = true;}
      if(ooQGwsFKbV == SmXXOiyKmr){mopIlAyOpw = true;}
      else if(SmXXOiyKmr == ooQGwsFKbV){nuWKKCduZu = true;}
      if(yyFdfHVchK == WlPFoZRPBm){kbSmqwAorO = true;}
      else if(WlPFoZRPBm == yyFdfHVchK){iZczsrVnwe = true;}
      if(RkDIQUasFB == DCmxICIYfV){sTmnpKnZxp = true;}
      else if(DCmxICIYfV == RkDIQUasFB){CIZajWkKGr = true;}
      if(WBjJREGaPj == HCrWQzUVao){QYrkoemQDY = true;}
      else if(HCrWQzUVao == WBjJREGaPj){mAyVelxrTC = true;}
      if(ZHEEQghizP == LhXPpfhezq){WLjKPXcTWS = true;}
      else if(LhXPpfhezq == ZHEEQghizP){WOAMlDIyhT = true;}
      if(dMIXCEkHoa == wlbSQPzZOL){kPOQcSCBSb = true;}
      if(SLFZywOuLb == ZZdRjTssop){MXRAfMigxM = true;}
      if(BtNyjKgyqj == FunMbUeXHb){IilSqgicYS = true;}
      while(wlbSQPzZOL == dMIXCEkHoa){cFmzAeVuam = true;}
      while(ZZdRjTssop == ZZdRjTssop){QSnhHiaGUH = true;}
      while(FunMbUeXHb == FunMbUeXHb){ucTtHmHNof = true;}
      if(TdZoZUaZGA == true){TdZoZUaZGA = false;}
      if(zuHOPlEGfV == true){zuHOPlEGfV = false;}
      if(mopIlAyOpw == true){mopIlAyOpw = false;}
      if(kbSmqwAorO == true){kbSmqwAorO = false;}
      if(sTmnpKnZxp == true){sTmnpKnZxp = false;}
      if(QYrkoemQDY == true){QYrkoemQDY = false;}
      if(WLjKPXcTWS == true){WLjKPXcTWS = false;}
      if(kPOQcSCBSb == true){kPOQcSCBSb = false;}
      if(MXRAfMigxM == true){MXRAfMigxM = false;}
      if(IilSqgicYS == true){IilSqgicYS = false;}
      if(hTCdEAKaHV == true){hTCdEAKaHV = false;}
      if(ckybMztidC == true){ckybMztidC = false;}
      if(nuWKKCduZu == true){nuWKKCduZu = false;}
      if(iZczsrVnwe == true){iZczsrVnwe = false;}
      if(CIZajWkKGr == true){CIZajWkKGr = false;}
      if(mAyVelxrTC == true){mAyVelxrTC = false;}
      if(WOAMlDIyhT == true){WOAMlDIyhT = false;}
      if(cFmzAeVuam == true){cFmzAeVuam = false;}
      if(QSnhHiaGUH == true){QSnhHiaGUH = false;}
      if(ucTtHmHNof == true){ucTtHmHNof = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEPOCMVULK
{ 
  void WQOITXCLZB()
  { 
      bool iLeJSmTMwH = false;
      bool azmWXhEgmR = false;
      bool xnhLhcjYGt = false;
      bool XTbIKSywDY = false;
      bool KogfTPEtgH = false;
      bool tMADhudSap = false;
      bool CuGCjHXeLF = false;
      bool jHcOHIGCrS = false;
      bool YpryzKTYZO = false;
      bool oeUNWPieuL = false;
      bool rYhaXljkwZ = false;
      bool obaIRMDICZ = false;
      bool myEwPEmOrq = false;
      bool YaGfazHQZN = false;
      bool aibAZNEMwK = false;
      bool MZcVYsUkKT = false;
      bool zUsFAOUthS = false;
      bool EmhoyEWEWC = false;
      bool AaSgeyxkGg = false;
      bool dVFGNGoWzL = false;
      string pwpOpcKfTi;
      string htnpTdArMX;
      string HHwIVBZiUp;
      string tJLdblyOJc;
      string yulhKMYKqu;
      string MJyYlhzhro;
      string CaLcnXhJOg;
      string ekijYMVNyI;
      string cPqYdjKmrs;
      string lQVUZXjItl;
      string dOwKQaZNAZ;
      string MlijLmilzD;
      string NuQUtNPOKA;
      string bMTMdNSgIC;
      string KwmSfAhkIm;
      string nxJpYiybPD;
      string LLDzxARVGy;
      string TBdwsQHyns;
      string edGWLeCdnt;
      string PqQEpzsmVf;
      if(pwpOpcKfTi == dOwKQaZNAZ){iLeJSmTMwH = true;}
      else if(dOwKQaZNAZ == pwpOpcKfTi){rYhaXljkwZ = true;}
      if(htnpTdArMX == MlijLmilzD){azmWXhEgmR = true;}
      else if(MlijLmilzD == htnpTdArMX){obaIRMDICZ = true;}
      if(HHwIVBZiUp == NuQUtNPOKA){xnhLhcjYGt = true;}
      else if(NuQUtNPOKA == HHwIVBZiUp){myEwPEmOrq = true;}
      if(tJLdblyOJc == bMTMdNSgIC){XTbIKSywDY = true;}
      else if(bMTMdNSgIC == tJLdblyOJc){YaGfazHQZN = true;}
      if(yulhKMYKqu == KwmSfAhkIm){KogfTPEtgH = true;}
      else if(KwmSfAhkIm == yulhKMYKqu){aibAZNEMwK = true;}
      if(MJyYlhzhro == nxJpYiybPD){tMADhudSap = true;}
      else if(nxJpYiybPD == MJyYlhzhro){MZcVYsUkKT = true;}
      if(CaLcnXhJOg == LLDzxARVGy){CuGCjHXeLF = true;}
      else if(LLDzxARVGy == CaLcnXhJOg){zUsFAOUthS = true;}
      if(ekijYMVNyI == TBdwsQHyns){jHcOHIGCrS = true;}
      if(cPqYdjKmrs == edGWLeCdnt){YpryzKTYZO = true;}
      if(lQVUZXjItl == PqQEpzsmVf){oeUNWPieuL = true;}
      while(TBdwsQHyns == ekijYMVNyI){EmhoyEWEWC = true;}
      while(edGWLeCdnt == edGWLeCdnt){AaSgeyxkGg = true;}
      while(PqQEpzsmVf == PqQEpzsmVf){dVFGNGoWzL = true;}
      if(iLeJSmTMwH == true){iLeJSmTMwH = false;}
      if(azmWXhEgmR == true){azmWXhEgmR = false;}
      if(xnhLhcjYGt == true){xnhLhcjYGt = false;}
      if(XTbIKSywDY == true){XTbIKSywDY = false;}
      if(KogfTPEtgH == true){KogfTPEtgH = false;}
      if(tMADhudSap == true){tMADhudSap = false;}
      if(CuGCjHXeLF == true){CuGCjHXeLF = false;}
      if(jHcOHIGCrS == true){jHcOHIGCrS = false;}
      if(YpryzKTYZO == true){YpryzKTYZO = false;}
      if(oeUNWPieuL == true){oeUNWPieuL = false;}
      if(rYhaXljkwZ == true){rYhaXljkwZ = false;}
      if(obaIRMDICZ == true){obaIRMDICZ = false;}
      if(myEwPEmOrq == true){myEwPEmOrq = false;}
      if(YaGfazHQZN == true){YaGfazHQZN = false;}
      if(aibAZNEMwK == true){aibAZNEMwK = false;}
      if(MZcVYsUkKT == true){MZcVYsUkKT = false;}
      if(zUsFAOUthS == true){zUsFAOUthS = false;}
      if(EmhoyEWEWC == true){EmhoyEWEWC = false;}
      if(AaSgeyxkGg == true){AaSgeyxkGg = false;}
      if(dVFGNGoWzL == true){dVFGNGoWzL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDRDGDUTWJ
{ 
  void FskVNhuNGL()
  { 
      bool wWrYKADIcU = false;
      bool udzqLdDtGl = false;
      bool UKSqOgRrYK = false;
      bool mURpUGoNJm = false;
      bool yrYiwAEAxQ = false;
      bool mLUZwlDAKd = false;
      bool hLiSgaLIWF = false;
      bool nojSmckiuN = false;
      bool bRtIWbAqti = false;
      bool CoDfElIGCU = false;
      bool nwcqbyaBmS = false;
      bool ATEwCPRawE = false;
      bool aTOmCzlENA = false;
      bool UegZYenCgX = false;
      bool AzEahijGco = false;
      bool UhKxtUgpoc = false;
      bool MWmlyVmdXW = false;
      bool bOsXEaOnET = false;
      bool OeaYflTifE = false;
      bool yyNDLdLSbM = false;
      string JGPxxQAjzn;
      string zHizTYNFQn;
      string XfTgjqDCaz;
      string amaFQoSJDG;
      string TMBZmpQmOR;
      string YxnMIcmiNF;
      string NyIzMLfcid;
      string GECJTLesss;
      string ZPmJZcyOxm;
      string CiuxsVDBNa;
      string JnDkLUuerw;
      string ysoTexLyYi;
      string NRewaWIEQy;
      string HcfRjlLBxF;
      string hTVBnJtbRu;
      string KEbdNrIHJn;
      string LpOtoVMWjr;
      string kJBTBswdIR;
      string cgmUnCACEr;
      string dEqItqFaMR;
      if(JGPxxQAjzn == JnDkLUuerw){wWrYKADIcU = true;}
      else if(JnDkLUuerw == JGPxxQAjzn){nwcqbyaBmS = true;}
      if(zHizTYNFQn == ysoTexLyYi){udzqLdDtGl = true;}
      else if(ysoTexLyYi == zHizTYNFQn){ATEwCPRawE = true;}
      if(XfTgjqDCaz == NRewaWIEQy){UKSqOgRrYK = true;}
      else if(NRewaWIEQy == XfTgjqDCaz){aTOmCzlENA = true;}
      if(amaFQoSJDG == HcfRjlLBxF){mURpUGoNJm = true;}
      else if(HcfRjlLBxF == amaFQoSJDG){UegZYenCgX = true;}
      if(TMBZmpQmOR == hTVBnJtbRu){yrYiwAEAxQ = true;}
      else if(hTVBnJtbRu == TMBZmpQmOR){AzEahijGco = true;}
      if(YxnMIcmiNF == KEbdNrIHJn){mLUZwlDAKd = true;}
      else if(KEbdNrIHJn == YxnMIcmiNF){UhKxtUgpoc = true;}
      if(NyIzMLfcid == LpOtoVMWjr){hLiSgaLIWF = true;}
      else if(LpOtoVMWjr == NyIzMLfcid){MWmlyVmdXW = true;}
      if(GECJTLesss == kJBTBswdIR){nojSmckiuN = true;}
      if(ZPmJZcyOxm == cgmUnCACEr){bRtIWbAqti = true;}
      if(CiuxsVDBNa == dEqItqFaMR){CoDfElIGCU = true;}
      while(kJBTBswdIR == GECJTLesss){bOsXEaOnET = true;}
      while(cgmUnCACEr == cgmUnCACEr){OeaYflTifE = true;}
      while(dEqItqFaMR == dEqItqFaMR){yyNDLdLSbM = true;}
      if(wWrYKADIcU == true){wWrYKADIcU = false;}
      if(udzqLdDtGl == true){udzqLdDtGl = false;}
      if(UKSqOgRrYK == true){UKSqOgRrYK = false;}
      if(mURpUGoNJm == true){mURpUGoNJm = false;}
      if(yrYiwAEAxQ == true){yrYiwAEAxQ = false;}
      if(mLUZwlDAKd == true){mLUZwlDAKd = false;}
      if(hLiSgaLIWF == true){hLiSgaLIWF = false;}
      if(nojSmckiuN == true){nojSmckiuN = false;}
      if(bRtIWbAqti == true){bRtIWbAqti = false;}
      if(CoDfElIGCU == true){CoDfElIGCU = false;}
      if(nwcqbyaBmS == true){nwcqbyaBmS = false;}
      if(ATEwCPRawE == true){ATEwCPRawE = false;}
      if(aTOmCzlENA == true){aTOmCzlENA = false;}
      if(UegZYenCgX == true){UegZYenCgX = false;}
      if(AzEahijGco == true){AzEahijGco = false;}
      if(UhKxtUgpoc == true){UhKxtUgpoc = false;}
      if(MWmlyVmdXW == true){MWmlyVmdXW = false;}
      if(bOsXEaOnET == true){bOsXEaOnET = false;}
      if(OeaYflTifE == true){OeaYflTifE = false;}
      if(yyNDLdLSbM == true){yyNDLdLSbM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OZWNFZDNTG
{ 
  void bDejFIcDKF()
  { 
      bool FaXooydGVI = false;
      bool ItOIcpdepZ = false;
      bool GIEshaXAlq = false;
      bool wBOhqjNMwS = false;
      bool kXHQqUWqKM = false;
      bool hqiuoxWdGO = false;
      bool ZdTeLGffQr = false;
      bool cQiWniBmCN = false;
      bool DfoZIESTst = false;
      bool MjGhrHDbEj = false;
      bool nqZSjQIMGG = false;
      bool ujbrKtosVH = false;
      bool nMmWfsKBdg = false;
      bool eYiRYMFWpr = false;
      bool wFMmycHNXy = false;
      bool RKFxwbDDmp = false;
      bool GHiZaWBJTx = false;
      bool nSDdKhzAYC = false;
      bool kxdeOUTkUw = false;
      bool ICjzloWmLb = false;
      string rMtEuNorQK;
      string onMxNCyPDO;
      string HoAbzfnMpk;
      string CkGetsBAuT;
      string bmxcoXJFNG;
      string bppfsDMREP;
      string ZbBeHEghCU;
      string AxUilTrXma;
      string WhzjJMuZkq;
      string fjuftzkRUk;
      string qbDsFdUGtY;
      string KoedrqcRVu;
      string IHwKnQCoom;
      string iZCBjtdFde;
      string rofLgqERmC;
      string VSwZbjerFo;
      string bfRGpjlcsy;
      string MXnpDTajdw;
      string LkBlQPdcYA;
      string PlAnDLWYVw;
      if(rMtEuNorQK == qbDsFdUGtY){FaXooydGVI = true;}
      else if(qbDsFdUGtY == rMtEuNorQK){nqZSjQIMGG = true;}
      if(onMxNCyPDO == KoedrqcRVu){ItOIcpdepZ = true;}
      else if(KoedrqcRVu == onMxNCyPDO){ujbrKtosVH = true;}
      if(HoAbzfnMpk == IHwKnQCoom){GIEshaXAlq = true;}
      else if(IHwKnQCoom == HoAbzfnMpk){nMmWfsKBdg = true;}
      if(CkGetsBAuT == iZCBjtdFde){wBOhqjNMwS = true;}
      else if(iZCBjtdFde == CkGetsBAuT){eYiRYMFWpr = true;}
      if(bmxcoXJFNG == rofLgqERmC){kXHQqUWqKM = true;}
      else if(rofLgqERmC == bmxcoXJFNG){wFMmycHNXy = true;}
      if(bppfsDMREP == VSwZbjerFo){hqiuoxWdGO = true;}
      else if(VSwZbjerFo == bppfsDMREP){RKFxwbDDmp = true;}
      if(ZbBeHEghCU == bfRGpjlcsy){ZdTeLGffQr = true;}
      else if(bfRGpjlcsy == ZbBeHEghCU){GHiZaWBJTx = true;}
      if(AxUilTrXma == MXnpDTajdw){cQiWniBmCN = true;}
      if(WhzjJMuZkq == LkBlQPdcYA){DfoZIESTst = true;}
      if(fjuftzkRUk == PlAnDLWYVw){MjGhrHDbEj = true;}
      while(MXnpDTajdw == AxUilTrXma){nSDdKhzAYC = true;}
      while(LkBlQPdcYA == LkBlQPdcYA){kxdeOUTkUw = true;}
      while(PlAnDLWYVw == PlAnDLWYVw){ICjzloWmLb = true;}
      if(FaXooydGVI == true){FaXooydGVI = false;}
      if(ItOIcpdepZ == true){ItOIcpdepZ = false;}
      if(GIEshaXAlq == true){GIEshaXAlq = false;}
      if(wBOhqjNMwS == true){wBOhqjNMwS = false;}
      if(kXHQqUWqKM == true){kXHQqUWqKM = false;}
      if(hqiuoxWdGO == true){hqiuoxWdGO = false;}
      if(ZdTeLGffQr == true){ZdTeLGffQr = false;}
      if(cQiWniBmCN == true){cQiWniBmCN = false;}
      if(DfoZIESTst == true){DfoZIESTst = false;}
      if(MjGhrHDbEj == true){MjGhrHDbEj = false;}
      if(nqZSjQIMGG == true){nqZSjQIMGG = false;}
      if(ujbrKtosVH == true){ujbrKtosVH = false;}
      if(nMmWfsKBdg == true){nMmWfsKBdg = false;}
      if(eYiRYMFWpr == true){eYiRYMFWpr = false;}
      if(wFMmycHNXy == true){wFMmycHNXy = false;}
      if(RKFxwbDDmp == true){RKFxwbDDmp = false;}
      if(GHiZaWBJTx == true){GHiZaWBJTx = false;}
      if(nSDdKhzAYC == true){nSDdKhzAYC = false;}
      if(kxdeOUTkUw == true){kxdeOUTkUw = false;}
      if(ICjzloWmLb == true){ICjzloWmLb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCMMHAUOYA
{ 
  void pZFLfsjmzf()
  { 
      bool orJdYQqTJW = false;
      bool uDyeFcaDlE = false;
      bool GdLpWrtarr = false;
      bool NxVKkefBrL = false;
      bool seIMXOxBZj = false;
      bool hXYNPKgSGg = false;
      bool WPbRIygntZ = false;
      bool wZLZLaVzRI = false;
      bool trBIJpXItZ = false;
      bool yNtKocDpDZ = false;
      bool gIHzmIMyCo = false;
      bool ogAyleOSHS = false;
      bool ZYtTbieAkh = false;
      bool WeuraljBVB = false;
      bool cZGFkQMwYJ = false;
      bool NkikAIOnXD = false;
      bool cLNTRJlIXz = false;
      bool tNwFozSnhL = false;
      bool WibaTkwJrR = false;
      bool XwdSXRLlma = false;
      string CDZWuxLhfj;
      string hLRoLJsdIC;
      string SmXjiCTrXn;
      string uyUuXpTlLE;
      string ZXCRkbIEmb;
      string hYCLRPeoms;
      string dTKrnjqWQV;
      string oGREbujFyH;
      string tOEuGWuJcH;
      string KdySaGMKcB;
      string kknRmaGyjW;
      string eYqfyOOOkR;
      string ngtILKIzcU;
      string hYcwWJamIf;
      string QxZGbkmSTM;
      string ryZKNDqeFc;
      string SGUOnGwtJo;
      string maGFBpHnfZ;
      string WofQcjzRiS;
      string RugeMJbKRV;
      if(CDZWuxLhfj == kknRmaGyjW){orJdYQqTJW = true;}
      else if(kknRmaGyjW == CDZWuxLhfj){gIHzmIMyCo = true;}
      if(hLRoLJsdIC == eYqfyOOOkR){uDyeFcaDlE = true;}
      else if(eYqfyOOOkR == hLRoLJsdIC){ogAyleOSHS = true;}
      if(SmXjiCTrXn == ngtILKIzcU){GdLpWrtarr = true;}
      else if(ngtILKIzcU == SmXjiCTrXn){ZYtTbieAkh = true;}
      if(uyUuXpTlLE == hYcwWJamIf){NxVKkefBrL = true;}
      else if(hYcwWJamIf == uyUuXpTlLE){WeuraljBVB = true;}
      if(ZXCRkbIEmb == QxZGbkmSTM){seIMXOxBZj = true;}
      else if(QxZGbkmSTM == ZXCRkbIEmb){cZGFkQMwYJ = true;}
      if(hYCLRPeoms == ryZKNDqeFc){hXYNPKgSGg = true;}
      else if(ryZKNDqeFc == hYCLRPeoms){NkikAIOnXD = true;}
      if(dTKrnjqWQV == SGUOnGwtJo){WPbRIygntZ = true;}
      else if(SGUOnGwtJo == dTKrnjqWQV){cLNTRJlIXz = true;}
      if(oGREbujFyH == maGFBpHnfZ){wZLZLaVzRI = true;}
      if(tOEuGWuJcH == WofQcjzRiS){trBIJpXItZ = true;}
      if(KdySaGMKcB == RugeMJbKRV){yNtKocDpDZ = true;}
      while(maGFBpHnfZ == oGREbujFyH){tNwFozSnhL = true;}
      while(WofQcjzRiS == WofQcjzRiS){WibaTkwJrR = true;}
      while(RugeMJbKRV == RugeMJbKRV){XwdSXRLlma = true;}
      if(orJdYQqTJW == true){orJdYQqTJW = false;}
      if(uDyeFcaDlE == true){uDyeFcaDlE = false;}
      if(GdLpWrtarr == true){GdLpWrtarr = false;}
      if(NxVKkefBrL == true){NxVKkefBrL = false;}
      if(seIMXOxBZj == true){seIMXOxBZj = false;}
      if(hXYNPKgSGg == true){hXYNPKgSGg = false;}
      if(WPbRIygntZ == true){WPbRIygntZ = false;}
      if(wZLZLaVzRI == true){wZLZLaVzRI = false;}
      if(trBIJpXItZ == true){trBIJpXItZ = false;}
      if(yNtKocDpDZ == true){yNtKocDpDZ = false;}
      if(gIHzmIMyCo == true){gIHzmIMyCo = false;}
      if(ogAyleOSHS == true){ogAyleOSHS = false;}
      if(ZYtTbieAkh == true){ZYtTbieAkh = false;}
      if(WeuraljBVB == true){WeuraljBVB = false;}
      if(cZGFkQMwYJ == true){cZGFkQMwYJ = false;}
      if(NkikAIOnXD == true){NkikAIOnXD = false;}
      if(cLNTRJlIXz == true){cLNTRJlIXz = false;}
      if(tNwFozSnhL == true){tNwFozSnhL = false;}
      if(WibaTkwJrR == true){WibaTkwJrR = false;}
      if(XwdSXRLlma == true){XwdSXRLlma = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUBCVIQBVU
{ 
  void SCmfgsbyRt()
  { 
      bool UNUpKcnKOM = false;
      bool nrLAZIFWEh = false;
      bool VBiPBFDKia = false;
      bool pCDTMWpoat = false;
      bool MIqSSqqhXe = false;
      bool QtVVISdEnE = false;
      bool YdanWlornC = false;
      bool RPwKVNKQxK = false;
      bool OVlEJwfgLs = false;
      bool rlAVUhgDuf = false;
      bool BzsUMAxLAt = false;
      bool INHdpDqVda = false;
      bool GHguJeOZom = false;
      bool fGUQIPbQqI = false;
      bool yUfQjeeWeR = false;
      bool qLYUZtSxLh = false;
      bool kWVNOCspUa = false;
      bool aZdUckaPKe = false;
      bool AruXuUgAqO = false;
      bool weFJXaySCh = false;
      string UMZWmtdGsI;
      string LZUYZLoDxh;
      string SYEMIljRKm;
      string CtfHCLFAxB;
      string eIPWOoHwHe;
      string KAJQowHMOA;
      string KMwFGQsMVO;
      string GoGwDJIhyT;
      string emJfcCkOSF;
      string DrlxqRMJPy;
      string utZsXVtMNf;
      string mZOuVWCPcE;
      string edtPKNCIFk;
      string xzRzXjNQHG;
      string HYBmSccqbT;
      string OwgLTQAJhK;
      string TkHbinIPWk;
      string JlHWwGbHxg;
      string kKfkWASGfG;
      string iDhxmVQZEd;
      if(UMZWmtdGsI == utZsXVtMNf){UNUpKcnKOM = true;}
      else if(utZsXVtMNf == UMZWmtdGsI){BzsUMAxLAt = true;}
      if(LZUYZLoDxh == mZOuVWCPcE){nrLAZIFWEh = true;}
      else if(mZOuVWCPcE == LZUYZLoDxh){INHdpDqVda = true;}
      if(SYEMIljRKm == edtPKNCIFk){VBiPBFDKia = true;}
      else if(edtPKNCIFk == SYEMIljRKm){GHguJeOZom = true;}
      if(CtfHCLFAxB == xzRzXjNQHG){pCDTMWpoat = true;}
      else if(xzRzXjNQHG == CtfHCLFAxB){fGUQIPbQqI = true;}
      if(eIPWOoHwHe == HYBmSccqbT){MIqSSqqhXe = true;}
      else if(HYBmSccqbT == eIPWOoHwHe){yUfQjeeWeR = true;}
      if(KAJQowHMOA == OwgLTQAJhK){QtVVISdEnE = true;}
      else if(OwgLTQAJhK == KAJQowHMOA){qLYUZtSxLh = true;}
      if(KMwFGQsMVO == TkHbinIPWk){YdanWlornC = true;}
      else if(TkHbinIPWk == KMwFGQsMVO){kWVNOCspUa = true;}
      if(GoGwDJIhyT == JlHWwGbHxg){RPwKVNKQxK = true;}
      if(emJfcCkOSF == kKfkWASGfG){OVlEJwfgLs = true;}
      if(DrlxqRMJPy == iDhxmVQZEd){rlAVUhgDuf = true;}
      while(JlHWwGbHxg == GoGwDJIhyT){aZdUckaPKe = true;}
      while(kKfkWASGfG == kKfkWASGfG){AruXuUgAqO = true;}
      while(iDhxmVQZEd == iDhxmVQZEd){weFJXaySCh = true;}
      if(UNUpKcnKOM == true){UNUpKcnKOM = false;}
      if(nrLAZIFWEh == true){nrLAZIFWEh = false;}
      if(VBiPBFDKia == true){VBiPBFDKia = false;}
      if(pCDTMWpoat == true){pCDTMWpoat = false;}
      if(MIqSSqqhXe == true){MIqSSqqhXe = false;}
      if(QtVVISdEnE == true){QtVVISdEnE = false;}
      if(YdanWlornC == true){YdanWlornC = false;}
      if(RPwKVNKQxK == true){RPwKVNKQxK = false;}
      if(OVlEJwfgLs == true){OVlEJwfgLs = false;}
      if(rlAVUhgDuf == true){rlAVUhgDuf = false;}
      if(BzsUMAxLAt == true){BzsUMAxLAt = false;}
      if(INHdpDqVda == true){INHdpDqVda = false;}
      if(GHguJeOZom == true){GHguJeOZom = false;}
      if(fGUQIPbQqI == true){fGUQIPbQqI = false;}
      if(yUfQjeeWeR == true){yUfQjeeWeR = false;}
      if(qLYUZtSxLh == true){qLYUZtSxLh = false;}
      if(kWVNOCspUa == true){kWVNOCspUa = false;}
      if(aZdUckaPKe == true){aZdUckaPKe = false;}
      if(AruXuUgAqO == true){AruXuUgAqO = false;}
      if(weFJXaySCh == true){weFJXaySCh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVPKHLECVN
{ 
  void CooriaHmZl()
  { 
      bool ElqlZjViNz = false;
      bool DGfHQyjQhm = false;
      bool AyoMKOcroy = false;
      bool xQilVTVbEk = false;
      bool PCJkErJRIP = false;
      bool EXoYYFwdaL = false;
      bool HcsOCmXskw = false;
      bool cHMxWyoEIR = false;
      bool FKjZtZaKNP = false;
      bool WqArdmIuiQ = false;
      bool UPgLlwKrBa = false;
      bool QrVJGwsTTc = false;
      bool MNfUYlGTSj = false;
      bool otVqxodXmx = false;
      bool OhIlzeVqkg = false;
      bool soaGEHiLlA = false;
      bool pqYRlWWdLQ = false;
      bool SVfVNdEtVt = false;
      bool QOilqzTPlp = false;
      bool GSkmHXIqzc = false;
      string meXzayzquw;
      string fJVKcHVXeE;
      string VqqxUfLwuG;
      string aUFGQHhMDE;
      string zwEuSMwLEM;
      string tdeRXwnZdu;
      string mCwoVLEOsU;
      string YITaFZlwdI;
      string iAriLwoniU;
      string SHiIRxAPYH;
      string IhRjmlJELy;
      string JrwVLmKMcY;
      string VPfYBQZLJI;
      string YWWVABhHuZ;
      string ljbkLaLMwe;
      string lmlzkrBshV;
      string LyuDYlVZVK;
      string ECRDllnuMa;
      string FMOeVlkWjI;
      string zoZYNnnXLZ;
      if(meXzayzquw == IhRjmlJELy){ElqlZjViNz = true;}
      else if(IhRjmlJELy == meXzayzquw){UPgLlwKrBa = true;}
      if(fJVKcHVXeE == JrwVLmKMcY){DGfHQyjQhm = true;}
      else if(JrwVLmKMcY == fJVKcHVXeE){QrVJGwsTTc = true;}
      if(VqqxUfLwuG == VPfYBQZLJI){AyoMKOcroy = true;}
      else if(VPfYBQZLJI == VqqxUfLwuG){MNfUYlGTSj = true;}
      if(aUFGQHhMDE == YWWVABhHuZ){xQilVTVbEk = true;}
      else if(YWWVABhHuZ == aUFGQHhMDE){otVqxodXmx = true;}
      if(zwEuSMwLEM == ljbkLaLMwe){PCJkErJRIP = true;}
      else if(ljbkLaLMwe == zwEuSMwLEM){OhIlzeVqkg = true;}
      if(tdeRXwnZdu == lmlzkrBshV){EXoYYFwdaL = true;}
      else if(lmlzkrBshV == tdeRXwnZdu){soaGEHiLlA = true;}
      if(mCwoVLEOsU == LyuDYlVZVK){HcsOCmXskw = true;}
      else if(LyuDYlVZVK == mCwoVLEOsU){pqYRlWWdLQ = true;}
      if(YITaFZlwdI == ECRDllnuMa){cHMxWyoEIR = true;}
      if(iAriLwoniU == FMOeVlkWjI){FKjZtZaKNP = true;}
      if(SHiIRxAPYH == zoZYNnnXLZ){WqArdmIuiQ = true;}
      while(ECRDllnuMa == YITaFZlwdI){SVfVNdEtVt = true;}
      while(FMOeVlkWjI == FMOeVlkWjI){QOilqzTPlp = true;}
      while(zoZYNnnXLZ == zoZYNnnXLZ){GSkmHXIqzc = true;}
      if(ElqlZjViNz == true){ElqlZjViNz = false;}
      if(DGfHQyjQhm == true){DGfHQyjQhm = false;}
      if(AyoMKOcroy == true){AyoMKOcroy = false;}
      if(xQilVTVbEk == true){xQilVTVbEk = false;}
      if(PCJkErJRIP == true){PCJkErJRIP = false;}
      if(EXoYYFwdaL == true){EXoYYFwdaL = false;}
      if(HcsOCmXskw == true){HcsOCmXskw = false;}
      if(cHMxWyoEIR == true){cHMxWyoEIR = false;}
      if(FKjZtZaKNP == true){FKjZtZaKNP = false;}
      if(WqArdmIuiQ == true){WqArdmIuiQ = false;}
      if(UPgLlwKrBa == true){UPgLlwKrBa = false;}
      if(QrVJGwsTTc == true){QrVJGwsTTc = false;}
      if(MNfUYlGTSj == true){MNfUYlGTSj = false;}
      if(otVqxodXmx == true){otVqxodXmx = false;}
      if(OhIlzeVqkg == true){OhIlzeVqkg = false;}
      if(soaGEHiLlA == true){soaGEHiLlA = false;}
      if(pqYRlWWdLQ == true){pqYRlWWdLQ = false;}
      if(SVfVNdEtVt == true){SVfVNdEtVt = false;}
      if(QOilqzTPlp == true){QOilqzTPlp = false;}
      if(GSkmHXIqzc == true){GSkmHXIqzc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCNPLWTMUQ
{ 
  void DhEhDjMAQt()
  { 
      bool ZcdyYClBNT = false;
      bool nHikgFubgW = false;
      bool PliszwDJUt = false;
      bool PGJfRPkAeu = false;
      bool iqmmwsBNOx = false;
      bool Jgfotmskzc = false;
      bool zbgSEhyCTR = false;
      bool TuwlmYywwG = false;
      bool touXjhZTld = false;
      bool WABBwHKUhO = false;
      bool tztxcOjtCV = false;
      bool ownriJfIhV = false;
      bool HdQouSsupf = false;
      bool OdOgLuuytU = false;
      bool yfRPoZMISl = false;
      bool aBlMHQiECJ = false;
      bool VoEVHKhGgn = false;
      bool OhOMXaMAAU = false;
      bool GkbDFMrBZu = false;
      bool LpujzIauIe = false;
      string WPFIXLEFdA;
      string ZefzRaaJmM;
      string sOiIVPbORR;
      string IesxzwFUjf;
      string ZJeFCGjiDH;
      string AQyTnHfwmI;
      string ipmMrukhAU;
      string UGYHliicGO;
      string erKJRqgYIq;
      string PIgbwjVSNG;
      string UCihmtrqgF;
      string YCoYcpectA;
      string OMYJELYxKC;
      string NQPztcJcWX;
      string zorDSNSIyF;
      string ErXNrIcZca;
      string UtfeqImpez;
      string fCGWAYTVpq;
      string sPzExUrBGk;
      string AjzwCFINLK;
      if(WPFIXLEFdA == UCihmtrqgF){ZcdyYClBNT = true;}
      else if(UCihmtrqgF == WPFIXLEFdA){tztxcOjtCV = true;}
      if(ZefzRaaJmM == YCoYcpectA){nHikgFubgW = true;}
      else if(YCoYcpectA == ZefzRaaJmM){ownriJfIhV = true;}
      if(sOiIVPbORR == OMYJELYxKC){PliszwDJUt = true;}
      else if(OMYJELYxKC == sOiIVPbORR){HdQouSsupf = true;}
      if(IesxzwFUjf == NQPztcJcWX){PGJfRPkAeu = true;}
      else if(NQPztcJcWX == IesxzwFUjf){OdOgLuuytU = true;}
      if(ZJeFCGjiDH == zorDSNSIyF){iqmmwsBNOx = true;}
      else if(zorDSNSIyF == ZJeFCGjiDH){yfRPoZMISl = true;}
      if(AQyTnHfwmI == ErXNrIcZca){Jgfotmskzc = true;}
      else if(ErXNrIcZca == AQyTnHfwmI){aBlMHQiECJ = true;}
      if(ipmMrukhAU == UtfeqImpez){zbgSEhyCTR = true;}
      else if(UtfeqImpez == ipmMrukhAU){VoEVHKhGgn = true;}
      if(UGYHliicGO == fCGWAYTVpq){TuwlmYywwG = true;}
      if(erKJRqgYIq == sPzExUrBGk){touXjhZTld = true;}
      if(PIgbwjVSNG == AjzwCFINLK){WABBwHKUhO = true;}
      while(fCGWAYTVpq == UGYHliicGO){OhOMXaMAAU = true;}
      while(sPzExUrBGk == sPzExUrBGk){GkbDFMrBZu = true;}
      while(AjzwCFINLK == AjzwCFINLK){LpujzIauIe = true;}
      if(ZcdyYClBNT == true){ZcdyYClBNT = false;}
      if(nHikgFubgW == true){nHikgFubgW = false;}
      if(PliszwDJUt == true){PliszwDJUt = false;}
      if(PGJfRPkAeu == true){PGJfRPkAeu = false;}
      if(iqmmwsBNOx == true){iqmmwsBNOx = false;}
      if(Jgfotmskzc == true){Jgfotmskzc = false;}
      if(zbgSEhyCTR == true){zbgSEhyCTR = false;}
      if(TuwlmYywwG == true){TuwlmYywwG = false;}
      if(touXjhZTld == true){touXjhZTld = false;}
      if(WABBwHKUhO == true){WABBwHKUhO = false;}
      if(tztxcOjtCV == true){tztxcOjtCV = false;}
      if(ownriJfIhV == true){ownriJfIhV = false;}
      if(HdQouSsupf == true){HdQouSsupf = false;}
      if(OdOgLuuytU == true){OdOgLuuytU = false;}
      if(yfRPoZMISl == true){yfRPoZMISl = false;}
      if(aBlMHQiECJ == true){aBlMHQiECJ = false;}
      if(VoEVHKhGgn == true){VoEVHKhGgn = false;}
      if(OhOMXaMAAU == true){OhOMXaMAAU = false;}
      if(GkbDFMrBZu == true){GkbDFMrBZu = false;}
      if(LpujzIauIe == true){LpujzIauIe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UOWYFGTYDS
{ 
  void xGSLHyAFhu()
  { 
      bool MaMrjfsxke = false;
      bool wAHzipKdaB = false;
      bool cwapShgxAa = false;
      bool aJtHSwDQgH = false;
      bool DZQWrogshu = false;
      bool CGxoNQAWZC = false;
      bool zwxJElGAgm = false;
      bool lsxSxCeDyd = false;
      bool BmOEXTLFtB = false;
      bool wgqdIGcGSF = false;
      bool igMtJJJeqK = false;
      bool lwXuALgrlk = false;
      bool ZAFeqFCSKq = false;
      bool ZXkstUZTtO = false;
      bool KgOjPzIudw = false;
      bool YjUgeiahDD = false;
      bool GpTAjNLeBf = false;
      bool lMxWaskUOr = false;
      bool wHoNRoDDNL = false;
      bool srQpITMOzC = false;
      string ttIufbloHV;
      string HRJJIkEGbx;
      string mSyFfKUrwV;
      string oPCtXgfFIe;
      string ynzbbOYfyo;
      string OcPHCawCPV;
      string GsskgrPPkb;
      string FzywzzTVdR;
      string kotGHLztqx;
      string kcpmYEtNtj;
      string yJtViPeSID;
      string GZXxjRyldU;
      string rUYnqbILXt;
      string EGatSatXXr;
      string gflnpLFrCG;
      string GHiYqdkFeG;
      string GTuNyAydeJ;
      string WZOlnLhjyf;
      string WQJQmxWBCn;
      string pnsRlNkXpp;
      if(ttIufbloHV == yJtViPeSID){MaMrjfsxke = true;}
      else if(yJtViPeSID == ttIufbloHV){igMtJJJeqK = true;}
      if(HRJJIkEGbx == GZXxjRyldU){wAHzipKdaB = true;}
      else if(GZXxjRyldU == HRJJIkEGbx){lwXuALgrlk = true;}
      if(mSyFfKUrwV == rUYnqbILXt){cwapShgxAa = true;}
      else if(rUYnqbILXt == mSyFfKUrwV){ZAFeqFCSKq = true;}
      if(oPCtXgfFIe == EGatSatXXr){aJtHSwDQgH = true;}
      else if(EGatSatXXr == oPCtXgfFIe){ZXkstUZTtO = true;}
      if(ynzbbOYfyo == gflnpLFrCG){DZQWrogshu = true;}
      else if(gflnpLFrCG == ynzbbOYfyo){KgOjPzIudw = true;}
      if(OcPHCawCPV == GHiYqdkFeG){CGxoNQAWZC = true;}
      else if(GHiYqdkFeG == OcPHCawCPV){YjUgeiahDD = true;}
      if(GsskgrPPkb == GTuNyAydeJ){zwxJElGAgm = true;}
      else if(GTuNyAydeJ == GsskgrPPkb){GpTAjNLeBf = true;}
      if(FzywzzTVdR == WZOlnLhjyf){lsxSxCeDyd = true;}
      if(kotGHLztqx == WQJQmxWBCn){BmOEXTLFtB = true;}
      if(kcpmYEtNtj == pnsRlNkXpp){wgqdIGcGSF = true;}
      while(WZOlnLhjyf == FzywzzTVdR){lMxWaskUOr = true;}
      while(WQJQmxWBCn == WQJQmxWBCn){wHoNRoDDNL = true;}
      while(pnsRlNkXpp == pnsRlNkXpp){srQpITMOzC = true;}
      if(MaMrjfsxke == true){MaMrjfsxke = false;}
      if(wAHzipKdaB == true){wAHzipKdaB = false;}
      if(cwapShgxAa == true){cwapShgxAa = false;}
      if(aJtHSwDQgH == true){aJtHSwDQgH = false;}
      if(DZQWrogshu == true){DZQWrogshu = false;}
      if(CGxoNQAWZC == true){CGxoNQAWZC = false;}
      if(zwxJElGAgm == true){zwxJElGAgm = false;}
      if(lsxSxCeDyd == true){lsxSxCeDyd = false;}
      if(BmOEXTLFtB == true){BmOEXTLFtB = false;}
      if(wgqdIGcGSF == true){wgqdIGcGSF = false;}
      if(igMtJJJeqK == true){igMtJJJeqK = false;}
      if(lwXuALgrlk == true){lwXuALgrlk = false;}
      if(ZAFeqFCSKq == true){ZAFeqFCSKq = false;}
      if(ZXkstUZTtO == true){ZXkstUZTtO = false;}
      if(KgOjPzIudw == true){KgOjPzIudw = false;}
      if(YjUgeiahDD == true){YjUgeiahDD = false;}
      if(GpTAjNLeBf == true){GpTAjNLeBf = false;}
      if(lMxWaskUOr == true){lMxWaskUOr = false;}
      if(wHoNRoDDNL == true){wHoNRoDDNL = false;}
      if(srQpITMOzC == true){srQpITMOzC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMWMMGVWTB
{ 
  void FiMVeiosBh()
  { 
      bool QreZOxWQUz = false;
      bool TdNUJrNsit = false;
      bool sOiTLzrTmH = false;
      bool VZQyBVByzf = false;
      bool VQqwldXwYL = false;
      bool zHhbEBJKNP = false;
      bool FCdMdsMPSn = false;
      bool qOtCYbWlgh = false;
      bool autbINrotz = false;
      bool LpkjaSmeSr = false;
      bool QIdkTjNeDb = false;
      bool dXcenJHCEP = false;
      bool BXVSbBdJaG = false;
      bool orTnRRRJHX = false;
      bool zMkRUnMFuQ = false;
      bool KkZCqrmKJS = false;
      bool GDDxmlEnNV = false;
      bool rytgPnmDxm = false;
      bool nXOKuESQxZ = false;
      bool eGAoQwIndi = false;
      string WsoZJTuLgn;
      string yifYAsaijq;
      string LryYfVMfjd;
      string PrjTRRkqbo;
      string jKdjGfdleS;
      string rLPGFdtPsm;
      string HObDYGzMHh;
      string HiHuHAOOSz;
      string rZBRkDbcOm;
      string XUyogUiZLA;
      string gQdxKIEUzE;
      string PexsugNJSU;
      string dVyTKlkRNl;
      string RoDRSawDGb;
      string zHdJXrXFsz;
      string HYHpVLSJlX;
      string XlGMmZbeaT;
      string kJCpUWqnwR;
      string OfXNdrgMwG;
      string HlRiDNAQWx;
      if(WsoZJTuLgn == gQdxKIEUzE){QreZOxWQUz = true;}
      else if(gQdxKIEUzE == WsoZJTuLgn){QIdkTjNeDb = true;}
      if(yifYAsaijq == PexsugNJSU){TdNUJrNsit = true;}
      else if(PexsugNJSU == yifYAsaijq){dXcenJHCEP = true;}
      if(LryYfVMfjd == dVyTKlkRNl){sOiTLzrTmH = true;}
      else if(dVyTKlkRNl == LryYfVMfjd){BXVSbBdJaG = true;}
      if(PrjTRRkqbo == RoDRSawDGb){VZQyBVByzf = true;}
      else if(RoDRSawDGb == PrjTRRkqbo){orTnRRRJHX = true;}
      if(jKdjGfdleS == zHdJXrXFsz){VQqwldXwYL = true;}
      else if(zHdJXrXFsz == jKdjGfdleS){zMkRUnMFuQ = true;}
      if(rLPGFdtPsm == HYHpVLSJlX){zHhbEBJKNP = true;}
      else if(HYHpVLSJlX == rLPGFdtPsm){KkZCqrmKJS = true;}
      if(HObDYGzMHh == XlGMmZbeaT){FCdMdsMPSn = true;}
      else if(XlGMmZbeaT == HObDYGzMHh){GDDxmlEnNV = true;}
      if(HiHuHAOOSz == kJCpUWqnwR){qOtCYbWlgh = true;}
      if(rZBRkDbcOm == OfXNdrgMwG){autbINrotz = true;}
      if(XUyogUiZLA == HlRiDNAQWx){LpkjaSmeSr = true;}
      while(kJCpUWqnwR == HiHuHAOOSz){rytgPnmDxm = true;}
      while(OfXNdrgMwG == OfXNdrgMwG){nXOKuESQxZ = true;}
      while(HlRiDNAQWx == HlRiDNAQWx){eGAoQwIndi = true;}
      if(QreZOxWQUz == true){QreZOxWQUz = false;}
      if(TdNUJrNsit == true){TdNUJrNsit = false;}
      if(sOiTLzrTmH == true){sOiTLzrTmH = false;}
      if(VZQyBVByzf == true){VZQyBVByzf = false;}
      if(VQqwldXwYL == true){VQqwldXwYL = false;}
      if(zHhbEBJKNP == true){zHhbEBJKNP = false;}
      if(FCdMdsMPSn == true){FCdMdsMPSn = false;}
      if(qOtCYbWlgh == true){qOtCYbWlgh = false;}
      if(autbINrotz == true){autbINrotz = false;}
      if(LpkjaSmeSr == true){LpkjaSmeSr = false;}
      if(QIdkTjNeDb == true){QIdkTjNeDb = false;}
      if(dXcenJHCEP == true){dXcenJHCEP = false;}
      if(BXVSbBdJaG == true){BXVSbBdJaG = false;}
      if(orTnRRRJHX == true){orTnRRRJHX = false;}
      if(zMkRUnMFuQ == true){zMkRUnMFuQ = false;}
      if(KkZCqrmKJS == true){KkZCqrmKJS = false;}
      if(GDDxmlEnNV == true){GDDxmlEnNV = false;}
      if(rytgPnmDxm == true){rytgPnmDxm = false;}
      if(nXOKuESQxZ == true){nXOKuESQxZ = false;}
      if(eGAoQwIndi == true){eGAoQwIndi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIEMOWNSGL
{ 
  void MysKuCqpBF()
  { 
      bool ButGglMUwl = false;
      bool swRWSWGAzS = false;
      bool UVVBjGODjg = false;
      bool xPlEAaOIWA = false;
      bool mEisZMZrfV = false;
      bool kiEpReZsVa = false;
      bool WIjPncJMWr = false;
      bool HydzfQmbbX = false;
      bool fWXNuNLwmU = false;
      bool BVlucdTSFx = false;
      bool CMVnOmFEKB = false;
      bool rxRytAkVUZ = false;
      bool QNZCplLhVB = false;
      bool wTWeUSAizH = false;
      bool HGkkbDEmBc = false;
      bool sxyefomTxc = false;
      bool aXiJEYamda = false;
      bool zBWMRJcnZm = false;
      bool gXgrHyVrye = false;
      bool fgkWfjXbgD = false;
      string HXTCbQjQEn;
      string gkxScCyVZA;
      string bMJdEOkCXV;
      string zgBQtSlLJK;
      string PCkyoEwElY;
      string qyEYHtNoyN;
      string fhrinzjgXJ;
      string PlLPkZaLoz;
      string RgPyeAcbJA;
      string FxNwehJCJo;
      string TPfbIElonh;
      string SCAzuyRsDn;
      string VHXXESXPjC;
      string PYBzeBAmoZ;
      string OnnagCwOAf;
      string QPzVTMrIXp;
      string gVEkRtBBTs;
      string ydDdYhTwqB;
      string WJPElzZeeS;
      string JrOzsrjDJl;
      if(HXTCbQjQEn == TPfbIElonh){ButGglMUwl = true;}
      else if(TPfbIElonh == HXTCbQjQEn){CMVnOmFEKB = true;}
      if(gkxScCyVZA == SCAzuyRsDn){swRWSWGAzS = true;}
      else if(SCAzuyRsDn == gkxScCyVZA){rxRytAkVUZ = true;}
      if(bMJdEOkCXV == VHXXESXPjC){UVVBjGODjg = true;}
      else if(VHXXESXPjC == bMJdEOkCXV){QNZCplLhVB = true;}
      if(zgBQtSlLJK == PYBzeBAmoZ){xPlEAaOIWA = true;}
      else if(PYBzeBAmoZ == zgBQtSlLJK){wTWeUSAizH = true;}
      if(PCkyoEwElY == OnnagCwOAf){mEisZMZrfV = true;}
      else if(OnnagCwOAf == PCkyoEwElY){HGkkbDEmBc = true;}
      if(qyEYHtNoyN == QPzVTMrIXp){kiEpReZsVa = true;}
      else if(QPzVTMrIXp == qyEYHtNoyN){sxyefomTxc = true;}
      if(fhrinzjgXJ == gVEkRtBBTs){WIjPncJMWr = true;}
      else if(gVEkRtBBTs == fhrinzjgXJ){aXiJEYamda = true;}
      if(PlLPkZaLoz == ydDdYhTwqB){HydzfQmbbX = true;}
      if(RgPyeAcbJA == WJPElzZeeS){fWXNuNLwmU = true;}
      if(FxNwehJCJo == JrOzsrjDJl){BVlucdTSFx = true;}
      while(ydDdYhTwqB == PlLPkZaLoz){zBWMRJcnZm = true;}
      while(WJPElzZeeS == WJPElzZeeS){gXgrHyVrye = true;}
      while(JrOzsrjDJl == JrOzsrjDJl){fgkWfjXbgD = true;}
      if(ButGglMUwl == true){ButGglMUwl = false;}
      if(swRWSWGAzS == true){swRWSWGAzS = false;}
      if(UVVBjGODjg == true){UVVBjGODjg = false;}
      if(xPlEAaOIWA == true){xPlEAaOIWA = false;}
      if(mEisZMZrfV == true){mEisZMZrfV = false;}
      if(kiEpReZsVa == true){kiEpReZsVa = false;}
      if(WIjPncJMWr == true){WIjPncJMWr = false;}
      if(HydzfQmbbX == true){HydzfQmbbX = false;}
      if(fWXNuNLwmU == true){fWXNuNLwmU = false;}
      if(BVlucdTSFx == true){BVlucdTSFx = false;}
      if(CMVnOmFEKB == true){CMVnOmFEKB = false;}
      if(rxRytAkVUZ == true){rxRytAkVUZ = false;}
      if(QNZCplLhVB == true){QNZCplLhVB = false;}
      if(wTWeUSAizH == true){wTWeUSAizH = false;}
      if(HGkkbDEmBc == true){HGkkbDEmBc = false;}
      if(sxyefomTxc == true){sxyefomTxc = false;}
      if(aXiJEYamda == true){aXiJEYamda = false;}
      if(zBWMRJcnZm == true){zBWMRJcnZm = false;}
      if(gXgrHyVrye == true){gXgrHyVrye = false;}
      if(fgkWfjXbgD == true){fgkWfjXbgD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKPUWTQNEW
{ 
  void iWnCqZdoLD()
  { 
      bool aeZHrpzImZ = false;
      bool JRIJmDRjYf = false;
      bool AgfasKHNth = false;
      bool kfutRmfTrC = false;
      bool kZkrfZartO = false;
      bool xQQQfsyyNg = false;
      bool ilOEodVOrz = false;
      bool WyqVuZwnuT = false;
      bool jOSejTOeOX = false;
      bool nhFLTzLfDC = false;
      bool EMAtqzYtUF = false;
      bool xJDtxTSiUU = false;
      bool OpzTLoreCu = false;
      bool OQkrOWOXnk = false;
      bool uTJIadeKOz = false;
      bool gbLhmONgiB = false;
      bool HtrZpgYKfZ = false;
      bool FtuiZtfprg = false;
      bool KgQDNmFCFA = false;
      bool JgomdAbjRs = false;
      string DEBKGdaPsZ;
      string BrjGlccmmY;
      string JyifpBTcrU;
      string qgsRJQazkM;
      string NAidkJiXwD;
      string kQSXGEUVTF;
      string KxWYiTzRxU;
      string BcBZLJPFtf;
      string RugojZNULF;
      string uFefCQcKuQ;
      string JQabBHPrMx;
      string oPbnmOPhoI;
      string GdGqYwxUXt;
      string fEKcVBTFmb;
      string KUINQfdqsm;
      string BuVlKfJjCF;
      string JtUSRjFyRk;
      string uKuMykVrar;
      string SGbkskiXRp;
      string qjChSPApwf;
      if(DEBKGdaPsZ == JQabBHPrMx){aeZHrpzImZ = true;}
      else if(JQabBHPrMx == DEBKGdaPsZ){EMAtqzYtUF = true;}
      if(BrjGlccmmY == oPbnmOPhoI){JRIJmDRjYf = true;}
      else if(oPbnmOPhoI == BrjGlccmmY){xJDtxTSiUU = true;}
      if(JyifpBTcrU == GdGqYwxUXt){AgfasKHNth = true;}
      else if(GdGqYwxUXt == JyifpBTcrU){OpzTLoreCu = true;}
      if(qgsRJQazkM == fEKcVBTFmb){kfutRmfTrC = true;}
      else if(fEKcVBTFmb == qgsRJQazkM){OQkrOWOXnk = true;}
      if(NAidkJiXwD == KUINQfdqsm){kZkrfZartO = true;}
      else if(KUINQfdqsm == NAidkJiXwD){uTJIadeKOz = true;}
      if(kQSXGEUVTF == BuVlKfJjCF){xQQQfsyyNg = true;}
      else if(BuVlKfJjCF == kQSXGEUVTF){gbLhmONgiB = true;}
      if(KxWYiTzRxU == JtUSRjFyRk){ilOEodVOrz = true;}
      else if(JtUSRjFyRk == KxWYiTzRxU){HtrZpgYKfZ = true;}
      if(BcBZLJPFtf == uKuMykVrar){WyqVuZwnuT = true;}
      if(RugojZNULF == SGbkskiXRp){jOSejTOeOX = true;}
      if(uFefCQcKuQ == qjChSPApwf){nhFLTzLfDC = true;}
      while(uKuMykVrar == BcBZLJPFtf){FtuiZtfprg = true;}
      while(SGbkskiXRp == SGbkskiXRp){KgQDNmFCFA = true;}
      while(qjChSPApwf == qjChSPApwf){JgomdAbjRs = true;}
      if(aeZHrpzImZ == true){aeZHrpzImZ = false;}
      if(JRIJmDRjYf == true){JRIJmDRjYf = false;}
      if(AgfasKHNth == true){AgfasKHNth = false;}
      if(kfutRmfTrC == true){kfutRmfTrC = false;}
      if(kZkrfZartO == true){kZkrfZartO = false;}
      if(xQQQfsyyNg == true){xQQQfsyyNg = false;}
      if(ilOEodVOrz == true){ilOEodVOrz = false;}
      if(WyqVuZwnuT == true){WyqVuZwnuT = false;}
      if(jOSejTOeOX == true){jOSejTOeOX = false;}
      if(nhFLTzLfDC == true){nhFLTzLfDC = false;}
      if(EMAtqzYtUF == true){EMAtqzYtUF = false;}
      if(xJDtxTSiUU == true){xJDtxTSiUU = false;}
      if(OpzTLoreCu == true){OpzTLoreCu = false;}
      if(OQkrOWOXnk == true){OQkrOWOXnk = false;}
      if(uTJIadeKOz == true){uTJIadeKOz = false;}
      if(gbLhmONgiB == true){gbLhmONgiB = false;}
      if(HtrZpgYKfZ == true){HtrZpgYKfZ = false;}
      if(FtuiZtfprg == true){FtuiZtfprg = false;}
      if(KgQDNmFCFA == true){KgQDNmFCFA = false;}
      if(JgomdAbjRs == true){JgomdAbjRs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGPAPWYCYS
{ 
  void rHxGDSzsZq()
  { 
      bool zbVoSWucjQ = false;
      bool aAhdQXydIl = false;
      bool QdpwjIcgbg = false;
      bool tLCasnMlJD = false;
      bool fGERtzDbqz = false;
      bool ZPaTdUlZEJ = false;
      bool tOACVPyHjb = false;
      bool LMTFGKYYBk = false;
      bool FAobHekixX = false;
      bool ClhzJQFBud = false;
      bool AwrPnMuUMS = false;
      bool wNXTEsYXuq = false;
      bool eOJLYYdUwo = false;
      bool EXcWjJIZnt = false;
      bool jPVdboNOuP = false;
      bool rgFEzklfpO = false;
      bool iZYWOXjAiu = false;
      bool kziAGOseij = false;
      bool KPZfxXRYXy = false;
      bool WbiZLJpzPE = false;
      string fVquAojkmA;
      string LrVwLfyehd;
      string JFzBKJuQRC;
      string UetxclBfKs;
      string ihpZXhLlGc;
      string uujKBZWojq;
      string tTSkegxYSZ;
      string dRTouaPZdb;
      string xJJnHZtiuD;
      string OMuTyPOFtq;
      string kmSgzcauPa;
      string JxLItkJdcE;
      string lOcOKRVApf;
      string MKemqJpbod;
      string zyTUsRAmYN;
      string FjbpEVJEWg;
      string GZFjOzSYQj;
      string uhozFmuIVs;
      string QiababinhU;
      string AlFHWYsiGt;
      if(fVquAojkmA == kmSgzcauPa){zbVoSWucjQ = true;}
      else if(kmSgzcauPa == fVquAojkmA){AwrPnMuUMS = true;}
      if(LrVwLfyehd == JxLItkJdcE){aAhdQXydIl = true;}
      else if(JxLItkJdcE == LrVwLfyehd){wNXTEsYXuq = true;}
      if(JFzBKJuQRC == lOcOKRVApf){QdpwjIcgbg = true;}
      else if(lOcOKRVApf == JFzBKJuQRC){eOJLYYdUwo = true;}
      if(UetxclBfKs == MKemqJpbod){tLCasnMlJD = true;}
      else if(MKemqJpbod == UetxclBfKs){EXcWjJIZnt = true;}
      if(ihpZXhLlGc == zyTUsRAmYN){fGERtzDbqz = true;}
      else if(zyTUsRAmYN == ihpZXhLlGc){jPVdboNOuP = true;}
      if(uujKBZWojq == FjbpEVJEWg){ZPaTdUlZEJ = true;}
      else if(FjbpEVJEWg == uujKBZWojq){rgFEzklfpO = true;}
      if(tTSkegxYSZ == GZFjOzSYQj){tOACVPyHjb = true;}
      else if(GZFjOzSYQj == tTSkegxYSZ){iZYWOXjAiu = true;}
      if(dRTouaPZdb == uhozFmuIVs){LMTFGKYYBk = true;}
      if(xJJnHZtiuD == QiababinhU){FAobHekixX = true;}
      if(OMuTyPOFtq == AlFHWYsiGt){ClhzJQFBud = true;}
      while(uhozFmuIVs == dRTouaPZdb){kziAGOseij = true;}
      while(QiababinhU == QiababinhU){KPZfxXRYXy = true;}
      while(AlFHWYsiGt == AlFHWYsiGt){WbiZLJpzPE = true;}
      if(zbVoSWucjQ == true){zbVoSWucjQ = false;}
      if(aAhdQXydIl == true){aAhdQXydIl = false;}
      if(QdpwjIcgbg == true){QdpwjIcgbg = false;}
      if(tLCasnMlJD == true){tLCasnMlJD = false;}
      if(fGERtzDbqz == true){fGERtzDbqz = false;}
      if(ZPaTdUlZEJ == true){ZPaTdUlZEJ = false;}
      if(tOACVPyHjb == true){tOACVPyHjb = false;}
      if(LMTFGKYYBk == true){LMTFGKYYBk = false;}
      if(FAobHekixX == true){FAobHekixX = false;}
      if(ClhzJQFBud == true){ClhzJQFBud = false;}
      if(AwrPnMuUMS == true){AwrPnMuUMS = false;}
      if(wNXTEsYXuq == true){wNXTEsYXuq = false;}
      if(eOJLYYdUwo == true){eOJLYYdUwo = false;}
      if(EXcWjJIZnt == true){EXcWjJIZnt = false;}
      if(jPVdboNOuP == true){jPVdboNOuP = false;}
      if(rgFEzklfpO == true){rgFEzklfpO = false;}
      if(iZYWOXjAiu == true){iZYWOXjAiu = false;}
      if(kziAGOseij == true){kziAGOseij = false;}
      if(KPZfxXRYXy == true){KPZfxXRYXy = false;}
      if(WbiZLJpzPE == true){WbiZLJpzPE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZARDLDQMGG
{ 
  void EgrHgTyHWC()
  { 
      bool FSJizrfhpl = false;
      bool afkIPCKEEK = false;
      bool PGPluSTndu = false;
      bool xrMWXwcTVe = false;
      bool nflGmtKIWN = false;
      bool nATXJzCXnf = false;
      bool XrDuniTOkS = false;
      bool YqiYVjUJyB = false;
      bool ILQQHwYoNY = false;
      bool sFfpHwcqRE = false;
      bool awWEnwRuBZ = false;
      bool dsYlXMalnq = false;
      bool KeBMYTLsRZ = false;
      bool GdqsaLnMcK = false;
      bool ecmmtAfsSt = false;
      bool UpCatutKfT = false;
      bool kYdbSACeLL = false;
      bool XOJcMgqNSX = false;
      bool mRaWFQaQze = false;
      bool QdgIYFyKUs = false;
      string brqwNWRDmi;
      string NVliuTHYIj;
      string LooxWDQTUt;
      string rqaGLoKrmP;
      string PhVjsFQFKf;
      string BHCxkmCsZK;
      string FxhsqWufXF;
      string IOksTcSFDR;
      string mLIorjndVX;
      string lQRcJSAcrW;
      string JkgFWlWJcH;
      string UxoHXtosAH;
      string hRJzSqxIjB;
      string bpNgHBdDRF;
      string MeANDobJFO;
      string cHbkorbhle;
      string oNZbfdiIAV;
      string PkattCQuwc;
      string PmDUXUNcrO;
      string ZwQlPzFXhY;
      if(brqwNWRDmi == JkgFWlWJcH){FSJizrfhpl = true;}
      else if(JkgFWlWJcH == brqwNWRDmi){awWEnwRuBZ = true;}
      if(NVliuTHYIj == UxoHXtosAH){afkIPCKEEK = true;}
      else if(UxoHXtosAH == NVliuTHYIj){dsYlXMalnq = true;}
      if(LooxWDQTUt == hRJzSqxIjB){PGPluSTndu = true;}
      else if(hRJzSqxIjB == LooxWDQTUt){KeBMYTLsRZ = true;}
      if(rqaGLoKrmP == bpNgHBdDRF){xrMWXwcTVe = true;}
      else if(bpNgHBdDRF == rqaGLoKrmP){GdqsaLnMcK = true;}
      if(PhVjsFQFKf == MeANDobJFO){nflGmtKIWN = true;}
      else if(MeANDobJFO == PhVjsFQFKf){ecmmtAfsSt = true;}
      if(BHCxkmCsZK == cHbkorbhle){nATXJzCXnf = true;}
      else if(cHbkorbhle == BHCxkmCsZK){UpCatutKfT = true;}
      if(FxhsqWufXF == oNZbfdiIAV){XrDuniTOkS = true;}
      else if(oNZbfdiIAV == FxhsqWufXF){kYdbSACeLL = true;}
      if(IOksTcSFDR == PkattCQuwc){YqiYVjUJyB = true;}
      if(mLIorjndVX == PmDUXUNcrO){ILQQHwYoNY = true;}
      if(lQRcJSAcrW == ZwQlPzFXhY){sFfpHwcqRE = true;}
      while(PkattCQuwc == IOksTcSFDR){XOJcMgqNSX = true;}
      while(PmDUXUNcrO == PmDUXUNcrO){mRaWFQaQze = true;}
      while(ZwQlPzFXhY == ZwQlPzFXhY){QdgIYFyKUs = true;}
      if(FSJizrfhpl == true){FSJizrfhpl = false;}
      if(afkIPCKEEK == true){afkIPCKEEK = false;}
      if(PGPluSTndu == true){PGPluSTndu = false;}
      if(xrMWXwcTVe == true){xrMWXwcTVe = false;}
      if(nflGmtKIWN == true){nflGmtKIWN = false;}
      if(nATXJzCXnf == true){nATXJzCXnf = false;}
      if(XrDuniTOkS == true){XrDuniTOkS = false;}
      if(YqiYVjUJyB == true){YqiYVjUJyB = false;}
      if(ILQQHwYoNY == true){ILQQHwYoNY = false;}
      if(sFfpHwcqRE == true){sFfpHwcqRE = false;}
      if(awWEnwRuBZ == true){awWEnwRuBZ = false;}
      if(dsYlXMalnq == true){dsYlXMalnq = false;}
      if(KeBMYTLsRZ == true){KeBMYTLsRZ = false;}
      if(GdqsaLnMcK == true){GdqsaLnMcK = false;}
      if(ecmmtAfsSt == true){ecmmtAfsSt = false;}
      if(UpCatutKfT == true){UpCatutKfT = false;}
      if(kYdbSACeLL == true){kYdbSACeLL = false;}
      if(XOJcMgqNSX == true){XOJcMgqNSX = false;}
      if(mRaWFQaQze == true){mRaWFQaQze = false;}
      if(QdgIYFyKUs == true){QdgIYFyKUs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSRSVYRYNJ
{ 
  void NjcBJolQTt()
  { 
      bool jbMDXNCESy = false;
      bool VsZjtsZzMo = false;
      bool UPClXLdxET = false;
      bool bxjaQpaANh = false;
      bool yuwXNNfyHK = false;
      bool WYLemUZZfL = false;
      bool jFzyWYJzTD = false;
      bool SYldqZSeYJ = false;
      bool efosxCkFmw = false;
      bool QAUBysuyBn = false;
      bool EgeErymgmN = false;
      bool CtAVgDPGAU = false;
      bool mELXmRDjey = false;
      bool dTdjFyAjAz = false;
      bool ODRZsVAzUt = false;
      bool cnygBAVHRa = false;
      bool tCBoihQPQi = false;
      bool DfFBFilkdQ = false;
      bool QEPkUoVwiE = false;
      bool bsSZFMBbpL = false;
      string tiymounFKu;
      string MxdbCnkTmB;
      string sxgXaqcgth;
      string MegNGtWnPo;
      string RagIqIbqKy;
      string xUIRKxBaLy;
      string SGLchgQQVI;
      string QwExjRQYfR;
      string OkWwjqVOCJ;
      string rwbRWLPEZK;
      string rLVBgAQLhr;
      string gcttigiOrq;
      string LBNLPTUmaY;
      string CLyVYDPUOj;
      string ZKgKcOBhho;
      string bBMizpxJkM;
      string fdkIpUeYUe;
      string RNzHQAUDiB;
      string SmEkwAzOVi;
      string GGiCDwYXTI;
      if(tiymounFKu == rLVBgAQLhr){jbMDXNCESy = true;}
      else if(rLVBgAQLhr == tiymounFKu){EgeErymgmN = true;}
      if(MxdbCnkTmB == gcttigiOrq){VsZjtsZzMo = true;}
      else if(gcttigiOrq == MxdbCnkTmB){CtAVgDPGAU = true;}
      if(sxgXaqcgth == LBNLPTUmaY){UPClXLdxET = true;}
      else if(LBNLPTUmaY == sxgXaqcgth){mELXmRDjey = true;}
      if(MegNGtWnPo == CLyVYDPUOj){bxjaQpaANh = true;}
      else if(CLyVYDPUOj == MegNGtWnPo){dTdjFyAjAz = true;}
      if(RagIqIbqKy == ZKgKcOBhho){yuwXNNfyHK = true;}
      else if(ZKgKcOBhho == RagIqIbqKy){ODRZsVAzUt = true;}
      if(xUIRKxBaLy == bBMizpxJkM){WYLemUZZfL = true;}
      else if(bBMizpxJkM == xUIRKxBaLy){cnygBAVHRa = true;}
      if(SGLchgQQVI == fdkIpUeYUe){jFzyWYJzTD = true;}
      else if(fdkIpUeYUe == SGLchgQQVI){tCBoihQPQi = true;}
      if(QwExjRQYfR == RNzHQAUDiB){SYldqZSeYJ = true;}
      if(OkWwjqVOCJ == SmEkwAzOVi){efosxCkFmw = true;}
      if(rwbRWLPEZK == GGiCDwYXTI){QAUBysuyBn = true;}
      while(RNzHQAUDiB == QwExjRQYfR){DfFBFilkdQ = true;}
      while(SmEkwAzOVi == SmEkwAzOVi){QEPkUoVwiE = true;}
      while(GGiCDwYXTI == GGiCDwYXTI){bsSZFMBbpL = true;}
      if(jbMDXNCESy == true){jbMDXNCESy = false;}
      if(VsZjtsZzMo == true){VsZjtsZzMo = false;}
      if(UPClXLdxET == true){UPClXLdxET = false;}
      if(bxjaQpaANh == true){bxjaQpaANh = false;}
      if(yuwXNNfyHK == true){yuwXNNfyHK = false;}
      if(WYLemUZZfL == true){WYLemUZZfL = false;}
      if(jFzyWYJzTD == true){jFzyWYJzTD = false;}
      if(SYldqZSeYJ == true){SYldqZSeYJ = false;}
      if(efosxCkFmw == true){efosxCkFmw = false;}
      if(QAUBysuyBn == true){QAUBysuyBn = false;}
      if(EgeErymgmN == true){EgeErymgmN = false;}
      if(CtAVgDPGAU == true){CtAVgDPGAU = false;}
      if(mELXmRDjey == true){mELXmRDjey = false;}
      if(dTdjFyAjAz == true){dTdjFyAjAz = false;}
      if(ODRZsVAzUt == true){ODRZsVAzUt = false;}
      if(cnygBAVHRa == true){cnygBAVHRa = false;}
      if(tCBoihQPQi == true){tCBoihQPQi = false;}
      if(DfFBFilkdQ == true){DfFBFilkdQ = false;}
      if(QEPkUoVwiE == true){QEPkUoVwiE = false;}
      if(bsSZFMBbpL == true){bsSZFMBbpL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDRAOCOHSN
{ 
  void fCIUaXyIgb()
  { 
      bool zLSByxKNKS = false;
      bool YypbnzQeaY = false;
      bool nghAKfAbKL = false;
      bool cStAPjjMBN = false;
      bool lRVtIytCEs = false;
      bool yOtskRdSqS = false;
      bool wiDzoGEoLD = false;
      bool ODcMmVLmrM = false;
      bool kyXQMOXBOy = false;
      bool GRViQDOWFB = false;
      bool sFpAdukgGP = false;
      bool FqZdgxKlmZ = false;
      bool hDaNxxgtui = false;
      bool HogpTfHWlR = false;
      bool dptzrOqrBT = false;
      bool rbjfTodcDg = false;
      bool NqkWHQKjJB = false;
      bool pmzUwqIbUh = false;
      bool ForbpeFAWd = false;
      bool BeTFElEWqb = false;
      string MxWOPqScrT;
      string YylPQyiNZg;
      string uhtllcrdOo;
      string BJVtnuoDNe;
      string QqTXzjFKox;
      string lDpoEdCkcm;
      string yoOCSObrbV;
      string IezuPENWmB;
      string WhoRDyTgoJ;
      string rEaafbbQFj;
      string HNhTnGDtYz;
      string QexaQQAxzU;
      string uuCScDDYPm;
      string cwRCsIAUcw;
      string tYHosNHAJO;
      string beQkoMLPqk;
      string DeelWTNugH;
      string QeTDZWnMZP;
      string wDOAKxefMg;
      string xjdrsOsVSY;
      if(MxWOPqScrT == HNhTnGDtYz){zLSByxKNKS = true;}
      else if(HNhTnGDtYz == MxWOPqScrT){sFpAdukgGP = true;}
      if(YylPQyiNZg == QexaQQAxzU){YypbnzQeaY = true;}
      else if(QexaQQAxzU == YylPQyiNZg){FqZdgxKlmZ = true;}
      if(uhtllcrdOo == uuCScDDYPm){nghAKfAbKL = true;}
      else if(uuCScDDYPm == uhtllcrdOo){hDaNxxgtui = true;}
      if(BJVtnuoDNe == cwRCsIAUcw){cStAPjjMBN = true;}
      else if(cwRCsIAUcw == BJVtnuoDNe){HogpTfHWlR = true;}
      if(QqTXzjFKox == tYHosNHAJO){lRVtIytCEs = true;}
      else if(tYHosNHAJO == QqTXzjFKox){dptzrOqrBT = true;}
      if(lDpoEdCkcm == beQkoMLPqk){yOtskRdSqS = true;}
      else if(beQkoMLPqk == lDpoEdCkcm){rbjfTodcDg = true;}
      if(yoOCSObrbV == DeelWTNugH){wiDzoGEoLD = true;}
      else if(DeelWTNugH == yoOCSObrbV){NqkWHQKjJB = true;}
      if(IezuPENWmB == QeTDZWnMZP){ODcMmVLmrM = true;}
      if(WhoRDyTgoJ == wDOAKxefMg){kyXQMOXBOy = true;}
      if(rEaafbbQFj == xjdrsOsVSY){GRViQDOWFB = true;}
      while(QeTDZWnMZP == IezuPENWmB){pmzUwqIbUh = true;}
      while(wDOAKxefMg == wDOAKxefMg){ForbpeFAWd = true;}
      while(xjdrsOsVSY == xjdrsOsVSY){BeTFElEWqb = true;}
      if(zLSByxKNKS == true){zLSByxKNKS = false;}
      if(YypbnzQeaY == true){YypbnzQeaY = false;}
      if(nghAKfAbKL == true){nghAKfAbKL = false;}
      if(cStAPjjMBN == true){cStAPjjMBN = false;}
      if(lRVtIytCEs == true){lRVtIytCEs = false;}
      if(yOtskRdSqS == true){yOtskRdSqS = false;}
      if(wiDzoGEoLD == true){wiDzoGEoLD = false;}
      if(ODcMmVLmrM == true){ODcMmVLmrM = false;}
      if(kyXQMOXBOy == true){kyXQMOXBOy = false;}
      if(GRViQDOWFB == true){GRViQDOWFB = false;}
      if(sFpAdukgGP == true){sFpAdukgGP = false;}
      if(FqZdgxKlmZ == true){FqZdgxKlmZ = false;}
      if(hDaNxxgtui == true){hDaNxxgtui = false;}
      if(HogpTfHWlR == true){HogpTfHWlR = false;}
      if(dptzrOqrBT == true){dptzrOqrBT = false;}
      if(rbjfTodcDg == true){rbjfTodcDg = false;}
      if(NqkWHQKjJB == true){NqkWHQKjJB = false;}
      if(pmzUwqIbUh == true){pmzUwqIbUh = false;}
      if(ForbpeFAWd == true){ForbpeFAWd = false;}
      if(BeTFElEWqb == true){BeTFElEWqb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBBVHYJWJP
{ 
  void fIlSjrBYLN()
  { 
      bool NqAwIaRdWg = false;
      bool krphiTdTqO = false;
      bool ZnfKRpMHzB = false;
      bool pKwjxjtfQZ = false;
      bool nDrXTwNywr = false;
      bool xBoydYKpeR = false;
      bool NJdVqawFjz = false;
      bool YyCRaWwIpV = false;
      bool cOLHDnUyGX = false;
      bool YEAzLdYWgs = false;
      bool AHNxTyyXWG = false;
      bool cCzJnzxWRC = false;
      bool FxzLZTyDFw = false;
      bool xZaxUVANnF = false;
      bool pxazuVFqKM = false;
      bool fCEemCIBWz = false;
      bool AtRaICbBnS = false;
      bool yjiLLIVzPE = false;
      bool OHssPuUuKS = false;
      bool NyqnFufAqr = false;
      string DFscJQxXFT;
      string YwkHmeOOaI;
      string OYOsHccgmL;
      string mOAjTZMkhT;
      string CUXpcksQjg;
      string GSdRYepAUg;
      string nPjsfKwAmM;
      string RcfHGtAYQW;
      string iLxFFUjhKn;
      string iMPAeljdKS;
      string orcWPclVLd;
      string dRiyxbSdnK;
      string ZNpzcENebT;
      string KWNxgqhZpb;
      string hOWfKRcRDC;
      string TFpzrbCdsK;
      string PGsqTGDlQG;
      string tsnLcLpJnL;
      string aubZAFgOFF;
      string oDffMbUfMD;
      if(DFscJQxXFT == orcWPclVLd){NqAwIaRdWg = true;}
      else if(orcWPclVLd == DFscJQxXFT){AHNxTyyXWG = true;}
      if(YwkHmeOOaI == dRiyxbSdnK){krphiTdTqO = true;}
      else if(dRiyxbSdnK == YwkHmeOOaI){cCzJnzxWRC = true;}
      if(OYOsHccgmL == ZNpzcENebT){ZnfKRpMHzB = true;}
      else if(ZNpzcENebT == OYOsHccgmL){FxzLZTyDFw = true;}
      if(mOAjTZMkhT == KWNxgqhZpb){pKwjxjtfQZ = true;}
      else if(KWNxgqhZpb == mOAjTZMkhT){xZaxUVANnF = true;}
      if(CUXpcksQjg == hOWfKRcRDC){nDrXTwNywr = true;}
      else if(hOWfKRcRDC == CUXpcksQjg){pxazuVFqKM = true;}
      if(GSdRYepAUg == TFpzrbCdsK){xBoydYKpeR = true;}
      else if(TFpzrbCdsK == GSdRYepAUg){fCEemCIBWz = true;}
      if(nPjsfKwAmM == PGsqTGDlQG){NJdVqawFjz = true;}
      else if(PGsqTGDlQG == nPjsfKwAmM){AtRaICbBnS = true;}
      if(RcfHGtAYQW == tsnLcLpJnL){YyCRaWwIpV = true;}
      if(iLxFFUjhKn == aubZAFgOFF){cOLHDnUyGX = true;}
      if(iMPAeljdKS == oDffMbUfMD){YEAzLdYWgs = true;}
      while(tsnLcLpJnL == RcfHGtAYQW){yjiLLIVzPE = true;}
      while(aubZAFgOFF == aubZAFgOFF){OHssPuUuKS = true;}
      while(oDffMbUfMD == oDffMbUfMD){NyqnFufAqr = true;}
      if(NqAwIaRdWg == true){NqAwIaRdWg = false;}
      if(krphiTdTqO == true){krphiTdTqO = false;}
      if(ZnfKRpMHzB == true){ZnfKRpMHzB = false;}
      if(pKwjxjtfQZ == true){pKwjxjtfQZ = false;}
      if(nDrXTwNywr == true){nDrXTwNywr = false;}
      if(xBoydYKpeR == true){xBoydYKpeR = false;}
      if(NJdVqawFjz == true){NJdVqawFjz = false;}
      if(YyCRaWwIpV == true){YyCRaWwIpV = false;}
      if(cOLHDnUyGX == true){cOLHDnUyGX = false;}
      if(YEAzLdYWgs == true){YEAzLdYWgs = false;}
      if(AHNxTyyXWG == true){AHNxTyyXWG = false;}
      if(cCzJnzxWRC == true){cCzJnzxWRC = false;}
      if(FxzLZTyDFw == true){FxzLZTyDFw = false;}
      if(xZaxUVANnF == true){xZaxUVANnF = false;}
      if(pxazuVFqKM == true){pxazuVFqKM = false;}
      if(fCEemCIBWz == true){fCEemCIBWz = false;}
      if(AtRaICbBnS == true){AtRaICbBnS = false;}
      if(yjiLLIVzPE == true){yjiLLIVzPE = false;}
      if(OHssPuUuKS == true){OHssPuUuKS = false;}
      if(NyqnFufAqr == true){NyqnFufAqr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIAAOFFWJX
{ 
  void jMPpAkRlUa()
  { 
      bool KBGNHuSjqT = false;
      bool TbBDAOEIyD = false;
      bool JLneslcEqB = false;
      bool zirETDobai = false;
      bool RkPxrVeFfY = false;
      bool uMaLqyNaTV = false;
      bool ROrpUkjwiw = false;
      bool ZcgOkXwpmX = false;
      bool HWXSFlHfNV = false;
      bool pNHFQCrZbH = false;
      bool kiVizReMZS = false;
      bool BWnwOtpZjh = false;
      bool dDhNGLVbyi = false;
      bool eWOelXBoTn = false;
      bool HtGtUTZKqV = false;
      bool MSosdgAIcm = false;
      bool wDNqmeIIKp = false;
      bool sBGwaixnsl = false;
      bool lKkbVMgUBF = false;
      bool XsMfqEgPHp = false;
      string qIgVAFnezY;
      string BEKbBkDzPw;
      string VxEsPCObCW;
      string uGDWqzGhaX;
      string YFURQndfsx;
      string WMrMssEnFx;
      string pMccduBmkC;
      string eUXqXQclba;
      string YihFzhNqdx;
      string tScdhLbrmV;
      string mqupSCnBnb;
      string QRLeYGdXcu;
      string gKImHLrtJL;
      string nkyGngnrmx;
      string tMCCgcGxFa;
      string gDOrobiHhG;
      string JtqcmeSFqq;
      string SlkeBUIGGe;
      string FuoidjVGRL;
      string yfJgmAUZOB;
      if(qIgVAFnezY == mqupSCnBnb){KBGNHuSjqT = true;}
      else if(mqupSCnBnb == qIgVAFnezY){kiVizReMZS = true;}
      if(BEKbBkDzPw == QRLeYGdXcu){TbBDAOEIyD = true;}
      else if(QRLeYGdXcu == BEKbBkDzPw){BWnwOtpZjh = true;}
      if(VxEsPCObCW == gKImHLrtJL){JLneslcEqB = true;}
      else if(gKImHLrtJL == VxEsPCObCW){dDhNGLVbyi = true;}
      if(uGDWqzGhaX == nkyGngnrmx){zirETDobai = true;}
      else if(nkyGngnrmx == uGDWqzGhaX){eWOelXBoTn = true;}
      if(YFURQndfsx == tMCCgcGxFa){RkPxrVeFfY = true;}
      else if(tMCCgcGxFa == YFURQndfsx){HtGtUTZKqV = true;}
      if(WMrMssEnFx == gDOrobiHhG){uMaLqyNaTV = true;}
      else if(gDOrobiHhG == WMrMssEnFx){MSosdgAIcm = true;}
      if(pMccduBmkC == JtqcmeSFqq){ROrpUkjwiw = true;}
      else if(JtqcmeSFqq == pMccduBmkC){wDNqmeIIKp = true;}
      if(eUXqXQclba == SlkeBUIGGe){ZcgOkXwpmX = true;}
      if(YihFzhNqdx == FuoidjVGRL){HWXSFlHfNV = true;}
      if(tScdhLbrmV == yfJgmAUZOB){pNHFQCrZbH = true;}
      while(SlkeBUIGGe == eUXqXQclba){sBGwaixnsl = true;}
      while(FuoidjVGRL == FuoidjVGRL){lKkbVMgUBF = true;}
      while(yfJgmAUZOB == yfJgmAUZOB){XsMfqEgPHp = true;}
      if(KBGNHuSjqT == true){KBGNHuSjqT = false;}
      if(TbBDAOEIyD == true){TbBDAOEIyD = false;}
      if(JLneslcEqB == true){JLneslcEqB = false;}
      if(zirETDobai == true){zirETDobai = false;}
      if(RkPxrVeFfY == true){RkPxrVeFfY = false;}
      if(uMaLqyNaTV == true){uMaLqyNaTV = false;}
      if(ROrpUkjwiw == true){ROrpUkjwiw = false;}
      if(ZcgOkXwpmX == true){ZcgOkXwpmX = false;}
      if(HWXSFlHfNV == true){HWXSFlHfNV = false;}
      if(pNHFQCrZbH == true){pNHFQCrZbH = false;}
      if(kiVizReMZS == true){kiVizReMZS = false;}
      if(BWnwOtpZjh == true){BWnwOtpZjh = false;}
      if(dDhNGLVbyi == true){dDhNGLVbyi = false;}
      if(eWOelXBoTn == true){eWOelXBoTn = false;}
      if(HtGtUTZKqV == true){HtGtUTZKqV = false;}
      if(MSosdgAIcm == true){MSosdgAIcm = false;}
      if(wDNqmeIIKp == true){wDNqmeIIKp = false;}
      if(sBGwaixnsl == true){sBGwaixnsl = false;}
      if(lKkbVMgUBF == true){lKkbVMgUBF = false;}
      if(XsMfqEgPHp == true){XsMfqEgPHp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUQXNUPLTX
{ 
  void wUeCmlCLti()
  { 
      bool oRfyBjigal = false;
      bool gzrCYmgCLC = false;
      bool hYQxaOOjzy = false;
      bool GZtLMyGVaL = false;
      bool uJnRqAkojp = false;
      bool WVnUtPAhXl = false;
      bool UyhbeGEgoZ = false;
      bool fLaAGXkzGZ = false;
      bool dZzJajlYRw = false;
      bool xXynpxbLlj = false;
      bool wEzKJLumOW = false;
      bool eBbxIuyXBt = false;
      bool TeOsbINlKJ = false;
      bool uZMVdYaoAO = false;
      bool ozKuRwuAft = false;
      bool yDJqQQoGhA = false;
      bool yIbFaFnGSj = false;
      bool UIXmFUUTaf = false;
      bool NMGQKrPUFN = false;
      bool iTHzPfXFUM = false;
      string iinVCQduJR;
      string gRRLFbOYMF;
      string aUZXyFbzOQ;
      string HlfErRtYNn;
      string YAfwycBrVY;
      string CGcbNOJQWw;
      string negrJtlNTm;
      string gpKXfZncYV;
      string EjcoOBJDqc;
      string IdCQzsTmlD;
      string pmXhqMuEum;
      string afqArEBqdI;
      string kiVqdCmsXm;
      string GAqVfQLuxB;
      string FFIECcmBYu;
      string qbJcRHQgDn;
      string YBfHfZnUUa;
      string sGsbCfaRnB;
      string PlUcwdqODX;
      string zdqIcEYAXc;
      if(iinVCQduJR == pmXhqMuEum){oRfyBjigal = true;}
      else if(pmXhqMuEum == iinVCQduJR){wEzKJLumOW = true;}
      if(gRRLFbOYMF == afqArEBqdI){gzrCYmgCLC = true;}
      else if(afqArEBqdI == gRRLFbOYMF){eBbxIuyXBt = true;}
      if(aUZXyFbzOQ == kiVqdCmsXm){hYQxaOOjzy = true;}
      else if(kiVqdCmsXm == aUZXyFbzOQ){TeOsbINlKJ = true;}
      if(HlfErRtYNn == GAqVfQLuxB){GZtLMyGVaL = true;}
      else if(GAqVfQLuxB == HlfErRtYNn){uZMVdYaoAO = true;}
      if(YAfwycBrVY == FFIECcmBYu){uJnRqAkojp = true;}
      else if(FFIECcmBYu == YAfwycBrVY){ozKuRwuAft = true;}
      if(CGcbNOJQWw == qbJcRHQgDn){WVnUtPAhXl = true;}
      else if(qbJcRHQgDn == CGcbNOJQWw){yDJqQQoGhA = true;}
      if(negrJtlNTm == YBfHfZnUUa){UyhbeGEgoZ = true;}
      else if(YBfHfZnUUa == negrJtlNTm){yIbFaFnGSj = true;}
      if(gpKXfZncYV == sGsbCfaRnB){fLaAGXkzGZ = true;}
      if(EjcoOBJDqc == PlUcwdqODX){dZzJajlYRw = true;}
      if(IdCQzsTmlD == zdqIcEYAXc){xXynpxbLlj = true;}
      while(sGsbCfaRnB == gpKXfZncYV){UIXmFUUTaf = true;}
      while(PlUcwdqODX == PlUcwdqODX){NMGQKrPUFN = true;}
      while(zdqIcEYAXc == zdqIcEYAXc){iTHzPfXFUM = true;}
      if(oRfyBjigal == true){oRfyBjigal = false;}
      if(gzrCYmgCLC == true){gzrCYmgCLC = false;}
      if(hYQxaOOjzy == true){hYQxaOOjzy = false;}
      if(GZtLMyGVaL == true){GZtLMyGVaL = false;}
      if(uJnRqAkojp == true){uJnRqAkojp = false;}
      if(WVnUtPAhXl == true){WVnUtPAhXl = false;}
      if(UyhbeGEgoZ == true){UyhbeGEgoZ = false;}
      if(fLaAGXkzGZ == true){fLaAGXkzGZ = false;}
      if(dZzJajlYRw == true){dZzJajlYRw = false;}
      if(xXynpxbLlj == true){xXynpxbLlj = false;}
      if(wEzKJLumOW == true){wEzKJLumOW = false;}
      if(eBbxIuyXBt == true){eBbxIuyXBt = false;}
      if(TeOsbINlKJ == true){TeOsbINlKJ = false;}
      if(uZMVdYaoAO == true){uZMVdYaoAO = false;}
      if(ozKuRwuAft == true){ozKuRwuAft = false;}
      if(yDJqQQoGhA == true){yDJqQQoGhA = false;}
      if(yIbFaFnGSj == true){yIbFaFnGSj = false;}
      if(UIXmFUUTaf == true){UIXmFUUTaf = false;}
      if(NMGQKrPUFN == true){NMGQKrPUFN = false;}
      if(iTHzPfXFUM == true){iTHzPfXFUM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKWTMLBOST
{ 
  void gGuMGEKwuw()
  { 
      bool ZONUALoXCV = false;
      bool XFcXkwBiyJ = false;
      bool wuhVcgBFed = false;
      bool sqJCtSWxYQ = false;
      bool myqmqbZLlI = false;
      bool uorOyefrrT = false;
      bool JjrYcfwacR = false;
      bool ZEKgVyDudB = false;
      bool GoTWhDzuDP = false;
      bool mdEEHDFSKL = false;
      bool eyhUhqdKrz = false;
      bool bkNqMUQVpY = false;
      bool gAXNeuAFZR = false;
      bool sjkSVHHzoq = false;
      bool YoCDnBQNql = false;
      bool mibkeeaUol = false;
      bool pYjaGqzuUF = false;
      bool NQgzAqxTYc = false;
      bool elNmeJIAnq = false;
      bool glJCAAEbxx = false;
      string OHwjrBQtco;
      string eYokyuaxlS;
      string eKxYCNXugE;
      string LdFGOlPmoc;
      string gyCBoZNHok;
      string DablNEJWhd;
      string dUNXdBTiVL;
      string fmIIkfIwjb;
      string zPGuBjBSrK;
      string brEKyLkdXm;
      string GelcFPSSAh;
      string wNmGeNORVs;
      string AAqLjmiyJZ;
      string udXwUUdcol;
      string RhRJNOFyfj;
      string wSHdmFmasS;
      string gTIalSoqkK;
      string jkcjaRhgxU;
      string hjSYccVtIO;
      string gDjWExYpXu;
      if(OHwjrBQtco == GelcFPSSAh){ZONUALoXCV = true;}
      else if(GelcFPSSAh == OHwjrBQtco){eyhUhqdKrz = true;}
      if(eYokyuaxlS == wNmGeNORVs){XFcXkwBiyJ = true;}
      else if(wNmGeNORVs == eYokyuaxlS){bkNqMUQVpY = true;}
      if(eKxYCNXugE == AAqLjmiyJZ){wuhVcgBFed = true;}
      else if(AAqLjmiyJZ == eKxYCNXugE){gAXNeuAFZR = true;}
      if(LdFGOlPmoc == udXwUUdcol){sqJCtSWxYQ = true;}
      else if(udXwUUdcol == LdFGOlPmoc){sjkSVHHzoq = true;}
      if(gyCBoZNHok == RhRJNOFyfj){myqmqbZLlI = true;}
      else if(RhRJNOFyfj == gyCBoZNHok){YoCDnBQNql = true;}
      if(DablNEJWhd == wSHdmFmasS){uorOyefrrT = true;}
      else if(wSHdmFmasS == DablNEJWhd){mibkeeaUol = true;}
      if(dUNXdBTiVL == gTIalSoqkK){JjrYcfwacR = true;}
      else if(gTIalSoqkK == dUNXdBTiVL){pYjaGqzuUF = true;}
      if(fmIIkfIwjb == jkcjaRhgxU){ZEKgVyDudB = true;}
      if(zPGuBjBSrK == hjSYccVtIO){GoTWhDzuDP = true;}
      if(brEKyLkdXm == gDjWExYpXu){mdEEHDFSKL = true;}
      while(jkcjaRhgxU == fmIIkfIwjb){NQgzAqxTYc = true;}
      while(hjSYccVtIO == hjSYccVtIO){elNmeJIAnq = true;}
      while(gDjWExYpXu == gDjWExYpXu){glJCAAEbxx = true;}
      if(ZONUALoXCV == true){ZONUALoXCV = false;}
      if(XFcXkwBiyJ == true){XFcXkwBiyJ = false;}
      if(wuhVcgBFed == true){wuhVcgBFed = false;}
      if(sqJCtSWxYQ == true){sqJCtSWxYQ = false;}
      if(myqmqbZLlI == true){myqmqbZLlI = false;}
      if(uorOyefrrT == true){uorOyefrrT = false;}
      if(JjrYcfwacR == true){JjrYcfwacR = false;}
      if(ZEKgVyDudB == true){ZEKgVyDudB = false;}
      if(GoTWhDzuDP == true){GoTWhDzuDP = false;}
      if(mdEEHDFSKL == true){mdEEHDFSKL = false;}
      if(eyhUhqdKrz == true){eyhUhqdKrz = false;}
      if(bkNqMUQVpY == true){bkNqMUQVpY = false;}
      if(gAXNeuAFZR == true){gAXNeuAFZR = false;}
      if(sjkSVHHzoq == true){sjkSVHHzoq = false;}
      if(YoCDnBQNql == true){YoCDnBQNql = false;}
      if(mibkeeaUol == true){mibkeeaUol = false;}
      if(pYjaGqzuUF == true){pYjaGqzuUF = false;}
      if(NQgzAqxTYc == true){NQgzAqxTYc = false;}
      if(elNmeJIAnq == true){elNmeJIAnq = false;}
      if(glJCAAEbxx == true){glJCAAEbxx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMGPORPXJQ
{ 
  void JWrysfHtzT()
  { 
      bool hRmaQnMJZH = false;
      bool oGhDplQeWM = false;
      bool DwZPpDDycR = false;
      bool PwsutIDYUw = false;
      bool aCzezxZhtM = false;
      bool fyAeUkqXjM = false;
      bool kNfIqsMlJh = false;
      bool iqJZkAxtPs = false;
      bool dUDQlRuOaI = false;
      bool QenHLMWqnG = false;
      bool kmYMcnnasT = false;
      bool nxHqiPKPWZ = false;
      bool xxLAQDCCNY = false;
      bool dFGJHpwpmx = false;
      bool dUUGTSXxXw = false;
      bool CGTOImbYwZ = false;
      bool llMUphqyis = false;
      bool STbYubcEfx = false;
      bool fFdRVWkrAU = false;
      bool NXtNLrIzPl = false;
      string XayVsSpebq;
      string ScbJOtjxqW;
      string yWQVMmhGah;
      string RJbYBwIEQg;
      string VijouIXQcF;
      string sSmYyAKbIF;
      string kjEtZIBDHR;
      string kffJBOmbaE;
      string PRcUozWCaA;
      string lfwKwkepOl;
      string GTILUMldXi;
      string NiBDpTHiEa;
      string lycGeEiUNP;
      string ixMnyuIRAb;
      string MseqmDerUb;
      string duknAIqBfP;
      string cQQHAPVNFt;
      string KoibNsSkTb;
      string ZqAkkmMYmo;
      string DHljzwcWqX;
      if(XayVsSpebq == GTILUMldXi){hRmaQnMJZH = true;}
      else if(GTILUMldXi == XayVsSpebq){kmYMcnnasT = true;}
      if(ScbJOtjxqW == NiBDpTHiEa){oGhDplQeWM = true;}
      else if(NiBDpTHiEa == ScbJOtjxqW){nxHqiPKPWZ = true;}
      if(yWQVMmhGah == lycGeEiUNP){DwZPpDDycR = true;}
      else if(lycGeEiUNP == yWQVMmhGah){xxLAQDCCNY = true;}
      if(RJbYBwIEQg == ixMnyuIRAb){PwsutIDYUw = true;}
      else if(ixMnyuIRAb == RJbYBwIEQg){dFGJHpwpmx = true;}
      if(VijouIXQcF == MseqmDerUb){aCzezxZhtM = true;}
      else if(MseqmDerUb == VijouIXQcF){dUUGTSXxXw = true;}
      if(sSmYyAKbIF == duknAIqBfP){fyAeUkqXjM = true;}
      else if(duknAIqBfP == sSmYyAKbIF){CGTOImbYwZ = true;}
      if(kjEtZIBDHR == cQQHAPVNFt){kNfIqsMlJh = true;}
      else if(cQQHAPVNFt == kjEtZIBDHR){llMUphqyis = true;}
      if(kffJBOmbaE == KoibNsSkTb){iqJZkAxtPs = true;}
      if(PRcUozWCaA == ZqAkkmMYmo){dUDQlRuOaI = true;}
      if(lfwKwkepOl == DHljzwcWqX){QenHLMWqnG = true;}
      while(KoibNsSkTb == kffJBOmbaE){STbYubcEfx = true;}
      while(ZqAkkmMYmo == ZqAkkmMYmo){fFdRVWkrAU = true;}
      while(DHljzwcWqX == DHljzwcWqX){NXtNLrIzPl = true;}
      if(hRmaQnMJZH == true){hRmaQnMJZH = false;}
      if(oGhDplQeWM == true){oGhDplQeWM = false;}
      if(DwZPpDDycR == true){DwZPpDDycR = false;}
      if(PwsutIDYUw == true){PwsutIDYUw = false;}
      if(aCzezxZhtM == true){aCzezxZhtM = false;}
      if(fyAeUkqXjM == true){fyAeUkqXjM = false;}
      if(kNfIqsMlJh == true){kNfIqsMlJh = false;}
      if(iqJZkAxtPs == true){iqJZkAxtPs = false;}
      if(dUDQlRuOaI == true){dUDQlRuOaI = false;}
      if(QenHLMWqnG == true){QenHLMWqnG = false;}
      if(kmYMcnnasT == true){kmYMcnnasT = false;}
      if(nxHqiPKPWZ == true){nxHqiPKPWZ = false;}
      if(xxLAQDCCNY == true){xxLAQDCCNY = false;}
      if(dFGJHpwpmx == true){dFGJHpwpmx = false;}
      if(dUUGTSXxXw == true){dUUGTSXxXw = false;}
      if(CGTOImbYwZ == true){CGTOImbYwZ = false;}
      if(llMUphqyis == true){llMUphqyis = false;}
      if(STbYubcEfx == true){STbYubcEfx = false;}
      if(fFdRVWkrAU == true){fFdRVWkrAU = false;}
      if(NXtNLrIzPl == true){NXtNLrIzPl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGYJTCLYQG
{ 
  void KarJdnwMXE()
  { 
      bool ZaRKmtFoSQ = false;
      bool HqUhzhXkyf = false;
      bool oJERJPQZum = false;
      bool JmMnejSLey = false;
      bool ulCGgeRUji = false;
      bool KWfaQQVzAX = false;
      bool cfseHUdfDP = false;
      bool PLGzkDGyke = false;
      bool xwoLcmHkWO = false;
      bool NSLGVPrXyM = false;
      bool AkQUTzPfpN = false;
      bool JWOVZgpgCU = false;
      bool NrJoBwAAdV = false;
      bool KiAXdMeUrc = false;
      bool WauIEqDogn = false;
      bool YLVdyHbbTW = false;
      bool zPCTDZWprN = false;
      bool BUoYxlwAjK = false;
      bool sKSowyNVZW = false;
      bool jCBVdHYbEe = false;
      string xElcigzRBg;
      string puSPqqtchG;
      string aeQiiUuxtt;
      string AmsVhiooPf;
      string aqFSPLSNGa;
      string hSObhSmCsO;
      string lBXHfCBxgH;
      string BFMCejZxTX;
      string ChpTLhYQmP;
      string wmuBtYTxmM;
      string JUfzYbFMwy;
      string spiVLDKDwy;
      string dkJRLOJLIG;
      string QbKGNgBqti;
      string bLToWFDZop;
      string NPBoiYLOnK;
      string RtDphQecHe;
      string CTJMVRQTtF;
      string KjWSrBaVXo;
      string VlDjQhIdHG;
      if(xElcigzRBg == JUfzYbFMwy){ZaRKmtFoSQ = true;}
      else if(JUfzYbFMwy == xElcigzRBg){AkQUTzPfpN = true;}
      if(puSPqqtchG == spiVLDKDwy){HqUhzhXkyf = true;}
      else if(spiVLDKDwy == puSPqqtchG){JWOVZgpgCU = true;}
      if(aeQiiUuxtt == dkJRLOJLIG){oJERJPQZum = true;}
      else if(dkJRLOJLIG == aeQiiUuxtt){NrJoBwAAdV = true;}
      if(AmsVhiooPf == QbKGNgBqti){JmMnejSLey = true;}
      else if(QbKGNgBqti == AmsVhiooPf){KiAXdMeUrc = true;}
      if(aqFSPLSNGa == bLToWFDZop){ulCGgeRUji = true;}
      else if(bLToWFDZop == aqFSPLSNGa){WauIEqDogn = true;}
      if(hSObhSmCsO == NPBoiYLOnK){KWfaQQVzAX = true;}
      else if(NPBoiYLOnK == hSObhSmCsO){YLVdyHbbTW = true;}
      if(lBXHfCBxgH == RtDphQecHe){cfseHUdfDP = true;}
      else if(RtDphQecHe == lBXHfCBxgH){zPCTDZWprN = true;}
      if(BFMCejZxTX == CTJMVRQTtF){PLGzkDGyke = true;}
      if(ChpTLhYQmP == KjWSrBaVXo){xwoLcmHkWO = true;}
      if(wmuBtYTxmM == VlDjQhIdHG){NSLGVPrXyM = true;}
      while(CTJMVRQTtF == BFMCejZxTX){BUoYxlwAjK = true;}
      while(KjWSrBaVXo == KjWSrBaVXo){sKSowyNVZW = true;}
      while(VlDjQhIdHG == VlDjQhIdHG){jCBVdHYbEe = true;}
      if(ZaRKmtFoSQ == true){ZaRKmtFoSQ = false;}
      if(HqUhzhXkyf == true){HqUhzhXkyf = false;}
      if(oJERJPQZum == true){oJERJPQZum = false;}
      if(JmMnejSLey == true){JmMnejSLey = false;}
      if(ulCGgeRUji == true){ulCGgeRUji = false;}
      if(KWfaQQVzAX == true){KWfaQQVzAX = false;}
      if(cfseHUdfDP == true){cfseHUdfDP = false;}
      if(PLGzkDGyke == true){PLGzkDGyke = false;}
      if(xwoLcmHkWO == true){xwoLcmHkWO = false;}
      if(NSLGVPrXyM == true){NSLGVPrXyM = false;}
      if(AkQUTzPfpN == true){AkQUTzPfpN = false;}
      if(JWOVZgpgCU == true){JWOVZgpgCU = false;}
      if(NrJoBwAAdV == true){NrJoBwAAdV = false;}
      if(KiAXdMeUrc == true){KiAXdMeUrc = false;}
      if(WauIEqDogn == true){WauIEqDogn = false;}
      if(YLVdyHbbTW == true){YLVdyHbbTW = false;}
      if(zPCTDZWprN == true){zPCTDZWprN = false;}
      if(BUoYxlwAjK == true){BUoYxlwAjK = false;}
      if(sKSowyNVZW == true){sKSowyNVZW = false;}
      if(jCBVdHYbEe == true){jCBVdHYbEe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CILKJIZHWQ
{ 
  void lNmQQSRZTT()
  { 
      bool ikBECRxhGu = false;
      bool AoZazxteGM = false;
      bool YwHaxWJHQb = false;
      bool thsrTlWNMJ = false;
      bool TYKeromMeA = false;
      bool rVaVBlcaHe = false;
      bool IoRdBRwhGN = false;
      bool afSxrAlbhH = false;
      bool jwcQjXGWqg = false;
      bool IuGgAdHfdZ = false;
      bool rFFRYLDddA = false;
      bool ABszuLMAtc = false;
      bool KZqZEeZkwN = false;
      bool sFxHPdqLqX = false;
      bool UcspfHCGkn = false;
      bool RGkBOSOfNs = false;
      bool lRgPGtDkjQ = false;
      bool UBIWHhfAsw = false;
      bool cTAHwmUwrw = false;
      bool PKxykCucjl = false;
      string FMQgLRarKE;
      string wthdQhOgTI;
      string EjmOGmERnq;
      string cPeAMVVWco;
      string nczNNHlhXY;
      string HPZsHVYBaY;
      string MJDSbfPgQt;
      string LqDdUajYAz;
      string AWtPjMplsq;
      string wUwEcdYflh;
      string rERcNPMuXf;
      string kABaXpOniP;
      string pcnYyptzBp;
      string CEmSHuFRBT;
      string AtOMGuTVgm;
      string PjxVqOQrdW;
      string VMsgdfMhTb;
      string jxmOPuOaSC;
      string WYSOaRGQar;
      string eMnexmBghZ;
      if(FMQgLRarKE == rERcNPMuXf){ikBECRxhGu = true;}
      else if(rERcNPMuXf == FMQgLRarKE){rFFRYLDddA = true;}
      if(wthdQhOgTI == kABaXpOniP){AoZazxteGM = true;}
      else if(kABaXpOniP == wthdQhOgTI){ABszuLMAtc = true;}
      if(EjmOGmERnq == pcnYyptzBp){YwHaxWJHQb = true;}
      else if(pcnYyptzBp == EjmOGmERnq){KZqZEeZkwN = true;}
      if(cPeAMVVWco == CEmSHuFRBT){thsrTlWNMJ = true;}
      else if(CEmSHuFRBT == cPeAMVVWco){sFxHPdqLqX = true;}
      if(nczNNHlhXY == AtOMGuTVgm){TYKeromMeA = true;}
      else if(AtOMGuTVgm == nczNNHlhXY){UcspfHCGkn = true;}
      if(HPZsHVYBaY == PjxVqOQrdW){rVaVBlcaHe = true;}
      else if(PjxVqOQrdW == HPZsHVYBaY){RGkBOSOfNs = true;}
      if(MJDSbfPgQt == VMsgdfMhTb){IoRdBRwhGN = true;}
      else if(VMsgdfMhTb == MJDSbfPgQt){lRgPGtDkjQ = true;}
      if(LqDdUajYAz == jxmOPuOaSC){afSxrAlbhH = true;}
      if(AWtPjMplsq == WYSOaRGQar){jwcQjXGWqg = true;}
      if(wUwEcdYflh == eMnexmBghZ){IuGgAdHfdZ = true;}
      while(jxmOPuOaSC == LqDdUajYAz){UBIWHhfAsw = true;}
      while(WYSOaRGQar == WYSOaRGQar){cTAHwmUwrw = true;}
      while(eMnexmBghZ == eMnexmBghZ){PKxykCucjl = true;}
      if(ikBECRxhGu == true){ikBECRxhGu = false;}
      if(AoZazxteGM == true){AoZazxteGM = false;}
      if(YwHaxWJHQb == true){YwHaxWJHQb = false;}
      if(thsrTlWNMJ == true){thsrTlWNMJ = false;}
      if(TYKeromMeA == true){TYKeromMeA = false;}
      if(rVaVBlcaHe == true){rVaVBlcaHe = false;}
      if(IoRdBRwhGN == true){IoRdBRwhGN = false;}
      if(afSxrAlbhH == true){afSxrAlbhH = false;}
      if(jwcQjXGWqg == true){jwcQjXGWqg = false;}
      if(IuGgAdHfdZ == true){IuGgAdHfdZ = false;}
      if(rFFRYLDddA == true){rFFRYLDddA = false;}
      if(ABszuLMAtc == true){ABszuLMAtc = false;}
      if(KZqZEeZkwN == true){KZqZEeZkwN = false;}
      if(sFxHPdqLqX == true){sFxHPdqLqX = false;}
      if(UcspfHCGkn == true){UcspfHCGkn = false;}
      if(RGkBOSOfNs == true){RGkBOSOfNs = false;}
      if(lRgPGtDkjQ == true){lRgPGtDkjQ = false;}
      if(UBIWHhfAsw == true){UBIWHhfAsw = false;}
      if(cTAHwmUwrw == true){cTAHwmUwrw = false;}
      if(PKxykCucjl == true){PKxykCucjl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPKHPRXKFM
{ 
  void ynqrSYGSrH()
  { 
      bool TRhLVAFCqg = false;
      bool rZZwrfWEsH = false;
      bool XbItQbslna = false;
      bool VkqmYyiqNl = false;
      bool wffKURjKPo = false;
      bool SSWnyqImts = false;
      bool HTNPKHhlXs = false;
      bool xepHKrwxZz = false;
      bool riWzHDNCog = false;
      bool ouxUebRPzN = false;
      bool jxlVqmcPdG = false;
      bool uKNuAYwOIH = false;
      bool sewpEChUbh = false;
      bool afyLPtwBHU = false;
      bool ZyYilegBUG = false;
      bool eCHqUEBwRn = false;
      bool FHnuePMBfF = false;
      bool buHnguFMEY = false;
      bool VfAVCXXGqK = false;
      bool sAjTOSJdDV = false;
      string IVlquhKfxS;
      string oxqUWWuKFg;
      string iZPUUXqPPu;
      string UwcjJICeFc;
      string tYqpXPNeQK;
      string VEHIUhGQWX;
      string quPCysTHLO;
      string TQFcmKiYxE;
      string KLyFYPoTOa;
      string BlIhlyIord;
      string uFTCpFydVK;
      string zgTRNexJci;
      string DArjMhHXqo;
      string BtgSIErwPS;
      string QKyEaTRqUH;
      string BzLIauMioH;
      string xamgIFAAII;
      string lAsJRsCmJr;
      string PQDimBhXrN;
      string qJGHVpWQwV;
      if(IVlquhKfxS == uFTCpFydVK){TRhLVAFCqg = true;}
      else if(uFTCpFydVK == IVlquhKfxS){jxlVqmcPdG = true;}
      if(oxqUWWuKFg == zgTRNexJci){rZZwrfWEsH = true;}
      else if(zgTRNexJci == oxqUWWuKFg){uKNuAYwOIH = true;}
      if(iZPUUXqPPu == DArjMhHXqo){XbItQbslna = true;}
      else if(DArjMhHXqo == iZPUUXqPPu){sewpEChUbh = true;}
      if(UwcjJICeFc == BtgSIErwPS){VkqmYyiqNl = true;}
      else if(BtgSIErwPS == UwcjJICeFc){afyLPtwBHU = true;}
      if(tYqpXPNeQK == QKyEaTRqUH){wffKURjKPo = true;}
      else if(QKyEaTRqUH == tYqpXPNeQK){ZyYilegBUG = true;}
      if(VEHIUhGQWX == BzLIauMioH){SSWnyqImts = true;}
      else if(BzLIauMioH == VEHIUhGQWX){eCHqUEBwRn = true;}
      if(quPCysTHLO == xamgIFAAII){HTNPKHhlXs = true;}
      else if(xamgIFAAII == quPCysTHLO){FHnuePMBfF = true;}
      if(TQFcmKiYxE == lAsJRsCmJr){xepHKrwxZz = true;}
      if(KLyFYPoTOa == PQDimBhXrN){riWzHDNCog = true;}
      if(BlIhlyIord == qJGHVpWQwV){ouxUebRPzN = true;}
      while(lAsJRsCmJr == TQFcmKiYxE){buHnguFMEY = true;}
      while(PQDimBhXrN == PQDimBhXrN){VfAVCXXGqK = true;}
      while(qJGHVpWQwV == qJGHVpWQwV){sAjTOSJdDV = true;}
      if(TRhLVAFCqg == true){TRhLVAFCqg = false;}
      if(rZZwrfWEsH == true){rZZwrfWEsH = false;}
      if(XbItQbslna == true){XbItQbslna = false;}
      if(VkqmYyiqNl == true){VkqmYyiqNl = false;}
      if(wffKURjKPo == true){wffKURjKPo = false;}
      if(SSWnyqImts == true){SSWnyqImts = false;}
      if(HTNPKHhlXs == true){HTNPKHhlXs = false;}
      if(xepHKrwxZz == true){xepHKrwxZz = false;}
      if(riWzHDNCog == true){riWzHDNCog = false;}
      if(ouxUebRPzN == true){ouxUebRPzN = false;}
      if(jxlVqmcPdG == true){jxlVqmcPdG = false;}
      if(uKNuAYwOIH == true){uKNuAYwOIH = false;}
      if(sewpEChUbh == true){sewpEChUbh = false;}
      if(afyLPtwBHU == true){afyLPtwBHU = false;}
      if(ZyYilegBUG == true){ZyYilegBUG = false;}
      if(eCHqUEBwRn == true){eCHqUEBwRn = false;}
      if(FHnuePMBfF == true){FHnuePMBfF = false;}
      if(buHnguFMEY == true){buHnguFMEY = false;}
      if(VfAVCXXGqK == true){VfAVCXXGqK = false;}
      if(sAjTOSJdDV == true){sAjTOSJdDV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSKDXDUBMW
{ 
  void PCngArnADU()
  { 
      bool alpjgxAXsy = false;
      bool IYIkpNyUVW = false;
      bool tjjnftyDoz = false;
      bool ALrusHMYqO = false;
      bool LXETHPePCB = false;
      bool ygolMpCCEl = false;
      bool ywhsyxfNqh = false;
      bool BZcHKWePfP = false;
      bool OhBnASVGiD = false;
      bool FJTEQPoLVJ = false;
      bool jRYTzYDhap = false;
      bool LlWoXPutrf = false;
      bool bZdncrFXqu = false;
      bool hTtVfwJhob = false;
      bool OmesqSlegA = false;
      bool TtSohKmjpG = false;
      bool TfqfHrrAJa = false;
      bool FNFQQntkwJ = false;
      bool FaqpbmAEmU = false;
      bool IZqhIiuzkz = false;
      string sCfrPibVpc;
      string YmohosoRfF;
      string NmAqurmgEH;
      string AyjHTfAsNs;
      string wkyUYAEaqK;
      string KYUzUFBowX;
      string utQhcaChOI;
      string suDmJcofRu;
      string mMoswacjlN;
      string eLxoyBTPry;
      string yWMiRPVhpr;
      string PVWBkiFXlC;
      string xRuAdhyNnH;
      string IZnTxPAGbg;
      string EutsxInuEP;
      string wwdpAfaLFi;
      string QHshjphCEU;
      string izuFxBWCCU;
      string sDIYLMwxSQ;
      string onArPxBLJH;
      if(sCfrPibVpc == yWMiRPVhpr){alpjgxAXsy = true;}
      else if(yWMiRPVhpr == sCfrPibVpc){jRYTzYDhap = true;}
      if(YmohosoRfF == PVWBkiFXlC){IYIkpNyUVW = true;}
      else if(PVWBkiFXlC == YmohosoRfF){LlWoXPutrf = true;}
      if(NmAqurmgEH == xRuAdhyNnH){tjjnftyDoz = true;}
      else if(xRuAdhyNnH == NmAqurmgEH){bZdncrFXqu = true;}
      if(AyjHTfAsNs == IZnTxPAGbg){ALrusHMYqO = true;}
      else if(IZnTxPAGbg == AyjHTfAsNs){hTtVfwJhob = true;}
      if(wkyUYAEaqK == EutsxInuEP){LXETHPePCB = true;}
      else if(EutsxInuEP == wkyUYAEaqK){OmesqSlegA = true;}
      if(KYUzUFBowX == wwdpAfaLFi){ygolMpCCEl = true;}
      else if(wwdpAfaLFi == KYUzUFBowX){TtSohKmjpG = true;}
      if(utQhcaChOI == QHshjphCEU){ywhsyxfNqh = true;}
      else if(QHshjphCEU == utQhcaChOI){TfqfHrrAJa = true;}
      if(suDmJcofRu == izuFxBWCCU){BZcHKWePfP = true;}
      if(mMoswacjlN == sDIYLMwxSQ){OhBnASVGiD = true;}
      if(eLxoyBTPry == onArPxBLJH){FJTEQPoLVJ = true;}
      while(izuFxBWCCU == suDmJcofRu){FNFQQntkwJ = true;}
      while(sDIYLMwxSQ == sDIYLMwxSQ){FaqpbmAEmU = true;}
      while(onArPxBLJH == onArPxBLJH){IZqhIiuzkz = true;}
      if(alpjgxAXsy == true){alpjgxAXsy = false;}
      if(IYIkpNyUVW == true){IYIkpNyUVW = false;}
      if(tjjnftyDoz == true){tjjnftyDoz = false;}
      if(ALrusHMYqO == true){ALrusHMYqO = false;}
      if(LXETHPePCB == true){LXETHPePCB = false;}
      if(ygolMpCCEl == true){ygolMpCCEl = false;}
      if(ywhsyxfNqh == true){ywhsyxfNqh = false;}
      if(BZcHKWePfP == true){BZcHKWePfP = false;}
      if(OhBnASVGiD == true){OhBnASVGiD = false;}
      if(FJTEQPoLVJ == true){FJTEQPoLVJ = false;}
      if(jRYTzYDhap == true){jRYTzYDhap = false;}
      if(LlWoXPutrf == true){LlWoXPutrf = false;}
      if(bZdncrFXqu == true){bZdncrFXqu = false;}
      if(hTtVfwJhob == true){hTtVfwJhob = false;}
      if(OmesqSlegA == true){OmesqSlegA = false;}
      if(TtSohKmjpG == true){TtSohKmjpG = false;}
      if(TfqfHrrAJa == true){TfqfHrrAJa = false;}
      if(FNFQQntkwJ == true){FNFQQntkwJ = false;}
      if(FaqpbmAEmU == true){FaqpbmAEmU = false;}
      if(IZqhIiuzkz == true){IZqhIiuzkz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MHTVHKMBZS
{ 
  void RRSBTRyAXo()
  { 
      bool lfPYqJLOST = false;
      bool LlRsrIYZbK = false;
      bool YQWQryoLtN = false;
      bool OTidUbBCsY = false;
      bool kjmlHMnkRY = false;
      bool UZOpIUJzgs = false;
      bool UzTEEqCnYP = false;
      bool HVfDYnckJe = false;
      bool JDtVroFrVz = false;
      bool SCVAElPhgP = false;
      bool KALBRzsLRT = false;
      bool rXpCiQFyMO = false;
      bool lJSZxEAfym = false;
      bool XtDsUJrsEs = false;
      bool wtaBGtMTQm = false;
      bool gRVRdAhlEM = false;
      bool zNMduyUwgZ = false;
      bool YLsSSrhQTC = false;
      bool rgPLFGXkPU = false;
      bool aFoqthhwGH = false;
      string DsqsfaYyRo;
      string pVNfEgOmYB;
      string NZeeulGioi;
      string yOiZwbnXUF;
      string PVJTiVDcpM;
      string iKLJddOMyt;
      string ToIipblnib;
      string sqRTlqPKuY;
      string idrczmCZuS;
      string MaZalZMZcH;
      string iOsOSrrrWl;
      string NERZKoxfiC;
      string YMsPORRqgL;
      string eognoUjdJH;
      string tKCIFIJAPw;
      string cgpahVVczA;
      string ZAKLHXWcjp;
      string FSVbHOKjKG;
      string IRbkixzGFS;
      string yGdJgtzqAg;
      if(DsqsfaYyRo == iOsOSrrrWl){lfPYqJLOST = true;}
      else if(iOsOSrrrWl == DsqsfaYyRo){KALBRzsLRT = true;}
      if(pVNfEgOmYB == NERZKoxfiC){LlRsrIYZbK = true;}
      else if(NERZKoxfiC == pVNfEgOmYB){rXpCiQFyMO = true;}
      if(NZeeulGioi == YMsPORRqgL){YQWQryoLtN = true;}
      else if(YMsPORRqgL == NZeeulGioi){lJSZxEAfym = true;}
      if(yOiZwbnXUF == eognoUjdJH){OTidUbBCsY = true;}
      else if(eognoUjdJH == yOiZwbnXUF){XtDsUJrsEs = true;}
      if(PVJTiVDcpM == tKCIFIJAPw){kjmlHMnkRY = true;}
      else if(tKCIFIJAPw == PVJTiVDcpM){wtaBGtMTQm = true;}
      if(iKLJddOMyt == cgpahVVczA){UZOpIUJzgs = true;}
      else if(cgpahVVczA == iKLJddOMyt){gRVRdAhlEM = true;}
      if(ToIipblnib == ZAKLHXWcjp){UzTEEqCnYP = true;}
      else if(ZAKLHXWcjp == ToIipblnib){zNMduyUwgZ = true;}
      if(sqRTlqPKuY == FSVbHOKjKG){HVfDYnckJe = true;}
      if(idrczmCZuS == IRbkixzGFS){JDtVroFrVz = true;}
      if(MaZalZMZcH == yGdJgtzqAg){SCVAElPhgP = true;}
      while(FSVbHOKjKG == sqRTlqPKuY){YLsSSrhQTC = true;}
      while(IRbkixzGFS == IRbkixzGFS){rgPLFGXkPU = true;}
      while(yGdJgtzqAg == yGdJgtzqAg){aFoqthhwGH = true;}
      if(lfPYqJLOST == true){lfPYqJLOST = false;}
      if(LlRsrIYZbK == true){LlRsrIYZbK = false;}
      if(YQWQryoLtN == true){YQWQryoLtN = false;}
      if(OTidUbBCsY == true){OTidUbBCsY = false;}
      if(kjmlHMnkRY == true){kjmlHMnkRY = false;}
      if(UZOpIUJzgs == true){UZOpIUJzgs = false;}
      if(UzTEEqCnYP == true){UzTEEqCnYP = false;}
      if(HVfDYnckJe == true){HVfDYnckJe = false;}
      if(JDtVroFrVz == true){JDtVroFrVz = false;}
      if(SCVAElPhgP == true){SCVAElPhgP = false;}
      if(KALBRzsLRT == true){KALBRzsLRT = false;}
      if(rXpCiQFyMO == true){rXpCiQFyMO = false;}
      if(lJSZxEAfym == true){lJSZxEAfym = false;}
      if(XtDsUJrsEs == true){XtDsUJrsEs = false;}
      if(wtaBGtMTQm == true){wtaBGtMTQm = false;}
      if(gRVRdAhlEM == true){gRVRdAhlEM = false;}
      if(zNMduyUwgZ == true){zNMduyUwgZ = false;}
      if(YLsSSrhQTC == true){YLsSSrhQTC = false;}
      if(rgPLFGXkPU == true){rgPLFGXkPU = false;}
      if(aFoqthhwGH == true){aFoqthhwGH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CCMNIYTETH
{ 
  void aZDPxoSqRX()
  { 
      bool YSlamGufMF = false;
      bool aWeHeWzHsI = false;
      bool TZAhsjcuOI = false;
      bool SiSSmkALhR = false;
      bool hkzDFgRRQC = false;
      bool lhXTYySEgC = false;
      bool dARDmrDLTt = false;
      bool VnYaaiawbM = false;
      bool SLdLWjLztn = false;
      bool SudfngSwQN = false;
      bool cFxWfxJwsp = false;
      bool XVcTiRVFfC = false;
      bool gEReaaJsms = false;
      bool PdeOiNNHfY = false;
      bool aOFEQwSKwV = false;
      bool LNPOgYmSuF = false;
      bool nPJzZsqOjU = false;
      bool ENZGbRyNOe = false;
      bool HzxRhCOQgJ = false;
      bool ZuMakKFGdW = false;
      string RyJsZuFLwA;
      string rpNuKwgNOZ;
      string nSzOzFBXzs;
      string QgWlBRFSLi;
      string mSrHBeFdkF;
      string MywmVyyusT;
      string shMCjLSatr;
      string qOCemUarNU;
      string AXlsgSjiPC;
      string SKZqpEFoXo;
      string LdisOywRAB;
      string XGhXTVuTVQ;
      string aiKqYfnKoh;
      string OkTXJVnsdh;
      string WSiOeMcBXT;
      string JkTGNbSqTi;
      string JkbRllmJOx;
      string gCpmtIAwMM;
      string DmlUYcRMJg;
      string DwYuYkpQcs;
      if(RyJsZuFLwA == LdisOywRAB){YSlamGufMF = true;}
      else if(LdisOywRAB == RyJsZuFLwA){cFxWfxJwsp = true;}
      if(rpNuKwgNOZ == XGhXTVuTVQ){aWeHeWzHsI = true;}
      else if(XGhXTVuTVQ == rpNuKwgNOZ){XVcTiRVFfC = true;}
      if(nSzOzFBXzs == aiKqYfnKoh){TZAhsjcuOI = true;}
      else if(aiKqYfnKoh == nSzOzFBXzs){gEReaaJsms = true;}
      if(QgWlBRFSLi == OkTXJVnsdh){SiSSmkALhR = true;}
      else if(OkTXJVnsdh == QgWlBRFSLi){PdeOiNNHfY = true;}
      if(mSrHBeFdkF == WSiOeMcBXT){hkzDFgRRQC = true;}
      else if(WSiOeMcBXT == mSrHBeFdkF){aOFEQwSKwV = true;}
      if(MywmVyyusT == JkTGNbSqTi){lhXTYySEgC = true;}
      else if(JkTGNbSqTi == MywmVyyusT){LNPOgYmSuF = true;}
      if(shMCjLSatr == JkbRllmJOx){dARDmrDLTt = true;}
      else if(JkbRllmJOx == shMCjLSatr){nPJzZsqOjU = true;}
      if(qOCemUarNU == gCpmtIAwMM){VnYaaiawbM = true;}
      if(AXlsgSjiPC == DmlUYcRMJg){SLdLWjLztn = true;}
      if(SKZqpEFoXo == DwYuYkpQcs){SudfngSwQN = true;}
      while(gCpmtIAwMM == qOCemUarNU){ENZGbRyNOe = true;}
      while(DmlUYcRMJg == DmlUYcRMJg){HzxRhCOQgJ = true;}
      while(DwYuYkpQcs == DwYuYkpQcs){ZuMakKFGdW = true;}
      if(YSlamGufMF == true){YSlamGufMF = false;}
      if(aWeHeWzHsI == true){aWeHeWzHsI = false;}
      if(TZAhsjcuOI == true){TZAhsjcuOI = false;}
      if(SiSSmkALhR == true){SiSSmkALhR = false;}
      if(hkzDFgRRQC == true){hkzDFgRRQC = false;}
      if(lhXTYySEgC == true){lhXTYySEgC = false;}
      if(dARDmrDLTt == true){dARDmrDLTt = false;}
      if(VnYaaiawbM == true){VnYaaiawbM = false;}
      if(SLdLWjLztn == true){SLdLWjLztn = false;}
      if(SudfngSwQN == true){SudfngSwQN = false;}
      if(cFxWfxJwsp == true){cFxWfxJwsp = false;}
      if(XVcTiRVFfC == true){XVcTiRVFfC = false;}
      if(gEReaaJsms == true){gEReaaJsms = false;}
      if(PdeOiNNHfY == true){PdeOiNNHfY = false;}
      if(aOFEQwSKwV == true){aOFEQwSKwV = false;}
      if(LNPOgYmSuF == true){LNPOgYmSuF = false;}
      if(nPJzZsqOjU == true){nPJzZsqOjU = false;}
      if(ENZGbRyNOe == true){ENZGbRyNOe = false;}
      if(HzxRhCOQgJ == true){HzxRhCOQgJ = false;}
      if(ZuMakKFGdW == true){ZuMakKFGdW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZMLOPZFQT
{ 
  void QoFcARbIOG()
  { 
      bool nOlWFetawn = false;
      bool RRVKlOiZhY = false;
      bool pZSRMfmOjD = false;
      bool aRwzEVbIwG = false;
      bool NLCwfpQsZU = false;
      bool lIrpKNwTJZ = false;
      bool qfqrNAVVGQ = false;
      bool lacbKdWVlW = false;
      bool PtnOQRYGop = false;
      bool ZIyVOhUKif = false;
      bool UtlJhLeQef = false;
      bool pZhmKxqbbu = false;
      bool aPgQpdbHMc = false;
      bool JMlGBUHegF = false;
      bool mIbIAzZKLR = false;
      bool pshnEENVTE = false;
      bool jXDBWcmako = false;
      bool oMtWHRnXPp = false;
      bool DRuulPeyBx = false;
      bool HlKcUPFZlW = false;
      string VCUiwBBLUL;
      string PhuIOpozFN;
      string OKInHTSlpl;
      string flZguBjAbg;
      string jCGJrEyLWg;
      string gJaEYLsgab;
      string hOUiedHOMN;
      string GoWYcMDzwD;
      string UHPJEVLVIj;
      string HDYzyVgXdO;
      string wjyIZrlBaM;
      string HtkWGayKeI;
      string RlGcFDPXZH;
      string efUgHkIHiL;
      string jJtubNSBrX;
      string WVsUwJcVCW;
      string cObTgbZDPV;
      string RqaSYIrKAr;
      string kNeCkIlzkx;
      string IlEMiVhaOA;
      if(VCUiwBBLUL == wjyIZrlBaM){nOlWFetawn = true;}
      else if(wjyIZrlBaM == VCUiwBBLUL){UtlJhLeQef = true;}
      if(PhuIOpozFN == HtkWGayKeI){RRVKlOiZhY = true;}
      else if(HtkWGayKeI == PhuIOpozFN){pZhmKxqbbu = true;}
      if(OKInHTSlpl == RlGcFDPXZH){pZSRMfmOjD = true;}
      else if(RlGcFDPXZH == OKInHTSlpl){aPgQpdbHMc = true;}
      if(flZguBjAbg == efUgHkIHiL){aRwzEVbIwG = true;}
      else if(efUgHkIHiL == flZguBjAbg){JMlGBUHegF = true;}
      if(jCGJrEyLWg == jJtubNSBrX){NLCwfpQsZU = true;}
      else if(jJtubNSBrX == jCGJrEyLWg){mIbIAzZKLR = true;}
      if(gJaEYLsgab == WVsUwJcVCW){lIrpKNwTJZ = true;}
      else if(WVsUwJcVCW == gJaEYLsgab){pshnEENVTE = true;}
      if(hOUiedHOMN == cObTgbZDPV){qfqrNAVVGQ = true;}
      else if(cObTgbZDPV == hOUiedHOMN){jXDBWcmako = true;}
      if(GoWYcMDzwD == RqaSYIrKAr){lacbKdWVlW = true;}
      if(UHPJEVLVIj == kNeCkIlzkx){PtnOQRYGop = true;}
      if(HDYzyVgXdO == IlEMiVhaOA){ZIyVOhUKif = true;}
      while(RqaSYIrKAr == GoWYcMDzwD){oMtWHRnXPp = true;}
      while(kNeCkIlzkx == kNeCkIlzkx){DRuulPeyBx = true;}
      while(IlEMiVhaOA == IlEMiVhaOA){HlKcUPFZlW = true;}
      if(nOlWFetawn == true){nOlWFetawn = false;}
      if(RRVKlOiZhY == true){RRVKlOiZhY = false;}
      if(pZSRMfmOjD == true){pZSRMfmOjD = false;}
      if(aRwzEVbIwG == true){aRwzEVbIwG = false;}
      if(NLCwfpQsZU == true){NLCwfpQsZU = false;}
      if(lIrpKNwTJZ == true){lIrpKNwTJZ = false;}
      if(qfqrNAVVGQ == true){qfqrNAVVGQ = false;}
      if(lacbKdWVlW == true){lacbKdWVlW = false;}
      if(PtnOQRYGop == true){PtnOQRYGop = false;}
      if(ZIyVOhUKif == true){ZIyVOhUKif = false;}
      if(UtlJhLeQef == true){UtlJhLeQef = false;}
      if(pZhmKxqbbu == true){pZhmKxqbbu = false;}
      if(aPgQpdbHMc == true){aPgQpdbHMc = false;}
      if(JMlGBUHegF == true){JMlGBUHegF = false;}
      if(mIbIAzZKLR == true){mIbIAzZKLR = false;}
      if(pshnEENVTE == true){pshnEENVTE = false;}
      if(jXDBWcmako == true){jXDBWcmako = false;}
      if(oMtWHRnXPp == true){oMtWHRnXPp = false;}
      if(DRuulPeyBx == true){DRuulPeyBx = false;}
      if(HlKcUPFZlW == true){HlKcUPFZlW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYOASDCTRJ
{ 
  void ngDnNbaUWr()
  { 
      bool mysOLbicAw = false;
      bool pqcjXxIXAJ = false;
      bool fQogiSFLjU = false;
      bool AbUlMsWKgY = false;
      bool tsLRAoyQJj = false;
      bool WJYPwVILfs = false;
      bool WWsfuOVqXe = false;
      bool ZyqbOlFWgs = false;
      bool ToCAxpCEop = false;
      bool jLdnCXAeVl = false;
      bool SHrdJXSxBJ = false;
      bool QkemZgUshF = false;
      bool LRCgtOTCYq = false;
      bool lZAtZMwXpZ = false;
      bool WEDeYygqNV = false;
      bool DGwQZBELju = false;
      bool EPXKXqjjNM = false;
      bool jwCIhHNWHw = false;
      bool hcnDmecjUX = false;
      bool HknuUGfsHh = false;
      string WWSgXKAtrT;
      string yImpEpngJT;
      string geDQVYpSBq;
      string FANXtcAiNo;
      string IKHbKQKidy;
      string AFjyQrTCKy;
      string UgsBNxtPwa;
      string pFSTLWXbFE;
      string OGnDpAPPGB;
      string JxXOUaRFNM;
      string WumCHulQms;
      string UqwGjNroLN;
      string heIuRrhEzj;
      string FRNshTTlwt;
      string NzcNfRBReG;
      string ibtAeqlqkO;
      string NhQCmDdDXP;
      string tGsQziBuOA;
      string qQYsBdWMNp;
      string gbAggehZZc;
      if(WWSgXKAtrT == WumCHulQms){mysOLbicAw = true;}
      else if(WumCHulQms == WWSgXKAtrT){SHrdJXSxBJ = true;}
      if(yImpEpngJT == UqwGjNroLN){pqcjXxIXAJ = true;}
      else if(UqwGjNroLN == yImpEpngJT){QkemZgUshF = true;}
      if(geDQVYpSBq == heIuRrhEzj){fQogiSFLjU = true;}
      else if(heIuRrhEzj == geDQVYpSBq){LRCgtOTCYq = true;}
      if(FANXtcAiNo == FRNshTTlwt){AbUlMsWKgY = true;}
      else if(FRNshTTlwt == FANXtcAiNo){lZAtZMwXpZ = true;}
      if(IKHbKQKidy == NzcNfRBReG){tsLRAoyQJj = true;}
      else if(NzcNfRBReG == IKHbKQKidy){WEDeYygqNV = true;}
      if(AFjyQrTCKy == ibtAeqlqkO){WJYPwVILfs = true;}
      else if(ibtAeqlqkO == AFjyQrTCKy){DGwQZBELju = true;}
      if(UgsBNxtPwa == NhQCmDdDXP){WWsfuOVqXe = true;}
      else if(NhQCmDdDXP == UgsBNxtPwa){EPXKXqjjNM = true;}
      if(pFSTLWXbFE == tGsQziBuOA){ZyqbOlFWgs = true;}
      if(OGnDpAPPGB == qQYsBdWMNp){ToCAxpCEop = true;}
      if(JxXOUaRFNM == gbAggehZZc){jLdnCXAeVl = true;}
      while(tGsQziBuOA == pFSTLWXbFE){jwCIhHNWHw = true;}
      while(qQYsBdWMNp == qQYsBdWMNp){hcnDmecjUX = true;}
      while(gbAggehZZc == gbAggehZZc){HknuUGfsHh = true;}
      if(mysOLbicAw == true){mysOLbicAw = false;}
      if(pqcjXxIXAJ == true){pqcjXxIXAJ = false;}
      if(fQogiSFLjU == true){fQogiSFLjU = false;}
      if(AbUlMsWKgY == true){AbUlMsWKgY = false;}
      if(tsLRAoyQJj == true){tsLRAoyQJj = false;}
      if(WJYPwVILfs == true){WJYPwVILfs = false;}
      if(WWsfuOVqXe == true){WWsfuOVqXe = false;}
      if(ZyqbOlFWgs == true){ZyqbOlFWgs = false;}
      if(ToCAxpCEop == true){ToCAxpCEop = false;}
      if(jLdnCXAeVl == true){jLdnCXAeVl = false;}
      if(SHrdJXSxBJ == true){SHrdJXSxBJ = false;}
      if(QkemZgUshF == true){QkemZgUshF = false;}
      if(LRCgtOTCYq == true){LRCgtOTCYq = false;}
      if(lZAtZMwXpZ == true){lZAtZMwXpZ = false;}
      if(WEDeYygqNV == true){WEDeYygqNV = false;}
      if(DGwQZBELju == true){DGwQZBELju = false;}
      if(EPXKXqjjNM == true){EPXKXqjjNM = false;}
      if(jwCIhHNWHw == true){jwCIhHNWHw = false;}
      if(hcnDmecjUX == true){hcnDmecjUX = false;}
      if(HknuUGfsHh == true){HknuUGfsHh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXERIUMTCM
{ 
  void TxdkPPPisZ()
  { 
      bool gcusFKeihh = false;
      bool GGbYiBUSQG = false;
      bool nIZPuMsdwc = false;
      bool CjebKRDeca = false;
      bool FCjrwxmNRB = false;
      bool nyMXbYDexs = false;
      bool RAlFeWaAOR = false;
      bool xoooBkXgTy = false;
      bool ZeLuoDWHAk = false;
      bool NXgjJEPdMY = false;
      bool VmzADyIWVp = false;
      bool AVLzTlnqQb = false;
      bool ATzcDZIFfw = false;
      bool UsUtblfLrp = false;
      bool tzkJkqLhQX = false;
      bool QYNkYCmVxd = false;
      bool pDqYVGBQXg = false;
      bool FczZgAiprM = false;
      bool NZnIewfiVY = false;
      bool yJOOApILnd = false;
      string zHWOdIzGOF;
      string rgtwxbtbKT;
      string dDAdquHAOw;
      string EShIebxbww;
      string VNAHNJgTjg;
      string fqgaBuGrWh;
      string AyrRAYylQU;
      string dSfNxPCsQg;
      string OmQhQNlHGi;
      string VFENuWUiGn;
      string KtCOCNLSck;
      string sNbpTNgKBm;
      string mqehzYNRRa;
      string tTlbWTjCeC;
      string BSeVoHdOsh;
      string oKhTBTPUPd;
      string AsBBqZaASA;
      string cefykTMJrq;
      string uzYikjlSZD;
      string EPlBCIQcdP;
      if(zHWOdIzGOF == KtCOCNLSck){gcusFKeihh = true;}
      else if(KtCOCNLSck == zHWOdIzGOF){VmzADyIWVp = true;}
      if(rgtwxbtbKT == sNbpTNgKBm){GGbYiBUSQG = true;}
      else if(sNbpTNgKBm == rgtwxbtbKT){AVLzTlnqQb = true;}
      if(dDAdquHAOw == mqehzYNRRa){nIZPuMsdwc = true;}
      else if(mqehzYNRRa == dDAdquHAOw){ATzcDZIFfw = true;}
      if(EShIebxbww == tTlbWTjCeC){CjebKRDeca = true;}
      else if(tTlbWTjCeC == EShIebxbww){UsUtblfLrp = true;}
      if(VNAHNJgTjg == BSeVoHdOsh){FCjrwxmNRB = true;}
      else if(BSeVoHdOsh == VNAHNJgTjg){tzkJkqLhQX = true;}
      if(fqgaBuGrWh == oKhTBTPUPd){nyMXbYDexs = true;}
      else if(oKhTBTPUPd == fqgaBuGrWh){QYNkYCmVxd = true;}
      if(AyrRAYylQU == AsBBqZaASA){RAlFeWaAOR = true;}
      else if(AsBBqZaASA == AyrRAYylQU){pDqYVGBQXg = true;}
      if(dSfNxPCsQg == cefykTMJrq){xoooBkXgTy = true;}
      if(OmQhQNlHGi == uzYikjlSZD){ZeLuoDWHAk = true;}
      if(VFENuWUiGn == EPlBCIQcdP){NXgjJEPdMY = true;}
      while(cefykTMJrq == dSfNxPCsQg){FczZgAiprM = true;}
      while(uzYikjlSZD == uzYikjlSZD){NZnIewfiVY = true;}
      while(EPlBCIQcdP == EPlBCIQcdP){yJOOApILnd = true;}
      if(gcusFKeihh == true){gcusFKeihh = false;}
      if(GGbYiBUSQG == true){GGbYiBUSQG = false;}
      if(nIZPuMsdwc == true){nIZPuMsdwc = false;}
      if(CjebKRDeca == true){CjebKRDeca = false;}
      if(FCjrwxmNRB == true){FCjrwxmNRB = false;}
      if(nyMXbYDexs == true){nyMXbYDexs = false;}
      if(RAlFeWaAOR == true){RAlFeWaAOR = false;}
      if(xoooBkXgTy == true){xoooBkXgTy = false;}
      if(ZeLuoDWHAk == true){ZeLuoDWHAk = false;}
      if(NXgjJEPdMY == true){NXgjJEPdMY = false;}
      if(VmzADyIWVp == true){VmzADyIWVp = false;}
      if(AVLzTlnqQb == true){AVLzTlnqQb = false;}
      if(ATzcDZIFfw == true){ATzcDZIFfw = false;}
      if(UsUtblfLrp == true){UsUtblfLrp = false;}
      if(tzkJkqLhQX == true){tzkJkqLhQX = false;}
      if(QYNkYCmVxd == true){QYNkYCmVxd = false;}
      if(pDqYVGBQXg == true){pDqYVGBQXg = false;}
      if(FczZgAiprM == true){FczZgAiprM = false;}
      if(NZnIewfiVY == true){NZnIewfiVY = false;}
      if(yJOOApILnd == true){yJOOApILnd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBOOEWOOYU
{ 
  void rokizFZmfk()
  { 
      bool sDnNYONCtF = false;
      bool AyhQaDABID = false;
      bool aTYCZAwjzJ = false;
      bool FCUneQpDww = false;
      bool RuWeIDLCmR = false;
      bool QBLGWYelmY = false;
      bool SdDjzycskJ = false;
      bool MwEMkfxssV = false;
      bool oswgsEqORG = false;
      bool lEPXdnrlfK = false;
      bool aRRcETxzUq = false;
      bool bkrQiYgVqu = false;
      bool GObeXIgfhx = false;
      bool nKMiuXbSbZ = false;
      bool GrtadALynF = false;
      bool GVukDMolFw = false;
      bool mQQWCQYJVL = false;
      bool wNsRnOTAAW = false;
      bool xhqcqRPbei = false;
      bool hpNfloaWXM = false;
      string CzQdSxbMss;
      string pVJtBXjlzY;
      string duJNQeuBQF;
      string eTHNVsVIjf;
      string dQgrSyyCAd;
      string oZgGpGpCNn;
      string CZunNVNuXH;
      string BaCTtNNQuS;
      string gsBmQFmBWO;
      string DTuwcDUsdw;
      string jCdscNWNLc;
      string rYHtGJYIWI;
      string iMYIDgfGpq;
      string rTmyheOIJC;
      string hZotVeMBoT;
      string eMWVNXcUou;
      string hQWUjYlIMb;
      string tPyTaIWelY;
      string UeQVLfxRjJ;
      string BtSOUQCUJx;
      if(CzQdSxbMss == jCdscNWNLc){sDnNYONCtF = true;}
      else if(jCdscNWNLc == CzQdSxbMss){aRRcETxzUq = true;}
      if(pVJtBXjlzY == rYHtGJYIWI){AyhQaDABID = true;}
      else if(rYHtGJYIWI == pVJtBXjlzY){bkrQiYgVqu = true;}
      if(duJNQeuBQF == iMYIDgfGpq){aTYCZAwjzJ = true;}
      else if(iMYIDgfGpq == duJNQeuBQF){GObeXIgfhx = true;}
      if(eTHNVsVIjf == rTmyheOIJC){FCUneQpDww = true;}
      else if(rTmyheOIJC == eTHNVsVIjf){nKMiuXbSbZ = true;}
      if(dQgrSyyCAd == hZotVeMBoT){RuWeIDLCmR = true;}
      else if(hZotVeMBoT == dQgrSyyCAd){GrtadALynF = true;}
      if(oZgGpGpCNn == eMWVNXcUou){QBLGWYelmY = true;}
      else if(eMWVNXcUou == oZgGpGpCNn){GVukDMolFw = true;}
      if(CZunNVNuXH == hQWUjYlIMb){SdDjzycskJ = true;}
      else if(hQWUjYlIMb == CZunNVNuXH){mQQWCQYJVL = true;}
      if(BaCTtNNQuS == tPyTaIWelY){MwEMkfxssV = true;}
      if(gsBmQFmBWO == UeQVLfxRjJ){oswgsEqORG = true;}
      if(DTuwcDUsdw == BtSOUQCUJx){lEPXdnrlfK = true;}
      while(tPyTaIWelY == BaCTtNNQuS){wNsRnOTAAW = true;}
      while(UeQVLfxRjJ == UeQVLfxRjJ){xhqcqRPbei = true;}
      while(BtSOUQCUJx == BtSOUQCUJx){hpNfloaWXM = true;}
      if(sDnNYONCtF == true){sDnNYONCtF = false;}
      if(AyhQaDABID == true){AyhQaDABID = false;}
      if(aTYCZAwjzJ == true){aTYCZAwjzJ = false;}
      if(FCUneQpDww == true){FCUneQpDww = false;}
      if(RuWeIDLCmR == true){RuWeIDLCmR = false;}
      if(QBLGWYelmY == true){QBLGWYelmY = false;}
      if(SdDjzycskJ == true){SdDjzycskJ = false;}
      if(MwEMkfxssV == true){MwEMkfxssV = false;}
      if(oswgsEqORG == true){oswgsEqORG = false;}
      if(lEPXdnrlfK == true){lEPXdnrlfK = false;}
      if(aRRcETxzUq == true){aRRcETxzUq = false;}
      if(bkrQiYgVqu == true){bkrQiYgVqu = false;}
      if(GObeXIgfhx == true){GObeXIgfhx = false;}
      if(nKMiuXbSbZ == true){nKMiuXbSbZ = false;}
      if(GrtadALynF == true){GrtadALynF = false;}
      if(GVukDMolFw == true){GVukDMolFw = false;}
      if(mQQWCQYJVL == true){mQQWCQYJVL = false;}
      if(wNsRnOTAAW == true){wNsRnOTAAW = false;}
      if(xhqcqRPbei == true){xhqcqRPbei = false;}
      if(hpNfloaWXM == true){hpNfloaWXM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFFXNZFYQG
{ 
  void ddyAEVFjTA()
  { 
      bool pzOpQgQklO = false;
      bool SWmJsHEfpr = false;
      bool kIXRXXcqqj = false;
      bool NaSheTENAF = false;
      bool VnOKMHygMg = false;
      bool CywjmgbwRs = false;
      bool EYtBAqEEeZ = false;
      bool DpfjVwtMFQ = false;
      bool YudKhOdhtx = false;
      bool rIwGAxtMJU = false;
      bool CtCmcMSMOq = false;
      bool mOpAUJtiSl = false;
      bool MVJghusYjY = false;
      bool BgCjNesqhV = false;
      bool uRTDJcRwlq = false;
      bool CLtXHgjUFh = false;
      bool SsbooGMGlp = false;
      bool QDBxpuCGWF = false;
      bool dxmrVomdcg = false;
      bool tXkzCCodND = false;
      string BUCbjmeXzh;
      string DkmcryGogZ;
      string WpUSsWfWMf;
      string JQZyylJECX;
      string wpiHMVIOER;
      string IpzsLLAihM;
      string GHLTYlKodG;
      string oClJcfHMGX;
      string OQSuWSRgmm;
      string lZWpQoeOia;
      string LTkybGEoQf;
      string DmcKxpnQwF;
      string TdBpTPewrn;
      string ArdfMufUSP;
      string ObPHjzwMra;
      string AORcGgRtdM;
      string aHxceLJxxC;
      string JTxfqrNtGU;
      string SSDRmlZAYe;
      string dlpGoGembY;
      if(BUCbjmeXzh == LTkybGEoQf){pzOpQgQklO = true;}
      else if(LTkybGEoQf == BUCbjmeXzh){CtCmcMSMOq = true;}
      if(DkmcryGogZ == DmcKxpnQwF){SWmJsHEfpr = true;}
      else if(DmcKxpnQwF == DkmcryGogZ){mOpAUJtiSl = true;}
      if(WpUSsWfWMf == TdBpTPewrn){kIXRXXcqqj = true;}
      else if(TdBpTPewrn == WpUSsWfWMf){MVJghusYjY = true;}
      if(JQZyylJECX == ArdfMufUSP){NaSheTENAF = true;}
      else if(ArdfMufUSP == JQZyylJECX){BgCjNesqhV = true;}
      if(wpiHMVIOER == ObPHjzwMra){VnOKMHygMg = true;}
      else if(ObPHjzwMra == wpiHMVIOER){uRTDJcRwlq = true;}
      if(IpzsLLAihM == AORcGgRtdM){CywjmgbwRs = true;}
      else if(AORcGgRtdM == IpzsLLAihM){CLtXHgjUFh = true;}
      if(GHLTYlKodG == aHxceLJxxC){EYtBAqEEeZ = true;}
      else if(aHxceLJxxC == GHLTYlKodG){SsbooGMGlp = true;}
      if(oClJcfHMGX == JTxfqrNtGU){DpfjVwtMFQ = true;}
      if(OQSuWSRgmm == SSDRmlZAYe){YudKhOdhtx = true;}
      if(lZWpQoeOia == dlpGoGembY){rIwGAxtMJU = true;}
      while(JTxfqrNtGU == oClJcfHMGX){QDBxpuCGWF = true;}
      while(SSDRmlZAYe == SSDRmlZAYe){dxmrVomdcg = true;}
      while(dlpGoGembY == dlpGoGembY){tXkzCCodND = true;}
      if(pzOpQgQklO == true){pzOpQgQklO = false;}
      if(SWmJsHEfpr == true){SWmJsHEfpr = false;}
      if(kIXRXXcqqj == true){kIXRXXcqqj = false;}
      if(NaSheTENAF == true){NaSheTENAF = false;}
      if(VnOKMHygMg == true){VnOKMHygMg = false;}
      if(CywjmgbwRs == true){CywjmgbwRs = false;}
      if(EYtBAqEEeZ == true){EYtBAqEEeZ = false;}
      if(DpfjVwtMFQ == true){DpfjVwtMFQ = false;}
      if(YudKhOdhtx == true){YudKhOdhtx = false;}
      if(rIwGAxtMJU == true){rIwGAxtMJU = false;}
      if(CtCmcMSMOq == true){CtCmcMSMOq = false;}
      if(mOpAUJtiSl == true){mOpAUJtiSl = false;}
      if(MVJghusYjY == true){MVJghusYjY = false;}
      if(BgCjNesqhV == true){BgCjNesqhV = false;}
      if(uRTDJcRwlq == true){uRTDJcRwlq = false;}
      if(CLtXHgjUFh == true){CLtXHgjUFh = false;}
      if(SsbooGMGlp == true){SsbooGMGlp = false;}
      if(QDBxpuCGWF == true){QDBxpuCGWF = false;}
      if(dxmrVomdcg == true){dxmrVomdcg = false;}
      if(tXkzCCodND == true){tXkzCCodND = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGXCRQGPIT
{ 
  void BxPIwolVVQ()
  { 
      bool WycVqsGZdF = false;
      bool bXWEaWtSoY = false;
      bool aJXtmzFLIZ = false;
      bool mcsmQEjHgB = false;
      bool ZirRnaIODj = false;
      bool DZtQdNaiir = false;
      bool nuQERyeimV = false;
      bool mmknzqRFGL = false;
      bool qpIYWNibJD = false;
      bool dBYoNeSmAo = false;
      bool uZbgwPnGRl = false;
      bool uUbWBxlqhE = false;
      bool PCZjqlOuZT = false;
      bool YdFQQQOacG = false;
      bool YcKWHJYBnQ = false;
      bool raFuZszqpJ = false;
      bool BsfxNROLGj = false;
      bool hKOaelqCbh = false;
      bool NMGJaxXKpW = false;
      bool RWkSEfxNIp = false;
      string FFGpKOIwIp;
      string ngAKaHGKFB;
      string JaitxfwbLX;
      string TChqDcKybN;
      string jhfQlVrEgZ;
      string tpePLdVMse;
      string RfkjVlzIGx;
      string wHhqRbuSIb;
      string nrulccWReY;
      string GyFxwDxwtz;
      string VixiclImyj;
      string iDEQpZkzGr;
      string OgchqyCjuN;
      string dyXIFEtLIq;
      string UjTuoCtoHW;
      string SxoBkoFPre;
      string jXqjFjfuLk;
      string eYpPXeMhrn;
      string DNcYugJVXQ;
      string yeTdGxrjoE;
      if(FFGpKOIwIp == VixiclImyj){WycVqsGZdF = true;}
      else if(VixiclImyj == FFGpKOIwIp){uZbgwPnGRl = true;}
      if(ngAKaHGKFB == iDEQpZkzGr){bXWEaWtSoY = true;}
      else if(iDEQpZkzGr == ngAKaHGKFB){uUbWBxlqhE = true;}
      if(JaitxfwbLX == OgchqyCjuN){aJXtmzFLIZ = true;}
      else if(OgchqyCjuN == JaitxfwbLX){PCZjqlOuZT = true;}
      if(TChqDcKybN == dyXIFEtLIq){mcsmQEjHgB = true;}
      else if(dyXIFEtLIq == TChqDcKybN){YdFQQQOacG = true;}
      if(jhfQlVrEgZ == UjTuoCtoHW){ZirRnaIODj = true;}
      else if(UjTuoCtoHW == jhfQlVrEgZ){YcKWHJYBnQ = true;}
      if(tpePLdVMse == SxoBkoFPre){DZtQdNaiir = true;}
      else if(SxoBkoFPre == tpePLdVMse){raFuZszqpJ = true;}
      if(RfkjVlzIGx == jXqjFjfuLk){nuQERyeimV = true;}
      else if(jXqjFjfuLk == RfkjVlzIGx){BsfxNROLGj = true;}
      if(wHhqRbuSIb == eYpPXeMhrn){mmknzqRFGL = true;}
      if(nrulccWReY == DNcYugJVXQ){qpIYWNibJD = true;}
      if(GyFxwDxwtz == yeTdGxrjoE){dBYoNeSmAo = true;}
      while(eYpPXeMhrn == wHhqRbuSIb){hKOaelqCbh = true;}
      while(DNcYugJVXQ == DNcYugJVXQ){NMGJaxXKpW = true;}
      while(yeTdGxrjoE == yeTdGxrjoE){RWkSEfxNIp = true;}
      if(WycVqsGZdF == true){WycVqsGZdF = false;}
      if(bXWEaWtSoY == true){bXWEaWtSoY = false;}
      if(aJXtmzFLIZ == true){aJXtmzFLIZ = false;}
      if(mcsmQEjHgB == true){mcsmQEjHgB = false;}
      if(ZirRnaIODj == true){ZirRnaIODj = false;}
      if(DZtQdNaiir == true){DZtQdNaiir = false;}
      if(nuQERyeimV == true){nuQERyeimV = false;}
      if(mmknzqRFGL == true){mmknzqRFGL = false;}
      if(qpIYWNibJD == true){qpIYWNibJD = false;}
      if(dBYoNeSmAo == true){dBYoNeSmAo = false;}
      if(uZbgwPnGRl == true){uZbgwPnGRl = false;}
      if(uUbWBxlqhE == true){uUbWBxlqhE = false;}
      if(PCZjqlOuZT == true){PCZjqlOuZT = false;}
      if(YdFQQQOacG == true){YdFQQQOacG = false;}
      if(YcKWHJYBnQ == true){YcKWHJYBnQ = false;}
      if(raFuZszqpJ == true){raFuZszqpJ = false;}
      if(BsfxNROLGj == true){BsfxNROLGj = false;}
      if(hKOaelqCbh == true){hKOaelqCbh = false;}
      if(NMGJaxXKpW == true){NMGJaxXKpW = false;}
      if(RWkSEfxNIp == true){RWkSEfxNIp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQNIHVUKRP
{ 
  void kRShAbUzgm()
  { 
      bool pEZewMljKd = false;
      bool nIhVHillWz = false;
      bool boizjxdueQ = false;
      bool jkGlrAnPAE = false;
      bool BTypiPtnwz = false;
      bool EQekoBVZuy = false;
      bool hpEstDBwcH = false;
      bool tVkRxHprQU = false;
      bool DozeMTFVxq = false;
      bool dOUCVKPEwf = false;
      bool NyKnFheMmg = false;
      bool KcJZtspZga = false;
      bool xfyldeAium = false;
      bool rlwjGEdLYd = false;
      bool nsiPfBEtHc = false;
      bool UpXUhhAYKa = false;
      bool hwRzoXgYTp = false;
      bool OdAClEwhFb = false;
      bool ZFaRSBOaCX = false;
      bool EFBywrbiZI = false;
      string kaABxulhDY;
      string kxNbhcQfcQ;
      string kNigekIuaW;
      string GWYUABRodx;
      string uJVNEcELGk;
      string jShbmXrSWL;
      string lqGfSNYsbf;
      string LbBeVbqUcB;
      string gxopmnowgc;
      string JyRSLDCpup;
      string DKjZZHQCGL;
      string gWpUenCQsd;
      string YcMyVMKiTR;
      string YBZlyWNOQe;
      string XlpVwmIwmW;
      string AlxQRaykEM;
      string xginlexDWI;
      string anzNGmlpCh;
      string ENuwRmDIUW;
      string XcJEhpCBjQ;
      if(kaABxulhDY == DKjZZHQCGL){pEZewMljKd = true;}
      else if(DKjZZHQCGL == kaABxulhDY){NyKnFheMmg = true;}
      if(kxNbhcQfcQ == gWpUenCQsd){nIhVHillWz = true;}
      else if(gWpUenCQsd == kxNbhcQfcQ){KcJZtspZga = true;}
      if(kNigekIuaW == YcMyVMKiTR){boizjxdueQ = true;}
      else if(YcMyVMKiTR == kNigekIuaW){xfyldeAium = true;}
      if(GWYUABRodx == YBZlyWNOQe){jkGlrAnPAE = true;}
      else if(YBZlyWNOQe == GWYUABRodx){rlwjGEdLYd = true;}
      if(uJVNEcELGk == XlpVwmIwmW){BTypiPtnwz = true;}
      else if(XlpVwmIwmW == uJVNEcELGk){nsiPfBEtHc = true;}
      if(jShbmXrSWL == AlxQRaykEM){EQekoBVZuy = true;}
      else if(AlxQRaykEM == jShbmXrSWL){UpXUhhAYKa = true;}
      if(lqGfSNYsbf == xginlexDWI){hpEstDBwcH = true;}
      else if(xginlexDWI == lqGfSNYsbf){hwRzoXgYTp = true;}
      if(LbBeVbqUcB == anzNGmlpCh){tVkRxHprQU = true;}
      if(gxopmnowgc == ENuwRmDIUW){DozeMTFVxq = true;}
      if(JyRSLDCpup == XcJEhpCBjQ){dOUCVKPEwf = true;}
      while(anzNGmlpCh == LbBeVbqUcB){OdAClEwhFb = true;}
      while(ENuwRmDIUW == ENuwRmDIUW){ZFaRSBOaCX = true;}
      while(XcJEhpCBjQ == XcJEhpCBjQ){EFBywrbiZI = true;}
      if(pEZewMljKd == true){pEZewMljKd = false;}
      if(nIhVHillWz == true){nIhVHillWz = false;}
      if(boizjxdueQ == true){boizjxdueQ = false;}
      if(jkGlrAnPAE == true){jkGlrAnPAE = false;}
      if(BTypiPtnwz == true){BTypiPtnwz = false;}
      if(EQekoBVZuy == true){EQekoBVZuy = false;}
      if(hpEstDBwcH == true){hpEstDBwcH = false;}
      if(tVkRxHprQU == true){tVkRxHprQU = false;}
      if(DozeMTFVxq == true){DozeMTFVxq = false;}
      if(dOUCVKPEwf == true){dOUCVKPEwf = false;}
      if(NyKnFheMmg == true){NyKnFheMmg = false;}
      if(KcJZtspZga == true){KcJZtspZga = false;}
      if(xfyldeAium == true){xfyldeAium = false;}
      if(rlwjGEdLYd == true){rlwjGEdLYd = false;}
      if(nsiPfBEtHc == true){nsiPfBEtHc = false;}
      if(UpXUhhAYKa == true){UpXUhhAYKa = false;}
      if(hwRzoXgYTp == true){hwRzoXgYTp = false;}
      if(OdAClEwhFb == true){OdAClEwhFb = false;}
      if(ZFaRSBOaCX == true){ZFaRSBOaCX = false;}
      if(EFBywrbiZI == true){EFBywrbiZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQTCICQKOX
{ 
  void kJFPdOWnCS()
  { 
      bool LfiVTKeAYH = false;
      bool xEyuStJafs = false;
      bool foTIuaNwJZ = false;
      bool wrgtkIUJAZ = false;
      bool epFBXbMdsJ = false;
      bool PCkidVLaZr = false;
      bool xhqzKFWDKJ = false;
      bool YzZFOojSjT = false;
      bool OiDAJtGyPO = false;
      bool xtjIcwzGpR = false;
      bool EJTjjQbeTo = false;
      bool lrpFdNeqoQ = false;
      bool zYmuMePRcR = false;
      bool occSPEPSPs = false;
      bool SbdabEEdeO = false;
      bool RIRZSeVXXE = false;
      bool AJCCzJPXpY = false;
      bool xLawxWtMSH = false;
      bool almNAgLDzj = false;
      bool iruKrJZbaS = false;
      string xXnqyooGHo;
      string sBcHsuwlul;
      string gpPxGcksFY;
      string wzXCOLTHnM;
      string zRJcZcehEf;
      string FPEnSGIqkU;
      string EuBhsscZsg;
      string aoxhmPflWc;
      string yDoYSfujjH;
      string DcVTHDQbjf;
      string zEnWFQRVBD;
      string aWTHVBFbOM;
      string yrpkdxScai;
      string yDCpctOSTC;
      string NYiggfINxG;
      string xnMWhHNDsH;
      string youREWUceb;
      string mmIMyZJJEx;
      string oEfTkKqeIV;
      string fLZLDYcRbJ;
      if(xXnqyooGHo == zEnWFQRVBD){LfiVTKeAYH = true;}
      else if(zEnWFQRVBD == xXnqyooGHo){EJTjjQbeTo = true;}
      if(sBcHsuwlul == aWTHVBFbOM){xEyuStJafs = true;}
      else if(aWTHVBFbOM == sBcHsuwlul){lrpFdNeqoQ = true;}
      if(gpPxGcksFY == yrpkdxScai){foTIuaNwJZ = true;}
      else if(yrpkdxScai == gpPxGcksFY){zYmuMePRcR = true;}
      if(wzXCOLTHnM == yDCpctOSTC){wrgtkIUJAZ = true;}
      else if(yDCpctOSTC == wzXCOLTHnM){occSPEPSPs = true;}
      if(zRJcZcehEf == NYiggfINxG){epFBXbMdsJ = true;}
      else if(NYiggfINxG == zRJcZcehEf){SbdabEEdeO = true;}
      if(FPEnSGIqkU == xnMWhHNDsH){PCkidVLaZr = true;}
      else if(xnMWhHNDsH == FPEnSGIqkU){RIRZSeVXXE = true;}
      if(EuBhsscZsg == youREWUceb){xhqzKFWDKJ = true;}
      else if(youREWUceb == EuBhsscZsg){AJCCzJPXpY = true;}
      if(aoxhmPflWc == mmIMyZJJEx){YzZFOojSjT = true;}
      if(yDoYSfujjH == oEfTkKqeIV){OiDAJtGyPO = true;}
      if(DcVTHDQbjf == fLZLDYcRbJ){xtjIcwzGpR = true;}
      while(mmIMyZJJEx == aoxhmPflWc){xLawxWtMSH = true;}
      while(oEfTkKqeIV == oEfTkKqeIV){almNAgLDzj = true;}
      while(fLZLDYcRbJ == fLZLDYcRbJ){iruKrJZbaS = true;}
      if(LfiVTKeAYH == true){LfiVTKeAYH = false;}
      if(xEyuStJafs == true){xEyuStJafs = false;}
      if(foTIuaNwJZ == true){foTIuaNwJZ = false;}
      if(wrgtkIUJAZ == true){wrgtkIUJAZ = false;}
      if(epFBXbMdsJ == true){epFBXbMdsJ = false;}
      if(PCkidVLaZr == true){PCkidVLaZr = false;}
      if(xhqzKFWDKJ == true){xhqzKFWDKJ = false;}
      if(YzZFOojSjT == true){YzZFOojSjT = false;}
      if(OiDAJtGyPO == true){OiDAJtGyPO = false;}
      if(xtjIcwzGpR == true){xtjIcwzGpR = false;}
      if(EJTjjQbeTo == true){EJTjjQbeTo = false;}
      if(lrpFdNeqoQ == true){lrpFdNeqoQ = false;}
      if(zYmuMePRcR == true){zYmuMePRcR = false;}
      if(occSPEPSPs == true){occSPEPSPs = false;}
      if(SbdabEEdeO == true){SbdabEEdeO = false;}
      if(RIRZSeVXXE == true){RIRZSeVXXE = false;}
      if(AJCCzJPXpY == true){AJCCzJPXpY = false;}
      if(xLawxWtMSH == true){xLawxWtMSH = false;}
      if(almNAgLDzj == true){almNAgLDzj = false;}
      if(iruKrJZbaS == true){iruKrJZbaS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUMGWLLSBO
{ 
  void MytLwlqhag()
  { 
      bool pEVQgJojch = false;
      bool DQZPVIYgWz = false;
      bool SPJSbzTSeI = false;
      bool QVUOrQlncl = false;
      bool schiGSgAdA = false;
      bool ZiUJJZtCng = false;
      bool oWETQhuKWE = false;
      bool WkEkFohaLI = false;
      bool SSndihALFS = false;
      bool VizuwWXNRY = false;
      bool XVdYdndjET = false;
      bool rTpeOVhZki = false;
      bool giFEhmkJni = false;
      bool RTJmjwoPAt = false;
      bool DQHlZCsUfZ = false;
      bool oxchrnQYqp = false;
      bool DUuUBYJDtS = false;
      bool gSZqfPbSee = false;
      bool tQcNtTqatu = false;
      bool eQXJqhVljB = false;
      string zBfSllIGhZ;
      string tJeaMXdGCs;
      string NONiyzUuOZ;
      string AFQsHaiVGj;
      string HHswuiChif;
      string dLHudknwTm;
      string QMqIZoskTl;
      string nHARkFURnP;
      string wlMiunyUOW;
      string mmCSTtPkVG;
      string oROxrVKpJX;
      string PVHDpeAIMk;
      string pYVxzAFgyp;
      string pjugaeXOpY;
      string cIKqGQeybn;
      string tHXjPQuQyq;
      string PdqSheaacL;
      string GkRnHhNeph;
      string VHEJwhMKQJ;
      string iHQzIzQrJb;
      if(zBfSllIGhZ == oROxrVKpJX){pEVQgJojch = true;}
      else if(oROxrVKpJX == zBfSllIGhZ){XVdYdndjET = true;}
      if(tJeaMXdGCs == PVHDpeAIMk){DQZPVIYgWz = true;}
      else if(PVHDpeAIMk == tJeaMXdGCs){rTpeOVhZki = true;}
      if(NONiyzUuOZ == pYVxzAFgyp){SPJSbzTSeI = true;}
      else if(pYVxzAFgyp == NONiyzUuOZ){giFEhmkJni = true;}
      if(AFQsHaiVGj == pjugaeXOpY){QVUOrQlncl = true;}
      else if(pjugaeXOpY == AFQsHaiVGj){RTJmjwoPAt = true;}
      if(HHswuiChif == cIKqGQeybn){schiGSgAdA = true;}
      else if(cIKqGQeybn == HHswuiChif){DQHlZCsUfZ = true;}
      if(dLHudknwTm == tHXjPQuQyq){ZiUJJZtCng = true;}
      else if(tHXjPQuQyq == dLHudknwTm){oxchrnQYqp = true;}
      if(QMqIZoskTl == PdqSheaacL){oWETQhuKWE = true;}
      else if(PdqSheaacL == QMqIZoskTl){DUuUBYJDtS = true;}
      if(nHARkFURnP == GkRnHhNeph){WkEkFohaLI = true;}
      if(wlMiunyUOW == VHEJwhMKQJ){SSndihALFS = true;}
      if(mmCSTtPkVG == iHQzIzQrJb){VizuwWXNRY = true;}
      while(GkRnHhNeph == nHARkFURnP){gSZqfPbSee = true;}
      while(VHEJwhMKQJ == VHEJwhMKQJ){tQcNtTqatu = true;}
      while(iHQzIzQrJb == iHQzIzQrJb){eQXJqhVljB = true;}
      if(pEVQgJojch == true){pEVQgJojch = false;}
      if(DQZPVIYgWz == true){DQZPVIYgWz = false;}
      if(SPJSbzTSeI == true){SPJSbzTSeI = false;}
      if(QVUOrQlncl == true){QVUOrQlncl = false;}
      if(schiGSgAdA == true){schiGSgAdA = false;}
      if(ZiUJJZtCng == true){ZiUJJZtCng = false;}
      if(oWETQhuKWE == true){oWETQhuKWE = false;}
      if(WkEkFohaLI == true){WkEkFohaLI = false;}
      if(SSndihALFS == true){SSndihALFS = false;}
      if(VizuwWXNRY == true){VizuwWXNRY = false;}
      if(XVdYdndjET == true){XVdYdndjET = false;}
      if(rTpeOVhZki == true){rTpeOVhZki = false;}
      if(giFEhmkJni == true){giFEhmkJni = false;}
      if(RTJmjwoPAt == true){RTJmjwoPAt = false;}
      if(DQHlZCsUfZ == true){DQHlZCsUfZ = false;}
      if(oxchrnQYqp == true){oxchrnQYqp = false;}
      if(DUuUBYJDtS == true){DUuUBYJDtS = false;}
      if(gSZqfPbSee == true){gSZqfPbSee = false;}
      if(tQcNtTqatu == true){tQcNtTqatu = false;}
      if(eQXJqhVljB == true){eQXJqhVljB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXTDILAXJJ
{ 
  void TFogNJDPkq()
  { 
      bool HCGyCMMhpj = false;
      bool QhKocWzRqb = false;
      bool joDtuwfzBF = false;
      bool oJnQPQhkjz = false;
      bool WYphYrYnsF = false;
      bool EuaclRyLDF = false;
      bool gMgktGstZM = false;
      bool nOgqFLzVVD = false;
      bool XrGwAshKex = false;
      bool RVgdSJqFmR = false;
      bool yeOgQpNiXZ = false;
      bool ScpzhoGkjA = false;
      bool YiObtRgDYu = false;
      bool UshDErcZeK = false;
      bool fylEdofgwd = false;
      bool DGVlsPPllz = false;
      bool IKKcFYulto = false;
      bool LfFZUZwKxE = false;
      bool kzGurOXuKo = false;
      bool cpmfBVnJzF = false;
      string UgANpwCWDj;
      string iHHDuUqFCe;
      string xPzSVcEzfJ;
      string LbBFdNfBHm;
      string ZLUVKxnXub;
      string fkmrNEggrN;
      string rDpsXHGBZh;
      string ooxOFktdHY;
      string ofDDdanIrY;
      string gyJsuVUbxD;
      string plyNlqmXmb;
      string KCZSYMzlPx;
      string SxJBBqfETi;
      string QSgDhCgpQm;
      string mQVPNdXqUh;
      string WhLAkrbxMu;
      string KiDDKqVVjV;
      string fJVcJBbsmW;
      string SnilMiHfRo;
      string aicVbEMRFV;
      if(UgANpwCWDj == plyNlqmXmb){HCGyCMMhpj = true;}
      else if(plyNlqmXmb == UgANpwCWDj){yeOgQpNiXZ = true;}
      if(iHHDuUqFCe == KCZSYMzlPx){QhKocWzRqb = true;}
      else if(KCZSYMzlPx == iHHDuUqFCe){ScpzhoGkjA = true;}
      if(xPzSVcEzfJ == SxJBBqfETi){joDtuwfzBF = true;}
      else if(SxJBBqfETi == xPzSVcEzfJ){YiObtRgDYu = true;}
      if(LbBFdNfBHm == QSgDhCgpQm){oJnQPQhkjz = true;}
      else if(QSgDhCgpQm == LbBFdNfBHm){UshDErcZeK = true;}
      if(ZLUVKxnXub == mQVPNdXqUh){WYphYrYnsF = true;}
      else if(mQVPNdXqUh == ZLUVKxnXub){fylEdofgwd = true;}
      if(fkmrNEggrN == WhLAkrbxMu){EuaclRyLDF = true;}
      else if(WhLAkrbxMu == fkmrNEggrN){DGVlsPPllz = true;}
      if(rDpsXHGBZh == KiDDKqVVjV){gMgktGstZM = true;}
      else if(KiDDKqVVjV == rDpsXHGBZh){IKKcFYulto = true;}
      if(ooxOFktdHY == fJVcJBbsmW){nOgqFLzVVD = true;}
      if(ofDDdanIrY == SnilMiHfRo){XrGwAshKex = true;}
      if(gyJsuVUbxD == aicVbEMRFV){RVgdSJqFmR = true;}
      while(fJVcJBbsmW == ooxOFktdHY){LfFZUZwKxE = true;}
      while(SnilMiHfRo == SnilMiHfRo){kzGurOXuKo = true;}
      while(aicVbEMRFV == aicVbEMRFV){cpmfBVnJzF = true;}
      if(HCGyCMMhpj == true){HCGyCMMhpj = false;}
      if(QhKocWzRqb == true){QhKocWzRqb = false;}
      if(joDtuwfzBF == true){joDtuwfzBF = false;}
      if(oJnQPQhkjz == true){oJnQPQhkjz = false;}
      if(WYphYrYnsF == true){WYphYrYnsF = false;}
      if(EuaclRyLDF == true){EuaclRyLDF = false;}
      if(gMgktGstZM == true){gMgktGstZM = false;}
      if(nOgqFLzVVD == true){nOgqFLzVVD = false;}
      if(XrGwAshKex == true){XrGwAshKex = false;}
      if(RVgdSJqFmR == true){RVgdSJqFmR = false;}
      if(yeOgQpNiXZ == true){yeOgQpNiXZ = false;}
      if(ScpzhoGkjA == true){ScpzhoGkjA = false;}
      if(YiObtRgDYu == true){YiObtRgDYu = false;}
      if(UshDErcZeK == true){UshDErcZeK = false;}
      if(fylEdofgwd == true){fylEdofgwd = false;}
      if(DGVlsPPllz == true){DGVlsPPllz = false;}
      if(IKKcFYulto == true){IKKcFYulto = false;}
      if(LfFZUZwKxE == true){LfFZUZwKxE = false;}
      if(kzGurOXuKo == true){kzGurOXuKo = false;}
      if(cpmfBVnJzF == true){cpmfBVnJzF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGNIBARNZY
{ 
  void YgnBulLhJH()
  { 
      bool JWTcdzSIJK = false;
      bool AwcBxqgPNH = false;
      bool FOBikPQnRA = false;
      bool IVUHXwcUbB = false;
      bool RXNzXaxgzh = false;
      bool TaPGPtVjqN = false;
      bool idqICeaUcB = false;
      bool OMmMpgBBLK = false;
      bool SjojggFOrd = false;
      bool ZrdOSmgEwr = false;
      bool AbDxTGnDQh = false;
      bool sTYgtyoHbV = false;
      bool ZMczaViYtC = false;
      bool AwESKqgqPZ = false;
      bool rCxKjGSwTT = false;
      bool yZcaSmzDWx = false;
      bool XPINhwPGVD = false;
      bool RxqBcWORPU = false;
      bool ClEZDZTczW = false;
      bool rdURBcsjbn = false;
      string hCDCUTfyya;
      string mjuxJBhWAa;
      string dZDgGfZjRS;
      string wTkOjPkCmj;
      string KklZpqEDGj;
      string rzLdZIyWun;
      string sugfeTzfMt;
      string QeiQPrndpP;
      string bWdgZwHHob;
      string QOHypPDGtV;
      string qXpMSMPuOg;
      string UUffMWQzFi;
      string LrqjcBXjZz;
      string nhiUXDfRON;
      string gMrHHuhalT;
      string yEALKzfGiR;
      string nfVOrllLHI;
      string pzkqBzzjcg;
      string TwyFAjgWKX;
      string WZhxZBqdOU;
      if(hCDCUTfyya == qXpMSMPuOg){JWTcdzSIJK = true;}
      else if(qXpMSMPuOg == hCDCUTfyya){AbDxTGnDQh = true;}
      if(mjuxJBhWAa == UUffMWQzFi){AwcBxqgPNH = true;}
      else if(UUffMWQzFi == mjuxJBhWAa){sTYgtyoHbV = true;}
      if(dZDgGfZjRS == LrqjcBXjZz){FOBikPQnRA = true;}
      else if(LrqjcBXjZz == dZDgGfZjRS){ZMczaViYtC = true;}
      if(wTkOjPkCmj == nhiUXDfRON){IVUHXwcUbB = true;}
      else if(nhiUXDfRON == wTkOjPkCmj){AwESKqgqPZ = true;}
      if(KklZpqEDGj == gMrHHuhalT){RXNzXaxgzh = true;}
      else if(gMrHHuhalT == KklZpqEDGj){rCxKjGSwTT = true;}
      if(rzLdZIyWun == yEALKzfGiR){TaPGPtVjqN = true;}
      else if(yEALKzfGiR == rzLdZIyWun){yZcaSmzDWx = true;}
      if(sugfeTzfMt == nfVOrllLHI){idqICeaUcB = true;}
      else if(nfVOrllLHI == sugfeTzfMt){XPINhwPGVD = true;}
      if(QeiQPrndpP == pzkqBzzjcg){OMmMpgBBLK = true;}
      if(bWdgZwHHob == TwyFAjgWKX){SjojggFOrd = true;}
      if(QOHypPDGtV == WZhxZBqdOU){ZrdOSmgEwr = true;}
      while(pzkqBzzjcg == QeiQPrndpP){RxqBcWORPU = true;}
      while(TwyFAjgWKX == TwyFAjgWKX){ClEZDZTczW = true;}
      while(WZhxZBqdOU == WZhxZBqdOU){rdURBcsjbn = true;}
      if(JWTcdzSIJK == true){JWTcdzSIJK = false;}
      if(AwcBxqgPNH == true){AwcBxqgPNH = false;}
      if(FOBikPQnRA == true){FOBikPQnRA = false;}
      if(IVUHXwcUbB == true){IVUHXwcUbB = false;}
      if(RXNzXaxgzh == true){RXNzXaxgzh = false;}
      if(TaPGPtVjqN == true){TaPGPtVjqN = false;}
      if(idqICeaUcB == true){idqICeaUcB = false;}
      if(OMmMpgBBLK == true){OMmMpgBBLK = false;}
      if(SjojggFOrd == true){SjojggFOrd = false;}
      if(ZrdOSmgEwr == true){ZrdOSmgEwr = false;}
      if(AbDxTGnDQh == true){AbDxTGnDQh = false;}
      if(sTYgtyoHbV == true){sTYgtyoHbV = false;}
      if(ZMczaViYtC == true){ZMczaViYtC = false;}
      if(AwESKqgqPZ == true){AwESKqgqPZ = false;}
      if(rCxKjGSwTT == true){rCxKjGSwTT = false;}
      if(yZcaSmzDWx == true){yZcaSmzDWx = false;}
      if(XPINhwPGVD == true){XPINhwPGVD = false;}
      if(RxqBcWORPU == true){RxqBcWORPU = false;}
      if(ClEZDZTczW == true){ClEZDZTczW = false;}
      if(rdURBcsjbn == true){rdURBcsjbn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXPPNYRABK
{ 
  void XaOwlQQkos()
  { 
      bool CYiPNODkXp = false;
      bool IzqFMyCtyc = false;
      bool QkxGofydZZ = false;
      bool MqZLoLykgk = false;
      bool TeHAasGfWW = false;
      bool NPLuCQacZg = false;
      bool PYLycQYfQA = false;
      bool ARNNIkcxew = false;
      bool YRHCLweeJX = false;
      bool jVKzUuTJWK = false;
      bool TaPWWwCymQ = false;
      bool mdxdIxRIlg = false;
      bool ktVrPdGNrM = false;
      bool RTaUbxCkfP = false;
      bool tgrrjGXgpW = false;
      bool cLXpYZEWGr = false;
      bool pnGZzTCcBK = false;
      bool ugbVlEBdIJ = false;
      bool FZWUjFwjuB = false;
      bool redmZGZSsQ = false;
      string sInGyzwnee;
      string VlqozdZYkr;
      string fpcNFQemTr;
      string waTFgKdKDJ;
      string afQIcnGJwt;
      string CXBNpDfaBh;
      string TJTmiuRlIo;
      string APUbQAZUjQ;
      string KVpZoXYGOd;
      string dCJVpRLdZh;
      string VUBHtmDZxp;
      string cLpjXyStxK;
      string VLWeKxGzky;
      string owtCtoUifC;
      string UyJYASMYyq;
      string yRfOMKxVxw;
      string fDnyAgQnph;
      string djNupWCyeq;
      string jgBtzXPfpi;
      string ryliVQKKXS;
      if(sInGyzwnee == VUBHtmDZxp){CYiPNODkXp = true;}
      else if(VUBHtmDZxp == sInGyzwnee){TaPWWwCymQ = true;}
      if(VlqozdZYkr == cLpjXyStxK){IzqFMyCtyc = true;}
      else if(cLpjXyStxK == VlqozdZYkr){mdxdIxRIlg = true;}
      if(fpcNFQemTr == VLWeKxGzky){QkxGofydZZ = true;}
      else if(VLWeKxGzky == fpcNFQemTr){ktVrPdGNrM = true;}
      if(waTFgKdKDJ == owtCtoUifC){MqZLoLykgk = true;}
      else if(owtCtoUifC == waTFgKdKDJ){RTaUbxCkfP = true;}
      if(afQIcnGJwt == UyJYASMYyq){TeHAasGfWW = true;}
      else if(UyJYASMYyq == afQIcnGJwt){tgrrjGXgpW = true;}
      if(CXBNpDfaBh == yRfOMKxVxw){NPLuCQacZg = true;}
      else if(yRfOMKxVxw == CXBNpDfaBh){cLXpYZEWGr = true;}
      if(TJTmiuRlIo == fDnyAgQnph){PYLycQYfQA = true;}
      else if(fDnyAgQnph == TJTmiuRlIo){pnGZzTCcBK = true;}
      if(APUbQAZUjQ == djNupWCyeq){ARNNIkcxew = true;}
      if(KVpZoXYGOd == jgBtzXPfpi){YRHCLweeJX = true;}
      if(dCJVpRLdZh == ryliVQKKXS){jVKzUuTJWK = true;}
      while(djNupWCyeq == APUbQAZUjQ){ugbVlEBdIJ = true;}
      while(jgBtzXPfpi == jgBtzXPfpi){FZWUjFwjuB = true;}
      while(ryliVQKKXS == ryliVQKKXS){redmZGZSsQ = true;}
      if(CYiPNODkXp == true){CYiPNODkXp = false;}
      if(IzqFMyCtyc == true){IzqFMyCtyc = false;}
      if(QkxGofydZZ == true){QkxGofydZZ = false;}
      if(MqZLoLykgk == true){MqZLoLykgk = false;}
      if(TeHAasGfWW == true){TeHAasGfWW = false;}
      if(NPLuCQacZg == true){NPLuCQacZg = false;}
      if(PYLycQYfQA == true){PYLycQYfQA = false;}
      if(ARNNIkcxew == true){ARNNIkcxew = false;}
      if(YRHCLweeJX == true){YRHCLweeJX = false;}
      if(jVKzUuTJWK == true){jVKzUuTJWK = false;}
      if(TaPWWwCymQ == true){TaPWWwCymQ = false;}
      if(mdxdIxRIlg == true){mdxdIxRIlg = false;}
      if(ktVrPdGNrM == true){ktVrPdGNrM = false;}
      if(RTaUbxCkfP == true){RTaUbxCkfP = false;}
      if(tgrrjGXgpW == true){tgrrjGXgpW = false;}
      if(cLXpYZEWGr == true){cLXpYZEWGr = false;}
      if(pnGZzTCcBK == true){pnGZzTCcBK = false;}
      if(ugbVlEBdIJ == true){ugbVlEBdIJ = false;}
      if(FZWUjFwjuB == true){FZWUjFwjuB = false;}
      if(redmZGZSsQ == true){redmZGZSsQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJKOUSAOZZ
{ 
  void MXuBJjcBsK()
  { 
      bool EUidFUYake = false;
      bool TIDcwdRTch = false;
      bool BgxTWBbypO = false;
      bool MJNioRocfu = false;
      bool oXwhyleyNt = false;
      bool JnHSTXWOHD = false;
      bool sZjVSJtUnd = false;
      bool nnmhrcjOVj = false;
      bool WcjwEXBtOR = false;
      bool tZVcCOnaPn = false;
      bool rKKiFVBZZp = false;
      bool nIsWfPonQt = false;
      bool IzFVjNRKec = false;
      bool oJygrMSApi = false;
      bool WbTYdlgzwm = false;
      bool ZzJVfrEnzq = false;
      bool DqtxAdJMdT = false;
      bool xnxgWffgrx = false;
      bool gSNrDpzcAA = false;
      bool HdByffgWXz = false;
      string fIhdQCEXQH;
      string wuMUpEGyKY;
      string RRKJrgBTYC;
      string oSINdmdYOS;
      string KjujMYhalb;
      string eLYwYOxXki;
      string BjzOSclzqC;
      string ZhirOgWZxS;
      string zahwXctMnO;
      string pGmfQZkgRi;
      string mhjiCwcghq;
      string qWZRiaCDpp;
      string iYLbMStDan;
      string wpIOfRpysa;
      string ANewWSfUwo;
      string XhpaANWHWi;
      string CYFsuBOLlR;
      string jDJOpUtOEs;
      string mYHkPNzhNR;
      string thbKXaIkAV;
      if(fIhdQCEXQH == mhjiCwcghq){EUidFUYake = true;}
      else if(mhjiCwcghq == fIhdQCEXQH){rKKiFVBZZp = true;}
      if(wuMUpEGyKY == qWZRiaCDpp){TIDcwdRTch = true;}
      else if(qWZRiaCDpp == wuMUpEGyKY){nIsWfPonQt = true;}
      if(RRKJrgBTYC == iYLbMStDan){BgxTWBbypO = true;}
      else if(iYLbMStDan == RRKJrgBTYC){IzFVjNRKec = true;}
      if(oSINdmdYOS == wpIOfRpysa){MJNioRocfu = true;}
      else if(wpIOfRpysa == oSINdmdYOS){oJygrMSApi = true;}
      if(KjujMYhalb == ANewWSfUwo){oXwhyleyNt = true;}
      else if(ANewWSfUwo == KjujMYhalb){WbTYdlgzwm = true;}
      if(eLYwYOxXki == XhpaANWHWi){JnHSTXWOHD = true;}
      else if(XhpaANWHWi == eLYwYOxXki){ZzJVfrEnzq = true;}
      if(BjzOSclzqC == CYFsuBOLlR){sZjVSJtUnd = true;}
      else if(CYFsuBOLlR == BjzOSclzqC){DqtxAdJMdT = true;}
      if(ZhirOgWZxS == jDJOpUtOEs){nnmhrcjOVj = true;}
      if(zahwXctMnO == mYHkPNzhNR){WcjwEXBtOR = true;}
      if(pGmfQZkgRi == thbKXaIkAV){tZVcCOnaPn = true;}
      while(jDJOpUtOEs == ZhirOgWZxS){xnxgWffgrx = true;}
      while(mYHkPNzhNR == mYHkPNzhNR){gSNrDpzcAA = true;}
      while(thbKXaIkAV == thbKXaIkAV){HdByffgWXz = true;}
      if(EUidFUYake == true){EUidFUYake = false;}
      if(TIDcwdRTch == true){TIDcwdRTch = false;}
      if(BgxTWBbypO == true){BgxTWBbypO = false;}
      if(MJNioRocfu == true){MJNioRocfu = false;}
      if(oXwhyleyNt == true){oXwhyleyNt = false;}
      if(JnHSTXWOHD == true){JnHSTXWOHD = false;}
      if(sZjVSJtUnd == true){sZjVSJtUnd = false;}
      if(nnmhrcjOVj == true){nnmhrcjOVj = false;}
      if(WcjwEXBtOR == true){WcjwEXBtOR = false;}
      if(tZVcCOnaPn == true){tZVcCOnaPn = false;}
      if(rKKiFVBZZp == true){rKKiFVBZZp = false;}
      if(nIsWfPonQt == true){nIsWfPonQt = false;}
      if(IzFVjNRKec == true){IzFVjNRKec = false;}
      if(oJygrMSApi == true){oJygrMSApi = false;}
      if(WbTYdlgzwm == true){WbTYdlgzwm = false;}
      if(ZzJVfrEnzq == true){ZzJVfrEnzq = false;}
      if(DqtxAdJMdT == true){DqtxAdJMdT = false;}
      if(xnxgWffgrx == true){xnxgWffgrx = false;}
      if(gSNrDpzcAA == true){gSNrDpzcAA = false;}
      if(HdByffgWXz == true){HdByffgWXz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IIPWTYSMRQ
{ 
  void ixYOAcmpET()
  { 
      bool rBVfbqMaMD = false;
      bool buHgherUnz = false;
      bool NYBhMNKGOL = false;
      bool xyEzglHTyY = false;
      bool FUCUnBbgOD = false;
      bool HhHBYTAmTO = false;
      bool fGMBGdpIAw = false;
      bool WXWPsrVftK = false;
      bool kdrKDOpDZN = false;
      bool kTzirzIBNK = false;
      bool LTgRfjKrHf = false;
      bool xTsJdBNByq = false;
      bool mlhlKDXnWt = false;
      bool jUSjyRxZeS = false;
      bool DyutQRZpEq = false;
      bool kHDWWZktHc = false;
      bool LWVNubBJLM = false;
      bool EnWemopmVr = false;
      bool chifIbQuMY = false;
      bool fCRBHgchyn = false;
      string mKIiKbtDna;
      string kscyNArJjj;
      string cbUbxitOeE;
      string wqOlmyJpXi;
      string rJuGwuNmdb;
      string HUxcTLogla;
      string hfXjesepKP;
      string qBlBrTfOeB;
      string UGjDwatkSb;
      string IcEwBLkLaC;
      string PXbOkFiukA;
      string eaBjGauUmD;
      string ztXiGOxpAf;
      string hUmblxdVSp;
      string ryARxgaToZ;
      string QPXXDVAsHV;
      string IruERKnYyJ;
      string xYCxLAtFlZ;
      string mcAZPSwOXP;
      string wjOwhADuAl;
      if(mKIiKbtDna == PXbOkFiukA){rBVfbqMaMD = true;}
      else if(PXbOkFiukA == mKIiKbtDna){LTgRfjKrHf = true;}
      if(kscyNArJjj == eaBjGauUmD){buHgherUnz = true;}
      else if(eaBjGauUmD == kscyNArJjj){xTsJdBNByq = true;}
      if(cbUbxitOeE == ztXiGOxpAf){NYBhMNKGOL = true;}
      else if(ztXiGOxpAf == cbUbxitOeE){mlhlKDXnWt = true;}
      if(wqOlmyJpXi == hUmblxdVSp){xyEzglHTyY = true;}
      else if(hUmblxdVSp == wqOlmyJpXi){jUSjyRxZeS = true;}
      if(rJuGwuNmdb == ryARxgaToZ){FUCUnBbgOD = true;}
      else if(ryARxgaToZ == rJuGwuNmdb){DyutQRZpEq = true;}
      if(HUxcTLogla == QPXXDVAsHV){HhHBYTAmTO = true;}
      else if(QPXXDVAsHV == HUxcTLogla){kHDWWZktHc = true;}
      if(hfXjesepKP == IruERKnYyJ){fGMBGdpIAw = true;}
      else if(IruERKnYyJ == hfXjesepKP){LWVNubBJLM = true;}
      if(qBlBrTfOeB == xYCxLAtFlZ){WXWPsrVftK = true;}
      if(UGjDwatkSb == mcAZPSwOXP){kdrKDOpDZN = true;}
      if(IcEwBLkLaC == wjOwhADuAl){kTzirzIBNK = true;}
      while(xYCxLAtFlZ == qBlBrTfOeB){EnWemopmVr = true;}
      while(mcAZPSwOXP == mcAZPSwOXP){chifIbQuMY = true;}
      while(wjOwhADuAl == wjOwhADuAl){fCRBHgchyn = true;}
      if(rBVfbqMaMD == true){rBVfbqMaMD = false;}
      if(buHgherUnz == true){buHgherUnz = false;}
      if(NYBhMNKGOL == true){NYBhMNKGOL = false;}
      if(xyEzglHTyY == true){xyEzglHTyY = false;}
      if(FUCUnBbgOD == true){FUCUnBbgOD = false;}
      if(HhHBYTAmTO == true){HhHBYTAmTO = false;}
      if(fGMBGdpIAw == true){fGMBGdpIAw = false;}
      if(WXWPsrVftK == true){WXWPsrVftK = false;}
      if(kdrKDOpDZN == true){kdrKDOpDZN = false;}
      if(kTzirzIBNK == true){kTzirzIBNK = false;}
      if(LTgRfjKrHf == true){LTgRfjKrHf = false;}
      if(xTsJdBNByq == true){xTsJdBNByq = false;}
      if(mlhlKDXnWt == true){mlhlKDXnWt = false;}
      if(jUSjyRxZeS == true){jUSjyRxZeS = false;}
      if(DyutQRZpEq == true){DyutQRZpEq = false;}
      if(kHDWWZktHc == true){kHDWWZktHc = false;}
      if(LWVNubBJLM == true){LWVNubBJLM = false;}
      if(EnWemopmVr == true){EnWemopmVr = false;}
      if(chifIbQuMY == true){chifIbQuMY = false;}
      if(fCRBHgchyn == true){fCRBHgchyn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJBIVUJAYO
{ 
  void tThNZsGAwW()
  { 
      bool dEsqBpaslY = false;
      bool nLzYdfiDRT = false;
      bool WUXHlIZAcw = false;
      bool UtqZGNpjXb = false;
      bool NHzahlThDq = false;
      bool EOMdQJgkEs = false;
      bool QaPpEsTZSQ = false;
      bool ozfpFOVwZz = false;
      bool orwlrFhMJx = false;
      bool fEfdLmrJWn = false;
      bool SsOlCFiWXB = false;
      bool mjLEEXddxy = false;
      bool LGQUjjSBeS = false;
      bool WMZkgucJjm = false;
      bool WLnHJwsaZm = false;
      bool JNLXcLcsBR = false;
      bool lgqFeaJZXI = false;
      bool uUtKazRJLn = false;
      bool qraqIIACIU = false;
      bool RiHRAoTibh = false;
      string MyKaBTDwWl;
      string HLHfDKfKqi;
      string YNSRYQzEOX;
      string owerdfFmwE;
      string VDhDIjPkFt;
      string ObTnczesCk;
      string UygyxLfOCX;
      string FrNmNUePIn;
      string ANzTJMbqPe;
      string BLkLjWWiGw;
      string DAigoWNfaH;
      string TPjNjGzMnj;
      string ioyWWsGCDp;
      string ywIMjAeRdm;
      string zwPIKkbWac;
      string XJtWMNBLKw;
      string PKckJXGXdj;
      string bghBjmZpMk;
      string RjbZSoBlzV;
      string ySHhXnSeym;
      if(MyKaBTDwWl == DAigoWNfaH){dEsqBpaslY = true;}
      else if(DAigoWNfaH == MyKaBTDwWl){SsOlCFiWXB = true;}
      if(HLHfDKfKqi == TPjNjGzMnj){nLzYdfiDRT = true;}
      else if(TPjNjGzMnj == HLHfDKfKqi){mjLEEXddxy = true;}
      if(YNSRYQzEOX == ioyWWsGCDp){WUXHlIZAcw = true;}
      else if(ioyWWsGCDp == YNSRYQzEOX){LGQUjjSBeS = true;}
      if(owerdfFmwE == ywIMjAeRdm){UtqZGNpjXb = true;}
      else if(ywIMjAeRdm == owerdfFmwE){WMZkgucJjm = true;}
      if(VDhDIjPkFt == zwPIKkbWac){NHzahlThDq = true;}
      else if(zwPIKkbWac == VDhDIjPkFt){WLnHJwsaZm = true;}
      if(ObTnczesCk == XJtWMNBLKw){EOMdQJgkEs = true;}
      else if(XJtWMNBLKw == ObTnczesCk){JNLXcLcsBR = true;}
      if(UygyxLfOCX == PKckJXGXdj){QaPpEsTZSQ = true;}
      else if(PKckJXGXdj == UygyxLfOCX){lgqFeaJZXI = true;}
      if(FrNmNUePIn == bghBjmZpMk){ozfpFOVwZz = true;}
      if(ANzTJMbqPe == RjbZSoBlzV){orwlrFhMJx = true;}
      if(BLkLjWWiGw == ySHhXnSeym){fEfdLmrJWn = true;}
      while(bghBjmZpMk == FrNmNUePIn){uUtKazRJLn = true;}
      while(RjbZSoBlzV == RjbZSoBlzV){qraqIIACIU = true;}
      while(ySHhXnSeym == ySHhXnSeym){RiHRAoTibh = true;}
      if(dEsqBpaslY == true){dEsqBpaslY = false;}
      if(nLzYdfiDRT == true){nLzYdfiDRT = false;}
      if(WUXHlIZAcw == true){WUXHlIZAcw = false;}
      if(UtqZGNpjXb == true){UtqZGNpjXb = false;}
      if(NHzahlThDq == true){NHzahlThDq = false;}
      if(EOMdQJgkEs == true){EOMdQJgkEs = false;}
      if(QaPpEsTZSQ == true){QaPpEsTZSQ = false;}
      if(ozfpFOVwZz == true){ozfpFOVwZz = false;}
      if(orwlrFhMJx == true){orwlrFhMJx = false;}
      if(fEfdLmrJWn == true){fEfdLmrJWn = false;}
      if(SsOlCFiWXB == true){SsOlCFiWXB = false;}
      if(mjLEEXddxy == true){mjLEEXddxy = false;}
      if(LGQUjjSBeS == true){LGQUjjSBeS = false;}
      if(WMZkgucJjm == true){WMZkgucJjm = false;}
      if(WLnHJwsaZm == true){WLnHJwsaZm = false;}
      if(JNLXcLcsBR == true){JNLXcLcsBR = false;}
      if(lgqFeaJZXI == true){lgqFeaJZXI = false;}
      if(uUtKazRJLn == true){uUtKazRJLn = false;}
      if(qraqIIACIU == true){qraqIIACIU = false;}
      if(RiHRAoTibh == true){RiHRAoTibh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAZVRPDIJT
{ 
  void yYMncAdXIN()
  { 
      bool GEoIMyhsix = false;
      bool RGKggWIkKD = false;
      bool BPwqyqNkWj = false;
      bool KXxXpFCrtp = false;
      bool fQFtUqAVku = false;
      bool CJKVdqIxKV = false;
      bool kwVzlsImqb = false;
      bool TPpUXkJBWG = false;
      bool przbgBNbsz = false;
      bool wFhYFitGIa = false;
      bool iNdJamToys = false;
      bool gGaDfrxtRk = false;
      bool fgtqeOhRPn = false;
      bool pDswXcNpAt = false;
      bool gXczRpedsM = false;
      bool lAnWuCSldM = false;
      bool ECZKDdNdfC = false;
      bool dGsXEHDtZo = false;
      bool jEYCCoOVAV = false;
      bool JbMnoeySwm = false;
      string YHLZaHXxIh;
      string egypXlswYC;
      string RYPjdjqDeh;
      string fiuZxcFoQI;
      string iRcyrJQFha;
      string cufWRAqbup;
      string PUSZBukXst;
      string fDfQSzuRrU;
      string TlVEEkCXIx;
      string lcsZsOzDww;
      string XrLmtYPPDR;
      string EZjaVcyNUQ;
      string sNOwIDKFWE;
      string zrUuwaahJf;
      string UmTqrLsSDP;
      string PlheDKdOeq;
      string OJrzRLEndu;
      string CQDouFsXDx;
      string JqBHnNKorl;
      string xLDSRLtUZf;
      if(YHLZaHXxIh == XrLmtYPPDR){GEoIMyhsix = true;}
      else if(XrLmtYPPDR == YHLZaHXxIh){iNdJamToys = true;}
      if(egypXlswYC == EZjaVcyNUQ){RGKggWIkKD = true;}
      else if(EZjaVcyNUQ == egypXlswYC){gGaDfrxtRk = true;}
      if(RYPjdjqDeh == sNOwIDKFWE){BPwqyqNkWj = true;}
      else if(sNOwIDKFWE == RYPjdjqDeh){fgtqeOhRPn = true;}
      if(fiuZxcFoQI == zrUuwaahJf){KXxXpFCrtp = true;}
      else if(zrUuwaahJf == fiuZxcFoQI){pDswXcNpAt = true;}
      if(iRcyrJQFha == UmTqrLsSDP){fQFtUqAVku = true;}
      else if(UmTqrLsSDP == iRcyrJQFha){gXczRpedsM = true;}
      if(cufWRAqbup == PlheDKdOeq){CJKVdqIxKV = true;}
      else if(PlheDKdOeq == cufWRAqbup){lAnWuCSldM = true;}
      if(PUSZBukXst == OJrzRLEndu){kwVzlsImqb = true;}
      else if(OJrzRLEndu == PUSZBukXst){ECZKDdNdfC = true;}
      if(fDfQSzuRrU == CQDouFsXDx){TPpUXkJBWG = true;}
      if(TlVEEkCXIx == JqBHnNKorl){przbgBNbsz = true;}
      if(lcsZsOzDww == xLDSRLtUZf){wFhYFitGIa = true;}
      while(CQDouFsXDx == fDfQSzuRrU){dGsXEHDtZo = true;}
      while(JqBHnNKorl == JqBHnNKorl){jEYCCoOVAV = true;}
      while(xLDSRLtUZf == xLDSRLtUZf){JbMnoeySwm = true;}
      if(GEoIMyhsix == true){GEoIMyhsix = false;}
      if(RGKggWIkKD == true){RGKggWIkKD = false;}
      if(BPwqyqNkWj == true){BPwqyqNkWj = false;}
      if(KXxXpFCrtp == true){KXxXpFCrtp = false;}
      if(fQFtUqAVku == true){fQFtUqAVku = false;}
      if(CJKVdqIxKV == true){CJKVdqIxKV = false;}
      if(kwVzlsImqb == true){kwVzlsImqb = false;}
      if(TPpUXkJBWG == true){TPpUXkJBWG = false;}
      if(przbgBNbsz == true){przbgBNbsz = false;}
      if(wFhYFitGIa == true){wFhYFitGIa = false;}
      if(iNdJamToys == true){iNdJamToys = false;}
      if(gGaDfrxtRk == true){gGaDfrxtRk = false;}
      if(fgtqeOhRPn == true){fgtqeOhRPn = false;}
      if(pDswXcNpAt == true){pDswXcNpAt = false;}
      if(gXczRpedsM == true){gXczRpedsM = false;}
      if(lAnWuCSldM == true){lAnWuCSldM = false;}
      if(ECZKDdNdfC == true){ECZKDdNdfC = false;}
      if(dGsXEHDtZo == true){dGsXEHDtZo = false;}
      if(jEYCCoOVAV == true){jEYCCoOVAV = false;}
      if(JbMnoeySwm == true){JbMnoeySwm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGDEODRUZQ
{ 
  void sWOIkokUhy()
  { 
      bool AMBArOnKQp = false;
      bool HluOZigEOF = false;
      bool VwCQZQPmCu = false;
      bool BRIsCrBFUo = false;
      bool qseeGgHstG = false;
      bool KauJjDKjaa = false;
      bool yAIUnodBMg = false;
      bool gaiYNbRXKs = false;
      bool IWsujaWyIy = false;
      bool hResqpkJpQ = false;
      bool CGfMYjqVuI = false;
      bool lmYgSbHMjN = false;
      bool RfrOzPwphX = false;
      bool qHgsqBpfWA = false;
      bool iACALtrxZO = false;
      bool hXYczWNRMI = false;
      bool mAnXQeGfpQ = false;
      bool lbpjdQcqCE = false;
      bool XyPSoShDtU = false;
      bool nYSNMhMejg = false;
      string VyCXToQGUR;
      string kVrSdoHVUE;
      string KMjzNixddF;
      string cZdFWyBRCU;
      string YfjMKeVWqJ;
      string KIoprJODKk;
      string qlbOnLrlue;
      string npSAeebXoi;
      string NZmUuUjnNN;
      string jyHRcmDVXy;
      string libMUTonLM;
      string gqNaXRzHST;
      string bDYgtohBXr;
      string bGzqwdyZza;
      string fubAgrjftL;
      string nwCEViKuRe;
      string lnQSkZrWes;
      string TYHqmfaXAC;
      string FCGMEfEuUN;
      string TCIToreJPG;
      if(VyCXToQGUR == libMUTonLM){AMBArOnKQp = true;}
      else if(libMUTonLM == VyCXToQGUR){CGfMYjqVuI = true;}
      if(kVrSdoHVUE == gqNaXRzHST){HluOZigEOF = true;}
      else if(gqNaXRzHST == kVrSdoHVUE){lmYgSbHMjN = true;}
      if(KMjzNixddF == bDYgtohBXr){VwCQZQPmCu = true;}
      else if(bDYgtohBXr == KMjzNixddF){RfrOzPwphX = true;}
      if(cZdFWyBRCU == bGzqwdyZza){BRIsCrBFUo = true;}
      else if(bGzqwdyZza == cZdFWyBRCU){qHgsqBpfWA = true;}
      if(YfjMKeVWqJ == fubAgrjftL){qseeGgHstG = true;}
      else if(fubAgrjftL == YfjMKeVWqJ){iACALtrxZO = true;}
      if(KIoprJODKk == nwCEViKuRe){KauJjDKjaa = true;}
      else if(nwCEViKuRe == KIoprJODKk){hXYczWNRMI = true;}
      if(qlbOnLrlue == lnQSkZrWes){yAIUnodBMg = true;}
      else if(lnQSkZrWes == qlbOnLrlue){mAnXQeGfpQ = true;}
      if(npSAeebXoi == TYHqmfaXAC){gaiYNbRXKs = true;}
      if(NZmUuUjnNN == FCGMEfEuUN){IWsujaWyIy = true;}
      if(jyHRcmDVXy == TCIToreJPG){hResqpkJpQ = true;}
      while(TYHqmfaXAC == npSAeebXoi){lbpjdQcqCE = true;}
      while(FCGMEfEuUN == FCGMEfEuUN){XyPSoShDtU = true;}
      while(TCIToreJPG == TCIToreJPG){nYSNMhMejg = true;}
      if(AMBArOnKQp == true){AMBArOnKQp = false;}
      if(HluOZigEOF == true){HluOZigEOF = false;}
      if(VwCQZQPmCu == true){VwCQZQPmCu = false;}
      if(BRIsCrBFUo == true){BRIsCrBFUo = false;}
      if(qseeGgHstG == true){qseeGgHstG = false;}
      if(KauJjDKjaa == true){KauJjDKjaa = false;}
      if(yAIUnodBMg == true){yAIUnodBMg = false;}
      if(gaiYNbRXKs == true){gaiYNbRXKs = false;}
      if(IWsujaWyIy == true){IWsujaWyIy = false;}
      if(hResqpkJpQ == true){hResqpkJpQ = false;}
      if(CGfMYjqVuI == true){CGfMYjqVuI = false;}
      if(lmYgSbHMjN == true){lmYgSbHMjN = false;}
      if(RfrOzPwphX == true){RfrOzPwphX = false;}
      if(qHgsqBpfWA == true){qHgsqBpfWA = false;}
      if(iACALtrxZO == true){iACALtrxZO = false;}
      if(hXYczWNRMI == true){hXYczWNRMI = false;}
      if(mAnXQeGfpQ == true){mAnXQeGfpQ = false;}
      if(lbpjdQcqCE == true){lbpjdQcqCE = false;}
      if(XyPSoShDtU == true){XyPSoShDtU = false;}
      if(nYSNMhMejg == true){nYSNMhMejg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWUHGZXAHL
{ 
  void EYfSaDiwFZ()
  { 
      bool xGlujJcbyQ = false;
      bool dtSOPsLdKm = false;
      bool dEVCJlWiiX = false;
      bool MsMQKCjcax = false;
      bool oWtkHjtXFn = false;
      bool rNseEsjily = false;
      bool ltsZDkhCDN = false;
      bool IiCNyGKjtY = false;
      bool qyctfzAhLR = false;
      bool RApcKudTgW = false;
      bool CrUqeJKefy = false;
      bool hAoMGmQytD = false;
      bool jzpluHrYDC = false;
      bool bpCWWzdkOV = false;
      bool oUBMiRLdWW = false;
      bool eeZclCCiwX = false;
      bool RkbcWqxRoH = false;
      bool JeiXOPycCd = false;
      bool wNCfXwQZkU = false;
      bool xuoqEDsXpr = false;
      string lZHyISbhQx;
      string VtqmDEQcUz;
      string RVykklcZcu;
      string CSOMwnspwG;
      string nlZmIaGToV;
      string mXzBjQbVMW;
      string oCFVuDfeqP;
      string KZgNKfwKbJ;
      string eJjGIeSMbf;
      string LXdZQkfEqF;
      string ubcZLMplqE;
      string UQtCqfSzMQ;
      string kSCKDlwGwY;
      string zqTWODfJtw;
      string ngVXLudaik;
      string SgraUbYRWY;
      string PjoRFcxXnm;
      string AJEPcExezI;
      string IVXLGRzrBl;
      string dNlVgEqERh;
      if(lZHyISbhQx == ubcZLMplqE){xGlujJcbyQ = true;}
      else if(ubcZLMplqE == lZHyISbhQx){CrUqeJKefy = true;}
      if(VtqmDEQcUz == UQtCqfSzMQ){dtSOPsLdKm = true;}
      else if(UQtCqfSzMQ == VtqmDEQcUz){hAoMGmQytD = true;}
      if(RVykklcZcu == kSCKDlwGwY){dEVCJlWiiX = true;}
      else if(kSCKDlwGwY == RVykklcZcu){jzpluHrYDC = true;}
      if(CSOMwnspwG == zqTWODfJtw){MsMQKCjcax = true;}
      else if(zqTWODfJtw == CSOMwnspwG){bpCWWzdkOV = true;}
      if(nlZmIaGToV == ngVXLudaik){oWtkHjtXFn = true;}
      else if(ngVXLudaik == nlZmIaGToV){oUBMiRLdWW = true;}
      if(mXzBjQbVMW == SgraUbYRWY){rNseEsjily = true;}
      else if(SgraUbYRWY == mXzBjQbVMW){eeZclCCiwX = true;}
      if(oCFVuDfeqP == PjoRFcxXnm){ltsZDkhCDN = true;}
      else if(PjoRFcxXnm == oCFVuDfeqP){RkbcWqxRoH = true;}
      if(KZgNKfwKbJ == AJEPcExezI){IiCNyGKjtY = true;}
      if(eJjGIeSMbf == IVXLGRzrBl){qyctfzAhLR = true;}
      if(LXdZQkfEqF == dNlVgEqERh){RApcKudTgW = true;}
      while(AJEPcExezI == KZgNKfwKbJ){JeiXOPycCd = true;}
      while(IVXLGRzrBl == IVXLGRzrBl){wNCfXwQZkU = true;}
      while(dNlVgEqERh == dNlVgEqERh){xuoqEDsXpr = true;}
      if(xGlujJcbyQ == true){xGlujJcbyQ = false;}
      if(dtSOPsLdKm == true){dtSOPsLdKm = false;}
      if(dEVCJlWiiX == true){dEVCJlWiiX = false;}
      if(MsMQKCjcax == true){MsMQKCjcax = false;}
      if(oWtkHjtXFn == true){oWtkHjtXFn = false;}
      if(rNseEsjily == true){rNseEsjily = false;}
      if(ltsZDkhCDN == true){ltsZDkhCDN = false;}
      if(IiCNyGKjtY == true){IiCNyGKjtY = false;}
      if(qyctfzAhLR == true){qyctfzAhLR = false;}
      if(RApcKudTgW == true){RApcKudTgW = false;}
      if(CrUqeJKefy == true){CrUqeJKefy = false;}
      if(hAoMGmQytD == true){hAoMGmQytD = false;}
      if(jzpluHrYDC == true){jzpluHrYDC = false;}
      if(bpCWWzdkOV == true){bpCWWzdkOV = false;}
      if(oUBMiRLdWW == true){oUBMiRLdWW = false;}
      if(eeZclCCiwX == true){eeZclCCiwX = false;}
      if(RkbcWqxRoH == true){RkbcWqxRoH = false;}
      if(JeiXOPycCd == true){JeiXOPycCd = false;}
      if(wNCfXwQZkU == true){wNCfXwQZkU = false;}
      if(xuoqEDsXpr == true){xuoqEDsXpr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZOPICRFOY
{ 
  void sDVsyWyLgR()
  { 
      bool yTIGOjYdoD = false;
      bool FJhFLEZOpo = false;
      bool zIkqGmtBWo = false;
      bool OShSWYdrsd = false;
      bool GIFqKPoOTX = false;
      bool yoqTwphQzb = false;
      bool pWHAnmaPil = false;
      bool ahVLhqDtfp = false;
      bool xehypYaOVg = false;
      bool qMrRniBFCX = false;
      bool nZfgxQTekF = false;
      bool lmkIeKoJJP = false;
      bool LMsCuNoEXy = false;
      bool pyqHCXyAAY = false;
      bool FudQtDbilc = false;
      bool trumMbfdlj = false;
      bool bPHlPnwcGG = false;
      bool MoIjJPhcHr = false;
      bool kFRuEyCEuZ = false;
      bool qUOPxonqBF = false;
      string OJMzWgaUAS;
      string BkFeoVyajs;
      string hyweBUmTUO;
      string yYtBzPewwx;
      string TXjiujYYXm;
      string xpqqQPNhyC;
      string sHzkUcpEfZ;
      string pCelYKOMjR;
      string uNugQIgDji;
      string CxxsELXyOS;
      string sUsyxuKFRG;
      string BAxgGeMRUL;
      string ulTwWrEkhN;
      string lPxRXZUwjU;
      string xblchBzQmY;
      string zGdDWGAxbE;
      string qYXEUkDfIf;
      string KPgzNTAqOV;
      string rmyINflttQ;
      string ZXUfcYEhIw;
      if(OJMzWgaUAS == sUsyxuKFRG){yTIGOjYdoD = true;}
      else if(sUsyxuKFRG == OJMzWgaUAS){nZfgxQTekF = true;}
      if(BkFeoVyajs == BAxgGeMRUL){FJhFLEZOpo = true;}
      else if(BAxgGeMRUL == BkFeoVyajs){lmkIeKoJJP = true;}
      if(hyweBUmTUO == ulTwWrEkhN){zIkqGmtBWo = true;}
      else if(ulTwWrEkhN == hyweBUmTUO){LMsCuNoEXy = true;}
      if(yYtBzPewwx == lPxRXZUwjU){OShSWYdrsd = true;}
      else if(lPxRXZUwjU == yYtBzPewwx){pyqHCXyAAY = true;}
      if(TXjiujYYXm == xblchBzQmY){GIFqKPoOTX = true;}
      else if(xblchBzQmY == TXjiujYYXm){FudQtDbilc = true;}
      if(xpqqQPNhyC == zGdDWGAxbE){yoqTwphQzb = true;}
      else if(zGdDWGAxbE == xpqqQPNhyC){trumMbfdlj = true;}
      if(sHzkUcpEfZ == qYXEUkDfIf){pWHAnmaPil = true;}
      else if(qYXEUkDfIf == sHzkUcpEfZ){bPHlPnwcGG = true;}
      if(pCelYKOMjR == KPgzNTAqOV){ahVLhqDtfp = true;}
      if(uNugQIgDji == rmyINflttQ){xehypYaOVg = true;}
      if(CxxsELXyOS == ZXUfcYEhIw){qMrRniBFCX = true;}
      while(KPgzNTAqOV == pCelYKOMjR){MoIjJPhcHr = true;}
      while(rmyINflttQ == rmyINflttQ){kFRuEyCEuZ = true;}
      while(ZXUfcYEhIw == ZXUfcYEhIw){qUOPxonqBF = true;}
      if(yTIGOjYdoD == true){yTIGOjYdoD = false;}
      if(FJhFLEZOpo == true){FJhFLEZOpo = false;}
      if(zIkqGmtBWo == true){zIkqGmtBWo = false;}
      if(OShSWYdrsd == true){OShSWYdrsd = false;}
      if(GIFqKPoOTX == true){GIFqKPoOTX = false;}
      if(yoqTwphQzb == true){yoqTwphQzb = false;}
      if(pWHAnmaPil == true){pWHAnmaPil = false;}
      if(ahVLhqDtfp == true){ahVLhqDtfp = false;}
      if(xehypYaOVg == true){xehypYaOVg = false;}
      if(qMrRniBFCX == true){qMrRniBFCX = false;}
      if(nZfgxQTekF == true){nZfgxQTekF = false;}
      if(lmkIeKoJJP == true){lmkIeKoJJP = false;}
      if(LMsCuNoEXy == true){LMsCuNoEXy = false;}
      if(pyqHCXyAAY == true){pyqHCXyAAY = false;}
      if(FudQtDbilc == true){FudQtDbilc = false;}
      if(trumMbfdlj == true){trumMbfdlj = false;}
      if(bPHlPnwcGG == true){bPHlPnwcGG = false;}
      if(MoIjJPhcHr == true){MoIjJPhcHr = false;}
      if(kFRuEyCEuZ == true){kFRuEyCEuZ = false;}
      if(qUOPxonqBF == true){qUOPxonqBF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBLGPWUWTL
{ 
  void gVrAjRfeGx()
  { 
      bool cCEQdYXFNe = false;
      bool MCgXSnatbo = false;
      bool VASinYRMrH = false;
      bool QNTsVBaqpu = false;
      bool GSrJDjHlWu = false;
      bool wVnlAbiUbE = false;
      bool HKMGNzhnCQ = false;
      bool MiEghCHJfE = false;
      bool RepxKuZhrs = false;
      bool RFPlmwGluD = false;
      bool CSjFhNRGDy = false;
      bool TYoWlbTPuS = false;
      bool ZzuIzHTSsl = false;
      bool uVNbCzukOx = false;
      bool cSdtZrQrzL = false;
      bool bppbdCWaGa = false;
      bool szMRCxKNUm = false;
      bool fiByoHUBiG = false;
      bool paShKEflyz = false;
      bool bUdmDdFMqb = false;
      string sMzbwuKVpr;
      string GktjEbujEZ;
      string wWbSjPjSKC;
      string VlTlmcxChB;
      string zABzsxtXgO;
      string widqTVjfrf;
      string KrKmWURHwb;
      string dsBCauUcYl;
      string VMkwGmHbSQ;
      string rQJCpGoOcY;
      string flaFjCgbPY;
      string BHHFKyGOfj;
      string MooeiNizMT;
      string FGzAGikfLD;
      string FfLtPkJDqq;
      string AahrLpxwVW;
      string ThOwTtHHza;
      string NaCcegcuOy;
      string DeHUTdYGnQ;
      string lnJojWQPaV;
      if(sMzbwuKVpr == flaFjCgbPY){cCEQdYXFNe = true;}
      else if(flaFjCgbPY == sMzbwuKVpr){CSjFhNRGDy = true;}
      if(GktjEbujEZ == BHHFKyGOfj){MCgXSnatbo = true;}
      else if(BHHFKyGOfj == GktjEbujEZ){TYoWlbTPuS = true;}
      if(wWbSjPjSKC == MooeiNizMT){VASinYRMrH = true;}
      else if(MooeiNizMT == wWbSjPjSKC){ZzuIzHTSsl = true;}
      if(VlTlmcxChB == FGzAGikfLD){QNTsVBaqpu = true;}
      else if(FGzAGikfLD == VlTlmcxChB){uVNbCzukOx = true;}
      if(zABzsxtXgO == FfLtPkJDqq){GSrJDjHlWu = true;}
      else if(FfLtPkJDqq == zABzsxtXgO){cSdtZrQrzL = true;}
      if(widqTVjfrf == AahrLpxwVW){wVnlAbiUbE = true;}
      else if(AahrLpxwVW == widqTVjfrf){bppbdCWaGa = true;}
      if(KrKmWURHwb == ThOwTtHHza){HKMGNzhnCQ = true;}
      else if(ThOwTtHHza == KrKmWURHwb){szMRCxKNUm = true;}
      if(dsBCauUcYl == NaCcegcuOy){MiEghCHJfE = true;}
      if(VMkwGmHbSQ == DeHUTdYGnQ){RepxKuZhrs = true;}
      if(rQJCpGoOcY == lnJojWQPaV){RFPlmwGluD = true;}
      while(NaCcegcuOy == dsBCauUcYl){fiByoHUBiG = true;}
      while(DeHUTdYGnQ == DeHUTdYGnQ){paShKEflyz = true;}
      while(lnJojWQPaV == lnJojWQPaV){bUdmDdFMqb = true;}
      if(cCEQdYXFNe == true){cCEQdYXFNe = false;}
      if(MCgXSnatbo == true){MCgXSnatbo = false;}
      if(VASinYRMrH == true){VASinYRMrH = false;}
      if(QNTsVBaqpu == true){QNTsVBaqpu = false;}
      if(GSrJDjHlWu == true){GSrJDjHlWu = false;}
      if(wVnlAbiUbE == true){wVnlAbiUbE = false;}
      if(HKMGNzhnCQ == true){HKMGNzhnCQ = false;}
      if(MiEghCHJfE == true){MiEghCHJfE = false;}
      if(RepxKuZhrs == true){RepxKuZhrs = false;}
      if(RFPlmwGluD == true){RFPlmwGluD = false;}
      if(CSjFhNRGDy == true){CSjFhNRGDy = false;}
      if(TYoWlbTPuS == true){TYoWlbTPuS = false;}
      if(ZzuIzHTSsl == true){ZzuIzHTSsl = false;}
      if(uVNbCzukOx == true){uVNbCzukOx = false;}
      if(cSdtZrQrzL == true){cSdtZrQrzL = false;}
      if(bppbdCWaGa == true){bppbdCWaGa = false;}
      if(szMRCxKNUm == true){szMRCxKNUm = false;}
      if(fiByoHUBiG == true){fiByoHUBiG = false;}
      if(paShKEflyz == true){paShKEflyz = false;}
      if(bUdmDdFMqb == true){bUdmDdFMqb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFMYQWMMNM
{ 
  void iUCyknTokA()
  { 
      bool ZZCkGpALNb = false;
      bool CIstewJmOV = false;
      bool MdOljcfFDF = false;
      bool KgZNidetsN = false;
      bool dMZTmbfORL = false;
      bool orYOCwLQAd = false;
      bool KtHIQVieKB = false;
      bool ROtAqADtyH = false;
      bool xRmrQSHKLm = false;
      bool ROtODjERDR = false;
      bool sADQtayXWC = false;
      bool rRRrgrGOqy = false;
      bool NYTXiCTfxH = false;
      bool ulqgOwOWyp = false;
      bool TimItAwBgL = false;
      bool cpZEDTffgq = false;
      bool GSaPGFZkcj = false;
      bool djQBddkKci = false;
      bool FRyldFMlct = false;
      bool QipHiBIXCo = false;
      string McNszQRRaX;
      string EOotebzCZU;
      string BOkwsBQwbz;
      string PddYgJcTfH;
      string DexTDhfQbW;
      string WzOUFyqRAx;
      string zVpaIZjPNU;
      string zfVRRWRRrK;
      string VATFcQPJTh;
      string RKTiIgnVKc;
      string xPDHXpcwDh;
      string gYZobzBkyr;
      string KaweCnMmJj;
      string huGOMFxMgl;
      string nSGkBsjeHJ;
      string fDXSSWTXEi;
      string domSAkSKbV;
      string CoDLEqUKdJ;
      string DhfAEdXnwp;
      string kYIxHyfmkP;
      if(McNszQRRaX == xPDHXpcwDh){ZZCkGpALNb = true;}
      else if(xPDHXpcwDh == McNszQRRaX){sADQtayXWC = true;}
      if(EOotebzCZU == gYZobzBkyr){CIstewJmOV = true;}
      else if(gYZobzBkyr == EOotebzCZU){rRRrgrGOqy = true;}
      if(BOkwsBQwbz == KaweCnMmJj){MdOljcfFDF = true;}
      else if(KaweCnMmJj == BOkwsBQwbz){NYTXiCTfxH = true;}
      if(PddYgJcTfH == huGOMFxMgl){KgZNidetsN = true;}
      else if(huGOMFxMgl == PddYgJcTfH){ulqgOwOWyp = true;}
      if(DexTDhfQbW == nSGkBsjeHJ){dMZTmbfORL = true;}
      else if(nSGkBsjeHJ == DexTDhfQbW){TimItAwBgL = true;}
      if(WzOUFyqRAx == fDXSSWTXEi){orYOCwLQAd = true;}
      else if(fDXSSWTXEi == WzOUFyqRAx){cpZEDTffgq = true;}
      if(zVpaIZjPNU == domSAkSKbV){KtHIQVieKB = true;}
      else if(domSAkSKbV == zVpaIZjPNU){GSaPGFZkcj = true;}
      if(zfVRRWRRrK == CoDLEqUKdJ){ROtAqADtyH = true;}
      if(VATFcQPJTh == DhfAEdXnwp){xRmrQSHKLm = true;}
      if(RKTiIgnVKc == kYIxHyfmkP){ROtODjERDR = true;}
      while(CoDLEqUKdJ == zfVRRWRRrK){djQBddkKci = true;}
      while(DhfAEdXnwp == DhfAEdXnwp){FRyldFMlct = true;}
      while(kYIxHyfmkP == kYIxHyfmkP){QipHiBIXCo = true;}
      if(ZZCkGpALNb == true){ZZCkGpALNb = false;}
      if(CIstewJmOV == true){CIstewJmOV = false;}
      if(MdOljcfFDF == true){MdOljcfFDF = false;}
      if(KgZNidetsN == true){KgZNidetsN = false;}
      if(dMZTmbfORL == true){dMZTmbfORL = false;}
      if(orYOCwLQAd == true){orYOCwLQAd = false;}
      if(KtHIQVieKB == true){KtHIQVieKB = false;}
      if(ROtAqADtyH == true){ROtAqADtyH = false;}
      if(xRmrQSHKLm == true){xRmrQSHKLm = false;}
      if(ROtODjERDR == true){ROtODjERDR = false;}
      if(sADQtayXWC == true){sADQtayXWC = false;}
      if(rRRrgrGOqy == true){rRRrgrGOqy = false;}
      if(NYTXiCTfxH == true){NYTXiCTfxH = false;}
      if(ulqgOwOWyp == true){ulqgOwOWyp = false;}
      if(TimItAwBgL == true){TimItAwBgL = false;}
      if(cpZEDTffgq == true){cpZEDTffgq = false;}
      if(GSaPGFZkcj == true){GSaPGFZkcj = false;}
      if(djQBddkKci == true){djQBddkKci = false;}
      if(FRyldFMlct == true){FRyldFMlct = false;}
      if(QipHiBIXCo == true){QipHiBIXCo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPKAYAUWAH
{ 
  void HPHnEmxwMo()
  { 
      bool nslkkGqBpe = false;
      bool ZArhWKqjyC = false;
      bool WJIKVGyxnx = false;
      bool hSHyAmhpQu = false;
      bool ZmgqbIWmFO = false;
      bool MqmFAdkbOe = false;
      bool IsMswGstgi = false;
      bool cATCcicQhM = false;
      bool iKrZjpfBxW = false;
      bool BFakmfamuV = false;
      bool PcFVkMXkbR = false;
      bool BTsBuxAmIF = false;
      bool aqwJhWYhPx = false;
      bool IoVMxGEWnX = false;
      bool StZfVhMYpo = false;
      bool eneouYfwnO = false;
      bool moVeJLxgEo = false;
      bool rdykmfQPnz = false;
      bool KzrZRUKgQX = false;
      bool ZIiYkcYtWJ = false;
      string kPndfaOGiu;
      string FJxBPxDGZf;
      string PlqXfAZfOO;
      string uVDexodqyJ;
      string TNBOybWYHb;
      string LQLnDzXPxf;
      string BirUAiFREa;
      string SMIQLCjcZD;
      string cAXmDdJOby;
      string QOsRHjUgNO;
      string VFUgIyIubA;
      string OuptCAKERW;
      string YqpFJETpIb;
      string gDOLgXeqeE;
      string VOlaiUXzPG;
      string ZQOqoeOPWD;
      string eRlASLgeMe;
      string VSZNAKEOWo;
      string gTaBCQnWVC;
      string IPUbYDblHX;
      if(kPndfaOGiu == VFUgIyIubA){nslkkGqBpe = true;}
      else if(VFUgIyIubA == kPndfaOGiu){PcFVkMXkbR = true;}
      if(FJxBPxDGZf == OuptCAKERW){ZArhWKqjyC = true;}
      else if(OuptCAKERW == FJxBPxDGZf){BTsBuxAmIF = true;}
      if(PlqXfAZfOO == YqpFJETpIb){WJIKVGyxnx = true;}
      else if(YqpFJETpIb == PlqXfAZfOO){aqwJhWYhPx = true;}
      if(uVDexodqyJ == gDOLgXeqeE){hSHyAmhpQu = true;}
      else if(gDOLgXeqeE == uVDexodqyJ){IoVMxGEWnX = true;}
      if(TNBOybWYHb == VOlaiUXzPG){ZmgqbIWmFO = true;}
      else if(VOlaiUXzPG == TNBOybWYHb){StZfVhMYpo = true;}
      if(LQLnDzXPxf == ZQOqoeOPWD){MqmFAdkbOe = true;}
      else if(ZQOqoeOPWD == LQLnDzXPxf){eneouYfwnO = true;}
      if(BirUAiFREa == eRlASLgeMe){IsMswGstgi = true;}
      else if(eRlASLgeMe == BirUAiFREa){moVeJLxgEo = true;}
      if(SMIQLCjcZD == VSZNAKEOWo){cATCcicQhM = true;}
      if(cAXmDdJOby == gTaBCQnWVC){iKrZjpfBxW = true;}
      if(QOsRHjUgNO == IPUbYDblHX){BFakmfamuV = true;}
      while(VSZNAKEOWo == SMIQLCjcZD){rdykmfQPnz = true;}
      while(gTaBCQnWVC == gTaBCQnWVC){KzrZRUKgQX = true;}
      while(IPUbYDblHX == IPUbYDblHX){ZIiYkcYtWJ = true;}
      if(nslkkGqBpe == true){nslkkGqBpe = false;}
      if(ZArhWKqjyC == true){ZArhWKqjyC = false;}
      if(WJIKVGyxnx == true){WJIKVGyxnx = false;}
      if(hSHyAmhpQu == true){hSHyAmhpQu = false;}
      if(ZmgqbIWmFO == true){ZmgqbIWmFO = false;}
      if(MqmFAdkbOe == true){MqmFAdkbOe = false;}
      if(IsMswGstgi == true){IsMswGstgi = false;}
      if(cATCcicQhM == true){cATCcicQhM = false;}
      if(iKrZjpfBxW == true){iKrZjpfBxW = false;}
      if(BFakmfamuV == true){BFakmfamuV = false;}
      if(PcFVkMXkbR == true){PcFVkMXkbR = false;}
      if(BTsBuxAmIF == true){BTsBuxAmIF = false;}
      if(aqwJhWYhPx == true){aqwJhWYhPx = false;}
      if(IoVMxGEWnX == true){IoVMxGEWnX = false;}
      if(StZfVhMYpo == true){StZfVhMYpo = false;}
      if(eneouYfwnO == true){eneouYfwnO = false;}
      if(moVeJLxgEo == true){moVeJLxgEo = false;}
      if(rdykmfQPnz == true){rdykmfQPnz = false;}
      if(KzrZRUKgQX == true){KzrZRUKgQX = false;}
      if(ZIiYkcYtWJ == true){ZIiYkcYtWJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXBOVLHSLW
{ 
  void xmoZZObfwn()
  { 
      bool MqSaUUWFzg = false;
      bool cWdcYUpwSn = false;
      bool EinSlwhAfo = false;
      bool kRUblunytm = false;
      bool dRxXbxxfSN = false;
      bool LrIqecCAnX = false;
      bool mWYJwLBCqd = false;
      bool fqCeJmkQpo = false;
      bool zBhRdrJdwI = false;
      bool rnJVzHrmaP = false;
      bool utoogTpcgr = false;
      bool qlJzYknHfD = false;
      bool BXFhkrhfeB = false;
      bool txoasEMrkJ = false;
      bool CgwEQGdKxO = false;
      bool SkHXNXnGEn = false;
      bool lKxexswiGT = false;
      bool XuVWBUaBRd = false;
      bool OXhQiJpQMU = false;
      bool PGnxXqiRGW = false;
      string wuRmOJAGSI;
      string RoIeVxUNpW;
      string RsnTxbpXaE;
      string IYzKfSmfVB;
      string PpIAZGpMUq;
      string QQGCiCGypl;
      string TceOArpxzC;
      string KnrnGbkmsq;
      string ldCjnqRwbc;
      string LnpihlKtAg;
      string PsMRgbYRuG;
      string RTEyAoauZJ;
      string ZtUWqVyIGT;
      string QpmLarRjCL;
      string RABUKrjqir;
      string LPTpHVXpaK;
      string cPKaoafsXH;
      string XprOqZrALy;
      string lHZOIBWwEF;
      string UaIqiBoaej;
      if(wuRmOJAGSI == PsMRgbYRuG){MqSaUUWFzg = true;}
      else if(PsMRgbYRuG == wuRmOJAGSI){utoogTpcgr = true;}
      if(RoIeVxUNpW == RTEyAoauZJ){cWdcYUpwSn = true;}
      else if(RTEyAoauZJ == RoIeVxUNpW){qlJzYknHfD = true;}
      if(RsnTxbpXaE == ZtUWqVyIGT){EinSlwhAfo = true;}
      else if(ZtUWqVyIGT == RsnTxbpXaE){BXFhkrhfeB = true;}
      if(IYzKfSmfVB == QpmLarRjCL){kRUblunytm = true;}
      else if(QpmLarRjCL == IYzKfSmfVB){txoasEMrkJ = true;}
      if(PpIAZGpMUq == RABUKrjqir){dRxXbxxfSN = true;}
      else if(RABUKrjqir == PpIAZGpMUq){CgwEQGdKxO = true;}
      if(QQGCiCGypl == LPTpHVXpaK){LrIqecCAnX = true;}
      else if(LPTpHVXpaK == QQGCiCGypl){SkHXNXnGEn = true;}
      if(TceOArpxzC == cPKaoafsXH){mWYJwLBCqd = true;}
      else if(cPKaoafsXH == TceOArpxzC){lKxexswiGT = true;}
      if(KnrnGbkmsq == XprOqZrALy){fqCeJmkQpo = true;}
      if(ldCjnqRwbc == lHZOIBWwEF){zBhRdrJdwI = true;}
      if(LnpihlKtAg == UaIqiBoaej){rnJVzHrmaP = true;}
      while(XprOqZrALy == KnrnGbkmsq){XuVWBUaBRd = true;}
      while(lHZOIBWwEF == lHZOIBWwEF){OXhQiJpQMU = true;}
      while(UaIqiBoaej == UaIqiBoaej){PGnxXqiRGW = true;}
      if(MqSaUUWFzg == true){MqSaUUWFzg = false;}
      if(cWdcYUpwSn == true){cWdcYUpwSn = false;}
      if(EinSlwhAfo == true){EinSlwhAfo = false;}
      if(kRUblunytm == true){kRUblunytm = false;}
      if(dRxXbxxfSN == true){dRxXbxxfSN = false;}
      if(LrIqecCAnX == true){LrIqecCAnX = false;}
      if(mWYJwLBCqd == true){mWYJwLBCqd = false;}
      if(fqCeJmkQpo == true){fqCeJmkQpo = false;}
      if(zBhRdrJdwI == true){zBhRdrJdwI = false;}
      if(rnJVzHrmaP == true){rnJVzHrmaP = false;}
      if(utoogTpcgr == true){utoogTpcgr = false;}
      if(qlJzYknHfD == true){qlJzYknHfD = false;}
      if(BXFhkrhfeB == true){BXFhkrhfeB = false;}
      if(txoasEMrkJ == true){txoasEMrkJ = false;}
      if(CgwEQGdKxO == true){CgwEQGdKxO = false;}
      if(SkHXNXnGEn == true){SkHXNXnGEn = false;}
      if(lKxexswiGT == true){lKxexswiGT = false;}
      if(XuVWBUaBRd == true){XuVWBUaBRd = false;}
      if(OXhQiJpQMU == true){OXhQiJpQMU = false;}
      if(PGnxXqiRGW == true){PGnxXqiRGW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMXAIXRQUN
{ 
  void QfwUaVZVSz()
  { 
      bool feHnoqjukf = false;
      bool kfqJhhFVcj = false;
      bool WALJrkoapi = false;
      bool xLiNNgHIcM = false;
      bool OByqxZnOfN = false;
      bool CjLXtfSyuD = false;
      bool BIEBhZwdwB = false;
      bool axrPUUCTLS = false;
      bool xaucfNzLSh = false;
      bool OINZKGxwJX = false;
      bool dJSemFruDY = false;
      bool cylcFaNaUU = false;
      bool ZkLNlRjSEO = false;
      bool XFKnnmIPoa = false;
      bool VDIsEPWjTj = false;
      bool rVanxsyErV = false;
      bool VYqnBXnxnR = false;
      bool SxltzVbRIW = false;
      bool tzzUVBdWqu = false;
      bool oDXTEwMTrg = false;
      string fSPDkXVMeq;
      string ZmqReYaddk;
      string DqbfPYRkhs;
      string nTFIVEpzce;
      string gDzionofqD;
      string moMtIopimM;
      string FkdkCGgiuZ;
      string haBzEzqsqa;
      string ilseFzHLAg;
      string OGMQZuZNfi;
      string HFjQVMnNoI;
      string xxrMcSqzfD;
      string yViOLaOkYI;
      string ZdMITdBcJs;
      string LtVqjQOzmG;
      string EZgcjkWVEt;
      string xDngiSjjrz;
      string RNplqDAqdt;
      string LOxSDzwjXi;
      string GfYOwIGnHQ;
      if(fSPDkXVMeq == HFjQVMnNoI){feHnoqjukf = true;}
      else if(HFjQVMnNoI == fSPDkXVMeq){dJSemFruDY = true;}
      if(ZmqReYaddk == xxrMcSqzfD){kfqJhhFVcj = true;}
      else if(xxrMcSqzfD == ZmqReYaddk){cylcFaNaUU = true;}
      if(DqbfPYRkhs == yViOLaOkYI){WALJrkoapi = true;}
      else if(yViOLaOkYI == DqbfPYRkhs){ZkLNlRjSEO = true;}
      if(nTFIVEpzce == ZdMITdBcJs){xLiNNgHIcM = true;}
      else if(ZdMITdBcJs == nTFIVEpzce){XFKnnmIPoa = true;}
      if(gDzionofqD == LtVqjQOzmG){OByqxZnOfN = true;}
      else if(LtVqjQOzmG == gDzionofqD){VDIsEPWjTj = true;}
      if(moMtIopimM == EZgcjkWVEt){CjLXtfSyuD = true;}
      else if(EZgcjkWVEt == moMtIopimM){rVanxsyErV = true;}
      if(FkdkCGgiuZ == xDngiSjjrz){BIEBhZwdwB = true;}
      else if(xDngiSjjrz == FkdkCGgiuZ){VYqnBXnxnR = true;}
      if(haBzEzqsqa == RNplqDAqdt){axrPUUCTLS = true;}
      if(ilseFzHLAg == LOxSDzwjXi){xaucfNzLSh = true;}
      if(OGMQZuZNfi == GfYOwIGnHQ){OINZKGxwJX = true;}
      while(RNplqDAqdt == haBzEzqsqa){SxltzVbRIW = true;}
      while(LOxSDzwjXi == LOxSDzwjXi){tzzUVBdWqu = true;}
      while(GfYOwIGnHQ == GfYOwIGnHQ){oDXTEwMTrg = true;}
      if(feHnoqjukf == true){feHnoqjukf = false;}
      if(kfqJhhFVcj == true){kfqJhhFVcj = false;}
      if(WALJrkoapi == true){WALJrkoapi = false;}
      if(xLiNNgHIcM == true){xLiNNgHIcM = false;}
      if(OByqxZnOfN == true){OByqxZnOfN = false;}
      if(CjLXtfSyuD == true){CjLXtfSyuD = false;}
      if(BIEBhZwdwB == true){BIEBhZwdwB = false;}
      if(axrPUUCTLS == true){axrPUUCTLS = false;}
      if(xaucfNzLSh == true){xaucfNzLSh = false;}
      if(OINZKGxwJX == true){OINZKGxwJX = false;}
      if(dJSemFruDY == true){dJSemFruDY = false;}
      if(cylcFaNaUU == true){cylcFaNaUU = false;}
      if(ZkLNlRjSEO == true){ZkLNlRjSEO = false;}
      if(XFKnnmIPoa == true){XFKnnmIPoa = false;}
      if(VDIsEPWjTj == true){VDIsEPWjTj = false;}
      if(rVanxsyErV == true){rVanxsyErV = false;}
      if(VYqnBXnxnR == true){VYqnBXnxnR = false;}
      if(SxltzVbRIW == true){SxltzVbRIW = false;}
      if(tzzUVBdWqu == true){tzzUVBdWqu = false;}
      if(oDXTEwMTrg == true){oDXTEwMTrg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXRQEXTMGC
{ 
  void HalNkrxweX()
  { 
      bool CkIacxMLWE = false;
      bool IlDhaQqEes = false;
      bool OGDSlFBaUz = false;
      bool YEeEAlCHeG = false;
      bool bdNAlrZZwx = false;
      bool nkCSmwhpoW = false;
      bool ulqWeDGzgn = false;
      bool NjYYQkrDgs = false;
      bool fbdXLmCMRE = false;
      bool EMSILolpVh = false;
      bool karHiDMdBB = false;
      bool DeIuqSITLq = false;
      bool BtgcjARQMb = false;
      bool yCgzHFjVnH = false;
      bool aYKPAZDWRr = false;
      bool gSddgqsOXh = false;
      bool lwQZDBxJmk = false;
      bool ileEQbiRcK = false;
      bool xtzUtfXDRQ = false;
      bool MUyGUeHkLy = false;
      string kxdBtnHznb;
      string XtCBkFatdM;
      string KsxqHABbtQ;
      string nWdnoTMTHX;
      string pgpZjQdlzI;
      string QkmQKrzmtt;
      string mfEXnAQOLQ;
      string rHlFVcCXGp;
      string WOblzDjMcx;
      string UZZNkKcSli;
      string AOZhQJyguh;
      string obfDWXDSXj;
      string QElOwRgYUL;
      string zjkXpHnsUp;
      string FCRtHstVpM;
      string GKtBSucKly;
      string bZMihFpINP;
      string iJxheOmqHD;
      string XLhIEopjEt;
      string ddHWNfohLC;
      if(kxdBtnHznb == AOZhQJyguh){CkIacxMLWE = true;}
      else if(AOZhQJyguh == kxdBtnHznb){karHiDMdBB = true;}
      if(XtCBkFatdM == obfDWXDSXj){IlDhaQqEes = true;}
      else if(obfDWXDSXj == XtCBkFatdM){DeIuqSITLq = true;}
      if(KsxqHABbtQ == QElOwRgYUL){OGDSlFBaUz = true;}
      else if(QElOwRgYUL == KsxqHABbtQ){BtgcjARQMb = true;}
      if(nWdnoTMTHX == zjkXpHnsUp){YEeEAlCHeG = true;}
      else if(zjkXpHnsUp == nWdnoTMTHX){yCgzHFjVnH = true;}
      if(pgpZjQdlzI == FCRtHstVpM){bdNAlrZZwx = true;}
      else if(FCRtHstVpM == pgpZjQdlzI){aYKPAZDWRr = true;}
      if(QkmQKrzmtt == GKtBSucKly){nkCSmwhpoW = true;}
      else if(GKtBSucKly == QkmQKrzmtt){gSddgqsOXh = true;}
      if(mfEXnAQOLQ == bZMihFpINP){ulqWeDGzgn = true;}
      else if(bZMihFpINP == mfEXnAQOLQ){lwQZDBxJmk = true;}
      if(rHlFVcCXGp == iJxheOmqHD){NjYYQkrDgs = true;}
      if(WOblzDjMcx == XLhIEopjEt){fbdXLmCMRE = true;}
      if(UZZNkKcSli == ddHWNfohLC){EMSILolpVh = true;}
      while(iJxheOmqHD == rHlFVcCXGp){ileEQbiRcK = true;}
      while(XLhIEopjEt == XLhIEopjEt){xtzUtfXDRQ = true;}
      while(ddHWNfohLC == ddHWNfohLC){MUyGUeHkLy = true;}
      if(CkIacxMLWE == true){CkIacxMLWE = false;}
      if(IlDhaQqEes == true){IlDhaQqEes = false;}
      if(OGDSlFBaUz == true){OGDSlFBaUz = false;}
      if(YEeEAlCHeG == true){YEeEAlCHeG = false;}
      if(bdNAlrZZwx == true){bdNAlrZZwx = false;}
      if(nkCSmwhpoW == true){nkCSmwhpoW = false;}
      if(ulqWeDGzgn == true){ulqWeDGzgn = false;}
      if(NjYYQkrDgs == true){NjYYQkrDgs = false;}
      if(fbdXLmCMRE == true){fbdXLmCMRE = false;}
      if(EMSILolpVh == true){EMSILolpVh = false;}
      if(karHiDMdBB == true){karHiDMdBB = false;}
      if(DeIuqSITLq == true){DeIuqSITLq = false;}
      if(BtgcjARQMb == true){BtgcjARQMb = false;}
      if(yCgzHFjVnH == true){yCgzHFjVnH = false;}
      if(aYKPAZDWRr == true){aYKPAZDWRr = false;}
      if(gSddgqsOXh == true){gSddgqsOXh = false;}
      if(lwQZDBxJmk == true){lwQZDBxJmk = false;}
      if(ileEQbiRcK == true){ileEQbiRcK = false;}
      if(xtzUtfXDRQ == true){xtzUtfXDRQ = false;}
      if(MUyGUeHkLy == true){MUyGUeHkLy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTZUAOOKZE
{ 
  void WxVlfuqWaT()
  { 
      bool RbMychIsZu = false;
      bool XVcnXybckj = false;
      bool qbdGulfGGQ = false;
      bool eCjzNgPEHW = false;
      bool JDDEmrVuip = false;
      bool GdWLGpyFCp = false;
      bool CBmJQVkcaq = false;
      bool iWUOamYZSD = false;
      bool QkWPJAfYsX = false;
      bool iJBQUHQtmR = false;
      bool GrUrHjIIkS = false;
      bool RYlzZReXzQ = false;
      bool oLjCIYUDtS = false;
      bool VelBwXQdHZ = false;
      bool qXnZGJWCqC = false;
      bool cstWbtIRjh = false;
      bool OEORxmlkDC = false;
      bool BAPYYRXKwy = false;
      bool CSMqpcjOZB = false;
      bool PytZKmJVcT = false;
      string MobnSkZDlq;
      string AJJaMirpkd;
      string YypulxrfPb;
      string dNGqbdAtBP;
      string KMKAZxzIFe;
      string ecgNCOygCV;
      string rsmJNlDSyh;
      string iyoUTMmpUo;
      string xiakxAfrnN;
      string eSqeWQYBlm;
      string sgKWwgnLsp;
      string aILMYJSCLM;
      string FKejCPGJyC;
      string nlDhuPYDnP;
      string MUzxlWGdGN;
      string xWoZgiCZTg;
      string adNpBnFdRI;
      string jPNuzkKgxf;
      string IbCkFRxcAL;
      string NyiHohGIwy;
      if(MobnSkZDlq == sgKWwgnLsp){RbMychIsZu = true;}
      else if(sgKWwgnLsp == MobnSkZDlq){GrUrHjIIkS = true;}
      if(AJJaMirpkd == aILMYJSCLM){XVcnXybckj = true;}
      else if(aILMYJSCLM == AJJaMirpkd){RYlzZReXzQ = true;}
      if(YypulxrfPb == FKejCPGJyC){qbdGulfGGQ = true;}
      else if(FKejCPGJyC == YypulxrfPb){oLjCIYUDtS = true;}
      if(dNGqbdAtBP == nlDhuPYDnP){eCjzNgPEHW = true;}
      else if(nlDhuPYDnP == dNGqbdAtBP){VelBwXQdHZ = true;}
      if(KMKAZxzIFe == MUzxlWGdGN){JDDEmrVuip = true;}
      else if(MUzxlWGdGN == KMKAZxzIFe){qXnZGJWCqC = true;}
      if(ecgNCOygCV == xWoZgiCZTg){GdWLGpyFCp = true;}
      else if(xWoZgiCZTg == ecgNCOygCV){cstWbtIRjh = true;}
      if(rsmJNlDSyh == adNpBnFdRI){CBmJQVkcaq = true;}
      else if(adNpBnFdRI == rsmJNlDSyh){OEORxmlkDC = true;}
      if(iyoUTMmpUo == jPNuzkKgxf){iWUOamYZSD = true;}
      if(xiakxAfrnN == IbCkFRxcAL){QkWPJAfYsX = true;}
      if(eSqeWQYBlm == NyiHohGIwy){iJBQUHQtmR = true;}
      while(jPNuzkKgxf == iyoUTMmpUo){BAPYYRXKwy = true;}
      while(IbCkFRxcAL == IbCkFRxcAL){CSMqpcjOZB = true;}
      while(NyiHohGIwy == NyiHohGIwy){PytZKmJVcT = true;}
      if(RbMychIsZu == true){RbMychIsZu = false;}
      if(XVcnXybckj == true){XVcnXybckj = false;}
      if(qbdGulfGGQ == true){qbdGulfGGQ = false;}
      if(eCjzNgPEHW == true){eCjzNgPEHW = false;}
      if(JDDEmrVuip == true){JDDEmrVuip = false;}
      if(GdWLGpyFCp == true){GdWLGpyFCp = false;}
      if(CBmJQVkcaq == true){CBmJQVkcaq = false;}
      if(iWUOamYZSD == true){iWUOamYZSD = false;}
      if(QkWPJAfYsX == true){QkWPJAfYsX = false;}
      if(iJBQUHQtmR == true){iJBQUHQtmR = false;}
      if(GrUrHjIIkS == true){GrUrHjIIkS = false;}
      if(RYlzZReXzQ == true){RYlzZReXzQ = false;}
      if(oLjCIYUDtS == true){oLjCIYUDtS = false;}
      if(VelBwXQdHZ == true){VelBwXQdHZ = false;}
      if(qXnZGJWCqC == true){qXnZGJWCqC = false;}
      if(cstWbtIRjh == true){cstWbtIRjh = false;}
      if(OEORxmlkDC == true){OEORxmlkDC = false;}
      if(BAPYYRXKwy == true){BAPYYRXKwy = false;}
      if(CSMqpcjOZB == true){CSMqpcjOZB = false;}
      if(PytZKmJVcT == true){PytZKmJVcT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMOCDZAXYM
{ 
  void JNwlzdgXYe()
  { 
      bool uzCzoSssuY = false;
      bool LnoptPipZQ = false;
      bool kRlDwsSGAo = false;
      bool YMQZGFlRsg = false;
      bool dpYEGymEGW = false;
      bool lTqCldMyCu = false;
      bool zmsGzyWPjo = false;
      bool cQxsmtrhwy = false;
      bool GOAcDEVOmb = false;
      bool rmPxhpxSEH = false;
      bool aWUQsUWyPq = false;
      bool leBEnjmPCu = false;
      bool cIbHwoBzLw = false;
      bool xYcnWitijh = false;
      bool hXyupNkKJx = false;
      bool CgPJeStMUD = false;
      bool TWlStMCNgF = false;
      bool pEeUMFJgQi = false;
      bool EppNtPISJE = false;
      bool ngNfNKkfBd = false;
      string SNKBUPeHTo;
      string YjaDsKRRMI;
      string XLqABBmQbl;
      string qGQPjPZCsX;
      string uoohqfbuDF;
      string fXGSuGVJzS;
      string bNehyRTLSc;
      string kPYnMiVJJU;
      string ZqNVGTAxTc;
      string tPCZugJGjY;
      string MPbaUQyRFM;
      string jMAdrkAIbd;
      string RVqpiUMysf;
      string YPZjIKOlBo;
      string UiqHrgPXgK;
      string fBeFHpXlqA;
      string DAYZnUlPVh;
      string VNHlJiejxB;
      string FnQhzXjUcS;
      string lbtBlUKRSX;
      if(SNKBUPeHTo == MPbaUQyRFM){uzCzoSssuY = true;}
      else if(MPbaUQyRFM == SNKBUPeHTo){aWUQsUWyPq = true;}
      if(YjaDsKRRMI == jMAdrkAIbd){LnoptPipZQ = true;}
      else if(jMAdrkAIbd == YjaDsKRRMI){leBEnjmPCu = true;}
      if(XLqABBmQbl == RVqpiUMysf){kRlDwsSGAo = true;}
      else if(RVqpiUMysf == XLqABBmQbl){cIbHwoBzLw = true;}
      if(qGQPjPZCsX == YPZjIKOlBo){YMQZGFlRsg = true;}
      else if(YPZjIKOlBo == qGQPjPZCsX){xYcnWitijh = true;}
      if(uoohqfbuDF == UiqHrgPXgK){dpYEGymEGW = true;}
      else if(UiqHrgPXgK == uoohqfbuDF){hXyupNkKJx = true;}
      if(fXGSuGVJzS == fBeFHpXlqA){lTqCldMyCu = true;}
      else if(fBeFHpXlqA == fXGSuGVJzS){CgPJeStMUD = true;}
      if(bNehyRTLSc == DAYZnUlPVh){zmsGzyWPjo = true;}
      else if(DAYZnUlPVh == bNehyRTLSc){TWlStMCNgF = true;}
      if(kPYnMiVJJU == VNHlJiejxB){cQxsmtrhwy = true;}
      if(ZqNVGTAxTc == FnQhzXjUcS){GOAcDEVOmb = true;}
      if(tPCZugJGjY == lbtBlUKRSX){rmPxhpxSEH = true;}
      while(VNHlJiejxB == kPYnMiVJJU){pEeUMFJgQi = true;}
      while(FnQhzXjUcS == FnQhzXjUcS){EppNtPISJE = true;}
      while(lbtBlUKRSX == lbtBlUKRSX){ngNfNKkfBd = true;}
      if(uzCzoSssuY == true){uzCzoSssuY = false;}
      if(LnoptPipZQ == true){LnoptPipZQ = false;}
      if(kRlDwsSGAo == true){kRlDwsSGAo = false;}
      if(YMQZGFlRsg == true){YMQZGFlRsg = false;}
      if(dpYEGymEGW == true){dpYEGymEGW = false;}
      if(lTqCldMyCu == true){lTqCldMyCu = false;}
      if(zmsGzyWPjo == true){zmsGzyWPjo = false;}
      if(cQxsmtrhwy == true){cQxsmtrhwy = false;}
      if(GOAcDEVOmb == true){GOAcDEVOmb = false;}
      if(rmPxhpxSEH == true){rmPxhpxSEH = false;}
      if(aWUQsUWyPq == true){aWUQsUWyPq = false;}
      if(leBEnjmPCu == true){leBEnjmPCu = false;}
      if(cIbHwoBzLw == true){cIbHwoBzLw = false;}
      if(xYcnWitijh == true){xYcnWitijh = false;}
      if(hXyupNkKJx == true){hXyupNkKJx = false;}
      if(CgPJeStMUD == true){CgPJeStMUD = false;}
      if(TWlStMCNgF == true){TWlStMCNgF = false;}
      if(pEeUMFJgQi == true){pEeUMFJgQi = false;}
      if(EppNtPISJE == true){EppNtPISJE = false;}
      if(ngNfNKkfBd == true){ngNfNKkfBd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JLFBBUPDVX
{ 
  void pcQuhifPkE()
  { 
      bool xAumXOQiwn = false;
      bool XFZKemxLjP = false;
      bool aINTrerysz = false;
      bool dPXoGTFmbQ = false;
      bool tHdxrBFhBq = false;
      bool kzxlBnlatr = false;
      bool WSpwKHhkDK = false;
      bool hJiSUTePbq = false;
      bool ZKwBOeSkmR = false;
      bool hdsitbQgmj = false;
      bool SUdpJaPdRh = false;
      bool JVzCSLVogf = false;
      bool oxykcDQAYs = false;
      bool CxcqYFfFqm = false;
      bool OnTEILepQi = false;
      bool FbAHuUWsNG = false;
      bool KPFXeMsIdN = false;
      bool ePxsQAdscR = false;
      bool XaipmaxUuD = false;
      bool hmrkcyiuYw = false;
      string jXgpcNwRVr;
      string mEWrXQPUcH;
      string hXQPNTCBFr;
      string NMNHVXgfhb;
      string kTbwNIyaxE;
      string EXuSwLGRcI;
      string KtMddapOWA;
      string jjlBWOwUCE;
      string VbDAmpQtLJ;
      string QPDYRpHyRm;
      string RiExTUktwh;
      string PkOXlhpLqm;
      string KwDMiUgMif;
      string GxDOmmWGfS;
      string FVycteAfli;
      string zuHdcVfrNz;
      string nXLQaRhAkz;
      string KjeXhnyZRD;
      string TAZAfKpZlQ;
      string GergehKhCc;
      if(jXgpcNwRVr == RiExTUktwh){xAumXOQiwn = true;}
      else if(RiExTUktwh == jXgpcNwRVr){SUdpJaPdRh = true;}
      if(mEWrXQPUcH == PkOXlhpLqm){XFZKemxLjP = true;}
      else if(PkOXlhpLqm == mEWrXQPUcH){JVzCSLVogf = true;}
      if(hXQPNTCBFr == KwDMiUgMif){aINTrerysz = true;}
      else if(KwDMiUgMif == hXQPNTCBFr){oxykcDQAYs = true;}
      if(NMNHVXgfhb == GxDOmmWGfS){dPXoGTFmbQ = true;}
      else if(GxDOmmWGfS == NMNHVXgfhb){CxcqYFfFqm = true;}
      if(kTbwNIyaxE == FVycteAfli){tHdxrBFhBq = true;}
      else if(FVycteAfli == kTbwNIyaxE){OnTEILepQi = true;}
      if(EXuSwLGRcI == zuHdcVfrNz){kzxlBnlatr = true;}
      else if(zuHdcVfrNz == EXuSwLGRcI){FbAHuUWsNG = true;}
      if(KtMddapOWA == nXLQaRhAkz){WSpwKHhkDK = true;}
      else if(nXLQaRhAkz == KtMddapOWA){KPFXeMsIdN = true;}
      if(jjlBWOwUCE == KjeXhnyZRD){hJiSUTePbq = true;}
      if(VbDAmpQtLJ == TAZAfKpZlQ){ZKwBOeSkmR = true;}
      if(QPDYRpHyRm == GergehKhCc){hdsitbQgmj = true;}
      while(KjeXhnyZRD == jjlBWOwUCE){ePxsQAdscR = true;}
      while(TAZAfKpZlQ == TAZAfKpZlQ){XaipmaxUuD = true;}
      while(GergehKhCc == GergehKhCc){hmrkcyiuYw = true;}
      if(xAumXOQiwn == true){xAumXOQiwn = false;}
      if(XFZKemxLjP == true){XFZKemxLjP = false;}
      if(aINTrerysz == true){aINTrerysz = false;}
      if(dPXoGTFmbQ == true){dPXoGTFmbQ = false;}
      if(tHdxrBFhBq == true){tHdxrBFhBq = false;}
      if(kzxlBnlatr == true){kzxlBnlatr = false;}
      if(WSpwKHhkDK == true){WSpwKHhkDK = false;}
      if(hJiSUTePbq == true){hJiSUTePbq = false;}
      if(ZKwBOeSkmR == true){ZKwBOeSkmR = false;}
      if(hdsitbQgmj == true){hdsitbQgmj = false;}
      if(SUdpJaPdRh == true){SUdpJaPdRh = false;}
      if(JVzCSLVogf == true){JVzCSLVogf = false;}
      if(oxykcDQAYs == true){oxykcDQAYs = false;}
      if(CxcqYFfFqm == true){CxcqYFfFqm = false;}
      if(OnTEILepQi == true){OnTEILepQi = false;}
      if(FbAHuUWsNG == true){FbAHuUWsNG = false;}
      if(KPFXeMsIdN == true){KPFXeMsIdN = false;}
      if(ePxsQAdscR == true){ePxsQAdscR = false;}
      if(XaipmaxUuD == true){XaipmaxUuD = false;}
      if(hmrkcyiuYw == true){hmrkcyiuYw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNBPOREWAA
{ 
  void HaDaCgxGBZ()
  { 
      bool TGLrkSGcTw = false;
      bool AxJwQoabja = false;
      bool iABsUFDbAs = false;
      bool CNiJJVOliE = false;
      bool tKhQaWUumk = false;
      bool hJgnLTFRXf = false;
      bool OecasmNAmu = false;
      bool ZorefXRjRx = false;
      bool kIoOKsftxp = false;
      bool PxODpPhHXm = false;
      bool IUIqLsQCHm = false;
      bool BUAZtGoNPz = false;
      bool HTCwecZnoP = false;
      bool pKMdoPAxDR = false;
      bool bclKntwnIi = false;
      bool ZTqXfoSLLh = false;
      bool ScMqwqIVke = false;
      bool FrJyXdgqHk = false;
      bool fleFpWToyz = false;
      bool xnlVyzQtNx = false;
      string sxXXsQWhfu;
      string txcOrjxlrs;
      string kPEFBmMSPA;
      string uBYcLrCfpB;
      string fgBoAIllaZ;
      string mNdGTdrSVF;
      string DERezsXzCA;
      string hQwpMDOPFs;
      string BaroNgWSJg;
      string ziJjyaPVoG;
      string kliZrWRnsQ;
      string PcNcDbMcRS;
      string WEpVAyGLql;
      string nrZyIPrRxp;
      string PhZrRWVfgV;
      string NlEWjfuNZs;
      string PFxHcWDOUn;
      string jufaCneyDc;
      string bZeUXBnCNb;
      string TdqDaJkRPt;
      if(sxXXsQWhfu == kliZrWRnsQ){TGLrkSGcTw = true;}
      else if(kliZrWRnsQ == sxXXsQWhfu){IUIqLsQCHm = true;}
      if(txcOrjxlrs == PcNcDbMcRS){AxJwQoabja = true;}
      else if(PcNcDbMcRS == txcOrjxlrs){BUAZtGoNPz = true;}
      if(kPEFBmMSPA == WEpVAyGLql){iABsUFDbAs = true;}
      else if(WEpVAyGLql == kPEFBmMSPA){HTCwecZnoP = true;}
      if(uBYcLrCfpB == nrZyIPrRxp){CNiJJVOliE = true;}
      else if(nrZyIPrRxp == uBYcLrCfpB){pKMdoPAxDR = true;}
      if(fgBoAIllaZ == PhZrRWVfgV){tKhQaWUumk = true;}
      else if(PhZrRWVfgV == fgBoAIllaZ){bclKntwnIi = true;}
      if(mNdGTdrSVF == NlEWjfuNZs){hJgnLTFRXf = true;}
      else if(NlEWjfuNZs == mNdGTdrSVF){ZTqXfoSLLh = true;}
      if(DERezsXzCA == PFxHcWDOUn){OecasmNAmu = true;}
      else if(PFxHcWDOUn == DERezsXzCA){ScMqwqIVke = true;}
      if(hQwpMDOPFs == jufaCneyDc){ZorefXRjRx = true;}
      if(BaroNgWSJg == bZeUXBnCNb){kIoOKsftxp = true;}
      if(ziJjyaPVoG == TdqDaJkRPt){PxODpPhHXm = true;}
      while(jufaCneyDc == hQwpMDOPFs){FrJyXdgqHk = true;}
      while(bZeUXBnCNb == bZeUXBnCNb){fleFpWToyz = true;}
      while(TdqDaJkRPt == TdqDaJkRPt){xnlVyzQtNx = true;}
      if(TGLrkSGcTw == true){TGLrkSGcTw = false;}
      if(AxJwQoabja == true){AxJwQoabja = false;}
      if(iABsUFDbAs == true){iABsUFDbAs = false;}
      if(CNiJJVOliE == true){CNiJJVOliE = false;}
      if(tKhQaWUumk == true){tKhQaWUumk = false;}
      if(hJgnLTFRXf == true){hJgnLTFRXf = false;}
      if(OecasmNAmu == true){OecasmNAmu = false;}
      if(ZorefXRjRx == true){ZorefXRjRx = false;}
      if(kIoOKsftxp == true){kIoOKsftxp = false;}
      if(PxODpPhHXm == true){PxODpPhHXm = false;}
      if(IUIqLsQCHm == true){IUIqLsQCHm = false;}
      if(BUAZtGoNPz == true){BUAZtGoNPz = false;}
      if(HTCwecZnoP == true){HTCwecZnoP = false;}
      if(pKMdoPAxDR == true){pKMdoPAxDR = false;}
      if(bclKntwnIi == true){bclKntwnIi = false;}
      if(ZTqXfoSLLh == true){ZTqXfoSLLh = false;}
      if(ScMqwqIVke == true){ScMqwqIVke = false;}
      if(FrJyXdgqHk == true){FrJyXdgqHk = false;}
      if(fleFpWToyz == true){fleFpWToyz = false;}
      if(xnlVyzQtNx == true){xnlVyzQtNx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLEUDPVSHC
{ 
  void pRKeDNRDQi()
  { 
      bool WrhPZwZdDE = false;
      bool qXVBDcqjLI = false;
      bool TBlHEagSlj = false;
      bool cFIcamoYiT = false;
      bool DmHSAPewRq = false;
      bool wPzClVGZLy = false;
      bool PHqSakOsZP = false;
      bool mRArFfsTHn = false;
      bool ujAtmNGFpF = false;
      bool gONkDuunrO = false;
      bool AlVCDdOGxF = false;
      bool cmSWCfHxfN = false;
      bool eJCTiXEPnJ = false;
      bool kEasnJNypI = false;
      bool yzIjctwqhX = false;
      bool myIejqjCTe = false;
      bool ZzSmUXLZhs = false;
      bool RJGXOeARqo = false;
      bool bMgPVluwIx = false;
      bool ZLeKhygUPE = false;
      string ncyGttcygn;
      string OlusHioHzy;
      string QiUcqmZYka;
      string xwXDkqkziE;
      string FTTLVbAnwP;
      string xzzObEIUPH;
      string TDNFpSOrIP;
      string ypXusxPIHO;
      string llcVcxwJag;
      string iPibjBFNUD;
      string NHffRHbEUd;
      string nzNBUhaqcs;
      string VFQaghGuKr;
      string qCmEAdFwEV;
      string UrnxriChGC;
      string aNkbgIqEzi;
      string AfscllMJAq;
      string bdmGYcQTiy;
      string fXoIQdRLWr;
      string mAxUUnzKKG;
      if(ncyGttcygn == NHffRHbEUd){WrhPZwZdDE = true;}
      else if(NHffRHbEUd == ncyGttcygn){AlVCDdOGxF = true;}
      if(OlusHioHzy == nzNBUhaqcs){qXVBDcqjLI = true;}
      else if(nzNBUhaqcs == OlusHioHzy){cmSWCfHxfN = true;}
      if(QiUcqmZYka == VFQaghGuKr){TBlHEagSlj = true;}
      else if(VFQaghGuKr == QiUcqmZYka){eJCTiXEPnJ = true;}
      if(xwXDkqkziE == qCmEAdFwEV){cFIcamoYiT = true;}
      else if(qCmEAdFwEV == xwXDkqkziE){kEasnJNypI = true;}
      if(FTTLVbAnwP == UrnxriChGC){DmHSAPewRq = true;}
      else if(UrnxriChGC == FTTLVbAnwP){yzIjctwqhX = true;}
      if(xzzObEIUPH == aNkbgIqEzi){wPzClVGZLy = true;}
      else if(aNkbgIqEzi == xzzObEIUPH){myIejqjCTe = true;}
      if(TDNFpSOrIP == AfscllMJAq){PHqSakOsZP = true;}
      else if(AfscllMJAq == TDNFpSOrIP){ZzSmUXLZhs = true;}
      if(ypXusxPIHO == bdmGYcQTiy){mRArFfsTHn = true;}
      if(llcVcxwJag == fXoIQdRLWr){ujAtmNGFpF = true;}
      if(iPibjBFNUD == mAxUUnzKKG){gONkDuunrO = true;}
      while(bdmGYcQTiy == ypXusxPIHO){RJGXOeARqo = true;}
      while(fXoIQdRLWr == fXoIQdRLWr){bMgPVluwIx = true;}
      while(mAxUUnzKKG == mAxUUnzKKG){ZLeKhygUPE = true;}
      if(WrhPZwZdDE == true){WrhPZwZdDE = false;}
      if(qXVBDcqjLI == true){qXVBDcqjLI = false;}
      if(TBlHEagSlj == true){TBlHEagSlj = false;}
      if(cFIcamoYiT == true){cFIcamoYiT = false;}
      if(DmHSAPewRq == true){DmHSAPewRq = false;}
      if(wPzClVGZLy == true){wPzClVGZLy = false;}
      if(PHqSakOsZP == true){PHqSakOsZP = false;}
      if(mRArFfsTHn == true){mRArFfsTHn = false;}
      if(ujAtmNGFpF == true){ujAtmNGFpF = false;}
      if(gONkDuunrO == true){gONkDuunrO = false;}
      if(AlVCDdOGxF == true){AlVCDdOGxF = false;}
      if(cmSWCfHxfN == true){cmSWCfHxfN = false;}
      if(eJCTiXEPnJ == true){eJCTiXEPnJ = false;}
      if(kEasnJNypI == true){kEasnJNypI = false;}
      if(yzIjctwqhX == true){yzIjctwqhX = false;}
      if(myIejqjCTe == true){myIejqjCTe = false;}
      if(ZzSmUXLZhs == true){ZzSmUXLZhs = false;}
      if(RJGXOeARqo == true){RJGXOeARqo = false;}
      if(bMgPVluwIx == true){bMgPVluwIx = false;}
      if(ZLeKhygUPE == true){ZLeKhygUPE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWGPKFVKIU
{ 
  void PrTJgkUOjl()
  { 
      bool eHuHYHwhjd = false;
      bool sFxUcujYfU = false;
      bool jZPsJyhWUF = false;
      bool RDhisocwPd = false;
      bool NROUzkEbhQ = false;
      bool cHZbjFrCxZ = false;
      bool ZZNdLpWOan = false;
      bool RnIBHRKtsY = false;
      bool sFnDcJcFyn = false;
      bool wazoEmEjIJ = false;
      bool NpBtynyXUR = false;
      bool txIXgTkJBB = false;
      bool MRPmrqoSxT = false;
      bool NZljLCEtFn = false;
      bool LEjgszRaIj = false;
      bool CuiGwwaNCG = false;
      bool zeaBEULYMd = false;
      bool PpDNpHgitr = false;
      bool ZOKMRRqemO = false;
      bool bqrynfdibX = false;
      string WPLiKxWFKS;
      string DmPEgZxVnW;
      string tgRbTQfoEu;
      string wpnKsaudbu;
      string pCqshkxTbX;
      string qtUXMoxiPs;
      string QhBPWNzFKG;
      string eStrgqpXth;
      string SMMfDCVPxD;
      string cLOhdHBaWT;
      string lrIVsXAbqU;
      string zZogaEVULU;
      string riHHcSELNY;
      string pOBawaDple;
      string BtYbEDWgHZ;
      string lfOCbDjBsZ;
      string SnNSejYOkA;
      string BeigSyJeDY;
      string wXDnlKAyyr;
      string pCxLLNfGxT;
      if(WPLiKxWFKS == lrIVsXAbqU){eHuHYHwhjd = true;}
      else if(lrIVsXAbqU == WPLiKxWFKS){NpBtynyXUR = true;}
      if(DmPEgZxVnW == zZogaEVULU){sFxUcujYfU = true;}
      else if(zZogaEVULU == DmPEgZxVnW){txIXgTkJBB = true;}
      if(tgRbTQfoEu == riHHcSELNY){jZPsJyhWUF = true;}
      else if(riHHcSELNY == tgRbTQfoEu){MRPmrqoSxT = true;}
      if(wpnKsaudbu == pOBawaDple){RDhisocwPd = true;}
      else if(pOBawaDple == wpnKsaudbu){NZljLCEtFn = true;}
      if(pCqshkxTbX == BtYbEDWgHZ){NROUzkEbhQ = true;}
      else if(BtYbEDWgHZ == pCqshkxTbX){LEjgszRaIj = true;}
      if(qtUXMoxiPs == lfOCbDjBsZ){cHZbjFrCxZ = true;}
      else if(lfOCbDjBsZ == qtUXMoxiPs){CuiGwwaNCG = true;}
      if(QhBPWNzFKG == SnNSejYOkA){ZZNdLpWOan = true;}
      else if(SnNSejYOkA == QhBPWNzFKG){zeaBEULYMd = true;}
      if(eStrgqpXth == BeigSyJeDY){RnIBHRKtsY = true;}
      if(SMMfDCVPxD == wXDnlKAyyr){sFnDcJcFyn = true;}
      if(cLOhdHBaWT == pCxLLNfGxT){wazoEmEjIJ = true;}
      while(BeigSyJeDY == eStrgqpXth){PpDNpHgitr = true;}
      while(wXDnlKAyyr == wXDnlKAyyr){ZOKMRRqemO = true;}
      while(pCxLLNfGxT == pCxLLNfGxT){bqrynfdibX = true;}
      if(eHuHYHwhjd == true){eHuHYHwhjd = false;}
      if(sFxUcujYfU == true){sFxUcujYfU = false;}
      if(jZPsJyhWUF == true){jZPsJyhWUF = false;}
      if(RDhisocwPd == true){RDhisocwPd = false;}
      if(NROUzkEbhQ == true){NROUzkEbhQ = false;}
      if(cHZbjFrCxZ == true){cHZbjFrCxZ = false;}
      if(ZZNdLpWOan == true){ZZNdLpWOan = false;}
      if(RnIBHRKtsY == true){RnIBHRKtsY = false;}
      if(sFnDcJcFyn == true){sFnDcJcFyn = false;}
      if(wazoEmEjIJ == true){wazoEmEjIJ = false;}
      if(NpBtynyXUR == true){NpBtynyXUR = false;}
      if(txIXgTkJBB == true){txIXgTkJBB = false;}
      if(MRPmrqoSxT == true){MRPmrqoSxT = false;}
      if(NZljLCEtFn == true){NZljLCEtFn = false;}
      if(LEjgszRaIj == true){LEjgszRaIj = false;}
      if(CuiGwwaNCG == true){CuiGwwaNCG = false;}
      if(zeaBEULYMd == true){zeaBEULYMd = false;}
      if(PpDNpHgitr == true){PpDNpHgitr = false;}
      if(ZOKMRRqemO == true){ZOKMRRqemO = false;}
      if(bqrynfdibX == true){bqrynfdibX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFRXOQMREU
{ 
  void ANhgwIYxOM()
  { 
      bool pljfRTnLYJ = false;
      bool oPHqanyXzA = false;
      bool hzIZMrDJcX = false;
      bool BoLLxxijHX = false;
      bool cmZXFjdNEa = false;
      bool sbcGNqdJSY = false;
      bool PdhAIzEwtd = false;
      bool EOPaWtZkUc = false;
      bool OoFBeYLExG = false;
      bool TZQiIzEYPF = false;
      bool fhTaVdMCjT = false;
      bool QrnoJaYfVi = false;
      bool mzzmKeyfSX = false;
      bool oBVOxfVefB = false;
      bool MJUdoakaYg = false;
      bool ZYCfRfifQq = false;
      bool efiMdPWYrd = false;
      bool FsAUWdeUyi = false;
      bool tWGkxQyoxR = false;
      bool xoOoVfaHAY = false;
      string FmcgKToEDq;
      string CykEGfAfEw;
      string EDFkLKoCMk;
      string sjeFLFFylG;
      string HAjIeNEpJz;
      string hPRzSBgqVA;
      string dlrRySSesB;
      string aBsynETwGx;
      string GysNDcRfmJ;
      string YNclbUIRKM;
      string uYxIXfVTKN;
      string hjjXsfseOV;
      string AmqicNYHVT;
      string uBlsCgAkoW;
      string GyUYbncFrw;
      string bdDnLHhOfK;
      string HOxqRfxpUM;
      string eIorPCSRGn;
      string jTPZqRyyht;
      string zlFeOrAcGu;
      if(FmcgKToEDq == uYxIXfVTKN){pljfRTnLYJ = true;}
      else if(uYxIXfVTKN == FmcgKToEDq){fhTaVdMCjT = true;}
      if(CykEGfAfEw == hjjXsfseOV){oPHqanyXzA = true;}
      else if(hjjXsfseOV == CykEGfAfEw){QrnoJaYfVi = true;}
      if(EDFkLKoCMk == AmqicNYHVT){hzIZMrDJcX = true;}
      else if(AmqicNYHVT == EDFkLKoCMk){mzzmKeyfSX = true;}
      if(sjeFLFFylG == uBlsCgAkoW){BoLLxxijHX = true;}
      else if(uBlsCgAkoW == sjeFLFFylG){oBVOxfVefB = true;}
      if(HAjIeNEpJz == GyUYbncFrw){cmZXFjdNEa = true;}
      else if(GyUYbncFrw == HAjIeNEpJz){MJUdoakaYg = true;}
      if(hPRzSBgqVA == bdDnLHhOfK){sbcGNqdJSY = true;}
      else if(bdDnLHhOfK == hPRzSBgqVA){ZYCfRfifQq = true;}
      if(dlrRySSesB == HOxqRfxpUM){PdhAIzEwtd = true;}
      else if(HOxqRfxpUM == dlrRySSesB){efiMdPWYrd = true;}
      if(aBsynETwGx == eIorPCSRGn){EOPaWtZkUc = true;}
      if(GysNDcRfmJ == jTPZqRyyht){OoFBeYLExG = true;}
      if(YNclbUIRKM == zlFeOrAcGu){TZQiIzEYPF = true;}
      while(eIorPCSRGn == aBsynETwGx){FsAUWdeUyi = true;}
      while(jTPZqRyyht == jTPZqRyyht){tWGkxQyoxR = true;}
      while(zlFeOrAcGu == zlFeOrAcGu){xoOoVfaHAY = true;}
      if(pljfRTnLYJ == true){pljfRTnLYJ = false;}
      if(oPHqanyXzA == true){oPHqanyXzA = false;}
      if(hzIZMrDJcX == true){hzIZMrDJcX = false;}
      if(BoLLxxijHX == true){BoLLxxijHX = false;}
      if(cmZXFjdNEa == true){cmZXFjdNEa = false;}
      if(sbcGNqdJSY == true){sbcGNqdJSY = false;}
      if(PdhAIzEwtd == true){PdhAIzEwtd = false;}
      if(EOPaWtZkUc == true){EOPaWtZkUc = false;}
      if(OoFBeYLExG == true){OoFBeYLExG = false;}
      if(TZQiIzEYPF == true){TZQiIzEYPF = false;}
      if(fhTaVdMCjT == true){fhTaVdMCjT = false;}
      if(QrnoJaYfVi == true){QrnoJaYfVi = false;}
      if(mzzmKeyfSX == true){mzzmKeyfSX = false;}
      if(oBVOxfVefB == true){oBVOxfVefB = false;}
      if(MJUdoakaYg == true){MJUdoakaYg = false;}
      if(ZYCfRfifQq == true){ZYCfRfifQq = false;}
      if(efiMdPWYrd == true){efiMdPWYrd = false;}
      if(FsAUWdeUyi == true){FsAUWdeUyi = false;}
      if(tWGkxQyoxR == true){tWGkxQyoxR = false;}
      if(xoOoVfaHAY == true){xoOoVfaHAY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDNURETTIK
{ 
  void BKQjsVHPND()
  { 
      bool PtizINlLmO = false;
      bool aIQlBOuCNM = false;
      bool oGtqpmeumc = false;
      bool ZLOQGROAuD = false;
      bool DeFGRQbWyu = false;
      bool RNKwtJzrIU = false;
      bool iqYJnPszej = false;
      bool zuHKIJBnYZ = false;
      bool KHxqLLASWx = false;
      bool RWqZUMGuRB = false;
      bool WcqNuWGAmj = false;
      bool HKTiJatgyc = false;
      bool PabhScEgow = false;
      bool DFWWChPiuo = false;
      bool EzfloGDHPt = false;
      bool SYxolwAJuS = false;
      bool RYLpgCnwfb = false;
      bool KKkJXPupsL = false;
      bool ZwQucdIhkG = false;
      bool hGmcWfnoFm = false;
      string yXZyFOEHoB;
      string ZaFPlGhelE;
      string KlzqCNgjCO;
      string grgfFLiFdM;
      string cuGyzwppVF;
      string IMWbqLYhwr;
      string gUFaThtYJZ;
      string WbBYbOfBrG;
      string WpNwFUUEnt;
      string mAJkfIpedR;
      string BQfuigLyzb;
      string fWpoVpGIVz;
      string MokPmVSPrT;
      string XAWZFFJRMY;
      string IVFMOPKTPo;
      string BhJdELfQIN;
      string NuFfDfzPjP;
      string fnuxppjXAW;
      string LyADRppsUs;
      string YsJzKNQYJi;
      if(yXZyFOEHoB == BQfuigLyzb){PtizINlLmO = true;}
      else if(BQfuigLyzb == yXZyFOEHoB){WcqNuWGAmj = true;}
      if(ZaFPlGhelE == fWpoVpGIVz){aIQlBOuCNM = true;}
      else if(fWpoVpGIVz == ZaFPlGhelE){HKTiJatgyc = true;}
      if(KlzqCNgjCO == MokPmVSPrT){oGtqpmeumc = true;}
      else if(MokPmVSPrT == KlzqCNgjCO){PabhScEgow = true;}
      if(grgfFLiFdM == XAWZFFJRMY){ZLOQGROAuD = true;}
      else if(XAWZFFJRMY == grgfFLiFdM){DFWWChPiuo = true;}
      if(cuGyzwppVF == IVFMOPKTPo){DeFGRQbWyu = true;}
      else if(IVFMOPKTPo == cuGyzwppVF){EzfloGDHPt = true;}
      if(IMWbqLYhwr == BhJdELfQIN){RNKwtJzrIU = true;}
      else if(BhJdELfQIN == IMWbqLYhwr){SYxolwAJuS = true;}
      if(gUFaThtYJZ == NuFfDfzPjP){iqYJnPszej = true;}
      else if(NuFfDfzPjP == gUFaThtYJZ){RYLpgCnwfb = true;}
      if(WbBYbOfBrG == fnuxppjXAW){zuHKIJBnYZ = true;}
      if(WpNwFUUEnt == LyADRppsUs){KHxqLLASWx = true;}
      if(mAJkfIpedR == YsJzKNQYJi){RWqZUMGuRB = true;}
      while(fnuxppjXAW == WbBYbOfBrG){KKkJXPupsL = true;}
      while(LyADRppsUs == LyADRppsUs){ZwQucdIhkG = true;}
      while(YsJzKNQYJi == YsJzKNQYJi){hGmcWfnoFm = true;}
      if(PtizINlLmO == true){PtizINlLmO = false;}
      if(aIQlBOuCNM == true){aIQlBOuCNM = false;}
      if(oGtqpmeumc == true){oGtqpmeumc = false;}
      if(ZLOQGROAuD == true){ZLOQGROAuD = false;}
      if(DeFGRQbWyu == true){DeFGRQbWyu = false;}
      if(RNKwtJzrIU == true){RNKwtJzrIU = false;}
      if(iqYJnPszej == true){iqYJnPszej = false;}
      if(zuHKIJBnYZ == true){zuHKIJBnYZ = false;}
      if(KHxqLLASWx == true){KHxqLLASWx = false;}
      if(RWqZUMGuRB == true){RWqZUMGuRB = false;}
      if(WcqNuWGAmj == true){WcqNuWGAmj = false;}
      if(HKTiJatgyc == true){HKTiJatgyc = false;}
      if(PabhScEgow == true){PabhScEgow = false;}
      if(DFWWChPiuo == true){DFWWChPiuo = false;}
      if(EzfloGDHPt == true){EzfloGDHPt = false;}
      if(SYxolwAJuS == true){SYxolwAJuS = false;}
      if(RYLpgCnwfb == true){RYLpgCnwfb = false;}
      if(KKkJXPupsL == true){KKkJXPupsL = false;}
      if(ZwQucdIhkG == true){ZwQucdIhkG = false;}
      if(hGmcWfnoFm == true){hGmcWfnoFm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQKBWYCPCW
{ 
  void phwUFOlhZd()
  { 
      bool DqlgWxrfoK = false;
      bool FAseuLxWox = false;
      bool QjznlDIipN = false;
      bool qslUjbTpTp = false;
      bool JltAfClLNG = false;
      bool HqUdfTrxuS = false;
      bool oJobTLOXtS = false;
      bool rGCymdpyIj = false;
      bool RwUiFzXHnQ = false;
      bool jWuBAzxRgT = false;
      bool mORtOBnVqB = false;
      bool csoKBsnGVT = false;
      bool nGidhULByn = false;
      bool gXRnwDeZUE = false;
      bool KBQmmqhjAH = false;
      bool KqwNegemLs = false;
      bool pmXCUFaAOy = false;
      bool OOkQImpwqq = false;
      bool maApcpbEIP = false;
      bool XqNaOXcNSh = false;
      string aZEGzNNdWA;
      string xIlgiKsXly;
      string LqVrqYlPFF;
      string VbMkImAtCI;
      string FYAdTxEjZw;
      string jioIYiDLOa;
      string byYQdVwBYu;
      string KyUdrmqrYt;
      string UBoJVlmEMY;
      string infbfGAiAy;
      string ADKekkNKPl;
      string qLlTGZJPtq;
      string hrnzLVSsxl;
      string lHratRqJXk;
      string YbnagXCMVG;
      string xjoIPIOLSO;
      string STNdzjTKZo;
      string izqISFDNSn;
      string TGWqnCSjLk;
      string CeqISEOKbx;
      if(aZEGzNNdWA == ADKekkNKPl){DqlgWxrfoK = true;}
      else if(ADKekkNKPl == aZEGzNNdWA){mORtOBnVqB = true;}
      if(xIlgiKsXly == qLlTGZJPtq){FAseuLxWox = true;}
      else if(qLlTGZJPtq == xIlgiKsXly){csoKBsnGVT = true;}
      if(LqVrqYlPFF == hrnzLVSsxl){QjznlDIipN = true;}
      else if(hrnzLVSsxl == LqVrqYlPFF){nGidhULByn = true;}
      if(VbMkImAtCI == lHratRqJXk){qslUjbTpTp = true;}
      else if(lHratRqJXk == VbMkImAtCI){gXRnwDeZUE = true;}
      if(FYAdTxEjZw == YbnagXCMVG){JltAfClLNG = true;}
      else if(YbnagXCMVG == FYAdTxEjZw){KBQmmqhjAH = true;}
      if(jioIYiDLOa == xjoIPIOLSO){HqUdfTrxuS = true;}
      else if(xjoIPIOLSO == jioIYiDLOa){KqwNegemLs = true;}
      if(byYQdVwBYu == STNdzjTKZo){oJobTLOXtS = true;}
      else if(STNdzjTKZo == byYQdVwBYu){pmXCUFaAOy = true;}
      if(KyUdrmqrYt == izqISFDNSn){rGCymdpyIj = true;}
      if(UBoJVlmEMY == TGWqnCSjLk){RwUiFzXHnQ = true;}
      if(infbfGAiAy == CeqISEOKbx){jWuBAzxRgT = true;}
      while(izqISFDNSn == KyUdrmqrYt){OOkQImpwqq = true;}
      while(TGWqnCSjLk == TGWqnCSjLk){maApcpbEIP = true;}
      while(CeqISEOKbx == CeqISEOKbx){XqNaOXcNSh = true;}
      if(DqlgWxrfoK == true){DqlgWxrfoK = false;}
      if(FAseuLxWox == true){FAseuLxWox = false;}
      if(QjznlDIipN == true){QjznlDIipN = false;}
      if(qslUjbTpTp == true){qslUjbTpTp = false;}
      if(JltAfClLNG == true){JltAfClLNG = false;}
      if(HqUdfTrxuS == true){HqUdfTrxuS = false;}
      if(oJobTLOXtS == true){oJobTLOXtS = false;}
      if(rGCymdpyIj == true){rGCymdpyIj = false;}
      if(RwUiFzXHnQ == true){RwUiFzXHnQ = false;}
      if(jWuBAzxRgT == true){jWuBAzxRgT = false;}
      if(mORtOBnVqB == true){mORtOBnVqB = false;}
      if(csoKBsnGVT == true){csoKBsnGVT = false;}
      if(nGidhULByn == true){nGidhULByn = false;}
      if(gXRnwDeZUE == true){gXRnwDeZUE = false;}
      if(KBQmmqhjAH == true){KBQmmqhjAH = false;}
      if(KqwNegemLs == true){KqwNegemLs = false;}
      if(pmXCUFaAOy == true){pmXCUFaAOy = false;}
      if(OOkQImpwqq == true){OOkQImpwqq = false;}
      if(maApcpbEIP == true){maApcpbEIP = false;}
      if(XqNaOXcNSh == true){XqNaOXcNSh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDENUOCUAK
{ 
  void GuYmQICRMb()
  { 
      bool hqkYFXWIKG = false;
      bool deSrxKZzuM = false;
      bool uIgEsoWBnA = false;
      bool eAdOCQxAxP = false;
      bool XHDpXVlheF = false;
      bool cZZXPZJfeQ = false;
      bool AVUKbdAEpf = false;
      bool NZBfomEqgX = false;
      bool DoWhXEaGzc = false;
      bool GQVgOCmsNt = false;
      bool VhryrCXthb = false;
      bool USzHMLyllW = false;
      bool CsENZwEUQm = false;
      bool AKcmBVxYpU = false;
      bool ffXWHnRNTD = false;
      bool DAGqqbceYu = false;
      bool yDdubJpLFq = false;
      bool NZwRpVVgFl = false;
      bool epBMizElwZ = false;
      bool rSAuVcCbuy = false;
      string yRlPYLyQBw;
      string tkBJtdPuRS;
      string yIUBaphelQ;
      string shPDBArorV;
      string opHXCwxuKU;
      string rwBUJpwkni;
      string dTdjDMVyHs;
      string kaCucHAxyd;
      string slTRYwgusL;
      string EHBJrUMXUp;
      string aynRiRsFqC;
      string ozlJorALLG;
      string eZFuodYsDI;
      string ucbHDtxChH;
      string DaDqWEUqTA;
      string UAMNKAsrbF;
      string rzChGLWdGu;
      string txdDDEVOYj;
      string IhZDmtQOxC;
      string BFZbPDYVjK;
      if(yRlPYLyQBw == aynRiRsFqC){hqkYFXWIKG = true;}
      else if(aynRiRsFqC == yRlPYLyQBw){VhryrCXthb = true;}
      if(tkBJtdPuRS == ozlJorALLG){deSrxKZzuM = true;}
      else if(ozlJorALLG == tkBJtdPuRS){USzHMLyllW = true;}
      if(yIUBaphelQ == eZFuodYsDI){uIgEsoWBnA = true;}
      else if(eZFuodYsDI == yIUBaphelQ){CsENZwEUQm = true;}
      if(shPDBArorV == ucbHDtxChH){eAdOCQxAxP = true;}
      else if(ucbHDtxChH == shPDBArorV){AKcmBVxYpU = true;}
      if(opHXCwxuKU == DaDqWEUqTA){XHDpXVlheF = true;}
      else if(DaDqWEUqTA == opHXCwxuKU){ffXWHnRNTD = true;}
      if(rwBUJpwkni == UAMNKAsrbF){cZZXPZJfeQ = true;}
      else if(UAMNKAsrbF == rwBUJpwkni){DAGqqbceYu = true;}
      if(dTdjDMVyHs == rzChGLWdGu){AVUKbdAEpf = true;}
      else if(rzChGLWdGu == dTdjDMVyHs){yDdubJpLFq = true;}
      if(kaCucHAxyd == txdDDEVOYj){NZBfomEqgX = true;}
      if(slTRYwgusL == IhZDmtQOxC){DoWhXEaGzc = true;}
      if(EHBJrUMXUp == BFZbPDYVjK){GQVgOCmsNt = true;}
      while(txdDDEVOYj == kaCucHAxyd){NZwRpVVgFl = true;}
      while(IhZDmtQOxC == IhZDmtQOxC){epBMizElwZ = true;}
      while(BFZbPDYVjK == BFZbPDYVjK){rSAuVcCbuy = true;}
      if(hqkYFXWIKG == true){hqkYFXWIKG = false;}
      if(deSrxKZzuM == true){deSrxKZzuM = false;}
      if(uIgEsoWBnA == true){uIgEsoWBnA = false;}
      if(eAdOCQxAxP == true){eAdOCQxAxP = false;}
      if(XHDpXVlheF == true){XHDpXVlheF = false;}
      if(cZZXPZJfeQ == true){cZZXPZJfeQ = false;}
      if(AVUKbdAEpf == true){AVUKbdAEpf = false;}
      if(NZBfomEqgX == true){NZBfomEqgX = false;}
      if(DoWhXEaGzc == true){DoWhXEaGzc = false;}
      if(GQVgOCmsNt == true){GQVgOCmsNt = false;}
      if(VhryrCXthb == true){VhryrCXthb = false;}
      if(USzHMLyllW == true){USzHMLyllW = false;}
      if(CsENZwEUQm == true){CsENZwEUQm = false;}
      if(AKcmBVxYpU == true){AKcmBVxYpU = false;}
      if(ffXWHnRNTD == true){ffXWHnRNTD = false;}
      if(DAGqqbceYu == true){DAGqqbceYu = false;}
      if(yDdubJpLFq == true){yDdubJpLFq = false;}
      if(NZwRpVVgFl == true){NZwRpVVgFl = false;}
      if(epBMizElwZ == true){epBMizElwZ = false;}
      if(rSAuVcCbuy == true){rSAuVcCbuy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHZYDYVIWA
{ 
  void gJSmIZWAaT()
  { 
      bool WqZGKGkrHH = false;
      bool ghqxBuJLGt = false;
      bool IxCkZTCEJb = false;
      bool cxVFUTerBT = false;
      bool KtjgWJfUQL = false;
      bool GYlkLYoofp = false;
      bool EfifdiLkbh = false;
      bool PRKliNNVOP = false;
      bool mgmxVEKktw = false;
      bool eoLKPdLDCm = false;
      bool yusiunOABx = false;
      bool KSaPDXskKZ = false;
      bool YZqfDaFzVF = false;
      bool CKSaRrmECg = false;
      bool pKjxkLOwHr = false;
      bool kascOXDNfU = false;
      bool iOduuAAzxK = false;
      bool jniciNpttr = false;
      bool LJrdUbQoMt = false;
      bool nZYhyafnBj = false;
      string RrOKgZYIpq;
      string rYxVmQMXGl;
      string LAzKdLyuUt;
      string VbyQXmmMkK;
      string gyanINiDsi;
      string TRhoFQrDfU;
      string bdnwVPZfxz;
      string cAlwFNZKCP;
      string cuBkZEsJLH;
      string tjfPiDKdSr;
      string nCGtFTekir;
      string qhBQrfbCVR;
      string WQUoEsTWNC;
      string CurKbZnHeG;
      string YIZTPMhOXC;
      string aHIAVXhQoM;
      string zIWgowoqoR;
      string qUWPrNpAZr;
      string KEyLaumqnD;
      string qXRSGQkreT;
      if(RrOKgZYIpq == nCGtFTekir){WqZGKGkrHH = true;}
      else if(nCGtFTekir == RrOKgZYIpq){yusiunOABx = true;}
      if(rYxVmQMXGl == qhBQrfbCVR){ghqxBuJLGt = true;}
      else if(qhBQrfbCVR == rYxVmQMXGl){KSaPDXskKZ = true;}
      if(LAzKdLyuUt == WQUoEsTWNC){IxCkZTCEJb = true;}
      else if(WQUoEsTWNC == LAzKdLyuUt){YZqfDaFzVF = true;}
      if(VbyQXmmMkK == CurKbZnHeG){cxVFUTerBT = true;}
      else if(CurKbZnHeG == VbyQXmmMkK){CKSaRrmECg = true;}
      if(gyanINiDsi == YIZTPMhOXC){KtjgWJfUQL = true;}
      else if(YIZTPMhOXC == gyanINiDsi){pKjxkLOwHr = true;}
      if(TRhoFQrDfU == aHIAVXhQoM){GYlkLYoofp = true;}
      else if(aHIAVXhQoM == TRhoFQrDfU){kascOXDNfU = true;}
      if(bdnwVPZfxz == zIWgowoqoR){EfifdiLkbh = true;}
      else if(zIWgowoqoR == bdnwVPZfxz){iOduuAAzxK = true;}
      if(cAlwFNZKCP == qUWPrNpAZr){PRKliNNVOP = true;}
      if(cuBkZEsJLH == KEyLaumqnD){mgmxVEKktw = true;}
      if(tjfPiDKdSr == qXRSGQkreT){eoLKPdLDCm = true;}
      while(qUWPrNpAZr == cAlwFNZKCP){jniciNpttr = true;}
      while(KEyLaumqnD == KEyLaumqnD){LJrdUbQoMt = true;}
      while(qXRSGQkreT == qXRSGQkreT){nZYhyafnBj = true;}
      if(WqZGKGkrHH == true){WqZGKGkrHH = false;}
      if(ghqxBuJLGt == true){ghqxBuJLGt = false;}
      if(IxCkZTCEJb == true){IxCkZTCEJb = false;}
      if(cxVFUTerBT == true){cxVFUTerBT = false;}
      if(KtjgWJfUQL == true){KtjgWJfUQL = false;}
      if(GYlkLYoofp == true){GYlkLYoofp = false;}
      if(EfifdiLkbh == true){EfifdiLkbh = false;}
      if(PRKliNNVOP == true){PRKliNNVOP = false;}
      if(mgmxVEKktw == true){mgmxVEKktw = false;}
      if(eoLKPdLDCm == true){eoLKPdLDCm = false;}
      if(yusiunOABx == true){yusiunOABx = false;}
      if(KSaPDXskKZ == true){KSaPDXskKZ = false;}
      if(YZqfDaFzVF == true){YZqfDaFzVF = false;}
      if(CKSaRrmECg == true){CKSaRrmECg = false;}
      if(pKjxkLOwHr == true){pKjxkLOwHr = false;}
      if(kascOXDNfU == true){kascOXDNfU = false;}
      if(iOduuAAzxK == true){iOduuAAzxK = false;}
      if(jniciNpttr == true){jniciNpttr = false;}
      if(LJrdUbQoMt == true){LJrdUbQoMt = false;}
      if(nZYhyafnBj == true){nZYhyafnBj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZAXDCJIFZ
{ 
  void PcWMnWpsWX()
  { 
      bool KjeGzoJcNM = false;
      bool YRFkpkwzzX = false;
      bool iocaXZIWAo = false;
      bool daNYJniJMz = false;
      bool AolgyiZAmj = false;
      bool BLHFfUHEhZ = false;
      bool fmcYiyDfbC = false;
      bool CmlzXsDubo = false;
      bool AIiPmSSIso = false;
      bool fdamTMMNyA = false;
      bool etYkhNYIhl = false;
      bool RMcrYXDMkQ = false;
      bool eullVXMyfK = false;
      bool gpwaKGiygZ = false;
      bool sJaHWTBhOu = false;
      bool JzbhUjHlOK = false;
      bool BacWFbPChS = false;
      bool nEfLWUTeOC = false;
      bool WdjjAhNOFa = false;
      bool yxiVYSgDBu = false;
      string mDCaxJGWQw;
      string kFDCoHxagY;
      string MJNbjsJBoI;
      string gbToNfBxRh;
      string bmzNUVYmjB;
      string sPbKccoZqD;
      string zEhHOJlNoJ;
      string GzIzwZJzHN;
      string UWRnPRzIMj;
      string paGOhWEryL;
      string iKyZtsGcNC;
      string TpScicmtrx;
      string JcBETfstRY;
      string URAudJXrsV;
      string KVuKQzHdeE;
      string jKzABGJsFO;
      string AMLngBoWyY;
      string EuBVmnhqnT;
      string XOPMoJSztX;
      string AeldVyKGcO;
      if(mDCaxJGWQw == iKyZtsGcNC){KjeGzoJcNM = true;}
      else if(iKyZtsGcNC == mDCaxJGWQw){etYkhNYIhl = true;}
      if(kFDCoHxagY == TpScicmtrx){YRFkpkwzzX = true;}
      else if(TpScicmtrx == kFDCoHxagY){RMcrYXDMkQ = true;}
      if(MJNbjsJBoI == JcBETfstRY){iocaXZIWAo = true;}
      else if(JcBETfstRY == MJNbjsJBoI){eullVXMyfK = true;}
      if(gbToNfBxRh == URAudJXrsV){daNYJniJMz = true;}
      else if(URAudJXrsV == gbToNfBxRh){gpwaKGiygZ = true;}
      if(bmzNUVYmjB == KVuKQzHdeE){AolgyiZAmj = true;}
      else if(KVuKQzHdeE == bmzNUVYmjB){sJaHWTBhOu = true;}
      if(sPbKccoZqD == jKzABGJsFO){BLHFfUHEhZ = true;}
      else if(jKzABGJsFO == sPbKccoZqD){JzbhUjHlOK = true;}
      if(zEhHOJlNoJ == AMLngBoWyY){fmcYiyDfbC = true;}
      else if(AMLngBoWyY == zEhHOJlNoJ){BacWFbPChS = true;}
      if(GzIzwZJzHN == EuBVmnhqnT){CmlzXsDubo = true;}
      if(UWRnPRzIMj == XOPMoJSztX){AIiPmSSIso = true;}
      if(paGOhWEryL == AeldVyKGcO){fdamTMMNyA = true;}
      while(EuBVmnhqnT == GzIzwZJzHN){nEfLWUTeOC = true;}
      while(XOPMoJSztX == XOPMoJSztX){WdjjAhNOFa = true;}
      while(AeldVyKGcO == AeldVyKGcO){yxiVYSgDBu = true;}
      if(KjeGzoJcNM == true){KjeGzoJcNM = false;}
      if(YRFkpkwzzX == true){YRFkpkwzzX = false;}
      if(iocaXZIWAo == true){iocaXZIWAo = false;}
      if(daNYJniJMz == true){daNYJniJMz = false;}
      if(AolgyiZAmj == true){AolgyiZAmj = false;}
      if(BLHFfUHEhZ == true){BLHFfUHEhZ = false;}
      if(fmcYiyDfbC == true){fmcYiyDfbC = false;}
      if(CmlzXsDubo == true){CmlzXsDubo = false;}
      if(AIiPmSSIso == true){AIiPmSSIso = false;}
      if(fdamTMMNyA == true){fdamTMMNyA = false;}
      if(etYkhNYIhl == true){etYkhNYIhl = false;}
      if(RMcrYXDMkQ == true){RMcrYXDMkQ = false;}
      if(eullVXMyfK == true){eullVXMyfK = false;}
      if(gpwaKGiygZ == true){gpwaKGiygZ = false;}
      if(sJaHWTBhOu == true){sJaHWTBhOu = false;}
      if(JzbhUjHlOK == true){JzbhUjHlOK = false;}
      if(BacWFbPChS == true){BacWFbPChS = false;}
      if(nEfLWUTeOC == true){nEfLWUTeOC = false;}
      if(WdjjAhNOFa == true){WdjjAhNOFa = false;}
      if(yxiVYSgDBu == true){yxiVYSgDBu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJNFFIBIJK
{ 
  void eGHlyQDAPP()
  { 
      bool ISKCKwUNHD = false;
      bool MSxDDmGpxd = false;
      bool xFqzrGBjAY = false;
      bool oPnBuLYFNQ = false;
      bool hZiiRCChbZ = false;
      bool xFJkhCaKJD = false;
      bool tkMiOwewHr = false;
      bool NAbguXVIho = false;
      bool ESIabiGCSr = false;
      bool jNwJVxMAUV = false;
      bool WFajMxccpK = false;
      bool gScTybblHe = false;
      bool obdPHzESKx = false;
      bool KVnLSyrYNd = false;
      bool GdMHLRkbKt = false;
      bool UaspftbKbM = false;
      bool sKRrAKeQBA = false;
      bool iDXcXKPVDp = false;
      bool ObHQcjbyfX = false;
      bool VhwAkwMUHA = false;
      string cTBqMmNzMo;
      string PDJMDeNgoX;
      string PqmsPwtUBi;
      string nJsrAMGHlu;
      string JMDfmfknIf;
      string ChwUZlgIaQ;
      string rsydAGKQLp;
      string XGtsNDmHFi;
      string LGLUfFMXSO;
      string fygVDQNYeg;
      string VTbSHwmDHW;
      string yZCqFlgcyt;
      string smyxKZYYox;
      string oNbYNqesNj;
      string RJQwPGuoQR;
      string jkajmiVeHh;
      string WONJgjxcdN;
      string GmPNbjWCgE;
      string djIXMDmqld;
      string VzleMDuGOf;
      if(cTBqMmNzMo == VTbSHwmDHW){ISKCKwUNHD = true;}
      else if(VTbSHwmDHW == cTBqMmNzMo){WFajMxccpK = true;}
      if(PDJMDeNgoX == yZCqFlgcyt){MSxDDmGpxd = true;}
      else if(yZCqFlgcyt == PDJMDeNgoX){gScTybblHe = true;}
      if(PqmsPwtUBi == smyxKZYYox){xFqzrGBjAY = true;}
      else if(smyxKZYYox == PqmsPwtUBi){obdPHzESKx = true;}
      if(nJsrAMGHlu == oNbYNqesNj){oPnBuLYFNQ = true;}
      else if(oNbYNqesNj == nJsrAMGHlu){KVnLSyrYNd = true;}
      if(JMDfmfknIf == RJQwPGuoQR){hZiiRCChbZ = true;}
      else if(RJQwPGuoQR == JMDfmfknIf){GdMHLRkbKt = true;}
      if(ChwUZlgIaQ == jkajmiVeHh){xFJkhCaKJD = true;}
      else if(jkajmiVeHh == ChwUZlgIaQ){UaspftbKbM = true;}
      if(rsydAGKQLp == WONJgjxcdN){tkMiOwewHr = true;}
      else if(WONJgjxcdN == rsydAGKQLp){sKRrAKeQBA = true;}
      if(XGtsNDmHFi == GmPNbjWCgE){NAbguXVIho = true;}
      if(LGLUfFMXSO == djIXMDmqld){ESIabiGCSr = true;}
      if(fygVDQNYeg == VzleMDuGOf){jNwJVxMAUV = true;}
      while(GmPNbjWCgE == XGtsNDmHFi){iDXcXKPVDp = true;}
      while(djIXMDmqld == djIXMDmqld){ObHQcjbyfX = true;}
      while(VzleMDuGOf == VzleMDuGOf){VhwAkwMUHA = true;}
      if(ISKCKwUNHD == true){ISKCKwUNHD = false;}
      if(MSxDDmGpxd == true){MSxDDmGpxd = false;}
      if(xFqzrGBjAY == true){xFqzrGBjAY = false;}
      if(oPnBuLYFNQ == true){oPnBuLYFNQ = false;}
      if(hZiiRCChbZ == true){hZiiRCChbZ = false;}
      if(xFJkhCaKJD == true){xFJkhCaKJD = false;}
      if(tkMiOwewHr == true){tkMiOwewHr = false;}
      if(NAbguXVIho == true){NAbguXVIho = false;}
      if(ESIabiGCSr == true){ESIabiGCSr = false;}
      if(jNwJVxMAUV == true){jNwJVxMAUV = false;}
      if(WFajMxccpK == true){WFajMxccpK = false;}
      if(gScTybblHe == true){gScTybblHe = false;}
      if(obdPHzESKx == true){obdPHzESKx = false;}
      if(KVnLSyrYNd == true){KVnLSyrYNd = false;}
      if(GdMHLRkbKt == true){GdMHLRkbKt = false;}
      if(UaspftbKbM == true){UaspftbKbM = false;}
      if(sKRrAKeQBA == true){sKRrAKeQBA = false;}
      if(iDXcXKPVDp == true){iDXcXKPVDp = false;}
      if(ObHQcjbyfX == true){ObHQcjbyfX = false;}
      if(VhwAkwMUHA == true){VhwAkwMUHA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZITPVKDZVU
{ 
  void mVHuiGstTQ()
  { 
      bool xMzxGqlqZJ = false;
      bool DadCbLflal = false;
      bool FVppVMIWCJ = false;
      bool dpPgJbLXgl = false;
      bool MdnDbtBdQP = false;
      bool tcBLcbWIbs = false;
      bool iPnQeNKwrA = false;
      bool zIFnZahmOa = false;
      bool LeGlOAnDEh = false;
      bool EDumDwoWXN = false;
      bool iEkPQkXNlB = false;
      bool sjsAhDJCBe = false;
      bool YGrJuuMRjc = false;
      bool lKOBqGspVd = false;
      bool caRCoUJuFA = false;
      bool mmVsnbLbUU = false;
      bool XFdJPiUrIa = false;
      bool JTfXByopTZ = false;
      bool lRMjoznUMO = false;
      bool tRUAFWxImG = false;
      string YXhmiOquLA;
      string lfsgbpRhSE;
      string GRSPppIVpg;
      string zGiehuBqhT;
      string gfcXPSxRfK;
      string eLHlLGESwr;
      string GUEdAfwOzf;
      string nazyWaouzX;
      string rppfBnywSa;
      string qitoNLayWj;
      string ViRzVDLJPk;
      string RISYAPeYcM;
      string hzuYoFgKjK;
      string AqYPCIXpJy;
      string bnghIhQVox;
      string gBVKCWnsJQ;
      string WBYEjajDVq;
      string qoPdjsSMPH;
      string oLUmdyUNMf;
      string UefrbaPbxh;
      if(YXhmiOquLA == ViRzVDLJPk){xMzxGqlqZJ = true;}
      else if(ViRzVDLJPk == YXhmiOquLA){iEkPQkXNlB = true;}
      if(lfsgbpRhSE == RISYAPeYcM){DadCbLflal = true;}
      else if(RISYAPeYcM == lfsgbpRhSE){sjsAhDJCBe = true;}
      if(GRSPppIVpg == hzuYoFgKjK){FVppVMIWCJ = true;}
      else if(hzuYoFgKjK == GRSPppIVpg){YGrJuuMRjc = true;}
      if(zGiehuBqhT == AqYPCIXpJy){dpPgJbLXgl = true;}
      else if(AqYPCIXpJy == zGiehuBqhT){lKOBqGspVd = true;}
      if(gfcXPSxRfK == bnghIhQVox){MdnDbtBdQP = true;}
      else if(bnghIhQVox == gfcXPSxRfK){caRCoUJuFA = true;}
      if(eLHlLGESwr == gBVKCWnsJQ){tcBLcbWIbs = true;}
      else if(gBVKCWnsJQ == eLHlLGESwr){mmVsnbLbUU = true;}
      if(GUEdAfwOzf == WBYEjajDVq){iPnQeNKwrA = true;}
      else if(WBYEjajDVq == GUEdAfwOzf){XFdJPiUrIa = true;}
      if(nazyWaouzX == qoPdjsSMPH){zIFnZahmOa = true;}
      if(rppfBnywSa == oLUmdyUNMf){LeGlOAnDEh = true;}
      if(qitoNLayWj == UefrbaPbxh){EDumDwoWXN = true;}
      while(qoPdjsSMPH == nazyWaouzX){JTfXByopTZ = true;}
      while(oLUmdyUNMf == oLUmdyUNMf){lRMjoznUMO = true;}
      while(UefrbaPbxh == UefrbaPbxh){tRUAFWxImG = true;}
      if(xMzxGqlqZJ == true){xMzxGqlqZJ = false;}
      if(DadCbLflal == true){DadCbLflal = false;}
      if(FVppVMIWCJ == true){FVppVMIWCJ = false;}
      if(dpPgJbLXgl == true){dpPgJbLXgl = false;}
      if(MdnDbtBdQP == true){MdnDbtBdQP = false;}
      if(tcBLcbWIbs == true){tcBLcbWIbs = false;}
      if(iPnQeNKwrA == true){iPnQeNKwrA = false;}
      if(zIFnZahmOa == true){zIFnZahmOa = false;}
      if(LeGlOAnDEh == true){LeGlOAnDEh = false;}
      if(EDumDwoWXN == true){EDumDwoWXN = false;}
      if(iEkPQkXNlB == true){iEkPQkXNlB = false;}
      if(sjsAhDJCBe == true){sjsAhDJCBe = false;}
      if(YGrJuuMRjc == true){YGrJuuMRjc = false;}
      if(lKOBqGspVd == true){lKOBqGspVd = false;}
      if(caRCoUJuFA == true){caRCoUJuFA = false;}
      if(mmVsnbLbUU == true){mmVsnbLbUU = false;}
      if(XFdJPiUrIa == true){XFdJPiUrIa = false;}
      if(JTfXByopTZ == true){JTfXByopTZ = false;}
      if(lRMjoznUMO == true){lRMjoznUMO = false;}
      if(tRUAFWxImG == true){tRUAFWxImG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJXRLMJIPL
{ 
  void NbCPOIHiIM()
  { 
      bool PLfWksNcWF = false;
      bool RCJTEmaCwc = false;
      bool VKRBsJmuMC = false;
      bool MwQrwNTKOn = false;
      bool XHebjLMVgL = false;
      bool HkzKsFsdda = false;
      bool GRQTsUlRXp = false;
      bool SQmHFNfoQg = false;
      bool xROAubwFyq = false;
      bool UpgngFpKiO = false;
      bool ZuyprqxqFf = false;
      bool ZEMwdoCQYR = false;
      bool YfSfVcizZz = false;
      bool WUFCHCSXID = false;
      bool dEASRPcjJr = false;
      bool DZkRpsbRUO = false;
      bool HxQFJEyKoa = false;
      bool VdHVmTeAOF = false;
      bool AzohwwinLO = false;
      bool ZBDsugnuJM = false;
      string xKHmIVxBPF;
      string ttMfNEdoBu;
      string lDljmwPDbK;
      string JpUKxXVxTt;
      string RPqkAAOdKy;
      string CrcLPsXWAL;
      string GsZFwDZBho;
      string ifUGcVLAjl;
      string hksdIQMIuD;
      string AyxHnXplow;
      string aMwVOVWVis;
      string gXmOcVAwxf;
      string qRFdokiNSF;
      string eZLmKVnWOl;
      string sqZBWbKieS;
      string WtnJFJGRgd;
      string mJDdNHMzDH;
      string gdgKlzrEHM;
      string ZzhAhkkBhB;
      string OWpkyimumP;
      if(xKHmIVxBPF == aMwVOVWVis){PLfWksNcWF = true;}
      else if(aMwVOVWVis == xKHmIVxBPF){ZuyprqxqFf = true;}
      if(ttMfNEdoBu == gXmOcVAwxf){RCJTEmaCwc = true;}
      else if(gXmOcVAwxf == ttMfNEdoBu){ZEMwdoCQYR = true;}
      if(lDljmwPDbK == qRFdokiNSF){VKRBsJmuMC = true;}
      else if(qRFdokiNSF == lDljmwPDbK){YfSfVcizZz = true;}
      if(JpUKxXVxTt == eZLmKVnWOl){MwQrwNTKOn = true;}
      else if(eZLmKVnWOl == JpUKxXVxTt){WUFCHCSXID = true;}
      if(RPqkAAOdKy == sqZBWbKieS){XHebjLMVgL = true;}
      else if(sqZBWbKieS == RPqkAAOdKy){dEASRPcjJr = true;}
      if(CrcLPsXWAL == WtnJFJGRgd){HkzKsFsdda = true;}
      else if(WtnJFJGRgd == CrcLPsXWAL){DZkRpsbRUO = true;}
      if(GsZFwDZBho == mJDdNHMzDH){GRQTsUlRXp = true;}
      else if(mJDdNHMzDH == GsZFwDZBho){HxQFJEyKoa = true;}
      if(ifUGcVLAjl == gdgKlzrEHM){SQmHFNfoQg = true;}
      if(hksdIQMIuD == ZzhAhkkBhB){xROAubwFyq = true;}
      if(AyxHnXplow == OWpkyimumP){UpgngFpKiO = true;}
      while(gdgKlzrEHM == ifUGcVLAjl){VdHVmTeAOF = true;}
      while(ZzhAhkkBhB == ZzhAhkkBhB){AzohwwinLO = true;}
      while(OWpkyimumP == OWpkyimumP){ZBDsugnuJM = true;}
      if(PLfWksNcWF == true){PLfWksNcWF = false;}
      if(RCJTEmaCwc == true){RCJTEmaCwc = false;}
      if(VKRBsJmuMC == true){VKRBsJmuMC = false;}
      if(MwQrwNTKOn == true){MwQrwNTKOn = false;}
      if(XHebjLMVgL == true){XHebjLMVgL = false;}
      if(HkzKsFsdda == true){HkzKsFsdda = false;}
      if(GRQTsUlRXp == true){GRQTsUlRXp = false;}
      if(SQmHFNfoQg == true){SQmHFNfoQg = false;}
      if(xROAubwFyq == true){xROAubwFyq = false;}
      if(UpgngFpKiO == true){UpgngFpKiO = false;}
      if(ZuyprqxqFf == true){ZuyprqxqFf = false;}
      if(ZEMwdoCQYR == true){ZEMwdoCQYR = false;}
      if(YfSfVcizZz == true){YfSfVcizZz = false;}
      if(WUFCHCSXID == true){WUFCHCSXID = false;}
      if(dEASRPcjJr == true){dEASRPcjJr = false;}
      if(DZkRpsbRUO == true){DZkRpsbRUO = false;}
      if(HxQFJEyKoa == true){HxQFJEyKoa = false;}
      if(VdHVmTeAOF == true){VdHVmTeAOF = false;}
      if(AzohwwinLO == true){AzohwwinLO = false;}
      if(ZBDsugnuJM == true){ZBDsugnuJM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIDOCDPZJQ
{ 
  void sKCwlpRxEN()
  { 
      bool UyKfuxpbLm = false;
      bool YmFcYRLdaR = false;
      bool KACrZVdwNy = false;
      bool kJHKGqVdzw = false;
      bool TnMmYoOknN = false;
      bool mzaGRTwRGZ = false;
      bool SsONCPetWg = false;
      bool wgedxVnOTk = false;
      bool HrIzKkhArm = false;
      bool uDXZcZZzkJ = false;
      bool JTOGRGUxJu = false;
      bool fgyVRakOCQ = false;
      bool gdCjlrJFAW = false;
      bool wndJancChE = false;
      bool QkqwGOFBHC = false;
      bool oKxTbfQeTY = false;
      bool xPwlzrCnud = false;
      bool yhfxAwlFcX = false;
      bool mHxygkpKgu = false;
      bool WyhIHAoFxO = false;
      string FGtDFizoca;
      string GddUqrCuEx;
      string XKoodMlrtt;
      string WgTNMToxXj;
      string KdcercQqyk;
      string jlYqcuREYs;
      string wHthDYKQIX;
      string DFXTmsgJxA;
      string uutJJjHbjR;
      string BjYemCjtbT;
      string SAiaheOFEj;
      string NHHXxBMkXS;
      string QhfpVSgrfj;
      string ImhchuLTbd;
      string VCWzDtcAhk;
      string pzVICjTrEO;
      string yWYUaaZdpB;
      string psJsxOLfma;
      string pfKusJQYax;
      string bTOMfzdCYb;
      if(FGtDFizoca == SAiaheOFEj){UyKfuxpbLm = true;}
      else if(SAiaheOFEj == FGtDFizoca){JTOGRGUxJu = true;}
      if(GddUqrCuEx == NHHXxBMkXS){YmFcYRLdaR = true;}
      else if(NHHXxBMkXS == GddUqrCuEx){fgyVRakOCQ = true;}
      if(XKoodMlrtt == QhfpVSgrfj){KACrZVdwNy = true;}
      else if(QhfpVSgrfj == XKoodMlrtt){gdCjlrJFAW = true;}
      if(WgTNMToxXj == ImhchuLTbd){kJHKGqVdzw = true;}
      else if(ImhchuLTbd == WgTNMToxXj){wndJancChE = true;}
      if(KdcercQqyk == VCWzDtcAhk){TnMmYoOknN = true;}
      else if(VCWzDtcAhk == KdcercQqyk){QkqwGOFBHC = true;}
      if(jlYqcuREYs == pzVICjTrEO){mzaGRTwRGZ = true;}
      else if(pzVICjTrEO == jlYqcuREYs){oKxTbfQeTY = true;}
      if(wHthDYKQIX == yWYUaaZdpB){SsONCPetWg = true;}
      else if(yWYUaaZdpB == wHthDYKQIX){xPwlzrCnud = true;}
      if(DFXTmsgJxA == psJsxOLfma){wgedxVnOTk = true;}
      if(uutJJjHbjR == pfKusJQYax){HrIzKkhArm = true;}
      if(BjYemCjtbT == bTOMfzdCYb){uDXZcZZzkJ = true;}
      while(psJsxOLfma == DFXTmsgJxA){yhfxAwlFcX = true;}
      while(pfKusJQYax == pfKusJQYax){mHxygkpKgu = true;}
      while(bTOMfzdCYb == bTOMfzdCYb){WyhIHAoFxO = true;}
      if(UyKfuxpbLm == true){UyKfuxpbLm = false;}
      if(YmFcYRLdaR == true){YmFcYRLdaR = false;}
      if(KACrZVdwNy == true){KACrZVdwNy = false;}
      if(kJHKGqVdzw == true){kJHKGqVdzw = false;}
      if(TnMmYoOknN == true){TnMmYoOknN = false;}
      if(mzaGRTwRGZ == true){mzaGRTwRGZ = false;}
      if(SsONCPetWg == true){SsONCPetWg = false;}
      if(wgedxVnOTk == true){wgedxVnOTk = false;}
      if(HrIzKkhArm == true){HrIzKkhArm = false;}
      if(uDXZcZZzkJ == true){uDXZcZZzkJ = false;}
      if(JTOGRGUxJu == true){JTOGRGUxJu = false;}
      if(fgyVRakOCQ == true){fgyVRakOCQ = false;}
      if(gdCjlrJFAW == true){gdCjlrJFAW = false;}
      if(wndJancChE == true){wndJancChE = false;}
      if(QkqwGOFBHC == true){QkqwGOFBHC = false;}
      if(oKxTbfQeTY == true){oKxTbfQeTY = false;}
      if(xPwlzrCnud == true){xPwlzrCnud = false;}
      if(yhfxAwlFcX == true){yhfxAwlFcX = false;}
      if(mHxygkpKgu == true){mHxygkpKgu = false;}
      if(WyhIHAoFxO == true){WyhIHAoFxO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLPMLCFYGO
{ 
  void psRFeprbqB()
  { 
      bool XbuBRztyju = false;
      bool OnrBtJwCcO = false;
      bool EyZHBgqoiE = false;
      bool mlHEoZFVco = false;
      bool wyZCruhHdM = false;
      bool saTMKZCmzj = false;
      bool IEOfIcgnLU = false;
      bool DZZmRGXWPG = false;
      bool yiKVKLRtsP = false;
      bool WRWrgqittO = false;
      bool OsuJISBguE = false;
      bool BfXrlYsrUw = false;
      bool LluuxlDhGa = false;
      bool WdbArFnBMr = false;
      bool KjzoOqtdGH = false;
      bool ypYyDbyzLW = false;
      bool OTaTgXEWzf = false;
      bool kreckalFgG = false;
      bool qYaycfEcxP = false;
      bool GnopcqJfHp = false;
      string QSycUFOHGC;
      string bxXJXTlLlf;
      string jXyAJfcMEP;
      string JtgZJzhwUx;
      string WtgakKjtgj;
      string MVENrrUySn;
      string cCDprgQxzX;
      string lppnIoqWOz;
      string uhfTDnpShQ;
      string djdfUUqphD;
      string tmuIyWePEC;
      string BxiTsuVimD;
      string qxOitCLKTm;
      string yAoKEHmWUg;
      string JZOfPgAKmY;
      string yIDdMxXLOw;
      string KTwREAIXOk;
      string HzNFtQiiSN;
      string BBXtopwKyG;
      string iaIYWodxaO;
      if(QSycUFOHGC == tmuIyWePEC){XbuBRztyju = true;}
      else if(tmuIyWePEC == QSycUFOHGC){OsuJISBguE = true;}
      if(bxXJXTlLlf == BxiTsuVimD){OnrBtJwCcO = true;}
      else if(BxiTsuVimD == bxXJXTlLlf){BfXrlYsrUw = true;}
      if(jXyAJfcMEP == qxOitCLKTm){EyZHBgqoiE = true;}
      else if(qxOitCLKTm == jXyAJfcMEP){LluuxlDhGa = true;}
      if(JtgZJzhwUx == yAoKEHmWUg){mlHEoZFVco = true;}
      else if(yAoKEHmWUg == JtgZJzhwUx){WdbArFnBMr = true;}
      if(WtgakKjtgj == JZOfPgAKmY){wyZCruhHdM = true;}
      else if(JZOfPgAKmY == WtgakKjtgj){KjzoOqtdGH = true;}
      if(MVENrrUySn == yIDdMxXLOw){saTMKZCmzj = true;}
      else if(yIDdMxXLOw == MVENrrUySn){ypYyDbyzLW = true;}
      if(cCDprgQxzX == KTwREAIXOk){IEOfIcgnLU = true;}
      else if(KTwREAIXOk == cCDprgQxzX){OTaTgXEWzf = true;}
      if(lppnIoqWOz == HzNFtQiiSN){DZZmRGXWPG = true;}
      if(uhfTDnpShQ == BBXtopwKyG){yiKVKLRtsP = true;}
      if(djdfUUqphD == iaIYWodxaO){WRWrgqittO = true;}
      while(HzNFtQiiSN == lppnIoqWOz){kreckalFgG = true;}
      while(BBXtopwKyG == BBXtopwKyG){qYaycfEcxP = true;}
      while(iaIYWodxaO == iaIYWodxaO){GnopcqJfHp = true;}
      if(XbuBRztyju == true){XbuBRztyju = false;}
      if(OnrBtJwCcO == true){OnrBtJwCcO = false;}
      if(EyZHBgqoiE == true){EyZHBgqoiE = false;}
      if(mlHEoZFVco == true){mlHEoZFVco = false;}
      if(wyZCruhHdM == true){wyZCruhHdM = false;}
      if(saTMKZCmzj == true){saTMKZCmzj = false;}
      if(IEOfIcgnLU == true){IEOfIcgnLU = false;}
      if(DZZmRGXWPG == true){DZZmRGXWPG = false;}
      if(yiKVKLRtsP == true){yiKVKLRtsP = false;}
      if(WRWrgqittO == true){WRWrgqittO = false;}
      if(OsuJISBguE == true){OsuJISBguE = false;}
      if(BfXrlYsrUw == true){BfXrlYsrUw = false;}
      if(LluuxlDhGa == true){LluuxlDhGa = false;}
      if(WdbArFnBMr == true){WdbArFnBMr = false;}
      if(KjzoOqtdGH == true){KjzoOqtdGH = false;}
      if(ypYyDbyzLW == true){ypYyDbyzLW = false;}
      if(OTaTgXEWzf == true){OTaTgXEWzf = false;}
      if(kreckalFgG == true){kreckalFgG = false;}
      if(qYaycfEcxP == true){qYaycfEcxP = false;}
      if(GnopcqJfHp == true){GnopcqJfHp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSTLVSOYOT
{ 
  void yPWjVwtemY()
  { 
      bool zjZBIaLfQU = false;
      bool nxtELlrXID = false;
      bool UdDRMcksoU = false;
      bool CdJmeOOJXT = false;
      bool aaYBDuaiEP = false;
      bool ItCWYVfIne = false;
      bool pSqwSKmHZw = false;
      bool WiAnbtFBNR = false;
      bool CBoYMIalOJ = false;
      bool iGUrcIibis = false;
      bool HSJHsYtNue = false;
      bool PetVcocSiK = false;
      bool iAsPNQNHLT = false;
      bool KcSUJjqgfm = false;
      bool OMqisDLyPn = false;
      bool fPsYJHYstb = false;
      bool KlCbTmMZLs = false;
      bool xuluwVIJWJ = false;
      bool FOrWntisKC = false;
      bool KxmEcbKPPG = false;
      string mhNeCwuENo;
      string IOteNlidPi;
      string xKxgyMbwYQ;
      string sBzbDAdubX;
      string sjoHnwCDsc;
      string mVkmLbkfgo;
      string TyfxwHPRbM;
      string HmCroMVosB;
      string KYDucWPLPa;
      string PxOlDuEqLg;
      string gjbfUzTsxy;
      string GwmeeuujTY;
      string qDCAxJYQnt;
      string HecMUZwWac;
      string DWORUSKjGH;
      string zUXmochaiK;
      string aCEDpbTaJF;
      string yYJqVTokfd;
      string zoKgtmGpWr;
      string rVnPCARKas;
      if(mhNeCwuENo == gjbfUzTsxy){zjZBIaLfQU = true;}
      else if(gjbfUzTsxy == mhNeCwuENo){HSJHsYtNue = true;}
      if(IOteNlidPi == GwmeeuujTY){nxtELlrXID = true;}
      else if(GwmeeuujTY == IOteNlidPi){PetVcocSiK = true;}
      if(xKxgyMbwYQ == qDCAxJYQnt){UdDRMcksoU = true;}
      else if(qDCAxJYQnt == xKxgyMbwYQ){iAsPNQNHLT = true;}
      if(sBzbDAdubX == HecMUZwWac){CdJmeOOJXT = true;}
      else if(HecMUZwWac == sBzbDAdubX){KcSUJjqgfm = true;}
      if(sjoHnwCDsc == DWORUSKjGH){aaYBDuaiEP = true;}
      else if(DWORUSKjGH == sjoHnwCDsc){OMqisDLyPn = true;}
      if(mVkmLbkfgo == zUXmochaiK){ItCWYVfIne = true;}
      else if(zUXmochaiK == mVkmLbkfgo){fPsYJHYstb = true;}
      if(TyfxwHPRbM == aCEDpbTaJF){pSqwSKmHZw = true;}
      else if(aCEDpbTaJF == TyfxwHPRbM){KlCbTmMZLs = true;}
      if(HmCroMVosB == yYJqVTokfd){WiAnbtFBNR = true;}
      if(KYDucWPLPa == zoKgtmGpWr){CBoYMIalOJ = true;}
      if(PxOlDuEqLg == rVnPCARKas){iGUrcIibis = true;}
      while(yYJqVTokfd == HmCroMVosB){xuluwVIJWJ = true;}
      while(zoKgtmGpWr == zoKgtmGpWr){FOrWntisKC = true;}
      while(rVnPCARKas == rVnPCARKas){KxmEcbKPPG = true;}
      if(zjZBIaLfQU == true){zjZBIaLfQU = false;}
      if(nxtELlrXID == true){nxtELlrXID = false;}
      if(UdDRMcksoU == true){UdDRMcksoU = false;}
      if(CdJmeOOJXT == true){CdJmeOOJXT = false;}
      if(aaYBDuaiEP == true){aaYBDuaiEP = false;}
      if(ItCWYVfIne == true){ItCWYVfIne = false;}
      if(pSqwSKmHZw == true){pSqwSKmHZw = false;}
      if(WiAnbtFBNR == true){WiAnbtFBNR = false;}
      if(CBoYMIalOJ == true){CBoYMIalOJ = false;}
      if(iGUrcIibis == true){iGUrcIibis = false;}
      if(HSJHsYtNue == true){HSJHsYtNue = false;}
      if(PetVcocSiK == true){PetVcocSiK = false;}
      if(iAsPNQNHLT == true){iAsPNQNHLT = false;}
      if(KcSUJjqgfm == true){KcSUJjqgfm = false;}
      if(OMqisDLyPn == true){OMqisDLyPn = false;}
      if(fPsYJHYstb == true){fPsYJHYstb = false;}
      if(KlCbTmMZLs == true){KlCbTmMZLs = false;}
      if(xuluwVIJWJ == true){xuluwVIJWJ = false;}
      if(FOrWntisKC == true){FOrWntisKC = false;}
      if(KxmEcbKPPG == true){KxmEcbKPPG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWVPNKCRRX
{ 
  void MVldgtgRYm()
  { 
      bool poYbLliTMh = false;
      bool NZVfgLYfoa = false;
      bool IwVHEdudml = false;
      bool MjQDdUzajt = false;
      bool dCXfOjpJlt = false;
      bool fEwyhsSRWg = false;
      bool pEgZVcIRCL = false;
      bool MxuuwGXpsU = false;
      bool mlrsGInSUj = false;
      bool BhDDDZVxJk = false;
      bool bXGZghIBBb = false;
      bool VcYCsELnTN = false;
      bool opxRKetrqV = false;
      bool kZfHrOeSLY = false;
      bool zmQsOYJAJz = false;
      bool OgdwwlaoPC = false;
      bool mPJfquwQKe = false;
      bool YscuNBYEDk = false;
      bool UsiqHDujLG = false;
      bool npDIkickCT = false;
      string aIhchKTjTg;
      string WWAgPCbmHN;
      string GdVUBDlJtX;
      string DaLFgfPiLq;
      string JauFkZMebL;
      string LzodLwlMae;
      string XJowcuLuzj;
      string lrbQEehQib;
      string pGhiLElgsj;
      string sCIfSzlybo;
      string OQeqZTXYZg;
      string OVdynRbGkX;
      string JdBPqiiuxE;
      string sjnsNYbpJq;
      string gMHMVWYKqB;
      string XfNDfjOPAp;
      string kbbVnegjkP;
      string pkxsqxVotT;
      string JYDufNVkNc;
      string KLpSGEjkYq;
      if(aIhchKTjTg == OQeqZTXYZg){poYbLliTMh = true;}
      else if(OQeqZTXYZg == aIhchKTjTg){bXGZghIBBb = true;}
      if(WWAgPCbmHN == OVdynRbGkX){NZVfgLYfoa = true;}
      else if(OVdynRbGkX == WWAgPCbmHN){VcYCsELnTN = true;}
      if(GdVUBDlJtX == JdBPqiiuxE){IwVHEdudml = true;}
      else if(JdBPqiiuxE == GdVUBDlJtX){opxRKetrqV = true;}
      if(DaLFgfPiLq == sjnsNYbpJq){MjQDdUzajt = true;}
      else if(sjnsNYbpJq == DaLFgfPiLq){kZfHrOeSLY = true;}
      if(JauFkZMebL == gMHMVWYKqB){dCXfOjpJlt = true;}
      else if(gMHMVWYKqB == JauFkZMebL){zmQsOYJAJz = true;}
      if(LzodLwlMae == XfNDfjOPAp){fEwyhsSRWg = true;}
      else if(XfNDfjOPAp == LzodLwlMae){OgdwwlaoPC = true;}
      if(XJowcuLuzj == kbbVnegjkP){pEgZVcIRCL = true;}
      else if(kbbVnegjkP == XJowcuLuzj){mPJfquwQKe = true;}
      if(lrbQEehQib == pkxsqxVotT){MxuuwGXpsU = true;}
      if(pGhiLElgsj == JYDufNVkNc){mlrsGInSUj = true;}
      if(sCIfSzlybo == KLpSGEjkYq){BhDDDZVxJk = true;}
      while(pkxsqxVotT == lrbQEehQib){YscuNBYEDk = true;}
      while(JYDufNVkNc == JYDufNVkNc){UsiqHDujLG = true;}
      while(KLpSGEjkYq == KLpSGEjkYq){npDIkickCT = true;}
      if(poYbLliTMh == true){poYbLliTMh = false;}
      if(NZVfgLYfoa == true){NZVfgLYfoa = false;}
      if(IwVHEdudml == true){IwVHEdudml = false;}
      if(MjQDdUzajt == true){MjQDdUzajt = false;}
      if(dCXfOjpJlt == true){dCXfOjpJlt = false;}
      if(fEwyhsSRWg == true){fEwyhsSRWg = false;}
      if(pEgZVcIRCL == true){pEgZVcIRCL = false;}
      if(MxuuwGXpsU == true){MxuuwGXpsU = false;}
      if(mlrsGInSUj == true){mlrsGInSUj = false;}
      if(BhDDDZVxJk == true){BhDDDZVxJk = false;}
      if(bXGZghIBBb == true){bXGZghIBBb = false;}
      if(VcYCsELnTN == true){VcYCsELnTN = false;}
      if(opxRKetrqV == true){opxRKetrqV = false;}
      if(kZfHrOeSLY == true){kZfHrOeSLY = false;}
      if(zmQsOYJAJz == true){zmQsOYJAJz = false;}
      if(OgdwwlaoPC == true){OgdwwlaoPC = false;}
      if(mPJfquwQKe == true){mPJfquwQKe = false;}
      if(YscuNBYEDk == true){YscuNBYEDk = false;}
      if(UsiqHDujLG == true){UsiqHDujLG = false;}
      if(npDIkickCT == true){npDIkickCT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZOUTHJFWB
{ 
  void sdgGUNVuZF()
  { 
      bool mxrqbokUYs = false;
      bool IfWCwuQHjh = false;
      bool ibTqDmcWAo = false;
      bool SGMZKLAonL = false;
      bool UHQCttKQdG = false;
      bool LnUKyLcAmn = false;
      bool MNUjaBTwrk = false;
      bool taSYMbKQxI = false;
      bool cMrtcdlBay = false;
      bool hACzzHmgbr = false;
      bool aOXsLkUuyW = false;
      bool BLDdLAVZGw = false;
      bool PRUtDtXTZE = false;
      bool ocoFhNnzhq = false;
      bool JpDExVxYnz = false;
      bool lMafbItdoR = false;
      bool NBVshXWxwy = false;
      bool LWrOmZOPwh = false;
      bool xzfaSbCIcY = false;
      bool SJJPdHUJVZ = false;
      string wdlthBemRH;
      string SCjZbIxJwp;
      string HbPVjEbmwP;
      string qgioWTANrE;
      string xEPzapTiMl;
      string ERcSfUOPKc;
      string ZrpCQkTuDI;
      string IiRrsCLPts;
      string krZKKZDQJB;
      string EjDOeENNho;
      string WXfEdUzkZc;
      string IzVQrgReqq;
      string gClBDXfCNn;
      string oygEWMMUgp;
      string ZSqgsFOlVx;
      string liVqHTleBF;
      string nxXlnKRQte;
      string UxyBROLFIy;
      string IsgPBFbpwC;
      string agTaBcuFrh;
      if(wdlthBemRH == WXfEdUzkZc){mxrqbokUYs = true;}
      else if(WXfEdUzkZc == wdlthBemRH){aOXsLkUuyW = true;}
      if(SCjZbIxJwp == IzVQrgReqq){IfWCwuQHjh = true;}
      else if(IzVQrgReqq == SCjZbIxJwp){BLDdLAVZGw = true;}
      if(HbPVjEbmwP == gClBDXfCNn){ibTqDmcWAo = true;}
      else if(gClBDXfCNn == HbPVjEbmwP){PRUtDtXTZE = true;}
      if(qgioWTANrE == oygEWMMUgp){SGMZKLAonL = true;}
      else if(oygEWMMUgp == qgioWTANrE){ocoFhNnzhq = true;}
      if(xEPzapTiMl == ZSqgsFOlVx){UHQCttKQdG = true;}
      else if(ZSqgsFOlVx == xEPzapTiMl){JpDExVxYnz = true;}
      if(ERcSfUOPKc == liVqHTleBF){LnUKyLcAmn = true;}
      else if(liVqHTleBF == ERcSfUOPKc){lMafbItdoR = true;}
      if(ZrpCQkTuDI == nxXlnKRQte){MNUjaBTwrk = true;}
      else if(nxXlnKRQte == ZrpCQkTuDI){NBVshXWxwy = true;}
      if(IiRrsCLPts == UxyBROLFIy){taSYMbKQxI = true;}
      if(krZKKZDQJB == IsgPBFbpwC){cMrtcdlBay = true;}
      if(EjDOeENNho == agTaBcuFrh){hACzzHmgbr = true;}
      while(UxyBROLFIy == IiRrsCLPts){LWrOmZOPwh = true;}
      while(IsgPBFbpwC == IsgPBFbpwC){xzfaSbCIcY = true;}
      while(agTaBcuFrh == agTaBcuFrh){SJJPdHUJVZ = true;}
      if(mxrqbokUYs == true){mxrqbokUYs = false;}
      if(IfWCwuQHjh == true){IfWCwuQHjh = false;}
      if(ibTqDmcWAo == true){ibTqDmcWAo = false;}
      if(SGMZKLAonL == true){SGMZKLAonL = false;}
      if(UHQCttKQdG == true){UHQCttKQdG = false;}
      if(LnUKyLcAmn == true){LnUKyLcAmn = false;}
      if(MNUjaBTwrk == true){MNUjaBTwrk = false;}
      if(taSYMbKQxI == true){taSYMbKQxI = false;}
      if(cMrtcdlBay == true){cMrtcdlBay = false;}
      if(hACzzHmgbr == true){hACzzHmgbr = false;}
      if(aOXsLkUuyW == true){aOXsLkUuyW = false;}
      if(BLDdLAVZGw == true){BLDdLAVZGw = false;}
      if(PRUtDtXTZE == true){PRUtDtXTZE = false;}
      if(ocoFhNnzhq == true){ocoFhNnzhq = false;}
      if(JpDExVxYnz == true){JpDExVxYnz = false;}
      if(lMafbItdoR == true){lMafbItdoR = false;}
      if(NBVshXWxwy == true){NBVshXWxwy = false;}
      if(LWrOmZOPwh == true){LWrOmZOPwh = false;}
      if(xzfaSbCIcY == true){xzfaSbCIcY = false;}
      if(SJJPdHUJVZ == true){SJJPdHUJVZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEPVNJXZUC
{ 
  void UamxTrCsFy()
  { 
      bool BcNdmZuLxL = false;
      bool OsdPKcQoCT = false;
      bool lmxXZuumIm = false;
      bool FRQsQBeFwC = false;
      bool kdZUFEmfQM = false;
      bool GGoJyOfoEr = false;
      bool eICJFxbjzJ = false;
      bool xLsAhHMbSV = false;
      bool IOWwgzbHtC = false;
      bool UpBDXcbQPH = false;
      bool bCgHOtMoap = false;
      bool BDVhiPlGbG = false;
      bool UToxnHKobF = false;
      bool fwMKtGhOgl = false;
      bool lmgEARTSTI = false;
      bool pUnImHMiTH = false;
      bool jXMUJFqKnc = false;
      bool gWYpUgmkwW = false;
      bool mrUTOLHDXl = false;
      bool syuZCOZLuu = false;
      string lePLILyBfu;
      string DdobBxKNIe;
      string pkPNdCFlfn;
      string xEBusSgWPp;
      string yJNpigFhup;
      string HkaFYBPCgF;
      string GMUqxzctih;
      string QmxSffWYdw;
      string wWqpfMcwVq;
      string DeoKiloVsj;
      string ELyMZTmIYr;
      string dpXjIjUdLj;
      string WfXqekylis;
      string qBftrkXdPL;
      string YUWdNMGFCz;
      string QKKIMXmHhn;
      string VBYeAcKdrX;
      string LqOzLBJtdR;
      string drjicgpXgT;
      string xQwapXuqck;
      if(lePLILyBfu == ELyMZTmIYr){BcNdmZuLxL = true;}
      else if(ELyMZTmIYr == lePLILyBfu){bCgHOtMoap = true;}
      if(DdobBxKNIe == dpXjIjUdLj){OsdPKcQoCT = true;}
      else if(dpXjIjUdLj == DdobBxKNIe){BDVhiPlGbG = true;}
      if(pkPNdCFlfn == WfXqekylis){lmxXZuumIm = true;}
      else if(WfXqekylis == pkPNdCFlfn){UToxnHKobF = true;}
      if(xEBusSgWPp == qBftrkXdPL){FRQsQBeFwC = true;}
      else if(qBftrkXdPL == xEBusSgWPp){fwMKtGhOgl = true;}
      if(yJNpigFhup == YUWdNMGFCz){kdZUFEmfQM = true;}
      else if(YUWdNMGFCz == yJNpigFhup){lmgEARTSTI = true;}
      if(HkaFYBPCgF == QKKIMXmHhn){GGoJyOfoEr = true;}
      else if(QKKIMXmHhn == HkaFYBPCgF){pUnImHMiTH = true;}
      if(GMUqxzctih == VBYeAcKdrX){eICJFxbjzJ = true;}
      else if(VBYeAcKdrX == GMUqxzctih){jXMUJFqKnc = true;}
      if(QmxSffWYdw == LqOzLBJtdR){xLsAhHMbSV = true;}
      if(wWqpfMcwVq == drjicgpXgT){IOWwgzbHtC = true;}
      if(DeoKiloVsj == xQwapXuqck){UpBDXcbQPH = true;}
      while(LqOzLBJtdR == QmxSffWYdw){gWYpUgmkwW = true;}
      while(drjicgpXgT == drjicgpXgT){mrUTOLHDXl = true;}
      while(xQwapXuqck == xQwapXuqck){syuZCOZLuu = true;}
      if(BcNdmZuLxL == true){BcNdmZuLxL = false;}
      if(OsdPKcQoCT == true){OsdPKcQoCT = false;}
      if(lmxXZuumIm == true){lmxXZuumIm = false;}
      if(FRQsQBeFwC == true){FRQsQBeFwC = false;}
      if(kdZUFEmfQM == true){kdZUFEmfQM = false;}
      if(GGoJyOfoEr == true){GGoJyOfoEr = false;}
      if(eICJFxbjzJ == true){eICJFxbjzJ = false;}
      if(xLsAhHMbSV == true){xLsAhHMbSV = false;}
      if(IOWwgzbHtC == true){IOWwgzbHtC = false;}
      if(UpBDXcbQPH == true){UpBDXcbQPH = false;}
      if(bCgHOtMoap == true){bCgHOtMoap = false;}
      if(BDVhiPlGbG == true){BDVhiPlGbG = false;}
      if(UToxnHKobF == true){UToxnHKobF = false;}
      if(fwMKtGhOgl == true){fwMKtGhOgl = false;}
      if(lmgEARTSTI == true){lmgEARTSTI = false;}
      if(pUnImHMiTH == true){pUnImHMiTH = false;}
      if(jXMUJFqKnc == true){jXMUJFqKnc = false;}
      if(gWYpUgmkwW == true){gWYpUgmkwW = false;}
      if(mrUTOLHDXl == true){mrUTOLHDXl = false;}
      if(syuZCOZLuu == true){syuZCOZLuu = false;}
    } 
}; 
