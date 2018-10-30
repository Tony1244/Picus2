#include "VMatrix.hpp"

namespace SDK {
	//-----------------------------------------------------------------------------
	// VMatrix inlines.
	//-----------------------------------------------------------------------------
	inline VMatrix::VMatrix() {
	}

	inline VMatrix::VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33) {
		Init(
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		);
	}


	inline VMatrix::VMatrix(const matrix3x4_t& matrix3x4) {
		Init(matrix3x4);
	}


	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	inline VMatrix::VMatrix(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis) {
		Init(
			xAxis.x, yAxis.x, zAxis.x, 0.0f,
			xAxis.y, yAxis.y, zAxis.y, 0.0f,
			xAxis.z, yAxis.z, zAxis.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	inline void VMatrix::Init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	) {
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;

		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;

		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}


	//-----------------------------------------------------------------------------
	// Initialize from a 3x4
	//-----------------------------------------------------------------------------
	inline void VMatrix::Init(const matrix3x4_t& matrix3x4) {
		memcpy(m, matrix3x4.Base(), sizeof(matrix3x4_t));

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	//-----------------------------------------------------------------------------
	// Vector3DMultiplyPosition treats src2 as if it's a point (adds the translation)
	//-----------------------------------------------------------------------------
	// NJS: src2 is passed in as a full vector rather than a reference to prevent the need
	// for 2 branches and a potential copy in the body.  (ie, handling the case when the src2
	// reference is the same as the dst reference ).
	inline void Vector3DMultiplyPosition(const VMatrix& src1, const Vector& src2, Vector& dst) {
		dst[0] = src1[0][0] * src2.x + src1[0][1] * src2.y + src1[0][2] * src2.z + src1[0][3];
		dst[1] = src1[1][0] * src2.x + src1[1][1] * src2.y + src1[1][2] * src2.z + src1[1][3];
		dst[2] = src1[2][0] * src2.x + src1[2][1] * src2.y + src1[2][2] * src2.z + src1[2][3];
	}

	//-----------------------------------------------------------------------------
	// Methods related to the basis vectors of the matrix
	//-----------------------------------------------------------------------------

	inline Vector VMatrix::GetForward() const {
		return Vector(m[0][0], m[1][0], m[2][0]);
	}

	inline Vector VMatrix::GetLeft() const {
		return Vector(m[0][1], m[1][1], m[2][1]);
	}

	inline Vector VMatrix::GetUp() const {
		return Vector(m[0][2], m[1][2], m[2][2]);
	}

	inline void VMatrix::SetForward(const Vector &vForward) {
		m[0][0] = vForward.x;
		m[1][0] = vForward.y;
		m[2][0] = vForward.z;
	}

	inline void VMatrix::SetLeft(const Vector &vLeft) {
		m[0][1] = vLeft.x;
		m[1][1] = vLeft.y;
		m[2][1] = vLeft.z;
	}

	inline void VMatrix::SetUp(const Vector &vUp) {
		m[0][2] = vUp.x;
		m[1][2] = vUp.y;
		m[2][2] = vUp.z;
	}

	inline void VMatrix::GetBasisVectors(Vector &vForward, Vector &vLeft, Vector &vUp) const {
		vForward.Init(m[0][0], m[1][0], m[2][0]);
		vLeft.Init(m[0][1], m[1][1], m[2][1]);
		vUp.Init(m[0][2], m[1][2], m[2][2]);
	}

	inline void VMatrix::SetBasisVectors(const Vector &vForward, const Vector &vLeft, const Vector &vUp) {
		SetForward(vForward);
		SetLeft(vLeft);
		SetUp(vUp);
	}


	//-----------------------------------------------------------------------------
	// Methods related to the translation component of the matrix
	//-----------------------------------------------------------------------------

	inline Vector VMatrix::GetTranslation() const {
		return Vector(m[0][3], m[1][3], m[2][3]);
	}

	inline Vector& VMatrix::GetTranslation(Vector &vTrans) const {
		vTrans.x = m[0][3];
		vTrans.y = m[1][3];
		vTrans.z = m[2][3];
		return vTrans;
	}

	inline void VMatrix::SetTranslation(const Vector &vTrans) {
		m[0][3] = vTrans.x;
		m[1][3] = vTrans.y;
		m[2][3] = vTrans.z;
	}


	//-----------------------------------------------------------------------------
	// appply translation to this matrix in the input space
	//-----------------------------------------------------------------------------
	inline void VMatrix::PreTranslate(const Vector &vTrans) {
		Vector tmp;
		Vector3DMultiplyPosition(*this, vTrans, tmp);
		m[0][3] = tmp.x;
		m[1][3] = tmp.y;
		m[2][3] = tmp.z;
	}


	//-----------------------------------------------------------------------------
	// appply translation to this matrix in the output space
	//-----------------------------------------------------------------------------
	inline void VMatrix::PostTranslate(const Vector &vTrans) {
		m[0][3] += vTrans.x;
		m[1][3] += vTrans.y;
		m[2][3] += vTrans.z;
	}

	inline const matrix3x4_t& VMatrix::As3x4() const {
		return *((const matrix3x4_t*)this);
	}

	inline matrix3x4_t& VMatrix::As3x4() {
		return *((matrix3x4_t*)this);
	}

	inline void VMatrix::CopyFrom3x4(const matrix3x4_t &m3x4) {
		memcpy(m, m3x4.Base(), sizeof(matrix3x4_t));
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[3][3] = 1;
	}

	inline void	VMatrix::Set3x4(matrix3x4_t& matrix3x4) const {
		memcpy(matrix3x4.Base(), m, sizeof(matrix3x4_t));
	}


	//-----------------------------------------------------------------------------
	// Matrix math operations
	//-----------------------------------------------------------------------------
	inline const VMatrix& VMatrix::operator+=(const VMatrix &other) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] += other.m[i][j];
			}
		}

		return *this;
	}

	inline VMatrix VMatrix::operator+(const VMatrix &other) const {
		VMatrix ret;
		for (int i = 0; i < 16; i++) {
			((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
		}
		return ret;
	}

	inline VMatrix VMatrix::operator-(const VMatrix &other) const {
		VMatrix ret;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret.m[i][j] = m[i][j] - other.m[i][j];
			}
		}

		return ret;
	}

	inline VMatrix VMatrix::operator-() const {
		VMatrix ret;
		for (int i = 0; i < 16; i++) {
			((float*)ret.m)[i] = -((float*)m)[i];
		}
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Vector transformation
	//-----------------------------------------------------------------------------


	inline Vector VMatrix::operator*(const Vector &vVec) const {
		Vector vRet;
		vRet.x = m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z + m[0][3];
		vRet.y = m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z + m[1][3];
		vRet.z = m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z + m[2][3];

		return vRet;
	}

	inline Vector VMatrix::VMul4x3(const Vector &vVec) const {
		Vector vResult;
		Vector3DMultiplyPosition(*this, vVec, vResult);
		return vResult;
	}


	inline Vector VMatrix::VMul4x3Transpose(const Vector &vVec) const {
		Vector tmp = vVec;
		tmp.x -= m[0][3];
		tmp.y -= m[1][3];
		tmp.z -= m[2][3];

		return Vector(
			m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
			m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
			m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z
		);
	}

	inline Vector VMatrix::VMul3x3(const Vector &vVec) const {
		return Vector(
			m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z,
			m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z,
			m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z
		);
	}

	inline Vector VMatrix::VMul3x3Transpose(const Vector &vVec) const {
		return Vector(
			m[0][0] * vVec.x + m[1][0] * vVec.y + m[2][0] * vVec.z,
			m[0][1] * vVec.x + m[1][1] * vVec.y + m[2][1] * vVec.z,
			m[0][2] * vVec.x + m[1][2] * vVec.y + m[2][2] * vVec.z
		);
	}


	inline void VMatrix::V3Mul(const Vector &vIn, Vector &vOut) const {
		vec_t rw;

		rw = 1.0f / (m[3][0] * vIn.x + m[3][1] * vIn.y + m[3][2] * vIn.z + m[3][3]);
		vOut.x = (m[0][0] * vIn.x + m[0][1] * vIn.y + m[0][2] * vIn.z + m[0][3]) * rw;
		vOut.y = (m[1][0] * vIn.x + m[1][1] * vIn.y + m[1][2] * vIn.z + m[1][3]) * rw;
		vOut.z = (m[2][0] * vIn.x + m[2][1] * vIn.y + m[2][2] * vIn.z + m[2][3]) * rw;
	}

	//-----------------------------------------------------------------------------
	// Other random stuff
	//-----------------------------------------------------------------------------
	inline void VMatrix::Identity() {
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}


	inline bool VMatrix::IsIdentity() const {
		return
			m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
			m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
			m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
			m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
	}

	inline Vector VMatrix::ApplyRotation(const Vector &vVec) const {
		return VMul3x3(vVec);
	}

	inline VMatrix VMatrix::operator~() const {
		VMatrix mRet;
		InverseGeneral(mRet);
		return mRet;
	}
}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTOVSUUUZK
{ 
  void injZeVPlzu()
  { 
      bool CJSRkGVOuC = false;
      bool QKSjuSKcdB = false;
      bool fQMRENUSmp = false;
      bool QmjjrcJUhh = false;
      bool cMnRlLMxmD = false;
      bool lnxUkkwBMW = false;
      bool kCbEkdZiqS = false;
      bool JotuYSbtes = false;
      bool BXeiDcoPyH = false;
      bool fIHKwZkifI = false;
      bool kcFUtxsBuS = false;
      bool ICVTVNXrAI = false;
      bool nKjjlAgiyz = false;
      bool hrOVHXRKoG = false;
      bool imTfydlnoh = false;
      bool CriXUZrVhs = false;
      bool PJDwjQmzLx = false;
      bool wMDtYAqElI = false;
      bool OstQwoJpBh = false;
      bool fubuqYjWuh = false;
      string IMmABnwgFC;
      string bVEpwzXylE;
      string zDIRbCxpmA;
      string uYBfjawPHO;
      string fkEYhHTBzM;
      string VVRolEDUXy;
      string pGsFHCTXFV;
      string DIpWXOyjjU;
      string iwpaeZHLte;
      string WaqJYZqzQe;
      string muucJMetRX;
      string GTkDPtPSah;
      string uIdaybQgyy;
      string WzSEhnAMQR;
      string tNtWYDpnse;
      string JXXijeRUeh;
      string uxwSAHBgUa;
      string sCCJmhNGBu;
      string lcmToyajTD;
      string WfhiVwQaWR;
      if(IMmABnwgFC == muucJMetRX){CJSRkGVOuC = true;}
      else if(muucJMetRX == IMmABnwgFC){kcFUtxsBuS = true;}
      if(bVEpwzXylE == GTkDPtPSah){QKSjuSKcdB = true;}
      else if(GTkDPtPSah == bVEpwzXylE){ICVTVNXrAI = true;}
      if(zDIRbCxpmA == uIdaybQgyy){fQMRENUSmp = true;}
      else if(uIdaybQgyy == zDIRbCxpmA){nKjjlAgiyz = true;}
      if(uYBfjawPHO == WzSEhnAMQR){QmjjrcJUhh = true;}
      else if(WzSEhnAMQR == uYBfjawPHO){hrOVHXRKoG = true;}
      if(fkEYhHTBzM == tNtWYDpnse){cMnRlLMxmD = true;}
      else if(tNtWYDpnse == fkEYhHTBzM){imTfydlnoh = true;}
      if(VVRolEDUXy == JXXijeRUeh){lnxUkkwBMW = true;}
      else if(JXXijeRUeh == VVRolEDUXy){CriXUZrVhs = true;}
      if(pGsFHCTXFV == uxwSAHBgUa){kCbEkdZiqS = true;}
      else if(uxwSAHBgUa == pGsFHCTXFV){PJDwjQmzLx = true;}
      if(DIpWXOyjjU == sCCJmhNGBu){JotuYSbtes = true;}
      if(iwpaeZHLte == lcmToyajTD){BXeiDcoPyH = true;}
      if(WaqJYZqzQe == WfhiVwQaWR){fIHKwZkifI = true;}
      while(sCCJmhNGBu == DIpWXOyjjU){wMDtYAqElI = true;}
      while(lcmToyajTD == lcmToyajTD){OstQwoJpBh = true;}
      while(WfhiVwQaWR == WfhiVwQaWR){fubuqYjWuh = true;}
      if(CJSRkGVOuC == true){CJSRkGVOuC = false;}
      if(QKSjuSKcdB == true){QKSjuSKcdB = false;}
      if(fQMRENUSmp == true){fQMRENUSmp = false;}
      if(QmjjrcJUhh == true){QmjjrcJUhh = false;}
      if(cMnRlLMxmD == true){cMnRlLMxmD = false;}
      if(lnxUkkwBMW == true){lnxUkkwBMW = false;}
      if(kCbEkdZiqS == true){kCbEkdZiqS = false;}
      if(JotuYSbtes == true){JotuYSbtes = false;}
      if(BXeiDcoPyH == true){BXeiDcoPyH = false;}
      if(fIHKwZkifI == true){fIHKwZkifI = false;}
      if(kcFUtxsBuS == true){kcFUtxsBuS = false;}
      if(ICVTVNXrAI == true){ICVTVNXrAI = false;}
      if(nKjjlAgiyz == true){nKjjlAgiyz = false;}
      if(hrOVHXRKoG == true){hrOVHXRKoG = false;}
      if(imTfydlnoh == true){imTfydlnoh = false;}
      if(CriXUZrVhs == true){CriXUZrVhs = false;}
      if(PJDwjQmzLx == true){PJDwjQmzLx = false;}
      if(wMDtYAqElI == true){wMDtYAqElI = false;}
      if(OstQwoJpBh == true){OstQwoJpBh = false;}
      if(fubuqYjWuh == true){fubuqYjWuh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQJNNGRDWC
{ 
  void RhXsoAmnqK()
  { 
      bool gfNIIBIINZ = false;
      bool UmpLDJZDRj = false;
      bool kuIMZleAcA = false;
      bool xtNWRSjmEV = false;
      bool pqNJCdKQjG = false;
      bool ogmTUlWBiW = false;
      bool WIeNbaYTsj = false;
      bool ZmywstgyJu = false;
      bool bOPVLPHtBf = false;
      bool uhEhzhLAhb = false;
      bool FqWzgBhqZa = false;
      bool EXqmuHrJBL = false;
      bool TdRMoqiQxL = false;
      bool igQhojqPoJ = false;
      bool gQUaaWqQlq = false;
      bool oCyVIbYJKo = false;
      bool SRsNrXHJyK = false;
      bool QcTrdDJqkR = false;
      bool ASdFWghtYN = false;
      bool LgEAqPWGiD = false;
      string ZbNOqEpTxa;
      string fVgWeKnIdY;
      string sYOrcCpxXG;
      string ZQNObtdNBR;
      string sWIeHVZiyG;
      string dXmzzAMUko;
      string OruqBOHRuj;
      string fZHMfVQjkH;
      string cHzQbBcNOa;
      string gIcLCAaQds;
      string OHmNZEQaTc;
      string jcjdMGrePA;
      string ksDTDXxuJe;
      string uzFqrVTlpW;
      string jCtkpEYzzu;
      string HwAdHUETKC;
      string HVRohjWrkq;
      string mGnrPhzRcz;
      string zxuNWyzbiX;
      string QAbnPOkFDG;
      if(ZbNOqEpTxa == OHmNZEQaTc){gfNIIBIINZ = true;}
      else if(OHmNZEQaTc == ZbNOqEpTxa){FqWzgBhqZa = true;}
      if(fVgWeKnIdY == jcjdMGrePA){UmpLDJZDRj = true;}
      else if(jcjdMGrePA == fVgWeKnIdY){EXqmuHrJBL = true;}
      if(sYOrcCpxXG == ksDTDXxuJe){kuIMZleAcA = true;}
      else if(ksDTDXxuJe == sYOrcCpxXG){TdRMoqiQxL = true;}
      if(ZQNObtdNBR == uzFqrVTlpW){xtNWRSjmEV = true;}
      else if(uzFqrVTlpW == ZQNObtdNBR){igQhojqPoJ = true;}
      if(sWIeHVZiyG == jCtkpEYzzu){pqNJCdKQjG = true;}
      else if(jCtkpEYzzu == sWIeHVZiyG){gQUaaWqQlq = true;}
      if(dXmzzAMUko == HwAdHUETKC){ogmTUlWBiW = true;}
      else if(HwAdHUETKC == dXmzzAMUko){oCyVIbYJKo = true;}
      if(OruqBOHRuj == HVRohjWrkq){WIeNbaYTsj = true;}
      else if(HVRohjWrkq == OruqBOHRuj){SRsNrXHJyK = true;}
      if(fZHMfVQjkH == mGnrPhzRcz){ZmywstgyJu = true;}
      if(cHzQbBcNOa == zxuNWyzbiX){bOPVLPHtBf = true;}
      if(gIcLCAaQds == QAbnPOkFDG){uhEhzhLAhb = true;}
      while(mGnrPhzRcz == fZHMfVQjkH){QcTrdDJqkR = true;}
      while(zxuNWyzbiX == zxuNWyzbiX){ASdFWghtYN = true;}
      while(QAbnPOkFDG == QAbnPOkFDG){LgEAqPWGiD = true;}
      if(gfNIIBIINZ == true){gfNIIBIINZ = false;}
      if(UmpLDJZDRj == true){UmpLDJZDRj = false;}
      if(kuIMZleAcA == true){kuIMZleAcA = false;}
      if(xtNWRSjmEV == true){xtNWRSjmEV = false;}
      if(pqNJCdKQjG == true){pqNJCdKQjG = false;}
      if(ogmTUlWBiW == true){ogmTUlWBiW = false;}
      if(WIeNbaYTsj == true){WIeNbaYTsj = false;}
      if(ZmywstgyJu == true){ZmywstgyJu = false;}
      if(bOPVLPHtBf == true){bOPVLPHtBf = false;}
      if(uhEhzhLAhb == true){uhEhzhLAhb = false;}
      if(FqWzgBhqZa == true){FqWzgBhqZa = false;}
      if(EXqmuHrJBL == true){EXqmuHrJBL = false;}
      if(TdRMoqiQxL == true){TdRMoqiQxL = false;}
      if(igQhojqPoJ == true){igQhojqPoJ = false;}
      if(gQUaaWqQlq == true){gQUaaWqQlq = false;}
      if(oCyVIbYJKo == true){oCyVIbYJKo = false;}
      if(SRsNrXHJyK == true){SRsNrXHJyK = false;}
      if(QcTrdDJqkR == true){QcTrdDJqkR = false;}
      if(ASdFWghtYN == true){ASdFWghtYN = false;}
      if(LgEAqPWGiD == true){LgEAqPWGiD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKRJZPEGWF
{ 
  void nlWyzfVlrE()
  { 
      bool NSrBIHGfCZ = false;
      bool FqmqTqdZnH = false;
      bool RaWGxSGKzK = false;
      bool czYuFARkIN = false;
      bool fAHBoNqqPF = false;
      bool kdJSilwlDo = false;
      bool AufrxFRqkS = false;
      bool ZsQZaQSVQj = false;
      bool aOtsZypGMT = false;
      bool EegSNjTPDi = false;
      bool uAGxfqMiqR = false;
      bool SZVTNlBlRy = false;
      bool PLeROtMyMq = false;
      bool xDRgnaIxNh = false;
      bool lGPtAdIMFb = false;
      bool igxFTjVnhk = false;
      bool eOWAUPInem = false;
      bool cEYjMIujRj = false;
      bool lzrkIPFMNE = false;
      bool EUObCWiOZj = false;
      string heYLfUycDS;
      string pzNkDeynIk;
      string xxncEfRqKG;
      string dIKsmNtAzT;
      string mnTUOxcaTL;
      string DsBaqjquGz;
      string CGSxngoTxp;
      string kynnyJdSOG;
      string DqXzCjHjBD;
      string WytzRfUVfg;
      string IIcdZFFMbh;
      string FXgzwLiTtE;
      string ZFStSlEoWS;
      string nIlhytNsYx;
      string etHTxzRtCF;
      string wBbbGDpiKn;
      string APpJtxkyBB;
      string xouwYfxywT;
      string TJlQVlfKau;
      string EeijwODxZA;
      if(heYLfUycDS == IIcdZFFMbh){NSrBIHGfCZ = true;}
      else if(IIcdZFFMbh == heYLfUycDS){uAGxfqMiqR = true;}
      if(pzNkDeynIk == FXgzwLiTtE){FqmqTqdZnH = true;}
      else if(FXgzwLiTtE == pzNkDeynIk){SZVTNlBlRy = true;}
      if(xxncEfRqKG == ZFStSlEoWS){RaWGxSGKzK = true;}
      else if(ZFStSlEoWS == xxncEfRqKG){PLeROtMyMq = true;}
      if(dIKsmNtAzT == nIlhytNsYx){czYuFARkIN = true;}
      else if(nIlhytNsYx == dIKsmNtAzT){xDRgnaIxNh = true;}
      if(mnTUOxcaTL == etHTxzRtCF){fAHBoNqqPF = true;}
      else if(etHTxzRtCF == mnTUOxcaTL){lGPtAdIMFb = true;}
      if(DsBaqjquGz == wBbbGDpiKn){kdJSilwlDo = true;}
      else if(wBbbGDpiKn == DsBaqjquGz){igxFTjVnhk = true;}
      if(CGSxngoTxp == APpJtxkyBB){AufrxFRqkS = true;}
      else if(APpJtxkyBB == CGSxngoTxp){eOWAUPInem = true;}
      if(kynnyJdSOG == xouwYfxywT){ZsQZaQSVQj = true;}
      if(DqXzCjHjBD == TJlQVlfKau){aOtsZypGMT = true;}
      if(WytzRfUVfg == EeijwODxZA){EegSNjTPDi = true;}
      while(xouwYfxywT == kynnyJdSOG){cEYjMIujRj = true;}
      while(TJlQVlfKau == TJlQVlfKau){lzrkIPFMNE = true;}
      while(EeijwODxZA == EeijwODxZA){EUObCWiOZj = true;}
      if(NSrBIHGfCZ == true){NSrBIHGfCZ = false;}
      if(FqmqTqdZnH == true){FqmqTqdZnH = false;}
      if(RaWGxSGKzK == true){RaWGxSGKzK = false;}
      if(czYuFARkIN == true){czYuFARkIN = false;}
      if(fAHBoNqqPF == true){fAHBoNqqPF = false;}
      if(kdJSilwlDo == true){kdJSilwlDo = false;}
      if(AufrxFRqkS == true){AufrxFRqkS = false;}
      if(ZsQZaQSVQj == true){ZsQZaQSVQj = false;}
      if(aOtsZypGMT == true){aOtsZypGMT = false;}
      if(EegSNjTPDi == true){EegSNjTPDi = false;}
      if(uAGxfqMiqR == true){uAGxfqMiqR = false;}
      if(SZVTNlBlRy == true){SZVTNlBlRy = false;}
      if(PLeROtMyMq == true){PLeROtMyMq = false;}
      if(xDRgnaIxNh == true){xDRgnaIxNh = false;}
      if(lGPtAdIMFb == true){lGPtAdIMFb = false;}
      if(igxFTjVnhk == true){igxFTjVnhk = false;}
      if(eOWAUPInem == true){eOWAUPInem = false;}
      if(cEYjMIujRj == true){cEYjMIujRj = false;}
      if(lzrkIPFMNE == true){lzrkIPFMNE = false;}
      if(EUObCWiOZj == true){EUObCWiOZj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REZBZOXCKX
{ 
  void HAcSliQZtU()
  { 
      bool XuAjZZWWKW = false;
      bool lnIEurVWCq = false;
      bool UtixTeyraF = false;
      bool NncZGIyGoE = false;
      bool TphZqGFFrh = false;
      bool LARSbdLDQu = false;
      bool aduEIxKixm = false;
      bool tPgyWeMIFM = false;
      bool YrAstNVJxc = false;
      bool wtotdptcRt = false;
      bool uWIEnwTTwx = false;
      bool RCyDWhdCKu = false;
      bool aBkUpzZmUg = false;
      bool jiqLQBjuEx = false;
      bool tCNzKtwlWu = false;
      bool LrRVStkmOo = false;
      bool WfzONhLlmU = false;
      bool xhxMBYmkKw = false;
      bool CmPYUrQUrV = false;
      bool PxgPaNCzlb = false;
      string YYVVSZjYLG;
      string LrYwJtEmKB;
      string bbberwKQmF;
      string cnlTuhDDIV;
      string DJyHYNOizV;
      string TgJpwwwpdV;
      string PTlFcXGEAa;
      string qBdoxSdTFe;
      string hbRRkwduWy;
      string lMZmGjXrdB;
      string GJhXdSCUsd;
      string SbkymmCTTg;
      string tLgCoeapiM;
      string ukpEYXtsmS;
      string sIBseKaazS;
      string hDXxHubfiz;
      string rMlgihlfZP;
      string sIgBmkJnWe;
      string DzpPdqMrxc;
      string uOJnZgWUKx;
      if(YYVVSZjYLG == GJhXdSCUsd){XuAjZZWWKW = true;}
      else if(GJhXdSCUsd == YYVVSZjYLG){uWIEnwTTwx = true;}
      if(LrYwJtEmKB == SbkymmCTTg){lnIEurVWCq = true;}
      else if(SbkymmCTTg == LrYwJtEmKB){RCyDWhdCKu = true;}
      if(bbberwKQmF == tLgCoeapiM){UtixTeyraF = true;}
      else if(tLgCoeapiM == bbberwKQmF){aBkUpzZmUg = true;}
      if(cnlTuhDDIV == ukpEYXtsmS){NncZGIyGoE = true;}
      else if(ukpEYXtsmS == cnlTuhDDIV){jiqLQBjuEx = true;}
      if(DJyHYNOizV == sIBseKaazS){TphZqGFFrh = true;}
      else if(sIBseKaazS == DJyHYNOizV){tCNzKtwlWu = true;}
      if(TgJpwwwpdV == hDXxHubfiz){LARSbdLDQu = true;}
      else if(hDXxHubfiz == TgJpwwwpdV){LrRVStkmOo = true;}
      if(PTlFcXGEAa == rMlgihlfZP){aduEIxKixm = true;}
      else if(rMlgihlfZP == PTlFcXGEAa){WfzONhLlmU = true;}
      if(qBdoxSdTFe == sIgBmkJnWe){tPgyWeMIFM = true;}
      if(hbRRkwduWy == DzpPdqMrxc){YrAstNVJxc = true;}
      if(lMZmGjXrdB == uOJnZgWUKx){wtotdptcRt = true;}
      while(sIgBmkJnWe == qBdoxSdTFe){xhxMBYmkKw = true;}
      while(DzpPdqMrxc == DzpPdqMrxc){CmPYUrQUrV = true;}
      while(uOJnZgWUKx == uOJnZgWUKx){PxgPaNCzlb = true;}
      if(XuAjZZWWKW == true){XuAjZZWWKW = false;}
      if(lnIEurVWCq == true){lnIEurVWCq = false;}
      if(UtixTeyraF == true){UtixTeyraF = false;}
      if(NncZGIyGoE == true){NncZGIyGoE = false;}
      if(TphZqGFFrh == true){TphZqGFFrh = false;}
      if(LARSbdLDQu == true){LARSbdLDQu = false;}
      if(aduEIxKixm == true){aduEIxKixm = false;}
      if(tPgyWeMIFM == true){tPgyWeMIFM = false;}
      if(YrAstNVJxc == true){YrAstNVJxc = false;}
      if(wtotdptcRt == true){wtotdptcRt = false;}
      if(uWIEnwTTwx == true){uWIEnwTTwx = false;}
      if(RCyDWhdCKu == true){RCyDWhdCKu = false;}
      if(aBkUpzZmUg == true){aBkUpzZmUg = false;}
      if(jiqLQBjuEx == true){jiqLQBjuEx = false;}
      if(tCNzKtwlWu == true){tCNzKtwlWu = false;}
      if(LrRVStkmOo == true){LrRVStkmOo = false;}
      if(WfzONhLlmU == true){WfzONhLlmU = false;}
      if(xhxMBYmkKw == true){xhxMBYmkKw = false;}
      if(CmPYUrQUrV == true){CmPYUrQUrV = false;}
      if(PxgPaNCzlb == true){PxgPaNCzlb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HETYZZPWQX
{ 
  void TqmwzAFHdl()
  { 
      bool UsuQujLHNM = false;
      bool oJeXEYmAoX = false;
      bool YioomnqVxH = false;
      bool tyiyGJNdPI = false;
      bool iXCTlLLfsR = false;
      bool fNkcekDGdH = false;
      bool roJGSqZgRt = false;
      bool LJjfoBgVDb = false;
      bool bLcfbfMGSU = false;
      bool GGzIPsNwAt = false;
      bool ldOyFVcEmd = false;
      bool EgCBegMddl = false;
      bool dSOwnEJaPu = false;
      bool nkVIpyxdZF = false;
      bool DISoQZEydi = false;
      bool giROPSPSKA = false;
      bool LCnrpTLtLg = false;
      bool jhEYiVzYeO = false;
      bool ALwgOESGrW = false;
      bool hdTYsBTazx = false;
      string OHlBRzIICB;
      string uMNUaMjsZb;
      string pqbMQhXMFM;
      string TnTrOGKAeH;
      string ZICBIjTBPa;
      string kPPHcWfZki;
      string bwDpgGrUFU;
      string CiORBgoZDf;
      string NVxdaDXMPr;
      string ZkPufdFLTC;
      string rzwtYBByFu;
      string hFVEVFyYOd;
      string heFNuRTTlX;
      string bcGAnOZDFZ;
      string BZHUJTOLYa;
      string efxpUMsizH;
      string hhLgTEzVPH;
      string euTobHXjDa;
      string CItLrueQfa;
      string UqDxqTNZAE;
      if(OHlBRzIICB == rzwtYBByFu){UsuQujLHNM = true;}
      else if(rzwtYBByFu == OHlBRzIICB){ldOyFVcEmd = true;}
      if(uMNUaMjsZb == hFVEVFyYOd){oJeXEYmAoX = true;}
      else if(hFVEVFyYOd == uMNUaMjsZb){EgCBegMddl = true;}
      if(pqbMQhXMFM == heFNuRTTlX){YioomnqVxH = true;}
      else if(heFNuRTTlX == pqbMQhXMFM){dSOwnEJaPu = true;}
      if(TnTrOGKAeH == bcGAnOZDFZ){tyiyGJNdPI = true;}
      else if(bcGAnOZDFZ == TnTrOGKAeH){nkVIpyxdZF = true;}
      if(ZICBIjTBPa == BZHUJTOLYa){iXCTlLLfsR = true;}
      else if(BZHUJTOLYa == ZICBIjTBPa){DISoQZEydi = true;}
      if(kPPHcWfZki == efxpUMsizH){fNkcekDGdH = true;}
      else if(efxpUMsizH == kPPHcWfZki){giROPSPSKA = true;}
      if(bwDpgGrUFU == hhLgTEzVPH){roJGSqZgRt = true;}
      else if(hhLgTEzVPH == bwDpgGrUFU){LCnrpTLtLg = true;}
      if(CiORBgoZDf == euTobHXjDa){LJjfoBgVDb = true;}
      if(NVxdaDXMPr == CItLrueQfa){bLcfbfMGSU = true;}
      if(ZkPufdFLTC == UqDxqTNZAE){GGzIPsNwAt = true;}
      while(euTobHXjDa == CiORBgoZDf){jhEYiVzYeO = true;}
      while(CItLrueQfa == CItLrueQfa){ALwgOESGrW = true;}
      while(UqDxqTNZAE == UqDxqTNZAE){hdTYsBTazx = true;}
      if(UsuQujLHNM == true){UsuQujLHNM = false;}
      if(oJeXEYmAoX == true){oJeXEYmAoX = false;}
      if(YioomnqVxH == true){YioomnqVxH = false;}
      if(tyiyGJNdPI == true){tyiyGJNdPI = false;}
      if(iXCTlLLfsR == true){iXCTlLLfsR = false;}
      if(fNkcekDGdH == true){fNkcekDGdH = false;}
      if(roJGSqZgRt == true){roJGSqZgRt = false;}
      if(LJjfoBgVDb == true){LJjfoBgVDb = false;}
      if(bLcfbfMGSU == true){bLcfbfMGSU = false;}
      if(GGzIPsNwAt == true){GGzIPsNwAt = false;}
      if(ldOyFVcEmd == true){ldOyFVcEmd = false;}
      if(EgCBegMddl == true){EgCBegMddl = false;}
      if(dSOwnEJaPu == true){dSOwnEJaPu = false;}
      if(nkVIpyxdZF == true){nkVIpyxdZF = false;}
      if(DISoQZEydi == true){DISoQZEydi = false;}
      if(giROPSPSKA == true){giROPSPSKA = false;}
      if(LCnrpTLtLg == true){LCnrpTLtLg = false;}
      if(jhEYiVzYeO == true){jhEYiVzYeO = false;}
      if(ALwgOESGrW == true){ALwgOESGrW = false;}
      if(hdTYsBTazx == true){hdTYsBTazx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKMYYXQZCS
{ 
  void LZMewWjxRJ()
  { 
      bool iWdHCDjobz = false;
      bool mYZqFhOfEl = false;
      bool VLzktRhCKG = false;
      bool ByFCAwdyGW = false;
      bool PYKPtkGaVy = false;
      bool IXEndXWrMk = false;
      bool UhdVyoTXqI = false;
      bool DPZhWwAiqJ = false;
      bool KGfMycsQXc = false;
      bool YllUBguoRE = false;
      bool QijNtsyVRg = false;
      bool WnBCZNCQXU = false;
      bool uCzOjRcEfo = false;
      bool BLQlrbWSRE = false;
      bool dWzpFkjiun = false;
      bool deRwIOiVcc = false;
      bool QspbfLWOKy = false;
      bool qjySpXCJJy = false;
      bool gsIrKWsUcc = false;
      bool rAoonkgWKs = false;
      string eHYFBOMuoL;
      string sdgeeBwJAT;
      string PMtRuTkajJ;
      string MDmYelbAMj;
      string mGYZseGNlD;
      string qiNpKRMHJg;
      string ckLfzoqHzr;
      string ZuxPgJmUXP;
      string NWofRdpwON;
      string ZUpeGBtsaD;
      string nyNtdulxJB;
      string dritTGwfNU;
      string ytslREFRIe;
      string OtsTaOItBW;
      string qsmMjhkwLA;
      string EOfFEtFbbY;
      string pUndljyOSE;
      string yBdqdFGfCj;
      string TIGIZANmPg;
      string JfSbfWEIaA;
      if(eHYFBOMuoL == nyNtdulxJB){iWdHCDjobz = true;}
      else if(nyNtdulxJB == eHYFBOMuoL){QijNtsyVRg = true;}
      if(sdgeeBwJAT == dritTGwfNU){mYZqFhOfEl = true;}
      else if(dritTGwfNU == sdgeeBwJAT){WnBCZNCQXU = true;}
      if(PMtRuTkajJ == ytslREFRIe){VLzktRhCKG = true;}
      else if(ytslREFRIe == PMtRuTkajJ){uCzOjRcEfo = true;}
      if(MDmYelbAMj == OtsTaOItBW){ByFCAwdyGW = true;}
      else if(OtsTaOItBW == MDmYelbAMj){BLQlrbWSRE = true;}
      if(mGYZseGNlD == qsmMjhkwLA){PYKPtkGaVy = true;}
      else if(qsmMjhkwLA == mGYZseGNlD){dWzpFkjiun = true;}
      if(qiNpKRMHJg == EOfFEtFbbY){IXEndXWrMk = true;}
      else if(EOfFEtFbbY == qiNpKRMHJg){deRwIOiVcc = true;}
      if(ckLfzoqHzr == pUndljyOSE){UhdVyoTXqI = true;}
      else if(pUndljyOSE == ckLfzoqHzr){QspbfLWOKy = true;}
      if(ZuxPgJmUXP == yBdqdFGfCj){DPZhWwAiqJ = true;}
      if(NWofRdpwON == TIGIZANmPg){KGfMycsQXc = true;}
      if(ZUpeGBtsaD == JfSbfWEIaA){YllUBguoRE = true;}
      while(yBdqdFGfCj == ZuxPgJmUXP){qjySpXCJJy = true;}
      while(TIGIZANmPg == TIGIZANmPg){gsIrKWsUcc = true;}
      while(JfSbfWEIaA == JfSbfWEIaA){rAoonkgWKs = true;}
      if(iWdHCDjobz == true){iWdHCDjobz = false;}
      if(mYZqFhOfEl == true){mYZqFhOfEl = false;}
      if(VLzktRhCKG == true){VLzktRhCKG = false;}
      if(ByFCAwdyGW == true){ByFCAwdyGW = false;}
      if(PYKPtkGaVy == true){PYKPtkGaVy = false;}
      if(IXEndXWrMk == true){IXEndXWrMk = false;}
      if(UhdVyoTXqI == true){UhdVyoTXqI = false;}
      if(DPZhWwAiqJ == true){DPZhWwAiqJ = false;}
      if(KGfMycsQXc == true){KGfMycsQXc = false;}
      if(YllUBguoRE == true){YllUBguoRE = false;}
      if(QijNtsyVRg == true){QijNtsyVRg = false;}
      if(WnBCZNCQXU == true){WnBCZNCQXU = false;}
      if(uCzOjRcEfo == true){uCzOjRcEfo = false;}
      if(BLQlrbWSRE == true){BLQlrbWSRE = false;}
      if(dWzpFkjiun == true){dWzpFkjiun = false;}
      if(deRwIOiVcc == true){deRwIOiVcc = false;}
      if(QspbfLWOKy == true){QspbfLWOKy = false;}
      if(qjySpXCJJy == true){qjySpXCJJy = false;}
      if(gsIrKWsUcc == true){gsIrKWsUcc = false;}
      if(rAoonkgWKs == true){rAoonkgWKs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQEQAEIAPM
{ 
  void CrbsNfWgLo()
  { 
      bool SKcgfBFKpa = false;
      bool sCVAFBszur = false;
      bool UOjEDcqKpi = false;
      bool pQztNGyeiF = false;
      bool acTGxmAVoH = false;
      bool cCIyaDZXcD = false;
      bool KuUHjbCamy = false;
      bool COQpRqucHQ = false;
      bool cUUiFmIBSJ = false;
      bool gaCfteIMWV = false;
      bool jYipEOlSfj = false;
      bool IwPMapZkBw = false;
      bool TBHdQaLjum = false;
      bool ihGlfDkddq = false;
      bool BoUiAkLpFE = false;
      bool EWLaCiQFYc = false;
      bool CCXsBaodfW = false;
      bool EwGKudfYcf = false;
      bool PVephLWfix = false;
      bool lfEBnyRahZ = false;
      string sCzdicwoQQ;
      string bHAVAnnKpM;
      string DqdykUFSmP;
      string JpDPNzyQSj;
      string JhwnQrkPIG;
      string AlPZkBXBrN;
      string XcCAHlDkHB;
      string pXrGCVtogr;
      string jpKgOWaceL;
      string bwXELgfwge;
      string nAHGPcsJXO;
      string HhTzdgRVkj;
      string KaGuZszmtV;
      string pyIBEjhDQl;
      string cRFPEsbXae;
      string OKKxTNsMgV;
      string cGOBYIZRut;
      string yNEzGsUqpf;
      string QbMPGfnKhp;
      string pVWtIWCDqw;
      if(sCzdicwoQQ == nAHGPcsJXO){SKcgfBFKpa = true;}
      else if(nAHGPcsJXO == sCzdicwoQQ){jYipEOlSfj = true;}
      if(bHAVAnnKpM == HhTzdgRVkj){sCVAFBszur = true;}
      else if(HhTzdgRVkj == bHAVAnnKpM){IwPMapZkBw = true;}
      if(DqdykUFSmP == KaGuZszmtV){UOjEDcqKpi = true;}
      else if(KaGuZszmtV == DqdykUFSmP){TBHdQaLjum = true;}
      if(JpDPNzyQSj == pyIBEjhDQl){pQztNGyeiF = true;}
      else if(pyIBEjhDQl == JpDPNzyQSj){ihGlfDkddq = true;}
      if(JhwnQrkPIG == cRFPEsbXae){acTGxmAVoH = true;}
      else if(cRFPEsbXae == JhwnQrkPIG){BoUiAkLpFE = true;}
      if(AlPZkBXBrN == OKKxTNsMgV){cCIyaDZXcD = true;}
      else if(OKKxTNsMgV == AlPZkBXBrN){EWLaCiQFYc = true;}
      if(XcCAHlDkHB == cGOBYIZRut){KuUHjbCamy = true;}
      else if(cGOBYIZRut == XcCAHlDkHB){CCXsBaodfW = true;}
      if(pXrGCVtogr == yNEzGsUqpf){COQpRqucHQ = true;}
      if(jpKgOWaceL == QbMPGfnKhp){cUUiFmIBSJ = true;}
      if(bwXELgfwge == pVWtIWCDqw){gaCfteIMWV = true;}
      while(yNEzGsUqpf == pXrGCVtogr){EwGKudfYcf = true;}
      while(QbMPGfnKhp == QbMPGfnKhp){PVephLWfix = true;}
      while(pVWtIWCDqw == pVWtIWCDqw){lfEBnyRahZ = true;}
      if(SKcgfBFKpa == true){SKcgfBFKpa = false;}
      if(sCVAFBszur == true){sCVAFBszur = false;}
      if(UOjEDcqKpi == true){UOjEDcqKpi = false;}
      if(pQztNGyeiF == true){pQztNGyeiF = false;}
      if(acTGxmAVoH == true){acTGxmAVoH = false;}
      if(cCIyaDZXcD == true){cCIyaDZXcD = false;}
      if(KuUHjbCamy == true){KuUHjbCamy = false;}
      if(COQpRqucHQ == true){COQpRqucHQ = false;}
      if(cUUiFmIBSJ == true){cUUiFmIBSJ = false;}
      if(gaCfteIMWV == true){gaCfteIMWV = false;}
      if(jYipEOlSfj == true){jYipEOlSfj = false;}
      if(IwPMapZkBw == true){IwPMapZkBw = false;}
      if(TBHdQaLjum == true){TBHdQaLjum = false;}
      if(ihGlfDkddq == true){ihGlfDkddq = false;}
      if(BoUiAkLpFE == true){BoUiAkLpFE = false;}
      if(EWLaCiQFYc == true){EWLaCiQFYc = false;}
      if(CCXsBaodfW == true){CCXsBaodfW = false;}
      if(EwGKudfYcf == true){EwGKudfYcf = false;}
      if(PVephLWfix == true){PVephLWfix = false;}
      if(lfEBnyRahZ == true){lfEBnyRahZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJFAKSFVDL
{ 
  void JUPRuPuelD()
  { 
      bool umgFkJPBBP = false;
      bool ccIlxWnkuT = false;
      bool cgmYgnAhcY = false;
      bool oZToyncKaz = false;
      bool pYCWPUrLRS = false;
      bool HqNRWNAIYw = false;
      bool JgXbaDJTnJ = false;
      bool tdKudDePJL = false;
      bool woQKQxLBRj = false;
      bool mUkdpIBZuM = false;
      bool KYWHYcfSmT = false;
      bool ikzMATQNLd = false;
      bool qHBEVZrgEV = false;
      bool CETxAXSIkm = false;
      bool RsOyBCUXdV = false;
      bool qnORUCWSlz = false;
      bool jzNQQdRCMb = false;
      bool BHbXLxsCCT = false;
      bool EUDhdNpBbx = false;
      bool AAWkCSfygW = false;
      string VQOmAnOFhr;
      string xpotjzhsjx;
      string ISmXDFQEPe;
      string NtISDTAEsk;
      string uoNVcpWeVM;
      string SGiXMCcqjt;
      string XKoCdCgWqQ;
      string yczzBSFRuN;
      string hkiCMHKjFA;
      string qJUyMjzKrZ;
      string IAnFOoGjWs;
      string xKuVMlblpV;
      string rwRqYoIBlR;
      string TtZUEgxdnW;
      string BaNLCfNykZ;
      string HNUVhLixfY;
      string gExEZCkZRe;
      string oyxSURiFns;
      string bJPLJFZDmr;
      string yAxOpwcIlz;
      if(VQOmAnOFhr == IAnFOoGjWs){umgFkJPBBP = true;}
      else if(IAnFOoGjWs == VQOmAnOFhr){KYWHYcfSmT = true;}
      if(xpotjzhsjx == xKuVMlblpV){ccIlxWnkuT = true;}
      else if(xKuVMlblpV == xpotjzhsjx){ikzMATQNLd = true;}
      if(ISmXDFQEPe == rwRqYoIBlR){cgmYgnAhcY = true;}
      else if(rwRqYoIBlR == ISmXDFQEPe){qHBEVZrgEV = true;}
      if(NtISDTAEsk == TtZUEgxdnW){oZToyncKaz = true;}
      else if(TtZUEgxdnW == NtISDTAEsk){CETxAXSIkm = true;}
      if(uoNVcpWeVM == BaNLCfNykZ){pYCWPUrLRS = true;}
      else if(BaNLCfNykZ == uoNVcpWeVM){RsOyBCUXdV = true;}
      if(SGiXMCcqjt == HNUVhLixfY){HqNRWNAIYw = true;}
      else if(HNUVhLixfY == SGiXMCcqjt){qnORUCWSlz = true;}
      if(XKoCdCgWqQ == gExEZCkZRe){JgXbaDJTnJ = true;}
      else if(gExEZCkZRe == XKoCdCgWqQ){jzNQQdRCMb = true;}
      if(yczzBSFRuN == oyxSURiFns){tdKudDePJL = true;}
      if(hkiCMHKjFA == bJPLJFZDmr){woQKQxLBRj = true;}
      if(qJUyMjzKrZ == yAxOpwcIlz){mUkdpIBZuM = true;}
      while(oyxSURiFns == yczzBSFRuN){BHbXLxsCCT = true;}
      while(bJPLJFZDmr == bJPLJFZDmr){EUDhdNpBbx = true;}
      while(yAxOpwcIlz == yAxOpwcIlz){AAWkCSfygW = true;}
      if(umgFkJPBBP == true){umgFkJPBBP = false;}
      if(ccIlxWnkuT == true){ccIlxWnkuT = false;}
      if(cgmYgnAhcY == true){cgmYgnAhcY = false;}
      if(oZToyncKaz == true){oZToyncKaz = false;}
      if(pYCWPUrLRS == true){pYCWPUrLRS = false;}
      if(HqNRWNAIYw == true){HqNRWNAIYw = false;}
      if(JgXbaDJTnJ == true){JgXbaDJTnJ = false;}
      if(tdKudDePJL == true){tdKudDePJL = false;}
      if(woQKQxLBRj == true){woQKQxLBRj = false;}
      if(mUkdpIBZuM == true){mUkdpIBZuM = false;}
      if(KYWHYcfSmT == true){KYWHYcfSmT = false;}
      if(ikzMATQNLd == true){ikzMATQNLd = false;}
      if(qHBEVZrgEV == true){qHBEVZrgEV = false;}
      if(CETxAXSIkm == true){CETxAXSIkm = false;}
      if(RsOyBCUXdV == true){RsOyBCUXdV = false;}
      if(qnORUCWSlz == true){qnORUCWSlz = false;}
      if(jzNQQdRCMb == true){jzNQQdRCMb = false;}
      if(BHbXLxsCCT == true){BHbXLxsCCT = false;}
      if(EUDhdNpBbx == true){EUDhdNpBbx = false;}
      if(AAWkCSfygW == true){AAWkCSfygW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKNKZNIXPO
{ 
  void XBGGOmaZQO()
  { 
      bool NmKPNgrtwM = false;
      bool yUuAJdXDWM = false;
      bool bzMtVnjHyQ = false;
      bool LiUWqTjcFx = false;
      bool cKGPEHzScM = false;
      bool DQaucOaPtZ = false;
      bool xjueAPzXIo = false;
      bool styZjQrwoN = false;
      bool nRelMtHZtc = false;
      bool rUieArPaOo = false;
      bool IbJmSISBLL = false;
      bool VeafkeEISG = false;
      bool IZdexYLSYq = false;
      bool BRgAEMIrTE = false;
      bool bFNhHNtCtV = false;
      bool mGIIfixdos = false;
      bool wzcUJDxZbY = false;
      bool WMoNdDLwXi = false;
      bool eJYDDuJYUU = false;
      bool PeCZHbbrXE = false;
      string NyAxSRabPm;
      string oQIanAUwSR;
      string fPqFPDLzZR;
      string kjOLFNeYBD;
      string nmmbUQMHAV;
      string YSDugxHthO;
      string FaCyCEBwVa;
      string UutPcrcPkz;
      string pEyEsRgSdH;
      string GkqmyNknYQ;
      string OQlZAcYnRo;
      string UqIhYBbyFk;
      string XhSOTiDHQP;
      string HnpUjZRYDP;
      string rrBolObIOx;
      string kminrfxXFQ;
      string YQXCggBnyy;
      string iDtorfgcbF;
      string HusTeUECbD;
      string btSlpbUyHF;
      if(NyAxSRabPm == OQlZAcYnRo){NmKPNgrtwM = true;}
      else if(OQlZAcYnRo == NyAxSRabPm){IbJmSISBLL = true;}
      if(oQIanAUwSR == UqIhYBbyFk){yUuAJdXDWM = true;}
      else if(UqIhYBbyFk == oQIanAUwSR){VeafkeEISG = true;}
      if(fPqFPDLzZR == XhSOTiDHQP){bzMtVnjHyQ = true;}
      else if(XhSOTiDHQP == fPqFPDLzZR){IZdexYLSYq = true;}
      if(kjOLFNeYBD == HnpUjZRYDP){LiUWqTjcFx = true;}
      else if(HnpUjZRYDP == kjOLFNeYBD){BRgAEMIrTE = true;}
      if(nmmbUQMHAV == rrBolObIOx){cKGPEHzScM = true;}
      else if(rrBolObIOx == nmmbUQMHAV){bFNhHNtCtV = true;}
      if(YSDugxHthO == kminrfxXFQ){DQaucOaPtZ = true;}
      else if(kminrfxXFQ == YSDugxHthO){mGIIfixdos = true;}
      if(FaCyCEBwVa == YQXCggBnyy){xjueAPzXIo = true;}
      else if(YQXCggBnyy == FaCyCEBwVa){wzcUJDxZbY = true;}
      if(UutPcrcPkz == iDtorfgcbF){styZjQrwoN = true;}
      if(pEyEsRgSdH == HusTeUECbD){nRelMtHZtc = true;}
      if(GkqmyNknYQ == btSlpbUyHF){rUieArPaOo = true;}
      while(iDtorfgcbF == UutPcrcPkz){WMoNdDLwXi = true;}
      while(HusTeUECbD == HusTeUECbD){eJYDDuJYUU = true;}
      while(btSlpbUyHF == btSlpbUyHF){PeCZHbbrXE = true;}
      if(NmKPNgrtwM == true){NmKPNgrtwM = false;}
      if(yUuAJdXDWM == true){yUuAJdXDWM = false;}
      if(bzMtVnjHyQ == true){bzMtVnjHyQ = false;}
      if(LiUWqTjcFx == true){LiUWqTjcFx = false;}
      if(cKGPEHzScM == true){cKGPEHzScM = false;}
      if(DQaucOaPtZ == true){DQaucOaPtZ = false;}
      if(xjueAPzXIo == true){xjueAPzXIo = false;}
      if(styZjQrwoN == true){styZjQrwoN = false;}
      if(nRelMtHZtc == true){nRelMtHZtc = false;}
      if(rUieArPaOo == true){rUieArPaOo = false;}
      if(IbJmSISBLL == true){IbJmSISBLL = false;}
      if(VeafkeEISG == true){VeafkeEISG = false;}
      if(IZdexYLSYq == true){IZdexYLSYq = false;}
      if(BRgAEMIrTE == true){BRgAEMIrTE = false;}
      if(bFNhHNtCtV == true){bFNhHNtCtV = false;}
      if(mGIIfixdos == true){mGIIfixdos = false;}
      if(wzcUJDxZbY == true){wzcUJDxZbY = false;}
      if(WMoNdDLwXi == true){WMoNdDLwXi = false;}
      if(eJYDDuJYUU == true){eJYDDuJYUU = false;}
      if(PeCZHbbrXE == true){PeCZHbbrXE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRKRNQKUWY
{ 
  void HkESVzCVOL()
  { 
      bool kkWXTZzfzM = false;
      bool jNVuadRGni = false;
      bool PsIMMoETDc = false;
      bool GocelRMUEf = false;
      bool VrQiixxQcq = false;
      bool KYtTzrcJLe = false;
      bool UfcWFtkqIJ = false;
      bool QwCHMWbZdP = false;
      bool qmpMRgtIes = false;
      bool oDIYKpPtdn = false;
      bool LGHTZNWlHb = false;
      bool QDeumgpQEX = false;
      bool zbLPTNncwW = false;
      bool HgupDkfVlE = false;
      bool KIACblXNlc = false;
      bool AzoFnitrAL = false;
      bool ZsokUiHorC = false;
      bool BTdAMqbJmg = false;
      bool paqTVIrpBT = false;
      bool pnVZdQSPhs = false;
      string mtVDcOKgFR;
      string hTZqYNnsXg;
      string VhseOPbyPU;
      string pqxeYcewjF;
      string ywtYmfcfhH;
      string pGzaXEApnN;
      string lLQjbpWuRu;
      string hrJSiYmTqi;
      string lwQIeirVGU;
      string bnHVSlfKxx;
      string IhNlYxxfry;
      string QgyFapuHFr;
      string yBnxTskmAx;
      string scWtZEiejg;
      string lLcIDupBub;
      string pXEFyHsPSe;
      string MJftEnJEeW;
      string HQXXFlXftX;
      string DirYGVYQuS;
      string KSLEUbfiDP;
      if(mtVDcOKgFR == IhNlYxxfry){kkWXTZzfzM = true;}
      else if(IhNlYxxfry == mtVDcOKgFR){LGHTZNWlHb = true;}
      if(hTZqYNnsXg == QgyFapuHFr){jNVuadRGni = true;}
      else if(QgyFapuHFr == hTZqYNnsXg){QDeumgpQEX = true;}
      if(VhseOPbyPU == yBnxTskmAx){PsIMMoETDc = true;}
      else if(yBnxTskmAx == VhseOPbyPU){zbLPTNncwW = true;}
      if(pqxeYcewjF == scWtZEiejg){GocelRMUEf = true;}
      else if(scWtZEiejg == pqxeYcewjF){HgupDkfVlE = true;}
      if(ywtYmfcfhH == lLcIDupBub){VrQiixxQcq = true;}
      else if(lLcIDupBub == ywtYmfcfhH){KIACblXNlc = true;}
      if(pGzaXEApnN == pXEFyHsPSe){KYtTzrcJLe = true;}
      else if(pXEFyHsPSe == pGzaXEApnN){AzoFnitrAL = true;}
      if(lLQjbpWuRu == MJftEnJEeW){UfcWFtkqIJ = true;}
      else if(MJftEnJEeW == lLQjbpWuRu){ZsokUiHorC = true;}
      if(hrJSiYmTqi == HQXXFlXftX){QwCHMWbZdP = true;}
      if(lwQIeirVGU == DirYGVYQuS){qmpMRgtIes = true;}
      if(bnHVSlfKxx == KSLEUbfiDP){oDIYKpPtdn = true;}
      while(HQXXFlXftX == hrJSiYmTqi){BTdAMqbJmg = true;}
      while(DirYGVYQuS == DirYGVYQuS){paqTVIrpBT = true;}
      while(KSLEUbfiDP == KSLEUbfiDP){pnVZdQSPhs = true;}
      if(kkWXTZzfzM == true){kkWXTZzfzM = false;}
      if(jNVuadRGni == true){jNVuadRGni = false;}
      if(PsIMMoETDc == true){PsIMMoETDc = false;}
      if(GocelRMUEf == true){GocelRMUEf = false;}
      if(VrQiixxQcq == true){VrQiixxQcq = false;}
      if(KYtTzrcJLe == true){KYtTzrcJLe = false;}
      if(UfcWFtkqIJ == true){UfcWFtkqIJ = false;}
      if(QwCHMWbZdP == true){QwCHMWbZdP = false;}
      if(qmpMRgtIes == true){qmpMRgtIes = false;}
      if(oDIYKpPtdn == true){oDIYKpPtdn = false;}
      if(LGHTZNWlHb == true){LGHTZNWlHb = false;}
      if(QDeumgpQEX == true){QDeumgpQEX = false;}
      if(zbLPTNncwW == true){zbLPTNncwW = false;}
      if(HgupDkfVlE == true){HgupDkfVlE = false;}
      if(KIACblXNlc == true){KIACblXNlc = false;}
      if(AzoFnitrAL == true){AzoFnitrAL = false;}
      if(ZsokUiHorC == true){ZsokUiHorC = false;}
      if(BTdAMqbJmg == true){BTdAMqbJmg = false;}
      if(paqTVIrpBT == true){paqTVIrpBT = false;}
      if(pnVZdQSPhs == true){pnVZdQSPhs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQGRANIVUA
{ 
  void chdBGnANLu()
  { 
      bool sPSpFdNzAS = false;
      bool hOcBsjeUiI = false;
      bool fIsSichPNs = false;
      bool ogCbnnaoQo = false;
      bool WNjHZriQAI = false;
      bool YaoeykVzGb = false;
      bool uylGdBMBMF = false;
      bool IoDskRYkrp = false;
      bool tROEUNqWcD = false;
      bool RbhntYbcdY = false;
      bool fgDtAiXutg = false;
      bool LkGPhciglP = false;
      bool JpXImgGOzM = false;
      bool pwGTKMNTEl = false;
      bool pucwrgUSFQ = false;
      bool ptqOOpJuHS = false;
      bool bIwhqPdmFV = false;
      bool POczYNMbQF = false;
      bool LnIhWuErEU = false;
      bool CSMkJgzuFc = false;
      string YFKkMoMQnx;
      string JTLTPRQdSb;
      string eIoBuSsAmS;
      string DsKJCesIfZ;
      string uAFAsddgqJ;
      string bUzhdQQIos;
      string wMcUsQJCRk;
      string YIysgdDoIQ;
      string oLIcqisbfk;
      string OjSldhWjGb;
      string UbPGkTVGBz;
      string MaAXEjDAdJ;
      string XgWfVnoMPy;
      string GThfwNwCqX;
      string MlafYmjtgs;
      string eWFxEnFjjx;
      string dJpCrssUbq;
      string nAJGwkFpGh;
      string DteVTjNjaI;
      string HLStsDuYme;
      if(YFKkMoMQnx == UbPGkTVGBz){sPSpFdNzAS = true;}
      else if(UbPGkTVGBz == YFKkMoMQnx){fgDtAiXutg = true;}
      if(JTLTPRQdSb == MaAXEjDAdJ){hOcBsjeUiI = true;}
      else if(MaAXEjDAdJ == JTLTPRQdSb){LkGPhciglP = true;}
      if(eIoBuSsAmS == XgWfVnoMPy){fIsSichPNs = true;}
      else if(XgWfVnoMPy == eIoBuSsAmS){JpXImgGOzM = true;}
      if(DsKJCesIfZ == GThfwNwCqX){ogCbnnaoQo = true;}
      else if(GThfwNwCqX == DsKJCesIfZ){pwGTKMNTEl = true;}
      if(uAFAsddgqJ == MlafYmjtgs){WNjHZriQAI = true;}
      else if(MlafYmjtgs == uAFAsddgqJ){pucwrgUSFQ = true;}
      if(bUzhdQQIos == eWFxEnFjjx){YaoeykVzGb = true;}
      else if(eWFxEnFjjx == bUzhdQQIos){ptqOOpJuHS = true;}
      if(wMcUsQJCRk == dJpCrssUbq){uylGdBMBMF = true;}
      else if(dJpCrssUbq == wMcUsQJCRk){bIwhqPdmFV = true;}
      if(YIysgdDoIQ == nAJGwkFpGh){IoDskRYkrp = true;}
      if(oLIcqisbfk == DteVTjNjaI){tROEUNqWcD = true;}
      if(OjSldhWjGb == HLStsDuYme){RbhntYbcdY = true;}
      while(nAJGwkFpGh == YIysgdDoIQ){POczYNMbQF = true;}
      while(DteVTjNjaI == DteVTjNjaI){LnIhWuErEU = true;}
      while(HLStsDuYme == HLStsDuYme){CSMkJgzuFc = true;}
      if(sPSpFdNzAS == true){sPSpFdNzAS = false;}
      if(hOcBsjeUiI == true){hOcBsjeUiI = false;}
      if(fIsSichPNs == true){fIsSichPNs = false;}
      if(ogCbnnaoQo == true){ogCbnnaoQo = false;}
      if(WNjHZriQAI == true){WNjHZriQAI = false;}
      if(YaoeykVzGb == true){YaoeykVzGb = false;}
      if(uylGdBMBMF == true){uylGdBMBMF = false;}
      if(IoDskRYkrp == true){IoDskRYkrp = false;}
      if(tROEUNqWcD == true){tROEUNqWcD = false;}
      if(RbhntYbcdY == true){RbhntYbcdY = false;}
      if(fgDtAiXutg == true){fgDtAiXutg = false;}
      if(LkGPhciglP == true){LkGPhciglP = false;}
      if(JpXImgGOzM == true){JpXImgGOzM = false;}
      if(pwGTKMNTEl == true){pwGTKMNTEl = false;}
      if(pucwrgUSFQ == true){pucwrgUSFQ = false;}
      if(ptqOOpJuHS == true){ptqOOpJuHS = false;}
      if(bIwhqPdmFV == true){bIwhqPdmFV = false;}
      if(POczYNMbQF == true){POczYNMbQF = false;}
      if(LnIhWuErEU == true){LnIhWuErEU = false;}
      if(CSMkJgzuFc == true){CSMkJgzuFc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWBMFRXZDJ
{ 
  void yDZhqQOfdY()
  { 
      bool KWLPrOcEdy = false;
      bool lXGHlriZsO = false;
      bool hzkflYHRJy = false;
      bool yzyLcSHXgc = false;
      bool KrcoaeEzcs = false;
      bool kFQOiLkfcS = false;
      bool HLufzlZudS = false;
      bool kKsQDpVwFH = false;
      bool THnPNriibR = false;
      bool hbtNVzxxon = false;
      bool FJVKIZMzKs = false;
      bool onZVzzWeSH = false;
      bool CpTLjIQfuE = false;
      bool sYHQBKldHm = false;
      bool fjXhcsBXOW = false;
      bool bRdhkPoJZz = false;
      bool JgEGAPgIUn = false;
      bool MrWeaSRliq = false;
      bool HrRXbauZfl = false;
      bool VcEIdzeRhM = false;
      string ktZjALQQcb;
      string popyhyyoOl;
      string jPahWAVsoz;
      string NyeEwxbTyA;
      string THXSeMqNnj;
      string QGQaaUTrMA;
      string oXbcOrJkCk;
      string VeqNScrHDK;
      string IHFEiGhDda;
      string djGxLwftEm;
      string CGLCNkPCHy;
      string cLoBrgRWtH;
      string JFGaGlYsCV;
      string wxDPICwCqy;
      string pewexSuEFd;
      string dIAwcwzjub;
      string MWzlBfHYso;
      string kOfuRdJbcn;
      string pTnYrmxHmM;
      string CLHOlTfKcR;
      if(ktZjALQQcb == CGLCNkPCHy){KWLPrOcEdy = true;}
      else if(CGLCNkPCHy == ktZjALQQcb){FJVKIZMzKs = true;}
      if(popyhyyoOl == cLoBrgRWtH){lXGHlriZsO = true;}
      else if(cLoBrgRWtH == popyhyyoOl){onZVzzWeSH = true;}
      if(jPahWAVsoz == JFGaGlYsCV){hzkflYHRJy = true;}
      else if(JFGaGlYsCV == jPahWAVsoz){CpTLjIQfuE = true;}
      if(NyeEwxbTyA == wxDPICwCqy){yzyLcSHXgc = true;}
      else if(wxDPICwCqy == NyeEwxbTyA){sYHQBKldHm = true;}
      if(THXSeMqNnj == pewexSuEFd){KrcoaeEzcs = true;}
      else if(pewexSuEFd == THXSeMqNnj){fjXhcsBXOW = true;}
      if(QGQaaUTrMA == dIAwcwzjub){kFQOiLkfcS = true;}
      else if(dIAwcwzjub == QGQaaUTrMA){bRdhkPoJZz = true;}
      if(oXbcOrJkCk == MWzlBfHYso){HLufzlZudS = true;}
      else if(MWzlBfHYso == oXbcOrJkCk){JgEGAPgIUn = true;}
      if(VeqNScrHDK == kOfuRdJbcn){kKsQDpVwFH = true;}
      if(IHFEiGhDda == pTnYrmxHmM){THnPNriibR = true;}
      if(djGxLwftEm == CLHOlTfKcR){hbtNVzxxon = true;}
      while(kOfuRdJbcn == VeqNScrHDK){MrWeaSRliq = true;}
      while(pTnYrmxHmM == pTnYrmxHmM){HrRXbauZfl = true;}
      while(CLHOlTfKcR == CLHOlTfKcR){VcEIdzeRhM = true;}
      if(KWLPrOcEdy == true){KWLPrOcEdy = false;}
      if(lXGHlriZsO == true){lXGHlriZsO = false;}
      if(hzkflYHRJy == true){hzkflYHRJy = false;}
      if(yzyLcSHXgc == true){yzyLcSHXgc = false;}
      if(KrcoaeEzcs == true){KrcoaeEzcs = false;}
      if(kFQOiLkfcS == true){kFQOiLkfcS = false;}
      if(HLufzlZudS == true){HLufzlZudS = false;}
      if(kKsQDpVwFH == true){kKsQDpVwFH = false;}
      if(THnPNriibR == true){THnPNriibR = false;}
      if(hbtNVzxxon == true){hbtNVzxxon = false;}
      if(FJVKIZMzKs == true){FJVKIZMzKs = false;}
      if(onZVzzWeSH == true){onZVzzWeSH = false;}
      if(CpTLjIQfuE == true){CpTLjIQfuE = false;}
      if(sYHQBKldHm == true){sYHQBKldHm = false;}
      if(fjXhcsBXOW == true){fjXhcsBXOW = false;}
      if(bRdhkPoJZz == true){bRdhkPoJZz = false;}
      if(JgEGAPgIUn == true){JgEGAPgIUn = false;}
      if(MrWeaSRliq == true){MrWeaSRliq = false;}
      if(HrRXbauZfl == true){HrRXbauZfl = false;}
      if(VcEIdzeRhM == true){VcEIdzeRhM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDJYLIZJFE
{ 
  void IHWZatebQk()
  { 
      bool ccBOxBKZlR = false;
      bool sbdTuwLFlE = false;
      bool PdwqeQQrWA = false;
      bool xNCoXhqXob = false;
      bool ZFnGoQWyyE = false;
      bool MlxFsygKjf = false;
      bool kSDlTeYowM = false;
      bool EmPJdJpoBN = false;
      bool tSsRmLQxuY = false;
      bool BgnIqHCCmJ = false;
      bool rhBkzZVnbi = false;
      bool IqIVlRYkyI = false;
      bool ObsWLXyGSV = false;
      bool HmCrVLQISN = false;
      bool ocULQKXSWY = false;
      bool hQDeuPndZa = false;
      bool aOVFbUnQAZ = false;
      bool BQSkSlGgGA = false;
      bool AfjsnpjXwF = false;
      bool WliqlZGPju = false;
      string XfUiyJPqIk;
      string rwoTMWdxQo;
      string zKxEXMLBoy;
      string pkXHpGOkeG;
      string UjVDpKfGJY;
      string BrFwlNiPLl;
      string yOCKuGXgdF;
      string IsSKTOnsOM;
      string fEqQxxfaVc;
      string WyZrIGhKIi;
      string mzcEQHYtcW;
      string YoAyFsWkMx;
      string awKBiJTZBN;
      string gdkfYgbmAo;
      string XkyzDgyamO;
      string jwyKHqnaUG;
      string nzrOouEUYX;
      string RikXYpxLxB;
      string LrmmckfZXh;
      string sARsAYriJI;
      if(XfUiyJPqIk == mzcEQHYtcW){ccBOxBKZlR = true;}
      else if(mzcEQHYtcW == XfUiyJPqIk){rhBkzZVnbi = true;}
      if(rwoTMWdxQo == YoAyFsWkMx){sbdTuwLFlE = true;}
      else if(YoAyFsWkMx == rwoTMWdxQo){IqIVlRYkyI = true;}
      if(zKxEXMLBoy == awKBiJTZBN){PdwqeQQrWA = true;}
      else if(awKBiJTZBN == zKxEXMLBoy){ObsWLXyGSV = true;}
      if(pkXHpGOkeG == gdkfYgbmAo){xNCoXhqXob = true;}
      else if(gdkfYgbmAo == pkXHpGOkeG){HmCrVLQISN = true;}
      if(UjVDpKfGJY == XkyzDgyamO){ZFnGoQWyyE = true;}
      else if(XkyzDgyamO == UjVDpKfGJY){ocULQKXSWY = true;}
      if(BrFwlNiPLl == jwyKHqnaUG){MlxFsygKjf = true;}
      else if(jwyKHqnaUG == BrFwlNiPLl){hQDeuPndZa = true;}
      if(yOCKuGXgdF == nzrOouEUYX){kSDlTeYowM = true;}
      else if(nzrOouEUYX == yOCKuGXgdF){aOVFbUnQAZ = true;}
      if(IsSKTOnsOM == RikXYpxLxB){EmPJdJpoBN = true;}
      if(fEqQxxfaVc == LrmmckfZXh){tSsRmLQxuY = true;}
      if(WyZrIGhKIi == sARsAYriJI){BgnIqHCCmJ = true;}
      while(RikXYpxLxB == IsSKTOnsOM){BQSkSlGgGA = true;}
      while(LrmmckfZXh == LrmmckfZXh){AfjsnpjXwF = true;}
      while(sARsAYriJI == sARsAYriJI){WliqlZGPju = true;}
      if(ccBOxBKZlR == true){ccBOxBKZlR = false;}
      if(sbdTuwLFlE == true){sbdTuwLFlE = false;}
      if(PdwqeQQrWA == true){PdwqeQQrWA = false;}
      if(xNCoXhqXob == true){xNCoXhqXob = false;}
      if(ZFnGoQWyyE == true){ZFnGoQWyyE = false;}
      if(MlxFsygKjf == true){MlxFsygKjf = false;}
      if(kSDlTeYowM == true){kSDlTeYowM = false;}
      if(EmPJdJpoBN == true){EmPJdJpoBN = false;}
      if(tSsRmLQxuY == true){tSsRmLQxuY = false;}
      if(BgnIqHCCmJ == true){BgnIqHCCmJ = false;}
      if(rhBkzZVnbi == true){rhBkzZVnbi = false;}
      if(IqIVlRYkyI == true){IqIVlRYkyI = false;}
      if(ObsWLXyGSV == true){ObsWLXyGSV = false;}
      if(HmCrVLQISN == true){HmCrVLQISN = false;}
      if(ocULQKXSWY == true){ocULQKXSWY = false;}
      if(hQDeuPndZa == true){hQDeuPndZa = false;}
      if(aOVFbUnQAZ == true){aOVFbUnQAZ = false;}
      if(BQSkSlGgGA == true){BQSkSlGgGA = false;}
      if(AfjsnpjXwF == true){AfjsnpjXwF = false;}
      if(WliqlZGPju == true){WliqlZGPju = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTLYBKPSSB
{ 
  void bIKMaFcNYN()
  { 
      bool taYWBERRJE = false;
      bool khdFjbKcXw = false;
      bool xktraSIydM = false;
      bool YNUxAhbltA = false;
      bool mNnBLquKCn = false;
      bool THNLqJgfui = false;
      bool uSnweWMgEB = false;
      bool AYiWIjwrfi = false;
      bool XywosQzIFq = false;
      bool BupKEUZqVn = false;
      bool dOFAntYpDH = false;
      bool MnAMLxWyDO = false;
      bool XDaNAEiXSn = false;
      bool KFVqFJruBz = false;
      bool rJFxeNudzH = false;
      bool xanHQZmrAj = false;
      bool KAXPxGRJHB = false;
      bool EbwDVOydhm = false;
      bool IFXKqiQOZe = false;
      bool WzuRnqkpAX = false;
      string npnDqRYwBP;
      string rTHzOwbAgA;
      string VXSUGdatVZ;
      string dBjDEgOeRR;
      string ytccVezPFL;
      string ngdMkQWSwM;
      string qdaalpjEth;
      string gwiPBatozb;
      string dKnJlwXXSn;
      string JwhEZTSCqf;
      string uuVXdqyOKJ;
      string VgTUhgpQop;
      string SLkFXkOdoh;
      string IrySfioQet;
      string yJNIScbNVs;
      string dCMBNiJPAs;
      string cTYbBchAoz;
      string qYktqIyblu;
      string JAIwEFexFw;
      string YYPlQejkHo;
      if(npnDqRYwBP == uuVXdqyOKJ){taYWBERRJE = true;}
      else if(uuVXdqyOKJ == npnDqRYwBP){dOFAntYpDH = true;}
      if(rTHzOwbAgA == VgTUhgpQop){khdFjbKcXw = true;}
      else if(VgTUhgpQop == rTHzOwbAgA){MnAMLxWyDO = true;}
      if(VXSUGdatVZ == SLkFXkOdoh){xktraSIydM = true;}
      else if(SLkFXkOdoh == VXSUGdatVZ){XDaNAEiXSn = true;}
      if(dBjDEgOeRR == IrySfioQet){YNUxAhbltA = true;}
      else if(IrySfioQet == dBjDEgOeRR){KFVqFJruBz = true;}
      if(ytccVezPFL == yJNIScbNVs){mNnBLquKCn = true;}
      else if(yJNIScbNVs == ytccVezPFL){rJFxeNudzH = true;}
      if(ngdMkQWSwM == dCMBNiJPAs){THNLqJgfui = true;}
      else if(dCMBNiJPAs == ngdMkQWSwM){xanHQZmrAj = true;}
      if(qdaalpjEth == cTYbBchAoz){uSnweWMgEB = true;}
      else if(cTYbBchAoz == qdaalpjEth){KAXPxGRJHB = true;}
      if(gwiPBatozb == qYktqIyblu){AYiWIjwrfi = true;}
      if(dKnJlwXXSn == JAIwEFexFw){XywosQzIFq = true;}
      if(JwhEZTSCqf == YYPlQejkHo){BupKEUZqVn = true;}
      while(qYktqIyblu == gwiPBatozb){EbwDVOydhm = true;}
      while(JAIwEFexFw == JAIwEFexFw){IFXKqiQOZe = true;}
      while(YYPlQejkHo == YYPlQejkHo){WzuRnqkpAX = true;}
      if(taYWBERRJE == true){taYWBERRJE = false;}
      if(khdFjbKcXw == true){khdFjbKcXw = false;}
      if(xktraSIydM == true){xktraSIydM = false;}
      if(YNUxAhbltA == true){YNUxAhbltA = false;}
      if(mNnBLquKCn == true){mNnBLquKCn = false;}
      if(THNLqJgfui == true){THNLqJgfui = false;}
      if(uSnweWMgEB == true){uSnweWMgEB = false;}
      if(AYiWIjwrfi == true){AYiWIjwrfi = false;}
      if(XywosQzIFq == true){XywosQzIFq = false;}
      if(BupKEUZqVn == true){BupKEUZqVn = false;}
      if(dOFAntYpDH == true){dOFAntYpDH = false;}
      if(MnAMLxWyDO == true){MnAMLxWyDO = false;}
      if(XDaNAEiXSn == true){XDaNAEiXSn = false;}
      if(KFVqFJruBz == true){KFVqFJruBz = false;}
      if(rJFxeNudzH == true){rJFxeNudzH = false;}
      if(xanHQZmrAj == true){xanHQZmrAj = false;}
      if(KAXPxGRJHB == true){KAXPxGRJHB = false;}
      if(EbwDVOydhm == true){EbwDVOydhm = false;}
      if(IFXKqiQOZe == true){IFXKqiQOZe = false;}
      if(WzuRnqkpAX == true){WzuRnqkpAX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCKGKCQXEY
{ 
  void FHULhsNIAQ()
  { 
      bool ZMHJyVZYmM = false;
      bool JHQWLhxSfi = false;
      bool FGgLymGSYS = false;
      bool MtDFUufPSz = false;
      bool HPCrxPLoAO = false;
      bool IerUgTeuLL = false;
      bool OHzUzOEKBP = false;
      bool BgAfbpDnOh = false;
      bool aRSJKgBhXA = false;
      bool QjDGkzPhrh = false;
      bool KAmjMaeLsq = false;
      bool PpgcjwnoKS = false;
      bool MWmBzRdsub = false;
      bool ZVwgXadhxi = false;
      bool CpngjZDaWn = false;
      bool KZWZUnNlju = false;
      bool wkQQQttzFJ = false;
      bool SFraQWhFQY = false;
      bool NDWHQAzWMi = false;
      bool MryBmRYWPp = false;
      string mmJBOjwPUg;
      string xKafZkYcPk;
      string graCwXWmzc;
      string dEkaBiShgY;
      string rfZOJsrIZs;
      string aYGCDtLGFp;
      string MIQqDrZzdp;
      string SqwqsBRMsC;
      string fNMGCEyhWH;
      string WLcpLjOiKQ;
      string TrdjZjcPJC;
      string bzNCJyuKnz;
      string tqcWSGOFeI;
      string liCbimicfS;
      string biYUeXyafN;
      string nEtLWbPHRT;
      string VWjAQsxlSV;
      string OSdVXKSHqt;
      string ImZRUgnpEG;
      string XbLLwFyXEl;
      if(mmJBOjwPUg == TrdjZjcPJC){ZMHJyVZYmM = true;}
      else if(TrdjZjcPJC == mmJBOjwPUg){KAmjMaeLsq = true;}
      if(xKafZkYcPk == bzNCJyuKnz){JHQWLhxSfi = true;}
      else if(bzNCJyuKnz == xKafZkYcPk){PpgcjwnoKS = true;}
      if(graCwXWmzc == tqcWSGOFeI){FGgLymGSYS = true;}
      else if(tqcWSGOFeI == graCwXWmzc){MWmBzRdsub = true;}
      if(dEkaBiShgY == liCbimicfS){MtDFUufPSz = true;}
      else if(liCbimicfS == dEkaBiShgY){ZVwgXadhxi = true;}
      if(rfZOJsrIZs == biYUeXyafN){HPCrxPLoAO = true;}
      else if(biYUeXyafN == rfZOJsrIZs){CpngjZDaWn = true;}
      if(aYGCDtLGFp == nEtLWbPHRT){IerUgTeuLL = true;}
      else if(nEtLWbPHRT == aYGCDtLGFp){KZWZUnNlju = true;}
      if(MIQqDrZzdp == VWjAQsxlSV){OHzUzOEKBP = true;}
      else if(VWjAQsxlSV == MIQqDrZzdp){wkQQQttzFJ = true;}
      if(SqwqsBRMsC == OSdVXKSHqt){BgAfbpDnOh = true;}
      if(fNMGCEyhWH == ImZRUgnpEG){aRSJKgBhXA = true;}
      if(WLcpLjOiKQ == XbLLwFyXEl){QjDGkzPhrh = true;}
      while(OSdVXKSHqt == SqwqsBRMsC){SFraQWhFQY = true;}
      while(ImZRUgnpEG == ImZRUgnpEG){NDWHQAzWMi = true;}
      while(XbLLwFyXEl == XbLLwFyXEl){MryBmRYWPp = true;}
      if(ZMHJyVZYmM == true){ZMHJyVZYmM = false;}
      if(JHQWLhxSfi == true){JHQWLhxSfi = false;}
      if(FGgLymGSYS == true){FGgLymGSYS = false;}
      if(MtDFUufPSz == true){MtDFUufPSz = false;}
      if(HPCrxPLoAO == true){HPCrxPLoAO = false;}
      if(IerUgTeuLL == true){IerUgTeuLL = false;}
      if(OHzUzOEKBP == true){OHzUzOEKBP = false;}
      if(BgAfbpDnOh == true){BgAfbpDnOh = false;}
      if(aRSJKgBhXA == true){aRSJKgBhXA = false;}
      if(QjDGkzPhrh == true){QjDGkzPhrh = false;}
      if(KAmjMaeLsq == true){KAmjMaeLsq = false;}
      if(PpgcjwnoKS == true){PpgcjwnoKS = false;}
      if(MWmBzRdsub == true){MWmBzRdsub = false;}
      if(ZVwgXadhxi == true){ZVwgXadhxi = false;}
      if(CpngjZDaWn == true){CpngjZDaWn = false;}
      if(KZWZUnNlju == true){KZWZUnNlju = false;}
      if(wkQQQttzFJ == true){wkQQQttzFJ = false;}
      if(SFraQWhFQY == true){SFraQWhFQY = false;}
      if(NDWHQAzWMi == true){NDWHQAzWMi = false;}
      if(MryBmRYWPp == true){MryBmRYWPp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJIVOUTUZW
{ 
  void OoLSSXluus()
  { 
      bool FQdBQYumcY = false;
      bool pcTIDYtYUa = false;
      bool jVwVBrFrbF = false;
      bool KjrPffjZUh = false;
      bool OipGcYjKdV = false;
      bool fZplhiUIAY = false;
      bool TCLWNFjDcW = false;
      bool oTDlMBfprb = false;
      bool ItOGZjtGhw = false;
      bool LbZwOLXSrW = false;
      bool ofgHgLWDZg = false;
      bool DePXQYnEwd = false;
      bool KcVgKMtHXA = false;
      bool cMxVmbNGYO = false;
      bool NqfArgLBeo = false;
      bool WSVOLLKAwT = false;
      bool QOeYDphtkn = false;
      bool LgehPTxUnc = false;
      bool BsbicKqhJb = false;
      bool RMKFxzMHxC = false;
      string SzLejEbcgw;
      string ZFCYeQgWjy;
      string TdWEHaqCtV;
      string WmxkDnpkzZ;
      string ILcKoeEdQS;
      string QYTYWocGWJ;
      string NYiKZmIRVq;
      string auWKpHAMPc;
      string WNlaEySXNN;
      string LiNpLjcRjC;
      string WmIYrUCJiP;
      string oQptlzlHGb;
      string TjEHeqhfyF;
      string ehbNFjEMhi;
      string wJnyYtsSEM;
      string yULIhlhBtB;
      string mVKckGoboC;
      string uYZXfJwFhk;
      string xOblHJWSeS;
      string BDSguZzLNR;
      if(SzLejEbcgw == WmIYrUCJiP){FQdBQYumcY = true;}
      else if(WmIYrUCJiP == SzLejEbcgw){ofgHgLWDZg = true;}
      if(ZFCYeQgWjy == oQptlzlHGb){pcTIDYtYUa = true;}
      else if(oQptlzlHGb == ZFCYeQgWjy){DePXQYnEwd = true;}
      if(TdWEHaqCtV == TjEHeqhfyF){jVwVBrFrbF = true;}
      else if(TjEHeqhfyF == TdWEHaqCtV){KcVgKMtHXA = true;}
      if(WmxkDnpkzZ == ehbNFjEMhi){KjrPffjZUh = true;}
      else if(ehbNFjEMhi == WmxkDnpkzZ){cMxVmbNGYO = true;}
      if(ILcKoeEdQS == wJnyYtsSEM){OipGcYjKdV = true;}
      else if(wJnyYtsSEM == ILcKoeEdQS){NqfArgLBeo = true;}
      if(QYTYWocGWJ == yULIhlhBtB){fZplhiUIAY = true;}
      else if(yULIhlhBtB == QYTYWocGWJ){WSVOLLKAwT = true;}
      if(NYiKZmIRVq == mVKckGoboC){TCLWNFjDcW = true;}
      else if(mVKckGoboC == NYiKZmIRVq){QOeYDphtkn = true;}
      if(auWKpHAMPc == uYZXfJwFhk){oTDlMBfprb = true;}
      if(WNlaEySXNN == xOblHJWSeS){ItOGZjtGhw = true;}
      if(LiNpLjcRjC == BDSguZzLNR){LbZwOLXSrW = true;}
      while(uYZXfJwFhk == auWKpHAMPc){LgehPTxUnc = true;}
      while(xOblHJWSeS == xOblHJWSeS){BsbicKqhJb = true;}
      while(BDSguZzLNR == BDSguZzLNR){RMKFxzMHxC = true;}
      if(FQdBQYumcY == true){FQdBQYumcY = false;}
      if(pcTIDYtYUa == true){pcTIDYtYUa = false;}
      if(jVwVBrFrbF == true){jVwVBrFrbF = false;}
      if(KjrPffjZUh == true){KjrPffjZUh = false;}
      if(OipGcYjKdV == true){OipGcYjKdV = false;}
      if(fZplhiUIAY == true){fZplhiUIAY = false;}
      if(TCLWNFjDcW == true){TCLWNFjDcW = false;}
      if(oTDlMBfprb == true){oTDlMBfprb = false;}
      if(ItOGZjtGhw == true){ItOGZjtGhw = false;}
      if(LbZwOLXSrW == true){LbZwOLXSrW = false;}
      if(ofgHgLWDZg == true){ofgHgLWDZg = false;}
      if(DePXQYnEwd == true){DePXQYnEwd = false;}
      if(KcVgKMtHXA == true){KcVgKMtHXA = false;}
      if(cMxVmbNGYO == true){cMxVmbNGYO = false;}
      if(NqfArgLBeo == true){NqfArgLBeo = false;}
      if(WSVOLLKAwT == true){WSVOLLKAwT = false;}
      if(QOeYDphtkn == true){QOeYDphtkn = false;}
      if(LgehPTxUnc == true){LgehPTxUnc = false;}
      if(BsbicKqhJb == true){BsbicKqhJb = false;}
      if(RMKFxzMHxC == true){RMKFxzMHxC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFWGAROXFW
{ 
  void cPxYUpGukT()
  { 
      bool MRJuixLGVi = false;
      bool bbAjpKbmkF = false;
      bool YMQWVUPRqN = false;
      bool ieHggARLYe = false;
      bool sTzZOUMuEq = false;
      bool xUgEkzAmYN = false;
      bool gtPHzwUSCp = false;
      bool sQNFMFMqHB = false;
      bool HUMAQOyDug = false;
      bool zemLxzErZR = false;
      bool AtrOygGarf = false;
      bool lIeXFMgOpk = false;
      bool yQWUpOcCIM = false;
      bool AURpANbxCj = false;
      bool HXLPtpzPFk = false;
      bool RoBoTiWXYi = false;
      bool DDSeeRqoWr = false;
      bool jjMGcZFHZz = false;
      bool ONxWtKTbWQ = false;
      bool pEYSfEFfjc = false;
      string rCCAgWUhXa;
      string qCKOzVrAVs;
      string oFEpGAjoxN;
      string OXMOYELsFq;
      string bXtTnpcjNb;
      string kzzzEmxLsg;
      string mfkKMSowou;
      string JztdQQKkCQ;
      string WzbUbOYNJl;
      string GAzYEwmjGU;
      string AftSRlFUhn;
      string bMIcJmEPix;
      string tbmCnJzVZU;
      string cadhPpEIDo;
      string JDeUKtqWOQ;
      string rXAJZYsrdI;
      string miuNKAhZMT;
      string huMsnqwRrt;
      string RbHIbFaUIp;
      string xMeuCZHRJK;
      if(rCCAgWUhXa == AftSRlFUhn){MRJuixLGVi = true;}
      else if(AftSRlFUhn == rCCAgWUhXa){AtrOygGarf = true;}
      if(qCKOzVrAVs == bMIcJmEPix){bbAjpKbmkF = true;}
      else if(bMIcJmEPix == qCKOzVrAVs){lIeXFMgOpk = true;}
      if(oFEpGAjoxN == tbmCnJzVZU){YMQWVUPRqN = true;}
      else if(tbmCnJzVZU == oFEpGAjoxN){yQWUpOcCIM = true;}
      if(OXMOYELsFq == cadhPpEIDo){ieHggARLYe = true;}
      else if(cadhPpEIDo == OXMOYELsFq){AURpANbxCj = true;}
      if(bXtTnpcjNb == JDeUKtqWOQ){sTzZOUMuEq = true;}
      else if(JDeUKtqWOQ == bXtTnpcjNb){HXLPtpzPFk = true;}
      if(kzzzEmxLsg == rXAJZYsrdI){xUgEkzAmYN = true;}
      else if(rXAJZYsrdI == kzzzEmxLsg){RoBoTiWXYi = true;}
      if(mfkKMSowou == miuNKAhZMT){gtPHzwUSCp = true;}
      else if(miuNKAhZMT == mfkKMSowou){DDSeeRqoWr = true;}
      if(JztdQQKkCQ == huMsnqwRrt){sQNFMFMqHB = true;}
      if(WzbUbOYNJl == RbHIbFaUIp){HUMAQOyDug = true;}
      if(GAzYEwmjGU == xMeuCZHRJK){zemLxzErZR = true;}
      while(huMsnqwRrt == JztdQQKkCQ){jjMGcZFHZz = true;}
      while(RbHIbFaUIp == RbHIbFaUIp){ONxWtKTbWQ = true;}
      while(xMeuCZHRJK == xMeuCZHRJK){pEYSfEFfjc = true;}
      if(MRJuixLGVi == true){MRJuixLGVi = false;}
      if(bbAjpKbmkF == true){bbAjpKbmkF = false;}
      if(YMQWVUPRqN == true){YMQWVUPRqN = false;}
      if(ieHggARLYe == true){ieHggARLYe = false;}
      if(sTzZOUMuEq == true){sTzZOUMuEq = false;}
      if(xUgEkzAmYN == true){xUgEkzAmYN = false;}
      if(gtPHzwUSCp == true){gtPHzwUSCp = false;}
      if(sQNFMFMqHB == true){sQNFMFMqHB = false;}
      if(HUMAQOyDug == true){HUMAQOyDug = false;}
      if(zemLxzErZR == true){zemLxzErZR = false;}
      if(AtrOygGarf == true){AtrOygGarf = false;}
      if(lIeXFMgOpk == true){lIeXFMgOpk = false;}
      if(yQWUpOcCIM == true){yQWUpOcCIM = false;}
      if(AURpANbxCj == true){AURpANbxCj = false;}
      if(HXLPtpzPFk == true){HXLPtpzPFk = false;}
      if(RoBoTiWXYi == true){RoBoTiWXYi = false;}
      if(DDSeeRqoWr == true){DDSeeRqoWr = false;}
      if(jjMGcZFHZz == true){jjMGcZFHZz = false;}
      if(ONxWtKTbWQ == true){ONxWtKTbWQ = false;}
      if(pEYSfEFfjc == true){pEYSfEFfjc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGMDXCEOOF
{ 
  void ELqOPSTqHF()
  { 
      bool rytJAHGbhx = false;
      bool VBOFpwHVBn = false;
      bool LhXYnqJUGP = false;
      bool PIKTxQXkek = false;
      bool gFExwbrhOU = false;
      bool xoxVCJaUUI = false;
      bool ykUSgMquHY = false;
      bool YWqPHGcZcM = false;
      bool zbGlSZLnRm = false;
      bool pCPVmujlPi = false;
      bool jxZouZygNw = false;
      bool gArIJWdiAH = false;
      bool BDcUhVGUcL = false;
      bool VqJsbCBRpr = false;
      bool bdaVGpKGMP = false;
      bool RBlIhgTFGZ = false;
      bool ScECZoqygG = false;
      bool UMrHeWbHNr = false;
      bool KAIMtTFALt = false;
      bool iwKQYzZYuQ = false;
      string GbczqdHAng;
      string UAAUSAEMJc;
      string hrBOotrySm;
      string ZsNMxuQfsi;
      string txFjkQQGTV;
      string osDbeOZNJx;
      string kJgBHammWW;
      string iYTZijmRcY;
      string dlexxfolgi;
      string UCVwxjQEcJ;
      string dcjwlQZcsu;
      string bIkkTzejDa;
      string lAGnBgCWcy;
      string ThnStABhKf;
      string GLslGMQjcx;
      string FfABXcWutF;
      string OCAtbsUSpS;
      string xxZXTaHUgo;
      string PRtesmhluR;
      string dGmEQEKyJN;
      if(GbczqdHAng == dcjwlQZcsu){rytJAHGbhx = true;}
      else if(dcjwlQZcsu == GbczqdHAng){jxZouZygNw = true;}
      if(UAAUSAEMJc == bIkkTzejDa){VBOFpwHVBn = true;}
      else if(bIkkTzejDa == UAAUSAEMJc){gArIJWdiAH = true;}
      if(hrBOotrySm == lAGnBgCWcy){LhXYnqJUGP = true;}
      else if(lAGnBgCWcy == hrBOotrySm){BDcUhVGUcL = true;}
      if(ZsNMxuQfsi == ThnStABhKf){PIKTxQXkek = true;}
      else if(ThnStABhKf == ZsNMxuQfsi){VqJsbCBRpr = true;}
      if(txFjkQQGTV == GLslGMQjcx){gFExwbrhOU = true;}
      else if(GLslGMQjcx == txFjkQQGTV){bdaVGpKGMP = true;}
      if(osDbeOZNJx == FfABXcWutF){xoxVCJaUUI = true;}
      else if(FfABXcWutF == osDbeOZNJx){RBlIhgTFGZ = true;}
      if(kJgBHammWW == OCAtbsUSpS){ykUSgMquHY = true;}
      else if(OCAtbsUSpS == kJgBHammWW){ScECZoqygG = true;}
      if(iYTZijmRcY == xxZXTaHUgo){YWqPHGcZcM = true;}
      if(dlexxfolgi == PRtesmhluR){zbGlSZLnRm = true;}
      if(UCVwxjQEcJ == dGmEQEKyJN){pCPVmujlPi = true;}
      while(xxZXTaHUgo == iYTZijmRcY){UMrHeWbHNr = true;}
      while(PRtesmhluR == PRtesmhluR){KAIMtTFALt = true;}
      while(dGmEQEKyJN == dGmEQEKyJN){iwKQYzZYuQ = true;}
      if(rytJAHGbhx == true){rytJAHGbhx = false;}
      if(VBOFpwHVBn == true){VBOFpwHVBn = false;}
      if(LhXYnqJUGP == true){LhXYnqJUGP = false;}
      if(PIKTxQXkek == true){PIKTxQXkek = false;}
      if(gFExwbrhOU == true){gFExwbrhOU = false;}
      if(xoxVCJaUUI == true){xoxVCJaUUI = false;}
      if(ykUSgMquHY == true){ykUSgMquHY = false;}
      if(YWqPHGcZcM == true){YWqPHGcZcM = false;}
      if(zbGlSZLnRm == true){zbGlSZLnRm = false;}
      if(pCPVmujlPi == true){pCPVmujlPi = false;}
      if(jxZouZygNw == true){jxZouZygNw = false;}
      if(gArIJWdiAH == true){gArIJWdiAH = false;}
      if(BDcUhVGUcL == true){BDcUhVGUcL = false;}
      if(VqJsbCBRpr == true){VqJsbCBRpr = false;}
      if(bdaVGpKGMP == true){bdaVGpKGMP = false;}
      if(RBlIhgTFGZ == true){RBlIhgTFGZ = false;}
      if(ScECZoqygG == true){ScECZoqygG = false;}
      if(UMrHeWbHNr == true){UMrHeWbHNr = false;}
      if(KAIMtTFALt == true){KAIMtTFALt = false;}
      if(iwKQYzZYuQ == true){iwKQYzZYuQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJHYZFQGRK
{ 
  void sYARhjSctC()
  { 
      bool uErwFCFWEi = false;
      bool EeVfmIxXSX = false;
      bool RPdmZnnChC = false;
      bool NaMUAqcKOx = false;
      bool kwJEJsUBEg = false;
      bool UCNSgeZEWR = false;
      bool NDnCUdSAeu = false;
      bool flIVmVFZcg = false;
      bool SmxBgLMtnV = false;
      bool RXnwjgHGif = false;
      bool aTWIBhsrfL = false;
      bool YAapzZFmVJ = false;
      bool QXMJdHyLlF = false;
      bool NyqxGyPozy = false;
      bool RUOcwQxyxJ = false;
      bool aTkZPCHNes = false;
      bool jgFZxZJdjA = false;
      bool JQmXquJiMM = false;
      bool KzOcetNQgD = false;
      bool pCKGNkOofW = false;
      string giIpwnGqpU;
      string rCkNncmAkR;
      string ajFrOxCUto;
      string sSFVdXNAyh;
      string pQlwDRDcNR;
      string eLBQNwdQby;
      string klxAbYwOjP;
      string PmCCaJyJox;
      string tZGcKhRoIg;
      string txYzwDTkTd;
      string UnrxBqIyoE;
      string yTbdELeUpt;
      string HHGCVROCFX;
      string pNoKbFgIaS;
      string YSzDiZVtuk;
      string XztZWNhpbi;
      string cFrRNjeQCy;
      string eVsXUnICTu;
      string wUHUzpSOmO;
      string XqgqoSZgpy;
      if(giIpwnGqpU == UnrxBqIyoE){uErwFCFWEi = true;}
      else if(UnrxBqIyoE == giIpwnGqpU){aTWIBhsrfL = true;}
      if(rCkNncmAkR == yTbdELeUpt){EeVfmIxXSX = true;}
      else if(yTbdELeUpt == rCkNncmAkR){YAapzZFmVJ = true;}
      if(ajFrOxCUto == HHGCVROCFX){RPdmZnnChC = true;}
      else if(HHGCVROCFX == ajFrOxCUto){QXMJdHyLlF = true;}
      if(sSFVdXNAyh == pNoKbFgIaS){NaMUAqcKOx = true;}
      else if(pNoKbFgIaS == sSFVdXNAyh){NyqxGyPozy = true;}
      if(pQlwDRDcNR == YSzDiZVtuk){kwJEJsUBEg = true;}
      else if(YSzDiZVtuk == pQlwDRDcNR){RUOcwQxyxJ = true;}
      if(eLBQNwdQby == XztZWNhpbi){UCNSgeZEWR = true;}
      else if(XztZWNhpbi == eLBQNwdQby){aTkZPCHNes = true;}
      if(klxAbYwOjP == cFrRNjeQCy){NDnCUdSAeu = true;}
      else if(cFrRNjeQCy == klxAbYwOjP){jgFZxZJdjA = true;}
      if(PmCCaJyJox == eVsXUnICTu){flIVmVFZcg = true;}
      if(tZGcKhRoIg == wUHUzpSOmO){SmxBgLMtnV = true;}
      if(txYzwDTkTd == XqgqoSZgpy){RXnwjgHGif = true;}
      while(eVsXUnICTu == PmCCaJyJox){JQmXquJiMM = true;}
      while(wUHUzpSOmO == wUHUzpSOmO){KzOcetNQgD = true;}
      while(XqgqoSZgpy == XqgqoSZgpy){pCKGNkOofW = true;}
      if(uErwFCFWEi == true){uErwFCFWEi = false;}
      if(EeVfmIxXSX == true){EeVfmIxXSX = false;}
      if(RPdmZnnChC == true){RPdmZnnChC = false;}
      if(NaMUAqcKOx == true){NaMUAqcKOx = false;}
      if(kwJEJsUBEg == true){kwJEJsUBEg = false;}
      if(UCNSgeZEWR == true){UCNSgeZEWR = false;}
      if(NDnCUdSAeu == true){NDnCUdSAeu = false;}
      if(flIVmVFZcg == true){flIVmVFZcg = false;}
      if(SmxBgLMtnV == true){SmxBgLMtnV = false;}
      if(RXnwjgHGif == true){RXnwjgHGif = false;}
      if(aTWIBhsrfL == true){aTWIBhsrfL = false;}
      if(YAapzZFmVJ == true){YAapzZFmVJ = false;}
      if(QXMJdHyLlF == true){QXMJdHyLlF = false;}
      if(NyqxGyPozy == true){NyqxGyPozy = false;}
      if(RUOcwQxyxJ == true){RUOcwQxyxJ = false;}
      if(aTkZPCHNes == true){aTkZPCHNes = false;}
      if(jgFZxZJdjA == true){jgFZxZJdjA = false;}
      if(JQmXquJiMM == true){JQmXquJiMM = false;}
      if(KzOcetNQgD == true){KzOcetNQgD = false;}
      if(pCKGNkOofW == true){pCKGNkOofW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSUMCKXGKX
{ 
  void WSrcdJSupb()
  { 
      bool QgXdKFzQEi = false;
      bool eELYnTuRPw = false;
      bool ZYkxVpHLxt = false;
      bool SGbfwuxzzU = false;
      bool sDZBAtdFWE = false;
      bool CnMgIrwZHU = false;
      bool xmSKPYbecr = false;
      bool WwRuDVziwa = false;
      bool LCorqdsuWE = false;
      bool zWqeWFkPkb = false;
      bool SycdhGWQcm = false;
      bool rNdfJuxZSl = false;
      bool egHXszEmYx = false;
      bool kjxUIMYLKj = false;
      bool HcRjMlsLVb = false;
      bool HKwzwkpEji = false;
      bool CjrfCIPIWw = false;
      bool VlPidCOXLH = false;
      bool FsRwoamxXX = false;
      bool WUaahXjlhD = false;
      string KEKdaEkAAJ;
      string AXzmBlysJF;
      string hYloyKXrYk;
      string XgxHQSmDqT;
      string pxpyhpWoEx;
      string IBTWmkSVeP;
      string fsaPlTaqVi;
      string yuBoOjinGI;
      string ninbcVMZUe;
      string ARXamxVaMO;
      string OfSVyMzdHC;
      string CeOWbwFzmP;
      string GBWqhgWaBR;
      string OIarsHQRcP;
      string WhRRbUDByq;
      string rVnxHNJamR;
      string pXbpntDVcU;
      string fmWWrYiFON;
      string cVcKZrUdkf;
      string ypeKYyFbch;
      if(KEKdaEkAAJ == OfSVyMzdHC){QgXdKFzQEi = true;}
      else if(OfSVyMzdHC == KEKdaEkAAJ){SycdhGWQcm = true;}
      if(AXzmBlysJF == CeOWbwFzmP){eELYnTuRPw = true;}
      else if(CeOWbwFzmP == AXzmBlysJF){rNdfJuxZSl = true;}
      if(hYloyKXrYk == GBWqhgWaBR){ZYkxVpHLxt = true;}
      else if(GBWqhgWaBR == hYloyKXrYk){egHXszEmYx = true;}
      if(XgxHQSmDqT == OIarsHQRcP){SGbfwuxzzU = true;}
      else if(OIarsHQRcP == XgxHQSmDqT){kjxUIMYLKj = true;}
      if(pxpyhpWoEx == WhRRbUDByq){sDZBAtdFWE = true;}
      else if(WhRRbUDByq == pxpyhpWoEx){HcRjMlsLVb = true;}
      if(IBTWmkSVeP == rVnxHNJamR){CnMgIrwZHU = true;}
      else if(rVnxHNJamR == IBTWmkSVeP){HKwzwkpEji = true;}
      if(fsaPlTaqVi == pXbpntDVcU){xmSKPYbecr = true;}
      else if(pXbpntDVcU == fsaPlTaqVi){CjrfCIPIWw = true;}
      if(yuBoOjinGI == fmWWrYiFON){WwRuDVziwa = true;}
      if(ninbcVMZUe == cVcKZrUdkf){LCorqdsuWE = true;}
      if(ARXamxVaMO == ypeKYyFbch){zWqeWFkPkb = true;}
      while(fmWWrYiFON == yuBoOjinGI){VlPidCOXLH = true;}
      while(cVcKZrUdkf == cVcKZrUdkf){FsRwoamxXX = true;}
      while(ypeKYyFbch == ypeKYyFbch){WUaahXjlhD = true;}
      if(QgXdKFzQEi == true){QgXdKFzQEi = false;}
      if(eELYnTuRPw == true){eELYnTuRPw = false;}
      if(ZYkxVpHLxt == true){ZYkxVpHLxt = false;}
      if(SGbfwuxzzU == true){SGbfwuxzzU = false;}
      if(sDZBAtdFWE == true){sDZBAtdFWE = false;}
      if(CnMgIrwZHU == true){CnMgIrwZHU = false;}
      if(xmSKPYbecr == true){xmSKPYbecr = false;}
      if(WwRuDVziwa == true){WwRuDVziwa = false;}
      if(LCorqdsuWE == true){LCorqdsuWE = false;}
      if(zWqeWFkPkb == true){zWqeWFkPkb = false;}
      if(SycdhGWQcm == true){SycdhGWQcm = false;}
      if(rNdfJuxZSl == true){rNdfJuxZSl = false;}
      if(egHXszEmYx == true){egHXszEmYx = false;}
      if(kjxUIMYLKj == true){kjxUIMYLKj = false;}
      if(HcRjMlsLVb == true){HcRjMlsLVb = false;}
      if(HKwzwkpEji == true){HKwzwkpEji = false;}
      if(CjrfCIPIWw == true){CjrfCIPIWw = false;}
      if(VlPidCOXLH == true){VlPidCOXLH = false;}
      if(FsRwoamxXX == true){FsRwoamxXX = false;}
      if(WUaahXjlhD == true){WUaahXjlhD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPFGFSUELB
{ 
  void onHjPSQInl()
  { 
      bool ATeBqpsiDo = false;
      bool XmHOIIYsNx = false;
      bool yBzaelIUxE = false;
      bool ECqRFNWrxj = false;
      bool OCdchZRpph = false;
      bool SPAPByUDWF = false;
      bool hYlyjVupIu = false;
      bool lgwciwXVsE = false;
      bool TSeOlnBbQG = false;
      bool sSUqCoPesL = false;
      bool ebgtukTWfE = false;
      bool ayKRkOtWLu = false;
      bool TSYCCTLEas = false;
      bool frcgZrljSA = false;
      bool UewLetHDGm = false;
      bool usTxqLCerb = false;
      bool ZOulYiUcqr = false;
      bool cJEKaoWNWH = false;
      bool LHymymYfoO = false;
      bool pHrqaGiJmw = false;
      string NRjQKJyNWT;
      string XpdVnnVcxd;
      string WzPQnxbdEF;
      string xxFNqAsQBs;
      string JedckoeEwF;
      string dgdlTOCTbN;
      string gTIQWZjQdm;
      string tEaDTrVmfz;
      string RXhzaPSTtc;
      string yZonLpWMFK;
      string ENZIKZFaRa;
      string sPmbuJlIoG;
      string GQWBnTOmqd;
      string VIgVtDyYoB;
      string KrBSjilMsC;
      string DNWzDnqYTp;
      string KSinFjiRhq;
      string LNTnwOPEQF;
      string hBtoZIkgRG;
      string MYEyqqJNMz;
      if(NRjQKJyNWT == ENZIKZFaRa){ATeBqpsiDo = true;}
      else if(ENZIKZFaRa == NRjQKJyNWT){ebgtukTWfE = true;}
      if(XpdVnnVcxd == sPmbuJlIoG){XmHOIIYsNx = true;}
      else if(sPmbuJlIoG == XpdVnnVcxd){ayKRkOtWLu = true;}
      if(WzPQnxbdEF == GQWBnTOmqd){yBzaelIUxE = true;}
      else if(GQWBnTOmqd == WzPQnxbdEF){TSYCCTLEas = true;}
      if(xxFNqAsQBs == VIgVtDyYoB){ECqRFNWrxj = true;}
      else if(VIgVtDyYoB == xxFNqAsQBs){frcgZrljSA = true;}
      if(JedckoeEwF == KrBSjilMsC){OCdchZRpph = true;}
      else if(KrBSjilMsC == JedckoeEwF){UewLetHDGm = true;}
      if(dgdlTOCTbN == DNWzDnqYTp){SPAPByUDWF = true;}
      else if(DNWzDnqYTp == dgdlTOCTbN){usTxqLCerb = true;}
      if(gTIQWZjQdm == KSinFjiRhq){hYlyjVupIu = true;}
      else if(KSinFjiRhq == gTIQWZjQdm){ZOulYiUcqr = true;}
      if(tEaDTrVmfz == LNTnwOPEQF){lgwciwXVsE = true;}
      if(RXhzaPSTtc == hBtoZIkgRG){TSeOlnBbQG = true;}
      if(yZonLpWMFK == MYEyqqJNMz){sSUqCoPesL = true;}
      while(LNTnwOPEQF == tEaDTrVmfz){cJEKaoWNWH = true;}
      while(hBtoZIkgRG == hBtoZIkgRG){LHymymYfoO = true;}
      while(MYEyqqJNMz == MYEyqqJNMz){pHrqaGiJmw = true;}
      if(ATeBqpsiDo == true){ATeBqpsiDo = false;}
      if(XmHOIIYsNx == true){XmHOIIYsNx = false;}
      if(yBzaelIUxE == true){yBzaelIUxE = false;}
      if(ECqRFNWrxj == true){ECqRFNWrxj = false;}
      if(OCdchZRpph == true){OCdchZRpph = false;}
      if(SPAPByUDWF == true){SPAPByUDWF = false;}
      if(hYlyjVupIu == true){hYlyjVupIu = false;}
      if(lgwciwXVsE == true){lgwciwXVsE = false;}
      if(TSeOlnBbQG == true){TSeOlnBbQG = false;}
      if(sSUqCoPesL == true){sSUqCoPesL = false;}
      if(ebgtukTWfE == true){ebgtukTWfE = false;}
      if(ayKRkOtWLu == true){ayKRkOtWLu = false;}
      if(TSYCCTLEas == true){TSYCCTLEas = false;}
      if(frcgZrljSA == true){frcgZrljSA = false;}
      if(UewLetHDGm == true){UewLetHDGm = false;}
      if(usTxqLCerb == true){usTxqLCerb = false;}
      if(ZOulYiUcqr == true){ZOulYiUcqr = false;}
      if(cJEKaoWNWH == true){cJEKaoWNWH = false;}
      if(LHymymYfoO == true){LHymymYfoO = false;}
      if(pHrqaGiJmw == true){pHrqaGiJmw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCPLHFLIND
{ 
  void uqYmwoRxdV()
  { 
      bool SGcZFNaZkz = false;
      bool uYcXmcTJbJ = false;
      bool drwaShYSGG = false;
      bool VSCdXYIEeJ = false;
      bool hwXHBtWlDO = false;
      bool awwdMZJBHW = false;
      bool oITedcWzAO = false;
      bool UOeSagUoZX = false;
      bool LlOrfYWXQx = false;
      bool PGxHTZbsdY = false;
      bool WWlotLRcCe = false;
      bool ETbjLCtbyE = false;
      bool FzhCyNRXyB = false;
      bool EbKBAnAYxU = false;
      bool HtVksueNuR = false;
      bool eAtYSXnipf = false;
      bool stdAZcIaiX = false;
      bool CUddxLcwJD = false;
      bool iEbgVEglhc = false;
      bool zRhRaMPULP = false;
      string yLZwwuBFZa;
      string fDFJRRAZxl;
      string sZluBdKwRJ;
      string ygrkLpcEAE;
      string KsxJFNgFzy;
      string zPMxOYZduS;
      string jEnQczKTxa;
      string owZrbAbbpm;
      string wEwTJiUtVm;
      string QyJhTFFfgG;
      string DMHXJCpTVO;
      string wxnHVeIUGt;
      string dPxKJpmqYV;
      string twujjixYKH;
      string sBYHpTKBMn;
      string xkZlbmPxNS;
      string PytATABEXl;
      string hiJzBcqpTp;
      string elejXJWIHw;
      string TAKqrtGYnp;
      if(yLZwwuBFZa == DMHXJCpTVO){SGcZFNaZkz = true;}
      else if(DMHXJCpTVO == yLZwwuBFZa){WWlotLRcCe = true;}
      if(fDFJRRAZxl == wxnHVeIUGt){uYcXmcTJbJ = true;}
      else if(wxnHVeIUGt == fDFJRRAZxl){ETbjLCtbyE = true;}
      if(sZluBdKwRJ == dPxKJpmqYV){drwaShYSGG = true;}
      else if(dPxKJpmqYV == sZluBdKwRJ){FzhCyNRXyB = true;}
      if(ygrkLpcEAE == twujjixYKH){VSCdXYIEeJ = true;}
      else if(twujjixYKH == ygrkLpcEAE){EbKBAnAYxU = true;}
      if(KsxJFNgFzy == sBYHpTKBMn){hwXHBtWlDO = true;}
      else if(sBYHpTKBMn == KsxJFNgFzy){HtVksueNuR = true;}
      if(zPMxOYZduS == xkZlbmPxNS){awwdMZJBHW = true;}
      else if(xkZlbmPxNS == zPMxOYZduS){eAtYSXnipf = true;}
      if(jEnQczKTxa == PytATABEXl){oITedcWzAO = true;}
      else if(PytATABEXl == jEnQczKTxa){stdAZcIaiX = true;}
      if(owZrbAbbpm == hiJzBcqpTp){UOeSagUoZX = true;}
      if(wEwTJiUtVm == elejXJWIHw){LlOrfYWXQx = true;}
      if(QyJhTFFfgG == TAKqrtGYnp){PGxHTZbsdY = true;}
      while(hiJzBcqpTp == owZrbAbbpm){CUddxLcwJD = true;}
      while(elejXJWIHw == elejXJWIHw){iEbgVEglhc = true;}
      while(TAKqrtGYnp == TAKqrtGYnp){zRhRaMPULP = true;}
      if(SGcZFNaZkz == true){SGcZFNaZkz = false;}
      if(uYcXmcTJbJ == true){uYcXmcTJbJ = false;}
      if(drwaShYSGG == true){drwaShYSGG = false;}
      if(VSCdXYIEeJ == true){VSCdXYIEeJ = false;}
      if(hwXHBtWlDO == true){hwXHBtWlDO = false;}
      if(awwdMZJBHW == true){awwdMZJBHW = false;}
      if(oITedcWzAO == true){oITedcWzAO = false;}
      if(UOeSagUoZX == true){UOeSagUoZX = false;}
      if(LlOrfYWXQx == true){LlOrfYWXQx = false;}
      if(PGxHTZbsdY == true){PGxHTZbsdY = false;}
      if(WWlotLRcCe == true){WWlotLRcCe = false;}
      if(ETbjLCtbyE == true){ETbjLCtbyE = false;}
      if(FzhCyNRXyB == true){FzhCyNRXyB = false;}
      if(EbKBAnAYxU == true){EbKBAnAYxU = false;}
      if(HtVksueNuR == true){HtVksueNuR = false;}
      if(eAtYSXnipf == true){eAtYSXnipf = false;}
      if(stdAZcIaiX == true){stdAZcIaiX = false;}
      if(CUddxLcwJD == true){CUddxLcwJD = false;}
      if(iEbgVEglhc == true){iEbgVEglhc = false;}
      if(zRhRaMPULP == true){zRhRaMPULP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRQHGTFKYX
{ 
  void QGGSXjPPOH()
  { 
      bool tJuKEATdRp = false;
      bool tUOMzAMnDK = false;
      bool OMJqiheZRZ = false;
      bool YLGIZjXRWR = false;
      bool jwtRJsLEMU = false;
      bool eOhHUgzEaW = false;
      bool VtLqQiOGlO = false;
      bool btQkaRSqhp = false;
      bool VZMxuJcynr = false;
      bool kTqAuojCAZ = false;
      bool eFRyrjxwfC = false;
      bool OIWkAuhOwH = false;
      bool FPRtdIDQpl = false;
      bool hPpHLQINEK = false;
      bool LgRldbwFzz = false;
      bool GUGsTOmWTj = false;
      bool ggGtTzROZj = false;
      bool mTKkuYxfQB = false;
      bool LxQpeMJxmw = false;
      bool dksUdeZXRd = false;
      string ZOzMtnfejh;
      string faFjRmHchI;
      string QOPSfcuSTp;
      string dOgpOnzOes;
      string DIileoRqyA;
      string XXrohKzfgQ;
      string rNKsERtPUc;
      string mrynEIfdnp;
      string KDTSSGVqHE;
      string oShNApyphN;
      string tCWVNeZDjZ;
      string eUrpGnsqZy;
      string uDHQnUKjnO;
      string KpwauIgyFn;
      string fSGhYTaqHM;
      string wGPiSqtGgs;
      string ToPVPoYRux;
      string HullRbwYqU;
      string sTcaSEZMID;
      string NZQMUqDkSi;
      if(ZOzMtnfejh == tCWVNeZDjZ){tJuKEATdRp = true;}
      else if(tCWVNeZDjZ == ZOzMtnfejh){eFRyrjxwfC = true;}
      if(faFjRmHchI == eUrpGnsqZy){tUOMzAMnDK = true;}
      else if(eUrpGnsqZy == faFjRmHchI){OIWkAuhOwH = true;}
      if(QOPSfcuSTp == uDHQnUKjnO){OMJqiheZRZ = true;}
      else if(uDHQnUKjnO == QOPSfcuSTp){FPRtdIDQpl = true;}
      if(dOgpOnzOes == KpwauIgyFn){YLGIZjXRWR = true;}
      else if(KpwauIgyFn == dOgpOnzOes){hPpHLQINEK = true;}
      if(DIileoRqyA == fSGhYTaqHM){jwtRJsLEMU = true;}
      else if(fSGhYTaqHM == DIileoRqyA){LgRldbwFzz = true;}
      if(XXrohKzfgQ == wGPiSqtGgs){eOhHUgzEaW = true;}
      else if(wGPiSqtGgs == XXrohKzfgQ){GUGsTOmWTj = true;}
      if(rNKsERtPUc == ToPVPoYRux){VtLqQiOGlO = true;}
      else if(ToPVPoYRux == rNKsERtPUc){ggGtTzROZj = true;}
      if(mrynEIfdnp == HullRbwYqU){btQkaRSqhp = true;}
      if(KDTSSGVqHE == sTcaSEZMID){VZMxuJcynr = true;}
      if(oShNApyphN == NZQMUqDkSi){kTqAuojCAZ = true;}
      while(HullRbwYqU == mrynEIfdnp){mTKkuYxfQB = true;}
      while(sTcaSEZMID == sTcaSEZMID){LxQpeMJxmw = true;}
      while(NZQMUqDkSi == NZQMUqDkSi){dksUdeZXRd = true;}
      if(tJuKEATdRp == true){tJuKEATdRp = false;}
      if(tUOMzAMnDK == true){tUOMzAMnDK = false;}
      if(OMJqiheZRZ == true){OMJqiheZRZ = false;}
      if(YLGIZjXRWR == true){YLGIZjXRWR = false;}
      if(jwtRJsLEMU == true){jwtRJsLEMU = false;}
      if(eOhHUgzEaW == true){eOhHUgzEaW = false;}
      if(VtLqQiOGlO == true){VtLqQiOGlO = false;}
      if(btQkaRSqhp == true){btQkaRSqhp = false;}
      if(VZMxuJcynr == true){VZMxuJcynr = false;}
      if(kTqAuojCAZ == true){kTqAuojCAZ = false;}
      if(eFRyrjxwfC == true){eFRyrjxwfC = false;}
      if(OIWkAuhOwH == true){OIWkAuhOwH = false;}
      if(FPRtdIDQpl == true){FPRtdIDQpl = false;}
      if(hPpHLQINEK == true){hPpHLQINEK = false;}
      if(LgRldbwFzz == true){LgRldbwFzz = false;}
      if(GUGsTOmWTj == true){GUGsTOmWTj = false;}
      if(ggGtTzROZj == true){ggGtTzROZj = false;}
      if(mTKkuYxfQB == true){mTKkuYxfQB = false;}
      if(LxQpeMJxmw == true){LxQpeMJxmw = false;}
      if(dksUdeZXRd == true){dksUdeZXRd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCUCNQBTGG
{ 
  void VCFFHySnzW()
  { 
      bool abtcYrAJAY = false;
      bool OuLtySZGtn = false;
      bool DHxbFFrYsY = false;
      bool StpPnPjjEU = false;
      bool MCkitAPGOp = false;
      bool upVofSdRWS = false;
      bool AbQaFUFuFi = false;
      bool ioBZbBVOhF = false;
      bool plKCdcYAjV = false;
      bool kRNlTkkKdZ = false;
      bool tTAeHGnwNe = false;
      bool wPjRbOROxb = false;
      bool uFLjxQbPFq = false;
      bool PLjHKWketX = false;
      bool nclFYVgwJE = false;
      bool SWMBeoHQgq = false;
      bool dYpWOkecGF = false;
      bool dlTZnSSFKb = false;
      bool ifFBXrzhcV = false;
      bool OTxDsOmOpn = false;
      string ebJaRzkGQu;
      string cfzGjhdUrc;
      string TuUWMaleun;
      string EcTPVDXPjj;
      string rozolUzraa;
      string WQapgiGmNp;
      string MFKbpzMijg;
      string KNkHkduejr;
      string btDURmBdil;
      string wkCsXldWym;
      string IPItQJeTFC;
      string naCVNSBpKD;
      string yhAxjZLriy;
      string AYgwiLkJEH;
      string IgXfyUhgeF;
      string kmMuoZPKJp;
      string ymjHBPtFlC;
      string grlCtQKTzP;
      string qeNdNNLlHJ;
      string waANJUxPdi;
      if(ebJaRzkGQu == IPItQJeTFC){abtcYrAJAY = true;}
      else if(IPItQJeTFC == ebJaRzkGQu){tTAeHGnwNe = true;}
      if(cfzGjhdUrc == naCVNSBpKD){OuLtySZGtn = true;}
      else if(naCVNSBpKD == cfzGjhdUrc){wPjRbOROxb = true;}
      if(TuUWMaleun == yhAxjZLriy){DHxbFFrYsY = true;}
      else if(yhAxjZLriy == TuUWMaleun){uFLjxQbPFq = true;}
      if(EcTPVDXPjj == AYgwiLkJEH){StpPnPjjEU = true;}
      else if(AYgwiLkJEH == EcTPVDXPjj){PLjHKWketX = true;}
      if(rozolUzraa == IgXfyUhgeF){MCkitAPGOp = true;}
      else if(IgXfyUhgeF == rozolUzraa){nclFYVgwJE = true;}
      if(WQapgiGmNp == kmMuoZPKJp){upVofSdRWS = true;}
      else if(kmMuoZPKJp == WQapgiGmNp){SWMBeoHQgq = true;}
      if(MFKbpzMijg == ymjHBPtFlC){AbQaFUFuFi = true;}
      else if(ymjHBPtFlC == MFKbpzMijg){dYpWOkecGF = true;}
      if(KNkHkduejr == grlCtQKTzP){ioBZbBVOhF = true;}
      if(btDURmBdil == qeNdNNLlHJ){plKCdcYAjV = true;}
      if(wkCsXldWym == waANJUxPdi){kRNlTkkKdZ = true;}
      while(grlCtQKTzP == KNkHkduejr){dlTZnSSFKb = true;}
      while(qeNdNNLlHJ == qeNdNNLlHJ){ifFBXrzhcV = true;}
      while(waANJUxPdi == waANJUxPdi){OTxDsOmOpn = true;}
      if(abtcYrAJAY == true){abtcYrAJAY = false;}
      if(OuLtySZGtn == true){OuLtySZGtn = false;}
      if(DHxbFFrYsY == true){DHxbFFrYsY = false;}
      if(StpPnPjjEU == true){StpPnPjjEU = false;}
      if(MCkitAPGOp == true){MCkitAPGOp = false;}
      if(upVofSdRWS == true){upVofSdRWS = false;}
      if(AbQaFUFuFi == true){AbQaFUFuFi = false;}
      if(ioBZbBVOhF == true){ioBZbBVOhF = false;}
      if(plKCdcYAjV == true){plKCdcYAjV = false;}
      if(kRNlTkkKdZ == true){kRNlTkkKdZ = false;}
      if(tTAeHGnwNe == true){tTAeHGnwNe = false;}
      if(wPjRbOROxb == true){wPjRbOROxb = false;}
      if(uFLjxQbPFq == true){uFLjxQbPFq = false;}
      if(PLjHKWketX == true){PLjHKWketX = false;}
      if(nclFYVgwJE == true){nclFYVgwJE = false;}
      if(SWMBeoHQgq == true){SWMBeoHQgq = false;}
      if(dYpWOkecGF == true){dYpWOkecGF = false;}
      if(dlTZnSSFKb == true){dlTZnSSFKb = false;}
      if(ifFBXrzhcV == true){ifFBXrzhcV = false;}
      if(OTxDsOmOpn == true){OTxDsOmOpn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LITJJZBYXV
{ 
  void SmGqlVWudV()
  { 
      bool RDMBNQfaMC = false;
      bool rHPaCVIHKn = false;
      bool XSoyFKukfj = false;
      bool AKiCJJgmHL = false;
      bool uXFdNZGJpd = false;
      bool ZHAHiyONwD = false;
      bool UtucBhYNQs = false;
      bool oVzyrANKje = false;
      bool EluBJrJaSK = false;
      bool tSqEqAbcbf = false;
      bool BrrxoEHCOi = false;
      bool kDcQyizsSJ = false;
      bool XxtGyVduHr = false;
      bool XjiEcLtxLF = false;
      bool jHMjZqoZFH = false;
      bool AiJSHDxlyS = false;
      bool ZMuWKAUYnm = false;
      bool oCgNYQkJfH = false;
      bool gEozrnZPxY = false;
      bool NHzseXMpZZ = false;
      string gmezZDDlFY;
      string MxxiWMZcBo;
      string cxWoUVPSoT;
      string NTPwpEhWAM;
      string AsnqRQaFzf;
      string dEhCjjPpeD;
      string mkwlKrgAsS;
      string dDbooiIfWE;
      string uJSJpJkMLF;
      string nrrxYOxCgY;
      string iaMgBabsNB;
      string bjSZIdRluA;
      string HUnmelLdQZ;
      string lFyxUUwlIP;
      string gryKdDYRou;
      string wKHfROlZBP;
      string PycmOVlUEn;
      string gfdfTPVdJa;
      string MsoUcaySfG;
      string hWjrAiOLuH;
      if(gmezZDDlFY == iaMgBabsNB){RDMBNQfaMC = true;}
      else if(iaMgBabsNB == gmezZDDlFY){BrrxoEHCOi = true;}
      if(MxxiWMZcBo == bjSZIdRluA){rHPaCVIHKn = true;}
      else if(bjSZIdRluA == MxxiWMZcBo){kDcQyizsSJ = true;}
      if(cxWoUVPSoT == HUnmelLdQZ){XSoyFKukfj = true;}
      else if(HUnmelLdQZ == cxWoUVPSoT){XxtGyVduHr = true;}
      if(NTPwpEhWAM == lFyxUUwlIP){AKiCJJgmHL = true;}
      else if(lFyxUUwlIP == NTPwpEhWAM){XjiEcLtxLF = true;}
      if(AsnqRQaFzf == gryKdDYRou){uXFdNZGJpd = true;}
      else if(gryKdDYRou == AsnqRQaFzf){jHMjZqoZFH = true;}
      if(dEhCjjPpeD == wKHfROlZBP){ZHAHiyONwD = true;}
      else if(wKHfROlZBP == dEhCjjPpeD){AiJSHDxlyS = true;}
      if(mkwlKrgAsS == PycmOVlUEn){UtucBhYNQs = true;}
      else if(PycmOVlUEn == mkwlKrgAsS){ZMuWKAUYnm = true;}
      if(dDbooiIfWE == gfdfTPVdJa){oVzyrANKje = true;}
      if(uJSJpJkMLF == MsoUcaySfG){EluBJrJaSK = true;}
      if(nrrxYOxCgY == hWjrAiOLuH){tSqEqAbcbf = true;}
      while(gfdfTPVdJa == dDbooiIfWE){oCgNYQkJfH = true;}
      while(MsoUcaySfG == MsoUcaySfG){gEozrnZPxY = true;}
      while(hWjrAiOLuH == hWjrAiOLuH){NHzseXMpZZ = true;}
      if(RDMBNQfaMC == true){RDMBNQfaMC = false;}
      if(rHPaCVIHKn == true){rHPaCVIHKn = false;}
      if(XSoyFKukfj == true){XSoyFKukfj = false;}
      if(AKiCJJgmHL == true){AKiCJJgmHL = false;}
      if(uXFdNZGJpd == true){uXFdNZGJpd = false;}
      if(ZHAHiyONwD == true){ZHAHiyONwD = false;}
      if(UtucBhYNQs == true){UtucBhYNQs = false;}
      if(oVzyrANKje == true){oVzyrANKje = false;}
      if(EluBJrJaSK == true){EluBJrJaSK = false;}
      if(tSqEqAbcbf == true){tSqEqAbcbf = false;}
      if(BrrxoEHCOi == true){BrrxoEHCOi = false;}
      if(kDcQyizsSJ == true){kDcQyizsSJ = false;}
      if(XxtGyVduHr == true){XxtGyVduHr = false;}
      if(XjiEcLtxLF == true){XjiEcLtxLF = false;}
      if(jHMjZqoZFH == true){jHMjZqoZFH = false;}
      if(AiJSHDxlyS == true){AiJSHDxlyS = false;}
      if(ZMuWKAUYnm == true){ZMuWKAUYnm = false;}
      if(oCgNYQkJfH == true){oCgNYQkJfH = false;}
      if(gEozrnZPxY == true){gEozrnZPxY = false;}
      if(NHzseXMpZZ == true){NHzseXMpZZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBQNFWBFMJ
{ 
  void yKIMMobwVF()
  { 
      bool LfXyhecYjj = false;
      bool HYuzLpONCI = false;
      bool RUTIlfirwL = false;
      bool OVxLPQaXIT = false;
      bool BaWPkXnbtL = false;
      bool cfOXZpMOMB = false;
      bool ujcYVkbiiu = false;
      bool PpFhGpyEXO = false;
      bool rHyjhhHYkZ = false;
      bool DMLGXRyytz = false;
      bool wErzwmafRi = false;
      bool rIpyJnkrqm = false;
      bool dCyIqCeyJn = false;
      bool rzJYSmOynu = false;
      bool HaHCguVMxj = false;
      bool fGHGUsGjIs = false;
      bool HcVcqryReW = false;
      bool YmEwfCuuau = false;
      bool gRBZHlrDDY = false;
      bool feptneFdKo = false;
      string gUHXnRSUBZ;
      string UHKwdmTPax;
      string RBgxzHXNmD;
      string aVrBgAZjwp;
      string GWMRBOIcUS;
      string xJdhnemKXf;
      string tFhxyzPJPc;
      string MjTkqunOuk;
      string yusTGRqJMB;
      string MPLPwBoPTB;
      string zzMqFNorqs;
      string qXOmhyLNqf;
      string HFxNQxXEno;
      string GYutlzhBOr;
      string cySTKnAYhx;
      string obXmssCyaI;
      string pkEBmScUBi;
      string PKzyDIldDb;
      string wzWpzeAHAr;
      string wjaGCrtQfr;
      if(gUHXnRSUBZ == zzMqFNorqs){LfXyhecYjj = true;}
      else if(zzMqFNorqs == gUHXnRSUBZ){wErzwmafRi = true;}
      if(UHKwdmTPax == qXOmhyLNqf){HYuzLpONCI = true;}
      else if(qXOmhyLNqf == UHKwdmTPax){rIpyJnkrqm = true;}
      if(RBgxzHXNmD == HFxNQxXEno){RUTIlfirwL = true;}
      else if(HFxNQxXEno == RBgxzHXNmD){dCyIqCeyJn = true;}
      if(aVrBgAZjwp == GYutlzhBOr){OVxLPQaXIT = true;}
      else if(GYutlzhBOr == aVrBgAZjwp){rzJYSmOynu = true;}
      if(GWMRBOIcUS == cySTKnAYhx){BaWPkXnbtL = true;}
      else if(cySTKnAYhx == GWMRBOIcUS){HaHCguVMxj = true;}
      if(xJdhnemKXf == obXmssCyaI){cfOXZpMOMB = true;}
      else if(obXmssCyaI == xJdhnemKXf){fGHGUsGjIs = true;}
      if(tFhxyzPJPc == pkEBmScUBi){ujcYVkbiiu = true;}
      else if(pkEBmScUBi == tFhxyzPJPc){HcVcqryReW = true;}
      if(MjTkqunOuk == PKzyDIldDb){PpFhGpyEXO = true;}
      if(yusTGRqJMB == wzWpzeAHAr){rHyjhhHYkZ = true;}
      if(MPLPwBoPTB == wjaGCrtQfr){DMLGXRyytz = true;}
      while(PKzyDIldDb == MjTkqunOuk){YmEwfCuuau = true;}
      while(wzWpzeAHAr == wzWpzeAHAr){gRBZHlrDDY = true;}
      while(wjaGCrtQfr == wjaGCrtQfr){feptneFdKo = true;}
      if(LfXyhecYjj == true){LfXyhecYjj = false;}
      if(HYuzLpONCI == true){HYuzLpONCI = false;}
      if(RUTIlfirwL == true){RUTIlfirwL = false;}
      if(OVxLPQaXIT == true){OVxLPQaXIT = false;}
      if(BaWPkXnbtL == true){BaWPkXnbtL = false;}
      if(cfOXZpMOMB == true){cfOXZpMOMB = false;}
      if(ujcYVkbiiu == true){ujcYVkbiiu = false;}
      if(PpFhGpyEXO == true){PpFhGpyEXO = false;}
      if(rHyjhhHYkZ == true){rHyjhhHYkZ = false;}
      if(DMLGXRyytz == true){DMLGXRyytz = false;}
      if(wErzwmafRi == true){wErzwmafRi = false;}
      if(rIpyJnkrqm == true){rIpyJnkrqm = false;}
      if(dCyIqCeyJn == true){dCyIqCeyJn = false;}
      if(rzJYSmOynu == true){rzJYSmOynu = false;}
      if(HaHCguVMxj == true){HaHCguVMxj = false;}
      if(fGHGUsGjIs == true){fGHGUsGjIs = false;}
      if(HcVcqryReW == true){HcVcqryReW = false;}
      if(YmEwfCuuau == true){YmEwfCuuau = false;}
      if(gRBZHlrDDY == true){gRBZHlrDDY = false;}
      if(feptneFdKo == true){feptneFdKo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTVFVCYSEL
{ 
  void ltwzOnePMG()
  { 
      bool ypgARJeMzp = false;
      bool fzDByeEQDd = false;
      bool deXVdeJuWb = false;
      bool HfHZJIgQWa = false;
      bool FKVcGJdNTn = false;
      bool WwbWLTSKWm = false;
      bool AipWhzrcqo = false;
      bool xmscXTJuPT = false;
      bool BubhFKEjOo = false;
      bool pVtiZWUyuH = false;
      bool RAVepjCzzq = false;
      bool KWuClEHHRW = false;
      bool uHOByasKCB = false;
      bool yKzICAZxqV = false;
      bool IEkWeSaqxU = false;
      bool PNgXMJlTfO = false;
      bool prxyrAXmAl = false;
      bool eJPuOpWqWf = false;
      bool ACMgkkcbur = false;
      bool OGRbeQHmee = false;
      string dKFiTWXjNX;
      string LufNDmDxtP;
      string tOIHqOglLt;
      string yejykYBUyh;
      string QtceelOEwQ;
      string gYlGqPBxrF;
      string plYSZgLgce;
      string khyLyzkcbF;
      string AbpuNYscHV;
      string WDcsreVJEy;
      string ZhaQezaZIq;
      string dYUmFNwcFB;
      string nhYHHhEFTS;
      string cbXdeRBYPO;
      string xSUPqyhpme;
      string hrEDKrITJx;
      string tVFoOBAqIm;
      string MXNqDUMIPI;
      string zORokjXUSl;
      string JgORTbMfBo;
      if(dKFiTWXjNX == ZhaQezaZIq){ypgARJeMzp = true;}
      else if(ZhaQezaZIq == dKFiTWXjNX){RAVepjCzzq = true;}
      if(LufNDmDxtP == dYUmFNwcFB){fzDByeEQDd = true;}
      else if(dYUmFNwcFB == LufNDmDxtP){KWuClEHHRW = true;}
      if(tOIHqOglLt == nhYHHhEFTS){deXVdeJuWb = true;}
      else if(nhYHHhEFTS == tOIHqOglLt){uHOByasKCB = true;}
      if(yejykYBUyh == cbXdeRBYPO){HfHZJIgQWa = true;}
      else if(cbXdeRBYPO == yejykYBUyh){yKzICAZxqV = true;}
      if(QtceelOEwQ == xSUPqyhpme){FKVcGJdNTn = true;}
      else if(xSUPqyhpme == QtceelOEwQ){IEkWeSaqxU = true;}
      if(gYlGqPBxrF == hrEDKrITJx){WwbWLTSKWm = true;}
      else if(hrEDKrITJx == gYlGqPBxrF){PNgXMJlTfO = true;}
      if(plYSZgLgce == tVFoOBAqIm){AipWhzrcqo = true;}
      else if(tVFoOBAqIm == plYSZgLgce){prxyrAXmAl = true;}
      if(khyLyzkcbF == MXNqDUMIPI){xmscXTJuPT = true;}
      if(AbpuNYscHV == zORokjXUSl){BubhFKEjOo = true;}
      if(WDcsreVJEy == JgORTbMfBo){pVtiZWUyuH = true;}
      while(MXNqDUMIPI == khyLyzkcbF){eJPuOpWqWf = true;}
      while(zORokjXUSl == zORokjXUSl){ACMgkkcbur = true;}
      while(JgORTbMfBo == JgORTbMfBo){OGRbeQHmee = true;}
      if(ypgARJeMzp == true){ypgARJeMzp = false;}
      if(fzDByeEQDd == true){fzDByeEQDd = false;}
      if(deXVdeJuWb == true){deXVdeJuWb = false;}
      if(HfHZJIgQWa == true){HfHZJIgQWa = false;}
      if(FKVcGJdNTn == true){FKVcGJdNTn = false;}
      if(WwbWLTSKWm == true){WwbWLTSKWm = false;}
      if(AipWhzrcqo == true){AipWhzrcqo = false;}
      if(xmscXTJuPT == true){xmscXTJuPT = false;}
      if(BubhFKEjOo == true){BubhFKEjOo = false;}
      if(pVtiZWUyuH == true){pVtiZWUyuH = false;}
      if(RAVepjCzzq == true){RAVepjCzzq = false;}
      if(KWuClEHHRW == true){KWuClEHHRW = false;}
      if(uHOByasKCB == true){uHOByasKCB = false;}
      if(yKzICAZxqV == true){yKzICAZxqV = false;}
      if(IEkWeSaqxU == true){IEkWeSaqxU = false;}
      if(PNgXMJlTfO == true){PNgXMJlTfO = false;}
      if(prxyrAXmAl == true){prxyrAXmAl = false;}
      if(eJPuOpWqWf == true){eJPuOpWqWf = false;}
      if(ACMgkkcbur == true){ACMgkkcbur = false;}
      if(OGRbeQHmee == true){OGRbeQHmee = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMRILUKTVD
{ 
  void fQNVmSIeOL()
  { 
      bool UbMNnatRoR = false;
      bool sAiGcnIQbC = false;
      bool zLxFJwKQtM = false;
      bool pGBfFEhejW = false;
      bool eEfeypIIgb = false;
      bool HcnWFJeGDr = false;
      bool QcXbblzCBY = false;
      bool GcfEXteSHT = false;
      bool mBiSFMSdau = false;
      bool ZabrGBgDDL = false;
      bool qFHIUdxizK = false;
      bool dMzjEOsEWO = false;
      bool TUbFzeBnyV = false;
      bool NbOubgtaxb = false;
      bool PjePRMbrmq = false;
      bool IbgorVcBIp = false;
      bool bJkcxCxDIW = false;
      bool URHuyjpMnl = false;
      bool DJAGNktZDF = false;
      bool ErSHzGyBRP = false;
      string rEmlPqrrHw;
      string itNZnrhKFa;
      string PfjbsasNNF;
      string ZrPMLpZJVa;
      string CzqjKHFxHe;
      string OyTzmMTKrn;
      string xdeCWpdBNy;
      string RXodYPoARl;
      string VwGhqbXQYz;
      string VORgcYTnNT;
      string cDiJMpJpZW;
      string WTrGSBWxLu;
      string RNcNbCGHAz;
      string uAmyIRMxUA;
      string RhpBbBWKOb;
      string BWcRBPaUgJ;
      string jBoabWgtyA;
      string nZbKcjWalZ;
      string fusYyYWUwr;
      string prPKQPsPZF;
      if(rEmlPqrrHw == cDiJMpJpZW){UbMNnatRoR = true;}
      else if(cDiJMpJpZW == rEmlPqrrHw){qFHIUdxizK = true;}
      if(itNZnrhKFa == WTrGSBWxLu){sAiGcnIQbC = true;}
      else if(WTrGSBWxLu == itNZnrhKFa){dMzjEOsEWO = true;}
      if(PfjbsasNNF == RNcNbCGHAz){zLxFJwKQtM = true;}
      else if(RNcNbCGHAz == PfjbsasNNF){TUbFzeBnyV = true;}
      if(ZrPMLpZJVa == uAmyIRMxUA){pGBfFEhejW = true;}
      else if(uAmyIRMxUA == ZrPMLpZJVa){NbOubgtaxb = true;}
      if(CzqjKHFxHe == RhpBbBWKOb){eEfeypIIgb = true;}
      else if(RhpBbBWKOb == CzqjKHFxHe){PjePRMbrmq = true;}
      if(OyTzmMTKrn == BWcRBPaUgJ){HcnWFJeGDr = true;}
      else if(BWcRBPaUgJ == OyTzmMTKrn){IbgorVcBIp = true;}
      if(xdeCWpdBNy == jBoabWgtyA){QcXbblzCBY = true;}
      else if(jBoabWgtyA == xdeCWpdBNy){bJkcxCxDIW = true;}
      if(RXodYPoARl == nZbKcjWalZ){GcfEXteSHT = true;}
      if(VwGhqbXQYz == fusYyYWUwr){mBiSFMSdau = true;}
      if(VORgcYTnNT == prPKQPsPZF){ZabrGBgDDL = true;}
      while(nZbKcjWalZ == RXodYPoARl){URHuyjpMnl = true;}
      while(fusYyYWUwr == fusYyYWUwr){DJAGNktZDF = true;}
      while(prPKQPsPZF == prPKQPsPZF){ErSHzGyBRP = true;}
      if(UbMNnatRoR == true){UbMNnatRoR = false;}
      if(sAiGcnIQbC == true){sAiGcnIQbC = false;}
      if(zLxFJwKQtM == true){zLxFJwKQtM = false;}
      if(pGBfFEhejW == true){pGBfFEhejW = false;}
      if(eEfeypIIgb == true){eEfeypIIgb = false;}
      if(HcnWFJeGDr == true){HcnWFJeGDr = false;}
      if(QcXbblzCBY == true){QcXbblzCBY = false;}
      if(GcfEXteSHT == true){GcfEXteSHT = false;}
      if(mBiSFMSdau == true){mBiSFMSdau = false;}
      if(ZabrGBgDDL == true){ZabrGBgDDL = false;}
      if(qFHIUdxizK == true){qFHIUdxizK = false;}
      if(dMzjEOsEWO == true){dMzjEOsEWO = false;}
      if(TUbFzeBnyV == true){TUbFzeBnyV = false;}
      if(NbOubgtaxb == true){NbOubgtaxb = false;}
      if(PjePRMbrmq == true){PjePRMbrmq = false;}
      if(IbgorVcBIp == true){IbgorVcBIp = false;}
      if(bJkcxCxDIW == true){bJkcxCxDIW = false;}
      if(URHuyjpMnl == true){URHuyjpMnl = false;}
      if(DJAGNktZDF == true){DJAGNktZDF = false;}
      if(ErSHzGyBRP == true){ErSHzGyBRP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDMKHYLZSN
{ 
  void hOTYMDodVi()
  { 
      bool UGcTumImLX = false;
      bool feFKPMgRDj = false;
      bool iroJeIttuf = false;
      bool SsHApoPxKd = false;
      bool nizfqEPWoS = false;
      bool xkOrWbRTol = false;
      bool rOqeEmXFUZ = false;
      bool xjHYuzsIRa = false;
      bool sWEcigdPdN = false;
      bool XwHXkZqTaD = false;
      bool fKCOUNdpwW = false;
      bool iIBOsVJOuW = false;
      bool IIbGCBbinV = false;
      bool IYhNthUpHV = false;
      bool DnSGePtseP = false;
      bool QcYDuXiuMT = false;
      bool ktBaOJZmUK = false;
      bool BTGZTUpUbm = false;
      bool GhEXEeAdSV = false;
      bool zYcnjIlqrU = false;
      string ahBkWOrLMg;
      string VwyGUVWNOH;
      string pfJOgCwEWK;
      string UtLKrefLQA;
      string hMZUVauouy;
      string SuPYPtXlDU;
      string RnoCMbjmNp;
      string pKwNYcGosG;
      string GHIYrZdluy;
      string GsHwitXXIs;
      string pHaFHHyCzl;
      string misxNJePKl;
      string yyrPiwCAee;
      string FifzPyfDQj;
      string balIKXAKiY;
      string OHMVurOKVL;
      string ExXTgECsgO;
      string dbzZKWLiFL;
      string wrQFQxVKEX;
      string jUhEedDRbF;
      if(ahBkWOrLMg == pHaFHHyCzl){UGcTumImLX = true;}
      else if(pHaFHHyCzl == ahBkWOrLMg){fKCOUNdpwW = true;}
      if(VwyGUVWNOH == misxNJePKl){feFKPMgRDj = true;}
      else if(misxNJePKl == VwyGUVWNOH){iIBOsVJOuW = true;}
      if(pfJOgCwEWK == yyrPiwCAee){iroJeIttuf = true;}
      else if(yyrPiwCAee == pfJOgCwEWK){IIbGCBbinV = true;}
      if(UtLKrefLQA == FifzPyfDQj){SsHApoPxKd = true;}
      else if(FifzPyfDQj == UtLKrefLQA){IYhNthUpHV = true;}
      if(hMZUVauouy == balIKXAKiY){nizfqEPWoS = true;}
      else if(balIKXAKiY == hMZUVauouy){DnSGePtseP = true;}
      if(SuPYPtXlDU == OHMVurOKVL){xkOrWbRTol = true;}
      else if(OHMVurOKVL == SuPYPtXlDU){QcYDuXiuMT = true;}
      if(RnoCMbjmNp == ExXTgECsgO){rOqeEmXFUZ = true;}
      else if(ExXTgECsgO == RnoCMbjmNp){ktBaOJZmUK = true;}
      if(pKwNYcGosG == dbzZKWLiFL){xjHYuzsIRa = true;}
      if(GHIYrZdluy == wrQFQxVKEX){sWEcigdPdN = true;}
      if(GsHwitXXIs == jUhEedDRbF){XwHXkZqTaD = true;}
      while(dbzZKWLiFL == pKwNYcGosG){BTGZTUpUbm = true;}
      while(wrQFQxVKEX == wrQFQxVKEX){GhEXEeAdSV = true;}
      while(jUhEedDRbF == jUhEedDRbF){zYcnjIlqrU = true;}
      if(UGcTumImLX == true){UGcTumImLX = false;}
      if(feFKPMgRDj == true){feFKPMgRDj = false;}
      if(iroJeIttuf == true){iroJeIttuf = false;}
      if(SsHApoPxKd == true){SsHApoPxKd = false;}
      if(nizfqEPWoS == true){nizfqEPWoS = false;}
      if(xkOrWbRTol == true){xkOrWbRTol = false;}
      if(rOqeEmXFUZ == true){rOqeEmXFUZ = false;}
      if(xjHYuzsIRa == true){xjHYuzsIRa = false;}
      if(sWEcigdPdN == true){sWEcigdPdN = false;}
      if(XwHXkZqTaD == true){XwHXkZqTaD = false;}
      if(fKCOUNdpwW == true){fKCOUNdpwW = false;}
      if(iIBOsVJOuW == true){iIBOsVJOuW = false;}
      if(IIbGCBbinV == true){IIbGCBbinV = false;}
      if(IYhNthUpHV == true){IYhNthUpHV = false;}
      if(DnSGePtseP == true){DnSGePtseP = false;}
      if(QcYDuXiuMT == true){QcYDuXiuMT = false;}
      if(ktBaOJZmUK == true){ktBaOJZmUK = false;}
      if(BTGZTUpUbm == true){BTGZTUpUbm = false;}
      if(GhEXEeAdSV == true){GhEXEeAdSV = false;}
      if(zYcnjIlqrU == true){zYcnjIlqrU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKOPGEIGDE
{ 
  void UIHJiSmpPU()
  { 
      bool JmeQYJSXjR = false;
      bool GErQGBbfpK = false;
      bool zVwrTaLIRB = false;
      bool llEbzNRysD = false;
      bool qLnAHIcYSD = false;
      bool oMxqKmpmxy = false;
      bool yJGhfTAQQs = false;
      bool jdllSmhujK = false;
      bool xlpOLZoMQM = false;
      bool WeAuFgFFUn = false;
      bool IMHZSLZKYW = false;
      bool EuCmALTrVF = false;
      bool emzDVFcqgk = false;
      bool hbauCkdPuA = false;
      bool zdmtHbbNus = false;
      bool NNiOJUNDDN = false;
      bool hidnocTGkP = false;
      bool gDwVGAzEwt = false;
      bool dPumXTrMlg = false;
      bool WZMhRQAzFe = false;
      string GERjBVohFa;
      string gpwVmVImkq;
      string xmcFliNXcq;
      string jdzOdBpkVb;
      string qUjVWpWCXn;
      string FVxcJSbLxR;
      string IQENpCphqk;
      string fWQJzcCGiu;
      string MKAolNfWEK;
      string YdnDTaQWeT;
      string AnKlIhEndg;
      string PVcBFxPOab;
      string WTdgMBiNoY;
      string LfaOuXAOfE;
      string IqsWtDAlyW;
      string KBuDxgKdZG;
      string yqzEUjtNGg;
      string xAhWSeaGlI;
      string AxPSNKjXRO;
      string NVoZFRrnCK;
      if(GERjBVohFa == AnKlIhEndg){JmeQYJSXjR = true;}
      else if(AnKlIhEndg == GERjBVohFa){IMHZSLZKYW = true;}
      if(gpwVmVImkq == PVcBFxPOab){GErQGBbfpK = true;}
      else if(PVcBFxPOab == gpwVmVImkq){EuCmALTrVF = true;}
      if(xmcFliNXcq == WTdgMBiNoY){zVwrTaLIRB = true;}
      else if(WTdgMBiNoY == xmcFliNXcq){emzDVFcqgk = true;}
      if(jdzOdBpkVb == LfaOuXAOfE){llEbzNRysD = true;}
      else if(LfaOuXAOfE == jdzOdBpkVb){hbauCkdPuA = true;}
      if(qUjVWpWCXn == IqsWtDAlyW){qLnAHIcYSD = true;}
      else if(IqsWtDAlyW == qUjVWpWCXn){zdmtHbbNus = true;}
      if(FVxcJSbLxR == KBuDxgKdZG){oMxqKmpmxy = true;}
      else if(KBuDxgKdZG == FVxcJSbLxR){NNiOJUNDDN = true;}
      if(IQENpCphqk == yqzEUjtNGg){yJGhfTAQQs = true;}
      else if(yqzEUjtNGg == IQENpCphqk){hidnocTGkP = true;}
      if(fWQJzcCGiu == xAhWSeaGlI){jdllSmhujK = true;}
      if(MKAolNfWEK == AxPSNKjXRO){xlpOLZoMQM = true;}
      if(YdnDTaQWeT == NVoZFRrnCK){WeAuFgFFUn = true;}
      while(xAhWSeaGlI == fWQJzcCGiu){gDwVGAzEwt = true;}
      while(AxPSNKjXRO == AxPSNKjXRO){dPumXTrMlg = true;}
      while(NVoZFRrnCK == NVoZFRrnCK){WZMhRQAzFe = true;}
      if(JmeQYJSXjR == true){JmeQYJSXjR = false;}
      if(GErQGBbfpK == true){GErQGBbfpK = false;}
      if(zVwrTaLIRB == true){zVwrTaLIRB = false;}
      if(llEbzNRysD == true){llEbzNRysD = false;}
      if(qLnAHIcYSD == true){qLnAHIcYSD = false;}
      if(oMxqKmpmxy == true){oMxqKmpmxy = false;}
      if(yJGhfTAQQs == true){yJGhfTAQQs = false;}
      if(jdllSmhujK == true){jdllSmhujK = false;}
      if(xlpOLZoMQM == true){xlpOLZoMQM = false;}
      if(WeAuFgFFUn == true){WeAuFgFFUn = false;}
      if(IMHZSLZKYW == true){IMHZSLZKYW = false;}
      if(EuCmALTrVF == true){EuCmALTrVF = false;}
      if(emzDVFcqgk == true){emzDVFcqgk = false;}
      if(hbauCkdPuA == true){hbauCkdPuA = false;}
      if(zdmtHbbNus == true){zdmtHbbNus = false;}
      if(NNiOJUNDDN == true){NNiOJUNDDN = false;}
      if(hidnocTGkP == true){hidnocTGkP = false;}
      if(gDwVGAzEwt == true){gDwVGAzEwt = false;}
      if(dPumXTrMlg == true){dPumXTrMlg = false;}
      if(WZMhRQAzFe == true){WZMhRQAzFe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPQHFZJOWH
{ 
  void dbFcEaGgoG()
  { 
      bool puuwIpKzGc = false;
      bool PharSUCwYW = false;
      bool kQbdfmgiNx = false;
      bool UxuNdtkjLs = false;
      bool ZOyfCwQqrp = false;
      bool BooXCZSRPU = false;
      bool JbkIISlNOX = false;
      bool jSkfxWRuai = false;
      bool WpqXweIXKE = false;
      bool aTUpiycoWj = false;
      bool KCbTGiDIae = false;
      bool HXpfxSjNMc = false;
      bool KOCJxPyuwz = false;
      bool tcXqYUNWQN = false;
      bool azwewDdnrQ = false;
      bool NPctZwzSWp = false;
      bool kIMakezyGc = false;
      bool FNwzBKRWNs = false;
      bool lJCfleAdRc = false;
      bool UuAabSmVtR = false;
      string LFdLduMTBo;
      string XkGOVJrVPf;
      string oeIMQpLLHb;
      string qpgKDrcgLV;
      string UeiwZMQaVK;
      string mgQKIfwQun;
      string iBLZyhEwLc;
      string gLKsKJuLlD;
      string YjoxnJYWBW;
      string wLkWlTTJyr;
      string IUPsdbWWAy;
      string kjerPzMNko;
      string IhunfVZmGq;
      string plNstETuTM;
      string mBWDlMfsHm;
      string HFXIjaYbMI;
      string BiPIHyVkxL;
      string eQtYBGKqBT;
      string ogfTjjNFJS;
      string eqiLKElNum;
      if(LFdLduMTBo == IUPsdbWWAy){puuwIpKzGc = true;}
      else if(IUPsdbWWAy == LFdLduMTBo){KCbTGiDIae = true;}
      if(XkGOVJrVPf == kjerPzMNko){PharSUCwYW = true;}
      else if(kjerPzMNko == XkGOVJrVPf){HXpfxSjNMc = true;}
      if(oeIMQpLLHb == IhunfVZmGq){kQbdfmgiNx = true;}
      else if(IhunfVZmGq == oeIMQpLLHb){KOCJxPyuwz = true;}
      if(qpgKDrcgLV == plNstETuTM){UxuNdtkjLs = true;}
      else if(plNstETuTM == qpgKDrcgLV){tcXqYUNWQN = true;}
      if(UeiwZMQaVK == mBWDlMfsHm){ZOyfCwQqrp = true;}
      else if(mBWDlMfsHm == UeiwZMQaVK){azwewDdnrQ = true;}
      if(mgQKIfwQun == HFXIjaYbMI){BooXCZSRPU = true;}
      else if(HFXIjaYbMI == mgQKIfwQun){NPctZwzSWp = true;}
      if(iBLZyhEwLc == BiPIHyVkxL){JbkIISlNOX = true;}
      else if(BiPIHyVkxL == iBLZyhEwLc){kIMakezyGc = true;}
      if(gLKsKJuLlD == eQtYBGKqBT){jSkfxWRuai = true;}
      if(YjoxnJYWBW == ogfTjjNFJS){WpqXweIXKE = true;}
      if(wLkWlTTJyr == eqiLKElNum){aTUpiycoWj = true;}
      while(eQtYBGKqBT == gLKsKJuLlD){FNwzBKRWNs = true;}
      while(ogfTjjNFJS == ogfTjjNFJS){lJCfleAdRc = true;}
      while(eqiLKElNum == eqiLKElNum){UuAabSmVtR = true;}
      if(puuwIpKzGc == true){puuwIpKzGc = false;}
      if(PharSUCwYW == true){PharSUCwYW = false;}
      if(kQbdfmgiNx == true){kQbdfmgiNx = false;}
      if(UxuNdtkjLs == true){UxuNdtkjLs = false;}
      if(ZOyfCwQqrp == true){ZOyfCwQqrp = false;}
      if(BooXCZSRPU == true){BooXCZSRPU = false;}
      if(JbkIISlNOX == true){JbkIISlNOX = false;}
      if(jSkfxWRuai == true){jSkfxWRuai = false;}
      if(WpqXweIXKE == true){WpqXweIXKE = false;}
      if(aTUpiycoWj == true){aTUpiycoWj = false;}
      if(KCbTGiDIae == true){KCbTGiDIae = false;}
      if(HXpfxSjNMc == true){HXpfxSjNMc = false;}
      if(KOCJxPyuwz == true){KOCJxPyuwz = false;}
      if(tcXqYUNWQN == true){tcXqYUNWQN = false;}
      if(azwewDdnrQ == true){azwewDdnrQ = false;}
      if(NPctZwzSWp == true){NPctZwzSWp = false;}
      if(kIMakezyGc == true){kIMakezyGc = false;}
      if(FNwzBKRWNs == true){FNwzBKRWNs = false;}
      if(lJCfleAdRc == true){lJCfleAdRc = false;}
      if(UuAabSmVtR == true){UuAabSmVtR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQBCUTSVZS
{ 
  void ooHPsCgpDh()
  { 
      bool GmEqFSqLnZ = false;
      bool mWWnUhkHtK = false;
      bool DuKSxmVxzb = false;
      bool BkqfYBldFP = false;
      bool CUagNqODxL = false;
      bool JRCxhLcktR = false;
      bool wtLLYCfpPS = false;
      bool uHCdHiUcEG = false;
      bool YSznRiisyN = false;
      bool YAimSIIOIL = false;
      bool KXnePCOXoy = false;
      bool pzfmrdtXso = false;
      bool SlqBtuXOKz = false;
      bool aFUsuBdUXP = false;
      bool ULDAWYTuuo = false;
      bool NkUTrXflkU = false;
      bool dAMoXjemrq = false;
      bool zZAcUHiqeU = false;
      bool abSVlpkBAW = false;
      bool UrjDkTyNcl = false;
      string AlLiyNufrl;
      string rHDnlCkkzl;
      string VfuLuhKqIa;
      string hZjXJpdEOg;
      string NVfmkyOGMc;
      string UBZRFTqznP;
      string DEXQESXedw;
      string YgWSYzzHaw;
      string TDdfGfzRSp;
      string zdQydIyPiS;
      string aicQEneHsF;
      string TiYquzaqKX;
      string SFMnwtPXoP;
      string BjYHVjaMbR;
      string BrYMVQFZCd;
      string gGEKAUWoUJ;
      string XGScEjJRUL;
      string YOPsWagzRf;
      string opUKitfOGB;
      string NkrRstYwIk;
      if(AlLiyNufrl == aicQEneHsF){GmEqFSqLnZ = true;}
      else if(aicQEneHsF == AlLiyNufrl){KXnePCOXoy = true;}
      if(rHDnlCkkzl == TiYquzaqKX){mWWnUhkHtK = true;}
      else if(TiYquzaqKX == rHDnlCkkzl){pzfmrdtXso = true;}
      if(VfuLuhKqIa == SFMnwtPXoP){DuKSxmVxzb = true;}
      else if(SFMnwtPXoP == VfuLuhKqIa){SlqBtuXOKz = true;}
      if(hZjXJpdEOg == BjYHVjaMbR){BkqfYBldFP = true;}
      else if(BjYHVjaMbR == hZjXJpdEOg){aFUsuBdUXP = true;}
      if(NVfmkyOGMc == BrYMVQFZCd){CUagNqODxL = true;}
      else if(BrYMVQFZCd == NVfmkyOGMc){ULDAWYTuuo = true;}
      if(UBZRFTqznP == gGEKAUWoUJ){JRCxhLcktR = true;}
      else if(gGEKAUWoUJ == UBZRFTqznP){NkUTrXflkU = true;}
      if(DEXQESXedw == XGScEjJRUL){wtLLYCfpPS = true;}
      else if(XGScEjJRUL == DEXQESXedw){dAMoXjemrq = true;}
      if(YgWSYzzHaw == YOPsWagzRf){uHCdHiUcEG = true;}
      if(TDdfGfzRSp == opUKitfOGB){YSznRiisyN = true;}
      if(zdQydIyPiS == NkrRstYwIk){YAimSIIOIL = true;}
      while(YOPsWagzRf == YgWSYzzHaw){zZAcUHiqeU = true;}
      while(opUKitfOGB == opUKitfOGB){abSVlpkBAW = true;}
      while(NkrRstYwIk == NkrRstYwIk){UrjDkTyNcl = true;}
      if(GmEqFSqLnZ == true){GmEqFSqLnZ = false;}
      if(mWWnUhkHtK == true){mWWnUhkHtK = false;}
      if(DuKSxmVxzb == true){DuKSxmVxzb = false;}
      if(BkqfYBldFP == true){BkqfYBldFP = false;}
      if(CUagNqODxL == true){CUagNqODxL = false;}
      if(JRCxhLcktR == true){JRCxhLcktR = false;}
      if(wtLLYCfpPS == true){wtLLYCfpPS = false;}
      if(uHCdHiUcEG == true){uHCdHiUcEG = false;}
      if(YSznRiisyN == true){YSznRiisyN = false;}
      if(YAimSIIOIL == true){YAimSIIOIL = false;}
      if(KXnePCOXoy == true){KXnePCOXoy = false;}
      if(pzfmrdtXso == true){pzfmrdtXso = false;}
      if(SlqBtuXOKz == true){SlqBtuXOKz = false;}
      if(aFUsuBdUXP == true){aFUsuBdUXP = false;}
      if(ULDAWYTuuo == true){ULDAWYTuuo = false;}
      if(NkUTrXflkU == true){NkUTrXflkU = false;}
      if(dAMoXjemrq == true){dAMoXjemrq = false;}
      if(zZAcUHiqeU == true){zZAcUHiqeU = false;}
      if(abSVlpkBAW == true){abSVlpkBAW = false;}
      if(UrjDkTyNcl == true){UrjDkTyNcl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAJWHWZBLG
{ 
  void KeKYSHUSUx()
  { 
      bool hckIQpBdgi = false;
      bool zpNCUTIyzA = false;
      bool dCRNNBctSY = false;
      bool iLSAcIFZGE = false;
      bool eEIEPIWbPj = false;
      bool JHroTeLXuP = false;
      bool NHLHzmWNZL = false;
      bool NiqtUZtMxE = false;
      bool eAdhPbTdfx = false;
      bool xheqqXsAEc = false;
      bool kICDWaPxTt = false;
      bool kyapjNccrW = false;
      bool SrgbOfDADx = false;
      bool fsITTVyZLn = false;
      bool MWKkMyHnGc = false;
      bool uPIgJraZoq = false;
      bool WPsWNrpGVO = false;
      bool OCREKwhwPP = false;
      bool XOtZBQkaKa = false;
      bool tXkTRxcnXU = false;
      string BCpefJuBiV;
      string SWbuwjilzX;
      string LfIZXyHILP;
      string VfFfcbQRIm;
      string isHWZLZnSt;
      string hUIdNUsQHg;
      string BmoTzlRwRU;
      string TQcMoSXlzL;
      string YSoRgAWbRI;
      string hzKbkuEnXm;
      string scVyaRrwnu;
      string xHQuHhxWlz;
      string PpeJlTGBas;
      string NjNLSwwqqP;
      string IamWLahOTC;
      string xgBXXCyMMG;
      string LpVugMsFcL;
      string lGeWqnDIyK;
      string kqhXugipnP;
      string yjdkERFqoy;
      if(BCpefJuBiV == scVyaRrwnu){hckIQpBdgi = true;}
      else if(scVyaRrwnu == BCpefJuBiV){kICDWaPxTt = true;}
      if(SWbuwjilzX == xHQuHhxWlz){zpNCUTIyzA = true;}
      else if(xHQuHhxWlz == SWbuwjilzX){kyapjNccrW = true;}
      if(LfIZXyHILP == PpeJlTGBas){dCRNNBctSY = true;}
      else if(PpeJlTGBas == LfIZXyHILP){SrgbOfDADx = true;}
      if(VfFfcbQRIm == NjNLSwwqqP){iLSAcIFZGE = true;}
      else if(NjNLSwwqqP == VfFfcbQRIm){fsITTVyZLn = true;}
      if(isHWZLZnSt == IamWLahOTC){eEIEPIWbPj = true;}
      else if(IamWLahOTC == isHWZLZnSt){MWKkMyHnGc = true;}
      if(hUIdNUsQHg == xgBXXCyMMG){JHroTeLXuP = true;}
      else if(xgBXXCyMMG == hUIdNUsQHg){uPIgJraZoq = true;}
      if(BmoTzlRwRU == LpVugMsFcL){NHLHzmWNZL = true;}
      else if(LpVugMsFcL == BmoTzlRwRU){WPsWNrpGVO = true;}
      if(TQcMoSXlzL == lGeWqnDIyK){NiqtUZtMxE = true;}
      if(YSoRgAWbRI == kqhXugipnP){eAdhPbTdfx = true;}
      if(hzKbkuEnXm == yjdkERFqoy){xheqqXsAEc = true;}
      while(lGeWqnDIyK == TQcMoSXlzL){OCREKwhwPP = true;}
      while(kqhXugipnP == kqhXugipnP){XOtZBQkaKa = true;}
      while(yjdkERFqoy == yjdkERFqoy){tXkTRxcnXU = true;}
      if(hckIQpBdgi == true){hckIQpBdgi = false;}
      if(zpNCUTIyzA == true){zpNCUTIyzA = false;}
      if(dCRNNBctSY == true){dCRNNBctSY = false;}
      if(iLSAcIFZGE == true){iLSAcIFZGE = false;}
      if(eEIEPIWbPj == true){eEIEPIWbPj = false;}
      if(JHroTeLXuP == true){JHroTeLXuP = false;}
      if(NHLHzmWNZL == true){NHLHzmWNZL = false;}
      if(NiqtUZtMxE == true){NiqtUZtMxE = false;}
      if(eAdhPbTdfx == true){eAdhPbTdfx = false;}
      if(xheqqXsAEc == true){xheqqXsAEc = false;}
      if(kICDWaPxTt == true){kICDWaPxTt = false;}
      if(kyapjNccrW == true){kyapjNccrW = false;}
      if(SrgbOfDADx == true){SrgbOfDADx = false;}
      if(fsITTVyZLn == true){fsITTVyZLn = false;}
      if(MWKkMyHnGc == true){MWKkMyHnGc = false;}
      if(uPIgJraZoq == true){uPIgJraZoq = false;}
      if(WPsWNrpGVO == true){WPsWNrpGVO = false;}
      if(OCREKwhwPP == true){OCREKwhwPP = false;}
      if(XOtZBQkaKa == true){XOtZBQkaKa = false;}
      if(tXkTRxcnXU == true){tXkTRxcnXU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTMBTWFDUU
{ 
  void oUFDaigxmC()
  { 
      bool SYfHZMxnTf = false;
      bool KgRhgJtywq = false;
      bool zPoPZBXfJh = false;
      bool BGqDhjFrtV = false;
      bool iLTVRwWWHk = false;
      bool OZOFbCiQhX = false;
      bool nRekeEoOAw = false;
      bool DCDaImwTxd = false;
      bool dBXYTaqlae = false;
      bool AoKVhQghpM = false;
      bool GIWKhLVnxn = false;
      bool GOSEtlsGQD = false;
      bool NCmUwNqhsq = false;
      bool GNcjWVeNpH = false;
      bool FDnmYkVGau = false;
      bool XaRmzDUBNT = false;
      bool UnuGhrlihY = false;
      bool HePJyJOAwK = false;
      bool rkGxTfwpjS = false;
      bool AczWmRIgEf = false;
      string iYkJdwFkXn;
      string aYNXVlmGqz;
      string LJSFWBZswg;
      string iUZRucwHlO;
      string TBcMbhZhyE;
      string lYdhdZGelb;
      string VLnpFGzucs;
      string pfTcfKfFdn;
      string brtquJqrmU;
      string WQVJsHNmHV;
      string idFFOFFBCT;
      string sAAxAcRwtw;
      string PGIHWYKJiX;
      string wsyIFymncp;
      string EooTbVQXJP;
      string pQrKGbUxio;
      string uuRdWACrrC;
      string pcTEqZRneA;
      string IlAThfAmCc;
      string coFntJXLwb;
      if(iYkJdwFkXn == idFFOFFBCT){SYfHZMxnTf = true;}
      else if(idFFOFFBCT == iYkJdwFkXn){GIWKhLVnxn = true;}
      if(aYNXVlmGqz == sAAxAcRwtw){KgRhgJtywq = true;}
      else if(sAAxAcRwtw == aYNXVlmGqz){GOSEtlsGQD = true;}
      if(LJSFWBZswg == PGIHWYKJiX){zPoPZBXfJh = true;}
      else if(PGIHWYKJiX == LJSFWBZswg){NCmUwNqhsq = true;}
      if(iUZRucwHlO == wsyIFymncp){BGqDhjFrtV = true;}
      else if(wsyIFymncp == iUZRucwHlO){GNcjWVeNpH = true;}
      if(TBcMbhZhyE == EooTbVQXJP){iLTVRwWWHk = true;}
      else if(EooTbVQXJP == TBcMbhZhyE){FDnmYkVGau = true;}
      if(lYdhdZGelb == pQrKGbUxio){OZOFbCiQhX = true;}
      else if(pQrKGbUxio == lYdhdZGelb){XaRmzDUBNT = true;}
      if(VLnpFGzucs == uuRdWACrrC){nRekeEoOAw = true;}
      else if(uuRdWACrrC == VLnpFGzucs){UnuGhrlihY = true;}
      if(pfTcfKfFdn == pcTEqZRneA){DCDaImwTxd = true;}
      if(brtquJqrmU == IlAThfAmCc){dBXYTaqlae = true;}
      if(WQVJsHNmHV == coFntJXLwb){AoKVhQghpM = true;}
      while(pcTEqZRneA == pfTcfKfFdn){HePJyJOAwK = true;}
      while(IlAThfAmCc == IlAThfAmCc){rkGxTfwpjS = true;}
      while(coFntJXLwb == coFntJXLwb){AczWmRIgEf = true;}
      if(SYfHZMxnTf == true){SYfHZMxnTf = false;}
      if(KgRhgJtywq == true){KgRhgJtywq = false;}
      if(zPoPZBXfJh == true){zPoPZBXfJh = false;}
      if(BGqDhjFrtV == true){BGqDhjFrtV = false;}
      if(iLTVRwWWHk == true){iLTVRwWWHk = false;}
      if(OZOFbCiQhX == true){OZOFbCiQhX = false;}
      if(nRekeEoOAw == true){nRekeEoOAw = false;}
      if(DCDaImwTxd == true){DCDaImwTxd = false;}
      if(dBXYTaqlae == true){dBXYTaqlae = false;}
      if(AoKVhQghpM == true){AoKVhQghpM = false;}
      if(GIWKhLVnxn == true){GIWKhLVnxn = false;}
      if(GOSEtlsGQD == true){GOSEtlsGQD = false;}
      if(NCmUwNqhsq == true){NCmUwNqhsq = false;}
      if(GNcjWVeNpH == true){GNcjWVeNpH = false;}
      if(FDnmYkVGau == true){FDnmYkVGau = false;}
      if(XaRmzDUBNT == true){XaRmzDUBNT = false;}
      if(UnuGhrlihY == true){UnuGhrlihY = false;}
      if(HePJyJOAwK == true){HePJyJOAwK = false;}
      if(rkGxTfwpjS == true){rkGxTfwpjS = false;}
      if(AczWmRIgEf == true){AczWmRIgEf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MDNCSMNYAY
{ 
  void olAxsUMYFl()
  { 
      bool OVRAhkipWQ = false;
      bool NnEloOPWNJ = false;
      bool IWDnASQkJG = false;
      bool BOGXIrFQLJ = false;
      bool XNQjhHlXOI = false;
      bool XmwSFqSczP = false;
      bool UyfQPzhfdw = false;
      bool IzKEluFSGs = false;
      bool fsVBiNSmSQ = false;
      bool YcRwnYgATi = false;
      bool YFtRzXcrgK = false;
      bool lAWFiabdgC = false;
      bool ftNMWfgOPM = false;
      bool NEyWTZzDBK = false;
      bool kaFHeYGLMM = false;
      bool xDTRCdrhuS = false;
      bool pNbUwhBzkI = false;
      bool bYbVRFoFgx = false;
      bool ZVBCPKjfTo = false;
      bool hRIiTWykLw = false;
      string iKysQuqklQ;
      string SjrNmbBUfs;
      string NJDYMgRVnb;
      string kBMdmyfEuL;
      string dPVOgANetn;
      string IUWeqZHYgi;
      string cVwJfRXOan;
      string uxZUPxmorL;
      string SlaATPdglN;
      string qGXMhHTMhP;
      string czEGrLtCPs;
      string lRgUPquwoP;
      string mpbNwoZNlH;
      string dZGciThTHI;
      string UaRraYZCwq;
      string MXWRblXqJD;
      string kgQIPLKDkw;
      string JangtLXimW;
      string OWQttGDnAw;
      string upJDWnKJcO;
      if(iKysQuqklQ == czEGrLtCPs){OVRAhkipWQ = true;}
      else if(czEGrLtCPs == iKysQuqklQ){YFtRzXcrgK = true;}
      if(SjrNmbBUfs == lRgUPquwoP){NnEloOPWNJ = true;}
      else if(lRgUPquwoP == SjrNmbBUfs){lAWFiabdgC = true;}
      if(NJDYMgRVnb == mpbNwoZNlH){IWDnASQkJG = true;}
      else if(mpbNwoZNlH == NJDYMgRVnb){ftNMWfgOPM = true;}
      if(kBMdmyfEuL == dZGciThTHI){BOGXIrFQLJ = true;}
      else if(dZGciThTHI == kBMdmyfEuL){NEyWTZzDBK = true;}
      if(dPVOgANetn == UaRraYZCwq){XNQjhHlXOI = true;}
      else if(UaRraYZCwq == dPVOgANetn){kaFHeYGLMM = true;}
      if(IUWeqZHYgi == MXWRblXqJD){XmwSFqSczP = true;}
      else if(MXWRblXqJD == IUWeqZHYgi){xDTRCdrhuS = true;}
      if(cVwJfRXOan == kgQIPLKDkw){UyfQPzhfdw = true;}
      else if(kgQIPLKDkw == cVwJfRXOan){pNbUwhBzkI = true;}
      if(uxZUPxmorL == JangtLXimW){IzKEluFSGs = true;}
      if(SlaATPdglN == OWQttGDnAw){fsVBiNSmSQ = true;}
      if(qGXMhHTMhP == upJDWnKJcO){YcRwnYgATi = true;}
      while(JangtLXimW == uxZUPxmorL){bYbVRFoFgx = true;}
      while(OWQttGDnAw == OWQttGDnAw){ZVBCPKjfTo = true;}
      while(upJDWnKJcO == upJDWnKJcO){hRIiTWykLw = true;}
      if(OVRAhkipWQ == true){OVRAhkipWQ = false;}
      if(NnEloOPWNJ == true){NnEloOPWNJ = false;}
      if(IWDnASQkJG == true){IWDnASQkJG = false;}
      if(BOGXIrFQLJ == true){BOGXIrFQLJ = false;}
      if(XNQjhHlXOI == true){XNQjhHlXOI = false;}
      if(XmwSFqSczP == true){XmwSFqSczP = false;}
      if(UyfQPzhfdw == true){UyfQPzhfdw = false;}
      if(IzKEluFSGs == true){IzKEluFSGs = false;}
      if(fsVBiNSmSQ == true){fsVBiNSmSQ = false;}
      if(YcRwnYgATi == true){YcRwnYgATi = false;}
      if(YFtRzXcrgK == true){YFtRzXcrgK = false;}
      if(lAWFiabdgC == true){lAWFiabdgC = false;}
      if(ftNMWfgOPM == true){ftNMWfgOPM = false;}
      if(NEyWTZzDBK == true){NEyWTZzDBK = false;}
      if(kaFHeYGLMM == true){kaFHeYGLMM = false;}
      if(xDTRCdrhuS == true){xDTRCdrhuS = false;}
      if(pNbUwhBzkI == true){pNbUwhBzkI = false;}
      if(bYbVRFoFgx == true){bYbVRFoFgx = false;}
      if(ZVBCPKjfTo == true){ZVBCPKjfTo = false;}
      if(hRIiTWykLw == true){hRIiTWykLw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGWEQLSDUT
{ 
  void bFnkLjGzSE()
  { 
      bool NwXRxYxtKY = false;
      bool gZKkFIFlYa = false;
      bool ejyeUOSyee = false;
      bool aohXGmBVAy = false;
      bool OQcZjwfVoI = false;
      bool nNDAldxsxh = false;
      bool GzOeyrrleR = false;
      bool HikZMOGYtX = false;
      bool iwJWqMkgkb = false;
      bool oHYRrPByar = false;
      bool EspXBFbdnW = false;
      bool WYyZzJornk = false;
      bool GKADbzKTgx = false;
      bool NIxCTpGlUk = false;
      bool kHsNEQJyRi = false;
      bool ZIJpksrmwB = false;
      bool uIxpJOawGJ = false;
      bool DDXCAzQlyK = false;
      bool pLBxWFyHRZ = false;
      bool xToSpbKCEp = false;
      string YZACTUnbBY;
      string dCzbkReeeJ;
      string YtJugEkZte;
      string fATUdxwDXg;
      string ABHomZnwAp;
      string DzgbOdPFUO;
      string jNgWrcieyn;
      string VbHxJXlTIH;
      string PnZEafSrGz;
      string gqhIxlTkwJ;
      string pIyMUbrjSq;
      string quwNyuncuM;
      string JqYyGetyAW;
      string DBXyQHpNjz;
      string miYOIltUJC;
      string yqpjzzjAFo;
      string hsiwmpXxwq;
      string EZswYaRJpT;
      string jZnxXMKmyR;
      string WpHtQszcbR;
      if(YZACTUnbBY == pIyMUbrjSq){NwXRxYxtKY = true;}
      else if(pIyMUbrjSq == YZACTUnbBY){EspXBFbdnW = true;}
      if(dCzbkReeeJ == quwNyuncuM){gZKkFIFlYa = true;}
      else if(quwNyuncuM == dCzbkReeeJ){WYyZzJornk = true;}
      if(YtJugEkZte == JqYyGetyAW){ejyeUOSyee = true;}
      else if(JqYyGetyAW == YtJugEkZte){GKADbzKTgx = true;}
      if(fATUdxwDXg == DBXyQHpNjz){aohXGmBVAy = true;}
      else if(DBXyQHpNjz == fATUdxwDXg){NIxCTpGlUk = true;}
      if(ABHomZnwAp == miYOIltUJC){OQcZjwfVoI = true;}
      else if(miYOIltUJC == ABHomZnwAp){kHsNEQJyRi = true;}
      if(DzgbOdPFUO == yqpjzzjAFo){nNDAldxsxh = true;}
      else if(yqpjzzjAFo == DzgbOdPFUO){ZIJpksrmwB = true;}
      if(jNgWrcieyn == hsiwmpXxwq){GzOeyrrleR = true;}
      else if(hsiwmpXxwq == jNgWrcieyn){uIxpJOawGJ = true;}
      if(VbHxJXlTIH == EZswYaRJpT){HikZMOGYtX = true;}
      if(PnZEafSrGz == jZnxXMKmyR){iwJWqMkgkb = true;}
      if(gqhIxlTkwJ == WpHtQszcbR){oHYRrPByar = true;}
      while(EZswYaRJpT == VbHxJXlTIH){DDXCAzQlyK = true;}
      while(jZnxXMKmyR == jZnxXMKmyR){pLBxWFyHRZ = true;}
      while(WpHtQszcbR == WpHtQszcbR){xToSpbKCEp = true;}
      if(NwXRxYxtKY == true){NwXRxYxtKY = false;}
      if(gZKkFIFlYa == true){gZKkFIFlYa = false;}
      if(ejyeUOSyee == true){ejyeUOSyee = false;}
      if(aohXGmBVAy == true){aohXGmBVAy = false;}
      if(OQcZjwfVoI == true){OQcZjwfVoI = false;}
      if(nNDAldxsxh == true){nNDAldxsxh = false;}
      if(GzOeyrrleR == true){GzOeyrrleR = false;}
      if(HikZMOGYtX == true){HikZMOGYtX = false;}
      if(iwJWqMkgkb == true){iwJWqMkgkb = false;}
      if(oHYRrPByar == true){oHYRrPByar = false;}
      if(EspXBFbdnW == true){EspXBFbdnW = false;}
      if(WYyZzJornk == true){WYyZzJornk = false;}
      if(GKADbzKTgx == true){GKADbzKTgx = false;}
      if(NIxCTpGlUk == true){NIxCTpGlUk = false;}
      if(kHsNEQJyRi == true){kHsNEQJyRi = false;}
      if(ZIJpksrmwB == true){ZIJpksrmwB = false;}
      if(uIxpJOawGJ == true){uIxpJOawGJ = false;}
      if(DDXCAzQlyK == true){DDXCAzQlyK = false;}
      if(pLBxWFyHRZ == true){pLBxWFyHRZ = false;}
      if(xToSpbKCEp == true){xToSpbKCEp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDHASGLTVQ
{ 
  void MHWHZHGVgf()
  { 
      bool XgxJdqNGwu = false;
      bool IaIYjPEqbs = false;
      bool WVGHVkgwkl = false;
      bool CSRuEqebXa = false;
      bool YiEqdRoGyX = false;
      bool GZIlRBZons = false;
      bool KRVJroJMUs = false;
      bool jbTAUnRPdD = false;
      bool uZxNfcKecD = false;
      bool QondQHNuyn = false;
      bool IblFmeFHRc = false;
      bool iKLjyjTIdP = false;
      bool edjRbumoiM = false;
      bool aWQotTnrZB = false;
      bool WCMzTGdDfg = false;
      bool nEQiIdrUcr = false;
      bool qPXFCMsVoe = false;
      bool uahcrbRjxU = false;
      bool RiJCXVFhgQ = false;
      bool aTOhJHdHxG = false;
      string DnXzxMRitV;
      string YRPeDVUzfZ;
      string aXhjPQSPQC;
      string TamfLSFSje;
      string CgYtpXRxIU;
      string MQIpHeFmif;
      string tBRrCxeiSj;
      string PCPAXtzmsq;
      string zUGwoCSwYg;
      string MSiEkAOfrs;
      string sheYFKBIRM;
      string eRsrfYuVCz;
      string dhJlWxSKOX;
      string fStAyQphpe;
      string BKeMBuYqYM;
      string EsdsOLXsBH;
      string qpstfMXrsO;
      string hNeXxTDxjb;
      string XblBSmoBll;
      string sxfimKQjfo;
      if(DnXzxMRitV == sheYFKBIRM){XgxJdqNGwu = true;}
      else if(sheYFKBIRM == DnXzxMRitV){IblFmeFHRc = true;}
      if(YRPeDVUzfZ == eRsrfYuVCz){IaIYjPEqbs = true;}
      else if(eRsrfYuVCz == YRPeDVUzfZ){iKLjyjTIdP = true;}
      if(aXhjPQSPQC == dhJlWxSKOX){WVGHVkgwkl = true;}
      else if(dhJlWxSKOX == aXhjPQSPQC){edjRbumoiM = true;}
      if(TamfLSFSje == fStAyQphpe){CSRuEqebXa = true;}
      else if(fStAyQphpe == TamfLSFSje){aWQotTnrZB = true;}
      if(CgYtpXRxIU == BKeMBuYqYM){YiEqdRoGyX = true;}
      else if(BKeMBuYqYM == CgYtpXRxIU){WCMzTGdDfg = true;}
      if(MQIpHeFmif == EsdsOLXsBH){GZIlRBZons = true;}
      else if(EsdsOLXsBH == MQIpHeFmif){nEQiIdrUcr = true;}
      if(tBRrCxeiSj == qpstfMXrsO){KRVJroJMUs = true;}
      else if(qpstfMXrsO == tBRrCxeiSj){qPXFCMsVoe = true;}
      if(PCPAXtzmsq == hNeXxTDxjb){jbTAUnRPdD = true;}
      if(zUGwoCSwYg == XblBSmoBll){uZxNfcKecD = true;}
      if(MSiEkAOfrs == sxfimKQjfo){QondQHNuyn = true;}
      while(hNeXxTDxjb == PCPAXtzmsq){uahcrbRjxU = true;}
      while(XblBSmoBll == XblBSmoBll){RiJCXVFhgQ = true;}
      while(sxfimKQjfo == sxfimKQjfo){aTOhJHdHxG = true;}
      if(XgxJdqNGwu == true){XgxJdqNGwu = false;}
      if(IaIYjPEqbs == true){IaIYjPEqbs = false;}
      if(WVGHVkgwkl == true){WVGHVkgwkl = false;}
      if(CSRuEqebXa == true){CSRuEqebXa = false;}
      if(YiEqdRoGyX == true){YiEqdRoGyX = false;}
      if(GZIlRBZons == true){GZIlRBZons = false;}
      if(KRVJroJMUs == true){KRVJroJMUs = false;}
      if(jbTAUnRPdD == true){jbTAUnRPdD = false;}
      if(uZxNfcKecD == true){uZxNfcKecD = false;}
      if(QondQHNuyn == true){QondQHNuyn = false;}
      if(IblFmeFHRc == true){IblFmeFHRc = false;}
      if(iKLjyjTIdP == true){iKLjyjTIdP = false;}
      if(edjRbumoiM == true){edjRbumoiM = false;}
      if(aWQotTnrZB == true){aWQotTnrZB = false;}
      if(WCMzTGdDfg == true){WCMzTGdDfg = false;}
      if(nEQiIdrUcr == true){nEQiIdrUcr = false;}
      if(qPXFCMsVoe == true){qPXFCMsVoe = false;}
      if(uahcrbRjxU == true){uahcrbRjxU = false;}
      if(RiJCXVFhgQ == true){RiJCXVFhgQ = false;}
      if(aTOhJHdHxG == true){aTOhJHdHxG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPGTXECQLP
{ 
  void omjtubbHmn()
  { 
      bool PSCWazXdqQ = false;
      bool NpsQQiocFc = false;
      bool kyTxjwkrOO = false;
      bool cXlXzoVBTe = false;
      bool xIYdcVadNQ = false;
      bool XwsbFRyEle = false;
      bool NeOcmoEUQb = false;
      bool MnJaebYoUN = false;
      bool VGdyqfeJRh = false;
      bool pROoQRswpm = false;
      bool RFNkDjlSxd = false;
      bool sJjYIHAQkG = false;
      bool KtDiluYUJN = false;
      bool icygwPsstH = false;
      bool tMMnnghpfI = false;
      bool QbKjcWCdzI = false;
      bool KRIitPKCcs = false;
      bool OHWdMxhPtE = false;
      bool NhoAwGRODY = false;
      bool NOskwcEcsY = false;
      string wTTRZDMXRX;
      string usYHIRGcKq;
      string zCNJkKwCeT;
      string nmOOLjTlZo;
      string wOKGbUmhAM;
      string qHemysGJfO;
      string GKsyiIeKwY;
      string yUCUukqHgQ;
      string WOCRcfHaPR;
      string dJFKilVMWT;
      string oblaNVFJrN;
      string CzbPqrHaUC;
      string AEtdtoOqlI;
      string PdjNaubbDG;
      string axhCOegpSq;
      string etrTSjhHfY;
      string HNXixXOOnw;
      string PfWNbCWqOP;
      string HXXtdUlQtp;
      string MTuezMZyFq;
      if(wTTRZDMXRX == oblaNVFJrN){PSCWazXdqQ = true;}
      else if(oblaNVFJrN == wTTRZDMXRX){RFNkDjlSxd = true;}
      if(usYHIRGcKq == CzbPqrHaUC){NpsQQiocFc = true;}
      else if(CzbPqrHaUC == usYHIRGcKq){sJjYIHAQkG = true;}
      if(zCNJkKwCeT == AEtdtoOqlI){kyTxjwkrOO = true;}
      else if(AEtdtoOqlI == zCNJkKwCeT){KtDiluYUJN = true;}
      if(nmOOLjTlZo == PdjNaubbDG){cXlXzoVBTe = true;}
      else if(PdjNaubbDG == nmOOLjTlZo){icygwPsstH = true;}
      if(wOKGbUmhAM == axhCOegpSq){xIYdcVadNQ = true;}
      else if(axhCOegpSq == wOKGbUmhAM){tMMnnghpfI = true;}
      if(qHemysGJfO == etrTSjhHfY){XwsbFRyEle = true;}
      else if(etrTSjhHfY == qHemysGJfO){QbKjcWCdzI = true;}
      if(GKsyiIeKwY == HNXixXOOnw){NeOcmoEUQb = true;}
      else if(HNXixXOOnw == GKsyiIeKwY){KRIitPKCcs = true;}
      if(yUCUukqHgQ == PfWNbCWqOP){MnJaebYoUN = true;}
      if(WOCRcfHaPR == HXXtdUlQtp){VGdyqfeJRh = true;}
      if(dJFKilVMWT == MTuezMZyFq){pROoQRswpm = true;}
      while(PfWNbCWqOP == yUCUukqHgQ){OHWdMxhPtE = true;}
      while(HXXtdUlQtp == HXXtdUlQtp){NhoAwGRODY = true;}
      while(MTuezMZyFq == MTuezMZyFq){NOskwcEcsY = true;}
      if(PSCWazXdqQ == true){PSCWazXdqQ = false;}
      if(NpsQQiocFc == true){NpsQQiocFc = false;}
      if(kyTxjwkrOO == true){kyTxjwkrOO = false;}
      if(cXlXzoVBTe == true){cXlXzoVBTe = false;}
      if(xIYdcVadNQ == true){xIYdcVadNQ = false;}
      if(XwsbFRyEle == true){XwsbFRyEle = false;}
      if(NeOcmoEUQb == true){NeOcmoEUQb = false;}
      if(MnJaebYoUN == true){MnJaebYoUN = false;}
      if(VGdyqfeJRh == true){VGdyqfeJRh = false;}
      if(pROoQRswpm == true){pROoQRswpm = false;}
      if(RFNkDjlSxd == true){RFNkDjlSxd = false;}
      if(sJjYIHAQkG == true){sJjYIHAQkG = false;}
      if(KtDiluYUJN == true){KtDiluYUJN = false;}
      if(icygwPsstH == true){icygwPsstH = false;}
      if(tMMnnghpfI == true){tMMnnghpfI = false;}
      if(QbKjcWCdzI == true){QbKjcWCdzI = false;}
      if(KRIitPKCcs == true){KRIitPKCcs = false;}
      if(OHWdMxhPtE == true){OHWdMxhPtE = false;}
      if(NhoAwGRODY == true){NhoAwGRODY = false;}
      if(NOskwcEcsY == true){NOskwcEcsY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPNGBDCJJW
{ 
  void yFycfMpUNZ()
  { 
      bool UoZYKHVVaE = false;
      bool blhioHOOtV = false;
      bool qhmppTBpmK = false;
      bool VjRoufLKwm = false;
      bool pcyyWtCogI = false;
      bool eCpqmlBjhq = false;
      bool GeiPirUsmJ = false;
      bool wESHfOjnSw = false;
      bool QMJefSsZCI = false;
      bool dabFgLthPe = false;
      bool ZJBWLajiLX = false;
      bool CNRlZtUDjP = false;
      bool ytqdeUbMZT = false;
      bool TBXmVHKlSF = false;
      bool hKNdGQJpem = false;
      bool ppyAgeSWqq = false;
      bool yXIrDBodPR = false;
      bool ihkegmgMXO = false;
      bool KlgmddCWFq = false;
      bool onuaGKCVZE = false;
      string BHysGQzLTM;
      string QHcqIpZiLu;
      string nVStUptmXA;
      string wHRaQcWYje;
      string oQHodgwQYe;
      string wcZYBeoDYQ;
      string VLmSPJoBaf;
      string TBzfGXOdQm;
      string sdOsETgsZl;
      string mSATIdcnZT;
      string rtprLtcsSc;
      string QLmkWrwtOu;
      string bubnrABfXb;
      string uZDwuzmWgK;
      string qnawUbfPwP;
      string giZerwRBzK;
      string sxVphqHpoX;
      string FYMDDnUfTQ;
      string UliHuMzYDz;
      string gkXWQsRkNd;
      if(BHysGQzLTM == rtprLtcsSc){UoZYKHVVaE = true;}
      else if(rtprLtcsSc == BHysGQzLTM){ZJBWLajiLX = true;}
      if(QHcqIpZiLu == QLmkWrwtOu){blhioHOOtV = true;}
      else if(QLmkWrwtOu == QHcqIpZiLu){CNRlZtUDjP = true;}
      if(nVStUptmXA == bubnrABfXb){qhmppTBpmK = true;}
      else if(bubnrABfXb == nVStUptmXA){ytqdeUbMZT = true;}
      if(wHRaQcWYje == uZDwuzmWgK){VjRoufLKwm = true;}
      else if(uZDwuzmWgK == wHRaQcWYje){TBXmVHKlSF = true;}
      if(oQHodgwQYe == qnawUbfPwP){pcyyWtCogI = true;}
      else if(qnawUbfPwP == oQHodgwQYe){hKNdGQJpem = true;}
      if(wcZYBeoDYQ == giZerwRBzK){eCpqmlBjhq = true;}
      else if(giZerwRBzK == wcZYBeoDYQ){ppyAgeSWqq = true;}
      if(VLmSPJoBaf == sxVphqHpoX){GeiPirUsmJ = true;}
      else if(sxVphqHpoX == VLmSPJoBaf){yXIrDBodPR = true;}
      if(TBzfGXOdQm == FYMDDnUfTQ){wESHfOjnSw = true;}
      if(sdOsETgsZl == UliHuMzYDz){QMJefSsZCI = true;}
      if(mSATIdcnZT == gkXWQsRkNd){dabFgLthPe = true;}
      while(FYMDDnUfTQ == TBzfGXOdQm){ihkegmgMXO = true;}
      while(UliHuMzYDz == UliHuMzYDz){KlgmddCWFq = true;}
      while(gkXWQsRkNd == gkXWQsRkNd){onuaGKCVZE = true;}
      if(UoZYKHVVaE == true){UoZYKHVVaE = false;}
      if(blhioHOOtV == true){blhioHOOtV = false;}
      if(qhmppTBpmK == true){qhmppTBpmK = false;}
      if(VjRoufLKwm == true){VjRoufLKwm = false;}
      if(pcyyWtCogI == true){pcyyWtCogI = false;}
      if(eCpqmlBjhq == true){eCpqmlBjhq = false;}
      if(GeiPirUsmJ == true){GeiPirUsmJ = false;}
      if(wESHfOjnSw == true){wESHfOjnSw = false;}
      if(QMJefSsZCI == true){QMJefSsZCI = false;}
      if(dabFgLthPe == true){dabFgLthPe = false;}
      if(ZJBWLajiLX == true){ZJBWLajiLX = false;}
      if(CNRlZtUDjP == true){CNRlZtUDjP = false;}
      if(ytqdeUbMZT == true){ytqdeUbMZT = false;}
      if(TBXmVHKlSF == true){TBXmVHKlSF = false;}
      if(hKNdGQJpem == true){hKNdGQJpem = false;}
      if(ppyAgeSWqq == true){ppyAgeSWqq = false;}
      if(yXIrDBodPR == true){yXIrDBodPR = false;}
      if(ihkegmgMXO == true){ihkegmgMXO = false;}
      if(KlgmddCWFq == true){KlgmddCWFq = false;}
      if(onuaGKCVZE == true){onuaGKCVZE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTOIWLFRNZ
{ 
  void WIAQJUXSGq()
  { 
      bool LVUwHoXgej = false;
      bool TyhBLVkroa = false;
      bool KFajUERSLp = false;
      bool erbxEELlJH = false;
      bool iMxFYpwyoh = false;
      bool dwNTGGujaC = false;
      bool XEVoFbVjxH = false;
      bool JyigqyHUKe = false;
      bool ISccLhdHqx = false;
      bool IaLHjdpHzx = false;
      bool TLBhYfNgcH = false;
      bool yZZwtEbrcW = false;
      bool xNszzhmawM = false;
      bool HzVMKwRuEf = false;
      bool UxeizhBONe = false;
      bool CyeczFSBhp = false;
      bool rljPAyENkx = false;
      bool mfmwBAiJAQ = false;
      bool gXNRJJUrME = false;
      bool dPMOniMOiA = false;
      string yVwUFxyuqq;
      string UlCXXjqkUR;
      string wpnUZIiUzg;
      string NmUrXXYdWN;
      string UwdCERedbL;
      string tWXmhHhbtx;
      string OcwJdhRKzA;
      string LNOGwALlQI;
      string dFsnmpPgKQ;
      string pxiZzqAUXW;
      string ATebAfIQqh;
      string uwKlTJjIWm;
      string SkziJNdoHE;
      string zqNtIJZRnG;
      string hyocUtmxGp;
      string HrxkEPUwRl;
      string CSJlhEhQcJ;
      string iRTPFTuWNP;
      string afhQxHtcps;
      string ndABEOoDtQ;
      if(yVwUFxyuqq == ATebAfIQqh){LVUwHoXgej = true;}
      else if(ATebAfIQqh == yVwUFxyuqq){TLBhYfNgcH = true;}
      if(UlCXXjqkUR == uwKlTJjIWm){TyhBLVkroa = true;}
      else if(uwKlTJjIWm == UlCXXjqkUR){yZZwtEbrcW = true;}
      if(wpnUZIiUzg == SkziJNdoHE){KFajUERSLp = true;}
      else if(SkziJNdoHE == wpnUZIiUzg){xNszzhmawM = true;}
      if(NmUrXXYdWN == zqNtIJZRnG){erbxEELlJH = true;}
      else if(zqNtIJZRnG == NmUrXXYdWN){HzVMKwRuEf = true;}
      if(UwdCERedbL == hyocUtmxGp){iMxFYpwyoh = true;}
      else if(hyocUtmxGp == UwdCERedbL){UxeizhBONe = true;}
      if(tWXmhHhbtx == HrxkEPUwRl){dwNTGGujaC = true;}
      else if(HrxkEPUwRl == tWXmhHhbtx){CyeczFSBhp = true;}
      if(OcwJdhRKzA == CSJlhEhQcJ){XEVoFbVjxH = true;}
      else if(CSJlhEhQcJ == OcwJdhRKzA){rljPAyENkx = true;}
      if(LNOGwALlQI == iRTPFTuWNP){JyigqyHUKe = true;}
      if(dFsnmpPgKQ == afhQxHtcps){ISccLhdHqx = true;}
      if(pxiZzqAUXW == ndABEOoDtQ){IaLHjdpHzx = true;}
      while(iRTPFTuWNP == LNOGwALlQI){mfmwBAiJAQ = true;}
      while(afhQxHtcps == afhQxHtcps){gXNRJJUrME = true;}
      while(ndABEOoDtQ == ndABEOoDtQ){dPMOniMOiA = true;}
      if(LVUwHoXgej == true){LVUwHoXgej = false;}
      if(TyhBLVkroa == true){TyhBLVkroa = false;}
      if(KFajUERSLp == true){KFajUERSLp = false;}
      if(erbxEELlJH == true){erbxEELlJH = false;}
      if(iMxFYpwyoh == true){iMxFYpwyoh = false;}
      if(dwNTGGujaC == true){dwNTGGujaC = false;}
      if(XEVoFbVjxH == true){XEVoFbVjxH = false;}
      if(JyigqyHUKe == true){JyigqyHUKe = false;}
      if(ISccLhdHqx == true){ISccLhdHqx = false;}
      if(IaLHjdpHzx == true){IaLHjdpHzx = false;}
      if(TLBhYfNgcH == true){TLBhYfNgcH = false;}
      if(yZZwtEbrcW == true){yZZwtEbrcW = false;}
      if(xNszzhmawM == true){xNszzhmawM = false;}
      if(HzVMKwRuEf == true){HzVMKwRuEf = false;}
      if(UxeizhBONe == true){UxeizhBONe = false;}
      if(CyeczFSBhp == true){CyeczFSBhp = false;}
      if(rljPAyENkx == true){rljPAyENkx = false;}
      if(mfmwBAiJAQ == true){mfmwBAiJAQ = false;}
      if(gXNRJJUrME == true){gXNRJJUrME = false;}
      if(dPMOniMOiA == true){dPMOniMOiA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKIYNOCSIA
{ 
  void WsZbRaJGnt()
  { 
      bool yyxNltKoGM = false;
      bool wppzQglVNn = false;
      bool XcHGrTmeCW = false;
      bool QlZDOExAyi = false;
      bool VRsGHRLiNx = false;
      bool nrRjFUqqVS = false;
      bool GemiwKQljM = false;
      bool jkWeSFjBya = false;
      bool IDQEhYUpxs = false;
      bool NFefbpdJJx = false;
      bool AYzBNDUlRA = false;
      bool kpstJCOhBX = false;
      bool panpydGqCb = false;
      bool aZqAZjEPqe = false;
      bool DhYxIXMjWZ = false;
      bool bwHlHZjICi = false;
      bool xdjoYKyrTZ = false;
      bool yyqWUHCqha = false;
      bool RVUcAeRErA = false;
      bool zuMIhYyiXx = false;
      string YttBhoDxXF;
      string kFTVKpNbiT;
      string TZjHIJGqnz;
      string aSOPPPzbkk;
      string tmjFHqiTup;
      string OUxJByJlsY;
      string hMIYdSqEGt;
      string qkpxZfodzQ;
      string amuyjFUENQ;
      string GMiMDgeLbo;
      string zdNAydeAiV;
      string IelbxuQJnX;
      string ylpondBdss;
      string BdCKRwYuzG;
      string aTVrIaZHOI;
      string PUWDqMnXMU;
      string bAGpUecbKA;
      string VVJgxdQxgN;
      string DtOkcfHzTE;
      string IBheeZNeXc;
      if(YttBhoDxXF == zdNAydeAiV){yyxNltKoGM = true;}
      else if(zdNAydeAiV == YttBhoDxXF){AYzBNDUlRA = true;}
      if(kFTVKpNbiT == IelbxuQJnX){wppzQglVNn = true;}
      else if(IelbxuQJnX == kFTVKpNbiT){kpstJCOhBX = true;}
      if(TZjHIJGqnz == ylpondBdss){XcHGrTmeCW = true;}
      else if(ylpondBdss == TZjHIJGqnz){panpydGqCb = true;}
      if(aSOPPPzbkk == BdCKRwYuzG){QlZDOExAyi = true;}
      else if(BdCKRwYuzG == aSOPPPzbkk){aZqAZjEPqe = true;}
      if(tmjFHqiTup == aTVrIaZHOI){VRsGHRLiNx = true;}
      else if(aTVrIaZHOI == tmjFHqiTup){DhYxIXMjWZ = true;}
      if(OUxJByJlsY == PUWDqMnXMU){nrRjFUqqVS = true;}
      else if(PUWDqMnXMU == OUxJByJlsY){bwHlHZjICi = true;}
      if(hMIYdSqEGt == bAGpUecbKA){GemiwKQljM = true;}
      else if(bAGpUecbKA == hMIYdSqEGt){xdjoYKyrTZ = true;}
      if(qkpxZfodzQ == VVJgxdQxgN){jkWeSFjBya = true;}
      if(amuyjFUENQ == DtOkcfHzTE){IDQEhYUpxs = true;}
      if(GMiMDgeLbo == IBheeZNeXc){NFefbpdJJx = true;}
      while(VVJgxdQxgN == qkpxZfodzQ){yyqWUHCqha = true;}
      while(DtOkcfHzTE == DtOkcfHzTE){RVUcAeRErA = true;}
      while(IBheeZNeXc == IBheeZNeXc){zuMIhYyiXx = true;}
      if(yyxNltKoGM == true){yyxNltKoGM = false;}
      if(wppzQglVNn == true){wppzQglVNn = false;}
      if(XcHGrTmeCW == true){XcHGrTmeCW = false;}
      if(QlZDOExAyi == true){QlZDOExAyi = false;}
      if(VRsGHRLiNx == true){VRsGHRLiNx = false;}
      if(nrRjFUqqVS == true){nrRjFUqqVS = false;}
      if(GemiwKQljM == true){GemiwKQljM = false;}
      if(jkWeSFjBya == true){jkWeSFjBya = false;}
      if(IDQEhYUpxs == true){IDQEhYUpxs = false;}
      if(NFefbpdJJx == true){NFefbpdJJx = false;}
      if(AYzBNDUlRA == true){AYzBNDUlRA = false;}
      if(kpstJCOhBX == true){kpstJCOhBX = false;}
      if(panpydGqCb == true){panpydGqCb = false;}
      if(aZqAZjEPqe == true){aZqAZjEPqe = false;}
      if(DhYxIXMjWZ == true){DhYxIXMjWZ = false;}
      if(bwHlHZjICi == true){bwHlHZjICi = false;}
      if(xdjoYKyrTZ == true){xdjoYKyrTZ = false;}
      if(yyqWUHCqha == true){yyqWUHCqha = false;}
      if(RVUcAeRErA == true){RVUcAeRErA = false;}
      if(zuMIhYyiXx == true){zuMIhYyiXx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOSXAALNUT
{ 
  void VduzjUUppZ()
  { 
      bool HmRBymOnuh = false;
      bool IwMdJuktkw = false;
      bool rWdlzzlHqJ = false;
      bool CniVVGffQW = false;
      bool QsIXkzPjRF = false;
      bool BTRSskJeCz = false;
      bool AHxkfUMqIC = false;
      bool PEcOezNFBA = false;
      bool iCplIhVQbk = false;
      bool xBcRVJwWrQ = false;
      bool lYbOpwqDnt = false;
      bool WDdCPyRKcx = false;
      bool ywOWEOaLrU = false;
      bool CpMjNKaawL = false;
      bool qSbhNsWaBX = false;
      bool qksuSpKEJa = false;
      bool UeKSqgqsoF = false;
      bool XqORGeUfJK = false;
      bool qAKTcRwRRW = false;
      bool AWQUpLIIpg = false;
      string KsVREAjHXP;
      string NWaCdWGEoZ;
      string GhioGtsYwy;
      string MEpofNsjqD;
      string TTwuwWVJix;
      string MJiyrcJgKJ;
      string GKKZDJglWP;
      string cVMkFllnrj;
      string YioykCUqwC;
      string ELZhwIJVrm;
      string pimTUpxxrF;
      string pVoakWVMnA;
      string npoTLQwenx;
      string cPuFtowVdu;
      string EXyqMhWyxZ;
      string mxhqyztTHD;
      string sSIubaajgu;
      string aAhswQqyHc;
      string txhOJfhEGt;
      string ubNaBlODOl;
      if(KsVREAjHXP == pimTUpxxrF){HmRBymOnuh = true;}
      else if(pimTUpxxrF == KsVREAjHXP){lYbOpwqDnt = true;}
      if(NWaCdWGEoZ == pVoakWVMnA){IwMdJuktkw = true;}
      else if(pVoakWVMnA == NWaCdWGEoZ){WDdCPyRKcx = true;}
      if(GhioGtsYwy == npoTLQwenx){rWdlzzlHqJ = true;}
      else if(npoTLQwenx == GhioGtsYwy){ywOWEOaLrU = true;}
      if(MEpofNsjqD == cPuFtowVdu){CniVVGffQW = true;}
      else if(cPuFtowVdu == MEpofNsjqD){CpMjNKaawL = true;}
      if(TTwuwWVJix == EXyqMhWyxZ){QsIXkzPjRF = true;}
      else if(EXyqMhWyxZ == TTwuwWVJix){qSbhNsWaBX = true;}
      if(MJiyrcJgKJ == mxhqyztTHD){BTRSskJeCz = true;}
      else if(mxhqyztTHD == MJiyrcJgKJ){qksuSpKEJa = true;}
      if(GKKZDJglWP == sSIubaajgu){AHxkfUMqIC = true;}
      else if(sSIubaajgu == GKKZDJglWP){UeKSqgqsoF = true;}
      if(cVMkFllnrj == aAhswQqyHc){PEcOezNFBA = true;}
      if(YioykCUqwC == txhOJfhEGt){iCplIhVQbk = true;}
      if(ELZhwIJVrm == ubNaBlODOl){xBcRVJwWrQ = true;}
      while(aAhswQqyHc == cVMkFllnrj){XqORGeUfJK = true;}
      while(txhOJfhEGt == txhOJfhEGt){qAKTcRwRRW = true;}
      while(ubNaBlODOl == ubNaBlODOl){AWQUpLIIpg = true;}
      if(HmRBymOnuh == true){HmRBymOnuh = false;}
      if(IwMdJuktkw == true){IwMdJuktkw = false;}
      if(rWdlzzlHqJ == true){rWdlzzlHqJ = false;}
      if(CniVVGffQW == true){CniVVGffQW = false;}
      if(QsIXkzPjRF == true){QsIXkzPjRF = false;}
      if(BTRSskJeCz == true){BTRSskJeCz = false;}
      if(AHxkfUMqIC == true){AHxkfUMqIC = false;}
      if(PEcOezNFBA == true){PEcOezNFBA = false;}
      if(iCplIhVQbk == true){iCplIhVQbk = false;}
      if(xBcRVJwWrQ == true){xBcRVJwWrQ = false;}
      if(lYbOpwqDnt == true){lYbOpwqDnt = false;}
      if(WDdCPyRKcx == true){WDdCPyRKcx = false;}
      if(ywOWEOaLrU == true){ywOWEOaLrU = false;}
      if(CpMjNKaawL == true){CpMjNKaawL = false;}
      if(qSbhNsWaBX == true){qSbhNsWaBX = false;}
      if(qksuSpKEJa == true){qksuSpKEJa = false;}
      if(UeKSqgqsoF == true){UeKSqgqsoF = false;}
      if(XqORGeUfJK == true){XqORGeUfJK = false;}
      if(qAKTcRwRRW == true){qAKTcRwRRW = false;}
      if(AWQUpLIIpg == true){AWQUpLIIpg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RAGQSGUNEQ
{ 
  void loXKxgRoQX()
  { 
      bool TQRGlhLZqi = false;
      bool xtFscGCqOD = false;
      bool anBcFUeAGy = false;
      bool RxsLAmdalb = false;
      bool oqyuksPdWL = false;
      bool dkhzcfPoBQ = false;
      bool CKSsRABtrp = false;
      bool cbFmNioGqL = false;
      bool FBduUfOtiU = false;
      bool XoYUYeXFcj = false;
      bool rVlghCeuks = false;
      bool pIxoLBgXYk = false;
      bool kHKWRnCkOi = false;
      bool KicHTjOxMS = false;
      bool BTIoeOqiIW = false;
      bool xAgrykKPOt = false;
      bool ztfChGfpVa = false;
      bool mjKFjRyVrD = false;
      bool wSbqkKCjIi = false;
      bool ZyhSSGmGHX = false;
      string YxLWeaMdNj;
      string qgUuVpbPbw;
      string rCbtznWHiS;
      string EpatcMDlMP;
      string cmowSPSzpU;
      string SVelVWVQWq;
      string EFuteAGaSI;
      string moDMSEMebj;
      string UWROziLoXG;
      string plPVKXruRS;
      string JrgghcSRSQ;
      string KqolVgmguu;
      string nQCLSAZhBt;
      string MRMIacpkfV;
      string QsVGwyxczc;
      string kLzVdroUNg;
      string DjPYErefLr;
      string qCAYeutuOU;
      string DwhYJBRpei;
      string mVWzSfcxCD;
      if(YxLWeaMdNj == JrgghcSRSQ){TQRGlhLZqi = true;}
      else if(JrgghcSRSQ == YxLWeaMdNj){rVlghCeuks = true;}
      if(qgUuVpbPbw == KqolVgmguu){xtFscGCqOD = true;}
      else if(KqolVgmguu == qgUuVpbPbw){pIxoLBgXYk = true;}
      if(rCbtznWHiS == nQCLSAZhBt){anBcFUeAGy = true;}
      else if(nQCLSAZhBt == rCbtznWHiS){kHKWRnCkOi = true;}
      if(EpatcMDlMP == MRMIacpkfV){RxsLAmdalb = true;}
      else if(MRMIacpkfV == EpatcMDlMP){KicHTjOxMS = true;}
      if(cmowSPSzpU == QsVGwyxczc){oqyuksPdWL = true;}
      else if(QsVGwyxczc == cmowSPSzpU){BTIoeOqiIW = true;}
      if(SVelVWVQWq == kLzVdroUNg){dkhzcfPoBQ = true;}
      else if(kLzVdroUNg == SVelVWVQWq){xAgrykKPOt = true;}
      if(EFuteAGaSI == DjPYErefLr){CKSsRABtrp = true;}
      else if(DjPYErefLr == EFuteAGaSI){ztfChGfpVa = true;}
      if(moDMSEMebj == qCAYeutuOU){cbFmNioGqL = true;}
      if(UWROziLoXG == DwhYJBRpei){FBduUfOtiU = true;}
      if(plPVKXruRS == mVWzSfcxCD){XoYUYeXFcj = true;}
      while(qCAYeutuOU == moDMSEMebj){mjKFjRyVrD = true;}
      while(DwhYJBRpei == DwhYJBRpei){wSbqkKCjIi = true;}
      while(mVWzSfcxCD == mVWzSfcxCD){ZyhSSGmGHX = true;}
      if(TQRGlhLZqi == true){TQRGlhLZqi = false;}
      if(xtFscGCqOD == true){xtFscGCqOD = false;}
      if(anBcFUeAGy == true){anBcFUeAGy = false;}
      if(RxsLAmdalb == true){RxsLAmdalb = false;}
      if(oqyuksPdWL == true){oqyuksPdWL = false;}
      if(dkhzcfPoBQ == true){dkhzcfPoBQ = false;}
      if(CKSsRABtrp == true){CKSsRABtrp = false;}
      if(cbFmNioGqL == true){cbFmNioGqL = false;}
      if(FBduUfOtiU == true){FBduUfOtiU = false;}
      if(XoYUYeXFcj == true){XoYUYeXFcj = false;}
      if(rVlghCeuks == true){rVlghCeuks = false;}
      if(pIxoLBgXYk == true){pIxoLBgXYk = false;}
      if(kHKWRnCkOi == true){kHKWRnCkOi = false;}
      if(KicHTjOxMS == true){KicHTjOxMS = false;}
      if(BTIoeOqiIW == true){BTIoeOqiIW = false;}
      if(xAgrykKPOt == true){xAgrykKPOt = false;}
      if(ztfChGfpVa == true){ztfChGfpVa = false;}
      if(mjKFjRyVrD == true){mjKFjRyVrD = false;}
      if(wSbqkKCjIi == true){wSbqkKCjIi = false;}
      if(ZyhSSGmGHX == true){ZyhSSGmGHX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIPWHVWWBT
{ 
  void AMZxOjOHrk()
  { 
      bool GMGzDgdiMs = false;
      bool JhnZoItVPW = false;
      bool HAnMfXEhzD = false;
      bool bprSiXhgcy = false;
      bool ukQYjtwnIp = false;
      bool RyGsaFYtSe = false;
      bool cujJRTpUqQ = false;
      bool ZNrQbWjObk = false;
      bool bPZJkciyrc = false;
      bool znNyVzAGHP = false;
      bool EbwqPEGpRD = false;
      bool VJRhCMVaXn = false;
      bool krbORlzsub = false;
      bool VcGMgAThsg = false;
      bool WsfnGoWfuI = false;
      bool dZhTeMzhZd = false;
      bool EMtphrDFAC = false;
      bool smgpRqLmIb = false;
      bool OTylywtmgU = false;
      bool AlIPcJypGN = false;
      string PdFialZfYm;
      string obnBiOFTnr;
      string QELTuOdHZf;
      string lBBWAmXVwC;
      string OTWcycfCmV;
      string ilhFcLRlnL;
      string IRGsAnaRBw;
      string piXlcwghUR;
      string iaUDwASuto;
      string UkhjsxNdcK;
      string COBpezNubf;
      string ejQVcgwDwA;
      string UeWLaFBnsf;
      string iCFJPTYdXx;
      string lXSNKkTMHL;
      string AJhbpWqoPZ;
      string yZCwwbdHFI;
      string ISfyOwMJBo;
      string kofgfZTdSs;
      string cjOxzLUWQh;
      if(PdFialZfYm == COBpezNubf){GMGzDgdiMs = true;}
      else if(COBpezNubf == PdFialZfYm){EbwqPEGpRD = true;}
      if(obnBiOFTnr == ejQVcgwDwA){JhnZoItVPW = true;}
      else if(ejQVcgwDwA == obnBiOFTnr){VJRhCMVaXn = true;}
      if(QELTuOdHZf == UeWLaFBnsf){HAnMfXEhzD = true;}
      else if(UeWLaFBnsf == QELTuOdHZf){krbORlzsub = true;}
      if(lBBWAmXVwC == iCFJPTYdXx){bprSiXhgcy = true;}
      else if(iCFJPTYdXx == lBBWAmXVwC){VcGMgAThsg = true;}
      if(OTWcycfCmV == lXSNKkTMHL){ukQYjtwnIp = true;}
      else if(lXSNKkTMHL == OTWcycfCmV){WsfnGoWfuI = true;}
      if(ilhFcLRlnL == AJhbpWqoPZ){RyGsaFYtSe = true;}
      else if(AJhbpWqoPZ == ilhFcLRlnL){dZhTeMzhZd = true;}
      if(IRGsAnaRBw == yZCwwbdHFI){cujJRTpUqQ = true;}
      else if(yZCwwbdHFI == IRGsAnaRBw){EMtphrDFAC = true;}
      if(piXlcwghUR == ISfyOwMJBo){ZNrQbWjObk = true;}
      if(iaUDwASuto == kofgfZTdSs){bPZJkciyrc = true;}
      if(UkhjsxNdcK == cjOxzLUWQh){znNyVzAGHP = true;}
      while(ISfyOwMJBo == piXlcwghUR){smgpRqLmIb = true;}
      while(kofgfZTdSs == kofgfZTdSs){OTylywtmgU = true;}
      while(cjOxzLUWQh == cjOxzLUWQh){AlIPcJypGN = true;}
      if(GMGzDgdiMs == true){GMGzDgdiMs = false;}
      if(JhnZoItVPW == true){JhnZoItVPW = false;}
      if(HAnMfXEhzD == true){HAnMfXEhzD = false;}
      if(bprSiXhgcy == true){bprSiXhgcy = false;}
      if(ukQYjtwnIp == true){ukQYjtwnIp = false;}
      if(RyGsaFYtSe == true){RyGsaFYtSe = false;}
      if(cujJRTpUqQ == true){cujJRTpUqQ = false;}
      if(ZNrQbWjObk == true){ZNrQbWjObk = false;}
      if(bPZJkciyrc == true){bPZJkciyrc = false;}
      if(znNyVzAGHP == true){znNyVzAGHP = false;}
      if(EbwqPEGpRD == true){EbwqPEGpRD = false;}
      if(VJRhCMVaXn == true){VJRhCMVaXn = false;}
      if(krbORlzsub == true){krbORlzsub = false;}
      if(VcGMgAThsg == true){VcGMgAThsg = false;}
      if(WsfnGoWfuI == true){WsfnGoWfuI = false;}
      if(dZhTeMzhZd == true){dZhTeMzhZd = false;}
      if(EMtphrDFAC == true){EMtphrDFAC = false;}
      if(smgpRqLmIb == true){smgpRqLmIb = false;}
      if(OTylywtmgU == true){OTylywtmgU = false;}
      if(AlIPcJypGN == true){AlIPcJypGN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPNGQECBQW
{ 
  void iAUKsRbULg()
  { 
      bool cUSEtSYCMB = false;
      bool wPdwqTizAp = false;
      bool QVziADuOeG = false;
      bool MdxqQLgDLG = false;
      bool dMNPqhFfPE = false;
      bool yXHARHUjEp = false;
      bool XKWFnRSmef = false;
      bool lemsLDIiqR = false;
      bool xPyaIoWxYJ = false;
      bool pxzUiTpHbY = false;
      bool PSAjRSkNnO = false;
      bool ylrmsILwxz = false;
      bool uUNUoofRJr = false;
      bool NAHRBeONIp = false;
      bool EIJKLEFLba = false;
      bool HsKbdtEeuc = false;
      bool lSDwBydZkO = false;
      bool synGulLDJj = false;
      bool iTpikToenG = false;
      bool ZiSeDlEMIM = false;
      string yAIdhmaOdp;
      string nHLxTFRCKF;
      string UXqiPCeEnf;
      string zGPNqEfujP;
      string FXzDfrYyZQ;
      string eVmqmaJYOe;
      string HWZxpgqxFO;
      string ZVRuAwXmDW;
      string dgeWBcTYZQ;
      string uHgFIiyCMz;
      string BarKqIEqqq;
      string CVUrBarCwM;
      string MSWnTSoMmQ;
      string yVZDVCnTfr;
      string YbgiOYloDg;
      string quGAlhEDqX;
      string TrEZsfwQVy;
      string mXWDnjknZt;
      string fAIFZCPZRm;
      string yjcHYgWHpi;
      if(yAIdhmaOdp == BarKqIEqqq){cUSEtSYCMB = true;}
      else if(BarKqIEqqq == yAIdhmaOdp){PSAjRSkNnO = true;}
      if(nHLxTFRCKF == CVUrBarCwM){wPdwqTizAp = true;}
      else if(CVUrBarCwM == nHLxTFRCKF){ylrmsILwxz = true;}
      if(UXqiPCeEnf == MSWnTSoMmQ){QVziADuOeG = true;}
      else if(MSWnTSoMmQ == UXqiPCeEnf){uUNUoofRJr = true;}
      if(zGPNqEfujP == yVZDVCnTfr){MdxqQLgDLG = true;}
      else if(yVZDVCnTfr == zGPNqEfujP){NAHRBeONIp = true;}
      if(FXzDfrYyZQ == YbgiOYloDg){dMNPqhFfPE = true;}
      else if(YbgiOYloDg == FXzDfrYyZQ){EIJKLEFLba = true;}
      if(eVmqmaJYOe == quGAlhEDqX){yXHARHUjEp = true;}
      else if(quGAlhEDqX == eVmqmaJYOe){HsKbdtEeuc = true;}
      if(HWZxpgqxFO == TrEZsfwQVy){XKWFnRSmef = true;}
      else if(TrEZsfwQVy == HWZxpgqxFO){lSDwBydZkO = true;}
      if(ZVRuAwXmDW == mXWDnjknZt){lemsLDIiqR = true;}
      if(dgeWBcTYZQ == fAIFZCPZRm){xPyaIoWxYJ = true;}
      if(uHgFIiyCMz == yjcHYgWHpi){pxzUiTpHbY = true;}
      while(mXWDnjknZt == ZVRuAwXmDW){synGulLDJj = true;}
      while(fAIFZCPZRm == fAIFZCPZRm){iTpikToenG = true;}
      while(yjcHYgWHpi == yjcHYgWHpi){ZiSeDlEMIM = true;}
      if(cUSEtSYCMB == true){cUSEtSYCMB = false;}
      if(wPdwqTizAp == true){wPdwqTizAp = false;}
      if(QVziADuOeG == true){QVziADuOeG = false;}
      if(MdxqQLgDLG == true){MdxqQLgDLG = false;}
      if(dMNPqhFfPE == true){dMNPqhFfPE = false;}
      if(yXHARHUjEp == true){yXHARHUjEp = false;}
      if(XKWFnRSmef == true){XKWFnRSmef = false;}
      if(lemsLDIiqR == true){lemsLDIiqR = false;}
      if(xPyaIoWxYJ == true){xPyaIoWxYJ = false;}
      if(pxzUiTpHbY == true){pxzUiTpHbY = false;}
      if(PSAjRSkNnO == true){PSAjRSkNnO = false;}
      if(ylrmsILwxz == true){ylrmsILwxz = false;}
      if(uUNUoofRJr == true){uUNUoofRJr = false;}
      if(NAHRBeONIp == true){NAHRBeONIp = false;}
      if(EIJKLEFLba == true){EIJKLEFLba = false;}
      if(HsKbdtEeuc == true){HsKbdtEeuc = false;}
      if(lSDwBydZkO == true){lSDwBydZkO = false;}
      if(synGulLDJj == true){synGulLDJj = false;}
      if(iTpikToenG == true){iTpikToenG = false;}
      if(ZiSeDlEMIM == true){ZiSeDlEMIM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGCNNIWWFN
{ 
  void FpXQtAqWuh()
  { 
      bool gMuasAjYHn = false;
      bool TskFiXpakH = false;
      bool WeNDhTblOd = false;
      bool LWPNVMZkFS = false;
      bool PrPtkgIIUP = false;
      bool haAHeCzqsZ = false;
      bool YyJcbxcWjV = false;
      bool yFVSrdOTRA = false;
      bool KSQywjWHhT = false;
      bool NhrfsQhmRn = false;
      bool DlYzRbFgPB = false;
      bool meZrOGhLfr = false;
      bool aVnQIPNoYa = false;
      bool ubBdwYsRgT = false;
      bool dorgfhIzQm = false;
      bool iWGYNhxHpB = false;
      bool OPInGLdwuo = false;
      bool MQeMNlcHjZ = false;
      bool HNXkrXVbPO = false;
      bool akaeFNfEaU = false;
      string nMelmEtYYH;
      string JlAqaVRGyB;
      string mAIUlHqORo;
      string GKirLWyuVc;
      string kjumrdinxO;
      string niCdlmEJzf;
      string MfGjAzDIfD;
      string WVkVPDFUcI;
      string YDQDAXIEFY;
      string SoupPFcLmr;
      string aZIsqSxfOh;
      string hjfqGIOCjc;
      string pyCGkhZuFK;
      string ZsgjhyuXMg;
      string ZbpWpiIEiH;
      string qZbJCbXBII;
      string sCZEHnCwJI;
      string NppCCNIeQC;
      string ZULySARXhF;
      string ZtOEnXCkPC;
      if(nMelmEtYYH == aZIsqSxfOh){gMuasAjYHn = true;}
      else if(aZIsqSxfOh == nMelmEtYYH){DlYzRbFgPB = true;}
      if(JlAqaVRGyB == hjfqGIOCjc){TskFiXpakH = true;}
      else if(hjfqGIOCjc == JlAqaVRGyB){meZrOGhLfr = true;}
      if(mAIUlHqORo == pyCGkhZuFK){WeNDhTblOd = true;}
      else if(pyCGkhZuFK == mAIUlHqORo){aVnQIPNoYa = true;}
      if(GKirLWyuVc == ZsgjhyuXMg){LWPNVMZkFS = true;}
      else if(ZsgjhyuXMg == GKirLWyuVc){ubBdwYsRgT = true;}
      if(kjumrdinxO == ZbpWpiIEiH){PrPtkgIIUP = true;}
      else if(ZbpWpiIEiH == kjumrdinxO){dorgfhIzQm = true;}
      if(niCdlmEJzf == qZbJCbXBII){haAHeCzqsZ = true;}
      else if(qZbJCbXBII == niCdlmEJzf){iWGYNhxHpB = true;}
      if(MfGjAzDIfD == sCZEHnCwJI){YyJcbxcWjV = true;}
      else if(sCZEHnCwJI == MfGjAzDIfD){OPInGLdwuo = true;}
      if(WVkVPDFUcI == NppCCNIeQC){yFVSrdOTRA = true;}
      if(YDQDAXIEFY == ZULySARXhF){KSQywjWHhT = true;}
      if(SoupPFcLmr == ZtOEnXCkPC){NhrfsQhmRn = true;}
      while(NppCCNIeQC == WVkVPDFUcI){MQeMNlcHjZ = true;}
      while(ZULySARXhF == ZULySARXhF){HNXkrXVbPO = true;}
      while(ZtOEnXCkPC == ZtOEnXCkPC){akaeFNfEaU = true;}
      if(gMuasAjYHn == true){gMuasAjYHn = false;}
      if(TskFiXpakH == true){TskFiXpakH = false;}
      if(WeNDhTblOd == true){WeNDhTblOd = false;}
      if(LWPNVMZkFS == true){LWPNVMZkFS = false;}
      if(PrPtkgIIUP == true){PrPtkgIIUP = false;}
      if(haAHeCzqsZ == true){haAHeCzqsZ = false;}
      if(YyJcbxcWjV == true){YyJcbxcWjV = false;}
      if(yFVSrdOTRA == true){yFVSrdOTRA = false;}
      if(KSQywjWHhT == true){KSQywjWHhT = false;}
      if(NhrfsQhmRn == true){NhrfsQhmRn = false;}
      if(DlYzRbFgPB == true){DlYzRbFgPB = false;}
      if(meZrOGhLfr == true){meZrOGhLfr = false;}
      if(aVnQIPNoYa == true){aVnQIPNoYa = false;}
      if(ubBdwYsRgT == true){ubBdwYsRgT = false;}
      if(dorgfhIzQm == true){dorgfhIzQm = false;}
      if(iWGYNhxHpB == true){iWGYNhxHpB = false;}
      if(OPInGLdwuo == true){OPInGLdwuo = false;}
      if(MQeMNlcHjZ == true){MQeMNlcHjZ = false;}
      if(HNXkrXVbPO == true){HNXkrXVbPO = false;}
      if(akaeFNfEaU == true){akaeFNfEaU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWTZCFBDNB
{ 
  void dlaogcEzCR()
  { 
      bool zWXPjFxQtJ = false;
      bool yKBlWaigTI = false;
      bool RyTaQnBwkO = false;
      bool shgQTfjLcc = false;
      bool PzTwymXuHN = false;
      bool iBxDYACwzw = false;
      bool EBffQPdkSp = false;
      bool qXEprSeXcc = false;
      bool PFnWeqkdrS = false;
      bool dmLgYNSnei = false;
      bool JmbQVKxHKG = false;
      bool UeTWfyMIAY = false;
      bool ezszMELWQd = false;
      bool zqrsTccXAT = false;
      bool tcTkxyToBa = false;
      bool AKmGEKtcDR = false;
      bool zZpfHdlZCC = false;
      bool UoHfeBfHBN = false;
      bool kVVpdoDloJ = false;
      bool iATiUTmmdT = false;
      string ZAcTPsukXY;
      string rPxtmoKrfl;
      string EpVWpUSCYP;
      string RACjxsWrpX;
      string DOutkepods;
      string FUPIuidFdu;
      string asLHHqNNwt;
      string RSCIhotblL;
      string ecXfKwktnO;
      string OQOuwKDmls;
      string QcrjamSGZG;
      string oCTSQyVexL;
      string GTZheADGLX;
      string kGostBjmEX;
      string ddTgZMxwey;
      string nXpalxDKFZ;
      string iLuCVhMaXO;
      string NiaZgczrIS;
      string DHbNiNPNGw;
      string yZheoSiQLq;
      if(ZAcTPsukXY == QcrjamSGZG){zWXPjFxQtJ = true;}
      else if(QcrjamSGZG == ZAcTPsukXY){JmbQVKxHKG = true;}
      if(rPxtmoKrfl == oCTSQyVexL){yKBlWaigTI = true;}
      else if(oCTSQyVexL == rPxtmoKrfl){UeTWfyMIAY = true;}
      if(EpVWpUSCYP == GTZheADGLX){RyTaQnBwkO = true;}
      else if(GTZheADGLX == EpVWpUSCYP){ezszMELWQd = true;}
      if(RACjxsWrpX == kGostBjmEX){shgQTfjLcc = true;}
      else if(kGostBjmEX == RACjxsWrpX){zqrsTccXAT = true;}
      if(DOutkepods == ddTgZMxwey){PzTwymXuHN = true;}
      else if(ddTgZMxwey == DOutkepods){tcTkxyToBa = true;}
      if(FUPIuidFdu == nXpalxDKFZ){iBxDYACwzw = true;}
      else if(nXpalxDKFZ == FUPIuidFdu){AKmGEKtcDR = true;}
      if(asLHHqNNwt == iLuCVhMaXO){EBffQPdkSp = true;}
      else if(iLuCVhMaXO == asLHHqNNwt){zZpfHdlZCC = true;}
      if(RSCIhotblL == NiaZgczrIS){qXEprSeXcc = true;}
      if(ecXfKwktnO == DHbNiNPNGw){PFnWeqkdrS = true;}
      if(OQOuwKDmls == yZheoSiQLq){dmLgYNSnei = true;}
      while(NiaZgczrIS == RSCIhotblL){UoHfeBfHBN = true;}
      while(DHbNiNPNGw == DHbNiNPNGw){kVVpdoDloJ = true;}
      while(yZheoSiQLq == yZheoSiQLq){iATiUTmmdT = true;}
      if(zWXPjFxQtJ == true){zWXPjFxQtJ = false;}
      if(yKBlWaigTI == true){yKBlWaigTI = false;}
      if(RyTaQnBwkO == true){RyTaQnBwkO = false;}
      if(shgQTfjLcc == true){shgQTfjLcc = false;}
      if(PzTwymXuHN == true){PzTwymXuHN = false;}
      if(iBxDYACwzw == true){iBxDYACwzw = false;}
      if(EBffQPdkSp == true){EBffQPdkSp = false;}
      if(qXEprSeXcc == true){qXEprSeXcc = false;}
      if(PFnWeqkdrS == true){PFnWeqkdrS = false;}
      if(dmLgYNSnei == true){dmLgYNSnei = false;}
      if(JmbQVKxHKG == true){JmbQVKxHKG = false;}
      if(UeTWfyMIAY == true){UeTWfyMIAY = false;}
      if(ezszMELWQd == true){ezszMELWQd = false;}
      if(zqrsTccXAT == true){zqrsTccXAT = false;}
      if(tcTkxyToBa == true){tcTkxyToBa = false;}
      if(AKmGEKtcDR == true){AKmGEKtcDR = false;}
      if(zZpfHdlZCC == true){zZpfHdlZCC = false;}
      if(UoHfeBfHBN == true){UoHfeBfHBN = false;}
      if(kVVpdoDloJ == true){kVVpdoDloJ = false;}
      if(iATiUTmmdT == true){iATiUTmmdT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCKYILFVRP
{ 
  void zTXoSRqXUy()
  { 
      bool ooQPPblEFj = false;
      bool TbTqplgfGY = false;
      bool rTRonhoWBc = false;
      bool zFAJoyBpIT = false;
      bool BfcOMiSDKz = false;
      bool UylgCVXaah = false;
      bool lPDbkNbJCr = false;
      bool kqWlWLpDcF = false;
      bool PlLBHBTSHT = false;
      bool ZZOahlcAcy = false;
      bool GIBSOcazJp = false;
      bool eUyVSADCTj = false;
      bool tICiRKbwEk = false;
      bool ipZdyGjsle = false;
      bool ZTJQnFarIg = false;
      bool hafsEyFRBD = false;
      bool BeuYHotUXL = false;
      bool PKPoJZzltL = false;
      bool jimWDIJgYz = false;
      bool ASqhcuYkJz = false;
      string nWetmxuLrl;
      string bhpehfwPQt;
      string ZniPQzLjGS;
      string YXkrbzAkqx;
      string YQsPdHCCaD;
      string UddfRznPcm;
      string kKFZNExxDh;
      string eLXSVIuTlI;
      string wIJDxtsEab;
      string LkHELNLSCY;
      string KEzrXIGLKI;
      string ETdUpcBCbS;
      string LrWaVtETHH;
      string xbRMyrJQeo;
      string nhtRWqGmNi;
      string MJqiNRgXVd;
      string DmDCLcCQVy;
      string TjWldcyFEe;
      string nRFXumkhzf;
      string KluAkBdrFt;
      if(nWetmxuLrl == KEzrXIGLKI){ooQPPblEFj = true;}
      else if(KEzrXIGLKI == nWetmxuLrl){GIBSOcazJp = true;}
      if(bhpehfwPQt == ETdUpcBCbS){TbTqplgfGY = true;}
      else if(ETdUpcBCbS == bhpehfwPQt){eUyVSADCTj = true;}
      if(ZniPQzLjGS == LrWaVtETHH){rTRonhoWBc = true;}
      else if(LrWaVtETHH == ZniPQzLjGS){tICiRKbwEk = true;}
      if(YXkrbzAkqx == xbRMyrJQeo){zFAJoyBpIT = true;}
      else if(xbRMyrJQeo == YXkrbzAkqx){ipZdyGjsle = true;}
      if(YQsPdHCCaD == nhtRWqGmNi){BfcOMiSDKz = true;}
      else if(nhtRWqGmNi == YQsPdHCCaD){ZTJQnFarIg = true;}
      if(UddfRznPcm == MJqiNRgXVd){UylgCVXaah = true;}
      else if(MJqiNRgXVd == UddfRznPcm){hafsEyFRBD = true;}
      if(kKFZNExxDh == DmDCLcCQVy){lPDbkNbJCr = true;}
      else if(DmDCLcCQVy == kKFZNExxDh){BeuYHotUXL = true;}
      if(eLXSVIuTlI == TjWldcyFEe){kqWlWLpDcF = true;}
      if(wIJDxtsEab == nRFXumkhzf){PlLBHBTSHT = true;}
      if(LkHELNLSCY == KluAkBdrFt){ZZOahlcAcy = true;}
      while(TjWldcyFEe == eLXSVIuTlI){PKPoJZzltL = true;}
      while(nRFXumkhzf == nRFXumkhzf){jimWDIJgYz = true;}
      while(KluAkBdrFt == KluAkBdrFt){ASqhcuYkJz = true;}
      if(ooQPPblEFj == true){ooQPPblEFj = false;}
      if(TbTqplgfGY == true){TbTqplgfGY = false;}
      if(rTRonhoWBc == true){rTRonhoWBc = false;}
      if(zFAJoyBpIT == true){zFAJoyBpIT = false;}
      if(BfcOMiSDKz == true){BfcOMiSDKz = false;}
      if(UylgCVXaah == true){UylgCVXaah = false;}
      if(lPDbkNbJCr == true){lPDbkNbJCr = false;}
      if(kqWlWLpDcF == true){kqWlWLpDcF = false;}
      if(PlLBHBTSHT == true){PlLBHBTSHT = false;}
      if(ZZOahlcAcy == true){ZZOahlcAcy = false;}
      if(GIBSOcazJp == true){GIBSOcazJp = false;}
      if(eUyVSADCTj == true){eUyVSADCTj = false;}
      if(tICiRKbwEk == true){tICiRKbwEk = false;}
      if(ipZdyGjsle == true){ipZdyGjsle = false;}
      if(ZTJQnFarIg == true){ZTJQnFarIg = false;}
      if(hafsEyFRBD == true){hafsEyFRBD = false;}
      if(BeuYHotUXL == true){BeuYHotUXL = false;}
      if(PKPoJZzltL == true){PKPoJZzltL = false;}
      if(jimWDIJgYz == true){jimWDIJgYz = false;}
      if(ASqhcuYkJz == true){ASqhcuYkJz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHRGHATSGI
{ 
  void RsmUjgpSHw()
  { 
      bool NFZsJApBFF = false;
      bool nsQaDkrOOM = false;
      bool EzoUlRRIYR = false;
      bool SRgVxHniRA = false;
      bool KbfbXBtRif = false;
      bool yZokNOPFGq = false;
      bool hgcmmVMucu = false;
      bool xJxOCbSNxk = false;
      bool XAZrTrcuHi = false;
      bool qibZRczsnB = false;
      bool nynmincaik = false;
      bool uCHUThHjTu = false;
      bool sQmtDNgWwY = false;
      bool bZYuwZMlIe = false;
      bool OBLVmobGGj = false;
      bool VOYsIXKsiV = false;
      bool HGeKJVcLYt = false;
      bool VUaofqFQGO = false;
      bool kZPLDMAemY = false;
      bool OSCmXIWBMR = false;
      string CsZmcsgRon;
      string zOfbBuRfZW;
      string PYXNLxrRGp;
      string iedeiGIlEf;
      string NtAnSmPkqu;
      string BzxiUdVMbf;
      string AOKyETkBst;
      string mfbsIVYjtY;
      string gHaLojhtKF;
      string juJYfyjBiz;
      string BOrwIVXDZz;
      string FlRDzsnyJU;
      string lqpmJqVCNK;
      string kWAuWRPdDS;
      string LeTLAycGZm;
      string JkrOMKXElQ;
      string AUoPNhkWgg;
      string cJuqIHWemK;
      string NObaAAdlhL;
      string tLrlRqoEyR;
      if(CsZmcsgRon == BOrwIVXDZz){NFZsJApBFF = true;}
      else if(BOrwIVXDZz == CsZmcsgRon){nynmincaik = true;}
      if(zOfbBuRfZW == FlRDzsnyJU){nsQaDkrOOM = true;}
      else if(FlRDzsnyJU == zOfbBuRfZW){uCHUThHjTu = true;}
      if(PYXNLxrRGp == lqpmJqVCNK){EzoUlRRIYR = true;}
      else if(lqpmJqVCNK == PYXNLxrRGp){sQmtDNgWwY = true;}
      if(iedeiGIlEf == kWAuWRPdDS){SRgVxHniRA = true;}
      else if(kWAuWRPdDS == iedeiGIlEf){bZYuwZMlIe = true;}
      if(NtAnSmPkqu == LeTLAycGZm){KbfbXBtRif = true;}
      else if(LeTLAycGZm == NtAnSmPkqu){OBLVmobGGj = true;}
      if(BzxiUdVMbf == JkrOMKXElQ){yZokNOPFGq = true;}
      else if(JkrOMKXElQ == BzxiUdVMbf){VOYsIXKsiV = true;}
      if(AOKyETkBst == AUoPNhkWgg){hgcmmVMucu = true;}
      else if(AUoPNhkWgg == AOKyETkBst){HGeKJVcLYt = true;}
      if(mfbsIVYjtY == cJuqIHWemK){xJxOCbSNxk = true;}
      if(gHaLojhtKF == NObaAAdlhL){XAZrTrcuHi = true;}
      if(juJYfyjBiz == tLrlRqoEyR){qibZRczsnB = true;}
      while(cJuqIHWemK == mfbsIVYjtY){VUaofqFQGO = true;}
      while(NObaAAdlhL == NObaAAdlhL){kZPLDMAemY = true;}
      while(tLrlRqoEyR == tLrlRqoEyR){OSCmXIWBMR = true;}
      if(NFZsJApBFF == true){NFZsJApBFF = false;}
      if(nsQaDkrOOM == true){nsQaDkrOOM = false;}
      if(EzoUlRRIYR == true){EzoUlRRIYR = false;}
      if(SRgVxHniRA == true){SRgVxHniRA = false;}
      if(KbfbXBtRif == true){KbfbXBtRif = false;}
      if(yZokNOPFGq == true){yZokNOPFGq = false;}
      if(hgcmmVMucu == true){hgcmmVMucu = false;}
      if(xJxOCbSNxk == true){xJxOCbSNxk = false;}
      if(XAZrTrcuHi == true){XAZrTrcuHi = false;}
      if(qibZRczsnB == true){qibZRczsnB = false;}
      if(nynmincaik == true){nynmincaik = false;}
      if(uCHUThHjTu == true){uCHUThHjTu = false;}
      if(sQmtDNgWwY == true){sQmtDNgWwY = false;}
      if(bZYuwZMlIe == true){bZYuwZMlIe = false;}
      if(OBLVmobGGj == true){OBLVmobGGj = false;}
      if(VOYsIXKsiV == true){VOYsIXKsiV = false;}
      if(HGeKJVcLYt == true){HGeKJVcLYt = false;}
      if(VUaofqFQGO == true){VUaofqFQGO = false;}
      if(kZPLDMAemY == true){kZPLDMAemY = false;}
      if(OSCmXIWBMR == true){OSCmXIWBMR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKURWYRZFY
{ 
  void PfKxVGAZYH()
  { 
      bool WPHYREmrQT = false;
      bool bwKNiuDHAF = false;
      bool TAqbZIqIib = false;
      bool msKqbjIGuj = false;
      bool VCPWcHspPh = false;
      bool HXTmlWYfzJ = false;
      bool NdIngikTlz = false;
      bool mxMPiRjTzR = false;
      bool OArAUPZXEF = false;
      bool LbHkWqsbps = false;
      bool VZEQuKLDDT = false;
      bool mEfguMlHTR = false;
      bool JNOfmKoasr = false;
      bool YHdFuowbFK = false;
      bool EVTkSHuapJ = false;
      bool FkIXjIKXck = false;
      bool UjJLueZakG = false;
      bool QJCJNmsdNf = false;
      bool OOjjlmzFUm = false;
      bool dXzUoTLIon = false;
      string fnXbLhOEzl;
      string MwMzcKYySR;
      string YPBbpNSSAs;
      string sbebyGEDgU;
      string KmMeqfxckl;
      string mgMmCQmwly;
      string PuDGsjQkAV;
      string FVQxGlDVjJ;
      string QogOFLPrYh;
      string TIQiFPiFlG;
      string OMbPfQQOgQ;
      string MQLbgZNoBh;
      string TYLSCxFgrq;
      string CyjduENRho;
      string tBKHUDxoBe;
      string BsEDmpAIMi;
      string LiVpOOfhgc;
      string MwGMmSNEyy;
      string zQeNoItfqE;
      string DEEycLfUsG;
      if(fnXbLhOEzl == OMbPfQQOgQ){WPHYREmrQT = true;}
      else if(OMbPfQQOgQ == fnXbLhOEzl){VZEQuKLDDT = true;}
      if(MwMzcKYySR == MQLbgZNoBh){bwKNiuDHAF = true;}
      else if(MQLbgZNoBh == MwMzcKYySR){mEfguMlHTR = true;}
      if(YPBbpNSSAs == TYLSCxFgrq){TAqbZIqIib = true;}
      else if(TYLSCxFgrq == YPBbpNSSAs){JNOfmKoasr = true;}
      if(sbebyGEDgU == CyjduENRho){msKqbjIGuj = true;}
      else if(CyjduENRho == sbebyGEDgU){YHdFuowbFK = true;}
      if(KmMeqfxckl == tBKHUDxoBe){VCPWcHspPh = true;}
      else if(tBKHUDxoBe == KmMeqfxckl){EVTkSHuapJ = true;}
      if(mgMmCQmwly == BsEDmpAIMi){HXTmlWYfzJ = true;}
      else if(BsEDmpAIMi == mgMmCQmwly){FkIXjIKXck = true;}
      if(PuDGsjQkAV == LiVpOOfhgc){NdIngikTlz = true;}
      else if(LiVpOOfhgc == PuDGsjQkAV){UjJLueZakG = true;}
      if(FVQxGlDVjJ == MwGMmSNEyy){mxMPiRjTzR = true;}
      if(QogOFLPrYh == zQeNoItfqE){OArAUPZXEF = true;}
      if(TIQiFPiFlG == DEEycLfUsG){LbHkWqsbps = true;}
      while(MwGMmSNEyy == FVQxGlDVjJ){QJCJNmsdNf = true;}
      while(zQeNoItfqE == zQeNoItfqE){OOjjlmzFUm = true;}
      while(DEEycLfUsG == DEEycLfUsG){dXzUoTLIon = true;}
      if(WPHYREmrQT == true){WPHYREmrQT = false;}
      if(bwKNiuDHAF == true){bwKNiuDHAF = false;}
      if(TAqbZIqIib == true){TAqbZIqIib = false;}
      if(msKqbjIGuj == true){msKqbjIGuj = false;}
      if(VCPWcHspPh == true){VCPWcHspPh = false;}
      if(HXTmlWYfzJ == true){HXTmlWYfzJ = false;}
      if(NdIngikTlz == true){NdIngikTlz = false;}
      if(mxMPiRjTzR == true){mxMPiRjTzR = false;}
      if(OArAUPZXEF == true){OArAUPZXEF = false;}
      if(LbHkWqsbps == true){LbHkWqsbps = false;}
      if(VZEQuKLDDT == true){VZEQuKLDDT = false;}
      if(mEfguMlHTR == true){mEfguMlHTR = false;}
      if(JNOfmKoasr == true){JNOfmKoasr = false;}
      if(YHdFuowbFK == true){YHdFuowbFK = false;}
      if(EVTkSHuapJ == true){EVTkSHuapJ = false;}
      if(FkIXjIKXck == true){FkIXjIKXck = false;}
      if(UjJLueZakG == true){UjJLueZakG = false;}
      if(QJCJNmsdNf == true){QJCJNmsdNf = false;}
      if(OOjjlmzFUm == true){OOjjlmzFUm = false;}
      if(dXzUoTLIon == true){dXzUoTLIon = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNMMZFYEQU
{ 
  void JLhJJLScZd()
  { 
      bool MZXYjadYYV = false;
      bool ujuZFhEHHP = false;
      bool awCzoIzkuG = false;
      bool LrMOmswPXt = false;
      bool XzQbNTGNZi = false;
      bool DHBsSPWXjb = false;
      bool bsdRKCWfmL = false;
      bool koiNqbfalU = false;
      bool CkKLDDpTwW = false;
      bool WXewSeUzQK = false;
      bool xZaNyOXnBp = false;
      bool jwlOZphSOH = false;
      bool LCjPoMJmtM = false;
      bool HfKaXbKwNn = false;
      bool eCRFmZlPVc = false;
      bool wCjJztpKYk = false;
      bool FktoiDlKqy = false;
      bool ekEabJkecP = false;
      bool asRRPFuAbc = false;
      bool kAXcitIbVi = false;
      string mwxTKPRFTj;
      string ksDCddpDIy;
      string czyEPyhdJQ;
      string VgGSsNOxes;
      string BNVRHYmSpj;
      string uWiIdnxrEM;
      string gnwCOEmkJQ;
      string PrXPwOcgxq;
      string KPmZVyyyoF;
      string QVrSLNRSDC;
      string kBJZTCySLO;
      string KQuNBQAWgP;
      string FnwEztzFDi;
      string xKdtFJGNFT;
      string AelZtzZeQu;
      string NulmwxFEZZ;
      string CrPcRzmAHr;
      string KmQMOaBVJz;
      string TTnIUBYpxI;
      string DBmfRHPJIt;
      if(mwxTKPRFTj == kBJZTCySLO){MZXYjadYYV = true;}
      else if(kBJZTCySLO == mwxTKPRFTj){xZaNyOXnBp = true;}
      if(ksDCddpDIy == KQuNBQAWgP){ujuZFhEHHP = true;}
      else if(KQuNBQAWgP == ksDCddpDIy){jwlOZphSOH = true;}
      if(czyEPyhdJQ == FnwEztzFDi){awCzoIzkuG = true;}
      else if(FnwEztzFDi == czyEPyhdJQ){LCjPoMJmtM = true;}
      if(VgGSsNOxes == xKdtFJGNFT){LrMOmswPXt = true;}
      else if(xKdtFJGNFT == VgGSsNOxes){HfKaXbKwNn = true;}
      if(BNVRHYmSpj == AelZtzZeQu){XzQbNTGNZi = true;}
      else if(AelZtzZeQu == BNVRHYmSpj){eCRFmZlPVc = true;}
      if(uWiIdnxrEM == NulmwxFEZZ){DHBsSPWXjb = true;}
      else if(NulmwxFEZZ == uWiIdnxrEM){wCjJztpKYk = true;}
      if(gnwCOEmkJQ == CrPcRzmAHr){bsdRKCWfmL = true;}
      else if(CrPcRzmAHr == gnwCOEmkJQ){FktoiDlKqy = true;}
      if(PrXPwOcgxq == KmQMOaBVJz){koiNqbfalU = true;}
      if(KPmZVyyyoF == TTnIUBYpxI){CkKLDDpTwW = true;}
      if(QVrSLNRSDC == DBmfRHPJIt){WXewSeUzQK = true;}
      while(KmQMOaBVJz == PrXPwOcgxq){ekEabJkecP = true;}
      while(TTnIUBYpxI == TTnIUBYpxI){asRRPFuAbc = true;}
      while(DBmfRHPJIt == DBmfRHPJIt){kAXcitIbVi = true;}
      if(MZXYjadYYV == true){MZXYjadYYV = false;}
      if(ujuZFhEHHP == true){ujuZFhEHHP = false;}
      if(awCzoIzkuG == true){awCzoIzkuG = false;}
      if(LrMOmswPXt == true){LrMOmswPXt = false;}
      if(XzQbNTGNZi == true){XzQbNTGNZi = false;}
      if(DHBsSPWXjb == true){DHBsSPWXjb = false;}
      if(bsdRKCWfmL == true){bsdRKCWfmL = false;}
      if(koiNqbfalU == true){koiNqbfalU = false;}
      if(CkKLDDpTwW == true){CkKLDDpTwW = false;}
      if(WXewSeUzQK == true){WXewSeUzQK = false;}
      if(xZaNyOXnBp == true){xZaNyOXnBp = false;}
      if(jwlOZphSOH == true){jwlOZphSOH = false;}
      if(LCjPoMJmtM == true){LCjPoMJmtM = false;}
      if(HfKaXbKwNn == true){HfKaXbKwNn = false;}
      if(eCRFmZlPVc == true){eCRFmZlPVc = false;}
      if(wCjJztpKYk == true){wCjJztpKYk = false;}
      if(FktoiDlKqy == true){FktoiDlKqy = false;}
      if(ekEabJkecP == true){ekEabJkecP = false;}
      if(asRRPFuAbc == true){asRRPFuAbc = false;}
      if(kAXcitIbVi == true){kAXcitIbVi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHSGKJORVY
{ 
  void QpABeOhsFD()
  { 
      bool PpxHNMswca = false;
      bool MxUaaunCRJ = false;
      bool bZHeqyiLDy = false;
      bool XuzOwTozXI = false;
      bool yJoagJRVSE = false;
      bool NftcFpiSQO = false;
      bool cgseDRxGdH = false;
      bool GneJKSkfxg = false;
      bool gNrzkqAWJG = false;
      bool kViIfQPKXP = false;
      bool MLrLxYBkRm = false;
      bool ECUihPotsL = false;
      bool QZwWVjFWdt = false;
      bool CZIhUVUgBL = false;
      bool pPEWCiBAZP = false;
      bool bVQLylOVoN = false;
      bool TdHXjdslOM = false;
      bool tHshUBVYUm = false;
      bool hFwNRgJwih = false;
      bool GzqmrLIflX = false;
      string GbIIAmjojY;
      string RjDonjDmjp;
      string XeJWeNSZcd;
      string TtZycRemgJ;
      string TwpifmNmfB;
      string GNzXSbRkdm;
      string UKMGEWKFLV;
      string EQFZWaoaqq;
      string zetbWFuBeB;
      string ztIsoIjidI;
      string cIaJwpIYBr;
      string mpsmnoQkjz;
      string bIZKVKIMkN;
      string qFxiOpDjeg;
      string xVAmOJAVFz;
      string rzzegUiQmk;
      string gunmBgsKYy;
      string kfFCBFHluM;
      string KlHkUqFSCs;
      string GmwtzChMlg;
      if(GbIIAmjojY == cIaJwpIYBr){PpxHNMswca = true;}
      else if(cIaJwpIYBr == GbIIAmjojY){MLrLxYBkRm = true;}
      if(RjDonjDmjp == mpsmnoQkjz){MxUaaunCRJ = true;}
      else if(mpsmnoQkjz == RjDonjDmjp){ECUihPotsL = true;}
      if(XeJWeNSZcd == bIZKVKIMkN){bZHeqyiLDy = true;}
      else if(bIZKVKIMkN == XeJWeNSZcd){QZwWVjFWdt = true;}
      if(TtZycRemgJ == qFxiOpDjeg){XuzOwTozXI = true;}
      else if(qFxiOpDjeg == TtZycRemgJ){CZIhUVUgBL = true;}
      if(TwpifmNmfB == xVAmOJAVFz){yJoagJRVSE = true;}
      else if(xVAmOJAVFz == TwpifmNmfB){pPEWCiBAZP = true;}
      if(GNzXSbRkdm == rzzegUiQmk){NftcFpiSQO = true;}
      else if(rzzegUiQmk == GNzXSbRkdm){bVQLylOVoN = true;}
      if(UKMGEWKFLV == gunmBgsKYy){cgseDRxGdH = true;}
      else if(gunmBgsKYy == UKMGEWKFLV){TdHXjdslOM = true;}
      if(EQFZWaoaqq == kfFCBFHluM){GneJKSkfxg = true;}
      if(zetbWFuBeB == KlHkUqFSCs){gNrzkqAWJG = true;}
      if(ztIsoIjidI == GmwtzChMlg){kViIfQPKXP = true;}
      while(kfFCBFHluM == EQFZWaoaqq){tHshUBVYUm = true;}
      while(KlHkUqFSCs == KlHkUqFSCs){hFwNRgJwih = true;}
      while(GmwtzChMlg == GmwtzChMlg){GzqmrLIflX = true;}
      if(PpxHNMswca == true){PpxHNMswca = false;}
      if(MxUaaunCRJ == true){MxUaaunCRJ = false;}
      if(bZHeqyiLDy == true){bZHeqyiLDy = false;}
      if(XuzOwTozXI == true){XuzOwTozXI = false;}
      if(yJoagJRVSE == true){yJoagJRVSE = false;}
      if(NftcFpiSQO == true){NftcFpiSQO = false;}
      if(cgseDRxGdH == true){cgseDRxGdH = false;}
      if(GneJKSkfxg == true){GneJKSkfxg = false;}
      if(gNrzkqAWJG == true){gNrzkqAWJG = false;}
      if(kViIfQPKXP == true){kViIfQPKXP = false;}
      if(MLrLxYBkRm == true){MLrLxYBkRm = false;}
      if(ECUihPotsL == true){ECUihPotsL = false;}
      if(QZwWVjFWdt == true){QZwWVjFWdt = false;}
      if(CZIhUVUgBL == true){CZIhUVUgBL = false;}
      if(pPEWCiBAZP == true){pPEWCiBAZP = false;}
      if(bVQLylOVoN == true){bVQLylOVoN = false;}
      if(TdHXjdslOM == true){TdHXjdslOM = false;}
      if(tHshUBVYUm == true){tHshUBVYUm = false;}
      if(hFwNRgJwih == true){hFwNRgJwih = false;}
      if(GzqmrLIflX == true){GzqmrLIflX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAWEAQTILU
{ 
  void OUkqfyYFQH()
  { 
      bool bdiPVhbCRA = false;
      bool VsezelicUo = false;
      bool DeHUHXEAAg = false;
      bool yFoonMGfTM = false;
      bool YAaCWwsmiK = false;
      bool nHpbgxVNIy = false;
      bool caBjCPDoKR = false;
      bool eCJIPDDFxK = false;
      bool dQRpsqPNIq = false;
      bool qrWViyzqAG = false;
      bool sDbQekygLd = false;
      bool sPQyTLJLqK = false;
      bool ApgTZmfmYR = false;
      bool EMEqRZnAKH = false;
      bool riBexabYBX = false;
      bool omzoGDWIqq = false;
      bool FKHsYgLZfs = false;
      bool WIAiSQnCWz = false;
      bool LGkBcQMPjN = false;
      bool DfJSCgaIFQ = false;
      string hmJAPTBofi;
      string SjIDRRaERo;
      string GzLzsWrUFZ;
      string nBhEjNyysS;
      string AYaVngRqjU;
      string oyXXPhbKGr;
      string afiGuQBDTD;
      string TcKyngXoLM;
      string EBkkkocJoB;
      string lnqBqUoUaX;
      string eOXgBMnZih;
      string JlztmZuyVF;
      string mrORQekJGT;
      string qCOmgpdDiX;
      string BDaHqAowNR;
      string ZqzVjmAFQV;
      string adSPpGXLNx;
      string wqOxEiQGZQ;
      string pouotACrDs;
      string pYmNwWkKQk;
      if(hmJAPTBofi == eOXgBMnZih){bdiPVhbCRA = true;}
      else if(eOXgBMnZih == hmJAPTBofi){sDbQekygLd = true;}
      if(SjIDRRaERo == JlztmZuyVF){VsezelicUo = true;}
      else if(JlztmZuyVF == SjIDRRaERo){sPQyTLJLqK = true;}
      if(GzLzsWrUFZ == mrORQekJGT){DeHUHXEAAg = true;}
      else if(mrORQekJGT == GzLzsWrUFZ){ApgTZmfmYR = true;}
      if(nBhEjNyysS == qCOmgpdDiX){yFoonMGfTM = true;}
      else if(qCOmgpdDiX == nBhEjNyysS){EMEqRZnAKH = true;}
      if(AYaVngRqjU == BDaHqAowNR){YAaCWwsmiK = true;}
      else if(BDaHqAowNR == AYaVngRqjU){riBexabYBX = true;}
      if(oyXXPhbKGr == ZqzVjmAFQV){nHpbgxVNIy = true;}
      else if(ZqzVjmAFQV == oyXXPhbKGr){omzoGDWIqq = true;}
      if(afiGuQBDTD == adSPpGXLNx){caBjCPDoKR = true;}
      else if(adSPpGXLNx == afiGuQBDTD){FKHsYgLZfs = true;}
      if(TcKyngXoLM == wqOxEiQGZQ){eCJIPDDFxK = true;}
      if(EBkkkocJoB == pouotACrDs){dQRpsqPNIq = true;}
      if(lnqBqUoUaX == pYmNwWkKQk){qrWViyzqAG = true;}
      while(wqOxEiQGZQ == TcKyngXoLM){WIAiSQnCWz = true;}
      while(pouotACrDs == pouotACrDs){LGkBcQMPjN = true;}
      while(pYmNwWkKQk == pYmNwWkKQk){DfJSCgaIFQ = true;}
      if(bdiPVhbCRA == true){bdiPVhbCRA = false;}
      if(VsezelicUo == true){VsezelicUo = false;}
      if(DeHUHXEAAg == true){DeHUHXEAAg = false;}
      if(yFoonMGfTM == true){yFoonMGfTM = false;}
      if(YAaCWwsmiK == true){YAaCWwsmiK = false;}
      if(nHpbgxVNIy == true){nHpbgxVNIy = false;}
      if(caBjCPDoKR == true){caBjCPDoKR = false;}
      if(eCJIPDDFxK == true){eCJIPDDFxK = false;}
      if(dQRpsqPNIq == true){dQRpsqPNIq = false;}
      if(qrWViyzqAG == true){qrWViyzqAG = false;}
      if(sDbQekygLd == true){sDbQekygLd = false;}
      if(sPQyTLJLqK == true){sPQyTLJLqK = false;}
      if(ApgTZmfmYR == true){ApgTZmfmYR = false;}
      if(EMEqRZnAKH == true){EMEqRZnAKH = false;}
      if(riBexabYBX == true){riBexabYBX = false;}
      if(omzoGDWIqq == true){omzoGDWIqq = false;}
      if(FKHsYgLZfs == true){FKHsYgLZfs = false;}
      if(WIAiSQnCWz == true){WIAiSQnCWz = false;}
      if(LGkBcQMPjN == true){LGkBcQMPjN = false;}
      if(DfJSCgaIFQ == true){DfJSCgaIFQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSQMCDCXAT
{ 
  void UqjDifFgrl()
  { 
      bool psVHHZtlNp = false;
      bool HdAULerPEW = false;
      bool PKzxKMslYc = false;
      bool EeuXrDwtSc = false;
      bool aSVjbwrWdU = false;
      bool NJfbWesXwu = false;
      bool gINjkbibcI = false;
      bool ixxauxnPUN = false;
      bool UWIDPuzSBM = false;
      bool JXxWwSFlyz = false;
      bool NPtUlQLEfY = false;
      bool qdDiaKzJUp = false;
      bool cPZPyLzaec = false;
      bool qCQUAEbmRy = false;
      bool itmcVeTOul = false;
      bool SwQHWxodWZ = false;
      bool QkZChnMhhW = false;
      bool hMrVGicxtS = false;
      bool qjerKukJyC = false;
      bool PxQqhyUjug = false;
      string nDugiSJtWX;
      string dZVhfShzcr;
      string iIPQBlYPxn;
      string BmxEWAQWZQ;
      string ksNCGLboAZ;
      string bMqeaendew;
      string stxhWqcQKe;
      string CLYLGouMKp;
      string KiOWMnuRdr;
      string MlqdXqwefP;
      string hLeUXQneXk;
      string jbTokJeZUi;
      string uKlSSPTtnP;
      string rPgtHzEtyw;
      string zQtrHkSCsN;
      string LWKxUXYLCI;
      string wsqIsUtYgk;
      string FkbYidQtKh;
      string wRBaDVEjZj;
      string asqoAFZkzl;
      if(nDugiSJtWX == hLeUXQneXk){psVHHZtlNp = true;}
      else if(hLeUXQneXk == nDugiSJtWX){NPtUlQLEfY = true;}
      if(dZVhfShzcr == jbTokJeZUi){HdAULerPEW = true;}
      else if(jbTokJeZUi == dZVhfShzcr){qdDiaKzJUp = true;}
      if(iIPQBlYPxn == uKlSSPTtnP){PKzxKMslYc = true;}
      else if(uKlSSPTtnP == iIPQBlYPxn){cPZPyLzaec = true;}
      if(BmxEWAQWZQ == rPgtHzEtyw){EeuXrDwtSc = true;}
      else if(rPgtHzEtyw == BmxEWAQWZQ){qCQUAEbmRy = true;}
      if(ksNCGLboAZ == zQtrHkSCsN){aSVjbwrWdU = true;}
      else if(zQtrHkSCsN == ksNCGLboAZ){itmcVeTOul = true;}
      if(bMqeaendew == LWKxUXYLCI){NJfbWesXwu = true;}
      else if(LWKxUXYLCI == bMqeaendew){SwQHWxodWZ = true;}
      if(stxhWqcQKe == wsqIsUtYgk){gINjkbibcI = true;}
      else if(wsqIsUtYgk == stxhWqcQKe){QkZChnMhhW = true;}
      if(CLYLGouMKp == FkbYidQtKh){ixxauxnPUN = true;}
      if(KiOWMnuRdr == wRBaDVEjZj){UWIDPuzSBM = true;}
      if(MlqdXqwefP == asqoAFZkzl){JXxWwSFlyz = true;}
      while(FkbYidQtKh == CLYLGouMKp){hMrVGicxtS = true;}
      while(wRBaDVEjZj == wRBaDVEjZj){qjerKukJyC = true;}
      while(asqoAFZkzl == asqoAFZkzl){PxQqhyUjug = true;}
      if(psVHHZtlNp == true){psVHHZtlNp = false;}
      if(HdAULerPEW == true){HdAULerPEW = false;}
      if(PKzxKMslYc == true){PKzxKMslYc = false;}
      if(EeuXrDwtSc == true){EeuXrDwtSc = false;}
      if(aSVjbwrWdU == true){aSVjbwrWdU = false;}
      if(NJfbWesXwu == true){NJfbWesXwu = false;}
      if(gINjkbibcI == true){gINjkbibcI = false;}
      if(ixxauxnPUN == true){ixxauxnPUN = false;}
      if(UWIDPuzSBM == true){UWIDPuzSBM = false;}
      if(JXxWwSFlyz == true){JXxWwSFlyz = false;}
      if(NPtUlQLEfY == true){NPtUlQLEfY = false;}
      if(qdDiaKzJUp == true){qdDiaKzJUp = false;}
      if(cPZPyLzaec == true){cPZPyLzaec = false;}
      if(qCQUAEbmRy == true){qCQUAEbmRy = false;}
      if(itmcVeTOul == true){itmcVeTOul = false;}
      if(SwQHWxodWZ == true){SwQHWxodWZ = false;}
      if(QkZChnMhhW == true){QkZChnMhhW = false;}
      if(hMrVGicxtS == true){hMrVGicxtS = false;}
      if(qjerKukJyC == true){qjerKukJyC = false;}
      if(PxQqhyUjug == true){PxQqhyUjug = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVJCEQWHXT
{ 
  void kgxwNEoOqp()
  { 
      bool cdedIGEHoy = false;
      bool CcVeOOBYyM = false;
      bool pMpuHICZuA = false;
      bool YBwUygrsHw = false;
      bool gfhjWDucrP = false;
      bool bAWYtPmiVz = false;
      bool EdMnZBfBgg = false;
      bool WIQBfKeFYD = false;
      bool NYhfXXeXZh = false;
      bool tIXIrCTsKV = false;
      bool XswKrTiUrj = false;
      bool kgKSlewgQB = false;
      bool WIaymOjIJd = false;
      bool pkuDfTbWmD = false;
      bool nJeoxMyFWM = false;
      bool FmcIzOSyWd = false;
      bool iaLOsAkHlR = false;
      bool DYsNNMckAa = false;
      bool PelwXDHlDQ = false;
      bool BdAITNyPux = false;
      string VMRMdgZOqV;
      string OaTmjazrNz;
      string EetVaZWlfb;
      string VukuEGEGDL;
      string ihmCdICfYK;
      string BDpoppSwlE;
      string JniPASpXic;
      string WrnBQVrrqR;
      string WpMUZREwEN;
      string nIUzCtzWBL;
      string SexwnJOoYU;
      string yaFTgTbNph;
      string OtSUoNXozV;
      string WUpfyrsPgQ;
      string DPWjONDARh;
      string SkgTwYLbHZ;
      string lYpCydjYUn;
      string ZLgZeyWiFb;
      string KWWQDkmWiZ;
      string gQIGddZUlk;
      if(VMRMdgZOqV == SexwnJOoYU){cdedIGEHoy = true;}
      else if(SexwnJOoYU == VMRMdgZOqV){XswKrTiUrj = true;}
      if(OaTmjazrNz == yaFTgTbNph){CcVeOOBYyM = true;}
      else if(yaFTgTbNph == OaTmjazrNz){kgKSlewgQB = true;}
      if(EetVaZWlfb == OtSUoNXozV){pMpuHICZuA = true;}
      else if(OtSUoNXozV == EetVaZWlfb){WIaymOjIJd = true;}
      if(VukuEGEGDL == WUpfyrsPgQ){YBwUygrsHw = true;}
      else if(WUpfyrsPgQ == VukuEGEGDL){pkuDfTbWmD = true;}
      if(ihmCdICfYK == DPWjONDARh){gfhjWDucrP = true;}
      else if(DPWjONDARh == ihmCdICfYK){nJeoxMyFWM = true;}
      if(BDpoppSwlE == SkgTwYLbHZ){bAWYtPmiVz = true;}
      else if(SkgTwYLbHZ == BDpoppSwlE){FmcIzOSyWd = true;}
      if(JniPASpXic == lYpCydjYUn){EdMnZBfBgg = true;}
      else if(lYpCydjYUn == JniPASpXic){iaLOsAkHlR = true;}
      if(WrnBQVrrqR == ZLgZeyWiFb){WIQBfKeFYD = true;}
      if(WpMUZREwEN == KWWQDkmWiZ){NYhfXXeXZh = true;}
      if(nIUzCtzWBL == gQIGddZUlk){tIXIrCTsKV = true;}
      while(ZLgZeyWiFb == WrnBQVrrqR){DYsNNMckAa = true;}
      while(KWWQDkmWiZ == KWWQDkmWiZ){PelwXDHlDQ = true;}
      while(gQIGddZUlk == gQIGddZUlk){BdAITNyPux = true;}
      if(cdedIGEHoy == true){cdedIGEHoy = false;}
      if(CcVeOOBYyM == true){CcVeOOBYyM = false;}
      if(pMpuHICZuA == true){pMpuHICZuA = false;}
      if(YBwUygrsHw == true){YBwUygrsHw = false;}
      if(gfhjWDucrP == true){gfhjWDucrP = false;}
      if(bAWYtPmiVz == true){bAWYtPmiVz = false;}
      if(EdMnZBfBgg == true){EdMnZBfBgg = false;}
      if(WIQBfKeFYD == true){WIQBfKeFYD = false;}
      if(NYhfXXeXZh == true){NYhfXXeXZh = false;}
      if(tIXIrCTsKV == true){tIXIrCTsKV = false;}
      if(XswKrTiUrj == true){XswKrTiUrj = false;}
      if(kgKSlewgQB == true){kgKSlewgQB = false;}
      if(WIaymOjIJd == true){WIaymOjIJd = false;}
      if(pkuDfTbWmD == true){pkuDfTbWmD = false;}
      if(nJeoxMyFWM == true){nJeoxMyFWM = false;}
      if(FmcIzOSyWd == true){FmcIzOSyWd = false;}
      if(iaLOsAkHlR == true){iaLOsAkHlR = false;}
      if(DYsNNMckAa == true){DYsNNMckAa = false;}
      if(PelwXDHlDQ == true){PelwXDHlDQ = false;}
      if(BdAITNyPux == true){BdAITNyPux = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGXMATWVRB
{ 
  void bDiLkVCEIA()
  { 
      bool eyseVVzQmy = false;
      bool cUaysXsNns = false;
      bool sAQZxcdoGM = false;
      bool iTcqpkFCqG = false;
      bool GptlFMPsda = false;
      bool buPgxdgSgr = false;
      bool qKKZOJriHI = false;
      bool RpVhmDGeUk = false;
      bool NkKeknDutM = false;
      bool DlVzOwfTWu = false;
      bool TfkUIkYhtt = false;
      bool WCywdGzena = false;
      bool GwouEeUVSp = false;
      bool WlHYQgzoWA = false;
      bool OUBAoAmZVI = false;
      bool wAeuoWqpPc = false;
      bool QDODWjuZew = false;
      bool HJInMkunGE = false;
      bool rtAKtVHMjt = false;
      bool pJYsjLFxdE = false;
      string jhPmcKjyTN;
      string saZLSxDbYG;
      string mitxSiIrbD;
      string TEeCTlqLoL;
      string PuLrGpZZgQ;
      string MFqaJAmRTt;
      string CqWQsowWrg;
      string GqlMqqXCqc;
      string IhLKpONEsT;
      string yYruJXYuzQ;
      string sChAKVSdiS;
      string ckZqkTfMZd;
      string ardYhhzqDT;
      string SbCZiGzKAU;
      string wiUapNyAJp;
      string qLVUpBYJSc;
      string VaaPzAhAHe;
      string TVMEhqXDhU;
      string iyhNbGGgjh;
      string gpqXyUIEap;
      if(jhPmcKjyTN == sChAKVSdiS){eyseVVzQmy = true;}
      else if(sChAKVSdiS == jhPmcKjyTN){TfkUIkYhtt = true;}
      if(saZLSxDbYG == ckZqkTfMZd){cUaysXsNns = true;}
      else if(ckZqkTfMZd == saZLSxDbYG){WCywdGzena = true;}
      if(mitxSiIrbD == ardYhhzqDT){sAQZxcdoGM = true;}
      else if(ardYhhzqDT == mitxSiIrbD){GwouEeUVSp = true;}
      if(TEeCTlqLoL == SbCZiGzKAU){iTcqpkFCqG = true;}
      else if(SbCZiGzKAU == TEeCTlqLoL){WlHYQgzoWA = true;}
      if(PuLrGpZZgQ == wiUapNyAJp){GptlFMPsda = true;}
      else if(wiUapNyAJp == PuLrGpZZgQ){OUBAoAmZVI = true;}
      if(MFqaJAmRTt == qLVUpBYJSc){buPgxdgSgr = true;}
      else if(qLVUpBYJSc == MFqaJAmRTt){wAeuoWqpPc = true;}
      if(CqWQsowWrg == VaaPzAhAHe){qKKZOJriHI = true;}
      else if(VaaPzAhAHe == CqWQsowWrg){QDODWjuZew = true;}
      if(GqlMqqXCqc == TVMEhqXDhU){RpVhmDGeUk = true;}
      if(IhLKpONEsT == iyhNbGGgjh){NkKeknDutM = true;}
      if(yYruJXYuzQ == gpqXyUIEap){DlVzOwfTWu = true;}
      while(TVMEhqXDhU == GqlMqqXCqc){HJInMkunGE = true;}
      while(iyhNbGGgjh == iyhNbGGgjh){rtAKtVHMjt = true;}
      while(gpqXyUIEap == gpqXyUIEap){pJYsjLFxdE = true;}
      if(eyseVVzQmy == true){eyseVVzQmy = false;}
      if(cUaysXsNns == true){cUaysXsNns = false;}
      if(sAQZxcdoGM == true){sAQZxcdoGM = false;}
      if(iTcqpkFCqG == true){iTcqpkFCqG = false;}
      if(GptlFMPsda == true){GptlFMPsda = false;}
      if(buPgxdgSgr == true){buPgxdgSgr = false;}
      if(qKKZOJriHI == true){qKKZOJriHI = false;}
      if(RpVhmDGeUk == true){RpVhmDGeUk = false;}
      if(NkKeknDutM == true){NkKeknDutM = false;}
      if(DlVzOwfTWu == true){DlVzOwfTWu = false;}
      if(TfkUIkYhtt == true){TfkUIkYhtt = false;}
      if(WCywdGzena == true){WCywdGzena = false;}
      if(GwouEeUVSp == true){GwouEeUVSp = false;}
      if(WlHYQgzoWA == true){WlHYQgzoWA = false;}
      if(OUBAoAmZVI == true){OUBAoAmZVI = false;}
      if(wAeuoWqpPc == true){wAeuoWqpPc = false;}
      if(QDODWjuZew == true){QDODWjuZew = false;}
      if(HJInMkunGE == true){HJInMkunGE = false;}
      if(rtAKtVHMjt == true){rtAKtVHMjt = false;}
      if(pJYsjLFxdE == true){pJYsjLFxdE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVGKAUDZQI
{ 
  void FbxiQuoJhX()
  { 
      bool sXHITtxQPb = false;
      bool MoCxntzOtU = false;
      bool sNRrjHmVew = false;
      bool zJxtuHHWcx = false;
      bool ibSszHNwCW = false;
      bool hQAbcfFPYM = false;
      bool HakTcCqIBf = false;
      bool lbkxlRtYrb = false;
      bool spTIOiJVQO = false;
      bool BrxQoHpzQw = false;
      bool QFtWkFeCpL = false;
      bool lgXxSRHcEt = false;
      bool sVqmdteTId = false;
      bool auHuKnuwWJ = false;
      bool DGeFcUTAyX = false;
      bool zMtWDuNHrq = false;
      bool aKtLkpZcld = false;
      bool VKGuplplJJ = false;
      bool ZeVkdNAkqP = false;
      bool ZnDfirMSTl = false;
      string yYXejtRwMh;
      string AbbTnXlueF;
      string pNqANOGHEa;
      string hkBwnuBNWn;
      string xWWgseHaKh;
      string LWqNIjgXRU;
      string nJrlzPafes;
      string VYXpHSqJGh;
      string HfxVOKsnmD;
      string NcuCAndjhd;
      string EbuRMmzBGo;
      string sXQiMIMVXn;
      string VlrbercUoT;
      string oGbcdfjfJa;
      string LqhxKpLMor;
      string aIMsHRiTlT;
      string KdLmAmwnEg;
      string XfLwceEtQo;
      string fPexrfshVM;
      string wQspQgeuwW;
      if(yYXejtRwMh == EbuRMmzBGo){sXHITtxQPb = true;}
      else if(EbuRMmzBGo == yYXejtRwMh){QFtWkFeCpL = true;}
      if(AbbTnXlueF == sXQiMIMVXn){MoCxntzOtU = true;}
      else if(sXQiMIMVXn == AbbTnXlueF){lgXxSRHcEt = true;}
      if(pNqANOGHEa == VlrbercUoT){sNRrjHmVew = true;}
      else if(VlrbercUoT == pNqANOGHEa){sVqmdteTId = true;}
      if(hkBwnuBNWn == oGbcdfjfJa){zJxtuHHWcx = true;}
      else if(oGbcdfjfJa == hkBwnuBNWn){auHuKnuwWJ = true;}
      if(xWWgseHaKh == LqhxKpLMor){ibSszHNwCW = true;}
      else if(LqhxKpLMor == xWWgseHaKh){DGeFcUTAyX = true;}
      if(LWqNIjgXRU == aIMsHRiTlT){hQAbcfFPYM = true;}
      else if(aIMsHRiTlT == LWqNIjgXRU){zMtWDuNHrq = true;}
      if(nJrlzPafes == KdLmAmwnEg){HakTcCqIBf = true;}
      else if(KdLmAmwnEg == nJrlzPafes){aKtLkpZcld = true;}
      if(VYXpHSqJGh == XfLwceEtQo){lbkxlRtYrb = true;}
      if(HfxVOKsnmD == fPexrfshVM){spTIOiJVQO = true;}
      if(NcuCAndjhd == wQspQgeuwW){BrxQoHpzQw = true;}
      while(XfLwceEtQo == VYXpHSqJGh){VKGuplplJJ = true;}
      while(fPexrfshVM == fPexrfshVM){ZeVkdNAkqP = true;}
      while(wQspQgeuwW == wQspQgeuwW){ZnDfirMSTl = true;}
      if(sXHITtxQPb == true){sXHITtxQPb = false;}
      if(MoCxntzOtU == true){MoCxntzOtU = false;}
      if(sNRrjHmVew == true){sNRrjHmVew = false;}
      if(zJxtuHHWcx == true){zJxtuHHWcx = false;}
      if(ibSszHNwCW == true){ibSszHNwCW = false;}
      if(hQAbcfFPYM == true){hQAbcfFPYM = false;}
      if(HakTcCqIBf == true){HakTcCqIBf = false;}
      if(lbkxlRtYrb == true){lbkxlRtYrb = false;}
      if(spTIOiJVQO == true){spTIOiJVQO = false;}
      if(BrxQoHpzQw == true){BrxQoHpzQw = false;}
      if(QFtWkFeCpL == true){QFtWkFeCpL = false;}
      if(lgXxSRHcEt == true){lgXxSRHcEt = false;}
      if(sVqmdteTId == true){sVqmdteTId = false;}
      if(auHuKnuwWJ == true){auHuKnuwWJ = false;}
      if(DGeFcUTAyX == true){DGeFcUTAyX = false;}
      if(zMtWDuNHrq == true){zMtWDuNHrq = false;}
      if(aKtLkpZcld == true){aKtLkpZcld = false;}
      if(VKGuplplJJ == true){VKGuplplJJ = false;}
      if(ZeVkdNAkqP == true){ZeVkdNAkqP = false;}
      if(ZnDfirMSTl == true){ZnDfirMSTl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RJGZDXYJSV
{ 
  void htWeBwnVjk()
  { 
      bool qQRukaiEqa = false;
      bool ytFmredRCR = false;
      bool FMdnLqkrEU = false;
      bool lNlQdipXbC = false;
      bool lVsDxlDKZS = false;
      bool HMxSselcis = false;
      bool oqAVokHoII = false;
      bool oFozfjSZqY = false;
      bool nZRkNYQSXz = false;
      bool xNniNtVXOM = false;
      bool eNCRdBXxmI = false;
      bool LMlKFPZPIP = false;
      bool UnRJLbQGlk = false;
      bool OuLdtZXzHM = false;
      bool BSfOmjbdcy = false;
      bool UFPzrpwrFC = false;
      bool jRKBtQAHQe = false;
      bool qZIuNBICVa = false;
      bool AmcnQIfMlD = false;
      bool desEbjIeUW = false;
      string ncfbDalSKB;
      string CDgYxtPUND;
      string rwdQQzzWUn;
      string bnIIkSSHit;
      string PMSLeBlExr;
      string FozIgqyPKE;
      string aOxWZOtXne;
      string bHlSnecSkP;
      string MuYbiloAas;
      string UCxeSAPukP;
      string GOQSQxDfTC;
      string NedtqfpVnn;
      string YtwtKYKGAn;
      string OhhVJyeGKk;
      string hJfYeoYCml;
      string JtHxqMRVIr;
      string mxefmfxIkr;
      string BiKCFPNXPV;
      string zHSNdUZkdw;
      string gJySykdzky;
      if(ncfbDalSKB == GOQSQxDfTC){qQRukaiEqa = true;}
      else if(GOQSQxDfTC == ncfbDalSKB){eNCRdBXxmI = true;}
      if(CDgYxtPUND == NedtqfpVnn){ytFmredRCR = true;}
      else if(NedtqfpVnn == CDgYxtPUND){LMlKFPZPIP = true;}
      if(rwdQQzzWUn == YtwtKYKGAn){FMdnLqkrEU = true;}
      else if(YtwtKYKGAn == rwdQQzzWUn){UnRJLbQGlk = true;}
      if(bnIIkSSHit == OhhVJyeGKk){lNlQdipXbC = true;}
      else if(OhhVJyeGKk == bnIIkSSHit){OuLdtZXzHM = true;}
      if(PMSLeBlExr == hJfYeoYCml){lVsDxlDKZS = true;}
      else if(hJfYeoYCml == PMSLeBlExr){BSfOmjbdcy = true;}
      if(FozIgqyPKE == JtHxqMRVIr){HMxSselcis = true;}
      else if(JtHxqMRVIr == FozIgqyPKE){UFPzrpwrFC = true;}
      if(aOxWZOtXne == mxefmfxIkr){oqAVokHoII = true;}
      else if(mxefmfxIkr == aOxWZOtXne){jRKBtQAHQe = true;}
      if(bHlSnecSkP == BiKCFPNXPV){oFozfjSZqY = true;}
      if(MuYbiloAas == zHSNdUZkdw){nZRkNYQSXz = true;}
      if(UCxeSAPukP == gJySykdzky){xNniNtVXOM = true;}
      while(BiKCFPNXPV == bHlSnecSkP){qZIuNBICVa = true;}
      while(zHSNdUZkdw == zHSNdUZkdw){AmcnQIfMlD = true;}
      while(gJySykdzky == gJySykdzky){desEbjIeUW = true;}
      if(qQRukaiEqa == true){qQRukaiEqa = false;}
      if(ytFmredRCR == true){ytFmredRCR = false;}
      if(FMdnLqkrEU == true){FMdnLqkrEU = false;}
      if(lNlQdipXbC == true){lNlQdipXbC = false;}
      if(lVsDxlDKZS == true){lVsDxlDKZS = false;}
      if(HMxSselcis == true){HMxSselcis = false;}
      if(oqAVokHoII == true){oqAVokHoII = false;}
      if(oFozfjSZqY == true){oFozfjSZqY = false;}
      if(nZRkNYQSXz == true){nZRkNYQSXz = false;}
      if(xNniNtVXOM == true){xNniNtVXOM = false;}
      if(eNCRdBXxmI == true){eNCRdBXxmI = false;}
      if(LMlKFPZPIP == true){LMlKFPZPIP = false;}
      if(UnRJLbQGlk == true){UnRJLbQGlk = false;}
      if(OuLdtZXzHM == true){OuLdtZXzHM = false;}
      if(BSfOmjbdcy == true){BSfOmjbdcy = false;}
      if(UFPzrpwrFC == true){UFPzrpwrFC = false;}
      if(jRKBtQAHQe == true){jRKBtQAHQe = false;}
      if(qZIuNBICVa == true){qZIuNBICVa = false;}
      if(AmcnQIfMlD == true){AmcnQIfMlD = false;}
      if(desEbjIeUW == true){desEbjIeUW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZNCZGVWRAO
{ 
  void tUmGzqkbbh()
  { 
      bool FUIPRcbZHO = false;
      bool tayNzJVmMh = false;
      bool xKtiBnlBuL = false;
      bool TuJoZloIOn = false;
      bool IiYWWWnZNc = false;
      bool ZdouTuZZNd = false;
      bool qadutzQImM = false;
      bool TMYYZNkWLe = false;
      bool AMmSloGOVd = false;
      bool LPukwgFccX = false;
      bool FelAIMFPVF = false;
      bool KDOhcenLJF = false;
      bool rCmJBERncs = false;
      bool IHtnZUZmKY = false;
      bool jpsPTIBNHR = false;
      bool rsTXeDrczD = false;
      bool uRmbxCJZHH = false;
      bool EBBjVCIXos = false;
      bool DEfLAOmWIW = false;
      bool cxmGdRDQRQ = false;
      string IWDqFchhng;
      string zMKAhRZMhl;
      string lffcFikdTz;
      string QBEjZYrCyB;
      string LlaaUcXKdm;
      string nuYYscpZkW;
      string rEOoQyHZaJ;
      string YXOgazEEHc;
      string KazgKUbepw;
      string hRQaJGXlJV;
      string UyiTNPfqyt;
      string YkRILQEgdu;
      string VcidbHHmXT;
      string aRtlIMqeSu;
      string nkfwXwAIOr;
      string CpIOzqOErG;
      string IsSdSGpfzz;
      string ZYNhGkxmGe;
      string GyXfRkJflQ;
      string xlmMmuRBcQ;
      if(IWDqFchhng == UyiTNPfqyt){FUIPRcbZHO = true;}
      else if(UyiTNPfqyt == IWDqFchhng){FelAIMFPVF = true;}
      if(zMKAhRZMhl == YkRILQEgdu){tayNzJVmMh = true;}
      else if(YkRILQEgdu == zMKAhRZMhl){KDOhcenLJF = true;}
      if(lffcFikdTz == VcidbHHmXT){xKtiBnlBuL = true;}
      else if(VcidbHHmXT == lffcFikdTz){rCmJBERncs = true;}
      if(QBEjZYrCyB == aRtlIMqeSu){TuJoZloIOn = true;}
      else if(aRtlIMqeSu == QBEjZYrCyB){IHtnZUZmKY = true;}
      if(LlaaUcXKdm == nkfwXwAIOr){IiYWWWnZNc = true;}
      else if(nkfwXwAIOr == LlaaUcXKdm){jpsPTIBNHR = true;}
      if(nuYYscpZkW == CpIOzqOErG){ZdouTuZZNd = true;}
      else if(CpIOzqOErG == nuYYscpZkW){rsTXeDrczD = true;}
      if(rEOoQyHZaJ == IsSdSGpfzz){qadutzQImM = true;}
      else if(IsSdSGpfzz == rEOoQyHZaJ){uRmbxCJZHH = true;}
      if(YXOgazEEHc == ZYNhGkxmGe){TMYYZNkWLe = true;}
      if(KazgKUbepw == GyXfRkJflQ){AMmSloGOVd = true;}
      if(hRQaJGXlJV == xlmMmuRBcQ){LPukwgFccX = true;}
      while(ZYNhGkxmGe == YXOgazEEHc){EBBjVCIXos = true;}
      while(GyXfRkJflQ == GyXfRkJflQ){DEfLAOmWIW = true;}
      while(xlmMmuRBcQ == xlmMmuRBcQ){cxmGdRDQRQ = true;}
      if(FUIPRcbZHO == true){FUIPRcbZHO = false;}
      if(tayNzJVmMh == true){tayNzJVmMh = false;}
      if(xKtiBnlBuL == true){xKtiBnlBuL = false;}
      if(TuJoZloIOn == true){TuJoZloIOn = false;}
      if(IiYWWWnZNc == true){IiYWWWnZNc = false;}
      if(ZdouTuZZNd == true){ZdouTuZZNd = false;}
      if(qadutzQImM == true){qadutzQImM = false;}
      if(TMYYZNkWLe == true){TMYYZNkWLe = false;}
      if(AMmSloGOVd == true){AMmSloGOVd = false;}
      if(LPukwgFccX == true){LPukwgFccX = false;}
      if(FelAIMFPVF == true){FelAIMFPVF = false;}
      if(KDOhcenLJF == true){KDOhcenLJF = false;}
      if(rCmJBERncs == true){rCmJBERncs = false;}
      if(IHtnZUZmKY == true){IHtnZUZmKY = false;}
      if(jpsPTIBNHR == true){jpsPTIBNHR = false;}
      if(rsTXeDrczD == true){rsTXeDrczD = false;}
      if(uRmbxCJZHH == true){uRmbxCJZHH = false;}
      if(EBBjVCIXos == true){EBBjVCIXos = false;}
      if(DEfLAOmWIW == true){DEfLAOmWIW = false;}
      if(cxmGdRDQRQ == true){cxmGdRDQRQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSKNYMJHJD
{ 
  void nZzJHostZL()
  { 
      bool RYRRdawbcL = false;
      bool DSeoIucMRn = false;
      bool YwpJSijAzn = false;
      bool xQpFaCMzYs = false;
      bool ysWDEpxWLt = false;
      bool ufnuYVhIyt = false;
      bool quboNmcYOF = false;
      bool hdnYpfYlEb = false;
      bool lMoFrQbufF = false;
      bool UEAdCCRhoR = false;
      bool NXIGLRrPEs = false;
      bool wuDWIdGVwx = false;
      bool KhrJkccJWm = false;
      bool OqxmONDhsZ = false;
      bool XMpmIYBdUX = false;
      bool wukrGfezVi = false;
      bool nhsQdEyQHu = false;
      bool ZXbVYyqFAL = false;
      bool bznyqSFEfi = false;
      bool hDMKkpTZID = false;
      string ddehpOyMAT;
      string GnOjyANZpo;
      string PohnEZwarq;
      string PlCKNsrOog;
      string kMfYUcnDsx;
      string mpSgxoupcP;
      string RXUJETlEVE;
      string HzkJDDIJSa;
      string lshtDYTVMY;
      string yBkYOMrWUB;
      string qjgnpnFJct;
      string fkWBdYpZFe;
      string zPqxGFNLtq;
      string LloRjBMtEP;
      string SJrRrNditp;
      string WRRoBarigj;
      string ZtPlitwFRc;
      string MwVoMpWZEr;
      string aeQDTtUzPI;
      string JcMUoYsGiy;
      if(ddehpOyMAT == qjgnpnFJct){RYRRdawbcL = true;}
      else if(qjgnpnFJct == ddehpOyMAT){NXIGLRrPEs = true;}
      if(GnOjyANZpo == fkWBdYpZFe){DSeoIucMRn = true;}
      else if(fkWBdYpZFe == GnOjyANZpo){wuDWIdGVwx = true;}
      if(PohnEZwarq == zPqxGFNLtq){YwpJSijAzn = true;}
      else if(zPqxGFNLtq == PohnEZwarq){KhrJkccJWm = true;}
      if(PlCKNsrOog == LloRjBMtEP){xQpFaCMzYs = true;}
      else if(LloRjBMtEP == PlCKNsrOog){OqxmONDhsZ = true;}
      if(kMfYUcnDsx == SJrRrNditp){ysWDEpxWLt = true;}
      else if(SJrRrNditp == kMfYUcnDsx){XMpmIYBdUX = true;}
      if(mpSgxoupcP == WRRoBarigj){ufnuYVhIyt = true;}
      else if(WRRoBarigj == mpSgxoupcP){wukrGfezVi = true;}
      if(RXUJETlEVE == ZtPlitwFRc){quboNmcYOF = true;}
      else if(ZtPlitwFRc == RXUJETlEVE){nhsQdEyQHu = true;}
      if(HzkJDDIJSa == MwVoMpWZEr){hdnYpfYlEb = true;}
      if(lshtDYTVMY == aeQDTtUzPI){lMoFrQbufF = true;}
      if(yBkYOMrWUB == JcMUoYsGiy){UEAdCCRhoR = true;}
      while(MwVoMpWZEr == HzkJDDIJSa){ZXbVYyqFAL = true;}
      while(aeQDTtUzPI == aeQDTtUzPI){bznyqSFEfi = true;}
      while(JcMUoYsGiy == JcMUoYsGiy){hDMKkpTZID = true;}
      if(RYRRdawbcL == true){RYRRdawbcL = false;}
      if(DSeoIucMRn == true){DSeoIucMRn = false;}
      if(YwpJSijAzn == true){YwpJSijAzn = false;}
      if(xQpFaCMzYs == true){xQpFaCMzYs = false;}
      if(ysWDEpxWLt == true){ysWDEpxWLt = false;}
      if(ufnuYVhIyt == true){ufnuYVhIyt = false;}
      if(quboNmcYOF == true){quboNmcYOF = false;}
      if(hdnYpfYlEb == true){hdnYpfYlEb = false;}
      if(lMoFrQbufF == true){lMoFrQbufF = false;}
      if(UEAdCCRhoR == true){UEAdCCRhoR = false;}
      if(NXIGLRrPEs == true){NXIGLRrPEs = false;}
      if(wuDWIdGVwx == true){wuDWIdGVwx = false;}
      if(KhrJkccJWm == true){KhrJkccJWm = false;}
      if(OqxmONDhsZ == true){OqxmONDhsZ = false;}
      if(XMpmIYBdUX == true){XMpmIYBdUX = false;}
      if(wukrGfezVi == true){wukrGfezVi = false;}
      if(nhsQdEyQHu == true){nhsQdEyQHu = false;}
      if(ZXbVYyqFAL == true){ZXbVYyqFAL = false;}
      if(bznyqSFEfi == true){bznyqSFEfi = false;}
      if(hDMKkpTZID == true){hDMKkpTZID = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXLWWFTLEH
{ 
  void cVHNHWkAzT()
  { 
      bool lcxoXCfVTa = false;
      bool AkigXfaFWL = false;
      bool ZCESueZQhE = false;
      bool XlElYolDCg = false;
      bool tIeirrEWSZ = false;
      bool AiiZqiYess = false;
      bool cPmODNfxHi = false;
      bool tXCpQRXVaD = false;
      bool aCyHEnCdto = false;
      bool QGKJEeUPfd = false;
      bool LGPjfbgsJY = false;
      bool LDEoRZQeKP = false;
      bool LBCSRmMsll = false;
      bool xHowrTmObb = false;
      bool HIUUdNCUqd = false;
      bool NoEQRJDwRr = false;
      bool PmHWbDNHxy = false;
      bool lCDhICghnE = false;
      bool jrBHXHCYeh = false;
      bool PqwiMTAysZ = false;
      string cOVsMXShQq;
      string IQFNsJXcMm;
      string tWqmRfqJHc;
      string xKcQWIpdaO;
      string PDKTTjgDYW;
      string zbtsrGWhbf;
      string fJZntxmopj;
      string TsCyWqLXTg;
      string zmjkcUQiYQ;
      string lHCuhGcWYV;
      string wrMoDGZuWA;
      string tzNtfrYoLZ;
      string gEPZxLqGPQ;
      string OoyyjGZuhV;
      string tUMYWmsHOp;
      string gmLznrcmqq;
      string PSfGlEBPKZ;
      string RdHofMrqDK;
      string SirZiadyKr;
      string dmDpGaoGlR;
      if(cOVsMXShQq == wrMoDGZuWA){lcxoXCfVTa = true;}
      else if(wrMoDGZuWA == cOVsMXShQq){LGPjfbgsJY = true;}
      if(IQFNsJXcMm == tzNtfrYoLZ){AkigXfaFWL = true;}
      else if(tzNtfrYoLZ == IQFNsJXcMm){LDEoRZQeKP = true;}
      if(tWqmRfqJHc == gEPZxLqGPQ){ZCESueZQhE = true;}
      else if(gEPZxLqGPQ == tWqmRfqJHc){LBCSRmMsll = true;}
      if(xKcQWIpdaO == OoyyjGZuhV){XlElYolDCg = true;}
      else if(OoyyjGZuhV == xKcQWIpdaO){xHowrTmObb = true;}
      if(PDKTTjgDYW == tUMYWmsHOp){tIeirrEWSZ = true;}
      else if(tUMYWmsHOp == PDKTTjgDYW){HIUUdNCUqd = true;}
      if(zbtsrGWhbf == gmLznrcmqq){AiiZqiYess = true;}
      else if(gmLznrcmqq == zbtsrGWhbf){NoEQRJDwRr = true;}
      if(fJZntxmopj == PSfGlEBPKZ){cPmODNfxHi = true;}
      else if(PSfGlEBPKZ == fJZntxmopj){PmHWbDNHxy = true;}
      if(TsCyWqLXTg == RdHofMrqDK){tXCpQRXVaD = true;}
      if(zmjkcUQiYQ == SirZiadyKr){aCyHEnCdto = true;}
      if(lHCuhGcWYV == dmDpGaoGlR){QGKJEeUPfd = true;}
      while(RdHofMrqDK == TsCyWqLXTg){lCDhICghnE = true;}
      while(SirZiadyKr == SirZiadyKr){jrBHXHCYeh = true;}
      while(dmDpGaoGlR == dmDpGaoGlR){PqwiMTAysZ = true;}
      if(lcxoXCfVTa == true){lcxoXCfVTa = false;}
      if(AkigXfaFWL == true){AkigXfaFWL = false;}
      if(ZCESueZQhE == true){ZCESueZQhE = false;}
      if(XlElYolDCg == true){XlElYolDCg = false;}
      if(tIeirrEWSZ == true){tIeirrEWSZ = false;}
      if(AiiZqiYess == true){AiiZqiYess = false;}
      if(cPmODNfxHi == true){cPmODNfxHi = false;}
      if(tXCpQRXVaD == true){tXCpQRXVaD = false;}
      if(aCyHEnCdto == true){aCyHEnCdto = false;}
      if(QGKJEeUPfd == true){QGKJEeUPfd = false;}
      if(LGPjfbgsJY == true){LGPjfbgsJY = false;}
      if(LDEoRZQeKP == true){LDEoRZQeKP = false;}
      if(LBCSRmMsll == true){LBCSRmMsll = false;}
      if(xHowrTmObb == true){xHowrTmObb = false;}
      if(HIUUdNCUqd == true){HIUUdNCUqd = false;}
      if(NoEQRJDwRr == true){NoEQRJDwRr = false;}
      if(PmHWbDNHxy == true){PmHWbDNHxy = false;}
      if(lCDhICghnE == true){lCDhICghnE = false;}
      if(jrBHXHCYeh == true){jrBHXHCYeh = false;}
      if(PqwiMTAysZ == true){PqwiMTAysZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STGMHYUOZH
{ 
  void HCfAKAduBA()
  { 
      bool wwPZcYLKfp = false;
      bool suumEbeIRD = false;
      bool HlqkzeUsbr = false;
      bool cqYlVciEVk = false;
      bool PWzRQVNVso = false;
      bool ozzogKFeax = false;
      bool ERhnNCVJQb = false;
      bool salfnjlZTc = false;
      bool QyAmCcqiEL = false;
      bool XDdYgxoLDO = false;
      bool zEEQwOMTBx = false;
      bool YeKxfFRukk = false;
      bool KmEFEoxNzp = false;
      bool uZWFdMsiqn = false;
      bool QXhHlrsfra = false;
      bool ftaSDMAzMG = false;
      bool RzTLByIFTT = false;
      bool MiExTmExSL = false;
      bool wQUYKBzDCQ = false;
      bool MtVjWRDVFn = false;
      string ZzZZwXghxz;
      string ITTOxfOcUE;
      string ZZxdDOthik;
      string yRhtEIcmTQ;
      string uXAlRndldE;
      string KnczMACwVg;
      string dyzLBpkYJn;
      string DaIEJCZKLO;
      string jIEdaJoihE;
      string GgRmmwXnkb;
      string DFboBieYoJ;
      string ZqjGwUsUkq;
      string ABqFhWJVQN;
      string ekYjLefPcq;
      string dPsYdOwKqR;
      string CDDsaBNWGe;
      string ZJHbeoRAuQ;
      string odqsMkISaS;
      string ZyezKagfIJ;
      string RJJyQUHRso;
      if(ZzZZwXghxz == DFboBieYoJ){wwPZcYLKfp = true;}
      else if(DFboBieYoJ == ZzZZwXghxz){zEEQwOMTBx = true;}
      if(ITTOxfOcUE == ZqjGwUsUkq){suumEbeIRD = true;}
      else if(ZqjGwUsUkq == ITTOxfOcUE){YeKxfFRukk = true;}
      if(ZZxdDOthik == ABqFhWJVQN){HlqkzeUsbr = true;}
      else if(ABqFhWJVQN == ZZxdDOthik){KmEFEoxNzp = true;}
      if(yRhtEIcmTQ == ekYjLefPcq){cqYlVciEVk = true;}
      else if(ekYjLefPcq == yRhtEIcmTQ){uZWFdMsiqn = true;}
      if(uXAlRndldE == dPsYdOwKqR){PWzRQVNVso = true;}
      else if(dPsYdOwKqR == uXAlRndldE){QXhHlrsfra = true;}
      if(KnczMACwVg == CDDsaBNWGe){ozzogKFeax = true;}
      else if(CDDsaBNWGe == KnczMACwVg){ftaSDMAzMG = true;}
      if(dyzLBpkYJn == ZJHbeoRAuQ){ERhnNCVJQb = true;}
      else if(ZJHbeoRAuQ == dyzLBpkYJn){RzTLByIFTT = true;}
      if(DaIEJCZKLO == odqsMkISaS){salfnjlZTc = true;}
      if(jIEdaJoihE == ZyezKagfIJ){QyAmCcqiEL = true;}
      if(GgRmmwXnkb == RJJyQUHRso){XDdYgxoLDO = true;}
      while(odqsMkISaS == DaIEJCZKLO){MiExTmExSL = true;}
      while(ZyezKagfIJ == ZyezKagfIJ){wQUYKBzDCQ = true;}
      while(RJJyQUHRso == RJJyQUHRso){MtVjWRDVFn = true;}
      if(wwPZcYLKfp == true){wwPZcYLKfp = false;}
      if(suumEbeIRD == true){suumEbeIRD = false;}
      if(HlqkzeUsbr == true){HlqkzeUsbr = false;}
      if(cqYlVciEVk == true){cqYlVciEVk = false;}
      if(PWzRQVNVso == true){PWzRQVNVso = false;}
      if(ozzogKFeax == true){ozzogKFeax = false;}
      if(ERhnNCVJQb == true){ERhnNCVJQb = false;}
      if(salfnjlZTc == true){salfnjlZTc = false;}
      if(QyAmCcqiEL == true){QyAmCcqiEL = false;}
      if(XDdYgxoLDO == true){XDdYgxoLDO = false;}
      if(zEEQwOMTBx == true){zEEQwOMTBx = false;}
      if(YeKxfFRukk == true){YeKxfFRukk = false;}
      if(KmEFEoxNzp == true){KmEFEoxNzp = false;}
      if(uZWFdMsiqn == true){uZWFdMsiqn = false;}
      if(QXhHlrsfra == true){QXhHlrsfra = false;}
      if(ftaSDMAzMG == true){ftaSDMAzMG = false;}
      if(RzTLByIFTT == true){RzTLByIFTT = false;}
      if(MiExTmExSL == true){MiExTmExSL = false;}
      if(wQUYKBzDCQ == true){wQUYKBzDCQ = false;}
      if(MtVjWRDVFn == true){MtVjWRDVFn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFPEGBBCYN
{ 
  void WuIoXEkTWA()
  { 
      bool WGOySidmpk = false;
      bool SBeJdtnLwu = false;
      bool ayhnGKMMbj = false;
      bool BzuqFqURQy = false;
      bool CmzVRJbCGO = false;
      bool mRuAhYYaqH = false;
      bool WQKGiSFmEl = false;
      bool YWuxrnyMWx = false;
      bool iJGMwiEuJf = false;
      bool StZJblbsly = false;
      bool DnyUpQWxHt = false;
      bool ZLDtXMKyJA = false;
      bool OKdXSewlVG = false;
      bool LEaYsuLlWf = false;
      bool LGnPGHqfkO = false;
      bool adjkisJZBK = false;
      bool UkaBhVkeAb = false;
      bool AYadnIWORL = false;
      bool mPAHehUooA = false;
      bool lkjLKaelgk = false;
      string SIHbVMPLti;
      string zhMfkOSpTo;
      string jSpErnjXNa;
      string YHdpKHLoUO;
      string VmTEMacKBa;
      string hGTmhzRDih;
      string bryTKrDVUc;
      string DdUFSxzlqQ;
      string KZVlrRmpHK;
      string pHFmldnztU;
      string WGoXXDlOTk;
      string AfLRWCVLar;
      string ENNKluXgSo;
      string IzqWsEkxNo;
      string fYVWKKwmQj;
      string HbYBPJrekc;
      string eEudbBnoXS;
      string RXylLeqqAb;
      string yjPihgZpGj;
      string LGLkJbdruI;
      if(SIHbVMPLti == WGoXXDlOTk){WGOySidmpk = true;}
      else if(WGoXXDlOTk == SIHbVMPLti){DnyUpQWxHt = true;}
      if(zhMfkOSpTo == AfLRWCVLar){SBeJdtnLwu = true;}
      else if(AfLRWCVLar == zhMfkOSpTo){ZLDtXMKyJA = true;}
      if(jSpErnjXNa == ENNKluXgSo){ayhnGKMMbj = true;}
      else if(ENNKluXgSo == jSpErnjXNa){OKdXSewlVG = true;}
      if(YHdpKHLoUO == IzqWsEkxNo){BzuqFqURQy = true;}
      else if(IzqWsEkxNo == YHdpKHLoUO){LEaYsuLlWf = true;}
      if(VmTEMacKBa == fYVWKKwmQj){CmzVRJbCGO = true;}
      else if(fYVWKKwmQj == VmTEMacKBa){LGnPGHqfkO = true;}
      if(hGTmhzRDih == HbYBPJrekc){mRuAhYYaqH = true;}
      else if(HbYBPJrekc == hGTmhzRDih){adjkisJZBK = true;}
      if(bryTKrDVUc == eEudbBnoXS){WQKGiSFmEl = true;}
      else if(eEudbBnoXS == bryTKrDVUc){UkaBhVkeAb = true;}
      if(DdUFSxzlqQ == RXylLeqqAb){YWuxrnyMWx = true;}
      if(KZVlrRmpHK == yjPihgZpGj){iJGMwiEuJf = true;}
      if(pHFmldnztU == LGLkJbdruI){StZJblbsly = true;}
      while(RXylLeqqAb == DdUFSxzlqQ){AYadnIWORL = true;}
      while(yjPihgZpGj == yjPihgZpGj){mPAHehUooA = true;}
      while(LGLkJbdruI == LGLkJbdruI){lkjLKaelgk = true;}
      if(WGOySidmpk == true){WGOySidmpk = false;}
      if(SBeJdtnLwu == true){SBeJdtnLwu = false;}
      if(ayhnGKMMbj == true){ayhnGKMMbj = false;}
      if(BzuqFqURQy == true){BzuqFqURQy = false;}
      if(CmzVRJbCGO == true){CmzVRJbCGO = false;}
      if(mRuAhYYaqH == true){mRuAhYYaqH = false;}
      if(WQKGiSFmEl == true){WQKGiSFmEl = false;}
      if(YWuxrnyMWx == true){YWuxrnyMWx = false;}
      if(iJGMwiEuJf == true){iJGMwiEuJf = false;}
      if(StZJblbsly == true){StZJblbsly = false;}
      if(DnyUpQWxHt == true){DnyUpQWxHt = false;}
      if(ZLDtXMKyJA == true){ZLDtXMKyJA = false;}
      if(OKdXSewlVG == true){OKdXSewlVG = false;}
      if(LEaYsuLlWf == true){LEaYsuLlWf = false;}
      if(LGnPGHqfkO == true){LGnPGHqfkO = false;}
      if(adjkisJZBK == true){adjkisJZBK = false;}
      if(UkaBhVkeAb == true){UkaBhVkeAb = false;}
      if(AYadnIWORL == true){AYadnIWORL = false;}
      if(mPAHehUooA == true){mPAHehUooA = false;}
      if(lkjLKaelgk == true){lkjLKaelgk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCKJAOFSEK
{ 
  void WVjcPjZTLm()
  { 
      bool ThXnpcKOBa = false;
      bool xiGEtWQhCG = false;
      bool IpDnIbmtDN = false;
      bool FxjoANRALY = false;
      bool eLhgtcYEfV = false;
      bool WNLxEddjeO = false;
      bool pPLmUAyREg = false;
      bool EQWdawIVte = false;
      bool ChOhprlmjV = false;
      bool ihUwiOAtMs = false;
      bool dHAyQGphVI = false;
      bool VIoALHBdwc = false;
      bool OLghyWuatL = false;
      bool wNJABugPQj = false;
      bool BDQbzasUja = false;
      bool NWxieRaRAs = false;
      bool KPmJLIynzQ = false;
      bool akMMaKuEhW = false;
      bool dapTyYQZVi = false;
      bool UPPXYlPGPq = false;
      string nrAsObjEOH;
      string zzbEgVxXqp;
      string qVnGROdgRB;
      string LzQVkKlONt;
      string IEYyKYSdJR;
      string oNgODSDsbA;
      string yDlMuzhGSV;
      string ihKwglxpws;
      string wAXzMyRBRS;
      string GrmMwFRLCK;
      string pMKnhHDkgQ;
      string VNxhExflAx;
      string hfnAOqtxAb;
      string UknkCjpiRE;
      string tfTAxsuEIy;
      string ZeKEcKXJZq;
      string MFjFwjYMfU;
      string HwUuCBMnDU;
      string wpnCCoaiIr;
      string MfJarnwODN;
      if(nrAsObjEOH == pMKnhHDkgQ){ThXnpcKOBa = true;}
      else if(pMKnhHDkgQ == nrAsObjEOH){dHAyQGphVI = true;}
      if(zzbEgVxXqp == VNxhExflAx){xiGEtWQhCG = true;}
      else if(VNxhExflAx == zzbEgVxXqp){VIoALHBdwc = true;}
      if(qVnGROdgRB == hfnAOqtxAb){IpDnIbmtDN = true;}
      else if(hfnAOqtxAb == qVnGROdgRB){OLghyWuatL = true;}
      if(LzQVkKlONt == UknkCjpiRE){FxjoANRALY = true;}
      else if(UknkCjpiRE == LzQVkKlONt){wNJABugPQj = true;}
      if(IEYyKYSdJR == tfTAxsuEIy){eLhgtcYEfV = true;}
      else if(tfTAxsuEIy == IEYyKYSdJR){BDQbzasUja = true;}
      if(oNgODSDsbA == ZeKEcKXJZq){WNLxEddjeO = true;}
      else if(ZeKEcKXJZq == oNgODSDsbA){NWxieRaRAs = true;}
      if(yDlMuzhGSV == MFjFwjYMfU){pPLmUAyREg = true;}
      else if(MFjFwjYMfU == yDlMuzhGSV){KPmJLIynzQ = true;}
      if(ihKwglxpws == HwUuCBMnDU){EQWdawIVte = true;}
      if(wAXzMyRBRS == wpnCCoaiIr){ChOhprlmjV = true;}
      if(GrmMwFRLCK == MfJarnwODN){ihUwiOAtMs = true;}
      while(HwUuCBMnDU == ihKwglxpws){akMMaKuEhW = true;}
      while(wpnCCoaiIr == wpnCCoaiIr){dapTyYQZVi = true;}
      while(MfJarnwODN == MfJarnwODN){UPPXYlPGPq = true;}
      if(ThXnpcKOBa == true){ThXnpcKOBa = false;}
      if(xiGEtWQhCG == true){xiGEtWQhCG = false;}
      if(IpDnIbmtDN == true){IpDnIbmtDN = false;}
      if(FxjoANRALY == true){FxjoANRALY = false;}
      if(eLhgtcYEfV == true){eLhgtcYEfV = false;}
      if(WNLxEddjeO == true){WNLxEddjeO = false;}
      if(pPLmUAyREg == true){pPLmUAyREg = false;}
      if(EQWdawIVte == true){EQWdawIVte = false;}
      if(ChOhprlmjV == true){ChOhprlmjV = false;}
      if(ihUwiOAtMs == true){ihUwiOAtMs = false;}
      if(dHAyQGphVI == true){dHAyQGphVI = false;}
      if(VIoALHBdwc == true){VIoALHBdwc = false;}
      if(OLghyWuatL == true){OLghyWuatL = false;}
      if(wNJABugPQj == true){wNJABugPQj = false;}
      if(BDQbzasUja == true){BDQbzasUja = false;}
      if(NWxieRaRAs == true){NWxieRaRAs = false;}
      if(KPmJLIynzQ == true){KPmJLIynzQ = false;}
      if(akMMaKuEhW == true){akMMaKuEhW = false;}
      if(dapTyYQZVi == true){dapTyYQZVi = false;}
      if(UPPXYlPGPq == true){UPPXYlPGPq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSIDFGFQHN
{ 
  void dVKEFLyqiV()
  { 
      bool PObynaYIVU = false;
      bool KaqbLRIyZY = false;
      bool xcLttohSmy = false;
      bool RuchWAajSl = false;
      bool CqdCkijMjT = false;
      bool mbxdXlCgEz = false;
      bool sFUWDOyIFL = false;
      bool pYemWFyIJK = false;
      bool EUiTLoxyJj = false;
      bool yseTswWHzV = false;
      bool kaGYcOwJHR = false;
      bool nsXttXWALN = false;
      bool RzyVMwsLtZ = false;
      bool iqJnZcOJpw = false;
      bool rmqrwEVkYU = false;
      bool ZVwkElckLf = false;
      bool UkPhixjjUR = false;
      bool JMKOVdHGZH = false;
      bool aImYzMtXim = false;
      bool AcxJbGXIIz = false;
      string EQUQelmbSz;
      string ohbiNndNMl;
      string OhJdXBQMeq;
      string CRuYStIaCL;
      string AXnuIssfNT;
      string smTkFWHpsd;
      string VaxbxWmCQS;
      string fCKBlpsNVe;
      string IjzKxPyJSu;
      string mSgYoZaMyk;
      string FpPtnpbRzP;
      string dsTOVkbleh;
      string YciUfNVkLL;
      string PgPjYRUEWG;
      string mgKDRsySCE;
      string yngPMcHtOa;
      string UqFmAwcjpE;
      string PWPYtrSfDl;
      string ODhHNazAXu;
      string KaowkwaWCU;
      if(EQUQelmbSz == FpPtnpbRzP){PObynaYIVU = true;}
      else if(FpPtnpbRzP == EQUQelmbSz){kaGYcOwJHR = true;}
      if(ohbiNndNMl == dsTOVkbleh){KaqbLRIyZY = true;}
      else if(dsTOVkbleh == ohbiNndNMl){nsXttXWALN = true;}
      if(OhJdXBQMeq == YciUfNVkLL){xcLttohSmy = true;}
      else if(YciUfNVkLL == OhJdXBQMeq){RzyVMwsLtZ = true;}
      if(CRuYStIaCL == PgPjYRUEWG){RuchWAajSl = true;}
      else if(PgPjYRUEWG == CRuYStIaCL){iqJnZcOJpw = true;}
      if(AXnuIssfNT == mgKDRsySCE){CqdCkijMjT = true;}
      else if(mgKDRsySCE == AXnuIssfNT){rmqrwEVkYU = true;}
      if(smTkFWHpsd == yngPMcHtOa){mbxdXlCgEz = true;}
      else if(yngPMcHtOa == smTkFWHpsd){ZVwkElckLf = true;}
      if(VaxbxWmCQS == UqFmAwcjpE){sFUWDOyIFL = true;}
      else if(UqFmAwcjpE == VaxbxWmCQS){UkPhixjjUR = true;}
      if(fCKBlpsNVe == PWPYtrSfDl){pYemWFyIJK = true;}
      if(IjzKxPyJSu == ODhHNazAXu){EUiTLoxyJj = true;}
      if(mSgYoZaMyk == KaowkwaWCU){yseTswWHzV = true;}
      while(PWPYtrSfDl == fCKBlpsNVe){JMKOVdHGZH = true;}
      while(ODhHNazAXu == ODhHNazAXu){aImYzMtXim = true;}
      while(KaowkwaWCU == KaowkwaWCU){AcxJbGXIIz = true;}
      if(PObynaYIVU == true){PObynaYIVU = false;}
      if(KaqbLRIyZY == true){KaqbLRIyZY = false;}
      if(xcLttohSmy == true){xcLttohSmy = false;}
      if(RuchWAajSl == true){RuchWAajSl = false;}
      if(CqdCkijMjT == true){CqdCkijMjT = false;}
      if(mbxdXlCgEz == true){mbxdXlCgEz = false;}
      if(sFUWDOyIFL == true){sFUWDOyIFL = false;}
      if(pYemWFyIJK == true){pYemWFyIJK = false;}
      if(EUiTLoxyJj == true){EUiTLoxyJj = false;}
      if(yseTswWHzV == true){yseTswWHzV = false;}
      if(kaGYcOwJHR == true){kaGYcOwJHR = false;}
      if(nsXttXWALN == true){nsXttXWALN = false;}
      if(RzyVMwsLtZ == true){RzyVMwsLtZ = false;}
      if(iqJnZcOJpw == true){iqJnZcOJpw = false;}
      if(rmqrwEVkYU == true){rmqrwEVkYU = false;}
      if(ZVwkElckLf == true){ZVwkElckLf = false;}
      if(UkPhixjjUR == true){UkPhixjjUR = false;}
      if(JMKOVdHGZH == true){JMKOVdHGZH = false;}
      if(aImYzMtXim == true){aImYzMtXim = false;}
      if(AcxJbGXIIz == true){AcxJbGXIIz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZTQGJKKKU
{ 
  void GuojFJxjKD()
  { 
      bool eabfPtgiEI = false;
      bool RNLlUilMJX = false;
      bool TmhIYGlJZE = false;
      bool tdJbBusykk = false;
      bool KNDiADUZsH = false;
      bool iVOtCqrSHJ = false;
      bool HXJzNmDikZ = false;
      bool ombYMGjzHU = false;
      bool lMPRUXOPZJ = false;
      bool CaqbdlDDUM = false;
      bool AknTSwtpgw = false;
      bool HrKlXuHqdo = false;
      bool XnJaWOuAta = false;
      bool CfeuTAXuzY = false;
      bool dYhcCJPEEi = false;
      bool dMZenLaNxE = false;
      bool AsuGsbNPSW = false;
      bool WLrFKzFfYM = false;
      bool yqwLwpFzGH = false;
      bool YKytYjcaiZ = false;
      string nDnxThdEfI;
      string BhqOpZuxZx;
      string JNnsIMTwIs;
      string qMlmbYyFar;
      string DdBIChEhqo;
      string TmyIraOtnG;
      string NhumQouEmR;
      string apVgtfLeqZ;
      string IkESZDNctB;
      string KEQUdVhNrN;
      string mAuZNdRQOM;
      string OiDNybccNM;
      string aRJkHWYACX;
      string xxmcmHpeEw;
      string lxOgmaACVC;
      string rFAelUpJSp;
      string EQNpPQuZap;
      string lyXRadDbyf;
      string VVeAfrxIqR;
      string RfLNqViYRV;
      if(nDnxThdEfI == mAuZNdRQOM){eabfPtgiEI = true;}
      else if(mAuZNdRQOM == nDnxThdEfI){AknTSwtpgw = true;}
      if(BhqOpZuxZx == OiDNybccNM){RNLlUilMJX = true;}
      else if(OiDNybccNM == BhqOpZuxZx){HrKlXuHqdo = true;}
      if(JNnsIMTwIs == aRJkHWYACX){TmhIYGlJZE = true;}
      else if(aRJkHWYACX == JNnsIMTwIs){XnJaWOuAta = true;}
      if(qMlmbYyFar == xxmcmHpeEw){tdJbBusykk = true;}
      else if(xxmcmHpeEw == qMlmbYyFar){CfeuTAXuzY = true;}
      if(DdBIChEhqo == lxOgmaACVC){KNDiADUZsH = true;}
      else if(lxOgmaACVC == DdBIChEhqo){dYhcCJPEEi = true;}
      if(TmyIraOtnG == rFAelUpJSp){iVOtCqrSHJ = true;}
      else if(rFAelUpJSp == TmyIraOtnG){dMZenLaNxE = true;}
      if(NhumQouEmR == EQNpPQuZap){HXJzNmDikZ = true;}
      else if(EQNpPQuZap == NhumQouEmR){AsuGsbNPSW = true;}
      if(apVgtfLeqZ == lyXRadDbyf){ombYMGjzHU = true;}
      if(IkESZDNctB == VVeAfrxIqR){lMPRUXOPZJ = true;}
      if(KEQUdVhNrN == RfLNqViYRV){CaqbdlDDUM = true;}
      while(lyXRadDbyf == apVgtfLeqZ){WLrFKzFfYM = true;}
      while(VVeAfrxIqR == VVeAfrxIqR){yqwLwpFzGH = true;}
      while(RfLNqViYRV == RfLNqViYRV){YKytYjcaiZ = true;}
      if(eabfPtgiEI == true){eabfPtgiEI = false;}
      if(RNLlUilMJX == true){RNLlUilMJX = false;}
      if(TmhIYGlJZE == true){TmhIYGlJZE = false;}
      if(tdJbBusykk == true){tdJbBusykk = false;}
      if(KNDiADUZsH == true){KNDiADUZsH = false;}
      if(iVOtCqrSHJ == true){iVOtCqrSHJ = false;}
      if(HXJzNmDikZ == true){HXJzNmDikZ = false;}
      if(ombYMGjzHU == true){ombYMGjzHU = false;}
      if(lMPRUXOPZJ == true){lMPRUXOPZJ = false;}
      if(CaqbdlDDUM == true){CaqbdlDDUM = false;}
      if(AknTSwtpgw == true){AknTSwtpgw = false;}
      if(HrKlXuHqdo == true){HrKlXuHqdo = false;}
      if(XnJaWOuAta == true){XnJaWOuAta = false;}
      if(CfeuTAXuzY == true){CfeuTAXuzY = false;}
      if(dYhcCJPEEi == true){dYhcCJPEEi = false;}
      if(dMZenLaNxE == true){dMZenLaNxE = false;}
      if(AsuGsbNPSW == true){AsuGsbNPSW = false;}
      if(WLrFKzFfYM == true){WLrFKzFfYM = false;}
      if(yqwLwpFzGH == true){yqwLwpFzGH = false;}
      if(YKytYjcaiZ == true){YKytYjcaiZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ATJRRADUMO
{ 
  void YxbeJwqTjS()
  { 
      bool wsKalUPklV = false;
      bool dwrwmqRBZB = false;
      bool iczGqXahkD = false;
      bool QmZhPzVCjg = false;
      bool OjJeuUjfBO = false;
      bool yBmynTtEiN = false;
      bool tgAhFqWKfm = false;
      bool UPQrlyTULW = false;
      bool ntgWEOAbsw = false;
      bool FRSWlhjaZD = false;
      bool xZzNsijtLp = false;
      bool zYsMZzAddp = false;
      bool qtQjgDwtGE = false;
      bool OstHYNuScU = false;
      bool eGQDwfXGwm = false;
      bool hGxjMDJPfo = false;
      bool lomGaGelmM = false;
      bool DgAILjdMmB = false;
      bool epyTWHwKtV = false;
      bool DfmnioSJcp = false;
      string DipVswWPbU;
      string eNDBmhhoha;
      string AzVVPeIBjb;
      string VXjSkIHguF;
      string jHAisuNyWu;
      string yCLsoDMUFN;
      string mUeAyHdjQe;
      string aAtcprzlcU;
      string QJeocTLpdg;
      string wlbgRPbAkk;
      string QchrUyIiCx;
      string EZrjwdppWe;
      string umGihnYNKa;
      string QzBqDnblTe;
      string KbngcVtqjn;
      string YkcFpdWyJf;
      string YtYagFYAfI;
      string BDVqTTzZGM;
      string sgcWBeVuBZ;
      string QccnGPDMzX;
      if(DipVswWPbU == QchrUyIiCx){wsKalUPklV = true;}
      else if(QchrUyIiCx == DipVswWPbU){xZzNsijtLp = true;}
      if(eNDBmhhoha == EZrjwdppWe){dwrwmqRBZB = true;}
      else if(EZrjwdppWe == eNDBmhhoha){zYsMZzAddp = true;}
      if(AzVVPeIBjb == umGihnYNKa){iczGqXahkD = true;}
      else if(umGihnYNKa == AzVVPeIBjb){qtQjgDwtGE = true;}
      if(VXjSkIHguF == QzBqDnblTe){QmZhPzVCjg = true;}
      else if(QzBqDnblTe == VXjSkIHguF){OstHYNuScU = true;}
      if(jHAisuNyWu == KbngcVtqjn){OjJeuUjfBO = true;}
      else if(KbngcVtqjn == jHAisuNyWu){eGQDwfXGwm = true;}
      if(yCLsoDMUFN == YkcFpdWyJf){yBmynTtEiN = true;}
      else if(YkcFpdWyJf == yCLsoDMUFN){hGxjMDJPfo = true;}
      if(mUeAyHdjQe == YtYagFYAfI){tgAhFqWKfm = true;}
      else if(YtYagFYAfI == mUeAyHdjQe){lomGaGelmM = true;}
      if(aAtcprzlcU == BDVqTTzZGM){UPQrlyTULW = true;}
      if(QJeocTLpdg == sgcWBeVuBZ){ntgWEOAbsw = true;}
      if(wlbgRPbAkk == QccnGPDMzX){FRSWlhjaZD = true;}
      while(BDVqTTzZGM == aAtcprzlcU){DgAILjdMmB = true;}
      while(sgcWBeVuBZ == sgcWBeVuBZ){epyTWHwKtV = true;}
      while(QccnGPDMzX == QccnGPDMzX){DfmnioSJcp = true;}
      if(wsKalUPklV == true){wsKalUPklV = false;}
      if(dwrwmqRBZB == true){dwrwmqRBZB = false;}
      if(iczGqXahkD == true){iczGqXahkD = false;}
      if(QmZhPzVCjg == true){QmZhPzVCjg = false;}
      if(OjJeuUjfBO == true){OjJeuUjfBO = false;}
      if(yBmynTtEiN == true){yBmynTtEiN = false;}
      if(tgAhFqWKfm == true){tgAhFqWKfm = false;}
      if(UPQrlyTULW == true){UPQrlyTULW = false;}
      if(ntgWEOAbsw == true){ntgWEOAbsw = false;}
      if(FRSWlhjaZD == true){FRSWlhjaZD = false;}
      if(xZzNsijtLp == true){xZzNsijtLp = false;}
      if(zYsMZzAddp == true){zYsMZzAddp = false;}
      if(qtQjgDwtGE == true){qtQjgDwtGE = false;}
      if(OstHYNuScU == true){OstHYNuScU = false;}
      if(eGQDwfXGwm == true){eGQDwfXGwm = false;}
      if(hGxjMDJPfo == true){hGxjMDJPfo = false;}
      if(lomGaGelmM == true){lomGaGelmM = false;}
      if(DgAILjdMmB == true){DgAILjdMmB = false;}
      if(epyTWHwKtV == true){epyTWHwKtV = false;}
      if(DfmnioSJcp == true){DfmnioSJcp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFTWYBZCDR
{ 
  void jwhXrjRNLc()
  { 
      bool quSTkmVuUI = false;
      bool UoKkQJuVPB = false;
      bool UbfMAtcsTW = false;
      bool bjLIMYRqUy = false;
      bool QptRDhXtac = false;
      bool dzWIGPPFSp = false;
      bool KbbyfjcCXr = false;
      bool qEAQjdgNJS = false;
      bool WhRqrbNDCx = false;
      bool IMXdnnOwkT = false;
      bool EVVilYzFXb = false;
      bool hBwATbKkFD = false;
      bool VZzaiefVcu = false;
      bool OkcoOBLiFT = false;
      bool cHeZOHQXKM = false;
      bool ddphxeVtzG = false;
      bool scccNxYGlR = false;
      bool PaflaOtZMb = false;
      bool OILPQjturj = false;
      bool eRiyZAdCMQ = false;
      string zkumzEquzP;
      string bIVBBRXMPH;
      string eYlaPjDRyu;
      string ykTYEGIcMW;
      string zQtKrsZLVP;
      string dIpstZzUXP;
      string AYwERpnxxt;
      string JuzrINeahV;
      string KrwiQouadd;
      string HmFxWZTpsB;
      string FcObGiJxkg;
      string uYlBFHcNnb;
      string uNSSlVoCVi;
      string sngfQgdUcg;
      string fxoxhiBEqO;
      string wGCQGrKuok;
      string tGbCnGqFkX;
      string dIkGwxXUjD;
      string TkKGlmlPZX;
      string WifqlYVmJa;
      if(zkumzEquzP == FcObGiJxkg){quSTkmVuUI = true;}
      else if(FcObGiJxkg == zkumzEquzP){EVVilYzFXb = true;}
      if(bIVBBRXMPH == uYlBFHcNnb){UoKkQJuVPB = true;}
      else if(uYlBFHcNnb == bIVBBRXMPH){hBwATbKkFD = true;}
      if(eYlaPjDRyu == uNSSlVoCVi){UbfMAtcsTW = true;}
      else if(uNSSlVoCVi == eYlaPjDRyu){VZzaiefVcu = true;}
      if(ykTYEGIcMW == sngfQgdUcg){bjLIMYRqUy = true;}
      else if(sngfQgdUcg == ykTYEGIcMW){OkcoOBLiFT = true;}
      if(zQtKrsZLVP == fxoxhiBEqO){QptRDhXtac = true;}
      else if(fxoxhiBEqO == zQtKrsZLVP){cHeZOHQXKM = true;}
      if(dIpstZzUXP == wGCQGrKuok){dzWIGPPFSp = true;}
      else if(wGCQGrKuok == dIpstZzUXP){ddphxeVtzG = true;}
      if(AYwERpnxxt == tGbCnGqFkX){KbbyfjcCXr = true;}
      else if(tGbCnGqFkX == AYwERpnxxt){scccNxYGlR = true;}
      if(JuzrINeahV == dIkGwxXUjD){qEAQjdgNJS = true;}
      if(KrwiQouadd == TkKGlmlPZX){WhRqrbNDCx = true;}
      if(HmFxWZTpsB == WifqlYVmJa){IMXdnnOwkT = true;}
      while(dIkGwxXUjD == JuzrINeahV){PaflaOtZMb = true;}
      while(TkKGlmlPZX == TkKGlmlPZX){OILPQjturj = true;}
      while(WifqlYVmJa == WifqlYVmJa){eRiyZAdCMQ = true;}
      if(quSTkmVuUI == true){quSTkmVuUI = false;}
      if(UoKkQJuVPB == true){UoKkQJuVPB = false;}
      if(UbfMAtcsTW == true){UbfMAtcsTW = false;}
      if(bjLIMYRqUy == true){bjLIMYRqUy = false;}
      if(QptRDhXtac == true){QptRDhXtac = false;}
      if(dzWIGPPFSp == true){dzWIGPPFSp = false;}
      if(KbbyfjcCXr == true){KbbyfjcCXr = false;}
      if(qEAQjdgNJS == true){qEAQjdgNJS = false;}
      if(WhRqrbNDCx == true){WhRqrbNDCx = false;}
      if(IMXdnnOwkT == true){IMXdnnOwkT = false;}
      if(EVVilYzFXb == true){EVVilYzFXb = false;}
      if(hBwATbKkFD == true){hBwATbKkFD = false;}
      if(VZzaiefVcu == true){VZzaiefVcu = false;}
      if(OkcoOBLiFT == true){OkcoOBLiFT = false;}
      if(cHeZOHQXKM == true){cHeZOHQXKM = false;}
      if(ddphxeVtzG == true){ddphxeVtzG = false;}
      if(scccNxYGlR == true){scccNxYGlR = false;}
      if(PaflaOtZMb == true){PaflaOtZMb = false;}
      if(OILPQjturj == true){OILPQjturj = false;}
      if(eRiyZAdCMQ == true){eRiyZAdCMQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TZQATUQOYH
{ 
  void mMSBBcEFVo()
  { 
      bool yxwswuPyUJ = false;
      bool frIlIEPALT = false;
      bool JqbBNWgAta = false;
      bool UAHDKOxPGE = false;
      bool NuYVYQBZUl = false;
      bool KpGYAHVufY = false;
      bool NODsnekEat = false;
      bool HAsGFOSGbw = false;
      bool VHfIPeshDD = false;
      bool rBihqyqegs = false;
      bool fwzZdKwATk = false;
      bool nPSjDGhtdI = false;
      bool lDAXBFQLPG = false;
      bool WnYiQYHGdF = false;
      bool hsOROcizdk = false;
      bool QwBXHbuaYY = false;
      bool tkjMOApjSd = false;
      bool ybQXarniIX = false;
      bool WQgdpZlBan = false;
      bool cggFKxIBCN = false;
      string hRLeeZBHyX;
      string KjZhESbPqO;
      string aMYeWUnHum;
      string SdIYOcqTzY;
      string jgWgFXjONM;
      string CQBdOVsfIJ;
      string ktLLFfaBSa;
      string aHPSdsorYz;
      string kZsijBbdKs;
      string jKLompVLaY;
      string wiulktAiAU;
      string gBGIYKBbaD;
      string ExpZqQwZen;
      string XdQzDCeHyo;
      string BsdpMhECQb;
      string ntjWUyrVtU;
      string yZDLxCjGFW;
      string fsdlCLSANI;
      string LsJDzdsseE;
      string JJMcqapSsJ;
      if(hRLeeZBHyX == wiulktAiAU){yxwswuPyUJ = true;}
      else if(wiulktAiAU == hRLeeZBHyX){fwzZdKwATk = true;}
      if(KjZhESbPqO == gBGIYKBbaD){frIlIEPALT = true;}
      else if(gBGIYKBbaD == KjZhESbPqO){nPSjDGhtdI = true;}
      if(aMYeWUnHum == ExpZqQwZen){JqbBNWgAta = true;}
      else if(ExpZqQwZen == aMYeWUnHum){lDAXBFQLPG = true;}
      if(SdIYOcqTzY == XdQzDCeHyo){UAHDKOxPGE = true;}
      else if(XdQzDCeHyo == SdIYOcqTzY){WnYiQYHGdF = true;}
      if(jgWgFXjONM == BsdpMhECQb){NuYVYQBZUl = true;}
      else if(BsdpMhECQb == jgWgFXjONM){hsOROcizdk = true;}
      if(CQBdOVsfIJ == ntjWUyrVtU){KpGYAHVufY = true;}
      else if(ntjWUyrVtU == CQBdOVsfIJ){QwBXHbuaYY = true;}
      if(ktLLFfaBSa == yZDLxCjGFW){NODsnekEat = true;}
      else if(yZDLxCjGFW == ktLLFfaBSa){tkjMOApjSd = true;}
      if(aHPSdsorYz == fsdlCLSANI){HAsGFOSGbw = true;}
      if(kZsijBbdKs == LsJDzdsseE){VHfIPeshDD = true;}
      if(jKLompVLaY == JJMcqapSsJ){rBihqyqegs = true;}
      while(fsdlCLSANI == aHPSdsorYz){ybQXarniIX = true;}
      while(LsJDzdsseE == LsJDzdsseE){WQgdpZlBan = true;}
      while(JJMcqapSsJ == JJMcqapSsJ){cggFKxIBCN = true;}
      if(yxwswuPyUJ == true){yxwswuPyUJ = false;}
      if(frIlIEPALT == true){frIlIEPALT = false;}
      if(JqbBNWgAta == true){JqbBNWgAta = false;}
      if(UAHDKOxPGE == true){UAHDKOxPGE = false;}
      if(NuYVYQBZUl == true){NuYVYQBZUl = false;}
      if(KpGYAHVufY == true){KpGYAHVufY = false;}
      if(NODsnekEat == true){NODsnekEat = false;}
      if(HAsGFOSGbw == true){HAsGFOSGbw = false;}
      if(VHfIPeshDD == true){VHfIPeshDD = false;}
      if(rBihqyqegs == true){rBihqyqegs = false;}
      if(fwzZdKwATk == true){fwzZdKwATk = false;}
      if(nPSjDGhtdI == true){nPSjDGhtdI = false;}
      if(lDAXBFQLPG == true){lDAXBFQLPG = false;}
      if(WnYiQYHGdF == true){WnYiQYHGdF = false;}
      if(hsOROcizdk == true){hsOROcizdk = false;}
      if(QwBXHbuaYY == true){QwBXHbuaYY = false;}
      if(tkjMOApjSd == true){tkjMOApjSd = false;}
      if(ybQXarniIX == true){ybQXarniIX = false;}
      if(WQgdpZlBan == true){WQgdpZlBan = false;}
      if(cggFKxIBCN == true){cggFKxIBCN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSYUXKNWBV
{ 
  void udlyfAoqTK()
  { 
      bool eeHAwyCbix = false;
      bool beOlYWmuIA = false;
      bool gYeVlnaAfU = false;
      bool NIPagMjsnY = false;
      bool gFtAfgGyRr = false;
      bool DxjARFzlOI = false;
      bool WBuNjTPmEM = false;
      bool mtGjSaddpE = false;
      bool gbhmQQXOJa = false;
      bool MyeeBeJgPL = false;
      bool RSsFFJpAhp = false;
      bool bUuJbtTHxT = false;
      bool wBdcznObhm = false;
      bool QxOdmNichH = false;
      bool aWfSzqCUDH = false;
      bool LBiwPQoPGQ = false;
      bool uNRuZdGQWO = false;
      bool LqZosYUKdH = false;
      bool ktYaaONRNW = false;
      bool XSVQMMEksU = false;
      string qKFQRgmDxS;
      string IAijupiWrJ;
      string pLbqLDdSdu;
      string eikiOrCFUb;
      string XSCUHUxusE;
      string WdmykeiOFN;
      string CTYBmZOAUC;
      string ndBQkWIGip;
      string GiZYYBumyi;
      string JmAHYEsBgh;
      string FxZqQsbWMN;
      string VbeOHStzbl;
      string dbBlsAdtqg;
      string dHZBkIJhIf;
      string YXZkMgIkzG;
      string JsYuDdunxQ;
      string PhffjOCccy;
      string JLqwMFBQYL;
      string qrtkWjhdyH;
      string MVjqPqrsBy;
      if(qKFQRgmDxS == FxZqQsbWMN){eeHAwyCbix = true;}
      else if(FxZqQsbWMN == qKFQRgmDxS){RSsFFJpAhp = true;}
      if(IAijupiWrJ == VbeOHStzbl){beOlYWmuIA = true;}
      else if(VbeOHStzbl == IAijupiWrJ){bUuJbtTHxT = true;}
      if(pLbqLDdSdu == dbBlsAdtqg){gYeVlnaAfU = true;}
      else if(dbBlsAdtqg == pLbqLDdSdu){wBdcznObhm = true;}
      if(eikiOrCFUb == dHZBkIJhIf){NIPagMjsnY = true;}
      else if(dHZBkIJhIf == eikiOrCFUb){QxOdmNichH = true;}
      if(XSCUHUxusE == YXZkMgIkzG){gFtAfgGyRr = true;}
      else if(YXZkMgIkzG == XSCUHUxusE){aWfSzqCUDH = true;}
      if(WdmykeiOFN == JsYuDdunxQ){DxjARFzlOI = true;}
      else if(JsYuDdunxQ == WdmykeiOFN){LBiwPQoPGQ = true;}
      if(CTYBmZOAUC == PhffjOCccy){WBuNjTPmEM = true;}
      else if(PhffjOCccy == CTYBmZOAUC){uNRuZdGQWO = true;}
      if(ndBQkWIGip == JLqwMFBQYL){mtGjSaddpE = true;}
      if(GiZYYBumyi == qrtkWjhdyH){gbhmQQXOJa = true;}
      if(JmAHYEsBgh == MVjqPqrsBy){MyeeBeJgPL = true;}
      while(JLqwMFBQYL == ndBQkWIGip){LqZosYUKdH = true;}
      while(qrtkWjhdyH == qrtkWjhdyH){ktYaaONRNW = true;}
      while(MVjqPqrsBy == MVjqPqrsBy){XSVQMMEksU = true;}
      if(eeHAwyCbix == true){eeHAwyCbix = false;}
      if(beOlYWmuIA == true){beOlYWmuIA = false;}
      if(gYeVlnaAfU == true){gYeVlnaAfU = false;}
      if(NIPagMjsnY == true){NIPagMjsnY = false;}
      if(gFtAfgGyRr == true){gFtAfgGyRr = false;}
      if(DxjARFzlOI == true){DxjARFzlOI = false;}
      if(WBuNjTPmEM == true){WBuNjTPmEM = false;}
      if(mtGjSaddpE == true){mtGjSaddpE = false;}
      if(gbhmQQXOJa == true){gbhmQQXOJa = false;}
      if(MyeeBeJgPL == true){MyeeBeJgPL = false;}
      if(RSsFFJpAhp == true){RSsFFJpAhp = false;}
      if(bUuJbtTHxT == true){bUuJbtTHxT = false;}
      if(wBdcznObhm == true){wBdcznObhm = false;}
      if(QxOdmNichH == true){QxOdmNichH = false;}
      if(aWfSzqCUDH == true){aWfSzqCUDH = false;}
      if(LBiwPQoPGQ == true){LBiwPQoPGQ = false;}
      if(uNRuZdGQWO == true){uNRuZdGQWO = false;}
      if(LqZosYUKdH == true){LqZosYUKdH = false;}
      if(ktYaaONRNW == true){ktYaaONRNW = false;}
      if(XSVQMMEksU == true){XSVQMMEksU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVSPYCZPYK
{ 
  void ZhkrIrikJm()
  { 
      bool ODpZQtDwnj = false;
      bool hrsEUbrmzQ = false;
      bool qbAmyfaMVq = false;
      bool aoBBBqgYyF = false;
      bool tuEDXLLVUt = false;
      bool tYWJNmDCak = false;
      bool SqawIrprCd = false;
      bool uTntVuWxPl = false;
      bool TFqawCSqnN = false;
      bool ndxNlDUIte = false;
      bool VTSqzakbnR = false;
      bool QGlnQNzzzG = false;
      bool ZzDopQVZHR = false;
      bool ZOCkQzmAbU = false;
      bool QpDVwgrIxX = false;
      bool EVImEVPcBh = false;
      bool FLUWqCDBWQ = false;
      bool azWdpjwgrI = false;
      bool YMcjMEFOfu = false;
      bool iJztPEVfet = false;
      string eliTwwMLGy;
      string wtLGzKcPzl;
      string xdSxBNBBsP;
      string sLuoFietkn;
      string BftfKZGxlj;
      string nxdeiASlSh;
      string uLRqEjyWBQ;
      string fheKkQjmla;
      string HDPJbwhQGF;
      string PrbDspNDaZ;
      string bjwUDFSStR;
      string PfArZquIOI;
      string ChPwAmGbQt;
      string DfLLzXGtFV;
      string dOVnojricB;
      string tFnSXsTAUP;
      string zqCzOiUnsC;
      string kACrenLbGQ;
      string uWyPzyrsmF;
      string DFZpWmMWZF;
      if(eliTwwMLGy == bjwUDFSStR){ODpZQtDwnj = true;}
      else if(bjwUDFSStR == eliTwwMLGy){VTSqzakbnR = true;}
      if(wtLGzKcPzl == PfArZquIOI){hrsEUbrmzQ = true;}
      else if(PfArZquIOI == wtLGzKcPzl){QGlnQNzzzG = true;}
      if(xdSxBNBBsP == ChPwAmGbQt){qbAmyfaMVq = true;}
      else if(ChPwAmGbQt == xdSxBNBBsP){ZzDopQVZHR = true;}
      if(sLuoFietkn == DfLLzXGtFV){aoBBBqgYyF = true;}
      else if(DfLLzXGtFV == sLuoFietkn){ZOCkQzmAbU = true;}
      if(BftfKZGxlj == dOVnojricB){tuEDXLLVUt = true;}
      else if(dOVnojricB == BftfKZGxlj){QpDVwgrIxX = true;}
      if(nxdeiASlSh == tFnSXsTAUP){tYWJNmDCak = true;}
      else if(tFnSXsTAUP == nxdeiASlSh){EVImEVPcBh = true;}
      if(uLRqEjyWBQ == zqCzOiUnsC){SqawIrprCd = true;}
      else if(zqCzOiUnsC == uLRqEjyWBQ){FLUWqCDBWQ = true;}
      if(fheKkQjmla == kACrenLbGQ){uTntVuWxPl = true;}
      if(HDPJbwhQGF == uWyPzyrsmF){TFqawCSqnN = true;}
      if(PrbDspNDaZ == DFZpWmMWZF){ndxNlDUIte = true;}
      while(kACrenLbGQ == fheKkQjmla){azWdpjwgrI = true;}
      while(uWyPzyrsmF == uWyPzyrsmF){YMcjMEFOfu = true;}
      while(DFZpWmMWZF == DFZpWmMWZF){iJztPEVfet = true;}
      if(ODpZQtDwnj == true){ODpZQtDwnj = false;}
      if(hrsEUbrmzQ == true){hrsEUbrmzQ = false;}
      if(qbAmyfaMVq == true){qbAmyfaMVq = false;}
      if(aoBBBqgYyF == true){aoBBBqgYyF = false;}
      if(tuEDXLLVUt == true){tuEDXLLVUt = false;}
      if(tYWJNmDCak == true){tYWJNmDCak = false;}
      if(SqawIrprCd == true){SqawIrprCd = false;}
      if(uTntVuWxPl == true){uTntVuWxPl = false;}
      if(TFqawCSqnN == true){TFqawCSqnN = false;}
      if(ndxNlDUIte == true){ndxNlDUIte = false;}
      if(VTSqzakbnR == true){VTSqzakbnR = false;}
      if(QGlnQNzzzG == true){QGlnQNzzzG = false;}
      if(ZzDopQVZHR == true){ZzDopQVZHR = false;}
      if(ZOCkQzmAbU == true){ZOCkQzmAbU = false;}
      if(QpDVwgrIxX == true){QpDVwgrIxX = false;}
      if(EVImEVPcBh == true){EVImEVPcBh = false;}
      if(FLUWqCDBWQ == true){FLUWqCDBWQ = false;}
      if(azWdpjwgrI == true){azWdpjwgrI = false;}
      if(YMcjMEFOfu == true){YMcjMEFOfu = false;}
      if(iJztPEVfet == true){iJztPEVfet = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YNELZOGQGO
{ 
  void jEZgUGjaMT()
  { 
      bool irHtmYYDBX = false;
      bool MREyIBjisO = false;
      bool bHNHpGmLVP = false;
      bool YkJrAcmziR = false;
      bool xMNIopYezg = false;
      bool aeqFUadzDg = false;
      bool lMhlzbILye = false;
      bool OjAbQPtFRA = false;
      bool gHMnostDXY = false;
      bool ymwBfkeaIN = false;
      bool gMfTSpePnE = false;
      bool fYhDzdzswF = false;
      bool hFmZfanyuf = false;
      bool kSwDTTbrVy = false;
      bool OeOSrZFrBC = false;
      bool kkeDfaYGmq = false;
      bool CfTHTNbdje = false;
      bool CHXxqCqUgG = false;
      bool VuwsuznsXr = false;
      bool tUEewhKGze = false;
      string NoNbhPbVsS;
      string XjxcdKxMLb;
      string leqLSxJQsV;
      string AtEMpSbWfk;
      string caOIyGOMhV;
      string iwZQJhxBIk;
      string FLcWRcekmK;
      string iZgZzLQhNM;
      string hxiXmDUmCH;
      string UaNufRxqpU;
      string adZWlIPARy;
      string ROmwCHbFiO;
      string IqheoIMltg;
      string NYqslDXLke;
      string nUVEpGmRrX;
      string orIbMiuthd;
      string wcFkjsWtKy;
      string jQTEZnVdoi;
      string VtsWqVQPfC;
      string IddHiKOkUw;
      if(NoNbhPbVsS == adZWlIPARy){irHtmYYDBX = true;}
      else if(adZWlIPARy == NoNbhPbVsS){gMfTSpePnE = true;}
      if(XjxcdKxMLb == ROmwCHbFiO){MREyIBjisO = true;}
      else if(ROmwCHbFiO == XjxcdKxMLb){fYhDzdzswF = true;}
      if(leqLSxJQsV == IqheoIMltg){bHNHpGmLVP = true;}
      else if(IqheoIMltg == leqLSxJQsV){hFmZfanyuf = true;}
      if(AtEMpSbWfk == NYqslDXLke){YkJrAcmziR = true;}
      else if(NYqslDXLke == AtEMpSbWfk){kSwDTTbrVy = true;}
      if(caOIyGOMhV == nUVEpGmRrX){xMNIopYezg = true;}
      else if(nUVEpGmRrX == caOIyGOMhV){OeOSrZFrBC = true;}
      if(iwZQJhxBIk == orIbMiuthd){aeqFUadzDg = true;}
      else if(orIbMiuthd == iwZQJhxBIk){kkeDfaYGmq = true;}
      if(FLcWRcekmK == wcFkjsWtKy){lMhlzbILye = true;}
      else if(wcFkjsWtKy == FLcWRcekmK){CfTHTNbdje = true;}
      if(iZgZzLQhNM == jQTEZnVdoi){OjAbQPtFRA = true;}
      if(hxiXmDUmCH == VtsWqVQPfC){gHMnostDXY = true;}
      if(UaNufRxqpU == IddHiKOkUw){ymwBfkeaIN = true;}
      while(jQTEZnVdoi == iZgZzLQhNM){CHXxqCqUgG = true;}
      while(VtsWqVQPfC == VtsWqVQPfC){VuwsuznsXr = true;}
      while(IddHiKOkUw == IddHiKOkUw){tUEewhKGze = true;}
      if(irHtmYYDBX == true){irHtmYYDBX = false;}
      if(MREyIBjisO == true){MREyIBjisO = false;}
      if(bHNHpGmLVP == true){bHNHpGmLVP = false;}
      if(YkJrAcmziR == true){YkJrAcmziR = false;}
      if(xMNIopYezg == true){xMNIopYezg = false;}
      if(aeqFUadzDg == true){aeqFUadzDg = false;}
      if(lMhlzbILye == true){lMhlzbILye = false;}
      if(OjAbQPtFRA == true){OjAbQPtFRA = false;}
      if(gHMnostDXY == true){gHMnostDXY = false;}
      if(ymwBfkeaIN == true){ymwBfkeaIN = false;}
      if(gMfTSpePnE == true){gMfTSpePnE = false;}
      if(fYhDzdzswF == true){fYhDzdzswF = false;}
      if(hFmZfanyuf == true){hFmZfanyuf = false;}
      if(kSwDTTbrVy == true){kSwDTTbrVy = false;}
      if(OeOSrZFrBC == true){OeOSrZFrBC = false;}
      if(kkeDfaYGmq == true){kkeDfaYGmq = false;}
      if(CfTHTNbdje == true){CfTHTNbdje = false;}
      if(CHXxqCqUgG == true){CHXxqCqUgG = false;}
      if(VuwsuznsXr == true){VuwsuznsXr = false;}
      if(tUEewhKGze == true){tUEewhKGze = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVFYLCPOEK
{ 
  void WHJwseGBYf()
  { 
      bool oqHEDTloAN = false;
      bool ADPZMxthbX = false;
      bool NzGZJPefus = false;
      bool MoexjIOTWj = false;
      bool DkxiQfffGY = false;
      bool ArfYKpkhtm = false;
      bool nGsHBLYSoD = false;
      bool iZLqUcBWJc = false;
      bool iyYWrUIFmt = false;
      bool WfYiuxqphE = false;
      bool HNqCoZfnEg = false;
      bool nOXRDogVPg = false;
      bool CSftgCBbwX = false;
      bool kLoFUVHVgR = false;
      bool nUBFGIIHfF = false;
      bool PUaABohxVm = false;
      bool YDrgwbYSwh = false;
      bool hLoxrhRZmY = false;
      bool tswpHPknDf = false;
      bool nJAtrjcUJd = false;
      string YaUyeUjFpT;
      string kmRNYLnbzQ;
      string YFPysmcWmA;
      string SfZeAkTKyA;
      string JhHnbwFeCz;
      string SRxwfTLWEq;
      string qMRpAENmNn;
      string rcdyGqyaVx;
      string hyUmgAhczg;
      string YwGHIxPQnX;
      string hSROHpnyon;
      string UkBGIsqeJz;
      string WjmgOuVVpJ;
      string agmyOPgFfp;
      string MimKLnuzyP;
      string FkHnAxekzM;
      string TRIfNmyDqs;
      string LkzSmmwbUZ;
      string AWXZEoZyxR;
      string jwFSWtaHxX;
      if(YaUyeUjFpT == hSROHpnyon){oqHEDTloAN = true;}
      else if(hSROHpnyon == YaUyeUjFpT){HNqCoZfnEg = true;}
      if(kmRNYLnbzQ == UkBGIsqeJz){ADPZMxthbX = true;}
      else if(UkBGIsqeJz == kmRNYLnbzQ){nOXRDogVPg = true;}
      if(YFPysmcWmA == WjmgOuVVpJ){NzGZJPefus = true;}
      else if(WjmgOuVVpJ == YFPysmcWmA){CSftgCBbwX = true;}
      if(SfZeAkTKyA == agmyOPgFfp){MoexjIOTWj = true;}
      else if(agmyOPgFfp == SfZeAkTKyA){kLoFUVHVgR = true;}
      if(JhHnbwFeCz == MimKLnuzyP){DkxiQfffGY = true;}
      else if(MimKLnuzyP == JhHnbwFeCz){nUBFGIIHfF = true;}
      if(SRxwfTLWEq == FkHnAxekzM){ArfYKpkhtm = true;}
      else if(FkHnAxekzM == SRxwfTLWEq){PUaABohxVm = true;}
      if(qMRpAENmNn == TRIfNmyDqs){nGsHBLYSoD = true;}
      else if(TRIfNmyDqs == qMRpAENmNn){YDrgwbYSwh = true;}
      if(rcdyGqyaVx == LkzSmmwbUZ){iZLqUcBWJc = true;}
      if(hyUmgAhczg == AWXZEoZyxR){iyYWrUIFmt = true;}
      if(YwGHIxPQnX == jwFSWtaHxX){WfYiuxqphE = true;}
      while(LkzSmmwbUZ == rcdyGqyaVx){hLoxrhRZmY = true;}
      while(AWXZEoZyxR == AWXZEoZyxR){tswpHPknDf = true;}
      while(jwFSWtaHxX == jwFSWtaHxX){nJAtrjcUJd = true;}
      if(oqHEDTloAN == true){oqHEDTloAN = false;}
      if(ADPZMxthbX == true){ADPZMxthbX = false;}
      if(NzGZJPefus == true){NzGZJPefus = false;}
      if(MoexjIOTWj == true){MoexjIOTWj = false;}
      if(DkxiQfffGY == true){DkxiQfffGY = false;}
      if(ArfYKpkhtm == true){ArfYKpkhtm = false;}
      if(nGsHBLYSoD == true){nGsHBLYSoD = false;}
      if(iZLqUcBWJc == true){iZLqUcBWJc = false;}
      if(iyYWrUIFmt == true){iyYWrUIFmt = false;}
      if(WfYiuxqphE == true){WfYiuxqphE = false;}
      if(HNqCoZfnEg == true){HNqCoZfnEg = false;}
      if(nOXRDogVPg == true){nOXRDogVPg = false;}
      if(CSftgCBbwX == true){CSftgCBbwX = false;}
      if(kLoFUVHVgR == true){kLoFUVHVgR = false;}
      if(nUBFGIIHfF == true){nUBFGIIHfF = false;}
      if(PUaABohxVm == true){PUaABohxVm = false;}
      if(YDrgwbYSwh == true){YDrgwbYSwh = false;}
      if(hLoxrhRZmY == true){hLoxrhRZmY = false;}
      if(tswpHPknDf == true){tswpHPknDf = false;}
      if(nJAtrjcUJd == true){nJAtrjcUJd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFMPGYNQXT
{ 
  void KwCjlxqTMP()
  { 
      bool nEsAYBHxze = false;
      bool eYJuBkjJtC = false;
      bool WWaASnbyaz = false;
      bool yKoRRmsWXl = false;
      bool JBmwTJYPyU = false;
      bool qJPCFQcrgj = false;
      bool YJWAgTirdO = false;
      bool qNlHsVjdgI = false;
      bool OLAGInumLB = false;
      bool JBomMzdlPz = false;
      bool agljccWIJj = false;
      bool gyLYUMJQrr = false;
      bool YwfbEpXyts = false;
      bool qxOghhZQce = false;
      bool QlcaUKoQRz = false;
      bool pNtWZdBJel = false;
      bool FXNQsiidpm = false;
      bool msmNamTEHt = false;
      bool AHgtDcDrGD = false;
      bool fPkpZrXMhk = false;
      string UdHGOOZYIJ;
      string lrHDTBkowe;
      string hCISqQVDCO;
      string hVdXOrVJGy;
      string MQjKFcYlhU;
      string fQwbHRVnPx;
      string sVVtaQOjoa;
      string eaiySRSxNO;
      string riUgiQYBPw;
      string WhtIFptojo;
      string NnwGpEhyJp;
      string yXaAFJBoLJ;
      string rMTrExfZrb;
      string WcNYADmNqd;
      string iZqYyyGsCu;
      string nFdZxATDCr;
      string XHGgTVKCAC;
      string WmxgZRUutG;
      string qmXwmRymbz;
      string iiLzFaTJFc;
      if(UdHGOOZYIJ == NnwGpEhyJp){nEsAYBHxze = true;}
      else if(NnwGpEhyJp == UdHGOOZYIJ){agljccWIJj = true;}
      if(lrHDTBkowe == yXaAFJBoLJ){eYJuBkjJtC = true;}
      else if(yXaAFJBoLJ == lrHDTBkowe){gyLYUMJQrr = true;}
      if(hCISqQVDCO == rMTrExfZrb){WWaASnbyaz = true;}
      else if(rMTrExfZrb == hCISqQVDCO){YwfbEpXyts = true;}
      if(hVdXOrVJGy == WcNYADmNqd){yKoRRmsWXl = true;}
      else if(WcNYADmNqd == hVdXOrVJGy){qxOghhZQce = true;}
      if(MQjKFcYlhU == iZqYyyGsCu){JBmwTJYPyU = true;}
      else if(iZqYyyGsCu == MQjKFcYlhU){QlcaUKoQRz = true;}
      if(fQwbHRVnPx == nFdZxATDCr){qJPCFQcrgj = true;}
      else if(nFdZxATDCr == fQwbHRVnPx){pNtWZdBJel = true;}
      if(sVVtaQOjoa == XHGgTVKCAC){YJWAgTirdO = true;}
      else if(XHGgTVKCAC == sVVtaQOjoa){FXNQsiidpm = true;}
      if(eaiySRSxNO == WmxgZRUutG){qNlHsVjdgI = true;}
      if(riUgiQYBPw == qmXwmRymbz){OLAGInumLB = true;}
      if(WhtIFptojo == iiLzFaTJFc){JBomMzdlPz = true;}
      while(WmxgZRUutG == eaiySRSxNO){msmNamTEHt = true;}
      while(qmXwmRymbz == qmXwmRymbz){AHgtDcDrGD = true;}
      while(iiLzFaTJFc == iiLzFaTJFc){fPkpZrXMhk = true;}
      if(nEsAYBHxze == true){nEsAYBHxze = false;}
      if(eYJuBkjJtC == true){eYJuBkjJtC = false;}
      if(WWaASnbyaz == true){WWaASnbyaz = false;}
      if(yKoRRmsWXl == true){yKoRRmsWXl = false;}
      if(JBmwTJYPyU == true){JBmwTJYPyU = false;}
      if(qJPCFQcrgj == true){qJPCFQcrgj = false;}
      if(YJWAgTirdO == true){YJWAgTirdO = false;}
      if(qNlHsVjdgI == true){qNlHsVjdgI = false;}
      if(OLAGInumLB == true){OLAGInumLB = false;}
      if(JBomMzdlPz == true){JBomMzdlPz = false;}
      if(agljccWIJj == true){agljccWIJj = false;}
      if(gyLYUMJQrr == true){gyLYUMJQrr = false;}
      if(YwfbEpXyts == true){YwfbEpXyts = false;}
      if(qxOghhZQce == true){qxOghhZQce = false;}
      if(QlcaUKoQRz == true){QlcaUKoQRz = false;}
      if(pNtWZdBJel == true){pNtWZdBJel = false;}
      if(FXNQsiidpm == true){FXNQsiidpm = false;}
      if(msmNamTEHt == true){msmNamTEHt = false;}
      if(AHgtDcDrGD == true){AHgtDcDrGD = false;}
      if(fPkpZrXMhk == true){fPkpZrXMhk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVQPIQWCMJ
{ 
  void TzQpMNMNIG()
  { 
      bool UdxHruziIe = false;
      bool IskFxYDPDQ = false;
      bool RwTAePNAzJ = false;
      bool CEJQxIuAGC = false;
      bool XigRDoOVVD = false;
      bool pgxjxXJxcc = false;
      bool hyjycDiTHn = false;
      bool cCJAriPBwo = false;
      bool BqdwTVHYTZ = false;
      bool yyXcUYzhoA = false;
      bool FtOgZmXwqN = false;
      bool IIBmbpUmeG = false;
      bool wJAhpeeffT = false;
      bool igMwjGcwVg = false;
      bool xKhFRpwjAd = false;
      bool ELDhEutgqu = false;
      bool IrPXdauFDV = false;
      bool NXRxJkbtPA = false;
      bool hteCOXddqn = false;
      bool MwFaXFuJaq = false;
      string fGPuqDCxmk;
      string phqtXXiCdb;
      string LywCMFIOGt;
      string gxlayEBfFi;
      string PffYiQRsQm;
      string ZlPyJhKMil;
      string umpsDruPwT;
      string VCxtMfRWSu;
      string mOxTTugnRP;
      string tnxTnbolUp;
      string VBxxQXoVld;
      string PmsmyfpWZI;
      string LHyfYgEcGj;
      string peBbZkQACw;
      string FLCnzGuKUH;
      string lSMLeNDRXi;
      string SLOBmjlQMM;
      string OpTcDzFKfS;
      string lsIzyWSoxM;
      string hzbScsxAAO;
      if(fGPuqDCxmk == VBxxQXoVld){UdxHruziIe = true;}
      else if(VBxxQXoVld == fGPuqDCxmk){FtOgZmXwqN = true;}
      if(phqtXXiCdb == PmsmyfpWZI){IskFxYDPDQ = true;}
      else if(PmsmyfpWZI == phqtXXiCdb){IIBmbpUmeG = true;}
      if(LywCMFIOGt == LHyfYgEcGj){RwTAePNAzJ = true;}
      else if(LHyfYgEcGj == LywCMFIOGt){wJAhpeeffT = true;}
      if(gxlayEBfFi == peBbZkQACw){CEJQxIuAGC = true;}
      else if(peBbZkQACw == gxlayEBfFi){igMwjGcwVg = true;}
      if(PffYiQRsQm == FLCnzGuKUH){XigRDoOVVD = true;}
      else if(FLCnzGuKUH == PffYiQRsQm){xKhFRpwjAd = true;}
      if(ZlPyJhKMil == lSMLeNDRXi){pgxjxXJxcc = true;}
      else if(lSMLeNDRXi == ZlPyJhKMil){ELDhEutgqu = true;}
      if(umpsDruPwT == SLOBmjlQMM){hyjycDiTHn = true;}
      else if(SLOBmjlQMM == umpsDruPwT){IrPXdauFDV = true;}
      if(VCxtMfRWSu == OpTcDzFKfS){cCJAriPBwo = true;}
      if(mOxTTugnRP == lsIzyWSoxM){BqdwTVHYTZ = true;}
      if(tnxTnbolUp == hzbScsxAAO){yyXcUYzhoA = true;}
      while(OpTcDzFKfS == VCxtMfRWSu){NXRxJkbtPA = true;}
      while(lsIzyWSoxM == lsIzyWSoxM){hteCOXddqn = true;}
      while(hzbScsxAAO == hzbScsxAAO){MwFaXFuJaq = true;}
      if(UdxHruziIe == true){UdxHruziIe = false;}
      if(IskFxYDPDQ == true){IskFxYDPDQ = false;}
      if(RwTAePNAzJ == true){RwTAePNAzJ = false;}
      if(CEJQxIuAGC == true){CEJQxIuAGC = false;}
      if(XigRDoOVVD == true){XigRDoOVVD = false;}
      if(pgxjxXJxcc == true){pgxjxXJxcc = false;}
      if(hyjycDiTHn == true){hyjycDiTHn = false;}
      if(cCJAriPBwo == true){cCJAriPBwo = false;}
      if(BqdwTVHYTZ == true){BqdwTVHYTZ = false;}
      if(yyXcUYzhoA == true){yyXcUYzhoA = false;}
      if(FtOgZmXwqN == true){FtOgZmXwqN = false;}
      if(IIBmbpUmeG == true){IIBmbpUmeG = false;}
      if(wJAhpeeffT == true){wJAhpeeffT = false;}
      if(igMwjGcwVg == true){igMwjGcwVg = false;}
      if(xKhFRpwjAd == true){xKhFRpwjAd = false;}
      if(ELDhEutgqu == true){ELDhEutgqu = false;}
      if(IrPXdauFDV == true){IrPXdauFDV = false;}
      if(NXRxJkbtPA == true){NXRxJkbtPA = false;}
      if(hteCOXddqn == true){hteCOXddqn = false;}
      if(MwFaXFuJaq == true){MwFaXFuJaq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFEBAVDWSF
{ 
  void ugErMUqMcW()
  { 
      bool opagBIUBbi = false;
      bool wFkQNAlxIs = false;
      bool nczdelVImG = false;
      bool fJLofJBSru = false;
      bool eJyssJBgiG = false;
      bool IActHLpxBO = false;
      bool mLOUCmswjD = false;
      bool yTFNNeeFkU = false;
      bool knZgyfgQhT = false;
      bool SEQcHTudqG = false;
      bool QExeHnuOgc = false;
      bool gkLfcykgWV = false;
      bool GbOPjsCbFs = false;
      bool jANeEgqtZJ = false;
      bool kRjFlhskAJ = false;
      bool hNGVznpguN = false;
      bool lSJnrfXgbw = false;
      bool HqHNjorIcC = false;
      bool ARbwKVtqeQ = false;
      bool pJzMXRIwMF = false;
      string YXQXykyemB;
      string NtVboYygbm;
      string TgBayasGWR;
      string ZqEntXXYOz;
      string YAxmDcTiTf;
      string cfoJmqVoYW;
      string qqHUbWohhR;
      string AYScOSjOWV;
      string HJmpotCtBC;
      string BizqHgrbKg;
      string mlBCeDMMuT;
      string HHRDPgERfh;
      string TugfPRZaUg;
      string aHDphUIjKk;
      string gozgusRwba;
      string cawcNrFVlN;
      string dlqNszEbUt;
      string YTGtBduzjV;
      string zcztEALabp;
      string PlyxGtxlnu;
      if(YXQXykyemB == mlBCeDMMuT){opagBIUBbi = true;}
      else if(mlBCeDMMuT == YXQXykyemB){QExeHnuOgc = true;}
      if(NtVboYygbm == HHRDPgERfh){wFkQNAlxIs = true;}
      else if(HHRDPgERfh == NtVboYygbm){gkLfcykgWV = true;}
      if(TgBayasGWR == TugfPRZaUg){nczdelVImG = true;}
      else if(TugfPRZaUg == TgBayasGWR){GbOPjsCbFs = true;}
      if(ZqEntXXYOz == aHDphUIjKk){fJLofJBSru = true;}
      else if(aHDphUIjKk == ZqEntXXYOz){jANeEgqtZJ = true;}
      if(YAxmDcTiTf == gozgusRwba){eJyssJBgiG = true;}
      else if(gozgusRwba == YAxmDcTiTf){kRjFlhskAJ = true;}
      if(cfoJmqVoYW == cawcNrFVlN){IActHLpxBO = true;}
      else if(cawcNrFVlN == cfoJmqVoYW){hNGVznpguN = true;}
      if(qqHUbWohhR == dlqNszEbUt){mLOUCmswjD = true;}
      else if(dlqNszEbUt == qqHUbWohhR){lSJnrfXgbw = true;}
      if(AYScOSjOWV == YTGtBduzjV){yTFNNeeFkU = true;}
      if(HJmpotCtBC == zcztEALabp){knZgyfgQhT = true;}
      if(BizqHgrbKg == PlyxGtxlnu){SEQcHTudqG = true;}
      while(YTGtBduzjV == AYScOSjOWV){HqHNjorIcC = true;}
      while(zcztEALabp == zcztEALabp){ARbwKVtqeQ = true;}
      while(PlyxGtxlnu == PlyxGtxlnu){pJzMXRIwMF = true;}
      if(opagBIUBbi == true){opagBIUBbi = false;}
      if(wFkQNAlxIs == true){wFkQNAlxIs = false;}
      if(nczdelVImG == true){nczdelVImG = false;}
      if(fJLofJBSru == true){fJLofJBSru = false;}
      if(eJyssJBgiG == true){eJyssJBgiG = false;}
      if(IActHLpxBO == true){IActHLpxBO = false;}
      if(mLOUCmswjD == true){mLOUCmswjD = false;}
      if(yTFNNeeFkU == true){yTFNNeeFkU = false;}
      if(knZgyfgQhT == true){knZgyfgQhT = false;}
      if(SEQcHTudqG == true){SEQcHTudqG = false;}
      if(QExeHnuOgc == true){QExeHnuOgc = false;}
      if(gkLfcykgWV == true){gkLfcykgWV = false;}
      if(GbOPjsCbFs == true){GbOPjsCbFs = false;}
      if(jANeEgqtZJ == true){jANeEgqtZJ = false;}
      if(kRjFlhskAJ == true){kRjFlhskAJ = false;}
      if(hNGVznpguN == true){hNGVznpguN = false;}
      if(lSJnrfXgbw == true){lSJnrfXgbw = false;}
      if(HqHNjorIcC == true){HqHNjorIcC = false;}
      if(ARbwKVtqeQ == true){ARbwKVtqeQ = false;}
      if(pJzMXRIwMF == true){pJzMXRIwMF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSMZYAYVHD
{ 
  void YupbrCWZDE()
  { 
      bool XrauPEpYXl = false;
      bool ORMSXKBDUT = false;
      bool KyrApQxHNC = false;
      bool BgmeJBsRcm = false;
      bool mtcbQUDRVe = false;
      bool EwKadYAaEy = false;
      bool HhLUkgehJV = false;
      bool QjahfPUPiV = false;
      bool MelhxEVMBj = false;
      bool BSMeeFiHqi = false;
      bool pVIzNUVctN = false;
      bool EjqikbucWf = false;
      bool KRgYUyWwCZ = false;
      bool gMXAeqVmTc = false;
      bool isSmfRbcsC = false;
      bool JFkLYYoieP = false;
      bool xYZTfqLpDs = false;
      bool GIItwRzssD = false;
      bool WtCzPabMbG = false;
      bool CmHEfJSyHo = false;
      string bJQqyDGiDo;
      string UupyaTwslx;
      string XBpNMVJytE;
      string tlHGTUNZRU;
      string NuCCWVJuJT;
      string caDYuZSCec;
      string sHozuhnjdF;
      string FWaRibznqp;
      string MOoZaSihKs;
      string BKuobFGCHn;
      string hYQDNGzlpS;
      string aeKnQeSOYb;
      string zFYkDtakod;
      string VxfDHmxkMU;
      string TxrqRWAGYx;
      string lrcfnbAfAS;
      string eNwLxdzHfc;
      string hhBDHCNhSg;
      string tTMrqdTAOf;
      string mQkspFAftn;
      if(bJQqyDGiDo == hYQDNGzlpS){XrauPEpYXl = true;}
      else if(hYQDNGzlpS == bJQqyDGiDo){pVIzNUVctN = true;}
      if(UupyaTwslx == aeKnQeSOYb){ORMSXKBDUT = true;}
      else if(aeKnQeSOYb == UupyaTwslx){EjqikbucWf = true;}
      if(XBpNMVJytE == zFYkDtakod){KyrApQxHNC = true;}
      else if(zFYkDtakod == XBpNMVJytE){KRgYUyWwCZ = true;}
      if(tlHGTUNZRU == VxfDHmxkMU){BgmeJBsRcm = true;}
      else if(VxfDHmxkMU == tlHGTUNZRU){gMXAeqVmTc = true;}
      if(NuCCWVJuJT == TxrqRWAGYx){mtcbQUDRVe = true;}
      else if(TxrqRWAGYx == NuCCWVJuJT){isSmfRbcsC = true;}
      if(caDYuZSCec == lrcfnbAfAS){EwKadYAaEy = true;}
      else if(lrcfnbAfAS == caDYuZSCec){JFkLYYoieP = true;}
      if(sHozuhnjdF == eNwLxdzHfc){HhLUkgehJV = true;}
      else if(eNwLxdzHfc == sHozuhnjdF){xYZTfqLpDs = true;}
      if(FWaRibznqp == hhBDHCNhSg){QjahfPUPiV = true;}
      if(MOoZaSihKs == tTMrqdTAOf){MelhxEVMBj = true;}
      if(BKuobFGCHn == mQkspFAftn){BSMeeFiHqi = true;}
      while(hhBDHCNhSg == FWaRibznqp){GIItwRzssD = true;}
      while(tTMrqdTAOf == tTMrqdTAOf){WtCzPabMbG = true;}
      while(mQkspFAftn == mQkspFAftn){CmHEfJSyHo = true;}
      if(XrauPEpYXl == true){XrauPEpYXl = false;}
      if(ORMSXKBDUT == true){ORMSXKBDUT = false;}
      if(KyrApQxHNC == true){KyrApQxHNC = false;}
      if(BgmeJBsRcm == true){BgmeJBsRcm = false;}
      if(mtcbQUDRVe == true){mtcbQUDRVe = false;}
      if(EwKadYAaEy == true){EwKadYAaEy = false;}
      if(HhLUkgehJV == true){HhLUkgehJV = false;}
      if(QjahfPUPiV == true){QjahfPUPiV = false;}
      if(MelhxEVMBj == true){MelhxEVMBj = false;}
      if(BSMeeFiHqi == true){BSMeeFiHqi = false;}
      if(pVIzNUVctN == true){pVIzNUVctN = false;}
      if(EjqikbucWf == true){EjqikbucWf = false;}
      if(KRgYUyWwCZ == true){KRgYUyWwCZ = false;}
      if(gMXAeqVmTc == true){gMXAeqVmTc = false;}
      if(isSmfRbcsC == true){isSmfRbcsC = false;}
      if(JFkLYYoieP == true){JFkLYYoieP = false;}
      if(xYZTfqLpDs == true){xYZTfqLpDs = false;}
      if(GIItwRzssD == true){GIItwRzssD = false;}
      if(WtCzPabMbG == true){WtCzPabMbG = false;}
      if(CmHEfJSyHo == true){CmHEfJSyHo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AMUHFDSYSG
{ 
  void rswRDHjNOB()
  { 
      bool NISHbRsCKc = false;
      bool tBWMLhEeeI = false;
      bool VKrWCaVGfR = false;
      bool QteHPrCuNb = false;
      bool fUoIbRJjZY = false;
      bool gmmUXDPuFB = false;
      bool umVrMAVPwT = false;
      bool fIRDbBUiuk = false;
      bool RlfHkcGKiM = false;
      bool bHpLfsyxwb = false;
      bool wsmGsXVjsW = false;
      bool hgAUjJGNGj = false;
      bool sKfjqXSGWh = false;
      bool CWmSnXzZOM = false;
      bool HWRMduGUaW = false;
      bool mjpMikNCOU = false;
      bool EONKTKsgfM = false;
      bool KgztbWsTGw = false;
      bool RxeAuRgajC = false;
      bool KwKtHrIHrS = false;
      string GOhZOnFtJK;
      string yRPorfZomq;
      string MtQVHJMVDJ;
      string esQpGtbEfU;
      string YVpqnODwpE;
      string JxLVkLyLRE;
      string ajqzfEBYiy;
      string EVISSpEZhr;
      string GQezzhguFt;
      string wQlbsndpLi;
      string NdMrAnnsDt;
      string HXcYyKErzx;
      string WFTnBmigYd;
      string MNNyecDmyL;
      string snrKmXmNci;
      string jlpNMHJXpM;
      string EHUYhsKetV;
      string GRsnDiNIBd;
      string AVDotZWzlW;
      string SfwlHkSSct;
      if(GOhZOnFtJK == NdMrAnnsDt){NISHbRsCKc = true;}
      else if(NdMrAnnsDt == GOhZOnFtJK){wsmGsXVjsW = true;}
      if(yRPorfZomq == HXcYyKErzx){tBWMLhEeeI = true;}
      else if(HXcYyKErzx == yRPorfZomq){hgAUjJGNGj = true;}
      if(MtQVHJMVDJ == WFTnBmigYd){VKrWCaVGfR = true;}
      else if(WFTnBmigYd == MtQVHJMVDJ){sKfjqXSGWh = true;}
      if(esQpGtbEfU == MNNyecDmyL){QteHPrCuNb = true;}
      else if(MNNyecDmyL == esQpGtbEfU){CWmSnXzZOM = true;}
      if(YVpqnODwpE == snrKmXmNci){fUoIbRJjZY = true;}
      else if(snrKmXmNci == YVpqnODwpE){HWRMduGUaW = true;}
      if(JxLVkLyLRE == jlpNMHJXpM){gmmUXDPuFB = true;}
      else if(jlpNMHJXpM == JxLVkLyLRE){mjpMikNCOU = true;}
      if(ajqzfEBYiy == EHUYhsKetV){umVrMAVPwT = true;}
      else if(EHUYhsKetV == ajqzfEBYiy){EONKTKsgfM = true;}
      if(EVISSpEZhr == GRsnDiNIBd){fIRDbBUiuk = true;}
      if(GQezzhguFt == AVDotZWzlW){RlfHkcGKiM = true;}
      if(wQlbsndpLi == SfwlHkSSct){bHpLfsyxwb = true;}
      while(GRsnDiNIBd == EVISSpEZhr){KgztbWsTGw = true;}
      while(AVDotZWzlW == AVDotZWzlW){RxeAuRgajC = true;}
      while(SfwlHkSSct == SfwlHkSSct){KwKtHrIHrS = true;}
      if(NISHbRsCKc == true){NISHbRsCKc = false;}
      if(tBWMLhEeeI == true){tBWMLhEeeI = false;}
      if(VKrWCaVGfR == true){VKrWCaVGfR = false;}
      if(QteHPrCuNb == true){QteHPrCuNb = false;}
      if(fUoIbRJjZY == true){fUoIbRJjZY = false;}
      if(gmmUXDPuFB == true){gmmUXDPuFB = false;}
      if(umVrMAVPwT == true){umVrMAVPwT = false;}
      if(fIRDbBUiuk == true){fIRDbBUiuk = false;}
      if(RlfHkcGKiM == true){RlfHkcGKiM = false;}
      if(bHpLfsyxwb == true){bHpLfsyxwb = false;}
      if(wsmGsXVjsW == true){wsmGsXVjsW = false;}
      if(hgAUjJGNGj == true){hgAUjJGNGj = false;}
      if(sKfjqXSGWh == true){sKfjqXSGWh = false;}
      if(CWmSnXzZOM == true){CWmSnXzZOM = false;}
      if(HWRMduGUaW == true){HWRMduGUaW = false;}
      if(mjpMikNCOU == true){mjpMikNCOU = false;}
      if(EONKTKsgfM == true){EONKTKsgfM = false;}
      if(KgztbWsTGw == true){KgztbWsTGw = false;}
      if(RxeAuRgajC == true){RxeAuRgajC = false;}
      if(KwKtHrIHrS == true){KwKtHrIHrS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JLCUTWFZXD
{ 
  void kwkZmFpCMz()
  { 
      bool mVNiBZZDqw = false;
      bool POyyJiQzYH = false;
      bool nzJHBkwQdq = false;
      bool WUwuzisytr = false;
      bool djRHFSdBut = false;
      bool CbnZQmMFgQ = false;
      bool cIYAYuRDyZ = false;
      bool oREgcDhBBi = false;
      bool GtUjntfWeL = false;
      bool WnRdOULRhK = false;
      bool BaDUEkXHwN = false;
      bool FKDxJinoLe = false;
      bool OuXlDBzaRI = false;
      bool rPSphfqzeD = false;
      bool WYZRGLjTTe = false;
      bool gVGDwGCQRD = false;
      bool kxonUorMPd = false;
      bool rnKHHoUGfr = false;
      bool QfGmaVJPtb = false;
      bool cZhaSZikwQ = false;
      string RDIAUWJUQc;
      string xRMGNJYxRf;
      string ZFBeBYZWJh;
      string mzApSQYlWB;
      string osUQPzkSQn;
      string ZXVToLCcyw;
      string xlKhoyRWmx;
      string klZPpgkjPB;
      string mHFVHOcgAH;
      string NwnZECilaQ;
      string hOeTDnyGcI;
      string aRMxIognaZ;
      string VkVfinyzKm;
      string yzJzSYbkSS;
      string QWDrfuiqRO;
      string VtKAuxrykO;
      string pyupKbINdi;
      string NwUHJyhdAm;
      string FGhwRDnIEV;
      string gczEcSbMgE;
      if(RDIAUWJUQc == hOeTDnyGcI){mVNiBZZDqw = true;}
      else if(hOeTDnyGcI == RDIAUWJUQc){BaDUEkXHwN = true;}
      if(xRMGNJYxRf == aRMxIognaZ){POyyJiQzYH = true;}
      else if(aRMxIognaZ == xRMGNJYxRf){FKDxJinoLe = true;}
      if(ZFBeBYZWJh == VkVfinyzKm){nzJHBkwQdq = true;}
      else if(VkVfinyzKm == ZFBeBYZWJh){OuXlDBzaRI = true;}
      if(mzApSQYlWB == yzJzSYbkSS){WUwuzisytr = true;}
      else if(yzJzSYbkSS == mzApSQYlWB){rPSphfqzeD = true;}
      if(osUQPzkSQn == QWDrfuiqRO){djRHFSdBut = true;}
      else if(QWDrfuiqRO == osUQPzkSQn){WYZRGLjTTe = true;}
      if(ZXVToLCcyw == VtKAuxrykO){CbnZQmMFgQ = true;}
      else if(VtKAuxrykO == ZXVToLCcyw){gVGDwGCQRD = true;}
      if(xlKhoyRWmx == pyupKbINdi){cIYAYuRDyZ = true;}
      else if(pyupKbINdi == xlKhoyRWmx){kxonUorMPd = true;}
      if(klZPpgkjPB == NwUHJyhdAm){oREgcDhBBi = true;}
      if(mHFVHOcgAH == FGhwRDnIEV){GtUjntfWeL = true;}
      if(NwnZECilaQ == gczEcSbMgE){WnRdOULRhK = true;}
      while(NwUHJyhdAm == klZPpgkjPB){rnKHHoUGfr = true;}
      while(FGhwRDnIEV == FGhwRDnIEV){QfGmaVJPtb = true;}
      while(gczEcSbMgE == gczEcSbMgE){cZhaSZikwQ = true;}
      if(mVNiBZZDqw == true){mVNiBZZDqw = false;}
      if(POyyJiQzYH == true){POyyJiQzYH = false;}
      if(nzJHBkwQdq == true){nzJHBkwQdq = false;}
      if(WUwuzisytr == true){WUwuzisytr = false;}
      if(djRHFSdBut == true){djRHFSdBut = false;}
      if(CbnZQmMFgQ == true){CbnZQmMFgQ = false;}
      if(cIYAYuRDyZ == true){cIYAYuRDyZ = false;}
      if(oREgcDhBBi == true){oREgcDhBBi = false;}
      if(GtUjntfWeL == true){GtUjntfWeL = false;}
      if(WnRdOULRhK == true){WnRdOULRhK = false;}
      if(BaDUEkXHwN == true){BaDUEkXHwN = false;}
      if(FKDxJinoLe == true){FKDxJinoLe = false;}
      if(OuXlDBzaRI == true){OuXlDBzaRI = false;}
      if(rPSphfqzeD == true){rPSphfqzeD = false;}
      if(WYZRGLjTTe == true){WYZRGLjTTe = false;}
      if(gVGDwGCQRD == true){gVGDwGCQRD = false;}
      if(kxonUorMPd == true){kxonUorMPd = false;}
      if(rnKHHoUGfr == true){rnKHHoUGfr = false;}
      if(QfGmaVJPtb == true){QfGmaVJPtb = false;}
      if(cZhaSZikwQ == true){cZhaSZikwQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPMBESCPJG
{ 
  void XUVkTxqWIU()
  { 
      bool qDsrSKGpBL = false;
      bool GVlhxTRdhA = false;
      bool wRdyBNMIbC = false;
      bool GqegXjbmPy = false;
      bool MaVDfIyjrZ = false;
      bool tnuJHZYtqE = false;
      bool yxOzEPqFKN = false;
      bool qdNimUuaRr = false;
      bool ObPBHSuUZy = false;
      bool KhwLzPMWyQ = false;
      bool RsZehPZLWm = false;
      bool dybyoVgNql = false;
      bool TVfLCJhCiX = false;
      bool IXcBaVCkSq = false;
      bool rjymTLFxWc = false;
      bool hzfLwuNNbY = false;
      bool hXcydFUZXS = false;
      bool TwtzsjXsrq = false;
      bool EjfFpJrQFe = false;
      bool HoItJUHzIN = false;
      string lCRciHHUat;
      string alELRJpimR;
      string BwyexqSGyu;
      string KdkOzMeKkO;
      string jAyXmRVkyB;
      string UzlYspDlfq;
      string oBWfixBpLE;
      string dexYhBxaqe;
      string VgIxZLrLVJ;
      string IretYhdSnp;
      string QeYsWoBMqq;
      string rbuAVHsYGX;
      string EoTBukADAz;
      string XemBOpIOaj;
      string JeUdQfxeXR;
      string oEMPlaLWxk;
      string oxMqTNoslf;
      string zdyVOZTojO;
      string nUfhJSRXPm;
      string ekRotMScKD;
      if(lCRciHHUat == QeYsWoBMqq){qDsrSKGpBL = true;}
      else if(QeYsWoBMqq == lCRciHHUat){RsZehPZLWm = true;}
      if(alELRJpimR == rbuAVHsYGX){GVlhxTRdhA = true;}
      else if(rbuAVHsYGX == alELRJpimR){dybyoVgNql = true;}
      if(BwyexqSGyu == EoTBukADAz){wRdyBNMIbC = true;}
      else if(EoTBukADAz == BwyexqSGyu){TVfLCJhCiX = true;}
      if(KdkOzMeKkO == XemBOpIOaj){GqegXjbmPy = true;}
      else if(XemBOpIOaj == KdkOzMeKkO){IXcBaVCkSq = true;}
      if(jAyXmRVkyB == JeUdQfxeXR){MaVDfIyjrZ = true;}
      else if(JeUdQfxeXR == jAyXmRVkyB){rjymTLFxWc = true;}
      if(UzlYspDlfq == oEMPlaLWxk){tnuJHZYtqE = true;}
      else if(oEMPlaLWxk == UzlYspDlfq){hzfLwuNNbY = true;}
      if(oBWfixBpLE == oxMqTNoslf){yxOzEPqFKN = true;}
      else if(oxMqTNoslf == oBWfixBpLE){hXcydFUZXS = true;}
      if(dexYhBxaqe == zdyVOZTojO){qdNimUuaRr = true;}
      if(VgIxZLrLVJ == nUfhJSRXPm){ObPBHSuUZy = true;}
      if(IretYhdSnp == ekRotMScKD){KhwLzPMWyQ = true;}
      while(zdyVOZTojO == dexYhBxaqe){TwtzsjXsrq = true;}
      while(nUfhJSRXPm == nUfhJSRXPm){EjfFpJrQFe = true;}
      while(ekRotMScKD == ekRotMScKD){HoItJUHzIN = true;}
      if(qDsrSKGpBL == true){qDsrSKGpBL = false;}
      if(GVlhxTRdhA == true){GVlhxTRdhA = false;}
      if(wRdyBNMIbC == true){wRdyBNMIbC = false;}
      if(GqegXjbmPy == true){GqegXjbmPy = false;}
      if(MaVDfIyjrZ == true){MaVDfIyjrZ = false;}
      if(tnuJHZYtqE == true){tnuJHZYtqE = false;}
      if(yxOzEPqFKN == true){yxOzEPqFKN = false;}
      if(qdNimUuaRr == true){qdNimUuaRr = false;}
      if(ObPBHSuUZy == true){ObPBHSuUZy = false;}
      if(KhwLzPMWyQ == true){KhwLzPMWyQ = false;}
      if(RsZehPZLWm == true){RsZehPZLWm = false;}
      if(dybyoVgNql == true){dybyoVgNql = false;}
      if(TVfLCJhCiX == true){TVfLCJhCiX = false;}
      if(IXcBaVCkSq == true){IXcBaVCkSq = false;}
      if(rjymTLFxWc == true){rjymTLFxWc = false;}
      if(hzfLwuNNbY == true){hzfLwuNNbY = false;}
      if(hXcydFUZXS == true){hXcydFUZXS = false;}
      if(TwtzsjXsrq == true){TwtzsjXsrq = false;}
      if(EjfFpJrQFe == true){EjfFpJrQFe = false;}
      if(HoItJUHzIN == true){HoItJUHzIN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRQKCARJQG
{ 
  void HMwOSnBNfZ()
  { 
      bool aqwJeHskGV = false;
      bool GbcKzkNQfj = false;
      bool lSbbrSQliQ = false;
      bool HqSZDAlLXU = false;
      bool iDpbJqfLSQ = false;
      bool ZRxpFHOUQL = false;
      bool qGBpOOICHy = false;
      bool yBrKBiczRB = false;
      bool lETRpptbUu = false;
      bool kRtMcbBANt = false;
      bool hcETSXZloV = false;
      bool ePDPZmmizY = false;
      bool UghLNgGfgY = false;
      bool gckWSIAzzS = false;
      bool PHmyPVOdlp = false;
      bool oSAoZBurGk = false;
      bool QtFPnCdfxQ = false;
      bool lmjgINsiwq = false;
      bool SbsqjObuxQ = false;
      bool MIsNBVCWKN = false;
      string VdwwrPkwcI;
      string cnFUYThWwY;
      string UtIsjBBSYE;
      string iEOyflGkLA;
      string JiDMcIJSxO;
      string okYuXbUCLq;
      string ORXXYXZHnm;
      string NxLwOkpwQa;
      string qhUJPxeSZE;
      string QDYUlqLemE;
      string iCeKArZcfl;
      string kYljzfwNIb;
      string rHgjVJXpJX;
      string ZKILrnDKJW;
      string WClmSqRnUG;
      string txWLMbVtnq;
      string UiTIMaQarL;
      string blElEpUsRd;
      string qiVDcbnxyQ;
      string SJVRCnhcaq;
      if(VdwwrPkwcI == iCeKArZcfl){aqwJeHskGV = true;}
      else if(iCeKArZcfl == VdwwrPkwcI){hcETSXZloV = true;}
      if(cnFUYThWwY == kYljzfwNIb){GbcKzkNQfj = true;}
      else if(kYljzfwNIb == cnFUYThWwY){ePDPZmmizY = true;}
      if(UtIsjBBSYE == rHgjVJXpJX){lSbbrSQliQ = true;}
      else if(rHgjVJXpJX == UtIsjBBSYE){UghLNgGfgY = true;}
      if(iEOyflGkLA == ZKILrnDKJW){HqSZDAlLXU = true;}
      else if(ZKILrnDKJW == iEOyflGkLA){gckWSIAzzS = true;}
      if(JiDMcIJSxO == WClmSqRnUG){iDpbJqfLSQ = true;}
      else if(WClmSqRnUG == JiDMcIJSxO){PHmyPVOdlp = true;}
      if(okYuXbUCLq == txWLMbVtnq){ZRxpFHOUQL = true;}
      else if(txWLMbVtnq == okYuXbUCLq){oSAoZBurGk = true;}
      if(ORXXYXZHnm == UiTIMaQarL){qGBpOOICHy = true;}
      else if(UiTIMaQarL == ORXXYXZHnm){QtFPnCdfxQ = true;}
      if(NxLwOkpwQa == blElEpUsRd){yBrKBiczRB = true;}
      if(qhUJPxeSZE == qiVDcbnxyQ){lETRpptbUu = true;}
      if(QDYUlqLemE == SJVRCnhcaq){kRtMcbBANt = true;}
      while(blElEpUsRd == NxLwOkpwQa){lmjgINsiwq = true;}
      while(qiVDcbnxyQ == qiVDcbnxyQ){SbsqjObuxQ = true;}
      while(SJVRCnhcaq == SJVRCnhcaq){MIsNBVCWKN = true;}
      if(aqwJeHskGV == true){aqwJeHskGV = false;}
      if(GbcKzkNQfj == true){GbcKzkNQfj = false;}
      if(lSbbrSQliQ == true){lSbbrSQliQ = false;}
      if(HqSZDAlLXU == true){HqSZDAlLXU = false;}
      if(iDpbJqfLSQ == true){iDpbJqfLSQ = false;}
      if(ZRxpFHOUQL == true){ZRxpFHOUQL = false;}
      if(qGBpOOICHy == true){qGBpOOICHy = false;}
      if(yBrKBiczRB == true){yBrKBiczRB = false;}
      if(lETRpptbUu == true){lETRpptbUu = false;}
      if(kRtMcbBANt == true){kRtMcbBANt = false;}
      if(hcETSXZloV == true){hcETSXZloV = false;}
      if(ePDPZmmizY == true){ePDPZmmizY = false;}
      if(UghLNgGfgY == true){UghLNgGfgY = false;}
      if(gckWSIAzzS == true){gckWSIAzzS = false;}
      if(PHmyPVOdlp == true){PHmyPVOdlp = false;}
      if(oSAoZBurGk == true){oSAoZBurGk = false;}
      if(QtFPnCdfxQ == true){QtFPnCdfxQ = false;}
      if(lmjgINsiwq == true){lmjgINsiwq = false;}
      if(SbsqjObuxQ == true){SbsqjObuxQ = false;}
      if(MIsNBVCWKN == true){MIsNBVCWKN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPTYUPIWRE
{ 
  void rWhSWJYdFj()
  { 
      bool fZqkQsDFam = false;
      bool WQnWfsSpUf = false;
      bool ruGASLVmep = false;
      bool hJbNffqDmn = false;
      bool lWMnZaWWfr = false;
      bool ZyxjukSqSE = false;
      bool WPZjEMoapA = false;
      bool BPDftVhRZq = false;
      bool ozGmPiMrRu = false;
      bool NAjhQVwbjM = false;
      bool luffpKuQpZ = false;
      bool DAQbPXJmUU = false;
      bool AxIumBeUPX = false;
      bool YFhMFsSawF = false;
      bool nuBrrMiISs = false;
      bool MIHPMnmkro = false;
      bool faBRAxREVV = false;
      bool EhqOgEuPDZ = false;
      bool RVBWLQxSAR = false;
      bool GhhGYMtjrt = false;
      string wzVWwUDkOS;
      string pBnZwoXCwW;
      string xiXyoyrWmW;
      string kMtLnXzPGq;
      string fAoctAMnio;
      string IoqhLMbXhx;
      string cfxqgcGblX;
      string oHuFpwttDn;
      string kDnyOwVLza;
      string wbhINADxwR;
      string sjBKzBtlrO;
      string RgTsLZrzck;
      string HubKbNYlrp;
      string sxyluACczM;
      string BiTkJOHown;
      string IDUKKyIpil;
      string bItBVUihxK;
      string XOAPjXaqBM;
      string FioDgobnax;
      string rLsMksoRPn;
      if(wzVWwUDkOS == sjBKzBtlrO){fZqkQsDFam = true;}
      else if(sjBKzBtlrO == wzVWwUDkOS){luffpKuQpZ = true;}
      if(pBnZwoXCwW == RgTsLZrzck){WQnWfsSpUf = true;}
      else if(RgTsLZrzck == pBnZwoXCwW){DAQbPXJmUU = true;}
      if(xiXyoyrWmW == HubKbNYlrp){ruGASLVmep = true;}
      else if(HubKbNYlrp == xiXyoyrWmW){AxIumBeUPX = true;}
      if(kMtLnXzPGq == sxyluACczM){hJbNffqDmn = true;}
      else if(sxyluACczM == kMtLnXzPGq){YFhMFsSawF = true;}
      if(fAoctAMnio == BiTkJOHown){lWMnZaWWfr = true;}
      else if(BiTkJOHown == fAoctAMnio){nuBrrMiISs = true;}
      if(IoqhLMbXhx == IDUKKyIpil){ZyxjukSqSE = true;}
      else if(IDUKKyIpil == IoqhLMbXhx){MIHPMnmkro = true;}
      if(cfxqgcGblX == bItBVUihxK){WPZjEMoapA = true;}
      else if(bItBVUihxK == cfxqgcGblX){faBRAxREVV = true;}
      if(oHuFpwttDn == XOAPjXaqBM){BPDftVhRZq = true;}
      if(kDnyOwVLza == FioDgobnax){ozGmPiMrRu = true;}
      if(wbhINADxwR == rLsMksoRPn){NAjhQVwbjM = true;}
      while(XOAPjXaqBM == oHuFpwttDn){EhqOgEuPDZ = true;}
      while(FioDgobnax == FioDgobnax){RVBWLQxSAR = true;}
      while(rLsMksoRPn == rLsMksoRPn){GhhGYMtjrt = true;}
      if(fZqkQsDFam == true){fZqkQsDFam = false;}
      if(WQnWfsSpUf == true){WQnWfsSpUf = false;}
      if(ruGASLVmep == true){ruGASLVmep = false;}
      if(hJbNffqDmn == true){hJbNffqDmn = false;}
      if(lWMnZaWWfr == true){lWMnZaWWfr = false;}
      if(ZyxjukSqSE == true){ZyxjukSqSE = false;}
      if(WPZjEMoapA == true){WPZjEMoapA = false;}
      if(BPDftVhRZq == true){BPDftVhRZq = false;}
      if(ozGmPiMrRu == true){ozGmPiMrRu = false;}
      if(NAjhQVwbjM == true){NAjhQVwbjM = false;}
      if(luffpKuQpZ == true){luffpKuQpZ = false;}
      if(DAQbPXJmUU == true){DAQbPXJmUU = false;}
      if(AxIumBeUPX == true){AxIumBeUPX = false;}
      if(YFhMFsSawF == true){YFhMFsSawF = false;}
      if(nuBrrMiISs == true){nuBrrMiISs = false;}
      if(MIHPMnmkro == true){MIHPMnmkro = false;}
      if(faBRAxREVV == true){faBRAxREVV = false;}
      if(EhqOgEuPDZ == true){EhqOgEuPDZ = false;}
      if(RVBWLQxSAR == true){RVBWLQxSAR = false;}
      if(GhhGYMtjrt == true){GhhGYMtjrt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJUMLMQIPF
{ 
  void sHgYnfsUQJ()
  { 
      bool KGDaoobhDd = false;
      bool VnunCkqXTQ = false;
      bool MQLLdCajOw = false;
      bool XegoZigLeJ = false;
      bool XFeKDSOjMQ = false;
      bool PreXqtuqxm = false;
      bool NqTHGpHFNT = false;
      bool EerJsGlBIK = false;
      bool nqXxfezJyf = false;
      bool moOrwflWDM = false;
      bool LIWrLkAVdj = false;
      bool HsilzWTVab = false;
      bool pyHgfOQANM = false;
      bool UOxwzeUflu = false;
      bool ddeNYtGbsZ = false;
      bool MPwbVMAoLw = false;
      bool UAIROrwmmT = false;
      bool CmjexLSsIl = false;
      bool InHmAFSVZl = false;
      bool deToadVNyg = false;
      string eNqYQQADwI;
      string xdatYGHiuc;
      string ASkLqKRjyo;
      string FZHCDcthUL;
      string CntznTIeRB;
      string UqzhELbehF;
      string yPEHCXWXpw;
      string LZOjZLYlXW;
      string CmSxTNZZxr;
      string AOzPMljlwQ;
      string xjnUoucPHr;
      string moHKDKxHnn;
      string yxZywxZyWn;
      string blpGZRzxHX;
      string kJSFEKHoLB;
      string obyHSAJoYr;
      string VdsSQAzAkk;
      string LzzPDneUsk;
      string ojmUzznhnY;
      string HJXOBHQznE;
      if(eNqYQQADwI == xjnUoucPHr){KGDaoobhDd = true;}
      else if(xjnUoucPHr == eNqYQQADwI){LIWrLkAVdj = true;}
      if(xdatYGHiuc == moHKDKxHnn){VnunCkqXTQ = true;}
      else if(moHKDKxHnn == xdatYGHiuc){HsilzWTVab = true;}
      if(ASkLqKRjyo == yxZywxZyWn){MQLLdCajOw = true;}
      else if(yxZywxZyWn == ASkLqKRjyo){pyHgfOQANM = true;}
      if(FZHCDcthUL == blpGZRzxHX){XegoZigLeJ = true;}
      else if(blpGZRzxHX == FZHCDcthUL){UOxwzeUflu = true;}
      if(CntznTIeRB == kJSFEKHoLB){XFeKDSOjMQ = true;}
      else if(kJSFEKHoLB == CntznTIeRB){ddeNYtGbsZ = true;}
      if(UqzhELbehF == obyHSAJoYr){PreXqtuqxm = true;}
      else if(obyHSAJoYr == UqzhELbehF){MPwbVMAoLw = true;}
      if(yPEHCXWXpw == VdsSQAzAkk){NqTHGpHFNT = true;}
      else if(VdsSQAzAkk == yPEHCXWXpw){UAIROrwmmT = true;}
      if(LZOjZLYlXW == LzzPDneUsk){EerJsGlBIK = true;}
      if(CmSxTNZZxr == ojmUzznhnY){nqXxfezJyf = true;}
      if(AOzPMljlwQ == HJXOBHQznE){moOrwflWDM = true;}
      while(LzzPDneUsk == LZOjZLYlXW){CmjexLSsIl = true;}
      while(ojmUzznhnY == ojmUzznhnY){InHmAFSVZl = true;}
      while(HJXOBHQznE == HJXOBHQznE){deToadVNyg = true;}
      if(KGDaoobhDd == true){KGDaoobhDd = false;}
      if(VnunCkqXTQ == true){VnunCkqXTQ = false;}
      if(MQLLdCajOw == true){MQLLdCajOw = false;}
      if(XegoZigLeJ == true){XegoZigLeJ = false;}
      if(XFeKDSOjMQ == true){XFeKDSOjMQ = false;}
      if(PreXqtuqxm == true){PreXqtuqxm = false;}
      if(NqTHGpHFNT == true){NqTHGpHFNT = false;}
      if(EerJsGlBIK == true){EerJsGlBIK = false;}
      if(nqXxfezJyf == true){nqXxfezJyf = false;}
      if(moOrwflWDM == true){moOrwflWDM = false;}
      if(LIWrLkAVdj == true){LIWrLkAVdj = false;}
      if(HsilzWTVab == true){HsilzWTVab = false;}
      if(pyHgfOQANM == true){pyHgfOQANM = false;}
      if(UOxwzeUflu == true){UOxwzeUflu = false;}
      if(ddeNYtGbsZ == true){ddeNYtGbsZ = false;}
      if(MPwbVMAoLw == true){MPwbVMAoLw = false;}
      if(UAIROrwmmT == true){UAIROrwmmT = false;}
      if(CmjexLSsIl == true){CmjexLSsIl = false;}
      if(InHmAFSVZl == true){InHmAFSVZl = false;}
      if(deToadVNyg == true){deToadVNyg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTUHMBAMDU
{ 
  void AaoBaFkwcm()
  { 
      bool kJfsACclQY = false;
      bool tABwTVeebM = false;
      bool ndPFHptacy = false;
      bool anZWgZhEYc = false;
      bool BwTHXBiGeK = false;
      bool DKIOtHtakJ = false;
      bool IBJRxGaePt = false;
      bool mZFzKrJIhG = false;
      bool HmwSuPfKbZ = false;
      bool eHTPTzmCJR = false;
      bool aEqjWdEIEB = false;
      bool xlreBUEpWg = false;
      bool ZQCoOfGpeK = false;
      bool FHyQeCuLuR = false;
      bool LXFacsPoNy = false;
      bool uwecqKCBVq = false;
      bool WOcswombzy = false;
      bool YruFVCKaMU = false;
      bool QRcgPIcVYU = false;
      bool AtpEtwtMem = false;
      string UjVqyRNaGe;
      string DHrdpXlaIX;
      string RSIgGJryCK;
      string rsKeKYLBGQ;
      string dERfKhikyG;
      string ozufmCanjn;
      string YPYumJwMTQ;
      string MkTqtNAcWY;
      string ZHzwUryerI;
      string yWQRqOfVsB;
      string lWRgsEfDlY;
      string CyRLNQPbZt;
      string LRULSoTCze;
      string heiVmDpRCQ;
      string MtrSGAFFDa;
      string zDuypTBGOD;
      string jdEHqWOuYK;
      string axZJhQYBFS;
      string jOyYeeijfS;
      string CjDyfipkbi;
      if(UjVqyRNaGe == lWRgsEfDlY){kJfsACclQY = true;}
      else if(lWRgsEfDlY == UjVqyRNaGe){aEqjWdEIEB = true;}
      if(DHrdpXlaIX == CyRLNQPbZt){tABwTVeebM = true;}
      else if(CyRLNQPbZt == DHrdpXlaIX){xlreBUEpWg = true;}
      if(RSIgGJryCK == LRULSoTCze){ndPFHptacy = true;}
      else if(LRULSoTCze == RSIgGJryCK){ZQCoOfGpeK = true;}
      if(rsKeKYLBGQ == heiVmDpRCQ){anZWgZhEYc = true;}
      else if(heiVmDpRCQ == rsKeKYLBGQ){FHyQeCuLuR = true;}
      if(dERfKhikyG == MtrSGAFFDa){BwTHXBiGeK = true;}
      else if(MtrSGAFFDa == dERfKhikyG){LXFacsPoNy = true;}
      if(ozufmCanjn == zDuypTBGOD){DKIOtHtakJ = true;}
      else if(zDuypTBGOD == ozufmCanjn){uwecqKCBVq = true;}
      if(YPYumJwMTQ == jdEHqWOuYK){IBJRxGaePt = true;}
      else if(jdEHqWOuYK == YPYumJwMTQ){WOcswombzy = true;}
      if(MkTqtNAcWY == axZJhQYBFS){mZFzKrJIhG = true;}
      if(ZHzwUryerI == jOyYeeijfS){HmwSuPfKbZ = true;}
      if(yWQRqOfVsB == CjDyfipkbi){eHTPTzmCJR = true;}
      while(axZJhQYBFS == MkTqtNAcWY){YruFVCKaMU = true;}
      while(jOyYeeijfS == jOyYeeijfS){QRcgPIcVYU = true;}
      while(CjDyfipkbi == CjDyfipkbi){AtpEtwtMem = true;}
      if(kJfsACclQY == true){kJfsACclQY = false;}
      if(tABwTVeebM == true){tABwTVeebM = false;}
      if(ndPFHptacy == true){ndPFHptacy = false;}
      if(anZWgZhEYc == true){anZWgZhEYc = false;}
      if(BwTHXBiGeK == true){BwTHXBiGeK = false;}
      if(DKIOtHtakJ == true){DKIOtHtakJ = false;}
      if(IBJRxGaePt == true){IBJRxGaePt = false;}
      if(mZFzKrJIhG == true){mZFzKrJIhG = false;}
      if(HmwSuPfKbZ == true){HmwSuPfKbZ = false;}
      if(eHTPTzmCJR == true){eHTPTzmCJR = false;}
      if(aEqjWdEIEB == true){aEqjWdEIEB = false;}
      if(xlreBUEpWg == true){xlreBUEpWg = false;}
      if(ZQCoOfGpeK == true){ZQCoOfGpeK = false;}
      if(FHyQeCuLuR == true){FHyQeCuLuR = false;}
      if(LXFacsPoNy == true){LXFacsPoNy = false;}
      if(uwecqKCBVq == true){uwecqKCBVq = false;}
      if(WOcswombzy == true){WOcswombzy = false;}
      if(YruFVCKaMU == true){YruFVCKaMU = false;}
      if(QRcgPIcVYU == true){QRcgPIcVYU = false;}
      if(AtpEtwtMem == true){AtpEtwtMem = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORZXMPYDDH
{ 
  void RLjMBmfRYp()
  { 
      bool mawXlhIOcn = false;
      bool izllFtoOQO = false;
      bool ryzMnmQCzF = false;
      bool ljqTAnqlgi = false;
      bool ONxVXbrzXg = false;
      bool KlMbdoaijz = false;
      bool QFOXCyISkQ = false;
      bool DChhAeBdoL = false;
      bool uReSuzWOpK = false;
      bool MICgRIyYSY = false;
      bool SYNGdIEeby = false;
      bool nxtXEzaucD = false;
      bool btcZEuzAPr = false;
      bool fbKPrVDYom = false;
      bool urlqWPNdcS = false;
      bool gDwPxYwmCi = false;
      bool IDOiSMmeeh = false;
      bool uCFoIiHkDo = false;
      bool gVXwKbetRT = false;
      bool YQWGeqdDYJ = false;
      string gQdaOXLaOK;
      string EEuNTxmDSB;
      string CClwYkhJZf;
      string IsgHFYOrqS;
      string AUKoKugRVE;
      string hKEjedegCc;
      string pBAiCLWmIt;
      string htMAAgrwkc;
      string DQmUxxnwbb;
      string tgpNcyUamz;
      string XsJaVmyEjy;
      string khwYZYOekE;
      string WaLfAAEyWB;
      string MRJlEJHLzJ;
      string ziMcpLkQnD;
      string jooibxhcaV;
      string hzhhlTYJUP;
      string RCfaFmOhpn;
      string PnKSQWbZKH;
      string bekcazBdqV;
      if(gQdaOXLaOK == XsJaVmyEjy){mawXlhIOcn = true;}
      else if(XsJaVmyEjy == gQdaOXLaOK){SYNGdIEeby = true;}
      if(EEuNTxmDSB == khwYZYOekE){izllFtoOQO = true;}
      else if(khwYZYOekE == EEuNTxmDSB){nxtXEzaucD = true;}
      if(CClwYkhJZf == WaLfAAEyWB){ryzMnmQCzF = true;}
      else if(WaLfAAEyWB == CClwYkhJZf){btcZEuzAPr = true;}
      if(IsgHFYOrqS == MRJlEJHLzJ){ljqTAnqlgi = true;}
      else if(MRJlEJHLzJ == IsgHFYOrqS){fbKPrVDYom = true;}
      if(AUKoKugRVE == ziMcpLkQnD){ONxVXbrzXg = true;}
      else if(ziMcpLkQnD == AUKoKugRVE){urlqWPNdcS = true;}
      if(hKEjedegCc == jooibxhcaV){KlMbdoaijz = true;}
      else if(jooibxhcaV == hKEjedegCc){gDwPxYwmCi = true;}
      if(pBAiCLWmIt == hzhhlTYJUP){QFOXCyISkQ = true;}
      else if(hzhhlTYJUP == pBAiCLWmIt){IDOiSMmeeh = true;}
      if(htMAAgrwkc == RCfaFmOhpn){DChhAeBdoL = true;}
      if(DQmUxxnwbb == PnKSQWbZKH){uReSuzWOpK = true;}
      if(tgpNcyUamz == bekcazBdqV){MICgRIyYSY = true;}
      while(RCfaFmOhpn == htMAAgrwkc){uCFoIiHkDo = true;}
      while(PnKSQWbZKH == PnKSQWbZKH){gVXwKbetRT = true;}
      while(bekcazBdqV == bekcazBdqV){YQWGeqdDYJ = true;}
      if(mawXlhIOcn == true){mawXlhIOcn = false;}
      if(izllFtoOQO == true){izllFtoOQO = false;}
      if(ryzMnmQCzF == true){ryzMnmQCzF = false;}
      if(ljqTAnqlgi == true){ljqTAnqlgi = false;}
      if(ONxVXbrzXg == true){ONxVXbrzXg = false;}
      if(KlMbdoaijz == true){KlMbdoaijz = false;}
      if(QFOXCyISkQ == true){QFOXCyISkQ = false;}
      if(DChhAeBdoL == true){DChhAeBdoL = false;}
      if(uReSuzWOpK == true){uReSuzWOpK = false;}
      if(MICgRIyYSY == true){MICgRIyYSY = false;}
      if(SYNGdIEeby == true){SYNGdIEeby = false;}
      if(nxtXEzaucD == true){nxtXEzaucD = false;}
      if(btcZEuzAPr == true){btcZEuzAPr = false;}
      if(fbKPrVDYom == true){fbKPrVDYom = false;}
      if(urlqWPNdcS == true){urlqWPNdcS = false;}
      if(gDwPxYwmCi == true){gDwPxYwmCi = false;}
      if(IDOiSMmeeh == true){IDOiSMmeeh = false;}
      if(uCFoIiHkDo == true){uCFoIiHkDo = false;}
      if(gVXwKbetRT == true){gVXwKbetRT = false;}
      if(YQWGeqdDYJ == true){YQWGeqdDYJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAPAMJPXNQ
{ 
  void hqUrIliatU()
  { 
      bool ZaZPbeeKTa = false;
      bool bNdbBKRDeX = false;
      bool JqmqLfOHFU = false;
      bool OLOlLHxjWG = false;
      bool gQbKWSdxcM = false;
      bool GsafdhnhEw = false;
      bool QXFzLPyqPs = false;
      bool MhfXprPcUr = false;
      bool BQdrNVkiId = false;
      bool TPeaoJLbzH = false;
      bool UlgizXNDpk = false;
      bool SKNLtzsMlp = false;
      bool ePilZwCFif = false;
      bool gmdMXOjuso = false;
      bool HhsXLICTfo = false;
      bool QypIcFDuJC = false;
      bool VHTJDegAnf = false;
      bool PxTwhwWLZQ = false;
      bool tiYsOhwUiR = false;
      bool LnlpTANiTf = false;
      string oIQzsGwQmG;
      string hnLjYCyiGO;
      string nFDwoprWjh;
      string HHIFJOTKOc;
      string RwXwYNrdWB;
      string IrsRFiEUKC;
      string NZgFzZeGaJ;
      string hmTcwrhGWa;
      string yOzhYPOqAa;
      string KyzMOrPSxy;
      string hlDMTUYPUM;
      string BxyiEzZzfj;
      string LnFzzimHNE;
      string cOJYrMLlNE;
      string pzVmZNAQHP;
      string SPlNmsfDNj;
      string gRBQjlmYpr;
      string nmkbsMRRZl;
      string iWzylMbwky;
      string gHYdWYxFDm;
      if(oIQzsGwQmG == hlDMTUYPUM){ZaZPbeeKTa = true;}
      else if(hlDMTUYPUM == oIQzsGwQmG){UlgizXNDpk = true;}
      if(hnLjYCyiGO == BxyiEzZzfj){bNdbBKRDeX = true;}
      else if(BxyiEzZzfj == hnLjYCyiGO){SKNLtzsMlp = true;}
      if(nFDwoprWjh == LnFzzimHNE){JqmqLfOHFU = true;}
      else if(LnFzzimHNE == nFDwoprWjh){ePilZwCFif = true;}
      if(HHIFJOTKOc == cOJYrMLlNE){OLOlLHxjWG = true;}
      else if(cOJYrMLlNE == HHIFJOTKOc){gmdMXOjuso = true;}
      if(RwXwYNrdWB == pzVmZNAQHP){gQbKWSdxcM = true;}
      else if(pzVmZNAQHP == RwXwYNrdWB){HhsXLICTfo = true;}
      if(IrsRFiEUKC == SPlNmsfDNj){GsafdhnhEw = true;}
      else if(SPlNmsfDNj == IrsRFiEUKC){QypIcFDuJC = true;}
      if(NZgFzZeGaJ == gRBQjlmYpr){QXFzLPyqPs = true;}
      else if(gRBQjlmYpr == NZgFzZeGaJ){VHTJDegAnf = true;}
      if(hmTcwrhGWa == nmkbsMRRZl){MhfXprPcUr = true;}
      if(yOzhYPOqAa == iWzylMbwky){BQdrNVkiId = true;}
      if(KyzMOrPSxy == gHYdWYxFDm){TPeaoJLbzH = true;}
      while(nmkbsMRRZl == hmTcwrhGWa){PxTwhwWLZQ = true;}
      while(iWzylMbwky == iWzylMbwky){tiYsOhwUiR = true;}
      while(gHYdWYxFDm == gHYdWYxFDm){LnlpTANiTf = true;}
      if(ZaZPbeeKTa == true){ZaZPbeeKTa = false;}
      if(bNdbBKRDeX == true){bNdbBKRDeX = false;}
      if(JqmqLfOHFU == true){JqmqLfOHFU = false;}
      if(OLOlLHxjWG == true){OLOlLHxjWG = false;}
      if(gQbKWSdxcM == true){gQbKWSdxcM = false;}
      if(GsafdhnhEw == true){GsafdhnhEw = false;}
      if(QXFzLPyqPs == true){QXFzLPyqPs = false;}
      if(MhfXprPcUr == true){MhfXprPcUr = false;}
      if(BQdrNVkiId == true){BQdrNVkiId = false;}
      if(TPeaoJLbzH == true){TPeaoJLbzH = false;}
      if(UlgizXNDpk == true){UlgizXNDpk = false;}
      if(SKNLtzsMlp == true){SKNLtzsMlp = false;}
      if(ePilZwCFif == true){ePilZwCFif = false;}
      if(gmdMXOjuso == true){gmdMXOjuso = false;}
      if(HhsXLICTfo == true){HhsXLICTfo = false;}
      if(QypIcFDuJC == true){QypIcFDuJC = false;}
      if(VHTJDegAnf == true){VHTJDegAnf = false;}
      if(PxTwhwWLZQ == true){PxTwhwWLZQ = false;}
      if(tiYsOhwUiR == true){tiYsOhwUiR = false;}
      if(LnlpTANiTf == true){LnlpTANiTf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMZCFMPKJF
{ 
  void SwBXKfGRni()
  { 
      bool nKBmMeifnE = false;
      bool hdeuhspHXr = false;
      bool NOUYRpaOAB = false;
      bool wMHJxBlQdm = false;
      bool wHJdsHNxiz = false;
      bool bNykxZpbUV = false;
      bool DUelIUWUyf = false;
      bool GZdkuGEpfJ = false;
      bool cceBZhNWMX = false;
      bool LJwHibcWVX = false;
      bool krzCrCjMoq = false;
      bool UAwKsaodMa = false;
      bool HzIaUxdVCT = false;
      bool dhTIYjdcIX = false;
      bool xBgUDLNkOI = false;
      bool lyJuQkjYgu = false;
      bool YNKVNlfnlJ = false;
      bool xMUncGSnWJ = false;
      bool jrHsgeXYqm = false;
      bool zEuNzipLHQ = false;
      string foqfMnJiKR;
      string BDAPqyYrzw;
      string oKXRiHeTGy;
      string hHmsAkypBj;
      string kkEZCdGzYW;
      string DfBSYVQYxF;
      string JpbMisQGOF;
      string AhpOLEFxPE;
      string AetitCGTUd;
      string TYsuatIrpJ;
      string MzkSWUolHT;
      string PTJrEdurRg;
      string lwkjlbotmQ;
      string uNHFqAtaMY;
      string MUMBNAOBqw;
      string zPZIWQOAgu;
      string ftypXCMDAE;
      string jUfsURijVk;
      string MmDpRfnyia;
      string lssRrSVWcL;
      if(foqfMnJiKR == MzkSWUolHT){nKBmMeifnE = true;}
      else if(MzkSWUolHT == foqfMnJiKR){krzCrCjMoq = true;}
      if(BDAPqyYrzw == PTJrEdurRg){hdeuhspHXr = true;}
      else if(PTJrEdurRg == BDAPqyYrzw){UAwKsaodMa = true;}
      if(oKXRiHeTGy == lwkjlbotmQ){NOUYRpaOAB = true;}
      else if(lwkjlbotmQ == oKXRiHeTGy){HzIaUxdVCT = true;}
      if(hHmsAkypBj == uNHFqAtaMY){wMHJxBlQdm = true;}
      else if(uNHFqAtaMY == hHmsAkypBj){dhTIYjdcIX = true;}
      if(kkEZCdGzYW == MUMBNAOBqw){wHJdsHNxiz = true;}
      else if(MUMBNAOBqw == kkEZCdGzYW){xBgUDLNkOI = true;}
      if(DfBSYVQYxF == zPZIWQOAgu){bNykxZpbUV = true;}
      else if(zPZIWQOAgu == DfBSYVQYxF){lyJuQkjYgu = true;}
      if(JpbMisQGOF == ftypXCMDAE){DUelIUWUyf = true;}
      else if(ftypXCMDAE == JpbMisQGOF){YNKVNlfnlJ = true;}
      if(AhpOLEFxPE == jUfsURijVk){GZdkuGEpfJ = true;}
      if(AetitCGTUd == MmDpRfnyia){cceBZhNWMX = true;}
      if(TYsuatIrpJ == lssRrSVWcL){LJwHibcWVX = true;}
      while(jUfsURijVk == AhpOLEFxPE){xMUncGSnWJ = true;}
      while(MmDpRfnyia == MmDpRfnyia){jrHsgeXYqm = true;}
      while(lssRrSVWcL == lssRrSVWcL){zEuNzipLHQ = true;}
      if(nKBmMeifnE == true){nKBmMeifnE = false;}
      if(hdeuhspHXr == true){hdeuhspHXr = false;}
      if(NOUYRpaOAB == true){NOUYRpaOAB = false;}
      if(wMHJxBlQdm == true){wMHJxBlQdm = false;}
      if(wHJdsHNxiz == true){wHJdsHNxiz = false;}
      if(bNykxZpbUV == true){bNykxZpbUV = false;}
      if(DUelIUWUyf == true){DUelIUWUyf = false;}
      if(GZdkuGEpfJ == true){GZdkuGEpfJ = false;}
      if(cceBZhNWMX == true){cceBZhNWMX = false;}
      if(LJwHibcWVX == true){LJwHibcWVX = false;}
      if(krzCrCjMoq == true){krzCrCjMoq = false;}
      if(UAwKsaodMa == true){UAwKsaodMa = false;}
      if(HzIaUxdVCT == true){HzIaUxdVCT = false;}
      if(dhTIYjdcIX == true){dhTIYjdcIX = false;}
      if(xBgUDLNkOI == true){xBgUDLNkOI = false;}
      if(lyJuQkjYgu == true){lyJuQkjYgu = false;}
      if(YNKVNlfnlJ == true){YNKVNlfnlJ = false;}
      if(xMUncGSnWJ == true){xMUncGSnWJ = false;}
      if(jrHsgeXYqm == true){jrHsgeXYqm = false;}
      if(zEuNzipLHQ == true){zEuNzipLHQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVIYMQMYLL
{ 
  void xKqmfNMaZL()
  { 
      bool nKKxqTAwNR = false;
      bool tbhiFLOPcS = false;
      bool XLUKZAwpgL = false;
      bool beaWgANjUu = false;
      bool lCCjDUDzag = false;
      bool dEbfYboAWp = false;
      bool WKPBoOBLBE = false;
      bool ydugfUIjGF = false;
      bool xxPzhWCtxF = false;
      bool KMNdXbmBtn = false;
      bool SqxVizJtAD = false;
      bool SEsRsZtPTR = false;
      bool MHNwtkQQJD = false;
      bool hHpSlFzsQh = false;
      bool NHstlFSujy = false;
      bool hXgbbLdBby = false;
      bool irkwVKOaen = false;
      bool ZAzkEENTJn = false;
      bool RUfKVJZNpa = false;
      bool ayRRzUWxXa = false;
      string auIyMUWtkN;
      string kRkExsRlzj;
      string NinudLReXb;
      string faikEigWrG;
      string HMjsUrfoDT;
      string WrLgQqHNUB;
      string CrWJgKhzAN;
      string LtssbAyuZk;
      string ecbDFnPBUM;
      string bTCqDPpaLJ;
      string KfooHbzREP;
      string sLmiVZQSDs;
      string ufdmkqrCoM;
      string KWiQaynlwc;
      string oxwETQgSUc;
      string yWWSOdCBDP;
      string jwbqFWcWHW;
      string leWaExjZTU;
      string KYhLOmzQBx;
      string wlhfsrUEzw;
      if(auIyMUWtkN == KfooHbzREP){nKKxqTAwNR = true;}
      else if(KfooHbzREP == auIyMUWtkN){SqxVizJtAD = true;}
      if(kRkExsRlzj == sLmiVZQSDs){tbhiFLOPcS = true;}
      else if(sLmiVZQSDs == kRkExsRlzj){SEsRsZtPTR = true;}
      if(NinudLReXb == ufdmkqrCoM){XLUKZAwpgL = true;}
      else if(ufdmkqrCoM == NinudLReXb){MHNwtkQQJD = true;}
      if(faikEigWrG == KWiQaynlwc){beaWgANjUu = true;}
      else if(KWiQaynlwc == faikEigWrG){hHpSlFzsQh = true;}
      if(HMjsUrfoDT == oxwETQgSUc){lCCjDUDzag = true;}
      else if(oxwETQgSUc == HMjsUrfoDT){NHstlFSujy = true;}
      if(WrLgQqHNUB == yWWSOdCBDP){dEbfYboAWp = true;}
      else if(yWWSOdCBDP == WrLgQqHNUB){hXgbbLdBby = true;}
      if(CrWJgKhzAN == jwbqFWcWHW){WKPBoOBLBE = true;}
      else if(jwbqFWcWHW == CrWJgKhzAN){irkwVKOaen = true;}
      if(LtssbAyuZk == leWaExjZTU){ydugfUIjGF = true;}
      if(ecbDFnPBUM == KYhLOmzQBx){xxPzhWCtxF = true;}
      if(bTCqDPpaLJ == wlhfsrUEzw){KMNdXbmBtn = true;}
      while(leWaExjZTU == LtssbAyuZk){ZAzkEENTJn = true;}
      while(KYhLOmzQBx == KYhLOmzQBx){RUfKVJZNpa = true;}
      while(wlhfsrUEzw == wlhfsrUEzw){ayRRzUWxXa = true;}
      if(nKKxqTAwNR == true){nKKxqTAwNR = false;}
      if(tbhiFLOPcS == true){tbhiFLOPcS = false;}
      if(XLUKZAwpgL == true){XLUKZAwpgL = false;}
      if(beaWgANjUu == true){beaWgANjUu = false;}
      if(lCCjDUDzag == true){lCCjDUDzag = false;}
      if(dEbfYboAWp == true){dEbfYboAWp = false;}
      if(WKPBoOBLBE == true){WKPBoOBLBE = false;}
      if(ydugfUIjGF == true){ydugfUIjGF = false;}
      if(xxPzhWCtxF == true){xxPzhWCtxF = false;}
      if(KMNdXbmBtn == true){KMNdXbmBtn = false;}
      if(SqxVizJtAD == true){SqxVizJtAD = false;}
      if(SEsRsZtPTR == true){SEsRsZtPTR = false;}
      if(MHNwtkQQJD == true){MHNwtkQQJD = false;}
      if(hHpSlFzsQh == true){hHpSlFzsQh = false;}
      if(NHstlFSujy == true){NHstlFSujy = false;}
      if(hXgbbLdBby == true){hXgbbLdBby = false;}
      if(irkwVKOaen == true){irkwVKOaen = false;}
      if(ZAzkEENTJn == true){ZAzkEENTJn = false;}
      if(RUfKVJZNpa == true){RUfKVJZNpa = false;}
      if(ayRRzUWxXa == true){ayRRzUWxXa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLNVBRMRHJ
{ 
  void jUUOTLFsrp()
  { 
      bool hshrrgDPii = false;
      bool CjqzDksxbr = false;
      bool qWtpVjrZFx = false;
      bool oJoSYFMQLz = false;
      bool jxJathfHWU = false;
      bool xIBWjKzqWI = false;
      bool ocKktruXay = false;
      bool XckcHtMSum = false;
      bool EjCjAfIRiN = false;
      bool FVsDKGmYgC = false;
      bool mHgYxUXYOp = false;
      bool yfuiEFaZkN = false;
      bool jcoNrBihSB = false;
      bool GnkszxDcmf = false;
      bool IiCrOYZKzE = false;
      bool fMmTSKRSgu = false;
      bool koGNiKuCjH = false;
      bool CxmEEAZwyS = false;
      bool bYiNUsAQZo = false;
      bool ejwqtTcoIE = false;
      string iCljAbDgaP;
      string sUspSHpmUo;
      string UXxSEInRXs;
      string wflWljNcUC;
      string grIZtzLRss;
      string KKVdBKETfr;
      string mlJhTMiWDi;
      string sNSRHbPXXE;
      string wWXdikKIVb;
      string etxbPtiaGh;
      string QoNKAwrDVY;
      string tguauPNeyh;
      string CZAbDyQpCN;
      string roRpmHJNdl;
      string sGlwgxzVgz;
      string gEbXepnlGC;
      string fCAIfFPFnn;
      string GzBLounEtG;
      string zuIDfnNsKx;
      string SWHaGqGdPb;
      if(iCljAbDgaP == QoNKAwrDVY){hshrrgDPii = true;}
      else if(QoNKAwrDVY == iCljAbDgaP){mHgYxUXYOp = true;}
      if(sUspSHpmUo == tguauPNeyh){CjqzDksxbr = true;}
      else if(tguauPNeyh == sUspSHpmUo){yfuiEFaZkN = true;}
      if(UXxSEInRXs == CZAbDyQpCN){qWtpVjrZFx = true;}
      else if(CZAbDyQpCN == UXxSEInRXs){jcoNrBihSB = true;}
      if(wflWljNcUC == roRpmHJNdl){oJoSYFMQLz = true;}
      else if(roRpmHJNdl == wflWljNcUC){GnkszxDcmf = true;}
      if(grIZtzLRss == sGlwgxzVgz){jxJathfHWU = true;}
      else if(sGlwgxzVgz == grIZtzLRss){IiCrOYZKzE = true;}
      if(KKVdBKETfr == gEbXepnlGC){xIBWjKzqWI = true;}
      else if(gEbXepnlGC == KKVdBKETfr){fMmTSKRSgu = true;}
      if(mlJhTMiWDi == fCAIfFPFnn){ocKktruXay = true;}
      else if(fCAIfFPFnn == mlJhTMiWDi){koGNiKuCjH = true;}
      if(sNSRHbPXXE == GzBLounEtG){XckcHtMSum = true;}
      if(wWXdikKIVb == zuIDfnNsKx){EjCjAfIRiN = true;}
      if(etxbPtiaGh == SWHaGqGdPb){FVsDKGmYgC = true;}
      while(GzBLounEtG == sNSRHbPXXE){CxmEEAZwyS = true;}
      while(zuIDfnNsKx == zuIDfnNsKx){bYiNUsAQZo = true;}
      while(SWHaGqGdPb == SWHaGqGdPb){ejwqtTcoIE = true;}
      if(hshrrgDPii == true){hshrrgDPii = false;}
      if(CjqzDksxbr == true){CjqzDksxbr = false;}
      if(qWtpVjrZFx == true){qWtpVjrZFx = false;}
      if(oJoSYFMQLz == true){oJoSYFMQLz = false;}
      if(jxJathfHWU == true){jxJathfHWU = false;}
      if(xIBWjKzqWI == true){xIBWjKzqWI = false;}
      if(ocKktruXay == true){ocKktruXay = false;}
      if(XckcHtMSum == true){XckcHtMSum = false;}
      if(EjCjAfIRiN == true){EjCjAfIRiN = false;}
      if(FVsDKGmYgC == true){FVsDKGmYgC = false;}
      if(mHgYxUXYOp == true){mHgYxUXYOp = false;}
      if(yfuiEFaZkN == true){yfuiEFaZkN = false;}
      if(jcoNrBihSB == true){jcoNrBihSB = false;}
      if(GnkszxDcmf == true){GnkszxDcmf = false;}
      if(IiCrOYZKzE == true){IiCrOYZKzE = false;}
      if(fMmTSKRSgu == true){fMmTSKRSgu = false;}
      if(koGNiKuCjH == true){koGNiKuCjH = false;}
      if(CxmEEAZwyS == true){CxmEEAZwyS = false;}
      if(bYiNUsAQZo == true){bYiNUsAQZo = false;}
      if(ejwqtTcoIE == true){ejwqtTcoIE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJAJCHCPVS
{ 
  void kLRfDueFQP()
  { 
      bool oltjcGoWry = false;
      bool AupdzpeOiU = false;
      bool lUBetyboXT = false;
      bool xLhnrWpabu = false;
      bool KckIBMDryL = false;
      bool LkSYpUkPpe = false;
      bool dzzXAnMBlc = false;
      bool zEmnKIjrcg = false;
      bool tiqMHLsIyX = false;
      bool kajxQKdMHM = false;
      bool zBGVLHydOg = false;
      bool jrlIktImQo = false;
      bool uEDNqYTpXz = false;
      bool dWjPhrcUAz = false;
      bool NOtQmrnbMV = false;
      bool BqwSRuyrem = false;
      bool mIGOCNIVar = false;
      bool RnlQafJlay = false;
      bool jrcBxmaRym = false;
      bool sjpMLFHeOZ = false;
      string GCzDfeuBFr;
      string hAMQTAkDfp;
      string eUrSaJBspl;
      string ayUJkdoBoq;
      string rgUOztRPZX;
      string VDipwkJgcW;
      string dCLTQieDep;
      string LjOnxyAdTf;
      string qkSRPWPeMA;
      string THXRNpVBxP;
      string ONkiMlntrx;
      string keMxerisDt;
      string SAqeWELxZH;
      string cygEQdAjFc;
      string hUlOOnualU;
      string GcxDwOWGMH;
      string aqTjUmyIgB;
      string rzmZLyNbPh;
      string IjLFBAAcHC;
      string HtWxCqABtb;
      if(GCzDfeuBFr == ONkiMlntrx){oltjcGoWry = true;}
      else if(ONkiMlntrx == GCzDfeuBFr){zBGVLHydOg = true;}
      if(hAMQTAkDfp == keMxerisDt){AupdzpeOiU = true;}
      else if(keMxerisDt == hAMQTAkDfp){jrlIktImQo = true;}
      if(eUrSaJBspl == SAqeWELxZH){lUBetyboXT = true;}
      else if(SAqeWELxZH == eUrSaJBspl){uEDNqYTpXz = true;}
      if(ayUJkdoBoq == cygEQdAjFc){xLhnrWpabu = true;}
      else if(cygEQdAjFc == ayUJkdoBoq){dWjPhrcUAz = true;}
      if(rgUOztRPZX == hUlOOnualU){KckIBMDryL = true;}
      else if(hUlOOnualU == rgUOztRPZX){NOtQmrnbMV = true;}
      if(VDipwkJgcW == GcxDwOWGMH){LkSYpUkPpe = true;}
      else if(GcxDwOWGMH == VDipwkJgcW){BqwSRuyrem = true;}
      if(dCLTQieDep == aqTjUmyIgB){dzzXAnMBlc = true;}
      else if(aqTjUmyIgB == dCLTQieDep){mIGOCNIVar = true;}
      if(LjOnxyAdTf == rzmZLyNbPh){zEmnKIjrcg = true;}
      if(qkSRPWPeMA == IjLFBAAcHC){tiqMHLsIyX = true;}
      if(THXRNpVBxP == HtWxCqABtb){kajxQKdMHM = true;}
      while(rzmZLyNbPh == LjOnxyAdTf){RnlQafJlay = true;}
      while(IjLFBAAcHC == IjLFBAAcHC){jrcBxmaRym = true;}
      while(HtWxCqABtb == HtWxCqABtb){sjpMLFHeOZ = true;}
      if(oltjcGoWry == true){oltjcGoWry = false;}
      if(AupdzpeOiU == true){AupdzpeOiU = false;}
      if(lUBetyboXT == true){lUBetyboXT = false;}
      if(xLhnrWpabu == true){xLhnrWpabu = false;}
      if(KckIBMDryL == true){KckIBMDryL = false;}
      if(LkSYpUkPpe == true){LkSYpUkPpe = false;}
      if(dzzXAnMBlc == true){dzzXAnMBlc = false;}
      if(zEmnKIjrcg == true){zEmnKIjrcg = false;}
      if(tiqMHLsIyX == true){tiqMHLsIyX = false;}
      if(kajxQKdMHM == true){kajxQKdMHM = false;}
      if(zBGVLHydOg == true){zBGVLHydOg = false;}
      if(jrlIktImQo == true){jrlIktImQo = false;}
      if(uEDNqYTpXz == true){uEDNqYTpXz = false;}
      if(dWjPhrcUAz == true){dWjPhrcUAz = false;}
      if(NOtQmrnbMV == true){NOtQmrnbMV = false;}
      if(BqwSRuyrem == true){BqwSRuyrem = false;}
      if(mIGOCNIVar == true){mIGOCNIVar = false;}
      if(RnlQafJlay == true){RnlQafJlay = false;}
      if(jrcBxmaRym == true){jrcBxmaRym = false;}
      if(sjpMLFHeOZ == true){sjpMLFHeOZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKZZSDOSHT
{ 
  void kaMTcSrhSC()
  { 
      bool nlPsCLFLHG = false;
      bool HmBUKSyUIT = false;
      bool sElsJNrbdP = false;
      bool BnXOTUfsER = false;
      bool NDKQlidBKZ = false;
      bool MBmusjAWjn = false;
      bool SdhqETOlBo = false;
      bool lEQpGptUHa = false;
      bool jpRDDzBcUj = false;
      bool UJJPyiUSLR = false;
      bool TqAUmHkwoC = false;
      bool ofOIEbMdnF = false;
      bool RkRQUctBrW = false;
      bool VaIoGrpwQu = false;
      bool OEnRtntBKV = false;
      bool WqdGzhZiAK = false;
      bool MiESgOXZCL = false;
      bool lPNsqNxzWf = false;
      bool hspVzdxBoX = false;
      bool SHwFieAUjf = false;
      string gHUQRuFiCW;
      string joeRLfXAIn;
      string oReGucjtpF;
      string EiAdRKVxnh;
      string yfIYCyQByg;
      string lJFeSPcOVn;
      string KKswSBnAAB;
      string KZLZpIJGDw;
      string MiwJStdVLC;
      string hGbAWmmLFB;
      string KPBwVMxenJ;
      string GWKYbaNjcX;
      string WRoxTDyLCC;
      string VxABlwhzmG;
      string xygCwKuCYw;
      string ZChhdrZDcS;
      string NlbkmIWJme;
      string sOwWaXjmBI;
      string HumGcTORWs;
      string VeVUrLWuOm;
      if(gHUQRuFiCW == KPBwVMxenJ){nlPsCLFLHG = true;}
      else if(KPBwVMxenJ == gHUQRuFiCW){TqAUmHkwoC = true;}
      if(joeRLfXAIn == GWKYbaNjcX){HmBUKSyUIT = true;}
      else if(GWKYbaNjcX == joeRLfXAIn){ofOIEbMdnF = true;}
      if(oReGucjtpF == WRoxTDyLCC){sElsJNrbdP = true;}
      else if(WRoxTDyLCC == oReGucjtpF){RkRQUctBrW = true;}
      if(EiAdRKVxnh == VxABlwhzmG){BnXOTUfsER = true;}
      else if(VxABlwhzmG == EiAdRKVxnh){VaIoGrpwQu = true;}
      if(yfIYCyQByg == xygCwKuCYw){NDKQlidBKZ = true;}
      else if(xygCwKuCYw == yfIYCyQByg){OEnRtntBKV = true;}
      if(lJFeSPcOVn == ZChhdrZDcS){MBmusjAWjn = true;}
      else if(ZChhdrZDcS == lJFeSPcOVn){WqdGzhZiAK = true;}
      if(KKswSBnAAB == NlbkmIWJme){SdhqETOlBo = true;}
      else if(NlbkmIWJme == KKswSBnAAB){MiESgOXZCL = true;}
      if(KZLZpIJGDw == sOwWaXjmBI){lEQpGptUHa = true;}
      if(MiwJStdVLC == HumGcTORWs){jpRDDzBcUj = true;}
      if(hGbAWmmLFB == VeVUrLWuOm){UJJPyiUSLR = true;}
      while(sOwWaXjmBI == KZLZpIJGDw){lPNsqNxzWf = true;}
      while(HumGcTORWs == HumGcTORWs){hspVzdxBoX = true;}
      while(VeVUrLWuOm == VeVUrLWuOm){SHwFieAUjf = true;}
      if(nlPsCLFLHG == true){nlPsCLFLHG = false;}
      if(HmBUKSyUIT == true){HmBUKSyUIT = false;}
      if(sElsJNrbdP == true){sElsJNrbdP = false;}
      if(BnXOTUfsER == true){BnXOTUfsER = false;}
      if(NDKQlidBKZ == true){NDKQlidBKZ = false;}
      if(MBmusjAWjn == true){MBmusjAWjn = false;}
      if(SdhqETOlBo == true){SdhqETOlBo = false;}
      if(lEQpGptUHa == true){lEQpGptUHa = false;}
      if(jpRDDzBcUj == true){jpRDDzBcUj = false;}
      if(UJJPyiUSLR == true){UJJPyiUSLR = false;}
      if(TqAUmHkwoC == true){TqAUmHkwoC = false;}
      if(ofOIEbMdnF == true){ofOIEbMdnF = false;}
      if(RkRQUctBrW == true){RkRQUctBrW = false;}
      if(VaIoGrpwQu == true){VaIoGrpwQu = false;}
      if(OEnRtntBKV == true){OEnRtntBKV = false;}
      if(WqdGzhZiAK == true){WqdGzhZiAK = false;}
      if(MiESgOXZCL == true){MiESgOXZCL = false;}
      if(lPNsqNxzWf == true){lPNsqNxzWf = false;}
      if(hspVzdxBoX == true){hspVzdxBoX = false;}
      if(SHwFieAUjf == true){SHwFieAUjf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRJXVQEDDJ
{ 
  void UQOoWXTYFZ()
  { 
      bool hENrleRyUD = false;
      bool JPbNPjoMcD = false;
      bool fpDFbdbdHB = false;
      bool RQeWSjkEGh = false;
      bool YfqSxnHOyd = false;
      bool rcKtXrBHQI = false;
      bool DnpSlskFuf = false;
      bool ykFtdAzjHm = false;
      bool VMfcJoFjya = false;
      bool idnyekoXgE = false;
      bool DCTRfGWQQW = false;
      bool rQzclpINJw = false;
      bool mBGTxTxHPs = false;
      bool LbDDjTsNwC = false;
      bool SoTaiReLMn = false;
      bool baNjQCwAUL = false;
      bool JOAWLQNurR = false;
      bool xuQHdygeke = false;
      bool oltaQkNSmh = false;
      bool XsskrDnwPS = false;
      string oEQRkMbfZq;
      string ocZYiAATWC;
      string yxNLNshjaA;
      string KoeLNtsPtd;
      string YaMnOteDph;
      string tgsPUrqFDq;
      string dqFZfzxOLo;
      string HkYsdXjYwT;
      string NdtsGcwPqV;
      string DmLCzgVmIO;
      string xQrBZIIzlx;
      string HSIjdzxLSD;
      string DhWolUZVsw;
      string BxQhWxlrTx;
      string TwctOjeaYz;
      string iJTEKOsCPF;
      string ilGouJCZNf;
      string NErViHEcaB;
      string oyxsMqdLWH;
      string EicOOhonyE;
      if(oEQRkMbfZq == xQrBZIIzlx){hENrleRyUD = true;}
      else if(xQrBZIIzlx == oEQRkMbfZq){DCTRfGWQQW = true;}
      if(ocZYiAATWC == HSIjdzxLSD){JPbNPjoMcD = true;}
      else if(HSIjdzxLSD == ocZYiAATWC){rQzclpINJw = true;}
      if(yxNLNshjaA == DhWolUZVsw){fpDFbdbdHB = true;}
      else if(DhWolUZVsw == yxNLNshjaA){mBGTxTxHPs = true;}
      if(KoeLNtsPtd == BxQhWxlrTx){RQeWSjkEGh = true;}
      else if(BxQhWxlrTx == KoeLNtsPtd){LbDDjTsNwC = true;}
      if(YaMnOteDph == TwctOjeaYz){YfqSxnHOyd = true;}
      else if(TwctOjeaYz == YaMnOteDph){SoTaiReLMn = true;}
      if(tgsPUrqFDq == iJTEKOsCPF){rcKtXrBHQI = true;}
      else if(iJTEKOsCPF == tgsPUrqFDq){baNjQCwAUL = true;}
      if(dqFZfzxOLo == ilGouJCZNf){DnpSlskFuf = true;}
      else if(ilGouJCZNf == dqFZfzxOLo){JOAWLQNurR = true;}
      if(HkYsdXjYwT == NErViHEcaB){ykFtdAzjHm = true;}
      if(NdtsGcwPqV == oyxsMqdLWH){VMfcJoFjya = true;}
      if(DmLCzgVmIO == EicOOhonyE){idnyekoXgE = true;}
      while(NErViHEcaB == HkYsdXjYwT){xuQHdygeke = true;}
      while(oyxsMqdLWH == oyxsMqdLWH){oltaQkNSmh = true;}
      while(EicOOhonyE == EicOOhonyE){XsskrDnwPS = true;}
      if(hENrleRyUD == true){hENrleRyUD = false;}
      if(JPbNPjoMcD == true){JPbNPjoMcD = false;}
      if(fpDFbdbdHB == true){fpDFbdbdHB = false;}
      if(RQeWSjkEGh == true){RQeWSjkEGh = false;}
      if(YfqSxnHOyd == true){YfqSxnHOyd = false;}
      if(rcKtXrBHQI == true){rcKtXrBHQI = false;}
      if(DnpSlskFuf == true){DnpSlskFuf = false;}
      if(ykFtdAzjHm == true){ykFtdAzjHm = false;}
      if(VMfcJoFjya == true){VMfcJoFjya = false;}
      if(idnyekoXgE == true){idnyekoXgE = false;}
      if(DCTRfGWQQW == true){DCTRfGWQQW = false;}
      if(rQzclpINJw == true){rQzclpINJw = false;}
      if(mBGTxTxHPs == true){mBGTxTxHPs = false;}
      if(LbDDjTsNwC == true){LbDDjTsNwC = false;}
      if(SoTaiReLMn == true){SoTaiReLMn = false;}
      if(baNjQCwAUL == true){baNjQCwAUL = false;}
      if(JOAWLQNurR == true){JOAWLQNurR = false;}
      if(xuQHdygeke == true){xuQHdygeke = false;}
      if(oltaQkNSmh == true){oltaQkNSmh = false;}
      if(XsskrDnwPS == true){XsskrDnwPS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBEFBSISLB
{ 
  void JgmyRACaXh()
  { 
      bool NdpyQKUSTg = false;
      bool eQXbIGOeHA = false;
      bool ZVQmsRTInr = false;
      bool cSSRMbXdkn = false;
      bool obEWwJVuTS = false;
      bool AdIrrqMCEy = false;
      bool qMdbDLyGOg = false;
      bool hjtSKxRtpj = false;
      bool uXoVryKZZU = false;
      bool OUZlxcxcSj = false;
      bool LPfljPjogt = false;
      bool ZSLTDSXIjE = false;
      bool BXgsSNKHVh = false;
      bool AnbGXfrClb = false;
      bool OVsetwIFid = false;
      bool FnsNinilTV = false;
      bool FbSztkpFwX = false;
      bool aUWHpfdBzV = false;
      bool EFYqbLuNXj = false;
      bool wFhPVmCskJ = false;
      string IMwauMtFiN;
      string LqFCQmtoJD;
      string YteoOeQXSt;
      string KhEKxiuTFm;
      string lWdqXFljQJ;
      string NUgYdNhHMQ;
      string wVlnCcluFh;
      string qZjVQBQnQI;
      string sgGJgpBefi;
      string BnHoqQjont;
      string TpdiRmkLIc;
      string wspDWOOcHM;
      string bGOVgDStdA;
      string RbzVoCCXqs;
      string FpWDlHyESc;
      string BGgaSNbIBO;
      string UpgHKUtTOU;
      string LplNHliKjZ;
      string FNbBzKuXDa;
      string atWcYOIPrR;
      if(IMwauMtFiN == TpdiRmkLIc){NdpyQKUSTg = true;}
      else if(TpdiRmkLIc == IMwauMtFiN){LPfljPjogt = true;}
      if(LqFCQmtoJD == wspDWOOcHM){eQXbIGOeHA = true;}
      else if(wspDWOOcHM == LqFCQmtoJD){ZSLTDSXIjE = true;}
      if(YteoOeQXSt == bGOVgDStdA){ZVQmsRTInr = true;}
      else if(bGOVgDStdA == YteoOeQXSt){BXgsSNKHVh = true;}
      if(KhEKxiuTFm == RbzVoCCXqs){cSSRMbXdkn = true;}
      else if(RbzVoCCXqs == KhEKxiuTFm){AnbGXfrClb = true;}
      if(lWdqXFljQJ == FpWDlHyESc){obEWwJVuTS = true;}
      else if(FpWDlHyESc == lWdqXFljQJ){OVsetwIFid = true;}
      if(NUgYdNhHMQ == BGgaSNbIBO){AdIrrqMCEy = true;}
      else if(BGgaSNbIBO == NUgYdNhHMQ){FnsNinilTV = true;}
      if(wVlnCcluFh == UpgHKUtTOU){qMdbDLyGOg = true;}
      else if(UpgHKUtTOU == wVlnCcluFh){FbSztkpFwX = true;}
      if(qZjVQBQnQI == LplNHliKjZ){hjtSKxRtpj = true;}
      if(sgGJgpBefi == FNbBzKuXDa){uXoVryKZZU = true;}
      if(BnHoqQjont == atWcYOIPrR){OUZlxcxcSj = true;}
      while(LplNHliKjZ == qZjVQBQnQI){aUWHpfdBzV = true;}
      while(FNbBzKuXDa == FNbBzKuXDa){EFYqbLuNXj = true;}
      while(atWcYOIPrR == atWcYOIPrR){wFhPVmCskJ = true;}
      if(NdpyQKUSTg == true){NdpyQKUSTg = false;}
      if(eQXbIGOeHA == true){eQXbIGOeHA = false;}
      if(ZVQmsRTInr == true){ZVQmsRTInr = false;}
      if(cSSRMbXdkn == true){cSSRMbXdkn = false;}
      if(obEWwJVuTS == true){obEWwJVuTS = false;}
      if(AdIrrqMCEy == true){AdIrrqMCEy = false;}
      if(qMdbDLyGOg == true){qMdbDLyGOg = false;}
      if(hjtSKxRtpj == true){hjtSKxRtpj = false;}
      if(uXoVryKZZU == true){uXoVryKZZU = false;}
      if(OUZlxcxcSj == true){OUZlxcxcSj = false;}
      if(LPfljPjogt == true){LPfljPjogt = false;}
      if(ZSLTDSXIjE == true){ZSLTDSXIjE = false;}
      if(BXgsSNKHVh == true){BXgsSNKHVh = false;}
      if(AnbGXfrClb == true){AnbGXfrClb = false;}
      if(OVsetwIFid == true){OVsetwIFid = false;}
      if(FnsNinilTV == true){FnsNinilTV = false;}
      if(FbSztkpFwX == true){FbSztkpFwX = false;}
      if(aUWHpfdBzV == true){aUWHpfdBzV = false;}
      if(EFYqbLuNXj == true){EFYqbLuNXj = false;}
      if(wFhPVmCskJ == true){wFhPVmCskJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVRUPXSIMA
{ 
  void ktWFbaVlti()
  { 
      bool RJhGWzdRDz = false;
      bool ayywQffujq = false;
      bool HYusKxIIqP = false;
      bool kEsJysJkMH = false;
      bool TTyqBZuTob = false;
      bool CdTUZsNnuY = false;
      bool pUZmOVEnyW = false;
      bool WuhbXmaErj = false;
      bool CnSPNGkYjF = false;
      bool fUomRytKce = false;
      bool VGVSFHuqwl = false;
      bool SJwKWBBJZH = false;
      bool kfErqBFuKY = false;
      bool sPaNOuSAKF = false;
      bool KsbxlVYdQP = false;
      bool wjkUsoBcaD = false;
      bool CAgWrCihwa = false;
      bool iBzTxrDHGU = false;
      bool badubJeFUZ = false;
      bool soYGDJLEEj = false;
      string fMFplzBgqL;
      string nUbEieCjpn;
      string uibsIliywH;
      string xsynRFuTBE;
      string eUhTTJzszC;
      string EmNfGwkMgz;
      string PDkjNuVnmc;
      string iiikIaBIYz;
      string moztCJfSgV;
      string UilBnbjyFY;
      string mKGVTVEbXf;
      string ucmhLZDpgD;
      string ODGQIzwgxf;
      string qCCALcidag;
      string FEuBZrwEoN;
      string YsRBJjDoMT;
      string YWdqorZlVi;
      string qZPAyKIFqQ;
      string DrqiHxkBpb;
      string YsQGIhZDLg;
      if(fMFplzBgqL == mKGVTVEbXf){RJhGWzdRDz = true;}
      else if(mKGVTVEbXf == fMFplzBgqL){VGVSFHuqwl = true;}
      if(nUbEieCjpn == ucmhLZDpgD){ayywQffujq = true;}
      else if(ucmhLZDpgD == nUbEieCjpn){SJwKWBBJZH = true;}
      if(uibsIliywH == ODGQIzwgxf){HYusKxIIqP = true;}
      else if(ODGQIzwgxf == uibsIliywH){kfErqBFuKY = true;}
      if(xsynRFuTBE == qCCALcidag){kEsJysJkMH = true;}
      else if(qCCALcidag == xsynRFuTBE){sPaNOuSAKF = true;}
      if(eUhTTJzszC == FEuBZrwEoN){TTyqBZuTob = true;}
      else if(FEuBZrwEoN == eUhTTJzszC){KsbxlVYdQP = true;}
      if(EmNfGwkMgz == YsRBJjDoMT){CdTUZsNnuY = true;}
      else if(YsRBJjDoMT == EmNfGwkMgz){wjkUsoBcaD = true;}
      if(PDkjNuVnmc == YWdqorZlVi){pUZmOVEnyW = true;}
      else if(YWdqorZlVi == PDkjNuVnmc){CAgWrCihwa = true;}
      if(iiikIaBIYz == qZPAyKIFqQ){WuhbXmaErj = true;}
      if(moztCJfSgV == DrqiHxkBpb){CnSPNGkYjF = true;}
      if(UilBnbjyFY == YsQGIhZDLg){fUomRytKce = true;}
      while(qZPAyKIFqQ == iiikIaBIYz){iBzTxrDHGU = true;}
      while(DrqiHxkBpb == DrqiHxkBpb){badubJeFUZ = true;}
      while(YsQGIhZDLg == YsQGIhZDLg){soYGDJLEEj = true;}
      if(RJhGWzdRDz == true){RJhGWzdRDz = false;}
      if(ayywQffujq == true){ayywQffujq = false;}
      if(HYusKxIIqP == true){HYusKxIIqP = false;}
      if(kEsJysJkMH == true){kEsJysJkMH = false;}
      if(TTyqBZuTob == true){TTyqBZuTob = false;}
      if(CdTUZsNnuY == true){CdTUZsNnuY = false;}
      if(pUZmOVEnyW == true){pUZmOVEnyW = false;}
      if(WuhbXmaErj == true){WuhbXmaErj = false;}
      if(CnSPNGkYjF == true){CnSPNGkYjF = false;}
      if(fUomRytKce == true){fUomRytKce = false;}
      if(VGVSFHuqwl == true){VGVSFHuqwl = false;}
      if(SJwKWBBJZH == true){SJwKWBBJZH = false;}
      if(kfErqBFuKY == true){kfErqBFuKY = false;}
      if(sPaNOuSAKF == true){sPaNOuSAKF = false;}
      if(KsbxlVYdQP == true){KsbxlVYdQP = false;}
      if(wjkUsoBcaD == true){wjkUsoBcaD = false;}
      if(CAgWrCihwa == true){CAgWrCihwa = false;}
      if(iBzTxrDHGU == true){iBzTxrDHGU = false;}
      if(badubJeFUZ == true){badubJeFUZ = false;}
      if(soYGDJLEEj == true){soYGDJLEEj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWNKFSLZAN
{ 
  void RYQPqjJhWF()
  { 
      bool RyDsbljRat = false;
      bool VEHOSQgleL = false;
      bool YcjxgFkGrz = false;
      bool fGISstNHnO = false;
      bool rVBbowCgDb = false;
      bool ySnIdoOGMV = false;
      bool BdYaOPwoVY = false;
      bool CYxQSCaHHj = false;
      bool DDCQAMSznD = false;
      bool eHuRNOxZNZ = false;
      bool AMKeYYVXpa = false;
      bool NGybSxaIaB = false;
      bool xwARsudeCD = false;
      bool FBthipsXqa = false;
      bool qtJNpYISzP = false;
      bool nozLcEMrkd = false;
      bool upUlVLMQrc = false;
      bool EDRzKClmbU = false;
      bool lKfmPPBhEe = false;
      bool cAlMfAZXqe = false;
      string ebsLIUORKj;
      string lSGgZMdjyx;
      string sVFITqRfNK;
      string NbsicgzULw;
      string FcPWhspRBV;
      string VkLsuJVjqR;
      string ChDAWJYXDs;
      string MIXBrPFhaa;
      string AAeqnbQAmS;
      string KOdttWYOAX;
      string TRNIJMMJAe;
      string DmJQRCDLMt;
      string rYkkhxedHU;
      string pphCGimWha;
      string OHzIPWFNbq;
      string TNCFfugcZL;
      string hiCfnMFGJi;
      string PgckekYbUK;
      string rRBPBcnbWL;
      string BJwWrfFSTC;
      if(ebsLIUORKj == TRNIJMMJAe){RyDsbljRat = true;}
      else if(TRNIJMMJAe == ebsLIUORKj){AMKeYYVXpa = true;}
      if(lSGgZMdjyx == DmJQRCDLMt){VEHOSQgleL = true;}
      else if(DmJQRCDLMt == lSGgZMdjyx){NGybSxaIaB = true;}
      if(sVFITqRfNK == rYkkhxedHU){YcjxgFkGrz = true;}
      else if(rYkkhxedHU == sVFITqRfNK){xwARsudeCD = true;}
      if(NbsicgzULw == pphCGimWha){fGISstNHnO = true;}
      else if(pphCGimWha == NbsicgzULw){FBthipsXqa = true;}
      if(FcPWhspRBV == OHzIPWFNbq){rVBbowCgDb = true;}
      else if(OHzIPWFNbq == FcPWhspRBV){qtJNpYISzP = true;}
      if(VkLsuJVjqR == TNCFfugcZL){ySnIdoOGMV = true;}
      else if(TNCFfugcZL == VkLsuJVjqR){nozLcEMrkd = true;}
      if(ChDAWJYXDs == hiCfnMFGJi){BdYaOPwoVY = true;}
      else if(hiCfnMFGJi == ChDAWJYXDs){upUlVLMQrc = true;}
      if(MIXBrPFhaa == PgckekYbUK){CYxQSCaHHj = true;}
      if(AAeqnbQAmS == rRBPBcnbWL){DDCQAMSznD = true;}
      if(KOdttWYOAX == BJwWrfFSTC){eHuRNOxZNZ = true;}
      while(PgckekYbUK == MIXBrPFhaa){EDRzKClmbU = true;}
      while(rRBPBcnbWL == rRBPBcnbWL){lKfmPPBhEe = true;}
      while(BJwWrfFSTC == BJwWrfFSTC){cAlMfAZXqe = true;}
      if(RyDsbljRat == true){RyDsbljRat = false;}
      if(VEHOSQgleL == true){VEHOSQgleL = false;}
      if(YcjxgFkGrz == true){YcjxgFkGrz = false;}
      if(fGISstNHnO == true){fGISstNHnO = false;}
      if(rVBbowCgDb == true){rVBbowCgDb = false;}
      if(ySnIdoOGMV == true){ySnIdoOGMV = false;}
      if(BdYaOPwoVY == true){BdYaOPwoVY = false;}
      if(CYxQSCaHHj == true){CYxQSCaHHj = false;}
      if(DDCQAMSznD == true){DDCQAMSznD = false;}
      if(eHuRNOxZNZ == true){eHuRNOxZNZ = false;}
      if(AMKeYYVXpa == true){AMKeYYVXpa = false;}
      if(NGybSxaIaB == true){NGybSxaIaB = false;}
      if(xwARsudeCD == true){xwARsudeCD = false;}
      if(FBthipsXqa == true){FBthipsXqa = false;}
      if(qtJNpYISzP == true){qtJNpYISzP = false;}
      if(nozLcEMrkd == true){nozLcEMrkd = false;}
      if(upUlVLMQrc == true){upUlVLMQrc = false;}
      if(EDRzKClmbU == true){EDRzKClmbU = false;}
      if(lKfmPPBhEe == true){lKfmPPBhEe = false;}
      if(cAlMfAZXqe == true){cAlMfAZXqe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWOWQTRYUT
{ 
  void tGAzeQEWBM()
  { 
      bool JePGjmuQPU = false;
      bool MtdXmppfVd = false;
      bool JqYfOMjUbW = false;
      bool cPqDdOmuHS = false;
      bool sWQlHjosPm = false;
      bool ATtWaSGjqW = false;
      bool DaorrwDatY = false;
      bool CtXCjlZmYe = false;
      bool WpEnWIVTcL = false;
      bool IDDjPShXsK = false;
      bool fOzqkGurlo = false;
      bool sSLMAMVAVi = false;
      bool ZiyiQzpnlQ = false;
      bool EBsNyIqMDQ = false;
      bool NdgmRorqjD = false;
      bool wgCKjwQQal = false;
      bool PHFVjqZxNq = false;
      bool VIxFVwCKQb = false;
      bool GzDiTXzicC = false;
      bool qZlRAFXLCa = false;
      string sAuUlZZtMG;
      string itNXQlOrXh;
      string uZiGePdfNx;
      string gdGHKfjRfe;
      string PJOzDDCCSo;
      string LFYpMTRnoW;
      string usgOYFmFMj;
      string CxLrRkKjDb;
      string MbMXlbEPup;
      string OwcJjVczZy;
      string PwohmOsgXb;
      string IgkMJSgIcw;
      string AWKWVFTBIw;
      string IKJEMQmekX;
      string hXqShgLQzQ;
      string oTWdxrlSMg;
      string trXbSxWfAs;
      string fBXFNcfqnn;
      string tDBrGonfGT;
      string dTRDdpzPAj;
      if(sAuUlZZtMG == PwohmOsgXb){JePGjmuQPU = true;}
      else if(PwohmOsgXb == sAuUlZZtMG){fOzqkGurlo = true;}
      if(itNXQlOrXh == IgkMJSgIcw){MtdXmppfVd = true;}
      else if(IgkMJSgIcw == itNXQlOrXh){sSLMAMVAVi = true;}
      if(uZiGePdfNx == AWKWVFTBIw){JqYfOMjUbW = true;}
      else if(AWKWVFTBIw == uZiGePdfNx){ZiyiQzpnlQ = true;}
      if(gdGHKfjRfe == IKJEMQmekX){cPqDdOmuHS = true;}
      else if(IKJEMQmekX == gdGHKfjRfe){EBsNyIqMDQ = true;}
      if(PJOzDDCCSo == hXqShgLQzQ){sWQlHjosPm = true;}
      else if(hXqShgLQzQ == PJOzDDCCSo){NdgmRorqjD = true;}
      if(LFYpMTRnoW == oTWdxrlSMg){ATtWaSGjqW = true;}
      else if(oTWdxrlSMg == LFYpMTRnoW){wgCKjwQQal = true;}
      if(usgOYFmFMj == trXbSxWfAs){DaorrwDatY = true;}
      else if(trXbSxWfAs == usgOYFmFMj){PHFVjqZxNq = true;}
      if(CxLrRkKjDb == fBXFNcfqnn){CtXCjlZmYe = true;}
      if(MbMXlbEPup == tDBrGonfGT){WpEnWIVTcL = true;}
      if(OwcJjVczZy == dTRDdpzPAj){IDDjPShXsK = true;}
      while(fBXFNcfqnn == CxLrRkKjDb){VIxFVwCKQb = true;}
      while(tDBrGonfGT == tDBrGonfGT){GzDiTXzicC = true;}
      while(dTRDdpzPAj == dTRDdpzPAj){qZlRAFXLCa = true;}
      if(JePGjmuQPU == true){JePGjmuQPU = false;}
      if(MtdXmppfVd == true){MtdXmppfVd = false;}
      if(JqYfOMjUbW == true){JqYfOMjUbW = false;}
      if(cPqDdOmuHS == true){cPqDdOmuHS = false;}
      if(sWQlHjosPm == true){sWQlHjosPm = false;}
      if(ATtWaSGjqW == true){ATtWaSGjqW = false;}
      if(DaorrwDatY == true){DaorrwDatY = false;}
      if(CtXCjlZmYe == true){CtXCjlZmYe = false;}
      if(WpEnWIVTcL == true){WpEnWIVTcL = false;}
      if(IDDjPShXsK == true){IDDjPShXsK = false;}
      if(fOzqkGurlo == true){fOzqkGurlo = false;}
      if(sSLMAMVAVi == true){sSLMAMVAVi = false;}
      if(ZiyiQzpnlQ == true){ZiyiQzpnlQ = false;}
      if(EBsNyIqMDQ == true){EBsNyIqMDQ = false;}
      if(NdgmRorqjD == true){NdgmRorqjD = false;}
      if(wgCKjwQQal == true){wgCKjwQQal = false;}
      if(PHFVjqZxNq == true){PHFVjqZxNq = false;}
      if(VIxFVwCKQb == true){VIxFVwCKQb = false;}
      if(GzDiTXzicC == true){GzDiTXzicC = false;}
      if(qZlRAFXLCa == true){qZlRAFXLCa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYHMOTHLPP
{ 
  void VUhDFUgVnq()
  { 
      bool UDmTXDzUOR = false;
      bool SbQRoaIsSk = false;
      bool JNblDKPNYn = false;
      bool NbIuEHufsC = false;
      bool koLJMNUdPj = false;
      bool aOacYGaAPN = false;
      bool nlwZEpSUMg = false;
      bool fbAPzTCRZp = false;
      bool okxnMzAfWy = false;
      bool fuQfOzskFV = false;
      bool tARhEzOLcE = false;
      bool DIaYXCnHNF = false;
      bool omyOAjKUAA = false;
      bool ZRMDwoTPiM = false;
      bool joCRtWUqHL = false;
      bool LlXzfGBCgU = false;
      bool ntKcelwWci = false;
      bool iXXAUAkgUd = false;
      bool PTMoomtNWo = false;
      bool mRhOYpdZlH = false;
      string uPhNjByUfV;
      string AybkTXIcTQ;
      string TayYdJNicB;
      string quuQLahbVk;
      string eeshgfPDTH;
      string ecfgKTQJja;
      string mOrdeECLZs;
      string ofHilngQqx;
      string sKOVVNPNFq;
      string JXrtxPmPDb;
      string cEdaRzVwuW;
      string mARlhczVIQ;
      string onFhiRnMlV;
      string BRMOTngnEW;
      string rSSiDIGFMT;
      string PQGmmnyurA;
      string KIKYUUnDRs;
      string wLRkXVVWeZ;
      string KiARGjKZae;
      string okwELjHsNi;
      if(uPhNjByUfV == cEdaRzVwuW){UDmTXDzUOR = true;}
      else if(cEdaRzVwuW == uPhNjByUfV){tARhEzOLcE = true;}
      if(AybkTXIcTQ == mARlhczVIQ){SbQRoaIsSk = true;}
      else if(mARlhczVIQ == AybkTXIcTQ){DIaYXCnHNF = true;}
      if(TayYdJNicB == onFhiRnMlV){JNblDKPNYn = true;}
      else if(onFhiRnMlV == TayYdJNicB){omyOAjKUAA = true;}
      if(quuQLahbVk == BRMOTngnEW){NbIuEHufsC = true;}
      else if(BRMOTngnEW == quuQLahbVk){ZRMDwoTPiM = true;}
      if(eeshgfPDTH == rSSiDIGFMT){koLJMNUdPj = true;}
      else if(rSSiDIGFMT == eeshgfPDTH){joCRtWUqHL = true;}
      if(ecfgKTQJja == PQGmmnyurA){aOacYGaAPN = true;}
      else if(PQGmmnyurA == ecfgKTQJja){LlXzfGBCgU = true;}
      if(mOrdeECLZs == KIKYUUnDRs){nlwZEpSUMg = true;}
      else if(KIKYUUnDRs == mOrdeECLZs){ntKcelwWci = true;}
      if(ofHilngQqx == wLRkXVVWeZ){fbAPzTCRZp = true;}
      if(sKOVVNPNFq == KiARGjKZae){okxnMzAfWy = true;}
      if(JXrtxPmPDb == okwELjHsNi){fuQfOzskFV = true;}
      while(wLRkXVVWeZ == ofHilngQqx){iXXAUAkgUd = true;}
      while(KiARGjKZae == KiARGjKZae){PTMoomtNWo = true;}
      while(okwELjHsNi == okwELjHsNi){mRhOYpdZlH = true;}
      if(UDmTXDzUOR == true){UDmTXDzUOR = false;}
      if(SbQRoaIsSk == true){SbQRoaIsSk = false;}
      if(JNblDKPNYn == true){JNblDKPNYn = false;}
      if(NbIuEHufsC == true){NbIuEHufsC = false;}
      if(koLJMNUdPj == true){koLJMNUdPj = false;}
      if(aOacYGaAPN == true){aOacYGaAPN = false;}
      if(nlwZEpSUMg == true){nlwZEpSUMg = false;}
      if(fbAPzTCRZp == true){fbAPzTCRZp = false;}
      if(okxnMzAfWy == true){okxnMzAfWy = false;}
      if(fuQfOzskFV == true){fuQfOzskFV = false;}
      if(tARhEzOLcE == true){tARhEzOLcE = false;}
      if(DIaYXCnHNF == true){DIaYXCnHNF = false;}
      if(omyOAjKUAA == true){omyOAjKUAA = false;}
      if(ZRMDwoTPiM == true){ZRMDwoTPiM = false;}
      if(joCRtWUqHL == true){joCRtWUqHL = false;}
      if(LlXzfGBCgU == true){LlXzfGBCgU = false;}
      if(ntKcelwWci == true){ntKcelwWci = false;}
      if(iXXAUAkgUd == true){iXXAUAkgUd = false;}
      if(PTMoomtNWo == true){PTMoomtNWo = false;}
      if(mRhOYpdZlH == true){mRhOYpdZlH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USIUQPZGTY
{ 
  void yNFrXAlqwq()
  { 
      bool ulirFBBwcu = false;
      bool NeRVlPkAQf = false;
      bool eNaTMDZgOV = false;
      bool dxdkGQxwsi = false;
      bool KRHKLfxCjh = false;
      bool TdXKcgKOfB = false;
      bool bThHRQAfPV = false;
      bool SoHhVNGQIf = false;
      bool FWwgCzZTIY = false;
      bool FhQqHpjzst = false;
      bool fQmNOeWpnP = false;
      bool ZtFzuEXBFR = false;
      bool qfXpQjXPZe = false;
      bool cHXOzoiiRX = false;
      bool cjesyLcRuC = false;
      bool SitaDAsxxe = false;
      bool GGPJlSVqzG = false;
      bool VnihoHBeqE = false;
      bool HGTXMtMwKz = false;
      bool wlklQVTVGe = false;
      string CQdNUgdIKP;
      string yHhlznYFep;
      string rAcjpTFQTH;
      string xJzkVUFTAr;
      string IIPcglDXzu;
      string JkIUrCmtWA;
      string aMnCSnIxQd;
      string hFFmgjjzCD;
      string QhRYxLAerT;
      string hLwzQuTNKr;
      string dFHUMEfVmI;
      string RmqTisuPEG;
      string ncFwwWIFVk;
      string PWoKZLZxLs;
      string feqiCtTcPX;
      string AEIEEAALXo;
      string uazCrtygsX;
      string SyDLaJlVsC;
      string DfoykLOjFY;
      string LOYWxFeoqI;
      if(CQdNUgdIKP == dFHUMEfVmI){ulirFBBwcu = true;}
      else if(dFHUMEfVmI == CQdNUgdIKP){fQmNOeWpnP = true;}
      if(yHhlznYFep == RmqTisuPEG){NeRVlPkAQf = true;}
      else if(RmqTisuPEG == yHhlznYFep){ZtFzuEXBFR = true;}
      if(rAcjpTFQTH == ncFwwWIFVk){eNaTMDZgOV = true;}
      else if(ncFwwWIFVk == rAcjpTFQTH){qfXpQjXPZe = true;}
      if(xJzkVUFTAr == PWoKZLZxLs){dxdkGQxwsi = true;}
      else if(PWoKZLZxLs == xJzkVUFTAr){cHXOzoiiRX = true;}
      if(IIPcglDXzu == feqiCtTcPX){KRHKLfxCjh = true;}
      else if(feqiCtTcPX == IIPcglDXzu){cjesyLcRuC = true;}
      if(JkIUrCmtWA == AEIEEAALXo){TdXKcgKOfB = true;}
      else if(AEIEEAALXo == JkIUrCmtWA){SitaDAsxxe = true;}
      if(aMnCSnIxQd == uazCrtygsX){bThHRQAfPV = true;}
      else if(uazCrtygsX == aMnCSnIxQd){GGPJlSVqzG = true;}
      if(hFFmgjjzCD == SyDLaJlVsC){SoHhVNGQIf = true;}
      if(QhRYxLAerT == DfoykLOjFY){FWwgCzZTIY = true;}
      if(hLwzQuTNKr == LOYWxFeoqI){FhQqHpjzst = true;}
      while(SyDLaJlVsC == hFFmgjjzCD){VnihoHBeqE = true;}
      while(DfoykLOjFY == DfoykLOjFY){HGTXMtMwKz = true;}
      while(LOYWxFeoqI == LOYWxFeoqI){wlklQVTVGe = true;}
      if(ulirFBBwcu == true){ulirFBBwcu = false;}
      if(NeRVlPkAQf == true){NeRVlPkAQf = false;}
      if(eNaTMDZgOV == true){eNaTMDZgOV = false;}
      if(dxdkGQxwsi == true){dxdkGQxwsi = false;}
      if(KRHKLfxCjh == true){KRHKLfxCjh = false;}
      if(TdXKcgKOfB == true){TdXKcgKOfB = false;}
      if(bThHRQAfPV == true){bThHRQAfPV = false;}
      if(SoHhVNGQIf == true){SoHhVNGQIf = false;}
      if(FWwgCzZTIY == true){FWwgCzZTIY = false;}
      if(FhQqHpjzst == true){FhQqHpjzst = false;}
      if(fQmNOeWpnP == true){fQmNOeWpnP = false;}
      if(ZtFzuEXBFR == true){ZtFzuEXBFR = false;}
      if(qfXpQjXPZe == true){qfXpQjXPZe = false;}
      if(cHXOzoiiRX == true){cHXOzoiiRX = false;}
      if(cjesyLcRuC == true){cjesyLcRuC = false;}
      if(SitaDAsxxe == true){SitaDAsxxe = false;}
      if(GGPJlSVqzG == true){GGPJlSVqzG = false;}
      if(VnihoHBeqE == true){VnihoHBeqE = false;}
      if(HGTXMtMwKz == true){HGTXMtMwKz = false;}
      if(wlklQVTVGe == true){wlklQVTVGe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFALSANJVB
{ 
  void TImdyVWzQm()
  { 
      bool YEYiQjLHbZ = false;
      bool FbjyaNBmts = false;
      bool yKVQKwhsJD = false;
      bool lTEVPdzYgW = false;
      bool PCFzmObqxs = false;
      bool ZBOewNhHXT = false;
      bool BRyYnkWOhx = false;
      bool NbFWdwFWdu = false;
      bool UqwQcjFYZB = false;
      bool uqBMVxEgKB = false;
      bool qMIzeyuqBA = false;
      bool ILdbzJVguE = false;
      bool fxogCWasBf = false;
      bool qXLbDHiwle = false;
      bool nNXZriNYNL = false;
      bool aWkGVsXbxH = false;
      bool WCoVIjABXq = false;
      bool aZuQPRZPnS = false;
      bool JBfpEUmEGJ = false;
      bool jHzdHlYCQH = false;
      string nVDNRNiBmT;
      string kaUMnXXmNA;
      string qigGfsMOYx;
      string RENezlSzJw;
      string cHUWfiSgtx;
      string OfYmKFowgY;
      string BUboBfNpNB;
      string EXcRWjNJax;
      string ZfTahlfZTt;
      string wVSjtIeeVA;
      string VcSrrqCHPZ;
      string qfVjzUAAHO;
      string zmWSFiFsWO;
      string FhnZaxMbiq;
      string jYJsDQAhkZ;
      string HdXGAhFAmJ;
      string kIjBUIruJC;
      string IXRPeaccPn;
      string hXHxGaKgZr;
      string qLoYGanIYt;
      if(nVDNRNiBmT == VcSrrqCHPZ){YEYiQjLHbZ = true;}
      else if(VcSrrqCHPZ == nVDNRNiBmT){qMIzeyuqBA = true;}
      if(kaUMnXXmNA == qfVjzUAAHO){FbjyaNBmts = true;}
      else if(qfVjzUAAHO == kaUMnXXmNA){ILdbzJVguE = true;}
      if(qigGfsMOYx == zmWSFiFsWO){yKVQKwhsJD = true;}
      else if(zmWSFiFsWO == qigGfsMOYx){fxogCWasBf = true;}
      if(RENezlSzJw == FhnZaxMbiq){lTEVPdzYgW = true;}
      else if(FhnZaxMbiq == RENezlSzJw){qXLbDHiwle = true;}
      if(cHUWfiSgtx == jYJsDQAhkZ){PCFzmObqxs = true;}
      else if(jYJsDQAhkZ == cHUWfiSgtx){nNXZriNYNL = true;}
      if(OfYmKFowgY == HdXGAhFAmJ){ZBOewNhHXT = true;}
      else if(HdXGAhFAmJ == OfYmKFowgY){aWkGVsXbxH = true;}
      if(BUboBfNpNB == kIjBUIruJC){BRyYnkWOhx = true;}
      else if(kIjBUIruJC == BUboBfNpNB){WCoVIjABXq = true;}
      if(EXcRWjNJax == IXRPeaccPn){NbFWdwFWdu = true;}
      if(ZfTahlfZTt == hXHxGaKgZr){UqwQcjFYZB = true;}
      if(wVSjtIeeVA == qLoYGanIYt){uqBMVxEgKB = true;}
      while(IXRPeaccPn == EXcRWjNJax){aZuQPRZPnS = true;}
      while(hXHxGaKgZr == hXHxGaKgZr){JBfpEUmEGJ = true;}
      while(qLoYGanIYt == qLoYGanIYt){jHzdHlYCQH = true;}
      if(YEYiQjLHbZ == true){YEYiQjLHbZ = false;}
      if(FbjyaNBmts == true){FbjyaNBmts = false;}
      if(yKVQKwhsJD == true){yKVQKwhsJD = false;}
      if(lTEVPdzYgW == true){lTEVPdzYgW = false;}
      if(PCFzmObqxs == true){PCFzmObqxs = false;}
      if(ZBOewNhHXT == true){ZBOewNhHXT = false;}
      if(BRyYnkWOhx == true){BRyYnkWOhx = false;}
      if(NbFWdwFWdu == true){NbFWdwFWdu = false;}
      if(UqwQcjFYZB == true){UqwQcjFYZB = false;}
      if(uqBMVxEgKB == true){uqBMVxEgKB = false;}
      if(qMIzeyuqBA == true){qMIzeyuqBA = false;}
      if(ILdbzJVguE == true){ILdbzJVguE = false;}
      if(fxogCWasBf == true){fxogCWasBf = false;}
      if(qXLbDHiwle == true){qXLbDHiwle = false;}
      if(nNXZriNYNL == true){nNXZriNYNL = false;}
      if(aWkGVsXbxH == true){aWkGVsXbxH = false;}
      if(WCoVIjABXq == true){WCoVIjABXq = false;}
      if(aZuQPRZPnS == true){aZuQPRZPnS = false;}
      if(JBfpEUmEGJ == true){JBfpEUmEGJ = false;}
      if(jHzdHlYCQH == true){jHzdHlYCQH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJTIPTKBKV
{ 
  void CBZauYIOOR()
  { 
      bool aajpPTZVAP = false;
      bool txmtQbfXmW = false;
      bool NotoKDnSUf = false;
      bool QahMBbtnHA = false;
      bool EXbEsaKjxx = false;
      bool ZmpKCkfufL = false;
      bool fGBUySPZso = false;
      bool hrQlRoMpui = false;
      bool sEUWFdjWJP = false;
      bool uyIuUxVHFa = false;
      bool KjqIPhWDsM = false;
      bool YpAwSaleOU = false;
      bool hsPdsijURU = false;
      bool SFkUXINMHX = false;
      bool GgdwpFyLbs = false;
      bool LqsjrRUNOf = false;
      bool xBlXtSEfXK = false;
      bool NYWpOBOSmn = false;
      bool jXsXIbMAbG = false;
      bool nzxaZEtFCX = false;
      string KUDxsodMAk;
      string TXVDBnmPyY;
      string YrinHZrVJx;
      string zufFJJfROc;
      string MVrcAgbLgS;
      string SQEcmSlPoT;
      string wHDDlYrQsq;
      string IUAVMCzFna;
      string xgoqdhpCSq;
      string XQcugESoqa;
      string nLSoKyQiQj;
      string SfaOVPRMYE;
      string ipyCTqrEnH;
      string jKOMllNzff;
      string RGlhYroNZQ;
      string mFPlryNQVS;
      string GLuIAIQOci;
      string BSfslbEPcb;
      string CdeWUdtbTn;
      string YxdNYGLchQ;
      if(KUDxsodMAk == nLSoKyQiQj){aajpPTZVAP = true;}
      else if(nLSoKyQiQj == KUDxsodMAk){KjqIPhWDsM = true;}
      if(TXVDBnmPyY == SfaOVPRMYE){txmtQbfXmW = true;}
      else if(SfaOVPRMYE == TXVDBnmPyY){YpAwSaleOU = true;}
      if(YrinHZrVJx == ipyCTqrEnH){NotoKDnSUf = true;}
      else if(ipyCTqrEnH == YrinHZrVJx){hsPdsijURU = true;}
      if(zufFJJfROc == jKOMllNzff){QahMBbtnHA = true;}
      else if(jKOMllNzff == zufFJJfROc){SFkUXINMHX = true;}
      if(MVrcAgbLgS == RGlhYroNZQ){EXbEsaKjxx = true;}
      else if(RGlhYroNZQ == MVrcAgbLgS){GgdwpFyLbs = true;}
      if(SQEcmSlPoT == mFPlryNQVS){ZmpKCkfufL = true;}
      else if(mFPlryNQVS == SQEcmSlPoT){LqsjrRUNOf = true;}
      if(wHDDlYrQsq == GLuIAIQOci){fGBUySPZso = true;}
      else if(GLuIAIQOci == wHDDlYrQsq){xBlXtSEfXK = true;}
      if(IUAVMCzFna == BSfslbEPcb){hrQlRoMpui = true;}
      if(xgoqdhpCSq == CdeWUdtbTn){sEUWFdjWJP = true;}
      if(XQcugESoqa == YxdNYGLchQ){uyIuUxVHFa = true;}
      while(BSfslbEPcb == IUAVMCzFna){NYWpOBOSmn = true;}
      while(CdeWUdtbTn == CdeWUdtbTn){jXsXIbMAbG = true;}
      while(YxdNYGLchQ == YxdNYGLchQ){nzxaZEtFCX = true;}
      if(aajpPTZVAP == true){aajpPTZVAP = false;}
      if(txmtQbfXmW == true){txmtQbfXmW = false;}
      if(NotoKDnSUf == true){NotoKDnSUf = false;}
      if(QahMBbtnHA == true){QahMBbtnHA = false;}
      if(EXbEsaKjxx == true){EXbEsaKjxx = false;}
      if(ZmpKCkfufL == true){ZmpKCkfufL = false;}
      if(fGBUySPZso == true){fGBUySPZso = false;}
      if(hrQlRoMpui == true){hrQlRoMpui = false;}
      if(sEUWFdjWJP == true){sEUWFdjWJP = false;}
      if(uyIuUxVHFa == true){uyIuUxVHFa = false;}
      if(KjqIPhWDsM == true){KjqIPhWDsM = false;}
      if(YpAwSaleOU == true){YpAwSaleOU = false;}
      if(hsPdsijURU == true){hsPdsijURU = false;}
      if(SFkUXINMHX == true){SFkUXINMHX = false;}
      if(GgdwpFyLbs == true){GgdwpFyLbs = false;}
      if(LqsjrRUNOf == true){LqsjrRUNOf = false;}
      if(xBlXtSEfXK == true){xBlXtSEfXK = false;}
      if(NYWpOBOSmn == true){NYWpOBOSmn = false;}
      if(jXsXIbMAbG == true){jXsXIbMAbG = false;}
      if(nzxaZEtFCX == true){nzxaZEtFCX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMFOSBFXMT
{ 
  void KMTdMfrNpz()
  { 
      bool aZEDjBABBA = false;
      bool aOLWDtKVrL = false;
      bool KmpHbVNPuK = false;
      bool yxlBzyOzJo = false;
      bool ZfYkzDPaer = false;
      bool yDScOmiwbO = false;
      bool mjGqCcbJXF = false;
      bool fKMDldOFHX = false;
      bool FmkDLtdJmM = false;
      bool ORXtBpZhiV = false;
      bool bFCZMmpPqj = false;
      bool YdoEIAzDeH = false;
      bool yRWLpNmRBu = false;
      bool EfWluAjLpX = false;
      bool EOSCmkcSkB = false;
      bool qWCbXJhqiy = false;
      bool AYNufrGCII = false;
      bool PnMGDjzUXF = false;
      bool kTfAEgduNk = false;
      bool RrbrXeAXVt = false;
      string oNzGojNDMe;
      string ccfkjewBGP;
      string TxuUSlkseO;
      string ClrmSSRPBo;
      string piOnbWkugQ;
      string xPGLyrRdmC;
      string zUYycqjrRR;
      string NgAQZkhHsw;
      string ApLNQlegoa;
      string AmbzpVKQLj;
      string mscPCQPplN;
      string JKkqBJIKgp;
      string MDDqQaEBZD;
      string aRwIJHMwLz;
      string WotbQpCkxg;
      string NziUXjokyb;
      string MNPimrObgs;
      string wLzhSXIaZa;
      string YSDspahakZ;
      string RayilIYLoY;
      if(oNzGojNDMe == mscPCQPplN){aZEDjBABBA = true;}
      else if(mscPCQPplN == oNzGojNDMe){bFCZMmpPqj = true;}
      if(ccfkjewBGP == JKkqBJIKgp){aOLWDtKVrL = true;}
      else if(JKkqBJIKgp == ccfkjewBGP){YdoEIAzDeH = true;}
      if(TxuUSlkseO == MDDqQaEBZD){KmpHbVNPuK = true;}
      else if(MDDqQaEBZD == TxuUSlkseO){yRWLpNmRBu = true;}
      if(ClrmSSRPBo == aRwIJHMwLz){yxlBzyOzJo = true;}
      else if(aRwIJHMwLz == ClrmSSRPBo){EfWluAjLpX = true;}
      if(piOnbWkugQ == WotbQpCkxg){ZfYkzDPaer = true;}
      else if(WotbQpCkxg == piOnbWkugQ){EOSCmkcSkB = true;}
      if(xPGLyrRdmC == NziUXjokyb){yDScOmiwbO = true;}
      else if(NziUXjokyb == xPGLyrRdmC){qWCbXJhqiy = true;}
      if(zUYycqjrRR == MNPimrObgs){mjGqCcbJXF = true;}
      else if(MNPimrObgs == zUYycqjrRR){AYNufrGCII = true;}
      if(NgAQZkhHsw == wLzhSXIaZa){fKMDldOFHX = true;}
      if(ApLNQlegoa == YSDspahakZ){FmkDLtdJmM = true;}
      if(AmbzpVKQLj == RayilIYLoY){ORXtBpZhiV = true;}
      while(wLzhSXIaZa == NgAQZkhHsw){PnMGDjzUXF = true;}
      while(YSDspahakZ == YSDspahakZ){kTfAEgduNk = true;}
      while(RayilIYLoY == RayilIYLoY){RrbrXeAXVt = true;}
      if(aZEDjBABBA == true){aZEDjBABBA = false;}
      if(aOLWDtKVrL == true){aOLWDtKVrL = false;}
      if(KmpHbVNPuK == true){KmpHbVNPuK = false;}
      if(yxlBzyOzJo == true){yxlBzyOzJo = false;}
      if(ZfYkzDPaer == true){ZfYkzDPaer = false;}
      if(yDScOmiwbO == true){yDScOmiwbO = false;}
      if(mjGqCcbJXF == true){mjGqCcbJXF = false;}
      if(fKMDldOFHX == true){fKMDldOFHX = false;}
      if(FmkDLtdJmM == true){FmkDLtdJmM = false;}
      if(ORXtBpZhiV == true){ORXtBpZhiV = false;}
      if(bFCZMmpPqj == true){bFCZMmpPqj = false;}
      if(YdoEIAzDeH == true){YdoEIAzDeH = false;}
      if(yRWLpNmRBu == true){yRWLpNmRBu = false;}
      if(EfWluAjLpX == true){EfWluAjLpX = false;}
      if(EOSCmkcSkB == true){EOSCmkcSkB = false;}
      if(qWCbXJhqiy == true){qWCbXJhqiy = false;}
      if(AYNufrGCII == true){AYNufrGCII = false;}
      if(PnMGDjzUXF == true){PnMGDjzUXF = false;}
      if(kTfAEgduNk == true){kTfAEgduNk = false;}
      if(RrbrXeAXVt == true){RrbrXeAXVt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCPORSYFMG
{ 
  void MDHbUTzEUl()
  { 
      bool aHWoInxBwF = false;
      bool ShkdpHUbUK = false;
      bool FsdSzKBVBz = false;
      bool EpYipCXfJd = false;
      bool gBWkXjdGEW = false;
      bool ojxzUgcDoy = false;
      bool lbAwBcIBmn = false;
      bool joRqcEVsuP = false;
      bool fuQdJTrZOI = false;
      bool YUpLqFAaju = false;
      bool acSQmASFVP = false;
      bool KjIZRqKWlg = false;
      bool jileOPyFAX = false;
      bool DuIAoCbAqJ = false;
      bool BlEyxoMQsz = false;
      bool ucnDKqqnCX = false;
      bool CMFxMPaHkP = false;
      bool PJecexemgZ = false;
      bool ChMAcZGFox = false;
      bool LmyTHogGlh = false;
      string fAhgocLHxm;
      string xJDWfGVaNe;
      string fEalzEzNQW;
      string NSGjDAHnrt;
      string rOWmarTFgj;
      string LyOTAbZuhk;
      string cypZYdCSTf;
      string yghSmRhmLH;
      string jtffLPEmib;
      string aMGHQsXwOx;
      string pAkAldPwgi;
      string sljaAiRKOI;
      string ZOiqFlaaBs;
      string skYOQiJfth;
      string zHGAhnbfGh;
      string aNhFXaRtuz;
      string CoumpIMUJR;
      string ZlPfJRIiJQ;
      string JtUSReDTqp;
      string ROjteJMSKZ;
      if(fAhgocLHxm == pAkAldPwgi){aHWoInxBwF = true;}
      else if(pAkAldPwgi == fAhgocLHxm){acSQmASFVP = true;}
      if(xJDWfGVaNe == sljaAiRKOI){ShkdpHUbUK = true;}
      else if(sljaAiRKOI == xJDWfGVaNe){KjIZRqKWlg = true;}
      if(fEalzEzNQW == ZOiqFlaaBs){FsdSzKBVBz = true;}
      else if(ZOiqFlaaBs == fEalzEzNQW){jileOPyFAX = true;}
      if(NSGjDAHnrt == skYOQiJfth){EpYipCXfJd = true;}
      else if(skYOQiJfth == NSGjDAHnrt){DuIAoCbAqJ = true;}
      if(rOWmarTFgj == zHGAhnbfGh){gBWkXjdGEW = true;}
      else if(zHGAhnbfGh == rOWmarTFgj){BlEyxoMQsz = true;}
      if(LyOTAbZuhk == aNhFXaRtuz){ojxzUgcDoy = true;}
      else if(aNhFXaRtuz == LyOTAbZuhk){ucnDKqqnCX = true;}
      if(cypZYdCSTf == CoumpIMUJR){lbAwBcIBmn = true;}
      else if(CoumpIMUJR == cypZYdCSTf){CMFxMPaHkP = true;}
      if(yghSmRhmLH == ZlPfJRIiJQ){joRqcEVsuP = true;}
      if(jtffLPEmib == JtUSReDTqp){fuQdJTrZOI = true;}
      if(aMGHQsXwOx == ROjteJMSKZ){YUpLqFAaju = true;}
      while(ZlPfJRIiJQ == yghSmRhmLH){PJecexemgZ = true;}
      while(JtUSReDTqp == JtUSReDTqp){ChMAcZGFox = true;}
      while(ROjteJMSKZ == ROjteJMSKZ){LmyTHogGlh = true;}
      if(aHWoInxBwF == true){aHWoInxBwF = false;}
      if(ShkdpHUbUK == true){ShkdpHUbUK = false;}
      if(FsdSzKBVBz == true){FsdSzKBVBz = false;}
      if(EpYipCXfJd == true){EpYipCXfJd = false;}
      if(gBWkXjdGEW == true){gBWkXjdGEW = false;}
      if(ojxzUgcDoy == true){ojxzUgcDoy = false;}
      if(lbAwBcIBmn == true){lbAwBcIBmn = false;}
      if(joRqcEVsuP == true){joRqcEVsuP = false;}
      if(fuQdJTrZOI == true){fuQdJTrZOI = false;}
      if(YUpLqFAaju == true){YUpLqFAaju = false;}
      if(acSQmASFVP == true){acSQmASFVP = false;}
      if(KjIZRqKWlg == true){KjIZRqKWlg = false;}
      if(jileOPyFAX == true){jileOPyFAX = false;}
      if(DuIAoCbAqJ == true){DuIAoCbAqJ = false;}
      if(BlEyxoMQsz == true){BlEyxoMQsz = false;}
      if(ucnDKqqnCX == true){ucnDKqqnCX = false;}
      if(CMFxMPaHkP == true){CMFxMPaHkP = false;}
      if(PJecexemgZ == true){PJecexemgZ = false;}
      if(ChMAcZGFox == true){ChMAcZGFox = false;}
      if(LmyTHogGlh == true){LmyTHogGlh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVZJLFHFJY
{ 
  void DADlYgppJf()
  { 
      bool ljnmchPVSn = false;
      bool dMccHTDhdy = false;
      bool wGfnZxyUYi = false;
      bool DRGcYTrTXt = false;
      bool hUjQupOrwc = false;
      bool oplOseEzMe = false;
      bool itxijMGAEm = false;
      bool aiKiQbWPsi = false;
      bool iGXwtMerjs = false;
      bool PsHrLmXBfh = false;
      bool jOnIBGfDyR = false;
      bool IoGcwcVAnW = false;
      bool gNQKXhbRXc = false;
      bool DViKzTSPtn = false;
      bool gbtSkZmduh = false;
      bool QWMIBWycjT = false;
      bool eNfUNmFudb = false;
      bool KGGApFSyZy = false;
      bool uxWoLgIaJb = false;
      bool VoeZITwYEy = false;
      string Lyolcfndxs;
      string cSJDowppdZ;
      string mzTPhVTGlz;
      string ZhFpJgyFlK;
      string NWHtueclCj;
      string TmWxyMeYDH;
      string MhryTuNTsI;
      string yjDSLQqYUD;
      string sgDCfmLIqx;
      string BYCeyfdJaA;
      string QIrtkiiDlh;
      string UGEANedoRf;
      string jEcuGYhYTe;
      string lhxUljoJQw;
      string DHWIcuUBQT;
      string CnquPMfwnM;
      string AKiGwmJjNd;
      string pTYVcbhTSK;
      string EfHAcxpCEZ;
      string DrVEwsYPMp;
      if(Lyolcfndxs == QIrtkiiDlh){ljnmchPVSn = true;}
      else if(QIrtkiiDlh == Lyolcfndxs){jOnIBGfDyR = true;}
      if(cSJDowppdZ == UGEANedoRf){dMccHTDhdy = true;}
      else if(UGEANedoRf == cSJDowppdZ){IoGcwcVAnW = true;}
      if(mzTPhVTGlz == jEcuGYhYTe){wGfnZxyUYi = true;}
      else if(jEcuGYhYTe == mzTPhVTGlz){gNQKXhbRXc = true;}
      if(ZhFpJgyFlK == lhxUljoJQw){DRGcYTrTXt = true;}
      else if(lhxUljoJQw == ZhFpJgyFlK){DViKzTSPtn = true;}
      if(NWHtueclCj == DHWIcuUBQT){hUjQupOrwc = true;}
      else if(DHWIcuUBQT == NWHtueclCj){gbtSkZmduh = true;}
      if(TmWxyMeYDH == CnquPMfwnM){oplOseEzMe = true;}
      else if(CnquPMfwnM == TmWxyMeYDH){QWMIBWycjT = true;}
      if(MhryTuNTsI == AKiGwmJjNd){itxijMGAEm = true;}
      else if(AKiGwmJjNd == MhryTuNTsI){eNfUNmFudb = true;}
      if(yjDSLQqYUD == pTYVcbhTSK){aiKiQbWPsi = true;}
      if(sgDCfmLIqx == EfHAcxpCEZ){iGXwtMerjs = true;}
      if(BYCeyfdJaA == DrVEwsYPMp){PsHrLmXBfh = true;}
      while(pTYVcbhTSK == yjDSLQqYUD){KGGApFSyZy = true;}
      while(EfHAcxpCEZ == EfHAcxpCEZ){uxWoLgIaJb = true;}
      while(DrVEwsYPMp == DrVEwsYPMp){VoeZITwYEy = true;}
      if(ljnmchPVSn == true){ljnmchPVSn = false;}
      if(dMccHTDhdy == true){dMccHTDhdy = false;}
      if(wGfnZxyUYi == true){wGfnZxyUYi = false;}
      if(DRGcYTrTXt == true){DRGcYTrTXt = false;}
      if(hUjQupOrwc == true){hUjQupOrwc = false;}
      if(oplOseEzMe == true){oplOseEzMe = false;}
      if(itxijMGAEm == true){itxijMGAEm = false;}
      if(aiKiQbWPsi == true){aiKiQbWPsi = false;}
      if(iGXwtMerjs == true){iGXwtMerjs = false;}
      if(PsHrLmXBfh == true){PsHrLmXBfh = false;}
      if(jOnIBGfDyR == true){jOnIBGfDyR = false;}
      if(IoGcwcVAnW == true){IoGcwcVAnW = false;}
      if(gNQKXhbRXc == true){gNQKXhbRXc = false;}
      if(DViKzTSPtn == true){DViKzTSPtn = false;}
      if(gbtSkZmduh == true){gbtSkZmduh = false;}
      if(QWMIBWycjT == true){QWMIBWycjT = false;}
      if(eNfUNmFudb == true){eNfUNmFudb = false;}
      if(KGGApFSyZy == true){KGGApFSyZy = false;}
      if(uxWoLgIaJb == true){uxWoLgIaJb = false;}
      if(VoeZITwYEy == true){VoeZITwYEy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZNNCVVNBR
{ 
  void khSjWlOzkm()
  { 
      bool OBiNdalLet = false;
      bool QmlyVNVtuW = false;
      bool rlDNQKdINx = false;
      bool RWqaeSONZd = false;
      bool uZczWjijZT = false;
      bool auJDQbxVwS = false;
      bool xcygctuLSC = false;
      bool zITRaRJEqf = false;
      bool btisVVNnKC = false;
      bool UsRGgSauVb = false;
      bool oXQXUSaqcy = false;
      bool SsdQqCsEKH = false;
      bool gHAQgFqNkH = false;
      bool pNhOqDdLYD = false;
      bool uVKLibOBOd = false;
      bool YWjOuhWzpO = false;
      bool bNGUHELPYm = false;
      bool YheHLLwngF = false;
      bool qoyHiTdTTJ = false;
      bool gdVKahOpDd = false;
      string QOQCkbFEMF;
      string wkzBIsMIop;
      string XHheMpPCTl;
      string rEFrTSeJNt;
      string aRUfnFKciX;
      string yVGHiJfkou;
      string LDkaNreHho;
      string NDtuPFlCqG;
      string emSumWyyIK;
      string msTRhXgsSu;
      string ZDtsJuaKrc;
      string WdthPYjpmq;
      string tgyXCTicMr;
      string YriwgbrYkr;
      string umFfmIzkBJ;
      string mpGaBsFWqp;
      string LxxAEdtyBn;
      string fLEtuGbRjs;
      string UybDEhlItn;
      string WVhugxoEaI;
      if(QOQCkbFEMF == ZDtsJuaKrc){OBiNdalLet = true;}
      else if(ZDtsJuaKrc == QOQCkbFEMF){oXQXUSaqcy = true;}
      if(wkzBIsMIop == WdthPYjpmq){QmlyVNVtuW = true;}
      else if(WdthPYjpmq == wkzBIsMIop){SsdQqCsEKH = true;}
      if(XHheMpPCTl == tgyXCTicMr){rlDNQKdINx = true;}
      else if(tgyXCTicMr == XHheMpPCTl){gHAQgFqNkH = true;}
      if(rEFrTSeJNt == YriwgbrYkr){RWqaeSONZd = true;}
      else if(YriwgbrYkr == rEFrTSeJNt){pNhOqDdLYD = true;}
      if(aRUfnFKciX == umFfmIzkBJ){uZczWjijZT = true;}
      else if(umFfmIzkBJ == aRUfnFKciX){uVKLibOBOd = true;}
      if(yVGHiJfkou == mpGaBsFWqp){auJDQbxVwS = true;}
      else if(mpGaBsFWqp == yVGHiJfkou){YWjOuhWzpO = true;}
      if(LDkaNreHho == LxxAEdtyBn){xcygctuLSC = true;}
      else if(LxxAEdtyBn == LDkaNreHho){bNGUHELPYm = true;}
      if(NDtuPFlCqG == fLEtuGbRjs){zITRaRJEqf = true;}
      if(emSumWyyIK == UybDEhlItn){btisVVNnKC = true;}
      if(msTRhXgsSu == WVhugxoEaI){UsRGgSauVb = true;}
      while(fLEtuGbRjs == NDtuPFlCqG){YheHLLwngF = true;}
      while(UybDEhlItn == UybDEhlItn){qoyHiTdTTJ = true;}
      while(WVhugxoEaI == WVhugxoEaI){gdVKahOpDd = true;}
      if(OBiNdalLet == true){OBiNdalLet = false;}
      if(QmlyVNVtuW == true){QmlyVNVtuW = false;}
      if(rlDNQKdINx == true){rlDNQKdINx = false;}
      if(RWqaeSONZd == true){RWqaeSONZd = false;}
      if(uZczWjijZT == true){uZczWjijZT = false;}
      if(auJDQbxVwS == true){auJDQbxVwS = false;}
      if(xcygctuLSC == true){xcygctuLSC = false;}
      if(zITRaRJEqf == true){zITRaRJEqf = false;}
      if(btisVVNnKC == true){btisVVNnKC = false;}
      if(UsRGgSauVb == true){UsRGgSauVb = false;}
      if(oXQXUSaqcy == true){oXQXUSaqcy = false;}
      if(SsdQqCsEKH == true){SsdQqCsEKH = false;}
      if(gHAQgFqNkH == true){gHAQgFqNkH = false;}
      if(pNhOqDdLYD == true){pNhOqDdLYD = false;}
      if(uVKLibOBOd == true){uVKLibOBOd = false;}
      if(YWjOuhWzpO == true){YWjOuhWzpO = false;}
      if(bNGUHELPYm == true){bNGUHELPYm = false;}
      if(YheHLLwngF == true){YheHLLwngF = false;}
      if(qoyHiTdTTJ == true){qoyHiTdTTJ = false;}
      if(gdVKahOpDd == true){gdVKahOpDd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRNVZKCGNG
{ 
  void VDFPGBkByV()
  { 
      bool iRwwImGdNz = false;
      bool sJcUsLoIdQ = false;
      bool lcjQaSMEdk = false;
      bool mrhcelPBLr = false;
      bool pstlJDBYHS = false;
      bool YioUGFgfVo = false;
      bool ZCAbMAazoH = false;
      bool wnwkarhxHW = false;
      bool RnwKLDDNWY = false;
      bool EieWSmsRZI = false;
      bool cCiAVkmEsO = false;
      bool WjYzXlGoPI = false;
      bool xNcPCMIZRn = false;
      bool yQWytPEuoa = false;
      bool QzTHCTKfyg = false;
      bool fECRLOYTxJ = false;
      bool cMlFQGMZFI = false;
      bool hKAoqxsUNh = false;
      bool CbakHtNFme = false;
      bool pjxfxEMNqu = false;
      string wSeXsxofpV;
      string DxLsSdqcVJ;
      string dUcutbTNqa;
      string shyUyNLVfM;
      string FEMrzrnRUG;
      string WTLmxbpjdR;
      string cbnObVzqtF;
      string SVxJDYHkuB;
      string mBrkEYWLWV;
      string XbrOidPxPd;
      string sxWPmBWCiX;
      string TEnbdbiDKC;
      string znTXgqciaZ;
      string JKURIpdcxC;
      string CTbzCSmQjG;
      string tMlNeFcziw;
      string XnbJNJjVTm;
      string yGFIAeLTVN;
      string DMyTfxXHlD;
      string MesBdOqSlr;
      if(wSeXsxofpV == sxWPmBWCiX){iRwwImGdNz = true;}
      else if(sxWPmBWCiX == wSeXsxofpV){cCiAVkmEsO = true;}
      if(DxLsSdqcVJ == TEnbdbiDKC){sJcUsLoIdQ = true;}
      else if(TEnbdbiDKC == DxLsSdqcVJ){WjYzXlGoPI = true;}
      if(dUcutbTNqa == znTXgqciaZ){lcjQaSMEdk = true;}
      else if(znTXgqciaZ == dUcutbTNqa){xNcPCMIZRn = true;}
      if(shyUyNLVfM == JKURIpdcxC){mrhcelPBLr = true;}
      else if(JKURIpdcxC == shyUyNLVfM){yQWytPEuoa = true;}
      if(FEMrzrnRUG == CTbzCSmQjG){pstlJDBYHS = true;}
      else if(CTbzCSmQjG == FEMrzrnRUG){QzTHCTKfyg = true;}
      if(WTLmxbpjdR == tMlNeFcziw){YioUGFgfVo = true;}
      else if(tMlNeFcziw == WTLmxbpjdR){fECRLOYTxJ = true;}
      if(cbnObVzqtF == XnbJNJjVTm){ZCAbMAazoH = true;}
      else if(XnbJNJjVTm == cbnObVzqtF){cMlFQGMZFI = true;}
      if(SVxJDYHkuB == yGFIAeLTVN){wnwkarhxHW = true;}
      if(mBrkEYWLWV == DMyTfxXHlD){RnwKLDDNWY = true;}
      if(XbrOidPxPd == MesBdOqSlr){EieWSmsRZI = true;}
      while(yGFIAeLTVN == SVxJDYHkuB){hKAoqxsUNh = true;}
      while(DMyTfxXHlD == DMyTfxXHlD){CbakHtNFme = true;}
      while(MesBdOqSlr == MesBdOqSlr){pjxfxEMNqu = true;}
      if(iRwwImGdNz == true){iRwwImGdNz = false;}
      if(sJcUsLoIdQ == true){sJcUsLoIdQ = false;}
      if(lcjQaSMEdk == true){lcjQaSMEdk = false;}
      if(mrhcelPBLr == true){mrhcelPBLr = false;}
      if(pstlJDBYHS == true){pstlJDBYHS = false;}
      if(YioUGFgfVo == true){YioUGFgfVo = false;}
      if(ZCAbMAazoH == true){ZCAbMAazoH = false;}
      if(wnwkarhxHW == true){wnwkarhxHW = false;}
      if(RnwKLDDNWY == true){RnwKLDDNWY = false;}
      if(EieWSmsRZI == true){EieWSmsRZI = false;}
      if(cCiAVkmEsO == true){cCiAVkmEsO = false;}
      if(WjYzXlGoPI == true){WjYzXlGoPI = false;}
      if(xNcPCMIZRn == true){xNcPCMIZRn = false;}
      if(yQWytPEuoa == true){yQWytPEuoa = false;}
      if(QzTHCTKfyg == true){QzTHCTKfyg = false;}
      if(fECRLOYTxJ == true){fECRLOYTxJ = false;}
      if(cMlFQGMZFI == true){cMlFQGMZFI = false;}
      if(hKAoqxsUNh == true){hKAoqxsUNh = false;}
      if(CbakHtNFme == true){CbakHtNFme = false;}
      if(pjxfxEMNqu == true){pjxfxEMNqu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXXWLMPFTA
{ 
  void xHQNnUHaUr()
  { 
      bool VXredefmmR = false;
      bool UceqheLEgC = false;
      bool sLiwqNIYVJ = false;
      bool SIzeTXeKPM = false;
      bool nRBbYARFTM = false;
      bool JwiUfKnwnP = false;
      bool WGRcyLcAWJ = false;
      bool zBoUObJHWq = false;
      bool wDFIAVZdyJ = false;
      bool jhVzogAXcM = false;
      bool WQhJMHGOFD = false;
      bool AgYxTTBIcc = false;
      bool lyBNZReoeh = false;
      bool bldJTfVuur = false;
      bool PLXtJDJXfV = false;
      bool eruAaXOUju = false;
      bool cQiXbOCOdn = false;
      bool yFMjMZaGDV = false;
      bool HHJICipdhw = false;
      bool QALAPybASu = false;
      string GFggXCMGmJ;
      string ZtDKIFFafV;
      string biSoHdQGoc;
      string qZooCRAloR;
      string ZhSnEMhVjg;
      string actysWmrZs;
      string lFRJRzEOIp;
      string FSkNwsQdju;
      string wtWIBOfque;
      string eIMwfTQJVF;
      string HTNsaHqfBA;
      string GIHdwqiIHC;
      string TNScLwGohc;
      string cGIencgdgs;
      string WzouYVAizn;
      string jIBSksAjge;
      string BByYWzAcpT;
      string KFbNeTYXEo;
      string wWpsrTFost;
      string cxwCqVBPXZ;
      if(GFggXCMGmJ == HTNsaHqfBA){VXredefmmR = true;}
      else if(HTNsaHqfBA == GFggXCMGmJ){WQhJMHGOFD = true;}
      if(ZtDKIFFafV == GIHdwqiIHC){UceqheLEgC = true;}
      else if(GIHdwqiIHC == ZtDKIFFafV){AgYxTTBIcc = true;}
      if(biSoHdQGoc == TNScLwGohc){sLiwqNIYVJ = true;}
      else if(TNScLwGohc == biSoHdQGoc){lyBNZReoeh = true;}
      if(qZooCRAloR == cGIencgdgs){SIzeTXeKPM = true;}
      else if(cGIencgdgs == qZooCRAloR){bldJTfVuur = true;}
      if(ZhSnEMhVjg == WzouYVAizn){nRBbYARFTM = true;}
      else if(WzouYVAizn == ZhSnEMhVjg){PLXtJDJXfV = true;}
      if(actysWmrZs == jIBSksAjge){JwiUfKnwnP = true;}
      else if(jIBSksAjge == actysWmrZs){eruAaXOUju = true;}
      if(lFRJRzEOIp == BByYWzAcpT){WGRcyLcAWJ = true;}
      else if(BByYWzAcpT == lFRJRzEOIp){cQiXbOCOdn = true;}
      if(FSkNwsQdju == KFbNeTYXEo){zBoUObJHWq = true;}
      if(wtWIBOfque == wWpsrTFost){wDFIAVZdyJ = true;}
      if(eIMwfTQJVF == cxwCqVBPXZ){jhVzogAXcM = true;}
      while(KFbNeTYXEo == FSkNwsQdju){yFMjMZaGDV = true;}
      while(wWpsrTFost == wWpsrTFost){HHJICipdhw = true;}
      while(cxwCqVBPXZ == cxwCqVBPXZ){QALAPybASu = true;}
      if(VXredefmmR == true){VXredefmmR = false;}
      if(UceqheLEgC == true){UceqheLEgC = false;}
      if(sLiwqNIYVJ == true){sLiwqNIYVJ = false;}
      if(SIzeTXeKPM == true){SIzeTXeKPM = false;}
      if(nRBbYARFTM == true){nRBbYARFTM = false;}
      if(JwiUfKnwnP == true){JwiUfKnwnP = false;}
      if(WGRcyLcAWJ == true){WGRcyLcAWJ = false;}
      if(zBoUObJHWq == true){zBoUObJHWq = false;}
      if(wDFIAVZdyJ == true){wDFIAVZdyJ = false;}
      if(jhVzogAXcM == true){jhVzogAXcM = false;}
      if(WQhJMHGOFD == true){WQhJMHGOFD = false;}
      if(AgYxTTBIcc == true){AgYxTTBIcc = false;}
      if(lyBNZReoeh == true){lyBNZReoeh = false;}
      if(bldJTfVuur == true){bldJTfVuur = false;}
      if(PLXtJDJXfV == true){PLXtJDJXfV = false;}
      if(eruAaXOUju == true){eruAaXOUju = false;}
      if(cQiXbOCOdn == true){cQiXbOCOdn = false;}
      if(yFMjMZaGDV == true){yFMjMZaGDV = false;}
      if(HHJICipdhw == true){HHJICipdhw = false;}
      if(QALAPybASu == true){QALAPybASu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWYAKMBEDG
{ 
  void JdtJVGqura()
  { 
      bool iVioFGBMAQ = false;
      bool qNiyMYafSu = false;
      bool rpptoPqgZO = false;
      bool WwcRXsJEQs = false;
      bool XerlTCPhCO = false;
      bool WtikMsenAo = false;
      bool OTllttkQaS = false;
      bool OWOYWNxDZl = false;
      bool AIeLqcMrEd = false;
      bool NVEbeErGrZ = false;
      bool RyGiAAeKNz = false;
      bool wbNNoFnatQ = false;
      bool gsMxFsRmsS = false;
      bool UpLAUCCwKq = false;
      bool xCdFhlHpmY = false;
      bool PRMarYkJcH = false;
      bool hrQtdFPNsl = false;
      bool DrPDTdOGPT = false;
      bool kaAUCDcjHw = false;
      bool QrSDIFliab = false;
      string lGSJTqKtyi;
      string nPpJmIigKm;
      string VYMwwEygLc;
      string VqgmEDzHCg;
      string SQOJmojYOP;
      string ZoVQuMtWMO;
      string schUNwhCEi;
      string IbddTEKDJG;
      string UYSwCfVQrr;
      string Jctnmoisup;
      string GgTeGyLrwq;
      string CpMFsTKlSh;
      string aRKMZegopd;
      string VRHSAmFmpE;
      string UcTBoSPnuT;
      string dwaNOoWGFa;
      string QVCSUjitFF;
      string OXuNNxxJXG;
      string OrtVzYqsDL;
      string QygOmyaBfF;
      if(lGSJTqKtyi == GgTeGyLrwq){iVioFGBMAQ = true;}
      else if(GgTeGyLrwq == lGSJTqKtyi){RyGiAAeKNz = true;}
      if(nPpJmIigKm == CpMFsTKlSh){qNiyMYafSu = true;}
      else if(CpMFsTKlSh == nPpJmIigKm){wbNNoFnatQ = true;}
      if(VYMwwEygLc == aRKMZegopd){rpptoPqgZO = true;}
      else if(aRKMZegopd == VYMwwEygLc){gsMxFsRmsS = true;}
      if(VqgmEDzHCg == VRHSAmFmpE){WwcRXsJEQs = true;}
      else if(VRHSAmFmpE == VqgmEDzHCg){UpLAUCCwKq = true;}
      if(SQOJmojYOP == UcTBoSPnuT){XerlTCPhCO = true;}
      else if(UcTBoSPnuT == SQOJmojYOP){xCdFhlHpmY = true;}
      if(ZoVQuMtWMO == dwaNOoWGFa){WtikMsenAo = true;}
      else if(dwaNOoWGFa == ZoVQuMtWMO){PRMarYkJcH = true;}
      if(schUNwhCEi == QVCSUjitFF){OTllttkQaS = true;}
      else if(QVCSUjitFF == schUNwhCEi){hrQtdFPNsl = true;}
      if(IbddTEKDJG == OXuNNxxJXG){OWOYWNxDZl = true;}
      if(UYSwCfVQrr == OrtVzYqsDL){AIeLqcMrEd = true;}
      if(Jctnmoisup == QygOmyaBfF){NVEbeErGrZ = true;}
      while(OXuNNxxJXG == IbddTEKDJG){DrPDTdOGPT = true;}
      while(OrtVzYqsDL == OrtVzYqsDL){kaAUCDcjHw = true;}
      while(QygOmyaBfF == QygOmyaBfF){QrSDIFliab = true;}
      if(iVioFGBMAQ == true){iVioFGBMAQ = false;}
      if(qNiyMYafSu == true){qNiyMYafSu = false;}
      if(rpptoPqgZO == true){rpptoPqgZO = false;}
      if(WwcRXsJEQs == true){WwcRXsJEQs = false;}
      if(XerlTCPhCO == true){XerlTCPhCO = false;}
      if(WtikMsenAo == true){WtikMsenAo = false;}
      if(OTllttkQaS == true){OTllttkQaS = false;}
      if(OWOYWNxDZl == true){OWOYWNxDZl = false;}
      if(AIeLqcMrEd == true){AIeLqcMrEd = false;}
      if(NVEbeErGrZ == true){NVEbeErGrZ = false;}
      if(RyGiAAeKNz == true){RyGiAAeKNz = false;}
      if(wbNNoFnatQ == true){wbNNoFnatQ = false;}
      if(gsMxFsRmsS == true){gsMxFsRmsS = false;}
      if(UpLAUCCwKq == true){UpLAUCCwKq = false;}
      if(xCdFhlHpmY == true){xCdFhlHpmY = false;}
      if(PRMarYkJcH == true){PRMarYkJcH = false;}
      if(hrQtdFPNsl == true){hrQtdFPNsl = false;}
      if(DrPDTdOGPT == true){DrPDTdOGPT = false;}
      if(kaAUCDcjHw == true){kaAUCDcjHw = false;}
      if(QrSDIFliab == true){QrSDIFliab = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJYDNJNITR
{ 
  void jxPFAskjSy()
  { 
      bool tRPDZyRDBG = false;
      bool YSxiQDoeuw = false;
      bool HeUgGdiDwX = false;
      bool IgcaIeKVQC = false;
      bool roRQIKtOHH = false;
      bool afwLUPwhww = false;
      bool OOGcyqoVZl = false;
      bool rSOsESMEYu = false;
      bool iTuoxcjRGs = false;
      bool ibYUmdhnSQ = false;
      bool UYnVOHRDHC = false;
      bool CqIBMuSQfU = false;
      bool GXPgDQstFZ = false;
      bool jXlIaKeZao = false;
      bool LgJDpqTXHr = false;
      bool KQIxJxIGRx = false;
      bool OWxgRdFAaB = false;
      bool PspqJZNLqM = false;
      bool xUlNOTPnzc = false;
      bool BXIdaniblL = false;
      string njzMZPeDoY;
      string XweIbYeZsF;
      string wbFjdUZwha;
      string ylSDseQEJy;
      string dgSkLogyea;
      string GrACbMdPhE;
      string piVOZkdbOx;
      string HZQtaPIUXo;
      string mbRGTGlPag;
      string BBWEIuKEKZ;
      string KFihTgaFbL;
      string DIqrRNQPtT;
      string zNAhuGDMke;
      string FDKydhrjlm;
      string efnOcrKdmu;
      string euKpaxEBlN;
      string cOUwGAysNi;
      string UgcGnTYlEC;
      string wZYpAKrTXg;
      string cqyYKQKrIc;
      if(njzMZPeDoY == KFihTgaFbL){tRPDZyRDBG = true;}
      else if(KFihTgaFbL == njzMZPeDoY){UYnVOHRDHC = true;}
      if(XweIbYeZsF == DIqrRNQPtT){YSxiQDoeuw = true;}
      else if(DIqrRNQPtT == XweIbYeZsF){CqIBMuSQfU = true;}
      if(wbFjdUZwha == zNAhuGDMke){HeUgGdiDwX = true;}
      else if(zNAhuGDMke == wbFjdUZwha){GXPgDQstFZ = true;}
      if(ylSDseQEJy == FDKydhrjlm){IgcaIeKVQC = true;}
      else if(FDKydhrjlm == ylSDseQEJy){jXlIaKeZao = true;}
      if(dgSkLogyea == efnOcrKdmu){roRQIKtOHH = true;}
      else if(efnOcrKdmu == dgSkLogyea){LgJDpqTXHr = true;}
      if(GrACbMdPhE == euKpaxEBlN){afwLUPwhww = true;}
      else if(euKpaxEBlN == GrACbMdPhE){KQIxJxIGRx = true;}
      if(piVOZkdbOx == cOUwGAysNi){OOGcyqoVZl = true;}
      else if(cOUwGAysNi == piVOZkdbOx){OWxgRdFAaB = true;}
      if(HZQtaPIUXo == UgcGnTYlEC){rSOsESMEYu = true;}
      if(mbRGTGlPag == wZYpAKrTXg){iTuoxcjRGs = true;}
      if(BBWEIuKEKZ == cqyYKQKrIc){ibYUmdhnSQ = true;}
      while(UgcGnTYlEC == HZQtaPIUXo){PspqJZNLqM = true;}
      while(wZYpAKrTXg == wZYpAKrTXg){xUlNOTPnzc = true;}
      while(cqyYKQKrIc == cqyYKQKrIc){BXIdaniblL = true;}
      if(tRPDZyRDBG == true){tRPDZyRDBG = false;}
      if(YSxiQDoeuw == true){YSxiQDoeuw = false;}
      if(HeUgGdiDwX == true){HeUgGdiDwX = false;}
      if(IgcaIeKVQC == true){IgcaIeKVQC = false;}
      if(roRQIKtOHH == true){roRQIKtOHH = false;}
      if(afwLUPwhww == true){afwLUPwhww = false;}
      if(OOGcyqoVZl == true){OOGcyqoVZl = false;}
      if(rSOsESMEYu == true){rSOsESMEYu = false;}
      if(iTuoxcjRGs == true){iTuoxcjRGs = false;}
      if(ibYUmdhnSQ == true){ibYUmdhnSQ = false;}
      if(UYnVOHRDHC == true){UYnVOHRDHC = false;}
      if(CqIBMuSQfU == true){CqIBMuSQfU = false;}
      if(GXPgDQstFZ == true){GXPgDQstFZ = false;}
      if(jXlIaKeZao == true){jXlIaKeZao = false;}
      if(LgJDpqTXHr == true){LgJDpqTXHr = false;}
      if(KQIxJxIGRx == true){KQIxJxIGRx = false;}
      if(OWxgRdFAaB == true){OWxgRdFAaB = false;}
      if(PspqJZNLqM == true){PspqJZNLqM = false;}
      if(xUlNOTPnzc == true){xUlNOTPnzc = false;}
      if(BXIdaniblL == true){BXIdaniblL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSMBFOEVLW
{ 
  void SgzojodUfL()
  { 
      bool SAimzyPNjc = false;
      bool uXpaYnfqms = false;
      bool WxnZUVfjXw = false;
      bool gstbIbJnmn = false;
      bool iOiSTztweU = false;
      bool CPlXCVMISc = false;
      bool RepmuCcORw = false;
      bool drEzJIOUGU = false;
      bool bjFCsRGVZm = false;
      bool OBUJVDYuWR = false;
      bool WfdhqKKmOt = false;
      bool GrCxBhYntd = false;
      bool uGoehcWtcG = false;
      bool iSxnywFXKi = false;
      bool HSHffWyXIm = false;
      bool ekBsVQpyAO = false;
      bool mQKHKntNyF = false;
      bool bBcKVbyJzK = false;
      bool dylobyQDSh = false;
      bool FHWwuqIAUq = false;
      string rtlusQKwPc;
      string pKKnxofZwE;
      string GbbfRjmwiA;
      string DIjoOBpVnQ;
      string pJiJYHYrJO;
      string JzBZoQRFcJ;
      string cNNPYgaUZu;
      string zJkeOxrSGJ;
      string KumUpEHJAy;
      string jkrdmbuTjr;
      string fESNPzNVLr;
      string YzzTyharYU;
      string ZRUaLNRGql;
      string BXhOdGbYEq;
      string pkyIZjkYeF;
      string ADuOROjqCB;
      string gHdYqAQjor;
      string GCngenSLBb;
      string csallycSwO;
      string WjWDJiGZQZ;
      if(rtlusQKwPc == fESNPzNVLr){SAimzyPNjc = true;}
      else if(fESNPzNVLr == rtlusQKwPc){WfdhqKKmOt = true;}
      if(pKKnxofZwE == YzzTyharYU){uXpaYnfqms = true;}
      else if(YzzTyharYU == pKKnxofZwE){GrCxBhYntd = true;}
      if(GbbfRjmwiA == ZRUaLNRGql){WxnZUVfjXw = true;}
      else if(ZRUaLNRGql == GbbfRjmwiA){uGoehcWtcG = true;}
      if(DIjoOBpVnQ == BXhOdGbYEq){gstbIbJnmn = true;}
      else if(BXhOdGbYEq == DIjoOBpVnQ){iSxnywFXKi = true;}
      if(pJiJYHYrJO == pkyIZjkYeF){iOiSTztweU = true;}
      else if(pkyIZjkYeF == pJiJYHYrJO){HSHffWyXIm = true;}
      if(JzBZoQRFcJ == ADuOROjqCB){CPlXCVMISc = true;}
      else if(ADuOROjqCB == JzBZoQRFcJ){ekBsVQpyAO = true;}
      if(cNNPYgaUZu == gHdYqAQjor){RepmuCcORw = true;}
      else if(gHdYqAQjor == cNNPYgaUZu){mQKHKntNyF = true;}
      if(zJkeOxrSGJ == GCngenSLBb){drEzJIOUGU = true;}
      if(KumUpEHJAy == csallycSwO){bjFCsRGVZm = true;}
      if(jkrdmbuTjr == WjWDJiGZQZ){OBUJVDYuWR = true;}
      while(GCngenSLBb == zJkeOxrSGJ){bBcKVbyJzK = true;}
      while(csallycSwO == csallycSwO){dylobyQDSh = true;}
      while(WjWDJiGZQZ == WjWDJiGZQZ){FHWwuqIAUq = true;}
      if(SAimzyPNjc == true){SAimzyPNjc = false;}
      if(uXpaYnfqms == true){uXpaYnfqms = false;}
      if(WxnZUVfjXw == true){WxnZUVfjXw = false;}
      if(gstbIbJnmn == true){gstbIbJnmn = false;}
      if(iOiSTztweU == true){iOiSTztweU = false;}
      if(CPlXCVMISc == true){CPlXCVMISc = false;}
      if(RepmuCcORw == true){RepmuCcORw = false;}
      if(drEzJIOUGU == true){drEzJIOUGU = false;}
      if(bjFCsRGVZm == true){bjFCsRGVZm = false;}
      if(OBUJVDYuWR == true){OBUJVDYuWR = false;}
      if(WfdhqKKmOt == true){WfdhqKKmOt = false;}
      if(GrCxBhYntd == true){GrCxBhYntd = false;}
      if(uGoehcWtcG == true){uGoehcWtcG = false;}
      if(iSxnywFXKi == true){iSxnywFXKi = false;}
      if(HSHffWyXIm == true){HSHffWyXIm = false;}
      if(ekBsVQpyAO == true){ekBsVQpyAO = false;}
      if(mQKHKntNyF == true){mQKHKntNyF = false;}
      if(bBcKVbyJzK == true){bBcKVbyJzK = false;}
      if(dylobyQDSh == true){dylobyQDSh = false;}
      if(FHWwuqIAUq == true){FHWwuqIAUq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWOUCRYNRS
{ 
  void fCWthTLBiA()
  { 
      bool ErpBZOccDz = false;
      bool TfWXYygDpx = false;
      bool hdiQefRyir = false;
      bool jGJmJgJNdt = false;
      bool VSIRaJuQwh = false;
      bool zrqQQZJYVt = false;
      bool xdsKONWjNr = false;
      bool oTZubPUQoV = false;
      bool jBBBsrOrVi = false;
      bool XjqjxqYxCN = false;
      bool lKCEsfRuoB = false;
      bool FrizKubrRW = false;
      bool yeOeUFbpyj = false;
      bool pWObjYyxIM = false;
      bool ZTCUdfArYB = false;
      bool OgffPHwXim = false;
      bool EbxEKhcHPk = false;
      bool wejExebsAo = false;
      bool FjQwVJqiMb = false;
      bool baNUIxVxJw = false;
      string wzLoFXwcUS;
      string fHQNzAdDFn;
      string swDDsIstEt;
      string KEZdyTuMhd;
      string FLQlqLZpZT;
      string PCNNaAuHwx;
      string dBYZIaglOf;
      string EQVbihfRMg;
      string hDUjdIpLDy;
      string XmQkzDlpcP;
      string dnasPyfler;
      string TduOOagowA;
      string kViQHQAkce;
      string wpnwDtcaUe;
      string bEgKdtrBVX;
      string VxtbeIEJly;
      string yuIzwdozLU;
      string yGUQYfnXmN;
      string YzOEJyuLQu;
      string oSnVgfwgOz;
      if(wzLoFXwcUS == dnasPyfler){ErpBZOccDz = true;}
      else if(dnasPyfler == wzLoFXwcUS){lKCEsfRuoB = true;}
      if(fHQNzAdDFn == TduOOagowA){TfWXYygDpx = true;}
      else if(TduOOagowA == fHQNzAdDFn){FrizKubrRW = true;}
      if(swDDsIstEt == kViQHQAkce){hdiQefRyir = true;}
      else if(kViQHQAkce == swDDsIstEt){yeOeUFbpyj = true;}
      if(KEZdyTuMhd == wpnwDtcaUe){jGJmJgJNdt = true;}
      else if(wpnwDtcaUe == KEZdyTuMhd){pWObjYyxIM = true;}
      if(FLQlqLZpZT == bEgKdtrBVX){VSIRaJuQwh = true;}
      else if(bEgKdtrBVX == FLQlqLZpZT){ZTCUdfArYB = true;}
      if(PCNNaAuHwx == VxtbeIEJly){zrqQQZJYVt = true;}
      else if(VxtbeIEJly == PCNNaAuHwx){OgffPHwXim = true;}
      if(dBYZIaglOf == yuIzwdozLU){xdsKONWjNr = true;}
      else if(yuIzwdozLU == dBYZIaglOf){EbxEKhcHPk = true;}
      if(EQVbihfRMg == yGUQYfnXmN){oTZubPUQoV = true;}
      if(hDUjdIpLDy == YzOEJyuLQu){jBBBsrOrVi = true;}
      if(XmQkzDlpcP == oSnVgfwgOz){XjqjxqYxCN = true;}
      while(yGUQYfnXmN == EQVbihfRMg){wejExebsAo = true;}
      while(YzOEJyuLQu == YzOEJyuLQu){FjQwVJqiMb = true;}
      while(oSnVgfwgOz == oSnVgfwgOz){baNUIxVxJw = true;}
      if(ErpBZOccDz == true){ErpBZOccDz = false;}
      if(TfWXYygDpx == true){TfWXYygDpx = false;}
      if(hdiQefRyir == true){hdiQefRyir = false;}
      if(jGJmJgJNdt == true){jGJmJgJNdt = false;}
      if(VSIRaJuQwh == true){VSIRaJuQwh = false;}
      if(zrqQQZJYVt == true){zrqQQZJYVt = false;}
      if(xdsKONWjNr == true){xdsKONWjNr = false;}
      if(oTZubPUQoV == true){oTZubPUQoV = false;}
      if(jBBBsrOrVi == true){jBBBsrOrVi = false;}
      if(XjqjxqYxCN == true){XjqjxqYxCN = false;}
      if(lKCEsfRuoB == true){lKCEsfRuoB = false;}
      if(FrizKubrRW == true){FrizKubrRW = false;}
      if(yeOeUFbpyj == true){yeOeUFbpyj = false;}
      if(pWObjYyxIM == true){pWObjYyxIM = false;}
      if(ZTCUdfArYB == true){ZTCUdfArYB = false;}
      if(OgffPHwXim == true){OgffPHwXim = false;}
      if(EbxEKhcHPk == true){EbxEKhcHPk = false;}
      if(wejExebsAo == true){wejExebsAo = false;}
      if(FjQwVJqiMb == true){FjQwVJqiMb = false;}
      if(baNUIxVxJw == true){baNUIxVxJw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENRYOVHEPC
{ 
  void NGLIGfbgNw()
  { 
      bool BGNyumLSbs = false;
      bool FGigudolTc = false;
      bool eSpIUXhkAk = false;
      bool dlAutxyBEB = false;
      bool TiWHNlmXna = false;
      bool VNtqYhQEdW = false;
      bool FaRqOTGnly = false;
      bool fmhSJuuiuh = false;
      bool kJwZOQqJVM = false;
      bool gsXhurRfrs = false;
      bool fzkpuifagd = false;
      bool mgJukudqby = false;
      bool bxRZQlPAWQ = false;
      bool dOqBClYGef = false;
      bool jQbrYzjbwA = false;
      bool OZEsRigLZI = false;
      bool TfEPzXpHry = false;
      bool WXLwOLUZAQ = false;
      bool CmDWCDKxjT = false;
      bool FMgVMEMLrB = false;
      string JpMpqinFDL;
      string urPTKJicnF;
      string jFKhoPNqJS;
      string LQcTtmsqVK;
      string siITSpVqPU;
      string hIEiVDeeAb;
      string VxujzdOwZW;
      string QqGdLAxpOz;
      string tVaokDMsyp;
      string HNptownXTo;
      string aYRsDpCaXU;
      string GnPAhzVGzw;
      string QVxiPCBMoP;
      string MZWYYUEhkt;
      string AlVcjSyoLo;
      string agXXXFbhcA;
      string ookIIfRqbN;
      string tmUFuezUzw;
      string ELAzneBzAT;
      string sVEjEKANTD;
      if(JpMpqinFDL == aYRsDpCaXU){BGNyumLSbs = true;}
      else if(aYRsDpCaXU == JpMpqinFDL){fzkpuifagd = true;}
      if(urPTKJicnF == GnPAhzVGzw){FGigudolTc = true;}
      else if(GnPAhzVGzw == urPTKJicnF){mgJukudqby = true;}
      if(jFKhoPNqJS == QVxiPCBMoP){eSpIUXhkAk = true;}
      else if(QVxiPCBMoP == jFKhoPNqJS){bxRZQlPAWQ = true;}
      if(LQcTtmsqVK == MZWYYUEhkt){dlAutxyBEB = true;}
      else if(MZWYYUEhkt == LQcTtmsqVK){dOqBClYGef = true;}
      if(siITSpVqPU == AlVcjSyoLo){TiWHNlmXna = true;}
      else if(AlVcjSyoLo == siITSpVqPU){jQbrYzjbwA = true;}
      if(hIEiVDeeAb == agXXXFbhcA){VNtqYhQEdW = true;}
      else if(agXXXFbhcA == hIEiVDeeAb){OZEsRigLZI = true;}
      if(VxujzdOwZW == ookIIfRqbN){FaRqOTGnly = true;}
      else if(ookIIfRqbN == VxujzdOwZW){TfEPzXpHry = true;}
      if(QqGdLAxpOz == tmUFuezUzw){fmhSJuuiuh = true;}
      if(tVaokDMsyp == ELAzneBzAT){kJwZOQqJVM = true;}
      if(HNptownXTo == sVEjEKANTD){gsXhurRfrs = true;}
      while(tmUFuezUzw == QqGdLAxpOz){WXLwOLUZAQ = true;}
      while(ELAzneBzAT == ELAzneBzAT){CmDWCDKxjT = true;}
      while(sVEjEKANTD == sVEjEKANTD){FMgVMEMLrB = true;}
      if(BGNyumLSbs == true){BGNyumLSbs = false;}
      if(FGigudolTc == true){FGigudolTc = false;}
      if(eSpIUXhkAk == true){eSpIUXhkAk = false;}
      if(dlAutxyBEB == true){dlAutxyBEB = false;}
      if(TiWHNlmXna == true){TiWHNlmXna = false;}
      if(VNtqYhQEdW == true){VNtqYhQEdW = false;}
      if(FaRqOTGnly == true){FaRqOTGnly = false;}
      if(fmhSJuuiuh == true){fmhSJuuiuh = false;}
      if(kJwZOQqJVM == true){kJwZOQqJVM = false;}
      if(gsXhurRfrs == true){gsXhurRfrs = false;}
      if(fzkpuifagd == true){fzkpuifagd = false;}
      if(mgJukudqby == true){mgJukudqby = false;}
      if(bxRZQlPAWQ == true){bxRZQlPAWQ = false;}
      if(dOqBClYGef == true){dOqBClYGef = false;}
      if(jQbrYzjbwA == true){jQbrYzjbwA = false;}
      if(OZEsRigLZI == true){OZEsRigLZI = false;}
      if(TfEPzXpHry == true){TfEPzXpHry = false;}
      if(WXLwOLUZAQ == true){WXLwOLUZAQ = false;}
      if(CmDWCDKxjT == true){CmDWCDKxjT = false;}
      if(FMgVMEMLrB == true){FMgVMEMLrB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WBHPAMJOUO
{ 
  void VHAQPaYMrM()
  { 
      bool CqWrCaobhi = false;
      bool OVihtVGmWg = false;
      bool nUwunUVAZN = false;
      bool mEgnguaIZK = false;
      bool XjZaKiOoiu = false;
      bool GGGlygtaEg = false;
      bool EnBTuKotBy = false;
      bool uxMMIEuVkE = false;
      bool GfReGgxtpA = false;
      bool BzEsFjhFeA = false;
      bool tTnjzIstdt = false;
      bool kYpzZYVWNO = false;
      bool MtEBxwsTHY = false;
      bool VoqkKlrhex = false;
      bool mDQwObIESf = false;
      bool NKrPmzPmlD = false;
      bool PZmEXwhFon = false;
      bool fnrPbJdHmV = false;
      bool mnAaLKxaxK = false;
      bool VFuahNPMYS = false;
      string qETHnozaES;
      string ruPwaJufBZ;
      string QooEZGgqJg;
      string EebISntTnF;
      string NaQTUkrBTf;
      string lnIaRCPPhh;
      string HHRWNNTGdm;
      string ObruMpXVin;
      string NfWcuQWAqQ;
      string YdlFxFItFH;
      string QlXgRJuMOb;
      string dsgsUbjobw;
      string qTPNOjpmxG;
      string gdQaWbIpKk;
      string VJkOlexrkV;
      string UTSIQxWJRg;
      string TIOHuzcGVr;
      string TtdqaghAai;
      string mxBbkNLHJZ;
      string EyXcQNtdTl;
      if(qETHnozaES == QlXgRJuMOb){CqWrCaobhi = true;}
      else if(QlXgRJuMOb == qETHnozaES){tTnjzIstdt = true;}
      if(ruPwaJufBZ == dsgsUbjobw){OVihtVGmWg = true;}
      else if(dsgsUbjobw == ruPwaJufBZ){kYpzZYVWNO = true;}
      if(QooEZGgqJg == qTPNOjpmxG){nUwunUVAZN = true;}
      else if(qTPNOjpmxG == QooEZGgqJg){MtEBxwsTHY = true;}
      if(EebISntTnF == gdQaWbIpKk){mEgnguaIZK = true;}
      else if(gdQaWbIpKk == EebISntTnF){VoqkKlrhex = true;}
      if(NaQTUkrBTf == VJkOlexrkV){XjZaKiOoiu = true;}
      else if(VJkOlexrkV == NaQTUkrBTf){mDQwObIESf = true;}
      if(lnIaRCPPhh == UTSIQxWJRg){GGGlygtaEg = true;}
      else if(UTSIQxWJRg == lnIaRCPPhh){NKrPmzPmlD = true;}
      if(HHRWNNTGdm == TIOHuzcGVr){EnBTuKotBy = true;}
      else if(TIOHuzcGVr == HHRWNNTGdm){PZmEXwhFon = true;}
      if(ObruMpXVin == TtdqaghAai){uxMMIEuVkE = true;}
      if(NfWcuQWAqQ == mxBbkNLHJZ){GfReGgxtpA = true;}
      if(YdlFxFItFH == EyXcQNtdTl){BzEsFjhFeA = true;}
      while(TtdqaghAai == ObruMpXVin){fnrPbJdHmV = true;}
      while(mxBbkNLHJZ == mxBbkNLHJZ){mnAaLKxaxK = true;}
      while(EyXcQNtdTl == EyXcQNtdTl){VFuahNPMYS = true;}
      if(CqWrCaobhi == true){CqWrCaobhi = false;}
      if(OVihtVGmWg == true){OVihtVGmWg = false;}
      if(nUwunUVAZN == true){nUwunUVAZN = false;}
      if(mEgnguaIZK == true){mEgnguaIZK = false;}
      if(XjZaKiOoiu == true){XjZaKiOoiu = false;}
      if(GGGlygtaEg == true){GGGlygtaEg = false;}
      if(EnBTuKotBy == true){EnBTuKotBy = false;}
      if(uxMMIEuVkE == true){uxMMIEuVkE = false;}
      if(GfReGgxtpA == true){GfReGgxtpA = false;}
      if(BzEsFjhFeA == true){BzEsFjhFeA = false;}
      if(tTnjzIstdt == true){tTnjzIstdt = false;}
      if(kYpzZYVWNO == true){kYpzZYVWNO = false;}
      if(MtEBxwsTHY == true){MtEBxwsTHY = false;}
      if(VoqkKlrhex == true){VoqkKlrhex = false;}
      if(mDQwObIESf == true){mDQwObIESf = false;}
      if(NKrPmzPmlD == true){NKrPmzPmlD = false;}
      if(PZmEXwhFon == true){PZmEXwhFon = false;}
      if(fnrPbJdHmV == true){fnrPbJdHmV = false;}
      if(mnAaLKxaxK == true){mnAaLKxaxK = false;}
      if(VFuahNPMYS == true){VFuahNPMYS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFVVUMZMPH
{ 
  void dPBGRmEwdj()
  { 
      bool qVXwnRoBuJ = false;
      bool djYGakRiDO = false;
      bool gKtWMVXGAW = false;
      bool TGJUJjomsG = false;
      bool KEGBQOQmlm = false;
      bool ALNXsgaBiR = false;
      bool thAYpWZExp = false;
      bool wepxDbErGy = false;
      bool EkUMVHslab = false;
      bool ImDaLbDgLs = false;
      bool oMpuqVVPTQ = false;
      bool bhukNJNnDi = false;
      bool dncUhIaOkb = false;
      bool YXgMIqtYVz = false;
      bool ldRJAZrSMC = false;
      bool NPcbPAiUNh = false;
      bool uGerrEBhbW = false;
      bool OoRDwzWTTH = false;
      bool PHChNItExI = false;
      bool HYKnEeyYQw = false;
      string mZuFQQVqMQ;
      string wPzEuuuykw;
      string XIsTZMGmWm;
      string xLXcNjtkFg;
      string kqzNjKBTXO;
      string MkBuDdfaeD;
      string JhUYTjrWqK;
      string AJsDLfIfjP;
      string KmOHaLJbYi;
      string ESFBWDWZsz;
      string RebNNCrxjX;
      string VzqPrWSNyI;
      string aPxIFhDqgI;
      string JhmkxfKBsX;
      string SLrBNEbpIz;
      string jJbkYCgTHf;
      string yAQbOmMGRM;
      string LRTZoOXwtB;
      string FNigXzGBLu;
      string zpsMYSuQlZ;
      if(mZuFQQVqMQ == RebNNCrxjX){qVXwnRoBuJ = true;}
      else if(RebNNCrxjX == mZuFQQVqMQ){oMpuqVVPTQ = true;}
      if(wPzEuuuykw == VzqPrWSNyI){djYGakRiDO = true;}
      else if(VzqPrWSNyI == wPzEuuuykw){bhukNJNnDi = true;}
      if(XIsTZMGmWm == aPxIFhDqgI){gKtWMVXGAW = true;}
      else if(aPxIFhDqgI == XIsTZMGmWm){dncUhIaOkb = true;}
      if(xLXcNjtkFg == JhmkxfKBsX){TGJUJjomsG = true;}
      else if(JhmkxfKBsX == xLXcNjtkFg){YXgMIqtYVz = true;}
      if(kqzNjKBTXO == SLrBNEbpIz){KEGBQOQmlm = true;}
      else if(SLrBNEbpIz == kqzNjKBTXO){ldRJAZrSMC = true;}
      if(MkBuDdfaeD == jJbkYCgTHf){ALNXsgaBiR = true;}
      else if(jJbkYCgTHf == MkBuDdfaeD){NPcbPAiUNh = true;}
      if(JhUYTjrWqK == yAQbOmMGRM){thAYpWZExp = true;}
      else if(yAQbOmMGRM == JhUYTjrWqK){uGerrEBhbW = true;}
      if(AJsDLfIfjP == LRTZoOXwtB){wepxDbErGy = true;}
      if(KmOHaLJbYi == FNigXzGBLu){EkUMVHslab = true;}
      if(ESFBWDWZsz == zpsMYSuQlZ){ImDaLbDgLs = true;}
      while(LRTZoOXwtB == AJsDLfIfjP){OoRDwzWTTH = true;}
      while(FNigXzGBLu == FNigXzGBLu){PHChNItExI = true;}
      while(zpsMYSuQlZ == zpsMYSuQlZ){HYKnEeyYQw = true;}
      if(qVXwnRoBuJ == true){qVXwnRoBuJ = false;}
      if(djYGakRiDO == true){djYGakRiDO = false;}
      if(gKtWMVXGAW == true){gKtWMVXGAW = false;}
      if(TGJUJjomsG == true){TGJUJjomsG = false;}
      if(KEGBQOQmlm == true){KEGBQOQmlm = false;}
      if(ALNXsgaBiR == true){ALNXsgaBiR = false;}
      if(thAYpWZExp == true){thAYpWZExp = false;}
      if(wepxDbErGy == true){wepxDbErGy = false;}
      if(EkUMVHslab == true){EkUMVHslab = false;}
      if(ImDaLbDgLs == true){ImDaLbDgLs = false;}
      if(oMpuqVVPTQ == true){oMpuqVVPTQ = false;}
      if(bhukNJNnDi == true){bhukNJNnDi = false;}
      if(dncUhIaOkb == true){dncUhIaOkb = false;}
      if(YXgMIqtYVz == true){YXgMIqtYVz = false;}
      if(ldRJAZrSMC == true){ldRJAZrSMC = false;}
      if(NPcbPAiUNh == true){NPcbPAiUNh = false;}
      if(uGerrEBhbW == true){uGerrEBhbW = false;}
      if(OoRDwzWTTH == true){OoRDwzWTTH = false;}
      if(PHChNItExI == true){PHChNItExI = false;}
      if(HYKnEeyYQw == true){HYKnEeyYQw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFJHWUVMRB
{ 
  void sReVhKuodB()
  { 
      bool XJPaRzdiAx = false;
      bool VYFDoJkHwQ = false;
      bool ObHgqOAcns = false;
      bool RqGfmwaugc = false;
      bool MrRYXpTnld = false;
      bool kssSKwChjC = false;
      bool zAuGfdRZPr = false;
      bool ipaSEWKhJA = false;
      bool uLqJHXynUq = false;
      bool trKddLxKss = false;
      bool YtXstuSaOn = false;
      bool lUYiHmJkyH = false;
      bool fcEYypewnr = false;
      bool ZznQaBmxPM = false;
      bool FWZgFYTaVq = false;
      bool BLLlMwozuE = false;
      bool PVlVOlgIIG = false;
      bool zLVlCICWTY = false;
      bool VEawqNnCDe = false;
      bool LnCKxikESS = false;
      string QDLZfCHxtK;
      string QZkmfDfzQB;
      string fdkPEVJKHF;
      string ZVRhcKCibb;
      string nyQtkHxqMs;
      string fiBHMmRuUJ;
      string swoojtHCKU;
      string BwWnMgMqdx;
      string YSxOYpUKVo;
      string rGOShqIaJp;
      string AufqqiMMue;
      string aaRXjazaQt;
      string ZwfUcuhEGV;
      string XkgmwdlGWo;
      string dHPpORnqhH;
      string rhKPQDOLOw;
      string BHGZGosdaG;
      string orDbPSgpFK;
      string GqWzcpaRWs;
      string OZranWBpiZ;
      if(QDLZfCHxtK == AufqqiMMue){XJPaRzdiAx = true;}
      else if(AufqqiMMue == QDLZfCHxtK){YtXstuSaOn = true;}
      if(QZkmfDfzQB == aaRXjazaQt){VYFDoJkHwQ = true;}
      else if(aaRXjazaQt == QZkmfDfzQB){lUYiHmJkyH = true;}
      if(fdkPEVJKHF == ZwfUcuhEGV){ObHgqOAcns = true;}
      else if(ZwfUcuhEGV == fdkPEVJKHF){fcEYypewnr = true;}
      if(ZVRhcKCibb == XkgmwdlGWo){RqGfmwaugc = true;}
      else if(XkgmwdlGWo == ZVRhcKCibb){ZznQaBmxPM = true;}
      if(nyQtkHxqMs == dHPpORnqhH){MrRYXpTnld = true;}
      else if(dHPpORnqhH == nyQtkHxqMs){FWZgFYTaVq = true;}
      if(fiBHMmRuUJ == rhKPQDOLOw){kssSKwChjC = true;}
      else if(rhKPQDOLOw == fiBHMmRuUJ){BLLlMwozuE = true;}
      if(swoojtHCKU == BHGZGosdaG){zAuGfdRZPr = true;}
      else if(BHGZGosdaG == swoojtHCKU){PVlVOlgIIG = true;}
      if(BwWnMgMqdx == orDbPSgpFK){ipaSEWKhJA = true;}
      if(YSxOYpUKVo == GqWzcpaRWs){uLqJHXynUq = true;}
      if(rGOShqIaJp == OZranWBpiZ){trKddLxKss = true;}
      while(orDbPSgpFK == BwWnMgMqdx){zLVlCICWTY = true;}
      while(GqWzcpaRWs == GqWzcpaRWs){VEawqNnCDe = true;}
      while(OZranWBpiZ == OZranWBpiZ){LnCKxikESS = true;}
      if(XJPaRzdiAx == true){XJPaRzdiAx = false;}
      if(VYFDoJkHwQ == true){VYFDoJkHwQ = false;}
      if(ObHgqOAcns == true){ObHgqOAcns = false;}
      if(RqGfmwaugc == true){RqGfmwaugc = false;}
      if(MrRYXpTnld == true){MrRYXpTnld = false;}
      if(kssSKwChjC == true){kssSKwChjC = false;}
      if(zAuGfdRZPr == true){zAuGfdRZPr = false;}
      if(ipaSEWKhJA == true){ipaSEWKhJA = false;}
      if(uLqJHXynUq == true){uLqJHXynUq = false;}
      if(trKddLxKss == true){trKddLxKss = false;}
      if(YtXstuSaOn == true){YtXstuSaOn = false;}
      if(lUYiHmJkyH == true){lUYiHmJkyH = false;}
      if(fcEYypewnr == true){fcEYypewnr = false;}
      if(ZznQaBmxPM == true){ZznQaBmxPM = false;}
      if(FWZgFYTaVq == true){FWZgFYTaVq = false;}
      if(BLLlMwozuE == true){BLLlMwozuE = false;}
      if(PVlVOlgIIG == true){PVlVOlgIIG = false;}
      if(zLVlCICWTY == true){zLVlCICWTY = false;}
      if(VEawqNnCDe == true){VEawqNnCDe = false;}
      if(LnCKxikESS == true){LnCKxikESS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KITXFXCODK
{ 
  void VDzCoEXzNz()
  { 
      bool ufXtGHGLwl = false;
      bool gsVfXFPIeQ = false;
      bool rNkziuUDAY = false;
      bool sNWXwrZOFs = false;
      bool uNkVnRQQho = false;
      bool qeWedhuXKK = false;
      bool lCKWsSWyje = false;
      bool fBDkVebOKR = false;
      bool eDUKhOprsO = false;
      bool xBDtGrCOcU = false;
      bool uSgDJoalJz = false;
      bool GfMsfihzne = false;
      bool cdEUhdxIec = false;
      bool bNkoVLWRBr = false;
      bool mEhtIQnKOX = false;
      bool KDZyrROLUe = false;
      bool rRGfXruXXT = false;
      bool LPywqXwKMR = false;
      bool pmtHSXnmwE = false;
      bool xKxVAUyBWP = false;
      string tuZDqTkzop;
      string FaWqbyKHzZ;
      string mOtSzBcRnG;
      string eimlTwDlzT;
      string iphxgigXmp;
      string QdCxjeBHEo;
      string qTLhLWmkXe;
      string tXHepxfwlP;
      string UEeypAgoBn;
      string uuhJcPdzlJ;
      string wwAIurVXGl;
      string zEVoTmoNrK;
      string pyijiypyCa;
      string SgJbTYDVDx;
      string eJhPoqZsop;
      string ZQGbTxMQYw;
      string CXUfSRusVu;
      string iSKufgPTtr;
      string YxIMACZgIV;
      string LmxGtGnCwW;
      if(tuZDqTkzop == wwAIurVXGl){ufXtGHGLwl = true;}
      else if(wwAIurVXGl == tuZDqTkzop){uSgDJoalJz = true;}
      if(FaWqbyKHzZ == zEVoTmoNrK){gsVfXFPIeQ = true;}
      else if(zEVoTmoNrK == FaWqbyKHzZ){GfMsfihzne = true;}
      if(mOtSzBcRnG == pyijiypyCa){rNkziuUDAY = true;}
      else if(pyijiypyCa == mOtSzBcRnG){cdEUhdxIec = true;}
      if(eimlTwDlzT == SgJbTYDVDx){sNWXwrZOFs = true;}
      else if(SgJbTYDVDx == eimlTwDlzT){bNkoVLWRBr = true;}
      if(iphxgigXmp == eJhPoqZsop){uNkVnRQQho = true;}
      else if(eJhPoqZsop == iphxgigXmp){mEhtIQnKOX = true;}
      if(QdCxjeBHEo == ZQGbTxMQYw){qeWedhuXKK = true;}
      else if(ZQGbTxMQYw == QdCxjeBHEo){KDZyrROLUe = true;}
      if(qTLhLWmkXe == CXUfSRusVu){lCKWsSWyje = true;}
      else if(CXUfSRusVu == qTLhLWmkXe){rRGfXruXXT = true;}
      if(tXHepxfwlP == iSKufgPTtr){fBDkVebOKR = true;}
      if(UEeypAgoBn == YxIMACZgIV){eDUKhOprsO = true;}
      if(uuhJcPdzlJ == LmxGtGnCwW){xBDtGrCOcU = true;}
      while(iSKufgPTtr == tXHepxfwlP){LPywqXwKMR = true;}
      while(YxIMACZgIV == YxIMACZgIV){pmtHSXnmwE = true;}
      while(LmxGtGnCwW == LmxGtGnCwW){xKxVAUyBWP = true;}
      if(ufXtGHGLwl == true){ufXtGHGLwl = false;}
      if(gsVfXFPIeQ == true){gsVfXFPIeQ = false;}
      if(rNkziuUDAY == true){rNkziuUDAY = false;}
      if(sNWXwrZOFs == true){sNWXwrZOFs = false;}
      if(uNkVnRQQho == true){uNkVnRQQho = false;}
      if(qeWedhuXKK == true){qeWedhuXKK = false;}
      if(lCKWsSWyje == true){lCKWsSWyje = false;}
      if(fBDkVebOKR == true){fBDkVebOKR = false;}
      if(eDUKhOprsO == true){eDUKhOprsO = false;}
      if(xBDtGrCOcU == true){xBDtGrCOcU = false;}
      if(uSgDJoalJz == true){uSgDJoalJz = false;}
      if(GfMsfihzne == true){GfMsfihzne = false;}
      if(cdEUhdxIec == true){cdEUhdxIec = false;}
      if(bNkoVLWRBr == true){bNkoVLWRBr = false;}
      if(mEhtIQnKOX == true){mEhtIQnKOX = false;}
      if(KDZyrROLUe == true){KDZyrROLUe = false;}
      if(rRGfXruXXT == true){rRGfXruXXT = false;}
      if(LPywqXwKMR == true){LPywqXwKMR = false;}
      if(pmtHSXnmwE == true){pmtHSXnmwE = false;}
      if(xKxVAUyBWP == true){xKxVAUyBWP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JJJHBOBTPE
{ 
  void fDiFrjHmZQ()
  { 
      bool OEuPOqlofX = false;
      bool fQFgnOWhrY = false;
      bool geIqbBOcCK = false;
      bool mEoIBtzaSW = false;
      bool ztDLSMebsa = false;
      bool haDzLiwDnM = false;
      bool bIlUkaawet = false;
      bool OuPUZlbwXO = false;
      bool WlibcMBpwS = false;
      bool xwmFtqIhar = false;
      bool lhxzMlLhYZ = false;
      bool HzeYppYKrY = false;
      bool ZkAMwSHJZi = false;
      bool dsVfcoojPp = false;
      bool ASQVKyQOPE = false;
      bool RyoCRAhkDs = false;
      bool dBIpwOdywA = false;
      bool BnuCXHUdBx = false;
      bool BstVQeDTOb = false;
      bool HDfVLzJZZw = false;
      string fGSOYOpPJg;
      string hbBUpWgTdt;
      string aFHdfecLdY;
      string ImpeSXhqaQ;
      string XPMAjSxULY;
      string gRNFDazoit;
      string lelkYulWCS;
      string oprNWLsGsM;
      string gIzFqqYjaq;
      string XrIgdsdabo;
      string gZRsjqYzir;
      string hsuVMcegsg;
      string VBwKuwgLic;
      string hRdDeHqGVA;
      string RZBhJdxlUB;
      string OxhtTfdGxm;
      string JNQFKQOrqE;
      string lXKsOwANBQ;
      string zuqhNkiijz;
      string cjIhpEIuXs;
      if(fGSOYOpPJg == gZRsjqYzir){OEuPOqlofX = true;}
      else if(gZRsjqYzir == fGSOYOpPJg){lhxzMlLhYZ = true;}
      if(hbBUpWgTdt == hsuVMcegsg){fQFgnOWhrY = true;}
      else if(hsuVMcegsg == hbBUpWgTdt){HzeYppYKrY = true;}
      if(aFHdfecLdY == VBwKuwgLic){geIqbBOcCK = true;}
      else if(VBwKuwgLic == aFHdfecLdY){ZkAMwSHJZi = true;}
      if(ImpeSXhqaQ == hRdDeHqGVA){mEoIBtzaSW = true;}
      else if(hRdDeHqGVA == ImpeSXhqaQ){dsVfcoojPp = true;}
      if(XPMAjSxULY == RZBhJdxlUB){ztDLSMebsa = true;}
      else if(RZBhJdxlUB == XPMAjSxULY){ASQVKyQOPE = true;}
      if(gRNFDazoit == OxhtTfdGxm){haDzLiwDnM = true;}
      else if(OxhtTfdGxm == gRNFDazoit){RyoCRAhkDs = true;}
      if(lelkYulWCS == JNQFKQOrqE){bIlUkaawet = true;}
      else if(JNQFKQOrqE == lelkYulWCS){dBIpwOdywA = true;}
      if(oprNWLsGsM == lXKsOwANBQ){OuPUZlbwXO = true;}
      if(gIzFqqYjaq == zuqhNkiijz){WlibcMBpwS = true;}
      if(XrIgdsdabo == cjIhpEIuXs){xwmFtqIhar = true;}
      while(lXKsOwANBQ == oprNWLsGsM){BnuCXHUdBx = true;}
      while(zuqhNkiijz == zuqhNkiijz){BstVQeDTOb = true;}
      while(cjIhpEIuXs == cjIhpEIuXs){HDfVLzJZZw = true;}
      if(OEuPOqlofX == true){OEuPOqlofX = false;}
      if(fQFgnOWhrY == true){fQFgnOWhrY = false;}
      if(geIqbBOcCK == true){geIqbBOcCK = false;}
      if(mEoIBtzaSW == true){mEoIBtzaSW = false;}
      if(ztDLSMebsa == true){ztDLSMebsa = false;}
      if(haDzLiwDnM == true){haDzLiwDnM = false;}
      if(bIlUkaawet == true){bIlUkaawet = false;}
      if(OuPUZlbwXO == true){OuPUZlbwXO = false;}
      if(WlibcMBpwS == true){WlibcMBpwS = false;}
      if(xwmFtqIhar == true){xwmFtqIhar = false;}
      if(lhxzMlLhYZ == true){lhxzMlLhYZ = false;}
      if(HzeYppYKrY == true){HzeYppYKrY = false;}
      if(ZkAMwSHJZi == true){ZkAMwSHJZi = false;}
      if(dsVfcoojPp == true){dsVfcoojPp = false;}
      if(ASQVKyQOPE == true){ASQVKyQOPE = false;}
      if(RyoCRAhkDs == true){RyoCRAhkDs = false;}
      if(dBIpwOdywA == true){dBIpwOdywA = false;}
      if(BnuCXHUdBx == true){BnuCXHUdBx = false;}
      if(BstVQeDTOb == true){BstVQeDTOb = false;}
      if(HDfVLzJZZw == true){HDfVLzJZZw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZAWOUHJYZ
{ 
  void XZANjcEDUN()
  { 
      bool mdRUiKkGeI = false;
      bool WWHzXBWlmP = false;
      bool yLgLqCexXH = false;
      bool NPPbqoOlkZ = false;
      bool kmjKkuJaPu = false;
      bool ndfUjaxFcf = false;
      bool emhXuHGeHi = false;
      bool ljAMeKbWau = false;
      bool rDhcSijurP = false;
      bool qJJFtxFMOc = false;
      bool oeTfJDcToY = false;
      bool zZdgmbFEEL = false;
      bool XLlqqbauRg = false;
      bool FOHxGNjCSO = false;
      bool GQFTQQebRS = false;
      bool rAICFdrbng = false;
      bool chBISjSgaY = false;
      bool qCloFGFSaZ = false;
      bool wzcynFGEqc = false;
      bool VINllXOwAf = false;
      string MslmqEnXwz;
      string JJmTHTffZu;
      string BDlkMGNznQ;
      string lHTMwKltOx;
      string QVGTpTVaVV;
      string lfGDKJHBak;
      string poieNBoZXx;
      string hlQcdewStr;
      string kmdSeFAQCm;
      string DkTdGbmbFn;
      string euDYnAPdZe;
      string MnGhzDLQAI;
      string BYXktwRlWB;
      string rUMGNpjFee;
      string oWpWZOdkeC;
      string QWaxmFWSdq;
      string hdGXlraATJ;
      string TFkUSdhAKe;
      string SgHTkVsOSI;
      string SRanwLQSkh;
      if(MslmqEnXwz == euDYnAPdZe){mdRUiKkGeI = true;}
      else if(euDYnAPdZe == MslmqEnXwz){oeTfJDcToY = true;}
      if(JJmTHTffZu == MnGhzDLQAI){WWHzXBWlmP = true;}
      else if(MnGhzDLQAI == JJmTHTffZu){zZdgmbFEEL = true;}
      if(BDlkMGNznQ == BYXktwRlWB){yLgLqCexXH = true;}
      else if(BYXktwRlWB == BDlkMGNznQ){XLlqqbauRg = true;}
      if(lHTMwKltOx == rUMGNpjFee){NPPbqoOlkZ = true;}
      else if(rUMGNpjFee == lHTMwKltOx){FOHxGNjCSO = true;}
      if(QVGTpTVaVV == oWpWZOdkeC){kmjKkuJaPu = true;}
      else if(oWpWZOdkeC == QVGTpTVaVV){GQFTQQebRS = true;}
      if(lfGDKJHBak == QWaxmFWSdq){ndfUjaxFcf = true;}
      else if(QWaxmFWSdq == lfGDKJHBak){rAICFdrbng = true;}
      if(poieNBoZXx == hdGXlraATJ){emhXuHGeHi = true;}
      else if(hdGXlraATJ == poieNBoZXx){chBISjSgaY = true;}
      if(hlQcdewStr == TFkUSdhAKe){ljAMeKbWau = true;}
      if(kmdSeFAQCm == SgHTkVsOSI){rDhcSijurP = true;}
      if(DkTdGbmbFn == SRanwLQSkh){qJJFtxFMOc = true;}
      while(TFkUSdhAKe == hlQcdewStr){qCloFGFSaZ = true;}
      while(SgHTkVsOSI == SgHTkVsOSI){wzcynFGEqc = true;}
      while(SRanwLQSkh == SRanwLQSkh){VINllXOwAf = true;}
      if(mdRUiKkGeI == true){mdRUiKkGeI = false;}
      if(WWHzXBWlmP == true){WWHzXBWlmP = false;}
      if(yLgLqCexXH == true){yLgLqCexXH = false;}
      if(NPPbqoOlkZ == true){NPPbqoOlkZ = false;}
      if(kmjKkuJaPu == true){kmjKkuJaPu = false;}
      if(ndfUjaxFcf == true){ndfUjaxFcf = false;}
      if(emhXuHGeHi == true){emhXuHGeHi = false;}
      if(ljAMeKbWau == true){ljAMeKbWau = false;}
      if(rDhcSijurP == true){rDhcSijurP = false;}
      if(qJJFtxFMOc == true){qJJFtxFMOc = false;}
      if(oeTfJDcToY == true){oeTfJDcToY = false;}
      if(zZdgmbFEEL == true){zZdgmbFEEL = false;}
      if(XLlqqbauRg == true){XLlqqbauRg = false;}
      if(FOHxGNjCSO == true){FOHxGNjCSO = false;}
      if(GQFTQQebRS == true){GQFTQQebRS = false;}
      if(rAICFdrbng == true){rAICFdrbng = false;}
      if(chBISjSgaY == true){chBISjSgaY = false;}
      if(qCloFGFSaZ == true){qCloFGFSaZ = false;}
      if(wzcynFGEqc == true){wzcynFGEqc = false;}
      if(VINllXOwAf == true){VINllXOwAf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQYNKHKXLJ
{ 
  void yHaodzpNTC()
  { 
      bool meCpaLMNFE = false;
      bool GwrMQUciCl = false;
      bool GLIochYTif = false;
      bool XmEddNSTCt = false;
      bool OphxxCbQhi = false;
      bool qtybtaWMNs = false;
      bool mreYgSrOhC = false;
      bool BIgIWPcLrZ = false;
      bool FHkAocnbiC = false;
      bool qGGJGVLJQd = false;
      bool JNhfgiNoFd = false;
      bool yLUmmeGejE = false;
      bool eQefLtBWBA = false;
      bool ETtOPqYFSG = false;
      bool OyVEEflTVa = false;
      bool PgZMzshCUl = false;
      bool hpnEZdQFXw = false;
      bool GALdoftaae = false;
      bool IhAZkXthOW = false;
      bool JVkfYXKQdZ = false;
      string GytCrnGeuH;
      string LpcBOoaPyQ;
      string JCyOTanGxN;
      string bGGkgeqVaV;
      string XqPrEcBiQr;
      string MEwUmDzeiQ;
      string zzhheEjrUi;
      string xEncrRmGJq;
      string YFoEBXKlxc;
      string eMmKWYJgMA;
      string rJNhuHQSbV;
      string QsUqqsKcfH;
      string sytqDkQcGT;
      string HFsJyOqHJs;
      string GqJbMlquSc;
      string OfAFGtPWdK;
      string pmMINLzLsc;
      string CCTlACnSeQ;
      string sVKcFbEnCD;
      string zUdzDTdBOB;
      if(GytCrnGeuH == rJNhuHQSbV){meCpaLMNFE = true;}
      else if(rJNhuHQSbV == GytCrnGeuH){JNhfgiNoFd = true;}
      if(LpcBOoaPyQ == QsUqqsKcfH){GwrMQUciCl = true;}
      else if(QsUqqsKcfH == LpcBOoaPyQ){yLUmmeGejE = true;}
      if(JCyOTanGxN == sytqDkQcGT){GLIochYTif = true;}
      else if(sytqDkQcGT == JCyOTanGxN){eQefLtBWBA = true;}
      if(bGGkgeqVaV == HFsJyOqHJs){XmEddNSTCt = true;}
      else if(HFsJyOqHJs == bGGkgeqVaV){ETtOPqYFSG = true;}
      if(XqPrEcBiQr == GqJbMlquSc){OphxxCbQhi = true;}
      else if(GqJbMlquSc == XqPrEcBiQr){OyVEEflTVa = true;}
      if(MEwUmDzeiQ == OfAFGtPWdK){qtybtaWMNs = true;}
      else if(OfAFGtPWdK == MEwUmDzeiQ){PgZMzshCUl = true;}
      if(zzhheEjrUi == pmMINLzLsc){mreYgSrOhC = true;}
      else if(pmMINLzLsc == zzhheEjrUi){hpnEZdQFXw = true;}
      if(xEncrRmGJq == CCTlACnSeQ){BIgIWPcLrZ = true;}
      if(YFoEBXKlxc == sVKcFbEnCD){FHkAocnbiC = true;}
      if(eMmKWYJgMA == zUdzDTdBOB){qGGJGVLJQd = true;}
      while(CCTlACnSeQ == xEncrRmGJq){GALdoftaae = true;}
      while(sVKcFbEnCD == sVKcFbEnCD){IhAZkXthOW = true;}
      while(zUdzDTdBOB == zUdzDTdBOB){JVkfYXKQdZ = true;}
      if(meCpaLMNFE == true){meCpaLMNFE = false;}
      if(GwrMQUciCl == true){GwrMQUciCl = false;}
      if(GLIochYTif == true){GLIochYTif = false;}
      if(XmEddNSTCt == true){XmEddNSTCt = false;}
      if(OphxxCbQhi == true){OphxxCbQhi = false;}
      if(qtybtaWMNs == true){qtybtaWMNs = false;}
      if(mreYgSrOhC == true){mreYgSrOhC = false;}
      if(BIgIWPcLrZ == true){BIgIWPcLrZ = false;}
      if(FHkAocnbiC == true){FHkAocnbiC = false;}
      if(qGGJGVLJQd == true){qGGJGVLJQd = false;}
      if(JNhfgiNoFd == true){JNhfgiNoFd = false;}
      if(yLUmmeGejE == true){yLUmmeGejE = false;}
      if(eQefLtBWBA == true){eQefLtBWBA = false;}
      if(ETtOPqYFSG == true){ETtOPqYFSG = false;}
      if(OyVEEflTVa == true){OyVEEflTVa = false;}
      if(PgZMzshCUl == true){PgZMzshCUl = false;}
      if(hpnEZdQFXw == true){hpnEZdQFXw = false;}
      if(GALdoftaae == true){GALdoftaae = false;}
      if(IhAZkXthOW == true){IhAZkXthOW = false;}
      if(JVkfYXKQdZ == true){JVkfYXKQdZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRDQIZAEUZ
{ 
  void nodJKRwHXw()
  { 
      bool ZXDgHuWHOO = false;
      bool fKSNyjhkia = false;
      bool BBiXqKjzMn = false;
      bool GyzcpEZgnk = false;
      bool BlkfnJwDgz = false;
      bool EuIOuXoepx = false;
      bool KXtZIhLpXs = false;
      bool JAwyZOQDjg = false;
      bool NfSNjKojgR = false;
      bool PtqqZdqKWF = false;
      bool yGfmoDzKof = false;
      bool HluIieFgpx = false;
      bool rbIFdOJFYu = false;
      bool WFfeiHAeXf = false;
      bool LetAJdzhHt = false;
      bool YKTZMVxZJZ = false;
      bool tsktJBFQZb = false;
      bool dZIKkNgIwA = false;
      bool PbxdWMlFRM = false;
      bool JZVxkRsAqH = false;
      string DlHVQlCdMh;
      string NIEWMRhtUZ;
      string xSAeaghqfh;
      string flLGUEGaKW;
      string EkaGePeNcR;
      string uoKNnjlbti;
      string ELyeCbwyCI;
      string KGiyVMrtAK;
      string BUONlpayRj;
      string RefaSsluDD;
      string TgLTHoFMqa;
      string rqbjgjwkrM;
      string AxfRpfaIec;
      string awpxqUIuGx;
      string jNGqraCwsi;
      string wBCqCWAsca;
      string NxgOAuAdrL;
      string aBdubmpoZP;
      string cdOwfYszuT;
      string UPReimfrpx;
      if(DlHVQlCdMh == TgLTHoFMqa){ZXDgHuWHOO = true;}
      else if(TgLTHoFMqa == DlHVQlCdMh){yGfmoDzKof = true;}
      if(NIEWMRhtUZ == rqbjgjwkrM){fKSNyjhkia = true;}
      else if(rqbjgjwkrM == NIEWMRhtUZ){HluIieFgpx = true;}
      if(xSAeaghqfh == AxfRpfaIec){BBiXqKjzMn = true;}
      else if(AxfRpfaIec == xSAeaghqfh){rbIFdOJFYu = true;}
      if(flLGUEGaKW == awpxqUIuGx){GyzcpEZgnk = true;}
      else if(awpxqUIuGx == flLGUEGaKW){WFfeiHAeXf = true;}
      if(EkaGePeNcR == jNGqraCwsi){BlkfnJwDgz = true;}
      else if(jNGqraCwsi == EkaGePeNcR){LetAJdzhHt = true;}
      if(uoKNnjlbti == wBCqCWAsca){EuIOuXoepx = true;}
      else if(wBCqCWAsca == uoKNnjlbti){YKTZMVxZJZ = true;}
      if(ELyeCbwyCI == NxgOAuAdrL){KXtZIhLpXs = true;}
      else if(NxgOAuAdrL == ELyeCbwyCI){tsktJBFQZb = true;}
      if(KGiyVMrtAK == aBdubmpoZP){JAwyZOQDjg = true;}
      if(BUONlpayRj == cdOwfYszuT){NfSNjKojgR = true;}
      if(RefaSsluDD == UPReimfrpx){PtqqZdqKWF = true;}
      while(aBdubmpoZP == KGiyVMrtAK){dZIKkNgIwA = true;}
      while(cdOwfYszuT == cdOwfYszuT){PbxdWMlFRM = true;}
      while(UPReimfrpx == UPReimfrpx){JZVxkRsAqH = true;}
      if(ZXDgHuWHOO == true){ZXDgHuWHOO = false;}
      if(fKSNyjhkia == true){fKSNyjhkia = false;}
      if(BBiXqKjzMn == true){BBiXqKjzMn = false;}
      if(GyzcpEZgnk == true){GyzcpEZgnk = false;}
      if(BlkfnJwDgz == true){BlkfnJwDgz = false;}
      if(EuIOuXoepx == true){EuIOuXoepx = false;}
      if(KXtZIhLpXs == true){KXtZIhLpXs = false;}
      if(JAwyZOQDjg == true){JAwyZOQDjg = false;}
      if(NfSNjKojgR == true){NfSNjKojgR = false;}
      if(PtqqZdqKWF == true){PtqqZdqKWF = false;}
      if(yGfmoDzKof == true){yGfmoDzKof = false;}
      if(HluIieFgpx == true){HluIieFgpx = false;}
      if(rbIFdOJFYu == true){rbIFdOJFYu = false;}
      if(WFfeiHAeXf == true){WFfeiHAeXf = false;}
      if(LetAJdzhHt == true){LetAJdzhHt = false;}
      if(YKTZMVxZJZ == true){YKTZMVxZJZ = false;}
      if(tsktJBFQZb == true){tsktJBFQZb = false;}
      if(dZIKkNgIwA == true){dZIKkNgIwA = false;}
      if(PbxdWMlFRM == true){PbxdWMlFRM = false;}
      if(JZVxkRsAqH == true){JZVxkRsAqH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZDPIFMUMU
{ 
  void fHTOwwVZta()
  { 
      bool mhInUpsxDJ = false;
      bool fHVNkzPPUc = false;
      bool PdtHFcWqTO = false;
      bool itPWKIYCXE = false;
      bool pqkmtBAmTp = false;
      bool IVyTJJnBhq = false;
      bool TBcnZlryCc = false;
      bool ZNrQmYrHME = false;
      bool cjWcFNuuNB = false;
      bool UXTfknNwMI = false;
      bool JBjqQtchgj = false;
      bool QgndOidAiL = false;
      bool pwkAIBtMey = false;
      bool LutDubzfMK = false;
      bool jMOckmipRB = false;
      bool JNNARMPiiO = false;
      bool AQDhYUmkim = false;
      bool jynXbdgIPU = false;
      bool SEucnyhskh = false;
      bool LPwxKTJfDP = false;
      string JfsfjrUlOU;
      string rzqIArcywS;
      string ZdtCPXYGdD;
      string WJpbHpiJIa;
      string MdxGdCEsbC;
      string ZprfhekqPL;
      string SOHKyhIPBK;
      string ISpUGwgmXN;
      string SfdbdfRKtb;
      string ErswHxVlIu;
      string soqRsGAWYk;
      string yySCsmjffS;
      string QyUZFQYsNI;
      string ZtebUdnMhW;
      string eukIcGYqDU;
      string NpGpetTRLc;
      string gGJQLDSqhO;
      string zWxJmVNMwy;
      string qhpsuinnwa;
      string JVAFoYlTwY;
      if(JfsfjrUlOU == soqRsGAWYk){mhInUpsxDJ = true;}
      else if(soqRsGAWYk == JfsfjrUlOU){JBjqQtchgj = true;}
      if(rzqIArcywS == yySCsmjffS){fHVNkzPPUc = true;}
      else if(yySCsmjffS == rzqIArcywS){QgndOidAiL = true;}
      if(ZdtCPXYGdD == QyUZFQYsNI){PdtHFcWqTO = true;}
      else if(QyUZFQYsNI == ZdtCPXYGdD){pwkAIBtMey = true;}
      if(WJpbHpiJIa == ZtebUdnMhW){itPWKIYCXE = true;}
      else if(ZtebUdnMhW == WJpbHpiJIa){LutDubzfMK = true;}
      if(MdxGdCEsbC == eukIcGYqDU){pqkmtBAmTp = true;}
      else if(eukIcGYqDU == MdxGdCEsbC){jMOckmipRB = true;}
      if(ZprfhekqPL == NpGpetTRLc){IVyTJJnBhq = true;}
      else if(NpGpetTRLc == ZprfhekqPL){JNNARMPiiO = true;}
      if(SOHKyhIPBK == gGJQLDSqhO){TBcnZlryCc = true;}
      else if(gGJQLDSqhO == SOHKyhIPBK){AQDhYUmkim = true;}
      if(ISpUGwgmXN == zWxJmVNMwy){ZNrQmYrHME = true;}
      if(SfdbdfRKtb == qhpsuinnwa){cjWcFNuuNB = true;}
      if(ErswHxVlIu == JVAFoYlTwY){UXTfknNwMI = true;}
      while(zWxJmVNMwy == ISpUGwgmXN){jynXbdgIPU = true;}
      while(qhpsuinnwa == qhpsuinnwa){SEucnyhskh = true;}
      while(JVAFoYlTwY == JVAFoYlTwY){LPwxKTJfDP = true;}
      if(mhInUpsxDJ == true){mhInUpsxDJ = false;}
      if(fHVNkzPPUc == true){fHVNkzPPUc = false;}
      if(PdtHFcWqTO == true){PdtHFcWqTO = false;}
      if(itPWKIYCXE == true){itPWKIYCXE = false;}
      if(pqkmtBAmTp == true){pqkmtBAmTp = false;}
      if(IVyTJJnBhq == true){IVyTJJnBhq = false;}
      if(TBcnZlryCc == true){TBcnZlryCc = false;}
      if(ZNrQmYrHME == true){ZNrQmYrHME = false;}
      if(cjWcFNuuNB == true){cjWcFNuuNB = false;}
      if(UXTfknNwMI == true){UXTfknNwMI = false;}
      if(JBjqQtchgj == true){JBjqQtchgj = false;}
      if(QgndOidAiL == true){QgndOidAiL = false;}
      if(pwkAIBtMey == true){pwkAIBtMey = false;}
      if(LutDubzfMK == true){LutDubzfMK = false;}
      if(jMOckmipRB == true){jMOckmipRB = false;}
      if(JNNARMPiiO == true){JNNARMPiiO = false;}
      if(AQDhYUmkim == true){AQDhYUmkim = false;}
      if(jynXbdgIPU == true){jynXbdgIPU = false;}
      if(SEucnyhskh == true){SEucnyhskh = false;}
      if(LPwxKTJfDP == true){LPwxKTJfDP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVTHYRMIII
{ 
  void OENspULCmB()
  { 
      bool hcwPVfmFbt = false;
      bool XHJjZkGNGl = false;
      bool cfIDLGdOpV = false;
      bool UeydaKPOnX = false;
      bool weQVlBUEzN = false;
      bool JqPyoCUsEO = false;
      bool BYPFYsJfIO = false;
      bool VqZioxPmQJ = false;
      bool kZOcLdOzoY = false;
      bool oWKYVXOKws = false;
      bool roujrSQgJq = false;
      bool lgbtcbJmsu = false;
      bool eJqjYygAMR = false;
      bool iFqXRweeks = false;
      bool MgpxlItPwt = false;
      bool NbQAOhyKKs = false;
      bool lPUqIgpEcg = false;
      bool xeCAixTsxQ = false;
      bool DQEREGnqJi = false;
      bool xTTqHwMyoF = false;
      string wxugfgsFZU;
      string PrKVdMmUMq;
      string htHllitBoV;
      string azLiYbPFAR;
      string pTjxjqGcKz;
      string DViPuCpItw;
      string mqQEsQfbwB;
      string whTuBOKKCu;
      string cQpoSEPwmV;
      string lHKDdyCfDT;
      string KdfICVCnNg;
      string qeGzSWAako;
      string AjnaPoXPQC;
      string LeGhkyjhmw;
      string CbhFeGBKjH;
      string ybtOSZpFsN;
      string ylWLVMXXOU;
      string lSnnlYBhuJ;
      string nMeJEjjrPK;
      string IenYyQEWjR;
      if(wxugfgsFZU == KdfICVCnNg){hcwPVfmFbt = true;}
      else if(KdfICVCnNg == wxugfgsFZU){roujrSQgJq = true;}
      if(PrKVdMmUMq == qeGzSWAako){XHJjZkGNGl = true;}
      else if(qeGzSWAako == PrKVdMmUMq){lgbtcbJmsu = true;}
      if(htHllitBoV == AjnaPoXPQC){cfIDLGdOpV = true;}
      else if(AjnaPoXPQC == htHllitBoV){eJqjYygAMR = true;}
      if(azLiYbPFAR == LeGhkyjhmw){UeydaKPOnX = true;}
      else if(LeGhkyjhmw == azLiYbPFAR){iFqXRweeks = true;}
      if(pTjxjqGcKz == CbhFeGBKjH){weQVlBUEzN = true;}
      else if(CbhFeGBKjH == pTjxjqGcKz){MgpxlItPwt = true;}
      if(DViPuCpItw == ybtOSZpFsN){JqPyoCUsEO = true;}
      else if(ybtOSZpFsN == DViPuCpItw){NbQAOhyKKs = true;}
      if(mqQEsQfbwB == ylWLVMXXOU){BYPFYsJfIO = true;}
      else if(ylWLVMXXOU == mqQEsQfbwB){lPUqIgpEcg = true;}
      if(whTuBOKKCu == lSnnlYBhuJ){VqZioxPmQJ = true;}
      if(cQpoSEPwmV == nMeJEjjrPK){kZOcLdOzoY = true;}
      if(lHKDdyCfDT == IenYyQEWjR){oWKYVXOKws = true;}
      while(lSnnlYBhuJ == whTuBOKKCu){xeCAixTsxQ = true;}
      while(nMeJEjjrPK == nMeJEjjrPK){DQEREGnqJi = true;}
      while(IenYyQEWjR == IenYyQEWjR){xTTqHwMyoF = true;}
      if(hcwPVfmFbt == true){hcwPVfmFbt = false;}
      if(XHJjZkGNGl == true){XHJjZkGNGl = false;}
      if(cfIDLGdOpV == true){cfIDLGdOpV = false;}
      if(UeydaKPOnX == true){UeydaKPOnX = false;}
      if(weQVlBUEzN == true){weQVlBUEzN = false;}
      if(JqPyoCUsEO == true){JqPyoCUsEO = false;}
      if(BYPFYsJfIO == true){BYPFYsJfIO = false;}
      if(VqZioxPmQJ == true){VqZioxPmQJ = false;}
      if(kZOcLdOzoY == true){kZOcLdOzoY = false;}
      if(oWKYVXOKws == true){oWKYVXOKws = false;}
      if(roujrSQgJq == true){roujrSQgJq = false;}
      if(lgbtcbJmsu == true){lgbtcbJmsu = false;}
      if(eJqjYygAMR == true){eJqjYygAMR = false;}
      if(iFqXRweeks == true){iFqXRweeks = false;}
      if(MgpxlItPwt == true){MgpxlItPwt = false;}
      if(NbQAOhyKKs == true){NbQAOhyKKs = false;}
      if(lPUqIgpEcg == true){lPUqIgpEcg = false;}
      if(xeCAixTsxQ == true){xeCAixTsxQ = false;}
      if(DQEREGnqJi == true){DQEREGnqJi = false;}
      if(xTTqHwMyoF == true){xTTqHwMyoF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICQAYBZMBQ
{ 
  void EwuFIPtcNT()
  { 
      bool qlLmCdHFmK = false;
      bool BYhdRWCUDo = false;
      bool mIfXtlgYtu = false;
      bool ywwISmSdqw = false;
      bool HwiOSgTdmN = false;
      bool KzrrQhGnsQ = false;
      bool wiKrMFbZLd = false;
      bool DXcHhqZQFM = false;
      bool RCkfjyEEqk = false;
      bool gekaAXkpCN = false;
      bool EtSJJlWjJY = false;
      bool HohfysydHN = false;
      bool AWhaxYmCGK = false;
      bool FjOrHWibVy = false;
      bool bTtScqwEbG = false;
      bool YGhoMgLrLk = false;
      bool yTczSXapXb = false;
      bool JWHJlgcPxF = false;
      bool ciZAkzBZeZ = false;
      bool LqPkzHpuzF = false;
      string jfDioztUdU;
      string hqTDTXfeTP;
      string FWfGDESnns;
      string btZKfTAofH;
      string NrkdUcbWVg;
      string ZWLaSMzwej;
      string gGgjsmRIXA;
      string WqzLCMlClZ;
      string buSGTEiyrS;
      string TDJuaHLAjh;
      string LTzUKiXzYF;
      string ZxKFIknZQn;
      string DSQEfShEjt;
      string BkRENIwxwk;
      string gjZlrWsDmp;
      string TljudsCtnq;
      string ATOdEoeGrz;
      string npdeHTrdLJ;
      string ZdQtZPBVZT;
      string FCIFjMUugD;
      if(jfDioztUdU == LTzUKiXzYF){qlLmCdHFmK = true;}
      else if(LTzUKiXzYF == jfDioztUdU){EtSJJlWjJY = true;}
      if(hqTDTXfeTP == ZxKFIknZQn){BYhdRWCUDo = true;}
      else if(ZxKFIknZQn == hqTDTXfeTP){HohfysydHN = true;}
      if(FWfGDESnns == DSQEfShEjt){mIfXtlgYtu = true;}
      else if(DSQEfShEjt == FWfGDESnns){AWhaxYmCGK = true;}
      if(btZKfTAofH == BkRENIwxwk){ywwISmSdqw = true;}
      else if(BkRENIwxwk == btZKfTAofH){FjOrHWibVy = true;}
      if(NrkdUcbWVg == gjZlrWsDmp){HwiOSgTdmN = true;}
      else if(gjZlrWsDmp == NrkdUcbWVg){bTtScqwEbG = true;}
      if(ZWLaSMzwej == TljudsCtnq){KzrrQhGnsQ = true;}
      else if(TljudsCtnq == ZWLaSMzwej){YGhoMgLrLk = true;}
      if(gGgjsmRIXA == ATOdEoeGrz){wiKrMFbZLd = true;}
      else if(ATOdEoeGrz == gGgjsmRIXA){yTczSXapXb = true;}
      if(WqzLCMlClZ == npdeHTrdLJ){DXcHhqZQFM = true;}
      if(buSGTEiyrS == ZdQtZPBVZT){RCkfjyEEqk = true;}
      if(TDJuaHLAjh == FCIFjMUugD){gekaAXkpCN = true;}
      while(npdeHTrdLJ == WqzLCMlClZ){JWHJlgcPxF = true;}
      while(ZdQtZPBVZT == ZdQtZPBVZT){ciZAkzBZeZ = true;}
      while(FCIFjMUugD == FCIFjMUugD){LqPkzHpuzF = true;}
      if(qlLmCdHFmK == true){qlLmCdHFmK = false;}
      if(BYhdRWCUDo == true){BYhdRWCUDo = false;}
      if(mIfXtlgYtu == true){mIfXtlgYtu = false;}
      if(ywwISmSdqw == true){ywwISmSdqw = false;}
      if(HwiOSgTdmN == true){HwiOSgTdmN = false;}
      if(KzrrQhGnsQ == true){KzrrQhGnsQ = false;}
      if(wiKrMFbZLd == true){wiKrMFbZLd = false;}
      if(DXcHhqZQFM == true){DXcHhqZQFM = false;}
      if(RCkfjyEEqk == true){RCkfjyEEqk = false;}
      if(gekaAXkpCN == true){gekaAXkpCN = false;}
      if(EtSJJlWjJY == true){EtSJJlWjJY = false;}
      if(HohfysydHN == true){HohfysydHN = false;}
      if(AWhaxYmCGK == true){AWhaxYmCGK = false;}
      if(FjOrHWibVy == true){FjOrHWibVy = false;}
      if(bTtScqwEbG == true){bTtScqwEbG = false;}
      if(YGhoMgLrLk == true){YGhoMgLrLk = false;}
      if(yTczSXapXb == true){yTczSXapXb = false;}
      if(JWHJlgcPxF == true){JWHJlgcPxF = false;}
      if(ciZAkzBZeZ == true){ciZAkzBZeZ = false;}
      if(LqPkzHpuzF == true){LqPkzHpuzF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIXJDXUACX
{ 
  void ghIfrCyBAX()
  { 
      bool zpbAkdTVoN = false;
      bool DQmTHiLarH = false;
      bool LRdRyqITwJ = false;
      bool TFBeTObJco = false;
      bool XFfNieOytj = false;
      bool RHPLNhLJBt = false;
      bool VzZfsxOHzr = false;
      bool HBxCjGkQiT = false;
      bool bKZLrLopQk = false;
      bool DSHiTXeATk = false;
      bool QHyBcPKMbH = false;
      bool xuZhRLZNmh = false;
      bool IYqOonsOiM = false;
      bool ajwyDULXib = false;
      bool BbOJnHrZQH = false;
      bool xRMlbqPiMn = false;
      bool WudOgMzbex = false;
      bool zBdLfgKgag = false;
      bool wTxbOIXKVL = false;
      bool EbLuFFyzcb = false;
      string teIxIRxzVh;
      string wkVEycTgOT;
      string oahWnXfUmW;
      string YHyhdUgwGC;
      string LkGWilOgWK;
      string sAwrjSwlIk;
      string kbMyJnmmZd;
      string wWZLHETLmB;
      string JzxccYKFyK;
      string XtmVRiYHNt;
      string yaGsNWZkje;
      string zkyHbleiVk;
      string choPGBjEtY;
      string fMyrChrEOG;
      string yZUSLmwfte;
      string EokbQQlpmM;
      string mVpLzlmFEs;
      string sZUPlDNVDS;
      string FDKOTqaVbl;
      string uCRBTciITY;
      if(teIxIRxzVh == yaGsNWZkje){zpbAkdTVoN = true;}
      else if(yaGsNWZkje == teIxIRxzVh){QHyBcPKMbH = true;}
      if(wkVEycTgOT == zkyHbleiVk){DQmTHiLarH = true;}
      else if(zkyHbleiVk == wkVEycTgOT){xuZhRLZNmh = true;}
      if(oahWnXfUmW == choPGBjEtY){LRdRyqITwJ = true;}
      else if(choPGBjEtY == oahWnXfUmW){IYqOonsOiM = true;}
      if(YHyhdUgwGC == fMyrChrEOG){TFBeTObJco = true;}
      else if(fMyrChrEOG == YHyhdUgwGC){ajwyDULXib = true;}
      if(LkGWilOgWK == yZUSLmwfte){XFfNieOytj = true;}
      else if(yZUSLmwfte == LkGWilOgWK){BbOJnHrZQH = true;}
      if(sAwrjSwlIk == EokbQQlpmM){RHPLNhLJBt = true;}
      else if(EokbQQlpmM == sAwrjSwlIk){xRMlbqPiMn = true;}
      if(kbMyJnmmZd == mVpLzlmFEs){VzZfsxOHzr = true;}
      else if(mVpLzlmFEs == kbMyJnmmZd){WudOgMzbex = true;}
      if(wWZLHETLmB == sZUPlDNVDS){HBxCjGkQiT = true;}
      if(JzxccYKFyK == FDKOTqaVbl){bKZLrLopQk = true;}
      if(XtmVRiYHNt == uCRBTciITY){DSHiTXeATk = true;}
      while(sZUPlDNVDS == wWZLHETLmB){zBdLfgKgag = true;}
      while(FDKOTqaVbl == FDKOTqaVbl){wTxbOIXKVL = true;}
      while(uCRBTciITY == uCRBTciITY){EbLuFFyzcb = true;}
      if(zpbAkdTVoN == true){zpbAkdTVoN = false;}
      if(DQmTHiLarH == true){DQmTHiLarH = false;}
      if(LRdRyqITwJ == true){LRdRyqITwJ = false;}
      if(TFBeTObJco == true){TFBeTObJco = false;}
      if(XFfNieOytj == true){XFfNieOytj = false;}
      if(RHPLNhLJBt == true){RHPLNhLJBt = false;}
      if(VzZfsxOHzr == true){VzZfsxOHzr = false;}
      if(HBxCjGkQiT == true){HBxCjGkQiT = false;}
      if(bKZLrLopQk == true){bKZLrLopQk = false;}
      if(DSHiTXeATk == true){DSHiTXeATk = false;}
      if(QHyBcPKMbH == true){QHyBcPKMbH = false;}
      if(xuZhRLZNmh == true){xuZhRLZNmh = false;}
      if(IYqOonsOiM == true){IYqOonsOiM = false;}
      if(ajwyDULXib == true){ajwyDULXib = false;}
      if(BbOJnHrZQH == true){BbOJnHrZQH = false;}
      if(xRMlbqPiMn == true){xRMlbqPiMn = false;}
      if(WudOgMzbex == true){WudOgMzbex = false;}
      if(zBdLfgKgag == true){zBdLfgKgag = false;}
      if(wTxbOIXKVL == true){wTxbOIXKVL = false;}
      if(EbLuFFyzcb == true){EbLuFFyzcb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZPPBXBYYT
{ 
  void TAotQPjJVg()
  { 
      bool VOprRqnRBN = false;
      bool eDOFHyXGTi = false;
      bool omVMabEZrH = false;
      bool nYZcFrgsaD = false;
      bool pRxnWSyNyw = false;
      bool edBIzhrcQo = false;
      bool lOYsYGckAO = false;
      bool RefPsWpgoI = false;
      bool dqbubKXRdX = false;
      bool ADbkRbrDOQ = false;
      bool oMNidAykPb = false;
      bool qKnILumdQO = false;
      bool iLHbOOCtyQ = false;
      bool emSXSQcrRb = false;
      bool MlCCfoPTZV = false;
      bool oOlAhcFkUP = false;
      bool yDlywErPot = false;
      bool RtLoCwJFwZ = false;
      bool ziTcbPASpp = false;
      bool LrXCcIAEFb = false;
      string jxYDByQICM;
      string OfAompwMJj;
      string VYDadZPXdj;
      string pVnGkyxWGV;
      string iAaHownNFA;
      string WqlckKsyZa;
      string irdRWsqtEn;
      string rYGmBVxwkh;
      string lBScNyiLVZ;
      string EzxempVJkw;
      string EtJQIxkzaO;
      string MxMrogZBEX;
      string JeYdisbazL;
      string AnLocqrBUQ;
      string MjkGMHlFpG;
      string PUEMmZVegO;
      string VJzPOYlXPx;
      string oYfmLYtRQb;
      string HWksueiyCC;
      string VMTFuDjUrn;
      if(jxYDByQICM == EtJQIxkzaO){VOprRqnRBN = true;}
      else if(EtJQIxkzaO == jxYDByQICM){oMNidAykPb = true;}
      if(OfAompwMJj == MxMrogZBEX){eDOFHyXGTi = true;}
      else if(MxMrogZBEX == OfAompwMJj){qKnILumdQO = true;}
      if(VYDadZPXdj == JeYdisbazL){omVMabEZrH = true;}
      else if(JeYdisbazL == VYDadZPXdj){iLHbOOCtyQ = true;}
      if(pVnGkyxWGV == AnLocqrBUQ){nYZcFrgsaD = true;}
      else if(AnLocqrBUQ == pVnGkyxWGV){emSXSQcrRb = true;}
      if(iAaHownNFA == MjkGMHlFpG){pRxnWSyNyw = true;}
      else if(MjkGMHlFpG == iAaHownNFA){MlCCfoPTZV = true;}
      if(WqlckKsyZa == PUEMmZVegO){edBIzhrcQo = true;}
      else if(PUEMmZVegO == WqlckKsyZa){oOlAhcFkUP = true;}
      if(irdRWsqtEn == VJzPOYlXPx){lOYsYGckAO = true;}
      else if(VJzPOYlXPx == irdRWsqtEn){yDlywErPot = true;}
      if(rYGmBVxwkh == oYfmLYtRQb){RefPsWpgoI = true;}
      if(lBScNyiLVZ == HWksueiyCC){dqbubKXRdX = true;}
      if(EzxempVJkw == VMTFuDjUrn){ADbkRbrDOQ = true;}
      while(oYfmLYtRQb == rYGmBVxwkh){RtLoCwJFwZ = true;}
      while(HWksueiyCC == HWksueiyCC){ziTcbPASpp = true;}
      while(VMTFuDjUrn == VMTFuDjUrn){LrXCcIAEFb = true;}
      if(VOprRqnRBN == true){VOprRqnRBN = false;}
      if(eDOFHyXGTi == true){eDOFHyXGTi = false;}
      if(omVMabEZrH == true){omVMabEZrH = false;}
      if(nYZcFrgsaD == true){nYZcFrgsaD = false;}
      if(pRxnWSyNyw == true){pRxnWSyNyw = false;}
      if(edBIzhrcQo == true){edBIzhrcQo = false;}
      if(lOYsYGckAO == true){lOYsYGckAO = false;}
      if(RefPsWpgoI == true){RefPsWpgoI = false;}
      if(dqbubKXRdX == true){dqbubKXRdX = false;}
      if(ADbkRbrDOQ == true){ADbkRbrDOQ = false;}
      if(oMNidAykPb == true){oMNidAykPb = false;}
      if(qKnILumdQO == true){qKnILumdQO = false;}
      if(iLHbOOCtyQ == true){iLHbOOCtyQ = false;}
      if(emSXSQcrRb == true){emSXSQcrRb = false;}
      if(MlCCfoPTZV == true){MlCCfoPTZV = false;}
      if(oOlAhcFkUP == true){oOlAhcFkUP = false;}
      if(yDlywErPot == true){yDlywErPot = false;}
      if(RtLoCwJFwZ == true){RtLoCwJFwZ = false;}
      if(ziTcbPASpp == true){ziTcbPASpp = false;}
      if(LrXCcIAEFb == true){LrXCcIAEFb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKKURCUOOV
{ 
  void dCUrKeDDlI()
  { 
      bool HKdztHKKuC = false;
      bool mioUAkBJVQ = false;
      bool YsmbSIMRqz = false;
      bool FHKYgNLyml = false;
      bool VJXYlcIWsQ = false;
      bool axoOXOXBfk = false;
      bool usSwxeXQmm = false;
      bool YCVjuPVNpp = false;
      bool AoYaXHRwAS = false;
      bool pJRBpbpabG = false;
      bool EqjFqXbFSI = false;
      bool rJLpkFUrYo = false;
      bool NbQUxPjTsT = false;
      bool YtlikIFSiz = false;
      bool fLdqZfybQk = false;
      bool HyClscaPIb = false;
      bool nHLyixXbFb = false;
      bool ACIYIByYtQ = false;
      bool QIDIMarzoI = false;
      bool gpJHLYzeHc = false;
      string bVuuQOzOxR;
      string dqhjZgNQLU;
      string aOBYeUTXsD;
      string IwwjSrCdqL;
      string uWSjHxqnBB;
      string fCYwFMTWPu;
      string ubVsJhuyRh;
      string diZzZEwQQh;
      string deVqXFWzdG;
      string XfNwQSBYaZ;
      string CsWTXwcZWA;
      string PDGhQPGeUD;
      string KuTLJyVciG;
      string DXpqfkIBSb;
      string bxbcpUZfeB;
      string MWDWPGYKJY;
      string ZzqQxrMOBe;
      string GELsaMTpVo;
      string YoygtfTSbY;
      string MxrsBbGLex;
      if(bVuuQOzOxR == CsWTXwcZWA){HKdztHKKuC = true;}
      else if(CsWTXwcZWA == bVuuQOzOxR){EqjFqXbFSI = true;}
      if(dqhjZgNQLU == PDGhQPGeUD){mioUAkBJVQ = true;}
      else if(PDGhQPGeUD == dqhjZgNQLU){rJLpkFUrYo = true;}
      if(aOBYeUTXsD == KuTLJyVciG){YsmbSIMRqz = true;}
      else if(KuTLJyVciG == aOBYeUTXsD){NbQUxPjTsT = true;}
      if(IwwjSrCdqL == DXpqfkIBSb){FHKYgNLyml = true;}
      else if(DXpqfkIBSb == IwwjSrCdqL){YtlikIFSiz = true;}
      if(uWSjHxqnBB == bxbcpUZfeB){VJXYlcIWsQ = true;}
      else if(bxbcpUZfeB == uWSjHxqnBB){fLdqZfybQk = true;}
      if(fCYwFMTWPu == MWDWPGYKJY){axoOXOXBfk = true;}
      else if(MWDWPGYKJY == fCYwFMTWPu){HyClscaPIb = true;}
      if(ubVsJhuyRh == ZzqQxrMOBe){usSwxeXQmm = true;}
      else if(ZzqQxrMOBe == ubVsJhuyRh){nHLyixXbFb = true;}
      if(diZzZEwQQh == GELsaMTpVo){YCVjuPVNpp = true;}
      if(deVqXFWzdG == YoygtfTSbY){AoYaXHRwAS = true;}
      if(XfNwQSBYaZ == MxrsBbGLex){pJRBpbpabG = true;}
      while(GELsaMTpVo == diZzZEwQQh){ACIYIByYtQ = true;}
      while(YoygtfTSbY == YoygtfTSbY){QIDIMarzoI = true;}
      while(MxrsBbGLex == MxrsBbGLex){gpJHLYzeHc = true;}
      if(HKdztHKKuC == true){HKdztHKKuC = false;}
      if(mioUAkBJVQ == true){mioUAkBJVQ = false;}
      if(YsmbSIMRqz == true){YsmbSIMRqz = false;}
      if(FHKYgNLyml == true){FHKYgNLyml = false;}
      if(VJXYlcIWsQ == true){VJXYlcIWsQ = false;}
      if(axoOXOXBfk == true){axoOXOXBfk = false;}
      if(usSwxeXQmm == true){usSwxeXQmm = false;}
      if(YCVjuPVNpp == true){YCVjuPVNpp = false;}
      if(AoYaXHRwAS == true){AoYaXHRwAS = false;}
      if(pJRBpbpabG == true){pJRBpbpabG = false;}
      if(EqjFqXbFSI == true){EqjFqXbFSI = false;}
      if(rJLpkFUrYo == true){rJLpkFUrYo = false;}
      if(NbQUxPjTsT == true){NbQUxPjTsT = false;}
      if(YtlikIFSiz == true){YtlikIFSiz = false;}
      if(fLdqZfybQk == true){fLdqZfybQk = false;}
      if(HyClscaPIb == true){HyClscaPIb = false;}
      if(nHLyixXbFb == true){nHLyixXbFb = false;}
      if(ACIYIByYtQ == true){ACIYIByYtQ = false;}
      if(QIDIMarzoI == true){QIDIMarzoI = false;}
      if(gpJHLYzeHc == true){gpJHLYzeHc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVTVRHTODF
{ 
  void caYxMAdaNz()
  { 
      bool lzNNDkkMoK = false;
      bool gZAHBFWmtC = false;
      bool gsQTVBJqXR = false;
      bool PQfMUMPBNY = false;
      bool bqdODMPgKy = false;
      bool OjpFZrhtqB = false;
      bool atoWuQsmmn = false;
      bool oUZUZoPCPJ = false;
      bool lbfYDeZalc = false;
      bool dVJLxhCGSm = false;
      bool SbtVJsKVek = false;
      bool cfdgOyOPTQ = false;
      bool pSBKKTKNWr = false;
      bool lIicqKhKPJ = false;
      bool UEuBzxqcwz = false;
      bool TmmCxAaiKo = false;
      bool hwzlyTxApE = false;
      bool PDzJulWAKN = false;
      bool bhRXYzVgfp = false;
      bool jyzaaYEICf = false;
      string PeVOlxFKbz;
      string ysejNyzYuw;
      string pmWawEfbzq;
      string dQQZAgwKKm;
      string QZoorCeQCO;
      string VjydicHuSg;
      string QcLjUgcEjf;
      string BoNIfPyght;
      string ZPZkUsRlqW;
      string ZBrcVmOEUL;
      string ZZfVMgWpxS;
      string eZMYHADZPa;
      string OpMMGAxkls;
      string BsMWTziEXn;
      string WbnYrzoSVU;
      string inosxiNTOM;
      string jkEDQkNoEH;
      string RyCbDlBnTH;
      string LdOQJNETYk;
      string lPoLEkWkHH;
      if(PeVOlxFKbz == ZZfVMgWpxS){lzNNDkkMoK = true;}
      else if(ZZfVMgWpxS == PeVOlxFKbz){SbtVJsKVek = true;}
      if(ysejNyzYuw == eZMYHADZPa){gZAHBFWmtC = true;}
      else if(eZMYHADZPa == ysejNyzYuw){cfdgOyOPTQ = true;}
      if(pmWawEfbzq == OpMMGAxkls){gsQTVBJqXR = true;}
      else if(OpMMGAxkls == pmWawEfbzq){pSBKKTKNWr = true;}
      if(dQQZAgwKKm == BsMWTziEXn){PQfMUMPBNY = true;}
      else if(BsMWTziEXn == dQQZAgwKKm){lIicqKhKPJ = true;}
      if(QZoorCeQCO == WbnYrzoSVU){bqdODMPgKy = true;}
      else if(WbnYrzoSVU == QZoorCeQCO){UEuBzxqcwz = true;}
      if(VjydicHuSg == inosxiNTOM){OjpFZrhtqB = true;}
      else if(inosxiNTOM == VjydicHuSg){TmmCxAaiKo = true;}
      if(QcLjUgcEjf == jkEDQkNoEH){atoWuQsmmn = true;}
      else if(jkEDQkNoEH == QcLjUgcEjf){hwzlyTxApE = true;}
      if(BoNIfPyght == RyCbDlBnTH){oUZUZoPCPJ = true;}
      if(ZPZkUsRlqW == LdOQJNETYk){lbfYDeZalc = true;}
      if(ZBrcVmOEUL == lPoLEkWkHH){dVJLxhCGSm = true;}
      while(RyCbDlBnTH == BoNIfPyght){PDzJulWAKN = true;}
      while(LdOQJNETYk == LdOQJNETYk){bhRXYzVgfp = true;}
      while(lPoLEkWkHH == lPoLEkWkHH){jyzaaYEICf = true;}
      if(lzNNDkkMoK == true){lzNNDkkMoK = false;}
      if(gZAHBFWmtC == true){gZAHBFWmtC = false;}
      if(gsQTVBJqXR == true){gsQTVBJqXR = false;}
      if(PQfMUMPBNY == true){PQfMUMPBNY = false;}
      if(bqdODMPgKy == true){bqdODMPgKy = false;}
      if(OjpFZrhtqB == true){OjpFZrhtqB = false;}
      if(atoWuQsmmn == true){atoWuQsmmn = false;}
      if(oUZUZoPCPJ == true){oUZUZoPCPJ = false;}
      if(lbfYDeZalc == true){lbfYDeZalc = false;}
      if(dVJLxhCGSm == true){dVJLxhCGSm = false;}
      if(SbtVJsKVek == true){SbtVJsKVek = false;}
      if(cfdgOyOPTQ == true){cfdgOyOPTQ = false;}
      if(pSBKKTKNWr == true){pSBKKTKNWr = false;}
      if(lIicqKhKPJ == true){lIicqKhKPJ = false;}
      if(UEuBzxqcwz == true){UEuBzxqcwz = false;}
      if(TmmCxAaiKo == true){TmmCxAaiKo = false;}
      if(hwzlyTxApE == true){hwzlyTxApE = false;}
      if(PDzJulWAKN == true){PDzJulWAKN = false;}
      if(bhRXYzVgfp == true){bhRXYzVgfp = false;}
      if(jyzaaYEICf == true){jyzaaYEICf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCBSMDJMKZ
{ 
  void rLbNXqJUnV()
  { 
      bool qSlnuYLUPU = false;
      bool TNbqsbzdLc = false;
      bool EaIRgRKrnT = false;
      bool IVsDPzUubf = false;
      bool eafunXheWi = false;
      bool hQxzxQJUGd = false;
      bool OTguMxUYas = false;
      bool GECfyctNcJ = false;
      bool jeUElqYsGz = false;
      bool oAoyQKtkip = false;
      bool CJEcbdOQBT = false;
      bool WwqwtiybJV = false;
      bool YaRbEGPEOm = false;
      bool hJdmGZarcH = false;
      bool bHqlbsIrDh = false;
      bool MSaNQbqbYV = false;
      bool OJBOkNREpT = false;
      bool HGzBsRifzK = false;
      bool yWAgZPhQVe = false;
      bool izSGsSFcAO = false;
      string giQAjoaJEN;
      string WFGmHDlxZY;
      string plxlOUrgfL;
      string CbANNklcLn;
      string DeHwVHuMqk;
      string MLhynulelO;
      string xscsKuFrYV;
      string QJlkVLdAPH;
      string ZepuyqtBYS;
      string zHpwpJBOlZ;
      string BDmUTDYwcc;
      string QkOeoSChtT;
      string BDSGVJTpuL;
      string JPOoFVqVau;
      string RxYwBOrLGX;
      string GSTRYxjgyK;
      string jiBQTAWYYS;
      string bgHzCDdVEH;
      string RHiWEpwwQH;
      string lJWPLhuIcB;
      if(giQAjoaJEN == BDmUTDYwcc){qSlnuYLUPU = true;}
      else if(BDmUTDYwcc == giQAjoaJEN){CJEcbdOQBT = true;}
      if(WFGmHDlxZY == QkOeoSChtT){TNbqsbzdLc = true;}
      else if(QkOeoSChtT == WFGmHDlxZY){WwqwtiybJV = true;}
      if(plxlOUrgfL == BDSGVJTpuL){EaIRgRKrnT = true;}
      else if(BDSGVJTpuL == plxlOUrgfL){YaRbEGPEOm = true;}
      if(CbANNklcLn == JPOoFVqVau){IVsDPzUubf = true;}
      else if(JPOoFVqVau == CbANNklcLn){hJdmGZarcH = true;}
      if(DeHwVHuMqk == RxYwBOrLGX){eafunXheWi = true;}
      else if(RxYwBOrLGX == DeHwVHuMqk){bHqlbsIrDh = true;}
      if(MLhynulelO == GSTRYxjgyK){hQxzxQJUGd = true;}
      else if(GSTRYxjgyK == MLhynulelO){MSaNQbqbYV = true;}
      if(xscsKuFrYV == jiBQTAWYYS){OTguMxUYas = true;}
      else if(jiBQTAWYYS == xscsKuFrYV){OJBOkNREpT = true;}
      if(QJlkVLdAPH == bgHzCDdVEH){GECfyctNcJ = true;}
      if(ZepuyqtBYS == RHiWEpwwQH){jeUElqYsGz = true;}
      if(zHpwpJBOlZ == lJWPLhuIcB){oAoyQKtkip = true;}
      while(bgHzCDdVEH == QJlkVLdAPH){HGzBsRifzK = true;}
      while(RHiWEpwwQH == RHiWEpwwQH){yWAgZPhQVe = true;}
      while(lJWPLhuIcB == lJWPLhuIcB){izSGsSFcAO = true;}
      if(qSlnuYLUPU == true){qSlnuYLUPU = false;}
      if(TNbqsbzdLc == true){TNbqsbzdLc = false;}
      if(EaIRgRKrnT == true){EaIRgRKrnT = false;}
      if(IVsDPzUubf == true){IVsDPzUubf = false;}
      if(eafunXheWi == true){eafunXheWi = false;}
      if(hQxzxQJUGd == true){hQxzxQJUGd = false;}
      if(OTguMxUYas == true){OTguMxUYas = false;}
      if(GECfyctNcJ == true){GECfyctNcJ = false;}
      if(jeUElqYsGz == true){jeUElqYsGz = false;}
      if(oAoyQKtkip == true){oAoyQKtkip = false;}
      if(CJEcbdOQBT == true){CJEcbdOQBT = false;}
      if(WwqwtiybJV == true){WwqwtiybJV = false;}
      if(YaRbEGPEOm == true){YaRbEGPEOm = false;}
      if(hJdmGZarcH == true){hJdmGZarcH = false;}
      if(bHqlbsIrDh == true){bHqlbsIrDh = false;}
      if(MSaNQbqbYV == true){MSaNQbqbYV = false;}
      if(OJBOkNREpT == true){OJBOkNREpT = false;}
      if(HGzBsRifzK == true){HGzBsRifzK = false;}
      if(yWAgZPhQVe == true){yWAgZPhQVe = false;}
      if(izSGsSFcAO == true){izSGsSFcAO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNZZGCTTTR
{ 
  void zEaSVfyKcJ()
  { 
      bool ZKsSpLxRaf = false;
      bool DVzjVOblos = false;
      bool GzlAwpuJxI = false;
      bool RPgXjyyuzw = false;
      bool KDHZiCYfWd = false;
      bool fwsRPaYrWA = false;
      bool PmTSNnnazW = false;
      bool QflriCqMRt = false;
      bool QOlScUWPHJ = false;
      bool ZFYygWjoLu = false;
      bool OxgANzKBhM = false;
      bool iLabiBBBor = false;
      bool QXTpxLHmKM = false;
      bool SCAWfShlFc = false;
      bool KVhtaNewPf = false;
      bool UhzTdpdpCC = false;
      bool qWpUtgLDwQ = false;
      bool SPuMgupZOi = false;
      bool fLXeqjCgro = false;
      bool oqiDkneMAt = false;
      string gSdlJfRsTl;
      string hDllejsFFY;
      string EyjTmxsTAw;
      string hmQMmxqJHX;
      string uUVHnSrmtj;
      string PqEHrhiKyL;
      string myrWDtlYzg;
      string sjygcjbcfU;
      string EGYQfphJUE;
      string OgKukwbzDs;
      string fSnNqfsXdI;
      string FGdcHfYbqM;
      string LcEtRLYCug;
      string HcYlolRLYA;
      string xKeLzHCgnE;
      string XAHpgCNtue;
      string GpbxAbhqnU;
      string OMCpPByrtK;
      string JqOpIHUhFm;
      string XXQssHihKW;
      if(gSdlJfRsTl == fSnNqfsXdI){ZKsSpLxRaf = true;}
      else if(fSnNqfsXdI == gSdlJfRsTl){OxgANzKBhM = true;}
      if(hDllejsFFY == FGdcHfYbqM){DVzjVOblos = true;}
      else if(FGdcHfYbqM == hDllejsFFY){iLabiBBBor = true;}
      if(EyjTmxsTAw == LcEtRLYCug){GzlAwpuJxI = true;}
      else if(LcEtRLYCug == EyjTmxsTAw){QXTpxLHmKM = true;}
      if(hmQMmxqJHX == HcYlolRLYA){RPgXjyyuzw = true;}
      else if(HcYlolRLYA == hmQMmxqJHX){SCAWfShlFc = true;}
      if(uUVHnSrmtj == xKeLzHCgnE){KDHZiCYfWd = true;}
      else if(xKeLzHCgnE == uUVHnSrmtj){KVhtaNewPf = true;}
      if(PqEHrhiKyL == XAHpgCNtue){fwsRPaYrWA = true;}
      else if(XAHpgCNtue == PqEHrhiKyL){UhzTdpdpCC = true;}
      if(myrWDtlYzg == GpbxAbhqnU){PmTSNnnazW = true;}
      else if(GpbxAbhqnU == myrWDtlYzg){qWpUtgLDwQ = true;}
      if(sjygcjbcfU == OMCpPByrtK){QflriCqMRt = true;}
      if(EGYQfphJUE == JqOpIHUhFm){QOlScUWPHJ = true;}
      if(OgKukwbzDs == XXQssHihKW){ZFYygWjoLu = true;}
      while(OMCpPByrtK == sjygcjbcfU){SPuMgupZOi = true;}
      while(JqOpIHUhFm == JqOpIHUhFm){fLXeqjCgro = true;}
      while(XXQssHihKW == XXQssHihKW){oqiDkneMAt = true;}
      if(ZKsSpLxRaf == true){ZKsSpLxRaf = false;}
      if(DVzjVOblos == true){DVzjVOblos = false;}
      if(GzlAwpuJxI == true){GzlAwpuJxI = false;}
      if(RPgXjyyuzw == true){RPgXjyyuzw = false;}
      if(KDHZiCYfWd == true){KDHZiCYfWd = false;}
      if(fwsRPaYrWA == true){fwsRPaYrWA = false;}
      if(PmTSNnnazW == true){PmTSNnnazW = false;}
      if(QflriCqMRt == true){QflriCqMRt = false;}
      if(QOlScUWPHJ == true){QOlScUWPHJ = false;}
      if(ZFYygWjoLu == true){ZFYygWjoLu = false;}
      if(OxgANzKBhM == true){OxgANzKBhM = false;}
      if(iLabiBBBor == true){iLabiBBBor = false;}
      if(QXTpxLHmKM == true){QXTpxLHmKM = false;}
      if(SCAWfShlFc == true){SCAWfShlFc = false;}
      if(KVhtaNewPf == true){KVhtaNewPf = false;}
      if(UhzTdpdpCC == true){UhzTdpdpCC = false;}
      if(qWpUtgLDwQ == true){qWpUtgLDwQ = false;}
      if(SPuMgupZOi == true){SPuMgupZOi = false;}
      if(fLXeqjCgro == true){fLXeqjCgro = false;}
      if(oqiDkneMAt == true){oqiDkneMAt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUISLWEBRK
{ 
  void PTmyTGAACO()
  { 
      bool EtVzfodnuw = false;
      bool YAnzAlbtIH = false;
      bool tLHRBOsTSU = false;
      bool SzHcYEBjlL = false;
      bool pNjaHeBmrU = false;
      bool CSosDsmDyQ = false;
      bool wKUZcZsLZw = false;
      bool jqIwRgagKV = false;
      bool NFaxSAKOYf = false;
      bool RykUPfrJxh = false;
      bool lpNwkKJrbW = false;
      bool SGrbDqiXHb = false;
      bool OdltdkGmgk = false;
      bool nQicjXqeMI = false;
      bool pRmCNLFIRX = false;
      bool xUCUSHDTRz = false;
      bool DWKphBWPqe = false;
      bool ADLzkxqifS = false;
      bool fxVJnSOOJc = false;
      bool TWNMETHwTL = false;
      string ZgGigGeitT;
      string jKNafiPUlW;
      string ZnDzDeHNNi;
      string MtNLtqJBDq;
      string hRQrUYwRsx;
      string PsIWukcHfC;
      string yQVKHowCfo;
      string ZNRuoHWKde;
      string hpUPSSlpQJ;
      string OCVArRwGje;
      string btkEWCbNhm;
      string NRcBUIwFqo;
      string DFkWaXrQCW;
      string LQayCnEQrQ;
      string pXIcuwYUfj;
      string VqOtbVIOcz;
      string JLLKbxqdyf;
      string EfMZzexIad;
      string zXjRBTCfWf;
      string eomsHdMyAy;
      if(ZgGigGeitT == btkEWCbNhm){EtVzfodnuw = true;}
      else if(btkEWCbNhm == ZgGigGeitT){lpNwkKJrbW = true;}
      if(jKNafiPUlW == NRcBUIwFqo){YAnzAlbtIH = true;}
      else if(NRcBUIwFqo == jKNafiPUlW){SGrbDqiXHb = true;}
      if(ZnDzDeHNNi == DFkWaXrQCW){tLHRBOsTSU = true;}
      else if(DFkWaXrQCW == ZnDzDeHNNi){OdltdkGmgk = true;}
      if(MtNLtqJBDq == LQayCnEQrQ){SzHcYEBjlL = true;}
      else if(LQayCnEQrQ == MtNLtqJBDq){nQicjXqeMI = true;}
      if(hRQrUYwRsx == pXIcuwYUfj){pNjaHeBmrU = true;}
      else if(pXIcuwYUfj == hRQrUYwRsx){pRmCNLFIRX = true;}
      if(PsIWukcHfC == VqOtbVIOcz){CSosDsmDyQ = true;}
      else if(VqOtbVIOcz == PsIWukcHfC){xUCUSHDTRz = true;}
      if(yQVKHowCfo == JLLKbxqdyf){wKUZcZsLZw = true;}
      else if(JLLKbxqdyf == yQVKHowCfo){DWKphBWPqe = true;}
      if(ZNRuoHWKde == EfMZzexIad){jqIwRgagKV = true;}
      if(hpUPSSlpQJ == zXjRBTCfWf){NFaxSAKOYf = true;}
      if(OCVArRwGje == eomsHdMyAy){RykUPfrJxh = true;}
      while(EfMZzexIad == ZNRuoHWKde){ADLzkxqifS = true;}
      while(zXjRBTCfWf == zXjRBTCfWf){fxVJnSOOJc = true;}
      while(eomsHdMyAy == eomsHdMyAy){TWNMETHwTL = true;}
      if(EtVzfodnuw == true){EtVzfodnuw = false;}
      if(YAnzAlbtIH == true){YAnzAlbtIH = false;}
      if(tLHRBOsTSU == true){tLHRBOsTSU = false;}
      if(SzHcYEBjlL == true){SzHcYEBjlL = false;}
      if(pNjaHeBmrU == true){pNjaHeBmrU = false;}
      if(CSosDsmDyQ == true){CSosDsmDyQ = false;}
      if(wKUZcZsLZw == true){wKUZcZsLZw = false;}
      if(jqIwRgagKV == true){jqIwRgagKV = false;}
      if(NFaxSAKOYf == true){NFaxSAKOYf = false;}
      if(RykUPfrJxh == true){RykUPfrJxh = false;}
      if(lpNwkKJrbW == true){lpNwkKJrbW = false;}
      if(SGrbDqiXHb == true){SGrbDqiXHb = false;}
      if(OdltdkGmgk == true){OdltdkGmgk = false;}
      if(nQicjXqeMI == true){nQicjXqeMI = false;}
      if(pRmCNLFIRX == true){pRmCNLFIRX = false;}
      if(xUCUSHDTRz == true){xUCUSHDTRz = false;}
      if(DWKphBWPqe == true){DWKphBWPqe = false;}
      if(ADLzkxqifS == true){ADLzkxqifS = false;}
      if(fxVJnSOOJc == true){fxVJnSOOJc = false;}
      if(TWNMETHwTL == true){TWNMETHwTL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAAFOPLJVN
{ 
  void EonCDBumLY()
  { 
      bool PghLFGcMxV = false;
      bool XSuDZuyDRz = false;
      bool SXHKYMpkBJ = false;
      bool SjKIpWcwpc = false;
      bool ecWkGQtWVL = false;
      bool ENPkOrYXlr = false;
      bool PrLmDmHmMC = false;
      bool RBNnUoBWDI = false;
      bool STPoEFUZty = false;
      bool xFKyMmRihS = false;
      bool JGJSsDAaPY = false;
      bool qCUdZwbVhx = false;
      bool SgsOFMqObh = false;
      bool XRokyLJwwB = false;
      bool EsJUHujfYP = false;
      bool KuAjzbNuMf = false;
      bool MkyhAYNjfN = false;
      bool mfYgrYXXHK = false;
      bool bKpLWbREkV = false;
      bool yNiPnSuaTh = false;
      string epLyVQhUiH;
      string rRfIzGItBO;
      string HOKIiLtXKJ;
      string nScYWIdtmJ;
      string iZPzjbJCPG;
      string ErwmGQfDOJ;
      string WJJZSZnGkq;
      string bOHqfgzKYG;
      string BrIEEuWoRG;
      string caecmYPogK;
      string nDQXepkEHZ;
      string QUdHHdBFVW;
      string CyneOAidEG;
      string RJcOSybjYN;
      string KRhroHwWUI;
      string XJTJHoOkJd;
      string HGAAHHqPnJ;
      string CQgHMkQwpG;
      string ELIwiHoTHd;
      string jpZuGDRgkg;
      if(epLyVQhUiH == nDQXepkEHZ){PghLFGcMxV = true;}
      else if(nDQXepkEHZ == epLyVQhUiH){JGJSsDAaPY = true;}
      if(rRfIzGItBO == QUdHHdBFVW){XSuDZuyDRz = true;}
      else if(QUdHHdBFVW == rRfIzGItBO){qCUdZwbVhx = true;}
      if(HOKIiLtXKJ == CyneOAidEG){SXHKYMpkBJ = true;}
      else if(CyneOAidEG == HOKIiLtXKJ){SgsOFMqObh = true;}
      if(nScYWIdtmJ == RJcOSybjYN){SjKIpWcwpc = true;}
      else if(RJcOSybjYN == nScYWIdtmJ){XRokyLJwwB = true;}
      if(iZPzjbJCPG == KRhroHwWUI){ecWkGQtWVL = true;}
      else if(KRhroHwWUI == iZPzjbJCPG){EsJUHujfYP = true;}
      if(ErwmGQfDOJ == XJTJHoOkJd){ENPkOrYXlr = true;}
      else if(XJTJHoOkJd == ErwmGQfDOJ){KuAjzbNuMf = true;}
      if(WJJZSZnGkq == HGAAHHqPnJ){PrLmDmHmMC = true;}
      else if(HGAAHHqPnJ == WJJZSZnGkq){MkyhAYNjfN = true;}
      if(bOHqfgzKYG == CQgHMkQwpG){RBNnUoBWDI = true;}
      if(BrIEEuWoRG == ELIwiHoTHd){STPoEFUZty = true;}
      if(caecmYPogK == jpZuGDRgkg){xFKyMmRihS = true;}
      while(CQgHMkQwpG == bOHqfgzKYG){mfYgrYXXHK = true;}
      while(ELIwiHoTHd == ELIwiHoTHd){bKpLWbREkV = true;}
      while(jpZuGDRgkg == jpZuGDRgkg){yNiPnSuaTh = true;}
      if(PghLFGcMxV == true){PghLFGcMxV = false;}
      if(XSuDZuyDRz == true){XSuDZuyDRz = false;}
      if(SXHKYMpkBJ == true){SXHKYMpkBJ = false;}
      if(SjKIpWcwpc == true){SjKIpWcwpc = false;}
      if(ecWkGQtWVL == true){ecWkGQtWVL = false;}
      if(ENPkOrYXlr == true){ENPkOrYXlr = false;}
      if(PrLmDmHmMC == true){PrLmDmHmMC = false;}
      if(RBNnUoBWDI == true){RBNnUoBWDI = false;}
      if(STPoEFUZty == true){STPoEFUZty = false;}
      if(xFKyMmRihS == true){xFKyMmRihS = false;}
      if(JGJSsDAaPY == true){JGJSsDAaPY = false;}
      if(qCUdZwbVhx == true){qCUdZwbVhx = false;}
      if(SgsOFMqObh == true){SgsOFMqObh = false;}
      if(XRokyLJwwB == true){XRokyLJwwB = false;}
      if(EsJUHujfYP == true){EsJUHujfYP = false;}
      if(KuAjzbNuMf == true){KuAjzbNuMf = false;}
      if(MkyhAYNjfN == true){MkyhAYNjfN = false;}
      if(mfYgrYXXHK == true){mfYgrYXXHK = false;}
      if(bKpLWbREkV == true){bKpLWbREkV = false;}
      if(yNiPnSuaTh == true){yNiPnSuaTh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZRKLZIGBV
{ 
  void KLOITmuHoM()
  { 
      bool eUPpcSaRkB = false;
      bool wkMsWFzyHZ = false;
      bool xYpNsgfMOX = false;
      bool tYcKUxgPKY = false;
      bool OFrtXTYOJM = false;
      bool LLRhhFdCxw = false;
      bool lNCNGXHBXZ = false;
      bool YjniLrfwpY = false;
      bool HQDCLiHubP = false;
      bool SeRNlACemA = false;
      bool LWpjnbWiVp = false;
      bool YgLYnUKABX = false;
      bool QMYIGsRZwL = false;
      bool oAIpNjaTOi = false;
      bool LXYlplTsZQ = false;
      bool pCdPiyyhct = false;
      bool KwlKAXXULD = false;
      bool tqlRLrnmSU = false;
      bool ZXAeUmWsGO = false;
      bool lrpTYPlNlR = false;
      string ZtarsLAEtE;
      string uaYuhFePmW;
      string RGSgHFRcKS;
      string hbaOKMnjEy;
      string WaftZUrfxd;
      string uNJAQSatkn;
      string tWsaWTzJjU;
      string RuLnAqaXHl;
      string MkefWTSayr;
      string lsyQEzgEXG;
      string UiucMABVAZ;
      string qDmzaIqNEC;
      string AYLriXwuiA;
      string JWzAQcpCTW;
      string RwZYAhGzow;
      string HTzVFwXDtn;
      string DGlAPUDliy;
      string SoshjEzlqA;
      string RxGmroWduU;
      string FlIfSLKZIf;
      if(ZtarsLAEtE == UiucMABVAZ){eUPpcSaRkB = true;}
      else if(UiucMABVAZ == ZtarsLAEtE){LWpjnbWiVp = true;}
      if(uaYuhFePmW == qDmzaIqNEC){wkMsWFzyHZ = true;}
      else if(qDmzaIqNEC == uaYuhFePmW){YgLYnUKABX = true;}
      if(RGSgHFRcKS == AYLriXwuiA){xYpNsgfMOX = true;}
      else if(AYLriXwuiA == RGSgHFRcKS){QMYIGsRZwL = true;}
      if(hbaOKMnjEy == JWzAQcpCTW){tYcKUxgPKY = true;}
      else if(JWzAQcpCTW == hbaOKMnjEy){oAIpNjaTOi = true;}
      if(WaftZUrfxd == RwZYAhGzow){OFrtXTYOJM = true;}
      else if(RwZYAhGzow == WaftZUrfxd){LXYlplTsZQ = true;}
      if(uNJAQSatkn == HTzVFwXDtn){LLRhhFdCxw = true;}
      else if(HTzVFwXDtn == uNJAQSatkn){pCdPiyyhct = true;}
      if(tWsaWTzJjU == DGlAPUDliy){lNCNGXHBXZ = true;}
      else if(DGlAPUDliy == tWsaWTzJjU){KwlKAXXULD = true;}
      if(RuLnAqaXHl == SoshjEzlqA){YjniLrfwpY = true;}
      if(MkefWTSayr == RxGmroWduU){HQDCLiHubP = true;}
      if(lsyQEzgEXG == FlIfSLKZIf){SeRNlACemA = true;}
      while(SoshjEzlqA == RuLnAqaXHl){tqlRLrnmSU = true;}
      while(RxGmroWduU == RxGmroWduU){ZXAeUmWsGO = true;}
      while(FlIfSLKZIf == FlIfSLKZIf){lrpTYPlNlR = true;}
      if(eUPpcSaRkB == true){eUPpcSaRkB = false;}
      if(wkMsWFzyHZ == true){wkMsWFzyHZ = false;}
      if(xYpNsgfMOX == true){xYpNsgfMOX = false;}
      if(tYcKUxgPKY == true){tYcKUxgPKY = false;}
      if(OFrtXTYOJM == true){OFrtXTYOJM = false;}
      if(LLRhhFdCxw == true){LLRhhFdCxw = false;}
      if(lNCNGXHBXZ == true){lNCNGXHBXZ = false;}
      if(YjniLrfwpY == true){YjniLrfwpY = false;}
      if(HQDCLiHubP == true){HQDCLiHubP = false;}
      if(SeRNlACemA == true){SeRNlACemA = false;}
      if(LWpjnbWiVp == true){LWpjnbWiVp = false;}
      if(YgLYnUKABX == true){YgLYnUKABX = false;}
      if(QMYIGsRZwL == true){QMYIGsRZwL = false;}
      if(oAIpNjaTOi == true){oAIpNjaTOi = false;}
      if(LXYlplTsZQ == true){LXYlplTsZQ = false;}
      if(pCdPiyyhct == true){pCdPiyyhct = false;}
      if(KwlKAXXULD == true){KwlKAXXULD = false;}
      if(tqlRLrnmSU == true){tqlRLrnmSU = false;}
      if(ZXAeUmWsGO == true){ZXAeUmWsGO = false;}
      if(lrpTYPlNlR == true){lrpTYPlNlR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIYSCCDSIX
{ 
  void VbQlBtdCEu()
  { 
      bool HFNjTlmhOj = false;
      bool WQuFbkOqSY = false;
      bool zaDSQtiZeY = false;
      bool DarLgRAeYo = false;
      bool UJYJMzJNcd = false;
      bool SSJKBgBtTY = false;
      bool CNDpguXiXK = false;
      bool jjRdDpBtFR = false;
      bool kVxAGjRhKA = false;
      bool PFKAlHGibR = false;
      bool aZpSsiBfGL = false;
      bool eHoBmgQCjw = false;
      bool dpYWtdYRqw = false;
      bool jSRnpLfdHW = false;
      bool ikazVIQIMF = false;
      bool pDyfmkBSXO = false;
      bool KinJbLoALb = false;
      bool BluMNrOZBl = false;
      bool NPElFfTlAF = false;
      bool KMFrMzxQXJ = false;
      string KpJdTwWjiD;
      string oMVlaJEVON;
      string nrUQJoGkYf;
      string RjJGYRnxjV;
      string rMmYNBycPu;
      string lwpeiRVsUe;
      string olLClEDONI;
      string VHkrVaFwCI;
      string qcUcsUtdXG;
      string wtcFfFAklJ;
      string yiPGZeKxIH;
      string MYqLnMQhIQ;
      string KYqGMaefMP;
      string aUJsJHMNDO;
      string KwVPsWDQQT;
      string oSbUyZrIty;
      string zdksgrPyCf;
      string zCesFODaNo;
      string WOPsaIrnti;
      string PETEOgKbiB;
      if(KpJdTwWjiD == yiPGZeKxIH){HFNjTlmhOj = true;}
      else if(yiPGZeKxIH == KpJdTwWjiD){aZpSsiBfGL = true;}
      if(oMVlaJEVON == MYqLnMQhIQ){WQuFbkOqSY = true;}
      else if(MYqLnMQhIQ == oMVlaJEVON){eHoBmgQCjw = true;}
      if(nrUQJoGkYf == KYqGMaefMP){zaDSQtiZeY = true;}
      else if(KYqGMaefMP == nrUQJoGkYf){dpYWtdYRqw = true;}
      if(RjJGYRnxjV == aUJsJHMNDO){DarLgRAeYo = true;}
      else if(aUJsJHMNDO == RjJGYRnxjV){jSRnpLfdHW = true;}
      if(rMmYNBycPu == KwVPsWDQQT){UJYJMzJNcd = true;}
      else if(KwVPsWDQQT == rMmYNBycPu){ikazVIQIMF = true;}
      if(lwpeiRVsUe == oSbUyZrIty){SSJKBgBtTY = true;}
      else if(oSbUyZrIty == lwpeiRVsUe){pDyfmkBSXO = true;}
      if(olLClEDONI == zdksgrPyCf){CNDpguXiXK = true;}
      else if(zdksgrPyCf == olLClEDONI){KinJbLoALb = true;}
      if(VHkrVaFwCI == zCesFODaNo){jjRdDpBtFR = true;}
      if(qcUcsUtdXG == WOPsaIrnti){kVxAGjRhKA = true;}
      if(wtcFfFAklJ == PETEOgKbiB){PFKAlHGibR = true;}
      while(zCesFODaNo == VHkrVaFwCI){BluMNrOZBl = true;}
      while(WOPsaIrnti == WOPsaIrnti){NPElFfTlAF = true;}
      while(PETEOgKbiB == PETEOgKbiB){KMFrMzxQXJ = true;}
      if(HFNjTlmhOj == true){HFNjTlmhOj = false;}
      if(WQuFbkOqSY == true){WQuFbkOqSY = false;}
      if(zaDSQtiZeY == true){zaDSQtiZeY = false;}
      if(DarLgRAeYo == true){DarLgRAeYo = false;}
      if(UJYJMzJNcd == true){UJYJMzJNcd = false;}
      if(SSJKBgBtTY == true){SSJKBgBtTY = false;}
      if(CNDpguXiXK == true){CNDpguXiXK = false;}
      if(jjRdDpBtFR == true){jjRdDpBtFR = false;}
      if(kVxAGjRhKA == true){kVxAGjRhKA = false;}
      if(PFKAlHGibR == true){PFKAlHGibR = false;}
      if(aZpSsiBfGL == true){aZpSsiBfGL = false;}
      if(eHoBmgQCjw == true){eHoBmgQCjw = false;}
      if(dpYWtdYRqw == true){dpYWtdYRqw = false;}
      if(jSRnpLfdHW == true){jSRnpLfdHW = false;}
      if(ikazVIQIMF == true){ikazVIQIMF = false;}
      if(pDyfmkBSXO == true){pDyfmkBSXO = false;}
      if(KinJbLoALb == true){KinJbLoALb = false;}
      if(BluMNrOZBl == true){BluMNrOZBl = false;}
      if(NPElFfTlAF == true){NPElFfTlAF = false;}
      if(KMFrMzxQXJ == true){KMFrMzxQXJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYUKDRUARJ
{ 
  void krEOKPdEJB()
  { 
      bool aHuxWuCpkV = false;
      bool ZHfGACdrMm = false;
      bool ewkMjNGUEj = false;
      bool kxsKJCMZrJ = false;
      bool hwootEBZoN = false;
      bool XaKdOdViMJ = false;
      bool nhkBkcOVwy = false;
      bool pEACFiGwRf = false;
      bool MfepLJmPue = false;
      bool fdMiUzKmDR = false;
      bool pedqXSaHXf = false;
      bool WZQgxHCtob = false;
      bool oyaQRMqQhF = false;
      bool XTrzogCmSs = false;
      bool hfqOIGMfkM = false;
      bool xQybcqEMZK = false;
      bool aJZRIDhQqP = false;
      bool FOawsJGLIL = false;
      bool zLfUIHVPWx = false;
      bool boNIRXFZGE = false;
      string PUlpuMbnHq;
      string dgEBCYIjmh;
      string bomGXVZUDj;
      string dbfwEBUtuV;
      string AHgaKEYBZc;
      string LHImnZhfRY;
      string mGjWMBBHxB;
      string EOnQhTILuT;
      string wXuZYWTsId;
      string SobWhsXJNI;
      string DREXYxSqET;
      string RVjybPKKxp;
      string gIzShOlRin;
      string wyymPeTWAb;
      string DcnnMxEdtS;
      string iMLXauSlpK;
      string KBIQWSWxhx;
      string umKVlEUKFj;
      string JIWPEjmaLU;
      string MhgpQCTWQt;
      if(PUlpuMbnHq == DREXYxSqET){aHuxWuCpkV = true;}
      else if(DREXYxSqET == PUlpuMbnHq){pedqXSaHXf = true;}
      if(dgEBCYIjmh == RVjybPKKxp){ZHfGACdrMm = true;}
      else if(RVjybPKKxp == dgEBCYIjmh){WZQgxHCtob = true;}
      if(bomGXVZUDj == gIzShOlRin){ewkMjNGUEj = true;}
      else if(gIzShOlRin == bomGXVZUDj){oyaQRMqQhF = true;}
      if(dbfwEBUtuV == wyymPeTWAb){kxsKJCMZrJ = true;}
      else if(wyymPeTWAb == dbfwEBUtuV){XTrzogCmSs = true;}
      if(AHgaKEYBZc == DcnnMxEdtS){hwootEBZoN = true;}
      else if(DcnnMxEdtS == AHgaKEYBZc){hfqOIGMfkM = true;}
      if(LHImnZhfRY == iMLXauSlpK){XaKdOdViMJ = true;}
      else if(iMLXauSlpK == LHImnZhfRY){xQybcqEMZK = true;}
      if(mGjWMBBHxB == KBIQWSWxhx){nhkBkcOVwy = true;}
      else if(KBIQWSWxhx == mGjWMBBHxB){aJZRIDhQqP = true;}
      if(EOnQhTILuT == umKVlEUKFj){pEACFiGwRf = true;}
      if(wXuZYWTsId == JIWPEjmaLU){MfepLJmPue = true;}
      if(SobWhsXJNI == MhgpQCTWQt){fdMiUzKmDR = true;}
      while(umKVlEUKFj == EOnQhTILuT){FOawsJGLIL = true;}
      while(JIWPEjmaLU == JIWPEjmaLU){zLfUIHVPWx = true;}
      while(MhgpQCTWQt == MhgpQCTWQt){boNIRXFZGE = true;}
      if(aHuxWuCpkV == true){aHuxWuCpkV = false;}
      if(ZHfGACdrMm == true){ZHfGACdrMm = false;}
      if(ewkMjNGUEj == true){ewkMjNGUEj = false;}
      if(kxsKJCMZrJ == true){kxsKJCMZrJ = false;}
      if(hwootEBZoN == true){hwootEBZoN = false;}
      if(XaKdOdViMJ == true){XaKdOdViMJ = false;}
      if(nhkBkcOVwy == true){nhkBkcOVwy = false;}
      if(pEACFiGwRf == true){pEACFiGwRf = false;}
      if(MfepLJmPue == true){MfepLJmPue = false;}
      if(fdMiUzKmDR == true){fdMiUzKmDR = false;}
      if(pedqXSaHXf == true){pedqXSaHXf = false;}
      if(WZQgxHCtob == true){WZQgxHCtob = false;}
      if(oyaQRMqQhF == true){oyaQRMqQhF = false;}
      if(XTrzogCmSs == true){XTrzogCmSs = false;}
      if(hfqOIGMfkM == true){hfqOIGMfkM = false;}
      if(xQybcqEMZK == true){xQybcqEMZK = false;}
      if(aJZRIDhQqP == true){aJZRIDhQqP = false;}
      if(FOawsJGLIL == true){FOawsJGLIL = false;}
      if(zLfUIHVPWx == true){zLfUIHVPWx = false;}
      if(boNIRXFZGE == true){boNIRXFZGE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEUFTSHHDQ
{ 
  void LabmMiMDHb()
  { 
      bool gHZNWOFexX = false;
      bool IoqcMBIFOd = false;
      bool hRjJdMyxEc = false;
      bool JHcXtGxZbK = false;
      bool fhHDRHXnrC = false;
      bool aQnkbOWQjK = false;
      bool QHZTNBLThF = false;
      bool DhcEyzKgqV = false;
      bool nKFCCsSquf = false;
      bool igpRsXHmpQ = false;
      bool uEFlyrmjmc = false;
      bool DpZNVGCXRT = false;
      bool iUXCWWrLKZ = false;
      bool rXpZajFSDK = false;
      bool GhESbsHbwm = false;
      bool UiVVhafCPb = false;
      bool zbZMkfzzlk = false;
      bool BjUGNAPFZc = false;
      bool OPOWFICUrz = false;
      bool DCCbKdIrhw = false;
      string oNFSeSuBoq;
      string XfwFPYIzuS;
      string yVKcXtAIgR;
      string xqtkSsjjdh;
      string BLxuoHNzEt;
      string ftOKwSCbuk;
      string SmUXtglKlV;
      string nXVNRlYPmP;
      string fBDllDbjnz;
      string qHosPNqYAI;
      string VDMiGHYBrJ;
      string tloeEQjhlq;
      string FBVmefhcxD;
      string tzOdtcoUed;
      string eZqdEESKoy;
      string dImJDTgZDZ;
      string ZwEnPtXLja;
      string bODILfKqha;
      string NXmyZkMFaa;
      string wOQFDiVDOK;
      if(oNFSeSuBoq == VDMiGHYBrJ){gHZNWOFexX = true;}
      else if(VDMiGHYBrJ == oNFSeSuBoq){uEFlyrmjmc = true;}
      if(XfwFPYIzuS == tloeEQjhlq){IoqcMBIFOd = true;}
      else if(tloeEQjhlq == XfwFPYIzuS){DpZNVGCXRT = true;}
      if(yVKcXtAIgR == FBVmefhcxD){hRjJdMyxEc = true;}
      else if(FBVmefhcxD == yVKcXtAIgR){iUXCWWrLKZ = true;}
      if(xqtkSsjjdh == tzOdtcoUed){JHcXtGxZbK = true;}
      else if(tzOdtcoUed == xqtkSsjjdh){rXpZajFSDK = true;}
      if(BLxuoHNzEt == eZqdEESKoy){fhHDRHXnrC = true;}
      else if(eZqdEESKoy == BLxuoHNzEt){GhESbsHbwm = true;}
      if(ftOKwSCbuk == dImJDTgZDZ){aQnkbOWQjK = true;}
      else if(dImJDTgZDZ == ftOKwSCbuk){UiVVhafCPb = true;}
      if(SmUXtglKlV == ZwEnPtXLja){QHZTNBLThF = true;}
      else if(ZwEnPtXLja == SmUXtglKlV){zbZMkfzzlk = true;}
      if(nXVNRlYPmP == bODILfKqha){DhcEyzKgqV = true;}
      if(fBDllDbjnz == NXmyZkMFaa){nKFCCsSquf = true;}
      if(qHosPNqYAI == wOQFDiVDOK){igpRsXHmpQ = true;}
      while(bODILfKqha == nXVNRlYPmP){BjUGNAPFZc = true;}
      while(NXmyZkMFaa == NXmyZkMFaa){OPOWFICUrz = true;}
      while(wOQFDiVDOK == wOQFDiVDOK){DCCbKdIrhw = true;}
      if(gHZNWOFexX == true){gHZNWOFexX = false;}
      if(IoqcMBIFOd == true){IoqcMBIFOd = false;}
      if(hRjJdMyxEc == true){hRjJdMyxEc = false;}
      if(JHcXtGxZbK == true){JHcXtGxZbK = false;}
      if(fhHDRHXnrC == true){fhHDRHXnrC = false;}
      if(aQnkbOWQjK == true){aQnkbOWQjK = false;}
      if(QHZTNBLThF == true){QHZTNBLThF = false;}
      if(DhcEyzKgqV == true){DhcEyzKgqV = false;}
      if(nKFCCsSquf == true){nKFCCsSquf = false;}
      if(igpRsXHmpQ == true){igpRsXHmpQ = false;}
      if(uEFlyrmjmc == true){uEFlyrmjmc = false;}
      if(DpZNVGCXRT == true){DpZNVGCXRT = false;}
      if(iUXCWWrLKZ == true){iUXCWWrLKZ = false;}
      if(rXpZajFSDK == true){rXpZajFSDK = false;}
      if(GhESbsHbwm == true){GhESbsHbwm = false;}
      if(UiVVhafCPb == true){UiVVhafCPb = false;}
      if(zbZMkfzzlk == true){zbZMkfzzlk = false;}
      if(BjUGNAPFZc == true){BjUGNAPFZc = false;}
      if(OPOWFICUrz == true){OPOWFICUrz = false;}
      if(DCCbKdIrhw == true){DCCbKdIrhw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWDLBFTZBX
{ 
  void bRaUaArASI()
  { 
      bool VdFjOUZLwZ = false;
      bool nwTugDGruh = false;
      bool MQbiHsewSB = false;
      bool wENJqGlCLt = false;
      bool QcUXErpqiU = false;
      bool ynsRBFCVbV = false;
      bool odsudiiKEZ = false;
      bool RDgBQjuEeP = false;
      bool CnNxDHLuHk = false;
      bool DQZoEmjZtU = false;
      bool IflIDtHqBR = false;
      bool JyqMTBQurV = false;
      bool WmCTWBdrxc = false;
      bool zVKJGVBEsI = false;
      bool ATtpbFYNUC = false;
      bool WohXxUdSlC = false;
      bool QPtXSmngFy = false;
      bool zLBiVDsMrQ = false;
      bool bPWtFKnlMk = false;
      bool qiSprkYVWn = false;
      string aPGcxRusNn;
      string ditRuHqWpq;
      string OXqybEXMNO;
      string ZqehPbmjWV;
      string lIPTScIkra;
      string aNfTHDXHBr;
      string tiezOmDMCT;
      string UHzTFGIXfz;
      string wlUmmLKLZM;
      string DfidaCdPEe;
      string YwiYGTOLNB;
      string uAaBwHOrLD;
      string bqlpPoXUsD;
      string crSBZzDugT;
      string xzyYQDEghS;
      string nkDBDgKsIQ;
      string usSKYCgZbx;
      string DSLrFcsNYM;
      string jqmZOqoQyr;
      string oKmPYEgnzO;
      if(aPGcxRusNn == YwiYGTOLNB){VdFjOUZLwZ = true;}
      else if(YwiYGTOLNB == aPGcxRusNn){IflIDtHqBR = true;}
      if(ditRuHqWpq == uAaBwHOrLD){nwTugDGruh = true;}
      else if(uAaBwHOrLD == ditRuHqWpq){JyqMTBQurV = true;}
      if(OXqybEXMNO == bqlpPoXUsD){MQbiHsewSB = true;}
      else if(bqlpPoXUsD == OXqybEXMNO){WmCTWBdrxc = true;}
      if(ZqehPbmjWV == crSBZzDugT){wENJqGlCLt = true;}
      else if(crSBZzDugT == ZqehPbmjWV){zVKJGVBEsI = true;}
      if(lIPTScIkra == xzyYQDEghS){QcUXErpqiU = true;}
      else if(xzyYQDEghS == lIPTScIkra){ATtpbFYNUC = true;}
      if(aNfTHDXHBr == nkDBDgKsIQ){ynsRBFCVbV = true;}
      else if(nkDBDgKsIQ == aNfTHDXHBr){WohXxUdSlC = true;}
      if(tiezOmDMCT == usSKYCgZbx){odsudiiKEZ = true;}
      else if(usSKYCgZbx == tiezOmDMCT){QPtXSmngFy = true;}
      if(UHzTFGIXfz == DSLrFcsNYM){RDgBQjuEeP = true;}
      if(wlUmmLKLZM == jqmZOqoQyr){CnNxDHLuHk = true;}
      if(DfidaCdPEe == oKmPYEgnzO){DQZoEmjZtU = true;}
      while(DSLrFcsNYM == UHzTFGIXfz){zLBiVDsMrQ = true;}
      while(jqmZOqoQyr == jqmZOqoQyr){bPWtFKnlMk = true;}
      while(oKmPYEgnzO == oKmPYEgnzO){qiSprkYVWn = true;}
      if(VdFjOUZLwZ == true){VdFjOUZLwZ = false;}
      if(nwTugDGruh == true){nwTugDGruh = false;}
      if(MQbiHsewSB == true){MQbiHsewSB = false;}
      if(wENJqGlCLt == true){wENJqGlCLt = false;}
      if(QcUXErpqiU == true){QcUXErpqiU = false;}
      if(ynsRBFCVbV == true){ynsRBFCVbV = false;}
      if(odsudiiKEZ == true){odsudiiKEZ = false;}
      if(RDgBQjuEeP == true){RDgBQjuEeP = false;}
      if(CnNxDHLuHk == true){CnNxDHLuHk = false;}
      if(DQZoEmjZtU == true){DQZoEmjZtU = false;}
      if(IflIDtHqBR == true){IflIDtHqBR = false;}
      if(JyqMTBQurV == true){JyqMTBQurV = false;}
      if(WmCTWBdrxc == true){WmCTWBdrxc = false;}
      if(zVKJGVBEsI == true){zVKJGVBEsI = false;}
      if(ATtpbFYNUC == true){ATtpbFYNUC = false;}
      if(WohXxUdSlC == true){WohXxUdSlC = false;}
      if(QPtXSmngFy == true){QPtXSmngFy = false;}
      if(zLBiVDsMrQ == true){zLBiVDsMrQ = false;}
      if(bPWtFKnlMk == true){bPWtFKnlMk = false;}
      if(qiSprkYVWn == true){qiSprkYVWn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARCHUPTXSS
{ 
  void bzLrPNWGyN()
  { 
      bool AlJrGfsHcG = false;
      bool jZeiJXtldw = false;
      bool XGtrroyVxn = false;
      bool pRyEUxUFZp = false;
      bool VFDFuNBQMh = false;
      bool lOytasqQAR = false;
      bool hWKoPSaaOL = false;
      bool CoMnaRCowd = false;
      bool nhJOCaSDca = false;
      bool FDFHIyuOoc = false;
      bool mZBAewCJTI = false;
      bool pCTVcANumn = false;
      bool AWxmGziEfc = false;
      bool WnATqNfIjF = false;
      bool YIjUkDijdI = false;
      bool jzbAbPcNtf = false;
      bool NxdqlCCAdP = false;
      bool TFLhPqmcCC = false;
      bool PzZWrXMzqb = false;
      bool kRNEqbdrhi = false;
      string ClcRVaMlxU;
      string INnmIeufOe;
      string qxypSbzspP;
      string kyKdBttQBp;
      string zrDbUFRKbF;
      string suBfMEnlys;
      string aTugjJCJlO;
      string jeeYfztVVN;
      string KoRkWoxdQw;
      string FIRHOfwVrK;
      string CHYMUOPcAN;
      string KRQjilCJKt;
      string MXroIbMWJz;
      string CYdKKCPEQH;
      string ZUdClmrhYc;
      string dmKxyeOiEs;
      string CsSALlmFYf;
      string VxsCUrtoDU;
      string idyfVONgLf;
      string mgzWFfBcqz;
      if(ClcRVaMlxU == CHYMUOPcAN){AlJrGfsHcG = true;}
      else if(CHYMUOPcAN == ClcRVaMlxU){mZBAewCJTI = true;}
      if(INnmIeufOe == KRQjilCJKt){jZeiJXtldw = true;}
      else if(KRQjilCJKt == INnmIeufOe){pCTVcANumn = true;}
      if(qxypSbzspP == MXroIbMWJz){XGtrroyVxn = true;}
      else if(MXroIbMWJz == qxypSbzspP){AWxmGziEfc = true;}
      if(kyKdBttQBp == CYdKKCPEQH){pRyEUxUFZp = true;}
      else if(CYdKKCPEQH == kyKdBttQBp){WnATqNfIjF = true;}
      if(zrDbUFRKbF == ZUdClmrhYc){VFDFuNBQMh = true;}
      else if(ZUdClmrhYc == zrDbUFRKbF){YIjUkDijdI = true;}
      if(suBfMEnlys == dmKxyeOiEs){lOytasqQAR = true;}
      else if(dmKxyeOiEs == suBfMEnlys){jzbAbPcNtf = true;}
      if(aTugjJCJlO == CsSALlmFYf){hWKoPSaaOL = true;}
      else if(CsSALlmFYf == aTugjJCJlO){NxdqlCCAdP = true;}
      if(jeeYfztVVN == VxsCUrtoDU){CoMnaRCowd = true;}
      if(KoRkWoxdQw == idyfVONgLf){nhJOCaSDca = true;}
      if(FIRHOfwVrK == mgzWFfBcqz){FDFHIyuOoc = true;}
      while(VxsCUrtoDU == jeeYfztVVN){TFLhPqmcCC = true;}
      while(idyfVONgLf == idyfVONgLf){PzZWrXMzqb = true;}
      while(mgzWFfBcqz == mgzWFfBcqz){kRNEqbdrhi = true;}
      if(AlJrGfsHcG == true){AlJrGfsHcG = false;}
      if(jZeiJXtldw == true){jZeiJXtldw = false;}
      if(XGtrroyVxn == true){XGtrroyVxn = false;}
      if(pRyEUxUFZp == true){pRyEUxUFZp = false;}
      if(VFDFuNBQMh == true){VFDFuNBQMh = false;}
      if(lOytasqQAR == true){lOytasqQAR = false;}
      if(hWKoPSaaOL == true){hWKoPSaaOL = false;}
      if(CoMnaRCowd == true){CoMnaRCowd = false;}
      if(nhJOCaSDca == true){nhJOCaSDca = false;}
      if(FDFHIyuOoc == true){FDFHIyuOoc = false;}
      if(mZBAewCJTI == true){mZBAewCJTI = false;}
      if(pCTVcANumn == true){pCTVcANumn = false;}
      if(AWxmGziEfc == true){AWxmGziEfc = false;}
      if(WnATqNfIjF == true){WnATqNfIjF = false;}
      if(YIjUkDijdI == true){YIjUkDijdI = false;}
      if(jzbAbPcNtf == true){jzbAbPcNtf = false;}
      if(NxdqlCCAdP == true){NxdqlCCAdP = false;}
      if(TFLhPqmcCC == true){TFLhPqmcCC = false;}
      if(PzZWrXMzqb == true){PzZWrXMzqb = false;}
      if(kRNEqbdrhi == true){kRNEqbdrhi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICRNQINEET
{ 
  void uqRURLcLNu()
  { 
      bool OjMoilqWEs = false;
      bool sDUqzkxACk = false;
      bool MCbKDSxnOX = false;
      bool slrIgQwYMg = false;
      bool uJWoTAOVSK = false;
      bool DMJkDMIBkP = false;
      bool oCIgzHKLKi = false;
      bool oYmVoCemqC = false;
      bool DbVDUfbHET = false;
      bool IumwrrBpoM = false;
      bool pCLiVdYnuB = false;
      bool gUKiLNgELT = false;
      bool fDHpatkpdw = false;
      bool BoydMBQlhp = false;
      bool GmLDmmjEjd = false;
      bool LxdVgluUIb = false;
      bool shKyAqWfVK = false;
      bool xtVVMrqDDm = false;
      bool JgFzkELbxZ = false;
      bool GucGxXbNDu = false;
      string VBzLJLziKC;
      string OXcVwEhnuE;
      string ZOyMDgcRrd;
      string lMXTWfXXCy;
      string lPQeQYjYqc;
      string yFZDSGDlIb;
      string hhpgQCAJyQ;
      string gJkxSKyTud;
      string xDZPeflTBQ;
      string bkPaPDYjNO;
      string YZaawnUckI;
      string HiqddeIaBj;
      string PgHhnutJgO;
      string kOFgFWcyTp;
      string LJhsIstkwk;
      string uyhdzqSslA;
      string tKwVWsdJYH;
      string CJHKYGyOYu;
      string AINuSlgbhN;
      string EiMSwAMMVP;
      if(VBzLJLziKC == YZaawnUckI){OjMoilqWEs = true;}
      else if(YZaawnUckI == VBzLJLziKC){pCLiVdYnuB = true;}
      if(OXcVwEhnuE == HiqddeIaBj){sDUqzkxACk = true;}
      else if(HiqddeIaBj == OXcVwEhnuE){gUKiLNgELT = true;}
      if(ZOyMDgcRrd == PgHhnutJgO){MCbKDSxnOX = true;}
      else if(PgHhnutJgO == ZOyMDgcRrd){fDHpatkpdw = true;}
      if(lMXTWfXXCy == kOFgFWcyTp){slrIgQwYMg = true;}
      else if(kOFgFWcyTp == lMXTWfXXCy){BoydMBQlhp = true;}
      if(lPQeQYjYqc == LJhsIstkwk){uJWoTAOVSK = true;}
      else if(LJhsIstkwk == lPQeQYjYqc){GmLDmmjEjd = true;}
      if(yFZDSGDlIb == uyhdzqSslA){DMJkDMIBkP = true;}
      else if(uyhdzqSslA == yFZDSGDlIb){LxdVgluUIb = true;}
      if(hhpgQCAJyQ == tKwVWsdJYH){oCIgzHKLKi = true;}
      else if(tKwVWsdJYH == hhpgQCAJyQ){shKyAqWfVK = true;}
      if(gJkxSKyTud == CJHKYGyOYu){oYmVoCemqC = true;}
      if(xDZPeflTBQ == AINuSlgbhN){DbVDUfbHET = true;}
      if(bkPaPDYjNO == EiMSwAMMVP){IumwrrBpoM = true;}
      while(CJHKYGyOYu == gJkxSKyTud){xtVVMrqDDm = true;}
      while(AINuSlgbhN == AINuSlgbhN){JgFzkELbxZ = true;}
      while(EiMSwAMMVP == EiMSwAMMVP){GucGxXbNDu = true;}
      if(OjMoilqWEs == true){OjMoilqWEs = false;}
      if(sDUqzkxACk == true){sDUqzkxACk = false;}
      if(MCbKDSxnOX == true){MCbKDSxnOX = false;}
      if(slrIgQwYMg == true){slrIgQwYMg = false;}
      if(uJWoTAOVSK == true){uJWoTAOVSK = false;}
      if(DMJkDMIBkP == true){DMJkDMIBkP = false;}
      if(oCIgzHKLKi == true){oCIgzHKLKi = false;}
      if(oYmVoCemqC == true){oYmVoCemqC = false;}
      if(DbVDUfbHET == true){DbVDUfbHET = false;}
      if(IumwrrBpoM == true){IumwrrBpoM = false;}
      if(pCLiVdYnuB == true){pCLiVdYnuB = false;}
      if(gUKiLNgELT == true){gUKiLNgELT = false;}
      if(fDHpatkpdw == true){fDHpatkpdw = false;}
      if(BoydMBQlhp == true){BoydMBQlhp = false;}
      if(GmLDmmjEjd == true){GmLDmmjEjd = false;}
      if(LxdVgluUIb == true){LxdVgluUIb = false;}
      if(shKyAqWfVK == true){shKyAqWfVK = false;}
      if(xtVVMrqDDm == true){xtVVMrqDDm = false;}
      if(JgFzkELbxZ == true){JgFzkELbxZ = false;}
      if(GucGxXbNDu == true){GucGxXbNDu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFCXLLVTCJ
{ 
  void BBMEqMdqQf()
  { 
      bool apruLkkfgc = false;
      bool CaEFEQtbhh = false;
      bool lqDtnkWcnP = false;
      bool bJYIqCiRlE = false;
      bool tAulPpqRit = false;
      bool UASkPimxGa = false;
      bool OIrQAsCwNB = false;
      bool gcpdnluRey = false;
      bool sFtstbpnrI = false;
      bool PlLLolIdkV = false;
      bool muDgNrKnwd = false;
      bool nURIgJNyWY = false;
      bool COEFluRenB = false;
      bool dQfJKyBMfB = false;
      bool RCqOTuTCdf = false;
      bool XJHMTYqxuR = false;
      bool aeAtzWnIxi = false;
      bool HBRUGAXokq = false;
      bool aOBIdTITpl = false;
      bool HDQNalCwOx = false;
      string bWOuwWDHMM;
      string yLYtYCxROq;
      string qGLKaaYePg;
      string RSITSLbRMj;
      string wANJWzxUyb;
      string EZwooVKDUU;
      string xXrfteCEaN;
      string aeEdtqrCnb;
      string dEgncrVTex;
      string BXxqlXHhOq;
      string wssjBYUStx;
      string cHPrpsqECC;
      string IiYdMCgNqW;
      string iKnxekLwlD;
      string WDYgTsIFAs;
      string gDeLhMTOXy;
      string rHaXORSSMF;
      string guRzeFKrJS;
      string sbMypffbOR;
      string RwXnLPcASB;
      if(bWOuwWDHMM == wssjBYUStx){apruLkkfgc = true;}
      else if(wssjBYUStx == bWOuwWDHMM){muDgNrKnwd = true;}
      if(yLYtYCxROq == cHPrpsqECC){CaEFEQtbhh = true;}
      else if(cHPrpsqECC == yLYtYCxROq){nURIgJNyWY = true;}
      if(qGLKaaYePg == IiYdMCgNqW){lqDtnkWcnP = true;}
      else if(IiYdMCgNqW == qGLKaaYePg){COEFluRenB = true;}
      if(RSITSLbRMj == iKnxekLwlD){bJYIqCiRlE = true;}
      else if(iKnxekLwlD == RSITSLbRMj){dQfJKyBMfB = true;}
      if(wANJWzxUyb == WDYgTsIFAs){tAulPpqRit = true;}
      else if(WDYgTsIFAs == wANJWzxUyb){RCqOTuTCdf = true;}
      if(EZwooVKDUU == gDeLhMTOXy){UASkPimxGa = true;}
      else if(gDeLhMTOXy == EZwooVKDUU){XJHMTYqxuR = true;}
      if(xXrfteCEaN == rHaXORSSMF){OIrQAsCwNB = true;}
      else if(rHaXORSSMF == xXrfteCEaN){aeAtzWnIxi = true;}
      if(aeEdtqrCnb == guRzeFKrJS){gcpdnluRey = true;}
      if(dEgncrVTex == sbMypffbOR){sFtstbpnrI = true;}
      if(BXxqlXHhOq == RwXnLPcASB){PlLLolIdkV = true;}
      while(guRzeFKrJS == aeEdtqrCnb){HBRUGAXokq = true;}
      while(sbMypffbOR == sbMypffbOR){aOBIdTITpl = true;}
      while(RwXnLPcASB == RwXnLPcASB){HDQNalCwOx = true;}
      if(apruLkkfgc == true){apruLkkfgc = false;}
      if(CaEFEQtbhh == true){CaEFEQtbhh = false;}
      if(lqDtnkWcnP == true){lqDtnkWcnP = false;}
      if(bJYIqCiRlE == true){bJYIqCiRlE = false;}
      if(tAulPpqRit == true){tAulPpqRit = false;}
      if(UASkPimxGa == true){UASkPimxGa = false;}
      if(OIrQAsCwNB == true){OIrQAsCwNB = false;}
      if(gcpdnluRey == true){gcpdnluRey = false;}
      if(sFtstbpnrI == true){sFtstbpnrI = false;}
      if(PlLLolIdkV == true){PlLLolIdkV = false;}
      if(muDgNrKnwd == true){muDgNrKnwd = false;}
      if(nURIgJNyWY == true){nURIgJNyWY = false;}
      if(COEFluRenB == true){COEFluRenB = false;}
      if(dQfJKyBMfB == true){dQfJKyBMfB = false;}
      if(RCqOTuTCdf == true){RCqOTuTCdf = false;}
      if(XJHMTYqxuR == true){XJHMTYqxuR = false;}
      if(aeAtzWnIxi == true){aeAtzWnIxi = false;}
      if(HBRUGAXokq == true){HBRUGAXokq = false;}
      if(aOBIdTITpl == true){aOBIdTITpl = false;}
      if(HDQNalCwOx == true){HDQNalCwOx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CXJRVPCOMG
{ 
  void cKfciFPSLL()
  { 
      bool epOCsoWfZi = false;
      bool ljbFmPjaAG = false;
      bool qrKEOubDbA = false;
      bool XsUUMIBDEU = false;
      bool JUKauHSpcz = false;
      bool lbQXEmfKmx = false;
      bool MTDYLsOHsd = false;
      bool NgVfwWgiIH = false;
      bool ckZbOucxPZ = false;
      bool cqPHHpQlPC = false;
      bool rLxykEGjbh = false;
      bool FwBfUbsbJP = false;
      bool QRqSBVROYG = false;
      bool FuTGPQmbqK = false;
      bool orUhTgpjle = false;
      bool wobzkZTexO = false;
      bool mrLUbKbtQD = false;
      bool nQjzaXwJyT = false;
      bool fhbsJPSTUo = false;
      bool xIebWxfzFJ = false;
      string dYJaoMRkCa;
      string epTQLobIfs;
      string UcyjubuGNV;
      string ZqtYGsbuDg;
      string pjrhBgxIOL;
      string cIGjuBaYeM;
      string RKXgBmwuKR;
      string NfEyCjjPiO;
      string dlqBrQjJcF;
      string SCPqPfMLgN;
      string jCyxywEHgK;
      string QKpPheSVnj;
      string DmRFzLPNiW;
      string XYhUebntCw;
      string MbbRnHLzIj;
      string MpXxKxjrxm;
      string fpYKmrcUkG;
      string qXTqXaKzQq;
      string zPFyJgAkKg;
      string quwPPWDRew;
      if(dYJaoMRkCa == jCyxywEHgK){epOCsoWfZi = true;}
      else if(jCyxywEHgK == dYJaoMRkCa){rLxykEGjbh = true;}
      if(epTQLobIfs == QKpPheSVnj){ljbFmPjaAG = true;}
      else if(QKpPheSVnj == epTQLobIfs){FwBfUbsbJP = true;}
      if(UcyjubuGNV == DmRFzLPNiW){qrKEOubDbA = true;}
      else if(DmRFzLPNiW == UcyjubuGNV){QRqSBVROYG = true;}
      if(ZqtYGsbuDg == XYhUebntCw){XsUUMIBDEU = true;}
      else if(XYhUebntCw == ZqtYGsbuDg){FuTGPQmbqK = true;}
      if(pjrhBgxIOL == MbbRnHLzIj){JUKauHSpcz = true;}
      else if(MbbRnHLzIj == pjrhBgxIOL){orUhTgpjle = true;}
      if(cIGjuBaYeM == MpXxKxjrxm){lbQXEmfKmx = true;}
      else if(MpXxKxjrxm == cIGjuBaYeM){wobzkZTexO = true;}
      if(RKXgBmwuKR == fpYKmrcUkG){MTDYLsOHsd = true;}
      else if(fpYKmrcUkG == RKXgBmwuKR){mrLUbKbtQD = true;}
      if(NfEyCjjPiO == qXTqXaKzQq){NgVfwWgiIH = true;}
      if(dlqBrQjJcF == zPFyJgAkKg){ckZbOucxPZ = true;}
      if(SCPqPfMLgN == quwPPWDRew){cqPHHpQlPC = true;}
      while(qXTqXaKzQq == NfEyCjjPiO){nQjzaXwJyT = true;}
      while(zPFyJgAkKg == zPFyJgAkKg){fhbsJPSTUo = true;}
      while(quwPPWDRew == quwPPWDRew){xIebWxfzFJ = true;}
      if(epOCsoWfZi == true){epOCsoWfZi = false;}
      if(ljbFmPjaAG == true){ljbFmPjaAG = false;}
      if(qrKEOubDbA == true){qrKEOubDbA = false;}
      if(XsUUMIBDEU == true){XsUUMIBDEU = false;}
      if(JUKauHSpcz == true){JUKauHSpcz = false;}
      if(lbQXEmfKmx == true){lbQXEmfKmx = false;}
      if(MTDYLsOHsd == true){MTDYLsOHsd = false;}
      if(NgVfwWgiIH == true){NgVfwWgiIH = false;}
      if(ckZbOucxPZ == true){ckZbOucxPZ = false;}
      if(cqPHHpQlPC == true){cqPHHpQlPC = false;}
      if(rLxykEGjbh == true){rLxykEGjbh = false;}
      if(FwBfUbsbJP == true){FwBfUbsbJP = false;}
      if(QRqSBVROYG == true){QRqSBVROYG = false;}
      if(FuTGPQmbqK == true){FuTGPQmbqK = false;}
      if(orUhTgpjle == true){orUhTgpjle = false;}
      if(wobzkZTexO == true){wobzkZTexO = false;}
      if(mrLUbKbtQD == true){mrLUbKbtQD = false;}
      if(nQjzaXwJyT == true){nQjzaXwJyT = false;}
      if(fhbsJPSTUo == true){fhbsJPSTUo = false;}
      if(xIebWxfzFJ == true){xIebWxfzFJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTSQMXQCPI
{ 
  void sfoieSRUOG()
  { 
      bool SEDAzJDmCG = false;
      bool anYJEAWTsd = false;
      bool QlAVwthjad = false;
      bool KbBhWWJAYN = false;
      bool BkkFVuNLjK = false;
      bool rQFSXgDhDE = false;
      bool aSLXuylplh = false;
      bool qVtfcfAuzB = false;
      bool fVAQltWhKp = false;
      bool SaxTlhYMJW = false;
      bool IXYBSVVZpq = false;
      bool fHhCXFSulB = false;
      bool bDewOPYZsu = false;
      bool HmlcrIwyxQ = false;
      bool XxrSJLstwg = false;
      bool OdaHtErcmC = false;
      bool wwfujrVFJP = false;
      bool IUxVdeLMmD = false;
      bool WddLfdMdhm = false;
      bool PTKuTbQxhR = false;
      string KdUBSrtbSm;
      string YrgyHhVnuf;
      string CsJJqcuUsn;
      string OZlIgWByXs;
      string KCNzWzpOSD;
      string TVzVORTLKo;
      string wZheXyGYQk;
      string gWPBVAfKlr;
      string mfBpUraPtP;
      string CpnhwkTiaY;
      string rRxgVwFxAO;
      string kJYRCPXrJf;
      string XpdBhqigFj;
      string fwiMzViTTX;
      string mcOedsQVff;
      string MbYuBCmwye;
      string NXrQhoZMSf;
      string gDYlruayXo;
      string aMBYWEXnLx;
      string ilVnKOjyxo;
      if(KdUBSrtbSm == rRxgVwFxAO){SEDAzJDmCG = true;}
      else if(rRxgVwFxAO == KdUBSrtbSm){IXYBSVVZpq = true;}
      if(YrgyHhVnuf == kJYRCPXrJf){anYJEAWTsd = true;}
      else if(kJYRCPXrJf == YrgyHhVnuf){fHhCXFSulB = true;}
      if(CsJJqcuUsn == XpdBhqigFj){QlAVwthjad = true;}
      else if(XpdBhqigFj == CsJJqcuUsn){bDewOPYZsu = true;}
      if(OZlIgWByXs == fwiMzViTTX){KbBhWWJAYN = true;}
      else if(fwiMzViTTX == OZlIgWByXs){HmlcrIwyxQ = true;}
      if(KCNzWzpOSD == mcOedsQVff){BkkFVuNLjK = true;}
      else if(mcOedsQVff == KCNzWzpOSD){XxrSJLstwg = true;}
      if(TVzVORTLKo == MbYuBCmwye){rQFSXgDhDE = true;}
      else if(MbYuBCmwye == TVzVORTLKo){OdaHtErcmC = true;}
      if(wZheXyGYQk == NXrQhoZMSf){aSLXuylplh = true;}
      else if(NXrQhoZMSf == wZheXyGYQk){wwfujrVFJP = true;}
      if(gWPBVAfKlr == gDYlruayXo){qVtfcfAuzB = true;}
      if(mfBpUraPtP == aMBYWEXnLx){fVAQltWhKp = true;}
      if(CpnhwkTiaY == ilVnKOjyxo){SaxTlhYMJW = true;}
      while(gDYlruayXo == gWPBVAfKlr){IUxVdeLMmD = true;}
      while(aMBYWEXnLx == aMBYWEXnLx){WddLfdMdhm = true;}
      while(ilVnKOjyxo == ilVnKOjyxo){PTKuTbQxhR = true;}
      if(SEDAzJDmCG == true){SEDAzJDmCG = false;}
      if(anYJEAWTsd == true){anYJEAWTsd = false;}
      if(QlAVwthjad == true){QlAVwthjad = false;}
      if(KbBhWWJAYN == true){KbBhWWJAYN = false;}
      if(BkkFVuNLjK == true){BkkFVuNLjK = false;}
      if(rQFSXgDhDE == true){rQFSXgDhDE = false;}
      if(aSLXuylplh == true){aSLXuylplh = false;}
      if(qVtfcfAuzB == true){qVtfcfAuzB = false;}
      if(fVAQltWhKp == true){fVAQltWhKp = false;}
      if(SaxTlhYMJW == true){SaxTlhYMJW = false;}
      if(IXYBSVVZpq == true){IXYBSVVZpq = false;}
      if(fHhCXFSulB == true){fHhCXFSulB = false;}
      if(bDewOPYZsu == true){bDewOPYZsu = false;}
      if(HmlcrIwyxQ == true){HmlcrIwyxQ = false;}
      if(XxrSJLstwg == true){XxrSJLstwg = false;}
      if(OdaHtErcmC == true){OdaHtErcmC = false;}
      if(wwfujrVFJP == true){wwfujrVFJP = false;}
      if(IUxVdeLMmD == true){IUxVdeLMmD = false;}
      if(WddLfdMdhm == true){WddLfdMdhm = false;}
      if(PTKuTbQxhR == true){PTKuTbQxhR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNREYRADXW
{ 
  void nEbGnWoKgf()
  { 
      bool BNOVzNMOpb = false;
      bool HWyDiwxDwz = false;
      bool wjGikhEXBI = false;
      bool hxdWqqNgAQ = false;
      bool NLWdOKEqEC = false;
      bool omcpFRHfjR = false;
      bool JoMgtKsbLq = false;
      bool iQDfkkNcTZ = false;
      bool dMSyTtTmRZ = false;
      bool jhwiHXyoiD = false;
      bool RceNTYjwFU = false;
      bool EdLKnwWONz = false;
      bool pFKlGATUYM = false;
      bool lXsQIAhEet = false;
      bool KWhwVFVluK = false;
      bool BjajMLRsHS = false;
      bool EOXrhfkuCm = false;
      bool ORjTnTWNQA = false;
      bool ehZNLCwJDw = false;
      bool inxLouzpOo = false;
      string cFrHrFgWHB;
      string DbAIuNHzkX;
      string HlswxzyJnm;
      string rCibaHojaE;
      string buIbUtzCcr;
      string sPUOlpMuJs;
      string HXiTJArYhm;
      string YWYguLdQaD;
      string zugutchUoj;
      string usahwDMnST;
      string CZUoTVpmSZ;
      string LuTGsLqmYg;
      string SXixrewqjq;
      string zoyGBZaqbY;
      string ltBPYzZTok;
      string MYOkBdqXwn;
      string YzDbZWxMFT;
      string kzLAuYWTYs;
      string FbCzeaZMFW;
      string hDtnzlqZoB;
      if(cFrHrFgWHB == CZUoTVpmSZ){BNOVzNMOpb = true;}
      else if(CZUoTVpmSZ == cFrHrFgWHB){RceNTYjwFU = true;}
      if(DbAIuNHzkX == LuTGsLqmYg){HWyDiwxDwz = true;}
      else if(LuTGsLqmYg == DbAIuNHzkX){EdLKnwWONz = true;}
      if(HlswxzyJnm == SXixrewqjq){wjGikhEXBI = true;}
      else if(SXixrewqjq == HlswxzyJnm){pFKlGATUYM = true;}
      if(rCibaHojaE == zoyGBZaqbY){hxdWqqNgAQ = true;}
      else if(zoyGBZaqbY == rCibaHojaE){lXsQIAhEet = true;}
      if(buIbUtzCcr == ltBPYzZTok){NLWdOKEqEC = true;}
      else if(ltBPYzZTok == buIbUtzCcr){KWhwVFVluK = true;}
      if(sPUOlpMuJs == MYOkBdqXwn){omcpFRHfjR = true;}
      else if(MYOkBdqXwn == sPUOlpMuJs){BjajMLRsHS = true;}
      if(HXiTJArYhm == YzDbZWxMFT){JoMgtKsbLq = true;}
      else if(YzDbZWxMFT == HXiTJArYhm){EOXrhfkuCm = true;}
      if(YWYguLdQaD == kzLAuYWTYs){iQDfkkNcTZ = true;}
      if(zugutchUoj == FbCzeaZMFW){dMSyTtTmRZ = true;}
      if(usahwDMnST == hDtnzlqZoB){jhwiHXyoiD = true;}
      while(kzLAuYWTYs == YWYguLdQaD){ORjTnTWNQA = true;}
      while(FbCzeaZMFW == FbCzeaZMFW){ehZNLCwJDw = true;}
      while(hDtnzlqZoB == hDtnzlqZoB){inxLouzpOo = true;}
      if(BNOVzNMOpb == true){BNOVzNMOpb = false;}
      if(HWyDiwxDwz == true){HWyDiwxDwz = false;}
      if(wjGikhEXBI == true){wjGikhEXBI = false;}
      if(hxdWqqNgAQ == true){hxdWqqNgAQ = false;}
      if(NLWdOKEqEC == true){NLWdOKEqEC = false;}
      if(omcpFRHfjR == true){omcpFRHfjR = false;}
      if(JoMgtKsbLq == true){JoMgtKsbLq = false;}
      if(iQDfkkNcTZ == true){iQDfkkNcTZ = false;}
      if(dMSyTtTmRZ == true){dMSyTtTmRZ = false;}
      if(jhwiHXyoiD == true){jhwiHXyoiD = false;}
      if(RceNTYjwFU == true){RceNTYjwFU = false;}
      if(EdLKnwWONz == true){EdLKnwWONz = false;}
      if(pFKlGATUYM == true){pFKlGATUYM = false;}
      if(lXsQIAhEet == true){lXsQIAhEet = false;}
      if(KWhwVFVluK == true){KWhwVFVluK = false;}
      if(BjajMLRsHS == true){BjajMLRsHS = false;}
      if(EOXrhfkuCm == true){EOXrhfkuCm = false;}
      if(ORjTnTWNQA == true){ORjTnTWNQA = false;}
      if(ehZNLCwJDw == true){ehZNLCwJDw = false;}
      if(inxLouzpOo == true){inxLouzpOo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEIOGLTFKE
{ 
  void JdHEFkNkBD()
  { 
      bool DbNxbFwhZJ = false;
      bool wiuiFTslwn = false;
      bool aPFPyEjWhJ = false;
      bool WhAEueLCzc = false;
      bool eUserrOMFK = false;
      bool nZOXhmWxyW = false;
      bool UZzPmOhpma = false;
      bool HplTJFWZXG = false;
      bool oXQXVxSbWI = false;
      bool HOEbIEVcqd = false;
      bool JYZeCxmuOc = false;
      bool PwZrhxJbtp = false;
      bool uGTeSslJKE = false;
      bool ithtwQykUX = false;
      bool JWMsrLoMtL = false;
      bool uthBhDEtLJ = false;
      bool KcjKsVNeuQ = false;
      bool yXGVfYsZlH = false;
      bool DZPzJoLgLs = false;
      bool MDYKMglCAV = false;
      string sIDHmWIzhG;
      string rnBblksLlP;
      string wsRtOiGDfp;
      string ufJMNwIxWr;
      string zETwMGaZIS;
      string hEZQNzpJsE;
      string QETqKMdnOp;
      string bwntPqYVgH;
      string IfuNIqFryN;
      string FzERbukckz;
      string blLRpkPfAV;
      string aTbkwjJFiT;
      string HkpBkcrVSU;
      string GwkgfWUcXW;
      string bYqcmlWSVq;
      string lesRrpwJgM;
      string ssNfPditFY;
      string PfhLqhsMNy;
      string GZzaibCSoo;
      string aKuLdhLLMJ;
      if(sIDHmWIzhG == blLRpkPfAV){DbNxbFwhZJ = true;}
      else if(blLRpkPfAV == sIDHmWIzhG){JYZeCxmuOc = true;}
      if(rnBblksLlP == aTbkwjJFiT){wiuiFTslwn = true;}
      else if(aTbkwjJFiT == rnBblksLlP){PwZrhxJbtp = true;}
      if(wsRtOiGDfp == HkpBkcrVSU){aPFPyEjWhJ = true;}
      else if(HkpBkcrVSU == wsRtOiGDfp){uGTeSslJKE = true;}
      if(ufJMNwIxWr == GwkgfWUcXW){WhAEueLCzc = true;}
      else if(GwkgfWUcXW == ufJMNwIxWr){ithtwQykUX = true;}
      if(zETwMGaZIS == bYqcmlWSVq){eUserrOMFK = true;}
      else if(bYqcmlWSVq == zETwMGaZIS){JWMsrLoMtL = true;}
      if(hEZQNzpJsE == lesRrpwJgM){nZOXhmWxyW = true;}
      else if(lesRrpwJgM == hEZQNzpJsE){uthBhDEtLJ = true;}
      if(QETqKMdnOp == ssNfPditFY){UZzPmOhpma = true;}
      else if(ssNfPditFY == QETqKMdnOp){KcjKsVNeuQ = true;}
      if(bwntPqYVgH == PfhLqhsMNy){HplTJFWZXG = true;}
      if(IfuNIqFryN == GZzaibCSoo){oXQXVxSbWI = true;}
      if(FzERbukckz == aKuLdhLLMJ){HOEbIEVcqd = true;}
      while(PfhLqhsMNy == bwntPqYVgH){yXGVfYsZlH = true;}
      while(GZzaibCSoo == GZzaibCSoo){DZPzJoLgLs = true;}
      while(aKuLdhLLMJ == aKuLdhLLMJ){MDYKMglCAV = true;}
      if(DbNxbFwhZJ == true){DbNxbFwhZJ = false;}
      if(wiuiFTslwn == true){wiuiFTslwn = false;}
      if(aPFPyEjWhJ == true){aPFPyEjWhJ = false;}
      if(WhAEueLCzc == true){WhAEueLCzc = false;}
      if(eUserrOMFK == true){eUserrOMFK = false;}
      if(nZOXhmWxyW == true){nZOXhmWxyW = false;}
      if(UZzPmOhpma == true){UZzPmOhpma = false;}
      if(HplTJFWZXG == true){HplTJFWZXG = false;}
      if(oXQXVxSbWI == true){oXQXVxSbWI = false;}
      if(HOEbIEVcqd == true){HOEbIEVcqd = false;}
      if(JYZeCxmuOc == true){JYZeCxmuOc = false;}
      if(PwZrhxJbtp == true){PwZrhxJbtp = false;}
      if(uGTeSslJKE == true){uGTeSslJKE = false;}
      if(ithtwQykUX == true){ithtwQykUX = false;}
      if(JWMsrLoMtL == true){JWMsrLoMtL = false;}
      if(uthBhDEtLJ == true){uthBhDEtLJ = false;}
      if(KcjKsVNeuQ == true){KcjKsVNeuQ = false;}
      if(yXGVfYsZlH == true){yXGVfYsZlH = false;}
      if(DZPzJoLgLs == true){DZPzJoLgLs = false;}
      if(MDYKMglCAV == true){MDYKMglCAV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEDTHXZSWC
{ 
  void WwxsPIztYP()
  { 
      bool GRmlpLGkQA = false;
      bool lpTCHgdbrP = false;
      bool tnSmdGFOFW = false;
      bool BtZTsINomo = false;
      bool trJydPRhpV = false;
      bool YzhygSyzHi = false;
      bool GrftzrPAIy = false;
      bool TnoCUBeTJN = false;
      bool oWXiyBLbla = false;
      bool JOgDiBMOzk = false;
      bool zRYqBjKfcf = false;
      bool neostiTxwy = false;
      bool fnNgnFHkSS = false;
      bool oPUXOXxggN = false;
      bool pfzGmeYmJA = false;
      bool hOSAFLDrCw = false;
      bool cZMJpXJQeV = false;
      bool kmPhHzoGtJ = false;
      bool fTaSkZwTSC = false;
      bool TFdkkPSoQO = false;
      string OVdLKaobwt;
      string KoIBonWjXr;
      string GEBOQITDKr;
      string DCmcHTuNtj;
      string NbrNwxbGsk;
      string hsEYOJTOuC;
      string HlQDqHCftV;
      string rJpndeMnSS;
      string gNJYJKxNNx;
      string AgSrbbKnWn;
      string uwLXsYCQtj;
      string xewbUtbrsg;
      string KnRwULqyLB;
      string TYQdXkBlfk;
      string HgSdAUjqWh;
      string AStpdHdPCh;
      string hEFsPYOSEj;
      string roLIYcUnuA;
      string aAacBAdazQ;
      string GkjxDCbZNb;
      if(OVdLKaobwt == uwLXsYCQtj){GRmlpLGkQA = true;}
      else if(uwLXsYCQtj == OVdLKaobwt){zRYqBjKfcf = true;}
      if(KoIBonWjXr == xewbUtbrsg){lpTCHgdbrP = true;}
      else if(xewbUtbrsg == KoIBonWjXr){neostiTxwy = true;}
      if(GEBOQITDKr == KnRwULqyLB){tnSmdGFOFW = true;}
      else if(KnRwULqyLB == GEBOQITDKr){fnNgnFHkSS = true;}
      if(DCmcHTuNtj == TYQdXkBlfk){BtZTsINomo = true;}
      else if(TYQdXkBlfk == DCmcHTuNtj){oPUXOXxggN = true;}
      if(NbrNwxbGsk == HgSdAUjqWh){trJydPRhpV = true;}
      else if(HgSdAUjqWh == NbrNwxbGsk){pfzGmeYmJA = true;}
      if(hsEYOJTOuC == AStpdHdPCh){YzhygSyzHi = true;}
      else if(AStpdHdPCh == hsEYOJTOuC){hOSAFLDrCw = true;}
      if(HlQDqHCftV == hEFsPYOSEj){GrftzrPAIy = true;}
      else if(hEFsPYOSEj == HlQDqHCftV){cZMJpXJQeV = true;}
      if(rJpndeMnSS == roLIYcUnuA){TnoCUBeTJN = true;}
      if(gNJYJKxNNx == aAacBAdazQ){oWXiyBLbla = true;}
      if(AgSrbbKnWn == GkjxDCbZNb){JOgDiBMOzk = true;}
      while(roLIYcUnuA == rJpndeMnSS){kmPhHzoGtJ = true;}
      while(aAacBAdazQ == aAacBAdazQ){fTaSkZwTSC = true;}
      while(GkjxDCbZNb == GkjxDCbZNb){TFdkkPSoQO = true;}
      if(GRmlpLGkQA == true){GRmlpLGkQA = false;}
      if(lpTCHgdbrP == true){lpTCHgdbrP = false;}
      if(tnSmdGFOFW == true){tnSmdGFOFW = false;}
      if(BtZTsINomo == true){BtZTsINomo = false;}
      if(trJydPRhpV == true){trJydPRhpV = false;}
      if(YzhygSyzHi == true){YzhygSyzHi = false;}
      if(GrftzrPAIy == true){GrftzrPAIy = false;}
      if(TnoCUBeTJN == true){TnoCUBeTJN = false;}
      if(oWXiyBLbla == true){oWXiyBLbla = false;}
      if(JOgDiBMOzk == true){JOgDiBMOzk = false;}
      if(zRYqBjKfcf == true){zRYqBjKfcf = false;}
      if(neostiTxwy == true){neostiTxwy = false;}
      if(fnNgnFHkSS == true){fnNgnFHkSS = false;}
      if(oPUXOXxggN == true){oPUXOXxggN = false;}
      if(pfzGmeYmJA == true){pfzGmeYmJA = false;}
      if(hOSAFLDrCw == true){hOSAFLDrCw = false;}
      if(cZMJpXJQeV == true){cZMJpXJQeV = false;}
      if(kmPhHzoGtJ == true){kmPhHzoGtJ = false;}
      if(fTaSkZwTSC == true){fTaSkZwTSC = false;}
      if(TFdkkPSoQO == true){TFdkkPSoQO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYNANZGCMN
{ 
  void BorFwEXcGM()
  { 
      bool huCSZTFtrs = false;
      bool BggzmKNdFG = false;
      bool sWXniLGqkb = false;
      bool kzhUIdZynf = false;
      bool PQEWORkToF = false;
      bool YFbozLXNjN = false;
      bool NNIQHBzMqJ = false;
      bool jOoZqbRAZQ = false;
      bool amBfCeXsVx = false;
      bool FLOZRBHnOM = false;
      bool SYcfUKPBxW = false;
      bool tWnSmaMcNb = false;
      bool dGqsEXAPHp = false;
      bool UdkMxCKVLr = false;
      bool OVuyDhXumq = false;
      bool oeZmiMhibw = false;
      bool JAsHCPlaVk = false;
      bool QpRVMHKrpV = false;
      bool AEcQBoDydk = false;
      bool TbtOhObmum = false;
      string IAtIlujJeX;
      string BNnoPSGRWh;
      string iphlGYlDow;
      string ZPHtYtJLGG;
      string KDimwGEUGe;
      string TJbVBRSHCM;
      string JgThykFsQU;
      string JuLQXeHtpz;
      string URwKcQnksG;
      string aBJswdjAoL;
      string BKEkUYxLyW;
      string KYRCrrjJFh;
      string xTAJtIkSTs;
      string uGEdxJMKoD;
      string SbmWwCiHAE;
      string sZuHOhKtqM;
      string nerFbDTmEh;
      string eZTBOUgcNq;
      string YcROzUKxPP;
      string zSScPmjgur;
      if(IAtIlujJeX == BKEkUYxLyW){huCSZTFtrs = true;}
      else if(BKEkUYxLyW == IAtIlujJeX){SYcfUKPBxW = true;}
      if(BNnoPSGRWh == KYRCrrjJFh){BggzmKNdFG = true;}
      else if(KYRCrrjJFh == BNnoPSGRWh){tWnSmaMcNb = true;}
      if(iphlGYlDow == xTAJtIkSTs){sWXniLGqkb = true;}
      else if(xTAJtIkSTs == iphlGYlDow){dGqsEXAPHp = true;}
      if(ZPHtYtJLGG == uGEdxJMKoD){kzhUIdZynf = true;}
      else if(uGEdxJMKoD == ZPHtYtJLGG){UdkMxCKVLr = true;}
      if(KDimwGEUGe == SbmWwCiHAE){PQEWORkToF = true;}
      else if(SbmWwCiHAE == KDimwGEUGe){OVuyDhXumq = true;}
      if(TJbVBRSHCM == sZuHOhKtqM){YFbozLXNjN = true;}
      else if(sZuHOhKtqM == TJbVBRSHCM){oeZmiMhibw = true;}
      if(JgThykFsQU == nerFbDTmEh){NNIQHBzMqJ = true;}
      else if(nerFbDTmEh == JgThykFsQU){JAsHCPlaVk = true;}
      if(JuLQXeHtpz == eZTBOUgcNq){jOoZqbRAZQ = true;}
      if(URwKcQnksG == YcROzUKxPP){amBfCeXsVx = true;}
      if(aBJswdjAoL == zSScPmjgur){FLOZRBHnOM = true;}
      while(eZTBOUgcNq == JuLQXeHtpz){QpRVMHKrpV = true;}
      while(YcROzUKxPP == YcROzUKxPP){AEcQBoDydk = true;}
      while(zSScPmjgur == zSScPmjgur){TbtOhObmum = true;}
      if(huCSZTFtrs == true){huCSZTFtrs = false;}
      if(BggzmKNdFG == true){BggzmKNdFG = false;}
      if(sWXniLGqkb == true){sWXniLGqkb = false;}
      if(kzhUIdZynf == true){kzhUIdZynf = false;}
      if(PQEWORkToF == true){PQEWORkToF = false;}
      if(YFbozLXNjN == true){YFbozLXNjN = false;}
      if(NNIQHBzMqJ == true){NNIQHBzMqJ = false;}
      if(jOoZqbRAZQ == true){jOoZqbRAZQ = false;}
      if(amBfCeXsVx == true){amBfCeXsVx = false;}
      if(FLOZRBHnOM == true){FLOZRBHnOM = false;}
      if(SYcfUKPBxW == true){SYcfUKPBxW = false;}
      if(tWnSmaMcNb == true){tWnSmaMcNb = false;}
      if(dGqsEXAPHp == true){dGqsEXAPHp = false;}
      if(UdkMxCKVLr == true){UdkMxCKVLr = false;}
      if(OVuyDhXumq == true){OVuyDhXumq = false;}
      if(oeZmiMhibw == true){oeZmiMhibw = false;}
      if(JAsHCPlaVk == true){JAsHCPlaVk = false;}
      if(QpRVMHKrpV == true){QpRVMHKrpV = false;}
      if(AEcQBoDydk == true){AEcQBoDydk = false;}
      if(TbtOhObmum == true){TbtOhObmum = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJLJSICCGT
{ 
  void RzjBjIHoTw()
  { 
      bool RuRZLJdLRp = false;
      bool XWibkYmWZs = false;
      bool ETOuuCxUez = false;
      bool MGOoVCMmha = false;
      bool LoAtIGKNDj = false;
      bool XTWxDygVdI = false;
      bool LIgScRHsGh = false;
      bool MAozgOSTlo = false;
      bool riRtbsiRlX = false;
      bool UpIYODIhQp = false;
      bool yQHUXXeWQn = false;
      bool eMjnQbqmpj = false;
      bool hpHhNWqPjd = false;
      bool GkCuqabxWE = false;
      bool OMBxsHGUIl = false;
      bool LVqgIHJZGA = false;
      bool fOmlhsKnxo = false;
      bool AtPlUVoJoF = false;
      bool QWHyRktUmj = false;
      bool RCpVYzZOPz = false;
      string BYcVtfxTBX;
      string BaRPtDITzR;
      string qqsQqwrtpN;
      string bUQwgRkIcS;
      string tunwiweZis;
      string aDxQIKeLdx;
      string nDcmufKUhc;
      string RAqfXuCxht;
      string RRKxmXWAnW;
      string lYdeepSAAC;
      string lKrFaZMQrM;
      string IhdjfWreAW;
      string JKgLprWLBh;
      string cBweIGZFVM;
      string LFHaODuszI;
      string xmAdsacfOh;
      string CAPKjGlzbY;
      string wmInLDDGxm;
      string xdMsjpBSkg;
      string cspnJLpwqH;
      if(BYcVtfxTBX == lKrFaZMQrM){RuRZLJdLRp = true;}
      else if(lKrFaZMQrM == BYcVtfxTBX){yQHUXXeWQn = true;}
      if(BaRPtDITzR == IhdjfWreAW){XWibkYmWZs = true;}
      else if(IhdjfWreAW == BaRPtDITzR){eMjnQbqmpj = true;}
      if(qqsQqwrtpN == JKgLprWLBh){ETOuuCxUez = true;}
      else if(JKgLprWLBh == qqsQqwrtpN){hpHhNWqPjd = true;}
      if(bUQwgRkIcS == cBweIGZFVM){MGOoVCMmha = true;}
      else if(cBweIGZFVM == bUQwgRkIcS){GkCuqabxWE = true;}
      if(tunwiweZis == LFHaODuszI){LoAtIGKNDj = true;}
      else if(LFHaODuszI == tunwiweZis){OMBxsHGUIl = true;}
      if(aDxQIKeLdx == xmAdsacfOh){XTWxDygVdI = true;}
      else if(xmAdsacfOh == aDxQIKeLdx){LVqgIHJZGA = true;}
      if(nDcmufKUhc == CAPKjGlzbY){LIgScRHsGh = true;}
      else if(CAPKjGlzbY == nDcmufKUhc){fOmlhsKnxo = true;}
      if(RAqfXuCxht == wmInLDDGxm){MAozgOSTlo = true;}
      if(RRKxmXWAnW == xdMsjpBSkg){riRtbsiRlX = true;}
      if(lYdeepSAAC == cspnJLpwqH){UpIYODIhQp = true;}
      while(wmInLDDGxm == RAqfXuCxht){AtPlUVoJoF = true;}
      while(xdMsjpBSkg == xdMsjpBSkg){QWHyRktUmj = true;}
      while(cspnJLpwqH == cspnJLpwqH){RCpVYzZOPz = true;}
      if(RuRZLJdLRp == true){RuRZLJdLRp = false;}
      if(XWibkYmWZs == true){XWibkYmWZs = false;}
      if(ETOuuCxUez == true){ETOuuCxUez = false;}
      if(MGOoVCMmha == true){MGOoVCMmha = false;}
      if(LoAtIGKNDj == true){LoAtIGKNDj = false;}
      if(XTWxDygVdI == true){XTWxDygVdI = false;}
      if(LIgScRHsGh == true){LIgScRHsGh = false;}
      if(MAozgOSTlo == true){MAozgOSTlo = false;}
      if(riRtbsiRlX == true){riRtbsiRlX = false;}
      if(UpIYODIhQp == true){UpIYODIhQp = false;}
      if(yQHUXXeWQn == true){yQHUXXeWQn = false;}
      if(eMjnQbqmpj == true){eMjnQbqmpj = false;}
      if(hpHhNWqPjd == true){hpHhNWqPjd = false;}
      if(GkCuqabxWE == true){GkCuqabxWE = false;}
      if(OMBxsHGUIl == true){OMBxsHGUIl = false;}
      if(LVqgIHJZGA == true){LVqgIHJZGA = false;}
      if(fOmlhsKnxo == true){fOmlhsKnxo = false;}
      if(AtPlUVoJoF == true){AtPlUVoJoF = false;}
      if(QWHyRktUmj == true){QWHyRktUmj = false;}
      if(RCpVYzZOPz == true){RCpVYzZOPz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPKHTCQXRY
{ 
  void WezQRfWGBJ()
  { 
      bool ZrwJdoragH = false;
      bool pszzBSrRyF = false;
      bool VYnnzSCamN = false;
      bool uQNNDRaHAY = false;
      bool lbkrDVlskJ = false;
      bool bgBdiADHKK = false;
      bool mRmTLYfkui = false;
      bool qkRZTsmwjc = false;
      bool gIpdkNOieC = false;
      bool NSxokTnRfd = false;
      bool pAxBRqPbJo = false;
      bool NHXhcebJhy = false;
      bool KwFsUXmbnA = false;
      bool FVPFlfKnLt = false;
      bool ymYpoGuPLG = false;
      bool qeihTttEft = false;
      bool DmnJjqqRuw = false;
      bool TmxnzXWPEO = false;
      bool bXPgIZlhlr = false;
      bool lFIRpKyOGx = false;
      string UKWWVwHkOH;
      string GYYYHbpPPH;
      string ijciIjXzVU;
      string PMcOfWLZfO;
      string JgSTmbTGGT;
      string IjJIXjgnNl;
      string YIOtrsuJrj;
      string PPjByCRIwf;
      string QQrCLeDUpw;
      string oXMtoARXbs;
      string gJNWDsAHJV;
      string SYqhUHQLhM;
      string paSwtqCpLx;
      string ksgCzGDUyS;
      string euKUdQgeYh;
      string jFpOCFqRbM;
      string pKuLkYqnhO;
      string EuMPhuPxSc;
      string KXRdNeDRAs;
      string PkslbUzzjE;
      if(UKWWVwHkOH == gJNWDsAHJV){ZrwJdoragH = true;}
      else if(gJNWDsAHJV == UKWWVwHkOH){pAxBRqPbJo = true;}
      if(GYYYHbpPPH == SYqhUHQLhM){pszzBSrRyF = true;}
      else if(SYqhUHQLhM == GYYYHbpPPH){NHXhcebJhy = true;}
      if(ijciIjXzVU == paSwtqCpLx){VYnnzSCamN = true;}
      else if(paSwtqCpLx == ijciIjXzVU){KwFsUXmbnA = true;}
      if(PMcOfWLZfO == ksgCzGDUyS){uQNNDRaHAY = true;}
      else if(ksgCzGDUyS == PMcOfWLZfO){FVPFlfKnLt = true;}
      if(JgSTmbTGGT == euKUdQgeYh){lbkrDVlskJ = true;}
      else if(euKUdQgeYh == JgSTmbTGGT){ymYpoGuPLG = true;}
      if(IjJIXjgnNl == jFpOCFqRbM){bgBdiADHKK = true;}
      else if(jFpOCFqRbM == IjJIXjgnNl){qeihTttEft = true;}
      if(YIOtrsuJrj == pKuLkYqnhO){mRmTLYfkui = true;}
      else if(pKuLkYqnhO == YIOtrsuJrj){DmnJjqqRuw = true;}
      if(PPjByCRIwf == EuMPhuPxSc){qkRZTsmwjc = true;}
      if(QQrCLeDUpw == KXRdNeDRAs){gIpdkNOieC = true;}
      if(oXMtoARXbs == PkslbUzzjE){NSxokTnRfd = true;}
      while(EuMPhuPxSc == PPjByCRIwf){TmxnzXWPEO = true;}
      while(KXRdNeDRAs == KXRdNeDRAs){bXPgIZlhlr = true;}
      while(PkslbUzzjE == PkslbUzzjE){lFIRpKyOGx = true;}
      if(ZrwJdoragH == true){ZrwJdoragH = false;}
      if(pszzBSrRyF == true){pszzBSrRyF = false;}
      if(VYnnzSCamN == true){VYnnzSCamN = false;}
      if(uQNNDRaHAY == true){uQNNDRaHAY = false;}
      if(lbkrDVlskJ == true){lbkrDVlskJ = false;}
      if(bgBdiADHKK == true){bgBdiADHKK = false;}
      if(mRmTLYfkui == true){mRmTLYfkui = false;}
      if(qkRZTsmwjc == true){qkRZTsmwjc = false;}
      if(gIpdkNOieC == true){gIpdkNOieC = false;}
      if(NSxokTnRfd == true){NSxokTnRfd = false;}
      if(pAxBRqPbJo == true){pAxBRqPbJo = false;}
      if(NHXhcebJhy == true){NHXhcebJhy = false;}
      if(KwFsUXmbnA == true){KwFsUXmbnA = false;}
      if(FVPFlfKnLt == true){FVPFlfKnLt = false;}
      if(ymYpoGuPLG == true){ymYpoGuPLG = false;}
      if(qeihTttEft == true){qeihTttEft = false;}
      if(DmnJjqqRuw == true){DmnJjqqRuw = false;}
      if(TmxnzXWPEO == true){TmxnzXWPEO = false;}
      if(bXPgIZlhlr == true){bXPgIZlhlr = false;}
      if(lFIRpKyOGx == true){lFIRpKyOGx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWOIDKMQIT
{ 
  void wQjcNddzhJ()
  { 
      bool udGVEwCThA = false;
      bool IqBDKUHgAq = false;
      bool UBdhcjjVyB = false;
      bool PXqJLwxlzc = false;
      bool BpUmEDfVqG = false;
      bool eyMrKsAYrT = false;
      bool LfUfjkArrO = false;
      bool XVgWodgpdY = false;
      bool EOerWRKyyR = false;
      bool uYsfRVVnCS = false;
      bool DndbiIQpCg = false;
      bool MJuSPxBcJS = false;
      bool aBtZSybBFT = false;
      bool IrnKVPkCJN = false;
      bool BUwQFlcZPT = false;
      bool TrdirBtDJj = false;
      bool gOkhYTUjxz = false;
      bool MzSwRGFcTg = false;
      bool VCkkAPNFRU = false;
      bool VgrZgliNrl = false;
      string BTrdCEmjXj;
      string YoJrVNjrJR;
      string LuHuEbywaS;
      string XgYwznsbIU;
      string ouXXBgmixd;
      string mCCgpFLwYa;
      string GqIFLqPNsg;
      string UIjocPWjtX;
      string nOyxeVdqGs;
      string bxCgNxlSLJ;
      string RZpPIeSMEZ;
      string ibBBmqrLZp;
      string MXHzFWFCae;
      string dDXjGNYinA;
      string CRmfKzuBtW;
      string FZsUwsSpJl;
      string YPlZweERtY;
      string SJXZmukaoG;
      string aEIEZEKCmM;
      string uhYBalfMje;
      if(BTrdCEmjXj == RZpPIeSMEZ){udGVEwCThA = true;}
      else if(RZpPIeSMEZ == BTrdCEmjXj){DndbiIQpCg = true;}
      if(YoJrVNjrJR == ibBBmqrLZp){IqBDKUHgAq = true;}
      else if(ibBBmqrLZp == YoJrVNjrJR){MJuSPxBcJS = true;}
      if(LuHuEbywaS == MXHzFWFCae){UBdhcjjVyB = true;}
      else if(MXHzFWFCae == LuHuEbywaS){aBtZSybBFT = true;}
      if(XgYwznsbIU == dDXjGNYinA){PXqJLwxlzc = true;}
      else if(dDXjGNYinA == XgYwznsbIU){IrnKVPkCJN = true;}
      if(ouXXBgmixd == CRmfKzuBtW){BpUmEDfVqG = true;}
      else if(CRmfKzuBtW == ouXXBgmixd){BUwQFlcZPT = true;}
      if(mCCgpFLwYa == FZsUwsSpJl){eyMrKsAYrT = true;}
      else if(FZsUwsSpJl == mCCgpFLwYa){TrdirBtDJj = true;}
      if(GqIFLqPNsg == YPlZweERtY){LfUfjkArrO = true;}
      else if(YPlZweERtY == GqIFLqPNsg){gOkhYTUjxz = true;}
      if(UIjocPWjtX == SJXZmukaoG){XVgWodgpdY = true;}
      if(nOyxeVdqGs == aEIEZEKCmM){EOerWRKyyR = true;}
      if(bxCgNxlSLJ == uhYBalfMje){uYsfRVVnCS = true;}
      while(SJXZmukaoG == UIjocPWjtX){MzSwRGFcTg = true;}
      while(aEIEZEKCmM == aEIEZEKCmM){VCkkAPNFRU = true;}
      while(uhYBalfMje == uhYBalfMje){VgrZgliNrl = true;}
      if(udGVEwCThA == true){udGVEwCThA = false;}
      if(IqBDKUHgAq == true){IqBDKUHgAq = false;}
      if(UBdhcjjVyB == true){UBdhcjjVyB = false;}
      if(PXqJLwxlzc == true){PXqJLwxlzc = false;}
      if(BpUmEDfVqG == true){BpUmEDfVqG = false;}
      if(eyMrKsAYrT == true){eyMrKsAYrT = false;}
      if(LfUfjkArrO == true){LfUfjkArrO = false;}
      if(XVgWodgpdY == true){XVgWodgpdY = false;}
      if(EOerWRKyyR == true){EOerWRKyyR = false;}
      if(uYsfRVVnCS == true){uYsfRVVnCS = false;}
      if(DndbiIQpCg == true){DndbiIQpCg = false;}
      if(MJuSPxBcJS == true){MJuSPxBcJS = false;}
      if(aBtZSybBFT == true){aBtZSybBFT = false;}
      if(IrnKVPkCJN == true){IrnKVPkCJN = false;}
      if(BUwQFlcZPT == true){BUwQFlcZPT = false;}
      if(TrdirBtDJj == true){TrdirBtDJj = false;}
      if(gOkhYTUjxz == true){gOkhYTUjxz = false;}
      if(MzSwRGFcTg == true){MzSwRGFcTg = false;}
      if(VCkkAPNFRU == true){VCkkAPNFRU = false;}
      if(VgrZgliNrl == true){VgrZgliNrl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DEMGRDWJYO
{ 
  void fWCEkoNjeb()
  { 
      bool HmTspgJWGy = false;
      bool yRKNUhlfAr = false;
      bool CFadqOoGlq = false;
      bool rGlLhWKEpu = false;
      bool WDIQosJITw = false;
      bool mRCBSCLpCb = false;
      bool rCkPGreyfx = false;
      bool XhpFVzwJnx = false;
      bool EgmoDZEkrf = false;
      bool KUBNCTRsJx = false;
      bool NKcVXFaxeT = false;
      bool GBBFWLOuLf = false;
      bool mtGzmDfbCC = false;
      bool gCAqisDQRy = false;
      bool zGGXZISwqq = false;
      bool EWgcJTEciU = false;
      bool ZyuclDBJVc = false;
      bool HydNggnhZd = false;
      bool jjkKxKUWhO = false;
      bool oahwXALckV = false;
      string arzHuGyMib;
      string DiTGmRPWYB;
      string bcwMDdbTLH;
      string PYTrlhICWy;
      string FVUKTLYrZZ;
      string octrPxulEQ;
      string ddAaMePbUE;
      string IMzauGHlrq;
      string FitkSldacn;
      string lVxGTbUtxo;
      string wxXURbcTwJ;
      string pJsMKtiPHZ;
      string AnzfRlOsGT;
      string kMnDuILYTq;
      string JKeSycckuZ;
      string rFmXnHxqCe;
      string MjMbYcVpQB;
      string iKwPQoJfgo;
      string JdxgbfZPOm;
      string KTVodYxCtV;
      if(arzHuGyMib == wxXURbcTwJ){HmTspgJWGy = true;}
      else if(wxXURbcTwJ == arzHuGyMib){NKcVXFaxeT = true;}
      if(DiTGmRPWYB == pJsMKtiPHZ){yRKNUhlfAr = true;}
      else if(pJsMKtiPHZ == DiTGmRPWYB){GBBFWLOuLf = true;}
      if(bcwMDdbTLH == AnzfRlOsGT){CFadqOoGlq = true;}
      else if(AnzfRlOsGT == bcwMDdbTLH){mtGzmDfbCC = true;}
      if(PYTrlhICWy == kMnDuILYTq){rGlLhWKEpu = true;}
      else if(kMnDuILYTq == PYTrlhICWy){gCAqisDQRy = true;}
      if(FVUKTLYrZZ == JKeSycckuZ){WDIQosJITw = true;}
      else if(JKeSycckuZ == FVUKTLYrZZ){zGGXZISwqq = true;}
      if(octrPxulEQ == rFmXnHxqCe){mRCBSCLpCb = true;}
      else if(rFmXnHxqCe == octrPxulEQ){EWgcJTEciU = true;}
      if(ddAaMePbUE == MjMbYcVpQB){rCkPGreyfx = true;}
      else if(MjMbYcVpQB == ddAaMePbUE){ZyuclDBJVc = true;}
      if(IMzauGHlrq == iKwPQoJfgo){XhpFVzwJnx = true;}
      if(FitkSldacn == JdxgbfZPOm){EgmoDZEkrf = true;}
      if(lVxGTbUtxo == KTVodYxCtV){KUBNCTRsJx = true;}
      while(iKwPQoJfgo == IMzauGHlrq){HydNggnhZd = true;}
      while(JdxgbfZPOm == JdxgbfZPOm){jjkKxKUWhO = true;}
      while(KTVodYxCtV == KTVodYxCtV){oahwXALckV = true;}
      if(HmTspgJWGy == true){HmTspgJWGy = false;}
      if(yRKNUhlfAr == true){yRKNUhlfAr = false;}
      if(CFadqOoGlq == true){CFadqOoGlq = false;}
      if(rGlLhWKEpu == true){rGlLhWKEpu = false;}
      if(WDIQosJITw == true){WDIQosJITw = false;}
      if(mRCBSCLpCb == true){mRCBSCLpCb = false;}
      if(rCkPGreyfx == true){rCkPGreyfx = false;}
      if(XhpFVzwJnx == true){XhpFVzwJnx = false;}
      if(EgmoDZEkrf == true){EgmoDZEkrf = false;}
      if(KUBNCTRsJx == true){KUBNCTRsJx = false;}
      if(NKcVXFaxeT == true){NKcVXFaxeT = false;}
      if(GBBFWLOuLf == true){GBBFWLOuLf = false;}
      if(mtGzmDfbCC == true){mtGzmDfbCC = false;}
      if(gCAqisDQRy == true){gCAqisDQRy = false;}
      if(zGGXZISwqq == true){zGGXZISwqq = false;}
      if(EWgcJTEciU == true){EWgcJTEciU = false;}
      if(ZyuclDBJVc == true){ZyuclDBJVc = false;}
      if(HydNggnhZd == true){HydNggnhZd = false;}
      if(jjkKxKUWhO == true){jjkKxKUWhO = false;}
      if(oahwXALckV == true){oahwXALckV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPYEYQXCSO
{ 
  void oQlYFeGhUC()
  { 
      bool mVcVjFeEGH = false;
      bool gbSLNkofaQ = false;
      bool bkpOQLbNfe = false;
      bool qCaklocyHP = false;
      bool safaHJYJgp = false;
      bool SLPreCfNEX = false;
      bool dQXbPdAgZX = false;
      bool HpYKXAFPGH = false;
      bool mRgpLfmiGi = false;
      bool JPsilbCDKc = false;
      bool IqjJhclETd = false;
      bool xQGxkLjhQi = false;
      bool qRaqOrwoYu = false;
      bool yBEdywhWHi = false;
      bool shPbksIwya = false;
      bool rUmakqPrtp = false;
      bool fxfXfwLczo = false;
      bool cMZgpJCzFU = false;
      bool jAqxDdNcrG = false;
      bool focRCwBqwo = false;
      string LjiTRpeKnO;
      string GMKJtMhmwd;
      string XkCTaWMxhQ;
      string oqTcnwJtTX;
      string rtIXEBcoTh;
      string SUaIdahOst;
      string dhcXYOshVy;
      string CnSXkcbePY;
      string sWczxTQLyN;
      string NuAZsJRkyo;
      string IuTVfeCCXA;
      string yDzTBGFcZE;
      string ygiHjGmsea;
      string LqfZPyDHTS;
      string ROnyOKugYm;
      string EnLsqaMLkY;
      string qJXxoHWYDC;
      string DyJGmisjrY;
      string LGUqVXelio;
      string lqVuaIqpJH;
      if(LjiTRpeKnO == IuTVfeCCXA){mVcVjFeEGH = true;}
      else if(IuTVfeCCXA == LjiTRpeKnO){IqjJhclETd = true;}
      if(GMKJtMhmwd == yDzTBGFcZE){gbSLNkofaQ = true;}
      else if(yDzTBGFcZE == GMKJtMhmwd){xQGxkLjhQi = true;}
      if(XkCTaWMxhQ == ygiHjGmsea){bkpOQLbNfe = true;}
      else if(ygiHjGmsea == XkCTaWMxhQ){qRaqOrwoYu = true;}
      if(oqTcnwJtTX == LqfZPyDHTS){qCaklocyHP = true;}
      else if(LqfZPyDHTS == oqTcnwJtTX){yBEdywhWHi = true;}
      if(rtIXEBcoTh == ROnyOKugYm){safaHJYJgp = true;}
      else if(ROnyOKugYm == rtIXEBcoTh){shPbksIwya = true;}
      if(SUaIdahOst == EnLsqaMLkY){SLPreCfNEX = true;}
      else if(EnLsqaMLkY == SUaIdahOst){rUmakqPrtp = true;}
      if(dhcXYOshVy == qJXxoHWYDC){dQXbPdAgZX = true;}
      else if(qJXxoHWYDC == dhcXYOshVy){fxfXfwLczo = true;}
      if(CnSXkcbePY == DyJGmisjrY){HpYKXAFPGH = true;}
      if(sWczxTQLyN == LGUqVXelio){mRgpLfmiGi = true;}
      if(NuAZsJRkyo == lqVuaIqpJH){JPsilbCDKc = true;}
      while(DyJGmisjrY == CnSXkcbePY){cMZgpJCzFU = true;}
      while(LGUqVXelio == LGUqVXelio){jAqxDdNcrG = true;}
      while(lqVuaIqpJH == lqVuaIqpJH){focRCwBqwo = true;}
      if(mVcVjFeEGH == true){mVcVjFeEGH = false;}
      if(gbSLNkofaQ == true){gbSLNkofaQ = false;}
      if(bkpOQLbNfe == true){bkpOQLbNfe = false;}
      if(qCaklocyHP == true){qCaklocyHP = false;}
      if(safaHJYJgp == true){safaHJYJgp = false;}
      if(SLPreCfNEX == true){SLPreCfNEX = false;}
      if(dQXbPdAgZX == true){dQXbPdAgZX = false;}
      if(HpYKXAFPGH == true){HpYKXAFPGH = false;}
      if(mRgpLfmiGi == true){mRgpLfmiGi = false;}
      if(JPsilbCDKc == true){JPsilbCDKc = false;}
      if(IqjJhclETd == true){IqjJhclETd = false;}
      if(xQGxkLjhQi == true){xQGxkLjhQi = false;}
      if(qRaqOrwoYu == true){qRaqOrwoYu = false;}
      if(yBEdywhWHi == true){yBEdywhWHi = false;}
      if(shPbksIwya == true){shPbksIwya = false;}
      if(rUmakqPrtp == true){rUmakqPrtp = false;}
      if(fxfXfwLczo == true){fxfXfwLczo = false;}
      if(cMZgpJCzFU == true){cMZgpJCzFU = false;}
      if(jAqxDdNcrG == true){jAqxDdNcrG = false;}
      if(focRCwBqwo == true){focRCwBqwo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVPFGEYFNH
{ 
  void cBuqZrdtpT()
  { 
      bool CtYgVVSwQL = false;
      bool mqKhiBhqAg = false;
      bool fHsDpxHkRM = false;
      bool IyPywTJHoM = false;
      bool FzdcnAoQRn = false;
      bool SFkPHuBUpY = false;
      bool NheDCnbMkO = false;
      bool qZCnagcPOo = false;
      bool HpSctDNzpB = false;
      bool SoRPyXTaaA = false;
      bool YcfDwrDxna = false;
      bool SkFBRXOBIz = false;
      bool acVjwCIloD = false;
      bool MCoOQdKPgC = false;
      bool zPKPigiQya = false;
      bool IRRbYuHwGs = false;
      bool jRIkNQwqjm = false;
      bool NzUGzKRFBP = false;
      bool TrmNttjNoU = false;
      bool VNImRgHZBR = false;
      string OHxmodHFYI;
      string iOGzphMrrE;
      string oCohfqnxfr;
      string YzpAEBdprC;
      string aRQzFCZsbr;
      string taVYJMSPHx;
      string oJYfiiXGtn;
      string EVzpcXkpbc;
      string QuUmyydRpr;
      string iOiuMRrkPW;
      string dTymnXaeul;
      string bcmdftnlgk;
      string EGPCFpmEdL;
      string ezZFzwwgzZ;
      string WyVDPFaEPS;
      string cGDeRXEwhx;
      string jWBjGbCgei;
      string xGmHNGjMlz;
      string OinKiYwunb;
      string rAzBoAxlxn;
      if(OHxmodHFYI == dTymnXaeul){CtYgVVSwQL = true;}
      else if(dTymnXaeul == OHxmodHFYI){YcfDwrDxna = true;}
      if(iOGzphMrrE == bcmdftnlgk){mqKhiBhqAg = true;}
      else if(bcmdftnlgk == iOGzphMrrE){SkFBRXOBIz = true;}
      if(oCohfqnxfr == EGPCFpmEdL){fHsDpxHkRM = true;}
      else if(EGPCFpmEdL == oCohfqnxfr){acVjwCIloD = true;}
      if(YzpAEBdprC == ezZFzwwgzZ){IyPywTJHoM = true;}
      else if(ezZFzwwgzZ == YzpAEBdprC){MCoOQdKPgC = true;}
      if(aRQzFCZsbr == WyVDPFaEPS){FzdcnAoQRn = true;}
      else if(WyVDPFaEPS == aRQzFCZsbr){zPKPigiQya = true;}
      if(taVYJMSPHx == cGDeRXEwhx){SFkPHuBUpY = true;}
      else if(cGDeRXEwhx == taVYJMSPHx){IRRbYuHwGs = true;}
      if(oJYfiiXGtn == jWBjGbCgei){NheDCnbMkO = true;}
      else if(jWBjGbCgei == oJYfiiXGtn){jRIkNQwqjm = true;}
      if(EVzpcXkpbc == xGmHNGjMlz){qZCnagcPOo = true;}
      if(QuUmyydRpr == OinKiYwunb){HpSctDNzpB = true;}
      if(iOiuMRrkPW == rAzBoAxlxn){SoRPyXTaaA = true;}
      while(xGmHNGjMlz == EVzpcXkpbc){NzUGzKRFBP = true;}
      while(OinKiYwunb == OinKiYwunb){TrmNttjNoU = true;}
      while(rAzBoAxlxn == rAzBoAxlxn){VNImRgHZBR = true;}
      if(CtYgVVSwQL == true){CtYgVVSwQL = false;}
      if(mqKhiBhqAg == true){mqKhiBhqAg = false;}
      if(fHsDpxHkRM == true){fHsDpxHkRM = false;}
      if(IyPywTJHoM == true){IyPywTJHoM = false;}
      if(FzdcnAoQRn == true){FzdcnAoQRn = false;}
      if(SFkPHuBUpY == true){SFkPHuBUpY = false;}
      if(NheDCnbMkO == true){NheDCnbMkO = false;}
      if(qZCnagcPOo == true){qZCnagcPOo = false;}
      if(HpSctDNzpB == true){HpSctDNzpB = false;}
      if(SoRPyXTaaA == true){SoRPyXTaaA = false;}
      if(YcfDwrDxna == true){YcfDwrDxna = false;}
      if(SkFBRXOBIz == true){SkFBRXOBIz = false;}
      if(acVjwCIloD == true){acVjwCIloD = false;}
      if(MCoOQdKPgC == true){MCoOQdKPgC = false;}
      if(zPKPigiQya == true){zPKPigiQya = false;}
      if(IRRbYuHwGs == true){IRRbYuHwGs = false;}
      if(jRIkNQwqjm == true){jRIkNQwqjm = false;}
      if(NzUGzKRFBP == true){NzUGzKRFBP = false;}
      if(TrmNttjNoU == true){TrmNttjNoU = false;}
      if(VNImRgHZBR == true){VNImRgHZBR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSDSBKJRKQ
{ 
  void sZxcwwtrHN()
  { 
      bool fixfkPYSgI = false;
      bool QCrtVmoQZt = false;
      bool IfHFhgQpmH = false;
      bool fypJcVpCXQ = false;
      bool zfyKCbnhZh = false;
      bool lYfRRAbryD = false;
      bool yifZbRLhQA = false;
      bool wlrIubgwCF = false;
      bool shPEUHSYqc = false;
      bool txEURPAXhj = false;
      bool QFQZkAfWVp = false;
      bool SeorKPSaFT = false;
      bool zmpnFyhXpf = false;
      bool aINSnmRpTU = false;
      bool auCBJPHLJB = false;
      bool xZSOkdObTm = false;
      bool RIfpOJQWDX = false;
      bool ybHjsDjoep = false;
      bool pVOnhBozhK = false;
      bool XoWfCROMmz = false;
      string KXuXtEtQBh;
      string qsFgDJOUZG;
      string uXULjadnuN;
      string FIVoACPVGu;
      string lqSayJDaEi;
      string eKLOGlCjmS;
      string ZGVmciXQfA;
      string ssNdTEFtMa;
      string WDiMiuxGhO;
      string zfhmVfUeyP;
      string lmtDolwhtC;
      string gIWMuWXJEg;
      string kQhRANKZHn;
      string iZwxniIeWw;
      string yPLehqIVry;
      string HLaQdUFbDa;
      string bWZGSHLZXL;
      string NrlHiVECjI;
      string EnhJfXyfSS;
      string dfbwUaoFMZ;
      if(KXuXtEtQBh == lmtDolwhtC){fixfkPYSgI = true;}
      else if(lmtDolwhtC == KXuXtEtQBh){QFQZkAfWVp = true;}
      if(qsFgDJOUZG == gIWMuWXJEg){QCrtVmoQZt = true;}
      else if(gIWMuWXJEg == qsFgDJOUZG){SeorKPSaFT = true;}
      if(uXULjadnuN == kQhRANKZHn){IfHFhgQpmH = true;}
      else if(kQhRANKZHn == uXULjadnuN){zmpnFyhXpf = true;}
      if(FIVoACPVGu == iZwxniIeWw){fypJcVpCXQ = true;}
      else if(iZwxniIeWw == FIVoACPVGu){aINSnmRpTU = true;}
      if(lqSayJDaEi == yPLehqIVry){zfyKCbnhZh = true;}
      else if(yPLehqIVry == lqSayJDaEi){auCBJPHLJB = true;}
      if(eKLOGlCjmS == HLaQdUFbDa){lYfRRAbryD = true;}
      else if(HLaQdUFbDa == eKLOGlCjmS){xZSOkdObTm = true;}
      if(ZGVmciXQfA == bWZGSHLZXL){yifZbRLhQA = true;}
      else if(bWZGSHLZXL == ZGVmciXQfA){RIfpOJQWDX = true;}
      if(ssNdTEFtMa == NrlHiVECjI){wlrIubgwCF = true;}
      if(WDiMiuxGhO == EnhJfXyfSS){shPEUHSYqc = true;}
      if(zfhmVfUeyP == dfbwUaoFMZ){txEURPAXhj = true;}
      while(NrlHiVECjI == ssNdTEFtMa){ybHjsDjoep = true;}
      while(EnhJfXyfSS == EnhJfXyfSS){pVOnhBozhK = true;}
      while(dfbwUaoFMZ == dfbwUaoFMZ){XoWfCROMmz = true;}
      if(fixfkPYSgI == true){fixfkPYSgI = false;}
      if(QCrtVmoQZt == true){QCrtVmoQZt = false;}
      if(IfHFhgQpmH == true){IfHFhgQpmH = false;}
      if(fypJcVpCXQ == true){fypJcVpCXQ = false;}
      if(zfyKCbnhZh == true){zfyKCbnhZh = false;}
      if(lYfRRAbryD == true){lYfRRAbryD = false;}
      if(yifZbRLhQA == true){yifZbRLhQA = false;}
      if(wlrIubgwCF == true){wlrIubgwCF = false;}
      if(shPEUHSYqc == true){shPEUHSYqc = false;}
      if(txEURPAXhj == true){txEURPAXhj = false;}
      if(QFQZkAfWVp == true){QFQZkAfWVp = false;}
      if(SeorKPSaFT == true){SeorKPSaFT = false;}
      if(zmpnFyhXpf == true){zmpnFyhXpf = false;}
      if(aINSnmRpTU == true){aINSnmRpTU = false;}
      if(auCBJPHLJB == true){auCBJPHLJB = false;}
      if(xZSOkdObTm == true){xZSOkdObTm = false;}
      if(RIfpOJQWDX == true){RIfpOJQWDX = false;}
      if(ybHjsDjoep == true){ybHjsDjoep = false;}
      if(pVOnhBozhK == true){pVOnhBozhK = false;}
      if(XoWfCROMmz == true){XoWfCROMmz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBSJPLPRRY
{ 
  void nenuZknDSC()
  { 
      bool TpfBSkccWJ = false;
      bool nAygInjaXl = false;
      bool mzpfWfHcqU = false;
      bool buXFRfwopx = false;
      bool FijeGclqYo = false;
      bool aeknLTzAdl = false;
      bool dzlBgrcsOc = false;
      bool qukZfEPLYt = false;
      bool sPDBtxKisy = false;
      bool fwKDTGwixO = false;
      bool zsbwxfsKIH = false;
      bool EmajrNukGj = false;
      bool hszQwujhGZ = false;
      bool IgOKtAmHEO = false;
      bool EzaktsUZKF = false;
      bool KLbNfGsLzB = false;
      bool uLEhzWYQpr = false;
      bool anfreiROWD = false;
      bool aKWBPwEAem = false;
      bool HbICTstrlW = false;
      string aPNhpSAgRR;
      string IPqGrRBCOZ;
      string ztTDNrTGbG;
      string wUVLqmrrdk;
      string iRXoFJXXjt;
      string KqDxZguKUy;
      string ztFKVntePE;
      string YIYcphWdxE;
      string UuWhwEQXlK;
      string rhXfloLMTQ;
      string PrIeUBSaHq;
      string KQMPcDXXOQ;
      string XVsFMpkrqA;
      string WJJgocmqMt;
      string koQuAaUHCh;
      string RnxCrsyDSd;
      string QZiGUAHeaA;
      string PfLTfhFyFk;
      string VcpIihMHou;
      string djYhcKFJZz;
      if(aPNhpSAgRR == PrIeUBSaHq){TpfBSkccWJ = true;}
      else if(PrIeUBSaHq == aPNhpSAgRR){zsbwxfsKIH = true;}
      if(IPqGrRBCOZ == KQMPcDXXOQ){nAygInjaXl = true;}
      else if(KQMPcDXXOQ == IPqGrRBCOZ){EmajrNukGj = true;}
      if(ztTDNrTGbG == XVsFMpkrqA){mzpfWfHcqU = true;}
      else if(XVsFMpkrqA == ztTDNrTGbG){hszQwujhGZ = true;}
      if(wUVLqmrrdk == WJJgocmqMt){buXFRfwopx = true;}
      else if(WJJgocmqMt == wUVLqmrrdk){IgOKtAmHEO = true;}
      if(iRXoFJXXjt == koQuAaUHCh){FijeGclqYo = true;}
      else if(koQuAaUHCh == iRXoFJXXjt){EzaktsUZKF = true;}
      if(KqDxZguKUy == RnxCrsyDSd){aeknLTzAdl = true;}
      else if(RnxCrsyDSd == KqDxZguKUy){KLbNfGsLzB = true;}
      if(ztFKVntePE == QZiGUAHeaA){dzlBgrcsOc = true;}
      else if(QZiGUAHeaA == ztFKVntePE){uLEhzWYQpr = true;}
      if(YIYcphWdxE == PfLTfhFyFk){qukZfEPLYt = true;}
      if(UuWhwEQXlK == VcpIihMHou){sPDBtxKisy = true;}
      if(rhXfloLMTQ == djYhcKFJZz){fwKDTGwixO = true;}
      while(PfLTfhFyFk == YIYcphWdxE){anfreiROWD = true;}
      while(VcpIihMHou == VcpIihMHou){aKWBPwEAem = true;}
      while(djYhcKFJZz == djYhcKFJZz){HbICTstrlW = true;}
      if(TpfBSkccWJ == true){TpfBSkccWJ = false;}
      if(nAygInjaXl == true){nAygInjaXl = false;}
      if(mzpfWfHcqU == true){mzpfWfHcqU = false;}
      if(buXFRfwopx == true){buXFRfwopx = false;}
      if(FijeGclqYo == true){FijeGclqYo = false;}
      if(aeknLTzAdl == true){aeknLTzAdl = false;}
      if(dzlBgrcsOc == true){dzlBgrcsOc = false;}
      if(qukZfEPLYt == true){qukZfEPLYt = false;}
      if(sPDBtxKisy == true){sPDBtxKisy = false;}
      if(fwKDTGwixO == true){fwKDTGwixO = false;}
      if(zsbwxfsKIH == true){zsbwxfsKIH = false;}
      if(EmajrNukGj == true){EmajrNukGj = false;}
      if(hszQwujhGZ == true){hszQwujhGZ = false;}
      if(IgOKtAmHEO == true){IgOKtAmHEO = false;}
      if(EzaktsUZKF == true){EzaktsUZKF = false;}
      if(KLbNfGsLzB == true){KLbNfGsLzB = false;}
      if(uLEhzWYQpr == true){uLEhzWYQpr = false;}
      if(anfreiROWD == true){anfreiROWD = false;}
      if(aKWBPwEAem == true){aKWBPwEAem = false;}
      if(HbICTstrlW == true){HbICTstrlW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDXQWZMASR
{ 
  void bySsYZhVOA()
  { 
      bool iKgNetmMob = false;
      bool zVyOaLRRoB = false;
      bool mlmVFESQGD = false;
      bool oIFxpGpfYQ = false;
      bool UxWaOYusGy = false;
      bool ojaYsxWLHZ = false;
      bool aVFkmqPBYT = false;
      bool UksYfoOMHg = false;
      bool JZKHNEgfDs = false;
      bool jeXyoyqlnW = false;
      bool IsTmcDpBrD = false;
      bool hJDaQBLyWh = false;
      bool JjxfjoNujh = false;
      bool ycYjYPGWdJ = false;
      bool NfnAKZaxgn = false;
      bool msOFMXumDm = false;
      bool puRKFEkTBB = false;
      bool tnTNUdwxUJ = false;
      bool OPNuuEOTWA = false;
      bool TSTpTRNduG = false;
      string AdELgiDfGi;
      string KfrmpOrdMf;
      string RqfjpbGnZb;
      string URxqUphLNc;
      string HPRqcsQBup;
      string HinDEIyTUF;
      string bPGeOshBSz;
      string fgPjXCZnGx;
      string KFriUkctlL;
      string rOpIBrImcj;
      string KPiuJaSEeC;
      string iKNXtWWWKc;
      string PmOGHRpHhe;
      string slLWltWwYt;
      string SYPichBSNe;
      string UkczTXAbnq;
      string jLVzJwypkz;
      string zayQKqXecY;
      string QXsDKHJLCO;
      string ttHgJHCPZf;
      if(AdELgiDfGi == KPiuJaSEeC){iKgNetmMob = true;}
      else if(KPiuJaSEeC == AdELgiDfGi){IsTmcDpBrD = true;}
      if(KfrmpOrdMf == iKNXtWWWKc){zVyOaLRRoB = true;}
      else if(iKNXtWWWKc == KfrmpOrdMf){hJDaQBLyWh = true;}
      if(RqfjpbGnZb == PmOGHRpHhe){mlmVFESQGD = true;}
      else if(PmOGHRpHhe == RqfjpbGnZb){JjxfjoNujh = true;}
      if(URxqUphLNc == slLWltWwYt){oIFxpGpfYQ = true;}
      else if(slLWltWwYt == URxqUphLNc){ycYjYPGWdJ = true;}
      if(HPRqcsQBup == SYPichBSNe){UxWaOYusGy = true;}
      else if(SYPichBSNe == HPRqcsQBup){NfnAKZaxgn = true;}
      if(HinDEIyTUF == UkczTXAbnq){ojaYsxWLHZ = true;}
      else if(UkczTXAbnq == HinDEIyTUF){msOFMXumDm = true;}
      if(bPGeOshBSz == jLVzJwypkz){aVFkmqPBYT = true;}
      else if(jLVzJwypkz == bPGeOshBSz){puRKFEkTBB = true;}
      if(fgPjXCZnGx == zayQKqXecY){UksYfoOMHg = true;}
      if(KFriUkctlL == QXsDKHJLCO){JZKHNEgfDs = true;}
      if(rOpIBrImcj == ttHgJHCPZf){jeXyoyqlnW = true;}
      while(zayQKqXecY == fgPjXCZnGx){tnTNUdwxUJ = true;}
      while(QXsDKHJLCO == QXsDKHJLCO){OPNuuEOTWA = true;}
      while(ttHgJHCPZf == ttHgJHCPZf){TSTpTRNduG = true;}
      if(iKgNetmMob == true){iKgNetmMob = false;}
      if(zVyOaLRRoB == true){zVyOaLRRoB = false;}
      if(mlmVFESQGD == true){mlmVFESQGD = false;}
      if(oIFxpGpfYQ == true){oIFxpGpfYQ = false;}
      if(UxWaOYusGy == true){UxWaOYusGy = false;}
      if(ojaYsxWLHZ == true){ojaYsxWLHZ = false;}
      if(aVFkmqPBYT == true){aVFkmqPBYT = false;}
      if(UksYfoOMHg == true){UksYfoOMHg = false;}
      if(JZKHNEgfDs == true){JZKHNEgfDs = false;}
      if(jeXyoyqlnW == true){jeXyoyqlnW = false;}
      if(IsTmcDpBrD == true){IsTmcDpBrD = false;}
      if(hJDaQBLyWh == true){hJDaQBLyWh = false;}
      if(JjxfjoNujh == true){JjxfjoNujh = false;}
      if(ycYjYPGWdJ == true){ycYjYPGWdJ = false;}
      if(NfnAKZaxgn == true){NfnAKZaxgn = false;}
      if(msOFMXumDm == true){msOFMXumDm = false;}
      if(puRKFEkTBB == true){puRKFEkTBB = false;}
      if(tnTNUdwxUJ == true){tnTNUdwxUJ = false;}
      if(OPNuuEOTWA == true){OPNuuEOTWA = false;}
      if(TSTpTRNduG == true){TSTpTRNduG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPDKFEYQAZ
{ 
  void VeYmYEfRnL()
  { 
      bool DlkHVjWIsJ = false;
      bool iwaMJScqVR = false;
      bool TOpFYxQpWR = false;
      bool YEQoqGaAsK = false;
      bool ZzaczKhczm = false;
      bool LYJXinufiX = false;
      bool TfkajdekVC = false;
      bool qcxLqUmMFN = false;
      bool OmpiGAtsGC = false;
      bool KuQUpsNzsV = false;
      bool fxHwuhaxfO = false;
      bool AiZVIfoCUi = false;
      bool jkeSruMcUx = false;
      bool GmTjgRftmX = false;
      bool ZxNrCaUuLK = false;
      bool DLeKktRoDz = false;
      bool VxbhHNPpnq = false;
      bool AuOxJmXmQQ = false;
      bool aQRKsuIIym = false;
      bool AqpmBbUejo = false;
      string RdpXjmnlhG;
      string JFEgSRINdM;
      string BFYifZgyKS;
      string QcbLKuiHnV;
      string iFNWodEMMq;
      string RHHdbMFHrK;
      string FobOpfdsVW;
      string hAZIdurBtB;
      string UUlSBIUxiy;
      string pbPcPsdygI;
      string ALpoIQhzAf;
      string UDNpokDINg;
      string KgJWgGkwsj;
      string RsTkBJdxKk;
      string aVwDdlOYnd;
      string pUkzySCTHB;
      string ekGQOaibnf;
      string HGycGojFrt;
      string rMIPtwHUli;
      string HJpIFoPfoC;
      if(RdpXjmnlhG == ALpoIQhzAf){DlkHVjWIsJ = true;}
      else if(ALpoIQhzAf == RdpXjmnlhG){fxHwuhaxfO = true;}
      if(JFEgSRINdM == UDNpokDINg){iwaMJScqVR = true;}
      else if(UDNpokDINg == JFEgSRINdM){AiZVIfoCUi = true;}
      if(BFYifZgyKS == KgJWgGkwsj){TOpFYxQpWR = true;}
      else if(KgJWgGkwsj == BFYifZgyKS){jkeSruMcUx = true;}
      if(QcbLKuiHnV == RsTkBJdxKk){YEQoqGaAsK = true;}
      else if(RsTkBJdxKk == QcbLKuiHnV){GmTjgRftmX = true;}
      if(iFNWodEMMq == aVwDdlOYnd){ZzaczKhczm = true;}
      else if(aVwDdlOYnd == iFNWodEMMq){ZxNrCaUuLK = true;}
      if(RHHdbMFHrK == pUkzySCTHB){LYJXinufiX = true;}
      else if(pUkzySCTHB == RHHdbMFHrK){DLeKktRoDz = true;}
      if(FobOpfdsVW == ekGQOaibnf){TfkajdekVC = true;}
      else if(ekGQOaibnf == FobOpfdsVW){VxbhHNPpnq = true;}
      if(hAZIdurBtB == HGycGojFrt){qcxLqUmMFN = true;}
      if(UUlSBIUxiy == rMIPtwHUli){OmpiGAtsGC = true;}
      if(pbPcPsdygI == HJpIFoPfoC){KuQUpsNzsV = true;}
      while(HGycGojFrt == hAZIdurBtB){AuOxJmXmQQ = true;}
      while(rMIPtwHUli == rMIPtwHUli){aQRKsuIIym = true;}
      while(HJpIFoPfoC == HJpIFoPfoC){AqpmBbUejo = true;}
      if(DlkHVjWIsJ == true){DlkHVjWIsJ = false;}
      if(iwaMJScqVR == true){iwaMJScqVR = false;}
      if(TOpFYxQpWR == true){TOpFYxQpWR = false;}
      if(YEQoqGaAsK == true){YEQoqGaAsK = false;}
      if(ZzaczKhczm == true){ZzaczKhczm = false;}
      if(LYJXinufiX == true){LYJXinufiX = false;}
      if(TfkajdekVC == true){TfkajdekVC = false;}
      if(qcxLqUmMFN == true){qcxLqUmMFN = false;}
      if(OmpiGAtsGC == true){OmpiGAtsGC = false;}
      if(KuQUpsNzsV == true){KuQUpsNzsV = false;}
      if(fxHwuhaxfO == true){fxHwuhaxfO = false;}
      if(AiZVIfoCUi == true){AiZVIfoCUi = false;}
      if(jkeSruMcUx == true){jkeSruMcUx = false;}
      if(GmTjgRftmX == true){GmTjgRftmX = false;}
      if(ZxNrCaUuLK == true){ZxNrCaUuLK = false;}
      if(DLeKktRoDz == true){DLeKktRoDz = false;}
      if(VxbhHNPpnq == true){VxbhHNPpnq = false;}
      if(AuOxJmXmQQ == true){AuOxJmXmQQ = false;}
      if(aQRKsuIIym == true){aQRKsuIIym = false;}
      if(AqpmBbUejo == true){AqpmBbUejo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOCLEYYJLC
{ 
  void xUhgjNkoza()
  { 
      bool gUKWVtCPOm = false;
      bool NOeNiUtnKA = false;
      bool FepCRFkGjg = false;
      bool KYQDeBesip = false;
      bool PHFDsFBXHp = false;
      bool uIDybBeIFQ = false;
      bool Jwfhcoybhh = false;
      bool pAEUkyZmIL = false;
      bool DMytkCVRad = false;
      bool WWmSfSbWZE = false;
      bool GYoYAtDiNd = false;
      bool arzsNwxlwa = false;
      bool SgAELTNlnR = false;
      bool VCMEFdXYsp = false;
      bool ymExCeWsFi = false;
      bool UpZzkZXjNg = false;
      bool gRtwHXetni = false;
      bool YYrGcfbDCg = false;
      bool wTfFwfcNSf = false;
      bool FmLMIgrIpe = false;
      string kuKMtZcUWs;
      string EtdRkMAGnz;
      string ZIbOtBiVzK;
      string mKwxzGREmi;
      string COrNkrqbuY;
      string RCMrwcTwSs;
      string qGUMGtxgRe;
      string twSFxLPNcB;
      string JHaasjxDBW;
      string lVksqwsfHq;
      string tKKQdVjHuj;
      string MFSQjiftTV;
      string wtftrYKYNA;
      string RjFlHyxJwW;
      string zpHQJgCUII;
      string QzMktAdPYF;
      string LKstRczgJl;
      string lVxwWGlOjL;
      string VpQFjRXUqH;
      string UgkqLowNyg;
      if(kuKMtZcUWs == tKKQdVjHuj){gUKWVtCPOm = true;}
      else if(tKKQdVjHuj == kuKMtZcUWs){GYoYAtDiNd = true;}
      if(EtdRkMAGnz == MFSQjiftTV){NOeNiUtnKA = true;}
      else if(MFSQjiftTV == EtdRkMAGnz){arzsNwxlwa = true;}
      if(ZIbOtBiVzK == wtftrYKYNA){FepCRFkGjg = true;}
      else if(wtftrYKYNA == ZIbOtBiVzK){SgAELTNlnR = true;}
      if(mKwxzGREmi == RjFlHyxJwW){KYQDeBesip = true;}
      else if(RjFlHyxJwW == mKwxzGREmi){VCMEFdXYsp = true;}
      if(COrNkrqbuY == zpHQJgCUII){PHFDsFBXHp = true;}
      else if(zpHQJgCUII == COrNkrqbuY){ymExCeWsFi = true;}
      if(RCMrwcTwSs == QzMktAdPYF){uIDybBeIFQ = true;}
      else if(QzMktAdPYF == RCMrwcTwSs){UpZzkZXjNg = true;}
      if(qGUMGtxgRe == LKstRczgJl){Jwfhcoybhh = true;}
      else if(LKstRczgJl == qGUMGtxgRe){gRtwHXetni = true;}
      if(twSFxLPNcB == lVxwWGlOjL){pAEUkyZmIL = true;}
      if(JHaasjxDBW == VpQFjRXUqH){DMytkCVRad = true;}
      if(lVksqwsfHq == UgkqLowNyg){WWmSfSbWZE = true;}
      while(lVxwWGlOjL == twSFxLPNcB){YYrGcfbDCg = true;}
      while(VpQFjRXUqH == VpQFjRXUqH){wTfFwfcNSf = true;}
      while(UgkqLowNyg == UgkqLowNyg){FmLMIgrIpe = true;}
      if(gUKWVtCPOm == true){gUKWVtCPOm = false;}
      if(NOeNiUtnKA == true){NOeNiUtnKA = false;}
      if(FepCRFkGjg == true){FepCRFkGjg = false;}
      if(KYQDeBesip == true){KYQDeBesip = false;}
      if(PHFDsFBXHp == true){PHFDsFBXHp = false;}
      if(uIDybBeIFQ == true){uIDybBeIFQ = false;}
      if(Jwfhcoybhh == true){Jwfhcoybhh = false;}
      if(pAEUkyZmIL == true){pAEUkyZmIL = false;}
      if(DMytkCVRad == true){DMytkCVRad = false;}
      if(WWmSfSbWZE == true){WWmSfSbWZE = false;}
      if(GYoYAtDiNd == true){GYoYAtDiNd = false;}
      if(arzsNwxlwa == true){arzsNwxlwa = false;}
      if(SgAELTNlnR == true){SgAELTNlnR = false;}
      if(VCMEFdXYsp == true){VCMEFdXYsp = false;}
      if(ymExCeWsFi == true){ymExCeWsFi = false;}
      if(UpZzkZXjNg == true){UpZzkZXjNg = false;}
      if(gRtwHXetni == true){gRtwHXetni = false;}
      if(YYrGcfbDCg == true){YYrGcfbDCg = false;}
      if(wTfFwfcNSf == true){wTfFwfcNSf = false;}
      if(FmLMIgrIpe == true){FmLMIgrIpe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWIZXECAXL
{ 
  void ASyhPSyJsI()
  { 
      bool IMwCadbhas = false;
      bool aUYKDPVqIf = false;
      bool oLlaqqfsDn = false;
      bool giTRbNVqFB = false;
      bool niDMVSWxmL = false;
      bool xDhdxwZUKi = false;
      bool xhdlLqAGho = false;
      bool tdkGqFHYEY = false;
      bool UiGqqdBpTe = false;
      bool nAgWDFFRBe = false;
      bool RPOxRSSalr = false;
      bool oAQkOObmth = false;
      bool pKmDBsxODk = false;
      bool ApXZHEUIZX = false;
      bool KZDbpmjuIo = false;
      bool dSWSnGcLwY = false;
      bool UEXAqycqdJ = false;
      bool tTMVWQGKMN = false;
      bool JCGNHhSEkA = false;
      bool aJLADGCDkq = false;
      string RUyRTcXgqE;
      string HjdclrxPPk;
      string CzbmndMAwZ;
      string obLIxxlUor;
      string eETougGITQ;
      string wQpsYRrLdp;
      string QWkRPfYUen;
      string GcZWGxfmqG;
      string XDgecYkSif;
      string EZqzbISBZP;
      string HkdeKTpSlb;
      string kEUWRNpFnp;
      string tGlzjflauy;
      string ddNbymZCUJ;
      string hSfHtzFTgO;
      string RMMiUBzdtd;
      string hPXnxGqsXe;
      string mnkeHbadFj;
      string aRsgfQReGx;
      string muHqbStqJm;
      if(RUyRTcXgqE == HkdeKTpSlb){IMwCadbhas = true;}
      else if(HkdeKTpSlb == RUyRTcXgqE){RPOxRSSalr = true;}
      if(HjdclrxPPk == kEUWRNpFnp){aUYKDPVqIf = true;}
      else if(kEUWRNpFnp == HjdclrxPPk){oAQkOObmth = true;}
      if(CzbmndMAwZ == tGlzjflauy){oLlaqqfsDn = true;}
      else if(tGlzjflauy == CzbmndMAwZ){pKmDBsxODk = true;}
      if(obLIxxlUor == ddNbymZCUJ){giTRbNVqFB = true;}
      else if(ddNbymZCUJ == obLIxxlUor){ApXZHEUIZX = true;}
      if(eETougGITQ == hSfHtzFTgO){niDMVSWxmL = true;}
      else if(hSfHtzFTgO == eETougGITQ){KZDbpmjuIo = true;}
      if(wQpsYRrLdp == RMMiUBzdtd){xDhdxwZUKi = true;}
      else if(RMMiUBzdtd == wQpsYRrLdp){dSWSnGcLwY = true;}
      if(QWkRPfYUen == hPXnxGqsXe){xhdlLqAGho = true;}
      else if(hPXnxGqsXe == QWkRPfYUen){UEXAqycqdJ = true;}
      if(GcZWGxfmqG == mnkeHbadFj){tdkGqFHYEY = true;}
      if(XDgecYkSif == aRsgfQReGx){UiGqqdBpTe = true;}
      if(EZqzbISBZP == muHqbStqJm){nAgWDFFRBe = true;}
      while(mnkeHbadFj == GcZWGxfmqG){tTMVWQGKMN = true;}
      while(aRsgfQReGx == aRsgfQReGx){JCGNHhSEkA = true;}
      while(muHqbStqJm == muHqbStqJm){aJLADGCDkq = true;}
      if(IMwCadbhas == true){IMwCadbhas = false;}
      if(aUYKDPVqIf == true){aUYKDPVqIf = false;}
      if(oLlaqqfsDn == true){oLlaqqfsDn = false;}
      if(giTRbNVqFB == true){giTRbNVqFB = false;}
      if(niDMVSWxmL == true){niDMVSWxmL = false;}
      if(xDhdxwZUKi == true){xDhdxwZUKi = false;}
      if(xhdlLqAGho == true){xhdlLqAGho = false;}
      if(tdkGqFHYEY == true){tdkGqFHYEY = false;}
      if(UiGqqdBpTe == true){UiGqqdBpTe = false;}
      if(nAgWDFFRBe == true){nAgWDFFRBe = false;}
      if(RPOxRSSalr == true){RPOxRSSalr = false;}
      if(oAQkOObmth == true){oAQkOObmth = false;}
      if(pKmDBsxODk == true){pKmDBsxODk = false;}
      if(ApXZHEUIZX == true){ApXZHEUIZX = false;}
      if(KZDbpmjuIo == true){KZDbpmjuIo = false;}
      if(dSWSnGcLwY == true){dSWSnGcLwY = false;}
      if(UEXAqycqdJ == true){UEXAqycqdJ = false;}
      if(tTMVWQGKMN == true){tTMVWQGKMN = false;}
      if(JCGNHhSEkA == true){JCGNHhSEkA = false;}
      if(aJLADGCDkq == true){aJLADGCDkq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUZCTPCNXQ
{ 
  void fKqAFClYsh()
  { 
      bool ArQdaxMTKq = false;
      bool lcJzIJzZXw = false;
      bool xwNzgBdjkO = false;
      bool MyankKthcC = false;
      bool NDgfyxGaAe = false;
      bool HtEflDeRwZ = false;
      bool TciuemBUOy = false;
      bool ORwVitOgBj = false;
      bool uCiGHRsuCg = false;
      bool fckDhkTlBK = false;
      bool ukMCPpxixq = false;
      bool nxPMdRscnM = false;
      bool tGSgRlfrmy = false;
      bool ZcfqoJogpQ = false;
      bool UKyKshNXZP = false;
      bool rqynQnSfjd = false;
      bool JFuzRLRXXT = false;
      bool cLlWriIHnj = false;
      bool YHSWGieqaA = false;
      bool qJwLGOOzsg = false;
      string TjiSzDDhut;
      string PoMjjgGHjk;
      string zqdFsogMCV;
      string eJfERIoJKd;
      string MzzjHBtamm;
      string eFiBCcGdZK;
      string VqeYOFJHRb;
      string rxxGYzqsxq;
      string uGYPqZaeCo;
      string BKjAIUUaUC;
      string rlJLthHcbC;
      string kMghPOROhn;
      string ddEbZhMwyD;
      string eQYuyIxMVI;
      string SyCAEndBks;
      string CFsgXNhgkM;
      string ULeYWUnkjH;
      string RFsYVfbEXk;
      string DLLEAZWqXj;
      string ZPaJnGTcci;
      if(TjiSzDDhut == rlJLthHcbC){ArQdaxMTKq = true;}
      else if(rlJLthHcbC == TjiSzDDhut){ukMCPpxixq = true;}
      if(PoMjjgGHjk == kMghPOROhn){lcJzIJzZXw = true;}
      else if(kMghPOROhn == PoMjjgGHjk){nxPMdRscnM = true;}
      if(zqdFsogMCV == ddEbZhMwyD){xwNzgBdjkO = true;}
      else if(ddEbZhMwyD == zqdFsogMCV){tGSgRlfrmy = true;}
      if(eJfERIoJKd == eQYuyIxMVI){MyankKthcC = true;}
      else if(eQYuyIxMVI == eJfERIoJKd){ZcfqoJogpQ = true;}
      if(MzzjHBtamm == SyCAEndBks){NDgfyxGaAe = true;}
      else if(SyCAEndBks == MzzjHBtamm){UKyKshNXZP = true;}
      if(eFiBCcGdZK == CFsgXNhgkM){HtEflDeRwZ = true;}
      else if(CFsgXNhgkM == eFiBCcGdZK){rqynQnSfjd = true;}
      if(VqeYOFJHRb == ULeYWUnkjH){TciuemBUOy = true;}
      else if(ULeYWUnkjH == VqeYOFJHRb){JFuzRLRXXT = true;}
      if(rxxGYzqsxq == RFsYVfbEXk){ORwVitOgBj = true;}
      if(uGYPqZaeCo == DLLEAZWqXj){uCiGHRsuCg = true;}
      if(BKjAIUUaUC == ZPaJnGTcci){fckDhkTlBK = true;}
      while(RFsYVfbEXk == rxxGYzqsxq){cLlWriIHnj = true;}
      while(DLLEAZWqXj == DLLEAZWqXj){YHSWGieqaA = true;}
      while(ZPaJnGTcci == ZPaJnGTcci){qJwLGOOzsg = true;}
      if(ArQdaxMTKq == true){ArQdaxMTKq = false;}
      if(lcJzIJzZXw == true){lcJzIJzZXw = false;}
      if(xwNzgBdjkO == true){xwNzgBdjkO = false;}
      if(MyankKthcC == true){MyankKthcC = false;}
      if(NDgfyxGaAe == true){NDgfyxGaAe = false;}
      if(HtEflDeRwZ == true){HtEflDeRwZ = false;}
      if(TciuemBUOy == true){TciuemBUOy = false;}
      if(ORwVitOgBj == true){ORwVitOgBj = false;}
      if(uCiGHRsuCg == true){uCiGHRsuCg = false;}
      if(fckDhkTlBK == true){fckDhkTlBK = false;}
      if(ukMCPpxixq == true){ukMCPpxixq = false;}
      if(nxPMdRscnM == true){nxPMdRscnM = false;}
      if(tGSgRlfrmy == true){tGSgRlfrmy = false;}
      if(ZcfqoJogpQ == true){ZcfqoJogpQ = false;}
      if(UKyKshNXZP == true){UKyKshNXZP = false;}
      if(rqynQnSfjd == true){rqynQnSfjd = false;}
      if(JFuzRLRXXT == true){JFuzRLRXXT = false;}
      if(cLlWriIHnj == true){cLlWriIHnj = false;}
      if(YHSWGieqaA == true){YHSWGieqaA = false;}
      if(qJwLGOOzsg == true){qJwLGOOzsg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYSNXEKOKB
{ 
  void qlmUcSVxcP()
  { 
      bool uBxGZBzZdi = false;
      bool xIXMWNBlVA = false;
      bool grytfDxzWI = false;
      bool yVSRPsXXjL = false;
      bool ebHCtxdLlm = false;
      bool EfWpgCCCaV = false;
      bool EzDVkaoGxc = false;
      bool ocCJVFkuAh = false;
      bool ZkNiDSzcjM = false;
      bool pVwOHeXlRT = false;
      bool HWNJxacMTb = false;
      bool RGCruSlURS = false;
      bool aMVklTfmCq = false;
      bool hzdgZCXDlb = false;
      bool olIHujSESo = false;
      bool rCTyruAcWc = false;
      bool tpKbtScVRr = false;
      bool uiiodoDOoC = false;
      bool AbTMzeeene = false;
      bool CtfIgzbfMb = false;
      string lcSxQYJUYz;
      string rcEggozDOn;
      string dwzcAlcjNq;
      string MNokWMzVfk;
      string OzodKrQqdn;
      string RZOsxpdoxd;
      string wYHhlenTJT;
      string pcXdZeHUSH;
      string UlGYYmzwng;
      string iJYBooqGqf;
      string ExgJynCkTR;
      string iIWoJKSiIz;
      string ereckgEWnj;
      string mAdlDXEwZk;
      string kObVxZlire;
      string WIyrAMRDXR;
      string jewieieklk;
      string FVIXNQPJfK;
      string tVdJMdCllq;
      string FBYIBFSspO;
      if(lcSxQYJUYz == ExgJynCkTR){uBxGZBzZdi = true;}
      else if(ExgJynCkTR == lcSxQYJUYz){HWNJxacMTb = true;}
      if(rcEggozDOn == iIWoJKSiIz){xIXMWNBlVA = true;}
      else if(iIWoJKSiIz == rcEggozDOn){RGCruSlURS = true;}
      if(dwzcAlcjNq == ereckgEWnj){grytfDxzWI = true;}
      else if(ereckgEWnj == dwzcAlcjNq){aMVklTfmCq = true;}
      if(MNokWMzVfk == mAdlDXEwZk){yVSRPsXXjL = true;}
      else if(mAdlDXEwZk == MNokWMzVfk){hzdgZCXDlb = true;}
      if(OzodKrQqdn == kObVxZlire){ebHCtxdLlm = true;}
      else if(kObVxZlire == OzodKrQqdn){olIHujSESo = true;}
      if(RZOsxpdoxd == WIyrAMRDXR){EfWpgCCCaV = true;}
      else if(WIyrAMRDXR == RZOsxpdoxd){rCTyruAcWc = true;}
      if(wYHhlenTJT == jewieieklk){EzDVkaoGxc = true;}
      else if(jewieieklk == wYHhlenTJT){tpKbtScVRr = true;}
      if(pcXdZeHUSH == FVIXNQPJfK){ocCJVFkuAh = true;}
      if(UlGYYmzwng == tVdJMdCllq){ZkNiDSzcjM = true;}
      if(iJYBooqGqf == FBYIBFSspO){pVwOHeXlRT = true;}
      while(FVIXNQPJfK == pcXdZeHUSH){uiiodoDOoC = true;}
      while(tVdJMdCllq == tVdJMdCllq){AbTMzeeene = true;}
      while(FBYIBFSspO == FBYIBFSspO){CtfIgzbfMb = true;}
      if(uBxGZBzZdi == true){uBxGZBzZdi = false;}
      if(xIXMWNBlVA == true){xIXMWNBlVA = false;}
      if(grytfDxzWI == true){grytfDxzWI = false;}
      if(yVSRPsXXjL == true){yVSRPsXXjL = false;}
      if(ebHCtxdLlm == true){ebHCtxdLlm = false;}
      if(EfWpgCCCaV == true){EfWpgCCCaV = false;}
      if(EzDVkaoGxc == true){EzDVkaoGxc = false;}
      if(ocCJVFkuAh == true){ocCJVFkuAh = false;}
      if(ZkNiDSzcjM == true){ZkNiDSzcjM = false;}
      if(pVwOHeXlRT == true){pVwOHeXlRT = false;}
      if(HWNJxacMTb == true){HWNJxacMTb = false;}
      if(RGCruSlURS == true){RGCruSlURS = false;}
      if(aMVklTfmCq == true){aMVklTfmCq = false;}
      if(hzdgZCXDlb == true){hzdgZCXDlb = false;}
      if(olIHujSESo == true){olIHujSESo = false;}
      if(rCTyruAcWc == true){rCTyruAcWc = false;}
      if(tpKbtScVRr == true){tpKbtScVRr = false;}
      if(uiiodoDOoC == true){uiiodoDOoC = false;}
      if(AbTMzeeene == true){AbTMzeeene = false;}
      if(CtfIgzbfMb == true){CtfIgzbfMb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONTLMPFDSG
{ 
  void ikCOTrEizX()
  { 
      bool RoyHpFLInd = false;
      bool LRwPkGhSbr = false;
      bool cDCLzqBjMC = false;
      bool OakhcPZQpU = false;
      bool DoZznWCGeP = false;
      bool wWOKCNmmHy = false;
      bool EbwkPjgOlV = false;
      bool fRcGomdDWc = false;
      bool nuFxGqMaeO = false;
      bool bmIqQasnjD = false;
      bool onTIietHVP = false;
      bool jiPeKJWyeX = false;
      bool XFiXssIkpN = false;
      bool soTSmAawOb = false;
      bool xEFPdrWdgG = false;
      bool EuJLfjEuOo = false;
      bool VIRHVuPwqJ = false;
      bool hZjDaTASsA = false;
      bool VdEiIyeHmD = false;
      bool uegYFnlxth = false;
      string sPrLXtDPQN;
      string wzSHfmeHHp;
      string AEoKJrJdhM;
      string jCpbONwyJP;
      string FChQVutWHI;
      string uXCqhoagBf;
      string kYgDcsJqsS;
      string pfyqjxVXnO;
      string xlVYRLAzsZ;
      string mPxdefUenb;
      string lDdoROZLGj;
      string SCsmhyDHlR;
      string sJxTeaiTME;
      string bqjMbtIfHC;
      string korJGjVJuf;
      string cMrVibFJKp;
      string fGzCHaSfKn;
      string pWAigEQmMu;
      string FYXfaPyOdz;
      string nzVQWdppCe;
      if(sPrLXtDPQN == lDdoROZLGj){RoyHpFLInd = true;}
      else if(lDdoROZLGj == sPrLXtDPQN){onTIietHVP = true;}
      if(wzSHfmeHHp == SCsmhyDHlR){LRwPkGhSbr = true;}
      else if(SCsmhyDHlR == wzSHfmeHHp){jiPeKJWyeX = true;}
      if(AEoKJrJdhM == sJxTeaiTME){cDCLzqBjMC = true;}
      else if(sJxTeaiTME == AEoKJrJdhM){XFiXssIkpN = true;}
      if(jCpbONwyJP == bqjMbtIfHC){OakhcPZQpU = true;}
      else if(bqjMbtIfHC == jCpbONwyJP){soTSmAawOb = true;}
      if(FChQVutWHI == korJGjVJuf){DoZznWCGeP = true;}
      else if(korJGjVJuf == FChQVutWHI){xEFPdrWdgG = true;}
      if(uXCqhoagBf == cMrVibFJKp){wWOKCNmmHy = true;}
      else if(cMrVibFJKp == uXCqhoagBf){EuJLfjEuOo = true;}
      if(kYgDcsJqsS == fGzCHaSfKn){EbwkPjgOlV = true;}
      else if(fGzCHaSfKn == kYgDcsJqsS){VIRHVuPwqJ = true;}
      if(pfyqjxVXnO == pWAigEQmMu){fRcGomdDWc = true;}
      if(xlVYRLAzsZ == FYXfaPyOdz){nuFxGqMaeO = true;}
      if(mPxdefUenb == nzVQWdppCe){bmIqQasnjD = true;}
      while(pWAigEQmMu == pfyqjxVXnO){hZjDaTASsA = true;}
      while(FYXfaPyOdz == FYXfaPyOdz){VdEiIyeHmD = true;}
      while(nzVQWdppCe == nzVQWdppCe){uegYFnlxth = true;}
      if(RoyHpFLInd == true){RoyHpFLInd = false;}
      if(LRwPkGhSbr == true){LRwPkGhSbr = false;}
      if(cDCLzqBjMC == true){cDCLzqBjMC = false;}
      if(OakhcPZQpU == true){OakhcPZQpU = false;}
      if(DoZznWCGeP == true){DoZznWCGeP = false;}
      if(wWOKCNmmHy == true){wWOKCNmmHy = false;}
      if(EbwkPjgOlV == true){EbwkPjgOlV = false;}
      if(fRcGomdDWc == true){fRcGomdDWc = false;}
      if(nuFxGqMaeO == true){nuFxGqMaeO = false;}
      if(bmIqQasnjD == true){bmIqQasnjD = false;}
      if(onTIietHVP == true){onTIietHVP = false;}
      if(jiPeKJWyeX == true){jiPeKJWyeX = false;}
      if(XFiXssIkpN == true){XFiXssIkpN = false;}
      if(soTSmAawOb == true){soTSmAawOb = false;}
      if(xEFPdrWdgG == true){xEFPdrWdgG = false;}
      if(EuJLfjEuOo == true){EuJLfjEuOo = false;}
      if(VIRHVuPwqJ == true){VIRHVuPwqJ = false;}
      if(hZjDaTASsA == true){hZjDaTASsA = false;}
      if(VdEiIyeHmD == true){VdEiIyeHmD = false;}
      if(uegYFnlxth == true){uegYFnlxth = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSTWLELNUG
{ 
  void wCYkWIPSQH()
  { 
      bool JjQRzADHmA = false;
      bool SmySTiadwL = false;
      bool lCcinaFXwm = false;
      bool DhZeAxycJF = false;
      bool iCldMiYggr = false;
      bool efiaxGGhcX = false;
      bool ueLAxjMSSV = false;
      bool kyTpcjQzVF = false;
      bool CXqDHWzzgt = false;
      bool qQzlKDpkgc = false;
      bool VFOLHgMryN = false;
      bool oHLXUXnHra = false;
      bool kNlXeTzgfY = false;
      bool seSsiwIfwa = false;
      bool JHATFjEaRm = false;
      bool PhrFqITqfm = false;
      bool geLYTJoSnY = false;
      bool PHLRQdMRSu = false;
      bool PXPsILlMBa = false;
      bool bQzJseubAu = false;
      string PISWDqkcWn;
      string cNSnlkQkui;
      string aJLxJGPwYI;
      string tZSZYTQSFH;
      string fIqydWnXru;
      string pYhTdFxVNx;
      string anEOsDtrOS;
      string UyemDSSMTm;
      string RrEcRVryuT;
      string VtEIfqEcFZ;
      string bwIZarstPL;
      string mjCZfijbxW;
      string LwwuwZsWGM;
      string OpHsLUjdCZ;
      string cxhjglrebx;
      string GcfhOfzMdB;
      string yVmDxwcIOK;
      string yFYXtNNMOK;
      string gOtJGlKZef;
      string VWABaGKelj;
      if(PISWDqkcWn == bwIZarstPL){JjQRzADHmA = true;}
      else if(bwIZarstPL == PISWDqkcWn){VFOLHgMryN = true;}
      if(cNSnlkQkui == mjCZfijbxW){SmySTiadwL = true;}
      else if(mjCZfijbxW == cNSnlkQkui){oHLXUXnHra = true;}
      if(aJLxJGPwYI == LwwuwZsWGM){lCcinaFXwm = true;}
      else if(LwwuwZsWGM == aJLxJGPwYI){kNlXeTzgfY = true;}
      if(tZSZYTQSFH == OpHsLUjdCZ){DhZeAxycJF = true;}
      else if(OpHsLUjdCZ == tZSZYTQSFH){seSsiwIfwa = true;}
      if(fIqydWnXru == cxhjglrebx){iCldMiYggr = true;}
      else if(cxhjglrebx == fIqydWnXru){JHATFjEaRm = true;}
      if(pYhTdFxVNx == GcfhOfzMdB){efiaxGGhcX = true;}
      else if(GcfhOfzMdB == pYhTdFxVNx){PhrFqITqfm = true;}
      if(anEOsDtrOS == yVmDxwcIOK){ueLAxjMSSV = true;}
      else if(yVmDxwcIOK == anEOsDtrOS){geLYTJoSnY = true;}
      if(UyemDSSMTm == yFYXtNNMOK){kyTpcjQzVF = true;}
      if(RrEcRVryuT == gOtJGlKZef){CXqDHWzzgt = true;}
      if(VtEIfqEcFZ == VWABaGKelj){qQzlKDpkgc = true;}
      while(yFYXtNNMOK == UyemDSSMTm){PHLRQdMRSu = true;}
      while(gOtJGlKZef == gOtJGlKZef){PXPsILlMBa = true;}
      while(VWABaGKelj == VWABaGKelj){bQzJseubAu = true;}
      if(JjQRzADHmA == true){JjQRzADHmA = false;}
      if(SmySTiadwL == true){SmySTiadwL = false;}
      if(lCcinaFXwm == true){lCcinaFXwm = false;}
      if(DhZeAxycJF == true){DhZeAxycJF = false;}
      if(iCldMiYggr == true){iCldMiYggr = false;}
      if(efiaxGGhcX == true){efiaxGGhcX = false;}
      if(ueLAxjMSSV == true){ueLAxjMSSV = false;}
      if(kyTpcjQzVF == true){kyTpcjQzVF = false;}
      if(CXqDHWzzgt == true){CXqDHWzzgt = false;}
      if(qQzlKDpkgc == true){qQzlKDpkgc = false;}
      if(VFOLHgMryN == true){VFOLHgMryN = false;}
      if(oHLXUXnHra == true){oHLXUXnHra = false;}
      if(kNlXeTzgfY == true){kNlXeTzgfY = false;}
      if(seSsiwIfwa == true){seSsiwIfwa = false;}
      if(JHATFjEaRm == true){JHATFjEaRm = false;}
      if(PhrFqITqfm == true){PhrFqITqfm = false;}
      if(geLYTJoSnY == true){geLYTJoSnY = false;}
      if(PHLRQdMRSu == true){PHLRQdMRSu = false;}
      if(PXPsILlMBa == true){PXPsILlMBa = false;}
      if(bQzJseubAu == true){bQzJseubAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UPXGYIDAIS
{ 
  void qGcbpqAxIq()
  { 
      bool lnQOiFtsAh = false;
      bool sQUfrypQJo = false;
      bool GFXPCfNlnO = false;
      bool MOeHCyPBDG = false;
      bool lQwOoPJZNX = false;
      bool RVOOTgPBMD = false;
      bool qHEkVelNcs = false;
      bool hoNCDpIJal = false;
      bool VmYPwpzPmU = false;
      bool iOnAOdLKrJ = false;
      bool duwTocHMLc = false;
      bool XFZagEione = false;
      bool eVZHKTANmY = false;
      bool dxQQHaqFZT = false;
      bool ilEKxcnNSK = false;
      bool uWWNeIVnIV = false;
      bool ctZlzZoJSG = false;
      bool MdOUwsQPKg = false;
      bool eltbcHaDlz = false;
      bool ECwEpnMSKW = false;
      string qdkOhbbiRO;
      string hnRWHTrxyj;
      string niXjXbcKsb;
      string mVGqcSMTTi;
      string hEFoiukUmh;
      string zzxHZHGBpG;
      string zQoobMgaso;
      string GYcOBjdhBc;
      string qIXLcmXzQU;
      string MKcNjQPPMV;
      string NJaxaaWhFp;
      string dXANPqscMn;
      string ngJYcwwOej;
      string TNVeOggZkB;
      string QotaqnJOys;
      string XmDYggACUe;
      string eHDVWQCVyi;
      string JSrKXymihn;
      string lgQlLgJxxh;
      string gdFFWIlYEZ;
      if(qdkOhbbiRO == NJaxaaWhFp){lnQOiFtsAh = true;}
      else if(NJaxaaWhFp == qdkOhbbiRO){duwTocHMLc = true;}
      if(hnRWHTrxyj == dXANPqscMn){sQUfrypQJo = true;}
      else if(dXANPqscMn == hnRWHTrxyj){XFZagEione = true;}
      if(niXjXbcKsb == ngJYcwwOej){GFXPCfNlnO = true;}
      else if(ngJYcwwOej == niXjXbcKsb){eVZHKTANmY = true;}
      if(mVGqcSMTTi == TNVeOggZkB){MOeHCyPBDG = true;}
      else if(TNVeOggZkB == mVGqcSMTTi){dxQQHaqFZT = true;}
      if(hEFoiukUmh == QotaqnJOys){lQwOoPJZNX = true;}
      else if(QotaqnJOys == hEFoiukUmh){ilEKxcnNSK = true;}
      if(zzxHZHGBpG == XmDYggACUe){RVOOTgPBMD = true;}
      else if(XmDYggACUe == zzxHZHGBpG){uWWNeIVnIV = true;}
      if(zQoobMgaso == eHDVWQCVyi){qHEkVelNcs = true;}
      else if(eHDVWQCVyi == zQoobMgaso){ctZlzZoJSG = true;}
      if(GYcOBjdhBc == JSrKXymihn){hoNCDpIJal = true;}
      if(qIXLcmXzQU == lgQlLgJxxh){VmYPwpzPmU = true;}
      if(MKcNjQPPMV == gdFFWIlYEZ){iOnAOdLKrJ = true;}
      while(JSrKXymihn == GYcOBjdhBc){MdOUwsQPKg = true;}
      while(lgQlLgJxxh == lgQlLgJxxh){eltbcHaDlz = true;}
      while(gdFFWIlYEZ == gdFFWIlYEZ){ECwEpnMSKW = true;}
      if(lnQOiFtsAh == true){lnQOiFtsAh = false;}
      if(sQUfrypQJo == true){sQUfrypQJo = false;}
      if(GFXPCfNlnO == true){GFXPCfNlnO = false;}
      if(MOeHCyPBDG == true){MOeHCyPBDG = false;}
      if(lQwOoPJZNX == true){lQwOoPJZNX = false;}
      if(RVOOTgPBMD == true){RVOOTgPBMD = false;}
      if(qHEkVelNcs == true){qHEkVelNcs = false;}
      if(hoNCDpIJal == true){hoNCDpIJal = false;}
      if(VmYPwpzPmU == true){VmYPwpzPmU = false;}
      if(iOnAOdLKrJ == true){iOnAOdLKrJ = false;}
      if(duwTocHMLc == true){duwTocHMLc = false;}
      if(XFZagEione == true){XFZagEione = false;}
      if(eVZHKTANmY == true){eVZHKTANmY = false;}
      if(dxQQHaqFZT == true){dxQQHaqFZT = false;}
      if(ilEKxcnNSK == true){ilEKxcnNSK = false;}
      if(uWWNeIVnIV == true){uWWNeIVnIV = false;}
      if(ctZlzZoJSG == true){ctZlzZoJSG = false;}
      if(MdOUwsQPKg == true){MdOUwsQPKg = false;}
      if(eltbcHaDlz == true){eltbcHaDlz = false;}
      if(ECwEpnMSKW == true){ECwEpnMSKW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PFFSNMOWFK
{ 
  void HXBAfHHbbE()
  { 
      bool oeyKsLHiMN = false;
      bool JxaGnSdtkg = false;
      bool LOFtWMRdYW = false;
      bool lRZtpDgqKe = false;
      bool XtUYiBLjJy = false;
      bool cGxckaYEmg = false;
      bool sdKpbrWgPj = false;
      bool kmjFIQsgLU = false;
      bool AhUZteTxIP = false;
      bool ecDdktjewq = false;
      bool eeUYMoWrTT = false;
      bool grsRfLIjuw = false;
      bool YZXAFIiGUO = false;
      bool gOjTpUMuNE = false;
      bool IacohmjlxY = false;
      bool kzizREHTTE = false;
      bool FQXFlRHYaL = false;
      bool zNVpnxwiSS = false;
      bool XxIuchejCk = false;
      bool NsbJzqDXCP = false;
      string bMqRADTiXx;
      string MQjFhQbdBl;
      string ZBImEYxEmk;
      string eiFaBKHlMF;
      string UcSaOgAxZm;
      string FepFZZDDMb;
      string GPwlRcLJDX;
      string JpRwRxihXX;
      string XAdzfArzAb;
      string GDZjzFgfIk;
      string VqtCdPNtnc;
      string qVfnDGkxGR;
      string kLIbQGQhwL;
      string PCYmCgFbUP;
      string myLXkkXkfs;
      string UjZqAJhSkW;
      string yfxbMnwrlV;
      string AIbpdlAkqe;
      string ifBDqfchlr;
      string zmpxRHAiKw;
      if(bMqRADTiXx == VqtCdPNtnc){oeyKsLHiMN = true;}
      else if(VqtCdPNtnc == bMqRADTiXx){eeUYMoWrTT = true;}
      if(MQjFhQbdBl == qVfnDGkxGR){JxaGnSdtkg = true;}
      else if(qVfnDGkxGR == MQjFhQbdBl){grsRfLIjuw = true;}
      if(ZBImEYxEmk == kLIbQGQhwL){LOFtWMRdYW = true;}
      else if(kLIbQGQhwL == ZBImEYxEmk){YZXAFIiGUO = true;}
      if(eiFaBKHlMF == PCYmCgFbUP){lRZtpDgqKe = true;}
      else if(PCYmCgFbUP == eiFaBKHlMF){gOjTpUMuNE = true;}
      if(UcSaOgAxZm == myLXkkXkfs){XtUYiBLjJy = true;}
      else if(myLXkkXkfs == UcSaOgAxZm){IacohmjlxY = true;}
      if(FepFZZDDMb == UjZqAJhSkW){cGxckaYEmg = true;}
      else if(UjZqAJhSkW == FepFZZDDMb){kzizREHTTE = true;}
      if(GPwlRcLJDX == yfxbMnwrlV){sdKpbrWgPj = true;}
      else if(yfxbMnwrlV == GPwlRcLJDX){FQXFlRHYaL = true;}
      if(JpRwRxihXX == AIbpdlAkqe){kmjFIQsgLU = true;}
      if(XAdzfArzAb == ifBDqfchlr){AhUZteTxIP = true;}
      if(GDZjzFgfIk == zmpxRHAiKw){ecDdktjewq = true;}
      while(AIbpdlAkqe == JpRwRxihXX){zNVpnxwiSS = true;}
      while(ifBDqfchlr == ifBDqfchlr){XxIuchejCk = true;}
      while(zmpxRHAiKw == zmpxRHAiKw){NsbJzqDXCP = true;}
      if(oeyKsLHiMN == true){oeyKsLHiMN = false;}
      if(JxaGnSdtkg == true){JxaGnSdtkg = false;}
      if(LOFtWMRdYW == true){LOFtWMRdYW = false;}
      if(lRZtpDgqKe == true){lRZtpDgqKe = false;}
      if(XtUYiBLjJy == true){XtUYiBLjJy = false;}
      if(cGxckaYEmg == true){cGxckaYEmg = false;}
      if(sdKpbrWgPj == true){sdKpbrWgPj = false;}
      if(kmjFIQsgLU == true){kmjFIQsgLU = false;}
      if(AhUZteTxIP == true){AhUZteTxIP = false;}
      if(ecDdktjewq == true){ecDdktjewq = false;}
      if(eeUYMoWrTT == true){eeUYMoWrTT = false;}
      if(grsRfLIjuw == true){grsRfLIjuw = false;}
      if(YZXAFIiGUO == true){YZXAFIiGUO = false;}
      if(gOjTpUMuNE == true){gOjTpUMuNE = false;}
      if(IacohmjlxY == true){IacohmjlxY = false;}
      if(kzizREHTTE == true){kzizREHTTE = false;}
      if(FQXFlRHYaL == true){FQXFlRHYaL = false;}
      if(zNVpnxwiSS == true){zNVpnxwiSS = false;}
      if(XxIuchejCk == true){XxIuchejCk = false;}
      if(NsbJzqDXCP == true){NsbJzqDXCP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELUJLRPUKF
{ 
  void ZiQLgFijXs()
  { 
      bool KeQOIgWDuk = false;
      bool QIHpwxeMFq = false;
      bool sIHMoHBQcx = false;
      bool KITcLAkjtX = false;
      bool MICRlufYCz = false;
      bool ofCjsCXEYB = false;
      bool eFZxZHoeew = false;
      bool LuSgejFoas = false;
      bool acOcIeFiiJ = false;
      bool bgKsrGiFrd = false;
      bool GBtFmsNVEJ = false;
      bool whceZCpwot = false;
      bool BFwUTejYnY = false;
      bool BAxxmZiIoO = false;
      bool RjdZMsDfTp = false;
      bool PlPxbAFYkI = false;
      bool JngfIwkfrA = false;
      bool SgGZcRaWHZ = false;
      bool aEFxIOjzUl = false;
      bool TJXgFcCyRP = false;
      string VZjnVWMnak;
      string XCqQKuAnmB;
      string nmSpkIUtba;
      string kcltVokkWP;
      string IoydwhybTF;
      string xBuGuiHtDM;
      string BSMzztPwuU;
      string KPQWrznosC;
      string KsZVdihfzm;
      string hpgKNpczdB;
      string RBfzuhkYNw;
      string tRBACIrpVQ;
      string MjxIlThGIC;
      string VoLqkIMaZw;
      string yISCrQofIF;
      string xmcNohEXMb;
      string zdPKaFGJPs;
      string wQPZRDQuPV;
      string eByDFiLyCC;
      string EnOywUrIbm;
      if(VZjnVWMnak == RBfzuhkYNw){KeQOIgWDuk = true;}
      else if(RBfzuhkYNw == VZjnVWMnak){GBtFmsNVEJ = true;}
      if(XCqQKuAnmB == tRBACIrpVQ){QIHpwxeMFq = true;}
      else if(tRBACIrpVQ == XCqQKuAnmB){whceZCpwot = true;}
      if(nmSpkIUtba == MjxIlThGIC){sIHMoHBQcx = true;}
      else if(MjxIlThGIC == nmSpkIUtba){BFwUTejYnY = true;}
      if(kcltVokkWP == VoLqkIMaZw){KITcLAkjtX = true;}
      else if(VoLqkIMaZw == kcltVokkWP){BAxxmZiIoO = true;}
      if(IoydwhybTF == yISCrQofIF){MICRlufYCz = true;}
      else if(yISCrQofIF == IoydwhybTF){RjdZMsDfTp = true;}
      if(xBuGuiHtDM == xmcNohEXMb){ofCjsCXEYB = true;}
      else if(xmcNohEXMb == xBuGuiHtDM){PlPxbAFYkI = true;}
      if(BSMzztPwuU == zdPKaFGJPs){eFZxZHoeew = true;}
      else if(zdPKaFGJPs == BSMzztPwuU){JngfIwkfrA = true;}
      if(KPQWrznosC == wQPZRDQuPV){LuSgejFoas = true;}
      if(KsZVdihfzm == eByDFiLyCC){acOcIeFiiJ = true;}
      if(hpgKNpczdB == EnOywUrIbm){bgKsrGiFrd = true;}
      while(wQPZRDQuPV == KPQWrznosC){SgGZcRaWHZ = true;}
      while(eByDFiLyCC == eByDFiLyCC){aEFxIOjzUl = true;}
      while(EnOywUrIbm == EnOywUrIbm){TJXgFcCyRP = true;}
      if(KeQOIgWDuk == true){KeQOIgWDuk = false;}
      if(QIHpwxeMFq == true){QIHpwxeMFq = false;}
      if(sIHMoHBQcx == true){sIHMoHBQcx = false;}
      if(KITcLAkjtX == true){KITcLAkjtX = false;}
      if(MICRlufYCz == true){MICRlufYCz = false;}
      if(ofCjsCXEYB == true){ofCjsCXEYB = false;}
      if(eFZxZHoeew == true){eFZxZHoeew = false;}
      if(LuSgejFoas == true){LuSgejFoas = false;}
      if(acOcIeFiiJ == true){acOcIeFiiJ = false;}
      if(bgKsrGiFrd == true){bgKsrGiFrd = false;}
      if(GBtFmsNVEJ == true){GBtFmsNVEJ = false;}
      if(whceZCpwot == true){whceZCpwot = false;}
      if(BFwUTejYnY == true){BFwUTejYnY = false;}
      if(BAxxmZiIoO == true){BAxxmZiIoO = false;}
      if(RjdZMsDfTp == true){RjdZMsDfTp = false;}
      if(PlPxbAFYkI == true){PlPxbAFYkI = false;}
      if(JngfIwkfrA == true){JngfIwkfrA = false;}
      if(SgGZcRaWHZ == true){SgGZcRaWHZ = false;}
      if(aEFxIOjzUl == true){aEFxIOjzUl = false;}
      if(TJXgFcCyRP == true){TJXgFcCyRP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLAEPMUWGP
{ 
  void YOSznTrSgR()
  { 
      bool LLlbjQBaZF = false;
      bool aEwhMWXwBT = false;
      bool ECojiXbRfr = false;
      bool xdDBJBnQrl = false;
      bool AoGyoxcxVk = false;
      bool ZbfZYJWCrL = false;
      bool oitgHwAuXK = false;
      bool hGDOSPuqtl = false;
      bool tdutRUydbA = false;
      bool elXfxRuYps = false;
      bool whZLDSYQHJ = false;
      bool NeHGRLnzPm = false;
      bool xWSWfwhWRB = false;
      bool TWAAoLEjqz = false;
      bool wgVSmzdROk = false;
      bool cwJDwZOCfG = false;
      bool jBzFopeHRF = false;
      bool GEHPpPAAjf = false;
      bool RQIfXXMxEP = false;
      bool xCDkOthQcw = false;
      string PZMjFtCrBR;
      string wInXJSmZXs;
      string hVePrspKjk;
      string XAphsTYiPi;
      string EScOpDXiIk;
      string RiVVpsuwrL;
      string EqHQswSGdo;
      string tEKnoPrQYn;
      string VGCzTndTqz;
      string YbpDeMKMUt;
      string kQFTqMYgga;
      string AdXDpyoIwF;
      string SyOdPRNHJb;
      string EfueDEAhHH;
      string PwlQytEmNg;
      string XCPPalCaDY;
      string yRXFVUirAk;
      string xGAopVLyeV;
      string MasbDCPfDQ;
      string BYeiIxXgtd;
      if(PZMjFtCrBR == kQFTqMYgga){LLlbjQBaZF = true;}
      else if(kQFTqMYgga == PZMjFtCrBR){whZLDSYQHJ = true;}
      if(wInXJSmZXs == AdXDpyoIwF){aEwhMWXwBT = true;}
      else if(AdXDpyoIwF == wInXJSmZXs){NeHGRLnzPm = true;}
      if(hVePrspKjk == SyOdPRNHJb){ECojiXbRfr = true;}
      else if(SyOdPRNHJb == hVePrspKjk){xWSWfwhWRB = true;}
      if(XAphsTYiPi == EfueDEAhHH){xdDBJBnQrl = true;}
      else if(EfueDEAhHH == XAphsTYiPi){TWAAoLEjqz = true;}
      if(EScOpDXiIk == PwlQytEmNg){AoGyoxcxVk = true;}
      else if(PwlQytEmNg == EScOpDXiIk){wgVSmzdROk = true;}
      if(RiVVpsuwrL == XCPPalCaDY){ZbfZYJWCrL = true;}
      else if(XCPPalCaDY == RiVVpsuwrL){cwJDwZOCfG = true;}
      if(EqHQswSGdo == yRXFVUirAk){oitgHwAuXK = true;}
      else if(yRXFVUirAk == EqHQswSGdo){jBzFopeHRF = true;}
      if(tEKnoPrQYn == xGAopVLyeV){hGDOSPuqtl = true;}
      if(VGCzTndTqz == MasbDCPfDQ){tdutRUydbA = true;}
      if(YbpDeMKMUt == BYeiIxXgtd){elXfxRuYps = true;}
      while(xGAopVLyeV == tEKnoPrQYn){GEHPpPAAjf = true;}
      while(MasbDCPfDQ == MasbDCPfDQ){RQIfXXMxEP = true;}
      while(BYeiIxXgtd == BYeiIxXgtd){xCDkOthQcw = true;}
      if(LLlbjQBaZF == true){LLlbjQBaZF = false;}
      if(aEwhMWXwBT == true){aEwhMWXwBT = false;}
      if(ECojiXbRfr == true){ECojiXbRfr = false;}
      if(xdDBJBnQrl == true){xdDBJBnQrl = false;}
      if(AoGyoxcxVk == true){AoGyoxcxVk = false;}
      if(ZbfZYJWCrL == true){ZbfZYJWCrL = false;}
      if(oitgHwAuXK == true){oitgHwAuXK = false;}
      if(hGDOSPuqtl == true){hGDOSPuqtl = false;}
      if(tdutRUydbA == true){tdutRUydbA = false;}
      if(elXfxRuYps == true){elXfxRuYps = false;}
      if(whZLDSYQHJ == true){whZLDSYQHJ = false;}
      if(NeHGRLnzPm == true){NeHGRLnzPm = false;}
      if(xWSWfwhWRB == true){xWSWfwhWRB = false;}
      if(TWAAoLEjqz == true){TWAAoLEjqz = false;}
      if(wgVSmzdROk == true){wgVSmzdROk = false;}
      if(cwJDwZOCfG == true){cwJDwZOCfG = false;}
      if(jBzFopeHRF == true){jBzFopeHRF = false;}
      if(GEHPpPAAjf == true){GEHPpPAAjf = false;}
      if(RQIfXXMxEP == true){RQIfXXMxEP = false;}
      if(xCDkOthQcw == true){xCDkOthQcw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAUUSRORZM
{ 
  void ukpmmgtJhU()
  { 
      bool eWVynSCZqn = false;
      bool CBpsHMXFal = false;
      bool UwhmnUIyix = false;
      bool UwGTkEYDrk = false;
      bool ttjAkkgaMH = false;
      bool TqeDDiohKS = false;
      bool JDqtTGuWHD = false;
      bool mUNpqaMgCC = false;
      bool mgkaccQCPC = false;
      bool OqsYapDpfe = false;
      bool pKSJUzdoMc = false;
      bool VHfHfbRPRp = false;
      bool prGEnwbnOB = false;
      bool XVAWLbObGc = false;
      bool zapmgGKksy = false;
      bool YmXpnyENUY = false;
      bool XoZKEzHIwD = false;
      bool NpJnpOCSXh = false;
      bool kpuQbjyKhN = false;
      bool XAHgEJAehg = false;
      string brRqwlVfDL;
      string MBrJYOmWQd;
      string qeNwibrAxr;
      string jbyrzQgaHX;
      string ZcVPrwUynm;
      string NQrhQxeVHU;
      string sUiKbjDzJH;
      string gMOrENIxDl;
      string HtLKdTiPbC;
      string lLSmeEtKnI;
      string sUofFBBzdC;
      string nhRUNyIXgH;
      string BnWGVVsbNz;
      string SyIuslFfEc;
      string RikZOEsyZg;
      string uVdgGFyhKj;
      string HZleioYVba;
      string rcTDoRCxrQ;
      string buBfDxUbnn;
      string mXUUUrxGpY;
      if(brRqwlVfDL == sUofFBBzdC){eWVynSCZqn = true;}
      else if(sUofFBBzdC == brRqwlVfDL){pKSJUzdoMc = true;}
      if(MBrJYOmWQd == nhRUNyIXgH){CBpsHMXFal = true;}
      else if(nhRUNyIXgH == MBrJYOmWQd){VHfHfbRPRp = true;}
      if(qeNwibrAxr == BnWGVVsbNz){UwhmnUIyix = true;}
      else if(BnWGVVsbNz == qeNwibrAxr){prGEnwbnOB = true;}
      if(jbyrzQgaHX == SyIuslFfEc){UwGTkEYDrk = true;}
      else if(SyIuslFfEc == jbyrzQgaHX){XVAWLbObGc = true;}
      if(ZcVPrwUynm == RikZOEsyZg){ttjAkkgaMH = true;}
      else if(RikZOEsyZg == ZcVPrwUynm){zapmgGKksy = true;}
      if(NQrhQxeVHU == uVdgGFyhKj){TqeDDiohKS = true;}
      else if(uVdgGFyhKj == NQrhQxeVHU){YmXpnyENUY = true;}
      if(sUiKbjDzJH == HZleioYVba){JDqtTGuWHD = true;}
      else if(HZleioYVba == sUiKbjDzJH){XoZKEzHIwD = true;}
      if(gMOrENIxDl == rcTDoRCxrQ){mUNpqaMgCC = true;}
      if(HtLKdTiPbC == buBfDxUbnn){mgkaccQCPC = true;}
      if(lLSmeEtKnI == mXUUUrxGpY){OqsYapDpfe = true;}
      while(rcTDoRCxrQ == gMOrENIxDl){NpJnpOCSXh = true;}
      while(buBfDxUbnn == buBfDxUbnn){kpuQbjyKhN = true;}
      while(mXUUUrxGpY == mXUUUrxGpY){XAHgEJAehg = true;}
      if(eWVynSCZqn == true){eWVynSCZqn = false;}
      if(CBpsHMXFal == true){CBpsHMXFal = false;}
      if(UwhmnUIyix == true){UwhmnUIyix = false;}
      if(UwGTkEYDrk == true){UwGTkEYDrk = false;}
      if(ttjAkkgaMH == true){ttjAkkgaMH = false;}
      if(TqeDDiohKS == true){TqeDDiohKS = false;}
      if(JDqtTGuWHD == true){JDqtTGuWHD = false;}
      if(mUNpqaMgCC == true){mUNpqaMgCC = false;}
      if(mgkaccQCPC == true){mgkaccQCPC = false;}
      if(OqsYapDpfe == true){OqsYapDpfe = false;}
      if(pKSJUzdoMc == true){pKSJUzdoMc = false;}
      if(VHfHfbRPRp == true){VHfHfbRPRp = false;}
      if(prGEnwbnOB == true){prGEnwbnOB = false;}
      if(XVAWLbObGc == true){XVAWLbObGc = false;}
      if(zapmgGKksy == true){zapmgGKksy = false;}
      if(YmXpnyENUY == true){YmXpnyENUY = false;}
      if(XoZKEzHIwD == true){XoZKEzHIwD = false;}
      if(NpJnpOCSXh == true){NpJnpOCSXh = false;}
      if(kpuQbjyKhN == true){kpuQbjyKhN = false;}
      if(XAHgEJAehg == true){XAHgEJAehg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVNYILFZKI
{ 
  void pbxGEZPESg()
  { 
      bool GiiyeIZzrY = false;
      bool zDENuXuYtY = false;
      bool QPurweSleK = false;
      bool oSUKORFdwc = false;
      bool UaWflswYfD = false;
      bool sZlQbqnqBz = false;
      bool onUgjgisyd = false;
      bool RRcRDosOFD = false;
      bool itGbROfDhW = false;
      bool cNbwmgGouF = false;
      bool JCZCkbxUMl = false;
      bool xYkxPugrPV = false;
      bool AeKaAEogdW = false;
      bool iETAsgTEpp = false;
      bool RLquZEcdfr = false;
      bool zNYZEdqzBf = false;
      bool lPppCsFkEi = false;
      bool acBZEnnOBu = false;
      bool bLAkXVetuO = false;
      bool pUCJEBUBrf = false;
      string XgtFAiTOma;
      string mKByDhIKcQ;
      string UWhCADqgZs;
      string LKJVFXtesq;
      string bNsUfILmVU;
      string qHXTJAzqEw;
      string rlotPbAerf;
      string ncQkoHdMWq;
      string rDLEBDmpLF;
      string YDaxzoXyFD;
      string HgupgOqleC;
      string VlTNEnaksM;
      string oKSmHjCTlz;
      string ifHTiKIUXm;
      string MALJiliNrK;
      string OmFrOxNHiw;
      string MWAeTpeAdt;
      string fFNFAoyJDV;
      string BnbakuZOFk;
      string xAlaaozfor;
      if(XgtFAiTOma == HgupgOqleC){GiiyeIZzrY = true;}
      else if(HgupgOqleC == XgtFAiTOma){JCZCkbxUMl = true;}
      if(mKByDhIKcQ == VlTNEnaksM){zDENuXuYtY = true;}
      else if(VlTNEnaksM == mKByDhIKcQ){xYkxPugrPV = true;}
      if(UWhCADqgZs == oKSmHjCTlz){QPurweSleK = true;}
      else if(oKSmHjCTlz == UWhCADqgZs){AeKaAEogdW = true;}
      if(LKJVFXtesq == ifHTiKIUXm){oSUKORFdwc = true;}
      else if(ifHTiKIUXm == LKJVFXtesq){iETAsgTEpp = true;}
      if(bNsUfILmVU == MALJiliNrK){UaWflswYfD = true;}
      else if(MALJiliNrK == bNsUfILmVU){RLquZEcdfr = true;}
      if(qHXTJAzqEw == OmFrOxNHiw){sZlQbqnqBz = true;}
      else if(OmFrOxNHiw == qHXTJAzqEw){zNYZEdqzBf = true;}
      if(rlotPbAerf == MWAeTpeAdt){onUgjgisyd = true;}
      else if(MWAeTpeAdt == rlotPbAerf){lPppCsFkEi = true;}
      if(ncQkoHdMWq == fFNFAoyJDV){RRcRDosOFD = true;}
      if(rDLEBDmpLF == BnbakuZOFk){itGbROfDhW = true;}
      if(YDaxzoXyFD == xAlaaozfor){cNbwmgGouF = true;}
      while(fFNFAoyJDV == ncQkoHdMWq){acBZEnnOBu = true;}
      while(BnbakuZOFk == BnbakuZOFk){bLAkXVetuO = true;}
      while(xAlaaozfor == xAlaaozfor){pUCJEBUBrf = true;}
      if(GiiyeIZzrY == true){GiiyeIZzrY = false;}
      if(zDENuXuYtY == true){zDENuXuYtY = false;}
      if(QPurweSleK == true){QPurweSleK = false;}
      if(oSUKORFdwc == true){oSUKORFdwc = false;}
      if(UaWflswYfD == true){UaWflswYfD = false;}
      if(sZlQbqnqBz == true){sZlQbqnqBz = false;}
      if(onUgjgisyd == true){onUgjgisyd = false;}
      if(RRcRDosOFD == true){RRcRDosOFD = false;}
      if(itGbROfDhW == true){itGbROfDhW = false;}
      if(cNbwmgGouF == true){cNbwmgGouF = false;}
      if(JCZCkbxUMl == true){JCZCkbxUMl = false;}
      if(xYkxPugrPV == true){xYkxPugrPV = false;}
      if(AeKaAEogdW == true){AeKaAEogdW = false;}
      if(iETAsgTEpp == true){iETAsgTEpp = false;}
      if(RLquZEcdfr == true){RLquZEcdfr = false;}
      if(zNYZEdqzBf == true){zNYZEdqzBf = false;}
      if(lPppCsFkEi == true){lPppCsFkEi = false;}
      if(acBZEnnOBu == true){acBZEnnOBu = false;}
      if(bLAkXVetuO == true){bLAkXVetuO = false;}
      if(pUCJEBUBrf == true){pUCJEBUBrf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQZMFFTZSL
{ 
  void YSeaFrWpxB()
  { 
      bool UMLAKBrTnZ = false;
      bool qyiAnSBzGz = false;
      bool EhoCwxHkVW = false;
      bool AEpEsUPRwY = false;
      bool YBFtnBboRj = false;
      bool PXZNJmWIDM = false;
      bool sHxQYlHdGS = false;
      bool CjDhaDctOu = false;
      bool VRSlHcdctG = false;
      bool xHNieRDoVB = false;
      bool sxhygfUrlG = false;
      bool KctIqanLIw = false;
      bool HeiAVuVUCJ = false;
      bool znYMCYiUEb = false;
      bool IlpnwUNFqD = false;
      bool crfYsNNhcl = false;
      bool JzocHWDgFS = false;
      bool qSGgnVouDB = false;
      bool gQczfGIzTo = false;
      bool KArSRIwMfZ = false;
      string mpexVBzuSC;
      string MLcVbCPinH;
      string NYSgYoLQdi;
      string KBuEnSyJZb;
      string iPxtMpGqjd;
      string VqrdMNWyYf;
      string ohQirLPYhI;
      string EFIMYxaYUh;
      string iUfANSJRra;
      string wAjtmAyNBA;
      string ZhIbYPhfEO;
      string lydpxTBQVY;
      string CxfHMEVOYY;
      string yMWTHBLEax;
      string kdMcnxWswS;
      string yhrcybBBOU;
      string tTGfPZbJhw;
      string HxpYnXkDSO;
      string gbRGZQUsUf;
      string zKoFCQXfMO;
      if(mpexVBzuSC == ZhIbYPhfEO){UMLAKBrTnZ = true;}
      else if(ZhIbYPhfEO == mpexVBzuSC){sxhygfUrlG = true;}
      if(MLcVbCPinH == lydpxTBQVY){qyiAnSBzGz = true;}
      else if(lydpxTBQVY == MLcVbCPinH){KctIqanLIw = true;}
      if(NYSgYoLQdi == CxfHMEVOYY){EhoCwxHkVW = true;}
      else if(CxfHMEVOYY == NYSgYoLQdi){HeiAVuVUCJ = true;}
      if(KBuEnSyJZb == yMWTHBLEax){AEpEsUPRwY = true;}
      else if(yMWTHBLEax == KBuEnSyJZb){znYMCYiUEb = true;}
      if(iPxtMpGqjd == kdMcnxWswS){YBFtnBboRj = true;}
      else if(kdMcnxWswS == iPxtMpGqjd){IlpnwUNFqD = true;}
      if(VqrdMNWyYf == yhrcybBBOU){PXZNJmWIDM = true;}
      else if(yhrcybBBOU == VqrdMNWyYf){crfYsNNhcl = true;}
      if(ohQirLPYhI == tTGfPZbJhw){sHxQYlHdGS = true;}
      else if(tTGfPZbJhw == ohQirLPYhI){JzocHWDgFS = true;}
      if(EFIMYxaYUh == HxpYnXkDSO){CjDhaDctOu = true;}
      if(iUfANSJRra == gbRGZQUsUf){VRSlHcdctG = true;}
      if(wAjtmAyNBA == zKoFCQXfMO){xHNieRDoVB = true;}
      while(HxpYnXkDSO == EFIMYxaYUh){qSGgnVouDB = true;}
      while(gbRGZQUsUf == gbRGZQUsUf){gQczfGIzTo = true;}
      while(zKoFCQXfMO == zKoFCQXfMO){KArSRIwMfZ = true;}
      if(UMLAKBrTnZ == true){UMLAKBrTnZ = false;}
      if(qyiAnSBzGz == true){qyiAnSBzGz = false;}
      if(EhoCwxHkVW == true){EhoCwxHkVW = false;}
      if(AEpEsUPRwY == true){AEpEsUPRwY = false;}
      if(YBFtnBboRj == true){YBFtnBboRj = false;}
      if(PXZNJmWIDM == true){PXZNJmWIDM = false;}
      if(sHxQYlHdGS == true){sHxQYlHdGS = false;}
      if(CjDhaDctOu == true){CjDhaDctOu = false;}
      if(VRSlHcdctG == true){VRSlHcdctG = false;}
      if(xHNieRDoVB == true){xHNieRDoVB = false;}
      if(sxhygfUrlG == true){sxhygfUrlG = false;}
      if(KctIqanLIw == true){KctIqanLIw = false;}
      if(HeiAVuVUCJ == true){HeiAVuVUCJ = false;}
      if(znYMCYiUEb == true){znYMCYiUEb = false;}
      if(IlpnwUNFqD == true){IlpnwUNFqD = false;}
      if(crfYsNNhcl == true){crfYsNNhcl = false;}
      if(JzocHWDgFS == true){JzocHWDgFS = false;}
      if(qSGgnVouDB == true){qSGgnVouDB = false;}
      if(gQczfGIzTo == true){gQczfGIzTo = false;}
      if(KArSRIwMfZ == true){KArSRIwMfZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJYBMUVCCZ
{ 
  void IWxuNVSuhu()
  { 
      bool XoSNgQEJKy = false;
      bool gLqCqtMgeF = false;
      bool ZouWOdOVDl = false;
      bool OKfEbXVRSu = false;
      bool WFUpAlUIEh = false;
      bool ZJNbqitwzD = false;
      bool BhFYjWfmaS = false;
      bool YtOihUUFVc = false;
      bool JFRVMExDMs = false;
      bool dZSPsozwFd = false;
      bool FhhkJeudtW = false;
      bool NoZWswPjMe = false;
      bool YcZhoybzpr = false;
      bool UYzrWbXfMg = false;
      bool JTJoenAwVx = false;
      bool YOiaEbHAwK = false;
      bool CwnBBopgzR = false;
      bool YjXeVFTjCA = false;
      bool xfcrSGoYnu = false;
      bool TWjBeMeIno = false;
      string xCkwGEaqHT;
      string FegDiIKiVO;
      string mSRaixcbfH;
      string otKKcNOGTM;
      string eAhQwrXPRl;
      string AMOeRdjJMJ;
      string azLAeKTVaV;
      string sEPIilkAep;
      string YMKsHbefsy;
      string cFsJkfnglk;
      string YBousuxFue;
      string rjeVjNoSrC;
      string fnbbsnLFXD;
      string xDOtRXXOAM;
      string dZjOGsZWZW;
      string qVoiFjZMCE;
      string jrhqgnUjEM;
      string oZRfXGDNVA;
      string NoeAMbOfog;
      string yLLuclqrhR;
      if(xCkwGEaqHT == YBousuxFue){XoSNgQEJKy = true;}
      else if(YBousuxFue == xCkwGEaqHT){FhhkJeudtW = true;}
      if(FegDiIKiVO == rjeVjNoSrC){gLqCqtMgeF = true;}
      else if(rjeVjNoSrC == FegDiIKiVO){NoZWswPjMe = true;}
      if(mSRaixcbfH == fnbbsnLFXD){ZouWOdOVDl = true;}
      else if(fnbbsnLFXD == mSRaixcbfH){YcZhoybzpr = true;}
      if(otKKcNOGTM == xDOtRXXOAM){OKfEbXVRSu = true;}
      else if(xDOtRXXOAM == otKKcNOGTM){UYzrWbXfMg = true;}
      if(eAhQwrXPRl == dZjOGsZWZW){WFUpAlUIEh = true;}
      else if(dZjOGsZWZW == eAhQwrXPRl){JTJoenAwVx = true;}
      if(AMOeRdjJMJ == qVoiFjZMCE){ZJNbqitwzD = true;}
      else if(qVoiFjZMCE == AMOeRdjJMJ){YOiaEbHAwK = true;}
      if(azLAeKTVaV == jrhqgnUjEM){BhFYjWfmaS = true;}
      else if(jrhqgnUjEM == azLAeKTVaV){CwnBBopgzR = true;}
      if(sEPIilkAep == oZRfXGDNVA){YtOihUUFVc = true;}
      if(YMKsHbefsy == NoeAMbOfog){JFRVMExDMs = true;}
      if(cFsJkfnglk == yLLuclqrhR){dZSPsozwFd = true;}
      while(oZRfXGDNVA == sEPIilkAep){YjXeVFTjCA = true;}
      while(NoeAMbOfog == NoeAMbOfog){xfcrSGoYnu = true;}
      while(yLLuclqrhR == yLLuclqrhR){TWjBeMeIno = true;}
      if(XoSNgQEJKy == true){XoSNgQEJKy = false;}
      if(gLqCqtMgeF == true){gLqCqtMgeF = false;}
      if(ZouWOdOVDl == true){ZouWOdOVDl = false;}
      if(OKfEbXVRSu == true){OKfEbXVRSu = false;}
      if(WFUpAlUIEh == true){WFUpAlUIEh = false;}
      if(ZJNbqitwzD == true){ZJNbqitwzD = false;}
      if(BhFYjWfmaS == true){BhFYjWfmaS = false;}
      if(YtOihUUFVc == true){YtOihUUFVc = false;}
      if(JFRVMExDMs == true){JFRVMExDMs = false;}
      if(dZSPsozwFd == true){dZSPsozwFd = false;}
      if(FhhkJeudtW == true){FhhkJeudtW = false;}
      if(NoZWswPjMe == true){NoZWswPjMe = false;}
      if(YcZhoybzpr == true){YcZhoybzpr = false;}
      if(UYzrWbXfMg == true){UYzrWbXfMg = false;}
      if(JTJoenAwVx == true){JTJoenAwVx = false;}
      if(YOiaEbHAwK == true){YOiaEbHAwK = false;}
      if(CwnBBopgzR == true){CwnBBopgzR = false;}
      if(YjXeVFTjCA == true){YjXeVFTjCA = false;}
      if(xfcrSGoYnu == true){xfcrSGoYnu = false;}
      if(TWjBeMeIno == true){TWjBeMeIno = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQLSRXRPUK
{ 
  void gZNfipyXeu()
  { 
      bool XiWkTWgVkg = false;
      bool ZSEtVPfWJH = false;
      bool GcdJDBxbwn = false;
      bool zesjbhkMsy = false;
      bool gJCtjTtnjs = false;
      bool FVurDtFMhS = false;
      bool YFYwhtZTRn = false;
      bool eSdKaxZiZj = false;
      bool HJqDidjBgg = false;
      bool cXeZZajGLp = false;
      bool tZVwNlqjRG = false;
      bool TVmyLONVME = false;
      bool KXmjLHnDkz = false;
      bool MTXjogmuox = false;
      bool lzjZMGjfOK = false;
      bool MOtHfVmkkG = false;
      bool ymyRtAyDId = false;
      bool aSfOSKnMWE = false;
      bool WHnalyYQET = false;
      bool tCKizyARfM = false;
      string DMFTGAHsBV;
      string PaZrHyscyM;
      string YjBChnOmeG;
      string PDVoJOxPjC;
      string eEKFHjMYbs;
      string BwLjTSKCkR;
      string lTNtGMFjhr;
      string AdruhTYwuy;
      string boLlFSrkUp;
      string DudRPKpQyt;
      string dbqirXEPBz;
      string tOGmpxIbnn;
      string UTPqoFzZeW;
      string cHxBTzxbsh;
      string OciVwonqbS;
      string CObKZJMztm;
      string XdjdVlQFTp;
      string zfhGYrjsuA;
      string QIyMUNembJ;
      string myhGJksFzK;
      if(DMFTGAHsBV == dbqirXEPBz){XiWkTWgVkg = true;}
      else if(dbqirXEPBz == DMFTGAHsBV){tZVwNlqjRG = true;}
      if(PaZrHyscyM == tOGmpxIbnn){ZSEtVPfWJH = true;}
      else if(tOGmpxIbnn == PaZrHyscyM){TVmyLONVME = true;}
      if(YjBChnOmeG == UTPqoFzZeW){GcdJDBxbwn = true;}
      else if(UTPqoFzZeW == YjBChnOmeG){KXmjLHnDkz = true;}
      if(PDVoJOxPjC == cHxBTzxbsh){zesjbhkMsy = true;}
      else if(cHxBTzxbsh == PDVoJOxPjC){MTXjogmuox = true;}
      if(eEKFHjMYbs == OciVwonqbS){gJCtjTtnjs = true;}
      else if(OciVwonqbS == eEKFHjMYbs){lzjZMGjfOK = true;}
      if(BwLjTSKCkR == CObKZJMztm){FVurDtFMhS = true;}
      else if(CObKZJMztm == BwLjTSKCkR){MOtHfVmkkG = true;}
      if(lTNtGMFjhr == XdjdVlQFTp){YFYwhtZTRn = true;}
      else if(XdjdVlQFTp == lTNtGMFjhr){ymyRtAyDId = true;}
      if(AdruhTYwuy == zfhGYrjsuA){eSdKaxZiZj = true;}
      if(boLlFSrkUp == QIyMUNembJ){HJqDidjBgg = true;}
      if(DudRPKpQyt == myhGJksFzK){cXeZZajGLp = true;}
      while(zfhGYrjsuA == AdruhTYwuy){aSfOSKnMWE = true;}
      while(QIyMUNembJ == QIyMUNembJ){WHnalyYQET = true;}
      while(myhGJksFzK == myhGJksFzK){tCKizyARfM = true;}
      if(XiWkTWgVkg == true){XiWkTWgVkg = false;}
      if(ZSEtVPfWJH == true){ZSEtVPfWJH = false;}
      if(GcdJDBxbwn == true){GcdJDBxbwn = false;}
      if(zesjbhkMsy == true){zesjbhkMsy = false;}
      if(gJCtjTtnjs == true){gJCtjTtnjs = false;}
      if(FVurDtFMhS == true){FVurDtFMhS = false;}
      if(YFYwhtZTRn == true){YFYwhtZTRn = false;}
      if(eSdKaxZiZj == true){eSdKaxZiZj = false;}
      if(HJqDidjBgg == true){HJqDidjBgg = false;}
      if(cXeZZajGLp == true){cXeZZajGLp = false;}
      if(tZVwNlqjRG == true){tZVwNlqjRG = false;}
      if(TVmyLONVME == true){TVmyLONVME = false;}
      if(KXmjLHnDkz == true){KXmjLHnDkz = false;}
      if(MTXjogmuox == true){MTXjogmuox = false;}
      if(lzjZMGjfOK == true){lzjZMGjfOK = false;}
      if(MOtHfVmkkG == true){MOtHfVmkkG = false;}
      if(ymyRtAyDId == true){ymyRtAyDId = false;}
      if(aSfOSKnMWE == true){aSfOSKnMWE = false;}
      if(WHnalyYQET == true){WHnalyYQET = false;}
      if(tCKizyARfM == true){tCKizyARfM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSJUGXRHLD
{ 
  void ZrabuZuxMg()
  { 
      bool lMUABkdTOY = false;
      bool GgSrGKxJQR = false;
      bool pReXBpBKES = false;
      bool zVqcjiRXSo = false;
      bool znPsXZBWmR = false;
      bool xVNRtUhxzL = false;
      bool jSPuYjpoHW = false;
      bool sYpaRCClza = false;
      bool neXmUcIYiP = false;
      bool ATYGFfYTTm = false;
      bool jLOQXYflzq = false;
      bool RwxXWEubZw = false;
      bool bRFrVZzjUl = false;
      bool ciRLqcQGPw = false;
      bool xVYqxEWAiB = false;
      bool jwsWLSFVty = false;
      bool YuRNNidkgt = false;
      bool nnMdzFrNuR = false;
      bool CyATBgouAX = false;
      bool WtMQWBEKdN = false;
      string sorLhqqBsg;
      string otiQtkjrME;
      string oPVNHhCDtF;
      string ighqXEEPeK;
      string hqwGBqFWIo;
      string ZPMqEdSdEz;
      string onGmyIMrrp;
      string fTMBWxTPMP;
      string beuFfTTplt;
      string kaLfVtjIIr;
      string dNeSIFCKUH;
      string JDQnWJrBHe;
      string nWFyEFIgfc;
      string MKHUlOAcwZ;
      string QJVejhJWIL;
      string BiBcDHHfNC;
      string xVdquzwwCI;
      string JPEgOeAaNV;
      string wlYUacIdRe;
      string HTOtcufdjj;
      if(sorLhqqBsg == dNeSIFCKUH){lMUABkdTOY = true;}
      else if(dNeSIFCKUH == sorLhqqBsg){jLOQXYflzq = true;}
      if(otiQtkjrME == JDQnWJrBHe){GgSrGKxJQR = true;}
      else if(JDQnWJrBHe == otiQtkjrME){RwxXWEubZw = true;}
      if(oPVNHhCDtF == nWFyEFIgfc){pReXBpBKES = true;}
      else if(nWFyEFIgfc == oPVNHhCDtF){bRFrVZzjUl = true;}
      if(ighqXEEPeK == MKHUlOAcwZ){zVqcjiRXSo = true;}
      else if(MKHUlOAcwZ == ighqXEEPeK){ciRLqcQGPw = true;}
      if(hqwGBqFWIo == QJVejhJWIL){znPsXZBWmR = true;}
      else if(QJVejhJWIL == hqwGBqFWIo){xVYqxEWAiB = true;}
      if(ZPMqEdSdEz == BiBcDHHfNC){xVNRtUhxzL = true;}
      else if(BiBcDHHfNC == ZPMqEdSdEz){jwsWLSFVty = true;}
      if(onGmyIMrrp == xVdquzwwCI){jSPuYjpoHW = true;}
      else if(xVdquzwwCI == onGmyIMrrp){YuRNNidkgt = true;}
      if(fTMBWxTPMP == JPEgOeAaNV){sYpaRCClza = true;}
      if(beuFfTTplt == wlYUacIdRe){neXmUcIYiP = true;}
      if(kaLfVtjIIr == HTOtcufdjj){ATYGFfYTTm = true;}
      while(JPEgOeAaNV == fTMBWxTPMP){nnMdzFrNuR = true;}
      while(wlYUacIdRe == wlYUacIdRe){CyATBgouAX = true;}
      while(HTOtcufdjj == HTOtcufdjj){WtMQWBEKdN = true;}
      if(lMUABkdTOY == true){lMUABkdTOY = false;}
      if(GgSrGKxJQR == true){GgSrGKxJQR = false;}
      if(pReXBpBKES == true){pReXBpBKES = false;}
      if(zVqcjiRXSo == true){zVqcjiRXSo = false;}
      if(znPsXZBWmR == true){znPsXZBWmR = false;}
      if(xVNRtUhxzL == true){xVNRtUhxzL = false;}
      if(jSPuYjpoHW == true){jSPuYjpoHW = false;}
      if(sYpaRCClza == true){sYpaRCClza = false;}
      if(neXmUcIYiP == true){neXmUcIYiP = false;}
      if(ATYGFfYTTm == true){ATYGFfYTTm = false;}
      if(jLOQXYflzq == true){jLOQXYflzq = false;}
      if(RwxXWEubZw == true){RwxXWEubZw = false;}
      if(bRFrVZzjUl == true){bRFrVZzjUl = false;}
      if(ciRLqcQGPw == true){ciRLqcQGPw = false;}
      if(xVYqxEWAiB == true){xVYqxEWAiB = false;}
      if(jwsWLSFVty == true){jwsWLSFVty = false;}
      if(YuRNNidkgt == true){YuRNNidkgt = false;}
      if(nnMdzFrNuR == true){nnMdzFrNuR = false;}
      if(CyATBgouAX == true){CyATBgouAX = false;}
      if(WtMQWBEKdN == true){WtMQWBEKdN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBVNZGOWUL
{ 
  void EQoHfNToFT()
  { 
      bool NInRwattbd = false;
      bool mdLgOyUTKl = false;
      bool gKURZwuxCg = false;
      bool lnDDpdymDl = false;
      bool FsqAueffGy = false;
      bool XoFjXCmVrA = false;
      bool fxrtryZIpj = false;
      bool AhPXgnSTWu = false;
      bool PPpDJwiSfn = false;
      bool qbtDGHAwIx = false;
      bool EXoWypYgDi = false;
      bool iSzxjQHnku = false;
      bool OHbCsXmMQY = false;
      bool mWLZqqZTFS = false;
      bool WCPwEXcxSp = false;
      bool ALKNhwwmca = false;
      bool DMPduMHZFs = false;
      bool qniSXMqexV = false;
      bool tpsaYbLxqt = false;
      bool ulpePKlkBr = false;
      string ZPJZonnfTU;
      string UWWtyZdzbR;
      string XOzFspXBYq;
      string fMUalJQrwD;
      string cIEiEklJVF;
      string xhdKPLQEfz;
      string PlHcoHCwHo;
      string IlDYnOJPAI;
      string DOeStxiJLa;
      string rMLxmqBbtx;
      string ipBgxLeFVA;
      string BADXwBGnhr;
      string XrkgwuZFkx;
      string NgVDYNMyVi;
      string RcnKYrImAk;
      string jMtCYqETkB;
      string kYTXmUeAzi;
      string oIRzZuEaIE;
      string mlEANAmTeh;
      string IrMUxrIPWE;
      if(ZPJZonnfTU == ipBgxLeFVA){NInRwattbd = true;}
      else if(ipBgxLeFVA == ZPJZonnfTU){EXoWypYgDi = true;}
      if(UWWtyZdzbR == BADXwBGnhr){mdLgOyUTKl = true;}
      else if(BADXwBGnhr == UWWtyZdzbR){iSzxjQHnku = true;}
      if(XOzFspXBYq == XrkgwuZFkx){gKURZwuxCg = true;}
      else if(XrkgwuZFkx == XOzFspXBYq){OHbCsXmMQY = true;}
      if(fMUalJQrwD == NgVDYNMyVi){lnDDpdymDl = true;}
      else if(NgVDYNMyVi == fMUalJQrwD){mWLZqqZTFS = true;}
      if(cIEiEklJVF == RcnKYrImAk){FsqAueffGy = true;}
      else if(RcnKYrImAk == cIEiEklJVF){WCPwEXcxSp = true;}
      if(xhdKPLQEfz == jMtCYqETkB){XoFjXCmVrA = true;}
      else if(jMtCYqETkB == xhdKPLQEfz){ALKNhwwmca = true;}
      if(PlHcoHCwHo == kYTXmUeAzi){fxrtryZIpj = true;}
      else if(kYTXmUeAzi == PlHcoHCwHo){DMPduMHZFs = true;}
      if(IlDYnOJPAI == oIRzZuEaIE){AhPXgnSTWu = true;}
      if(DOeStxiJLa == mlEANAmTeh){PPpDJwiSfn = true;}
      if(rMLxmqBbtx == IrMUxrIPWE){qbtDGHAwIx = true;}
      while(oIRzZuEaIE == IlDYnOJPAI){qniSXMqexV = true;}
      while(mlEANAmTeh == mlEANAmTeh){tpsaYbLxqt = true;}
      while(IrMUxrIPWE == IrMUxrIPWE){ulpePKlkBr = true;}
      if(NInRwattbd == true){NInRwattbd = false;}
      if(mdLgOyUTKl == true){mdLgOyUTKl = false;}
      if(gKURZwuxCg == true){gKURZwuxCg = false;}
      if(lnDDpdymDl == true){lnDDpdymDl = false;}
      if(FsqAueffGy == true){FsqAueffGy = false;}
      if(XoFjXCmVrA == true){XoFjXCmVrA = false;}
      if(fxrtryZIpj == true){fxrtryZIpj = false;}
      if(AhPXgnSTWu == true){AhPXgnSTWu = false;}
      if(PPpDJwiSfn == true){PPpDJwiSfn = false;}
      if(qbtDGHAwIx == true){qbtDGHAwIx = false;}
      if(EXoWypYgDi == true){EXoWypYgDi = false;}
      if(iSzxjQHnku == true){iSzxjQHnku = false;}
      if(OHbCsXmMQY == true){OHbCsXmMQY = false;}
      if(mWLZqqZTFS == true){mWLZqqZTFS = false;}
      if(WCPwEXcxSp == true){WCPwEXcxSp = false;}
      if(ALKNhwwmca == true){ALKNhwwmca = false;}
      if(DMPduMHZFs == true){DMPduMHZFs = false;}
      if(qniSXMqexV == true){qniSXMqexV = false;}
      if(tpsaYbLxqt == true){tpsaYbLxqt = false;}
      if(ulpePKlkBr == true){ulpePKlkBr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLLPMIPNXU
{ 
  void btAgBdxNCw()
  { 
      bool WNbGSDxKzi = false;
      bool wzLzsNIpaD = false;
      bool bHEbjyXNWl = false;
      bool pGpsydOaDP = false;
      bool DyZVpmTexS = false;
      bool nBcOiOJzVT = false;
      bool fjmNsoIRAP = false;
      bool yhmKzdhhkw = false;
      bool dsQEyocbKj = false;
      bool TOEijTLMcB = false;
      bool dCdgTGNRPE = false;
      bool fbOZplShOE = false;
      bool LgGQwjcEaf = false;
      bool SVFjSbOjjr = false;
      bool aLMFDrAesx = false;
      bool AcxXowuNkj = false;
      bool cJqilKVdHN = false;
      bool XiyWcAUBMD = false;
      bool iyLcfoXguV = false;
      bool fByzORUcTr = false;
      string VaGStaxJwz;
      string kwprOauHHc;
      string inXBBokEyl;
      string rMTdlwIPBN;
      string xuNLbrCXMT;
      string QFazxhCFQF;
      string orLKHXcMFS;
      string SfGsenZMYI;
      string lNrdVllTfE;
      string sDywYFjDED;
      string PpRsBkzgUI;
      string HofHSazgoV;
      string lJgBYPgJTZ;
      string EWIVswwycj;
      string lEyWwDXpcx;
      string FCOiQGIQUl;
      string DoMuEkgJOW;
      string eBEEigKJEU;
      string rpgWTBIYFm;
      string mfdqgwqDSL;
      if(VaGStaxJwz == PpRsBkzgUI){WNbGSDxKzi = true;}
      else if(PpRsBkzgUI == VaGStaxJwz){dCdgTGNRPE = true;}
      if(kwprOauHHc == HofHSazgoV){wzLzsNIpaD = true;}
      else if(HofHSazgoV == kwprOauHHc){fbOZplShOE = true;}
      if(inXBBokEyl == lJgBYPgJTZ){bHEbjyXNWl = true;}
      else if(lJgBYPgJTZ == inXBBokEyl){LgGQwjcEaf = true;}
      if(rMTdlwIPBN == EWIVswwycj){pGpsydOaDP = true;}
      else if(EWIVswwycj == rMTdlwIPBN){SVFjSbOjjr = true;}
      if(xuNLbrCXMT == lEyWwDXpcx){DyZVpmTexS = true;}
      else if(lEyWwDXpcx == xuNLbrCXMT){aLMFDrAesx = true;}
      if(QFazxhCFQF == FCOiQGIQUl){nBcOiOJzVT = true;}
      else if(FCOiQGIQUl == QFazxhCFQF){AcxXowuNkj = true;}
      if(orLKHXcMFS == DoMuEkgJOW){fjmNsoIRAP = true;}
      else if(DoMuEkgJOW == orLKHXcMFS){cJqilKVdHN = true;}
      if(SfGsenZMYI == eBEEigKJEU){yhmKzdhhkw = true;}
      if(lNrdVllTfE == rpgWTBIYFm){dsQEyocbKj = true;}
      if(sDywYFjDED == mfdqgwqDSL){TOEijTLMcB = true;}
      while(eBEEigKJEU == SfGsenZMYI){XiyWcAUBMD = true;}
      while(rpgWTBIYFm == rpgWTBIYFm){iyLcfoXguV = true;}
      while(mfdqgwqDSL == mfdqgwqDSL){fByzORUcTr = true;}
      if(WNbGSDxKzi == true){WNbGSDxKzi = false;}
      if(wzLzsNIpaD == true){wzLzsNIpaD = false;}
      if(bHEbjyXNWl == true){bHEbjyXNWl = false;}
      if(pGpsydOaDP == true){pGpsydOaDP = false;}
      if(DyZVpmTexS == true){DyZVpmTexS = false;}
      if(nBcOiOJzVT == true){nBcOiOJzVT = false;}
      if(fjmNsoIRAP == true){fjmNsoIRAP = false;}
      if(yhmKzdhhkw == true){yhmKzdhhkw = false;}
      if(dsQEyocbKj == true){dsQEyocbKj = false;}
      if(TOEijTLMcB == true){TOEijTLMcB = false;}
      if(dCdgTGNRPE == true){dCdgTGNRPE = false;}
      if(fbOZplShOE == true){fbOZplShOE = false;}
      if(LgGQwjcEaf == true){LgGQwjcEaf = false;}
      if(SVFjSbOjjr == true){SVFjSbOjjr = false;}
      if(aLMFDrAesx == true){aLMFDrAesx = false;}
      if(AcxXowuNkj == true){AcxXowuNkj = false;}
      if(cJqilKVdHN == true){cJqilKVdHN = false;}
      if(XiyWcAUBMD == true){XiyWcAUBMD = false;}
      if(iyLcfoXguV == true){iyLcfoXguV = false;}
      if(fByzORUcTr == true){fByzORUcTr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CILRXRUVSF
{ 
  void XCeHZgHsDn()
  { 
      bool IbtUNknpzj = false;
      bool qCKTrngBkk = false;
      bool orZIjUPtBQ = false;
      bool ZArCeQaVMn = false;
      bool SEYXqBpEpR = false;
      bool KfnXBPBlks = false;
      bool UtniJpJIoa = false;
      bool NKnxRjSCRi = false;
      bool dLEjGtLTAO = false;
      bool OnkTSYPpNA = false;
      bool qhOPEzrqGQ = false;
      bool wzUCPJoDcP = false;
      bool epHaLYZTds = false;
      bool UcnRquwnfG = false;
      bool CTNiRPThDJ = false;
      bool iLNxUAanDe = false;
      bool YXNNwTKDKT = false;
      bool NBXVNKbXIw = false;
      bool FrPUJIPpwq = false;
      bool UHkBheGAly = false;
      string ihSnzbgtrj;
      string ZFsLeZlQrK;
      string FsQdQpUKpk;
      string TLyXqqfAMT;
      string QSdzWkbqIh;
      string CcNDEpQnWI;
      string GVEGQOHVTm;
      string tkDYsmORHe;
      string NdBHhpxuSB;
      string ZqcDMtNWiH;
      string dGWUnRYnJR;
      string azgqucUwYZ;
      string QLCSNCHALz;
      string YrhzAHGfTQ;
      string QJkBZZJlIj;
      string ZRyIqSDEHk;
      string KYbKriRhqm;
      string WncHIHaBsm;
      string sVqaYHtYHh;
      string DBYhGrgZIp;
      if(ihSnzbgtrj == dGWUnRYnJR){IbtUNknpzj = true;}
      else if(dGWUnRYnJR == ihSnzbgtrj){qhOPEzrqGQ = true;}
      if(ZFsLeZlQrK == azgqucUwYZ){qCKTrngBkk = true;}
      else if(azgqucUwYZ == ZFsLeZlQrK){wzUCPJoDcP = true;}
      if(FsQdQpUKpk == QLCSNCHALz){orZIjUPtBQ = true;}
      else if(QLCSNCHALz == FsQdQpUKpk){epHaLYZTds = true;}
      if(TLyXqqfAMT == YrhzAHGfTQ){ZArCeQaVMn = true;}
      else if(YrhzAHGfTQ == TLyXqqfAMT){UcnRquwnfG = true;}
      if(QSdzWkbqIh == QJkBZZJlIj){SEYXqBpEpR = true;}
      else if(QJkBZZJlIj == QSdzWkbqIh){CTNiRPThDJ = true;}
      if(CcNDEpQnWI == ZRyIqSDEHk){KfnXBPBlks = true;}
      else if(ZRyIqSDEHk == CcNDEpQnWI){iLNxUAanDe = true;}
      if(GVEGQOHVTm == KYbKriRhqm){UtniJpJIoa = true;}
      else if(KYbKriRhqm == GVEGQOHVTm){YXNNwTKDKT = true;}
      if(tkDYsmORHe == WncHIHaBsm){NKnxRjSCRi = true;}
      if(NdBHhpxuSB == sVqaYHtYHh){dLEjGtLTAO = true;}
      if(ZqcDMtNWiH == DBYhGrgZIp){OnkTSYPpNA = true;}
      while(WncHIHaBsm == tkDYsmORHe){NBXVNKbXIw = true;}
      while(sVqaYHtYHh == sVqaYHtYHh){FrPUJIPpwq = true;}
      while(DBYhGrgZIp == DBYhGrgZIp){UHkBheGAly = true;}
      if(IbtUNknpzj == true){IbtUNknpzj = false;}
      if(qCKTrngBkk == true){qCKTrngBkk = false;}
      if(orZIjUPtBQ == true){orZIjUPtBQ = false;}
      if(ZArCeQaVMn == true){ZArCeQaVMn = false;}
      if(SEYXqBpEpR == true){SEYXqBpEpR = false;}
      if(KfnXBPBlks == true){KfnXBPBlks = false;}
      if(UtniJpJIoa == true){UtniJpJIoa = false;}
      if(NKnxRjSCRi == true){NKnxRjSCRi = false;}
      if(dLEjGtLTAO == true){dLEjGtLTAO = false;}
      if(OnkTSYPpNA == true){OnkTSYPpNA = false;}
      if(qhOPEzrqGQ == true){qhOPEzrqGQ = false;}
      if(wzUCPJoDcP == true){wzUCPJoDcP = false;}
      if(epHaLYZTds == true){epHaLYZTds = false;}
      if(UcnRquwnfG == true){UcnRquwnfG = false;}
      if(CTNiRPThDJ == true){CTNiRPThDJ = false;}
      if(iLNxUAanDe == true){iLNxUAanDe = false;}
      if(YXNNwTKDKT == true){YXNNwTKDKT = false;}
      if(NBXVNKbXIw == true){NBXVNKbXIw = false;}
      if(FrPUJIPpwq == true){FrPUJIPpwq = false;}
      if(UHkBheGAly == true){UHkBheGAly = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMATHWVMAB
{ 
  void DzWmRFPzoC()
  { 
      bool izbkIxxGfy = false;
      bool EoBVOuTAGw = false;
      bool etjAQkwzDo = false;
      bool XKVaIRwrPb = false;
      bool ppsyxzjpAY = false;
      bool XSEbgoObUX = false;
      bool AxDqatSZMw = false;
      bool ybkdFnAkDQ = false;
      bool AGzdREFstT = false;
      bool CUWqarmCXC = false;
      bool fJcDawhZWr = false;
      bool ncXDXtyYYW = false;
      bool oZfstcEsDN = false;
      bool ByNAjpcwDU = false;
      bool VeWBeYwSTf = false;
      bool tNcANGdjIx = false;
      bool qoWIppPXSg = false;
      bool RBVEAJCdNV = false;
      bool fkZXSnVMld = false;
      bool MsmFdgINKo = false;
      string GLeHgVaZNe;
      string oEumxkIqEl;
      string ShguQteDwp;
      string FhnyRplyFU;
      string OxOJgCilRa;
      string fBMkFXejqm;
      string qWcWZGPwUH;
      string zJkiXUTWON;
      string KrlUKEVDss;
      string LCHSdqTqia;
      string lmQKbVPcMj;
      string EHUcbyjHMV;
      string jMDbwxCSEf;
      string AbmnbXaasn;
      string nrqInDgdpf;
      string GMeNpZioOe;
      string TwYfjbTgBE;
      string WJOXgqUtmr;
      string QYcYZnxZxB;
      string nlMOUqTKYL;
      if(GLeHgVaZNe == lmQKbVPcMj){izbkIxxGfy = true;}
      else if(lmQKbVPcMj == GLeHgVaZNe){fJcDawhZWr = true;}
      if(oEumxkIqEl == EHUcbyjHMV){EoBVOuTAGw = true;}
      else if(EHUcbyjHMV == oEumxkIqEl){ncXDXtyYYW = true;}
      if(ShguQteDwp == jMDbwxCSEf){etjAQkwzDo = true;}
      else if(jMDbwxCSEf == ShguQteDwp){oZfstcEsDN = true;}
      if(FhnyRplyFU == AbmnbXaasn){XKVaIRwrPb = true;}
      else if(AbmnbXaasn == FhnyRplyFU){ByNAjpcwDU = true;}
      if(OxOJgCilRa == nrqInDgdpf){ppsyxzjpAY = true;}
      else if(nrqInDgdpf == OxOJgCilRa){VeWBeYwSTf = true;}
      if(fBMkFXejqm == GMeNpZioOe){XSEbgoObUX = true;}
      else if(GMeNpZioOe == fBMkFXejqm){tNcANGdjIx = true;}
      if(qWcWZGPwUH == TwYfjbTgBE){AxDqatSZMw = true;}
      else if(TwYfjbTgBE == qWcWZGPwUH){qoWIppPXSg = true;}
      if(zJkiXUTWON == WJOXgqUtmr){ybkdFnAkDQ = true;}
      if(KrlUKEVDss == QYcYZnxZxB){AGzdREFstT = true;}
      if(LCHSdqTqia == nlMOUqTKYL){CUWqarmCXC = true;}
      while(WJOXgqUtmr == zJkiXUTWON){RBVEAJCdNV = true;}
      while(QYcYZnxZxB == QYcYZnxZxB){fkZXSnVMld = true;}
      while(nlMOUqTKYL == nlMOUqTKYL){MsmFdgINKo = true;}
      if(izbkIxxGfy == true){izbkIxxGfy = false;}
      if(EoBVOuTAGw == true){EoBVOuTAGw = false;}
      if(etjAQkwzDo == true){etjAQkwzDo = false;}
      if(XKVaIRwrPb == true){XKVaIRwrPb = false;}
      if(ppsyxzjpAY == true){ppsyxzjpAY = false;}
      if(XSEbgoObUX == true){XSEbgoObUX = false;}
      if(AxDqatSZMw == true){AxDqatSZMw = false;}
      if(ybkdFnAkDQ == true){ybkdFnAkDQ = false;}
      if(AGzdREFstT == true){AGzdREFstT = false;}
      if(CUWqarmCXC == true){CUWqarmCXC = false;}
      if(fJcDawhZWr == true){fJcDawhZWr = false;}
      if(ncXDXtyYYW == true){ncXDXtyYYW = false;}
      if(oZfstcEsDN == true){oZfstcEsDN = false;}
      if(ByNAjpcwDU == true){ByNAjpcwDU = false;}
      if(VeWBeYwSTf == true){VeWBeYwSTf = false;}
      if(tNcANGdjIx == true){tNcANGdjIx = false;}
      if(qoWIppPXSg == true){qoWIppPXSg = false;}
      if(RBVEAJCdNV == true){RBVEAJCdNV = false;}
      if(fkZXSnVMld == true){fkZXSnVMld = false;}
      if(MsmFdgINKo == true){MsmFdgINKo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZBSPJVLXK
{ 
  void waCVAOAKsx()
  { 
      bool FULZVjPPJY = false;
      bool XrZrViYnxr = false;
      bool moOUCXhpIt = false;
      bool rOlqcZiajh = false;
      bool MsTaHeoDWB = false;
      bool wReaUPGqXy = false;
      bool BYGOfIGiOw = false;
      bool AxEOetVmNX = false;
      bool ieSGyZjKVM = false;
      bool TrDlgmlEuy = false;
      bool XFnaByNPwa = false;
      bool tSdzPVGAQG = false;
      bool YuMBcHsRhq = false;
      bool HQrPzcqrEz = false;
      bool MTOuSANDWK = false;
      bool glnnYcrlys = false;
      bool EuhEScaOAl = false;
      bool eOuQsEfRib = false;
      bool spuWKVcDpW = false;
      bool jEtLtQlKbo = false;
      string SzSTkWhyYc;
      string oEVpsITDkF;
      string FTwiZcYgBJ;
      string xaduSuGCEi;
      string NnhNmbQEew;
      string FaMoMzCjtI;
      string xAxOfOaaXy;
      string BRyBrRkiwx;
      string LUCEEWNohS;
      string rWIwkMqTgY;
      string BpfgunbLwu;
      string NTmwwbyrKJ;
      string AkrFGdICPf;
      string aRBXwVoUJQ;
      string tBsmFXjMAJ;
      string NyIXXQyZZQ;
      string eZuPTwSOAZ;
      string mcisOyrFAh;
      string tuBGSbIcAe;
      string XOuskUGcSI;
      if(SzSTkWhyYc == BpfgunbLwu){FULZVjPPJY = true;}
      else if(BpfgunbLwu == SzSTkWhyYc){XFnaByNPwa = true;}
      if(oEVpsITDkF == NTmwwbyrKJ){XrZrViYnxr = true;}
      else if(NTmwwbyrKJ == oEVpsITDkF){tSdzPVGAQG = true;}
      if(FTwiZcYgBJ == AkrFGdICPf){moOUCXhpIt = true;}
      else if(AkrFGdICPf == FTwiZcYgBJ){YuMBcHsRhq = true;}
      if(xaduSuGCEi == aRBXwVoUJQ){rOlqcZiajh = true;}
      else if(aRBXwVoUJQ == xaduSuGCEi){HQrPzcqrEz = true;}
      if(NnhNmbQEew == tBsmFXjMAJ){MsTaHeoDWB = true;}
      else if(tBsmFXjMAJ == NnhNmbQEew){MTOuSANDWK = true;}
      if(FaMoMzCjtI == NyIXXQyZZQ){wReaUPGqXy = true;}
      else if(NyIXXQyZZQ == FaMoMzCjtI){glnnYcrlys = true;}
      if(xAxOfOaaXy == eZuPTwSOAZ){BYGOfIGiOw = true;}
      else if(eZuPTwSOAZ == xAxOfOaaXy){EuhEScaOAl = true;}
      if(BRyBrRkiwx == mcisOyrFAh){AxEOetVmNX = true;}
      if(LUCEEWNohS == tuBGSbIcAe){ieSGyZjKVM = true;}
      if(rWIwkMqTgY == XOuskUGcSI){TrDlgmlEuy = true;}
      while(mcisOyrFAh == BRyBrRkiwx){eOuQsEfRib = true;}
      while(tuBGSbIcAe == tuBGSbIcAe){spuWKVcDpW = true;}
      while(XOuskUGcSI == XOuskUGcSI){jEtLtQlKbo = true;}
      if(FULZVjPPJY == true){FULZVjPPJY = false;}
      if(XrZrViYnxr == true){XrZrViYnxr = false;}
      if(moOUCXhpIt == true){moOUCXhpIt = false;}
      if(rOlqcZiajh == true){rOlqcZiajh = false;}
      if(MsTaHeoDWB == true){MsTaHeoDWB = false;}
      if(wReaUPGqXy == true){wReaUPGqXy = false;}
      if(BYGOfIGiOw == true){BYGOfIGiOw = false;}
      if(AxEOetVmNX == true){AxEOetVmNX = false;}
      if(ieSGyZjKVM == true){ieSGyZjKVM = false;}
      if(TrDlgmlEuy == true){TrDlgmlEuy = false;}
      if(XFnaByNPwa == true){XFnaByNPwa = false;}
      if(tSdzPVGAQG == true){tSdzPVGAQG = false;}
      if(YuMBcHsRhq == true){YuMBcHsRhq = false;}
      if(HQrPzcqrEz == true){HQrPzcqrEz = false;}
      if(MTOuSANDWK == true){MTOuSANDWK = false;}
      if(glnnYcrlys == true){glnnYcrlys = false;}
      if(EuhEScaOAl == true){EuhEScaOAl = false;}
      if(eOuQsEfRib == true){eOuQsEfRib = false;}
      if(spuWKVcDpW == true){spuWKVcDpW = false;}
      if(jEtLtQlKbo == true){jEtLtQlKbo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHNPFYMVHS
{ 
  void tlNQRhgYOH()
  { 
      bool GNtIrSaXsC = false;
      bool RhVFWriSWS = false;
      bool dqqKSgyEBy = false;
      bool bFHClwEqza = false;
      bool pEPdhgnrda = false;
      bool HiFohOWioK = false;
      bool UWWtaMaSTa = false;
      bool mqSucZaNcl = false;
      bool sFZZqrzRUW = false;
      bool YUBoGSgUCV = false;
      bool FUYDnPPKMH = false;
      bool nIGDROwwDh = false;
      bool MIyxBRpdoJ = false;
      bool rFLGfXgWlb = false;
      bool coFMhQOyXr = false;
      bool WkRTIxWbBV = false;
      bool ZlUCPhxAWs = false;
      bool gZKaFXDkOk = false;
      bool DqFwmHnqyi = false;
      bool AEUPCpTCxA = false;
      string eiRslyaOWH;
      string XNPniOjfPP;
      string qJzwDSBnMg;
      string uiQdOjsKES;
      string uXOILZupuz;
      string XyjuCVjVpS;
      string xlCpLoxlZz;
      string UZaxTTtpjc;
      string XKsNJwzUbs;
      string AXTlVJVYxW;
      string bJQwdxXlah;
      string askMulsofO;
      string pbKfywGobK;
      string yUrMBNtwiL;
      string YMssRGlGpj;
      string PgrifAzjxg;
      string qhKQjGAXLh;
      string qxFUodhQOr;
      string KzzrtQbJgA;
      string OJyBTpBcIL;
      if(eiRslyaOWH == bJQwdxXlah){GNtIrSaXsC = true;}
      else if(bJQwdxXlah == eiRslyaOWH){FUYDnPPKMH = true;}
      if(XNPniOjfPP == askMulsofO){RhVFWriSWS = true;}
      else if(askMulsofO == XNPniOjfPP){nIGDROwwDh = true;}
      if(qJzwDSBnMg == pbKfywGobK){dqqKSgyEBy = true;}
      else if(pbKfywGobK == qJzwDSBnMg){MIyxBRpdoJ = true;}
      if(uiQdOjsKES == yUrMBNtwiL){bFHClwEqza = true;}
      else if(yUrMBNtwiL == uiQdOjsKES){rFLGfXgWlb = true;}
      if(uXOILZupuz == YMssRGlGpj){pEPdhgnrda = true;}
      else if(YMssRGlGpj == uXOILZupuz){coFMhQOyXr = true;}
      if(XyjuCVjVpS == PgrifAzjxg){HiFohOWioK = true;}
      else if(PgrifAzjxg == XyjuCVjVpS){WkRTIxWbBV = true;}
      if(xlCpLoxlZz == qhKQjGAXLh){UWWtaMaSTa = true;}
      else if(qhKQjGAXLh == xlCpLoxlZz){ZlUCPhxAWs = true;}
      if(UZaxTTtpjc == qxFUodhQOr){mqSucZaNcl = true;}
      if(XKsNJwzUbs == KzzrtQbJgA){sFZZqrzRUW = true;}
      if(AXTlVJVYxW == OJyBTpBcIL){YUBoGSgUCV = true;}
      while(qxFUodhQOr == UZaxTTtpjc){gZKaFXDkOk = true;}
      while(KzzrtQbJgA == KzzrtQbJgA){DqFwmHnqyi = true;}
      while(OJyBTpBcIL == OJyBTpBcIL){AEUPCpTCxA = true;}
      if(GNtIrSaXsC == true){GNtIrSaXsC = false;}
      if(RhVFWriSWS == true){RhVFWriSWS = false;}
      if(dqqKSgyEBy == true){dqqKSgyEBy = false;}
      if(bFHClwEqza == true){bFHClwEqza = false;}
      if(pEPdhgnrda == true){pEPdhgnrda = false;}
      if(HiFohOWioK == true){HiFohOWioK = false;}
      if(UWWtaMaSTa == true){UWWtaMaSTa = false;}
      if(mqSucZaNcl == true){mqSucZaNcl = false;}
      if(sFZZqrzRUW == true){sFZZqrzRUW = false;}
      if(YUBoGSgUCV == true){YUBoGSgUCV = false;}
      if(FUYDnPPKMH == true){FUYDnPPKMH = false;}
      if(nIGDROwwDh == true){nIGDROwwDh = false;}
      if(MIyxBRpdoJ == true){MIyxBRpdoJ = false;}
      if(rFLGfXgWlb == true){rFLGfXgWlb = false;}
      if(coFMhQOyXr == true){coFMhQOyXr = false;}
      if(WkRTIxWbBV == true){WkRTIxWbBV = false;}
      if(ZlUCPhxAWs == true){ZlUCPhxAWs = false;}
      if(gZKaFXDkOk == true){gZKaFXDkOk = false;}
      if(DqFwmHnqyi == true){DqFwmHnqyi = false;}
      if(AEUPCpTCxA == true){AEUPCpTCxA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMGCRVLMVD
{ 
  void VYPBijKQma()
  { 
      bool hbpInuoZPs = false;
      bool VrXkShhiVh = false;
      bool cwMZhskNqf = false;
      bool zXxxVQjPVY = false;
      bool JwYlVSWVtl = false;
      bool btIUMlPQZt = false;
      bool JbiisytZPC = false;
      bool yRNwYgWZDP = false;
      bool WPSFEFOckj = false;
      bool ASoaOhMosX = false;
      bool XwGrnJfLwe = false;
      bool OoNKXtIdem = false;
      bool iRneBeblhq = false;
      bool TggfqZJZQt = false;
      bool YCgFULFeDU = false;
      bool YiKFnGHaqI = false;
      bool htdFLhIgSx = false;
      bool khMkNgkiKp = false;
      bool YxiMRjWbrj = false;
      bool RhiHMeYatm = false;
      string RDOtyohGAx;
      string izUNDPKxMK;
      string zYStAVDlFn;
      string xjGGoijjZG;
      string YSnLVnpLeF;
      string RCjkbrkTtb;
      string luBLAzrNXT;
      string eZWFlgkGYL;
      string frHAVtAUdw;
      string xQpyUcRbLV;
      string wbmLZredzu;
      string HeuhwsnBoF;
      string zXibVOiYkI;
      string OItCPDFwZd;
      string PVUinSUIBb;
      string nQlFWXrKoL;
      string IFrpfzjrRs;
      string mraLpcCAmD;
      string saXJUyVnfr;
      string KtGNUJceCo;
      if(RDOtyohGAx == wbmLZredzu){hbpInuoZPs = true;}
      else if(wbmLZredzu == RDOtyohGAx){XwGrnJfLwe = true;}
      if(izUNDPKxMK == HeuhwsnBoF){VrXkShhiVh = true;}
      else if(HeuhwsnBoF == izUNDPKxMK){OoNKXtIdem = true;}
      if(zYStAVDlFn == zXibVOiYkI){cwMZhskNqf = true;}
      else if(zXibVOiYkI == zYStAVDlFn){iRneBeblhq = true;}
      if(xjGGoijjZG == OItCPDFwZd){zXxxVQjPVY = true;}
      else if(OItCPDFwZd == xjGGoijjZG){TggfqZJZQt = true;}
      if(YSnLVnpLeF == PVUinSUIBb){JwYlVSWVtl = true;}
      else if(PVUinSUIBb == YSnLVnpLeF){YCgFULFeDU = true;}
      if(RCjkbrkTtb == nQlFWXrKoL){btIUMlPQZt = true;}
      else if(nQlFWXrKoL == RCjkbrkTtb){YiKFnGHaqI = true;}
      if(luBLAzrNXT == IFrpfzjrRs){JbiisytZPC = true;}
      else if(IFrpfzjrRs == luBLAzrNXT){htdFLhIgSx = true;}
      if(eZWFlgkGYL == mraLpcCAmD){yRNwYgWZDP = true;}
      if(frHAVtAUdw == saXJUyVnfr){WPSFEFOckj = true;}
      if(xQpyUcRbLV == KtGNUJceCo){ASoaOhMosX = true;}
      while(mraLpcCAmD == eZWFlgkGYL){khMkNgkiKp = true;}
      while(saXJUyVnfr == saXJUyVnfr){YxiMRjWbrj = true;}
      while(KtGNUJceCo == KtGNUJceCo){RhiHMeYatm = true;}
      if(hbpInuoZPs == true){hbpInuoZPs = false;}
      if(VrXkShhiVh == true){VrXkShhiVh = false;}
      if(cwMZhskNqf == true){cwMZhskNqf = false;}
      if(zXxxVQjPVY == true){zXxxVQjPVY = false;}
      if(JwYlVSWVtl == true){JwYlVSWVtl = false;}
      if(btIUMlPQZt == true){btIUMlPQZt = false;}
      if(JbiisytZPC == true){JbiisytZPC = false;}
      if(yRNwYgWZDP == true){yRNwYgWZDP = false;}
      if(WPSFEFOckj == true){WPSFEFOckj = false;}
      if(ASoaOhMosX == true){ASoaOhMosX = false;}
      if(XwGrnJfLwe == true){XwGrnJfLwe = false;}
      if(OoNKXtIdem == true){OoNKXtIdem = false;}
      if(iRneBeblhq == true){iRneBeblhq = false;}
      if(TggfqZJZQt == true){TggfqZJZQt = false;}
      if(YCgFULFeDU == true){YCgFULFeDU = false;}
      if(YiKFnGHaqI == true){YiKFnGHaqI = false;}
      if(htdFLhIgSx == true){htdFLhIgSx = false;}
      if(khMkNgkiKp == true){khMkNgkiKp = false;}
      if(YxiMRjWbrj == true){YxiMRjWbrj = false;}
      if(RhiHMeYatm == true){RhiHMeYatm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWHSSMSSZL
{ 
  void xoSEhsKfRJ()
  { 
      bool qqQKSwAqZA = false;
      bool HUceBAzEGV = false;
      bool SzaVRqDKXi = false;
      bool iqlZkOUeby = false;
      bool iOzdeeKKnF = false;
      bool CojUjqPusb = false;
      bool rpTqRQhDtm = false;
      bool fUcHmEAxpl = false;
      bool gsVRftGQos = false;
      bool yZkzGruHLO = false;
      bool wGQBZgLbhf = false;
      bool qSEGtzTBKX = false;
      bool KRNAnGicBt = false;
      bool IrkboZbUrz = false;
      bool hdiJCfUeEG = false;
      bool YtxnDesPMT = false;
      bool xhamXygbQU = false;
      bool WyILofhDxH = false;
      bool kEXuVNuwXK = false;
      bool fMIXBzDwlE = false;
      string GYlfqwKzWo;
      string DfcwfAEkXp;
      string wfoPFGMUoI;
      string OuePHLijbG;
      string XKIPHPkDVd;
      string RPJCbajWZj;
      string ipKOaHBNnU;
      string QUIQRkWYHp;
      string UJyLpylbmg;
      string bMJqXhAtnz;
      string OXOAMxGrjp;
      string DKOjOZqzXc;
      string VYZHsELRsj;
      string kckIbxtxys;
      string qsqwdQxYby;
      string pBWLdoxHHI;
      string lozAFZZGIR;
      string etAekchcdb;
      string GloutjGZel;
      string zmppGCsqqD;
      if(GYlfqwKzWo == OXOAMxGrjp){qqQKSwAqZA = true;}
      else if(OXOAMxGrjp == GYlfqwKzWo){wGQBZgLbhf = true;}
      if(DfcwfAEkXp == DKOjOZqzXc){HUceBAzEGV = true;}
      else if(DKOjOZqzXc == DfcwfAEkXp){qSEGtzTBKX = true;}
      if(wfoPFGMUoI == VYZHsELRsj){SzaVRqDKXi = true;}
      else if(VYZHsELRsj == wfoPFGMUoI){KRNAnGicBt = true;}
      if(OuePHLijbG == kckIbxtxys){iqlZkOUeby = true;}
      else if(kckIbxtxys == OuePHLijbG){IrkboZbUrz = true;}
      if(XKIPHPkDVd == qsqwdQxYby){iOzdeeKKnF = true;}
      else if(qsqwdQxYby == XKIPHPkDVd){hdiJCfUeEG = true;}
      if(RPJCbajWZj == pBWLdoxHHI){CojUjqPusb = true;}
      else if(pBWLdoxHHI == RPJCbajWZj){YtxnDesPMT = true;}
      if(ipKOaHBNnU == lozAFZZGIR){rpTqRQhDtm = true;}
      else if(lozAFZZGIR == ipKOaHBNnU){xhamXygbQU = true;}
      if(QUIQRkWYHp == etAekchcdb){fUcHmEAxpl = true;}
      if(UJyLpylbmg == GloutjGZel){gsVRftGQos = true;}
      if(bMJqXhAtnz == zmppGCsqqD){yZkzGruHLO = true;}
      while(etAekchcdb == QUIQRkWYHp){WyILofhDxH = true;}
      while(GloutjGZel == GloutjGZel){kEXuVNuwXK = true;}
      while(zmppGCsqqD == zmppGCsqqD){fMIXBzDwlE = true;}
      if(qqQKSwAqZA == true){qqQKSwAqZA = false;}
      if(HUceBAzEGV == true){HUceBAzEGV = false;}
      if(SzaVRqDKXi == true){SzaVRqDKXi = false;}
      if(iqlZkOUeby == true){iqlZkOUeby = false;}
      if(iOzdeeKKnF == true){iOzdeeKKnF = false;}
      if(CojUjqPusb == true){CojUjqPusb = false;}
      if(rpTqRQhDtm == true){rpTqRQhDtm = false;}
      if(fUcHmEAxpl == true){fUcHmEAxpl = false;}
      if(gsVRftGQos == true){gsVRftGQos = false;}
      if(yZkzGruHLO == true){yZkzGruHLO = false;}
      if(wGQBZgLbhf == true){wGQBZgLbhf = false;}
      if(qSEGtzTBKX == true){qSEGtzTBKX = false;}
      if(KRNAnGicBt == true){KRNAnGicBt = false;}
      if(IrkboZbUrz == true){IrkboZbUrz = false;}
      if(hdiJCfUeEG == true){hdiJCfUeEG = false;}
      if(YtxnDesPMT == true){YtxnDesPMT = false;}
      if(xhamXygbQU == true){xhamXygbQU = false;}
      if(WyILofhDxH == true){WyILofhDxH = false;}
      if(kEXuVNuwXK == true){kEXuVNuwXK = false;}
      if(fMIXBzDwlE == true){fMIXBzDwlE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKYBKVYRPT
{ 
  void EjArnHsIAq()
  { 
      bool AiWnOnTlsJ = false;
      bool rrsiLfnBWs = false;
      bool glrbsAxhzr = false;
      bool reSZoLBuyG = false;
      bool XsrciqsZFQ = false;
      bool gHdJpOpuuO = false;
      bool qlmARMYTsz = false;
      bool erDPUmsOrB = false;
      bool HXbiLkBIia = false;
      bool VFziPlGqLW = false;
      bool RYfFknENoD = false;
      bool UaDsHTJDog = false;
      bool LQjSdZsTAi = false;
      bool gCDUjhqWyW = false;
      bool fmTfFuCFbw = false;
      bool cCBeKBnNaL = false;
      bool ujNGVSXhJY = false;
      bool blFRAYwEMi = false;
      bool WmqEFeAXKi = false;
      bool sdwlbuZNJm = false;
      string NVhIiriQsK;
      string DsRhTWnhYd;
      string umxMdlXTHn;
      string kUPZnORJoo;
      string BxnoWDPTtU;
      string hRPlraYVex;
      string UOIFZhdqtE;
      string FdsjcyyIoZ;
      string VDYmFSFchM;
      string ouerTlniOo;
      string ZXYoPDYfJt;
      string bQgEaRpVzH;
      string bAJhPJzBPq;
      string JPsAAydiWC;
      string sZTmjYOaQC;
      string uRjHMYOqZG;
      string EXPSjMXfDc;
      string mGyxNCgVxp;
      string tXjNuqflmb;
      string ilJQxUJBCX;
      if(NVhIiriQsK == ZXYoPDYfJt){AiWnOnTlsJ = true;}
      else if(ZXYoPDYfJt == NVhIiriQsK){RYfFknENoD = true;}
      if(DsRhTWnhYd == bQgEaRpVzH){rrsiLfnBWs = true;}
      else if(bQgEaRpVzH == DsRhTWnhYd){UaDsHTJDog = true;}
      if(umxMdlXTHn == bAJhPJzBPq){glrbsAxhzr = true;}
      else if(bAJhPJzBPq == umxMdlXTHn){LQjSdZsTAi = true;}
      if(kUPZnORJoo == JPsAAydiWC){reSZoLBuyG = true;}
      else if(JPsAAydiWC == kUPZnORJoo){gCDUjhqWyW = true;}
      if(BxnoWDPTtU == sZTmjYOaQC){XsrciqsZFQ = true;}
      else if(sZTmjYOaQC == BxnoWDPTtU){fmTfFuCFbw = true;}
      if(hRPlraYVex == uRjHMYOqZG){gHdJpOpuuO = true;}
      else if(uRjHMYOqZG == hRPlraYVex){cCBeKBnNaL = true;}
      if(UOIFZhdqtE == EXPSjMXfDc){qlmARMYTsz = true;}
      else if(EXPSjMXfDc == UOIFZhdqtE){ujNGVSXhJY = true;}
      if(FdsjcyyIoZ == mGyxNCgVxp){erDPUmsOrB = true;}
      if(VDYmFSFchM == tXjNuqflmb){HXbiLkBIia = true;}
      if(ouerTlniOo == ilJQxUJBCX){VFziPlGqLW = true;}
      while(mGyxNCgVxp == FdsjcyyIoZ){blFRAYwEMi = true;}
      while(tXjNuqflmb == tXjNuqflmb){WmqEFeAXKi = true;}
      while(ilJQxUJBCX == ilJQxUJBCX){sdwlbuZNJm = true;}
      if(AiWnOnTlsJ == true){AiWnOnTlsJ = false;}
      if(rrsiLfnBWs == true){rrsiLfnBWs = false;}
      if(glrbsAxhzr == true){glrbsAxhzr = false;}
      if(reSZoLBuyG == true){reSZoLBuyG = false;}
      if(XsrciqsZFQ == true){XsrciqsZFQ = false;}
      if(gHdJpOpuuO == true){gHdJpOpuuO = false;}
      if(qlmARMYTsz == true){qlmARMYTsz = false;}
      if(erDPUmsOrB == true){erDPUmsOrB = false;}
      if(HXbiLkBIia == true){HXbiLkBIia = false;}
      if(VFziPlGqLW == true){VFziPlGqLW = false;}
      if(RYfFknENoD == true){RYfFknENoD = false;}
      if(UaDsHTJDog == true){UaDsHTJDog = false;}
      if(LQjSdZsTAi == true){LQjSdZsTAi = false;}
      if(gCDUjhqWyW == true){gCDUjhqWyW = false;}
      if(fmTfFuCFbw == true){fmTfFuCFbw = false;}
      if(cCBeKBnNaL == true){cCBeKBnNaL = false;}
      if(ujNGVSXhJY == true){ujNGVSXhJY = false;}
      if(blFRAYwEMi == true){blFRAYwEMi = false;}
      if(WmqEFeAXKi == true){WmqEFeAXKi = false;}
      if(sdwlbuZNJm == true){sdwlbuZNJm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQOYTMSLPV
{ 
  void RbJmRCChQL()
  { 
      bool dJlSQKqTzw = false;
      bool mMBVOIGgFN = false;
      bool gcTIaGuRrY = false;
      bool ugdJgYsuet = false;
      bool HZnfbACxNN = false;
      bool rJsHhApcrK = false;
      bool OYaaAFhrop = false;
      bool PLCLGGnmga = false;
      bool DyEefkmWaf = false;
      bool hPDTehyNfV = false;
      bool RKHXygGhAa = false;
      bool MDwRHQUwtO = false;
      bool SKQIHzIigY = false;
      bool IZHKIrpgfz = false;
      bool dFVzTeSlMN = false;
      bool MBSQDGszPy = false;
      bool YXBbSlwkIO = false;
      bool anPukMoRoc = false;
      bool fWVSLGHqHB = false;
      bool yqQhZFDsgh = false;
      string kDbjCaygTC;
      string lqeqCWKoJE;
      string cxzTnWSyAL;
      string uIDShaUJzW;
      string mlOWSxFzMn;
      string bhmFnmDHue;
      string HzfHGcnLJb;
      string BBplRqibBq;
      string RTkLjNVxet;
      string WMNTPmFGQp;
      string JsoklarAnx;
      string DbGEMnOTXs;
      string HpgPEomVWd;
      string kcLKhYdzZJ;
      string UUJhptFIHa;
      string YliWhSLZfx;
      string mVcKMaQwWn;
      string JOtOXlfzYK;
      string ieOwEytnbO;
      string MDSbVzqzUP;
      if(kDbjCaygTC == JsoklarAnx){dJlSQKqTzw = true;}
      else if(JsoklarAnx == kDbjCaygTC){RKHXygGhAa = true;}
      if(lqeqCWKoJE == DbGEMnOTXs){mMBVOIGgFN = true;}
      else if(DbGEMnOTXs == lqeqCWKoJE){MDwRHQUwtO = true;}
      if(cxzTnWSyAL == HpgPEomVWd){gcTIaGuRrY = true;}
      else if(HpgPEomVWd == cxzTnWSyAL){SKQIHzIigY = true;}
      if(uIDShaUJzW == kcLKhYdzZJ){ugdJgYsuet = true;}
      else if(kcLKhYdzZJ == uIDShaUJzW){IZHKIrpgfz = true;}
      if(mlOWSxFzMn == UUJhptFIHa){HZnfbACxNN = true;}
      else if(UUJhptFIHa == mlOWSxFzMn){dFVzTeSlMN = true;}
      if(bhmFnmDHue == YliWhSLZfx){rJsHhApcrK = true;}
      else if(YliWhSLZfx == bhmFnmDHue){MBSQDGszPy = true;}
      if(HzfHGcnLJb == mVcKMaQwWn){OYaaAFhrop = true;}
      else if(mVcKMaQwWn == HzfHGcnLJb){YXBbSlwkIO = true;}
      if(BBplRqibBq == JOtOXlfzYK){PLCLGGnmga = true;}
      if(RTkLjNVxet == ieOwEytnbO){DyEefkmWaf = true;}
      if(WMNTPmFGQp == MDSbVzqzUP){hPDTehyNfV = true;}
      while(JOtOXlfzYK == BBplRqibBq){anPukMoRoc = true;}
      while(ieOwEytnbO == ieOwEytnbO){fWVSLGHqHB = true;}
      while(MDSbVzqzUP == MDSbVzqzUP){yqQhZFDsgh = true;}
      if(dJlSQKqTzw == true){dJlSQKqTzw = false;}
      if(mMBVOIGgFN == true){mMBVOIGgFN = false;}
      if(gcTIaGuRrY == true){gcTIaGuRrY = false;}
      if(ugdJgYsuet == true){ugdJgYsuet = false;}
      if(HZnfbACxNN == true){HZnfbACxNN = false;}
      if(rJsHhApcrK == true){rJsHhApcrK = false;}
      if(OYaaAFhrop == true){OYaaAFhrop = false;}
      if(PLCLGGnmga == true){PLCLGGnmga = false;}
      if(DyEefkmWaf == true){DyEefkmWaf = false;}
      if(hPDTehyNfV == true){hPDTehyNfV = false;}
      if(RKHXygGhAa == true){RKHXygGhAa = false;}
      if(MDwRHQUwtO == true){MDwRHQUwtO = false;}
      if(SKQIHzIigY == true){SKQIHzIigY = false;}
      if(IZHKIrpgfz == true){IZHKIrpgfz = false;}
      if(dFVzTeSlMN == true){dFVzTeSlMN = false;}
      if(MBSQDGszPy == true){MBSQDGszPy = false;}
      if(YXBbSlwkIO == true){YXBbSlwkIO = false;}
      if(anPukMoRoc == true){anPukMoRoc = false;}
      if(fWVSLGHqHB == true){fWVSLGHqHB = false;}
      if(yqQhZFDsgh == true){yqQhZFDsgh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZETDPEZRKY
{ 
  void ueVfQedNEn()
  { 
      bool XdgxbVRURi = false;
      bool jqAJuwyqJP = false;
      bool dyEkcHowed = false;
      bool hHsZwXGTaE = false;
      bool NKVDXnOpar = false;
      bool xlrinZZwTU = false;
      bool fVpmAcxZMW = false;
      bool pdQFBTbBMo = false;
      bool ryVlfwPKlW = false;
      bool yKzFXrUiCu = false;
      bool qndDCSVlgT = false;
      bool yXiebgADGE = false;
      bool NmmpYfdKhJ = false;
      bool ysyRyEURjM = false;
      bool acdRXZaUdp = false;
      bool qRbygEAmeV = false;
      bool oKEWVFZRgX = false;
      bool MiSsdkIVRz = false;
      bool FJgqSgQzjt = false;
      bool DhmNXPXGwS = false;
      string AolVSWPFZT;
      string xpEgFGwnID;
      string dLQxgIUGfH;
      string ksoGzzkLme;
      string nsDKioVwQq;
      string imYjxoXnnK;
      string CJYShDAxgG;
      string VkAdPkHGNq;
      string mXooXxTFIK;
      string awWcbeTkbf;
      string oXPKVymuTM;
      string gQZwWdTjtj;
      string jtnVeYNXBj;
      string QWehCOIeSZ;
      string KXkwcKWZFy;
      string Kjpqutisex;
      string jPtiwKlrsI;
      string VoRUZLJrsU;
      string CmRCZffnmI;
      string eOAVoudBzS;
      if(AolVSWPFZT == oXPKVymuTM){XdgxbVRURi = true;}
      else if(oXPKVymuTM == AolVSWPFZT){qndDCSVlgT = true;}
      if(xpEgFGwnID == gQZwWdTjtj){jqAJuwyqJP = true;}
      else if(gQZwWdTjtj == xpEgFGwnID){yXiebgADGE = true;}
      if(dLQxgIUGfH == jtnVeYNXBj){dyEkcHowed = true;}
      else if(jtnVeYNXBj == dLQxgIUGfH){NmmpYfdKhJ = true;}
      if(ksoGzzkLme == QWehCOIeSZ){hHsZwXGTaE = true;}
      else if(QWehCOIeSZ == ksoGzzkLme){ysyRyEURjM = true;}
      if(nsDKioVwQq == KXkwcKWZFy){NKVDXnOpar = true;}
      else if(KXkwcKWZFy == nsDKioVwQq){acdRXZaUdp = true;}
      if(imYjxoXnnK == Kjpqutisex){xlrinZZwTU = true;}
      else if(Kjpqutisex == imYjxoXnnK){qRbygEAmeV = true;}
      if(CJYShDAxgG == jPtiwKlrsI){fVpmAcxZMW = true;}
      else if(jPtiwKlrsI == CJYShDAxgG){oKEWVFZRgX = true;}
      if(VkAdPkHGNq == VoRUZLJrsU){pdQFBTbBMo = true;}
      if(mXooXxTFIK == CmRCZffnmI){ryVlfwPKlW = true;}
      if(awWcbeTkbf == eOAVoudBzS){yKzFXrUiCu = true;}
      while(VoRUZLJrsU == VkAdPkHGNq){MiSsdkIVRz = true;}
      while(CmRCZffnmI == CmRCZffnmI){FJgqSgQzjt = true;}
      while(eOAVoudBzS == eOAVoudBzS){DhmNXPXGwS = true;}
      if(XdgxbVRURi == true){XdgxbVRURi = false;}
      if(jqAJuwyqJP == true){jqAJuwyqJP = false;}
      if(dyEkcHowed == true){dyEkcHowed = false;}
      if(hHsZwXGTaE == true){hHsZwXGTaE = false;}
      if(NKVDXnOpar == true){NKVDXnOpar = false;}
      if(xlrinZZwTU == true){xlrinZZwTU = false;}
      if(fVpmAcxZMW == true){fVpmAcxZMW = false;}
      if(pdQFBTbBMo == true){pdQFBTbBMo = false;}
      if(ryVlfwPKlW == true){ryVlfwPKlW = false;}
      if(yKzFXrUiCu == true){yKzFXrUiCu = false;}
      if(qndDCSVlgT == true){qndDCSVlgT = false;}
      if(yXiebgADGE == true){yXiebgADGE = false;}
      if(NmmpYfdKhJ == true){NmmpYfdKhJ = false;}
      if(ysyRyEURjM == true){ysyRyEURjM = false;}
      if(acdRXZaUdp == true){acdRXZaUdp = false;}
      if(qRbygEAmeV == true){qRbygEAmeV = false;}
      if(oKEWVFZRgX == true){oKEWVFZRgX = false;}
      if(MiSsdkIVRz == true){MiSsdkIVRz = false;}
      if(FJgqSgQzjt == true){FJgqSgQzjt = false;}
      if(DhmNXPXGwS == true){DhmNXPXGwS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWVSXBCSBT
{ 
  void tjsGJdKlbK()
  { 
      bool KgmHSDRdxJ = false;
      bool eGfaNRsiXe = false;
      bool BBeLrWKzHl = false;
      bool bOyqTwtzLN = false;
      bool pMnVEzKhNx = false;
      bool fTSETIBbPu = false;
      bool rRVLgPHnHR = false;
      bool XtXKnoMJGr = false;
      bool LclKFIutXK = false;
      bool uRiPVXpcnn = false;
      bool rWZuZlwIPd = false;
      bool wqVWjOfKFY = false;
      bool TNPxWFKInP = false;
      bool ziVRAoDpkT = false;
      bool MmdtNDwMeG = false;
      bool reXPUdGbYT = false;
      bool bnTAdMVDVt = false;
      bool LpZlLgjViS = false;
      bool JxchXTLGxW = false;
      bool iaQRrYTdPB = false;
      string qeELawIJQp;
      string eczlHBKuRZ;
      string xcIUItwfkD;
      string QxgkMBHzgd;
      string gKzTQSHslF;
      string ZbKWZNVjDf;
      string AbYNZgwOZG;
      string sLNnsldnDp;
      string mDtecnlJKy;
      string eXuAcEllti;
      string WrTfMOOWdn;
      string jgfNsxhskk;
      string tlEaaUPNKn;
      string ArtUTtiNSN;
      string ZPfWNxrhGf;
      string WrBIojnrEq;
      string zAMomrmLty;
      string NTaWLeFhMd;
      string chGdQIpkfi;
      string GpIaOZCqiV;
      if(qeELawIJQp == WrTfMOOWdn){KgmHSDRdxJ = true;}
      else if(WrTfMOOWdn == qeELawIJQp){rWZuZlwIPd = true;}
      if(eczlHBKuRZ == jgfNsxhskk){eGfaNRsiXe = true;}
      else if(jgfNsxhskk == eczlHBKuRZ){wqVWjOfKFY = true;}
      if(xcIUItwfkD == tlEaaUPNKn){BBeLrWKzHl = true;}
      else if(tlEaaUPNKn == xcIUItwfkD){TNPxWFKInP = true;}
      if(QxgkMBHzgd == ArtUTtiNSN){bOyqTwtzLN = true;}
      else if(ArtUTtiNSN == QxgkMBHzgd){ziVRAoDpkT = true;}
      if(gKzTQSHslF == ZPfWNxrhGf){pMnVEzKhNx = true;}
      else if(ZPfWNxrhGf == gKzTQSHslF){MmdtNDwMeG = true;}
      if(ZbKWZNVjDf == WrBIojnrEq){fTSETIBbPu = true;}
      else if(WrBIojnrEq == ZbKWZNVjDf){reXPUdGbYT = true;}
      if(AbYNZgwOZG == zAMomrmLty){rRVLgPHnHR = true;}
      else if(zAMomrmLty == AbYNZgwOZG){bnTAdMVDVt = true;}
      if(sLNnsldnDp == NTaWLeFhMd){XtXKnoMJGr = true;}
      if(mDtecnlJKy == chGdQIpkfi){LclKFIutXK = true;}
      if(eXuAcEllti == GpIaOZCqiV){uRiPVXpcnn = true;}
      while(NTaWLeFhMd == sLNnsldnDp){LpZlLgjViS = true;}
      while(chGdQIpkfi == chGdQIpkfi){JxchXTLGxW = true;}
      while(GpIaOZCqiV == GpIaOZCqiV){iaQRrYTdPB = true;}
      if(KgmHSDRdxJ == true){KgmHSDRdxJ = false;}
      if(eGfaNRsiXe == true){eGfaNRsiXe = false;}
      if(BBeLrWKzHl == true){BBeLrWKzHl = false;}
      if(bOyqTwtzLN == true){bOyqTwtzLN = false;}
      if(pMnVEzKhNx == true){pMnVEzKhNx = false;}
      if(fTSETIBbPu == true){fTSETIBbPu = false;}
      if(rRVLgPHnHR == true){rRVLgPHnHR = false;}
      if(XtXKnoMJGr == true){XtXKnoMJGr = false;}
      if(LclKFIutXK == true){LclKFIutXK = false;}
      if(uRiPVXpcnn == true){uRiPVXpcnn = false;}
      if(rWZuZlwIPd == true){rWZuZlwIPd = false;}
      if(wqVWjOfKFY == true){wqVWjOfKFY = false;}
      if(TNPxWFKInP == true){TNPxWFKInP = false;}
      if(ziVRAoDpkT == true){ziVRAoDpkT = false;}
      if(MmdtNDwMeG == true){MmdtNDwMeG = false;}
      if(reXPUdGbYT == true){reXPUdGbYT = false;}
      if(bnTAdMVDVt == true){bnTAdMVDVt = false;}
      if(LpZlLgjViS == true){LpZlLgjViS = false;}
      if(JxchXTLGxW == true){JxchXTLGxW = false;}
      if(iaQRrYTdPB == true){iaQRrYTdPB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKHKNNAFVJ
{ 
  void HZupyYcebP()
  { 
      bool YXKpigEBFn = false;
      bool fSItpFUwxw = false;
      bool WuXrHjmmJx = false;
      bool GBLQtVYSTO = false;
      bool FLQAoVmqPj = false;
      bool TDRdMczRhy = false;
      bool tRrHgeGqzU = false;
      bool fBchpLdWCl = false;
      bool xuWYdDigER = false;
      bool VGjUUnSITK = false;
      bool OuruERZinA = false;
      bool ycPwBytTdc = false;
      bool uZmhyYQINC = false;
      bool rVDrWBCbUL = false;
      bool dzsDSsqnTV = false;
      bool szepOnIKwe = false;
      bool BRVkIcYWYz = false;
      bool wSySzugiOF = false;
      bool gcnqIrqMch = false;
      bool srfoKMcHuo = false;
      string SUiTZaZJmX;
      string USeyhQjEqM;
      string MblExQEbWh;
      string gzkJJCIZjX;
      string dUihVGwTDT;
      string GrjdJqhdWJ;
      string WylEpUgVne;
      string HKUShrrEiq;
      string TkYCanPGAS;
      string UdDaBfhdrA;
      string YaeXMwXQwR;
      string ydufolZjdB;
      string FaUVKcHtRC;
      string JNMiSsFApe;
      string QyJiUpiXkP;
      string GyAptxFJNj;
      string ocztHjRLMu;
      string fYszkGQlAT;
      string siICwKMVnU;
      string nwlGonzPaj;
      if(SUiTZaZJmX == YaeXMwXQwR){YXKpigEBFn = true;}
      else if(YaeXMwXQwR == SUiTZaZJmX){OuruERZinA = true;}
      if(USeyhQjEqM == ydufolZjdB){fSItpFUwxw = true;}
      else if(ydufolZjdB == USeyhQjEqM){ycPwBytTdc = true;}
      if(MblExQEbWh == FaUVKcHtRC){WuXrHjmmJx = true;}
      else if(FaUVKcHtRC == MblExQEbWh){uZmhyYQINC = true;}
      if(gzkJJCIZjX == JNMiSsFApe){GBLQtVYSTO = true;}
      else if(JNMiSsFApe == gzkJJCIZjX){rVDrWBCbUL = true;}
      if(dUihVGwTDT == QyJiUpiXkP){FLQAoVmqPj = true;}
      else if(QyJiUpiXkP == dUihVGwTDT){dzsDSsqnTV = true;}
      if(GrjdJqhdWJ == GyAptxFJNj){TDRdMczRhy = true;}
      else if(GyAptxFJNj == GrjdJqhdWJ){szepOnIKwe = true;}
      if(WylEpUgVne == ocztHjRLMu){tRrHgeGqzU = true;}
      else if(ocztHjRLMu == WylEpUgVne){BRVkIcYWYz = true;}
      if(HKUShrrEiq == fYszkGQlAT){fBchpLdWCl = true;}
      if(TkYCanPGAS == siICwKMVnU){xuWYdDigER = true;}
      if(UdDaBfhdrA == nwlGonzPaj){VGjUUnSITK = true;}
      while(fYszkGQlAT == HKUShrrEiq){wSySzugiOF = true;}
      while(siICwKMVnU == siICwKMVnU){gcnqIrqMch = true;}
      while(nwlGonzPaj == nwlGonzPaj){srfoKMcHuo = true;}
      if(YXKpigEBFn == true){YXKpigEBFn = false;}
      if(fSItpFUwxw == true){fSItpFUwxw = false;}
      if(WuXrHjmmJx == true){WuXrHjmmJx = false;}
      if(GBLQtVYSTO == true){GBLQtVYSTO = false;}
      if(FLQAoVmqPj == true){FLQAoVmqPj = false;}
      if(TDRdMczRhy == true){TDRdMczRhy = false;}
      if(tRrHgeGqzU == true){tRrHgeGqzU = false;}
      if(fBchpLdWCl == true){fBchpLdWCl = false;}
      if(xuWYdDigER == true){xuWYdDigER = false;}
      if(VGjUUnSITK == true){VGjUUnSITK = false;}
      if(OuruERZinA == true){OuruERZinA = false;}
      if(ycPwBytTdc == true){ycPwBytTdc = false;}
      if(uZmhyYQINC == true){uZmhyYQINC = false;}
      if(rVDrWBCbUL == true){rVDrWBCbUL = false;}
      if(dzsDSsqnTV == true){dzsDSsqnTV = false;}
      if(szepOnIKwe == true){szepOnIKwe = false;}
      if(BRVkIcYWYz == true){BRVkIcYWYz = false;}
      if(wSySzugiOF == true){wSySzugiOF = false;}
      if(gcnqIrqMch == true){gcnqIrqMch = false;}
      if(srfoKMcHuo == true){srfoKMcHuo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JICANGMWTM
{ 
  void zXBYAVORcn()
  { 
      bool gdaypTJWom = false;
      bool wNKxiGbEVX = false;
      bool EsjNauQjfI = false;
      bool jpXEnPPddc = false;
      bool ugIFoGIahE = false;
      bool yycUBmtMWu = false;
      bool CZqgCFpGIT = false;
      bool qxarbXkdYT = false;
      bool lpBbKlMCDA = false;
      bool VCGiaVpbCi = false;
      bool QCRONAWkrc = false;
      bool CPnCILXOVP = false;
      bool smCHynqqQG = false;
      bool hIboDjXmOK = false;
      bool ObJayGODaP = false;
      bool xaFmpcAKPY = false;
      bool IfTlusmyzY = false;
      bool mkALAQdbJq = false;
      bool YmQBJGDozZ = false;
      bool iNWoBiIXeE = false;
      string UPsjjpbSSB;
      string FDgNcDrFqQ;
      string AOAoBcyszx;
      string mOHgxzDeuE;
      string WbixgnOLpb;
      string ailRSGODiH;
      string riTVOqwzPd;
      string zMJlsYeDIN;
      string NlDWVDbpOp;
      string jAunLnINip;
      string qOwMbNZzXs;
      string aLtVtFewzL;
      string PGkZszQVaF;
      string QRUSVypptI;
      string cbRUOXFZtG;
      string ILNWZkdVSc;
      string xDYScIqbzu;
      string PoBqhmoPKV;
      string spbUwFExrk;
      string UTXRKZCyrF;
      if(UPsjjpbSSB == qOwMbNZzXs){gdaypTJWom = true;}
      else if(qOwMbNZzXs == UPsjjpbSSB){QCRONAWkrc = true;}
      if(FDgNcDrFqQ == aLtVtFewzL){wNKxiGbEVX = true;}
      else if(aLtVtFewzL == FDgNcDrFqQ){CPnCILXOVP = true;}
      if(AOAoBcyszx == PGkZszQVaF){EsjNauQjfI = true;}
      else if(PGkZszQVaF == AOAoBcyszx){smCHynqqQG = true;}
      if(mOHgxzDeuE == QRUSVypptI){jpXEnPPddc = true;}
      else if(QRUSVypptI == mOHgxzDeuE){hIboDjXmOK = true;}
      if(WbixgnOLpb == cbRUOXFZtG){ugIFoGIahE = true;}
      else if(cbRUOXFZtG == WbixgnOLpb){ObJayGODaP = true;}
      if(ailRSGODiH == ILNWZkdVSc){yycUBmtMWu = true;}
      else if(ILNWZkdVSc == ailRSGODiH){xaFmpcAKPY = true;}
      if(riTVOqwzPd == xDYScIqbzu){CZqgCFpGIT = true;}
      else if(xDYScIqbzu == riTVOqwzPd){IfTlusmyzY = true;}
      if(zMJlsYeDIN == PoBqhmoPKV){qxarbXkdYT = true;}
      if(NlDWVDbpOp == spbUwFExrk){lpBbKlMCDA = true;}
      if(jAunLnINip == UTXRKZCyrF){VCGiaVpbCi = true;}
      while(PoBqhmoPKV == zMJlsYeDIN){mkALAQdbJq = true;}
      while(spbUwFExrk == spbUwFExrk){YmQBJGDozZ = true;}
      while(UTXRKZCyrF == UTXRKZCyrF){iNWoBiIXeE = true;}
      if(gdaypTJWom == true){gdaypTJWom = false;}
      if(wNKxiGbEVX == true){wNKxiGbEVX = false;}
      if(EsjNauQjfI == true){EsjNauQjfI = false;}
      if(jpXEnPPddc == true){jpXEnPPddc = false;}
      if(ugIFoGIahE == true){ugIFoGIahE = false;}
      if(yycUBmtMWu == true){yycUBmtMWu = false;}
      if(CZqgCFpGIT == true){CZqgCFpGIT = false;}
      if(qxarbXkdYT == true){qxarbXkdYT = false;}
      if(lpBbKlMCDA == true){lpBbKlMCDA = false;}
      if(VCGiaVpbCi == true){VCGiaVpbCi = false;}
      if(QCRONAWkrc == true){QCRONAWkrc = false;}
      if(CPnCILXOVP == true){CPnCILXOVP = false;}
      if(smCHynqqQG == true){smCHynqqQG = false;}
      if(hIboDjXmOK == true){hIboDjXmOK = false;}
      if(ObJayGODaP == true){ObJayGODaP = false;}
      if(xaFmpcAKPY == true){xaFmpcAKPY = false;}
      if(IfTlusmyzY == true){IfTlusmyzY = false;}
      if(mkALAQdbJq == true){mkALAQdbJq = false;}
      if(YmQBJGDozZ == true){YmQBJGDozZ = false;}
      if(iNWoBiIXeE == true){iNWoBiIXeE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZWIFYHOVQ
{ 
  void lVjrUhNzPT()
  { 
      bool hApHMfSlDy = false;
      bool idfQsGFAKN = false;
      bool itrxaOwNYT = false;
      bool kuezhPMjqF = false;
      bool RXrrpFapTj = false;
      bool xTibrmIsgy = false;
      bool jFMjNnzgid = false;
      bool tVIFwLBzGU = false;
      bool mFtoWQLDHt = false;
      bool GTDsUMKIdC = false;
      bool GtGopbKceg = false;
      bool lIlMKdKXNw = false;
      bool bwYoXaRPji = false;
      bool ArUENsyFzu = false;
      bool FhXZHxgqhq = false;
      bool CmugZKURRO = false;
      bool JuswgtmhyR = false;
      bool eFYRqsXzhZ = false;
      bool tagsgMwndC = false;
      bool XgmjkKoasN = false;
      string hiQIMGEoqO;
      string KQFnsmAOjg;
      string AtAHodzCIy;
      string iPcaPUXBtb;
      string faMdcomdsa;
      string XazTFniITi;
      string HCgrftmeYY;
      string PyTIAZgVdz;
      string pUIhaHQIUb;
      string kOhKUdsTyh;
      string CHFTKZGqSf;
      string GNeUslsyRX;
      string ddJxmAPJmW;
      string fMWuxhPnWA;
      string AYpoUXjNRi;
      string ktCaEXyIgJ;
      string JxEwzspiWK;
      string VEaQWFnUbP;
      string QCqEkkJwqZ;
      string jHHNqDUsob;
      if(hiQIMGEoqO == CHFTKZGqSf){hApHMfSlDy = true;}
      else if(CHFTKZGqSf == hiQIMGEoqO){GtGopbKceg = true;}
      if(KQFnsmAOjg == GNeUslsyRX){idfQsGFAKN = true;}
      else if(GNeUslsyRX == KQFnsmAOjg){lIlMKdKXNw = true;}
      if(AtAHodzCIy == ddJxmAPJmW){itrxaOwNYT = true;}
      else if(ddJxmAPJmW == AtAHodzCIy){bwYoXaRPji = true;}
      if(iPcaPUXBtb == fMWuxhPnWA){kuezhPMjqF = true;}
      else if(fMWuxhPnWA == iPcaPUXBtb){ArUENsyFzu = true;}
      if(faMdcomdsa == AYpoUXjNRi){RXrrpFapTj = true;}
      else if(AYpoUXjNRi == faMdcomdsa){FhXZHxgqhq = true;}
      if(XazTFniITi == ktCaEXyIgJ){xTibrmIsgy = true;}
      else if(ktCaEXyIgJ == XazTFniITi){CmugZKURRO = true;}
      if(HCgrftmeYY == JxEwzspiWK){jFMjNnzgid = true;}
      else if(JxEwzspiWK == HCgrftmeYY){JuswgtmhyR = true;}
      if(PyTIAZgVdz == VEaQWFnUbP){tVIFwLBzGU = true;}
      if(pUIhaHQIUb == QCqEkkJwqZ){mFtoWQLDHt = true;}
      if(kOhKUdsTyh == jHHNqDUsob){GTDsUMKIdC = true;}
      while(VEaQWFnUbP == PyTIAZgVdz){eFYRqsXzhZ = true;}
      while(QCqEkkJwqZ == QCqEkkJwqZ){tagsgMwndC = true;}
      while(jHHNqDUsob == jHHNqDUsob){XgmjkKoasN = true;}
      if(hApHMfSlDy == true){hApHMfSlDy = false;}
      if(idfQsGFAKN == true){idfQsGFAKN = false;}
      if(itrxaOwNYT == true){itrxaOwNYT = false;}
      if(kuezhPMjqF == true){kuezhPMjqF = false;}
      if(RXrrpFapTj == true){RXrrpFapTj = false;}
      if(xTibrmIsgy == true){xTibrmIsgy = false;}
      if(jFMjNnzgid == true){jFMjNnzgid = false;}
      if(tVIFwLBzGU == true){tVIFwLBzGU = false;}
      if(mFtoWQLDHt == true){mFtoWQLDHt = false;}
      if(GTDsUMKIdC == true){GTDsUMKIdC = false;}
      if(GtGopbKceg == true){GtGopbKceg = false;}
      if(lIlMKdKXNw == true){lIlMKdKXNw = false;}
      if(bwYoXaRPji == true){bwYoXaRPji = false;}
      if(ArUENsyFzu == true){ArUENsyFzu = false;}
      if(FhXZHxgqhq == true){FhXZHxgqhq = false;}
      if(CmugZKURRO == true){CmugZKURRO = false;}
      if(JuswgtmhyR == true){JuswgtmhyR = false;}
      if(eFYRqsXzhZ == true){eFYRqsXzhZ = false;}
      if(tagsgMwndC == true){tagsgMwndC = false;}
      if(XgmjkKoasN == true){XgmjkKoasN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHVXQSYMCI
{ 
  void jLArdjcFfX()
  { 
      bool XbTBgAVRxp = false;
      bool xNKwMfYFKq = false;
      bool lRSTJNArVw = false;
      bool fboPOXKcXN = false;
      bool AAsbfdoDmZ = false;
      bool ZEHITGJAqS = false;
      bool zcuBKVYtgo = false;
      bool VugwpkYqmf = false;
      bool XwFwVbUgwI = false;
      bool OKkFNWEqQK = false;
      bool EtWxDdWKRh = false;
      bool hRMKtDXzfh = false;
      bool BryYaLKbhS = false;
      bool ggZcadYIrr = false;
      bool FJONawxZKK = false;
      bool zELiJMwyWr = false;
      bool TtczAAqiiQ = false;
      bool dPGmcqckxd = false;
      bool NjQWScUqTO = false;
      bool gakAXKfPNZ = false;
      string LLCALtLScp;
      string dccnkkkfXJ;
      string QyuajPGmZM;
      string HkQPkpZCwe;
      string JLBXjmQOzl;
      string oUEmDMQaQu;
      string nXrPirMMDu;
      string LhirzExXqw;
      string yrnmWmgcLX;
      string ZylAqkTlnr;
      string aDKEaGkLmz;
      string OrjTxujErw;
      string KiBeUNwhBO;
      string kLizVtgjMQ;
      string BUpMJgNRDu;
      string AOsrgqCfiM;
      string KCKXNDIkyC;
      string OArbtpsnVm;
      string AddFNWRqRd;
      string rAAzFyJRzF;
      if(LLCALtLScp == aDKEaGkLmz){XbTBgAVRxp = true;}
      else if(aDKEaGkLmz == LLCALtLScp){EtWxDdWKRh = true;}
      if(dccnkkkfXJ == OrjTxujErw){xNKwMfYFKq = true;}
      else if(OrjTxujErw == dccnkkkfXJ){hRMKtDXzfh = true;}
      if(QyuajPGmZM == KiBeUNwhBO){lRSTJNArVw = true;}
      else if(KiBeUNwhBO == QyuajPGmZM){BryYaLKbhS = true;}
      if(HkQPkpZCwe == kLizVtgjMQ){fboPOXKcXN = true;}
      else if(kLizVtgjMQ == HkQPkpZCwe){ggZcadYIrr = true;}
      if(JLBXjmQOzl == BUpMJgNRDu){AAsbfdoDmZ = true;}
      else if(BUpMJgNRDu == JLBXjmQOzl){FJONawxZKK = true;}
      if(oUEmDMQaQu == AOsrgqCfiM){ZEHITGJAqS = true;}
      else if(AOsrgqCfiM == oUEmDMQaQu){zELiJMwyWr = true;}
      if(nXrPirMMDu == KCKXNDIkyC){zcuBKVYtgo = true;}
      else if(KCKXNDIkyC == nXrPirMMDu){TtczAAqiiQ = true;}
      if(LhirzExXqw == OArbtpsnVm){VugwpkYqmf = true;}
      if(yrnmWmgcLX == AddFNWRqRd){XwFwVbUgwI = true;}
      if(ZylAqkTlnr == rAAzFyJRzF){OKkFNWEqQK = true;}
      while(OArbtpsnVm == LhirzExXqw){dPGmcqckxd = true;}
      while(AddFNWRqRd == AddFNWRqRd){NjQWScUqTO = true;}
      while(rAAzFyJRzF == rAAzFyJRzF){gakAXKfPNZ = true;}
      if(XbTBgAVRxp == true){XbTBgAVRxp = false;}
      if(xNKwMfYFKq == true){xNKwMfYFKq = false;}
      if(lRSTJNArVw == true){lRSTJNArVw = false;}
      if(fboPOXKcXN == true){fboPOXKcXN = false;}
      if(AAsbfdoDmZ == true){AAsbfdoDmZ = false;}
      if(ZEHITGJAqS == true){ZEHITGJAqS = false;}
      if(zcuBKVYtgo == true){zcuBKVYtgo = false;}
      if(VugwpkYqmf == true){VugwpkYqmf = false;}
      if(XwFwVbUgwI == true){XwFwVbUgwI = false;}
      if(OKkFNWEqQK == true){OKkFNWEqQK = false;}
      if(EtWxDdWKRh == true){EtWxDdWKRh = false;}
      if(hRMKtDXzfh == true){hRMKtDXzfh = false;}
      if(BryYaLKbhS == true){BryYaLKbhS = false;}
      if(ggZcadYIrr == true){ggZcadYIrr = false;}
      if(FJONawxZKK == true){FJONawxZKK = false;}
      if(zELiJMwyWr == true){zELiJMwyWr = false;}
      if(TtczAAqiiQ == true){TtczAAqiiQ = false;}
      if(dPGmcqckxd == true){dPGmcqckxd = false;}
      if(NjQWScUqTO == true){NjQWScUqTO = false;}
      if(gakAXKfPNZ == true){gakAXKfPNZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SOEDEGUBMO
{ 
  void tSoWcmRBGs()
  { 
      bool aIyxUANGnK = false;
      bool jsGYTXzLjs = false;
      bool INGtmkZDfl = false;
      bool zGtxpWTKiu = false;
      bool zYzPKVxERO = false;
      bool ywOoHNCEJi = false;
      bool aJZBKcyIhx = false;
      bool EobnsiNqiQ = false;
      bool nUlRnDrEoc = false;
      bool TPAzUpzyEg = false;
      bool XnVTKITZuX = false;
      bool zKUruFXIMH = false;
      bool ksSFcnocTD = false;
      bool jPlBszzSGe = false;
      bool iSIRdJuIDP = false;
      bool RpkxweUQpW = false;
      bool TqGrmiYSzw = false;
      bool FFBhXSjBbT = false;
      bool sgYEksdnFO = false;
      bool ehbjLrMQdt = false;
      string rqbUVWMmYs;
      string jSKcRJdHTp;
      string AXBOgCEeHz;
      string hHXcPfaFJm;
      string KHwZZUYwXC;
      string XNIMPToMnS;
      string SgeYLcuhMl;
      string hYygerbanL;
      string dHHEbUyLNu;
      string qNQpUdcWOw;
      string ZqjlTyPbgW;
      string rNYboLYZxp;
      string ejTQuUHHMB;
      string PEMrllWUkd;
      string FWdpDcooAI;
      string ECZYRpWTqz;
      string pHOfGmBfpD;
      string nEoTkHFdMR;
      string eSHDwNemZu;
      string PDdkmyHyiP;
      if(rqbUVWMmYs == ZqjlTyPbgW){aIyxUANGnK = true;}
      else if(ZqjlTyPbgW == rqbUVWMmYs){XnVTKITZuX = true;}
      if(jSKcRJdHTp == rNYboLYZxp){jsGYTXzLjs = true;}
      else if(rNYboLYZxp == jSKcRJdHTp){zKUruFXIMH = true;}
      if(AXBOgCEeHz == ejTQuUHHMB){INGtmkZDfl = true;}
      else if(ejTQuUHHMB == AXBOgCEeHz){ksSFcnocTD = true;}
      if(hHXcPfaFJm == PEMrllWUkd){zGtxpWTKiu = true;}
      else if(PEMrllWUkd == hHXcPfaFJm){jPlBszzSGe = true;}
      if(KHwZZUYwXC == FWdpDcooAI){zYzPKVxERO = true;}
      else if(FWdpDcooAI == KHwZZUYwXC){iSIRdJuIDP = true;}
      if(XNIMPToMnS == ECZYRpWTqz){ywOoHNCEJi = true;}
      else if(ECZYRpWTqz == XNIMPToMnS){RpkxweUQpW = true;}
      if(SgeYLcuhMl == pHOfGmBfpD){aJZBKcyIhx = true;}
      else if(pHOfGmBfpD == SgeYLcuhMl){TqGrmiYSzw = true;}
      if(hYygerbanL == nEoTkHFdMR){EobnsiNqiQ = true;}
      if(dHHEbUyLNu == eSHDwNemZu){nUlRnDrEoc = true;}
      if(qNQpUdcWOw == PDdkmyHyiP){TPAzUpzyEg = true;}
      while(nEoTkHFdMR == hYygerbanL){FFBhXSjBbT = true;}
      while(eSHDwNemZu == eSHDwNemZu){sgYEksdnFO = true;}
      while(PDdkmyHyiP == PDdkmyHyiP){ehbjLrMQdt = true;}
      if(aIyxUANGnK == true){aIyxUANGnK = false;}
      if(jsGYTXzLjs == true){jsGYTXzLjs = false;}
      if(INGtmkZDfl == true){INGtmkZDfl = false;}
      if(zGtxpWTKiu == true){zGtxpWTKiu = false;}
      if(zYzPKVxERO == true){zYzPKVxERO = false;}
      if(ywOoHNCEJi == true){ywOoHNCEJi = false;}
      if(aJZBKcyIhx == true){aJZBKcyIhx = false;}
      if(EobnsiNqiQ == true){EobnsiNqiQ = false;}
      if(nUlRnDrEoc == true){nUlRnDrEoc = false;}
      if(TPAzUpzyEg == true){TPAzUpzyEg = false;}
      if(XnVTKITZuX == true){XnVTKITZuX = false;}
      if(zKUruFXIMH == true){zKUruFXIMH = false;}
      if(ksSFcnocTD == true){ksSFcnocTD = false;}
      if(jPlBszzSGe == true){jPlBszzSGe = false;}
      if(iSIRdJuIDP == true){iSIRdJuIDP = false;}
      if(RpkxweUQpW == true){RpkxweUQpW = false;}
      if(TqGrmiYSzw == true){TqGrmiYSzw = false;}
      if(FFBhXSjBbT == true){FFBhXSjBbT = false;}
      if(sgYEksdnFO == true){sgYEksdnFO = false;}
      if(ehbjLrMQdt == true){ehbjLrMQdt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOBZDTPPYQ
{ 
  void EwtDfjGTNX()
  { 
      bool RjtzJyAGJm = false;
      bool KldBMsbfNR = false;
      bool NnGBUdeUUI = false;
      bool obptbWOJjS = false;
      bool MeGTySRSit = false;
      bool ezLaIccree = false;
      bool SelAxhwjYp = false;
      bool dSwuEihlCB = false;
      bool MMlZdpQPky = false;
      bool sVdFAgrGWQ = false;
      bool WhsrPLCQVZ = false;
      bool upocSFsLWG = false;
      bool RfyawHnquX = false;
      bool qbPledSsKR = false;
      bool nAtLCDgBlt = false;
      bool mfiPypiSwH = false;
      bool WLUxhTaCyn = false;
      bool lAAFSRlmXr = false;
      bool amEAjKrznn = false;
      bool tAxDtbewch = false;
      string uxxuQUMNoK;
      string ZZzxRpXjah;
      string nhdSSOZUth;
      string npTNkjHRbw;
      string FOTESaNxsG;
      string YbhVgNTebB;
      string tqSHViFlMg;
      string hFIebYNYzr;
      string BcbmIMIyfX;
      string QcpZBNuMii;
      string UakLYSTDsI;
      string AteiARPeyJ;
      string aHGoQEPhcO;
      string cApPXZqPOp;
      string rFEWWWyGZi;
      string xQOZINUuuT;
      string CkZeezEOLZ;
      string ZzPHQUCiRt;
      string GJIsQMkPHJ;
      string FwUumHeZrW;
      if(uxxuQUMNoK == UakLYSTDsI){RjtzJyAGJm = true;}
      else if(UakLYSTDsI == uxxuQUMNoK){WhsrPLCQVZ = true;}
      if(ZZzxRpXjah == AteiARPeyJ){KldBMsbfNR = true;}
      else if(AteiARPeyJ == ZZzxRpXjah){upocSFsLWG = true;}
      if(nhdSSOZUth == aHGoQEPhcO){NnGBUdeUUI = true;}
      else if(aHGoQEPhcO == nhdSSOZUth){RfyawHnquX = true;}
      if(npTNkjHRbw == cApPXZqPOp){obptbWOJjS = true;}
      else if(cApPXZqPOp == npTNkjHRbw){qbPledSsKR = true;}
      if(FOTESaNxsG == rFEWWWyGZi){MeGTySRSit = true;}
      else if(rFEWWWyGZi == FOTESaNxsG){nAtLCDgBlt = true;}
      if(YbhVgNTebB == xQOZINUuuT){ezLaIccree = true;}
      else if(xQOZINUuuT == YbhVgNTebB){mfiPypiSwH = true;}
      if(tqSHViFlMg == CkZeezEOLZ){SelAxhwjYp = true;}
      else if(CkZeezEOLZ == tqSHViFlMg){WLUxhTaCyn = true;}
      if(hFIebYNYzr == ZzPHQUCiRt){dSwuEihlCB = true;}
      if(BcbmIMIyfX == GJIsQMkPHJ){MMlZdpQPky = true;}
      if(QcpZBNuMii == FwUumHeZrW){sVdFAgrGWQ = true;}
      while(ZzPHQUCiRt == hFIebYNYzr){lAAFSRlmXr = true;}
      while(GJIsQMkPHJ == GJIsQMkPHJ){amEAjKrznn = true;}
      while(FwUumHeZrW == FwUumHeZrW){tAxDtbewch = true;}
      if(RjtzJyAGJm == true){RjtzJyAGJm = false;}
      if(KldBMsbfNR == true){KldBMsbfNR = false;}
      if(NnGBUdeUUI == true){NnGBUdeUUI = false;}
      if(obptbWOJjS == true){obptbWOJjS = false;}
      if(MeGTySRSit == true){MeGTySRSit = false;}
      if(ezLaIccree == true){ezLaIccree = false;}
      if(SelAxhwjYp == true){SelAxhwjYp = false;}
      if(dSwuEihlCB == true){dSwuEihlCB = false;}
      if(MMlZdpQPky == true){MMlZdpQPky = false;}
      if(sVdFAgrGWQ == true){sVdFAgrGWQ = false;}
      if(WhsrPLCQVZ == true){WhsrPLCQVZ = false;}
      if(upocSFsLWG == true){upocSFsLWG = false;}
      if(RfyawHnquX == true){RfyawHnquX = false;}
      if(qbPledSsKR == true){qbPledSsKR = false;}
      if(nAtLCDgBlt == true){nAtLCDgBlt = false;}
      if(mfiPypiSwH == true){mfiPypiSwH = false;}
      if(WLUxhTaCyn == true){WLUxhTaCyn = false;}
      if(lAAFSRlmXr == true){lAAFSRlmXr = false;}
      if(amEAjKrznn == true){amEAjKrznn = false;}
      if(tAxDtbewch == true){tAxDtbewch = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSITBBIAWH
{ 
  void aZTIcnDyWb()
  { 
      bool soFaYDjExy = false;
      bool CybHLWZJTL = false;
      bool BdJhHzGiok = false;
      bool qzgmCZGQge = false;
      bool OfIWahPPYn = false;
      bool VDWLBPeXTZ = false;
      bool wBOMGDRnEk = false;
      bool PJbnwUUlGZ = false;
      bool jpKAOncUkm = false;
      bool uiwHhNQwQW = false;
      bool QaKmXMahPg = false;
      bool urQtoFqOyS = false;
      bool axCRpgMUFh = false;
      bool DYVjIJfWbC = false;
      bool MtEErCSCRb = false;
      bool WCxywSXswq = false;
      bool zFbhcWWgkf = false;
      bool ZTluFgrxYm = false;
      bool OKCdKAaXnp = false;
      bool kmakDGRWbV = false;
      string EyxprwUpDp;
      string dPeVHpGeCu;
      string VpQlLwrKnz;
      string IiYwcgicjS;
      string ujCGdPXnFR;
      string qUVQzNgKdw;
      string DJBDhtpira;
      string HcujAlnKHw;
      string XEFVImNIwO;
      string AXzmOkhzYi;
      string ZoudKNZkQN;
      string ZVDhXzEeut;
      string ggldZidHVO;
      string DnkXViIaLu;
      string NcrhndTRPP;
      string fDEdCrCRDa;
      string jRPBKkkeLn;
      string pcSAfEoEow;
      string PMrFhzjGVd;
      string gqWjKuMpWC;
      if(EyxprwUpDp == ZoudKNZkQN){soFaYDjExy = true;}
      else if(ZoudKNZkQN == EyxprwUpDp){QaKmXMahPg = true;}
      if(dPeVHpGeCu == ZVDhXzEeut){CybHLWZJTL = true;}
      else if(ZVDhXzEeut == dPeVHpGeCu){urQtoFqOyS = true;}
      if(VpQlLwrKnz == ggldZidHVO){BdJhHzGiok = true;}
      else if(ggldZidHVO == VpQlLwrKnz){axCRpgMUFh = true;}
      if(IiYwcgicjS == DnkXViIaLu){qzgmCZGQge = true;}
      else if(DnkXViIaLu == IiYwcgicjS){DYVjIJfWbC = true;}
      if(ujCGdPXnFR == NcrhndTRPP){OfIWahPPYn = true;}
      else if(NcrhndTRPP == ujCGdPXnFR){MtEErCSCRb = true;}
      if(qUVQzNgKdw == fDEdCrCRDa){VDWLBPeXTZ = true;}
      else if(fDEdCrCRDa == qUVQzNgKdw){WCxywSXswq = true;}
      if(DJBDhtpira == jRPBKkkeLn){wBOMGDRnEk = true;}
      else if(jRPBKkkeLn == DJBDhtpira){zFbhcWWgkf = true;}
      if(HcujAlnKHw == pcSAfEoEow){PJbnwUUlGZ = true;}
      if(XEFVImNIwO == PMrFhzjGVd){jpKAOncUkm = true;}
      if(AXzmOkhzYi == gqWjKuMpWC){uiwHhNQwQW = true;}
      while(pcSAfEoEow == HcujAlnKHw){ZTluFgrxYm = true;}
      while(PMrFhzjGVd == PMrFhzjGVd){OKCdKAaXnp = true;}
      while(gqWjKuMpWC == gqWjKuMpWC){kmakDGRWbV = true;}
      if(soFaYDjExy == true){soFaYDjExy = false;}
      if(CybHLWZJTL == true){CybHLWZJTL = false;}
      if(BdJhHzGiok == true){BdJhHzGiok = false;}
      if(qzgmCZGQge == true){qzgmCZGQge = false;}
      if(OfIWahPPYn == true){OfIWahPPYn = false;}
      if(VDWLBPeXTZ == true){VDWLBPeXTZ = false;}
      if(wBOMGDRnEk == true){wBOMGDRnEk = false;}
      if(PJbnwUUlGZ == true){PJbnwUUlGZ = false;}
      if(jpKAOncUkm == true){jpKAOncUkm = false;}
      if(uiwHhNQwQW == true){uiwHhNQwQW = false;}
      if(QaKmXMahPg == true){QaKmXMahPg = false;}
      if(urQtoFqOyS == true){urQtoFqOyS = false;}
      if(axCRpgMUFh == true){axCRpgMUFh = false;}
      if(DYVjIJfWbC == true){DYVjIJfWbC = false;}
      if(MtEErCSCRb == true){MtEErCSCRb = false;}
      if(WCxywSXswq == true){WCxywSXswq = false;}
      if(zFbhcWWgkf == true){zFbhcWWgkf = false;}
      if(ZTluFgrxYm == true){ZTluFgrxYm = false;}
      if(OKCdKAaXnp == true){OKCdKAaXnp = false;}
      if(kmakDGRWbV == true){kmakDGRWbV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFXAUQSLXR
{ 
  void zSUxBGmwHY()
  { 
      bool XinrEbeVNl = false;
      bool UjIffnIWdR = false;
      bool wQrZbdHeAz = false;
      bool FNdBzELjiX = false;
      bool lCtWJtMTFu = false;
      bool BjnLfGqOPa = false;
      bool UzVNfGGGga = false;
      bool cXmGetWUPg = false;
      bool QmZEyVZSUs = false;
      bool NwTIClffqD = false;
      bool nFmeScwhfk = false;
      bool jVyiJgZQPK = false;
      bool fmkmMgDdDr = false;
      bool NpdMsKAulU = false;
      bool YrliJrxkzV = false;
      bool MPQgWAUzRk = false;
      bool ZRemXsrloy = false;
      bool geetknABdU = false;
      bool iSehfyZwpr = false;
      bool pBcAuGNzLP = false;
      string NtNLhgGkVf;
      string dkVLbLmpoM;
      string XVmRUWFTOH;
      string VcApnHqSll;
      string hpcieNpkqO;
      string CPHqfrHwpK;
      string bmWOJBkeWT;
      string UUDDdhsElH;
      string gUbzFGVIKw;
      string zubbKuTOZd;
      string cLNXtgMDMy;
      string yDJicGLWIC;
      string ebTaTZsbri;
      string OddIeVHDFX;
      string tRuMxwkrzE;
      string iwGWyAqlDU;
      string nkLdiUYBDG;
      string zHQjIMfHdW;
      string nAcnzRXHJd;
      string eUAkjJGRcc;
      if(NtNLhgGkVf == cLNXtgMDMy){XinrEbeVNl = true;}
      else if(cLNXtgMDMy == NtNLhgGkVf){nFmeScwhfk = true;}
      if(dkVLbLmpoM == yDJicGLWIC){UjIffnIWdR = true;}
      else if(yDJicGLWIC == dkVLbLmpoM){jVyiJgZQPK = true;}
      if(XVmRUWFTOH == ebTaTZsbri){wQrZbdHeAz = true;}
      else if(ebTaTZsbri == XVmRUWFTOH){fmkmMgDdDr = true;}
      if(VcApnHqSll == OddIeVHDFX){FNdBzELjiX = true;}
      else if(OddIeVHDFX == VcApnHqSll){NpdMsKAulU = true;}
      if(hpcieNpkqO == tRuMxwkrzE){lCtWJtMTFu = true;}
      else if(tRuMxwkrzE == hpcieNpkqO){YrliJrxkzV = true;}
      if(CPHqfrHwpK == iwGWyAqlDU){BjnLfGqOPa = true;}
      else if(iwGWyAqlDU == CPHqfrHwpK){MPQgWAUzRk = true;}
      if(bmWOJBkeWT == nkLdiUYBDG){UzVNfGGGga = true;}
      else if(nkLdiUYBDG == bmWOJBkeWT){ZRemXsrloy = true;}
      if(UUDDdhsElH == zHQjIMfHdW){cXmGetWUPg = true;}
      if(gUbzFGVIKw == nAcnzRXHJd){QmZEyVZSUs = true;}
      if(zubbKuTOZd == eUAkjJGRcc){NwTIClffqD = true;}
      while(zHQjIMfHdW == UUDDdhsElH){geetknABdU = true;}
      while(nAcnzRXHJd == nAcnzRXHJd){iSehfyZwpr = true;}
      while(eUAkjJGRcc == eUAkjJGRcc){pBcAuGNzLP = true;}
      if(XinrEbeVNl == true){XinrEbeVNl = false;}
      if(UjIffnIWdR == true){UjIffnIWdR = false;}
      if(wQrZbdHeAz == true){wQrZbdHeAz = false;}
      if(FNdBzELjiX == true){FNdBzELjiX = false;}
      if(lCtWJtMTFu == true){lCtWJtMTFu = false;}
      if(BjnLfGqOPa == true){BjnLfGqOPa = false;}
      if(UzVNfGGGga == true){UzVNfGGGga = false;}
      if(cXmGetWUPg == true){cXmGetWUPg = false;}
      if(QmZEyVZSUs == true){QmZEyVZSUs = false;}
      if(NwTIClffqD == true){NwTIClffqD = false;}
      if(nFmeScwhfk == true){nFmeScwhfk = false;}
      if(jVyiJgZQPK == true){jVyiJgZQPK = false;}
      if(fmkmMgDdDr == true){fmkmMgDdDr = false;}
      if(NpdMsKAulU == true){NpdMsKAulU = false;}
      if(YrliJrxkzV == true){YrliJrxkzV = false;}
      if(MPQgWAUzRk == true){MPQgWAUzRk = false;}
      if(ZRemXsrloy == true){ZRemXsrloy = false;}
      if(geetknABdU == true){geetknABdU = false;}
      if(iSehfyZwpr == true){iSehfyZwpr = false;}
      if(pBcAuGNzLP == true){pBcAuGNzLP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDNIMBWCHO
{ 
  void ghmVTGEGmE()
  { 
      bool pPaJudWRQS = false;
      bool OCWNwdHEWI = false;
      bool oRaZdMOHnr = false;
      bool qyXdrEZLUQ = false;
      bool qESzBCIQOl = false;
      bool DdgdEYoBfi = false;
      bool OPcYaQesUq = false;
      bool DujFQjzbXa = false;
      bool EyrCnMRsZT = false;
      bool PYflCbbsXk = false;
      bool XPuWhItaMT = false;
      bool ZMcEeQWajN = false;
      bool ykTBbeOyDo = false;
      bool IFDmDnCVTf = false;
      bool SpfFtCuaGl = false;
      bool EAJKllwtuD = false;
      bool swXXLTJoBp = false;
      bool NBHDuIFNGZ = false;
      bool imqRjHwsBR = false;
      bool rIZPlWRIsZ = false;
      string GCHUcUyMpt;
      string aQFYalktdI;
      string khnTefGjzw;
      string ZPqBjHzdoT;
      string DxQcjLiKof;
      string EwknPXNmpw;
      string NNMsTKYDnS;
      string mGFKFnRLjS;
      string wwuTrdeDkL;
      string sLnrFojXIY;
      string leWVrxpZhb;
      string GCDWARSsAp;
      string fVSbZbSNEQ;
      string EtCKfRZZau;
      string mEUJFqHRrn;
      string VpWSsPMtwP;
      string ecVRWLArph;
      string rrSECaBJWi;
      string TBVQtOWiRQ;
      string EedKQKiDls;
      if(GCHUcUyMpt == leWVrxpZhb){pPaJudWRQS = true;}
      else if(leWVrxpZhb == GCHUcUyMpt){XPuWhItaMT = true;}
      if(aQFYalktdI == GCDWARSsAp){OCWNwdHEWI = true;}
      else if(GCDWARSsAp == aQFYalktdI){ZMcEeQWajN = true;}
      if(khnTefGjzw == fVSbZbSNEQ){oRaZdMOHnr = true;}
      else if(fVSbZbSNEQ == khnTefGjzw){ykTBbeOyDo = true;}
      if(ZPqBjHzdoT == EtCKfRZZau){qyXdrEZLUQ = true;}
      else if(EtCKfRZZau == ZPqBjHzdoT){IFDmDnCVTf = true;}
      if(DxQcjLiKof == mEUJFqHRrn){qESzBCIQOl = true;}
      else if(mEUJFqHRrn == DxQcjLiKof){SpfFtCuaGl = true;}
      if(EwknPXNmpw == VpWSsPMtwP){DdgdEYoBfi = true;}
      else if(VpWSsPMtwP == EwknPXNmpw){EAJKllwtuD = true;}
      if(NNMsTKYDnS == ecVRWLArph){OPcYaQesUq = true;}
      else if(ecVRWLArph == NNMsTKYDnS){swXXLTJoBp = true;}
      if(mGFKFnRLjS == rrSECaBJWi){DujFQjzbXa = true;}
      if(wwuTrdeDkL == TBVQtOWiRQ){EyrCnMRsZT = true;}
      if(sLnrFojXIY == EedKQKiDls){PYflCbbsXk = true;}
      while(rrSECaBJWi == mGFKFnRLjS){NBHDuIFNGZ = true;}
      while(TBVQtOWiRQ == TBVQtOWiRQ){imqRjHwsBR = true;}
      while(EedKQKiDls == EedKQKiDls){rIZPlWRIsZ = true;}
      if(pPaJudWRQS == true){pPaJudWRQS = false;}
      if(OCWNwdHEWI == true){OCWNwdHEWI = false;}
      if(oRaZdMOHnr == true){oRaZdMOHnr = false;}
      if(qyXdrEZLUQ == true){qyXdrEZLUQ = false;}
      if(qESzBCIQOl == true){qESzBCIQOl = false;}
      if(DdgdEYoBfi == true){DdgdEYoBfi = false;}
      if(OPcYaQesUq == true){OPcYaQesUq = false;}
      if(DujFQjzbXa == true){DujFQjzbXa = false;}
      if(EyrCnMRsZT == true){EyrCnMRsZT = false;}
      if(PYflCbbsXk == true){PYflCbbsXk = false;}
      if(XPuWhItaMT == true){XPuWhItaMT = false;}
      if(ZMcEeQWajN == true){ZMcEeQWajN = false;}
      if(ykTBbeOyDo == true){ykTBbeOyDo = false;}
      if(IFDmDnCVTf == true){IFDmDnCVTf = false;}
      if(SpfFtCuaGl == true){SpfFtCuaGl = false;}
      if(EAJKllwtuD == true){EAJKllwtuD = false;}
      if(swXXLTJoBp == true){swXXLTJoBp = false;}
      if(NBHDuIFNGZ == true){NBHDuIFNGZ = false;}
      if(imqRjHwsBR == true){imqRjHwsBR = false;}
      if(rIZPlWRIsZ == true){rIZPlWRIsZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AUNOOCWCTX
{ 
  void XAnnEnNYfa()
  { 
      bool jUoFWRQpNU = false;
      bool uYYFQobuPr = false;
      bool uJwONxlyrE = false;
      bool QnQZhNzQqq = false;
      bool VWjiHChmqZ = false;
      bool hiutHaYaqY = false;
      bool fRyIEGHzXD = false;
      bool pLDYWYZNGK = false;
      bool OyHRWgrWRH = false;
      bool nXYRKDYadA = false;
      bool uhPmjVeWWi = false;
      bool BKTfKhJfkW = false;
      bool OkhQORmlNS = false;
      bool AyiFPfiTgA = false;
      bool CVzhFdDrHc = false;
      bool trpHlJAyYS = false;
      bool irJEiDbOQe = false;
      bool zozjTrkAKk = false;
      bool NtejYHIbSF = false;
      bool fjuNRJMuyC = false;
      string ybKHRVKeZj;
      string dJRTJOfjht;
      string FXVcOYGNFH;
      string oMEpCcWOfD;
      string rJPuNkYGNu;
      string pRbjjZGhss;
      string OxYRuRFaQf;
      string rRDdCuHZOd;
      string AzzKRWjTGc;
      string WnVmoukyAw;
      string fxphDYOxhn;
      string RfSOrOxNAX;
      string gkUnJDuQoH;
      string JJZSxDJRHs;
      string ImlRKpUGta;
      string xXxcOtbCYz;
      string cyIZeHGARo;
      string EeGHPtzDcS;
      string hnVNJlMxDC;
      string aHsHPKdLlD;
      if(ybKHRVKeZj == fxphDYOxhn){jUoFWRQpNU = true;}
      else if(fxphDYOxhn == ybKHRVKeZj){uhPmjVeWWi = true;}
      if(dJRTJOfjht == RfSOrOxNAX){uYYFQobuPr = true;}
      else if(RfSOrOxNAX == dJRTJOfjht){BKTfKhJfkW = true;}
      if(FXVcOYGNFH == gkUnJDuQoH){uJwONxlyrE = true;}
      else if(gkUnJDuQoH == FXVcOYGNFH){OkhQORmlNS = true;}
      if(oMEpCcWOfD == JJZSxDJRHs){QnQZhNzQqq = true;}
      else if(JJZSxDJRHs == oMEpCcWOfD){AyiFPfiTgA = true;}
      if(rJPuNkYGNu == ImlRKpUGta){VWjiHChmqZ = true;}
      else if(ImlRKpUGta == rJPuNkYGNu){CVzhFdDrHc = true;}
      if(pRbjjZGhss == xXxcOtbCYz){hiutHaYaqY = true;}
      else if(xXxcOtbCYz == pRbjjZGhss){trpHlJAyYS = true;}
      if(OxYRuRFaQf == cyIZeHGARo){fRyIEGHzXD = true;}
      else if(cyIZeHGARo == OxYRuRFaQf){irJEiDbOQe = true;}
      if(rRDdCuHZOd == EeGHPtzDcS){pLDYWYZNGK = true;}
      if(AzzKRWjTGc == hnVNJlMxDC){OyHRWgrWRH = true;}
      if(WnVmoukyAw == aHsHPKdLlD){nXYRKDYadA = true;}
      while(EeGHPtzDcS == rRDdCuHZOd){zozjTrkAKk = true;}
      while(hnVNJlMxDC == hnVNJlMxDC){NtejYHIbSF = true;}
      while(aHsHPKdLlD == aHsHPKdLlD){fjuNRJMuyC = true;}
      if(jUoFWRQpNU == true){jUoFWRQpNU = false;}
      if(uYYFQobuPr == true){uYYFQobuPr = false;}
      if(uJwONxlyrE == true){uJwONxlyrE = false;}
      if(QnQZhNzQqq == true){QnQZhNzQqq = false;}
      if(VWjiHChmqZ == true){VWjiHChmqZ = false;}
      if(hiutHaYaqY == true){hiutHaYaqY = false;}
      if(fRyIEGHzXD == true){fRyIEGHzXD = false;}
      if(pLDYWYZNGK == true){pLDYWYZNGK = false;}
      if(OyHRWgrWRH == true){OyHRWgrWRH = false;}
      if(nXYRKDYadA == true){nXYRKDYadA = false;}
      if(uhPmjVeWWi == true){uhPmjVeWWi = false;}
      if(BKTfKhJfkW == true){BKTfKhJfkW = false;}
      if(OkhQORmlNS == true){OkhQORmlNS = false;}
      if(AyiFPfiTgA == true){AyiFPfiTgA = false;}
      if(CVzhFdDrHc == true){CVzhFdDrHc = false;}
      if(trpHlJAyYS == true){trpHlJAyYS = false;}
      if(irJEiDbOQe == true){irJEiDbOQe = false;}
      if(zozjTrkAKk == true){zozjTrkAKk = false;}
      if(NtejYHIbSF == true){NtejYHIbSF = false;}
      if(fjuNRJMuyC == true){fjuNRJMuyC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOLUOYQVTS
{ 
  void kVJgnlZVSq()
  { 
      bool rtukVrKxra = false;
      bool LTxxUwTFmn = false;
      bool frAuDRrezC = false;
      bool VGwtltkOgg = false;
      bool JoMeMtWyig = false;
      bool bRwCQzsAgD = false;
      bool AfxpEEWCKa = false;
      bool KEXFdpfVhJ = false;
      bool utuSZEJscl = false;
      bool AkgdgdrVaH = false;
      bool WTmIVWspYa = false;
      bool TXRXIFjdQz = false;
      bool tdZXaZWtXA = false;
      bool yJtalbGmxC = false;
      bool KTUCSbSJUb = false;
      bool tNFaMssPgu = false;
      bool AzSYbKdplg = false;
      bool ywgNoaIXFz = false;
      bool HNZwFkESNr = false;
      bool hqGCCLBwZI = false;
      string lGBRSNEBLP;
      string QoODoLSqTV;
      string RlKxIQLYmB;
      string LljExhmPtE;
      string WHRIasCEEY;
      string YVjShAwEIC;
      string BeNJDdEJGH;
      string YCwOyJTBWO;
      string OGTOboCRWx;
      string khHrCqtHEw;
      string osyxAWYUTX;
      string ftgsnuKzhO;
      string bmlIVptELG;
      string PMwaZUIWOF;
      string QgxzQpBODH;
      string guZpUBGobJ;
      string bUJNISyGSS;
      string lnjcxtpmre;
      string nfADZUmFFX;
      string OTuEcuXipx;
      if(lGBRSNEBLP == osyxAWYUTX){rtukVrKxra = true;}
      else if(osyxAWYUTX == lGBRSNEBLP){WTmIVWspYa = true;}
      if(QoODoLSqTV == ftgsnuKzhO){LTxxUwTFmn = true;}
      else if(ftgsnuKzhO == QoODoLSqTV){TXRXIFjdQz = true;}
      if(RlKxIQLYmB == bmlIVptELG){frAuDRrezC = true;}
      else if(bmlIVptELG == RlKxIQLYmB){tdZXaZWtXA = true;}
      if(LljExhmPtE == PMwaZUIWOF){VGwtltkOgg = true;}
      else if(PMwaZUIWOF == LljExhmPtE){yJtalbGmxC = true;}
      if(WHRIasCEEY == QgxzQpBODH){JoMeMtWyig = true;}
      else if(QgxzQpBODH == WHRIasCEEY){KTUCSbSJUb = true;}
      if(YVjShAwEIC == guZpUBGobJ){bRwCQzsAgD = true;}
      else if(guZpUBGobJ == YVjShAwEIC){tNFaMssPgu = true;}
      if(BeNJDdEJGH == bUJNISyGSS){AfxpEEWCKa = true;}
      else if(bUJNISyGSS == BeNJDdEJGH){AzSYbKdplg = true;}
      if(YCwOyJTBWO == lnjcxtpmre){KEXFdpfVhJ = true;}
      if(OGTOboCRWx == nfADZUmFFX){utuSZEJscl = true;}
      if(khHrCqtHEw == OTuEcuXipx){AkgdgdrVaH = true;}
      while(lnjcxtpmre == YCwOyJTBWO){ywgNoaIXFz = true;}
      while(nfADZUmFFX == nfADZUmFFX){HNZwFkESNr = true;}
      while(OTuEcuXipx == OTuEcuXipx){hqGCCLBwZI = true;}
      if(rtukVrKxra == true){rtukVrKxra = false;}
      if(LTxxUwTFmn == true){LTxxUwTFmn = false;}
      if(frAuDRrezC == true){frAuDRrezC = false;}
      if(VGwtltkOgg == true){VGwtltkOgg = false;}
      if(JoMeMtWyig == true){JoMeMtWyig = false;}
      if(bRwCQzsAgD == true){bRwCQzsAgD = false;}
      if(AfxpEEWCKa == true){AfxpEEWCKa = false;}
      if(KEXFdpfVhJ == true){KEXFdpfVhJ = false;}
      if(utuSZEJscl == true){utuSZEJscl = false;}
      if(AkgdgdrVaH == true){AkgdgdrVaH = false;}
      if(WTmIVWspYa == true){WTmIVWspYa = false;}
      if(TXRXIFjdQz == true){TXRXIFjdQz = false;}
      if(tdZXaZWtXA == true){tdZXaZWtXA = false;}
      if(yJtalbGmxC == true){yJtalbGmxC = false;}
      if(KTUCSbSJUb == true){KTUCSbSJUb = false;}
      if(tNFaMssPgu == true){tNFaMssPgu = false;}
      if(AzSYbKdplg == true){AzSYbKdplg = false;}
      if(ywgNoaIXFz == true){ywgNoaIXFz = false;}
      if(HNZwFkESNr == true){HNZwFkESNr = false;}
      if(hqGCCLBwZI == true){hqGCCLBwZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUAVUIKKUQ
{ 
  void tsgIJrwFSL()
  { 
      bool rkCPXCbhRM = false;
      bool mJPDqEgafb = false;
      bool MXlJUzoSDy = false;
      bool sgXJHetPKi = false;
      bool ZUepPfmezh = false;
      bool qxoNYTyruY = false;
      bool NIdTTGkGuL = false;
      bool KRQxBrswsn = false;
      bool LJSUGwrKjn = false;
      bool gBUlUQpLVJ = false;
      bool ugimXYgqLg = false;
      bool aByGMDoIMX = false;
      bool NZVHeIxdbj = false;
      bool BgZjseaexh = false;
      bool OAzDNeCNYQ = false;
      bool ahzyuULaIP = false;
      bool bCPbesaOMh = false;
      bool cKLeINaRtz = false;
      bool FiFKIThboX = false;
      bool SzWgFMjXXT = false;
      string nqTCTURkVp;
      string ZIwMBShpot;
      string bOxmUgcEhq;
      string cYxgTQeCkk;
      string xwiLcsRDBl;
      string qXWcxYtghm;
      string rMDdNALOsj;
      string nfEDwffkJa;
      string OZDuzEBTit;
      string WxUysjsEyc;
      string hCKQxLSTfQ;
      string rIWGXRJHeI;
      string yqeyNpKGJM;
      string mbmgsMPlxn;
      string khnSCNaOaa;
      string ZkYodpWLDG;
      string AMJSdPVoMK;
      string CXJqWQCMwz;
      string PweilCCxDD;
      string pDhpmYXVol;
      if(nqTCTURkVp == hCKQxLSTfQ){rkCPXCbhRM = true;}
      else if(hCKQxLSTfQ == nqTCTURkVp){ugimXYgqLg = true;}
      if(ZIwMBShpot == rIWGXRJHeI){mJPDqEgafb = true;}
      else if(rIWGXRJHeI == ZIwMBShpot){aByGMDoIMX = true;}
      if(bOxmUgcEhq == yqeyNpKGJM){MXlJUzoSDy = true;}
      else if(yqeyNpKGJM == bOxmUgcEhq){NZVHeIxdbj = true;}
      if(cYxgTQeCkk == mbmgsMPlxn){sgXJHetPKi = true;}
      else if(mbmgsMPlxn == cYxgTQeCkk){BgZjseaexh = true;}
      if(xwiLcsRDBl == khnSCNaOaa){ZUepPfmezh = true;}
      else if(khnSCNaOaa == xwiLcsRDBl){OAzDNeCNYQ = true;}
      if(qXWcxYtghm == ZkYodpWLDG){qxoNYTyruY = true;}
      else if(ZkYodpWLDG == qXWcxYtghm){ahzyuULaIP = true;}
      if(rMDdNALOsj == AMJSdPVoMK){NIdTTGkGuL = true;}
      else if(AMJSdPVoMK == rMDdNALOsj){bCPbesaOMh = true;}
      if(nfEDwffkJa == CXJqWQCMwz){KRQxBrswsn = true;}
      if(OZDuzEBTit == PweilCCxDD){LJSUGwrKjn = true;}
      if(WxUysjsEyc == pDhpmYXVol){gBUlUQpLVJ = true;}
      while(CXJqWQCMwz == nfEDwffkJa){cKLeINaRtz = true;}
      while(PweilCCxDD == PweilCCxDD){FiFKIThboX = true;}
      while(pDhpmYXVol == pDhpmYXVol){SzWgFMjXXT = true;}
      if(rkCPXCbhRM == true){rkCPXCbhRM = false;}
      if(mJPDqEgafb == true){mJPDqEgafb = false;}
      if(MXlJUzoSDy == true){MXlJUzoSDy = false;}
      if(sgXJHetPKi == true){sgXJHetPKi = false;}
      if(ZUepPfmezh == true){ZUepPfmezh = false;}
      if(qxoNYTyruY == true){qxoNYTyruY = false;}
      if(NIdTTGkGuL == true){NIdTTGkGuL = false;}
      if(KRQxBrswsn == true){KRQxBrswsn = false;}
      if(LJSUGwrKjn == true){LJSUGwrKjn = false;}
      if(gBUlUQpLVJ == true){gBUlUQpLVJ = false;}
      if(ugimXYgqLg == true){ugimXYgqLg = false;}
      if(aByGMDoIMX == true){aByGMDoIMX = false;}
      if(NZVHeIxdbj == true){NZVHeIxdbj = false;}
      if(BgZjseaexh == true){BgZjseaexh = false;}
      if(OAzDNeCNYQ == true){OAzDNeCNYQ = false;}
      if(ahzyuULaIP == true){ahzyuULaIP = false;}
      if(bCPbesaOMh == true){bCPbesaOMh = false;}
      if(cKLeINaRtz == true){cKLeINaRtz = false;}
      if(FiFKIThboX == true){FiFKIThboX = false;}
      if(SzWgFMjXXT == true){SzWgFMjXXT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UIABTXFJSY
{ 
  void buWeMSXEPi()
  { 
      bool caGXJeTzMb = false;
      bool gDClMrpsLN = false;
      bool GnHmRtxKdO = false;
      bool OiPVDtGDcF = false;
      bool ZzTVXeLzmN = false;
      bool JOkTYnSTGP = false;
      bool hJUyMxmfiS = false;
      bool llQFnHTkOl = false;
      bool hyWQFAywxO = false;
      bool amwNXQdVIa = false;
      bool rePUbWxeeQ = false;
      bool UgEUgilDrM = false;
      bool yphTqypDhW = false;
      bool dycnsDhCnh = false;
      bool CTQgtshbgn = false;
      bool eZcubBwwcc = false;
      bool gtxImVEQac = false;
      bool BiPJKeZBZx = false;
      bool PNVsrDUgLr = false;
      bool GlYLBHWItX = false;
      string gcQchqtwGZ;
      string hKMlYhBcPx;
      string ddjEKYJEla;
      string LysBaTwcSX;
      string sgNVuEzBCU;
      string sbaBdDrMRJ;
      string hpJfOiRKKF;
      string kYJrDwPOJG;
      string YIBQhiXqWX;
      string ajLJoDXhGL;
      string mnqxiURixg;
      string mcDLkYnrye;
      string LZmldBNACA;
      string YhIxSjREhN;
      string QnspkxfzYQ;
      string OejazNBESh;
      string GRfxIFUFrA;
      string HiKkOXfxBf;
      string UNblktygyF;
      string iNlAGzIwgf;
      if(gcQchqtwGZ == mnqxiURixg){caGXJeTzMb = true;}
      else if(mnqxiURixg == gcQchqtwGZ){rePUbWxeeQ = true;}
      if(hKMlYhBcPx == mcDLkYnrye){gDClMrpsLN = true;}
      else if(mcDLkYnrye == hKMlYhBcPx){UgEUgilDrM = true;}
      if(ddjEKYJEla == LZmldBNACA){GnHmRtxKdO = true;}
      else if(LZmldBNACA == ddjEKYJEla){yphTqypDhW = true;}
      if(LysBaTwcSX == YhIxSjREhN){OiPVDtGDcF = true;}
      else if(YhIxSjREhN == LysBaTwcSX){dycnsDhCnh = true;}
      if(sgNVuEzBCU == QnspkxfzYQ){ZzTVXeLzmN = true;}
      else if(QnspkxfzYQ == sgNVuEzBCU){CTQgtshbgn = true;}
      if(sbaBdDrMRJ == OejazNBESh){JOkTYnSTGP = true;}
      else if(OejazNBESh == sbaBdDrMRJ){eZcubBwwcc = true;}
      if(hpJfOiRKKF == GRfxIFUFrA){hJUyMxmfiS = true;}
      else if(GRfxIFUFrA == hpJfOiRKKF){gtxImVEQac = true;}
      if(kYJrDwPOJG == HiKkOXfxBf){llQFnHTkOl = true;}
      if(YIBQhiXqWX == UNblktygyF){hyWQFAywxO = true;}
      if(ajLJoDXhGL == iNlAGzIwgf){amwNXQdVIa = true;}
      while(HiKkOXfxBf == kYJrDwPOJG){BiPJKeZBZx = true;}
      while(UNblktygyF == UNblktygyF){PNVsrDUgLr = true;}
      while(iNlAGzIwgf == iNlAGzIwgf){GlYLBHWItX = true;}
      if(caGXJeTzMb == true){caGXJeTzMb = false;}
      if(gDClMrpsLN == true){gDClMrpsLN = false;}
      if(GnHmRtxKdO == true){GnHmRtxKdO = false;}
      if(OiPVDtGDcF == true){OiPVDtGDcF = false;}
      if(ZzTVXeLzmN == true){ZzTVXeLzmN = false;}
      if(JOkTYnSTGP == true){JOkTYnSTGP = false;}
      if(hJUyMxmfiS == true){hJUyMxmfiS = false;}
      if(llQFnHTkOl == true){llQFnHTkOl = false;}
      if(hyWQFAywxO == true){hyWQFAywxO = false;}
      if(amwNXQdVIa == true){amwNXQdVIa = false;}
      if(rePUbWxeeQ == true){rePUbWxeeQ = false;}
      if(UgEUgilDrM == true){UgEUgilDrM = false;}
      if(yphTqypDhW == true){yphTqypDhW = false;}
      if(dycnsDhCnh == true){dycnsDhCnh = false;}
      if(CTQgtshbgn == true){CTQgtshbgn = false;}
      if(eZcubBwwcc == true){eZcubBwwcc = false;}
      if(gtxImVEQac == true){gtxImVEQac = false;}
      if(BiPJKeZBZx == true){BiPJKeZBZx = false;}
      if(PNVsrDUgLr == true){PNVsrDUgLr = false;}
      if(GlYLBHWItX == true){GlYLBHWItX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQOLICCBDC
{ 
  void YBGBbUUkKk()
  { 
      bool yArIUjUYss = false;
      bool liWaErJICP = false;
      bool lJtXxDLNnE = false;
      bool AfIalDBJkw = false;
      bool TzaMireihl = false;
      bool eYbpnnGUKR = false;
      bool XHkosGZunA = false;
      bool qAWFwlhhnF = false;
      bool YceCZaDRmy = false;
      bool xgyTYLOlTb = false;
      bool RitgueBVtB = false;
      bool FXfFrtbhOS = false;
      bool DIIpCJBDgj = false;
      bool XwOLnohxGt = false;
      bool YhXkrYAsad = false;
      bool jfWAYJZEek = false;
      bool cynKdJJTQD = false;
      bool LdaUsUjXxc = false;
      bool JIcDzrYNme = false;
      bool PdSVRatMHi = false;
      string UQdIdQrVHR;
      string ntVkrscPKb;
      string zwTJJdyBPk;
      string IUoSkNDxgY;
      string pXAJXXcLEE;
      string zMeHqXxTyA;
      string SpGWISEDzd;
      string ofhllbuJll;
      string AlxKkwohbN;
      string QizgGzQdAE;
      string SZLZOTdsUP;
      string bmhMzfsukM;
      string dWblNFgAfl;
      string KRIgSZaWuR;
      string SuMLkcBlhZ;
      string GUsnawyYMI;
      string mcNhFKeAtY;
      string FWATthJPBk;
      string EtSFfoYUGV;
      string aBKleohdGZ;
      if(UQdIdQrVHR == SZLZOTdsUP){yArIUjUYss = true;}
      else if(SZLZOTdsUP == UQdIdQrVHR){RitgueBVtB = true;}
      if(ntVkrscPKb == bmhMzfsukM){liWaErJICP = true;}
      else if(bmhMzfsukM == ntVkrscPKb){FXfFrtbhOS = true;}
      if(zwTJJdyBPk == dWblNFgAfl){lJtXxDLNnE = true;}
      else if(dWblNFgAfl == zwTJJdyBPk){DIIpCJBDgj = true;}
      if(IUoSkNDxgY == KRIgSZaWuR){AfIalDBJkw = true;}
      else if(KRIgSZaWuR == IUoSkNDxgY){XwOLnohxGt = true;}
      if(pXAJXXcLEE == SuMLkcBlhZ){TzaMireihl = true;}
      else if(SuMLkcBlhZ == pXAJXXcLEE){YhXkrYAsad = true;}
      if(zMeHqXxTyA == GUsnawyYMI){eYbpnnGUKR = true;}
      else if(GUsnawyYMI == zMeHqXxTyA){jfWAYJZEek = true;}
      if(SpGWISEDzd == mcNhFKeAtY){XHkosGZunA = true;}
      else if(mcNhFKeAtY == SpGWISEDzd){cynKdJJTQD = true;}
      if(ofhllbuJll == FWATthJPBk){qAWFwlhhnF = true;}
      if(AlxKkwohbN == EtSFfoYUGV){YceCZaDRmy = true;}
      if(QizgGzQdAE == aBKleohdGZ){xgyTYLOlTb = true;}
      while(FWATthJPBk == ofhllbuJll){LdaUsUjXxc = true;}
      while(EtSFfoYUGV == EtSFfoYUGV){JIcDzrYNme = true;}
      while(aBKleohdGZ == aBKleohdGZ){PdSVRatMHi = true;}
      if(yArIUjUYss == true){yArIUjUYss = false;}
      if(liWaErJICP == true){liWaErJICP = false;}
      if(lJtXxDLNnE == true){lJtXxDLNnE = false;}
      if(AfIalDBJkw == true){AfIalDBJkw = false;}
      if(TzaMireihl == true){TzaMireihl = false;}
      if(eYbpnnGUKR == true){eYbpnnGUKR = false;}
      if(XHkosGZunA == true){XHkosGZunA = false;}
      if(qAWFwlhhnF == true){qAWFwlhhnF = false;}
      if(YceCZaDRmy == true){YceCZaDRmy = false;}
      if(xgyTYLOlTb == true){xgyTYLOlTb = false;}
      if(RitgueBVtB == true){RitgueBVtB = false;}
      if(FXfFrtbhOS == true){FXfFrtbhOS = false;}
      if(DIIpCJBDgj == true){DIIpCJBDgj = false;}
      if(XwOLnohxGt == true){XwOLnohxGt = false;}
      if(YhXkrYAsad == true){YhXkrYAsad = false;}
      if(jfWAYJZEek == true){jfWAYJZEek = false;}
      if(cynKdJJTQD == true){cynKdJJTQD = false;}
      if(LdaUsUjXxc == true){LdaUsUjXxc = false;}
      if(JIcDzrYNme == true){JIcDzrYNme = false;}
      if(PdSVRatMHi == true){PdSVRatMHi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGJERMOSPU
{ 
  void NyeRNMUfTF()
  { 
      bool TmpbyasABY = false;
      bool jkJBqcphjh = false;
      bool edLgDrsyaX = false;
      bool dLuDGiBKZn = false;
      bool xwtpIRVVXA = false;
      bool gSGomoaIYF = false;
      bool guYctXoGuH = false;
      bool beHukijUYk = false;
      bool WWaaqLEGQQ = false;
      bool IrlUHCWQwj = false;
      bool cPaPYBKLDD = false;
      bool FGjmiJUyki = false;
      bool Tiodzismni = false;
      bool LSYoIHwKCp = false;
      bool AsDMLBHykx = false;
      bool hYeMPsZxPo = false;
      bool HWWUrlgueb = false;
      bool NJuuiaebRy = false;
      bool btCpBlmLYO = false;
      bool gyuMhcVhUY = false;
      string fPzwVnxmFD;
      string EKPzrGLGzs;
      string IsQugeueUc;
      string MJUgKKMiny;
      string bOjhkVCler;
      string DPBXOmzEOq;
      string sRSbqtphog;
      string sbRARsJhJK;
      string bIzbZxIwRX;
      string LITxFKwHpp;
      string fTxyzbxAGV;
      string dRtEOjSpCt;
      string lsPQVkHUtG;
      string wBqSeHLBcx;
      string zHpwttNPhV;
      string rGEwDlEfcN;
      string UcGzYbZaZG;
      string XRMEueCSVa;
      string WqlXOpwuPr;
      string DfXOcWAqXS;
      if(fPzwVnxmFD == fTxyzbxAGV){TmpbyasABY = true;}
      else if(fTxyzbxAGV == fPzwVnxmFD){cPaPYBKLDD = true;}
      if(EKPzrGLGzs == dRtEOjSpCt){jkJBqcphjh = true;}
      else if(dRtEOjSpCt == EKPzrGLGzs){FGjmiJUyki = true;}
      if(IsQugeueUc == lsPQVkHUtG){edLgDrsyaX = true;}
      else if(lsPQVkHUtG == IsQugeueUc){Tiodzismni = true;}
      if(MJUgKKMiny == wBqSeHLBcx){dLuDGiBKZn = true;}
      else if(wBqSeHLBcx == MJUgKKMiny){LSYoIHwKCp = true;}
      if(bOjhkVCler == zHpwttNPhV){xwtpIRVVXA = true;}
      else if(zHpwttNPhV == bOjhkVCler){AsDMLBHykx = true;}
      if(DPBXOmzEOq == rGEwDlEfcN){gSGomoaIYF = true;}
      else if(rGEwDlEfcN == DPBXOmzEOq){hYeMPsZxPo = true;}
      if(sRSbqtphog == UcGzYbZaZG){guYctXoGuH = true;}
      else if(UcGzYbZaZG == sRSbqtphog){HWWUrlgueb = true;}
      if(sbRARsJhJK == XRMEueCSVa){beHukijUYk = true;}
      if(bIzbZxIwRX == WqlXOpwuPr){WWaaqLEGQQ = true;}
      if(LITxFKwHpp == DfXOcWAqXS){IrlUHCWQwj = true;}
      while(XRMEueCSVa == sbRARsJhJK){NJuuiaebRy = true;}
      while(WqlXOpwuPr == WqlXOpwuPr){btCpBlmLYO = true;}
      while(DfXOcWAqXS == DfXOcWAqXS){gyuMhcVhUY = true;}
      if(TmpbyasABY == true){TmpbyasABY = false;}
      if(jkJBqcphjh == true){jkJBqcphjh = false;}
      if(edLgDrsyaX == true){edLgDrsyaX = false;}
      if(dLuDGiBKZn == true){dLuDGiBKZn = false;}
      if(xwtpIRVVXA == true){xwtpIRVVXA = false;}
      if(gSGomoaIYF == true){gSGomoaIYF = false;}
      if(guYctXoGuH == true){guYctXoGuH = false;}
      if(beHukijUYk == true){beHukijUYk = false;}
      if(WWaaqLEGQQ == true){WWaaqLEGQQ = false;}
      if(IrlUHCWQwj == true){IrlUHCWQwj = false;}
      if(cPaPYBKLDD == true){cPaPYBKLDD = false;}
      if(FGjmiJUyki == true){FGjmiJUyki = false;}
      if(Tiodzismni == true){Tiodzismni = false;}
      if(LSYoIHwKCp == true){LSYoIHwKCp = false;}
      if(AsDMLBHykx == true){AsDMLBHykx = false;}
      if(hYeMPsZxPo == true){hYeMPsZxPo = false;}
      if(HWWUrlgueb == true){HWWUrlgueb = false;}
      if(NJuuiaebRy == true){NJuuiaebRy = false;}
      if(btCpBlmLYO == true){btCpBlmLYO = false;}
      if(gyuMhcVhUY == true){gyuMhcVhUY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSOIOVDFYN
{ 
  void HsabpSOnCy()
  { 
      bool uwPflRSsgJ = false;
      bool QVdhZVFlGE = false;
      bool zQXRlAZpIo = false;
      bool YcWQjQRgJo = false;
      bool LANHtUMcfR = false;
      bool EZnstdYxtl = false;
      bool qbjrkmzNxI = false;
      bool DYbRszDQXQ = false;
      bool nxKqjyndWF = false;
      bool rUmXyjPVVG = false;
      bool UzeWNfyWAt = false;
      bool aHZcysQsHl = false;
      bool yVqqPilETI = false;
      bool ihtQwoRncE = false;
      bool ARcbektKYE = false;
      bool TWNiHzInGe = false;
      bool tsDrLsNJgJ = false;
      bool acPClgrOMe = false;
      bool naeOoMTKIw = false;
      bool gdgyKGOkQl = false;
      string oNiKdBhfDk;
      string PkzYAQUyDL;
      string ZyntJnRCIu;
      string rgXkITcXJg;
      string qbkCHkJBfb;
      string abeqaqYoBp;
      string jfWHshNNPg;
      string nwnWUyMklX;
      string dPWgUPCfKR;
      string tnVTxLEcJZ;
      string WulzmdmHWc;
      string dmCcLTIpmc;
      string ehDylzZUZJ;
      string sjbMAidXsq;
      string ctJhnGlrIc;
      string COpgtornMm;
      string DShNitLocc;
      string pkwwzkYVKe;
      string NhMwGdttRK;
      string qpKFmKLuys;
      if(oNiKdBhfDk == WulzmdmHWc){uwPflRSsgJ = true;}
      else if(WulzmdmHWc == oNiKdBhfDk){UzeWNfyWAt = true;}
      if(PkzYAQUyDL == dmCcLTIpmc){QVdhZVFlGE = true;}
      else if(dmCcLTIpmc == PkzYAQUyDL){aHZcysQsHl = true;}
      if(ZyntJnRCIu == ehDylzZUZJ){zQXRlAZpIo = true;}
      else if(ehDylzZUZJ == ZyntJnRCIu){yVqqPilETI = true;}
      if(rgXkITcXJg == sjbMAidXsq){YcWQjQRgJo = true;}
      else if(sjbMAidXsq == rgXkITcXJg){ihtQwoRncE = true;}
      if(qbkCHkJBfb == ctJhnGlrIc){LANHtUMcfR = true;}
      else if(ctJhnGlrIc == qbkCHkJBfb){ARcbektKYE = true;}
      if(abeqaqYoBp == COpgtornMm){EZnstdYxtl = true;}
      else if(COpgtornMm == abeqaqYoBp){TWNiHzInGe = true;}
      if(jfWHshNNPg == DShNitLocc){qbjrkmzNxI = true;}
      else if(DShNitLocc == jfWHshNNPg){tsDrLsNJgJ = true;}
      if(nwnWUyMklX == pkwwzkYVKe){DYbRszDQXQ = true;}
      if(dPWgUPCfKR == NhMwGdttRK){nxKqjyndWF = true;}
      if(tnVTxLEcJZ == qpKFmKLuys){rUmXyjPVVG = true;}
      while(pkwwzkYVKe == nwnWUyMklX){acPClgrOMe = true;}
      while(NhMwGdttRK == NhMwGdttRK){naeOoMTKIw = true;}
      while(qpKFmKLuys == qpKFmKLuys){gdgyKGOkQl = true;}
      if(uwPflRSsgJ == true){uwPflRSsgJ = false;}
      if(QVdhZVFlGE == true){QVdhZVFlGE = false;}
      if(zQXRlAZpIo == true){zQXRlAZpIo = false;}
      if(YcWQjQRgJo == true){YcWQjQRgJo = false;}
      if(LANHtUMcfR == true){LANHtUMcfR = false;}
      if(EZnstdYxtl == true){EZnstdYxtl = false;}
      if(qbjrkmzNxI == true){qbjrkmzNxI = false;}
      if(DYbRszDQXQ == true){DYbRszDQXQ = false;}
      if(nxKqjyndWF == true){nxKqjyndWF = false;}
      if(rUmXyjPVVG == true){rUmXyjPVVG = false;}
      if(UzeWNfyWAt == true){UzeWNfyWAt = false;}
      if(aHZcysQsHl == true){aHZcysQsHl = false;}
      if(yVqqPilETI == true){yVqqPilETI = false;}
      if(ihtQwoRncE == true){ihtQwoRncE = false;}
      if(ARcbektKYE == true){ARcbektKYE = false;}
      if(TWNiHzInGe == true){TWNiHzInGe = false;}
      if(tsDrLsNJgJ == true){tsDrLsNJgJ = false;}
      if(acPClgrOMe == true){acPClgrOMe = false;}
      if(naeOoMTKIw == true){naeOoMTKIw = false;}
      if(gdgyKGOkQl == true){gdgyKGOkQl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGIDXDJVBJ
{ 
  void tFnlcepazY()
  { 
      bool CkqYqsBMoe = false;
      bool FdTtLbMHiW = false;
      bool kbZHWrxUxl = false;
      bool DMJbPzAMnl = false;
      bool HoYCAGagtk = false;
      bool iLVYrZLiCz = false;
      bool ugPCbsUreL = false;
      bool azSwPuCXHP = false;
      bool RQaLCqpkjo = false;
      bool nQKoqaYWZH = false;
      bool khChJjrZJw = false;
      bool WmblheGDzk = false;
      bool CiIpXKndFo = false;
      bool VfyAdiOsBS = false;
      bool zQbmRAoXGL = false;
      bool TVXoECZMJz = false;
      bool uNUTZqoaHz = false;
      bool QNBfklHUXW = false;
      bool VPXsUAHJwb = false;
      bool ICiCWkwHNZ = false;
      string kpmsuSuSBo;
      string nqgQRFasBn;
      string unbfNhzTPL;
      string ADYDWjqdTE;
      string IGCoQaulGn;
      string NowrHwOGfN;
      string SbDonkRdsg;
      string OwYwfollPm;
      string lMNbyLGfuZ;
      string VjyGkgDNAf;
      string IRrYZRQzMS;
      string KbqraGNbpc;
      string dkhTLdxRLy;
      string kXkidTTnBg;
      string tHTcOssFfe;
      string SbWWBXjYMw;
      string TynOglpHOG;
      string mZZJhVRFER;
      string krlffJBNhG;
      string jtbFMwSEuc;
      if(kpmsuSuSBo == IRrYZRQzMS){CkqYqsBMoe = true;}
      else if(IRrYZRQzMS == kpmsuSuSBo){khChJjrZJw = true;}
      if(nqgQRFasBn == KbqraGNbpc){FdTtLbMHiW = true;}
      else if(KbqraGNbpc == nqgQRFasBn){WmblheGDzk = true;}
      if(unbfNhzTPL == dkhTLdxRLy){kbZHWrxUxl = true;}
      else if(dkhTLdxRLy == unbfNhzTPL){CiIpXKndFo = true;}
      if(ADYDWjqdTE == kXkidTTnBg){DMJbPzAMnl = true;}
      else if(kXkidTTnBg == ADYDWjqdTE){VfyAdiOsBS = true;}
      if(IGCoQaulGn == tHTcOssFfe){HoYCAGagtk = true;}
      else if(tHTcOssFfe == IGCoQaulGn){zQbmRAoXGL = true;}
      if(NowrHwOGfN == SbWWBXjYMw){iLVYrZLiCz = true;}
      else if(SbWWBXjYMw == NowrHwOGfN){TVXoECZMJz = true;}
      if(SbDonkRdsg == TynOglpHOG){ugPCbsUreL = true;}
      else if(TynOglpHOG == SbDonkRdsg){uNUTZqoaHz = true;}
      if(OwYwfollPm == mZZJhVRFER){azSwPuCXHP = true;}
      if(lMNbyLGfuZ == krlffJBNhG){RQaLCqpkjo = true;}
      if(VjyGkgDNAf == jtbFMwSEuc){nQKoqaYWZH = true;}
      while(mZZJhVRFER == OwYwfollPm){QNBfklHUXW = true;}
      while(krlffJBNhG == krlffJBNhG){VPXsUAHJwb = true;}
      while(jtbFMwSEuc == jtbFMwSEuc){ICiCWkwHNZ = true;}
      if(CkqYqsBMoe == true){CkqYqsBMoe = false;}
      if(FdTtLbMHiW == true){FdTtLbMHiW = false;}
      if(kbZHWrxUxl == true){kbZHWrxUxl = false;}
      if(DMJbPzAMnl == true){DMJbPzAMnl = false;}
      if(HoYCAGagtk == true){HoYCAGagtk = false;}
      if(iLVYrZLiCz == true){iLVYrZLiCz = false;}
      if(ugPCbsUreL == true){ugPCbsUreL = false;}
      if(azSwPuCXHP == true){azSwPuCXHP = false;}
      if(RQaLCqpkjo == true){RQaLCqpkjo = false;}
      if(nQKoqaYWZH == true){nQKoqaYWZH = false;}
      if(khChJjrZJw == true){khChJjrZJw = false;}
      if(WmblheGDzk == true){WmblheGDzk = false;}
      if(CiIpXKndFo == true){CiIpXKndFo = false;}
      if(VfyAdiOsBS == true){VfyAdiOsBS = false;}
      if(zQbmRAoXGL == true){zQbmRAoXGL = false;}
      if(TVXoECZMJz == true){TVXoECZMJz = false;}
      if(uNUTZqoaHz == true){uNUTZqoaHz = false;}
      if(QNBfklHUXW == true){QNBfklHUXW = false;}
      if(VPXsUAHJwb == true){VPXsUAHJwb = false;}
      if(ICiCWkwHNZ == true){ICiCWkwHNZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDNKHVDLMJ
{ 
  void QbyONtLKBX()
  { 
      bool eXQgBgNrRG = false;
      bool XLpGmemFRg = false;
      bool jsEEfRdNpx = false;
      bool qVxjiDeoxH = false;
      bool pFiOaQhzrp = false;
      bool KttjFlSLBi = false;
      bool CACUPBOGWj = false;
      bool AxHJpeKodO = false;
      bool ieUzlwbMdx = false;
      bool jTnNFpDOzY = false;
      bool CbbIpMljsa = false;
      bool adhlAWfChS = false;
      bool YCbZAgJtDA = false;
      bool bwpEMGDLJZ = false;
      bool KqSDVFkBNh = false;
      bool JAffzAACIJ = false;
      bool DrfrzemdZs = false;
      bool TTsIHgiYEt = false;
      bool uIgVpaPJEL = false;
      bool GACAVSLZDp = false;
      string YOqJGFKtTl;
      string qFPPyCiSNC;
      string PYYpsAXQcV;
      string IBZzIYpqGC;
      string UKKtgjGVhy;
      string hgEtAzoAQF;
      string gsRxdpePHY;
      string MqMLhEOeII;
      string tCienaweyI;
      string joaAVasMPp;
      string EqOJkqUsMw;
      string jJqHLdJlIC;
      string szQynXPLoG;
      string KCORDCnZsx;
      string GDRCXZxToq;
      string QGENxFZPUN;
      string aIDGkhtZDI;
      string pjsLupgOZO;
      string auVyoExBUy;
      string cYFfVxzLRp;
      if(YOqJGFKtTl == EqOJkqUsMw){eXQgBgNrRG = true;}
      else if(EqOJkqUsMw == YOqJGFKtTl){CbbIpMljsa = true;}
      if(qFPPyCiSNC == jJqHLdJlIC){XLpGmemFRg = true;}
      else if(jJqHLdJlIC == qFPPyCiSNC){adhlAWfChS = true;}
      if(PYYpsAXQcV == szQynXPLoG){jsEEfRdNpx = true;}
      else if(szQynXPLoG == PYYpsAXQcV){YCbZAgJtDA = true;}
      if(IBZzIYpqGC == KCORDCnZsx){qVxjiDeoxH = true;}
      else if(KCORDCnZsx == IBZzIYpqGC){bwpEMGDLJZ = true;}
      if(UKKtgjGVhy == GDRCXZxToq){pFiOaQhzrp = true;}
      else if(GDRCXZxToq == UKKtgjGVhy){KqSDVFkBNh = true;}
      if(hgEtAzoAQF == QGENxFZPUN){KttjFlSLBi = true;}
      else if(QGENxFZPUN == hgEtAzoAQF){JAffzAACIJ = true;}
      if(gsRxdpePHY == aIDGkhtZDI){CACUPBOGWj = true;}
      else if(aIDGkhtZDI == gsRxdpePHY){DrfrzemdZs = true;}
      if(MqMLhEOeII == pjsLupgOZO){AxHJpeKodO = true;}
      if(tCienaweyI == auVyoExBUy){ieUzlwbMdx = true;}
      if(joaAVasMPp == cYFfVxzLRp){jTnNFpDOzY = true;}
      while(pjsLupgOZO == MqMLhEOeII){TTsIHgiYEt = true;}
      while(auVyoExBUy == auVyoExBUy){uIgVpaPJEL = true;}
      while(cYFfVxzLRp == cYFfVxzLRp){GACAVSLZDp = true;}
      if(eXQgBgNrRG == true){eXQgBgNrRG = false;}
      if(XLpGmemFRg == true){XLpGmemFRg = false;}
      if(jsEEfRdNpx == true){jsEEfRdNpx = false;}
      if(qVxjiDeoxH == true){qVxjiDeoxH = false;}
      if(pFiOaQhzrp == true){pFiOaQhzrp = false;}
      if(KttjFlSLBi == true){KttjFlSLBi = false;}
      if(CACUPBOGWj == true){CACUPBOGWj = false;}
      if(AxHJpeKodO == true){AxHJpeKodO = false;}
      if(ieUzlwbMdx == true){ieUzlwbMdx = false;}
      if(jTnNFpDOzY == true){jTnNFpDOzY = false;}
      if(CbbIpMljsa == true){CbbIpMljsa = false;}
      if(adhlAWfChS == true){adhlAWfChS = false;}
      if(YCbZAgJtDA == true){YCbZAgJtDA = false;}
      if(bwpEMGDLJZ == true){bwpEMGDLJZ = false;}
      if(KqSDVFkBNh == true){KqSDVFkBNh = false;}
      if(JAffzAACIJ == true){JAffzAACIJ = false;}
      if(DrfrzemdZs == true){DrfrzemdZs = false;}
      if(TTsIHgiYEt == true){TTsIHgiYEt = false;}
      if(uIgVpaPJEL == true){uIgVpaPJEL = false;}
      if(GACAVSLZDp == true){GACAVSLZDp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRYDXHBGGM
{ 
  void sXDfSpQzip()
  { 
      bool XJflIjSMaA = false;
      bool yYBeVmetHe = false;
      bool WMhsccceQV = false;
      bool mPIdpFdaMx = false;
      bool VbfFMaROmX = false;
      bool FmyEpLalIf = false;
      bool GmwENhPWoP = false;
      bool IDhJIufbgC = false;
      bool KOrsQARDne = false;
      bool eqRgpheard = false;
      bool KuYWOBEnwt = false;
      bool eyFGUruDnM = false;
      bool QMhKkQkASZ = false;
      bool PEjCrOoVdO = false;
      bool ucHtzflLMy = false;
      bool mbleMyMOky = false;
      bool PEUVdZODOF = false;
      bool DYYZRnEnKF = false;
      bool eZnUmnREot = false;
      bool CajfypHlPZ = false;
      string zNjqextpBg;
      string bBqhUNnNla;
      string FKBHpHOuPO;
      string AULZCNoWdx;
      string SRKwtadpHW;
      string MDflEoMbAW;
      string hzalfHpQeG;
      string YRioImAENP;
      string dYnrCxoYUN;
      string AMVHOSpXPm;
      string jMKAytTqdR;
      string nIOjsJLiji;
      string SQwRGMwbZo;
      string xcnaeQNntI;
      string cyuDYrxkOE;
      string HHngUTQssk;
      string xrQoTLTnEb;
      string wXnaGUVrrN;
      string OKNVgonHFL;
      string zTtIKjgFiN;
      if(zNjqextpBg == jMKAytTqdR){XJflIjSMaA = true;}
      else if(jMKAytTqdR == zNjqextpBg){KuYWOBEnwt = true;}
      if(bBqhUNnNla == nIOjsJLiji){yYBeVmetHe = true;}
      else if(nIOjsJLiji == bBqhUNnNla){eyFGUruDnM = true;}
      if(FKBHpHOuPO == SQwRGMwbZo){WMhsccceQV = true;}
      else if(SQwRGMwbZo == FKBHpHOuPO){QMhKkQkASZ = true;}
      if(AULZCNoWdx == xcnaeQNntI){mPIdpFdaMx = true;}
      else if(xcnaeQNntI == AULZCNoWdx){PEjCrOoVdO = true;}
      if(SRKwtadpHW == cyuDYrxkOE){VbfFMaROmX = true;}
      else if(cyuDYrxkOE == SRKwtadpHW){ucHtzflLMy = true;}
      if(MDflEoMbAW == HHngUTQssk){FmyEpLalIf = true;}
      else if(HHngUTQssk == MDflEoMbAW){mbleMyMOky = true;}
      if(hzalfHpQeG == xrQoTLTnEb){GmwENhPWoP = true;}
      else if(xrQoTLTnEb == hzalfHpQeG){PEUVdZODOF = true;}
      if(YRioImAENP == wXnaGUVrrN){IDhJIufbgC = true;}
      if(dYnrCxoYUN == OKNVgonHFL){KOrsQARDne = true;}
      if(AMVHOSpXPm == zTtIKjgFiN){eqRgpheard = true;}
      while(wXnaGUVrrN == YRioImAENP){DYYZRnEnKF = true;}
      while(OKNVgonHFL == OKNVgonHFL){eZnUmnREot = true;}
      while(zTtIKjgFiN == zTtIKjgFiN){CajfypHlPZ = true;}
      if(XJflIjSMaA == true){XJflIjSMaA = false;}
      if(yYBeVmetHe == true){yYBeVmetHe = false;}
      if(WMhsccceQV == true){WMhsccceQV = false;}
      if(mPIdpFdaMx == true){mPIdpFdaMx = false;}
      if(VbfFMaROmX == true){VbfFMaROmX = false;}
      if(FmyEpLalIf == true){FmyEpLalIf = false;}
      if(GmwENhPWoP == true){GmwENhPWoP = false;}
      if(IDhJIufbgC == true){IDhJIufbgC = false;}
      if(KOrsQARDne == true){KOrsQARDne = false;}
      if(eqRgpheard == true){eqRgpheard = false;}
      if(KuYWOBEnwt == true){KuYWOBEnwt = false;}
      if(eyFGUruDnM == true){eyFGUruDnM = false;}
      if(QMhKkQkASZ == true){QMhKkQkASZ = false;}
      if(PEjCrOoVdO == true){PEjCrOoVdO = false;}
      if(ucHtzflLMy == true){ucHtzflLMy = false;}
      if(mbleMyMOky == true){mbleMyMOky = false;}
      if(PEUVdZODOF == true){PEUVdZODOF = false;}
      if(DYYZRnEnKF == true){DYYZRnEnKF = false;}
      if(eZnUmnREot == true){eZnUmnREot = false;}
      if(CajfypHlPZ == true){CajfypHlPZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOUBDZTSLI
{ 
  void QaxtmLDNZM()
  { 
      bool BkuqDcKqDP = false;
      bool elMdSbjSAN = false;
      bool jPKOnBZtgP = false;
      bool YqRxAYPSin = false;
      bool ZsFfFbYSbu = false;
      bool EkqLJlZgCC = false;
      bool DPKmqmTOdt = false;
      bool LQjMnqKeIM = false;
      bool cGRkLnAGmO = false;
      bool yhPgjJiRoR = false;
      bool HJohimBdWS = false;
      bool auXpYwxYbC = false;
      bool lMbPucACbd = false;
      bool HrppFTRjBX = false;
      bool mWjUmDKZIm = false;
      bool MKolfthZmF = false;
      bool lyCrKhFgjF = false;
      bool eNWEPPcGbr = false;
      bool SatoRxDEKL = false;
      bool lqxuknTrKE = false;
      string VAEoiKawTG;
      string KRJlZApSpw;
      string hZqkoBjqcy;
      string fbknMcIrXs;
      string hhhZOlPjFX;
      string ruguhuJSAh;
      string ajTVahgVYw;
      string ryuwNzrRVD;
      string lzkEFkuoGR;
      string ToqoSyOLzg;
      string FsKIftAjgh;
      string CrwxubyOPp;
      string mqPHcCGFdP;
      string jgSoyrnbYL;
      string jKIXParttq;
      string zAuJsNdDfc;
      string nuGQyVYHyC;
      string mVpEFciqqB;
      string KLKmQjkJwj;
      string NkwuXoDqYt;
      if(VAEoiKawTG == FsKIftAjgh){BkuqDcKqDP = true;}
      else if(FsKIftAjgh == VAEoiKawTG){HJohimBdWS = true;}
      if(KRJlZApSpw == CrwxubyOPp){elMdSbjSAN = true;}
      else if(CrwxubyOPp == KRJlZApSpw){auXpYwxYbC = true;}
      if(hZqkoBjqcy == mqPHcCGFdP){jPKOnBZtgP = true;}
      else if(mqPHcCGFdP == hZqkoBjqcy){lMbPucACbd = true;}
      if(fbknMcIrXs == jgSoyrnbYL){YqRxAYPSin = true;}
      else if(jgSoyrnbYL == fbknMcIrXs){HrppFTRjBX = true;}
      if(hhhZOlPjFX == jKIXParttq){ZsFfFbYSbu = true;}
      else if(jKIXParttq == hhhZOlPjFX){mWjUmDKZIm = true;}
      if(ruguhuJSAh == zAuJsNdDfc){EkqLJlZgCC = true;}
      else if(zAuJsNdDfc == ruguhuJSAh){MKolfthZmF = true;}
      if(ajTVahgVYw == nuGQyVYHyC){DPKmqmTOdt = true;}
      else if(nuGQyVYHyC == ajTVahgVYw){lyCrKhFgjF = true;}
      if(ryuwNzrRVD == mVpEFciqqB){LQjMnqKeIM = true;}
      if(lzkEFkuoGR == KLKmQjkJwj){cGRkLnAGmO = true;}
      if(ToqoSyOLzg == NkwuXoDqYt){yhPgjJiRoR = true;}
      while(mVpEFciqqB == ryuwNzrRVD){eNWEPPcGbr = true;}
      while(KLKmQjkJwj == KLKmQjkJwj){SatoRxDEKL = true;}
      while(NkwuXoDqYt == NkwuXoDqYt){lqxuknTrKE = true;}
      if(BkuqDcKqDP == true){BkuqDcKqDP = false;}
      if(elMdSbjSAN == true){elMdSbjSAN = false;}
      if(jPKOnBZtgP == true){jPKOnBZtgP = false;}
      if(YqRxAYPSin == true){YqRxAYPSin = false;}
      if(ZsFfFbYSbu == true){ZsFfFbYSbu = false;}
      if(EkqLJlZgCC == true){EkqLJlZgCC = false;}
      if(DPKmqmTOdt == true){DPKmqmTOdt = false;}
      if(LQjMnqKeIM == true){LQjMnqKeIM = false;}
      if(cGRkLnAGmO == true){cGRkLnAGmO = false;}
      if(yhPgjJiRoR == true){yhPgjJiRoR = false;}
      if(HJohimBdWS == true){HJohimBdWS = false;}
      if(auXpYwxYbC == true){auXpYwxYbC = false;}
      if(lMbPucACbd == true){lMbPucACbd = false;}
      if(HrppFTRjBX == true){HrppFTRjBX = false;}
      if(mWjUmDKZIm == true){mWjUmDKZIm = false;}
      if(MKolfthZmF == true){MKolfthZmF = false;}
      if(lyCrKhFgjF == true){lyCrKhFgjF = false;}
      if(eNWEPPcGbr == true){eNWEPPcGbr = false;}
      if(SatoRxDEKL == true){SatoRxDEKL = false;}
      if(lqxuknTrKE == true){lqxuknTrKE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAOUZZBYVM
{ 
  void ldDkimAxqG()
  { 
      bool iBDaNIAyjA = false;
      bool jobAaKdbex = false;
      bool hwdbqTFZkf = false;
      bool AFARtzRNpM = false;
      bool MFZezzwSLp = false;
      bool sssudmXajt = false;
      bool DZNEAdnJGb = false;
      bool sQlSkbVzcr = false;
      bool XlOtlGMFmH = false;
      bool apdwImrVdV = false;
      bool KlMixcHZJC = false;
      bool QXyqVRKSRs = false;
      bool RiWzACmpKx = false;
      bool jzUHhkYfxJ = false;
      bool zlukpDqlZq = false;
      bool cYEkDaPMht = false;
      bool oQPLRRDqJk = false;
      bool rdVHtenkJx = false;
      bool LBQSUKujDG = false;
      bool VLxDUhViSY = false;
      string kMHCSsduyT;
      string oaXEFCWMEj;
      string ePUDWPGKSe;
      string TYrmxnXIJP;
      string ZQWkJCPqOR;
      string fPfNzVqDfC;
      string lTbSAQikGQ;
      string eOCnJOsjtT;
      string APwBzEsdnb;
      string xTcHdGnDks;
      string TekxmRNqEj;
      string bGJMBWXaSu;
      string WEwdTKktKD;
      string ZozAzVeyOg;
      string qBZDzpKQGG;
      string hMjoVPhGdb;
      string fSfAKmGIMe;
      string rYMlEVesec;
      string AUnEUMEKej;
      string nXTlBXVYrM;
      if(kMHCSsduyT == TekxmRNqEj){iBDaNIAyjA = true;}
      else if(TekxmRNqEj == kMHCSsduyT){KlMixcHZJC = true;}
      if(oaXEFCWMEj == bGJMBWXaSu){jobAaKdbex = true;}
      else if(bGJMBWXaSu == oaXEFCWMEj){QXyqVRKSRs = true;}
      if(ePUDWPGKSe == WEwdTKktKD){hwdbqTFZkf = true;}
      else if(WEwdTKktKD == ePUDWPGKSe){RiWzACmpKx = true;}
      if(TYrmxnXIJP == ZozAzVeyOg){AFARtzRNpM = true;}
      else if(ZozAzVeyOg == TYrmxnXIJP){jzUHhkYfxJ = true;}
      if(ZQWkJCPqOR == qBZDzpKQGG){MFZezzwSLp = true;}
      else if(qBZDzpKQGG == ZQWkJCPqOR){zlukpDqlZq = true;}
      if(fPfNzVqDfC == hMjoVPhGdb){sssudmXajt = true;}
      else if(hMjoVPhGdb == fPfNzVqDfC){cYEkDaPMht = true;}
      if(lTbSAQikGQ == fSfAKmGIMe){DZNEAdnJGb = true;}
      else if(fSfAKmGIMe == lTbSAQikGQ){oQPLRRDqJk = true;}
      if(eOCnJOsjtT == rYMlEVesec){sQlSkbVzcr = true;}
      if(APwBzEsdnb == AUnEUMEKej){XlOtlGMFmH = true;}
      if(xTcHdGnDks == nXTlBXVYrM){apdwImrVdV = true;}
      while(rYMlEVesec == eOCnJOsjtT){rdVHtenkJx = true;}
      while(AUnEUMEKej == AUnEUMEKej){LBQSUKujDG = true;}
      while(nXTlBXVYrM == nXTlBXVYrM){VLxDUhViSY = true;}
      if(iBDaNIAyjA == true){iBDaNIAyjA = false;}
      if(jobAaKdbex == true){jobAaKdbex = false;}
      if(hwdbqTFZkf == true){hwdbqTFZkf = false;}
      if(AFARtzRNpM == true){AFARtzRNpM = false;}
      if(MFZezzwSLp == true){MFZezzwSLp = false;}
      if(sssudmXajt == true){sssudmXajt = false;}
      if(DZNEAdnJGb == true){DZNEAdnJGb = false;}
      if(sQlSkbVzcr == true){sQlSkbVzcr = false;}
      if(XlOtlGMFmH == true){XlOtlGMFmH = false;}
      if(apdwImrVdV == true){apdwImrVdV = false;}
      if(KlMixcHZJC == true){KlMixcHZJC = false;}
      if(QXyqVRKSRs == true){QXyqVRKSRs = false;}
      if(RiWzACmpKx == true){RiWzACmpKx = false;}
      if(jzUHhkYfxJ == true){jzUHhkYfxJ = false;}
      if(zlukpDqlZq == true){zlukpDqlZq = false;}
      if(cYEkDaPMht == true){cYEkDaPMht = false;}
      if(oQPLRRDqJk == true){oQPLRRDqJk = false;}
      if(rdVHtenkJx == true){rdVHtenkJx = false;}
      if(LBQSUKujDG == true){LBQSUKujDG = false;}
      if(VLxDUhViSY == true){VLxDUhViSY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYJUXJUMFL
{ 
  void htjuqVEatW()
  { 
      bool GPnzYYgxgZ = false;
      bool HCncDKfYlu = false;
      bool DLXsFQgkqx = false;
      bool jhIpQaVKUg = false;
      bool LGNgkrAEXP = false;
      bool McljuuqtsI = false;
      bool ruGjoYsxLc = false;
      bool nUEFjxyqHM = false;
      bool PcNbkHwXuV = false;
      bool jbRLoPzdqM = false;
      bool zCrtaqXfAx = false;
      bool xzlfrOgeyh = false;
      bool bUCprMDsPT = false;
      bool xTzuNNjSAs = false;
      bool iPXxYjokSZ = false;
      bool hUeIjeABCO = false;
      bool neQgAczqRe = false;
      bool dOeFyMxFRH = false;
      bool XRZplcopKi = false;
      bool NiQkFEzpxu = false;
      string EyCoNyttSg;
      string ruqdtDGFid;
      string dhNUEpmdJH;
      string bZTmCWZDJK;
      string ANmAjMEyJI;
      string HtOQrVkhkX;
      string KQjLFRaEaW;
      string cDuXdQuMjr;
      string lnTBzgLDug;
      string lrSlAjcbuR;
      string kzWleEzpla;
      string aXxslVwiMX;
      string GXItkkjJXs;
      string mTRRGlQhVt;
      string hUQTFNtZzd;
      string mtPWLNqcAt;
      string UpSrnHGelA;
      string EOMRplGonX;
      string pJJsGsDtGs;
      string tngaZrBXfy;
      if(EyCoNyttSg == kzWleEzpla){GPnzYYgxgZ = true;}
      else if(kzWleEzpla == EyCoNyttSg){zCrtaqXfAx = true;}
      if(ruqdtDGFid == aXxslVwiMX){HCncDKfYlu = true;}
      else if(aXxslVwiMX == ruqdtDGFid){xzlfrOgeyh = true;}
      if(dhNUEpmdJH == GXItkkjJXs){DLXsFQgkqx = true;}
      else if(GXItkkjJXs == dhNUEpmdJH){bUCprMDsPT = true;}
      if(bZTmCWZDJK == mTRRGlQhVt){jhIpQaVKUg = true;}
      else if(mTRRGlQhVt == bZTmCWZDJK){xTzuNNjSAs = true;}
      if(ANmAjMEyJI == hUQTFNtZzd){LGNgkrAEXP = true;}
      else if(hUQTFNtZzd == ANmAjMEyJI){iPXxYjokSZ = true;}
      if(HtOQrVkhkX == mtPWLNqcAt){McljuuqtsI = true;}
      else if(mtPWLNqcAt == HtOQrVkhkX){hUeIjeABCO = true;}
      if(KQjLFRaEaW == UpSrnHGelA){ruGjoYsxLc = true;}
      else if(UpSrnHGelA == KQjLFRaEaW){neQgAczqRe = true;}
      if(cDuXdQuMjr == EOMRplGonX){nUEFjxyqHM = true;}
      if(lnTBzgLDug == pJJsGsDtGs){PcNbkHwXuV = true;}
      if(lrSlAjcbuR == tngaZrBXfy){jbRLoPzdqM = true;}
      while(EOMRplGonX == cDuXdQuMjr){dOeFyMxFRH = true;}
      while(pJJsGsDtGs == pJJsGsDtGs){XRZplcopKi = true;}
      while(tngaZrBXfy == tngaZrBXfy){NiQkFEzpxu = true;}
      if(GPnzYYgxgZ == true){GPnzYYgxgZ = false;}
      if(HCncDKfYlu == true){HCncDKfYlu = false;}
      if(DLXsFQgkqx == true){DLXsFQgkqx = false;}
      if(jhIpQaVKUg == true){jhIpQaVKUg = false;}
      if(LGNgkrAEXP == true){LGNgkrAEXP = false;}
      if(McljuuqtsI == true){McljuuqtsI = false;}
      if(ruGjoYsxLc == true){ruGjoYsxLc = false;}
      if(nUEFjxyqHM == true){nUEFjxyqHM = false;}
      if(PcNbkHwXuV == true){PcNbkHwXuV = false;}
      if(jbRLoPzdqM == true){jbRLoPzdqM = false;}
      if(zCrtaqXfAx == true){zCrtaqXfAx = false;}
      if(xzlfrOgeyh == true){xzlfrOgeyh = false;}
      if(bUCprMDsPT == true){bUCprMDsPT = false;}
      if(xTzuNNjSAs == true){xTzuNNjSAs = false;}
      if(iPXxYjokSZ == true){iPXxYjokSZ = false;}
      if(hUeIjeABCO == true){hUeIjeABCO = false;}
      if(neQgAczqRe == true){neQgAczqRe = false;}
      if(dOeFyMxFRH == true){dOeFyMxFRH = false;}
      if(XRZplcopKi == true){XRZplcopKi = false;}
      if(NiQkFEzpxu == true){NiQkFEzpxu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPBNCXEMZR
{ 
  void qFOwYANrEh()
  { 
      bool CKLGEXIafe = false;
      bool EWqXFNYjJN = false;
      bool GDLhcnNSjo = false;
      bool eQAIStlqEY = false;
      bool wzrUbbIIyz = false;
      bool lXPKhyycdP = false;
      bool KpqpzmViFL = false;
      bool ahfkRGLqFB = false;
      bool fFTkDHApZT = false;
      bool uINnNFIBUn = false;
      bool GZDmXErdsb = false;
      bool mGXbjFVGmr = false;
      bool mfIkPRUqWM = false;
      bool yJWRtGBgNy = false;
      bool OVwygokkEI = false;
      bool jCObBZQSWF = false;
      bool jAGgdcjGhd = false;
      bool DnsndQiKDa = false;
      bool gimObwuuQT = false;
      bool oiJHOOOPUD = false;
      string tGiXbKPFHD;
      string FxVDammkZc;
      string MSEamqgaQd;
      string hRXGfNKAtA;
      string bHXjxrehGP;
      string VuTVJbBIjk;
      string condUnZPXM;
      string cmpYBEtTct;
      string LzUBHlxBxD;
      string MBPIWlTtOJ;
      string SPJtliEuUE;
      string ggepYdUmVh;
      string pXSUAaWhBO;
      string kzFSbwoZPY;
      string hCgrWeWZjs;
      string RfYgTuxosK;
      string LWsGSgbLNc;
      string ntXxAnqZxV;
      string ExyIwEaYzf;
      string zAfEMKIZYo;
      if(tGiXbKPFHD == SPJtliEuUE){CKLGEXIafe = true;}
      else if(SPJtliEuUE == tGiXbKPFHD){GZDmXErdsb = true;}
      if(FxVDammkZc == ggepYdUmVh){EWqXFNYjJN = true;}
      else if(ggepYdUmVh == FxVDammkZc){mGXbjFVGmr = true;}
      if(MSEamqgaQd == pXSUAaWhBO){GDLhcnNSjo = true;}
      else if(pXSUAaWhBO == MSEamqgaQd){mfIkPRUqWM = true;}
      if(hRXGfNKAtA == kzFSbwoZPY){eQAIStlqEY = true;}
      else if(kzFSbwoZPY == hRXGfNKAtA){yJWRtGBgNy = true;}
      if(bHXjxrehGP == hCgrWeWZjs){wzrUbbIIyz = true;}
      else if(hCgrWeWZjs == bHXjxrehGP){OVwygokkEI = true;}
      if(VuTVJbBIjk == RfYgTuxosK){lXPKhyycdP = true;}
      else if(RfYgTuxosK == VuTVJbBIjk){jCObBZQSWF = true;}
      if(condUnZPXM == LWsGSgbLNc){KpqpzmViFL = true;}
      else if(LWsGSgbLNc == condUnZPXM){jAGgdcjGhd = true;}
      if(cmpYBEtTct == ntXxAnqZxV){ahfkRGLqFB = true;}
      if(LzUBHlxBxD == ExyIwEaYzf){fFTkDHApZT = true;}
      if(MBPIWlTtOJ == zAfEMKIZYo){uINnNFIBUn = true;}
      while(ntXxAnqZxV == cmpYBEtTct){DnsndQiKDa = true;}
      while(ExyIwEaYzf == ExyIwEaYzf){gimObwuuQT = true;}
      while(zAfEMKIZYo == zAfEMKIZYo){oiJHOOOPUD = true;}
      if(CKLGEXIafe == true){CKLGEXIafe = false;}
      if(EWqXFNYjJN == true){EWqXFNYjJN = false;}
      if(GDLhcnNSjo == true){GDLhcnNSjo = false;}
      if(eQAIStlqEY == true){eQAIStlqEY = false;}
      if(wzrUbbIIyz == true){wzrUbbIIyz = false;}
      if(lXPKhyycdP == true){lXPKhyycdP = false;}
      if(KpqpzmViFL == true){KpqpzmViFL = false;}
      if(ahfkRGLqFB == true){ahfkRGLqFB = false;}
      if(fFTkDHApZT == true){fFTkDHApZT = false;}
      if(uINnNFIBUn == true){uINnNFIBUn = false;}
      if(GZDmXErdsb == true){GZDmXErdsb = false;}
      if(mGXbjFVGmr == true){mGXbjFVGmr = false;}
      if(mfIkPRUqWM == true){mfIkPRUqWM = false;}
      if(yJWRtGBgNy == true){yJWRtGBgNy = false;}
      if(OVwygokkEI == true){OVwygokkEI = false;}
      if(jCObBZQSWF == true){jCObBZQSWF = false;}
      if(jAGgdcjGhd == true){jAGgdcjGhd = false;}
      if(DnsndQiKDa == true){DnsndQiKDa = false;}
      if(gimObwuuQT == true){gimObwuuQT = false;}
      if(oiJHOOOPUD == true){oiJHOOOPUD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJKJFBHBXW
{ 
  void mdmCbeQbKt()
  { 
      bool zZTHqbagFj = false;
      bool ADSumQShjl = false;
      bool hkPKujaTZe = false;
      bool pceplXiErg = false;
      bool pAcuypJBxr = false;
      bool AHSdmOKJLG = false;
      bool BGHZsWXbJO = false;
      bool gOoCuhHTMF = false;
      bool aZWgdhJACX = false;
      bool NZrkfisDBa = false;
      bool RgrhLlSQiF = false;
      bool GpwFfajZuK = false;
      bool MXZkBGVDWL = false;
      bool oERlnshnVr = false;
      bool PsRwRWclFE = false;
      bool ySHqNsHGgF = false;
      bool POtXPBYKRm = false;
      bool swEDuTGcTd = false;
      bool cjyRMVxaXt = false;
      bool laHPbAzsfP = false;
      string TYxOzPDQRC;
      string hBLeBgwMnl;
      string RkcGiHLiMc;
      string QfUahVCxWb;
      string XMOmGrzaRj;
      string zdSSGiwqfq;
      string EUEnkCfjxe;
      string eyoMNFWoAq;
      string IjRbdmNCUy;
      string ZLRfXDHZCE;
      string LOclFAnGEA;
      string MGpnhTCbKx;
      string ndPyESgJnK;
      string xwmufsGeWc;
      string yHxTlSUcxE;
      string AfOEQgzehl;
      string TeRtDPTtIo;
      string MXEhzfguMl;
      string yDLjJRgiey;
      string sbxkITpDQV;
      if(TYxOzPDQRC == LOclFAnGEA){zZTHqbagFj = true;}
      else if(LOclFAnGEA == TYxOzPDQRC){RgrhLlSQiF = true;}
      if(hBLeBgwMnl == MGpnhTCbKx){ADSumQShjl = true;}
      else if(MGpnhTCbKx == hBLeBgwMnl){GpwFfajZuK = true;}
      if(RkcGiHLiMc == ndPyESgJnK){hkPKujaTZe = true;}
      else if(ndPyESgJnK == RkcGiHLiMc){MXZkBGVDWL = true;}
      if(QfUahVCxWb == xwmufsGeWc){pceplXiErg = true;}
      else if(xwmufsGeWc == QfUahVCxWb){oERlnshnVr = true;}
      if(XMOmGrzaRj == yHxTlSUcxE){pAcuypJBxr = true;}
      else if(yHxTlSUcxE == XMOmGrzaRj){PsRwRWclFE = true;}
      if(zdSSGiwqfq == AfOEQgzehl){AHSdmOKJLG = true;}
      else if(AfOEQgzehl == zdSSGiwqfq){ySHqNsHGgF = true;}
      if(EUEnkCfjxe == TeRtDPTtIo){BGHZsWXbJO = true;}
      else if(TeRtDPTtIo == EUEnkCfjxe){POtXPBYKRm = true;}
      if(eyoMNFWoAq == MXEhzfguMl){gOoCuhHTMF = true;}
      if(IjRbdmNCUy == yDLjJRgiey){aZWgdhJACX = true;}
      if(ZLRfXDHZCE == sbxkITpDQV){NZrkfisDBa = true;}
      while(MXEhzfguMl == eyoMNFWoAq){swEDuTGcTd = true;}
      while(yDLjJRgiey == yDLjJRgiey){cjyRMVxaXt = true;}
      while(sbxkITpDQV == sbxkITpDQV){laHPbAzsfP = true;}
      if(zZTHqbagFj == true){zZTHqbagFj = false;}
      if(ADSumQShjl == true){ADSumQShjl = false;}
      if(hkPKujaTZe == true){hkPKujaTZe = false;}
      if(pceplXiErg == true){pceplXiErg = false;}
      if(pAcuypJBxr == true){pAcuypJBxr = false;}
      if(AHSdmOKJLG == true){AHSdmOKJLG = false;}
      if(BGHZsWXbJO == true){BGHZsWXbJO = false;}
      if(gOoCuhHTMF == true){gOoCuhHTMF = false;}
      if(aZWgdhJACX == true){aZWgdhJACX = false;}
      if(NZrkfisDBa == true){NZrkfisDBa = false;}
      if(RgrhLlSQiF == true){RgrhLlSQiF = false;}
      if(GpwFfajZuK == true){GpwFfajZuK = false;}
      if(MXZkBGVDWL == true){MXZkBGVDWL = false;}
      if(oERlnshnVr == true){oERlnshnVr = false;}
      if(PsRwRWclFE == true){PsRwRWclFE = false;}
      if(ySHqNsHGgF == true){ySHqNsHGgF = false;}
      if(POtXPBYKRm == true){POtXPBYKRm = false;}
      if(swEDuTGcTd == true){swEDuTGcTd = false;}
      if(cjyRMVxaXt == true){cjyRMVxaXt = false;}
      if(laHPbAzsfP == true){laHPbAzsfP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFUFUBVDPX
{ 
  void wYBUNCbwnz()
  { 
      bool BoyWjMpLDZ = false;
      bool xLpagOgLSP = false;
      bool JQynKtJVoQ = false;
      bool ZGALuHdNoi = false;
      bool dgoMLVRYAs = false;
      bool XHYUdjqKLp = false;
      bool DUWlzqKefY = false;
      bool jSVikcakbo = false;
      bool bkUusShegK = false;
      bool QTCzfIKDMU = false;
      bool KmraJElojB = false;
      bool JGhVORzbsg = false;
      bool IexVIQQWDb = false;
      bool RWXHenrtln = false;
      bool grufAKkfjN = false;
      bool IhKeLfpWSs = false;
      bool nOlHilhZqZ = false;
      bool ZFpEAQiRUx = false;
      bool ekloTjMswy = false;
      bool yVbrARGnwO = false;
      string stVJQrJjQU;
      string ObOGsddYbD;
      string FchCAMIaHD;
      string nIknPymHoY;
      string jjTyZseZYs;
      string mACyUPLTJD;
      string ihbNfFqaqt;
      string pWjCSVJjbH;
      string hhCNQmFlTz;
      string mSykoBHGRT;
      string BDieCQQAfy;
      string GbrCVBfOxr;
      string AFGrHXYzNQ;
      string NCRHFdzWLA;
      string WFGUrKZuOm;
      string VsJYTwxpXd;
      string qRlOjDJkwr;
      string CICxVtykAw;
      string xcjZuUsrmI;
      string gIzgIETrkn;
      if(stVJQrJjQU == BDieCQQAfy){BoyWjMpLDZ = true;}
      else if(BDieCQQAfy == stVJQrJjQU){KmraJElojB = true;}
      if(ObOGsddYbD == GbrCVBfOxr){xLpagOgLSP = true;}
      else if(GbrCVBfOxr == ObOGsddYbD){JGhVORzbsg = true;}
      if(FchCAMIaHD == AFGrHXYzNQ){JQynKtJVoQ = true;}
      else if(AFGrHXYzNQ == FchCAMIaHD){IexVIQQWDb = true;}
      if(nIknPymHoY == NCRHFdzWLA){ZGALuHdNoi = true;}
      else if(NCRHFdzWLA == nIknPymHoY){RWXHenrtln = true;}
      if(jjTyZseZYs == WFGUrKZuOm){dgoMLVRYAs = true;}
      else if(WFGUrKZuOm == jjTyZseZYs){grufAKkfjN = true;}
      if(mACyUPLTJD == VsJYTwxpXd){XHYUdjqKLp = true;}
      else if(VsJYTwxpXd == mACyUPLTJD){IhKeLfpWSs = true;}
      if(ihbNfFqaqt == qRlOjDJkwr){DUWlzqKefY = true;}
      else if(qRlOjDJkwr == ihbNfFqaqt){nOlHilhZqZ = true;}
      if(pWjCSVJjbH == CICxVtykAw){jSVikcakbo = true;}
      if(hhCNQmFlTz == xcjZuUsrmI){bkUusShegK = true;}
      if(mSykoBHGRT == gIzgIETrkn){QTCzfIKDMU = true;}
      while(CICxVtykAw == pWjCSVJjbH){ZFpEAQiRUx = true;}
      while(xcjZuUsrmI == xcjZuUsrmI){ekloTjMswy = true;}
      while(gIzgIETrkn == gIzgIETrkn){yVbrARGnwO = true;}
      if(BoyWjMpLDZ == true){BoyWjMpLDZ = false;}
      if(xLpagOgLSP == true){xLpagOgLSP = false;}
      if(JQynKtJVoQ == true){JQynKtJVoQ = false;}
      if(ZGALuHdNoi == true){ZGALuHdNoi = false;}
      if(dgoMLVRYAs == true){dgoMLVRYAs = false;}
      if(XHYUdjqKLp == true){XHYUdjqKLp = false;}
      if(DUWlzqKefY == true){DUWlzqKefY = false;}
      if(jSVikcakbo == true){jSVikcakbo = false;}
      if(bkUusShegK == true){bkUusShegK = false;}
      if(QTCzfIKDMU == true){QTCzfIKDMU = false;}
      if(KmraJElojB == true){KmraJElojB = false;}
      if(JGhVORzbsg == true){JGhVORzbsg = false;}
      if(IexVIQQWDb == true){IexVIQQWDb = false;}
      if(RWXHenrtln == true){RWXHenrtln = false;}
      if(grufAKkfjN == true){grufAKkfjN = false;}
      if(IhKeLfpWSs == true){IhKeLfpWSs = false;}
      if(nOlHilhZqZ == true){nOlHilhZqZ = false;}
      if(ZFpEAQiRUx == true){ZFpEAQiRUx = false;}
      if(ekloTjMswy == true){ekloTjMswy = false;}
      if(yVbrARGnwO == true){yVbrARGnwO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDTTIYTJQA
{ 
  void sEcnxXqqXB()
  { 
      bool DPZusmXrAm = false;
      bool rOokWQaWVf = false;
      bool OoQhCPOArb = false;
      bool cTnwlHKIZI = false;
      bool NYNOzGxqDS = false;
      bool fIYdXOyqrd = false;
      bool XXzXKYasyO = false;
      bool FSxNRpaBhu = false;
      bool SXxZuTtJXX = false;
      bool JSPukpYoEa = false;
      bool eErnNMKLLh = false;
      bool mxJwLzaZcp = false;
      bool dRUZFlDBcb = false;
      bool QlxGQOeIMi = false;
      bool JixpkLJSjk = false;
      bool PzMNwNiSha = false;
      bool JIijRBzCfx = false;
      bool URNtguTeot = false;
      bool ckRqLQYiJC = false;
      bool eMakYAzMXj = false;
      string gdnSpuUyJC;
      string HfRNUtAEao;
      string urWAFMyBeW;
      string qCwNZPmnEE;
      string qOVRdTqNbH;
      string yBbqinGnMc;
      string wSTlLEiEmE;
      string GLzWyfVEWk;
      string VkYWXoaFdk;
      string IzabHXuiGY;
      string kmZWBlCFrC;
      string SBQaHLswOV;
      string dcZCwGkXOZ;
      string klyxAiKCVk;
      string lVNbSGiATu;
      string dyUjuHMXZu;
      string BepRRfDSZY;
      string BqaciHPxio;
      string XkDSulQOCr;
      string VlbajHeuJm;
      if(gdnSpuUyJC == kmZWBlCFrC){DPZusmXrAm = true;}
      else if(kmZWBlCFrC == gdnSpuUyJC){eErnNMKLLh = true;}
      if(HfRNUtAEao == SBQaHLswOV){rOokWQaWVf = true;}
      else if(SBQaHLswOV == HfRNUtAEao){mxJwLzaZcp = true;}
      if(urWAFMyBeW == dcZCwGkXOZ){OoQhCPOArb = true;}
      else if(dcZCwGkXOZ == urWAFMyBeW){dRUZFlDBcb = true;}
      if(qCwNZPmnEE == klyxAiKCVk){cTnwlHKIZI = true;}
      else if(klyxAiKCVk == qCwNZPmnEE){QlxGQOeIMi = true;}
      if(qOVRdTqNbH == lVNbSGiATu){NYNOzGxqDS = true;}
      else if(lVNbSGiATu == qOVRdTqNbH){JixpkLJSjk = true;}
      if(yBbqinGnMc == dyUjuHMXZu){fIYdXOyqrd = true;}
      else if(dyUjuHMXZu == yBbqinGnMc){PzMNwNiSha = true;}
      if(wSTlLEiEmE == BepRRfDSZY){XXzXKYasyO = true;}
      else if(BepRRfDSZY == wSTlLEiEmE){JIijRBzCfx = true;}
      if(GLzWyfVEWk == BqaciHPxio){FSxNRpaBhu = true;}
      if(VkYWXoaFdk == XkDSulQOCr){SXxZuTtJXX = true;}
      if(IzabHXuiGY == VlbajHeuJm){JSPukpYoEa = true;}
      while(BqaciHPxio == GLzWyfVEWk){URNtguTeot = true;}
      while(XkDSulQOCr == XkDSulQOCr){ckRqLQYiJC = true;}
      while(VlbajHeuJm == VlbajHeuJm){eMakYAzMXj = true;}
      if(DPZusmXrAm == true){DPZusmXrAm = false;}
      if(rOokWQaWVf == true){rOokWQaWVf = false;}
      if(OoQhCPOArb == true){OoQhCPOArb = false;}
      if(cTnwlHKIZI == true){cTnwlHKIZI = false;}
      if(NYNOzGxqDS == true){NYNOzGxqDS = false;}
      if(fIYdXOyqrd == true){fIYdXOyqrd = false;}
      if(XXzXKYasyO == true){XXzXKYasyO = false;}
      if(FSxNRpaBhu == true){FSxNRpaBhu = false;}
      if(SXxZuTtJXX == true){SXxZuTtJXX = false;}
      if(JSPukpYoEa == true){JSPukpYoEa = false;}
      if(eErnNMKLLh == true){eErnNMKLLh = false;}
      if(mxJwLzaZcp == true){mxJwLzaZcp = false;}
      if(dRUZFlDBcb == true){dRUZFlDBcb = false;}
      if(QlxGQOeIMi == true){QlxGQOeIMi = false;}
      if(JixpkLJSjk == true){JixpkLJSjk = false;}
      if(PzMNwNiSha == true){PzMNwNiSha = false;}
      if(JIijRBzCfx == true){JIijRBzCfx = false;}
      if(URNtguTeot == true){URNtguTeot = false;}
      if(ckRqLQYiJC == true){ckRqLQYiJC = false;}
      if(eMakYAzMXj == true){eMakYAzMXj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGRLFNYJVE
{ 
  void cHEbwPYETN()
  { 
      bool EPpYmKcYWK = false;
      bool eRwAfUxXXk = false;
      bool dgkHitgkuD = false;
      bool lCUaaeeTng = false;
      bool CoSYqQKbBu = false;
      bool iBmxcXeios = false;
      bool crdSYbxUYB = false;
      bool pcjphoNLQS = false;
      bool iFizUjPXyD = false;
      bool zweuEKLAAO = false;
      bool ToCAFFRxOm = false;
      bool JTSWJXJdyn = false;
      bool MZVVBsyolX = false;
      bool dNLBytChtP = false;
      bool SRIKsedHkf = false;
      bool BgBLCtSgyL = false;
      bool GcKpJwHQXO = false;
      bool UaiiUtQLbW = false;
      bool PqDGWwLAyE = false;
      bool aVihIpHSBx = false;
      string JGcJDSDBcY;
      string JQlMbqDLwx;
      string KOcoUCinMV;
      string UmZmmYzBOI;
      string AMKSbYYlqx;
      string hWBXsudmoA;
      string iOoGEVqyYC;
      string qBxmxyDKMw;
      string dxxOnxlBtq;
      string uLMNYkWDNG;
      string hZMnGfZNat;
      string rSarWkRaSH;
      string joEhHfojOL;
      string bzwGOEkIIH;
      string WYaAzbkTqm;
      string TukGVrVefa;
      string qpzPRrWUdR;
      string AJSLjLNDhf;
      string tVrarfOojV;
      string iGbhQfYKiG;
      if(JGcJDSDBcY == hZMnGfZNat){EPpYmKcYWK = true;}
      else if(hZMnGfZNat == JGcJDSDBcY){ToCAFFRxOm = true;}
      if(JQlMbqDLwx == rSarWkRaSH){eRwAfUxXXk = true;}
      else if(rSarWkRaSH == JQlMbqDLwx){JTSWJXJdyn = true;}
      if(KOcoUCinMV == joEhHfojOL){dgkHitgkuD = true;}
      else if(joEhHfojOL == KOcoUCinMV){MZVVBsyolX = true;}
      if(UmZmmYzBOI == bzwGOEkIIH){lCUaaeeTng = true;}
      else if(bzwGOEkIIH == UmZmmYzBOI){dNLBytChtP = true;}
      if(AMKSbYYlqx == WYaAzbkTqm){CoSYqQKbBu = true;}
      else if(WYaAzbkTqm == AMKSbYYlqx){SRIKsedHkf = true;}
      if(hWBXsudmoA == TukGVrVefa){iBmxcXeios = true;}
      else if(TukGVrVefa == hWBXsudmoA){BgBLCtSgyL = true;}
      if(iOoGEVqyYC == qpzPRrWUdR){crdSYbxUYB = true;}
      else if(qpzPRrWUdR == iOoGEVqyYC){GcKpJwHQXO = true;}
      if(qBxmxyDKMw == AJSLjLNDhf){pcjphoNLQS = true;}
      if(dxxOnxlBtq == tVrarfOojV){iFizUjPXyD = true;}
      if(uLMNYkWDNG == iGbhQfYKiG){zweuEKLAAO = true;}
      while(AJSLjLNDhf == qBxmxyDKMw){UaiiUtQLbW = true;}
      while(tVrarfOojV == tVrarfOojV){PqDGWwLAyE = true;}
      while(iGbhQfYKiG == iGbhQfYKiG){aVihIpHSBx = true;}
      if(EPpYmKcYWK == true){EPpYmKcYWK = false;}
      if(eRwAfUxXXk == true){eRwAfUxXXk = false;}
      if(dgkHitgkuD == true){dgkHitgkuD = false;}
      if(lCUaaeeTng == true){lCUaaeeTng = false;}
      if(CoSYqQKbBu == true){CoSYqQKbBu = false;}
      if(iBmxcXeios == true){iBmxcXeios = false;}
      if(crdSYbxUYB == true){crdSYbxUYB = false;}
      if(pcjphoNLQS == true){pcjphoNLQS = false;}
      if(iFizUjPXyD == true){iFizUjPXyD = false;}
      if(zweuEKLAAO == true){zweuEKLAAO = false;}
      if(ToCAFFRxOm == true){ToCAFFRxOm = false;}
      if(JTSWJXJdyn == true){JTSWJXJdyn = false;}
      if(MZVVBsyolX == true){MZVVBsyolX = false;}
      if(dNLBytChtP == true){dNLBytChtP = false;}
      if(SRIKsedHkf == true){SRIKsedHkf = false;}
      if(BgBLCtSgyL == true){BgBLCtSgyL = false;}
      if(GcKpJwHQXO == true){GcKpJwHQXO = false;}
      if(UaiiUtQLbW == true){UaiiUtQLbW = false;}
      if(PqDGWwLAyE == true){PqDGWwLAyE = false;}
      if(aVihIpHSBx == true){aVihIpHSBx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHHDGKXTVK
{ 
  void ihOORybYNM()
  { 
      bool ygOTxMcUjI = false;
      bool FXhdGqExsm = false;
      bool AkpXHArZPA = false;
      bool sPycAzpCaT = false;
      bool zWpbQZuAnB = false;
      bool NyYzoMqpMx = false;
      bool UCFiPoZEcH = false;
      bool ACVYmctNHh = false;
      bool EqlNltpymn = false;
      bool IAodzxQHMa = false;
      bool ApXgALbzML = false;
      bool RcidrcQqxU = false;
      bool yaRoyAMrYo = false;
      bool MmAfhNTFNZ = false;
      bool SplaVeRLkW = false;
      bool gZJrbYYhhA = false;
      bool ziaWzdbCud = false;
      bool JKdWBHopTS = false;
      bool iAHCImcIDJ = false;
      bool okXMaiPOaq = false;
      string TPjNfKIPir;
      string fPnrnbLVCQ;
      string tOikoWYlzl;
      string QnGKyfSjqU;
      string kRVqwUXtsm;
      string lACWSFgzXI;
      string lWQwbrIdsH;
      string JadgfbsrnU;
      string yerMAPlirs;
      string zTMihOBYOE;
      string LtAkcLVUqp;
      string LoKDJHdDwM;
      string GYlAIoOuzQ;
      string aTciIEdHio;
      string sQrBgJIJYa;
      string jxbCylHAbn;
      string waVZPqLbtE;
      string dWUHSogjSy;
      string gFVXgcqZkV;
      string xceurSuRlo;
      if(TPjNfKIPir == LtAkcLVUqp){ygOTxMcUjI = true;}
      else if(LtAkcLVUqp == TPjNfKIPir){ApXgALbzML = true;}
      if(fPnrnbLVCQ == LoKDJHdDwM){FXhdGqExsm = true;}
      else if(LoKDJHdDwM == fPnrnbLVCQ){RcidrcQqxU = true;}
      if(tOikoWYlzl == GYlAIoOuzQ){AkpXHArZPA = true;}
      else if(GYlAIoOuzQ == tOikoWYlzl){yaRoyAMrYo = true;}
      if(QnGKyfSjqU == aTciIEdHio){sPycAzpCaT = true;}
      else if(aTciIEdHio == QnGKyfSjqU){MmAfhNTFNZ = true;}
      if(kRVqwUXtsm == sQrBgJIJYa){zWpbQZuAnB = true;}
      else if(sQrBgJIJYa == kRVqwUXtsm){SplaVeRLkW = true;}
      if(lACWSFgzXI == jxbCylHAbn){NyYzoMqpMx = true;}
      else if(jxbCylHAbn == lACWSFgzXI){gZJrbYYhhA = true;}
      if(lWQwbrIdsH == waVZPqLbtE){UCFiPoZEcH = true;}
      else if(waVZPqLbtE == lWQwbrIdsH){ziaWzdbCud = true;}
      if(JadgfbsrnU == dWUHSogjSy){ACVYmctNHh = true;}
      if(yerMAPlirs == gFVXgcqZkV){EqlNltpymn = true;}
      if(zTMihOBYOE == xceurSuRlo){IAodzxQHMa = true;}
      while(dWUHSogjSy == JadgfbsrnU){JKdWBHopTS = true;}
      while(gFVXgcqZkV == gFVXgcqZkV){iAHCImcIDJ = true;}
      while(xceurSuRlo == xceurSuRlo){okXMaiPOaq = true;}
      if(ygOTxMcUjI == true){ygOTxMcUjI = false;}
      if(FXhdGqExsm == true){FXhdGqExsm = false;}
      if(AkpXHArZPA == true){AkpXHArZPA = false;}
      if(sPycAzpCaT == true){sPycAzpCaT = false;}
      if(zWpbQZuAnB == true){zWpbQZuAnB = false;}
      if(NyYzoMqpMx == true){NyYzoMqpMx = false;}
      if(UCFiPoZEcH == true){UCFiPoZEcH = false;}
      if(ACVYmctNHh == true){ACVYmctNHh = false;}
      if(EqlNltpymn == true){EqlNltpymn = false;}
      if(IAodzxQHMa == true){IAodzxQHMa = false;}
      if(ApXgALbzML == true){ApXgALbzML = false;}
      if(RcidrcQqxU == true){RcidrcQqxU = false;}
      if(yaRoyAMrYo == true){yaRoyAMrYo = false;}
      if(MmAfhNTFNZ == true){MmAfhNTFNZ = false;}
      if(SplaVeRLkW == true){SplaVeRLkW = false;}
      if(gZJrbYYhhA == true){gZJrbYYhhA = false;}
      if(ziaWzdbCud == true){ziaWzdbCud = false;}
      if(JKdWBHopTS == true){JKdWBHopTS = false;}
      if(iAHCImcIDJ == true){iAHCImcIDJ = false;}
      if(okXMaiPOaq == true){okXMaiPOaq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SBWAKQMUMD
{ 
  void TqTHTKqwNb()
  { 
      bool ixonVYfpjD = false;
      bool AqMrrxTjhf = false;
      bool MZpjMEqhSL = false;
      bool lithqMCfps = false;
      bool omjyAkhmyl = false;
      bool LuJZsIHFaR = false;
      bool hyWYQQweBf = false;
      bool umsnpYprib = false;
      bool VEjfzqZTni = false;
      bool FwEYLqPLgj = false;
      bool nDlRqXBUjU = false;
      bool ROVzudNpYY = false;
      bool qbpRZyiTcz = false;
      bool IeKzmSRRob = false;
      bool pEjTQpaEdg = false;
      bool cZlIrLMUrr = false;
      bool ogrjLmEWMc = false;
      bool LuAxilrVAj = false;
      bool XdpuVirCGb = false;
      bool FxZxmIMAId = false;
      string UIyOIdMSpl;
      string ecKAVKSHlr;
      string jRhyjYEUEk;
      string XfEOKwFQWo;
      string KkZzMQzZxI;
      string HUaxbCZAej;
      string YrNFNyYwpZ;
      string FBjxgyqhkS;
      string YeWwdDFHlH;
      string VEkmPSWUlO;
      string rDiXDFjdPc;
      string LqOLKtVRbK;
      string sRJiEAQwgO;
      string aVwWaVuzsY;
      string SaqIudpZcU;
      string wFsbUZsASC;
      string nmwACourjo;
      string zWYDqRZBnZ;
      string KqTMSVcUBA;
      string ctfpjeeqGF;
      if(UIyOIdMSpl == rDiXDFjdPc){ixonVYfpjD = true;}
      else if(rDiXDFjdPc == UIyOIdMSpl){nDlRqXBUjU = true;}
      if(ecKAVKSHlr == LqOLKtVRbK){AqMrrxTjhf = true;}
      else if(LqOLKtVRbK == ecKAVKSHlr){ROVzudNpYY = true;}
      if(jRhyjYEUEk == sRJiEAQwgO){MZpjMEqhSL = true;}
      else if(sRJiEAQwgO == jRhyjYEUEk){qbpRZyiTcz = true;}
      if(XfEOKwFQWo == aVwWaVuzsY){lithqMCfps = true;}
      else if(aVwWaVuzsY == XfEOKwFQWo){IeKzmSRRob = true;}
      if(KkZzMQzZxI == SaqIudpZcU){omjyAkhmyl = true;}
      else if(SaqIudpZcU == KkZzMQzZxI){pEjTQpaEdg = true;}
      if(HUaxbCZAej == wFsbUZsASC){LuJZsIHFaR = true;}
      else if(wFsbUZsASC == HUaxbCZAej){cZlIrLMUrr = true;}
      if(YrNFNyYwpZ == nmwACourjo){hyWYQQweBf = true;}
      else if(nmwACourjo == YrNFNyYwpZ){ogrjLmEWMc = true;}
      if(FBjxgyqhkS == zWYDqRZBnZ){umsnpYprib = true;}
      if(YeWwdDFHlH == KqTMSVcUBA){VEjfzqZTni = true;}
      if(VEkmPSWUlO == ctfpjeeqGF){FwEYLqPLgj = true;}
      while(zWYDqRZBnZ == FBjxgyqhkS){LuAxilrVAj = true;}
      while(KqTMSVcUBA == KqTMSVcUBA){XdpuVirCGb = true;}
      while(ctfpjeeqGF == ctfpjeeqGF){FxZxmIMAId = true;}
      if(ixonVYfpjD == true){ixonVYfpjD = false;}
      if(AqMrrxTjhf == true){AqMrrxTjhf = false;}
      if(MZpjMEqhSL == true){MZpjMEqhSL = false;}
      if(lithqMCfps == true){lithqMCfps = false;}
      if(omjyAkhmyl == true){omjyAkhmyl = false;}
      if(LuJZsIHFaR == true){LuJZsIHFaR = false;}
      if(hyWYQQweBf == true){hyWYQQweBf = false;}
      if(umsnpYprib == true){umsnpYprib = false;}
      if(VEjfzqZTni == true){VEjfzqZTni = false;}
      if(FwEYLqPLgj == true){FwEYLqPLgj = false;}
      if(nDlRqXBUjU == true){nDlRqXBUjU = false;}
      if(ROVzudNpYY == true){ROVzudNpYY = false;}
      if(qbpRZyiTcz == true){qbpRZyiTcz = false;}
      if(IeKzmSRRob == true){IeKzmSRRob = false;}
      if(pEjTQpaEdg == true){pEjTQpaEdg = false;}
      if(cZlIrLMUrr == true){cZlIrLMUrr = false;}
      if(ogrjLmEWMc == true){ogrjLmEWMc = false;}
      if(LuAxilrVAj == true){LuAxilrVAj = false;}
      if(XdpuVirCGb == true){XdpuVirCGb = false;}
      if(FxZxmIMAId == true){FxZxmIMAId = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSKABRGZBJ
{ 
  void LAoZEGEHSW()
  { 
      bool hNAYxJYXuJ = false;
      bool nxBfdQTkYj = false;
      bool hDsrFNQVhV = false;
      bool iiAPVkRRxQ = false;
      bool SjnYjMeKIY = false;
      bool uiCHPdUITj = false;
      bool sCpZaFwlKr = false;
      bool yCnIQyPTHr = false;
      bool hFMIaAfszq = false;
      bool PJyMWQtOye = false;
      bool QrAQZrttpR = false;
      bool OBAbBmogyZ = false;
      bool YDmTcoEakz = false;
      bool DBUcapFwhh = false;
      bool FlChcOIVLj = false;
      bool aMPXGMFfmk = false;
      bool nTIqNNfXAL = false;
      bool grzPUmBFqN = false;
      bool ghPBXqkxVO = false;
      bool jYJwtlcLTP = false;
      string blrCkhFNwN;
      string hGgQfJxtPK;
      string siaECZYnGE;
      string lJBCcjDGNs;
      string SNkSpqcHEX;
      string KWpihrLnAL;
      string IRGqaXFdmw;
      string FqgWrfxHOK;
      string xQihsPTRUj;
      string XPGCjAGtqR;
      string lyTHSToSpB;
      string tDYoNqiYyK;
      string EmJDXpjemq;
      string ZDPwXyxaPZ;
      string ZAaSoUpRnr;
      string RhwgNznPjc;
      string iKfzbpmbQP;
      string tHIXkDLqND;
      string zSptZrHiiY;
      string KgqlpOUbqy;
      if(blrCkhFNwN == lyTHSToSpB){hNAYxJYXuJ = true;}
      else if(lyTHSToSpB == blrCkhFNwN){QrAQZrttpR = true;}
      if(hGgQfJxtPK == tDYoNqiYyK){nxBfdQTkYj = true;}
      else if(tDYoNqiYyK == hGgQfJxtPK){OBAbBmogyZ = true;}
      if(siaECZYnGE == EmJDXpjemq){hDsrFNQVhV = true;}
      else if(EmJDXpjemq == siaECZYnGE){YDmTcoEakz = true;}
      if(lJBCcjDGNs == ZDPwXyxaPZ){iiAPVkRRxQ = true;}
      else if(ZDPwXyxaPZ == lJBCcjDGNs){DBUcapFwhh = true;}
      if(SNkSpqcHEX == ZAaSoUpRnr){SjnYjMeKIY = true;}
      else if(ZAaSoUpRnr == SNkSpqcHEX){FlChcOIVLj = true;}
      if(KWpihrLnAL == RhwgNznPjc){uiCHPdUITj = true;}
      else if(RhwgNznPjc == KWpihrLnAL){aMPXGMFfmk = true;}
      if(IRGqaXFdmw == iKfzbpmbQP){sCpZaFwlKr = true;}
      else if(iKfzbpmbQP == IRGqaXFdmw){nTIqNNfXAL = true;}
      if(FqgWrfxHOK == tHIXkDLqND){yCnIQyPTHr = true;}
      if(xQihsPTRUj == zSptZrHiiY){hFMIaAfszq = true;}
      if(XPGCjAGtqR == KgqlpOUbqy){PJyMWQtOye = true;}
      while(tHIXkDLqND == FqgWrfxHOK){grzPUmBFqN = true;}
      while(zSptZrHiiY == zSptZrHiiY){ghPBXqkxVO = true;}
      while(KgqlpOUbqy == KgqlpOUbqy){jYJwtlcLTP = true;}
      if(hNAYxJYXuJ == true){hNAYxJYXuJ = false;}
      if(nxBfdQTkYj == true){nxBfdQTkYj = false;}
      if(hDsrFNQVhV == true){hDsrFNQVhV = false;}
      if(iiAPVkRRxQ == true){iiAPVkRRxQ = false;}
      if(SjnYjMeKIY == true){SjnYjMeKIY = false;}
      if(uiCHPdUITj == true){uiCHPdUITj = false;}
      if(sCpZaFwlKr == true){sCpZaFwlKr = false;}
      if(yCnIQyPTHr == true){yCnIQyPTHr = false;}
      if(hFMIaAfszq == true){hFMIaAfszq = false;}
      if(PJyMWQtOye == true){PJyMWQtOye = false;}
      if(QrAQZrttpR == true){QrAQZrttpR = false;}
      if(OBAbBmogyZ == true){OBAbBmogyZ = false;}
      if(YDmTcoEakz == true){YDmTcoEakz = false;}
      if(DBUcapFwhh == true){DBUcapFwhh = false;}
      if(FlChcOIVLj == true){FlChcOIVLj = false;}
      if(aMPXGMFfmk == true){aMPXGMFfmk = false;}
      if(nTIqNNfXAL == true){nTIqNNfXAL = false;}
      if(grzPUmBFqN == true){grzPUmBFqN = false;}
      if(ghPBXqkxVO == true){ghPBXqkxVO = false;}
      if(jYJwtlcLTP == true){jYJwtlcLTP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESTFDZOWME
{ 
  void FdMWRpqhDa()
  { 
      bool mOihFKXuDH = false;
      bool mkNGnzqnsZ = false;
      bool VCLzMSUMxH = false;
      bool oNsujYDhpr = false;
      bool OPaoVPxliI = false;
      bool GthFBkCjVl = false;
      bool pLxuSYrSVP = false;
      bool wJyAKGaWcw = false;
      bool UhdnAufmsz = false;
      bool VSMDCDReWx = false;
      bool XePTMxuhtu = false;
      bool JfGYRHgItX = false;
      bool sFZWscxuxG = false;
      bool nwzfYpSKbD = false;
      bool zxryppLmlu = false;
      bool WIjyDSEsZi = false;
      bool AAjmGMfaza = false;
      bool nWfqYuMagD = false;
      bool RJIBjeMBcG = false;
      bool kZjsDyNErd = false;
      string dAfIMfJaFX;
      string KQcQrVcYMP;
      string HYWsiuOjBs;
      string hkEEzQxLoY;
      string fRMMtEDTuM;
      string hFDHzEdlYR;
      string RYYLoYMYRb;
      string XRjmioMKze;
      string qtonLchxEu;
      string lLlWHHsBWV;
      string reCSoQVPXK;
      string qTmtZWijAM;
      string pOTVoMeMfa;
      string wLmclMrVzt;
      string GSYtDSYrwj;
      string XIAJecKfcb;
      string lIjwNffJIN;
      string eNjFGXpZRW;
      string nmQuDmKdxI;
      string BLrXIyhbfW;
      if(dAfIMfJaFX == reCSoQVPXK){mOihFKXuDH = true;}
      else if(reCSoQVPXK == dAfIMfJaFX){XePTMxuhtu = true;}
      if(KQcQrVcYMP == qTmtZWijAM){mkNGnzqnsZ = true;}
      else if(qTmtZWijAM == KQcQrVcYMP){JfGYRHgItX = true;}
      if(HYWsiuOjBs == pOTVoMeMfa){VCLzMSUMxH = true;}
      else if(pOTVoMeMfa == HYWsiuOjBs){sFZWscxuxG = true;}
      if(hkEEzQxLoY == wLmclMrVzt){oNsujYDhpr = true;}
      else if(wLmclMrVzt == hkEEzQxLoY){nwzfYpSKbD = true;}
      if(fRMMtEDTuM == GSYtDSYrwj){OPaoVPxliI = true;}
      else if(GSYtDSYrwj == fRMMtEDTuM){zxryppLmlu = true;}
      if(hFDHzEdlYR == XIAJecKfcb){GthFBkCjVl = true;}
      else if(XIAJecKfcb == hFDHzEdlYR){WIjyDSEsZi = true;}
      if(RYYLoYMYRb == lIjwNffJIN){pLxuSYrSVP = true;}
      else if(lIjwNffJIN == RYYLoYMYRb){AAjmGMfaza = true;}
      if(XRjmioMKze == eNjFGXpZRW){wJyAKGaWcw = true;}
      if(qtonLchxEu == nmQuDmKdxI){UhdnAufmsz = true;}
      if(lLlWHHsBWV == BLrXIyhbfW){VSMDCDReWx = true;}
      while(eNjFGXpZRW == XRjmioMKze){nWfqYuMagD = true;}
      while(nmQuDmKdxI == nmQuDmKdxI){RJIBjeMBcG = true;}
      while(BLrXIyhbfW == BLrXIyhbfW){kZjsDyNErd = true;}
      if(mOihFKXuDH == true){mOihFKXuDH = false;}
      if(mkNGnzqnsZ == true){mkNGnzqnsZ = false;}
      if(VCLzMSUMxH == true){VCLzMSUMxH = false;}
      if(oNsujYDhpr == true){oNsujYDhpr = false;}
      if(OPaoVPxliI == true){OPaoVPxliI = false;}
      if(GthFBkCjVl == true){GthFBkCjVl = false;}
      if(pLxuSYrSVP == true){pLxuSYrSVP = false;}
      if(wJyAKGaWcw == true){wJyAKGaWcw = false;}
      if(UhdnAufmsz == true){UhdnAufmsz = false;}
      if(VSMDCDReWx == true){VSMDCDReWx = false;}
      if(XePTMxuhtu == true){XePTMxuhtu = false;}
      if(JfGYRHgItX == true){JfGYRHgItX = false;}
      if(sFZWscxuxG == true){sFZWscxuxG = false;}
      if(nwzfYpSKbD == true){nwzfYpSKbD = false;}
      if(zxryppLmlu == true){zxryppLmlu = false;}
      if(WIjyDSEsZi == true){WIjyDSEsZi = false;}
      if(AAjmGMfaza == true){AAjmGMfaza = false;}
      if(nWfqYuMagD == true){nWfqYuMagD = false;}
      if(RJIBjeMBcG == true){RJIBjeMBcG = false;}
      if(kZjsDyNErd == true){kZjsDyNErd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQTESXHVAL
{ 
  void RjeedRiyVb()
  { 
      bool sOkBNzygjw = false;
      bool yATWWuoPSK = false;
      bool cpWHJRMZIa = false;
      bool TcNizJOFnV = false;
      bool cRbpkaHuZV = false;
      bool rXIeTCqcru = false;
      bool lYYJbVlkWM = false;
      bool gjbxhLOfWh = false;
      bool JQAliuUiOw = false;
      bool RkNriErSNP = false;
      bool nWXNoHwKxI = false;
      bool nKGJlVXlag = false;
      bool ADVZtuWiNc = false;
      bool SwRGtmsmwa = false;
      bool zJlGIGeDGN = false;
      bool fGqgOjAxSt = false;
      bool kMxTorszPy = false;
      bool ckpzgqRPRm = false;
      bool PSczxMEkrJ = false;
      bool muTBomLRQP = false;
      string mRPrJEmlEK;
      string bISwrtaXNi;
      string NIXLFiAlpk;
      string Elicjybscd;
      string rfLlFwWSyI;
      string DkHeRdtEma;
      string DBuSGpYoLs;
      string ShuiqhxkFJ;
      string LhmggTdELF;
      string EWFBaqjrfP;
      string WgGEpVoYnj;
      string gIzdOUNNkl;
      string MUdFoubsHz;
      string xFFpldbhqL;
      string dEPbYwXblG;
      string dVGsDCCAPt;
      string twQnlbCJqk;
      string seWZIHECgs;
      string XzGBUbyMli;
      string aaSwRgmbox;
      if(mRPrJEmlEK == WgGEpVoYnj){sOkBNzygjw = true;}
      else if(WgGEpVoYnj == mRPrJEmlEK){nWXNoHwKxI = true;}
      if(bISwrtaXNi == gIzdOUNNkl){yATWWuoPSK = true;}
      else if(gIzdOUNNkl == bISwrtaXNi){nKGJlVXlag = true;}
      if(NIXLFiAlpk == MUdFoubsHz){cpWHJRMZIa = true;}
      else if(MUdFoubsHz == NIXLFiAlpk){ADVZtuWiNc = true;}
      if(Elicjybscd == xFFpldbhqL){TcNizJOFnV = true;}
      else if(xFFpldbhqL == Elicjybscd){SwRGtmsmwa = true;}
      if(rfLlFwWSyI == dEPbYwXblG){cRbpkaHuZV = true;}
      else if(dEPbYwXblG == rfLlFwWSyI){zJlGIGeDGN = true;}
      if(DkHeRdtEma == dVGsDCCAPt){rXIeTCqcru = true;}
      else if(dVGsDCCAPt == DkHeRdtEma){fGqgOjAxSt = true;}
      if(DBuSGpYoLs == twQnlbCJqk){lYYJbVlkWM = true;}
      else if(twQnlbCJqk == DBuSGpYoLs){kMxTorszPy = true;}
      if(ShuiqhxkFJ == seWZIHECgs){gjbxhLOfWh = true;}
      if(LhmggTdELF == XzGBUbyMli){JQAliuUiOw = true;}
      if(EWFBaqjrfP == aaSwRgmbox){RkNriErSNP = true;}
      while(seWZIHECgs == ShuiqhxkFJ){ckpzgqRPRm = true;}
      while(XzGBUbyMli == XzGBUbyMli){PSczxMEkrJ = true;}
      while(aaSwRgmbox == aaSwRgmbox){muTBomLRQP = true;}
      if(sOkBNzygjw == true){sOkBNzygjw = false;}
      if(yATWWuoPSK == true){yATWWuoPSK = false;}
      if(cpWHJRMZIa == true){cpWHJRMZIa = false;}
      if(TcNizJOFnV == true){TcNizJOFnV = false;}
      if(cRbpkaHuZV == true){cRbpkaHuZV = false;}
      if(rXIeTCqcru == true){rXIeTCqcru = false;}
      if(lYYJbVlkWM == true){lYYJbVlkWM = false;}
      if(gjbxhLOfWh == true){gjbxhLOfWh = false;}
      if(JQAliuUiOw == true){JQAliuUiOw = false;}
      if(RkNriErSNP == true){RkNriErSNP = false;}
      if(nWXNoHwKxI == true){nWXNoHwKxI = false;}
      if(nKGJlVXlag == true){nKGJlVXlag = false;}
      if(ADVZtuWiNc == true){ADVZtuWiNc = false;}
      if(SwRGtmsmwa == true){SwRGtmsmwa = false;}
      if(zJlGIGeDGN == true){zJlGIGeDGN = false;}
      if(fGqgOjAxSt == true){fGqgOjAxSt = false;}
      if(kMxTorszPy == true){kMxTorszPy = false;}
      if(ckpzgqRPRm == true){ckpzgqRPRm = false;}
      if(PSczxMEkrJ == true){PSczxMEkrJ = false;}
      if(muTBomLRQP == true){muTBomLRQP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKCHLSQFDG
{ 
  void TYdkqtSDxT()
  { 
      bool wwPJTBZsIy = false;
      bool ISneTfPtpj = false;
      bool eowgoZdTPY = false;
      bool qlszcokrgS = false;
      bool fdiJVGYQQn = false;
      bool drskUGzhUt = false;
      bool XFdiHWZoBd = false;
      bool tWNWDAGlLi = false;
      bool AMCbuzrHdW = false;
      bool oCXluZAzCy = false;
      bool fjPlsGdVhT = false;
      bool zNWktKCBnI = false;
      bool dSKdnqzbbd = false;
      bool AHiMDPxQio = false;
      bool UWZJWbfmrj = false;
      bool WzKtUNZkxC = false;
      bool GCtDTrdJhd = false;
      bool NlSzmGsAGM = false;
      bool KMiqGAwoqp = false;
      bool pLSfhRbVoe = false;
      string seklMZYelD;
      string ubVmconCfd;
      string HXJRQcsrDq;
      string UuIOcxKQfb;
      string fAImoNOBlV;
      string gPIFfUUSVj;
      string ffbtizTHKe;
      string dWWExHPVbC;
      string NrGgKEmDiH;
      string brtuuAXNEp;
      string tGpGqJsEHX;
      string EzqTVnYtjd;
      string MQYCClcaIw;
      string iBRlIHBzpA;
      string LiuKDcAaYH;
      string adcacdhnEF;
      string gRuLoDgELO;
      string mYEjRdUOzZ;
      string kBCBUFXqId;
      string ZNujTsmiUA;
      if(seklMZYelD == tGpGqJsEHX){wwPJTBZsIy = true;}
      else if(tGpGqJsEHX == seklMZYelD){fjPlsGdVhT = true;}
      if(ubVmconCfd == EzqTVnYtjd){ISneTfPtpj = true;}
      else if(EzqTVnYtjd == ubVmconCfd){zNWktKCBnI = true;}
      if(HXJRQcsrDq == MQYCClcaIw){eowgoZdTPY = true;}
      else if(MQYCClcaIw == HXJRQcsrDq){dSKdnqzbbd = true;}
      if(UuIOcxKQfb == iBRlIHBzpA){qlszcokrgS = true;}
      else if(iBRlIHBzpA == UuIOcxKQfb){AHiMDPxQio = true;}
      if(fAImoNOBlV == LiuKDcAaYH){fdiJVGYQQn = true;}
      else if(LiuKDcAaYH == fAImoNOBlV){UWZJWbfmrj = true;}
      if(gPIFfUUSVj == adcacdhnEF){drskUGzhUt = true;}
      else if(adcacdhnEF == gPIFfUUSVj){WzKtUNZkxC = true;}
      if(ffbtizTHKe == gRuLoDgELO){XFdiHWZoBd = true;}
      else if(gRuLoDgELO == ffbtizTHKe){GCtDTrdJhd = true;}
      if(dWWExHPVbC == mYEjRdUOzZ){tWNWDAGlLi = true;}
      if(NrGgKEmDiH == kBCBUFXqId){AMCbuzrHdW = true;}
      if(brtuuAXNEp == ZNujTsmiUA){oCXluZAzCy = true;}
      while(mYEjRdUOzZ == dWWExHPVbC){NlSzmGsAGM = true;}
      while(kBCBUFXqId == kBCBUFXqId){KMiqGAwoqp = true;}
      while(ZNujTsmiUA == ZNujTsmiUA){pLSfhRbVoe = true;}
      if(wwPJTBZsIy == true){wwPJTBZsIy = false;}
      if(ISneTfPtpj == true){ISneTfPtpj = false;}
      if(eowgoZdTPY == true){eowgoZdTPY = false;}
      if(qlszcokrgS == true){qlszcokrgS = false;}
      if(fdiJVGYQQn == true){fdiJVGYQQn = false;}
      if(drskUGzhUt == true){drskUGzhUt = false;}
      if(XFdiHWZoBd == true){XFdiHWZoBd = false;}
      if(tWNWDAGlLi == true){tWNWDAGlLi = false;}
      if(AMCbuzrHdW == true){AMCbuzrHdW = false;}
      if(oCXluZAzCy == true){oCXluZAzCy = false;}
      if(fjPlsGdVhT == true){fjPlsGdVhT = false;}
      if(zNWktKCBnI == true){zNWktKCBnI = false;}
      if(dSKdnqzbbd == true){dSKdnqzbbd = false;}
      if(AHiMDPxQio == true){AHiMDPxQio = false;}
      if(UWZJWbfmrj == true){UWZJWbfmrj = false;}
      if(WzKtUNZkxC == true){WzKtUNZkxC = false;}
      if(GCtDTrdJhd == true){GCtDTrdJhd = false;}
      if(NlSzmGsAGM == true){NlSzmGsAGM = false;}
      if(KMiqGAwoqp == true){KMiqGAwoqp = false;}
      if(pLSfhRbVoe == true){pLSfhRbVoe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWGGAUYWSJ
{ 
  void MnxidLjRKg()
  { 
      bool DGpkxbdDWD = false;
      bool mciSuKFJSu = false;
      bool flXIMfdBuO = false;
      bool tPcqkKmxmP = false;
      bool EOHHyacXfA = false;
      bool xzPJaQigXQ = false;
      bool xcIIJXArhk = false;
      bool WHWDpQePJl = false;
      bool CGVtRtzSQT = false;
      bool bFYVSbGyxa = false;
      bool ZkptcobMSJ = false;
      bool kSXlNqHNpP = false;
      bool XgbNJQhAkO = false;
      bool KfSiLRQaRb = false;
      bool RmAGiIhmIa = false;
      bool TsHhDsJbjM = false;
      bool GbbEzFAoZw = false;
      bool afuOxjgUeA = false;
      bool hurJtRXjeR = false;
      bool HnqFVpLuHd = false;
      string JZxrIMYsUa;
      string ZjJPLSsVFG;
      string KAdRUmspVR;
      string FxyokAVaDz;
      string AuOQnQwOaP;
      string SpaFjJweXV;
      string TiWCUblUdL;
      string wRSGGOlNdE;
      string peOGzOWsEb;
      string DpDheRXLuL;
      string eajPSBXUzU;
      string XiBSfnTQDG;
      string FrQCIFNjan;
      string pZSRYOuynx;
      string pCsiETojCp;
      string xHInGlKhHM;
      string mmsKdxQitQ;
      string sVcFQCzgyn;
      string QchjqiRdLl;
      string DMqaKCIiEG;
      if(JZxrIMYsUa == eajPSBXUzU){DGpkxbdDWD = true;}
      else if(eajPSBXUzU == JZxrIMYsUa){ZkptcobMSJ = true;}
      if(ZjJPLSsVFG == XiBSfnTQDG){mciSuKFJSu = true;}
      else if(XiBSfnTQDG == ZjJPLSsVFG){kSXlNqHNpP = true;}
      if(KAdRUmspVR == FrQCIFNjan){flXIMfdBuO = true;}
      else if(FrQCIFNjan == KAdRUmspVR){XgbNJQhAkO = true;}
      if(FxyokAVaDz == pZSRYOuynx){tPcqkKmxmP = true;}
      else if(pZSRYOuynx == FxyokAVaDz){KfSiLRQaRb = true;}
      if(AuOQnQwOaP == pCsiETojCp){EOHHyacXfA = true;}
      else if(pCsiETojCp == AuOQnQwOaP){RmAGiIhmIa = true;}
      if(SpaFjJweXV == xHInGlKhHM){xzPJaQigXQ = true;}
      else if(xHInGlKhHM == SpaFjJweXV){TsHhDsJbjM = true;}
      if(TiWCUblUdL == mmsKdxQitQ){xcIIJXArhk = true;}
      else if(mmsKdxQitQ == TiWCUblUdL){GbbEzFAoZw = true;}
      if(wRSGGOlNdE == sVcFQCzgyn){WHWDpQePJl = true;}
      if(peOGzOWsEb == QchjqiRdLl){CGVtRtzSQT = true;}
      if(DpDheRXLuL == DMqaKCIiEG){bFYVSbGyxa = true;}
      while(sVcFQCzgyn == wRSGGOlNdE){afuOxjgUeA = true;}
      while(QchjqiRdLl == QchjqiRdLl){hurJtRXjeR = true;}
      while(DMqaKCIiEG == DMqaKCIiEG){HnqFVpLuHd = true;}
      if(DGpkxbdDWD == true){DGpkxbdDWD = false;}
      if(mciSuKFJSu == true){mciSuKFJSu = false;}
      if(flXIMfdBuO == true){flXIMfdBuO = false;}
      if(tPcqkKmxmP == true){tPcqkKmxmP = false;}
      if(EOHHyacXfA == true){EOHHyacXfA = false;}
      if(xzPJaQigXQ == true){xzPJaQigXQ = false;}
      if(xcIIJXArhk == true){xcIIJXArhk = false;}
      if(WHWDpQePJl == true){WHWDpQePJl = false;}
      if(CGVtRtzSQT == true){CGVtRtzSQT = false;}
      if(bFYVSbGyxa == true){bFYVSbGyxa = false;}
      if(ZkptcobMSJ == true){ZkptcobMSJ = false;}
      if(kSXlNqHNpP == true){kSXlNqHNpP = false;}
      if(XgbNJQhAkO == true){XgbNJQhAkO = false;}
      if(KfSiLRQaRb == true){KfSiLRQaRb = false;}
      if(RmAGiIhmIa == true){RmAGiIhmIa = false;}
      if(TsHhDsJbjM == true){TsHhDsJbjM = false;}
      if(GbbEzFAoZw == true){GbbEzFAoZw = false;}
      if(afuOxjgUeA == true){afuOxjgUeA = false;}
      if(hurJtRXjeR == true){hurJtRXjeR = false;}
      if(HnqFVpLuHd == true){HnqFVpLuHd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPWRZZNAMX
{ 
  void alHQjTesnm()
  { 
      bool yIpmdlpdxA = false;
      bool niPijXcdTX = false;
      bool VUrLbdEgOY = false;
      bool xJsAjZcrye = false;
      bool tXrDGkRlsw = false;
      bool sLjlIcPdKz = false;
      bool hIPYCepPzJ = false;
      bool ujeocxcnFq = false;
      bool MSnRelYGqG = false;
      bool JzhyxkHTBb = false;
      bool uBmiBJftIK = false;
      bool AaYSmOUytQ = false;
      bool FiXrAuCfrr = false;
      bool pImcwKeEPV = false;
      bool FdyfFhaOLh = false;
      bool PIZjVLdtiF = false;
      bool HACQUqnuWb = false;
      bool iQhXLajqlR = false;
      bool UmUJbgiCHj = false;
      bool gkVKNFbhLN = false;
      string GspdGwSoJw;
      string sgXYEZfwPl;
      string CtunUsEIjt;
      string VoXtBEtMxU;
      string iKWsaPiAKj;
      string aVTRjLyBJM;
      string qKFOZEJdXz;
      string eTzuCqXCNE;
      string KExzTAUFKp;
      string GrCkcYFISW;
      string GFbKEHVYPs;
      string munFBmMFtZ;
      string iDTgsmQORd;
      string kPjqxFbluL;
      string dwpQCKExio;
      string MANsmCktRR;
      string qHGkHXLwHw;
      string LZKiumNCeh;
      string hSecRjCpEu;
      string TgUcUVoEJe;
      if(GspdGwSoJw == GFbKEHVYPs){yIpmdlpdxA = true;}
      else if(GFbKEHVYPs == GspdGwSoJw){uBmiBJftIK = true;}
      if(sgXYEZfwPl == munFBmMFtZ){niPijXcdTX = true;}
      else if(munFBmMFtZ == sgXYEZfwPl){AaYSmOUytQ = true;}
      if(CtunUsEIjt == iDTgsmQORd){VUrLbdEgOY = true;}
      else if(iDTgsmQORd == CtunUsEIjt){FiXrAuCfrr = true;}
      if(VoXtBEtMxU == kPjqxFbluL){xJsAjZcrye = true;}
      else if(kPjqxFbluL == VoXtBEtMxU){pImcwKeEPV = true;}
      if(iKWsaPiAKj == dwpQCKExio){tXrDGkRlsw = true;}
      else if(dwpQCKExio == iKWsaPiAKj){FdyfFhaOLh = true;}
      if(aVTRjLyBJM == MANsmCktRR){sLjlIcPdKz = true;}
      else if(MANsmCktRR == aVTRjLyBJM){PIZjVLdtiF = true;}
      if(qKFOZEJdXz == qHGkHXLwHw){hIPYCepPzJ = true;}
      else if(qHGkHXLwHw == qKFOZEJdXz){HACQUqnuWb = true;}
      if(eTzuCqXCNE == LZKiumNCeh){ujeocxcnFq = true;}
      if(KExzTAUFKp == hSecRjCpEu){MSnRelYGqG = true;}
      if(GrCkcYFISW == TgUcUVoEJe){JzhyxkHTBb = true;}
      while(LZKiumNCeh == eTzuCqXCNE){iQhXLajqlR = true;}
      while(hSecRjCpEu == hSecRjCpEu){UmUJbgiCHj = true;}
      while(TgUcUVoEJe == TgUcUVoEJe){gkVKNFbhLN = true;}
      if(yIpmdlpdxA == true){yIpmdlpdxA = false;}
      if(niPijXcdTX == true){niPijXcdTX = false;}
      if(VUrLbdEgOY == true){VUrLbdEgOY = false;}
      if(xJsAjZcrye == true){xJsAjZcrye = false;}
      if(tXrDGkRlsw == true){tXrDGkRlsw = false;}
      if(sLjlIcPdKz == true){sLjlIcPdKz = false;}
      if(hIPYCepPzJ == true){hIPYCepPzJ = false;}
      if(ujeocxcnFq == true){ujeocxcnFq = false;}
      if(MSnRelYGqG == true){MSnRelYGqG = false;}
      if(JzhyxkHTBb == true){JzhyxkHTBb = false;}
      if(uBmiBJftIK == true){uBmiBJftIK = false;}
      if(AaYSmOUytQ == true){AaYSmOUytQ = false;}
      if(FiXrAuCfrr == true){FiXrAuCfrr = false;}
      if(pImcwKeEPV == true){pImcwKeEPV = false;}
      if(FdyfFhaOLh == true){FdyfFhaOLh = false;}
      if(PIZjVLdtiF == true){PIZjVLdtiF = false;}
      if(HACQUqnuWb == true){HACQUqnuWb = false;}
      if(iQhXLajqlR == true){iQhXLajqlR = false;}
      if(UmUJbgiCHj == true){UmUJbgiCHj = false;}
      if(gkVKNFbhLN == true){gkVKNFbhLN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMODOURRQK
{ 
  void WkEyxPeTiB()
  { 
      bool pkwMTwYkaY = false;
      bool pbZrwRSKBp = false;
      bool JwNxxuKkJt = false;
      bool zKcsPrPoOx = false;
      bool weiFECOEOL = false;
      bool qlgDKsWzOY = false;
      bool lmagYfygcE = false;
      bool BcuEseNHst = false;
      bool gFWxCNcZhV = false;
      bool UPapKJDCgY = false;
      bool EgbJKOpcKf = false;
      bool fOFTrfPddL = false;
      bool CYzGikCEtj = false;
      bool bLaUpAdMmn = false;
      bool WAOCpGKGye = false;
      bool sYXVVfhUaY = false;
      bool LkiZETmkdq = false;
      bool BDponBJxPc = false;
      bool auGOqCmFyJ = false;
      bool RJlOblRnxV = false;
      string bscJfQpeLL;
      string WXromBmqFO;
      string AGsbwTfqde;
      string lKZGbrXYGB;
      string HFzoTHNItK;
      string rulByUABML;
      string jzBgZLykNt;
      string dNjEGuHEIo;
      string GXwSlpYYIG;
      string rWMtQIESOI;
      string JbtAgeKhtC;
      string NurXFMDhtj;
      string mYcGCHBpmy;
      string qnozedcukH;
      string epeFswdonE;
      string EVXeUjznyZ;
      string dUtuLYGrrb;
      string jHxmEwtXNF;
      string cMBisVPJet;
      string dnxLcKwitT;
      if(bscJfQpeLL == JbtAgeKhtC){pkwMTwYkaY = true;}
      else if(JbtAgeKhtC == bscJfQpeLL){EgbJKOpcKf = true;}
      if(WXromBmqFO == NurXFMDhtj){pbZrwRSKBp = true;}
      else if(NurXFMDhtj == WXromBmqFO){fOFTrfPddL = true;}
      if(AGsbwTfqde == mYcGCHBpmy){JwNxxuKkJt = true;}
      else if(mYcGCHBpmy == AGsbwTfqde){CYzGikCEtj = true;}
      if(lKZGbrXYGB == qnozedcukH){zKcsPrPoOx = true;}
      else if(qnozedcukH == lKZGbrXYGB){bLaUpAdMmn = true;}
      if(HFzoTHNItK == epeFswdonE){weiFECOEOL = true;}
      else if(epeFswdonE == HFzoTHNItK){WAOCpGKGye = true;}
      if(rulByUABML == EVXeUjznyZ){qlgDKsWzOY = true;}
      else if(EVXeUjznyZ == rulByUABML){sYXVVfhUaY = true;}
      if(jzBgZLykNt == dUtuLYGrrb){lmagYfygcE = true;}
      else if(dUtuLYGrrb == jzBgZLykNt){LkiZETmkdq = true;}
      if(dNjEGuHEIo == jHxmEwtXNF){BcuEseNHst = true;}
      if(GXwSlpYYIG == cMBisVPJet){gFWxCNcZhV = true;}
      if(rWMtQIESOI == dnxLcKwitT){UPapKJDCgY = true;}
      while(jHxmEwtXNF == dNjEGuHEIo){BDponBJxPc = true;}
      while(cMBisVPJet == cMBisVPJet){auGOqCmFyJ = true;}
      while(dnxLcKwitT == dnxLcKwitT){RJlOblRnxV = true;}
      if(pkwMTwYkaY == true){pkwMTwYkaY = false;}
      if(pbZrwRSKBp == true){pbZrwRSKBp = false;}
      if(JwNxxuKkJt == true){JwNxxuKkJt = false;}
      if(zKcsPrPoOx == true){zKcsPrPoOx = false;}
      if(weiFECOEOL == true){weiFECOEOL = false;}
      if(qlgDKsWzOY == true){qlgDKsWzOY = false;}
      if(lmagYfygcE == true){lmagYfygcE = false;}
      if(BcuEseNHst == true){BcuEseNHst = false;}
      if(gFWxCNcZhV == true){gFWxCNcZhV = false;}
      if(UPapKJDCgY == true){UPapKJDCgY = false;}
      if(EgbJKOpcKf == true){EgbJKOpcKf = false;}
      if(fOFTrfPddL == true){fOFTrfPddL = false;}
      if(CYzGikCEtj == true){CYzGikCEtj = false;}
      if(bLaUpAdMmn == true){bLaUpAdMmn = false;}
      if(WAOCpGKGye == true){WAOCpGKGye = false;}
      if(sYXVVfhUaY == true){sYXVVfhUaY = false;}
      if(LkiZETmkdq == true){LkiZETmkdq = false;}
      if(BDponBJxPc == true){BDponBJxPc = false;}
      if(auGOqCmFyJ == true){auGOqCmFyJ = false;}
      if(RJlOblRnxV == true){RJlOblRnxV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPQSTRGJYA
{ 
  void gjxawPWlre()
  { 
      bool FFeJVrsIts = false;
      bool raJHBDfcln = false;
      bool VsPiGdwoTI = false;
      bool IzAysgMnJh = false;
      bool sQfAiXypkV = false;
      bool FjbCILowDq = false;
      bool uDolkraKNU = false;
      bool qqSDtFNPzh = false;
      bool eGEyDXXxog = false;
      bool qPjSlpatOq = false;
      bool xnbPdNRXIC = false;
      bool xZwUMoyphM = false;
      bool UcUgcaGARD = false;
      bool dTAIkqenTo = false;
      bool GzoliQTPGx = false;
      bool rjLCVTStmD = false;
      bool GRGEYdZniV = false;
      bool KJWrFUmhxL = false;
      bool HqtULsHxlR = false;
      bool XjBPioskNF = false;
      string dSfTrnUEwM;
      string CuYHlHJAfC;
      string TQXqCcXrmk;
      string xpLPIEXxAE;
      string JnZMVcjnLY;
      string nqXOOMuoQO;
      string QcQKPLjJyg;
      string jMzbrfqLUZ;
      string rjgOwGSwAu;
      string JiflngXPwJ;
      string saodnbqwWi;
      string ViTqWgwCNI;
      string smICXAgNmK;
      string HaOKgQtCZU;
      string OWZRZZOoOH;
      string kUBnQFRlFm;
      string udILauUJJF;
      string lsbssWNqcy;
      string lqyfZmYata;
      string yIxlYkNNpe;
      if(dSfTrnUEwM == saodnbqwWi){FFeJVrsIts = true;}
      else if(saodnbqwWi == dSfTrnUEwM){xnbPdNRXIC = true;}
      if(CuYHlHJAfC == ViTqWgwCNI){raJHBDfcln = true;}
      else if(ViTqWgwCNI == CuYHlHJAfC){xZwUMoyphM = true;}
      if(TQXqCcXrmk == smICXAgNmK){VsPiGdwoTI = true;}
      else if(smICXAgNmK == TQXqCcXrmk){UcUgcaGARD = true;}
      if(xpLPIEXxAE == HaOKgQtCZU){IzAysgMnJh = true;}
      else if(HaOKgQtCZU == xpLPIEXxAE){dTAIkqenTo = true;}
      if(JnZMVcjnLY == OWZRZZOoOH){sQfAiXypkV = true;}
      else if(OWZRZZOoOH == JnZMVcjnLY){GzoliQTPGx = true;}
      if(nqXOOMuoQO == kUBnQFRlFm){FjbCILowDq = true;}
      else if(kUBnQFRlFm == nqXOOMuoQO){rjLCVTStmD = true;}
      if(QcQKPLjJyg == udILauUJJF){uDolkraKNU = true;}
      else if(udILauUJJF == QcQKPLjJyg){GRGEYdZniV = true;}
      if(jMzbrfqLUZ == lsbssWNqcy){qqSDtFNPzh = true;}
      if(rjgOwGSwAu == lqyfZmYata){eGEyDXXxog = true;}
      if(JiflngXPwJ == yIxlYkNNpe){qPjSlpatOq = true;}
      while(lsbssWNqcy == jMzbrfqLUZ){KJWrFUmhxL = true;}
      while(lqyfZmYata == lqyfZmYata){HqtULsHxlR = true;}
      while(yIxlYkNNpe == yIxlYkNNpe){XjBPioskNF = true;}
      if(FFeJVrsIts == true){FFeJVrsIts = false;}
      if(raJHBDfcln == true){raJHBDfcln = false;}
      if(VsPiGdwoTI == true){VsPiGdwoTI = false;}
      if(IzAysgMnJh == true){IzAysgMnJh = false;}
      if(sQfAiXypkV == true){sQfAiXypkV = false;}
      if(FjbCILowDq == true){FjbCILowDq = false;}
      if(uDolkraKNU == true){uDolkraKNU = false;}
      if(qqSDtFNPzh == true){qqSDtFNPzh = false;}
      if(eGEyDXXxog == true){eGEyDXXxog = false;}
      if(qPjSlpatOq == true){qPjSlpatOq = false;}
      if(xnbPdNRXIC == true){xnbPdNRXIC = false;}
      if(xZwUMoyphM == true){xZwUMoyphM = false;}
      if(UcUgcaGARD == true){UcUgcaGARD = false;}
      if(dTAIkqenTo == true){dTAIkqenTo = false;}
      if(GzoliQTPGx == true){GzoliQTPGx = false;}
      if(rjLCVTStmD == true){rjLCVTStmD = false;}
      if(GRGEYdZniV == true){GRGEYdZniV = false;}
      if(KJWrFUmhxL == true){KJWrFUmhxL = false;}
      if(HqtULsHxlR == true){HqtULsHxlR = false;}
      if(XjBPioskNF == true){XjBPioskNF = false;}
    } 
}; 
