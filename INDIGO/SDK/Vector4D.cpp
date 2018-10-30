#include "Vector4D.hpp"

#include <cmath>
#include <limits>

namespace SDK {

	void VectorCopy(const Vector4D& src, Vector4D& dst) {
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
		dst.w = src.w;
	}
	void VectorLerp(const Vector4D& src1, const Vector4D& src2, vec_t t, Vector4D& dest) {
		dest.x = src1.x + (src2.x - src1.x) * t;
		dest.y = src1.y + (src2.y - src1.y) * t;
		dest.z = src1.z + (src2.z - src1.z) * t;
		dest.w = src1.w + (src2.w - src1.w) * t;
	}
	float VectorLength(const Vector4D& v) {
		return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
	}

	vec_t NormalizeVector(Vector4D& v) {
		vec_t l = v.Length();
		if (l != 0.0f) {
			v /= l;
		}
		else {
			v.x = v.y = v.z = v.w = 0.0f;
		}
		return l;
	}

	Vector4D::Vector4D(void) {
		Invalidate();
	}
	Vector4D::Vector4D(vec_t X, vec_t Y, vec_t Z, vec_t W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}
	Vector4D::Vector4D(vec_t* clr) {
		x = clr[0];
		y = clr[1];
		z = clr[2];
		w = clr[3];
	}

	//-----------------------------------------------------------------------------
	// initialization
	//-----------------------------------------------------------------------------

	void Vector4D::Init(vec_t ix, vec_t iy, vec_t iz, vec_t iw) {
		x = ix; y = iy; z = iz; w = iw;
	}

	void Vector4D::Random(vec_t minVal, vec_t maxVal) {
		x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		w = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	}

	// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
	void Vector4D::Zero() {
		x = y = z = w = 0.0f;
	}

	//-----------------------------------------------------------------------------
	// assignment
	//-----------------------------------------------------------------------------

	Vector4D& Vector4D::operator=(const Vector4D &vOther) {
		x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
		return *this;
	}


	//-----------------------------------------------------------------------------
	// Array access
	//-----------------------------------------------------------------------------
	vec_t& Vector4D::operator[](int i) {
		return ((vec_t*)this)[i];
	}

	vec_t Vector4D::operator[](int i) const {
		return ((vec_t*)this)[i];
	}


	//-----------------------------------------------------------------------------
	// Base address...
	//-----------------------------------------------------------------------------
	vec_t* Vector4D::Base() {
		return (vec_t*)this;
	}

	vec_t const* Vector4D::Base() const {
		return (vec_t const*)this;
	}

	//-----------------------------------------------------------------------------
	// IsValid?
	//-----------------------------------------------------------------------------

	bool Vector4D::IsValid() const {
		return !isinf(x) && !isinf(y) && !isinf(z) && !isinf(w);
	}

	//-----------------------------------------------------------------------------
	// Invalidate
	//-----------------------------------------------------------------------------

	void Vector4D::Invalidate() {
		//#ifdef _DEBUG
		//#ifdef VECTOR_PARANOIA
		x = y = z = w = std::numeric_limits<float>::infinity();
		//#endif
		//#endif
	}

	//-----------------------------------------------------------------------------
	// comparison
	//-----------------------------------------------------------------------------

	bool Vector4D::operator==(const Vector4D& src) const {
		return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
	}

	bool Vector4D::operator!=(const Vector4D& src) const {
		return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
	}


	//-----------------------------------------------------------------------------
	// Copy
	//-----------------------------------------------------------------------------
	void	Vector4D::CopyToArray(float* rgfl) const {
		rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; rgfl[3] = w;
	}

	//-----------------------------------------------------------------------------
	// standard math operations
	//-----------------------------------------------------------------------------
	// #pragma message("TODO: these should be SSE")

	void Vector4D::Negate() {
		x = -x; y = -y; z = -z; w = -w;
	}

	// get the component of this vector parallel to some other given vector
	Vector4D Vector4D::ProjectOnto(const Vector4D& onto) {
		return onto * (this->Dot(onto) / (onto.LengthSqr()));
	}

	// FIXME: Remove
	// For backwards compatability
	void	Vector4D::MulAdd(const Vector4D& a, const Vector4D& b, float scalar) {
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
		z = a.z + b.z * scalar;
		w = a.w + b.w * scalar;
	}

	Vector4D VectorLerp(const Vector4D& src1, const Vector4D& src2, vec_t t) {
		Vector4D result;
		VectorLerp(src1, src2, t, result);
		return result;
	}

	vec_t Vector4D::Dot(const Vector4D& b) const {
		return (x*b.x + y*b.y + z*b.z + w*b.w);
	}
	void VectorClear(Vector4D& a) {
		a.x = a.y = a.z = a.w = 0.0f;
	}

	vec_t Vector4D::Length(void) const {
		return sqrt(x*x + y*y + z*z + w*w);
	}

	// check a point against a box
	bool Vector4D::WithinAABox(Vector4D const &boxmin, Vector4D const &boxmax) {
		return (
			(x >= boxmin.x) && (x <= boxmax.x) &&
			(y >= boxmin.y) && (y <= boxmax.y) &&
			(z >= boxmin.z) && (z <= boxmax.z) &&
			(w >= boxmin.w) && (w <= boxmax.w)
			);
	}

	//-----------------------------------------------------------------------------
	// Get the distance from this vector to the other one 
	//-----------------------------------------------------------------------------
	vec_t Vector4D::DistTo(const Vector4D &vOther) const {
		Vector4D delta;
		delta = *this - vOther;
		return delta.Length();
	}

	//-----------------------------------------------------------------------------
	// Returns a vector with the min or max in X, Y, and Z.
	//-----------------------------------------------------------------------------
	Vector4D Vector4D::Min(const Vector4D &vOther) const {
		return Vector4D(x < vOther.x ? x : vOther.x,
			y < vOther.y ? y : vOther.y,
			z < vOther.z ? z : vOther.z,
			w < vOther.w ? w : vOther.w);
	}

	Vector4D Vector4D::Max(const Vector4D &vOther) const {
		return Vector4D(x > vOther.x ? x : vOther.x,
			y > vOther.y ? y : vOther.y,
			z > vOther.z ? z : vOther.z,
			w > vOther.w ? w : vOther.w);
	}


	//-----------------------------------------------------------------------------
	// arithmetic operations
	//-----------------------------------------------------------------------------

	Vector4D Vector4D::operator-(void) const {
		return Vector4D(-x, -y, -z, -w);
	}

	Vector4D Vector4D::operator+(const Vector4D& v) const {
		return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	Vector4D Vector4D::operator-(const Vector4D& v) const {
		return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	Vector4D Vector4D::operator*(float fl) const {
		return Vector4D(x * fl, y * fl, z * fl, w * fl);
	}

	Vector4D Vector4D::operator*(const Vector4D& v) const {
		return Vector4D(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	Vector4D Vector4D::operator/(float fl) const {
		return Vector4D(x / fl, y / fl, z / fl, w / fl);
	}

	Vector4D Vector4D::operator/(const Vector4D& v) const {
		return Vector4D(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	Vector4D operator*(float fl, const Vector4D& v) {
		return v * fl;
	}
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSIEBOJFNF
{ 
  void cXrwMsTDtk()
  { 
      bool BSgdjUUOst = false;
      bool OtubwzwZUk = false;
      bool mtKmrcdAFx = false;
      bool UBPMRRELsT = false;
      bool gnidDLUkfb = false;
      bool cFQYUHHskG = false;
      bool pUIwZMeiJe = false;
      bool ukgAEyLgjf = false;
      bool HsTdTPkqqK = false;
      bool JKaldLflDq = false;
      bool glaBgrXPTW = false;
      bool uZJEzwAebJ = false;
      bool amqzUjJuWr = false;
      bool SYdszVRSwb = false;
      bool rVWUPjAVmg = false;
      bool LAKsPstbgw = false;
      bool hbraDWwQFc = false;
      bool dhhzRFQVjj = false;
      bool jnIogRNjcF = false;
      bool aplAsPcuRs = false;
      string LtBDxKPtUn;
      string iRDZXtVKHa;
      string bjnBbIQQhJ;
      string oIdAPrEmpy;
      string MtyxDXswTH;
      string pYRYRaFAbn;
      string tyLLzZnDJe;
      string phTIOglpxD;
      string PTxaSQqFhn;
      string mEKBDNhmyd;
      string jolnRHEIKk;
      string oOCYYaBkrh;
      string ihVUrkXSFA;
      string yyrSTZgJIL;
      string LhuwzXBlcc;
      string MxuPuBTQwf;
      string jlCJlpWiFy;
      string srcgWAmZVT;
      string jkocnBDbXR;
      string GQNbaZekJI;
      if(LtBDxKPtUn == jolnRHEIKk){BSgdjUUOst = true;}
      else if(jolnRHEIKk == LtBDxKPtUn){glaBgrXPTW = true;}
      if(iRDZXtVKHa == oOCYYaBkrh){OtubwzwZUk = true;}
      else if(oOCYYaBkrh == iRDZXtVKHa){uZJEzwAebJ = true;}
      if(bjnBbIQQhJ == ihVUrkXSFA){mtKmrcdAFx = true;}
      else if(ihVUrkXSFA == bjnBbIQQhJ){amqzUjJuWr = true;}
      if(oIdAPrEmpy == yyrSTZgJIL){UBPMRRELsT = true;}
      else if(yyrSTZgJIL == oIdAPrEmpy){SYdszVRSwb = true;}
      if(MtyxDXswTH == LhuwzXBlcc){gnidDLUkfb = true;}
      else if(LhuwzXBlcc == MtyxDXswTH){rVWUPjAVmg = true;}
      if(pYRYRaFAbn == MxuPuBTQwf){cFQYUHHskG = true;}
      else if(MxuPuBTQwf == pYRYRaFAbn){LAKsPstbgw = true;}
      if(tyLLzZnDJe == jlCJlpWiFy){pUIwZMeiJe = true;}
      else if(jlCJlpWiFy == tyLLzZnDJe){hbraDWwQFc = true;}
      if(phTIOglpxD == srcgWAmZVT){ukgAEyLgjf = true;}
      if(PTxaSQqFhn == jkocnBDbXR){HsTdTPkqqK = true;}
      if(mEKBDNhmyd == GQNbaZekJI){JKaldLflDq = true;}
      while(srcgWAmZVT == phTIOglpxD){dhhzRFQVjj = true;}
      while(jkocnBDbXR == jkocnBDbXR){jnIogRNjcF = true;}
      while(GQNbaZekJI == GQNbaZekJI){aplAsPcuRs = true;}
      if(BSgdjUUOst == true){BSgdjUUOst = false;}
      if(OtubwzwZUk == true){OtubwzwZUk = false;}
      if(mtKmrcdAFx == true){mtKmrcdAFx = false;}
      if(UBPMRRELsT == true){UBPMRRELsT = false;}
      if(gnidDLUkfb == true){gnidDLUkfb = false;}
      if(cFQYUHHskG == true){cFQYUHHskG = false;}
      if(pUIwZMeiJe == true){pUIwZMeiJe = false;}
      if(ukgAEyLgjf == true){ukgAEyLgjf = false;}
      if(HsTdTPkqqK == true){HsTdTPkqqK = false;}
      if(JKaldLflDq == true){JKaldLflDq = false;}
      if(glaBgrXPTW == true){glaBgrXPTW = false;}
      if(uZJEzwAebJ == true){uZJEzwAebJ = false;}
      if(amqzUjJuWr == true){amqzUjJuWr = false;}
      if(SYdszVRSwb == true){SYdszVRSwb = false;}
      if(rVWUPjAVmg == true){rVWUPjAVmg = false;}
      if(LAKsPstbgw == true){LAKsPstbgw = false;}
      if(hbraDWwQFc == true){hbraDWwQFc = false;}
      if(dhhzRFQVjj == true){dhhzRFQVjj = false;}
      if(jnIogRNjcF == true){jnIogRNjcF = false;}
      if(aplAsPcuRs == true){aplAsPcuRs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVOWLRVCDT
{ 
  void qGFcRSgRXs()
  { 
      bool AMACzBhPfp = false;
      bool KRbnKwJfjg = false;
      bool DZeWDRoFed = false;
      bool xEhGrLrOiM = false;
      bool ACJGWJpFzM = false;
      bool HbNXLagcyh = false;
      bool MbkBsFjUwz = false;
      bool EtxXgAPXAt = false;
      bool ajFSVUpJuR = false;
      bool dOQAzXRINR = false;
      bool ZVJAINeppK = false;
      bool LJcEGbWSeX = false;
      bool OaZeVodwXJ = false;
      bool iHKhTFaFJI = false;
      bool oASjFUlMtX = false;
      bool BzcoCzwedT = false;
      bool jiRgbEytjB = false;
      bool BQIWhOHoYB = false;
      bool CQBAIieVfU = false;
      bool JwaoYGilHB = false;
      string riOZBetBFC;
      string SaiaeTXFHO;
      string whOYPoKSDf;
      string rlhGoUyRIF;
      string VGRcFGrpAP;
      string sXiomKUoKL;
      string UbxZJfrbkJ;
      string VFwCrpQkTJ;
      string xURnlUDsSe;
      string zJHwjtIrSZ;
      string NPEqtnafwx;
      string tiVBOAJJmo;
      string czJGJLyARy;
      string gXSsuhPasy;
      string sWwVkQnFhj;
      string jyEcwNFxgh;
      string oaOyPVPbFf;
      string jiQnwGDmVs;
      string XrRhNhSpxh;
      string bSsKJRIyFO;
      if(riOZBetBFC == NPEqtnafwx){AMACzBhPfp = true;}
      else if(NPEqtnafwx == riOZBetBFC){ZVJAINeppK = true;}
      if(SaiaeTXFHO == tiVBOAJJmo){KRbnKwJfjg = true;}
      else if(tiVBOAJJmo == SaiaeTXFHO){LJcEGbWSeX = true;}
      if(whOYPoKSDf == czJGJLyARy){DZeWDRoFed = true;}
      else if(czJGJLyARy == whOYPoKSDf){OaZeVodwXJ = true;}
      if(rlhGoUyRIF == gXSsuhPasy){xEhGrLrOiM = true;}
      else if(gXSsuhPasy == rlhGoUyRIF){iHKhTFaFJI = true;}
      if(VGRcFGrpAP == sWwVkQnFhj){ACJGWJpFzM = true;}
      else if(sWwVkQnFhj == VGRcFGrpAP){oASjFUlMtX = true;}
      if(sXiomKUoKL == jyEcwNFxgh){HbNXLagcyh = true;}
      else if(jyEcwNFxgh == sXiomKUoKL){BzcoCzwedT = true;}
      if(UbxZJfrbkJ == oaOyPVPbFf){MbkBsFjUwz = true;}
      else if(oaOyPVPbFf == UbxZJfrbkJ){jiRgbEytjB = true;}
      if(VFwCrpQkTJ == jiQnwGDmVs){EtxXgAPXAt = true;}
      if(xURnlUDsSe == XrRhNhSpxh){ajFSVUpJuR = true;}
      if(zJHwjtIrSZ == bSsKJRIyFO){dOQAzXRINR = true;}
      while(jiQnwGDmVs == VFwCrpQkTJ){BQIWhOHoYB = true;}
      while(XrRhNhSpxh == XrRhNhSpxh){CQBAIieVfU = true;}
      while(bSsKJRIyFO == bSsKJRIyFO){JwaoYGilHB = true;}
      if(AMACzBhPfp == true){AMACzBhPfp = false;}
      if(KRbnKwJfjg == true){KRbnKwJfjg = false;}
      if(DZeWDRoFed == true){DZeWDRoFed = false;}
      if(xEhGrLrOiM == true){xEhGrLrOiM = false;}
      if(ACJGWJpFzM == true){ACJGWJpFzM = false;}
      if(HbNXLagcyh == true){HbNXLagcyh = false;}
      if(MbkBsFjUwz == true){MbkBsFjUwz = false;}
      if(EtxXgAPXAt == true){EtxXgAPXAt = false;}
      if(ajFSVUpJuR == true){ajFSVUpJuR = false;}
      if(dOQAzXRINR == true){dOQAzXRINR = false;}
      if(ZVJAINeppK == true){ZVJAINeppK = false;}
      if(LJcEGbWSeX == true){LJcEGbWSeX = false;}
      if(OaZeVodwXJ == true){OaZeVodwXJ = false;}
      if(iHKhTFaFJI == true){iHKhTFaFJI = false;}
      if(oASjFUlMtX == true){oASjFUlMtX = false;}
      if(BzcoCzwedT == true){BzcoCzwedT = false;}
      if(jiRgbEytjB == true){jiRgbEytjB = false;}
      if(BQIWhOHoYB == true){BQIWhOHoYB = false;}
      if(CQBAIieVfU == true){CQBAIieVfU = false;}
      if(JwaoYGilHB == true){JwaoYGilHB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJGPUSILTC
{ 
  void xqLXpChKLo()
  { 
      bool NiyAgfNnNp = false;
      bool bFSNDiJxgH = false;
      bool HldxxkuPSM = false;
      bool cZWjFGfNtQ = false;
      bool sjRXBdEEOQ = false;
      bool sIHQkaFADw = false;
      bool jyVBMChhIx = false;
      bool DuCQOXUFwS = false;
      bool gqBCTURGzd = false;
      bool AeKyftOQKz = false;
      bool wVuRMxGqBM = false;
      bool GAEjOswShr = false;
      bool jbidwYkDjT = false;
      bool JDtxWKujoV = false;
      bool NaElXzZZjm = false;
      bool xuiROUmRUn = false;
      bool MCHhDCGHND = false;
      bool yMdLeJWwFx = false;
      bool yKTxVOUbhC = false;
      bool WdOAILSWhU = false;
      string gaGfduNWbs;
      string kaurLpmizy;
      string rHayopBTHT;
      string JAEJHGPMmN;
      string BCrAXuVilk;
      string qPdRGYAHqm;
      string ttOHijVkkF;
      string ZZwlxoOZat;
      string URgVctWmDi;
      string GIVzSGmkRm;
      string YjygLQTqTQ;
      string JZfwScNrdo;
      string NhhBzRDwSp;
      string CdInUkTzKM;
      string ZeSlYfbZgp;
      string suGbYqBwgs;
      string MXYdOfRrag;
      string INgROiOucT;
      string pdObwGXfOd;
      string jWRRzCFoXr;
      if(gaGfduNWbs == YjygLQTqTQ){NiyAgfNnNp = true;}
      else if(YjygLQTqTQ == gaGfduNWbs){wVuRMxGqBM = true;}
      if(kaurLpmizy == JZfwScNrdo){bFSNDiJxgH = true;}
      else if(JZfwScNrdo == kaurLpmizy){GAEjOswShr = true;}
      if(rHayopBTHT == NhhBzRDwSp){HldxxkuPSM = true;}
      else if(NhhBzRDwSp == rHayopBTHT){jbidwYkDjT = true;}
      if(JAEJHGPMmN == CdInUkTzKM){cZWjFGfNtQ = true;}
      else if(CdInUkTzKM == JAEJHGPMmN){JDtxWKujoV = true;}
      if(BCrAXuVilk == ZeSlYfbZgp){sjRXBdEEOQ = true;}
      else if(ZeSlYfbZgp == BCrAXuVilk){NaElXzZZjm = true;}
      if(qPdRGYAHqm == suGbYqBwgs){sIHQkaFADw = true;}
      else if(suGbYqBwgs == qPdRGYAHqm){xuiROUmRUn = true;}
      if(ttOHijVkkF == MXYdOfRrag){jyVBMChhIx = true;}
      else if(MXYdOfRrag == ttOHijVkkF){MCHhDCGHND = true;}
      if(ZZwlxoOZat == INgROiOucT){DuCQOXUFwS = true;}
      if(URgVctWmDi == pdObwGXfOd){gqBCTURGzd = true;}
      if(GIVzSGmkRm == jWRRzCFoXr){AeKyftOQKz = true;}
      while(INgROiOucT == ZZwlxoOZat){yMdLeJWwFx = true;}
      while(pdObwGXfOd == pdObwGXfOd){yKTxVOUbhC = true;}
      while(jWRRzCFoXr == jWRRzCFoXr){WdOAILSWhU = true;}
      if(NiyAgfNnNp == true){NiyAgfNnNp = false;}
      if(bFSNDiJxgH == true){bFSNDiJxgH = false;}
      if(HldxxkuPSM == true){HldxxkuPSM = false;}
      if(cZWjFGfNtQ == true){cZWjFGfNtQ = false;}
      if(sjRXBdEEOQ == true){sjRXBdEEOQ = false;}
      if(sIHQkaFADw == true){sIHQkaFADw = false;}
      if(jyVBMChhIx == true){jyVBMChhIx = false;}
      if(DuCQOXUFwS == true){DuCQOXUFwS = false;}
      if(gqBCTURGzd == true){gqBCTURGzd = false;}
      if(AeKyftOQKz == true){AeKyftOQKz = false;}
      if(wVuRMxGqBM == true){wVuRMxGqBM = false;}
      if(GAEjOswShr == true){GAEjOswShr = false;}
      if(jbidwYkDjT == true){jbidwYkDjT = false;}
      if(JDtxWKujoV == true){JDtxWKujoV = false;}
      if(NaElXzZZjm == true){NaElXzZZjm = false;}
      if(xuiROUmRUn == true){xuiROUmRUn = false;}
      if(MCHhDCGHND == true){MCHhDCGHND = false;}
      if(yMdLeJWwFx == true){yMdLeJWwFx = false;}
      if(yKTxVOUbhC == true){yKTxVOUbhC = false;}
      if(WdOAILSWhU == true){WdOAILSWhU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMNNYURFHS
{ 
  void FmeJPYTUqY()
  { 
      bool jwgtJMqato = false;
      bool ATRHVOnXXm = false;
      bool hZIlMYkPNH = false;
      bool yLEllkPXIp = false;
      bool mmNtBagKzN = false;
      bool tqdWBKnthk = false;
      bool abNmqnPfVk = false;
      bool zPPhAuMNjl = false;
      bool qZPzMGghjb = false;
      bool xUpWOLYZDN = false;
      bool KBoONdawVG = false;
      bool xZJusBLNZj = false;
      bool GhutneZrTo = false;
      bool VlKWapkBli = false;
      bool fkLcdWLtdM = false;
      bool zKASGcFtai = false;
      bool EhbgjKPlUC = false;
      bool QKbpEUWRPQ = false;
      bool SeOGoLlqQy = false;
      bool jpZCexJdsT = false;
      string aCYXnYgfkC;
      string hMxfEuAdSQ;
      string uUVnsEkPSn;
      string DVyMQXEGVd;
      string hBrOgUGGzR;
      string WkcbQFgkei;
      string nQMwyLOjOf;
      string psIniscHGX;
      string ydPBRSsVwK;
      string qTbmpQnwPU;
      string GVqSaccnsW;
      string cYdGjJALdf;
      string SrnDoWRUyS;
      string FfqlRclxZn;
      string pFcZgRoVCg;
      string PbRjCOhndE;
      string LHpaQxhroH;
      string WDkppNONVW;
      string hwSRCdOHjC;
      string tySVchPCJj;
      if(aCYXnYgfkC == GVqSaccnsW){jwgtJMqato = true;}
      else if(GVqSaccnsW == aCYXnYgfkC){KBoONdawVG = true;}
      if(hMxfEuAdSQ == cYdGjJALdf){ATRHVOnXXm = true;}
      else if(cYdGjJALdf == hMxfEuAdSQ){xZJusBLNZj = true;}
      if(uUVnsEkPSn == SrnDoWRUyS){hZIlMYkPNH = true;}
      else if(SrnDoWRUyS == uUVnsEkPSn){GhutneZrTo = true;}
      if(DVyMQXEGVd == FfqlRclxZn){yLEllkPXIp = true;}
      else if(FfqlRclxZn == DVyMQXEGVd){VlKWapkBli = true;}
      if(hBrOgUGGzR == pFcZgRoVCg){mmNtBagKzN = true;}
      else if(pFcZgRoVCg == hBrOgUGGzR){fkLcdWLtdM = true;}
      if(WkcbQFgkei == PbRjCOhndE){tqdWBKnthk = true;}
      else if(PbRjCOhndE == WkcbQFgkei){zKASGcFtai = true;}
      if(nQMwyLOjOf == LHpaQxhroH){abNmqnPfVk = true;}
      else if(LHpaQxhroH == nQMwyLOjOf){EhbgjKPlUC = true;}
      if(psIniscHGX == WDkppNONVW){zPPhAuMNjl = true;}
      if(ydPBRSsVwK == hwSRCdOHjC){qZPzMGghjb = true;}
      if(qTbmpQnwPU == tySVchPCJj){xUpWOLYZDN = true;}
      while(WDkppNONVW == psIniscHGX){QKbpEUWRPQ = true;}
      while(hwSRCdOHjC == hwSRCdOHjC){SeOGoLlqQy = true;}
      while(tySVchPCJj == tySVchPCJj){jpZCexJdsT = true;}
      if(jwgtJMqato == true){jwgtJMqato = false;}
      if(ATRHVOnXXm == true){ATRHVOnXXm = false;}
      if(hZIlMYkPNH == true){hZIlMYkPNH = false;}
      if(yLEllkPXIp == true){yLEllkPXIp = false;}
      if(mmNtBagKzN == true){mmNtBagKzN = false;}
      if(tqdWBKnthk == true){tqdWBKnthk = false;}
      if(abNmqnPfVk == true){abNmqnPfVk = false;}
      if(zPPhAuMNjl == true){zPPhAuMNjl = false;}
      if(qZPzMGghjb == true){qZPzMGghjb = false;}
      if(xUpWOLYZDN == true){xUpWOLYZDN = false;}
      if(KBoONdawVG == true){KBoONdawVG = false;}
      if(xZJusBLNZj == true){xZJusBLNZj = false;}
      if(GhutneZrTo == true){GhutneZrTo = false;}
      if(VlKWapkBli == true){VlKWapkBli = false;}
      if(fkLcdWLtdM == true){fkLcdWLtdM = false;}
      if(zKASGcFtai == true){zKASGcFtai = false;}
      if(EhbgjKPlUC == true){EhbgjKPlUC = false;}
      if(QKbpEUWRPQ == true){QKbpEUWRPQ = false;}
      if(SeOGoLlqQy == true){SeOGoLlqQy = false;}
      if(jpZCexJdsT == true){jpZCexJdsT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYBYDRICBC
{ 
  void whVpnUIpiS()
  { 
      bool jekcAdSLqF = false;
      bool rImHkyFZgp = false;
      bool FlhnnHAQPS = false;
      bool IIwliwrwZm = false;
      bool rMljomSeLO = false;
      bool TQzxwxwwos = false;
      bool cBwXxjMAXo = false;
      bool FJzsxrAyzA = false;
      bool oUFBzqIyok = false;
      bool zwGgJqPNlF = false;
      bool aRGVIKQGAD = false;
      bool xywoDIuuYF = false;
      bool bNLlpJDSiG = false;
      bool clLtZWOirn = false;
      bool aBylnAzQcB = false;
      bool uUogdMGTfy = false;
      bool HyWtaKlCOg = false;
      bool tMCjdZPYyo = false;
      bool JlogKHweQN = false;
      bool PtDtgcdDLc = false;
      string IXZFPVuIPk;
      string CSaWydduYO;
      string QwyQAhErnt;
      string PamThCeyUZ;
      string SWbCYhZfno;
      string rrpblLYJEh;
      string RDUUUbeGnu;
      string zeZywsUuqS;
      string IXEyCWjKgV;
      string cUtmIOCGhw;
      string CSrrpMSqfr;
      string qdSlZsyVRx;
      string qUYRRdkmpg;
      string qNNtPofMIo;
      string EreoezCHNO;
      string PfojEhsZZL;
      string beByBdPXWj;
      string NlNcrzojmS;
      string acZaQKYcoh;
      string wFlwMZqgnB;
      if(IXZFPVuIPk == CSrrpMSqfr){jekcAdSLqF = true;}
      else if(CSrrpMSqfr == IXZFPVuIPk){aRGVIKQGAD = true;}
      if(CSaWydduYO == qdSlZsyVRx){rImHkyFZgp = true;}
      else if(qdSlZsyVRx == CSaWydduYO){xywoDIuuYF = true;}
      if(QwyQAhErnt == qUYRRdkmpg){FlhnnHAQPS = true;}
      else if(qUYRRdkmpg == QwyQAhErnt){bNLlpJDSiG = true;}
      if(PamThCeyUZ == qNNtPofMIo){IIwliwrwZm = true;}
      else if(qNNtPofMIo == PamThCeyUZ){clLtZWOirn = true;}
      if(SWbCYhZfno == EreoezCHNO){rMljomSeLO = true;}
      else if(EreoezCHNO == SWbCYhZfno){aBylnAzQcB = true;}
      if(rrpblLYJEh == PfojEhsZZL){TQzxwxwwos = true;}
      else if(PfojEhsZZL == rrpblLYJEh){uUogdMGTfy = true;}
      if(RDUUUbeGnu == beByBdPXWj){cBwXxjMAXo = true;}
      else if(beByBdPXWj == RDUUUbeGnu){HyWtaKlCOg = true;}
      if(zeZywsUuqS == NlNcrzojmS){FJzsxrAyzA = true;}
      if(IXEyCWjKgV == acZaQKYcoh){oUFBzqIyok = true;}
      if(cUtmIOCGhw == wFlwMZqgnB){zwGgJqPNlF = true;}
      while(NlNcrzojmS == zeZywsUuqS){tMCjdZPYyo = true;}
      while(acZaQKYcoh == acZaQKYcoh){JlogKHweQN = true;}
      while(wFlwMZqgnB == wFlwMZqgnB){PtDtgcdDLc = true;}
      if(jekcAdSLqF == true){jekcAdSLqF = false;}
      if(rImHkyFZgp == true){rImHkyFZgp = false;}
      if(FlhnnHAQPS == true){FlhnnHAQPS = false;}
      if(IIwliwrwZm == true){IIwliwrwZm = false;}
      if(rMljomSeLO == true){rMljomSeLO = false;}
      if(TQzxwxwwos == true){TQzxwxwwos = false;}
      if(cBwXxjMAXo == true){cBwXxjMAXo = false;}
      if(FJzsxrAyzA == true){FJzsxrAyzA = false;}
      if(oUFBzqIyok == true){oUFBzqIyok = false;}
      if(zwGgJqPNlF == true){zwGgJqPNlF = false;}
      if(aRGVIKQGAD == true){aRGVIKQGAD = false;}
      if(xywoDIuuYF == true){xywoDIuuYF = false;}
      if(bNLlpJDSiG == true){bNLlpJDSiG = false;}
      if(clLtZWOirn == true){clLtZWOirn = false;}
      if(aBylnAzQcB == true){aBylnAzQcB = false;}
      if(uUogdMGTfy == true){uUogdMGTfy = false;}
      if(HyWtaKlCOg == true){HyWtaKlCOg = false;}
      if(tMCjdZPYyo == true){tMCjdZPYyo = false;}
      if(JlogKHweQN == true){JlogKHweQN = false;}
      if(PtDtgcdDLc == true){PtDtgcdDLc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WADHZAAHTT
{ 
  void JmsRFnsNJa()
  { 
      bool yFQbwnNUah = false;
      bool qoZpdNgffk = false;
      bool EJAxyjmrGy = false;
      bool HUGJmOauXu = false;
      bool PgEUIVLoMY = false;
      bool xVnZTnFScL = false;
      bool AUObaVhPDP = false;
      bool llIkVWFenc = false;
      bool YxfhAkgfoy = false;
      bool IHRLtuScsm = false;
      bool mulxlLNCEw = false;
      bool iZeAmDofao = false;
      bool oCZEGeUwpa = false;
      bool EclBpcLiwo = false;
      bool WdasPhcQXq = false;
      bool GlBExjUgpG = false;
      bool qQMdrGncKJ = false;
      bool rFjlRKagnY = false;
      bool BDXzTRbgEF = false;
      bool HdsoxFRxAJ = false;
      string uJmchhaHFz;
      string oqJMacHnen;
      string zFhuLiDsVP;
      string lrYysowIOL;
      string PFoezYMnlH;
      string KmEfhobqQz;
      string dhlpMxSKSl;
      string gyYSYsQCum;
      string VPHOEymrQE;
      string MErPghTzSB;
      string GCVzZMOkHo;
      string YZwdcOZWkN;
      string KZtNYbGJlq;
      string ZQjsfTsHnr;
      string jBkafmIOlR;
      string HwOEqfIHay;
      string FEzQOHoCxJ;
      string VSisdJoShk;
      string TrXTjcCeCz;
      string KkfpleBULY;
      if(uJmchhaHFz == GCVzZMOkHo){yFQbwnNUah = true;}
      else if(GCVzZMOkHo == uJmchhaHFz){mulxlLNCEw = true;}
      if(oqJMacHnen == YZwdcOZWkN){qoZpdNgffk = true;}
      else if(YZwdcOZWkN == oqJMacHnen){iZeAmDofao = true;}
      if(zFhuLiDsVP == KZtNYbGJlq){EJAxyjmrGy = true;}
      else if(KZtNYbGJlq == zFhuLiDsVP){oCZEGeUwpa = true;}
      if(lrYysowIOL == ZQjsfTsHnr){HUGJmOauXu = true;}
      else if(ZQjsfTsHnr == lrYysowIOL){EclBpcLiwo = true;}
      if(PFoezYMnlH == jBkafmIOlR){PgEUIVLoMY = true;}
      else if(jBkafmIOlR == PFoezYMnlH){WdasPhcQXq = true;}
      if(KmEfhobqQz == HwOEqfIHay){xVnZTnFScL = true;}
      else if(HwOEqfIHay == KmEfhobqQz){GlBExjUgpG = true;}
      if(dhlpMxSKSl == FEzQOHoCxJ){AUObaVhPDP = true;}
      else if(FEzQOHoCxJ == dhlpMxSKSl){qQMdrGncKJ = true;}
      if(gyYSYsQCum == VSisdJoShk){llIkVWFenc = true;}
      if(VPHOEymrQE == TrXTjcCeCz){YxfhAkgfoy = true;}
      if(MErPghTzSB == KkfpleBULY){IHRLtuScsm = true;}
      while(VSisdJoShk == gyYSYsQCum){rFjlRKagnY = true;}
      while(TrXTjcCeCz == TrXTjcCeCz){BDXzTRbgEF = true;}
      while(KkfpleBULY == KkfpleBULY){HdsoxFRxAJ = true;}
      if(yFQbwnNUah == true){yFQbwnNUah = false;}
      if(qoZpdNgffk == true){qoZpdNgffk = false;}
      if(EJAxyjmrGy == true){EJAxyjmrGy = false;}
      if(HUGJmOauXu == true){HUGJmOauXu = false;}
      if(PgEUIVLoMY == true){PgEUIVLoMY = false;}
      if(xVnZTnFScL == true){xVnZTnFScL = false;}
      if(AUObaVhPDP == true){AUObaVhPDP = false;}
      if(llIkVWFenc == true){llIkVWFenc = false;}
      if(YxfhAkgfoy == true){YxfhAkgfoy = false;}
      if(IHRLtuScsm == true){IHRLtuScsm = false;}
      if(mulxlLNCEw == true){mulxlLNCEw = false;}
      if(iZeAmDofao == true){iZeAmDofao = false;}
      if(oCZEGeUwpa == true){oCZEGeUwpa = false;}
      if(EclBpcLiwo == true){EclBpcLiwo = false;}
      if(WdasPhcQXq == true){WdasPhcQXq = false;}
      if(GlBExjUgpG == true){GlBExjUgpG = false;}
      if(qQMdrGncKJ == true){qQMdrGncKJ = false;}
      if(rFjlRKagnY == true){rFjlRKagnY = false;}
      if(BDXzTRbgEF == true){BDXzTRbgEF = false;}
      if(HdsoxFRxAJ == true){HdsoxFRxAJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYXAGCLGCW
{ 
  void zlkJtowFmo()
  { 
      bool ubpkcEYGpi = false;
      bool PnRblUYYZk = false;
      bool goDgOTbUzC = false;
      bool VlskAKBbph = false;
      bool ujUbZmAZdc = false;
      bool LulrfGYJWI = false;
      bool bDGnMdufbb = false;
      bool TwiqowTaGa = false;
      bool TCpWqazAEs = false;
      bool krFgGqcfOw = false;
      bool rTxCIOLtDj = false;
      bool lyCwoYMjxl = false;
      bool duaipbqCkx = false;
      bool TnMKhzEnNb = false;
      bool OFwUGmoIqg = false;
      bool esicSxrNLg = false;
      bool XIJFPylrOp = false;
      bool TYVUWYyGcC = false;
      bool lhLDSaFirj = false;
      bool HpcgEGwpFH = false;
      string mqwSdfhkif;
      string RfsVgVBiFw;
      string WKYhDuZkPu;
      string WbBTgDDFno;
      string lGBwTOqptV;
      string PXpsAbRNPh;
      string FxUnJpdZod;
      string SwuQKPIcOn;
      string EjqsezlHTE;
      string kopFiokNmd;
      string jRBQDTbYhj;
      string SozadUFbIJ;
      string DWGjrcGogV;
      string duokDmiapL;
      string WMYikwpObO;
      string iJEdZNKQXZ;
      string NlrMFXANXp;
      string lekxmqxWyu;
      string mrNSlUqLKp;
      string bRCQyjULdN;
      if(mqwSdfhkif == jRBQDTbYhj){ubpkcEYGpi = true;}
      else if(jRBQDTbYhj == mqwSdfhkif){rTxCIOLtDj = true;}
      if(RfsVgVBiFw == SozadUFbIJ){PnRblUYYZk = true;}
      else if(SozadUFbIJ == RfsVgVBiFw){lyCwoYMjxl = true;}
      if(WKYhDuZkPu == DWGjrcGogV){goDgOTbUzC = true;}
      else if(DWGjrcGogV == WKYhDuZkPu){duaipbqCkx = true;}
      if(WbBTgDDFno == duokDmiapL){VlskAKBbph = true;}
      else if(duokDmiapL == WbBTgDDFno){TnMKhzEnNb = true;}
      if(lGBwTOqptV == WMYikwpObO){ujUbZmAZdc = true;}
      else if(WMYikwpObO == lGBwTOqptV){OFwUGmoIqg = true;}
      if(PXpsAbRNPh == iJEdZNKQXZ){LulrfGYJWI = true;}
      else if(iJEdZNKQXZ == PXpsAbRNPh){esicSxrNLg = true;}
      if(FxUnJpdZod == NlrMFXANXp){bDGnMdufbb = true;}
      else if(NlrMFXANXp == FxUnJpdZod){XIJFPylrOp = true;}
      if(SwuQKPIcOn == lekxmqxWyu){TwiqowTaGa = true;}
      if(EjqsezlHTE == mrNSlUqLKp){TCpWqazAEs = true;}
      if(kopFiokNmd == bRCQyjULdN){krFgGqcfOw = true;}
      while(lekxmqxWyu == SwuQKPIcOn){TYVUWYyGcC = true;}
      while(mrNSlUqLKp == mrNSlUqLKp){lhLDSaFirj = true;}
      while(bRCQyjULdN == bRCQyjULdN){HpcgEGwpFH = true;}
      if(ubpkcEYGpi == true){ubpkcEYGpi = false;}
      if(PnRblUYYZk == true){PnRblUYYZk = false;}
      if(goDgOTbUzC == true){goDgOTbUzC = false;}
      if(VlskAKBbph == true){VlskAKBbph = false;}
      if(ujUbZmAZdc == true){ujUbZmAZdc = false;}
      if(LulrfGYJWI == true){LulrfGYJWI = false;}
      if(bDGnMdufbb == true){bDGnMdufbb = false;}
      if(TwiqowTaGa == true){TwiqowTaGa = false;}
      if(TCpWqazAEs == true){TCpWqazAEs = false;}
      if(krFgGqcfOw == true){krFgGqcfOw = false;}
      if(rTxCIOLtDj == true){rTxCIOLtDj = false;}
      if(lyCwoYMjxl == true){lyCwoYMjxl = false;}
      if(duaipbqCkx == true){duaipbqCkx = false;}
      if(TnMKhzEnNb == true){TnMKhzEnNb = false;}
      if(OFwUGmoIqg == true){OFwUGmoIqg = false;}
      if(esicSxrNLg == true){esicSxrNLg = false;}
      if(XIJFPylrOp == true){XIJFPylrOp = false;}
      if(TYVUWYyGcC == true){TYVUWYyGcC = false;}
      if(lhLDSaFirj == true){lhLDSaFirj = false;}
      if(HpcgEGwpFH == true){HpcgEGwpFH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHVWMFXXGN
{ 
  void fMZFMAzTVV()
  { 
      bool eseCqoaQgs = false;
      bool EdVVjRtjVO = false;
      bool QUKGlbUmIr = false;
      bool CObObXykAm = false;
      bool fWSPgbmPHl = false;
      bool XSbCyJhXPO = false;
      bool TnIoppBGtL = false;
      bool SIihisBuZJ = false;
      bool oFeWUjlZQR = false;
      bool oaUkTrNdZp = false;
      bool afVuSOjsSE = false;
      bool ImxFZOIkTF = false;
      bool EapcVrnxOp = false;
      bool fXUjiIiiDG = false;
      bool ArGMJCcOLE = false;
      bool icJTkzpsZa = false;
      bool ZldcYjRNWR = false;
      bool eYhNFLTcTT = false;
      bool OZlKHDOByi = false;
      bool RpJbfNOdnY = false;
      string lPILAaTNbq;
      string bQKBiWRNGd;
      string PILpjxfASR;
      string VOkCRPFuRQ;
      string lXAUyFNdCu;
      string TJlPcdDSaD;
      string uTtJUNeIiS;
      string QWuprqHqrd;
      string iCxXxMbUZn;
      string MmUOUScpzj;
      string aFtiexNwXk;
      string VMawUrVWMI;
      string kJhuGdBgUY;
      string NRqHDcHOrz;
      string yexnSzMXsb;
      string wGdqzRWycB;
      string ugbyWDUSsq;
      string kHeMJGMscG;
      string QdmrcHmAIl;
      string FIlqDRDyRO;
      if(lPILAaTNbq == aFtiexNwXk){eseCqoaQgs = true;}
      else if(aFtiexNwXk == lPILAaTNbq){afVuSOjsSE = true;}
      if(bQKBiWRNGd == VMawUrVWMI){EdVVjRtjVO = true;}
      else if(VMawUrVWMI == bQKBiWRNGd){ImxFZOIkTF = true;}
      if(PILpjxfASR == kJhuGdBgUY){QUKGlbUmIr = true;}
      else if(kJhuGdBgUY == PILpjxfASR){EapcVrnxOp = true;}
      if(VOkCRPFuRQ == NRqHDcHOrz){CObObXykAm = true;}
      else if(NRqHDcHOrz == VOkCRPFuRQ){fXUjiIiiDG = true;}
      if(lXAUyFNdCu == yexnSzMXsb){fWSPgbmPHl = true;}
      else if(yexnSzMXsb == lXAUyFNdCu){ArGMJCcOLE = true;}
      if(TJlPcdDSaD == wGdqzRWycB){XSbCyJhXPO = true;}
      else if(wGdqzRWycB == TJlPcdDSaD){icJTkzpsZa = true;}
      if(uTtJUNeIiS == ugbyWDUSsq){TnIoppBGtL = true;}
      else if(ugbyWDUSsq == uTtJUNeIiS){ZldcYjRNWR = true;}
      if(QWuprqHqrd == kHeMJGMscG){SIihisBuZJ = true;}
      if(iCxXxMbUZn == QdmrcHmAIl){oFeWUjlZQR = true;}
      if(MmUOUScpzj == FIlqDRDyRO){oaUkTrNdZp = true;}
      while(kHeMJGMscG == QWuprqHqrd){eYhNFLTcTT = true;}
      while(QdmrcHmAIl == QdmrcHmAIl){OZlKHDOByi = true;}
      while(FIlqDRDyRO == FIlqDRDyRO){RpJbfNOdnY = true;}
      if(eseCqoaQgs == true){eseCqoaQgs = false;}
      if(EdVVjRtjVO == true){EdVVjRtjVO = false;}
      if(QUKGlbUmIr == true){QUKGlbUmIr = false;}
      if(CObObXykAm == true){CObObXykAm = false;}
      if(fWSPgbmPHl == true){fWSPgbmPHl = false;}
      if(XSbCyJhXPO == true){XSbCyJhXPO = false;}
      if(TnIoppBGtL == true){TnIoppBGtL = false;}
      if(SIihisBuZJ == true){SIihisBuZJ = false;}
      if(oFeWUjlZQR == true){oFeWUjlZQR = false;}
      if(oaUkTrNdZp == true){oaUkTrNdZp = false;}
      if(afVuSOjsSE == true){afVuSOjsSE = false;}
      if(ImxFZOIkTF == true){ImxFZOIkTF = false;}
      if(EapcVrnxOp == true){EapcVrnxOp = false;}
      if(fXUjiIiiDG == true){fXUjiIiiDG = false;}
      if(ArGMJCcOLE == true){ArGMJCcOLE = false;}
      if(icJTkzpsZa == true){icJTkzpsZa = false;}
      if(ZldcYjRNWR == true){ZldcYjRNWR = false;}
      if(eYhNFLTcTT == true){eYhNFLTcTT = false;}
      if(OZlKHDOByi == true){OZlKHDOByi = false;}
      if(RpJbfNOdnY == true){RpJbfNOdnY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPLKKHIBHF
{ 
  void gVioVsPWNN()
  { 
      bool sScVYJXHqb = false;
      bool wSJXYjDHks = false;
      bool tQVpsIfqOc = false;
      bool NbYPEbXLwu = false;
      bool GBQmshNnEo = false;
      bool mVYtlcxlbP = false;
      bool cgsONTtsTw = false;
      bool MrKplrzixK = false;
      bool urlYprCecb = false;
      bool ekigSZICYY = false;
      bool nTUHctKiHt = false;
      bool cOoQTjtTXV = false;
      bool QOQrRbJdWM = false;
      bool jxJXWbXeww = false;
      bool gTWiyQwRMh = false;
      bool eneDHYCcpB = false;
      bool kgLuJfEQtr = false;
      bool MPXanxrgsA = false;
      bool eqQngwSGQx = false;
      bool YunuLAHbYS = false;
      string AEfBexauat;
      string DUHVEIhEZH;
      string gtlQDPYfJX;
      string nzhfxdlKKl;
      string XywLTJeKLp;
      string SdqhbFSPyO;
      string XtlDFEmaXa;
      string VWtnjhxZwt;
      string kOTSFKIzDr;
      string KWMuNcLsGO;
      string VDlkTuiCys;
      string HrSDdIaTxt;
      string wnWfPzJyZH;
      string WEThXhchyK;
      string aFBKjREJRE;
      string CruLShfFVU;
      string kkcpWDYkfu;
      string frUmTplMwx;
      string uAgUEdJIOo;
      string BWMdYpcKmf;
      if(AEfBexauat == VDlkTuiCys){sScVYJXHqb = true;}
      else if(VDlkTuiCys == AEfBexauat){nTUHctKiHt = true;}
      if(DUHVEIhEZH == HrSDdIaTxt){wSJXYjDHks = true;}
      else if(HrSDdIaTxt == DUHVEIhEZH){cOoQTjtTXV = true;}
      if(gtlQDPYfJX == wnWfPzJyZH){tQVpsIfqOc = true;}
      else if(wnWfPzJyZH == gtlQDPYfJX){QOQrRbJdWM = true;}
      if(nzhfxdlKKl == WEThXhchyK){NbYPEbXLwu = true;}
      else if(WEThXhchyK == nzhfxdlKKl){jxJXWbXeww = true;}
      if(XywLTJeKLp == aFBKjREJRE){GBQmshNnEo = true;}
      else if(aFBKjREJRE == XywLTJeKLp){gTWiyQwRMh = true;}
      if(SdqhbFSPyO == CruLShfFVU){mVYtlcxlbP = true;}
      else if(CruLShfFVU == SdqhbFSPyO){eneDHYCcpB = true;}
      if(XtlDFEmaXa == kkcpWDYkfu){cgsONTtsTw = true;}
      else if(kkcpWDYkfu == XtlDFEmaXa){kgLuJfEQtr = true;}
      if(VWtnjhxZwt == frUmTplMwx){MrKplrzixK = true;}
      if(kOTSFKIzDr == uAgUEdJIOo){urlYprCecb = true;}
      if(KWMuNcLsGO == BWMdYpcKmf){ekigSZICYY = true;}
      while(frUmTplMwx == VWtnjhxZwt){MPXanxrgsA = true;}
      while(uAgUEdJIOo == uAgUEdJIOo){eqQngwSGQx = true;}
      while(BWMdYpcKmf == BWMdYpcKmf){YunuLAHbYS = true;}
      if(sScVYJXHqb == true){sScVYJXHqb = false;}
      if(wSJXYjDHks == true){wSJXYjDHks = false;}
      if(tQVpsIfqOc == true){tQVpsIfqOc = false;}
      if(NbYPEbXLwu == true){NbYPEbXLwu = false;}
      if(GBQmshNnEo == true){GBQmshNnEo = false;}
      if(mVYtlcxlbP == true){mVYtlcxlbP = false;}
      if(cgsONTtsTw == true){cgsONTtsTw = false;}
      if(MrKplrzixK == true){MrKplrzixK = false;}
      if(urlYprCecb == true){urlYprCecb = false;}
      if(ekigSZICYY == true){ekigSZICYY = false;}
      if(nTUHctKiHt == true){nTUHctKiHt = false;}
      if(cOoQTjtTXV == true){cOoQTjtTXV = false;}
      if(QOQrRbJdWM == true){QOQrRbJdWM = false;}
      if(jxJXWbXeww == true){jxJXWbXeww = false;}
      if(gTWiyQwRMh == true){gTWiyQwRMh = false;}
      if(eneDHYCcpB == true){eneDHYCcpB = false;}
      if(kgLuJfEQtr == true){kgLuJfEQtr = false;}
      if(MPXanxrgsA == true){MPXanxrgsA = false;}
      if(eqQngwSGQx == true){eqQngwSGQx = false;}
      if(YunuLAHbYS == true){YunuLAHbYS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LAZGJEOAVK
{ 
  void zDWHUdAXIs()
  { 
      bool LSCzJyZawy = false;
      bool xqWhmKEJoA = false;
      bool XrPByLXkEn = false;
      bool aCsIHUNaWu = false;
      bool mBgaoDclWR = false;
      bool AIiaHSDBBx = false;
      bool ZnWHWuyOZR = false;
      bool xdmtNWLnMt = false;
      bool hlOmmRTSAo = false;
      bool RLYYUydYEs = false;
      bool FOLETWVoNk = false;
      bool HOoHPmZjUE = false;
      bool beNkAkFOYO = false;
      bool rljSoTZJSQ = false;
      bool weFPgCWRIg = false;
      bool YtEzRZAaEh = false;
      bool RGPzrUeVRw = false;
      bool NPQEIwZxDx = false;
      bool NmGrpyhjAO = false;
      bool SzFjypOFXL = false;
      string HGhlpkhUtM;
      string ufTSbnEtMa;
      string WsaOXGQyiV;
      string xpbTeDgFeP;
      string nmQkAHYVac;
      string hNoEgNfTOj;
      string UjlXOEDzmX;
      string HzOwmjcpNP;
      string huWFmjBXmR;
      string XMquuDBrVw;
      string EYhCUiyrRx;
      string kpGzCYNfke;
      string DfLVAtHTBi;
      string ijTRKIMUjD;
      string kJFpggGqsV;
      string pUHprXNMBa;
      string bephOAVnns;
      string LrugttZVoT;
      string mQafsNbcYm;
      string uATJbFSXbf;
      if(HGhlpkhUtM == EYhCUiyrRx){LSCzJyZawy = true;}
      else if(EYhCUiyrRx == HGhlpkhUtM){FOLETWVoNk = true;}
      if(ufTSbnEtMa == kpGzCYNfke){xqWhmKEJoA = true;}
      else if(kpGzCYNfke == ufTSbnEtMa){HOoHPmZjUE = true;}
      if(WsaOXGQyiV == DfLVAtHTBi){XrPByLXkEn = true;}
      else if(DfLVAtHTBi == WsaOXGQyiV){beNkAkFOYO = true;}
      if(xpbTeDgFeP == ijTRKIMUjD){aCsIHUNaWu = true;}
      else if(ijTRKIMUjD == xpbTeDgFeP){rljSoTZJSQ = true;}
      if(nmQkAHYVac == kJFpggGqsV){mBgaoDclWR = true;}
      else if(kJFpggGqsV == nmQkAHYVac){weFPgCWRIg = true;}
      if(hNoEgNfTOj == pUHprXNMBa){AIiaHSDBBx = true;}
      else if(pUHprXNMBa == hNoEgNfTOj){YtEzRZAaEh = true;}
      if(UjlXOEDzmX == bephOAVnns){ZnWHWuyOZR = true;}
      else if(bephOAVnns == UjlXOEDzmX){RGPzrUeVRw = true;}
      if(HzOwmjcpNP == LrugttZVoT){xdmtNWLnMt = true;}
      if(huWFmjBXmR == mQafsNbcYm){hlOmmRTSAo = true;}
      if(XMquuDBrVw == uATJbFSXbf){RLYYUydYEs = true;}
      while(LrugttZVoT == HzOwmjcpNP){NPQEIwZxDx = true;}
      while(mQafsNbcYm == mQafsNbcYm){NmGrpyhjAO = true;}
      while(uATJbFSXbf == uATJbFSXbf){SzFjypOFXL = true;}
      if(LSCzJyZawy == true){LSCzJyZawy = false;}
      if(xqWhmKEJoA == true){xqWhmKEJoA = false;}
      if(XrPByLXkEn == true){XrPByLXkEn = false;}
      if(aCsIHUNaWu == true){aCsIHUNaWu = false;}
      if(mBgaoDclWR == true){mBgaoDclWR = false;}
      if(AIiaHSDBBx == true){AIiaHSDBBx = false;}
      if(ZnWHWuyOZR == true){ZnWHWuyOZR = false;}
      if(xdmtNWLnMt == true){xdmtNWLnMt = false;}
      if(hlOmmRTSAo == true){hlOmmRTSAo = false;}
      if(RLYYUydYEs == true){RLYYUydYEs = false;}
      if(FOLETWVoNk == true){FOLETWVoNk = false;}
      if(HOoHPmZjUE == true){HOoHPmZjUE = false;}
      if(beNkAkFOYO == true){beNkAkFOYO = false;}
      if(rljSoTZJSQ == true){rljSoTZJSQ = false;}
      if(weFPgCWRIg == true){weFPgCWRIg = false;}
      if(YtEzRZAaEh == true){YtEzRZAaEh = false;}
      if(RGPzrUeVRw == true){RGPzrUeVRw = false;}
      if(NPQEIwZxDx == true){NPQEIwZxDx = false;}
      if(NmGrpyhjAO == true){NmGrpyhjAO = false;}
      if(SzFjypOFXL == true){SzFjypOFXL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SBXWHEIWYB
{ 
  void ypAHbsySJI()
  { 
      bool XNMYauKRst = false;
      bool KcJXSytJcZ = false;
      bool ArgcnfqWgU = false;
      bool ofDrDkxWJZ = false;
      bool AWjbnQjLUl = false;
      bool NIjgZegiju = false;
      bool DmkYFeZRTh = false;
      bool BXACZdHFnX = false;
      bool ufCuGguVRX = false;
      bool DNlOVMlLVJ = false;
      bool pSqljpHhHw = false;
      bool WatMzXjpRY = false;
      bool iDzwdnklfM = false;
      bool rwiegcoPKQ = false;
      bool YNOVBcSZOy = false;
      bool bwtxZmTuIw = false;
      bool EVBtEaqPeV = false;
      bool iTeAAVnctB = false;
      bool ULWhjuBlFt = false;
      bool JsHOMCLURa = false;
      string GRjLKCMfiS;
      string WPsePOblZI;
      string DXCTVVQEcY;
      string FMKkOeHJLl;
      string mmEIdLyeDo;
      string YQTKehPPpn;
      string kIDKNKEIQj;
      string HRZmUPStpK;
      string XlAmznrAGf;
      string PqTXBdjttS;
      string HoNShGqfoO;
      string OVZeQyIPKY;
      string RDBjUPyClq;
      string eYzWChXhFs;
      string xLKqQsQnGC;
      string VUjVADncyR;
      string IotyjpVDbh;
      string aaKRbGrKTa;
      string zJujVKodVz;
      string ttimjHRMGa;
      if(GRjLKCMfiS == HoNShGqfoO){XNMYauKRst = true;}
      else if(HoNShGqfoO == GRjLKCMfiS){pSqljpHhHw = true;}
      if(WPsePOblZI == OVZeQyIPKY){KcJXSytJcZ = true;}
      else if(OVZeQyIPKY == WPsePOblZI){WatMzXjpRY = true;}
      if(DXCTVVQEcY == RDBjUPyClq){ArgcnfqWgU = true;}
      else if(RDBjUPyClq == DXCTVVQEcY){iDzwdnklfM = true;}
      if(FMKkOeHJLl == eYzWChXhFs){ofDrDkxWJZ = true;}
      else if(eYzWChXhFs == FMKkOeHJLl){rwiegcoPKQ = true;}
      if(mmEIdLyeDo == xLKqQsQnGC){AWjbnQjLUl = true;}
      else if(xLKqQsQnGC == mmEIdLyeDo){YNOVBcSZOy = true;}
      if(YQTKehPPpn == VUjVADncyR){NIjgZegiju = true;}
      else if(VUjVADncyR == YQTKehPPpn){bwtxZmTuIw = true;}
      if(kIDKNKEIQj == IotyjpVDbh){DmkYFeZRTh = true;}
      else if(IotyjpVDbh == kIDKNKEIQj){EVBtEaqPeV = true;}
      if(HRZmUPStpK == aaKRbGrKTa){BXACZdHFnX = true;}
      if(XlAmznrAGf == zJujVKodVz){ufCuGguVRX = true;}
      if(PqTXBdjttS == ttimjHRMGa){DNlOVMlLVJ = true;}
      while(aaKRbGrKTa == HRZmUPStpK){iTeAAVnctB = true;}
      while(zJujVKodVz == zJujVKodVz){ULWhjuBlFt = true;}
      while(ttimjHRMGa == ttimjHRMGa){JsHOMCLURa = true;}
      if(XNMYauKRst == true){XNMYauKRst = false;}
      if(KcJXSytJcZ == true){KcJXSytJcZ = false;}
      if(ArgcnfqWgU == true){ArgcnfqWgU = false;}
      if(ofDrDkxWJZ == true){ofDrDkxWJZ = false;}
      if(AWjbnQjLUl == true){AWjbnQjLUl = false;}
      if(NIjgZegiju == true){NIjgZegiju = false;}
      if(DmkYFeZRTh == true){DmkYFeZRTh = false;}
      if(BXACZdHFnX == true){BXACZdHFnX = false;}
      if(ufCuGguVRX == true){ufCuGguVRX = false;}
      if(DNlOVMlLVJ == true){DNlOVMlLVJ = false;}
      if(pSqljpHhHw == true){pSqljpHhHw = false;}
      if(WatMzXjpRY == true){WatMzXjpRY = false;}
      if(iDzwdnklfM == true){iDzwdnklfM = false;}
      if(rwiegcoPKQ == true){rwiegcoPKQ = false;}
      if(YNOVBcSZOy == true){YNOVBcSZOy = false;}
      if(bwtxZmTuIw == true){bwtxZmTuIw = false;}
      if(EVBtEaqPeV == true){EVBtEaqPeV = false;}
      if(iTeAAVnctB == true){iTeAAVnctB = false;}
      if(ULWhjuBlFt == true){ULWhjuBlFt = false;}
      if(JsHOMCLURa == true){JsHOMCLURa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBBZGSMAXK
{ 
  void BgMViPweNL()
  { 
      bool euFXNJRlcn = false;
      bool pweCahjwju = false;
      bool LmJBHHFhSn = false;
      bool JQgGoODrpc = false;
      bool tdIrRHFWqu = false;
      bool YKsbarkDPF = false;
      bool DjTneZOXNL = false;
      bool erFGAheQiz = false;
      bool CiqWOzWEex = false;
      bool czcjZKKTNr = false;
      bool rgIePgFmas = false;
      bool MUTPDTrwZf = false;
      bool DKsPifPUgp = false;
      bool XKDqGUaLHg = false;
      bool sjcljIeMgF = false;
      bool RNsgnhnrwi = false;
      bool RjGkVCQcIh = false;
      bool sgorlTgGfZ = false;
      bool ACnaXJQVCY = false;
      bool ghPXPJcrQh = false;
      string YfWWjNKNsf;
      string hkJOeSnFPY;
      string DzzeudWtbr;
      string LsqFPTGuFy;
      string fFBDQXogEr;
      string HAbqlYfqbF;
      string qQkBTnsDzK;
      string LrzRryyuOW;
      string opoijLRzTp;
      string mPTzGPTzjb;
      string dkgsgPAKzm;
      string ajcEQAaBQI;
      string WsjIWwXzKb;
      string eyLlsEIuCU;
      string KGAfPDlPiF;
      string oRhaEjAXWj;
      string qAAWIbXqKL;
      string rezwyQsEsT;
      string JIPEmMPkgI;
      string DjYRdJGcXm;
      if(YfWWjNKNsf == dkgsgPAKzm){euFXNJRlcn = true;}
      else if(dkgsgPAKzm == YfWWjNKNsf){rgIePgFmas = true;}
      if(hkJOeSnFPY == ajcEQAaBQI){pweCahjwju = true;}
      else if(ajcEQAaBQI == hkJOeSnFPY){MUTPDTrwZf = true;}
      if(DzzeudWtbr == WsjIWwXzKb){LmJBHHFhSn = true;}
      else if(WsjIWwXzKb == DzzeudWtbr){DKsPifPUgp = true;}
      if(LsqFPTGuFy == eyLlsEIuCU){JQgGoODrpc = true;}
      else if(eyLlsEIuCU == LsqFPTGuFy){XKDqGUaLHg = true;}
      if(fFBDQXogEr == KGAfPDlPiF){tdIrRHFWqu = true;}
      else if(KGAfPDlPiF == fFBDQXogEr){sjcljIeMgF = true;}
      if(HAbqlYfqbF == oRhaEjAXWj){YKsbarkDPF = true;}
      else if(oRhaEjAXWj == HAbqlYfqbF){RNsgnhnrwi = true;}
      if(qQkBTnsDzK == qAAWIbXqKL){DjTneZOXNL = true;}
      else if(qAAWIbXqKL == qQkBTnsDzK){RjGkVCQcIh = true;}
      if(LrzRryyuOW == rezwyQsEsT){erFGAheQiz = true;}
      if(opoijLRzTp == JIPEmMPkgI){CiqWOzWEex = true;}
      if(mPTzGPTzjb == DjYRdJGcXm){czcjZKKTNr = true;}
      while(rezwyQsEsT == LrzRryyuOW){sgorlTgGfZ = true;}
      while(JIPEmMPkgI == JIPEmMPkgI){ACnaXJQVCY = true;}
      while(DjYRdJGcXm == DjYRdJGcXm){ghPXPJcrQh = true;}
      if(euFXNJRlcn == true){euFXNJRlcn = false;}
      if(pweCahjwju == true){pweCahjwju = false;}
      if(LmJBHHFhSn == true){LmJBHHFhSn = false;}
      if(JQgGoODrpc == true){JQgGoODrpc = false;}
      if(tdIrRHFWqu == true){tdIrRHFWqu = false;}
      if(YKsbarkDPF == true){YKsbarkDPF = false;}
      if(DjTneZOXNL == true){DjTneZOXNL = false;}
      if(erFGAheQiz == true){erFGAheQiz = false;}
      if(CiqWOzWEex == true){CiqWOzWEex = false;}
      if(czcjZKKTNr == true){czcjZKKTNr = false;}
      if(rgIePgFmas == true){rgIePgFmas = false;}
      if(MUTPDTrwZf == true){MUTPDTrwZf = false;}
      if(DKsPifPUgp == true){DKsPifPUgp = false;}
      if(XKDqGUaLHg == true){XKDqGUaLHg = false;}
      if(sjcljIeMgF == true){sjcljIeMgF = false;}
      if(RNsgnhnrwi == true){RNsgnhnrwi = false;}
      if(RjGkVCQcIh == true){RjGkVCQcIh = false;}
      if(sgorlTgGfZ == true){sgorlTgGfZ = false;}
      if(ACnaXJQVCY == true){ACnaXJQVCY = false;}
      if(ghPXPJcrQh == true){ghPXPJcrQh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRKOISNPUR
{ 
  void HVaVueoVlk()
  { 
      bool TFQhNbILOc = false;
      bool SOgYxeHuuO = false;
      bool almZoNaIHC = false;
      bool QzCsYfLieB = false;
      bool HZWdLEhQpT = false;
      bool iSqStgRqsA = false;
      bool AAEMLSMnzR = false;
      bool SXPtGBPINk = false;
      bool fKSnSyIizq = false;
      bool NUpeBHUKRr = false;
      bool qsQYALCxLr = false;
      bool RIcHTohQsM = false;
      bool KcoHDygksz = false;
      bool fFqUsmtsmH = false;
      bool wLWGZEqiKL = false;
      bool ZEQFhNEIUC = false;
      bool dQDMMMRIOg = false;
      bool unclQzGihz = false;
      bool GyagZankme = false;
      bool hlXkdfHKsN = false;
      string CdKWDahJGM;
      string TnSzuOrZfZ;
      string aysyuQmFBc;
      string DMjIDxUjBR;
      string pfLcuIElyM;
      string OElcuEjLal;
      string mcHcJGEJux;
      string sHXNitlPCm;
      string MAGoOyaGNz;
      string MIJPdNYhTn;
      string DuqBSGgYtA;
      string RUInZmVSOK;
      string fywujkyHjU;
      string VEuOiRJFVH;
      string QBLMhrzUpq;
      string rFSJHEyuQh;
      string IZnYeMYtEH;
      string cPwGteljNr;
      string kcRscQllGd;
      string SOomzqNmgU;
      if(CdKWDahJGM == DuqBSGgYtA){TFQhNbILOc = true;}
      else if(DuqBSGgYtA == CdKWDahJGM){qsQYALCxLr = true;}
      if(TnSzuOrZfZ == RUInZmVSOK){SOgYxeHuuO = true;}
      else if(RUInZmVSOK == TnSzuOrZfZ){RIcHTohQsM = true;}
      if(aysyuQmFBc == fywujkyHjU){almZoNaIHC = true;}
      else if(fywujkyHjU == aysyuQmFBc){KcoHDygksz = true;}
      if(DMjIDxUjBR == VEuOiRJFVH){QzCsYfLieB = true;}
      else if(VEuOiRJFVH == DMjIDxUjBR){fFqUsmtsmH = true;}
      if(pfLcuIElyM == QBLMhrzUpq){HZWdLEhQpT = true;}
      else if(QBLMhrzUpq == pfLcuIElyM){wLWGZEqiKL = true;}
      if(OElcuEjLal == rFSJHEyuQh){iSqStgRqsA = true;}
      else if(rFSJHEyuQh == OElcuEjLal){ZEQFhNEIUC = true;}
      if(mcHcJGEJux == IZnYeMYtEH){AAEMLSMnzR = true;}
      else if(IZnYeMYtEH == mcHcJGEJux){dQDMMMRIOg = true;}
      if(sHXNitlPCm == cPwGteljNr){SXPtGBPINk = true;}
      if(MAGoOyaGNz == kcRscQllGd){fKSnSyIizq = true;}
      if(MIJPdNYhTn == SOomzqNmgU){NUpeBHUKRr = true;}
      while(cPwGteljNr == sHXNitlPCm){unclQzGihz = true;}
      while(kcRscQllGd == kcRscQllGd){GyagZankme = true;}
      while(SOomzqNmgU == SOomzqNmgU){hlXkdfHKsN = true;}
      if(TFQhNbILOc == true){TFQhNbILOc = false;}
      if(SOgYxeHuuO == true){SOgYxeHuuO = false;}
      if(almZoNaIHC == true){almZoNaIHC = false;}
      if(QzCsYfLieB == true){QzCsYfLieB = false;}
      if(HZWdLEhQpT == true){HZWdLEhQpT = false;}
      if(iSqStgRqsA == true){iSqStgRqsA = false;}
      if(AAEMLSMnzR == true){AAEMLSMnzR = false;}
      if(SXPtGBPINk == true){SXPtGBPINk = false;}
      if(fKSnSyIizq == true){fKSnSyIizq = false;}
      if(NUpeBHUKRr == true){NUpeBHUKRr = false;}
      if(qsQYALCxLr == true){qsQYALCxLr = false;}
      if(RIcHTohQsM == true){RIcHTohQsM = false;}
      if(KcoHDygksz == true){KcoHDygksz = false;}
      if(fFqUsmtsmH == true){fFqUsmtsmH = false;}
      if(wLWGZEqiKL == true){wLWGZEqiKL = false;}
      if(ZEQFhNEIUC == true){ZEQFhNEIUC = false;}
      if(dQDMMMRIOg == true){dQDMMMRIOg = false;}
      if(unclQzGihz == true){unclQzGihz = false;}
      if(GyagZankme == true){GyagZankme = false;}
      if(hlXkdfHKsN == true){hlXkdfHKsN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBRERLVPWH
{ 
  void zHOUIPhLMG()
  { 
      bool HTDIrbcUHT = false;
      bool jPowzhVThY = false;
      bool QmCGrVrdmD = false;
      bool yNUWTcBqxe = false;
      bool ULiUlInLoQ = false;
      bool IInWzTRxQW = false;
      bool jyhDUVuSbW = false;
      bool gdVDEEEgTj = false;
      bool hfnVupZyWz = false;
      bool KEZauVcezP = false;
      bool MViSjdmjRt = false;
      bool PjcgoDJMIe = false;
      bool uwubLbDuIi = false;
      bool bYhEWLwVlQ = false;
      bool DofcjZbskq = false;
      bool LQWUTPZHGH = false;
      bool ZqbiRpCXKc = false;
      bool HnZqbFQSrl = false;
      bool zKJQWLCMjG = false;
      bool loOdpLNwKs = false;
      string oNWZupLnAu;
      string wjQAKBEIJG;
      string zjDBBDFLpQ;
      string PBEyCDHVmf;
      string LBPCGuhYry;
      string FSVTOEJVXq;
      string kAxieufRxG;
      string shVctyTBuF;
      string VgSqKxfjix;
      string skxuuKDfWK;
      string PPbkEXwrYQ;
      string kIaRVDhGYh;
      string PuizMHjZhj;
      string tnejpFFglm;
      string AmLRMkKeZq;
      string cxHnuTgbYx;
      string mWKoWxcpbQ;
      string yATlgbjQlb;
      string xEApGxfpnV;
      string XcIozdcVuP;
      if(oNWZupLnAu == PPbkEXwrYQ){HTDIrbcUHT = true;}
      else if(PPbkEXwrYQ == oNWZupLnAu){MViSjdmjRt = true;}
      if(wjQAKBEIJG == kIaRVDhGYh){jPowzhVThY = true;}
      else if(kIaRVDhGYh == wjQAKBEIJG){PjcgoDJMIe = true;}
      if(zjDBBDFLpQ == PuizMHjZhj){QmCGrVrdmD = true;}
      else if(PuizMHjZhj == zjDBBDFLpQ){uwubLbDuIi = true;}
      if(PBEyCDHVmf == tnejpFFglm){yNUWTcBqxe = true;}
      else if(tnejpFFglm == PBEyCDHVmf){bYhEWLwVlQ = true;}
      if(LBPCGuhYry == AmLRMkKeZq){ULiUlInLoQ = true;}
      else if(AmLRMkKeZq == LBPCGuhYry){DofcjZbskq = true;}
      if(FSVTOEJVXq == cxHnuTgbYx){IInWzTRxQW = true;}
      else if(cxHnuTgbYx == FSVTOEJVXq){LQWUTPZHGH = true;}
      if(kAxieufRxG == mWKoWxcpbQ){jyhDUVuSbW = true;}
      else if(mWKoWxcpbQ == kAxieufRxG){ZqbiRpCXKc = true;}
      if(shVctyTBuF == yATlgbjQlb){gdVDEEEgTj = true;}
      if(VgSqKxfjix == xEApGxfpnV){hfnVupZyWz = true;}
      if(skxuuKDfWK == XcIozdcVuP){KEZauVcezP = true;}
      while(yATlgbjQlb == shVctyTBuF){HnZqbFQSrl = true;}
      while(xEApGxfpnV == xEApGxfpnV){zKJQWLCMjG = true;}
      while(XcIozdcVuP == XcIozdcVuP){loOdpLNwKs = true;}
      if(HTDIrbcUHT == true){HTDIrbcUHT = false;}
      if(jPowzhVThY == true){jPowzhVThY = false;}
      if(QmCGrVrdmD == true){QmCGrVrdmD = false;}
      if(yNUWTcBqxe == true){yNUWTcBqxe = false;}
      if(ULiUlInLoQ == true){ULiUlInLoQ = false;}
      if(IInWzTRxQW == true){IInWzTRxQW = false;}
      if(jyhDUVuSbW == true){jyhDUVuSbW = false;}
      if(gdVDEEEgTj == true){gdVDEEEgTj = false;}
      if(hfnVupZyWz == true){hfnVupZyWz = false;}
      if(KEZauVcezP == true){KEZauVcezP = false;}
      if(MViSjdmjRt == true){MViSjdmjRt = false;}
      if(PjcgoDJMIe == true){PjcgoDJMIe = false;}
      if(uwubLbDuIi == true){uwubLbDuIi = false;}
      if(bYhEWLwVlQ == true){bYhEWLwVlQ = false;}
      if(DofcjZbskq == true){DofcjZbskq = false;}
      if(LQWUTPZHGH == true){LQWUTPZHGH = false;}
      if(ZqbiRpCXKc == true){ZqbiRpCXKc = false;}
      if(HnZqbFQSrl == true){HnZqbFQSrl = false;}
      if(zKJQWLCMjG == true){zKJQWLCMjG = false;}
      if(loOdpLNwKs == true){loOdpLNwKs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LORXEUXXXD
{ 
  void ESozdACVnj()
  { 
      bool nQAijsLgFL = false;
      bool FbEsWsCkCH = false;
      bool LVQbnbMira = false;
      bool iQCwnWcaJD = false;
      bool SqJGNlTxZT = false;
      bool gbXBxSzXuI = false;
      bool gbnecnYHEA = false;
      bool PbazoTLJOC = false;
      bool HOJYsHsAzV = false;
      bool WFfBWpDedZ = false;
      bool MMsZDFAXMc = false;
      bool GpIrARSOlU = false;
      bool tXIicKwYcy = false;
      bool QgfoouViVm = false;
      bool HVnWOgwmAE = false;
      bool XnsJenDJwr = false;
      bool JatOLZJTCF = false;
      bool wisyNXjkUw = false;
      bool NJYXZbmWJB = false;
      bool qLmcdfaYKn = false;
      string JRqPxUzwVQ;
      string yFYHBnWXxY;
      string jduJbyqyAC;
      string AJUPTKqsmy;
      string PdrplyCxNt;
      string YsIBNfVhny;
      string dBuSQojInp;
      string wdjzIFkFXc;
      string usjFdGBSCn;
      string oJFnUOhZZw;
      string NtJWxuIJsH;
      string uPKKDjQpnJ;
      string nQGzBmXudt;
      string WKfaPBiMIi;
      string yqZtsYzukj;
      string xrlQIwnKVK;
      string WNezkjjiuB;
      string ADgFLwqLFc;
      string mcKswdYOSS;
      string NYqxMjMZII;
      if(JRqPxUzwVQ == NtJWxuIJsH){nQAijsLgFL = true;}
      else if(NtJWxuIJsH == JRqPxUzwVQ){MMsZDFAXMc = true;}
      if(yFYHBnWXxY == uPKKDjQpnJ){FbEsWsCkCH = true;}
      else if(uPKKDjQpnJ == yFYHBnWXxY){GpIrARSOlU = true;}
      if(jduJbyqyAC == nQGzBmXudt){LVQbnbMira = true;}
      else if(nQGzBmXudt == jduJbyqyAC){tXIicKwYcy = true;}
      if(AJUPTKqsmy == WKfaPBiMIi){iQCwnWcaJD = true;}
      else if(WKfaPBiMIi == AJUPTKqsmy){QgfoouViVm = true;}
      if(PdrplyCxNt == yqZtsYzukj){SqJGNlTxZT = true;}
      else if(yqZtsYzukj == PdrplyCxNt){HVnWOgwmAE = true;}
      if(YsIBNfVhny == xrlQIwnKVK){gbXBxSzXuI = true;}
      else if(xrlQIwnKVK == YsIBNfVhny){XnsJenDJwr = true;}
      if(dBuSQojInp == WNezkjjiuB){gbnecnYHEA = true;}
      else if(WNezkjjiuB == dBuSQojInp){JatOLZJTCF = true;}
      if(wdjzIFkFXc == ADgFLwqLFc){PbazoTLJOC = true;}
      if(usjFdGBSCn == mcKswdYOSS){HOJYsHsAzV = true;}
      if(oJFnUOhZZw == NYqxMjMZII){WFfBWpDedZ = true;}
      while(ADgFLwqLFc == wdjzIFkFXc){wisyNXjkUw = true;}
      while(mcKswdYOSS == mcKswdYOSS){NJYXZbmWJB = true;}
      while(NYqxMjMZII == NYqxMjMZII){qLmcdfaYKn = true;}
      if(nQAijsLgFL == true){nQAijsLgFL = false;}
      if(FbEsWsCkCH == true){FbEsWsCkCH = false;}
      if(LVQbnbMira == true){LVQbnbMira = false;}
      if(iQCwnWcaJD == true){iQCwnWcaJD = false;}
      if(SqJGNlTxZT == true){SqJGNlTxZT = false;}
      if(gbXBxSzXuI == true){gbXBxSzXuI = false;}
      if(gbnecnYHEA == true){gbnecnYHEA = false;}
      if(PbazoTLJOC == true){PbazoTLJOC = false;}
      if(HOJYsHsAzV == true){HOJYsHsAzV = false;}
      if(WFfBWpDedZ == true){WFfBWpDedZ = false;}
      if(MMsZDFAXMc == true){MMsZDFAXMc = false;}
      if(GpIrARSOlU == true){GpIrARSOlU = false;}
      if(tXIicKwYcy == true){tXIicKwYcy = false;}
      if(QgfoouViVm == true){QgfoouViVm = false;}
      if(HVnWOgwmAE == true){HVnWOgwmAE = false;}
      if(XnsJenDJwr == true){XnsJenDJwr = false;}
      if(JatOLZJTCF == true){JatOLZJTCF = false;}
      if(wisyNXjkUw == true){wisyNXjkUw = false;}
      if(NJYXZbmWJB == true){NJYXZbmWJB = false;}
      if(qLmcdfaYKn == true){qLmcdfaYKn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAISPSUFDH
{ 
  void kHDujyuDXq()
  { 
      bool xThTuCDLIO = false;
      bool lBPTRBcruu = false;
      bool tRgAStsAqr = false;
      bool wsUaNirUqf = false;
      bool CErZxwgdjJ = false;
      bool rNZrtelhAA = false;
      bool IDUQSrfnGi = false;
      bool IHAProZHDV = false;
      bool NPPgAhTbgh = false;
      bool wKTpWzjaGE = false;
      bool PsWBAjMKAE = false;
      bool FddemrnnQj = false;
      bool YDGXlymKrs = false;
      bool EyAzFTsNfP = false;
      bool UIbbcSfoDd = false;
      bool KwKWeMlyPC = false;
      bool wCRGzGdeYS = false;
      bool zZHAPQaeuT = false;
      bool RyGOiImdTs = false;
      bool htydTSpVbV = false;
      string QekucAdQNj;
      string BQVRaVlkVJ;
      string gpuucjOZHM;
      string EXAOOqJFCq;
      string SnFBieQupY;
      string CZiwIZjpSr;
      string lEIAecQGCi;
      string LfiepsjsMy;
      string TTiiKeoDGo;
      string HTmJFOeEWF;
      string NKrGMVqEFP;
      string ppcTYSUYpA;
      string nMzNbrsYYb;
      string NeWGjIacWn;
      string mkypyQpSjm;
      string tGOVRAKdeT;
      string cRecCKTWjQ;
      string qqCCMCOJOK;
      string CaolhGQBoi;
      string xwxCLUGUnn;
      if(QekucAdQNj == NKrGMVqEFP){xThTuCDLIO = true;}
      else if(NKrGMVqEFP == QekucAdQNj){PsWBAjMKAE = true;}
      if(BQVRaVlkVJ == ppcTYSUYpA){lBPTRBcruu = true;}
      else if(ppcTYSUYpA == BQVRaVlkVJ){FddemrnnQj = true;}
      if(gpuucjOZHM == nMzNbrsYYb){tRgAStsAqr = true;}
      else if(nMzNbrsYYb == gpuucjOZHM){YDGXlymKrs = true;}
      if(EXAOOqJFCq == NeWGjIacWn){wsUaNirUqf = true;}
      else if(NeWGjIacWn == EXAOOqJFCq){EyAzFTsNfP = true;}
      if(SnFBieQupY == mkypyQpSjm){CErZxwgdjJ = true;}
      else if(mkypyQpSjm == SnFBieQupY){UIbbcSfoDd = true;}
      if(CZiwIZjpSr == tGOVRAKdeT){rNZrtelhAA = true;}
      else if(tGOVRAKdeT == CZiwIZjpSr){KwKWeMlyPC = true;}
      if(lEIAecQGCi == cRecCKTWjQ){IDUQSrfnGi = true;}
      else if(cRecCKTWjQ == lEIAecQGCi){wCRGzGdeYS = true;}
      if(LfiepsjsMy == qqCCMCOJOK){IHAProZHDV = true;}
      if(TTiiKeoDGo == CaolhGQBoi){NPPgAhTbgh = true;}
      if(HTmJFOeEWF == xwxCLUGUnn){wKTpWzjaGE = true;}
      while(qqCCMCOJOK == LfiepsjsMy){zZHAPQaeuT = true;}
      while(CaolhGQBoi == CaolhGQBoi){RyGOiImdTs = true;}
      while(xwxCLUGUnn == xwxCLUGUnn){htydTSpVbV = true;}
      if(xThTuCDLIO == true){xThTuCDLIO = false;}
      if(lBPTRBcruu == true){lBPTRBcruu = false;}
      if(tRgAStsAqr == true){tRgAStsAqr = false;}
      if(wsUaNirUqf == true){wsUaNirUqf = false;}
      if(CErZxwgdjJ == true){CErZxwgdjJ = false;}
      if(rNZrtelhAA == true){rNZrtelhAA = false;}
      if(IDUQSrfnGi == true){IDUQSrfnGi = false;}
      if(IHAProZHDV == true){IHAProZHDV = false;}
      if(NPPgAhTbgh == true){NPPgAhTbgh = false;}
      if(wKTpWzjaGE == true){wKTpWzjaGE = false;}
      if(PsWBAjMKAE == true){PsWBAjMKAE = false;}
      if(FddemrnnQj == true){FddemrnnQj = false;}
      if(YDGXlymKrs == true){YDGXlymKrs = false;}
      if(EyAzFTsNfP == true){EyAzFTsNfP = false;}
      if(UIbbcSfoDd == true){UIbbcSfoDd = false;}
      if(KwKWeMlyPC == true){KwKWeMlyPC = false;}
      if(wCRGzGdeYS == true){wCRGzGdeYS = false;}
      if(zZHAPQaeuT == true){zZHAPQaeuT = false;}
      if(RyGOiImdTs == true){RyGOiImdTs = false;}
      if(htydTSpVbV == true){htydTSpVbV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHWTHYDJXP
{ 
  void rmzNxcAUrs()
  { 
      bool KhCQyWJiYY = false;
      bool xjcTQAHXUs = false;
      bool kbcNVSmGzI = false;
      bool qKFxsCilDZ = false;
      bool RVRMhaBYzU = false;
      bool MDEVhiEntf = false;
      bool iCiPgmeeaO = false;
      bool QUTuaPJQfu = false;
      bool QNHewmFiOJ = false;
      bool xuqXpPlCeu = false;
      bool uWykDqjItR = false;
      bool ZnIzPVtDTt = false;
      bool guPRQVcwEL = false;
      bool cHkjztPWbE = false;
      bool DxnxjJlrIU = false;
      bool UhhkOAGfTg = false;
      bool NnEioRCXzU = false;
      bool GXbOpjHSgG = false;
      bool jkmjpuYzVz = false;
      bool miCtpOrFHR = false;
      string XlbhgNcCpB;
      string IMtkmpIPtb;
      string wgRuJIzFIh;
      string ANcYALUYSe;
      string ZQoMGqgFgG;
      string EImTJqTfXX;
      string OWsHAtjVka;
      string ViwOCfqFnS;
      string bsYCdrZIOJ;
      string rnAtQCWhLL;
      string HLUGjUMYRd;
      string zNqEwUypdI;
      string UaGahhhByA;
      string IJtcLPXRSI;
      string eBqkJdwwxu;
      string DgECqfFtXC;
      string mKZRUpTOsg;
      string wgXUcSiUQD;
      string klDCwbEqke;
      string KdsQUTaYPT;
      if(XlbhgNcCpB == HLUGjUMYRd){KhCQyWJiYY = true;}
      else if(HLUGjUMYRd == XlbhgNcCpB){uWykDqjItR = true;}
      if(IMtkmpIPtb == zNqEwUypdI){xjcTQAHXUs = true;}
      else if(zNqEwUypdI == IMtkmpIPtb){ZnIzPVtDTt = true;}
      if(wgRuJIzFIh == UaGahhhByA){kbcNVSmGzI = true;}
      else if(UaGahhhByA == wgRuJIzFIh){guPRQVcwEL = true;}
      if(ANcYALUYSe == IJtcLPXRSI){qKFxsCilDZ = true;}
      else if(IJtcLPXRSI == ANcYALUYSe){cHkjztPWbE = true;}
      if(ZQoMGqgFgG == eBqkJdwwxu){RVRMhaBYzU = true;}
      else if(eBqkJdwwxu == ZQoMGqgFgG){DxnxjJlrIU = true;}
      if(EImTJqTfXX == DgECqfFtXC){MDEVhiEntf = true;}
      else if(DgECqfFtXC == EImTJqTfXX){UhhkOAGfTg = true;}
      if(OWsHAtjVka == mKZRUpTOsg){iCiPgmeeaO = true;}
      else if(mKZRUpTOsg == OWsHAtjVka){NnEioRCXzU = true;}
      if(ViwOCfqFnS == wgXUcSiUQD){QUTuaPJQfu = true;}
      if(bsYCdrZIOJ == klDCwbEqke){QNHewmFiOJ = true;}
      if(rnAtQCWhLL == KdsQUTaYPT){xuqXpPlCeu = true;}
      while(wgXUcSiUQD == ViwOCfqFnS){GXbOpjHSgG = true;}
      while(klDCwbEqke == klDCwbEqke){jkmjpuYzVz = true;}
      while(KdsQUTaYPT == KdsQUTaYPT){miCtpOrFHR = true;}
      if(KhCQyWJiYY == true){KhCQyWJiYY = false;}
      if(xjcTQAHXUs == true){xjcTQAHXUs = false;}
      if(kbcNVSmGzI == true){kbcNVSmGzI = false;}
      if(qKFxsCilDZ == true){qKFxsCilDZ = false;}
      if(RVRMhaBYzU == true){RVRMhaBYzU = false;}
      if(MDEVhiEntf == true){MDEVhiEntf = false;}
      if(iCiPgmeeaO == true){iCiPgmeeaO = false;}
      if(QUTuaPJQfu == true){QUTuaPJQfu = false;}
      if(QNHewmFiOJ == true){QNHewmFiOJ = false;}
      if(xuqXpPlCeu == true){xuqXpPlCeu = false;}
      if(uWykDqjItR == true){uWykDqjItR = false;}
      if(ZnIzPVtDTt == true){ZnIzPVtDTt = false;}
      if(guPRQVcwEL == true){guPRQVcwEL = false;}
      if(cHkjztPWbE == true){cHkjztPWbE = false;}
      if(DxnxjJlrIU == true){DxnxjJlrIU = false;}
      if(UhhkOAGfTg == true){UhhkOAGfTg = false;}
      if(NnEioRCXzU == true){NnEioRCXzU = false;}
      if(GXbOpjHSgG == true){GXbOpjHSgG = false;}
      if(jkmjpuYzVz == true){jkmjpuYzVz = false;}
      if(miCtpOrFHR == true){miCtpOrFHR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWPSGAZWIC
{ 
  void RQalWtFMEN()
  { 
      bool WcJSygHjHH = false;
      bool KTYqrFeSBc = false;
      bool qhOPbCXDgP = false;
      bool ompxeYhaon = false;
      bool DmmqTgNhEY = false;
      bool ERfgQoOtqu = false;
      bool JDDqRWcaLT = false;
      bool XEdNYDuWwt = false;
      bool opyHLWHJgp = false;
      bool KnisezjuZw = false;
      bool DlVkBznRIM = false;
      bool srxxFSFwfu = false;
      bool PTtVIjVkhY = false;
      bool TAxAqDUMGL = false;
      bool ioBTxSplmL = false;
      bool tnOdfjrAcQ = false;
      bool dDiisruwGC = false;
      bool yrpUMZSaYp = false;
      bool tjxWeflSTG = false;
      bool LTjogeFRZE = false;
      string xaIpxCXRjH;
      string VsjmRthNsQ;
      string pGYdWLVsuW;
      string XbrfAiPceY;
      string WWzCuHWweQ;
      string zyBPaqCdTk;
      string fdWMjsBEmi;
      string dFiTsTGViP;
      string nZOdXZZbFI;
      string fkIsssAlSB;
      string FSJwmtPhWH;
      string jfuExFProK;
      string SZydCrwoaz;
      string SUDgJUQSqc;
      string JrEyXApEum;
      string dHwIhfUest;
      string xZGWnPcNtb;
      string owALAaUAGC;
      string BrtmVLXtzd;
      string AlYxejkgJI;
      if(xaIpxCXRjH == FSJwmtPhWH){WcJSygHjHH = true;}
      else if(FSJwmtPhWH == xaIpxCXRjH){DlVkBznRIM = true;}
      if(VsjmRthNsQ == jfuExFProK){KTYqrFeSBc = true;}
      else if(jfuExFProK == VsjmRthNsQ){srxxFSFwfu = true;}
      if(pGYdWLVsuW == SZydCrwoaz){qhOPbCXDgP = true;}
      else if(SZydCrwoaz == pGYdWLVsuW){PTtVIjVkhY = true;}
      if(XbrfAiPceY == SUDgJUQSqc){ompxeYhaon = true;}
      else if(SUDgJUQSqc == XbrfAiPceY){TAxAqDUMGL = true;}
      if(WWzCuHWweQ == JrEyXApEum){DmmqTgNhEY = true;}
      else if(JrEyXApEum == WWzCuHWweQ){ioBTxSplmL = true;}
      if(zyBPaqCdTk == dHwIhfUest){ERfgQoOtqu = true;}
      else if(dHwIhfUest == zyBPaqCdTk){tnOdfjrAcQ = true;}
      if(fdWMjsBEmi == xZGWnPcNtb){JDDqRWcaLT = true;}
      else if(xZGWnPcNtb == fdWMjsBEmi){dDiisruwGC = true;}
      if(dFiTsTGViP == owALAaUAGC){XEdNYDuWwt = true;}
      if(nZOdXZZbFI == BrtmVLXtzd){opyHLWHJgp = true;}
      if(fkIsssAlSB == AlYxejkgJI){KnisezjuZw = true;}
      while(owALAaUAGC == dFiTsTGViP){yrpUMZSaYp = true;}
      while(BrtmVLXtzd == BrtmVLXtzd){tjxWeflSTG = true;}
      while(AlYxejkgJI == AlYxejkgJI){LTjogeFRZE = true;}
      if(WcJSygHjHH == true){WcJSygHjHH = false;}
      if(KTYqrFeSBc == true){KTYqrFeSBc = false;}
      if(qhOPbCXDgP == true){qhOPbCXDgP = false;}
      if(ompxeYhaon == true){ompxeYhaon = false;}
      if(DmmqTgNhEY == true){DmmqTgNhEY = false;}
      if(ERfgQoOtqu == true){ERfgQoOtqu = false;}
      if(JDDqRWcaLT == true){JDDqRWcaLT = false;}
      if(XEdNYDuWwt == true){XEdNYDuWwt = false;}
      if(opyHLWHJgp == true){opyHLWHJgp = false;}
      if(KnisezjuZw == true){KnisezjuZw = false;}
      if(DlVkBznRIM == true){DlVkBznRIM = false;}
      if(srxxFSFwfu == true){srxxFSFwfu = false;}
      if(PTtVIjVkhY == true){PTtVIjVkhY = false;}
      if(TAxAqDUMGL == true){TAxAqDUMGL = false;}
      if(ioBTxSplmL == true){ioBTxSplmL = false;}
      if(tnOdfjrAcQ == true){tnOdfjrAcQ = false;}
      if(dDiisruwGC == true){dDiisruwGC = false;}
      if(yrpUMZSaYp == true){yrpUMZSaYp = false;}
      if(tjxWeflSTG == true){tjxWeflSTG = false;}
      if(LTjogeFRZE == true){LTjogeFRZE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLVXLYEOIX
{ 
  void TnpCuSMmho()
  { 
      bool AUlMWlMtYe = false;
      bool VWYynYLxcU = false;
      bool yAHdOYBheV = false;
      bool tOXJktGgja = false;
      bool EUhPBjhDCf = false;
      bool XwHBazMIxy = false;
      bool keOCkGyONs = false;
      bool ReMBPdSrce = false;
      bool pxeyyxGWhk = false;
      bool hyilpZFeet = false;
      bool kSpJOriFlx = false;
      bool gTeSHmzQEm = false;
      bool zagbKTuaKo = false;
      bool YmNhsXGVjF = false;
      bool NBkjEOSQeC = false;
      bool aoaqtKkOyu = false;
      bool xIuwYsGwZi = false;
      bool fdfyZypwXw = false;
      bool AewHOiMWni = false;
      bool lrWoIFGnLK = false;
      string rsKCohqDTL;
      string bnsGwCZHoP;
      string LBrYYHtmBm;
      string zdtsmBaKHj;
      string iFTiDmRzXR;
      string OfRZupBldh;
      string nEBfMyszTt;
      string bOAEgGhIUk;
      string otPjXSLTxw;
      string AogZwdDmWF;
      string sSfcpAeMso;
      string IrRrrtoRIs;
      string lZCXsmhaIC;
      string CtkOqWOlsX;
      string nyaHnHXngC;
      string okedTTQHjD;
      string SEEplNHDBU;
      string eDYjFnytik;
      string OssGNROGuW;
      string GGCpFitjVZ;
      if(rsKCohqDTL == sSfcpAeMso){AUlMWlMtYe = true;}
      else if(sSfcpAeMso == rsKCohqDTL){kSpJOriFlx = true;}
      if(bnsGwCZHoP == IrRrrtoRIs){VWYynYLxcU = true;}
      else if(IrRrrtoRIs == bnsGwCZHoP){gTeSHmzQEm = true;}
      if(LBrYYHtmBm == lZCXsmhaIC){yAHdOYBheV = true;}
      else if(lZCXsmhaIC == LBrYYHtmBm){zagbKTuaKo = true;}
      if(zdtsmBaKHj == CtkOqWOlsX){tOXJktGgja = true;}
      else if(CtkOqWOlsX == zdtsmBaKHj){YmNhsXGVjF = true;}
      if(iFTiDmRzXR == nyaHnHXngC){EUhPBjhDCf = true;}
      else if(nyaHnHXngC == iFTiDmRzXR){NBkjEOSQeC = true;}
      if(OfRZupBldh == okedTTQHjD){XwHBazMIxy = true;}
      else if(okedTTQHjD == OfRZupBldh){aoaqtKkOyu = true;}
      if(nEBfMyszTt == SEEplNHDBU){keOCkGyONs = true;}
      else if(SEEplNHDBU == nEBfMyszTt){xIuwYsGwZi = true;}
      if(bOAEgGhIUk == eDYjFnytik){ReMBPdSrce = true;}
      if(otPjXSLTxw == OssGNROGuW){pxeyyxGWhk = true;}
      if(AogZwdDmWF == GGCpFitjVZ){hyilpZFeet = true;}
      while(eDYjFnytik == bOAEgGhIUk){fdfyZypwXw = true;}
      while(OssGNROGuW == OssGNROGuW){AewHOiMWni = true;}
      while(GGCpFitjVZ == GGCpFitjVZ){lrWoIFGnLK = true;}
      if(AUlMWlMtYe == true){AUlMWlMtYe = false;}
      if(VWYynYLxcU == true){VWYynYLxcU = false;}
      if(yAHdOYBheV == true){yAHdOYBheV = false;}
      if(tOXJktGgja == true){tOXJktGgja = false;}
      if(EUhPBjhDCf == true){EUhPBjhDCf = false;}
      if(XwHBazMIxy == true){XwHBazMIxy = false;}
      if(keOCkGyONs == true){keOCkGyONs = false;}
      if(ReMBPdSrce == true){ReMBPdSrce = false;}
      if(pxeyyxGWhk == true){pxeyyxGWhk = false;}
      if(hyilpZFeet == true){hyilpZFeet = false;}
      if(kSpJOriFlx == true){kSpJOriFlx = false;}
      if(gTeSHmzQEm == true){gTeSHmzQEm = false;}
      if(zagbKTuaKo == true){zagbKTuaKo = false;}
      if(YmNhsXGVjF == true){YmNhsXGVjF = false;}
      if(NBkjEOSQeC == true){NBkjEOSQeC = false;}
      if(aoaqtKkOyu == true){aoaqtKkOyu = false;}
      if(xIuwYsGwZi == true){xIuwYsGwZi = false;}
      if(fdfyZypwXw == true){fdfyZypwXw = false;}
      if(AewHOiMWni == true){AewHOiMWni = false;}
      if(lrWoIFGnLK == true){lrWoIFGnLK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZQJLOZVER
{ 
  void NVbGiHtccV()
  { 
      bool hQYWzdFyyb = false;
      bool GoWsqYMpoW = false;
      bool ZFVhmYohyE = false;
      bool JmQrDtYWpK = false;
      bool ArAErSkuZk = false;
      bool hrybWctqia = false;
      bool nXztSTXdow = false;
      bool zpAeWgEQpT = false;
      bool mtHNWQnoVZ = false;
      bool AhmOVbsGlX = false;
      bool uHFckqrTEp = false;
      bool YcAPnsPkXB = false;
      bool ehIPwRDlJt = false;
      bool nyeRYfoebe = false;
      bool YUjfBWgXZb = false;
      bool MHhksMyofT = false;
      bool mFKKCZyipI = false;
      bool EjJrcKycNZ = false;
      bool jfLghfPtXM = false;
      bool gzyIrSJZda = false;
      string xQSsUDFJDo;
      string BCnLDIPYOV;
      string doQjVFWmmG;
      string UYRiioGqnM;
      string VttTFMypRj;
      string yCFZVIziWO;
      string fRVxTbkEcN;
      string CXkCAitxdJ;
      string HgVCHSTqNa;
      string oXTZfDYwzc;
      string btNDhaRDZm;
      string NCENHzwToB;
      string IspBYeDKVw;
      string KxxBgMTSUg;
      string BPRaMmTFRf;
      string HEGyUhELeD;
      string WGgdbPECgu;
      string fdzIzrbPok;
      string LyspnFpzgy;
      string HHnRJuinyw;
      if(xQSsUDFJDo == btNDhaRDZm){hQYWzdFyyb = true;}
      else if(btNDhaRDZm == xQSsUDFJDo){uHFckqrTEp = true;}
      if(BCnLDIPYOV == NCENHzwToB){GoWsqYMpoW = true;}
      else if(NCENHzwToB == BCnLDIPYOV){YcAPnsPkXB = true;}
      if(doQjVFWmmG == IspBYeDKVw){ZFVhmYohyE = true;}
      else if(IspBYeDKVw == doQjVFWmmG){ehIPwRDlJt = true;}
      if(UYRiioGqnM == KxxBgMTSUg){JmQrDtYWpK = true;}
      else if(KxxBgMTSUg == UYRiioGqnM){nyeRYfoebe = true;}
      if(VttTFMypRj == BPRaMmTFRf){ArAErSkuZk = true;}
      else if(BPRaMmTFRf == VttTFMypRj){YUjfBWgXZb = true;}
      if(yCFZVIziWO == HEGyUhELeD){hrybWctqia = true;}
      else if(HEGyUhELeD == yCFZVIziWO){MHhksMyofT = true;}
      if(fRVxTbkEcN == WGgdbPECgu){nXztSTXdow = true;}
      else if(WGgdbPECgu == fRVxTbkEcN){mFKKCZyipI = true;}
      if(CXkCAitxdJ == fdzIzrbPok){zpAeWgEQpT = true;}
      if(HgVCHSTqNa == LyspnFpzgy){mtHNWQnoVZ = true;}
      if(oXTZfDYwzc == HHnRJuinyw){AhmOVbsGlX = true;}
      while(fdzIzrbPok == CXkCAitxdJ){EjJrcKycNZ = true;}
      while(LyspnFpzgy == LyspnFpzgy){jfLghfPtXM = true;}
      while(HHnRJuinyw == HHnRJuinyw){gzyIrSJZda = true;}
      if(hQYWzdFyyb == true){hQYWzdFyyb = false;}
      if(GoWsqYMpoW == true){GoWsqYMpoW = false;}
      if(ZFVhmYohyE == true){ZFVhmYohyE = false;}
      if(JmQrDtYWpK == true){JmQrDtYWpK = false;}
      if(ArAErSkuZk == true){ArAErSkuZk = false;}
      if(hrybWctqia == true){hrybWctqia = false;}
      if(nXztSTXdow == true){nXztSTXdow = false;}
      if(zpAeWgEQpT == true){zpAeWgEQpT = false;}
      if(mtHNWQnoVZ == true){mtHNWQnoVZ = false;}
      if(AhmOVbsGlX == true){AhmOVbsGlX = false;}
      if(uHFckqrTEp == true){uHFckqrTEp = false;}
      if(YcAPnsPkXB == true){YcAPnsPkXB = false;}
      if(ehIPwRDlJt == true){ehIPwRDlJt = false;}
      if(nyeRYfoebe == true){nyeRYfoebe = false;}
      if(YUjfBWgXZb == true){YUjfBWgXZb = false;}
      if(MHhksMyofT == true){MHhksMyofT = false;}
      if(mFKKCZyipI == true){mFKKCZyipI = false;}
      if(EjJrcKycNZ == true){EjJrcKycNZ = false;}
      if(jfLghfPtXM == true){jfLghfPtXM = false;}
      if(gzyIrSJZda == true){gzyIrSJZda = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JOQGBDWAYE
{ 
  void eJZjszKbQq()
  { 
      bool AkbOTdbWCj = false;
      bool hAxyntdTww = false;
      bool RTYwfNJKak = false;
      bool SkhMqXKuCA = false;
      bool DVdcGsYFKA = false;
      bool FmoBXgLfhG = false;
      bool TRwQRxRjHP = false;
      bool jhQwrupwom = false;
      bool nDzZfewgoK = false;
      bool MdNwflZNKI = false;
      bool bnytQXVsIc = false;
      bool pPpuRQRVjl = false;
      bool BjuwDFUUPG = false;
      bool UckgLzEFJI = false;
      bool JCXMTwmRdO = false;
      bool UEcYHqsCqL = false;
      bool CBcCHNdJjR = false;
      bool LMLbbyLibG = false;
      bool RCpAlQzLZT = false;
      bool GCOyFIZVEF = false;
      string dJQfqbApCk;
      string zYusUszjkQ;
      string ZtmKRdpKMn;
      string gQfTlZiGzy;
      string rTJTLhPMem;
      string bWEVzjVFNM;
      string kpdNDhsbGu;
      string JrjmYFjTyi;
      string NdeYMKMJTB;
      string DdrlMCouPd;
      string onFicilQxs;
      string ACGeyHKEBs;
      string UiHFrfAyaV;
      string QnDUtZXwud;
      string XwMaBAWMmE;
      string rktWIFgAqx;
      string hnpacLzkjY;
      string jOIWUYWgDr;
      string JmKWdfsfMn;
      string sWEyuiGkyp;
      if(dJQfqbApCk == onFicilQxs){AkbOTdbWCj = true;}
      else if(onFicilQxs == dJQfqbApCk){bnytQXVsIc = true;}
      if(zYusUszjkQ == ACGeyHKEBs){hAxyntdTww = true;}
      else if(ACGeyHKEBs == zYusUszjkQ){pPpuRQRVjl = true;}
      if(ZtmKRdpKMn == UiHFrfAyaV){RTYwfNJKak = true;}
      else if(UiHFrfAyaV == ZtmKRdpKMn){BjuwDFUUPG = true;}
      if(gQfTlZiGzy == QnDUtZXwud){SkhMqXKuCA = true;}
      else if(QnDUtZXwud == gQfTlZiGzy){UckgLzEFJI = true;}
      if(rTJTLhPMem == XwMaBAWMmE){DVdcGsYFKA = true;}
      else if(XwMaBAWMmE == rTJTLhPMem){JCXMTwmRdO = true;}
      if(bWEVzjVFNM == rktWIFgAqx){FmoBXgLfhG = true;}
      else if(rktWIFgAqx == bWEVzjVFNM){UEcYHqsCqL = true;}
      if(kpdNDhsbGu == hnpacLzkjY){TRwQRxRjHP = true;}
      else if(hnpacLzkjY == kpdNDhsbGu){CBcCHNdJjR = true;}
      if(JrjmYFjTyi == jOIWUYWgDr){jhQwrupwom = true;}
      if(NdeYMKMJTB == JmKWdfsfMn){nDzZfewgoK = true;}
      if(DdrlMCouPd == sWEyuiGkyp){MdNwflZNKI = true;}
      while(jOIWUYWgDr == JrjmYFjTyi){LMLbbyLibG = true;}
      while(JmKWdfsfMn == JmKWdfsfMn){RCpAlQzLZT = true;}
      while(sWEyuiGkyp == sWEyuiGkyp){GCOyFIZVEF = true;}
      if(AkbOTdbWCj == true){AkbOTdbWCj = false;}
      if(hAxyntdTww == true){hAxyntdTww = false;}
      if(RTYwfNJKak == true){RTYwfNJKak = false;}
      if(SkhMqXKuCA == true){SkhMqXKuCA = false;}
      if(DVdcGsYFKA == true){DVdcGsYFKA = false;}
      if(FmoBXgLfhG == true){FmoBXgLfhG = false;}
      if(TRwQRxRjHP == true){TRwQRxRjHP = false;}
      if(jhQwrupwom == true){jhQwrupwom = false;}
      if(nDzZfewgoK == true){nDzZfewgoK = false;}
      if(MdNwflZNKI == true){MdNwflZNKI = false;}
      if(bnytQXVsIc == true){bnytQXVsIc = false;}
      if(pPpuRQRVjl == true){pPpuRQRVjl = false;}
      if(BjuwDFUUPG == true){BjuwDFUUPG = false;}
      if(UckgLzEFJI == true){UckgLzEFJI = false;}
      if(JCXMTwmRdO == true){JCXMTwmRdO = false;}
      if(UEcYHqsCqL == true){UEcYHqsCqL = false;}
      if(CBcCHNdJjR == true){CBcCHNdJjR = false;}
      if(LMLbbyLibG == true){LMLbbyLibG = false;}
      if(RCpAlQzLZT == true){RCpAlQzLZT = false;}
      if(GCOyFIZVEF == true){GCOyFIZVEF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBAYZGZLSS
{ 
  void RlPQPAoJjI()
  { 
      bool eKFtqQnnaB = false;
      bool EIRmnTnbaJ = false;
      bool QbOmJrMitE = false;
      bool rOtqHocdWF = false;
      bool tnXZSDIpqI = false;
      bool bysYLDuSjy = false;
      bool DFsWJoNaez = false;
      bool pJEUObEnTF = false;
      bool jWqkbsVVeE = false;
      bool sJsXCouAQc = false;
      bool ogLrRRsYJi = false;
      bool yHyeOgNHtP = false;
      bool TruaGgPfRZ = false;
      bool gDXqPCKzTK = false;
      bool AwLwFlLOJV = false;
      bool amGAIxljlk = false;
      bool BMGiCuiHOM = false;
      bool VOniOWfzUU = false;
      bool UBWwzswXhS = false;
      bool QaNhJnpctK = false;
      string iwqFgSiVzS;
      string NBGaxDnJRI;
      string zAsJkcBNfP;
      string xCFBjcSFmF;
      string YbyKMkrPnX;
      string jVZLziChUD;
      string QUpiVLwEpT;
      string kiWLiWChwz;
      string klYHfactCB;
      string akjinElOoB;
      string omZTmAzNbc;
      string fTkUSewiDt;
      string hBCnszynXe;
      string kmsuKxLETe;
      string aPRZUGAPPJ;
      string HCLtTmkkan;
      string CLoxqsapJV;
      string SqOXTRicSm;
      string ziXNWhbyaW;
      string LadfcPZThb;
      if(iwqFgSiVzS == omZTmAzNbc){eKFtqQnnaB = true;}
      else if(omZTmAzNbc == iwqFgSiVzS){ogLrRRsYJi = true;}
      if(NBGaxDnJRI == fTkUSewiDt){EIRmnTnbaJ = true;}
      else if(fTkUSewiDt == NBGaxDnJRI){yHyeOgNHtP = true;}
      if(zAsJkcBNfP == hBCnszynXe){QbOmJrMitE = true;}
      else if(hBCnszynXe == zAsJkcBNfP){TruaGgPfRZ = true;}
      if(xCFBjcSFmF == kmsuKxLETe){rOtqHocdWF = true;}
      else if(kmsuKxLETe == xCFBjcSFmF){gDXqPCKzTK = true;}
      if(YbyKMkrPnX == aPRZUGAPPJ){tnXZSDIpqI = true;}
      else if(aPRZUGAPPJ == YbyKMkrPnX){AwLwFlLOJV = true;}
      if(jVZLziChUD == HCLtTmkkan){bysYLDuSjy = true;}
      else if(HCLtTmkkan == jVZLziChUD){amGAIxljlk = true;}
      if(QUpiVLwEpT == CLoxqsapJV){DFsWJoNaez = true;}
      else if(CLoxqsapJV == QUpiVLwEpT){BMGiCuiHOM = true;}
      if(kiWLiWChwz == SqOXTRicSm){pJEUObEnTF = true;}
      if(klYHfactCB == ziXNWhbyaW){jWqkbsVVeE = true;}
      if(akjinElOoB == LadfcPZThb){sJsXCouAQc = true;}
      while(SqOXTRicSm == kiWLiWChwz){VOniOWfzUU = true;}
      while(ziXNWhbyaW == ziXNWhbyaW){UBWwzswXhS = true;}
      while(LadfcPZThb == LadfcPZThb){QaNhJnpctK = true;}
      if(eKFtqQnnaB == true){eKFtqQnnaB = false;}
      if(EIRmnTnbaJ == true){EIRmnTnbaJ = false;}
      if(QbOmJrMitE == true){QbOmJrMitE = false;}
      if(rOtqHocdWF == true){rOtqHocdWF = false;}
      if(tnXZSDIpqI == true){tnXZSDIpqI = false;}
      if(bysYLDuSjy == true){bysYLDuSjy = false;}
      if(DFsWJoNaez == true){DFsWJoNaez = false;}
      if(pJEUObEnTF == true){pJEUObEnTF = false;}
      if(jWqkbsVVeE == true){jWqkbsVVeE = false;}
      if(sJsXCouAQc == true){sJsXCouAQc = false;}
      if(ogLrRRsYJi == true){ogLrRRsYJi = false;}
      if(yHyeOgNHtP == true){yHyeOgNHtP = false;}
      if(TruaGgPfRZ == true){TruaGgPfRZ = false;}
      if(gDXqPCKzTK == true){gDXqPCKzTK = false;}
      if(AwLwFlLOJV == true){AwLwFlLOJV = false;}
      if(amGAIxljlk == true){amGAIxljlk = false;}
      if(BMGiCuiHOM == true){BMGiCuiHOM = false;}
      if(VOniOWfzUU == true){VOniOWfzUU = false;}
      if(UBWwzswXhS == true){UBWwzswXhS = false;}
      if(QaNhJnpctK == true){QaNhJnpctK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZNMQRUJKF
{ 
  void QXbQmeBZxz()
  { 
      bool HuOUDaceYs = false;
      bool hRPSSTdhqJ = false;
      bool OdgoeJwUnW = false;
      bool nIusmeoAcG = false;
      bool nlMkCRfBtS = false;
      bool IegyNdNYos = false;
      bool dIpBFYVVem = false;
      bool dcFjUbQwlN = false;
      bool dtZVNIaxfJ = false;
      bool RPLibfuLec = false;
      bool uJWGneZxdk = false;
      bool MQmaPihUmw = false;
      bool yYpVVORVHo = false;
      bool fFRJSUXTgh = false;
      bool idStwBcjTr = false;
      bool xaXheVTAkZ = false;
      bool MDooEHydIt = false;
      bool LOmENTFuYU = false;
      bool lhCOqFgjdw = false;
      bool AWiHUendoo = false;
      string oJEafmWACB;
      string WnxcNwexJR;
      string yTYYLxFMfq;
      string KQMVjpXama;
      string AUCXcTjJBz;
      string SQlPhVjfPh;
      string gJUKqGaasW;
      string YDKhQcQBuq;
      string NwLgYsdwnO;
      string FqLEspzrgW;
      string rIPdZOFDzE;
      string FikXUkynkx;
      string bdmeQgqFoZ;
      string cYTYyFfgGJ;
      string maxiIWGnjI;
      string rLGitOVkMs;
      string XAOYagOLYO;
      string EQhaKAgDVt;
      string ZDVfhRRkdj;
      string iuTNlmMXHb;
      if(oJEafmWACB == rIPdZOFDzE){HuOUDaceYs = true;}
      else if(rIPdZOFDzE == oJEafmWACB){uJWGneZxdk = true;}
      if(WnxcNwexJR == FikXUkynkx){hRPSSTdhqJ = true;}
      else if(FikXUkynkx == WnxcNwexJR){MQmaPihUmw = true;}
      if(yTYYLxFMfq == bdmeQgqFoZ){OdgoeJwUnW = true;}
      else if(bdmeQgqFoZ == yTYYLxFMfq){yYpVVORVHo = true;}
      if(KQMVjpXama == cYTYyFfgGJ){nIusmeoAcG = true;}
      else if(cYTYyFfgGJ == KQMVjpXama){fFRJSUXTgh = true;}
      if(AUCXcTjJBz == maxiIWGnjI){nlMkCRfBtS = true;}
      else if(maxiIWGnjI == AUCXcTjJBz){idStwBcjTr = true;}
      if(SQlPhVjfPh == rLGitOVkMs){IegyNdNYos = true;}
      else if(rLGitOVkMs == SQlPhVjfPh){xaXheVTAkZ = true;}
      if(gJUKqGaasW == XAOYagOLYO){dIpBFYVVem = true;}
      else if(XAOYagOLYO == gJUKqGaasW){MDooEHydIt = true;}
      if(YDKhQcQBuq == EQhaKAgDVt){dcFjUbQwlN = true;}
      if(NwLgYsdwnO == ZDVfhRRkdj){dtZVNIaxfJ = true;}
      if(FqLEspzrgW == iuTNlmMXHb){RPLibfuLec = true;}
      while(EQhaKAgDVt == YDKhQcQBuq){LOmENTFuYU = true;}
      while(ZDVfhRRkdj == ZDVfhRRkdj){lhCOqFgjdw = true;}
      while(iuTNlmMXHb == iuTNlmMXHb){AWiHUendoo = true;}
      if(HuOUDaceYs == true){HuOUDaceYs = false;}
      if(hRPSSTdhqJ == true){hRPSSTdhqJ = false;}
      if(OdgoeJwUnW == true){OdgoeJwUnW = false;}
      if(nIusmeoAcG == true){nIusmeoAcG = false;}
      if(nlMkCRfBtS == true){nlMkCRfBtS = false;}
      if(IegyNdNYos == true){IegyNdNYos = false;}
      if(dIpBFYVVem == true){dIpBFYVVem = false;}
      if(dcFjUbQwlN == true){dcFjUbQwlN = false;}
      if(dtZVNIaxfJ == true){dtZVNIaxfJ = false;}
      if(RPLibfuLec == true){RPLibfuLec = false;}
      if(uJWGneZxdk == true){uJWGneZxdk = false;}
      if(MQmaPihUmw == true){MQmaPihUmw = false;}
      if(yYpVVORVHo == true){yYpVVORVHo = false;}
      if(fFRJSUXTgh == true){fFRJSUXTgh = false;}
      if(idStwBcjTr == true){idStwBcjTr = false;}
      if(xaXheVTAkZ == true){xaXheVTAkZ = false;}
      if(MDooEHydIt == true){MDooEHydIt = false;}
      if(LOmENTFuYU == true){LOmENTFuYU = false;}
      if(lhCOqFgjdw == true){lhCOqFgjdw = false;}
      if(AWiHUendoo == true){AWiHUendoo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQVAROXISH
{ 
  void ByzKJAlTTA()
  { 
      bool BrjGNsLjBD = false;
      bool QjuVBocAVG = false;
      bool DHBinfQGzE = false;
      bool rSwcIJzXIa = false;
      bool zhkSDueSrF = false;
      bool YRksItpBSh = false;
      bool cFjwLynSMr = false;
      bool oEqtGUVifr = false;
      bool ByOteZgCUO = false;
      bool SyFaytxnHE = false;
      bool HMFzPUZpmm = false;
      bool XHVZgdppRk = false;
      bool QkxyZqzQuL = false;
      bool WhaaknsPdK = false;
      bool zqPgqKbetU = false;
      bool EHWVnWOGZY = false;
      bool UJtaPpfuor = false;
      bool kaLGlYUQHO = false;
      bool OTWaHPKElO = false;
      bool ZlpFopwnQA = false;
      string dkgwNcUAQY;
      string JyKckeBAEH;
      string MTbWOaskii;
      string nCRkItkfqY;
      string KcbIWsTacP;
      string RUwIbJIKhl;
      string jiRgjHfYTq;
      string sUJfwjrTAV;
      string GRHTQTGJJy;
      string kayFnaKuYP;
      string MuGlVwKPLq;
      string RoJLeSayPP;
      string BWOVFSWErU;
      string YwukJLLVxU;
      string IpxSguQmZU;
      string zMeIOofkfD;
      string ZGXqSUtYCT;
      string GFAuGKYwoK;
      string BjdWULRlWT;
      string eaotuCSGzL;
      if(dkgwNcUAQY == MuGlVwKPLq){BrjGNsLjBD = true;}
      else if(MuGlVwKPLq == dkgwNcUAQY){HMFzPUZpmm = true;}
      if(JyKckeBAEH == RoJLeSayPP){QjuVBocAVG = true;}
      else if(RoJLeSayPP == JyKckeBAEH){XHVZgdppRk = true;}
      if(MTbWOaskii == BWOVFSWErU){DHBinfQGzE = true;}
      else if(BWOVFSWErU == MTbWOaskii){QkxyZqzQuL = true;}
      if(nCRkItkfqY == YwukJLLVxU){rSwcIJzXIa = true;}
      else if(YwukJLLVxU == nCRkItkfqY){WhaaknsPdK = true;}
      if(KcbIWsTacP == IpxSguQmZU){zhkSDueSrF = true;}
      else if(IpxSguQmZU == KcbIWsTacP){zqPgqKbetU = true;}
      if(RUwIbJIKhl == zMeIOofkfD){YRksItpBSh = true;}
      else if(zMeIOofkfD == RUwIbJIKhl){EHWVnWOGZY = true;}
      if(jiRgjHfYTq == ZGXqSUtYCT){cFjwLynSMr = true;}
      else if(ZGXqSUtYCT == jiRgjHfYTq){UJtaPpfuor = true;}
      if(sUJfwjrTAV == GFAuGKYwoK){oEqtGUVifr = true;}
      if(GRHTQTGJJy == BjdWULRlWT){ByOteZgCUO = true;}
      if(kayFnaKuYP == eaotuCSGzL){SyFaytxnHE = true;}
      while(GFAuGKYwoK == sUJfwjrTAV){kaLGlYUQHO = true;}
      while(BjdWULRlWT == BjdWULRlWT){OTWaHPKElO = true;}
      while(eaotuCSGzL == eaotuCSGzL){ZlpFopwnQA = true;}
      if(BrjGNsLjBD == true){BrjGNsLjBD = false;}
      if(QjuVBocAVG == true){QjuVBocAVG = false;}
      if(DHBinfQGzE == true){DHBinfQGzE = false;}
      if(rSwcIJzXIa == true){rSwcIJzXIa = false;}
      if(zhkSDueSrF == true){zhkSDueSrF = false;}
      if(YRksItpBSh == true){YRksItpBSh = false;}
      if(cFjwLynSMr == true){cFjwLynSMr = false;}
      if(oEqtGUVifr == true){oEqtGUVifr = false;}
      if(ByOteZgCUO == true){ByOteZgCUO = false;}
      if(SyFaytxnHE == true){SyFaytxnHE = false;}
      if(HMFzPUZpmm == true){HMFzPUZpmm = false;}
      if(XHVZgdppRk == true){XHVZgdppRk = false;}
      if(QkxyZqzQuL == true){QkxyZqzQuL = false;}
      if(WhaaknsPdK == true){WhaaknsPdK = false;}
      if(zqPgqKbetU == true){zqPgqKbetU = false;}
      if(EHWVnWOGZY == true){EHWVnWOGZY = false;}
      if(UJtaPpfuor == true){UJtaPpfuor = false;}
      if(kaLGlYUQHO == true){kaLGlYUQHO = false;}
      if(OTWaHPKElO == true){OTWaHPKElO = false;}
      if(ZlpFopwnQA == true){ZlpFopwnQA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGLNHCPXIP
{ 
  void NXoWrDgjrN()
  { 
      bool EEGVtiUqqr = false;
      bool XiHqQhpLEi = false;
      bool LgAMOIdIUS = false;
      bool fGJKGTUxZj = false;
      bool bmutgsPhPR = false;
      bool tSKkBXDsHl = false;
      bool ELVYLQYwjx = false;
      bool NrkUHYkFeV = false;
      bool rwsDYMuYJh = false;
      bool PapnePQWiQ = false;
      bool TSxSEBgpdc = false;
      bool lxOksHSSzz = false;
      bool UAmBglBxoq = false;
      bool HNWOCZzZzW = false;
      bool eEufuSMFtX = false;
      bool xyWjuSeukR = false;
      bool zjBlVYaziT = false;
      bool HrScTPFHGO = false;
      bool ZwDQtIqmTi = false;
      bool tEogWuDIJW = false;
      string jqwJUdDBLx;
      string oseHVyAsSc;
      string lVKDmBfLOO;
      string KbQIxJNLOJ;
      string HIngmhQSyn;
      string wWlzSNgsVS;
      string xqlwmMbVKM;
      string jndIVdhcPE;
      string kMMZRnpRpi;
      string bUowLQVqtZ;
      string FtIlEIrdcn;
      string fDcQhkdLey;
      string WKfbjPzhwF;
      string HpipzpEaVJ;
      string uLnBDYqXNa;
      string lKMuCtNgCo;
      string JKgXgoTmRq;
      string fDoUDKWeYK;
      string XaTUSxdmmE;
      string bXYgAjePUN;
      if(jqwJUdDBLx == FtIlEIrdcn){EEGVtiUqqr = true;}
      else if(FtIlEIrdcn == jqwJUdDBLx){TSxSEBgpdc = true;}
      if(oseHVyAsSc == fDcQhkdLey){XiHqQhpLEi = true;}
      else if(fDcQhkdLey == oseHVyAsSc){lxOksHSSzz = true;}
      if(lVKDmBfLOO == WKfbjPzhwF){LgAMOIdIUS = true;}
      else if(WKfbjPzhwF == lVKDmBfLOO){UAmBglBxoq = true;}
      if(KbQIxJNLOJ == HpipzpEaVJ){fGJKGTUxZj = true;}
      else if(HpipzpEaVJ == KbQIxJNLOJ){HNWOCZzZzW = true;}
      if(HIngmhQSyn == uLnBDYqXNa){bmutgsPhPR = true;}
      else if(uLnBDYqXNa == HIngmhQSyn){eEufuSMFtX = true;}
      if(wWlzSNgsVS == lKMuCtNgCo){tSKkBXDsHl = true;}
      else if(lKMuCtNgCo == wWlzSNgsVS){xyWjuSeukR = true;}
      if(xqlwmMbVKM == JKgXgoTmRq){ELVYLQYwjx = true;}
      else if(JKgXgoTmRq == xqlwmMbVKM){zjBlVYaziT = true;}
      if(jndIVdhcPE == fDoUDKWeYK){NrkUHYkFeV = true;}
      if(kMMZRnpRpi == XaTUSxdmmE){rwsDYMuYJh = true;}
      if(bUowLQVqtZ == bXYgAjePUN){PapnePQWiQ = true;}
      while(fDoUDKWeYK == jndIVdhcPE){HrScTPFHGO = true;}
      while(XaTUSxdmmE == XaTUSxdmmE){ZwDQtIqmTi = true;}
      while(bXYgAjePUN == bXYgAjePUN){tEogWuDIJW = true;}
      if(EEGVtiUqqr == true){EEGVtiUqqr = false;}
      if(XiHqQhpLEi == true){XiHqQhpLEi = false;}
      if(LgAMOIdIUS == true){LgAMOIdIUS = false;}
      if(fGJKGTUxZj == true){fGJKGTUxZj = false;}
      if(bmutgsPhPR == true){bmutgsPhPR = false;}
      if(tSKkBXDsHl == true){tSKkBXDsHl = false;}
      if(ELVYLQYwjx == true){ELVYLQYwjx = false;}
      if(NrkUHYkFeV == true){NrkUHYkFeV = false;}
      if(rwsDYMuYJh == true){rwsDYMuYJh = false;}
      if(PapnePQWiQ == true){PapnePQWiQ = false;}
      if(TSxSEBgpdc == true){TSxSEBgpdc = false;}
      if(lxOksHSSzz == true){lxOksHSSzz = false;}
      if(UAmBglBxoq == true){UAmBglBxoq = false;}
      if(HNWOCZzZzW == true){HNWOCZzZzW = false;}
      if(eEufuSMFtX == true){eEufuSMFtX = false;}
      if(xyWjuSeukR == true){xyWjuSeukR = false;}
      if(zjBlVYaziT == true){zjBlVYaziT = false;}
      if(HrScTPFHGO == true){HrScTPFHGO = false;}
      if(ZwDQtIqmTi == true){ZwDQtIqmTi = false;}
      if(tEogWuDIJW == true){tEogWuDIJW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRDRENVHVL
{ 
  void VTYzGRYFfG()
  { 
      bool ITtAeUYDcw = false;
      bool KnnZKDESlx = false;
      bool NdZQEMgFoC = false;
      bool xlWsptALrI = false;
      bool SFAQBZXqeK = false;
      bool PyZMndscuR = false;
      bool mTOZzXRuiP = false;
      bool CsZcdHcIPe = false;
      bool opadlyMKEM = false;
      bool AWQaVzqZRd = false;
      bool IbHOHWYwhg = false;
      bool AkNPbxrknA = false;
      bool LGpWPfczHe = false;
      bool PCplWMhLVP = false;
      bool ZPbXLPJAyX = false;
      bool GGlRRBljyb = false;
      bool tZoDQxtbsO = false;
      bool PfOXZueRLz = false;
      bool VbAjXJQYTV = false;
      bool axMsVAaXHO = false;
      string fMQLIxDAbS;
      string ocVUwiNLlg;
      string bElsITgknh;
      string dqKondsYKn;
      string anQyhCiiGh;
      string EwQTnbaXDn;
      string QSMsoyRggS;
      string pnByGmmmKF;
      string kxdFdgapAM;
      string DUVVWIaWJj;
      string jBCnrQuRNB;
      string nmNyCTnHPI;
      string XafTPUSeax;
      string LQdZUitpMM;
      string kIczYQHXSD;
      string TTGALIViYX;
      string yQpQoWIncS;
      string YytDWPygty;
      string NuLXdrJdNL;
      string NLRoOURMJB;
      if(fMQLIxDAbS == jBCnrQuRNB){ITtAeUYDcw = true;}
      else if(jBCnrQuRNB == fMQLIxDAbS){IbHOHWYwhg = true;}
      if(ocVUwiNLlg == nmNyCTnHPI){KnnZKDESlx = true;}
      else if(nmNyCTnHPI == ocVUwiNLlg){AkNPbxrknA = true;}
      if(bElsITgknh == XafTPUSeax){NdZQEMgFoC = true;}
      else if(XafTPUSeax == bElsITgknh){LGpWPfczHe = true;}
      if(dqKondsYKn == LQdZUitpMM){xlWsptALrI = true;}
      else if(LQdZUitpMM == dqKondsYKn){PCplWMhLVP = true;}
      if(anQyhCiiGh == kIczYQHXSD){SFAQBZXqeK = true;}
      else if(kIczYQHXSD == anQyhCiiGh){ZPbXLPJAyX = true;}
      if(EwQTnbaXDn == TTGALIViYX){PyZMndscuR = true;}
      else if(TTGALIViYX == EwQTnbaXDn){GGlRRBljyb = true;}
      if(QSMsoyRggS == yQpQoWIncS){mTOZzXRuiP = true;}
      else if(yQpQoWIncS == QSMsoyRggS){tZoDQxtbsO = true;}
      if(pnByGmmmKF == YytDWPygty){CsZcdHcIPe = true;}
      if(kxdFdgapAM == NuLXdrJdNL){opadlyMKEM = true;}
      if(DUVVWIaWJj == NLRoOURMJB){AWQaVzqZRd = true;}
      while(YytDWPygty == pnByGmmmKF){PfOXZueRLz = true;}
      while(NuLXdrJdNL == NuLXdrJdNL){VbAjXJQYTV = true;}
      while(NLRoOURMJB == NLRoOURMJB){axMsVAaXHO = true;}
      if(ITtAeUYDcw == true){ITtAeUYDcw = false;}
      if(KnnZKDESlx == true){KnnZKDESlx = false;}
      if(NdZQEMgFoC == true){NdZQEMgFoC = false;}
      if(xlWsptALrI == true){xlWsptALrI = false;}
      if(SFAQBZXqeK == true){SFAQBZXqeK = false;}
      if(PyZMndscuR == true){PyZMndscuR = false;}
      if(mTOZzXRuiP == true){mTOZzXRuiP = false;}
      if(CsZcdHcIPe == true){CsZcdHcIPe = false;}
      if(opadlyMKEM == true){opadlyMKEM = false;}
      if(AWQaVzqZRd == true){AWQaVzqZRd = false;}
      if(IbHOHWYwhg == true){IbHOHWYwhg = false;}
      if(AkNPbxrknA == true){AkNPbxrknA = false;}
      if(LGpWPfczHe == true){LGpWPfczHe = false;}
      if(PCplWMhLVP == true){PCplWMhLVP = false;}
      if(ZPbXLPJAyX == true){ZPbXLPJAyX = false;}
      if(GGlRRBljyb == true){GGlRRBljyb = false;}
      if(tZoDQxtbsO == true){tZoDQxtbsO = false;}
      if(PfOXZueRLz == true){PfOXZueRLz = false;}
      if(VbAjXJQYTV == true){VbAjXJQYTV = false;}
      if(axMsVAaXHO == true){axMsVAaXHO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDCJCUPVBV
{ 
  void gtSADjWfVk()
  { 
      bool IhsIJZCatP = false;
      bool cYpjlYBetP = false;
      bool RsDgaaoLzr = false;
      bool JSgVlLpHZc = false;
      bool aUDBnGnVFk = false;
      bool GDWUMOdLgh = false;
      bool jpbCGKrTyZ = false;
      bool itERoxpCrT = false;
      bool mSFOkGwLJW = false;
      bool gdZrrjrBud = false;
      bool OTXfBMzEfO = false;
      bool YbSNuRjMQz = false;
      bool OgKbrEUMZE = false;
      bool EoGOFSuZMX = false;
      bool HqftyEKMwa = false;
      bool AejuPhJwmx = false;
      bool rmeaKiVEHc = false;
      bool VKAsrXAPcm = false;
      bool sHPyEYFLzX = false;
      bool IzlPeULFjO = false;
      string WUgGotuISj;
      string EMCGCMwHAT;
      string eiZPjARFdn;
      string pGfAabPuhP;
      string rNpOtroOxa;
      string lUxwtmtQWn;
      string boedtxgCfZ;
      string xAYkaRrLVq;
      string KDICCUIiGm;
      string gyYsmDhLTw;
      string LmiWdkwMUb;
      string thuedYgbaY;
      string nywrsybexX;
      string igqZfWTkXR;
      string YwNdryDsPN;
      string VGktHNqpdf;
      string IQOwsNpVzG;
      string EwDJArjRAt;
      string tiPjCcwxRR;
      string fdGrJIhQkd;
      if(WUgGotuISj == LmiWdkwMUb){IhsIJZCatP = true;}
      else if(LmiWdkwMUb == WUgGotuISj){OTXfBMzEfO = true;}
      if(EMCGCMwHAT == thuedYgbaY){cYpjlYBetP = true;}
      else if(thuedYgbaY == EMCGCMwHAT){YbSNuRjMQz = true;}
      if(eiZPjARFdn == nywrsybexX){RsDgaaoLzr = true;}
      else if(nywrsybexX == eiZPjARFdn){OgKbrEUMZE = true;}
      if(pGfAabPuhP == igqZfWTkXR){JSgVlLpHZc = true;}
      else if(igqZfWTkXR == pGfAabPuhP){EoGOFSuZMX = true;}
      if(rNpOtroOxa == YwNdryDsPN){aUDBnGnVFk = true;}
      else if(YwNdryDsPN == rNpOtroOxa){HqftyEKMwa = true;}
      if(lUxwtmtQWn == VGktHNqpdf){GDWUMOdLgh = true;}
      else if(VGktHNqpdf == lUxwtmtQWn){AejuPhJwmx = true;}
      if(boedtxgCfZ == IQOwsNpVzG){jpbCGKrTyZ = true;}
      else if(IQOwsNpVzG == boedtxgCfZ){rmeaKiVEHc = true;}
      if(xAYkaRrLVq == EwDJArjRAt){itERoxpCrT = true;}
      if(KDICCUIiGm == tiPjCcwxRR){mSFOkGwLJW = true;}
      if(gyYsmDhLTw == fdGrJIhQkd){gdZrrjrBud = true;}
      while(EwDJArjRAt == xAYkaRrLVq){VKAsrXAPcm = true;}
      while(tiPjCcwxRR == tiPjCcwxRR){sHPyEYFLzX = true;}
      while(fdGrJIhQkd == fdGrJIhQkd){IzlPeULFjO = true;}
      if(IhsIJZCatP == true){IhsIJZCatP = false;}
      if(cYpjlYBetP == true){cYpjlYBetP = false;}
      if(RsDgaaoLzr == true){RsDgaaoLzr = false;}
      if(JSgVlLpHZc == true){JSgVlLpHZc = false;}
      if(aUDBnGnVFk == true){aUDBnGnVFk = false;}
      if(GDWUMOdLgh == true){GDWUMOdLgh = false;}
      if(jpbCGKrTyZ == true){jpbCGKrTyZ = false;}
      if(itERoxpCrT == true){itERoxpCrT = false;}
      if(mSFOkGwLJW == true){mSFOkGwLJW = false;}
      if(gdZrrjrBud == true){gdZrrjrBud = false;}
      if(OTXfBMzEfO == true){OTXfBMzEfO = false;}
      if(YbSNuRjMQz == true){YbSNuRjMQz = false;}
      if(OgKbrEUMZE == true){OgKbrEUMZE = false;}
      if(EoGOFSuZMX == true){EoGOFSuZMX = false;}
      if(HqftyEKMwa == true){HqftyEKMwa = false;}
      if(AejuPhJwmx == true){AejuPhJwmx = false;}
      if(rmeaKiVEHc == true){rmeaKiVEHc = false;}
      if(VKAsrXAPcm == true){VKAsrXAPcm = false;}
      if(sHPyEYFLzX == true){sHPyEYFLzX = false;}
      if(IzlPeULFjO == true){IzlPeULFjO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGXSJXWZQW
{ 
  void BSWuXwIYZC()
  { 
      bool YuDUxUXWlR = false;
      bool YlRVoUrXzz = false;
      bool admFRHUOFo = false;
      bool QBQzfXttkB = false;
      bool uftfgcRwuh = false;
      bool ehsRjtHyDp = false;
      bool zJQxBXUSpQ = false;
      bool ZxlyEtjHYo = false;
      bool oYSXJiIzPk = false;
      bool QwquBlPwdI = false;
      bool HzGeHgutNo = false;
      bool KzYNAapsmS = false;
      bool OVCEAdGqxR = false;
      bool encPgpSnPc = false;
      bool mOlZaQWcuZ = false;
      bool wWJLtlwBed = false;
      bool aEwuKWVJgJ = false;
      bool IBdKeAjcdi = false;
      bool GduWVHdRVu = false;
      bool tQJkChRpOE = false;
      string sJftWGeIix;
      string uGaKCrGrqw;
      string NlyzFfRpPA;
      string GahLIklpJe;
      string cHsepCFdgO;
      string xGnSPGKgoq;
      string oosipUYPBQ;
      string FPiLSFsTID;
      string ZmIBDAmOuC;
      string aFBSonOKnV;
      string cobPIgWbAK;
      string MpXlQCfqeo;
      string gJUzoANQVd;
      string pielZjLrrV;
      string dLOkojgPBm;
      string IWeynTUbaI;
      string SGFVTdLlLg;
      string pmzILVtiKE;
      string SyOhVTDgyF;
      string OiRjDWFsRK;
      if(sJftWGeIix == cobPIgWbAK){YuDUxUXWlR = true;}
      else if(cobPIgWbAK == sJftWGeIix){HzGeHgutNo = true;}
      if(uGaKCrGrqw == MpXlQCfqeo){YlRVoUrXzz = true;}
      else if(MpXlQCfqeo == uGaKCrGrqw){KzYNAapsmS = true;}
      if(NlyzFfRpPA == gJUzoANQVd){admFRHUOFo = true;}
      else if(gJUzoANQVd == NlyzFfRpPA){OVCEAdGqxR = true;}
      if(GahLIklpJe == pielZjLrrV){QBQzfXttkB = true;}
      else if(pielZjLrrV == GahLIklpJe){encPgpSnPc = true;}
      if(cHsepCFdgO == dLOkojgPBm){uftfgcRwuh = true;}
      else if(dLOkojgPBm == cHsepCFdgO){mOlZaQWcuZ = true;}
      if(xGnSPGKgoq == IWeynTUbaI){ehsRjtHyDp = true;}
      else if(IWeynTUbaI == xGnSPGKgoq){wWJLtlwBed = true;}
      if(oosipUYPBQ == SGFVTdLlLg){zJQxBXUSpQ = true;}
      else if(SGFVTdLlLg == oosipUYPBQ){aEwuKWVJgJ = true;}
      if(FPiLSFsTID == pmzILVtiKE){ZxlyEtjHYo = true;}
      if(ZmIBDAmOuC == SyOhVTDgyF){oYSXJiIzPk = true;}
      if(aFBSonOKnV == OiRjDWFsRK){QwquBlPwdI = true;}
      while(pmzILVtiKE == FPiLSFsTID){IBdKeAjcdi = true;}
      while(SyOhVTDgyF == SyOhVTDgyF){GduWVHdRVu = true;}
      while(OiRjDWFsRK == OiRjDWFsRK){tQJkChRpOE = true;}
      if(YuDUxUXWlR == true){YuDUxUXWlR = false;}
      if(YlRVoUrXzz == true){YlRVoUrXzz = false;}
      if(admFRHUOFo == true){admFRHUOFo = false;}
      if(QBQzfXttkB == true){QBQzfXttkB = false;}
      if(uftfgcRwuh == true){uftfgcRwuh = false;}
      if(ehsRjtHyDp == true){ehsRjtHyDp = false;}
      if(zJQxBXUSpQ == true){zJQxBXUSpQ = false;}
      if(ZxlyEtjHYo == true){ZxlyEtjHYo = false;}
      if(oYSXJiIzPk == true){oYSXJiIzPk = false;}
      if(QwquBlPwdI == true){QwquBlPwdI = false;}
      if(HzGeHgutNo == true){HzGeHgutNo = false;}
      if(KzYNAapsmS == true){KzYNAapsmS = false;}
      if(OVCEAdGqxR == true){OVCEAdGqxR = false;}
      if(encPgpSnPc == true){encPgpSnPc = false;}
      if(mOlZaQWcuZ == true){mOlZaQWcuZ = false;}
      if(wWJLtlwBed == true){wWJLtlwBed = false;}
      if(aEwuKWVJgJ == true){aEwuKWVJgJ = false;}
      if(IBdKeAjcdi == true){IBdKeAjcdi = false;}
      if(GduWVHdRVu == true){GduWVHdRVu = false;}
      if(tQJkChRpOE == true){tQJkChRpOE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQYTHNMTBV
{ 
  void WswPToIegF()
  { 
      bool kVyCJaAgNS = false;
      bool FTtZHnKAXw = false;
      bool ZpKnaXkNjZ = false;
      bool LnZtRnCQPg = false;
      bool FpGVfCJPHD = false;
      bool FEydwtKJbl = false;
      bool plxnHRszIS = false;
      bool lskppijoHX = false;
      bool OUGfTHowyW = false;
      bool crocqTrSNO = false;
      bool IJGnRMSHmM = false;
      bool KVCDWUeQTA = false;
      bool bxBkptEHzW = false;
      bool qRasOENSOH = false;
      bool ngIlMHpkGV = false;
      bool nbyNlLIUyX = false;
      bool IKIPVstInS = false;
      bool GMCLLtnOYh = false;
      bool DSBdiPSMGD = false;
      bool wrTqzdYrQS = false;
      string GUdnqYlgtX;
      string AGzCAyoUIs;
      string ocazaRcxwl;
      string wmuNYYYOMW;
      string kUbOsqgVDU;
      string oFWzDdteMY;
      string wnjHaMKldb;
      string YaHlHTALFi;
      string kGtawqQuKu;
      string dtBnawkTmf;
      string ftrauOxkri;
      string chYcmotIKj;
      string wPahyeYTKK;
      string hfXYDpNSfh;
      string seDaRuUXAk;
      string CcJDjQTKcQ;
      string odZgBwKzZx;
      string baccpQLzPC;
      string JATYIFWTol;
      string WDpOrPFWZV;
      if(GUdnqYlgtX == ftrauOxkri){kVyCJaAgNS = true;}
      else if(ftrauOxkri == GUdnqYlgtX){IJGnRMSHmM = true;}
      if(AGzCAyoUIs == chYcmotIKj){FTtZHnKAXw = true;}
      else if(chYcmotIKj == AGzCAyoUIs){KVCDWUeQTA = true;}
      if(ocazaRcxwl == wPahyeYTKK){ZpKnaXkNjZ = true;}
      else if(wPahyeYTKK == ocazaRcxwl){bxBkptEHzW = true;}
      if(wmuNYYYOMW == hfXYDpNSfh){LnZtRnCQPg = true;}
      else if(hfXYDpNSfh == wmuNYYYOMW){qRasOENSOH = true;}
      if(kUbOsqgVDU == seDaRuUXAk){FpGVfCJPHD = true;}
      else if(seDaRuUXAk == kUbOsqgVDU){ngIlMHpkGV = true;}
      if(oFWzDdteMY == CcJDjQTKcQ){FEydwtKJbl = true;}
      else if(CcJDjQTKcQ == oFWzDdteMY){nbyNlLIUyX = true;}
      if(wnjHaMKldb == odZgBwKzZx){plxnHRszIS = true;}
      else if(odZgBwKzZx == wnjHaMKldb){IKIPVstInS = true;}
      if(YaHlHTALFi == baccpQLzPC){lskppijoHX = true;}
      if(kGtawqQuKu == JATYIFWTol){OUGfTHowyW = true;}
      if(dtBnawkTmf == WDpOrPFWZV){crocqTrSNO = true;}
      while(baccpQLzPC == YaHlHTALFi){GMCLLtnOYh = true;}
      while(JATYIFWTol == JATYIFWTol){DSBdiPSMGD = true;}
      while(WDpOrPFWZV == WDpOrPFWZV){wrTqzdYrQS = true;}
      if(kVyCJaAgNS == true){kVyCJaAgNS = false;}
      if(FTtZHnKAXw == true){FTtZHnKAXw = false;}
      if(ZpKnaXkNjZ == true){ZpKnaXkNjZ = false;}
      if(LnZtRnCQPg == true){LnZtRnCQPg = false;}
      if(FpGVfCJPHD == true){FpGVfCJPHD = false;}
      if(FEydwtKJbl == true){FEydwtKJbl = false;}
      if(plxnHRszIS == true){plxnHRszIS = false;}
      if(lskppijoHX == true){lskppijoHX = false;}
      if(OUGfTHowyW == true){OUGfTHowyW = false;}
      if(crocqTrSNO == true){crocqTrSNO = false;}
      if(IJGnRMSHmM == true){IJGnRMSHmM = false;}
      if(KVCDWUeQTA == true){KVCDWUeQTA = false;}
      if(bxBkptEHzW == true){bxBkptEHzW = false;}
      if(qRasOENSOH == true){qRasOENSOH = false;}
      if(ngIlMHpkGV == true){ngIlMHpkGV = false;}
      if(nbyNlLIUyX == true){nbyNlLIUyX = false;}
      if(IKIPVstInS == true){IKIPVstInS = false;}
      if(GMCLLtnOYh == true){GMCLLtnOYh = false;}
      if(DSBdiPSMGD == true){DSBdiPSMGD = false;}
      if(wrTqzdYrQS == true){wrTqzdYrQS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DEKLZQBUYB
{ 
  void gTYKKNIiTH()
  { 
      bool rnicoWIshU = false;
      bool jpwfsMRuxe = false;
      bool yugToTbfOf = false;
      bool XUnmbLgapa = false;
      bool pCKsnPsHNi = false;
      bool mIfIcxHOmU = false;
      bool tbeBwPBIEg = false;
      bool fqFWowkmfY = false;
      bool aUSfsPoeKe = false;
      bool ERmUfNWIxY = false;
      bool NkDfCuDISf = false;
      bool LTiOtZJyIf = false;
      bool ZWxYcNDjpb = false;
      bool YcpHKpQlcx = false;
      bool MfLdSjiYaG = false;
      bool EXAQyqmdDo = false;
      bool rSSqHidaDE = false;
      bool IXVKTtKTFs = false;
      bool ddJiWAcYJT = false;
      bool ClinFsNTWj = false;
      string iGgApmgyHg;
      string WhjpJjFQEX;
      string iCMLnkiffe;
      string teKxtZKmwP;
      string tCPTwbAomC;
      string lTtIFfsVLE;
      string EARbmqXmwi;
      string YSUodfmsPL;
      string kssdrZjBrN;
      string goarKskmgE;
      string EMsDcTzFdZ;
      string sAFzTKGniM;
      string HVthBiqbej;
      string uzLKHXApAY;
      string aeXSTgiaXz;
      string mwETxiRKBs;
      string cWatdsnuru;
      string KQmKkcybNU;
      string APEexyurNY;
      string FpnHuEEcna;
      if(iGgApmgyHg == EMsDcTzFdZ){rnicoWIshU = true;}
      else if(EMsDcTzFdZ == iGgApmgyHg){NkDfCuDISf = true;}
      if(WhjpJjFQEX == sAFzTKGniM){jpwfsMRuxe = true;}
      else if(sAFzTKGniM == WhjpJjFQEX){LTiOtZJyIf = true;}
      if(iCMLnkiffe == HVthBiqbej){yugToTbfOf = true;}
      else if(HVthBiqbej == iCMLnkiffe){ZWxYcNDjpb = true;}
      if(teKxtZKmwP == uzLKHXApAY){XUnmbLgapa = true;}
      else if(uzLKHXApAY == teKxtZKmwP){YcpHKpQlcx = true;}
      if(tCPTwbAomC == aeXSTgiaXz){pCKsnPsHNi = true;}
      else if(aeXSTgiaXz == tCPTwbAomC){MfLdSjiYaG = true;}
      if(lTtIFfsVLE == mwETxiRKBs){mIfIcxHOmU = true;}
      else if(mwETxiRKBs == lTtIFfsVLE){EXAQyqmdDo = true;}
      if(EARbmqXmwi == cWatdsnuru){tbeBwPBIEg = true;}
      else if(cWatdsnuru == EARbmqXmwi){rSSqHidaDE = true;}
      if(YSUodfmsPL == KQmKkcybNU){fqFWowkmfY = true;}
      if(kssdrZjBrN == APEexyurNY){aUSfsPoeKe = true;}
      if(goarKskmgE == FpnHuEEcna){ERmUfNWIxY = true;}
      while(KQmKkcybNU == YSUodfmsPL){IXVKTtKTFs = true;}
      while(APEexyurNY == APEexyurNY){ddJiWAcYJT = true;}
      while(FpnHuEEcna == FpnHuEEcna){ClinFsNTWj = true;}
      if(rnicoWIshU == true){rnicoWIshU = false;}
      if(jpwfsMRuxe == true){jpwfsMRuxe = false;}
      if(yugToTbfOf == true){yugToTbfOf = false;}
      if(XUnmbLgapa == true){XUnmbLgapa = false;}
      if(pCKsnPsHNi == true){pCKsnPsHNi = false;}
      if(mIfIcxHOmU == true){mIfIcxHOmU = false;}
      if(tbeBwPBIEg == true){tbeBwPBIEg = false;}
      if(fqFWowkmfY == true){fqFWowkmfY = false;}
      if(aUSfsPoeKe == true){aUSfsPoeKe = false;}
      if(ERmUfNWIxY == true){ERmUfNWIxY = false;}
      if(NkDfCuDISf == true){NkDfCuDISf = false;}
      if(LTiOtZJyIf == true){LTiOtZJyIf = false;}
      if(ZWxYcNDjpb == true){ZWxYcNDjpb = false;}
      if(YcpHKpQlcx == true){YcpHKpQlcx = false;}
      if(MfLdSjiYaG == true){MfLdSjiYaG = false;}
      if(EXAQyqmdDo == true){EXAQyqmdDo = false;}
      if(rSSqHidaDE == true){rSSqHidaDE = false;}
      if(IXVKTtKTFs == true){IXVKTtKTFs = false;}
      if(ddJiWAcYJT == true){ddJiWAcYJT = false;}
      if(ClinFsNTWj == true){ClinFsNTWj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDWUIQZSTY
{ 
  void yXprUfDfpx()
  { 
      bool cXaHLciSWT = false;
      bool BZxDGuJprs = false;
      bool IAUNoTxJAq = false;
      bool CfwXGVzkTN = false;
      bool DUKipWVlOr = false;
      bool ugmEIcDNRq = false;
      bool eZRfQVcYxj = false;
      bool wYWdompkWR = false;
      bool yLtIwVrqPc = false;
      bool RkTbidDeSU = false;
      bool twneuWKIPU = false;
      bool mSpzsTfIiu = false;
      bool ckJTSKFtuL = false;
      bool iLSCXBWPMZ = false;
      bool KibtpyuThO = false;
      bool ytuWqImTLj = false;
      bool RPNDlaAnar = false;
      bool xPwJjsJOdT = false;
      bool PkMgNnPuKP = false;
      bool NCDbHtVXHO = false;
      string lHQJtWOSwU;
      string hTsCuzkszD;
      string psxmJikjGK;
      string USnJwEtoIc;
      string MZrXcSarYu;
      string XYXhxrJdAL;
      string kdLkAOfiFp;
      string FujWpPBZKq;
      string HrLLlwuFLD;
      string uPoxqiOGXN;
      string lqmhpboBqh;
      string qjTJDrRAzD;
      string TZXBtoGleH;
      string BuBwEQFdVK;
      string HsOdMLuftz;
      string QOHTsMTlmA;
      string VCVifwhWEl;
      string mneowZLtni;
      string tZrfqmnhCq;
      string xSpUnEXexQ;
      if(lHQJtWOSwU == lqmhpboBqh){cXaHLciSWT = true;}
      else if(lqmhpboBqh == lHQJtWOSwU){twneuWKIPU = true;}
      if(hTsCuzkszD == qjTJDrRAzD){BZxDGuJprs = true;}
      else if(qjTJDrRAzD == hTsCuzkszD){mSpzsTfIiu = true;}
      if(psxmJikjGK == TZXBtoGleH){IAUNoTxJAq = true;}
      else if(TZXBtoGleH == psxmJikjGK){ckJTSKFtuL = true;}
      if(USnJwEtoIc == BuBwEQFdVK){CfwXGVzkTN = true;}
      else if(BuBwEQFdVK == USnJwEtoIc){iLSCXBWPMZ = true;}
      if(MZrXcSarYu == HsOdMLuftz){DUKipWVlOr = true;}
      else if(HsOdMLuftz == MZrXcSarYu){KibtpyuThO = true;}
      if(XYXhxrJdAL == QOHTsMTlmA){ugmEIcDNRq = true;}
      else if(QOHTsMTlmA == XYXhxrJdAL){ytuWqImTLj = true;}
      if(kdLkAOfiFp == VCVifwhWEl){eZRfQVcYxj = true;}
      else if(VCVifwhWEl == kdLkAOfiFp){RPNDlaAnar = true;}
      if(FujWpPBZKq == mneowZLtni){wYWdompkWR = true;}
      if(HrLLlwuFLD == tZrfqmnhCq){yLtIwVrqPc = true;}
      if(uPoxqiOGXN == xSpUnEXexQ){RkTbidDeSU = true;}
      while(mneowZLtni == FujWpPBZKq){xPwJjsJOdT = true;}
      while(tZrfqmnhCq == tZrfqmnhCq){PkMgNnPuKP = true;}
      while(xSpUnEXexQ == xSpUnEXexQ){NCDbHtVXHO = true;}
      if(cXaHLciSWT == true){cXaHLciSWT = false;}
      if(BZxDGuJprs == true){BZxDGuJprs = false;}
      if(IAUNoTxJAq == true){IAUNoTxJAq = false;}
      if(CfwXGVzkTN == true){CfwXGVzkTN = false;}
      if(DUKipWVlOr == true){DUKipWVlOr = false;}
      if(ugmEIcDNRq == true){ugmEIcDNRq = false;}
      if(eZRfQVcYxj == true){eZRfQVcYxj = false;}
      if(wYWdompkWR == true){wYWdompkWR = false;}
      if(yLtIwVrqPc == true){yLtIwVrqPc = false;}
      if(RkTbidDeSU == true){RkTbidDeSU = false;}
      if(twneuWKIPU == true){twneuWKIPU = false;}
      if(mSpzsTfIiu == true){mSpzsTfIiu = false;}
      if(ckJTSKFtuL == true){ckJTSKFtuL = false;}
      if(iLSCXBWPMZ == true){iLSCXBWPMZ = false;}
      if(KibtpyuThO == true){KibtpyuThO = false;}
      if(ytuWqImTLj == true){ytuWqImTLj = false;}
      if(RPNDlaAnar == true){RPNDlaAnar = false;}
      if(xPwJjsJOdT == true){xPwJjsJOdT = false;}
      if(PkMgNnPuKP == true){PkMgNnPuKP = false;}
      if(NCDbHtVXHO == true){NCDbHtVXHO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUUGXEBMMO
{ 
  void GSuzeGmYEb()
  { 
      bool zJVlDVcQSF = false;
      bool JTEBlpUAta = false;
      bool KEFVzfwUOn = false;
      bool pHCARuDDGF = false;
      bool wHPJgFfpCt = false;
      bool wnOVAuEAlX = false;
      bool YIBePCQEjp = false;
      bool lQsndCnuot = false;
      bool AGRTrBrfzV = false;
      bool qCRigmFktd = false;
      bool nbGMHeuaqy = false;
      bool HILrWSqhmN = false;
      bool JkFNyizJHq = false;
      bool xCBKFXzEMM = false;
      bool GRnBOiqZLN = false;
      bool uXygUDWsOX = false;
      bool ekSAAEGBlz = false;
      bool TlUZHqwEyO = false;
      bool rYysuYEUoC = false;
      bool BFpngUznAK = false;
      string HAoBGESVnz;
      string VRQJbcwfuj;
      string LkqBlfPnYR;
      string cAlJmppaDb;
      string oYjckzWrHP;
      string soKBzWImPZ;
      string oexWVUeGWk;
      string mUcSumANQl;
      string IWfIXnpkJQ;
      string gCLcmJaNGP;
      string UPVVcXLqGM;
      string VuWcRRzoyh;
      string etwGDkIAfk;
      string LmHBQrAKfA;
      string bzdxtlehKU;
      string KlOYkZSPSq;
      string PKKUAimVMY;
      string QnIyFeQzLQ;
      string FZpKaZXiPp;
      string YkrnjRnIxL;
      if(HAoBGESVnz == UPVVcXLqGM){zJVlDVcQSF = true;}
      else if(UPVVcXLqGM == HAoBGESVnz){nbGMHeuaqy = true;}
      if(VRQJbcwfuj == VuWcRRzoyh){JTEBlpUAta = true;}
      else if(VuWcRRzoyh == VRQJbcwfuj){HILrWSqhmN = true;}
      if(LkqBlfPnYR == etwGDkIAfk){KEFVzfwUOn = true;}
      else if(etwGDkIAfk == LkqBlfPnYR){JkFNyizJHq = true;}
      if(cAlJmppaDb == LmHBQrAKfA){pHCARuDDGF = true;}
      else if(LmHBQrAKfA == cAlJmppaDb){xCBKFXzEMM = true;}
      if(oYjckzWrHP == bzdxtlehKU){wHPJgFfpCt = true;}
      else if(bzdxtlehKU == oYjckzWrHP){GRnBOiqZLN = true;}
      if(soKBzWImPZ == KlOYkZSPSq){wnOVAuEAlX = true;}
      else if(KlOYkZSPSq == soKBzWImPZ){uXygUDWsOX = true;}
      if(oexWVUeGWk == PKKUAimVMY){YIBePCQEjp = true;}
      else if(PKKUAimVMY == oexWVUeGWk){ekSAAEGBlz = true;}
      if(mUcSumANQl == QnIyFeQzLQ){lQsndCnuot = true;}
      if(IWfIXnpkJQ == FZpKaZXiPp){AGRTrBrfzV = true;}
      if(gCLcmJaNGP == YkrnjRnIxL){qCRigmFktd = true;}
      while(QnIyFeQzLQ == mUcSumANQl){TlUZHqwEyO = true;}
      while(FZpKaZXiPp == FZpKaZXiPp){rYysuYEUoC = true;}
      while(YkrnjRnIxL == YkrnjRnIxL){BFpngUznAK = true;}
      if(zJVlDVcQSF == true){zJVlDVcQSF = false;}
      if(JTEBlpUAta == true){JTEBlpUAta = false;}
      if(KEFVzfwUOn == true){KEFVzfwUOn = false;}
      if(pHCARuDDGF == true){pHCARuDDGF = false;}
      if(wHPJgFfpCt == true){wHPJgFfpCt = false;}
      if(wnOVAuEAlX == true){wnOVAuEAlX = false;}
      if(YIBePCQEjp == true){YIBePCQEjp = false;}
      if(lQsndCnuot == true){lQsndCnuot = false;}
      if(AGRTrBrfzV == true){AGRTrBrfzV = false;}
      if(qCRigmFktd == true){qCRigmFktd = false;}
      if(nbGMHeuaqy == true){nbGMHeuaqy = false;}
      if(HILrWSqhmN == true){HILrWSqhmN = false;}
      if(JkFNyizJHq == true){JkFNyizJHq = false;}
      if(xCBKFXzEMM == true){xCBKFXzEMM = false;}
      if(GRnBOiqZLN == true){GRnBOiqZLN = false;}
      if(uXygUDWsOX == true){uXygUDWsOX = false;}
      if(ekSAAEGBlz == true){ekSAAEGBlz = false;}
      if(TlUZHqwEyO == true){TlUZHqwEyO = false;}
      if(rYysuYEUoC == true){rYysuYEUoC = false;}
      if(BFpngUznAK == true){BFpngUznAK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PDYUYPXVWW
{ 
  void iBjOdQHIBZ()
  { 
      bool wtLwZLsJjE = false;
      bool nGtZRrMbwF = false;
      bool MNzOYTPASC = false;
      bool DsCQobpKry = false;
      bool YehCuFfYne = false;
      bool NNylGhuwXF = false;
      bool usphAtEcjp = false;
      bool BBiyggewTT = false;
      bool mqLnoptPKG = false;
      bool gsmmCfnACA = false;
      bool ADnycLdAFY = false;
      bool DycEREgCsK = false;
      bool AnSdIHOwuB = false;
      bool retSSjCNKc = false;
      bool LsKkDhQiVy = false;
      bool ylHrAMjKoU = false;
      bool whFEfYEJkg = false;
      bool BTqPyGdhZZ = false;
      bool qfawCGXCSG = false;
      bool ArXpfcnGFe = false;
      string PAqZNIPuwI;
      string uuaCSguOFg;
      string TgZAiuaKrP;
      string gBMLqPAMwA;
      string BCmKUCYqbo;
      string pclUGhapqS;
      string hFDgasiOLC;
      string fiSFeRtOff;
      string VihDYEPrFI;
      string nKVdSwzGia;
      string TJfYJHJfoo;
      string nLKKwyWAHW;
      string cqJCNVMoli;
      string RmeELLDJsR;
      string tjCPTczKgU;
      string YzzMxcAcKm;
      string tUtGXBfFyj;
      string tNGobsntik;
      string VCHRJRnSGi;
      string LZyFWZourS;
      if(PAqZNIPuwI == TJfYJHJfoo){wtLwZLsJjE = true;}
      else if(TJfYJHJfoo == PAqZNIPuwI){ADnycLdAFY = true;}
      if(uuaCSguOFg == nLKKwyWAHW){nGtZRrMbwF = true;}
      else if(nLKKwyWAHW == uuaCSguOFg){DycEREgCsK = true;}
      if(TgZAiuaKrP == cqJCNVMoli){MNzOYTPASC = true;}
      else if(cqJCNVMoli == TgZAiuaKrP){AnSdIHOwuB = true;}
      if(gBMLqPAMwA == RmeELLDJsR){DsCQobpKry = true;}
      else if(RmeELLDJsR == gBMLqPAMwA){retSSjCNKc = true;}
      if(BCmKUCYqbo == tjCPTczKgU){YehCuFfYne = true;}
      else if(tjCPTczKgU == BCmKUCYqbo){LsKkDhQiVy = true;}
      if(pclUGhapqS == YzzMxcAcKm){NNylGhuwXF = true;}
      else if(YzzMxcAcKm == pclUGhapqS){ylHrAMjKoU = true;}
      if(hFDgasiOLC == tUtGXBfFyj){usphAtEcjp = true;}
      else if(tUtGXBfFyj == hFDgasiOLC){whFEfYEJkg = true;}
      if(fiSFeRtOff == tNGobsntik){BBiyggewTT = true;}
      if(VihDYEPrFI == VCHRJRnSGi){mqLnoptPKG = true;}
      if(nKVdSwzGia == LZyFWZourS){gsmmCfnACA = true;}
      while(tNGobsntik == fiSFeRtOff){BTqPyGdhZZ = true;}
      while(VCHRJRnSGi == VCHRJRnSGi){qfawCGXCSG = true;}
      while(LZyFWZourS == LZyFWZourS){ArXpfcnGFe = true;}
      if(wtLwZLsJjE == true){wtLwZLsJjE = false;}
      if(nGtZRrMbwF == true){nGtZRrMbwF = false;}
      if(MNzOYTPASC == true){MNzOYTPASC = false;}
      if(DsCQobpKry == true){DsCQobpKry = false;}
      if(YehCuFfYne == true){YehCuFfYne = false;}
      if(NNylGhuwXF == true){NNylGhuwXF = false;}
      if(usphAtEcjp == true){usphAtEcjp = false;}
      if(BBiyggewTT == true){BBiyggewTT = false;}
      if(mqLnoptPKG == true){mqLnoptPKG = false;}
      if(gsmmCfnACA == true){gsmmCfnACA = false;}
      if(ADnycLdAFY == true){ADnycLdAFY = false;}
      if(DycEREgCsK == true){DycEREgCsK = false;}
      if(AnSdIHOwuB == true){AnSdIHOwuB = false;}
      if(retSSjCNKc == true){retSSjCNKc = false;}
      if(LsKkDhQiVy == true){LsKkDhQiVy = false;}
      if(ylHrAMjKoU == true){ylHrAMjKoU = false;}
      if(whFEfYEJkg == true){whFEfYEJkg = false;}
      if(BTqPyGdhZZ == true){BTqPyGdhZZ = false;}
      if(qfawCGXCSG == true){qfawCGXCSG = false;}
      if(ArXpfcnGFe == true){ArXpfcnGFe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AQIIFMTAAB
{ 
  void HmFUqYfVgp()
  { 
      bool kkDVjTHdXb = false;
      bool AVsBPzqjlw = false;
      bool ESRxNBgNCi = false;
      bool inqjWgFUgq = false;
      bool MKiSPMgLty = false;
      bool JKJHpRSGIi = false;
      bool lsbnsMdJdh = false;
      bool sVCtjsjzhB = false;
      bool TVSDYYdjsF = false;
      bool OzMxESitZD = false;
      bool hXgMEnHOWx = false;
      bool hSYHOQZXPT = false;
      bool htPYTtJFpQ = false;
      bool JoZeSwnGzk = false;
      bool QPNuWuaFim = false;
      bool rLeFVnHHsK = false;
      bool dCYFnsstnS = false;
      bool bTYdDRfUBX = false;
      bool SEWCYyJUJe = false;
      bool ofNnGOqHHd = false;
      string JqGwCQQWih;
      string XeFmycPTPF;
      string CqLNSVBxOi;
      string oVnCSeCIuA;
      string zFlUhDlLwX;
      string qOtaPRercf;
      string PTHAsCpDTS;
      string ZGXOFxFpfO;
      string ioBqrZbNmA;
      string zJfOkfxlbf;
      string NiqcyjpeVR;
      string MoMOxZRQHT;
      string ZcQSSPaIcY;
      string ATOABAyXrH;
      string iwrUnKxQRL;
      string OfdHFkRXJh;
      string JhBwQsZMNw;
      string atXAjdjueI;
      string SJpRKUoGtP;
      string iZNKyBtuDu;
      if(JqGwCQQWih == NiqcyjpeVR){kkDVjTHdXb = true;}
      else if(NiqcyjpeVR == JqGwCQQWih){hXgMEnHOWx = true;}
      if(XeFmycPTPF == MoMOxZRQHT){AVsBPzqjlw = true;}
      else if(MoMOxZRQHT == XeFmycPTPF){hSYHOQZXPT = true;}
      if(CqLNSVBxOi == ZcQSSPaIcY){ESRxNBgNCi = true;}
      else if(ZcQSSPaIcY == CqLNSVBxOi){htPYTtJFpQ = true;}
      if(oVnCSeCIuA == ATOABAyXrH){inqjWgFUgq = true;}
      else if(ATOABAyXrH == oVnCSeCIuA){JoZeSwnGzk = true;}
      if(zFlUhDlLwX == iwrUnKxQRL){MKiSPMgLty = true;}
      else if(iwrUnKxQRL == zFlUhDlLwX){QPNuWuaFim = true;}
      if(qOtaPRercf == OfdHFkRXJh){JKJHpRSGIi = true;}
      else if(OfdHFkRXJh == qOtaPRercf){rLeFVnHHsK = true;}
      if(PTHAsCpDTS == JhBwQsZMNw){lsbnsMdJdh = true;}
      else if(JhBwQsZMNw == PTHAsCpDTS){dCYFnsstnS = true;}
      if(ZGXOFxFpfO == atXAjdjueI){sVCtjsjzhB = true;}
      if(ioBqrZbNmA == SJpRKUoGtP){TVSDYYdjsF = true;}
      if(zJfOkfxlbf == iZNKyBtuDu){OzMxESitZD = true;}
      while(atXAjdjueI == ZGXOFxFpfO){bTYdDRfUBX = true;}
      while(SJpRKUoGtP == SJpRKUoGtP){SEWCYyJUJe = true;}
      while(iZNKyBtuDu == iZNKyBtuDu){ofNnGOqHHd = true;}
      if(kkDVjTHdXb == true){kkDVjTHdXb = false;}
      if(AVsBPzqjlw == true){AVsBPzqjlw = false;}
      if(ESRxNBgNCi == true){ESRxNBgNCi = false;}
      if(inqjWgFUgq == true){inqjWgFUgq = false;}
      if(MKiSPMgLty == true){MKiSPMgLty = false;}
      if(JKJHpRSGIi == true){JKJHpRSGIi = false;}
      if(lsbnsMdJdh == true){lsbnsMdJdh = false;}
      if(sVCtjsjzhB == true){sVCtjsjzhB = false;}
      if(TVSDYYdjsF == true){TVSDYYdjsF = false;}
      if(OzMxESitZD == true){OzMxESitZD = false;}
      if(hXgMEnHOWx == true){hXgMEnHOWx = false;}
      if(hSYHOQZXPT == true){hSYHOQZXPT = false;}
      if(htPYTtJFpQ == true){htPYTtJFpQ = false;}
      if(JoZeSwnGzk == true){JoZeSwnGzk = false;}
      if(QPNuWuaFim == true){QPNuWuaFim = false;}
      if(rLeFVnHHsK == true){rLeFVnHHsK = false;}
      if(dCYFnsstnS == true){dCYFnsstnS = false;}
      if(bTYdDRfUBX == true){bTYdDRfUBX = false;}
      if(SEWCYyJUJe == true){SEWCYyJUJe = false;}
      if(ofNnGOqHHd == true){ofNnGOqHHd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPYFDKAEPA
{ 
  void kGshQKoDXE()
  { 
      bool TyKVwMeJWa = false;
      bool wwNEWVthky = false;
      bool HSgwbpqrcI = false;
      bool VmTMYTmauc = false;
      bool dqQPDaKQfQ = false;
      bool PFzhnBQNtF = false;
      bool UmfOEJcBeC = false;
      bool iTmITPBRrA = false;
      bool eZLLsPnkYW = false;
      bool CYgpHqLCLt = false;
      bool xJkdhwSqOX = false;
      bool zzVsZubTVn = false;
      bool VqbHzJlwAc = false;
      bool EyFyDVogdw = false;
      bool xwWBXDCmPM = false;
      bool OqgWYFhddX = false;
      bool JWqlSBsXpE = false;
      bool GtpYqYUajw = false;
      bool HzgmNNRiYx = false;
      bool nKDFmaFkhV = false;
      string IyzPkyrWVH;
      string NxokNRtYif;
      string YIaNVKKeLZ;
      string cuJVmiHSQJ;
      string PZonbtEgwo;
      string yRDGpAXktZ;
      string nMLweRnTye;
      string KbIYQySmlb;
      string FdiWaKrCel;
      string LVYpVCOsJK;
      string GkhQdVJdpq;
      string hjzRUKdnUT;
      string YknMToDSDO;
      string jZdbVUuRrE;
      string BOMnEaVGVL;
      string YaYokUxVxo;
      string SqZaHIGXwz;
      string PLuPSKYAIs;
      string SxwrpJAnpA;
      string XYUDlJnkfu;
      if(IyzPkyrWVH == GkhQdVJdpq){TyKVwMeJWa = true;}
      else if(GkhQdVJdpq == IyzPkyrWVH){xJkdhwSqOX = true;}
      if(NxokNRtYif == hjzRUKdnUT){wwNEWVthky = true;}
      else if(hjzRUKdnUT == NxokNRtYif){zzVsZubTVn = true;}
      if(YIaNVKKeLZ == YknMToDSDO){HSgwbpqrcI = true;}
      else if(YknMToDSDO == YIaNVKKeLZ){VqbHzJlwAc = true;}
      if(cuJVmiHSQJ == jZdbVUuRrE){VmTMYTmauc = true;}
      else if(jZdbVUuRrE == cuJVmiHSQJ){EyFyDVogdw = true;}
      if(PZonbtEgwo == BOMnEaVGVL){dqQPDaKQfQ = true;}
      else if(BOMnEaVGVL == PZonbtEgwo){xwWBXDCmPM = true;}
      if(yRDGpAXktZ == YaYokUxVxo){PFzhnBQNtF = true;}
      else if(YaYokUxVxo == yRDGpAXktZ){OqgWYFhddX = true;}
      if(nMLweRnTye == SqZaHIGXwz){UmfOEJcBeC = true;}
      else if(SqZaHIGXwz == nMLweRnTye){JWqlSBsXpE = true;}
      if(KbIYQySmlb == PLuPSKYAIs){iTmITPBRrA = true;}
      if(FdiWaKrCel == SxwrpJAnpA){eZLLsPnkYW = true;}
      if(LVYpVCOsJK == XYUDlJnkfu){CYgpHqLCLt = true;}
      while(PLuPSKYAIs == KbIYQySmlb){GtpYqYUajw = true;}
      while(SxwrpJAnpA == SxwrpJAnpA){HzgmNNRiYx = true;}
      while(XYUDlJnkfu == XYUDlJnkfu){nKDFmaFkhV = true;}
      if(TyKVwMeJWa == true){TyKVwMeJWa = false;}
      if(wwNEWVthky == true){wwNEWVthky = false;}
      if(HSgwbpqrcI == true){HSgwbpqrcI = false;}
      if(VmTMYTmauc == true){VmTMYTmauc = false;}
      if(dqQPDaKQfQ == true){dqQPDaKQfQ = false;}
      if(PFzhnBQNtF == true){PFzhnBQNtF = false;}
      if(UmfOEJcBeC == true){UmfOEJcBeC = false;}
      if(iTmITPBRrA == true){iTmITPBRrA = false;}
      if(eZLLsPnkYW == true){eZLLsPnkYW = false;}
      if(CYgpHqLCLt == true){CYgpHqLCLt = false;}
      if(xJkdhwSqOX == true){xJkdhwSqOX = false;}
      if(zzVsZubTVn == true){zzVsZubTVn = false;}
      if(VqbHzJlwAc == true){VqbHzJlwAc = false;}
      if(EyFyDVogdw == true){EyFyDVogdw = false;}
      if(xwWBXDCmPM == true){xwWBXDCmPM = false;}
      if(OqgWYFhddX == true){OqgWYFhddX = false;}
      if(JWqlSBsXpE == true){JWqlSBsXpE = false;}
      if(GtpYqYUajw == true){GtpYqYUajw = false;}
      if(HzgmNNRiYx == true){HzgmNNRiYx = false;}
      if(nKDFmaFkhV == true){nKDFmaFkhV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYCVBUOEHI
{ 
  void cnXkHieMlm()
  { 
      bool ppxUgxqGMq = false;
      bool VgMuqSuYZE = false;
      bool BeDpfqhMiI = false;
      bool BJSMyaAQtm = false;
      bool XhbkQyBJlN = false;
      bool CJuEQKlHop = false;
      bool OeXDpLNAxQ = false;
      bool ReemgSCRYg = false;
      bool oXZUFrOOum = false;
      bool nraEXsJXuE = false;
      bool kBLVwXdIXy = false;
      bool HThIAqEDyx = false;
      bool xzFJbYDaOm = false;
      bool IeVUunLEYh = false;
      bool NGpxeUKSDg = false;
      bool nGZyHkwCsW = false;
      bool TCsjocxNML = false;
      bool ezdPjpIHdH = false;
      bool OkWgyBEXMJ = false;
      bool rJLCNKMFIC = false;
      string YdAraIkjky;
      string BobELmPlNl;
      string ibmPeVLnXm;
      string egSZHbrClx;
      string HXgYPgRaRp;
      string BzgIcwpkNF;
      string wxLySUVCxj;
      string tNzPdKtOzy;
      string EjVhkfAKwK;
      string kHogAKMiGu;
      string LOdhunzQdS;
      string CbkOAMadMm;
      string TKFmymXRPT;
      string yLHEmoGnlx;
      string fjfdIJWZfn;
      string iiWSaAJqjI;
      string QgBKTpTgbL;
      string GlqPGjebdn;
      string QykbjPoncl;
      string fOEdfyiUJR;
      if(YdAraIkjky == LOdhunzQdS){ppxUgxqGMq = true;}
      else if(LOdhunzQdS == YdAraIkjky){kBLVwXdIXy = true;}
      if(BobELmPlNl == CbkOAMadMm){VgMuqSuYZE = true;}
      else if(CbkOAMadMm == BobELmPlNl){HThIAqEDyx = true;}
      if(ibmPeVLnXm == TKFmymXRPT){BeDpfqhMiI = true;}
      else if(TKFmymXRPT == ibmPeVLnXm){xzFJbYDaOm = true;}
      if(egSZHbrClx == yLHEmoGnlx){BJSMyaAQtm = true;}
      else if(yLHEmoGnlx == egSZHbrClx){IeVUunLEYh = true;}
      if(HXgYPgRaRp == fjfdIJWZfn){XhbkQyBJlN = true;}
      else if(fjfdIJWZfn == HXgYPgRaRp){NGpxeUKSDg = true;}
      if(BzgIcwpkNF == iiWSaAJqjI){CJuEQKlHop = true;}
      else if(iiWSaAJqjI == BzgIcwpkNF){nGZyHkwCsW = true;}
      if(wxLySUVCxj == QgBKTpTgbL){OeXDpLNAxQ = true;}
      else if(QgBKTpTgbL == wxLySUVCxj){TCsjocxNML = true;}
      if(tNzPdKtOzy == GlqPGjebdn){ReemgSCRYg = true;}
      if(EjVhkfAKwK == QykbjPoncl){oXZUFrOOum = true;}
      if(kHogAKMiGu == fOEdfyiUJR){nraEXsJXuE = true;}
      while(GlqPGjebdn == tNzPdKtOzy){ezdPjpIHdH = true;}
      while(QykbjPoncl == QykbjPoncl){OkWgyBEXMJ = true;}
      while(fOEdfyiUJR == fOEdfyiUJR){rJLCNKMFIC = true;}
      if(ppxUgxqGMq == true){ppxUgxqGMq = false;}
      if(VgMuqSuYZE == true){VgMuqSuYZE = false;}
      if(BeDpfqhMiI == true){BeDpfqhMiI = false;}
      if(BJSMyaAQtm == true){BJSMyaAQtm = false;}
      if(XhbkQyBJlN == true){XhbkQyBJlN = false;}
      if(CJuEQKlHop == true){CJuEQKlHop = false;}
      if(OeXDpLNAxQ == true){OeXDpLNAxQ = false;}
      if(ReemgSCRYg == true){ReemgSCRYg = false;}
      if(oXZUFrOOum == true){oXZUFrOOum = false;}
      if(nraEXsJXuE == true){nraEXsJXuE = false;}
      if(kBLVwXdIXy == true){kBLVwXdIXy = false;}
      if(HThIAqEDyx == true){HThIAqEDyx = false;}
      if(xzFJbYDaOm == true){xzFJbYDaOm = false;}
      if(IeVUunLEYh == true){IeVUunLEYh = false;}
      if(NGpxeUKSDg == true){NGpxeUKSDg = false;}
      if(nGZyHkwCsW == true){nGZyHkwCsW = false;}
      if(TCsjocxNML == true){TCsjocxNML = false;}
      if(ezdPjpIHdH == true){ezdPjpIHdH = false;}
      if(OkWgyBEXMJ == true){OkWgyBEXMJ = false;}
      if(rJLCNKMFIC == true){rJLCNKMFIC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DOIQWJHJIH
{ 
  void pgbLqgQnPi()
  { 
      bool OGLrHaakYU = false;
      bool TOPpzyYfkf = false;
      bool YMSPMHLJFK = false;
      bool rrDhtqWWkn = false;
      bool VcsmsDOUiQ = false;
      bool dCgaTCnweA = false;
      bool OReNcaKhuH = false;
      bool aBuxKwTeVJ = false;
      bool rpZofoLcNr = false;
      bool DarkYExeJS = false;
      bool rgYbpcHjPX = false;
      bool iIZVHYqphm = false;
      bool PhTDEzIKXG = false;
      bool ynVDQLQyyD = false;
      bool gaMoJtAWcA = false;
      bool MHxWDKMVWp = false;
      bool TxLJZtmWEu = false;
      bool HsqdFnUesK = false;
      bool zlgXsqqzzF = false;
      bool yubIjjODOO = false;
      string ikbaAnoJFz;
      string UpMifOEROZ;
      string kjIPJMNral;
      string bSkknCXYia;
      string eaqNgLytdS;
      string jJzGFzbMRm;
      string ZxhSWBFbuc;
      string peimtKrtix;
      string OTNIBRSdfn;
      string aLHwAhsXqe;
      string GVyBbEaLMt;
      string HhdTXGiYRE;
      string ibwHCeXmlM;
      string QTDDqrULfw;
      string qHRkfrgnXs;
      string yTGlwdZpzx;
      string gnYzdmdZbf;
      string lXrUNaKKaJ;
      string yiOrOxNRHM;
      string SdLiODiRHs;
      if(ikbaAnoJFz == GVyBbEaLMt){OGLrHaakYU = true;}
      else if(GVyBbEaLMt == ikbaAnoJFz){rgYbpcHjPX = true;}
      if(UpMifOEROZ == HhdTXGiYRE){TOPpzyYfkf = true;}
      else if(HhdTXGiYRE == UpMifOEROZ){iIZVHYqphm = true;}
      if(kjIPJMNral == ibwHCeXmlM){YMSPMHLJFK = true;}
      else if(ibwHCeXmlM == kjIPJMNral){PhTDEzIKXG = true;}
      if(bSkknCXYia == QTDDqrULfw){rrDhtqWWkn = true;}
      else if(QTDDqrULfw == bSkknCXYia){ynVDQLQyyD = true;}
      if(eaqNgLytdS == qHRkfrgnXs){VcsmsDOUiQ = true;}
      else if(qHRkfrgnXs == eaqNgLytdS){gaMoJtAWcA = true;}
      if(jJzGFzbMRm == yTGlwdZpzx){dCgaTCnweA = true;}
      else if(yTGlwdZpzx == jJzGFzbMRm){MHxWDKMVWp = true;}
      if(ZxhSWBFbuc == gnYzdmdZbf){OReNcaKhuH = true;}
      else if(gnYzdmdZbf == ZxhSWBFbuc){TxLJZtmWEu = true;}
      if(peimtKrtix == lXrUNaKKaJ){aBuxKwTeVJ = true;}
      if(OTNIBRSdfn == yiOrOxNRHM){rpZofoLcNr = true;}
      if(aLHwAhsXqe == SdLiODiRHs){DarkYExeJS = true;}
      while(lXrUNaKKaJ == peimtKrtix){HsqdFnUesK = true;}
      while(yiOrOxNRHM == yiOrOxNRHM){zlgXsqqzzF = true;}
      while(SdLiODiRHs == SdLiODiRHs){yubIjjODOO = true;}
      if(OGLrHaakYU == true){OGLrHaakYU = false;}
      if(TOPpzyYfkf == true){TOPpzyYfkf = false;}
      if(YMSPMHLJFK == true){YMSPMHLJFK = false;}
      if(rrDhtqWWkn == true){rrDhtqWWkn = false;}
      if(VcsmsDOUiQ == true){VcsmsDOUiQ = false;}
      if(dCgaTCnweA == true){dCgaTCnweA = false;}
      if(OReNcaKhuH == true){OReNcaKhuH = false;}
      if(aBuxKwTeVJ == true){aBuxKwTeVJ = false;}
      if(rpZofoLcNr == true){rpZofoLcNr = false;}
      if(DarkYExeJS == true){DarkYExeJS = false;}
      if(rgYbpcHjPX == true){rgYbpcHjPX = false;}
      if(iIZVHYqphm == true){iIZVHYqphm = false;}
      if(PhTDEzIKXG == true){PhTDEzIKXG = false;}
      if(ynVDQLQyyD == true){ynVDQLQyyD = false;}
      if(gaMoJtAWcA == true){gaMoJtAWcA = false;}
      if(MHxWDKMVWp == true){MHxWDKMVWp = false;}
      if(TxLJZtmWEu == true){TxLJZtmWEu = false;}
      if(HsqdFnUesK == true){HsqdFnUesK = false;}
      if(zlgXsqqzzF == true){zlgXsqqzzF = false;}
      if(yubIjjODOO == true){yubIjjODOO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTCZWETOPM
{ 
  void OMpIexkpex()
  { 
      bool sIThSVqdHC = false;
      bool kqygbtFQuE = false;
      bool GLyOrAuDZf = false;
      bool tljehEbgfr = false;
      bool dCxTqXzBVy = false;
      bool OWirsgKEoS = false;
      bool anEaHyHSyW = false;
      bool RYkDZDNeXT = false;
      bool BsgaQXCrkB = false;
      bool tWqMQpxWLr = false;
      bool QfCyfpkfRo = false;
      bool SegURhHcKj = false;
      bool uOhxcugXlj = false;
      bool FqTeCUqhua = false;
      bool lWawiPoVui = false;
      bool iUMbxCyEVk = false;
      bool IMsgiaLCRw = false;
      bool pYhixYmlOM = false;
      bool FKbDBkeqhA = false;
      bool WmLKRYcsMH = false;
      string mKhYhUNUns;
      string lmaIGPZzhK;
      string AySYPRdGFK;
      string lQTGpfPoFe;
      string azZGsbyLUh;
      string gVhGrnqIIQ;
      string pGOcHUSTSa;
      string zktDiAYMfm;
      string SSlXdQiMOB;
      string oHfnnUkwzX;
      string IdsthuaeXq;
      string PecUxXUqzp;
      string lGFQkrFFON;
      string PcNHeoZqoh;
      string pDoXlKdKqQ;
      string zswIkCYbIp;
      string oUPJamQUpI;
      string xcCRAiRgda;
      string NuOyOVfFVb;
      string PxhyrUnewz;
      if(mKhYhUNUns == IdsthuaeXq){sIThSVqdHC = true;}
      else if(IdsthuaeXq == mKhYhUNUns){QfCyfpkfRo = true;}
      if(lmaIGPZzhK == PecUxXUqzp){kqygbtFQuE = true;}
      else if(PecUxXUqzp == lmaIGPZzhK){SegURhHcKj = true;}
      if(AySYPRdGFK == lGFQkrFFON){GLyOrAuDZf = true;}
      else if(lGFQkrFFON == AySYPRdGFK){uOhxcugXlj = true;}
      if(lQTGpfPoFe == PcNHeoZqoh){tljehEbgfr = true;}
      else if(PcNHeoZqoh == lQTGpfPoFe){FqTeCUqhua = true;}
      if(azZGsbyLUh == pDoXlKdKqQ){dCxTqXzBVy = true;}
      else if(pDoXlKdKqQ == azZGsbyLUh){lWawiPoVui = true;}
      if(gVhGrnqIIQ == zswIkCYbIp){OWirsgKEoS = true;}
      else if(zswIkCYbIp == gVhGrnqIIQ){iUMbxCyEVk = true;}
      if(pGOcHUSTSa == oUPJamQUpI){anEaHyHSyW = true;}
      else if(oUPJamQUpI == pGOcHUSTSa){IMsgiaLCRw = true;}
      if(zktDiAYMfm == xcCRAiRgda){RYkDZDNeXT = true;}
      if(SSlXdQiMOB == NuOyOVfFVb){BsgaQXCrkB = true;}
      if(oHfnnUkwzX == PxhyrUnewz){tWqMQpxWLr = true;}
      while(xcCRAiRgda == zktDiAYMfm){pYhixYmlOM = true;}
      while(NuOyOVfFVb == NuOyOVfFVb){FKbDBkeqhA = true;}
      while(PxhyrUnewz == PxhyrUnewz){WmLKRYcsMH = true;}
      if(sIThSVqdHC == true){sIThSVqdHC = false;}
      if(kqygbtFQuE == true){kqygbtFQuE = false;}
      if(GLyOrAuDZf == true){GLyOrAuDZf = false;}
      if(tljehEbgfr == true){tljehEbgfr = false;}
      if(dCxTqXzBVy == true){dCxTqXzBVy = false;}
      if(OWirsgKEoS == true){OWirsgKEoS = false;}
      if(anEaHyHSyW == true){anEaHyHSyW = false;}
      if(RYkDZDNeXT == true){RYkDZDNeXT = false;}
      if(BsgaQXCrkB == true){BsgaQXCrkB = false;}
      if(tWqMQpxWLr == true){tWqMQpxWLr = false;}
      if(QfCyfpkfRo == true){QfCyfpkfRo = false;}
      if(SegURhHcKj == true){SegURhHcKj = false;}
      if(uOhxcugXlj == true){uOhxcugXlj = false;}
      if(FqTeCUqhua == true){FqTeCUqhua = false;}
      if(lWawiPoVui == true){lWawiPoVui = false;}
      if(iUMbxCyEVk == true){iUMbxCyEVk = false;}
      if(IMsgiaLCRw == true){IMsgiaLCRw = false;}
      if(pYhixYmlOM == true){pYhixYmlOM = false;}
      if(FKbDBkeqhA == true){FKbDBkeqhA = false;}
      if(WmLKRYcsMH == true){WmLKRYcsMH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKIVYUOOAX
{ 
  void nYIhUVLkTp()
  { 
      bool cCKGhXqbzk = false;
      bool tgnaOMrynp = false;
      bool WxEnCGTwZL = false;
      bool zwHqPcIRsK = false;
      bool VNiZwriESC = false;
      bool AdtSOfxWDb = false;
      bool EuBmlxYwLk = false;
      bool EZEdUJNeqJ = false;
      bool WOdXLUCocj = false;
      bool elNRFaLunz = false;
      bool SmsgyZYQyE = false;
      bool RSesFoRdbQ = false;
      bool ujSaFRMmXs = false;
      bool xRqrqiUwZk = false;
      bool ukpXRMHTMQ = false;
      bool JgTWDhTRaf = false;
      bool NlrEGzblCV = false;
      bool TUEqUJstJs = false;
      bool KrZHjQyTnI = false;
      bool PDUsWIrlRR = false;
      string KrHiyVdiBj;
      string tFUiZNIMAM;
      string zjTDJCTMMb;
      string oylqqzKLag;
      string lsbNmfEktu;
      string nIgDraXEZu;
      string BQVZuuTcra;
      string DwkSaFIFPc;
      string xhSRnfQhzQ;
      string aGlfeVXCSr;
      string LasTqqWNbl;
      string SSnwxSyDkO;
      string eldbAxJFnF;
      string hFmXQVoyaw;
      string JCFNyIRphL;
      string WUQEMZxRSs;
      string gQZWEMfPea;
      string dzcoEbfQcr;
      string eTXbhNohKq;
      string YXfgPsciJk;
      if(KrHiyVdiBj == LasTqqWNbl){cCKGhXqbzk = true;}
      else if(LasTqqWNbl == KrHiyVdiBj){SmsgyZYQyE = true;}
      if(tFUiZNIMAM == SSnwxSyDkO){tgnaOMrynp = true;}
      else if(SSnwxSyDkO == tFUiZNIMAM){RSesFoRdbQ = true;}
      if(zjTDJCTMMb == eldbAxJFnF){WxEnCGTwZL = true;}
      else if(eldbAxJFnF == zjTDJCTMMb){ujSaFRMmXs = true;}
      if(oylqqzKLag == hFmXQVoyaw){zwHqPcIRsK = true;}
      else if(hFmXQVoyaw == oylqqzKLag){xRqrqiUwZk = true;}
      if(lsbNmfEktu == JCFNyIRphL){VNiZwriESC = true;}
      else if(JCFNyIRphL == lsbNmfEktu){ukpXRMHTMQ = true;}
      if(nIgDraXEZu == WUQEMZxRSs){AdtSOfxWDb = true;}
      else if(WUQEMZxRSs == nIgDraXEZu){JgTWDhTRaf = true;}
      if(BQVZuuTcra == gQZWEMfPea){EuBmlxYwLk = true;}
      else if(gQZWEMfPea == BQVZuuTcra){NlrEGzblCV = true;}
      if(DwkSaFIFPc == dzcoEbfQcr){EZEdUJNeqJ = true;}
      if(xhSRnfQhzQ == eTXbhNohKq){WOdXLUCocj = true;}
      if(aGlfeVXCSr == YXfgPsciJk){elNRFaLunz = true;}
      while(dzcoEbfQcr == DwkSaFIFPc){TUEqUJstJs = true;}
      while(eTXbhNohKq == eTXbhNohKq){KrZHjQyTnI = true;}
      while(YXfgPsciJk == YXfgPsciJk){PDUsWIrlRR = true;}
      if(cCKGhXqbzk == true){cCKGhXqbzk = false;}
      if(tgnaOMrynp == true){tgnaOMrynp = false;}
      if(WxEnCGTwZL == true){WxEnCGTwZL = false;}
      if(zwHqPcIRsK == true){zwHqPcIRsK = false;}
      if(VNiZwriESC == true){VNiZwriESC = false;}
      if(AdtSOfxWDb == true){AdtSOfxWDb = false;}
      if(EuBmlxYwLk == true){EuBmlxYwLk = false;}
      if(EZEdUJNeqJ == true){EZEdUJNeqJ = false;}
      if(WOdXLUCocj == true){WOdXLUCocj = false;}
      if(elNRFaLunz == true){elNRFaLunz = false;}
      if(SmsgyZYQyE == true){SmsgyZYQyE = false;}
      if(RSesFoRdbQ == true){RSesFoRdbQ = false;}
      if(ujSaFRMmXs == true){ujSaFRMmXs = false;}
      if(xRqrqiUwZk == true){xRqrqiUwZk = false;}
      if(ukpXRMHTMQ == true){ukpXRMHTMQ = false;}
      if(JgTWDhTRaf == true){JgTWDhTRaf = false;}
      if(NlrEGzblCV == true){NlrEGzblCV = false;}
      if(TUEqUJstJs == true){TUEqUJstJs = false;}
      if(KrZHjQyTnI == true){KrZHjQyTnI = false;}
      if(PDUsWIrlRR == true){PDUsWIrlRR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLZOFJWKWM
{ 
  void DgBzwkIrEe()
  { 
      bool AEGwNDuCMR = false;
      bool CHcRolkmQo = false;
      bool kYNqYxiQpy = false;
      bool MrFbJgpKhe = false;
      bool YlxOpqaerT = false;
      bool oMlcrbpOXQ = false;
      bool TeMNEKCBIH = false;
      bool wZElQzayBg = false;
      bool WDXVJAFbjh = false;
      bool pamRKsZjKf = false;
      bool oYWjXOIAMs = false;
      bool BrNpsPHpEE = false;
      bool FaQaRUmlaW = false;
      bool YqnUrxgnyt = false;
      bool qEOqfyNwXt = false;
      bool ljeGZOHwSC = false;
      bool bVYoTJEryu = false;
      bool iSqJMALZtS = false;
      bool GpNgjoLhuc = false;
      bool pkUuSVfZWW = false;
      string DxfYYTkmpA;
      string UWqlhkuBpL;
      string iMonGDzePq;
      string RsCmJXwmwY;
      string zVkNCRnTgy;
      string eaNfkqHrRU;
      string TFWyibUEbK;
      string nIERMMbblo;
      string PexRLpeVBS;
      string PEUaEsylea;
      string xirWJWWwSX;
      string OfFcFoHFlr;
      string wyCItjndMT;
      string NowLrfmaHo;
      string TiCdDjyqVP;
      string ksAldygicZ;
      string isizKZitkY;
      string BgxxYMuYFK;
      string kwHwhUoKgs;
      string zExgGZzDSc;
      if(DxfYYTkmpA == xirWJWWwSX){AEGwNDuCMR = true;}
      else if(xirWJWWwSX == DxfYYTkmpA){oYWjXOIAMs = true;}
      if(UWqlhkuBpL == OfFcFoHFlr){CHcRolkmQo = true;}
      else if(OfFcFoHFlr == UWqlhkuBpL){BrNpsPHpEE = true;}
      if(iMonGDzePq == wyCItjndMT){kYNqYxiQpy = true;}
      else if(wyCItjndMT == iMonGDzePq){FaQaRUmlaW = true;}
      if(RsCmJXwmwY == NowLrfmaHo){MrFbJgpKhe = true;}
      else if(NowLrfmaHo == RsCmJXwmwY){YqnUrxgnyt = true;}
      if(zVkNCRnTgy == TiCdDjyqVP){YlxOpqaerT = true;}
      else if(TiCdDjyqVP == zVkNCRnTgy){qEOqfyNwXt = true;}
      if(eaNfkqHrRU == ksAldygicZ){oMlcrbpOXQ = true;}
      else if(ksAldygicZ == eaNfkqHrRU){ljeGZOHwSC = true;}
      if(TFWyibUEbK == isizKZitkY){TeMNEKCBIH = true;}
      else if(isizKZitkY == TFWyibUEbK){bVYoTJEryu = true;}
      if(nIERMMbblo == BgxxYMuYFK){wZElQzayBg = true;}
      if(PexRLpeVBS == kwHwhUoKgs){WDXVJAFbjh = true;}
      if(PEUaEsylea == zExgGZzDSc){pamRKsZjKf = true;}
      while(BgxxYMuYFK == nIERMMbblo){iSqJMALZtS = true;}
      while(kwHwhUoKgs == kwHwhUoKgs){GpNgjoLhuc = true;}
      while(zExgGZzDSc == zExgGZzDSc){pkUuSVfZWW = true;}
      if(AEGwNDuCMR == true){AEGwNDuCMR = false;}
      if(CHcRolkmQo == true){CHcRolkmQo = false;}
      if(kYNqYxiQpy == true){kYNqYxiQpy = false;}
      if(MrFbJgpKhe == true){MrFbJgpKhe = false;}
      if(YlxOpqaerT == true){YlxOpqaerT = false;}
      if(oMlcrbpOXQ == true){oMlcrbpOXQ = false;}
      if(TeMNEKCBIH == true){TeMNEKCBIH = false;}
      if(wZElQzayBg == true){wZElQzayBg = false;}
      if(WDXVJAFbjh == true){WDXVJAFbjh = false;}
      if(pamRKsZjKf == true){pamRKsZjKf = false;}
      if(oYWjXOIAMs == true){oYWjXOIAMs = false;}
      if(BrNpsPHpEE == true){BrNpsPHpEE = false;}
      if(FaQaRUmlaW == true){FaQaRUmlaW = false;}
      if(YqnUrxgnyt == true){YqnUrxgnyt = false;}
      if(qEOqfyNwXt == true){qEOqfyNwXt = false;}
      if(ljeGZOHwSC == true){ljeGZOHwSC = false;}
      if(bVYoTJEryu == true){bVYoTJEryu = false;}
      if(iSqJMALZtS == true){iSqJMALZtS = false;}
      if(GpNgjoLhuc == true){GpNgjoLhuc = false;}
      if(pkUuSVfZWW == true){pkUuSVfZWW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWOJNYSEFW
{ 
  void xCpGfbxfdU()
  { 
      bool bLNmlBMlmf = false;
      bool GsEoLLydJR = false;
      bool DhSHzcLOGD = false;
      bool PhGsnQWenn = false;
      bool YmmAaSjGqe = false;
      bool NtgFzsrGnI = false;
      bool pyfjQYlKAt = false;
      bool oSoUrQtSfg = false;
      bool sEWboVABtt = false;
      bool YPqeyaHDiB = false;
      bool fYGxptEMNi = false;
      bool zYZHPkaDtu = false;
      bool XkQFUZaKWR = false;
      bool IqieAUyZkt = false;
      bool RnmLuzojON = false;
      bool zDInctHAbQ = false;
      bool SsouZHouGu = false;
      bool lBSzcjxFKV = false;
      bool jqwJREiuBF = false;
      bool MxxUaXyrkn = false;
      string jqZZNftbHX;
      string KResBwKYjz;
      string XNfpNABfyy;
      string OkKZsfuRJr;
      string gReFHDkeZd;
      string bzaSaWLiMM;
      string eOdIJYHFzU;
      string ArOrSFhZiJ;
      string PVFTWOKqyV;
      string UMFwMSnWwh;
      string weeEcikiAV;
      string okACwIIJlt;
      string OPHdznmSeA;
      string RKcANkpAqm;
      string daqbgjLCzE;
      string JekCTfXBEn;
      string wRDAEdHAoL;
      string RHRyPmYewP;
      string cjSZplZZgh;
      string MnuDqMXqXD;
      if(jqZZNftbHX == weeEcikiAV){bLNmlBMlmf = true;}
      else if(weeEcikiAV == jqZZNftbHX){fYGxptEMNi = true;}
      if(KResBwKYjz == okACwIIJlt){GsEoLLydJR = true;}
      else if(okACwIIJlt == KResBwKYjz){zYZHPkaDtu = true;}
      if(XNfpNABfyy == OPHdznmSeA){DhSHzcLOGD = true;}
      else if(OPHdznmSeA == XNfpNABfyy){XkQFUZaKWR = true;}
      if(OkKZsfuRJr == RKcANkpAqm){PhGsnQWenn = true;}
      else if(RKcANkpAqm == OkKZsfuRJr){IqieAUyZkt = true;}
      if(gReFHDkeZd == daqbgjLCzE){YmmAaSjGqe = true;}
      else if(daqbgjLCzE == gReFHDkeZd){RnmLuzojON = true;}
      if(bzaSaWLiMM == JekCTfXBEn){NtgFzsrGnI = true;}
      else if(JekCTfXBEn == bzaSaWLiMM){zDInctHAbQ = true;}
      if(eOdIJYHFzU == wRDAEdHAoL){pyfjQYlKAt = true;}
      else if(wRDAEdHAoL == eOdIJYHFzU){SsouZHouGu = true;}
      if(ArOrSFhZiJ == RHRyPmYewP){oSoUrQtSfg = true;}
      if(PVFTWOKqyV == cjSZplZZgh){sEWboVABtt = true;}
      if(UMFwMSnWwh == MnuDqMXqXD){YPqeyaHDiB = true;}
      while(RHRyPmYewP == ArOrSFhZiJ){lBSzcjxFKV = true;}
      while(cjSZplZZgh == cjSZplZZgh){jqwJREiuBF = true;}
      while(MnuDqMXqXD == MnuDqMXqXD){MxxUaXyrkn = true;}
      if(bLNmlBMlmf == true){bLNmlBMlmf = false;}
      if(GsEoLLydJR == true){GsEoLLydJR = false;}
      if(DhSHzcLOGD == true){DhSHzcLOGD = false;}
      if(PhGsnQWenn == true){PhGsnQWenn = false;}
      if(YmmAaSjGqe == true){YmmAaSjGqe = false;}
      if(NtgFzsrGnI == true){NtgFzsrGnI = false;}
      if(pyfjQYlKAt == true){pyfjQYlKAt = false;}
      if(oSoUrQtSfg == true){oSoUrQtSfg = false;}
      if(sEWboVABtt == true){sEWboVABtt = false;}
      if(YPqeyaHDiB == true){YPqeyaHDiB = false;}
      if(fYGxptEMNi == true){fYGxptEMNi = false;}
      if(zYZHPkaDtu == true){zYZHPkaDtu = false;}
      if(XkQFUZaKWR == true){XkQFUZaKWR = false;}
      if(IqieAUyZkt == true){IqieAUyZkt = false;}
      if(RnmLuzojON == true){RnmLuzojON = false;}
      if(zDInctHAbQ == true){zDInctHAbQ = false;}
      if(SsouZHouGu == true){SsouZHouGu = false;}
      if(lBSzcjxFKV == true){lBSzcjxFKV = false;}
      if(jqwJREiuBF == true){jqwJREiuBF = false;}
      if(MxxUaXyrkn == true){MxxUaXyrkn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIAYBCNKFF
{ 
  void twMNUSOXYz()
  { 
      bool CQPmWepUdd = false;
      bool GpDmSpigpr = false;
      bool eYxMXVxQSz = false;
      bool wLPgJBKjtK = false;
      bool GzUQdIUgyM = false;
      bool CwzrudSDPB = false;
      bool hZCdguZWcQ = false;
      bool fymfkeDghP = false;
      bool BPSFwAMXke = false;
      bool hGUscgxqii = false;
      bool hxDggEJTGP = false;
      bool alUAzSHxgg = false;
      bool iCkyhYctCD = false;
      bool hMxzgDLkYr = false;
      bool prQVEwlUsK = false;
      bool ZzJCAfLFzH = false;
      bool aPQCgNnVSw = false;
      bool GVXoppkPsk = false;
      bool mIBrdhCuzB = false;
      bool qGlQQabOnq = false;
      string pSTgmmfPks;
      string TrdHLiKlWo;
      string lmVUSZjqNW;
      string dLdVoLCShw;
      string VJuKOtWJlu;
      string xtFmlDxzON;
      string DoCOPHOISA;
      string frDaTbqKGY;
      string CZERYjGpil;
      string NDDUsgHfuG;
      string fOqkPFpeTJ;
      string LmrpKcjjoe;
      string BXYgmcnigm;
      string ULOzrniSCT;
      string saWYZaKNKQ;
      string wXpPEHoKyl;
      string QHxgoAXsxW;
      string tQgVlaBzGL;
      string SaXQpxUzuk;
      string yXTQDldojZ;
      if(pSTgmmfPks == fOqkPFpeTJ){CQPmWepUdd = true;}
      else if(fOqkPFpeTJ == pSTgmmfPks){hxDggEJTGP = true;}
      if(TrdHLiKlWo == LmrpKcjjoe){GpDmSpigpr = true;}
      else if(LmrpKcjjoe == TrdHLiKlWo){alUAzSHxgg = true;}
      if(lmVUSZjqNW == BXYgmcnigm){eYxMXVxQSz = true;}
      else if(BXYgmcnigm == lmVUSZjqNW){iCkyhYctCD = true;}
      if(dLdVoLCShw == ULOzrniSCT){wLPgJBKjtK = true;}
      else if(ULOzrniSCT == dLdVoLCShw){hMxzgDLkYr = true;}
      if(VJuKOtWJlu == saWYZaKNKQ){GzUQdIUgyM = true;}
      else if(saWYZaKNKQ == VJuKOtWJlu){prQVEwlUsK = true;}
      if(xtFmlDxzON == wXpPEHoKyl){CwzrudSDPB = true;}
      else if(wXpPEHoKyl == xtFmlDxzON){ZzJCAfLFzH = true;}
      if(DoCOPHOISA == QHxgoAXsxW){hZCdguZWcQ = true;}
      else if(QHxgoAXsxW == DoCOPHOISA){aPQCgNnVSw = true;}
      if(frDaTbqKGY == tQgVlaBzGL){fymfkeDghP = true;}
      if(CZERYjGpil == SaXQpxUzuk){BPSFwAMXke = true;}
      if(NDDUsgHfuG == yXTQDldojZ){hGUscgxqii = true;}
      while(tQgVlaBzGL == frDaTbqKGY){GVXoppkPsk = true;}
      while(SaXQpxUzuk == SaXQpxUzuk){mIBrdhCuzB = true;}
      while(yXTQDldojZ == yXTQDldojZ){qGlQQabOnq = true;}
      if(CQPmWepUdd == true){CQPmWepUdd = false;}
      if(GpDmSpigpr == true){GpDmSpigpr = false;}
      if(eYxMXVxQSz == true){eYxMXVxQSz = false;}
      if(wLPgJBKjtK == true){wLPgJBKjtK = false;}
      if(GzUQdIUgyM == true){GzUQdIUgyM = false;}
      if(CwzrudSDPB == true){CwzrudSDPB = false;}
      if(hZCdguZWcQ == true){hZCdguZWcQ = false;}
      if(fymfkeDghP == true){fymfkeDghP = false;}
      if(BPSFwAMXke == true){BPSFwAMXke = false;}
      if(hGUscgxqii == true){hGUscgxqii = false;}
      if(hxDggEJTGP == true){hxDggEJTGP = false;}
      if(alUAzSHxgg == true){alUAzSHxgg = false;}
      if(iCkyhYctCD == true){iCkyhYctCD = false;}
      if(hMxzgDLkYr == true){hMxzgDLkYr = false;}
      if(prQVEwlUsK == true){prQVEwlUsK = false;}
      if(ZzJCAfLFzH == true){ZzJCAfLFzH = false;}
      if(aPQCgNnVSw == true){aPQCgNnVSw = false;}
      if(GVXoppkPsk == true){GVXoppkPsk = false;}
      if(mIBrdhCuzB == true){mIBrdhCuzB = false;}
      if(qGlQQabOnq == true){qGlQQabOnq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHEWVVIBQE
{ 
  void xnuLKulHhO()
  { 
      bool sOZbBOHorK = false;
      bool inZNZNYtNa = false;
      bool uwIqdYcStf = false;
      bool HTKGprfdgY = false;
      bool CUMXbkytUh = false;
      bool pRRCzxGhxc = false;
      bool lnuLDPcTWh = false;
      bool htMoXZjjPs = false;
      bool ZhxLppBIHs = false;
      bool lxgDmNZAUM = false;
      bool IeWmAuEceY = false;
      bool MVSEDDqiVM = false;
      bool NUMdujNJCJ = false;
      bool AiPCkuKKKu = false;
      bool lYdhfPecAi = false;
      bool WpdHynSsqQ = false;
      bool gtZUYdFPTH = false;
      bool rfYaaopdyf = false;
      bool FkISlJEIEx = false;
      bool bRTtNqyIJC = false;
      string TAmkpXBBQw;
      string qyXLMfoBAy;
      string TwpleAyamk;
      string ylsnQwKecV;
      string RaSYoUQVsP;
      string OnnVIXJAFp;
      string YZOeyEEitQ;
      string VJXdfrcRxJ;
      string jbhWWJxXes;
      string lJZlwrMnaj;
      string PgbbtEQKoQ;
      string trDwGxqqIn;
      string GgDAdMjkhn;
      string foqMsCAGcR;
      string smhOztFcfz;
      string AVeldhcaxg;
      string UebBkEBqCD;
      string xkNptSzoBj;
      string GGFhmJJEiK;
      string ZYIuwOLfdt;
      if(TAmkpXBBQw == PgbbtEQKoQ){sOZbBOHorK = true;}
      else if(PgbbtEQKoQ == TAmkpXBBQw){IeWmAuEceY = true;}
      if(qyXLMfoBAy == trDwGxqqIn){inZNZNYtNa = true;}
      else if(trDwGxqqIn == qyXLMfoBAy){MVSEDDqiVM = true;}
      if(TwpleAyamk == GgDAdMjkhn){uwIqdYcStf = true;}
      else if(GgDAdMjkhn == TwpleAyamk){NUMdujNJCJ = true;}
      if(ylsnQwKecV == foqMsCAGcR){HTKGprfdgY = true;}
      else if(foqMsCAGcR == ylsnQwKecV){AiPCkuKKKu = true;}
      if(RaSYoUQVsP == smhOztFcfz){CUMXbkytUh = true;}
      else if(smhOztFcfz == RaSYoUQVsP){lYdhfPecAi = true;}
      if(OnnVIXJAFp == AVeldhcaxg){pRRCzxGhxc = true;}
      else if(AVeldhcaxg == OnnVIXJAFp){WpdHynSsqQ = true;}
      if(YZOeyEEitQ == UebBkEBqCD){lnuLDPcTWh = true;}
      else if(UebBkEBqCD == YZOeyEEitQ){gtZUYdFPTH = true;}
      if(VJXdfrcRxJ == xkNptSzoBj){htMoXZjjPs = true;}
      if(jbhWWJxXes == GGFhmJJEiK){ZhxLppBIHs = true;}
      if(lJZlwrMnaj == ZYIuwOLfdt){lxgDmNZAUM = true;}
      while(xkNptSzoBj == VJXdfrcRxJ){rfYaaopdyf = true;}
      while(GGFhmJJEiK == GGFhmJJEiK){FkISlJEIEx = true;}
      while(ZYIuwOLfdt == ZYIuwOLfdt){bRTtNqyIJC = true;}
      if(sOZbBOHorK == true){sOZbBOHorK = false;}
      if(inZNZNYtNa == true){inZNZNYtNa = false;}
      if(uwIqdYcStf == true){uwIqdYcStf = false;}
      if(HTKGprfdgY == true){HTKGprfdgY = false;}
      if(CUMXbkytUh == true){CUMXbkytUh = false;}
      if(pRRCzxGhxc == true){pRRCzxGhxc = false;}
      if(lnuLDPcTWh == true){lnuLDPcTWh = false;}
      if(htMoXZjjPs == true){htMoXZjjPs = false;}
      if(ZhxLppBIHs == true){ZhxLppBIHs = false;}
      if(lxgDmNZAUM == true){lxgDmNZAUM = false;}
      if(IeWmAuEceY == true){IeWmAuEceY = false;}
      if(MVSEDDqiVM == true){MVSEDDqiVM = false;}
      if(NUMdujNJCJ == true){NUMdujNJCJ = false;}
      if(AiPCkuKKKu == true){AiPCkuKKKu = false;}
      if(lYdhfPecAi == true){lYdhfPecAi = false;}
      if(WpdHynSsqQ == true){WpdHynSsqQ = false;}
      if(gtZUYdFPTH == true){gtZUYdFPTH = false;}
      if(rfYaaopdyf == true){rfYaaopdyf = false;}
      if(FkISlJEIEx == true){FkISlJEIEx = false;}
      if(bRTtNqyIJC == true){bRTtNqyIJC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOCLUUAYIU
{ 
  void FUEWkoGWys()
  { 
      bool DVywipZtbm = false;
      bool GJeoEkJEBc = false;
      bool huwcFAoUOl = false;
      bool EMQAycjyhh = false;
      bool DBwDghkNWN = false;
      bool NrDeCHYUph = false;
      bool AEeoisseqa = false;
      bool AKWSZfyswX = false;
      bool ObxAYLIkxp = false;
      bool DPIzgzWGTm = false;
      bool oGWuNCUkFV = false;
      bool IfXSSYGdQW = false;
      bool kHgAXjBXkZ = false;
      bool JqZJhIECmV = false;
      bool pXebhWrpgI = false;
      bool srpxBhYWXc = false;
      bool AxzeLQGNjJ = false;
      bool TEqtfNbESA = false;
      bool rLqcgRAbHA = false;
      bool ihdKUsXzQQ = false;
      string ZZWRDEwECh;
      string fblYoOjxIs;
      string OxNSJfJAlm;
      string ZHTaaOexor;
      string QQEfgchNpu;
      string DCCIEbMDHW;
      string twRPIYIKya;
      string imIPbxshlf;
      string ywJpiWFLVy;
      string BapSyUynXH;
      string UXPPLQtlfG;
      string idRaXylbfl;
      string TwozYIxoQG;
      string zEKdKafteS;
      string bSePPWJOtA;
      string hWHlnXiPqD;
      string TEVZGeTmPx;
      string RrwNJBRYjB;
      string ziuQXcwYpm;
      string qQDbyWxFIj;
      if(ZZWRDEwECh == UXPPLQtlfG){DVywipZtbm = true;}
      else if(UXPPLQtlfG == ZZWRDEwECh){oGWuNCUkFV = true;}
      if(fblYoOjxIs == idRaXylbfl){GJeoEkJEBc = true;}
      else if(idRaXylbfl == fblYoOjxIs){IfXSSYGdQW = true;}
      if(OxNSJfJAlm == TwozYIxoQG){huwcFAoUOl = true;}
      else if(TwozYIxoQG == OxNSJfJAlm){kHgAXjBXkZ = true;}
      if(ZHTaaOexor == zEKdKafteS){EMQAycjyhh = true;}
      else if(zEKdKafteS == ZHTaaOexor){JqZJhIECmV = true;}
      if(QQEfgchNpu == bSePPWJOtA){DBwDghkNWN = true;}
      else if(bSePPWJOtA == QQEfgchNpu){pXebhWrpgI = true;}
      if(DCCIEbMDHW == hWHlnXiPqD){NrDeCHYUph = true;}
      else if(hWHlnXiPqD == DCCIEbMDHW){srpxBhYWXc = true;}
      if(twRPIYIKya == TEVZGeTmPx){AEeoisseqa = true;}
      else if(TEVZGeTmPx == twRPIYIKya){AxzeLQGNjJ = true;}
      if(imIPbxshlf == RrwNJBRYjB){AKWSZfyswX = true;}
      if(ywJpiWFLVy == ziuQXcwYpm){ObxAYLIkxp = true;}
      if(BapSyUynXH == qQDbyWxFIj){DPIzgzWGTm = true;}
      while(RrwNJBRYjB == imIPbxshlf){TEqtfNbESA = true;}
      while(ziuQXcwYpm == ziuQXcwYpm){rLqcgRAbHA = true;}
      while(qQDbyWxFIj == qQDbyWxFIj){ihdKUsXzQQ = true;}
      if(DVywipZtbm == true){DVywipZtbm = false;}
      if(GJeoEkJEBc == true){GJeoEkJEBc = false;}
      if(huwcFAoUOl == true){huwcFAoUOl = false;}
      if(EMQAycjyhh == true){EMQAycjyhh = false;}
      if(DBwDghkNWN == true){DBwDghkNWN = false;}
      if(NrDeCHYUph == true){NrDeCHYUph = false;}
      if(AEeoisseqa == true){AEeoisseqa = false;}
      if(AKWSZfyswX == true){AKWSZfyswX = false;}
      if(ObxAYLIkxp == true){ObxAYLIkxp = false;}
      if(DPIzgzWGTm == true){DPIzgzWGTm = false;}
      if(oGWuNCUkFV == true){oGWuNCUkFV = false;}
      if(IfXSSYGdQW == true){IfXSSYGdQW = false;}
      if(kHgAXjBXkZ == true){kHgAXjBXkZ = false;}
      if(JqZJhIECmV == true){JqZJhIECmV = false;}
      if(pXebhWrpgI == true){pXebhWrpgI = false;}
      if(srpxBhYWXc == true){srpxBhYWXc = false;}
      if(AxzeLQGNjJ == true){AxzeLQGNjJ = false;}
      if(TEqtfNbESA == true){TEqtfNbESA = false;}
      if(rLqcgRAbHA == true){rLqcgRAbHA = false;}
      if(ihdKUsXzQQ == true){ihdKUsXzQQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUMJBQTOWK
{ 
  void AkwsWwXxxI()
  { 
      bool NTwaIAESFE = false;
      bool xnpNFUUYWZ = false;
      bool siOePgxPaV = false;
      bool EdruGXuKtw = false;
      bool kIqkqljWPk = false;
      bool HiTQWdERKa = false;
      bool CorjATutHh = false;
      bool YKdankrcnd = false;
      bool xazoNVJaYc = false;
      bool SdATsuPGkW = false;
      bool qoOhMxEsck = false;
      bool lbcgdapCWd = false;
      bool JTVePuJKgr = false;
      bool UkqQmHLQcP = false;
      bool QQymppASoS = false;
      bool FMjGMWTjSR = false;
      bool msLjQAkMtV = false;
      bool OYZGNrVinY = false;
      bool tpUOlHBjDP = false;
      bool nbyLcXENWp = false;
      string dcqbLCUYzp;
      string VOJYqUaKbR;
      string uKFJtNtDrL;
      string MtYSyATZCI;
      string BYlQnnDWnN;
      string WRPPRSXhgx;
      string HQgmcaoqZq;
      string BBHTPWYoUG;
      string KXPdnteJBe;
      string ckrEAjrymN;
      string yMwwMVKuzt;
      string thMamjBCzi;
      string wfouOPIDTf;
      string eZBHHxbSRS;
      string jiKGjtYQQQ;
      string iozEQSWBhw;
      string MHbTPUgETp;
      string IhjfyMUiKT;
      string qrlCwpaxpo;
      string ZajUFcHqqP;
      if(dcqbLCUYzp == yMwwMVKuzt){NTwaIAESFE = true;}
      else if(yMwwMVKuzt == dcqbLCUYzp){qoOhMxEsck = true;}
      if(VOJYqUaKbR == thMamjBCzi){xnpNFUUYWZ = true;}
      else if(thMamjBCzi == VOJYqUaKbR){lbcgdapCWd = true;}
      if(uKFJtNtDrL == wfouOPIDTf){siOePgxPaV = true;}
      else if(wfouOPIDTf == uKFJtNtDrL){JTVePuJKgr = true;}
      if(MtYSyATZCI == eZBHHxbSRS){EdruGXuKtw = true;}
      else if(eZBHHxbSRS == MtYSyATZCI){UkqQmHLQcP = true;}
      if(BYlQnnDWnN == jiKGjtYQQQ){kIqkqljWPk = true;}
      else if(jiKGjtYQQQ == BYlQnnDWnN){QQymppASoS = true;}
      if(WRPPRSXhgx == iozEQSWBhw){HiTQWdERKa = true;}
      else if(iozEQSWBhw == WRPPRSXhgx){FMjGMWTjSR = true;}
      if(HQgmcaoqZq == MHbTPUgETp){CorjATutHh = true;}
      else if(MHbTPUgETp == HQgmcaoqZq){msLjQAkMtV = true;}
      if(BBHTPWYoUG == IhjfyMUiKT){YKdankrcnd = true;}
      if(KXPdnteJBe == qrlCwpaxpo){xazoNVJaYc = true;}
      if(ckrEAjrymN == ZajUFcHqqP){SdATsuPGkW = true;}
      while(IhjfyMUiKT == BBHTPWYoUG){OYZGNrVinY = true;}
      while(qrlCwpaxpo == qrlCwpaxpo){tpUOlHBjDP = true;}
      while(ZajUFcHqqP == ZajUFcHqqP){nbyLcXENWp = true;}
      if(NTwaIAESFE == true){NTwaIAESFE = false;}
      if(xnpNFUUYWZ == true){xnpNFUUYWZ = false;}
      if(siOePgxPaV == true){siOePgxPaV = false;}
      if(EdruGXuKtw == true){EdruGXuKtw = false;}
      if(kIqkqljWPk == true){kIqkqljWPk = false;}
      if(HiTQWdERKa == true){HiTQWdERKa = false;}
      if(CorjATutHh == true){CorjATutHh = false;}
      if(YKdankrcnd == true){YKdankrcnd = false;}
      if(xazoNVJaYc == true){xazoNVJaYc = false;}
      if(SdATsuPGkW == true){SdATsuPGkW = false;}
      if(qoOhMxEsck == true){qoOhMxEsck = false;}
      if(lbcgdapCWd == true){lbcgdapCWd = false;}
      if(JTVePuJKgr == true){JTVePuJKgr = false;}
      if(UkqQmHLQcP == true){UkqQmHLQcP = false;}
      if(QQymppASoS == true){QQymppASoS = false;}
      if(FMjGMWTjSR == true){FMjGMWTjSR = false;}
      if(msLjQAkMtV == true){msLjQAkMtV = false;}
      if(OYZGNrVinY == true){OYZGNrVinY = false;}
      if(tpUOlHBjDP == true){tpUOlHBjDP = false;}
      if(nbyLcXENWp == true){nbyLcXENWp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROREQPEKXB
{ 
  void QifXjGpBfZ()
  { 
      bool JGgwWQtrHC = false;
      bool hIKrSTNssl = false;
      bool oXgzVAYebK = false;
      bool iExQNqKIfX = false;
      bool cMFYQFADSY = false;
      bool gWpPbkZgZV = false;
      bool rOPxScLsda = false;
      bool JENUIbRHiP = false;
      bool zUMCcMOhnc = false;
      bool RdhJfOwIFm = false;
      bool tGZqPbJVGA = false;
      bool SRyKWWBNTG = false;
      bool OcFBJfWDnt = false;
      bool eJCuUruUlA = false;
      bool CsbmJzfXmI = false;
      bool MinzXRBXhj = false;
      bool FGgMVJPCod = false;
      bool bgaTDVBRrJ = false;
      bool zzPfguUDWD = false;
      bool qXlCuwLORA = false;
      string fnmTTxiXHc;
      string MWWIApfMkz;
      string rMVKFVrEXr;
      string sHmJqZcLlD;
      string AeEOSJfCIq;
      string DcOJFTScNx;
      string FeAPiEiNQZ;
      string MUZhyNHGqu;
      string oowgnPrcDX;
      string HAxoxVeofN;
      string aSlidiDfLr;
      string MMkSHPiTaS;
      string LFKsSMWkkc;
      string hSacTWDMCF;
      string MLRKLtOegh;
      string mKNNCVHrQQ;
      string LRuiJskHyk;
      string LVQVFzmzhX;
      string yqECoXENay;
      string OLwksuQiBR;
      if(fnmTTxiXHc == aSlidiDfLr){JGgwWQtrHC = true;}
      else if(aSlidiDfLr == fnmTTxiXHc){tGZqPbJVGA = true;}
      if(MWWIApfMkz == MMkSHPiTaS){hIKrSTNssl = true;}
      else if(MMkSHPiTaS == MWWIApfMkz){SRyKWWBNTG = true;}
      if(rMVKFVrEXr == LFKsSMWkkc){oXgzVAYebK = true;}
      else if(LFKsSMWkkc == rMVKFVrEXr){OcFBJfWDnt = true;}
      if(sHmJqZcLlD == hSacTWDMCF){iExQNqKIfX = true;}
      else if(hSacTWDMCF == sHmJqZcLlD){eJCuUruUlA = true;}
      if(AeEOSJfCIq == MLRKLtOegh){cMFYQFADSY = true;}
      else if(MLRKLtOegh == AeEOSJfCIq){CsbmJzfXmI = true;}
      if(DcOJFTScNx == mKNNCVHrQQ){gWpPbkZgZV = true;}
      else if(mKNNCVHrQQ == DcOJFTScNx){MinzXRBXhj = true;}
      if(FeAPiEiNQZ == LRuiJskHyk){rOPxScLsda = true;}
      else if(LRuiJskHyk == FeAPiEiNQZ){FGgMVJPCod = true;}
      if(MUZhyNHGqu == LVQVFzmzhX){JENUIbRHiP = true;}
      if(oowgnPrcDX == yqECoXENay){zUMCcMOhnc = true;}
      if(HAxoxVeofN == OLwksuQiBR){RdhJfOwIFm = true;}
      while(LVQVFzmzhX == MUZhyNHGqu){bgaTDVBRrJ = true;}
      while(yqECoXENay == yqECoXENay){zzPfguUDWD = true;}
      while(OLwksuQiBR == OLwksuQiBR){qXlCuwLORA = true;}
      if(JGgwWQtrHC == true){JGgwWQtrHC = false;}
      if(hIKrSTNssl == true){hIKrSTNssl = false;}
      if(oXgzVAYebK == true){oXgzVAYebK = false;}
      if(iExQNqKIfX == true){iExQNqKIfX = false;}
      if(cMFYQFADSY == true){cMFYQFADSY = false;}
      if(gWpPbkZgZV == true){gWpPbkZgZV = false;}
      if(rOPxScLsda == true){rOPxScLsda = false;}
      if(JENUIbRHiP == true){JENUIbRHiP = false;}
      if(zUMCcMOhnc == true){zUMCcMOhnc = false;}
      if(RdhJfOwIFm == true){RdhJfOwIFm = false;}
      if(tGZqPbJVGA == true){tGZqPbJVGA = false;}
      if(SRyKWWBNTG == true){SRyKWWBNTG = false;}
      if(OcFBJfWDnt == true){OcFBJfWDnt = false;}
      if(eJCuUruUlA == true){eJCuUruUlA = false;}
      if(CsbmJzfXmI == true){CsbmJzfXmI = false;}
      if(MinzXRBXhj == true){MinzXRBXhj = false;}
      if(FGgMVJPCod == true){FGgMVJPCod = false;}
      if(bgaTDVBRrJ == true){bgaTDVBRrJ = false;}
      if(zzPfguUDWD == true){zzPfguUDWD = false;}
      if(qXlCuwLORA == true){qXlCuwLORA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAGDIZAKJO
{ 
  void tmjRhQMutz()
  { 
      bool GylWmqKMuz = false;
      bool CiReaaBLYB = false;
      bool gDQfkSJyNZ = false;
      bool ccjHdVfzBx = false;
      bool GRUmTuAcSn = false;
      bool cygaRChGlU = false;
      bool hLzVWYyKAE = false;
      bool tBKauPidLo = false;
      bool SgfZwduIoa = false;
      bool nZNgOtSzPt = false;
      bool xobOsbnFfB = false;
      bool TEuwBBfYZs = false;
      bool doUZQUncLA = false;
      bool xjNQrcERfU = false;
      bool opcnHjeQeN = false;
      bool OsYWQHUCxY = false;
      bool mLsfEjpdEY = false;
      bool wOsFDnMgRf = false;
      bool pWyykEKpAj = false;
      bool ICTHgdwwjW = false;
      string qWSTDmkbKj;
      string ZMadngKhRf;
      string jPPZNgfwjQ;
      string wAgfTRaEyF;
      string kcUsLRAAxZ;
      string HOZEtbGrFV;
      string GnrtmYetJW;
      string GGjLtGtVNu;
      string ffzJJgZckr;
      string KhzbyxkZGm;
      string mFpaTAeNJn;
      string gjeKpaohkG;
      string zBJRLXHHMx;
      string UUPaHapXoI;
      string BLSwLaDnlX;
      string IDozmkwXPu;
      string sWAMTMTECO;
      string jQrbEmiMGk;
      string USVonReQmW;
      string dRHsOeKFcz;
      if(qWSTDmkbKj == mFpaTAeNJn){GylWmqKMuz = true;}
      else if(mFpaTAeNJn == qWSTDmkbKj){xobOsbnFfB = true;}
      if(ZMadngKhRf == gjeKpaohkG){CiReaaBLYB = true;}
      else if(gjeKpaohkG == ZMadngKhRf){TEuwBBfYZs = true;}
      if(jPPZNgfwjQ == zBJRLXHHMx){gDQfkSJyNZ = true;}
      else if(zBJRLXHHMx == jPPZNgfwjQ){doUZQUncLA = true;}
      if(wAgfTRaEyF == UUPaHapXoI){ccjHdVfzBx = true;}
      else if(UUPaHapXoI == wAgfTRaEyF){xjNQrcERfU = true;}
      if(kcUsLRAAxZ == BLSwLaDnlX){GRUmTuAcSn = true;}
      else if(BLSwLaDnlX == kcUsLRAAxZ){opcnHjeQeN = true;}
      if(HOZEtbGrFV == IDozmkwXPu){cygaRChGlU = true;}
      else if(IDozmkwXPu == HOZEtbGrFV){OsYWQHUCxY = true;}
      if(GnrtmYetJW == sWAMTMTECO){hLzVWYyKAE = true;}
      else if(sWAMTMTECO == GnrtmYetJW){mLsfEjpdEY = true;}
      if(GGjLtGtVNu == jQrbEmiMGk){tBKauPidLo = true;}
      if(ffzJJgZckr == USVonReQmW){SgfZwduIoa = true;}
      if(KhzbyxkZGm == dRHsOeKFcz){nZNgOtSzPt = true;}
      while(jQrbEmiMGk == GGjLtGtVNu){wOsFDnMgRf = true;}
      while(USVonReQmW == USVonReQmW){pWyykEKpAj = true;}
      while(dRHsOeKFcz == dRHsOeKFcz){ICTHgdwwjW = true;}
      if(GylWmqKMuz == true){GylWmqKMuz = false;}
      if(CiReaaBLYB == true){CiReaaBLYB = false;}
      if(gDQfkSJyNZ == true){gDQfkSJyNZ = false;}
      if(ccjHdVfzBx == true){ccjHdVfzBx = false;}
      if(GRUmTuAcSn == true){GRUmTuAcSn = false;}
      if(cygaRChGlU == true){cygaRChGlU = false;}
      if(hLzVWYyKAE == true){hLzVWYyKAE = false;}
      if(tBKauPidLo == true){tBKauPidLo = false;}
      if(SgfZwduIoa == true){SgfZwduIoa = false;}
      if(nZNgOtSzPt == true){nZNgOtSzPt = false;}
      if(xobOsbnFfB == true){xobOsbnFfB = false;}
      if(TEuwBBfYZs == true){TEuwBBfYZs = false;}
      if(doUZQUncLA == true){doUZQUncLA = false;}
      if(xjNQrcERfU == true){xjNQrcERfU = false;}
      if(opcnHjeQeN == true){opcnHjeQeN = false;}
      if(OsYWQHUCxY == true){OsYWQHUCxY = false;}
      if(mLsfEjpdEY == true){mLsfEjpdEY = false;}
      if(wOsFDnMgRf == true){wOsFDnMgRf = false;}
      if(pWyykEKpAj == true){pWyykEKpAj = false;}
      if(ICTHgdwwjW == true){ICTHgdwwjW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LQPPXKOSBC
{ 
  void pshIjRsuaq()
  { 
      bool XAjhyPIguC = false;
      bool eMwqKUTkgR = false;
      bool oNmRRUcOPK = false;
      bool tdAkntWnek = false;
      bool tlFbXsiEMn = false;
      bool fwzjeJMRQc = false;
      bool ltQkIALKCQ = false;
      bool yeFuXCILtX = false;
      bool kYBbdxdPGd = false;
      bool gEXByAUUSW = false;
      bool gYBwoAqEMb = false;
      bool BBXrrNroGL = false;
      bool VwEXjsHDwW = false;
      bool hnrWqMWEld = false;
      bool GZCdcegfJk = false;
      bool HeOHBjTcMw = false;
      bool smHptNIAAe = false;
      bool pmCcFutauE = false;
      bool MbsLOCZkUG = false;
      bool rsrpjSSLjP = false;
      string JKKzWtoeYS;
      string wSeWuqQeup;
      string UmdWeSrNWp;
      string GmINfnilCj;
      string nQyRLXHaKb;
      string RwBYWVgnUD;
      string BaIhLJJRqG;
      string IdbKCEoLLH;
      string LRCuYKljpJ;
      string HuRyiMHPGC;
      string OpiDSnTpWS;
      string gUbNriYNJA;
      string WYagzNLcbo;
      string xYFJrUhzbk;
      string puNXbmSEGz;
      string ntFFeoOCDE;
      string bqNgUHOSUX;
      string BYkYKbKCFM;
      string tGWcADSAeC;
      string FfuWIzgfCT;
      if(JKKzWtoeYS == OpiDSnTpWS){XAjhyPIguC = true;}
      else if(OpiDSnTpWS == JKKzWtoeYS){gYBwoAqEMb = true;}
      if(wSeWuqQeup == gUbNriYNJA){eMwqKUTkgR = true;}
      else if(gUbNriYNJA == wSeWuqQeup){BBXrrNroGL = true;}
      if(UmdWeSrNWp == WYagzNLcbo){oNmRRUcOPK = true;}
      else if(WYagzNLcbo == UmdWeSrNWp){VwEXjsHDwW = true;}
      if(GmINfnilCj == xYFJrUhzbk){tdAkntWnek = true;}
      else if(xYFJrUhzbk == GmINfnilCj){hnrWqMWEld = true;}
      if(nQyRLXHaKb == puNXbmSEGz){tlFbXsiEMn = true;}
      else if(puNXbmSEGz == nQyRLXHaKb){GZCdcegfJk = true;}
      if(RwBYWVgnUD == ntFFeoOCDE){fwzjeJMRQc = true;}
      else if(ntFFeoOCDE == RwBYWVgnUD){HeOHBjTcMw = true;}
      if(BaIhLJJRqG == bqNgUHOSUX){ltQkIALKCQ = true;}
      else if(bqNgUHOSUX == BaIhLJJRqG){smHptNIAAe = true;}
      if(IdbKCEoLLH == BYkYKbKCFM){yeFuXCILtX = true;}
      if(LRCuYKljpJ == tGWcADSAeC){kYBbdxdPGd = true;}
      if(HuRyiMHPGC == FfuWIzgfCT){gEXByAUUSW = true;}
      while(BYkYKbKCFM == IdbKCEoLLH){pmCcFutauE = true;}
      while(tGWcADSAeC == tGWcADSAeC){MbsLOCZkUG = true;}
      while(FfuWIzgfCT == FfuWIzgfCT){rsrpjSSLjP = true;}
      if(XAjhyPIguC == true){XAjhyPIguC = false;}
      if(eMwqKUTkgR == true){eMwqKUTkgR = false;}
      if(oNmRRUcOPK == true){oNmRRUcOPK = false;}
      if(tdAkntWnek == true){tdAkntWnek = false;}
      if(tlFbXsiEMn == true){tlFbXsiEMn = false;}
      if(fwzjeJMRQc == true){fwzjeJMRQc = false;}
      if(ltQkIALKCQ == true){ltQkIALKCQ = false;}
      if(yeFuXCILtX == true){yeFuXCILtX = false;}
      if(kYBbdxdPGd == true){kYBbdxdPGd = false;}
      if(gEXByAUUSW == true){gEXByAUUSW = false;}
      if(gYBwoAqEMb == true){gYBwoAqEMb = false;}
      if(BBXrrNroGL == true){BBXrrNroGL = false;}
      if(VwEXjsHDwW == true){VwEXjsHDwW = false;}
      if(hnrWqMWEld == true){hnrWqMWEld = false;}
      if(GZCdcegfJk == true){GZCdcegfJk = false;}
      if(HeOHBjTcMw == true){HeOHBjTcMw = false;}
      if(smHptNIAAe == true){smHptNIAAe = false;}
      if(pmCcFutauE == true){pmCcFutauE = false;}
      if(MbsLOCZkUG == true){MbsLOCZkUG = false;}
      if(rsrpjSSLjP == true){rsrpjSSLjP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARMRNXGUOJ
{ 
  void CwNrpTfWGk()
  { 
      bool PrjMEWemDA = false;
      bool zlqtaGuGAC = false;
      bool EjxkVqMsCm = false;
      bool QCuXDNsiZR = false;
      bool RrYaqyljBz = false;
      bool osfLcfuzpN = false;
      bool KljQjxpTpN = false;
      bool MMfhjLLVsX = false;
      bool EbqDxWWitX = false;
      bool StsMHfHIqt = false;
      bool HStnlcNxbQ = false;
      bool UYFRIhtfTM = false;
      bool ZGZRtSSSZD = false;
      bool DDezPlhDRU = false;
      bool JYHcDsnbEZ = false;
      bool laneTBrbsT = false;
      bool KtWXMRsGCV = false;
      bool zqOzCBywOB = false;
      bool dqOARbOAfO = false;
      bool sGJxJOBjPl = false;
      string RtrepIDXHs;
      string ZeYPqYdMqu;
      string FhsMRDQMcr;
      string JuMnOwQarO;
      string qaKMyFDVGN;
      string caSxbjAfNl;
      string rqtOjeSjBt;
      string ICUbEdXgNL;
      string zuFOPibOLd;
      string wjNFWAfucT;
      string lTTMFZGpsy;
      string MSSBmwkezA;
      string CDXWyXoOFD;
      string ybEsZfasJp;
      string ckVNRdRLSZ;
      string OAwbRhuwOg;
      string jqkozjNYbG;
      string VqVIXQhJFT;
      string Gdueoxfcbq;
      string jdecFkAfOg;
      if(RtrepIDXHs == lTTMFZGpsy){PrjMEWemDA = true;}
      else if(lTTMFZGpsy == RtrepIDXHs){HStnlcNxbQ = true;}
      if(ZeYPqYdMqu == MSSBmwkezA){zlqtaGuGAC = true;}
      else if(MSSBmwkezA == ZeYPqYdMqu){UYFRIhtfTM = true;}
      if(FhsMRDQMcr == CDXWyXoOFD){EjxkVqMsCm = true;}
      else if(CDXWyXoOFD == FhsMRDQMcr){ZGZRtSSSZD = true;}
      if(JuMnOwQarO == ybEsZfasJp){QCuXDNsiZR = true;}
      else if(ybEsZfasJp == JuMnOwQarO){DDezPlhDRU = true;}
      if(qaKMyFDVGN == ckVNRdRLSZ){RrYaqyljBz = true;}
      else if(ckVNRdRLSZ == qaKMyFDVGN){JYHcDsnbEZ = true;}
      if(caSxbjAfNl == OAwbRhuwOg){osfLcfuzpN = true;}
      else if(OAwbRhuwOg == caSxbjAfNl){laneTBrbsT = true;}
      if(rqtOjeSjBt == jqkozjNYbG){KljQjxpTpN = true;}
      else if(jqkozjNYbG == rqtOjeSjBt){KtWXMRsGCV = true;}
      if(ICUbEdXgNL == VqVIXQhJFT){MMfhjLLVsX = true;}
      if(zuFOPibOLd == Gdueoxfcbq){EbqDxWWitX = true;}
      if(wjNFWAfucT == jdecFkAfOg){StsMHfHIqt = true;}
      while(VqVIXQhJFT == ICUbEdXgNL){zqOzCBywOB = true;}
      while(Gdueoxfcbq == Gdueoxfcbq){dqOARbOAfO = true;}
      while(jdecFkAfOg == jdecFkAfOg){sGJxJOBjPl = true;}
      if(PrjMEWemDA == true){PrjMEWemDA = false;}
      if(zlqtaGuGAC == true){zlqtaGuGAC = false;}
      if(EjxkVqMsCm == true){EjxkVqMsCm = false;}
      if(QCuXDNsiZR == true){QCuXDNsiZR = false;}
      if(RrYaqyljBz == true){RrYaqyljBz = false;}
      if(osfLcfuzpN == true){osfLcfuzpN = false;}
      if(KljQjxpTpN == true){KljQjxpTpN = false;}
      if(MMfhjLLVsX == true){MMfhjLLVsX = false;}
      if(EbqDxWWitX == true){EbqDxWWitX = false;}
      if(StsMHfHIqt == true){StsMHfHIqt = false;}
      if(HStnlcNxbQ == true){HStnlcNxbQ = false;}
      if(UYFRIhtfTM == true){UYFRIhtfTM = false;}
      if(ZGZRtSSSZD == true){ZGZRtSSSZD = false;}
      if(DDezPlhDRU == true){DDezPlhDRU = false;}
      if(JYHcDsnbEZ == true){JYHcDsnbEZ = false;}
      if(laneTBrbsT == true){laneTBrbsT = false;}
      if(KtWXMRsGCV == true){KtWXMRsGCV = false;}
      if(zqOzCBywOB == true){zqOzCBywOB = false;}
      if(dqOARbOAfO == true){dqOARbOAfO = false;}
      if(sGJxJOBjPl == true){sGJxJOBjPl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOPWBMVGJB
{ 
  void bJbOxMeeEa()
  { 
      bool YwqurNoPnK = false;
      bool SEytcnsKfr = false;
      bool wfLmZaIlqq = false;
      bool PeApjsmRcQ = false;
      bool qFqemarhAE = false;
      bool XaSKsrkEUQ = false;
      bool FDYwunEHJj = false;
      bool BagOBqofAy = false;
      bool iZklTnMpxq = false;
      bool HiwLLnftjy = false;
      bool WkYPDwsDJC = false;
      bool DEDVheRlcG = false;
      bool bNKRbSeVCM = false;
      bool KtwBbxBViW = false;
      bool uIgunDeZdg = false;
      bool VtRcWJZGmk = false;
      bool RWBwqIHCtj = false;
      bool cwCFKTgPdY = false;
      bool mEqVqPbTeS = false;
      bool XuhyFXHjDe = false;
      string AsdpMJnNMB;
      string KZUZdULjEJ;
      string izDyImisyX;
      string bRmAtMfPXY;
      string MgjAUVIwOu;
      string dipmNBofhZ;
      string ZuPoYrmTeR;
      string nwMewCPCcl;
      string dldDssbAmr;
      string WAgxyRQubb;
      string ioQxGhVLpK;
      string llCwunRMue;
      string QmfmtmPPfe;
      string kUaBCoUfwL;
      string WQJbGjykCK;
      string zEzwKwIdDS;
      string SGeLYQLBsG;
      string SkPjIAcDfJ;
      string odNUegUepG;
      string fqcdrQkyDo;
      if(AsdpMJnNMB == ioQxGhVLpK){YwqurNoPnK = true;}
      else if(ioQxGhVLpK == AsdpMJnNMB){WkYPDwsDJC = true;}
      if(KZUZdULjEJ == llCwunRMue){SEytcnsKfr = true;}
      else if(llCwunRMue == KZUZdULjEJ){DEDVheRlcG = true;}
      if(izDyImisyX == QmfmtmPPfe){wfLmZaIlqq = true;}
      else if(QmfmtmPPfe == izDyImisyX){bNKRbSeVCM = true;}
      if(bRmAtMfPXY == kUaBCoUfwL){PeApjsmRcQ = true;}
      else if(kUaBCoUfwL == bRmAtMfPXY){KtwBbxBViW = true;}
      if(MgjAUVIwOu == WQJbGjykCK){qFqemarhAE = true;}
      else if(WQJbGjykCK == MgjAUVIwOu){uIgunDeZdg = true;}
      if(dipmNBofhZ == zEzwKwIdDS){XaSKsrkEUQ = true;}
      else if(zEzwKwIdDS == dipmNBofhZ){VtRcWJZGmk = true;}
      if(ZuPoYrmTeR == SGeLYQLBsG){FDYwunEHJj = true;}
      else if(SGeLYQLBsG == ZuPoYrmTeR){RWBwqIHCtj = true;}
      if(nwMewCPCcl == SkPjIAcDfJ){BagOBqofAy = true;}
      if(dldDssbAmr == odNUegUepG){iZklTnMpxq = true;}
      if(WAgxyRQubb == fqcdrQkyDo){HiwLLnftjy = true;}
      while(SkPjIAcDfJ == nwMewCPCcl){cwCFKTgPdY = true;}
      while(odNUegUepG == odNUegUepG){mEqVqPbTeS = true;}
      while(fqcdrQkyDo == fqcdrQkyDo){XuhyFXHjDe = true;}
      if(YwqurNoPnK == true){YwqurNoPnK = false;}
      if(SEytcnsKfr == true){SEytcnsKfr = false;}
      if(wfLmZaIlqq == true){wfLmZaIlqq = false;}
      if(PeApjsmRcQ == true){PeApjsmRcQ = false;}
      if(qFqemarhAE == true){qFqemarhAE = false;}
      if(XaSKsrkEUQ == true){XaSKsrkEUQ = false;}
      if(FDYwunEHJj == true){FDYwunEHJj = false;}
      if(BagOBqofAy == true){BagOBqofAy = false;}
      if(iZklTnMpxq == true){iZklTnMpxq = false;}
      if(HiwLLnftjy == true){HiwLLnftjy = false;}
      if(WkYPDwsDJC == true){WkYPDwsDJC = false;}
      if(DEDVheRlcG == true){DEDVheRlcG = false;}
      if(bNKRbSeVCM == true){bNKRbSeVCM = false;}
      if(KtwBbxBViW == true){KtwBbxBViW = false;}
      if(uIgunDeZdg == true){uIgunDeZdg = false;}
      if(VtRcWJZGmk == true){VtRcWJZGmk = false;}
      if(RWBwqIHCtj == true){RWBwqIHCtj = false;}
      if(cwCFKTgPdY == true){cwCFKTgPdY = false;}
      if(mEqVqPbTeS == true){mEqVqPbTeS = false;}
      if(XuhyFXHjDe == true){XuhyFXHjDe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGIVEJKUAW
{ 
  void RpVUNkZqGG()
  { 
      bool goPeiSdUCQ = false;
      bool SwLUBAKSox = false;
      bool mcBVxsitjb = false;
      bool CorapWyJmo = false;
      bool pnBqYWKbiE = false;
      bool RiDgxEmshp = false;
      bool jikZOdEjdd = false;
      bool CAfAHybJxZ = false;
      bool hGLeKSkLcl = false;
      bool iEawFGDacu = false;
      bool SZxECQDDYz = false;
      bool ccwIHcXFPu = false;
      bool rsGruyYitA = false;
      bool uAgBHHIHbs = false;
      bool PhldIGHSoc = false;
      bool ixLgDYTEJE = false;
      bool qTIYEbwuBz = false;
      bool TPcVfKHcin = false;
      bool pGsRRxozxh = false;
      bool nEyXBuYNZg = false;
      string CQroAlUDBe;
      string czKygcrSxg;
      string CwcHOVTiBP;
      string lhcAFraMfX;
      string FmGfLuwJRc;
      string mYhgJGnkae;
      string RlBlsuVJso;
      string CemZaOoxuS;
      string ZJQYbNzwqz;
      string EolBFTlUlQ;
      string ZlQcaHkIFt;
      string RqoHEHUcJf;
      string uYSskMslTH;
      string cUKdsmsnyT;
      string bqqwhNAewx;
      string zIKGVATWqN;
      string OzoyRwfKOQ;
      string OfeoEEhWLW;
      string MOoVITJDIr;
      string TVwjFbCsdk;
      if(CQroAlUDBe == ZlQcaHkIFt){goPeiSdUCQ = true;}
      else if(ZlQcaHkIFt == CQroAlUDBe){SZxECQDDYz = true;}
      if(czKygcrSxg == RqoHEHUcJf){SwLUBAKSox = true;}
      else if(RqoHEHUcJf == czKygcrSxg){ccwIHcXFPu = true;}
      if(CwcHOVTiBP == uYSskMslTH){mcBVxsitjb = true;}
      else if(uYSskMslTH == CwcHOVTiBP){rsGruyYitA = true;}
      if(lhcAFraMfX == cUKdsmsnyT){CorapWyJmo = true;}
      else if(cUKdsmsnyT == lhcAFraMfX){uAgBHHIHbs = true;}
      if(FmGfLuwJRc == bqqwhNAewx){pnBqYWKbiE = true;}
      else if(bqqwhNAewx == FmGfLuwJRc){PhldIGHSoc = true;}
      if(mYhgJGnkae == zIKGVATWqN){RiDgxEmshp = true;}
      else if(zIKGVATWqN == mYhgJGnkae){ixLgDYTEJE = true;}
      if(RlBlsuVJso == OzoyRwfKOQ){jikZOdEjdd = true;}
      else if(OzoyRwfKOQ == RlBlsuVJso){qTIYEbwuBz = true;}
      if(CemZaOoxuS == OfeoEEhWLW){CAfAHybJxZ = true;}
      if(ZJQYbNzwqz == MOoVITJDIr){hGLeKSkLcl = true;}
      if(EolBFTlUlQ == TVwjFbCsdk){iEawFGDacu = true;}
      while(OfeoEEhWLW == CemZaOoxuS){TPcVfKHcin = true;}
      while(MOoVITJDIr == MOoVITJDIr){pGsRRxozxh = true;}
      while(TVwjFbCsdk == TVwjFbCsdk){nEyXBuYNZg = true;}
      if(goPeiSdUCQ == true){goPeiSdUCQ = false;}
      if(SwLUBAKSox == true){SwLUBAKSox = false;}
      if(mcBVxsitjb == true){mcBVxsitjb = false;}
      if(CorapWyJmo == true){CorapWyJmo = false;}
      if(pnBqYWKbiE == true){pnBqYWKbiE = false;}
      if(RiDgxEmshp == true){RiDgxEmshp = false;}
      if(jikZOdEjdd == true){jikZOdEjdd = false;}
      if(CAfAHybJxZ == true){CAfAHybJxZ = false;}
      if(hGLeKSkLcl == true){hGLeKSkLcl = false;}
      if(iEawFGDacu == true){iEawFGDacu = false;}
      if(SZxECQDDYz == true){SZxECQDDYz = false;}
      if(ccwIHcXFPu == true){ccwIHcXFPu = false;}
      if(rsGruyYitA == true){rsGruyYitA = false;}
      if(uAgBHHIHbs == true){uAgBHHIHbs = false;}
      if(PhldIGHSoc == true){PhldIGHSoc = false;}
      if(ixLgDYTEJE == true){ixLgDYTEJE = false;}
      if(qTIYEbwuBz == true){qTIYEbwuBz = false;}
      if(TPcVfKHcin == true){TPcVfKHcin = false;}
      if(pGsRRxozxh == true){pGsRRxozxh = false;}
      if(nEyXBuYNZg == true){nEyXBuYNZg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WTXQYCTNEY
{ 
  void XRcTkKBiOq()
  { 
      bool cKbZPfMwxC = false;
      bool lSkkDiXKmr = false;
      bool WljquIcRFI = false;
      bool TYKJDdpxrO = false;
      bool FGKYubWGxm = false;
      bool rXBZQqakdH = false;
      bool CuqniMHbhY = false;
      bool rZSYmPaKuS = false;
      bool kWTRQwWkrM = false;
      bool DFSjLJPWoh = false;
      bool TuYXuREcmB = false;
      bool PPoKWfaZXl = false;
      bool pWjVVmHhMc = false;
      bool AEUMzpywVy = false;
      bool qtypwnPHNe = false;
      bool ipzDrwKCCI = false;
      bool KVQJBLtcLf = false;
      bool heDYuuYsZh = false;
      bool WzUgtKFRUC = false;
      bool eutNnVdnoj = false;
      string dYFcatLhsp;
      string NKetAaORIb;
      string pZRTAuCzYw;
      string NxSkTCAkee;
      string uAXhaeySTc;
      string AUlNyEHkcf;
      string qMIxbQrsZy;
      string ZclcfoCirU;
      string wifwwsKFlP;
      string uOIzniqZFK;
      string mEsVDWhIgI;
      string BXsHiHfLBi;
      string FlHKDKUmox;
      string ybdghrpKsY;
      string KCXcNWVBQg;
      string CfYVFAxhRr;
      string CtTiKZtLYp;
      string QVSbYCNdxf;
      string nSWIuRDHbh;
      string uIrAWPioSm;
      if(dYFcatLhsp == mEsVDWhIgI){cKbZPfMwxC = true;}
      else if(mEsVDWhIgI == dYFcatLhsp){TuYXuREcmB = true;}
      if(NKetAaORIb == BXsHiHfLBi){lSkkDiXKmr = true;}
      else if(BXsHiHfLBi == NKetAaORIb){PPoKWfaZXl = true;}
      if(pZRTAuCzYw == FlHKDKUmox){WljquIcRFI = true;}
      else if(FlHKDKUmox == pZRTAuCzYw){pWjVVmHhMc = true;}
      if(NxSkTCAkee == ybdghrpKsY){TYKJDdpxrO = true;}
      else if(ybdghrpKsY == NxSkTCAkee){AEUMzpywVy = true;}
      if(uAXhaeySTc == KCXcNWVBQg){FGKYubWGxm = true;}
      else if(KCXcNWVBQg == uAXhaeySTc){qtypwnPHNe = true;}
      if(AUlNyEHkcf == CfYVFAxhRr){rXBZQqakdH = true;}
      else if(CfYVFAxhRr == AUlNyEHkcf){ipzDrwKCCI = true;}
      if(qMIxbQrsZy == CtTiKZtLYp){CuqniMHbhY = true;}
      else if(CtTiKZtLYp == qMIxbQrsZy){KVQJBLtcLf = true;}
      if(ZclcfoCirU == QVSbYCNdxf){rZSYmPaKuS = true;}
      if(wifwwsKFlP == nSWIuRDHbh){kWTRQwWkrM = true;}
      if(uOIzniqZFK == uIrAWPioSm){DFSjLJPWoh = true;}
      while(QVSbYCNdxf == ZclcfoCirU){heDYuuYsZh = true;}
      while(nSWIuRDHbh == nSWIuRDHbh){WzUgtKFRUC = true;}
      while(uIrAWPioSm == uIrAWPioSm){eutNnVdnoj = true;}
      if(cKbZPfMwxC == true){cKbZPfMwxC = false;}
      if(lSkkDiXKmr == true){lSkkDiXKmr = false;}
      if(WljquIcRFI == true){WljquIcRFI = false;}
      if(TYKJDdpxrO == true){TYKJDdpxrO = false;}
      if(FGKYubWGxm == true){FGKYubWGxm = false;}
      if(rXBZQqakdH == true){rXBZQqakdH = false;}
      if(CuqniMHbhY == true){CuqniMHbhY = false;}
      if(rZSYmPaKuS == true){rZSYmPaKuS = false;}
      if(kWTRQwWkrM == true){kWTRQwWkrM = false;}
      if(DFSjLJPWoh == true){DFSjLJPWoh = false;}
      if(TuYXuREcmB == true){TuYXuREcmB = false;}
      if(PPoKWfaZXl == true){PPoKWfaZXl = false;}
      if(pWjVVmHhMc == true){pWjVVmHhMc = false;}
      if(AEUMzpywVy == true){AEUMzpywVy = false;}
      if(qtypwnPHNe == true){qtypwnPHNe = false;}
      if(ipzDrwKCCI == true){ipzDrwKCCI = false;}
      if(KVQJBLtcLf == true){KVQJBLtcLf = false;}
      if(heDYuuYsZh == true){heDYuuYsZh = false;}
      if(WzUgtKFRUC == true){WzUgtKFRUC = false;}
      if(eutNnVdnoj == true){eutNnVdnoj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AEZETBHECD
{ 
  void QatBlQDpNV()
  { 
      bool enxNmFTfMg = false;
      bool FHwCJnpHLD = false;
      bool baWaMzAQfx = false;
      bool mbEYoZgdeI = false;
      bool tfBJpdgFdR = false;
      bool ncwgBDQWBm = false;
      bool EDzOscCWNi = false;
      bool HMbCJuZNjh = false;
      bool RulOIJfXWk = false;
      bool JJcrEqflPN = false;
      bool bJrtJaBsWF = false;
      bool dClSUJQkFi = false;
      bool weAbZxjjyR = false;
      bool PnxWGHCrEh = false;
      bool IlAQHGXKWt = false;
      bool auffQwJPUM = false;
      bool pQtEpoEPLN = false;
      bool HYgXaKeiUS = false;
      bool ZZNEqUHRFK = false;
      bool xmWrqqruaR = false;
      string MWLPTSZioi;
      string cVhOfbMCXD;
      string cmAVKMSyRm;
      string qbQiKgAiCU;
      string aEeUmOnXJQ;
      string woKebZVpEG;
      string AaQCqAFzEz;
      string adACbYHfhu;
      string XuoBqBRkGj;
      string KKduUAmcdm;
      string JoSKoSnHCD;
      string SpIJhElPKo;
      string hTrTnQzFhb;
      string kdBulibdLY;
      string NKiDRTBUNP;
      string NWRnEpwyVY;
      string SiZaRnoNWz;
      string cIDlbXjoCT;
      string OdrRONLNpw;
      string lcHmFekIkd;
      if(MWLPTSZioi == JoSKoSnHCD){enxNmFTfMg = true;}
      else if(JoSKoSnHCD == MWLPTSZioi){bJrtJaBsWF = true;}
      if(cVhOfbMCXD == SpIJhElPKo){FHwCJnpHLD = true;}
      else if(SpIJhElPKo == cVhOfbMCXD){dClSUJQkFi = true;}
      if(cmAVKMSyRm == hTrTnQzFhb){baWaMzAQfx = true;}
      else if(hTrTnQzFhb == cmAVKMSyRm){weAbZxjjyR = true;}
      if(qbQiKgAiCU == kdBulibdLY){mbEYoZgdeI = true;}
      else if(kdBulibdLY == qbQiKgAiCU){PnxWGHCrEh = true;}
      if(aEeUmOnXJQ == NKiDRTBUNP){tfBJpdgFdR = true;}
      else if(NKiDRTBUNP == aEeUmOnXJQ){IlAQHGXKWt = true;}
      if(woKebZVpEG == NWRnEpwyVY){ncwgBDQWBm = true;}
      else if(NWRnEpwyVY == woKebZVpEG){auffQwJPUM = true;}
      if(AaQCqAFzEz == SiZaRnoNWz){EDzOscCWNi = true;}
      else if(SiZaRnoNWz == AaQCqAFzEz){pQtEpoEPLN = true;}
      if(adACbYHfhu == cIDlbXjoCT){HMbCJuZNjh = true;}
      if(XuoBqBRkGj == OdrRONLNpw){RulOIJfXWk = true;}
      if(KKduUAmcdm == lcHmFekIkd){JJcrEqflPN = true;}
      while(cIDlbXjoCT == adACbYHfhu){HYgXaKeiUS = true;}
      while(OdrRONLNpw == OdrRONLNpw){ZZNEqUHRFK = true;}
      while(lcHmFekIkd == lcHmFekIkd){xmWrqqruaR = true;}
      if(enxNmFTfMg == true){enxNmFTfMg = false;}
      if(FHwCJnpHLD == true){FHwCJnpHLD = false;}
      if(baWaMzAQfx == true){baWaMzAQfx = false;}
      if(mbEYoZgdeI == true){mbEYoZgdeI = false;}
      if(tfBJpdgFdR == true){tfBJpdgFdR = false;}
      if(ncwgBDQWBm == true){ncwgBDQWBm = false;}
      if(EDzOscCWNi == true){EDzOscCWNi = false;}
      if(HMbCJuZNjh == true){HMbCJuZNjh = false;}
      if(RulOIJfXWk == true){RulOIJfXWk = false;}
      if(JJcrEqflPN == true){JJcrEqflPN = false;}
      if(bJrtJaBsWF == true){bJrtJaBsWF = false;}
      if(dClSUJQkFi == true){dClSUJQkFi = false;}
      if(weAbZxjjyR == true){weAbZxjjyR = false;}
      if(PnxWGHCrEh == true){PnxWGHCrEh = false;}
      if(IlAQHGXKWt == true){IlAQHGXKWt = false;}
      if(auffQwJPUM == true){auffQwJPUM = false;}
      if(pQtEpoEPLN == true){pQtEpoEPLN = false;}
      if(HYgXaKeiUS == true){HYgXaKeiUS = false;}
      if(ZZNEqUHRFK == true){ZZNEqUHRFK = false;}
      if(xmWrqqruaR == true){xmWrqqruaR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGBERXTSNS
{ 
  void kxXfsJLTWK()
  { 
      bool JjrkVWXlqo = false;
      bool MqcktZlZEL = false;
      bool UILLcEdpIa = false;
      bool kInVZRJRdS = false;
      bool BBmgwGWNce = false;
      bool ZzcJwBYgIR = false;
      bool rgcQDDCGKb = false;
      bool QTukJSUdOV = false;
      bool gQNdAkedZY = false;
      bool sbJLaUXVcr = false;
      bool DPCANFDrzc = false;
      bool ftSljbSzPS = false;
      bool XYglioJiKo = false;
      bool uzAVRRNNPt = false;
      bool gmewryJXby = false;
      bool BXFKUehQQY = false;
      bool wTgKggswTS = false;
      bool OFjVkjtksk = false;
      bool flHMmWsoBm = false;
      bool jwwpyMGTPL = false;
      string NQfCsyaHmF;
      string WPDWwuQYMG;
      string LnqxlErFqV;
      string KOjgrTEIZw;
      string ThJORDnEfH;
      string yEPWaYZhPo;
      string FVQQuIfWdc;
      string qHzQmdecei;
      string PnYjWGyMFS;
      string tVsjqxRrTJ;
      string WRZDQpEzjx;
      string twDfYRxfsn;
      string JTRLhUOOYo;
      string LlJVMyNUSg;
      string BzcHYxSMLY;
      string zkyezDAOVw;
      string boZtlImhTa;
      string DcNMmKqJlj;
      string CBDApZmeVI;
      string xzyWELZhVQ;
      if(NQfCsyaHmF == WRZDQpEzjx){JjrkVWXlqo = true;}
      else if(WRZDQpEzjx == NQfCsyaHmF){DPCANFDrzc = true;}
      if(WPDWwuQYMG == twDfYRxfsn){MqcktZlZEL = true;}
      else if(twDfYRxfsn == WPDWwuQYMG){ftSljbSzPS = true;}
      if(LnqxlErFqV == JTRLhUOOYo){UILLcEdpIa = true;}
      else if(JTRLhUOOYo == LnqxlErFqV){XYglioJiKo = true;}
      if(KOjgrTEIZw == LlJVMyNUSg){kInVZRJRdS = true;}
      else if(LlJVMyNUSg == KOjgrTEIZw){uzAVRRNNPt = true;}
      if(ThJORDnEfH == BzcHYxSMLY){BBmgwGWNce = true;}
      else if(BzcHYxSMLY == ThJORDnEfH){gmewryJXby = true;}
      if(yEPWaYZhPo == zkyezDAOVw){ZzcJwBYgIR = true;}
      else if(zkyezDAOVw == yEPWaYZhPo){BXFKUehQQY = true;}
      if(FVQQuIfWdc == boZtlImhTa){rgcQDDCGKb = true;}
      else if(boZtlImhTa == FVQQuIfWdc){wTgKggswTS = true;}
      if(qHzQmdecei == DcNMmKqJlj){QTukJSUdOV = true;}
      if(PnYjWGyMFS == CBDApZmeVI){gQNdAkedZY = true;}
      if(tVsjqxRrTJ == xzyWELZhVQ){sbJLaUXVcr = true;}
      while(DcNMmKqJlj == qHzQmdecei){OFjVkjtksk = true;}
      while(CBDApZmeVI == CBDApZmeVI){flHMmWsoBm = true;}
      while(xzyWELZhVQ == xzyWELZhVQ){jwwpyMGTPL = true;}
      if(JjrkVWXlqo == true){JjrkVWXlqo = false;}
      if(MqcktZlZEL == true){MqcktZlZEL = false;}
      if(UILLcEdpIa == true){UILLcEdpIa = false;}
      if(kInVZRJRdS == true){kInVZRJRdS = false;}
      if(BBmgwGWNce == true){BBmgwGWNce = false;}
      if(ZzcJwBYgIR == true){ZzcJwBYgIR = false;}
      if(rgcQDDCGKb == true){rgcQDDCGKb = false;}
      if(QTukJSUdOV == true){QTukJSUdOV = false;}
      if(gQNdAkedZY == true){gQNdAkedZY = false;}
      if(sbJLaUXVcr == true){sbJLaUXVcr = false;}
      if(DPCANFDrzc == true){DPCANFDrzc = false;}
      if(ftSljbSzPS == true){ftSljbSzPS = false;}
      if(XYglioJiKo == true){XYglioJiKo = false;}
      if(uzAVRRNNPt == true){uzAVRRNNPt = false;}
      if(gmewryJXby == true){gmewryJXby = false;}
      if(BXFKUehQQY == true){BXFKUehQQY = false;}
      if(wTgKggswTS == true){wTgKggswTS = false;}
      if(OFjVkjtksk == true){OFjVkjtksk = false;}
      if(flHMmWsoBm == true){flHMmWsoBm = false;}
      if(jwwpyMGTPL == true){jwwpyMGTPL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLJQWEYPMW
{ 
  void jVTJlAuDot()
  { 
      bool ndGgBCNFRx = false;
      bool VaiUpWNNIL = false;
      bool WbIzDrkGia = false;
      bool jFqaGcOpUb = false;
      bool OgEwwulNeu = false;
      bool BuNgOLUGcJ = false;
      bool RGVpMPiINM = false;
      bool IWsgwoXMDI = false;
      bool GWbnZnqJLt = false;
      bool IHMLKILOif = false;
      bool LcASldCgkZ = false;
      bool nIDUDtdhPY = false;
      bool YZwSEBKgWm = false;
      bool dIcWwcWJBu = false;
      bool lKXlFzDrHP = false;
      bool dcyKHkggNj = false;
      bool TUKyufegXZ = false;
      bool WUfTlOBKNE = false;
      bool ySZGIAJROK = false;
      bool wpuRbQzZpZ = false;
      string DepBIjEltW;
      string RHAUPUqWZp;
      string inbqSqhpok;
      string TPYuNSQoeu;
      string BgbAdSgLun;
      string mGAbIODyhQ;
      string BNwJDBiEHx;
      string EBqenCLaMA;
      string JVuBxNOwmy;
      string ORHNsnjSxc;
      string jcExilOVmG;
      string CblhGeRtMo;
      string llRIhltdkA;
      string RsdjPgRyRK;
      string zsJgumfYGO;
      string VoGHpyKwPw;
      string rjjmnJyCRZ;
      string NTbBpsbjMu;
      string GUWWdblVsR;
      string VUhUSOJWsl;
      if(DepBIjEltW == jcExilOVmG){ndGgBCNFRx = true;}
      else if(jcExilOVmG == DepBIjEltW){LcASldCgkZ = true;}
      if(RHAUPUqWZp == CblhGeRtMo){VaiUpWNNIL = true;}
      else if(CblhGeRtMo == RHAUPUqWZp){nIDUDtdhPY = true;}
      if(inbqSqhpok == llRIhltdkA){WbIzDrkGia = true;}
      else if(llRIhltdkA == inbqSqhpok){YZwSEBKgWm = true;}
      if(TPYuNSQoeu == RsdjPgRyRK){jFqaGcOpUb = true;}
      else if(RsdjPgRyRK == TPYuNSQoeu){dIcWwcWJBu = true;}
      if(BgbAdSgLun == zsJgumfYGO){OgEwwulNeu = true;}
      else if(zsJgumfYGO == BgbAdSgLun){lKXlFzDrHP = true;}
      if(mGAbIODyhQ == VoGHpyKwPw){BuNgOLUGcJ = true;}
      else if(VoGHpyKwPw == mGAbIODyhQ){dcyKHkggNj = true;}
      if(BNwJDBiEHx == rjjmnJyCRZ){RGVpMPiINM = true;}
      else if(rjjmnJyCRZ == BNwJDBiEHx){TUKyufegXZ = true;}
      if(EBqenCLaMA == NTbBpsbjMu){IWsgwoXMDI = true;}
      if(JVuBxNOwmy == GUWWdblVsR){GWbnZnqJLt = true;}
      if(ORHNsnjSxc == VUhUSOJWsl){IHMLKILOif = true;}
      while(NTbBpsbjMu == EBqenCLaMA){WUfTlOBKNE = true;}
      while(GUWWdblVsR == GUWWdblVsR){ySZGIAJROK = true;}
      while(VUhUSOJWsl == VUhUSOJWsl){wpuRbQzZpZ = true;}
      if(ndGgBCNFRx == true){ndGgBCNFRx = false;}
      if(VaiUpWNNIL == true){VaiUpWNNIL = false;}
      if(WbIzDrkGia == true){WbIzDrkGia = false;}
      if(jFqaGcOpUb == true){jFqaGcOpUb = false;}
      if(OgEwwulNeu == true){OgEwwulNeu = false;}
      if(BuNgOLUGcJ == true){BuNgOLUGcJ = false;}
      if(RGVpMPiINM == true){RGVpMPiINM = false;}
      if(IWsgwoXMDI == true){IWsgwoXMDI = false;}
      if(GWbnZnqJLt == true){GWbnZnqJLt = false;}
      if(IHMLKILOif == true){IHMLKILOif = false;}
      if(LcASldCgkZ == true){LcASldCgkZ = false;}
      if(nIDUDtdhPY == true){nIDUDtdhPY = false;}
      if(YZwSEBKgWm == true){YZwSEBKgWm = false;}
      if(dIcWwcWJBu == true){dIcWwcWJBu = false;}
      if(lKXlFzDrHP == true){lKXlFzDrHP = false;}
      if(dcyKHkggNj == true){dcyKHkggNj = false;}
      if(TUKyufegXZ == true){TUKyufegXZ = false;}
      if(WUfTlOBKNE == true){WUfTlOBKNE = false;}
      if(ySZGIAJROK == true){ySZGIAJROK = false;}
      if(wpuRbQzZpZ == true){wpuRbQzZpZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDZJLZXPCA
{ 
  void RzlAOQgPgw()
  { 
      bool txptUEHCGJ = false;
      bool MjkurGFHxf = false;
      bool biLssZkmFu = false;
      bool qAVOtspopw = false;
      bool IdFdVIuUcG = false;
      bool LPjwrKkxAu = false;
      bool SUwKRLNWBy = false;
      bool QQRBXycgWk = false;
      bool dQKyiaPYVi = false;
      bool HsntdmguLK = false;
      bool tXTdpuyiYt = false;
      bool gEZPQCJxaq = false;
      bool unARpWbWWj = false;
      bool QhUMpFwfIm = false;
      bool cgAbCDTYcb = false;
      bool diTUOFXBmS = false;
      bool TaLncyiMYK = false;
      bool FdonOOnXPm = false;
      bool DDtuGgOAxk = false;
      bool htspTBUMyD = false;
      string lXkAJpwbHr;
      string dLGhJHtxju;
      string TldfDNGcpz;
      string RXJikMMVoQ;
      string dMwLlNebMQ;
      string LKZWhztEww;
      string jTkHZFCXxx;
      string tYHSQGpRsp;
      string hdQZnHylAl;
      string SHYsgJbnlf;
      string LGeOVmCGFa;
      string JbLGNFDLTR;
      string HPXKemzOlH;
      string eBfMdbzBDB;
      string FrgYcpwSfa;
      string GPUTYuiTji;
      string mnTywIwzbl;
      string FCHSMPiyhn;
      string pgiLAPfMmi;
      string rfQUNQXhcT;
      if(lXkAJpwbHr == LGeOVmCGFa){txptUEHCGJ = true;}
      else if(LGeOVmCGFa == lXkAJpwbHr){tXTdpuyiYt = true;}
      if(dLGhJHtxju == JbLGNFDLTR){MjkurGFHxf = true;}
      else if(JbLGNFDLTR == dLGhJHtxju){gEZPQCJxaq = true;}
      if(TldfDNGcpz == HPXKemzOlH){biLssZkmFu = true;}
      else if(HPXKemzOlH == TldfDNGcpz){unARpWbWWj = true;}
      if(RXJikMMVoQ == eBfMdbzBDB){qAVOtspopw = true;}
      else if(eBfMdbzBDB == RXJikMMVoQ){QhUMpFwfIm = true;}
      if(dMwLlNebMQ == FrgYcpwSfa){IdFdVIuUcG = true;}
      else if(FrgYcpwSfa == dMwLlNebMQ){cgAbCDTYcb = true;}
      if(LKZWhztEww == GPUTYuiTji){LPjwrKkxAu = true;}
      else if(GPUTYuiTji == LKZWhztEww){diTUOFXBmS = true;}
      if(jTkHZFCXxx == mnTywIwzbl){SUwKRLNWBy = true;}
      else if(mnTywIwzbl == jTkHZFCXxx){TaLncyiMYK = true;}
      if(tYHSQGpRsp == FCHSMPiyhn){QQRBXycgWk = true;}
      if(hdQZnHylAl == pgiLAPfMmi){dQKyiaPYVi = true;}
      if(SHYsgJbnlf == rfQUNQXhcT){HsntdmguLK = true;}
      while(FCHSMPiyhn == tYHSQGpRsp){FdonOOnXPm = true;}
      while(pgiLAPfMmi == pgiLAPfMmi){DDtuGgOAxk = true;}
      while(rfQUNQXhcT == rfQUNQXhcT){htspTBUMyD = true;}
      if(txptUEHCGJ == true){txptUEHCGJ = false;}
      if(MjkurGFHxf == true){MjkurGFHxf = false;}
      if(biLssZkmFu == true){biLssZkmFu = false;}
      if(qAVOtspopw == true){qAVOtspopw = false;}
      if(IdFdVIuUcG == true){IdFdVIuUcG = false;}
      if(LPjwrKkxAu == true){LPjwrKkxAu = false;}
      if(SUwKRLNWBy == true){SUwKRLNWBy = false;}
      if(QQRBXycgWk == true){QQRBXycgWk = false;}
      if(dQKyiaPYVi == true){dQKyiaPYVi = false;}
      if(HsntdmguLK == true){HsntdmguLK = false;}
      if(tXTdpuyiYt == true){tXTdpuyiYt = false;}
      if(gEZPQCJxaq == true){gEZPQCJxaq = false;}
      if(unARpWbWWj == true){unARpWbWWj = false;}
      if(QhUMpFwfIm == true){QhUMpFwfIm = false;}
      if(cgAbCDTYcb == true){cgAbCDTYcb = false;}
      if(diTUOFXBmS == true){diTUOFXBmS = false;}
      if(TaLncyiMYK == true){TaLncyiMYK = false;}
      if(FdonOOnXPm == true){FdonOOnXPm = false;}
      if(DDtuGgOAxk == true){DDtuGgOAxk = false;}
      if(htspTBUMyD == true){htspTBUMyD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNWDRHJRHW
{ 
  void HityFyRWSy()
  { 
      bool YZhEJNyXox = false;
      bool wqlXKKNTsY = false;
      bool DhmWylViuu = false;
      bool NYiRmTPXzW = false;
      bool oXEjZQBbFn = false;
      bool qfBeWqlKGX = false;
      bool rPcsjXIUkp = false;
      bool uoTWiecDxg = false;
      bool kscHEgWDtw = false;
      bool hFRbdZuKzC = false;
      bool IfpPsBMdwq = false;
      bool NhMYmylUoC = false;
      bool AEZoHoXrsI = false;
      bool iSDuYECNND = false;
      bool UrHDhzrroe = false;
      bool nZVxBDGBHD = false;
      bool dUkmHueRAh = false;
      bool uXHlhHwWGI = false;
      bool xeCNUIxGsU = false;
      bool yBGKYAHTum = false;
      string rXQAiZrnlU;
      string pBkwZYIFDn;
      string BslBZVTFGw;
      string wthQnzZfOh;
      string dyJNBdBEXr;
      string JUrJBykPaM;
      string GmgoYuSTHZ;
      string zcpUKCjYzw;
      string UOgNmaCYPo;
      string NKECapQUnF;
      string KhwxsfeXzy;
      string OMPerrFTBx;
      string stDSMoXmsU;
      string lOktllRjUH;
      string weZQZAuZKi;
      string jxSpMPddjE;
      string IqddMzbUrF;
      string ZVztBOTmrL;
      string txcJjnwthV;
      string HmAPzFAuDZ;
      if(rXQAiZrnlU == KhwxsfeXzy){YZhEJNyXox = true;}
      else if(KhwxsfeXzy == rXQAiZrnlU){IfpPsBMdwq = true;}
      if(pBkwZYIFDn == OMPerrFTBx){wqlXKKNTsY = true;}
      else if(OMPerrFTBx == pBkwZYIFDn){NhMYmylUoC = true;}
      if(BslBZVTFGw == stDSMoXmsU){DhmWylViuu = true;}
      else if(stDSMoXmsU == BslBZVTFGw){AEZoHoXrsI = true;}
      if(wthQnzZfOh == lOktllRjUH){NYiRmTPXzW = true;}
      else if(lOktllRjUH == wthQnzZfOh){iSDuYECNND = true;}
      if(dyJNBdBEXr == weZQZAuZKi){oXEjZQBbFn = true;}
      else if(weZQZAuZKi == dyJNBdBEXr){UrHDhzrroe = true;}
      if(JUrJBykPaM == jxSpMPddjE){qfBeWqlKGX = true;}
      else if(jxSpMPddjE == JUrJBykPaM){nZVxBDGBHD = true;}
      if(GmgoYuSTHZ == IqddMzbUrF){rPcsjXIUkp = true;}
      else if(IqddMzbUrF == GmgoYuSTHZ){dUkmHueRAh = true;}
      if(zcpUKCjYzw == ZVztBOTmrL){uoTWiecDxg = true;}
      if(UOgNmaCYPo == txcJjnwthV){kscHEgWDtw = true;}
      if(NKECapQUnF == HmAPzFAuDZ){hFRbdZuKzC = true;}
      while(ZVztBOTmrL == zcpUKCjYzw){uXHlhHwWGI = true;}
      while(txcJjnwthV == txcJjnwthV){xeCNUIxGsU = true;}
      while(HmAPzFAuDZ == HmAPzFAuDZ){yBGKYAHTum = true;}
      if(YZhEJNyXox == true){YZhEJNyXox = false;}
      if(wqlXKKNTsY == true){wqlXKKNTsY = false;}
      if(DhmWylViuu == true){DhmWylViuu = false;}
      if(NYiRmTPXzW == true){NYiRmTPXzW = false;}
      if(oXEjZQBbFn == true){oXEjZQBbFn = false;}
      if(qfBeWqlKGX == true){qfBeWqlKGX = false;}
      if(rPcsjXIUkp == true){rPcsjXIUkp = false;}
      if(uoTWiecDxg == true){uoTWiecDxg = false;}
      if(kscHEgWDtw == true){kscHEgWDtw = false;}
      if(hFRbdZuKzC == true){hFRbdZuKzC = false;}
      if(IfpPsBMdwq == true){IfpPsBMdwq = false;}
      if(NhMYmylUoC == true){NhMYmylUoC = false;}
      if(AEZoHoXrsI == true){AEZoHoXrsI = false;}
      if(iSDuYECNND == true){iSDuYECNND = false;}
      if(UrHDhzrroe == true){UrHDhzrroe = false;}
      if(nZVxBDGBHD == true){nZVxBDGBHD = false;}
      if(dUkmHueRAh == true){dUkmHueRAh = false;}
      if(uXHlhHwWGI == true){uXHlhHwWGI = false;}
      if(xeCNUIxGsU == true){xeCNUIxGsU = false;}
      if(yBGKYAHTum == true){yBGKYAHTum = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZRTKAPOGQ
{ 
  void FSdulUKMLY()
  { 
      bool nLyhIKLzUq = false;
      bool EkWfVnedGJ = false;
      bool MlJNwGjtzs = false;
      bool OBOXYfbRhL = false;
      bool hRVWpJbSnM = false;
      bool OczCTBBkkB = false;
      bool aQzacDVyHo = false;
      bool LNutatQmWm = false;
      bool dQFmekCMEW = false;
      bool eqffkQRtsm = false;
      bool mcLzABgFaY = false;
      bool jOOyXKKMwr = false;
      bool BJtjKUgPJK = false;
      bool cWsjABFGlc = false;
      bool DwkelQchIa = false;
      bool FFxBldiaoe = false;
      bool TRuQwNUdyV = false;
      bool EEZTnEXPxs = false;
      bool rzHiEWZryW = false;
      bool SdRHIlBUhY = false;
      string SobPiaIMDa;
      string RfQHWiIYpz;
      string tlnplccQSV;
      string gVKxmwVBbr;
      string NnBQFZULzD;
      string FCWfUgBkcF;
      string yrshswVSUa;
      string NGwylGkXkM;
      string IRQOPezdcF;
      string ukXWtUuSWJ;
      string EBpYpyFXtN;
      string ucAQxfadRN;
      string wqpOebiZEQ;
      string KRAbHGarYQ;
      string ZaiOJRjHZN;
      string sQAJMMLbsN;
      string PeTcDdcYIq;
      string FiFBnUHaEN;
      string raApWsRpOu;
      string tzzKBtGGLf;
      if(SobPiaIMDa == EBpYpyFXtN){nLyhIKLzUq = true;}
      else if(EBpYpyFXtN == SobPiaIMDa){mcLzABgFaY = true;}
      if(RfQHWiIYpz == ucAQxfadRN){EkWfVnedGJ = true;}
      else if(ucAQxfadRN == RfQHWiIYpz){jOOyXKKMwr = true;}
      if(tlnplccQSV == wqpOebiZEQ){MlJNwGjtzs = true;}
      else if(wqpOebiZEQ == tlnplccQSV){BJtjKUgPJK = true;}
      if(gVKxmwVBbr == KRAbHGarYQ){OBOXYfbRhL = true;}
      else if(KRAbHGarYQ == gVKxmwVBbr){cWsjABFGlc = true;}
      if(NnBQFZULzD == ZaiOJRjHZN){hRVWpJbSnM = true;}
      else if(ZaiOJRjHZN == NnBQFZULzD){DwkelQchIa = true;}
      if(FCWfUgBkcF == sQAJMMLbsN){OczCTBBkkB = true;}
      else if(sQAJMMLbsN == FCWfUgBkcF){FFxBldiaoe = true;}
      if(yrshswVSUa == PeTcDdcYIq){aQzacDVyHo = true;}
      else if(PeTcDdcYIq == yrshswVSUa){TRuQwNUdyV = true;}
      if(NGwylGkXkM == FiFBnUHaEN){LNutatQmWm = true;}
      if(IRQOPezdcF == raApWsRpOu){dQFmekCMEW = true;}
      if(ukXWtUuSWJ == tzzKBtGGLf){eqffkQRtsm = true;}
      while(FiFBnUHaEN == NGwylGkXkM){EEZTnEXPxs = true;}
      while(raApWsRpOu == raApWsRpOu){rzHiEWZryW = true;}
      while(tzzKBtGGLf == tzzKBtGGLf){SdRHIlBUhY = true;}
      if(nLyhIKLzUq == true){nLyhIKLzUq = false;}
      if(EkWfVnedGJ == true){EkWfVnedGJ = false;}
      if(MlJNwGjtzs == true){MlJNwGjtzs = false;}
      if(OBOXYfbRhL == true){OBOXYfbRhL = false;}
      if(hRVWpJbSnM == true){hRVWpJbSnM = false;}
      if(OczCTBBkkB == true){OczCTBBkkB = false;}
      if(aQzacDVyHo == true){aQzacDVyHo = false;}
      if(LNutatQmWm == true){LNutatQmWm = false;}
      if(dQFmekCMEW == true){dQFmekCMEW = false;}
      if(eqffkQRtsm == true){eqffkQRtsm = false;}
      if(mcLzABgFaY == true){mcLzABgFaY = false;}
      if(jOOyXKKMwr == true){jOOyXKKMwr = false;}
      if(BJtjKUgPJK == true){BJtjKUgPJK = false;}
      if(cWsjABFGlc == true){cWsjABFGlc = false;}
      if(DwkelQchIa == true){DwkelQchIa = false;}
      if(FFxBldiaoe == true){FFxBldiaoe = false;}
      if(TRuQwNUdyV == true){TRuQwNUdyV = false;}
      if(EEZTnEXPxs == true){EEZTnEXPxs = false;}
      if(rzHiEWZryW == true){rzHiEWZryW = false;}
      if(SdRHIlBUhY == true){SdRHIlBUhY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXWBPWKHEK
{ 
  void oiLMENHHLf()
  { 
      bool zZMLTexfJD = false;
      bool htCSDUSDlF = false;
      bool kKtxzGCkVl = false;
      bool qkKzrznply = false;
      bool igkbJkqrdG = false;
      bool JfXMZoePMN = false;
      bool bLKXMwiDZE = false;
      bool gcQmVEYRmO = false;
      bool OKGObLMyYD = false;
      bool TXdYVXWMPM = false;
      bool BnRZZgOkpU = false;
      bool PNbyyRFuwB = false;
      bool jjdWjIzqQy = false;
      bool hLCaMarfou = false;
      bool wbHDmGweaE = false;
      bool RaQNcRJupQ = false;
      bool hXTrmEKBlW = false;
      bool ZYGBFHbajd = false;
      bool MTQMfGunyu = false;
      bool RwpXMXIPQi = false;
      string QFrnYkfXea;
      string JpoZooIgWu;
      string kKXzHioPdL;
      string xNETFMdsOV;
      string tpsPrkaBkO;
      string nikpdGgrfo;
      string uPtTcukVTc;
      string LPSBBtQHHV;
      string HneOWOcOoz;
      string ekMYadwZmw;
      string AEgIDYPjnj;
      string oZkKhGkewN;
      string SWgUxZCsZX;
      string xqUKVCGWLy;
      string zraEJFABqT;
      string sQdYddWMKc;
      string VVJQlyFaoe;
      string ANTyOZucKr;
      string ZACGdgMufq;
      string esLhbciKRL;
      if(QFrnYkfXea == AEgIDYPjnj){zZMLTexfJD = true;}
      else if(AEgIDYPjnj == QFrnYkfXea){BnRZZgOkpU = true;}
      if(JpoZooIgWu == oZkKhGkewN){htCSDUSDlF = true;}
      else if(oZkKhGkewN == JpoZooIgWu){PNbyyRFuwB = true;}
      if(kKXzHioPdL == SWgUxZCsZX){kKtxzGCkVl = true;}
      else if(SWgUxZCsZX == kKXzHioPdL){jjdWjIzqQy = true;}
      if(xNETFMdsOV == xqUKVCGWLy){qkKzrznply = true;}
      else if(xqUKVCGWLy == xNETFMdsOV){hLCaMarfou = true;}
      if(tpsPrkaBkO == zraEJFABqT){igkbJkqrdG = true;}
      else if(zraEJFABqT == tpsPrkaBkO){wbHDmGweaE = true;}
      if(nikpdGgrfo == sQdYddWMKc){JfXMZoePMN = true;}
      else if(sQdYddWMKc == nikpdGgrfo){RaQNcRJupQ = true;}
      if(uPtTcukVTc == VVJQlyFaoe){bLKXMwiDZE = true;}
      else if(VVJQlyFaoe == uPtTcukVTc){hXTrmEKBlW = true;}
      if(LPSBBtQHHV == ANTyOZucKr){gcQmVEYRmO = true;}
      if(HneOWOcOoz == ZACGdgMufq){OKGObLMyYD = true;}
      if(ekMYadwZmw == esLhbciKRL){TXdYVXWMPM = true;}
      while(ANTyOZucKr == LPSBBtQHHV){ZYGBFHbajd = true;}
      while(ZACGdgMufq == ZACGdgMufq){MTQMfGunyu = true;}
      while(esLhbciKRL == esLhbciKRL){RwpXMXIPQi = true;}
      if(zZMLTexfJD == true){zZMLTexfJD = false;}
      if(htCSDUSDlF == true){htCSDUSDlF = false;}
      if(kKtxzGCkVl == true){kKtxzGCkVl = false;}
      if(qkKzrznply == true){qkKzrznply = false;}
      if(igkbJkqrdG == true){igkbJkqrdG = false;}
      if(JfXMZoePMN == true){JfXMZoePMN = false;}
      if(bLKXMwiDZE == true){bLKXMwiDZE = false;}
      if(gcQmVEYRmO == true){gcQmVEYRmO = false;}
      if(OKGObLMyYD == true){OKGObLMyYD = false;}
      if(TXdYVXWMPM == true){TXdYVXWMPM = false;}
      if(BnRZZgOkpU == true){BnRZZgOkpU = false;}
      if(PNbyyRFuwB == true){PNbyyRFuwB = false;}
      if(jjdWjIzqQy == true){jjdWjIzqQy = false;}
      if(hLCaMarfou == true){hLCaMarfou = false;}
      if(wbHDmGweaE == true){wbHDmGweaE = false;}
      if(RaQNcRJupQ == true){RaQNcRJupQ = false;}
      if(hXTrmEKBlW == true){hXTrmEKBlW = false;}
      if(ZYGBFHbajd == true){ZYGBFHbajd = false;}
      if(MTQMfGunyu == true){MTQMfGunyu = false;}
      if(RwpXMXIPQi == true){RwpXMXIPQi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LLYPXRMQWN
{ 
  void RDnqxBQJVN()
  { 
      bool QjNGHNqNgj = false;
      bool oCjzpMiyIK = false;
      bool fHtGqrbCdK = false;
      bool BYgXtpOTEg = false;
      bool lYrdnfRpKI = false;
      bool kWEsaJoHPP = false;
      bool lniWhPULFz = false;
      bool xOtbXGPQSL = false;
      bool alqVZeUnwk = false;
      bool BHEotxoVwY = false;
      bool KGkLKVbcUU = false;
      bool sYoEnAxNwD = false;
      bool tfPTypKFgZ = false;
      bool QtTtAUBfKD = false;
      bool CrTbqbSAAt = false;
      bool AbYsddpQNU = false;
      bool LWuuDzEuDT = false;
      bool zQCrACMmcV = false;
      bool WKFlYoUaPV = false;
      bool djRprfwYYr = false;
      string jIRqTELGxt;
      string VGwnUfYorU;
      string hogERlFTgI;
      string qLFMosmLHN;
      string rqOYWgATxd;
      string exEIFtbNYg;
      string yqYoDKBjzb;
      string sNgdcqaIhk;
      string llWDctGxGt;
      string RYlaOARZVL;
      string fQUUkRPZfO;
      string TTfnuMTVLI;
      string DEcFJTaGOb;
      string ZBlVEVRBRL;
      string dfQrZysxfC;
      string guNMHbmOLQ;
      string pJKDnSgJiY;
      string tSEzeXmkeL;
      string acaMudmYOc;
      string hCpBUTVNDH;
      if(jIRqTELGxt == fQUUkRPZfO){QjNGHNqNgj = true;}
      else if(fQUUkRPZfO == jIRqTELGxt){KGkLKVbcUU = true;}
      if(VGwnUfYorU == TTfnuMTVLI){oCjzpMiyIK = true;}
      else if(TTfnuMTVLI == VGwnUfYorU){sYoEnAxNwD = true;}
      if(hogERlFTgI == DEcFJTaGOb){fHtGqrbCdK = true;}
      else if(DEcFJTaGOb == hogERlFTgI){tfPTypKFgZ = true;}
      if(qLFMosmLHN == ZBlVEVRBRL){BYgXtpOTEg = true;}
      else if(ZBlVEVRBRL == qLFMosmLHN){QtTtAUBfKD = true;}
      if(rqOYWgATxd == dfQrZysxfC){lYrdnfRpKI = true;}
      else if(dfQrZysxfC == rqOYWgATxd){CrTbqbSAAt = true;}
      if(exEIFtbNYg == guNMHbmOLQ){kWEsaJoHPP = true;}
      else if(guNMHbmOLQ == exEIFtbNYg){AbYsddpQNU = true;}
      if(yqYoDKBjzb == pJKDnSgJiY){lniWhPULFz = true;}
      else if(pJKDnSgJiY == yqYoDKBjzb){LWuuDzEuDT = true;}
      if(sNgdcqaIhk == tSEzeXmkeL){xOtbXGPQSL = true;}
      if(llWDctGxGt == acaMudmYOc){alqVZeUnwk = true;}
      if(RYlaOARZVL == hCpBUTVNDH){BHEotxoVwY = true;}
      while(tSEzeXmkeL == sNgdcqaIhk){zQCrACMmcV = true;}
      while(acaMudmYOc == acaMudmYOc){WKFlYoUaPV = true;}
      while(hCpBUTVNDH == hCpBUTVNDH){djRprfwYYr = true;}
      if(QjNGHNqNgj == true){QjNGHNqNgj = false;}
      if(oCjzpMiyIK == true){oCjzpMiyIK = false;}
      if(fHtGqrbCdK == true){fHtGqrbCdK = false;}
      if(BYgXtpOTEg == true){BYgXtpOTEg = false;}
      if(lYrdnfRpKI == true){lYrdnfRpKI = false;}
      if(kWEsaJoHPP == true){kWEsaJoHPP = false;}
      if(lniWhPULFz == true){lniWhPULFz = false;}
      if(xOtbXGPQSL == true){xOtbXGPQSL = false;}
      if(alqVZeUnwk == true){alqVZeUnwk = false;}
      if(BHEotxoVwY == true){BHEotxoVwY = false;}
      if(KGkLKVbcUU == true){KGkLKVbcUU = false;}
      if(sYoEnAxNwD == true){sYoEnAxNwD = false;}
      if(tfPTypKFgZ == true){tfPTypKFgZ = false;}
      if(QtTtAUBfKD == true){QtTtAUBfKD = false;}
      if(CrTbqbSAAt == true){CrTbqbSAAt = false;}
      if(AbYsddpQNU == true){AbYsddpQNU = false;}
      if(LWuuDzEuDT == true){LWuuDzEuDT = false;}
      if(zQCrACMmcV == true){zQCrACMmcV = false;}
      if(WKFlYoUaPV == true){WKFlYoUaPV = false;}
      if(djRprfwYYr == true){djRprfwYYr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGLTTRSNFN
{ 
  void BmRRfXFGgl()
  { 
      bool CfYiPpUVyr = false;
      bool RrzYGmZEVT = false;
      bool zKQGUaNOzp = false;
      bool oYtqmhSEDP = false;
      bool mqmdpMiFOn = false;
      bool VHdgOqORNn = false;
      bool bFWHCryHkY = false;
      bool TVAFgIXlPH = false;
      bool rHAKUguMbw = false;
      bool SApPmhTfby = false;
      bool NbToUzHXAG = false;
      bool TcCGwUEMlU = false;
      bool wleoGSfjRy = false;
      bool nrKQtPnKoU = false;
      bool ZWLVboxjTS = false;
      bool cHsGBbweiB = false;
      bool TWFCSbRlLf = false;
      bool gtWRuZZJNQ = false;
      bool UwQzVfyDPS = false;
      bool TIbnADQJDz = false;
      string RPQemZgQwM;
      string YFsliajaTF;
      string qJwQaMxAxB;
      string ykMBGgWECB;
      string zyWtTjFTEF;
      string mgjVhISAEa;
      string bgStNnrrfB;
      string EeXSGrlCwp;
      string HcurNRBqSx;
      string OWAbYSfcff;
      string qNnCBIIQPo;
      string VQDNTzkafu;
      string lAYhmgdusm;
      string MJVPzsospF;
      string IjbdbxTmIZ;
      string gEwjtpnFOU;
      string dMXbbMumOZ;
      string KqjalBYuGp;
      string NqmTFHMkVI;
      string FidVawMzBO;
      if(RPQemZgQwM == qNnCBIIQPo){CfYiPpUVyr = true;}
      else if(qNnCBIIQPo == RPQemZgQwM){NbToUzHXAG = true;}
      if(YFsliajaTF == VQDNTzkafu){RrzYGmZEVT = true;}
      else if(VQDNTzkafu == YFsliajaTF){TcCGwUEMlU = true;}
      if(qJwQaMxAxB == lAYhmgdusm){zKQGUaNOzp = true;}
      else if(lAYhmgdusm == qJwQaMxAxB){wleoGSfjRy = true;}
      if(ykMBGgWECB == MJVPzsospF){oYtqmhSEDP = true;}
      else if(MJVPzsospF == ykMBGgWECB){nrKQtPnKoU = true;}
      if(zyWtTjFTEF == IjbdbxTmIZ){mqmdpMiFOn = true;}
      else if(IjbdbxTmIZ == zyWtTjFTEF){ZWLVboxjTS = true;}
      if(mgjVhISAEa == gEwjtpnFOU){VHdgOqORNn = true;}
      else if(gEwjtpnFOU == mgjVhISAEa){cHsGBbweiB = true;}
      if(bgStNnrrfB == dMXbbMumOZ){bFWHCryHkY = true;}
      else if(dMXbbMumOZ == bgStNnrrfB){TWFCSbRlLf = true;}
      if(EeXSGrlCwp == KqjalBYuGp){TVAFgIXlPH = true;}
      if(HcurNRBqSx == NqmTFHMkVI){rHAKUguMbw = true;}
      if(OWAbYSfcff == FidVawMzBO){SApPmhTfby = true;}
      while(KqjalBYuGp == EeXSGrlCwp){gtWRuZZJNQ = true;}
      while(NqmTFHMkVI == NqmTFHMkVI){UwQzVfyDPS = true;}
      while(FidVawMzBO == FidVawMzBO){TIbnADQJDz = true;}
      if(CfYiPpUVyr == true){CfYiPpUVyr = false;}
      if(RrzYGmZEVT == true){RrzYGmZEVT = false;}
      if(zKQGUaNOzp == true){zKQGUaNOzp = false;}
      if(oYtqmhSEDP == true){oYtqmhSEDP = false;}
      if(mqmdpMiFOn == true){mqmdpMiFOn = false;}
      if(VHdgOqORNn == true){VHdgOqORNn = false;}
      if(bFWHCryHkY == true){bFWHCryHkY = false;}
      if(TVAFgIXlPH == true){TVAFgIXlPH = false;}
      if(rHAKUguMbw == true){rHAKUguMbw = false;}
      if(SApPmhTfby == true){SApPmhTfby = false;}
      if(NbToUzHXAG == true){NbToUzHXAG = false;}
      if(TcCGwUEMlU == true){TcCGwUEMlU = false;}
      if(wleoGSfjRy == true){wleoGSfjRy = false;}
      if(nrKQtPnKoU == true){nrKQtPnKoU = false;}
      if(ZWLVboxjTS == true){ZWLVboxjTS = false;}
      if(cHsGBbweiB == true){cHsGBbweiB = false;}
      if(TWFCSbRlLf == true){TWFCSbRlLf = false;}
      if(gtWRuZZJNQ == true){gtWRuZZJNQ = false;}
      if(UwQzVfyDPS == true){UwQzVfyDPS = false;}
      if(TIbnADQJDz == true){TIbnADQJDz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBGIUODZTN
{ 
  void IyAakYQyEm()
  { 
      bool NCenQKwPIk = false;
      bool AjSRMnlyGt = false;
      bool GgHtFdzzyD = false;
      bool tEuHnFDwiZ = false;
      bool uRdfsiOtiW = false;
      bool QrGjxgtkil = false;
      bool LwRFpwoLdG = false;
      bool koOfyoDaBV = false;
      bool PEQalCyKJH = false;
      bool KSNwOyzYow = false;
      bool tCQblbcZlI = false;
      bool cTjNWGfqSn = false;
      bool xeCWwRbSRA = false;
      bool oekEaNnonK = false;
      bool YYYAdqizZH = false;
      bool SIFBzOzsfT = false;
      bool AKHkSyielJ = false;
      bool SpCHOYGBsE = false;
      bool ibsJgfYjEM = false;
      bool NtJTKOQmge = false;
      string ayNPhpyZNJ;
      string HrPGNEsLwJ;
      string UBaSNBWXtI;
      string fSUpNahWwT;
      string niZZjMYboZ;
      string yjDSGYWuCf;
      string SafEcnXYsl;
      string VWOcUlbAiB;
      string cuhTKuOBjo;
      string DmTQANDUxu;
      string nziCDaVaxT;
      string wWMACXrLtg;
      string YVoEiiCybG;
      string iHCmMdLfQj;
      string ZnEPrgaTNb;
      string VqZPVSJeTU;
      string XWyqknTYnY;
      string LLuKGkRYLB;
      string HikzjqhmRt;
      string TgMuLDpMdE;
      if(ayNPhpyZNJ == nziCDaVaxT){NCenQKwPIk = true;}
      else if(nziCDaVaxT == ayNPhpyZNJ){tCQblbcZlI = true;}
      if(HrPGNEsLwJ == wWMACXrLtg){AjSRMnlyGt = true;}
      else if(wWMACXrLtg == HrPGNEsLwJ){cTjNWGfqSn = true;}
      if(UBaSNBWXtI == YVoEiiCybG){GgHtFdzzyD = true;}
      else if(YVoEiiCybG == UBaSNBWXtI){xeCWwRbSRA = true;}
      if(fSUpNahWwT == iHCmMdLfQj){tEuHnFDwiZ = true;}
      else if(iHCmMdLfQj == fSUpNahWwT){oekEaNnonK = true;}
      if(niZZjMYboZ == ZnEPrgaTNb){uRdfsiOtiW = true;}
      else if(ZnEPrgaTNb == niZZjMYboZ){YYYAdqizZH = true;}
      if(yjDSGYWuCf == VqZPVSJeTU){QrGjxgtkil = true;}
      else if(VqZPVSJeTU == yjDSGYWuCf){SIFBzOzsfT = true;}
      if(SafEcnXYsl == XWyqknTYnY){LwRFpwoLdG = true;}
      else if(XWyqknTYnY == SafEcnXYsl){AKHkSyielJ = true;}
      if(VWOcUlbAiB == LLuKGkRYLB){koOfyoDaBV = true;}
      if(cuhTKuOBjo == HikzjqhmRt){PEQalCyKJH = true;}
      if(DmTQANDUxu == TgMuLDpMdE){KSNwOyzYow = true;}
      while(LLuKGkRYLB == VWOcUlbAiB){SpCHOYGBsE = true;}
      while(HikzjqhmRt == HikzjqhmRt){ibsJgfYjEM = true;}
      while(TgMuLDpMdE == TgMuLDpMdE){NtJTKOQmge = true;}
      if(NCenQKwPIk == true){NCenQKwPIk = false;}
      if(AjSRMnlyGt == true){AjSRMnlyGt = false;}
      if(GgHtFdzzyD == true){GgHtFdzzyD = false;}
      if(tEuHnFDwiZ == true){tEuHnFDwiZ = false;}
      if(uRdfsiOtiW == true){uRdfsiOtiW = false;}
      if(QrGjxgtkil == true){QrGjxgtkil = false;}
      if(LwRFpwoLdG == true){LwRFpwoLdG = false;}
      if(koOfyoDaBV == true){koOfyoDaBV = false;}
      if(PEQalCyKJH == true){PEQalCyKJH = false;}
      if(KSNwOyzYow == true){KSNwOyzYow = false;}
      if(tCQblbcZlI == true){tCQblbcZlI = false;}
      if(cTjNWGfqSn == true){cTjNWGfqSn = false;}
      if(xeCWwRbSRA == true){xeCWwRbSRA = false;}
      if(oekEaNnonK == true){oekEaNnonK = false;}
      if(YYYAdqizZH == true){YYYAdqizZH = false;}
      if(SIFBzOzsfT == true){SIFBzOzsfT = false;}
      if(AKHkSyielJ == true){AKHkSyielJ = false;}
      if(SpCHOYGBsE == true){SpCHOYGBsE = false;}
      if(ibsJgfYjEM == true){ibsJgfYjEM = false;}
      if(NtJTKOQmge == true){NtJTKOQmge = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJIVNTZHTG
{ 
  void IoplpBwmcS()
  { 
      bool aCiOkNPAHE = false;
      bool BSGkJIuusX = false;
      bool WUWgqRkAlt = false;
      bool zEROBrrtuF = false;
      bool zThBbwkWJN = false;
      bool QzgPCFeCWS = false;
      bool bOOMEwAriR = false;
      bool PBzmXCmUEt = false;
      bool fNpXcAXCLw = false;
      bool MpWbcjFUxf = false;
      bool urmrxPAsqz = false;
      bool SJxbmNXpjE = false;
      bool YygmEZdWKm = false;
      bool xRXYynayaN = false;
      bool zdKLdCrtoO = false;
      bool LOksHxKznX = false;
      bool kdiECAlYcy = false;
      bool mZPWEtnVJB = false;
      bool gjguaigdRB = false;
      bool caKDbVuGJd = false;
      string KHePuYzNQB;
      string irfBTGRGwf;
      string yqBapDllTt;
      string dsEgHGRkKd;
      string jVrJFjGwnR;
      string keUhQTGDYr;
      string lMsWWpmytN;
      string nfwRwcyqUF;
      string woxBJzYWQm;
      string ANLRqWbUlP;
      string wHCadEhCkn;
      string UOhSwxPrMX;
      string QQhGNZTdaZ;
      string AcEFJomVXF;
      string QWkbRkesVt;
      string GjIOyfYuND;
      string jEbLnrKcJG;
      string JsTHHteGnb;
      string taIfSPUoGc;
      string PrITVMtZnZ;
      if(KHePuYzNQB == wHCadEhCkn){aCiOkNPAHE = true;}
      else if(wHCadEhCkn == KHePuYzNQB){urmrxPAsqz = true;}
      if(irfBTGRGwf == UOhSwxPrMX){BSGkJIuusX = true;}
      else if(UOhSwxPrMX == irfBTGRGwf){SJxbmNXpjE = true;}
      if(yqBapDllTt == QQhGNZTdaZ){WUWgqRkAlt = true;}
      else if(QQhGNZTdaZ == yqBapDllTt){YygmEZdWKm = true;}
      if(dsEgHGRkKd == AcEFJomVXF){zEROBrrtuF = true;}
      else if(AcEFJomVXF == dsEgHGRkKd){xRXYynayaN = true;}
      if(jVrJFjGwnR == QWkbRkesVt){zThBbwkWJN = true;}
      else if(QWkbRkesVt == jVrJFjGwnR){zdKLdCrtoO = true;}
      if(keUhQTGDYr == GjIOyfYuND){QzgPCFeCWS = true;}
      else if(GjIOyfYuND == keUhQTGDYr){LOksHxKznX = true;}
      if(lMsWWpmytN == jEbLnrKcJG){bOOMEwAriR = true;}
      else if(jEbLnrKcJG == lMsWWpmytN){kdiECAlYcy = true;}
      if(nfwRwcyqUF == JsTHHteGnb){PBzmXCmUEt = true;}
      if(woxBJzYWQm == taIfSPUoGc){fNpXcAXCLw = true;}
      if(ANLRqWbUlP == PrITVMtZnZ){MpWbcjFUxf = true;}
      while(JsTHHteGnb == nfwRwcyqUF){mZPWEtnVJB = true;}
      while(taIfSPUoGc == taIfSPUoGc){gjguaigdRB = true;}
      while(PrITVMtZnZ == PrITVMtZnZ){caKDbVuGJd = true;}
      if(aCiOkNPAHE == true){aCiOkNPAHE = false;}
      if(BSGkJIuusX == true){BSGkJIuusX = false;}
      if(WUWgqRkAlt == true){WUWgqRkAlt = false;}
      if(zEROBrrtuF == true){zEROBrrtuF = false;}
      if(zThBbwkWJN == true){zThBbwkWJN = false;}
      if(QzgPCFeCWS == true){QzgPCFeCWS = false;}
      if(bOOMEwAriR == true){bOOMEwAriR = false;}
      if(PBzmXCmUEt == true){PBzmXCmUEt = false;}
      if(fNpXcAXCLw == true){fNpXcAXCLw = false;}
      if(MpWbcjFUxf == true){MpWbcjFUxf = false;}
      if(urmrxPAsqz == true){urmrxPAsqz = false;}
      if(SJxbmNXpjE == true){SJxbmNXpjE = false;}
      if(YygmEZdWKm == true){YygmEZdWKm = false;}
      if(xRXYynayaN == true){xRXYynayaN = false;}
      if(zdKLdCrtoO == true){zdKLdCrtoO = false;}
      if(LOksHxKznX == true){LOksHxKznX = false;}
      if(kdiECAlYcy == true){kdiECAlYcy = false;}
      if(mZPWEtnVJB == true){mZPWEtnVJB = false;}
      if(gjguaigdRB == true){gjguaigdRB = false;}
      if(caKDbVuGJd == true){caKDbVuGJd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTEOLWETCF
{ 
  void XthpmllYFu()
  { 
      bool qYDfNmUMcF = false;
      bool kcNcpXwAgM = false;
      bool tNZcDHhMsU = false;
      bool nhJjBgtmbf = false;
      bool RxjSQtUqLk = false;
      bool yNMVKdyabG = false;
      bool FISHRCTcaJ = false;
      bool dIXAuxdGLJ = false;
      bool mpAIWaVmZX = false;
      bool hSKUaJdbBN = false;
      bool ZqQBGpoLaN = false;
      bool zrOSTOHKkp = false;
      bool ggDDaLxCZl = false;
      bool SBFxiwZyBg = false;
      bool kJLLXpDrBL = false;
      bool BSqKgsmMau = false;
      bool rmlouylQiX = false;
      bool oIJDFWUrej = false;
      bool HFBNjzJtQp = false;
      bool IMXFnxXVQZ = false;
      string oVaDFzlQDP;
      string wtEgOHWdWC;
      string ulQCMBhRen;
      string pAPgrEaQdx;
      string GfNrINQrrG;
      string GpLIhDFXpE;
      string RUkOZudWoK;
      string fFAZwPXYsy;
      string kpZYgzoHzo;
      string yCZZekuySN;
      string jsDhZBpkLS;
      string egerSbtMhZ;
      string FWXzLdeatK;
      string TZFfOrlqye;
      string JEugJRXhGD;
      string phPsHMUDWw;
      string VPqByEayda;
      string oDNCPBbqps;
      string FxTpTlKMYB;
      string WhUBJtNshF;
      if(oVaDFzlQDP == jsDhZBpkLS){qYDfNmUMcF = true;}
      else if(jsDhZBpkLS == oVaDFzlQDP){ZqQBGpoLaN = true;}
      if(wtEgOHWdWC == egerSbtMhZ){kcNcpXwAgM = true;}
      else if(egerSbtMhZ == wtEgOHWdWC){zrOSTOHKkp = true;}
      if(ulQCMBhRen == FWXzLdeatK){tNZcDHhMsU = true;}
      else if(FWXzLdeatK == ulQCMBhRen){ggDDaLxCZl = true;}
      if(pAPgrEaQdx == TZFfOrlqye){nhJjBgtmbf = true;}
      else if(TZFfOrlqye == pAPgrEaQdx){SBFxiwZyBg = true;}
      if(GfNrINQrrG == JEugJRXhGD){RxjSQtUqLk = true;}
      else if(JEugJRXhGD == GfNrINQrrG){kJLLXpDrBL = true;}
      if(GpLIhDFXpE == phPsHMUDWw){yNMVKdyabG = true;}
      else if(phPsHMUDWw == GpLIhDFXpE){BSqKgsmMau = true;}
      if(RUkOZudWoK == VPqByEayda){FISHRCTcaJ = true;}
      else if(VPqByEayda == RUkOZudWoK){rmlouylQiX = true;}
      if(fFAZwPXYsy == oDNCPBbqps){dIXAuxdGLJ = true;}
      if(kpZYgzoHzo == FxTpTlKMYB){mpAIWaVmZX = true;}
      if(yCZZekuySN == WhUBJtNshF){hSKUaJdbBN = true;}
      while(oDNCPBbqps == fFAZwPXYsy){oIJDFWUrej = true;}
      while(FxTpTlKMYB == FxTpTlKMYB){HFBNjzJtQp = true;}
      while(WhUBJtNshF == WhUBJtNshF){IMXFnxXVQZ = true;}
      if(qYDfNmUMcF == true){qYDfNmUMcF = false;}
      if(kcNcpXwAgM == true){kcNcpXwAgM = false;}
      if(tNZcDHhMsU == true){tNZcDHhMsU = false;}
      if(nhJjBgtmbf == true){nhJjBgtmbf = false;}
      if(RxjSQtUqLk == true){RxjSQtUqLk = false;}
      if(yNMVKdyabG == true){yNMVKdyabG = false;}
      if(FISHRCTcaJ == true){FISHRCTcaJ = false;}
      if(dIXAuxdGLJ == true){dIXAuxdGLJ = false;}
      if(mpAIWaVmZX == true){mpAIWaVmZX = false;}
      if(hSKUaJdbBN == true){hSKUaJdbBN = false;}
      if(ZqQBGpoLaN == true){ZqQBGpoLaN = false;}
      if(zrOSTOHKkp == true){zrOSTOHKkp = false;}
      if(ggDDaLxCZl == true){ggDDaLxCZl = false;}
      if(SBFxiwZyBg == true){SBFxiwZyBg = false;}
      if(kJLLXpDrBL == true){kJLLXpDrBL = false;}
      if(BSqKgsmMau == true){BSqKgsmMau = false;}
      if(rmlouylQiX == true){rmlouylQiX = false;}
      if(oIJDFWUrej == true){oIJDFWUrej = false;}
      if(HFBNjzJtQp == true){HFBNjzJtQp = false;}
      if(IMXFnxXVQZ == true){IMXFnxXVQZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FOVRYUADXY
{ 
  void aUPaIWAfXU()
  { 
      bool gnHIoLWdoD = false;
      bool UAWebtlhLR = false;
      bool aBVXudxKVY = false;
      bool bkXfTTTLHz = false;
      bool sBtYxXdDOq = false;
      bool wCdOnfRjNL = false;
      bool OMHQaibpKH = false;
      bool aaaLXYHxaW = false;
      bool ztudbZGIrn = false;
      bool BiyukgtcxN = false;
      bool unrGQUaRpO = false;
      bool XUJpMUQcnB = false;
      bool bTyWGqceaq = false;
      bool edAMaLBoNG = false;
      bool zoRcQgZHiQ = false;
      bool PQowkboVAZ = false;
      bool rwqzisUwPA = false;
      bool SbPgCmBUFZ = false;
      bool RUuKaOoDby = false;
      bool VfnmNCySsW = false;
      string nDxoRCZwwP;
      string eNxAZlSoCh;
      string UuNSsXAPOZ;
      string WqsunYKtST;
      string tgZmgAYxBI;
      string UaeKKspdut;
      string BJhVsnTCMB;
      string bYVimnUZls;
      string yDOGEuLijt;
      string hfzYRkzDtr;
      string fVjzfwEwXV;
      string XQrBwxtaQx;
      string bkRRSwYxQB;
      string nRfsMbSOZI;
      string pPKOVRmxcT;
      string qXlwQuDSfj;
      string WHeVhGkzoT;
      string deAIHMZDuB;
      string IbUxKQeicR;
      string XAhplijofP;
      if(nDxoRCZwwP == fVjzfwEwXV){gnHIoLWdoD = true;}
      else if(fVjzfwEwXV == nDxoRCZwwP){unrGQUaRpO = true;}
      if(eNxAZlSoCh == XQrBwxtaQx){UAWebtlhLR = true;}
      else if(XQrBwxtaQx == eNxAZlSoCh){XUJpMUQcnB = true;}
      if(UuNSsXAPOZ == bkRRSwYxQB){aBVXudxKVY = true;}
      else if(bkRRSwYxQB == UuNSsXAPOZ){bTyWGqceaq = true;}
      if(WqsunYKtST == nRfsMbSOZI){bkXfTTTLHz = true;}
      else if(nRfsMbSOZI == WqsunYKtST){edAMaLBoNG = true;}
      if(tgZmgAYxBI == pPKOVRmxcT){sBtYxXdDOq = true;}
      else if(pPKOVRmxcT == tgZmgAYxBI){zoRcQgZHiQ = true;}
      if(UaeKKspdut == qXlwQuDSfj){wCdOnfRjNL = true;}
      else if(qXlwQuDSfj == UaeKKspdut){PQowkboVAZ = true;}
      if(BJhVsnTCMB == WHeVhGkzoT){OMHQaibpKH = true;}
      else if(WHeVhGkzoT == BJhVsnTCMB){rwqzisUwPA = true;}
      if(bYVimnUZls == deAIHMZDuB){aaaLXYHxaW = true;}
      if(yDOGEuLijt == IbUxKQeicR){ztudbZGIrn = true;}
      if(hfzYRkzDtr == XAhplijofP){BiyukgtcxN = true;}
      while(deAIHMZDuB == bYVimnUZls){SbPgCmBUFZ = true;}
      while(IbUxKQeicR == IbUxKQeicR){RUuKaOoDby = true;}
      while(XAhplijofP == XAhplijofP){VfnmNCySsW = true;}
      if(gnHIoLWdoD == true){gnHIoLWdoD = false;}
      if(UAWebtlhLR == true){UAWebtlhLR = false;}
      if(aBVXudxKVY == true){aBVXudxKVY = false;}
      if(bkXfTTTLHz == true){bkXfTTTLHz = false;}
      if(sBtYxXdDOq == true){sBtYxXdDOq = false;}
      if(wCdOnfRjNL == true){wCdOnfRjNL = false;}
      if(OMHQaibpKH == true){OMHQaibpKH = false;}
      if(aaaLXYHxaW == true){aaaLXYHxaW = false;}
      if(ztudbZGIrn == true){ztudbZGIrn = false;}
      if(BiyukgtcxN == true){BiyukgtcxN = false;}
      if(unrGQUaRpO == true){unrGQUaRpO = false;}
      if(XUJpMUQcnB == true){XUJpMUQcnB = false;}
      if(bTyWGqceaq == true){bTyWGqceaq = false;}
      if(edAMaLBoNG == true){edAMaLBoNG = false;}
      if(zoRcQgZHiQ == true){zoRcQgZHiQ = false;}
      if(PQowkboVAZ == true){PQowkboVAZ = false;}
      if(rwqzisUwPA == true){rwqzisUwPA = false;}
      if(SbPgCmBUFZ == true){SbPgCmBUFZ = false;}
      if(RUuKaOoDby == true){RUuKaOoDby = false;}
      if(VfnmNCySsW == true){VfnmNCySsW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTBXNRRQIC
{ 
  void QwxhPPkYGC()
  { 
      bool suoEUhbRsf = false;
      bool bxUXcyskQK = false;
      bool cwdgEYlAVa = false;
      bool rPCWuTJKhR = false;
      bool GjzeCrrjOE = false;
      bool TtBMowQHzw = false;
      bool wauRmMuycI = false;
      bool niCyDrxzeM = false;
      bool gBlRHxOogy = false;
      bool DBLlVfogqo = false;
      bool wtHGPkrCJx = false;
      bool zRblOtodKo = false;
      bool yFQdEmWPcW = false;
      bool DQHoPltfBV = false;
      bool ELejzlZYXa = false;
      bool qKVBqqccBc = false;
      bool NcZltiJlVc = false;
      bool AIcnjmageS = false;
      bool NyrBfrtFyY = false;
      bool IReXIbkroP = false;
      string fmfLSDSNRc;
      string HgIQwoYAVT;
      string ywGSqnZDJw;
      string culGGcBWis;
      string DAlpIYOGBg;
      string zmbJtifNTe;
      string cOEVzMuCJT;
      string nCRbQyKQKS;
      string YTBcwpTcMW;
      string xmCEQnuQpw;
      string cMwhswUzsw;
      string YODBGJMbYJ;
      string rRpmVAzMKb;
      string CsZNoLWTjz;
      string UTjQxhjByH;
      string bTqgDKWJLr;
      string xHnQseooLt;
      string lsrYnXhYon;
      string PyODAiCrKd;
      string oMHqCMfSWS;
      if(fmfLSDSNRc == cMwhswUzsw){suoEUhbRsf = true;}
      else if(cMwhswUzsw == fmfLSDSNRc){wtHGPkrCJx = true;}
      if(HgIQwoYAVT == YODBGJMbYJ){bxUXcyskQK = true;}
      else if(YODBGJMbYJ == HgIQwoYAVT){zRblOtodKo = true;}
      if(ywGSqnZDJw == rRpmVAzMKb){cwdgEYlAVa = true;}
      else if(rRpmVAzMKb == ywGSqnZDJw){yFQdEmWPcW = true;}
      if(culGGcBWis == CsZNoLWTjz){rPCWuTJKhR = true;}
      else if(CsZNoLWTjz == culGGcBWis){DQHoPltfBV = true;}
      if(DAlpIYOGBg == UTjQxhjByH){GjzeCrrjOE = true;}
      else if(UTjQxhjByH == DAlpIYOGBg){ELejzlZYXa = true;}
      if(zmbJtifNTe == bTqgDKWJLr){TtBMowQHzw = true;}
      else if(bTqgDKWJLr == zmbJtifNTe){qKVBqqccBc = true;}
      if(cOEVzMuCJT == xHnQseooLt){wauRmMuycI = true;}
      else if(xHnQseooLt == cOEVzMuCJT){NcZltiJlVc = true;}
      if(nCRbQyKQKS == lsrYnXhYon){niCyDrxzeM = true;}
      if(YTBcwpTcMW == PyODAiCrKd){gBlRHxOogy = true;}
      if(xmCEQnuQpw == oMHqCMfSWS){DBLlVfogqo = true;}
      while(lsrYnXhYon == nCRbQyKQKS){AIcnjmageS = true;}
      while(PyODAiCrKd == PyODAiCrKd){NyrBfrtFyY = true;}
      while(oMHqCMfSWS == oMHqCMfSWS){IReXIbkroP = true;}
      if(suoEUhbRsf == true){suoEUhbRsf = false;}
      if(bxUXcyskQK == true){bxUXcyskQK = false;}
      if(cwdgEYlAVa == true){cwdgEYlAVa = false;}
      if(rPCWuTJKhR == true){rPCWuTJKhR = false;}
      if(GjzeCrrjOE == true){GjzeCrrjOE = false;}
      if(TtBMowQHzw == true){TtBMowQHzw = false;}
      if(wauRmMuycI == true){wauRmMuycI = false;}
      if(niCyDrxzeM == true){niCyDrxzeM = false;}
      if(gBlRHxOogy == true){gBlRHxOogy = false;}
      if(DBLlVfogqo == true){DBLlVfogqo = false;}
      if(wtHGPkrCJx == true){wtHGPkrCJx = false;}
      if(zRblOtodKo == true){zRblOtodKo = false;}
      if(yFQdEmWPcW == true){yFQdEmWPcW = false;}
      if(DQHoPltfBV == true){DQHoPltfBV = false;}
      if(ELejzlZYXa == true){ELejzlZYXa = false;}
      if(qKVBqqccBc == true){qKVBqqccBc = false;}
      if(NcZltiJlVc == true){NcZltiJlVc = false;}
      if(AIcnjmageS == true){AIcnjmageS = false;}
      if(NyrBfrtFyY == true){NyrBfrtFyY = false;}
      if(IReXIbkroP == true){IReXIbkroP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYBUADLOBM
{ 
  void IQAKdgrtTo()
  { 
      bool GnYuqEIQlS = false;
      bool uNXWMEKsTj = false;
      bool mWAxDpzyQA = false;
      bool nmHeXJIjsQ = false;
      bool kGJiVEEzZT = false;
      bool ZbWZUimarA = false;
      bool FJAkdIFrzD = false;
      bool uZzCzgNRby = false;
      bool kAYwZLPgKo = false;
      bool WgqrLaGXEN = false;
      bool yLAWXAbUan = false;
      bool UVztOEkDKR = false;
      bool rYhJfNhGpX = false;
      bool aoMOzZzCYZ = false;
      bool iuGVTBhxcG = false;
      bool pCNlUZcppJ = false;
      bool RVdCNeIjto = false;
      bool FiekhwRLpe = false;
      bool fkcihXbZtY = false;
      bool wILOINREIn = false;
      string cHZfxQNnOR;
      string lFxzQezjwF;
      string YFQdunxsIw;
      string oGYkgCSfyj;
      string nIXMPRAmSL;
      string bZjEfWpukJ;
      string STfSbefMRO;
      string LSlMRPhEOd;
      string mKaxTOWTFJ;
      string LXunRTcEkj;
      string lnUDzJnXmQ;
      string olgGVHsizM;
      string ILGIDnWxtx;
      string mcTdqzoWxK;
      string aygnUYpoRJ;
      string asFXbZgMAK;
      string lpdpdLSCPV;
      string SVknlJdSnd;
      string xhfjVsXuBR;
      string ScVmXkUqKI;
      if(cHZfxQNnOR == lnUDzJnXmQ){GnYuqEIQlS = true;}
      else if(lnUDzJnXmQ == cHZfxQNnOR){yLAWXAbUan = true;}
      if(lFxzQezjwF == olgGVHsizM){uNXWMEKsTj = true;}
      else if(olgGVHsizM == lFxzQezjwF){UVztOEkDKR = true;}
      if(YFQdunxsIw == ILGIDnWxtx){mWAxDpzyQA = true;}
      else if(ILGIDnWxtx == YFQdunxsIw){rYhJfNhGpX = true;}
      if(oGYkgCSfyj == mcTdqzoWxK){nmHeXJIjsQ = true;}
      else if(mcTdqzoWxK == oGYkgCSfyj){aoMOzZzCYZ = true;}
      if(nIXMPRAmSL == aygnUYpoRJ){kGJiVEEzZT = true;}
      else if(aygnUYpoRJ == nIXMPRAmSL){iuGVTBhxcG = true;}
      if(bZjEfWpukJ == asFXbZgMAK){ZbWZUimarA = true;}
      else if(asFXbZgMAK == bZjEfWpukJ){pCNlUZcppJ = true;}
      if(STfSbefMRO == lpdpdLSCPV){FJAkdIFrzD = true;}
      else if(lpdpdLSCPV == STfSbefMRO){RVdCNeIjto = true;}
      if(LSlMRPhEOd == SVknlJdSnd){uZzCzgNRby = true;}
      if(mKaxTOWTFJ == xhfjVsXuBR){kAYwZLPgKo = true;}
      if(LXunRTcEkj == ScVmXkUqKI){WgqrLaGXEN = true;}
      while(SVknlJdSnd == LSlMRPhEOd){FiekhwRLpe = true;}
      while(xhfjVsXuBR == xhfjVsXuBR){fkcihXbZtY = true;}
      while(ScVmXkUqKI == ScVmXkUqKI){wILOINREIn = true;}
      if(GnYuqEIQlS == true){GnYuqEIQlS = false;}
      if(uNXWMEKsTj == true){uNXWMEKsTj = false;}
      if(mWAxDpzyQA == true){mWAxDpzyQA = false;}
      if(nmHeXJIjsQ == true){nmHeXJIjsQ = false;}
      if(kGJiVEEzZT == true){kGJiVEEzZT = false;}
      if(ZbWZUimarA == true){ZbWZUimarA = false;}
      if(FJAkdIFrzD == true){FJAkdIFrzD = false;}
      if(uZzCzgNRby == true){uZzCzgNRby = false;}
      if(kAYwZLPgKo == true){kAYwZLPgKo = false;}
      if(WgqrLaGXEN == true){WgqrLaGXEN = false;}
      if(yLAWXAbUan == true){yLAWXAbUan = false;}
      if(UVztOEkDKR == true){UVztOEkDKR = false;}
      if(rYhJfNhGpX == true){rYhJfNhGpX = false;}
      if(aoMOzZzCYZ == true){aoMOzZzCYZ = false;}
      if(iuGVTBhxcG == true){iuGVTBhxcG = false;}
      if(pCNlUZcppJ == true){pCNlUZcppJ = false;}
      if(RVdCNeIjto == true){RVdCNeIjto = false;}
      if(FiekhwRLpe == true){FiekhwRLpe = false;}
      if(fkcihXbZtY == true){fkcihXbZtY = false;}
      if(wILOINREIn == true){wILOINREIn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBIGNVGWNK
{ 
  void CwMWgCVFAY()
  { 
      bool LXXOaWmIDw = false;
      bool ZMfoQQglMT = false;
      bool huRNlxszAZ = false;
      bool XrdjOTfzzb = false;
      bool sFHheLySwB = false;
      bool iyUrYQGKcc = false;
      bool cmHdXgiwZw = false;
      bool jgmkZcniiZ = false;
      bool zaDyqZXkLy = false;
      bool NVWVyGxdKx = false;
      bool cCrzQBLiRw = false;
      bool bWaCdCjJly = false;
      bool IxkaiOJQlT = false;
      bool eJYkxxhEho = false;
      bool NnTPVptUru = false;
      bool VnqLofRRPB = false;
      bool qtwyQSypEf = false;
      bool UfaxjTdUEs = false;
      bool UoYqxqSMuR = false;
      bool fQnfxTqUyD = false;
      string FYlbhFVuYk;
      string qPbUYpNWmQ;
      string SCGIgVKQWU;
      string isXjoydGXa;
      string AFiAKKstjg;
      string UkDysDSdtM;
      string tEXECxrqeZ;
      string LGzLQMSFxW;
      string bQgpAypZql;
      string fAMKgugeyN;
      string SBPJUNkqgf;
      string jNfWkdXhED;
      string HSArsLsodV;
      string fnGjEZBWVl;
      string MyrLCSTpZD;
      string WzauFzBWPI;
      string TwNKAuGwSK;
      string bAMRqJZopa;
      string rDOayfNLdE;
      string YdHMRQkgLG;
      if(FYlbhFVuYk == SBPJUNkqgf){LXXOaWmIDw = true;}
      else if(SBPJUNkqgf == FYlbhFVuYk){cCrzQBLiRw = true;}
      if(qPbUYpNWmQ == jNfWkdXhED){ZMfoQQglMT = true;}
      else if(jNfWkdXhED == qPbUYpNWmQ){bWaCdCjJly = true;}
      if(SCGIgVKQWU == HSArsLsodV){huRNlxszAZ = true;}
      else if(HSArsLsodV == SCGIgVKQWU){IxkaiOJQlT = true;}
      if(isXjoydGXa == fnGjEZBWVl){XrdjOTfzzb = true;}
      else if(fnGjEZBWVl == isXjoydGXa){eJYkxxhEho = true;}
      if(AFiAKKstjg == MyrLCSTpZD){sFHheLySwB = true;}
      else if(MyrLCSTpZD == AFiAKKstjg){NnTPVptUru = true;}
      if(UkDysDSdtM == WzauFzBWPI){iyUrYQGKcc = true;}
      else if(WzauFzBWPI == UkDysDSdtM){VnqLofRRPB = true;}
      if(tEXECxrqeZ == TwNKAuGwSK){cmHdXgiwZw = true;}
      else if(TwNKAuGwSK == tEXECxrqeZ){qtwyQSypEf = true;}
      if(LGzLQMSFxW == bAMRqJZopa){jgmkZcniiZ = true;}
      if(bQgpAypZql == rDOayfNLdE){zaDyqZXkLy = true;}
      if(fAMKgugeyN == YdHMRQkgLG){NVWVyGxdKx = true;}
      while(bAMRqJZopa == LGzLQMSFxW){UfaxjTdUEs = true;}
      while(rDOayfNLdE == rDOayfNLdE){UoYqxqSMuR = true;}
      while(YdHMRQkgLG == YdHMRQkgLG){fQnfxTqUyD = true;}
      if(LXXOaWmIDw == true){LXXOaWmIDw = false;}
      if(ZMfoQQglMT == true){ZMfoQQglMT = false;}
      if(huRNlxszAZ == true){huRNlxszAZ = false;}
      if(XrdjOTfzzb == true){XrdjOTfzzb = false;}
      if(sFHheLySwB == true){sFHheLySwB = false;}
      if(iyUrYQGKcc == true){iyUrYQGKcc = false;}
      if(cmHdXgiwZw == true){cmHdXgiwZw = false;}
      if(jgmkZcniiZ == true){jgmkZcniiZ = false;}
      if(zaDyqZXkLy == true){zaDyqZXkLy = false;}
      if(NVWVyGxdKx == true){NVWVyGxdKx = false;}
      if(cCrzQBLiRw == true){cCrzQBLiRw = false;}
      if(bWaCdCjJly == true){bWaCdCjJly = false;}
      if(IxkaiOJQlT == true){IxkaiOJQlT = false;}
      if(eJYkxxhEho == true){eJYkxxhEho = false;}
      if(NnTPVptUru == true){NnTPVptUru = false;}
      if(VnqLofRRPB == true){VnqLofRRPB = false;}
      if(qtwyQSypEf == true){qtwyQSypEf = false;}
      if(UfaxjTdUEs == true){UfaxjTdUEs = false;}
      if(UoYqxqSMuR == true){UoYqxqSMuR = false;}
      if(fQnfxTqUyD == true){fQnfxTqUyD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBZPZTUKCI
{ 
  void HKxRedfsso()
  { 
      bool ePhslJyrYq = false;
      bool prjMJkzXei = false;
      bool MHizMKykcc = false;
      bool LKFRVatXHu = false;
      bool quRESNYNoW = false;
      bool RaTBIXghgb = false;
      bool KMPwfflRqi = false;
      bool qbQjrRoegy = false;
      bool lkwGLjqEJx = false;
      bool sLqfjdfVXm = false;
      bool aGWGeoKjIp = false;
      bool iCBhpZQIkw = false;
      bool nhHsoejjAO = false;
      bool lSGtXeOoaV = false;
      bool YGwSNpKJpJ = false;
      bool NWkbyszcQA = false;
      bool EZjtEQwHJK = false;
      bool LahOWhlnfy = false;
      bool UatpBPhdwd = false;
      bool fkYaQyWBOx = false;
      string WSfLwElARa;
      string bMxJQkAAXb;
      string czFZrOrqfH;
      string VLOqLzcZCR;
      string qmuAwqoeKt;
      string FrZIlWMFSh;
      string MtUJFPyFyQ;
      string IZyFjpDEdB;
      string YMgkCclGFo;
      string lWHUFwRluf;
      string rigslftTXw;
      string SIbRIzNiHb;
      string drAJekRcAn;
      string XRJxIofnzV;
      string hShJVdtpLF;
      string ihdSCAiWNA;
      string NQSjYAydIS;
      string TYjksKJpmB;
      string qbQtEonquI;
      string GIZyIQzyjU;
      if(WSfLwElARa == rigslftTXw){ePhslJyrYq = true;}
      else if(rigslftTXw == WSfLwElARa){aGWGeoKjIp = true;}
      if(bMxJQkAAXb == SIbRIzNiHb){prjMJkzXei = true;}
      else if(SIbRIzNiHb == bMxJQkAAXb){iCBhpZQIkw = true;}
      if(czFZrOrqfH == drAJekRcAn){MHizMKykcc = true;}
      else if(drAJekRcAn == czFZrOrqfH){nhHsoejjAO = true;}
      if(VLOqLzcZCR == XRJxIofnzV){LKFRVatXHu = true;}
      else if(XRJxIofnzV == VLOqLzcZCR){lSGtXeOoaV = true;}
      if(qmuAwqoeKt == hShJVdtpLF){quRESNYNoW = true;}
      else if(hShJVdtpLF == qmuAwqoeKt){YGwSNpKJpJ = true;}
      if(FrZIlWMFSh == ihdSCAiWNA){RaTBIXghgb = true;}
      else if(ihdSCAiWNA == FrZIlWMFSh){NWkbyszcQA = true;}
      if(MtUJFPyFyQ == NQSjYAydIS){KMPwfflRqi = true;}
      else if(NQSjYAydIS == MtUJFPyFyQ){EZjtEQwHJK = true;}
      if(IZyFjpDEdB == TYjksKJpmB){qbQjrRoegy = true;}
      if(YMgkCclGFo == qbQtEonquI){lkwGLjqEJx = true;}
      if(lWHUFwRluf == GIZyIQzyjU){sLqfjdfVXm = true;}
      while(TYjksKJpmB == IZyFjpDEdB){LahOWhlnfy = true;}
      while(qbQtEonquI == qbQtEonquI){UatpBPhdwd = true;}
      while(GIZyIQzyjU == GIZyIQzyjU){fkYaQyWBOx = true;}
      if(ePhslJyrYq == true){ePhslJyrYq = false;}
      if(prjMJkzXei == true){prjMJkzXei = false;}
      if(MHizMKykcc == true){MHizMKykcc = false;}
      if(LKFRVatXHu == true){LKFRVatXHu = false;}
      if(quRESNYNoW == true){quRESNYNoW = false;}
      if(RaTBIXghgb == true){RaTBIXghgb = false;}
      if(KMPwfflRqi == true){KMPwfflRqi = false;}
      if(qbQjrRoegy == true){qbQjrRoegy = false;}
      if(lkwGLjqEJx == true){lkwGLjqEJx = false;}
      if(sLqfjdfVXm == true){sLqfjdfVXm = false;}
      if(aGWGeoKjIp == true){aGWGeoKjIp = false;}
      if(iCBhpZQIkw == true){iCBhpZQIkw = false;}
      if(nhHsoejjAO == true){nhHsoejjAO = false;}
      if(lSGtXeOoaV == true){lSGtXeOoaV = false;}
      if(YGwSNpKJpJ == true){YGwSNpKJpJ = false;}
      if(NWkbyszcQA == true){NWkbyszcQA = false;}
      if(EZjtEQwHJK == true){EZjtEQwHJK = false;}
      if(LahOWhlnfy == true){LahOWhlnfy = false;}
      if(UatpBPhdwd == true){UatpBPhdwd = false;}
      if(fkYaQyWBOx == true){fkYaQyWBOx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BELTEFLATI
{ 
  void UgeouFAfHa()
  { 
      bool YJQzYwhVUE = false;
      bool YssZFhCyBn = false;
      bool lozGlhgXqM = false;
      bool NcFGFSlVuh = false;
      bool LbSTEPElGJ = false;
      bool PMzfJjJJMq = false;
      bool OKeIpwmmTm = false;
      bool wgDSbJVfCV = false;
      bool cuQgwAcYwV = false;
      bool IbIDSAxKcH = false;
      bool bQRTNiJgDz = false;
      bool NdHpOTsxLp = false;
      bool TOpxdTXzAb = false;
      bool MKCttLcxTM = false;
      bool puUxIeUSoz = false;
      bool HzzmnNaTot = false;
      bool LKgbmCaMwC = false;
      bool pucyzXssoz = false;
      bool yFJAUMLPGf = false;
      bool kJIZBfOsJF = false;
      string YNGQprCSOC;
      string BAcUuiCwil;
      string bSkwDtwnzg;
      string AXGCWuReOc;
      string PRyZLIVZkK;
      string MVzXFFcJMw;
      string wNTgCcsZxz;
      string RWhGWKTLju;
      string XVCnTeYixQ;
      string SHSSfByRXi;
      string OwbkspmsBt;
      string lQZQXaKeMW;
      string EKcfgKEPZU;
      string MCnBgbtQud;
      string qegCeBhBtF;
      string pSEAdDSuEh;
      string lXSfhjcXju;
      string fsjifZdZBe;
      string cDUUetxnXd;
      string IyLMrSLBUu;
      if(YNGQprCSOC == OwbkspmsBt){YJQzYwhVUE = true;}
      else if(OwbkspmsBt == YNGQprCSOC){bQRTNiJgDz = true;}
      if(BAcUuiCwil == lQZQXaKeMW){YssZFhCyBn = true;}
      else if(lQZQXaKeMW == BAcUuiCwil){NdHpOTsxLp = true;}
      if(bSkwDtwnzg == EKcfgKEPZU){lozGlhgXqM = true;}
      else if(EKcfgKEPZU == bSkwDtwnzg){TOpxdTXzAb = true;}
      if(AXGCWuReOc == MCnBgbtQud){NcFGFSlVuh = true;}
      else if(MCnBgbtQud == AXGCWuReOc){MKCttLcxTM = true;}
      if(PRyZLIVZkK == qegCeBhBtF){LbSTEPElGJ = true;}
      else if(qegCeBhBtF == PRyZLIVZkK){puUxIeUSoz = true;}
      if(MVzXFFcJMw == pSEAdDSuEh){PMzfJjJJMq = true;}
      else if(pSEAdDSuEh == MVzXFFcJMw){HzzmnNaTot = true;}
      if(wNTgCcsZxz == lXSfhjcXju){OKeIpwmmTm = true;}
      else if(lXSfhjcXju == wNTgCcsZxz){LKgbmCaMwC = true;}
      if(RWhGWKTLju == fsjifZdZBe){wgDSbJVfCV = true;}
      if(XVCnTeYixQ == cDUUetxnXd){cuQgwAcYwV = true;}
      if(SHSSfByRXi == IyLMrSLBUu){IbIDSAxKcH = true;}
      while(fsjifZdZBe == RWhGWKTLju){pucyzXssoz = true;}
      while(cDUUetxnXd == cDUUetxnXd){yFJAUMLPGf = true;}
      while(IyLMrSLBUu == IyLMrSLBUu){kJIZBfOsJF = true;}
      if(YJQzYwhVUE == true){YJQzYwhVUE = false;}
      if(YssZFhCyBn == true){YssZFhCyBn = false;}
      if(lozGlhgXqM == true){lozGlhgXqM = false;}
      if(NcFGFSlVuh == true){NcFGFSlVuh = false;}
      if(LbSTEPElGJ == true){LbSTEPElGJ = false;}
      if(PMzfJjJJMq == true){PMzfJjJJMq = false;}
      if(OKeIpwmmTm == true){OKeIpwmmTm = false;}
      if(wgDSbJVfCV == true){wgDSbJVfCV = false;}
      if(cuQgwAcYwV == true){cuQgwAcYwV = false;}
      if(IbIDSAxKcH == true){IbIDSAxKcH = false;}
      if(bQRTNiJgDz == true){bQRTNiJgDz = false;}
      if(NdHpOTsxLp == true){NdHpOTsxLp = false;}
      if(TOpxdTXzAb == true){TOpxdTXzAb = false;}
      if(MKCttLcxTM == true){MKCttLcxTM = false;}
      if(puUxIeUSoz == true){puUxIeUSoz = false;}
      if(HzzmnNaTot == true){HzzmnNaTot = false;}
      if(LKgbmCaMwC == true){LKgbmCaMwC = false;}
      if(pucyzXssoz == true){pucyzXssoz = false;}
      if(yFJAUMLPGf == true){yFJAUMLPGf = false;}
      if(kJIZBfOsJF == true){kJIZBfOsJF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGHQSHVAPD
{ 
  void USEktQNcQf()
  { 
      bool BOubFHTHOp = false;
      bool GWlGTGiIhE = false;
      bool hgIibqXzCp = false;
      bool fgWWuawsgX = false;
      bool eDrSGOmqZC = false;
      bool uttIeUFLAN = false;
      bool iUFYKZAOLs = false;
      bool KoaKZdopcM = false;
      bool EgZzullNqZ = false;
      bool UjsTnJyTIf = false;
      bool OXffrFSihB = false;
      bool fPinJCtGdY = false;
      bool nlXkYZwHVQ = false;
      bool fUgwygAtGo = false;
      bool SCeptEBEJl = false;
      bool PqojrbAuGS = false;
      bool ILNRUKimpc = false;
      bool BAznFkHgpU = false;
      bool YqxjAofxDV = false;
      bool gFmngHoMUj = false;
      string ObZAHKGFkd;
      string dHDxifrNle;
      string OUUhcxrpWZ;
      string ZttTZbapGy;
      string TrAqrftjxl;
      string iYqglsHrXJ;
      string SQhKEjNjWH;
      string FBHnKVUcpw;
      string DHrjpACMgf;
      string UiSwfCKomH;
      string RJMpghQDVP;
      string YdBaGKYxUD;
      string hACqmWiLHI;
      string LfpiestBDI;
      string iypRGpgqoU;
      string dNTiZQHVDJ;
      string yFuNDsnSwN;
      string PWsLTiKkjw;
      string oqVmeyLHJN;
      string kYysJdDcNN;
      if(ObZAHKGFkd == RJMpghQDVP){BOubFHTHOp = true;}
      else if(RJMpghQDVP == ObZAHKGFkd){OXffrFSihB = true;}
      if(dHDxifrNle == YdBaGKYxUD){GWlGTGiIhE = true;}
      else if(YdBaGKYxUD == dHDxifrNle){fPinJCtGdY = true;}
      if(OUUhcxrpWZ == hACqmWiLHI){hgIibqXzCp = true;}
      else if(hACqmWiLHI == OUUhcxrpWZ){nlXkYZwHVQ = true;}
      if(ZttTZbapGy == LfpiestBDI){fgWWuawsgX = true;}
      else if(LfpiestBDI == ZttTZbapGy){fUgwygAtGo = true;}
      if(TrAqrftjxl == iypRGpgqoU){eDrSGOmqZC = true;}
      else if(iypRGpgqoU == TrAqrftjxl){SCeptEBEJl = true;}
      if(iYqglsHrXJ == dNTiZQHVDJ){uttIeUFLAN = true;}
      else if(dNTiZQHVDJ == iYqglsHrXJ){PqojrbAuGS = true;}
      if(SQhKEjNjWH == yFuNDsnSwN){iUFYKZAOLs = true;}
      else if(yFuNDsnSwN == SQhKEjNjWH){ILNRUKimpc = true;}
      if(FBHnKVUcpw == PWsLTiKkjw){KoaKZdopcM = true;}
      if(DHrjpACMgf == oqVmeyLHJN){EgZzullNqZ = true;}
      if(UiSwfCKomH == kYysJdDcNN){UjsTnJyTIf = true;}
      while(PWsLTiKkjw == FBHnKVUcpw){BAznFkHgpU = true;}
      while(oqVmeyLHJN == oqVmeyLHJN){YqxjAofxDV = true;}
      while(kYysJdDcNN == kYysJdDcNN){gFmngHoMUj = true;}
      if(BOubFHTHOp == true){BOubFHTHOp = false;}
      if(GWlGTGiIhE == true){GWlGTGiIhE = false;}
      if(hgIibqXzCp == true){hgIibqXzCp = false;}
      if(fgWWuawsgX == true){fgWWuawsgX = false;}
      if(eDrSGOmqZC == true){eDrSGOmqZC = false;}
      if(uttIeUFLAN == true){uttIeUFLAN = false;}
      if(iUFYKZAOLs == true){iUFYKZAOLs = false;}
      if(KoaKZdopcM == true){KoaKZdopcM = false;}
      if(EgZzullNqZ == true){EgZzullNqZ = false;}
      if(UjsTnJyTIf == true){UjsTnJyTIf = false;}
      if(OXffrFSihB == true){OXffrFSihB = false;}
      if(fPinJCtGdY == true){fPinJCtGdY = false;}
      if(nlXkYZwHVQ == true){nlXkYZwHVQ = false;}
      if(fUgwygAtGo == true){fUgwygAtGo = false;}
      if(SCeptEBEJl == true){SCeptEBEJl = false;}
      if(PqojrbAuGS == true){PqojrbAuGS = false;}
      if(ILNRUKimpc == true){ILNRUKimpc = false;}
      if(BAznFkHgpU == true){BAznFkHgpU = false;}
      if(YqxjAofxDV == true){YqxjAofxDV = false;}
      if(gFmngHoMUj == true){gFmngHoMUj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUZGACYENK
{ 
  void pMoLffJksu()
  { 
      bool RpgepcOyhV = false;
      bool xzLqRhRopW = false;
      bool AFMNxiQNTY = false;
      bool kJxYJXHjgM = false;
      bool oakMwiwnqs = false;
      bool oYECfLdTgG = false;
      bool LAdIjnClht = false;
      bool ZhHchYTzQO = false;
      bool lbWajMFtsx = false;
      bool snCZAowbbI = false;
      bool fKGxSGRaUG = false;
      bool rdDSTjdDYX = false;
      bool iHrkAlegcs = false;
      bool bqWHhbUYHc = false;
      bool udZlEOkjFP = false;
      bool KsDEZYRVwg = false;
      bool ajybeBHukr = false;
      bool OEwucEhFfk = false;
      bool AuaMhimShJ = false;
      bool JzbZBKfyHD = false;
      string bhKfVyIeKm;
      string VsMAgaqGIe;
      string WgLKCjjftT;
      string YGwWrSmViJ;
      string wicwKbkjxV;
      string VdPbEuVzdk;
      string OckqOPxpHN;
      string nVWzhnDPzZ;
      string zAhXytpTRx;
      string xmrxuTylhu;
      string etbihAGQtQ;
      string qGADlOtMrT;
      string ZcXKQBcZDO;
      string oRhEuFXypx;
      string mZZBFplnLf;
      string YksNVBWQRg;
      string WgMeaYYuHf;
      string pwWufzDWFa;
      string OoOXoDYTit;
      string iHfJaGNtZf;
      if(bhKfVyIeKm == etbihAGQtQ){RpgepcOyhV = true;}
      else if(etbihAGQtQ == bhKfVyIeKm){fKGxSGRaUG = true;}
      if(VsMAgaqGIe == qGADlOtMrT){xzLqRhRopW = true;}
      else if(qGADlOtMrT == VsMAgaqGIe){rdDSTjdDYX = true;}
      if(WgLKCjjftT == ZcXKQBcZDO){AFMNxiQNTY = true;}
      else if(ZcXKQBcZDO == WgLKCjjftT){iHrkAlegcs = true;}
      if(YGwWrSmViJ == oRhEuFXypx){kJxYJXHjgM = true;}
      else if(oRhEuFXypx == YGwWrSmViJ){bqWHhbUYHc = true;}
      if(wicwKbkjxV == mZZBFplnLf){oakMwiwnqs = true;}
      else if(mZZBFplnLf == wicwKbkjxV){udZlEOkjFP = true;}
      if(VdPbEuVzdk == YksNVBWQRg){oYECfLdTgG = true;}
      else if(YksNVBWQRg == VdPbEuVzdk){KsDEZYRVwg = true;}
      if(OckqOPxpHN == WgMeaYYuHf){LAdIjnClht = true;}
      else if(WgMeaYYuHf == OckqOPxpHN){ajybeBHukr = true;}
      if(nVWzhnDPzZ == pwWufzDWFa){ZhHchYTzQO = true;}
      if(zAhXytpTRx == OoOXoDYTit){lbWajMFtsx = true;}
      if(xmrxuTylhu == iHfJaGNtZf){snCZAowbbI = true;}
      while(pwWufzDWFa == nVWzhnDPzZ){OEwucEhFfk = true;}
      while(OoOXoDYTit == OoOXoDYTit){AuaMhimShJ = true;}
      while(iHfJaGNtZf == iHfJaGNtZf){JzbZBKfyHD = true;}
      if(RpgepcOyhV == true){RpgepcOyhV = false;}
      if(xzLqRhRopW == true){xzLqRhRopW = false;}
      if(AFMNxiQNTY == true){AFMNxiQNTY = false;}
      if(kJxYJXHjgM == true){kJxYJXHjgM = false;}
      if(oakMwiwnqs == true){oakMwiwnqs = false;}
      if(oYECfLdTgG == true){oYECfLdTgG = false;}
      if(LAdIjnClht == true){LAdIjnClht = false;}
      if(ZhHchYTzQO == true){ZhHchYTzQO = false;}
      if(lbWajMFtsx == true){lbWajMFtsx = false;}
      if(snCZAowbbI == true){snCZAowbbI = false;}
      if(fKGxSGRaUG == true){fKGxSGRaUG = false;}
      if(rdDSTjdDYX == true){rdDSTjdDYX = false;}
      if(iHrkAlegcs == true){iHrkAlegcs = false;}
      if(bqWHhbUYHc == true){bqWHhbUYHc = false;}
      if(udZlEOkjFP == true){udZlEOkjFP = false;}
      if(KsDEZYRVwg == true){KsDEZYRVwg = false;}
      if(ajybeBHukr == true){ajybeBHukr = false;}
      if(OEwucEhFfk == true){OEwucEhFfk = false;}
      if(AuaMhimShJ == true){AuaMhimShJ = false;}
      if(JzbZBKfyHD == true){JzbZBKfyHD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUEOKWTYEG
{ 
  void jXrbLGtxMF()
  { 
      bool xTThTXgwVB = false;
      bool puefGDgEFK = false;
      bool SPJViaKJpQ = false;
      bool XipBMiozlS = false;
      bool xKLMtAJnix = false;
      bool TomWdgKxzr = false;
      bool NXGFcHEdTW = false;
      bool OhRlMHExbi = false;
      bool RVZrwiwTXe = false;
      bool YqAtEZEFim = false;
      bool ufUMhkWAJV = false;
      bool cMVParxNJs = false;
      bool KkFoyWgXhm = false;
      bool DzNnnkBNJL = false;
      bool MwJCCLVkSM = false;
      bool cqwobKZeOL = false;
      bool DzSWRczgbo = false;
      bool qiDygOaCml = false;
      bool AwFUJMDXLc = false;
      bool KVzyHMcmjY = false;
      string BbIMhcSzst;
      string nCqKqGHfaf;
      string gtSjOLcVud;
      string lNIWyWSkdS;
      string qlHbObhKOq;
      string TMIexHIYxW;
      string AxEOHZtTLT;
      string nWCInulpUl;
      string cRGDKZEdYq;
      string NtmHRthrUn;
      string hNyuDwJApC;
      string USDLsipAEg;
      string VPtUFsjupt;
      string MtUfDOSLAN;
      string PDnWWupaNi;
      string DhmmSSTdpJ;
      string MOKuoZxWHe;
      string PeAqQRbXyJ;
      string DIhGpeHgNk;
      string uoUpAAsrgw;
      if(BbIMhcSzst == hNyuDwJApC){xTThTXgwVB = true;}
      else if(hNyuDwJApC == BbIMhcSzst){ufUMhkWAJV = true;}
      if(nCqKqGHfaf == USDLsipAEg){puefGDgEFK = true;}
      else if(USDLsipAEg == nCqKqGHfaf){cMVParxNJs = true;}
      if(gtSjOLcVud == VPtUFsjupt){SPJViaKJpQ = true;}
      else if(VPtUFsjupt == gtSjOLcVud){KkFoyWgXhm = true;}
      if(lNIWyWSkdS == MtUfDOSLAN){XipBMiozlS = true;}
      else if(MtUfDOSLAN == lNIWyWSkdS){DzNnnkBNJL = true;}
      if(qlHbObhKOq == PDnWWupaNi){xKLMtAJnix = true;}
      else if(PDnWWupaNi == qlHbObhKOq){MwJCCLVkSM = true;}
      if(TMIexHIYxW == DhmmSSTdpJ){TomWdgKxzr = true;}
      else if(DhmmSSTdpJ == TMIexHIYxW){cqwobKZeOL = true;}
      if(AxEOHZtTLT == MOKuoZxWHe){NXGFcHEdTW = true;}
      else if(MOKuoZxWHe == AxEOHZtTLT){DzSWRczgbo = true;}
      if(nWCInulpUl == PeAqQRbXyJ){OhRlMHExbi = true;}
      if(cRGDKZEdYq == DIhGpeHgNk){RVZrwiwTXe = true;}
      if(NtmHRthrUn == uoUpAAsrgw){YqAtEZEFim = true;}
      while(PeAqQRbXyJ == nWCInulpUl){qiDygOaCml = true;}
      while(DIhGpeHgNk == DIhGpeHgNk){AwFUJMDXLc = true;}
      while(uoUpAAsrgw == uoUpAAsrgw){KVzyHMcmjY = true;}
      if(xTThTXgwVB == true){xTThTXgwVB = false;}
      if(puefGDgEFK == true){puefGDgEFK = false;}
      if(SPJViaKJpQ == true){SPJViaKJpQ = false;}
      if(XipBMiozlS == true){XipBMiozlS = false;}
      if(xKLMtAJnix == true){xKLMtAJnix = false;}
      if(TomWdgKxzr == true){TomWdgKxzr = false;}
      if(NXGFcHEdTW == true){NXGFcHEdTW = false;}
      if(OhRlMHExbi == true){OhRlMHExbi = false;}
      if(RVZrwiwTXe == true){RVZrwiwTXe = false;}
      if(YqAtEZEFim == true){YqAtEZEFim = false;}
      if(ufUMhkWAJV == true){ufUMhkWAJV = false;}
      if(cMVParxNJs == true){cMVParxNJs = false;}
      if(KkFoyWgXhm == true){KkFoyWgXhm = false;}
      if(DzNnnkBNJL == true){DzNnnkBNJL = false;}
      if(MwJCCLVkSM == true){MwJCCLVkSM = false;}
      if(cqwobKZeOL == true){cqwobKZeOL = false;}
      if(DzSWRczgbo == true){DzSWRczgbo = false;}
      if(qiDygOaCml == true){qiDygOaCml = false;}
      if(AwFUJMDXLc == true){AwFUJMDXLc = false;}
      if(KVzyHMcmjY == true){KVzyHMcmjY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPIKGTUWKW
{ 
  void UgpCWQGsHp()
  { 
      bool BXbfPSLUAT = false;
      bool QQFPBUuoVN = false;
      bool WKDeADzXmJ = false;
      bool DYHDjATuFV = false;
      bool iuMlIyCuNf = false;
      bool FqCmBqTwfM = false;
      bool TngqPrJBeA = false;
      bool AAiAdayRWB = false;
      bool BEKHDMVTCr = false;
      bool fWOrCuOUVQ = false;
      bool oBPMeEHCIa = false;
      bool sCZeLOcZmD = false;
      bool VoylTclqyi = false;
      bool McuGLAnyby = false;
      bool FTLbzdxjgm = false;
      bool RngStzCcrC = false;
      bool SQEYNPHTSL = false;
      bool ZeynyCdVmp = false;
      bool eBJKRXucLM = false;
      bool xLFYfoPlNi = false;
      string SezCptUCUp;
      string DLKhROxRFV;
      string nRPrbClVGE;
      string ndOgXkIxqh;
      string AUewEsUdul;
      string sVezVAPHZn;
      string HyuQCZxcKg;
      string GAaWUTmSni;
      string hIaTKSzOLX;
      string VAWCZBZNtd;
      string wqTNfstHdC;
      string MwTqGzXaFi;
      string ahRlLFcXwS;
      string sYYJmpnMnR;
      string XqjJKYgfwa;
      string dyILDNZgCZ;
      string QWKLImXJEP;
      string KKlnKjxIbl;
      string XwaVouQMFY;
      string PHKOABfYAX;
      if(SezCptUCUp == wqTNfstHdC){BXbfPSLUAT = true;}
      else if(wqTNfstHdC == SezCptUCUp){oBPMeEHCIa = true;}
      if(DLKhROxRFV == MwTqGzXaFi){QQFPBUuoVN = true;}
      else if(MwTqGzXaFi == DLKhROxRFV){sCZeLOcZmD = true;}
      if(nRPrbClVGE == ahRlLFcXwS){WKDeADzXmJ = true;}
      else if(ahRlLFcXwS == nRPrbClVGE){VoylTclqyi = true;}
      if(ndOgXkIxqh == sYYJmpnMnR){DYHDjATuFV = true;}
      else if(sYYJmpnMnR == ndOgXkIxqh){McuGLAnyby = true;}
      if(AUewEsUdul == XqjJKYgfwa){iuMlIyCuNf = true;}
      else if(XqjJKYgfwa == AUewEsUdul){FTLbzdxjgm = true;}
      if(sVezVAPHZn == dyILDNZgCZ){FqCmBqTwfM = true;}
      else if(dyILDNZgCZ == sVezVAPHZn){RngStzCcrC = true;}
      if(HyuQCZxcKg == QWKLImXJEP){TngqPrJBeA = true;}
      else if(QWKLImXJEP == HyuQCZxcKg){SQEYNPHTSL = true;}
      if(GAaWUTmSni == KKlnKjxIbl){AAiAdayRWB = true;}
      if(hIaTKSzOLX == XwaVouQMFY){BEKHDMVTCr = true;}
      if(VAWCZBZNtd == PHKOABfYAX){fWOrCuOUVQ = true;}
      while(KKlnKjxIbl == GAaWUTmSni){ZeynyCdVmp = true;}
      while(XwaVouQMFY == XwaVouQMFY){eBJKRXucLM = true;}
      while(PHKOABfYAX == PHKOABfYAX){xLFYfoPlNi = true;}
      if(BXbfPSLUAT == true){BXbfPSLUAT = false;}
      if(QQFPBUuoVN == true){QQFPBUuoVN = false;}
      if(WKDeADzXmJ == true){WKDeADzXmJ = false;}
      if(DYHDjATuFV == true){DYHDjATuFV = false;}
      if(iuMlIyCuNf == true){iuMlIyCuNf = false;}
      if(FqCmBqTwfM == true){FqCmBqTwfM = false;}
      if(TngqPrJBeA == true){TngqPrJBeA = false;}
      if(AAiAdayRWB == true){AAiAdayRWB = false;}
      if(BEKHDMVTCr == true){BEKHDMVTCr = false;}
      if(fWOrCuOUVQ == true){fWOrCuOUVQ = false;}
      if(oBPMeEHCIa == true){oBPMeEHCIa = false;}
      if(sCZeLOcZmD == true){sCZeLOcZmD = false;}
      if(VoylTclqyi == true){VoylTclqyi = false;}
      if(McuGLAnyby == true){McuGLAnyby = false;}
      if(FTLbzdxjgm == true){FTLbzdxjgm = false;}
      if(RngStzCcrC == true){RngStzCcrC = false;}
      if(SQEYNPHTSL == true){SQEYNPHTSL = false;}
      if(ZeynyCdVmp == true){ZeynyCdVmp = false;}
      if(eBJKRXucLM == true){eBJKRXucLM = false;}
      if(xLFYfoPlNi == true){xLFYfoPlNi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIOYTIOJFM
{ 
  void zInoLIotZV()
  { 
      bool DMPqVeMpBe = false;
      bool jXNmfMqIjY = false;
      bool laOQwAuRrA = false;
      bool LibLgJgtnh = false;
      bool BZZEqRuVFb = false;
      bool MKRJHbxytV = false;
      bool juyBTAuBGV = false;
      bool ewUCXLBKYd = false;
      bool EYMPmBQSEE = false;
      bool MhASyGbYkp = false;
      bool WtPixPpOlu = false;
      bool amZPQKihNS = false;
      bool ibwCJxwBER = false;
      bool jcYhHKJcSW = false;
      bool KCgIcYIkCm = false;
      bool XsKSGtxMZA = false;
      bool TnKTLyNqIF = false;
      bool AFPpHgunYj = false;
      bool oLzQtpRGbM = false;
      bool NwDSCVqMwe = false;
      string QffjZAQQJe;
      string RnJSbQlsCQ;
      string HhYNqZQlAU;
      string VFHoYwZmoz;
      string zWpAonkQrb;
      string LwLMBiHSrA;
      string jdPnJMgUse;
      string pyEDRjqXXD;
      string ozsYJYtumo;
      string oHuoOUGCpc;
      string GPXMkMrHtQ;
      string riunLjkqek;
      string RlgDpiDOnw;
      string dnguwYbfnx;
      string glAVxFMGdd;
      string iPXFKUiTWC;
      string IcSymDCzql;
      string IECgEekKGj;
      string WwkJNNQaja;
      string pIJkoDTCit;
      if(QffjZAQQJe == GPXMkMrHtQ){DMPqVeMpBe = true;}
      else if(GPXMkMrHtQ == QffjZAQQJe){WtPixPpOlu = true;}
      if(RnJSbQlsCQ == riunLjkqek){jXNmfMqIjY = true;}
      else if(riunLjkqek == RnJSbQlsCQ){amZPQKihNS = true;}
      if(HhYNqZQlAU == RlgDpiDOnw){laOQwAuRrA = true;}
      else if(RlgDpiDOnw == HhYNqZQlAU){ibwCJxwBER = true;}
      if(VFHoYwZmoz == dnguwYbfnx){LibLgJgtnh = true;}
      else if(dnguwYbfnx == VFHoYwZmoz){jcYhHKJcSW = true;}
      if(zWpAonkQrb == glAVxFMGdd){BZZEqRuVFb = true;}
      else if(glAVxFMGdd == zWpAonkQrb){KCgIcYIkCm = true;}
      if(LwLMBiHSrA == iPXFKUiTWC){MKRJHbxytV = true;}
      else if(iPXFKUiTWC == LwLMBiHSrA){XsKSGtxMZA = true;}
      if(jdPnJMgUse == IcSymDCzql){juyBTAuBGV = true;}
      else if(IcSymDCzql == jdPnJMgUse){TnKTLyNqIF = true;}
      if(pyEDRjqXXD == IECgEekKGj){ewUCXLBKYd = true;}
      if(ozsYJYtumo == WwkJNNQaja){EYMPmBQSEE = true;}
      if(oHuoOUGCpc == pIJkoDTCit){MhASyGbYkp = true;}
      while(IECgEekKGj == pyEDRjqXXD){AFPpHgunYj = true;}
      while(WwkJNNQaja == WwkJNNQaja){oLzQtpRGbM = true;}
      while(pIJkoDTCit == pIJkoDTCit){NwDSCVqMwe = true;}
      if(DMPqVeMpBe == true){DMPqVeMpBe = false;}
      if(jXNmfMqIjY == true){jXNmfMqIjY = false;}
      if(laOQwAuRrA == true){laOQwAuRrA = false;}
      if(LibLgJgtnh == true){LibLgJgtnh = false;}
      if(BZZEqRuVFb == true){BZZEqRuVFb = false;}
      if(MKRJHbxytV == true){MKRJHbxytV = false;}
      if(juyBTAuBGV == true){juyBTAuBGV = false;}
      if(ewUCXLBKYd == true){ewUCXLBKYd = false;}
      if(EYMPmBQSEE == true){EYMPmBQSEE = false;}
      if(MhASyGbYkp == true){MhASyGbYkp = false;}
      if(WtPixPpOlu == true){WtPixPpOlu = false;}
      if(amZPQKihNS == true){amZPQKihNS = false;}
      if(ibwCJxwBER == true){ibwCJxwBER = false;}
      if(jcYhHKJcSW == true){jcYhHKJcSW = false;}
      if(KCgIcYIkCm == true){KCgIcYIkCm = false;}
      if(XsKSGtxMZA == true){XsKSGtxMZA = false;}
      if(TnKTLyNqIF == true){TnKTLyNqIF = false;}
      if(AFPpHgunYj == true){AFPpHgunYj = false;}
      if(oLzQtpRGbM == true){oLzQtpRGbM = false;}
      if(NwDSCVqMwe == true){NwDSCVqMwe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUYGSLPRUI
{ 
  void WpLJEaMQxH()
  { 
      bool iYINlFSXrS = false;
      bool DETkEKZIdz = false;
      bool eSHmPranAd = false;
      bool FpfGyMJTOJ = false;
      bool pIZZJApAkd = false;
      bool KbkONQQUxs = false;
      bool ddWOMMYNmr = false;
      bool AFtTJVrhdP = false;
      bool CZDWTcEQsh = false;
      bool uoWUeMkKNw = false;
      bool abMrcEhRFq = false;
      bool XiqgpDZzuj = false;
      bool IHTFxLiZnx = false;
      bool kgTgnZNLsO = false;
      bool ulKCJLyoda = false;
      bool lkPcnTIHuR = false;
      bool VIdIGpOJrQ = false;
      bool pOGfnVwRul = false;
      bool MtuMKzQqsU = false;
      bool RFQbsmICuT = false;
      string PPaaACRLze;
      string hgdbHQufGy;
      string LBSZNCZYUa;
      string KBhTTbcqHx;
      string dxqgbVcbAn;
      string GwHxeNwAMy;
      string crpYTfzJHf;
      string mDYJUNKlyr;
      string YxYgTOskoG;
      string ebdITlGRMu;
      string WTUTBCWybQ;
      string DKCUZeSJFF;
      string lNTBBKZPoi;
      string GrZCUEcFeQ;
      string quIYCTZIin;
      string SxMGJIzSSp;
      string bHJsJKkAAU;
      string CNdoNqFuyg;
      string kRgAPJfSrM;
      string EJlonjkPOr;
      if(PPaaACRLze == WTUTBCWybQ){iYINlFSXrS = true;}
      else if(WTUTBCWybQ == PPaaACRLze){abMrcEhRFq = true;}
      if(hgdbHQufGy == DKCUZeSJFF){DETkEKZIdz = true;}
      else if(DKCUZeSJFF == hgdbHQufGy){XiqgpDZzuj = true;}
      if(LBSZNCZYUa == lNTBBKZPoi){eSHmPranAd = true;}
      else if(lNTBBKZPoi == LBSZNCZYUa){IHTFxLiZnx = true;}
      if(KBhTTbcqHx == GrZCUEcFeQ){FpfGyMJTOJ = true;}
      else if(GrZCUEcFeQ == KBhTTbcqHx){kgTgnZNLsO = true;}
      if(dxqgbVcbAn == quIYCTZIin){pIZZJApAkd = true;}
      else if(quIYCTZIin == dxqgbVcbAn){ulKCJLyoda = true;}
      if(GwHxeNwAMy == SxMGJIzSSp){KbkONQQUxs = true;}
      else if(SxMGJIzSSp == GwHxeNwAMy){lkPcnTIHuR = true;}
      if(crpYTfzJHf == bHJsJKkAAU){ddWOMMYNmr = true;}
      else if(bHJsJKkAAU == crpYTfzJHf){VIdIGpOJrQ = true;}
      if(mDYJUNKlyr == CNdoNqFuyg){AFtTJVrhdP = true;}
      if(YxYgTOskoG == kRgAPJfSrM){CZDWTcEQsh = true;}
      if(ebdITlGRMu == EJlonjkPOr){uoWUeMkKNw = true;}
      while(CNdoNqFuyg == mDYJUNKlyr){pOGfnVwRul = true;}
      while(kRgAPJfSrM == kRgAPJfSrM){MtuMKzQqsU = true;}
      while(EJlonjkPOr == EJlonjkPOr){RFQbsmICuT = true;}
      if(iYINlFSXrS == true){iYINlFSXrS = false;}
      if(DETkEKZIdz == true){DETkEKZIdz = false;}
      if(eSHmPranAd == true){eSHmPranAd = false;}
      if(FpfGyMJTOJ == true){FpfGyMJTOJ = false;}
      if(pIZZJApAkd == true){pIZZJApAkd = false;}
      if(KbkONQQUxs == true){KbkONQQUxs = false;}
      if(ddWOMMYNmr == true){ddWOMMYNmr = false;}
      if(AFtTJVrhdP == true){AFtTJVrhdP = false;}
      if(CZDWTcEQsh == true){CZDWTcEQsh = false;}
      if(uoWUeMkKNw == true){uoWUeMkKNw = false;}
      if(abMrcEhRFq == true){abMrcEhRFq = false;}
      if(XiqgpDZzuj == true){XiqgpDZzuj = false;}
      if(IHTFxLiZnx == true){IHTFxLiZnx = false;}
      if(kgTgnZNLsO == true){kgTgnZNLsO = false;}
      if(ulKCJLyoda == true){ulKCJLyoda = false;}
      if(lkPcnTIHuR == true){lkPcnTIHuR = false;}
      if(VIdIGpOJrQ == true){VIdIGpOJrQ = false;}
      if(pOGfnVwRul == true){pOGfnVwRul = false;}
      if(MtuMKzQqsU == true){MtuMKzQqsU = false;}
      if(RFQbsmICuT == true){RFQbsmICuT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PPIIMKPDVV
{ 
  void RAtjmYTpWT()
  { 
      bool gRnTlwUpZD = false;
      bool VUkzuGKFAR = false;
      bool sVcPTQtUDX = false;
      bool lcsKTdpeOf = false;
      bool VQnIGMCqgA = false;
      bool SRKKuKnYzU = false;
      bool BAlCQrbafQ = false;
      bool QepTwbgUIH = false;
      bool NCnDEUShOI = false;
      bool pResdUdlqO = false;
      bool kbLPjmbpOT = false;
      bool dTQrHyMiyw = false;
      bool ZsLXayAwpa = false;
      bool xuctVlqXSQ = false;
      bool scSudVAmle = false;
      bool IumunrPmok = false;
      bool meAnViqVVU = false;
      bool HnQgDxZPsF = false;
      bool yNKKRCHhFd = false;
      bool VEhgcNbdZu = false;
      string oydRWqTEFN;
      string xjIMbhoMIS;
      string wQUoMZNhcL;
      string KihCYTKRtx;
      string xIAQOmDOYQ;
      string UuIIDYdoEx;
      string clbtCNBFnH;
      string XXRLVnPDZY;
      string WzIMpPaZzz;
      string pUMxTLgGNA;
      string lxZQsxcxlO;
      string JZOfadcPEm;
      string mbGoQCLUqJ;
      string HJoZmYYqSs;
      string lcmjoQGgVp;
      string hRBaNKqkAq;
      string kIFcHAjorC;
      string ElwLAJnVzA;
      string ueyAbpHOLc;
      string hnqbHcWKco;
      if(oydRWqTEFN == lxZQsxcxlO){gRnTlwUpZD = true;}
      else if(lxZQsxcxlO == oydRWqTEFN){kbLPjmbpOT = true;}
      if(xjIMbhoMIS == JZOfadcPEm){VUkzuGKFAR = true;}
      else if(JZOfadcPEm == xjIMbhoMIS){dTQrHyMiyw = true;}
      if(wQUoMZNhcL == mbGoQCLUqJ){sVcPTQtUDX = true;}
      else if(mbGoQCLUqJ == wQUoMZNhcL){ZsLXayAwpa = true;}
      if(KihCYTKRtx == HJoZmYYqSs){lcsKTdpeOf = true;}
      else if(HJoZmYYqSs == KihCYTKRtx){xuctVlqXSQ = true;}
      if(xIAQOmDOYQ == lcmjoQGgVp){VQnIGMCqgA = true;}
      else if(lcmjoQGgVp == xIAQOmDOYQ){scSudVAmle = true;}
      if(UuIIDYdoEx == hRBaNKqkAq){SRKKuKnYzU = true;}
      else if(hRBaNKqkAq == UuIIDYdoEx){IumunrPmok = true;}
      if(clbtCNBFnH == kIFcHAjorC){BAlCQrbafQ = true;}
      else if(kIFcHAjorC == clbtCNBFnH){meAnViqVVU = true;}
      if(XXRLVnPDZY == ElwLAJnVzA){QepTwbgUIH = true;}
      if(WzIMpPaZzz == ueyAbpHOLc){NCnDEUShOI = true;}
      if(pUMxTLgGNA == hnqbHcWKco){pResdUdlqO = true;}
      while(ElwLAJnVzA == XXRLVnPDZY){HnQgDxZPsF = true;}
      while(ueyAbpHOLc == ueyAbpHOLc){yNKKRCHhFd = true;}
      while(hnqbHcWKco == hnqbHcWKco){VEhgcNbdZu = true;}
      if(gRnTlwUpZD == true){gRnTlwUpZD = false;}
      if(VUkzuGKFAR == true){VUkzuGKFAR = false;}
      if(sVcPTQtUDX == true){sVcPTQtUDX = false;}
      if(lcsKTdpeOf == true){lcsKTdpeOf = false;}
      if(VQnIGMCqgA == true){VQnIGMCqgA = false;}
      if(SRKKuKnYzU == true){SRKKuKnYzU = false;}
      if(BAlCQrbafQ == true){BAlCQrbafQ = false;}
      if(QepTwbgUIH == true){QepTwbgUIH = false;}
      if(NCnDEUShOI == true){NCnDEUShOI = false;}
      if(pResdUdlqO == true){pResdUdlqO = false;}
      if(kbLPjmbpOT == true){kbLPjmbpOT = false;}
      if(dTQrHyMiyw == true){dTQrHyMiyw = false;}
      if(ZsLXayAwpa == true){ZsLXayAwpa = false;}
      if(xuctVlqXSQ == true){xuctVlqXSQ = false;}
      if(scSudVAmle == true){scSudVAmle = false;}
      if(IumunrPmok == true){IumunrPmok = false;}
      if(meAnViqVVU == true){meAnViqVVU = false;}
      if(HnQgDxZPsF == true){HnQgDxZPsF = false;}
      if(yNKKRCHhFd == true){yNKKRCHhFd = false;}
      if(VEhgcNbdZu == true){VEhgcNbdZu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEPXEPHZBT
{ 
  void gSkijjlzMx()
  { 
      bool CWFsqgyrbX = false;
      bool DVMRWXiIzX = false;
      bool qVrcGKSXPZ = false;
      bool YmGgqDELJj = false;
      bool SWmwcCUcAj = false;
      bool IqFzTfdblg = false;
      bool NZbBzPPeZT = false;
      bool SWzOEThwzE = false;
      bool ooXfRggGNK = false;
      bool ZcZcVstlxM = false;
      bool loCfQkrptz = false;
      bool xgcgqYCwiR = false;
      bool iIRPtpxVsL = false;
      bool ZwzlSAlqOg = false;
      bool npMNNrzrlw = false;
      bool pxCedcWmla = false;
      bool nWxhZAhpOq = false;
      bool mLhCcrwEBC = false;
      bool pEjxVbtTIo = false;
      bool cyFnsRsdnM = false;
      string jirUdsdAlP;
      string ZGjBuPpBeK;
      string VsmPBJTJHb;
      string UnxgqdqSwk;
      string jCmmRRtVJf;
      string eWlBTqucTT;
      string ZUrKukIDJQ;
      string XXFtaTGAyi;
      string PxAbxxCwMA;
      string iOybKOJbqf;
      string IqMsHHRraz;
      string jtejEbUPMx;
      string iMpIhJYciL;
      string KdJRaYkGUp;
      string fJUMQnjOXh;
      string tsOsxuADLx;
      string hnJPoFkMIe;
      string qNuWRYrdqs;
      string ZKEAQQOPUf;
      string YguXHqAEWK;
      if(jirUdsdAlP == IqMsHHRraz){CWFsqgyrbX = true;}
      else if(IqMsHHRraz == jirUdsdAlP){loCfQkrptz = true;}
      if(ZGjBuPpBeK == jtejEbUPMx){DVMRWXiIzX = true;}
      else if(jtejEbUPMx == ZGjBuPpBeK){xgcgqYCwiR = true;}
      if(VsmPBJTJHb == iMpIhJYciL){qVrcGKSXPZ = true;}
      else if(iMpIhJYciL == VsmPBJTJHb){iIRPtpxVsL = true;}
      if(UnxgqdqSwk == KdJRaYkGUp){YmGgqDELJj = true;}
      else if(KdJRaYkGUp == UnxgqdqSwk){ZwzlSAlqOg = true;}
      if(jCmmRRtVJf == fJUMQnjOXh){SWmwcCUcAj = true;}
      else if(fJUMQnjOXh == jCmmRRtVJf){npMNNrzrlw = true;}
      if(eWlBTqucTT == tsOsxuADLx){IqFzTfdblg = true;}
      else if(tsOsxuADLx == eWlBTqucTT){pxCedcWmla = true;}
      if(ZUrKukIDJQ == hnJPoFkMIe){NZbBzPPeZT = true;}
      else if(hnJPoFkMIe == ZUrKukIDJQ){nWxhZAhpOq = true;}
      if(XXFtaTGAyi == qNuWRYrdqs){SWzOEThwzE = true;}
      if(PxAbxxCwMA == ZKEAQQOPUf){ooXfRggGNK = true;}
      if(iOybKOJbqf == YguXHqAEWK){ZcZcVstlxM = true;}
      while(qNuWRYrdqs == XXFtaTGAyi){mLhCcrwEBC = true;}
      while(ZKEAQQOPUf == ZKEAQQOPUf){pEjxVbtTIo = true;}
      while(YguXHqAEWK == YguXHqAEWK){cyFnsRsdnM = true;}
      if(CWFsqgyrbX == true){CWFsqgyrbX = false;}
      if(DVMRWXiIzX == true){DVMRWXiIzX = false;}
      if(qVrcGKSXPZ == true){qVrcGKSXPZ = false;}
      if(YmGgqDELJj == true){YmGgqDELJj = false;}
      if(SWmwcCUcAj == true){SWmwcCUcAj = false;}
      if(IqFzTfdblg == true){IqFzTfdblg = false;}
      if(NZbBzPPeZT == true){NZbBzPPeZT = false;}
      if(SWzOEThwzE == true){SWzOEThwzE = false;}
      if(ooXfRggGNK == true){ooXfRggGNK = false;}
      if(ZcZcVstlxM == true){ZcZcVstlxM = false;}
      if(loCfQkrptz == true){loCfQkrptz = false;}
      if(xgcgqYCwiR == true){xgcgqYCwiR = false;}
      if(iIRPtpxVsL == true){iIRPtpxVsL = false;}
      if(ZwzlSAlqOg == true){ZwzlSAlqOg = false;}
      if(npMNNrzrlw == true){npMNNrzrlw = false;}
      if(pxCedcWmla == true){pxCedcWmla = false;}
      if(nWxhZAhpOq == true){nWxhZAhpOq = false;}
      if(mLhCcrwEBC == true){mLhCcrwEBC = false;}
      if(pEjxVbtTIo == true){pEjxVbtTIo = false;}
      if(cyFnsRsdnM == true){cyFnsRsdnM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQTVMZGSWG
{ 
  void RxZexzUnzP()
  { 
      bool PVeNPBhIIX = false;
      bool bfpUIPfPdI = false;
      bool pjrqHBnfZu = false;
      bool TjmTHSOjcB = false;
      bool kxkluYRQDO = false;
      bool ZTwpafcnGO = false;
      bool NBiMDrrWMp = false;
      bool AwlcXryGui = false;
      bool iWbKVAmwra = false;
      bool oadOniOYhD = false;
      bool fuENOdhTSh = false;
      bool hWrWepYYpD = false;
      bool EwdlAZSXnn = false;
      bool dYYqDnSOwr = false;
      bool SSdKsShGix = false;
      bool JpidyjRRMn = false;
      bool LJedEIyBTq = false;
      bool XKbxkkRTrh = false;
      bool qLnqenptrT = false;
      bool WABHgImzGk = false;
      string ooDDeMjoMl;
      string teNtxwTYDl;
      string jBLALuKpNl;
      string RerARFRMrS;
      string ZHdNossCCp;
      string DgLXAmdCrj;
      string BsaZTPmNcr;
      string dGfjLbWxLR;
      string BInWijTTzd;
      string aPTIRgfDsY;
      string GfZJLwBaLX;
      string PgpZhrEEqj;
      string wSNyROmXSe;
      string uSDmLVidKm;
      string irHbNsZsZY;
      string bbMJbmRarx;
      string IcIgbwdDOL;
      string JZsDBDKlkX;
      string osxsDTGsKX;
      string EIlMdFiazQ;
      if(ooDDeMjoMl == GfZJLwBaLX){PVeNPBhIIX = true;}
      else if(GfZJLwBaLX == ooDDeMjoMl){fuENOdhTSh = true;}
      if(teNtxwTYDl == PgpZhrEEqj){bfpUIPfPdI = true;}
      else if(PgpZhrEEqj == teNtxwTYDl){hWrWepYYpD = true;}
      if(jBLALuKpNl == wSNyROmXSe){pjrqHBnfZu = true;}
      else if(wSNyROmXSe == jBLALuKpNl){EwdlAZSXnn = true;}
      if(RerARFRMrS == uSDmLVidKm){TjmTHSOjcB = true;}
      else if(uSDmLVidKm == RerARFRMrS){dYYqDnSOwr = true;}
      if(ZHdNossCCp == irHbNsZsZY){kxkluYRQDO = true;}
      else if(irHbNsZsZY == ZHdNossCCp){SSdKsShGix = true;}
      if(DgLXAmdCrj == bbMJbmRarx){ZTwpafcnGO = true;}
      else if(bbMJbmRarx == DgLXAmdCrj){JpidyjRRMn = true;}
      if(BsaZTPmNcr == IcIgbwdDOL){NBiMDrrWMp = true;}
      else if(IcIgbwdDOL == BsaZTPmNcr){LJedEIyBTq = true;}
      if(dGfjLbWxLR == JZsDBDKlkX){AwlcXryGui = true;}
      if(BInWijTTzd == osxsDTGsKX){iWbKVAmwra = true;}
      if(aPTIRgfDsY == EIlMdFiazQ){oadOniOYhD = true;}
      while(JZsDBDKlkX == dGfjLbWxLR){XKbxkkRTrh = true;}
      while(osxsDTGsKX == osxsDTGsKX){qLnqenptrT = true;}
      while(EIlMdFiazQ == EIlMdFiazQ){WABHgImzGk = true;}
      if(PVeNPBhIIX == true){PVeNPBhIIX = false;}
      if(bfpUIPfPdI == true){bfpUIPfPdI = false;}
      if(pjrqHBnfZu == true){pjrqHBnfZu = false;}
      if(TjmTHSOjcB == true){TjmTHSOjcB = false;}
      if(kxkluYRQDO == true){kxkluYRQDO = false;}
      if(ZTwpafcnGO == true){ZTwpafcnGO = false;}
      if(NBiMDrrWMp == true){NBiMDrrWMp = false;}
      if(AwlcXryGui == true){AwlcXryGui = false;}
      if(iWbKVAmwra == true){iWbKVAmwra = false;}
      if(oadOniOYhD == true){oadOniOYhD = false;}
      if(fuENOdhTSh == true){fuENOdhTSh = false;}
      if(hWrWepYYpD == true){hWrWepYYpD = false;}
      if(EwdlAZSXnn == true){EwdlAZSXnn = false;}
      if(dYYqDnSOwr == true){dYYqDnSOwr = false;}
      if(SSdKsShGix == true){SSdKsShGix = false;}
      if(JpidyjRRMn == true){JpidyjRRMn = false;}
      if(LJedEIyBTq == true){LJedEIyBTq = false;}
      if(XKbxkkRTrh == true){XKbxkkRTrh = false;}
      if(qLnqenptrT == true){qLnqenptrT = false;}
      if(WABHgImzGk == true){WABHgImzGk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYTKKVKMIH
{ 
  void EZwPLLiZqt()
  { 
      bool LTQUKfKzrL = false;
      bool brlJzxISTw = false;
      bool IKgKqSGhdg = false;
      bool AiphiKSuSu = false;
      bool wdwjGMhMBP = false;
      bool zKJfSBlFdq = false;
      bool YcVLKrBDZn = false;
      bool eNzXzeOwDe = false;
      bool jtfNhpYKOh = false;
      bool YMQbWSHkZN = false;
      bool KdlMklKkgn = false;
      bool lpCyGdxHcT = false;
      bool TqorPRwXBf = false;
      bool WdWoUGIScw = false;
      bool fncauhKRUr = false;
      bool VAHFtSosxS = false;
      bool oliBQISMdA = false;
      bool VdegnfOOxg = false;
      bool HdDJJWWQtB = false;
      bool ROVJGsEbJl = false;
      string RdTRNYVZNJ;
      string tPnCNqFcIw;
      string PUiZGYngbL;
      string CscBObElRi;
      string AGbJtKxGwq;
      string sQwaPwttLn;
      string jnyCGAmlnl;
      string lTKZwJrYeu;
      string bhjjSlwClR;
      string gKadzMHZCs;
      string XLSKFYFWeF;
      string EVOQMCDNjU;
      string DjzWFasgaj;
      string BSVkWQPZes;
      string fZXfMKwJQx;
      string IspgonLuEd;
      string fXwtDkzcsw;
      string lcipodMSJt;
      string eiPcaHcnui;
      string ETVAMHccbb;
      if(RdTRNYVZNJ == XLSKFYFWeF){LTQUKfKzrL = true;}
      else if(XLSKFYFWeF == RdTRNYVZNJ){KdlMklKkgn = true;}
      if(tPnCNqFcIw == EVOQMCDNjU){brlJzxISTw = true;}
      else if(EVOQMCDNjU == tPnCNqFcIw){lpCyGdxHcT = true;}
      if(PUiZGYngbL == DjzWFasgaj){IKgKqSGhdg = true;}
      else if(DjzWFasgaj == PUiZGYngbL){TqorPRwXBf = true;}
      if(CscBObElRi == BSVkWQPZes){AiphiKSuSu = true;}
      else if(BSVkWQPZes == CscBObElRi){WdWoUGIScw = true;}
      if(AGbJtKxGwq == fZXfMKwJQx){wdwjGMhMBP = true;}
      else if(fZXfMKwJQx == AGbJtKxGwq){fncauhKRUr = true;}
      if(sQwaPwttLn == IspgonLuEd){zKJfSBlFdq = true;}
      else if(IspgonLuEd == sQwaPwttLn){VAHFtSosxS = true;}
      if(jnyCGAmlnl == fXwtDkzcsw){YcVLKrBDZn = true;}
      else if(fXwtDkzcsw == jnyCGAmlnl){oliBQISMdA = true;}
      if(lTKZwJrYeu == lcipodMSJt){eNzXzeOwDe = true;}
      if(bhjjSlwClR == eiPcaHcnui){jtfNhpYKOh = true;}
      if(gKadzMHZCs == ETVAMHccbb){YMQbWSHkZN = true;}
      while(lcipodMSJt == lTKZwJrYeu){VdegnfOOxg = true;}
      while(eiPcaHcnui == eiPcaHcnui){HdDJJWWQtB = true;}
      while(ETVAMHccbb == ETVAMHccbb){ROVJGsEbJl = true;}
      if(LTQUKfKzrL == true){LTQUKfKzrL = false;}
      if(brlJzxISTw == true){brlJzxISTw = false;}
      if(IKgKqSGhdg == true){IKgKqSGhdg = false;}
      if(AiphiKSuSu == true){AiphiKSuSu = false;}
      if(wdwjGMhMBP == true){wdwjGMhMBP = false;}
      if(zKJfSBlFdq == true){zKJfSBlFdq = false;}
      if(YcVLKrBDZn == true){YcVLKrBDZn = false;}
      if(eNzXzeOwDe == true){eNzXzeOwDe = false;}
      if(jtfNhpYKOh == true){jtfNhpYKOh = false;}
      if(YMQbWSHkZN == true){YMQbWSHkZN = false;}
      if(KdlMklKkgn == true){KdlMklKkgn = false;}
      if(lpCyGdxHcT == true){lpCyGdxHcT = false;}
      if(TqorPRwXBf == true){TqorPRwXBf = false;}
      if(WdWoUGIScw == true){WdWoUGIScw = false;}
      if(fncauhKRUr == true){fncauhKRUr = false;}
      if(VAHFtSosxS == true){VAHFtSosxS = false;}
      if(oliBQISMdA == true){oliBQISMdA = false;}
      if(VdegnfOOxg == true){VdegnfOOxg = false;}
      if(HdDJJWWQtB == true){HdDJJWWQtB = false;}
      if(ROVJGsEbJl == true){ROVJGsEbJl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBQBIXQQKC
{ 
  void xPnWiXIVTs()
  { 
      bool MfiUBgJpYq = false;
      bool DMrTiMPKdB = false;
      bool rgZxVhsBkV = false;
      bool OLTmomorUQ = false;
      bool JFLaPFDLWy = false;
      bool nNgUTfGlyS = false;
      bool mIEDcrrEeu = false;
      bool XWpNqmVygQ = false;
      bool dgdmgAdzTJ = false;
      bool gCtBcBBIyX = false;
      bool NzgaZQXTcg = false;
      bool JIEhnGdQVc = false;
      bool NskVOUcnjp = false;
      bool kMzJCeACMQ = false;
      bool bKVmzYyMMW = false;
      bool WjlVJUNKMF = false;
      bool njimuwIueJ = false;
      bool FbDFADWxWo = false;
      bool WPaNTBadzh = false;
      bool QopHcrahrC = false;
      string eiorerMaFQ;
      string OZDaqbqWCJ;
      string XtoeARrbFE;
      string ZdrYFbWFfz;
      string UDgyJSNMTA;
      string xqmWajsKrN;
      string zjVAqkgeUP;
      string ElpDoTNqVg;
      string DfHEHiqVxV;
      string hMMSAjhfHY;
      string liqEuKAjgG;
      string VCnLJTcQsH;
      string tLgzhrYWCE;
      string khjwtUnDJw;
      string hGnqzfXAJf;
      string GRlzeaCrWD;
      string kdgbUnSrQo;
      string eZHwZmWpzC;
      string TYNVyTukRT;
      string SwfGKEYLVL;
      if(eiorerMaFQ == liqEuKAjgG){MfiUBgJpYq = true;}
      else if(liqEuKAjgG == eiorerMaFQ){NzgaZQXTcg = true;}
      if(OZDaqbqWCJ == VCnLJTcQsH){DMrTiMPKdB = true;}
      else if(VCnLJTcQsH == OZDaqbqWCJ){JIEhnGdQVc = true;}
      if(XtoeARrbFE == tLgzhrYWCE){rgZxVhsBkV = true;}
      else if(tLgzhrYWCE == XtoeARrbFE){NskVOUcnjp = true;}
      if(ZdrYFbWFfz == khjwtUnDJw){OLTmomorUQ = true;}
      else if(khjwtUnDJw == ZdrYFbWFfz){kMzJCeACMQ = true;}
      if(UDgyJSNMTA == hGnqzfXAJf){JFLaPFDLWy = true;}
      else if(hGnqzfXAJf == UDgyJSNMTA){bKVmzYyMMW = true;}
      if(xqmWajsKrN == GRlzeaCrWD){nNgUTfGlyS = true;}
      else if(GRlzeaCrWD == xqmWajsKrN){WjlVJUNKMF = true;}
      if(zjVAqkgeUP == kdgbUnSrQo){mIEDcrrEeu = true;}
      else if(kdgbUnSrQo == zjVAqkgeUP){njimuwIueJ = true;}
      if(ElpDoTNqVg == eZHwZmWpzC){XWpNqmVygQ = true;}
      if(DfHEHiqVxV == TYNVyTukRT){dgdmgAdzTJ = true;}
      if(hMMSAjhfHY == SwfGKEYLVL){gCtBcBBIyX = true;}
      while(eZHwZmWpzC == ElpDoTNqVg){FbDFADWxWo = true;}
      while(TYNVyTukRT == TYNVyTukRT){WPaNTBadzh = true;}
      while(SwfGKEYLVL == SwfGKEYLVL){QopHcrahrC = true;}
      if(MfiUBgJpYq == true){MfiUBgJpYq = false;}
      if(DMrTiMPKdB == true){DMrTiMPKdB = false;}
      if(rgZxVhsBkV == true){rgZxVhsBkV = false;}
      if(OLTmomorUQ == true){OLTmomorUQ = false;}
      if(JFLaPFDLWy == true){JFLaPFDLWy = false;}
      if(nNgUTfGlyS == true){nNgUTfGlyS = false;}
      if(mIEDcrrEeu == true){mIEDcrrEeu = false;}
      if(XWpNqmVygQ == true){XWpNqmVygQ = false;}
      if(dgdmgAdzTJ == true){dgdmgAdzTJ = false;}
      if(gCtBcBBIyX == true){gCtBcBBIyX = false;}
      if(NzgaZQXTcg == true){NzgaZQXTcg = false;}
      if(JIEhnGdQVc == true){JIEhnGdQVc = false;}
      if(NskVOUcnjp == true){NskVOUcnjp = false;}
      if(kMzJCeACMQ == true){kMzJCeACMQ = false;}
      if(bKVmzYyMMW == true){bKVmzYyMMW = false;}
      if(WjlVJUNKMF == true){WjlVJUNKMF = false;}
      if(njimuwIueJ == true){njimuwIueJ = false;}
      if(FbDFADWxWo == true){FbDFADWxWo = false;}
      if(WPaNTBadzh == true){WPaNTBadzh = false;}
      if(QopHcrahrC == true){QopHcrahrC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKTBGRTBYS
{ 
  void BAOfdfrnFJ()
  { 
      bool SyaNZRVbXp = false;
      bool NwVkIUhKdK = false;
      bool FjreAcbBmN = false;
      bool oeRRuboSBk = false;
      bool RkrPBslsoG = false;
      bool RLlzliGuMw = false;
      bool pToJAhdDpf = false;
      bool ePJrsUqbdH = false;
      bool qiLgwcrRfL = false;
      bool VsFEuxwiPS = false;
      bool OhDJaBCtGR = false;
      bool reRFFHIHMW = false;
      bool pMXdKlKEwu = false;
      bool XILLrJeCFt = false;
      bool ayKOTpbzzn = false;
      bool onVrbCJYzn = false;
      bool qxxLsiSFMu = false;
      bool bFCRwqBIKT = false;
      bool KKFIFjmTip = false;
      bool zGCQDcBzUj = false;
      string nmhEQCpwhz;
      string TxiclQueQr;
      string guWyRmotZZ;
      string GUAgajnXlw;
      string GXYGTwNBhj;
      string srqtQsQjld;
      string MwVHryxCBB;
      string bWrUkJVPdV;
      string ZnLogOdFPh;
      string TDlIiJBROV;
      string zKzgIVzWIG;
      string WAGQEYkgZc;
      string TqlTgYkjkb;
      string IEBIWOndgL;
      string OHwJKSxUDK;
      string YUqkBHYfzi;
      string jOkgySzytp;
      string kGzONLtcJO;
      string aPfaDmNPGO;
      string oHdxaAWPKq;
      if(nmhEQCpwhz == zKzgIVzWIG){SyaNZRVbXp = true;}
      else if(zKzgIVzWIG == nmhEQCpwhz){OhDJaBCtGR = true;}
      if(TxiclQueQr == WAGQEYkgZc){NwVkIUhKdK = true;}
      else if(WAGQEYkgZc == TxiclQueQr){reRFFHIHMW = true;}
      if(guWyRmotZZ == TqlTgYkjkb){FjreAcbBmN = true;}
      else if(TqlTgYkjkb == guWyRmotZZ){pMXdKlKEwu = true;}
      if(GUAgajnXlw == IEBIWOndgL){oeRRuboSBk = true;}
      else if(IEBIWOndgL == GUAgajnXlw){XILLrJeCFt = true;}
      if(GXYGTwNBhj == OHwJKSxUDK){RkrPBslsoG = true;}
      else if(OHwJKSxUDK == GXYGTwNBhj){ayKOTpbzzn = true;}
      if(srqtQsQjld == YUqkBHYfzi){RLlzliGuMw = true;}
      else if(YUqkBHYfzi == srqtQsQjld){onVrbCJYzn = true;}
      if(MwVHryxCBB == jOkgySzytp){pToJAhdDpf = true;}
      else if(jOkgySzytp == MwVHryxCBB){qxxLsiSFMu = true;}
      if(bWrUkJVPdV == kGzONLtcJO){ePJrsUqbdH = true;}
      if(ZnLogOdFPh == aPfaDmNPGO){qiLgwcrRfL = true;}
      if(TDlIiJBROV == oHdxaAWPKq){VsFEuxwiPS = true;}
      while(kGzONLtcJO == bWrUkJVPdV){bFCRwqBIKT = true;}
      while(aPfaDmNPGO == aPfaDmNPGO){KKFIFjmTip = true;}
      while(oHdxaAWPKq == oHdxaAWPKq){zGCQDcBzUj = true;}
      if(SyaNZRVbXp == true){SyaNZRVbXp = false;}
      if(NwVkIUhKdK == true){NwVkIUhKdK = false;}
      if(FjreAcbBmN == true){FjreAcbBmN = false;}
      if(oeRRuboSBk == true){oeRRuboSBk = false;}
      if(RkrPBslsoG == true){RkrPBslsoG = false;}
      if(RLlzliGuMw == true){RLlzliGuMw = false;}
      if(pToJAhdDpf == true){pToJAhdDpf = false;}
      if(ePJrsUqbdH == true){ePJrsUqbdH = false;}
      if(qiLgwcrRfL == true){qiLgwcrRfL = false;}
      if(VsFEuxwiPS == true){VsFEuxwiPS = false;}
      if(OhDJaBCtGR == true){OhDJaBCtGR = false;}
      if(reRFFHIHMW == true){reRFFHIHMW = false;}
      if(pMXdKlKEwu == true){pMXdKlKEwu = false;}
      if(XILLrJeCFt == true){XILLrJeCFt = false;}
      if(ayKOTpbzzn == true){ayKOTpbzzn = false;}
      if(onVrbCJYzn == true){onVrbCJYzn = false;}
      if(qxxLsiSFMu == true){qxxLsiSFMu = false;}
      if(bFCRwqBIKT == true){bFCRwqBIKT = false;}
      if(KKFIFjmTip == true){KKFIFjmTip = false;}
      if(zGCQDcBzUj == true){zGCQDcBzUj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSDSNBVVDS
{ 
  void yiYqHcauKE()
  { 
      bool qQgWpTjykr = false;
      bool madFttDrUA = false;
      bool JoThrCXYOW = false;
      bool mXMwdoOxHe = false;
      bool AzsRXLldXt = false;
      bool ixNCABwzdm = false;
      bool uKiNFOOhbF = false;
      bool eFkpAJwBJg = false;
      bool QtATnoKKub = false;
      bool rOTTjoPfMI = false;
      bool xEBSPdMXBq = false;
      bool FuoxWAJOZQ = false;
      bool EDlzMQkQFL = false;
      bool sQoBiLshEK = false;
      bool blIEWxYVwi = false;
      bool eBGuDsRBGy = false;
      bool ruRpxoGnOK = false;
      bool HbJOnRuhcP = false;
      bool qOUWfrJsxo = false;
      bool tqaGRfURHh = false;
      string lLrSDkoHWK;
      string wTeIaeRjps;
      string UucXPRJHbw;
      string kLLlNoYYzE;
      string ZUKnOJpBrG;
      string FfhOzpiTCl;
      string bgfZYkHrtl;
      string FrjkSAjnJG;
      string bHPUqFcxmW;
      string FFVMcrnkOc;
      string CxHGBMuxuy;
      string GtKwKTQLiT;
      string IJFWfAVXHa;
      string MzZfDeAJTe;
      string JeCoQLtZCJ;
      string abCuUsqjZA;
      string pXpTkGUdrf;
      string SHrDJcGQGU;
      string FwUxzjxeKK;
      string mPiSnloiDJ;
      if(lLrSDkoHWK == CxHGBMuxuy){qQgWpTjykr = true;}
      else if(CxHGBMuxuy == lLrSDkoHWK){xEBSPdMXBq = true;}
      if(wTeIaeRjps == GtKwKTQLiT){madFttDrUA = true;}
      else if(GtKwKTQLiT == wTeIaeRjps){FuoxWAJOZQ = true;}
      if(UucXPRJHbw == IJFWfAVXHa){JoThrCXYOW = true;}
      else if(IJFWfAVXHa == UucXPRJHbw){EDlzMQkQFL = true;}
      if(kLLlNoYYzE == MzZfDeAJTe){mXMwdoOxHe = true;}
      else if(MzZfDeAJTe == kLLlNoYYzE){sQoBiLshEK = true;}
      if(ZUKnOJpBrG == JeCoQLtZCJ){AzsRXLldXt = true;}
      else if(JeCoQLtZCJ == ZUKnOJpBrG){blIEWxYVwi = true;}
      if(FfhOzpiTCl == abCuUsqjZA){ixNCABwzdm = true;}
      else if(abCuUsqjZA == FfhOzpiTCl){eBGuDsRBGy = true;}
      if(bgfZYkHrtl == pXpTkGUdrf){uKiNFOOhbF = true;}
      else if(pXpTkGUdrf == bgfZYkHrtl){ruRpxoGnOK = true;}
      if(FrjkSAjnJG == SHrDJcGQGU){eFkpAJwBJg = true;}
      if(bHPUqFcxmW == FwUxzjxeKK){QtATnoKKub = true;}
      if(FFVMcrnkOc == mPiSnloiDJ){rOTTjoPfMI = true;}
      while(SHrDJcGQGU == FrjkSAjnJG){HbJOnRuhcP = true;}
      while(FwUxzjxeKK == FwUxzjxeKK){qOUWfrJsxo = true;}
      while(mPiSnloiDJ == mPiSnloiDJ){tqaGRfURHh = true;}
      if(qQgWpTjykr == true){qQgWpTjykr = false;}
      if(madFttDrUA == true){madFttDrUA = false;}
      if(JoThrCXYOW == true){JoThrCXYOW = false;}
      if(mXMwdoOxHe == true){mXMwdoOxHe = false;}
      if(AzsRXLldXt == true){AzsRXLldXt = false;}
      if(ixNCABwzdm == true){ixNCABwzdm = false;}
      if(uKiNFOOhbF == true){uKiNFOOhbF = false;}
      if(eFkpAJwBJg == true){eFkpAJwBJg = false;}
      if(QtATnoKKub == true){QtATnoKKub = false;}
      if(rOTTjoPfMI == true){rOTTjoPfMI = false;}
      if(xEBSPdMXBq == true){xEBSPdMXBq = false;}
      if(FuoxWAJOZQ == true){FuoxWAJOZQ = false;}
      if(EDlzMQkQFL == true){EDlzMQkQFL = false;}
      if(sQoBiLshEK == true){sQoBiLshEK = false;}
      if(blIEWxYVwi == true){blIEWxYVwi = false;}
      if(eBGuDsRBGy == true){eBGuDsRBGy = false;}
      if(ruRpxoGnOK == true){ruRpxoGnOK = false;}
      if(HbJOnRuhcP == true){HbJOnRuhcP = false;}
      if(qOUWfrJsxo == true){qOUWfrJsxo = false;}
      if(tqaGRfURHh == true){tqaGRfURHh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQWCRWPMGG
{ 
  void oaPnebZDEE()
  { 
      bool CKwspReBQZ = false;
      bool TrFJCynVus = false;
      bool sTOCUMAgWQ = false;
      bool EqVPusTBpg = false;
      bool QrFCjqGpIR = false;
      bool FGGFoiwtYc = false;
      bool RydzUcWoOJ = false;
      bool dmfNbAOLRc = false;
      bool FJYELyjPaM = false;
      bool xZbMPSNFgH = false;
      bool TRbymRZrdn = false;
      bool UjbwXHZZmW = false;
      bool rHOCLDKTyI = false;
      bool lIeKInhZQt = false;
      bool YqklqNyfnH = false;
      bool rnRJOMDZmj = false;
      bool GFtUCLERmi = false;
      bool ZAIsyAWbKy = false;
      bool FeepQxpUuw = false;
      bool kHmgmSxPjf = false;
      string gaxzSmnRcU;
      string NyQCFsOPad;
      string ZZXPJxNZbw;
      string aXFJuiKRVc;
      string mXmJKsdbUw;
      string gVuALHCgoV;
      string YNpgsosHGW;
      string iwsypBmOFQ;
      string TkFfOFbFyn;
      string fcbADZhFPU;
      string AVVxMjbxJJ;
      string TnbXCnHKRn;
      string MmIRpFUsuQ;
      string TgyjQxPHSe;
      string ceunUrBDyO;
      string RWmbHMMDHH;
      string OiCsolpqHE;
      string YArlKhrUxx;
      string EQtfywsVcE;
      string jMALPscBzh;
      if(gaxzSmnRcU == AVVxMjbxJJ){CKwspReBQZ = true;}
      else if(AVVxMjbxJJ == gaxzSmnRcU){TRbymRZrdn = true;}
      if(NyQCFsOPad == TnbXCnHKRn){TrFJCynVus = true;}
      else if(TnbXCnHKRn == NyQCFsOPad){UjbwXHZZmW = true;}
      if(ZZXPJxNZbw == MmIRpFUsuQ){sTOCUMAgWQ = true;}
      else if(MmIRpFUsuQ == ZZXPJxNZbw){rHOCLDKTyI = true;}
      if(aXFJuiKRVc == TgyjQxPHSe){EqVPusTBpg = true;}
      else if(TgyjQxPHSe == aXFJuiKRVc){lIeKInhZQt = true;}
      if(mXmJKsdbUw == ceunUrBDyO){QrFCjqGpIR = true;}
      else if(ceunUrBDyO == mXmJKsdbUw){YqklqNyfnH = true;}
      if(gVuALHCgoV == RWmbHMMDHH){FGGFoiwtYc = true;}
      else if(RWmbHMMDHH == gVuALHCgoV){rnRJOMDZmj = true;}
      if(YNpgsosHGW == OiCsolpqHE){RydzUcWoOJ = true;}
      else if(OiCsolpqHE == YNpgsosHGW){GFtUCLERmi = true;}
      if(iwsypBmOFQ == YArlKhrUxx){dmfNbAOLRc = true;}
      if(TkFfOFbFyn == EQtfywsVcE){FJYELyjPaM = true;}
      if(fcbADZhFPU == jMALPscBzh){xZbMPSNFgH = true;}
      while(YArlKhrUxx == iwsypBmOFQ){ZAIsyAWbKy = true;}
      while(EQtfywsVcE == EQtfywsVcE){FeepQxpUuw = true;}
      while(jMALPscBzh == jMALPscBzh){kHmgmSxPjf = true;}
      if(CKwspReBQZ == true){CKwspReBQZ = false;}
      if(TrFJCynVus == true){TrFJCynVus = false;}
      if(sTOCUMAgWQ == true){sTOCUMAgWQ = false;}
      if(EqVPusTBpg == true){EqVPusTBpg = false;}
      if(QrFCjqGpIR == true){QrFCjqGpIR = false;}
      if(FGGFoiwtYc == true){FGGFoiwtYc = false;}
      if(RydzUcWoOJ == true){RydzUcWoOJ = false;}
      if(dmfNbAOLRc == true){dmfNbAOLRc = false;}
      if(FJYELyjPaM == true){FJYELyjPaM = false;}
      if(xZbMPSNFgH == true){xZbMPSNFgH = false;}
      if(TRbymRZrdn == true){TRbymRZrdn = false;}
      if(UjbwXHZZmW == true){UjbwXHZZmW = false;}
      if(rHOCLDKTyI == true){rHOCLDKTyI = false;}
      if(lIeKInhZQt == true){lIeKInhZQt = false;}
      if(YqklqNyfnH == true){YqklqNyfnH = false;}
      if(rnRJOMDZmj == true){rnRJOMDZmj = false;}
      if(GFtUCLERmi == true){GFtUCLERmi = false;}
      if(ZAIsyAWbKy == true){ZAIsyAWbKy = false;}
      if(FeepQxpUuw == true){FeepQxpUuw = false;}
      if(kHmgmSxPjf == true){kHmgmSxPjf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UWJCVGYMAH
{ 
  void zbfoBUOXkh()
  { 
      bool eABKJeWHhs = false;
      bool eszStOzDMB = false;
      bool wDqGIPYQzN = false;
      bool BmCtyaSOcP = false;
      bool kdDGzCWzSN = false;
      bool koRAuaJuBt = false;
      bool FFIUqqpEUS = false;
      bool wkZwPSAjGG = false;
      bool rYxkbLUCyW = false;
      bool RWMiJeUhOI = false;
      bool LSeARzPVjc = false;
      bool aYntBfIWse = false;
      bool VnFxBYXpmk = false;
      bool xRVyuZtxTc = false;
      bool wzRVwriSgc = false;
      bool WyoilWMgyr = false;
      bool aYhzfJDpzb = false;
      bool lKCQiWWjBI = false;
      bool pFJKNyblLY = false;
      bool NNzbBXRSom = false;
      string sqhXNsyhkK;
      string loOHXopLOp;
      string TAZBlLrgyx;
      string fDcTTuBkMp;
      string twJRyLGlXb;
      string uKwTorQflB;
      string BQindiMtmc;
      string nFyXuWpHCZ;
      string EGJWBVGJda;
      string dUyKodNVnP;
      string zMytnpLXXS;
      string BJdLwtGMmH;
      string bCPLySGmhR;
      string JUSmarIOhL;
      string JhkLYUqmOu;
      string WAigmwxlwU;
      string iYpGJgpqkE;
      string lqdbytRDmc;
      string aTYmtIklzd;
      string uVSMbkrdBr;
      if(sqhXNsyhkK == zMytnpLXXS){eABKJeWHhs = true;}
      else if(zMytnpLXXS == sqhXNsyhkK){LSeARzPVjc = true;}
      if(loOHXopLOp == BJdLwtGMmH){eszStOzDMB = true;}
      else if(BJdLwtGMmH == loOHXopLOp){aYntBfIWse = true;}
      if(TAZBlLrgyx == bCPLySGmhR){wDqGIPYQzN = true;}
      else if(bCPLySGmhR == TAZBlLrgyx){VnFxBYXpmk = true;}
      if(fDcTTuBkMp == JUSmarIOhL){BmCtyaSOcP = true;}
      else if(JUSmarIOhL == fDcTTuBkMp){xRVyuZtxTc = true;}
      if(twJRyLGlXb == JhkLYUqmOu){kdDGzCWzSN = true;}
      else if(JhkLYUqmOu == twJRyLGlXb){wzRVwriSgc = true;}
      if(uKwTorQflB == WAigmwxlwU){koRAuaJuBt = true;}
      else if(WAigmwxlwU == uKwTorQflB){WyoilWMgyr = true;}
      if(BQindiMtmc == iYpGJgpqkE){FFIUqqpEUS = true;}
      else if(iYpGJgpqkE == BQindiMtmc){aYhzfJDpzb = true;}
      if(nFyXuWpHCZ == lqdbytRDmc){wkZwPSAjGG = true;}
      if(EGJWBVGJda == aTYmtIklzd){rYxkbLUCyW = true;}
      if(dUyKodNVnP == uVSMbkrdBr){RWMiJeUhOI = true;}
      while(lqdbytRDmc == nFyXuWpHCZ){lKCQiWWjBI = true;}
      while(aTYmtIklzd == aTYmtIklzd){pFJKNyblLY = true;}
      while(uVSMbkrdBr == uVSMbkrdBr){NNzbBXRSom = true;}
      if(eABKJeWHhs == true){eABKJeWHhs = false;}
      if(eszStOzDMB == true){eszStOzDMB = false;}
      if(wDqGIPYQzN == true){wDqGIPYQzN = false;}
      if(BmCtyaSOcP == true){BmCtyaSOcP = false;}
      if(kdDGzCWzSN == true){kdDGzCWzSN = false;}
      if(koRAuaJuBt == true){koRAuaJuBt = false;}
      if(FFIUqqpEUS == true){FFIUqqpEUS = false;}
      if(wkZwPSAjGG == true){wkZwPSAjGG = false;}
      if(rYxkbLUCyW == true){rYxkbLUCyW = false;}
      if(RWMiJeUhOI == true){RWMiJeUhOI = false;}
      if(LSeARzPVjc == true){LSeARzPVjc = false;}
      if(aYntBfIWse == true){aYntBfIWse = false;}
      if(VnFxBYXpmk == true){VnFxBYXpmk = false;}
      if(xRVyuZtxTc == true){xRVyuZtxTc = false;}
      if(wzRVwriSgc == true){wzRVwriSgc = false;}
      if(WyoilWMgyr == true){WyoilWMgyr = false;}
      if(aYhzfJDpzb == true){aYhzfJDpzb = false;}
      if(lKCQiWWjBI == true){lKCQiWWjBI = false;}
      if(pFJKNyblLY == true){pFJKNyblLY = false;}
      if(NNzbBXRSom == true){NNzbBXRSom = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSFESHGFBD
{ 
  void CENwEGazfs()
  { 
      bool EdkaEpMSux = false;
      bool UpLQzzjNZb = false;
      bool VNXghWhBTg = false;
      bool yHutJKeIdW = false;
      bool PAjkwCnsPE = false;
      bool BpgdjpFEsh = false;
      bool HLzNzMtRHn = false;
      bool TajDLUcmje = false;
      bool hokPfHaRKS = false;
      bool FaPwPEBWki = false;
      bool IWkajaGdRO = false;
      bool NRUNzRZjhq = false;
      bool lcGnisKnnH = false;
      bool TGBAWKDKeF = false;
      bool BwzuFmFBwx = false;
      bool dRntxePxrq = false;
      bool PSoKuGPUqn = false;
      bool NPEcpocLiu = false;
      bool mIqpdBRHDq = false;
      bool uGSnoiHozy = false;
      string qbPdNbfGQy;
      string CLMaGnTDul;
      string hAFtfSUTXn;
      string NqXgkIrhGV;
      string aeJXLigyoI;
      string DChsMpVVxu;
      string HLibjKnepy;
      string ukxZKCqhhx;
      string kVePkLIdUt;
      string lWjLOOwgmB;
      string uBIpMRFIiK;
      string znmAJkgSqY;
      string CKKuLYBkLu;
      string FJtgCiNnCT;
      string FAuJuyjjBc;
      string hcpOzjpMen;
      string QTwmEosGyZ;
      string XrPWSBPAAN;
      string nQjiMcTfhR;
      string rAJODkDHFF;
      if(qbPdNbfGQy == uBIpMRFIiK){EdkaEpMSux = true;}
      else if(uBIpMRFIiK == qbPdNbfGQy){IWkajaGdRO = true;}
      if(CLMaGnTDul == znmAJkgSqY){UpLQzzjNZb = true;}
      else if(znmAJkgSqY == CLMaGnTDul){NRUNzRZjhq = true;}
      if(hAFtfSUTXn == CKKuLYBkLu){VNXghWhBTg = true;}
      else if(CKKuLYBkLu == hAFtfSUTXn){lcGnisKnnH = true;}
      if(NqXgkIrhGV == FJtgCiNnCT){yHutJKeIdW = true;}
      else if(FJtgCiNnCT == NqXgkIrhGV){TGBAWKDKeF = true;}
      if(aeJXLigyoI == FAuJuyjjBc){PAjkwCnsPE = true;}
      else if(FAuJuyjjBc == aeJXLigyoI){BwzuFmFBwx = true;}
      if(DChsMpVVxu == hcpOzjpMen){BpgdjpFEsh = true;}
      else if(hcpOzjpMen == DChsMpVVxu){dRntxePxrq = true;}
      if(HLibjKnepy == QTwmEosGyZ){HLzNzMtRHn = true;}
      else if(QTwmEosGyZ == HLibjKnepy){PSoKuGPUqn = true;}
      if(ukxZKCqhhx == XrPWSBPAAN){TajDLUcmje = true;}
      if(kVePkLIdUt == nQjiMcTfhR){hokPfHaRKS = true;}
      if(lWjLOOwgmB == rAJODkDHFF){FaPwPEBWki = true;}
      while(XrPWSBPAAN == ukxZKCqhhx){NPEcpocLiu = true;}
      while(nQjiMcTfhR == nQjiMcTfhR){mIqpdBRHDq = true;}
      while(rAJODkDHFF == rAJODkDHFF){uGSnoiHozy = true;}
      if(EdkaEpMSux == true){EdkaEpMSux = false;}
      if(UpLQzzjNZb == true){UpLQzzjNZb = false;}
      if(VNXghWhBTg == true){VNXghWhBTg = false;}
      if(yHutJKeIdW == true){yHutJKeIdW = false;}
      if(PAjkwCnsPE == true){PAjkwCnsPE = false;}
      if(BpgdjpFEsh == true){BpgdjpFEsh = false;}
      if(HLzNzMtRHn == true){HLzNzMtRHn = false;}
      if(TajDLUcmje == true){TajDLUcmje = false;}
      if(hokPfHaRKS == true){hokPfHaRKS = false;}
      if(FaPwPEBWki == true){FaPwPEBWki = false;}
      if(IWkajaGdRO == true){IWkajaGdRO = false;}
      if(NRUNzRZjhq == true){NRUNzRZjhq = false;}
      if(lcGnisKnnH == true){lcGnisKnnH = false;}
      if(TGBAWKDKeF == true){TGBAWKDKeF = false;}
      if(BwzuFmFBwx == true){BwzuFmFBwx = false;}
      if(dRntxePxrq == true){dRntxePxrq = false;}
      if(PSoKuGPUqn == true){PSoKuGPUqn = false;}
      if(NPEcpocLiu == true){NPEcpocLiu = false;}
      if(mIqpdBRHDq == true){mIqpdBRHDq = false;}
      if(uGSnoiHozy == true){uGSnoiHozy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NULHMXJHVC
{ 
  void gGOQVbXAPN()
  { 
      bool rXAqsotRMu = false;
      bool jbmJEgMVJo = false;
      bool YEoOeIAkhx = false;
      bool cLOMGumfej = false;
      bool JKwobTcynu = false;
      bool QRbRXmhkMj = false;
      bool oJjOSYNaDJ = false;
      bool sgqZfOHAmK = false;
      bool eBxmgKiwnS = false;
      bool MBTttAahVD = false;
      bool FBueBjaClJ = false;
      bool fhyBEnMwhH = false;
      bool oQljwqMwee = false;
      bool mZdjFdFSlx = false;
      bool jfKdmeDRoG = false;
      bool ndAONnOLhJ = false;
      bool WdXGWGENwa = false;
      bool hsKkWJGIwR = false;
      bool ntGXqIZOWQ = false;
      bool OtjbZFHDHg = false;
      string NVOuZFToMY;
      string UTzWaiMENX;
      string bPikimuOjX;
      string tBbzFExEaQ;
      string caYIdqVYjb;
      string qFhBYxlcLl;
      string KEEneSrzQW;
      string kHdwuApaHr;
      string QWeIgoTZaH;
      string RTsnGXVkcK;
      string zWHNpiakFY;
      string HLVSVnZwHo;
      string zRXJEROppW;
      string dFxwrtOQRx;
      string OhUCzGxaSS;
      string yZcnLgyxIY;
      string UjthtCNZZa;
      string YIeKaQxVKy;
      string TmXXYEcJjL;
      string wQIsbdnlHx;
      if(NVOuZFToMY == zWHNpiakFY){rXAqsotRMu = true;}
      else if(zWHNpiakFY == NVOuZFToMY){FBueBjaClJ = true;}
      if(UTzWaiMENX == HLVSVnZwHo){jbmJEgMVJo = true;}
      else if(HLVSVnZwHo == UTzWaiMENX){fhyBEnMwhH = true;}
      if(bPikimuOjX == zRXJEROppW){YEoOeIAkhx = true;}
      else if(zRXJEROppW == bPikimuOjX){oQljwqMwee = true;}
      if(tBbzFExEaQ == dFxwrtOQRx){cLOMGumfej = true;}
      else if(dFxwrtOQRx == tBbzFExEaQ){mZdjFdFSlx = true;}
      if(caYIdqVYjb == OhUCzGxaSS){JKwobTcynu = true;}
      else if(OhUCzGxaSS == caYIdqVYjb){jfKdmeDRoG = true;}
      if(qFhBYxlcLl == yZcnLgyxIY){QRbRXmhkMj = true;}
      else if(yZcnLgyxIY == qFhBYxlcLl){ndAONnOLhJ = true;}
      if(KEEneSrzQW == UjthtCNZZa){oJjOSYNaDJ = true;}
      else if(UjthtCNZZa == KEEneSrzQW){WdXGWGENwa = true;}
      if(kHdwuApaHr == YIeKaQxVKy){sgqZfOHAmK = true;}
      if(QWeIgoTZaH == TmXXYEcJjL){eBxmgKiwnS = true;}
      if(RTsnGXVkcK == wQIsbdnlHx){MBTttAahVD = true;}
      while(YIeKaQxVKy == kHdwuApaHr){hsKkWJGIwR = true;}
      while(TmXXYEcJjL == TmXXYEcJjL){ntGXqIZOWQ = true;}
      while(wQIsbdnlHx == wQIsbdnlHx){OtjbZFHDHg = true;}
      if(rXAqsotRMu == true){rXAqsotRMu = false;}
      if(jbmJEgMVJo == true){jbmJEgMVJo = false;}
      if(YEoOeIAkhx == true){YEoOeIAkhx = false;}
      if(cLOMGumfej == true){cLOMGumfej = false;}
      if(JKwobTcynu == true){JKwobTcynu = false;}
      if(QRbRXmhkMj == true){QRbRXmhkMj = false;}
      if(oJjOSYNaDJ == true){oJjOSYNaDJ = false;}
      if(sgqZfOHAmK == true){sgqZfOHAmK = false;}
      if(eBxmgKiwnS == true){eBxmgKiwnS = false;}
      if(MBTttAahVD == true){MBTttAahVD = false;}
      if(FBueBjaClJ == true){FBueBjaClJ = false;}
      if(fhyBEnMwhH == true){fhyBEnMwhH = false;}
      if(oQljwqMwee == true){oQljwqMwee = false;}
      if(mZdjFdFSlx == true){mZdjFdFSlx = false;}
      if(jfKdmeDRoG == true){jfKdmeDRoG = false;}
      if(ndAONnOLhJ == true){ndAONnOLhJ = false;}
      if(WdXGWGENwa == true){WdXGWGENwa = false;}
      if(hsKkWJGIwR == true){hsKkWJGIwR = false;}
      if(ntGXqIZOWQ == true){ntGXqIZOWQ = false;}
      if(OtjbZFHDHg == true){OtjbZFHDHg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUKCNPDKDD
{ 
  void JQtAMndKRd()
  { 
      bool NiFcDpynCM = false;
      bool OuSZRAJHhd = false;
      bool gPzOhrCCNs = false;
      bool PahiOaeDoT = false;
      bool nZYiLpQkSB = false;
      bool dZiUNxjqtK = false;
      bool nuZIwmNjLp = false;
      bool VFROpHqPDr = false;
      bool aQjMPprMUQ = false;
      bool qmJefrAPmY = false;
      bool cgZbeXIUeG = false;
      bool GTnBjXKMsG = false;
      bool uAOuziulix = false;
      bool HacePtpIgr = false;
      bool gXhOKWzHuH = false;
      bool hmWgcbRecw = false;
      bool bVkgyeqJlo = false;
      bool gCeBYWRAjb = false;
      bool imqaPUEwBm = false;
      bool bLekPKlAPe = false;
      string nYOwdCBDho;
      string dozUMxkLNA;
      string exNSdIsaVW;
      string drTAuUalBz;
      string GUUFYiWrbo;
      string QelBypKuSU;
      string JZhLKkVyZr;
      string VzKNtKcHtu;
      string lAyfGzGRCE;
      string JfSfofmJun;
      string MXSjSRUYHn;
      string NDBXiJbBFL;
      string eEuUhpfdYO;
      string XSLFhOgNNn;
      string dgKOpFeuxe;
      string EkEjJIbxCc;
      string lpArPuruoU;
      string bNmQgxsgdb;
      string KkgsKlNbwZ;
      string ljLjCmgRyu;
      if(nYOwdCBDho == MXSjSRUYHn){NiFcDpynCM = true;}
      else if(MXSjSRUYHn == nYOwdCBDho){cgZbeXIUeG = true;}
      if(dozUMxkLNA == NDBXiJbBFL){OuSZRAJHhd = true;}
      else if(NDBXiJbBFL == dozUMxkLNA){GTnBjXKMsG = true;}
      if(exNSdIsaVW == eEuUhpfdYO){gPzOhrCCNs = true;}
      else if(eEuUhpfdYO == exNSdIsaVW){uAOuziulix = true;}
      if(drTAuUalBz == XSLFhOgNNn){PahiOaeDoT = true;}
      else if(XSLFhOgNNn == drTAuUalBz){HacePtpIgr = true;}
      if(GUUFYiWrbo == dgKOpFeuxe){nZYiLpQkSB = true;}
      else if(dgKOpFeuxe == GUUFYiWrbo){gXhOKWzHuH = true;}
      if(QelBypKuSU == EkEjJIbxCc){dZiUNxjqtK = true;}
      else if(EkEjJIbxCc == QelBypKuSU){hmWgcbRecw = true;}
      if(JZhLKkVyZr == lpArPuruoU){nuZIwmNjLp = true;}
      else if(lpArPuruoU == JZhLKkVyZr){bVkgyeqJlo = true;}
      if(VzKNtKcHtu == bNmQgxsgdb){VFROpHqPDr = true;}
      if(lAyfGzGRCE == KkgsKlNbwZ){aQjMPprMUQ = true;}
      if(JfSfofmJun == ljLjCmgRyu){qmJefrAPmY = true;}
      while(bNmQgxsgdb == VzKNtKcHtu){gCeBYWRAjb = true;}
      while(KkgsKlNbwZ == KkgsKlNbwZ){imqaPUEwBm = true;}
      while(ljLjCmgRyu == ljLjCmgRyu){bLekPKlAPe = true;}
      if(NiFcDpynCM == true){NiFcDpynCM = false;}
      if(OuSZRAJHhd == true){OuSZRAJHhd = false;}
      if(gPzOhrCCNs == true){gPzOhrCCNs = false;}
      if(PahiOaeDoT == true){PahiOaeDoT = false;}
      if(nZYiLpQkSB == true){nZYiLpQkSB = false;}
      if(dZiUNxjqtK == true){dZiUNxjqtK = false;}
      if(nuZIwmNjLp == true){nuZIwmNjLp = false;}
      if(VFROpHqPDr == true){VFROpHqPDr = false;}
      if(aQjMPprMUQ == true){aQjMPprMUQ = false;}
      if(qmJefrAPmY == true){qmJefrAPmY = false;}
      if(cgZbeXIUeG == true){cgZbeXIUeG = false;}
      if(GTnBjXKMsG == true){GTnBjXKMsG = false;}
      if(uAOuziulix == true){uAOuziulix = false;}
      if(HacePtpIgr == true){HacePtpIgr = false;}
      if(gXhOKWzHuH == true){gXhOKWzHuH = false;}
      if(hmWgcbRecw == true){hmWgcbRecw = false;}
      if(bVkgyeqJlo == true){bVkgyeqJlo = false;}
      if(gCeBYWRAjb == true){gCeBYWRAjb = false;}
      if(imqaPUEwBm == true){imqaPUEwBm = false;}
      if(bLekPKlAPe == true){bLekPKlAPe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TAGKPSNRUU
{ 
  void UFHLABxqSW()
  { 
      bool GsPiVlFglK = false;
      bool lJBzUwuehC = false;
      bool xORQPyphBl = false;
      bool AyDwJgwUdm = false;
      bool QAaUWZyhnJ = false;
      bool GAoVprayTW = false;
      bool uWfAKmGEpn = false;
      bool zaAulwmxto = false;
      bool AHtqeAIhFQ = false;
      bool FyAHqtUaJi = false;
      bool TsrzJeztjs = false;
      bool EcEdWnbnUK = false;
      bool eXzYhBZsDq = false;
      bool bMmLUHPuhz = false;
      bool AOxLMcsWjD = false;
      bool RgFzEusSRI = false;
      bool EGqrRqpsJO = false;
      bool XgGVJQamLF = false;
      bool HDIAZuHmGY = false;
      bool NwcYttWFtV = false;
      string UhyRNwLKUA;
      string VoGddIjBda;
      string ImHcAJocBX;
      string TZVqEbgzII;
      string NzGzaabPQm;
      string xeRCBhZVQD;
      string HhIwfwSPZB;
      string bkrUNJfIBZ;
      string hZMOaoHSoV;
      string BLhEBepJSe;
      string ILoOKLlxoq;
      string CRTqVhUtVq;
      string oAZDzQDmSh;
      string SVoVQVjxDO;
      string CJdxTiqpiS;
      string JwnapIlkPt;
      string IzeGYfcyZz;
      string xXqGoeVbjP;
      string ZMDzYVhNfI;
      string jzhIFCeWYn;
      if(UhyRNwLKUA == ILoOKLlxoq){GsPiVlFglK = true;}
      else if(ILoOKLlxoq == UhyRNwLKUA){TsrzJeztjs = true;}
      if(VoGddIjBda == CRTqVhUtVq){lJBzUwuehC = true;}
      else if(CRTqVhUtVq == VoGddIjBda){EcEdWnbnUK = true;}
      if(ImHcAJocBX == oAZDzQDmSh){xORQPyphBl = true;}
      else if(oAZDzQDmSh == ImHcAJocBX){eXzYhBZsDq = true;}
      if(TZVqEbgzII == SVoVQVjxDO){AyDwJgwUdm = true;}
      else if(SVoVQVjxDO == TZVqEbgzII){bMmLUHPuhz = true;}
      if(NzGzaabPQm == CJdxTiqpiS){QAaUWZyhnJ = true;}
      else if(CJdxTiqpiS == NzGzaabPQm){AOxLMcsWjD = true;}
      if(xeRCBhZVQD == JwnapIlkPt){GAoVprayTW = true;}
      else if(JwnapIlkPt == xeRCBhZVQD){RgFzEusSRI = true;}
      if(HhIwfwSPZB == IzeGYfcyZz){uWfAKmGEpn = true;}
      else if(IzeGYfcyZz == HhIwfwSPZB){EGqrRqpsJO = true;}
      if(bkrUNJfIBZ == xXqGoeVbjP){zaAulwmxto = true;}
      if(hZMOaoHSoV == ZMDzYVhNfI){AHtqeAIhFQ = true;}
      if(BLhEBepJSe == jzhIFCeWYn){FyAHqtUaJi = true;}
      while(xXqGoeVbjP == bkrUNJfIBZ){XgGVJQamLF = true;}
      while(ZMDzYVhNfI == ZMDzYVhNfI){HDIAZuHmGY = true;}
      while(jzhIFCeWYn == jzhIFCeWYn){NwcYttWFtV = true;}
      if(GsPiVlFglK == true){GsPiVlFglK = false;}
      if(lJBzUwuehC == true){lJBzUwuehC = false;}
      if(xORQPyphBl == true){xORQPyphBl = false;}
      if(AyDwJgwUdm == true){AyDwJgwUdm = false;}
      if(QAaUWZyhnJ == true){QAaUWZyhnJ = false;}
      if(GAoVprayTW == true){GAoVprayTW = false;}
      if(uWfAKmGEpn == true){uWfAKmGEpn = false;}
      if(zaAulwmxto == true){zaAulwmxto = false;}
      if(AHtqeAIhFQ == true){AHtqeAIhFQ = false;}
      if(FyAHqtUaJi == true){FyAHqtUaJi = false;}
      if(TsrzJeztjs == true){TsrzJeztjs = false;}
      if(EcEdWnbnUK == true){EcEdWnbnUK = false;}
      if(eXzYhBZsDq == true){eXzYhBZsDq = false;}
      if(bMmLUHPuhz == true){bMmLUHPuhz = false;}
      if(AOxLMcsWjD == true){AOxLMcsWjD = false;}
      if(RgFzEusSRI == true){RgFzEusSRI = false;}
      if(EGqrRqpsJO == true){EGqrRqpsJO = false;}
      if(XgGVJQamLF == true){XgGVJQamLF = false;}
      if(HDIAZuHmGY == true){HDIAZuHmGY = false;}
      if(NwcYttWFtV == true){NwcYttWFtV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUCKLURNDQ
{ 
  void udftYHHOfb()
  { 
      bool eOmDXZyilx = false;
      bool xSxDtNpPWz = false;
      bool cQcifVbbNe = false;
      bool updthzTuaR = false;
      bool JRaYHAENUn = false;
      bool PjJDOOkDXB = false;
      bool yWVHBGoDVt = false;
      bool ttnFoKoDbe = false;
      bool QOGYOLgaeS = false;
      bool NPXZTmwTXA = false;
      bool LBqZtVuDNE = false;
      bool YgarjiPwsp = false;
      bool YOYCfeWOlC = false;
      bool NVfaSPWges = false;
      bool PdMatgneoj = false;
      bool XAagbxbosO = false;
      bool zgQLpCBzZT = false;
      bool MiRzatBxIz = false;
      bool pqYCeNuzzV = false;
      bool mhmPthMBkr = false;
      string LatRxZGXRd;
      string SskjbVpetE;
      string dqTJpPkGAC;
      string HiEaWfOREt;
      string waCcocCFjr;
      string bSJhJTGjbg;
      string ozWOWjoJMu;
      string HXZAICnqUN;
      string MeWIanYVRC;
      string YdpXFwEmFE;
      string nrsnkDrJZG;
      string fPPOTJcOnh;
      string LSrJWchCtL;
      string yAkPZUliWX;
      string wPuKWJObDu;
      string TpzXsUAjQI;
      string UoOOHedznz;
      string XsqQkwWglN;
      string NGzzqIBNWE;
      string TCROCGAfDr;
      if(LatRxZGXRd == nrsnkDrJZG){eOmDXZyilx = true;}
      else if(nrsnkDrJZG == LatRxZGXRd){LBqZtVuDNE = true;}
      if(SskjbVpetE == fPPOTJcOnh){xSxDtNpPWz = true;}
      else if(fPPOTJcOnh == SskjbVpetE){YgarjiPwsp = true;}
      if(dqTJpPkGAC == LSrJWchCtL){cQcifVbbNe = true;}
      else if(LSrJWchCtL == dqTJpPkGAC){YOYCfeWOlC = true;}
      if(HiEaWfOREt == yAkPZUliWX){updthzTuaR = true;}
      else if(yAkPZUliWX == HiEaWfOREt){NVfaSPWges = true;}
      if(waCcocCFjr == wPuKWJObDu){JRaYHAENUn = true;}
      else if(wPuKWJObDu == waCcocCFjr){PdMatgneoj = true;}
      if(bSJhJTGjbg == TpzXsUAjQI){PjJDOOkDXB = true;}
      else if(TpzXsUAjQI == bSJhJTGjbg){XAagbxbosO = true;}
      if(ozWOWjoJMu == UoOOHedznz){yWVHBGoDVt = true;}
      else if(UoOOHedznz == ozWOWjoJMu){zgQLpCBzZT = true;}
      if(HXZAICnqUN == XsqQkwWglN){ttnFoKoDbe = true;}
      if(MeWIanYVRC == NGzzqIBNWE){QOGYOLgaeS = true;}
      if(YdpXFwEmFE == TCROCGAfDr){NPXZTmwTXA = true;}
      while(XsqQkwWglN == HXZAICnqUN){MiRzatBxIz = true;}
      while(NGzzqIBNWE == NGzzqIBNWE){pqYCeNuzzV = true;}
      while(TCROCGAfDr == TCROCGAfDr){mhmPthMBkr = true;}
      if(eOmDXZyilx == true){eOmDXZyilx = false;}
      if(xSxDtNpPWz == true){xSxDtNpPWz = false;}
      if(cQcifVbbNe == true){cQcifVbbNe = false;}
      if(updthzTuaR == true){updthzTuaR = false;}
      if(JRaYHAENUn == true){JRaYHAENUn = false;}
      if(PjJDOOkDXB == true){PjJDOOkDXB = false;}
      if(yWVHBGoDVt == true){yWVHBGoDVt = false;}
      if(ttnFoKoDbe == true){ttnFoKoDbe = false;}
      if(QOGYOLgaeS == true){QOGYOLgaeS = false;}
      if(NPXZTmwTXA == true){NPXZTmwTXA = false;}
      if(LBqZtVuDNE == true){LBqZtVuDNE = false;}
      if(YgarjiPwsp == true){YgarjiPwsp = false;}
      if(YOYCfeWOlC == true){YOYCfeWOlC = false;}
      if(NVfaSPWges == true){NVfaSPWges = false;}
      if(PdMatgneoj == true){PdMatgneoj = false;}
      if(XAagbxbosO == true){XAagbxbosO = false;}
      if(zgQLpCBzZT == true){zgQLpCBzZT = false;}
      if(MiRzatBxIz == true){MiRzatBxIz = false;}
      if(pqYCeNuzzV == true){pqYCeNuzzV = false;}
      if(mhmPthMBkr == true){mhmPthMBkr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JVHDOBHFXT
{ 
  void muTKMKKNTH()
  { 
      bool KcfnMzXhEW = false;
      bool oaBKLXithI = false;
      bool badtrWLEMI = false;
      bool BBmTJoQnPD = false;
      bool ktHVjZJLpQ = false;
      bool tzroBjykup = false;
      bool mSUwUmnhAV = false;
      bool GtddXgSIKR = false;
      bool NzOwNCJySZ = false;
      bool pesZPRZLAx = false;
      bool lbLUKzVNRT = false;
      bool QpadcmEXhS = false;
      bool cpOaeaBENF = false;
      bool GGIMelntlO = false;
      bool fwfyIAEOxb = false;
      bool NBdhTwMkoi = false;
      bool xRzLMJhNzq = false;
      bool zJlSlgJQRe = false;
      bool WmGlrFcZsh = false;
      bool YDECQOwUkz = false;
      string JdTZabisrQ;
      string xZwwBHbMky;
      string qmVuTytBbF;
      string dXEeTuGRPW;
      string xjgDEYbFDx;
      string cSKWLVHYFc;
      string ggRmlZURbF;
      string AJxOAGFSpt;
      string WnydbLMhSx;
      string mhLmoPStQe;
      string EJdxxSVwVE;
      string PohKFsinKa;
      string MmydSSyJYk;
      string nLBLpMKAgJ;
      string oQLOgyzAgu;
      string geioSQLzed;
      string ULWkQEmWUs;
      string ihHBkubjxU;
      string SxccDIbLrZ;
      string BLVCncsZxc;
      if(JdTZabisrQ == EJdxxSVwVE){KcfnMzXhEW = true;}
      else if(EJdxxSVwVE == JdTZabisrQ){lbLUKzVNRT = true;}
      if(xZwwBHbMky == PohKFsinKa){oaBKLXithI = true;}
      else if(PohKFsinKa == xZwwBHbMky){QpadcmEXhS = true;}
      if(qmVuTytBbF == MmydSSyJYk){badtrWLEMI = true;}
      else if(MmydSSyJYk == qmVuTytBbF){cpOaeaBENF = true;}
      if(dXEeTuGRPW == nLBLpMKAgJ){BBmTJoQnPD = true;}
      else if(nLBLpMKAgJ == dXEeTuGRPW){GGIMelntlO = true;}
      if(xjgDEYbFDx == oQLOgyzAgu){ktHVjZJLpQ = true;}
      else if(oQLOgyzAgu == xjgDEYbFDx){fwfyIAEOxb = true;}
      if(cSKWLVHYFc == geioSQLzed){tzroBjykup = true;}
      else if(geioSQLzed == cSKWLVHYFc){NBdhTwMkoi = true;}
      if(ggRmlZURbF == ULWkQEmWUs){mSUwUmnhAV = true;}
      else if(ULWkQEmWUs == ggRmlZURbF){xRzLMJhNzq = true;}
      if(AJxOAGFSpt == ihHBkubjxU){GtddXgSIKR = true;}
      if(WnydbLMhSx == SxccDIbLrZ){NzOwNCJySZ = true;}
      if(mhLmoPStQe == BLVCncsZxc){pesZPRZLAx = true;}
      while(ihHBkubjxU == AJxOAGFSpt){zJlSlgJQRe = true;}
      while(SxccDIbLrZ == SxccDIbLrZ){WmGlrFcZsh = true;}
      while(BLVCncsZxc == BLVCncsZxc){YDECQOwUkz = true;}
      if(KcfnMzXhEW == true){KcfnMzXhEW = false;}
      if(oaBKLXithI == true){oaBKLXithI = false;}
      if(badtrWLEMI == true){badtrWLEMI = false;}
      if(BBmTJoQnPD == true){BBmTJoQnPD = false;}
      if(ktHVjZJLpQ == true){ktHVjZJLpQ = false;}
      if(tzroBjykup == true){tzroBjykup = false;}
      if(mSUwUmnhAV == true){mSUwUmnhAV = false;}
      if(GtddXgSIKR == true){GtddXgSIKR = false;}
      if(NzOwNCJySZ == true){NzOwNCJySZ = false;}
      if(pesZPRZLAx == true){pesZPRZLAx = false;}
      if(lbLUKzVNRT == true){lbLUKzVNRT = false;}
      if(QpadcmEXhS == true){QpadcmEXhS = false;}
      if(cpOaeaBENF == true){cpOaeaBENF = false;}
      if(GGIMelntlO == true){GGIMelntlO = false;}
      if(fwfyIAEOxb == true){fwfyIAEOxb = false;}
      if(NBdhTwMkoi == true){NBdhTwMkoi = false;}
      if(xRzLMJhNzq == true){xRzLMJhNzq = false;}
      if(zJlSlgJQRe == true){zJlSlgJQRe = false;}
      if(WmGlrFcZsh == true){WmGlrFcZsh = false;}
      if(YDECQOwUkz == true){YDECQOwUkz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEQPVADTPB
{ 
  void WFcZiuBPRS()
  { 
      bool cMtxMpxFaH = false;
      bool bzyzQiWBrg = false;
      bool cQPTmocoQJ = false;
      bool PQZHERFgeP = false;
      bool ygUpjOLEkV = false;
      bool mmftZMxZJW = false;
      bool NHoRrLYquz = false;
      bool dpWchwuYjY = false;
      bool dYDuVcjfhr = false;
      bool UeWHCqrDxX = false;
      bool pUIlqxPDMc = false;
      bool QXpksnDtuP = false;
      bool asJDdyTOap = false;
      bool EraLhJQRDY = false;
      bool MgSEawnkON = false;
      bool myIhxxKFHs = false;
      bool dBcVYYxeDi = false;
      bool XlpVCsZFbh = false;
      bool KhzMDFirOk = false;
      bool yLJJuLExeC = false;
      string MmDHgqQCTm;
      string aHRtelIsqT;
      string nlQVrwRJJO;
      string PLxtVPgyzG;
      string zXoyNmbKTI;
      string SYgycZVgOj;
      string ZHrFWPKWYP;
      string FJsjUPxSIF;
      string TGoBwqdzQu;
      string szjPgqejax;
      string bFlDCIewcN;
      string cDYJPTSpIf;
      string kLFcWGZdDd;
      string jNqKcOTkzm;
      string LgWDSoaZzM;
      string XnauLQAJgw;
      string iBsycPMNfB;
      string AgqUTEnBKg;
      string ezdqGwlwyM;
      string NKECEKnXaC;
      if(MmDHgqQCTm == bFlDCIewcN){cMtxMpxFaH = true;}
      else if(bFlDCIewcN == MmDHgqQCTm){pUIlqxPDMc = true;}
      if(aHRtelIsqT == cDYJPTSpIf){bzyzQiWBrg = true;}
      else if(cDYJPTSpIf == aHRtelIsqT){QXpksnDtuP = true;}
      if(nlQVrwRJJO == kLFcWGZdDd){cQPTmocoQJ = true;}
      else if(kLFcWGZdDd == nlQVrwRJJO){asJDdyTOap = true;}
      if(PLxtVPgyzG == jNqKcOTkzm){PQZHERFgeP = true;}
      else if(jNqKcOTkzm == PLxtVPgyzG){EraLhJQRDY = true;}
      if(zXoyNmbKTI == LgWDSoaZzM){ygUpjOLEkV = true;}
      else if(LgWDSoaZzM == zXoyNmbKTI){MgSEawnkON = true;}
      if(SYgycZVgOj == XnauLQAJgw){mmftZMxZJW = true;}
      else if(XnauLQAJgw == SYgycZVgOj){myIhxxKFHs = true;}
      if(ZHrFWPKWYP == iBsycPMNfB){NHoRrLYquz = true;}
      else if(iBsycPMNfB == ZHrFWPKWYP){dBcVYYxeDi = true;}
      if(FJsjUPxSIF == AgqUTEnBKg){dpWchwuYjY = true;}
      if(TGoBwqdzQu == ezdqGwlwyM){dYDuVcjfhr = true;}
      if(szjPgqejax == NKECEKnXaC){UeWHCqrDxX = true;}
      while(AgqUTEnBKg == FJsjUPxSIF){XlpVCsZFbh = true;}
      while(ezdqGwlwyM == ezdqGwlwyM){KhzMDFirOk = true;}
      while(NKECEKnXaC == NKECEKnXaC){yLJJuLExeC = true;}
      if(cMtxMpxFaH == true){cMtxMpxFaH = false;}
      if(bzyzQiWBrg == true){bzyzQiWBrg = false;}
      if(cQPTmocoQJ == true){cQPTmocoQJ = false;}
      if(PQZHERFgeP == true){PQZHERFgeP = false;}
      if(ygUpjOLEkV == true){ygUpjOLEkV = false;}
      if(mmftZMxZJW == true){mmftZMxZJW = false;}
      if(NHoRrLYquz == true){NHoRrLYquz = false;}
      if(dpWchwuYjY == true){dpWchwuYjY = false;}
      if(dYDuVcjfhr == true){dYDuVcjfhr = false;}
      if(UeWHCqrDxX == true){UeWHCqrDxX = false;}
      if(pUIlqxPDMc == true){pUIlqxPDMc = false;}
      if(QXpksnDtuP == true){QXpksnDtuP = false;}
      if(asJDdyTOap == true){asJDdyTOap = false;}
      if(EraLhJQRDY == true){EraLhJQRDY = false;}
      if(MgSEawnkON == true){MgSEawnkON = false;}
      if(myIhxxKFHs == true){myIhxxKFHs = false;}
      if(dBcVYYxeDi == true){dBcVYYxeDi = false;}
      if(XlpVCsZFbh == true){XlpVCsZFbh = false;}
      if(KhzMDFirOk == true){KhzMDFirOk = false;}
      if(yLJJuLExeC == true){yLJJuLExeC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWXAAQOGCS
{ 
  void wrlhxHKpcC()
  { 
      bool ccSqRKIwTV = false;
      bool FnySBzRmec = false;
      bool LWwYBjVIOP = false;
      bool fpxpwoYqEV = false;
      bool fwkhxfEwKx = false;
      bool twlZTFfsog = false;
      bool ozgEoPpHVM = false;
      bool ZZhJwPkObV = false;
      bool eYyQUjDWWp = false;
      bool IfBWggOgrg = false;
      bool owZyXUNccE = false;
      bool URQTCPAPjF = false;
      bool LSkeDtXLbP = false;
      bool AEVugiyAsz = false;
      bool WatRVqOhUR = false;
      bool fzxmVVLutc = false;
      bool xBBMEPuVmS = false;
      bool QzVjhkYTIM = false;
      bool foqKjBHiZL = false;
      bool WDFQBUYhNG = false;
      string QgpcjrsTDj;
      string ibCKOPZPSd;
      string QxRNTreTZe;
      string mAXfLzyxfc;
      string MWjfcDdcnf;
      string IeYFcTObIq;
      string NYsYwiEWzP;
      string RbjoQtNkjP;
      string OCftVIaSCq;
      string jVnnPncLjt;
      string zHdXOfuini;
      string GdqsbKrzCn;
      string HlTHfunuZb;
      string RBBpQHXHep;
      string MrdTkFduME;
      string ucIulNmVrS;
      string rAILQEcBbU;
      string mkUMbPHzWZ;
      string RriVgnrFEC;
      string TCOLxMiRCf;
      if(QgpcjrsTDj == zHdXOfuini){ccSqRKIwTV = true;}
      else if(zHdXOfuini == QgpcjrsTDj){owZyXUNccE = true;}
      if(ibCKOPZPSd == GdqsbKrzCn){FnySBzRmec = true;}
      else if(GdqsbKrzCn == ibCKOPZPSd){URQTCPAPjF = true;}
      if(QxRNTreTZe == HlTHfunuZb){LWwYBjVIOP = true;}
      else if(HlTHfunuZb == QxRNTreTZe){LSkeDtXLbP = true;}
      if(mAXfLzyxfc == RBBpQHXHep){fpxpwoYqEV = true;}
      else if(RBBpQHXHep == mAXfLzyxfc){AEVugiyAsz = true;}
      if(MWjfcDdcnf == MrdTkFduME){fwkhxfEwKx = true;}
      else if(MrdTkFduME == MWjfcDdcnf){WatRVqOhUR = true;}
      if(IeYFcTObIq == ucIulNmVrS){twlZTFfsog = true;}
      else if(ucIulNmVrS == IeYFcTObIq){fzxmVVLutc = true;}
      if(NYsYwiEWzP == rAILQEcBbU){ozgEoPpHVM = true;}
      else if(rAILQEcBbU == NYsYwiEWzP){xBBMEPuVmS = true;}
      if(RbjoQtNkjP == mkUMbPHzWZ){ZZhJwPkObV = true;}
      if(OCftVIaSCq == RriVgnrFEC){eYyQUjDWWp = true;}
      if(jVnnPncLjt == TCOLxMiRCf){IfBWggOgrg = true;}
      while(mkUMbPHzWZ == RbjoQtNkjP){QzVjhkYTIM = true;}
      while(RriVgnrFEC == RriVgnrFEC){foqKjBHiZL = true;}
      while(TCOLxMiRCf == TCOLxMiRCf){WDFQBUYhNG = true;}
      if(ccSqRKIwTV == true){ccSqRKIwTV = false;}
      if(FnySBzRmec == true){FnySBzRmec = false;}
      if(LWwYBjVIOP == true){LWwYBjVIOP = false;}
      if(fpxpwoYqEV == true){fpxpwoYqEV = false;}
      if(fwkhxfEwKx == true){fwkhxfEwKx = false;}
      if(twlZTFfsog == true){twlZTFfsog = false;}
      if(ozgEoPpHVM == true){ozgEoPpHVM = false;}
      if(ZZhJwPkObV == true){ZZhJwPkObV = false;}
      if(eYyQUjDWWp == true){eYyQUjDWWp = false;}
      if(IfBWggOgrg == true){IfBWggOgrg = false;}
      if(owZyXUNccE == true){owZyXUNccE = false;}
      if(URQTCPAPjF == true){URQTCPAPjF = false;}
      if(LSkeDtXLbP == true){LSkeDtXLbP = false;}
      if(AEVugiyAsz == true){AEVugiyAsz = false;}
      if(WatRVqOhUR == true){WatRVqOhUR = false;}
      if(fzxmVVLutc == true){fzxmVVLutc = false;}
      if(xBBMEPuVmS == true){xBBMEPuVmS = false;}
      if(QzVjhkYTIM == true){QzVjhkYTIM = false;}
      if(foqKjBHiZL == true){foqKjBHiZL = false;}
      if(WDFQBUYhNG == true){WDFQBUYhNG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JAETBQBMPE
{ 
  void dayhgHXDUB()
  { 
      bool GWScWVHthD = false;
      bool bzmJEktOay = false;
      bool nTGtXJbWxq = false;
      bool jaOiCqiZIu = false;
      bool yMLcZBDAjD = false;
      bool nMGbklQXEN = false;
      bool sjwqTAjEHN = false;
      bool BUGfAaIcUW = false;
      bool GblsCWUlyQ = false;
      bool ZLUtBNPTJY = false;
      bool QzrWCTGabJ = false;
      bool cnChHQyCox = false;
      bool eyFpmozLdl = false;
      bool KnTuFGjPqi = false;
      bool QsJnmlIlmk = false;
      bool PNeLtSsBiN = false;
      bool TuwpyoTHcA = false;
      bool ghLFgknRDB = false;
      bool fMXsVxIHBm = false;
      bool NhgdOUxToy = false;
      string bGHzFnYjku;
      string KnkllpzxBH;
      string aPWfIqzkNs;
      string FPJEMVVmct;
      string KLjEoAqtMM;
      string PVBPsMiapN;
      string omWqptdfZP;
      string TMTGxOeRqI;
      string AEYBdiOsKz;
      string luwPFWosOt;
      string VKUwrCCtSe;
      string gRjhNjOUMG;
      string fkVZdYPEAZ;
      string ZlCwlojbIa;
      string gUafSUKNBV;
      string ITfIOkotSS;
      string mxsrEtOmuY;
      string zlMlZKJoHI;
      string NBDeRFGtgB;
      string ApJoniahaY;
      if(bGHzFnYjku == VKUwrCCtSe){GWScWVHthD = true;}
      else if(VKUwrCCtSe == bGHzFnYjku){QzrWCTGabJ = true;}
      if(KnkllpzxBH == gRjhNjOUMG){bzmJEktOay = true;}
      else if(gRjhNjOUMG == KnkllpzxBH){cnChHQyCox = true;}
      if(aPWfIqzkNs == fkVZdYPEAZ){nTGtXJbWxq = true;}
      else if(fkVZdYPEAZ == aPWfIqzkNs){eyFpmozLdl = true;}
      if(FPJEMVVmct == ZlCwlojbIa){jaOiCqiZIu = true;}
      else if(ZlCwlojbIa == FPJEMVVmct){KnTuFGjPqi = true;}
      if(KLjEoAqtMM == gUafSUKNBV){yMLcZBDAjD = true;}
      else if(gUafSUKNBV == KLjEoAqtMM){QsJnmlIlmk = true;}
      if(PVBPsMiapN == ITfIOkotSS){nMGbklQXEN = true;}
      else if(ITfIOkotSS == PVBPsMiapN){PNeLtSsBiN = true;}
      if(omWqptdfZP == mxsrEtOmuY){sjwqTAjEHN = true;}
      else if(mxsrEtOmuY == omWqptdfZP){TuwpyoTHcA = true;}
      if(TMTGxOeRqI == zlMlZKJoHI){BUGfAaIcUW = true;}
      if(AEYBdiOsKz == NBDeRFGtgB){GblsCWUlyQ = true;}
      if(luwPFWosOt == ApJoniahaY){ZLUtBNPTJY = true;}
      while(zlMlZKJoHI == TMTGxOeRqI){ghLFgknRDB = true;}
      while(NBDeRFGtgB == NBDeRFGtgB){fMXsVxIHBm = true;}
      while(ApJoniahaY == ApJoniahaY){NhgdOUxToy = true;}
      if(GWScWVHthD == true){GWScWVHthD = false;}
      if(bzmJEktOay == true){bzmJEktOay = false;}
      if(nTGtXJbWxq == true){nTGtXJbWxq = false;}
      if(jaOiCqiZIu == true){jaOiCqiZIu = false;}
      if(yMLcZBDAjD == true){yMLcZBDAjD = false;}
      if(nMGbklQXEN == true){nMGbklQXEN = false;}
      if(sjwqTAjEHN == true){sjwqTAjEHN = false;}
      if(BUGfAaIcUW == true){BUGfAaIcUW = false;}
      if(GblsCWUlyQ == true){GblsCWUlyQ = false;}
      if(ZLUtBNPTJY == true){ZLUtBNPTJY = false;}
      if(QzrWCTGabJ == true){QzrWCTGabJ = false;}
      if(cnChHQyCox == true){cnChHQyCox = false;}
      if(eyFpmozLdl == true){eyFpmozLdl = false;}
      if(KnTuFGjPqi == true){KnTuFGjPqi = false;}
      if(QsJnmlIlmk == true){QsJnmlIlmk = false;}
      if(PNeLtSsBiN == true){PNeLtSsBiN = false;}
      if(TuwpyoTHcA == true){TuwpyoTHcA = false;}
      if(ghLFgknRDB == true){ghLFgknRDB = false;}
      if(fMXsVxIHBm == true){fMXsVxIHBm = false;}
      if(NhgdOUxToy == true){NhgdOUxToy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWQKIKXNDJ
{ 
  void LxybhAVJqn()
  { 
      bool VFGQHDGQKy = false;
      bool zYyaBVwNDR = false;
      bool zXkRYaAHaD = false;
      bool LIQxAuuCLs = false;
      bool cwsrTSGlyh = false;
      bool mBDFZxUorg = false;
      bool CypGmpHBaG = false;
      bool ZsCJnCerxF = false;
      bool UOJrPJFLWC = false;
      bool ZGKeqeGmEc = false;
      bool KELqHtzsRX = false;
      bool SbqlMnnyqd = false;
      bool kwdXgTiXSI = false;
      bool uqmUtPDRjV = false;
      bool KMszixOXRC = false;
      bool pIuarOamKm = false;
      bool KaZIbanVqx = false;
      bool kVNUTXCdni = false;
      bool FKFPRmwMcf = false;
      bool nPHwKiljWH = false;
      string rEikyZGhIy;
      string jifKBwxOLB;
      string sLiYzuJAjK;
      string qapspAkuIK;
      string wWAsIeNAUw;
      string SYoTVgUJlD;
      string PFyyGJslTB;
      string KCGAEVKoPT;
      string gIfnrSkVXI;
      string ebJEtpYBly;
      string lbgTkQRnOz;
      string VfsRWHZKGn;
      string YWNKVirBGN;
      string xJCRhFbLCb;
      string AxHYmzhqhm;
      string QNuyZONWyC;
      string XQgABMcbjQ;
      string fNHemaPoXW;
      string ABTSwjNEqS;
      string rENzEjPGXZ;
      if(rEikyZGhIy == lbgTkQRnOz){VFGQHDGQKy = true;}
      else if(lbgTkQRnOz == rEikyZGhIy){KELqHtzsRX = true;}
      if(jifKBwxOLB == VfsRWHZKGn){zYyaBVwNDR = true;}
      else if(VfsRWHZKGn == jifKBwxOLB){SbqlMnnyqd = true;}
      if(sLiYzuJAjK == YWNKVirBGN){zXkRYaAHaD = true;}
      else if(YWNKVirBGN == sLiYzuJAjK){kwdXgTiXSI = true;}
      if(qapspAkuIK == xJCRhFbLCb){LIQxAuuCLs = true;}
      else if(xJCRhFbLCb == qapspAkuIK){uqmUtPDRjV = true;}
      if(wWAsIeNAUw == AxHYmzhqhm){cwsrTSGlyh = true;}
      else if(AxHYmzhqhm == wWAsIeNAUw){KMszixOXRC = true;}
      if(SYoTVgUJlD == QNuyZONWyC){mBDFZxUorg = true;}
      else if(QNuyZONWyC == SYoTVgUJlD){pIuarOamKm = true;}
      if(PFyyGJslTB == XQgABMcbjQ){CypGmpHBaG = true;}
      else if(XQgABMcbjQ == PFyyGJslTB){KaZIbanVqx = true;}
      if(KCGAEVKoPT == fNHemaPoXW){ZsCJnCerxF = true;}
      if(gIfnrSkVXI == ABTSwjNEqS){UOJrPJFLWC = true;}
      if(ebJEtpYBly == rENzEjPGXZ){ZGKeqeGmEc = true;}
      while(fNHemaPoXW == KCGAEVKoPT){kVNUTXCdni = true;}
      while(ABTSwjNEqS == ABTSwjNEqS){FKFPRmwMcf = true;}
      while(rENzEjPGXZ == rENzEjPGXZ){nPHwKiljWH = true;}
      if(VFGQHDGQKy == true){VFGQHDGQKy = false;}
      if(zYyaBVwNDR == true){zYyaBVwNDR = false;}
      if(zXkRYaAHaD == true){zXkRYaAHaD = false;}
      if(LIQxAuuCLs == true){LIQxAuuCLs = false;}
      if(cwsrTSGlyh == true){cwsrTSGlyh = false;}
      if(mBDFZxUorg == true){mBDFZxUorg = false;}
      if(CypGmpHBaG == true){CypGmpHBaG = false;}
      if(ZsCJnCerxF == true){ZsCJnCerxF = false;}
      if(UOJrPJFLWC == true){UOJrPJFLWC = false;}
      if(ZGKeqeGmEc == true){ZGKeqeGmEc = false;}
      if(KELqHtzsRX == true){KELqHtzsRX = false;}
      if(SbqlMnnyqd == true){SbqlMnnyqd = false;}
      if(kwdXgTiXSI == true){kwdXgTiXSI = false;}
      if(uqmUtPDRjV == true){uqmUtPDRjV = false;}
      if(KMszixOXRC == true){KMszixOXRC = false;}
      if(pIuarOamKm == true){pIuarOamKm = false;}
      if(KaZIbanVqx == true){KaZIbanVqx = false;}
      if(kVNUTXCdni == true){kVNUTXCdni = false;}
      if(FKFPRmwMcf == true){FKFPRmwMcf = false;}
      if(nPHwKiljWH == true){nPHwKiljWH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPTJCUCNCT
{ 
  void xPZibaxxYI()
  { 
      bool YruhxCyLsm = false;
      bool QTdCTQNNRX = false;
      bool gHbOQkkMes = false;
      bool VMsIWHewoj = false;
      bool DmxfOwQFNQ = false;
      bool edVToRQfQL = false;
      bool QkfzQEZUeL = false;
      bool kQYgUsKuAU = false;
      bool UfyOOrqZTF = false;
      bool qzecTRGxPJ = false;
      bool VuaBfNEnyu = false;
      bool HUeuqjlRkY = false;
      bool MABYTlkwNC = false;
      bool mMfpyYFxiA = false;
      bool mCaXyWTikj = false;
      bool enLqxVsBgs = false;
      bool bIawHtonxR = false;
      bool doijkKYdax = false;
      bool RBKcXzBnsc = false;
      bool eEPoXeaePD = false;
      string ezkpDrUGzM;
      string LQZQjgfLPx;
      string YAMtoXPxDj;
      string Uyslhcrhyn;
      string TqVqTgtXYu;
      string FzqPBempAf;
      string bXDOqMWmiH;
      string oyMbchdUaI;
      string crXHeVHdkC;
      string oChSMunHAG;
      string KHoRGGlPlT;
      string BSOrDizujU;
      string FrCfSmQtPh;
      string tVUTxVDGBX;
      string jrrQBWmpPc;
      string urXeARFIyT;
      string pqAEZexutg;
      string fstLkNAkew;
      string zZdllBypSe;
      string QtHggrqmqV;
      if(ezkpDrUGzM == KHoRGGlPlT){YruhxCyLsm = true;}
      else if(KHoRGGlPlT == ezkpDrUGzM){VuaBfNEnyu = true;}
      if(LQZQjgfLPx == BSOrDizujU){QTdCTQNNRX = true;}
      else if(BSOrDizujU == LQZQjgfLPx){HUeuqjlRkY = true;}
      if(YAMtoXPxDj == FrCfSmQtPh){gHbOQkkMes = true;}
      else if(FrCfSmQtPh == YAMtoXPxDj){MABYTlkwNC = true;}
      if(Uyslhcrhyn == tVUTxVDGBX){VMsIWHewoj = true;}
      else if(tVUTxVDGBX == Uyslhcrhyn){mMfpyYFxiA = true;}
      if(TqVqTgtXYu == jrrQBWmpPc){DmxfOwQFNQ = true;}
      else if(jrrQBWmpPc == TqVqTgtXYu){mCaXyWTikj = true;}
      if(FzqPBempAf == urXeARFIyT){edVToRQfQL = true;}
      else if(urXeARFIyT == FzqPBempAf){enLqxVsBgs = true;}
      if(bXDOqMWmiH == pqAEZexutg){QkfzQEZUeL = true;}
      else if(pqAEZexutg == bXDOqMWmiH){bIawHtonxR = true;}
      if(oyMbchdUaI == fstLkNAkew){kQYgUsKuAU = true;}
      if(crXHeVHdkC == zZdllBypSe){UfyOOrqZTF = true;}
      if(oChSMunHAG == QtHggrqmqV){qzecTRGxPJ = true;}
      while(fstLkNAkew == oyMbchdUaI){doijkKYdax = true;}
      while(zZdllBypSe == zZdllBypSe){RBKcXzBnsc = true;}
      while(QtHggrqmqV == QtHggrqmqV){eEPoXeaePD = true;}
      if(YruhxCyLsm == true){YruhxCyLsm = false;}
      if(QTdCTQNNRX == true){QTdCTQNNRX = false;}
      if(gHbOQkkMes == true){gHbOQkkMes = false;}
      if(VMsIWHewoj == true){VMsIWHewoj = false;}
      if(DmxfOwQFNQ == true){DmxfOwQFNQ = false;}
      if(edVToRQfQL == true){edVToRQfQL = false;}
      if(QkfzQEZUeL == true){QkfzQEZUeL = false;}
      if(kQYgUsKuAU == true){kQYgUsKuAU = false;}
      if(UfyOOrqZTF == true){UfyOOrqZTF = false;}
      if(qzecTRGxPJ == true){qzecTRGxPJ = false;}
      if(VuaBfNEnyu == true){VuaBfNEnyu = false;}
      if(HUeuqjlRkY == true){HUeuqjlRkY = false;}
      if(MABYTlkwNC == true){MABYTlkwNC = false;}
      if(mMfpyYFxiA == true){mMfpyYFxiA = false;}
      if(mCaXyWTikj == true){mCaXyWTikj = false;}
      if(enLqxVsBgs == true){enLqxVsBgs = false;}
      if(bIawHtonxR == true){bIawHtonxR = false;}
      if(doijkKYdax == true){doijkKYdax = false;}
      if(RBKcXzBnsc == true){RBKcXzBnsc = false;}
      if(eEPoXeaePD == true){eEPoXeaePD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHVDTOAMCR
{ 
  void ernnenGzxd()
  { 
      bool WyfEZLcBTQ = false;
      bool mpJCcnTUAS = false;
      bool swzrZaRoPx = false;
      bool BjrIRCRsuY = false;
      bool fRLtewfJuf = false;
      bool XseWVZymey = false;
      bool tmlVPCyBkZ = false;
      bool VZZblbjFNc = false;
      bool uHsiZHEVlq = false;
      bool DdOwdsepeb = false;
      bool ydYVJyTDkt = false;
      bool osZBDmsCwH = false;
      bool xbOsVqLcxs = false;
      bool wtZkeQhXZb = false;
      bool nBkrBKEMsq = false;
      bool zctXdVOfzR = false;
      bool lpFqxuSoWl = false;
      bool EVcUSwqWqL = false;
      bool myjGsTACGI = false;
      bool BCXHoxustG = false;
      string ibFgKPeJlf;
      string cwWkpSNHNk;
      string ZhIPxBZPAO;
      string jCmdskzEAV;
      string lQAHZrQWiI;
      string hptKjATpjJ;
      string pOIWuaIrqE;
      string TIGryIhBoE;
      string jCgqftHcss;
      string RJUpeXIcLz;
      string iXedoZiCLb;
      string RSAeYngQqB;
      string TfzymKmQMa;
      string AFppULWDCG;
      string KEQQazIpRq;
      string pqlJeCYgpd;
      string lSpkbMbKKM;
      string QdNjpOPhWn;
      string BxyUjJSfKR;
      string mpMYUrNeoO;
      if(ibFgKPeJlf == iXedoZiCLb){WyfEZLcBTQ = true;}
      else if(iXedoZiCLb == ibFgKPeJlf){ydYVJyTDkt = true;}
      if(cwWkpSNHNk == RSAeYngQqB){mpJCcnTUAS = true;}
      else if(RSAeYngQqB == cwWkpSNHNk){osZBDmsCwH = true;}
      if(ZhIPxBZPAO == TfzymKmQMa){swzrZaRoPx = true;}
      else if(TfzymKmQMa == ZhIPxBZPAO){xbOsVqLcxs = true;}
      if(jCmdskzEAV == AFppULWDCG){BjrIRCRsuY = true;}
      else if(AFppULWDCG == jCmdskzEAV){wtZkeQhXZb = true;}
      if(lQAHZrQWiI == KEQQazIpRq){fRLtewfJuf = true;}
      else if(KEQQazIpRq == lQAHZrQWiI){nBkrBKEMsq = true;}
      if(hptKjATpjJ == pqlJeCYgpd){XseWVZymey = true;}
      else if(pqlJeCYgpd == hptKjATpjJ){zctXdVOfzR = true;}
      if(pOIWuaIrqE == lSpkbMbKKM){tmlVPCyBkZ = true;}
      else if(lSpkbMbKKM == pOIWuaIrqE){lpFqxuSoWl = true;}
      if(TIGryIhBoE == QdNjpOPhWn){VZZblbjFNc = true;}
      if(jCgqftHcss == BxyUjJSfKR){uHsiZHEVlq = true;}
      if(RJUpeXIcLz == mpMYUrNeoO){DdOwdsepeb = true;}
      while(QdNjpOPhWn == TIGryIhBoE){EVcUSwqWqL = true;}
      while(BxyUjJSfKR == BxyUjJSfKR){myjGsTACGI = true;}
      while(mpMYUrNeoO == mpMYUrNeoO){BCXHoxustG = true;}
      if(WyfEZLcBTQ == true){WyfEZLcBTQ = false;}
      if(mpJCcnTUAS == true){mpJCcnTUAS = false;}
      if(swzrZaRoPx == true){swzrZaRoPx = false;}
      if(BjrIRCRsuY == true){BjrIRCRsuY = false;}
      if(fRLtewfJuf == true){fRLtewfJuf = false;}
      if(XseWVZymey == true){XseWVZymey = false;}
      if(tmlVPCyBkZ == true){tmlVPCyBkZ = false;}
      if(VZZblbjFNc == true){VZZblbjFNc = false;}
      if(uHsiZHEVlq == true){uHsiZHEVlq = false;}
      if(DdOwdsepeb == true){DdOwdsepeb = false;}
      if(ydYVJyTDkt == true){ydYVJyTDkt = false;}
      if(osZBDmsCwH == true){osZBDmsCwH = false;}
      if(xbOsVqLcxs == true){xbOsVqLcxs = false;}
      if(wtZkeQhXZb == true){wtZkeQhXZb = false;}
      if(nBkrBKEMsq == true){nBkrBKEMsq = false;}
      if(zctXdVOfzR == true){zctXdVOfzR = false;}
      if(lpFqxuSoWl == true){lpFqxuSoWl = false;}
      if(EVcUSwqWqL == true){EVcUSwqWqL = false;}
      if(myjGsTACGI == true){myjGsTACGI = false;}
      if(BCXHoxustG == true){BCXHoxustG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SRQKMTINWP
{ 
  void skKzjipnKk()
  { 
      bool JExJPVQkWR = false;
      bool DkwmsIlftD = false;
      bool oLbLymMbpj = false;
      bool RHdajFwfsO = false;
      bool QyxEIffngU = false;
      bool eZyiaxbkKb = false;
      bool IotmzuHVCm = false;
      bool LFmflqOWDS = false;
      bool GYtUEqItAm = false;
      bool cKVQFbDKEN = false;
      bool XKltIYmSxi = false;
      bool iFhqVjtYhI = false;
      bool lNUPJAjVZK = false;
      bool nESotulALf = false;
      bool EpwQDXcduV = false;
      bool gdcwaKoVjH = false;
      bool oQrmuelrxZ = false;
      bool xtMBDwQELk = false;
      bool XFZEcJbVOj = false;
      bool FQPEqmyJVY = false;
      string zYERENMGod;
      string EsBmgPOknn;
      string WuwZlGrmhp;
      string CIZzFmqoJj;
      string iWDqEutELo;
      string rShdmDbeex;
      string VZYybuTBht;
      string YZaDEArFUq;
      string MmasyiawLB;
      string KLJLOJyEOJ;
      string arVQPRqeYm;
      string LVJnkhyeAr;
      string TXogiMPPot;
      string BmpLPURJcf;
      string rwWYooCVZf;
      string KSEWoDCnhD;
      string CaodlYeyXQ;
      string QoBTAXAQrt;
      string KtoIjhiTVL;
      string RcbZdQGsmQ;
      if(zYERENMGod == arVQPRqeYm){JExJPVQkWR = true;}
      else if(arVQPRqeYm == zYERENMGod){XKltIYmSxi = true;}
      if(EsBmgPOknn == LVJnkhyeAr){DkwmsIlftD = true;}
      else if(LVJnkhyeAr == EsBmgPOknn){iFhqVjtYhI = true;}
      if(WuwZlGrmhp == TXogiMPPot){oLbLymMbpj = true;}
      else if(TXogiMPPot == WuwZlGrmhp){lNUPJAjVZK = true;}
      if(CIZzFmqoJj == BmpLPURJcf){RHdajFwfsO = true;}
      else if(BmpLPURJcf == CIZzFmqoJj){nESotulALf = true;}
      if(iWDqEutELo == rwWYooCVZf){QyxEIffngU = true;}
      else if(rwWYooCVZf == iWDqEutELo){EpwQDXcduV = true;}
      if(rShdmDbeex == KSEWoDCnhD){eZyiaxbkKb = true;}
      else if(KSEWoDCnhD == rShdmDbeex){gdcwaKoVjH = true;}
      if(VZYybuTBht == CaodlYeyXQ){IotmzuHVCm = true;}
      else if(CaodlYeyXQ == VZYybuTBht){oQrmuelrxZ = true;}
      if(YZaDEArFUq == QoBTAXAQrt){LFmflqOWDS = true;}
      if(MmasyiawLB == KtoIjhiTVL){GYtUEqItAm = true;}
      if(KLJLOJyEOJ == RcbZdQGsmQ){cKVQFbDKEN = true;}
      while(QoBTAXAQrt == YZaDEArFUq){xtMBDwQELk = true;}
      while(KtoIjhiTVL == KtoIjhiTVL){XFZEcJbVOj = true;}
      while(RcbZdQGsmQ == RcbZdQGsmQ){FQPEqmyJVY = true;}
      if(JExJPVQkWR == true){JExJPVQkWR = false;}
      if(DkwmsIlftD == true){DkwmsIlftD = false;}
      if(oLbLymMbpj == true){oLbLymMbpj = false;}
      if(RHdajFwfsO == true){RHdajFwfsO = false;}
      if(QyxEIffngU == true){QyxEIffngU = false;}
      if(eZyiaxbkKb == true){eZyiaxbkKb = false;}
      if(IotmzuHVCm == true){IotmzuHVCm = false;}
      if(LFmflqOWDS == true){LFmflqOWDS = false;}
      if(GYtUEqItAm == true){GYtUEqItAm = false;}
      if(cKVQFbDKEN == true){cKVQFbDKEN = false;}
      if(XKltIYmSxi == true){XKltIYmSxi = false;}
      if(iFhqVjtYhI == true){iFhqVjtYhI = false;}
      if(lNUPJAjVZK == true){lNUPJAjVZK = false;}
      if(nESotulALf == true){nESotulALf = false;}
      if(EpwQDXcduV == true){EpwQDXcduV = false;}
      if(gdcwaKoVjH == true){gdcwaKoVjH = false;}
      if(oQrmuelrxZ == true){oQrmuelrxZ = false;}
      if(xtMBDwQELk == true){xtMBDwQELk = false;}
      if(XFZEcJbVOj == true){XFZEcJbVOj = false;}
      if(FQPEqmyJVY == true){FQPEqmyJVY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELGNEFEEVI
{ 
  void KnthUmSmmC()
  { 
      bool PPtWjPCjrU = false;
      bool YnpKYMlQpG = false;
      bool wXRJsJbsLW = false;
      bool GdHMQLbfZn = false;
      bool GhjgTyHJos = false;
      bool iOODUrxjdZ = false;
      bool mJXVOtgdsM = false;
      bool kFpCANmkpu = false;
      bool CRDSmqPDqY = false;
      bool OrBzAxJOSY = false;
      bool QcPcIcYMCH = false;
      bool EMsiXVFFhW = false;
      bool eclUysEpCD = false;
      bool EXSRdYBaJJ = false;
      bool SCAjTCySbd = false;
      bool qEgusmqudP = false;
      bool YhKzCfsbEz = false;
      bool TeuXEccCBw = false;
      bool tlOXLAqWXq = false;
      bool gGwtkkrBgn = false;
      string yKfLHUOAFq;
      string FnnASaHaAH;
      string TkwpTqzKGH;
      string hbzmbrCprj;
      string XXGuedzCMi;
      string RcrreNOoqQ;
      string UEsxIcoAYZ;
      string XQhPiwdALo;
      string rwxXpFiHIO;
      string dNybPTdJmB;
      string oydlKBubIh;
      string iNdCYYHUHC;
      string tgrJwKRFAP;
      string RUNJAsRKNo;
      string KHyZfPiwCp;
      string LJCjHHGUpz;
      string ioasPOATCf;
      string GwGRrliRdf;
      string aVDKDIRcCr;
      string lxUNGVfEKR;
      if(yKfLHUOAFq == oydlKBubIh){PPtWjPCjrU = true;}
      else if(oydlKBubIh == yKfLHUOAFq){QcPcIcYMCH = true;}
      if(FnnASaHaAH == iNdCYYHUHC){YnpKYMlQpG = true;}
      else if(iNdCYYHUHC == FnnASaHaAH){EMsiXVFFhW = true;}
      if(TkwpTqzKGH == tgrJwKRFAP){wXRJsJbsLW = true;}
      else if(tgrJwKRFAP == TkwpTqzKGH){eclUysEpCD = true;}
      if(hbzmbrCprj == RUNJAsRKNo){GdHMQLbfZn = true;}
      else if(RUNJAsRKNo == hbzmbrCprj){EXSRdYBaJJ = true;}
      if(XXGuedzCMi == KHyZfPiwCp){GhjgTyHJos = true;}
      else if(KHyZfPiwCp == XXGuedzCMi){SCAjTCySbd = true;}
      if(RcrreNOoqQ == LJCjHHGUpz){iOODUrxjdZ = true;}
      else if(LJCjHHGUpz == RcrreNOoqQ){qEgusmqudP = true;}
      if(UEsxIcoAYZ == ioasPOATCf){mJXVOtgdsM = true;}
      else if(ioasPOATCf == UEsxIcoAYZ){YhKzCfsbEz = true;}
      if(XQhPiwdALo == GwGRrliRdf){kFpCANmkpu = true;}
      if(rwxXpFiHIO == aVDKDIRcCr){CRDSmqPDqY = true;}
      if(dNybPTdJmB == lxUNGVfEKR){OrBzAxJOSY = true;}
      while(GwGRrliRdf == XQhPiwdALo){TeuXEccCBw = true;}
      while(aVDKDIRcCr == aVDKDIRcCr){tlOXLAqWXq = true;}
      while(lxUNGVfEKR == lxUNGVfEKR){gGwtkkrBgn = true;}
      if(PPtWjPCjrU == true){PPtWjPCjrU = false;}
      if(YnpKYMlQpG == true){YnpKYMlQpG = false;}
      if(wXRJsJbsLW == true){wXRJsJbsLW = false;}
      if(GdHMQLbfZn == true){GdHMQLbfZn = false;}
      if(GhjgTyHJos == true){GhjgTyHJos = false;}
      if(iOODUrxjdZ == true){iOODUrxjdZ = false;}
      if(mJXVOtgdsM == true){mJXVOtgdsM = false;}
      if(kFpCANmkpu == true){kFpCANmkpu = false;}
      if(CRDSmqPDqY == true){CRDSmqPDqY = false;}
      if(OrBzAxJOSY == true){OrBzAxJOSY = false;}
      if(QcPcIcYMCH == true){QcPcIcYMCH = false;}
      if(EMsiXVFFhW == true){EMsiXVFFhW = false;}
      if(eclUysEpCD == true){eclUysEpCD = false;}
      if(EXSRdYBaJJ == true){EXSRdYBaJJ = false;}
      if(SCAjTCySbd == true){SCAjTCySbd = false;}
      if(qEgusmqudP == true){qEgusmqudP = false;}
      if(YhKzCfsbEz == true){YhKzCfsbEz = false;}
      if(TeuXEccCBw == true){TeuXEccCBw = false;}
      if(tlOXLAqWXq == true){tlOXLAqWXq = false;}
      if(gGwtkkrBgn == true){gGwtkkrBgn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRHEJVRWHJ
{ 
  void FyPhHFfDCL()
  { 
      bool hyQKcwtjVm = false;
      bool JtVzhwVFJD = false;
      bool RLlrfdgePN = false;
      bool wFdXQHZlCV = false;
      bool oISYalIKSU = false;
      bool SHmVxVLXdy = false;
      bool OOUIqDQyiZ = false;
      bool ViDmOIrNRt = false;
      bool VWMutoSHZt = false;
      bool wCIDHamKhW = false;
      bool UKbsyiEzGo = false;
      bool dyGicrBZOB = false;
      bool kIYndTazfn = false;
      bool UhetYKuTwK = false;
      bool jSBkQyuYaO = false;
      bool YNwflMlmOe = false;
      bool HETSTwSLJR = false;
      bool xhdDRRHmXf = false;
      bool XCXQPHkyIM = false;
      bool YHEQCfyiQU = false;
      string BjuFRwccGO;
      string OPkjijVgrM;
      string zUbZAgosdx;
      string MFhKaEaUzp;
      string UtKhMTneIz;
      string WTEaBfHUEj;
      string HizJBIhZId;
      string IAhBrEKtMg;
      string sJkeZrBHJu;
      string wFQOikuAgD;
      string lOVdpWlDiw;
      string UNIXqxyUiI;
      string HaQNgCjTRG;
      string JKMIudmGnD;
      string GyYMZixsWl;
      string mZQXwKyIxm;
      string mRkbmKAzbM;
      string JqffBJBDmy;
      string FqweSisoMj;
      string feJAQnMwZP;
      if(BjuFRwccGO == lOVdpWlDiw){hyQKcwtjVm = true;}
      else if(lOVdpWlDiw == BjuFRwccGO){UKbsyiEzGo = true;}
      if(OPkjijVgrM == UNIXqxyUiI){JtVzhwVFJD = true;}
      else if(UNIXqxyUiI == OPkjijVgrM){dyGicrBZOB = true;}
      if(zUbZAgosdx == HaQNgCjTRG){RLlrfdgePN = true;}
      else if(HaQNgCjTRG == zUbZAgosdx){kIYndTazfn = true;}
      if(MFhKaEaUzp == JKMIudmGnD){wFdXQHZlCV = true;}
      else if(JKMIudmGnD == MFhKaEaUzp){UhetYKuTwK = true;}
      if(UtKhMTneIz == GyYMZixsWl){oISYalIKSU = true;}
      else if(GyYMZixsWl == UtKhMTneIz){jSBkQyuYaO = true;}
      if(WTEaBfHUEj == mZQXwKyIxm){SHmVxVLXdy = true;}
      else if(mZQXwKyIxm == WTEaBfHUEj){YNwflMlmOe = true;}
      if(HizJBIhZId == mRkbmKAzbM){OOUIqDQyiZ = true;}
      else if(mRkbmKAzbM == HizJBIhZId){HETSTwSLJR = true;}
      if(IAhBrEKtMg == JqffBJBDmy){ViDmOIrNRt = true;}
      if(sJkeZrBHJu == FqweSisoMj){VWMutoSHZt = true;}
      if(wFQOikuAgD == feJAQnMwZP){wCIDHamKhW = true;}
      while(JqffBJBDmy == IAhBrEKtMg){xhdDRRHmXf = true;}
      while(FqweSisoMj == FqweSisoMj){XCXQPHkyIM = true;}
      while(feJAQnMwZP == feJAQnMwZP){YHEQCfyiQU = true;}
      if(hyQKcwtjVm == true){hyQKcwtjVm = false;}
      if(JtVzhwVFJD == true){JtVzhwVFJD = false;}
      if(RLlrfdgePN == true){RLlrfdgePN = false;}
      if(wFdXQHZlCV == true){wFdXQHZlCV = false;}
      if(oISYalIKSU == true){oISYalIKSU = false;}
      if(SHmVxVLXdy == true){SHmVxVLXdy = false;}
      if(OOUIqDQyiZ == true){OOUIqDQyiZ = false;}
      if(ViDmOIrNRt == true){ViDmOIrNRt = false;}
      if(VWMutoSHZt == true){VWMutoSHZt = false;}
      if(wCIDHamKhW == true){wCIDHamKhW = false;}
      if(UKbsyiEzGo == true){UKbsyiEzGo = false;}
      if(dyGicrBZOB == true){dyGicrBZOB = false;}
      if(kIYndTazfn == true){kIYndTazfn = false;}
      if(UhetYKuTwK == true){UhetYKuTwK = false;}
      if(jSBkQyuYaO == true){jSBkQyuYaO = false;}
      if(YNwflMlmOe == true){YNwflMlmOe = false;}
      if(HETSTwSLJR == true){HETSTwSLJR = false;}
      if(xhdDRRHmXf == true){xhdDRRHmXf = false;}
      if(XCXQPHkyIM == true){XCXQPHkyIM = false;}
      if(YHEQCfyiQU == true){YHEQCfyiQU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QILVNBTNJC
{ 
  void zRfRwtRNbS()
  { 
      bool kXSTePdXRM = false;
      bool rMRVNOzcWI = false;
      bool xpcdEzpHda = false;
      bool QaqTAQJzQs = false;
      bool QIfuTeUKFi = false;
      bool bzejntuoOf = false;
      bool YVspwQUyUw = false;
      bool FAMcroKhJZ = false;
      bool efCuyRuHfF = false;
      bool VUkjUuPoyC = false;
      bool JWoIcblCrz = false;
      bool iMeoBrSxre = false;
      bool VNSPZkObIw = false;
      bool YViGPHqsSV = false;
      bool esPfVJowib = false;
      bool cRxTgwDZiq = false;
      bool NKtuZNcYZs = false;
      bool BYeVAbxlsQ = false;
      bool uSrfTHYPZS = false;
      bool ERKaIUzUGI = false;
      string FuJJetRzqi;
      string oEdaMbkuyy;
      string TxCwVZqGfI;
      string mGgAfXUTHT;
      string GTAPiFHmEI;
      string roRUCHsMmE;
      string CLThwiXdtn;
      string HQmerzxlNP;
      string SECWQxnLyY;
      string eIfDQuARTA;
      string hcsPBbCmcC;
      string JGyXlyIwRy;
      string tLfUJyjjNw;
      string zfSNhoLlVo;
      string uBiuPYJIQR;
      string lEzUFVxXGC;
      string qSYfDdnkpx;
      string mWabDscjFk;
      string obSuJtfxHM;
      string rmfSybbCrl;
      if(FuJJetRzqi == hcsPBbCmcC){kXSTePdXRM = true;}
      else if(hcsPBbCmcC == FuJJetRzqi){JWoIcblCrz = true;}
      if(oEdaMbkuyy == JGyXlyIwRy){rMRVNOzcWI = true;}
      else if(JGyXlyIwRy == oEdaMbkuyy){iMeoBrSxre = true;}
      if(TxCwVZqGfI == tLfUJyjjNw){xpcdEzpHda = true;}
      else if(tLfUJyjjNw == TxCwVZqGfI){VNSPZkObIw = true;}
      if(mGgAfXUTHT == zfSNhoLlVo){QaqTAQJzQs = true;}
      else if(zfSNhoLlVo == mGgAfXUTHT){YViGPHqsSV = true;}
      if(GTAPiFHmEI == uBiuPYJIQR){QIfuTeUKFi = true;}
      else if(uBiuPYJIQR == GTAPiFHmEI){esPfVJowib = true;}
      if(roRUCHsMmE == lEzUFVxXGC){bzejntuoOf = true;}
      else if(lEzUFVxXGC == roRUCHsMmE){cRxTgwDZiq = true;}
      if(CLThwiXdtn == qSYfDdnkpx){YVspwQUyUw = true;}
      else if(qSYfDdnkpx == CLThwiXdtn){NKtuZNcYZs = true;}
      if(HQmerzxlNP == mWabDscjFk){FAMcroKhJZ = true;}
      if(SECWQxnLyY == obSuJtfxHM){efCuyRuHfF = true;}
      if(eIfDQuARTA == rmfSybbCrl){VUkjUuPoyC = true;}
      while(mWabDscjFk == HQmerzxlNP){BYeVAbxlsQ = true;}
      while(obSuJtfxHM == obSuJtfxHM){uSrfTHYPZS = true;}
      while(rmfSybbCrl == rmfSybbCrl){ERKaIUzUGI = true;}
      if(kXSTePdXRM == true){kXSTePdXRM = false;}
      if(rMRVNOzcWI == true){rMRVNOzcWI = false;}
      if(xpcdEzpHda == true){xpcdEzpHda = false;}
      if(QaqTAQJzQs == true){QaqTAQJzQs = false;}
      if(QIfuTeUKFi == true){QIfuTeUKFi = false;}
      if(bzejntuoOf == true){bzejntuoOf = false;}
      if(YVspwQUyUw == true){YVspwQUyUw = false;}
      if(FAMcroKhJZ == true){FAMcroKhJZ = false;}
      if(efCuyRuHfF == true){efCuyRuHfF = false;}
      if(VUkjUuPoyC == true){VUkjUuPoyC = false;}
      if(JWoIcblCrz == true){JWoIcblCrz = false;}
      if(iMeoBrSxre == true){iMeoBrSxre = false;}
      if(VNSPZkObIw == true){VNSPZkObIw = false;}
      if(YViGPHqsSV == true){YViGPHqsSV = false;}
      if(esPfVJowib == true){esPfVJowib = false;}
      if(cRxTgwDZiq == true){cRxTgwDZiq = false;}
      if(NKtuZNcYZs == true){NKtuZNcYZs = false;}
      if(BYeVAbxlsQ == true){BYeVAbxlsQ = false;}
      if(uSrfTHYPZS == true){uSrfTHYPZS = false;}
      if(ERKaIUzUGI == true){ERKaIUzUGI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AUKQMCLKML
{ 
  void BWbNpgYbyg()
  { 
      bool ozMrGjlUDz = false;
      bool RiWpxprtVn = false;
      bool okzAGoVZDW = false;
      bool schbyFLqCJ = false;
      bool MJjCHUHaXt = false;
      bool WhokDEALlR = false;
      bool NLQfGoAtrq = false;
      bool dBrLbfAxsl = false;
      bool guCJzKmxYt = false;
      bool FAEjwArDwS = false;
      bool TNifPVodJX = false;
      bool DCSAkSJHfu = false;
      bool CDVykdwHPa = false;
      bool mxBZRTMVsd = false;
      bool VJnBpDhEzd = false;
      bool qjWAQQqjul = false;
      bool YhNhjGBrhR = false;
      bool FmNCZrOUHh = false;
      bool urIkiCZAJB = false;
      bool bbaGEmuFQj = false;
      string gpBHeNhjRr;
      string YpmQagKKAq;
      string mpthxUaXgF;
      string LEQkMKuERB;
      string REGzouOeww;
      string gGlGDquSJK;
      string lKDLgTYCEQ;
      string kGszYhitsC;
      string GwajYESJhV;
      string ObtHPHBuRV;
      string VLafLZNmhU;
      string HAZHEoiTlc;
      string APUiBILliR;
      string gmbWftVuXy;
      string qfaMNNCmCZ;
      string XhIoUGqqdD;
      string ObDPmTYCaJ;
      string SmunlUnHUm;
      string FXiJtzemCZ;
      string DdRUjPbLYs;
      if(gpBHeNhjRr == VLafLZNmhU){ozMrGjlUDz = true;}
      else if(VLafLZNmhU == gpBHeNhjRr){TNifPVodJX = true;}
      if(YpmQagKKAq == HAZHEoiTlc){RiWpxprtVn = true;}
      else if(HAZHEoiTlc == YpmQagKKAq){DCSAkSJHfu = true;}
      if(mpthxUaXgF == APUiBILliR){okzAGoVZDW = true;}
      else if(APUiBILliR == mpthxUaXgF){CDVykdwHPa = true;}
      if(LEQkMKuERB == gmbWftVuXy){schbyFLqCJ = true;}
      else if(gmbWftVuXy == LEQkMKuERB){mxBZRTMVsd = true;}
      if(REGzouOeww == qfaMNNCmCZ){MJjCHUHaXt = true;}
      else if(qfaMNNCmCZ == REGzouOeww){VJnBpDhEzd = true;}
      if(gGlGDquSJK == XhIoUGqqdD){WhokDEALlR = true;}
      else if(XhIoUGqqdD == gGlGDquSJK){qjWAQQqjul = true;}
      if(lKDLgTYCEQ == ObDPmTYCaJ){NLQfGoAtrq = true;}
      else if(ObDPmTYCaJ == lKDLgTYCEQ){YhNhjGBrhR = true;}
      if(kGszYhitsC == SmunlUnHUm){dBrLbfAxsl = true;}
      if(GwajYESJhV == FXiJtzemCZ){guCJzKmxYt = true;}
      if(ObtHPHBuRV == DdRUjPbLYs){FAEjwArDwS = true;}
      while(SmunlUnHUm == kGszYhitsC){FmNCZrOUHh = true;}
      while(FXiJtzemCZ == FXiJtzemCZ){urIkiCZAJB = true;}
      while(DdRUjPbLYs == DdRUjPbLYs){bbaGEmuFQj = true;}
      if(ozMrGjlUDz == true){ozMrGjlUDz = false;}
      if(RiWpxprtVn == true){RiWpxprtVn = false;}
      if(okzAGoVZDW == true){okzAGoVZDW = false;}
      if(schbyFLqCJ == true){schbyFLqCJ = false;}
      if(MJjCHUHaXt == true){MJjCHUHaXt = false;}
      if(WhokDEALlR == true){WhokDEALlR = false;}
      if(NLQfGoAtrq == true){NLQfGoAtrq = false;}
      if(dBrLbfAxsl == true){dBrLbfAxsl = false;}
      if(guCJzKmxYt == true){guCJzKmxYt = false;}
      if(FAEjwArDwS == true){FAEjwArDwS = false;}
      if(TNifPVodJX == true){TNifPVodJX = false;}
      if(DCSAkSJHfu == true){DCSAkSJHfu = false;}
      if(CDVykdwHPa == true){CDVykdwHPa = false;}
      if(mxBZRTMVsd == true){mxBZRTMVsd = false;}
      if(VJnBpDhEzd == true){VJnBpDhEzd = false;}
      if(qjWAQQqjul == true){qjWAQQqjul = false;}
      if(YhNhjGBrhR == true){YhNhjGBrhR = false;}
      if(FmNCZrOUHh == true){FmNCZrOUHh = false;}
      if(urIkiCZAJB == true){urIkiCZAJB = false;}
      if(bbaGEmuFQj == true){bbaGEmuFQj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTVHVBACUM
{ 
  void xmprfJcAWk()
  { 
      bool wwkMSKmDAI = false;
      bool ilixrIcSCj = false;
      bool OmlMcDxCcK = false;
      bool zsTjXwpklG = false;
      bool aBHbokKzSg = false;
      bool aWSZXJJYjO = false;
      bool MjZpJpRyYu = false;
      bool RrfuIMfKWr = false;
      bool syjwjbasLO = false;
      bool lRAXtpbQRz = false;
      bool SLZWOiqWRK = false;
      bool dzBqUNAdGg = false;
      bool OXmKIzqIBR = false;
      bool kOrXZhYMgA = false;
      bool kDbBkmQJCf = false;
      bool pxKjjtYPNO = false;
      bool qhVzYPGcRm = false;
      bool omwFwLwkZV = false;
      bool ihFUbnDHnf = false;
      bool JJyRIChcbV = false;
      string osjkfYEiUU;
      string rnUTlzlpTC;
      string qEtuGBwAeT;
      string MgFLnLNJem;
      string RQOPLiLOGj;
      string LxZaokzned;
      string bDEAHKhIfZ;
      string kcLfkaoeiW;
      string pgttIPHeWC;
      string MYdALOLNHB;
      string ACifyikspN;
      string uTFHmuJJrr;
      string DDldNMyKUW;
      string PaXhWmyOwZ;
      string dNnIGrTWMP;
      string EBVOxxQFRk;
      string jaXTyTwWkA;
      string xtNSNoOdWU;
      string sbxFROFIjY;
      string WswKoDpUJl;
      if(osjkfYEiUU == ACifyikspN){wwkMSKmDAI = true;}
      else if(ACifyikspN == osjkfYEiUU){SLZWOiqWRK = true;}
      if(rnUTlzlpTC == uTFHmuJJrr){ilixrIcSCj = true;}
      else if(uTFHmuJJrr == rnUTlzlpTC){dzBqUNAdGg = true;}
      if(qEtuGBwAeT == DDldNMyKUW){OmlMcDxCcK = true;}
      else if(DDldNMyKUW == qEtuGBwAeT){OXmKIzqIBR = true;}
      if(MgFLnLNJem == PaXhWmyOwZ){zsTjXwpklG = true;}
      else if(PaXhWmyOwZ == MgFLnLNJem){kOrXZhYMgA = true;}
      if(RQOPLiLOGj == dNnIGrTWMP){aBHbokKzSg = true;}
      else if(dNnIGrTWMP == RQOPLiLOGj){kDbBkmQJCf = true;}
      if(LxZaokzned == EBVOxxQFRk){aWSZXJJYjO = true;}
      else if(EBVOxxQFRk == LxZaokzned){pxKjjtYPNO = true;}
      if(bDEAHKhIfZ == jaXTyTwWkA){MjZpJpRyYu = true;}
      else if(jaXTyTwWkA == bDEAHKhIfZ){qhVzYPGcRm = true;}
      if(kcLfkaoeiW == xtNSNoOdWU){RrfuIMfKWr = true;}
      if(pgttIPHeWC == sbxFROFIjY){syjwjbasLO = true;}
      if(MYdALOLNHB == WswKoDpUJl){lRAXtpbQRz = true;}
      while(xtNSNoOdWU == kcLfkaoeiW){omwFwLwkZV = true;}
      while(sbxFROFIjY == sbxFROFIjY){ihFUbnDHnf = true;}
      while(WswKoDpUJl == WswKoDpUJl){JJyRIChcbV = true;}
      if(wwkMSKmDAI == true){wwkMSKmDAI = false;}
      if(ilixrIcSCj == true){ilixrIcSCj = false;}
      if(OmlMcDxCcK == true){OmlMcDxCcK = false;}
      if(zsTjXwpklG == true){zsTjXwpklG = false;}
      if(aBHbokKzSg == true){aBHbokKzSg = false;}
      if(aWSZXJJYjO == true){aWSZXJJYjO = false;}
      if(MjZpJpRyYu == true){MjZpJpRyYu = false;}
      if(RrfuIMfKWr == true){RrfuIMfKWr = false;}
      if(syjwjbasLO == true){syjwjbasLO = false;}
      if(lRAXtpbQRz == true){lRAXtpbQRz = false;}
      if(SLZWOiqWRK == true){SLZWOiqWRK = false;}
      if(dzBqUNAdGg == true){dzBqUNAdGg = false;}
      if(OXmKIzqIBR == true){OXmKIzqIBR = false;}
      if(kOrXZhYMgA == true){kOrXZhYMgA = false;}
      if(kDbBkmQJCf == true){kDbBkmQJCf = false;}
      if(pxKjjtYPNO == true){pxKjjtYPNO = false;}
      if(qhVzYPGcRm == true){qhVzYPGcRm = false;}
      if(omwFwLwkZV == true){omwFwLwkZV = false;}
      if(ihFUbnDHnf == true){ihFUbnDHnf = false;}
      if(JJyRIChcbV == true){JJyRIChcbV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXGZLQLQTS
{ 
  void qJdrQLduyG()
  { 
      bool IIERVpyAnD = false;
      bool eyXmfrhurP = false;
      bool jDFqsUDCIl = false;
      bool hIiRgmThbM = false;
      bool EjlVHLKziu = false;
      bool bwpkIECNYB = false;
      bool lurCVWOGFr = false;
      bool XASeLzRiih = false;
      bool KESMJkSyIc = false;
      bool jGIaaIrjzk = false;
      bool wEspWbcLYI = false;
      bool mSdqqhberj = false;
      bool DPxcHRqqED = false;
      bool HgjxkGKcph = false;
      bool IGZzpQbRjs = false;
      bool fMrOggGQhF = false;
      bool jlGVBFifGk = false;
      bool WzoKbxpxlp = false;
      bool oYHLWuoUPD = false;
      bool zttjxVAEyj = false;
      string bQLSEKJfJQ;
      string rzsgIAtbAp;
      string cyqmbcSgUg;
      string ggRisCtOqk;
      string QkWHxZxuLR;
      string EmfGddZXpa;
      string rbLbiKgKnF;
      string FfkPYrbjoC;
      string fXVCctBLFP;
      string cVXPrnYuYl;
      string rmGFLYCQgk;
      string BphnuTGIzn;
      string JVEXciHUWk;
      string SgKDJrQPqD;
      string rjdTNmniUY;
      string gPujcWihcb;
      string QhsuSUeeeC;
      string CqRuwYqjKo;
      string uYzyDCkaZm;
      string JhmPmKqhBs;
      if(bQLSEKJfJQ == rmGFLYCQgk){IIERVpyAnD = true;}
      else if(rmGFLYCQgk == bQLSEKJfJQ){wEspWbcLYI = true;}
      if(rzsgIAtbAp == BphnuTGIzn){eyXmfrhurP = true;}
      else if(BphnuTGIzn == rzsgIAtbAp){mSdqqhberj = true;}
      if(cyqmbcSgUg == JVEXciHUWk){jDFqsUDCIl = true;}
      else if(JVEXciHUWk == cyqmbcSgUg){DPxcHRqqED = true;}
      if(ggRisCtOqk == SgKDJrQPqD){hIiRgmThbM = true;}
      else if(SgKDJrQPqD == ggRisCtOqk){HgjxkGKcph = true;}
      if(QkWHxZxuLR == rjdTNmniUY){EjlVHLKziu = true;}
      else if(rjdTNmniUY == QkWHxZxuLR){IGZzpQbRjs = true;}
      if(EmfGddZXpa == gPujcWihcb){bwpkIECNYB = true;}
      else if(gPujcWihcb == EmfGddZXpa){fMrOggGQhF = true;}
      if(rbLbiKgKnF == QhsuSUeeeC){lurCVWOGFr = true;}
      else if(QhsuSUeeeC == rbLbiKgKnF){jlGVBFifGk = true;}
      if(FfkPYrbjoC == CqRuwYqjKo){XASeLzRiih = true;}
      if(fXVCctBLFP == uYzyDCkaZm){KESMJkSyIc = true;}
      if(cVXPrnYuYl == JhmPmKqhBs){jGIaaIrjzk = true;}
      while(CqRuwYqjKo == FfkPYrbjoC){WzoKbxpxlp = true;}
      while(uYzyDCkaZm == uYzyDCkaZm){oYHLWuoUPD = true;}
      while(JhmPmKqhBs == JhmPmKqhBs){zttjxVAEyj = true;}
      if(IIERVpyAnD == true){IIERVpyAnD = false;}
      if(eyXmfrhurP == true){eyXmfrhurP = false;}
      if(jDFqsUDCIl == true){jDFqsUDCIl = false;}
      if(hIiRgmThbM == true){hIiRgmThbM = false;}
      if(EjlVHLKziu == true){EjlVHLKziu = false;}
      if(bwpkIECNYB == true){bwpkIECNYB = false;}
      if(lurCVWOGFr == true){lurCVWOGFr = false;}
      if(XASeLzRiih == true){XASeLzRiih = false;}
      if(KESMJkSyIc == true){KESMJkSyIc = false;}
      if(jGIaaIrjzk == true){jGIaaIrjzk = false;}
      if(wEspWbcLYI == true){wEspWbcLYI = false;}
      if(mSdqqhberj == true){mSdqqhberj = false;}
      if(DPxcHRqqED == true){DPxcHRqqED = false;}
      if(HgjxkGKcph == true){HgjxkGKcph = false;}
      if(IGZzpQbRjs == true){IGZzpQbRjs = false;}
      if(fMrOggGQhF == true){fMrOggGQhF = false;}
      if(jlGVBFifGk == true){jlGVBFifGk = false;}
      if(WzoKbxpxlp == true){WzoKbxpxlp = false;}
      if(oYHLWuoUPD == true){oYHLWuoUPD = false;}
      if(zttjxVAEyj == true){zttjxVAEyj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVXMEXRBHB
{ 
  void pAKnjOxgwa()
  { 
      bool oADMjuKznf = false;
      bool lYXFCYThZj = false;
      bool fJZLryPIio = false;
      bool kkuERsNzkU = false;
      bool WuBaUBQmnG = false;
      bool JufFcfaqTl = false;
      bool fCQzuAcSmJ = false;
      bool LUwEMjHypq = false;
      bool gbUbepEobl = false;
      bool SVezoUeCfT = false;
      bool Xyzeuoybsr = false;
      bool XbAbEEgnUE = false;
      bool wnpBpooxPr = false;
      bool EERWTicpgo = false;
      bool rbuiNpUCtj = false;
      bool mqhaXiHynF = false;
      bool AAMBnTJdIU = false;
      bool aqHeMTrHmz = false;
      bool UlCeENWqzk = false;
      bool bdBboqPtut = false;
      string gPlRlbfnTq;
      string dDfaEtjtkd;
      string uogHOyGFkj;
      string eEGUKUxZUG;
      string rChxOOMyqW;
      string lxaxCqhdCn;
      string VaDiLYxKQi;
      string wJYelrHjsA;
      string lINOyhdIRT;
      string mTXgkQzykp;
      string QChIZbXwLK;
      string jykBCNMnkd;
      string unrwwclqsU;
      string sIyCiiZFnV;
      string KgxHioiVeX;
      string DKNHucJkMx;
      string pfDqRazhRS;
      string mHAOSOqkNG;
      string tQMVQhupHG;
      string ZorqfdcGpI;
      if(gPlRlbfnTq == QChIZbXwLK){oADMjuKznf = true;}
      else if(QChIZbXwLK == gPlRlbfnTq){Xyzeuoybsr = true;}
      if(dDfaEtjtkd == jykBCNMnkd){lYXFCYThZj = true;}
      else if(jykBCNMnkd == dDfaEtjtkd){XbAbEEgnUE = true;}
      if(uogHOyGFkj == unrwwclqsU){fJZLryPIio = true;}
      else if(unrwwclqsU == uogHOyGFkj){wnpBpooxPr = true;}
      if(eEGUKUxZUG == sIyCiiZFnV){kkuERsNzkU = true;}
      else if(sIyCiiZFnV == eEGUKUxZUG){EERWTicpgo = true;}
      if(rChxOOMyqW == KgxHioiVeX){WuBaUBQmnG = true;}
      else if(KgxHioiVeX == rChxOOMyqW){rbuiNpUCtj = true;}
      if(lxaxCqhdCn == DKNHucJkMx){JufFcfaqTl = true;}
      else if(DKNHucJkMx == lxaxCqhdCn){mqhaXiHynF = true;}
      if(VaDiLYxKQi == pfDqRazhRS){fCQzuAcSmJ = true;}
      else if(pfDqRazhRS == VaDiLYxKQi){AAMBnTJdIU = true;}
      if(wJYelrHjsA == mHAOSOqkNG){LUwEMjHypq = true;}
      if(lINOyhdIRT == tQMVQhupHG){gbUbepEobl = true;}
      if(mTXgkQzykp == ZorqfdcGpI){SVezoUeCfT = true;}
      while(mHAOSOqkNG == wJYelrHjsA){aqHeMTrHmz = true;}
      while(tQMVQhupHG == tQMVQhupHG){UlCeENWqzk = true;}
      while(ZorqfdcGpI == ZorqfdcGpI){bdBboqPtut = true;}
      if(oADMjuKznf == true){oADMjuKznf = false;}
      if(lYXFCYThZj == true){lYXFCYThZj = false;}
      if(fJZLryPIio == true){fJZLryPIio = false;}
      if(kkuERsNzkU == true){kkuERsNzkU = false;}
      if(WuBaUBQmnG == true){WuBaUBQmnG = false;}
      if(JufFcfaqTl == true){JufFcfaqTl = false;}
      if(fCQzuAcSmJ == true){fCQzuAcSmJ = false;}
      if(LUwEMjHypq == true){LUwEMjHypq = false;}
      if(gbUbepEobl == true){gbUbepEobl = false;}
      if(SVezoUeCfT == true){SVezoUeCfT = false;}
      if(Xyzeuoybsr == true){Xyzeuoybsr = false;}
      if(XbAbEEgnUE == true){XbAbEEgnUE = false;}
      if(wnpBpooxPr == true){wnpBpooxPr = false;}
      if(EERWTicpgo == true){EERWTicpgo = false;}
      if(rbuiNpUCtj == true){rbuiNpUCtj = false;}
      if(mqhaXiHynF == true){mqhaXiHynF = false;}
      if(AAMBnTJdIU == true){AAMBnTJdIU = false;}
      if(aqHeMTrHmz == true){aqHeMTrHmz = false;}
      if(UlCeENWqzk == true){UlCeENWqzk = false;}
      if(bdBboqPtut == true){bdBboqPtut = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQJGKTUDYP
{ 
  void GlgslgDZUV()
  { 
      bool CORodoDMMI = false;
      bool fMqLswLues = false;
      bool nCOLqoRock = false;
      bool yGzBsiPjxq = false;
      bool AqrDePGrMd = false;
      bool XdjcYzzFxo = false;
      bool XOjaKYNpSK = false;
      bool fbxnswKLfb = false;
      bool hYbzMTWWbt = false;
      bool iJlISkHRsG = false;
      bool BPZCxwgujc = false;
      bool onZVGyljNq = false;
      bool BpOYbWooUH = false;
      bool osRYZRyZBQ = false;
      bool lalzEtiPBT = false;
      bool yWDCEKBBZZ = false;
      bool GqacmwVBwn = false;
      bool AMhxEZEPTg = false;
      bool nZnAIRoPTO = false;
      bool QxzbKuAJLI = false;
      string ZVhndKHdyI;
      string MwaIWQPVkn;
      string MUOWpQnzGr;
      string cgTQWLTWAf;
      string CQcDebgKYc;
      string qnUoxEGKyN;
      string VIWGefbJlK;
      string xsUEkwqLqN;
      string idZdAnMeTS;
      string FJYmKssWYz;
      string zXYNexSQDA;
      string MtSjdrhsGp;
      string TxoTFnUhtr;
      string DUmrNKEMyC;
      string UwaTFKpnIR;
      string LzQhfCiFHq;
      string ckWLxrHaWT;
      string nVuDUXWVNu;
      string xgYbfEEELL;
      string byEGZjYPVM;
      if(ZVhndKHdyI == zXYNexSQDA){CORodoDMMI = true;}
      else if(zXYNexSQDA == ZVhndKHdyI){BPZCxwgujc = true;}
      if(MwaIWQPVkn == MtSjdrhsGp){fMqLswLues = true;}
      else if(MtSjdrhsGp == MwaIWQPVkn){onZVGyljNq = true;}
      if(MUOWpQnzGr == TxoTFnUhtr){nCOLqoRock = true;}
      else if(TxoTFnUhtr == MUOWpQnzGr){BpOYbWooUH = true;}
      if(cgTQWLTWAf == DUmrNKEMyC){yGzBsiPjxq = true;}
      else if(DUmrNKEMyC == cgTQWLTWAf){osRYZRyZBQ = true;}
      if(CQcDebgKYc == UwaTFKpnIR){AqrDePGrMd = true;}
      else if(UwaTFKpnIR == CQcDebgKYc){lalzEtiPBT = true;}
      if(qnUoxEGKyN == LzQhfCiFHq){XdjcYzzFxo = true;}
      else if(LzQhfCiFHq == qnUoxEGKyN){yWDCEKBBZZ = true;}
      if(VIWGefbJlK == ckWLxrHaWT){XOjaKYNpSK = true;}
      else if(ckWLxrHaWT == VIWGefbJlK){GqacmwVBwn = true;}
      if(xsUEkwqLqN == nVuDUXWVNu){fbxnswKLfb = true;}
      if(idZdAnMeTS == xgYbfEEELL){hYbzMTWWbt = true;}
      if(FJYmKssWYz == byEGZjYPVM){iJlISkHRsG = true;}
      while(nVuDUXWVNu == xsUEkwqLqN){AMhxEZEPTg = true;}
      while(xgYbfEEELL == xgYbfEEELL){nZnAIRoPTO = true;}
      while(byEGZjYPVM == byEGZjYPVM){QxzbKuAJLI = true;}
      if(CORodoDMMI == true){CORodoDMMI = false;}
      if(fMqLswLues == true){fMqLswLues = false;}
      if(nCOLqoRock == true){nCOLqoRock = false;}
      if(yGzBsiPjxq == true){yGzBsiPjxq = false;}
      if(AqrDePGrMd == true){AqrDePGrMd = false;}
      if(XdjcYzzFxo == true){XdjcYzzFxo = false;}
      if(XOjaKYNpSK == true){XOjaKYNpSK = false;}
      if(fbxnswKLfb == true){fbxnswKLfb = false;}
      if(hYbzMTWWbt == true){hYbzMTWWbt = false;}
      if(iJlISkHRsG == true){iJlISkHRsG = false;}
      if(BPZCxwgujc == true){BPZCxwgujc = false;}
      if(onZVGyljNq == true){onZVGyljNq = false;}
      if(BpOYbWooUH == true){BpOYbWooUH = false;}
      if(osRYZRyZBQ == true){osRYZRyZBQ = false;}
      if(lalzEtiPBT == true){lalzEtiPBT = false;}
      if(yWDCEKBBZZ == true){yWDCEKBBZZ = false;}
      if(GqacmwVBwn == true){GqacmwVBwn = false;}
      if(AMhxEZEPTg == true){AMhxEZEPTg = false;}
      if(nZnAIRoPTO == true){nZnAIRoPTO = false;}
      if(QxzbKuAJLI == true){QxzbKuAJLI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJILMOFGWN
{ 
  void FZiBXJWfDR()
  { 
      bool drcolYcyEV = false;
      bool WeGmPXGfOR = false;
      bool YHPVBROzLp = false;
      bool JqKewkVimx = false;
      bool dsraUgxtxn = false;
      bool IqKxCWbGnT = false;
      bool KdmNMfTbqd = false;
      bool CWrQneOoBU = false;
      bool UUBWgRfNbY = false;
      bool JPuTlzGeOn = false;
      bool MUCSlkzsIX = false;
      bool ImESypbPgt = false;
      bool zGzRTlbYen = false;
      bool YjZMIARhju = false;
      bool SmFEQWKbUw = false;
      bool XqxUnGUkzA = false;
      bool JaOTzYMqKy = false;
      bool XtekaMAuBx = false;
      bool bADhQglFYB = false;
      bool egijlrXkFq = false;
      string SHcNkoqUrV;
      string DhziWCzCtQ;
      string NmfAYXVlRk;
      string SeSdHUyYtQ;
      string OKoOldnoWh;
      string mPPeWfbcnN;
      string TECHDYOUaB;
      string EZIdBDyROt;
      string jfPjxCOnHa;
      string sUjfwKHgKM;
      string OSNVcMHlcT;
      string hKOsdnoSJA;
      string JaNAIjpbgq;
      string uQGBfQRtGj;
      string ubKmshFpCH;
      string UoXJDnFNMs;
      string WfEkXRENNM;
      string VuLYFgQZGZ;
      string dzYYWGrwxr;
      string LDgMMPWYOb;
      if(SHcNkoqUrV == OSNVcMHlcT){drcolYcyEV = true;}
      else if(OSNVcMHlcT == SHcNkoqUrV){MUCSlkzsIX = true;}
      if(DhziWCzCtQ == hKOsdnoSJA){WeGmPXGfOR = true;}
      else if(hKOsdnoSJA == DhziWCzCtQ){ImESypbPgt = true;}
      if(NmfAYXVlRk == JaNAIjpbgq){YHPVBROzLp = true;}
      else if(JaNAIjpbgq == NmfAYXVlRk){zGzRTlbYen = true;}
      if(SeSdHUyYtQ == uQGBfQRtGj){JqKewkVimx = true;}
      else if(uQGBfQRtGj == SeSdHUyYtQ){YjZMIARhju = true;}
      if(OKoOldnoWh == ubKmshFpCH){dsraUgxtxn = true;}
      else if(ubKmshFpCH == OKoOldnoWh){SmFEQWKbUw = true;}
      if(mPPeWfbcnN == UoXJDnFNMs){IqKxCWbGnT = true;}
      else if(UoXJDnFNMs == mPPeWfbcnN){XqxUnGUkzA = true;}
      if(TECHDYOUaB == WfEkXRENNM){KdmNMfTbqd = true;}
      else if(WfEkXRENNM == TECHDYOUaB){JaOTzYMqKy = true;}
      if(EZIdBDyROt == VuLYFgQZGZ){CWrQneOoBU = true;}
      if(jfPjxCOnHa == dzYYWGrwxr){UUBWgRfNbY = true;}
      if(sUjfwKHgKM == LDgMMPWYOb){JPuTlzGeOn = true;}
      while(VuLYFgQZGZ == EZIdBDyROt){XtekaMAuBx = true;}
      while(dzYYWGrwxr == dzYYWGrwxr){bADhQglFYB = true;}
      while(LDgMMPWYOb == LDgMMPWYOb){egijlrXkFq = true;}
      if(drcolYcyEV == true){drcolYcyEV = false;}
      if(WeGmPXGfOR == true){WeGmPXGfOR = false;}
      if(YHPVBROzLp == true){YHPVBROzLp = false;}
      if(JqKewkVimx == true){JqKewkVimx = false;}
      if(dsraUgxtxn == true){dsraUgxtxn = false;}
      if(IqKxCWbGnT == true){IqKxCWbGnT = false;}
      if(KdmNMfTbqd == true){KdmNMfTbqd = false;}
      if(CWrQneOoBU == true){CWrQneOoBU = false;}
      if(UUBWgRfNbY == true){UUBWgRfNbY = false;}
      if(JPuTlzGeOn == true){JPuTlzGeOn = false;}
      if(MUCSlkzsIX == true){MUCSlkzsIX = false;}
      if(ImESypbPgt == true){ImESypbPgt = false;}
      if(zGzRTlbYen == true){zGzRTlbYen = false;}
      if(YjZMIARhju == true){YjZMIARhju = false;}
      if(SmFEQWKbUw == true){SmFEQWKbUw = false;}
      if(XqxUnGUkzA == true){XqxUnGUkzA = false;}
      if(JaOTzYMqKy == true){JaOTzYMqKy = false;}
      if(XtekaMAuBx == true){XtekaMAuBx = false;}
      if(bADhQglFYB == true){bADhQglFYB = false;}
      if(egijlrXkFq == true){egijlrXkFq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIIRHESEER
{ 
  void kMHGAkRsHY()
  { 
      bool iqnWhwdpby = false;
      bool PoaNYEWYCD = false;
      bool NQfiXKrorR = false;
      bool xfroqoRpXs = false;
      bool RcQiGYwRkE = false;
      bool BcdQuSLEyX = false;
      bool DnxKBjwkWi = false;
      bool mfAJkjzwcz = false;
      bool NaDnPTBbtY = false;
      bool dMqAodfFgV = false;
      bool bLuCQVbUeK = false;
      bool SOazJcjJuh = false;
      bool iTqxFanATH = false;
      bool EtPHWCeBXs = false;
      bool rfxiGOkrpM = false;
      bool sWJzmHUyxo = false;
      bool gbAWGXzTbH = false;
      bool xilBoDWHqp = false;
      bool ouJHOhjPTP = false;
      bool hgDhMQeZbh = false;
      string xzzNRrtHnL;
      string VZSSrjSwMQ;
      string kiCytOzVko;
      string AHJpwKzTOq;
      string oQLapfNlqc;
      string KmXftOwATD;
      string sYWzLOQcWh;
      string kzgVbTWaHO;
      string AMeHdNiduh;
      string NyzLxPsMPb;
      string PjOJrKFCEa;
      string qUsFCgtPUx;
      string elhoTlAVXL;
      string ZKLezQyUPT;
      string HfZUpsFtIQ;
      string VdqRxcCZoF;
      string KierAgJNFl;
      string iYzBoyMMya;
      string gFMGpwSshV;
      string NXfJIXBgTI;
      if(xzzNRrtHnL == PjOJrKFCEa){iqnWhwdpby = true;}
      else if(PjOJrKFCEa == xzzNRrtHnL){bLuCQVbUeK = true;}
      if(VZSSrjSwMQ == qUsFCgtPUx){PoaNYEWYCD = true;}
      else if(qUsFCgtPUx == VZSSrjSwMQ){SOazJcjJuh = true;}
      if(kiCytOzVko == elhoTlAVXL){NQfiXKrorR = true;}
      else if(elhoTlAVXL == kiCytOzVko){iTqxFanATH = true;}
      if(AHJpwKzTOq == ZKLezQyUPT){xfroqoRpXs = true;}
      else if(ZKLezQyUPT == AHJpwKzTOq){EtPHWCeBXs = true;}
      if(oQLapfNlqc == HfZUpsFtIQ){RcQiGYwRkE = true;}
      else if(HfZUpsFtIQ == oQLapfNlqc){rfxiGOkrpM = true;}
      if(KmXftOwATD == VdqRxcCZoF){BcdQuSLEyX = true;}
      else if(VdqRxcCZoF == KmXftOwATD){sWJzmHUyxo = true;}
      if(sYWzLOQcWh == KierAgJNFl){DnxKBjwkWi = true;}
      else if(KierAgJNFl == sYWzLOQcWh){gbAWGXzTbH = true;}
      if(kzgVbTWaHO == iYzBoyMMya){mfAJkjzwcz = true;}
      if(AMeHdNiduh == gFMGpwSshV){NaDnPTBbtY = true;}
      if(NyzLxPsMPb == NXfJIXBgTI){dMqAodfFgV = true;}
      while(iYzBoyMMya == kzgVbTWaHO){xilBoDWHqp = true;}
      while(gFMGpwSshV == gFMGpwSshV){ouJHOhjPTP = true;}
      while(NXfJIXBgTI == NXfJIXBgTI){hgDhMQeZbh = true;}
      if(iqnWhwdpby == true){iqnWhwdpby = false;}
      if(PoaNYEWYCD == true){PoaNYEWYCD = false;}
      if(NQfiXKrorR == true){NQfiXKrorR = false;}
      if(xfroqoRpXs == true){xfroqoRpXs = false;}
      if(RcQiGYwRkE == true){RcQiGYwRkE = false;}
      if(BcdQuSLEyX == true){BcdQuSLEyX = false;}
      if(DnxKBjwkWi == true){DnxKBjwkWi = false;}
      if(mfAJkjzwcz == true){mfAJkjzwcz = false;}
      if(NaDnPTBbtY == true){NaDnPTBbtY = false;}
      if(dMqAodfFgV == true){dMqAodfFgV = false;}
      if(bLuCQVbUeK == true){bLuCQVbUeK = false;}
      if(SOazJcjJuh == true){SOazJcjJuh = false;}
      if(iTqxFanATH == true){iTqxFanATH = false;}
      if(EtPHWCeBXs == true){EtPHWCeBXs = false;}
      if(rfxiGOkrpM == true){rfxiGOkrpM = false;}
      if(sWJzmHUyxo == true){sWJzmHUyxo = false;}
      if(gbAWGXzTbH == true){gbAWGXzTbH = false;}
      if(xilBoDWHqp == true){xilBoDWHqp = false;}
      if(ouJHOhjPTP == true){ouJHOhjPTP = false;}
      if(hgDhMQeZbh == true){hgDhMQeZbh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOIRRACZTH
{ 
  void SigGEoZyeu()
  { 
      bool BjXtFkohYG = false;
      bool lnskfGKrsz = false;
      bool cmwkpczVdl = false;
      bool qrKBnKhKio = false;
      bool yoXaluKzTV = false;
      bool etfFyNmlEc = false;
      bool kSDmOsdqxV = false;
      bool XzJDAnPUzu = false;
      bool RABIGwMEDZ = false;
      bool WwGGEfkjMr = false;
      bool RTByyekbFK = false;
      bool yRmJKjQufS = false;
      bool gYnXyasDzU = false;
      bool CeIGcyyDKa = false;
      bool LjzraEJxuT = false;
      bool OpEtLredAW = false;
      bool lhckHTIffM = false;
      bool lNjFGwZuws = false;
      bool RwHeFLaOtj = false;
      bool SUDnodGOkH = false;
      string bSQCRQbSie;
      string iIHmmdEHOs;
      string QSARZCMPMx;
      string yFnUwoKxyu;
      string dMVQOiAPBD;
      string IAbepISzcP;
      string DLFkfdTmpy;
      string THJSOExiDq;
      string BxOJoxdIdm;
      string VKTirSGkjk;
      string ONYCiAqIPk;
      string LiwlNFwwui;
      string zKIDbInaaw;
      string yLyRbnYLZo;
      string GUsralOgUl;
      string VKoBkDEUaa;
      string MQhTmAkdJZ;
      string fkVGbeRPbo;
      string tGFoanWxgX;
      string iDkzbpmYFa;
      if(bSQCRQbSie == ONYCiAqIPk){BjXtFkohYG = true;}
      else if(ONYCiAqIPk == bSQCRQbSie){RTByyekbFK = true;}
      if(iIHmmdEHOs == LiwlNFwwui){lnskfGKrsz = true;}
      else if(LiwlNFwwui == iIHmmdEHOs){yRmJKjQufS = true;}
      if(QSARZCMPMx == zKIDbInaaw){cmwkpczVdl = true;}
      else if(zKIDbInaaw == QSARZCMPMx){gYnXyasDzU = true;}
      if(yFnUwoKxyu == yLyRbnYLZo){qrKBnKhKio = true;}
      else if(yLyRbnYLZo == yFnUwoKxyu){CeIGcyyDKa = true;}
      if(dMVQOiAPBD == GUsralOgUl){yoXaluKzTV = true;}
      else if(GUsralOgUl == dMVQOiAPBD){LjzraEJxuT = true;}
      if(IAbepISzcP == VKoBkDEUaa){etfFyNmlEc = true;}
      else if(VKoBkDEUaa == IAbepISzcP){OpEtLredAW = true;}
      if(DLFkfdTmpy == MQhTmAkdJZ){kSDmOsdqxV = true;}
      else if(MQhTmAkdJZ == DLFkfdTmpy){lhckHTIffM = true;}
      if(THJSOExiDq == fkVGbeRPbo){XzJDAnPUzu = true;}
      if(BxOJoxdIdm == tGFoanWxgX){RABIGwMEDZ = true;}
      if(VKTirSGkjk == iDkzbpmYFa){WwGGEfkjMr = true;}
      while(fkVGbeRPbo == THJSOExiDq){lNjFGwZuws = true;}
      while(tGFoanWxgX == tGFoanWxgX){RwHeFLaOtj = true;}
      while(iDkzbpmYFa == iDkzbpmYFa){SUDnodGOkH = true;}
      if(BjXtFkohYG == true){BjXtFkohYG = false;}
      if(lnskfGKrsz == true){lnskfGKrsz = false;}
      if(cmwkpczVdl == true){cmwkpczVdl = false;}
      if(qrKBnKhKio == true){qrKBnKhKio = false;}
      if(yoXaluKzTV == true){yoXaluKzTV = false;}
      if(etfFyNmlEc == true){etfFyNmlEc = false;}
      if(kSDmOsdqxV == true){kSDmOsdqxV = false;}
      if(XzJDAnPUzu == true){XzJDAnPUzu = false;}
      if(RABIGwMEDZ == true){RABIGwMEDZ = false;}
      if(WwGGEfkjMr == true){WwGGEfkjMr = false;}
      if(RTByyekbFK == true){RTByyekbFK = false;}
      if(yRmJKjQufS == true){yRmJKjQufS = false;}
      if(gYnXyasDzU == true){gYnXyasDzU = false;}
      if(CeIGcyyDKa == true){CeIGcyyDKa = false;}
      if(LjzraEJxuT == true){LjzraEJxuT = false;}
      if(OpEtLredAW == true){OpEtLredAW = false;}
      if(lhckHTIffM == true){lhckHTIffM = false;}
      if(lNjFGwZuws == true){lNjFGwZuws = false;}
      if(RwHeFLaOtj == true){RwHeFLaOtj = false;}
      if(SUDnodGOkH == true){SUDnodGOkH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDBTAAUSCL
{ 
  void SqDYUtFTBT()
  { 
      bool UKueUhgnpL = false;
      bool znLsCxHZJP = false;
      bool zRRWukDJCp = false;
      bool RpRUhaJDld = false;
      bool PfUgnaLDNT = false;
      bool OVjzsCrXjj = false;
      bool dXlAtJVpLb = false;
      bool nDmeASwkhT = false;
      bool ZAwhawFSae = false;
      bool hkTCArtTme = false;
      bool FUrkfKhFza = false;
      bool GGpPJdaDZx = false;
      bool DCOfsCjjdH = false;
      bool XbyCOEIKBP = false;
      bool NzTAYatDrW = false;
      bool RptobCFLqc = false;
      bool axaqCdImBE = false;
      bool UPCJiEiOHR = false;
      bool IfqHphgJaL = false;
      bool zxTYoPXbyt = false;
      string KDsMZqFdTI;
      string QtNONRgSIY;
      string FpUhVIlZAx;
      string GfOGdXLfEn;
      string FORdzOollB;
      string OdliJUhLpQ;
      string FecVCjeHkp;
      string GANTTqXphH;
      string TznzhctewJ;
      string ozoniZlubP;
      string igBwuNPRPS;
      string wqdixFqdnY;
      string pzLaAGLZkt;
      string FbOSXlxrET;
      string McPcMxVGpc;
      string hHHCYiVZun;
      string CpgVNTcLKL;
      string IzZTMNjhOC;
      string kEiHMxULsn;
      string PWwPRVutPs;
      if(KDsMZqFdTI == igBwuNPRPS){UKueUhgnpL = true;}
      else if(igBwuNPRPS == KDsMZqFdTI){FUrkfKhFza = true;}
      if(QtNONRgSIY == wqdixFqdnY){znLsCxHZJP = true;}
      else if(wqdixFqdnY == QtNONRgSIY){GGpPJdaDZx = true;}
      if(FpUhVIlZAx == pzLaAGLZkt){zRRWukDJCp = true;}
      else if(pzLaAGLZkt == FpUhVIlZAx){DCOfsCjjdH = true;}
      if(GfOGdXLfEn == FbOSXlxrET){RpRUhaJDld = true;}
      else if(FbOSXlxrET == GfOGdXLfEn){XbyCOEIKBP = true;}
      if(FORdzOollB == McPcMxVGpc){PfUgnaLDNT = true;}
      else if(McPcMxVGpc == FORdzOollB){NzTAYatDrW = true;}
      if(OdliJUhLpQ == hHHCYiVZun){OVjzsCrXjj = true;}
      else if(hHHCYiVZun == OdliJUhLpQ){RptobCFLqc = true;}
      if(FecVCjeHkp == CpgVNTcLKL){dXlAtJVpLb = true;}
      else if(CpgVNTcLKL == FecVCjeHkp){axaqCdImBE = true;}
      if(GANTTqXphH == IzZTMNjhOC){nDmeASwkhT = true;}
      if(TznzhctewJ == kEiHMxULsn){ZAwhawFSae = true;}
      if(ozoniZlubP == PWwPRVutPs){hkTCArtTme = true;}
      while(IzZTMNjhOC == GANTTqXphH){UPCJiEiOHR = true;}
      while(kEiHMxULsn == kEiHMxULsn){IfqHphgJaL = true;}
      while(PWwPRVutPs == PWwPRVutPs){zxTYoPXbyt = true;}
      if(UKueUhgnpL == true){UKueUhgnpL = false;}
      if(znLsCxHZJP == true){znLsCxHZJP = false;}
      if(zRRWukDJCp == true){zRRWukDJCp = false;}
      if(RpRUhaJDld == true){RpRUhaJDld = false;}
      if(PfUgnaLDNT == true){PfUgnaLDNT = false;}
      if(OVjzsCrXjj == true){OVjzsCrXjj = false;}
      if(dXlAtJVpLb == true){dXlAtJVpLb = false;}
      if(nDmeASwkhT == true){nDmeASwkhT = false;}
      if(ZAwhawFSae == true){ZAwhawFSae = false;}
      if(hkTCArtTme == true){hkTCArtTme = false;}
      if(FUrkfKhFza == true){FUrkfKhFza = false;}
      if(GGpPJdaDZx == true){GGpPJdaDZx = false;}
      if(DCOfsCjjdH == true){DCOfsCjjdH = false;}
      if(XbyCOEIKBP == true){XbyCOEIKBP = false;}
      if(NzTAYatDrW == true){NzTAYatDrW = false;}
      if(RptobCFLqc == true){RptobCFLqc = false;}
      if(axaqCdImBE == true){axaqCdImBE = false;}
      if(UPCJiEiOHR == true){UPCJiEiOHR = false;}
      if(IfqHphgJaL == true){IfqHphgJaL = false;}
      if(zxTYoPXbyt == true){zxTYoPXbyt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCQGXRUGPH
{ 
  void hkLaeRksnF()
  { 
      bool QXmmecytzT = false;
      bool SGrWELnRsL = false;
      bool dxHjCJNTEi = false;
      bool oXGEslrHuk = false;
      bool GFXDGtJQct = false;
      bool YsWIMTQDkU = false;
      bool PdpQetAmdS = false;
      bool TgVHEYZEcI = false;
      bool zxqKJwBxrZ = false;
      bool VoVaVbPGXM = false;
      bool tWmKZrWOEm = false;
      bool tMZbUSmeGi = false;
      bool rCtDweKulb = false;
      bool ISfQOcJfjR = false;
      bool YmsEfJOtFD = false;
      bool ojAoTqbjNu = false;
      bool gabbebfJNr = false;
      bool IGunJFJpXm = false;
      bool PPpimYRpwW = false;
      bool BZRojxKRZD = false;
      string PzhqWQdEaJ;
      string rPSktnnKre;
      string bJDADEWDhA;
      string AccqMWFZuk;
      string eVowmFXcCK;
      string hjPCeFuhnS;
      string tZWaIPlaXX;
      string iOPHzGUGNy;
      string fsBXRQMaMG;
      string aWlcpEzOmW;
      string SxEeaTUICY;
      string knUolAYyIr;
      string DLOQxMblQt;
      string GGTpfioVwy;
      string uDXmVlCwqp;
      string fAFuTGhmhO;
      string qirHReUdJD;
      string LCBKwznbuK;
      string KetZOFAXWY;
      string ABnhGMKPUp;
      if(PzhqWQdEaJ == SxEeaTUICY){QXmmecytzT = true;}
      else if(SxEeaTUICY == PzhqWQdEaJ){tWmKZrWOEm = true;}
      if(rPSktnnKre == knUolAYyIr){SGrWELnRsL = true;}
      else if(knUolAYyIr == rPSktnnKre){tMZbUSmeGi = true;}
      if(bJDADEWDhA == DLOQxMblQt){dxHjCJNTEi = true;}
      else if(DLOQxMblQt == bJDADEWDhA){rCtDweKulb = true;}
      if(AccqMWFZuk == GGTpfioVwy){oXGEslrHuk = true;}
      else if(GGTpfioVwy == AccqMWFZuk){ISfQOcJfjR = true;}
      if(eVowmFXcCK == uDXmVlCwqp){GFXDGtJQct = true;}
      else if(uDXmVlCwqp == eVowmFXcCK){YmsEfJOtFD = true;}
      if(hjPCeFuhnS == fAFuTGhmhO){YsWIMTQDkU = true;}
      else if(fAFuTGhmhO == hjPCeFuhnS){ojAoTqbjNu = true;}
      if(tZWaIPlaXX == qirHReUdJD){PdpQetAmdS = true;}
      else if(qirHReUdJD == tZWaIPlaXX){gabbebfJNr = true;}
      if(iOPHzGUGNy == LCBKwznbuK){TgVHEYZEcI = true;}
      if(fsBXRQMaMG == KetZOFAXWY){zxqKJwBxrZ = true;}
      if(aWlcpEzOmW == ABnhGMKPUp){VoVaVbPGXM = true;}
      while(LCBKwznbuK == iOPHzGUGNy){IGunJFJpXm = true;}
      while(KetZOFAXWY == KetZOFAXWY){PPpimYRpwW = true;}
      while(ABnhGMKPUp == ABnhGMKPUp){BZRojxKRZD = true;}
      if(QXmmecytzT == true){QXmmecytzT = false;}
      if(SGrWELnRsL == true){SGrWELnRsL = false;}
      if(dxHjCJNTEi == true){dxHjCJNTEi = false;}
      if(oXGEslrHuk == true){oXGEslrHuk = false;}
      if(GFXDGtJQct == true){GFXDGtJQct = false;}
      if(YsWIMTQDkU == true){YsWIMTQDkU = false;}
      if(PdpQetAmdS == true){PdpQetAmdS = false;}
      if(TgVHEYZEcI == true){TgVHEYZEcI = false;}
      if(zxqKJwBxrZ == true){zxqKJwBxrZ = false;}
      if(VoVaVbPGXM == true){VoVaVbPGXM = false;}
      if(tWmKZrWOEm == true){tWmKZrWOEm = false;}
      if(tMZbUSmeGi == true){tMZbUSmeGi = false;}
      if(rCtDweKulb == true){rCtDweKulb = false;}
      if(ISfQOcJfjR == true){ISfQOcJfjR = false;}
      if(YmsEfJOtFD == true){YmsEfJOtFD = false;}
      if(ojAoTqbjNu == true){ojAoTqbjNu = false;}
      if(gabbebfJNr == true){gabbebfJNr = false;}
      if(IGunJFJpXm == true){IGunJFJpXm = false;}
      if(PPpimYRpwW == true){PPpimYRpwW = false;}
      if(BZRojxKRZD == true){BZRojxKRZD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHNOXGBKTG
{ 
  void gIxuphTKBi()
  { 
      bool NDVmmMpMRM = false;
      bool NluXCbpzyU = false;
      bool WicZxHGlUn = false;
      bool tNzCqpzIuV = false;
      bool sJGsekKCWR = false;
      bool AXuEKdZwof = false;
      bool FEqcRAmrfL = false;
      bool cgEbbNcjtM = false;
      bool wEOCnVRuqN = false;
      bool QDTPPoRdae = false;
      bool yRVLnSSTbx = false;
      bool BpBciBoonu = false;
      bool hrBSuZNoLm = false;
      bool uzIPNehDNU = false;
      bool DySsLaBpfO = false;
      bool zcofxGPDPO = false;
      bool FdHoBBhlOD = false;
      bool TlaTriYHGU = false;
      bool YWJxmSKcRH = false;
      bool OdmzPYpcrJ = false;
      string kGEqnHYEyB;
      string JIGHYNKhuT;
      string pSEqnkljUr;
      string aOrhhAWaPR;
      string QTnezUmNcU;
      string qIsKMSCNCC;
      string VoiGZtQYYY;
      string piRdCVdZqT;
      string xYGAASVhUO;
      string yJXNwbkgEE;
      string EOnDdIpPHp;
      string ocViEwiiGH;
      string YhDJagKEga;
      string kwUlPijCWr;
      string bGZeZVmoIz;
      string rCawfVLecw;
      string xlhgErHjTV;
      string MfLOeSHYjF;
      string tUuhhiVXGs;
      string XFZZtpXsZg;
      if(kGEqnHYEyB == EOnDdIpPHp){NDVmmMpMRM = true;}
      else if(EOnDdIpPHp == kGEqnHYEyB){yRVLnSSTbx = true;}
      if(JIGHYNKhuT == ocViEwiiGH){NluXCbpzyU = true;}
      else if(ocViEwiiGH == JIGHYNKhuT){BpBciBoonu = true;}
      if(pSEqnkljUr == YhDJagKEga){WicZxHGlUn = true;}
      else if(YhDJagKEga == pSEqnkljUr){hrBSuZNoLm = true;}
      if(aOrhhAWaPR == kwUlPijCWr){tNzCqpzIuV = true;}
      else if(kwUlPijCWr == aOrhhAWaPR){uzIPNehDNU = true;}
      if(QTnezUmNcU == bGZeZVmoIz){sJGsekKCWR = true;}
      else if(bGZeZVmoIz == QTnezUmNcU){DySsLaBpfO = true;}
      if(qIsKMSCNCC == rCawfVLecw){AXuEKdZwof = true;}
      else if(rCawfVLecw == qIsKMSCNCC){zcofxGPDPO = true;}
      if(VoiGZtQYYY == xlhgErHjTV){FEqcRAmrfL = true;}
      else if(xlhgErHjTV == VoiGZtQYYY){FdHoBBhlOD = true;}
      if(piRdCVdZqT == MfLOeSHYjF){cgEbbNcjtM = true;}
      if(xYGAASVhUO == tUuhhiVXGs){wEOCnVRuqN = true;}
      if(yJXNwbkgEE == XFZZtpXsZg){QDTPPoRdae = true;}
      while(MfLOeSHYjF == piRdCVdZqT){TlaTriYHGU = true;}
      while(tUuhhiVXGs == tUuhhiVXGs){YWJxmSKcRH = true;}
      while(XFZZtpXsZg == XFZZtpXsZg){OdmzPYpcrJ = true;}
      if(NDVmmMpMRM == true){NDVmmMpMRM = false;}
      if(NluXCbpzyU == true){NluXCbpzyU = false;}
      if(WicZxHGlUn == true){WicZxHGlUn = false;}
      if(tNzCqpzIuV == true){tNzCqpzIuV = false;}
      if(sJGsekKCWR == true){sJGsekKCWR = false;}
      if(AXuEKdZwof == true){AXuEKdZwof = false;}
      if(FEqcRAmrfL == true){FEqcRAmrfL = false;}
      if(cgEbbNcjtM == true){cgEbbNcjtM = false;}
      if(wEOCnVRuqN == true){wEOCnVRuqN = false;}
      if(QDTPPoRdae == true){QDTPPoRdae = false;}
      if(yRVLnSSTbx == true){yRVLnSSTbx = false;}
      if(BpBciBoonu == true){BpBciBoonu = false;}
      if(hrBSuZNoLm == true){hrBSuZNoLm = false;}
      if(uzIPNehDNU == true){uzIPNehDNU = false;}
      if(DySsLaBpfO == true){DySsLaBpfO = false;}
      if(zcofxGPDPO == true){zcofxGPDPO = false;}
      if(FdHoBBhlOD == true){FdHoBBhlOD = false;}
      if(TlaTriYHGU == true){TlaTriYHGU = false;}
      if(YWJxmSKcRH == true){YWJxmSKcRH = false;}
      if(OdmzPYpcrJ == true){OdmzPYpcrJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FVVKYDRGPQ
{ 
  void aBXSKHjmqb()
  { 
      bool featILwDAy = false;
      bool NhtaneVkVn = false;
      bool seSlesJXBn = false;
      bool EiAPGTyaPy = false;
      bool NPaFUcbKGC = false;
      bool XtTIcBMnPP = false;
      bool CXCLsegeTU = false;
      bool gtUWacDNRC = false;
      bool QyQzQKPqmF = false;
      bool HJLzwoMOMp = false;
      bool uxqlUcYwgz = false;
      bool xzWNyDGDui = false;
      bool OoqNNXiUal = false;
      bool QoBaGTHedn = false;
      bool kTKmIIlxBr = false;
      bool hITcaFFcYw = false;
      bool sDUuiIxuGe = false;
      bool ubYHyueEEF = false;
      bool llThDHUXAB = false;
      bool NeGgtgyOEA = false;
      string duVlxwdBSI;
      string RCtADZgiIF;
      string jySUuBYxan;
      string EwohfdMbMQ;
      string jskFbtlULC;
      string dUzUOecBqu;
      string XgaeDVNMUZ;
      string MFWqVqMMrB;
      string PDkXKjwTSA;
      string BLkQsDRGCG;
      string fYAloXyHyW;
      string SPIofTuCTT;
      string YssTXBTGyS;
      string YFJlUpDzil;
      string koUuhkCujY;
      string HPlihlffNm;
      string EqJfyMFWUo;
      string PuThhjXxkl;
      string zYVYKJTaDh;
      string KWlugseoxV;
      if(duVlxwdBSI == fYAloXyHyW){featILwDAy = true;}
      else if(fYAloXyHyW == duVlxwdBSI){uxqlUcYwgz = true;}
      if(RCtADZgiIF == SPIofTuCTT){NhtaneVkVn = true;}
      else if(SPIofTuCTT == RCtADZgiIF){xzWNyDGDui = true;}
      if(jySUuBYxan == YssTXBTGyS){seSlesJXBn = true;}
      else if(YssTXBTGyS == jySUuBYxan){OoqNNXiUal = true;}
      if(EwohfdMbMQ == YFJlUpDzil){EiAPGTyaPy = true;}
      else if(YFJlUpDzil == EwohfdMbMQ){QoBaGTHedn = true;}
      if(jskFbtlULC == koUuhkCujY){NPaFUcbKGC = true;}
      else if(koUuhkCujY == jskFbtlULC){kTKmIIlxBr = true;}
      if(dUzUOecBqu == HPlihlffNm){XtTIcBMnPP = true;}
      else if(HPlihlffNm == dUzUOecBqu){hITcaFFcYw = true;}
      if(XgaeDVNMUZ == EqJfyMFWUo){CXCLsegeTU = true;}
      else if(EqJfyMFWUo == XgaeDVNMUZ){sDUuiIxuGe = true;}
      if(MFWqVqMMrB == PuThhjXxkl){gtUWacDNRC = true;}
      if(PDkXKjwTSA == zYVYKJTaDh){QyQzQKPqmF = true;}
      if(BLkQsDRGCG == KWlugseoxV){HJLzwoMOMp = true;}
      while(PuThhjXxkl == MFWqVqMMrB){ubYHyueEEF = true;}
      while(zYVYKJTaDh == zYVYKJTaDh){llThDHUXAB = true;}
      while(KWlugseoxV == KWlugseoxV){NeGgtgyOEA = true;}
      if(featILwDAy == true){featILwDAy = false;}
      if(NhtaneVkVn == true){NhtaneVkVn = false;}
      if(seSlesJXBn == true){seSlesJXBn = false;}
      if(EiAPGTyaPy == true){EiAPGTyaPy = false;}
      if(NPaFUcbKGC == true){NPaFUcbKGC = false;}
      if(XtTIcBMnPP == true){XtTIcBMnPP = false;}
      if(CXCLsegeTU == true){CXCLsegeTU = false;}
      if(gtUWacDNRC == true){gtUWacDNRC = false;}
      if(QyQzQKPqmF == true){QyQzQKPqmF = false;}
      if(HJLzwoMOMp == true){HJLzwoMOMp = false;}
      if(uxqlUcYwgz == true){uxqlUcYwgz = false;}
      if(xzWNyDGDui == true){xzWNyDGDui = false;}
      if(OoqNNXiUal == true){OoqNNXiUal = false;}
      if(QoBaGTHedn == true){QoBaGTHedn = false;}
      if(kTKmIIlxBr == true){kTKmIIlxBr = false;}
      if(hITcaFFcYw == true){hITcaFFcYw = false;}
      if(sDUuiIxuGe == true){sDUuiIxuGe = false;}
      if(ubYHyueEEF == true){ubYHyueEEF = false;}
      if(llThDHUXAB == true){llThDHUXAB = false;}
      if(NeGgtgyOEA == true){NeGgtgyOEA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HGEEPXYFCB
{ 
  void ghesxMhRIs()
  { 
      bool lzYqrgfjcE = false;
      bool YklPsngmfH = false;
      bool fuqjZHstUK = false;
      bool CnMjLYjTMB = false;
      bool tjYpxnFyLc = false;
      bool bPJWqqIoRk = false;
      bool mkPRCkXBDT = false;
      bool ENaeMwVBlk = false;
      bool CuirileprU = false;
      bool QtCaNJUHmM = false;
      bool QDtqYNodJu = false;
      bool UHDgirCWhP = false;
      bool FhIhDJLzQD = false;
      bool aONYUyAqTU = false;
      bool xAgwAIqUrV = false;
      bool GyYWGhtMnO = false;
      bool CoMFUGtdLj = false;
      bool qKCMSEAMht = false;
      bool RpGuwbopRl = false;
      bool EnDFRInabt = false;
      string uQdJLpxwmJ;
      string onGfNbIhud;
      string plCUQXsmUm;
      string qASBcwmFjX;
      string ieWjCFmeNS;
      string ntNezJOJrn;
      string xJazRoUFCQ;
      string nCyWuKORSL;
      string kNZCzxmmBT;
      string hcNuaYEWRM;
      string jgcxdlupjo;
      string txqgDijXAU;
      string CgEhiKnDwV;
      string GrzFaDkbXN;
      string BwDMZjlfqq;
      string nfWwKDctOS;
      string xrsNhBylGA;
      string yHAlTFdqIy;
      string YILFhaUCuW;
      string ZqNFQIDodX;
      if(uQdJLpxwmJ == jgcxdlupjo){lzYqrgfjcE = true;}
      else if(jgcxdlupjo == uQdJLpxwmJ){QDtqYNodJu = true;}
      if(onGfNbIhud == txqgDijXAU){YklPsngmfH = true;}
      else if(txqgDijXAU == onGfNbIhud){UHDgirCWhP = true;}
      if(plCUQXsmUm == CgEhiKnDwV){fuqjZHstUK = true;}
      else if(CgEhiKnDwV == plCUQXsmUm){FhIhDJLzQD = true;}
      if(qASBcwmFjX == GrzFaDkbXN){CnMjLYjTMB = true;}
      else if(GrzFaDkbXN == qASBcwmFjX){aONYUyAqTU = true;}
      if(ieWjCFmeNS == BwDMZjlfqq){tjYpxnFyLc = true;}
      else if(BwDMZjlfqq == ieWjCFmeNS){xAgwAIqUrV = true;}
      if(ntNezJOJrn == nfWwKDctOS){bPJWqqIoRk = true;}
      else if(nfWwKDctOS == ntNezJOJrn){GyYWGhtMnO = true;}
      if(xJazRoUFCQ == xrsNhBylGA){mkPRCkXBDT = true;}
      else if(xrsNhBylGA == xJazRoUFCQ){CoMFUGtdLj = true;}
      if(nCyWuKORSL == yHAlTFdqIy){ENaeMwVBlk = true;}
      if(kNZCzxmmBT == YILFhaUCuW){CuirileprU = true;}
      if(hcNuaYEWRM == ZqNFQIDodX){QtCaNJUHmM = true;}
      while(yHAlTFdqIy == nCyWuKORSL){qKCMSEAMht = true;}
      while(YILFhaUCuW == YILFhaUCuW){RpGuwbopRl = true;}
      while(ZqNFQIDodX == ZqNFQIDodX){EnDFRInabt = true;}
      if(lzYqrgfjcE == true){lzYqrgfjcE = false;}
      if(YklPsngmfH == true){YklPsngmfH = false;}
      if(fuqjZHstUK == true){fuqjZHstUK = false;}
      if(CnMjLYjTMB == true){CnMjLYjTMB = false;}
      if(tjYpxnFyLc == true){tjYpxnFyLc = false;}
      if(bPJWqqIoRk == true){bPJWqqIoRk = false;}
      if(mkPRCkXBDT == true){mkPRCkXBDT = false;}
      if(ENaeMwVBlk == true){ENaeMwVBlk = false;}
      if(CuirileprU == true){CuirileprU = false;}
      if(QtCaNJUHmM == true){QtCaNJUHmM = false;}
      if(QDtqYNodJu == true){QDtqYNodJu = false;}
      if(UHDgirCWhP == true){UHDgirCWhP = false;}
      if(FhIhDJLzQD == true){FhIhDJLzQD = false;}
      if(aONYUyAqTU == true){aONYUyAqTU = false;}
      if(xAgwAIqUrV == true){xAgwAIqUrV = false;}
      if(GyYWGhtMnO == true){GyYWGhtMnO = false;}
      if(CoMFUGtdLj == true){CoMFUGtdLj = false;}
      if(qKCMSEAMht == true){qKCMSEAMht = false;}
      if(RpGuwbopRl == true){RpGuwbopRl = false;}
      if(EnDFRInabt == true){EnDFRInabt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPUVUKVLUT
{ 
  void KDPOnbkBXX()
  { 
      bool ghXwJTtUKS = false;
      bool KQtjaUXsBn = false;
      bool lJzjPBJaFn = false;
      bool utaqdKLBil = false;
      bool mCzWJAganK = false;
      bool AdrzgXingI = false;
      bool JTPVWQpCFQ = false;
      bool IVKPAiKcaP = false;
      bool UiltnRBbJG = false;
      bool bWTZbTmczr = false;
      bool JdUXCdSbyx = false;
      bool MGNRmagUhF = false;
      bool PNszolCjng = false;
      bool wgchFpOOrK = false;
      bool yYcLsVJCmA = false;
      bool lSutcukVhP = false;
      bool binRBfceMw = false;
      bool MRbXGpkgFT = false;
      bool bAxmtdlhFJ = false;
      bool FrfbhPjKJN = false;
      string wDaXAXnMqP;
      string dJkcoHnPKT;
      string nAmPrWkuOY;
      string TXPQQVAdih;
      string JJtaWjXIds;
      string ZdtLSwPKec;
      string lsxSwGtULT;
      string HKgbJeFMrI;
      string zcRVypcDxU;
      string FpyGwPLadP;
      string oCwKlPwSBn;
      string pDRWcJbaUG;
      string dpWpNQLaft;
      string SehbSwfHji;
      string sKCIeCXbcm;
      string nkGXlzeFwU;
      string DVlHVKUoDf;
      string cUpkMTnOLL;
      string sixsFhXKpT;
      string QaKPeXXtmT;
      if(wDaXAXnMqP == oCwKlPwSBn){ghXwJTtUKS = true;}
      else if(oCwKlPwSBn == wDaXAXnMqP){JdUXCdSbyx = true;}
      if(dJkcoHnPKT == pDRWcJbaUG){KQtjaUXsBn = true;}
      else if(pDRWcJbaUG == dJkcoHnPKT){MGNRmagUhF = true;}
      if(nAmPrWkuOY == dpWpNQLaft){lJzjPBJaFn = true;}
      else if(dpWpNQLaft == nAmPrWkuOY){PNszolCjng = true;}
      if(TXPQQVAdih == SehbSwfHji){utaqdKLBil = true;}
      else if(SehbSwfHji == TXPQQVAdih){wgchFpOOrK = true;}
      if(JJtaWjXIds == sKCIeCXbcm){mCzWJAganK = true;}
      else if(sKCIeCXbcm == JJtaWjXIds){yYcLsVJCmA = true;}
      if(ZdtLSwPKec == nkGXlzeFwU){AdrzgXingI = true;}
      else if(nkGXlzeFwU == ZdtLSwPKec){lSutcukVhP = true;}
      if(lsxSwGtULT == DVlHVKUoDf){JTPVWQpCFQ = true;}
      else if(DVlHVKUoDf == lsxSwGtULT){binRBfceMw = true;}
      if(HKgbJeFMrI == cUpkMTnOLL){IVKPAiKcaP = true;}
      if(zcRVypcDxU == sixsFhXKpT){UiltnRBbJG = true;}
      if(FpyGwPLadP == QaKPeXXtmT){bWTZbTmczr = true;}
      while(cUpkMTnOLL == HKgbJeFMrI){MRbXGpkgFT = true;}
      while(sixsFhXKpT == sixsFhXKpT){bAxmtdlhFJ = true;}
      while(QaKPeXXtmT == QaKPeXXtmT){FrfbhPjKJN = true;}
      if(ghXwJTtUKS == true){ghXwJTtUKS = false;}
      if(KQtjaUXsBn == true){KQtjaUXsBn = false;}
      if(lJzjPBJaFn == true){lJzjPBJaFn = false;}
      if(utaqdKLBil == true){utaqdKLBil = false;}
      if(mCzWJAganK == true){mCzWJAganK = false;}
      if(AdrzgXingI == true){AdrzgXingI = false;}
      if(JTPVWQpCFQ == true){JTPVWQpCFQ = false;}
      if(IVKPAiKcaP == true){IVKPAiKcaP = false;}
      if(UiltnRBbJG == true){UiltnRBbJG = false;}
      if(bWTZbTmczr == true){bWTZbTmczr = false;}
      if(JdUXCdSbyx == true){JdUXCdSbyx = false;}
      if(MGNRmagUhF == true){MGNRmagUhF = false;}
      if(PNszolCjng == true){PNszolCjng = false;}
      if(wgchFpOOrK == true){wgchFpOOrK = false;}
      if(yYcLsVJCmA == true){yYcLsVJCmA = false;}
      if(lSutcukVhP == true){lSutcukVhP = false;}
      if(binRBfceMw == true){binRBfceMw = false;}
      if(MRbXGpkgFT == true){MRbXGpkgFT = false;}
      if(bAxmtdlhFJ == true){bAxmtdlhFJ = false;}
      if(FrfbhPjKJN == true){FrfbhPjKJN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PADZPHPLRJ
{ 
  void uyoBuOkrAe()
  { 
      bool gsrxmOfzpH = false;
      bool jKZGTNgCwg = false;
      bool ZaOpBpnnMZ = false;
      bool KfGHSBNVnz = false;
      bool yrXfhhjZkJ = false;
      bool xmXUwGdCww = false;
      bool ZqmQxEDSnS = false;
      bool AKNxihCiHS = false;
      bool FOCCcXIlKL = false;
      bool WLZrYGFHid = false;
      bool eRlSImYZlO = false;
      bool DutdpLnjmZ = false;
      bool wRHbuojUXb = false;
      bool buzdnncjsp = false;
      bool yhzwHaQwCN = false;
      bool SVTJgMKJWT = false;
      bool CECJlIwPpC = false;
      bool hDpxaNRLTU = false;
      bool XnSJJGboxa = false;
      bool cSNZmtfpJz = false;
      string XYukCMHJKi;
      string FHhNwFRObE;
      string PrnZDsJjVQ;
      string KamhMFRuGH;
      string OZFBEjqXTu;
      string xTNyEejUgI;
      string CWmtXeTAAq;
      string nVIUoollVT;
      string ClPaSpMncg;
      string UwOxEqlLcZ;
      string PpWcGaLsJO;
      string syzMGQHMbh;
      string SeWSWrHKPy;
      string DaJuDLOlTq;
      string dSeNnWxBqn;
      string jYitHkSEGO;
      string TAdKLRoDJt;
      string BUsjEzAIdA;
      string tFTbOdqOnS;
      string sKfEXdoTCW;
      if(XYukCMHJKi == PpWcGaLsJO){gsrxmOfzpH = true;}
      else if(PpWcGaLsJO == XYukCMHJKi){eRlSImYZlO = true;}
      if(FHhNwFRObE == syzMGQHMbh){jKZGTNgCwg = true;}
      else if(syzMGQHMbh == FHhNwFRObE){DutdpLnjmZ = true;}
      if(PrnZDsJjVQ == SeWSWrHKPy){ZaOpBpnnMZ = true;}
      else if(SeWSWrHKPy == PrnZDsJjVQ){wRHbuojUXb = true;}
      if(KamhMFRuGH == DaJuDLOlTq){KfGHSBNVnz = true;}
      else if(DaJuDLOlTq == KamhMFRuGH){buzdnncjsp = true;}
      if(OZFBEjqXTu == dSeNnWxBqn){yrXfhhjZkJ = true;}
      else if(dSeNnWxBqn == OZFBEjqXTu){yhzwHaQwCN = true;}
      if(xTNyEejUgI == jYitHkSEGO){xmXUwGdCww = true;}
      else if(jYitHkSEGO == xTNyEejUgI){SVTJgMKJWT = true;}
      if(CWmtXeTAAq == TAdKLRoDJt){ZqmQxEDSnS = true;}
      else if(TAdKLRoDJt == CWmtXeTAAq){CECJlIwPpC = true;}
      if(nVIUoollVT == BUsjEzAIdA){AKNxihCiHS = true;}
      if(ClPaSpMncg == tFTbOdqOnS){FOCCcXIlKL = true;}
      if(UwOxEqlLcZ == sKfEXdoTCW){WLZrYGFHid = true;}
      while(BUsjEzAIdA == nVIUoollVT){hDpxaNRLTU = true;}
      while(tFTbOdqOnS == tFTbOdqOnS){XnSJJGboxa = true;}
      while(sKfEXdoTCW == sKfEXdoTCW){cSNZmtfpJz = true;}
      if(gsrxmOfzpH == true){gsrxmOfzpH = false;}
      if(jKZGTNgCwg == true){jKZGTNgCwg = false;}
      if(ZaOpBpnnMZ == true){ZaOpBpnnMZ = false;}
      if(KfGHSBNVnz == true){KfGHSBNVnz = false;}
      if(yrXfhhjZkJ == true){yrXfhhjZkJ = false;}
      if(xmXUwGdCww == true){xmXUwGdCww = false;}
      if(ZqmQxEDSnS == true){ZqmQxEDSnS = false;}
      if(AKNxihCiHS == true){AKNxihCiHS = false;}
      if(FOCCcXIlKL == true){FOCCcXIlKL = false;}
      if(WLZrYGFHid == true){WLZrYGFHid = false;}
      if(eRlSImYZlO == true){eRlSImYZlO = false;}
      if(DutdpLnjmZ == true){DutdpLnjmZ = false;}
      if(wRHbuojUXb == true){wRHbuojUXb = false;}
      if(buzdnncjsp == true){buzdnncjsp = false;}
      if(yhzwHaQwCN == true){yhzwHaQwCN = false;}
      if(SVTJgMKJWT == true){SVTJgMKJWT = false;}
      if(CECJlIwPpC == true){CECJlIwPpC = false;}
      if(hDpxaNRLTU == true){hDpxaNRLTU = false;}
      if(XnSJJGboxa == true){XnSJJGboxa = false;}
      if(cSNZmtfpJz == true){cSNZmtfpJz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMQDBCXBJZ
{ 
  void dIudpRLgyM()
  { 
      bool lpxRhgdqCm = false;
      bool HaQDWNfAUt = false;
      bool SJjTnqbUqn = false;
      bool yIpnNfbRwQ = false;
      bool PMqBrmqSwH = false;
      bool TDHAGbFdcq = false;
      bool EIAOoykbpp = false;
      bool kOEEdFSiaA = false;
      bool zJYjTuBohk = false;
      bool axnELGMcLt = false;
      bool COcFVFyCWA = false;
      bool JWDbqujPtt = false;
      bool wutEPmZzsW = false;
      bool roWgxjgSNO = false;
      bool wySgbDtLNQ = false;
      bool WwiQxGUXoi = false;
      bool fyJzHTzVdG = false;
      bool NRCexycMcL = false;
      bool rNlbAuGFjq = false;
      bool PJceiyoSYI = false;
      string ihykbQUYtm;
      string ytTkShWkCf;
      string wRMoKqFddk;
      string BoXPuzcDib;
      string wPhgjtjeLk;
      string yTQfgQUJak;
      string KquIlJWDpT;
      string FTBaigifFP;
      string HaRsmhYqie;
      string dSbyQFUZua;
      string XforedSowA;
      string goDLdjYCVD;
      string keTKolqDKd;
      string MJkerakZNI;
      string PitixoPQTf;
      string fSEqorMdDs;
      string mOeSnXDYTC;
      string yznMnBkkNz;
      string WZidxsEsoz;
      string OHWTUADbuY;
      if(ihykbQUYtm == XforedSowA){lpxRhgdqCm = true;}
      else if(XforedSowA == ihykbQUYtm){COcFVFyCWA = true;}
      if(ytTkShWkCf == goDLdjYCVD){HaQDWNfAUt = true;}
      else if(goDLdjYCVD == ytTkShWkCf){JWDbqujPtt = true;}
      if(wRMoKqFddk == keTKolqDKd){SJjTnqbUqn = true;}
      else if(keTKolqDKd == wRMoKqFddk){wutEPmZzsW = true;}
      if(BoXPuzcDib == MJkerakZNI){yIpnNfbRwQ = true;}
      else if(MJkerakZNI == BoXPuzcDib){roWgxjgSNO = true;}
      if(wPhgjtjeLk == PitixoPQTf){PMqBrmqSwH = true;}
      else if(PitixoPQTf == wPhgjtjeLk){wySgbDtLNQ = true;}
      if(yTQfgQUJak == fSEqorMdDs){TDHAGbFdcq = true;}
      else if(fSEqorMdDs == yTQfgQUJak){WwiQxGUXoi = true;}
      if(KquIlJWDpT == mOeSnXDYTC){EIAOoykbpp = true;}
      else if(mOeSnXDYTC == KquIlJWDpT){fyJzHTzVdG = true;}
      if(FTBaigifFP == yznMnBkkNz){kOEEdFSiaA = true;}
      if(HaRsmhYqie == WZidxsEsoz){zJYjTuBohk = true;}
      if(dSbyQFUZua == OHWTUADbuY){axnELGMcLt = true;}
      while(yznMnBkkNz == FTBaigifFP){NRCexycMcL = true;}
      while(WZidxsEsoz == WZidxsEsoz){rNlbAuGFjq = true;}
      while(OHWTUADbuY == OHWTUADbuY){PJceiyoSYI = true;}
      if(lpxRhgdqCm == true){lpxRhgdqCm = false;}
      if(HaQDWNfAUt == true){HaQDWNfAUt = false;}
      if(SJjTnqbUqn == true){SJjTnqbUqn = false;}
      if(yIpnNfbRwQ == true){yIpnNfbRwQ = false;}
      if(PMqBrmqSwH == true){PMqBrmqSwH = false;}
      if(TDHAGbFdcq == true){TDHAGbFdcq = false;}
      if(EIAOoykbpp == true){EIAOoykbpp = false;}
      if(kOEEdFSiaA == true){kOEEdFSiaA = false;}
      if(zJYjTuBohk == true){zJYjTuBohk = false;}
      if(axnELGMcLt == true){axnELGMcLt = false;}
      if(COcFVFyCWA == true){COcFVFyCWA = false;}
      if(JWDbqujPtt == true){JWDbqujPtt = false;}
      if(wutEPmZzsW == true){wutEPmZzsW = false;}
      if(roWgxjgSNO == true){roWgxjgSNO = false;}
      if(wySgbDtLNQ == true){wySgbDtLNQ = false;}
      if(WwiQxGUXoi == true){WwiQxGUXoi = false;}
      if(fyJzHTzVdG == true){fyJzHTzVdG = false;}
      if(NRCexycMcL == true){NRCexycMcL = false;}
      if(rNlbAuGFjq == true){rNlbAuGFjq = false;}
      if(PJceiyoSYI == true){PJceiyoSYI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTMJFPLFZI
{ 
  void TekfgmTulw()
  { 
      bool xZHlxXZxob = false;
      bool FJKwMYrbnU = false;
      bool CqVPCtmYQJ = false;
      bool UtXkCZnfPV = false;
      bool aKaNIzkQag = false;
      bool QQDuiGEqiD = false;
      bool kAgfHKlYsl = false;
      bool jMMStrQHHD = false;
      bool IWyisDqbCw = false;
      bool VwwLkZdtGx = false;
      bool MMWnwDDkBq = false;
      bool owjftNCxlD = false;
      bool TJVwQnPAgT = false;
      bool NVAJpwAJmo = false;
      bool zGaLHYMPRX = false;
      bool XgICdCpZWI = false;
      bool nDEhcTuZpy = false;
      bool NrJxDNiKoq = false;
      bool aAiIwfNxfm = false;
      bool GZldBwCrhm = false;
      string NceROhaRPa;
      string scDTRsksKI;
      string whjXPRjEGp;
      string yWjlPchcND;
      string GKpUHAnFqI;
      string MFxFsfsGCw;
      string xWKZcVrREo;
      string LIfGClrOQP;
      string ddMxcrYdrj;
      string iaZQGizPrl;
      string HWBCxDZpCH;
      string mdpmSSKMwj;
      string wOYTFkiPAT;
      string lbWeHGcJAZ;
      string SiakwEkmxm;
      string YlTHosxgxM;
      string UJoiUKHKeL;
      string oAMVRNmnWA;
      string zuRNtAIPoO;
      string JuMmFIsrPl;
      if(NceROhaRPa == HWBCxDZpCH){xZHlxXZxob = true;}
      else if(HWBCxDZpCH == NceROhaRPa){MMWnwDDkBq = true;}
      if(scDTRsksKI == mdpmSSKMwj){FJKwMYrbnU = true;}
      else if(mdpmSSKMwj == scDTRsksKI){owjftNCxlD = true;}
      if(whjXPRjEGp == wOYTFkiPAT){CqVPCtmYQJ = true;}
      else if(wOYTFkiPAT == whjXPRjEGp){TJVwQnPAgT = true;}
      if(yWjlPchcND == lbWeHGcJAZ){UtXkCZnfPV = true;}
      else if(lbWeHGcJAZ == yWjlPchcND){NVAJpwAJmo = true;}
      if(GKpUHAnFqI == SiakwEkmxm){aKaNIzkQag = true;}
      else if(SiakwEkmxm == GKpUHAnFqI){zGaLHYMPRX = true;}
      if(MFxFsfsGCw == YlTHosxgxM){QQDuiGEqiD = true;}
      else if(YlTHosxgxM == MFxFsfsGCw){XgICdCpZWI = true;}
      if(xWKZcVrREo == UJoiUKHKeL){kAgfHKlYsl = true;}
      else if(UJoiUKHKeL == xWKZcVrREo){nDEhcTuZpy = true;}
      if(LIfGClrOQP == oAMVRNmnWA){jMMStrQHHD = true;}
      if(ddMxcrYdrj == zuRNtAIPoO){IWyisDqbCw = true;}
      if(iaZQGizPrl == JuMmFIsrPl){VwwLkZdtGx = true;}
      while(oAMVRNmnWA == LIfGClrOQP){NrJxDNiKoq = true;}
      while(zuRNtAIPoO == zuRNtAIPoO){aAiIwfNxfm = true;}
      while(JuMmFIsrPl == JuMmFIsrPl){GZldBwCrhm = true;}
      if(xZHlxXZxob == true){xZHlxXZxob = false;}
      if(FJKwMYrbnU == true){FJKwMYrbnU = false;}
      if(CqVPCtmYQJ == true){CqVPCtmYQJ = false;}
      if(UtXkCZnfPV == true){UtXkCZnfPV = false;}
      if(aKaNIzkQag == true){aKaNIzkQag = false;}
      if(QQDuiGEqiD == true){QQDuiGEqiD = false;}
      if(kAgfHKlYsl == true){kAgfHKlYsl = false;}
      if(jMMStrQHHD == true){jMMStrQHHD = false;}
      if(IWyisDqbCw == true){IWyisDqbCw = false;}
      if(VwwLkZdtGx == true){VwwLkZdtGx = false;}
      if(MMWnwDDkBq == true){MMWnwDDkBq = false;}
      if(owjftNCxlD == true){owjftNCxlD = false;}
      if(TJVwQnPAgT == true){TJVwQnPAgT = false;}
      if(NVAJpwAJmo == true){NVAJpwAJmo = false;}
      if(zGaLHYMPRX == true){zGaLHYMPRX = false;}
      if(XgICdCpZWI == true){XgICdCpZWI = false;}
      if(nDEhcTuZpy == true){nDEhcTuZpy = false;}
      if(NrJxDNiKoq == true){NrJxDNiKoq = false;}
      if(aAiIwfNxfm == true){aAiIwfNxfm = false;}
      if(GZldBwCrhm == true){GZldBwCrhm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHYNEDHTUW
{ 
  void Xjkojdieml()
  { 
      bool yoecHYxLVb = false;
      bool dRBwyKbRCW = false;
      bool wyFhmCHxLA = false;
      bool HucuJGQKwm = false;
      bool zmaYLydxHl = false;
      bool YERPfzjwpF = false;
      bool RzAVUioFmr = false;
      bool tRUPXJXfWo = false;
      bool XKoYbDcMPJ = false;
      bool VTTpVAlFEb = false;
      bool IYJPqGiCrW = false;
      bool bDZBgGJbsR = false;
      bool FbpcVaxdsX = false;
      bool WRbtfzAZgU = false;
      bool TaUrhStSIP = false;
      bool pJLlWfhgsQ = false;
      bool IEJUzJbeVh = false;
      bool GitYxeHxuD = false;
      bool geUdgNGoXz = false;
      bool RTgPLORzsX = false;
      string YDZGDxXTAL;
      string bnpkBEOiXj;
      string EHZgPBfVab;
      string nAAuDnCChw;
      string YzFNBizDSn;
      string RlrNWQcspC;
      string QBrXWbnuhN;
      string BLAaKECLeg;
      string BbCmKCImYl;
      string LJMffXGhqY;
      string uEVFlFkQCR;
      string OQNJAoyFMT;
      string TAWuCrzTum;
      string yTUGkxGxBE;
      string RqjGXtwDfp;
      string ZBUXEthZDt;
      string GQVPTuwGXC;
      string iBEIBcQPXH;
      string uunEMwyxBp;
      string PfsGxBVUmb;
      if(YDZGDxXTAL == uEVFlFkQCR){yoecHYxLVb = true;}
      else if(uEVFlFkQCR == YDZGDxXTAL){IYJPqGiCrW = true;}
      if(bnpkBEOiXj == OQNJAoyFMT){dRBwyKbRCW = true;}
      else if(OQNJAoyFMT == bnpkBEOiXj){bDZBgGJbsR = true;}
      if(EHZgPBfVab == TAWuCrzTum){wyFhmCHxLA = true;}
      else if(TAWuCrzTum == EHZgPBfVab){FbpcVaxdsX = true;}
      if(nAAuDnCChw == yTUGkxGxBE){HucuJGQKwm = true;}
      else if(yTUGkxGxBE == nAAuDnCChw){WRbtfzAZgU = true;}
      if(YzFNBizDSn == RqjGXtwDfp){zmaYLydxHl = true;}
      else if(RqjGXtwDfp == YzFNBizDSn){TaUrhStSIP = true;}
      if(RlrNWQcspC == ZBUXEthZDt){YERPfzjwpF = true;}
      else if(ZBUXEthZDt == RlrNWQcspC){pJLlWfhgsQ = true;}
      if(QBrXWbnuhN == GQVPTuwGXC){RzAVUioFmr = true;}
      else if(GQVPTuwGXC == QBrXWbnuhN){IEJUzJbeVh = true;}
      if(BLAaKECLeg == iBEIBcQPXH){tRUPXJXfWo = true;}
      if(BbCmKCImYl == uunEMwyxBp){XKoYbDcMPJ = true;}
      if(LJMffXGhqY == PfsGxBVUmb){VTTpVAlFEb = true;}
      while(iBEIBcQPXH == BLAaKECLeg){GitYxeHxuD = true;}
      while(uunEMwyxBp == uunEMwyxBp){geUdgNGoXz = true;}
      while(PfsGxBVUmb == PfsGxBVUmb){RTgPLORzsX = true;}
      if(yoecHYxLVb == true){yoecHYxLVb = false;}
      if(dRBwyKbRCW == true){dRBwyKbRCW = false;}
      if(wyFhmCHxLA == true){wyFhmCHxLA = false;}
      if(HucuJGQKwm == true){HucuJGQKwm = false;}
      if(zmaYLydxHl == true){zmaYLydxHl = false;}
      if(YERPfzjwpF == true){YERPfzjwpF = false;}
      if(RzAVUioFmr == true){RzAVUioFmr = false;}
      if(tRUPXJXfWo == true){tRUPXJXfWo = false;}
      if(XKoYbDcMPJ == true){XKoYbDcMPJ = false;}
      if(VTTpVAlFEb == true){VTTpVAlFEb = false;}
      if(IYJPqGiCrW == true){IYJPqGiCrW = false;}
      if(bDZBgGJbsR == true){bDZBgGJbsR = false;}
      if(FbpcVaxdsX == true){FbpcVaxdsX = false;}
      if(WRbtfzAZgU == true){WRbtfzAZgU = false;}
      if(TaUrhStSIP == true){TaUrhStSIP = false;}
      if(pJLlWfhgsQ == true){pJLlWfhgsQ = false;}
      if(IEJUzJbeVh == true){IEJUzJbeVh = false;}
      if(GitYxeHxuD == true){GitYxeHxuD = false;}
      if(geUdgNGoXz == true){geUdgNGoXz = false;}
      if(RTgPLORzsX == true){RTgPLORzsX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOVWJQHFNL
{ 
  void BwBctDonzH()
  { 
      bool TbuowzohtM = false;
      bool VQOluJfGGr = false;
      bool lsjyDVKYNl = false;
      bool WVNFLuueVw = false;
      bool ltoXFYsqus = false;
      bool eGOoGZqwka = false;
      bool oPTHpzCJaz = false;
      bool OAjJGqELre = false;
      bool cSdTHPHXyk = false;
      bool EytuHVZghF = false;
      bool ViQuedWFiP = false;
      bool VfEGxVlzAZ = false;
      bool rdKouPGoBj = false;
      bool QWdlIsChod = false;
      bool sBoiPXtmxl = false;
      bool jagHNqYazP = false;
      bool WgDzyzBRxE = false;
      bool SDKVgpobYW = false;
      bool USqPzpoVYR = false;
      bool UaiYHLypjQ = false;
      string rhLqWpncJS;
      string QnMjLdEMXO;
      string PFADPRFMFW;
      string wmNOihIKhH;
      string CDIXyBGTWH;
      string GghBMlgIbE;
      string jbWmWcayBc;
      string UtePMMxbEO;
      string KlpxQOFMBw;
      string BAicXafVAV;
      string aIRsmLCRnA;
      string oEDNtxkZVI;
      string XNwFbTLCrl;
      string gbbinBUwJE;
      string LmXBGwwUhZ;
      string oFzrxMLMRS;
      string AAYCTNcUZs;
      string coPRxkpuye;
      string WpTSwabikb;
      string oHdqDKNUhs;
      if(rhLqWpncJS == aIRsmLCRnA){TbuowzohtM = true;}
      else if(aIRsmLCRnA == rhLqWpncJS){ViQuedWFiP = true;}
      if(QnMjLdEMXO == oEDNtxkZVI){VQOluJfGGr = true;}
      else if(oEDNtxkZVI == QnMjLdEMXO){VfEGxVlzAZ = true;}
      if(PFADPRFMFW == XNwFbTLCrl){lsjyDVKYNl = true;}
      else if(XNwFbTLCrl == PFADPRFMFW){rdKouPGoBj = true;}
      if(wmNOihIKhH == gbbinBUwJE){WVNFLuueVw = true;}
      else if(gbbinBUwJE == wmNOihIKhH){QWdlIsChod = true;}
      if(CDIXyBGTWH == LmXBGwwUhZ){ltoXFYsqus = true;}
      else if(LmXBGwwUhZ == CDIXyBGTWH){sBoiPXtmxl = true;}
      if(GghBMlgIbE == oFzrxMLMRS){eGOoGZqwka = true;}
      else if(oFzrxMLMRS == GghBMlgIbE){jagHNqYazP = true;}
      if(jbWmWcayBc == AAYCTNcUZs){oPTHpzCJaz = true;}
      else if(AAYCTNcUZs == jbWmWcayBc){WgDzyzBRxE = true;}
      if(UtePMMxbEO == coPRxkpuye){OAjJGqELre = true;}
      if(KlpxQOFMBw == WpTSwabikb){cSdTHPHXyk = true;}
      if(BAicXafVAV == oHdqDKNUhs){EytuHVZghF = true;}
      while(coPRxkpuye == UtePMMxbEO){SDKVgpobYW = true;}
      while(WpTSwabikb == WpTSwabikb){USqPzpoVYR = true;}
      while(oHdqDKNUhs == oHdqDKNUhs){UaiYHLypjQ = true;}
      if(TbuowzohtM == true){TbuowzohtM = false;}
      if(VQOluJfGGr == true){VQOluJfGGr = false;}
      if(lsjyDVKYNl == true){lsjyDVKYNl = false;}
      if(WVNFLuueVw == true){WVNFLuueVw = false;}
      if(ltoXFYsqus == true){ltoXFYsqus = false;}
      if(eGOoGZqwka == true){eGOoGZqwka = false;}
      if(oPTHpzCJaz == true){oPTHpzCJaz = false;}
      if(OAjJGqELre == true){OAjJGqELre = false;}
      if(cSdTHPHXyk == true){cSdTHPHXyk = false;}
      if(EytuHVZghF == true){EytuHVZghF = false;}
      if(ViQuedWFiP == true){ViQuedWFiP = false;}
      if(VfEGxVlzAZ == true){VfEGxVlzAZ = false;}
      if(rdKouPGoBj == true){rdKouPGoBj = false;}
      if(QWdlIsChod == true){QWdlIsChod = false;}
      if(sBoiPXtmxl == true){sBoiPXtmxl = false;}
      if(jagHNqYazP == true){jagHNqYazP = false;}
      if(WgDzyzBRxE == true){WgDzyzBRxE = false;}
      if(SDKVgpobYW == true){SDKVgpobYW = false;}
      if(USqPzpoVYR == true){USqPzpoVYR = false;}
      if(UaiYHLypjQ == true){UaiYHLypjQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFTQZRMFIZ
{ 
  void jQyoMpqwHd()
  { 
      bool QeMUuTWJin = false;
      bool TUTfiNeMpO = false;
      bool VywJYSbYcL = false;
      bool YHfSrhZGMY = false;
      bool jGjQlxOpuo = false;
      bool DHKFqRhCwb = false;
      bool rxfXOMnAnA = false;
      bool nYARePOfXa = false;
      bool EkdmHRxabZ = false;
      bool zXKkflZMBZ = false;
      bool JNCtBeHsZb = false;
      bool DCeUWHTsPx = false;
      bool OMYNBQOOkr = false;
      bool oBdxRphjlc = false;
      bool KDAAWxroNY = false;
      bool SgxEKwoorj = false;
      bool PrIglBXgCg = false;
      bool ZjHmlKMXpD = false;
      bool XZBLZIEZlV = false;
      bool ArqBMRuTNU = false;
      string pmHHMUOHgj;
      string RfGrabcwPM;
      string aOFPAlUOQb;
      string LVJaThNkRf;
      string argoLsoFXD;
      string HZIfjahrHa;
      string zzpFXuWeYr;
      string OrejlihPDG;
      string wPqNTlNdpr;
      string AVcpfaCbRQ;
      string WJgfnPuYsB;
      string rRnAdjIbkl;
      string hsofqsOnDK;
      string fGymjmhKYE;
      string pnjozigcMw;
      string RZpehcUAnu;
      string AHUiUlSBQq;
      string ByDgusIAgI;
      string MlbHrGPTEG;
      string RhWdDiTBTN;
      if(pmHHMUOHgj == WJgfnPuYsB){QeMUuTWJin = true;}
      else if(WJgfnPuYsB == pmHHMUOHgj){JNCtBeHsZb = true;}
      if(RfGrabcwPM == rRnAdjIbkl){TUTfiNeMpO = true;}
      else if(rRnAdjIbkl == RfGrabcwPM){DCeUWHTsPx = true;}
      if(aOFPAlUOQb == hsofqsOnDK){VywJYSbYcL = true;}
      else if(hsofqsOnDK == aOFPAlUOQb){OMYNBQOOkr = true;}
      if(LVJaThNkRf == fGymjmhKYE){YHfSrhZGMY = true;}
      else if(fGymjmhKYE == LVJaThNkRf){oBdxRphjlc = true;}
      if(argoLsoFXD == pnjozigcMw){jGjQlxOpuo = true;}
      else if(pnjozigcMw == argoLsoFXD){KDAAWxroNY = true;}
      if(HZIfjahrHa == RZpehcUAnu){DHKFqRhCwb = true;}
      else if(RZpehcUAnu == HZIfjahrHa){SgxEKwoorj = true;}
      if(zzpFXuWeYr == AHUiUlSBQq){rxfXOMnAnA = true;}
      else if(AHUiUlSBQq == zzpFXuWeYr){PrIglBXgCg = true;}
      if(OrejlihPDG == ByDgusIAgI){nYARePOfXa = true;}
      if(wPqNTlNdpr == MlbHrGPTEG){EkdmHRxabZ = true;}
      if(AVcpfaCbRQ == RhWdDiTBTN){zXKkflZMBZ = true;}
      while(ByDgusIAgI == OrejlihPDG){ZjHmlKMXpD = true;}
      while(MlbHrGPTEG == MlbHrGPTEG){XZBLZIEZlV = true;}
      while(RhWdDiTBTN == RhWdDiTBTN){ArqBMRuTNU = true;}
      if(QeMUuTWJin == true){QeMUuTWJin = false;}
      if(TUTfiNeMpO == true){TUTfiNeMpO = false;}
      if(VywJYSbYcL == true){VywJYSbYcL = false;}
      if(YHfSrhZGMY == true){YHfSrhZGMY = false;}
      if(jGjQlxOpuo == true){jGjQlxOpuo = false;}
      if(DHKFqRhCwb == true){DHKFqRhCwb = false;}
      if(rxfXOMnAnA == true){rxfXOMnAnA = false;}
      if(nYARePOfXa == true){nYARePOfXa = false;}
      if(EkdmHRxabZ == true){EkdmHRxabZ = false;}
      if(zXKkflZMBZ == true){zXKkflZMBZ = false;}
      if(JNCtBeHsZb == true){JNCtBeHsZb = false;}
      if(DCeUWHTsPx == true){DCeUWHTsPx = false;}
      if(OMYNBQOOkr == true){OMYNBQOOkr = false;}
      if(oBdxRphjlc == true){oBdxRphjlc = false;}
      if(KDAAWxroNY == true){KDAAWxroNY = false;}
      if(SgxEKwoorj == true){SgxEKwoorj = false;}
      if(PrIglBXgCg == true){PrIglBXgCg = false;}
      if(ZjHmlKMXpD == true){ZjHmlKMXpD = false;}
      if(XZBLZIEZlV == true){XZBLZIEZlV = false;}
      if(ArqBMRuTNU == true){ArqBMRuTNU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCLKDEGHZB
{ 
  void UwapEFCeqY()
  { 
      bool pKZBVxiFCn = false;
      bool TOzqanifLf = false;
      bool KdMaaAdtRO = false;
      bool PMWHzxxNVB = false;
      bool hBSDGIVqSR = false;
      bool NWtUtMxzZU = false;
      bool TnmmYGqqrd = false;
      bool qVKKyIKITS = false;
      bool elbAArRCNm = false;
      bool zxmAhsOeez = false;
      bool RdynarLjVl = false;
      bool BofHpgLmlf = false;
      bool oodEdsiJcF = false;
      bool tedTAAmnZI = false;
      bool fggakKQeKA = false;
      bool gasyKcztJg = false;
      bool JCHPqVKMHp = false;
      bool sXNdzHHDST = false;
      bool bDzbYSleIX = false;
      bool AsdrzdZQiP = false;
      string DWmcJbBrAD;
      string xWKsPYcEPn;
      string Wujfeiotoe;
      string pUAChKdnhi;
      string srogdtQIRD;
      string AimOQIlHyZ;
      string lGDUNbVHKE;
      string uoWfueFDBj;
      string SgckdHhkkZ;
      string YVoHxmoUTB;
      string XIxMILMGTl;
      string CiFNHFcRqF;
      string tkWjeYzOiI;
      string okiAMJiQcS;
      string taRyWoQazr;
      string JXdNHllMgi;
      string MxXKxRzFBy;
      string VMnXLSSXNo;
      string IXOqyQHVrZ;
      string WVisGwDGBF;
      if(DWmcJbBrAD == XIxMILMGTl){pKZBVxiFCn = true;}
      else if(XIxMILMGTl == DWmcJbBrAD){RdynarLjVl = true;}
      if(xWKsPYcEPn == CiFNHFcRqF){TOzqanifLf = true;}
      else if(CiFNHFcRqF == xWKsPYcEPn){BofHpgLmlf = true;}
      if(Wujfeiotoe == tkWjeYzOiI){KdMaaAdtRO = true;}
      else if(tkWjeYzOiI == Wujfeiotoe){oodEdsiJcF = true;}
      if(pUAChKdnhi == okiAMJiQcS){PMWHzxxNVB = true;}
      else if(okiAMJiQcS == pUAChKdnhi){tedTAAmnZI = true;}
      if(srogdtQIRD == taRyWoQazr){hBSDGIVqSR = true;}
      else if(taRyWoQazr == srogdtQIRD){fggakKQeKA = true;}
      if(AimOQIlHyZ == JXdNHllMgi){NWtUtMxzZU = true;}
      else if(JXdNHllMgi == AimOQIlHyZ){gasyKcztJg = true;}
      if(lGDUNbVHKE == MxXKxRzFBy){TnmmYGqqrd = true;}
      else if(MxXKxRzFBy == lGDUNbVHKE){JCHPqVKMHp = true;}
      if(uoWfueFDBj == VMnXLSSXNo){qVKKyIKITS = true;}
      if(SgckdHhkkZ == IXOqyQHVrZ){elbAArRCNm = true;}
      if(YVoHxmoUTB == WVisGwDGBF){zxmAhsOeez = true;}
      while(VMnXLSSXNo == uoWfueFDBj){sXNdzHHDST = true;}
      while(IXOqyQHVrZ == IXOqyQHVrZ){bDzbYSleIX = true;}
      while(WVisGwDGBF == WVisGwDGBF){AsdrzdZQiP = true;}
      if(pKZBVxiFCn == true){pKZBVxiFCn = false;}
      if(TOzqanifLf == true){TOzqanifLf = false;}
      if(KdMaaAdtRO == true){KdMaaAdtRO = false;}
      if(PMWHzxxNVB == true){PMWHzxxNVB = false;}
      if(hBSDGIVqSR == true){hBSDGIVqSR = false;}
      if(NWtUtMxzZU == true){NWtUtMxzZU = false;}
      if(TnmmYGqqrd == true){TnmmYGqqrd = false;}
      if(qVKKyIKITS == true){qVKKyIKITS = false;}
      if(elbAArRCNm == true){elbAArRCNm = false;}
      if(zxmAhsOeez == true){zxmAhsOeez = false;}
      if(RdynarLjVl == true){RdynarLjVl = false;}
      if(BofHpgLmlf == true){BofHpgLmlf = false;}
      if(oodEdsiJcF == true){oodEdsiJcF = false;}
      if(tedTAAmnZI == true){tedTAAmnZI = false;}
      if(fggakKQeKA == true){fggakKQeKA = false;}
      if(gasyKcztJg == true){gasyKcztJg = false;}
      if(JCHPqVKMHp == true){JCHPqVKMHp = false;}
      if(sXNdzHHDST == true){sXNdzHHDST = false;}
      if(bDzbYSleIX == true){bDzbYSleIX = false;}
      if(AsdrzdZQiP == true){AsdrzdZQiP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUWIKESOCP
{ 
  void XkkVmNhLMZ()
  { 
      bool PEAXQIIWYg = false;
      bool NTEUMLsobI = false;
      bool gzxWiCEPHF = false;
      bool JlDbTakilW = false;
      bool mfRrBidNVA = false;
      bool CNnkkQGcoO = false;
      bool ErOTWbQcBk = false;
      bool aKDFUBhEVz = false;
      bool YqtHCwxRqD = false;
      bool UHsXRtRxVY = false;
      bool SALjZrKiQi = false;
      bool hCHppNyHQa = false;
      bool dylyQSQemZ = false;
      bool jjiwgXeKgK = false;
      bool kOBHVSADhD = false;
      bool wJguuUONTG = false;
      bool aeupzxSKJR = false;
      bool imZFoPwdcy = false;
      bool SNxicZCnBL = false;
      bool IQpajGTKIX = false;
      string wSxeEtoDqh;
      string XWJCILQAob;
      string PBYhsJzgDd;
      string USnCaFioOP;
      string dejkJYWWxb;
      string xFXgsusPku;
      string uIzMNEhGbC;
      string bblZxjRmYU;
      string lbiagPuHJf;
      string MTDTUVfWXE;
      string pPuuAVSyiJ;
      string dFqQISZYfx;
      string JaxwpIXSFa;
      string EtPTeVgmZK;
      string wwXzBGblKB;
      string uHqZtPSyEr;
      string xAsHFjpWll;
      string klyUBNCytj;
      string fkHDfwCpZO;
      string DhhhMuDQtR;
      if(wSxeEtoDqh == pPuuAVSyiJ){PEAXQIIWYg = true;}
      else if(pPuuAVSyiJ == wSxeEtoDqh){SALjZrKiQi = true;}
      if(XWJCILQAob == dFqQISZYfx){NTEUMLsobI = true;}
      else if(dFqQISZYfx == XWJCILQAob){hCHppNyHQa = true;}
      if(PBYhsJzgDd == JaxwpIXSFa){gzxWiCEPHF = true;}
      else if(JaxwpIXSFa == PBYhsJzgDd){dylyQSQemZ = true;}
      if(USnCaFioOP == EtPTeVgmZK){JlDbTakilW = true;}
      else if(EtPTeVgmZK == USnCaFioOP){jjiwgXeKgK = true;}
      if(dejkJYWWxb == wwXzBGblKB){mfRrBidNVA = true;}
      else if(wwXzBGblKB == dejkJYWWxb){kOBHVSADhD = true;}
      if(xFXgsusPku == uHqZtPSyEr){CNnkkQGcoO = true;}
      else if(uHqZtPSyEr == xFXgsusPku){wJguuUONTG = true;}
      if(uIzMNEhGbC == xAsHFjpWll){ErOTWbQcBk = true;}
      else if(xAsHFjpWll == uIzMNEhGbC){aeupzxSKJR = true;}
      if(bblZxjRmYU == klyUBNCytj){aKDFUBhEVz = true;}
      if(lbiagPuHJf == fkHDfwCpZO){YqtHCwxRqD = true;}
      if(MTDTUVfWXE == DhhhMuDQtR){UHsXRtRxVY = true;}
      while(klyUBNCytj == bblZxjRmYU){imZFoPwdcy = true;}
      while(fkHDfwCpZO == fkHDfwCpZO){SNxicZCnBL = true;}
      while(DhhhMuDQtR == DhhhMuDQtR){IQpajGTKIX = true;}
      if(PEAXQIIWYg == true){PEAXQIIWYg = false;}
      if(NTEUMLsobI == true){NTEUMLsobI = false;}
      if(gzxWiCEPHF == true){gzxWiCEPHF = false;}
      if(JlDbTakilW == true){JlDbTakilW = false;}
      if(mfRrBidNVA == true){mfRrBidNVA = false;}
      if(CNnkkQGcoO == true){CNnkkQGcoO = false;}
      if(ErOTWbQcBk == true){ErOTWbQcBk = false;}
      if(aKDFUBhEVz == true){aKDFUBhEVz = false;}
      if(YqtHCwxRqD == true){YqtHCwxRqD = false;}
      if(UHsXRtRxVY == true){UHsXRtRxVY = false;}
      if(SALjZrKiQi == true){SALjZrKiQi = false;}
      if(hCHppNyHQa == true){hCHppNyHQa = false;}
      if(dylyQSQemZ == true){dylyQSQemZ = false;}
      if(jjiwgXeKgK == true){jjiwgXeKgK = false;}
      if(kOBHVSADhD == true){kOBHVSADhD = false;}
      if(wJguuUONTG == true){wJguuUONTG = false;}
      if(aeupzxSKJR == true){aeupzxSKJR = false;}
      if(imZFoPwdcy == true){imZFoPwdcy = false;}
      if(SNxicZCnBL == true){SNxicZCnBL = false;}
      if(IQpajGTKIX == true){IQpajGTKIX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLNDKZEPKB
{ 
  void boCrqSEuNH()
  { 
      bool BfUcnzoNxE = false;
      bool ZppnzQMTnY = false;
      bool VAKftWrrrG = false;
      bool uVwVkJhsWo = false;
      bool DMaJKlmhUa = false;
      bool PMoiPBVniR = false;
      bool GxVpIDtUCp = false;
      bool hSwyVJYAVI = false;
      bool jKWRqigMGj = false;
      bool ntKFhFqjBG = false;
      bool qReerxPpNF = false;
      bool bUSZhwZDzZ = false;
      bool WgORCnHqPP = false;
      bool SnzOQRerZs = false;
      bool SqzAISajWl = false;
      bool fmkajKDMbE = false;
      bool pYZxmmVEJP = false;
      bool QgdGGfhOJj = false;
      bool MWTdjeDXeG = false;
      bool OSQUDtQCNU = false;
      string PjPaeasazw;
      string bjldloewSB;
      string OcWaKontGh;
      string jrrUnSQchC;
      string YtLnHVrbHK;
      string MTxHglNoPp;
      string mzTRLjqRpS;
      string XCOQbURhTo;
      string wLlwVQtkmB;
      string FbMrPZZsbW;
      string eZknlJEgeM;
      string TeVasaMXuu;
      string oFenNwoVAC;
      string tXFwJWaxKL;
      string LMGZgZFlzo;
      string NCxggYtxap;
      string UifcRwYZQV;
      string AOMjiczEGm;
      string pDWLnrZYOj;
      string bcVUqcgcIk;
      if(PjPaeasazw == eZknlJEgeM){BfUcnzoNxE = true;}
      else if(eZknlJEgeM == PjPaeasazw){qReerxPpNF = true;}
      if(bjldloewSB == TeVasaMXuu){ZppnzQMTnY = true;}
      else if(TeVasaMXuu == bjldloewSB){bUSZhwZDzZ = true;}
      if(OcWaKontGh == oFenNwoVAC){VAKftWrrrG = true;}
      else if(oFenNwoVAC == OcWaKontGh){WgORCnHqPP = true;}
      if(jrrUnSQchC == tXFwJWaxKL){uVwVkJhsWo = true;}
      else if(tXFwJWaxKL == jrrUnSQchC){SnzOQRerZs = true;}
      if(YtLnHVrbHK == LMGZgZFlzo){DMaJKlmhUa = true;}
      else if(LMGZgZFlzo == YtLnHVrbHK){SqzAISajWl = true;}
      if(MTxHglNoPp == NCxggYtxap){PMoiPBVniR = true;}
      else if(NCxggYtxap == MTxHglNoPp){fmkajKDMbE = true;}
      if(mzTRLjqRpS == UifcRwYZQV){GxVpIDtUCp = true;}
      else if(UifcRwYZQV == mzTRLjqRpS){pYZxmmVEJP = true;}
      if(XCOQbURhTo == AOMjiczEGm){hSwyVJYAVI = true;}
      if(wLlwVQtkmB == pDWLnrZYOj){jKWRqigMGj = true;}
      if(FbMrPZZsbW == bcVUqcgcIk){ntKFhFqjBG = true;}
      while(AOMjiczEGm == XCOQbURhTo){QgdGGfhOJj = true;}
      while(pDWLnrZYOj == pDWLnrZYOj){MWTdjeDXeG = true;}
      while(bcVUqcgcIk == bcVUqcgcIk){OSQUDtQCNU = true;}
      if(BfUcnzoNxE == true){BfUcnzoNxE = false;}
      if(ZppnzQMTnY == true){ZppnzQMTnY = false;}
      if(VAKftWrrrG == true){VAKftWrrrG = false;}
      if(uVwVkJhsWo == true){uVwVkJhsWo = false;}
      if(DMaJKlmhUa == true){DMaJKlmhUa = false;}
      if(PMoiPBVniR == true){PMoiPBVniR = false;}
      if(GxVpIDtUCp == true){GxVpIDtUCp = false;}
      if(hSwyVJYAVI == true){hSwyVJYAVI = false;}
      if(jKWRqigMGj == true){jKWRqigMGj = false;}
      if(ntKFhFqjBG == true){ntKFhFqjBG = false;}
      if(qReerxPpNF == true){qReerxPpNF = false;}
      if(bUSZhwZDzZ == true){bUSZhwZDzZ = false;}
      if(WgORCnHqPP == true){WgORCnHqPP = false;}
      if(SnzOQRerZs == true){SnzOQRerZs = false;}
      if(SqzAISajWl == true){SqzAISajWl = false;}
      if(fmkajKDMbE == true){fmkajKDMbE = false;}
      if(pYZxmmVEJP == true){pYZxmmVEJP = false;}
      if(QgdGGfhOJj == true){QgdGGfhOJj = false;}
      if(MWTdjeDXeG == true){MWTdjeDXeG = false;}
      if(OSQUDtQCNU == true){OSQUDtQCNU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZMENXSHBS
{ 
  void nYYbisTjRg()
  { 
      bool hIUmIhfKoQ = false;
      bool zAcwJzwMcM = false;
      bool bNMnzhwCoh = false;
      bool mpHZRNyEWW = false;
      bool odosUoiOpA = false;
      bool ycwQfTwfma = false;
      bool kcVHcIrCdu = false;
      bool BqoFWxXSSK = false;
      bool ygMoiKtpsx = false;
      bool RRQwlLIhQL = false;
      bool wgjuyGmpsi = false;
      bool wcMccDQgXS = false;
      bool OCJfdjasTL = false;
      bool ooCHNRwQpc = false;
      bool WDwKBnEnTh = false;
      bool ubKyxtWEQO = false;
      bool ftWhtGZFOK = false;
      bool HzptuLFyeo = false;
      bool elZlQMeEKT = false;
      bool trAbxcgNQt = false;
      string lGepRydHAE;
      string NaGKHFGacB;
      string knxqXrqjJM;
      string FoQIaVtnQa;
      string APsafyhCGt;
      string fQdeIyJmRZ;
      string GtymzXJxjk;
      string KRJCBVtWLY;
      string KodPfoKkzc;
      string LHVqTGQGaH;
      string njRViNGbcm;
      string EmasPQPhGK;
      string MYyGYCuSiu;
      string EnuEjaWHfR;
      string hiHMYYfcaC;
      string phzQtPkKwf;
      string RmshhQqWIn;
      string tICobdQkhz;
      string WSqfFVndJU;
      string oLLzztpZdI;
      if(lGepRydHAE == njRViNGbcm){hIUmIhfKoQ = true;}
      else if(njRViNGbcm == lGepRydHAE){wgjuyGmpsi = true;}
      if(NaGKHFGacB == EmasPQPhGK){zAcwJzwMcM = true;}
      else if(EmasPQPhGK == NaGKHFGacB){wcMccDQgXS = true;}
      if(knxqXrqjJM == MYyGYCuSiu){bNMnzhwCoh = true;}
      else if(MYyGYCuSiu == knxqXrqjJM){OCJfdjasTL = true;}
      if(FoQIaVtnQa == EnuEjaWHfR){mpHZRNyEWW = true;}
      else if(EnuEjaWHfR == FoQIaVtnQa){ooCHNRwQpc = true;}
      if(APsafyhCGt == hiHMYYfcaC){odosUoiOpA = true;}
      else if(hiHMYYfcaC == APsafyhCGt){WDwKBnEnTh = true;}
      if(fQdeIyJmRZ == phzQtPkKwf){ycwQfTwfma = true;}
      else if(phzQtPkKwf == fQdeIyJmRZ){ubKyxtWEQO = true;}
      if(GtymzXJxjk == RmshhQqWIn){kcVHcIrCdu = true;}
      else if(RmshhQqWIn == GtymzXJxjk){ftWhtGZFOK = true;}
      if(KRJCBVtWLY == tICobdQkhz){BqoFWxXSSK = true;}
      if(KodPfoKkzc == WSqfFVndJU){ygMoiKtpsx = true;}
      if(LHVqTGQGaH == oLLzztpZdI){RRQwlLIhQL = true;}
      while(tICobdQkhz == KRJCBVtWLY){HzptuLFyeo = true;}
      while(WSqfFVndJU == WSqfFVndJU){elZlQMeEKT = true;}
      while(oLLzztpZdI == oLLzztpZdI){trAbxcgNQt = true;}
      if(hIUmIhfKoQ == true){hIUmIhfKoQ = false;}
      if(zAcwJzwMcM == true){zAcwJzwMcM = false;}
      if(bNMnzhwCoh == true){bNMnzhwCoh = false;}
      if(mpHZRNyEWW == true){mpHZRNyEWW = false;}
      if(odosUoiOpA == true){odosUoiOpA = false;}
      if(ycwQfTwfma == true){ycwQfTwfma = false;}
      if(kcVHcIrCdu == true){kcVHcIrCdu = false;}
      if(BqoFWxXSSK == true){BqoFWxXSSK = false;}
      if(ygMoiKtpsx == true){ygMoiKtpsx = false;}
      if(RRQwlLIhQL == true){RRQwlLIhQL = false;}
      if(wgjuyGmpsi == true){wgjuyGmpsi = false;}
      if(wcMccDQgXS == true){wcMccDQgXS = false;}
      if(OCJfdjasTL == true){OCJfdjasTL = false;}
      if(ooCHNRwQpc == true){ooCHNRwQpc = false;}
      if(WDwKBnEnTh == true){WDwKBnEnTh = false;}
      if(ubKyxtWEQO == true){ubKyxtWEQO = false;}
      if(ftWhtGZFOK == true){ftWhtGZFOK = false;}
      if(HzptuLFyeo == true){HzptuLFyeo = false;}
      if(elZlQMeEKT == true){elZlQMeEKT = false;}
      if(trAbxcgNQt == true){trAbxcgNQt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJNYSLSIUV
{ 
  void uJAPMVItaY()
  { 
      bool QCfVSgAsqm = false;
      bool AgmFcTiibT = false;
      bool pYJLRxCVih = false;
      bool WyqaGWgQSF = false;
      bool ehMsyrdjWo = false;
      bool VKqWqqrTEU = false;
      bool deJJPCpMzG = false;
      bool lSPVnHMPNZ = false;
      bool SSytLMGTiO = false;
      bool dNLyaAXDdu = false;
      bool BRkQDCuUhi = false;
      bool dbGeBLfPxD = false;
      bool uVdjbYGRun = false;
      bool jJlRXBggqI = false;
      bool QlkzjCHgwO = false;
      bool UIFaAfnAod = false;
      bool wdZtzUpnGz = false;
      bool dyXnlJjdzZ = false;
      bool RZUfSaELRq = false;
      bool NgrMMmLqzP = false;
      string UGjRnFtUoL;
      string KfUcIwBjoy;
      string tIWoFiJYYg;
      string EaZApmNeuI;
      string DsazUWIqNC;
      string HJVTFLiuLF;
      string wUuHHjFUlU;
      string iWogtBgXUi;
      string aSKVZtEGud;
      string ESSpMixTqj;
      string QnEsSjToYE;
      string eKZcddJZhM;
      string fyYHQQDyUL;
      string DNgjRmNRCo;
      string aOgqzsrpMh;
      string YXldESOwbC;
      string gVUNARcpKp;
      string PrWrlQRhIW;
      string YMlllfbDfz;
      string YRoAIEsSqh;
      if(UGjRnFtUoL == QnEsSjToYE){QCfVSgAsqm = true;}
      else if(QnEsSjToYE == UGjRnFtUoL){BRkQDCuUhi = true;}
      if(KfUcIwBjoy == eKZcddJZhM){AgmFcTiibT = true;}
      else if(eKZcddJZhM == KfUcIwBjoy){dbGeBLfPxD = true;}
      if(tIWoFiJYYg == fyYHQQDyUL){pYJLRxCVih = true;}
      else if(fyYHQQDyUL == tIWoFiJYYg){uVdjbYGRun = true;}
      if(EaZApmNeuI == DNgjRmNRCo){WyqaGWgQSF = true;}
      else if(DNgjRmNRCo == EaZApmNeuI){jJlRXBggqI = true;}
      if(DsazUWIqNC == aOgqzsrpMh){ehMsyrdjWo = true;}
      else if(aOgqzsrpMh == DsazUWIqNC){QlkzjCHgwO = true;}
      if(HJVTFLiuLF == YXldESOwbC){VKqWqqrTEU = true;}
      else if(YXldESOwbC == HJVTFLiuLF){UIFaAfnAod = true;}
      if(wUuHHjFUlU == gVUNARcpKp){deJJPCpMzG = true;}
      else if(gVUNARcpKp == wUuHHjFUlU){wdZtzUpnGz = true;}
      if(iWogtBgXUi == PrWrlQRhIW){lSPVnHMPNZ = true;}
      if(aSKVZtEGud == YMlllfbDfz){SSytLMGTiO = true;}
      if(ESSpMixTqj == YRoAIEsSqh){dNLyaAXDdu = true;}
      while(PrWrlQRhIW == iWogtBgXUi){dyXnlJjdzZ = true;}
      while(YMlllfbDfz == YMlllfbDfz){RZUfSaELRq = true;}
      while(YRoAIEsSqh == YRoAIEsSqh){NgrMMmLqzP = true;}
      if(QCfVSgAsqm == true){QCfVSgAsqm = false;}
      if(AgmFcTiibT == true){AgmFcTiibT = false;}
      if(pYJLRxCVih == true){pYJLRxCVih = false;}
      if(WyqaGWgQSF == true){WyqaGWgQSF = false;}
      if(ehMsyrdjWo == true){ehMsyrdjWo = false;}
      if(VKqWqqrTEU == true){VKqWqqrTEU = false;}
      if(deJJPCpMzG == true){deJJPCpMzG = false;}
      if(lSPVnHMPNZ == true){lSPVnHMPNZ = false;}
      if(SSytLMGTiO == true){SSytLMGTiO = false;}
      if(dNLyaAXDdu == true){dNLyaAXDdu = false;}
      if(BRkQDCuUhi == true){BRkQDCuUhi = false;}
      if(dbGeBLfPxD == true){dbGeBLfPxD = false;}
      if(uVdjbYGRun == true){uVdjbYGRun = false;}
      if(jJlRXBggqI == true){jJlRXBggqI = false;}
      if(QlkzjCHgwO == true){QlkzjCHgwO = false;}
      if(UIFaAfnAod == true){UIFaAfnAod = false;}
      if(wdZtzUpnGz == true){wdZtzUpnGz = false;}
      if(dyXnlJjdzZ == true){dyXnlJjdzZ = false;}
      if(RZUfSaELRq == true){RZUfSaELRq = false;}
      if(NgrMMmLqzP == true){NgrMMmLqzP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBOXOPUGEW
{ 
  void MBAynzJHXe()
  { 
      bool QfUixGyQXp = false;
      bool zSlQSTETQX = false;
      bool jQkKBqlPDT = false;
      bool paXZellhok = false;
      bool hZWXaOPZtj = false;
      bool HcFGQztKgG = false;
      bool TiMDAXtLlf = false;
      bool hWdfoJtNil = false;
      bool bMUSMMUQJe = false;
      bool raAhRzMTWD = false;
      bool TDnOCkyZRG = false;
      bool FgbueGNtqn = false;
      bool CcCGmGVwOp = false;
      bool xapeSXYGQa = false;
      bool OuzCYLzFCK = false;
      bool lSbiApBgau = false;
      bool PCLbJepwbH = false;
      bool gGdPYHdzgb = false;
      bool GPsDEeyHeb = false;
      bool WrfULLjXst = false;
      string GZGXuByqmj;
      string cesycuwlOU;
      string PqtFQyNgkg;
      string eAlNfRZUAl;
      string fHQZuSmitE;
      string OqMXTPeBGw;
      string mRGFEcrfSK;
      string ValcoIZUJy;
      string KelfSnmOtQ;
      string mXODyOBLUS;
      string aHPjimEjiL;
      string oKqIlHeZmQ;
      string oclCXyMhda;
      string HOzqXDOCxe;
      string iCeiabfFRp;
      string iaXEcxVNLk;
      string aVGIEaLAkh;
      string rcbHglyCau;
      string RGQmqfptOZ;
      string gBpMEMwWeA;
      if(GZGXuByqmj == aHPjimEjiL){QfUixGyQXp = true;}
      else if(aHPjimEjiL == GZGXuByqmj){TDnOCkyZRG = true;}
      if(cesycuwlOU == oKqIlHeZmQ){zSlQSTETQX = true;}
      else if(oKqIlHeZmQ == cesycuwlOU){FgbueGNtqn = true;}
      if(PqtFQyNgkg == oclCXyMhda){jQkKBqlPDT = true;}
      else if(oclCXyMhda == PqtFQyNgkg){CcCGmGVwOp = true;}
      if(eAlNfRZUAl == HOzqXDOCxe){paXZellhok = true;}
      else if(HOzqXDOCxe == eAlNfRZUAl){xapeSXYGQa = true;}
      if(fHQZuSmitE == iCeiabfFRp){hZWXaOPZtj = true;}
      else if(iCeiabfFRp == fHQZuSmitE){OuzCYLzFCK = true;}
      if(OqMXTPeBGw == iaXEcxVNLk){HcFGQztKgG = true;}
      else if(iaXEcxVNLk == OqMXTPeBGw){lSbiApBgau = true;}
      if(mRGFEcrfSK == aVGIEaLAkh){TiMDAXtLlf = true;}
      else if(aVGIEaLAkh == mRGFEcrfSK){PCLbJepwbH = true;}
      if(ValcoIZUJy == rcbHglyCau){hWdfoJtNil = true;}
      if(KelfSnmOtQ == RGQmqfptOZ){bMUSMMUQJe = true;}
      if(mXODyOBLUS == gBpMEMwWeA){raAhRzMTWD = true;}
      while(rcbHglyCau == ValcoIZUJy){gGdPYHdzgb = true;}
      while(RGQmqfptOZ == RGQmqfptOZ){GPsDEeyHeb = true;}
      while(gBpMEMwWeA == gBpMEMwWeA){WrfULLjXst = true;}
      if(QfUixGyQXp == true){QfUixGyQXp = false;}
      if(zSlQSTETQX == true){zSlQSTETQX = false;}
      if(jQkKBqlPDT == true){jQkKBqlPDT = false;}
      if(paXZellhok == true){paXZellhok = false;}
      if(hZWXaOPZtj == true){hZWXaOPZtj = false;}
      if(HcFGQztKgG == true){HcFGQztKgG = false;}
      if(TiMDAXtLlf == true){TiMDAXtLlf = false;}
      if(hWdfoJtNil == true){hWdfoJtNil = false;}
      if(bMUSMMUQJe == true){bMUSMMUQJe = false;}
      if(raAhRzMTWD == true){raAhRzMTWD = false;}
      if(TDnOCkyZRG == true){TDnOCkyZRG = false;}
      if(FgbueGNtqn == true){FgbueGNtqn = false;}
      if(CcCGmGVwOp == true){CcCGmGVwOp = false;}
      if(xapeSXYGQa == true){xapeSXYGQa = false;}
      if(OuzCYLzFCK == true){OuzCYLzFCK = false;}
      if(lSbiApBgau == true){lSbiApBgau = false;}
      if(PCLbJepwbH == true){PCLbJepwbH = false;}
      if(gGdPYHdzgb == true){gGdPYHdzgb = false;}
      if(GPsDEeyHeb == true){GPsDEeyHeb = false;}
      if(WrfULLjXst == true){WrfULLjXst = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKXICGGUWK
{ 
  void VdZYUJxJfw()
  { 
      bool aFRjYjwMUJ = false;
      bool kSUwHrygqP = false;
      bool tDEWxpLejH = false;
      bool ytQUlzwCVa = false;
      bool MNGmljtkmS = false;
      bool YExdnWBumh = false;
      bool XQbMKqBAKH = false;
      bool wuLPDfxQkN = false;
      bool uZrRhsxmfO = false;
      bool yAPmCulsct = false;
      bool itaeVdsgZI = false;
      bool ZjKYlyXJdR = false;
      bool tNTuJueXNI = false;
      bool sDnpdByNuE = false;
      bool APNXoNppBD = false;
      bool WbPKAVZfUZ = false;
      bool yUSQOVwTuj = false;
      bool zKOZRdzwGw = false;
      bool FoWJkRncpI = false;
      bool aSrUFfwwJT = false;
      string wiTAOKWfUU;
      string XbFXLpoXaP;
      string xoLqfuCVSG;
      string OKXFNhcRje;
      string OPjuGwHmEl;
      string FxwqjHWcUT;
      string HBNOGNEzKd;
      string MXnwBgEQji;
      string mPQfAROfVF;
      string LAxQWNCVos;
      string rHcaYhIApC;
      string CGrkfrjgNn;
      string yXdFRMaXYn;
      string dhaqqflpHS;
      string INpSCFHLjd;
      string cVHAtTdWIM;
      string HkbBYUeBsz;
      string FsZufkhLCM;
      string FOmtKIaaxW;
      string CPhtKXlnth;
      if(wiTAOKWfUU == rHcaYhIApC){aFRjYjwMUJ = true;}
      else if(rHcaYhIApC == wiTAOKWfUU){itaeVdsgZI = true;}
      if(XbFXLpoXaP == CGrkfrjgNn){kSUwHrygqP = true;}
      else if(CGrkfrjgNn == XbFXLpoXaP){ZjKYlyXJdR = true;}
      if(xoLqfuCVSG == yXdFRMaXYn){tDEWxpLejH = true;}
      else if(yXdFRMaXYn == xoLqfuCVSG){tNTuJueXNI = true;}
      if(OKXFNhcRje == dhaqqflpHS){ytQUlzwCVa = true;}
      else if(dhaqqflpHS == OKXFNhcRje){sDnpdByNuE = true;}
      if(OPjuGwHmEl == INpSCFHLjd){MNGmljtkmS = true;}
      else if(INpSCFHLjd == OPjuGwHmEl){APNXoNppBD = true;}
      if(FxwqjHWcUT == cVHAtTdWIM){YExdnWBumh = true;}
      else if(cVHAtTdWIM == FxwqjHWcUT){WbPKAVZfUZ = true;}
      if(HBNOGNEzKd == HkbBYUeBsz){XQbMKqBAKH = true;}
      else if(HkbBYUeBsz == HBNOGNEzKd){yUSQOVwTuj = true;}
      if(MXnwBgEQji == FsZufkhLCM){wuLPDfxQkN = true;}
      if(mPQfAROfVF == FOmtKIaaxW){uZrRhsxmfO = true;}
      if(LAxQWNCVos == CPhtKXlnth){yAPmCulsct = true;}
      while(FsZufkhLCM == MXnwBgEQji){zKOZRdzwGw = true;}
      while(FOmtKIaaxW == FOmtKIaaxW){FoWJkRncpI = true;}
      while(CPhtKXlnth == CPhtKXlnth){aSrUFfwwJT = true;}
      if(aFRjYjwMUJ == true){aFRjYjwMUJ = false;}
      if(kSUwHrygqP == true){kSUwHrygqP = false;}
      if(tDEWxpLejH == true){tDEWxpLejH = false;}
      if(ytQUlzwCVa == true){ytQUlzwCVa = false;}
      if(MNGmljtkmS == true){MNGmljtkmS = false;}
      if(YExdnWBumh == true){YExdnWBumh = false;}
      if(XQbMKqBAKH == true){XQbMKqBAKH = false;}
      if(wuLPDfxQkN == true){wuLPDfxQkN = false;}
      if(uZrRhsxmfO == true){uZrRhsxmfO = false;}
      if(yAPmCulsct == true){yAPmCulsct = false;}
      if(itaeVdsgZI == true){itaeVdsgZI = false;}
      if(ZjKYlyXJdR == true){ZjKYlyXJdR = false;}
      if(tNTuJueXNI == true){tNTuJueXNI = false;}
      if(sDnpdByNuE == true){sDnpdByNuE = false;}
      if(APNXoNppBD == true){APNXoNppBD = false;}
      if(WbPKAVZfUZ == true){WbPKAVZfUZ = false;}
      if(yUSQOVwTuj == true){yUSQOVwTuj = false;}
      if(zKOZRdzwGw == true){zKOZRdzwGw = false;}
      if(FoWJkRncpI == true){FoWJkRncpI = false;}
      if(aSrUFfwwJT == true){aSrUFfwwJT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MISSYGAFGC
{ 
  void iJrZgfOutU()
  { 
      bool XjRpktChBN = false;
      bool aEbWBXwoBM = false;
      bool OZqOmAesrF = false;
      bool tsQXojYUGN = false;
      bool bYZTGseMVH = false;
      bool RQGgrxsCDj = false;
      bool OJouTgnDhQ = false;
      bool yaimjpAXIs = false;
      bool USXjncmifq = false;
      bool qVRVzSjdzY = false;
      bool FbdEJpgSwC = false;
      bool wVtJOulEHq = false;
      bool tEXpZbIMnR = false;
      bool GWYinsnSax = false;
      bool uUlctUbHGE = false;
      bool geVIeBEneg = false;
      bool gUeewZxLVV = false;
      bool GScKuZRtuE = false;
      bool ABFjkaAQEl = false;
      bool nAntPaoHgU = false;
      string OhLhpfkHqq;
      string NoSIjGKVVS;
      string GrcrSOZQDJ;
      string hVbsjbxjEV;
      string LfGUtKmrcJ;
      string uOQhQVFTOb;
      string FUDhJrNZYH;
      string IaRAHalHyH;
      string bhmtOTEsbN;
      string WdUcPpcYLC;
      string xMSUATxQap;
      string jxUGAWhJSp;
      string mTxKkdFnjQ;
      string yNwwKOPSst;
      string VmSldYJNcr;
      string ISGUOcPIiV;
      string OIgJrWBYwl;
      string HOPXTABKfM;
      string UqLqHeHagg;
      string yHiWfNGItH;
      if(OhLhpfkHqq == xMSUATxQap){XjRpktChBN = true;}
      else if(xMSUATxQap == OhLhpfkHqq){FbdEJpgSwC = true;}
      if(NoSIjGKVVS == jxUGAWhJSp){aEbWBXwoBM = true;}
      else if(jxUGAWhJSp == NoSIjGKVVS){wVtJOulEHq = true;}
      if(GrcrSOZQDJ == mTxKkdFnjQ){OZqOmAesrF = true;}
      else if(mTxKkdFnjQ == GrcrSOZQDJ){tEXpZbIMnR = true;}
      if(hVbsjbxjEV == yNwwKOPSst){tsQXojYUGN = true;}
      else if(yNwwKOPSst == hVbsjbxjEV){GWYinsnSax = true;}
      if(LfGUtKmrcJ == VmSldYJNcr){bYZTGseMVH = true;}
      else if(VmSldYJNcr == LfGUtKmrcJ){uUlctUbHGE = true;}
      if(uOQhQVFTOb == ISGUOcPIiV){RQGgrxsCDj = true;}
      else if(ISGUOcPIiV == uOQhQVFTOb){geVIeBEneg = true;}
      if(FUDhJrNZYH == OIgJrWBYwl){OJouTgnDhQ = true;}
      else if(OIgJrWBYwl == FUDhJrNZYH){gUeewZxLVV = true;}
      if(IaRAHalHyH == HOPXTABKfM){yaimjpAXIs = true;}
      if(bhmtOTEsbN == UqLqHeHagg){USXjncmifq = true;}
      if(WdUcPpcYLC == yHiWfNGItH){qVRVzSjdzY = true;}
      while(HOPXTABKfM == IaRAHalHyH){GScKuZRtuE = true;}
      while(UqLqHeHagg == UqLqHeHagg){ABFjkaAQEl = true;}
      while(yHiWfNGItH == yHiWfNGItH){nAntPaoHgU = true;}
      if(XjRpktChBN == true){XjRpktChBN = false;}
      if(aEbWBXwoBM == true){aEbWBXwoBM = false;}
      if(OZqOmAesrF == true){OZqOmAesrF = false;}
      if(tsQXojYUGN == true){tsQXojYUGN = false;}
      if(bYZTGseMVH == true){bYZTGseMVH = false;}
      if(RQGgrxsCDj == true){RQGgrxsCDj = false;}
      if(OJouTgnDhQ == true){OJouTgnDhQ = false;}
      if(yaimjpAXIs == true){yaimjpAXIs = false;}
      if(USXjncmifq == true){USXjncmifq = false;}
      if(qVRVzSjdzY == true){qVRVzSjdzY = false;}
      if(FbdEJpgSwC == true){FbdEJpgSwC = false;}
      if(wVtJOulEHq == true){wVtJOulEHq = false;}
      if(tEXpZbIMnR == true){tEXpZbIMnR = false;}
      if(GWYinsnSax == true){GWYinsnSax = false;}
      if(uUlctUbHGE == true){uUlctUbHGE = false;}
      if(geVIeBEneg == true){geVIeBEneg = false;}
      if(gUeewZxLVV == true){gUeewZxLVV = false;}
      if(GScKuZRtuE == true){GScKuZRtuE = false;}
      if(ABFjkaAQEl == true){ABFjkaAQEl = false;}
      if(nAntPaoHgU == true){nAntPaoHgU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVWENIXZDO
{ 
  void spKOMNmxBO()
  { 
      bool OGpunsLHRQ = false;
      bool oGFBTQNtOc = false;
      bool SjoUiKsTHy = false;
      bool UFmVmobbst = false;
      bool BNRnRRQpyh = false;
      bool YaRaKeQVLc = false;
      bool zrASwjTiOd = false;
      bool olATaERACQ = false;
      bool sCUZZtmLKH = false;
      bool XFPPtJNyrg = false;
      bool yhbTrlayzG = false;
      bool MQStixWZsB = false;
      bool xIXGGiWjYR = false;
      bool pSIVSLaBgm = false;
      bool SoLEuHmUfx = false;
      bool lnFpjpJVNJ = false;
      bool PqYgQsIxbX = false;
      bool WVsGiIwTKy = false;
      bool wBDbeCNRkc = false;
      bool BFmXWbPemC = false;
      string pNllLnFaUF;
      string FbRMRdchTD;
      string QdHUxZfqKf;
      string KoDhCsZPWl;
      string ZjqILTSgKQ;
      string eYMzjLFQnl;
      string HNPouPXjJX;
      string EMLhdgmzJd;
      string GzgtAkbDyq;
      string nIbjdLTCMu;
      string uiXlLSMeUD;
      string YFHJfIfUnJ;
      string nUkRiwjbDS;
      string MjlNhWbuhh;
      string XxitRhAREV;
      string ezODHaxFCP;
      string ikbCpnTtbI;
      string gkmGkplqzB;
      string uRWhnNViFG;
      string YVrSymUfDd;
      if(pNllLnFaUF == uiXlLSMeUD){OGpunsLHRQ = true;}
      else if(uiXlLSMeUD == pNllLnFaUF){yhbTrlayzG = true;}
      if(FbRMRdchTD == YFHJfIfUnJ){oGFBTQNtOc = true;}
      else if(YFHJfIfUnJ == FbRMRdchTD){MQStixWZsB = true;}
      if(QdHUxZfqKf == nUkRiwjbDS){SjoUiKsTHy = true;}
      else if(nUkRiwjbDS == QdHUxZfqKf){xIXGGiWjYR = true;}
      if(KoDhCsZPWl == MjlNhWbuhh){UFmVmobbst = true;}
      else if(MjlNhWbuhh == KoDhCsZPWl){pSIVSLaBgm = true;}
      if(ZjqILTSgKQ == XxitRhAREV){BNRnRRQpyh = true;}
      else if(XxitRhAREV == ZjqILTSgKQ){SoLEuHmUfx = true;}
      if(eYMzjLFQnl == ezODHaxFCP){YaRaKeQVLc = true;}
      else if(ezODHaxFCP == eYMzjLFQnl){lnFpjpJVNJ = true;}
      if(HNPouPXjJX == ikbCpnTtbI){zrASwjTiOd = true;}
      else if(ikbCpnTtbI == HNPouPXjJX){PqYgQsIxbX = true;}
      if(EMLhdgmzJd == gkmGkplqzB){olATaERACQ = true;}
      if(GzgtAkbDyq == uRWhnNViFG){sCUZZtmLKH = true;}
      if(nIbjdLTCMu == YVrSymUfDd){XFPPtJNyrg = true;}
      while(gkmGkplqzB == EMLhdgmzJd){WVsGiIwTKy = true;}
      while(uRWhnNViFG == uRWhnNViFG){wBDbeCNRkc = true;}
      while(YVrSymUfDd == YVrSymUfDd){BFmXWbPemC = true;}
      if(OGpunsLHRQ == true){OGpunsLHRQ = false;}
      if(oGFBTQNtOc == true){oGFBTQNtOc = false;}
      if(SjoUiKsTHy == true){SjoUiKsTHy = false;}
      if(UFmVmobbst == true){UFmVmobbst = false;}
      if(BNRnRRQpyh == true){BNRnRRQpyh = false;}
      if(YaRaKeQVLc == true){YaRaKeQVLc = false;}
      if(zrASwjTiOd == true){zrASwjTiOd = false;}
      if(olATaERACQ == true){olATaERACQ = false;}
      if(sCUZZtmLKH == true){sCUZZtmLKH = false;}
      if(XFPPtJNyrg == true){XFPPtJNyrg = false;}
      if(yhbTrlayzG == true){yhbTrlayzG = false;}
      if(MQStixWZsB == true){MQStixWZsB = false;}
      if(xIXGGiWjYR == true){xIXGGiWjYR = false;}
      if(pSIVSLaBgm == true){pSIVSLaBgm = false;}
      if(SoLEuHmUfx == true){SoLEuHmUfx = false;}
      if(lnFpjpJVNJ == true){lnFpjpJVNJ = false;}
      if(PqYgQsIxbX == true){PqYgQsIxbX = false;}
      if(WVsGiIwTKy == true){WVsGiIwTKy = false;}
      if(wBDbeCNRkc == true){wBDbeCNRkc = false;}
      if(BFmXWbPemC == true){BFmXWbPemC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHOYFLPMZK
{ 
  void wRafjadwXh()
  { 
      bool jFSHxLItzo = false;
      bool iqpgEujZnG = false;
      bool JLqUxYaNXo = false;
      bool ASrDQdOFLF = false;
      bool NBmYwKZuEB = false;
      bool ufpjQYOxJY = false;
      bool juVJoQylPZ = false;
      bool gdNhrHXSYm = false;
      bool yeIVsUbIlr = false;
      bool PRwmUSedje = false;
      bool MmeeUQRHqI = false;
      bool AuXWZFlAPT = false;
      bool opzXJOhaNZ = false;
      bool ctisZKAdAc = false;
      bool DTQdqTsZMP = false;
      bool feNPpVnHUF = false;
      bool iqtRfGMdwP = false;
      bool EIzmQUZVfo = false;
      bool VINxtxgSCD = false;
      bool WsIusLYyxk = false;
      string TMVYhaPsKR;
      string MOhinSugze;
      string AgjEnsqVrL;
      string XAMdfPtQZt;
      string WAKLDOjeqJ;
      string IahrelcRkn;
      string jsBztMBDCX;
      string YeHEIzVXBY;
      string JLehDwRTzt;
      string mbelJcyLRp;
      string NfbSkcScje;
      string PEQLdXOTwx;
      string tgEIjwAVte;
      string BKGKLdiLxa;
      string cnjUehLSHl;
      string OePTwfaTin;
      string cxiFcEyFAA;
      string nDVVUGxjdB;
      string jgNIQWumOe;
      string CPcIxeFeqZ;
      if(TMVYhaPsKR == NfbSkcScje){jFSHxLItzo = true;}
      else if(NfbSkcScje == TMVYhaPsKR){MmeeUQRHqI = true;}
      if(MOhinSugze == PEQLdXOTwx){iqpgEujZnG = true;}
      else if(PEQLdXOTwx == MOhinSugze){AuXWZFlAPT = true;}
      if(AgjEnsqVrL == tgEIjwAVte){JLqUxYaNXo = true;}
      else if(tgEIjwAVte == AgjEnsqVrL){opzXJOhaNZ = true;}
      if(XAMdfPtQZt == BKGKLdiLxa){ASrDQdOFLF = true;}
      else if(BKGKLdiLxa == XAMdfPtQZt){ctisZKAdAc = true;}
      if(WAKLDOjeqJ == cnjUehLSHl){NBmYwKZuEB = true;}
      else if(cnjUehLSHl == WAKLDOjeqJ){DTQdqTsZMP = true;}
      if(IahrelcRkn == OePTwfaTin){ufpjQYOxJY = true;}
      else if(OePTwfaTin == IahrelcRkn){feNPpVnHUF = true;}
      if(jsBztMBDCX == cxiFcEyFAA){juVJoQylPZ = true;}
      else if(cxiFcEyFAA == jsBztMBDCX){iqtRfGMdwP = true;}
      if(YeHEIzVXBY == nDVVUGxjdB){gdNhrHXSYm = true;}
      if(JLehDwRTzt == jgNIQWumOe){yeIVsUbIlr = true;}
      if(mbelJcyLRp == CPcIxeFeqZ){PRwmUSedje = true;}
      while(nDVVUGxjdB == YeHEIzVXBY){EIzmQUZVfo = true;}
      while(jgNIQWumOe == jgNIQWumOe){VINxtxgSCD = true;}
      while(CPcIxeFeqZ == CPcIxeFeqZ){WsIusLYyxk = true;}
      if(jFSHxLItzo == true){jFSHxLItzo = false;}
      if(iqpgEujZnG == true){iqpgEujZnG = false;}
      if(JLqUxYaNXo == true){JLqUxYaNXo = false;}
      if(ASrDQdOFLF == true){ASrDQdOFLF = false;}
      if(NBmYwKZuEB == true){NBmYwKZuEB = false;}
      if(ufpjQYOxJY == true){ufpjQYOxJY = false;}
      if(juVJoQylPZ == true){juVJoQylPZ = false;}
      if(gdNhrHXSYm == true){gdNhrHXSYm = false;}
      if(yeIVsUbIlr == true){yeIVsUbIlr = false;}
      if(PRwmUSedje == true){PRwmUSedje = false;}
      if(MmeeUQRHqI == true){MmeeUQRHqI = false;}
      if(AuXWZFlAPT == true){AuXWZFlAPT = false;}
      if(opzXJOhaNZ == true){opzXJOhaNZ = false;}
      if(ctisZKAdAc == true){ctisZKAdAc = false;}
      if(DTQdqTsZMP == true){DTQdqTsZMP = false;}
      if(feNPpVnHUF == true){feNPpVnHUF = false;}
      if(iqtRfGMdwP == true){iqtRfGMdwP = false;}
      if(EIzmQUZVfo == true){EIzmQUZVfo = false;}
      if(VINxtxgSCD == true){VINxtxgSCD = false;}
      if(WsIusLYyxk == true){WsIusLYyxk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZNCIHYLOB
{ 
  void OTPqEqRErW()
  { 
      bool UBhVDEIWnH = false;
      bool mYeUTVBZqn = false;
      bool SgILAOAtdH = false;
      bool TFDEOpdFdP = false;
      bool eHKQVifYjo = false;
      bool dtdUOmrVVo = false;
      bool DNrfmhUaGc = false;
      bool ruwbIKWqpQ = false;
      bool hbKndYbioa = false;
      bool xHjnLROedn = false;
      bool OFSGxiyBLD = false;
      bool QBfFGbDECN = false;
      bool FkkffjKHPq = false;
      bool uqNBBcIDpu = false;
      bool aaWlJwbehj = false;
      bool OKcPhcTlaM = false;
      bool XqkUIZndDd = false;
      bool SzNGmeOzWi = false;
      bool HfZfckOxTY = false;
      bool JWbcXioBdj = false;
      string dNEeypNNTJ;
      string cZwcLnAGqr;
      string xDIPnRbczw;
      string UMFrsPanPw;
      string diRLernQmz;
      string HbPrkZFnpg;
      string OjOWnPUEiw;
      string MLpuNOlxkw;
      string dKpAnsxMGS;
      string KlxihtUtWO;
      string WigqlukUeV;
      string nHDtDDtNhu;
      string RIxQlaOHMT;
      string tqaVYtczOr;
      string IcgjeCiDee;
      string zGMaxOlQEK;
      string gcHLbxggVI;
      string auyomoaMki;
      string qLbhTmezYJ;
      string ILtDLeUVIg;
      if(dNEeypNNTJ == WigqlukUeV){UBhVDEIWnH = true;}
      else if(WigqlukUeV == dNEeypNNTJ){OFSGxiyBLD = true;}
      if(cZwcLnAGqr == nHDtDDtNhu){mYeUTVBZqn = true;}
      else if(nHDtDDtNhu == cZwcLnAGqr){QBfFGbDECN = true;}
      if(xDIPnRbczw == RIxQlaOHMT){SgILAOAtdH = true;}
      else if(RIxQlaOHMT == xDIPnRbczw){FkkffjKHPq = true;}
      if(UMFrsPanPw == tqaVYtczOr){TFDEOpdFdP = true;}
      else if(tqaVYtczOr == UMFrsPanPw){uqNBBcIDpu = true;}
      if(diRLernQmz == IcgjeCiDee){eHKQVifYjo = true;}
      else if(IcgjeCiDee == diRLernQmz){aaWlJwbehj = true;}
      if(HbPrkZFnpg == zGMaxOlQEK){dtdUOmrVVo = true;}
      else if(zGMaxOlQEK == HbPrkZFnpg){OKcPhcTlaM = true;}
      if(OjOWnPUEiw == gcHLbxggVI){DNrfmhUaGc = true;}
      else if(gcHLbxggVI == OjOWnPUEiw){XqkUIZndDd = true;}
      if(MLpuNOlxkw == auyomoaMki){ruwbIKWqpQ = true;}
      if(dKpAnsxMGS == qLbhTmezYJ){hbKndYbioa = true;}
      if(KlxihtUtWO == ILtDLeUVIg){xHjnLROedn = true;}
      while(auyomoaMki == MLpuNOlxkw){SzNGmeOzWi = true;}
      while(qLbhTmezYJ == qLbhTmezYJ){HfZfckOxTY = true;}
      while(ILtDLeUVIg == ILtDLeUVIg){JWbcXioBdj = true;}
      if(UBhVDEIWnH == true){UBhVDEIWnH = false;}
      if(mYeUTVBZqn == true){mYeUTVBZqn = false;}
      if(SgILAOAtdH == true){SgILAOAtdH = false;}
      if(TFDEOpdFdP == true){TFDEOpdFdP = false;}
      if(eHKQVifYjo == true){eHKQVifYjo = false;}
      if(dtdUOmrVVo == true){dtdUOmrVVo = false;}
      if(DNrfmhUaGc == true){DNrfmhUaGc = false;}
      if(ruwbIKWqpQ == true){ruwbIKWqpQ = false;}
      if(hbKndYbioa == true){hbKndYbioa = false;}
      if(xHjnLROedn == true){xHjnLROedn = false;}
      if(OFSGxiyBLD == true){OFSGxiyBLD = false;}
      if(QBfFGbDECN == true){QBfFGbDECN = false;}
      if(FkkffjKHPq == true){FkkffjKHPq = false;}
      if(uqNBBcIDpu == true){uqNBBcIDpu = false;}
      if(aaWlJwbehj == true){aaWlJwbehj = false;}
      if(OKcPhcTlaM == true){OKcPhcTlaM = false;}
      if(XqkUIZndDd == true){XqkUIZndDd = false;}
      if(SzNGmeOzWi == true){SzNGmeOzWi = false;}
      if(HfZfckOxTY == true){HfZfckOxTY = false;}
      if(JWbcXioBdj == true){JWbcXioBdj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDSVRNYUIU
{ 
  void lcDbCTquUQ()
  { 
      bool zPbVmzxPWp = false;
      bool MfTpnYzGfz = false;
      bool wSzpdqtHhn = false;
      bool cVwwSStHVU = false;
      bool OHLoXRjhok = false;
      bool hNVZrfQlqu = false;
      bool EpgiNpiWXU = false;
      bool erkKjoHJSM = false;
      bool GMSwFOzVEm = false;
      bool BIPZQYacbg = false;
      bool hMKTGocKpD = false;
      bool XGSenrXjcy = false;
      bool pNSkSWcLtL = false;
      bool OdhketCypQ = false;
      bool lnfBOuojkY = false;
      bool BpAdpTtYAj = false;
      bool MQQentYgAt = false;
      bool pYtLLBhQVX = false;
      bool grZVJXdEuK = false;
      bool zcxGEUXAMU = false;
      string MyXkylhOwK;
      string FsUCEDyDqX;
      string bXUjIQScZU;
      string PfcTyHfaFJ;
      string VKiTtbJGWX;
      string rBonZndmbh;
      string SFnatYPAEw;
      string WXyhCRnAog;
      string HMGCbNqosJ;
      string dsyXpQVIYV;
      string LIBZBUDHlI;
      string AcyuZGylzg;
      string haGuSdYZrl;
      string wfaTUyKfAG;
      string KjCkJAtCxi;
      string RiIrnkBGHW;
      string ucPALTBeZb;
      string wSksVxXVlR;
      string iWcITMWhej;
      string xEXdKhUCYo;
      if(MyXkylhOwK == LIBZBUDHlI){zPbVmzxPWp = true;}
      else if(LIBZBUDHlI == MyXkylhOwK){hMKTGocKpD = true;}
      if(FsUCEDyDqX == AcyuZGylzg){MfTpnYzGfz = true;}
      else if(AcyuZGylzg == FsUCEDyDqX){XGSenrXjcy = true;}
      if(bXUjIQScZU == haGuSdYZrl){wSzpdqtHhn = true;}
      else if(haGuSdYZrl == bXUjIQScZU){pNSkSWcLtL = true;}
      if(PfcTyHfaFJ == wfaTUyKfAG){cVwwSStHVU = true;}
      else if(wfaTUyKfAG == PfcTyHfaFJ){OdhketCypQ = true;}
      if(VKiTtbJGWX == KjCkJAtCxi){OHLoXRjhok = true;}
      else if(KjCkJAtCxi == VKiTtbJGWX){lnfBOuojkY = true;}
      if(rBonZndmbh == RiIrnkBGHW){hNVZrfQlqu = true;}
      else if(RiIrnkBGHW == rBonZndmbh){BpAdpTtYAj = true;}
      if(SFnatYPAEw == ucPALTBeZb){EpgiNpiWXU = true;}
      else if(ucPALTBeZb == SFnatYPAEw){MQQentYgAt = true;}
      if(WXyhCRnAog == wSksVxXVlR){erkKjoHJSM = true;}
      if(HMGCbNqosJ == iWcITMWhej){GMSwFOzVEm = true;}
      if(dsyXpQVIYV == xEXdKhUCYo){BIPZQYacbg = true;}
      while(wSksVxXVlR == WXyhCRnAog){pYtLLBhQVX = true;}
      while(iWcITMWhej == iWcITMWhej){grZVJXdEuK = true;}
      while(xEXdKhUCYo == xEXdKhUCYo){zcxGEUXAMU = true;}
      if(zPbVmzxPWp == true){zPbVmzxPWp = false;}
      if(MfTpnYzGfz == true){MfTpnYzGfz = false;}
      if(wSzpdqtHhn == true){wSzpdqtHhn = false;}
      if(cVwwSStHVU == true){cVwwSStHVU = false;}
      if(OHLoXRjhok == true){OHLoXRjhok = false;}
      if(hNVZrfQlqu == true){hNVZrfQlqu = false;}
      if(EpgiNpiWXU == true){EpgiNpiWXU = false;}
      if(erkKjoHJSM == true){erkKjoHJSM = false;}
      if(GMSwFOzVEm == true){GMSwFOzVEm = false;}
      if(BIPZQYacbg == true){BIPZQYacbg = false;}
      if(hMKTGocKpD == true){hMKTGocKpD = false;}
      if(XGSenrXjcy == true){XGSenrXjcy = false;}
      if(pNSkSWcLtL == true){pNSkSWcLtL = false;}
      if(OdhketCypQ == true){OdhketCypQ = false;}
      if(lnfBOuojkY == true){lnfBOuojkY = false;}
      if(BpAdpTtYAj == true){BpAdpTtYAj = false;}
      if(MQQentYgAt == true){MQQentYgAt = false;}
      if(pYtLLBhQVX == true){pYtLLBhQVX = false;}
      if(grZVJXdEuK == true){grZVJXdEuK = false;}
      if(zcxGEUXAMU == true){zcxGEUXAMU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUBEAYGTTG
{ 
  void mJEUTnsKdt()
  { 
      bool SeXkqRXOry = false;
      bool jwGafyIJVM = false;
      bool aEkwrYMaLt = false;
      bool YMdYKqmEmb = false;
      bool LBfVtegCXt = false;
      bool waXfGNsbrS = false;
      bool FxCyZXSgQn = false;
      bool LEWsAZYOBN = false;
      bool qJDRxxnxSw = false;
      bool xLLUVOzhwW = false;
      bool LAliirEefg = false;
      bool odZeawsjAb = false;
      bool iUNTqArCWk = false;
      bool ZpSdBqXUiF = false;
      bool sJRlGTkgsZ = false;
      bool VOhUnplRrh = false;
      bool zCHtGyLucj = false;
      bool YYBuhZDbNW = false;
      bool OLIwPLIxpK = false;
      bool EFcAFqBXfI = false;
      string IDDrWinsSw;
      string ETPVLBNThs;
      string HTzxXkWGwn;
      string zXafotaMFe;
      string MiGoZyMaui;
      string SFZzHnDGUl;
      string LhwdwgrigQ;
      string aANCfYMJWZ;
      string XwLNUtxbXA;
      string pTrTTdlcss;
      string FdtdIRqWSi;
      string bsjtNPWiIB;
      string jPKfZGItiC;
      string ljPdTtCgFD;
      string CZJoYwjxFE;
      string HCTqIpSNDB;
      string JxnPwqdFZT;
      string ModFzKFVHc;
      string VKodtjPYUd;
      string ancDsEksrh;
      if(IDDrWinsSw == FdtdIRqWSi){SeXkqRXOry = true;}
      else if(FdtdIRqWSi == IDDrWinsSw){LAliirEefg = true;}
      if(ETPVLBNThs == bsjtNPWiIB){jwGafyIJVM = true;}
      else if(bsjtNPWiIB == ETPVLBNThs){odZeawsjAb = true;}
      if(HTzxXkWGwn == jPKfZGItiC){aEkwrYMaLt = true;}
      else if(jPKfZGItiC == HTzxXkWGwn){iUNTqArCWk = true;}
      if(zXafotaMFe == ljPdTtCgFD){YMdYKqmEmb = true;}
      else if(ljPdTtCgFD == zXafotaMFe){ZpSdBqXUiF = true;}
      if(MiGoZyMaui == CZJoYwjxFE){LBfVtegCXt = true;}
      else if(CZJoYwjxFE == MiGoZyMaui){sJRlGTkgsZ = true;}
      if(SFZzHnDGUl == HCTqIpSNDB){waXfGNsbrS = true;}
      else if(HCTqIpSNDB == SFZzHnDGUl){VOhUnplRrh = true;}
      if(LhwdwgrigQ == JxnPwqdFZT){FxCyZXSgQn = true;}
      else if(JxnPwqdFZT == LhwdwgrigQ){zCHtGyLucj = true;}
      if(aANCfYMJWZ == ModFzKFVHc){LEWsAZYOBN = true;}
      if(XwLNUtxbXA == VKodtjPYUd){qJDRxxnxSw = true;}
      if(pTrTTdlcss == ancDsEksrh){xLLUVOzhwW = true;}
      while(ModFzKFVHc == aANCfYMJWZ){YYBuhZDbNW = true;}
      while(VKodtjPYUd == VKodtjPYUd){OLIwPLIxpK = true;}
      while(ancDsEksrh == ancDsEksrh){EFcAFqBXfI = true;}
      if(SeXkqRXOry == true){SeXkqRXOry = false;}
      if(jwGafyIJVM == true){jwGafyIJVM = false;}
      if(aEkwrYMaLt == true){aEkwrYMaLt = false;}
      if(YMdYKqmEmb == true){YMdYKqmEmb = false;}
      if(LBfVtegCXt == true){LBfVtegCXt = false;}
      if(waXfGNsbrS == true){waXfGNsbrS = false;}
      if(FxCyZXSgQn == true){FxCyZXSgQn = false;}
      if(LEWsAZYOBN == true){LEWsAZYOBN = false;}
      if(qJDRxxnxSw == true){qJDRxxnxSw = false;}
      if(xLLUVOzhwW == true){xLLUVOzhwW = false;}
      if(LAliirEefg == true){LAliirEefg = false;}
      if(odZeawsjAb == true){odZeawsjAb = false;}
      if(iUNTqArCWk == true){iUNTqArCWk = false;}
      if(ZpSdBqXUiF == true){ZpSdBqXUiF = false;}
      if(sJRlGTkgsZ == true){sJRlGTkgsZ = false;}
      if(VOhUnplRrh == true){VOhUnplRrh = false;}
      if(zCHtGyLucj == true){zCHtGyLucj = false;}
      if(YYBuhZDbNW == true){YYBuhZDbNW = false;}
      if(OLIwPLIxpK == true){OLIwPLIxpK = false;}
      if(EFcAFqBXfI == true){EFcAFqBXfI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXGKTQAOEY
{ 
  void LDCmiRjVLW()
  { 
      bool NeUPMXIULG = false;
      bool gVqTbhWhlW = false;
      bool YQIDNlQpgJ = false;
      bool oDFITCBVUR = false;
      bool SCWIXCdotQ = false;
      bool EIeqTwWRBa = false;
      bool GSmBQdPhAZ = false;
      bool gBNUDWtzeL = false;
      bool HbuQFgXOoW = false;
      bool eiTtKAOUqt = false;
      bool lwoUiDuKmw = false;
      bool CXmpSeWWwj = false;
      bool FArctygSKC = false;
      bool IZHjYLlagC = false;
      bool lNasTHwcbf = false;
      bool dqXHokDLZk = false;
      bool VbAjncPCQG = false;
      bool rwotyrZzIm = false;
      bool CDqdYQBAum = false;
      bool IZAwfJNpEq = false;
      string dmSGWFVCyR;
      string xPJyzrcVzs;
      string ytMQPplghF;
      string RjrUuPejgI;
      string XjgQnpJmcH;
      string xkJjLiZCpf;
      string TnUsANXoDi;
      string NsoqVNMubZ;
      string gyDaIfZIJL;
      string pcsAoiPmQZ;
      string RUjstEwSOx;
      string VdZQyUkskT;
      string mPfqsjznBm;
      string yZeCHMNJfE;
      string iHsMoMCcCT;
      string yVCwlCosAJ;
      string EIQaywzXIl;
      string HaMgkfVSBg;
      string gVlhobXhPF;
      string XUJWzaqRNr;
      if(dmSGWFVCyR == RUjstEwSOx){NeUPMXIULG = true;}
      else if(RUjstEwSOx == dmSGWFVCyR){lwoUiDuKmw = true;}
      if(xPJyzrcVzs == VdZQyUkskT){gVqTbhWhlW = true;}
      else if(VdZQyUkskT == xPJyzrcVzs){CXmpSeWWwj = true;}
      if(ytMQPplghF == mPfqsjznBm){YQIDNlQpgJ = true;}
      else if(mPfqsjznBm == ytMQPplghF){FArctygSKC = true;}
      if(RjrUuPejgI == yZeCHMNJfE){oDFITCBVUR = true;}
      else if(yZeCHMNJfE == RjrUuPejgI){IZHjYLlagC = true;}
      if(XjgQnpJmcH == iHsMoMCcCT){SCWIXCdotQ = true;}
      else if(iHsMoMCcCT == XjgQnpJmcH){lNasTHwcbf = true;}
      if(xkJjLiZCpf == yVCwlCosAJ){EIeqTwWRBa = true;}
      else if(yVCwlCosAJ == xkJjLiZCpf){dqXHokDLZk = true;}
      if(TnUsANXoDi == EIQaywzXIl){GSmBQdPhAZ = true;}
      else if(EIQaywzXIl == TnUsANXoDi){VbAjncPCQG = true;}
      if(NsoqVNMubZ == HaMgkfVSBg){gBNUDWtzeL = true;}
      if(gyDaIfZIJL == gVlhobXhPF){HbuQFgXOoW = true;}
      if(pcsAoiPmQZ == XUJWzaqRNr){eiTtKAOUqt = true;}
      while(HaMgkfVSBg == NsoqVNMubZ){rwotyrZzIm = true;}
      while(gVlhobXhPF == gVlhobXhPF){CDqdYQBAum = true;}
      while(XUJWzaqRNr == XUJWzaqRNr){IZAwfJNpEq = true;}
      if(NeUPMXIULG == true){NeUPMXIULG = false;}
      if(gVqTbhWhlW == true){gVqTbhWhlW = false;}
      if(YQIDNlQpgJ == true){YQIDNlQpgJ = false;}
      if(oDFITCBVUR == true){oDFITCBVUR = false;}
      if(SCWIXCdotQ == true){SCWIXCdotQ = false;}
      if(EIeqTwWRBa == true){EIeqTwWRBa = false;}
      if(GSmBQdPhAZ == true){GSmBQdPhAZ = false;}
      if(gBNUDWtzeL == true){gBNUDWtzeL = false;}
      if(HbuQFgXOoW == true){HbuQFgXOoW = false;}
      if(eiTtKAOUqt == true){eiTtKAOUqt = false;}
      if(lwoUiDuKmw == true){lwoUiDuKmw = false;}
      if(CXmpSeWWwj == true){CXmpSeWWwj = false;}
      if(FArctygSKC == true){FArctygSKC = false;}
      if(IZHjYLlagC == true){IZHjYLlagC = false;}
      if(lNasTHwcbf == true){lNasTHwcbf = false;}
      if(dqXHokDLZk == true){dqXHokDLZk = false;}
      if(VbAjncPCQG == true){VbAjncPCQG = false;}
      if(rwotyrZzIm == true){rwotyrZzIm = false;}
      if(CDqdYQBAum == true){CDqdYQBAum = false;}
      if(IZAwfJNpEq == true){IZAwfJNpEq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLQLIGOAYO
{ 
  void SFyjjnaPLD()
  { 
      bool OmKsNBzrBI = false;
      bool XpYnZPPiPC = false;
      bool shFqymNdsZ = false;
      bool gPHEmCFXOq = false;
      bool PQEdouYmzU = false;
      bool WdojMfhSta = false;
      bool mVzaaHhUBX = false;
      bool JqTYmcdaBC = false;
      bool NZdYCCaXqG = false;
      bool UlcnDsQcCg = false;
      bool NEkbKfKQxj = false;
      bool CGRrMNqaYY = false;
      bool gKcuCXNeUs = false;
      bool LBYUoJnCNW = false;
      bool qJZGENUkap = false;
      bool BpDdACapYm = false;
      bool ReuDYAgxDD = false;
      bool YoMCgWjVqo = false;
      bool CcDeqUyuTl = false;
      bool hycaELOWhD = false;
      string WAHzIMuEMc;
      string iTdlqkXjbD;
      string VogPDoEXno;
      string CBelZcETEd;
      string VJoUDSdQJP;
      string NHmYwhSruS;
      string IWPWahoqLO;
      string fDfyhLzMLj;
      string KmOXbtNFpr;
      string JLYkUztSsV;
      string dmEujKaoqj;
      string iGgKIUIquf;
      string TjBTEUdtci;
      string RfSoGXiSnQ;
      string TYNFICeNcA;
      string pCWNCsljpO;
      string fgLIRCnqDj;
      string loCdMtVuKB;
      string oPQcrPJFlM;
      string lybYkmMFmG;
      if(WAHzIMuEMc == dmEujKaoqj){OmKsNBzrBI = true;}
      else if(dmEujKaoqj == WAHzIMuEMc){NEkbKfKQxj = true;}
      if(iTdlqkXjbD == iGgKIUIquf){XpYnZPPiPC = true;}
      else if(iGgKIUIquf == iTdlqkXjbD){CGRrMNqaYY = true;}
      if(VogPDoEXno == TjBTEUdtci){shFqymNdsZ = true;}
      else if(TjBTEUdtci == VogPDoEXno){gKcuCXNeUs = true;}
      if(CBelZcETEd == RfSoGXiSnQ){gPHEmCFXOq = true;}
      else if(RfSoGXiSnQ == CBelZcETEd){LBYUoJnCNW = true;}
      if(VJoUDSdQJP == TYNFICeNcA){PQEdouYmzU = true;}
      else if(TYNFICeNcA == VJoUDSdQJP){qJZGENUkap = true;}
      if(NHmYwhSruS == pCWNCsljpO){WdojMfhSta = true;}
      else if(pCWNCsljpO == NHmYwhSruS){BpDdACapYm = true;}
      if(IWPWahoqLO == fgLIRCnqDj){mVzaaHhUBX = true;}
      else if(fgLIRCnqDj == IWPWahoqLO){ReuDYAgxDD = true;}
      if(fDfyhLzMLj == loCdMtVuKB){JqTYmcdaBC = true;}
      if(KmOXbtNFpr == oPQcrPJFlM){NZdYCCaXqG = true;}
      if(JLYkUztSsV == lybYkmMFmG){UlcnDsQcCg = true;}
      while(loCdMtVuKB == fDfyhLzMLj){YoMCgWjVqo = true;}
      while(oPQcrPJFlM == oPQcrPJFlM){CcDeqUyuTl = true;}
      while(lybYkmMFmG == lybYkmMFmG){hycaELOWhD = true;}
      if(OmKsNBzrBI == true){OmKsNBzrBI = false;}
      if(XpYnZPPiPC == true){XpYnZPPiPC = false;}
      if(shFqymNdsZ == true){shFqymNdsZ = false;}
      if(gPHEmCFXOq == true){gPHEmCFXOq = false;}
      if(PQEdouYmzU == true){PQEdouYmzU = false;}
      if(WdojMfhSta == true){WdojMfhSta = false;}
      if(mVzaaHhUBX == true){mVzaaHhUBX = false;}
      if(JqTYmcdaBC == true){JqTYmcdaBC = false;}
      if(NZdYCCaXqG == true){NZdYCCaXqG = false;}
      if(UlcnDsQcCg == true){UlcnDsQcCg = false;}
      if(NEkbKfKQxj == true){NEkbKfKQxj = false;}
      if(CGRrMNqaYY == true){CGRrMNqaYY = false;}
      if(gKcuCXNeUs == true){gKcuCXNeUs = false;}
      if(LBYUoJnCNW == true){LBYUoJnCNW = false;}
      if(qJZGENUkap == true){qJZGENUkap = false;}
      if(BpDdACapYm == true){BpDdACapYm = false;}
      if(ReuDYAgxDD == true){ReuDYAgxDD = false;}
      if(YoMCgWjVqo == true){YoMCgWjVqo = false;}
      if(CcDeqUyuTl == true){CcDeqUyuTl = false;}
      if(hycaELOWhD == true){hycaELOWhD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLRGFSZNQP
{ 
  void xNungftVIs()
  { 
      bool tgDiclsYDZ = false;
      bool ZsVmWHtcCj = false;
      bool MhkkbBKfxG = false;
      bool feuSPlqTto = false;
      bool hcVRfkcAuO = false;
      bool mtqhlLuRGa = false;
      bool bNawtuyDXj = false;
      bool PaiNBjMSFp = false;
      bool YKjhTkmMgE = false;
      bool qZMSMUBYXj = false;
      bool mZbLzLKcgB = false;
      bool zbLPCRdrcI = false;
      bool HkVSspNQBg = false;
      bool imuUDyhYiH = false;
      bool ZKffEONwPt = false;
      bool pIwPcCDJSJ = false;
      bool xtbzSMgqMD = false;
      bool jFJUhxEpNd = false;
      bool bRAGpZperA = false;
      bool tXFZJfhgMr = false;
      string VhIyVZcRAX;
      string zrJRXUVrif;
      string ydciCodxip;
      string kwiGOhhnQO;
      string AgwzIDCWAG;
      string ZQVVxqEYwf;
      string wfiJmCICCo;
      string lhbTfRgday;
      string lHwbQTaNJX;
      string cIrjSTylLF;
      string tzTKTroBpe;
      string JZyxsniGsT;
      string bureMdorBL;
      string TuRUElmkIY;
      string eYXdNCKupd;
      string jqsrcyHnyp;
      string CwAdLOHcrH;
      string BxyUoDXNRK;
      string TtCWabBZrG;
      string ezmRWhXsSy;
      if(VhIyVZcRAX == tzTKTroBpe){tgDiclsYDZ = true;}
      else if(tzTKTroBpe == VhIyVZcRAX){mZbLzLKcgB = true;}
      if(zrJRXUVrif == JZyxsniGsT){ZsVmWHtcCj = true;}
      else if(JZyxsniGsT == zrJRXUVrif){zbLPCRdrcI = true;}
      if(ydciCodxip == bureMdorBL){MhkkbBKfxG = true;}
      else if(bureMdorBL == ydciCodxip){HkVSspNQBg = true;}
      if(kwiGOhhnQO == TuRUElmkIY){feuSPlqTto = true;}
      else if(TuRUElmkIY == kwiGOhhnQO){imuUDyhYiH = true;}
      if(AgwzIDCWAG == eYXdNCKupd){hcVRfkcAuO = true;}
      else if(eYXdNCKupd == AgwzIDCWAG){ZKffEONwPt = true;}
      if(ZQVVxqEYwf == jqsrcyHnyp){mtqhlLuRGa = true;}
      else if(jqsrcyHnyp == ZQVVxqEYwf){pIwPcCDJSJ = true;}
      if(wfiJmCICCo == CwAdLOHcrH){bNawtuyDXj = true;}
      else if(CwAdLOHcrH == wfiJmCICCo){xtbzSMgqMD = true;}
      if(lhbTfRgday == BxyUoDXNRK){PaiNBjMSFp = true;}
      if(lHwbQTaNJX == TtCWabBZrG){YKjhTkmMgE = true;}
      if(cIrjSTylLF == ezmRWhXsSy){qZMSMUBYXj = true;}
      while(BxyUoDXNRK == lhbTfRgday){jFJUhxEpNd = true;}
      while(TtCWabBZrG == TtCWabBZrG){bRAGpZperA = true;}
      while(ezmRWhXsSy == ezmRWhXsSy){tXFZJfhgMr = true;}
      if(tgDiclsYDZ == true){tgDiclsYDZ = false;}
      if(ZsVmWHtcCj == true){ZsVmWHtcCj = false;}
      if(MhkkbBKfxG == true){MhkkbBKfxG = false;}
      if(feuSPlqTto == true){feuSPlqTto = false;}
      if(hcVRfkcAuO == true){hcVRfkcAuO = false;}
      if(mtqhlLuRGa == true){mtqhlLuRGa = false;}
      if(bNawtuyDXj == true){bNawtuyDXj = false;}
      if(PaiNBjMSFp == true){PaiNBjMSFp = false;}
      if(YKjhTkmMgE == true){YKjhTkmMgE = false;}
      if(qZMSMUBYXj == true){qZMSMUBYXj = false;}
      if(mZbLzLKcgB == true){mZbLzLKcgB = false;}
      if(zbLPCRdrcI == true){zbLPCRdrcI = false;}
      if(HkVSspNQBg == true){HkVSspNQBg = false;}
      if(imuUDyhYiH == true){imuUDyhYiH = false;}
      if(ZKffEONwPt == true){ZKffEONwPt = false;}
      if(pIwPcCDJSJ == true){pIwPcCDJSJ = false;}
      if(xtbzSMgqMD == true){xtbzSMgqMD = false;}
      if(jFJUhxEpNd == true){jFJUhxEpNd = false;}
      if(bRAGpZperA == true){bRAGpZperA = false;}
      if(tXFZJfhgMr == true){tXFZJfhgMr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVHEDAENLK
{ 
  void KVOWeBqLff()
  { 
      bool KVBewhlASp = false;
      bool UhjBeaFdMd = false;
      bool ThXRgTrrHO = false;
      bool ZCpHrRqXPH = false;
      bool mZRGDNbEll = false;
      bool AGXKjcyjxc = false;
      bool osrEQSqbIN = false;
      bool jgOEpsQRNS = false;
      bool qmFVNSdfWP = false;
      bool TGZmSshMpk = false;
      bool WzwYCSrSTq = false;
      bool MfVekBmWpx = false;
      bool nLErtdGalx = false;
      bool KDacwrqgTt = false;
      bool aLLfDmjuBQ = false;
      bool GLWsxKtDdY = false;
      bool MQgWfIEshs = false;
      bool KGDuWcAYoH = false;
      bool sKZUqzghel = false;
      bool xmCuhJdnAt = false;
      string udmgwRCCjh;
      string wmeBQNLlUR;
      string ciodpORqZt;
      string NxzuCLVIdP;
      string DSNroXUFrp;
      string HcmmgMoJqh;
      string zKcoTzmjzE;
      string rCIFOKUwoS;
      string tMziljKLNo;
      string WMRwPrpYXp;
      string jjFmyFUgYW;
      string qrUYmmLtCj;
      string naWJhfkLpW;
      string UwYyhJHLjg;
      string OcmqydrrIc;
      string guVnBINuFS;
      string TIqCCtSVpc;
      string fzJVULneLD;
      string nrDMoYakxY;
      string wLGRNGkknD;
      if(udmgwRCCjh == jjFmyFUgYW){KVBewhlASp = true;}
      else if(jjFmyFUgYW == udmgwRCCjh){WzwYCSrSTq = true;}
      if(wmeBQNLlUR == qrUYmmLtCj){UhjBeaFdMd = true;}
      else if(qrUYmmLtCj == wmeBQNLlUR){MfVekBmWpx = true;}
      if(ciodpORqZt == naWJhfkLpW){ThXRgTrrHO = true;}
      else if(naWJhfkLpW == ciodpORqZt){nLErtdGalx = true;}
      if(NxzuCLVIdP == UwYyhJHLjg){ZCpHrRqXPH = true;}
      else if(UwYyhJHLjg == NxzuCLVIdP){KDacwrqgTt = true;}
      if(DSNroXUFrp == OcmqydrrIc){mZRGDNbEll = true;}
      else if(OcmqydrrIc == DSNroXUFrp){aLLfDmjuBQ = true;}
      if(HcmmgMoJqh == guVnBINuFS){AGXKjcyjxc = true;}
      else if(guVnBINuFS == HcmmgMoJqh){GLWsxKtDdY = true;}
      if(zKcoTzmjzE == TIqCCtSVpc){osrEQSqbIN = true;}
      else if(TIqCCtSVpc == zKcoTzmjzE){MQgWfIEshs = true;}
      if(rCIFOKUwoS == fzJVULneLD){jgOEpsQRNS = true;}
      if(tMziljKLNo == nrDMoYakxY){qmFVNSdfWP = true;}
      if(WMRwPrpYXp == wLGRNGkknD){TGZmSshMpk = true;}
      while(fzJVULneLD == rCIFOKUwoS){KGDuWcAYoH = true;}
      while(nrDMoYakxY == nrDMoYakxY){sKZUqzghel = true;}
      while(wLGRNGkknD == wLGRNGkknD){xmCuhJdnAt = true;}
      if(KVBewhlASp == true){KVBewhlASp = false;}
      if(UhjBeaFdMd == true){UhjBeaFdMd = false;}
      if(ThXRgTrrHO == true){ThXRgTrrHO = false;}
      if(ZCpHrRqXPH == true){ZCpHrRqXPH = false;}
      if(mZRGDNbEll == true){mZRGDNbEll = false;}
      if(AGXKjcyjxc == true){AGXKjcyjxc = false;}
      if(osrEQSqbIN == true){osrEQSqbIN = false;}
      if(jgOEpsQRNS == true){jgOEpsQRNS = false;}
      if(qmFVNSdfWP == true){qmFVNSdfWP = false;}
      if(TGZmSshMpk == true){TGZmSshMpk = false;}
      if(WzwYCSrSTq == true){WzwYCSrSTq = false;}
      if(MfVekBmWpx == true){MfVekBmWpx = false;}
      if(nLErtdGalx == true){nLErtdGalx = false;}
      if(KDacwrqgTt == true){KDacwrqgTt = false;}
      if(aLLfDmjuBQ == true){aLLfDmjuBQ = false;}
      if(GLWsxKtDdY == true){GLWsxKtDdY = false;}
      if(MQgWfIEshs == true){MQgWfIEshs = false;}
      if(KGDuWcAYoH == true){KGDuWcAYoH = false;}
      if(sKZUqzghel == true){sKZUqzghel = false;}
      if(xmCuhJdnAt == true){xmCuhJdnAt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSLWWEKXEQ
{ 
  void XRZaBERmdQ()
  { 
      bool kzcjVpIIwD = false;
      bool dskhbIGAzA = false;
      bool oKnwZMzBHs = false;
      bool PXiMJdaapt = false;
      bool yOhuxPHmfy = false;
      bool xHSptZLfKJ = false;
      bool pGACmGKYXx = false;
      bool hfJEBabsyJ = false;
      bool EMUIuIErRj = false;
      bool StQgErNfHq = false;
      bool EiPiQRxNoT = false;
      bool yShAEdkrHe = false;
      bool BRHndnOcAI = false;
      bool MwkGFVwlrd = false;
      bool LqDxlAMQba = false;
      bool HVYcplbbEc = false;
      bool CTMfHBgati = false;
      bool gyAcSJOJBd = false;
      bool ayBZBpXIQT = false;
      bool tUgOareXoj = false;
      string rqfXgJTnpF;
      string XTaRAaPKhU;
      string TfoXxFbDcW;
      string SMqaRqIsEn;
      string tCbBdpnZHp;
      string lBsGxMCHZa;
      string gPLTlKczzJ;
      string SWGtZQDnsH;
      string QBwljRTjcF;
      string nBScGdqHOS;
      string MoaxXPuzgf;
      string IONSKfTYjU;
      string qsVsURDcmu;
      string ZuYaubZyOT;
      string WTDxxZmASa;
      string KSXtaTSgcG;
      string MRMkGMomXh;
      string FUKPyXpYwt;
      string dDKLkGXeza;
      string IrVIHEHSpj;
      if(rqfXgJTnpF == MoaxXPuzgf){kzcjVpIIwD = true;}
      else if(MoaxXPuzgf == rqfXgJTnpF){EiPiQRxNoT = true;}
      if(XTaRAaPKhU == IONSKfTYjU){dskhbIGAzA = true;}
      else if(IONSKfTYjU == XTaRAaPKhU){yShAEdkrHe = true;}
      if(TfoXxFbDcW == qsVsURDcmu){oKnwZMzBHs = true;}
      else if(qsVsURDcmu == TfoXxFbDcW){BRHndnOcAI = true;}
      if(SMqaRqIsEn == ZuYaubZyOT){PXiMJdaapt = true;}
      else if(ZuYaubZyOT == SMqaRqIsEn){MwkGFVwlrd = true;}
      if(tCbBdpnZHp == WTDxxZmASa){yOhuxPHmfy = true;}
      else if(WTDxxZmASa == tCbBdpnZHp){LqDxlAMQba = true;}
      if(lBsGxMCHZa == KSXtaTSgcG){xHSptZLfKJ = true;}
      else if(KSXtaTSgcG == lBsGxMCHZa){HVYcplbbEc = true;}
      if(gPLTlKczzJ == MRMkGMomXh){pGACmGKYXx = true;}
      else if(MRMkGMomXh == gPLTlKczzJ){CTMfHBgati = true;}
      if(SWGtZQDnsH == FUKPyXpYwt){hfJEBabsyJ = true;}
      if(QBwljRTjcF == dDKLkGXeza){EMUIuIErRj = true;}
      if(nBScGdqHOS == IrVIHEHSpj){StQgErNfHq = true;}
      while(FUKPyXpYwt == SWGtZQDnsH){gyAcSJOJBd = true;}
      while(dDKLkGXeza == dDKLkGXeza){ayBZBpXIQT = true;}
      while(IrVIHEHSpj == IrVIHEHSpj){tUgOareXoj = true;}
      if(kzcjVpIIwD == true){kzcjVpIIwD = false;}
      if(dskhbIGAzA == true){dskhbIGAzA = false;}
      if(oKnwZMzBHs == true){oKnwZMzBHs = false;}
      if(PXiMJdaapt == true){PXiMJdaapt = false;}
      if(yOhuxPHmfy == true){yOhuxPHmfy = false;}
      if(xHSptZLfKJ == true){xHSptZLfKJ = false;}
      if(pGACmGKYXx == true){pGACmGKYXx = false;}
      if(hfJEBabsyJ == true){hfJEBabsyJ = false;}
      if(EMUIuIErRj == true){EMUIuIErRj = false;}
      if(StQgErNfHq == true){StQgErNfHq = false;}
      if(EiPiQRxNoT == true){EiPiQRxNoT = false;}
      if(yShAEdkrHe == true){yShAEdkrHe = false;}
      if(BRHndnOcAI == true){BRHndnOcAI = false;}
      if(MwkGFVwlrd == true){MwkGFVwlrd = false;}
      if(LqDxlAMQba == true){LqDxlAMQba = false;}
      if(HVYcplbbEc == true){HVYcplbbEc = false;}
      if(CTMfHBgati == true){CTMfHBgati = false;}
      if(gyAcSJOJBd == true){gyAcSJOJBd = false;}
      if(ayBZBpXIQT == true){ayBZBpXIQT = false;}
      if(tUgOareXoj == true){tUgOareXoj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKAVSCPQTX
{ 
  void rWMakoJtCR()
  { 
      bool slWbTQSkLo = false;
      bool UiFFHSEzum = false;
      bool OjCeoccxFO = false;
      bool WrXhYcGRAi = false;
      bool mnOmGwjzyz = false;
      bool FdEWqJirmq = false;
      bool nUewRbLXfd = false;
      bool MlzMAaUPXs = false;
      bool rczGJrmApP = false;
      bool tOeJuRJRVd = false;
      bool jMSTmSerWQ = false;
      bool nTTsyKVYmY = false;
      bool oKgQjyHpQh = false;
      bool RDstIeKfSp = false;
      bool NudZbatkKk = false;
      bool wjdxoYeCjn = false;
      bool LoanzjZYkT = false;
      bool ApFxKsgHoI = false;
      bool DVeflgZwEi = false;
      bool AHuddXUoaq = false;
      string nnlFjLmzCk;
      string WajaVXiqCw;
      string tilbWQtHkx;
      string AwtXXaZFiG;
      string nQCFRgPglC;
      string fzWDzECJiT;
      string QeOFjZfLDt;
      string xcHwIdgfKo;
      string BNUhRBZqYT;
      string YQWPoJCxUq;
      string BEdrECqauU;
      string XVytRDKfmi;
      string AnliUgGrGz;
      string biLSnxjbcO;
      string JywEuDRcxl;
      string yVJkqMRtWX;
      string wzTwsoJeGU;
      string ShDYZBrhnR;
      string PctTAFZZba;
      string epEFSKdAKG;
      if(nnlFjLmzCk == BEdrECqauU){slWbTQSkLo = true;}
      else if(BEdrECqauU == nnlFjLmzCk){jMSTmSerWQ = true;}
      if(WajaVXiqCw == XVytRDKfmi){UiFFHSEzum = true;}
      else if(XVytRDKfmi == WajaVXiqCw){nTTsyKVYmY = true;}
      if(tilbWQtHkx == AnliUgGrGz){OjCeoccxFO = true;}
      else if(AnliUgGrGz == tilbWQtHkx){oKgQjyHpQh = true;}
      if(AwtXXaZFiG == biLSnxjbcO){WrXhYcGRAi = true;}
      else if(biLSnxjbcO == AwtXXaZFiG){RDstIeKfSp = true;}
      if(nQCFRgPglC == JywEuDRcxl){mnOmGwjzyz = true;}
      else if(JywEuDRcxl == nQCFRgPglC){NudZbatkKk = true;}
      if(fzWDzECJiT == yVJkqMRtWX){FdEWqJirmq = true;}
      else if(yVJkqMRtWX == fzWDzECJiT){wjdxoYeCjn = true;}
      if(QeOFjZfLDt == wzTwsoJeGU){nUewRbLXfd = true;}
      else if(wzTwsoJeGU == QeOFjZfLDt){LoanzjZYkT = true;}
      if(xcHwIdgfKo == ShDYZBrhnR){MlzMAaUPXs = true;}
      if(BNUhRBZqYT == PctTAFZZba){rczGJrmApP = true;}
      if(YQWPoJCxUq == epEFSKdAKG){tOeJuRJRVd = true;}
      while(ShDYZBrhnR == xcHwIdgfKo){ApFxKsgHoI = true;}
      while(PctTAFZZba == PctTAFZZba){DVeflgZwEi = true;}
      while(epEFSKdAKG == epEFSKdAKG){AHuddXUoaq = true;}
      if(slWbTQSkLo == true){slWbTQSkLo = false;}
      if(UiFFHSEzum == true){UiFFHSEzum = false;}
      if(OjCeoccxFO == true){OjCeoccxFO = false;}
      if(WrXhYcGRAi == true){WrXhYcGRAi = false;}
      if(mnOmGwjzyz == true){mnOmGwjzyz = false;}
      if(FdEWqJirmq == true){FdEWqJirmq = false;}
      if(nUewRbLXfd == true){nUewRbLXfd = false;}
      if(MlzMAaUPXs == true){MlzMAaUPXs = false;}
      if(rczGJrmApP == true){rczGJrmApP = false;}
      if(tOeJuRJRVd == true){tOeJuRJRVd = false;}
      if(jMSTmSerWQ == true){jMSTmSerWQ = false;}
      if(nTTsyKVYmY == true){nTTsyKVYmY = false;}
      if(oKgQjyHpQh == true){oKgQjyHpQh = false;}
      if(RDstIeKfSp == true){RDstIeKfSp = false;}
      if(NudZbatkKk == true){NudZbatkKk = false;}
      if(wjdxoYeCjn == true){wjdxoYeCjn = false;}
      if(LoanzjZYkT == true){LoanzjZYkT = false;}
      if(ApFxKsgHoI == true){ApFxKsgHoI = false;}
      if(DVeflgZwEi == true){DVeflgZwEi = false;}
      if(AHuddXUoaq == true){AHuddXUoaq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQWJFEJIPM
{ 
  void VAKYGAOGls()
  { 
      bool SQLUZjuhhM = false;
      bool DFgMtBBnIy = false;
      bool IJgbILoOgk = false;
      bool NyBEmOxxmQ = false;
      bool lAukNLJqOt = false;
      bool ZMPllIjiMO = false;
      bool tfBxzFDcYf = false;
      bool DEBqLINwOw = false;
      bool ByzmKAiPRd = false;
      bool eOjXVFyykH = false;
      bool HfRipVLXZc = false;
      bool umTPMwfOly = false;
      bool WnKuAoTcVG = false;
      bool JPKGnUfQwo = false;
      bool oKpniqtTKZ = false;
      bool YjMmkTVWhB = false;
      bool BhCTTfcNbq = false;
      bool PPRwILyVLJ = false;
      bool tASugZCWVT = false;
      bool zJhtnHIVUD = false;
      string PSiYpZexRn;
      string gBJEwnBKBh;
      string tqXPSBNNGG;
      string BXeHwOQwTM;
      string KRErAzwZMX;
      string cYfKJYtSFo;
      string LQpLlIWBIg;
      string XEqoXcmfPT;
      string FnBiccrTyX;
      string UxqeAsasFq;
      string cuQezXgpmg;
      string kNCkiXPHhJ;
      string QCDkMZNMod;
      string BtZYqJWViF;
      string wBfQlGuFub;
      string dTLwaZrfSZ;
      string JTBIfqndtZ;
      string BsXcNOVlzF;
      string eIRMAghdxR;
      string RpDJubAXjt;
      if(PSiYpZexRn == cuQezXgpmg){SQLUZjuhhM = true;}
      else if(cuQezXgpmg == PSiYpZexRn){HfRipVLXZc = true;}
      if(gBJEwnBKBh == kNCkiXPHhJ){DFgMtBBnIy = true;}
      else if(kNCkiXPHhJ == gBJEwnBKBh){umTPMwfOly = true;}
      if(tqXPSBNNGG == QCDkMZNMod){IJgbILoOgk = true;}
      else if(QCDkMZNMod == tqXPSBNNGG){WnKuAoTcVG = true;}
      if(BXeHwOQwTM == BtZYqJWViF){NyBEmOxxmQ = true;}
      else if(BtZYqJWViF == BXeHwOQwTM){JPKGnUfQwo = true;}
      if(KRErAzwZMX == wBfQlGuFub){lAukNLJqOt = true;}
      else if(wBfQlGuFub == KRErAzwZMX){oKpniqtTKZ = true;}
      if(cYfKJYtSFo == dTLwaZrfSZ){ZMPllIjiMO = true;}
      else if(dTLwaZrfSZ == cYfKJYtSFo){YjMmkTVWhB = true;}
      if(LQpLlIWBIg == JTBIfqndtZ){tfBxzFDcYf = true;}
      else if(JTBIfqndtZ == LQpLlIWBIg){BhCTTfcNbq = true;}
      if(XEqoXcmfPT == BsXcNOVlzF){DEBqLINwOw = true;}
      if(FnBiccrTyX == eIRMAghdxR){ByzmKAiPRd = true;}
      if(UxqeAsasFq == RpDJubAXjt){eOjXVFyykH = true;}
      while(BsXcNOVlzF == XEqoXcmfPT){PPRwILyVLJ = true;}
      while(eIRMAghdxR == eIRMAghdxR){tASugZCWVT = true;}
      while(RpDJubAXjt == RpDJubAXjt){zJhtnHIVUD = true;}
      if(SQLUZjuhhM == true){SQLUZjuhhM = false;}
      if(DFgMtBBnIy == true){DFgMtBBnIy = false;}
      if(IJgbILoOgk == true){IJgbILoOgk = false;}
      if(NyBEmOxxmQ == true){NyBEmOxxmQ = false;}
      if(lAukNLJqOt == true){lAukNLJqOt = false;}
      if(ZMPllIjiMO == true){ZMPllIjiMO = false;}
      if(tfBxzFDcYf == true){tfBxzFDcYf = false;}
      if(DEBqLINwOw == true){DEBqLINwOw = false;}
      if(ByzmKAiPRd == true){ByzmKAiPRd = false;}
      if(eOjXVFyykH == true){eOjXVFyykH = false;}
      if(HfRipVLXZc == true){HfRipVLXZc = false;}
      if(umTPMwfOly == true){umTPMwfOly = false;}
      if(WnKuAoTcVG == true){WnKuAoTcVG = false;}
      if(JPKGnUfQwo == true){JPKGnUfQwo = false;}
      if(oKpniqtTKZ == true){oKpniqtTKZ = false;}
      if(YjMmkTVWhB == true){YjMmkTVWhB = false;}
      if(BhCTTfcNbq == true){BhCTTfcNbq = false;}
      if(PPRwILyVLJ == true){PPRwILyVLJ = false;}
      if(tASugZCWVT == true){tASugZCWVT = false;}
      if(zJhtnHIVUD == true){zJhtnHIVUD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGCFHDCBBC
{ 
  void ubCuDbPMgJ()
  { 
      bool TYpzZtUFRE = false;
      bool RqOwOwNoks = false;
      bool cfhXHCDejh = false;
      bool bDadbpaRpO = false;
      bool yehKySnnij = false;
      bool rOimynpSrX = false;
      bool qoUjbOPjUX = false;
      bool VwyVuyxXZn = false;
      bool OOwAoNUnfm = false;
      bool AIZSXIJxij = false;
      bool DDTKOwQMqz = false;
      bool pSrDJbsUtO = false;
      bool sbEgXNVeym = false;
      bool oAopkKukks = false;
      bool wHwfxgPWJu = false;
      bool PnDUpazllB = false;
      bool akOEKpcCRy = false;
      bool fHjARkfXjq = false;
      bool xyVCXAwUzJ = false;
      bool KJzjSKrqVH = false;
      string FddecQXSFX;
      string OcIcxwbFRh;
      string fsBFAqFnQm;
      string sMmeXOqEdQ;
      string lHBMdRfTVV;
      string hqBjEMbXdl;
      string LjBRdCocFh;
      string FWbAuYqobi;
      string LkRtFCKCaK;
      string mSZrFCGihb;
      string bCOnQKPBnf;
      string VmwuaaSGMb;
      string qlCtulwius;
      string SHGzGIVccu;
      string mJOtozVeRd;
      string jzWGkpzTre;
      string NfFtNNfxnR;
      string EodRngXIFu;
      string PRRQJTjAOQ;
      string JCkygGETga;
      if(FddecQXSFX == bCOnQKPBnf){TYpzZtUFRE = true;}
      else if(bCOnQKPBnf == FddecQXSFX){DDTKOwQMqz = true;}
      if(OcIcxwbFRh == VmwuaaSGMb){RqOwOwNoks = true;}
      else if(VmwuaaSGMb == OcIcxwbFRh){pSrDJbsUtO = true;}
      if(fsBFAqFnQm == qlCtulwius){cfhXHCDejh = true;}
      else if(qlCtulwius == fsBFAqFnQm){sbEgXNVeym = true;}
      if(sMmeXOqEdQ == SHGzGIVccu){bDadbpaRpO = true;}
      else if(SHGzGIVccu == sMmeXOqEdQ){oAopkKukks = true;}
      if(lHBMdRfTVV == mJOtozVeRd){yehKySnnij = true;}
      else if(mJOtozVeRd == lHBMdRfTVV){wHwfxgPWJu = true;}
      if(hqBjEMbXdl == jzWGkpzTre){rOimynpSrX = true;}
      else if(jzWGkpzTre == hqBjEMbXdl){PnDUpazllB = true;}
      if(LjBRdCocFh == NfFtNNfxnR){qoUjbOPjUX = true;}
      else if(NfFtNNfxnR == LjBRdCocFh){akOEKpcCRy = true;}
      if(FWbAuYqobi == EodRngXIFu){VwyVuyxXZn = true;}
      if(LkRtFCKCaK == PRRQJTjAOQ){OOwAoNUnfm = true;}
      if(mSZrFCGihb == JCkygGETga){AIZSXIJxij = true;}
      while(EodRngXIFu == FWbAuYqobi){fHjARkfXjq = true;}
      while(PRRQJTjAOQ == PRRQJTjAOQ){xyVCXAwUzJ = true;}
      while(JCkygGETga == JCkygGETga){KJzjSKrqVH = true;}
      if(TYpzZtUFRE == true){TYpzZtUFRE = false;}
      if(RqOwOwNoks == true){RqOwOwNoks = false;}
      if(cfhXHCDejh == true){cfhXHCDejh = false;}
      if(bDadbpaRpO == true){bDadbpaRpO = false;}
      if(yehKySnnij == true){yehKySnnij = false;}
      if(rOimynpSrX == true){rOimynpSrX = false;}
      if(qoUjbOPjUX == true){qoUjbOPjUX = false;}
      if(VwyVuyxXZn == true){VwyVuyxXZn = false;}
      if(OOwAoNUnfm == true){OOwAoNUnfm = false;}
      if(AIZSXIJxij == true){AIZSXIJxij = false;}
      if(DDTKOwQMqz == true){DDTKOwQMqz = false;}
      if(pSrDJbsUtO == true){pSrDJbsUtO = false;}
      if(sbEgXNVeym == true){sbEgXNVeym = false;}
      if(oAopkKukks == true){oAopkKukks = false;}
      if(wHwfxgPWJu == true){wHwfxgPWJu = false;}
      if(PnDUpazllB == true){PnDUpazllB = false;}
      if(akOEKpcCRy == true){akOEKpcCRy = false;}
      if(fHjARkfXjq == true){fHjARkfXjq = false;}
      if(xyVCXAwUzJ == true){xyVCXAwUzJ = false;}
      if(KJzjSKrqVH == true){KJzjSKrqVH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMMCFBCTED
{ 
  void mkIiZFccRV()
  { 
      bool AoUPCoKmjn = false;
      bool XpPITfqVFa = false;
      bool SOLIlmlVCB = false;
      bool rnZhuYCRRe = false;
      bool tmLGNJQtID = false;
      bool MXkTpkdMcO = false;
      bool DnjiujQhMt = false;
      bool cZDZffDEuc = false;
      bool WqNynUCFrK = false;
      bool tpnCbFCcKc = false;
      bool rihNZmTKmK = false;
      bool gZQzrMakta = false;
      bool gLoBAmkAya = false;
      bool casRjmIzXA = false;
      bool AqRgcUYnKO = false;
      bool eRhiwgsfNm = false;
      bool CTMMhGfzPE = false;
      bool DaMtaotIXe = false;
      bool NwpiuLrKVD = false;
      bool sblkygeEzV = false;
      string jGjEBWImOu;
      string GbGQasPAAR;
      string FxAtdlZrbK;
      string cUoqeMMaPc;
      string qaBpfmUkYZ;
      string frEzWmFoaP;
      string xPKDSklOkN;
      string gnjWadwJOp;
      string QnSCejQpTr;
      string HWAAfaQxXt;
      string AFALrqHgYs;
      string qwajyIwHYh;
      string UwtrGKnjqz;
      string NykUpLnHJm;
      string ciQaBKwPCW;
      string dIYoZDKHEh;
      string DXpZfrKGtm;
      string UoxlFkeTqw;
      string OXgUUEZutl;
      string AgDbiEsqtI;
      if(jGjEBWImOu == AFALrqHgYs){AoUPCoKmjn = true;}
      else if(AFALrqHgYs == jGjEBWImOu){rihNZmTKmK = true;}
      if(GbGQasPAAR == qwajyIwHYh){XpPITfqVFa = true;}
      else if(qwajyIwHYh == GbGQasPAAR){gZQzrMakta = true;}
      if(FxAtdlZrbK == UwtrGKnjqz){SOLIlmlVCB = true;}
      else if(UwtrGKnjqz == FxAtdlZrbK){gLoBAmkAya = true;}
      if(cUoqeMMaPc == NykUpLnHJm){rnZhuYCRRe = true;}
      else if(NykUpLnHJm == cUoqeMMaPc){casRjmIzXA = true;}
      if(qaBpfmUkYZ == ciQaBKwPCW){tmLGNJQtID = true;}
      else if(ciQaBKwPCW == qaBpfmUkYZ){AqRgcUYnKO = true;}
      if(frEzWmFoaP == dIYoZDKHEh){MXkTpkdMcO = true;}
      else if(dIYoZDKHEh == frEzWmFoaP){eRhiwgsfNm = true;}
      if(xPKDSklOkN == DXpZfrKGtm){DnjiujQhMt = true;}
      else if(DXpZfrKGtm == xPKDSklOkN){CTMMhGfzPE = true;}
      if(gnjWadwJOp == UoxlFkeTqw){cZDZffDEuc = true;}
      if(QnSCejQpTr == OXgUUEZutl){WqNynUCFrK = true;}
      if(HWAAfaQxXt == AgDbiEsqtI){tpnCbFCcKc = true;}
      while(UoxlFkeTqw == gnjWadwJOp){DaMtaotIXe = true;}
      while(OXgUUEZutl == OXgUUEZutl){NwpiuLrKVD = true;}
      while(AgDbiEsqtI == AgDbiEsqtI){sblkygeEzV = true;}
      if(AoUPCoKmjn == true){AoUPCoKmjn = false;}
      if(XpPITfqVFa == true){XpPITfqVFa = false;}
      if(SOLIlmlVCB == true){SOLIlmlVCB = false;}
      if(rnZhuYCRRe == true){rnZhuYCRRe = false;}
      if(tmLGNJQtID == true){tmLGNJQtID = false;}
      if(MXkTpkdMcO == true){MXkTpkdMcO = false;}
      if(DnjiujQhMt == true){DnjiujQhMt = false;}
      if(cZDZffDEuc == true){cZDZffDEuc = false;}
      if(WqNynUCFrK == true){WqNynUCFrK = false;}
      if(tpnCbFCcKc == true){tpnCbFCcKc = false;}
      if(rihNZmTKmK == true){rihNZmTKmK = false;}
      if(gZQzrMakta == true){gZQzrMakta = false;}
      if(gLoBAmkAya == true){gLoBAmkAya = false;}
      if(casRjmIzXA == true){casRjmIzXA = false;}
      if(AqRgcUYnKO == true){AqRgcUYnKO = false;}
      if(eRhiwgsfNm == true){eRhiwgsfNm = false;}
      if(CTMMhGfzPE == true){CTMMhGfzPE = false;}
      if(DaMtaotIXe == true){DaMtaotIXe = false;}
      if(NwpiuLrKVD == true){NwpiuLrKVD = false;}
      if(sblkygeEzV == true){sblkygeEzV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCKWBXHHGZ
{ 
  void TrJVyabyEj()
  { 
      bool zjIUxMufVB = false;
      bool jECXrdoOtY = false;
      bool qzbNetQpkh = false;
      bool HEYUdZIzfL = false;
      bool XOhtxtYqBy = false;
      bool YaZPSAItpC = false;
      bool uEtmtfegtS = false;
      bool UpiiAcQgPk = false;
      bool VZomJfdJBc = false;
      bool RNJcPTTuAQ = false;
      bool PqxhcirqOp = false;
      bool iadFgVPHdN = false;
      bool CUeQBHfFTg = false;
      bool IVfzVdcGJa = false;
      bool nltLtpjEut = false;
      bool DLRlNtLfgV = false;
      bool ClXhgMuejD = false;
      bool rJyDZPZTVK = false;
      bool XbKYcwEtka = false;
      bool RwYnXBOMeg = false;
      string SLyadTeZqO;
      string BsoPYKJZgh;
      string SXYFXHYmbR;
      string pAIXQOSwOp;
      string eIENfHeHpL;
      string dndlAtlrDW;
      string tqxYXBjRyJ;
      string qNKqDJTLZP;
      string cQwQnCVWWW;
      string cZrrumLeoe;
      string XMIgTPcmip;
      string aZSnscugkV;
      string fNtbfRUSuP;
      string ynWurQIPwX;
      string YhngwCHEyR;
      string resSyJRgAC;
      string uKrSrlDXuc;
      string UejNxxYNec;
      string JQUcXStDwh;
      string yaOtbOpUnK;
      if(SLyadTeZqO == XMIgTPcmip){zjIUxMufVB = true;}
      else if(XMIgTPcmip == SLyadTeZqO){PqxhcirqOp = true;}
      if(BsoPYKJZgh == aZSnscugkV){jECXrdoOtY = true;}
      else if(aZSnscugkV == BsoPYKJZgh){iadFgVPHdN = true;}
      if(SXYFXHYmbR == fNtbfRUSuP){qzbNetQpkh = true;}
      else if(fNtbfRUSuP == SXYFXHYmbR){CUeQBHfFTg = true;}
      if(pAIXQOSwOp == ynWurQIPwX){HEYUdZIzfL = true;}
      else if(ynWurQIPwX == pAIXQOSwOp){IVfzVdcGJa = true;}
      if(eIENfHeHpL == YhngwCHEyR){XOhtxtYqBy = true;}
      else if(YhngwCHEyR == eIENfHeHpL){nltLtpjEut = true;}
      if(dndlAtlrDW == resSyJRgAC){YaZPSAItpC = true;}
      else if(resSyJRgAC == dndlAtlrDW){DLRlNtLfgV = true;}
      if(tqxYXBjRyJ == uKrSrlDXuc){uEtmtfegtS = true;}
      else if(uKrSrlDXuc == tqxYXBjRyJ){ClXhgMuejD = true;}
      if(qNKqDJTLZP == UejNxxYNec){UpiiAcQgPk = true;}
      if(cQwQnCVWWW == JQUcXStDwh){VZomJfdJBc = true;}
      if(cZrrumLeoe == yaOtbOpUnK){RNJcPTTuAQ = true;}
      while(UejNxxYNec == qNKqDJTLZP){rJyDZPZTVK = true;}
      while(JQUcXStDwh == JQUcXStDwh){XbKYcwEtka = true;}
      while(yaOtbOpUnK == yaOtbOpUnK){RwYnXBOMeg = true;}
      if(zjIUxMufVB == true){zjIUxMufVB = false;}
      if(jECXrdoOtY == true){jECXrdoOtY = false;}
      if(qzbNetQpkh == true){qzbNetQpkh = false;}
      if(HEYUdZIzfL == true){HEYUdZIzfL = false;}
      if(XOhtxtYqBy == true){XOhtxtYqBy = false;}
      if(YaZPSAItpC == true){YaZPSAItpC = false;}
      if(uEtmtfegtS == true){uEtmtfegtS = false;}
      if(UpiiAcQgPk == true){UpiiAcQgPk = false;}
      if(VZomJfdJBc == true){VZomJfdJBc = false;}
      if(RNJcPTTuAQ == true){RNJcPTTuAQ = false;}
      if(PqxhcirqOp == true){PqxhcirqOp = false;}
      if(iadFgVPHdN == true){iadFgVPHdN = false;}
      if(CUeQBHfFTg == true){CUeQBHfFTg = false;}
      if(IVfzVdcGJa == true){IVfzVdcGJa = false;}
      if(nltLtpjEut == true){nltLtpjEut = false;}
      if(DLRlNtLfgV == true){DLRlNtLfgV = false;}
      if(ClXhgMuejD == true){ClXhgMuejD = false;}
      if(rJyDZPZTVK == true){rJyDZPZTVK = false;}
      if(XbKYcwEtka == true){XbKYcwEtka = false;}
      if(RwYnXBOMeg == true){RwYnXBOMeg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHOLZVHVKS
{ 
  void XwpcwjXwhz()
  { 
      bool pVljdAjgrZ = false;
      bool sZYCkkzemT = false;
      bool ZDoRKGfUse = false;
      bool EsFYLBwkZW = false;
      bool gSXCfiazJP = false;
      bool lWYBnlfTYW = false;
      bool UPmNVzUAqi = false;
      bool nNFPmGfmka = false;
      bool egKdsgUEjY = false;
      bool VbMCCQeJgg = false;
      bool OaIaaXRINg = false;
      bool FsixrnEJTn = false;
      bool dQPRNLBCNV = false;
      bool bWGEMEYjCU = false;
      bool PMpCScsOKO = false;
      bool MVorCyKpNO = false;
      bool WPuqFilekn = false;
      bool OUGzXRZNzj = false;
      bool SmqyJFgNBO = false;
      bool siWmyAQywi = false;
      string sFQMsXMMIX;
      string VCmXTDRPNF;
      string yaGGwTEDUp;
      string BVixHCaKHW;
      string dMICXuZEgw;
      string nBNsnSyKQY;
      string SIrRVzSpQQ;
      string bGHqakREhA;
      string tAVXCzHoIo;
      string EQtiDUTqfY;
      string binQTgsWRC;
      string AsbPeSmTPW;
      string qcgbMLMYnG;
      string RaYJXKMFDU;
      string FkXGnKndDj;
      string hAaIgyBMDI;
      string TUiLkZTSqT;
      string GgPtQGFamB;
      string XiUDXQzPcZ;
      string JABuAkCLUO;
      if(sFQMsXMMIX == binQTgsWRC){pVljdAjgrZ = true;}
      else if(binQTgsWRC == sFQMsXMMIX){OaIaaXRINg = true;}
      if(VCmXTDRPNF == AsbPeSmTPW){sZYCkkzemT = true;}
      else if(AsbPeSmTPW == VCmXTDRPNF){FsixrnEJTn = true;}
      if(yaGGwTEDUp == qcgbMLMYnG){ZDoRKGfUse = true;}
      else if(qcgbMLMYnG == yaGGwTEDUp){dQPRNLBCNV = true;}
      if(BVixHCaKHW == RaYJXKMFDU){EsFYLBwkZW = true;}
      else if(RaYJXKMFDU == BVixHCaKHW){bWGEMEYjCU = true;}
      if(dMICXuZEgw == FkXGnKndDj){gSXCfiazJP = true;}
      else if(FkXGnKndDj == dMICXuZEgw){PMpCScsOKO = true;}
      if(nBNsnSyKQY == hAaIgyBMDI){lWYBnlfTYW = true;}
      else if(hAaIgyBMDI == nBNsnSyKQY){MVorCyKpNO = true;}
      if(SIrRVzSpQQ == TUiLkZTSqT){UPmNVzUAqi = true;}
      else if(TUiLkZTSqT == SIrRVzSpQQ){WPuqFilekn = true;}
      if(bGHqakREhA == GgPtQGFamB){nNFPmGfmka = true;}
      if(tAVXCzHoIo == XiUDXQzPcZ){egKdsgUEjY = true;}
      if(EQtiDUTqfY == JABuAkCLUO){VbMCCQeJgg = true;}
      while(GgPtQGFamB == bGHqakREhA){OUGzXRZNzj = true;}
      while(XiUDXQzPcZ == XiUDXQzPcZ){SmqyJFgNBO = true;}
      while(JABuAkCLUO == JABuAkCLUO){siWmyAQywi = true;}
      if(pVljdAjgrZ == true){pVljdAjgrZ = false;}
      if(sZYCkkzemT == true){sZYCkkzemT = false;}
      if(ZDoRKGfUse == true){ZDoRKGfUse = false;}
      if(EsFYLBwkZW == true){EsFYLBwkZW = false;}
      if(gSXCfiazJP == true){gSXCfiazJP = false;}
      if(lWYBnlfTYW == true){lWYBnlfTYW = false;}
      if(UPmNVzUAqi == true){UPmNVzUAqi = false;}
      if(nNFPmGfmka == true){nNFPmGfmka = false;}
      if(egKdsgUEjY == true){egKdsgUEjY = false;}
      if(VbMCCQeJgg == true){VbMCCQeJgg = false;}
      if(OaIaaXRINg == true){OaIaaXRINg = false;}
      if(FsixrnEJTn == true){FsixrnEJTn = false;}
      if(dQPRNLBCNV == true){dQPRNLBCNV = false;}
      if(bWGEMEYjCU == true){bWGEMEYjCU = false;}
      if(PMpCScsOKO == true){PMpCScsOKO = false;}
      if(MVorCyKpNO == true){MVorCyKpNO = false;}
      if(WPuqFilekn == true){WPuqFilekn = false;}
      if(OUGzXRZNzj == true){OUGzXRZNzj = false;}
      if(SmqyJFgNBO == true){SmqyJFgNBO = false;}
      if(siWmyAQywi == true){siWmyAQywi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRYBFIIQNW
{ 
  void BreOuyAZQH()
  { 
      bool zQWLYjCWKF = false;
      bool PHrlFAylnE = false;
      bool LplREgHHVN = false;
      bool hIVFQyFuGp = false;
      bool TuCbdGBkyw = false;
      bool FPiktJeEHr = false;
      bool buAwWHklUG = false;
      bool uDfyjPnJmy = false;
      bool eWIZHRYjKH = false;
      bool SAmNOYuFEW = false;
      bool UPQqBCjkBd = false;
      bool UUQJNElaoF = false;
      bool hBbMntQRjL = false;
      bool UhEQcPGQXF = false;
      bool hnifmyicAJ = false;
      bool lTQznTmEDG = false;
      bool lRAoJlPAfy = false;
      bool yUCiXtRuYo = false;
      bool KmRaYBRFcJ = false;
      bool bCNRTPmsWA = false;
      string WTFnNskYSk;
      string xIhaAVxVyZ;
      string OpereiVjtH;
      string GVAaFjqxHt;
      string SdwjWXEWmz;
      string pFCKxgnNJd;
      string WAeLdaIHVQ;
      string dzODGjsuUG;
      string eywtQBTpdY;
      string wdmcXSzkFw;
      string PxBWVpqyDM;
      string msrDzXDjtc;
      string GScxTAMkfn;
      string kIoXqgxZYa;
      string KVlQkDkidz;
      string OOpcpwTDCU;
      string dFSOadDTMR;
      string ZdLTSkfLLQ;
      string PcGfZWSMht;
      string NsWExECXpG;
      if(WTFnNskYSk == PxBWVpqyDM){zQWLYjCWKF = true;}
      else if(PxBWVpqyDM == WTFnNskYSk){UPQqBCjkBd = true;}
      if(xIhaAVxVyZ == msrDzXDjtc){PHrlFAylnE = true;}
      else if(msrDzXDjtc == xIhaAVxVyZ){UUQJNElaoF = true;}
      if(OpereiVjtH == GScxTAMkfn){LplREgHHVN = true;}
      else if(GScxTAMkfn == OpereiVjtH){hBbMntQRjL = true;}
      if(GVAaFjqxHt == kIoXqgxZYa){hIVFQyFuGp = true;}
      else if(kIoXqgxZYa == GVAaFjqxHt){UhEQcPGQXF = true;}
      if(SdwjWXEWmz == KVlQkDkidz){TuCbdGBkyw = true;}
      else if(KVlQkDkidz == SdwjWXEWmz){hnifmyicAJ = true;}
      if(pFCKxgnNJd == OOpcpwTDCU){FPiktJeEHr = true;}
      else if(OOpcpwTDCU == pFCKxgnNJd){lTQznTmEDG = true;}
      if(WAeLdaIHVQ == dFSOadDTMR){buAwWHklUG = true;}
      else if(dFSOadDTMR == WAeLdaIHVQ){lRAoJlPAfy = true;}
      if(dzODGjsuUG == ZdLTSkfLLQ){uDfyjPnJmy = true;}
      if(eywtQBTpdY == PcGfZWSMht){eWIZHRYjKH = true;}
      if(wdmcXSzkFw == NsWExECXpG){SAmNOYuFEW = true;}
      while(ZdLTSkfLLQ == dzODGjsuUG){yUCiXtRuYo = true;}
      while(PcGfZWSMht == PcGfZWSMht){KmRaYBRFcJ = true;}
      while(NsWExECXpG == NsWExECXpG){bCNRTPmsWA = true;}
      if(zQWLYjCWKF == true){zQWLYjCWKF = false;}
      if(PHrlFAylnE == true){PHrlFAylnE = false;}
      if(LplREgHHVN == true){LplREgHHVN = false;}
      if(hIVFQyFuGp == true){hIVFQyFuGp = false;}
      if(TuCbdGBkyw == true){TuCbdGBkyw = false;}
      if(FPiktJeEHr == true){FPiktJeEHr = false;}
      if(buAwWHklUG == true){buAwWHklUG = false;}
      if(uDfyjPnJmy == true){uDfyjPnJmy = false;}
      if(eWIZHRYjKH == true){eWIZHRYjKH = false;}
      if(SAmNOYuFEW == true){SAmNOYuFEW = false;}
      if(UPQqBCjkBd == true){UPQqBCjkBd = false;}
      if(UUQJNElaoF == true){UUQJNElaoF = false;}
      if(hBbMntQRjL == true){hBbMntQRjL = false;}
      if(UhEQcPGQXF == true){UhEQcPGQXF = false;}
      if(hnifmyicAJ == true){hnifmyicAJ = false;}
      if(lTQznTmEDG == true){lTQznTmEDG = false;}
      if(lRAoJlPAfy == true){lRAoJlPAfy = false;}
      if(yUCiXtRuYo == true){yUCiXtRuYo = false;}
      if(KmRaYBRFcJ == true){KmRaYBRFcJ = false;}
      if(bCNRTPmsWA == true){bCNRTPmsWA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSCFMOPXDN
{ 
  void VxaSqWuMzB()
  { 
      bool yYlpczphcx = false;
      bool CdwbbuhJQp = false;
      bool beKtDpbETx = false;
      bool XWOqFLTKcA = false;
      bool bIEFfdIbeS = false;
      bool iTyejTNqml = false;
      bool XkNeYfOFWQ = false;
      bool bWfPNSZFOY = false;
      bool gzYBOEXiGl = false;
      bool xbXqcptZfA = false;
      bool ODFOqLmiQQ = false;
      bool sIcNEYMMPU = false;
      bool HfykSzzomX = false;
      bool XAZOJdtKKC = false;
      bool RoRprozJlD = false;
      bool dhJKriFTuq = false;
      bool MyusrrhNEa = false;
      bool eBCNDRNHrc = false;
      bool zoDitpqOVZ = false;
      bool YZOSpSsYyA = false;
      string bBdZYAlsrN;
      string XIGtYepBSa;
      string WclVpsLnJD;
      string MnIlEMICOO;
      string uSFHbIuXHF;
      string NYAcfyPIje;
      string nxjoBizToL;
      string WnmEeDXdsh;
      string xmfDpmneGG;
      string wARiZxiPFr;
      string JbhuiYluyc;
      string akOCgARgzO;
      string tTNiOVVDeg;
      string UHYAYVFkUQ;
      string AsgdeLlPBY;
      string fCQqyoNzfM;
      string CiPRISMNdL;
      string ufLhOBljDD;
      string jGBGARqgCi;
      string HFEHOQcPVM;
      if(bBdZYAlsrN == JbhuiYluyc){yYlpczphcx = true;}
      else if(JbhuiYluyc == bBdZYAlsrN){ODFOqLmiQQ = true;}
      if(XIGtYepBSa == akOCgARgzO){CdwbbuhJQp = true;}
      else if(akOCgARgzO == XIGtYepBSa){sIcNEYMMPU = true;}
      if(WclVpsLnJD == tTNiOVVDeg){beKtDpbETx = true;}
      else if(tTNiOVVDeg == WclVpsLnJD){HfykSzzomX = true;}
      if(MnIlEMICOO == UHYAYVFkUQ){XWOqFLTKcA = true;}
      else if(UHYAYVFkUQ == MnIlEMICOO){XAZOJdtKKC = true;}
      if(uSFHbIuXHF == AsgdeLlPBY){bIEFfdIbeS = true;}
      else if(AsgdeLlPBY == uSFHbIuXHF){RoRprozJlD = true;}
      if(NYAcfyPIje == fCQqyoNzfM){iTyejTNqml = true;}
      else if(fCQqyoNzfM == NYAcfyPIje){dhJKriFTuq = true;}
      if(nxjoBizToL == CiPRISMNdL){XkNeYfOFWQ = true;}
      else if(CiPRISMNdL == nxjoBizToL){MyusrrhNEa = true;}
      if(WnmEeDXdsh == ufLhOBljDD){bWfPNSZFOY = true;}
      if(xmfDpmneGG == jGBGARqgCi){gzYBOEXiGl = true;}
      if(wARiZxiPFr == HFEHOQcPVM){xbXqcptZfA = true;}
      while(ufLhOBljDD == WnmEeDXdsh){eBCNDRNHrc = true;}
      while(jGBGARqgCi == jGBGARqgCi){zoDitpqOVZ = true;}
      while(HFEHOQcPVM == HFEHOQcPVM){YZOSpSsYyA = true;}
      if(yYlpczphcx == true){yYlpczphcx = false;}
      if(CdwbbuhJQp == true){CdwbbuhJQp = false;}
      if(beKtDpbETx == true){beKtDpbETx = false;}
      if(XWOqFLTKcA == true){XWOqFLTKcA = false;}
      if(bIEFfdIbeS == true){bIEFfdIbeS = false;}
      if(iTyejTNqml == true){iTyejTNqml = false;}
      if(XkNeYfOFWQ == true){XkNeYfOFWQ = false;}
      if(bWfPNSZFOY == true){bWfPNSZFOY = false;}
      if(gzYBOEXiGl == true){gzYBOEXiGl = false;}
      if(xbXqcptZfA == true){xbXqcptZfA = false;}
      if(ODFOqLmiQQ == true){ODFOqLmiQQ = false;}
      if(sIcNEYMMPU == true){sIcNEYMMPU = false;}
      if(HfykSzzomX == true){HfykSzzomX = false;}
      if(XAZOJdtKKC == true){XAZOJdtKKC = false;}
      if(RoRprozJlD == true){RoRprozJlD = false;}
      if(dhJKriFTuq == true){dhJKriFTuq = false;}
      if(MyusrrhNEa == true){MyusrrhNEa = false;}
      if(eBCNDRNHrc == true){eBCNDRNHrc = false;}
      if(zoDitpqOVZ == true){zoDitpqOVZ = false;}
      if(YZOSpSsYyA == true){YZOSpSsYyA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEFJCBRCTM
{ 
  void tszMrEzSsr()
  { 
      bool BrGLKoQkUy = false;
      bool iuLOHmheWP = false;
      bool awWEiGKhsZ = false;
      bool itsNPHkjdr = false;
      bool FdemszqHml = false;
      bool PPrwKFVBbE = false;
      bool dirtOnCyzz = false;
      bool CxAdKwQjKj = false;
      bool PCuGJTCwDJ = false;
      bool liHZNWljXF = false;
      bool wsImjSPNlN = false;
      bool nlprobmlku = false;
      bool kGtoNSoZPn = false;
      bool KfLFmVtHVp = false;
      bool EoKoVAsPkl = false;
      bool izzcTpySZR = false;
      bool doxxDIZkFS = false;
      bool gfQuquuFTM = false;
      bool ZZodEKghkx = false;
      bool XagDMOrMkM = false;
      string QjmAnigbar;
      string OzEKKpwobE;
      string GJNlKNGxmo;
      string DcwxuIVdoW;
      string rPMeFWLDxc;
      string bNjUuHVBoa;
      string bjoknkCGPB;
      string USzFMqwhgn;
      string BCzJNpsaCm;
      string lUnOtHZbpT;
      string TFnwHIOeID;
      string KnUBZYkeXy;
      string rbEbPAdkKE;
      string QTqMTwODCE;
      string aOSycyAmoU;
      string WtEqbrBLfH;
      string edTElqwHgd;
      string JhcSWdJFzR;
      string AquogWPzkb;
      string tDWtZxtOMk;
      if(QjmAnigbar == TFnwHIOeID){BrGLKoQkUy = true;}
      else if(TFnwHIOeID == QjmAnigbar){wsImjSPNlN = true;}
      if(OzEKKpwobE == KnUBZYkeXy){iuLOHmheWP = true;}
      else if(KnUBZYkeXy == OzEKKpwobE){nlprobmlku = true;}
      if(GJNlKNGxmo == rbEbPAdkKE){awWEiGKhsZ = true;}
      else if(rbEbPAdkKE == GJNlKNGxmo){kGtoNSoZPn = true;}
      if(DcwxuIVdoW == QTqMTwODCE){itsNPHkjdr = true;}
      else if(QTqMTwODCE == DcwxuIVdoW){KfLFmVtHVp = true;}
      if(rPMeFWLDxc == aOSycyAmoU){FdemszqHml = true;}
      else if(aOSycyAmoU == rPMeFWLDxc){EoKoVAsPkl = true;}
      if(bNjUuHVBoa == WtEqbrBLfH){PPrwKFVBbE = true;}
      else if(WtEqbrBLfH == bNjUuHVBoa){izzcTpySZR = true;}
      if(bjoknkCGPB == edTElqwHgd){dirtOnCyzz = true;}
      else if(edTElqwHgd == bjoknkCGPB){doxxDIZkFS = true;}
      if(USzFMqwhgn == JhcSWdJFzR){CxAdKwQjKj = true;}
      if(BCzJNpsaCm == AquogWPzkb){PCuGJTCwDJ = true;}
      if(lUnOtHZbpT == tDWtZxtOMk){liHZNWljXF = true;}
      while(JhcSWdJFzR == USzFMqwhgn){gfQuquuFTM = true;}
      while(AquogWPzkb == AquogWPzkb){ZZodEKghkx = true;}
      while(tDWtZxtOMk == tDWtZxtOMk){XagDMOrMkM = true;}
      if(BrGLKoQkUy == true){BrGLKoQkUy = false;}
      if(iuLOHmheWP == true){iuLOHmheWP = false;}
      if(awWEiGKhsZ == true){awWEiGKhsZ = false;}
      if(itsNPHkjdr == true){itsNPHkjdr = false;}
      if(FdemszqHml == true){FdemszqHml = false;}
      if(PPrwKFVBbE == true){PPrwKFVBbE = false;}
      if(dirtOnCyzz == true){dirtOnCyzz = false;}
      if(CxAdKwQjKj == true){CxAdKwQjKj = false;}
      if(PCuGJTCwDJ == true){PCuGJTCwDJ = false;}
      if(liHZNWljXF == true){liHZNWljXF = false;}
      if(wsImjSPNlN == true){wsImjSPNlN = false;}
      if(nlprobmlku == true){nlprobmlku = false;}
      if(kGtoNSoZPn == true){kGtoNSoZPn = false;}
      if(KfLFmVtHVp == true){KfLFmVtHVp = false;}
      if(EoKoVAsPkl == true){EoKoVAsPkl = false;}
      if(izzcTpySZR == true){izzcTpySZR = false;}
      if(doxxDIZkFS == true){doxxDIZkFS = false;}
      if(gfQuquuFTM == true){gfQuquuFTM = false;}
      if(ZZodEKghkx == true){ZZodEKghkx = false;}
      if(XagDMOrMkM == true){XagDMOrMkM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWHSGMCYSF
{ 
  void OmzOtBHWlB()
  { 
      bool omCJfrwxXY = false;
      bool goCGpHOZFu = false;
      bool rtDURBjhsS = false;
      bool jQdrXxOsIt = false;
      bool VMfdMDlyME = false;
      bool kkQegujhre = false;
      bool INDEoPKJir = false;
      bool sUQLZeNZIN = false;
      bool OkVngyAzLc = false;
      bool NfBdlHIanw = false;
      bool rbPTLQTFFB = false;
      bool gJZdPWrPWp = false;
      bool PLyFeMSmYR = false;
      bool WlkLVmUBbQ = false;
      bool etsJuEGWNP = false;
      bool PsExffcJoz = false;
      bool xgfnetXNIb = false;
      bool BqmGLURoKa = false;
      bool FwYJBchneo = false;
      bool KLLbSxOFdA = false;
      string BDySXcAoLZ;
      string PwLrWIuUMY;
      string ygoMyFMrod;
      string hyMQKrHQhi;
      string FyaTDJgsyF;
      string laBgNUNkTS;
      string QIAhrQiuhd;
      string AelcSzFVIo;
      string XTsjqGxeCo;
      string eVwOSxysbm;
      string ZlLTFHoXOO;
      string OrbduxOPpk;
      string TErrzdiWJU;
      string AMtVPlHZdj;
      string RYQnalsRTV;
      string hhCpTVsTTa;
      string XROsNBxGOJ;
      string oolFStnEQM;
      string kQDnmRJDCt;
      string rnFDMzKWZY;
      if(BDySXcAoLZ == ZlLTFHoXOO){omCJfrwxXY = true;}
      else if(ZlLTFHoXOO == BDySXcAoLZ){rbPTLQTFFB = true;}
      if(PwLrWIuUMY == OrbduxOPpk){goCGpHOZFu = true;}
      else if(OrbduxOPpk == PwLrWIuUMY){gJZdPWrPWp = true;}
      if(ygoMyFMrod == TErrzdiWJU){rtDURBjhsS = true;}
      else if(TErrzdiWJU == ygoMyFMrod){PLyFeMSmYR = true;}
      if(hyMQKrHQhi == AMtVPlHZdj){jQdrXxOsIt = true;}
      else if(AMtVPlHZdj == hyMQKrHQhi){WlkLVmUBbQ = true;}
      if(FyaTDJgsyF == RYQnalsRTV){VMfdMDlyME = true;}
      else if(RYQnalsRTV == FyaTDJgsyF){etsJuEGWNP = true;}
      if(laBgNUNkTS == hhCpTVsTTa){kkQegujhre = true;}
      else if(hhCpTVsTTa == laBgNUNkTS){PsExffcJoz = true;}
      if(QIAhrQiuhd == XROsNBxGOJ){INDEoPKJir = true;}
      else if(XROsNBxGOJ == QIAhrQiuhd){xgfnetXNIb = true;}
      if(AelcSzFVIo == oolFStnEQM){sUQLZeNZIN = true;}
      if(XTsjqGxeCo == kQDnmRJDCt){OkVngyAzLc = true;}
      if(eVwOSxysbm == rnFDMzKWZY){NfBdlHIanw = true;}
      while(oolFStnEQM == AelcSzFVIo){BqmGLURoKa = true;}
      while(kQDnmRJDCt == kQDnmRJDCt){FwYJBchneo = true;}
      while(rnFDMzKWZY == rnFDMzKWZY){KLLbSxOFdA = true;}
      if(omCJfrwxXY == true){omCJfrwxXY = false;}
      if(goCGpHOZFu == true){goCGpHOZFu = false;}
      if(rtDURBjhsS == true){rtDURBjhsS = false;}
      if(jQdrXxOsIt == true){jQdrXxOsIt = false;}
      if(VMfdMDlyME == true){VMfdMDlyME = false;}
      if(kkQegujhre == true){kkQegujhre = false;}
      if(INDEoPKJir == true){INDEoPKJir = false;}
      if(sUQLZeNZIN == true){sUQLZeNZIN = false;}
      if(OkVngyAzLc == true){OkVngyAzLc = false;}
      if(NfBdlHIanw == true){NfBdlHIanw = false;}
      if(rbPTLQTFFB == true){rbPTLQTFFB = false;}
      if(gJZdPWrPWp == true){gJZdPWrPWp = false;}
      if(PLyFeMSmYR == true){PLyFeMSmYR = false;}
      if(WlkLVmUBbQ == true){WlkLVmUBbQ = false;}
      if(etsJuEGWNP == true){etsJuEGWNP = false;}
      if(PsExffcJoz == true){PsExffcJoz = false;}
      if(xgfnetXNIb == true){xgfnetXNIb = false;}
      if(BqmGLURoKa == true){BqmGLURoKa = false;}
      if(FwYJBchneo == true){FwYJBchneo = false;}
      if(KLLbSxOFdA == true){KLLbSxOFdA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENPQPRLUDU
{ 
  void QgrSaHTOcz()
  { 
      bool KNxYtlRmjx = false;
      bool KYtafVhwzC = false;
      bool EFwcjGlpBI = false;
      bool GKOIrqriHr = false;
      bool qXNpkZpnWT = false;
      bool EEHUoERUon = false;
      bool AbkbqAKkho = false;
      bool czoGKgrFrK = false;
      bool PyShDCCsTn = false;
      bool ZXsTrPllzj = false;
      bool OEFhpEOBKH = false;
      bool MLbeXCIDXo = false;
      bool yQRtOFFUOt = false;
      bool uFGIuKrjqz = false;
      bool mBiLaOuOup = false;
      bool HiOJkylLTk = false;
      bool ytmPMGETjN = false;
      bool JXLYBxgFSA = false;
      bool JqZXmMqwWw = false;
      bool XfQGAsOSzT = false;
      string DPoWoliErV;
      string KMnxZmDDUP;
      string OqzHUFXztc;
      string LTbFXMIWkX;
      string QCiPCPOgJR;
      string EZhuqLQhCi;
      string OiJOKqjiYN;
      string dgSwzMIiEE;
      string ppobXkkgNM;
      string waUBJgrTFL;
      string ffIwnXHlwe;
      string DgcxsXtgqY;
      string GCULRCMQmR;
      string TndsYKgsnA;
      string dzkiJOxWIk;
      string mKcfEcLwdk;
      string LqydLPDjYi;
      string qAspuHRlCD;
      string EpIBeJKynw;
      string zjODomAHWt;
      if(DPoWoliErV == ffIwnXHlwe){KNxYtlRmjx = true;}
      else if(ffIwnXHlwe == DPoWoliErV){OEFhpEOBKH = true;}
      if(KMnxZmDDUP == DgcxsXtgqY){KYtafVhwzC = true;}
      else if(DgcxsXtgqY == KMnxZmDDUP){MLbeXCIDXo = true;}
      if(OqzHUFXztc == GCULRCMQmR){EFwcjGlpBI = true;}
      else if(GCULRCMQmR == OqzHUFXztc){yQRtOFFUOt = true;}
      if(LTbFXMIWkX == TndsYKgsnA){GKOIrqriHr = true;}
      else if(TndsYKgsnA == LTbFXMIWkX){uFGIuKrjqz = true;}
      if(QCiPCPOgJR == dzkiJOxWIk){qXNpkZpnWT = true;}
      else if(dzkiJOxWIk == QCiPCPOgJR){mBiLaOuOup = true;}
      if(EZhuqLQhCi == mKcfEcLwdk){EEHUoERUon = true;}
      else if(mKcfEcLwdk == EZhuqLQhCi){HiOJkylLTk = true;}
      if(OiJOKqjiYN == LqydLPDjYi){AbkbqAKkho = true;}
      else if(LqydLPDjYi == OiJOKqjiYN){ytmPMGETjN = true;}
      if(dgSwzMIiEE == qAspuHRlCD){czoGKgrFrK = true;}
      if(ppobXkkgNM == EpIBeJKynw){PyShDCCsTn = true;}
      if(waUBJgrTFL == zjODomAHWt){ZXsTrPllzj = true;}
      while(qAspuHRlCD == dgSwzMIiEE){JXLYBxgFSA = true;}
      while(EpIBeJKynw == EpIBeJKynw){JqZXmMqwWw = true;}
      while(zjODomAHWt == zjODomAHWt){XfQGAsOSzT = true;}
      if(KNxYtlRmjx == true){KNxYtlRmjx = false;}
      if(KYtafVhwzC == true){KYtafVhwzC = false;}
      if(EFwcjGlpBI == true){EFwcjGlpBI = false;}
      if(GKOIrqriHr == true){GKOIrqriHr = false;}
      if(qXNpkZpnWT == true){qXNpkZpnWT = false;}
      if(EEHUoERUon == true){EEHUoERUon = false;}
      if(AbkbqAKkho == true){AbkbqAKkho = false;}
      if(czoGKgrFrK == true){czoGKgrFrK = false;}
      if(PyShDCCsTn == true){PyShDCCsTn = false;}
      if(ZXsTrPllzj == true){ZXsTrPllzj = false;}
      if(OEFhpEOBKH == true){OEFhpEOBKH = false;}
      if(MLbeXCIDXo == true){MLbeXCIDXo = false;}
      if(yQRtOFFUOt == true){yQRtOFFUOt = false;}
      if(uFGIuKrjqz == true){uFGIuKrjqz = false;}
      if(mBiLaOuOup == true){mBiLaOuOup = false;}
      if(HiOJkylLTk == true){HiOJkylLTk = false;}
      if(ytmPMGETjN == true){ytmPMGETjN = false;}
      if(JXLYBxgFSA == true){JXLYBxgFSA = false;}
      if(JqZXmMqwWw == true){JqZXmMqwWw = false;}
      if(XfQGAsOSzT == true){XfQGAsOSzT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFWAAQEKEV
{ 
  void CJIIrtekUC()
  { 
      bool wIRDXhShad = false;
      bool ZJtccQSNoL = false;
      bool wELrXKEPmk = false;
      bool mzDcfjGTNA = false;
      bool AMlXtbSGmy = false;
      bool NBRgHrxYfM = false;
      bool dCtppZGQws = false;
      bool JzAnLiSnyu = false;
      bool ryboXlhVVn = false;
      bool lhnAWySwgT = false;
      bool VBJsnNAcVX = false;
      bool ZJajUeZFSE = false;
      bool qjuHHbLARM = false;
      bool QVGdYpniAJ = false;
      bool kFAyOcHDeq = false;
      bool YMccblGBlM = false;
      bool BAKJGDCwKd = false;
      bool qqEITlixsd = false;
      bool UHUZnDrdBm = false;
      bool jmwmHktpqL = false;
      string NbPFbyjdgX;
      string nfBHgRKCKT;
      string wSNqbxqRle;
      string hYmGMBnSxR;
      string QKuYMKYydO;
      string igbejuNYcd;
      string GRqCoOsttf;
      string dqEsDlXoeR;
      string YsnXuAxHWR;
      string mPoSKzSrix;
      string ReDyjqbhby;
      string WYsLENcTHo;
      string RkWbrOBlhE;
      string SfGgztoomE;
      string XOeYuOVdOx;
      string VzksffHbGV;
      string opzXeqRMMK;
      string YmgCRCGxgc;
      string rXWkhStNBT;
      string lNiQPgPGsD;
      if(NbPFbyjdgX == ReDyjqbhby){wIRDXhShad = true;}
      else if(ReDyjqbhby == NbPFbyjdgX){VBJsnNAcVX = true;}
      if(nfBHgRKCKT == WYsLENcTHo){ZJtccQSNoL = true;}
      else if(WYsLENcTHo == nfBHgRKCKT){ZJajUeZFSE = true;}
      if(wSNqbxqRle == RkWbrOBlhE){wELrXKEPmk = true;}
      else if(RkWbrOBlhE == wSNqbxqRle){qjuHHbLARM = true;}
      if(hYmGMBnSxR == SfGgztoomE){mzDcfjGTNA = true;}
      else if(SfGgztoomE == hYmGMBnSxR){QVGdYpniAJ = true;}
      if(QKuYMKYydO == XOeYuOVdOx){AMlXtbSGmy = true;}
      else if(XOeYuOVdOx == QKuYMKYydO){kFAyOcHDeq = true;}
      if(igbejuNYcd == VzksffHbGV){NBRgHrxYfM = true;}
      else if(VzksffHbGV == igbejuNYcd){YMccblGBlM = true;}
      if(GRqCoOsttf == opzXeqRMMK){dCtppZGQws = true;}
      else if(opzXeqRMMK == GRqCoOsttf){BAKJGDCwKd = true;}
      if(dqEsDlXoeR == YmgCRCGxgc){JzAnLiSnyu = true;}
      if(YsnXuAxHWR == rXWkhStNBT){ryboXlhVVn = true;}
      if(mPoSKzSrix == lNiQPgPGsD){lhnAWySwgT = true;}
      while(YmgCRCGxgc == dqEsDlXoeR){qqEITlixsd = true;}
      while(rXWkhStNBT == rXWkhStNBT){UHUZnDrdBm = true;}
      while(lNiQPgPGsD == lNiQPgPGsD){jmwmHktpqL = true;}
      if(wIRDXhShad == true){wIRDXhShad = false;}
      if(ZJtccQSNoL == true){ZJtccQSNoL = false;}
      if(wELrXKEPmk == true){wELrXKEPmk = false;}
      if(mzDcfjGTNA == true){mzDcfjGTNA = false;}
      if(AMlXtbSGmy == true){AMlXtbSGmy = false;}
      if(NBRgHrxYfM == true){NBRgHrxYfM = false;}
      if(dCtppZGQws == true){dCtppZGQws = false;}
      if(JzAnLiSnyu == true){JzAnLiSnyu = false;}
      if(ryboXlhVVn == true){ryboXlhVVn = false;}
      if(lhnAWySwgT == true){lhnAWySwgT = false;}
      if(VBJsnNAcVX == true){VBJsnNAcVX = false;}
      if(ZJajUeZFSE == true){ZJajUeZFSE = false;}
      if(qjuHHbLARM == true){qjuHHbLARM = false;}
      if(QVGdYpniAJ == true){QVGdYpniAJ = false;}
      if(kFAyOcHDeq == true){kFAyOcHDeq = false;}
      if(YMccblGBlM == true){YMccblGBlM = false;}
      if(BAKJGDCwKd == true){BAKJGDCwKd = false;}
      if(qqEITlixsd == true){qqEITlixsd = false;}
      if(UHUZnDrdBm == true){UHUZnDrdBm = false;}
      if(jmwmHktpqL == true){jmwmHktpqL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDNKCSZUDH
{ 
  void YOdbLLtSWZ()
  { 
      bool DqdAgfFUDL = false;
      bool XBMwAPbEiC = false;
      bool wFjMXCJyNr = false;
      bool fBgXwiLPwI = false;
      bool QScMDkVEex = false;
      bool YPBwVyGQce = false;
      bool WHHKfVToAR = false;
      bool EMHZldcXJl = false;
      bool fFSPTPAkBy = false;
      bool btmRlIKRfg = false;
      bool QfEMsMHaKq = false;
      bool UhHpyQoqqQ = false;
      bool VimBoJYpnc = false;
      bool SKqbUAAFWG = false;
      bool HZZKctlwSU = false;
      bool TTaPKhrCXi = false;
      bool nRlgYKqeVy = false;
      bool QiUkIwIcYu = false;
      bool XbWSJzjaRm = false;
      bool HxhmSpmskR = false;
      string UryFdwUUxB;
      string lINcsLpqge;
      string mcICwtqYcd;
      string zAAINspwZt;
      string wMGpCJoKmV;
      string DkRmGqjuIj;
      string EuqSClHEOz;
      string UsQlhaWSAl;
      string EglGaNhNCW;
      string IumppBUmmP;
      string CjumAJTeFe;
      string TRtWeWJjqn;
      string DsCrqZFawg;
      string GiekiUlyGQ;
      string tDIWCpAQKS;
      string qjuyMIgCwa;
      string EriXYjmJmK;
      string kLdatAkfoA;
      string ZoPdoVngYa;
      string miBfMBUjyR;
      if(UryFdwUUxB == CjumAJTeFe){DqdAgfFUDL = true;}
      else if(CjumAJTeFe == UryFdwUUxB){QfEMsMHaKq = true;}
      if(lINcsLpqge == TRtWeWJjqn){XBMwAPbEiC = true;}
      else if(TRtWeWJjqn == lINcsLpqge){UhHpyQoqqQ = true;}
      if(mcICwtqYcd == DsCrqZFawg){wFjMXCJyNr = true;}
      else if(DsCrqZFawg == mcICwtqYcd){VimBoJYpnc = true;}
      if(zAAINspwZt == GiekiUlyGQ){fBgXwiLPwI = true;}
      else if(GiekiUlyGQ == zAAINspwZt){SKqbUAAFWG = true;}
      if(wMGpCJoKmV == tDIWCpAQKS){QScMDkVEex = true;}
      else if(tDIWCpAQKS == wMGpCJoKmV){HZZKctlwSU = true;}
      if(DkRmGqjuIj == qjuyMIgCwa){YPBwVyGQce = true;}
      else if(qjuyMIgCwa == DkRmGqjuIj){TTaPKhrCXi = true;}
      if(EuqSClHEOz == EriXYjmJmK){WHHKfVToAR = true;}
      else if(EriXYjmJmK == EuqSClHEOz){nRlgYKqeVy = true;}
      if(UsQlhaWSAl == kLdatAkfoA){EMHZldcXJl = true;}
      if(EglGaNhNCW == ZoPdoVngYa){fFSPTPAkBy = true;}
      if(IumppBUmmP == miBfMBUjyR){btmRlIKRfg = true;}
      while(kLdatAkfoA == UsQlhaWSAl){QiUkIwIcYu = true;}
      while(ZoPdoVngYa == ZoPdoVngYa){XbWSJzjaRm = true;}
      while(miBfMBUjyR == miBfMBUjyR){HxhmSpmskR = true;}
      if(DqdAgfFUDL == true){DqdAgfFUDL = false;}
      if(XBMwAPbEiC == true){XBMwAPbEiC = false;}
      if(wFjMXCJyNr == true){wFjMXCJyNr = false;}
      if(fBgXwiLPwI == true){fBgXwiLPwI = false;}
      if(QScMDkVEex == true){QScMDkVEex = false;}
      if(YPBwVyGQce == true){YPBwVyGQce = false;}
      if(WHHKfVToAR == true){WHHKfVToAR = false;}
      if(EMHZldcXJl == true){EMHZldcXJl = false;}
      if(fFSPTPAkBy == true){fFSPTPAkBy = false;}
      if(btmRlIKRfg == true){btmRlIKRfg = false;}
      if(QfEMsMHaKq == true){QfEMsMHaKq = false;}
      if(UhHpyQoqqQ == true){UhHpyQoqqQ = false;}
      if(VimBoJYpnc == true){VimBoJYpnc = false;}
      if(SKqbUAAFWG == true){SKqbUAAFWG = false;}
      if(HZZKctlwSU == true){HZZKctlwSU = false;}
      if(TTaPKhrCXi == true){TTaPKhrCXi = false;}
      if(nRlgYKqeVy == true){nRlgYKqeVy = false;}
      if(QiUkIwIcYu == true){QiUkIwIcYu = false;}
      if(XbWSJzjaRm == true){XbWSJzjaRm = false;}
      if(HxhmSpmskR == true){HxhmSpmskR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTLXGFXMNU
{ 
  void YInlFzNBiV()
  { 
      bool mLVgLprntT = false;
      bool GamtLZGVjy = false;
      bool rouYwhpGeu = false;
      bool jzriYFcNGK = false;
      bool bPgPuoTKUU = false;
      bool XnPcgxPwkd = false;
      bool AlJyiGiDUG = false;
      bool xrOZWbHfdH = false;
      bool NfkJXuiOBb = false;
      bool ogccKpGifn = false;
      bool FPoNWeZpGE = false;
      bool pjRcPTAzam = false;
      bool WTBsQPPlPf = false;
      bool VYzoBypWmr = false;
      bool VsHwlFOzMp = false;
      bool oHHrRlNuxH = false;
      bool PmaaiQjbbR = false;
      bool dcLiRcMFHL = false;
      bool BPZYqNQGXP = false;
      bool jtZfbhSgMU = false;
      string CGrUKAksOp;
      string UNtskYiNWT;
      string qOXKnQcrDf;
      string PVQMZBzKJN;
      string lPoBGntwHK;
      string rtPGuniggs;
      string WrohazwhSi;
      string ZXEJgaYVEz;
      string WfjsnVFKQl;
      string RScPptaHZH;
      string rLcXjToGYU;
      string ONbhWqHutF;
      string slQgQHtnSm;
      string ARwxHKCMIT;
      string fylwWEpusz;
      string leNTNGuwHc;
      string YBnkTxReZL;
      string nulZZtATJM;
      string QyuSBUEbiB;
      string PGEfudKAbZ;
      if(CGrUKAksOp == rLcXjToGYU){mLVgLprntT = true;}
      else if(rLcXjToGYU == CGrUKAksOp){FPoNWeZpGE = true;}
      if(UNtskYiNWT == ONbhWqHutF){GamtLZGVjy = true;}
      else if(ONbhWqHutF == UNtskYiNWT){pjRcPTAzam = true;}
      if(qOXKnQcrDf == slQgQHtnSm){rouYwhpGeu = true;}
      else if(slQgQHtnSm == qOXKnQcrDf){WTBsQPPlPf = true;}
      if(PVQMZBzKJN == ARwxHKCMIT){jzriYFcNGK = true;}
      else if(ARwxHKCMIT == PVQMZBzKJN){VYzoBypWmr = true;}
      if(lPoBGntwHK == fylwWEpusz){bPgPuoTKUU = true;}
      else if(fylwWEpusz == lPoBGntwHK){VsHwlFOzMp = true;}
      if(rtPGuniggs == leNTNGuwHc){XnPcgxPwkd = true;}
      else if(leNTNGuwHc == rtPGuniggs){oHHrRlNuxH = true;}
      if(WrohazwhSi == YBnkTxReZL){AlJyiGiDUG = true;}
      else if(YBnkTxReZL == WrohazwhSi){PmaaiQjbbR = true;}
      if(ZXEJgaYVEz == nulZZtATJM){xrOZWbHfdH = true;}
      if(WfjsnVFKQl == QyuSBUEbiB){NfkJXuiOBb = true;}
      if(RScPptaHZH == PGEfudKAbZ){ogccKpGifn = true;}
      while(nulZZtATJM == ZXEJgaYVEz){dcLiRcMFHL = true;}
      while(QyuSBUEbiB == QyuSBUEbiB){BPZYqNQGXP = true;}
      while(PGEfudKAbZ == PGEfudKAbZ){jtZfbhSgMU = true;}
      if(mLVgLprntT == true){mLVgLprntT = false;}
      if(GamtLZGVjy == true){GamtLZGVjy = false;}
      if(rouYwhpGeu == true){rouYwhpGeu = false;}
      if(jzriYFcNGK == true){jzriYFcNGK = false;}
      if(bPgPuoTKUU == true){bPgPuoTKUU = false;}
      if(XnPcgxPwkd == true){XnPcgxPwkd = false;}
      if(AlJyiGiDUG == true){AlJyiGiDUG = false;}
      if(xrOZWbHfdH == true){xrOZWbHfdH = false;}
      if(NfkJXuiOBb == true){NfkJXuiOBb = false;}
      if(ogccKpGifn == true){ogccKpGifn = false;}
      if(FPoNWeZpGE == true){FPoNWeZpGE = false;}
      if(pjRcPTAzam == true){pjRcPTAzam = false;}
      if(WTBsQPPlPf == true){WTBsQPPlPf = false;}
      if(VYzoBypWmr == true){VYzoBypWmr = false;}
      if(VsHwlFOzMp == true){VsHwlFOzMp = false;}
      if(oHHrRlNuxH == true){oHHrRlNuxH = false;}
      if(PmaaiQjbbR == true){PmaaiQjbbR = false;}
      if(dcLiRcMFHL == true){dcLiRcMFHL = false;}
      if(BPZYqNQGXP == true){BPZYqNQGXP = false;}
      if(jtZfbhSgMU == true){jtZfbhSgMU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMPLELVXOZ
{ 
  void iJseIZVlqc()
  { 
      bool InaGMUbnwt = false;
      bool EwOAzHdJJW = false;
      bool IpDIuTqqJl = false;
      bool fVepGtsqmo = false;
      bool qyOWStcEXC = false;
      bool IEBhUSkSLs = false;
      bool djdKNhRXtF = false;
      bool OlVTfJagoA = false;
      bool pmSGcbUxUm = false;
      bool IZetLGUDIj = false;
      bool cFJSnVigBK = false;
      bool qEcLDpRXhl = false;
      bool MTCGwnHbHZ = false;
      bool oXXFXkcASG = false;
      bool snuJwExTpV = false;
      bool owVVXICDWz = false;
      bool OGYbVTfXmS = false;
      bool MREarYYsJq = false;
      bool qnkljrBChP = false;
      bool iZcSrlPSnc = false;
      string RfglbYmeNO;
      string ARqUbBKygN;
      string aTMsqdkNgP;
      string uadOMLYoCx;
      string FHLZfkpiFC;
      string YOSDSyTnty;
      string mYxxSZmbHQ;
      string cVuiHSIlMG;
      string mBIdpgHauO;
      string qjtEKgJNGG;
      string xNbnZDSiuz;
      string oganKkPTGl;
      string RMgsYraqYa;
      string JtfFIYZTEm;
      string NXewYKJGsY;
      string QpHUnkghPg;
      string bbKUpuBUel;
      string LuOTXtgjTO;
      string hUyAKSmLRW;
      string qrEWKlNKFd;
      if(RfglbYmeNO == xNbnZDSiuz){InaGMUbnwt = true;}
      else if(xNbnZDSiuz == RfglbYmeNO){cFJSnVigBK = true;}
      if(ARqUbBKygN == oganKkPTGl){EwOAzHdJJW = true;}
      else if(oganKkPTGl == ARqUbBKygN){qEcLDpRXhl = true;}
      if(aTMsqdkNgP == RMgsYraqYa){IpDIuTqqJl = true;}
      else if(RMgsYraqYa == aTMsqdkNgP){MTCGwnHbHZ = true;}
      if(uadOMLYoCx == JtfFIYZTEm){fVepGtsqmo = true;}
      else if(JtfFIYZTEm == uadOMLYoCx){oXXFXkcASG = true;}
      if(FHLZfkpiFC == NXewYKJGsY){qyOWStcEXC = true;}
      else if(NXewYKJGsY == FHLZfkpiFC){snuJwExTpV = true;}
      if(YOSDSyTnty == QpHUnkghPg){IEBhUSkSLs = true;}
      else if(QpHUnkghPg == YOSDSyTnty){owVVXICDWz = true;}
      if(mYxxSZmbHQ == bbKUpuBUel){djdKNhRXtF = true;}
      else if(bbKUpuBUel == mYxxSZmbHQ){OGYbVTfXmS = true;}
      if(cVuiHSIlMG == LuOTXtgjTO){OlVTfJagoA = true;}
      if(mBIdpgHauO == hUyAKSmLRW){pmSGcbUxUm = true;}
      if(qjtEKgJNGG == qrEWKlNKFd){IZetLGUDIj = true;}
      while(LuOTXtgjTO == cVuiHSIlMG){MREarYYsJq = true;}
      while(hUyAKSmLRW == hUyAKSmLRW){qnkljrBChP = true;}
      while(qrEWKlNKFd == qrEWKlNKFd){iZcSrlPSnc = true;}
      if(InaGMUbnwt == true){InaGMUbnwt = false;}
      if(EwOAzHdJJW == true){EwOAzHdJJW = false;}
      if(IpDIuTqqJl == true){IpDIuTqqJl = false;}
      if(fVepGtsqmo == true){fVepGtsqmo = false;}
      if(qyOWStcEXC == true){qyOWStcEXC = false;}
      if(IEBhUSkSLs == true){IEBhUSkSLs = false;}
      if(djdKNhRXtF == true){djdKNhRXtF = false;}
      if(OlVTfJagoA == true){OlVTfJagoA = false;}
      if(pmSGcbUxUm == true){pmSGcbUxUm = false;}
      if(IZetLGUDIj == true){IZetLGUDIj = false;}
      if(cFJSnVigBK == true){cFJSnVigBK = false;}
      if(qEcLDpRXhl == true){qEcLDpRXhl = false;}
      if(MTCGwnHbHZ == true){MTCGwnHbHZ = false;}
      if(oXXFXkcASG == true){oXXFXkcASG = false;}
      if(snuJwExTpV == true){snuJwExTpV = false;}
      if(owVVXICDWz == true){owVVXICDWz = false;}
      if(OGYbVTfXmS == true){OGYbVTfXmS = false;}
      if(MREarYYsJq == true){MREarYYsJq = false;}
      if(qnkljrBChP == true){qnkljrBChP = false;}
      if(iZcSrlPSnc == true){iZcSrlPSnc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOIREPRHDV
{ 
  void lVsfkRJBrV()
  { 
      bool kXCyTzNLrg = false;
      bool ZugtRuqbkW = false;
      bool nXEdpACDcK = false;
      bool RcgGEJsMcl = false;
      bool VmItgbqiuK = false;
      bool okILeMTYIS = false;
      bool wJigOxOZoI = false;
      bool CeyzABPJwO = false;
      bool JTISVfUVbr = false;
      bool oUEKoLDaej = false;
      bool NRtlHJlIKc = false;
      bool xJbtJcBPLi = false;
      bool brxxShanJo = false;
      bool xneMBqZVKL = false;
      bool sLKztfrJAM = false;
      bool KnPwHUUwSZ = false;
      bool ixzVfJdPsR = false;
      bool DeEAoQhyCm = false;
      bool oQnxdJXiEf = false;
      bool WcCjcwMnTk = false;
      string KHRpmswGOG;
      string fWVMDSNrDF;
      string CFxbNmYFiJ;
      string THfErfMDKQ;
      string PfhzFZjGHn;
      string kICcrEJobA;
      string UqXFmYpRTW;
      string GKhloWWyVm;
      string CRxtXKEDLm;
      string WWaJwYHcMg;
      string jSmjhaaQmV;
      string gLTnxDscgb;
      string TmGfAiiXpQ;
      string OtlnDjeMLx;
      string jnPoGKCmMr;
      string eeujMwMGjy;
      string qDZWGmZejN;
      string YfQirfWQZo;
      string guLxkjyBaG;
      string XXcNGgNsiS;
      if(KHRpmswGOG == jSmjhaaQmV){kXCyTzNLrg = true;}
      else if(jSmjhaaQmV == KHRpmswGOG){NRtlHJlIKc = true;}
      if(fWVMDSNrDF == gLTnxDscgb){ZugtRuqbkW = true;}
      else if(gLTnxDscgb == fWVMDSNrDF){xJbtJcBPLi = true;}
      if(CFxbNmYFiJ == TmGfAiiXpQ){nXEdpACDcK = true;}
      else if(TmGfAiiXpQ == CFxbNmYFiJ){brxxShanJo = true;}
      if(THfErfMDKQ == OtlnDjeMLx){RcgGEJsMcl = true;}
      else if(OtlnDjeMLx == THfErfMDKQ){xneMBqZVKL = true;}
      if(PfhzFZjGHn == jnPoGKCmMr){VmItgbqiuK = true;}
      else if(jnPoGKCmMr == PfhzFZjGHn){sLKztfrJAM = true;}
      if(kICcrEJobA == eeujMwMGjy){okILeMTYIS = true;}
      else if(eeujMwMGjy == kICcrEJobA){KnPwHUUwSZ = true;}
      if(UqXFmYpRTW == qDZWGmZejN){wJigOxOZoI = true;}
      else if(qDZWGmZejN == UqXFmYpRTW){ixzVfJdPsR = true;}
      if(GKhloWWyVm == YfQirfWQZo){CeyzABPJwO = true;}
      if(CRxtXKEDLm == guLxkjyBaG){JTISVfUVbr = true;}
      if(WWaJwYHcMg == XXcNGgNsiS){oUEKoLDaej = true;}
      while(YfQirfWQZo == GKhloWWyVm){DeEAoQhyCm = true;}
      while(guLxkjyBaG == guLxkjyBaG){oQnxdJXiEf = true;}
      while(XXcNGgNsiS == XXcNGgNsiS){WcCjcwMnTk = true;}
      if(kXCyTzNLrg == true){kXCyTzNLrg = false;}
      if(ZugtRuqbkW == true){ZugtRuqbkW = false;}
      if(nXEdpACDcK == true){nXEdpACDcK = false;}
      if(RcgGEJsMcl == true){RcgGEJsMcl = false;}
      if(VmItgbqiuK == true){VmItgbqiuK = false;}
      if(okILeMTYIS == true){okILeMTYIS = false;}
      if(wJigOxOZoI == true){wJigOxOZoI = false;}
      if(CeyzABPJwO == true){CeyzABPJwO = false;}
      if(JTISVfUVbr == true){JTISVfUVbr = false;}
      if(oUEKoLDaej == true){oUEKoLDaej = false;}
      if(NRtlHJlIKc == true){NRtlHJlIKc = false;}
      if(xJbtJcBPLi == true){xJbtJcBPLi = false;}
      if(brxxShanJo == true){brxxShanJo = false;}
      if(xneMBqZVKL == true){xneMBqZVKL = false;}
      if(sLKztfrJAM == true){sLKztfrJAM = false;}
      if(KnPwHUUwSZ == true){KnPwHUUwSZ = false;}
      if(ixzVfJdPsR == true){ixzVfJdPsR = false;}
      if(DeEAoQhyCm == true){DeEAoQhyCm = false;}
      if(oQnxdJXiEf == true){oQnxdJXiEf = false;}
      if(WcCjcwMnTk == true){WcCjcwMnTk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSTEKBTFWB
{ 
  void QjlFItgGeb()
  { 
      bool BwrWxlwsxj = false;
      bool kOSMxXmIlA = false;
      bool icxXgdpPeQ = false;
      bool dRgZaqTREy = false;
      bool FRNfdJFzcu = false;
      bool sbOiuYzTpS = false;
      bool ufNgGShslF = false;
      bool EVDmtROQtX = false;
      bool YpmiWBCydC = false;
      bool rAblDYDgZK = false;
      bool aMNWqXXbnd = false;
      bool KhYStEseJE = false;
      bool QjOiNEsRjU = false;
      bool NhqjwLcPry = false;
      bool cZJAqJaJqy = false;
      bool fYWUsqydJm = false;
      bool eGrTPcqoWh = false;
      bool bclLapZNrE = false;
      bool djZlnnKVpE = false;
      bool NyFFTWhpjO = false;
      string TmqnqkyFPT;
      string eyYODOfnki;
      string NZdtTuseJh;
      string GOmwPwgEin;
      string NjcRXGJyRP;
      string CBIRTtIxTu;
      string qSuhNPLcyH;
      string gbFxUcxMVN;
      string ktMseFGUbV;
      string mjkmwuotEH;
      string ugzKhauLwp;
      string wwaFJxFBCI;
      string JqBcTxqSBZ;
      string nCHNSEtCLE;
      string JuXkYpJecz;
      string omqwyDeWpk;
      string jcKWBtnMmF;
      string CCpyyOSPEc;
      string nLoBkBKLPO;
      string YXMZTgjBie;
      if(TmqnqkyFPT == ugzKhauLwp){BwrWxlwsxj = true;}
      else if(ugzKhauLwp == TmqnqkyFPT){aMNWqXXbnd = true;}
      if(eyYODOfnki == wwaFJxFBCI){kOSMxXmIlA = true;}
      else if(wwaFJxFBCI == eyYODOfnki){KhYStEseJE = true;}
      if(NZdtTuseJh == JqBcTxqSBZ){icxXgdpPeQ = true;}
      else if(JqBcTxqSBZ == NZdtTuseJh){QjOiNEsRjU = true;}
      if(GOmwPwgEin == nCHNSEtCLE){dRgZaqTREy = true;}
      else if(nCHNSEtCLE == GOmwPwgEin){NhqjwLcPry = true;}
      if(NjcRXGJyRP == JuXkYpJecz){FRNfdJFzcu = true;}
      else if(JuXkYpJecz == NjcRXGJyRP){cZJAqJaJqy = true;}
      if(CBIRTtIxTu == omqwyDeWpk){sbOiuYzTpS = true;}
      else if(omqwyDeWpk == CBIRTtIxTu){fYWUsqydJm = true;}
      if(qSuhNPLcyH == jcKWBtnMmF){ufNgGShslF = true;}
      else if(jcKWBtnMmF == qSuhNPLcyH){eGrTPcqoWh = true;}
      if(gbFxUcxMVN == CCpyyOSPEc){EVDmtROQtX = true;}
      if(ktMseFGUbV == nLoBkBKLPO){YpmiWBCydC = true;}
      if(mjkmwuotEH == YXMZTgjBie){rAblDYDgZK = true;}
      while(CCpyyOSPEc == gbFxUcxMVN){bclLapZNrE = true;}
      while(nLoBkBKLPO == nLoBkBKLPO){djZlnnKVpE = true;}
      while(YXMZTgjBie == YXMZTgjBie){NyFFTWhpjO = true;}
      if(BwrWxlwsxj == true){BwrWxlwsxj = false;}
      if(kOSMxXmIlA == true){kOSMxXmIlA = false;}
      if(icxXgdpPeQ == true){icxXgdpPeQ = false;}
      if(dRgZaqTREy == true){dRgZaqTREy = false;}
      if(FRNfdJFzcu == true){FRNfdJFzcu = false;}
      if(sbOiuYzTpS == true){sbOiuYzTpS = false;}
      if(ufNgGShslF == true){ufNgGShslF = false;}
      if(EVDmtROQtX == true){EVDmtROQtX = false;}
      if(YpmiWBCydC == true){YpmiWBCydC = false;}
      if(rAblDYDgZK == true){rAblDYDgZK = false;}
      if(aMNWqXXbnd == true){aMNWqXXbnd = false;}
      if(KhYStEseJE == true){KhYStEseJE = false;}
      if(QjOiNEsRjU == true){QjOiNEsRjU = false;}
      if(NhqjwLcPry == true){NhqjwLcPry = false;}
      if(cZJAqJaJqy == true){cZJAqJaJqy = false;}
      if(fYWUsqydJm == true){fYWUsqydJm = false;}
      if(eGrTPcqoWh == true){eGrTPcqoWh = false;}
      if(bclLapZNrE == true){bclLapZNrE = false;}
      if(djZlnnKVpE == true){djZlnnKVpE = false;}
      if(NyFFTWhpjO == true){NyFFTWhpjO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMOFQHQXPL
{ 
  void qGKXTlMSlC()
  { 
      bool usEJQsKfaQ = false;
      bool DlPgytjmWi = false;
      bool UpVhYtHkNe = false;
      bool bHYKldMDrh = false;
      bool BIaRRaonjz = false;
      bool RzRZPFXVkV = false;
      bool lYRunuMEtU = false;
      bool hguohLPDPy = false;
      bool FSAONcoyug = false;
      bool FqSWwcpecW = false;
      bool NjtPQjEcrE = false;
      bool oTFmQTYDgL = false;
      bool FOJNOqOXsE = false;
      bool UjZsjVYkxd = false;
      bool YMGpqlkeFb = false;
      bool DmyRQzZfAZ = false;
      bool VfjmiFsMCu = false;
      bool unFDmsITVc = false;
      bool FiSQBglIcj = false;
      bool urjWIrcSGl = false;
      string ChnyuSPzfh;
      string lAHWJPOGPP;
      string XjebShmabc;
      string rgZaAtcKeK;
      string bbEeiLpWBe;
      string njalhSDLeM;
      string eoWCoFZgWO;
      string mDbEmueArG;
      string rPYxoHGnrg;
      string qQfRemEBod;
      string lJAmqjIVzm;
      string mDSXUOPZNg;
      string ylnoWVXKYz;
      string qdKOUhPlFF;
      string zjoFtnyHwP;
      string WenIfAUKPV;
      string LyxzuJrEDl;
      string zdUHgOwiuh;
      string WQNJbLoCiU;
      string NEVisBmoJj;
      if(ChnyuSPzfh == lJAmqjIVzm){usEJQsKfaQ = true;}
      else if(lJAmqjIVzm == ChnyuSPzfh){NjtPQjEcrE = true;}
      if(lAHWJPOGPP == mDSXUOPZNg){DlPgytjmWi = true;}
      else if(mDSXUOPZNg == lAHWJPOGPP){oTFmQTYDgL = true;}
      if(XjebShmabc == ylnoWVXKYz){UpVhYtHkNe = true;}
      else if(ylnoWVXKYz == XjebShmabc){FOJNOqOXsE = true;}
      if(rgZaAtcKeK == qdKOUhPlFF){bHYKldMDrh = true;}
      else if(qdKOUhPlFF == rgZaAtcKeK){UjZsjVYkxd = true;}
      if(bbEeiLpWBe == zjoFtnyHwP){BIaRRaonjz = true;}
      else if(zjoFtnyHwP == bbEeiLpWBe){YMGpqlkeFb = true;}
      if(njalhSDLeM == WenIfAUKPV){RzRZPFXVkV = true;}
      else if(WenIfAUKPV == njalhSDLeM){DmyRQzZfAZ = true;}
      if(eoWCoFZgWO == LyxzuJrEDl){lYRunuMEtU = true;}
      else if(LyxzuJrEDl == eoWCoFZgWO){VfjmiFsMCu = true;}
      if(mDbEmueArG == zdUHgOwiuh){hguohLPDPy = true;}
      if(rPYxoHGnrg == WQNJbLoCiU){FSAONcoyug = true;}
      if(qQfRemEBod == NEVisBmoJj){FqSWwcpecW = true;}
      while(zdUHgOwiuh == mDbEmueArG){unFDmsITVc = true;}
      while(WQNJbLoCiU == WQNJbLoCiU){FiSQBglIcj = true;}
      while(NEVisBmoJj == NEVisBmoJj){urjWIrcSGl = true;}
      if(usEJQsKfaQ == true){usEJQsKfaQ = false;}
      if(DlPgytjmWi == true){DlPgytjmWi = false;}
      if(UpVhYtHkNe == true){UpVhYtHkNe = false;}
      if(bHYKldMDrh == true){bHYKldMDrh = false;}
      if(BIaRRaonjz == true){BIaRRaonjz = false;}
      if(RzRZPFXVkV == true){RzRZPFXVkV = false;}
      if(lYRunuMEtU == true){lYRunuMEtU = false;}
      if(hguohLPDPy == true){hguohLPDPy = false;}
      if(FSAONcoyug == true){FSAONcoyug = false;}
      if(FqSWwcpecW == true){FqSWwcpecW = false;}
      if(NjtPQjEcrE == true){NjtPQjEcrE = false;}
      if(oTFmQTYDgL == true){oTFmQTYDgL = false;}
      if(FOJNOqOXsE == true){FOJNOqOXsE = false;}
      if(UjZsjVYkxd == true){UjZsjVYkxd = false;}
      if(YMGpqlkeFb == true){YMGpqlkeFb = false;}
      if(DmyRQzZfAZ == true){DmyRQzZfAZ = false;}
      if(VfjmiFsMCu == true){VfjmiFsMCu = false;}
      if(unFDmsITVc == true){unFDmsITVc = false;}
      if(FiSQBglIcj == true){FiSQBglIcj = false;}
      if(urjWIrcSGl == true){urjWIrcSGl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UIJYFMKHOB
{ 
  void UVXKdRccga()
  { 
      bool zLgSkZCkpO = false;
      bool nCJElolKlV = false;
      bool LPjgfdDrFd = false;
      bool iEkKuXhixz = false;
      bool VEjJyDqXOQ = false;
      bool tNyjOiaAlG = false;
      bool WKfLfiRzJO = false;
      bool GDMlAGeZhc = false;
      bool lecnjUFAuL = false;
      bool whwpbKYXdP = false;
      bool lqNAKqAMjI = false;
      bool EBRJUqhqbK = false;
      bool cQEyRXGWJo = false;
      bool gGuSpuQcds = false;
      bool UsQmGuQmVk = false;
      bool chwTlUmPhl = false;
      bool jdCtaxFySY = false;
      bool ZEMhpizQqW = false;
      bool HSAYMzKbfV = false;
      bool IBurIpqWMJ = false;
      string bVEfQXFHFY;
      string SwYyapBbJa;
      string GctNQmslwD;
      string WmXORiPzXU;
      string gYVjYmxoaA;
      string XCekxybqOc;
      string eSLCBfXJgq;
      string aCDntgHJnd;
      string oELufUHmQT;
      string HXktpNMThs;
      string OnIiYVypqP;
      string pRDjnaHPVg;
      string XksNjDQIxf;
      string UnbtPBubWK;
      string VQuBcoUBGP;
      string GwxBVcttzV;
      string EosLtCpITm;
      string efsLKGoqjt;
      string iPChZYpaYl;
      string GBcBFgXjGZ;
      if(bVEfQXFHFY == OnIiYVypqP){zLgSkZCkpO = true;}
      else if(OnIiYVypqP == bVEfQXFHFY){lqNAKqAMjI = true;}
      if(SwYyapBbJa == pRDjnaHPVg){nCJElolKlV = true;}
      else if(pRDjnaHPVg == SwYyapBbJa){EBRJUqhqbK = true;}
      if(GctNQmslwD == XksNjDQIxf){LPjgfdDrFd = true;}
      else if(XksNjDQIxf == GctNQmslwD){cQEyRXGWJo = true;}
      if(WmXORiPzXU == UnbtPBubWK){iEkKuXhixz = true;}
      else if(UnbtPBubWK == WmXORiPzXU){gGuSpuQcds = true;}
      if(gYVjYmxoaA == VQuBcoUBGP){VEjJyDqXOQ = true;}
      else if(VQuBcoUBGP == gYVjYmxoaA){UsQmGuQmVk = true;}
      if(XCekxybqOc == GwxBVcttzV){tNyjOiaAlG = true;}
      else if(GwxBVcttzV == XCekxybqOc){chwTlUmPhl = true;}
      if(eSLCBfXJgq == EosLtCpITm){WKfLfiRzJO = true;}
      else if(EosLtCpITm == eSLCBfXJgq){jdCtaxFySY = true;}
      if(aCDntgHJnd == efsLKGoqjt){GDMlAGeZhc = true;}
      if(oELufUHmQT == iPChZYpaYl){lecnjUFAuL = true;}
      if(HXktpNMThs == GBcBFgXjGZ){whwpbKYXdP = true;}
      while(efsLKGoqjt == aCDntgHJnd){ZEMhpizQqW = true;}
      while(iPChZYpaYl == iPChZYpaYl){HSAYMzKbfV = true;}
      while(GBcBFgXjGZ == GBcBFgXjGZ){IBurIpqWMJ = true;}
      if(zLgSkZCkpO == true){zLgSkZCkpO = false;}
      if(nCJElolKlV == true){nCJElolKlV = false;}
      if(LPjgfdDrFd == true){LPjgfdDrFd = false;}
      if(iEkKuXhixz == true){iEkKuXhixz = false;}
      if(VEjJyDqXOQ == true){VEjJyDqXOQ = false;}
      if(tNyjOiaAlG == true){tNyjOiaAlG = false;}
      if(WKfLfiRzJO == true){WKfLfiRzJO = false;}
      if(GDMlAGeZhc == true){GDMlAGeZhc = false;}
      if(lecnjUFAuL == true){lecnjUFAuL = false;}
      if(whwpbKYXdP == true){whwpbKYXdP = false;}
      if(lqNAKqAMjI == true){lqNAKqAMjI = false;}
      if(EBRJUqhqbK == true){EBRJUqhqbK = false;}
      if(cQEyRXGWJo == true){cQEyRXGWJo = false;}
      if(gGuSpuQcds == true){gGuSpuQcds = false;}
      if(UsQmGuQmVk == true){UsQmGuQmVk = false;}
      if(chwTlUmPhl == true){chwTlUmPhl = false;}
      if(jdCtaxFySY == true){jdCtaxFySY = false;}
      if(ZEMhpizQqW == true){ZEMhpizQqW = false;}
      if(HSAYMzKbfV == true){HSAYMzKbfV = false;}
      if(IBurIpqWMJ == true){IBurIpqWMJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OUEQFEJZPJ
{ 
  void uNenwZfJgh()
  { 
      bool FFrUfNYTQi = false;
      bool MNztgWDNEf = false;
      bool UttiKitCEj = false;
      bool LlUSRkwYff = false;
      bool lbktBoKsRm = false;
      bool GEKEZLLJKx = false;
      bool TWPfWZsgbw = false;
      bool ZdhXsrJzgU = false;
      bool YAkQcHbPsG = false;
      bool YmOhMPLEXa = false;
      bool wdQUMcVmKh = false;
      bool BLboXSkyDP = false;
      bool ycnVWmOzLd = false;
      bool fEbGYujPEA = false;
      bool lnFKFNKZKs = false;
      bool dNBHcTpuxY = false;
      bool NVbgBxjVQc = false;
      bool iVtCcJXcPJ = false;
      bool cnoRzSDTdF = false;
      bool FnRelPMXJI = false;
      string FKckXIQJow;
      string YtPddxkZBF;
      string ZMamFPebVs;
      string JxYYytjsbV;
      string amPALyrSbG;
      string gZqUQripfI;
      string donwmbUpfj;
      string NqxedlxaaG;
      string XLzPLjFEHG;
      string KsNTrlzSNj;
      string dBmrrobMpe;
      string uIPYjRoYjC;
      string WPhYZUddlq;
      string ldMqbVXGWV;
      string IrNcLBdoiZ;
      string wahKNOSNSX;
      string LxZzrQwXwN;
      string shBOtdBFNX;
      string potLtLwBdN;
      string DKnzKKROkt;
      if(FKckXIQJow == dBmrrobMpe){FFrUfNYTQi = true;}
      else if(dBmrrobMpe == FKckXIQJow){wdQUMcVmKh = true;}
      if(YtPddxkZBF == uIPYjRoYjC){MNztgWDNEf = true;}
      else if(uIPYjRoYjC == YtPddxkZBF){BLboXSkyDP = true;}
      if(ZMamFPebVs == WPhYZUddlq){UttiKitCEj = true;}
      else if(WPhYZUddlq == ZMamFPebVs){ycnVWmOzLd = true;}
      if(JxYYytjsbV == ldMqbVXGWV){LlUSRkwYff = true;}
      else if(ldMqbVXGWV == JxYYytjsbV){fEbGYujPEA = true;}
      if(amPALyrSbG == IrNcLBdoiZ){lbktBoKsRm = true;}
      else if(IrNcLBdoiZ == amPALyrSbG){lnFKFNKZKs = true;}
      if(gZqUQripfI == wahKNOSNSX){GEKEZLLJKx = true;}
      else if(wahKNOSNSX == gZqUQripfI){dNBHcTpuxY = true;}
      if(donwmbUpfj == LxZzrQwXwN){TWPfWZsgbw = true;}
      else if(LxZzrQwXwN == donwmbUpfj){NVbgBxjVQc = true;}
      if(NqxedlxaaG == shBOtdBFNX){ZdhXsrJzgU = true;}
      if(XLzPLjFEHG == potLtLwBdN){YAkQcHbPsG = true;}
      if(KsNTrlzSNj == DKnzKKROkt){YmOhMPLEXa = true;}
      while(shBOtdBFNX == NqxedlxaaG){iVtCcJXcPJ = true;}
      while(potLtLwBdN == potLtLwBdN){cnoRzSDTdF = true;}
      while(DKnzKKROkt == DKnzKKROkt){FnRelPMXJI = true;}
      if(FFrUfNYTQi == true){FFrUfNYTQi = false;}
      if(MNztgWDNEf == true){MNztgWDNEf = false;}
      if(UttiKitCEj == true){UttiKitCEj = false;}
      if(LlUSRkwYff == true){LlUSRkwYff = false;}
      if(lbktBoKsRm == true){lbktBoKsRm = false;}
      if(GEKEZLLJKx == true){GEKEZLLJKx = false;}
      if(TWPfWZsgbw == true){TWPfWZsgbw = false;}
      if(ZdhXsrJzgU == true){ZdhXsrJzgU = false;}
      if(YAkQcHbPsG == true){YAkQcHbPsG = false;}
      if(YmOhMPLEXa == true){YmOhMPLEXa = false;}
      if(wdQUMcVmKh == true){wdQUMcVmKh = false;}
      if(BLboXSkyDP == true){BLboXSkyDP = false;}
      if(ycnVWmOzLd == true){ycnVWmOzLd = false;}
      if(fEbGYujPEA == true){fEbGYujPEA = false;}
      if(lnFKFNKZKs == true){lnFKFNKZKs = false;}
      if(dNBHcTpuxY == true){dNBHcTpuxY = false;}
      if(NVbgBxjVQc == true){NVbgBxjVQc = false;}
      if(iVtCcJXcPJ == true){iVtCcJXcPJ = false;}
      if(cnoRzSDTdF == true){cnoRzSDTdF = false;}
      if(FnRelPMXJI == true){FnRelPMXJI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORUEZITHTD
{ 
  void jHLdfHJcDF()
  { 
      bool taPIuGZhMX = false;
      bool xwtssZFJZq = false;
      bool WnbKmhGeKl = false;
      bool oYdswVaGaF = false;
      bool EfuPVwGrQa = false;
      bool cHIUrGyEUN = false;
      bool ztXaiYSAwX = false;
      bool yziUmpsLop = false;
      bool aNNiIgPIBp = false;
      bool XWkNFJITgw = false;
      bool dGwsccYnhB = false;
      bool NlPdllfnSB = false;
      bool IKzGzbNUOd = false;
      bool hYerMURUGe = false;
      bool IbaAckGGaT = false;
      bool cTBfnTGosB = false;
      bool ODYETnHWQR = false;
      bool TLhmrgizcO = false;
      bool UHtuANXyEs = false;
      bool NbaEPEDVfo = false;
      string ZkfftthADH;
      string hfrYZliTzz;
      string iAClajlYbF;
      string GqnSTMVBMc;
      string XgVGdXnSgu;
      string jeHXSYisFJ;
      string HIYyAqrZFM;
      string QhGWaCewHD;
      string uSrfUbjQzt;
      string dbwCUPHWGm;
      string eONUeCXjwQ;
      string slkCNoQrdX;
      string HaZKinkDCK;
      string tHpUXgFXBR;
      string DzTiBqqtoe;
      string zPshfEnDkp;
      string QUgkVlwQdg;
      string jspLUHGqIq;
      string wqOWLdOInS;
      string sBlKBiRhMP;
      if(ZkfftthADH == eONUeCXjwQ){taPIuGZhMX = true;}
      else if(eONUeCXjwQ == ZkfftthADH){dGwsccYnhB = true;}
      if(hfrYZliTzz == slkCNoQrdX){xwtssZFJZq = true;}
      else if(slkCNoQrdX == hfrYZliTzz){NlPdllfnSB = true;}
      if(iAClajlYbF == HaZKinkDCK){WnbKmhGeKl = true;}
      else if(HaZKinkDCK == iAClajlYbF){IKzGzbNUOd = true;}
      if(GqnSTMVBMc == tHpUXgFXBR){oYdswVaGaF = true;}
      else if(tHpUXgFXBR == GqnSTMVBMc){hYerMURUGe = true;}
      if(XgVGdXnSgu == DzTiBqqtoe){EfuPVwGrQa = true;}
      else if(DzTiBqqtoe == XgVGdXnSgu){IbaAckGGaT = true;}
      if(jeHXSYisFJ == zPshfEnDkp){cHIUrGyEUN = true;}
      else if(zPshfEnDkp == jeHXSYisFJ){cTBfnTGosB = true;}
      if(HIYyAqrZFM == QUgkVlwQdg){ztXaiYSAwX = true;}
      else if(QUgkVlwQdg == HIYyAqrZFM){ODYETnHWQR = true;}
      if(QhGWaCewHD == jspLUHGqIq){yziUmpsLop = true;}
      if(uSrfUbjQzt == wqOWLdOInS){aNNiIgPIBp = true;}
      if(dbwCUPHWGm == sBlKBiRhMP){XWkNFJITgw = true;}
      while(jspLUHGqIq == QhGWaCewHD){TLhmrgizcO = true;}
      while(wqOWLdOInS == wqOWLdOInS){UHtuANXyEs = true;}
      while(sBlKBiRhMP == sBlKBiRhMP){NbaEPEDVfo = true;}
      if(taPIuGZhMX == true){taPIuGZhMX = false;}
      if(xwtssZFJZq == true){xwtssZFJZq = false;}
      if(WnbKmhGeKl == true){WnbKmhGeKl = false;}
      if(oYdswVaGaF == true){oYdswVaGaF = false;}
      if(EfuPVwGrQa == true){EfuPVwGrQa = false;}
      if(cHIUrGyEUN == true){cHIUrGyEUN = false;}
      if(ztXaiYSAwX == true){ztXaiYSAwX = false;}
      if(yziUmpsLop == true){yziUmpsLop = false;}
      if(aNNiIgPIBp == true){aNNiIgPIBp = false;}
      if(XWkNFJITgw == true){XWkNFJITgw = false;}
      if(dGwsccYnhB == true){dGwsccYnhB = false;}
      if(NlPdllfnSB == true){NlPdllfnSB = false;}
      if(IKzGzbNUOd == true){IKzGzbNUOd = false;}
      if(hYerMURUGe == true){hYerMURUGe = false;}
      if(IbaAckGGaT == true){IbaAckGGaT = false;}
      if(cTBfnTGosB == true){cTBfnTGosB = false;}
      if(ODYETnHWQR == true){ODYETnHWQR = false;}
      if(TLhmrgizcO == true){TLhmrgizcO = false;}
      if(UHtuANXyEs == true){UHtuANXyEs = false;}
      if(NbaEPEDVfo == true){NbaEPEDVfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZRBFFTLBI
{ 
  void iDruBqwwqO()
  { 
      bool jGbGVRTdUe = false;
      bool TmbMYsBGlK = false;
      bool tgNPoATPzN = false;
      bool HzHYdfATFI = false;
      bool momDJWyYBO = false;
      bool dODxpDsLQV = false;
      bool xEdHWTfDhs = false;
      bool rgBdWEsJGS = false;
      bool BuOkiswJha = false;
      bool loCjKiKffo = false;
      bool quqHVxMYZk = false;
      bool JiEyTBosXd = false;
      bool XVUHHCeQSn = false;
      bool tNdRbFEGOl = false;
      bool fXjwQCkEQI = false;
      bool sRHCQUaiAT = false;
      bool RwFlqwFlVN = false;
      bool xidkyAlXqE = false;
      bool RZAJtbFbAH = false;
      bool eUGuTiRyFT = false;
      string LTgLGJMfwr;
      string gKtRLfVdtX;
      string GYUQqrPRQP;
      string ZkHwzkDWeg;
      string jCBhkDoKpc;
      string SIWwmmyQUN;
      string ttPfSwCySZ;
      string bzyMmEXlen;
      string CFbmwROLIM;
      string lmBRmpmUPo;
      string AqrPASJJJi;
      string PLkgKoScjB;
      string gqoGnoxgZx;
      string RDWomLMMlc;
      string HEBZwZCUGy;
      string WJjOHJClaL;
      string VbiMRMousz;
      string bFpGscoOJO;
      string lbabZHSIhc;
      string JakaHfUoHj;
      if(LTgLGJMfwr == AqrPASJJJi){jGbGVRTdUe = true;}
      else if(AqrPASJJJi == LTgLGJMfwr){quqHVxMYZk = true;}
      if(gKtRLfVdtX == PLkgKoScjB){TmbMYsBGlK = true;}
      else if(PLkgKoScjB == gKtRLfVdtX){JiEyTBosXd = true;}
      if(GYUQqrPRQP == gqoGnoxgZx){tgNPoATPzN = true;}
      else if(gqoGnoxgZx == GYUQqrPRQP){XVUHHCeQSn = true;}
      if(ZkHwzkDWeg == RDWomLMMlc){HzHYdfATFI = true;}
      else if(RDWomLMMlc == ZkHwzkDWeg){tNdRbFEGOl = true;}
      if(jCBhkDoKpc == HEBZwZCUGy){momDJWyYBO = true;}
      else if(HEBZwZCUGy == jCBhkDoKpc){fXjwQCkEQI = true;}
      if(SIWwmmyQUN == WJjOHJClaL){dODxpDsLQV = true;}
      else if(WJjOHJClaL == SIWwmmyQUN){sRHCQUaiAT = true;}
      if(ttPfSwCySZ == VbiMRMousz){xEdHWTfDhs = true;}
      else if(VbiMRMousz == ttPfSwCySZ){RwFlqwFlVN = true;}
      if(bzyMmEXlen == bFpGscoOJO){rgBdWEsJGS = true;}
      if(CFbmwROLIM == lbabZHSIhc){BuOkiswJha = true;}
      if(lmBRmpmUPo == JakaHfUoHj){loCjKiKffo = true;}
      while(bFpGscoOJO == bzyMmEXlen){xidkyAlXqE = true;}
      while(lbabZHSIhc == lbabZHSIhc){RZAJtbFbAH = true;}
      while(JakaHfUoHj == JakaHfUoHj){eUGuTiRyFT = true;}
      if(jGbGVRTdUe == true){jGbGVRTdUe = false;}
      if(TmbMYsBGlK == true){TmbMYsBGlK = false;}
      if(tgNPoATPzN == true){tgNPoATPzN = false;}
      if(HzHYdfATFI == true){HzHYdfATFI = false;}
      if(momDJWyYBO == true){momDJWyYBO = false;}
      if(dODxpDsLQV == true){dODxpDsLQV = false;}
      if(xEdHWTfDhs == true){xEdHWTfDhs = false;}
      if(rgBdWEsJGS == true){rgBdWEsJGS = false;}
      if(BuOkiswJha == true){BuOkiswJha = false;}
      if(loCjKiKffo == true){loCjKiKffo = false;}
      if(quqHVxMYZk == true){quqHVxMYZk = false;}
      if(JiEyTBosXd == true){JiEyTBosXd = false;}
      if(XVUHHCeQSn == true){XVUHHCeQSn = false;}
      if(tNdRbFEGOl == true){tNdRbFEGOl = false;}
      if(fXjwQCkEQI == true){fXjwQCkEQI = false;}
      if(sRHCQUaiAT == true){sRHCQUaiAT = false;}
      if(RwFlqwFlVN == true){RwFlqwFlVN = false;}
      if(xidkyAlXqE == true){xidkyAlXqE = false;}
      if(RZAJtbFbAH == true){RZAJtbFbAH = false;}
      if(eUGuTiRyFT == true){eUGuTiRyFT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZBGEUGVLN
{ 
  void yjCHEhJrrA()
  { 
      bool ZFODikQbuw = false;
      bool tUrkeiQUcC = false;
      bool KCsVJwqGpa = false;
      bool PRLoOKeDWy = false;
      bool hKXRKBXnAq = false;
      bool dMIgMXLstm = false;
      bool sJkTfcICWT = false;
      bool EMxeTzdbKI = false;
      bool YDFyxDJdbq = false;
      bool zkJjEYYEkh = false;
      bool rUQgmQOdNN = false;
      bool sihkNpElWb = false;
      bool SeZfUSDNZu = false;
      bool ZZpcQDlYLf = false;
      bool oeQOxPDXWO = false;
      bool TmgJOMukMT = false;
      bool MADSmTsFUJ = false;
      bool EfaplnOKhE = false;
      bool PeqLamrfND = false;
      bool IALqSoaxac = false;
      string LJNfzKTtQJ;
      string lkjsdyHryk;
      string DpPtxzVydf;
      string mupOQttCAS;
      string khxaotROqc;
      string QGKwYUtShz;
      string nVPjVquVci;
      string EEqfzUroFC;
      string hHGBPgktou;
      string AaUBdPRNFy;
      string zwlIYMOdwE;
      string bFNeRgOOUn;
      string FBfgicipCj;
      string CejGDlUybD;
      string SHxkTuMpiw;
      string ADsQsyPFYu;
      string cXaLBwUHaf;
      string MPmQVxDuMn;
      string QsHGizlSNF;
      string VPYfatgkiX;
      if(LJNfzKTtQJ == zwlIYMOdwE){ZFODikQbuw = true;}
      else if(zwlIYMOdwE == LJNfzKTtQJ){rUQgmQOdNN = true;}
      if(lkjsdyHryk == bFNeRgOOUn){tUrkeiQUcC = true;}
      else if(bFNeRgOOUn == lkjsdyHryk){sihkNpElWb = true;}
      if(DpPtxzVydf == FBfgicipCj){KCsVJwqGpa = true;}
      else if(FBfgicipCj == DpPtxzVydf){SeZfUSDNZu = true;}
      if(mupOQttCAS == CejGDlUybD){PRLoOKeDWy = true;}
      else if(CejGDlUybD == mupOQttCAS){ZZpcQDlYLf = true;}
      if(khxaotROqc == SHxkTuMpiw){hKXRKBXnAq = true;}
      else if(SHxkTuMpiw == khxaotROqc){oeQOxPDXWO = true;}
      if(QGKwYUtShz == ADsQsyPFYu){dMIgMXLstm = true;}
      else if(ADsQsyPFYu == QGKwYUtShz){TmgJOMukMT = true;}
      if(nVPjVquVci == cXaLBwUHaf){sJkTfcICWT = true;}
      else if(cXaLBwUHaf == nVPjVquVci){MADSmTsFUJ = true;}
      if(EEqfzUroFC == MPmQVxDuMn){EMxeTzdbKI = true;}
      if(hHGBPgktou == QsHGizlSNF){YDFyxDJdbq = true;}
      if(AaUBdPRNFy == VPYfatgkiX){zkJjEYYEkh = true;}
      while(MPmQVxDuMn == EEqfzUroFC){EfaplnOKhE = true;}
      while(QsHGizlSNF == QsHGizlSNF){PeqLamrfND = true;}
      while(VPYfatgkiX == VPYfatgkiX){IALqSoaxac = true;}
      if(ZFODikQbuw == true){ZFODikQbuw = false;}
      if(tUrkeiQUcC == true){tUrkeiQUcC = false;}
      if(KCsVJwqGpa == true){KCsVJwqGpa = false;}
      if(PRLoOKeDWy == true){PRLoOKeDWy = false;}
      if(hKXRKBXnAq == true){hKXRKBXnAq = false;}
      if(dMIgMXLstm == true){dMIgMXLstm = false;}
      if(sJkTfcICWT == true){sJkTfcICWT = false;}
      if(EMxeTzdbKI == true){EMxeTzdbKI = false;}
      if(YDFyxDJdbq == true){YDFyxDJdbq = false;}
      if(zkJjEYYEkh == true){zkJjEYYEkh = false;}
      if(rUQgmQOdNN == true){rUQgmQOdNN = false;}
      if(sihkNpElWb == true){sihkNpElWb = false;}
      if(SeZfUSDNZu == true){SeZfUSDNZu = false;}
      if(ZZpcQDlYLf == true){ZZpcQDlYLf = false;}
      if(oeQOxPDXWO == true){oeQOxPDXWO = false;}
      if(TmgJOMukMT == true){TmgJOMukMT = false;}
      if(MADSmTsFUJ == true){MADSmTsFUJ = false;}
      if(EfaplnOKhE == true){EfaplnOKhE = false;}
      if(PeqLamrfND == true){PeqLamrfND = false;}
      if(IALqSoaxac == true){IALqSoaxac = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKMWTKOMHK
{ 
  void jpseBxphHj()
  { 
      bool kefbyaUInD = false;
      bool YxjKpIRoua = false;
      bool oFPCJqXWAO = false;
      bool YxtjcDCMAa = false;
      bool WRwShFPUpF = false;
      bool kHYMmeOdRH = false;
      bool DyIZdaCAhm = false;
      bool GEnUDWJxUE = false;
      bool aCgtcRXhwx = false;
      bool oYusXYJVnG = false;
      bool CPmCzfSEJP = false;
      bool VRIMfAQNwM = false;
      bool CUDjygItwe = false;
      bool NmJNCLPduw = false;
      bool zTYgaXPiNW = false;
      bool HuZbDgMCER = false;
      bool XXHdCiHtJU = false;
      bool jlRzMiwVJZ = false;
      bool QZgZWRMhKV = false;
      bool zNYdYbLter = false;
      string ggqVFzrtGP;
      string bVIXJLEBeS;
      string acbelEMXEM;
      string tHncLNLglO;
      string DZlDCKANIY;
      string nzsrlEFLiA;
      string lUosVUgeLw;
      string zWOQOBpXcb;
      string EyOeXtNwpG;
      string Hzxkbijrgg;
      string cUCMYRjccj;
      string NgiHwmFKUa;
      string HknFnzYdnf;
      string RypwyiwCGG;
      string JkSGraQpoo;
      string dZWFZqfwXY;
      string rGnxSPplJN;
      string pCEORVShMN;
      string hiozCrakVG;
      string DzegODwUmc;
      if(ggqVFzrtGP == cUCMYRjccj){kefbyaUInD = true;}
      else if(cUCMYRjccj == ggqVFzrtGP){CPmCzfSEJP = true;}
      if(bVIXJLEBeS == NgiHwmFKUa){YxjKpIRoua = true;}
      else if(NgiHwmFKUa == bVIXJLEBeS){VRIMfAQNwM = true;}
      if(acbelEMXEM == HknFnzYdnf){oFPCJqXWAO = true;}
      else if(HknFnzYdnf == acbelEMXEM){CUDjygItwe = true;}
      if(tHncLNLglO == RypwyiwCGG){YxtjcDCMAa = true;}
      else if(RypwyiwCGG == tHncLNLglO){NmJNCLPduw = true;}
      if(DZlDCKANIY == JkSGraQpoo){WRwShFPUpF = true;}
      else if(JkSGraQpoo == DZlDCKANIY){zTYgaXPiNW = true;}
      if(nzsrlEFLiA == dZWFZqfwXY){kHYMmeOdRH = true;}
      else if(dZWFZqfwXY == nzsrlEFLiA){HuZbDgMCER = true;}
      if(lUosVUgeLw == rGnxSPplJN){DyIZdaCAhm = true;}
      else if(rGnxSPplJN == lUosVUgeLw){XXHdCiHtJU = true;}
      if(zWOQOBpXcb == pCEORVShMN){GEnUDWJxUE = true;}
      if(EyOeXtNwpG == hiozCrakVG){aCgtcRXhwx = true;}
      if(Hzxkbijrgg == DzegODwUmc){oYusXYJVnG = true;}
      while(pCEORVShMN == zWOQOBpXcb){jlRzMiwVJZ = true;}
      while(hiozCrakVG == hiozCrakVG){QZgZWRMhKV = true;}
      while(DzegODwUmc == DzegODwUmc){zNYdYbLter = true;}
      if(kefbyaUInD == true){kefbyaUInD = false;}
      if(YxjKpIRoua == true){YxjKpIRoua = false;}
      if(oFPCJqXWAO == true){oFPCJqXWAO = false;}
      if(YxtjcDCMAa == true){YxtjcDCMAa = false;}
      if(WRwShFPUpF == true){WRwShFPUpF = false;}
      if(kHYMmeOdRH == true){kHYMmeOdRH = false;}
      if(DyIZdaCAhm == true){DyIZdaCAhm = false;}
      if(GEnUDWJxUE == true){GEnUDWJxUE = false;}
      if(aCgtcRXhwx == true){aCgtcRXhwx = false;}
      if(oYusXYJVnG == true){oYusXYJVnG = false;}
      if(CPmCzfSEJP == true){CPmCzfSEJP = false;}
      if(VRIMfAQNwM == true){VRIMfAQNwM = false;}
      if(CUDjygItwe == true){CUDjygItwe = false;}
      if(NmJNCLPduw == true){NmJNCLPduw = false;}
      if(zTYgaXPiNW == true){zTYgaXPiNW = false;}
      if(HuZbDgMCER == true){HuZbDgMCER = false;}
      if(XXHdCiHtJU == true){XXHdCiHtJU = false;}
      if(jlRzMiwVJZ == true){jlRzMiwVJZ = false;}
      if(QZgZWRMhKV == true){QZgZWRMhKV = false;}
      if(zNYdYbLter == true){zNYdYbLter = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSJKODFPPT
{ 
  void MLHREEJsPY()
  { 
      bool NDZbIbeZVY = false;
      bool kqXcZsoipE = false;
      bool QeXkNBLwiz = false;
      bool WzhfBkmsIR = false;
      bool zLnRuUQasV = false;
      bool VFqIGhenOG = false;
      bool PhpWClJrbn = false;
      bool FuaYEEqFpr = false;
      bool kkDMcQHYYS = false;
      bool FzeBBRURPI = false;
      bool LYyEPadSDB = false;
      bool qZxVVeedsk = false;
      bool ejSJiGPZXm = false;
      bool jYogfLmzxB = false;
      bool lnVXbeBIeV = false;
      bool mqXedaGoVI = false;
      bool LEuPRRkPpK = false;
      bool rffrzpOtgD = false;
      bool EGtBAsBKDF = false;
      bool FxcnpgsFGJ = false;
      string xmHFRAoZEV;
      string CggDaUKjyK;
      string BnBFULcVeG;
      string ltugrXIuic;
      string WkoxsDfMOf;
      string ZhmJYJlCjG;
      string WSuyjHkzKD;
      string MPAVnPzEMR;
      string fQGzfDGlHi;
      string kGKcFDppMk;
      string RfBKSKhQUJ;
      string KgoSaFLuSf;
      string ByraSFEXQk;
      string ZIqazAOwfU;
      string VoRxYDRrCz;
      string qtXgjSmZrN;
      string FKAijBpOSZ;
      string pPPxKLguCO;
      string nMVQsekKqg;
      string MoDSOLohNW;
      if(xmHFRAoZEV == RfBKSKhQUJ){NDZbIbeZVY = true;}
      else if(RfBKSKhQUJ == xmHFRAoZEV){LYyEPadSDB = true;}
      if(CggDaUKjyK == KgoSaFLuSf){kqXcZsoipE = true;}
      else if(KgoSaFLuSf == CggDaUKjyK){qZxVVeedsk = true;}
      if(BnBFULcVeG == ByraSFEXQk){QeXkNBLwiz = true;}
      else if(ByraSFEXQk == BnBFULcVeG){ejSJiGPZXm = true;}
      if(ltugrXIuic == ZIqazAOwfU){WzhfBkmsIR = true;}
      else if(ZIqazAOwfU == ltugrXIuic){jYogfLmzxB = true;}
      if(WkoxsDfMOf == VoRxYDRrCz){zLnRuUQasV = true;}
      else if(VoRxYDRrCz == WkoxsDfMOf){lnVXbeBIeV = true;}
      if(ZhmJYJlCjG == qtXgjSmZrN){VFqIGhenOG = true;}
      else if(qtXgjSmZrN == ZhmJYJlCjG){mqXedaGoVI = true;}
      if(WSuyjHkzKD == FKAijBpOSZ){PhpWClJrbn = true;}
      else if(FKAijBpOSZ == WSuyjHkzKD){LEuPRRkPpK = true;}
      if(MPAVnPzEMR == pPPxKLguCO){FuaYEEqFpr = true;}
      if(fQGzfDGlHi == nMVQsekKqg){kkDMcQHYYS = true;}
      if(kGKcFDppMk == MoDSOLohNW){FzeBBRURPI = true;}
      while(pPPxKLguCO == MPAVnPzEMR){rffrzpOtgD = true;}
      while(nMVQsekKqg == nMVQsekKqg){EGtBAsBKDF = true;}
      while(MoDSOLohNW == MoDSOLohNW){FxcnpgsFGJ = true;}
      if(NDZbIbeZVY == true){NDZbIbeZVY = false;}
      if(kqXcZsoipE == true){kqXcZsoipE = false;}
      if(QeXkNBLwiz == true){QeXkNBLwiz = false;}
      if(WzhfBkmsIR == true){WzhfBkmsIR = false;}
      if(zLnRuUQasV == true){zLnRuUQasV = false;}
      if(VFqIGhenOG == true){VFqIGhenOG = false;}
      if(PhpWClJrbn == true){PhpWClJrbn = false;}
      if(FuaYEEqFpr == true){FuaYEEqFpr = false;}
      if(kkDMcQHYYS == true){kkDMcQHYYS = false;}
      if(FzeBBRURPI == true){FzeBBRURPI = false;}
      if(LYyEPadSDB == true){LYyEPadSDB = false;}
      if(qZxVVeedsk == true){qZxVVeedsk = false;}
      if(ejSJiGPZXm == true){ejSJiGPZXm = false;}
      if(jYogfLmzxB == true){jYogfLmzxB = false;}
      if(lnVXbeBIeV == true){lnVXbeBIeV = false;}
      if(mqXedaGoVI == true){mqXedaGoVI = false;}
      if(LEuPRRkPpK == true){LEuPRRkPpK = false;}
      if(rffrzpOtgD == true){rffrzpOtgD = false;}
      if(EGtBAsBKDF == true){EGtBAsBKDF = false;}
      if(FxcnpgsFGJ == true){FxcnpgsFGJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZIBFXEMOC
{ 
  void yMHMBBmJMH()
  { 
      bool ZcpHihjbOJ = false;
      bool hHZXGKhZjY = false;
      bool AXFsfHXKbJ = false;
      bool YjIUQBngsk = false;
      bool xgaTSTJscS = false;
      bool EJGSQCWxba = false;
      bool JZAEkxzEHF = false;
      bool WBgybTwkZL = false;
      bool xegIFOdoEN = false;
      bool dpFRaWfViV = false;
      bool UElXuDcHqw = false;
      bool GkXPcerrzV = false;
      bool TKAsbfuOWE = false;
      bool nZCDqssJNB = false;
      bool lVxHHrSpnw = false;
      bool enWMCKErwO = false;
      bool HNjmHfiTXj = false;
      bool lidxjxMrki = false;
      bool NFaaZADpBg = false;
      bool nANytXkKAb = false;
      string oTBFAABYXY;
      string xPzNXYeKpU;
      string LsiJRNoFLd;
      string dLKlXnmbuZ;
      string nGyNyfVRdO;
      string GqUYWukrnl;
      string LwMttkENpi;
      string lCOQgFuUKk;
      string rXaxWmpkOb;
      string DtnJNqtESN;
      string bHatbEcErQ;
      string APgDsnUPWH;
      string tTyOeqOFCo;
      string LpBxIkwfUS;
      string KlsybnMjPZ;
      string WdgLSIIMPk;
      string oWCCFJNjtI;
      string qotExIaAlq;
      string ddobSgIpdA;
      string bjQjcmjprR;
      if(oTBFAABYXY == bHatbEcErQ){ZcpHihjbOJ = true;}
      else if(bHatbEcErQ == oTBFAABYXY){UElXuDcHqw = true;}
      if(xPzNXYeKpU == APgDsnUPWH){hHZXGKhZjY = true;}
      else if(APgDsnUPWH == xPzNXYeKpU){GkXPcerrzV = true;}
      if(LsiJRNoFLd == tTyOeqOFCo){AXFsfHXKbJ = true;}
      else if(tTyOeqOFCo == LsiJRNoFLd){TKAsbfuOWE = true;}
      if(dLKlXnmbuZ == LpBxIkwfUS){YjIUQBngsk = true;}
      else if(LpBxIkwfUS == dLKlXnmbuZ){nZCDqssJNB = true;}
      if(nGyNyfVRdO == KlsybnMjPZ){xgaTSTJscS = true;}
      else if(KlsybnMjPZ == nGyNyfVRdO){lVxHHrSpnw = true;}
      if(GqUYWukrnl == WdgLSIIMPk){EJGSQCWxba = true;}
      else if(WdgLSIIMPk == GqUYWukrnl){enWMCKErwO = true;}
      if(LwMttkENpi == oWCCFJNjtI){JZAEkxzEHF = true;}
      else if(oWCCFJNjtI == LwMttkENpi){HNjmHfiTXj = true;}
      if(lCOQgFuUKk == qotExIaAlq){WBgybTwkZL = true;}
      if(rXaxWmpkOb == ddobSgIpdA){xegIFOdoEN = true;}
      if(DtnJNqtESN == bjQjcmjprR){dpFRaWfViV = true;}
      while(qotExIaAlq == lCOQgFuUKk){lidxjxMrki = true;}
      while(ddobSgIpdA == ddobSgIpdA){NFaaZADpBg = true;}
      while(bjQjcmjprR == bjQjcmjprR){nANytXkKAb = true;}
      if(ZcpHihjbOJ == true){ZcpHihjbOJ = false;}
      if(hHZXGKhZjY == true){hHZXGKhZjY = false;}
      if(AXFsfHXKbJ == true){AXFsfHXKbJ = false;}
      if(YjIUQBngsk == true){YjIUQBngsk = false;}
      if(xgaTSTJscS == true){xgaTSTJscS = false;}
      if(EJGSQCWxba == true){EJGSQCWxba = false;}
      if(JZAEkxzEHF == true){JZAEkxzEHF = false;}
      if(WBgybTwkZL == true){WBgybTwkZL = false;}
      if(xegIFOdoEN == true){xegIFOdoEN = false;}
      if(dpFRaWfViV == true){dpFRaWfViV = false;}
      if(UElXuDcHqw == true){UElXuDcHqw = false;}
      if(GkXPcerrzV == true){GkXPcerrzV = false;}
      if(TKAsbfuOWE == true){TKAsbfuOWE = false;}
      if(nZCDqssJNB == true){nZCDqssJNB = false;}
      if(lVxHHrSpnw == true){lVxHHrSpnw = false;}
      if(enWMCKErwO == true){enWMCKErwO = false;}
      if(HNjmHfiTXj == true){HNjmHfiTXj = false;}
      if(lidxjxMrki == true){lidxjxMrki = false;}
      if(NFaaZADpBg == true){NFaaZADpBg = false;}
      if(nANytXkKAb == true){nANytXkKAb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUSXNXOQYJ
{ 
  void TNlZDzSBje()
  { 
      bool JjafIDXyEL = false;
      bool fpLOialTQh = false;
      bool FVAuAfMCuG = false;
      bool MxYFjuoHoh = false;
      bool KUbJUlCZzn = false;
      bool ZUgCfmjfec = false;
      bool pVDxziRFem = false;
      bool kddiXjtqaN = false;
      bool clDGgrPVZx = false;
      bool LJbMqoRdJk = false;
      bool UwuLCupxeu = false;
      bool rsFRzDSwQH = false;
      bool SwfgbbCRqi = false;
      bool SQgorgqqEk = false;
      bool BSpdFREJMm = false;
      bool WUMCSYPNja = false;
      bool rXFwcbMPYR = false;
      bool MarfFAFCbJ = false;
      bool WsFELxDeVT = false;
      bool RcHcrdMtBd = false;
      string izGdXaHdzz;
      string mVWbaJtbOI;
      string GfOBJZqxww;
      string oHfAOCONOy;
      string OYckzLjTlw;
      string KihmpDjFUx;
      string iKhDKfoWNX;
      string ufMPthCdBy;
      string pXLzkGYsKL;
      string RJsQODqZaT;
      string WMFNBdVSrH;
      string AGDWHLzhRD;
      string GuMCFlmwAp;
      string qbDhadRxxG;
      string kFACKLFVJC;
      string EIIWMaADIP;
      string qYRCQYCUuc;
      string tBjKSAuJqs;
      string fQmykhSfUA;
      string cNohPLnykl;
      if(izGdXaHdzz == WMFNBdVSrH){JjafIDXyEL = true;}
      else if(WMFNBdVSrH == izGdXaHdzz){UwuLCupxeu = true;}
      if(mVWbaJtbOI == AGDWHLzhRD){fpLOialTQh = true;}
      else if(AGDWHLzhRD == mVWbaJtbOI){rsFRzDSwQH = true;}
      if(GfOBJZqxww == GuMCFlmwAp){FVAuAfMCuG = true;}
      else if(GuMCFlmwAp == GfOBJZqxww){SwfgbbCRqi = true;}
      if(oHfAOCONOy == qbDhadRxxG){MxYFjuoHoh = true;}
      else if(qbDhadRxxG == oHfAOCONOy){SQgorgqqEk = true;}
      if(OYckzLjTlw == kFACKLFVJC){KUbJUlCZzn = true;}
      else if(kFACKLFVJC == OYckzLjTlw){BSpdFREJMm = true;}
      if(KihmpDjFUx == EIIWMaADIP){ZUgCfmjfec = true;}
      else if(EIIWMaADIP == KihmpDjFUx){WUMCSYPNja = true;}
      if(iKhDKfoWNX == qYRCQYCUuc){pVDxziRFem = true;}
      else if(qYRCQYCUuc == iKhDKfoWNX){rXFwcbMPYR = true;}
      if(ufMPthCdBy == tBjKSAuJqs){kddiXjtqaN = true;}
      if(pXLzkGYsKL == fQmykhSfUA){clDGgrPVZx = true;}
      if(RJsQODqZaT == cNohPLnykl){LJbMqoRdJk = true;}
      while(tBjKSAuJqs == ufMPthCdBy){MarfFAFCbJ = true;}
      while(fQmykhSfUA == fQmykhSfUA){WsFELxDeVT = true;}
      while(cNohPLnykl == cNohPLnykl){RcHcrdMtBd = true;}
      if(JjafIDXyEL == true){JjafIDXyEL = false;}
      if(fpLOialTQh == true){fpLOialTQh = false;}
      if(FVAuAfMCuG == true){FVAuAfMCuG = false;}
      if(MxYFjuoHoh == true){MxYFjuoHoh = false;}
      if(KUbJUlCZzn == true){KUbJUlCZzn = false;}
      if(ZUgCfmjfec == true){ZUgCfmjfec = false;}
      if(pVDxziRFem == true){pVDxziRFem = false;}
      if(kddiXjtqaN == true){kddiXjtqaN = false;}
      if(clDGgrPVZx == true){clDGgrPVZx = false;}
      if(LJbMqoRdJk == true){LJbMqoRdJk = false;}
      if(UwuLCupxeu == true){UwuLCupxeu = false;}
      if(rsFRzDSwQH == true){rsFRzDSwQH = false;}
      if(SwfgbbCRqi == true){SwfgbbCRqi = false;}
      if(SQgorgqqEk == true){SQgorgqqEk = false;}
      if(BSpdFREJMm == true){BSpdFREJMm = false;}
      if(WUMCSYPNja == true){WUMCSYPNja = false;}
      if(rXFwcbMPYR == true){rXFwcbMPYR = false;}
      if(MarfFAFCbJ == true){MarfFAFCbJ = false;}
      if(WsFELxDeVT == true){WsFELxDeVT = false;}
      if(RcHcrdMtBd == true){RcHcrdMtBd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EODYORFIYM
{ 
  void BjNLfkZflZ()
  { 
      bool jFWVnxRHfa = false;
      bool lOluXWMyNr = false;
      bool ftfqIcntBZ = false;
      bool cJYjRyElSZ = false;
      bool hycOWnfpWY = false;
      bool kIIlUoZeML = false;
      bool JXFFybpBdZ = false;
      bool SaemJgRRUT = false;
      bool xxWcnTBlPb = false;
      bool XYYHQKsWPt = false;
      bool ydMxGKcUbm = false;
      bool XIKsOLAbRd = false;
      bool aDkBBsCXWz = false;
      bool nuBZUSkYWc = false;
      bool pfJcEPNerE = false;
      bool JQEkTurKwM = false;
      bool IFybycGkXw = false;
      bool aaFnntsIxk = false;
      bool fWeRpXpQFZ = false;
      bool ZZbKUkhhea = false;
      string wyxOeuYOND;
      string TcotUGrzom;
      string rpYTKqewTe;
      string jNAwocbzzg;
      string JPgPMghycm;
      string nIELaGZdDn;
      string PbtiSFbsFr;
      string dszIdcJJHd;
      string IgTgpbJoUi;
      string DyuLRgUywG;
      string EoskIuIwhy;
      string wQVYehINrq;
      string wmXWnfxnpw;
      string HLNAZTnhXt;
      string SMHVlmbVgi;
      string XHFEKRQWwb;
      string yUFkqkDVzK;
      string tZoyYifCjB;
      string EaHHXzFIoI;
      string CRluwyGVdA;
      if(wyxOeuYOND == EoskIuIwhy){jFWVnxRHfa = true;}
      else if(EoskIuIwhy == wyxOeuYOND){ydMxGKcUbm = true;}
      if(TcotUGrzom == wQVYehINrq){lOluXWMyNr = true;}
      else if(wQVYehINrq == TcotUGrzom){XIKsOLAbRd = true;}
      if(rpYTKqewTe == wmXWnfxnpw){ftfqIcntBZ = true;}
      else if(wmXWnfxnpw == rpYTKqewTe){aDkBBsCXWz = true;}
      if(jNAwocbzzg == HLNAZTnhXt){cJYjRyElSZ = true;}
      else if(HLNAZTnhXt == jNAwocbzzg){nuBZUSkYWc = true;}
      if(JPgPMghycm == SMHVlmbVgi){hycOWnfpWY = true;}
      else if(SMHVlmbVgi == JPgPMghycm){pfJcEPNerE = true;}
      if(nIELaGZdDn == XHFEKRQWwb){kIIlUoZeML = true;}
      else if(XHFEKRQWwb == nIELaGZdDn){JQEkTurKwM = true;}
      if(PbtiSFbsFr == yUFkqkDVzK){JXFFybpBdZ = true;}
      else if(yUFkqkDVzK == PbtiSFbsFr){IFybycGkXw = true;}
      if(dszIdcJJHd == tZoyYifCjB){SaemJgRRUT = true;}
      if(IgTgpbJoUi == EaHHXzFIoI){xxWcnTBlPb = true;}
      if(DyuLRgUywG == CRluwyGVdA){XYYHQKsWPt = true;}
      while(tZoyYifCjB == dszIdcJJHd){aaFnntsIxk = true;}
      while(EaHHXzFIoI == EaHHXzFIoI){fWeRpXpQFZ = true;}
      while(CRluwyGVdA == CRluwyGVdA){ZZbKUkhhea = true;}
      if(jFWVnxRHfa == true){jFWVnxRHfa = false;}
      if(lOluXWMyNr == true){lOluXWMyNr = false;}
      if(ftfqIcntBZ == true){ftfqIcntBZ = false;}
      if(cJYjRyElSZ == true){cJYjRyElSZ = false;}
      if(hycOWnfpWY == true){hycOWnfpWY = false;}
      if(kIIlUoZeML == true){kIIlUoZeML = false;}
      if(JXFFybpBdZ == true){JXFFybpBdZ = false;}
      if(SaemJgRRUT == true){SaemJgRRUT = false;}
      if(xxWcnTBlPb == true){xxWcnTBlPb = false;}
      if(XYYHQKsWPt == true){XYYHQKsWPt = false;}
      if(ydMxGKcUbm == true){ydMxGKcUbm = false;}
      if(XIKsOLAbRd == true){XIKsOLAbRd = false;}
      if(aDkBBsCXWz == true){aDkBBsCXWz = false;}
      if(nuBZUSkYWc == true){nuBZUSkYWc = false;}
      if(pfJcEPNerE == true){pfJcEPNerE = false;}
      if(JQEkTurKwM == true){JQEkTurKwM = false;}
      if(IFybycGkXw == true){IFybycGkXw = false;}
      if(aaFnntsIxk == true){aaFnntsIxk = false;}
      if(fWeRpXpQFZ == true){fWeRpXpQFZ = false;}
      if(ZZbKUkhhea == true){ZZbKUkhhea = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HABMIDWUSA
{ 
  void WETBtKwjtE()
  { 
      bool VhlreejyJB = false;
      bool iGPQqWxrfw = false;
      bool GkBWESfGwL = false;
      bool TVluuCHJGN = false;
      bool WJeTkfRcJq = false;
      bool dhsUVkgPnM = false;
      bool zdCygNUUUo = false;
      bool PmlSYwFglX = false;
      bool ACwFglbQYK = false;
      bool UrUtOrGglW = false;
      bool KxHTapwawY = false;
      bool eAcPLwgwQu = false;
      bool kEuJTXSqEg = false;
      bool oYtONDucdp = false;
      bool pBUzfUOFhR = false;
      bool KKPqlGBxzD = false;
      bool XEWPiFFOCI = false;
      bool BERZFjjwdy = false;
      bool INIlVeIDcG = false;
      bool BxcaSkeEPZ = false;
      string MAQVczTTto;
      string NUwEpeOACr;
      string cQoNLJJrqp;
      string LLDASTwapm;
      string jCCqyoenSy;
      string ZwKfbuKDJS;
      string obbEdBRwlW;
      string hmJOHZOyOV;
      string eVYrQOBXXW;
      string IsQWyIaxMw;
      string XhBwQlluXC;
      string fMnnmTCinP;
      string AtXONoVlQz;
      string zRlRxwTbbd;
      string bFzUqwEcjd;
      string FqJxwdJmhb;
      string PAeYDOZWpq;
      string zZGKmtuDXR;
      string jsClsHIoVT;
      string lgtANbaZRc;
      if(MAQVczTTto == XhBwQlluXC){VhlreejyJB = true;}
      else if(XhBwQlluXC == MAQVczTTto){KxHTapwawY = true;}
      if(NUwEpeOACr == fMnnmTCinP){iGPQqWxrfw = true;}
      else if(fMnnmTCinP == NUwEpeOACr){eAcPLwgwQu = true;}
      if(cQoNLJJrqp == AtXONoVlQz){GkBWESfGwL = true;}
      else if(AtXONoVlQz == cQoNLJJrqp){kEuJTXSqEg = true;}
      if(LLDASTwapm == zRlRxwTbbd){TVluuCHJGN = true;}
      else if(zRlRxwTbbd == LLDASTwapm){oYtONDucdp = true;}
      if(jCCqyoenSy == bFzUqwEcjd){WJeTkfRcJq = true;}
      else if(bFzUqwEcjd == jCCqyoenSy){pBUzfUOFhR = true;}
      if(ZwKfbuKDJS == FqJxwdJmhb){dhsUVkgPnM = true;}
      else if(FqJxwdJmhb == ZwKfbuKDJS){KKPqlGBxzD = true;}
      if(obbEdBRwlW == PAeYDOZWpq){zdCygNUUUo = true;}
      else if(PAeYDOZWpq == obbEdBRwlW){XEWPiFFOCI = true;}
      if(hmJOHZOyOV == zZGKmtuDXR){PmlSYwFglX = true;}
      if(eVYrQOBXXW == jsClsHIoVT){ACwFglbQYK = true;}
      if(IsQWyIaxMw == lgtANbaZRc){UrUtOrGglW = true;}
      while(zZGKmtuDXR == hmJOHZOyOV){BERZFjjwdy = true;}
      while(jsClsHIoVT == jsClsHIoVT){INIlVeIDcG = true;}
      while(lgtANbaZRc == lgtANbaZRc){BxcaSkeEPZ = true;}
      if(VhlreejyJB == true){VhlreejyJB = false;}
      if(iGPQqWxrfw == true){iGPQqWxrfw = false;}
      if(GkBWESfGwL == true){GkBWESfGwL = false;}
      if(TVluuCHJGN == true){TVluuCHJGN = false;}
      if(WJeTkfRcJq == true){WJeTkfRcJq = false;}
      if(dhsUVkgPnM == true){dhsUVkgPnM = false;}
      if(zdCygNUUUo == true){zdCygNUUUo = false;}
      if(PmlSYwFglX == true){PmlSYwFglX = false;}
      if(ACwFglbQYK == true){ACwFglbQYK = false;}
      if(UrUtOrGglW == true){UrUtOrGglW = false;}
      if(KxHTapwawY == true){KxHTapwawY = false;}
      if(eAcPLwgwQu == true){eAcPLwgwQu = false;}
      if(kEuJTXSqEg == true){kEuJTXSqEg = false;}
      if(oYtONDucdp == true){oYtONDucdp = false;}
      if(pBUzfUOFhR == true){pBUzfUOFhR = false;}
      if(KKPqlGBxzD == true){KKPqlGBxzD = false;}
      if(XEWPiFFOCI == true){XEWPiFFOCI = false;}
      if(BERZFjjwdy == true){BERZFjjwdy = false;}
      if(INIlVeIDcG == true){INIlVeIDcG = false;}
      if(BxcaSkeEPZ == true){BxcaSkeEPZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBRVBTYGNL
{ 
  void LlRiquYJxr()
  { 
      bool LtiljzWKDr = false;
      bool sZbbzsNSAH = false;
      bool wwqBNPXxnC = false;
      bool dWnblaWgxu = false;
      bool IQsuXAxeqx = false;
      bool eIBLeOChYU = false;
      bool bYWAOWkApY = false;
      bool WgVEzeDwcN = false;
      bool RrGpXUUbwX = false;
      bool XnHbTitrfB = false;
      bool OxoRaxmwMA = false;
      bool KGFLCjSfcs = false;
      bool BJDRAiYskP = false;
      bool kLPayUDnPZ = false;
      bool hXPwMRhwYj = false;
      bool QOOmAFsWRr = false;
      bool XsLwOzpeMh = false;
      bool fdQCKctGFi = false;
      bool AcTBzWwcZs = false;
      bool afWWBoMSgM = false;
      string ZGrmBKDKkF;
      string lCQHrLwfme;
      string nGDLJBWghS;
      string kVJPLxYiSJ;
      string NmcnuixfXE;
      string VllneTDgcz;
      string mVcRTQsAuu;
      string mNMdRBcOPa;
      string EqJcxziUkq;
      string sqFTVqKKTe;
      string pxjbRHYHWd;
      string qnQCtwMzUU;
      string gXPECwIrHZ;
      string pRukjHGgLo;
      string ZbyHAEZCYZ;
      string eKpyxShfZU;
      string zgAwmYseSm;
      string oeneuFYHDx;
      string VGSguebwmR;
      string ZZHppraCTb;
      if(ZGrmBKDKkF == pxjbRHYHWd){LtiljzWKDr = true;}
      else if(pxjbRHYHWd == ZGrmBKDKkF){OxoRaxmwMA = true;}
      if(lCQHrLwfme == qnQCtwMzUU){sZbbzsNSAH = true;}
      else if(qnQCtwMzUU == lCQHrLwfme){KGFLCjSfcs = true;}
      if(nGDLJBWghS == gXPECwIrHZ){wwqBNPXxnC = true;}
      else if(gXPECwIrHZ == nGDLJBWghS){BJDRAiYskP = true;}
      if(kVJPLxYiSJ == pRukjHGgLo){dWnblaWgxu = true;}
      else if(pRukjHGgLo == kVJPLxYiSJ){kLPayUDnPZ = true;}
      if(NmcnuixfXE == ZbyHAEZCYZ){IQsuXAxeqx = true;}
      else if(ZbyHAEZCYZ == NmcnuixfXE){hXPwMRhwYj = true;}
      if(VllneTDgcz == eKpyxShfZU){eIBLeOChYU = true;}
      else if(eKpyxShfZU == VllneTDgcz){QOOmAFsWRr = true;}
      if(mVcRTQsAuu == zgAwmYseSm){bYWAOWkApY = true;}
      else if(zgAwmYseSm == mVcRTQsAuu){XsLwOzpeMh = true;}
      if(mNMdRBcOPa == oeneuFYHDx){WgVEzeDwcN = true;}
      if(EqJcxziUkq == VGSguebwmR){RrGpXUUbwX = true;}
      if(sqFTVqKKTe == ZZHppraCTb){XnHbTitrfB = true;}
      while(oeneuFYHDx == mNMdRBcOPa){fdQCKctGFi = true;}
      while(VGSguebwmR == VGSguebwmR){AcTBzWwcZs = true;}
      while(ZZHppraCTb == ZZHppraCTb){afWWBoMSgM = true;}
      if(LtiljzWKDr == true){LtiljzWKDr = false;}
      if(sZbbzsNSAH == true){sZbbzsNSAH = false;}
      if(wwqBNPXxnC == true){wwqBNPXxnC = false;}
      if(dWnblaWgxu == true){dWnblaWgxu = false;}
      if(IQsuXAxeqx == true){IQsuXAxeqx = false;}
      if(eIBLeOChYU == true){eIBLeOChYU = false;}
      if(bYWAOWkApY == true){bYWAOWkApY = false;}
      if(WgVEzeDwcN == true){WgVEzeDwcN = false;}
      if(RrGpXUUbwX == true){RrGpXUUbwX = false;}
      if(XnHbTitrfB == true){XnHbTitrfB = false;}
      if(OxoRaxmwMA == true){OxoRaxmwMA = false;}
      if(KGFLCjSfcs == true){KGFLCjSfcs = false;}
      if(BJDRAiYskP == true){BJDRAiYskP = false;}
      if(kLPayUDnPZ == true){kLPayUDnPZ = false;}
      if(hXPwMRhwYj == true){hXPwMRhwYj = false;}
      if(QOOmAFsWRr == true){QOOmAFsWRr = false;}
      if(XsLwOzpeMh == true){XsLwOzpeMh = false;}
      if(fdQCKctGFi == true){fdQCKctGFi = false;}
      if(AcTBzWwcZs == true){AcTBzWwcZs = false;}
      if(afWWBoMSgM == true){afWWBoMSgM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYNGBMWUTV
{ 
  void lonDZJHYws()
  { 
      bool klLnjuJQiQ = false;
      bool LmqmkqTkiI = false;
      bool ojJHncTpDp = false;
      bool BsdYUpjnJF = false;
      bool mblCqxHmTq = false;
      bool rMOxmAbDzG = false;
      bool bSMrPRJSSu = false;
      bool HfbcUNxHPq = false;
      bool VgWMxndflT = false;
      bool NfnDdTPslZ = false;
      bool moUYiMklbZ = false;
      bool DUmIktwzta = false;
      bool mcfygaqXyB = false;
      bool xEVpDfMyck = false;
      bool DrEMQssfSj = false;
      bool WPyLlKIVqI = false;
      bool UMmZbyzwEE = false;
      bool hyWJXuYThn = false;
      bool hKFOdhFJEs = false;
      bool WpGUPpFdkR = false;
      string qGKUMbLnYO;
      string kbJhHpKlqS;
      string cDwSLEIqAo;
      string MqlwdLUACC;
      string XGuwnWeJjb;
      string OUaYdnKqJH;
      string TTmiBsoMDw;
      string VJjouVIzdo;
      string ZyHYarPNSp;
      string AcqthDTLtt;
      string gRFnGFjlcH;
      string eKNTgUMNIJ;
      string cbtMurSoGr;
      string CwFjIIrSSV;
      string HdjKLpPWMM;
      string pFDkQEWsrN;
      string muekFiEcLY;
      string ctumBzrjBF;
      string cubtBwsUSD;
      string kzZEiLyyFc;
      if(qGKUMbLnYO == gRFnGFjlcH){klLnjuJQiQ = true;}
      else if(gRFnGFjlcH == qGKUMbLnYO){moUYiMklbZ = true;}
      if(kbJhHpKlqS == eKNTgUMNIJ){LmqmkqTkiI = true;}
      else if(eKNTgUMNIJ == kbJhHpKlqS){DUmIktwzta = true;}
      if(cDwSLEIqAo == cbtMurSoGr){ojJHncTpDp = true;}
      else if(cbtMurSoGr == cDwSLEIqAo){mcfygaqXyB = true;}
      if(MqlwdLUACC == CwFjIIrSSV){BsdYUpjnJF = true;}
      else if(CwFjIIrSSV == MqlwdLUACC){xEVpDfMyck = true;}
      if(XGuwnWeJjb == HdjKLpPWMM){mblCqxHmTq = true;}
      else if(HdjKLpPWMM == XGuwnWeJjb){DrEMQssfSj = true;}
      if(OUaYdnKqJH == pFDkQEWsrN){rMOxmAbDzG = true;}
      else if(pFDkQEWsrN == OUaYdnKqJH){WPyLlKIVqI = true;}
      if(TTmiBsoMDw == muekFiEcLY){bSMrPRJSSu = true;}
      else if(muekFiEcLY == TTmiBsoMDw){UMmZbyzwEE = true;}
      if(VJjouVIzdo == ctumBzrjBF){HfbcUNxHPq = true;}
      if(ZyHYarPNSp == cubtBwsUSD){VgWMxndflT = true;}
      if(AcqthDTLtt == kzZEiLyyFc){NfnDdTPslZ = true;}
      while(ctumBzrjBF == VJjouVIzdo){hyWJXuYThn = true;}
      while(cubtBwsUSD == cubtBwsUSD){hKFOdhFJEs = true;}
      while(kzZEiLyyFc == kzZEiLyyFc){WpGUPpFdkR = true;}
      if(klLnjuJQiQ == true){klLnjuJQiQ = false;}
      if(LmqmkqTkiI == true){LmqmkqTkiI = false;}
      if(ojJHncTpDp == true){ojJHncTpDp = false;}
      if(BsdYUpjnJF == true){BsdYUpjnJF = false;}
      if(mblCqxHmTq == true){mblCqxHmTq = false;}
      if(rMOxmAbDzG == true){rMOxmAbDzG = false;}
      if(bSMrPRJSSu == true){bSMrPRJSSu = false;}
      if(HfbcUNxHPq == true){HfbcUNxHPq = false;}
      if(VgWMxndflT == true){VgWMxndflT = false;}
      if(NfnDdTPslZ == true){NfnDdTPslZ = false;}
      if(moUYiMklbZ == true){moUYiMklbZ = false;}
      if(DUmIktwzta == true){DUmIktwzta = false;}
      if(mcfygaqXyB == true){mcfygaqXyB = false;}
      if(xEVpDfMyck == true){xEVpDfMyck = false;}
      if(DrEMQssfSj == true){DrEMQssfSj = false;}
      if(WPyLlKIVqI == true){WPyLlKIVqI = false;}
      if(UMmZbyzwEE == true){UMmZbyzwEE = false;}
      if(hyWJXuYThn == true){hyWJXuYThn = false;}
      if(hKFOdhFJEs == true){hKFOdhFJEs = false;}
      if(WpGUPpFdkR == true){WpGUPpFdkR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNJTVIUMCM
{ 
  void IJEUeahFcm()
  { 
      bool TwQCMnKeyG = false;
      bool MnVRkRnIqW = false;
      bool SPmCImAIhO = false;
      bool XlZTsOHujB = false;
      bool GnZoTVxRhE = false;
      bool IGrpREJNsY = false;
      bool mCwjiaOCXW = false;
      bool JsYpQdpxil = false;
      bool ohadFQtiBo = false;
      bool FsBKNErpFr = false;
      bool HutKuPhBYm = false;
      bool NLeGiFaSdR = false;
      bool feAhRPqNbM = false;
      bool lAqpetnPip = false;
      bool irKOasOtaI = false;
      bool cYLnMcuLse = false;
      bool XUZMANTnbo = false;
      bool QLjmimUkHX = false;
      bool AwlTjMnDdB = false;
      bool zbWDSNSxNM = false;
      string rnMnRfWWIg;
      string suAxiTFkwV;
      string xxesFGlKgP;
      string ttuQHlYgnN;
      string iSsrAUBqxg;
      string mDEhWtISiL;
      string tLpslyzjox;
      string uXwileDmsj;
      string EtNAbqpMsN;
      string cFycSWbAFC;
      string URBzkPGVwq;
      string pVZyGzypQu;
      string HlpbUpYTPO;
      string DDhpOmsNOM;
      string jUQCWHeAVS;
      string YliJtibZeu;
      string plFgnmmiiT;
      string GjaELmVmEN;
      string KYywpQTXwf;
      string KSiSVxPiNj;
      if(rnMnRfWWIg == URBzkPGVwq){TwQCMnKeyG = true;}
      else if(URBzkPGVwq == rnMnRfWWIg){HutKuPhBYm = true;}
      if(suAxiTFkwV == pVZyGzypQu){MnVRkRnIqW = true;}
      else if(pVZyGzypQu == suAxiTFkwV){NLeGiFaSdR = true;}
      if(xxesFGlKgP == HlpbUpYTPO){SPmCImAIhO = true;}
      else if(HlpbUpYTPO == xxesFGlKgP){feAhRPqNbM = true;}
      if(ttuQHlYgnN == DDhpOmsNOM){XlZTsOHujB = true;}
      else if(DDhpOmsNOM == ttuQHlYgnN){lAqpetnPip = true;}
      if(iSsrAUBqxg == jUQCWHeAVS){GnZoTVxRhE = true;}
      else if(jUQCWHeAVS == iSsrAUBqxg){irKOasOtaI = true;}
      if(mDEhWtISiL == YliJtibZeu){IGrpREJNsY = true;}
      else if(YliJtibZeu == mDEhWtISiL){cYLnMcuLse = true;}
      if(tLpslyzjox == plFgnmmiiT){mCwjiaOCXW = true;}
      else if(plFgnmmiiT == tLpslyzjox){XUZMANTnbo = true;}
      if(uXwileDmsj == GjaELmVmEN){JsYpQdpxil = true;}
      if(EtNAbqpMsN == KYywpQTXwf){ohadFQtiBo = true;}
      if(cFycSWbAFC == KSiSVxPiNj){FsBKNErpFr = true;}
      while(GjaELmVmEN == uXwileDmsj){QLjmimUkHX = true;}
      while(KYywpQTXwf == KYywpQTXwf){AwlTjMnDdB = true;}
      while(KSiSVxPiNj == KSiSVxPiNj){zbWDSNSxNM = true;}
      if(TwQCMnKeyG == true){TwQCMnKeyG = false;}
      if(MnVRkRnIqW == true){MnVRkRnIqW = false;}
      if(SPmCImAIhO == true){SPmCImAIhO = false;}
      if(XlZTsOHujB == true){XlZTsOHujB = false;}
      if(GnZoTVxRhE == true){GnZoTVxRhE = false;}
      if(IGrpREJNsY == true){IGrpREJNsY = false;}
      if(mCwjiaOCXW == true){mCwjiaOCXW = false;}
      if(JsYpQdpxil == true){JsYpQdpxil = false;}
      if(ohadFQtiBo == true){ohadFQtiBo = false;}
      if(FsBKNErpFr == true){FsBKNErpFr = false;}
      if(HutKuPhBYm == true){HutKuPhBYm = false;}
      if(NLeGiFaSdR == true){NLeGiFaSdR = false;}
      if(feAhRPqNbM == true){feAhRPqNbM = false;}
      if(lAqpetnPip == true){lAqpetnPip = false;}
      if(irKOasOtaI == true){irKOasOtaI = false;}
      if(cYLnMcuLse == true){cYLnMcuLse = false;}
      if(XUZMANTnbo == true){XUZMANTnbo = false;}
      if(QLjmimUkHX == true){QLjmimUkHX = false;}
      if(AwlTjMnDdB == true){AwlTjMnDdB = false;}
      if(zbWDSNSxNM == true){zbWDSNSxNM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHRXUXCFFG
{ 
  void osPbuMNhbg()
  { 
      bool CmtPYHZDDT = false;
      bool zKbKEQwBux = false;
      bool wejSpLwVfN = false;
      bool WegyatjzsW = false;
      bool CLgpQyFfrq = false;
      bool KDPpBWDbZM = false;
      bool KDWowTddiK = false;
      bool gwIYtjxsCr = false;
      bool FPdoDSPpwD = false;
      bool pHZfLzorsw = false;
      bool TbwhKNuquQ = false;
      bool ZJZgGuZgkc = false;
      bool EmgeTYWcMu = false;
      bool uFzFXdSuep = false;
      bool XYufdghrYQ = false;
      bool YHGPrguROk = false;
      bool qRdzUUJTJc = false;
      bool bdCuFfrBBl = false;
      bool pdDwWnyiNp = false;
      bool iBgsyFtuKI = false;
      string ajgMzSWCXk;
      string KlJLcbtYwk;
      string hTldCJmmWb;
      string jgXQgoiYqw;
      string xVeNafHGXr;
      string WYEmHGxCJo;
      string eiewAdNsem;
      string sVgAmLoXDW;
      string CgPeELbkJZ;
      string rfOCQOqiNx;
      string RObjyBqDzu;
      string RZzmmyTzqo;
      string BbiEuNGejY;
      string UGJFEnEfgD;
      string TYkOIRfbPR;
      string urqYwoeWnk;
      string uMTZaKPshz;
      string smRnUbpUud;
      string gdPRdcOkJP;
      string IgqwHGFLnx;
      if(ajgMzSWCXk == RObjyBqDzu){CmtPYHZDDT = true;}
      else if(RObjyBqDzu == ajgMzSWCXk){TbwhKNuquQ = true;}
      if(KlJLcbtYwk == RZzmmyTzqo){zKbKEQwBux = true;}
      else if(RZzmmyTzqo == KlJLcbtYwk){ZJZgGuZgkc = true;}
      if(hTldCJmmWb == BbiEuNGejY){wejSpLwVfN = true;}
      else if(BbiEuNGejY == hTldCJmmWb){EmgeTYWcMu = true;}
      if(jgXQgoiYqw == UGJFEnEfgD){WegyatjzsW = true;}
      else if(UGJFEnEfgD == jgXQgoiYqw){uFzFXdSuep = true;}
      if(xVeNafHGXr == TYkOIRfbPR){CLgpQyFfrq = true;}
      else if(TYkOIRfbPR == xVeNafHGXr){XYufdghrYQ = true;}
      if(WYEmHGxCJo == urqYwoeWnk){KDPpBWDbZM = true;}
      else if(urqYwoeWnk == WYEmHGxCJo){YHGPrguROk = true;}
      if(eiewAdNsem == uMTZaKPshz){KDWowTddiK = true;}
      else if(uMTZaKPshz == eiewAdNsem){qRdzUUJTJc = true;}
      if(sVgAmLoXDW == smRnUbpUud){gwIYtjxsCr = true;}
      if(CgPeELbkJZ == gdPRdcOkJP){FPdoDSPpwD = true;}
      if(rfOCQOqiNx == IgqwHGFLnx){pHZfLzorsw = true;}
      while(smRnUbpUud == sVgAmLoXDW){bdCuFfrBBl = true;}
      while(gdPRdcOkJP == gdPRdcOkJP){pdDwWnyiNp = true;}
      while(IgqwHGFLnx == IgqwHGFLnx){iBgsyFtuKI = true;}
      if(CmtPYHZDDT == true){CmtPYHZDDT = false;}
      if(zKbKEQwBux == true){zKbKEQwBux = false;}
      if(wejSpLwVfN == true){wejSpLwVfN = false;}
      if(WegyatjzsW == true){WegyatjzsW = false;}
      if(CLgpQyFfrq == true){CLgpQyFfrq = false;}
      if(KDPpBWDbZM == true){KDPpBWDbZM = false;}
      if(KDWowTddiK == true){KDWowTddiK = false;}
      if(gwIYtjxsCr == true){gwIYtjxsCr = false;}
      if(FPdoDSPpwD == true){FPdoDSPpwD = false;}
      if(pHZfLzorsw == true){pHZfLzorsw = false;}
      if(TbwhKNuquQ == true){TbwhKNuquQ = false;}
      if(ZJZgGuZgkc == true){ZJZgGuZgkc = false;}
      if(EmgeTYWcMu == true){EmgeTYWcMu = false;}
      if(uFzFXdSuep == true){uFzFXdSuep = false;}
      if(XYufdghrYQ == true){XYufdghrYQ = false;}
      if(YHGPrguROk == true){YHGPrguROk = false;}
      if(qRdzUUJTJc == true){qRdzUUJTJc = false;}
      if(bdCuFfrBBl == true){bdCuFfrBBl = false;}
      if(pdDwWnyiNp == true){pdDwWnyiNp = false;}
      if(iBgsyFtuKI == true){iBgsyFtuKI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZUGXYGLRY
{ 
  void qVDmHntFNK()
  { 
      bool cVuNnELTbY = false;
      bool DQIZfSzDtz = false;
      bool OXGkYaRrbC = false;
      bool fMcJipHnHy = false;
      bool QRVIgxhwuF = false;
      bool lUYnxEPKoN = false;
      bool lSrYsqnyqo = false;
      bool LLuuhwBxDa = false;
      bool rUxWQKnnLd = false;
      bool axzsMyZxPp = false;
      bool JiFGsaZcGA = false;
      bool DRGNUQVUIh = false;
      bool CAlNNOLCij = false;
      bool WEhNRIPpco = false;
      bool kLhLZJpkYu = false;
      bool bEogmJwqre = false;
      bool PXsVcyirwL = false;
      bool AeqSxqRamE = false;
      bool XacmHSPAZI = false;
      bool LYyxZNRMha = false;
      string eZgatIAyVR;
      string LrirZDZVAj;
      string OFeSiAqwcw;
      string rNnGqeXyfI;
      string wnmUCipLpt;
      string OwqgIYuOqt;
      string REVZYyDcAt;
      string faprnZSKPA;
      string JfFhguWHxS;
      string jIHlqrSMuE;
      string eNLwOnGzrh;
      string Gkyqjkymrd;
      string auehKWSEAw;
      string HFOKUwTJTr;
      string nWPOLyJQBF;
      string seTQcjhdlr;
      string UCywaAVnVm;
      string QoTAoEfQVL;
      string MCCuCblygk;
      string OpWaXlXSmL;
      if(eZgatIAyVR == eNLwOnGzrh){cVuNnELTbY = true;}
      else if(eNLwOnGzrh == eZgatIAyVR){JiFGsaZcGA = true;}
      if(LrirZDZVAj == Gkyqjkymrd){DQIZfSzDtz = true;}
      else if(Gkyqjkymrd == LrirZDZVAj){DRGNUQVUIh = true;}
      if(OFeSiAqwcw == auehKWSEAw){OXGkYaRrbC = true;}
      else if(auehKWSEAw == OFeSiAqwcw){CAlNNOLCij = true;}
      if(rNnGqeXyfI == HFOKUwTJTr){fMcJipHnHy = true;}
      else if(HFOKUwTJTr == rNnGqeXyfI){WEhNRIPpco = true;}
      if(wnmUCipLpt == nWPOLyJQBF){QRVIgxhwuF = true;}
      else if(nWPOLyJQBF == wnmUCipLpt){kLhLZJpkYu = true;}
      if(OwqgIYuOqt == seTQcjhdlr){lUYnxEPKoN = true;}
      else if(seTQcjhdlr == OwqgIYuOqt){bEogmJwqre = true;}
      if(REVZYyDcAt == UCywaAVnVm){lSrYsqnyqo = true;}
      else if(UCywaAVnVm == REVZYyDcAt){PXsVcyirwL = true;}
      if(faprnZSKPA == QoTAoEfQVL){LLuuhwBxDa = true;}
      if(JfFhguWHxS == MCCuCblygk){rUxWQKnnLd = true;}
      if(jIHlqrSMuE == OpWaXlXSmL){axzsMyZxPp = true;}
      while(QoTAoEfQVL == faprnZSKPA){AeqSxqRamE = true;}
      while(MCCuCblygk == MCCuCblygk){XacmHSPAZI = true;}
      while(OpWaXlXSmL == OpWaXlXSmL){LYyxZNRMha = true;}
      if(cVuNnELTbY == true){cVuNnELTbY = false;}
      if(DQIZfSzDtz == true){DQIZfSzDtz = false;}
      if(OXGkYaRrbC == true){OXGkYaRrbC = false;}
      if(fMcJipHnHy == true){fMcJipHnHy = false;}
      if(QRVIgxhwuF == true){QRVIgxhwuF = false;}
      if(lUYnxEPKoN == true){lUYnxEPKoN = false;}
      if(lSrYsqnyqo == true){lSrYsqnyqo = false;}
      if(LLuuhwBxDa == true){LLuuhwBxDa = false;}
      if(rUxWQKnnLd == true){rUxWQKnnLd = false;}
      if(axzsMyZxPp == true){axzsMyZxPp = false;}
      if(JiFGsaZcGA == true){JiFGsaZcGA = false;}
      if(DRGNUQVUIh == true){DRGNUQVUIh = false;}
      if(CAlNNOLCij == true){CAlNNOLCij = false;}
      if(WEhNRIPpco == true){WEhNRIPpco = false;}
      if(kLhLZJpkYu == true){kLhLZJpkYu = false;}
      if(bEogmJwqre == true){bEogmJwqre = false;}
      if(PXsVcyirwL == true){PXsVcyirwL = false;}
      if(AeqSxqRamE == true){AeqSxqRamE = false;}
      if(XacmHSPAZI == true){XacmHSPAZI = false;}
      if(LYyxZNRMha == true){LYyxZNRMha = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BIDTVULNUL
{ 
  void GeYPLnrQWX()
  { 
      bool zupBUdnkPE = false;
      bool fyKjXxlPIu = false;
      bool ZgWekUqbeC = false;
      bool xxCNBfwaWR = false;
      bool YRIUssxSre = false;
      bool PlOgSSXKQA = false;
      bool mMFNGiuxhr = false;
      bool BKsqWIYBlq = false;
      bool WYiAlLiUti = false;
      bool HlKWeMLtNK = false;
      bool xAjAcErXJK = false;
      bool tWXYcOcFau = false;
      bool zaCzkPAWLK = false;
      bool wdnbtWniWh = false;
      bool SLKjnkNksQ = false;
      bool iGTRKWxjPN = false;
      bool DVLzNQhweG = false;
      bool ZthrcnPRKA = false;
      bool BOdubpJVRW = false;
      bool YETIexzLWX = false;
      string yoZngDBRBq;
      string MNlsdErYRI;
      string RSROfSfhbD;
      string nxKeYWYjpZ;
      string cfKoaDCMzu;
      string ZDpGofXLIN;
      string WSoxDOCHTG;
      string eIhrekHbmb;
      string PSifdjGEps;
      string zNabCJpMlL;
      string AursQQUxaD;
      string XuXfxDjJTS;
      string IyRaGQgGpV;
      string tupbbUZoPM;
      string PJclUEptdy;
      string YgrSDCcRlz;
      string jOHFIcEuEc;
      string dtsHDzVeGB;
      string albqwMCXYZ;
      string qIDQbBBXcr;
      if(yoZngDBRBq == AursQQUxaD){zupBUdnkPE = true;}
      else if(AursQQUxaD == yoZngDBRBq){xAjAcErXJK = true;}
      if(MNlsdErYRI == XuXfxDjJTS){fyKjXxlPIu = true;}
      else if(XuXfxDjJTS == MNlsdErYRI){tWXYcOcFau = true;}
      if(RSROfSfhbD == IyRaGQgGpV){ZgWekUqbeC = true;}
      else if(IyRaGQgGpV == RSROfSfhbD){zaCzkPAWLK = true;}
      if(nxKeYWYjpZ == tupbbUZoPM){xxCNBfwaWR = true;}
      else if(tupbbUZoPM == nxKeYWYjpZ){wdnbtWniWh = true;}
      if(cfKoaDCMzu == PJclUEptdy){YRIUssxSre = true;}
      else if(PJclUEptdy == cfKoaDCMzu){SLKjnkNksQ = true;}
      if(ZDpGofXLIN == YgrSDCcRlz){PlOgSSXKQA = true;}
      else if(YgrSDCcRlz == ZDpGofXLIN){iGTRKWxjPN = true;}
      if(WSoxDOCHTG == jOHFIcEuEc){mMFNGiuxhr = true;}
      else if(jOHFIcEuEc == WSoxDOCHTG){DVLzNQhweG = true;}
      if(eIhrekHbmb == dtsHDzVeGB){BKsqWIYBlq = true;}
      if(PSifdjGEps == albqwMCXYZ){WYiAlLiUti = true;}
      if(zNabCJpMlL == qIDQbBBXcr){HlKWeMLtNK = true;}
      while(dtsHDzVeGB == eIhrekHbmb){ZthrcnPRKA = true;}
      while(albqwMCXYZ == albqwMCXYZ){BOdubpJVRW = true;}
      while(qIDQbBBXcr == qIDQbBBXcr){YETIexzLWX = true;}
      if(zupBUdnkPE == true){zupBUdnkPE = false;}
      if(fyKjXxlPIu == true){fyKjXxlPIu = false;}
      if(ZgWekUqbeC == true){ZgWekUqbeC = false;}
      if(xxCNBfwaWR == true){xxCNBfwaWR = false;}
      if(YRIUssxSre == true){YRIUssxSre = false;}
      if(PlOgSSXKQA == true){PlOgSSXKQA = false;}
      if(mMFNGiuxhr == true){mMFNGiuxhr = false;}
      if(BKsqWIYBlq == true){BKsqWIYBlq = false;}
      if(WYiAlLiUti == true){WYiAlLiUti = false;}
      if(HlKWeMLtNK == true){HlKWeMLtNK = false;}
      if(xAjAcErXJK == true){xAjAcErXJK = false;}
      if(tWXYcOcFau == true){tWXYcOcFau = false;}
      if(zaCzkPAWLK == true){zaCzkPAWLK = false;}
      if(wdnbtWniWh == true){wdnbtWniWh = false;}
      if(SLKjnkNksQ == true){SLKjnkNksQ = false;}
      if(iGTRKWxjPN == true){iGTRKWxjPN = false;}
      if(DVLzNQhweG == true){DVLzNQhweG = false;}
      if(ZthrcnPRKA == true){ZthrcnPRKA = false;}
      if(BOdubpJVRW == true){BOdubpJVRW = false;}
      if(YETIexzLWX == true){YETIexzLWX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNLVDXTDVN
{ 
  void gmuYFYdyuS()
  { 
      bool mEzRVaKtwB = false;
      bool IRNffHpCGW = false;
      bool pryBtSVEXk = false;
      bool mpMnJIiMjk = false;
      bool wOgPiQDAFA = false;
      bool hcyJVuFyWD = false;
      bool EFWKOSEZVX = false;
      bool YdSUaaLiRd = false;
      bool PVzWDJqDSO = false;
      bool CkpffpqVAQ = false;
      bool LcdgbEKdht = false;
      bool iVfsniGAHE = false;
      bool aAHHUnnlnk = false;
      bool joiBSlqRuz = false;
      bool zNVXegExrx = false;
      bool iqOuoLVWMn = false;
      bool QXowKsleZB = false;
      bool qnFHENdibn = false;
      bool iqtqBramLG = false;
      bool PTFGibYYNk = false;
      string NAOoFzHHna;
      string bUPZhjymSf;
      string aoBCjZgAhs;
      string eLWOTMhnwl;
      string ywzHpTQdFc;
      string cnBpRYzMFe;
      string RHZtwPyBFU;
      string CKqggeotLQ;
      string IDtEQqJfxt;
      string NUhQTqWEKa;
      string UPYjZRwUIl;
      string jEAoVOMUdE;
      string GREKGgbZMp;
      string IjikuseJdy;
      string tnWKKJUsuF;
      string dBaGTDLNds;
      string pVISdzVPsc;
      string iCpfJRtszx;
      string MheGMGJcQr;
      string hQfkIYeEfL;
      if(NAOoFzHHna == UPYjZRwUIl){mEzRVaKtwB = true;}
      else if(UPYjZRwUIl == NAOoFzHHna){LcdgbEKdht = true;}
      if(bUPZhjymSf == jEAoVOMUdE){IRNffHpCGW = true;}
      else if(jEAoVOMUdE == bUPZhjymSf){iVfsniGAHE = true;}
      if(aoBCjZgAhs == GREKGgbZMp){pryBtSVEXk = true;}
      else if(GREKGgbZMp == aoBCjZgAhs){aAHHUnnlnk = true;}
      if(eLWOTMhnwl == IjikuseJdy){mpMnJIiMjk = true;}
      else if(IjikuseJdy == eLWOTMhnwl){joiBSlqRuz = true;}
      if(ywzHpTQdFc == tnWKKJUsuF){wOgPiQDAFA = true;}
      else if(tnWKKJUsuF == ywzHpTQdFc){zNVXegExrx = true;}
      if(cnBpRYzMFe == dBaGTDLNds){hcyJVuFyWD = true;}
      else if(dBaGTDLNds == cnBpRYzMFe){iqOuoLVWMn = true;}
      if(RHZtwPyBFU == pVISdzVPsc){EFWKOSEZVX = true;}
      else if(pVISdzVPsc == RHZtwPyBFU){QXowKsleZB = true;}
      if(CKqggeotLQ == iCpfJRtszx){YdSUaaLiRd = true;}
      if(IDtEQqJfxt == MheGMGJcQr){PVzWDJqDSO = true;}
      if(NUhQTqWEKa == hQfkIYeEfL){CkpffpqVAQ = true;}
      while(iCpfJRtszx == CKqggeotLQ){qnFHENdibn = true;}
      while(MheGMGJcQr == MheGMGJcQr){iqtqBramLG = true;}
      while(hQfkIYeEfL == hQfkIYeEfL){PTFGibYYNk = true;}
      if(mEzRVaKtwB == true){mEzRVaKtwB = false;}
      if(IRNffHpCGW == true){IRNffHpCGW = false;}
      if(pryBtSVEXk == true){pryBtSVEXk = false;}
      if(mpMnJIiMjk == true){mpMnJIiMjk = false;}
      if(wOgPiQDAFA == true){wOgPiQDAFA = false;}
      if(hcyJVuFyWD == true){hcyJVuFyWD = false;}
      if(EFWKOSEZVX == true){EFWKOSEZVX = false;}
      if(YdSUaaLiRd == true){YdSUaaLiRd = false;}
      if(PVzWDJqDSO == true){PVzWDJqDSO = false;}
      if(CkpffpqVAQ == true){CkpffpqVAQ = false;}
      if(LcdgbEKdht == true){LcdgbEKdht = false;}
      if(iVfsniGAHE == true){iVfsniGAHE = false;}
      if(aAHHUnnlnk == true){aAHHUnnlnk = false;}
      if(joiBSlqRuz == true){joiBSlqRuz = false;}
      if(zNVXegExrx == true){zNVXegExrx = false;}
      if(iqOuoLVWMn == true){iqOuoLVWMn = false;}
      if(QXowKsleZB == true){QXowKsleZB = false;}
      if(qnFHENdibn == true){qnFHENdibn = false;}
      if(iqtqBramLG == true){iqtqBramLG = false;}
      if(PTFGibYYNk == true){PTFGibYYNk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFBVILTTIS
{ 
  void nLeeNHeALs()
  { 
      bool DlPWIACMMw = false;
      bool slzsLBmoFc = false;
      bool JrDGBCRDWF = false;
      bool ZqtqBNnPHE = false;
      bool LWCfSlqIzk = false;
      bool wONSQLiJUF = false;
      bool iypGVCqIry = false;
      bool NWgAQmpWnP = false;
      bool LJDlJKdbZo = false;
      bool detBVMfuJP = false;
      bool thPBWYhMBd = false;
      bool ULVFtYuExL = false;
      bool YPiCTiceeD = false;
      bool GtNXUcsBOk = false;
      bool cQZuURInHw = false;
      bool RbyyqdzMgn = false;
      bool uChxXayxkQ = false;
      bool etoLhHpmhC = false;
      bool ZnWhlduPfq = false;
      bool dfTaoaibXs = false;
      string ZSuyhwNkZp;
      string rWCNWSQEpq;
      string VsewFBedyk;
      string aYSNDWzKBU;
      string ZoNOgwtQNx;
      string yKrCDgnyrf;
      string QjlnOSEnKz;
      string SFDVQgfPPJ;
      string GOPBlQfPKW;
      string iASUDpCYzN;
      string rGFOdsHWlW;
      string BXhiZCUkCy;
      string mndnPSmhRa;
      string eGQCQAIAWr;
      string IIdmVLSiuB;
      string UQWBZEbRyL;
      string GZFKqtHfSY;
      string sTOJodKpRE;
      string AElPFOjObM;
      string XpCLliDSwa;
      if(ZSuyhwNkZp == rGFOdsHWlW){DlPWIACMMw = true;}
      else if(rGFOdsHWlW == ZSuyhwNkZp){thPBWYhMBd = true;}
      if(rWCNWSQEpq == BXhiZCUkCy){slzsLBmoFc = true;}
      else if(BXhiZCUkCy == rWCNWSQEpq){ULVFtYuExL = true;}
      if(VsewFBedyk == mndnPSmhRa){JrDGBCRDWF = true;}
      else if(mndnPSmhRa == VsewFBedyk){YPiCTiceeD = true;}
      if(aYSNDWzKBU == eGQCQAIAWr){ZqtqBNnPHE = true;}
      else if(eGQCQAIAWr == aYSNDWzKBU){GtNXUcsBOk = true;}
      if(ZoNOgwtQNx == IIdmVLSiuB){LWCfSlqIzk = true;}
      else if(IIdmVLSiuB == ZoNOgwtQNx){cQZuURInHw = true;}
      if(yKrCDgnyrf == UQWBZEbRyL){wONSQLiJUF = true;}
      else if(UQWBZEbRyL == yKrCDgnyrf){RbyyqdzMgn = true;}
      if(QjlnOSEnKz == GZFKqtHfSY){iypGVCqIry = true;}
      else if(GZFKqtHfSY == QjlnOSEnKz){uChxXayxkQ = true;}
      if(SFDVQgfPPJ == sTOJodKpRE){NWgAQmpWnP = true;}
      if(GOPBlQfPKW == AElPFOjObM){LJDlJKdbZo = true;}
      if(iASUDpCYzN == XpCLliDSwa){detBVMfuJP = true;}
      while(sTOJodKpRE == SFDVQgfPPJ){etoLhHpmhC = true;}
      while(AElPFOjObM == AElPFOjObM){ZnWhlduPfq = true;}
      while(XpCLliDSwa == XpCLliDSwa){dfTaoaibXs = true;}
      if(DlPWIACMMw == true){DlPWIACMMw = false;}
      if(slzsLBmoFc == true){slzsLBmoFc = false;}
      if(JrDGBCRDWF == true){JrDGBCRDWF = false;}
      if(ZqtqBNnPHE == true){ZqtqBNnPHE = false;}
      if(LWCfSlqIzk == true){LWCfSlqIzk = false;}
      if(wONSQLiJUF == true){wONSQLiJUF = false;}
      if(iypGVCqIry == true){iypGVCqIry = false;}
      if(NWgAQmpWnP == true){NWgAQmpWnP = false;}
      if(LJDlJKdbZo == true){LJDlJKdbZo = false;}
      if(detBVMfuJP == true){detBVMfuJP = false;}
      if(thPBWYhMBd == true){thPBWYhMBd = false;}
      if(ULVFtYuExL == true){ULVFtYuExL = false;}
      if(YPiCTiceeD == true){YPiCTiceeD = false;}
      if(GtNXUcsBOk == true){GtNXUcsBOk = false;}
      if(cQZuURInHw == true){cQZuURInHw = false;}
      if(RbyyqdzMgn == true){RbyyqdzMgn = false;}
      if(uChxXayxkQ == true){uChxXayxkQ = false;}
      if(etoLhHpmhC == true){etoLhHpmhC = false;}
      if(ZnWhlduPfq == true){ZnWhlduPfq = false;}
      if(dfTaoaibXs == true){dfTaoaibXs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TZPMYDMUEC
{ 
  void nLYiUcAwwb()
  { 
      bool MPCNwdaGQL = false;
      bool eCgBhsHYrT = false;
      bool cmCbPPQAzJ = false;
      bool cQeYJsWaOQ = false;
      bool iCNCkdMsXg = false;
      bool DJDZHYMZyf = false;
      bool MaHHhOWHro = false;
      bool WgKajZZAqk = false;
      bool CXcRGTNFRk = false;
      bool fwbhDIuGTV = false;
      bool HFBhJWzbog = false;
      bool yMiNcoxoAO = false;
      bool BRoHJaEbWb = false;
      bool eSgUdxWtIi = false;
      bool TkPklSMOEO = false;
      bool KFFEUoPsYi = false;
      bool SWENBefNif = false;
      bool SDfRtPBEUp = false;
      bool NoWIRYNbzn = false;
      bool gcUZQxfCiG = false;
      string BwemcGAMey;
      string mxbmuuEOUy;
      string oleoqsEegg;
      string PmqmLfWpzC;
      string qOxyBtMxmE;
      string ALSguOQouj;
      string BVfyhzGobP;
      string XOORHZngmw;
      string fGqcfEUJrw;
      string OhtOAVizPC;
      string nXVXflwBZU;
      string ajBzEteCSc;
      string ewweAoTzQl;
      string qoQkHIkSws;
      string ISjXVeftKF;
      string pgflWqapXq;
      string SwjndkSQrw;
      string JLFZULMYJV;
      string IYoKuJIeNP;
      string gtuFZLiwsj;
      if(BwemcGAMey == nXVXflwBZU){MPCNwdaGQL = true;}
      else if(nXVXflwBZU == BwemcGAMey){HFBhJWzbog = true;}
      if(mxbmuuEOUy == ajBzEteCSc){eCgBhsHYrT = true;}
      else if(ajBzEteCSc == mxbmuuEOUy){yMiNcoxoAO = true;}
      if(oleoqsEegg == ewweAoTzQl){cmCbPPQAzJ = true;}
      else if(ewweAoTzQl == oleoqsEegg){BRoHJaEbWb = true;}
      if(PmqmLfWpzC == qoQkHIkSws){cQeYJsWaOQ = true;}
      else if(qoQkHIkSws == PmqmLfWpzC){eSgUdxWtIi = true;}
      if(qOxyBtMxmE == ISjXVeftKF){iCNCkdMsXg = true;}
      else if(ISjXVeftKF == qOxyBtMxmE){TkPklSMOEO = true;}
      if(ALSguOQouj == pgflWqapXq){DJDZHYMZyf = true;}
      else if(pgflWqapXq == ALSguOQouj){KFFEUoPsYi = true;}
      if(BVfyhzGobP == SwjndkSQrw){MaHHhOWHro = true;}
      else if(SwjndkSQrw == BVfyhzGobP){SWENBefNif = true;}
      if(XOORHZngmw == JLFZULMYJV){WgKajZZAqk = true;}
      if(fGqcfEUJrw == IYoKuJIeNP){CXcRGTNFRk = true;}
      if(OhtOAVizPC == gtuFZLiwsj){fwbhDIuGTV = true;}
      while(JLFZULMYJV == XOORHZngmw){SDfRtPBEUp = true;}
      while(IYoKuJIeNP == IYoKuJIeNP){NoWIRYNbzn = true;}
      while(gtuFZLiwsj == gtuFZLiwsj){gcUZQxfCiG = true;}
      if(MPCNwdaGQL == true){MPCNwdaGQL = false;}
      if(eCgBhsHYrT == true){eCgBhsHYrT = false;}
      if(cmCbPPQAzJ == true){cmCbPPQAzJ = false;}
      if(cQeYJsWaOQ == true){cQeYJsWaOQ = false;}
      if(iCNCkdMsXg == true){iCNCkdMsXg = false;}
      if(DJDZHYMZyf == true){DJDZHYMZyf = false;}
      if(MaHHhOWHro == true){MaHHhOWHro = false;}
      if(WgKajZZAqk == true){WgKajZZAqk = false;}
      if(CXcRGTNFRk == true){CXcRGTNFRk = false;}
      if(fwbhDIuGTV == true){fwbhDIuGTV = false;}
      if(HFBhJWzbog == true){HFBhJWzbog = false;}
      if(yMiNcoxoAO == true){yMiNcoxoAO = false;}
      if(BRoHJaEbWb == true){BRoHJaEbWb = false;}
      if(eSgUdxWtIi == true){eSgUdxWtIi = false;}
      if(TkPklSMOEO == true){TkPklSMOEO = false;}
      if(KFFEUoPsYi == true){KFFEUoPsYi = false;}
      if(SWENBefNif == true){SWENBefNif = false;}
      if(SDfRtPBEUp == true){SDfRtPBEUp = false;}
      if(NoWIRYNbzn == true){NoWIRYNbzn = false;}
      if(gcUZQxfCiG == true){gcUZQxfCiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKIJBRFPCF
{ 
  void uNzCdWAgrX()
  { 
      bool kLAuQGSFtq = false;
      bool BYDukwCjSW = false;
      bool QTAoVrFQxn = false;
      bool NCjnKnbENq = false;
      bool qUPMJedjlZ = false;
      bool HIWmIRLLYY = false;
      bool ACHGdyoPjx = false;
      bool UxVbeuDmep = false;
      bool NVeWfFfxfs = false;
      bool bPfnpoMIiL = false;
      bool pOznEJltHM = false;
      bool NXghKeXjZX = false;
      bool SripUERglp = false;
      bool huETAzVpSW = false;
      bool TkoSfDixdL = false;
      bool QbiKryeJTz = false;
      bool qEIReSTNhL = false;
      bool IhRDEgCQJQ = false;
      bool VUDaYGLtaB = false;
      bool UMWSfOcWnN = false;
      string ThcEurRBtn;
      string FXrToSmqRW;
      string epxPDQYkug;
      string wFKNjghFAh;
      string gJCsHGkeKl;
      string iNRwUdkNBe;
      string SgFNqzNejH;
      string jgqioVnEIx;
      string etZJxhnNrF;
      string wUEVOzDnBH;
      string rGuDBBWhGz;
      string pgEEzYHwPI;
      string LzmdLPcUUp;
      string RzCAEYzWIu;
      string LFGrPPPAVp;
      string rGYrwsTRqk;
      string YBNQhpdDza;
      string ZknTxFrtNw;
      string zbzdxKZKDK;
      string EheWWJrpKY;
      if(ThcEurRBtn == rGuDBBWhGz){kLAuQGSFtq = true;}
      else if(rGuDBBWhGz == ThcEurRBtn){pOznEJltHM = true;}
      if(FXrToSmqRW == pgEEzYHwPI){BYDukwCjSW = true;}
      else if(pgEEzYHwPI == FXrToSmqRW){NXghKeXjZX = true;}
      if(epxPDQYkug == LzmdLPcUUp){QTAoVrFQxn = true;}
      else if(LzmdLPcUUp == epxPDQYkug){SripUERglp = true;}
      if(wFKNjghFAh == RzCAEYzWIu){NCjnKnbENq = true;}
      else if(RzCAEYzWIu == wFKNjghFAh){huETAzVpSW = true;}
      if(gJCsHGkeKl == LFGrPPPAVp){qUPMJedjlZ = true;}
      else if(LFGrPPPAVp == gJCsHGkeKl){TkoSfDixdL = true;}
      if(iNRwUdkNBe == rGYrwsTRqk){HIWmIRLLYY = true;}
      else if(rGYrwsTRqk == iNRwUdkNBe){QbiKryeJTz = true;}
      if(SgFNqzNejH == YBNQhpdDza){ACHGdyoPjx = true;}
      else if(YBNQhpdDza == SgFNqzNejH){qEIReSTNhL = true;}
      if(jgqioVnEIx == ZknTxFrtNw){UxVbeuDmep = true;}
      if(etZJxhnNrF == zbzdxKZKDK){NVeWfFfxfs = true;}
      if(wUEVOzDnBH == EheWWJrpKY){bPfnpoMIiL = true;}
      while(ZknTxFrtNw == jgqioVnEIx){IhRDEgCQJQ = true;}
      while(zbzdxKZKDK == zbzdxKZKDK){VUDaYGLtaB = true;}
      while(EheWWJrpKY == EheWWJrpKY){UMWSfOcWnN = true;}
      if(kLAuQGSFtq == true){kLAuQGSFtq = false;}
      if(BYDukwCjSW == true){BYDukwCjSW = false;}
      if(QTAoVrFQxn == true){QTAoVrFQxn = false;}
      if(NCjnKnbENq == true){NCjnKnbENq = false;}
      if(qUPMJedjlZ == true){qUPMJedjlZ = false;}
      if(HIWmIRLLYY == true){HIWmIRLLYY = false;}
      if(ACHGdyoPjx == true){ACHGdyoPjx = false;}
      if(UxVbeuDmep == true){UxVbeuDmep = false;}
      if(NVeWfFfxfs == true){NVeWfFfxfs = false;}
      if(bPfnpoMIiL == true){bPfnpoMIiL = false;}
      if(pOznEJltHM == true){pOznEJltHM = false;}
      if(NXghKeXjZX == true){NXghKeXjZX = false;}
      if(SripUERglp == true){SripUERglp = false;}
      if(huETAzVpSW == true){huETAzVpSW = false;}
      if(TkoSfDixdL == true){TkoSfDixdL = false;}
      if(QbiKryeJTz == true){QbiKryeJTz = false;}
      if(qEIReSTNhL == true){qEIReSTNhL = false;}
      if(IhRDEgCQJQ == true){IhRDEgCQJQ = false;}
      if(VUDaYGLtaB == true){VUDaYGLtaB = false;}
      if(UMWSfOcWnN == true){UMWSfOcWnN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAJLQRHQZM
{ 
  void xgCOrVAnQn()
  { 
      bool gRgsLUanOQ = false;
      bool ROpgftVPRs = false;
      bool TPcIDpUfkC = false;
      bool AsatoFmbcf = false;
      bool MQkzdwCACN = false;
      bool eXmXrQoYpV = false;
      bool AuDLPXmurZ = false;
      bool GtllfDdceH = false;
      bool mUdWWbGCCX = false;
      bool QOkHfRMYjF = false;
      bool IGHbHkkBro = false;
      bool mMtiheRgom = false;
      bool RksUJrIeGN = false;
      bool pEsYyfMBPl = false;
      bool qEKMjEUCYA = false;
      bool AfjwmXNmSP = false;
      bool bFudyhSUjB = false;
      bool SQRCwMZfjE = false;
      bool WGFGNKTxla = false;
      bool SZhAJkJfOB = false;
      string sEUiSKZwWz;
      string odtlmAQCbs;
      string kttCVTHcVO;
      string tbrqwoqMlW;
      string IQHQyXCdUw;
      string XiscfzKSMy;
      string DwZHENkCox;
      string IEQEkTmcEx;
      string RdIZqKhPKx;
      string eYznTLpzLj;
      string lznWmTSoqL;
      string MgNOfYnAQt;
      string fVrqSiEbjY;
      string dmRULRoklW;
      string qrXzkxLjHu;
      string XohREPHwDD;
      string OpEShYPsDN;
      string iCOsCmyrGV;
      string XTUoAnFAQu;
      string KshhIAmERL;
      if(sEUiSKZwWz == lznWmTSoqL){gRgsLUanOQ = true;}
      else if(lznWmTSoqL == sEUiSKZwWz){IGHbHkkBro = true;}
      if(odtlmAQCbs == MgNOfYnAQt){ROpgftVPRs = true;}
      else if(MgNOfYnAQt == odtlmAQCbs){mMtiheRgom = true;}
      if(kttCVTHcVO == fVrqSiEbjY){TPcIDpUfkC = true;}
      else if(fVrqSiEbjY == kttCVTHcVO){RksUJrIeGN = true;}
      if(tbrqwoqMlW == dmRULRoklW){AsatoFmbcf = true;}
      else if(dmRULRoklW == tbrqwoqMlW){pEsYyfMBPl = true;}
      if(IQHQyXCdUw == qrXzkxLjHu){MQkzdwCACN = true;}
      else if(qrXzkxLjHu == IQHQyXCdUw){qEKMjEUCYA = true;}
      if(XiscfzKSMy == XohREPHwDD){eXmXrQoYpV = true;}
      else if(XohREPHwDD == XiscfzKSMy){AfjwmXNmSP = true;}
      if(DwZHENkCox == OpEShYPsDN){AuDLPXmurZ = true;}
      else if(OpEShYPsDN == DwZHENkCox){bFudyhSUjB = true;}
      if(IEQEkTmcEx == iCOsCmyrGV){GtllfDdceH = true;}
      if(RdIZqKhPKx == XTUoAnFAQu){mUdWWbGCCX = true;}
      if(eYznTLpzLj == KshhIAmERL){QOkHfRMYjF = true;}
      while(iCOsCmyrGV == IEQEkTmcEx){SQRCwMZfjE = true;}
      while(XTUoAnFAQu == XTUoAnFAQu){WGFGNKTxla = true;}
      while(KshhIAmERL == KshhIAmERL){SZhAJkJfOB = true;}
      if(gRgsLUanOQ == true){gRgsLUanOQ = false;}
      if(ROpgftVPRs == true){ROpgftVPRs = false;}
      if(TPcIDpUfkC == true){TPcIDpUfkC = false;}
      if(AsatoFmbcf == true){AsatoFmbcf = false;}
      if(MQkzdwCACN == true){MQkzdwCACN = false;}
      if(eXmXrQoYpV == true){eXmXrQoYpV = false;}
      if(AuDLPXmurZ == true){AuDLPXmurZ = false;}
      if(GtllfDdceH == true){GtllfDdceH = false;}
      if(mUdWWbGCCX == true){mUdWWbGCCX = false;}
      if(QOkHfRMYjF == true){QOkHfRMYjF = false;}
      if(IGHbHkkBro == true){IGHbHkkBro = false;}
      if(mMtiheRgom == true){mMtiheRgom = false;}
      if(RksUJrIeGN == true){RksUJrIeGN = false;}
      if(pEsYyfMBPl == true){pEsYyfMBPl = false;}
      if(qEKMjEUCYA == true){qEKMjEUCYA = false;}
      if(AfjwmXNmSP == true){AfjwmXNmSP = false;}
      if(bFudyhSUjB == true){bFudyhSUjB = false;}
      if(SQRCwMZfjE == true){SQRCwMZfjE = false;}
      if(WGFGNKTxla == true){WGFGNKTxla = false;}
      if(SZhAJkJfOB == true){SZhAJkJfOB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYWAZSJRMC
{ 
  void njqPLlXxKR()
  { 
      bool acigPlfQcr = false;
      bool qcmwDNzAHu = false;
      bool koPlRYgQli = false;
      bool rdEBTOUDUj = false;
      bool kdBxNjAYWs = false;
      bool uuUAekNwPq = false;
      bool EPetAMXkcn = false;
      bool rweXKHnRXh = false;
      bool XHssmxIEVh = false;
      bool BXmdfUyHxB = false;
      bool LPwiAzPxpX = false;
      bool xuYhSwWlGC = false;
      bool DSOtlTIBqo = false;
      bool JfTWVILKrn = false;
      bool gLOyjFzFKi = false;
      bool yMAuxsABwf = false;
      bool pNFANQbBMJ = false;
      bool kMsRVrEPKf = false;
      bool UDpIpwfYZb = false;
      bool HJNMySGNjS = false;
      string JFWwkIcBGt;
      string cNIxHteJDb;
      string MssXlmlTxT;
      string XbClyOJdfF;
      string MmNnBXIVZG;
      string xKwEaPMyJy;
      string WJDmWALVzs;
      string kAdxOYeEWO;
      string dQsqVMfxLh;
      string CKUgiDjaRA;
      string LmWgVxgzoC;
      string kHbtUGPMQJ;
      string UOJQpZewNK;
      string oEmVCpsMVY;
      string egHJxuhaLc;
      string nWJHfxcFqu;
      string RjkeNfUFqe;
      string MCprdnGASt;
      string rEjkWRtepF;
      string MmVZGuucuQ;
      if(JFWwkIcBGt == LmWgVxgzoC){acigPlfQcr = true;}
      else if(LmWgVxgzoC == JFWwkIcBGt){LPwiAzPxpX = true;}
      if(cNIxHteJDb == kHbtUGPMQJ){qcmwDNzAHu = true;}
      else if(kHbtUGPMQJ == cNIxHteJDb){xuYhSwWlGC = true;}
      if(MssXlmlTxT == UOJQpZewNK){koPlRYgQli = true;}
      else if(UOJQpZewNK == MssXlmlTxT){DSOtlTIBqo = true;}
      if(XbClyOJdfF == oEmVCpsMVY){rdEBTOUDUj = true;}
      else if(oEmVCpsMVY == XbClyOJdfF){JfTWVILKrn = true;}
      if(MmNnBXIVZG == egHJxuhaLc){kdBxNjAYWs = true;}
      else if(egHJxuhaLc == MmNnBXIVZG){gLOyjFzFKi = true;}
      if(xKwEaPMyJy == nWJHfxcFqu){uuUAekNwPq = true;}
      else if(nWJHfxcFqu == xKwEaPMyJy){yMAuxsABwf = true;}
      if(WJDmWALVzs == RjkeNfUFqe){EPetAMXkcn = true;}
      else if(RjkeNfUFqe == WJDmWALVzs){pNFANQbBMJ = true;}
      if(kAdxOYeEWO == MCprdnGASt){rweXKHnRXh = true;}
      if(dQsqVMfxLh == rEjkWRtepF){XHssmxIEVh = true;}
      if(CKUgiDjaRA == MmVZGuucuQ){BXmdfUyHxB = true;}
      while(MCprdnGASt == kAdxOYeEWO){kMsRVrEPKf = true;}
      while(rEjkWRtepF == rEjkWRtepF){UDpIpwfYZb = true;}
      while(MmVZGuucuQ == MmVZGuucuQ){HJNMySGNjS = true;}
      if(acigPlfQcr == true){acigPlfQcr = false;}
      if(qcmwDNzAHu == true){qcmwDNzAHu = false;}
      if(koPlRYgQli == true){koPlRYgQli = false;}
      if(rdEBTOUDUj == true){rdEBTOUDUj = false;}
      if(kdBxNjAYWs == true){kdBxNjAYWs = false;}
      if(uuUAekNwPq == true){uuUAekNwPq = false;}
      if(EPetAMXkcn == true){EPetAMXkcn = false;}
      if(rweXKHnRXh == true){rweXKHnRXh = false;}
      if(XHssmxIEVh == true){XHssmxIEVh = false;}
      if(BXmdfUyHxB == true){BXmdfUyHxB = false;}
      if(LPwiAzPxpX == true){LPwiAzPxpX = false;}
      if(xuYhSwWlGC == true){xuYhSwWlGC = false;}
      if(DSOtlTIBqo == true){DSOtlTIBqo = false;}
      if(JfTWVILKrn == true){JfTWVILKrn = false;}
      if(gLOyjFzFKi == true){gLOyjFzFKi = false;}
      if(yMAuxsABwf == true){yMAuxsABwf = false;}
      if(pNFANQbBMJ == true){pNFANQbBMJ = false;}
      if(kMsRVrEPKf == true){kMsRVrEPKf = false;}
      if(UDpIpwfYZb == true){UDpIpwfYZb = false;}
      if(HJNMySGNjS == true){HJNMySGNjS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLQDABZPPQ
{ 
  void fadWyebhnb()
  { 
      bool pbgWbbHgIn = false;
      bool ieOBdNScEh = false;
      bool HlxFTeHsqC = false;
      bool IALXQuMNJV = false;
      bool uRFKcMkRQs = false;
      bool FuIlLDeaCw = false;
      bool TNoFfhTpjh = false;
      bool BESilpgmcG = false;
      bool spbyxMrZLM = false;
      bool QkLNBhbzet = false;
      bool stgirBbZAV = false;
      bool WryuCdlqIS = false;
      bool pseWRPsFgE = false;
      bool OgHhMzIsGu = false;
      bool kSZppXmPKW = false;
      bool wjqMEzPKQb = false;
      bool IWrwGpjPiD = false;
      bool UrkMhXTngs = false;
      bool ccuKHdoudM = false;
      bool jycemNadiA = false;
      string yMXGpFQPDn;
      string xSkzStyhwt;
      string zoaDzYlfgd;
      string mkYIUcIgPL;
      string oRRnyRYFxj;
      string QnrHSIlUHQ;
      string SjiZBLsbep;
      string kRRkFhWlFg;
      string AghwMysRpL;
      string qnYyrEhrml;
      string XwZHzzWGCk;
      string kzOZPlBlMD;
      string SbkSyxrTrA;
      string zeySIDGaxN;
      string blOFaqYyiG;
      string CwfjTwLHIC;
      string GDOCkGAwRM;
      string eaoyafNfrH;
      string XsjlxDyOyL;
      string rzSuGXXMTT;
      if(yMXGpFQPDn == XwZHzzWGCk){pbgWbbHgIn = true;}
      else if(XwZHzzWGCk == yMXGpFQPDn){stgirBbZAV = true;}
      if(xSkzStyhwt == kzOZPlBlMD){ieOBdNScEh = true;}
      else if(kzOZPlBlMD == xSkzStyhwt){WryuCdlqIS = true;}
      if(zoaDzYlfgd == SbkSyxrTrA){HlxFTeHsqC = true;}
      else if(SbkSyxrTrA == zoaDzYlfgd){pseWRPsFgE = true;}
      if(mkYIUcIgPL == zeySIDGaxN){IALXQuMNJV = true;}
      else if(zeySIDGaxN == mkYIUcIgPL){OgHhMzIsGu = true;}
      if(oRRnyRYFxj == blOFaqYyiG){uRFKcMkRQs = true;}
      else if(blOFaqYyiG == oRRnyRYFxj){kSZppXmPKW = true;}
      if(QnrHSIlUHQ == CwfjTwLHIC){FuIlLDeaCw = true;}
      else if(CwfjTwLHIC == QnrHSIlUHQ){wjqMEzPKQb = true;}
      if(SjiZBLsbep == GDOCkGAwRM){TNoFfhTpjh = true;}
      else if(GDOCkGAwRM == SjiZBLsbep){IWrwGpjPiD = true;}
      if(kRRkFhWlFg == eaoyafNfrH){BESilpgmcG = true;}
      if(AghwMysRpL == XsjlxDyOyL){spbyxMrZLM = true;}
      if(qnYyrEhrml == rzSuGXXMTT){QkLNBhbzet = true;}
      while(eaoyafNfrH == kRRkFhWlFg){UrkMhXTngs = true;}
      while(XsjlxDyOyL == XsjlxDyOyL){ccuKHdoudM = true;}
      while(rzSuGXXMTT == rzSuGXXMTT){jycemNadiA = true;}
      if(pbgWbbHgIn == true){pbgWbbHgIn = false;}
      if(ieOBdNScEh == true){ieOBdNScEh = false;}
      if(HlxFTeHsqC == true){HlxFTeHsqC = false;}
      if(IALXQuMNJV == true){IALXQuMNJV = false;}
      if(uRFKcMkRQs == true){uRFKcMkRQs = false;}
      if(FuIlLDeaCw == true){FuIlLDeaCw = false;}
      if(TNoFfhTpjh == true){TNoFfhTpjh = false;}
      if(BESilpgmcG == true){BESilpgmcG = false;}
      if(spbyxMrZLM == true){spbyxMrZLM = false;}
      if(QkLNBhbzet == true){QkLNBhbzet = false;}
      if(stgirBbZAV == true){stgirBbZAV = false;}
      if(WryuCdlqIS == true){WryuCdlqIS = false;}
      if(pseWRPsFgE == true){pseWRPsFgE = false;}
      if(OgHhMzIsGu == true){OgHhMzIsGu = false;}
      if(kSZppXmPKW == true){kSZppXmPKW = false;}
      if(wjqMEzPKQb == true){wjqMEzPKQb = false;}
      if(IWrwGpjPiD == true){IWrwGpjPiD = false;}
      if(UrkMhXTngs == true){UrkMhXTngs = false;}
      if(ccuKHdoudM == true){ccuKHdoudM = false;}
      if(jycemNadiA == true){jycemNadiA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGFDNUKIFX
{ 
  void uGfsHkWcxX()
  { 
      bool pecVHAywtO = false;
      bool saHzZdSLMH = false;
      bool DElbshbDDw = false;
      bool wjmbbaSYzw = false;
      bool IdTyJmzZxa = false;
      bool xWbyCkrBbZ = false;
      bool YuryRImfWz = false;
      bool KsLPzYknRG = false;
      bool iBFcyZIoZp = false;
      bool hQxZXMkVgB = false;
      bool ATCyPDLMyc = false;
      bool AEjVqXoPzr = false;
      bool AxFfQtwkrl = false;
      bool mPGPGOyHNu = false;
      bool Nupxpdfaiz = false;
      bool WVVnACOVgU = false;
      bool GZUMokxTPb = false;
      bool YhBEdFGHpm = false;
      bool NVCrORsSPD = false;
      bool AbZrnnZdIE = false;
      string hiJznPtPAx;
      string tpicmFqPTW;
      string wFYRigWMNE;
      string qmKCTJeaZd;
      string cIkEhVOQYq;
      string uaNDkbJqPG;
      string sgBuGGefJc;
      string ZPpptnTTiN;
      string RFnVJPZHRq;
      string znKSkuGpya;
      string piHuRekXIw;
      string HoIComsflq;
      string gXORckFXEz;
      string hdVHWhxrEd;
      string dByUiKfIcx;
      string BaDHtSUpSf;
      string ZNSJOdTAeH;
      string oBbHMeYshS;
      string FwtHxHZOND;
      string NHZXEQinFF;
      if(hiJznPtPAx == piHuRekXIw){pecVHAywtO = true;}
      else if(piHuRekXIw == hiJznPtPAx){ATCyPDLMyc = true;}
      if(tpicmFqPTW == HoIComsflq){saHzZdSLMH = true;}
      else if(HoIComsflq == tpicmFqPTW){AEjVqXoPzr = true;}
      if(wFYRigWMNE == gXORckFXEz){DElbshbDDw = true;}
      else if(gXORckFXEz == wFYRigWMNE){AxFfQtwkrl = true;}
      if(qmKCTJeaZd == hdVHWhxrEd){wjmbbaSYzw = true;}
      else if(hdVHWhxrEd == qmKCTJeaZd){mPGPGOyHNu = true;}
      if(cIkEhVOQYq == dByUiKfIcx){IdTyJmzZxa = true;}
      else if(dByUiKfIcx == cIkEhVOQYq){Nupxpdfaiz = true;}
      if(uaNDkbJqPG == BaDHtSUpSf){xWbyCkrBbZ = true;}
      else if(BaDHtSUpSf == uaNDkbJqPG){WVVnACOVgU = true;}
      if(sgBuGGefJc == ZNSJOdTAeH){YuryRImfWz = true;}
      else if(ZNSJOdTAeH == sgBuGGefJc){GZUMokxTPb = true;}
      if(ZPpptnTTiN == oBbHMeYshS){KsLPzYknRG = true;}
      if(RFnVJPZHRq == FwtHxHZOND){iBFcyZIoZp = true;}
      if(znKSkuGpya == NHZXEQinFF){hQxZXMkVgB = true;}
      while(oBbHMeYshS == ZPpptnTTiN){YhBEdFGHpm = true;}
      while(FwtHxHZOND == FwtHxHZOND){NVCrORsSPD = true;}
      while(NHZXEQinFF == NHZXEQinFF){AbZrnnZdIE = true;}
      if(pecVHAywtO == true){pecVHAywtO = false;}
      if(saHzZdSLMH == true){saHzZdSLMH = false;}
      if(DElbshbDDw == true){DElbshbDDw = false;}
      if(wjmbbaSYzw == true){wjmbbaSYzw = false;}
      if(IdTyJmzZxa == true){IdTyJmzZxa = false;}
      if(xWbyCkrBbZ == true){xWbyCkrBbZ = false;}
      if(YuryRImfWz == true){YuryRImfWz = false;}
      if(KsLPzYknRG == true){KsLPzYknRG = false;}
      if(iBFcyZIoZp == true){iBFcyZIoZp = false;}
      if(hQxZXMkVgB == true){hQxZXMkVgB = false;}
      if(ATCyPDLMyc == true){ATCyPDLMyc = false;}
      if(AEjVqXoPzr == true){AEjVqXoPzr = false;}
      if(AxFfQtwkrl == true){AxFfQtwkrl = false;}
      if(mPGPGOyHNu == true){mPGPGOyHNu = false;}
      if(Nupxpdfaiz == true){Nupxpdfaiz = false;}
      if(WVVnACOVgU == true){WVVnACOVgU = false;}
      if(GZUMokxTPb == true){GZUMokxTPb = false;}
      if(YhBEdFGHpm == true){YhBEdFGHpm = false;}
      if(NVCrORsSPD == true){NVCrORsSPD = false;}
      if(AbZrnnZdIE == true){AbZrnnZdIE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWWEZCPLDU
{ 
  void YbRkjqxapW()
  { 
      bool RQfXsJwCXB = false;
      bool tozgQICLGJ = false;
      bool CwuRJWNQLm = false;
      bool NGLwPWubwG = false;
      bool PDYqMZxgck = false;
      bool JSGKAVUONW = false;
      bool uepjnmdCQt = false;
      bool MaPAszWEEj = false;
      bool ZgmZctzAwt = false;
      bool CgNYLjMoCY = false;
      bool utQiYiDGQB = false;
      bool zPJdxNrQGs = false;
      bool ncGWrfNpnJ = false;
      bool mgBfneQEAt = false;
      bool qsiuulWibx = false;
      bool ruiIkSmtqs = false;
      bool UMRHORNdoR = false;
      bool xmQLCutLbF = false;
      bool IdOqQqystV = false;
      bool rWMHYeaafc = false;
      string BzbFLUsZXy;
      string klKrKqMzcU;
      string NbcpVXBFSr;
      string SYYIDtRguw;
      string caXThgtxWV;
      string wDlPcYWkin;
      string TmHfeMNCnP;
      string YeEfqmEJIo;
      string cEiwuOlIfe;
      string XgyHcpSqnU;
      string TrIGwQzFXo;
      string UNbtKPEKjP;
      string ZEVJrrgwDB;
      string TMUmVkubze;
      string PgjpKKEExN;
      string kHHXtOVyOE;
      string jCBWVHrnXY;
      string TbLFAsTfzh;
      string mbzpPLFwsG;
      string PwNttMeNUC;
      if(BzbFLUsZXy == TrIGwQzFXo){RQfXsJwCXB = true;}
      else if(TrIGwQzFXo == BzbFLUsZXy){utQiYiDGQB = true;}
      if(klKrKqMzcU == UNbtKPEKjP){tozgQICLGJ = true;}
      else if(UNbtKPEKjP == klKrKqMzcU){zPJdxNrQGs = true;}
      if(NbcpVXBFSr == ZEVJrrgwDB){CwuRJWNQLm = true;}
      else if(ZEVJrrgwDB == NbcpVXBFSr){ncGWrfNpnJ = true;}
      if(SYYIDtRguw == TMUmVkubze){NGLwPWubwG = true;}
      else if(TMUmVkubze == SYYIDtRguw){mgBfneQEAt = true;}
      if(caXThgtxWV == PgjpKKEExN){PDYqMZxgck = true;}
      else if(PgjpKKEExN == caXThgtxWV){qsiuulWibx = true;}
      if(wDlPcYWkin == kHHXtOVyOE){JSGKAVUONW = true;}
      else if(kHHXtOVyOE == wDlPcYWkin){ruiIkSmtqs = true;}
      if(TmHfeMNCnP == jCBWVHrnXY){uepjnmdCQt = true;}
      else if(jCBWVHrnXY == TmHfeMNCnP){UMRHORNdoR = true;}
      if(YeEfqmEJIo == TbLFAsTfzh){MaPAszWEEj = true;}
      if(cEiwuOlIfe == mbzpPLFwsG){ZgmZctzAwt = true;}
      if(XgyHcpSqnU == PwNttMeNUC){CgNYLjMoCY = true;}
      while(TbLFAsTfzh == YeEfqmEJIo){xmQLCutLbF = true;}
      while(mbzpPLFwsG == mbzpPLFwsG){IdOqQqystV = true;}
      while(PwNttMeNUC == PwNttMeNUC){rWMHYeaafc = true;}
      if(RQfXsJwCXB == true){RQfXsJwCXB = false;}
      if(tozgQICLGJ == true){tozgQICLGJ = false;}
      if(CwuRJWNQLm == true){CwuRJWNQLm = false;}
      if(NGLwPWubwG == true){NGLwPWubwG = false;}
      if(PDYqMZxgck == true){PDYqMZxgck = false;}
      if(JSGKAVUONW == true){JSGKAVUONW = false;}
      if(uepjnmdCQt == true){uepjnmdCQt = false;}
      if(MaPAszWEEj == true){MaPAszWEEj = false;}
      if(ZgmZctzAwt == true){ZgmZctzAwt = false;}
      if(CgNYLjMoCY == true){CgNYLjMoCY = false;}
      if(utQiYiDGQB == true){utQiYiDGQB = false;}
      if(zPJdxNrQGs == true){zPJdxNrQGs = false;}
      if(ncGWrfNpnJ == true){ncGWrfNpnJ = false;}
      if(mgBfneQEAt == true){mgBfneQEAt = false;}
      if(qsiuulWibx == true){qsiuulWibx = false;}
      if(ruiIkSmtqs == true){ruiIkSmtqs = false;}
      if(UMRHORNdoR == true){UMRHORNdoR = false;}
      if(xmQLCutLbF == true){xmQLCutLbF = false;}
      if(IdOqQqystV == true){IdOqQqystV = false;}
      if(rWMHYeaafc == true){rWMHYeaafc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYHPXZXAZT
{ 
  void qwZSfSodhS()
  { 
      bool PCysHsnAnN = false;
      bool BGePmALOLK = false;
      bool SPbPlShZdw = false;
      bool dclPowhInN = false;
      bool LZDqNnpOXR = false;
      bool daJzwzaiGn = false;
      bool KNWriYUPZq = false;
      bool RCZyzrMjBy = false;
      bool cSCLRDSmSp = false;
      bool UzBACxDLIo = false;
      bool SZofzaALzD = false;
      bool lqgILrKKZf = false;
      bool FgwiVSAZwC = false;
      bool oBbLeCdWMq = false;
      bool CHmPDdRsnJ = false;
      bool mskbjldFKg = false;
      bool ZaPxOkPUdI = false;
      bool Onyicxtgfq = false;
      bool AHklOuPzbs = false;
      bool YXLeQbrpAS = false;
      string blGzKmbYzA;
      string depadpLmXC;
      string qreDyLoTWP;
      string RKZULEFaFO;
      string YJbyRsqMWE;
      string aXKHQjGDBz;
      string xIBjiSFVPZ;
      string jjhIcgQgkE;
      string TcwSosARDb;
      string xBZFQQIrOz;
      string nVxxUppBdi;
      string SZSwfULito;
      string SmRmbhJbqL;
      string YYRlQyfzxy;
      string DynUIXidZw;
      string FZxZgADJUl;
      string fNJRKtHgeg;
      string oMkwkTzwdE;
      string zfCuGzarEP;
      string tVeKRooVKO;
      if(blGzKmbYzA == nVxxUppBdi){PCysHsnAnN = true;}
      else if(nVxxUppBdi == blGzKmbYzA){SZofzaALzD = true;}
      if(depadpLmXC == SZSwfULito){BGePmALOLK = true;}
      else if(SZSwfULito == depadpLmXC){lqgILrKKZf = true;}
      if(qreDyLoTWP == SmRmbhJbqL){SPbPlShZdw = true;}
      else if(SmRmbhJbqL == qreDyLoTWP){FgwiVSAZwC = true;}
      if(RKZULEFaFO == YYRlQyfzxy){dclPowhInN = true;}
      else if(YYRlQyfzxy == RKZULEFaFO){oBbLeCdWMq = true;}
      if(YJbyRsqMWE == DynUIXidZw){LZDqNnpOXR = true;}
      else if(DynUIXidZw == YJbyRsqMWE){CHmPDdRsnJ = true;}
      if(aXKHQjGDBz == FZxZgADJUl){daJzwzaiGn = true;}
      else if(FZxZgADJUl == aXKHQjGDBz){mskbjldFKg = true;}
      if(xIBjiSFVPZ == fNJRKtHgeg){KNWriYUPZq = true;}
      else if(fNJRKtHgeg == xIBjiSFVPZ){ZaPxOkPUdI = true;}
      if(jjhIcgQgkE == oMkwkTzwdE){RCZyzrMjBy = true;}
      if(TcwSosARDb == zfCuGzarEP){cSCLRDSmSp = true;}
      if(xBZFQQIrOz == tVeKRooVKO){UzBACxDLIo = true;}
      while(oMkwkTzwdE == jjhIcgQgkE){Onyicxtgfq = true;}
      while(zfCuGzarEP == zfCuGzarEP){AHklOuPzbs = true;}
      while(tVeKRooVKO == tVeKRooVKO){YXLeQbrpAS = true;}
      if(PCysHsnAnN == true){PCysHsnAnN = false;}
      if(BGePmALOLK == true){BGePmALOLK = false;}
      if(SPbPlShZdw == true){SPbPlShZdw = false;}
      if(dclPowhInN == true){dclPowhInN = false;}
      if(LZDqNnpOXR == true){LZDqNnpOXR = false;}
      if(daJzwzaiGn == true){daJzwzaiGn = false;}
      if(KNWriYUPZq == true){KNWriYUPZq = false;}
      if(RCZyzrMjBy == true){RCZyzrMjBy = false;}
      if(cSCLRDSmSp == true){cSCLRDSmSp = false;}
      if(UzBACxDLIo == true){UzBACxDLIo = false;}
      if(SZofzaALzD == true){SZofzaALzD = false;}
      if(lqgILrKKZf == true){lqgILrKKZf = false;}
      if(FgwiVSAZwC == true){FgwiVSAZwC = false;}
      if(oBbLeCdWMq == true){oBbLeCdWMq = false;}
      if(CHmPDdRsnJ == true){CHmPDdRsnJ = false;}
      if(mskbjldFKg == true){mskbjldFKg = false;}
      if(ZaPxOkPUdI == true){ZaPxOkPUdI = false;}
      if(Onyicxtgfq == true){Onyicxtgfq = false;}
      if(AHklOuPzbs == true){AHklOuPzbs = false;}
      if(YXLeQbrpAS == true){YXLeQbrpAS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUFDRSIBWU
{ 
  void GsSmNYojBG()
  { 
      bool YsxcViWxzu = false;
      bool mXrIdVteSy = false;
      bool GaLalJxPpN = false;
      bool SoTgVQgFpo = false;
      bool EJXgNxiGbI = false;
      bool yMHHMygWpM = false;
      bool lHHkcyDLlM = false;
      bool noocswCdMo = false;
      bool ZpngPGhLUX = false;
      bool iKOcCxCmDP = false;
      bool sWTOTIWdOQ = false;
      bool uCJAluTZUW = false;
      bool PrqOddZLau = false;
      bool sPZwwCWZNG = false;
      bool iExDcfBOpH = false;
      bool dcRgABfEjp = false;
      bool iKDSWecMDi = false;
      bool YsMOmLtmlx = false;
      bool bKUSRQxswu = false;
      bool WRoWWYAdgx = false;
      string WRhzSPCnwf;
      string dijqFKtqsm;
      string WugZcQQgBJ;
      string onczskNeML;
      string ttEXpoqWqb;
      string VYrCWbkHVB;
      string zUmmqpGjyT;
      string xOdgrbpJjn;
      string ZspYmPuZcR;
      string AFILMZHRfA;
      string iGYXeHuLJu;
      string kbXhaFdOAa;
      string tfHfTqFSTS;
      string UXciETUSsf;
      string UjQgfXgajH;
      string urRFGDyrDn;
      string BbrpaMyncH;
      string kLUUGKPaAu;
      string JehMXbGXcB;
      string UbOFdrqZGS;
      if(WRhzSPCnwf == iGYXeHuLJu){YsxcViWxzu = true;}
      else if(iGYXeHuLJu == WRhzSPCnwf){sWTOTIWdOQ = true;}
      if(dijqFKtqsm == kbXhaFdOAa){mXrIdVteSy = true;}
      else if(kbXhaFdOAa == dijqFKtqsm){uCJAluTZUW = true;}
      if(WugZcQQgBJ == tfHfTqFSTS){GaLalJxPpN = true;}
      else if(tfHfTqFSTS == WugZcQQgBJ){PrqOddZLau = true;}
      if(onczskNeML == UXciETUSsf){SoTgVQgFpo = true;}
      else if(UXciETUSsf == onczskNeML){sPZwwCWZNG = true;}
      if(ttEXpoqWqb == UjQgfXgajH){EJXgNxiGbI = true;}
      else if(UjQgfXgajH == ttEXpoqWqb){iExDcfBOpH = true;}
      if(VYrCWbkHVB == urRFGDyrDn){yMHHMygWpM = true;}
      else if(urRFGDyrDn == VYrCWbkHVB){dcRgABfEjp = true;}
      if(zUmmqpGjyT == BbrpaMyncH){lHHkcyDLlM = true;}
      else if(BbrpaMyncH == zUmmqpGjyT){iKDSWecMDi = true;}
      if(xOdgrbpJjn == kLUUGKPaAu){noocswCdMo = true;}
      if(ZspYmPuZcR == JehMXbGXcB){ZpngPGhLUX = true;}
      if(AFILMZHRfA == UbOFdrqZGS){iKOcCxCmDP = true;}
      while(kLUUGKPaAu == xOdgrbpJjn){YsMOmLtmlx = true;}
      while(JehMXbGXcB == JehMXbGXcB){bKUSRQxswu = true;}
      while(UbOFdrqZGS == UbOFdrqZGS){WRoWWYAdgx = true;}
      if(YsxcViWxzu == true){YsxcViWxzu = false;}
      if(mXrIdVteSy == true){mXrIdVteSy = false;}
      if(GaLalJxPpN == true){GaLalJxPpN = false;}
      if(SoTgVQgFpo == true){SoTgVQgFpo = false;}
      if(EJXgNxiGbI == true){EJXgNxiGbI = false;}
      if(yMHHMygWpM == true){yMHHMygWpM = false;}
      if(lHHkcyDLlM == true){lHHkcyDLlM = false;}
      if(noocswCdMo == true){noocswCdMo = false;}
      if(ZpngPGhLUX == true){ZpngPGhLUX = false;}
      if(iKOcCxCmDP == true){iKOcCxCmDP = false;}
      if(sWTOTIWdOQ == true){sWTOTIWdOQ = false;}
      if(uCJAluTZUW == true){uCJAluTZUW = false;}
      if(PrqOddZLau == true){PrqOddZLau = false;}
      if(sPZwwCWZNG == true){sPZwwCWZNG = false;}
      if(iExDcfBOpH == true){iExDcfBOpH = false;}
      if(dcRgABfEjp == true){dcRgABfEjp = false;}
      if(iKDSWecMDi == true){iKDSWecMDi = false;}
      if(YsMOmLtmlx == true){YsMOmLtmlx = false;}
      if(bKUSRQxswu == true){bKUSRQxswu = false;}
      if(WRoWWYAdgx == true){WRoWWYAdgx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOBDMKPPHG
{ 
  void QsCkXaAbwT()
  { 
      bool bqwbggLHKX = false;
      bool LRFIIFkJlc = false;
      bool eeYgSNcuGe = false;
      bool frkqrgTZfh = false;
      bool EusxDUfXLE = false;
      bool TgEjnwSOJS = false;
      bool EQBerSgOQa = false;
      bool lKdEXikadx = false;
      bool hEiBLynADu = false;
      bool OEQNcntNFj = false;
      bool nRHkSIDALE = false;
      bool LqkLkAhzTs = false;
      bool efLULgsPaj = false;
      bool oWVsJPwxiC = false;
      bool umoyjXTFcc = false;
      bool FttLFHGmYk = false;
      bool OmZaOnVqCU = false;
      bool DjPQyqqMjn = false;
      bool NnmxetcJnB = false;
      bool JJYxnHNNjw = false;
      string efLdMSmyBp;
      string yIIsUNylDR;
      string nWcAmjhznu;
      string DfdNTwHpPV;
      string zDaIBDOCgw;
      string lqybVHDKpb;
      string jmJFmSeuYY;
      string FHVgSkwUzj;
      string UfSrJLgBqM;
      string swzmlLsUVh;
      string YTcIpdURIk;
      string KhLGGEURwa;
      string lcDMeJIhuG;
      string rbzRKBDKBf;
      string qOsGBKkrfh;
      string qaYtuuPQcg;
      string VlWBsiitwE;
      string AJPQjXjxKT;
      string XPBMPQDEVO;
      string llgUJEqqMS;
      if(efLdMSmyBp == YTcIpdURIk){bqwbggLHKX = true;}
      else if(YTcIpdURIk == efLdMSmyBp){nRHkSIDALE = true;}
      if(yIIsUNylDR == KhLGGEURwa){LRFIIFkJlc = true;}
      else if(KhLGGEURwa == yIIsUNylDR){LqkLkAhzTs = true;}
      if(nWcAmjhznu == lcDMeJIhuG){eeYgSNcuGe = true;}
      else if(lcDMeJIhuG == nWcAmjhznu){efLULgsPaj = true;}
      if(DfdNTwHpPV == rbzRKBDKBf){frkqrgTZfh = true;}
      else if(rbzRKBDKBf == DfdNTwHpPV){oWVsJPwxiC = true;}
      if(zDaIBDOCgw == qOsGBKkrfh){EusxDUfXLE = true;}
      else if(qOsGBKkrfh == zDaIBDOCgw){umoyjXTFcc = true;}
      if(lqybVHDKpb == qaYtuuPQcg){TgEjnwSOJS = true;}
      else if(qaYtuuPQcg == lqybVHDKpb){FttLFHGmYk = true;}
      if(jmJFmSeuYY == VlWBsiitwE){EQBerSgOQa = true;}
      else if(VlWBsiitwE == jmJFmSeuYY){OmZaOnVqCU = true;}
      if(FHVgSkwUzj == AJPQjXjxKT){lKdEXikadx = true;}
      if(UfSrJLgBqM == XPBMPQDEVO){hEiBLynADu = true;}
      if(swzmlLsUVh == llgUJEqqMS){OEQNcntNFj = true;}
      while(AJPQjXjxKT == FHVgSkwUzj){DjPQyqqMjn = true;}
      while(XPBMPQDEVO == XPBMPQDEVO){NnmxetcJnB = true;}
      while(llgUJEqqMS == llgUJEqqMS){JJYxnHNNjw = true;}
      if(bqwbggLHKX == true){bqwbggLHKX = false;}
      if(LRFIIFkJlc == true){LRFIIFkJlc = false;}
      if(eeYgSNcuGe == true){eeYgSNcuGe = false;}
      if(frkqrgTZfh == true){frkqrgTZfh = false;}
      if(EusxDUfXLE == true){EusxDUfXLE = false;}
      if(TgEjnwSOJS == true){TgEjnwSOJS = false;}
      if(EQBerSgOQa == true){EQBerSgOQa = false;}
      if(lKdEXikadx == true){lKdEXikadx = false;}
      if(hEiBLynADu == true){hEiBLynADu = false;}
      if(OEQNcntNFj == true){OEQNcntNFj = false;}
      if(nRHkSIDALE == true){nRHkSIDALE = false;}
      if(LqkLkAhzTs == true){LqkLkAhzTs = false;}
      if(efLULgsPaj == true){efLULgsPaj = false;}
      if(oWVsJPwxiC == true){oWVsJPwxiC = false;}
      if(umoyjXTFcc == true){umoyjXTFcc = false;}
      if(FttLFHGmYk == true){FttLFHGmYk = false;}
      if(OmZaOnVqCU == true){OmZaOnVqCU = false;}
      if(DjPQyqqMjn == true){DjPQyqqMjn = false;}
      if(NnmxetcJnB == true){NnmxetcJnB = false;}
      if(JJYxnHNNjw == true){JJYxnHNNjw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBNPFLXKKF
{ 
  void njYpMBUcDP()
  { 
      bool TBupoAHbSb = false;
      bool bpmcEkVaJl = false;
      bool hVnrRkeSty = false;
      bool ZZXSWwMlcU = false;
      bool dizbtoOyMN = false;
      bool MgksHyMDYE = false;
      bool VogUBBSTFI = false;
      bool YjynIzVMxb = false;
      bool VgFgksndLY = false;
      bool iJNXznBeZr = false;
      bool WurEnchwkH = false;
      bool czFwioiAiI = false;
      bool MnHgYPVaoT = false;
      bool xpmEFZnBrI = false;
      bool KrsDujDRnK = false;
      bool FBwRfimKeY = false;
      bool GHHRKmMAqI = false;
      bool AhHaxUtDko = false;
      bool MEldNutVYV = false;
      bool mcVTBDjasI = false;
      string KFwmfBVUWG;
      string MIngbMDqsL;
      string qrMeohdDBe;
      string slcedKTqLk;
      string aQBcUaIqlm;
      string YwwsbSsRxy;
      string WSSrMZfJDR;
      string sMfIkaqjJO;
      string ZlQNFxpiDK;
      string RBsNNIxIPu;
      string tznUtMQnIA;
      string bIHiXkBEmO;
      string jwFrAqSRtb;
      string dhTOTZyuTs;
      string gBaCiItKoc;
      string GrVAKxswUC;
      string sysfWtnrOy;
      string mFjtghVDIq;
      string xIcRVkLSDW;
      string fCaRziHueo;
      if(KFwmfBVUWG == tznUtMQnIA){TBupoAHbSb = true;}
      else if(tznUtMQnIA == KFwmfBVUWG){WurEnchwkH = true;}
      if(MIngbMDqsL == bIHiXkBEmO){bpmcEkVaJl = true;}
      else if(bIHiXkBEmO == MIngbMDqsL){czFwioiAiI = true;}
      if(qrMeohdDBe == jwFrAqSRtb){hVnrRkeSty = true;}
      else if(jwFrAqSRtb == qrMeohdDBe){MnHgYPVaoT = true;}
      if(slcedKTqLk == dhTOTZyuTs){ZZXSWwMlcU = true;}
      else if(dhTOTZyuTs == slcedKTqLk){xpmEFZnBrI = true;}
      if(aQBcUaIqlm == gBaCiItKoc){dizbtoOyMN = true;}
      else if(gBaCiItKoc == aQBcUaIqlm){KrsDujDRnK = true;}
      if(YwwsbSsRxy == GrVAKxswUC){MgksHyMDYE = true;}
      else if(GrVAKxswUC == YwwsbSsRxy){FBwRfimKeY = true;}
      if(WSSrMZfJDR == sysfWtnrOy){VogUBBSTFI = true;}
      else if(sysfWtnrOy == WSSrMZfJDR){GHHRKmMAqI = true;}
      if(sMfIkaqjJO == mFjtghVDIq){YjynIzVMxb = true;}
      if(ZlQNFxpiDK == xIcRVkLSDW){VgFgksndLY = true;}
      if(RBsNNIxIPu == fCaRziHueo){iJNXznBeZr = true;}
      while(mFjtghVDIq == sMfIkaqjJO){AhHaxUtDko = true;}
      while(xIcRVkLSDW == xIcRVkLSDW){MEldNutVYV = true;}
      while(fCaRziHueo == fCaRziHueo){mcVTBDjasI = true;}
      if(TBupoAHbSb == true){TBupoAHbSb = false;}
      if(bpmcEkVaJl == true){bpmcEkVaJl = false;}
      if(hVnrRkeSty == true){hVnrRkeSty = false;}
      if(ZZXSWwMlcU == true){ZZXSWwMlcU = false;}
      if(dizbtoOyMN == true){dizbtoOyMN = false;}
      if(MgksHyMDYE == true){MgksHyMDYE = false;}
      if(VogUBBSTFI == true){VogUBBSTFI = false;}
      if(YjynIzVMxb == true){YjynIzVMxb = false;}
      if(VgFgksndLY == true){VgFgksndLY = false;}
      if(iJNXznBeZr == true){iJNXznBeZr = false;}
      if(WurEnchwkH == true){WurEnchwkH = false;}
      if(czFwioiAiI == true){czFwioiAiI = false;}
      if(MnHgYPVaoT == true){MnHgYPVaoT = false;}
      if(xpmEFZnBrI == true){xpmEFZnBrI = false;}
      if(KrsDujDRnK == true){KrsDujDRnK = false;}
      if(FBwRfimKeY == true){FBwRfimKeY = false;}
      if(GHHRKmMAqI == true){GHHRKmMAqI = false;}
      if(AhHaxUtDko == true){AhHaxUtDko = false;}
      if(MEldNutVYV == true){MEldNutVYV = false;}
      if(mcVTBDjasI == true){mcVTBDjasI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCGWIJOEHW
{ 
  void AMuKwwLIDV()
  { 
      bool FGwSJUWiDo = false;
      bool LsQknfFrjQ = false;
      bool PVFkqaQMGT = false;
      bool AnWHLiPjgt = false;
      bool GxrMOxGymT = false;
      bool OLobCjBKah = false;
      bool DJbjnXWIZF = false;
      bool PULpJScrVs = false;
      bool TSYmEozuFa = false;
      bool hEIyqxUIYq = false;
      bool ayXhDsAzRj = false;
      bool HJogNjjnez = false;
      bool YbDyXLLMyM = false;
      bool xUSeSVtqiL = false;
      bool nzcUTXPajG = false;
      bool MgcZSztZKr = false;
      bool gnAElmpJOr = false;
      bool osETKYyhez = false;
      bool ujbrAQqsMT = false;
      bool aUfqdAzXig = false;
      string aHQDqLMbJl;
      string figdAWpKzU;
      string ozFfZyBsqH;
      string iTlFHfCzZf;
      string bqpKxKmENC;
      string DuAbhaBkcr;
      string KSjCDLxaWU;
      string UqjTrxJuhP;
      string LxfnEmTJXf;
      string dQVgUIHnHl;
      string NLhshMKgjj;
      string RGDNgNmuyP;
      string rmDppDUCyj;
      string oVnwBzOmGq;
      string bmZmOXNIAH;
      string ULoqtZIqDd;
      string rIhztwRHMh;
      string yAoGmENPaR;
      string pLCpOdfwCa;
      string pWibzTEZrS;
      if(aHQDqLMbJl == NLhshMKgjj){FGwSJUWiDo = true;}
      else if(NLhshMKgjj == aHQDqLMbJl){ayXhDsAzRj = true;}
      if(figdAWpKzU == RGDNgNmuyP){LsQknfFrjQ = true;}
      else if(RGDNgNmuyP == figdAWpKzU){HJogNjjnez = true;}
      if(ozFfZyBsqH == rmDppDUCyj){PVFkqaQMGT = true;}
      else if(rmDppDUCyj == ozFfZyBsqH){YbDyXLLMyM = true;}
      if(iTlFHfCzZf == oVnwBzOmGq){AnWHLiPjgt = true;}
      else if(oVnwBzOmGq == iTlFHfCzZf){xUSeSVtqiL = true;}
      if(bqpKxKmENC == bmZmOXNIAH){GxrMOxGymT = true;}
      else if(bmZmOXNIAH == bqpKxKmENC){nzcUTXPajG = true;}
      if(DuAbhaBkcr == ULoqtZIqDd){OLobCjBKah = true;}
      else if(ULoqtZIqDd == DuAbhaBkcr){MgcZSztZKr = true;}
      if(KSjCDLxaWU == rIhztwRHMh){DJbjnXWIZF = true;}
      else if(rIhztwRHMh == KSjCDLxaWU){gnAElmpJOr = true;}
      if(UqjTrxJuhP == yAoGmENPaR){PULpJScrVs = true;}
      if(LxfnEmTJXf == pLCpOdfwCa){TSYmEozuFa = true;}
      if(dQVgUIHnHl == pWibzTEZrS){hEIyqxUIYq = true;}
      while(yAoGmENPaR == UqjTrxJuhP){osETKYyhez = true;}
      while(pLCpOdfwCa == pLCpOdfwCa){ujbrAQqsMT = true;}
      while(pWibzTEZrS == pWibzTEZrS){aUfqdAzXig = true;}
      if(FGwSJUWiDo == true){FGwSJUWiDo = false;}
      if(LsQknfFrjQ == true){LsQknfFrjQ = false;}
      if(PVFkqaQMGT == true){PVFkqaQMGT = false;}
      if(AnWHLiPjgt == true){AnWHLiPjgt = false;}
      if(GxrMOxGymT == true){GxrMOxGymT = false;}
      if(OLobCjBKah == true){OLobCjBKah = false;}
      if(DJbjnXWIZF == true){DJbjnXWIZF = false;}
      if(PULpJScrVs == true){PULpJScrVs = false;}
      if(TSYmEozuFa == true){TSYmEozuFa = false;}
      if(hEIyqxUIYq == true){hEIyqxUIYq = false;}
      if(ayXhDsAzRj == true){ayXhDsAzRj = false;}
      if(HJogNjjnez == true){HJogNjjnez = false;}
      if(YbDyXLLMyM == true){YbDyXLLMyM = false;}
      if(xUSeSVtqiL == true){xUSeSVtqiL = false;}
      if(nzcUTXPajG == true){nzcUTXPajG = false;}
      if(MgcZSztZKr == true){MgcZSztZKr = false;}
      if(gnAElmpJOr == true){gnAElmpJOr = false;}
      if(osETKYyhez == true){osETKYyhez = false;}
      if(ujbrAQqsMT == true){ujbrAQqsMT = false;}
      if(aUfqdAzXig == true){aUfqdAzXig = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQJOHHMDYE
{ 
  void fCJNIxAYLV()
  { 
      bool ifWhVUtzbf = false;
      bool BsDFrXFRKn = false;
      bool cuqNNzqZhq = false;
      bool SujPcBSZgE = false;
      bool tsNWnzTbVe = false;
      bool aTajImoJTV = false;
      bool cURkMGInbq = false;
      bool EekFsigTYO = false;
      bool eODCPyTzHo = false;
      bool MJFKaZbcJh = false;
      bool pfzeawhUqY = false;
      bool GUjFpNQOUO = false;
      bool lJflduYaeT = false;
      bool HEJqXzPYbT = false;
      bool PyIiiqYATM = false;
      bool IMHuwgAMAe = false;
      bool WHpWQBLrgq = false;
      bool yrmBymBxDm = false;
      bool WYHRKuxNuq = false;
      bool zCXxxIIkRg = false;
      string PqcJsCsFiZ;
      string JkxlNjFhTV;
      string hyDNXjOXLn;
      string AaJiXjWnxf;
      string lCgrdMbZar;
      string tuDlfQmPlI;
      string nUstYhaOOc;
      string MRkmjfQKiK;
      string InxSsFWXCG;
      string wGBnrQIlTu;
      string lNLyfcKPCA;
      string AbgbAzXaBS;
      string LCLHfGPwuS;
      string WdqmYtbzmP;
      string uGVCGTZZnr;
      string shkAjiCERY;
      string MNUjcVksDF;
      string WYmkXEgIAL;
      string goICYospCo;
      string rXgNCgllYk;
      if(PqcJsCsFiZ == lNLyfcKPCA){ifWhVUtzbf = true;}
      else if(lNLyfcKPCA == PqcJsCsFiZ){pfzeawhUqY = true;}
      if(JkxlNjFhTV == AbgbAzXaBS){BsDFrXFRKn = true;}
      else if(AbgbAzXaBS == JkxlNjFhTV){GUjFpNQOUO = true;}
      if(hyDNXjOXLn == LCLHfGPwuS){cuqNNzqZhq = true;}
      else if(LCLHfGPwuS == hyDNXjOXLn){lJflduYaeT = true;}
      if(AaJiXjWnxf == WdqmYtbzmP){SujPcBSZgE = true;}
      else if(WdqmYtbzmP == AaJiXjWnxf){HEJqXzPYbT = true;}
      if(lCgrdMbZar == uGVCGTZZnr){tsNWnzTbVe = true;}
      else if(uGVCGTZZnr == lCgrdMbZar){PyIiiqYATM = true;}
      if(tuDlfQmPlI == shkAjiCERY){aTajImoJTV = true;}
      else if(shkAjiCERY == tuDlfQmPlI){IMHuwgAMAe = true;}
      if(nUstYhaOOc == MNUjcVksDF){cURkMGInbq = true;}
      else if(MNUjcVksDF == nUstYhaOOc){WHpWQBLrgq = true;}
      if(MRkmjfQKiK == WYmkXEgIAL){EekFsigTYO = true;}
      if(InxSsFWXCG == goICYospCo){eODCPyTzHo = true;}
      if(wGBnrQIlTu == rXgNCgllYk){MJFKaZbcJh = true;}
      while(WYmkXEgIAL == MRkmjfQKiK){yrmBymBxDm = true;}
      while(goICYospCo == goICYospCo){WYHRKuxNuq = true;}
      while(rXgNCgllYk == rXgNCgllYk){zCXxxIIkRg = true;}
      if(ifWhVUtzbf == true){ifWhVUtzbf = false;}
      if(BsDFrXFRKn == true){BsDFrXFRKn = false;}
      if(cuqNNzqZhq == true){cuqNNzqZhq = false;}
      if(SujPcBSZgE == true){SujPcBSZgE = false;}
      if(tsNWnzTbVe == true){tsNWnzTbVe = false;}
      if(aTajImoJTV == true){aTajImoJTV = false;}
      if(cURkMGInbq == true){cURkMGInbq = false;}
      if(EekFsigTYO == true){EekFsigTYO = false;}
      if(eODCPyTzHo == true){eODCPyTzHo = false;}
      if(MJFKaZbcJh == true){MJFKaZbcJh = false;}
      if(pfzeawhUqY == true){pfzeawhUqY = false;}
      if(GUjFpNQOUO == true){GUjFpNQOUO = false;}
      if(lJflduYaeT == true){lJflduYaeT = false;}
      if(HEJqXzPYbT == true){HEJqXzPYbT = false;}
      if(PyIiiqYATM == true){PyIiiqYATM = false;}
      if(IMHuwgAMAe == true){IMHuwgAMAe = false;}
      if(WHpWQBLrgq == true){WHpWQBLrgq = false;}
      if(yrmBymBxDm == true){yrmBymBxDm = false;}
      if(WYHRKuxNuq == true){WYHRKuxNuq = false;}
      if(zCXxxIIkRg == true){zCXxxIIkRg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCPKJUNZHE
{ 
  void yLwSaoFxDE()
  { 
      bool nmyNxzTKMa = false;
      bool NguUhdFAVr = false;
      bool LjVcfRkgUz = false;
      bool WbiYMktfrL = false;
      bool yzEalkOQWl = false;
      bool JSbjSDQVhe = false;
      bool OmpNDkyVIx = false;
      bool jZHJtLeupt = false;
      bool DTJioDzyGJ = false;
      bool TYxMxKJqWA = false;
      bool mrIZCjKSoG = false;
      bool XUembtcHYA = false;
      bool lzPzcKbuLi = false;
      bool CnYpHKLjfE = false;
      bool rgJzkztKkC = false;
      bool hCSWOnbJxq = false;
      bool HPGFEiwofQ = false;
      bool isaTHEoQNd = false;
      bool QRJJBAUBaT = false;
      bool iBloxbZEuC = false;
      string wCkVcNIbWu;
      string EyHVQLrGph;
      string jrEMaQJKbX;
      string xqwkjlajfP;
      string yFRDcuOrqZ;
      string wdeANExYuL;
      string DxAyxMBWle;
      string jHZajdZAif;
      string CQTBaSMwWf;
      string nBoULAFTGQ;
      string srGMooEDQj;
      string dxpOIldyWd;
      string zFzGqiSFOi;
      string YGtSmKKGLl;
      string OIfmBpKZLY;
      string WGwbQmrAUG;
      string WzohKWCXby;
      string bWlkOpZLEA;
      string XrsoLRKRBz;
      string RKlFPPTyce;
      if(wCkVcNIbWu == srGMooEDQj){nmyNxzTKMa = true;}
      else if(srGMooEDQj == wCkVcNIbWu){mrIZCjKSoG = true;}
      if(EyHVQLrGph == dxpOIldyWd){NguUhdFAVr = true;}
      else if(dxpOIldyWd == EyHVQLrGph){XUembtcHYA = true;}
      if(jrEMaQJKbX == zFzGqiSFOi){LjVcfRkgUz = true;}
      else if(zFzGqiSFOi == jrEMaQJKbX){lzPzcKbuLi = true;}
      if(xqwkjlajfP == YGtSmKKGLl){WbiYMktfrL = true;}
      else if(YGtSmKKGLl == xqwkjlajfP){CnYpHKLjfE = true;}
      if(yFRDcuOrqZ == OIfmBpKZLY){yzEalkOQWl = true;}
      else if(OIfmBpKZLY == yFRDcuOrqZ){rgJzkztKkC = true;}
      if(wdeANExYuL == WGwbQmrAUG){JSbjSDQVhe = true;}
      else if(WGwbQmrAUG == wdeANExYuL){hCSWOnbJxq = true;}
      if(DxAyxMBWle == WzohKWCXby){OmpNDkyVIx = true;}
      else if(WzohKWCXby == DxAyxMBWle){HPGFEiwofQ = true;}
      if(jHZajdZAif == bWlkOpZLEA){jZHJtLeupt = true;}
      if(CQTBaSMwWf == XrsoLRKRBz){DTJioDzyGJ = true;}
      if(nBoULAFTGQ == RKlFPPTyce){TYxMxKJqWA = true;}
      while(bWlkOpZLEA == jHZajdZAif){isaTHEoQNd = true;}
      while(XrsoLRKRBz == XrsoLRKRBz){QRJJBAUBaT = true;}
      while(RKlFPPTyce == RKlFPPTyce){iBloxbZEuC = true;}
      if(nmyNxzTKMa == true){nmyNxzTKMa = false;}
      if(NguUhdFAVr == true){NguUhdFAVr = false;}
      if(LjVcfRkgUz == true){LjVcfRkgUz = false;}
      if(WbiYMktfrL == true){WbiYMktfrL = false;}
      if(yzEalkOQWl == true){yzEalkOQWl = false;}
      if(JSbjSDQVhe == true){JSbjSDQVhe = false;}
      if(OmpNDkyVIx == true){OmpNDkyVIx = false;}
      if(jZHJtLeupt == true){jZHJtLeupt = false;}
      if(DTJioDzyGJ == true){DTJioDzyGJ = false;}
      if(TYxMxKJqWA == true){TYxMxKJqWA = false;}
      if(mrIZCjKSoG == true){mrIZCjKSoG = false;}
      if(XUembtcHYA == true){XUembtcHYA = false;}
      if(lzPzcKbuLi == true){lzPzcKbuLi = false;}
      if(CnYpHKLjfE == true){CnYpHKLjfE = false;}
      if(rgJzkztKkC == true){rgJzkztKkC = false;}
      if(hCSWOnbJxq == true){hCSWOnbJxq = false;}
      if(HPGFEiwofQ == true){HPGFEiwofQ = false;}
      if(isaTHEoQNd == true){isaTHEoQNd = false;}
      if(QRJJBAUBaT == true){QRJJBAUBaT = false;}
      if(iBloxbZEuC == true){iBloxbZEuC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDZIUAEDLF
{ 
  void cniPSoqOxB()
  { 
      bool XRzsEsPVmU = false;
      bool CYeeczJYJb = false;
      bool IIDnqRBEly = false;
      bool maBpVqlyRq = false;
      bool NdMwKLtKtK = false;
      bool ymPiKPNLBl = false;
      bool rLiogbWnIk = false;
      bool NKHROduHdf = false;
      bool WqKaAAKSfG = false;
      bool caxezCuXOh = false;
      bool nFBIxmfyUf = false;
      bool TGhUPAAHof = false;
      bool REICHlNbRL = false;
      bool iXsurRoBcM = false;
      bool ULxAmWscPz = false;
      bool BnihQjxzAL = false;
      bool ZDgIxuMlcx = false;
      bool KzdbLFGIPk = false;
      bool skMRKuoKeH = false;
      bool UpARlReoDq = false;
      string aXgTJNorTL;
      string VZmKICYmRY;
      string BPKNQXOWPB;
      string UwSQQxMUFA;
      string JDgCAdlVJY;
      string dudfYKMSDk;
      string ySbSpZGVsK;
      string pEgROxhHMm;
      string lrMqWYSlrF;
      string ksQTBqbOMa;
      string WPcyiZOLRa;
      string cEGQyGFjuR;
      string GUdmZwmMQW;
      string VTukPWPNIx;
      string KGUQcfmAUu;
      string kqTuUClpYl;
      string lBuuFJIUAb;
      string qqaxHzAMKs;
      string JlqVkdAAQM;
      string jZoWKILYKT;
      if(aXgTJNorTL == WPcyiZOLRa){XRzsEsPVmU = true;}
      else if(WPcyiZOLRa == aXgTJNorTL){nFBIxmfyUf = true;}
      if(VZmKICYmRY == cEGQyGFjuR){CYeeczJYJb = true;}
      else if(cEGQyGFjuR == VZmKICYmRY){TGhUPAAHof = true;}
      if(BPKNQXOWPB == GUdmZwmMQW){IIDnqRBEly = true;}
      else if(GUdmZwmMQW == BPKNQXOWPB){REICHlNbRL = true;}
      if(UwSQQxMUFA == VTukPWPNIx){maBpVqlyRq = true;}
      else if(VTukPWPNIx == UwSQQxMUFA){iXsurRoBcM = true;}
      if(JDgCAdlVJY == KGUQcfmAUu){NdMwKLtKtK = true;}
      else if(KGUQcfmAUu == JDgCAdlVJY){ULxAmWscPz = true;}
      if(dudfYKMSDk == kqTuUClpYl){ymPiKPNLBl = true;}
      else if(kqTuUClpYl == dudfYKMSDk){BnihQjxzAL = true;}
      if(ySbSpZGVsK == lBuuFJIUAb){rLiogbWnIk = true;}
      else if(lBuuFJIUAb == ySbSpZGVsK){ZDgIxuMlcx = true;}
      if(pEgROxhHMm == qqaxHzAMKs){NKHROduHdf = true;}
      if(lrMqWYSlrF == JlqVkdAAQM){WqKaAAKSfG = true;}
      if(ksQTBqbOMa == jZoWKILYKT){caxezCuXOh = true;}
      while(qqaxHzAMKs == pEgROxhHMm){KzdbLFGIPk = true;}
      while(JlqVkdAAQM == JlqVkdAAQM){skMRKuoKeH = true;}
      while(jZoWKILYKT == jZoWKILYKT){UpARlReoDq = true;}
      if(XRzsEsPVmU == true){XRzsEsPVmU = false;}
      if(CYeeczJYJb == true){CYeeczJYJb = false;}
      if(IIDnqRBEly == true){IIDnqRBEly = false;}
      if(maBpVqlyRq == true){maBpVqlyRq = false;}
      if(NdMwKLtKtK == true){NdMwKLtKtK = false;}
      if(ymPiKPNLBl == true){ymPiKPNLBl = false;}
      if(rLiogbWnIk == true){rLiogbWnIk = false;}
      if(NKHROduHdf == true){NKHROduHdf = false;}
      if(WqKaAAKSfG == true){WqKaAAKSfG = false;}
      if(caxezCuXOh == true){caxezCuXOh = false;}
      if(nFBIxmfyUf == true){nFBIxmfyUf = false;}
      if(TGhUPAAHof == true){TGhUPAAHof = false;}
      if(REICHlNbRL == true){REICHlNbRL = false;}
      if(iXsurRoBcM == true){iXsurRoBcM = false;}
      if(ULxAmWscPz == true){ULxAmWscPz = false;}
      if(BnihQjxzAL == true){BnihQjxzAL = false;}
      if(ZDgIxuMlcx == true){ZDgIxuMlcx = false;}
      if(KzdbLFGIPk == true){KzdbLFGIPk = false;}
      if(skMRKuoKeH == true){skMRKuoKeH = false;}
      if(UpARlReoDq == true){UpARlReoDq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQLZMBUVPW
{ 
  void tpaWKWCKeo()
  { 
      bool qaMpxKfVTo = false;
      bool ZQTzAOJqAz = false;
      bool nDQSgEQIQm = false;
      bool IpWZbfzMKE = false;
      bool mHmtTnwECd = false;
      bool PfykunKsIs = false;
      bool tWEggissXT = false;
      bool OwfuLgPWzs = false;
      bool HLFlXbrlem = false;
      bool VGERKPCFMk = false;
      bool uDgiOSzCYO = false;
      bool XmtPkhRSJE = false;
      bool qGOjxIrOju = false;
      bool dKJOyEeWWE = false;
      bool coMQOiMnfc = false;
      bool yjuHsnnwkG = false;
      bool ZkRcjNdeRg = false;
      bool DuuEbBsyVO = false;
      bool wDhHxtOBUJ = false;
      bool PhkQeqWjfB = false;
      string lqggOqZsmU;
      string aqbCjlckez;
      string OrayfnyUQa;
      string qcJiTPRuQY;
      string epXIVCbTIM;
      string sMfhCtQiAa;
      string rFbMcygrhU;
      string TgUGUYTSbd;
      string MeLEgdwbgZ;
      string ziupfYOLeW;
      string UiknsMrZMc;
      string ZxGVONsWey;
      string CFLIUjkeZw;
      string KImFJcsXLU;
      string lWPDzBcYbR;
      string fqffUPXcSI;
      string aMzQSQKBMk;
      string UVLKLeoHIT;
      string HLDIPScGjs;
      string EQEDsYWzji;
      if(lqggOqZsmU == UiknsMrZMc){qaMpxKfVTo = true;}
      else if(UiknsMrZMc == lqggOqZsmU){uDgiOSzCYO = true;}
      if(aqbCjlckez == ZxGVONsWey){ZQTzAOJqAz = true;}
      else if(ZxGVONsWey == aqbCjlckez){XmtPkhRSJE = true;}
      if(OrayfnyUQa == CFLIUjkeZw){nDQSgEQIQm = true;}
      else if(CFLIUjkeZw == OrayfnyUQa){qGOjxIrOju = true;}
      if(qcJiTPRuQY == KImFJcsXLU){IpWZbfzMKE = true;}
      else if(KImFJcsXLU == qcJiTPRuQY){dKJOyEeWWE = true;}
      if(epXIVCbTIM == lWPDzBcYbR){mHmtTnwECd = true;}
      else if(lWPDzBcYbR == epXIVCbTIM){coMQOiMnfc = true;}
      if(sMfhCtQiAa == fqffUPXcSI){PfykunKsIs = true;}
      else if(fqffUPXcSI == sMfhCtQiAa){yjuHsnnwkG = true;}
      if(rFbMcygrhU == aMzQSQKBMk){tWEggissXT = true;}
      else if(aMzQSQKBMk == rFbMcygrhU){ZkRcjNdeRg = true;}
      if(TgUGUYTSbd == UVLKLeoHIT){OwfuLgPWzs = true;}
      if(MeLEgdwbgZ == HLDIPScGjs){HLFlXbrlem = true;}
      if(ziupfYOLeW == EQEDsYWzji){VGERKPCFMk = true;}
      while(UVLKLeoHIT == TgUGUYTSbd){DuuEbBsyVO = true;}
      while(HLDIPScGjs == HLDIPScGjs){wDhHxtOBUJ = true;}
      while(EQEDsYWzji == EQEDsYWzji){PhkQeqWjfB = true;}
      if(qaMpxKfVTo == true){qaMpxKfVTo = false;}
      if(ZQTzAOJqAz == true){ZQTzAOJqAz = false;}
      if(nDQSgEQIQm == true){nDQSgEQIQm = false;}
      if(IpWZbfzMKE == true){IpWZbfzMKE = false;}
      if(mHmtTnwECd == true){mHmtTnwECd = false;}
      if(PfykunKsIs == true){PfykunKsIs = false;}
      if(tWEggissXT == true){tWEggissXT = false;}
      if(OwfuLgPWzs == true){OwfuLgPWzs = false;}
      if(HLFlXbrlem == true){HLFlXbrlem = false;}
      if(VGERKPCFMk == true){VGERKPCFMk = false;}
      if(uDgiOSzCYO == true){uDgiOSzCYO = false;}
      if(XmtPkhRSJE == true){XmtPkhRSJE = false;}
      if(qGOjxIrOju == true){qGOjxIrOju = false;}
      if(dKJOyEeWWE == true){dKJOyEeWWE = false;}
      if(coMQOiMnfc == true){coMQOiMnfc = false;}
      if(yjuHsnnwkG == true){yjuHsnnwkG = false;}
      if(ZkRcjNdeRg == true){ZkRcjNdeRg = false;}
      if(DuuEbBsyVO == true){DuuEbBsyVO = false;}
      if(wDhHxtOBUJ == true){wDhHxtOBUJ = false;}
      if(PhkQeqWjfB == true){PhkQeqWjfB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUQGJNEOMV
{ 
  void iQHsjrMDoz()
  { 
      bool mxCWLDPctB = false;
      bool GIpbKximJG = false;
      bool rLbBJwVdZi = false;
      bool ANlaOlJCsc = false;
      bool ySlpduxjFD = false;
      bool OcHqJaVBNO = false;
      bool hlDLBsVONY = false;
      bool nftfIYZkXO = false;
      bool ylXWTXGuQm = false;
      bool PIoduMOaok = false;
      bool YhVgPhhaik = false;
      bool BkcyQwNgqc = false;
      bool layZIepQkw = false;
      bool JzumoQPqHl = false;
      bool ofMfleepMz = false;
      bool yhiMyxiwXj = false;
      bool rQolaCopJz = false;
      bool gWYFnGOSnd = false;
      bool AzElxaPinr = false;
      bool gTSXsXpZEj = false;
      string RYPULLFNtK;
      string BIJHYnDGDR;
      string PmzbSGcdCk;
      string yaFtJImCAT;
      string maxaUYLjbw;
      string OYaohdZnCF;
      string haLIMaCPyP;
      string ABFjenoXGs;
      string trCGWYzQMe;
      string hzzukLPoOt;
      string WwlLuMSqJs;
      string nCgJKpYFkm;
      string akDShBCKzT;
      string YAIMWxGpKK;
      string GIGSpfRpjt;
      string lKEbTksSdt;
      string JIrpUnsUmN;
      string ihtagRdjcB;
      string iMZEgNwgrk;
      string DmMQAxQQyC;
      if(RYPULLFNtK == WwlLuMSqJs){mxCWLDPctB = true;}
      else if(WwlLuMSqJs == RYPULLFNtK){YhVgPhhaik = true;}
      if(BIJHYnDGDR == nCgJKpYFkm){GIpbKximJG = true;}
      else if(nCgJKpYFkm == BIJHYnDGDR){BkcyQwNgqc = true;}
      if(PmzbSGcdCk == akDShBCKzT){rLbBJwVdZi = true;}
      else if(akDShBCKzT == PmzbSGcdCk){layZIepQkw = true;}
      if(yaFtJImCAT == YAIMWxGpKK){ANlaOlJCsc = true;}
      else if(YAIMWxGpKK == yaFtJImCAT){JzumoQPqHl = true;}
      if(maxaUYLjbw == GIGSpfRpjt){ySlpduxjFD = true;}
      else if(GIGSpfRpjt == maxaUYLjbw){ofMfleepMz = true;}
      if(OYaohdZnCF == lKEbTksSdt){OcHqJaVBNO = true;}
      else if(lKEbTksSdt == OYaohdZnCF){yhiMyxiwXj = true;}
      if(haLIMaCPyP == JIrpUnsUmN){hlDLBsVONY = true;}
      else if(JIrpUnsUmN == haLIMaCPyP){rQolaCopJz = true;}
      if(ABFjenoXGs == ihtagRdjcB){nftfIYZkXO = true;}
      if(trCGWYzQMe == iMZEgNwgrk){ylXWTXGuQm = true;}
      if(hzzukLPoOt == DmMQAxQQyC){PIoduMOaok = true;}
      while(ihtagRdjcB == ABFjenoXGs){gWYFnGOSnd = true;}
      while(iMZEgNwgrk == iMZEgNwgrk){AzElxaPinr = true;}
      while(DmMQAxQQyC == DmMQAxQQyC){gTSXsXpZEj = true;}
      if(mxCWLDPctB == true){mxCWLDPctB = false;}
      if(GIpbKximJG == true){GIpbKximJG = false;}
      if(rLbBJwVdZi == true){rLbBJwVdZi = false;}
      if(ANlaOlJCsc == true){ANlaOlJCsc = false;}
      if(ySlpduxjFD == true){ySlpduxjFD = false;}
      if(OcHqJaVBNO == true){OcHqJaVBNO = false;}
      if(hlDLBsVONY == true){hlDLBsVONY = false;}
      if(nftfIYZkXO == true){nftfIYZkXO = false;}
      if(ylXWTXGuQm == true){ylXWTXGuQm = false;}
      if(PIoduMOaok == true){PIoduMOaok = false;}
      if(YhVgPhhaik == true){YhVgPhhaik = false;}
      if(BkcyQwNgqc == true){BkcyQwNgqc = false;}
      if(layZIepQkw == true){layZIepQkw = false;}
      if(JzumoQPqHl == true){JzumoQPqHl = false;}
      if(ofMfleepMz == true){ofMfleepMz = false;}
      if(yhiMyxiwXj == true){yhiMyxiwXj = false;}
      if(rQolaCopJz == true){rQolaCopJz = false;}
      if(gWYFnGOSnd == true){gWYFnGOSnd = false;}
      if(AzElxaPinr == true){AzElxaPinr = false;}
      if(gTSXsXpZEj == true){gTSXsXpZEj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZCCDHQCBB
{ 
  void CNQCFZOMWZ()
  { 
      bool uhsEYgsBEc = false;
      bool sleoIFbFnC = false;
      bool nHtJRXnGHZ = false;
      bool OWjtVRGxuH = false;
      bool VinlnIynNx = false;
      bool MkEIDmmimA = false;
      bool smseOVCkSp = false;
      bool yeKffETIVI = false;
      bool ZzrJMcRapi = false;
      bool eWKtOioIWR = false;
      bool FMUXzhaYbz = false;
      bool SdNdastjRk = false;
      bool EaujKaUPQx = false;
      bool PKlDCMdUKe = false;
      bool CsyqPAJfTV = false;
      bool nFqkNeRkMX = false;
      bool NKHejHrKaO = false;
      bool OZYmhKbDUJ = false;
      bool RnwuIJTApX = false;
      bool tsHmQrkTHH = false;
      string snIhTtsIRc;
      string VMInItsBEj;
      string fnLCLufqVu;
      string gSmBulDpcl;
      string zQFxEWMOoq;
      string tSkATFbFWX;
      string OClWuCZGsW;
      string pDXRjPhOyn;
      string iRCeANhlho;
      string JySFXxdiBB;
      string xGVSAquSPE;
      string XNGhoxAHVg;
      string TmYDMrjRtm;
      string lyMwqcuieJ;
      string SPWcRwqjQZ;
      string xVNThJhRFI;
      string GcYcRYAJqM;
      string BQcLOEQulQ;
      string AABToPkrOg;
      string udcVDopsKr;
      if(snIhTtsIRc == xGVSAquSPE){uhsEYgsBEc = true;}
      else if(xGVSAquSPE == snIhTtsIRc){FMUXzhaYbz = true;}
      if(VMInItsBEj == XNGhoxAHVg){sleoIFbFnC = true;}
      else if(XNGhoxAHVg == VMInItsBEj){SdNdastjRk = true;}
      if(fnLCLufqVu == TmYDMrjRtm){nHtJRXnGHZ = true;}
      else if(TmYDMrjRtm == fnLCLufqVu){EaujKaUPQx = true;}
      if(gSmBulDpcl == lyMwqcuieJ){OWjtVRGxuH = true;}
      else if(lyMwqcuieJ == gSmBulDpcl){PKlDCMdUKe = true;}
      if(zQFxEWMOoq == SPWcRwqjQZ){VinlnIynNx = true;}
      else if(SPWcRwqjQZ == zQFxEWMOoq){CsyqPAJfTV = true;}
      if(tSkATFbFWX == xVNThJhRFI){MkEIDmmimA = true;}
      else if(xVNThJhRFI == tSkATFbFWX){nFqkNeRkMX = true;}
      if(OClWuCZGsW == GcYcRYAJqM){smseOVCkSp = true;}
      else if(GcYcRYAJqM == OClWuCZGsW){NKHejHrKaO = true;}
      if(pDXRjPhOyn == BQcLOEQulQ){yeKffETIVI = true;}
      if(iRCeANhlho == AABToPkrOg){ZzrJMcRapi = true;}
      if(JySFXxdiBB == udcVDopsKr){eWKtOioIWR = true;}
      while(BQcLOEQulQ == pDXRjPhOyn){OZYmhKbDUJ = true;}
      while(AABToPkrOg == AABToPkrOg){RnwuIJTApX = true;}
      while(udcVDopsKr == udcVDopsKr){tsHmQrkTHH = true;}
      if(uhsEYgsBEc == true){uhsEYgsBEc = false;}
      if(sleoIFbFnC == true){sleoIFbFnC = false;}
      if(nHtJRXnGHZ == true){nHtJRXnGHZ = false;}
      if(OWjtVRGxuH == true){OWjtVRGxuH = false;}
      if(VinlnIynNx == true){VinlnIynNx = false;}
      if(MkEIDmmimA == true){MkEIDmmimA = false;}
      if(smseOVCkSp == true){smseOVCkSp = false;}
      if(yeKffETIVI == true){yeKffETIVI = false;}
      if(ZzrJMcRapi == true){ZzrJMcRapi = false;}
      if(eWKtOioIWR == true){eWKtOioIWR = false;}
      if(FMUXzhaYbz == true){FMUXzhaYbz = false;}
      if(SdNdastjRk == true){SdNdastjRk = false;}
      if(EaujKaUPQx == true){EaujKaUPQx = false;}
      if(PKlDCMdUKe == true){PKlDCMdUKe = false;}
      if(CsyqPAJfTV == true){CsyqPAJfTV = false;}
      if(nFqkNeRkMX == true){nFqkNeRkMX = false;}
      if(NKHejHrKaO == true){NKHejHrKaO = false;}
      if(OZYmhKbDUJ == true){OZYmhKbDUJ = false;}
      if(RnwuIJTApX == true){RnwuIJTApX = false;}
      if(tsHmQrkTHH == true){tsHmQrkTHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGCAHUOKXO
{ 
  void PMmbDuFqzI()
  { 
      bool XadWYlgmay = false;
      bool qNTANMLzCm = false;
      bool ctCUjlSdNf = false;
      bool XjSLwGGqsr = false;
      bool UPwEusmVdO = false;
      bool noQDzcYJll = false;
      bool SCZtaGtIDH = false;
      bool GUGJRMyxYp = false;
      bool zxzyriTOLT = false;
      bool gwEHZRpBdn = false;
      bool yeRWIShGkl = false;
      bool dbjumUDaCq = false;
      bool lfwjZJPyjA = false;
      bool WxSjrTfcoY = false;
      bool ANcZoEMIUE = false;
      bool OOymCRihwz = false;
      bool CjWkPfIzDS = false;
      bool oZlcqYCWtU = false;
      bool wHdelHzfhZ = false;
      bool kxfoWQprJI = false;
      string BPPgPjuYAK;
      string GVsdOeeqcQ;
      string fQfCPJBtUx;
      string fchgIUOnkM;
      string FPspIlWcYY;
      string IFSwJkjNQF;
      string iAECednLVt;
      string PqFPKPWosd;
      string mXUuoZJkXX;
      string jBWedFLpLe;
      string xKHeJQADks;
      string NtTmSKeINF;
      string TDnyJOTZkE;
      string EfcOfcQplX;
      string ZGzeJogjMS;
      string aCcGLtVIUt;
      string wZRgngRFGp;
      string tnVofMDInU;
      string gjNRdBDWDl;
      string GHVqbznSpc;
      if(BPPgPjuYAK == xKHeJQADks){XadWYlgmay = true;}
      else if(xKHeJQADks == BPPgPjuYAK){yeRWIShGkl = true;}
      if(GVsdOeeqcQ == NtTmSKeINF){qNTANMLzCm = true;}
      else if(NtTmSKeINF == GVsdOeeqcQ){dbjumUDaCq = true;}
      if(fQfCPJBtUx == TDnyJOTZkE){ctCUjlSdNf = true;}
      else if(TDnyJOTZkE == fQfCPJBtUx){lfwjZJPyjA = true;}
      if(fchgIUOnkM == EfcOfcQplX){XjSLwGGqsr = true;}
      else if(EfcOfcQplX == fchgIUOnkM){WxSjrTfcoY = true;}
      if(FPspIlWcYY == ZGzeJogjMS){UPwEusmVdO = true;}
      else if(ZGzeJogjMS == FPspIlWcYY){ANcZoEMIUE = true;}
      if(IFSwJkjNQF == aCcGLtVIUt){noQDzcYJll = true;}
      else if(aCcGLtVIUt == IFSwJkjNQF){OOymCRihwz = true;}
      if(iAECednLVt == wZRgngRFGp){SCZtaGtIDH = true;}
      else if(wZRgngRFGp == iAECednLVt){CjWkPfIzDS = true;}
      if(PqFPKPWosd == tnVofMDInU){GUGJRMyxYp = true;}
      if(mXUuoZJkXX == gjNRdBDWDl){zxzyriTOLT = true;}
      if(jBWedFLpLe == GHVqbznSpc){gwEHZRpBdn = true;}
      while(tnVofMDInU == PqFPKPWosd){oZlcqYCWtU = true;}
      while(gjNRdBDWDl == gjNRdBDWDl){wHdelHzfhZ = true;}
      while(GHVqbznSpc == GHVqbznSpc){kxfoWQprJI = true;}
      if(XadWYlgmay == true){XadWYlgmay = false;}
      if(qNTANMLzCm == true){qNTANMLzCm = false;}
      if(ctCUjlSdNf == true){ctCUjlSdNf = false;}
      if(XjSLwGGqsr == true){XjSLwGGqsr = false;}
      if(UPwEusmVdO == true){UPwEusmVdO = false;}
      if(noQDzcYJll == true){noQDzcYJll = false;}
      if(SCZtaGtIDH == true){SCZtaGtIDH = false;}
      if(GUGJRMyxYp == true){GUGJRMyxYp = false;}
      if(zxzyriTOLT == true){zxzyriTOLT = false;}
      if(gwEHZRpBdn == true){gwEHZRpBdn = false;}
      if(yeRWIShGkl == true){yeRWIShGkl = false;}
      if(dbjumUDaCq == true){dbjumUDaCq = false;}
      if(lfwjZJPyjA == true){lfwjZJPyjA = false;}
      if(WxSjrTfcoY == true){WxSjrTfcoY = false;}
      if(ANcZoEMIUE == true){ANcZoEMIUE = false;}
      if(OOymCRihwz == true){OOymCRihwz = false;}
      if(CjWkPfIzDS == true){CjWkPfIzDS = false;}
      if(oZlcqYCWtU == true){oZlcqYCWtU = false;}
      if(wHdelHzfhZ == true){wHdelHzfhZ = false;}
      if(kxfoWQprJI == true){kxfoWQprJI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRCFURXENG
{ 
  void Rzwwxcbpjp()
  { 
      bool EgfsUzWPRy = false;
      bool htEKxTpriL = false;
      bool GnzDFqLPbK = false;
      bool SlDdCJsbMj = false;
      bool pkfCIQeSSI = false;
      bool zdqCbPhcmc = false;
      bool nGnGfwpaIm = false;
      bool aNeyUUHwto = false;
      bool MsxTLntBBl = false;
      bool bQnjwixZWM = false;
      bool aEJehkzrgH = false;
      bool HkhyPuJUur = false;
      bool BnYVLJYuBk = false;
      bool WhZgNIiRkZ = false;
      bool oBUtepipTB = false;
      bool ZcdeLlenSX = false;
      bool LDpujYLAjH = false;
      bool LqiVCzTeqV = false;
      bool aibALsEuVb = false;
      bool duyMNkLYJF = false;
      string DfVlDRHYyJ;
      string lJutUSTEaL;
      string tFuTXcROWI;
      string PDUSTdYRZY;
      string PplMGnquFG;
      string tWEksykCNa;
      string zrBptincZp;
      string tCeCuEShMj;
      string lWJQOryiZV;
      string sWDzYWnwSX;
      string zOUOLrqCpn;
      string eCodncikaB;
      string jFCDxXyfcX;
      string PWPojWBtEV;
      string BuskqqgYKw;
      string nDURmtLRQn;
      string sLYSXIlAsQ;
      string bnfEzoLRMG;
      string pYVgiMByBp;
      string LjcQcoVZNi;
      if(DfVlDRHYyJ == zOUOLrqCpn){EgfsUzWPRy = true;}
      else if(zOUOLrqCpn == DfVlDRHYyJ){aEJehkzrgH = true;}
      if(lJutUSTEaL == eCodncikaB){htEKxTpriL = true;}
      else if(eCodncikaB == lJutUSTEaL){HkhyPuJUur = true;}
      if(tFuTXcROWI == jFCDxXyfcX){GnzDFqLPbK = true;}
      else if(jFCDxXyfcX == tFuTXcROWI){BnYVLJYuBk = true;}
      if(PDUSTdYRZY == PWPojWBtEV){SlDdCJsbMj = true;}
      else if(PWPojWBtEV == PDUSTdYRZY){WhZgNIiRkZ = true;}
      if(PplMGnquFG == BuskqqgYKw){pkfCIQeSSI = true;}
      else if(BuskqqgYKw == PplMGnquFG){oBUtepipTB = true;}
      if(tWEksykCNa == nDURmtLRQn){zdqCbPhcmc = true;}
      else if(nDURmtLRQn == tWEksykCNa){ZcdeLlenSX = true;}
      if(zrBptincZp == sLYSXIlAsQ){nGnGfwpaIm = true;}
      else if(sLYSXIlAsQ == zrBptincZp){LDpujYLAjH = true;}
      if(tCeCuEShMj == bnfEzoLRMG){aNeyUUHwto = true;}
      if(lWJQOryiZV == pYVgiMByBp){MsxTLntBBl = true;}
      if(sWDzYWnwSX == LjcQcoVZNi){bQnjwixZWM = true;}
      while(bnfEzoLRMG == tCeCuEShMj){LqiVCzTeqV = true;}
      while(pYVgiMByBp == pYVgiMByBp){aibALsEuVb = true;}
      while(LjcQcoVZNi == LjcQcoVZNi){duyMNkLYJF = true;}
      if(EgfsUzWPRy == true){EgfsUzWPRy = false;}
      if(htEKxTpriL == true){htEKxTpriL = false;}
      if(GnzDFqLPbK == true){GnzDFqLPbK = false;}
      if(SlDdCJsbMj == true){SlDdCJsbMj = false;}
      if(pkfCIQeSSI == true){pkfCIQeSSI = false;}
      if(zdqCbPhcmc == true){zdqCbPhcmc = false;}
      if(nGnGfwpaIm == true){nGnGfwpaIm = false;}
      if(aNeyUUHwto == true){aNeyUUHwto = false;}
      if(MsxTLntBBl == true){MsxTLntBBl = false;}
      if(bQnjwixZWM == true){bQnjwixZWM = false;}
      if(aEJehkzrgH == true){aEJehkzrgH = false;}
      if(HkhyPuJUur == true){HkhyPuJUur = false;}
      if(BnYVLJYuBk == true){BnYVLJYuBk = false;}
      if(WhZgNIiRkZ == true){WhZgNIiRkZ = false;}
      if(oBUtepipTB == true){oBUtepipTB = false;}
      if(ZcdeLlenSX == true){ZcdeLlenSX = false;}
      if(LDpujYLAjH == true){LDpujYLAjH = false;}
      if(LqiVCzTeqV == true){LqiVCzTeqV = false;}
      if(aibALsEuVb == true){aibALsEuVb = false;}
      if(duyMNkLYJF == true){duyMNkLYJF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGPFTMBUTU
{ 
  void gRlXzOVARX()
  { 
      bool xuYAPCwFSK = false;
      bool XIcGsfBkeS = false;
      bool wNszJgoFoo = false;
      bool DmmZXqufNz = false;
      bool IUKlyTAHHT = false;
      bool GDLmfjBZpi = false;
      bool MqPdGkUDiC = false;
      bool kUXfJaCGBp = false;
      bool ghyViAaAsm = false;
      bool oUoelREgeM = false;
      bool yxXEhkefcE = false;
      bool htYACestuG = false;
      bool JUJuNPfssr = false;
      bool VUbnqjJsmx = false;
      bool UuXnEtwocH = false;
      bool YKlYDdmcqS = false;
      bool FllkiNSjJS = false;
      bool UzHxlNxUqS = false;
      bool SpQlSLhCkN = false;
      bool wgCTrhJlFq = false;
      string tRGscOZRoD;
      string JIZbuUExCa;
      string RxhQdIHCri;
      string VpArlJSBXC;
      string VRqkRHGTYG;
      string RbTrgxipOT;
      string HWZGgSHhol;
      string BCYAFAFxyW;
      string CmclQsWIKo;
      string acmEuyqjDy;
      string zYemEPDTlg;
      string qkqrQTsnpm;
      string uzWzKYOUEG;
      string IUtAWdIpgA;
      string pDVdyoltma;
      string FDtPCABebf;
      string AhOfXVqqVl;
      string KDGoxrcsBV;
      string lUgcBFZdxV;
      string cdNBAHnpFb;
      if(tRGscOZRoD == zYemEPDTlg){xuYAPCwFSK = true;}
      else if(zYemEPDTlg == tRGscOZRoD){yxXEhkefcE = true;}
      if(JIZbuUExCa == qkqrQTsnpm){XIcGsfBkeS = true;}
      else if(qkqrQTsnpm == JIZbuUExCa){htYACestuG = true;}
      if(RxhQdIHCri == uzWzKYOUEG){wNszJgoFoo = true;}
      else if(uzWzKYOUEG == RxhQdIHCri){JUJuNPfssr = true;}
      if(VpArlJSBXC == IUtAWdIpgA){DmmZXqufNz = true;}
      else if(IUtAWdIpgA == VpArlJSBXC){VUbnqjJsmx = true;}
      if(VRqkRHGTYG == pDVdyoltma){IUKlyTAHHT = true;}
      else if(pDVdyoltma == VRqkRHGTYG){UuXnEtwocH = true;}
      if(RbTrgxipOT == FDtPCABebf){GDLmfjBZpi = true;}
      else if(FDtPCABebf == RbTrgxipOT){YKlYDdmcqS = true;}
      if(HWZGgSHhol == AhOfXVqqVl){MqPdGkUDiC = true;}
      else if(AhOfXVqqVl == HWZGgSHhol){FllkiNSjJS = true;}
      if(BCYAFAFxyW == KDGoxrcsBV){kUXfJaCGBp = true;}
      if(CmclQsWIKo == lUgcBFZdxV){ghyViAaAsm = true;}
      if(acmEuyqjDy == cdNBAHnpFb){oUoelREgeM = true;}
      while(KDGoxrcsBV == BCYAFAFxyW){UzHxlNxUqS = true;}
      while(lUgcBFZdxV == lUgcBFZdxV){SpQlSLhCkN = true;}
      while(cdNBAHnpFb == cdNBAHnpFb){wgCTrhJlFq = true;}
      if(xuYAPCwFSK == true){xuYAPCwFSK = false;}
      if(XIcGsfBkeS == true){XIcGsfBkeS = false;}
      if(wNszJgoFoo == true){wNszJgoFoo = false;}
      if(DmmZXqufNz == true){DmmZXqufNz = false;}
      if(IUKlyTAHHT == true){IUKlyTAHHT = false;}
      if(GDLmfjBZpi == true){GDLmfjBZpi = false;}
      if(MqPdGkUDiC == true){MqPdGkUDiC = false;}
      if(kUXfJaCGBp == true){kUXfJaCGBp = false;}
      if(ghyViAaAsm == true){ghyViAaAsm = false;}
      if(oUoelREgeM == true){oUoelREgeM = false;}
      if(yxXEhkefcE == true){yxXEhkefcE = false;}
      if(htYACestuG == true){htYACestuG = false;}
      if(JUJuNPfssr == true){JUJuNPfssr = false;}
      if(VUbnqjJsmx == true){VUbnqjJsmx = false;}
      if(UuXnEtwocH == true){UuXnEtwocH = false;}
      if(YKlYDdmcqS == true){YKlYDdmcqS = false;}
      if(FllkiNSjJS == true){FllkiNSjJS = false;}
      if(UzHxlNxUqS == true){UzHxlNxUqS = false;}
      if(SpQlSLhCkN == true){SpQlSLhCkN = false;}
      if(wgCTrhJlFq == true){wgCTrhJlFq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGRTRMDUTL
{ 
  void WJafruZhDA()
  { 
      bool FdJgmllUEQ = false;
      bool ZsVpDdajWR = false;
      bool wOiwyYKJeC = false;
      bool rmiqRXzQyq = false;
      bool hhWuGVeVws = false;
      bool kzQBSquMiN = false;
      bool aboBYmJdYf = false;
      bool eJlfiOqnob = false;
      bool soNkQrVhXZ = false;
      bool clgjPGrUWT = false;
      bool LBxQOaNkRE = false;
      bool zGXHUlOEjf = false;
      bool QbFyDrcBPc = false;
      bool VWRVPrqwWo = false;
      bool dkPTaVOZPc = false;
      bool qnjpDiuyNV = false;
      bool yLUohboCqb = false;
      bool tRguCeMkXg = false;
      bool dDllkgmbSf = false;
      bool xsiBqRPaly = false;
      string dsqWYNmYjl;
      string UyFdhCKSLz;
      string rxqNJkikVc;
      string gLGnUiCNGu;
      string HOpZiIVHeh;
      string gdkeffCdMn;
      string eCDHEIqQJz;
      string AxLPrcHQdA;
      string PaFmuDabIn;
      string gYASQFLhUa;
      string REyfgjRUmC;
      string YkzMXDwPMB;
      string hPIVSbxszl;
      string QYuDiKcZFK;
      string kFnFOuZmtN;
      string IwVTrBwbNF;
      string mYVAlzoudM;
      string ZWJBPbaCGW;
      string CJykcUCaLg;
      string OBLAWMjnTP;
      if(dsqWYNmYjl == REyfgjRUmC){FdJgmllUEQ = true;}
      else if(REyfgjRUmC == dsqWYNmYjl){LBxQOaNkRE = true;}
      if(UyFdhCKSLz == YkzMXDwPMB){ZsVpDdajWR = true;}
      else if(YkzMXDwPMB == UyFdhCKSLz){zGXHUlOEjf = true;}
      if(rxqNJkikVc == hPIVSbxszl){wOiwyYKJeC = true;}
      else if(hPIVSbxszl == rxqNJkikVc){QbFyDrcBPc = true;}
      if(gLGnUiCNGu == QYuDiKcZFK){rmiqRXzQyq = true;}
      else if(QYuDiKcZFK == gLGnUiCNGu){VWRVPrqwWo = true;}
      if(HOpZiIVHeh == kFnFOuZmtN){hhWuGVeVws = true;}
      else if(kFnFOuZmtN == HOpZiIVHeh){dkPTaVOZPc = true;}
      if(gdkeffCdMn == IwVTrBwbNF){kzQBSquMiN = true;}
      else if(IwVTrBwbNF == gdkeffCdMn){qnjpDiuyNV = true;}
      if(eCDHEIqQJz == mYVAlzoudM){aboBYmJdYf = true;}
      else if(mYVAlzoudM == eCDHEIqQJz){yLUohboCqb = true;}
      if(AxLPrcHQdA == ZWJBPbaCGW){eJlfiOqnob = true;}
      if(PaFmuDabIn == CJykcUCaLg){soNkQrVhXZ = true;}
      if(gYASQFLhUa == OBLAWMjnTP){clgjPGrUWT = true;}
      while(ZWJBPbaCGW == AxLPrcHQdA){tRguCeMkXg = true;}
      while(CJykcUCaLg == CJykcUCaLg){dDllkgmbSf = true;}
      while(OBLAWMjnTP == OBLAWMjnTP){xsiBqRPaly = true;}
      if(FdJgmllUEQ == true){FdJgmllUEQ = false;}
      if(ZsVpDdajWR == true){ZsVpDdajWR = false;}
      if(wOiwyYKJeC == true){wOiwyYKJeC = false;}
      if(rmiqRXzQyq == true){rmiqRXzQyq = false;}
      if(hhWuGVeVws == true){hhWuGVeVws = false;}
      if(kzQBSquMiN == true){kzQBSquMiN = false;}
      if(aboBYmJdYf == true){aboBYmJdYf = false;}
      if(eJlfiOqnob == true){eJlfiOqnob = false;}
      if(soNkQrVhXZ == true){soNkQrVhXZ = false;}
      if(clgjPGrUWT == true){clgjPGrUWT = false;}
      if(LBxQOaNkRE == true){LBxQOaNkRE = false;}
      if(zGXHUlOEjf == true){zGXHUlOEjf = false;}
      if(QbFyDrcBPc == true){QbFyDrcBPc = false;}
      if(VWRVPrqwWo == true){VWRVPrqwWo = false;}
      if(dkPTaVOZPc == true){dkPTaVOZPc = false;}
      if(qnjpDiuyNV == true){qnjpDiuyNV = false;}
      if(yLUohboCqb == true){yLUohboCqb = false;}
      if(tRguCeMkXg == true){tRguCeMkXg = false;}
      if(dDllkgmbSf == true){dDllkgmbSf = false;}
      if(xsiBqRPaly == true){xsiBqRPaly = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOLHLCMBPC
{ 
  void RcDXsnixgD()
  { 
      bool PCwFnmNTWL = false;
      bool ctQDGZfiMB = false;
      bool bwaLAsYYCM = false;
      bool JFZSfHlVzE = false;
      bool cjEJcNhJgA = false;
      bool qItioTajFt = false;
      bool OnRJCWUxWy = false;
      bool mKjHXqrRim = false;
      bool LPrBUAKpdM = false;
      bool gCPEpnStGF = false;
      bool rjliNgXmKx = false;
      bool aIBShywPoC = false;
      bool LdTKRjtfQj = false;
      bool YxLdtbdJmm = false;
      bool bXfflXBwWr = false;
      bool qCFEsOQbRc = false;
      bool lrWZYdxWYG = false;
      bool UmcBZnxmYs = false;
      bool iyJYrVrGje = false;
      bool KCrJAjAGGH = false;
      string CXKBlCFoOl;
      string IBhbaPTYpN;
      string yOPPeRbItO;
      string uluIQzaxBy;
      string WnGMBUPtKP;
      string bSgNUnHuWU;
      string ZxuzqVGZKa;
      string oWWqqKHDOJ;
      string BhxdmbFhmc;
      string qfZgXYrHVe;
      string OpijZEwpVK;
      string fEfMSrzRLO;
      string QYlhiJwoSR;
      string RAgiuLzNEi;
      string eOLcxmzNNf;
      string ZawGNpDBAQ;
      string IHWErfWxRH;
      string rlMcjBMJjw;
      string KibmrqDaVF;
      string HyMmaXrHjR;
      if(CXKBlCFoOl == OpijZEwpVK){PCwFnmNTWL = true;}
      else if(OpijZEwpVK == CXKBlCFoOl){rjliNgXmKx = true;}
      if(IBhbaPTYpN == fEfMSrzRLO){ctQDGZfiMB = true;}
      else if(fEfMSrzRLO == IBhbaPTYpN){aIBShywPoC = true;}
      if(yOPPeRbItO == QYlhiJwoSR){bwaLAsYYCM = true;}
      else if(QYlhiJwoSR == yOPPeRbItO){LdTKRjtfQj = true;}
      if(uluIQzaxBy == RAgiuLzNEi){JFZSfHlVzE = true;}
      else if(RAgiuLzNEi == uluIQzaxBy){YxLdtbdJmm = true;}
      if(WnGMBUPtKP == eOLcxmzNNf){cjEJcNhJgA = true;}
      else if(eOLcxmzNNf == WnGMBUPtKP){bXfflXBwWr = true;}
      if(bSgNUnHuWU == ZawGNpDBAQ){qItioTajFt = true;}
      else if(ZawGNpDBAQ == bSgNUnHuWU){qCFEsOQbRc = true;}
      if(ZxuzqVGZKa == IHWErfWxRH){OnRJCWUxWy = true;}
      else if(IHWErfWxRH == ZxuzqVGZKa){lrWZYdxWYG = true;}
      if(oWWqqKHDOJ == rlMcjBMJjw){mKjHXqrRim = true;}
      if(BhxdmbFhmc == KibmrqDaVF){LPrBUAKpdM = true;}
      if(qfZgXYrHVe == HyMmaXrHjR){gCPEpnStGF = true;}
      while(rlMcjBMJjw == oWWqqKHDOJ){UmcBZnxmYs = true;}
      while(KibmrqDaVF == KibmrqDaVF){iyJYrVrGje = true;}
      while(HyMmaXrHjR == HyMmaXrHjR){KCrJAjAGGH = true;}
      if(PCwFnmNTWL == true){PCwFnmNTWL = false;}
      if(ctQDGZfiMB == true){ctQDGZfiMB = false;}
      if(bwaLAsYYCM == true){bwaLAsYYCM = false;}
      if(JFZSfHlVzE == true){JFZSfHlVzE = false;}
      if(cjEJcNhJgA == true){cjEJcNhJgA = false;}
      if(qItioTajFt == true){qItioTajFt = false;}
      if(OnRJCWUxWy == true){OnRJCWUxWy = false;}
      if(mKjHXqrRim == true){mKjHXqrRim = false;}
      if(LPrBUAKpdM == true){LPrBUAKpdM = false;}
      if(gCPEpnStGF == true){gCPEpnStGF = false;}
      if(rjliNgXmKx == true){rjliNgXmKx = false;}
      if(aIBShywPoC == true){aIBShywPoC = false;}
      if(LdTKRjtfQj == true){LdTKRjtfQj = false;}
      if(YxLdtbdJmm == true){YxLdtbdJmm = false;}
      if(bXfflXBwWr == true){bXfflXBwWr = false;}
      if(qCFEsOQbRc == true){qCFEsOQbRc = false;}
      if(lrWZYdxWYG == true){lrWZYdxWYG = false;}
      if(UmcBZnxmYs == true){UmcBZnxmYs = false;}
      if(iyJYrVrGje == true){iyJYrVrGje = false;}
      if(KCrJAjAGGH == true){KCrJAjAGGH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQAGEPCOQM
{ 
  void oVkfBQzSxP()
  { 
      bool tDlWLljOcR = false;
      bool RRLlxVtKom = false;
      bool GMOaeEzmzO = false;
      bool yCisGwFdyQ = false;
      bool HksaUfzTMZ = false;
      bool uLIfHhnLqG = false;
      bool lxPNTOhSeB = false;
      bool QQMYfVSnFy = false;
      bool FfZYSlsDlY = false;
      bool HslqdKVeHF = false;
      bool xgnLIezjAk = false;
      bool PAGsBGWpug = false;
      bool UefGsWdUtU = false;
      bool AmfzAXqOQn = false;
      bool mJCAJHmspX = false;
      bool mejajRBhRk = false;
      bool BeoekbTGrc = false;
      bool OHZGtLcexl = false;
      bool jjeWhUDFOh = false;
      bool WJxemHTXPg = false;
      string DiDcQJpyHB;
      string TcfmXfLlHw;
      string NNVjuakbgi;
      string dMHWZcUAmx;
      string HCnuFfhIOS;
      string RuQcQpMThp;
      string XORXXHVJMt;
      string LLyKnKZadO;
      string rbNNRhweFj;
      string PASxYskPWy;
      string JYwTHGwFnF;
      string PloSxwADGp;
      string KqDbeKrBlu;
      string ZJDfFTftGK;
      string kppAUcLAAb;
      string rgJgmSUTnw;
      string OuTrfGiINc;
      string QFxuEUADHB;
      string zrAJDrzVsm;
      string yLGJwpVyTN;
      if(DiDcQJpyHB == JYwTHGwFnF){tDlWLljOcR = true;}
      else if(JYwTHGwFnF == DiDcQJpyHB){xgnLIezjAk = true;}
      if(TcfmXfLlHw == PloSxwADGp){RRLlxVtKom = true;}
      else if(PloSxwADGp == TcfmXfLlHw){PAGsBGWpug = true;}
      if(NNVjuakbgi == KqDbeKrBlu){GMOaeEzmzO = true;}
      else if(KqDbeKrBlu == NNVjuakbgi){UefGsWdUtU = true;}
      if(dMHWZcUAmx == ZJDfFTftGK){yCisGwFdyQ = true;}
      else if(ZJDfFTftGK == dMHWZcUAmx){AmfzAXqOQn = true;}
      if(HCnuFfhIOS == kppAUcLAAb){HksaUfzTMZ = true;}
      else if(kppAUcLAAb == HCnuFfhIOS){mJCAJHmspX = true;}
      if(RuQcQpMThp == rgJgmSUTnw){uLIfHhnLqG = true;}
      else if(rgJgmSUTnw == RuQcQpMThp){mejajRBhRk = true;}
      if(XORXXHVJMt == OuTrfGiINc){lxPNTOhSeB = true;}
      else if(OuTrfGiINc == XORXXHVJMt){BeoekbTGrc = true;}
      if(LLyKnKZadO == QFxuEUADHB){QQMYfVSnFy = true;}
      if(rbNNRhweFj == zrAJDrzVsm){FfZYSlsDlY = true;}
      if(PASxYskPWy == yLGJwpVyTN){HslqdKVeHF = true;}
      while(QFxuEUADHB == LLyKnKZadO){OHZGtLcexl = true;}
      while(zrAJDrzVsm == zrAJDrzVsm){jjeWhUDFOh = true;}
      while(yLGJwpVyTN == yLGJwpVyTN){WJxemHTXPg = true;}
      if(tDlWLljOcR == true){tDlWLljOcR = false;}
      if(RRLlxVtKom == true){RRLlxVtKom = false;}
      if(GMOaeEzmzO == true){GMOaeEzmzO = false;}
      if(yCisGwFdyQ == true){yCisGwFdyQ = false;}
      if(HksaUfzTMZ == true){HksaUfzTMZ = false;}
      if(uLIfHhnLqG == true){uLIfHhnLqG = false;}
      if(lxPNTOhSeB == true){lxPNTOhSeB = false;}
      if(QQMYfVSnFy == true){QQMYfVSnFy = false;}
      if(FfZYSlsDlY == true){FfZYSlsDlY = false;}
      if(HslqdKVeHF == true){HslqdKVeHF = false;}
      if(xgnLIezjAk == true){xgnLIezjAk = false;}
      if(PAGsBGWpug == true){PAGsBGWpug = false;}
      if(UefGsWdUtU == true){UefGsWdUtU = false;}
      if(AmfzAXqOQn == true){AmfzAXqOQn = false;}
      if(mJCAJHmspX == true){mJCAJHmspX = false;}
      if(mejajRBhRk == true){mejajRBhRk = false;}
      if(BeoekbTGrc == true){BeoekbTGrc = false;}
      if(OHZGtLcexl == true){OHZGtLcexl = false;}
      if(jjeWhUDFOh == true){jjeWhUDFOh = false;}
      if(WJxemHTXPg == true){WJxemHTXPg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMGEXGEGPL
{ 
  void bVYbkBRSMK()
  { 
      bool GQgeZzOHox = false;
      bool wSpsJAotAA = false;
      bool fQUwYbuQTF = false;
      bool GsXJlTEKBU = false;
      bool pDzaqyPbeu = false;
      bool IVrdOoukGx = false;
      bool DyniqCtfHo = false;
      bool udreKcRsFZ = false;
      bool LTkXxjAsux = false;
      bool XTEDQrPPjn = false;
      bool DiUpzdcNTl = false;
      bool XCffkjMPlG = false;
      bool CAkKRbZoNS = false;
      bool NBIQVbyuYT = false;
      bool GmZIYUnXRg = false;
      bool ezddlDyKXX = false;
      bool DnzAXWsOKI = false;
      bool lRqRzPabkw = false;
      bool mCWgnNWedS = false;
      bool dnWAQSmYjC = false;
      string OXMZeqWMPR;
      string RiTfzBOglx;
      string wqdANFWwCs;
      string SSKUgtJkXL;
      string SRpXcHIjwf;
      string UzdmHXsLMZ;
      string UZJWzyXzzF;
      string rcIZeeAGXF;
      string wlAWYSoWMI;
      string AxYyqrHTYd;
      string iJkqnqpDIc;
      string XmmGciZmxf;
      string IAmpFtEKim;
      string XggtVmAIhh;
      string ckOjkMJRUH;
      string RTVrUhVtls;
      string leUVEpFsjp;
      string hRFODWlDEr;
      string jlpaUEKoYn;
      string QFVnuxQset;
      if(OXMZeqWMPR == iJkqnqpDIc){GQgeZzOHox = true;}
      else if(iJkqnqpDIc == OXMZeqWMPR){DiUpzdcNTl = true;}
      if(RiTfzBOglx == XmmGciZmxf){wSpsJAotAA = true;}
      else if(XmmGciZmxf == RiTfzBOglx){XCffkjMPlG = true;}
      if(wqdANFWwCs == IAmpFtEKim){fQUwYbuQTF = true;}
      else if(IAmpFtEKim == wqdANFWwCs){CAkKRbZoNS = true;}
      if(SSKUgtJkXL == XggtVmAIhh){GsXJlTEKBU = true;}
      else if(XggtVmAIhh == SSKUgtJkXL){NBIQVbyuYT = true;}
      if(SRpXcHIjwf == ckOjkMJRUH){pDzaqyPbeu = true;}
      else if(ckOjkMJRUH == SRpXcHIjwf){GmZIYUnXRg = true;}
      if(UzdmHXsLMZ == RTVrUhVtls){IVrdOoukGx = true;}
      else if(RTVrUhVtls == UzdmHXsLMZ){ezddlDyKXX = true;}
      if(UZJWzyXzzF == leUVEpFsjp){DyniqCtfHo = true;}
      else if(leUVEpFsjp == UZJWzyXzzF){DnzAXWsOKI = true;}
      if(rcIZeeAGXF == hRFODWlDEr){udreKcRsFZ = true;}
      if(wlAWYSoWMI == jlpaUEKoYn){LTkXxjAsux = true;}
      if(AxYyqrHTYd == QFVnuxQset){XTEDQrPPjn = true;}
      while(hRFODWlDEr == rcIZeeAGXF){lRqRzPabkw = true;}
      while(jlpaUEKoYn == jlpaUEKoYn){mCWgnNWedS = true;}
      while(QFVnuxQset == QFVnuxQset){dnWAQSmYjC = true;}
      if(GQgeZzOHox == true){GQgeZzOHox = false;}
      if(wSpsJAotAA == true){wSpsJAotAA = false;}
      if(fQUwYbuQTF == true){fQUwYbuQTF = false;}
      if(GsXJlTEKBU == true){GsXJlTEKBU = false;}
      if(pDzaqyPbeu == true){pDzaqyPbeu = false;}
      if(IVrdOoukGx == true){IVrdOoukGx = false;}
      if(DyniqCtfHo == true){DyniqCtfHo = false;}
      if(udreKcRsFZ == true){udreKcRsFZ = false;}
      if(LTkXxjAsux == true){LTkXxjAsux = false;}
      if(XTEDQrPPjn == true){XTEDQrPPjn = false;}
      if(DiUpzdcNTl == true){DiUpzdcNTl = false;}
      if(XCffkjMPlG == true){XCffkjMPlG = false;}
      if(CAkKRbZoNS == true){CAkKRbZoNS = false;}
      if(NBIQVbyuYT == true){NBIQVbyuYT = false;}
      if(GmZIYUnXRg == true){GmZIYUnXRg = false;}
      if(ezddlDyKXX == true){ezddlDyKXX = false;}
      if(DnzAXWsOKI == true){DnzAXWsOKI = false;}
      if(lRqRzPabkw == true){lRqRzPabkw = false;}
      if(mCWgnNWedS == true){mCWgnNWedS = false;}
      if(dnWAQSmYjC == true){dnWAQSmYjC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGQDCEPBQM
{ 
  void DYVeXiNXrP()
  { 
      bool GZdjmsbUpG = false;
      bool VoIeTtLikn = false;
      bool JzaGuUraWN = false;
      bool PncPRfNeFj = false;
      bool NJXGwhZDdI = false;
      bool bFjnRGyWnR = false;
      bool BAxbqgLrMn = false;
      bool gfcAaAbUKN = false;
      bool tnwOkJDoyL = false;
      bool gpqniMLuPO = false;
      bool VgqpbwcjMR = false;
      bool edMaWNEiqh = false;
      bool dWtAGpooQO = false;
      bool ogFwrNwGlo = false;
      bool gSbgfCcQQV = false;
      bool HbEgjympik = false;
      bool HmSycyYQhJ = false;
      bool QyxBAKuNUD = false;
      bool NXYuGMcXLs = false;
      bool aFWAgtAcDh = false;
      string XTWkgRFnAX;
      string NmdKyEiBcH;
      string ManxrWkKTR;
      string CJrnZSEQxL;
      string bVrbmUxsbx;
      string xwdsMweYsK;
      string fuUhVDtokf;
      string AREQfqiLJX;
      string ZrhVTGfzbc;
      string meXlfgAJGj;
      string aHIwwerNNU;
      string NSPVjnMzOP;
      string XuMHsVtRky;
      string qYFZxRjlYn;
      string NSkGPTPCCq;
      string TBuqMeuADa;
      string kacPdnNoXS;
      string EaZZBFJFqY;
      string GqOsdodNNR;
      string WihyCmoVcb;
      if(XTWkgRFnAX == aHIwwerNNU){GZdjmsbUpG = true;}
      else if(aHIwwerNNU == XTWkgRFnAX){VgqpbwcjMR = true;}
      if(NmdKyEiBcH == NSPVjnMzOP){VoIeTtLikn = true;}
      else if(NSPVjnMzOP == NmdKyEiBcH){edMaWNEiqh = true;}
      if(ManxrWkKTR == XuMHsVtRky){JzaGuUraWN = true;}
      else if(XuMHsVtRky == ManxrWkKTR){dWtAGpooQO = true;}
      if(CJrnZSEQxL == qYFZxRjlYn){PncPRfNeFj = true;}
      else if(qYFZxRjlYn == CJrnZSEQxL){ogFwrNwGlo = true;}
      if(bVrbmUxsbx == NSkGPTPCCq){NJXGwhZDdI = true;}
      else if(NSkGPTPCCq == bVrbmUxsbx){gSbgfCcQQV = true;}
      if(xwdsMweYsK == TBuqMeuADa){bFjnRGyWnR = true;}
      else if(TBuqMeuADa == xwdsMweYsK){HbEgjympik = true;}
      if(fuUhVDtokf == kacPdnNoXS){BAxbqgLrMn = true;}
      else if(kacPdnNoXS == fuUhVDtokf){HmSycyYQhJ = true;}
      if(AREQfqiLJX == EaZZBFJFqY){gfcAaAbUKN = true;}
      if(ZrhVTGfzbc == GqOsdodNNR){tnwOkJDoyL = true;}
      if(meXlfgAJGj == WihyCmoVcb){gpqniMLuPO = true;}
      while(EaZZBFJFqY == AREQfqiLJX){QyxBAKuNUD = true;}
      while(GqOsdodNNR == GqOsdodNNR){NXYuGMcXLs = true;}
      while(WihyCmoVcb == WihyCmoVcb){aFWAgtAcDh = true;}
      if(GZdjmsbUpG == true){GZdjmsbUpG = false;}
      if(VoIeTtLikn == true){VoIeTtLikn = false;}
      if(JzaGuUraWN == true){JzaGuUraWN = false;}
      if(PncPRfNeFj == true){PncPRfNeFj = false;}
      if(NJXGwhZDdI == true){NJXGwhZDdI = false;}
      if(bFjnRGyWnR == true){bFjnRGyWnR = false;}
      if(BAxbqgLrMn == true){BAxbqgLrMn = false;}
      if(gfcAaAbUKN == true){gfcAaAbUKN = false;}
      if(tnwOkJDoyL == true){tnwOkJDoyL = false;}
      if(gpqniMLuPO == true){gpqniMLuPO = false;}
      if(VgqpbwcjMR == true){VgqpbwcjMR = false;}
      if(edMaWNEiqh == true){edMaWNEiqh = false;}
      if(dWtAGpooQO == true){dWtAGpooQO = false;}
      if(ogFwrNwGlo == true){ogFwrNwGlo = false;}
      if(gSbgfCcQQV == true){gSbgfCcQQV = false;}
      if(HbEgjympik == true){HbEgjympik = false;}
      if(HmSycyYQhJ == true){HmSycyYQhJ = false;}
      if(QyxBAKuNUD == true){QyxBAKuNUD = false;}
      if(NXYuGMcXLs == true){NXYuGMcXLs = false;}
      if(aFWAgtAcDh == true){aFWAgtAcDh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APFOECGKCZ
{ 
  void dmwTTDbjxd()
  { 
      bool CYBVEHBhPM = false;
      bool plVUVjQeHl = false;
      bool oEtnjPEODG = false;
      bool OIcyMCNBot = false;
      bool MqNykyclos = false;
      bool ztgNEyeNln = false;
      bool DmdJyhIWHS = false;
      bool WOoMZxpuDk = false;
      bool lSZJGTbPtN = false;
      bool XzPBqYMEAD = false;
      bool oFdVWkFTmG = false;
      bool IiKACkMTCe = false;
      bool FsctuWynUA = false;
      bool kluzwfnElV = false;
      bool NHbmFnoPyG = false;
      bool MsBVxucjZA = false;
      bool lRylVVmKDV = false;
      bool xIggQyQonG = false;
      bool gioOnqjZCA = false;
      bool DDdliwIpRi = false;
      string cOQjTFduoP;
      string yfClGEDrJr;
      string tKgDHHAAHU;
      string gcEfbTGYUA;
      string zwuzGJOYXz;
      string KYtYnRhMbL;
      string EdnUiUaVKm;
      string ydWIrxOgxx;
      string rbbHJHifrK;
      string lswJuVHaPl;
      string isOkBgCkgp;
      string CAPeTcCfKb;
      string kudzBEgNMV;
      string pnRKOzNpGc;
      string ExyBHkdRpS;
      string TbPmAmOOjw;
      string znYKANhEPT;
      string OLZhWmwcrP;
      string aPXsCOYdKb;
      string jzGKdQYnAs;
      if(cOQjTFduoP == isOkBgCkgp){CYBVEHBhPM = true;}
      else if(isOkBgCkgp == cOQjTFduoP){oFdVWkFTmG = true;}
      if(yfClGEDrJr == CAPeTcCfKb){plVUVjQeHl = true;}
      else if(CAPeTcCfKb == yfClGEDrJr){IiKACkMTCe = true;}
      if(tKgDHHAAHU == kudzBEgNMV){oEtnjPEODG = true;}
      else if(kudzBEgNMV == tKgDHHAAHU){FsctuWynUA = true;}
      if(gcEfbTGYUA == pnRKOzNpGc){OIcyMCNBot = true;}
      else if(pnRKOzNpGc == gcEfbTGYUA){kluzwfnElV = true;}
      if(zwuzGJOYXz == ExyBHkdRpS){MqNykyclos = true;}
      else if(ExyBHkdRpS == zwuzGJOYXz){NHbmFnoPyG = true;}
      if(KYtYnRhMbL == TbPmAmOOjw){ztgNEyeNln = true;}
      else if(TbPmAmOOjw == KYtYnRhMbL){MsBVxucjZA = true;}
      if(EdnUiUaVKm == znYKANhEPT){DmdJyhIWHS = true;}
      else if(znYKANhEPT == EdnUiUaVKm){lRylVVmKDV = true;}
      if(ydWIrxOgxx == OLZhWmwcrP){WOoMZxpuDk = true;}
      if(rbbHJHifrK == aPXsCOYdKb){lSZJGTbPtN = true;}
      if(lswJuVHaPl == jzGKdQYnAs){XzPBqYMEAD = true;}
      while(OLZhWmwcrP == ydWIrxOgxx){xIggQyQonG = true;}
      while(aPXsCOYdKb == aPXsCOYdKb){gioOnqjZCA = true;}
      while(jzGKdQYnAs == jzGKdQYnAs){DDdliwIpRi = true;}
      if(CYBVEHBhPM == true){CYBVEHBhPM = false;}
      if(plVUVjQeHl == true){plVUVjQeHl = false;}
      if(oEtnjPEODG == true){oEtnjPEODG = false;}
      if(OIcyMCNBot == true){OIcyMCNBot = false;}
      if(MqNykyclos == true){MqNykyclos = false;}
      if(ztgNEyeNln == true){ztgNEyeNln = false;}
      if(DmdJyhIWHS == true){DmdJyhIWHS = false;}
      if(WOoMZxpuDk == true){WOoMZxpuDk = false;}
      if(lSZJGTbPtN == true){lSZJGTbPtN = false;}
      if(XzPBqYMEAD == true){XzPBqYMEAD = false;}
      if(oFdVWkFTmG == true){oFdVWkFTmG = false;}
      if(IiKACkMTCe == true){IiKACkMTCe = false;}
      if(FsctuWynUA == true){FsctuWynUA = false;}
      if(kluzwfnElV == true){kluzwfnElV = false;}
      if(NHbmFnoPyG == true){NHbmFnoPyG = false;}
      if(MsBVxucjZA == true){MsBVxucjZA = false;}
      if(lRylVVmKDV == true){lRylVVmKDV = false;}
      if(xIggQyQonG == true){xIggQyQonG = false;}
      if(gioOnqjZCA == true){gioOnqjZCA = false;}
      if(DDdliwIpRi == true){DDdliwIpRi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOWMEXDDRO
{ 
  void HwcDLOzxtV()
  { 
      bool VNrFqBrliR = false;
      bool yyDTrIGxJQ = false;
      bool BopknKiTtR = false;
      bool VBHFHSconf = false;
      bool WrkzVBMIWf = false;
      bool YmhJYfWHRg = false;
      bool RYqRuxqyLZ = false;
      bool eQIcsJDpPm = false;
      bool xaxOrhSyfb = false;
      bool uVXHOyATEX = false;
      bool KOxwBHdEPP = false;
      bool bfrdiqbcYM = false;
      bool erRjdJsBOu = false;
      bool IilqcicANj = false;
      bool ENiQzOdsXW = false;
      bool WWuqsRxNSq = false;
      bool OcpTHrtAAA = false;
      bool NbPoIQJBjO = false;
      bool fzcrYknuxL = false;
      bool lPgVVaXOJG = false;
      string cfkyBXyFYJ;
      string dxGVFfAeqF;
      string aVOyzjWiRD;
      string LOzouGHPdw;
      string NluGKRkyDA;
      string jpWdLHRlyR;
      string BPnVyOxRay;
      string XkAtrnZHmg;
      string yYeQSVrUcm;
      string oVQMuxyZIw;
      string UTXFbzoclW;
      string gJzRScjWDc;
      string WbnmICUnyt;
      string pAzqMeBYnT;
      string fOiGGeVysS;
      string MaVeYrfjwY;
      string eAdqffJIFn;
      string aLhjwHsgfc;
      string gVtfgPeURU;
      string zQbOoekrZa;
      if(cfkyBXyFYJ == UTXFbzoclW){VNrFqBrliR = true;}
      else if(UTXFbzoclW == cfkyBXyFYJ){KOxwBHdEPP = true;}
      if(dxGVFfAeqF == gJzRScjWDc){yyDTrIGxJQ = true;}
      else if(gJzRScjWDc == dxGVFfAeqF){bfrdiqbcYM = true;}
      if(aVOyzjWiRD == WbnmICUnyt){BopknKiTtR = true;}
      else if(WbnmICUnyt == aVOyzjWiRD){erRjdJsBOu = true;}
      if(LOzouGHPdw == pAzqMeBYnT){VBHFHSconf = true;}
      else if(pAzqMeBYnT == LOzouGHPdw){IilqcicANj = true;}
      if(NluGKRkyDA == fOiGGeVysS){WrkzVBMIWf = true;}
      else if(fOiGGeVysS == NluGKRkyDA){ENiQzOdsXW = true;}
      if(jpWdLHRlyR == MaVeYrfjwY){YmhJYfWHRg = true;}
      else if(MaVeYrfjwY == jpWdLHRlyR){WWuqsRxNSq = true;}
      if(BPnVyOxRay == eAdqffJIFn){RYqRuxqyLZ = true;}
      else if(eAdqffJIFn == BPnVyOxRay){OcpTHrtAAA = true;}
      if(XkAtrnZHmg == aLhjwHsgfc){eQIcsJDpPm = true;}
      if(yYeQSVrUcm == gVtfgPeURU){xaxOrhSyfb = true;}
      if(oVQMuxyZIw == zQbOoekrZa){uVXHOyATEX = true;}
      while(aLhjwHsgfc == XkAtrnZHmg){NbPoIQJBjO = true;}
      while(gVtfgPeURU == gVtfgPeURU){fzcrYknuxL = true;}
      while(zQbOoekrZa == zQbOoekrZa){lPgVVaXOJG = true;}
      if(VNrFqBrliR == true){VNrFqBrliR = false;}
      if(yyDTrIGxJQ == true){yyDTrIGxJQ = false;}
      if(BopknKiTtR == true){BopknKiTtR = false;}
      if(VBHFHSconf == true){VBHFHSconf = false;}
      if(WrkzVBMIWf == true){WrkzVBMIWf = false;}
      if(YmhJYfWHRg == true){YmhJYfWHRg = false;}
      if(RYqRuxqyLZ == true){RYqRuxqyLZ = false;}
      if(eQIcsJDpPm == true){eQIcsJDpPm = false;}
      if(xaxOrhSyfb == true){xaxOrhSyfb = false;}
      if(uVXHOyATEX == true){uVXHOyATEX = false;}
      if(KOxwBHdEPP == true){KOxwBHdEPP = false;}
      if(bfrdiqbcYM == true){bfrdiqbcYM = false;}
      if(erRjdJsBOu == true){erRjdJsBOu = false;}
      if(IilqcicANj == true){IilqcicANj = false;}
      if(ENiQzOdsXW == true){ENiQzOdsXW = false;}
      if(WWuqsRxNSq == true){WWuqsRxNSq = false;}
      if(OcpTHrtAAA == true){OcpTHrtAAA = false;}
      if(NbPoIQJBjO == true){NbPoIQJBjO = false;}
      if(fzcrYknuxL == true){fzcrYknuxL = false;}
      if(lPgVVaXOJG == true){lPgVVaXOJG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWMLFVHQTB
{ 
  void pBlgCIfsyW()
  { 
      bool JeupzGbJlt = false;
      bool qKunOLbDzQ = false;
      bool EpIIlMtsEX = false;
      bool kkGgElFWuR = false;
      bool HWojhaowSc = false;
      bool LunMsSVmDm = false;
      bool MiFNJFENic = false;
      bool FEIgJgAYaL = false;
      bool WxZaMoxsml = false;
      bool PSSIFYRaZb = false;
      bool VbNoWGmGDM = false;
      bool SxLrQOIdBU = false;
      bool HKZxNmlzbj = false;
      bool OYyyotjjDG = false;
      bool CppaSSGarp = false;
      bool PnZFULBQbj = false;
      bool TmeSxsyMCV = false;
      bool eXZtRQUzdt = false;
      bool gLHkTayrdd = false;
      bool sTITlOLWcZ = false;
      string RhbZfPeLzp;
      string CWUZehmLJQ;
      string rPeIQjHgrM;
      string HdsmGViIPM;
      string BMiTlcrHBO;
      string UNnyTCCTJw;
      string HxTlhYdhSJ;
      string zduwOfgKWm;
      string qzedrtptSE;
      string SPzTEDsxkN;
      string zKorPqRqin;
      string UqxVEHRotn;
      string ijOOpiebrK;
      string mjZJngKmOA;
      string cyLeibSdOw;
      string lDCxdPuZCf;
      string MozXAkRmhX;
      string xeasLjYjeO;
      string QBNuYjgbeY;
      string kkjhnmzmdy;
      if(RhbZfPeLzp == zKorPqRqin){JeupzGbJlt = true;}
      else if(zKorPqRqin == RhbZfPeLzp){VbNoWGmGDM = true;}
      if(CWUZehmLJQ == UqxVEHRotn){qKunOLbDzQ = true;}
      else if(UqxVEHRotn == CWUZehmLJQ){SxLrQOIdBU = true;}
      if(rPeIQjHgrM == ijOOpiebrK){EpIIlMtsEX = true;}
      else if(ijOOpiebrK == rPeIQjHgrM){HKZxNmlzbj = true;}
      if(HdsmGViIPM == mjZJngKmOA){kkGgElFWuR = true;}
      else if(mjZJngKmOA == HdsmGViIPM){OYyyotjjDG = true;}
      if(BMiTlcrHBO == cyLeibSdOw){HWojhaowSc = true;}
      else if(cyLeibSdOw == BMiTlcrHBO){CppaSSGarp = true;}
      if(UNnyTCCTJw == lDCxdPuZCf){LunMsSVmDm = true;}
      else if(lDCxdPuZCf == UNnyTCCTJw){PnZFULBQbj = true;}
      if(HxTlhYdhSJ == MozXAkRmhX){MiFNJFENic = true;}
      else if(MozXAkRmhX == HxTlhYdhSJ){TmeSxsyMCV = true;}
      if(zduwOfgKWm == xeasLjYjeO){FEIgJgAYaL = true;}
      if(qzedrtptSE == QBNuYjgbeY){WxZaMoxsml = true;}
      if(SPzTEDsxkN == kkjhnmzmdy){PSSIFYRaZb = true;}
      while(xeasLjYjeO == zduwOfgKWm){eXZtRQUzdt = true;}
      while(QBNuYjgbeY == QBNuYjgbeY){gLHkTayrdd = true;}
      while(kkjhnmzmdy == kkjhnmzmdy){sTITlOLWcZ = true;}
      if(JeupzGbJlt == true){JeupzGbJlt = false;}
      if(qKunOLbDzQ == true){qKunOLbDzQ = false;}
      if(EpIIlMtsEX == true){EpIIlMtsEX = false;}
      if(kkGgElFWuR == true){kkGgElFWuR = false;}
      if(HWojhaowSc == true){HWojhaowSc = false;}
      if(LunMsSVmDm == true){LunMsSVmDm = false;}
      if(MiFNJFENic == true){MiFNJFENic = false;}
      if(FEIgJgAYaL == true){FEIgJgAYaL = false;}
      if(WxZaMoxsml == true){WxZaMoxsml = false;}
      if(PSSIFYRaZb == true){PSSIFYRaZb = false;}
      if(VbNoWGmGDM == true){VbNoWGmGDM = false;}
      if(SxLrQOIdBU == true){SxLrQOIdBU = false;}
      if(HKZxNmlzbj == true){HKZxNmlzbj = false;}
      if(OYyyotjjDG == true){OYyyotjjDG = false;}
      if(CppaSSGarp == true){CppaSSGarp = false;}
      if(PnZFULBQbj == true){PnZFULBQbj = false;}
      if(TmeSxsyMCV == true){TmeSxsyMCV = false;}
      if(eXZtRQUzdt == true){eXZtRQUzdt = false;}
      if(gLHkTayrdd == true){gLHkTayrdd = false;}
      if(sTITlOLWcZ == true){sTITlOLWcZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XAGLWNOQUU
{ 
  void sLFSQwpGFX()
  { 
      bool MhFjgBcNuQ = false;
      bool zqlLpefXbh = false;
      bool XARpGdDrsZ = false;
      bool wgPCaLJXBJ = false;
      bool lMPKaSkqcs = false;
      bool aSLIxLPPdC = false;
      bool yjUUTSbjje = false;
      bool UHVRuKjHPn = false;
      bool rLOzydUGFP = false;
      bool uttyLBrtpI = false;
      bool pBHyYTwtMl = false;
      bool bIAoJlUUWp = false;
      bool xUdUiaNXGt = false;
      bool SoRGxqEQae = false;
      bool gasSmmsEoZ = false;
      bool fWXzKUWmOx = false;
      bool FYmSTlqsqS = false;
      bool gEtqJVbLgw = false;
      bool gJhgNuRRuc = false;
      bool TRBcZHmZzB = false;
      string sGKZsEWIlr;
      string bGkFsSUcLU;
      string pVQPFXpDiB;
      string XXaCtLwBte;
      string jeAYsuYKqa;
      string AeErMXpuUV;
      string NTYkUEehLg;
      string VShgjKUqVK;
      string yeLIArTioV;
      string VBgYQQFPEo;
      string PqyKEgxWHB;
      string DyZKXhIQjb;
      string jwspKUlJQT;
      string EFmftHgBDS;
      string uxamSXaVAh;
      string IoebETxIzj;
      string unFmwyKsQQ;
      string BGMQgmUFWm;
      string sPIhLOZKbZ;
      string JXCTXGqmpU;
      if(sGKZsEWIlr == PqyKEgxWHB){MhFjgBcNuQ = true;}
      else if(PqyKEgxWHB == sGKZsEWIlr){pBHyYTwtMl = true;}
      if(bGkFsSUcLU == DyZKXhIQjb){zqlLpefXbh = true;}
      else if(DyZKXhIQjb == bGkFsSUcLU){bIAoJlUUWp = true;}
      if(pVQPFXpDiB == jwspKUlJQT){XARpGdDrsZ = true;}
      else if(jwspKUlJQT == pVQPFXpDiB){xUdUiaNXGt = true;}
      if(XXaCtLwBte == EFmftHgBDS){wgPCaLJXBJ = true;}
      else if(EFmftHgBDS == XXaCtLwBte){SoRGxqEQae = true;}
      if(jeAYsuYKqa == uxamSXaVAh){lMPKaSkqcs = true;}
      else if(uxamSXaVAh == jeAYsuYKqa){gasSmmsEoZ = true;}
      if(AeErMXpuUV == IoebETxIzj){aSLIxLPPdC = true;}
      else if(IoebETxIzj == AeErMXpuUV){fWXzKUWmOx = true;}
      if(NTYkUEehLg == unFmwyKsQQ){yjUUTSbjje = true;}
      else if(unFmwyKsQQ == NTYkUEehLg){FYmSTlqsqS = true;}
      if(VShgjKUqVK == BGMQgmUFWm){UHVRuKjHPn = true;}
      if(yeLIArTioV == sPIhLOZKbZ){rLOzydUGFP = true;}
      if(VBgYQQFPEo == JXCTXGqmpU){uttyLBrtpI = true;}
      while(BGMQgmUFWm == VShgjKUqVK){gEtqJVbLgw = true;}
      while(sPIhLOZKbZ == sPIhLOZKbZ){gJhgNuRRuc = true;}
      while(JXCTXGqmpU == JXCTXGqmpU){TRBcZHmZzB = true;}
      if(MhFjgBcNuQ == true){MhFjgBcNuQ = false;}
      if(zqlLpefXbh == true){zqlLpefXbh = false;}
      if(XARpGdDrsZ == true){XARpGdDrsZ = false;}
      if(wgPCaLJXBJ == true){wgPCaLJXBJ = false;}
      if(lMPKaSkqcs == true){lMPKaSkqcs = false;}
      if(aSLIxLPPdC == true){aSLIxLPPdC = false;}
      if(yjUUTSbjje == true){yjUUTSbjje = false;}
      if(UHVRuKjHPn == true){UHVRuKjHPn = false;}
      if(rLOzydUGFP == true){rLOzydUGFP = false;}
      if(uttyLBrtpI == true){uttyLBrtpI = false;}
      if(pBHyYTwtMl == true){pBHyYTwtMl = false;}
      if(bIAoJlUUWp == true){bIAoJlUUWp = false;}
      if(xUdUiaNXGt == true){xUdUiaNXGt = false;}
      if(SoRGxqEQae == true){SoRGxqEQae = false;}
      if(gasSmmsEoZ == true){gasSmmsEoZ = false;}
      if(fWXzKUWmOx == true){fWXzKUWmOx = false;}
      if(FYmSTlqsqS == true){FYmSTlqsqS = false;}
      if(gEtqJVbLgw == true){gEtqJVbLgw = false;}
      if(gJhgNuRRuc == true){gJhgNuRRuc = false;}
      if(TRBcZHmZzB == true){TRBcZHmZzB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEJCIXJSJU
{ 
  void VtgRWRZdCZ()
  { 
      bool BnEObOKZrM = false;
      bool VTmTFfCUDd = false;
      bool sflWdcgcLf = false;
      bool gndWdoBWfx = false;
      bool gAEhkfgSxA = false;
      bool nBRsAUChkz = false;
      bool ggOMfhpPoP = false;
      bool dfoFwsbEkx = false;
      bool wOfKqeVkWJ = false;
      bool mTkgPzkqBD = false;
      bool pQcgVIMLxH = false;
      bool rywmCSBDUA = false;
      bool LEsfbKtIow = false;
      bool HkChHekyoi = false;
      bool SJnOQoWydx = false;
      bool yhWBqkXwEK = false;
      bool NEWAAHuNfX = false;
      bool gDNlhCPdPm = false;
      bool mweryZNBqV = false;
      bool GosdUNmmOI = false;
      string cWqzZWAJBk;
      string JbdIaFFyxf;
      string kxzQYotsVA;
      string kunnEspVbV;
      string wucSiNEmsz;
      string InksrfWaZj;
      string bGnBANnoEh;
      string PiVajoTfgK;
      string kHzVqxKtuY;
      string VPwrsoHbSU;
      string YOiLjYRKJD;
      string LpsOzUHRJC;
      string DtseLAmdgt;
      string hrMLlVXmlR;
      string eAkrNeVgrY;
      string hpRQQeVEAj;
      string lncOVTcgcd;
      string wTeqXDJBRf;
      string dFkHLrZwuG;
      string ATmCfqWVWt;
      if(cWqzZWAJBk == YOiLjYRKJD){BnEObOKZrM = true;}
      else if(YOiLjYRKJD == cWqzZWAJBk){pQcgVIMLxH = true;}
      if(JbdIaFFyxf == LpsOzUHRJC){VTmTFfCUDd = true;}
      else if(LpsOzUHRJC == JbdIaFFyxf){rywmCSBDUA = true;}
      if(kxzQYotsVA == DtseLAmdgt){sflWdcgcLf = true;}
      else if(DtseLAmdgt == kxzQYotsVA){LEsfbKtIow = true;}
      if(kunnEspVbV == hrMLlVXmlR){gndWdoBWfx = true;}
      else if(hrMLlVXmlR == kunnEspVbV){HkChHekyoi = true;}
      if(wucSiNEmsz == eAkrNeVgrY){gAEhkfgSxA = true;}
      else if(eAkrNeVgrY == wucSiNEmsz){SJnOQoWydx = true;}
      if(InksrfWaZj == hpRQQeVEAj){nBRsAUChkz = true;}
      else if(hpRQQeVEAj == InksrfWaZj){yhWBqkXwEK = true;}
      if(bGnBANnoEh == lncOVTcgcd){ggOMfhpPoP = true;}
      else if(lncOVTcgcd == bGnBANnoEh){NEWAAHuNfX = true;}
      if(PiVajoTfgK == wTeqXDJBRf){dfoFwsbEkx = true;}
      if(kHzVqxKtuY == dFkHLrZwuG){wOfKqeVkWJ = true;}
      if(VPwrsoHbSU == ATmCfqWVWt){mTkgPzkqBD = true;}
      while(wTeqXDJBRf == PiVajoTfgK){gDNlhCPdPm = true;}
      while(dFkHLrZwuG == dFkHLrZwuG){mweryZNBqV = true;}
      while(ATmCfqWVWt == ATmCfqWVWt){GosdUNmmOI = true;}
      if(BnEObOKZrM == true){BnEObOKZrM = false;}
      if(VTmTFfCUDd == true){VTmTFfCUDd = false;}
      if(sflWdcgcLf == true){sflWdcgcLf = false;}
      if(gndWdoBWfx == true){gndWdoBWfx = false;}
      if(gAEhkfgSxA == true){gAEhkfgSxA = false;}
      if(nBRsAUChkz == true){nBRsAUChkz = false;}
      if(ggOMfhpPoP == true){ggOMfhpPoP = false;}
      if(dfoFwsbEkx == true){dfoFwsbEkx = false;}
      if(wOfKqeVkWJ == true){wOfKqeVkWJ = false;}
      if(mTkgPzkqBD == true){mTkgPzkqBD = false;}
      if(pQcgVIMLxH == true){pQcgVIMLxH = false;}
      if(rywmCSBDUA == true){rywmCSBDUA = false;}
      if(LEsfbKtIow == true){LEsfbKtIow = false;}
      if(HkChHekyoi == true){HkChHekyoi = false;}
      if(SJnOQoWydx == true){SJnOQoWydx = false;}
      if(yhWBqkXwEK == true){yhWBqkXwEK = false;}
      if(NEWAAHuNfX == true){NEWAAHuNfX = false;}
      if(gDNlhCPdPm == true){gDNlhCPdPm = false;}
      if(mweryZNBqV == true){mweryZNBqV = false;}
      if(GosdUNmmOI == true){GosdUNmmOI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WODXAFHPKS
{ 
  void AIbwByFCfd()
  { 
      bool dhXCPGkgqz = false;
      bool ESMRjyHPZP = false;
      bool DqTfTSKLrQ = false;
      bool jyYylKICDL = false;
      bool eTqkAZVJNn = false;
      bool xWnzamOrhw = false;
      bool uYoZPFtNfY = false;
      bool pFMNkizhft = false;
      bool wBxDTMJYXz = false;
      bool uPTGQFeQVt = false;
      bool eIdnyrKaNr = false;
      bool mgMnAtakGC = false;
      bool wUogcZlFxf = false;
      bool DhLkPnXIFa = false;
      bool CiLfLODeGV = false;
      bool dtKTyJSwKX = false;
      bool FFchnEUaYL = false;
      bool VSfezMJJUO = false;
      bool VGzaBJXqlF = false;
      bool VaxgVxFcrG = false;
      string FEPfyuZAwM;
      string TslHnYhYVG;
      string tPkaSxsNdM;
      string ajPSrspbct;
      string DDrmANIRyr;
      string acuGgpSnMB;
      string CMWilicTOt;
      string hFwbCqWxZF;
      string obOklyoJkC;
      string ZBPbrqfIBR;
      string joCDJUgSDp;
      string SVNGMaxkwn;
      string tShMUgpTjL;
      string KNwIVzYKaR;
      string RVGtiEmJPQ;
      string suMNXQGpic;
      string eMirfEZFkM;
      string BmJeVXMmcQ;
      string sgESRPBhkE;
      string ribymFmOOd;
      if(FEPfyuZAwM == joCDJUgSDp){dhXCPGkgqz = true;}
      else if(joCDJUgSDp == FEPfyuZAwM){eIdnyrKaNr = true;}
      if(TslHnYhYVG == SVNGMaxkwn){ESMRjyHPZP = true;}
      else if(SVNGMaxkwn == TslHnYhYVG){mgMnAtakGC = true;}
      if(tPkaSxsNdM == tShMUgpTjL){DqTfTSKLrQ = true;}
      else if(tShMUgpTjL == tPkaSxsNdM){wUogcZlFxf = true;}
      if(ajPSrspbct == KNwIVzYKaR){jyYylKICDL = true;}
      else if(KNwIVzYKaR == ajPSrspbct){DhLkPnXIFa = true;}
      if(DDrmANIRyr == RVGtiEmJPQ){eTqkAZVJNn = true;}
      else if(RVGtiEmJPQ == DDrmANIRyr){CiLfLODeGV = true;}
      if(acuGgpSnMB == suMNXQGpic){xWnzamOrhw = true;}
      else if(suMNXQGpic == acuGgpSnMB){dtKTyJSwKX = true;}
      if(CMWilicTOt == eMirfEZFkM){uYoZPFtNfY = true;}
      else if(eMirfEZFkM == CMWilicTOt){FFchnEUaYL = true;}
      if(hFwbCqWxZF == BmJeVXMmcQ){pFMNkizhft = true;}
      if(obOklyoJkC == sgESRPBhkE){wBxDTMJYXz = true;}
      if(ZBPbrqfIBR == ribymFmOOd){uPTGQFeQVt = true;}
      while(BmJeVXMmcQ == hFwbCqWxZF){VSfezMJJUO = true;}
      while(sgESRPBhkE == sgESRPBhkE){VGzaBJXqlF = true;}
      while(ribymFmOOd == ribymFmOOd){VaxgVxFcrG = true;}
      if(dhXCPGkgqz == true){dhXCPGkgqz = false;}
      if(ESMRjyHPZP == true){ESMRjyHPZP = false;}
      if(DqTfTSKLrQ == true){DqTfTSKLrQ = false;}
      if(jyYylKICDL == true){jyYylKICDL = false;}
      if(eTqkAZVJNn == true){eTqkAZVJNn = false;}
      if(xWnzamOrhw == true){xWnzamOrhw = false;}
      if(uYoZPFtNfY == true){uYoZPFtNfY = false;}
      if(pFMNkizhft == true){pFMNkizhft = false;}
      if(wBxDTMJYXz == true){wBxDTMJYXz = false;}
      if(uPTGQFeQVt == true){uPTGQFeQVt = false;}
      if(eIdnyrKaNr == true){eIdnyrKaNr = false;}
      if(mgMnAtakGC == true){mgMnAtakGC = false;}
      if(wUogcZlFxf == true){wUogcZlFxf = false;}
      if(DhLkPnXIFa == true){DhLkPnXIFa = false;}
      if(CiLfLODeGV == true){CiLfLODeGV = false;}
      if(dtKTyJSwKX == true){dtKTyJSwKX = false;}
      if(FFchnEUaYL == true){FFchnEUaYL = false;}
      if(VSfezMJJUO == true){VSfezMJJUO = false;}
      if(VGzaBJXqlF == true){VGzaBJXqlF = false;}
      if(VaxgVxFcrG == true){VaxgVxFcrG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POFINBGUVS
{ 
  void oKySolixVD()
  { 
      bool tMemdLIuDO = false;
      bool esOuXYwfnm = false;
      bool cLwkKRFuPF = false;
      bool fIJbfmjnPX = false;
      bool SJQuAQapYx = false;
      bool CpjFmiQtbL = false;
      bool GNexhWimPk = false;
      bool oHQQTTuBjt = false;
      bool qPVRDoXEnx = false;
      bool WoMDRFdSMd = false;
      bool gnZnItZSkT = false;
      bool nPJgUpqMtr = false;
      bool yeySOztMyO = false;
      bool pbnGMCogJI = false;
      bool PESUIGffib = false;
      bool NQYTeCoHZI = false;
      bool AMTWcLaDUR = false;
      bool AKCkcsMdJH = false;
      bool TOcWBYCTaK = false;
      bool NhGBHDjuqw = false;
      string iLmDVKPAeI;
      string hCrKgwKuVX;
      string iAuLMeGkYY;
      string EfNhAybuax;
      string gqkkSeQIGL;
      string OadDjiQapp;
      string EdaGDBnJJi;
      string UPTYprPJsh;
      string OxeMJcBJyR;
      string hBEjsCPdhR;
      string pHzWqzHFMq;
      string SHhIbGzOxZ;
      string zdKqBSKifm;
      string ckbbqGyHVK;
      string VwxHyZSwIl;
      string DBgHRLwHVX;
      string nXZYOgfGQU;
      string IqrlEDgDsa;
      string AOasjaETJf;
      string KpkxWyWYsQ;
      if(iLmDVKPAeI == pHzWqzHFMq){tMemdLIuDO = true;}
      else if(pHzWqzHFMq == iLmDVKPAeI){gnZnItZSkT = true;}
      if(hCrKgwKuVX == SHhIbGzOxZ){esOuXYwfnm = true;}
      else if(SHhIbGzOxZ == hCrKgwKuVX){nPJgUpqMtr = true;}
      if(iAuLMeGkYY == zdKqBSKifm){cLwkKRFuPF = true;}
      else if(zdKqBSKifm == iAuLMeGkYY){yeySOztMyO = true;}
      if(EfNhAybuax == ckbbqGyHVK){fIJbfmjnPX = true;}
      else if(ckbbqGyHVK == EfNhAybuax){pbnGMCogJI = true;}
      if(gqkkSeQIGL == VwxHyZSwIl){SJQuAQapYx = true;}
      else if(VwxHyZSwIl == gqkkSeQIGL){PESUIGffib = true;}
      if(OadDjiQapp == DBgHRLwHVX){CpjFmiQtbL = true;}
      else if(DBgHRLwHVX == OadDjiQapp){NQYTeCoHZI = true;}
      if(EdaGDBnJJi == nXZYOgfGQU){GNexhWimPk = true;}
      else if(nXZYOgfGQU == EdaGDBnJJi){AMTWcLaDUR = true;}
      if(UPTYprPJsh == IqrlEDgDsa){oHQQTTuBjt = true;}
      if(OxeMJcBJyR == AOasjaETJf){qPVRDoXEnx = true;}
      if(hBEjsCPdhR == KpkxWyWYsQ){WoMDRFdSMd = true;}
      while(IqrlEDgDsa == UPTYprPJsh){AKCkcsMdJH = true;}
      while(AOasjaETJf == AOasjaETJf){TOcWBYCTaK = true;}
      while(KpkxWyWYsQ == KpkxWyWYsQ){NhGBHDjuqw = true;}
      if(tMemdLIuDO == true){tMemdLIuDO = false;}
      if(esOuXYwfnm == true){esOuXYwfnm = false;}
      if(cLwkKRFuPF == true){cLwkKRFuPF = false;}
      if(fIJbfmjnPX == true){fIJbfmjnPX = false;}
      if(SJQuAQapYx == true){SJQuAQapYx = false;}
      if(CpjFmiQtbL == true){CpjFmiQtbL = false;}
      if(GNexhWimPk == true){GNexhWimPk = false;}
      if(oHQQTTuBjt == true){oHQQTTuBjt = false;}
      if(qPVRDoXEnx == true){qPVRDoXEnx = false;}
      if(WoMDRFdSMd == true){WoMDRFdSMd = false;}
      if(gnZnItZSkT == true){gnZnItZSkT = false;}
      if(nPJgUpqMtr == true){nPJgUpqMtr = false;}
      if(yeySOztMyO == true){yeySOztMyO = false;}
      if(pbnGMCogJI == true){pbnGMCogJI = false;}
      if(PESUIGffib == true){PESUIGffib = false;}
      if(NQYTeCoHZI == true){NQYTeCoHZI = false;}
      if(AMTWcLaDUR == true){AMTWcLaDUR = false;}
      if(AKCkcsMdJH == true){AKCkcsMdJH = false;}
      if(TOcWBYCTaK == true){TOcWBYCTaK = false;}
      if(NhGBHDjuqw == true){NhGBHDjuqw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBYLPXRCRO
{ 
  void kMmgPyWEnN()
  { 
      bool jEVuOrjhDV = false;
      bool wLnxuzckIh = false;
      bool RZKiKfnEIt = false;
      bool mqcRumDisn = false;
      bool PaufLkVPnX = false;
      bool xmpAWJsmkh = false;
      bool EeYJhEhVBH = false;
      bool wsqTSqddXZ = false;
      bool JXQkwzAbtk = false;
      bool sPyLijBlxG = false;
      bool CANfaDwVhf = false;
      bool fOOLYgNnMi = false;
      bool DFaQOfufjh = false;
      bool orgQWIJkJr = false;
      bool DetOFdBllC = false;
      bool WMYOCwYxRt = false;
      bool HPlzpmhynP = false;
      bool WceTeYLMKj = false;
      bool eJshLcTROa = false;
      bool jLTOkmruXS = false;
      string OAwGTqVJlE;
      string nPcTyXcnbu;
      string OwEFKVZWhB;
      string bngdgCCsbQ;
      string iJdFLAzDNQ;
      string tCQbJRwpwx;
      string QzbkcAiylu;
      string UiLLLERztK;
      string VVIRHYWEUP;
      string GMxdzjhsbK;
      string QBRRuKpFQE;
      string zwukbuqJdD;
      string cdcWoIlhMa;
      string WYWitUEpVw;
      string iRnQPJQMCE;
      string sXPXglXtcm;
      string YIsogaYMqG;
      string pAngULpMGf;
      string qYeHgzJzBH;
      string wJMiXaYyio;
      if(OAwGTqVJlE == QBRRuKpFQE){jEVuOrjhDV = true;}
      else if(QBRRuKpFQE == OAwGTqVJlE){CANfaDwVhf = true;}
      if(nPcTyXcnbu == zwukbuqJdD){wLnxuzckIh = true;}
      else if(zwukbuqJdD == nPcTyXcnbu){fOOLYgNnMi = true;}
      if(OwEFKVZWhB == cdcWoIlhMa){RZKiKfnEIt = true;}
      else if(cdcWoIlhMa == OwEFKVZWhB){DFaQOfufjh = true;}
      if(bngdgCCsbQ == WYWitUEpVw){mqcRumDisn = true;}
      else if(WYWitUEpVw == bngdgCCsbQ){orgQWIJkJr = true;}
      if(iJdFLAzDNQ == iRnQPJQMCE){PaufLkVPnX = true;}
      else if(iRnQPJQMCE == iJdFLAzDNQ){DetOFdBllC = true;}
      if(tCQbJRwpwx == sXPXglXtcm){xmpAWJsmkh = true;}
      else if(sXPXglXtcm == tCQbJRwpwx){WMYOCwYxRt = true;}
      if(QzbkcAiylu == YIsogaYMqG){EeYJhEhVBH = true;}
      else if(YIsogaYMqG == QzbkcAiylu){HPlzpmhynP = true;}
      if(UiLLLERztK == pAngULpMGf){wsqTSqddXZ = true;}
      if(VVIRHYWEUP == qYeHgzJzBH){JXQkwzAbtk = true;}
      if(GMxdzjhsbK == wJMiXaYyio){sPyLijBlxG = true;}
      while(pAngULpMGf == UiLLLERztK){WceTeYLMKj = true;}
      while(qYeHgzJzBH == qYeHgzJzBH){eJshLcTROa = true;}
      while(wJMiXaYyio == wJMiXaYyio){jLTOkmruXS = true;}
      if(jEVuOrjhDV == true){jEVuOrjhDV = false;}
      if(wLnxuzckIh == true){wLnxuzckIh = false;}
      if(RZKiKfnEIt == true){RZKiKfnEIt = false;}
      if(mqcRumDisn == true){mqcRumDisn = false;}
      if(PaufLkVPnX == true){PaufLkVPnX = false;}
      if(xmpAWJsmkh == true){xmpAWJsmkh = false;}
      if(EeYJhEhVBH == true){EeYJhEhVBH = false;}
      if(wsqTSqddXZ == true){wsqTSqddXZ = false;}
      if(JXQkwzAbtk == true){JXQkwzAbtk = false;}
      if(sPyLijBlxG == true){sPyLijBlxG = false;}
      if(CANfaDwVhf == true){CANfaDwVhf = false;}
      if(fOOLYgNnMi == true){fOOLYgNnMi = false;}
      if(DFaQOfufjh == true){DFaQOfufjh = false;}
      if(orgQWIJkJr == true){orgQWIJkJr = false;}
      if(DetOFdBllC == true){DetOFdBllC = false;}
      if(WMYOCwYxRt == true){WMYOCwYxRt = false;}
      if(HPlzpmhynP == true){HPlzpmhynP = false;}
      if(WceTeYLMKj == true){WceTeYLMKj = false;}
      if(eJshLcTROa == true){eJshLcTROa = false;}
      if(jLTOkmruXS == true){jLTOkmruXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBPPJMCISW
{ 
  void tKZTSZcMpM()
  { 
      bool NmPgeUVUKO = false;
      bool KYtmFxXEak = false;
      bool BJuHEVVygB = false;
      bool TOzUnuzoBV = false;
      bool icJYxQhRMm = false;
      bool acDAIDrHcJ = false;
      bool zWnJuuYZyK = false;
      bool yhCECYAWKn = false;
      bool mElsaqKzLk = false;
      bool CqMrWLoAcB = false;
      bool qISCnrZzxj = false;
      bool DVxoVtkthE = false;
      bool jYNNHHVJgq = false;
      bool iAsIwekiEh = false;
      bool QLBbhgsXWb = false;
      bool ZtRYRRuFtg = false;
      bool WPRGBCcorq = false;
      bool JBpAmYXkea = false;
      bool OxmEQnhTqd = false;
      bool ienWKAstae = false;
      string igkddBGWqa;
      string ytNDDtCwFK;
      string gLfKrPZKCU;
      string sMEqRFhwgJ;
      string KeYpWjsDhD;
      string OGtEiWBZkO;
      string awUWhlpVly;
      string LFOwABmonH;
      string VWcyGlRAIt;
      string DHKSiOJCIj;
      string tWRirIqyDg;
      string jLldrESWPw;
      string TpMqtEuwMl;
      string qjgDMzEsGy;
      string tSwaKrVfZe;
      string umlMPEJaon;
      string MulRozehQs;
      string zZQRBBskfC;
      string hOWgqExUmI;
      string ocERkzgdkK;
      if(igkddBGWqa == tWRirIqyDg){NmPgeUVUKO = true;}
      else if(tWRirIqyDg == igkddBGWqa){qISCnrZzxj = true;}
      if(ytNDDtCwFK == jLldrESWPw){KYtmFxXEak = true;}
      else if(jLldrESWPw == ytNDDtCwFK){DVxoVtkthE = true;}
      if(gLfKrPZKCU == TpMqtEuwMl){BJuHEVVygB = true;}
      else if(TpMqtEuwMl == gLfKrPZKCU){jYNNHHVJgq = true;}
      if(sMEqRFhwgJ == qjgDMzEsGy){TOzUnuzoBV = true;}
      else if(qjgDMzEsGy == sMEqRFhwgJ){iAsIwekiEh = true;}
      if(KeYpWjsDhD == tSwaKrVfZe){icJYxQhRMm = true;}
      else if(tSwaKrVfZe == KeYpWjsDhD){QLBbhgsXWb = true;}
      if(OGtEiWBZkO == umlMPEJaon){acDAIDrHcJ = true;}
      else if(umlMPEJaon == OGtEiWBZkO){ZtRYRRuFtg = true;}
      if(awUWhlpVly == MulRozehQs){zWnJuuYZyK = true;}
      else if(MulRozehQs == awUWhlpVly){WPRGBCcorq = true;}
      if(LFOwABmonH == zZQRBBskfC){yhCECYAWKn = true;}
      if(VWcyGlRAIt == hOWgqExUmI){mElsaqKzLk = true;}
      if(DHKSiOJCIj == ocERkzgdkK){CqMrWLoAcB = true;}
      while(zZQRBBskfC == LFOwABmonH){JBpAmYXkea = true;}
      while(hOWgqExUmI == hOWgqExUmI){OxmEQnhTqd = true;}
      while(ocERkzgdkK == ocERkzgdkK){ienWKAstae = true;}
      if(NmPgeUVUKO == true){NmPgeUVUKO = false;}
      if(KYtmFxXEak == true){KYtmFxXEak = false;}
      if(BJuHEVVygB == true){BJuHEVVygB = false;}
      if(TOzUnuzoBV == true){TOzUnuzoBV = false;}
      if(icJYxQhRMm == true){icJYxQhRMm = false;}
      if(acDAIDrHcJ == true){acDAIDrHcJ = false;}
      if(zWnJuuYZyK == true){zWnJuuYZyK = false;}
      if(yhCECYAWKn == true){yhCECYAWKn = false;}
      if(mElsaqKzLk == true){mElsaqKzLk = false;}
      if(CqMrWLoAcB == true){CqMrWLoAcB = false;}
      if(qISCnrZzxj == true){qISCnrZzxj = false;}
      if(DVxoVtkthE == true){DVxoVtkthE = false;}
      if(jYNNHHVJgq == true){jYNNHHVJgq = false;}
      if(iAsIwekiEh == true){iAsIwekiEh = false;}
      if(QLBbhgsXWb == true){QLBbhgsXWb = false;}
      if(ZtRYRRuFtg == true){ZtRYRRuFtg = false;}
      if(WPRGBCcorq == true){WPRGBCcorq = false;}
      if(JBpAmYXkea == true){JBpAmYXkea = false;}
      if(OxmEQnhTqd == true){OxmEQnhTqd = false;}
      if(ienWKAstae == true){ienWKAstae = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXEZNMNRPM
{ 
  void yJXkgIRGta()
  { 
      bool XQrEDVEKnw = false;
      bool tQRYRuioZo = false;
      bool UbknXStuyk = false;
      bool YYwOApnxfC = false;
      bool ERjCEwIneO = false;
      bool ViQDwwfDfj = false;
      bool bIMDWUTDYa = false;
      bool GkJWjCqiib = false;
      bool JFQiOoHrSD = false;
      bool KkQuawFgej = false;
      bool bFODIkZsSs = false;
      bool EwTEaVrcng = false;
      bool MbjUQVUOwn = false;
      bool xKEzAEqMad = false;
      bool PNZZzNQMUF = false;
      bool EcrxWzUtmm = false;
      bool QLxdwtrUDV = false;
      bool eeBKRyBKVC = false;
      bool FHsqjURGbA = false;
      bool jxYnNEQudF = false;
      string tzfsfryfRd;
      string BgCNZTfhsU;
      string rpdWbYJZQz;
      string dDnWLzkryx;
      string VZfMnGTsUO;
      string ZLAzXDVJRH;
      string hYPSAyrfBZ;
      string imiuzRJQhV;
      string EPFBYSCnyI;
      string dbaqPxKNMp;
      string NmqtfmbEAG;
      string tFauCRSNtg;
      string uDhswHLqfC;
      string GwErIRYKUk;
      string pxnrNYAeox;
      string dxTetJFxxY;
      string akYxzxAimj;
      string sHrIpyPoeX;
      string HfCiXJcYyy;
      string MaNwJFYpsQ;
      if(tzfsfryfRd == NmqtfmbEAG){XQrEDVEKnw = true;}
      else if(NmqtfmbEAG == tzfsfryfRd){bFODIkZsSs = true;}
      if(BgCNZTfhsU == tFauCRSNtg){tQRYRuioZo = true;}
      else if(tFauCRSNtg == BgCNZTfhsU){EwTEaVrcng = true;}
      if(rpdWbYJZQz == uDhswHLqfC){UbknXStuyk = true;}
      else if(uDhswHLqfC == rpdWbYJZQz){MbjUQVUOwn = true;}
      if(dDnWLzkryx == GwErIRYKUk){YYwOApnxfC = true;}
      else if(GwErIRYKUk == dDnWLzkryx){xKEzAEqMad = true;}
      if(VZfMnGTsUO == pxnrNYAeox){ERjCEwIneO = true;}
      else if(pxnrNYAeox == VZfMnGTsUO){PNZZzNQMUF = true;}
      if(ZLAzXDVJRH == dxTetJFxxY){ViQDwwfDfj = true;}
      else if(dxTetJFxxY == ZLAzXDVJRH){EcrxWzUtmm = true;}
      if(hYPSAyrfBZ == akYxzxAimj){bIMDWUTDYa = true;}
      else if(akYxzxAimj == hYPSAyrfBZ){QLxdwtrUDV = true;}
      if(imiuzRJQhV == sHrIpyPoeX){GkJWjCqiib = true;}
      if(EPFBYSCnyI == HfCiXJcYyy){JFQiOoHrSD = true;}
      if(dbaqPxKNMp == MaNwJFYpsQ){KkQuawFgej = true;}
      while(sHrIpyPoeX == imiuzRJQhV){eeBKRyBKVC = true;}
      while(HfCiXJcYyy == HfCiXJcYyy){FHsqjURGbA = true;}
      while(MaNwJFYpsQ == MaNwJFYpsQ){jxYnNEQudF = true;}
      if(XQrEDVEKnw == true){XQrEDVEKnw = false;}
      if(tQRYRuioZo == true){tQRYRuioZo = false;}
      if(UbknXStuyk == true){UbknXStuyk = false;}
      if(YYwOApnxfC == true){YYwOApnxfC = false;}
      if(ERjCEwIneO == true){ERjCEwIneO = false;}
      if(ViQDwwfDfj == true){ViQDwwfDfj = false;}
      if(bIMDWUTDYa == true){bIMDWUTDYa = false;}
      if(GkJWjCqiib == true){GkJWjCqiib = false;}
      if(JFQiOoHrSD == true){JFQiOoHrSD = false;}
      if(KkQuawFgej == true){KkQuawFgej = false;}
      if(bFODIkZsSs == true){bFODIkZsSs = false;}
      if(EwTEaVrcng == true){EwTEaVrcng = false;}
      if(MbjUQVUOwn == true){MbjUQVUOwn = false;}
      if(xKEzAEqMad == true){xKEzAEqMad = false;}
      if(PNZZzNQMUF == true){PNZZzNQMUF = false;}
      if(EcrxWzUtmm == true){EcrxWzUtmm = false;}
      if(QLxdwtrUDV == true){QLxdwtrUDV = false;}
      if(eeBKRyBKVC == true){eeBKRyBKVC = false;}
      if(FHsqjURGbA == true){FHsqjURGbA = false;}
      if(jxYnNEQudF == true){jxYnNEQudF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOKACVWJSC
{ 
  void VfkmiLePWH()
  { 
      bool ZLbXoYjDZr = false;
      bool bkUowfcSJm = false;
      bool RJWGHjLdLs = false;
      bool zJZhFBWfdJ = false;
      bool hbjSeZNHbA = false;
      bool mKmMCPoUPF = false;
      bool NFqfrSLliu = false;
      bool JwoAFpYDbh = false;
      bool VDCLFnWMfp = false;
      bool LBPYwbjDZM = false;
      bool NaYgqpVlHM = false;
      bool qlshiKDfZE = false;
      bool uyGsiHfPEd = false;
      bool FUcOTueVTP = false;
      bool SjFSyZHhok = false;
      bool XEcVQOTexi = false;
      bool JFhcHVIdNn = false;
      bool fhLKkLsntJ = false;
      bool zyaSFArHyE = false;
      bool azXkFMBbLc = false;
      string UJzaATaNZF;
      string fjpBnhEGKX;
      string dSJnAyymel;
      string YElwqHSUhC;
      string xEoXqdkBaf;
      string EAXkhBzKZC;
      string VnimfaytJg;
      string OiYIaZclwV;
      string NxMyhYfAOp;
      string HHtegJVCqP;
      string fqqtQUaOKI;
      string XNNEoXajFH;
      string txeTYHotbQ;
      string DatfpVFRhM;
      string xQpFRssppI;
      string hlwjViLWUJ;
      string fgmsFxTgNS;
      string SIBsJcGZCf;
      string NzDTiReKKH;
      string KhxXgQdxAT;
      if(UJzaATaNZF == fqqtQUaOKI){ZLbXoYjDZr = true;}
      else if(fqqtQUaOKI == UJzaATaNZF){NaYgqpVlHM = true;}
      if(fjpBnhEGKX == XNNEoXajFH){bkUowfcSJm = true;}
      else if(XNNEoXajFH == fjpBnhEGKX){qlshiKDfZE = true;}
      if(dSJnAyymel == txeTYHotbQ){RJWGHjLdLs = true;}
      else if(txeTYHotbQ == dSJnAyymel){uyGsiHfPEd = true;}
      if(YElwqHSUhC == DatfpVFRhM){zJZhFBWfdJ = true;}
      else if(DatfpVFRhM == YElwqHSUhC){FUcOTueVTP = true;}
      if(xEoXqdkBaf == xQpFRssppI){hbjSeZNHbA = true;}
      else if(xQpFRssppI == xEoXqdkBaf){SjFSyZHhok = true;}
      if(EAXkhBzKZC == hlwjViLWUJ){mKmMCPoUPF = true;}
      else if(hlwjViLWUJ == EAXkhBzKZC){XEcVQOTexi = true;}
      if(VnimfaytJg == fgmsFxTgNS){NFqfrSLliu = true;}
      else if(fgmsFxTgNS == VnimfaytJg){JFhcHVIdNn = true;}
      if(OiYIaZclwV == SIBsJcGZCf){JwoAFpYDbh = true;}
      if(NxMyhYfAOp == NzDTiReKKH){VDCLFnWMfp = true;}
      if(HHtegJVCqP == KhxXgQdxAT){LBPYwbjDZM = true;}
      while(SIBsJcGZCf == OiYIaZclwV){fhLKkLsntJ = true;}
      while(NzDTiReKKH == NzDTiReKKH){zyaSFArHyE = true;}
      while(KhxXgQdxAT == KhxXgQdxAT){azXkFMBbLc = true;}
      if(ZLbXoYjDZr == true){ZLbXoYjDZr = false;}
      if(bkUowfcSJm == true){bkUowfcSJm = false;}
      if(RJWGHjLdLs == true){RJWGHjLdLs = false;}
      if(zJZhFBWfdJ == true){zJZhFBWfdJ = false;}
      if(hbjSeZNHbA == true){hbjSeZNHbA = false;}
      if(mKmMCPoUPF == true){mKmMCPoUPF = false;}
      if(NFqfrSLliu == true){NFqfrSLliu = false;}
      if(JwoAFpYDbh == true){JwoAFpYDbh = false;}
      if(VDCLFnWMfp == true){VDCLFnWMfp = false;}
      if(LBPYwbjDZM == true){LBPYwbjDZM = false;}
      if(NaYgqpVlHM == true){NaYgqpVlHM = false;}
      if(qlshiKDfZE == true){qlshiKDfZE = false;}
      if(uyGsiHfPEd == true){uyGsiHfPEd = false;}
      if(FUcOTueVTP == true){FUcOTueVTP = false;}
      if(SjFSyZHhok == true){SjFSyZHhok = false;}
      if(XEcVQOTexi == true){XEcVQOTexi = false;}
      if(JFhcHVIdNn == true){JFhcHVIdNn = false;}
      if(fhLKkLsntJ == true){fhLKkLsntJ = false;}
      if(zyaSFArHyE == true){zyaSFArHyE = false;}
      if(azXkFMBbLc == true){azXkFMBbLc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVSTRPIHYQ
{ 
  void EpOqDdIUOe()
  { 
      bool nOHlYYQXUe = false;
      bool VIVtJgBjpW = false;
      bool WBWEDDXkxx = false;
      bool xYJaoVXrNV = false;
      bool VkhHUqEoyl = false;
      bool ATjqXmqDhV = false;
      bool AfZXhwzuEn = false;
      bool IJVTBlSPiL = false;
      bool yilLxcnRCC = false;
      bool dUJrUoKKZY = false;
      bool rJjJcpxPpk = false;
      bool TbTVWRsNaE = false;
      bool HhrCKmzdyL = false;
      bool bIpKToyciG = false;
      bool fYbRhCBmUC = false;
      bool wwjUQKQhzo = false;
      bool pSRdJLlJCh = false;
      bool TQeTXiFaTI = false;
      bool lLJwPeYUsJ = false;
      bool YPcsPNHxHW = false;
      string BqHzGzAXpz;
      string HgINLVATtZ;
      string HqqBCLulVR;
      string hqAiNUJHWE;
      string HGJSYLCnkQ;
      string oyDdGKAGxu;
      string ENBYRPgYAq;
      string MsxpSAgYbp;
      string JHAFbjnVcD;
      string TDJbAsFkBI;
      string ecntDwBMKF;
      string cbdGkwNuwg;
      string bKwwWJiUpZ;
      string uwWTLgSGCf;
      string haKXarYDpD;
      string eJnTfUgrXt;
      string MfWkJfEKuE;
      string dGsQzBzXVd;
      string jfdmtlIDmp;
      string AaiISBDZOu;
      if(BqHzGzAXpz == ecntDwBMKF){nOHlYYQXUe = true;}
      else if(ecntDwBMKF == BqHzGzAXpz){rJjJcpxPpk = true;}
      if(HgINLVATtZ == cbdGkwNuwg){VIVtJgBjpW = true;}
      else if(cbdGkwNuwg == HgINLVATtZ){TbTVWRsNaE = true;}
      if(HqqBCLulVR == bKwwWJiUpZ){WBWEDDXkxx = true;}
      else if(bKwwWJiUpZ == HqqBCLulVR){HhrCKmzdyL = true;}
      if(hqAiNUJHWE == uwWTLgSGCf){xYJaoVXrNV = true;}
      else if(uwWTLgSGCf == hqAiNUJHWE){bIpKToyciG = true;}
      if(HGJSYLCnkQ == haKXarYDpD){VkhHUqEoyl = true;}
      else if(haKXarYDpD == HGJSYLCnkQ){fYbRhCBmUC = true;}
      if(oyDdGKAGxu == eJnTfUgrXt){ATjqXmqDhV = true;}
      else if(eJnTfUgrXt == oyDdGKAGxu){wwjUQKQhzo = true;}
      if(ENBYRPgYAq == MfWkJfEKuE){AfZXhwzuEn = true;}
      else if(MfWkJfEKuE == ENBYRPgYAq){pSRdJLlJCh = true;}
      if(MsxpSAgYbp == dGsQzBzXVd){IJVTBlSPiL = true;}
      if(JHAFbjnVcD == jfdmtlIDmp){yilLxcnRCC = true;}
      if(TDJbAsFkBI == AaiISBDZOu){dUJrUoKKZY = true;}
      while(dGsQzBzXVd == MsxpSAgYbp){TQeTXiFaTI = true;}
      while(jfdmtlIDmp == jfdmtlIDmp){lLJwPeYUsJ = true;}
      while(AaiISBDZOu == AaiISBDZOu){YPcsPNHxHW = true;}
      if(nOHlYYQXUe == true){nOHlYYQXUe = false;}
      if(VIVtJgBjpW == true){VIVtJgBjpW = false;}
      if(WBWEDDXkxx == true){WBWEDDXkxx = false;}
      if(xYJaoVXrNV == true){xYJaoVXrNV = false;}
      if(VkhHUqEoyl == true){VkhHUqEoyl = false;}
      if(ATjqXmqDhV == true){ATjqXmqDhV = false;}
      if(AfZXhwzuEn == true){AfZXhwzuEn = false;}
      if(IJVTBlSPiL == true){IJVTBlSPiL = false;}
      if(yilLxcnRCC == true){yilLxcnRCC = false;}
      if(dUJrUoKKZY == true){dUJrUoKKZY = false;}
      if(rJjJcpxPpk == true){rJjJcpxPpk = false;}
      if(TbTVWRsNaE == true){TbTVWRsNaE = false;}
      if(HhrCKmzdyL == true){HhrCKmzdyL = false;}
      if(bIpKToyciG == true){bIpKToyciG = false;}
      if(fYbRhCBmUC == true){fYbRhCBmUC = false;}
      if(wwjUQKQhzo == true){wwjUQKQhzo = false;}
      if(pSRdJLlJCh == true){pSRdJLlJCh = false;}
      if(TQeTXiFaTI == true){TQeTXiFaTI = false;}
      if(lLJwPeYUsJ == true){lLJwPeYUsJ = false;}
      if(YPcsPNHxHW == true){YPcsPNHxHW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXBWACPXVS
{ 
  void okoOLUSoim()
  { 
      bool DiWMgNnsUH = false;
      bool nSMJgkCYwX = false;
      bool LyIpFEFYIU = false;
      bool kcwwLwYKsG = false;
      bool JRSxQHYkQd = false;
      bool sHFAgEZgGc = false;
      bool IPkAVLWPxj = false;
      bool MrfpOtfKYy = false;
      bool fTIdadWuPG = false;
      bool WqDQysgSaF = false;
      bool jJngRBbPlm = false;
      bool YOHHxnHGYr = false;
      bool nbApMUnOrU = false;
      bool MMiTOWfaLZ = false;
      bool BHIbgHiwTJ = false;
      bool lZsiQIIxTx = false;
      bool MNWRZLemra = false;
      bool HftyqfSXIE = false;
      bool kruhimSACG = false;
      bool NhHOMmjqBV = false;
      string SaZiZwCozt;
      string QGxqTTtBbW;
      string VIQUZNWjKm;
      string zhnGXLxuza;
      string CVwSLjuakL;
      string upAUfJJEJM;
      string YSeLtiRqSH;
      string VzCATzLxJp;
      string RuyzrIhTaN;
      string CskmBjpjXb;
      string REHdounzAf;
      string yMuStdUfTl;
      string ByPFFcOOzj;
      string JaZgXNmTJw;
      string UhSuPpxRrX;
      string OKQlaTnCYM;
      string gYAQWWlOtf;
      string pAVXQSeUpP;
      string fwWaUyKnFE;
      string ZkuxPwgCYs;
      if(SaZiZwCozt == REHdounzAf){DiWMgNnsUH = true;}
      else if(REHdounzAf == SaZiZwCozt){jJngRBbPlm = true;}
      if(QGxqTTtBbW == yMuStdUfTl){nSMJgkCYwX = true;}
      else if(yMuStdUfTl == QGxqTTtBbW){YOHHxnHGYr = true;}
      if(VIQUZNWjKm == ByPFFcOOzj){LyIpFEFYIU = true;}
      else if(ByPFFcOOzj == VIQUZNWjKm){nbApMUnOrU = true;}
      if(zhnGXLxuza == JaZgXNmTJw){kcwwLwYKsG = true;}
      else if(JaZgXNmTJw == zhnGXLxuza){MMiTOWfaLZ = true;}
      if(CVwSLjuakL == UhSuPpxRrX){JRSxQHYkQd = true;}
      else if(UhSuPpxRrX == CVwSLjuakL){BHIbgHiwTJ = true;}
      if(upAUfJJEJM == OKQlaTnCYM){sHFAgEZgGc = true;}
      else if(OKQlaTnCYM == upAUfJJEJM){lZsiQIIxTx = true;}
      if(YSeLtiRqSH == gYAQWWlOtf){IPkAVLWPxj = true;}
      else if(gYAQWWlOtf == YSeLtiRqSH){MNWRZLemra = true;}
      if(VzCATzLxJp == pAVXQSeUpP){MrfpOtfKYy = true;}
      if(RuyzrIhTaN == fwWaUyKnFE){fTIdadWuPG = true;}
      if(CskmBjpjXb == ZkuxPwgCYs){WqDQysgSaF = true;}
      while(pAVXQSeUpP == VzCATzLxJp){HftyqfSXIE = true;}
      while(fwWaUyKnFE == fwWaUyKnFE){kruhimSACG = true;}
      while(ZkuxPwgCYs == ZkuxPwgCYs){NhHOMmjqBV = true;}
      if(DiWMgNnsUH == true){DiWMgNnsUH = false;}
      if(nSMJgkCYwX == true){nSMJgkCYwX = false;}
      if(LyIpFEFYIU == true){LyIpFEFYIU = false;}
      if(kcwwLwYKsG == true){kcwwLwYKsG = false;}
      if(JRSxQHYkQd == true){JRSxQHYkQd = false;}
      if(sHFAgEZgGc == true){sHFAgEZgGc = false;}
      if(IPkAVLWPxj == true){IPkAVLWPxj = false;}
      if(MrfpOtfKYy == true){MrfpOtfKYy = false;}
      if(fTIdadWuPG == true){fTIdadWuPG = false;}
      if(WqDQysgSaF == true){WqDQysgSaF = false;}
      if(jJngRBbPlm == true){jJngRBbPlm = false;}
      if(YOHHxnHGYr == true){YOHHxnHGYr = false;}
      if(nbApMUnOrU == true){nbApMUnOrU = false;}
      if(MMiTOWfaLZ == true){MMiTOWfaLZ = false;}
      if(BHIbgHiwTJ == true){BHIbgHiwTJ = false;}
      if(lZsiQIIxTx == true){lZsiQIIxTx = false;}
      if(MNWRZLemra == true){MNWRZLemra = false;}
      if(HftyqfSXIE == true){HftyqfSXIE = false;}
      if(kruhimSACG == true){kruhimSACG = false;}
      if(NhHOMmjqBV == true){NhHOMmjqBV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJKGGMURVG
{ 
  void BGdmhLMfLt()
  { 
      bool ZgVjhzhkhK = false;
      bool caJPnnUgHF = false;
      bool CMoFsTxskH = false;
      bool CKgeNLkHZx = false;
      bool TJKxNjBrJH = false;
      bool iyViXNqPpO = false;
      bool CoAZISsdBb = false;
      bool DNHJlsCrqI = false;
      bool REjcXDnyHA = false;
      bool UUQKueIjnu = false;
      bool pXqgDUqMxd = false;
      bool LyYgwyEWCE = false;
      bool euWBHiwwOG = false;
      bool kRDwRtNCZC = false;
      bool MaBcoVwiOx = false;
      bool alhiQuApZU = false;
      bool YtxqssucPC = false;
      bool jBxzrDtsLl = false;
      bool lMhReyiUeW = false;
      bool sXcEdRdJiu = false;
      string DSPIhzHhST;
      string LrtPRUbUfD;
      string QkRWEuaDhf;
      string hebpCYVdnq;
      string bteIbFUGRB;
      string TYzjHRBsEm;
      string YEAllgPDNs;
      string zygnaWGIuy;
      string ZTlfMIerij;
      string XbYBSXtrWt;
      string oRsYCUrKIk;
      string LryFMFSUYc;
      string BXTdUWZeVD;
      string bNlAIIZMcq;
      string QUixXfdSnN;
      string FZSsrRxOEf;
      string uMoFIxFxxE;
      string eFqgLgnVFn;
      string rGqIxCtrHq;
      string LKIxwEedoa;
      if(DSPIhzHhST == oRsYCUrKIk){ZgVjhzhkhK = true;}
      else if(oRsYCUrKIk == DSPIhzHhST){pXqgDUqMxd = true;}
      if(LrtPRUbUfD == LryFMFSUYc){caJPnnUgHF = true;}
      else if(LryFMFSUYc == LrtPRUbUfD){LyYgwyEWCE = true;}
      if(QkRWEuaDhf == BXTdUWZeVD){CMoFsTxskH = true;}
      else if(BXTdUWZeVD == QkRWEuaDhf){euWBHiwwOG = true;}
      if(hebpCYVdnq == bNlAIIZMcq){CKgeNLkHZx = true;}
      else if(bNlAIIZMcq == hebpCYVdnq){kRDwRtNCZC = true;}
      if(bteIbFUGRB == QUixXfdSnN){TJKxNjBrJH = true;}
      else if(QUixXfdSnN == bteIbFUGRB){MaBcoVwiOx = true;}
      if(TYzjHRBsEm == FZSsrRxOEf){iyViXNqPpO = true;}
      else if(FZSsrRxOEf == TYzjHRBsEm){alhiQuApZU = true;}
      if(YEAllgPDNs == uMoFIxFxxE){CoAZISsdBb = true;}
      else if(uMoFIxFxxE == YEAllgPDNs){YtxqssucPC = true;}
      if(zygnaWGIuy == eFqgLgnVFn){DNHJlsCrqI = true;}
      if(ZTlfMIerij == rGqIxCtrHq){REjcXDnyHA = true;}
      if(XbYBSXtrWt == LKIxwEedoa){UUQKueIjnu = true;}
      while(eFqgLgnVFn == zygnaWGIuy){jBxzrDtsLl = true;}
      while(rGqIxCtrHq == rGqIxCtrHq){lMhReyiUeW = true;}
      while(LKIxwEedoa == LKIxwEedoa){sXcEdRdJiu = true;}
      if(ZgVjhzhkhK == true){ZgVjhzhkhK = false;}
      if(caJPnnUgHF == true){caJPnnUgHF = false;}
      if(CMoFsTxskH == true){CMoFsTxskH = false;}
      if(CKgeNLkHZx == true){CKgeNLkHZx = false;}
      if(TJKxNjBrJH == true){TJKxNjBrJH = false;}
      if(iyViXNqPpO == true){iyViXNqPpO = false;}
      if(CoAZISsdBb == true){CoAZISsdBb = false;}
      if(DNHJlsCrqI == true){DNHJlsCrqI = false;}
      if(REjcXDnyHA == true){REjcXDnyHA = false;}
      if(UUQKueIjnu == true){UUQKueIjnu = false;}
      if(pXqgDUqMxd == true){pXqgDUqMxd = false;}
      if(LyYgwyEWCE == true){LyYgwyEWCE = false;}
      if(euWBHiwwOG == true){euWBHiwwOG = false;}
      if(kRDwRtNCZC == true){kRDwRtNCZC = false;}
      if(MaBcoVwiOx == true){MaBcoVwiOx = false;}
      if(alhiQuApZU == true){alhiQuApZU = false;}
      if(YtxqssucPC == true){YtxqssucPC = false;}
      if(jBxzrDtsLl == true){jBxzrDtsLl = false;}
      if(lMhReyiUeW == true){lMhReyiUeW = false;}
      if(sXcEdRdJiu == true){sXcEdRdJiu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSVBIBAQUK
{ 
  void xHYPJHRjDl()
  { 
      bool BxafXTDosj = false;
      bool nyEzltysuG = false;
      bool XAbkHDxiPd = false;
      bool GwckonUfAW = false;
      bool wFywpCElum = false;
      bool HVOiqBVpYT = false;
      bool VUZOcrUTJy = false;
      bool YRrYJRCetE = false;
      bool zLmbWkgstn = false;
      bool SeHgAafjSy = false;
      bool gkbxNodpZZ = false;
      bool zpuTUJhxrr = false;
      bool KbYVetKLXh = false;
      bool kRLwWNjpNg = false;
      bool GqTUnbimLq = false;
      bool siqamFLGRT = false;
      bool eSRrngdzwH = false;
      bool ZqiLkSIEgC = false;
      bool KWAgnCakIR = false;
      bool BdXtCnZafH = false;
      string zLFDphpTJd;
      string XnCiIcCEQl;
      string yMBQtREZap;
      string CLLOTQmmnr;
      string ekYEVYTCUE;
      string qbBlomJnJY;
      string dQsSaMbnOr;
      string oPQYHMmxtU;
      string xBEVzaJZYg;
      string GydPNOqFcI;
      string wfmbPbKcdb;
      string zMsnabLWTA;
      string DBOhkqlBKs;
      string UgUlYRObGW;
      string PguwgtEpok;
      string CUlcFtQFqY;
      string pJRkGSrHOI;
      string NiQwjVGSAq;
      string lwLYpAuqfd;
      string BJkhgFOJoO;
      if(zLFDphpTJd == wfmbPbKcdb){BxafXTDosj = true;}
      else if(wfmbPbKcdb == zLFDphpTJd){gkbxNodpZZ = true;}
      if(XnCiIcCEQl == zMsnabLWTA){nyEzltysuG = true;}
      else if(zMsnabLWTA == XnCiIcCEQl){zpuTUJhxrr = true;}
      if(yMBQtREZap == DBOhkqlBKs){XAbkHDxiPd = true;}
      else if(DBOhkqlBKs == yMBQtREZap){KbYVetKLXh = true;}
      if(CLLOTQmmnr == UgUlYRObGW){GwckonUfAW = true;}
      else if(UgUlYRObGW == CLLOTQmmnr){kRLwWNjpNg = true;}
      if(ekYEVYTCUE == PguwgtEpok){wFywpCElum = true;}
      else if(PguwgtEpok == ekYEVYTCUE){GqTUnbimLq = true;}
      if(qbBlomJnJY == CUlcFtQFqY){HVOiqBVpYT = true;}
      else if(CUlcFtQFqY == qbBlomJnJY){siqamFLGRT = true;}
      if(dQsSaMbnOr == pJRkGSrHOI){VUZOcrUTJy = true;}
      else if(pJRkGSrHOI == dQsSaMbnOr){eSRrngdzwH = true;}
      if(oPQYHMmxtU == NiQwjVGSAq){YRrYJRCetE = true;}
      if(xBEVzaJZYg == lwLYpAuqfd){zLmbWkgstn = true;}
      if(GydPNOqFcI == BJkhgFOJoO){SeHgAafjSy = true;}
      while(NiQwjVGSAq == oPQYHMmxtU){ZqiLkSIEgC = true;}
      while(lwLYpAuqfd == lwLYpAuqfd){KWAgnCakIR = true;}
      while(BJkhgFOJoO == BJkhgFOJoO){BdXtCnZafH = true;}
      if(BxafXTDosj == true){BxafXTDosj = false;}
      if(nyEzltysuG == true){nyEzltysuG = false;}
      if(XAbkHDxiPd == true){XAbkHDxiPd = false;}
      if(GwckonUfAW == true){GwckonUfAW = false;}
      if(wFywpCElum == true){wFywpCElum = false;}
      if(HVOiqBVpYT == true){HVOiqBVpYT = false;}
      if(VUZOcrUTJy == true){VUZOcrUTJy = false;}
      if(YRrYJRCetE == true){YRrYJRCetE = false;}
      if(zLmbWkgstn == true){zLmbWkgstn = false;}
      if(SeHgAafjSy == true){SeHgAafjSy = false;}
      if(gkbxNodpZZ == true){gkbxNodpZZ = false;}
      if(zpuTUJhxrr == true){zpuTUJhxrr = false;}
      if(KbYVetKLXh == true){KbYVetKLXh = false;}
      if(kRLwWNjpNg == true){kRLwWNjpNg = false;}
      if(GqTUnbimLq == true){GqTUnbimLq = false;}
      if(siqamFLGRT == true){siqamFLGRT = false;}
      if(eSRrngdzwH == true){eSRrngdzwH = false;}
      if(ZqiLkSIEgC == true){ZqiLkSIEgC = false;}
      if(KWAgnCakIR == true){KWAgnCakIR = false;}
      if(BdXtCnZafH == true){BdXtCnZafH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TARTIZSFAV
{ 
  void fFygMflrPz()
  { 
      bool YKlrQrPQzA = false;
      bool tUZiBhHUQW = false;
      bool GPyMiOVkRO = false;
      bool CiNTAGCmaB = false;
      bool mgAHUjwQAu = false;
      bool LdPoBJLYIB = false;
      bool WeykxLGFht = false;
      bool eTtPjZPqrz = false;
      bool SEkWDXSYRq = false;
      bool uddZeIhPKI = false;
      bool cphFQqjAEb = false;
      bool tUfJhRtbhY = false;
      bool rhmpzApUja = false;
      bool qzfiWcWeGL = false;
      bool nSTpxZxUqM = false;
      bool NGglQtDqGP = false;
      bool BPPcjtnwlF = false;
      bool uOVVjZOxsY = false;
      bool CVcXNkRtSc = false;
      bool ZeYpKYDpFD = false;
      string UNUWeCMbke;
      string FFtWjxWpmD;
      string IqPZenbCuQ;
      string lYiPEjdFJj;
      string CqaNxnjKWW;
      string qfHVxdytqq;
      string ZJgUsfVdRz;
      string TQfCBQPBcq;
      string EQfYYFQNSa;
      string kjOSKrKGUR;
      string SFsWDZzEUf;
      string NwRAlIdHum;
      string OILpOjCMrI;
      string FJgKYyXIUz;
      string FLrlNnRNgB;
      string OCLgCJtCIT;
      string WmMLZEPGbn;
      string kVmugCPYcZ;
      string RofqtDxAHO;
      string EVzBcSzgLI;
      if(UNUWeCMbke == SFsWDZzEUf){YKlrQrPQzA = true;}
      else if(SFsWDZzEUf == UNUWeCMbke){cphFQqjAEb = true;}
      if(FFtWjxWpmD == NwRAlIdHum){tUZiBhHUQW = true;}
      else if(NwRAlIdHum == FFtWjxWpmD){tUfJhRtbhY = true;}
      if(IqPZenbCuQ == OILpOjCMrI){GPyMiOVkRO = true;}
      else if(OILpOjCMrI == IqPZenbCuQ){rhmpzApUja = true;}
      if(lYiPEjdFJj == FJgKYyXIUz){CiNTAGCmaB = true;}
      else if(FJgKYyXIUz == lYiPEjdFJj){qzfiWcWeGL = true;}
      if(CqaNxnjKWW == FLrlNnRNgB){mgAHUjwQAu = true;}
      else if(FLrlNnRNgB == CqaNxnjKWW){nSTpxZxUqM = true;}
      if(qfHVxdytqq == OCLgCJtCIT){LdPoBJLYIB = true;}
      else if(OCLgCJtCIT == qfHVxdytqq){NGglQtDqGP = true;}
      if(ZJgUsfVdRz == WmMLZEPGbn){WeykxLGFht = true;}
      else if(WmMLZEPGbn == ZJgUsfVdRz){BPPcjtnwlF = true;}
      if(TQfCBQPBcq == kVmugCPYcZ){eTtPjZPqrz = true;}
      if(EQfYYFQNSa == RofqtDxAHO){SEkWDXSYRq = true;}
      if(kjOSKrKGUR == EVzBcSzgLI){uddZeIhPKI = true;}
      while(kVmugCPYcZ == TQfCBQPBcq){uOVVjZOxsY = true;}
      while(RofqtDxAHO == RofqtDxAHO){CVcXNkRtSc = true;}
      while(EVzBcSzgLI == EVzBcSzgLI){ZeYpKYDpFD = true;}
      if(YKlrQrPQzA == true){YKlrQrPQzA = false;}
      if(tUZiBhHUQW == true){tUZiBhHUQW = false;}
      if(GPyMiOVkRO == true){GPyMiOVkRO = false;}
      if(CiNTAGCmaB == true){CiNTAGCmaB = false;}
      if(mgAHUjwQAu == true){mgAHUjwQAu = false;}
      if(LdPoBJLYIB == true){LdPoBJLYIB = false;}
      if(WeykxLGFht == true){WeykxLGFht = false;}
      if(eTtPjZPqrz == true){eTtPjZPqrz = false;}
      if(SEkWDXSYRq == true){SEkWDXSYRq = false;}
      if(uddZeIhPKI == true){uddZeIhPKI = false;}
      if(cphFQqjAEb == true){cphFQqjAEb = false;}
      if(tUfJhRtbhY == true){tUfJhRtbhY = false;}
      if(rhmpzApUja == true){rhmpzApUja = false;}
      if(qzfiWcWeGL == true){qzfiWcWeGL = false;}
      if(nSTpxZxUqM == true){nSTpxZxUqM = false;}
      if(NGglQtDqGP == true){NGglQtDqGP = false;}
      if(BPPcjtnwlF == true){BPPcjtnwlF = false;}
      if(uOVVjZOxsY == true){uOVVjZOxsY = false;}
      if(CVcXNkRtSc == true){CVcXNkRtSc = false;}
      if(ZeYpKYDpFD == true){ZeYpKYDpFD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCIWWPWLMM
{ 
  void XJuxgyqDRi()
  { 
      bool YCUITRmZLM = false;
      bool OfPPamnUXO = false;
      bool oiiLSECgUA = false;
      bool KTgcCyqVjg = false;
      bool yHBFjwlCgB = false;
      bool eksjHoTIoP = false;
      bool PFFKCtymMc = false;
      bool uSjpPggcaV = false;
      bool RzATVZaxUM = false;
      bool ehfUQsCqDp = false;
      bool yypEGMACUZ = false;
      bool HphTxQFkob = false;
      bool TBRzyMmPZV = false;
      bool dpYkXSJuMI = false;
      bool ZXbtEnAMWA = false;
      bool nQCbVxgpGs = false;
      bool YjczwRQwud = false;
      bool HJXfCwYWtJ = false;
      bool MasYgMmxPa = false;
      bool lSoTjotcym = false;
      string xnlBjhaznG;
      string GapAwdNdru;
      string PJPSRRLyGK;
      string LgGwxlWbGr;
      string swKhysklAo;
      string dXBKhnYTjR;
      string WbrctZUsDK;
      string HkXzCSygUY;
      string gZyRfmfuNJ;
      string MCroVQEgmX;
      string YqiogrABIO;
      string oqyLkwdaxH;
      string tYesxEshck;
      string ORtwzoqJjm;
      string ldmyTVEgEZ;
      string lcjfdAMoqb;
      string zSXWAWxBLu;
      string FUpJUQkfYb;
      string AMdDzlhNSz;
      string cBRInTFQyw;
      if(xnlBjhaznG == YqiogrABIO){YCUITRmZLM = true;}
      else if(YqiogrABIO == xnlBjhaznG){yypEGMACUZ = true;}
      if(GapAwdNdru == oqyLkwdaxH){OfPPamnUXO = true;}
      else if(oqyLkwdaxH == GapAwdNdru){HphTxQFkob = true;}
      if(PJPSRRLyGK == tYesxEshck){oiiLSECgUA = true;}
      else if(tYesxEshck == PJPSRRLyGK){TBRzyMmPZV = true;}
      if(LgGwxlWbGr == ORtwzoqJjm){KTgcCyqVjg = true;}
      else if(ORtwzoqJjm == LgGwxlWbGr){dpYkXSJuMI = true;}
      if(swKhysklAo == ldmyTVEgEZ){yHBFjwlCgB = true;}
      else if(ldmyTVEgEZ == swKhysklAo){ZXbtEnAMWA = true;}
      if(dXBKhnYTjR == lcjfdAMoqb){eksjHoTIoP = true;}
      else if(lcjfdAMoqb == dXBKhnYTjR){nQCbVxgpGs = true;}
      if(WbrctZUsDK == zSXWAWxBLu){PFFKCtymMc = true;}
      else if(zSXWAWxBLu == WbrctZUsDK){YjczwRQwud = true;}
      if(HkXzCSygUY == FUpJUQkfYb){uSjpPggcaV = true;}
      if(gZyRfmfuNJ == AMdDzlhNSz){RzATVZaxUM = true;}
      if(MCroVQEgmX == cBRInTFQyw){ehfUQsCqDp = true;}
      while(FUpJUQkfYb == HkXzCSygUY){HJXfCwYWtJ = true;}
      while(AMdDzlhNSz == AMdDzlhNSz){MasYgMmxPa = true;}
      while(cBRInTFQyw == cBRInTFQyw){lSoTjotcym = true;}
      if(YCUITRmZLM == true){YCUITRmZLM = false;}
      if(OfPPamnUXO == true){OfPPamnUXO = false;}
      if(oiiLSECgUA == true){oiiLSECgUA = false;}
      if(KTgcCyqVjg == true){KTgcCyqVjg = false;}
      if(yHBFjwlCgB == true){yHBFjwlCgB = false;}
      if(eksjHoTIoP == true){eksjHoTIoP = false;}
      if(PFFKCtymMc == true){PFFKCtymMc = false;}
      if(uSjpPggcaV == true){uSjpPggcaV = false;}
      if(RzATVZaxUM == true){RzATVZaxUM = false;}
      if(ehfUQsCqDp == true){ehfUQsCqDp = false;}
      if(yypEGMACUZ == true){yypEGMACUZ = false;}
      if(HphTxQFkob == true){HphTxQFkob = false;}
      if(TBRzyMmPZV == true){TBRzyMmPZV = false;}
      if(dpYkXSJuMI == true){dpYkXSJuMI = false;}
      if(ZXbtEnAMWA == true){ZXbtEnAMWA = false;}
      if(nQCbVxgpGs == true){nQCbVxgpGs = false;}
      if(YjczwRQwud == true){YjczwRQwud = false;}
      if(HJXfCwYWtJ == true){HJXfCwYWtJ = false;}
      if(MasYgMmxPa == true){MasYgMmxPa = false;}
      if(lSoTjotcym == true){lSoTjotcym = false;}
    } 
}; 
