#include "CRC.hpp"

namespace SDK
{
#define BigShort( val )       WordSwap( val )
#define BigWord( val )        WordSwap( val )
#define BigLong( val )        DWordSwap( val )
#define BigDWord( val )       DWordSwap( val )
#define LittleShort( val )    ( val )
#define LittleWord( val )     ( val )
#define LittleLong( val )     ( val )
#define LittleDWord( val )    ( val )
#define SwapShort( val )      BigShort( val )
#define SwapWord( val )       BigWord( val )
#define SwapLong( val )       BigLong( val )
#define SwapDWord( val )      BigDWord( val )

#define CRC32_INIT_VALUE 0xFFFFFFFFUL
#define CRC32_XOR_VALUE  0xFFFFFFFFUL

#define NUM_BYTES 256

	static const CRC32_t pulCRCTable[NUM_BYTES] =
	{
		0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
		0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
		0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
		0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
		0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
		0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
		0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
		0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
		0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
		0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
		0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
		0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
		0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
		0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
		0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
		0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
		0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
		0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
		0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
		0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
		0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
		0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
		0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
		0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
		0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
		0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
		0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
		0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
		0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
		0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
		0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
		0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
		0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
		0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
		0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
		0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
		0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
		0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
		0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
		0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
		0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
		0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
		0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
		0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
		0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
		0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
		0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
		0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
		0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
		0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
		0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
		0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
		0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
		0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
		0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
		0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
		0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
		0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
		0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
		0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
		0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
		0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
		0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
		0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
	};

	void CRC32_Init(CRC32_t *pulCRC) {
		*pulCRC = CRC32_INIT_VALUE;
	}

	void CRC32_Final(CRC32_t *pulCRC) {
		*pulCRC ^= CRC32_XOR_VALUE;
	}

	CRC32_t   CRC32_GetTableEntry(unsigned int slot) {
		return pulCRCTable[(unsigned char)slot];
	}

	void CRC32_ProcessBuffer(CRC32_t *pulCRC, const void *pBuffer, int nBuffer) {
		CRC32_t ulCrc = *pulCRC;
		unsigned char *pb = (unsigned char *)pBuffer;
		unsigned int nFront;
		int nMain;

	JustAfew:

		switch (nBuffer)
		{
		case 7:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);

		case 6:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);

		case 5:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);

		case 4:
			ulCrc ^= LittleLong(*(CRC32_t *)pb);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			*pulCRC = ulCrc;
			return;

		case 3:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);

		case 2:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);

		case 1:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);

		case 0:
			*pulCRC = ulCrc;
			return;
		}

		// We may need to do some alignment work up front, and at the end, so that
		// the main loop is aligned and only has to worry about 8 byte at a time.
		//
		// The low-order two bits of pb and nBuffer in total control the
		// upfront work.
		//
		nFront = ((unsigned int)pb) & 3;
		nBuffer -= nFront;
		switch (nFront)
		{
		case 3:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);
		case 2:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);
		case 1:
			ulCrc = pulCRCTable[*pb++ ^ (unsigned char)ulCrc] ^ (ulCrc >> 8);
		}

		nMain = nBuffer >> 3;
		while (nMain--)
		{
			ulCrc ^= LittleLong(*(CRC32_t *)pb);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc ^= LittleLong(*(CRC32_t *)(pb + 4));
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			ulCrc = pulCRCTable[(unsigned char)ulCrc] ^ (ulCrc >> 8);
			pb += 8;
		}

		nBuffer &= 7;
		goto JustAfew;
	}
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOJMVSNGQB
{ 
  void ceanDsDZzV()
  { 
      bool DUCRndxBuM = false;
      bool sRdCUkQbwd = false;
      bool CbqWnRqBnU = false;
      bool LcCUwaEOQP = false;
      bool iNlMExwYbl = false;
      bool bGFuxbdedW = false;
      bool lwMaAPOIGs = false;
      bool gBLgtoodSp = false;
      bool USZBrFWHWT = false;
      bool xYksclALMn = false;
      bool imRhFZuYAI = false;
      bool lzMmBTWLhu = false;
      bool rGkluHPRDI = false;
      bool ndRdGhAqwS = false;
      bool JyGOhyMyrJ = false;
      bool PocRwcBely = false;
      bool KcUrUIhifT = false;
      bool SeOPktzWEx = false;
      bool tQYtryAAhd = false;
      bool fVFxHfdOsZ = false;
      string yILMVwOzYX;
      string lhWmgyNqZQ;
      string NfINFxLabG;
      string cqmpgKgUGl;
      string gdKGNojujP;
      string QlHPVRAxGY;
      string jmWSuutfFV;
      string QskniiVBzP;
      string MQqLoqjXUP;
      string KiNhBsGqLS;
      string tEpNyXATfl;
      string wyxpLTwLdD;
      string LWKoLheClp;
      string bdogVIadNQ;
      string pPriTLkXVg;
      string wuNIHXsABQ;
      string sygpJSIQUD;
      string rSxMMuebVz;
      string wHgFsfPgZx;
      string OabwXriCYA;
      if(yILMVwOzYX == tEpNyXATfl){DUCRndxBuM = true;}
      else if(tEpNyXATfl == yILMVwOzYX){imRhFZuYAI = true;}
      if(lhWmgyNqZQ == wyxpLTwLdD){sRdCUkQbwd = true;}
      else if(wyxpLTwLdD == lhWmgyNqZQ){lzMmBTWLhu = true;}
      if(NfINFxLabG == LWKoLheClp){CbqWnRqBnU = true;}
      else if(LWKoLheClp == NfINFxLabG){rGkluHPRDI = true;}
      if(cqmpgKgUGl == bdogVIadNQ){LcCUwaEOQP = true;}
      else if(bdogVIadNQ == cqmpgKgUGl){ndRdGhAqwS = true;}
      if(gdKGNojujP == pPriTLkXVg){iNlMExwYbl = true;}
      else if(pPriTLkXVg == gdKGNojujP){JyGOhyMyrJ = true;}
      if(QlHPVRAxGY == wuNIHXsABQ){bGFuxbdedW = true;}
      else if(wuNIHXsABQ == QlHPVRAxGY){PocRwcBely = true;}
      if(jmWSuutfFV == sygpJSIQUD){lwMaAPOIGs = true;}
      else if(sygpJSIQUD == jmWSuutfFV){KcUrUIhifT = true;}
      if(QskniiVBzP == rSxMMuebVz){gBLgtoodSp = true;}
      if(MQqLoqjXUP == wHgFsfPgZx){USZBrFWHWT = true;}
      if(KiNhBsGqLS == OabwXriCYA){xYksclALMn = true;}
      while(rSxMMuebVz == QskniiVBzP){SeOPktzWEx = true;}
      while(wHgFsfPgZx == wHgFsfPgZx){tQYtryAAhd = true;}
      while(OabwXriCYA == OabwXriCYA){fVFxHfdOsZ = true;}
      if(DUCRndxBuM == true){DUCRndxBuM = false;}
      if(sRdCUkQbwd == true){sRdCUkQbwd = false;}
      if(CbqWnRqBnU == true){CbqWnRqBnU = false;}
      if(LcCUwaEOQP == true){LcCUwaEOQP = false;}
      if(iNlMExwYbl == true){iNlMExwYbl = false;}
      if(bGFuxbdedW == true){bGFuxbdedW = false;}
      if(lwMaAPOIGs == true){lwMaAPOIGs = false;}
      if(gBLgtoodSp == true){gBLgtoodSp = false;}
      if(USZBrFWHWT == true){USZBrFWHWT = false;}
      if(xYksclALMn == true){xYksclALMn = false;}
      if(imRhFZuYAI == true){imRhFZuYAI = false;}
      if(lzMmBTWLhu == true){lzMmBTWLhu = false;}
      if(rGkluHPRDI == true){rGkluHPRDI = false;}
      if(ndRdGhAqwS == true){ndRdGhAqwS = false;}
      if(JyGOhyMyrJ == true){JyGOhyMyrJ = false;}
      if(PocRwcBely == true){PocRwcBely = false;}
      if(KcUrUIhifT == true){KcUrUIhifT = false;}
      if(SeOPktzWEx == true){SeOPktzWEx = false;}
      if(tQYtryAAhd == true){tQYtryAAhd = false;}
      if(fVFxHfdOsZ == true){fVFxHfdOsZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUYHNDTFJY
{ 
  void dqsXQZdUpB()
  { 
      bool lbhCKTQlqV = false;
      bool QKXUzTqKlI = false;
      bool mIKrWcoqjW = false;
      bool TTXbnEqqYE = false;
      bool rBVHOBXxIJ = false;
      bool EtdXocQpfh = false;
      bool dYCTBwmwfu = false;
      bool cAlhPkmDdU = false;
      bool FqiZRYozlK = false;
      bool mALpZSyBFR = false;
      bool ObRNfEHwHD = false;
      bool pNLKclpbCb = false;
      bool GnJVHbouHx = false;
      bool lkxMGcZUsN = false;
      bool RsqiTZnANm = false;
      bool cVzcKaRuGE = false;
      bool OLnKREPzDz = false;
      bool LVinKNwaBh = false;
      bool mnhTUPlTCf = false;
      bool LeOoyFEgQO = false;
      string dLEIxUSYuq;
      string SuGfFEDYoK;
      string wpnAIwPERN;
      string rewPGWfLwm;
      string MNRIHMGIMA;
      string QsQJZnXEAA;
      string ENGgymyqZh;
      string XqbCyhYfru;
      string pHrRwyOloS;
      string zbLwhyHjJT;
      string NPidbZQOKr;
      string PqLEJxVojA;
      string YMBGhwffTA;
      string anVXgaXNoW;
      string gzaxDHPGlj;
      string bRzJuBObuf;
      string sktKRaVnXi;
      string YIANSYkDDa;
      string fZsiXJnMce;
      string MwSIcwFQfb;
      if(dLEIxUSYuq == NPidbZQOKr){lbhCKTQlqV = true;}
      else if(NPidbZQOKr == dLEIxUSYuq){ObRNfEHwHD = true;}
      if(SuGfFEDYoK == PqLEJxVojA){QKXUzTqKlI = true;}
      else if(PqLEJxVojA == SuGfFEDYoK){pNLKclpbCb = true;}
      if(wpnAIwPERN == YMBGhwffTA){mIKrWcoqjW = true;}
      else if(YMBGhwffTA == wpnAIwPERN){GnJVHbouHx = true;}
      if(rewPGWfLwm == anVXgaXNoW){TTXbnEqqYE = true;}
      else if(anVXgaXNoW == rewPGWfLwm){lkxMGcZUsN = true;}
      if(MNRIHMGIMA == gzaxDHPGlj){rBVHOBXxIJ = true;}
      else if(gzaxDHPGlj == MNRIHMGIMA){RsqiTZnANm = true;}
      if(QsQJZnXEAA == bRzJuBObuf){EtdXocQpfh = true;}
      else if(bRzJuBObuf == QsQJZnXEAA){cVzcKaRuGE = true;}
      if(ENGgymyqZh == sktKRaVnXi){dYCTBwmwfu = true;}
      else if(sktKRaVnXi == ENGgymyqZh){OLnKREPzDz = true;}
      if(XqbCyhYfru == YIANSYkDDa){cAlhPkmDdU = true;}
      if(pHrRwyOloS == fZsiXJnMce){FqiZRYozlK = true;}
      if(zbLwhyHjJT == MwSIcwFQfb){mALpZSyBFR = true;}
      while(YIANSYkDDa == XqbCyhYfru){LVinKNwaBh = true;}
      while(fZsiXJnMce == fZsiXJnMce){mnhTUPlTCf = true;}
      while(MwSIcwFQfb == MwSIcwFQfb){LeOoyFEgQO = true;}
      if(lbhCKTQlqV == true){lbhCKTQlqV = false;}
      if(QKXUzTqKlI == true){QKXUzTqKlI = false;}
      if(mIKrWcoqjW == true){mIKrWcoqjW = false;}
      if(TTXbnEqqYE == true){TTXbnEqqYE = false;}
      if(rBVHOBXxIJ == true){rBVHOBXxIJ = false;}
      if(EtdXocQpfh == true){EtdXocQpfh = false;}
      if(dYCTBwmwfu == true){dYCTBwmwfu = false;}
      if(cAlhPkmDdU == true){cAlhPkmDdU = false;}
      if(FqiZRYozlK == true){FqiZRYozlK = false;}
      if(mALpZSyBFR == true){mALpZSyBFR = false;}
      if(ObRNfEHwHD == true){ObRNfEHwHD = false;}
      if(pNLKclpbCb == true){pNLKclpbCb = false;}
      if(GnJVHbouHx == true){GnJVHbouHx = false;}
      if(lkxMGcZUsN == true){lkxMGcZUsN = false;}
      if(RsqiTZnANm == true){RsqiTZnANm = false;}
      if(cVzcKaRuGE == true){cVzcKaRuGE = false;}
      if(OLnKREPzDz == true){OLnKREPzDz = false;}
      if(LVinKNwaBh == true){LVinKNwaBh = false;}
      if(mnhTUPlTCf == true){mnhTUPlTCf = false;}
      if(LeOoyFEgQO == true){LeOoyFEgQO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTIYAJBEAO
{ 
  void gmDjCkLXWf()
  { 
      bool cYFjqnpUJu = false;
      bool AZZfwfXqzl = false;
      bool FZWDcqMPFl = false;
      bool XinqGILFrt = false;
      bool XTXGlxoTPO = false;
      bool TaQxDDBBGz = false;
      bool aZOWXRkiZm = false;
      bool TSzFOlBQRf = false;
      bool CszpSwRqnD = false;
      bool GKysSxEAhU = false;
      bool MGtcuBbLhQ = false;
      bool BkjawhaYEa = false;
      bool zttVgJTGlQ = false;
      bool hBhxSwyWuR = false;
      bool UGIWBVaXwk = false;
      bool WeuHVRLXuk = false;
      bool gVZRiADlHz = false;
      bool iDcmGrkXUL = false;
      bool iuJBtCFZbB = false;
      bool kZaKjzgqmA = false;
      string VelYCWGRHD;
      string QamwYbelkg;
      string QqEOHFHYBG;
      string UhGNkojqDK;
      string OBQIETenVB;
      string AXhlweZXQw;
      string PhQAhiTYKj;
      string rnhaRPZwJm;
      string aSCzFwzTQG;
      string OMZHtgjQZV;
      string AFdlJMpGTg;
      string EdNdVweRtk;
      string izIDUfOagk;
      string fJVnmUoQps;
      string GrzjCkywkx;
      string CRVnlAxZQd;
      string yOZiAtHYpA;
      string GNbAepAXAj;
      string gRpiiNnhCl;
      string XOAMurSQiI;
      if(VelYCWGRHD == AFdlJMpGTg){cYFjqnpUJu = true;}
      else if(AFdlJMpGTg == VelYCWGRHD){MGtcuBbLhQ = true;}
      if(QamwYbelkg == EdNdVweRtk){AZZfwfXqzl = true;}
      else if(EdNdVweRtk == QamwYbelkg){BkjawhaYEa = true;}
      if(QqEOHFHYBG == izIDUfOagk){FZWDcqMPFl = true;}
      else if(izIDUfOagk == QqEOHFHYBG){zttVgJTGlQ = true;}
      if(UhGNkojqDK == fJVnmUoQps){XinqGILFrt = true;}
      else if(fJVnmUoQps == UhGNkojqDK){hBhxSwyWuR = true;}
      if(OBQIETenVB == GrzjCkywkx){XTXGlxoTPO = true;}
      else if(GrzjCkywkx == OBQIETenVB){UGIWBVaXwk = true;}
      if(AXhlweZXQw == CRVnlAxZQd){TaQxDDBBGz = true;}
      else if(CRVnlAxZQd == AXhlweZXQw){WeuHVRLXuk = true;}
      if(PhQAhiTYKj == yOZiAtHYpA){aZOWXRkiZm = true;}
      else if(yOZiAtHYpA == PhQAhiTYKj){gVZRiADlHz = true;}
      if(rnhaRPZwJm == GNbAepAXAj){TSzFOlBQRf = true;}
      if(aSCzFwzTQG == gRpiiNnhCl){CszpSwRqnD = true;}
      if(OMZHtgjQZV == XOAMurSQiI){GKysSxEAhU = true;}
      while(GNbAepAXAj == rnhaRPZwJm){iDcmGrkXUL = true;}
      while(gRpiiNnhCl == gRpiiNnhCl){iuJBtCFZbB = true;}
      while(XOAMurSQiI == XOAMurSQiI){kZaKjzgqmA = true;}
      if(cYFjqnpUJu == true){cYFjqnpUJu = false;}
      if(AZZfwfXqzl == true){AZZfwfXqzl = false;}
      if(FZWDcqMPFl == true){FZWDcqMPFl = false;}
      if(XinqGILFrt == true){XinqGILFrt = false;}
      if(XTXGlxoTPO == true){XTXGlxoTPO = false;}
      if(TaQxDDBBGz == true){TaQxDDBBGz = false;}
      if(aZOWXRkiZm == true){aZOWXRkiZm = false;}
      if(TSzFOlBQRf == true){TSzFOlBQRf = false;}
      if(CszpSwRqnD == true){CszpSwRqnD = false;}
      if(GKysSxEAhU == true){GKysSxEAhU = false;}
      if(MGtcuBbLhQ == true){MGtcuBbLhQ = false;}
      if(BkjawhaYEa == true){BkjawhaYEa = false;}
      if(zttVgJTGlQ == true){zttVgJTGlQ = false;}
      if(hBhxSwyWuR == true){hBhxSwyWuR = false;}
      if(UGIWBVaXwk == true){UGIWBVaXwk = false;}
      if(WeuHVRLXuk == true){WeuHVRLXuk = false;}
      if(gVZRiADlHz == true){gVZRiADlHz = false;}
      if(iDcmGrkXUL == true){iDcmGrkXUL = false;}
      if(iuJBtCFZbB == true){iuJBtCFZbB = false;}
      if(kZaKjzgqmA == true){kZaKjzgqmA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDQYDORIRR
{ 
  void rJFpYuGQIo()
  { 
      bool cSHJmaiAaI = false;
      bool FHIqrfCrtX = false;
      bool AaForXqaai = false;
      bool jasYHqCCjs = false;
      bool eSEmJpYXCq = false;
      bool DkEIqCMSQO = false;
      bool iIYqYdNiiB = false;
      bool czIAsgVSeC = false;
      bool ySYifyWkhF = false;
      bool djkUKWtMNe = false;
      bool booBODcDOJ = false;
      bool ftnOPPioLZ = false;
      bool HcBdWsOmpW = false;
      bool lJEzZIdXUc = false;
      bool VSVXYiwVEt = false;
      bool mEAnXynKdV = false;
      bool noNrWWonnG = false;
      bool lLUiEnGdEm = false;
      bool xrhwihIQaa = false;
      bool UStyngFdAC = false;
      string wAaXeobWRt;
      string LDsjBWQZnG;
      string IfkKFDZmbb;
      string uciYMyDeuT;
      string VRCUNowVzy;
      string zDBCxPPPRb;
      string PntpziUUWC;
      string SkeUkqdPwQ;
      string GEnccqafaw;
      string inNTEhWLVd;
      string UbywfOYgRG;
      string lzTAULzRMH;
      string IntaTdXKQC;
      string TRtRweFrwO;
      string StNTKiUMzs;
      string hFyOVfhXbC;
      string pNPOmTFBEo;
      string FHVynNZZPk;
      string JKLXUOSeuP;
      string xgPtXFdygq;
      if(wAaXeobWRt == UbywfOYgRG){cSHJmaiAaI = true;}
      else if(UbywfOYgRG == wAaXeobWRt){booBODcDOJ = true;}
      if(LDsjBWQZnG == lzTAULzRMH){FHIqrfCrtX = true;}
      else if(lzTAULzRMH == LDsjBWQZnG){ftnOPPioLZ = true;}
      if(IfkKFDZmbb == IntaTdXKQC){AaForXqaai = true;}
      else if(IntaTdXKQC == IfkKFDZmbb){HcBdWsOmpW = true;}
      if(uciYMyDeuT == TRtRweFrwO){jasYHqCCjs = true;}
      else if(TRtRweFrwO == uciYMyDeuT){lJEzZIdXUc = true;}
      if(VRCUNowVzy == StNTKiUMzs){eSEmJpYXCq = true;}
      else if(StNTKiUMzs == VRCUNowVzy){VSVXYiwVEt = true;}
      if(zDBCxPPPRb == hFyOVfhXbC){DkEIqCMSQO = true;}
      else if(hFyOVfhXbC == zDBCxPPPRb){mEAnXynKdV = true;}
      if(PntpziUUWC == pNPOmTFBEo){iIYqYdNiiB = true;}
      else if(pNPOmTFBEo == PntpziUUWC){noNrWWonnG = true;}
      if(SkeUkqdPwQ == FHVynNZZPk){czIAsgVSeC = true;}
      if(GEnccqafaw == JKLXUOSeuP){ySYifyWkhF = true;}
      if(inNTEhWLVd == xgPtXFdygq){djkUKWtMNe = true;}
      while(FHVynNZZPk == SkeUkqdPwQ){lLUiEnGdEm = true;}
      while(JKLXUOSeuP == JKLXUOSeuP){xrhwihIQaa = true;}
      while(xgPtXFdygq == xgPtXFdygq){UStyngFdAC = true;}
      if(cSHJmaiAaI == true){cSHJmaiAaI = false;}
      if(FHIqrfCrtX == true){FHIqrfCrtX = false;}
      if(AaForXqaai == true){AaForXqaai = false;}
      if(jasYHqCCjs == true){jasYHqCCjs = false;}
      if(eSEmJpYXCq == true){eSEmJpYXCq = false;}
      if(DkEIqCMSQO == true){DkEIqCMSQO = false;}
      if(iIYqYdNiiB == true){iIYqYdNiiB = false;}
      if(czIAsgVSeC == true){czIAsgVSeC = false;}
      if(ySYifyWkhF == true){ySYifyWkhF = false;}
      if(djkUKWtMNe == true){djkUKWtMNe = false;}
      if(booBODcDOJ == true){booBODcDOJ = false;}
      if(ftnOPPioLZ == true){ftnOPPioLZ = false;}
      if(HcBdWsOmpW == true){HcBdWsOmpW = false;}
      if(lJEzZIdXUc == true){lJEzZIdXUc = false;}
      if(VSVXYiwVEt == true){VSVXYiwVEt = false;}
      if(mEAnXynKdV == true){mEAnXynKdV = false;}
      if(noNrWWonnG == true){noNrWWonnG = false;}
      if(lLUiEnGdEm == true){lLUiEnGdEm = false;}
      if(xrhwihIQaa == true){xrhwihIQaa = false;}
      if(UStyngFdAC == true){UStyngFdAC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCVKFRSMUG
{ 
  void hVDUgpuGox()
  { 
      bool rjbkiIdFBK = false;
      bool lEUNTnjyXQ = false;
      bool gujdAESGKc = false;
      bool mnJYwHUJMG = false;
      bool WqQnABQXmr = false;
      bool guIbExAykd = false;
      bool pXuYWxtuQL = false;
      bool TZlRsoducy = false;
      bool ntSSurfhTz = false;
      bool HWYhPzwqQD = false;
      bool HUGaYGJphP = false;
      bool SEVlpwEcce = false;
      bool QMbREwBDBt = false;
      bool smeZqSmrtn = false;
      bool hpzEfDBlrT = false;
      bool uSNkmtsoVb = false;
      bool FGonWfZwuW = false;
      bool IMioxaMWlB = false;
      bool uOLhzZYslw = false;
      bool ZyVRibALhA = false;
      string tmdykZsESp;
      string pEemtrmKKV;
      string QQEtDjwNdN;
      string gRhxUQgwMK;
      string lzNzmQCYaj;
      string SQPzbdhjuB;
      string dfaFJXWhRc;
      string KpyAiRDFHm;
      string gWlsuQCiUq;
      string hxALfGYHpO;
      string tTGxZbSOPK;
      string ZccITGsgKs;
      string VmMatNomUc;
      string ruPrrMQoTS;
      string xnSKQFUrqY;
      string NqxxsGGeCM;
      string lfsmReNjPG;
      string pENquhUCKo;
      string rxuuPBxSzl;
      string GklHgRtfrl;
      if(tmdykZsESp == tTGxZbSOPK){rjbkiIdFBK = true;}
      else if(tTGxZbSOPK == tmdykZsESp){HUGaYGJphP = true;}
      if(pEemtrmKKV == ZccITGsgKs){lEUNTnjyXQ = true;}
      else if(ZccITGsgKs == pEemtrmKKV){SEVlpwEcce = true;}
      if(QQEtDjwNdN == VmMatNomUc){gujdAESGKc = true;}
      else if(VmMatNomUc == QQEtDjwNdN){QMbREwBDBt = true;}
      if(gRhxUQgwMK == ruPrrMQoTS){mnJYwHUJMG = true;}
      else if(ruPrrMQoTS == gRhxUQgwMK){smeZqSmrtn = true;}
      if(lzNzmQCYaj == xnSKQFUrqY){WqQnABQXmr = true;}
      else if(xnSKQFUrqY == lzNzmQCYaj){hpzEfDBlrT = true;}
      if(SQPzbdhjuB == NqxxsGGeCM){guIbExAykd = true;}
      else if(NqxxsGGeCM == SQPzbdhjuB){uSNkmtsoVb = true;}
      if(dfaFJXWhRc == lfsmReNjPG){pXuYWxtuQL = true;}
      else if(lfsmReNjPG == dfaFJXWhRc){FGonWfZwuW = true;}
      if(KpyAiRDFHm == pENquhUCKo){TZlRsoducy = true;}
      if(gWlsuQCiUq == rxuuPBxSzl){ntSSurfhTz = true;}
      if(hxALfGYHpO == GklHgRtfrl){HWYhPzwqQD = true;}
      while(pENquhUCKo == KpyAiRDFHm){IMioxaMWlB = true;}
      while(rxuuPBxSzl == rxuuPBxSzl){uOLhzZYslw = true;}
      while(GklHgRtfrl == GklHgRtfrl){ZyVRibALhA = true;}
      if(rjbkiIdFBK == true){rjbkiIdFBK = false;}
      if(lEUNTnjyXQ == true){lEUNTnjyXQ = false;}
      if(gujdAESGKc == true){gujdAESGKc = false;}
      if(mnJYwHUJMG == true){mnJYwHUJMG = false;}
      if(WqQnABQXmr == true){WqQnABQXmr = false;}
      if(guIbExAykd == true){guIbExAykd = false;}
      if(pXuYWxtuQL == true){pXuYWxtuQL = false;}
      if(TZlRsoducy == true){TZlRsoducy = false;}
      if(ntSSurfhTz == true){ntSSurfhTz = false;}
      if(HWYhPzwqQD == true){HWYhPzwqQD = false;}
      if(HUGaYGJphP == true){HUGaYGJphP = false;}
      if(SEVlpwEcce == true){SEVlpwEcce = false;}
      if(QMbREwBDBt == true){QMbREwBDBt = false;}
      if(smeZqSmrtn == true){smeZqSmrtn = false;}
      if(hpzEfDBlrT == true){hpzEfDBlrT = false;}
      if(uSNkmtsoVb == true){uSNkmtsoVb = false;}
      if(FGonWfZwuW == true){FGonWfZwuW = false;}
      if(IMioxaMWlB == true){IMioxaMWlB = false;}
      if(uOLhzZYslw == true){uOLhzZYslw = false;}
      if(ZyVRibALhA == true){ZyVRibALhA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVFMOOGOMT
{ 
  void ghibsealft()
  { 
      bool sFRyuUdIGs = false;
      bool hCMAUYeoSB = false;
      bool DCsEOSfsbV = false;
      bool TPrRjFyahS = false;
      bool cRLONQHuWd = false;
      bool ztEohpMMib = false;
      bool nkfjYSJtQO = false;
      bool ZDHAYlqdqx = false;
      bool LkVxWYKDjt = false;
      bool slrFdqkbou = false;
      bool HMeHDumEQu = false;
      bool zhUlQDOiNA = false;
      bool HGJVVnLBVg = false;
      bool BOowpyFOsa = false;
      bool kGlnuKQGoa = false;
      bool cBNnmBCJlP = false;
      bool jlhjtjsYuR = false;
      bool xAolPATUZK = false;
      bool WELuEzAAIo = false;
      bool wwbcqyYCtL = false;
      string WpWzWXVikH;
      string boSoTHUJRm;
      string AMgGeIeUCB;
      string eiBFPSbDiy;
      string BFrRxahJXe;
      string mkydZKJPUN;
      string rAgjcrnNYB;
      string eQaSluUOJD;
      string ZUxXNsjWeF;
      string JMiUGAYIoE;
      string mUjWzWKfre;
      string ptFQnXDJVi;
      string HRiTrShGMk;
      string WMYEQFjaXq;
      string iEdzPOGRfh;
      string xPlGwUlQdg;
      string nETGIdVAAh;
      string mckdADmiEc;
      string LPZdnHZSHu;
      string TTwqCdjXpl;
      if(WpWzWXVikH == mUjWzWKfre){sFRyuUdIGs = true;}
      else if(mUjWzWKfre == WpWzWXVikH){HMeHDumEQu = true;}
      if(boSoTHUJRm == ptFQnXDJVi){hCMAUYeoSB = true;}
      else if(ptFQnXDJVi == boSoTHUJRm){zhUlQDOiNA = true;}
      if(AMgGeIeUCB == HRiTrShGMk){DCsEOSfsbV = true;}
      else if(HRiTrShGMk == AMgGeIeUCB){HGJVVnLBVg = true;}
      if(eiBFPSbDiy == WMYEQFjaXq){TPrRjFyahS = true;}
      else if(WMYEQFjaXq == eiBFPSbDiy){BOowpyFOsa = true;}
      if(BFrRxahJXe == iEdzPOGRfh){cRLONQHuWd = true;}
      else if(iEdzPOGRfh == BFrRxahJXe){kGlnuKQGoa = true;}
      if(mkydZKJPUN == xPlGwUlQdg){ztEohpMMib = true;}
      else if(xPlGwUlQdg == mkydZKJPUN){cBNnmBCJlP = true;}
      if(rAgjcrnNYB == nETGIdVAAh){nkfjYSJtQO = true;}
      else if(nETGIdVAAh == rAgjcrnNYB){jlhjtjsYuR = true;}
      if(eQaSluUOJD == mckdADmiEc){ZDHAYlqdqx = true;}
      if(ZUxXNsjWeF == LPZdnHZSHu){LkVxWYKDjt = true;}
      if(JMiUGAYIoE == TTwqCdjXpl){slrFdqkbou = true;}
      while(mckdADmiEc == eQaSluUOJD){xAolPATUZK = true;}
      while(LPZdnHZSHu == LPZdnHZSHu){WELuEzAAIo = true;}
      while(TTwqCdjXpl == TTwqCdjXpl){wwbcqyYCtL = true;}
      if(sFRyuUdIGs == true){sFRyuUdIGs = false;}
      if(hCMAUYeoSB == true){hCMAUYeoSB = false;}
      if(DCsEOSfsbV == true){DCsEOSfsbV = false;}
      if(TPrRjFyahS == true){TPrRjFyahS = false;}
      if(cRLONQHuWd == true){cRLONQHuWd = false;}
      if(ztEohpMMib == true){ztEohpMMib = false;}
      if(nkfjYSJtQO == true){nkfjYSJtQO = false;}
      if(ZDHAYlqdqx == true){ZDHAYlqdqx = false;}
      if(LkVxWYKDjt == true){LkVxWYKDjt = false;}
      if(slrFdqkbou == true){slrFdqkbou = false;}
      if(HMeHDumEQu == true){HMeHDumEQu = false;}
      if(zhUlQDOiNA == true){zhUlQDOiNA = false;}
      if(HGJVVnLBVg == true){HGJVVnLBVg = false;}
      if(BOowpyFOsa == true){BOowpyFOsa = false;}
      if(kGlnuKQGoa == true){kGlnuKQGoa = false;}
      if(cBNnmBCJlP == true){cBNnmBCJlP = false;}
      if(jlhjtjsYuR == true){jlhjtjsYuR = false;}
      if(xAolPATUZK == true){xAolPATUZK = false;}
      if(WELuEzAAIo == true){WELuEzAAIo = false;}
      if(wwbcqyYCtL == true){wwbcqyYCtL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDQGRJLRSV
{ 
  void UamzHIhwUB()
  { 
      bool REZXpkYCQJ = false;
      bool jIscKcWFFY = false;
      bool OCYrYkRLxf = false;
      bool QkteffVeoH = false;
      bool BWVJzuVRCu = false;
      bool QPqWiPfgzF = false;
      bool SMFjrzOOxd = false;
      bool GrPyXrfPsc = false;
      bool PAJBOBtWuP = false;
      bool zoejooQkQz = false;
      bool gHUYoYzrzp = false;
      bool iQnWpSDDVq = false;
      bool FqSgdRMfJh = false;
      bool auzsuHfjMo = false;
      bool BBXFgiBItV = false;
      bool lNPYtoomtX = false;
      bool MTiRPmQtah = false;
      bool mSqfoDTNAt = false;
      bool PEkmwNfZyG = false;
      bool SrpochRGps = false;
      string AsLYLCoQFj;
      string eLFpyAeujt;
      string BWmABluDyR;
      string JXzxCZOCIj;
      string UxftwFuYCN;
      string yRIPccFLXY;
      string HkRmaHLInX;
      string kbmzZEqrDu;
      string qVBjTrOjUY;
      string TDdicifrTn;
      string tmkebVdIoY;
      string lNHchkjgTh;
      string rbmODgxEWq;
      string YyXOBEkVHx;
      string NGtwlGwBBq;
      string yyYkwRzVau;
      string YZkyznorbc;
      string ANYVUlgpcx;
      string juCfrZYmSi;
      string EOuMYnUwwx;
      if(AsLYLCoQFj == tmkebVdIoY){REZXpkYCQJ = true;}
      else if(tmkebVdIoY == AsLYLCoQFj){gHUYoYzrzp = true;}
      if(eLFpyAeujt == lNHchkjgTh){jIscKcWFFY = true;}
      else if(lNHchkjgTh == eLFpyAeujt){iQnWpSDDVq = true;}
      if(BWmABluDyR == rbmODgxEWq){OCYrYkRLxf = true;}
      else if(rbmODgxEWq == BWmABluDyR){FqSgdRMfJh = true;}
      if(JXzxCZOCIj == YyXOBEkVHx){QkteffVeoH = true;}
      else if(YyXOBEkVHx == JXzxCZOCIj){auzsuHfjMo = true;}
      if(UxftwFuYCN == NGtwlGwBBq){BWVJzuVRCu = true;}
      else if(NGtwlGwBBq == UxftwFuYCN){BBXFgiBItV = true;}
      if(yRIPccFLXY == yyYkwRzVau){QPqWiPfgzF = true;}
      else if(yyYkwRzVau == yRIPccFLXY){lNPYtoomtX = true;}
      if(HkRmaHLInX == YZkyznorbc){SMFjrzOOxd = true;}
      else if(YZkyznorbc == HkRmaHLInX){MTiRPmQtah = true;}
      if(kbmzZEqrDu == ANYVUlgpcx){GrPyXrfPsc = true;}
      if(qVBjTrOjUY == juCfrZYmSi){PAJBOBtWuP = true;}
      if(TDdicifrTn == EOuMYnUwwx){zoejooQkQz = true;}
      while(ANYVUlgpcx == kbmzZEqrDu){mSqfoDTNAt = true;}
      while(juCfrZYmSi == juCfrZYmSi){PEkmwNfZyG = true;}
      while(EOuMYnUwwx == EOuMYnUwwx){SrpochRGps = true;}
      if(REZXpkYCQJ == true){REZXpkYCQJ = false;}
      if(jIscKcWFFY == true){jIscKcWFFY = false;}
      if(OCYrYkRLxf == true){OCYrYkRLxf = false;}
      if(QkteffVeoH == true){QkteffVeoH = false;}
      if(BWVJzuVRCu == true){BWVJzuVRCu = false;}
      if(QPqWiPfgzF == true){QPqWiPfgzF = false;}
      if(SMFjrzOOxd == true){SMFjrzOOxd = false;}
      if(GrPyXrfPsc == true){GrPyXrfPsc = false;}
      if(PAJBOBtWuP == true){PAJBOBtWuP = false;}
      if(zoejooQkQz == true){zoejooQkQz = false;}
      if(gHUYoYzrzp == true){gHUYoYzrzp = false;}
      if(iQnWpSDDVq == true){iQnWpSDDVq = false;}
      if(FqSgdRMfJh == true){FqSgdRMfJh = false;}
      if(auzsuHfjMo == true){auzsuHfjMo = false;}
      if(BBXFgiBItV == true){BBXFgiBItV = false;}
      if(lNPYtoomtX == true){lNPYtoomtX = false;}
      if(MTiRPmQtah == true){MTiRPmQtah = false;}
      if(mSqfoDTNAt == true){mSqfoDTNAt = false;}
      if(PEkmwNfZyG == true){PEkmwNfZyG = false;}
      if(SrpochRGps == true){SrpochRGps = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXOBHVHLAM
{ 
  void sYmLFquDJu()
  { 
      bool RHoKJyfGEg = false;
      bool NgFQeMDFaQ = false;
      bool KrKTQMsoSj = false;
      bool ZscwsKnWpg = false;
      bool pMhIOCkOdp = false;
      bool igbPfZxVtw = false;
      bool EpmUHTDIWT = false;
      bool YfPsZyJBEN = false;
      bool bdLcAsRNPT = false;
      bool MRbsczYNBt = false;
      bool zbqJRDQhoh = false;
      bool PwQgUZeKTN = false;
      bool CosDHGDWQZ = false;
      bool ZwzKNzmBLx = false;
      bool biYhDQBuXC = false;
      bool UNsmqKimCK = false;
      bool ztROHTwGSV = false;
      bool mdzWlTQKAp = false;
      bool FIyOFLCMSD = false;
      bool PzyAxhQJZi = false;
      string raYXMNBEmI;
      string OOPEJjffro;
      string BiACounZVd;
      string KwnfDNPACa;
      string fQySRoCDgr;
      string iIjTXJZVhR;
      string YahIxRZjBw;
      string UfdQJjjhkA;
      string rksduCMTHs;
      string nsRjCFioUA;
      string OSBkXDeTKn;
      string YqkgZnhENt;
      string FFcIIaNsND;
      string BuMklZjIFr;
      string XrJSUwIkKN;
      string XdbatJpscx;
      string okFGmddAuz;
      string EYyVWMwJmL;
      string SchzfWSlpb;
      string iqfIClmCfq;
      if(raYXMNBEmI == OSBkXDeTKn){RHoKJyfGEg = true;}
      else if(OSBkXDeTKn == raYXMNBEmI){zbqJRDQhoh = true;}
      if(OOPEJjffro == YqkgZnhENt){NgFQeMDFaQ = true;}
      else if(YqkgZnhENt == OOPEJjffro){PwQgUZeKTN = true;}
      if(BiACounZVd == FFcIIaNsND){KrKTQMsoSj = true;}
      else if(FFcIIaNsND == BiACounZVd){CosDHGDWQZ = true;}
      if(KwnfDNPACa == BuMklZjIFr){ZscwsKnWpg = true;}
      else if(BuMklZjIFr == KwnfDNPACa){ZwzKNzmBLx = true;}
      if(fQySRoCDgr == XrJSUwIkKN){pMhIOCkOdp = true;}
      else if(XrJSUwIkKN == fQySRoCDgr){biYhDQBuXC = true;}
      if(iIjTXJZVhR == XdbatJpscx){igbPfZxVtw = true;}
      else if(XdbatJpscx == iIjTXJZVhR){UNsmqKimCK = true;}
      if(YahIxRZjBw == okFGmddAuz){EpmUHTDIWT = true;}
      else if(okFGmddAuz == YahIxRZjBw){ztROHTwGSV = true;}
      if(UfdQJjjhkA == EYyVWMwJmL){YfPsZyJBEN = true;}
      if(rksduCMTHs == SchzfWSlpb){bdLcAsRNPT = true;}
      if(nsRjCFioUA == iqfIClmCfq){MRbsczYNBt = true;}
      while(EYyVWMwJmL == UfdQJjjhkA){mdzWlTQKAp = true;}
      while(SchzfWSlpb == SchzfWSlpb){FIyOFLCMSD = true;}
      while(iqfIClmCfq == iqfIClmCfq){PzyAxhQJZi = true;}
      if(RHoKJyfGEg == true){RHoKJyfGEg = false;}
      if(NgFQeMDFaQ == true){NgFQeMDFaQ = false;}
      if(KrKTQMsoSj == true){KrKTQMsoSj = false;}
      if(ZscwsKnWpg == true){ZscwsKnWpg = false;}
      if(pMhIOCkOdp == true){pMhIOCkOdp = false;}
      if(igbPfZxVtw == true){igbPfZxVtw = false;}
      if(EpmUHTDIWT == true){EpmUHTDIWT = false;}
      if(YfPsZyJBEN == true){YfPsZyJBEN = false;}
      if(bdLcAsRNPT == true){bdLcAsRNPT = false;}
      if(MRbsczYNBt == true){MRbsczYNBt = false;}
      if(zbqJRDQhoh == true){zbqJRDQhoh = false;}
      if(PwQgUZeKTN == true){PwQgUZeKTN = false;}
      if(CosDHGDWQZ == true){CosDHGDWQZ = false;}
      if(ZwzKNzmBLx == true){ZwzKNzmBLx = false;}
      if(biYhDQBuXC == true){biYhDQBuXC = false;}
      if(UNsmqKimCK == true){UNsmqKimCK = false;}
      if(ztROHTwGSV == true){ztROHTwGSV = false;}
      if(mdzWlTQKAp == true){mdzWlTQKAp = false;}
      if(FIyOFLCMSD == true){FIyOFLCMSD = false;}
      if(PzyAxhQJZi == true){PzyAxhQJZi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRVKSZYZZV
{ 
  void HyfXWHhuyn()
  { 
      bool iORNjyHOjI = false;
      bool WGTUPNYQgO = false;
      bool GQMOkygDAK = false;
      bool HbIefimIfY = false;
      bool uMhqiwjrGM = false;
      bool CYYjASCCck = false;
      bool RENYBtxong = false;
      bool ZQjHSsiUfn = false;
      bool OnwmIiCXeN = false;
      bool fkftHqyIpn = false;
      bool ztEZmlnRRG = false;
      bool igWoWcHaPS = false;
      bool qYKaAojoAb = false;
      bool uZeqoUjWAV = false;
      bool tkGXdzOqXd = false;
      bool jXrXwZjcYx = false;
      bool BzQoLJBeAC = false;
      bool sjZtXGRlwB = false;
      bool asQVqWgHtO = false;
      bool jGxCUuTQMT = false;
      string njedphyWzk;
      string XYsZuOYxEj;
      string LMufkgfujZ;
      string mwyBNbsMRB;
      string kfjbBYcqiK;
      string VynShanysJ;
      string BClYxbZqLT;
      string ULfDyebSeL;
      string DoMZEoHfSl;
      string muTHzitKeY;
      string zlePoKSkUC;
      string yVSgFMpLUI;
      string TtXYfZrXDP;
      string kRnFLRJwks;
      string VWKQnQbmBm;
      string rhpVFFNFiO;
      string StgERghMUn;
      string CtaalwiHkO;
      string yEVQXDaRAF;
      string DDMWaaoGyG;
      if(njedphyWzk == zlePoKSkUC){iORNjyHOjI = true;}
      else if(zlePoKSkUC == njedphyWzk){ztEZmlnRRG = true;}
      if(XYsZuOYxEj == yVSgFMpLUI){WGTUPNYQgO = true;}
      else if(yVSgFMpLUI == XYsZuOYxEj){igWoWcHaPS = true;}
      if(LMufkgfujZ == TtXYfZrXDP){GQMOkygDAK = true;}
      else if(TtXYfZrXDP == LMufkgfujZ){qYKaAojoAb = true;}
      if(mwyBNbsMRB == kRnFLRJwks){HbIefimIfY = true;}
      else if(kRnFLRJwks == mwyBNbsMRB){uZeqoUjWAV = true;}
      if(kfjbBYcqiK == VWKQnQbmBm){uMhqiwjrGM = true;}
      else if(VWKQnQbmBm == kfjbBYcqiK){tkGXdzOqXd = true;}
      if(VynShanysJ == rhpVFFNFiO){CYYjASCCck = true;}
      else if(rhpVFFNFiO == VynShanysJ){jXrXwZjcYx = true;}
      if(BClYxbZqLT == StgERghMUn){RENYBtxong = true;}
      else if(StgERghMUn == BClYxbZqLT){BzQoLJBeAC = true;}
      if(ULfDyebSeL == CtaalwiHkO){ZQjHSsiUfn = true;}
      if(DoMZEoHfSl == yEVQXDaRAF){OnwmIiCXeN = true;}
      if(muTHzitKeY == DDMWaaoGyG){fkftHqyIpn = true;}
      while(CtaalwiHkO == ULfDyebSeL){sjZtXGRlwB = true;}
      while(yEVQXDaRAF == yEVQXDaRAF){asQVqWgHtO = true;}
      while(DDMWaaoGyG == DDMWaaoGyG){jGxCUuTQMT = true;}
      if(iORNjyHOjI == true){iORNjyHOjI = false;}
      if(WGTUPNYQgO == true){WGTUPNYQgO = false;}
      if(GQMOkygDAK == true){GQMOkygDAK = false;}
      if(HbIefimIfY == true){HbIefimIfY = false;}
      if(uMhqiwjrGM == true){uMhqiwjrGM = false;}
      if(CYYjASCCck == true){CYYjASCCck = false;}
      if(RENYBtxong == true){RENYBtxong = false;}
      if(ZQjHSsiUfn == true){ZQjHSsiUfn = false;}
      if(OnwmIiCXeN == true){OnwmIiCXeN = false;}
      if(fkftHqyIpn == true){fkftHqyIpn = false;}
      if(ztEZmlnRRG == true){ztEZmlnRRG = false;}
      if(igWoWcHaPS == true){igWoWcHaPS = false;}
      if(qYKaAojoAb == true){qYKaAojoAb = false;}
      if(uZeqoUjWAV == true){uZeqoUjWAV = false;}
      if(tkGXdzOqXd == true){tkGXdzOqXd = false;}
      if(jXrXwZjcYx == true){jXrXwZjcYx = false;}
      if(BzQoLJBeAC == true){BzQoLJBeAC = false;}
      if(sjZtXGRlwB == true){sjZtXGRlwB = false;}
      if(asQVqWgHtO == true){asQVqWgHtO = false;}
      if(jGxCUuTQMT == true){jGxCUuTQMT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKRIYAYLWK
{ 
  void fXQhoVOFjY()
  { 
      bool zacMftPCHm = false;
      bool hsFQflAkmp = false;
      bool munhiFOLbw = false;
      bool aqBrqbDsMj = false;
      bool dGdAwryQZY = false;
      bool frhMzEluda = false;
      bool eEZKMprMZE = false;
      bool hGXDLgQnkq = false;
      bool GxkCQhInsm = false;
      bool oIPlEZfTmF = false;
      bool zkqVpYUeBR = false;
      bool nyJlUgTXtd = false;
      bool hDTmPZplyk = false;
      bool AwAfqUGOLq = false;
      bool MdmayqydRX = false;
      bool FIZJXwREFQ = false;
      bool iifPQqxdtz = false;
      bool aELCQDQsnX = false;
      bool aMUafrWqHu = false;
      bool DBIuIdxXJG = false;
      string yEAoYPUWhJ;
      string chadTIZino;
      string AubNjAgKhz;
      string HyKiiLteJU;
      string ofoDgRetnC;
      string iWflhDblEY;
      string iKnhBdXquH;
      string NuZTzUGXgS;
      string VlWeQkSXAf;
      string jIZkkeqHBC;
      string smyfomwLlN;
      string wDFkCwmIQQ;
      string LzpOXFUohU;
      string czWdYhnppc;
      string nHlmjfCoho;
      string qhpjqtwjIi;
      string RHdQjxgbLU;
      string IxRmcEMDeq;
      string CfGsdtJlmd;
      string kDhGLfcUCm;
      if(yEAoYPUWhJ == smyfomwLlN){zacMftPCHm = true;}
      else if(smyfomwLlN == yEAoYPUWhJ){zkqVpYUeBR = true;}
      if(chadTIZino == wDFkCwmIQQ){hsFQflAkmp = true;}
      else if(wDFkCwmIQQ == chadTIZino){nyJlUgTXtd = true;}
      if(AubNjAgKhz == LzpOXFUohU){munhiFOLbw = true;}
      else if(LzpOXFUohU == AubNjAgKhz){hDTmPZplyk = true;}
      if(HyKiiLteJU == czWdYhnppc){aqBrqbDsMj = true;}
      else if(czWdYhnppc == HyKiiLteJU){AwAfqUGOLq = true;}
      if(ofoDgRetnC == nHlmjfCoho){dGdAwryQZY = true;}
      else if(nHlmjfCoho == ofoDgRetnC){MdmayqydRX = true;}
      if(iWflhDblEY == qhpjqtwjIi){frhMzEluda = true;}
      else if(qhpjqtwjIi == iWflhDblEY){FIZJXwREFQ = true;}
      if(iKnhBdXquH == RHdQjxgbLU){eEZKMprMZE = true;}
      else if(RHdQjxgbLU == iKnhBdXquH){iifPQqxdtz = true;}
      if(NuZTzUGXgS == IxRmcEMDeq){hGXDLgQnkq = true;}
      if(VlWeQkSXAf == CfGsdtJlmd){GxkCQhInsm = true;}
      if(jIZkkeqHBC == kDhGLfcUCm){oIPlEZfTmF = true;}
      while(IxRmcEMDeq == NuZTzUGXgS){aELCQDQsnX = true;}
      while(CfGsdtJlmd == CfGsdtJlmd){aMUafrWqHu = true;}
      while(kDhGLfcUCm == kDhGLfcUCm){DBIuIdxXJG = true;}
      if(zacMftPCHm == true){zacMftPCHm = false;}
      if(hsFQflAkmp == true){hsFQflAkmp = false;}
      if(munhiFOLbw == true){munhiFOLbw = false;}
      if(aqBrqbDsMj == true){aqBrqbDsMj = false;}
      if(dGdAwryQZY == true){dGdAwryQZY = false;}
      if(frhMzEluda == true){frhMzEluda = false;}
      if(eEZKMprMZE == true){eEZKMprMZE = false;}
      if(hGXDLgQnkq == true){hGXDLgQnkq = false;}
      if(GxkCQhInsm == true){GxkCQhInsm = false;}
      if(oIPlEZfTmF == true){oIPlEZfTmF = false;}
      if(zkqVpYUeBR == true){zkqVpYUeBR = false;}
      if(nyJlUgTXtd == true){nyJlUgTXtd = false;}
      if(hDTmPZplyk == true){hDTmPZplyk = false;}
      if(AwAfqUGOLq == true){AwAfqUGOLq = false;}
      if(MdmayqydRX == true){MdmayqydRX = false;}
      if(FIZJXwREFQ == true){FIZJXwREFQ = false;}
      if(iifPQqxdtz == true){iifPQqxdtz = false;}
      if(aELCQDQsnX == true){aELCQDQsnX = false;}
      if(aMUafrWqHu == true){aMUafrWqHu = false;}
      if(DBIuIdxXJG == true){DBIuIdxXJG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJSMAZCIYW
{ 
  void eRWWXQXESy()
  { 
      bool anlQVuMKxJ = false;
      bool RCJdRcdsEh = false;
      bool ZZYdKLaAwK = false;
      bool foAhtnWGsw = false;
      bool LiSaLJzmAi = false;
      bool jVczKBOHFK = false;
      bool TMNmdbBbic = false;
      bool FWAIWpHySB = false;
      bool LnzNZKLAWs = false;
      bool YPAhbyVexi = false;
      bool HXDXdNVUcT = false;
      bool tQoEyfNANT = false;
      bool PAEpEpVRfX = false;
      bool UbBjsnjbjL = false;
      bool nqXDzHZujw = false;
      bool kURcSHTNSn = false;
      bool qEnEzRPFLK = false;
      bool ukPBeYbBpw = false;
      bool PZgjlAJXQl = false;
      bool UWIwUiDSEg = false;
      string JwEuJslggX;
      string FXuFzjUwyq;
      string guWpLkxXWr;
      string HCNXxSLBet;
      string MTMZaBfISq;
      string GeRGXNYOiX;
      string wOJoQDJXHf;
      string XTREdNiwOK;
      string EnEekbjHzj;
      string sxRGyyJWJX;
      string rIBlTmMNbK;
      string eczYSHKdEn;
      string SCXXmZBLFf;
      string DLlpSwmRLx;
      string PWeoEQxrmp;
      string neRVFokczs;
      string lBHwGTpJGW;
      string UrSHXuXiSV;
      string bJXOqYsQkc;
      string LJRRLNOhhk;
      if(JwEuJslggX == rIBlTmMNbK){anlQVuMKxJ = true;}
      else if(rIBlTmMNbK == JwEuJslggX){HXDXdNVUcT = true;}
      if(FXuFzjUwyq == eczYSHKdEn){RCJdRcdsEh = true;}
      else if(eczYSHKdEn == FXuFzjUwyq){tQoEyfNANT = true;}
      if(guWpLkxXWr == SCXXmZBLFf){ZZYdKLaAwK = true;}
      else if(SCXXmZBLFf == guWpLkxXWr){PAEpEpVRfX = true;}
      if(HCNXxSLBet == DLlpSwmRLx){foAhtnWGsw = true;}
      else if(DLlpSwmRLx == HCNXxSLBet){UbBjsnjbjL = true;}
      if(MTMZaBfISq == PWeoEQxrmp){LiSaLJzmAi = true;}
      else if(PWeoEQxrmp == MTMZaBfISq){nqXDzHZujw = true;}
      if(GeRGXNYOiX == neRVFokczs){jVczKBOHFK = true;}
      else if(neRVFokczs == GeRGXNYOiX){kURcSHTNSn = true;}
      if(wOJoQDJXHf == lBHwGTpJGW){TMNmdbBbic = true;}
      else if(lBHwGTpJGW == wOJoQDJXHf){qEnEzRPFLK = true;}
      if(XTREdNiwOK == UrSHXuXiSV){FWAIWpHySB = true;}
      if(EnEekbjHzj == bJXOqYsQkc){LnzNZKLAWs = true;}
      if(sxRGyyJWJX == LJRRLNOhhk){YPAhbyVexi = true;}
      while(UrSHXuXiSV == XTREdNiwOK){ukPBeYbBpw = true;}
      while(bJXOqYsQkc == bJXOqYsQkc){PZgjlAJXQl = true;}
      while(LJRRLNOhhk == LJRRLNOhhk){UWIwUiDSEg = true;}
      if(anlQVuMKxJ == true){anlQVuMKxJ = false;}
      if(RCJdRcdsEh == true){RCJdRcdsEh = false;}
      if(ZZYdKLaAwK == true){ZZYdKLaAwK = false;}
      if(foAhtnWGsw == true){foAhtnWGsw = false;}
      if(LiSaLJzmAi == true){LiSaLJzmAi = false;}
      if(jVczKBOHFK == true){jVczKBOHFK = false;}
      if(TMNmdbBbic == true){TMNmdbBbic = false;}
      if(FWAIWpHySB == true){FWAIWpHySB = false;}
      if(LnzNZKLAWs == true){LnzNZKLAWs = false;}
      if(YPAhbyVexi == true){YPAhbyVexi = false;}
      if(HXDXdNVUcT == true){HXDXdNVUcT = false;}
      if(tQoEyfNANT == true){tQoEyfNANT = false;}
      if(PAEpEpVRfX == true){PAEpEpVRfX = false;}
      if(UbBjsnjbjL == true){UbBjsnjbjL = false;}
      if(nqXDzHZujw == true){nqXDzHZujw = false;}
      if(kURcSHTNSn == true){kURcSHTNSn = false;}
      if(qEnEzRPFLK == true){qEnEzRPFLK = false;}
      if(ukPBeYbBpw == true){ukPBeYbBpw = false;}
      if(PZgjlAJXQl == true){PZgjlAJXQl = false;}
      if(UWIwUiDSEg == true){UWIwUiDSEg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUQDTUYTCI
{ 
  void soBaQbHFGP()
  { 
      bool ScoMkUntFN = false;
      bool FxnSKWbURX = false;
      bool dIlBWKARyV = false;
      bool pZiFIjJtUo = false;
      bool opmCKFnZcp = false;
      bool jZammJpnpZ = false;
      bool UWwjXfOiKa = false;
      bool NgAcinUiqR = false;
      bool WZnHkPyuRy = false;
      bool sUEuTRsDed = false;
      bool pFPBcDZyEz = false;
      bool oGwYCuhnyH = false;
      bool gTQLgrcFIQ = false;
      bool tQEMaRKleh = false;
      bool pApSJlYerY = false;
      bool jFEXxVnDUj = false;
      bool ZUomEXCixk = false;
      bool kuIQRfcyCt = false;
      bool TyMjgoLfPE = false;
      bool dGRuHUKCNk = false;
      string LymawegiTJ;
      string iBdcgbmWFa;
      string mJTBUhCUmJ;
      string FFqmnhjSUb;
      string GFNVhVoBpJ;
      string wegUDCelFN;
      string bLuJEdJpnz;
      string rTBcTguxTz;
      string sAedMZXVil;
      string CyNHzuKDRE;
      string LyMqRcdDBW;
      string GhSFUagQwd;
      string FmGCwsGtdY;
      string VqfPntmnLj;
      string wUUMfUfHmX;
      string OsHmyXrKtX;
      string ViZbAOBDRZ;
      string msFMhkStWb;
      string NzHFKcjsQP;
      string CcsnNMtrLQ;
      if(LymawegiTJ == LyMqRcdDBW){ScoMkUntFN = true;}
      else if(LyMqRcdDBW == LymawegiTJ){pFPBcDZyEz = true;}
      if(iBdcgbmWFa == GhSFUagQwd){FxnSKWbURX = true;}
      else if(GhSFUagQwd == iBdcgbmWFa){oGwYCuhnyH = true;}
      if(mJTBUhCUmJ == FmGCwsGtdY){dIlBWKARyV = true;}
      else if(FmGCwsGtdY == mJTBUhCUmJ){gTQLgrcFIQ = true;}
      if(FFqmnhjSUb == VqfPntmnLj){pZiFIjJtUo = true;}
      else if(VqfPntmnLj == FFqmnhjSUb){tQEMaRKleh = true;}
      if(GFNVhVoBpJ == wUUMfUfHmX){opmCKFnZcp = true;}
      else if(wUUMfUfHmX == GFNVhVoBpJ){pApSJlYerY = true;}
      if(wegUDCelFN == OsHmyXrKtX){jZammJpnpZ = true;}
      else if(OsHmyXrKtX == wegUDCelFN){jFEXxVnDUj = true;}
      if(bLuJEdJpnz == ViZbAOBDRZ){UWwjXfOiKa = true;}
      else if(ViZbAOBDRZ == bLuJEdJpnz){ZUomEXCixk = true;}
      if(rTBcTguxTz == msFMhkStWb){NgAcinUiqR = true;}
      if(sAedMZXVil == NzHFKcjsQP){WZnHkPyuRy = true;}
      if(CyNHzuKDRE == CcsnNMtrLQ){sUEuTRsDed = true;}
      while(msFMhkStWb == rTBcTguxTz){kuIQRfcyCt = true;}
      while(NzHFKcjsQP == NzHFKcjsQP){TyMjgoLfPE = true;}
      while(CcsnNMtrLQ == CcsnNMtrLQ){dGRuHUKCNk = true;}
      if(ScoMkUntFN == true){ScoMkUntFN = false;}
      if(FxnSKWbURX == true){FxnSKWbURX = false;}
      if(dIlBWKARyV == true){dIlBWKARyV = false;}
      if(pZiFIjJtUo == true){pZiFIjJtUo = false;}
      if(opmCKFnZcp == true){opmCKFnZcp = false;}
      if(jZammJpnpZ == true){jZammJpnpZ = false;}
      if(UWwjXfOiKa == true){UWwjXfOiKa = false;}
      if(NgAcinUiqR == true){NgAcinUiqR = false;}
      if(WZnHkPyuRy == true){WZnHkPyuRy = false;}
      if(sUEuTRsDed == true){sUEuTRsDed = false;}
      if(pFPBcDZyEz == true){pFPBcDZyEz = false;}
      if(oGwYCuhnyH == true){oGwYCuhnyH = false;}
      if(gTQLgrcFIQ == true){gTQLgrcFIQ = false;}
      if(tQEMaRKleh == true){tQEMaRKleh = false;}
      if(pApSJlYerY == true){pApSJlYerY = false;}
      if(jFEXxVnDUj == true){jFEXxVnDUj = false;}
      if(ZUomEXCixk == true){ZUomEXCixk = false;}
      if(kuIQRfcyCt == true){kuIQRfcyCt = false;}
      if(TyMjgoLfPE == true){TyMjgoLfPE = false;}
      if(dGRuHUKCNk == true){dGRuHUKCNk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZZHDVEQJT
{ 
  void jPDReblzHD()
  { 
      bool kNzuCZFgMF = false;
      bool JemFrCifbS = false;
      bool gNJIojsIWy = false;
      bool InyaKqLekP = false;
      bool pMVdJpVKhh = false;
      bool YWiidXEpFS = false;
      bool fxKNwVfMuA = false;
      bool pEtMcUqezy = false;
      bool OhZnYkEOwl = false;
      bool lVYSirBHgm = false;
      bool JIPgqUcVGJ = false;
      bool gYqHExWVoL = false;
      bool QRPIOUebdj = false;
      bool SiyLnFRrxD = false;
      bool IhImEMdRNk = false;
      bool UfSVVrsHSV = false;
      bool pArWpxaeSz = false;
      bool eeXkCiIcDB = false;
      bool qNNrOmQbow = false;
      bool LKYbNIplwH = false;
      string LKFYfWDugZ;
      string BmZCcIeTzO;
      string QbSLAYIgGZ;
      string sqpsfUuHXn;
      string gkAYKibWkX;
      string ZlOXdjqtXH;
      string OWoGgKwfVH;
      string NXwKhfatAR;
      string wkuhAHbSPu;
      string dAiQZKusrz;
      string mwBdKCoEoy;
      string IxsGKcaGFY;
      string icQZcMnfjX;
      string jhBAdAjQXy;
      string RWcQmgHcFw;
      string innSQJeaBx;
      string NJTROauscK;
      string sJiGGLzAmu;
      string FLZnoushiT;
      string UJPajIDLCL;
      if(LKFYfWDugZ == mwBdKCoEoy){kNzuCZFgMF = true;}
      else if(mwBdKCoEoy == LKFYfWDugZ){JIPgqUcVGJ = true;}
      if(BmZCcIeTzO == IxsGKcaGFY){JemFrCifbS = true;}
      else if(IxsGKcaGFY == BmZCcIeTzO){gYqHExWVoL = true;}
      if(QbSLAYIgGZ == icQZcMnfjX){gNJIojsIWy = true;}
      else if(icQZcMnfjX == QbSLAYIgGZ){QRPIOUebdj = true;}
      if(sqpsfUuHXn == jhBAdAjQXy){InyaKqLekP = true;}
      else if(jhBAdAjQXy == sqpsfUuHXn){SiyLnFRrxD = true;}
      if(gkAYKibWkX == RWcQmgHcFw){pMVdJpVKhh = true;}
      else if(RWcQmgHcFw == gkAYKibWkX){IhImEMdRNk = true;}
      if(ZlOXdjqtXH == innSQJeaBx){YWiidXEpFS = true;}
      else if(innSQJeaBx == ZlOXdjqtXH){UfSVVrsHSV = true;}
      if(OWoGgKwfVH == NJTROauscK){fxKNwVfMuA = true;}
      else if(NJTROauscK == OWoGgKwfVH){pArWpxaeSz = true;}
      if(NXwKhfatAR == sJiGGLzAmu){pEtMcUqezy = true;}
      if(wkuhAHbSPu == FLZnoushiT){OhZnYkEOwl = true;}
      if(dAiQZKusrz == UJPajIDLCL){lVYSirBHgm = true;}
      while(sJiGGLzAmu == NXwKhfatAR){eeXkCiIcDB = true;}
      while(FLZnoushiT == FLZnoushiT){qNNrOmQbow = true;}
      while(UJPajIDLCL == UJPajIDLCL){LKYbNIplwH = true;}
      if(kNzuCZFgMF == true){kNzuCZFgMF = false;}
      if(JemFrCifbS == true){JemFrCifbS = false;}
      if(gNJIojsIWy == true){gNJIojsIWy = false;}
      if(InyaKqLekP == true){InyaKqLekP = false;}
      if(pMVdJpVKhh == true){pMVdJpVKhh = false;}
      if(YWiidXEpFS == true){YWiidXEpFS = false;}
      if(fxKNwVfMuA == true){fxKNwVfMuA = false;}
      if(pEtMcUqezy == true){pEtMcUqezy = false;}
      if(OhZnYkEOwl == true){OhZnYkEOwl = false;}
      if(lVYSirBHgm == true){lVYSirBHgm = false;}
      if(JIPgqUcVGJ == true){JIPgqUcVGJ = false;}
      if(gYqHExWVoL == true){gYqHExWVoL = false;}
      if(QRPIOUebdj == true){QRPIOUebdj = false;}
      if(SiyLnFRrxD == true){SiyLnFRrxD = false;}
      if(IhImEMdRNk == true){IhImEMdRNk = false;}
      if(UfSVVrsHSV == true){UfSVVrsHSV = false;}
      if(pArWpxaeSz == true){pArWpxaeSz = false;}
      if(eeXkCiIcDB == true){eeXkCiIcDB = false;}
      if(qNNrOmQbow == true){qNNrOmQbow = false;}
      if(LKYbNIplwH == true){LKYbNIplwH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANHEHCBCBN
{ 
  void BKaaWrqDbW()
  { 
      bool mGAGUIkAGS = false;
      bool MbGqxULeVT = false;
      bool lyOrxiqVwX = false;
      bool ubHjKUxKNB = false;
      bool WkooDgekpi = false;
      bool nsSkPoqHJl = false;
      bool QPDhWkTVfb = false;
      bool WBQUxAIYoP = false;
      bool EGeNiCJWTV = false;
      bool cpAbjGhGRS = false;
      bool MIENLmbymP = false;
      bool fRStgKjpyU = false;
      bool bxBJyfAojq = false;
      bool RBHVCuBRBw = false;
      bool aKiEpKXGtY = false;
      bool WrIxqPGtOf = false;
      bool llNwxdKwql = false;
      bool JSnCtQOwTm = false;
      bool IttKTZsJem = false;
      bool nGCVJnwlHL = false;
      string UBILSFykQY;
      string yWdyHtABYY;
      string HBZGxecfUw;
      string mUzSDcudFO;
      string bjqRUluxxc;
      string yCwNETbBOn;
      string bRPTkdWKte;
      string yWuKwXJHkK;
      string ieirxjXlOj;
      string AsORlKTWfq;
      string PkCSdaGlRf;
      string KUQEExiXWB;
      string FkuKdEIdXk;
      string DlasuycPNW;
      string clUhYfcJMo;
      string awAeldoqnY;
      string ScNfbXsWJF;
      string TSKAYTQNkx;
      string byQiJHluHQ;
      string IkbnDAXnFB;
      if(UBILSFykQY == PkCSdaGlRf){mGAGUIkAGS = true;}
      else if(PkCSdaGlRf == UBILSFykQY){MIENLmbymP = true;}
      if(yWdyHtABYY == KUQEExiXWB){MbGqxULeVT = true;}
      else if(KUQEExiXWB == yWdyHtABYY){fRStgKjpyU = true;}
      if(HBZGxecfUw == FkuKdEIdXk){lyOrxiqVwX = true;}
      else if(FkuKdEIdXk == HBZGxecfUw){bxBJyfAojq = true;}
      if(mUzSDcudFO == DlasuycPNW){ubHjKUxKNB = true;}
      else if(DlasuycPNW == mUzSDcudFO){RBHVCuBRBw = true;}
      if(bjqRUluxxc == clUhYfcJMo){WkooDgekpi = true;}
      else if(clUhYfcJMo == bjqRUluxxc){aKiEpKXGtY = true;}
      if(yCwNETbBOn == awAeldoqnY){nsSkPoqHJl = true;}
      else if(awAeldoqnY == yCwNETbBOn){WrIxqPGtOf = true;}
      if(bRPTkdWKte == ScNfbXsWJF){QPDhWkTVfb = true;}
      else if(ScNfbXsWJF == bRPTkdWKte){llNwxdKwql = true;}
      if(yWuKwXJHkK == TSKAYTQNkx){WBQUxAIYoP = true;}
      if(ieirxjXlOj == byQiJHluHQ){EGeNiCJWTV = true;}
      if(AsORlKTWfq == IkbnDAXnFB){cpAbjGhGRS = true;}
      while(TSKAYTQNkx == yWuKwXJHkK){JSnCtQOwTm = true;}
      while(byQiJHluHQ == byQiJHluHQ){IttKTZsJem = true;}
      while(IkbnDAXnFB == IkbnDAXnFB){nGCVJnwlHL = true;}
      if(mGAGUIkAGS == true){mGAGUIkAGS = false;}
      if(MbGqxULeVT == true){MbGqxULeVT = false;}
      if(lyOrxiqVwX == true){lyOrxiqVwX = false;}
      if(ubHjKUxKNB == true){ubHjKUxKNB = false;}
      if(WkooDgekpi == true){WkooDgekpi = false;}
      if(nsSkPoqHJl == true){nsSkPoqHJl = false;}
      if(QPDhWkTVfb == true){QPDhWkTVfb = false;}
      if(WBQUxAIYoP == true){WBQUxAIYoP = false;}
      if(EGeNiCJWTV == true){EGeNiCJWTV = false;}
      if(cpAbjGhGRS == true){cpAbjGhGRS = false;}
      if(MIENLmbymP == true){MIENLmbymP = false;}
      if(fRStgKjpyU == true){fRStgKjpyU = false;}
      if(bxBJyfAojq == true){bxBJyfAojq = false;}
      if(RBHVCuBRBw == true){RBHVCuBRBw = false;}
      if(aKiEpKXGtY == true){aKiEpKXGtY = false;}
      if(WrIxqPGtOf == true){WrIxqPGtOf = false;}
      if(llNwxdKwql == true){llNwxdKwql = false;}
      if(JSnCtQOwTm == true){JSnCtQOwTm = false;}
      if(IttKTZsJem == true){IttKTZsJem = false;}
      if(nGCVJnwlHL == true){nGCVJnwlHL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABSMOAQWNR
{ 
  void inDzDWAdqj()
  { 
      bool dSilAanTTK = false;
      bool MJisgxqAbl = false;
      bool SOeCLyMhOO = false;
      bool aAzMpfMdLA = false;
      bool slHxIbMrfE = false;
      bool nIqOgOmfZB = false;
      bool OGFEiMJVDA = false;
      bool kMobsgGhsi = false;
      bool lTCKZRJjea = false;
      bool rfDJllfDNw = false;
      bool SpoeTbTPVA = false;
      bool HFmqPtEudR = false;
      bool DYpbIEIfoG = false;
      bool ADUxPueWpy = false;
      bool ysOeSlsMsr = false;
      bool hkYusszMVO = false;
      bool TmaPzEkpaT = false;
      bool OgEeTJKLIV = false;
      bool LwmwXPdYDV = false;
      bool uSBbeKSyeO = false;
      string qZxhJAlbaE;
      string qYHVDpacfq;
      string XmICalmnMX;
      string cuDesQopAs;
      string UkzWywJLmj;
      string giFaXDRtGW;
      string MyOCawUccl;
      string AkcmWmnlEe;
      string caAbqsobGo;
      string zuicfWVwwB;
      string agiAjuGSEk;
      string PfobslxlLg;
      string GsVmmECzGA;
      string QqoCDwqzru;
      string mVXUZTFGit;
      string YikOuhKwNe;
      string sHMDTYpmXx;
      string tytQtjUBNT;
      string yuPLahGaHV;
      string lulMBeJTBA;
      if(qZxhJAlbaE == agiAjuGSEk){dSilAanTTK = true;}
      else if(agiAjuGSEk == qZxhJAlbaE){SpoeTbTPVA = true;}
      if(qYHVDpacfq == PfobslxlLg){MJisgxqAbl = true;}
      else if(PfobslxlLg == qYHVDpacfq){HFmqPtEudR = true;}
      if(XmICalmnMX == GsVmmECzGA){SOeCLyMhOO = true;}
      else if(GsVmmECzGA == XmICalmnMX){DYpbIEIfoG = true;}
      if(cuDesQopAs == QqoCDwqzru){aAzMpfMdLA = true;}
      else if(QqoCDwqzru == cuDesQopAs){ADUxPueWpy = true;}
      if(UkzWywJLmj == mVXUZTFGit){slHxIbMrfE = true;}
      else if(mVXUZTFGit == UkzWywJLmj){ysOeSlsMsr = true;}
      if(giFaXDRtGW == YikOuhKwNe){nIqOgOmfZB = true;}
      else if(YikOuhKwNe == giFaXDRtGW){hkYusszMVO = true;}
      if(MyOCawUccl == sHMDTYpmXx){OGFEiMJVDA = true;}
      else if(sHMDTYpmXx == MyOCawUccl){TmaPzEkpaT = true;}
      if(AkcmWmnlEe == tytQtjUBNT){kMobsgGhsi = true;}
      if(caAbqsobGo == yuPLahGaHV){lTCKZRJjea = true;}
      if(zuicfWVwwB == lulMBeJTBA){rfDJllfDNw = true;}
      while(tytQtjUBNT == AkcmWmnlEe){OgEeTJKLIV = true;}
      while(yuPLahGaHV == yuPLahGaHV){LwmwXPdYDV = true;}
      while(lulMBeJTBA == lulMBeJTBA){uSBbeKSyeO = true;}
      if(dSilAanTTK == true){dSilAanTTK = false;}
      if(MJisgxqAbl == true){MJisgxqAbl = false;}
      if(SOeCLyMhOO == true){SOeCLyMhOO = false;}
      if(aAzMpfMdLA == true){aAzMpfMdLA = false;}
      if(slHxIbMrfE == true){slHxIbMrfE = false;}
      if(nIqOgOmfZB == true){nIqOgOmfZB = false;}
      if(OGFEiMJVDA == true){OGFEiMJVDA = false;}
      if(kMobsgGhsi == true){kMobsgGhsi = false;}
      if(lTCKZRJjea == true){lTCKZRJjea = false;}
      if(rfDJllfDNw == true){rfDJllfDNw = false;}
      if(SpoeTbTPVA == true){SpoeTbTPVA = false;}
      if(HFmqPtEudR == true){HFmqPtEudR = false;}
      if(DYpbIEIfoG == true){DYpbIEIfoG = false;}
      if(ADUxPueWpy == true){ADUxPueWpy = false;}
      if(ysOeSlsMsr == true){ysOeSlsMsr = false;}
      if(hkYusszMVO == true){hkYusszMVO = false;}
      if(TmaPzEkpaT == true){TmaPzEkpaT = false;}
      if(OgEeTJKLIV == true){OgEeTJKLIV = false;}
      if(LwmwXPdYDV == true){LwmwXPdYDV = false;}
      if(uSBbeKSyeO == true){uSBbeKSyeO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHBGTQANHB
{ 
  void iStVDhXBpc()
  { 
      bool dwUwLVMDyU = false;
      bool nKtJNFiLqk = false;
      bool mGoQSeOIqJ = false;
      bool chQfQKqeGu = false;
      bool ntIQSjnSGl = false;
      bool lDjcPXHDdg = false;
      bool HDLoqGtOrD = false;
      bool OEFwxsyXyh = false;
      bool quCEXYxmPs = false;
      bool CmBZnjhTYL = false;
      bool oYZDXhynfW = false;
      bool ZiEupLBGQR = false;
      bool IGzzAaCeHM = false;
      bool KdzlrRVzgp = false;
      bool aJHrSThFjb = false;
      bool ibCGChZaCw = false;
      bool eSfSMuiSCX = false;
      bool pBZaqzzGff = false;
      bool sxuecibsjJ = false;
      bool ruwjKHcnfX = false;
      string SZUiAttMwE;
      string iCVoqkPNhC;
      string QaBAKqDuGW;
      string SegKEOOrSp;
      string kPHaDNinVT;
      string rqOGeqXUXI;
      string pyGYlDULkc;
      string VWurRBTZxw;
      string IPZmeaQZeM;
      string psTJzlJhoz;
      string rWCrxUuWod;
      string XyXbzaYStK;
      string ltfYmcDkre;
      string qlkxElMgoJ;
      string ftkBoqVrJY;
      string NpndMxpdEU;
      string RKeJlkNZXN;
      string NqdjerJeiu;
      string GLaSRAyGkG;
      string uibUrUPbOD;
      if(SZUiAttMwE == rWCrxUuWod){dwUwLVMDyU = true;}
      else if(rWCrxUuWod == SZUiAttMwE){oYZDXhynfW = true;}
      if(iCVoqkPNhC == XyXbzaYStK){nKtJNFiLqk = true;}
      else if(XyXbzaYStK == iCVoqkPNhC){ZiEupLBGQR = true;}
      if(QaBAKqDuGW == ltfYmcDkre){mGoQSeOIqJ = true;}
      else if(ltfYmcDkre == QaBAKqDuGW){IGzzAaCeHM = true;}
      if(SegKEOOrSp == qlkxElMgoJ){chQfQKqeGu = true;}
      else if(qlkxElMgoJ == SegKEOOrSp){KdzlrRVzgp = true;}
      if(kPHaDNinVT == ftkBoqVrJY){ntIQSjnSGl = true;}
      else if(ftkBoqVrJY == kPHaDNinVT){aJHrSThFjb = true;}
      if(rqOGeqXUXI == NpndMxpdEU){lDjcPXHDdg = true;}
      else if(NpndMxpdEU == rqOGeqXUXI){ibCGChZaCw = true;}
      if(pyGYlDULkc == RKeJlkNZXN){HDLoqGtOrD = true;}
      else if(RKeJlkNZXN == pyGYlDULkc){eSfSMuiSCX = true;}
      if(VWurRBTZxw == NqdjerJeiu){OEFwxsyXyh = true;}
      if(IPZmeaQZeM == GLaSRAyGkG){quCEXYxmPs = true;}
      if(psTJzlJhoz == uibUrUPbOD){CmBZnjhTYL = true;}
      while(NqdjerJeiu == VWurRBTZxw){pBZaqzzGff = true;}
      while(GLaSRAyGkG == GLaSRAyGkG){sxuecibsjJ = true;}
      while(uibUrUPbOD == uibUrUPbOD){ruwjKHcnfX = true;}
      if(dwUwLVMDyU == true){dwUwLVMDyU = false;}
      if(nKtJNFiLqk == true){nKtJNFiLqk = false;}
      if(mGoQSeOIqJ == true){mGoQSeOIqJ = false;}
      if(chQfQKqeGu == true){chQfQKqeGu = false;}
      if(ntIQSjnSGl == true){ntIQSjnSGl = false;}
      if(lDjcPXHDdg == true){lDjcPXHDdg = false;}
      if(HDLoqGtOrD == true){HDLoqGtOrD = false;}
      if(OEFwxsyXyh == true){OEFwxsyXyh = false;}
      if(quCEXYxmPs == true){quCEXYxmPs = false;}
      if(CmBZnjhTYL == true){CmBZnjhTYL = false;}
      if(oYZDXhynfW == true){oYZDXhynfW = false;}
      if(ZiEupLBGQR == true){ZiEupLBGQR = false;}
      if(IGzzAaCeHM == true){IGzzAaCeHM = false;}
      if(KdzlrRVzgp == true){KdzlrRVzgp = false;}
      if(aJHrSThFjb == true){aJHrSThFjb = false;}
      if(ibCGChZaCw == true){ibCGChZaCw = false;}
      if(eSfSMuiSCX == true){eSfSMuiSCX = false;}
      if(pBZaqzzGff == true){pBZaqzzGff = false;}
      if(sxuecibsjJ == true){sxuecibsjJ = false;}
      if(ruwjKHcnfX == true){ruwjKHcnfX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTQKCCZGBF
{ 
  void jxywXdetNA()
  { 
      bool SHzYazMhhV = false;
      bool sOPKUBblaA = false;
      bool bALWymphPy = false;
      bool DhTwGQgnnV = false;
      bool xhjdWSVqOz = false;
      bool AuhanRwban = false;
      bool IdRjRLuSDE = false;
      bool UnxFCsQgzf = false;
      bool QzSQxIArIo = false;
      bool TEMAMSPzLL = false;
      bool WCmKdMxcYt = false;
      bool AOctWJKBlJ = false;
      bool LDJOjQaxri = false;
      bool dRUnIOMIlk = false;
      bool KWTOoFbScC = false;
      bool HNNCzTrXZM = false;
      bool lzjoQhsnlI = false;
      bool xCPAynjuZd = false;
      bool oHUpbPDSno = false;
      bool VnhYzKmeyG = false;
      string NOTgClaqRr;
      string gAQNtNpjhI;
      string xurWNtoRgg;
      string bPwxfCiumh;
      string cjiPqhKelQ;
      string wEQlMSWxTI;
      string wIKkPREShq;
      string duxAeNMbee;
      string jKfPkXyKkN;
      string flbdkTYyAY;
      string dqxtlBHQGz;
      string FtRnYlctzq;
      string StgUKrSSOL;
      string nNaGArNkci;
      string QhDlHkTmFz;
      string qdyJGjKbjs;
      string hnBuKqSLmf;
      string XqRQajpuMY;
      string YfMPUKPRzQ;
      string hkBiBbgIbP;
      if(NOTgClaqRr == dqxtlBHQGz){SHzYazMhhV = true;}
      else if(dqxtlBHQGz == NOTgClaqRr){WCmKdMxcYt = true;}
      if(gAQNtNpjhI == FtRnYlctzq){sOPKUBblaA = true;}
      else if(FtRnYlctzq == gAQNtNpjhI){AOctWJKBlJ = true;}
      if(xurWNtoRgg == StgUKrSSOL){bALWymphPy = true;}
      else if(StgUKrSSOL == xurWNtoRgg){LDJOjQaxri = true;}
      if(bPwxfCiumh == nNaGArNkci){DhTwGQgnnV = true;}
      else if(nNaGArNkci == bPwxfCiumh){dRUnIOMIlk = true;}
      if(cjiPqhKelQ == QhDlHkTmFz){xhjdWSVqOz = true;}
      else if(QhDlHkTmFz == cjiPqhKelQ){KWTOoFbScC = true;}
      if(wEQlMSWxTI == qdyJGjKbjs){AuhanRwban = true;}
      else if(qdyJGjKbjs == wEQlMSWxTI){HNNCzTrXZM = true;}
      if(wIKkPREShq == hnBuKqSLmf){IdRjRLuSDE = true;}
      else if(hnBuKqSLmf == wIKkPREShq){lzjoQhsnlI = true;}
      if(duxAeNMbee == XqRQajpuMY){UnxFCsQgzf = true;}
      if(jKfPkXyKkN == YfMPUKPRzQ){QzSQxIArIo = true;}
      if(flbdkTYyAY == hkBiBbgIbP){TEMAMSPzLL = true;}
      while(XqRQajpuMY == duxAeNMbee){xCPAynjuZd = true;}
      while(YfMPUKPRzQ == YfMPUKPRzQ){oHUpbPDSno = true;}
      while(hkBiBbgIbP == hkBiBbgIbP){VnhYzKmeyG = true;}
      if(SHzYazMhhV == true){SHzYazMhhV = false;}
      if(sOPKUBblaA == true){sOPKUBblaA = false;}
      if(bALWymphPy == true){bALWymphPy = false;}
      if(DhTwGQgnnV == true){DhTwGQgnnV = false;}
      if(xhjdWSVqOz == true){xhjdWSVqOz = false;}
      if(AuhanRwban == true){AuhanRwban = false;}
      if(IdRjRLuSDE == true){IdRjRLuSDE = false;}
      if(UnxFCsQgzf == true){UnxFCsQgzf = false;}
      if(QzSQxIArIo == true){QzSQxIArIo = false;}
      if(TEMAMSPzLL == true){TEMAMSPzLL = false;}
      if(WCmKdMxcYt == true){WCmKdMxcYt = false;}
      if(AOctWJKBlJ == true){AOctWJKBlJ = false;}
      if(LDJOjQaxri == true){LDJOjQaxri = false;}
      if(dRUnIOMIlk == true){dRUnIOMIlk = false;}
      if(KWTOoFbScC == true){KWTOoFbScC = false;}
      if(HNNCzTrXZM == true){HNNCzTrXZM = false;}
      if(lzjoQhsnlI == true){lzjoQhsnlI = false;}
      if(xCPAynjuZd == true){xCPAynjuZd = false;}
      if(oHUpbPDSno == true){oHUpbPDSno = false;}
      if(VnhYzKmeyG == true){VnhYzKmeyG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUBLQDMIVK
{ 
  void IXyNCpJflM()
  { 
      bool mVRfUxyMMF = false;
      bool KUqtPxPTRO = false;
      bool ZyjxCaGexk = false;
      bool rHzzlCSDLY = false;
      bool jYaSDLfzTU = false;
      bool lfxeTnkTct = false;
      bool pSObMCUrIM = false;
      bool dLHsdAWRsq = false;
      bool tHLcyLJUex = false;
      bool RyZRhRKzFA = false;
      bool pnpGpZYDAT = false;
      bool RTalAiHldB = false;
      bool rANLuflpLM = false;
      bool oWLrAGQElX = false;
      bool mGTLeyXnRz = false;
      bool JYVEIoZeLK = false;
      bool nhrndtHhks = false;
      bool RDzFNlfBfx = false;
      bool HyYMCQBGjL = false;
      bool flrajENfgj = false;
      string sIlOwDpRyV;
      string cqArHLrLGj;
      string xLDuCUExQm;
      string jhCcNGzuUb;
      string DAEZjyYMSC;
      string rmfoqhFpLa;
      string zrALktoXdA;
      string LxqdfwHcLE;
      string wqeNuxCNlf;
      string BJjscLAsno;
      string IAhRpuwCIt;
      string ZbeGeHNlPn;
      string rbkyyCMxBT;
      string wOoVuuIMXA;
      string AAEqFZecOU;
      string yNcAxgOjTm;
      string hyAnxLmILi;
      string zAOPmrWsrY;
      string XjigVilnYN;
      string gXsjRCzPts;
      if(sIlOwDpRyV == IAhRpuwCIt){mVRfUxyMMF = true;}
      else if(IAhRpuwCIt == sIlOwDpRyV){pnpGpZYDAT = true;}
      if(cqArHLrLGj == ZbeGeHNlPn){KUqtPxPTRO = true;}
      else if(ZbeGeHNlPn == cqArHLrLGj){RTalAiHldB = true;}
      if(xLDuCUExQm == rbkyyCMxBT){ZyjxCaGexk = true;}
      else if(rbkyyCMxBT == xLDuCUExQm){rANLuflpLM = true;}
      if(jhCcNGzuUb == wOoVuuIMXA){rHzzlCSDLY = true;}
      else if(wOoVuuIMXA == jhCcNGzuUb){oWLrAGQElX = true;}
      if(DAEZjyYMSC == AAEqFZecOU){jYaSDLfzTU = true;}
      else if(AAEqFZecOU == DAEZjyYMSC){mGTLeyXnRz = true;}
      if(rmfoqhFpLa == yNcAxgOjTm){lfxeTnkTct = true;}
      else if(yNcAxgOjTm == rmfoqhFpLa){JYVEIoZeLK = true;}
      if(zrALktoXdA == hyAnxLmILi){pSObMCUrIM = true;}
      else if(hyAnxLmILi == zrALktoXdA){nhrndtHhks = true;}
      if(LxqdfwHcLE == zAOPmrWsrY){dLHsdAWRsq = true;}
      if(wqeNuxCNlf == XjigVilnYN){tHLcyLJUex = true;}
      if(BJjscLAsno == gXsjRCzPts){RyZRhRKzFA = true;}
      while(zAOPmrWsrY == LxqdfwHcLE){RDzFNlfBfx = true;}
      while(XjigVilnYN == XjigVilnYN){HyYMCQBGjL = true;}
      while(gXsjRCzPts == gXsjRCzPts){flrajENfgj = true;}
      if(mVRfUxyMMF == true){mVRfUxyMMF = false;}
      if(KUqtPxPTRO == true){KUqtPxPTRO = false;}
      if(ZyjxCaGexk == true){ZyjxCaGexk = false;}
      if(rHzzlCSDLY == true){rHzzlCSDLY = false;}
      if(jYaSDLfzTU == true){jYaSDLfzTU = false;}
      if(lfxeTnkTct == true){lfxeTnkTct = false;}
      if(pSObMCUrIM == true){pSObMCUrIM = false;}
      if(dLHsdAWRsq == true){dLHsdAWRsq = false;}
      if(tHLcyLJUex == true){tHLcyLJUex = false;}
      if(RyZRhRKzFA == true){RyZRhRKzFA = false;}
      if(pnpGpZYDAT == true){pnpGpZYDAT = false;}
      if(RTalAiHldB == true){RTalAiHldB = false;}
      if(rANLuflpLM == true){rANLuflpLM = false;}
      if(oWLrAGQElX == true){oWLrAGQElX = false;}
      if(mGTLeyXnRz == true){mGTLeyXnRz = false;}
      if(JYVEIoZeLK == true){JYVEIoZeLK = false;}
      if(nhrndtHhks == true){nhrndtHhks = false;}
      if(RDzFNlfBfx == true){RDzFNlfBfx = false;}
      if(HyYMCQBGjL == true){HyYMCQBGjL = false;}
      if(flrajENfgj == true){flrajENfgj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWAKYZBYBS
{ 
  void VIhwFYUNss()
  { 
      bool DRLDWiJKqf = false;
      bool pkKYfkLcMZ = false;
      bool OAjyxCGDdX = false;
      bool CJimbXDTxg = false;
      bool wBLgZllSYS = false;
      bool EibkwDgMFU = false;
      bool bGgTcfBWwH = false;
      bool gqffcNnCYL = false;
      bool QndKTThypX = false;
      bool qpNcFoTrEs = false;
      bool jOVQkMCwHi = false;
      bool OdntEmbVAJ = false;
      bool xCgXQqdDZm = false;
      bool swyeaBSNZG = false;
      bool QlqHJMCTXR = false;
      bool Nyquwghxzt = false;
      bool izVToReJSC = false;
      bool UOwtrLLYOD = false;
      bool oKeHZuEDit = false;
      bool TUNeWRQXRq = false;
      string NVBDuzykEF;
      string aCwmVfKUsi;
      string FwgSYIwQCW;
      string rDsSikEZfc;
      string JhMeqOrxcC;
      string bQEAZQohel;
      string ChigNXJcDj;
      string aknQYWjBbK;
      string QznAuayrsS;
      string wVusZazeRT;
      string FOsrapcnaD;
      string fnGTVDthll;
      string YQjknFptpx;
      string WFiIEBFuZE;
      string yJRplIPaXV;
      string gRsftoeIEV;
      string AhycfaEyOT;
      string yyHhnOytyf;
      string oPWUPFLDNP;
      string WwqEDPLnKL;
      if(NVBDuzykEF == FOsrapcnaD){DRLDWiJKqf = true;}
      else if(FOsrapcnaD == NVBDuzykEF){jOVQkMCwHi = true;}
      if(aCwmVfKUsi == fnGTVDthll){pkKYfkLcMZ = true;}
      else if(fnGTVDthll == aCwmVfKUsi){OdntEmbVAJ = true;}
      if(FwgSYIwQCW == YQjknFptpx){OAjyxCGDdX = true;}
      else if(YQjknFptpx == FwgSYIwQCW){xCgXQqdDZm = true;}
      if(rDsSikEZfc == WFiIEBFuZE){CJimbXDTxg = true;}
      else if(WFiIEBFuZE == rDsSikEZfc){swyeaBSNZG = true;}
      if(JhMeqOrxcC == yJRplIPaXV){wBLgZllSYS = true;}
      else if(yJRplIPaXV == JhMeqOrxcC){QlqHJMCTXR = true;}
      if(bQEAZQohel == gRsftoeIEV){EibkwDgMFU = true;}
      else if(gRsftoeIEV == bQEAZQohel){Nyquwghxzt = true;}
      if(ChigNXJcDj == AhycfaEyOT){bGgTcfBWwH = true;}
      else if(AhycfaEyOT == ChigNXJcDj){izVToReJSC = true;}
      if(aknQYWjBbK == yyHhnOytyf){gqffcNnCYL = true;}
      if(QznAuayrsS == oPWUPFLDNP){QndKTThypX = true;}
      if(wVusZazeRT == WwqEDPLnKL){qpNcFoTrEs = true;}
      while(yyHhnOytyf == aknQYWjBbK){UOwtrLLYOD = true;}
      while(oPWUPFLDNP == oPWUPFLDNP){oKeHZuEDit = true;}
      while(WwqEDPLnKL == WwqEDPLnKL){TUNeWRQXRq = true;}
      if(DRLDWiJKqf == true){DRLDWiJKqf = false;}
      if(pkKYfkLcMZ == true){pkKYfkLcMZ = false;}
      if(OAjyxCGDdX == true){OAjyxCGDdX = false;}
      if(CJimbXDTxg == true){CJimbXDTxg = false;}
      if(wBLgZllSYS == true){wBLgZllSYS = false;}
      if(EibkwDgMFU == true){EibkwDgMFU = false;}
      if(bGgTcfBWwH == true){bGgTcfBWwH = false;}
      if(gqffcNnCYL == true){gqffcNnCYL = false;}
      if(QndKTThypX == true){QndKTThypX = false;}
      if(qpNcFoTrEs == true){qpNcFoTrEs = false;}
      if(jOVQkMCwHi == true){jOVQkMCwHi = false;}
      if(OdntEmbVAJ == true){OdntEmbVAJ = false;}
      if(xCgXQqdDZm == true){xCgXQqdDZm = false;}
      if(swyeaBSNZG == true){swyeaBSNZG = false;}
      if(QlqHJMCTXR == true){QlqHJMCTXR = false;}
      if(Nyquwghxzt == true){Nyquwghxzt = false;}
      if(izVToReJSC == true){izVToReJSC = false;}
      if(UOwtrLLYOD == true){UOwtrLLYOD = false;}
      if(oKeHZuEDit == true){oKeHZuEDit = false;}
      if(TUNeWRQXRq == true){TUNeWRQXRq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJAVIPLNYU
{ 
  void hFOOpVbnWP()
  { 
      bool uHsjewkHSc = false;
      bool akwCJhAKrT = false;
      bool HumgZZQWyi = false;
      bool LSmCSWKtSQ = false;
      bool iiSeOjHkdN = false;
      bool zCInnAUMJF = false;
      bool eOJiQHysjl = false;
      bool XFrbkYcIRp = false;
      bool SfsjjIKyOS = false;
      bool CxkNlUYiOG = false;
      bool lOBqosKgDO = false;
      bool XMtTmzVYzH = false;
      bool xzdQiaUdoP = false;
      bool zssKEDdBup = false;
      bool ycuzupCRZl = false;
      bool zAjGJljjHO = false;
      bool YfqmOdSjPi = false;
      bool UTdIJTDdVs = false;
      bool XDEDQzJmBR = false;
      bool TtsfRSkHjQ = false;
      string jSHqPVZCyW;
      string mYBiDOVksI;
      string UTwsfsGEPh;
      string qAVGDRWgzA;
      string hVutkYSTrP;
      string sZLuEQWNLW;
      string OVmQelCtfl;
      string qnksazXCIG;
      string ZlLAnRoaCl;
      string uIUbkLheOy;
      string VYnGXFnRTF;
      string rTFFxbKmcM;
      string warspiSJHO;
      string QsmJjByEbh;
      string dXGxtbDPeJ;
      string BuCBBuftQo;
      string ldJFoyfuVu;
      string dFKtiYUuyN;
      string eDdyMUqkHo;
      string UDnmwzNBIu;
      if(jSHqPVZCyW == VYnGXFnRTF){uHsjewkHSc = true;}
      else if(VYnGXFnRTF == jSHqPVZCyW){lOBqosKgDO = true;}
      if(mYBiDOVksI == rTFFxbKmcM){akwCJhAKrT = true;}
      else if(rTFFxbKmcM == mYBiDOVksI){XMtTmzVYzH = true;}
      if(UTwsfsGEPh == warspiSJHO){HumgZZQWyi = true;}
      else if(warspiSJHO == UTwsfsGEPh){xzdQiaUdoP = true;}
      if(qAVGDRWgzA == QsmJjByEbh){LSmCSWKtSQ = true;}
      else if(QsmJjByEbh == qAVGDRWgzA){zssKEDdBup = true;}
      if(hVutkYSTrP == dXGxtbDPeJ){iiSeOjHkdN = true;}
      else if(dXGxtbDPeJ == hVutkYSTrP){ycuzupCRZl = true;}
      if(sZLuEQWNLW == BuCBBuftQo){zCInnAUMJF = true;}
      else if(BuCBBuftQo == sZLuEQWNLW){zAjGJljjHO = true;}
      if(OVmQelCtfl == ldJFoyfuVu){eOJiQHysjl = true;}
      else if(ldJFoyfuVu == OVmQelCtfl){YfqmOdSjPi = true;}
      if(qnksazXCIG == dFKtiYUuyN){XFrbkYcIRp = true;}
      if(ZlLAnRoaCl == eDdyMUqkHo){SfsjjIKyOS = true;}
      if(uIUbkLheOy == UDnmwzNBIu){CxkNlUYiOG = true;}
      while(dFKtiYUuyN == qnksazXCIG){UTdIJTDdVs = true;}
      while(eDdyMUqkHo == eDdyMUqkHo){XDEDQzJmBR = true;}
      while(UDnmwzNBIu == UDnmwzNBIu){TtsfRSkHjQ = true;}
      if(uHsjewkHSc == true){uHsjewkHSc = false;}
      if(akwCJhAKrT == true){akwCJhAKrT = false;}
      if(HumgZZQWyi == true){HumgZZQWyi = false;}
      if(LSmCSWKtSQ == true){LSmCSWKtSQ = false;}
      if(iiSeOjHkdN == true){iiSeOjHkdN = false;}
      if(zCInnAUMJF == true){zCInnAUMJF = false;}
      if(eOJiQHysjl == true){eOJiQHysjl = false;}
      if(XFrbkYcIRp == true){XFrbkYcIRp = false;}
      if(SfsjjIKyOS == true){SfsjjIKyOS = false;}
      if(CxkNlUYiOG == true){CxkNlUYiOG = false;}
      if(lOBqosKgDO == true){lOBqosKgDO = false;}
      if(XMtTmzVYzH == true){XMtTmzVYzH = false;}
      if(xzdQiaUdoP == true){xzdQiaUdoP = false;}
      if(zssKEDdBup == true){zssKEDdBup = false;}
      if(ycuzupCRZl == true){ycuzupCRZl = false;}
      if(zAjGJljjHO == true){zAjGJljjHO = false;}
      if(YfqmOdSjPi == true){YfqmOdSjPi = false;}
      if(UTdIJTDdVs == true){UTdIJTDdVs = false;}
      if(XDEDQzJmBR == true){XDEDQzJmBR = false;}
      if(TtsfRSkHjQ == true){TtsfRSkHjQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBBJKJZFKM
{ 
  void oGSrhjTHIJ()
  { 
      bool cYOhVFgfcl = false;
      bool PrWLZpwkHN = false;
      bool WEaXdEsyWt = false;
      bool VayoPeWccq = false;
      bool KPgoaxAdus = false;
      bool sYGUsXyqER = false;
      bool LhJhPosguu = false;
      bool TTIPDHXkxf = false;
      bool DPCdBxTdwq = false;
      bool geYKfbGyZl = false;
      bool EShAYZQqQl = false;
      bool AMtYNwffgR = false;
      bool UOkDOntxib = false;
      bool BYLLajgCEa = false;
      bool fcNJqTkAxi = false;
      bool wZRHRphelk = false;
      bool eTHokaBixc = false;
      bool PcbFlqAaMt = false;
      bool CtAAfaGDtk = false;
      bool CBQSwMUYYP = false;
      string yUeNJbrHRk;
      string wPLKtQRaGb;
      string SIQrpPZiby;
      string joyCdgLMde;
      string ZCVxCeECBQ;
      string wQKpOoElWt;
      string BJfSBHQJfM;
      string FFwaBPlSoL;
      string KXhLCSeHmn;
      string cYojcPWDwu;
      string OuVnKqUioz;
      string DkxLidbUQi;
      string bIVrjfPMyk;
      string siWtwPBsAK;
      string yuSnkqbdBy;
      string nBlNSFZdEd;
      string bHkEFTOCOT;
      string biUFjgogGr;
      string EkKzxqwJaq;
      string pXoVipKOhQ;
      if(yUeNJbrHRk == OuVnKqUioz){cYOhVFgfcl = true;}
      else if(OuVnKqUioz == yUeNJbrHRk){EShAYZQqQl = true;}
      if(wPLKtQRaGb == DkxLidbUQi){PrWLZpwkHN = true;}
      else if(DkxLidbUQi == wPLKtQRaGb){AMtYNwffgR = true;}
      if(SIQrpPZiby == bIVrjfPMyk){WEaXdEsyWt = true;}
      else if(bIVrjfPMyk == SIQrpPZiby){UOkDOntxib = true;}
      if(joyCdgLMde == siWtwPBsAK){VayoPeWccq = true;}
      else if(siWtwPBsAK == joyCdgLMde){BYLLajgCEa = true;}
      if(ZCVxCeECBQ == yuSnkqbdBy){KPgoaxAdus = true;}
      else if(yuSnkqbdBy == ZCVxCeECBQ){fcNJqTkAxi = true;}
      if(wQKpOoElWt == nBlNSFZdEd){sYGUsXyqER = true;}
      else if(nBlNSFZdEd == wQKpOoElWt){wZRHRphelk = true;}
      if(BJfSBHQJfM == bHkEFTOCOT){LhJhPosguu = true;}
      else if(bHkEFTOCOT == BJfSBHQJfM){eTHokaBixc = true;}
      if(FFwaBPlSoL == biUFjgogGr){TTIPDHXkxf = true;}
      if(KXhLCSeHmn == EkKzxqwJaq){DPCdBxTdwq = true;}
      if(cYojcPWDwu == pXoVipKOhQ){geYKfbGyZl = true;}
      while(biUFjgogGr == FFwaBPlSoL){PcbFlqAaMt = true;}
      while(EkKzxqwJaq == EkKzxqwJaq){CtAAfaGDtk = true;}
      while(pXoVipKOhQ == pXoVipKOhQ){CBQSwMUYYP = true;}
      if(cYOhVFgfcl == true){cYOhVFgfcl = false;}
      if(PrWLZpwkHN == true){PrWLZpwkHN = false;}
      if(WEaXdEsyWt == true){WEaXdEsyWt = false;}
      if(VayoPeWccq == true){VayoPeWccq = false;}
      if(KPgoaxAdus == true){KPgoaxAdus = false;}
      if(sYGUsXyqER == true){sYGUsXyqER = false;}
      if(LhJhPosguu == true){LhJhPosguu = false;}
      if(TTIPDHXkxf == true){TTIPDHXkxf = false;}
      if(DPCdBxTdwq == true){DPCdBxTdwq = false;}
      if(geYKfbGyZl == true){geYKfbGyZl = false;}
      if(EShAYZQqQl == true){EShAYZQqQl = false;}
      if(AMtYNwffgR == true){AMtYNwffgR = false;}
      if(UOkDOntxib == true){UOkDOntxib = false;}
      if(BYLLajgCEa == true){BYLLajgCEa = false;}
      if(fcNJqTkAxi == true){fcNJqTkAxi = false;}
      if(wZRHRphelk == true){wZRHRphelk = false;}
      if(eTHokaBixc == true){eTHokaBixc = false;}
      if(PcbFlqAaMt == true){PcbFlqAaMt = false;}
      if(CtAAfaGDtk == true){CtAAfaGDtk = false;}
      if(CBQSwMUYYP == true){CBQSwMUYYP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FURKXBFLUT
{ 
  void olapNZFmUd()
  { 
      bool HMZjQUXtpd = false;
      bool tdtoiHDrgI = false;
      bool NaEtzzhHrh = false;
      bool tGNEAtxsjo = false;
      bool DkbOJdnRQo = false;
      bool ycewFfIfkQ = false;
      bool mPBHinQonn = false;
      bool KKHrFbyojU = false;
      bool LPpDjQbRyT = false;
      bool lQHSCmjUeV = false;
      bool NycbdmVlpd = false;
      bool gSuQFWZyWS = false;
      bool LzpUCsCooR = false;
      bool rdKOHNmOYw = false;
      bool uoaUlSUqNf = false;
      bool NkxMJNHIZk = false;
      bool kfwYkDIgJr = false;
      bool jKZaWWYUhi = false;
      bool XKaJEHgxEs = false;
      bool FdomLOrBji = false;
      string IGIjRzUGmP;
      string UonwNrkCDh;
      string FlgRUwMQMQ;
      string MiDDqOiCaU;
      string IWWtIVnIFP;
      string LcblYWZqOV;
      string mEtWCklkFy;
      string IiahYiOlIz;
      string IDKwEjHQeT;
      string ormFhEbArW;
      string iCDGGbCsMp;
      string HmhONisxRR;
      string dVGkJQwVAU;
      string GOskQFAEpc;
      string hODnMBJXrz;
      string KeiasMwSxp;
      string ffsqjstwyH;
      string hoHojPSRXH;
      string HXcAKaeSrD;
      string IhGzwBVLET;
      if(IGIjRzUGmP == iCDGGbCsMp){HMZjQUXtpd = true;}
      else if(iCDGGbCsMp == IGIjRzUGmP){NycbdmVlpd = true;}
      if(UonwNrkCDh == HmhONisxRR){tdtoiHDrgI = true;}
      else if(HmhONisxRR == UonwNrkCDh){gSuQFWZyWS = true;}
      if(FlgRUwMQMQ == dVGkJQwVAU){NaEtzzhHrh = true;}
      else if(dVGkJQwVAU == FlgRUwMQMQ){LzpUCsCooR = true;}
      if(MiDDqOiCaU == GOskQFAEpc){tGNEAtxsjo = true;}
      else if(GOskQFAEpc == MiDDqOiCaU){rdKOHNmOYw = true;}
      if(IWWtIVnIFP == hODnMBJXrz){DkbOJdnRQo = true;}
      else if(hODnMBJXrz == IWWtIVnIFP){uoaUlSUqNf = true;}
      if(LcblYWZqOV == KeiasMwSxp){ycewFfIfkQ = true;}
      else if(KeiasMwSxp == LcblYWZqOV){NkxMJNHIZk = true;}
      if(mEtWCklkFy == ffsqjstwyH){mPBHinQonn = true;}
      else if(ffsqjstwyH == mEtWCklkFy){kfwYkDIgJr = true;}
      if(IiahYiOlIz == hoHojPSRXH){KKHrFbyojU = true;}
      if(IDKwEjHQeT == HXcAKaeSrD){LPpDjQbRyT = true;}
      if(ormFhEbArW == IhGzwBVLET){lQHSCmjUeV = true;}
      while(hoHojPSRXH == IiahYiOlIz){jKZaWWYUhi = true;}
      while(HXcAKaeSrD == HXcAKaeSrD){XKaJEHgxEs = true;}
      while(IhGzwBVLET == IhGzwBVLET){FdomLOrBji = true;}
      if(HMZjQUXtpd == true){HMZjQUXtpd = false;}
      if(tdtoiHDrgI == true){tdtoiHDrgI = false;}
      if(NaEtzzhHrh == true){NaEtzzhHrh = false;}
      if(tGNEAtxsjo == true){tGNEAtxsjo = false;}
      if(DkbOJdnRQo == true){DkbOJdnRQo = false;}
      if(ycewFfIfkQ == true){ycewFfIfkQ = false;}
      if(mPBHinQonn == true){mPBHinQonn = false;}
      if(KKHrFbyojU == true){KKHrFbyojU = false;}
      if(LPpDjQbRyT == true){LPpDjQbRyT = false;}
      if(lQHSCmjUeV == true){lQHSCmjUeV = false;}
      if(NycbdmVlpd == true){NycbdmVlpd = false;}
      if(gSuQFWZyWS == true){gSuQFWZyWS = false;}
      if(LzpUCsCooR == true){LzpUCsCooR = false;}
      if(rdKOHNmOYw == true){rdKOHNmOYw = false;}
      if(uoaUlSUqNf == true){uoaUlSUqNf = false;}
      if(NkxMJNHIZk == true){NkxMJNHIZk = false;}
      if(kfwYkDIgJr == true){kfwYkDIgJr = false;}
      if(jKZaWWYUhi == true){jKZaWWYUhi = false;}
      if(XKaJEHgxEs == true){XKaJEHgxEs = false;}
      if(FdomLOrBji == true){FdomLOrBji = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFWRQQTUUY
{ 
  void bmuLNxPeNx()
  { 
      bool YimzALeqhQ = false;
      bool UYbhCJrQdG = false;
      bool YnFKGNrQSB = false;
      bool MkjmFpKLqn = false;
      bool fsmJIMSCqk = false;
      bool jSOYNkdcrm = false;
      bool SNXgDjoobL = false;
      bool yfYoZeAuCt = false;
      bool tpYhRtWKYU = false;
      bool MhSEVRVGGY = false;
      bool XdZflDsYzi = false;
      bool jhZyrbooPI = false;
      bool MdPHzQMUTH = false;
      bool ItodVPQsuN = false;
      bool AyLpjdHULs = false;
      bool cfqxLtNRfV = false;
      bool pYFqZprwbc = false;
      bool LwtBIORZWU = false;
      bool IrIZdcDrRb = false;
      bool CyMYWbrTPt = false;
      string lHgTsmspnq;
      string MCeVMINMFT;
      string IcMaWBLrXn;
      string AYLDEVmrAp;
      string PmTLnrbpSl;
      string EQXVnItFxq;
      string aARzqnqbRp;
      string VVLPDVJBme;
      string ZVZljiAoPu;
      string bguIOPUTTA;
      string BAXbQhEISR;
      string zrRSRFafPH;
      string mBMWOnaCAn;
      string AohmdZxxVB;
      string eqWxwiObqI;
      string noELMznBNb;
      string HCIdRJKeor;
      string IcKNcwdOZe;
      string ZyKqzLkVZd;
      string kujstbirem;
      if(lHgTsmspnq == BAXbQhEISR){YimzALeqhQ = true;}
      else if(BAXbQhEISR == lHgTsmspnq){XdZflDsYzi = true;}
      if(MCeVMINMFT == zrRSRFafPH){UYbhCJrQdG = true;}
      else if(zrRSRFafPH == MCeVMINMFT){jhZyrbooPI = true;}
      if(IcMaWBLrXn == mBMWOnaCAn){YnFKGNrQSB = true;}
      else if(mBMWOnaCAn == IcMaWBLrXn){MdPHzQMUTH = true;}
      if(AYLDEVmrAp == AohmdZxxVB){MkjmFpKLqn = true;}
      else if(AohmdZxxVB == AYLDEVmrAp){ItodVPQsuN = true;}
      if(PmTLnrbpSl == eqWxwiObqI){fsmJIMSCqk = true;}
      else if(eqWxwiObqI == PmTLnrbpSl){AyLpjdHULs = true;}
      if(EQXVnItFxq == noELMznBNb){jSOYNkdcrm = true;}
      else if(noELMznBNb == EQXVnItFxq){cfqxLtNRfV = true;}
      if(aARzqnqbRp == HCIdRJKeor){SNXgDjoobL = true;}
      else if(HCIdRJKeor == aARzqnqbRp){pYFqZprwbc = true;}
      if(VVLPDVJBme == IcKNcwdOZe){yfYoZeAuCt = true;}
      if(ZVZljiAoPu == ZyKqzLkVZd){tpYhRtWKYU = true;}
      if(bguIOPUTTA == kujstbirem){MhSEVRVGGY = true;}
      while(IcKNcwdOZe == VVLPDVJBme){LwtBIORZWU = true;}
      while(ZyKqzLkVZd == ZyKqzLkVZd){IrIZdcDrRb = true;}
      while(kujstbirem == kujstbirem){CyMYWbrTPt = true;}
      if(YimzALeqhQ == true){YimzALeqhQ = false;}
      if(UYbhCJrQdG == true){UYbhCJrQdG = false;}
      if(YnFKGNrQSB == true){YnFKGNrQSB = false;}
      if(MkjmFpKLqn == true){MkjmFpKLqn = false;}
      if(fsmJIMSCqk == true){fsmJIMSCqk = false;}
      if(jSOYNkdcrm == true){jSOYNkdcrm = false;}
      if(SNXgDjoobL == true){SNXgDjoobL = false;}
      if(yfYoZeAuCt == true){yfYoZeAuCt = false;}
      if(tpYhRtWKYU == true){tpYhRtWKYU = false;}
      if(MhSEVRVGGY == true){MhSEVRVGGY = false;}
      if(XdZflDsYzi == true){XdZflDsYzi = false;}
      if(jhZyrbooPI == true){jhZyrbooPI = false;}
      if(MdPHzQMUTH == true){MdPHzQMUTH = false;}
      if(ItodVPQsuN == true){ItodVPQsuN = false;}
      if(AyLpjdHULs == true){AyLpjdHULs = false;}
      if(cfqxLtNRfV == true){cfqxLtNRfV = false;}
      if(pYFqZprwbc == true){pYFqZprwbc = false;}
      if(LwtBIORZWU == true){LwtBIORZWU = false;}
      if(IrIZdcDrRb == true){IrIZdcDrRb = false;}
      if(CyMYWbrTPt == true){CyMYWbrTPt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGPSIIMAXF
{ 
  void kEyCaCcYrD()
  { 
      bool jkOhxjGIsA = false;
      bool zmDzpyHGHE = false;
      bool aKNeJAgEbG = false;
      bool HeMYVNuhCH = false;
      bool UwSpKiOaJQ = false;
      bool zjHySYWiXw = false;
      bool CCfmsTZddb = false;
      bool DZEzjerXUa = false;
      bool kFtLGWWOFw = false;
      bool pLJFESPfwp = false;
      bool IjxhNYeHOn = false;
      bool gzOxKxHUfW = false;
      bool xLYgkqQyuQ = false;
      bool PMaeRAHMyg = false;
      bool qOzRPqwLtG = false;
      bool LuzZswLPwV = false;
      bool IgMxXTXjfJ = false;
      bool otVzehLGRt = false;
      bool uFDnFUMBlU = false;
      bool orPcYKCCsu = false;
      string qIiNVzHnkR;
      string GDIVOwJJki;
      string CnzBNjgWbd;
      string nmxHPGTxIs;
      string SOVeOIFYYH;
      string jFQAFDJhzl;
      string RkMHdSFBGI;
      string bMBrQnSTlF;
      string dIxTtiWxBL;
      string wlxWagCNBw;
      string CDRQeWDXiR;
      string kousHJnrNt;
      string wIAtLpOeQj;
      string kESpDapfnW;
      string fyOiaGpEOQ;
      string rJzHzsDWEo;
      string IXGzffWFog;
      string TIDqNytQTF;
      string zJPAqaELqJ;
      string WSazOHqODt;
      if(qIiNVzHnkR == CDRQeWDXiR){jkOhxjGIsA = true;}
      else if(CDRQeWDXiR == qIiNVzHnkR){IjxhNYeHOn = true;}
      if(GDIVOwJJki == kousHJnrNt){zmDzpyHGHE = true;}
      else if(kousHJnrNt == GDIVOwJJki){gzOxKxHUfW = true;}
      if(CnzBNjgWbd == wIAtLpOeQj){aKNeJAgEbG = true;}
      else if(wIAtLpOeQj == CnzBNjgWbd){xLYgkqQyuQ = true;}
      if(nmxHPGTxIs == kESpDapfnW){HeMYVNuhCH = true;}
      else if(kESpDapfnW == nmxHPGTxIs){PMaeRAHMyg = true;}
      if(SOVeOIFYYH == fyOiaGpEOQ){UwSpKiOaJQ = true;}
      else if(fyOiaGpEOQ == SOVeOIFYYH){qOzRPqwLtG = true;}
      if(jFQAFDJhzl == rJzHzsDWEo){zjHySYWiXw = true;}
      else if(rJzHzsDWEo == jFQAFDJhzl){LuzZswLPwV = true;}
      if(RkMHdSFBGI == IXGzffWFog){CCfmsTZddb = true;}
      else if(IXGzffWFog == RkMHdSFBGI){IgMxXTXjfJ = true;}
      if(bMBrQnSTlF == TIDqNytQTF){DZEzjerXUa = true;}
      if(dIxTtiWxBL == zJPAqaELqJ){kFtLGWWOFw = true;}
      if(wlxWagCNBw == WSazOHqODt){pLJFESPfwp = true;}
      while(TIDqNytQTF == bMBrQnSTlF){otVzehLGRt = true;}
      while(zJPAqaELqJ == zJPAqaELqJ){uFDnFUMBlU = true;}
      while(WSazOHqODt == WSazOHqODt){orPcYKCCsu = true;}
      if(jkOhxjGIsA == true){jkOhxjGIsA = false;}
      if(zmDzpyHGHE == true){zmDzpyHGHE = false;}
      if(aKNeJAgEbG == true){aKNeJAgEbG = false;}
      if(HeMYVNuhCH == true){HeMYVNuhCH = false;}
      if(UwSpKiOaJQ == true){UwSpKiOaJQ = false;}
      if(zjHySYWiXw == true){zjHySYWiXw = false;}
      if(CCfmsTZddb == true){CCfmsTZddb = false;}
      if(DZEzjerXUa == true){DZEzjerXUa = false;}
      if(kFtLGWWOFw == true){kFtLGWWOFw = false;}
      if(pLJFESPfwp == true){pLJFESPfwp = false;}
      if(IjxhNYeHOn == true){IjxhNYeHOn = false;}
      if(gzOxKxHUfW == true){gzOxKxHUfW = false;}
      if(xLYgkqQyuQ == true){xLYgkqQyuQ = false;}
      if(PMaeRAHMyg == true){PMaeRAHMyg = false;}
      if(qOzRPqwLtG == true){qOzRPqwLtG = false;}
      if(LuzZswLPwV == true){LuzZswLPwV = false;}
      if(IgMxXTXjfJ == true){IgMxXTXjfJ = false;}
      if(otVzehLGRt == true){otVzehLGRt = false;}
      if(uFDnFUMBlU == true){uFDnFUMBlU = false;}
      if(orPcYKCCsu == true){orPcYKCCsu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REWXHOBLVO
{ 
  void KoLuFAADmn()
  { 
      bool CuasDcYJpW = false;
      bool nMZXLCHqea = false;
      bool mRsuXmJGMM = false;
      bool IWuZHetyIQ = false;
      bool ZyIwYhUXKz = false;
      bool YTfokkBfVP = false;
      bool SSxdNRRAQg = false;
      bool IJhOAnIxVp = false;
      bool SluMmopGnV = false;
      bool cNcryHBeiG = false;
      bool QUHdqPkRox = false;
      bool bEJexfXjpX = false;
      bool aKLtDtfpPr = false;
      bool mcNOZyeQVX = false;
      bool EYQqtYExuR = false;
      bool iRoKfFIMZw = false;
      bool iuBwKzptFz = false;
      bool BGNSSCtTAe = false;
      bool pityIVnDiU = false;
      bool oRpZnJWUgt = false;
      string SNxfHVgQAH;
      string rkCeOmYafw;
      string qxSwOgLDDK;
      string sxijRPcsXw;
      string yBDXQppDLb;
      string IHjyRVuAQa;
      string JdMpNtCSNz;
      string JfCjxpsteY;
      string pIraBlNjRu;
      string UcbxlUnMKW;
      string nXoMSbEAAb;
      string bAUrkBllna;
      string gRARdgEExb;
      string BgiIjRSeIZ;
      string gNioTTHiMk;
      string iCXjpWXXhk;
      string XACXZuQMIS;
      string hGcOsThKyJ;
      string ZUrLszIzSN;
      string ttwWCgKLPX;
      if(SNxfHVgQAH == nXoMSbEAAb){CuasDcYJpW = true;}
      else if(nXoMSbEAAb == SNxfHVgQAH){QUHdqPkRox = true;}
      if(rkCeOmYafw == bAUrkBllna){nMZXLCHqea = true;}
      else if(bAUrkBllna == rkCeOmYafw){bEJexfXjpX = true;}
      if(qxSwOgLDDK == gRARdgEExb){mRsuXmJGMM = true;}
      else if(gRARdgEExb == qxSwOgLDDK){aKLtDtfpPr = true;}
      if(sxijRPcsXw == BgiIjRSeIZ){IWuZHetyIQ = true;}
      else if(BgiIjRSeIZ == sxijRPcsXw){mcNOZyeQVX = true;}
      if(yBDXQppDLb == gNioTTHiMk){ZyIwYhUXKz = true;}
      else if(gNioTTHiMk == yBDXQppDLb){EYQqtYExuR = true;}
      if(IHjyRVuAQa == iCXjpWXXhk){YTfokkBfVP = true;}
      else if(iCXjpWXXhk == IHjyRVuAQa){iRoKfFIMZw = true;}
      if(JdMpNtCSNz == XACXZuQMIS){SSxdNRRAQg = true;}
      else if(XACXZuQMIS == JdMpNtCSNz){iuBwKzptFz = true;}
      if(JfCjxpsteY == hGcOsThKyJ){IJhOAnIxVp = true;}
      if(pIraBlNjRu == ZUrLszIzSN){SluMmopGnV = true;}
      if(UcbxlUnMKW == ttwWCgKLPX){cNcryHBeiG = true;}
      while(hGcOsThKyJ == JfCjxpsteY){BGNSSCtTAe = true;}
      while(ZUrLszIzSN == ZUrLszIzSN){pityIVnDiU = true;}
      while(ttwWCgKLPX == ttwWCgKLPX){oRpZnJWUgt = true;}
      if(CuasDcYJpW == true){CuasDcYJpW = false;}
      if(nMZXLCHqea == true){nMZXLCHqea = false;}
      if(mRsuXmJGMM == true){mRsuXmJGMM = false;}
      if(IWuZHetyIQ == true){IWuZHetyIQ = false;}
      if(ZyIwYhUXKz == true){ZyIwYhUXKz = false;}
      if(YTfokkBfVP == true){YTfokkBfVP = false;}
      if(SSxdNRRAQg == true){SSxdNRRAQg = false;}
      if(IJhOAnIxVp == true){IJhOAnIxVp = false;}
      if(SluMmopGnV == true){SluMmopGnV = false;}
      if(cNcryHBeiG == true){cNcryHBeiG = false;}
      if(QUHdqPkRox == true){QUHdqPkRox = false;}
      if(bEJexfXjpX == true){bEJexfXjpX = false;}
      if(aKLtDtfpPr == true){aKLtDtfpPr = false;}
      if(mcNOZyeQVX == true){mcNOZyeQVX = false;}
      if(EYQqtYExuR == true){EYQqtYExuR = false;}
      if(iRoKfFIMZw == true){iRoKfFIMZw = false;}
      if(iuBwKzptFz == true){iuBwKzptFz = false;}
      if(BGNSSCtTAe == true){BGNSSCtTAe = false;}
      if(pityIVnDiU == true){pityIVnDiU = false;}
      if(oRpZnJWUgt == true){oRpZnJWUgt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFSKLPRHUS
{ 
  void mPMmGqtmBd()
  { 
      bool IAOPUEHFSC = false;
      bool PQOrLOPWUa = false;
      bool KLnUbawlUH = false;
      bool IzsrNYuJuJ = false;
      bool lNJJIpKtyn = false;
      bool xwVCowLsmt = false;
      bool IVkLtQWVdm = false;
      bool TGaKnwCeMk = false;
      bool QBngKMdqDQ = false;
      bool MCVBBQcyOr = false;
      bool ToQKTpUKNr = false;
      bool tgfBcHgDAh = false;
      bool leRMaRjZIX = false;
      bool TEQURbjcMT = false;
      bool qSdKWeVUXt = false;
      bool iYxfFnWDjC = false;
      bool GuBoYpQLjB = false;
      bool WDpgqTBGpw = false;
      bool uPBOntHjPc = false;
      bool EgsKNuQnlf = false;
      string ZzLOXFxiWN;
      string DwUmwyxGcM;
      string uWVVssQfiF;
      string bqViJdgAGp;
      string nyuuVurGzb;
      string mNLKRDdpUd;
      string oQzRkLakcS;
      string QwAmYxaZzy;
      string AJgGROeLRG;
      string AqebAWycJK;
      string UGdfLpMYkT;
      string bDpWcfiszW;
      string gPTWRZRXlC;
      string zxPoctfAub;
      string CFZxdwBHyU;
      string mFdmcFmGNk;
      string YomiUdnAsi;
      string zixXUaoVrV;
      string YJYQOtTbLX;
      string HYmKCMSpcz;
      if(ZzLOXFxiWN == UGdfLpMYkT){IAOPUEHFSC = true;}
      else if(UGdfLpMYkT == ZzLOXFxiWN){ToQKTpUKNr = true;}
      if(DwUmwyxGcM == bDpWcfiszW){PQOrLOPWUa = true;}
      else if(bDpWcfiszW == DwUmwyxGcM){tgfBcHgDAh = true;}
      if(uWVVssQfiF == gPTWRZRXlC){KLnUbawlUH = true;}
      else if(gPTWRZRXlC == uWVVssQfiF){leRMaRjZIX = true;}
      if(bqViJdgAGp == zxPoctfAub){IzsrNYuJuJ = true;}
      else if(zxPoctfAub == bqViJdgAGp){TEQURbjcMT = true;}
      if(nyuuVurGzb == CFZxdwBHyU){lNJJIpKtyn = true;}
      else if(CFZxdwBHyU == nyuuVurGzb){qSdKWeVUXt = true;}
      if(mNLKRDdpUd == mFdmcFmGNk){xwVCowLsmt = true;}
      else if(mFdmcFmGNk == mNLKRDdpUd){iYxfFnWDjC = true;}
      if(oQzRkLakcS == YomiUdnAsi){IVkLtQWVdm = true;}
      else if(YomiUdnAsi == oQzRkLakcS){GuBoYpQLjB = true;}
      if(QwAmYxaZzy == zixXUaoVrV){TGaKnwCeMk = true;}
      if(AJgGROeLRG == YJYQOtTbLX){QBngKMdqDQ = true;}
      if(AqebAWycJK == HYmKCMSpcz){MCVBBQcyOr = true;}
      while(zixXUaoVrV == QwAmYxaZzy){WDpgqTBGpw = true;}
      while(YJYQOtTbLX == YJYQOtTbLX){uPBOntHjPc = true;}
      while(HYmKCMSpcz == HYmKCMSpcz){EgsKNuQnlf = true;}
      if(IAOPUEHFSC == true){IAOPUEHFSC = false;}
      if(PQOrLOPWUa == true){PQOrLOPWUa = false;}
      if(KLnUbawlUH == true){KLnUbawlUH = false;}
      if(IzsrNYuJuJ == true){IzsrNYuJuJ = false;}
      if(lNJJIpKtyn == true){lNJJIpKtyn = false;}
      if(xwVCowLsmt == true){xwVCowLsmt = false;}
      if(IVkLtQWVdm == true){IVkLtQWVdm = false;}
      if(TGaKnwCeMk == true){TGaKnwCeMk = false;}
      if(QBngKMdqDQ == true){QBngKMdqDQ = false;}
      if(MCVBBQcyOr == true){MCVBBQcyOr = false;}
      if(ToQKTpUKNr == true){ToQKTpUKNr = false;}
      if(tgfBcHgDAh == true){tgfBcHgDAh = false;}
      if(leRMaRjZIX == true){leRMaRjZIX = false;}
      if(TEQURbjcMT == true){TEQURbjcMT = false;}
      if(qSdKWeVUXt == true){qSdKWeVUXt = false;}
      if(iYxfFnWDjC == true){iYxfFnWDjC = false;}
      if(GuBoYpQLjB == true){GuBoYpQLjB = false;}
      if(WDpgqTBGpw == true){WDpgqTBGpw = false;}
      if(uPBOntHjPc == true){uPBOntHjPc = false;}
      if(EgsKNuQnlf == true){EgsKNuQnlf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MHNHEVURQM
{ 
  void AwmlohqzgH()
  { 
      bool ROSGnzzjFR = false;
      bool TDfmqCrkDc = false;
      bool SaOwcBdduH = false;
      bool EYaFnPqisg = false;
      bool EDFyMIzLDy = false;
      bool BhktBpAVcm = false;
      bool VVoyMubaza = false;
      bool LIqWXOVPjU = false;
      bool BRZxFVmgEx = false;
      bool PVFGLiOGkR = false;
      bool fYMclrqOVl = false;
      bool UjlIkDurrq = false;
      bool IuWBKpDkLn = false;
      bool APeRncFxKN = false;
      bool eXKRceiwVH = false;
      bool nWNsIkBLRw = false;
      bool nFDglEFTUH = false;
      bool yxgeMjjEXe = false;
      bool GGODAdBkID = false;
      bool btfOYYUcfY = false;
      string XCGtKUlFmM;
      string kbqldPRywX;
      string KoATPqFTEx;
      string rTUWjLPUQE;
      string QQfBPdYKWs;
      string PzMBFiCmeT;
      string OSApTQHUCS;
      string AwgrHtIyDk;
      string RuwKgsGTQB;
      string IbpxoyPogy;
      string VEHEsSRUsL;
      string ZDisBTVpJa;
      string JnDBKXGjCJ;
      string dTRFPMmrQN;
      string alZEaEswuU;
      string cYfGohBGsV;
      string MgSjhGlddn;
      string gcYwAXNyZG;
      string eJogfEmKPg;
      string LfzuAsToWU;
      if(XCGtKUlFmM == VEHEsSRUsL){ROSGnzzjFR = true;}
      else if(VEHEsSRUsL == XCGtKUlFmM){fYMclrqOVl = true;}
      if(kbqldPRywX == ZDisBTVpJa){TDfmqCrkDc = true;}
      else if(ZDisBTVpJa == kbqldPRywX){UjlIkDurrq = true;}
      if(KoATPqFTEx == JnDBKXGjCJ){SaOwcBdduH = true;}
      else if(JnDBKXGjCJ == KoATPqFTEx){IuWBKpDkLn = true;}
      if(rTUWjLPUQE == dTRFPMmrQN){EYaFnPqisg = true;}
      else if(dTRFPMmrQN == rTUWjLPUQE){APeRncFxKN = true;}
      if(QQfBPdYKWs == alZEaEswuU){EDFyMIzLDy = true;}
      else if(alZEaEswuU == QQfBPdYKWs){eXKRceiwVH = true;}
      if(PzMBFiCmeT == cYfGohBGsV){BhktBpAVcm = true;}
      else if(cYfGohBGsV == PzMBFiCmeT){nWNsIkBLRw = true;}
      if(OSApTQHUCS == MgSjhGlddn){VVoyMubaza = true;}
      else if(MgSjhGlddn == OSApTQHUCS){nFDglEFTUH = true;}
      if(AwgrHtIyDk == gcYwAXNyZG){LIqWXOVPjU = true;}
      if(RuwKgsGTQB == eJogfEmKPg){BRZxFVmgEx = true;}
      if(IbpxoyPogy == LfzuAsToWU){PVFGLiOGkR = true;}
      while(gcYwAXNyZG == AwgrHtIyDk){yxgeMjjEXe = true;}
      while(eJogfEmKPg == eJogfEmKPg){GGODAdBkID = true;}
      while(LfzuAsToWU == LfzuAsToWU){btfOYYUcfY = true;}
      if(ROSGnzzjFR == true){ROSGnzzjFR = false;}
      if(TDfmqCrkDc == true){TDfmqCrkDc = false;}
      if(SaOwcBdduH == true){SaOwcBdduH = false;}
      if(EYaFnPqisg == true){EYaFnPqisg = false;}
      if(EDFyMIzLDy == true){EDFyMIzLDy = false;}
      if(BhktBpAVcm == true){BhktBpAVcm = false;}
      if(VVoyMubaza == true){VVoyMubaza = false;}
      if(LIqWXOVPjU == true){LIqWXOVPjU = false;}
      if(BRZxFVmgEx == true){BRZxFVmgEx = false;}
      if(PVFGLiOGkR == true){PVFGLiOGkR = false;}
      if(fYMclrqOVl == true){fYMclrqOVl = false;}
      if(UjlIkDurrq == true){UjlIkDurrq = false;}
      if(IuWBKpDkLn == true){IuWBKpDkLn = false;}
      if(APeRncFxKN == true){APeRncFxKN = false;}
      if(eXKRceiwVH == true){eXKRceiwVH = false;}
      if(nWNsIkBLRw == true){nWNsIkBLRw = false;}
      if(nFDglEFTUH == true){nFDglEFTUH = false;}
      if(yxgeMjjEXe == true){yxgeMjjEXe = false;}
      if(GGODAdBkID == true){GGODAdBkID = false;}
      if(btfOYYUcfY == true){btfOYYUcfY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPHSZFCKTE
{ 
  void egrPMGcmqa()
  { 
      bool mLIksLrcTJ = false;
      bool hSmrWdBoop = false;
      bool XRsroGpuug = false;
      bool btXMzsAdQC = false;
      bool EiyRkjqoRy = false;
      bool VjVsbUSPwl = false;
      bool Uwhmgmuasd = false;
      bool cXYmkoTaHE = false;
      bool PAcwKrXejd = false;
      bool akgdhIBLjx = false;
      bool oPwnUyKiIm = false;
      bool BqHqWTTkbo = false;
      bool OQpPDrptFc = false;
      bool nIqJPzEoaM = false;
      bool hoWxcicoHN = false;
      bool oPitiYZfjc = false;
      bool HPdeyszxaW = false;
      bool OdJPHZsrmT = false;
      bool PAmqnXYwaq = false;
      bool ZYFyERLqyi = false;
      string IQdFCmqnju;
      string PZNJAoqsJd;
      string KKbySzADKO;
      string BclAfoSaBe;
      string KGJOYzRaAh;
      string hBRUQyofmD;
      string mncUtlmNdK;
      string WQqeTDBMYT;
      string hZCbgzLQig;
      string AlmyqVdnUl;
      string LEwoLQJmBM;
      string xcGTUNlBnu;
      string aWdwKjcrmx;
      string ZMrmHccMQP;
      string oYPWjXeTcd;
      string jcAZLoZzeb;
      string mQzDmjjTLr;
      string jYjXFBGHMl;
      string EJPJNxLSaS;
      string CdhocXZLiA;
      if(IQdFCmqnju == LEwoLQJmBM){mLIksLrcTJ = true;}
      else if(LEwoLQJmBM == IQdFCmqnju){oPwnUyKiIm = true;}
      if(PZNJAoqsJd == xcGTUNlBnu){hSmrWdBoop = true;}
      else if(xcGTUNlBnu == PZNJAoqsJd){BqHqWTTkbo = true;}
      if(KKbySzADKO == aWdwKjcrmx){XRsroGpuug = true;}
      else if(aWdwKjcrmx == KKbySzADKO){OQpPDrptFc = true;}
      if(BclAfoSaBe == ZMrmHccMQP){btXMzsAdQC = true;}
      else if(ZMrmHccMQP == BclAfoSaBe){nIqJPzEoaM = true;}
      if(KGJOYzRaAh == oYPWjXeTcd){EiyRkjqoRy = true;}
      else if(oYPWjXeTcd == KGJOYzRaAh){hoWxcicoHN = true;}
      if(hBRUQyofmD == jcAZLoZzeb){VjVsbUSPwl = true;}
      else if(jcAZLoZzeb == hBRUQyofmD){oPitiYZfjc = true;}
      if(mncUtlmNdK == mQzDmjjTLr){Uwhmgmuasd = true;}
      else if(mQzDmjjTLr == mncUtlmNdK){HPdeyszxaW = true;}
      if(WQqeTDBMYT == jYjXFBGHMl){cXYmkoTaHE = true;}
      if(hZCbgzLQig == EJPJNxLSaS){PAcwKrXejd = true;}
      if(AlmyqVdnUl == CdhocXZLiA){akgdhIBLjx = true;}
      while(jYjXFBGHMl == WQqeTDBMYT){OdJPHZsrmT = true;}
      while(EJPJNxLSaS == EJPJNxLSaS){PAmqnXYwaq = true;}
      while(CdhocXZLiA == CdhocXZLiA){ZYFyERLqyi = true;}
      if(mLIksLrcTJ == true){mLIksLrcTJ = false;}
      if(hSmrWdBoop == true){hSmrWdBoop = false;}
      if(XRsroGpuug == true){XRsroGpuug = false;}
      if(btXMzsAdQC == true){btXMzsAdQC = false;}
      if(EiyRkjqoRy == true){EiyRkjqoRy = false;}
      if(VjVsbUSPwl == true){VjVsbUSPwl = false;}
      if(Uwhmgmuasd == true){Uwhmgmuasd = false;}
      if(cXYmkoTaHE == true){cXYmkoTaHE = false;}
      if(PAcwKrXejd == true){PAcwKrXejd = false;}
      if(akgdhIBLjx == true){akgdhIBLjx = false;}
      if(oPwnUyKiIm == true){oPwnUyKiIm = false;}
      if(BqHqWTTkbo == true){BqHqWTTkbo = false;}
      if(OQpPDrptFc == true){OQpPDrptFc = false;}
      if(nIqJPzEoaM == true){nIqJPzEoaM = false;}
      if(hoWxcicoHN == true){hoWxcicoHN = false;}
      if(oPitiYZfjc == true){oPitiYZfjc = false;}
      if(HPdeyszxaW == true){HPdeyszxaW = false;}
      if(OdJPHZsrmT == true){OdJPHZsrmT = false;}
      if(PAmqnXYwaq == true){PAmqnXYwaq = false;}
      if(ZYFyERLqyi == true){ZYFyERLqyi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHYWLWTHBT
{ 
  void ZyUPXghrSu()
  { 
      bool MbAbVGQSbD = false;
      bool UAzmrpQWkz = false;
      bool RWVdJATwVG = false;
      bool OhBnxKuhBY = false;
      bool TrBBJDoijs = false;
      bool uLSQzoFWRV = false;
      bool mUwUnlzLoh = false;
      bool uiVLeYVUTG = false;
      bool LjLcLDPjnI = false;
      bool EXQflzwgMW = false;
      bool EcsCxLpGkZ = false;
      bool SkDKKCITIk = false;
      bool VOWgcWRoYe = false;
      bool coHwChpJeA = false;
      bool MIyOoSUFVj = false;
      bool qbXaBoGMYa = false;
      bool sAgGwddGIc = false;
      bool LyoIXNPHrJ = false;
      bool CMSonBQfuM = false;
      bool adjEGLarRK = false;
      string JrEnzlJgzg;
      string yUADqQEhAk;
      string kRtrrNGNUL;
      string MOuXyisyKX;
      string BjkULpKJaq;
      string yyFdLrxLul;
      string euLmTjZcFH;
      string WGXbiAfYgC;
      string CxlcMNIQLG;
      string khCYsFYxBb;
      string QhDTUqaduL;
      string LXesihIhaG;
      string aIQzWoEzic;
      string ahXElUsSIV;
      string mdVztMCIoK;
      string wpWtAHQEwe;
      string lauRjcAZHN;
      string opZESxmQEJ;
      string mwJXfkLcEd;
      string DnVciLiEPQ;
      if(JrEnzlJgzg == QhDTUqaduL){MbAbVGQSbD = true;}
      else if(QhDTUqaduL == JrEnzlJgzg){EcsCxLpGkZ = true;}
      if(yUADqQEhAk == LXesihIhaG){UAzmrpQWkz = true;}
      else if(LXesihIhaG == yUADqQEhAk){SkDKKCITIk = true;}
      if(kRtrrNGNUL == aIQzWoEzic){RWVdJATwVG = true;}
      else if(aIQzWoEzic == kRtrrNGNUL){VOWgcWRoYe = true;}
      if(MOuXyisyKX == ahXElUsSIV){OhBnxKuhBY = true;}
      else if(ahXElUsSIV == MOuXyisyKX){coHwChpJeA = true;}
      if(BjkULpKJaq == mdVztMCIoK){TrBBJDoijs = true;}
      else if(mdVztMCIoK == BjkULpKJaq){MIyOoSUFVj = true;}
      if(yyFdLrxLul == wpWtAHQEwe){uLSQzoFWRV = true;}
      else if(wpWtAHQEwe == yyFdLrxLul){qbXaBoGMYa = true;}
      if(euLmTjZcFH == lauRjcAZHN){mUwUnlzLoh = true;}
      else if(lauRjcAZHN == euLmTjZcFH){sAgGwddGIc = true;}
      if(WGXbiAfYgC == opZESxmQEJ){uiVLeYVUTG = true;}
      if(CxlcMNIQLG == mwJXfkLcEd){LjLcLDPjnI = true;}
      if(khCYsFYxBb == DnVciLiEPQ){EXQflzwgMW = true;}
      while(opZESxmQEJ == WGXbiAfYgC){LyoIXNPHrJ = true;}
      while(mwJXfkLcEd == mwJXfkLcEd){CMSonBQfuM = true;}
      while(DnVciLiEPQ == DnVciLiEPQ){adjEGLarRK = true;}
      if(MbAbVGQSbD == true){MbAbVGQSbD = false;}
      if(UAzmrpQWkz == true){UAzmrpQWkz = false;}
      if(RWVdJATwVG == true){RWVdJATwVG = false;}
      if(OhBnxKuhBY == true){OhBnxKuhBY = false;}
      if(TrBBJDoijs == true){TrBBJDoijs = false;}
      if(uLSQzoFWRV == true){uLSQzoFWRV = false;}
      if(mUwUnlzLoh == true){mUwUnlzLoh = false;}
      if(uiVLeYVUTG == true){uiVLeYVUTG = false;}
      if(LjLcLDPjnI == true){LjLcLDPjnI = false;}
      if(EXQflzwgMW == true){EXQflzwgMW = false;}
      if(EcsCxLpGkZ == true){EcsCxLpGkZ = false;}
      if(SkDKKCITIk == true){SkDKKCITIk = false;}
      if(VOWgcWRoYe == true){VOWgcWRoYe = false;}
      if(coHwChpJeA == true){coHwChpJeA = false;}
      if(MIyOoSUFVj == true){MIyOoSUFVj = false;}
      if(qbXaBoGMYa == true){qbXaBoGMYa = false;}
      if(sAgGwddGIc == true){sAgGwddGIc = false;}
      if(LyoIXNPHrJ == true){LyoIXNPHrJ = false;}
      if(CMSonBQfuM == true){CMSonBQfuM = false;}
      if(adjEGLarRK == true){adjEGLarRK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPFPFQZOGB
{ 
  void ZmBcdTRXsa()
  { 
      bool XTjhEFeZfR = false;
      bool PqgAbWtyMH = false;
      bool yXqrTCiUpH = false;
      bool byJkiIxqHO = false;
      bool HqAsitSaSW = false;
      bool gtGNozcrOC = false;
      bool WKiXpRguRS = false;
      bool ZCpyAHWxIY = false;
      bool iHBTagrwwi = false;
      bool fFcEqxHbDQ = false;
      bool MXJAweDHMh = false;
      bool beioSPIPxJ = false;
      bool ZkzhlUYlGD = false;
      bool zutrMLxBWu = false;
      bool cjiNGBVmlb = false;
      bool nrdsqbXbNb = false;
      bool FRBIhgjqcG = false;
      bool RHrBgoBkak = false;
      bool ylAdPHQAAk = false;
      bool mUmtpKhZeZ = false;
      string QhdTTdCwie;
      string yQBPgAMApd;
      string VIqWPfjfcl;
      string XsgNxTdDlI;
      string hdpBOiGyEZ;
      string XtLOUHqHDm;
      string sVSxHEjnRM;
      string VINhwrSpHf;
      string ZlaDNcgSrp;
      string cWzzOLKssJ;
      string zRgqDOgdRb;
      string nAAXMHuPid;
      string XRuaizJNTk;
      string hZwxgHFjzz;
      string uDAPBbVbmG;
      string QuJPlgWFHE;
      string FTKgtOECqE;
      string CKPjiUReYG;
      string chZMTlQgLz;
      string kzbusarSVm;
      if(QhdTTdCwie == zRgqDOgdRb){XTjhEFeZfR = true;}
      else if(zRgqDOgdRb == QhdTTdCwie){MXJAweDHMh = true;}
      if(yQBPgAMApd == nAAXMHuPid){PqgAbWtyMH = true;}
      else if(nAAXMHuPid == yQBPgAMApd){beioSPIPxJ = true;}
      if(VIqWPfjfcl == XRuaizJNTk){yXqrTCiUpH = true;}
      else if(XRuaizJNTk == VIqWPfjfcl){ZkzhlUYlGD = true;}
      if(XsgNxTdDlI == hZwxgHFjzz){byJkiIxqHO = true;}
      else if(hZwxgHFjzz == XsgNxTdDlI){zutrMLxBWu = true;}
      if(hdpBOiGyEZ == uDAPBbVbmG){HqAsitSaSW = true;}
      else if(uDAPBbVbmG == hdpBOiGyEZ){cjiNGBVmlb = true;}
      if(XtLOUHqHDm == QuJPlgWFHE){gtGNozcrOC = true;}
      else if(QuJPlgWFHE == XtLOUHqHDm){nrdsqbXbNb = true;}
      if(sVSxHEjnRM == FTKgtOECqE){WKiXpRguRS = true;}
      else if(FTKgtOECqE == sVSxHEjnRM){FRBIhgjqcG = true;}
      if(VINhwrSpHf == CKPjiUReYG){ZCpyAHWxIY = true;}
      if(ZlaDNcgSrp == chZMTlQgLz){iHBTagrwwi = true;}
      if(cWzzOLKssJ == kzbusarSVm){fFcEqxHbDQ = true;}
      while(CKPjiUReYG == VINhwrSpHf){RHrBgoBkak = true;}
      while(chZMTlQgLz == chZMTlQgLz){ylAdPHQAAk = true;}
      while(kzbusarSVm == kzbusarSVm){mUmtpKhZeZ = true;}
      if(XTjhEFeZfR == true){XTjhEFeZfR = false;}
      if(PqgAbWtyMH == true){PqgAbWtyMH = false;}
      if(yXqrTCiUpH == true){yXqrTCiUpH = false;}
      if(byJkiIxqHO == true){byJkiIxqHO = false;}
      if(HqAsitSaSW == true){HqAsitSaSW = false;}
      if(gtGNozcrOC == true){gtGNozcrOC = false;}
      if(WKiXpRguRS == true){WKiXpRguRS = false;}
      if(ZCpyAHWxIY == true){ZCpyAHWxIY = false;}
      if(iHBTagrwwi == true){iHBTagrwwi = false;}
      if(fFcEqxHbDQ == true){fFcEqxHbDQ = false;}
      if(MXJAweDHMh == true){MXJAweDHMh = false;}
      if(beioSPIPxJ == true){beioSPIPxJ = false;}
      if(ZkzhlUYlGD == true){ZkzhlUYlGD = false;}
      if(zutrMLxBWu == true){zutrMLxBWu = false;}
      if(cjiNGBVmlb == true){cjiNGBVmlb = false;}
      if(nrdsqbXbNb == true){nrdsqbXbNb = false;}
      if(FRBIhgjqcG == true){FRBIhgjqcG = false;}
      if(RHrBgoBkak == true){RHrBgoBkak = false;}
      if(ylAdPHQAAk == true){ylAdPHQAAk = false;}
      if(mUmtpKhZeZ == true){mUmtpKhZeZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZOSPTDQAG
{ 
  void EbdVZizOtA()
  { 
      bool txgetNtqHU = false;
      bool QOHBnOmqMn = false;
      bool qmiptnPuQY = false;
      bool eHMSjdAZxf = false;
      bool ZhCWcfASJP = false;
      bool aUKTfHOpkF = false;
      bool xzZhpJBnRK = false;
      bool ONsgNJjMNN = false;
      bool nxlAxJwsmc = false;
      bool PJorhaHTfS = false;
      bool eLAyBNadFV = false;
      bool WBbWQzNZkg = false;
      bool MHAnuEXByl = false;
      bool BPftibwmzj = false;
      bool hSnRFNhRah = false;
      bool NhizGXLMDw = false;
      bool oZeSUHVhno = false;
      bool CZZBytSihg = false;
      bool WGZQYTfgnK = false;
      bool QjjCtHmUwy = false;
      string VNlyKhGaBl;
      string KiYEIiEXFy;
      string gXNFdpySqI;
      string MIAEMsiMIc;
      string WdCQBkpRQO;
      string mjtZUxzgTT;
      string imirYBhUqP;
      string ArPbaDVxDs;
      string zfCbVcOaiO;
      string sBsnsitJqz;
      string CVaBOuTRyR;
      string bCdaTCkGWw;
      string mHlcVyzair;
      string ILFDpdFANa;
      string IwcQmqXRUq;
      string ymmuLuixfP;
      string wsiFJPxZko;
      string wjsumqdUpd;
      string agFqsUYKqt;
      string uITyeOMWHW;
      if(VNlyKhGaBl == CVaBOuTRyR){txgetNtqHU = true;}
      else if(CVaBOuTRyR == VNlyKhGaBl){eLAyBNadFV = true;}
      if(KiYEIiEXFy == bCdaTCkGWw){QOHBnOmqMn = true;}
      else if(bCdaTCkGWw == KiYEIiEXFy){WBbWQzNZkg = true;}
      if(gXNFdpySqI == mHlcVyzair){qmiptnPuQY = true;}
      else if(mHlcVyzair == gXNFdpySqI){MHAnuEXByl = true;}
      if(MIAEMsiMIc == ILFDpdFANa){eHMSjdAZxf = true;}
      else if(ILFDpdFANa == MIAEMsiMIc){BPftibwmzj = true;}
      if(WdCQBkpRQO == IwcQmqXRUq){ZhCWcfASJP = true;}
      else if(IwcQmqXRUq == WdCQBkpRQO){hSnRFNhRah = true;}
      if(mjtZUxzgTT == ymmuLuixfP){aUKTfHOpkF = true;}
      else if(ymmuLuixfP == mjtZUxzgTT){NhizGXLMDw = true;}
      if(imirYBhUqP == wsiFJPxZko){xzZhpJBnRK = true;}
      else if(wsiFJPxZko == imirYBhUqP){oZeSUHVhno = true;}
      if(ArPbaDVxDs == wjsumqdUpd){ONsgNJjMNN = true;}
      if(zfCbVcOaiO == agFqsUYKqt){nxlAxJwsmc = true;}
      if(sBsnsitJqz == uITyeOMWHW){PJorhaHTfS = true;}
      while(wjsumqdUpd == ArPbaDVxDs){CZZBytSihg = true;}
      while(agFqsUYKqt == agFqsUYKqt){WGZQYTfgnK = true;}
      while(uITyeOMWHW == uITyeOMWHW){QjjCtHmUwy = true;}
      if(txgetNtqHU == true){txgetNtqHU = false;}
      if(QOHBnOmqMn == true){QOHBnOmqMn = false;}
      if(qmiptnPuQY == true){qmiptnPuQY = false;}
      if(eHMSjdAZxf == true){eHMSjdAZxf = false;}
      if(ZhCWcfASJP == true){ZhCWcfASJP = false;}
      if(aUKTfHOpkF == true){aUKTfHOpkF = false;}
      if(xzZhpJBnRK == true){xzZhpJBnRK = false;}
      if(ONsgNJjMNN == true){ONsgNJjMNN = false;}
      if(nxlAxJwsmc == true){nxlAxJwsmc = false;}
      if(PJorhaHTfS == true){PJorhaHTfS = false;}
      if(eLAyBNadFV == true){eLAyBNadFV = false;}
      if(WBbWQzNZkg == true){WBbWQzNZkg = false;}
      if(MHAnuEXByl == true){MHAnuEXByl = false;}
      if(BPftibwmzj == true){BPftibwmzj = false;}
      if(hSnRFNhRah == true){hSnRFNhRah = false;}
      if(NhizGXLMDw == true){NhizGXLMDw = false;}
      if(oZeSUHVhno == true){oZeSUHVhno = false;}
      if(CZZBytSihg == true){CZZBytSihg = false;}
      if(WGZQYTfgnK == true){WGZQYTfgnK = false;}
      if(QjjCtHmUwy == true){QjjCtHmUwy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVISSHVZYR
{ 
  void dJDZDZyLXC()
  { 
      bool xeICJWntem = false;
      bool LsPrnCsRqx = false;
      bool YzFftFphzz = false;
      bool ctgVWNAjUV = false;
      bool MJNYJWuIau = false;
      bool HgHKwxYbIE = false;
      bool fGufKRLsVZ = false;
      bool BIwVjPkgVW = false;
      bool KgGDqwlWZY = false;
      bool nXbQoGOhOr = false;
      bool KClAsykkZg = false;
      bool MrFktyzqnN = false;
      bool eoSxkdgegd = false;
      bool ACSdMHuGKs = false;
      bool LAxsLwRpWp = false;
      bool GXtAMVioOP = false;
      bool QFDufJYbYl = false;
      bool DsftCdrZko = false;
      bool LqHqWcIRQq = false;
      bool XFqubFxBMC = false;
      string EzWiefKweM;
      string lsfCcdmfbf;
      string TmuRureWdg;
      string QRpunLwcIL;
      string GztJFkPNmH;
      string qDTPEQEFnl;
      string AnRxuUDkOR;
      string hKWQYTrlLJ;
      string cRiWpNyZpW;
      string HqoWKSgxNk;
      string hdyVYgfDpk;
      string XRsdJiEuGh;
      string VcuqJqUAGG;
      string muYaazSNxJ;
      string guiFzpxLMa;
      string NlqeOFiHLh;
      string LfwjxcrRCK;
      string QqxwAasorT;
      string sJmerADsLV;
      string PKBPxAyzHV;
      if(EzWiefKweM == hdyVYgfDpk){xeICJWntem = true;}
      else if(hdyVYgfDpk == EzWiefKweM){KClAsykkZg = true;}
      if(lsfCcdmfbf == XRsdJiEuGh){LsPrnCsRqx = true;}
      else if(XRsdJiEuGh == lsfCcdmfbf){MrFktyzqnN = true;}
      if(TmuRureWdg == VcuqJqUAGG){YzFftFphzz = true;}
      else if(VcuqJqUAGG == TmuRureWdg){eoSxkdgegd = true;}
      if(QRpunLwcIL == muYaazSNxJ){ctgVWNAjUV = true;}
      else if(muYaazSNxJ == QRpunLwcIL){ACSdMHuGKs = true;}
      if(GztJFkPNmH == guiFzpxLMa){MJNYJWuIau = true;}
      else if(guiFzpxLMa == GztJFkPNmH){LAxsLwRpWp = true;}
      if(qDTPEQEFnl == NlqeOFiHLh){HgHKwxYbIE = true;}
      else if(NlqeOFiHLh == qDTPEQEFnl){GXtAMVioOP = true;}
      if(AnRxuUDkOR == LfwjxcrRCK){fGufKRLsVZ = true;}
      else if(LfwjxcrRCK == AnRxuUDkOR){QFDufJYbYl = true;}
      if(hKWQYTrlLJ == QqxwAasorT){BIwVjPkgVW = true;}
      if(cRiWpNyZpW == sJmerADsLV){KgGDqwlWZY = true;}
      if(HqoWKSgxNk == PKBPxAyzHV){nXbQoGOhOr = true;}
      while(QqxwAasorT == hKWQYTrlLJ){DsftCdrZko = true;}
      while(sJmerADsLV == sJmerADsLV){LqHqWcIRQq = true;}
      while(PKBPxAyzHV == PKBPxAyzHV){XFqubFxBMC = true;}
      if(xeICJWntem == true){xeICJWntem = false;}
      if(LsPrnCsRqx == true){LsPrnCsRqx = false;}
      if(YzFftFphzz == true){YzFftFphzz = false;}
      if(ctgVWNAjUV == true){ctgVWNAjUV = false;}
      if(MJNYJWuIau == true){MJNYJWuIau = false;}
      if(HgHKwxYbIE == true){HgHKwxYbIE = false;}
      if(fGufKRLsVZ == true){fGufKRLsVZ = false;}
      if(BIwVjPkgVW == true){BIwVjPkgVW = false;}
      if(KgGDqwlWZY == true){KgGDqwlWZY = false;}
      if(nXbQoGOhOr == true){nXbQoGOhOr = false;}
      if(KClAsykkZg == true){KClAsykkZg = false;}
      if(MrFktyzqnN == true){MrFktyzqnN = false;}
      if(eoSxkdgegd == true){eoSxkdgegd = false;}
      if(ACSdMHuGKs == true){ACSdMHuGKs = false;}
      if(LAxsLwRpWp == true){LAxsLwRpWp = false;}
      if(GXtAMVioOP == true){GXtAMVioOP = false;}
      if(QFDufJYbYl == true){QFDufJYbYl = false;}
      if(DsftCdrZko == true){DsftCdrZko = false;}
      if(LqHqWcIRQq == true){LqHqWcIRQq = false;}
      if(XFqubFxBMC == true){XFqubFxBMC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGDIQKRWDU
{ 
  void UeClPpkhkh()
  { 
      bool FSntaEIKVc = false;
      bool EHktQefseV = false;
      bool fVDfKbaTRg = false;
      bool dgLHwSCgHG = false;
      bool VQVqwNmpWh = false;
      bool bcPiPiPHiz = false;
      bool dnrnyWwcxx = false;
      bool bykYAOzMjx = false;
      bool njwjFBRbrN = false;
      bool DuyIcgXhrY = false;
      bool RKsZFcqpiB = false;
      bool jCWkKsqIix = false;
      bool FUkjtgAbwT = false;
      bool qRULfdqWdb = false;
      bool JarpcBXMyi = false;
      bool oOztTwYIeY = false;
      bool cOtPJRgLFg = false;
      bool BUeGndbtGr = false;
      bool JmdMdbRZri = false;
      bool EhqEytgcgK = false;
      string PEfTcKMJeR;
      string OQXNZqSXOk;
      string pPSmfKnUow;
      string lbCBcUDWTM;
      string AhpxOGTeVS;
      string dMoBBAlsnR;
      string WqUhelNWjE;
      string muDBjHZUYZ;
      string qIyVSYmBzc;
      string iKiCpINHRb;
      string rwuRfhInQs;
      string ZQTNaNryPG;
      string zMWGUcLBLa;
      string sSDwgtNgpj;
      string PzjFDSpUab;
      string PPqLcfYnwC;
      string VHcpAHNXgg;
      string ALHfpAbQDC;
      string lqaiKdbqTA;
      string VYjnNIVtFu;
      if(PEfTcKMJeR == rwuRfhInQs){FSntaEIKVc = true;}
      else if(rwuRfhInQs == PEfTcKMJeR){RKsZFcqpiB = true;}
      if(OQXNZqSXOk == ZQTNaNryPG){EHktQefseV = true;}
      else if(ZQTNaNryPG == OQXNZqSXOk){jCWkKsqIix = true;}
      if(pPSmfKnUow == zMWGUcLBLa){fVDfKbaTRg = true;}
      else if(zMWGUcLBLa == pPSmfKnUow){FUkjtgAbwT = true;}
      if(lbCBcUDWTM == sSDwgtNgpj){dgLHwSCgHG = true;}
      else if(sSDwgtNgpj == lbCBcUDWTM){qRULfdqWdb = true;}
      if(AhpxOGTeVS == PzjFDSpUab){VQVqwNmpWh = true;}
      else if(PzjFDSpUab == AhpxOGTeVS){JarpcBXMyi = true;}
      if(dMoBBAlsnR == PPqLcfYnwC){bcPiPiPHiz = true;}
      else if(PPqLcfYnwC == dMoBBAlsnR){oOztTwYIeY = true;}
      if(WqUhelNWjE == VHcpAHNXgg){dnrnyWwcxx = true;}
      else if(VHcpAHNXgg == WqUhelNWjE){cOtPJRgLFg = true;}
      if(muDBjHZUYZ == ALHfpAbQDC){bykYAOzMjx = true;}
      if(qIyVSYmBzc == lqaiKdbqTA){njwjFBRbrN = true;}
      if(iKiCpINHRb == VYjnNIVtFu){DuyIcgXhrY = true;}
      while(ALHfpAbQDC == muDBjHZUYZ){BUeGndbtGr = true;}
      while(lqaiKdbqTA == lqaiKdbqTA){JmdMdbRZri = true;}
      while(VYjnNIVtFu == VYjnNIVtFu){EhqEytgcgK = true;}
      if(FSntaEIKVc == true){FSntaEIKVc = false;}
      if(EHktQefseV == true){EHktQefseV = false;}
      if(fVDfKbaTRg == true){fVDfKbaTRg = false;}
      if(dgLHwSCgHG == true){dgLHwSCgHG = false;}
      if(VQVqwNmpWh == true){VQVqwNmpWh = false;}
      if(bcPiPiPHiz == true){bcPiPiPHiz = false;}
      if(dnrnyWwcxx == true){dnrnyWwcxx = false;}
      if(bykYAOzMjx == true){bykYAOzMjx = false;}
      if(njwjFBRbrN == true){njwjFBRbrN = false;}
      if(DuyIcgXhrY == true){DuyIcgXhrY = false;}
      if(RKsZFcqpiB == true){RKsZFcqpiB = false;}
      if(jCWkKsqIix == true){jCWkKsqIix = false;}
      if(FUkjtgAbwT == true){FUkjtgAbwT = false;}
      if(qRULfdqWdb == true){qRULfdqWdb = false;}
      if(JarpcBXMyi == true){JarpcBXMyi = false;}
      if(oOztTwYIeY == true){oOztTwYIeY = false;}
      if(cOtPJRgLFg == true){cOtPJRgLFg = false;}
      if(BUeGndbtGr == true){BUeGndbtGr = false;}
      if(JmdMdbRZri == true){JmdMdbRZri = false;}
      if(EhqEytgcgK == true){EhqEytgcgK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AEXNVOLOBR
{ 
  void BsPdRHaTea()
  { 
      bool kXlZZwMdHf = false;
      bool QCzbeJmjBW = false;
      bool qHtkwdWptE = false;
      bool teenuMDLal = false;
      bool KpWyVkOFOO = false;
      bool GtirNddBdw = false;
      bool YViCllWLgS = false;
      bool FaIPLBkuOL = false;
      bool ORafxzwmZQ = false;
      bool iCheMnGTMj = false;
      bool NDXwIekSfM = false;
      bool shlRhHuDEl = false;
      bool ojlPiDsdCW = false;
      bool tQidyLseWS = false;
      bool NcHNXAPPxF = false;
      bool sDOatdRIME = false;
      bool lHPIRbyHTV = false;
      bool NPflXLbXrh = false;
      bool mdgwdpBIjT = false;
      bool tkSRfGMyuu = false;
      string hTkBLnNsjo;
      string mKOcZhfMZb;
      string BCmuYGYOqW;
      string iWmqXaudkj;
      string wrzdNnWKKj;
      string AwxzWegpcF;
      string PzBMFQXWEy;
      string lBbpfJCJgk;
      string jNDHWmYmUs;
      string tFBeUxpmYx;
      string QzFMxyUHSM;
      string bWIqUButpR;
      string qjCLDgzwUi;
      string SPkjTkIpKX;
      string SRUHRWwJKS;
      string BwwGFgxsIP;
      string zYljsLlXXj;
      string rFjSzZPttf;
      string kokBhWTddm;
      string nOhtXtejOF;
      if(hTkBLnNsjo == QzFMxyUHSM){kXlZZwMdHf = true;}
      else if(QzFMxyUHSM == hTkBLnNsjo){NDXwIekSfM = true;}
      if(mKOcZhfMZb == bWIqUButpR){QCzbeJmjBW = true;}
      else if(bWIqUButpR == mKOcZhfMZb){shlRhHuDEl = true;}
      if(BCmuYGYOqW == qjCLDgzwUi){qHtkwdWptE = true;}
      else if(qjCLDgzwUi == BCmuYGYOqW){ojlPiDsdCW = true;}
      if(iWmqXaudkj == SPkjTkIpKX){teenuMDLal = true;}
      else if(SPkjTkIpKX == iWmqXaudkj){tQidyLseWS = true;}
      if(wrzdNnWKKj == SRUHRWwJKS){KpWyVkOFOO = true;}
      else if(SRUHRWwJKS == wrzdNnWKKj){NcHNXAPPxF = true;}
      if(AwxzWegpcF == BwwGFgxsIP){GtirNddBdw = true;}
      else if(BwwGFgxsIP == AwxzWegpcF){sDOatdRIME = true;}
      if(PzBMFQXWEy == zYljsLlXXj){YViCllWLgS = true;}
      else if(zYljsLlXXj == PzBMFQXWEy){lHPIRbyHTV = true;}
      if(lBbpfJCJgk == rFjSzZPttf){FaIPLBkuOL = true;}
      if(jNDHWmYmUs == kokBhWTddm){ORafxzwmZQ = true;}
      if(tFBeUxpmYx == nOhtXtejOF){iCheMnGTMj = true;}
      while(rFjSzZPttf == lBbpfJCJgk){NPflXLbXrh = true;}
      while(kokBhWTddm == kokBhWTddm){mdgwdpBIjT = true;}
      while(nOhtXtejOF == nOhtXtejOF){tkSRfGMyuu = true;}
      if(kXlZZwMdHf == true){kXlZZwMdHf = false;}
      if(QCzbeJmjBW == true){QCzbeJmjBW = false;}
      if(qHtkwdWptE == true){qHtkwdWptE = false;}
      if(teenuMDLal == true){teenuMDLal = false;}
      if(KpWyVkOFOO == true){KpWyVkOFOO = false;}
      if(GtirNddBdw == true){GtirNddBdw = false;}
      if(YViCllWLgS == true){YViCllWLgS = false;}
      if(FaIPLBkuOL == true){FaIPLBkuOL = false;}
      if(ORafxzwmZQ == true){ORafxzwmZQ = false;}
      if(iCheMnGTMj == true){iCheMnGTMj = false;}
      if(NDXwIekSfM == true){NDXwIekSfM = false;}
      if(shlRhHuDEl == true){shlRhHuDEl = false;}
      if(ojlPiDsdCW == true){ojlPiDsdCW = false;}
      if(tQidyLseWS == true){tQidyLseWS = false;}
      if(NcHNXAPPxF == true){NcHNXAPPxF = false;}
      if(sDOatdRIME == true){sDOatdRIME = false;}
      if(lHPIRbyHTV == true){lHPIRbyHTV = false;}
      if(NPflXLbXrh == true){NPflXLbXrh = false;}
      if(mdgwdpBIjT == true){mdgwdpBIjT = false;}
      if(tkSRfGMyuu == true){tkSRfGMyuu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNAJYZNPOO
{ 
  void ClPuowHwZY()
  { 
      bool DEydnaCUDZ = false;
      bool LtzIRuWVeF = false;
      bool PlZswzeEXe = false;
      bool RnyuEbJQqK = false;
      bool TQYtszOSTm = false;
      bool FsujZRdEhn = false;
      bool uyxYIXwEDo = false;
      bool kGeUlyMfAw = false;
      bool jMjjZYrNUm = false;
      bool xEhCPVTAlV = false;
      bool DKOdCyOayb = false;
      bool EyElDhNNzi = false;
      bool ehiQqfYbFP = false;
      bool eMterZyFha = false;
      bool KRPshzAuyg = false;
      bool HGBCpVbxmV = false;
      bool ZlUhxrEZtd = false;
      bool iIfXYMSphr = false;
      bool fcdXIXKqnW = false;
      bool xASLBYxgup = false;
      string uzbcHtJnfq;
      string flttcWIbxH;
      string ousbgWPbxp;
      string MjDeIdUZYw;
      string LILqyQEArg;
      string sjkdWAFzwk;
      string dgppduhOlz;
      string BiDBufjBdP;
      string ROjPwbzZII;
      string XUcmSdRVNC;
      string ioOreJgjhp;
      string QEVfSOxZsC;
      string wHGdbfFPiR;
      string NOnagcAqjm;
      string tPrRrTzxUD;
      string grbLGbikQy;
      string DRBQbCPtyp;
      string OFoGHfPnkI;
      string gItekVlcUF;
      string tOakibOapp;
      if(uzbcHtJnfq == ioOreJgjhp){DEydnaCUDZ = true;}
      else if(ioOreJgjhp == uzbcHtJnfq){DKOdCyOayb = true;}
      if(flttcWIbxH == QEVfSOxZsC){LtzIRuWVeF = true;}
      else if(QEVfSOxZsC == flttcWIbxH){EyElDhNNzi = true;}
      if(ousbgWPbxp == wHGdbfFPiR){PlZswzeEXe = true;}
      else if(wHGdbfFPiR == ousbgWPbxp){ehiQqfYbFP = true;}
      if(MjDeIdUZYw == NOnagcAqjm){RnyuEbJQqK = true;}
      else if(NOnagcAqjm == MjDeIdUZYw){eMterZyFha = true;}
      if(LILqyQEArg == tPrRrTzxUD){TQYtszOSTm = true;}
      else if(tPrRrTzxUD == LILqyQEArg){KRPshzAuyg = true;}
      if(sjkdWAFzwk == grbLGbikQy){FsujZRdEhn = true;}
      else if(grbLGbikQy == sjkdWAFzwk){HGBCpVbxmV = true;}
      if(dgppduhOlz == DRBQbCPtyp){uyxYIXwEDo = true;}
      else if(DRBQbCPtyp == dgppduhOlz){ZlUhxrEZtd = true;}
      if(BiDBufjBdP == OFoGHfPnkI){kGeUlyMfAw = true;}
      if(ROjPwbzZII == gItekVlcUF){jMjjZYrNUm = true;}
      if(XUcmSdRVNC == tOakibOapp){xEhCPVTAlV = true;}
      while(OFoGHfPnkI == BiDBufjBdP){iIfXYMSphr = true;}
      while(gItekVlcUF == gItekVlcUF){fcdXIXKqnW = true;}
      while(tOakibOapp == tOakibOapp){xASLBYxgup = true;}
      if(DEydnaCUDZ == true){DEydnaCUDZ = false;}
      if(LtzIRuWVeF == true){LtzIRuWVeF = false;}
      if(PlZswzeEXe == true){PlZswzeEXe = false;}
      if(RnyuEbJQqK == true){RnyuEbJQqK = false;}
      if(TQYtszOSTm == true){TQYtszOSTm = false;}
      if(FsujZRdEhn == true){FsujZRdEhn = false;}
      if(uyxYIXwEDo == true){uyxYIXwEDo = false;}
      if(kGeUlyMfAw == true){kGeUlyMfAw = false;}
      if(jMjjZYrNUm == true){jMjjZYrNUm = false;}
      if(xEhCPVTAlV == true){xEhCPVTAlV = false;}
      if(DKOdCyOayb == true){DKOdCyOayb = false;}
      if(EyElDhNNzi == true){EyElDhNNzi = false;}
      if(ehiQqfYbFP == true){ehiQqfYbFP = false;}
      if(eMterZyFha == true){eMterZyFha = false;}
      if(KRPshzAuyg == true){KRPshzAuyg = false;}
      if(HGBCpVbxmV == true){HGBCpVbxmV = false;}
      if(ZlUhxrEZtd == true){ZlUhxrEZtd = false;}
      if(iIfXYMSphr == true){iIfXYMSphr = false;}
      if(fcdXIXKqnW == true){fcdXIXKqnW = false;}
      if(xASLBYxgup == true){xASLBYxgup = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLGJVOPRQW
{ 
  void ZMVaHXOQTa()
  { 
      bool DcRRhzIZrf = false;
      bool qqtmxNxgmN = false;
      bool YkrznYhJpY = false;
      bool LquoNaWtEy = false;
      bool tEIszCJtEh = false;
      bool YDRlERkRcJ = false;
      bool QzjSTAuFYV = false;
      bool pDcoTUbzAl = false;
      bool OmFHAHZJjw = false;
      bool pEQugtTpYz = false;
      bool GDVhqVacSj = false;
      bool olRqtdtbSL = false;
      bool alVcfklgHY = false;
      bool AlZBeKRWQd = false;
      bool fwpzGEmZBD = false;
      bool zqWNXUhsCG = false;
      bool jtUsjDLQMi = false;
      bool LWLnfduVWa = false;
      bool yLeEZIOMcJ = false;
      bool cYUKtlaxPC = false;
      string rmteworqFW;
      string ZeRehhjfmq;
      string HMCpCAPqWY;
      string syHyFESHHg;
      string QCauHxTkqR;
      string brYWsejDbu;
      string ZBTfdbWSYc;
      string PcXFaFkHiF;
      string gdAFwBYkFZ;
      string TPeMHPhuQf;
      string ZAMNBzUSun;
      string scUWNuBOic;
      string ClNzIzxKyL;
      string WppCefRlDx;
      string gFoRfquIyL;
      string NTLncnmNEC;
      string CJTjQDmRqg;
      string dOKkwxwwSR;
      string EnLmxDdBYq;
      string sEgBuWkEAc;
      if(rmteworqFW == ZAMNBzUSun){DcRRhzIZrf = true;}
      else if(ZAMNBzUSun == rmteworqFW){GDVhqVacSj = true;}
      if(ZeRehhjfmq == scUWNuBOic){qqtmxNxgmN = true;}
      else if(scUWNuBOic == ZeRehhjfmq){olRqtdtbSL = true;}
      if(HMCpCAPqWY == ClNzIzxKyL){YkrznYhJpY = true;}
      else if(ClNzIzxKyL == HMCpCAPqWY){alVcfklgHY = true;}
      if(syHyFESHHg == WppCefRlDx){LquoNaWtEy = true;}
      else if(WppCefRlDx == syHyFESHHg){AlZBeKRWQd = true;}
      if(QCauHxTkqR == gFoRfquIyL){tEIszCJtEh = true;}
      else if(gFoRfquIyL == QCauHxTkqR){fwpzGEmZBD = true;}
      if(brYWsejDbu == NTLncnmNEC){YDRlERkRcJ = true;}
      else if(NTLncnmNEC == brYWsejDbu){zqWNXUhsCG = true;}
      if(ZBTfdbWSYc == CJTjQDmRqg){QzjSTAuFYV = true;}
      else if(CJTjQDmRqg == ZBTfdbWSYc){jtUsjDLQMi = true;}
      if(PcXFaFkHiF == dOKkwxwwSR){pDcoTUbzAl = true;}
      if(gdAFwBYkFZ == EnLmxDdBYq){OmFHAHZJjw = true;}
      if(TPeMHPhuQf == sEgBuWkEAc){pEQugtTpYz = true;}
      while(dOKkwxwwSR == PcXFaFkHiF){LWLnfduVWa = true;}
      while(EnLmxDdBYq == EnLmxDdBYq){yLeEZIOMcJ = true;}
      while(sEgBuWkEAc == sEgBuWkEAc){cYUKtlaxPC = true;}
      if(DcRRhzIZrf == true){DcRRhzIZrf = false;}
      if(qqtmxNxgmN == true){qqtmxNxgmN = false;}
      if(YkrznYhJpY == true){YkrznYhJpY = false;}
      if(LquoNaWtEy == true){LquoNaWtEy = false;}
      if(tEIszCJtEh == true){tEIszCJtEh = false;}
      if(YDRlERkRcJ == true){YDRlERkRcJ = false;}
      if(QzjSTAuFYV == true){QzjSTAuFYV = false;}
      if(pDcoTUbzAl == true){pDcoTUbzAl = false;}
      if(OmFHAHZJjw == true){OmFHAHZJjw = false;}
      if(pEQugtTpYz == true){pEQugtTpYz = false;}
      if(GDVhqVacSj == true){GDVhqVacSj = false;}
      if(olRqtdtbSL == true){olRqtdtbSL = false;}
      if(alVcfklgHY == true){alVcfklgHY = false;}
      if(AlZBeKRWQd == true){AlZBeKRWQd = false;}
      if(fwpzGEmZBD == true){fwpzGEmZBD = false;}
      if(zqWNXUhsCG == true){zqWNXUhsCG = false;}
      if(jtUsjDLQMi == true){jtUsjDLQMi = false;}
      if(LWLnfduVWa == true){LWLnfduVWa = false;}
      if(yLeEZIOMcJ == true){yLeEZIOMcJ = false;}
      if(cYUKtlaxPC == true){cYUKtlaxPC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOMJQGSOPV
{ 
  void MhqOekpfSb()
  { 
      bool CMhkhswKCq = false;
      bool WfLsyeQrLn = false;
      bool bZIVqiWzIf = false;
      bool TAJrnkmfJT = false;
      bool ENSdcsQydw = false;
      bool arQUecDMsy = false;
      bool WwCVWWVTFN = false;
      bool qkiriOGesy = false;
      bool SYVLFainNK = false;
      bool galKxIKwGF = false;
      bool WwrQEpJXkP = false;
      bool VYStfxZpQw = false;
      bool mgGufQyYua = false;
      bool EKXmaVfEHO = false;
      bool RLCynIHqdz = false;
      bool hUeKSppxkn = false;
      bool rkbKLLAfTK = false;
      bool RViCeadIGW = false;
      bool IGtwrieNUk = false;
      bool ehSSWfirlc = false;
      string FSGuYMwgAw;
      string EyLLXuecbU;
      string kGJXrsHBVg;
      string bnTdbwUdVy;
      string wkbpkLBCAL;
      string cFyUOzIhDf;
      string EtLSTPehjb;
      string aAHdYzdSmg;
      string qFBJEWpyOc;
      string mlaosCZJWV;
      string fSRYkbyUwO;
      string UpuVnzrBNw;
      string ZfTGnnZRkW;
      string ZTuQAXmcYc;
      string YUCzHxqEBs;
      string JYuawAzKjw;
      string BgjZoAtdVP;
      string LPckXEcTzp;
      string xVQqNBXUUz;
      string YbrcbqkcJG;
      if(FSGuYMwgAw == fSRYkbyUwO){CMhkhswKCq = true;}
      else if(fSRYkbyUwO == FSGuYMwgAw){WwrQEpJXkP = true;}
      if(EyLLXuecbU == UpuVnzrBNw){WfLsyeQrLn = true;}
      else if(UpuVnzrBNw == EyLLXuecbU){VYStfxZpQw = true;}
      if(kGJXrsHBVg == ZfTGnnZRkW){bZIVqiWzIf = true;}
      else if(ZfTGnnZRkW == kGJXrsHBVg){mgGufQyYua = true;}
      if(bnTdbwUdVy == ZTuQAXmcYc){TAJrnkmfJT = true;}
      else if(ZTuQAXmcYc == bnTdbwUdVy){EKXmaVfEHO = true;}
      if(wkbpkLBCAL == YUCzHxqEBs){ENSdcsQydw = true;}
      else if(YUCzHxqEBs == wkbpkLBCAL){RLCynIHqdz = true;}
      if(cFyUOzIhDf == JYuawAzKjw){arQUecDMsy = true;}
      else if(JYuawAzKjw == cFyUOzIhDf){hUeKSppxkn = true;}
      if(EtLSTPehjb == BgjZoAtdVP){WwCVWWVTFN = true;}
      else if(BgjZoAtdVP == EtLSTPehjb){rkbKLLAfTK = true;}
      if(aAHdYzdSmg == LPckXEcTzp){qkiriOGesy = true;}
      if(qFBJEWpyOc == xVQqNBXUUz){SYVLFainNK = true;}
      if(mlaosCZJWV == YbrcbqkcJG){galKxIKwGF = true;}
      while(LPckXEcTzp == aAHdYzdSmg){RViCeadIGW = true;}
      while(xVQqNBXUUz == xVQqNBXUUz){IGtwrieNUk = true;}
      while(YbrcbqkcJG == YbrcbqkcJG){ehSSWfirlc = true;}
      if(CMhkhswKCq == true){CMhkhswKCq = false;}
      if(WfLsyeQrLn == true){WfLsyeQrLn = false;}
      if(bZIVqiWzIf == true){bZIVqiWzIf = false;}
      if(TAJrnkmfJT == true){TAJrnkmfJT = false;}
      if(ENSdcsQydw == true){ENSdcsQydw = false;}
      if(arQUecDMsy == true){arQUecDMsy = false;}
      if(WwCVWWVTFN == true){WwCVWWVTFN = false;}
      if(qkiriOGesy == true){qkiriOGesy = false;}
      if(SYVLFainNK == true){SYVLFainNK = false;}
      if(galKxIKwGF == true){galKxIKwGF = false;}
      if(WwrQEpJXkP == true){WwrQEpJXkP = false;}
      if(VYStfxZpQw == true){VYStfxZpQw = false;}
      if(mgGufQyYua == true){mgGufQyYua = false;}
      if(EKXmaVfEHO == true){EKXmaVfEHO = false;}
      if(RLCynIHqdz == true){RLCynIHqdz = false;}
      if(hUeKSppxkn == true){hUeKSppxkn = false;}
      if(rkbKLLAfTK == true){rkbKLLAfTK = false;}
      if(RViCeadIGW == true){RViCeadIGW = false;}
      if(IGtwrieNUk == true){IGtwrieNUk = false;}
      if(ehSSWfirlc == true){ehSSWfirlc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKBQEMZVEW
{ 
  void XergdXkRXG()
  { 
      bool ofuAenXhhK = false;
      bool fCiAAFVLhG = false;
      bool SQTjaJxjlW = false;
      bool DYKOHIhJoY = false;
      bool oUDyLmYgMR = false;
      bool oaTiFYMKZU = false;
      bool pmuKGHrUrq = false;
      bool XLVIRyNUYm = false;
      bool kPXUhcFbIi = false;
      bool uWjThBYrqD = false;
      bool uDnUscEKRH = false;
      bool LqlljZPZcd = false;
      bool CQMJuAbBaP = false;
      bool YUcUrgaCaE = false;
      bool XtJBXDkxjH = false;
      bool lyONAeqeYs = false;
      bool BCjChpOQtC = false;
      bool yNzYFIGLlr = false;
      bool OdRSdaFPTM = false;
      bool pwchDVKHSg = false;
      string eLKDNEgUbs;
      string tCnQjEEFjY;
      string RMMBzsZycX;
      string RWIRawHEyY;
      string NNKSgWjrcl;
      string iQIlGRzIEU;
      string ehqDbWsVon;
      string xAGLLEBsUc;
      string IgVqnBOWLJ;
      string xyzdtfVHqJ;
      string cOConiJwaC;
      string PFnbLxMAPZ;
      string IWKfpzAcQf;
      string htCKztegCF;
      string rRwJsrJXRx;
      string SVrQBGDVyo;
      string hgetTUCccR;
      string RexJhpZAlx;
      string ocKTMMClJr;
      string pIhMWLlBpX;
      if(eLKDNEgUbs == cOConiJwaC){ofuAenXhhK = true;}
      else if(cOConiJwaC == eLKDNEgUbs){uDnUscEKRH = true;}
      if(tCnQjEEFjY == PFnbLxMAPZ){fCiAAFVLhG = true;}
      else if(PFnbLxMAPZ == tCnQjEEFjY){LqlljZPZcd = true;}
      if(RMMBzsZycX == IWKfpzAcQf){SQTjaJxjlW = true;}
      else if(IWKfpzAcQf == RMMBzsZycX){CQMJuAbBaP = true;}
      if(RWIRawHEyY == htCKztegCF){DYKOHIhJoY = true;}
      else if(htCKztegCF == RWIRawHEyY){YUcUrgaCaE = true;}
      if(NNKSgWjrcl == rRwJsrJXRx){oUDyLmYgMR = true;}
      else if(rRwJsrJXRx == NNKSgWjrcl){XtJBXDkxjH = true;}
      if(iQIlGRzIEU == SVrQBGDVyo){oaTiFYMKZU = true;}
      else if(SVrQBGDVyo == iQIlGRzIEU){lyONAeqeYs = true;}
      if(ehqDbWsVon == hgetTUCccR){pmuKGHrUrq = true;}
      else if(hgetTUCccR == ehqDbWsVon){BCjChpOQtC = true;}
      if(xAGLLEBsUc == RexJhpZAlx){XLVIRyNUYm = true;}
      if(IgVqnBOWLJ == ocKTMMClJr){kPXUhcFbIi = true;}
      if(xyzdtfVHqJ == pIhMWLlBpX){uWjThBYrqD = true;}
      while(RexJhpZAlx == xAGLLEBsUc){yNzYFIGLlr = true;}
      while(ocKTMMClJr == ocKTMMClJr){OdRSdaFPTM = true;}
      while(pIhMWLlBpX == pIhMWLlBpX){pwchDVKHSg = true;}
      if(ofuAenXhhK == true){ofuAenXhhK = false;}
      if(fCiAAFVLhG == true){fCiAAFVLhG = false;}
      if(SQTjaJxjlW == true){SQTjaJxjlW = false;}
      if(DYKOHIhJoY == true){DYKOHIhJoY = false;}
      if(oUDyLmYgMR == true){oUDyLmYgMR = false;}
      if(oaTiFYMKZU == true){oaTiFYMKZU = false;}
      if(pmuKGHrUrq == true){pmuKGHrUrq = false;}
      if(XLVIRyNUYm == true){XLVIRyNUYm = false;}
      if(kPXUhcFbIi == true){kPXUhcFbIi = false;}
      if(uWjThBYrqD == true){uWjThBYrqD = false;}
      if(uDnUscEKRH == true){uDnUscEKRH = false;}
      if(LqlljZPZcd == true){LqlljZPZcd = false;}
      if(CQMJuAbBaP == true){CQMJuAbBaP = false;}
      if(YUcUrgaCaE == true){YUcUrgaCaE = false;}
      if(XtJBXDkxjH == true){XtJBXDkxjH = false;}
      if(lyONAeqeYs == true){lyONAeqeYs = false;}
      if(BCjChpOQtC == true){BCjChpOQtC = false;}
      if(yNzYFIGLlr == true){yNzYFIGLlr = false;}
      if(OdRSdaFPTM == true){OdRSdaFPTM = false;}
      if(pwchDVKHSg == true){pwchDVKHSg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEAHSKUFLS
{ 
  void biFUcsyWyI()
  { 
      bool lnFGspOWTa = false;
      bool ycirUjYPil = false;
      bool pCMoFrEFQr = false;
      bool xUmhUmEdGZ = false;
      bool YwHtLirEtr = false;
      bool XKPpzjbQAA = false;
      bool kIFaccoBWh = false;
      bool fuJINtuRcW = false;
      bool AALYUmFwik = false;
      bool LmcFoPqfRh = false;
      bool sqhLMcAGbF = false;
      bool oJmcAkxgGp = false;
      bool XrSlWrRDTy = false;
      bool DOAudJRzLr = false;
      bool lyUcuBAzFD = false;
      bool SKZaKAXwoU = false;
      bool KwmdBZIqzq = false;
      bool SxUODZXopU = false;
      bool qRyPfsoYkc = false;
      bool kVKqgoKpbV = false;
      string yOSJgWKShL;
      string OeALglUjOB;
      string sqMfUtFsdl;
      string reHixeMWhi;
      string FFbXxHdrYV;
      string GUJCjGBlom;
      string QQouSjWRNB;
      string ZxCfwmOnhM;
      string QNTIfXUFzq;
      string dahtRnQfEN;
      string jLdXwJRdGw;
      string rNDbWDxgPu;
      string ORSWXzPINH;
      string WijUbEiwLV;
      string GpyCyPWFXN;
      string qiPIzRsHzx;
      string sJPzZIchzR;
      string UBUsoXTPXH;
      string bJjAPmSaVK;
      string LbwObwaycp;
      if(yOSJgWKShL == jLdXwJRdGw){lnFGspOWTa = true;}
      else if(jLdXwJRdGw == yOSJgWKShL){sqhLMcAGbF = true;}
      if(OeALglUjOB == rNDbWDxgPu){ycirUjYPil = true;}
      else if(rNDbWDxgPu == OeALglUjOB){oJmcAkxgGp = true;}
      if(sqMfUtFsdl == ORSWXzPINH){pCMoFrEFQr = true;}
      else if(ORSWXzPINH == sqMfUtFsdl){XrSlWrRDTy = true;}
      if(reHixeMWhi == WijUbEiwLV){xUmhUmEdGZ = true;}
      else if(WijUbEiwLV == reHixeMWhi){DOAudJRzLr = true;}
      if(FFbXxHdrYV == GpyCyPWFXN){YwHtLirEtr = true;}
      else if(GpyCyPWFXN == FFbXxHdrYV){lyUcuBAzFD = true;}
      if(GUJCjGBlom == qiPIzRsHzx){XKPpzjbQAA = true;}
      else if(qiPIzRsHzx == GUJCjGBlom){SKZaKAXwoU = true;}
      if(QQouSjWRNB == sJPzZIchzR){kIFaccoBWh = true;}
      else if(sJPzZIchzR == QQouSjWRNB){KwmdBZIqzq = true;}
      if(ZxCfwmOnhM == UBUsoXTPXH){fuJINtuRcW = true;}
      if(QNTIfXUFzq == bJjAPmSaVK){AALYUmFwik = true;}
      if(dahtRnQfEN == LbwObwaycp){LmcFoPqfRh = true;}
      while(UBUsoXTPXH == ZxCfwmOnhM){SxUODZXopU = true;}
      while(bJjAPmSaVK == bJjAPmSaVK){qRyPfsoYkc = true;}
      while(LbwObwaycp == LbwObwaycp){kVKqgoKpbV = true;}
      if(lnFGspOWTa == true){lnFGspOWTa = false;}
      if(ycirUjYPil == true){ycirUjYPil = false;}
      if(pCMoFrEFQr == true){pCMoFrEFQr = false;}
      if(xUmhUmEdGZ == true){xUmhUmEdGZ = false;}
      if(YwHtLirEtr == true){YwHtLirEtr = false;}
      if(XKPpzjbQAA == true){XKPpzjbQAA = false;}
      if(kIFaccoBWh == true){kIFaccoBWh = false;}
      if(fuJINtuRcW == true){fuJINtuRcW = false;}
      if(AALYUmFwik == true){AALYUmFwik = false;}
      if(LmcFoPqfRh == true){LmcFoPqfRh = false;}
      if(sqhLMcAGbF == true){sqhLMcAGbF = false;}
      if(oJmcAkxgGp == true){oJmcAkxgGp = false;}
      if(XrSlWrRDTy == true){XrSlWrRDTy = false;}
      if(DOAudJRzLr == true){DOAudJRzLr = false;}
      if(lyUcuBAzFD == true){lyUcuBAzFD = false;}
      if(SKZaKAXwoU == true){SKZaKAXwoU = false;}
      if(KwmdBZIqzq == true){KwmdBZIqzq = false;}
      if(SxUODZXopU == true){SxUODZXopU = false;}
      if(qRyPfsoYkc == true){qRyPfsoYkc = false;}
      if(kVKqgoKpbV == true){kVKqgoKpbV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHTBXWNTTO
{ 
  void wRpcgCUIyi()
  { 
      bool IYDtQYVeBL = false;
      bool QwnyaOorXE = false;
      bool eyyTtlZeZp = false;
      bool zVCSDkbMzf = false;
      bool xQfgcNWncJ = false;
      bool PAFlcJajAd = false;
      bool zqEKLttUuo = false;
      bool lbrrGNSQqg = false;
      bool OkCQZzQQps = false;
      bool KqMVgGLUVh = false;
      bool SBsmWnIMfO = false;
      bool qKsTPOnnjM = false;
      bool ddeCetPWLz = false;
      bool BxtINMrPsl = false;
      bool qDkaBzysFR = false;
      bool RWjJDoVpHc = false;
      bool YlBfNsPjFC = false;
      bool WYuyVasEAe = false;
      bool wVQsgdNkFX = false;
      bool pBHQNFBEMH = false;
      string MEMjWcXeJU;
      string VMkyaaYRQu;
      string LpVahTKJBj;
      string RnfOGernHC;
      string JHUxeCUOEx;
      string aNAFBWhkBD;
      string SOdZCggVru;
      string ijJNkDUYwe;
      string zuFEJEmaNj;
      string wGmDjuduty;
      string VyWIOqDlTy;
      string BJoVEWJYQx;
      string sGIIybwGdp;
      string YZdxIAYwpS;
      string BBGPhmQQyN;
      string kFdxEPpNJl;
      string twIcYaeqME;
      string xMiyurzsZL;
      string KfHPETwgss;
      string KLmDXFrdpH;
      if(MEMjWcXeJU == VyWIOqDlTy){IYDtQYVeBL = true;}
      else if(VyWIOqDlTy == MEMjWcXeJU){SBsmWnIMfO = true;}
      if(VMkyaaYRQu == BJoVEWJYQx){QwnyaOorXE = true;}
      else if(BJoVEWJYQx == VMkyaaYRQu){qKsTPOnnjM = true;}
      if(LpVahTKJBj == sGIIybwGdp){eyyTtlZeZp = true;}
      else if(sGIIybwGdp == LpVahTKJBj){ddeCetPWLz = true;}
      if(RnfOGernHC == YZdxIAYwpS){zVCSDkbMzf = true;}
      else if(YZdxIAYwpS == RnfOGernHC){BxtINMrPsl = true;}
      if(JHUxeCUOEx == BBGPhmQQyN){xQfgcNWncJ = true;}
      else if(BBGPhmQQyN == JHUxeCUOEx){qDkaBzysFR = true;}
      if(aNAFBWhkBD == kFdxEPpNJl){PAFlcJajAd = true;}
      else if(kFdxEPpNJl == aNAFBWhkBD){RWjJDoVpHc = true;}
      if(SOdZCggVru == twIcYaeqME){zqEKLttUuo = true;}
      else if(twIcYaeqME == SOdZCggVru){YlBfNsPjFC = true;}
      if(ijJNkDUYwe == xMiyurzsZL){lbrrGNSQqg = true;}
      if(zuFEJEmaNj == KfHPETwgss){OkCQZzQQps = true;}
      if(wGmDjuduty == KLmDXFrdpH){KqMVgGLUVh = true;}
      while(xMiyurzsZL == ijJNkDUYwe){WYuyVasEAe = true;}
      while(KfHPETwgss == KfHPETwgss){wVQsgdNkFX = true;}
      while(KLmDXFrdpH == KLmDXFrdpH){pBHQNFBEMH = true;}
      if(IYDtQYVeBL == true){IYDtQYVeBL = false;}
      if(QwnyaOorXE == true){QwnyaOorXE = false;}
      if(eyyTtlZeZp == true){eyyTtlZeZp = false;}
      if(zVCSDkbMzf == true){zVCSDkbMzf = false;}
      if(xQfgcNWncJ == true){xQfgcNWncJ = false;}
      if(PAFlcJajAd == true){PAFlcJajAd = false;}
      if(zqEKLttUuo == true){zqEKLttUuo = false;}
      if(lbrrGNSQqg == true){lbrrGNSQqg = false;}
      if(OkCQZzQQps == true){OkCQZzQQps = false;}
      if(KqMVgGLUVh == true){KqMVgGLUVh = false;}
      if(SBsmWnIMfO == true){SBsmWnIMfO = false;}
      if(qKsTPOnnjM == true){qKsTPOnnjM = false;}
      if(ddeCetPWLz == true){ddeCetPWLz = false;}
      if(BxtINMrPsl == true){BxtINMrPsl = false;}
      if(qDkaBzysFR == true){qDkaBzysFR = false;}
      if(RWjJDoVpHc == true){RWjJDoVpHc = false;}
      if(YlBfNsPjFC == true){YlBfNsPjFC = false;}
      if(WYuyVasEAe == true){WYuyVasEAe = false;}
      if(wVQsgdNkFX == true){wVQsgdNkFX = false;}
      if(pBHQNFBEMH == true){pBHQNFBEMH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSNRPVCLSZ
{ 
  void FtxueNhQGJ()
  { 
      bool XptjiLEQsB = false;
      bool LixCLLZQMC = false;
      bool EOoxzzHDGz = false;
      bool NmiDsELoSR = false;
      bool VJDhMafNyx = false;
      bool UsamCIAxkj = false;
      bool DAKtmXAsJG = false;
      bool zjyuguLGjX = false;
      bool TsFIdUMuAk = false;
      bool DODiNUyJto = false;
      bool alEqxjteGH = false;
      bool wsMNPKuBPR = false;
      bool KErXDjfPhM = false;
      bool xBLuxgnNKt = false;
      bool ZgosnJBpSC = false;
      bool YwscdVtgnN = false;
      bool DextKuhRQi = false;
      bool WhqVrdPzis = false;
      bool ipxfmAIiRb = false;
      bool mHYxptjuhs = false;
      string PzkXmhcITb;
      string kebMZTzHVR;
      string tApTlsZLzR;
      string ZaqynqNhQh;
      string KFXdjgbfEU;
      string EKSKKOJRls;
      string IQICCJmdXi;
      string FRqmHocLjF;
      string QsGeMOIgmY;
      string hwwWZtwVaa;
      string syHVOmTfDU;
      string lxhgbOJdon;
      string AGpyBIVTMM;
      string rGkILSlkPZ;
      string tcdRmjOPtL;
      string jSfmZmHITF;
      string RzSpceMYUJ;
      string bYNOsXbXLQ;
      string tFZBcZaxiX;
      string KcQJItJnoH;
      if(PzkXmhcITb == syHVOmTfDU){XptjiLEQsB = true;}
      else if(syHVOmTfDU == PzkXmhcITb){alEqxjteGH = true;}
      if(kebMZTzHVR == lxhgbOJdon){LixCLLZQMC = true;}
      else if(lxhgbOJdon == kebMZTzHVR){wsMNPKuBPR = true;}
      if(tApTlsZLzR == AGpyBIVTMM){EOoxzzHDGz = true;}
      else if(AGpyBIVTMM == tApTlsZLzR){KErXDjfPhM = true;}
      if(ZaqynqNhQh == rGkILSlkPZ){NmiDsELoSR = true;}
      else if(rGkILSlkPZ == ZaqynqNhQh){xBLuxgnNKt = true;}
      if(KFXdjgbfEU == tcdRmjOPtL){VJDhMafNyx = true;}
      else if(tcdRmjOPtL == KFXdjgbfEU){ZgosnJBpSC = true;}
      if(EKSKKOJRls == jSfmZmHITF){UsamCIAxkj = true;}
      else if(jSfmZmHITF == EKSKKOJRls){YwscdVtgnN = true;}
      if(IQICCJmdXi == RzSpceMYUJ){DAKtmXAsJG = true;}
      else if(RzSpceMYUJ == IQICCJmdXi){DextKuhRQi = true;}
      if(FRqmHocLjF == bYNOsXbXLQ){zjyuguLGjX = true;}
      if(QsGeMOIgmY == tFZBcZaxiX){TsFIdUMuAk = true;}
      if(hwwWZtwVaa == KcQJItJnoH){DODiNUyJto = true;}
      while(bYNOsXbXLQ == FRqmHocLjF){WhqVrdPzis = true;}
      while(tFZBcZaxiX == tFZBcZaxiX){ipxfmAIiRb = true;}
      while(KcQJItJnoH == KcQJItJnoH){mHYxptjuhs = true;}
      if(XptjiLEQsB == true){XptjiLEQsB = false;}
      if(LixCLLZQMC == true){LixCLLZQMC = false;}
      if(EOoxzzHDGz == true){EOoxzzHDGz = false;}
      if(NmiDsELoSR == true){NmiDsELoSR = false;}
      if(VJDhMafNyx == true){VJDhMafNyx = false;}
      if(UsamCIAxkj == true){UsamCIAxkj = false;}
      if(DAKtmXAsJG == true){DAKtmXAsJG = false;}
      if(zjyuguLGjX == true){zjyuguLGjX = false;}
      if(TsFIdUMuAk == true){TsFIdUMuAk = false;}
      if(DODiNUyJto == true){DODiNUyJto = false;}
      if(alEqxjteGH == true){alEqxjteGH = false;}
      if(wsMNPKuBPR == true){wsMNPKuBPR = false;}
      if(KErXDjfPhM == true){KErXDjfPhM = false;}
      if(xBLuxgnNKt == true){xBLuxgnNKt = false;}
      if(ZgosnJBpSC == true){ZgosnJBpSC = false;}
      if(YwscdVtgnN == true){YwscdVtgnN = false;}
      if(DextKuhRQi == true){DextKuhRQi = false;}
      if(WhqVrdPzis == true){WhqVrdPzis = false;}
      if(ipxfmAIiRb == true){ipxfmAIiRb = false;}
      if(mHYxptjuhs == true){mHYxptjuhs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LACOCRJOOE
{ 
  void dNxULiVfol()
  { 
      bool qVhGyDpXqP = false;
      bool ajSOjbqyFO = false;
      bool neWIzmQpGS = false;
      bool RMhbWEkJIf = false;
      bool dUQMMjBnlc = false;
      bool OUgHQLzYGK = false;
      bool lAQXyNCqqf = false;
      bool qhpYkSOKuP = false;
      bool lbEcEwfZLK = false;
      bool FLCysdErOz = false;
      bool gKxGlgeHWy = false;
      bool xodpXKwnTB = false;
      bool gcefaeeqfH = false;
      bool NVuwiaexpW = false;
      bool QXDNNPhLZi = false;
      bool hQYNREeQfH = false;
      bool BmbPjbsgHx = false;
      bool eyxwjJZRSK = false;
      bool wSRwZxxhee = false;
      bool uORiVcwncl = false;
      string XZUrWoFYjy;
      string GANyUQAiAB;
      string xjgBSjWFqa;
      string AFAnijTNpC;
      string WcICLCZhFD;
      string eoPbamrTZm;
      string RzgJyAAYOk;
      string wlrxeTbdoP;
      string JnAnuKpYNw;
      string rAnDjWwyEL;
      string CASUGswRxG;
      string KNdJcdzsNm;
      string JbLSrwxoMH;
      string XdZdNJUegB;
      string NYbGkeVdZG;
      string XDjQBZoAbK;
      string uHEoignzwT;
      string ITMMZkzEgN;
      string ZTPGjUsIcm;
      string TUCVFGTlWE;
      if(XZUrWoFYjy == CASUGswRxG){qVhGyDpXqP = true;}
      else if(CASUGswRxG == XZUrWoFYjy){gKxGlgeHWy = true;}
      if(GANyUQAiAB == KNdJcdzsNm){ajSOjbqyFO = true;}
      else if(KNdJcdzsNm == GANyUQAiAB){xodpXKwnTB = true;}
      if(xjgBSjWFqa == JbLSrwxoMH){neWIzmQpGS = true;}
      else if(JbLSrwxoMH == xjgBSjWFqa){gcefaeeqfH = true;}
      if(AFAnijTNpC == XdZdNJUegB){RMhbWEkJIf = true;}
      else if(XdZdNJUegB == AFAnijTNpC){NVuwiaexpW = true;}
      if(WcICLCZhFD == NYbGkeVdZG){dUQMMjBnlc = true;}
      else if(NYbGkeVdZG == WcICLCZhFD){QXDNNPhLZi = true;}
      if(eoPbamrTZm == XDjQBZoAbK){OUgHQLzYGK = true;}
      else if(XDjQBZoAbK == eoPbamrTZm){hQYNREeQfH = true;}
      if(RzgJyAAYOk == uHEoignzwT){lAQXyNCqqf = true;}
      else if(uHEoignzwT == RzgJyAAYOk){BmbPjbsgHx = true;}
      if(wlrxeTbdoP == ITMMZkzEgN){qhpYkSOKuP = true;}
      if(JnAnuKpYNw == ZTPGjUsIcm){lbEcEwfZLK = true;}
      if(rAnDjWwyEL == TUCVFGTlWE){FLCysdErOz = true;}
      while(ITMMZkzEgN == wlrxeTbdoP){eyxwjJZRSK = true;}
      while(ZTPGjUsIcm == ZTPGjUsIcm){wSRwZxxhee = true;}
      while(TUCVFGTlWE == TUCVFGTlWE){uORiVcwncl = true;}
      if(qVhGyDpXqP == true){qVhGyDpXqP = false;}
      if(ajSOjbqyFO == true){ajSOjbqyFO = false;}
      if(neWIzmQpGS == true){neWIzmQpGS = false;}
      if(RMhbWEkJIf == true){RMhbWEkJIf = false;}
      if(dUQMMjBnlc == true){dUQMMjBnlc = false;}
      if(OUgHQLzYGK == true){OUgHQLzYGK = false;}
      if(lAQXyNCqqf == true){lAQXyNCqqf = false;}
      if(qhpYkSOKuP == true){qhpYkSOKuP = false;}
      if(lbEcEwfZLK == true){lbEcEwfZLK = false;}
      if(FLCysdErOz == true){FLCysdErOz = false;}
      if(gKxGlgeHWy == true){gKxGlgeHWy = false;}
      if(xodpXKwnTB == true){xodpXKwnTB = false;}
      if(gcefaeeqfH == true){gcefaeeqfH = false;}
      if(NVuwiaexpW == true){NVuwiaexpW = false;}
      if(QXDNNPhLZi == true){QXDNNPhLZi = false;}
      if(hQYNREeQfH == true){hQYNREeQfH = false;}
      if(BmbPjbsgHx == true){BmbPjbsgHx = false;}
      if(eyxwjJZRSK == true){eyxwjJZRSK = false;}
      if(wSRwZxxhee == true){wSRwZxxhee = false;}
      if(uORiVcwncl == true){uORiVcwncl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDIIPIZRHB
{ 
  void XFczOaVpaa()
  { 
      bool iVoYEIakko = false;
      bool KujQVsNRsu = false;
      bool QiigAUrwiC = false;
      bool dnjkcdGoHW = false;
      bool lmDlXCYdpf = false;
      bool aWjDBzmIYi = false;
      bool PeBhKWKznq = false;
      bool lXKVIdfwIx = false;
      bool uOFDbHDgic = false;
      bool qyQXGHkUaA = false;
      bool rZoysCMOtX = false;
      bool TpzbnBYyGD = false;
      bool SdPKAnHmOB = false;
      bool rKVIEVYHJZ = false;
      bool tolLJByniF = false;
      bool imOXgOJeyE = false;
      bool tZzsfJUqWS = false;
      bool bQnfIdqEBy = false;
      bool pTDJREuyap = false;
      bool LtIEfUpseA = false;
      string XyYIfyFPGx;
      string qLghuEwynU;
      string RfLAZLXbqd;
      string RPnhHhyOQj;
      string kxuMVSRZIH;
      string YrakXrmYhU;
      string ZdYceaWzaN;
      string FhgDjTjydH;
      string txSiFZoDJO;
      string uZfwKHXRht;
      string uSzuBpKWBD;
      string HntaZbKoXF;
      string lToLSfBjsb;
      string uSQjLbyXhO;
      string ORCGHGfFWh;
      string witbIbdncV;
      string oacYHoXJPy;
      string dmHIqTQhDL;
      string AwNLfMXnai;
      string yJtLZnocyS;
      if(XyYIfyFPGx == uSzuBpKWBD){iVoYEIakko = true;}
      else if(uSzuBpKWBD == XyYIfyFPGx){rZoysCMOtX = true;}
      if(qLghuEwynU == HntaZbKoXF){KujQVsNRsu = true;}
      else if(HntaZbKoXF == qLghuEwynU){TpzbnBYyGD = true;}
      if(RfLAZLXbqd == lToLSfBjsb){QiigAUrwiC = true;}
      else if(lToLSfBjsb == RfLAZLXbqd){SdPKAnHmOB = true;}
      if(RPnhHhyOQj == uSQjLbyXhO){dnjkcdGoHW = true;}
      else if(uSQjLbyXhO == RPnhHhyOQj){rKVIEVYHJZ = true;}
      if(kxuMVSRZIH == ORCGHGfFWh){lmDlXCYdpf = true;}
      else if(ORCGHGfFWh == kxuMVSRZIH){tolLJByniF = true;}
      if(YrakXrmYhU == witbIbdncV){aWjDBzmIYi = true;}
      else if(witbIbdncV == YrakXrmYhU){imOXgOJeyE = true;}
      if(ZdYceaWzaN == oacYHoXJPy){PeBhKWKznq = true;}
      else if(oacYHoXJPy == ZdYceaWzaN){tZzsfJUqWS = true;}
      if(FhgDjTjydH == dmHIqTQhDL){lXKVIdfwIx = true;}
      if(txSiFZoDJO == AwNLfMXnai){uOFDbHDgic = true;}
      if(uZfwKHXRht == yJtLZnocyS){qyQXGHkUaA = true;}
      while(dmHIqTQhDL == FhgDjTjydH){bQnfIdqEBy = true;}
      while(AwNLfMXnai == AwNLfMXnai){pTDJREuyap = true;}
      while(yJtLZnocyS == yJtLZnocyS){LtIEfUpseA = true;}
      if(iVoYEIakko == true){iVoYEIakko = false;}
      if(KujQVsNRsu == true){KujQVsNRsu = false;}
      if(QiigAUrwiC == true){QiigAUrwiC = false;}
      if(dnjkcdGoHW == true){dnjkcdGoHW = false;}
      if(lmDlXCYdpf == true){lmDlXCYdpf = false;}
      if(aWjDBzmIYi == true){aWjDBzmIYi = false;}
      if(PeBhKWKznq == true){PeBhKWKznq = false;}
      if(lXKVIdfwIx == true){lXKVIdfwIx = false;}
      if(uOFDbHDgic == true){uOFDbHDgic = false;}
      if(qyQXGHkUaA == true){qyQXGHkUaA = false;}
      if(rZoysCMOtX == true){rZoysCMOtX = false;}
      if(TpzbnBYyGD == true){TpzbnBYyGD = false;}
      if(SdPKAnHmOB == true){SdPKAnHmOB = false;}
      if(rKVIEVYHJZ == true){rKVIEVYHJZ = false;}
      if(tolLJByniF == true){tolLJByniF = false;}
      if(imOXgOJeyE == true){imOXgOJeyE = false;}
      if(tZzsfJUqWS == true){tZzsfJUqWS = false;}
      if(bQnfIdqEBy == true){bQnfIdqEBy = false;}
      if(pTDJREuyap == true){pTDJREuyap = false;}
      if(LtIEfUpseA == true){LtIEfUpseA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUHUVYDUEL
{ 
  void reWMPmZhGq()
  { 
      bool pGtnGYrxVD = false;
      bool zItXQtJbGd = false;
      bool FrIlnQhDFV = false;
      bool yTpQUxaBfF = false;
      bool uoEhnrlXoW = false;
      bool JAVNJyxHzo = false;
      bool pnrzEfRdCS = false;
      bool SHuAiQnZxu = false;
      bool dKNhMxycHW = false;
      bool zTBpOGwEcI = false;
      bool ZIVWEBEUer = false;
      bool KWJDLfaJmG = false;
      bool goVeSyFEkb = false;
      bool TiwoVVnqdK = false;
      bool scxOMcJxei = false;
      bool fmQVajlpDF = false;
      bool uzjDXaZUho = false;
      bool qiebNErHSp = false;
      bool oHYCwgRaNk = false;
      bool iynYOsrtpk = false;
      string MGBTZGObuL;
      string YfGZwBmpnA;
      string ylDcaReVqH;
      string YGsygOjVPl;
      string FWJDOpqHlp;
      string VpINhaDYsH;
      string bskmmRmHsg;
      string QRZBtbbANk;
      string aWjAkhyePF;
      string LLbIKMlVPx;
      string CiOEZEQGSG;
      string yCKIfFJjCF;
      string SHrmUEoRqh;
      string oGjPhrHeaf;
      string RrMJHJBTbE;
      string DBTJdtqaiU;
      string PyOkQrStZn;
      string xdJVnauhfL;
      string DVomemlZlm;
      string AguFQScbrO;
      if(MGBTZGObuL == CiOEZEQGSG){pGtnGYrxVD = true;}
      else if(CiOEZEQGSG == MGBTZGObuL){ZIVWEBEUer = true;}
      if(YfGZwBmpnA == yCKIfFJjCF){zItXQtJbGd = true;}
      else if(yCKIfFJjCF == YfGZwBmpnA){KWJDLfaJmG = true;}
      if(ylDcaReVqH == SHrmUEoRqh){FrIlnQhDFV = true;}
      else if(SHrmUEoRqh == ylDcaReVqH){goVeSyFEkb = true;}
      if(YGsygOjVPl == oGjPhrHeaf){yTpQUxaBfF = true;}
      else if(oGjPhrHeaf == YGsygOjVPl){TiwoVVnqdK = true;}
      if(FWJDOpqHlp == RrMJHJBTbE){uoEhnrlXoW = true;}
      else if(RrMJHJBTbE == FWJDOpqHlp){scxOMcJxei = true;}
      if(VpINhaDYsH == DBTJdtqaiU){JAVNJyxHzo = true;}
      else if(DBTJdtqaiU == VpINhaDYsH){fmQVajlpDF = true;}
      if(bskmmRmHsg == PyOkQrStZn){pnrzEfRdCS = true;}
      else if(PyOkQrStZn == bskmmRmHsg){uzjDXaZUho = true;}
      if(QRZBtbbANk == xdJVnauhfL){SHuAiQnZxu = true;}
      if(aWjAkhyePF == DVomemlZlm){dKNhMxycHW = true;}
      if(LLbIKMlVPx == AguFQScbrO){zTBpOGwEcI = true;}
      while(xdJVnauhfL == QRZBtbbANk){qiebNErHSp = true;}
      while(DVomemlZlm == DVomemlZlm){oHYCwgRaNk = true;}
      while(AguFQScbrO == AguFQScbrO){iynYOsrtpk = true;}
      if(pGtnGYrxVD == true){pGtnGYrxVD = false;}
      if(zItXQtJbGd == true){zItXQtJbGd = false;}
      if(FrIlnQhDFV == true){FrIlnQhDFV = false;}
      if(yTpQUxaBfF == true){yTpQUxaBfF = false;}
      if(uoEhnrlXoW == true){uoEhnrlXoW = false;}
      if(JAVNJyxHzo == true){JAVNJyxHzo = false;}
      if(pnrzEfRdCS == true){pnrzEfRdCS = false;}
      if(SHuAiQnZxu == true){SHuAiQnZxu = false;}
      if(dKNhMxycHW == true){dKNhMxycHW = false;}
      if(zTBpOGwEcI == true){zTBpOGwEcI = false;}
      if(ZIVWEBEUer == true){ZIVWEBEUer = false;}
      if(KWJDLfaJmG == true){KWJDLfaJmG = false;}
      if(goVeSyFEkb == true){goVeSyFEkb = false;}
      if(TiwoVVnqdK == true){TiwoVVnqdK = false;}
      if(scxOMcJxei == true){scxOMcJxei = false;}
      if(fmQVajlpDF == true){fmQVajlpDF = false;}
      if(uzjDXaZUho == true){uzjDXaZUho = false;}
      if(qiebNErHSp == true){qiebNErHSp = false;}
      if(oHYCwgRaNk == true){oHYCwgRaNk = false;}
      if(iynYOsrtpk == true){iynYOsrtpk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OZEZVPYKXM
{ 
  void IyQXAePwLd()
  { 
      bool ZgQMCKJLYm = false;
      bool zdTBAfrqeb = false;
      bool ylRyUMGlrp = false;
      bool fJEsJFkubz = false;
      bool DxZXrzFBCq = false;
      bool fdBaPmORqo = false;
      bool EXTiGpZaqt = false;
      bool twOfXBMtGV = false;
      bool GEiAJBIdcW = false;
      bool qSDmufdqRC = false;
      bool ZeKIwiOVDO = false;
      bool aULVhznSYE = false;
      bool huxUDbsbjq = false;
      bool XUbEwbtaEa = false;
      bool llZOwVHhEu = false;
      bool rKRMUdgoEU = false;
      bool pmkLpFrHZG = false;
      bool EMNxRuUiYg = false;
      bool TKWnzMCPjR = false;
      bool uEVijzAOXp = false;
      string xAFLtmqGgk;
      string yRdNukegRe;
      string ZgQszetazV;
      string FVLjaSzqnU;
      string hkFFKLepIX;
      string bMmSqQjLMO;
      string rPHLecGslc;
      string lmswxobLhm;
      string AESbsrhrsK;
      string ineYcRdsZh;
      string EkDekoTpVB;
      string oXcYNnxeSl;
      string tNzbtyHTTe;
      string LhlzhPAmpE;
      string YrWrUKKGLo;
      string UyZmnplajm;
      string gAWpoGkcpy;
      string mJnONBqHHi;
      string mBIeKNIzKr;
      string cZCCWXVgCO;
      if(xAFLtmqGgk == EkDekoTpVB){ZgQMCKJLYm = true;}
      else if(EkDekoTpVB == xAFLtmqGgk){ZeKIwiOVDO = true;}
      if(yRdNukegRe == oXcYNnxeSl){zdTBAfrqeb = true;}
      else if(oXcYNnxeSl == yRdNukegRe){aULVhznSYE = true;}
      if(ZgQszetazV == tNzbtyHTTe){ylRyUMGlrp = true;}
      else if(tNzbtyHTTe == ZgQszetazV){huxUDbsbjq = true;}
      if(FVLjaSzqnU == LhlzhPAmpE){fJEsJFkubz = true;}
      else if(LhlzhPAmpE == FVLjaSzqnU){XUbEwbtaEa = true;}
      if(hkFFKLepIX == YrWrUKKGLo){DxZXrzFBCq = true;}
      else if(YrWrUKKGLo == hkFFKLepIX){llZOwVHhEu = true;}
      if(bMmSqQjLMO == UyZmnplajm){fdBaPmORqo = true;}
      else if(UyZmnplajm == bMmSqQjLMO){rKRMUdgoEU = true;}
      if(rPHLecGslc == gAWpoGkcpy){EXTiGpZaqt = true;}
      else if(gAWpoGkcpy == rPHLecGslc){pmkLpFrHZG = true;}
      if(lmswxobLhm == mJnONBqHHi){twOfXBMtGV = true;}
      if(AESbsrhrsK == mBIeKNIzKr){GEiAJBIdcW = true;}
      if(ineYcRdsZh == cZCCWXVgCO){qSDmufdqRC = true;}
      while(mJnONBqHHi == lmswxobLhm){EMNxRuUiYg = true;}
      while(mBIeKNIzKr == mBIeKNIzKr){TKWnzMCPjR = true;}
      while(cZCCWXVgCO == cZCCWXVgCO){uEVijzAOXp = true;}
      if(ZgQMCKJLYm == true){ZgQMCKJLYm = false;}
      if(zdTBAfrqeb == true){zdTBAfrqeb = false;}
      if(ylRyUMGlrp == true){ylRyUMGlrp = false;}
      if(fJEsJFkubz == true){fJEsJFkubz = false;}
      if(DxZXrzFBCq == true){DxZXrzFBCq = false;}
      if(fdBaPmORqo == true){fdBaPmORqo = false;}
      if(EXTiGpZaqt == true){EXTiGpZaqt = false;}
      if(twOfXBMtGV == true){twOfXBMtGV = false;}
      if(GEiAJBIdcW == true){GEiAJBIdcW = false;}
      if(qSDmufdqRC == true){qSDmufdqRC = false;}
      if(ZeKIwiOVDO == true){ZeKIwiOVDO = false;}
      if(aULVhznSYE == true){aULVhznSYE = false;}
      if(huxUDbsbjq == true){huxUDbsbjq = false;}
      if(XUbEwbtaEa == true){XUbEwbtaEa = false;}
      if(llZOwVHhEu == true){llZOwVHhEu = false;}
      if(rKRMUdgoEU == true){rKRMUdgoEU = false;}
      if(pmkLpFrHZG == true){pmkLpFrHZG = false;}
      if(EMNxRuUiYg == true){EMNxRuUiYg = false;}
      if(TKWnzMCPjR == true){TKWnzMCPjR = false;}
      if(uEVijzAOXp == true){uEVijzAOXp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJHNOCISSD
{ 
  void shytJWaKAo()
  { 
      bool HyXtwAKFgZ = false;
      bool OlZLkjPYmH = false;
      bool RnCwmuXnVJ = false;
      bool YiilhBFFzH = false;
      bool iQwQguLXrX = false;
      bool UTrFfTubHA = false;
      bool cVjWAeCndj = false;
      bool eJYfYArlOq = false;
      bool izwynFqdFN = false;
      bool FdyydNgYPB = false;
      bool sXtHsLtMgf = false;
      bool bJMPRdYkht = false;
      bool mXhQeAKZBK = false;
      bool SSVMxLFnFc = false;
      bool KewZkuRhgA = false;
      bool owpVOUoccr = false;
      bool ATKWMJnzSF = false;
      bool YjeFiIbHei = false;
      bool icsAVWcAyc = false;
      bool VbLNcpTZNb = false;
      string sUiqMhaohE;
      string OtthuxIQyX;
      string IEYHjMXbUF;
      string beSrZnrkAR;
      string CcMyEszqXf;
      string duZgDoubGA;
      string KyUbbiaCIH;
      string FWQgUeraCp;
      string NfDnbfFlnj;
      string sPeAHDIjWU;
      string RwiQZGesLY;
      string xUZPldufAu;
      string doNXOorPYQ;
      string WHDgYQxmNV;
      string BMZPmYpOOc;
      string IbjaqciKCk;
      string NPTuCoQrqU;
      string gIRdtROxjp;
      string zcAuHtWcpu;
      string hljcHkreNy;
      if(sUiqMhaohE == RwiQZGesLY){HyXtwAKFgZ = true;}
      else if(RwiQZGesLY == sUiqMhaohE){sXtHsLtMgf = true;}
      if(OtthuxIQyX == xUZPldufAu){OlZLkjPYmH = true;}
      else if(xUZPldufAu == OtthuxIQyX){bJMPRdYkht = true;}
      if(IEYHjMXbUF == doNXOorPYQ){RnCwmuXnVJ = true;}
      else if(doNXOorPYQ == IEYHjMXbUF){mXhQeAKZBK = true;}
      if(beSrZnrkAR == WHDgYQxmNV){YiilhBFFzH = true;}
      else if(WHDgYQxmNV == beSrZnrkAR){SSVMxLFnFc = true;}
      if(CcMyEszqXf == BMZPmYpOOc){iQwQguLXrX = true;}
      else if(BMZPmYpOOc == CcMyEszqXf){KewZkuRhgA = true;}
      if(duZgDoubGA == IbjaqciKCk){UTrFfTubHA = true;}
      else if(IbjaqciKCk == duZgDoubGA){owpVOUoccr = true;}
      if(KyUbbiaCIH == NPTuCoQrqU){cVjWAeCndj = true;}
      else if(NPTuCoQrqU == KyUbbiaCIH){ATKWMJnzSF = true;}
      if(FWQgUeraCp == gIRdtROxjp){eJYfYArlOq = true;}
      if(NfDnbfFlnj == zcAuHtWcpu){izwynFqdFN = true;}
      if(sPeAHDIjWU == hljcHkreNy){FdyydNgYPB = true;}
      while(gIRdtROxjp == FWQgUeraCp){YjeFiIbHei = true;}
      while(zcAuHtWcpu == zcAuHtWcpu){icsAVWcAyc = true;}
      while(hljcHkreNy == hljcHkreNy){VbLNcpTZNb = true;}
      if(HyXtwAKFgZ == true){HyXtwAKFgZ = false;}
      if(OlZLkjPYmH == true){OlZLkjPYmH = false;}
      if(RnCwmuXnVJ == true){RnCwmuXnVJ = false;}
      if(YiilhBFFzH == true){YiilhBFFzH = false;}
      if(iQwQguLXrX == true){iQwQguLXrX = false;}
      if(UTrFfTubHA == true){UTrFfTubHA = false;}
      if(cVjWAeCndj == true){cVjWAeCndj = false;}
      if(eJYfYArlOq == true){eJYfYArlOq = false;}
      if(izwynFqdFN == true){izwynFqdFN = false;}
      if(FdyydNgYPB == true){FdyydNgYPB = false;}
      if(sXtHsLtMgf == true){sXtHsLtMgf = false;}
      if(bJMPRdYkht == true){bJMPRdYkht = false;}
      if(mXhQeAKZBK == true){mXhQeAKZBK = false;}
      if(SSVMxLFnFc == true){SSVMxLFnFc = false;}
      if(KewZkuRhgA == true){KewZkuRhgA = false;}
      if(owpVOUoccr == true){owpVOUoccr = false;}
      if(ATKWMJnzSF == true){ATKWMJnzSF = false;}
      if(YjeFiIbHei == true){YjeFiIbHei = false;}
      if(icsAVWcAyc == true){icsAVWcAyc = false;}
      if(VbLNcpTZNb == true){VbLNcpTZNb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALYCEYUGOT
{ 
  void mhwsfRpcgt()
  { 
      bool rSOUkfyJig = false;
      bool lOWlNeAWrW = false;
      bool rXRfbXVhWY = false;
      bool stTyrKkTaG = false;
      bool HcyzMrtGEW = false;
      bool oVrjATAhrM = false;
      bool KPlKnquXtC = false;
      bool tfwlOOYSTi = false;
      bool dOdAiXCixX = false;
      bool JCbOwrqmLU = false;
      bool xVMBcIYGUl = false;
      bool uhOIhuklaP = false;
      bool oLZWrrEhoW = false;
      bool XlHylICbWa = false;
      bool ywOLcbmSfB = false;
      bool GEMufkupJk = false;
      bool DqQxNIZPWZ = false;
      bool rJOARsxNsQ = false;
      bool ElBmQTZMSB = false;
      bool MMSlWGeQyT = false;
      string edCqAWgrPn;
      string MZjnCyrxJb;
      string XOXYSVnjnF;
      string eAzJsnpMQc;
      string VLAAsnYbRs;
      string CPCUsQGcYd;
      string hwDKJLaZtO;
      string HffgGMNWfd;
      string wMStDOxdQc;
      string gNmluYHpqg;
      string NzgDkWiVNg;
      string DjwthUdJGt;
      string NwJRgtrslh;
      string EWeyPxfPIg;
      string fbQiZxQsEZ;
      string tyjxSRoOVq;
      string doifcfFxdj;
      string oOAZOleZrj;
      string dzoLmFmgfy;
      string HQsRCprkGs;
      if(edCqAWgrPn == NzgDkWiVNg){rSOUkfyJig = true;}
      else if(NzgDkWiVNg == edCqAWgrPn){xVMBcIYGUl = true;}
      if(MZjnCyrxJb == DjwthUdJGt){lOWlNeAWrW = true;}
      else if(DjwthUdJGt == MZjnCyrxJb){uhOIhuklaP = true;}
      if(XOXYSVnjnF == NwJRgtrslh){rXRfbXVhWY = true;}
      else if(NwJRgtrslh == XOXYSVnjnF){oLZWrrEhoW = true;}
      if(eAzJsnpMQc == EWeyPxfPIg){stTyrKkTaG = true;}
      else if(EWeyPxfPIg == eAzJsnpMQc){XlHylICbWa = true;}
      if(VLAAsnYbRs == fbQiZxQsEZ){HcyzMrtGEW = true;}
      else if(fbQiZxQsEZ == VLAAsnYbRs){ywOLcbmSfB = true;}
      if(CPCUsQGcYd == tyjxSRoOVq){oVrjATAhrM = true;}
      else if(tyjxSRoOVq == CPCUsQGcYd){GEMufkupJk = true;}
      if(hwDKJLaZtO == doifcfFxdj){KPlKnquXtC = true;}
      else if(doifcfFxdj == hwDKJLaZtO){DqQxNIZPWZ = true;}
      if(HffgGMNWfd == oOAZOleZrj){tfwlOOYSTi = true;}
      if(wMStDOxdQc == dzoLmFmgfy){dOdAiXCixX = true;}
      if(gNmluYHpqg == HQsRCprkGs){JCbOwrqmLU = true;}
      while(oOAZOleZrj == HffgGMNWfd){rJOARsxNsQ = true;}
      while(dzoLmFmgfy == dzoLmFmgfy){ElBmQTZMSB = true;}
      while(HQsRCprkGs == HQsRCprkGs){MMSlWGeQyT = true;}
      if(rSOUkfyJig == true){rSOUkfyJig = false;}
      if(lOWlNeAWrW == true){lOWlNeAWrW = false;}
      if(rXRfbXVhWY == true){rXRfbXVhWY = false;}
      if(stTyrKkTaG == true){stTyrKkTaG = false;}
      if(HcyzMrtGEW == true){HcyzMrtGEW = false;}
      if(oVrjATAhrM == true){oVrjATAhrM = false;}
      if(KPlKnquXtC == true){KPlKnquXtC = false;}
      if(tfwlOOYSTi == true){tfwlOOYSTi = false;}
      if(dOdAiXCixX == true){dOdAiXCixX = false;}
      if(JCbOwrqmLU == true){JCbOwrqmLU = false;}
      if(xVMBcIYGUl == true){xVMBcIYGUl = false;}
      if(uhOIhuklaP == true){uhOIhuklaP = false;}
      if(oLZWrrEhoW == true){oLZWrrEhoW = false;}
      if(XlHylICbWa == true){XlHylICbWa = false;}
      if(ywOLcbmSfB == true){ywOLcbmSfB = false;}
      if(GEMufkupJk == true){GEMufkupJk = false;}
      if(DqQxNIZPWZ == true){DqQxNIZPWZ = false;}
      if(rJOARsxNsQ == true){rJOARsxNsQ = false;}
      if(ElBmQTZMSB == true){ElBmQTZMSB = false;}
      if(MMSlWGeQyT == true){MMSlWGeQyT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCDXTSXYDQ
{ 
  void JuHToOoMIY()
  { 
      bool sXuNtHbRXu = false;
      bool TpKbICwIoV = false;
      bool kraxsePIBh = false;
      bool UUUhiDEShX = false;
      bool SMBbyaDyPS = false;
      bool CtyrlBxyTO = false;
      bool rSQpazUbrF = false;
      bool ycZRDXpyyR = false;
      bool bQsheaVcuh = false;
      bool FFyTfzwLBz = false;
      bool GaGKTZUgoN = false;
      bool KyzCmaYhKA = false;
      bool crfKzrdFlD = false;
      bool bexzLAKiOF = false;
      bool FomhWHGwgE = false;
      bool aOABVNtuLa = false;
      bool wOtklfBApl = false;
      bool QpSEtnEynq = false;
      bool lgYhcMdwcx = false;
      bool GOXmJquBuq = false;
      string IVGVXRKxSA;
      string LadZxZPzpK;
      string TUdxPlJPXk;
      string eMBPJATePR;
      string OVRjcVDXpl;
      string yTYtRmqIGl;
      string HuZgUyZNPx;
      string GjjYwyDtUs;
      string hlYllLnHyW;
      string IKYcJTwjOd;
      string wpIseNiAxS;
      string ixnMDVVmuJ;
      string KSPrnwLGPc;
      string CTepwrcfGX;
      string bmJemLVLYm;
      string xIoFSdaPEi;
      string CckUQPRyQL;
      string spgWgXJjFc;
      string azgceteZXS;
      string RNaXVyCnOW;
      if(IVGVXRKxSA == wpIseNiAxS){sXuNtHbRXu = true;}
      else if(wpIseNiAxS == IVGVXRKxSA){GaGKTZUgoN = true;}
      if(LadZxZPzpK == ixnMDVVmuJ){TpKbICwIoV = true;}
      else if(ixnMDVVmuJ == LadZxZPzpK){KyzCmaYhKA = true;}
      if(TUdxPlJPXk == KSPrnwLGPc){kraxsePIBh = true;}
      else if(KSPrnwLGPc == TUdxPlJPXk){crfKzrdFlD = true;}
      if(eMBPJATePR == CTepwrcfGX){UUUhiDEShX = true;}
      else if(CTepwrcfGX == eMBPJATePR){bexzLAKiOF = true;}
      if(OVRjcVDXpl == bmJemLVLYm){SMBbyaDyPS = true;}
      else if(bmJemLVLYm == OVRjcVDXpl){FomhWHGwgE = true;}
      if(yTYtRmqIGl == xIoFSdaPEi){CtyrlBxyTO = true;}
      else if(xIoFSdaPEi == yTYtRmqIGl){aOABVNtuLa = true;}
      if(HuZgUyZNPx == CckUQPRyQL){rSQpazUbrF = true;}
      else if(CckUQPRyQL == HuZgUyZNPx){wOtklfBApl = true;}
      if(GjjYwyDtUs == spgWgXJjFc){ycZRDXpyyR = true;}
      if(hlYllLnHyW == azgceteZXS){bQsheaVcuh = true;}
      if(IKYcJTwjOd == RNaXVyCnOW){FFyTfzwLBz = true;}
      while(spgWgXJjFc == GjjYwyDtUs){QpSEtnEynq = true;}
      while(azgceteZXS == azgceteZXS){lgYhcMdwcx = true;}
      while(RNaXVyCnOW == RNaXVyCnOW){GOXmJquBuq = true;}
      if(sXuNtHbRXu == true){sXuNtHbRXu = false;}
      if(TpKbICwIoV == true){TpKbICwIoV = false;}
      if(kraxsePIBh == true){kraxsePIBh = false;}
      if(UUUhiDEShX == true){UUUhiDEShX = false;}
      if(SMBbyaDyPS == true){SMBbyaDyPS = false;}
      if(CtyrlBxyTO == true){CtyrlBxyTO = false;}
      if(rSQpazUbrF == true){rSQpazUbrF = false;}
      if(ycZRDXpyyR == true){ycZRDXpyyR = false;}
      if(bQsheaVcuh == true){bQsheaVcuh = false;}
      if(FFyTfzwLBz == true){FFyTfzwLBz = false;}
      if(GaGKTZUgoN == true){GaGKTZUgoN = false;}
      if(KyzCmaYhKA == true){KyzCmaYhKA = false;}
      if(crfKzrdFlD == true){crfKzrdFlD = false;}
      if(bexzLAKiOF == true){bexzLAKiOF = false;}
      if(FomhWHGwgE == true){FomhWHGwgE = false;}
      if(aOABVNtuLa == true){aOABVNtuLa = false;}
      if(wOtklfBApl == true){wOtklfBApl = false;}
      if(QpSEtnEynq == true){QpSEtnEynq = false;}
      if(lgYhcMdwcx == true){lgYhcMdwcx = false;}
      if(GOXmJquBuq == true){GOXmJquBuq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DPFYXQKRQV
{ 
  void bCDiTCprrD()
  { 
      bool XOCxzEXfNM = false;
      bool GXgtVlYguj = false;
      bool YGhoPHElgR = false;
      bool XwmgmEInrh = false;
      bool EgQxepypKW = false;
      bool uoOlURgNhq = false;
      bool zkyunKkAHQ = false;
      bool cjoMeqojKZ = false;
      bool JOaJVigALV = false;
      bool XtGAiThVIT = false;
      bool EyhssLACGd = false;
      bool cwCHgjJnYF = false;
      bool dkokshdndL = false;
      bool JSbpULfhQK = false;
      bool ieshsbqySy = false;
      bool JsxDpTJwAK = false;
      bool hLXuTJUMmV = false;
      bool EbXNWyrGrR = false;
      bool peUfCQUYAB = false;
      bool CigFcWGyNi = false;
      string irTGQxcYKK;
      string ZcQfakbTgZ;
      string MKguYPVgwV;
      string qoYCYiqjDo;
      string UJIkgOpURJ;
      string cnsSjXKYhA;
      string bucoTkENGq;
      string sqQqFCCuNJ;
      string ZAPmrCwFSA;
      string XSCCNYgSQw;
      string KcNZQlXBNh;
      string UOKYaafpwR;
      string nytFTaoNdf;
      string UidRywmpVG;
      string etrjeIHcbl;
      string sqWzHMhHFo;
      string xKXhNkkrad;
      string moTpltGJaK;
      string TLlqlcMdKk;
      string OejgITVKWs;
      if(irTGQxcYKK == KcNZQlXBNh){XOCxzEXfNM = true;}
      else if(KcNZQlXBNh == irTGQxcYKK){EyhssLACGd = true;}
      if(ZcQfakbTgZ == UOKYaafpwR){GXgtVlYguj = true;}
      else if(UOKYaafpwR == ZcQfakbTgZ){cwCHgjJnYF = true;}
      if(MKguYPVgwV == nytFTaoNdf){YGhoPHElgR = true;}
      else if(nytFTaoNdf == MKguYPVgwV){dkokshdndL = true;}
      if(qoYCYiqjDo == UidRywmpVG){XwmgmEInrh = true;}
      else if(UidRywmpVG == qoYCYiqjDo){JSbpULfhQK = true;}
      if(UJIkgOpURJ == etrjeIHcbl){EgQxepypKW = true;}
      else if(etrjeIHcbl == UJIkgOpURJ){ieshsbqySy = true;}
      if(cnsSjXKYhA == sqWzHMhHFo){uoOlURgNhq = true;}
      else if(sqWzHMhHFo == cnsSjXKYhA){JsxDpTJwAK = true;}
      if(bucoTkENGq == xKXhNkkrad){zkyunKkAHQ = true;}
      else if(xKXhNkkrad == bucoTkENGq){hLXuTJUMmV = true;}
      if(sqQqFCCuNJ == moTpltGJaK){cjoMeqojKZ = true;}
      if(ZAPmrCwFSA == TLlqlcMdKk){JOaJVigALV = true;}
      if(XSCCNYgSQw == OejgITVKWs){XtGAiThVIT = true;}
      while(moTpltGJaK == sqQqFCCuNJ){EbXNWyrGrR = true;}
      while(TLlqlcMdKk == TLlqlcMdKk){peUfCQUYAB = true;}
      while(OejgITVKWs == OejgITVKWs){CigFcWGyNi = true;}
      if(XOCxzEXfNM == true){XOCxzEXfNM = false;}
      if(GXgtVlYguj == true){GXgtVlYguj = false;}
      if(YGhoPHElgR == true){YGhoPHElgR = false;}
      if(XwmgmEInrh == true){XwmgmEInrh = false;}
      if(EgQxepypKW == true){EgQxepypKW = false;}
      if(uoOlURgNhq == true){uoOlURgNhq = false;}
      if(zkyunKkAHQ == true){zkyunKkAHQ = false;}
      if(cjoMeqojKZ == true){cjoMeqojKZ = false;}
      if(JOaJVigALV == true){JOaJVigALV = false;}
      if(XtGAiThVIT == true){XtGAiThVIT = false;}
      if(EyhssLACGd == true){EyhssLACGd = false;}
      if(cwCHgjJnYF == true){cwCHgjJnYF = false;}
      if(dkokshdndL == true){dkokshdndL = false;}
      if(JSbpULfhQK == true){JSbpULfhQK = false;}
      if(ieshsbqySy == true){ieshsbqySy = false;}
      if(JsxDpTJwAK == true){JsxDpTJwAK = false;}
      if(hLXuTJUMmV == true){hLXuTJUMmV = false;}
      if(EbXNWyrGrR == true){EbXNWyrGrR = false;}
      if(peUfCQUYAB == true){peUfCQUYAB = false;}
      if(CigFcWGyNi == true){CigFcWGyNi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBDOUQRXXM
{ 
  void fjdUegrAAo()
  { 
      bool XEkwagFXPj = false;
      bool rqtwSsaBNx = false;
      bool tkhUmjqrMX = false;
      bool wAlqlMPLNV = false;
      bool AWktEzEyCS = false;
      bool mCkDolWQIq = false;
      bool pNKqnrFDKG = false;
      bool dPmrwXznPm = false;
      bool esotksOiCz = false;
      bool ozDWemLtFL = false;
      bool tBmwoXOsGR = false;
      bool liAULxYQGt = false;
      bool dVALQeMQNJ = false;
      bool LFhEsdFrEN = false;
      bool eUckMGzhKg = false;
      bool NunKhYAbeK = false;
      bool LyfwFgAwbh = false;
      bool qfMsPIsPyK = false;
      bool fdFfwQRXVT = false;
      bool cdMtBgofef = false;
      string yGZllQeUKo;
      string apGWAojhZs;
      string CqZFerVSXW;
      string ptUeOfNTWK;
      string RlSjLeydsw;
      string PbHPtGfUHt;
      string uLxnygVbIT;
      string bQKPbPXosz;
      string sqZbGOlEjH;
      string ArLbOFoele;
      string JWVYTzQqne;
      string hpaIBElUgj;
      string tQrATiEhAW;
      string asDOpVUAHH;
      string xtQEYJRDaK;
      string STyCjreVFk;
      string tiqREolMSe;
      string ikNZlzzmaJ;
      string RBHoDGuBex;
      string qztVMODzAj;
      if(yGZllQeUKo == JWVYTzQqne){XEkwagFXPj = true;}
      else if(JWVYTzQqne == yGZllQeUKo){tBmwoXOsGR = true;}
      if(apGWAojhZs == hpaIBElUgj){rqtwSsaBNx = true;}
      else if(hpaIBElUgj == apGWAojhZs){liAULxYQGt = true;}
      if(CqZFerVSXW == tQrATiEhAW){tkhUmjqrMX = true;}
      else if(tQrATiEhAW == CqZFerVSXW){dVALQeMQNJ = true;}
      if(ptUeOfNTWK == asDOpVUAHH){wAlqlMPLNV = true;}
      else if(asDOpVUAHH == ptUeOfNTWK){LFhEsdFrEN = true;}
      if(RlSjLeydsw == xtQEYJRDaK){AWktEzEyCS = true;}
      else if(xtQEYJRDaK == RlSjLeydsw){eUckMGzhKg = true;}
      if(PbHPtGfUHt == STyCjreVFk){mCkDolWQIq = true;}
      else if(STyCjreVFk == PbHPtGfUHt){NunKhYAbeK = true;}
      if(uLxnygVbIT == tiqREolMSe){pNKqnrFDKG = true;}
      else if(tiqREolMSe == uLxnygVbIT){LyfwFgAwbh = true;}
      if(bQKPbPXosz == ikNZlzzmaJ){dPmrwXznPm = true;}
      if(sqZbGOlEjH == RBHoDGuBex){esotksOiCz = true;}
      if(ArLbOFoele == qztVMODzAj){ozDWemLtFL = true;}
      while(ikNZlzzmaJ == bQKPbPXosz){qfMsPIsPyK = true;}
      while(RBHoDGuBex == RBHoDGuBex){fdFfwQRXVT = true;}
      while(qztVMODzAj == qztVMODzAj){cdMtBgofef = true;}
      if(XEkwagFXPj == true){XEkwagFXPj = false;}
      if(rqtwSsaBNx == true){rqtwSsaBNx = false;}
      if(tkhUmjqrMX == true){tkhUmjqrMX = false;}
      if(wAlqlMPLNV == true){wAlqlMPLNV = false;}
      if(AWktEzEyCS == true){AWktEzEyCS = false;}
      if(mCkDolWQIq == true){mCkDolWQIq = false;}
      if(pNKqnrFDKG == true){pNKqnrFDKG = false;}
      if(dPmrwXznPm == true){dPmrwXznPm = false;}
      if(esotksOiCz == true){esotksOiCz = false;}
      if(ozDWemLtFL == true){ozDWemLtFL = false;}
      if(tBmwoXOsGR == true){tBmwoXOsGR = false;}
      if(liAULxYQGt == true){liAULxYQGt = false;}
      if(dVALQeMQNJ == true){dVALQeMQNJ = false;}
      if(LFhEsdFrEN == true){LFhEsdFrEN = false;}
      if(eUckMGzhKg == true){eUckMGzhKg = false;}
      if(NunKhYAbeK == true){NunKhYAbeK = false;}
      if(LyfwFgAwbh == true){LyfwFgAwbh = false;}
      if(qfMsPIsPyK == true){qfMsPIsPyK = false;}
      if(fdFfwQRXVT == true){fdFfwQRXVT = false;}
      if(cdMtBgofef == true){cdMtBgofef = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHWBUWNAMX
{ 
  void jRDAlTanlO()
  { 
      bool FPKsqTsDZC = false;
      bool xcKJaNlqXJ = false;
      bool LzGGjAYEfA = false;
      bool kBwUyrLklu = false;
      bool wqilMNmBhk = false;
      bool bfoWuGIEIq = false;
      bool tnXZRwfpLh = false;
      bool CBEcNUQUtW = false;
      bool MWWuXFLYZq = false;
      bool jGcuBHTITP = false;
      bool gxpAhaaMJZ = false;
      bool omKldWRcCM = false;
      bool jGPTywYIbF = false;
      bool BHAdoOgWMw = false;
      bool dzPzCwwpRd = false;
      bool opGHfahVCl = false;
      bool CRkDYgmgxO = false;
      bool ouPFhkqQRB = false;
      bool AhqxQKBrxN = false;
      bool gLTZtLNMZU = false;
      string RBbyAmtfsl;
      string KUaCEyUOcO;
      string cFJPGRkccM;
      string xXwmLOUHZe;
      string fQdZADETWg;
      string uCnoIMrMqi;
      string CQCfolYnpo;
      string cNnxhLbjPC;
      string MQGwRtjHdz;
      string WIPpcONxkO;
      string ePdgDhOpGx;
      string kHxnWlKGOu;
      string CQKpSTxxUS;
      string xdzBXwlZri;
      string fsBgOOLaTq;
      string EHioLNFmNi;
      string jQVmzGIwQa;
      string zkNePIPcbD;
      string IVddOpuJoK;
      string pyLIzOXNgH;
      if(RBbyAmtfsl == ePdgDhOpGx){FPKsqTsDZC = true;}
      else if(ePdgDhOpGx == RBbyAmtfsl){gxpAhaaMJZ = true;}
      if(KUaCEyUOcO == kHxnWlKGOu){xcKJaNlqXJ = true;}
      else if(kHxnWlKGOu == KUaCEyUOcO){omKldWRcCM = true;}
      if(cFJPGRkccM == CQKpSTxxUS){LzGGjAYEfA = true;}
      else if(CQKpSTxxUS == cFJPGRkccM){jGPTywYIbF = true;}
      if(xXwmLOUHZe == xdzBXwlZri){kBwUyrLklu = true;}
      else if(xdzBXwlZri == xXwmLOUHZe){BHAdoOgWMw = true;}
      if(fQdZADETWg == fsBgOOLaTq){wqilMNmBhk = true;}
      else if(fsBgOOLaTq == fQdZADETWg){dzPzCwwpRd = true;}
      if(uCnoIMrMqi == EHioLNFmNi){bfoWuGIEIq = true;}
      else if(EHioLNFmNi == uCnoIMrMqi){opGHfahVCl = true;}
      if(CQCfolYnpo == jQVmzGIwQa){tnXZRwfpLh = true;}
      else if(jQVmzGIwQa == CQCfolYnpo){CRkDYgmgxO = true;}
      if(cNnxhLbjPC == zkNePIPcbD){CBEcNUQUtW = true;}
      if(MQGwRtjHdz == IVddOpuJoK){MWWuXFLYZq = true;}
      if(WIPpcONxkO == pyLIzOXNgH){jGcuBHTITP = true;}
      while(zkNePIPcbD == cNnxhLbjPC){ouPFhkqQRB = true;}
      while(IVddOpuJoK == IVddOpuJoK){AhqxQKBrxN = true;}
      while(pyLIzOXNgH == pyLIzOXNgH){gLTZtLNMZU = true;}
      if(FPKsqTsDZC == true){FPKsqTsDZC = false;}
      if(xcKJaNlqXJ == true){xcKJaNlqXJ = false;}
      if(LzGGjAYEfA == true){LzGGjAYEfA = false;}
      if(kBwUyrLklu == true){kBwUyrLklu = false;}
      if(wqilMNmBhk == true){wqilMNmBhk = false;}
      if(bfoWuGIEIq == true){bfoWuGIEIq = false;}
      if(tnXZRwfpLh == true){tnXZRwfpLh = false;}
      if(CBEcNUQUtW == true){CBEcNUQUtW = false;}
      if(MWWuXFLYZq == true){MWWuXFLYZq = false;}
      if(jGcuBHTITP == true){jGcuBHTITP = false;}
      if(gxpAhaaMJZ == true){gxpAhaaMJZ = false;}
      if(omKldWRcCM == true){omKldWRcCM = false;}
      if(jGPTywYIbF == true){jGPTywYIbF = false;}
      if(BHAdoOgWMw == true){BHAdoOgWMw = false;}
      if(dzPzCwwpRd == true){dzPzCwwpRd = false;}
      if(opGHfahVCl == true){opGHfahVCl = false;}
      if(CRkDYgmgxO == true){CRkDYgmgxO = false;}
      if(ouPFhkqQRB == true){ouPFhkqQRB = false;}
      if(AhqxQKBrxN == true){AhqxQKBrxN = false;}
      if(gLTZtLNMZU == true){gLTZtLNMZU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMGXVZRNXA
{ 
  void EbsNoAOkEd()
  { 
      bool LYQwlIFTDi = false;
      bool dUAhDGdbts = false;
      bool YMWRuXFqEb = false;
      bool yuNjSdWlWa = false;
      bool eixlwdrNXA = false;
      bool DjmoDzCyAO = false;
      bool DNPbjhGPOY = false;
      bool irETNoPjVQ = false;
      bool fqTDXOHYfT = false;
      bool bXkIXRTVCN = false;
      bool WbzyQLeSaN = false;
      bool jRciiLsLDU = false;
      bool ahiuxLGuww = false;
      bool VthHsDrVmM = false;
      bool inxSjKuBZL = false;
      bool XHRgmosEBF = false;
      bool FjVdrojVoe = false;
      bool TXYqlljQKm = false;
      bool PEVkYNbATE = false;
      bool JnUgHzRTZt = false;
      string HVsFLMkfLO;
      string krSqGkQUTV;
      string KUTWBPDyYJ;
      string kfTNFBtlwh;
      string HesrFVcRWQ;
      string SIjjQmBWEw;
      string ImHCdEYEkE;
      string pdXlNeaaQe;
      string mlbHpcuixS;
      string zWhAYUWqOB;
      string xXfRZojyWk;
      string MZGZJVKzLB;
      string IpHSETuXMr;
      string HiMOgOFJgA;
      string rxMLFYQIpC;
      string JXeMsHPMNG;
      string sLkddcNqrt;
      string QBSLIKduMe;
      string DmhJijDAUZ;
      string yrwaGgLhhc;
      if(HVsFLMkfLO == xXfRZojyWk){LYQwlIFTDi = true;}
      else if(xXfRZojyWk == HVsFLMkfLO){WbzyQLeSaN = true;}
      if(krSqGkQUTV == MZGZJVKzLB){dUAhDGdbts = true;}
      else if(MZGZJVKzLB == krSqGkQUTV){jRciiLsLDU = true;}
      if(KUTWBPDyYJ == IpHSETuXMr){YMWRuXFqEb = true;}
      else if(IpHSETuXMr == KUTWBPDyYJ){ahiuxLGuww = true;}
      if(kfTNFBtlwh == HiMOgOFJgA){yuNjSdWlWa = true;}
      else if(HiMOgOFJgA == kfTNFBtlwh){VthHsDrVmM = true;}
      if(HesrFVcRWQ == rxMLFYQIpC){eixlwdrNXA = true;}
      else if(rxMLFYQIpC == HesrFVcRWQ){inxSjKuBZL = true;}
      if(SIjjQmBWEw == JXeMsHPMNG){DjmoDzCyAO = true;}
      else if(JXeMsHPMNG == SIjjQmBWEw){XHRgmosEBF = true;}
      if(ImHCdEYEkE == sLkddcNqrt){DNPbjhGPOY = true;}
      else if(sLkddcNqrt == ImHCdEYEkE){FjVdrojVoe = true;}
      if(pdXlNeaaQe == QBSLIKduMe){irETNoPjVQ = true;}
      if(mlbHpcuixS == DmhJijDAUZ){fqTDXOHYfT = true;}
      if(zWhAYUWqOB == yrwaGgLhhc){bXkIXRTVCN = true;}
      while(QBSLIKduMe == pdXlNeaaQe){TXYqlljQKm = true;}
      while(DmhJijDAUZ == DmhJijDAUZ){PEVkYNbATE = true;}
      while(yrwaGgLhhc == yrwaGgLhhc){JnUgHzRTZt = true;}
      if(LYQwlIFTDi == true){LYQwlIFTDi = false;}
      if(dUAhDGdbts == true){dUAhDGdbts = false;}
      if(YMWRuXFqEb == true){YMWRuXFqEb = false;}
      if(yuNjSdWlWa == true){yuNjSdWlWa = false;}
      if(eixlwdrNXA == true){eixlwdrNXA = false;}
      if(DjmoDzCyAO == true){DjmoDzCyAO = false;}
      if(DNPbjhGPOY == true){DNPbjhGPOY = false;}
      if(irETNoPjVQ == true){irETNoPjVQ = false;}
      if(fqTDXOHYfT == true){fqTDXOHYfT = false;}
      if(bXkIXRTVCN == true){bXkIXRTVCN = false;}
      if(WbzyQLeSaN == true){WbzyQLeSaN = false;}
      if(jRciiLsLDU == true){jRciiLsLDU = false;}
      if(ahiuxLGuww == true){ahiuxLGuww = false;}
      if(VthHsDrVmM == true){VthHsDrVmM = false;}
      if(inxSjKuBZL == true){inxSjKuBZL = false;}
      if(XHRgmosEBF == true){XHRgmosEBF = false;}
      if(FjVdrojVoe == true){FjVdrojVoe = false;}
      if(TXYqlljQKm == true){TXYqlljQKm = false;}
      if(PEVkYNbATE == true){PEVkYNbATE = false;}
      if(JnUgHzRTZt == true){JnUgHzRTZt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRHRJTOMQO
{ 
  void GhYguqHjgG()
  { 
      bool uCSkUfbuNS = false;
      bool GHMFCcUJWi = false;
      bool JTVkmrnDmk = false;
      bool wmyfGfcugJ = false;
      bool JbIjrOUtww = false;
      bool uaWNRaghyb = false;
      bool rXIcWSIgyW = false;
      bool zYbNZhLkrX = false;
      bool XtHpoUQkOe = false;
      bool yuxFQlSeNZ = false;
      bool GnuZwVyJnj = false;
      bool PwoZDyQRmB = false;
      bool CXRSXDaWwn = false;
      bool OfXSRjyhsS = false;
      bool VHwePCGXCS = false;
      bool UArLXhVbBr = false;
      bool ubMAUiXWHS = false;
      bool ziXTetbmDU = false;
      bool xDUcSNnLuj = false;
      bool OVfAXttwJg = false;
      string DBuhMQINFw;
      string OglJIVkXFp;
      string VwJozfDGrX;
      string jgTUaFIKNk;
      string RnzrJlkRAJ;
      string AnctRHrGif;
      string NCVhMgMRhD;
      string MaJUYgwQeM;
      string tkFhXuEZCS;
      string NCagXPRRfc;
      string ZTixwYdIUj;
      string LaaWkbwnKR;
      string clOOoKAcwI;
      string PekClaBIky;
      string QwFSHlaDuu;
      string TdHOzmETIl;
      string YBLLUgpXjK;
      string ZmCLAggwHC;
      string iwgBokWVCz;
      string WhzzYPjsxa;
      if(DBuhMQINFw == ZTixwYdIUj){uCSkUfbuNS = true;}
      else if(ZTixwYdIUj == DBuhMQINFw){GnuZwVyJnj = true;}
      if(OglJIVkXFp == LaaWkbwnKR){GHMFCcUJWi = true;}
      else if(LaaWkbwnKR == OglJIVkXFp){PwoZDyQRmB = true;}
      if(VwJozfDGrX == clOOoKAcwI){JTVkmrnDmk = true;}
      else if(clOOoKAcwI == VwJozfDGrX){CXRSXDaWwn = true;}
      if(jgTUaFIKNk == PekClaBIky){wmyfGfcugJ = true;}
      else if(PekClaBIky == jgTUaFIKNk){OfXSRjyhsS = true;}
      if(RnzrJlkRAJ == QwFSHlaDuu){JbIjrOUtww = true;}
      else if(QwFSHlaDuu == RnzrJlkRAJ){VHwePCGXCS = true;}
      if(AnctRHrGif == TdHOzmETIl){uaWNRaghyb = true;}
      else if(TdHOzmETIl == AnctRHrGif){UArLXhVbBr = true;}
      if(NCVhMgMRhD == YBLLUgpXjK){rXIcWSIgyW = true;}
      else if(YBLLUgpXjK == NCVhMgMRhD){ubMAUiXWHS = true;}
      if(MaJUYgwQeM == ZmCLAggwHC){zYbNZhLkrX = true;}
      if(tkFhXuEZCS == iwgBokWVCz){XtHpoUQkOe = true;}
      if(NCagXPRRfc == WhzzYPjsxa){yuxFQlSeNZ = true;}
      while(ZmCLAggwHC == MaJUYgwQeM){ziXTetbmDU = true;}
      while(iwgBokWVCz == iwgBokWVCz){xDUcSNnLuj = true;}
      while(WhzzYPjsxa == WhzzYPjsxa){OVfAXttwJg = true;}
      if(uCSkUfbuNS == true){uCSkUfbuNS = false;}
      if(GHMFCcUJWi == true){GHMFCcUJWi = false;}
      if(JTVkmrnDmk == true){JTVkmrnDmk = false;}
      if(wmyfGfcugJ == true){wmyfGfcugJ = false;}
      if(JbIjrOUtww == true){JbIjrOUtww = false;}
      if(uaWNRaghyb == true){uaWNRaghyb = false;}
      if(rXIcWSIgyW == true){rXIcWSIgyW = false;}
      if(zYbNZhLkrX == true){zYbNZhLkrX = false;}
      if(XtHpoUQkOe == true){XtHpoUQkOe = false;}
      if(yuxFQlSeNZ == true){yuxFQlSeNZ = false;}
      if(GnuZwVyJnj == true){GnuZwVyJnj = false;}
      if(PwoZDyQRmB == true){PwoZDyQRmB = false;}
      if(CXRSXDaWwn == true){CXRSXDaWwn = false;}
      if(OfXSRjyhsS == true){OfXSRjyhsS = false;}
      if(VHwePCGXCS == true){VHwePCGXCS = false;}
      if(UArLXhVbBr == true){UArLXhVbBr = false;}
      if(ubMAUiXWHS == true){ubMAUiXWHS = false;}
      if(ziXTetbmDU == true){ziXTetbmDU = false;}
      if(xDUcSNnLuj == true){xDUcSNnLuj = false;}
      if(OVfAXttwJg == true){OVfAXttwJg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AUCKHODQOS
{ 
  void SICxfkYHSw()
  { 
      bool zYigElaBhm = false;
      bool kuYNtRVJZf = false;
      bool ryqHFiVMRE = false;
      bool LStsGIeMmD = false;
      bool lfqpmLJDKo = false;
      bool ljGqBAhbaU = false;
      bool PNjcaSAeHl = false;
      bool lJWWtMHBUs = false;
      bool ZSBbRaMCrF = false;
      bool aDkRmXwOOU = false;
      bool KduYCcNjxn = false;
      bool sfGguxLHKz = false;
      bool FymCKiXFiV = false;
      bool QslAiuWcZn = false;
      bool NbEDLtwDVp = false;
      bool LoDPOMqsNT = false;
      bool FIBbXAtGyA = false;
      bool aigWldsipQ = false;
      bool mTjsJaoWlW = false;
      bool EcOGiFacfL = false;
      string bddgXTapAz;
      string jrXuwEXqIQ;
      string hunWzVrUCp;
      string pXTUjErncK;
      string DgyoGGCdmQ;
      string sQNrBgpHhB;
      string aFmJJLXDKq;
      string MiOyMBxyQr;
      string TOglxYKbSD;
      string OkFaiytnet;
      string hyTwEJCPeA;
      string iqqphMYAMj;
      string BwkHcbdmOO;
      string GITVJUtkhm;
      string WuwRTWtPsW;
      string ZsatskNMTb;
      string fOBPsZXUfM;
      string RmSYMFzSmF;
      string hOsqoNhYcY;
      string GhRFHItgXs;
      if(bddgXTapAz == hyTwEJCPeA){zYigElaBhm = true;}
      else if(hyTwEJCPeA == bddgXTapAz){KduYCcNjxn = true;}
      if(jrXuwEXqIQ == iqqphMYAMj){kuYNtRVJZf = true;}
      else if(iqqphMYAMj == jrXuwEXqIQ){sfGguxLHKz = true;}
      if(hunWzVrUCp == BwkHcbdmOO){ryqHFiVMRE = true;}
      else if(BwkHcbdmOO == hunWzVrUCp){FymCKiXFiV = true;}
      if(pXTUjErncK == GITVJUtkhm){LStsGIeMmD = true;}
      else if(GITVJUtkhm == pXTUjErncK){QslAiuWcZn = true;}
      if(DgyoGGCdmQ == WuwRTWtPsW){lfqpmLJDKo = true;}
      else if(WuwRTWtPsW == DgyoGGCdmQ){NbEDLtwDVp = true;}
      if(sQNrBgpHhB == ZsatskNMTb){ljGqBAhbaU = true;}
      else if(ZsatskNMTb == sQNrBgpHhB){LoDPOMqsNT = true;}
      if(aFmJJLXDKq == fOBPsZXUfM){PNjcaSAeHl = true;}
      else if(fOBPsZXUfM == aFmJJLXDKq){FIBbXAtGyA = true;}
      if(MiOyMBxyQr == RmSYMFzSmF){lJWWtMHBUs = true;}
      if(TOglxYKbSD == hOsqoNhYcY){ZSBbRaMCrF = true;}
      if(OkFaiytnet == GhRFHItgXs){aDkRmXwOOU = true;}
      while(RmSYMFzSmF == MiOyMBxyQr){aigWldsipQ = true;}
      while(hOsqoNhYcY == hOsqoNhYcY){mTjsJaoWlW = true;}
      while(GhRFHItgXs == GhRFHItgXs){EcOGiFacfL = true;}
      if(zYigElaBhm == true){zYigElaBhm = false;}
      if(kuYNtRVJZf == true){kuYNtRVJZf = false;}
      if(ryqHFiVMRE == true){ryqHFiVMRE = false;}
      if(LStsGIeMmD == true){LStsGIeMmD = false;}
      if(lfqpmLJDKo == true){lfqpmLJDKo = false;}
      if(ljGqBAhbaU == true){ljGqBAhbaU = false;}
      if(PNjcaSAeHl == true){PNjcaSAeHl = false;}
      if(lJWWtMHBUs == true){lJWWtMHBUs = false;}
      if(ZSBbRaMCrF == true){ZSBbRaMCrF = false;}
      if(aDkRmXwOOU == true){aDkRmXwOOU = false;}
      if(KduYCcNjxn == true){KduYCcNjxn = false;}
      if(sfGguxLHKz == true){sfGguxLHKz = false;}
      if(FymCKiXFiV == true){FymCKiXFiV = false;}
      if(QslAiuWcZn == true){QslAiuWcZn = false;}
      if(NbEDLtwDVp == true){NbEDLtwDVp = false;}
      if(LoDPOMqsNT == true){LoDPOMqsNT = false;}
      if(FIBbXAtGyA == true){FIBbXAtGyA = false;}
      if(aigWldsipQ == true){aigWldsipQ = false;}
      if(mTjsJaoWlW == true){mTjsJaoWlW = false;}
      if(EcOGiFacfL == true){EcOGiFacfL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZIUADWNCZ
{ 
  void yUmGcEgPMf()
  { 
      bool LqgRHQQRbh = false;
      bool HqWiBLPFqZ = false;
      bool eRzasNOyay = false;
      bool aIbYlbdZAX = false;
      bool HYzAyVQaRd = false;
      bool SbXhttrFXs = false;
      bool CRpdGzOywY = false;
      bool goFTSGRzcW = false;
      bool wmgweyjtdr = false;
      bool jYCGVohVsy = false;
      bool HSeswcWEOn = false;
      bool brbAxOktyI = false;
      bool PTTDnImzxc = false;
      bool XwFdPdInzC = false;
      bool beepPqwBJG = false;
      bool EnXkimyaEn = false;
      bool pXGlPfmykT = false;
      bool Fwtwgjndnx = false;
      bool LlpqYjYUtc = false;
      bool ehjLLEYsZj = false;
      string JNcSTHntyE;
      string XhJBHhuBrg;
      string ofYzNUWwmM;
      string VqFJSWJmRG;
      string wuwMcbQxVl;
      string DHQwzcocFz;
      string kqGlifbAik;
      string YHilktiMWk;
      string EYaBINaIKo;
      string gfhSVFnKcx;
      string zQOjNwXdLE;
      string tbGTtLPFcU;
      string FTosDrYQQe;
      string GXiYlnJqnM;
      string owwFuFYOXJ;
      string phhHqeaVgU;
      string WHNgyVsghG;
      string CYRQfJXjyy;
      string TKrHoXpbhG;
      string MnJSphhPHZ;
      if(JNcSTHntyE == zQOjNwXdLE){LqgRHQQRbh = true;}
      else if(zQOjNwXdLE == JNcSTHntyE){HSeswcWEOn = true;}
      if(XhJBHhuBrg == tbGTtLPFcU){HqWiBLPFqZ = true;}
      else if(tbGTtLPFcU == XhJBHhuBrg){brbAxOktyI = true;}
      if(ofYzNUWwmM == FTosDrYQQe){eRzasNOyay = true;}
      else if(FTosDrYQQe == ofYzNUWwmM){PTTDnImzxc = true;}
      if(VqFJSWJmRG == GXiYlnJqnM){aIbYlbdZAX = true;}
      else if(GXiYlnJqnM == VqFJSWJmRG){XwFdPdInzC = true;}
      if(wuwMcbQxVl == owwFuFYOXJ){HYzAyVQaRd = true;}
      else if(owwFuFYOXJ == wuwMcbQxVl){beepPqwBJG = true;}
      if(DHQwzcocFz == phhHqeaVgU){SbXhttrFXs = true;}
      else if(phhHqeaVgU == DHQwzcocFz){EnXkimyaEn = true;}
      if(kqGlifbAik == WHNgyVsghG){CRpdGzOywY = true;}
      else if(WHNgyVsghG == kqGlifbAik){pXGlPfmykT = true;}
      if(YHilktiMWk == CYRQfJXjyy){goFTSGRzcW = true;}
      if(EYaBINaIKo == TKrHoXpbhG){wmgweyjtdr = true;}
      if(gfhSVFnKcx == MnJSphhPHZ){jYCGVohVsy = true;}
      while(CYRQfJXjyy == YHilktiMWk){Fwtwgjndnx = true;}
      while(TKrHoXpbhG == TKrHoXpbhG){LlpqYjYUtc = true;}
      while(MnJSphhPHZ == MnJSphhPHZ){ehjLLEYsZj = true;}
      if(LqgRHQQRbh == true){LqgRHQQRbh = false;}
      if(HqWiBLPFqZ == true){HqWiBLPFqZ = false;}
      if(eRzasNOyay == true){eRzasNOyay = false;}
      if(aIbYlbdZAX == true){aIbYlbdZAX = false;}
      if(HYzAyVQaRd == true){HYzAyVQaRd = false;}
      if(SbXhttrFXs == true){SbXhttrFXs = false;}
      if(CRpdGzOywY == true){CRpdGzOywY = false;}
      if(goFTSGRzcW == true){goFTSGRzcW = false;}
      if(wmgweyjtdr == true){wmgweyjtdr = false;}
      if(jYCGVohVsy == true){jYCGVohVsy = false;}
      if(HSeswcWEOn == true){HSeswcWEOn = false;}
      if(brbAxOktyI == true){brbAxOktyI = false;}
      if(PTTDnImzxc == true){PTTDnImzxc = false;}
      if(XwFdPdInzC == true){XwFdPdInzC = false;}
      if(beepPqwBJG == true){beepPqwBJG = false;}
      if(EnXkimyaEn == true){EnXkimyaEn = false;}
      if(pXGlPfmykT == true){pXGlPfmykT = false;}
      if(Fwtwgjndnx == true){Fwtwgjndnx = false;}
      if(LlpqYjYUtc == true){LlpqYjYUtc = false;}
      if(ehjLLEYsZj == true){ehjLLEYsZj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONWVAGTGPY
{ 
  void bcfybDNuhz()
  { 
      bool YgGLdBiIjW = false;
      bool lfcPYTBLrt = false;
      bool EfAVluieZM = false;
      bool puMSJaKDsC = false;
      bool gyoIhrNCxX = false;
      bool kfxPDsgjYh = false;
      bool REiWfpSJGx = false;
      bool IxRpNFqqmt = false;
      bool hggBaKxxOQ = false;
      bool taeLjbPRbr = false;
      bool YDwAOnOHBy = false;
      bool CoxdAkXgwV = false;
      bool rVuoDhSGFl = false;
      bool pYOuVekgmm = false;
      bool upuQOEcALz = false;
      bool EhVFzCHGxg = false;
      bool UIBPIcaBIU = false;
      bool zqtIaCZdZy = false;
      bool ERtGhIDIwS = false;
      bool XdjGRmneIl = false;
      string pBcYLmrLtI;
      string RrJVGkxOPB;
      string ltrQBzItCW;
      string AKbiLBnCVc;
      string VxquTMYLQy;
      string tuLjBwJLXM;
      string dxIWIHQaKE;
      string xtsmfoCwwo;
      string ZwdEcEzqgO;
      string qbeIyXnUmM;
      string wxBLBABXEL;
      string tNPhmhTEtD;
      string IYswMUOkoH;
      string AhIjrbuRCc;
      string DamVUdMwVQ;
      string DjZjEXEEzg;
      string kQiwKLEfpK;
      string lCBQzglXbi;
      string HROXDPHYeU;
      string XpSVqmqpKI;
      if(pBcYLmrLtI == wxBLBABXEL){YgGLdBiIjW = true;}
      else if(wxBLBABXEL == pBcYLmrLtI){YDwAOnOHBy = true;}
      if(RrJVGkxOPB == tNPhmhTEtD){lfcPYTBLrt = true;}
      else if(tNPhmhTEtD == RrJVGkxOPB){CoxdAkXgwV = true;}
      if(ltrQBzItCW == IYswMUOkoH){EfAVluieZM = true;}
      else if(IYswMUOkoH == ltrQBzItCW){rVuoDhSGFl = true;}
      if(AKbiLBnCVc == AhIjrbuRCc){puMSJaKDsC = true;}
      else if(AhIjrbuRCc == AKbiLBnCVc){pYOuVekgmm = true;}
      if(VxquTMYLQy == DamVUdMwVQ){gyoIhrNCxX = true;}
      else if(DamVUdMwVQ == VxquTMYLQy){upuQOEcALz = true;}
      if(tuLjBwJLXM == DjZjEXEEzg){kfxPDsgjYh = true;}
      else if(DjZjEXEEzg == tuLjBwJLXM){EhVFzCHGxg = true;}
      if(dxIWIHQaKE == kQiwKLEfpK){REiWfpSJGx = true;}
      else if(kQiwKLEfpK == dxIWIHQaKE){UIBPIcaBIU = true;}
      if(xtsmfoCwwo == lCBQzglXbi){IxRpNFqqmt = true;}
      if(ZwdEcEzqgO == HROXDPHYeU){hggBaKxxOQ = true;}
      if(qbeIyXnUmM == XpSVqmqpKI){taeLjbPRbr = true;}
      while(lCBQzglXbi == xtsmfoCwwo){zqtIaCZdZy = true;}
      while(HROXDPHYeU == HROXDPHYeU){ERtGhIDIwS = true;}
      while(XpSVqmqpKI == XpSVqmqpKI){XdjGRmneIl = true;}
      if(YgGLdBiIjW == true){YgGLdBiIjW = false;}
      if(lfcPYTBLrt == true){lfcPYTBLrt = false;}
      if(EfAVluieZM == true){EfAVluieZM = false;}
      if(puMSJaKDsC == true){puMSJaKDsC = false;}
      if(gyoIhrNCxX == true){gyoIhrNCxX = false;}
      if(kfxPDsgjYh == true){kfxPDsgjYh = false;}
      if(REiWfpSJGx == true){REiWfpSJGx = false;}
      if(IxRpNFqqmt == true){IxRpNFqqmt = false;}
      if(hggBaKxxOQ == true){hggBaKxxOQ = false;}
      if(taeLjbPRbr == true){taeLjbPRbr = false;}
      if(YDwAOnOHBy == true){YDwAOnOHBy = false;}
      if(CoxdAkXgwV == true){CoxdAkXgwV = false;}
      if(rVuoDhSGFl == true){rVuoDhSGFl = false;}
      if(pYOuVekgmm == true){pYOuVekgmm = false;}
      if(upuQOEcALz == true){upuQOEcALz = false;}
      if(EhVFzCHGxg == true){EhVFzCHGxg = false;}
      if(UIBPIcaBIU == true){UIBPIcaBIU = false;}
      if(zqtIaCZdZy == true){zqtIaCZdZy = false;}
      if(ERtGhIDIwS == true){ERtGhIDIwS = false;}
      if(XdjGRmneIl == true){XdjGRmneIl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWWYUVXDWA
{ 
  void jPBfhzziwQ()
  { 
      bool yqHJTKbfXP = false;
      bool rhDFGWjlyl = false;
      bool KiktxBBUPR = false;
      bool Edhiwwpjlk = false;
      bool LOHTOMCVdZ = false;
      bool JOSZfOGMLS = false;
      bool IHPFKNzUJK = false;
      bool gAAMZubRek = false;
      bool yepoIpKHCg = false;
      bool pcXSbEzBIB = false;
      bool MhMTsIOFAk = false;
      bool mnhaTcRaxU = false;
      bool CrRbUDcgkV = false;
      bool wZIdXQSVwz = false;
      bool bFHRtBuwzz = false;
      bool mXDmyUPjzo = false;
      bool fgUeoMeDDC = false;
      bool KudxsxjAhS = false;
      bool HfglhXWVeC = false;
      bool AiWGTtjbcg = false;
      string KtIUEadOHI;
      string DwjGCTGXrP;
      string SGgJhIznDi;
      string dmzTtEjsMt;
      string jduyjraNEd;
      string oiVJkDNymw;
      string bpKYePxQMx;
      string jMKyeoKiYp;
      string gkiYtuQpip;
      string qkGPRtSWTU;
      string uKBHsbXXdw;
      string sdYxOqGkei;
      string yHgWGzGtfj;
      string VmPEuWjbfR;
      string WsLmwMLJBa;
      string nhrjVmcdAt;
      string UdrtZFOUBq;
      string GdFMLFutZt;
      string mxsFunueiH;
      string tFbkxsBRMq;
      if(KtIUEadOHI == uKBHsbXXdw){yqHJTKbfXP = true;}
      else if(uKBHsbXXdw == KtIUEadOHI){MhMTsIOFAk = true;}
      if(DwjGCTGXrP == sdYxOqGkei){rhDFGWjlyl = true;}
      else if(sdYxOqGkei == DwjGCTGXrP){mnhaTcRaxU = true;}
      if(SGgJhIznDi == yHgWGzGtfj){KiktxBBUPR = true;}
      else if(yHgWGzGtfj == SGgJhIznDi){CrRbUDcgkV = true;}
      if(dmzTtEjsMt == VmPEuWjbfR){Edhiwwpjlk = true;}
      else if(VmPEuWjbfR == dmzTtEjsMt){wZIdXQSVwz = true;}
      if(jduyjraNEd == WsLmwMLJBa){LOHTOMCVdZ = true;}
      else if(WsLmwMLJBa == jduyjraNEd){bFHRtBuwzz = true;}
      if(oiVJkDNymw == nhrjVmcdAt){JOSZfOGMLS = true;}
      else if(nhrjVmcdAt == oiVJkDNymw){mXDmyUPjzo = true;}
      if(bpKYePxQMx == UdrtZFOUBq){IHPFKNzUJK = true;}
      else if(UdrtZFOUBq == bpKYePxQMx){fgUeoMeDDC = true;}
      if(jMKyeoKiYp == GdFMLFutZt){gAAMZubRek = true;}
      if(gkiYtuQpip == mxsFunueiH){yepoIpKHCg = true;}
      if(qkGPRtSWTU == tFbkxsBRMq){pcXSbEzBIB = true;}
      while(GdFMLFutZt == jMKyeoKiYp){KudxsxjAhS = true;}
      while(mxsFunueiH == mxsFunueiH){HfglhXWVeC = true;}
      while(tFbkxsBRMq == tFbkxsBRMq){AiWGTtjbcg = true;}
      if(yqHJTKbfXP == true){yqHJTKbfXP = false;}
      if(rhDFGWjlyl == true){rhDFGWjlyl = false;}
      if(KiktxBBUPR == true){KiktxBBUPR = false;}
      if(Edhiwwpjlk == true){Edhiwwpjlk = false;}
      if(LOHTOMCVdZ == true){LOHTOMCVdZ = false;}
      if(JOSZfOGMLS == true){JOSZfOGMLS = false;}
      if(IHPFKNzUJK == true){IHPFKNzUJK = false;}
      if(gAAMZubRek == true){gAAMZubRek = false;}
      if(yepoIpKHCg == true){yepoIpKHCg = false;}
      if(pcXSbEzBIB == true){pcXSbEzBIB = false;}
      if(MhMTsIOFAk == true){MhMTsIOFAk = false;}
      if(mnhaTcRaxU == true){mnhaTcRaxU = false;}
      if(CrRbUDcgkV == true){CrRbUDcgkV = false;}
      if(wZIdXQSVwz == true){wZIdXQSVwz = false;}
      if(bFHRtBuwzz == true){bFHRtBuwzz = false;}
      if(mXDmyUPjzo == true){mXDmyUPjzo = false;}
      if(fgUeoMeDDC == true){fgUeoMeDDC = false;}
      if(KudxsxjAhS == true){KudxsxjAhS = false;}
      if(HfglhXWVeC == true){HfglhXWVeC = false;}
      if(AiWGTtjbcg == true){AiWGTtjbcg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHINCTWVZK
{ 
  void SuXqsUTEwc()
  { 
      bool WZmwRHsVLO = false;
      bool IEDEjRtGXL = false;
      bool aIpLPwiTsS = false;
      bool kemmTmLEEh = false;
      bool LMfwGbeyOf = false;
      bool OfhEcNibfV = false;
      bool XZcrdcRQjx = false;
      bool GoCozNbsEn = false;
      bool QjFMEFwhJF = false;
      bool DjXiJljnSd = false;
      bool KOORZYcsFP = false;
      bool lpXrEnTPmY = false;
      bool fjGesVRTeN = false;
      bool cnZacCVnme = false;
      bool bDbtTMMedV = false;
      bool RUAtxZHiXD = false;
      bool GJNqlxQwOC = false;
      bool RfbIwcHMLf = false;
      bool JloJuInfdC = false;
      bool tmQjXSpkIW = false;
      string OPZbrqTcqV;
      string dFrRwSFSNj;
      string NplzhZEchn;
      string AdfqrfCswp;
      string UUYmZYsaXB;
      string rKSNaXdZtR;
      string lptDUzYAZP;
      string QMWWOrRyYJ;
      string gdFgupLSQT;
      string CbzdEeZUSa;
      string zrAHkemuyi;
      string GfAjkHjNHe;
      string nFjFNnNsSj;
      string RweyJncxuP;
      string CPTgNWaOrw;
      string tMNmmtHutw;
      string RtcNQJABaw;
      string dlSqbXkDqp;
      string MzAVpFiqLP;
      string ghDyyIlGQE;
      if(OPZbrqTcqV == zrAHkemuyi){WZmwRHsVLO = true;}
      else if(zrAHkemuyi == OPZbrqTcqV){KOORZYcsFP = true;}
      if(dFrRwSFSNj == GfAjkHjNHe){IEDEjRtGXL = true;}
      else if(GfAjkHjNHe == dFrRwSFSNj){lpXrEnTPmY = true;}
      if(NplzhZEchn == nFjFNnNsSj){aIpLPwiTsS = true;}
      else if(nFjFNnNsSj == NplzhZEchn){fjGesVRTeN = true;}
      if(AdfqrfCswp == RweyJncxuP){kemmTmLEEh = true;}
      else if(RweyJncxuP == AdfqrfCswp){cnZacCVnme = true;}
      if(UUYmZYsaXB == CPTgNWaOrw){LMfwGbeyOf = true;}
      else if(CPTgNWaOrw == UUYmZYsaXB){bDbtTMMedV = true;}
      if(rKSNaXdZtR == tMNmmtHutw){OfhEcNibfV = true;}
      else if(tMNmmtHutw == rKSNaXdZtR){RUAtxZHiXD = true;}
      if(lptDUzYAZP == RtcNQJABaw){XZcrdcRQjx = true;}
      else if(RtcNQJABaw == lptDUzYAZP){GJNqlxQwOC = true;}
      if(QMWWOrRyYJ == dlSqbXkDqp){GoCozNbsEn = true;}
      if(gdFgupLSQT == MzAVpFiqLP){QjFMEFwhJF = true;}
      if(CbzdEeZUSa == ghDyyIlGQE){DjXiJljnSd = true;}
      while(dlSqbXkDqp == QMWWOrRyYJ){RfbIwcHMLf = true;}
      while(MzAVpFiqLP == MzAVpFiqLP){JloJuInfdC = true;}
      while(ghDyyIlGQE == ghDyyIlGQE){tmQjXSpkIW = true;}
      if(WZmwRHsVLO == true){WZmwRHsVLO = false;}
      if(IEDEjRtGXL == true){IEDEjRtGXL = false;}
      if(aIpLPwiTsS == true){aIpLPwiTsS = false;}
      if(kemmTmLEEh == true){kemmTmLEEh = false;}
      if(LMfwGbeyOf == true){LMfwGbeyOf = false;}
      if(OfhEcNibfV == true){OfhEcNibfV = false;}
      if(XZcrdcRQjx == true){XZcrdcRQjx = false;}
      if(GoCozNbsEn == true){GoCozNbsEn = false;}
      if(QjFMEFwhJF == true){QjFMEFwhJF = false;}
      if(DjXiJljnSd == true){DjXiJljnSd = false;}
      if(KOORZYcsFP == true){KOORZYcsFP = false;}
      if(lpXrEnTPmY == true){lpXrEnTPmY = false;}
      if(fjGesVRTeN == true){fjGesVRTeN = false;}
      if(cnZacCVnme == true){cnZacCVnme = false;}
      if(bDbtTMMedV == true){bDbtTMMedV = false;}
      if(RUAtxZHiXD == true){RUAtxZHiXD = false;}
      if(GJNqlxQwOC == true){GJNqlxQwOC = false;}
      if(RfbIwcHMLf == true){RfbIwcHMLf = false;}
      if(JloJuInfdC == true){JloJuInfdC = false;}
      if(tmQjXSpkIW == true){tmQjXSpkIW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WENVZXMGPQ
{ 
  void ukqcGWntIC()
  { 
      bool YWtNUaKLEF = false;
      bool gCYZlMuhto = false;
      bool CjDhMhVOdH = false;
      bool BFDAKtAioQ = false;
      bool FUuQiWoTBl = false;
      bool UFDSenSLAm = false;
      bool FwgwDbyXOq = false;
      bool MMrdjhnmzo = false;
      bool rBNrmuBjVW = false;
      bool bnhCKJmzMG = false;
      bool XQEJZHMZiw = false;
      bool zeLLtEhoII = false;
      bool ZOCrOXdpSa = false;
      bool uoasQbwDRe = false;
      bool hbAYWwbWIG = false;
      bool axpEfJNMuB = false;
      bool dWGIBJEStR = false;
      bool HeWdZyNcVR = false;
      bool uHhMzyzVMH = false;
      bool NjIPBLUrXM = false;
      string UPwCfDzUYe;
      string HJbxgMspte;
      string gQTXhgGYWh;
      string DjSIaRLMWg;
      string kARioMHcRQ;
      string dHhOMEwYUz;
      string waxpbXpTVO;
      string AgTMsfyjhV;
      string ZcGGEwBEuW;
      string VmrXkKDbHR;
      string VmHDQwnUUg;
      string FMpyYSTqkf;
      string VlYzsNnubi;
      string bWbQAmVDoH;
      string HgiNQJwszR;
      string qLpbujNHJC;
      string IrrlFijZyk;
      string wPBdXoCLhj;
      string QuwKrPfzVP;
      string YOtmzPnxIh;
      if(UPwCfDzUYe == VmHDQwnUUg){YWtNUaKLEF = true;}
      else if(VmHDQwnUUg == UPwCfDzUYe){XQEJZHMZiw = true;}
      if(HJbxgMspte == FMpyYSTqkf){gCYZlMuhto = true;}
      else if(FMpyYSTqkf == HJbxgMspte){zeLLtEhoII = true;}
      if(gQTXhgGYWh == VlYzsNnubi){CjDhMhVOdH = true;}
      else if(VlYzsNnubi == gQTXhgGYWh){ZOCrOXdpSa = true;}
      if(DjSIaRLMWg == bWbQAmVDoH){BFDAKtAioQ = true;}
      else if(bWbQAmVDoH == DjSIaRLMWg){uoasQbwDRe = true;}
      if(kARioMHcRQ == HgiNQJwszR){FUuQiWoTBl = true;}
      else if(HgiNQJwszR == kARioMHcRQ){hbAYWwbWIG = true;}
      if(dHhOMEwYUz == qLpbujNHJC){UFDSenSLAm = true;}
      else if(qLpbujNHJC == dHhOMEwYUz){axpEfJNMuB = true;}
      if(waxpbXpTVO == IrrlFijZyk){FwgwDbyXOq = true;}
      else if(IrrlFijZyk == waxpbXpTVO){dWGIBJEStR = true;}
      if(AgTMsfyjhV == wPBdXoCLhj){MMrdjhnmzo = true;}
      if(ZcGGEwBEuW == QuwKrPfzVP){rBNrmuBjVW = true;}
      if(VmrXkKDbHR == YOtmzPnxIh){bnhCKJmzMG = true;}
      while(wPBdXoCLhj == AgTMsfyjhV){HeWdZyNcVR = true;}
      while(QuwKrPfzVP == QuwKrPfzVP){uHhMzyzVMH = true;}
      while(YOtmzPnxIh == YOtmzPnxIh){NjIPBLUrXM = true;}
      if(YWtNUaKLEF == true){YWtNUaKLEF = false;}
      if(gCYZlMuhto == true){gCYZlMuhto = false;}
      if(CjDhMhVOdH == true){CjDhMhVOdH = false;}
      if(BFDAKtAioQ == true){BFDAKtAioQ = false;}
      if(FUuQiWoTBl == true){FUuQiWoTBl = false;}
      if(UFDSenSLAm == true){UFDSenSLAm = false;}
      if(FwgwDbyXOq == true){FwgwDbyXOq = false;}
      if(MMrdjhnmzo == true){MMrdjhnmzo = false;}
      if(rBNrmuBjVW == true){rBNrmuBjVW = false;}
      if(bnhCKJmzMG == true){bnhCKJmzMG = false;}
      if(XQEJZHMZiw == true){XQEJZHMZiw = false;}
      if(zeLLtEhoII == true){zeLLtEhoII = false;}
      if(ZOCrOXdpSa == true){ZOCrOXdpSa = false;}
      if(uoasQbwDRe == true){uoasQbwDRe = false;}
      if(hbAYWwbWIG == true){hbAYWwbWIG = false;}
      if(axpEfJNMuB == true){axpEfJNMuB = false;}
      if(dWGIBJEStR == true){dWGIBJEStR = false;}
      if(HeWdZyNcVR == true){HeWdZyNcVR = false;}
      if(uHhMzyzVMH == true){uHhMzyzVMH = false;}
      if(NjIPBLUrXM == true){NjIPBLUrXM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNTQMWJPFZ
{ 
  void gPVZaKbElU()
  { 
      bool MCzZgFyWrs = false;
      bool njahhVSVuE = false;
      bool VBAcVjOgrG = false;
      bool RsfkWoDwTs = false;
      bool xOqhXdKZXA = false;
      bool LlFUXLBVDw = false;
      bool pQekbtEoLr = false;
      bool SWBCGGJSFr = false;
      bool YoIrufmKNK = false;
      bool mgrXCfjFGc = false;
      bool ZVOegnjDOQ = false;
      bool CiQLWBImpu = false;
      bool HtaAFkedzZ = false;
      bool WELbSDacKG = false;
      bool wjwwIEPfAA = false;
      bool XwOKVetNZw = false;
      bool JFDntyWosT = false;
      bool afcjzWyerA = false;
      bool UycyCZoBGm = false;
      bool IMCNwpgHBK = false;
      string jWrsxZalMy;
      string RqPuPMkAiA;
      string lkdCshfCqp;
      string AFlcgnpWQM;
      string zzRhjbIBbQ;
      string dHyVUzsozP;
      string tYtVyLEmNb;
      string VNjWBlTwSQ;
      string ZeaaLrGPHg;
      string tAWBSZEuiX;
      string WUmztQXbUh;
      string fxWipOyTJF;
      string EoeggUqhEa;
      string gXMtsErafu;
      string UeuZBxdnLD;
      string bkkcShoGSY;
      string YoWtAHjbok;
      string WWmOkZtFej;
      string qCWBywliaL;
      string OlIGVeHBZs;
      if(jWrsxZalMy == WUmztQXbUh){MCzZgFyWrs = true;}
      else if(WUmztQXbUh == jWrsxZalMy){ZVOegnjDOQ = true;}
      if(RqPuPMkAiA == fxWipOyTJF){njahhVSVuE = true;}
      else if(fxWipOyTJF == RqPuPMkAiA){CiQLWBImpu = true;}
      if(lkdCshfCqp == EoeggUqhEa){VBAcVjOgrG = true;}
      else if(EoeggUqhEa == lkdCshfCqp){HtaAFkedzZ = true;}
      if(AFlcgnpWQM == gXMtsErafu){RsfkWoDwTs = true;}
      else if(gXMtsErafu == AFlcgnpWQM){WELbSDacKG = true;}
      if(zzRhjbIBbQ == UeuZBxdnLD){xOqhXdKZXA = true;}
      else if(UeuZBxdnLD == zzRhjbIBbQ){wjwwIEPfAA = true;}
      if(dHyVUzsozP == bkkcShoGSY){LlFUXLBVDw = true;}
      else if(bkkcShoGSY == dHyVUzsozP){XwOKVetNZw = true;}
      if(tYtVyLEmNb == YoWtAHjbok){pQekbtEoLr = true;}
      else if(YoWtAHjbok == tYtVyLEmNb){JFDntyWosT = true;}
      if(VNjWBlTwSQ == WWmOkZtFej){SWBCGGJSFr = true;}
      if(ZeaaLrGPHg == qCWBywliaL){YoIrufmKNK = true;}
      if(tAWBSZEuiX == OlIGVeHBZs){mgrXCfjFGc = true;}
      while(WWmOkZtFej == VNjWBlTwSQ){afcjzWyerA = true;}
      while(qCWBywliaL == qCWBywliaL){UycyCZoBGm = true;}
      while(OlIGVeHBZs == OlIGVeHBZs){IMCNwpgHBK = true;}
      if(MCzZgFyWrs == true){MCzZgFyWrs = false;}
      if(njahhVSVuE == true){njahhVSVuE = false;}
      if(VBAcVjOgrG == true){VBAcVjOgrG = false;}
      if(RsfkWoDwTs == true){RsfkWoDwTs = false;}
      if(xOqhXdKZXA == true){xOqhXdKZXA = false;}
      if(LlFUXLBVDw == true){LlFUXLBVDw = false;}
      if(pQekbtEoLr == true){pQekbtEoLr = false;}
      if(SWBCGGJSFr == true){SWBCGGJSFr = false;}
      if(YoIrufmKNK == true){YoIrufmKNK = false;}
      if(mgrXCfjFGc == true){mgrXCfjFGc = false;}
      if(ZVOegnjDOQ == true){ZVOegnjDOQ = false;}
      if(CiQLWBImpu == true){CiQLWBImpu = false;}
      if(HtaAFkedzZ == true){HtaAFkedzZ = false;}
      if(WELbSDacKG == true){WELbSDacKG = false;}
      if(wjwwIEPfAA == true){wjwwIEPfAA = false;}
      if(XwOKVetNZw == true){XwOKVetNZw = false;}
      if(JFDntyWosT == true){JFDntyWosT = false;}
      if(afcjzWyerA == true){afcjzWyerA = false;}
      if(UycyCZoBGm == true){UycyCZoBGm = false;}
      if(IMCNwpgHBK == true){IMCNwpgHBK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLZKYWHEZD
{ 
  void TQwhGMEbQa()
  { 
      bool CDMROHByyM = false;
      bool tELWDiMgQd = false;
      bool eQrSzXROFQ = false;
      bool jDeqhFkkSy = false;
      bool wdLKsBdFVz = false;
      bool HLlhGkLtSq = false;
      bool pmrhcpZUox = false;
      bool ybOShAFhYy = false;
      bool tMsFJXRxjw = false;
      bool tpSbHIkcgD = false;
      bool bIPXBfxSzG = false;
      bool fdUUwdsmYE = false;
      bool XckrDHIlKY = false;
      bool ObAVVkwVEc = false;
      bool ayxcQQVyfd = false;
      bool PyEbezXXUs = false;
      bool WLIZqEczyL = false;
      bool gXhudYeHbl = false;
      bool lKGfJQWYpW = false;
      bool MXBLGPpWlL = false;
      string ydDFiPYwPd;
      string RMObllJdmB;
      string ZUGlpuhpst;
      string duZbrXMdUE;
      string NUNFxTPsjP;
      string eBKTVcXQPn;
      string giDUzVmljO;
      string YfIimFHBnV;
      string enFcPcjGFO;
      string AwNgWeQrGa;
      string gcJVpzrbfQ;
      string VVctIscaFV;
      string kggUOcRbLI;
      string nOtMnCdilQ;
      string kIZordTTXd;
      string BpmjpAwnHN;
      string gQPXcGbPGF;
      string OsnnkcGqcj;
      string JyDhGybKWm;
      string GpbYiUsCMk;
      if(ydDFiPYwPd == gcJVpzrbfQ){CDMROHByyM = true;}
      else if(gcJVpzrbfQ == ydDFiPYwPd){bIPXBfxSzG = true;}
      if(RMObllJdmB == VVctIscaFV){tELWDiMgQd = true;}
      else if(VVctIscaFV == RMObllJdmB){fdUUwdsmYE = true;}
      if(ZUGlpuhpst == kggUOcRbLI){eQrSzXROFQ = true;}
      else if(kggUOcRbLI == ZUGlpuhpst){XckrDHIlKY = true;}
      if(duZbrXMdUE == nOtMnCdilQ){jDeqhFkkSy = true;}
      else if(nOtMnCdilQ == duZbrXMdUE){ObAVVkwVEc = true;}
      if(NUNFxTPsjP == kIZordTTXd){wdLKsBdFVz = true;}
      else if(kIZordTTXd == NUNFxTPsjP){ayxcQQVyfd = true;}
      if(eBKTVcXQPn == BpmjpAwnHN){HLlhGkLtSq = true;}
      else if(BpmjpAwnHN == eBKTVcXQPn){PyEbezXXUs = true;}
      if(giDUzVmljO == gQPXcGbPGF){pmrhcpZUox = true;}
      else if(gQPXcGbPGF == giDUzVmljO){WLIZqEczyL = true;}
      if(YfIimFHBnV == OsnnkcGqcj){ybOShAFhYy = true;}
      if(enFcPcjGFO == JyDhGybKWm){tMsFJXRxjw = true;}
      if(AwNgWeQrGa == GpbYiUsCMk){tpSbHIkcgD = true;}
      while(OsnnkcGqcj == YfIimFHBnV){gXhudYeHbl = true;}
      while(JyDhGybKWm == JyDhGybKWm){lKGfJQWYpW = true;}
      while(GpbYiUsCMk == GpbYiUsCMk){MXBLGPpWlL = true;}
      if(CDMROHByyM == true){CDMROHByyM = false;}
      if(tELWDiMgQd == true){tELWDiMgQd = false;}
      if(eQrSzXROFQ == true){eQrSzXROFQ = false;}
      if(jDeqhFkkSy == true){jDeqhFkkSy = false;}
      if(wdLKsBdFVz == true){wdLKsBdFVz = false;}
      if(HLlhGkLtSq == true){HLlhGkLtSq = false;}
      if(pmrhcpZUox == true){pmrhcpZUox = false;}
      if(ybOShAFhYy == true){ybOShAFhYy = false;}
      if(tMsFJXRxjw == true){tMsFJXRxjw = false;}
      if(tpSbHIkcgD == true){tpSbHIkcgD = false;}
      if(bIPXBfxSzG == true){bIPXBfxSzG = false;}
      if(fdUUwdsmYE == true){fdUUwdsmYE = false;}
      if(XckrDHIlKY == true){XckrDHIlKY = false;}
      if(ObAVVkwVEc == true){ObAVVkwVEc = false;}
      if(ayxcQQVyfd == true){ayxcQQVyfd = false;}
      if(PyEbezXXUs == true){PyEbezXXUs = false;}
      if(WLIZqEczyL == true){WLIZqEczyL = false;}
      if(gXhudYeHbl == true){gXhudYeHbl = false;}
      if(lKGfJQWYpW == true){lKGfJQWYpW = false;}
      if(MXBLGPpWlL == true){MXBLGPpWlL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNMLPCGJLB
{ 
  void xKCzmDBsuF()
  { 
      bool pkacocIUXl = false;
      bool oqNpXQGPMT = false;
      bool MMMLLYWmWc = false;
      bool mQFOMigVln = false;
      bool TnWaqQjWai = false;
      bool WzXGKcYPRQ = false;
      bool FUxtzXlzcn = false;
      bool ikcYzXpkTt = false;
      bool nAMnGmszDi = false;
      bool JRDVhyqbbT = false;
      bool ejsmAlVyHl = false;
      bool mnwWbFIJnL = false;
      bool emusdRgHqA = false;
      bool gNIAPEGYnT = false;
      bool RtrRwVVftc = false;
      bool ognQnrozIh = false;
      bool EOHGFYfuGX = false;
      bool yjUTtktdxI = false;
      bool uANNKzZqLX = false;
      bool PHQFPCmkMX = false;
      string IHXGnrNFCA;
      string ZoKWflgxmX;
      string TwitPgzXKh;
      string bfFNbBRXEW;
      string rUHqsnYYXs;
      string JstkULXdpH;
      string spuTXtiwud;
      string UJrQeynrBb;
      string HazQYikTsQ;
      string dnhwdCZmSy;
      string EbdsYAAdGV;
      string WfcOzSpduo;
      string JODeAfaulc;
      string YBYCWfwGqY;
      string hGNWsxLSwK;
      string MurdopXzsr;
      string YFqcwVHZrT;
      string VjlWGCBfkC;
      string UIybQcJtNg;
      string IxMzzcPjZW;
      if(IHXGnrNFCA == EbdsYAAdGV){pkacocIUXl = true;}
      else if(EbdsYAAdGV == IHXGnrNFCA){ejsmAlVyHl = true;}
      if(ZoKWflgxmX == WfcOzSpduo){oqNpXQGPMT = true;}
      else if(WfcOzSpduo == ZoKWflgxmX){mnwWbFIJnL = true;}
      if(TwitPgzXKh == JODeAfaulc){MMMLLYWmWc = true;}
      else if(JODeAfaulc == TwitPgzXKh){emusdRgHqA = true;}
      if(bfFNbBRXEW == YBYCWfwGqY){mQFOMigVln = true;}
      else if(YBYCWfwGqY == bfFNbBRXEW){gNIAPEGYnT = true;}
      if(rUHqsnYYXs == hGNWsxLSwK){TnWaqQjWai = true;}
      else if(hGNWsxLSwK == rUHqsnYYXs){RtrRwVVftc = true;}
      if(JstkULXdpH == MurdopXzsr){WzXGKcYPRQ = true;}
      else if(MurdopXzsr == JstkULXdpH){ognQnrozIh = true;}
      if(spuTXtiwud == YFqcwVHZrT){FUxtzXlzcn = true;}
      else if(YFqcwVHZrT == spuTXtiwud){EOHGFYfuGX = true;}
      if(UJrQeynrBb == VjlWGCBfkC){ikcYzXpkTt = true;}
      if(HazQYikTsQ == UIybQcJtNg){nAMnGmszDi = true;}
      if(dnhwdCZmSy == IxMzzcPjZW){JRDVhyqbbT = true;}
      while(VjlWGCBfkC == UJrQeynrBb){yjUTtktdxI = true;}
      while(UIybQcJtNg == UIybQcJtNg){uANNKzZqLX = true;}
      while(IxMzzcPjZW == IxMzzcPjZW){PHQFPCmkMX = true;}
      if(pkacocIUXl == true){pkacocIUXl = false;}
      if(oqNpXQGPMT == true){oqNpXQGPMT = false;}
      if(MMMLLYWmWc == true){MMMLLYWmWc = false;}
      if(mQFOMigVln == true){mQFOMigVln = false;}
      if(TnWaqQjWai == true){TnWaqQjWai = false;}
      if(WzXGKcYPRQ == true){WzXGKcYPRQ = false;}
      if(FUxtzXlzcn == true){FUxtzXlzcn = false;}
      if(ikcYzXpkTt == true){ikcYzXpkTt = false;}
      if(nAMnGmszDi == true){nAMnGmszDi = false;}
      if(JRDVhyqbbT == true){JRDVhyqbbT = false;}
      if(ejsmAlVyHl == true){ejsmAlVyHl = false;}
      if(mnwWbFIJnL == true){mnwWbFIJnL = false;}
      if(emusdRgHqA == true){emusdRgHqA = false;}
      if(gNIAPEGYnT == true){gNIAPEGYnT = false;}
      if(RtrRwVVftc == true){RtrRwVVftc = false;}
      if(ognQnrozIh == true){ognQnrozIh = false;}
      if(EOHGFYfuGX == true){EOHGFYfuGX = false;}
      if(yjUTtktdxI == true){yjUTtktdxI = false;}
      if(uANNKzZqLX == true){uANNKzZqLX = false;}
      if(PHQFPCmkMX == true){PHQFPCmkMX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNFASYUCEE
{ 
  void dzTWpMSQCq()
  { 
      bool LpAttFDYRT = false;
      bool QuScDWajhh = false;
      bool OgAkorbkAE = false;
      bool ZaapImcWCV = false;
      bool aLZhnVmNAy = false;
      bool LMmdIeoPFC = false;
      bool cRYNtoUbTQ = false;
      bool sEhMGCHRxS = false;
      bool FOkBrNnwhd = false;
      bool xNQArImLny = false;
      bool BKsiFHeaWF = false;
      bool WXSlwOgWVg = false;
      bool BXspSemgTy = false;
      bool PudyRtVBwj = false;
      bool iNYbGZueDd = false;
      bool bQpHxcQCPZ = false;
      bool TxGYpbsTUC = false;
      bool seakynzRis = false;
      bool jHdpVyEVAn = false;
      bool cSkVPkGzle = false;
      string mezUDCGIOc;
      string imEqjZbXgB;
      string UoXWIGNKxe;
      string SjXjBSQJBQ;
      string YdWpnCNITK;
      string mekjayHcMx;
      string ouLjKyOUoQ;
      string IRVQbpSghF;
      string rEplqnymJD;
      string LmxEbcSmfp;
      string nsSDBVIUIj;
      string fZuGEjFZrW;
      string zaLlFVUQny;
      string XfBrQylmjV;
      string eceYXkrpAr;
      string XstJpMhgxf;
      string ArgJMAYCoF;
      string xRoVqVwmOU;
      string cdQwaekqCE;
      string QFpDVmwUMX;
      if(mezUDCGIOc == nsSDBVIUIj){LpAttFDYRT = true;}
      else if(nsSDBVIUIj == mezUDCGIOc){BKsiFHeaWF = true;}
      if(imEqjZbXgB == fZuGEjFZrW){QuScDWajhh = true;}
      else if(fZuGEjFZrW == imEqjZbXgB){WXSlwOgWVg = true;}
      if(UoXWIGNKxe == zaLlFVUQny){OgAkorbkAE = true;}
      else if(zaLlFVUQny == UoXWIGNKxe){BXspSemgTy = true;}
      if(SjXjBSQJBQ == XfBrQylmjV){ZaapImcWCV = true;}
      else if(XfBrQylmjV == SjXjBSQJBQ){PudyRtVBwj = true;}
      if(YdWpnCNITK == eceYXkrpAr){aLZhnVmNAy = true;}
      else if(eceYXkrpAr == YdWpnCNITK){iNYbGZueDd = true;}
      if(mekjayHcMx == XstJpMhgxf){LMmdIeoPFC = true;}
      else if(XstJpMhgxf == mekjayHcMx){bQpHxcQCPZ = true;}
      if(ouLjKyOUoQ == ArgJMAYCoF){cRYNtoUbTQ = true;}
      else if(ArgJMAYCoF == ouLjKyOUoQ){TxGYpbsTUC = true;}
      if(IRVQbpSghF == xRoVqVwmOU){sEhMGCHRxS = true;}
      if(rEplqnymJD == cdQwaekqCE){FOkBrNnwhd = true;}
      if(LmxEbcSmfp == QFpDVmwUMX){xNQArImLny = true;}
      while(xRoVqVwmOU == IRVQbpSghF){seakynzRis = true;}
      while(cdQwaekqCE == cdQwaekqCE){jHdpVyEVAn = true;}
      while(QFpDVmwUMX == QFpDVmwUMX){cSkVPkGzle = true;}
      if(LpAttFDYRT == true){LpAttFDYRT = false;}
      if(QuScDWajhh == true){QuScDWajhh = false;}
      if(OgAkorbkAE == true){OgAkorbkAE = false;}
      if(ZaapImcWCV == true){ZaapImcWCV = false;}
      if(aLZhnVmNAy == true){aLZhnVmNAy = false;}
      if(LMmdIeoPFC == true){LMmdIeoPFC = false;}
      if(cRYNtoUbTQ == true){cRYNtoUbTQ = false;}
      if(sEhMGCHRxS == true){sEhMGCHRxS = false;}
      if(FOkBrNnwhd == true){FOkBrNnwhd = false;}
      if(xNQArImLny == true){xNQArImLny = false;}
      if(BKsiFHeaWF == true){BKsiFHeaWF = false;}
      if(WXSlwOgWVg == true){WXSlwOgWVg = false;}
      if(BXspSemgTy == true){BXspSemgTy = false;}
      if(PudyRtVBwj == true){PudyRtVBwj = false;}
      if(iNYbGZueDd == true){iNYbGZueDd = false;}
      if(bQpHxcQCPZ == true){bQpHxcQCPZ = false;}
      if(TxGYpbsTUC == true){TxGYpbsTUC = false;}
      if(seakynzRis == true){seakynzRis = false;}
      if(jHdpVyEVAn == true){jHdpVyEVAn = false;}
      if(cSkVPkGzle == true){cSkVPkGzle = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWATSFPOAD
{ 
  void YbnmPaQwiU()
  { 
      bool dxFruIsDze = false;
      bool qqFbHNWpyu = false;
      bool mKOQLtdnfR = false;
      bool pasYfJQjxx = false;
      bool CRkPEfsnkC = false;
      bool YDhWqThofB = false;
      bool eEWhnPxfwy = false;
      bool wlrAsVYzLf = false;
      bool BoDdrmsWhL = false;
      bool bbEwSxtCbn = false;
      bool hMrmGlKhdV = false;
      bool uicAzoBspB = false;
      bool WayjVUhugu = false;
      bool aVXWxnxPXF = false;
      bool bLrMPsyExc = false;
      bool wBMaRHOHQk = false;
      bool EOAhtZKGCK = false;
      bool rkVjYKilTc = false;
      bool VdyDzYIxFo = false;
      bool ZozlAMLJRp = false;
      string ZGnFYQYTdu;
      string DLHNnXYmVd;
      string VgsfPNJCxI;
      string ppVRIhiMww;
      string VkQZqfODcO;
      string jsrWwsNIoK;
      string GWVUEMppFF;
      string nLpYIjPTni;
      string zFZhYxxyUP;
      string UaXlpzOuUd;
      string oYyWaXCTNL;
      string ctTFKAwnwH;
      string OqUpkMnDiJ;
      string VUyKsaHCGA;
      string tdjIlZGRbo;
      string CazMPyDIlN;
      string jyjEpIuJLi;
      string ssgwMjGLDK;
      string GWbsGuUktu;
      string XyPrPutfSd;
      if(ZGnFYQYTdu == oYyWaXCTNL){dxFruIsDze = true;}
      else if(oYyWaXCTNL == ZGnFYQYTdu){hMrmGlKhdV = true;}
      if(DLHNnXYmVd == ctTFKAwnwH){qqFbHNWpyu = true;}
      else if(ctTFKAwnwH == DLHNnXYmVd){uicAzoBspB = true;}
      if(VgsfPNJCxI == OqUpkMnDiJ){mKOQLtdnfR = true;}
      else if(OqUpkMnDiJ == VgsfPNJCxI){WayjVUhugu = true;}
      if(ppVRIhiMww == VUyKsaHCGA){pasYfJQjxx = true;}
      else if(VUyKsaHCGA == ppVRIhiMww){aVXWxnxPXF = true;}
      if(VkQZqfODcO == tdjIlZGRbo){CRkPEfsnkC = true;}
      else if(tdjIlZGRbo == VkQZqfODcO){bLrMPsyExc = true;}
      if(jsrWwsNIoK == CazMPyDIlN){YDhWqThofB = true;}
      else if(CazMPyDIlN == jsrWwsNIoK){wBMaRHOHQk = true;}
      if(GWVUEMppFF == jyjEpIuJLi){eEWhnPxfwy = true;}
      else if(jyjEpIuJLi == GWVUEMppFF){EOAhtZKGCK = true;}
      if(nLpYIjPTni == ssgwMjGLDK){wlrAsVYzLf = true;}
      if(zFZhYxxyUP == GWbsGuUktu){BoDdrmsWhL = true;}
      if(UaXlpzOuUd == XyPrPutfSd){bbEwSxtCbn = true;}
      while(ssgwMjGLDK == nLpYIjPTni){rkVjYKilTc = true;}
      while(GWbsGuUktu == GWbsGuUktu){VdyDzYIxFo = true;}
      while(XyPrPutfSd == XyPrPutfSd){ZozlAMLJRp = true;}
      if(dxFruIsDze == true){dxFruIsDze = false;}
      if(qqFbHNWpyu == true){qqFbHNWpyu = false;}
      if(mKOQLtdnfR == true){mKOQLtdnfR = false;}
      if(pasYfJQjxx == true){pasYfJQjxx = false;}
      if(CRkPEfsnkC == true){CRkPEfsnkC = false;}
      if(YDhWqThofB == true){YDhWqThofB = false;}
      if(eEWhnPxfwy == true){eEWhnPxfwy = false;}
      if(wlrAsVYzLf == true){wlrAsVYzLf = false;}
      if(BoDdrmsWhL == true){BoDdrmsWhL = false;}
      if(bbEwSxtCbn == true){bbEwSxtCbn = false;}
      if(hMrmGlKhdV == true){hMrmGlKhdV = false;}
      if(uicAzoBspB == true){uicAzoBspB = false;}
      if(WayjVUhugu == true){WayjVUhugu = false;}
      if(aVXWxnxPXF == true){aVXWxnxPXF = false;}
      if(bLrMPsyExc == true){bLrMPsyExc = false;}
      if(wBMaRHOHQk == true){wBMaRHOHQk = false;}
      if(EOAhtZKGCK == true){EOAhtZKGCK = false;}
      if(rkVjYKilTc == true){rkVjYKilTc = false;}
      if(VdyDzYIxFo == true){VdyDzYIxFo = false;}
      if(ZozlAMLJRp == true){ZozlAMLJRp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HVBIWEQZFP
{ 
  void HSibAglGmD()
  { 
      bool MwmEyJMTdh = false;
      bool TxRfqNRBaN = false;
      bool KWhsucrcUD = false;
      bool QhBmmMkIAF = false;
      bool hFsFtQiiIC = false;
      bool iYGBlpOtIV = false;
      bool QjzaQkwdre = false;
      bool bIAUfFccze = false;
      bool sJURUqbAAx = false;
      bool yqAenxFRoI = false;
      bool UEpcaaYkUf = false;
      bool MludbHPhGY = false;
      bool JucugkHUfh = false;
      bool ALmpKoSqqs = false;
      bool SpeUjMwVDg = false;
      bool hXLPyYauwo = false;
      bool SDFmfByETl = false;
      bool nXpMFTQILT = false;
      bool olRyAbzWrk = false;
      bool NXuBaOkroh = false;
      string DfDzsNZzak;
      string frMDqVqkwE;
      string fOJPYfJmoe;
      string QLLKmcpZLM;
      string GcplKDDkCJ;
      string WeKTuoWnaM;
      string EmJwUTfCQN;
      string eRYiyDYWEV;
      string bXjfHkBrOy;
      string GCzyISTsRq;
      string WAUndEFaUr;
      string PziEkfCdni;
      string RmmSHcSaae;
      string jeFMyaCuBC;
      string eZWWhGStNb;
      string PoFhYjNCgB;
      string leApIksVGJ;
      string dGckDqPPjA;
      string JYNyOtZWmN;
      string NAOAQAZgOx;
      if(DfDzsNZzak == WAUndEFaUr){MwmEyJMTdh = true;}
      else if(WAUndEFaUr == DfDzsNZzak){UEpcaaYkUf = true;}
      if(frMDqVqkwE == PziEkfCdni){TxRfqNRBaN = true;}
      else if(PziEkfCdni == frMDqVqkwE){MludbHPhGY = true;}
      if(fOJPYfJmoe == RmmSHcSaae){KWhsucrcUD = true;}
      else if(RmmSHcSaae == fOJPYfJmoe){JucugkHUfh = true;}
      if(QLLKmcpZLM == jeFMyaCuBC){QhBmmMkIAF = true;}
      else if(jeFMyaCuBC == QLLKmcpZLM){ALmpKoSqqs = true;}
      if(GcplKDDkCJ == eZWWhGStNb){hFsFtQiiIC = true;}
      else if(eZWWhGStNb == GcplKDDkCJ){SpeUjMwVDg = true;}
      if(WeKTuoWnaM == PoFhYjNCgB){iYGBlpOtIV = true;}
      else if(PoFhYjNCgB == WeKTuoWnaM){hXLPyYauwo = true;}
      if(EmJwUTfCQN == leApIksVGJ){QjzaQkwdre = true;}
      else if(leApIksVGJ == EmJwUTfCQN){SDFmfByETl = true;}
      if(eRYiyDYWEV == dGckDqPPjA){bIAUfFccze = true;}
      if(bXjfHkBrOy == JYNyOtZWmN){sJURUqbAAx = true;}
      if(GCzyISTsRq == NAOAQAZgOx){yqAenxFRoI = true;}
      while(dGckDqPPjA == eRYiyDYWEV){nXpMFTQILT = true;}
      while(JYNyOtZWmN == JYNyOtZWmN){olRyAbzWrk = true;}
      while(NAOAQAZgOx == NAOAQAZgOx){NXuBaOkroh = true;}
      if(MwmEyJMTdh == true){MwmEyJMTdh = false;}
      if(TxRfqNRBaN == true){TxRfqNRBaN = false;}
      if(KWhsucrcUD == true){KWhsucrcUD = false;}
      if(QhBmmMkIAF == true){QhBmmMkIAF = false;}
      if(hFsFtQiiIC == true){hFsFtQiiIC = false;}
      if(iYGBlpOtIV == true){iYGBlpOtIV = false;}
      if(QjzaQkwdre == true){QjzaQkwdre = false;}
      if(bIAUfFccze == true){bIAUfFccze = false;}
      if(sJURUqbAAx == true){sJURUqbAAx = false;}
      if(yqAenxFRoI == true){yqAenxFRoI = false;}
      if(UEpcaaYkUf == true){UEpcaaYkUf = false;}
      if(MludbHPhGY == true){MludbHPhGY = false;}
      if(JucugkHUfh == true){JucugkHUfh = false;}
      if(ALmpKoSqqs == true){ALmpKoSqqs = false;}
      if(SpeUjMwVDg == true){SpeUjMwVDg = false;}
      if(hXLPyYauwo == true){hXLPyYauwo = false;}
      if(SDFmfByETl == true){SDFmfByETl = false;}
      if(nXpMFTQILT == true){nXpMFTQILT = false;}
      if(olRyAbzWrk == true){olRyAbzWrk = false;}
      if(NXuBaOkroh == true){NXuBaOkroh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXKAOGVRLB
{ 
  void jllAuZksyc()
  { 
      bool tMPZxsjGqA = false;
      bool IAeaQOfMXg = false;
      bool QIEhoSIJVl = false;
      bool lyoitirLSx = false;
      bool kqmPODGSnt = false;
      bool FaZNokIhke = false;
      bool jajEOKKufg = false;
      bool WUtZuYVoSk = false;
      bool LpUagKXbsI = false;
      bool aKamMJGhAD = false;
      bool rLlGXkfzRP = false;
      bool OSOzTtFIXE = false;
      bool liBWGMsHMl = false;
      bool SnoOszEODw = false;
      bool eXJctHubTS = false;
      bool DxKuQIJOzL = false;
      bool qYmfxadzGT = false;
      bool pqFaZOYXcz = false;
      bool QQmthUdsyj = false;
      bool ooOqEFkdfS = false;
      string OAACshVLMK;
      string tefeNmLlkG;
      string OfifcLoPXQ;
      string FoIjCdOdgF;
      string MRuxWkKFUO;
      string hcatSiQUZh;
      string sFnuFEWwci;
      string XgEesxjkIq;
      string BitIhcNNQS;
      string MtDzMGdzrR;
      string ONclqBXwBU;
      string yfLhfJLeMc;
      string qIeJVddFSl;
      string TjsqcmFIRg;
      string ERMuTghUSC;
      string uylPaFiTPM;
      string WScOBOmUFs;
      string ECNfXZwioo;
      string wIlQqUxdQX;
      string DksEJlnytF;
      if(OAACshVLMK == ONclqBXwBU){tMPZxsjGqA = true;}
      else if(ONclqBXwBU == OAACshVLMK){rLlGXkfzRP = true;}
      if(tefeNmLlkG == yfLhfJLeMc){IAeaQOfMXg = true;}
      else if(yfLhfJLeMc == tefeNmLlkG){OSOzTtFIXE = true;}
      if(OfifcLoPXQ == qIeJVddFSl){QIEhoSIJVl = true;}
      else if(qIeJVddFSl == OfifcLoPXQ){liBWGMsHMl = true;}
      if(FoIjCdOdgF == TjsqcmFIRg){lyoitirLSx = true;}
      else if(TjsqcmFIRg == FoIjCdOdgF){SnoOszEODw = true;}
      if(MRuxWkKFUO == ERMuTghUSC){kqmPODGSnt = true;}
      else if(ERMuTghUSC == MRuxWkKFUO){eXJctHubTS = true;}
      if(hcatSiQUZh == uylPaFiTPM){FaZNokIhke = true;}
      else if(uylPaFiTPM == hcatSiQUZh){DxKuQIJOzL = true;}
      if(sFnuFEWwci == WScOBOmUFs){jajEOKKufg = true;}
      else if(WScOBOmUFs == sFnuFEWwci){qYmfxadzGT = true;}
      if(XgEesxjkIq == ECNfXZwioo){WUtZuYVoSk = true;}
      if(BitIhcNNQS == wIlQqUxdQX){LpUagKXbsI = true;}
      if(MtDzMGdzrR == DksEJlnytF){aKamMJGhAD = true;}
      while(ECNfXZwioo == XgEesxjkIq){pqFaZOYXcz = true;}
      while(wIlQqUxdQX == wIlQqUxdQX){QQmthUdsyj = true;}
      while(DksEJlnytF == DksEJlnytF){ooOqEFkdfS = true;}
      if(tMPZxsjGqA == true){tMPZxsjGqA = false;}
      if(IAeaQOfMXg == true){IAeaQOfMXg = false;}
      if(QIEhoSIJVl == true){QIEhoSIJVl = false;}
      if(lyoitirLSx == true){lyoitirLSx = false;}
      if(kqmPODGSnt == true){kqmPODGSnt = false;}
      if(FaZNokIhke == true){FaZNokIhke = false;}
      if(jajEOKKufg == true){jajEOKKufg = false;}
      if(WUtZuYVoSk == true){WUtZuYVoSk = false;}
      if(LpUagKXbsI == true){LpUagKXbsI = false;}
      if(aKamMJGhAD == true){aKamMJGhAD = false;}
      if(rLlGXkfzRP == true){rLlGXkfzRP = false;}
      if(OSOzTtFIXE == true){OSOzTtFIXE = false;}
      if(liBWGMsHMl == true){liBWGMsHMl = false;}
      if(SnoOszEODw == true){SnoOszEODw = false;}
      if(eXJctHubTS == true){eXJctHubTS = false;}
      if(DxKuQIJOzL == true){DxKuQIJOzL = false;}
      if(qYmfxadzGT == true){qYmfxadzGT = false;}
      if(pqFaZOYXcz == true){pqFaZOYXcz = false;}
      if(QQmthUdsyj == true){QQmthUdsyj = false;}
      if(ooOqEFkdfS == true){ooOqEFkdfS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRPQOFAJVF
{ 
  void LDhuyIgwaT()
  { 
      bool CQfnrHHAZZ = false;
      bool GtpGMTGeqf = false;
      bool RcIYJpgHnN = false;
      bool ooCAwgDwMW = false;
      bool ipcGJAVTSw = false;
      bool GlWefYHGdC = false;
      bool ZAMMjQqpKe = false;
      bool PKRTwaACOJ = false;
      bool TNnrHDRXTW = false;
      bool ZwRKxhdQVs = false;
      bool IfJmfuTDhE = false;
      bool YFrThMMUEg = false;
      bool yTVmFSrHVO = false;
      bool xjfVAmDALL = false;
      bool iOoOyTEybk = false;
      bool VILouoKWgM = false;
      bool DMgTHnZVTu = false;
      bool ILIsyidGol = false;
      bool OteksnYpaK = false;
      bool cgSyIVgVHJ = false;
      string agfuGmFWeS;
      string DyrzgYPmiE;
      string WzPdItuAkd;
      string QMLIliKYLn;
      string HLbgdjnEid;
      string BtdMSbRCmM;
      string rElABqmjNx;
      string NqatxKWhAX;
      string FpQHcWizoK;
      string QIkzuDZaem;
      string xDqkPJSiPH;
      string EiCPGBmdWe;
      string HmuDgEFbzs;
      string kuDMZCzeqT;
      string DAjgFhGVrt;
      string PuEAfJImEL;
      string DqjVVIfooE;
      string CImDaGDNxy;
      string yjjEdpqCfP;
      string tLafPMQOKx;
      if(agfuGmFWeS == xDqkPJSiPH){CQfnrHHAZZ = true;}
      else if(xDqkPJSiPH == agfuGmFWeS){IfJmfuTDhE = true;}
      if(DyrzgYPmiE == EiCPGBmdWe){GtpGMTGeqf = true;}
      else if(EiCPGBmdWe == DyrzgYPmiE){YFrThMMUEg = true;}
      if(WzPdItuAkd == HmuDgEFbzs){RcIYJpgHnN = true;}
      else if(HmuDgEFbzs == WzPdItuAkd){yTVmFSrHVO = true;}
      if(QMLIliKYLn == kuDMZCzeqT){ooCAwgDwMW = true;}
      else if(kuDMZCzeqT == QMLIliKYLn){xjfVAmDALL = true;}
      if(HLbgdjnEid == DAjgFhGVrt){ipcGJAVTSw = true;}
      else if(DAjgFhGVrt == HLbgdjnEid){iOoOyTEybk = true;}
      if(BtdMSbRCmM == PuEAfJImEL){GlWefYHGdC = true;}
      else if(PuEAfJImEL == BtdMSbRCmM){VILouoKWgM = true;}
      if(rElABqmjNx == DqjVVIfooE){ZAMMjQqpKe = true;}
      else if(DqjVVIfooE == rElABqmjNx){DMgTHnZVTu = true;}
      if(NqatxKWhAX == CImDaGDNxy){PKRTwaACOJ = true;}
      if(FpQHcWizoK == yjjEdpqCfP){TNnrHDRXTW = true;}
      if(QIkzuDZaem == tLafPMQOKx){ZwRKxhdQVs = true;}
      while(CImDaGDNxy == NqatxKWhAX){ILIsyidGol = true;}
      while(yjjEdpqCfP == yjjEdpqCfP){OteksnYpaK = true;}
      while(tLafPMQOKx == tLafPMQOKx){cgSyIVgVHJ = true;}
      if(CQfnrHHAZZ == true){CQfnrHHAZZ = false;}
      if(GtpGMTGeqf == true){GtpGMTGeqf = false;}
      if(RcIYJpgHnN == true){RcIYJpgHnN = false;}
      if(ooCAwgDwMW == true){ooCAwgDwMW = false;}
      if(ipcGJAVTSw == true){ipcGJAVTSw = false;}
      if(GlWefYHGdC == true){GlWefYHGdC = false;}
      if(ZAMMjQqpKe == true){ZAMMjQqpKe = false;}
      if(PKRTwaACOJ == true){PKRTwaACOJ = false;}
      if(TNnrHDRXTW == true){TNnrHDRXTW = false;}
      if(ZwRKxhdQVs == true){ZwRKxhdQVs = false;}
      if(IfJmfuTDhE == true){IfJmfuTDhE = false;}
      if(YFrThMMUEg == true){YFrThMMUEg = false;}
      if(yTVmFSrHVO == true){yTVmFSrHVO = false;}
      if(xjfVAmDALL == true){xjfVAmDALL = false;}
      if(iOoOyTEybk == true){iOoOyTEybk = false;}
      if(VILouoKWgM == true){VILouoKWgM = false;}
      if(DMgTHnZVTu == true){DMgTHnZVTu = false;}
      if(ILIsyidGol == true){ILIsyidGol = false;}
      if(OteksnYpaK == true){OteksnYpaK = false;}
      if(cgSyIVgVHJ == true){cgSyIVgVHJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CREZIBVDYY
{ 
  void PMeWMBEUUG()
  { 
      bool lGIMNyEMhn = false;
      bool TKwuqGeGtB = false;
      bool RzloMnCsdJ = false;
      bool ZEpEWIfiAK = false;
      bool ulzETUKjsB = false;
      bool ylGrqlUSAY = false;
      bool uLiYNPUqYh = false;
      bool auGiFeAgVq = false;
      bool dRAbKmyxNj = false;
      bool nMhbOjDZpE = false;
      bool zSLKaCfWmL = false;
      bool lmxJtcLGNZ = false;
      bool RWdotONdTU = false;
      bool aZqRrLGoBI = false;
      bool HaKBxAOYgl = false;
      bool YwLPmbnWQM = false;
      bool oBCRkLwfQh = false;
      bool VVEFSpMbqs = false;
      bool znxhwdOadP = false;
      bool WjYoSFXrQl = false;
      string OKwUCPPyaN;
      string kdOenFXOoW;
      string LFIZhkofbG;
      string ltaDAHmRow;
      string iZMphlkaOa;
      string dClfWJCWmR;
      string ZjVUbqDLdg;
      string RGYsnlrRqu;
      string zNRAciHufq;
      string EQdWVzDrOq;
      string hZxgIXdsqk;
      string QkeqRMSUrr;
      string iIemcBbBXo;
      string iADANZQjqE;
      string FODuZTkmFJ;
      string fhAVHZtJEH;
      string wbUCBQgddr;
      string uhcmmTFiNI;
      string PowOIAzhrn;
      string fGfjIdsAsI;
      if(OKwUCPPyaN == hZxgIXdsqk){lGIMNyEMhn = true;}
      else if(hZxgIXdsqk == OKwUCPPyaN){zSLKaCfWmL = true;}
      if(kdOenFXOoW == QkeqRMSUrr){TKwuqGeGtB = true;}
      else if(QkeqRMSUrr == kdOenFXOoW){lmxJtcLGNZ = true;}
      if(LFIZhkofbG == iIemcBbBXo){RzloMnCsdJ = true;}
      else if(iIemcBbBXo == LFIZhkofbG){RWdotONdTU = true;}
      if(ltaDAHmRow == iADANZQjqE){ZEpEWIfiAK = true;}
      else if(iADANZQjqE == ltaDAHmRow){aZqRrLGoBI = true;}
      if(iZMphlkaOa == FODuZTkmFJ){ulzETUKjsB = true;}
      else if(FODuZTkmFJ == iZMphlkaOa){HaKBxAOYgl = true;}
      if(dClfWJCWmR == fhAVHZtJEH){ylGrqlUSAY = true;}
      else if(fhAVHZtJEH == dClfWJCWmR){YwLPmbnWQM = true;}
      if(ZjVUbqDLdg == wbUCBQgddr){uLiYNPUqYh = true;}
      else if(wbUCBQgddr == ZjVUbqDLdg){oBCRkLwfQh = true;}
      if(RGYsnlrRqu == uhcmmTFiNI){auGiFeAgVq = true;}
      if(zNRAciHufq == PowOIAzhrn){dRAbKmyxNj = true;}
      if(EQdWVzDrOq == fGfjIdsAsI){nMhbOjDZpE = true;}
      while(uhcmmTFiNI == RGYsnlrRqu){VVEFSpMbqs = true;}
      while(PowOIAzhrn == PowOIAzhrn){znxhwdOadP = true;}
      while(fGfjIdsAsI == fGfjIdsAsI){WjYoSFXrQl = true;}
      if(lGIMNyEMhn == true){lGIMNyEMhn = false;}
      if(TKwuqGeGtB == true){TKwuqGeGtB = false;}
      if(RzloMnCsdJ == true){RzloMnCsdJ = false;}
      if(ZEpEWIfiAK == true){ZEpEWIfiAK = false;}
      if(ulzETUKjsB == true){ulzETUKjsB = false;}
      if(ylGrqlUSAY == true){ylGrqlUSAY = false;}
      if(uLiYNPUqYh == true){uLiYNPUqYh = false;}
      if(auGiFeAgVq == true){auGiFeAgVq = false;}
      if(dRAbKmyxNj == true){dRAbKmyxNj = false;}
      if(nMhbOjDZpE == true){nMhbOjDZpE = false;}
      if(zSLKaCfWmL == true){zSLKaCfWmL = false;}
      if(lmxJtcLGNZ == true){lmxJtcLGNZ = false;}
      if(RWdotONdTU == true){RWdotONdTU = false;}
      if(aZqRrLGoBI == true){aZqRrLGoBI = false;}
      if(HaKBxAOYgl == true){HaKBxAOYgl = false;}
      if(YwLPmbnWQM == true){YwLPmbnWQM = false;}
      if(oBCRkLwfQh == true){oBCRkLwfQh = false;}
      if(VVEFSpMbqs == true){VVEFSpMbqs = false;}
      if(znxhwdOadP == true){znxhwdOadP = false;}
      if(WjYoSFXrQl == true){WjYoSFXrQl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIAKBMLSJW
{ 
  void LwoSFIGMOQ()
  { 
      bool YanhVdrnmT = false;
      bool JgWKTWyGNX = false;
      bool OYisBwZuEI = false;
      bool BaTEttXDlD = false;
      bool pmHtVflgis = false;
      bool nyDRGzqugZ = false;
      bool ExjdShNSPY = false;
      bool ytUJhaRnWU = false;
      bool JsMKUCWBxu = false;
      bool DbWLzsDcam = false;
      bool STQJtsdtjf = false;
      bool gCXLQLkYJQ = false;
      bool LLUUVVXIKo = false;
      bool WoMjCpbCQa = false;
      bool XcQRNAEKum = false;
      bool HeTKbGzwnX = false;
      bool VUjuIrpnJa = false;
      bool jhHhritCGU = false;
      bool RMNWgqVCIu = false;
      bool peOrFDrVJV = false;
      string EUSjCFwnkK;
      string lQGAWBHaRo;
      string IQpmojBAUJ;
      string CrYTaUsOer;
      string dADKuziJqr;
      string BMXlondfuR;
      string EuSaItrlZC;
      string IsuYLHMfqo;
      string AqJbHoTmem;
      string pNTNnhgbCB;
      string HxjojIRzZg;
      string aynGQMlpTS;
      string aFHlLtZhjd;
      string ZjdphDHUrz;
      string WTMxLrYMwb;
      string uqIiaCpxco;
      string ijOuHpTyYN;
      string FQyUuGrJZS;
      string VMkIhibtOe;
      string MJqCPmFRpV;
      if(EUSjCFwnkK == HxjojIRzZg){YanhVdrnmT = true;}
      else if(HxjojIRzZg == EUSjCFwnkK){STQJtsdtjf = true;}
      if(lQGAWBHaRo == aynGQMlpTS){JgWKTWyGNX = true;}
      else if(aynGQMlpTS == lQGAWBHaRo){gCXLQLkYJQ = true;}
      if(IQpmojBAUJ == aFHlLtZhjd){OYisBwZuEI = true;}
      else if(aFHlLtZhjd == IQpmojBAUJ){LLUUVVXIKo = true;}
      if(CrYTaUsOer == ZjdphDHUrz){BaTEttXDlD = true;}
      else if(ZjdphDHUrz == CrYTaUsOer){WoMjCpbCQa = true;}
      if(dADKuziJqr == WTMxLrYMwb){pmHtVflgis = true;}
      else if(WTMxLrYMwb == dADKuziJqr){XcQRNAEKum = true;}
      if(BMXlondfuR == uqIiaCpxco){nyDRGzqugZ = true;}
      else if(uqIiaCpxco == BMXlondfuR){HeTKbGzwnX = true;}
      if(EuSaItrlZC == ijOuHpTyYN){ExjdShNSPY = true;}
      else if(ijOuHpTyYN == EuSaItrlZC){VUjuIrpnJa = true;}
      if(IsuYLHMfqo == FQyUuGrJZS){ytUJhaRnWU = true;}
      if(AqJbHoTmem == VMkIhibtOe){JsMKUCWBxu = true;}
      if(pNTNnhgbCB == MJqCPmFRpV){DbWLzsDcam = true;}
      while(FQyUuGrJZS == IsuYLHMfqo){jhHhritCGU = true;}
      while(VMkIhibtOe == VMkIhibtOe){RMNWgqVCIu = true;}
      while(MJqCPmFRpV == MJqCPmFRpV){peOrFDrVJV = true;}
      if(YanhVdrnmT == true){YanhVdrnmT = false;}
      if(JgWKTWyGNX == true){JgWKTWyGNX = false;}
      if(OYisBwZuEI == true){OYisBwZuEI = false;}
      if(BaTEttXDlD == true){BaTEttXDlD = false;}
      if(pmHtVflgis == true){pmHtVflgis = false;}
      if(nyDRGzqugZ == true){nyDRGzqugZ = false;}
      if(ExjdShNSPY == true){ExjdShNSPY = false;}
      if(ytUJhaRnWU == true){ytUJhaRnWU = false;}
      if(JsMKUCWBxu == true){JsMKUCWBxu = false;}
      if(DbWLzsDcam == true){DbWLzsDcam = false;}
      if(STQJtsdtjf == true){STQJtsdtjf = false;}
      if(gCXLQLkYJQ == true){gCXLQLkYJQ = false;}
      if(LLUUVVXIKo == true){LLUUVVXIKo = false;}
      if(WoMjCpbCQa == true){WoMjCpbCQa = false;}
      if(XcQRNAEKum == true){XcQRNAEKum = false;}
      if(HeTKbGzwnX == true){HeTKbGzwnX = false;}
      if(VUjuIrpnJa == true){VUjuIrpnJa = false;}
      if(jhHhritCGU == true){jhHhritCGU = false;}
      if(RMNWgqVCIu == true){RMNWgqVCIu = false;}
      if(peOrFDrVJV == true){peOrFDrVJV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXIKFVAQEQ
{ 
  void mbteKhOwhW()
  { 
      bool ewFAUhezyM = false;
      bool YQROkynGlY = false;
      bool ibhADxzazf = false;
      bool ffIJQpkkGa = false;
      bool VQqkEzEPxS = false;
      bool NszQBCNFwX = false;
      bool hEARgrIHyt = false;
      bool NCALDSkxuD = false;
      bool sidfSlfqIN = false;
      bool ceoirRPYEM = false;
      bool qxRCFKsnNh = false;
      bool QQJrdzZUzt = false;
      bool LQyjRhMQSk = false;
      bool DLsiMwQaaH = false;
      bool srdawLUxEs = false;
      bool quYJAZzhkW = false;
      bool xbVbeFXaeh = false;
      bool hzsrATmXmF = false;
      bool MPMYtHmihl = false;
      bool xioDJRVBuq = false;
      string zKMRxZdLpi;
      string iNpEHcDLTl;
      string PAOuFkCUyw;
      string SnNtNfOthM;
      string mTgFArZfdC;
      string ZKGONywQLL;
      string WJMsQuzwqb;
      string NJcGywSIuN;
      string KVpuWIgygO;
      string jyhVpdGmnF;
      string rdnBnQgzQQ;
      string emVyBASQWI;
      string NBOcrPaGQU;
      string pfUoUfgnHG;
      string ahhQiwbjUo;
      string LoPerqPLJY;
      string oZhuZzRfdU;
      string TdJPgeSytu;
      string mqlbIBPoxc;
      string QVeiQBzlpj;
      if(zKMRxZdLpi == rdnBnQgzQQ){ewFAUhezyM = true;}
      else if(rdnBnQgzQQ == zKMRxZdLpi){qxRCFKsnNh = true;}
      if(iNpEHcDLTl == emVyBASQWI){YQROkynGlY = true;}
      else if(emVyBASQWI == iNpEHcDLTl){QQJrdzZUzt = true;}
      if(PAOuFkCUyw == NBOcrPaGQU){ibhADxzazf = true;}
      else if(NBOcrPaGQU == PAOuFkCUyw){LQyjRhMQSk = true;}
      if(SnNtNfOthM == pfUoUfgnHG){ffIJQpkkGa = true;}
      else if(pfUoUfgnHG == SnNtNfOthM){DLsiMwQaaH = true;}
      if(mTgFArZfdC == ahhQiwbjUo){VQqkEzEPxS = true;}
      else if(ahhQiwbjUo == mTgFArZfdC){srdawLUxEs = true;}
      if(ZKGONywQLL == LoPerqPLJY){NszQBCNFwX = true;}
      else if(LoPerqPLJY == ZKGONywQLL){quYJAZzhkW = true;}
      if(WJMsQuzwqb == oZhuZzRfdU){hEARgrIHyt = true;}
      else if(oZhuZzRfdU == WJMsQuzwqb){xbVbeFXaeh = true;}
      if(NJcGywSIuN == TdJPgeSytu){NCALDSkxuD = true;}
      if(KVpuWIgygO == mqlbIBPoxc){sidfSlfqIN = true;}
      if(jyhVpdGmnF == QVeiQBzlpj){ceoirRPYEM = true;}
      while(TdJPgeSytu == NJcGywSIuN){hzsrATmXmF = true;}
      while(mqlbIBPoxc == mqlbIBPoxc){MPMYtHmihl = true;}
      while(QVeiQBzlpj == QVeiQBzlpj){xioDJRVBuq = true;}
      if(ewFAUhezyM == true){ewFAUhezyM = false;}
      if(YQROkynGlY == true){YQROkynGlY = false;}
      if(ibhADxzazf == true){ibhADxzazf = false;}
      if(ffIJQpkkGa == true){ffIJQpkkGa = false;}
      if(VQqkEzEPxS == true){VQqkEzEPxS = false;}
      if(NszQBCNFwX == true){NszQBCNFwX = false;}
      if(hEARgrIHyt == true){hEARgrIHyt = false;}
      if(NCALDSkxuD == true){NCALDSkxuD = false;}
      if(sidfSlfqIN == true){sidfSlfqIN = false;}
      if(ceoirRPYEM == true){ceoirRPYEM = false;}
      if(qxRCFKsnNh == true){qxRCFKsnNh = false;}
      if(QQJrdzZUzt == true){QQJrdzZUzt = false;}
      if(LQyjRhMQSk == true){LQyjRhMQSk = false;}
      if(DLsiMwQaaH == true){DLsiMwQaaH = false;}
      if(srdawLUxEs == true){srdawLUxEs = false;}
      if(quYJAZzhkW == true){quYJAZzhkW = false;}
      if(xbVbeFXaeh == true){xbVbeFXaeh = false;}
      if(hzsrATmXmF == true){hzsrATmXmF = false;}
      if(MPMYtHmihl == true){MPMYtHmihl = false;}
      if(xioDJRVBuq == true){xioDJRVBuq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHFEVDETHA
{ 
  void RaQVFHuRUj()
  { 
      bool RrjynimCQZ = false;
      bool FbHMnFRdEu = false;
      bool NqwUHfsaiX = false;
      bool NoKrWyUFic = false;
      bool qHsHKPBWqt = false;
      bool CkCUQZwOqI = false;
      bool pMTrLPRPpp = false;
      bool jMubDGyoKr = false;
      bool dWinVcmobx = false;
      bool CGNZmenAut = false;
      bool ylgBKooaQJ = false;
      bool bHDzeSceWi = false;
      bool cbnrmdyUnY = false;
      bool RxtPtrphdf = false;
      bool mLYRVtCOuT = false;
      bool BJdLRVxnNf = false;
      bool qUlrreNmFl = false;
      bool cuApwQDWWr = false;
      bool aiYUXHShyX = false;
      bool tCTxoSYgYq = false;
      string nkhnxYIULn;
      string AmlUQVMDuk;
      string brEpumzzuZ;
      string olEeUVZPEi;
      string kmQrKFZEEo;
      string fYQpnwgqrJ;
      string ZJYlzOiGzu;
      string wxyLAnaLeo;
      string NttFsQVNpY;
      string nhXuJaNerw;
      string WSFJsiZEpA;
      string UUMCueOTsi;
      string sUPaHNYDCY;
      string ZwTiRuokMJ;
      string pQXpDSVUze;
      string MtlJCCCeBf;
      string JVBQZYBckA;
      string pcGircwZWn;
      string qEEXMeKJgP;
      string rJjfzUOHPe;
      if(nkhnxYIULn == WSFJsiZEpA){RrjynimCQZ = true;}
      else if(WSFJsiZEpA == nkhnxYIULn){ylgBKooaQJ = true;}
      if(AmlUQVMDuk == UUMCueOTsi){FbHMnFRdEu = true;}
      else if(UUMCueOTsi == AmlUQVMDuk){bHDzeSceWi = true;}
      if(brEpumzzuZ == sUPaHNYDCY){NqwUHfsaiX = true;}
      else if(sUPaHNYDCY == brEpumzzuZ){cbnrmdyUnY = true;}
      if(olEeUVZPEi == ZwTiRuokMJ){NoKrWyUFic = true;}
      else if(ZwTiRuokMJ == olEeUVZPEi){RxtPtrphdf = true;}
      if(kmQrKFZEEo == pQXpDSVUze){qHsHKPBWqt = true;}
      else if(pQXpDSVUze == kmQrKFZEEo){mLYRVtCOuT = true;}
      if(fYQpnwgqrJ == MtlJCCCeBf){CkCUQZwOqI = true;}
      else if(MtlJCCCeBf == fYQpnwgqrJ){BJdLRVxnNf = true;}
      if(ZJYlzOiGzu == JVBQZYBckA){pMTrLPRPpp = true;}
      else if(JVBQZYBckA == ZJYlzOiGzu){qUlrreNmFl = true;}
      if(wxyLAnaLeo == pcGircwZWn){jMubDGyoKr = true;}
      if(NttFsQVNpY == qEEXMeKJgP){dWinVcmobx = true;}
      if(nhXuJaNerw == rJjfzUOHPe){CGNZmenAut = true;}
      while(pcGircwZWn == wxyLAnaLeo){cuApwQDWWr = true;}
      while(qEEXMeKJgP == qEEXMeKJgP){aiYUXHShyX = true;}
      while(rJjfzUOHPe == rJjfzUOHPe){tCTxoSYgYq = true;}
      if(RrjynimCQZ == true){RrjynimCQZ = false;}
      if(FbHMnFRdEu == true){FbHMnFRdEu = false;}
      if(NqwUHfsaiX == true){NqwUHfsaiX = false;}
      if(NoKrWyUFic == true){NoKrWyUFic = false;}
      if(qHsHKPBWqt == true){qHsHKPBWqt = false;}
      if(CkCUQZwOqI == true){CkCUQZwOqI = false;}
      if(pMTrLPRPpp == true){pMTrLPRPpp = false;}
      if(jMubDGyoKr == true){jMubDGyoKr = false;}
      if(dWinVcmobx == true){dWinVcmobx = false;}
      if(CGNZmenAut == true){CGNZmenAut = false;}
      if(ylgBKooaQJ == true){ylgBKooaQJ = false;}
      if(bHDzeSceWi == true){bHDzeSceWi = false;}
      if(cbnrmdyUnY == true){cbnrmdyUnY = false;}
      if(RxtPtrphdf == true){RxtPtrphdf = false;}
      if(mLYRVtCOuT == true){mLYRVtCOuT = false;}
      if(BJdLRVxnNf == true){BJdLRVxnNf = false;}
      if(qUlrreNmFl == true){qUlrreNmFl = false;}
      if(cuApwQDWWr == true){cuApwQDWWr = false;}
      if(aiYUXHShyX == true){aiYUXHShyX = false;}
      if(tCTxoSYgYq == true){tCTxoSYgYq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSEDXHFJUL
{ 
  void TCECxuJosW()
  { 
      bool jHYLyabsKl = false;
      bool pcJGzbniMN = false;
      bool VGwjbRCyDV = false;
      bool ImhIeMNZbF = false;
      bool tCgrdxUfTy = false;
      bool SYSCbcLoif = false;
      bool YcoodCuAal = false;
      bool NOGGTTZDFd = false;
      bool xWdFDiUefB = false;
      bool AYqwgQMqOb = false;
      bool CTEgkERLiI = false;
      bool DIiEiBzjlt = false;
      bool gPTYknWKZD = false;
      bool GhodbcRwTy = false;
      bool QJwXyrplMe = false;
      bool RbFTtmzeuw = false;
      bool gHkfBVSEcF = false;
      bool iCPmdWSwas = false;
      bool ykxulebVjn = false;
      bool dmBXRJYQVc = false;
      string lLTnsccsPX;
      string QZEWhUtaYB;
      string UoAofGzDeb;
      string DjTGxXXSGQ;
      string nKeTTEaNbU;
      string HumEIwLeIl;
      string dYOmTgFyYJ;
      string wbUIMKKfVa;
      string fkaKUIxPyB;
      string MrKUmOwqAm;
      string yboSXfaeqx;
      string keJgGryDSL;
      string ipzXxDQAUy;
      string NTfhbDwIlo;
      string hSXAPhidNt;
      string QrXnDIcRVT;
      string OaJsiRyaEC;
      string woQdcQRzHO;
      string UmlZgVwreT;
      string aelSZHIeQy;
      if(lLTnsccsPX == yboSXfaeqx){jHYLyabsKl = true;}
      else if(yboSXfaeqx == lLTnsccsPX){CTEgkERLiI = true;}
      if(QZEWhUtaYB == keJgGryDSL){pcJGzbniMN = true;}
      else if(keJgGryDSL == QZEWhUtaYB){DIiEiBzjlt = true;}
      if(UoAofGzDeb == ipzXxDQAUy){VGwjbRCyDV = true;}
      else if(ipzXxDQAUy == UoAofGzDeb){gPTYknWKZD = true;}
      if(DjTGxXXSGQ == NTfhbDwIlo){ImhIeMNZbF = true;}
      else if(NTfhbDwIlo == DjTGxXXSGQ){GhodbcRwTy = true;}
      if(nKeTTEaNbU == hSXAPhidNt){tCgrdxUfTy = true;}
      else if(hSXAPhidNt == nKeTTEaNbU){QJwXyrplMe = true;}
      if(HumEIwLeIl == QrXnDIcRVT){SYSCbcLoif = true;}
      else if(QrXnDIcRVT == HumEIwLeIl){RbFTtmzeuw = true;}
      if(dYOmTgFyYJ == OaJsiRyaEC){YcoodCuAal = true;}
      else if(OaJsiRyaEC == dYOmTgFyYJ){gHkfBVSEcF = true;}
      if(wbUIMKKfVa == woQdcQRzHO){NOGGTTZDFd = true;}
      if(fkaKUIxPyB == UmlZgVwreT){xWdFDiUefB = true;}
      if(MrKUmOwqAm == aelSZHIeQy){AYqwgQMqOb = true;}
      while(woQdcQRzHO == wbUIMKKfVa){iCPmdWSwas = true;}
      while(UmlZgVwreT == UmlZgVwreT){ykxulebVjn = true;}
      while(aelSZHIeQy == aelSZHIeQy){dmBXRJYQVc = true;}
      if(jHYLyabsKl == true){jHYLyabsKl = false;}
      if(pcJGzbniMN == true){pcJGzbniMN = false;}
      if(VGwjbRCyDV == true){VGwjbRCyDV = false;}
      if(ImhIeMNZbF == true){ImhIeMNZbF = false;}
      if(tCgrdxUfTy == true){tCgrdxUfTy = false;}
      if(SYSCbcLoif == true){SYSCbcLoif = false;}
      if(YcoodCuAal == true){YcoodCuAal = false;}
      if(NOGGTTZDFd == true){NOGGTTZDFd = false;}
      if(xWdFDiUefB == true){xWdFDiUefB = false;}
      if(AYqwgQMqOb == true){AYqwgQMqOb = false;}
      if(CTEgkERLiI == true){CTEgkERLiI = false;}
      if(DIiEiBzjlt == true){DIiEiBzjlt = false;}
      if(gPTYknWKZD == true){gPTYknWKZD = false;}
      if(GhodbcRwTy == true){GhodbcRwTy = false;}
      if(QJwXyrplMe == true){QJwXyrplMe = false;}
      if(RbFTtmzeuw == true){RbFTtmzeuw = false;}
      if(gHkfBVSEcF == true){gHkfBVSEcF = false;}
      if(iCPmdWSwas == true){iCPmdWSwas = false;}
      if(ykxulebVjn == true){ykxulebVjn = false;}
      if(dmBXRJYQVc == true){dmBXRJYQVc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEXIDGZTKJ
{ 
  void UezTjogYIY()
  { 
      bool NoXxuenOxh = false;
      bool QKTcurLeLa = false;
      bool MuVgINmaOh = false;
      bool MgGojZouYO = false;
      bool jgBywOhuIH = false;
      bool UbEKQRTqog = false;
      bool rNAPUjEerU = false;
      bool DQGxqftWjs = false;
      bool fqSHMjcuYS = false;
      bool GyFqVWgkdL = false;
      bool KCDmDDVGTj = false;
      bool XxGwBAtrDk = false;
      bool HIGZOFLOaT = false;
      bool zIsXhcmfDI = false;
      bool NVbntJqIpU = false;
      bool bnhrEBwdYy = false;
      bool rGeAjPDhOX = false;
      bool NOotWkgReE = false;
      bool NDYFqLZATf = false;
      bool fIGFQGpbEe = false;
      string hioCmoSHtf;
      string XVsDHDjmBe;
      string sbFwWLBcgm;
      string NMofbpUSUE;
      string rmEflNxTxA;
      string zwbczGdsea;
      string mpZGRKfMaR;
      string hQSxlFWYJJ;
      string OhegmQkMgV;
      string LamsQBMxNb;
      string hjrfRideps;
      string iEjVMFKsTB;
      string ZSfFFGdYfk;
      string rZKhbdozOE;
      string lGVmmHqRfL;
      string qTdMBODmaK;
      string EEyFAJsCth;
      string QLeOOTxsSy;
      string PMrTsYwyfN;
      string ZCXDzgHPld;
      if(hioCmoSHtf == hjrfRideps){NoXxuenOxh = true;}
      else if(hjrfRideps == hioCmoSHtf){KCDmDDVGTj = true;}
      if(XVsDHDjmBe == iEjVMFKsTB){QKTcurLeLa = true;}
      else if(iEjVMFKsTB == XVsDHDjmBe){XxGwBAtrDk = true;}
      if(sbFwWLBcgm == ZSfFFGdYfk){MuVgINmaOh = true;}
      else if(ZSfFFGdYfk == sbFwWLBcgm){HIGZOFLOaT = true;}
      if(NMofbpUSUE == rZKhbdozOE){MgGojZouYO = true;}
      else if(rZKhbdozOE == NMofbpUSUE){zIsXhcmfDI = true;}
      if(rmEflNxTxA == lGVmmHqRfL){jgBywOhuIH = true;}
      else if(lGVmmHqRfL == rmEflNxTxA){NVbntJqIpU = true;}
      if(zwbczGdsea == qTdMBODmaK){UbEKQRTqog = true;}
      else if(qTdMBODmaK == zwbczGdsea){bnhrEBwdYy = true;}
      if(mpZGRKfMaR == EEyFAJsCth){rNAPUjEerU = true;}
      else if(EEyFAJsCth == mpZGRKfMaR){rGeAjPDhOX = true;}
      if(hQSxlFWYJJ == QLeOOTxsSy){DQGxqftWjs = true;}
      if(OhegmQkMgV == PMrTsYwyfN){fqSHMjcuYS = true;}
      if(LamsQBMxNb == ZCXDzgHPld){GyFqVWgkdL = true;}
      while(QLeOOTxsSy == hQSxlFWYJJ){NOotWkgReE = true;}
      while(PMrTsYwyfN == PMrTsYwyfN){NDYFqLZATf = true;}
      while(ZCXDzgHPld == ZCXDzgHPld){fIGFQGpbEe = true;}
      if(NoXxuenOxh == true){NoXxuenOxh = false;}
      if(QKTcurLeLa == true){QKTcurLeLa = false;}
      if(MuVgINmaOh == true){MuVgINmaOh = false;}
      if(MgGojZouYO == true){MgGojZouYO = false;}
      if(jgBywOhuIH == true){jgBywOhuIH = false;}
      if(UbEKQRTqog == true){UbEKQRTqog = false;}
      if(rNAPUjEerU == true){rNAPUjEerU = false;}
      if(DQGxqftWjs == true){DQGxqftWjs = false;}
      if(fqSHMjcuYS == true){fqSHMjcuYS = false;}
      if(GyFqVWgkdL == true){GyFqVWgkdL = false;}
      if(KCDmDDVGTj == true){KCDmDDVGTj = false;}
      if(XxGwBAtrDk == true){XxGwBAtrDk = false;}
      if(HIGZOFLOaT == true){HIGZOFLOaT = false;}
      if(zIsXhcmfDI == true){zIsXhcmfDI = false;}
      if(NVbntJqIpU == true){NVbntJqIpU = false;}
      if(bnhrEBwdYy == true){bnhrEBwdYy = false;}
      if(rGeAjPDhOX == true){rGeAjPDhOX = false;}
      if(NOotWkgReE == true){NOotWkgReE = false;}
      if(NDYFqLZATf == true){NDYFqLZATf = false;}
      if(fIGFQGpbEe == true){fIGFQGpbEe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOIMZMAHMB
{ 
  void EomJVtwRzD()
  { 
      bool tpLZGmiSRF = false;
      bool FHYHPOcufA = false;
      bool tmQibgStLF = false;
      bool lQRJSxzzpQ = false;
      bool VUKtHcZAty = false;
      bool bgZijHYcxZ = false;
      bool ToHLTnoPnR = false;
      bool OdEPdZcWbz = false;
      bool GRzMdEpiYL = false;
      bool XWBPwfMyaS = false;
      bool mJLbjxbKEK = false;
      bool eCByTBothO = false;
      bool xGqctrcnTy = false;
      bool MdwILwGXcf = false;
      bool bfdNgVVCwt = false;
      bool qRQLUgSihq = false;
      bool UnqGyAGrlW = false;
      bool uRRBmRbdwY = false;
      bool VZqYGtMkme = false;
      bool dWokLnoXPf = false;
      string upMmMzhctR;
      string aYJLtoblZS;
      string crZFVRZLAw;
      string gtWgftAMkG;
      string lfFciqbwrn;
      string LNwgtCQHQt;
      string YVcyjfCceA;
      string oPBSgwmxVe;
      string pdTLjTypmc;
      string csuphPDGrC;
      string oyQqzuMcAy;
      string OTklEtCQNQ;
      string hMpCWuUKkQ;
      string rgETorNbMn;
      string GUooNJHIlm;
      string NmrbTbINUD;
      string aBriFhPRwL;
      string gZDYKNWBnN;
      string nLYxDFnbAN;
      string jzHJNEbGie;
      if(upMmMzhctR == oyQqzuMcAy){tpLZGmiSRF = true;}
      else if(oyQqzuMcAy == upMmMzhctR){mJLbjxbKEK = true;}
      if(aYJLtoblZS == OTklEtCQNQ){FHYHPOcufA = true;}
      else if(OTklEtCQNQ == aYJLtoblZS){eCByTBothO = true;}
      if(crZFVRZLAw == hMpCWuUKkQ){tmQibgStLF = true;}
      else if(hMpCWuUKkQ == crZFVRZLAw){xGqctrcnTy = true;}
      if(gtWgftAMkG == rgETorNbMn){lQRJSxzzpQ = true;}
      else if(rgETorNbMn == gtWgftAMkG){MdwILwGXcf = true;}
      if(lfFciqbwrn == GUooNJHIlm){VUKtHcZAty = true;}
      else if(GUooNJHIlm == lfFciqbwrn){bfdNgVVCwt = true;}
      if(LNwgtCQHQt == NmrbTbINUD){bgZijHYcxZ = true;}
      else if(NmrbTbINUD == LNwgtCQHQt){qRQLUgSihq = true;}
      if(YVcyjfCceA == aBriFhPRwL){ToHLTnoPnR = true;}
      else if(aBriFhPRwL == YVcyjfCceA){UnqGyAGrlW = true;}
      if(oPBSgwmxVe == gZDYKNWBnN){OdEPdZcWbz = true;}
      if(pdTLjTypmc == nLYxDFnbAN){GRzMdEpiYL = true;}
      if(csuphPDGrC == jzHJNEbGie){XWBPwfMyaS = true;}
      while(gZDYKNWBnN == oPBSgwmxVe){uRRBmRbdwY = true;}
      while(nLYxDFnbAN == nLYxDFnbAN){VZqYGtMkme = true;}
      while(jzHJNEbGie == jzHJNEbGie){dWokLnoXPf = true;}
      if(tpLZGmiSRF == true){tpLZGmiSRF = false;}
      if(FHYHPOcufA == true){FHYHPOcufA = false;}
      if(tmQibgStLF == true){tmQibgStLF = false;}
      if(lQRJSxzzpQ == true){lQRJSxzzpQ = false;}
      if(VUKtHcZAty == true){VUKtHcZAty = false;}
      if(bgZijHYcxZ == true){bgZijHYcxZ = false;}
      if(ToHLTnoPnR == true){ToHLTnoPnR = false;}
      if(OdEPdZcWbz == true){OdEPdZcWbz = false;}
      if(GRzMdEpiYL == true){GRzMdEpiYL = false;}
      if(XWBPwfMyaS == true){XWBPwfMyaS = false;}
      if(mJLbjxbKEK == true){mJLbjxbKEK = false;}
      if(eCByTBothO == true){eCByTBothO = false;}
      if(xGqctrcnTy == true){xGqctrcnTy = false;}
      if(MdwILwGXcf == true){MdwILwGXcf = false;}
      if(bfdNgVVCwt == true){bfdNgVVCwt = false;}
      if(qRQLUgSihq == true){qRQLUgSihq = false;}
      if(UnqGyAGrlW == true){UnqGyAGrlW = false;}
      if(uRRBmRbdwY == true){uRRBmRbdwY = false;}
      if(VZqYGtMkme == true){VZqYGtMkme = false;}
      if(dWokLnoXPf == true){dWokLnoXPf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNLJVXRVIT
{ 
  void DBtBzPlRla()
  { 
      bool EbSWECKPbZ = false;
      bool eKSDKSixmL = false;
      bool lBEGnfcHQT = false;
      bool pMMVDymJeV = false;
      bool OjAIcaixkw = false;
      bool dtXcBDXMhX = false;
      bool YDyHjRxxzM = false;
      bool eYSRxBAwcN = false;
      bool xfVUowoiUz = false;
      bool aaaHwLlrXK = false;
      bool ckxYQFbFfz = false;
      bool CbiUasgcSn = false;
      bool cOcAkExKVl = false;
      bool PIXSjLhxEj = false;
      bool UiDUwyqGgD = false;
      bool dIZjhOIxmL = false;
      bool HQjtitDQjO = false;
      bool LjYhTsLHDl = false;
      bool MqdSHHhnkV = false;
      bool DjJrcDyIlC = false;
      string ngyoZfNTio;
      string mSEiOPxaPE;
      string pwILzNhIVM;
      string IBhWwXfzeu;
      string bzlBClYusL;
      string LmXsSqXmoL;
      string xFxVflkhlq;
      string ixuTbqKHIN;
      string nlOKBUdnDF;
      string zsJSxWBPUQ;
      string AqICbNrDQb;
      string fQdbWLplTK;
      string IwdgqpnbVE;
      string oulqMxcLhn;
      string cZXbYiOhwl;
      string gOuJIEMbLl;
      string YPhLlkdmOY;
      string hdEfhhYCII;
      string aGfjXZzciI;
      string kBAwONrLom;
      if(ngyoZfNTio == AqICbNrDQb){EbSWECKPbZ = true;}
      else if(AqICbNrDQb == ngyoZfNTio){ckxYQFbFfz = true;}
      if(mSEiOPxaPE == fQdbWLplTK){eKSDKSixmL = true;}
      else if(fQdbWLplTK == mSEiOPxaPE){CbiUasgcSn = true;}
      if(pwILzNhIVM == IwdgqpnbVE){lBEGnfcHQT = true;}
      else if(IwdgqpnbVE == pwILzNhIVM){cOcAkExKVl = true;}
      if(IBhWwXfzeu == oulqMxcLhn){pMMVDymJeV = true;}
      else if(oulqMxcLhn == IBhWwXfzeu){PIXSjLhxEj = true;}
      if(bzlBClYusL == cZXbYiOhwl){OjAIcaixkw = true;}
      else if(cZXbYiOhwl == bzlBClYusL){UiDUwyqGgD = true;}
      if(LmXsSqXmoL == gOuJIEMbLl){dtXcBDXMhX = true;}
      else if(gOuJIEMbLl == LmXsSqXmoL){dIZjhOIxmL = true;}
      if(xFxVflkhlq == YPhLlkdmOY){YDyHjRxxzM = true;}
      else if(YPhLlkdmOY == xFxVflkhlq){HQjtitDQjO = true;}
      if(ixuTbqKHIN == hdEfhhYCII){eYSRxBAwcN = true;}
      if(nlOKBUdnDF == aGfjXZzciI){xfVUowoiUz = true;}
      if(zsJSxWBPUQ == kBAwONrLom){aaaHwLlrXK = true;}
      while(hdEfhhYCII == ixuTbqKHIN){LjYhTsLHDl = true;}
      while(aGfjXZzciI == aGfjXZzciI){MqdSHHhnkV = true;}
      while(kBAwONrLom == kBAwONrLom){DjJrcDyIlC = true;}
      if(EbSWECKPbZ == true){EbSWECKPbZ = false;}
      if(eKSDKSixmL == true){eKSDKSixmL = false;}
      if(lBEGnfcHQT == true){lBEGnfcHQT = false;}
      if(pMMVDymJeV == true){pMMVDymJeV = false;}
      if(OjAIcaixkw == true){OjAIcaixkw = false;}
      if(dtXcBDXMhX == true){dtXcBDXMhX = false;}
      if(YDyHjRxxzM == true){YDyHjRxxzM = false;}
      if(eYSRxBAwcN == true){eYSRxBAwcN = false;}
      if(xfVUowoiUz == true){xfVUowoiUz = false;}
      if(aaaHwLlrXK == true){aaaHwLlrXK = false;}
      if(ckxYQFbFfz == true){ckxYQFbFfz = false;}
      if(CbiUasgcSn == true){CbiUasgcSn = false;}
      if(cOcAkExKVl == true){cOcAkExKVl = false;}
      if(PIXSjLhxEj == true){PIXSjLhxEj = false;}
      if(UiDUwyqGgD == true){UiDUwyqGgD = false;}
      if(dIZjhOIxmL == true){dIZjhOIxmL = false;}
      if(HQjtitDQjO == true){HQjtitDQjO = false;}
      if(LjYhTsLHDl == true){LjYhTsLHDl = false;}
      if(MqdSHHhnkV == true){MqdSHHhnkV = false;}
      if(DjJrcDyIlC == true){DjJrcDyIlC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQUVCJBQJO
{ 
  void Ybhogwakan()
  { 
      bool BlJXLggKlQ = false;
      bool zpJzNVGJFj = false;
      bool TgRxKOfaFg = false;
      bool rpBUmUVFVg = false;
      bool fVIxOLrHRe = false;
      bool nsoHPUTLNw = false;
      bool AFEFXInnLs = false;
      bool zBnYDyXUhy = false;
      bool WYJZryBtFS = false;
      bool AKqYgaQDYG = false;
      bool WEwYemFPDR = false;
      bool wzcOZbweNZ = false;
      bool HthrroJOrc = false;
      bool gUubaSbkuE = false;
      bool skqnWBgbzE = false;
      bool dlpzzcVDfo = false;
      bool cpXZjaDAmH = false;
      bool zLjIgVDtVq = false;
      bool IgPmyuewcy = false;
      bool wYEFaCMQEu = false;
      string gCufjdgeBQ;
      string CeuRLAFiXh;
      string kMlOmjhsgm;
      string dQLczdEYjE;
      string sqoHmDiRoo;
      string hyUrqUPgsA;
      string unyNllTSRh;
      string wfzSosXdai;
      string BPDrEewSke;
      string OXfjIFsaVB;
      string jPAHrCzBDx;
      string wkFKyfjFJH;
      string pAgmSYAOKi;
      string AxIZykPwzC;
      string etOnhdRUkc;
      string UmQNLjiNnT;
      string BjqUxzbfLM;
      string QnGGbukrEo;
      string GedgOMftNN;
      string CBHeBuDtqi;
      if(gCufjdgeBQ == jPAHrCzBDx){BlJXLggKlQ = true;}
      else if(jPAHrCzBDx == gCufjdgeBQ){WEwYemFPDR = true;}
      if(CeuRLAFiXh == wkFKyfjFJH){zpJzNVGJFj = true;}
      else if(wkFKyfjFJH == CeuRLAFiXh){wzcOZbweNZ = true;}
      if(kMlOmjhsgm == pAgmSYAOKi){TgRxKOfaFg = true;}
      else if(pAgmSYAOKi == kMlOmjhsgm){HthrroJOrc = true;}
      if(dQLczdEYjE == AxIZykPwzC){rpBUmUVFVg = true;}
      else if(AxIZykPwzC == dQLczdEYjE){gUubaSbkuE = true;}
      if(sqoHmDiRoo == etOnhdRUkc){fVIxOLrHRe = true;}
      else if(etOnhdRUkc == sqoHmDiRoo){skqnWBgbzE = true;}
      if(hyUrqUPgsA == UmQNLjiNnT){nsoHPUTLNw = true;}
      else if(UmQNLjiNnT == hyUrqUPgsA){dlpzzcVDfo = true;}
      if(unyNllTSRh == BjqUxzbfLM){AFEFXInnLs = true;}
      else if(BjqUxzbfLM == unyNllTSRh){cpXZjaDAmH = true;}
      if(wfzSosXdai == QnGGbukrEo){zBnYDyXUhy = true;}
      if(BPDrEewSke == GedgOMftNN){WYJZryBtFS = true;}
      if(OXfjIFsaVB == CBHeBuDtqi){AKqYgaQDYG = true;}
      while(QnGGbukrEo == wfzSosXdai){zLjIgVDtVq = true;}
      while(GedgOMftNN == GedgOMftNN){IgPmyuewcy = true;}
      while(CBHeBuDtqi == CBHeBuDtqi){wYEFaCMQEu = true;}
      if(BlJXLggKlQ == true){BlJXLggKlQ = false;}
      if(zpJzNVGJFj == true){zpJzNVGJFj = false;}
      if(TgRxKOfaFg == true){TgRxKOfaFg = false;}
      if(rpBUmUVFVg == true){rpBUmUVFVg = false;}
      if(fVIxOLrHRe == true){fVIxOLrHRe = false;}
      if(nsoHPUTLNw == true){nsoHPUTLNw = false;}
      if(AFEFXInnLs == true){AFEFXInnLs = false;}
      if(zBnYDyXUhy == true){zBnYDyXUhy = false;}
      if(WYJZryBtFS == true){WYJZryBtFS = false;}
      if(AKqYgaQDYG == true){AKqYgaQDYG = false;}
      if(WEwYemFPDR == true){WEwYemFPDR = false;}
      if(wzcOZbweNZ == true){wzcOZbweNZ = false;}
      if(HthrroJOrc == true){HthrroJOrc = false;}
      if(gUubaSbkuE == true){gUubaSbkuE = false;}
      if(skqnWBgbzE == true){skqnWBgbzE = false;}
      if(dlpzzcVDfo == true){dlpzzcVDfo = false;}
      if(cpXZjaDAmH == true){cpXZjaDAmH = false;}
      if(zLjIgVDtVq == true){zLjIgVDtVq = false;}
      if(IgPmyuewcy == true){IgPmyuewcy = false;}
      if(wYEFaCMQEu == true){wYEFaCMQEu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGAASCEIWB
{ 
  void lelskinJUn()
  { 
      bool TXFfJGhlle = false;
      bool FeLNXnZTeZ = false;
      bool xSYNqlBrta = false;
      bool xGTZozxUPN = false;
      bool JpaMlIxywH = false;
      bool PFgDXByqoX = false;
      bool EorLgyLlXX = false;
      bool pFDRQHqLah = false;
      bool nDumKrZQCn = false;
      bool BFerJTxPfn = false;
      bool xLZXQKBPmP = false;
      bool KlQHjAsFAo = false;
      bool XtiiWjZKHw = false;
      bool JafmjbcXVA = false;
      bool pKcldOoXII = false;
      bool ZrPpPDbqBf = false;
      bool jqHpFiFcWH = false;
      bool XVizyNQxFH = false;
      bool uBCyVRKoWg = false;
      bool zlVoPzCmgt = false;
      string UyGsywHqPm;
      string oYHanISShg;
      string fhIJDJYxqu;
      string HJsMLkwWxm;
      string bWZMXiSLiS;
      string CGSsMlpxpn;
      string XKAUffftOD;
      string LwUtEIIulT;
      string pMOXrApAAY;
      string tzgJPQWEgq;
      string DXweHFlXnD;
      string duKVxKwcbe;
      string oetpILOLen;
      string lEOtPRPiPm;
      string OSLwuznLLE;
      string TtbBCXdGWu;
      string qZszRZfQFe;
      string uNMoPWSyuJ;
      string XDAZTqbNrq;
      string nJLUuoYMdU;
      if(UyGsywHqPm == DXweHFlXnD){TXFfJGhlle = true;}
      else if(DXweHFlXnD == UyGsywHqPm){xLZXQKBPmP = true;}
      if(oYHanISShg == duKVxKwcbe){FeLNXnZTeZ = true;}
      else if(duKVxKwcbe == oYHanISShg){KlQHjAsFAo = true;}
      if(fhIJDJYxqu == oetpILOLen){xSYNqlBrta = true;}
      else if(oetpILOLen == fhIJDJYxqu){XtiiWjZKHw = true;}
      if(HJsMLkwWxm == lEOtPRPiPm){xGTZozxUPN = true;}
      else if(lEOtPRPiPm == HJsMLkwWxm){JafmjbcXVA = true;}
      if(bWZMXiSLiS == OSLwuznLLE){JpaMlIxywH = true;}
      else if(OSLwuznLLE == bWZMXiSLiS){pKcldOoXII = true;}
      if(CGSsMlpxpn == TtbBCXdGWu){PFgDXByqoX = true;}
      else if(TtbBCXdGWu == CGSsMlpxpn){ZrPpPDbqBf = true;}
      if(XKAUffftOD == qZszRZfQFe){EorLgyLlXX = true;}
      else if(qZszRZfQFe == XKAUffftOD){jqHpFiFcWH = true;}
      if(LwUtEIIulT == uNMoPWSyuJ){pFDRQHqLah = true;}
      if(pMOXrApAAY == XDAZTqbNrq){nDumKrZQCn = true;}
      if(tzgJPQWEgq == nJLUuoYMdU){BFerJTxPfn = true;}
      while(uNMoPWSyuJ == LwUtEIIulT){XVizyNQxFH = true;}
      while(XDAZTqbNrq == XDAZTqbNrq){uBCyVRKoWg = true;}
      while(nJLUuoYMdU == nJLUuoYMdU){zlVoPzCmgt = true;}
      if(TXFfJGhlle == true){TXFfJGhlle = false;}
      if(FeLNXnZTeZ == true){FeLNXnZTeZ = false;}
      if(xSYNqlBrta == true){xSYNqlBrta = false;}
      if(xGTZozxUPN == true){xGTZozxUPN = false;}
      if(JpaMlIxywH == true){JpaMlIxywH = false;}
      if(PFgDXByqoX == true){PFgDXByqoX = false;}
      if(EorLgyLlXX == true){EorLgyLlXX = false;}
      if(pFDRQHqLah == true){pFDRQHqLah = false;}
      if(nDumKrZQCn == true){nDumKrZQCn = false;}
      if(BFerJTxPfn == true){BFerJTxPfn = false;}
      if(xLZXQKBPmP == true){xLZXQKBPmP = false;}
      if(KlQHjAsFAo == true){KlQHjAsFAo = false;}
      if(XtiiWjZKHw == true){XtiiWjZKHw = false;}
      if(JafmjbcXVA == true){JafmjbcXVA = false;}
      if(pKcldOoXII == true){pKcldOoXII = false;}
      if(ZrPpPDbqBf == true){ZrPpPDbqBf = false;}
      if(jqHpFiFcWH == true){jqHpFiFcWH = false;}
      if(XVizyNQxFH == true){XVizyNQxFH = false;}
      if(uBCyVRKoWg == true){uBCyVRKoWg = false;}
      if(zlVoPzCmgt == true){zlVoPzCmgt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHCFVVEAOR
{ 
  void uLJyxqBhBK()
  { 
      bool XDiQljWGke = false;
      bool sacIreUOOG = false;
      bool hMnejSiIPF = false;
      bool CCTACOGKUp = false;
      bool rZzabGiApP = false;
      bool hRADZLPEfT = false;
      bool BNqebpGcFd = false;
      bool YJtXOIMMCd = false;
      bool jhRzWjCQaq = false;
      bool yCdAodiTyk = false;
      bool zGuMqYWcnR = false;
      bool zDBCjSuqIr = false;
      bool npBOeWeshk = false;
      bool YrNQdcmFIy = false;
      bool NZbJquAbQV = false;
      bool hrLGxJEfhT = false;
      bool tctDrGojXG = false;
      bool fpiKdOOrWi = false;
      bool WCbMCggHTU = false;
      bool XGWnDjeXQk = false;
      string VseQZuFanY;
      string yXyAoNKxMn;
      string gUpAROAuUA;
      string LOEHkynQyq;
      string XEfNhBJiWA;
      string nFQIaBDdyK;
      string uKFmNiSqPq;
      string ZsyUQbocRP;
      string FQYUMGywfi;
      string tJSnwNzrzy;
      string hRSfauGurz;
      string LZMhFdkkaG;
      string kWLfwPZKYC;
      string cxcShmyssQ;
      string zCEgXUxjiR;
      string bNQrNLFljK;
      string VwVoVOwsAR;
      string erqKHiReIa;
      string SpbHaOfjFV;
      string gMJiuCfPKI;
      if(VseQZuFanY == hRSfauGurz){XDiQljWGke = true;}
      else if(hRSfauGurz == VseQZuFanY){zGuMqYWcnR = true;}
      if(yXyAoNKxMn == LZMhFdkkaG){sacIreUOOG = true;}
      else if(LZMhFdkkaG == yXyAoNKxMn){zDBCjSuqIr = true;}
      if(gUpAROAuUA == kWLfwPZKYC){hMnejSiIPF = true;}
      else if(kWLfwPZKYC == gUpAROAuUA){npBOeWeshk = true;}
      if(LOEHkynQyq == cxcShmyssQ){CCTACOGKUp = true;}
      else if(cxcShmyssQ == LOEHkynQyq){YrNQdcmFIy = true;}
      if(XEfNhBJiWA == zCEgXUxjiR){rZzabGiApP = true;}
      else if(zCEgXUxjiR == XEfNhBJiWA){NZbJquAbQV = true;}
      if(nFQIaBDdyK == bNQrNLFljK){hRADZLPEfT = true;}
      else if(bNQrNLFljK == nFQIaBDdyK){hrLGxJEfhT = true;}
      if(uKFmNiSqPq == VwVoVOwsAR){BNqebpGcFd = true;}
      else if(VwVoVOwsAR == uKFmNiSqPq){tctDrGojXG = true;}
      if(ZsyUQbocRP == erqKHiReIa){YJtXOIMMCd = true;}
      if(FQYUMGywfi == SpbHaOfjFV){jhRzWjCQaq = true;}
      if(tJSnwNzrzy == gMJiuCfPKI){yCdAodiTyk = true;}
      while(erqKHiReIa == ZsyUQbocRP){fpiKdOOrWi = true;}
      while(SpbHaOfjFV == SpbHaOfjFV){WCbMCggHTU = true;}
      while(gMJiuCfPKI == gMJiuCfPKI){XGWnDjeXQk = true;}
      if(XDiQljWGke == true){XDiQljWGke = false;}
      if(sacIreUOOG == true){sacIreUOOG = false;}
      if(hMnejSiIPF == true){hMnejSiIPF = false;}
      if(CCTACOGKUp == true){CCTACOGKUp = false;}
      if(rZzabGiApP == true){rZzabGiApP = false;}
      if(hRADZLPEfT == true){hRADZLPEfT = false;}
      if(BNqebpGcFd == true){BNqebpGcFd = false;}
      if(YJtXOIMMCd == true){YJtXOIMMCd = false;}
      if(jhRzWjCQaq == true){jhRzWjCQaq = false;}
      if(yCdAodiTyk == true){yCdAodiTyk = false;}
      if(zGuMqYWcnR == true){zGuMqYWcnR = false;}
      if(zDBCjSuqIr == true){zDBCjSuqIr = false;}
      if(npBOeWeshk == true){npBOeWeshk = false;}
      if(YrNQdcmFIy == true){YrNQdcmFIy = false;}
      if(NZbJquAbQV == true){NZbJquAbQV = false;}
      if(hrLGxJEfhT == true){hrLGxJEfhT = false;}
      if(tctDrGojXG == true){tctDrGojXG = false;}
      if(fpiKdOOrWi == true){fpiKdOOrWi = false;}
      if(WCbMCggHTU == true){WCbMCggHTU = false;}
      if(XGWnDjeXQk == true){XGWnDjeXQk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MTBKHFHMKM
{ 
  void wnSViuGjeI()
  { 
      bool tYVYxrWtVq = false;
      bool OjcCaDQdPB = false;
      bool xIIxEDxUlx = false;
      bool ZFceuWMLfw = false;
      bool eSaxBFJLUT = false;
      bool HmuJMkQYTs = false;
      bool uCIXQJHxGD = false;
      bool pFxSVehKwz = false;
      bool tlARplJSSK = false;
      bool GnqlBcJCgq = false;
      bool xMEQcBpcng = false;
      bool CFbUzJBqhd = false;
      bool AoewxCOKRr = false;
      bool VedECggjnn = false;
      bool wgdkHALVmq = false;
      bool bRTCqHhHSZ = false;
      bool meKuLXbXSR = false;
      bool bQCtgSKsow = false;
      bool qrXZQDKaMt = false;
      bool zZRNARVhYj = false;
      string EAsZjoFuNh;
      string xOkOtwUGKi;
      string bpgxKjNCEf;
      string KcVVJLmIbJ;
      string WNDIWErgPx;
      string RhbJJNSwPA;
      string aCpgWTsPFi;
      string ILdAMOmYaG;
      string qflGOcBMLu;
      string sqsbiTWVkC;
      string LcbgnFDaxu;
      string asUIItQiSt;
      string SfEJoRSCRr;
      string qQmXuOEFSJ;
      string YaPPUzVjSn;
      string DnDqieYRqW;
      string lAIEEKFxNt;
      string pKQIUrQnoo;
      string uijdoCMwnP;
      string olNuWXRLLJ;
      if(EAsZjoFuNh == LcbgnFDaxu){tYVYxrWtVq = true;}
      else if(LcbgnFDaxu == EAsZjoFuNh){xMEQcBpcng = true;}
      if(xOkOtwUGKi == asUIItQiSt){OjcCaDQdPB = true;}
      else if(asUIItQiSt == xOkOtwUGKi){CFbUzJBqhd = true;}
      if(bpgxKjNCEf == SfEJoRSCRr){xIIxEDxUlx = true;}
      else if(SfEJoRSCRr == bpgxKjNCEf){AoewxCOKRr = true;}
      if(KcVVJLmIbJ == qQmXuOEFSJ){ZFceuWMLfw = true;}
      else if(qQmXuOEFSJ == KcVVJLmIbJ){VedECggjnn = true;}
      if(WNDIWErgPx == YaPPUzVjSn){eSaxBFJLUT = true;}
      else if(YaPPUzVjSn == WNDIWErgPx){wgdkHALVmq = true;}
      if(RhbJJNSwPA == DnDqieYRqW){HmuJMkQYTs = true;}
      else if(DnDqieYRqW == RhbJJNSwPA){bRTCqHhHSZ = true;}
      if(aCpgWTsPFi == lAIEEKFxNt){uCIXQJHxGD = true;}
      else if(lAIEEKFxNt == aCpgWTsPFi){meKuLXbXSR = true;}
      if(ILdAMOmYaG == pKQIUrQnoo){pFxSVehKwz = true;}
      if(qflGOcBMLu == uijdoCMwnP){tlARplJSSK = true;}
      if(sqsbiTWVkC == olNuWXRLLJ){GnqlBcJCgq = true;}
      while(pKQIUrQnoo == ILdAMOmYaG){bQCtgSKsow = true;}
      while(uijdoCMwnP == uijdoCMwnP){qrXZQDKaMt = true;}
      while(olNuWXRLLJ == olNuWXRLLJ){zZRNARVhYj = true;}
      if(tYVYxrWtVq == true){tYVYxrWtVq = false;}
      if(OjcCaDQdPB == true){OjcCaDQdPB = false;}
      if(xIIxEDxUlx == true){xIIxEDxUlx = false;}
      if(ZFceuWMLfw == true){ZFceuWMLfw = false;}
      if(eSaxBFJLUT == true){eSaxBFJLUT = false;}
      if(HmuJMkQYTs == true){HmuJMkQYTs = false;}
      if(uCIXQJHxGD == true){uCIXQJHxGD = false;}
      if(pFxSVehKwz == true){pFxSVehKwz = false;}
      if(tlARplJSSK == true){tlARplJSSK = false;}
      if(GnqlBcJCgq == true){GnqlBcJCgq = false;}
      if(xMEQcBpcng == true){xMEQcBpcng = false;}
      if(CFbUzJBqhd == true){CFbUzJBqhd = false;}
      if(AoewxCOKRr == true){AoewxCOKRr = false;}
      if(VedECggjnn == true){VedECggjnn = false;}
      if(wgdkHALVmq == true){wgdkHALVmq = false;}
      if(bRTCqHhHSZ == true){bRTCqHhHSZ = false;}
      if(meKuLXbXSR == true){meKuLXbXSR = false;}
      if(bQCtgSKsow == true){bQCtgSKsow = false;}
      if(qrXZQDKaMt == true){qrXZQDKaMt = false;}
      if(zZRNARVhYj == true){zZRNARVhYj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOQDGECALJ
{ 
  void dGJabDAIuQ()
  { 
      bool XmTCtGVryC = false;
      bool MltcrqcIeN = false;
      bool OsCfZnfbfg = false;
      bool WTBCXQIDXj = false;
      bool wxfZamnMQw = false;
      bool lPVSgejmcG = false;
      bool ZtLRfrkrFa = false;
      bool hYkuQQMbFm = false;
      bool zTLjtGyiUs = false;
      bool gUaQJClNth = false;
      bool CwHoOMeZBQ = false;
      bool RHhoGFhbWY = false;
      bool tCWLsMxTkN = false;
      bool eyhXkDMVVh = false;
      bool bXgEaYmlJE = false;
      bool UKpUnzYuwB = false;
      bool OKonlSZKED = false;
      bool rMFoxVUSkU = false;
      bool ZLJfrUIMik = false;
      bool dRZTSQirSI = false;
      string mItBcblukk;
      string fWDGppHDfy;
      string eruUQdMahT;
      string uXXsBGwNwf;
      string VIDeBWWuyL;
      string dBLPbuNYjz;
      string PKMQoHyKEj;
      string stHAcVnPTt;
      string GRbWptLIRG;
      string sWdwPKwlps;
      string XMpORitLmF;
      string GxFosyioau;
      string upsypVQKjR;
      string ZCZZVsaMEG;
      string zAVLAuRnDR;
      string bGLtxhTrXw;
      string SjaUfEXeTA;
      string WVkTwuUgyu;
      string EbGSpSpecn;
      string ZioImOYAfu;
      if(mItBcblukk == XMpORitLmF){XmTCtGVryC = true;}
      else if(XMpORitLmF == mItBcblukk){CwHoOMeZBQ = true;}
      if(fWDGppHDfy == GxFosyioau){MltcrqcIeN = true;}
      else if(GxFosyioau == fWDGppHDfy){RHhoGFhbWY = true;}
      if(eruUQdMahT == upsypVQKjR){OsCfZnfbfg = true;}
      else if(upsypVQKjR == eruUQdMahT){tCWLsMxTkN = true;}
      if(uXXsBGwNwf == ZCZZVsaMEG){WTBCXQIDXj = true;}
      else if(ZCZZVsaMEG == uXXsBGwNwf){eyhXkDMVVh = true;}
      if(VIDeBWWuyL == zAVLAuRnDR){wxfZamnMQw = true;}
      else if(zAVLAuRnDR == VIDeBWWuyL){bXgEaYmlJE = true;}
      if(dBLPbuNYjz == bGLtxhTrXw){lPVSgejmcG = true;}
      else if(bGLtxhTrXw == dBLPbuNYjz){UKpUnzYuwB = true;}
      if(PKMQoHyKEj == SjaUfEXeTA){ZtLRfrkrFa = true;}
      else if(SjaUfEXeTA == PKMQoHyKEj){OKonlSZKED = true;}
      if(stHAcVnPTt == WVkTwuUgyu){hYkuQQMbFm = true;}
      if(GRbWptLIRG == EbGSpSpecn){zTLjtGyiUs = true;}
      if(sWdwPKwlps == ZioImOYAfu){gUaQJClNth = true;}
      while(WVkTwuUgyu == stHAcVnPTt){rMFoxVUSkU = true;}
      while(EbGSpSpecn == EbGSpSpecn){ZLJfrUIMik = true;}
      while(ZioImOYAfu == ZioImOYAfu){dRZTSQirSI = true;}
      if(XmTCtGVryC == true){XmTCtGVryC = false;}
      if(MltcrqcIeN == true){MltcrqcIeN = false;}
      if(OsCfZnfbfg == true){OsCfZnfbfg = false;}
      if(WTBCXQIDXj == true){WTBCXQIDXj = false;}
      if(wxfZamnMQw == true){wxfZamnMQw = false;}
      if(lPVSgejmcG == true){lPVSgejmcG = false;}
      if(ZtLRfrkrFa == true){ZtLRfrkrFa = false;}
      if(hYkuQQMbFm == true){hYkuQQMbFm = false;}
      if(zTLjtGyiUs == true){zTLjtGyiUs = false;}
      if(gUaQJClNth == true){gUaQJClNth = false;}
      if(CwHoOMeZBQ == true){CwHoOMeZBQ = false;}
      if(RHhoGFhbWY == true){RHhoGFhbWY = false;}
      if(tCWLsMxTkN == true){tCWLsMxTkN = false;}
      if(eyhXkDMVVh == true){eyhXkDMVVh = false;}
      if(bXgEaYmlJE == true){bXgEaYmlJE = false;}
      if(UKpUnzYuwB == true){UKpUnzYuwB = false;}
      if(OKonlSZKED == true){OKonlSZKED = false;}
      if(rMFoxVUSkU == true){rMFoxVUSkU = false;}
      if(ZLJfrUIMik == true){ZLJfrUIMik = false;}
      if(dRZTSQirSI == true){dRZTSQirSI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDLNITXKVJ
{ 
  void fNdSDgVVQt()
  { 
      bool jyADDEZgtA = false;
      bool SVtiShKGlW = false;
      bool rnMZpdIcfe = false;
      bool ZSFffzYZwo = false;
      bool QrlTQaLdXz = false;
      bool zuzSmwkaMZ = false;
      bool uwAOaAPNDS = false;
      bool IkKxFABsIP = false;
      bool ReFgfdSmsj = false;
      bool OyMVsTqWrQ = false;
      bool LxZEqOkCMm = false;
      bool tqRxIQqTix = false;
      bool gcUSEJYnEl = false;
      bool IeBrEUEApQ = false;
      bool rQZGpWfPNc = false;
      bool cXmuihbGAg = false;
      bool pxyadOpZsm = false;
      bool LpcREQCOch = false;
      bool cJabJjrFIV = false;
      bool rxAJauSzbb = false;
      string IrADROaVUP;
      string IgHjfpFajC;
      string HCNLkpnLpj;
      string UVsHpVAtRL;
      string ZAiUAhOKdl;
      string CPSbFFeoSb;
      string aPektmnzsK;
      string pKIYcGTrKC;
      string bdgDgFCQBj;
      string pKapkJVyaN;
      string tOQTwqGtzy;
      string lleQAwiaDo;
      string jWyJTejSnT;
      string kURxHMMMHo;
      string yIRCxEfJpn;
      string ZtukcXQGzR;
      string HnGeNRUgJm;
      string jVTNpbEuMP;
      string yZcAsqYgTj;
      string wGNpgKClof;
      if(IrADROaVUP == tOQTwqGtzy){jyADDEZgtA = true;}
      else if(tOQTwqGtzy == IrADROaVUP){LxZEqOkCMm = true;}
      if(IgHjfpFajC == lleQAwiaDo){SVtiShKGlW = true;}
      else if(lleQAwiaDo == IgHjfpFajC){tqRxIQqTix = true;}
      if(HCNLkpnLpj == jWyJTejSnT){rnMZpdIcfe = true;}
      else if(jWyJTejSnT == HCNLkpnLpj){gcUSEJYnEl = true;}
      if(UVsHpVAtRL == kURxHMMMHo){ZSFffzYZwo = true;}
      else if(kURxHMMMHo == UVsHpVAtRL){IeBrEUEApQ = true;}
      if(ZAiUAhOKdl == yIRCxEfJpn){QrlTQaLdXz = true;}
      else if(yIRCxEfJpn == ZAiUAhOKdl){rQZGpWfPNc = true;}
      if(CPSbFFeoSb == ZtukcXQGzR){zuzSmwkaMZ = true;}
      else if(ZtukcXQGzR == CPSbFFeoSb){cXmuihbGAg = true;}
      if(aPektmnzsK == HnGeNRUgJm){uwAOaAPNDS = true;}
      else if(HnGeNRUgJm == aPektmnzsK){pxyadOpZsm = true;}
      if(pKIYcGTrKC == jVTNpbEuMP){IkKxFABsIP = true;}
      if(bdgDgFCQBj == yZcAsqYgTj){ReFgfdSmsj = true;}
      if(pKapkJVyaN == wGNpgKClof){OyMVsTqWrQ = true;}
      while(jVTNpbEuMP == pKIYcGTrKC){LpcREQCOch = true;}
      while(yZcAsqYgTj == yZcAsqYgTj){cJabJjrFIV = true;}
      while(wGNpgKClof == wGNpgKClof){rxAJauSzbb = true;}
      if(jyADDEZgtA == true){jyADDEZgtA = false;}
      if(SVtiShKGlW == true){SVtiShKGlW = false;}
      if(rnMZpdIcfe == true){rnMZpdIcfe = false;}
      if(ZSFffzYZwo == true){ZSFffzYZwo = false;}
      if(QrlTQaLdXz == true){QrlTQaLdXz = false;}
      if(zuzSmwkaMZ == true){zuzSmwkaMZ = false;}
      if(uwAOaAPNDS == true){uwAOaAPNDS = false;}
      if(IkKxFABsIP == true){IkKxFABsIP = false;}
      if(ReFgfdSmsj == true){ReFgfdSmsj = false;}
      if(OyMVsTqWrQ == true){OyMVsTqWrQ = false;}
      if(LxZEqOkCMm == true){LxZEqOkCMm = false;}
      if(tqRxIQqTix == true){tqRxIQqTix = false;}
      if(gcUSEJYnEl == true){gcUSEJYnEl = false;}
      if(IeBrEUEApQ == true){IeBrEUEApQ = false;}
      if(rQZGpWfPNc == true){rQZGpWfPNc = false;}
      if(cXmuihbGAg == true){cXmuihbGAg = false;}
      if(pxyadOpZsm == true){pxyadOpZsm = false;}
      if(LpcREQCOch == true){LpcREQCOch = false;}
      if(cJabJjrFIV == true){cJabJjrFIV = false;}
      if(rxAJauSzbb == true){rxAJauSzbb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXDQGMUYKD
{ 
  void JFHNgVjVdG()
  { 
      bool XjHBPQXubW = false;
      bool IXrnIffFJR = false;
      bool SXBXrSBcIf = false;
      bool AIJNRrrWnc = false;
      bool kcKeDhlMsj = false;
      bool HdBKTAhiJx = false;
      bool OumwVANdWQ = false;
      bool mJRgfoMWUK = false;
      bool fniXYWHztQ = false;
      bool JINqNppOJD = false;
      bool TIpcwxMTdd = false;
      bool mLOzQZLOWz = false;
      bool rOjFGduaSo = false;
      bool zxMQpXyFba = false;
      bool JmUQdytOZm = false;
      bool ebrJLEYjVR = false;
      bool CkBodoyyIs = false;
      bool bFmuoEtTbI = false;
      bool jgBeKXFCFl = false;
      bool zOiJYYlfln = false;
      string jVoEXQGHzM;
      string mfuTUcHWsm;
      string HRhecuDnDH;
      string fpPNeRLunu;
      string VZhpibgKFQ;
      string kKXiWSmJbb;
      string NRErgxPgoC;
      string QLiyRhirwB;
      string OrhlVUSgqM;
      string dBSLhDVpIl;
      string LzUCzYbZRn;
      string iuNZMUiRVM;
      string diocYPsWQN;
      string MriJoPWflw;
      string rsODcinryM;
      string TDUwHcJrdj;
      string fEIDapLDkx;
      string xDeYTkTlAo;
      string bAXDsJXmCM;
      string FeBCQmjKbl;
      if(jVoEXQGHzM == LzUCzYbZRn){XjHBPQXubW = true;}
      else if(LzUCzYbZRn == jVoEXQGHzM){TIpcwxMTdd = true;}
      if(mfuTUcHWsm == iuNZMUiRVM){IXrnIffFJR = true;}
      else if(iuNZMUiRVM == mfuTUcHWsm){mLOzQZLOWz = true;}
      if(HRhecuDnDH == diocYPsWQN){SXBXrSBcIf = true;}
      else if(diocYPsWQN == HRhecuDnDH){rOjFGduaSo = true;}
      if(fpPNeRLunu == MriJoPWflw){AIJNRrrWnc = true;}
      else if(MriJoPWflw == fpPNeRLunu){zxMQpXyFba = true;}
      if(VZhpibgKFQ == rsODcinryM){kcKeDhlMsj = true;}
      else if(rsODcinryM == VZhpibgKFQ){JmUQdytOZm = true;}
      if(kKXiWSmJbb == TDUwHcJrdj){HdBKTAhiJx = true;}
      else if(TDUwHcJrdj == kKXiWSmJbb){ebrJLEYjVR = true;}
      if(NRErgxPgoC == fEIDapLDkx){OumwVANdWQ = true;}
      else if(fEIDapLDkx == NRErgxPgoC){CkBodoyyIs = true;}
      if(QLiyRhirwB == xDeYTkTlAo){mJRgfoMWUK = true;}
      if(OrhlVUSgqM == bAXDsJXmCM){fniXYWHztQ = true;}
      if(dBSLhDVpIl == FeBCQmjKbl){JINqNppOJD = true;}
      while(xDeYTkTlAo == QLiyRhirwB){bFmuoEtTbI = true;}
      while(bAXDsJXmCM == bAXDsJXmCM){jgBeKXFCFl = true;}
      while(FeBCQmjKbl == FeBCQmjKbl){zOiJYYlfln = true;}
      if(XjHBPQXubW == true){XjHBPQXubW = false;}
      if(IXrnIffFJR == true){IXrnIffFJR = false;}
      if(SXBXrSBcIf == true){SXBXrSBcIf = false;}
      if(AIJNRrrWnc == true){AIJNRrrWnc = false;}
      if(kcKeDhlMsj == true){kcKeDhlMsj = false;}
      if(HdBKTAhiJx == true){HdBKTAhiJx = false;}
      if(OumwVANdWQ == true){OumwVANdWQ = false;}
      if(mJRgfoMWUK == true){mJRgfoMWUK = false;}
      if(fniXYWHztQ == true){fniXYWHztQ = false;}
      if(JINqNppOJD == true){JINqNppOJD = false;}
      if(TIpcwxMTdd == true){TIpcwxMTdd = false;}
      if(mLOzQZLOWz == true){mLOzQZLOWz = false;}
      if(rOjFGduaSo == true){rOjFGduaSo = false;}
      if(zxMQpXyFba == true){zxMQpXyFba = false;}
      if(JmUQdytOZm == true){JmUQdytOZm = false;}
      if(ebrJLEYjVR == true){ebrJLEYjVR = false;}
      if(CkBodoyyIs == true){CkBodoyyIs = false;}
      if(bFmuoEtTbI == true){bFmuoEtTbI = false;}
      if(jgBeKXFCFl == true){jgBeKXFCFl = false;}
      if(zOiJYYlfln == true){zOiJYYlfln = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWKUGFHAGT
{ 
  void tUUaYuxdFR()
  { 
      bool sofDnqxHEP = false;
      bool FPTFJdKcMD = false;
      bool BVDSqKWwQm = false;
      bool SaVZaSjxCA = false;
      bool TnZJhCBTwX = false;
      bool zVlGIWkNLd = false;
      bool TBqRxdstdq = false;
      bool tMZMiMwtjn = false;
      bool JDArmwnPQE = false;
      bool gVkYfRxIMD = false;
      bool JGpEdluZWw = false;
      bool aqdXTPBydA = false;
      bool odcYJYbBfQ = false;
      bool OngfeDNuNB = false;
      bool BOrUdoqNEP = false;
      bool QzdLNfcQuF = false;
      bool KstFgmJyrQ = false;
      bool CGkczalHuT = false;
      bool gOwPAPJVRz = false;
      bool ZwzIqHTlnq = false;
      string oQfFwDwiUb;
      string uoWWBomdhY;
      string OKgWACePoK;
      string QNbuFKKTex;
      string NUzfzVhLdW;
      string QWPreeiIFs;
      string XfsJLhMaRp;
      string dSykKsLBXd;
      string USlRtsxjQa;
      string bCOkYgboUR;
      string JGtnsxXegl;
      string ThjaXEtaOR;
      string jcKpNaDNLd;
      string RVgGUOYyYw;
      string USCdHsSmMU;
      string mAZCgfwDZS;
      string tKTDUxAcGJ;
      string fwCSxRZfiU;
      string IPAqqQweZn;
      string SUYGCJyzJJ;
      if(oQfFwDwiUb == JGtnsxXegl){sofDnqxHEP = true;}
      else if(JGtnsxXegl == oQfFwDwiUb){JGpEdluZWw = true;}
      if(uoWWBomdhY == ThjaXEtaOR){FPTFJdKcMD = true;}
      else if(ThjaXEtaOR == uoWWBomdhY){aqdXTPBydA = true;}
      if(OKgWACePoK == jcKpNaDNLd){BVDSqKWwQm = true;}
      else if(jcKpNaDNLd == OKgWACePoK){odcYJYbBfQ = true;}
      if(QNbuFKKTex == RVgGUOYyYw){SaVZaSjxCA = true;}
      else if(RVgGUOYyYw == QNbuFKKTex){OngfeDNuNB = true;}
      if(NUzfzVhLdW == USCdHsSmMU){TnZJhCBTwX = true;}
      else if(USCdHsSmMU == NUzfzVhLdW){BOrUdoqNEP = true;}
      if(QWPreeiIFs == mAZCgfwDZS){zVlGIWkNLd = true;}
      else if(mAZCgfwDZS == QWPreeiIFs){QzdLNfcQuF = true;}
      if(XfsJLhMaRp == tKTDUxAcGJ){TBqRxdstdq = true;}
      else if(tKTDUxAcGJ == XfsJLhMaRp){KstFgmJyrQ = true;}
      if(dSykKsLBXd == fwCSxRZfiU){tMZMiMwtjn = true;}
      if(USlRtsxjQa == IPAqqQweZn){JDArmwnPQE = true;}
      if(bCOkYgboUR == SUYGCJyzJJ){gVkYfRxIMD = true;}
      while(fwCSxRZfiU == dSykKsLBXd){CGkczalHuT = true;}
      while(IPAqqQweZn == IPAqqQweZn){gOwPAPJVRz = true;}
      while(SUYGCJyzJJ == SUYGCJyzJJ){ZwzIqHTlnq = true;}
      if(sofDnqxHEP == true){sofDnqxHEP = false;}
      if(FPTFJdKcMD == true){FPTFJdKcMD = false;}
      if(BVDSqKWwQm == true){BVDSqKWwQm = false;}
      if(SaVZaSjxCA == true){SaVZaSjxCA = false;}
      if(TnZJhCBTwX == true){TnZJhCBTwX = false;}
      if(zVlGIWkNLd == true){zVlGIWkNLd = false;}
      if(TBqRxdstdq == true){TBqRxdstdq = false;}
      if(tMZMiMwtjn == true){tMZMiMwtjn = false;}
      if(JDArmwnPQE == true){JDArmwnPQE = false;}
      if(gVkYfRxIMD == true){gVkYfRxIMD = false;}
      if(JGpEdluZWw == true){JGpEdluZWw = false;}
      if(aqdXTPBydA == true){aqdXTPBydA = false;}
      if(odcYJYbBfQ == true){odcYJYbBfQ = false;}
      if(OngfeDNuNB == true){OngfeDNuNB = false;}
      if(BOrUdoqNEP == true){BOrUdoqNEP = false;}
      if(QzdLNfcQuF == true){QzdLNfcQuF = false;}
      if(KstFgmJyrQ == true){KstFgmJyrQ = false;}
      if(CGkczalHuT == true){CGkczalHuT = false;}
      if(gOwPAPJVRz == true){gOwPAPJVRz = false;}
      if(ZwzIqHTlnq == true){ZwzIqHTlnq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKZVWNXRQR
{ 
  void MPqutbGZJk()
  { 
      bool KsKjbCGpcd = false;
      bool aCckuwhXFE = false;
      bool rHlPFXHSTZ = false;
      bool KhMjGPPikg = false;
      bool zOKczokbLK = false;
      bool XoBZGCGudE = false;
      bool tmWCTsoref = false;
      bool gzmYFcxJPQ = false;
      bool lfHICVfmdD = false;
      bool IUFglLrHJF = false;
      bool zrwedXCbTd = false;
      bool ExeMROfNAy = false;
      bool MCObXMtFmt = false;
      bool kpzJRsibed = false;
      bool SESAyKorPX = false;
      bool edGLrwdUHR = false;
      bool dwoYrOxUtX = false;
      bool eDiWeIiOcM = false;
      bool WBpOPHjnRU = false;
      bool PNTMzVOtHj = false;
      string MbeBshJkPR;
      string EeHbGKVRxy;
      string PxorZCFiqi;
      string VVCnfkaLEz;
      string iLDtJernth;
      string HNJKBOmlbq;
      string bZtgwicSwU;
      string iJMxPEttit;
      string JRoJbHLqlQ;
      string yoiNXIRWxZ;
      string CZqYyxALux;
      string UrChgKkjFn;
      string XkffWtazZG;
      string lWxJqjZPKd;
      string HzwowFlAgM;
      string XgRJCQsLCD;
      string WBlnKxuspx;
      string kVZafXoqiQ;
      string IZSNiFFmGa;
      string qNNGHGNHdy;
      if(MbeBshJkPR == CZqYyxALux){KsKjbCGpcd = true;}
      else if(CZqYyxALux == MbeBshJkPR){zrwedXCbTd = true;}
      if(EeHbGKVRxy == UrChgKkjFn){aCckuwhXFE = true;}
      else if(UrChgKkjFn == EeHbGKVRxy){ExeMROfNAy = true;}
      if(PxorZCFiqi == XkffWtazZG){rHlPFXHSTZ = true;}
      else if(XkffWtazZG == PxorZCFiqi){MCObXMtFmt = true;}
      if(VVCnfkaLEz == lWxJqjZPKd){KhMjGPPikg = true;}
      else if(lWxJqjZPKd == VVCnfkaLEz){kpzJRsibed = true;}
      if(iLDtJernth == HzwowFlAgM){zOKczokbLK = true;}
      else if(HzwowFlAgM == iLDtJernth){SESAyKorPX = true;}
      if(HNJKBOmlbq == XgRJCQsLCD){XoBZGCGudE = true;}
      else if(XgRJCQsLCD == HNJKBOmlbq){edGLrwdUHR = true;}
      if(bZtgwicSwU == WBlnKxuspx){tmWCTsoref = true;}
      else if(WBlnKxuspx == bZtgwicSwU){dwoYrOxUtX = true;}
      if(iJMxPEttit == kVZafXoqiQ){gzmYFcxJPQ = true;}
      if(JRoJbHLqlQ == IZSNiFFmGa){lfHICVfmdD = true;}
      if(yoiNXIRWxZ == qNNGHGNHdy){IUFglLrHJF = true;}
      while(kVZafXoqiQ == iJMxPEttit){eDiWeIiOcM = true;}
      while(IZSNiFFmGa == IZSNiFFmGa){WBpOPHjnRU = true;}
      while(qNNGHGNHdy == qNNGHGNHdy){PNTMzVOtHj = true;}
      if(KsKjbCGpcd == true){KsKjbCGpcd = false;}
      if(aCckuwhXFE == true){aCckuwhXFE = false;}
      if(rHlPFXHSTZ == true){rHlPFXHSTZ = false;}
      if(KhMjGPPikg == true){KhMjGPPikg = false;}
      if(zOKczokbLK == true){zOKczokbLK = false;}
      if(XoBZGCGudE == true){XoBZGCGudE = false;}
      if(tmWCTsoref == true){tmWCTsoref = false;}
      if(gzmYFcxJPQ == true){gzmYFcxJPQ = false;}
      if(lfHICVfmdD == true){lfHICVfmdD = false;}
      if(IUFglLrHJF == true){IUFglLrHJF = false;}
      if(zrwedXCbTd == true){zrwedXCbTd = false;}
      if(ExeMROfNAy == true){ExeMROfNAy = false;}
      if(MCObXMtFmt == true){MCObXMtFmt = false;}
      if(kpzJRsibed == true){kpzJRsibed = false;}
      if(SESAyKorPX == true){SESAyKorPX = false;}
      if(edGLrwdUHR == true){edGLrwdUHR = false;}
      if(dwoYrOxUtX == true){dwoYrOxUtX = false;}
      if(eDiWeIiOcM == true){eDiWeIiOcM = false;}
      if(WBpOPHjnRU == true){WBpOPHjnRU = false;}
      if(PNTMzVOtHj == true){PNTMzVOtHj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGQSERQGAY
{ 
  void eoAGrVxIkX()
  { 
      bool uDIESrpQZy = false;
      bool AEgKKGJipW = false;
      bool tTbkcKDrAu = false;
      bool hmuWqQjMFQ = false;
      bool HIeFGkKFZN = false;
      bool pwohkbbWaH = false;
      bool nyQePMIJTt = false;
      bool WxdYOlnWdq = false;
      bool AyRmEkxMkO = false;
      bool oNkybJqAps = false;
      bool cAkfprSPTy = false;
      bool nFrjGpfdZd = false;
      bool PuYFEJMfwF = false;
      bool tnfkOANlwL = false;
      bool ShsmajUBql = false;
      bool cNZLdgbeag = false;
      bool fmSNEzYHUG = false;
      bool csgNLhBldU = false;
      bool nKoKcgNUGg = false;
      bool YhLOffOfha = false;
      string iqJDidwTVo;
      string UZNiPtjAhG;
      string kPWhyslxYS;
      string deebznHXap;
      string rHdDDJSXeW;
      string FnqgPSTaFo;
      string rzuCLotlja;
      string lLZqNdlTdn;
      string aORBNonyLg;
      string UgRkysMarN;
      string OfmEksOATl;
      string fAwROdgsoV;
      string BwaDGFsnrU;
      string QLaQYuaNQT;
      string amdZAUjAWU;
      string LSlVMRFjxf;
      string zaHzUUYfrS;
      string CTcUuORACl;
      string UsQXIyZFDG;
      string pqPjTAfeFf;
      if(iqJDidwTVo == OfmEksOATl){uDIESrpQZy = true;}
      else if(OfmEksOATl == iqJDidwTVo){cAkfprSPTy = true;}
      if(UZNiPtjAhG == fAwROdgsoV){AEgKKGJipW = true;}
      else if(fAwROdgsoV == UZNiPtjAhG){nFrjGpfdZd = true;}
      if(kPWhyslxYS == BwaDGFsnrU){tTbkcKDrAu = true;}
      else if(BwaDGFsnrU == kPWhyslxYS){PuYFEJMfwF = true;}
      if(deebznHXap == QLaQYuaNQT){hmuWqQjMFQ = true;}
      else if(QLaQYuaNQT == deebznHXap){tnfkOANlwL = true;}
      if(rHdDDJSXeW == amdZAUjAWU){HIeFGkKFZN = true;}
      else if(amdZAUjAWU == rHdDDJSXeW){ShsmajUBql = true;}
      if(FnqgPSTaFo == LSlVMRFjxf){pwohkbbWaH = true;}
      else if(LSlVMRFjxf == FnqgPSTaFo){cNZLdgbeag = true;}
      if(rzuCLotlja == zaHzUUYfrS){nyQePMIJTt = true;}
      else if(zaHzUUYfrS == rzuCLotlja){fmSNEzYHUG = true;}
      if(lLZqNdlTdn == CTcUuORACl){WxdYOlnWdq = true;}
      if(aORBNonyLg == UsQXIyZFDG){AyRmEkxMkO = true;}
      if(UgRkysMarN == pqPjTAfeFf){oNkybJqAps = true;}
      while(CTcUuORACl == lLZqNdlTdn){csgNLhBldU = true;}
      while(UsQXIyZFDG == UsQXIyZFDG){nKoKcgNUGg = true;}
      while(pqPjTAfeFf == pqPjTAfeFf){YhLOffOfha = true;}
      if(uDIESrpQZy == true){uDIESrpQZy = false;}
      if(AEgKKGJipW == true){AEgKKGJipW = false;}
      if(tTbkcKDrAu == true){tTbkcKDrAu = false;}
      if(hmuWqQjMFQ == true){hmuWqQjMFQ = false;}
      if(HIeFGkKFZN == true){HIeFGkKFZN = false;}
      if(pwohkbbWaH == true){pwohkbbWaH = false;}
      if(nyQePMIJTt == true){nyQePMIJTt = false;}
      if(WxdYOlnWdq == true){WxdYOlnWdq = false;}
      if(AyRmEkxMkO == true){AyRmEkxMkO = false;}
      if(oNkybJqAps == true){oNkybJqAps = false;}
      if(cAkfprSPTy == true){cAkfprSPTy = false;}
      if(nFrjGpfdZd == true){nFrjGpfdZd = false;}
      if(PuYFEJMfwF == true){PuYFEJMfwF = false;}
      if(tnfkOANlwL == true){tnfkOANlwL = false;}
      if(ShsmajUBql == true){ShsmajUBql = false;}
      if(cNZLdgbeag == true){cNZLdgbeag = false;}
      if(fmSNEzYHUG == true){fmSNEzYHUG = false;}
      if(csgNLhBldU == true){csgNLhBldU = false;}
      if(nKoKcgNUGg == true){nKoKcgNUGg = false;}
      if(YhLOffOfha == true){YhLOffOfha = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XESYYJVYTE
{ 
  void TJxgpzyJCQ()
  { 
      bool jUnOyFTktT = false;
      bool HAhhpqyERR = false;
      bool qNNoUjlaVp = false;
      bool gewpVBlPkE = false;
      bool SPAdfcztjk = false;
      bool lLLWcVGzsN = false;
      bool SrPElbDrMo = false;
      bool FhSMybNjIq = false;
      bool krpjDVTZNz = false;
      bool ulVXlazwqD = false;
      bool ZGgufDsyXB = false;
      bool IVqBbZBfAQ = false;
      bool IdeNsSMuaW = false;
      bool bQrERdKuDA = false;
      bool bUBMpYuUuL = false;
      bool YTwauwbTBN = false;
      bool qyXBYrdljx = false;
      bool PFbzombSWT = false;
      bool WqAOyIURIV = false;
      bool CqtpIdxAmy = false;
      string UxQHMzpZxj;
      string pZSofjJgAP;
      string XgACoXQGfC;
      string QszkdOXRPq;
      string jEUbRFuaDc;
      string AkzlfnxNRo;
      string histSwahLQ;
      string MqRJeTLYkj;
      string boDDCftMEo;
      string RJzZIALaIU;
      string eNPmPIToHM;
      string cYchMrfpqm;
      string CNcWyCqqAe;
      string IjPPEOZQns;
      string MEFrMrgRNQ;
      string UViURQkrnM;
      string QbnbErIMcy;
      string ROBxayIjKF;
      string VZdjKmBuyn;
      string dgcabjQcnT;
      if(UxQHMzpZxj == eNPmPIToHM){jUnOyFTktT = true;}
      else if(eNPmPIToHM == UxQHMzpZxj){ZGgufDsyXB = true;}
      if(pZSofjJgAP == cYchMrfpqm){HAhhpqyERR = true;}
      else if(cYchMrfpqm == pZSofjJgAP){IVqBbZBfAQ = true;}
      if(XgACoXQGfC == CNcWyCqqAe){qNNoUjlaVp = true;}
      else if(CNcWyCqqAe == XgACoXQGfC){IdeNsSMuaW = true;}
      if(QszkdOXRPq == IjPPEOZQns){gewpVBlPkE = true;}
      else if(IjPPEOZQns == QszkdOXRPq){bQrERdKuDA = true;}
      if(jEUbRFuaDc == MEFrMrgRNQ){SPAdfcztjk = true;}
      else if(MEFrMrgRNQ == jEUbRFuaDc){bUBMpYuUuL = true;}
      if(AkzlfnxNRo == UViURQkrnM){lLLWcVGzsN = true;}
      else if(UViURQkrnM == AkzlfnxNRo){YTwauwbTBN = true;}
      if(histSwahLQ == QbnbErIMcy){SrPElbDrMo = true;}
      else if(QbnbErIMcy == histSwahLQ){qyXBYrdljx = true;}
      if(MqRJeTLYkj == ROBxayIjKF){FhSMybNjIq = true;}
      if(boDDCftMEo == VZdjKmBuyn){krpjDVTZNz = true;}
      if(RJzZIALaIU == dgcabjQcnT){ulVXlazwqD = true;}
      while(ROBxayIjKF == MqRJeTLYkj){PFbzombSWT = true;}
      while(VZdjKmBuyn == VZdjKmBuyn){WqAOyIURIV = true;}
      while(dgcabjQcnT == dgcabjQcnT){CqtpIdxAmy = true;}
      if(jUnOyFTktT == true){jUnOyFTktT = false;}
      if(HAhhpqyERR == true){HAhhpqyERR = false;}
      if(qNNoUjlaVp == true){qNNoUjlaVp = false;}
      if(gewpVBlPkE == true){gewpVBlPkE = false;}
      if(SPAdfcztjk == true){SPAdfcztjk = false;}
      if(lLLWcVGzsN == true){lLLWcVGzsN = false;}
      if(SrPElbDrMo == true){SrPElbDrMo = false;}
      if(FhSMybNjIq == true){FhSMybNjIq = false;}
      if(krpjDVTZNz == true){krpjDVTZNz = false;}
      if(ulVXlazwqD == true){ulVXlazwqD = false;}
      if(ZGgufDsyXB == true){ZGgufDsyXB = false;}
      if(IVqBbZBfAQ == true){IVqBbZBfAQ = false;}
      if(IdeNsSMuaW == true){IdeNsSMuaW = false;}
      if(bQrERdKuDA == true){bQrERdKuDA = false;}
      if(bUBMpYuUuL == true){bUBMpYuUuL = false;}
      if(YTwauwbTBN == true){YTwauwbTBN = false;}
      if(qyXBYrdljx == true){qyXBYrdljx = false;}
      if(PFbzombSWT == true){PFbzombSWT = false;}
      if(WqAOyIURIV == true){WqAOyIURIV = false;}
      if(CqtpIdxAmy == true){CqtpIdxAmy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGBPBSNUGJ
{ 
  void raVKnLMzrW()
  { 
      bool VDByggjdMf = false;
      bool sIXDgFNbEh = false;
      bool PljfTLCpIx = false;
      bool ueFSKUlryT = false;
      bool IAMhFCLhGo = false;
      bool yhrkXiSUeV = false;
      bool dtUOjOCEsL = false;
      bool TVdjZOZBaQ = false;
      bool AUjTzNlTua = false;
      bool BQNcpOfxyq = false;
      bool zHntVbEHLJ = false;
      bool JRsNUJJBPW = false;
      bool bhIRJCIAtL = false;
      bool icDiQrfoyW = false;
      bool IeIlRjWzHf = false;
      bool EegbPRyWkS = false;
      bool TENzagOKwc = false;
      bool cTDsOxZWAZ = false;
      bool eIrNHDubTz = false;
      bool tJEeCDQILj = false;
      string zqCsUUxeFt;
      string PTALgrztaO;
      string YFwoaycSiM;
      string gCKDhgPzXd;
      string LgSHaHBwyJ;
      string MsPfZttNSV;
      string qewrMNIxcz;
      string cAVxCrmoNS;
      string xgUZAnlecn;
      string lBfCmfkZtN;
      string yDSygMXSch;
      string GFzzYJKWrY;
      string adUnNaTTJW;
      string GMtATsNVrn;
      string PTCuhgCgcc;
      string VNhVlUhdjF;
      string rEIFatKyfe;
      string undEJGaZGg;
      string YmpfBreYOz;
      string LjkmuLKwTm;
      if(zqCsUUxeFt == yDSygMXSch){VDByggjdMf = true;}
      else if(yDSygMXSch == zqCsUUxeFt){zHntVbEHLJ = true;}
      if(PTALgrztaO == GFzzYJKWrY){sIXDgFNbEh = true;}
      else if(GFzzYJKWrY == PTALgrztaO){JRsNUJJBPW = true;}
      if(YFwoaycSiM == adUnNaTTJW){PljfTLCpIx = true;}
      else if(adUnNaTTJW == YFwoaycSiM){bhIRJCIAtL = true;}
      if(gCKDhgPzXd == GMtATsNVrn){ueFSKUlryT = true;}
      else if(GMtATsNVrn == gCKDhgPzXd){icDiQrfoyW = true;}
      if(LgSHaHBwyJ == PTCuhgCgcc){IAMhFCLhGo = true;}
      else if(PTCuhgCgcc == LgSHaHBwyJ){IeIlRjWzHf = true;}
      if(MsPfZttNSV == VNhVlUhdjF){yhrkXiSUeV = true;}
      else if(VNhVlUhdjF == MsPfZttNSV){EegbPRyWkS = true;}
      if(qewrMNIxcz == rEIFatKyfe){dtUOjOCEsL = true;}
      else if(rEIFatKyfe == qewrMNIxcz){TENzagOKwc = true;}
      if(cAVxCrmoNS == undEJGaZGg){TVdjZOZBaQ = true;}
      if(xgUZAnlecn == YmpfBreYOz){AUjTzNlTua = true;}
      if(lBfCmfkZtN == LjkmuLKwTm){BQNcpOfxyq = true;}
      while(undEJGaZGg == cAVxCrmoNS){cTDsOxZWAZ = true;}
      while(YmpfBreYOz == YmpfBreYOz){eIrNHDubTz = true;}
      while(LjkmuLKwTm == LjkmuLKwTm){tJEeCDQILj = true;}
      if(VDByggjdMf == true){VDByggjdMf = false;}
      if(sIXDgFNbEh == true){sIXDgFNbEh = false;}
      if(PljfTLCpIx == true){PljfTLCpIx = false;}
      if(ueFSKUlryT == true){ueFSKUlryT = false;}
      if(IAMhFCLhGo == true){IAMhFCLhGo = false;}
      if(yhrkXiSUeV == true){yhrkXiSUeV = false;}
      if(dtUOjOCEsL == true){dtUOjOCEsL = false;}
      if(TVdjZOZBaQ == true){TVdjZOZBaQ = false;}
      if(AUjTzNlTua == true){AUjTzNlTua = false;}
      if(BQNcpOfxyq == true){BQNcpOfxyq = false;}
      if(zHntVbEHLJ == true){zHntVbEHLJ = false;}
      if(JRsNUJJBPW == true){JRsNUJJBPW = false;}
      if(bhIRJCIAtL == true){bhIRJCIAtL = false;}
      if(icDiQrfoyW == true){icDiQrfoyW = false;}
      if(IeIlRjWzHf == true){IeIlRjWzHf = false;}
      if(EegbPRyWkS == true){EegbPRyWkS = false;}
      if(TENzagOKwc == true){TENzagOKwc = false;}
      if(cTDsOxZWAZ == true){cTDsOxZWAZ = false;}
      if(eIrNHDubTz == true){eIrNHDubTz = false;}
      if(tJEeCDQILj == true){tJEeCDQILj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJCAXRUIGD
{ 
  void PfQBqgJFVj()
  { 
      bool hSgsAuraoY = false;
      bool SxBefXiYSY = false;
      bool VXJoHPMBBq = false;
      bool xwyUiIrurH = false;
      bool ynolKNqLEp = false;
      bool LqxSCKIqkj = false;
      bool hpYxaWyfwX = false;
      bool engLZhhXes = false;
      bool YAwLfFzeRY = false;
      bool zAJHYHOqKn = false;
      bool OKPgKXKlrT = false;
      bool bkMrKgsMRV = false;
      bool WSNXXddYlR = false;
      bool SpNpdOkOAH = false;
      bool tNmxwOnRwq = false;
      bool NBZnQwwrJg = false;
      bool slzZBkXVNw = false;
      bool wdMJaJfPaI = false;
      bool pMbtEQQYYh = false;
      bool RsFTNINMwL = false;
      string KUGGDYmMSw;
      string UarQeXIJss;
      string rxXJiDpSMJ;
      string wXRGNnCCdn;
      string GKZhepUClt;
      string bEXIQNxxWA;
      string iUzIzwJlDq;
      string VFeFlgWoer;
      string hmfShrAIpA;
      string qFedElLRih;
      string gizuYWYRVj;
      string pHReRwngaG;
      string wAwDzPZAAA;
      string UFGwKynktK;
      string ThlGJinAMI;
      string xepblgmuuI;
      string wXQVOkBUTS;
      string ICmPmNNptQ;
      string bYnrCpOdKd;
      string LrpkNuQQqY;
      if(KUGGDYmMSw == gizuYWYRVj){hSgsAuraoY = true;}
      else if(gizuYWYRVj == KUGGDYmMSw){OKPgKXKlrT = true;}
      if(UarQeXIJss == pHReRwngaG){SxBefXiYSY = true;}
      else if(pHReRwngaG == UarQeXIJss){bkMrKgsMRV = true;}
      if(rxXJiDpSMJ == wAwDzPZAAA){VXJoHPMBBq = true;}
      else if(wAwDzPZAAA == rxXJiDpSMJ){WSNXXddYlR = true;}
      if(wXRGNnCCdn == UFGwKynktK){xwyUiIrurH = true;}
      else if(UFGwKynktK == wXRGNnCCdn){SpNpdOkOAH = true;}
      if(GKZhepUClt == ThlGJinAMI){ynolKNqLEp = true;}
      else if(ThlGJinAMI == GKZhepUClt){tNmxwOnRwq = true;}
      if(bEXIQNxxWA == xepblgmuuI){LqxSCKIqkj = true;}
      else if(xepblgmuuI == bEXIQNxxWA){NBZnQwwrJg = true;}
      if(iUzIzwJlDq == wXQVOkBUTS){hpYxaWyfwX = true;}
      else if(wXQVOkBUTS == iUzIzwJlDq){slzZBkXVNw = true;}
      if(VFeFlgWoer == ICmPmNNptQ){engLZhhXes = true;}
      if(hmfShrAIpA == bYnrCpOdKd){YAwLfFzeRY = true;}
      if(qFedElLRih == LrpkNuQQqY){zAJHYHOqKn = true;}
      while(ICmPmNNptQ == VFeFlgWoer){wdMJaJfPaI = true;}
      while(bYnrCpOdKd == bYnrCpOdKd){pMbtEQQYYh = true;}
      while(LrpkNuQQqY == LrpkNuQQqY){RsFTNINMwL = true;}
      if(hSgsAuraoY == true){hSgsAuraoY = false;}
      if(SxBefXiYSY == true){SxBefXiYSY = false;}
      if(VXJoHPMBBq == true){VXJoHPMBBq = false;}
      if(xwyUiIrurH == true){xwyUiIrurH = false;}
      if(ynolKNqLEp == true){ynolKNqLEp = false;}
      if(LqxSCKIqkj == true){LqxSCKIqkj = false;}
      if(hpYxaWyfwX == true){hpYxaWyfwX = false;}
      if(engLZhhXes == true){engLZhhXes = false;}
      if(YAwLfFzeRY == true){YAwLfFzeRY = false;}
      if(zAJHYHOqKn == true){zAJHYHOqKn = false;}
      if(OKPgKXKlrT == true){OKPgKXKlrT = false;}
      if(bkMrKgsMRV == true){bkMrKgsMRV = false;}
      if(WSNXXddYlR == true){WSNXXddYlR = false;}
      if(SpNpdOkOAH == true){SpNpdOkOAH = false;}
      if(tNmxwOnRwq == true){tNmxwOnRwq = false;}
      if(NBZnQwwrJg == true){NBZnQwwrJg = false;}
      if(slzZBkXVNw == true){slzZBkXVNw = false;}
      if(wdMJaJfPaI == true){wdMJaJfPaI = false;}
      if(pMbtEQQYYh == true){pMbtEQQYYh = false;}
      if(RsFTNINMwL == true){RsFTNINMwL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APKMZGLPRE
{ 
  void jiZJxiCRjB()
  { 
      bool yQtmeSnyrD = false;
      bool NdZDCbozHw = false;
      bool xxpMeDgZkd = false;
      bool xSNnkYcGmW = false;
      bool LBiTIEVGDl = false;
      bool VrZljAZhIa = false;
      bool kNMOGuPlRd = false;
      bool yhLjjuNWEa = false;
      bool hZWyIErbDk = false;
      bool yuyMkxnUMM = false;
      bool njoZmmgpBn = false;
      bool lDcgrLqNFB = false;
      bool CnhgeDjzyl = false;
      bool GsJqlykxLU = false;
      bool XCZOyuRQTZ = false;
      bool GZOLKzBHti = false;
      bool DgqPhstltt = false;
      bool ZtCkcAOShj = false;
      bool lTeYffdygm = false;
      bool wcCbRqLJgF = false;
      string AIAKNHojlX;
      string YYJMhQhSdj;
      string LuyQTiVEtK;
      string REVkgRplBJ;
      string jolWKtYdKk;
      string wthunFKjqe;
      string kjoaGTDXeP;
      string ZwQUzVIaGZ;
      string JrsJNWWZxb;
      string HGtWXAAKQp;
      string qBzuKAcNuR;
      string wjcRVspeMi;
      string xdaCHSBtwz;
      string VyJPiIsyyN;
      string tIdefXdcAe;
      string KUxhrMZwmr;
      string ziQwwyZNhN;
      string ArgzoozwWj;
      string oXsRoAAbWV;
      string hwKGNKqghh;
      if(AIAKNHojlX == qBzuKAcNuR){yQtmeSnyrD = true;}
      else if(qBzuKAcNuR == AIAKNHojlX){njoZmmgpBn = true;}
      if(YYJMhQhSdj == wjcRVspeMi){NdZDCbozHw = true;}
      else if(wjcRVspeMi == YYJMhQhSdj){lDcgrLqNFB = true;}
      if(LuyQTiVEtK == xdaCHSBtwz){xxpMeDgZkd = true;}
      else if(xdaCHSBtwz == LuyQTiVEtK){CnhgeDjzyl = true;}
      if(REVkgRplBJ == VyJPiIsyyN){xSNnkYcGmW = true;}
      else if(VyJPiIsyyN == REVkgRplBJ){GsJqlykxLU = true;}
      if(jolWKtYdKk == tIdefXdcAe){LBiTIEVGDl = true;}
      else if(tIdefXdcAe == jolWKtYdKk){XCZOyuRQTZ = true;}
      if(wthunFKjqe == KUxhrMZwmr){VrZljAZhIa = true;}
      else if(KUxhrMZwmr == wthunFKjqe){GZOLKzBHti = true;}
      if(kjoaGTDXeP == ziQwwyZNhN){kNMOGuPlRd = true;}
      else if(ziQwwyZNhN == kjoaGTDXeP){DgqPhstltt = true;}
      if(ZwQUzVIaGZ == ArgzoozwWj){yhLjjuNWEa = true;}
      if(JrsJNWWZxb == oXsRoAAbWV){hZWyIErbDk = true;}
      if(HGtWXAAKQp == hwKGNKqghh){yuyMkxnUMM = true;}
      while(ArgzoozwWj == ZwQUzVIaGZ){ZtCkcAOShj = true;}
      while(oXsRoAAbWV == oXsRoAAbWV){lTeYffdygm = true;}
      while(hwKGNKqghh == hwKGNKqghh){wcCbRqLJgF = true;}
      if(yQtmeSnyrD == true){yQtmeSnyrD = false;}
      if(NdZDCbozHw == true){NdZDCbozHw = false;}
      if(xxpMeDgZkd == true){xxpMeDgZkd = false;}
      if(xSNnkYcGmW == true){xSNnkYcGmW = false;}
      if(LBiTIEVGDl == true){LBiTIEVGDl = false;}
      if(VrZljAZhIa == true){VrZljAZhIa = false;}
      if(kNMOGuPlRd == true){kNMOGuPlRd = false;}
      if(yhLjjuNWEa == true){yhLjjuNWEa = false;}
      if(hZWyIErbDk == true){hZWyIErbDk = false;}
      if(yuyMkxnUMM == true){yuyMkxnUMM = false;}
      if(njoZmmgpBn == true){njoZmmgpBn = false;}
      if(lDcgrLqNFB == true){lDcgrLqNFB = false;}
      if(CnhgeDjzyl == true){CnhgeDjzyl = false;}
      if(GsJqlykxLU == true){GsJqlykxLU = false;}
      if(XCZOyuRQTZ == true){XCZOyuRQTZ = false;}
      if(GZOLKzBHti == true){GZOLKzBHti = false;}
      if(DgqPhstltt == true){DgqPhstltt = false;}
      if(ZtCkcAOShj == true){ZtCkcAOShj = false;}
      if(lTeYffdygm == true){lTeYffdygm = false;}
      if(wcCbRqLJgF == true){wcCbRqLJgF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZSODWQSAM
{ 
  void OAVeLLjyWx()
  { 
      bool FZAnVkyORq = false;
      bool tjyyeCbySf = false;
      bool woNEzEwReq = false;
      bool LKOSwYNYFw = false;
      bool EzrRgJfDfx = false;
      bool PnnayPMuoQ = false;
      bool ofjaejVeCG = false;
      bool nCsWaxwuXo = false;
      bool YrkgbXVnUf = false;
      bool LRjoHYPRlw = false;
      bool nABZIMuRzA = false;
      bool SRWzrwuCyH = false;
      bool NgJVtVSDOC = false;
      bool heIbAXqKXP = false;
      bool cEoTMttjxK = false;
      bool dMSehHpefm = false;
      bool tqCwSnIuzT = false;
      bool EjeieJrpJA = false;
      bool ahGDYULdss = false;
      bool gMekVlBrAY = false;
      string YdzPOoqoSV;
      string JuFcgEARho;
      string BKlcRAskGr;
      string igsplIoAqY;
      string ocOGdohWdp;
      string NNOSlNqVxN;
      string uGiZmcBPqX;
      string PzZJzYuezc;
      string SVHPeVRaDX;
      string RSCddhtnSA;
      string nRfFaNmFSN;
      string RLVUuYzSuR;
      string KaLTGwwwfR;
      string dHLznApBoQ;
      string hMIpFFxghE;
      string iasBoMGLzd;
      string QpZAiKzWgt;
      string ixcdiyRVNB;
      string zONahCNKJb;
      string tdBLzrlHGt;
      if(YdzPOoqoSV == nRfFaNmFSN){FZAnVkyORq = true;}
      else if(nRfFaNmFSN == YdzPOoqoSV){nABZIMuRzA = true;}
      if(JuFcgEARho == RLVUuYzSuR){tjyyeCbySf = true;}
      else if(RLVUuYzSuR == JuFcgEARho){SRWzrwuCyH = true;}
      if(BKlcRAskGr == KaLTGwwwfR){woNEzEwReq = true;}
      else if(KaLTGwwwfR == BKlcRAskGr){NgJVtVSDOC = true;}
      if(igsplIoAqY == dHLznApBoQ){LKOSwYNYFw = true;}
      else if(dHLznApBoQ == igsplIoAqY){heIbAXqKXP = true;}
      if(ocOGdohWdp == hMIpFFxghE){EzrRgJfDfx = true;}
      else if(hMIpFFxghE == ocOGdohWdp){cEoTMttjxK = true;}
      if(NNOSlNqVxN == iasBoMGLzd){PnnayPMuoQ = true;}
      else if(iasBoMGLzd == NNOSlNqVxN){dMSehHpefm = true;}
      if(uGiZmcBPqX == QpZAiKzWgt){ofjaejVeCG = true;}
      else if(QpZAiKzWgt == uGiZmcBPqX){tqCwSnIuzT = true;}
      if(PzZJzYuezc == ixcdiyRVNB){nCsWaxwuXo = true;}
      if(SVHPeVRaDX == zONahCNKJb){YrkgbXVnUf = true;}
      if(RSCddhtnSA == tdBLzrlHGt){LRjoHYPRlw = true;}
      while(ixcdiyRVNB == PzZJzYuezc){EjeieJrpJA = true;}
      while(zONahCNKJb == zONahCNKJb){ahGDYULdss = true;}
      while(tdBLzrlHGt == tdBLzrlHGt){gMekVlBrAY = true;}
      if(FZAnVkyORq == true){FZAnVkyORq = false;}
      if(tjyyeCbySf == true){tjyyeCbySf = false;}
      if(woNEzEwReq == true){woNEzEwReq = false;}
      if(LKOSwYNYFw == true){LKOSwYNYFw = false;}
      if(EzrRgJfDfx == true){EzrRgJfDfx = false;}
      if(PnnayPMuoQ == true){PnnayPMuoQ = false;}
      if(ofjaejVeCG == true){ofjaejVeCG = false;}
      if(nCsWaxwuXo == true){nCsWaxwuXo = false;}
      if(YrkgbXVnUf == true){YrkgbXVnUf = false;}
      if(LRjoHYPRlw == true){LRjoHYPRlw = false;}
      if(nABZIMuRzA == true){nABZIMuRzA = false;}
      if(SRWzrwuCyH == true){SRWzrwuCyH = false;}
      if(NgJVtVSDOC == true){NgJVtVSDOC = false;}
      if(heIbAXqKXP == true){heIbAXqKXP = false;}
      if(cEoTMttjxK == true){cEoTMttjxK = false;}
      if(dMSehHpefm == true){dMSehHpefm = false;}
      if(tqCwSnIuzT == true){tqCwSnIuzT = false;}
      if(EjeieJrpJA == true){EjeieJrpJA = false;}
      if(ahGDYULdss == true){ahGDYULdss = false;}
      if(gMekVlBrAY == true){gMekVlBrAY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XISWCSINWD
{ 
  void zXZZdlIBVO()
  { 
      bool lQlmwhFSfr = false;
      bool ldZzMkClju = false;
      bool UOnrZbzoiy = false;
      bool lqVNNNulNQ = false;
      bool ffNbRzBkdN = false;
      bool AmebFWcsMT = false;
      bool iQjgFtHMly = false;
      bool oQXSPnBMZa = false;
      bool aNLUxzLtIp = false;
      bool kBYthPwfVX = false;
      bool qoyfXiOLLR = false;
      bool VPTlsVFOjG = false;
      bool iMDwMnrdkA = false;
      bool rUpCikOexN = false;
      bool jzhpTUhmAL = false;
      bool KgwPodkCSj = false;
      bool qkaLZBZQCH = false;
      bool GZQVVieMbr = false;
      bool FFcYoKXaNF = false;
      bool zMMNWyYVQS = false;
      string SintMMxYkU;
      string IUxWctMSou;
      string XBICErdweh;
      string RxLpcEnSMf;
      string nwCRuIZpRB;
      string ewRJgRZkoU;
      string iAtCCLIGsX;
      string GtGJHaypGw;
      string SmedDVeCJL;
      string dCcqwnCzOj;
      string zSwsukpICF;
      string SiesBuUPzg;
      string gGwhtDROMS;
      string YzaWwzqkiR;
      string eVzDstXioB;
      string SmAhDrWOzq;
      string TbwjgSIHwC;
      string EjggCKGsnz;
      string ehYKzlysTD;
      string cbkqyDYPWZ;
      if(SintMMxYkU == zSwsukpICF){lQlmwhFSfr = true;}
      else if(zSwsukpICF == SintMMxYkU){qoyfXiOLLR = true;}
      if(IUxWctMSou == SiesBuUPzg){ldZzMkClju = true;}
      else if(SiesBuUPzg == IUxWctMSou){VPTlsVFOjG = true;}
      if(XBICErdweh == gGwhtDROMS){UOnrZbzoiy = true;}
      else if(gGwhtDROMS == XBICErdweh){iMDwMnrdkA = true;}
      if(RxLpcEnSMf == YzaWwzqkiR){lqVNNNulNQ = true;}
      else if(YzaWwzqkiR == RxLpcEnSMf){rUpCikOexN = true;}
      if(nwCRuIZpRB == eVzDstXioB){ffNbRzBkdN = true;}
      else if(eVzDstXioB == nwCRuIZpRB){jzhpTUhmAL = true;}
      if(ewRJgRZkoU == SmAhDrWOzq){AmebFWcsMT = true;}
      else if(SmAhDrWOzq == ewRJgRZkoU){KgwPodkCSj = true;}
      if(iAtCCLIGsX == TbwjgSIHwC){iQjgFtHMly = true;}
      else if(TbwjgSIHwC == iAtCCLIGsX){qkaLZBZQCH = true;}
      if(GtGJHaypGw == EjggCKGsnz){oQXSPnBMZa = true;}
      if(SmedDVeCJL == ehYKzlysTD){aNLUxzLtIp = true;}
      if(dCcqwnCzOj == cbkqyDYPWZ){kBYthPwfVX = true;}
      while(EjggCKGsnz == GtGJHaypGw){GZQVVieMbr = true;}
      while(ehYKzlysTD == ehYKzlysTD){FFcYoKXaNF = true;}
      while(cbkqyDYPWZ == cbkqyDYPWZ){zMMNWyYVQS = true;}
      if(lQlmwhFSfr == true){lQlmwhFSfr = false;}
      if(ldZzMkClju == true){ldZzMkClju = false;}
      if(UOnrZbzoiy == true){UOnrZbzoiy = false;}
      if(lqVNNNulNQ == true){lqVNNNulNQ = false;}
      if(ffNbRzBkdN == true){ffNbRzBkdN = false;}
      if(AmebFWcsMT == true){AmebFWcsMT = false;}
      if(iQjgFtHMly == true){iQjgFtHMly = false;}
      if(oQXSPnBMZa == true){oQXSPnBMZa = false;}
      if(aNLUxzLtIp == true){aNLUxzLtIp = false;}
      if(kBYthPwfVX == true){kBYthPwfVX = false;}
      if(qoyfXiOLLR == true){qoyfXiOLLR = false;}
      if(VPTlsVFOjG == true){VPTlsVFOjG = false;}
      if(iMDwMnrdkA == true){iMDwMnrdkA = false;}
      if(rUpCikOexN == true){rUpCikOexN = false;}
      if(jzhpTUhmAL == true){jzhpTUhmAL = false;}
      if(KgwPodkCSj == true){KgwPodkCSj = false;}
      if(qkaLZBZQCH == true){qkaLZBZQCH = false;}
      if(GZQVVieMbr == true){GZQVVieMbr = false;}
      if(FFcYoKXaNF == true){FFcYoKXaNF = false;}
      if(zMMNWyYVQS == true){zMMNWyYVQS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWHYFYILIA
{ 
  void UVagwioxOE()
  { 
      bool tezVUHglhr = false;
      bool fiJqffrFBX = false;
      bool iGMqBHPwCz = false;
      bool FPWbQIpLNz = false;
      bool SOgXEahiHj = false;
      bool xCnXqnSHTN = false;
      bool qjjilPMhZW = false;
      bool ogqBETYnmZ = false;
      bool YgoRBDbzkc = false;
      bool piqAIheyln = false;
      bool OAIjuQKlSW = false;
      bool OdUtnKuSgh = false;
      bool nNwxgGoqsV = false;
      bool oZCyLYXEWk = false;
      bool sofONLOxMy = false;
      bool mMREABDLDn = false;
      bool bSsxgnbViP = false;
      bool lpwunyghjV = false;
      bool qrduhcIyyJ = false;
      bool UMBhJZwigY = false;
      string bVjiDLFAoQ;
      string EKKkAphCiH;
      string qOwAVdahmH;
      string LFtSRzoofI;
      string mTtgOHetdQ;
      string gJRhLNYjNY;
      string jWMhFyQrTB;
      string AsVaUWTOlN;
      string zfEWaBmLGE;
      string ZFaHXPGMbP;
      string qlacPnmqNn;
      string sJxzYESpGD;
      string KEkOauROCE;
      string QHmVWMEbGm;
      string OwySLPHbhT;
      string xQFXFlBMBT;
      string VYnIXkVbbM;
      string zpiSoNFRCK;
      string npgiGABPPk;
      string KrZmQoHpuZ;
      if(bVjiDLFAoQ == qlacPnmqNn){tezVUHglhr = true;}
      else if(qlacPnmqNn == bVjiDLFAoQ){OAIjuQKlSW = true;}
      if(EKKkAphCiH == sJxzYESpGD){fiJqffrFBX = true;}
      else if(sJxzYESpGD == EKKkAphCiH){OdUtnKuSgh = true;}
      if(qOwAVdahmH == KEkOauROCE){iGMqBHPwCz = true;}
      else if(KEkOauROCE == qOwAVdahmH){nNwxgGoqsV = true;}
      if(LFtSRzoofI == QHmVWMEbGm){FPWbQIpLNz = true;}
      else if(QHmVWMEbGm == LFtSRzoofI){oZCyLYXEWk = true;}
      if(mTtgOHetdQ == OwySLPHbhT){SOgXEahiHj = true;}
      else if(OwySLPHbhT == mTtgOHetdQ){sofONLOxMy = true;}
      if(gJRhLNYjNY == xQFXFlBMBT){xCnXqnSHTN = true;}
      else if(xQFXFlBMBT == gJRhLNYjNY){mMREABDLDn = true;}
      if(jWMhFyQrTB == VYnIXkVbbM){qjjilPMhZW = true;}
      else if(VYnIXkVbbM == jWMhFyQrTB){bSsxgnbViP = true;}
      if(AsVaUWTOlN == zpiSoNFRCK){ogqBETYnmZ = true;}
      if(zfEWaBmLGE == npgiGABPPk){YgoRBDbzkc = true;}
      if(ZFaHXPGMbP == KrZmQoHpuZ){piqAIheyln = true;}
      while(zpiSoNFRCK == AsVaUWTOlN){lpwunyghjV = true;}
      while(npgiGABPPk == npgiGABPPk){qrduhcIyyJ = true;}
      while(KrZmQoHpuZ == KrZmQoHpuZ){UMBhJZwigY = true;}
      if(tezVUHglhr == true){tezVUHglhr = false;}
      if(fiJqffrFBX == true){fiJqffrFBX = false;}
      if(iGMqBHPwCz == true){iGMqBHPwCz = false;}
      if(FPWbQIpLNz == true){FPWbQIpLNz = false;}
      if(SOgXEahiHj == true){SOgXEahiHj = false;}
      if(xCnXqnSHTN == true){xCnXqnSHTN = false;}
      if(qjjilPMhZW == true){qjjilPMhZW = false;}
      if(ogqBETYnmZ == true){ogqBETYnmZ = false;}
      if(YgoRBDbzkc == true){YgoRBDbzkc = false;}
      if(piqAIheyln == true){piqAIheyln = false;}
      if(OAIjuQKlSW == true){OAIjuQKlSW = false;}
      if(OdUtnKuSgh == true){OdUtnKuSgh = false;}
      if(nNwxgGoqsV == true){nNwxgGoqsV = false;}
      if(oZCyLYXEWk == true){oZCyLYXEWk = false;}
      if(sofONLOxMy == true){sofONLOxMy = false;}
      if(mMREABDLDn == true){mMREABDLDn = false;}
      if(bSsxgnbViP == true){bSsxgnbViP = false;}
      if(lpwunyghjV == true){lpwunyghjV = false;}
      if(qrduhcIyyJ == true){qrduhcIyyJ = false;}
      if(UMBhJZwigY == true){UMBhJZwigY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QQFFSEIJKS
{ 
  void mRUVlBRaBe()
  { 
      bool VzFhMCJqhc = false;
      bool VeyOaxQisP = false;
      bool DMmOKXKiMO = false;
      bool XpmZOtgVgd = false;
      bool HCWyZclYnN = false;
      bool jwVJtIMpXo = false;
      bool radSEeqXAf = false;
      bool QuBPIBpnng = false;
      bool lkuzeaTcfF = false;
      bool hpyrkgXDtu = false;
      bool lNYHwotGBr = false;
      bool SXBqCGeemc = false;
      bool LNruxZxJea = false;
      bool cltstXMmCp = false;
      bool gNbmlJoGoe = false;
      bool BsQQiYVdJW = false;
      bool rkaaPgdHwd = false;
      bool trcxwxlEIn = false;
      bool jpTAYjVcKV = false;
      bool ChcfyulAXE = false;
      string SNcBrXypVk;
      string OYSTkBkaCC;
      string FWIGTLJEqV;
      string zzbiyJGhAz;
      string gpgVHVxMwZ;
      string oBwcVwFVgg;
      string NszzkOwiVa;
      string tCZCUOplzx;
      string NxIQgyCzNB;
      string EkATlmpgjr;
      string YNpUflbtIG;
      string GSVjSPkiSm;
      string MxVTVJCFQh;
      string YIBHXAHmkt;
      string WIpHulOQBV;
      string BHOxfbrWyV;
      string iVcZgxQOLS;
      string IyyXPDGNXj;
      string tlEtfQsEaw;
      string HjnOKAePZx;
      if(SNcBrXypVk == YNpUflbtIG){VzFhMCJqhc = true;}
      else if(YNpUflbtIG == SNcBrXypVk){lNYHwotGBr = true;}
      if(OYSTkBkaCC == GSVjSPkiSm){VeyOaxQisP = true;}
      else if(GSVjSPkiSm == OYSTkBkaCC){SXBqCGeemc = true;}
      if(FWIGTLJEqV == MxVTVJCFQh){DMmOKXKiMO = true;}
      else if(MxVTVJCFQh == FWIGTLJEqV){LNruxZxJea = true;}
      if(zzbiyJGhAz == YIBHXAHmkt){XpmZOtgVgd = true;}
      else if(YIBHXAHmkt == zzbiyJGhAz){cltstXMmCp = true;}
      if(gpgVHVxMwZ == WIpHulOQBV){HCWyZclYnN = true;}
      else if(WIpHulOQBV == gpgVHVxMwZ){gNbmlJoGoe = true;}
      if(oBwcVwFVgg == BHOxfbrWyV){jwVJtIMpXo = true;}
      else if(BHOxfbrWyV == oBwcVwFVgg){BsQQiYVdJW = true;}
      if(NszzkOwiVa == iVcZgxQOLS){radSEeqXAf = true;}
      else if(iVcZgxQOLS == NszzkOwiVa){rkaaPgdHwd = true;}
      if(tCZCUOplzx == IyyXPDGNXj){QuBPIBpnng = true;}
      if(NxIQgyCzNB == tlEtfQsEaw){lkuzeaTcfF = true;}
      if(EkATlmpgjr == HjnOKAePZx){hpyrkgXDtu = true;}
      while(IyyXPDGNXj == tCZCUOplzx){trcxwxlEIn = true;}
      while(tlEtfQsEaw == tlEtfQsEaw){jpTAYjVcKV = true;}
      while(HjnOKAePZx == HjnOKAePZx){ChcfyulAXE = true;}
      if(VzFhMCJqhc == true){VzFhMCJqhc = false;}
      if(VeyOaxQisP == true){VeyOaxQisP = false;}
      if(DMmOKXKiMO == true){DMmOKXKiMO = false;}
      if(XpmZOtgVgd == true){XpmZOtgVgd = false;}
      if(HCWyZclYnN == true){HCWyZclYnN = false;}
      if(jwVJtIMpXo == true){jwVJtIMpXo = false;}
      if(radSEeqXAf == true){radSEeqXAf = false;}
      if(QuBPIBpnng == true){QuBPIBpnng = false;}
      if(lkuzeaTcfF == true){lkuzeaTcfF = false;}
      if(hpyrkgXDtu == true){hpyrkgXDtu = false;}
      if(lNYHwotGBr == true){lNYHwotGBr = false;}
      if(SXBqCGeemc == true){SXBqCGeemc = false;}
      if(LNruxZxJea == true){LNruxZxJea = false;}
      if(cltstXMmCp == true){cltstXMmCp = false;}
      if(gNbmlJoGoe == true){gNbmlJoGoe = false;}
      if(BsQQiYVdJW == true){BsQQiYVdJW = false;}
      if(rkaaPgdHwd == true){rkaaPgdHwd = false;}
      if(trcxwxlEIn == true){trcxwxlEIn = false;}
      if(jpTAYjVcKV == true){jpTAYjVcKV = false;}
      if(ChcfyulAXE == true){ChcfyulAXE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJMMOPSYJO
{ 
  void kkdXRAhFeK()
  { 
      bool KHkQjgwqlw = false;
      bool OKGPRSajgy = false;
      bool gyQEJxbaPt = false;
      bool rYURGuIEkw = false;
      bool RhbfAGUKfs = false;
      bool bsbKqMqfHm = false;
      bool EVaqEppoJV = false;
      bool KVykfyWkEC = false;
      bool bQtWSywKZt = false;
      bool EbxyqwGjaK = false;
      bool PfBJhGtqdr = false;
      bool oGbEKnaEYG = false;
      bool sfOORhYAtj = false;
      bool rlJtluOknL = false;
      bool DFfhExArmC = false;
      bool UBKUQjRmrz = false;
      bool gtxtADwgRO = false;
      bool YpQMCnzgJT = false;
      bool hgMqOpbocC = false;
      bool dbsneJIlgB = false;
      string bSPqjsTtJV;
      string SJgoCmLsht;
      string nPYLzGGbLa;
      string LsSMpcscEt;
      string msCquoJQwT;
      string rAYdrMsEqd;
      string mqhiJYpUzY;
      string tiomHtMgQK;
      string wofrhLUoTd;
      string jokaHuKThV;
      string yoRWZJLkVx;
      string zLmfhxLpAx;
      string EBAUoExOfM;
      string jsztMGXIRX;
      string ziSWeXBErJ;
      string iUTjRxowhU;
      string LwFJNGMsTa;
      string YCXbxUhdpR;
      string DsVVcOYObP;
      string RbaxMDcJIX;
      if(bSPqjsTtJV == yoRWZJLkVx){KHkQjgwqlw = true;}
      else if(yoRWZJLkVx == bSPqjsTtJV){PfBJhGtqdr = true;}
      if(SJgoCmLsht == zLmfhxLpAx){OKGPRSajgy = true;}
      else if(zLmfhxLpAx == SJgoCmLsht){oGbEKnaEYG = true;}
      if(nPYLzGGbLa == EBAUoExOfM){gyQEJxbaPt = true;}
      else if(EBAUoExOfM == nPYLzGGbLa){sfOORhYAtj = true;}
      if(LsSMpcscEt == jsztMGXIRX){rYURGuIEkw = true;}
      else if(jsztMGXIRX == LsSMpcscEt){rlJtluOknL = true;}
      if(msCquoJQwT == ziSWeXBErJ){RhbfAGUKfs = true;}
      else if(ziSWeXBErJ == msCquoJQwT){DFfhExArmC = true;}
      if(rAYdrMsEqd == iUTjRxowhU){bsbKqMqfHm = true;}
      else if(iUTjRxowhU == rAYdrMsEqd){UBKUQjRmrz = true;}
      if(mqhiJYpUzY == LwFJNGMsTa){EVaqEppoJV = true;}
      else if(LwFJNGMsTa == mqhiJYpUzY){gtxtADwgRO = true;}
      if(tiomHtMgQK == YCXbxUhdpR){KVykfyWkEC = true;}
      if(wofrhLUoTd == DsVVcOYObP){bQtWSywKZt = true;}
      if(jokaHuKThV == RbaxMDcJIX){EbxyqwGjaK = true;}
      while(YCXbxUhdpR == tiomHtMgQK){YpQMCnzgJT = true;}
      while(DsVVcOYObP == DsVVcOYObP){hgMqOpbocC = true;}
      while(RbaxMDcJIX == RbaxMDcJIX){dbsneJIlgB = true;}
      if(KHkQjgwqlw == true){KHkQjgwqlw = false;}
      if(OKGPRSajgy == true){OKGPRSajgy = false;}
      if(gyQEJxbaPt == true){gyQEJxbaPt = false;}
      if(rYURGuIEkw == true){rYURGuIEkw = false;}
      if(RhbfAGUKfs == true){RhbfAGUKfs = false;}
      if(bsbKqMqfHm == true){bsbKqMqfHm = false;}
      if(EVaqEppoJV == true){EVaqEppoJV = false;}
      if(KVykfyWkEC == true){KVykfyWkEC = false;}
      if(bQtWSywKZt == true){bQtWSywKZt = false;}
      if(EbxyqwGjaK == true){EbxyqwGjaK = false;}
      if(PfBJhGtqdr == true){PfBJhGtqdr = false;}
      if(oGbEKnaEYG == true){oGbEKnaEYG = false;}
      if(sfOORhYAtj == true){sfOORhYAtj = false;}
      if(rlJtluOknL == true){rlJtluOknL = false;}
      if(DFfhExArmC == true){DFfhExArmC = false;}
      if(UBKUQjRmrz == true){UBKUQjRmrz = false;}
      if(gtxtADwgRO == true){gtxtADwgRO = false;}
      if(YpQMCnzgJT == true){YpQMCnzgJT = false;}
      if(hgMqOpbocC == true){hgMqOpbocC = false;}
      if(dbsneJIlgB == true){dbsneJIlgB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THIKNHORVA
{ 
  void sYMykPrMXL()
  { 
      bool nlQXlsrDqP = false;
      bool rRINyGApYG = false;
      bool ZiJdorqrNu = false;
      bool tTtGeljlTR = false;
      bool FUCcEolKHV = false;
      bool hTMdhFcmis = false;
      bool CAowVXWChM = false;
      bool VOVHBFffYz = false;
      bool GfjrNZHQYZ = false;
      bool IxCZOEfGHf = false;
      bool SjbuzTyEbb = false;
      bool YxNimVPxhu = false;
      bool QGdIDYLwrw = false;
      bool ZZYrgVDors = false;
      bool bCnwBLjSls = false;
      bool nhXLPLGTqa = false;
      bool ICLfCyXUCR = false;
      bool RaFoTNRgGr = false;
      bool orJzHqCMcU = false;
      bool OjyQkZqIsC = false;
      string eSgnJGbMKi;
      string ShkWImSrHY;
      string RXNUwnriVx;
      string aYfidOSIqt;
      string YKiCZaSiLG;
      string LqoFAGELrV;
      string OsqNItBBrt;
      string UJAMAHoKtU;
      string UIWOljiahX;
      string KGPVfeSVtf;
      string YQqQkBpcEs;
      string RsQWAFVbaX;
      string KaTUjNtegU;
      string nSQOuERFdj;
      string sGVoGQorUZ;
      string JqtVUywWgW;
      string HKwjEycCbw;
      string nPyqdEFeNS;
      string YBKGKxXtsx;
      string HuYGciKkjH;
      if(eSgnJGbMKi == YQqQkBpcEs){nlQXlsrDqP = true;}
      else if(YQqQkBpcEs == eSgnJGbMKi){SjbuzTyEbb = true;}
      if(ShkWImSrHY == RsQWAFVbaX){rRINyGApYG = true;}
      else if(RsQWAFVbaX == ShkWImSrHY){YxNimVPxhu = true;}
      if(RXNUwnriVx == KaTUjNtegU){ZiJdorqrNu = true;}
      else if(KaTUjNtegU == RXNUwnriVx){QGdIDYLwrw = true;}
      if(aYfidOSIqt == nSQOuERFdj){tTtGeljlTR = true;}
      else if(nSQOuERFdj == aYfidOSIqt){ZZYrgVDors = true;}
      if(YKiCZaSiLG == sGVoGQorUZ){FUCcEolKHV = true;}
      else if(sGVoGQorUZ == YKiCZaSiLG){bCnwBLjSls = true;}
      if(LqoFAGELrV == JqtVUywWgW){hTMdhFcmis = true;}
      else if(JqtVUywWgW == LqoFAGELrV){nhXLPLGTqa = true;}
      if(OsqNItBBrt == HKwjEycCbw){CAowVXWChM = true;}
      else if(HKwjEycCbw == OsqNItBBrt){ICLfCyXUCR = true;}
      if(UJAMAHoKtU == nPyqdEFeNS){VOVHBFffYz = true;}
      if(UIWOljiahX == YBKGKxXtsx){GfjrNZHQYZ = true;}
      if(KGPVfeSVtf == HuYGciKkjH){IxCZOEfGHf = true;}
      while(nPyqdEFeNS == UJAMAHoKtU){RaFoTNRgGr = true;}
      while(YBKGKxXtsx == YBKGKxXtsx){orJzHqCMcU = true;}
      while(HuYGciKkjH == HuYGciKkjH){OjyQkZqIsC = true;}
      if(nlQXlsrDqP == true){nlQXlsrDqP = false;}
      if(rRINyGApYG == true){rRINyGApYG = false;}
      if(ZiJdorqrNu == true){ZiJdorqrNu = false;}
      if(tTtGeljlTR == true){tTtGeljlTR = false;}
      if(FUCcEolKHV == true){FUCcEolKHV = false;}
      if(hTMdhFcmis == true){hTMdhFcmis = false;}
      if(CAowVXWChM == true){CAowVXWChM = false;}
      if(VOVHBFffYz == true){VOVHBFffYz = false;}
      if(GfjrNZHQYZ == true){GfjrNZHQYZ = false;}
      if(IxCZOEfGHf == true){IxCZOEfGHf = false;}
      if(SjbuzTyEbb == true){SjbuzTyEbb = false;}
      if(YxNimVPxhu == true){YxNimVPxhu = false;}
      if(QGdIDYLwrw == true){QGdIDYLwrw = false;}
      if(ZZYrgVDors == true){ZZYrgVDors = false;}
      if(bCnwBLjSls == true){bCnwBLjSls = false;}
      if(nhXLPLGTqa == true){nhXLPLGTqa = false;}
      if(ICLfCyXUCR == true){ICLfCyXUCR = false;}
      if(RaFoTNRgGr == true){RaFoTNRgGr = false;}
      if(orJzHqCMcU == true){orJzHqCMcU = false;}
      if(OjyQkZqIsC == true){OjyQkZqIsC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KZMKYLABUA
{ 
  void UfFwsuiVAB()
  { 
      bool thuQhnSnpj = false;
      bool htCYgYYlGc = false;
      bool ASUpoEERDk = false;
      bool WVDfFwETXM = false;
      bool RODPSTmkIi = false;
      bool lFjYraMEbd = false;
      bool jAkEMMpWSj = false;
      bool TEOsKlPEWV = false;
      bool QTJTyRlemd = false;
      bool iArtcQdyDG = false;
      bool cQRXPhppNF = false;
      bool LHhFMQpQGt = false;
      bool aLioBTMUQs = false;
      bool IQBPsABlEQ = false;
      bool buQgRaRlgM = false;
      bool aMrIfQhcVw = false;
      bool VVZTxuGSMM = false;
      bool ODMoSfuBWZ = false;
      bool CZmESuXsjc = false;
      bool RYQHtFUwjV = false;
      string kXUQGBRAIr;
      string JqOfqzgXaO;
      string ffrCZIeGwU;
      string pCXGIgqShH;
      string KlhGFXbTqB;
      string aFsOSFfSpx;
      string VLDmCHSIXJ;
      string HOpTDtykxB;
      string gLOtsjIInD;
      string BYbjlzitEx;
      string ETugtLPZLY;
      string GtUoQJwItR;
      string yJTUHhmFgD;
      string LDgzwNPhAg;
      string UixOwHDmTb;
      string CaAmzuzaYL;
      string YJrHNDMVrD;
      string sNHMwOMFYA;
      string dAkFBkCtAB;
      string NoJoILqpBs;
      if(kXUQGBRAIr == ETugtLPZLY){thuQhnSnpj = true;}
      else if(ETugtLPZLY == kXUQGBRAIr){cQRXPhppNF = true;}
      if(JqOfqzgXaO == GtUoQJwItR){htCYgYYlGc = true;}
      else if(GtUoQJwItR == JqOfqzgXaO){LHhFMQpQGt = true;}
      if(ffrCZIeGwU == yJTUHhmFgD){ASUpoEERDk = true;}
      else if(yJTUHhmFgD == ffrCZIeGwU){aLioBTMUQs = true;}
      if(pCXGIgqShH == LDgzwNPhAg){WVDfFwETXM = true;}
      else if(LDgzwNPhAg == pCXGIgqShH){IQBPsABlEQ = true;}
      if(KlhGFXbTqB == UixOwHDmTb){RODPSTmkIi = true;}
      else if(UixOwHDmTb == KlhGFXbTqB){buQgRaRlgM = true;}
      if(aFsOSFfSpx == CaAmzuzaYL){lFjYraMEbd = true;}
      else if(CaAmzuzaYL == aFsOSFfSpx){aMrIfQhcVw = true;}
      if(VLDmCHSIXJ == YJrHNDMVrD){jAkEMMpWSj = true;}
      else if(YJrHNDMVrD == VLDmCHSIXJ){VVZTxuGSMM = true;}
      if(HOpTDtykxB == sNHMwOMFYA){TEOsKlPEWV = true;}
      if(gLOtsjIInD == dAkFBkCtAB){QTJTyRlemd = true;}
      if(BYbjlzitEx == NoJoILqpBs){iArtcQdyDG = true;}
      while(sNHMwOMFYA == HOpTDtykxB){ODMoSfuBWZ = true;}
      while(dAkFBkCtAB == dAkFBkCtAB){CZmESuXsjc = true;}
      while(NoJoILqpBs == NoJoILqpBs){RYQHtFUwjV = true;}
      if(thuQhnSnpj == true){thuQhnSnpj = false;}
      if(htCYgYYlGc == true){htCYgYYlGc = false;}
      if(ASUpoEERDk == true){ASUpoEERDk = false;}
      if(WVDfFwETXM == true){WVDfFwETXM = false;}
      if(RODPSTmkIi == true){RODPSTmkIi = false;}
      if(lFjYraMEbd == true){lFjYraMEbd = false;}
      if(jAkEMMpWSj == true){jAkEMMpWSj = false;}
      if(TEOsKlPEWV == true){TEOsKlPEWV = false;}
      if(QTJTyRlemd == true){QTJTyRlemd = false;}
      if(iArtcQdyDG == true){iArtcQdyDG = false;}
      if(cQRXPhppNF == true){cQRXPhppNF = false;}
      if(LHhFMQpQGt == true){LHhFMQpQGt = false;}
      if(aLioBTMUQs == true){aLioBTMUQs = false;}
      if(IQBPsABlEQ == true){IQBPsABlEQ = false;}
      if(buQgRaRlgM == true){buQgRaRlgM = false;}
      if(aMrIfQhcVw == true){aMrIfQhcVw = false;}
      if(VVZTxuGSMM == true){VVZTxuGSMM = false;}
      if(ODMoSfuBWZ == true){ODMoSfuBWZ = false;}
      if(CZmESuXsjc == true){CZmESuXsjc = false;}
      if(RYQHtFUwjV == true){RYQHtFUwjV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWHPFZXFFS
{ 
  void yDjkMdxkPq()
  { 
      bool PRMMLzewOu = false;
      bool wJTLfYLQBj = false;
      bool bQlXtefJUI = false;
      bool jsSOygaPHl = false;
      bool qKkDWrttbk = false;
      bool tsGQizenSf = false;
      bool SVbGKCqFMz = false;
      bool ywJPrReiBB = false;
      bool klhiOqmBfy = false;
      bool BlwaSVidrU = false;
      bool AnhblxiqYR = false;
      bool UwmQugnrrT = false;
      bool PoZNxMzhwV = false;
      bool iApgAwEFxQ = false;
      bool HucNdEzfel = false;
      bool hplXEKOTdZ = false;
      bool xAtCiTFGPz = false;
      bool bhubMTMLis = false;
      bool NTDJmrOSbp = false;
      bool gjaXSGBZdK = false;
      string qrRXLuNhBp;
      string WmeRMkbSLw;
      string dPfeFyTtQa;
      string NilVmoLbxh;
      string WNEOOuNusC;
      string CtjiobMmRM;
      string aSQabmAIeX;
      string YAVcZPLQPK;
      string kYBOYSzDgK;
      string bYKkGDxcmb;
      string tEPVdCYGIY;
      string QuWHbCRBBI;
      string mwaUuzokWV;
      string ShdmQfJfkW;
      string tstHtgBCIE;
      string kuadoxduZd;
      string MnilGhQjpw;
      string slQeOsBTaO;
      string ymbSkWGAyS;
      string COFHKGJIBL;
      if(qrRXLuNhBp == tEPVdCYGIY){PRMMLzewOu = true;}
      else if(tEPVdCYGIY == qrRXLuNhBp){AnhblxiqYR = true;}
      if(WmeRMkbSLw == QuWHbCRBBI){wJTLfYLQBj = true;}
      else if(QuWHbCRBBI == WmeRMkbSLw){UwmQugnrrT = true;}
      if(dPfeFyTtQa == mwaUuzokWV){bQlXtefJUI = true;}
      else if(mwaUuzokWV == dPfeFyTtQa){PoZNxMzhwV = true;}
      if(NilVmoLbxh == ShdmQfJfkW){jsSOygaPHl = true;}
      else if(ShdmQfJfkW == NilVmoLbxh){iApgAwEFxQ = true;}
      if(WNEOOuNusC == tstHtgBCIE){qKkDWrttbk = true;}
      else if(tstHtgBCIE == WNEOOuNusC){HucNdEzfel = true;}
      if(CtjiobMmRM == kuadoxduZd){tsGQizenSf = true;}
      else if(kuadoxduZd == CtjiobMmRM){hplXEKOTdZ = true;}
      if(aSQabmAIeX == MnilGhQjpw){SVbGKCqFMz = true;}
      else if(MnilGhQjpw == aSQabmAIeX){xAtCiTFGPz = true;}
      if(YAVcZPLQPK == slQeOsBTaO){ywJPrReiBB = true;}
      if(kYBOYSzDgK == ymbSkWGAyS){klhiOqmBfy = true;}
      if(bYKkGDxcmb == COFHKGJIBL){BlwaSVidrU = true;}
      while(slQeOsBTaO == YAVcZPLQPK){bhubMTMLis = true;}
      while(ymbSkWGAyS == ymbSkWGAyS){NTDJmrOSbp = true;}
      while(COFHKGJIBL == COFHKGJIBL){gjaXSGBZdK = true;}
      if(PRMMLzewOu == true){PRMMLzewOu = false;}
      if(wJTLfYLQBj == true){wJTLfYLQBj = false;}
      if(bQlXtefJUI == true){bQlXtefJUI = false;}
      if(jsSOygaPHl == true){jsSOygaPHl = false;}
      if(qKkDWrttbk == true){qKkDWrttbk = false;}
      if(tsGQizenSf == true){tsGQizenSf = false;}
      if(SVbGKCqFMz == true){SVbGKCqFMz = false;}
      if(ywJPrReiBB == true){ywJPrReiBB = false;}
      if(klhiOqmBfy == true){klhiOqmBfy = false;}
      if(BlwaSVidrU == true){BlwaSVidrU = false;}
      if(AnhblxiqYR == true){AnhblxiqYR = false;}
      if(UwmQugnrrT == true){UwmQugnrrT = false;}
      if(PoZNxMzhwV == true){PoZNxMzhwV = false;}
      if(iApgAwEFxQ == true){iApgAwEFxQ = false;}
      if(HucNdEzfel == true){HucNdEzfel = false;}
      if(hplXEKOTdZ == true){hplXEKOTdZ = false;}
      if(xAtCiTFGPz == true){xAtCiTFGPz = false;}
      if(bhubMTMLis == true){bhubMTMLis = false;}
      if(NTDJmrOSbp == true){NTDJmrOSbp = false;}
      if(gjaXSGBZdK == true){gjaXSGBZdK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDVZMCTTGR
{ 
  void ulEzpwBxUg()
  { 
      bool fMtTQKkpTe = false;
      bool XPsoKmrUbz = false;
      bool RZcRNkrzQE = false;
      bool LSOnJLzfMF = false;
      bool YDUFQPVibT = false;
      bool QuLwNFicGe = false;
      bool SkZOSEAEez = false;
      bool nLIWaNEWBx = false;
      bool PIXwnQHSaD = false;
      bool bVZglmdFmL = false;
      bool OREcfElnVA = false;
      bool BMbIPJNcaB = false;
      bool xhcaWRlajm = false;
      bool iyjoixEtQi = false;
      bool dSxaCPtQRc = false;
      bool ZAekNfncGN = false;
      bool RLEhQCblZR = false;
      bool ETMrXdkBYH = false;
      bool XVJHNiTzaC = false;
      bool JbmCQSOOKA = false;
      string oEkRxXiWiR;
      string htTpGJDhFV;
      string FjumHBwxMI;
      string qkpFRoejHT;
      string hpAYwVEwfL;
      string thdYHFIxKu;
      string blJZZxENXQ;
      string eTZlnOiVqk;
      string wzRBOJGQxM;
      string ggZMrwfZyy;
      string RpXOfaHrkr;
      string VlGYybTILQ;
      string qmPLjytNsr;
      string hJWrSFbCUn;
      string COfFqtZANQ;
      string bXOhHeZMdh;
      string gsyrJMONFs;
      string AQmXNbGKTo;
      string XsAcPKtokn;
      string eOYmHJPmue;
      if(oEkRxXiWiR == RpXOfaHrkr){fMtTQKkpTe = true;}
      else if(RpXOfaHrkr == oEkRxXiWiR){OREcfElnVA = true;}
      if(htTpGJDhFV == VlGYybTILQ){XPsoKmrUbz = true;}
      else if(VlGYybTILQ == htTpGJDhFV){BMbIPJNcaB = true;}
      if(FjumHBwxMI == qmPLjytNsr){RZcRNkrzQE = true;}
      else if(qmPLjytNsr == FjumHBwxMI){xhcaWRlajm = true;}
      if(qkpFRoejHT == hJWrSFbCUn){LSOnJLzfMF = true;}
      else if(hJWrSFbCUn == qkpFRoejHT){iyjoixEtQi = true;}
      if(hpAYwVEwfL == COfFqtZANQ){YDUFQPVibT = true;}
      else if(COfFqtZANQ == hpAYwVEwfL){dSxaCPtQRc = true;}
      if(thdYHFIxKu == bXOhHeZMdh){QuLwNFicGe = true;}
      else if(bXOhHeZMdh == thdYHFIxKu){ZAekNfncGN = true;}
      if(blJZZxENXQ == gsyrJMONFs){SkZOSEAEez = true;}
      else if(gsyrJMONFs == blJZZxENXQ){RLEhQCblZR = true;}
      if(eTZlnOiVqk == AQmXNbGKTo){nLIWaNEWBx = true;}
      if(wzRBOJGQxM == XsAcPKtokn){PIXwnQHSaD = true;}
      if(ggZMrwfZyy == eOYmHJPmue){bVZglmdFmL = true;}
      while(AQmXNbGKTo == eTZlnOiVqk){ETMrXdkBYH = true;}
      while(XsAcPKtokn == XsAcPKtokn){XVJHNiTzaC = true;}
      while(eOYmHJPmue == eOYmHJPmue){JbmCQSOOKA = true;}
      if(fMtTQKkpTe == true){fMtTQKkpTe = false;}
      if(XPsoKmrUbz == true){XPsoKmrUbz = false;}
      if(RZcRNkrzQE == true){RZcRNkrzQE = false;}
      if(LSOnJLzfMF == true){LSOnJLzfMF = false;}
      if(YDUFQPVibT == true){YDUFQPVibT = false;}
      if(QuLwNFicGe == true){QuLwNFicGe = false;}
      if(SkZOSEAEez == true){SkZOSEAEez = false;}
      if(nLIWaNEWBx == true){nLIWaNEWBx = false;}
      if(PIXwnQHSaD == true){PIXwnQHSaD = false;}
      if(bVZglmdFmL == true){bVZglmdFmL = false;}
      if(OREcfElnVA == true){OREcfElnVA = false;}
      if(BMbIPJNcaB == true){BMbIPJNcaB = false;}
      if(xhcaWRlajm == true){xhcaWRlajm = false;}
      if(iyjoixEtQi == true){iyjoixEtQi = false;}
      if(dSxaCPtQRc == true){dSxaCPtQRc = false;}
      if(ZAekNfncGN == true){ZAekNfncGN = false;}
      if(RLEhQCblZR == true){RLEhQCblZR = false;}
      if(ETMrXdkBYH == true){ETMrXdkBYH = false;}
      if(XVJHNiTzaC == true){XVJHNiTzaC = false;}
      if(JbmCQSOOKA == true){JbmCQSOOKA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAGMAZMFUJ
{ 
  void RXZipOYpRK()
  { 
      bool rPNoIHpdfh = false;
      bool REDdpKwSkZ = false;
      bool WRgwsbrIwK = false;
      bool tPsuyGIgRj = false;
      bool qEHUlGJNmf = false;
      bool GlOFQZhRug = false;
      bool OhhVnCLIfj = false;
      bool BOBAiSJMJm = false;
      bool SeUPDHAndX = false;
      bool XpljVIWlfj = false;
      bool uBhDdrjNWy = false;
      bool PUHINiMRSg = false;
      bool BXdHLLcQeZ = false;
      bool wXgZqRxRkL = false;
      bool WmQeHDhcVl = false;
      bool uESzhXWZrS = false;
      bool OTiwCrnhQw = false;
      bool lufHJOGzzI = false;
      bool cztrdqEgrT = false;
      bool tXYSwDEUcP = false;
      string mbqJCSOzzl;
      string GzENKwnRCU;
      string ZFcHMfNAxy;
      string wrUohkFzLq;
      string zIcRrCDwhY;
      string HpbgjhyjwW;
      string FNBBoNePeZ;
      string qnGKURbKOJ;
      string bQSYpGQnEA;
      string lUCollGbce;
      string XnRHhSjRLR;
      string FnUmtntcKi;
      string xqKdnVlRXi;
      string KzhjlnzKpX;
      string VybltyAPtx;
      string qcRsggcmTM;
      string gSscHFGjBF;
      string njmmNyOXjp;
      string VWWaqghnDE;
      string LMqdpDEzen;
      if(mbqJCSOzzl == XnRHhSjRLR){rPNoIHpdfh = true;}
      else if(XnRHhSjRLR == mbqJCSOzzl){uBhDdrjNWy = true;}
      if(GzENKwnRCU == FnUmtntcKi){REDdpKwSkZ = true;}
      else if(FnUmtntcKi == GzENKwnRCU){PUHINiMRSg = true;}
      if(ZFcHMfNAxy == xqKdnVlRXi){WRgwsbrIwK = true;}
      else if(xqKdnVlRXi == ZFcHMfNAxy){BXdHLLcQeZ = true;}
      if(wrUohkFzLq == KzhjlnzKpX){tPsuyGIgRj = true;}
      else if(KzhjlnzKpX == wrUohkFzLq){wXgZqRxRkL = true;}
      if(zIcRrCDwhY == VybltyAPtx){qEHUlGJNmf = true;}
      else if(VybltyAPtx == zIcRrCDwhY){WmQeHDhcVl = true;}
      if(HpbgjhyjwW == qcRsggcmTM){GlOFQZhRug = true;}
      else if(qcRsggcmTM == HpbgjhyjwW){uESzhXWZrS = true;}
      if(FNBBoNePeZ == gSscHFGjBF){OhhVnCLIfj = true;}
      else if(gSscHFGjBF == FNBBoNePeZ){OTiwCrnhQw = true;}
      if(qnGKURbKOJ == njmmNyOXjp){BOBAiSJMJm = true;}
      if(bQSYpGQnEA == VWWaqghnDE){SeUPDHAndX = true;}
      if(lUCollGbce == LMqdpDEzen){XpljVIWlfj = true;}
      while(njmmNyOXjp == qnGKURbKOJ){lufHJOGzzI = true;}
      while(VWWaqghnDE == VWWaqghnDE){cztrdqEgrT = true;}
      while(LMqdpDEzen == LMqdpDEzen){tXYSwDEUcP = true;}
      if(rPNoIHpdfh == true){rPNoIHpdfh = false;}
      if(REDdpKwSkZ == true){REDdpKwSkZ = false;}
      if(WRgwsbrIwK == true){WRgwsbrIwK = false;}
      if(tPsuyGIgRj == true){tPsuyGIgRj = false;}
      if(qEHUlGJNmf == true){qEHUlGJNmf = false;}
      if(GlOFQZhRug == true){GlOFQZhRug = false;}
      if(OhhVnCLIfj == true){OhhVnCLIfj = false;}
      if(BOBAiSJMJm == true){BOBAiSJMJm = false;}
      if(SeUPDHAndX == true){SeUPDHAndX = false;}
      if(XpljVIWlfj == true){XpljVIWlfj = false;}
      if(uBhDdrjNWy == true){uBhDdrjNWy = false;}
      if(PUHINiMRSg == true){PUHINiMRSg = false;}
      if(BXdHLLcQeZ == true){BXdHLLcQeZ = false;}
      if(wXgZqRxRkL == true){wXgZqRxRkL = false;}
      if(WmQeHDhcVl == true){WmQeHDhcVl = false;}
      if(uESzhXWZrS == true){uESzhXWZrS = false;}
      if(OTiwCrnhQw == true){OTiwCrnhQw = false;}
      if(lufHJOGzzI == true){lufHJOGzzI = false;}
      if(cztrdqEgrT == true){cztrdqEgrT = false;}
      if(tXYSwDEUcP == true){tXYSwDEUcP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCPOLXLVXT
{ 
  void ucVfgycMpP()
  { 
      bool UcIJduoWSO = false;
      bool NVgHVUicgC = false;
      bool LjPIMoRwNC = false;
      bool AENqeqWQwJ = false;
      bool CoFRyyPhAH = false;
      bool WPdEpkNAwo = false;
      bool drIQOJIpcd = false;
      bool yRfWzWdyJO = false;
      bool ZjwFejZIAs = false;
      bool cVUHfKfoCo = false;
      bool pZEVJEiHET = false;
      bool HPqgPtuCkd = false;
      bool jzojBcxYpo = false;
      bool pouTXzeawZ = false;
      bool BRDgkMdmrl = false;
      bool OcDXFpjUTf = false;
      bool HKRPcSTXJP = false;
      bool OUFLcRuHyn = false;
      bool zJgEZNlXNg = false;
      bool OKGQRqAnES = false;
      string CakRacdJDm;
      string cPsSLkZHMT;
      string uxRObGCmju;
      string VxIabugcFy;
      string AKpQbxgkCn;
      string HdHOeEJWoT;
      string ZpYIQeGSqQ;
      string ExCNSkHAle;
      string ZRjunrpswW;
      string lKnkXJkhAx;
      string pNtljKbswt;
      string xIkJtIFdUY;
      string oMWTdtJRpJ;
      string zZAnoLWyLd;
      string PwxBZdZdqP;
      string DHNbHcqaIp;
      string AJDltXIwUh;
      string kHRpIsPUsA;
      string UfaZFrLYfM;
      string UwpVcGrKHC;
      if(CakRacdJDm == pNtljKbswt){UcIJduoWSO = true;}
      else if(pNtljKbswt == CakRacdJDm){pZEVJEiHET = true;}
      if(cPsSLkZHMT == xIkJtIFdUY){NVgHVUicgC = true;}
      else if(xIkJtIFdUY == cPsSLkZHMT){HPqgPtuCkd = true;}
      if(uxRObGCmju == oMWTdtJRpJ){LjPIMoRwNC = true;}
      else if(oMWTdtJRpJ == uxRObGCmju){jzojBcxYpo = true;}
      if(VxIabugcFy == zZAnoLWyLd){AENqeqWQwJ = true;}
      else if(zZAnoLWyLd == VxIabugcFy){pouTXzeawZ = true;}
      if(AKpQbxgkCn == PwxBZdZdqP){CoFRyyPhAH = true;}
      else if(PwxBZdZdqP == AKpQbxgkCn){BRDgkMdmrl = true;}
      if(HdHOeEJWoT == DHNbHcqaIp){WPdEpkNAwo = true;}
      else if(DHNbHcqaIp == HdHOeEJWoT){OcDXFpjUTf = true;}
      if(ZpYIQeGSqQ == AJDltXIwUh){drIQOJIpcd = true;}
      else if(AJDltXIwUh == ZpYIQeGSqQ){HKRPcSTXJP = true;}
      if(ExCNSkHAle == kHRpIsPUsA){yRfWzWdyJO = true;}
      if(ZRjunrpswW == UfaZFrLYfM){ZjwFejZIAs = true;}
      if(lKnkXJkhAx == UwpVcGrKHC){cVUHfKfoCo = true;}
      while(kHRpIsPUsA == ExCNSkHAle){OUFLcRuHyn = true;}
      while(UfaZFrLYfM == UfaZFrLYfM){zJgEZNlXNg = true;}
      while(UwpVcGrKHC == UwpVcGrKHC){OKGQRqAnES = true;}
      if(UcIJduoWSO == true){UcIJduoWSO = false;}
      if(NVgHVUicgC == true){NVgHVUicgC = false;}
      if(LjPIMoRwNC == true){LjPIMoRwNC = false;}
      if(AENqeqWQwJ == true){AENqeqWQwJ = false;}
      if(CoFRyyPhAH == true){CoFRyyPhAH = false;}
      if(WPdEpkNAwo == true){WPdEpkNAwo = false;}
      if(drIQOJIpcd == true){drIQOJIpcd = false;}
      if(yRfWzWdyJO == true){yRfWzWdyJO = false;}
      if(ZjwFejZIAs == true){ZjwFejZIAs = false;}
      if(cVUHfKfoCo == true){cVUHfKfoCo = false;}
      if(pZEVJEiHET == true){pZEVJEiHET = false;}
      if(HPqgPtuCkd == true){HPqgPtuCkd = false;}
      if(jzojBcxYpo == true){jzojBcxYpo = false;}
      if(pouTXzeawZ == true){pouTXzeawZ = false;}
      if(BRDgkMdmrl == true){BRDgkMdmrl = false;}
      if(OcDXFpjUTf == true){OcDXFpjUTf = false;}
      if(HKRPcSTXJP == true){HKRPcSTXJP = false;}
      if(OUFLcRuHyn == true){OUFLcRuHyn = false;}
      if(zJgEZNlXNg == true){zJgEZNlXNg = false;}
      if(OKGQRqAnES == true){OKGQRqAnES = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWUKSORIDC
{ 
  void ERolorJdTt()
  { 
      bool urRQjoWVbi = false;
      bool MfsNVRAHTJ = false;
      bool hnFARioJOT = false;
      bool CjGLEAtJpg = false;
      bool HgETtZasJk = false;
      bool qjAEyGmRyA = false;
      bool zNGHgbZhIU = false;
      bool WpRmBAjkGr = false;
      bool IwAccRjCMy = false;
      bool NbKogtZxlR = false;
      bool AsjnNARMCy = false;
      bool WBLGqDNdeP = false;
      bool rXUKGufcGH = false;
      bool ZlynqPLLOc = false;
      bool zXzOaLQDxd = false;
      bool fwRWZcXZgS = false;
      bool ToGuXjDWOb = false;
      bool rCOCPTXFju = false;
      bool dbecbcUbNO = false;
      bool qldwIKQDpp = false;
      string NQwEobSiye;
      string WxHGCCodci;
      string MIpYPWKByE;
      string peWyAfPwpP;
      string VcfFqIkFBu;
      string IfIMOEZXnS;
      string QRjtnqaJGW;
      string lsnMMickgH;
      string kFzCuKVKiu;
      string FqHXzErkQz;
      string hbyeJPruzf;
      string bopggKRgyd;
      string UPZLQtlQNI;
      string pqThYIHUsf;
      string SaKDSQBZpn;
      string lLmmdRCmNO;
      string cahpokUIHY;
      string DwnRLtEVsA;
      string sLaZVeDgDH;
      string GUHeCqrUOg;
      if(NQwEobSiye == hbyeJPruzf){urRQjoWVbi = true;}
      else if(hbyeJPruzf == NQwEobSiye){AsjnNARMCy = true;}
      if(WxHGCCodci == bopggKRgyd){MfsNVRAHTJ = true;}
      else if(bopggKRgyd == WxHGCCodci){WBLGqDNdeP = true;}
      if(MIpYPWKByE == UPZLQtlQNI){hnFARioJOT = true;}
      else if(UPZLQtlQNI == MIpYPWKByE){rXUKGufcGH = true;}
      if(peWyAfPwpP == pqThYIHUsf){CjGLEAtJpg = true;}
      else if(pqThYIHUsf == peWyAfPwpP){ZlynqPLLOc = true;}
      if(VcfFqIkFBu == SaKDSQBZpn){HgETtZasJk = true;}
      else if(SaKDSQBZpn == VcfFqIkFBu){zXzOaLQDxd = true;}
      if(IfIMOEZXnS == lLmmdRCmNO){qjAEyGmRyA = true;}
      else if(lLmmdRCmNO == IfIMOEZXnS){fwRWZcXZgS = true;}
      if(QRjtnqaJGW == cahpokUIHY){zNGHgbZhIU = true;}
      else if(cahpokUIHY == QRjtnqaJGW){ToGuXjDWOb = true;}
      if(lsnMMickgH == DwnRLtEVsA){WpRmBAjkGr = true;}
      if(kFzCuKVKiu == sLaZVeDgDH){IwAccRjCMy = true;}
      if(FqHXzErkQz == GUHeCqrUOg){NbKogtZxlR = true;}
      while(DwnRLtEVsA == lsnMMickgH){rCOCPTXFju = true;}
      while(sLaZVeDgDH == sLaZVeDgDH){dbecbcUbNO = true;}
      while(GUHeCqrUOg == GUHeCqrUOg){qldwIKQDpp = true;}
      if(urRQjoWVbi == true){urRQjoWVbi = false;}
      if(MfsNVRAHTJ == true){MfsNVRAHTJ = false;}
      if(hnFARioJOT == true){hnFARioJOT = false;}
      if(CjGLEAtJpg == true){CjGLEAtJpg = false;}
      if(HgETtZasJk == true){HgETtZasJk = false;}
      if(qjAEyGmRyA == true){qjAEyGmRyA = false;}
      if(zNGHgbZhIU == true){zNGHgbZhIU = false;}
      if(WpRmBAjkGr == true){WpRmBAjkGr = false;}
      if(IwAccRjCMy == true){IwAccRjCMy = false;}
      if(NbKogtZxlR == true){NbKogtZxlR = false;}
      if(AsjnNARMCy == true){AsjnNARMCy = false;}
      if(WBLGqDNdeP == true){WBLGqDNdeP = false;}
      if(rXUKGufcGH == true){rXUKGufcGH = false;}
      if(ZlynqPLLOc == true){ZlynqPLLOc = false;}
      if(zXzOaLQDxd == true){zXzOaLQDxd = false;}
      if(fwRWZcXZgS == true){fwRWZcXZgS = false;}
      if(ToGuXjDWOb == true){ToGuXjDWOb = false;}
      if(rCOCPTXFju == true){rCOCPTXFju = false;}
      if(dbecbcUbNO == true){dbecbcUbNO = false;}
      if(qldwIKQDpp == true){qldwIKQDpp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHESOJXGVV
{ 
  void uXhelhtBlf()
  { 
      bool aIwceXTrUa = false;
      bool sNkGYcwCRe = false;
      bool wPbFWwhuZQ = false;
      bool ckTGrTVQOV = false;
      bool mRwUPZYWJN = false;
      bool AbaMcLgpFh = false;
      bool oYRDyIsdOF = false;
      bool GemwreSGpw = false;
      bool WLkMQBKHcg = false;
      bool lfKffNzrWG = false;
      bool fuIEGUneUy = false;
      bool sZzILdnFmw = false;
      bool ylBgSaUHPd = false;
      bool fZjiPbDgFu = false;
      bool NflenMfBUC = false;
      bool ZtFZIttakf = false;
      bool AfOpRSpQsi = false;
      bool ZHzriSzVsG = false;
      bool tSlMElUJaV = false;
      bool hbuZtgQwMU = false;
      string wwnOTAyyjj;
      string HrwWXYiJOz;
      string fxepbOHasX;
      string ZaNgEGguQO;
      string WPVtumhyTA;
      string NPaSIzQxlF;
      string rWFLKfePSQ;
      string qmrAcQajto;
      string fIGrKJzuXE;
      string oiILVzKJjO;
      string HRfCIZWaor;
      string XgDxYjPMBA;
      string fjrNbIdgec;
      string FRAegNcEik;
      string mYFefHfLml;
      string ixIiiXZRaA;
      string upuLmGgXPK;
      string GLdPNHdMgT;
      string bSsstHJRwJ;
      string nKcipxdsrZ;
      if(wwnOTAyyjj == HRfCIZWaor){aIwceXTrUa = true;}
      else if(HRfCIZWaor == wwnOTAyyjj){fuIEGUneUy = true;}
      if(HrwWXYiJOz == XgDxYjPMBA){sNkGYcwCRe = true;}
      else if(XgDxYjPMBA == HrwWXYiJOz){sZzILdnFmw = true;}
      if(fxepbOHasX == fjrNbIdgec){wPbFWwhuZQ = true;}
      else if(fjrNbIdgec == fxepbOHasX){ylBgSaUHPd = true;}
      if(ZaNgEGguQO == FRAegNcEik){ckTGrTVQOV = true;}
      else if(FRAegNcEik == ZaNgEGguQO){fZjiPbDgFu = true;}
      if(WPVtumhyTA == mYFefHfLml){mRwUPZYWJN = true;}
      else if(mYFefHfLml == WPVtumhyTA){NflenMfBUC = true;}
      if(NPaSIzQxlF == ixIiiXZRaA){AbaMcLgpFh = true;}
      else if(ixIiiXZRaA == NPaSIzQxlF){ZtFZIttakf = true;}
      if(rWFLKfePSQ == upuLmGgXPK){oYRDyIsdOF = true;}
      else if(upuLmGgXPK == rWFLKfePSQ){AfOpRSpQsi = true;}
      if(qmrAcQajto == GLdPNHdMgT){GemwreSGpw = true;}
      if(fIGrKJzuXE == bSsstHJRwJ){WLkMQBKHcg = true;}
      if(oiILVzKJjO == nKcipxdsrZ){lfKffNzrWG = true;}
      while(GLdPNHdMgT == qmrAcQajto){ZHzriSzVsG = true;}
      while(bSsstHJRwJ == bSsstHJRwJ){tSlMElUJaV = true;}
      while(nKcipxdsrZ == nKcipxdsrZ){hbuZtgQwMU = true;}
      if(aIwceXTrUa == true){aIwceXTrUa = false;}
      if(sNkGYcwCRe == true){sNkGYcwCRe = false;}
      if(wPbFWwhuZQ == true){wPbFWwhuZQ = false;}
      if(ckTGrTVQOV == true){ckTGrTVQOV = false;}
      if(mRwUPZYWJN == true){mRwUPZYWJN = false;}
      if(AbaMcLgpFh == true){AbaMcLgpFh = false;}
      if(oYRDyIsdOF == true){oYRDyIsdOF = false;}
      if(GemwreSGpw == true){GemwreSGpw = false;}
      if(WLkMQBKHcg == true){WLkMQBKHcg = false;}
      if(lfKffNzrWG == true){lfKffNzrWG = false;}
      if(fuIEGUneUy == true){fuIEGUneUy = false;}
      if(sZzILdnFmw == true){sZzILdnFmw = false;}
      if(ylBgSaUHPd == true){ylBgSaUHPd = false;}
      if(fZjiPbDgFu == true){fZjiPbDgFu = false;}
      if(NflenMfBUC == true){NflenMfBUC = false;}
      if(ZtFZIttakf == true){ZtFZIttakf = false;}
      if(AfOpRSpQsi == true){AfOpRSpQsi = false;}
      if(ZHzriSzVsG == true){ZHzriSzVsG = false;}
      if(tSlMElUJaV == true){tSlMElUJaV = false;}
      if(hbuZtgQwMU == true){hbuZtgQwMU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AODSJPCINK
{ 
  void UVEbgbQRHT()
  { 
      bool GPXyCIQCTc = false;
      bool sqsoDANIDq = false;
      bool GyGpUEzHjB = false;
      bool eeXTJEItaR = false;
      bool tGoYRUimQl = false;
      bool KGuCYHIhdx = false;
      bool IISRxNTZfz = false;
      bool qSgkwAJhYz = false;
      bool VLqypXiVuB = false;
      bool uaQcJlnWaD = false;
      bool BJHQtrYJGY = false;
      bool yaJdbwQTbY = false;
      bool dxedEPBEbJ = false;
      bool MlHUyMDaDx = false;
      bool zZOVDTRmAM = false;
      bool UTuBYDedLe = false;
      bool pUgwLMSneP = false;
      bool rpPdZEiIZj = false;
      bool xODPorqGwu = false;
      bool hYOYHdrRJq = false;
      string BYZJVNoHwH;
      string BsuilaJdKn;
      string OFNDPcuHaB;
      string sFSeqibyYH;
      string euIMNElhmQ;
      string wiEzbwKWsr;
      string RgftOwaQrC;
      string yKEDJTxApL;
      string qMUKEJBTDu;
      string XFFgoxOOyR;
      string dVpkRldApH;
      string yJggBEMVoE;
      string tHMwesEXOL;
      string EhCXgUWisS;
      string eAcuwNYXek;
      string ksYsWWIsGY;
      string gGldCQHIAg;
      string hcbVZtdRAQ;
      string UgsdZLJIBK;
      string LccUlYOzsf;
      if(BYZJVNoHwH == dVpkRldApH){GPXyCIQCTc = true;}
      else if(dVpkRldApH == BYZJVNoHwH){BJHQtrYJGY = true;}
      if(BsuilaJdKn == yJggBEMVoE){sqsoDANIDq = true;}
      else if(yJggBEMVoE == BsuilaJdKn){yaJdbwQTbY = true;}
      if(OFNDPcuHaB == tHMwesEXOL){GyGpUEzHjB = true;}
      else if(tHMwesEXOL == OFNDPcuHaB){dxedEPBEbJ = true;}
      if(sFSeqibyYH == EhCXgUWisS){eeXTJEItaR = true;}
      else if(EhCXgUWisS == sFSeqibyYH){MlHUyMDaDx = true;}
      if(euIMNElhmQ == eAcuwNYXek){tGoYRUimQl = true;}
      else if(eAcuwNYXek == euIMNElhmQ){zZOVDTRmAM = true;}
      if(wiEzbwKWsr == ksYsWWIsGY){KGuCYHIhdx = true;}
      else if(ksYsWWIsGY == wiEzbwKWsr){UTuBYDedLe = true;}
      if(RgftOwaQrC == gGldCQHIAg){IISRxNTZfz = true;}
      else if(gGldCQHIAg == RgftOwaQrC){pUgwLMSneP = true;}
      if(yKEDJTxApL == hcbVZtdRAQ){qSgkwAJhYz = true;}
      if(qMUKEJBTDu == UgsdZLJIBK){VLqypXiVuB = true;}
      if(XFFgoxOOyR == LccUlYOzsf){uaQcJlnWaD = true;}
      while(hcbVZtdRAQ == yKEDJTxApL){rpPdZEiIZj = true;}
      while(UgsdZLJIBK == UgsdZLJIBK){xODPorqGwu = true;}
      while(LccUlYOzsf == LccUlYOzsf){hYOYHdrRJq = true;}
      if(GPXyCIQCTc == true){GPXyCIQCTc = false;}
      if(sqsoDANIDq == true){sqsoDANIDq = false;}
      if(GyGpUEzHjB == true){GyGpUEzHjB = false;}
      if(eeXTJEItaR == true){eeXTJEItaR = false;}
      if(tGoYRUimQl == true){tGoYRUimQl = false;}
      if(KGuCYHIhdx == true){KGuCYHIhdx = false;}
      if(IISRxNTZfz == true){IISRxNTZfz = false;}
      if(qSgkwAJhYz == true){qSgkwAJhYz = false;}
      if(VLqypXiVuB == true){VLqypXiVuB = false;}
      if(uaQcJlnWaD == true){uaQcJlnWaD = false;}
      if(BJHQtrYJGY == true){BJHQtrYJGY = false;}
      if(yaJdbwQTbY == true){yaJdbwQTbY = false;}
      if(dxedEPBEbJ == true){dxedEPBEbJ = false;}
      if(MlHUyMDaDx == true){MlHUyMDaDx = false;}
      if(zZOVDTRmAM == true){zZOVDTRmAM = false;}
      if(UTuBYDedLe == true){UTuBYDedLe = false;}
      if(pUgwLMSneP == true){pUgwLMSneP = false;}
      if(rpPdZEiIZj == true){rpPdZEiIZj = false;}
      if(xODPorqGwu == true){xODPorqGwu = false;}
      if(hYOYHdrRJq == true){hYOYHdrRJq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZVQWDSXMU
{ 
  void jSUxLkLInF()
  { 
      bool zmrLkDKbxI = false;
      bool PRopebIlMR = false;
      bool NMdWitnykK = false;
      bool LQPjYdqmiO = false;
      bool qbMLZdPClc = false;
      bool oIhbsmJUcq = false;
      bool PMqlwzBFRB = false;
      bool kUDxalzSxE = false;
      bool dlMIVDhmqk = false;
      bool TVKqzejaOZ = false;
      bool bKjjqTFjBG = false;
      bool nqWXNdAhQs = false;
      bool ROOfhOKLyw = false;
      bool BYDXbSBbQB = false;
      bool xxkjxczlcU = false;
      bool eCJUINwDCb = false;
      bool JtkFEOmzwu = false;
      bool bXQPwTcdiE = false;
      bool PXhcRzOiPO = false;
      bool VyZorDLffh = false;
      string hzLqahlbLy;
      string nNOdooNuaE;
      string VuZPjDKgkm;
      string fLThAjQpOu;
      string crynDGgaPX;
      string WcsKYlYuGX;
      string WEpXSctgdF;
      string YWfebdxlMc;
      string VjRNQDRIJN;
      string KUiqYXCZUa;
      string MzxJzzxOiu;
      string omidBmmcHO;
      string KkXPuDnoGD;
      string aWQkQWmHNQ;
      string GDZNYWlFpk;
      string jZSGQaagOw;
      string LHHeTRWyMd;
      string zfOpIHKJqX;
      string QizUSBDKUo;
      string uFrQFyuttG;
      if(hzLqahlbLy == MzxJzzxOiu){zmrLkDKbxI = true;}
      else if(MzxJzzxOiu == hzLqahlbLy){bKjjqTFjBG = true;}
      if(nNOdooNuaE == omidBmmcHO){PRopebIlMR = true;}
      else if(omidBmmcHO == nNOdooNuaE){nqWXNdAhQs = true;}
      if(VuZPjDKgkm == KkXPuDnoGD){NMdWitnykK = true;}
      else if(KkXPuDnoGD == VuZPjDKgkm){ROOfhOKLyw = true;}
      if(fLThAjQpOu == aWQkQWmHNQ){LQPjYdqmiO = true;}
      else if(aWQkQWmHNQ == fLThAjQpOu){BYDXbSBbQB = true;}
      if(crynDGgaPX == GDZNYWlFpk){qbMLZdPClc = true;}
      else if(GDZNYWlFpk == crynDGgaPX){xxkjxczlcU = true;}
      if(WcsKYlYuGX == jZSGQaagOw){oIhbsmJUcq = true;}
      else if(jZSGQaagOw == WcsKYlYuGX){eCJUINwDCb = true;}
      if(WEpXSctgdF == LHHeTRWyMd){PMqlwzBFRB = true;}
      else if(LHHeTRWyMd == WEpXSctgdF){JtkFEOmzwu = true;}
      if(YWfebdxlMc == zfOpIHKJqX){kUDxalzSxE = true;}
      if(VjRNQDRIJN == QizUSBDKUo){dlMIVDhmqk = true;}
      if(KUiqYXCZUa == uFrQFyuttG){TVKqzejaOZ = true;}
      while(zfOpIHKJqX == YWfebdxlMc){bXQPwTcdiE = true;}
      while(QizUSBDKUo == QizUSBDKUo){PXhcRzOiPO = true;}
      while(uFrQFyuttG == uFrQFyuttG){VyZorDLffh = true;}
      if(zmrLkDKbxI == true){zmrLkDKbxI = false;}
      if(PRopebIlMR == true){PRopebIlMR = false;}
      if(NMdWitnykK == true){NMdWitnykK = false;}
      if(LQPjYdqmiO == true){LQPjYdqmiO = false;}
      if(qbMLZdPClc == true){qbMLZdPClc = false;}
      if(oIhbsmJUcq == true){oIhbsmJUcq = false;}
      if(PMqlwzBFRB == true){PMqlwzBFRB = false;}
      if(kUDxalzSxE == true){kUDxalzSxE = false;}
      if(dlMIVDhmqk == true){dlMIVDhmqk = false;}
      if(TVKqzejaOZ == true){TVKqzejaOZ = false;}
      if(bKjjqTFjBG == true){bKjjqTFjBG = false;}
      if(nqWXNdAhQs == true){nqWXNdAhQs = false;}
      if(ROOfhOKLyw == true){ROOfhOKLyw = false;}
      if(BYDXbSBbQB == true){BYDXbSBbQB = false;}
      if(xxkjxczlcU == true){xxkjxczlcU = false;}
      if(eCJUINwDCb == true){eCJUINwDCb = false;}
      if(JtkFEOmzwu == true){JtkFEOmzwu = false;}
      if(bXQPwTcdiE == true){bXQPwTcdiE = false;}
      if(PXhcRzOiPO == true){PXhcRzOiPO = false;}
      if(VyZorDLffh == true){VyZorDLffh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLYKHDNONF
{ 
  void YSjBpmSAum()
  { 
      bool samkIjDLzw = false;
      bool NprVclQCMU = false;
      bool BiHZjYmdpQ = false;
      bool ULUnexJbdN = false;
      bool nsPdGluqsb = false;
      bool gOrkxKTNBj = false;
      bool wZUhaCUDqe = false;
      bool bnYyfISdTx = false;
      bool dwjOjFSiqU = false;
      bool dwasROYhCE = false;
      bool RqAOzrptEn = false;
      bool rosEFzoGyV = false;
      bool ikMVAfNefR = false;
      bool jjaPfmwVOq = false;
      bool PYeCcnCVmS = false;
      bool ZRifUfddNT = false;
      bool eKNmEHNdYS = false;
      bool CSrGGJGKsM = false;
      bool drqNqRAutz = false;
      bool JSItMFKqxU = false;
      string XGxStCkDpf;
      string LRfQMMnZWs;
      string cMwSMkjLYe;
      string VKcJrcehLQ;
      string SFbNeAhusR;
      string UEEUgLJdFI;
      string RZeKJBoWYi;
      string hGNGaWkhmL;
      string DnRGKRFIcf;
      string SAbCyraQEd;
      string LKWKiNpxsJ;
      string abqtFcHXAq;
      string uftrPheLHi;
      string wTcJzsRHXw;
      string bIPTFqIhxU;
      string jDPNieQetB;
      string idpKMGyhtL;
      string LAAEOmQamX;
      string YxNmyrEPZU;
      string bmMVNxREGy;
      if(XGxStCkDpf == LKWKiNpxsJ){samkIjDLzw = true;}
      else if(LKWKiNpxsJ == XGxStCkDpf){RqAOzrptEn = true;}
      if(LRfQMMnZWs == abqtFcHXAq){NprVclQCMU = true;}
      else if(abqtFcHXAq == LRfQMMnZWs){rosEFzoGyV = true;}
      if(cMwSMkjLYe == uftrPheLHi){BiHZjYmdpQ = true;}
      else if(uftrPheLHi == cMwSMkjLYe){ikMVAfNefR = true;}
      if(VKcJrcehLQ == wTcJzsRHXw){ULUnexJbdN = true;}
      else if(wTcJzsRHXw == VKcJrcehLQ){jjaPfmwVOq = true;}
      if(SFbNeAhusR == bIPTFqIhxU){nsPdGluqsb = true;}
      else if(bIPTFqIhxU == SFbNeAhusR){PYeCcnCVmS = true;}
      if(UEEUgLJdFI == jDPNieQetB){gOrkxKTNBj = true;}
      else if(jDPNieQetB == UEEUgLJdFI){ZRifUfddNT = true;}
      if(RZeKJBoWYi == idpKMGyhtL){wZUhaCUDqe = true;}
      else if(idpKMGyhtL == RZeKJBoWYi){eKNmEHNdYS = true;}
      if(hGNGaWkhmL == LAAEOmQamX){bnYyfISdTx = true;}
      if(DnRGKRFIcf == YxNmyrEPZU){dwjOjFSiqU = true;}
      if(SAbCyraQEd == bmMVNxREGy){dwasROYhCE = true;}
      while(LAAEOmQamX == hGNGaWkhmL){CSrGGJGKsM = true;}
      while(YxNmyrEPZU == YxNmyrEPZU){drqNqRAutz = true;}
      while(bmMVNxREGy == bmMVNxREGy){JSItMFKqxU = true;}
      if(samkIjDLzw == true){samkIjDLzw = false;}
      if(NprVclQCMU == true){NprVclQCMU = false;}
      if(BiHZjYmdpQ == true){BiHZjYmdpQ = false;}
      if(ULUnexJbdN == true){ULUnexJbdN = false;}
      if(nsPdGluqsb == true){nsPdGluqsb = false;}
      if(gOrkxKTNBj == true){gOrkxKTNBj = false;}
      if(wZUhaCUDqe == true){wZUhaCUDqe = false;}
      if(bnYyfISdTx == true){bnYyfISdTx = false;}
      if(dwjOjFSiqU == true){dwjOjFSiqU = false;}
      if(dwasROYhCE == true){dwasROYhCE = false;}
      if(RqAOzrptEn == true){RqAOzrptEn = false;}
      if(rosEFzoGyV == true){rosEFzoGyV = false;}
      if(ikMVAfNefR == true){ikMVAfNefR = false;}
      if(jjaPfmwVOq == true){jjaPfmwVOq = false;}
      if(PYeCcnCVmS == true){PYeCcnCVmS = false;}
      if(ZRifUfddNT == true){ZRifUfddNT = false;}
      if(eKNmEHNdYS == true){eKNmEHNdYS = false;}
      if(CSrGGJGKsM == true){CSrGGJGKsM = false;}
      if(drqNqRAutz == true){drqNqRAutz = false;}
      if(JSItMFKqxU == true){JSItMFKqxU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVTYWJXHMM
{ 
  void UodCFcsSgG()
  { 
      bool WxAecicKOy = false;
      bool kwKinfzNei = false;
      bool OWeXEnszgL = false;
      bool EqLHoqjIyC = false;
      bool xTlmSxaDxu = false;
      bool XpQKLzScZo = false;
      bool odcCstkCsw = false;
      bool uqPclukrEG = false;
      bool NpClnOaAwo = false;
      bool YHhIMTpjsX = false;
      bool MXJAzgZmYQ = false;
      bool OaXTazapOe = false;
      bool TjGDXnJGQR = false;
      bool EAyfspfCmG = false;
      bool ombeayiNhM = false;
      bool rzVOEcQGbL = false;
      bool XSWGLObqZk = false;
      bool SYDHpgIbcZ = false;
      bool FuYDZFdibQ = false;
      bool YZZbiWPUSL = false;
      string JPlIoSKEHT;
      string pDYgKJdSfD;
      string RCybDkkNGo;
      string IYYJSjhkcp;
      string ZMkEZCbJcJ;
      string UsJuFHQKFE;
      string gxxSKQdONZ;
      string broocEQsBB;
      string IajxTOOdEL;
      string SXfYJcPStJ;
      string YMwChcDURA;
      string qXIDuFNAzu;
      string CzKCHEMQeA;
      string oxzrcwegPq;
      string LsMETuObcD;
      string POSyGYCsud;
      string PmoQKsXQay;
      string ZfkIjImFiM;
      string ojmakaeAkD;
      string tklkaXDuta;
      if(JPlIoSKEHT == YMwChcDURA){WxAecicKOy = true;}
      else if(YMwChcDURA == JPlIoSKEHT){MXJAzgZmYQ = true;}
      if(pDYgKJdSfD == qXIDuFNAzu){kwKinfzNei = true;}
      else if(qXIDuFNAzu == pDYgKJdSfD){OaXTazapOe = true;}
      if(RCybDkkNGo == CzKCHEMQeA){OWeXEnszgL = true;}
      else if(CzKCHEMQeA == RCybDkkNGo){TjGDXnJGQR = true;}
      if(IYYJSjhkcp == oxzrcwegPq){EqLHoqjIyC = true;}
      else if(oxzrcwegPq == IYYJSjhkcp){EAyfspfCmG = true;}
      if(ZMkEZCbJcJ == LsMETuObcD){xTlmSxaDxu = true;}
      else if(LsMETuObcD == ZMkEZCbJcJ){ombeayiNhM = true;}
      if(UsJuFHQKFE == POSyGYCsud){XpQKLzScZo = true;}
      else if(POSyGYCsud == UsJuFHQKFE){rzVOEcQGbL = true;}
      if(gxxSKQdONZ == PmoQKsXQay){odcCstkCsw = true;}
      else if(PmoQKsXQay == gxxSKQdONZ){XSWGLObqZk = true;}
      if(broocEQsBB == ZfkIjImFiM){uqPclukrEG = true;}
      if(IajxTOOdEL == ojmakaeAkD){NpClnOaAwo = true;}
      if(SXfYJcPStJ == tklkaXDuta){YHhIMTpjsX = true;}
      while(ZfkIjImFiM == broocEQsBB){SYDHpgIbcZ = true;}
      while(ojmakaeAkD == ojmakaeAkD){FuYDZFdibQ = true;}
      while(tklkaXDuta == tklkaXDuta){YZZbiWPUSL = true;}
      if(WxAecicKOy == true){WxAecicKOy = false;}
      if(kwKinfzNei == true){kwKinfzNei = false;}
      if(OWeXEnszgL == true){OWeXEnszgL = false;}
      if(EqLHoqjIyC == true){EqLHoqjIyC = false;}
      if(xTlmSxaDxu == true){xTlmSxaDxu = false;}
      if(XpQKLzScZo == true){XpQKLzScZo = false;}
      if(odcCstkCsw == true){odcCstkCsw = false;}
      if(uqPclukrEG == true){uqPclukrEG = false;}
      if(NpClnOaAwo == true){NpClnOaAwo = false;}
      if(YHhIMTpjsX == true){YHhIMTpjsX = false;}
      if(MXJAzgZmYQ == true){MXJAzgZmYQ = false;}
      if(OaXTazapOe == true){OaXTazapOe = false;}
      if(TjGDXnJGQR == true){TjGDXnJGQR = false;}
      if(EAyfspfCmG == true){EAyfspfCmG = false;}
      if(ombeayiNhM == true){ombeayiNhM = false;}
      if(rzVOEcQGbL == true){rzVOEcQGbL = false;}
      if(XSWGLObqZk == true){XSWGLObqZk = false;}
      if(SYDHpgIbcZ == true){SYDHpgIbcZ = false;}
      if(FuYDZFdibQ == true){FuYDZFdibQ = false;}
      if(YZZbiWPUSL == true){YZZbiWPUSL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJDVRYSIJA
{ 
  void BxLcmVThrM()
  { 
      bool tDYFpgMDgZ = false;
      bool HeunPJfIMq = false;
      bool yyOVhHyoFC = false;
      bool mmZJJDEQHr = false;
      bool euYEOlrhzx = false;
      bool KWjnQwnDWi = false;
      bool iWxdlTFldM = false;
      bool EPBUMCYJGw = false;
      bool OPpIrPDkrN = false;
      bool PAsXIHxtSt = false;
      bool gGDmruVPbN = false;
      bool WdwaUSgolW = false;
      bool QTsQxEVcLF = false;
      bool EeqLPILDQw = false;
      bool snJepkDSDp = false;
      bool aIHwdMMlon = false;
      bool YsDWIrmkKM = false;
      bool HdXpccKOaL = false;
      bool ACZVewXuhC = false;
      bool wYNcXAjlVy = false;
      string nCyesmxNNw;
      string fqkdGZVzgA;
      string eqUHAjXzHe;
      string kwaMVRGCPG;
      string kNFYiadLlt;
      string CNRcHxgqeI;
      string PyFiKjQYIo;
      string TSiaOQkuXY;
      string GLMNcXdxEX;
      string kPXHpmIVOz;
      string KEDxaidqNp;
      string MkSFBDkqGm;
      string FSTjDDubjb;
      string HOgYNBIPlt;
      string sliOLzxRFl;
      string CQPasqjTsW;
      string mCGlhxEtrz;
      string uUEMsTjFXE;
      string GdVyZqzGeV;
      string QnWPGqfwfO;
      if(nCyesmxNNw == KEDxaidqNp){tDYFpgMDgZ = true;}
      else if(KEDxaidqNp == nCyesmxNNw){gGDmruVPbN = true;}
      if(fqkdGZVzgA == MkSFBDkqGm){HeunPJfIMq = true;}
      else if(MkSFBDkqGm == fqkdGZVzgA){WdwaUSgolW = true;}
      if(eqUHAjXzHe == FSTjDDubjb){yyOVhHyoFC = true;}
      else if(FSTjDDubjb == eqUHAjXzHe){QTsQxEVcLF = true;}
      if(kwaMVRGCPG == HOgYNBIPlt){mmZJJDEQHr = true;}
      else if(HOgYNBIPlt == kwaMVRGCPG){EeqLPILDQw = true;}
      if(kNFYiadLlt == sliOLzxRFl){euYEOlrhzx = true;}
      else if(sliOLzxRFl == kNFYiadLlt){snJepkDSDp = true;}
      if(CNRcHxgqeI == CQPasqjTsW){KWjnQwnDWi = true;}
      else if(CQPasqjTsW == CNRcHxgqeI){aIHwdMMlon = true;}
      if(PyFiKjQYIo == mCGlhxEtrz){iWxdlTFldM = true;}
      else if(mCGlhxEtrz == PyFiKjQYIo){YsDWIrmkKM = true;}
      if(TSiaOQkuXY == uUEMsTjFXE){EPBUMCYJGw = true;}
      if(GLMNcXdxEX == GdVyZqzGeV){OPpIrPDkrN = true;}
      if(kPXHpmIVOz == QnWPGqfwfO){PAsXIHxtSt = true;}
      while(uUEMsTjFXE == TSiaOQkuXY){HdXpccKOaL = true;}
      while(GdVyZqzGeV == GdVyZqzGeV){ACZVewXuhC = true;}
      while(QnWPGqfwfO == QnWPGqfwfO){wYNcXAjlVy = true;}
      if(tDYFpgMDgZ == true){tDYFpgMDgZ = false;}
      if(HeunPJfIMq == true){HeunPJfIMq = false;}
      if(yyOVhHyoFC == true){yyOVhHyoFC = false;}
      if(mmZJJDEQHr == true){mmZJJDEQHr = false;}
      if(euYEOlrhzx == true){euYEOlrhzx = false;}
      if(KWjnQwnDWi == true){KWjnQwnDWi = false;}
      if(iWxdlTFldM == true){iWxdlTFldM = false;}
      if(EPBUMCYJGw == true){EPBUMCYJGw = false;}
      if(OPpIrPDkrN == true){OPpIrPDkrN = false;}
      if(PAsXIHxtSt == true){PAsXIHxtSt = false;}
      if(gGDmruVPbN == true){gGDmruVPbN = false;}
      if(WdwaUSgolW == true){WdwaUSgolW = false;}
      if(QTsQxEVcLF == true){QTsQxEVcLF = false;}
      if(EeqLPILDQw == true){EeqLPILDQw = false;}
      if(snJepkDSDp == true){snJepkDSDp = false;}
      if(aIHwdMMlon == true){aIHwdMMlon = false;}
      if(YsDWIrmkKM == true){YsDWIrmkKM = false;}
      if(HdXpccKOaL == true){HdXpccKOaL = false;}
      if(ACZVewXuhC == true){ACZVewXuhC = false;}
      if(wYNcXAjlVy == true){wYNcXAjlVy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYYKBJZWMV
{ 
  void pEVqPgYjWd()
  { 
      bool xYKWWeixUI = false;
      bool tNDjkoKnSn = false;
      bool xWGePmrYPz = false;
      bool fFzmqqfEzO = false;
      bool aUJxFyoRLt = false;
      bool BfdHHaSeHi = false;
      bool mKgVboNPss = false;
      bool JGoEMbMJYR = false;
      bool yZNUxzarfP = false;
      bool YAwPbQmnVQ = false;
      bool jYYRkuqZte = false;
      bool NJGpjMwLXb = false;
      bool NVjcUIKYbu = false;
      bool nYnHgYBuiC = false;
      bool IBxACPtGfO = false;
      bool TbPsDOnwxc = false;
      bool kRxypoUyJK = false;
      bool LBbVTMYjaF = false;
      bool NDsNbMJtER = false;
      bool kEyGRpDyJN = false;
      string sxTmelCseU;
      string pmNQiJofsS;
      string jlanKQRuWk;
      string uumNGissJt;
      string CuHTiHySKU;
      string IihwDHVfcO;
      string UGVsYtAzKz;
      string PwVyPodHEC;
      string SykCcMNpJy;
      string MNPuZwYOto;
      string GyIKEMMigO;
      string dOaawVVTQM;
      string fKpMlCfaYT;
      string PPMOuToayQ;
      string zeJtTylozD;
      string ZFxhJuIwXB;
      string flJMzOBMeb;
      string guVAMBBurn;
      string QpaVsKReFz;
      string LsCwjMUwuE;
      if(sxTmelCseU == GyIKEMMigO){xYKWWeixUI = true;}
      else if(GyIKEMMigO == sxTmelCseU){jYYRkuqZte = true;}
      if(pmNQiJofsS == dOaawVVTQM){tNDjkoKnSn = true;}
      else if(dOaawVVTQM == pmNQiJofsS){NJGpjMwLXb = true;}
      if(jlanKQRuWk == fKpMlCfaYT){xWGePmrYPz = true;}
      else if(fKpMlCfaYT == jlanKQRuWk){NVjcUIKYbu = true;}
      if(uumNGissJt == PPMOuToayQ){fFzmqqfEzO = true;}
      else if(PPMOuToayQ == uumNGissJt){nYnHgYBuiC = true;}
      if(CuHTiHySKU == zeJtTylozD){aUJxFyoRLt = true;}
      else if(zeJtTylozD == CuHTiHySKU){IBxACPtGfO = true;}
      if(IihwDHVfcO == ZFxhJuIwXB){BfdHHaSeHi = true;}
      else if(ZFxhJuIwXB == IihwDHVfcO){TbPsDOnwxc = true;}
      if(UGVsYtAzKz == flJMzOBMeb){mKgVboNPss = true;}
      else if(flJMzOBMeb == UGVsYtAzKz){kRxypoUyJK = true;}
      if(PwVyPodHEC == guVAMBBurn){JGoEMbMJYR = true;}
      if(SykCcMNpJy == QpaVsKReFz){yZNUxzarfP = true;}
      if(MNPuZwYOto == LsCwjMUwuE){YAwPbQmnVQ = true;}
      while(guVAMBBurn == PwVyPodHEC){LBbVTMYjaF = true;}
      while(QpaVsKReFz == QpaVsKReFz){NDsNbMJtER = true;}
      while(LsCwjMUwuE == LsCwjMUwuE){kEyGRpDyJN = true;}
      if(xYKWWeixUI == true){xYKWWeixUI = false;}
      if(tNDjkoKnSn == true){tNDjkoKnSn = false;}
      if(xWGePmrYPz == true){xWGePmrYPz = false;}
      if(fFzmqqfEzO == true){fFzmqqfEzO = false;}
      if(aUJxFyoRLt == true){aUJxFyoRLt = false;}
      if(BfdHHaSeHi == true){BfdHHaSeHi = false;}
      if(mKgVboNPss == true){mKgVboNPss = false;}
      if(JGoEMbMJYR == true){JGoEMbMJYR = false;}
      if(yZNUxzarfP == true){yZNUxzarfP = false;}
      if(YAwPbQmnVQ == true){YAwPbQmnVQ = false;}
      if(jYYRkuqZte == true){jYYRkuqZte = false;}
      if(NJGpjMwLXb == true){NJGpjMwLXb = false;}
      if(NVjcUIKYbu == true){NVjcUIKYbu = false;}
      if(nYnHgYBuiC == true){nYnHgYBuiC = false;}
      if(IBxACPtGfO == true){IBxACPtGfO = false;}
      if(TbPsDOnwxc == true){TbPsDOnwxc = false;}
      if(kRxypoUyJK == true){kRxypoUyJK = false;}
      if(LBbVTMYjaF == true){LBbVTMYjaF = false;}
      if(NDsNbMJtER == true){NDsNbMJtER = false;}
      if(kEyGRpDyJN == true){kEyGRpDyJN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBODVEJXML
{ 
  void BoKPmdhBWW()
  { 
      bool wrfEiztsMf = false;
      bool tXmeClqxed = false;
      bool hxniJWryoe = false;
      bool uMkePUscMG = false;
      bool WQCxwVlJZl = false;
      bool cKxrhzEwtL = false;
      bool HwEhjgmHOg = false;
      bool sOjXHQtpmn = false;
      bool kiXCBkPrwQ = false;
      bool QwhBzZMUNP = false;
      bool hetssOZYjR = false;
      bool EOIFZXXBfz = false;
      bool RtKxPwfiYh = false;
      bool DYbXFGneIm = false;
      bool KpHeLCmbaa = false;
      bool BLnOxnUxcw = false;
      bool hqACOflkzT = false;
      bool jsrsoalelN = false;
      bool IDIyfrjNZR = false;
      bool lqBMESpFPf = false;
      string mxBzUFfnWw;
      string abfahoAXrh;
      string NDeSlLGYmy;
      string xAoGCPYRwh;
      string BneBPZeLfF;
      string XpdEGiRiMJ;
      string yGAYyamZXS;
      string PibJgZYdCM;
      string fushZGVjzS;
      string xpFlitmGCo;
      string lFmMooOTWg;
      string KnfzdDNSyq;
      string FCZEVYdpam;
      string lRaNZZHfrj;
      string rBMRIJKFIe;
      string gUHLjjfiqQ;
      string LYsjurMRZD;
      string wgZOyDoHwM;
      string NYgwFQKPdp;
      string sYnbYTIbWQ;
      if(mxBzUFfnWw == lFmMooOTWg){wrfEiztsMf = true;}
      else if(lFmMooOTWg == mxBzUFfnWw){hetssOZYjR = true;}
      if(abfahoAXrh == KnfzdDNSyq){tXmeClqxed = true;}
      else if(KnfzdDNSyq == abfahoAXrh){EOIFZXXBfz = true;}
      if(NDeSlLGYmy == FCZEVYdpam){hxniJWryoe = true;}
      else if(FCZEVYdpam == NDeSlLGYmy){RtKxPwfiYh = true;}
      if(xAoGCPYRwh == lRaNZZHfrj){uMkePUscMG = true;}
      else if(lRaNZZHfrj == xAoGCPYRwh){DYbXFGneIm = true;}
      if(BneBPZeLfF == rBMRIJKFIe){WQCxwVlJZl = true;}
      else if(rBMRIJKFIe == BneBPZeLfF){KpHeLCmbaa = true;}
      if(XpdEGiRiMJ == gUHLjjfiqQ){cKxrhzEwtL = true;}
      else if(gUHLjjfiqQ == XpdEGiRiMJ){BLnOxnUxcw = true;}
      if(yGAYyamZXS == LYsjurMRZD){HwEhjgmHOg = true;}
      else if(LYsjurMRZD == yGAYyamZXS){hqACOflkzT = true;}
      if(PibJgZYdCM == wgZOyDoHwM){sOjXHQtpmn = true;}
      if(fushZGVjzS == NYgwFQKPdp){kiXCBkPrwQ = true;}
      if(xpFlitmGCo == sYnbYTIbWQ){QwhBzZMUNP = true;}
      while(wgZOyDoHwM == PibJgZYdCM){jsrsoalelN = true;}
      while(NYgwFQKPdp == NYgwFQKPdp){IDIyfrjNZR = true;}
      while(sYnbYTIbWQ == sYnbYTIbWQ){lqBMESpFPf = true;}
      if(wrfEiztsMf == true){wrfEiztsMf = false;}
      if(tXmeClqxed == true){tXmeClqxed = false;}
      if(hxniJWryoe == true){hxniJWryoe = false;}
      if(uMkePUscMG == true){uMkePUscMG = false;}
      if(WQCxwVlJZl == true){WQCxwVlJZl = false;}
      if(cKxrhzEwtL == true){cKxrhzEwtL = false;}
      if(HwEhjgmHOg == true){HwEhjgmHOg = false;}
      if(sOjXHQtpmn == true){sOjXHQtpmn = false;}
      if(kiXCBkPrwQ == true){kiXCBkPrwQ = false;}
      if(QwhBzZMUNP == true){QwhBzZMUNP = false;}
      if(hetssOZYjR == true){hetssOZYjR = false;}
      if(EOIFZXXBfz == true){EOIFZXXBfz = false;}
      if(RtKxPwfiYh == true){RtKxPwfiYh = false;}
      if(DYbXFGneIm == true){DYbXFGneIm = false;}
      if(KpHeLCmbaa == true){KpHeLCmbaa = false;}
      if(BLnOxnUxcw == true){BLnOxnUxcw = false;}
      if(hqACOflkzT == true){hqACOflkzT = false;}
      if(jsrsoalelN == true){jsrsoalelN = false;}
      if(IDIyfrjNZR == true){IDIyfrjNZR = false;}
      if(lqBMESpFPf == true){lqBMESpFPf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJTAHNJYAP
{ 
  void HrNRUFHQil()
  { 
      bool xtygmAcGSG = false;
      bool LLEiyDQMxf = false;
      bool GCKmRlnVir = false;
      bool mHLXysEbaK = false;
      bool NqyJRyCDia = false;
      bool kNJkmujLPB = false;
      bool MGWaTDzfkE = false;
      bool yollRODAUS = false;
      bool ikmHHYyZjC = false;
      bool JsLYyGTXpO = false;
      bool zWRdcwaWTX = false;
      bool qipwRaTPSt = false;
      bool FYuhtFcMnL = false;
      bool ufKGTMSIeL = false;
      bool yaGMLaDOGW = false;
      bool lDEwIZajjW = false;
      bool SNhHcKXjcF = false;
      bool ILkHudRiVS = false;
      bool CNGRYqaOxt = false;
      bool kiXHrjsziA = false;
      string WGRgkMbmJI;
      string aqwEJybPfU;
      string OQrnAGdcAw;
      string PnFyXfJUNj;
      string QofbVpCRUk;
      string itRxSFOdgd;
      string hzlMrllxgc;
      string oHBuDZkPSJ;
      string EMHPNUWIfR;
      string QfmiBRCTji;
      string EFjquasVss;
      string UzKWZUqWzW;
      string OdQOMJTStk;
      string WQejFybQTl;
      string bBOmxRUQIf;
      string afTNTanVdl;
      string HZaHVDTaRb;
      string rZDNtNOcRu;
      string nDJNKpxRPd;
      string JGlgeBaGQs;
      if(WGRgkMbmJI == EFjquasVss){xtygmAcGSG = true;}
      else if(EFjquasVss == WGRgkMbmJI){zWRdcwaWTX = true;}
      if(aqwEJybPfU == UzKWZUqWzW){LLEiyDQMxf = true;}
      else if(UzKWZUqWzW == aqwEJybPfU){qipwRaTPSt = true;}
      if(OQrnAGdcAw == OdQOMJTStk){GCKmRlnVir = true;}
      else if(OdQOMJTStk == OQrnAGdcAw){FYuhtFcMnL = true;}
      if(PnFyXfJUNj == WQejFybQTl){mHLXysEbaK = true;}
      else if(WQejFybQTl == PnFyXfJUNj){ufKGTMSIeL = true;}
      if(QofbVpCRUk == bBOmxRUQIf){NqyJRyCDia = true;}
      else if(bBOmxRUQIf == QofbVpCRUk){yaGMLaDOGW = true;}
      if(itRxSFOdgd == afTNTanVdl){kNJkmujLPB = true;}
      else if(afTNTanVdl == itRxSFOdgd){lDEwIZajjW = true;}
      if(hzlMrllxgc == HZaHVDTaRb){MGWaTDzfkE = true;}
      else if(HZaHVDTaRb == hzlMrllxgc){SNhHcKXjcF = true;}
      if(oHBuDZkPSJ == rZDNtNOcRu){yollRODAUS = true;}
      if(EMHPNUWIfR == nDJNKpxRPd){ikmHHYyZjC = true;}
      if(QfmiBRCTji == JGlgeBaGQs){JsLYyGTXpO = true;}
      while(rZDNtNOcRu == oHBuDZkPSJ){ILkHudRiVS = true;}
      while(nDJNKpxRPd == nDJNKpxRPd){CNGRYqaOxt = true;}
      while(JGlgeBaGQs == JGlgeBaGQs){kiXHrjsziA = true;}
      if(xtygmAcGSG == true){xtygmAcGSG = false;}
      if(LLEiyDQMxf == true){LLEiyDQMxf = false;}
      if(GCKmRlnVir == true){GCKmRlnVir = false;}
      if(mHLXysEbaK == true){mHLXysEbaK = false;}
      if(NqyJRyCDia == true){NqyJRyCDia = false;}
      if(kNJkmujLPB == true){kNJkmujLPB = false;}
      if(MGWaTDzfkE == true){MGWaTDzfkE = false;}
      if(yollRODAUS == true){yollRODAUS = false;}
      if(ikmHHYyZjC == true){ikmHHYyZjC = false;}
      if(JsLYyGTXpO == true){JsLYyGTXpO = false;}
      if(zWRdcwaWTX == true){zWRdcwaWTX = false;}
      if(qipwRaTPSt == true){qipwRaTPSt = false;}
      if(FYuhtFcMnL == true){FYuhtFcMnL = false;}
      if(ufKGTMSIeL == true){ufKGTMSIeL = false;}
      if(yaGMLaDOGW == true){yaGMLaDOGW = false;}
      if(lDEwIZajjW == true){lDEwIZajjW = false;}
      if(SNhHcKXjcF == true){SNhHcKXjcF = false;}
      if(ILkHudRiVS == true){ILkHudRiVS = false;}
      if(CNGRYqaOxt == true){CNGRYqaOxt = false;}
      if(kiXHrjsziA == true){kiXHrjsziA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLJRGGVLXX
{ 
  void NbrLlXrsCe()
  { 
      bool QQCKWtiVqI = false;
      bool yYZTecuULP = false;
      bool sKpeUrTHgf = false;
      bool oLInyITHgk = false;
      bool hgpTBYrSiU = false;
      bool egNeIGaXoe = false;
      bool aanKSmQkVV = false;
      bool JnnZgLTVcw = false;
      bool zAYMBIydeq = false;
      bool guRCKHsfAN = false;
      bool IGwNLqsmxx = false;
      bool mFtsfZCaJK = false;
      bool omGdoNVkOZ = false;
      bool RnUPmrDKAK = false;
      bool PKfgEbBXWj = false;
      bool ERVpYUASYy = false;
      bool UHXXezjeFm = false;
      bool WqazudHYZM = false;
      bool LxOeVARepR = false;
      bool rklCoImHBF = false;
      string dBKgiIBAnT;
      string QQTWgFjYNz;
      string itGUxEerfI;
      string bJZGibSgDC;
      string mPKiZbVrNz;
      string GeVjYjuojd;
      string dIUfqHqNmF;
      string lCUKLSiWuU;
      string ilefCxnohy;
      string gdxYYeueqS;
      string kIEHMEJLYF;
      string AXtOtqdoct;
      string SBenYIEwlg;
      string XEebjahWSx;
      string mbQbyJihdg;
      string AFBxzicPiE;
      string zNZqhwrReT;
      string JGWfGqjDpO;
      string ZWREfRDhbA;
      string yRmOyZCYtC;
      if(dBKgiIBAnT == kIEHMEJLYF){QQCKWtiVqI = true;}
      else if(kIEHMEJLYF == dBKgiIBAnT){IGwNLqsmxx = true;}
      if(QQTWgFjYNz == AXtOtqdoct){yYZTecuULP = true;}
      else if(AXtOtqdoct == QQTWgFjYNz){mFtsfZCaJK = true;}
      if(itGUxEerfI == SBenYIEwlg){sKpeUrTHgf = true;}
      else if(SBenYIEwlg == itGUxEerfI){omGdoNVkOZ = true;}
      if(bJZGibSgDC == XEebjahWSx){oLInyITHgk = true;}
      else if(XEebjahWSx == bJZGibSgDC){RnUPmrDKAK = true;}
      if(mPKiZbVrNz == mbQbyJihdg){hgpTBYrSiU = true;}
      else if(mbQbyJihdg == mPKiZbVrNz){PKfgEbBXWj = true;}
      if(GeVjYjuojd == AFBxzicPiE){egNeIGaXoe = true;}
      else if(AFBxzicPiE == GeVjYjuojd){ERVpYUASYy = true;}
      if(dIUfqHqNmF == zNZqhwrReT){aanKSmQkVV = true;}
      else if(zNZqhwrReT == dIUfqHqNmF){UHXXezjeFm = true;}
      if(lCUKLSiWuU == JGWfGqjDpO){JnnZgLTVcw = true;}
      if(ilefCxnohy == ZWREfRDhbA){zAYMBIydeq = true;}
      if(gdxYYeueqS == yRmOyZCYtC){guRCKHsfAN = true;}
      while(JGWfGqjDpO == lCUKLSiWuU){WqazudHYZM = true;}
      while(ZWREfRDhbA == ZWREfRDhbA){LxOeVARepR = true;}
      while(yRmOyZCYtC == yRmOyZCYtC){rklCoImHBF = true;}
      if(QQCKWtiVqI == true){QQCKWtiVqI = false;}
      if(yYZTecuULP == true){yYZTecuULP = false;}
      if(sKpeUrTHgf == true){sKpeUrTHgf = false;}
      if(oLInyITHgk == true){oLInyITHgk = false;}
      if(hgpTBYrSiU == true){hgpTBYrSiU = false;}
      if(egNeIGaXoe == true){egNeIGaXoe = false;}
      if(aanKSmQkVV == true){aanKSmQkVV = false;}
      if(JnnZgLTVcw == true){JnnZgLTVcw = false;}
      if(zAYMBIydeq == true){zAYMBIydeq = false;}
      if(guRCKHsfAN == true){guRCKHsfAN = false;}
      if(IGwNLqsmxx == true){IGwNLqsmxx = false;}
      if(mFtsfZCaJK == true){mFtsfZCaJK = false;}
      if(omGdoNVkOZ == true){omGdoNVkOZ = false;}
      if(RnUPmrDKAK == true){RnUPmrDKAK = false;}
      if(PKfgEbBXWj == true){PKfgEbBXWj = false;}
      if(ERVpYUASYy == true){ERVpYUASYy = false;}
      if(UHXXezjeFm == true){UHXXezjeFm = false;}
      if(WqazudHYZM == true){WqazudHYZM = false;}
      if(LxOeVARepR == true){LxOeVARepR = false;}
      if(rklCoImHBF == true){rklCoImHBF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUOQEBDKRL
{ 
  void hhZxMQySIX()
  { 
      bool TSPGNSTxAw = false;
      bool YkaBimHAqF = false;
      bool bsfKDRyfeH = false;
      bool tXafQflani = false;
      bool saeienEZRn = false;
      bool hkuDgalEDu = false;
      bool TnSsBAJtkD = false;
      bool AgLILBOwfO = false;
      bool NYNpYJcWyp = false;
      bool shWsOEHlhd = false;
      bool dJnOmBYlrf = false;
      bool LpXohuabUq = false;
      bool XmwuJRJSsG = false;
      bool sbOCjEkzDW = false;
      bool jpdRdDKhKT = false;
      bool deRpFqMrEU = false;
      bool rFskljbVEc = false;
      bool JaYxHhIdRG = false;
      bool HbHZbOKXws = false;
      bool qrthedxses = false;
      string PxzDeGtkcY;
      string CwuziwBZPe;
      string CloargGacT;
      string MemXPFWpDB;
      string BXilUhExuj;
      string gbbRMdHYKy;
      string ATHJLXJXjc;
      string ZLWNceCDFJ;
      string bIfrljCUKk;
      string yxeFBhPZZx;
      string XgNRKVFOoh;
      string bDTAWqnOWb;
      string UoMyecfQLu;
      string ObdHlttNhQ;
      string enecJtddiK;
      string sADxchUPlh;
      string ooCsSAZLOb;
      string wZfFxfJjok;
      string yCgBCNXfeD;
      string YeaAapllJJ;
      if(PxzDeGtkcY == XgNRKVFOoh){TSPGNSTxAw = true;}
      else if(XgNRKVFOoh == PxzDeGtkcY){dJnOmBYlrf = true;}
      if(CwuziwBZPe == bDTAWqnOWb){YkaBimHAqF = true;}
      else if(bDTAWqnOWb == CwuziwBZPe){LpXohuabUq = true;}
      if(CloargGacT == UoMyecfQLu){bsfKDRyfeH = true;}
      else if(UoMyecfQLu == CloargGacT){XmwuJRJSsG = true;}
      if(MemXPFWpDB == ObdHlttNhQ){tXafQflani = true;}
      else if(ObdHlttNhQ == MemXPFWpDB){sbOCjEkzDW = true;}
      if(BXilUhExuj == enecJtddiK){saeienEZRn = true;}
      else if(enecJtddiK == BXilUhExuj){jpdRdDKhKT = true;}
      if(gbbRMdHYKy == sADxchUPlh){hkuDgalEDu = true;}
      else if(sADxchUPlh == gbbRMdHYKy){deRpFqMrEU = true;}
      if(ATHJLXJXjc == ooCsSAZLOb){TnSsBAJtkD = true;}
      else if(ooCsSAZLOb == ATHJLXJXjc){rFskljbVEc = true;}
      if(ZLWNceCDFJ == wZfFxfJjok){AgLILBOwfO = true;}
      if(bIfrljCUKk == yCgBCNXfeD){NYNpYJcWyp = true;}
      if(yxeFBhPZZx == YeaAapllJJ){shWsOEHlhd = true;}
      while(wZfFxfJjok == ZLWNceCDFJ){JaYxHhIdRG = true;}
      while(yCgBCNXfeD == yCgBCNXfeD){HbHZbOKXws = true;}
      while(YeaAapllJJ == YeaAapllJJ){qrthedxses = true;}
      if(TSPGNSTxAw == true){TSPGNSTxAw = false;}
      if(YkaBimHAqF == true){YkaBimHAqF = false;}
      if(bsfKDRyfeH == true){bsfKDRyfeH = false;}
      if(tXafQflani == true){tXafQflani = false;}
      if(saeienEZRn == true){saeienEZRn = false;}
      if(hkuDgalEDu == true){hkuDgalEDu = false;}
      if(TnSsBAJtkD == true){TnSsBAJtkD = false;}
      if(AgLILBOwfO == true){AgLILBOwfO = false;}
      if(NYNpYJcWyp == true){NYNpYJcWyp = false;}
      if(shWsOEHlhd == true){shWsOEHlhd = false;}
      if(dJnOmBYlrf == true){dJnOmBYlrf = false;}
      if(LpXohuabUq == true){LpXohuabUq = false;}
      if(XmwuJRJSsG == true){XmwuJRJSsG = false;}
      if(sbOCjEkzDW == true){sbOCjEkzDW = false;}
      if(jpdRdDKhKT == true){jpdRdDKhKT = false;}
      if(deRpFqMrEU == true){deRpFqMrEU = false;}
      if(rFskljbVEc == true){rFskljbVEc = false;}
      if(JaYxHhIdRG == true){JaYxHhIdRG = false;}
      if(HbHZbOKXws == true){HbHZbOKXws = false;}
      if(qrthedxses == true){qrthedxses = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XEOYDIYHMF
{ 
  void LyezRksoKb()
  { 
      bool AAgGDSazzY = false;
      bool pZoWpEoxEG = false;
      bool whwczLntzc = false;
      bool ZTOrioOVXD = false;
      bool PmhSYhtQWH = false;
      bool oycrxSDEHq = false;
      bool dgzVzVLwnB = false;
      bool oSYBqJzdDQ = false;
      bool QWWqnaqVtQ = false;
      bool kKOgYimMSD = false;
      bool VxcUSVYaBn = false;
      bool SZApaGJHhX = false;
      bool eoCXQeErbI = false;
      bool VmKAtStBYR = false;
      bool CPTFyKJYFR = false;
      bool YeduYfuEEm = false;
      bool QfzsSePAuH = false;
      bool LHiPVOUwZF = false;
      bool VfmJipIPaN = false;
      bool WoxkBWQamS = false;
      string rYWMapPPFh;
      string QmcJzMTcAm;
      string uaTWKZdkLy;
      string XDfyeaQZTT;
      string zmqUyFdXgG;
      string PShfeREACA;
      string MdEHJMHedX;
      string usJgmHizYE;
      string wFEEhFVzTM;
      string WQXSGVijKk;
      string yzsIKVIArW;
      string hFbyEHYAYD;
      string qHKRBeVqaR;
      string YynmFwLwsM;
      string wVHxdRoZNz;
      string whLGtpnbHf;
      string ARZZxjQnrH;
      string ucHLHVANmj;
      string owcbVqmhrO;
      string IjnMMdugzt;
      if(rYWMapPPFh == yzsIKVIArW){AAgGDSazzY = true;}
      else if(yzsIKVIArW == rYWMapPPFh){VxcUSVYaBn = true;}
      if(QmcJzMTcAm == hFbyEHYAYD){pZoWpEoxEG = true;}
      else if(hFbyEHYAYD == QmcJzMTcAm){SZApaGJHhX = true;}
      if(uaTWKZdkLy == qHKRBeVqaR){whwczLntzc = true;}
      else if(qHKRBeVqaR == uaTWKZdkLy){eoCXQeErbI = true;}
      if(XDfyeaQZTT == YynmFwLwsM){ZTOrioOVXD = true;}
      else if(YynmFwLwsM == XDfyeaQZTT){VmKAtStBYR = true;}
      if(zmqUyFdXgG == wVHxdRoZNz){PmhSYhtQWH = true;}
      else if(wVHxdRoZNz == zmqUyFdXgG){CPTFyKJYFR = true;}
      if(PShfeREACA == whLGtpnbHf){oycrxSDEHq = true;}
      else if(whLGtpnbHf == PShfeREACA){YeduYfuEEm = true;}
      if(MdEHJMHedX == ARZZxjQnrH){dgzVzVLwnB = true;}
      else if(ARZZxjQnrH == MdEHJMHedX){QfzsSePAuH = true;}
      if(usJgmHizYE == ucHLHVANmj){oSYBqJzdDQ = true;}
      if(wFEEhFVzTM == owcbVqmhrO){QWWqnaqVtQ = true;}
      if(WQXSGVijKk == IjnMMdugzt){kKOgYimMSD = true;}
      while(ucHLHVANmj == usJgmHizYE){LHiPVOUwZF = true;}
      while(owcbVqmhrO == owcbVqmhrO){VfmJipIPaN = true;}
      while(IjnMMdugzt == IjnMMdugzt){WoxkBWQamS = true;}
      if(AAgGDSazzY == true){AAgGDSazzY = false;}
      if(pZoWpEoxEG == true){pZoWpEoxEG = false;}
      if(whwczLntzc == true){whwczLntzc = false;}
      if(ZTOrioOVXD == true){ZTOrioOVXD = false;}
      if(PmhSYhtQWH == true){PmhSYhtQWH = false;}
      if(oycrxSDEHq == true){oycrxSDEHq = false;}
      if(dgzVzVLwnB == true){dgzVzVLwnB = false;}
      if(oSYBqJzdDQ == true){oSYBqJzdDQ = false;}
      if(QWWqnaqVtQ == true){QWWqnaqVtQ = false;}
      if(kKOgYimMSD == true){kKOgYimMSD = false;}
      if(VxcUSVYaBn == true){VxcUSVYaBn = false;}
      if(SZApaGJHhX == true){SZApaGJHhX = false;}
      if(eoCXQeErbI == true){eoCXQeErbI = false;}
      if(VmKAtStBYR == true){VmKAtStBYR = false;}
      if(CPTFyKJYFR == true){CPTFyKJYFR = false;}
      if(YeduYfuEEm == true){YeduYfuEEm = false;}
      if(QfzsSePAuH == true){QfzsSePAuH = false;}
      if(LHiPVOUwZF == true){LHiPVOUwZF = false;}
      if(VfmJipIPaN == true){VfmJipIPaN = false;}
      if(WoxkBWQamS == true){WoxkBWQamS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHDLYRGOUC
{ 
  void NxRSdDYSEf()
  { 
      bool ySbtVzkeZf = false;
      bool raLTxqwTNC = false;
      bool PbgQywzzKg = false;
      bool zNzbbdTKXF = false;
      bool gdeyMxazBc = false;
      bool NPdRzVlLuY = false;
      bool AlTsfebiqT = false;
      bool WkuIUkwhDB = false;
      bool VAxhSjigcG = false;
      bool qIOzEuJlRh = false;
      bool UrHhFbUVxN = false;
      bool YDHtDAnlZw = false;
      bool uuFkbNWuDZ = false;
      bool bKQUgdrPcp = false;
      bool PNjPgnBUwE = false;
      bool HWMUmYlVGq = false;
      bool FYRWkOmlNZ = false;
      bool HYJifhLoEn = false;
      bool MCzzSEyuhH = false;
      bool qVIkkquMeR = false;
      string iBbnBAUwLV;
      string rmaljsfxAe;
      string FfBeypGSsm;
      string iAUIfnhNTW;
      string DdSHmgUlzf;
      string zApRyCAxpL;
      string sBDYlqSRGw;
      string LRdcabMsqQ;
      string VUSMnhKCKc;
      string njXHdCZtVw;
      string NCfDUgWNqV;
      string pGGYpYipkD;
      string fQHcIatVzY;
      string BRXtDSoOrG;
      string LxKnlgdyQF;
      string TiJRPxtCus;
      string mBNSTXhLVW;
      string iTydqiFSqa;
      string wwEtFRIFeF;
      string YlTyTKirTO;
      if(iBbnBAUwLV == NCfDUgWNqV){ySbtVzkeZf = true;}
      else if(NCfDUgWNqV == iBbnBAUwLV){UrHhFbUVxN = true;}
      if(rmaljsfxAe == pGGYpYipkD){raLTxqwTNC = true;}
      else if(pGGYpYipkD == rmaljsfxAe){YDHtDAnlZw = true;}
      if(FfBeypGSsm == fQHcIatVzY){PbgQywzzKg = true;}
      else if(fQHcIatVzY == FfBeypGSsm){uuFkbNWuDZ = true;}
      if(iAUIfnhNTW == BRXtDSoOrG){zNzbbdTKXF = true;}
      else if(BRXtDSoOrG == iAUIfnhNTW){bKQUgdrPcp = true;}
      if(DdSHmgUlzf == LxKnlgdyQF){gdeyMxazBc = true;}
      else if(LxKnlgdyQF == DdSHmgUlzf){PNjPgnBUwE = true;}
      if(zApRyCAxpL == TiJRPxtCus){NPdRzVlLuY = true;}
      else if(TiJRPxtCus == zApRyCAxpL){HWMUmYlVGq = true;}
      if(sBDYlqSRGw == mBNSTXhLVW){AlTsfebiqT = true;}
      else if(mBNSTXhLVW == sBDYlqSRGw){FYRWkOmlNZ = true;}
      if(LRdcabMsqQ == iTydqiFSqa){WkuIUkwhDB = true;}
      if(VUSMnhKCKc == wwEtFRIFeF){VAxhSjigcG = true;}
      if(njXHdCZtVw == YlTyTKirTO){qIOzEuJlRh = true;}
      while(iTydqiFSqa == LRdcabMsqQ){HYJifhLoEn = true;}
      while(wwEtFRIFeF == wwEtFRIFeF){MCzzSEyuhH = true;}
      while(YlTyTKirTO == YlTyTKirTO){qVIkkquMeR = true;}
      if(ySbtVzkeZf == true){ySbtVzkeZf = false;}
      if(raLTxqwTNC == true){raLTxqwTNC = false;}
      if(PbgQywzzKg == true){PbgQywzzKg = false;}
      if(zNzbbdTKXF == true){zNzbbdTKXF = false;}
      if(gdeyMxazBc == true){gdeyMxazBc = false;}
      if(NPdRzVlLuY == true){NPdRzVlLuY = false;}
      if(AlTsfebiqT == true){AlTsfebiqT = false;}
      if(WkuIUkwhDB == true){WkuIUkwhDB = false;}
      if(VAxhSjigcG == true){VAxhSjigcG = false;}
      if(qIOzEuJlRh == true){qIOzEuJlRh = false;}
      if(UrHhFbUVxN == true){UrHhFbUVxN = false;}
      if(YDHtDAnlZw == true){YDHtDAnlZw = false;}
      if(uuFkbNWuDZ == true){uuFkbNWuDZ = false;}
      if(bKQUgdrPcp == true){bKQUgdrPcp = false;}
      if(PNjPgnBUwE == true){PNjPgnBUwE = false;}
      if(HWMUmYlVGq == true){HWMUmYlVGq = false;}
      if(FYRWkOmlNZ == true){FYRWkOmlNZ = false;}
      if(HYJifhLoEn == true){HYJifhLoEn = false;}
      if(MCzzSEyuhH == true){MCzzSEyuhH = false;}
      if(qVIkkquMeR == true){qVIkkquMeR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZGYTQFLRJ
{ 
  void lRnJqmhugy()
  { 
      bool yStGRUxXcd = false;
      bool goKaQsZqhD = false;
      bool tpCmVCdnaN = false;
      bool wQLzOXTJgQ = false;
      bool WNrmTIoOSQ = false;
      bool gOrafIQGjP = false;
      bool pJxPgQcKLr = false;
      bool ZPKQggyOSN = false;
      bool NPVKfgYkTG = false;
      bool HMZRaNQbFD = false;
      bool edCZqQDatz = false;
      bool KBnWCanljA = false;
      bool qrpFkMprpS = false;
      bool PVJOhiMwTO = false;
      bool cyqUwFYCPA = false;
      bool ZdrFMmnxod = false;
      bool aLkajnrYoS = false;
      bool NrSUWsAVJe = false;
      bool mmcoskdECt = false;
      bool uPGonRMPkH = false;
      string nwCPAdwczZ;
      string pPVrFUtzOi;
      string yAmLQuoKnX;
      string ekrIYwrygr;
      string XXpHjgolUN;
      string AAeFonIqzF;
      string nlobtEXNSJ;
      string cuSVLZKebj;
      string GDoaWdFmSk;
      string mAyaEkiOMe;
      string IaSLjEhIsP;
      string ccPPzkxNEP;
      string zjthWbxqRZ;
      string pwRwaejdpS;
      string wxsDHJkiaS;
      string nUJxfYfknH;
      string HppTYgKSoU;
      string BTWlTCqqaN;
      string qNQzkUlUQB;
      string yzoiKGGZea;
      if(nwCPAdwczZ == IaSLjEhIsP){yStGRUxXcd = true;}
      else if(IaSLjEhIsP == nwCPAdwczZ){edCZqQDatz = true;}
      if(pPVrFUtzOi == ccPPzkxNEP){goKaQsZqhD = true;}
      else if(ccPPzkxNEP == pPVrFUtzOi){KBnWCanljA = true;}
      if(yAmLQuoKnX == zjthWbxqRZ){tpCmVCdnaN = true;}
      else if(zjthWbxqRZ == yAmLQuoKnX){qrpFkMprpS = true;}
      if(ekrIYwrygr == pwRwaejdpS){wQLzOXTJgQ = true;}
      else if(pwRwaejdpS == ekrIYwrygr){PVJOhiMwTO = true;}
      if(XXpHjgolUN == wxsDHJkiaS){WNrmTIoOSQ = true;}
      else if(wxsDHJkiaS == XXpHjgolUN){cyqUwFYCPA = true;}
      if(AAeFonIqzF == nUJxfYfknH){gOrafIQGjP = true;}
      else if(nUJxfYfknH == AAeFonIqzF){ZdrFMmnxod = true;}
      if(nlobtEXNSJ == HppTYgKSoU){pJxPgQcKLr = true;}
      else if(HppTYgKSoU == nlobtEXNSJ){aLkajnrYoS = true;}
      if(cuSVLZKebj == BTWlTCqqaN){ZPKQggyOSN = true;}
      if(GDoaWdFmSk == qNQzkUlUQB){NPVKfgYkTG = true;}
      if(mAyaEkiOMe == yzoiKGGZea){HMZRaNQbFD = true;}
      while(BTWlTCqqaN == cuSVLZKebj){NrSUWsAVJe = true;}
      while(qNQzkUlUQB == qNQzkUlUQB){mmcoskdECt = true;}
      while(yzoiKGGZea == yzoiKGGZea){uPGonRMPkH = true;}
      if(yStGRUxXcd == true){yStGRUxXcd = false;}
      if(goKaQsZqhD == true){goKaQsZqhD = false;}
      if(tpCmVCdnaN == true){tpCmVCdnaN = false;}
      if(wQLzOXTJgQ == true){wQLzOXTJgQ = false;}
      if(WNrmTIoOSQ == true){WNrmTIoOSQ = false;}
      if(gOrafIQGjP == true){gOrafIQGjP = false;}
      if(pJxPgQcKLr == true){pJxPgQcKLr = false;}
      if(ZPKQggyOSN == true){ZPKQggyOSN = false;}
      if(NPVKfgYkTG == true){NPVKfgYkTG = false;}
      if(HMZRaNQbFD == true){HMZRaNQbFD = false;}
      if(edCZqQDatz == true){edCZqQDatz = false;}
      if(KBnWCanljA == true){KBnWCanljA = false;}
      if(qrpFkMprpS == true){qrpFkMprpS = false;}
      if(PVJOhiMwTO == true){PVJOhiMwTO = false;}
      if(cyqUwFYCPA == true){cyqUwFYCPA = false;}
      if(ZdrFMmnxod == true){ZdrFMmnxod = false;}
      if(aLkajnrYoS == true){aLkajnrYoS = false;}
      if(NrSUWsAVJe == true){NrSUWsAVJe = false;}
      if(mmcoskdECt == true){mmcoskdECt = false;}
      if(uPGonRMPkH == true){uPGonRMPkH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTXHEGISKK
{ 
  void azJBTOCdKx()
  { 
      bool KxtcynsLAn = false;
      bool TfCPflXRiK = false;
      bool WDRsRlMUDz = false;
      bool rLgdiPbdjy = false;
      bool rrrCsndTIS = false;
      bool YnFUGHeAKM = false;
      bool bYIBwHzXfP = false;
      bool JthkSeLPzd = false;
      bool HrLkaEGMWa = false;
      bool jaSWVTjpGl = false;
      bool oFnrIdGUCb = false;
      bool wPAgFiMWaq = false;
      bool AlBEfhaKOz = false;
      bool uUINnBETbw = false;
      bool ykKueUalRm = false;
      bool GMPOkCEiMa = false;
      bool DuFDfbGmrD = false;
      bool estdsObFZL = false;
      bool HnrbrhFtcl = false;
      bool wUGBsCfHOC = false;
      string ZimOdWHNub;
      string sJZhjTCHSS;
      string QNkbLeBMZi;
      string XgsaQpEqRt;
      string ViBZFwgnGc;
      string qrYpQLxKCz;
      string UunMDMPyRt;
      string OLoYxhMLWO;
      string xMFwreHDKE;
      string rtnSYZtnVr;
      string ghWLNeCAri;
      string zkmnCIprUY;
      string FLnMBUWWzW;
      string mXpdhOpshM;
      string bGKaFGGAPQ;
      string jCTxmUtJKs;
      string IeAVuauJGm;
      string RwJHwyBNHt;
      string NWGilkErqM;
      string UfioExFofd;
      if(ZimOdWHNub == ghWLNeCAri){KxtcynsLAn = true;}
      else if(ghWLNeCAri == ZimOdWHNub){oFnrIdGUCb = true;}
      if(sJZhjTCHSS == zkmnCIprUY){TfCPflXRiK = true;}
      else if(zkmnCIprUY == sJZhjTCHSS){wPAgFiMWaq = true;}
      if(QNkbLeBMZi == FLnMBUWWzW){WDRsRlMUDz = true;}
      else if(FLnMBUWWzW == QNkbLeBMZi){AlBEfhaKOz = true;}
      if(XgsaQpEqRt == mXpdhOpshM){rLgdiPbdjy = true;}
      else if(mXpdhOpshM == XgsaQpEqRt){uUINnBETbw = true;}
      if(ViBZFwgnGc == bGKaFGGAPQ){rrrCsndTIS = true;}
      else if(bGKaFGGAPQ == ViBZFwgnGc){ykKueUalRm = true;}
      if(qrYpQLxKCz == jCTxmUtJKs){YnFUGHeAKM = true;}
      else if(jCTxmUtJKs == qrYpQLxKCz){GMPOkCEiMa = true;}
      if(UunMDMPyRt == IeAVuauJGm){bYIBwHzXfP = true;}
      else if(IeAVuauJGm == UunMDMPyRt){DuFDfbGmrD = true;}
      if(OLoYxhMLWO == RwJHwyBNHt){JthkSeLPzd = true;}
      if(xMFwreHDKE == NWGilkErqM){HrLkaEGMWa = true;}
      if(rtnSYZtnVr == UfioExFofd){jaSWVTjpGl = true;}
      while(RwJHwyBNHt == OLoYxhMLWO){estdsObFZL = true;}
      while(NWGilkErqM == NWGilkErqM){HnrbrhFtcl = true;}
      while(UfioExFofd == UfioExFofd){wUGBsCfHOC = true;}
      if(KxtcynsLAn == true){KxtcynsLAn = false;}
      if(TfCPflXRiK == true){TfCPflXRiK = false;}
      if(WDRsRlMUDz == true){WDRsRlMUDz = false;}
      if(rLgdiPbdjy == true){rLgdiPbdjy = false;}
      if(rrrCsndTIS == true){rrrCsndTIS = false;}
      if(YnFUGHeAKM == true){YnFUGHeAKM = false;}
      if(bYIBwHzXfP == true){bYIBwHzXfP = false;}
      if(JthkSeLPzd == true){JthkSeLPzd = false;}
      if(HrLkaEGMWa == true){HrLkaEGMWa = false;}
      if(jaSWVTjpGl == true){jaSWVTjpGl = false;}
      if(oFnrIdGUCb == true){oFnrIdGUCb = false;}
      if(wPAgFiMWaq == true){wPAgFiMWaq = false;}
      if(AlBEfhaKOz == true){AlBEfhaKOz = false;}
      if(uUINnBETbw == true){uUINnBETbw = false;}
      if(ykKueUalRm == true){ykKueUalRm = false;}
      if(GMPOkCEiMa == true){GMPOkCEiMa = false;}
      if(DuFDfbGmrD == true){DuFDfbGmrD = false;}
      if(estdsObFZL == true){estdsObFZL = false;}
      if(HnrbrhFtcl == true){HnrbrhFtcl = false;}
      if(wUGBsCfHOC == true){wUGBsCfHOC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQEKTFCLAO
{ 
  void itkywMRToU()
  { 
      bool VhRalPCKcS = false;
      bool iKKFGdKBKn = false;
      bool WFcLUEasns = false;
      bool uNIAPKLOax = false;
      bool rZxxdZHPtJ = false;
      bool mwKouPEGGh = false;
      bool nJWiXVBKpw = false;
      bool SwZNuxIfhu = false;
      bool wKydFyCTEz = false;
      bool FFIsIhDNYH = false;
      bool XxYyqqWxsy = false;
      bool HYYLkcLrcZ = false;
      bool SgFppNmfEM = false;
      bool ttGZWzlAmO = false;
      bool bFaGrgfwHe = false;
      bool WKkzopriHd = false;
      bool DprfDMRynl = false;
      bool qLFOxMGyxJ = false;
      bool gqXYpiJHkg = false;
      bool GCrJKkMtCe = false;
      string QYcUPhkSRz;
      string mtiegcrROL;
      string sxmNnDulDS;
      string iiczbPLbcP;
      string SILdUMcauj;
      string sLknMTkOfL;
      string mzPyPDRjCQ;
      string QPnzrklJsa;
      string ZTpTZXyolI;
      string dxuRbTsMNQ;
      string usXdScXlua;
      string gbVEkSIuYr;
      string FcxtmTUVWX;
      string rYubfgwMAw;
      string AMsLaBapfI;
      string LxnULSwdqz;
      string IBOXiIfsYE;
      string WwtcrrikSk;
      string rdpNMukZQM;
      string jSUBnyxVcS;
      if(QYcUPhkSRz == usXdScXlua){VhRalPCKcS = true;}
      else if(usXdScXlua == QYcUPhkSRz){XxYyqqWxsy = true;}
      if(mtiegcrROL == gbVEkSIuYr){iKKFGdKBKn = true;}
      else if(gbVEkSIuYr == mtiegcrROL){HYYLkcLrcZ = true;}
      if(sxmNnDulDS == FcxtmTUVWX){WFcLUEasns = true;}
      else if(FcxtmTUVWX == sxmNnDulDS){SgFppNmfEM = true;}
      if(iiczbPLbcP == rYubfgwMAw){uNIAPKLOax = true;}
      else if(rYubfgwMAw == iiczbPLbcP){ttGZWzlAmO = true;}
      if(SILdUMcauj == AMsLaBapfI){rZxxdZHPtJ = true;}
      else if(AMsLaBapfI == SILdUMcauj){bFaGrgfwHe = true;}
      if(sLknMTkOfL == LxnULSwdqz){mwKouPEGGh = true;}
      else if(LxnULSwdqz == sLknMTkOfL){WKkzopriHd = true;}
      if(mzPyPDRjCQ == IBOXiIfsYE){nJWiXVBKpw = true;}
      else if(IBOXiIfsYE == mzPyPDRjCQ){DprfDMRynl = true;}
      if(QPnzrklJsa == WwtcrrikSk){SwZNuxIfhu = true;}
      if(ZTpTZXyolI == rdpNMukZQM){wKydFyCTEz = true;}
      if(dxuRbTsMNQ == jSUBnyxVcS){FFIsIhDNYH = true;}
      while(WwtcrrikSk == QPnzrklJsa){qLFOxMGyxJ = true;}
      while(rdpNMukZQM == rdpNMukZQM){gqXYpiJHkg = true;}
      while(jSUBnyxVcS == jSUBnyxVcS){GCrJKkMtCe = true;}
      if(VhRalPCKcS == true){VhRalPCKcS = false;}
      if(iKKFGdKBKn == true){iKKFGdKBKn = false;}
      if(WFcLUEasns == true){WFcLUEasns = false;}
      if(uNIAPKLOax == true){uNIAPKLOax = false;}
      if(rZxxdZHPtJ == true){rZxxdZHPtJ = false;}
      if(mwKouPEGGh == true){mwKouPEGGh = false;}
      if(nJWiXVBKpw == true){nJWiXVBKpw = false;}
      if(SwZNuxIfhu == true){SwZNuxIfhu = false;}
      if(wKydFyCTEz == true){wKydFyCTEz = false;}
      if(FFIsIhDNYH == true){FFIsIhDNYH = false;}
      if(XxYyqqWxsy == true){XxYyqqWxsy = false;}
      if(HYYLkcLrcZ == true){HYYLkcLrcZ = false;}
      if(SgFppNmfEM == true){SgFppNmfEM = false;}
      if(ttGZWzlAmO == true){ttGZWzlAmO = false;}
      if(bFaGrgfwHe == true){bFaGrgfwHe = false;}
      if(WKkzopriHd == true){WKkzopriHd = false;}
      if(DprfDMRynl == true){DprfDMRynl = false;}
      if(qLFOxMGyxJ == true){qLFOxMGyxJ = false;}
      if(gqXYpiJHkg == true){gqXYpiJHkg = false;}
      if(GCrJKkMtCe == true){GCrJKkMtCe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CIQJZSVBZG
{ 
  void dxChmFuQrG()
  { 
      bool LTUstiAImZ = false;
      bool cQuzMsoNDm = false;
      bool nnRMlswgdC = false;
      bool qCSKsuOGyu = false;
      bool BmrSjCXgGg = false;
      bool faorMXBHHB = false;
      bool mSdjiaxkFR = false;
      bool dhOHkAwzbi = false;
      bool UOaxVPMaxV = false;
      bool sHyxHiIHiJ = false;
      bool EmanDxMgGM = false;
      bool aCeXfXrgOT = false;
      bool NWmjYViQAC = false;
      bool qnPSehmltX = false;
      bool CeTktqcaQi = false;
      bool pbsPuhzqPg = false;
      bool NugEVmlMsy = false;
      bool kFlpQiDCoh = false;
      bool sIAQLOuzWx = false;
      bool hwVNJHxPOH = false;
      string nAXfbeleTH;
      string cKjeHGgZIl;
      string NPIkqZLtRC;
      string ZBpFDgZunN;
      string TLlZHMKfQB;
      string rZAqtXqloC;
      string TrNQhbUdba;
      string fkltSBdhdd;
      string OfcQJzAzLe;
      string omGltayUrf;
      string rgEpUHnFYr;
      string tJILmnOwHh;
      string aURwksezzq;
      string DJoykhaluC;
      string KuZTkfduzG;
      string MBNKFXOHFb;
      string coGhnjTKZF;
      string McBEXetyLF;
      string OjAsdBwerN;
      string STgTZUnreA;
      if(nAXfbeleTH == rgEpUHnFYr){LTUstiAImZ = true;}
      else if(rgEpUHnFYr == nAXfbeleTH){EmanDxMgGM = true;}
      if(cKjeHGgZIl == tJILmnOwHh){cQuzMsoNDm = true;}
      else if(tJILmnOwHh == cKjeHGgZIl){aCeXfXrgOT = true;}
      if(NPIkqZLtRC == aURwksezzq){nnRMlswgdC = true;}
      else if(aURwksezzq == NPIkqZLtRC){NWmjYViQAC = true;}
      if(ZBpFDgZunN == DJoykhaluC){qCSKsuOGyu = true;}
      else if(DJoykhaluC == ZBpFDgZunN){qnPSehmltX = true;}
      if(TLlZHMKfQB == KuZTkfduzG){BmrSjCXgGg = true;}
      else if(KuZTkfduzG == TLlZHMKfQB){CeTktqcaQi = true;}
      if(rZAqtXqloC == MBNKFXOHFb){faorMXBHHB = true;}
      else if(MBNKFXOHFb == rZAqtXqloC){pbsPuhzqPg = true;}
      if(TrNQhbUdba == coGhnjTKZF){mSdjiaxkFR = true;}
      else if(coGhnjTKZF == TrNQhbUdba){NugEVmlMsy = true;}
      if(fkltSBdhdd == McBEXetyLF){dhOHkAwzbi = true;}
      if(OfcQJzAzLe == OjAsdBwerN){UOaxVPMaxV = true;}
      if(omGltayUrf == STgTZUnreA){sHyxHiIHiJ = true;}
      while(McBEXetyLF == fkltSBdhdd){kFlpQiDCoh = true;}
      while(OjAsdBwerN == OjAsdBwerN){sIAQLOuzWx = true;}
      while(STgTZUnreA == STgTZUnreA){hwVNJHxPOH = true;}
      if(LTUstiAImZ == true){LTUstiAImZ = false;}
      if(cQuzMsoNDm == true){cQuzMsoNDm = false;}
      if(nnRMlswgdC == true){nnRMlswgdC = false;}
      if(qCSKsuOGyu == true){qCSKsuOGyu = false;}
      if(BmrSjCXgGg == true){BmrSjCXgGg = false;}
      if(faorMXBHHB == true){faorMXBHHB = false;}
      if(mSdjiaxkFR == true){mSdjiaxkFR = false;}
      if(dhOHkAwzbi == true){dhOHkAwzbi = false;}
      if(UOaxVPMaxV == true){UOaxVPMaxV = false;}
      if(sHyxHiIHiJ == true){sHyxHiIHiJ = false;}
      if(EmanDxMgGM == true){EmanDxMgGM = false;}
      if(aCeXfXrgOT == true){aCeXfXrgOT = false;}
      if(NWmjYViQAC == true){NWmjYViQAC = false;}
      if(qnPSehmltX == true){qnPSehmltX = false;}
      if(CeTktqcaQi == true){CeTktqcaQi = false;}
      if(pbsPuhzqPg == true){pbsPuhzqPg = false;}
      if(NugEVmlMsy == true){NugEVmlMsy = false;}
      if(kFlpQiDCoh == true){kFlpQiDCoh = false;}
      if(sIAQLOuzWx == true){sIAQLOuzWx = false;}
      if(hwVNJHxPOH == true){hwVNJHxPOH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFHHSSTCJH
{ 
  void qiFkOQpjNR()
  { 
      bool zpNthJUpOA = false;
      bool KtWrCdNYtz = false;
      bool OsNfLXqsCu = false;
      bool eSpixcLUIO = false;
      bool BpDEwkfkXe = false;
      bool sHxmoGbhiJ = false;
      bool SamSVrEmuY = false;
      bool SrPeyXoJiZ = false;
      bool rFVXCXUCtp = false;
      bool BdlzwZDjiE = false;
      bool fspyLAqRoR = false;
      bool QSyIRMFOQy = false;
      bool WBsEXnGQiX = false;
      bool UFaesyOWLB = false;
      bool fDNbYifcgj = false;
      bool UoSjheAkZX = false;
      bool tZiQxLrTOS = false;
      bool xiCORTnQfo = false;
      bool IcizDflpwO = false;
      bool ydwnHFTweM = false;
      string qZrsPVgaWZ;
      string pVRgDnmXwp;
      string fCqVKEWcPH;
      string YYUnRnQypx;
      string VPqEkqoMMU;
      string RKNoxnhVhK;
      string zDKPARAdPO;
      string WngyTPKmkS;
      string PKQtpNKepc;
      string GtPfyREbDS;
      string pLwxycdOUg;
      string dukPtomPZl;
      string GUmlIbYAAC;
      string KiiRcDNSwM;
      string juKJzLJAkJ;
      string dnCQMVXKoV;
      string DcOSVuLTmq;
      string bUTMCLKdmx;
      string SYPpXVfRFH;
      string fDdaJGfrmE;
      if(qZrsPVgaWZ == pLwxycdOUg){zpNthJUpOA = true;}
      else if(pLwxycdOUg == qZrsPVgaWZ){fspyLAqRoR = true;}
      if(pVRgDnmXwp == dukPtomPZl){KtWrCdNYtz = true;}
      else if(dukPtomPZl == pVRgDnmXwp){QSyIRMFOQy = true;}
      if(fCqVKEWcPH == GUmlIbYAAC){OsNfLXqsCu = true;}
      else if(GUmlIbYAAC == fCqVKEWcPH){WBsEXnGQiX = true;}
      if(YYUnRnQypx == KiiRcDNSwM){eSpixcLUIO = true;}
      else if(KiiRcDNSwM == YYUnRnQypx){UFaesyOWLB = true;}
      if(VPqEkqoMMU == juKJzLJAkJ){BpDEwkfkXe = true;}
      else if(juKJzLJAkJ == VPqEkqoMMU){fDNbYifcgj = true;}
      if(RKNoxnhVhK == dnCQMVXKoV){sHxmoGbhiJ = true;}
      else if(dnCQMVXKoV == RKNoxnhVhK){UoSjheAkZX = true;}
      if(zDKPARAdPO == DcOSVuLTmq){SamSVrEmuY = true;}
      else if(DcOSVuLTmq == zDKPARAdPO){tZiQxLrTOS = true;}
      if(WngyTPKmkS == bUTMCLKdmx){SrPeyXoJiZ = true;}
      if(PKQtpNKepc == SYPpXVfRFH){rFVXCXUCtp = true;}
      if(GtPfyREbDS == fDdaJGfrmE){BdlzwZDjiE = true;}
      while(bUTMCLKdmx == WngyTPKmkS){xiCORTnQfo = true;}
      while(SYPpXVfRFH == SYPpXVfRFH){IcizDflpwO = true;}
      while(fDdaJGfrmE == fDdaJGfrmE){ydwnHFTweM = true;}
      if(zpNthJUpOA == true){zpNthJUpOA = false;}
      if(KtWrCdNYtz == true){KtWrCdNYtz = false;}
      if(OsNfLXqsCu == true){OsNfLXqsCu = false;}
      if(eSpixcLUIO == true){eSpixcLUIO = false;}
      if(BpDEwkfkXe == true){BpDEwkfkXe = false;}
      if(sHxmoGbhiJ == true){sHxmoGbhiJ = false;}
      if(SamSVrEmuY == true){SamSVrEmuY = false;}
      if(SrPeyXoJiZ == true){SrPeyXoJiZ = false;}
      if(rFVXCXUCtp == true){rFVXCXUCtp = false;}
      if(BdlzwZDjiE == true){BdlzwZDjiE = false;}
      if(fspyLAqRoR == true){fspyLAqRoR = false;}
      if(QSyIRMFOQy == true){QSyIRMFOQy = false;}
      if(WBsEXnGQiX == true){WBsEXnGQiX = false;}
      if(UFaesyOWLB == true){UFaesyOWLB = false;}
      if(fDNbYifcgj == true){fDNbYifcgj = false;}
      if(UoSjheAkZX == true){UoSjheAkZX = false;}
      if(tZiQxLrTOS == true){tZiQxLrTOS = false;}
      if(xiCORTnQfo == true){xiCORTnQfo = false;}
      if(IcizDflpwO == true){IcizDflpwO = false;}
      if(ydwnHFTweM == true){ydwnHFTweM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHIHNABDLJ
{ 
  void QiwiXZBXRD()
  { 
      bool grMHzRfaod = false;
      bool WSzxVQJstV = false;
      bool IQrzDpIqms = false;
      bool dWWOSCFeuY = false;
      bool KLgwaCdGiR = false;
      bool lbyTtPANDI = false;
      bool JnnwAzujdS = false;
      bool LdxVLxiwYB = false;
      bool MCIUGCXCTC = false;
      bool CramPVXkua = false;
      bool GscPFHebIx = false;
      bool gDnCwGfSoy = false;
      bool brPaPSCJGp = false;
      bool ZxAytSZrPz = false;
      bool XutWVzEYqI = false;
      bool oFwxyOcBAm = false;
      bool EUVSXiCoHc = false;
      bool gnDoZfxsFQ = false;
      bool OdSyATBCzf = false;
      bool pXrcuDZbzl = false;
      string UJHjRsoNkm;
      string XtOQfhMFNm;
      string IYLujsDJEP;
      string xEKQXEtqfU;
      string XAGAFRtaqL;
      string iosWkwxMzY;
      string oeJVoSixsa;
      string nUZrOHSKpS;
      string ybRsgIKmfb;
      string GhqGesqkKl;
      string hxhQXNPBHc;
      string cmWgZMNQng;
      string IuQQTGcSMV;
      string QhzDjBtAUS;
      string rJeCyTLKfR;
      string eawddmfQxQ;
      string jwnlMumSxY;
      string SMuVnzPNRz;
      string uSmuqplVZx;
      string UcDEiuUspD;
      if(UJHjRsoNkm == hxhQXNPBHc){grMHzRfaod = true;}
      else if(hxhQXNPBHc == UJHjRsoNkm){GscPFHebIx = true;}
      if(XtOQfhMFNm == cmWgZMNQng){WSzxVQJstV = true;}
      else if(cmWgZMNQng == XtOQfhMFNm){gDnCwGfSoy = true;}
      if(IYLujsDJEP == IuQQTGcSMV){IQrzDpIqms = true;}
      else if(IuQQTGcSMV == IYLujsDJEP){brPaPSCJGp = true;}
      if(xEKQXEtqfU == QhzDjBtAUS){dWWOSCFeuY = true;}
      else if(QhzDjBtAUS == xEKQXEtqfU){ZxAytSZrPz = true;}
      if(XAGAFRtaqL == rJeCyTLKfR){KLgwaCdGiR = true;}
      else if(rJeCyTLKfR == XAGAFRtaqL){XutWVzEYqI = true;}
      if(iosWkwxMzY == eawddmfQxQ){lbyTtPANDI = true;}
      else if(eawddmfQxQ == iosWkwxMzY){oFwxyOcBAm = true;}
      if(oeJVoSixsa == jwnlMumSxY){JnnwAzujdS = true;}
      else if(jwnlMumSxY == oeJVoSixsa){EUVSXiCoHc = true;}
      if(nUZrOHSKpS == SMuVnzPNRz){LdxVLxiwYB = true;}
      if(ybRsgIKmfb == uSmuqplVZx){MCIUGCXCTC = true;}
      if(GhqGesqkKl == UcDEiuUspD){CramPVXkua = true;}
      while(SMuVnzPNRz == nUZrOHSKpS){gnDoZfxsFQ = true;}
      while(uSmuqplVZx == uSmuqplVZx){OdSyATBCzf = true;}
      while(UcDEiuUspD == UcDEiuUspD){pXrcuDZbzl = true;}
      if(grMHzRfaod == true){grMHzRfaod = false;}
      if(WSzxVQJstV == true){WSzxVQJstV = false;}
      if(IQrzDpIqms == true){IQrzDpIqms = false;}
      if(dWWOSCFeuY == true){dWWOSCFeuY = false;}
      if(KLgwaCdGiR == true){KLgwaCdGiR = false;}
      if(lbyTtPANDI == true){lbyTtPANDI = false;}
      if(JnnwAzujdS == true){JnnwAzujdS = false;}
      if(LdxVLxiwYB == true){LdxVLxiwYB = false;}
      if(MCIUGCXCTC == true){MCIUGCXCTC = false;}
      if(CramPVXkua == true){CramPVXkua = false;}
      if(GscPFHebIx == true){GscPFHebIx = false;}
      if(gDnCwGfSoy == true){gDnCwGfSoy = false;}
      if(brPaPSCJGp == true){brPaPSCJGp = false;}
      if(ZxAytSZrPz == true){ZxAytSZrPz = false;}
      if(XutWVzEYqI == true){XutWVzEYqI = false;}
      if(oFwxyOcBAm == true){oFwxyOcBAm = false;}
      if(EUVSXiCoHc == true){EUVSXiCoHc = false;}
      if(gnDoZfxsFQ == true){gnDoZfxsFQ = false;}
      if(OdSyATBCzf == true){OdSyATBCzf = false;}
      if(pXrcuDZbzl == true){pXrcuDZbzl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWCUYFMREP
{ 
  void mVKxtMRMwp()
  { 
      bool TqlfyDWSKT = false;
      bool RsPTxDVWWT = false;
      bool oRUWRdNsYx = false;
      bool RSWDjPSaye = false;
      bool SdWEyZZWWh = false;
      bool jPRkWBWPOT = false;
      bool ocsNCyVMjh = false;
      bool kuYqBLuQYq = false;
      bool DqWqNBAlfh = false;
      bool rCMeoojJBz = false;
      bool ENloxoqZjL = false;
      bool GGqWPyGCzB = false;
      bool xjfBohhtCL = false;
      bool akOYmpEgsY = false;
      bool JaBUblLoOq = false;
      bool ihJABUgkAP = false;
      bool GxXYjVqRjZ = false;
      bool sYIaqWhLZC = false;
      bool VseKbsaNWS = false;
      bool ITgcRLCckF = false;
      string BYuWkDXwna;
      string BzkHCOVdqZ;
      string lfcXgKrtkA;
      string BxGpfNwpQT;
      string GjWcoSIXjO;
      string SPGPnUwWpa;
      string KdKmZDrtan;
      string ReNXTBJzhO;
      string BTKWhlqqCK;
      string QZAoIbZiCk;
      string ZNxuxmBiwl;
      string LxoaYqTnFn;
      string MBrPXreXOq;
      string bZwwnnWOZt;
      string jHtPzTjYQR;
      string IkdOYYUgXF;
      string IdTFKlArmj;
      string TEOLDEHbQD;
      string HFHwhpwhXP;
      string SpqUlGmnFM;
      if(BYuWkDXwna == ZNxuxmBiwl){TqlfyDWSKT = true;}
      else if(ZNxuxmBiwl == BYuWkDXwna){ENloxoqZjL = true;}
      if(BzkHCOVdqZ == LxoaYqTnFn){RsPTxDVWWT = true;}
      else if(LxoaYqTnFn == BzkHCOVdqZ){GGqWPyGCzB = true;}
      if(lfcXgKrtkA == MBrPXreXOq){oRUWRdNsYx = true;}
      else if(MBrPXreXOq == lfcXgKrtkA){xjfBohhtCL = true;}
      if(BxGpfNwpQT == bZwwnnWOZt){RSWDjPSaye = true;}
      else if(bZwwnnWOZt == BxGpfNwpQT){akOYmpEgsY = true;}
      if(GjWcoSIXjO == jHtPzTjYQR){SdWEyZZWWh = true;}
      else if(jHtPzTjYQR == GjWcoSIXjO){JaBUblLoOq = true;}
      if(SPGPnUwWpa == IkdOYYUgXF){jPRkWBWPOT = true;}
      else if(IkdOYYUgXF == SPGPnUwWpa){ihJABUgkAP = true;}
      if(KdKmZDrtan == IdTFKlArmj){ocsNCyVMjh = true;}
      else if(IdTFKlArmj == KdKmZDrtan){GxXYjVqRjZ = true;}
      if(ReNXTBJzhO == TEOLDEHbQD){kuYqBLuQYq = true;}
      if(BTKWhlqqCK == HFHwhpwhXP){DqWqNBAlfh = true;}
      if(QZAoIbZiCk == SpqUlGmnFM){rCMeoojJBz = true;}
      while(TEOLDEHbQD == ReNXTBJzhO){sYIaqWhLZC = true;}
      while(HFHwhpwhXP == HFHwhpwhXP){VseKbsaNWS = true;}
      while(SpqUlGmnFM == SpqUlGmnFM){ITgcRLCckF = true;}
      if(TqlfyDWSKT == true){TqlfyDWSKT = false;}
      if(RsPTxDVWWT == true){RsPTxDVWWT = false;}
      if(oRUWRdNsYx == true){oRUWRdNsYx = false;}
      if(RSWDjPSaye == true){RSWDjPSaye = false;}
      if(SdWEyZZWWh == true){SdWEyZZWWh = false;}
      if(jPRkWBWPOT == true){jPRkWBWPOT = false;}
      if(ocsNCyVMjh == true){ocsNCyVMjh = false;}
      if(kuYqBLuQYq == true){kuYqBLuQYq = false;}
      if(DqWqNBAlfh == true){DqWqNBAlfh = false;}
      if(rCMeoojJBz == true){rCMeoojJBz = false;}
      if(ENloxoqZjL == true){ENloxoqZjL = false;}
      if(GGqWPyGCzB == true){GGqWPyGCzB = false;}
      if(xjfBohhtCL == true){xjfBohhtCL = false;}
      if(akOYmpEgsY == true){akOYmpEgsY = false;}
      if(JaBUblLoOq == true){JaBUblLoOq = false;}
      if(ihJABUgkAP == true){ihJABUgkAP = false;}
      if(GxXYjVqRjZ == true){GxXYjVqRjZ = false;}
      if(sYIaqWhLZC == true){sYIaqWhLZC = false;}
      if(VseKbsaNWS == true){VseKbsaNWS = false;}
      if(ITgcRLCckF == true){ITgcRLCckF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNVLUZFTRV
{ 
  void DmFnVSZhOy()
  { 
      bool inVoqsyWhF = false;
      bool glHsRMWssH = false;
      bool RmdurqLDnx = false;
      bool wuZCfwSLYy = false;
      bool OtCWWrUDoY = false;
      bool CrnRywJaxA = false;
      bool guhkJkMFMU = false;
      bool sKTtrWjHYA = false;
      bool VINPtDGHDi = false;
      bool lrOXRTLQMk = false;
      bool ePpUerXsYa = false;
      bool MCCwdXgRpF = false;
      bool dFBdhAuwcY = false;
      bool LTtmUGSrjC = false;
      bool fNhbWjpRts = false;
      bool lsZHGZNMle = false;
      bool wbQAPsHObW = false;
      bool FnhnYQWZGy = false;
      bool JcBilRsmft = false;
      bool sGGEGEwhLd = false;
      string EUIpdLLcJu;
      string jdtToNxzGa;
      string gnsGNxuKTz;
      string oalTJxRIhx;
      string QkSdZwDBYc;
      string AEtokQbCbg;
      string PAJKFJrZJr;
      string uoQIKwVOfQ;
      string stlpykfxhs;
      string UPfBgQaIYQ;
      string EcqfgLmkeo;
      string tNVLnVOSMT;
      string curQWeJPbs;
      string UMoPMPCFJm;
      string xuRsyHtUNK;
      string BHwEmJkZIC;
      string BXJkThXGyX;
      string TIJZVhcySP;
      string koBQqMQkbD;
      string ebwGkYkgYP;
      if(EUIpdLLcJu == EcqfgLmkeo){inVoqsyWhF = true;}
      else if(EcqfgLmkeo == EUIpdLLcJu){ePpUerXsYa = true;}
      if(jdtToNxzGa == tNVLnVOSMT){glHsRMWssH = true;}
      else if(tNVLnVOSMT == jdtToNxzGa){MCCwdXgRpF = true;}
      if(gnsGNxuKTz == curQWeJPbs){RmdurqLDnx = true;}
      else if(curQWeJPbs == gnsGNxuKTz){dFBdhAuwcY = true;}
      if(oalTJxRIhx == UMoPMPCFJm){wuZCfwSLYy = true;}
      else if(UMoPMPCFJm == oalTJxRIhx){LTtmUGSrjC = true;}
      if(QkSdZwDBYc == xuRsyHtUNK){OtCWWrUDoY = true;}
      else if(xuRsyHtUNK == QkSdZwDBYc){fNhbWjpRts = true;}
      if(AEtokQbCbg == BHwEmJkZIC){CrnRywJaxA = true;}
      else if(BHwEmJkZIC == AEtokQbCbg){lsZHGZNMle = true;}
      if(PAJKFJrZJr == BXJkThXGyX){guhkJkMFMU = true;}
      else if(BXJkThXGyX == PAJKFJrZJr){wbQAPsHObW = true;}
      if(uoQIKwVOfQ == TIJZVhcySP){sKTtrWjHYA = true;}
      if(stlpykfxhs == koBQqMQkbD){VINPtDGHDi = true;}
      if(UPfBgQaIYQ == ebwGkYkgYP){lrOXRTLQMk = true;}
      while(TIJZVhcySP == uoQIKwVOfQ){FnhnYQWZGy = true;}
      while(koBQqMQkbD == koBQqMQkbD){JcBilRsmft = true;}
      while(ebwGkYkgYP == ebwGkYkgYP){sGGEGEwhLd = true;}
      if(inVoqsyWhF == true){inVoqsyWhF = false;}
      if(glHsRMWssH == true){glHsRMWssH = false;}
      if(RmdurqLDnx == true){RmdurqLDnx = false;}
      if(wuZCfwSLYy == true){wuZCfwSLYy = false;}
      if(OtCWWrUDoY == true){OtCWWrUDoY = false;}
      if(CrnRywJaxA == true){CrnRywJaxA = false;}
      if(guhkJkMFMU == true){guhkJkMFMU = false;}
      if(sKTtrWjHYA == true){sKTtrWjHYA = false;}
      if(VINPtDGHDi == true){VINPtDGHDi = false;}
      if(lrOXRTLQMk == true){lrOXRTLQMk = false;}
      if(ePpUerXsYa == true){ePpUerXsYa = false;}
      if(MCCwdXgRpF == true){MCCwdXgRpF = false;}
      if(dFBdhAuwcY == true){dFBdhAuwcY = false;}
      if(LTtmUGSrjC == true){LTtmUGSrjC = false;}
      if(fNhbWjpRts == true){fNhbWjpRts = false;}
      if(lsZHGZNMle == true){lsZHGZNMle = false;}
      if(wbQAPsHObW == true){wbQAPsHObW = false;}
      if(FnhnYQWZGy == true){FnhnYQWZGy = false;}
      if(JcBilRsmft == true){JcBilRsmft = false;}
      if(sGGEGEwhLd == true){sGGEGEwhLd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOFABFXIWQ
{ 
  void iGdGirVgoq()
  { 
      bool fKaypqmNcC = false;
      bool ipUkFClhyW = false;
      bool enmHRuJBVU = false;
      bool QyLByUaQnV = false;
      bool qGRBlWbwCs = false;
      bool oySDlrWTgt = false;
      bool hlqHkjdSmj = false;
      bool bVtbfYWlUt = false;
      bool TMycfSfHPF = false;
      bool xGisnFOJPB = false;
      bool rJJSRTEpXM = false;
      bool VkzmaUmObS = false;
      bool EWCglUlAna = false;
      bool KNVTBKDfKM = false;
      bool OoiCjMHwST = false;
      bool RzgxwVGbfw = false;
      bool gDCxCIOekQ = false;
      bool QGDPDPmAxY = false;
      bool NohUIKfYWe = false;
      bool DbzOeKmlAa = false;
      string GimxkObRAE;
      string fzOAyOTpZu;
      string hPNwljbcEa;
      string IUSzEmlMzz;
      string YKVuBXETUt;
      string QkBgyqVpKA;
      string lyMZwKfOwK;
      string cHqaWXtSuN;
      string fIIKJWTlBM;
      string RwByMZyuyq;
      string roWJRJtaJZ;
      string xCtxUdpBQY;
      string qsNisgFrNx;
      string ZyTDUpkyrz;
      string cscaPOBDci;
      string iweZAzbnPk;
      string EBMLAyhpce;
      string rrIQwxPlSe;
      string eBOeNdTtDV;
      string NxhHuafQaQ;
      if(GimxkObRAE == roWJRJtaJZ){fKaypqmNcC = true;}
      else if(roWJRJtaJZ == GimxkObRAE){rJJSRTEpXM = true;}
      if(fzOAyOTpZu == xCtxUdpBQY){ipUkFClhyW = true;}
      else if(xCtxUdpBQY == fzOAyOTpZu){VkzmaUmObS = true;}
      if(hPNwljbcEa == qsNisgFrNx){enmHRuJBVU = true;}
      else if(qsNisgFrNx == hPNwljbcEa){EWCglUlAna = true;}
      if(IUSzEmlMzz == ZyTDUpkyrz){QyLByUaQnV = true;}
      else if(ZyTDUpkyrz == IUSzEmlMzz){KNVTBKDfKM = true;}
      if(YKVuBXETUt == cscaPOBDci){qGRBlWbwCs = true;}
      else if(cscaPOBDci == YKVuBXETUt){OoiCjMHwST = true;}
      if(QkBgyqVpKA == iweZAzbnPk){oySDlrWTgt = true;}
      else if(iweZAzbnPk == QkBgyqVpKA){RzgxwVGbfw = true;}
      if(lyMZwKfOwK == EBMLAyhpce){hlqHkjdSmj = true;}
      else if(EBMLAyhpce == lyMZwKfOwK){gDCxCIOekQ = true;}
      if(cHqaWXtSuN == rrIQwxPlSe){bVtbfYWlUt = true;}
      if(fIIKJWTlBM == eBOeNdTtDV){TMycfSfHPF = true;}
      if(RwByMZyuyq == NxhHuafQaQ){xGisnFOJPB = true;}
      while(rrIQwxPlSe == cHqaWXtSuN){QGDPDPmAxY = true;}
      while(eBOeNdTtDV == eBOeNdTtDV){NohUIKfYWe = true;}
      while(NxhHuafQaQ == NxhHuafQaQ){DbzOeKmlAa = true;}
      if(fKaypqmNcC == true){fKaypqmNcC = false;}
      if(ipUkFClhyW == true){ipUkFClhyW = false;}
      if(enmHRuJBVU == true){enmHRuJBVU = false;}
      if(QyLByUaQnV == true){QyLByUaQnV = false;}
      if(qGRBlWbwCs == true){qGRBlWbwCs = false;}
      if(oySDlrWTgt == true){oySDlrWTgt = false;}
      if(hlqHkjdSmj == true){hlqHkjdSmj = false;}
      if(bVtbfYWlUt == true){bVtbfYWlUt = false;}
      if(TMycfSfHPF == true){TMycfSfHPF = false;}
      if(xGisnFOJPB == true){xGisnFOJPB = false;}
      if(rJJSRTEpXM == true){rJJSRTEpXM = false;}
      if(VkzmaUmObS == true){VkzmaUmObS = false;}
      if(EWCglUlAna == true){EWCglUlAna = false;}
      if(KNVTBKDfKM == true){KNVTBKDfKM = false;}
      if(OoiCjMHwST == true){OoiCjMHwST = false;}
      if(RzgxwVGbfw == true){RzgxwVGbfw = false;}
      if(gDCxCIOekQ == true){gDCxCIOekQ = false;}
      if(QGDPDPmAxY == true){QGDPDPmAxY = false;}
      if(NohUIKfYWe == true){NohUIKfYWe = false;}
      if(DbzOeKmlAa == true){DbzOeKmlAa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJNHUNLMBV
{ 
  void uANLtNcbhx()
  { 
      bool wBlZRbfiVy = false;
      bool kQWFMpjHAM = false;
      bool ecAATOGcMx = false;
      bool ukXlJPMfuj = false;
      bool WRqswJMNFk = false;
      bool yhGYuTBkFC = false;
      bool UCWXCArjwx = false;
      bool dELPoMlGDJ = false;
      bool BsXayNdzqp = false;
      bool OaZrOUuSqw = false;
      bool QcQIHtWpih = false;
      bool hthwBaduYo = false;
      bool VsrFiCeSAU = false;
      bool RSPHrYbOTE = false;
      bool pmQJITsdqm = false;
      bool pzsBZXjLZE = false;
      bool ODoNPOdZDb = false;
      bool zPbUyhcixO = false;
      bool JBaMeSYOhU = false;
      bool oQnPolyCss = false;
      string ODgkCBOkrz;
      string hplCAYopoR;
      string zHcAqVJYFO;
      string BZmjURwHya;
      string xAFFpqklnS;
      string pJOtqHafsg;
      string qpfcxIDBgi;
      string chrOUyBWKz;
      string kXjmYqLrrN;
      string pQOQjGUbIh;
      string niEFpIRzZr;
      string FEVswSFsEG;
      string xKJTrLTaeN;
      string dYOcLBTewQ;
      string ZLSzHltUUQ;
      string BbXBjcZjMd;
      string opULOgoshu;
      string yZwnflrJMG;
      string RyFNLCBMrh;
      string ajSSaipGkZ;
      if(ODgkCBOkrz == niEFpIRzZr){wBlZRbfiVy = true;}
      else if(niEFpIRzZr == ODgkCBOkrz){QcQIHtWpih = true;}
      if(hplCAYopoR == FEVswSFsEG){kQWFMpjHAM = true;}
      else if(FEVswSFsEG == hplCAYopoR){hthwBaduYo = true;}
      if(zHcAqVJYFO == xKJTrLTaeN){ecAATOGcMx = true;}
      else if(xKJTrLTaeN == zHcAqVJYFO){VsrFiCeSAU = true;}
      if(BZmjURwHya == dYOcLBTewQ){ukXlJPMfuj = true;}
      else if(dYOcLBTewQ == BZmjURwHya){RSPHrYbOTE = true;}
      if(xAFFpqklnS == ZLSzHltUUQ){WRqswJMNFk = true;}
      else if(ZLSzHltUUQ == xAFFpqklnS){pmQJITsdqm = true;}
      if(pJOtqHafsg == BbXBjcZjMd){yhGYuTBkFC = true;}
      else if(BbXBjcZjMd == pJOtqHafsg){pzsBZXjLZE = true;}
      if(qpfcxIDBgi == opULOgoshu){UCWXCArjwx = true;}
      else if(opULOgoshu == qpfcxIDBgi){ODoNPOdZDb = true;}
      if(chrOUyBWKz == yZwnflrJMG){dELPoMlGDJ = true;}
      if(kXjmYqLrrN == RyFNLCBMrh){BsXayNdzqp = true;}
      if(pQOQjGUbIh == ajSSaipGkZ){OaZrOUuSqw = true;}
      while(yZwnflrJMG == chrOUyBWKz){zPbUyhcixO = true;}
      while(RyFNLCBMrh == RyFNLCBMrh){JBaMeSYOhU = true;}
      while(ajSSaipGkZ == ajSSaipGkZ){oQnPolyCss = true;}
      if(wBlZRbfiVy == true){wBlZRbfiVy = false;}
      if(kQWFMpjHAM == true){kQWFMpjHAM = false;}
      if(ecAATOGcMx == true){ecAATOGcMx = false;}
      if(ukXlJPMfuj == true){ukXlJPMfuj = false;}
      if(WRqswJMNFk == true){WRqswJMNFk = false;}
      if(yhGYuTBkFC == true){yhGYuTBkFC = false;}
      if(UCWXCArjwx == true){UCWXCArjwx = false;}
      if(dELPoMlGDJ == true){dELPoMlGDJ = false;}
      if(BsXayNdzqp == true){BsXayNdzqp = false;}
      if(OaZrOUuSqw == true){OaZrOUuSqw = false;}
      if(QcQIHtWpih == true){QcQIHtWpih = false;}
      if(hthwBaduYo == true){hthwBaduYo = false;}
      if(VsrFiCeSAU == true){VsrFiCeSAU = false;}
      if(RSPHrYbOTE == true){RSPHrYbOTE = false;}
      if(pmQJITsdqm == true){pmQJITsdqm = false;}
      if(pzsBZXjLZE == true){pzsBZXjLZE = false;}
      if(ODoNPOdZDb == true){ODoNPOdZDb = false;}
      if(zPbUyhcixO == true){zPbUyhcixO = false;}
      if(JBaMeSYOhU == true){JBaMeSYOhU = false;}
      if(oQnPolyCss == true){oQnPolyCss = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLXPVKMUUJ
{ 
  void FzWxXdKedr()
  { 
      bool NmBqLaiFuC = false;
      bool AqudlOeIfW = false;
      bool kIlkUdCZRB = false;
      bool oyVWjEMxZK = false;
      bool zPCTNEoLPh = false;
      bool FYNTbFAPWh = false;
      bool YImsMCUXsh = false;
      bool ChhUWUFSXP = false;
      bool opKiwQjCue = false;
      bool EwarlqbJGK = false;
      bool jQShfWpswG = false;
      bool zhrGriyDww = false;
      bool RRcNcFGphf = false;
      bool swLMfXWbDY = false;
      bool aqFneVDUzD = false;
      bool rXMKsRmFEZ = false;
      bool PAKQNDVfZT = false;
      bool LWAXVZMnhH = false;
      bool BlpemUiASN = false;
      bool kRXcIZgnab = false;
      string NcpFCkHRnb;
      string iaIeVPsbCg;
      string nRnSqZEjJg;
      string NEmFLuYVDk;
      string zaRkBlODVJ;
      string OqWDLwnWNc;
      string fXIHNdnCSZ;
      string pWYQgMACRF;
      string LANzRWgitP;
      string GBIZFbSKXW;
      string yLjuSqSFWy;
      string wlFHQeJIop;
      string xEHDToOyLE;
      string speuHzQRfZ;
      string EaLuSUwAIZ;
      string SKUgYsDfbd;
      string cTtRFGGJzR;
      string OqbPlWrMjy;
      string rNolliUyWO;
      string wjoBxjgtpM;
      if(NcpFCkHRnb == yLjuSqSFWy){NmBqLaiFuC = true;}
      else if(yLjuSqSFWy == NcpFCkHRnb){jQShfWpswG = true;}
      if(iaIeVPsbCg == wlFHQeJIop){AqudlOeIfW = true;}
      else if(wlFHQeJIop == iaIeVPsbCg){zhrGriyDww = true;}
      if(nRnSqZEjJg == xEHDToOyLE){kIlkUdCZRB = true;}
      else if(xEHDToOyLE == nRnSqZEjJg){RRcNcFGphf = true;}
      if(NEmFLuYVDk == speuHzQRfZ){oyVWjEMxZK = true;}
      else if(speuHzQRfZ == NEmFLuYVDk){swLMfXWbDY = true;}
      if(zaRkBlODVJ == EaLuSUwAIZ){zPCTNEoLPh = true;}
      else if(EaLuSUwAIZ == zaRkBlODVJ){aqFneVDUzD = true;}
      if(OqWDLwnWNc == SKUgYsDfbd){FYNTbFAPWh = true;}
      else if(SKUgYsDfbd == OqWDLwnWNc){rXMKsRmFEZ = true;}
      if(fXIHNdnCSZ == cTtRFGGJzR){YImsMCUXsh = true;}
      else if(cTtRFGGJzR == fXIHNdnCSZ){PAKQNDVfZT = true;}
      if(pWYQgMACRF == OqbPlWrMjy){ChhUWUFSXP = true;}
      if(LANzRWgitP == rNolliUyWO){opKiwQjCue = true;}
      if(GBIZFbSKXW == wjoBxjgtpM){EwarlqbJGK = true;}
      while(OqbPlWrMjy == pWYQgMACRF){LWAXVZMnhH = true;}
      while(rNolliUyWO == rNolliUyWO){BlpemUiASN = true;}
      while(wjoBxjgtpM == wjoBxjgtpM){kRXcIZgnab = true;}
      if(NmBqLaiFuC == true){NmBqLaiFuC = false;}
      if(AqudlOeIfW == true){AqudlOeIfW = false;}
      if(kIlkUdCZRB == true){kIlkUdCZRB = false;}
      if(oyVWjEMxZK == true){oyVWjEMxZK = false;}
      if(zPCTNEoLPh == true){zPCTNEoLPh = false;}
      if(FYNTbFAPWh == true){FYNTbFAPWh = false;}
      if(YImsMCUXsh == true){YImsMCUXsh = false;}
      if(ChhUWUFSXP == true){ChhUWUFSXP = false;}
      if(opKiwQjCue == true){opKiwQjCue = false;}
      if(EwarlqbJGK == true){EwarlqbJGK = false;}
      if(jQShfWpswG == true){jQShfWpswG = false;}
      if(zhrGriyDww == true){zhrGriyDww = false;}
      if(RRcNcFGphf == true){RRcNcFGphf = false;}
      if(swLMfXWbDY == true){swLMfXWbDY = false;}
      if(aqFneVDUzD == true){aqFneVDUzD = false;}
      if(rXMKsRmFEZ == true){rXMKsRmFEZ = false;}
      if(PAKQNDVfZT == true){PAKQNDVfZT = false;}
      if(LWAXVZMnhH == true){LWAXVZMnhH = false;}
      if(BlpemUiASN == true){BlpemUiASN = false;}
      if(kRXcIZgnab == true){kRXcIZgnab = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCLLKTFNHX
{ 
  void sVhMtmePFw()
  { 
      bool AKClnMwuUd = false;
      bool IuzQaOGnoU = false;
      bool QEwcOxXutH = false;
      bool GPXWIgMOsh = false;
      bool NahCOWdsNz = false;
      bool UiLItuOZXq = false;
      bool oBANWrXcIs = false;
      bool BquGHoVsNq = false;
      bool SegtlWEObN = false;
      bool RmqBsMZUeW = false;
      bool yBkTxdnFBF = false;
      bool ZVMfXJTFaz = false;
      bool mJBtbOAsMt = false;
      bool OANpsRtMwI = false;
      bool iyMWmwZKdj = false;
      bool sUseioApri = false;
      bool ctrHpYHVmG = false;
      bool PGISPowdHe = false;
      bool noOcBtGiHD = false;
      bool RDUNeoFFfN = false;
      string ajQqBBFjAD;
      string XNNBOVrVZQ;
      string kfkhTekKmI;
      string XlwTHXlXlV;
      string KVyEPsEJhg;
      string RLXhluyhXW;
      string QuxrfkQtsp;
      string iTiDGPggRZ;
      string ZbbFpLNNgM;
      string YDAOFOXGYd;
      string cKPqyxbUbW;
      string NQPxwnSqBT;
      string WDMgQeSTyq;
      string qaImxPMjHs;
      string jslKyImDSQ;
      string ugEEHZxhZS;
      string dHVkfmIbAf;
      string bhjIidRChI;
      string rPBhuKWDfX;
      string RdKnObWBdL;
      if(ajQqBBFjAD == cKPqyxbUbW){AKClnMwuUd = true;}
      else if(cKPqyxbUbW == ajQqBBFjAD){yBkTxdnFBF = true;}
      if(XNNBOVrVZQ == NQPxwnSqBT){IuzQaOGnoU = true;}
      else if(NQPxwnSqBT == XNNBOVrVZQ){ZVMfXJTFaz = true;}
      if(kfkhTekKmI == WDMgQeSTyq){QEwcOxXutH = true;}
      else if(WDMgQeSTyq == kfkhTekKmI){mJBtbOAsMt = true;}
      if(XlwTHXlXlV == qaImxPMjHs){GPXWIgMOsh = true;}
      else if(qaImxPMjHs == XlwTHXlXlV){OANpsRtMwI = true;}
      if(KVyEPsEJhg == jslKyImDSQ){NahCOWdsNz = true;}
      else if(jslKyImDSQ == KVyEPsEJhg){iyMWmwZKdj = true;}
      if(RLXhluyhXW == ugEEHZxhZS){UiLItuOZXq = true;}
      else if(ugEEHZxhZS == RLXhluyhXW){sUseioApri = true;}
      if(QuxrfkQtsp == dHVkfmIbAf){oBANWrXcIs = true;}
      else if(dHVkfmIbAf == QuxrfkQtsp){ctrHpYHVmG = true;}
      if(iTiDGPggRZ == bhjIidRChI){BquGHoVsNq = true;}
      if(ZbbFpLNNgM == rPBhuKWDfX){SegtlWEObN = true;}
      if(YDAOFOXGYd == RdKnObWBdL){RmqBsMZUeW = true;}
      while(bhjIidRChI == iTiDGPggRZ){PGISPowdHe = true;}
      while(rPBhuKWDfX == rPBhuKWDfX){noOcBtGiHD = true;}
      while(RdKnObWBdL == RdKnObWBdL){RDUNeoFFfN = true;}
      if(AKClnMwuUd == true){AKClnMwuUd = false;}
      if(IuzQaOGnoU == true){IuzQaOGnoU = false;}
      if(QEwcOxXutH == true){QEwcOxXutH = false;}
      if(GPXWIgMOsh == true){GPXWIgMOsh = false;}
      if(NahCOWdsNz == true){NahCOWdsNz = false;}
      if(UiLItuOZXq == true){UiLItuOZXq = false;}
      if(oBANWrXcIs == true){oBANWrXcIs = false;}
      if(BquGHoVsNq == true){BquGHoVsNq = false;}
      if(SegtlWEObN == true){SegtlWEObN = false;}
      if(RmqBsMZUeW == true){RmqBsMZUeW = false;}
      if(yBkTxdnFBF == true){yBkTxdnFBF = false;}
      if(ZVMfXJTFaz == true){ZVMfXJTFaz = false;}
      if(mJBtbOAsMt == true){mJBtbOAsMt = false;}
      if(OANpsRtMwI == true){OANpsRtMwI = false;}
      if(iyMWmwZKdj == true){iyMWmwZKdj = false;}
      if(sUseioApri == true){sUseioApri = false;}
      if(ctrHpYHVmG == true){ctrHpYHVmG = false;}
      if(PGISPowdHe == true){PGISPowdHe = false;}
      if(noOcBtGiHD == true){noOcBtGiHD = false;}
      if(RDUNeoFFfN == true){RDUNeoFFfN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYMWMQAACH
{ 
  void hzEQWqforT()
  { 
      bool gAlAPElPqc = false;
      bool OyePVoONly = false;
      bool mEnaYCUSRY = false;
      bool oHUFpyjTIH = false;
      bool orSjwDbdgB = false;
      bool HwCmDbLLbN = false;
      bool jTxRnHdZZX = false;
      bool FuEeIulDdU = false;
      bool apkQQrEgBN = false;
      bool lXrtXVtAwo = false;
      bool ZBEJuMrXeI = false;
      bool pIgGmshgBu = false;
      bool DwXLkgDJGm = false;
      bool AkHouYlbUD = false;
      bool AfCsXdpkHe = false;
      bool mMyAlcdrXO = false;
      bool JhQrHFArLO = false;
      bool GGMxuWtdnG = false;
      bool qRCbzmlGDR = false;
      bool tsDGtRPKlS = false;
      string ITOwxtxKNQ;
      string LEHFesnaYx;
      string lQUKTmFPRt;
      string ZizUGFxJUG;
      string zxBgyBJKdT;
      string klCdyqyDbK;
      string nhsTqbFmzY;
      string wdFRynOmLS;
      string culxImgUVP;
      string GthJSQEhpW;
      string wVLEXHfkfJ;
      string bLqIhswuKD;
      string ukRiRCuwyg;
      string jfxoWGigZB;
      string HwnLmuCYbZ;
      string UIXmbLEblV;
      string LjlzZuOCla;
      string JPVIwywGwW;
      string zWUYMbIJNL;
      string CHtDpWJokq;
      if(ITOwxtxKNQ == wVLEXHfkfJ){gAlAPElPqc = true;}
      else if(wVLEXHfkfJ == ITOwxtxKNQ){ZBEJuMrXeI = true;}
      if(LEHFesnaYx == bLqIhswuKD){OyePVoONly = true;}
      else if(bLqIhswuKD == LEHFesnaYx){pIgGmshgBu = true;}
      if(lQUKTmFPRt == ukRiRCuwyg){mEnaYCUSRY = true;}
      else if(ukRiRCuwyg == lQUKTmFPRt){DwXLkgDJGm = true;}
      if(ZizUGFxJUG == jfxoWGigZB){oHUFpyjTIH = true;}
      else if(jfxoWGigZB == ZizUGFxJUG){AkHouYlbUD = true;}
      if(zxBgyBJKdT == HwnLmuCYbZ){orSjwDbdgB = true;}
      else if(HwnLmuCYbZ == zxBgyBJKdT){AfCsXdpkHe = true;}
      if(klCdyqyDbK == UIXmbLEblV){HwCmDbLLbN = true;}
      else if(UIXmbLEblV == klCdyqyDbK){mMyAlcdrXO = true;}
      if(nhsTqbFmzY == LjlzZuOCla){jTxRnHdZZX = true;}
      else if(LjlzZuOCla == nhsTqbFmzY){JhQrHFArLO = true;}
      if(wdFRynOmLS == JPVIwywGwW){FuEeIulDdU = true;}
      if(culxImgUVP == zWUYMbIJNL){apkQQrEgBN = true;}
      if(GthJSQEhpW == CHtDpWJokq){lXrtXVtAwo = true;}
      while(JPVIwywGwW == wdFRynOmLS){GGMxuWtdnG = true;}
      while(zWUYMbIJNL == zWUYMbIJNL){qRCbzmlGDR = true;}
      while(CHtDpWJokq == CHtDpWJokq){tsDGtRPKlS = true;}
      if(gAlAPElPqc == true){gAlAPElPqc = false;}
      if(OyePVoONly == true){OyePVoONly = false;}
      if(mEnaYCUSRY == true){mEnaYCUSRY = false;}
      if(oHUFpyjTIH == true){oHUFpyjTIH = false;}
      if(orSjwDbdgB == true){orSjwDbdgB = false;}
      if(HwCmDbLLbN == true){HwCmDbLLbN = false;}
      if(jTxRnHdZZX == true){jTxRnHdZZX = false;}
      if(FuEeIulDdU == true){FuEeIulDdU = false;}
      if(apkQQrEgBN == true){apkQQrEgBN = false;}
      if(lXrtXVtAwo == true){lXrtXVtAwo = false;}
      if(ZBEJuMrXeI == true){ZBEJuMrXeI = false;}
      if(pIgGmshgBu == true){pIgGmshgBu = false;}
      if(DwXLkgDJGm == true){DwXLkgDJGm = false;}
      if(AkHouYlbUD == true){AkHouYlbUD = false;}
      if(AfCsXdpkHe == true){AfCsXdpkHe = false;}
      if(mMyAlcdrXO == true){mMyAlcdrXO = false;}
      if(JhQrHFArLO == true){JhQrHFArLO = false;}
      if(GGMxuWtdnG == true){GGMxuWtdnG = false;}
      if(qRCbzmlGDR == true){qRCbzmlGDR = false;}
      if(tsDGtRPKlS == true){tsDGtRPKlS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGPVCMAXSO
{ 
  void gGJHKpjwGq()
  { 
      bool ENnyWTweTr = false;
      bool FPUZPiuykd = false;
      bool eHtyIZRdRI = false;
      bool dewRHWqZDh = false;
      bool pHLXuSAkYP = false;
      bool sThOoxToow = false;
      bool BRMLOaTDSr = false;
      bool qUtDnXwWDp = false;
      bool ZgFCOJwgbJ = false;
      bool DCkHfXtzIU = false;
      bool yxSfYYYeZQ = false;
      bool BxlyWUMKxE = false;
      bool dlaIoojmWP = false;
      bool dwNhqcOYcp = false;
      bool jRHLIFPlkL = false;
      bool LiCEpMVJqi = false;
      bool nlHJlEjDHs = false;
      bool FmgGTMePzj = false;
      bool YxCLDutIre = false;
      bool GEgsByJxYE = false;
      string QDRhlaYRaE;
      string LpnAQreSIF;
      string BJwOORtLJy;
      string FMwPrjrOlX;
      string kdCYdBbmXK;
      string ANCFnGHCTT;
      string fNHbyytYIg;
      string zPfkUWHWkM;
      string pHnzyqJpak;
      string bpuSqWWZZe;
      string HDepKjhRkQ;
      string zjQGdYZHdH;
      string oDyXEJUNsy;
      string AhxGFmcxoN;
      string JqFJlrYooS;
      string wOuRpDEGlA;
      string OTYlQRmKAq;
      string wcSQyxyolM;
      string kfYZBlleQB;
      string hVKnyoSSsT;
      if(QDRhlaYRaE == HDepKjhRkQ){ENnyWTweTr = true;}
      else if(HDepKjhRkQ == QDRhlaYRaE){yxSfYYYeZQ = true;}
      if(LpnAQreSIF == zjQGdYZHdH){FPUZPiuykd = true;}
      else if(zjQGdYZHdH == LpnAQreSIF){BxlyWUMKxE = true;}
      if(BJwOORtLJy == oDyXEJUNsy){eHtyIZRdRI = true;}
      else if(oDyXEJUNsy == BJwOORtLJy){dlaIoojmWP = true;}
      if(FMwPrjrOlX == AhxGFmcxoN){dewRHWqZDh = true;}
      else if(AhxGFmcxoN == FMwPrjrOlX){dwNhqcOYcp = true;}
      if(kdCYdBbmXK == JqFJlrYooS){pHLXuSAkYP = true;}
      else if(JqFJlrYooS == kdCYdBbmXK){jRHLIFPlkL = true;}
      if(ANCFnGHCTT == wOuRpDEGlA){sThOoxToow = true;}
      else if(wOuRpDEGlA == ANCFnGHCTT){LiCEpMVJqi = true;}
      if(fNHbyytYIg == OTYlQRmKAq){BRMLOaTDSr = true;}
      else if(OTYlQRmKAq == fNHbyytYIg){nlHJlEjDHs = true;}
      if(zPfkUWHWkM == wcSQyxyolM){qUtDnXwWDp = true;}
      if(pHnzyqJpak == kfYZBlleQB){ZgFCOJwgbJ = true;}
      if(bpuSqWWZZe == hVKnyoSSsT){DCkHfXtzIU = true;}
      while(wcSQyxyolM == zPfkUWHWkM){FmgGTMePzj = true;}
      while(kfYZBlleQB == kfYZBlleQB){YxCLDutIre = true;}
      while(hVKnyoSSsT == hVKnyoSSsT){GEgsByJxYE = true;}
      if(ENnyWTweTr == true){ENnyWTweTr = false;}
      if(FPUZPiuykd == true){FPUZPiuykd = false;}
      if(eHtyIZRdRI == true){eHtyIZRdRI = false;}
      if(dewRHWqZDh == true){dewRHWqZDh = false;}
      if(pHLXuSAkYP == true){pHLXuSAkYP = false;}
      if(sThOoxToow == true){sThOoxToow = false;}
      if(BRMLOaTDSr == true){BRMLOaTDSr = false;}
      if(qUtDnXwWDp == true){qUtDnXwWDp = false;}
      if(ZgFCOJwgbJ == true){ZgFCOJwgbJ = false;}
      if(DCkHfXtzIU == true){DCkHfXtzIU = false;}
      if(yxSfYYYeZQ == true){yxSfYYYeZQ = false;}
      if(BxlyWUMKxE == true){BxlyWUMKxE = false;}
      if(dlaIoojmWP == true){dlaIoojmWP = false;}
      if(dwNhqcOYcp == true){dwNhqcOYcp = false;}
      if(jRHLIFPlkL == true){jRHLIFPlkL = false;}
      if(LiCEpMVJqi == true){LiCEpMVJqi = false;}
      if(nlHJlEjDHs == true){nlHJlEjDHs = false;}
      if(FmgGTMePzj == true){FmgGTMePzj = false;}
      if(YxCLDutIre == true){YxCLDutIre = false;}
      if(GEgsByJxYE == true){GEgsByJxYE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAZYWVHWLA
{ 
  void WlCyMesKfA()
  { 
      bool cYHwtRwwnk = false;
      bool WNaUYARCFD = false;
      bool sgOMyufmmY = false;
      bool WPSnMrxYTl = false;
      bool XQjJOeLVzL = false;
      bool PyoCnuJtyz = false;
      bool kJIPOGulHg = false;
      bool DshSfbxEyS = false;
      bool iJmbIXaQzR = false;
      bool hCZUAOIUuH = false;
      bool jZOSHWPVWM = false;
      bool xFwePbVfGp = false;
      bool fdmpyBSNRQ = false;
      bool TcIpiJuTTl = false;
      bool IEtmTcGtEY = false;
      bool rbNFbFlXUG = false;
      bool DCDFrUwFwG = false;
      bool fBMUhaiAVV = false;
      bool tYIsYrPDOc = false;
      bool WWzMiFBotz = false;
      string SiaQUHQZYb;
      string YiOzNHnPee;
      string dgOLhgDFrb;
      string gMNlneLGxw;
      string YRKUJROPSl;
      string wOoIKlUPhn;
      string DKgxuMUbKi;
      string whRhGLWsBQ;
      string RmlFfRXFaC;
      string JwXJrNjNYx;
      string wmEjpOwGBz;
      string OaNRVQYbQc;
      string oOAIYzJIpr;
      string bJUDTeiBPQ;
      string VQDbmihFmb;
      string nIwuIhlwKp;
      string EmQJWFGJyq;
      string hWLAHXKXVp;
      string QEUNDTMYuk;
      string slqYMhAtFg;
      if(SiaQUHQZYb == wmEjpOwGBz){cYHwtRwwnk = true;}
      else if(wmEjpOwGBz == SiaQUHQZYb){jZOSHWPVWM = true;}
      if(YiOzNHnPee == OaNRVQYbQc){WNaUYARCFD = true;}
      else if(OaNRVQYbQc == YiOzNHnPee){xFwePbVfGp = true;}
      if(dgOLhgDFrb == oOAIYzJIpr){sgOMyufmmY = true;}
      else if(oOAIYzJIpr == dgOLhgDFrb){fdmpyBSNRQ = true;}
      if(gMNlneLGxw == bJUDTeiBPQ){WPSnMrxYTl = true;}
      else if(bJUDTeiBPQ == gMNlneLGxw){TcIpiJuTTl = true;}
      if(YRKUJROPSl == VQDbmihFmb){XQjJOeLVzL = true;}
      else if(VQDbmihFmb == YRKUJROPSl){IEtmTcGtEY = true;}
      if(wOoIKlUPhn == nIwuIhlwKp){PyoCnuJtyz = true;}
      else if(nIwuIhlwKp == wOoIKlUPhn){rbNFbFlXUG = true;}
      if(DKgxuMUbKi == EmQJWFGJyq){kJIPOGulHg = true;}
      else if(EmQJWFGJyq == DKgxuMUbKi){DCDFrUwFwG = true;}
      if(whRhGLWsBQ == hWLAHXKXVp){DshSfbxEyS = true;}
      if(RmlFfRXFaC == QEUNDTMYuk){iJmbIXaQzR = true;}
      if(JwXJrNjNYx == slqYMhAtFg){hCZUAOIUuH = true;}
      while(hWLAHXKXVp == whRhGLWsBQ){fBMUhaiAVV = true;}
      while(QEUNDTMYuk == QEUNDTMYuk){tYIsYrPDOc = true;}
      while(slqYMhAtFg == slqYMhAtFg){WWzMiFBotz = true;}
      if(cYHwtRwwnk == true){cYHwtRwwnk = false;}
      if(WNaUYARCFD == true){WNaUYARCFD = false;}
      if(sgOMyufmmY == true){sgOMyufmmY = false;}
      if(WPSnMrxYTl == true){WPSnMrxYTl = false;}
      if(XQjJOeLVzL == true){XQjJOeLVzL = false;}
      if(PyoCnuJtyz == true){PyoCnuJtyz = false;}
      if(kJIPOGulHg == true){kJIPOGulHg = false;}
      if(DshSfbxEyS == true){DshSfbxEyS = false;}
      if(iJmbIXaQzR == true){iJmbIXaQzR = false;}
      if(hCZUAOIUuH == true){hCZUAOIUuH = false;}
      if(jZOSHWPVWM == true){jZOSHWPVWM = false;}
      if(xFwePbVfGp == true){xFwePbVfGp = false;}
      if(fdmpyBSNRQ == true){fdmpyBSNRQ = false;}
      if(TcIpiJuTTl == true){TcIpiJuTTl = false;}
      if(IEtmTcGtEY == true){IEtmTcGtEY = false;}
      if(rbNFbFlXUG == true){rbNFbFlXUG = false;}
      if(DCDFrUwFwG == true){DCDFrUwFwG = false;}
      if(fBMUhaiAVV == true){fBMUhaiAVV = false;}
      if(tYIsYrPDOc == true){tYIsYrPDOc = false;}
      if(WWzMiFBotz == true){WWzMiFBotz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOEEFHUSRG
{ 
  void blzUrQwOHs()
  { 
      bool jQtxwFyXUH = false;
      bool kndZbTuNqf = false;
      bool rVhrjtTdDo = false;
      bool FslGeRxgzz = false;
      bool kYrOhXjUPP = false;
      bool zmqySNiBMC = false;
      bool lUTeCrCWtK = false;
      bool WONrtScTJL = false;
      bool JyNnoRCmnQ = false;
      bool huTxNQENLp = false;
      bool VNZErkYyDz = false;
      bool jOrArmGfpk = false;
      bool pOhdbbtQec = false;
      bool OPHSowYJwD = false;
      bool rDiofTCSEZ = false;
      bool KXWazHewcQ = false;
      bool qITajUHYKw = false;
      bool OwjlrmesxI = false;
      bool YaLESprgTh = false;
      bool QbfeMjiIEL = false;
      string lizSOlAmuT;
      string CXtLDnnjpX;
      string VkGpZSwozI;
      string wMQWxxWqDO;
      string ddgfWZlZeh;
      string EdnPKAbJru;
      string oKnlWpHWNF;
      string RwgbsrDaSz;
      string gVKRDRXBMw;
      string VMzIYTotIg;
      string SPMZPIxMVR;
      string xBpsOSzWiE;
      string RGKQjExXCZ;
      string CIRkgRJkBu;
      string ULetzTVFtF;
      string USLEOMEupK;
      string LYJwPoiFLx;
      string IOUmjGaQRP;
      string hqdwEiwNWT;
      string MOuqjuBhdK;
      if(lizSOlAmuT == SPMZPIxMVR){jQtxwFyXUH = true;}
      else if(SPMZPIxMVR == lizSOlAmuT){VNZErkYyDz = true;}
      if(CXtLDnnjpX == xBpsOSzWiE){kndZbTuNqf = true;}
      else if(xBpsOSzWiE == CXtLDnnjpX){jOrArmGfpk = true;}
      if(VkGpZSwozI == RGKQjExXCZ){rVhrjtTdDo = true;}
      else if(RGKQjExXCZ == VkGpZSwozI){pOhdbbtQec = true;}
      if(wMQWxxWqDO == CIRkgRJkBu){FslGeRxgzz = true;}
      else if(CIRkgRJkBu == wMQWxxWqDO){OPHSowYJwD = true;}
      if(ddgfWZlZeh == ULetzTVFtF){kYrOhXjUPP = true;}
      else if(ULetzTVFtF == ddgfWZlZeh){rDiofTCSEZ = true;}
      if(EdnPKAbJru == USLEOMEupK){zmqySNiBMC = true;}
      else if(USLEOMEupK == EdnPKAbJru){KXWazHewcQ = true;}
      if(oKnlWpHWNF == LYJwPoiFLx){lUTeCrCWtK = true;}
      else if(LYJwPoiFLx == oKnlWpHWNF){qITajUHYKw = true;}
      if(RwgbsrDaSz == IOUmjGaQRP){WONrtScTJL = true;}
      if(gVKRDRXBMw == hqdwEiwNWT){JyNnoRCmnQ = true;}
      if(VMzIYTotIg == MOuqjuBhdK){huTxNQENLp = true;}
      while(IOUmjGaQRP == RwgbsrDaSz){OwjlrmesxI = true;}
      while(hqdwEiwNWT == hqdwEiwNWT){YaLESprgTh = true;}
      while(MOuqjuBhdK == MOuqjuBhdK){QbfeMjiIEL = true;}
      if(jQtxwFyXUH == true){jQtxwFyXUH = false;}
      if(kndZbTuNqf == true){kndZbTuNqf = false;}
      if(rVhrjtTdDo == true){rVhrjtTdDo = false;}
      if(FslGeRxgzz == true){FslGeRxgzz = false;}
      if(kYrOhXjUPP == true){kYrOhXjUPP = false;}
      if(zmqySNiBMC == true){zmqySNiBMC = false;}
      if(lUTeCrCWtK == true){lUTeCrCWtK = false;}
      if(WONrtScTJL == true){WONrtScTJL = false;}
      if(JyNnoRCmnQ == true){JyNnoRCmnQ = false;}
      if(huTxNQENLp == true){huTxNQENLp = false;}
      if(VNZErkYyDz == true){VNZErkYyDz = false;}
      if(jOrArmGfpk == true){jOrArmGfpk = false;}
      if(pOhdbbtQec == true){pOhdbbtQec = false;}
      if(OPHSowYJwD == true){OPHSowYJwD = false;}
      if(rDiofTCSEZ == true){rDiofTCSEZ = false;}
      if(KXWazHewcQ == true){KXWazHewcQ = false;}
      if(qITajUHYKw == true){qITajUHYKw = false;}
      if(OwjlrmesxI == true){OwjlrmesxI = false;}
      if(YaLESprgTh == true){YaLESprgTh = false;}
      if(QbfeMjiIEL == true){QbfeMjiIEL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEBUQYOBRD
{ 
  void oWFMZaoWtG()
  { 
      bool fAtJIWfgdz = false;
      bool CONDNfybNj = false;
      bool PRlDLJyQPD = false;
      bool gTGsJdObpQ = false;
      bool fCmKtrZnGi = false;
      bool jnyNWONpyz = false;
      bool YORaShHTtj = false;
      bool QWkwEMdbJT = false;
      bool iKKfSsVrWu = false;
      bool PYdqrQkMrL = false;
      bool jFsWRNCBIJ = false;
      bool jlgePNDkHY = false;
      bool MPxzTrrtEn = false;
      bool aQjxidQnOE = false;
      bool pUjMKdrybd = false;
      bool MAFSzUHtCZ = false;
      bool UHxUhTCiuk = false;
      bool wPWCirfknp = false;
      bool AtSZaaLQyO = false;
      bool VWknihWOdq = false;
      string aKkuTWYAMO;
      string EWHhgZDmrm;
      string efqnChDPZb;
      string tsKleyxVFD;
      string xniowqoMgu;
      string beVrQtSwsk;
      string TJakULMVCi;
      string chhooqwCrL;
      string sphdzPWRUk;
      string eBcTinNyUk;
      string dSKxStxfDZ;
      string yQEhrcawkE;
      string nuAREaENFB;
      string cygHgZfkLF;
      string SqOulOxubG;
      string MQNPwiSrsq;
      string ojaCwAiwBR;
      string xpkflxfEeo;
      string dJkznLjRKx;
      string GmqTPiPMyl;
      if(aKkuTWYAMO == dSKxStxfDZ){fAtJIWfgdz = true;}
      else if(dSKxStxfDZ == aKkuTWYAMO){jFsWRNCBIJ = true;}
      if(EWHhgZDmrm == yQEhrcawkE){CONDNfybNj = true;}
      else if(yQEhrcawkE == EWHhgZDmrm){jlgePNDkHY = true;}
      if(efqnChDPZb == nuAREaENFB){PRlDLJyQPD = true;}
      else if(nuAREaENFB == efqnChDPZb){MPxzTrrtEn = true;}
      if(tsKleyxVFD == cygHgZfkLF){gTGsJdObpQ = true;}
      else if(cygHgZfkLF == tsKleyxVFD){aQjxidQnOE = true;}
      if(xniowqoMgu == SqOulOxubG){fCmKtrZnGi = true;}
      else if(SqOulOxubG == xniowqoMgu){pUjMKdrybd = true;}
      if(beVrQtSwsk == MQNPwiSrsq){jnyNWONpyz = true;}
      else if(MQNPwiSrsq == beVrQtSwsk){MAFSzUHtCZ = true;}
      if(TJakULMVCi == ojaCwAiwBR){YORaShHTtj = true;}
      else if(ojaCwAiwBR == TJakULMVCi){UHxUhTCiuk = true;}
      if(chhooqwCrL == xpkflxfEeo){QWkwEMdbJT = true;}
      if(sphdzPWRUk == dJkznLjRKx){iKKfSsVrWu = true;}
      if(eBcTinNyUk == GmqTPiPMyl){PYdqrQkMrL = true;}
      while(xpkflxfEeo == chhooqwCrL){wPWCirfknp = true;}
      while(dJkznLjRKx == dJkznLjRKx){AtSZaaLQyO = true;}
      while(GmqTPiPMyl == GmqTPiPMyl){VWknihWOdq = true;}
      if(fAtJIWfgdz == true){fAtJIWfgdz = false;}
      if(CONDNfybNj == true){CONDNfybNj = false;}
      if(PRlDLJyQPD == true){PRlDLJyQPD = false;}
      if(gTGsJdObpQ == true){gTGsJdObpQ = false;}
      if(fCmKtrZnGi == true){fCmKtrZnGi = false;}
      if(jnyNWONpyz == true){jnyNWONpyz = false;}
      if(YORaShHTtj == true){YORaShHTtj = false;}
      if(QWkwEMdbJT == true){QWkwEMdbJT = false;}
      if(iKKfSsVrWu == true){iKKfSsVrWu = false;}
      if(PYdqrQkMrL == true){PYdqrQkMrL = false;}
      if(jFsWRNCBIJ == true){jFsWRNCBIJ = false;}
      if(jlgePNDkHY == true){jlgePNDkHY = false;}
      if(MPxzTrrtEn == true){MPxzTrrtEn = false;}
      if(aQjxidQnOE == true){aQjxidQnOE = false;}
      if(pUjMKdrybd == true){pUjMKdrybd = false;}
      if(MAFSzUHtCZ == true){MAFSzUHtCZ = false;}
      if(UHxUhTCiuk == true){UHxUhTCiuk = false;}
      if(wPWCirfknp == true){wPWCirfknp = false;}
      if(AtSZaaLQyO == true){AtSZaaLQyO = false;}
      if(VWknihWOdq == true){VWknihWOdq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDDRBJXXSJ
{ 
  void ZYtclliAfR()
  { 
      bool rRgOaurNTd = false;
      bool udUPABLIPO = false;
      bool cSJgbubJEm = false;
      bool oXckjgDrXX = false;
      bool QfxBdoRGMS = false;
      bool WNNKMYHAlf = false;
      bool ThIgoXBieT = false;
      bool xSjryxVIDm = false;
      bool dVxlPbJRYK = false;
      bool YDGrEiXQLG = false;
      bool miarUDcVMP = false;
      bool DywzCxjWQN = false;
      bool NiJTttMrnO = false;
      bool YFwxzutEQL = false;
      bool ynFJHZGGpG = false;
      bool yAzyrDYGxZ = false;
      bool qkgxpxCzzH = false;
      bool DfGEOYdzMU = false;
      bool nFBgQXGxEu = false;
      bool VmGpTNGITK = false;
      string SuQOguKsOz;
      string WlIcywOBrw;
      string ZOmIHGKjrS;
      string qpROVZZXfK;
      string eAOUKcZqWa;
      string BFxLUEHIHa;
      string jZBwIgTsGX;
      string WpVhQYzRye;
      string fTNQQksGsR;
      string RQQEZFzSMc;
      string JfkyEKjPtw;
      string EoJbuQMjeW;
      string nMznFFYQHL;
      string YgFUVziOMG;
      string BcLxMcGnJI;
      string sPmoowfwry;
      string lSHiXXjoGu;
      string hxXYVKACac;
      string ykHzSItQeY;
      string SlVNThVcZo;
      if(SuQOguKsOz == JfkyEKjPtw){rRgOaurNTd = true;}
      else if(JfkyEKjPtw == SuQOguKsOz){miarUDcVMP = true;}
      if(WlIcywOBrw == EoJbuQMjeW){udUPABLIPO = true;}
      else if(EoJbuQMjeW == WlIcywOBrw){DywzCxjWQN = true;}
      if(ZOmIHGKjrS == nMznFFYQHL){cSJgbubJEm = true;}
      else if(nMznFFYQHL == ZOmIHGKjrS){NiJTttMrnO = true;}
      if(qpROVZZXfK == YgFUVziOMG){oXckjgDrXX = true;}
      else if(YgFUVziOMG == qpROVZZXfK){YFwxzutEQL = true;}
      if(eAOUKcZqWa == BcLxMcGnJI){QfxBdoRGMS = true;}
      else if(BcLxMcGnJI == eAOUKcZqWa){ynFJHZGGpG = true;}
      if(BFxLUEHIHa == sPmoowfwry){WNNKMYHAlf = true;}
      else if(sPmoowfwry == BFxLUEHIHa){yAzyrDYGxZ = true;}
      if(jZBwIgTsGX == lSHiXXjoGu){ThIgoXBieT = true;}
      else if(lSHiXXjoGu == jZBwIgTsGX){qkgxpxCzzH = true;}
      if(WpVhQYzRye == hxXYVKACac){xSjryxVIDm = true;}
      if(fTNQQksGsR == ykHzSItQeY){dVxlPbJRYK = true;}
      if(RQQEZFzSMc == SlVNThVcZo){YDGrEiXQLG = true;}
      while(hxXYVKACac == WpVhQYzRye){DfGEOYdzMU = true;}
      while(ykHzSItQeY == ykHzSItQeY){nFBgQXGxEu = true;}
      while(SlVNThVcZo == SlVNThVcZo){VmGpTNGITK = true;}
      if(rRgOaurNTd == true){rRgOaurNTd = false;}
      if(udUPABLIPO == true){udUPABLIPO = false;}
      if(cSJgbubJEm == true){cSJgbubJEm = false;}
      if(oXckjgDrXX == true){oXckjgDrXX = false;}
      if(QfxBdoRGMS == true){QfxBdoRGMS = false;}
      if(WNNKMYHAlf == true){WNNKMYHAlf = false;}
      if(ThIgoXBieT == true){ThIgoXBieT = false;}
      if(xSjryxVIDm == true){xSjryxVIDm = false;}
      if(dVxlPbJRYK == true){dVxlPbJRYK = false;}
      if(YDGrEiXQLG == true){YDGrEiXQLG = false;}
      if(miarUDcVMP == true){miarUDcVMP = false;}
      if(DywzCxjWQN == true){DywzCxjWQN = false;}
      if(NiJTttMrnO == true){NiJTttMrnO = false;}
      if(YFwxzutEQL == true){YFwxzutEQL = false;}
      if(ynFJHZGGpG == true){ynFJHZGGpG = false;}
      if(yAzyrDYGxZ == true){yAzyrDYGxZ = false;}
      if(qkgxpxCzzH == true){qkgxpxCzzH = false;}
      if(DfGEOYdzMU == true){DfGEOYdzMU = false;}
      if(nFBgQXGxEu == true){nFBgQXGxEu = false;}
      if(VmGpTNGITK == true){VmGpTNGITK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOZVJUPQFY
{ 
  void ZkVJRpmtXU()
  { 
      bool hwUCGomIsx = false;
      bool hoLRVoAmWN = false;
      bool rwTNiYYuqO = false;
      bool DQGEiCPuNL = false;
      bool IxuZffNMZq = false;
      bool sryHdkbGSh = false;
      bool QqResQiHhT = false;
      bool ZFZLEtBshC = false;
      bool KLVzVLSyax = false;
      bool ZIbftRfQgO = false;
      bool xGdGRmRmCi = false;
      bool jiYQWEVRJg = false;
      bool yjfjsRdtQm = false;
      bool OjMSFEhPhh = false;
      bool tewqNpiKIo = false;
      bool uOHzPNZsMA = false;
      bool JXVPUAWGLS = false;
      bool WGiamSnoWC = false;
      bool hSkbqzcNCq = false;
      bool doChYVIgWN = false;
      string aHyNsUyUyl;
      string WXZhFGouzV;
      string VtkwVuTttI;
      string tihHjTkzuN;
      string PLzsonncIZ;
      string wBRXtfVCry;
      string AEaormoRxk;
      string UoAlFKurGg;
      string HqlTMrRKME;
      string yiHxNLjJBC;
      string yVeWFGBeRi;
      string jcuKpJRGcz;
      string VeEsmkgDXt;
      string ZlqEhlLOOF;
      string qlrdTUmxGE;
      string sdfBfTQljT;
      string YxHXIylqbE;
      string yDqXIilaZR;
      string yjxTBuGoXN;
      string VYeufseUUV;
      if(aHyNsUyUyl == yVeWFGBeRi){hwUCGomIsx = true;}
      else if(yVeWFGBeRi == aHyNsUyUyl){xGdGRmRmCi = true;}
      if(WXZhFGouzV == jcuKpJRGcz){hoLRVoAmWN = true;}
      else if(jcuKpJRGcz == WXZhFGouzV){jiYQWEVRJg = true;}
      if(VtkwVuTttI == VeEsmkgDXt){rwTNiYYuqO = true;}
      else if(VeEsmkgDXt == VtkwVuTttI){yjfjsRdtQm = true;}
      if(tihHjTkzuN == ZlqEhlLOOF){DQGEiCPuNL = true;}
      else if(ZlqEhlLOOF == tihHjTkzuN){OjMSFEhPhh = true;}
      if(PLzsonncIZ == qlrdTUmxGE){IxuZffNMZq = true;}
      else if(qlrdTUmxGE == PLzsonncIZ){tewqNpiKIo = true;}
      if(wBRXtfVCry == sdfBfTQljT){sryHdkbGSh = true;}
      else if(sdfBfTQljT == wBRXtfVCry){uOHzPNZsMA = true;}
      if(AEaormoRxk == YxHXIylqbE){QqResQiHhT = true;}
      else if(YxHXIylqbE == AEaormoRxk){JXVPUAWGLS = true;}
      if(UoAlFKurGg == yDqXIilaZR){ZFZLEtBshC = true;}
      if(HqlTMrRKME == yjxTBuGoXN){KLVzVLSyax = true;}
      if(yiHxNLjJBC == VYeufseUUV){ZIbftRfQgO = true;}
      while(yDqXIilaZR == UoAlFKurGg){WGiamSnoWC = true;}
      while(yjxTBuGoXN == yjxTBuGoXN){hSkbqzcNCq = true;}
      while(VYeufseUUV == VYeufseUUV){doChYVIgWN = true;}
      if(hwUCGomIsx == true){hwUCGomIsx = false;}
      if(hoLRVoAmWN == true){hoLRVoAmWN = false;}
      if(rwTNiYYuqO == true){rwTNiYYuqO = false;}
      if(DQGEiCPuNL == true){DQGEiCPuNL = false;}
      if(IxuZffNMZq == true){IxuZffNMZq = false;}
      if(sryHdkbGSh == true){sryHdkbGSh = false;}
      if(QqResQiHhT == true){QqResQiHhT = false;}
      if(ZFZLEtBshC == true){ZFZLEtBshC = false;}
      if(KLVzVLSyax == true){KLVzVLSyax = false;}
      if(ZIbftRfQgO == true){ZIbftRfQgO = false;}
      if(xGdGRmRmCi == true){xGdGRmRmCi = false;}
      if(jiYQWEVRJg == true){jiYQWEVRJg = false;}
      if(yjfjsRdtQm == true){yjfjsRdtQm = false;}
      if(OjMSFEhPhh == true){OjMSFEhPhh = false;}
      if(tewqNpiKIo == true){tewqNpiKIo = false;}
      if(uOHzPNZsMA == true){uOHzPNZsMA = false;}
      if(JXVPUAWGLS == true){JXVPUAWGLS = false;}
      if(WGiamSnoWC == true){WGiamSnoWC = false;}
      if(hSkbqzcNCq == true){hSkbqzcNCq = false;}
      if(doChYVIgWN == true){doChYVIgWN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKZATZOEHH
{ 
  void YjHjLaoYiH()
  { 
      bool znNBDMWLoo = false;
      bool KjhMrGylRO = false;
      bool PkcYyHQkAK = false;
      bool cIVoketGhy = false;
      bool UQbxtBCZwq = false;
      bool BjdLnOKoDw = false;
      bool ukLdLCNsbN = false;
      bool MrETtyIfdw = false;
      bool FqoIJsdKAW = false;
      bool TFClCjFykr = false;
      bool mJyieJeJQp = false;
      bool FeKGpEuCUR = false;
      bool XDrEsGoSRK = false;
      bool rKtlIwsFdz = false;
      bool NTsKRntuux = false;
      bool nCdTTiQtoX = false;
      bool UMrGxukYxt = false;
      bool KoYUEDKglE = false;
      bool MsWTWpgaSZ = false;
      bool ezQFeAbmNW = false;
      string KbAXYrPdYQ;
      string sbjiYLpCSy;
      string iVZxNsKHZi;
      string qtTeRUwATi;
      string OZLqjAPhmu;
      string FiqoDoBDKf;
      string gIEpZyIFRE;
      string OphjiJJiMM;
      string ccTedHCeab;
      string SsonBGVVRk;
      string rKQifPAHFt;
      string fSpxCEoYLR;
      string wcdokVAthc;
      string nmQaTSLkzN;
      string GuYgwACqlw;
      string RwJAoOgaxK;
      string PGYcGrBOdj;
      string rEZyKAEwsj;
      string SIIlLqcQlF;
      string lkmnyAWwaD;
      if(KbAXYrPdYQ == rKQifPAHFt){znNBDMWLoo = true;}
      else if(rKQifPAHFt == KbAXYrPdYQ){mJyieJeJQp = true;}
      if(sbjiYLpCSy == fSpxCEoYLR){KjhMrGylRO = true;}
      else if(fSpxCEoYLR == sbjiYLpCSy){FeKGpEuCUR = true;}
      if(iVZxNsKHZi == wcdokVAthc){PkcYyHQkAK = true;}
      else if(wcdokVAthc == iVZxNsKHZi){XDrEsGoSRK = true;}
      if(qtTeRUwATi == nmQaTSLkzN){cIVoketGhy = true;}
      else if(nmQaTSLkzN == qtTeRUwATi){rKtlIwsFdz = true;}
      if(OZLqjAPhmu == GuYgwACqlw){UQbxtBCZwq = true;}
      else if(GuYgwACqlw == OZLqjAPhmu){NTsKRntuux = true;}
      if(FiqoDoBDKf == RwJAoOgaxK){BjdLnOKoDw = true;}
      else if(RwJAoOgaxK == FiqoDoBDKf){nCdTTiQtoX = true;}
      if(gIEpZyIFRE == PGYcGrBOdj){ukLdLCNsbN = true;}
      else if(PGYcGrBOdj == gIEpZyIFRE){UMrGxukYxt = true;}
      if(OphjiJJiMM == rEZyKAEwsj){MrETtyIfdw = true;}
      if(ccTedHCeab == SIIlLqcQlF){FqoIJsdKAW = true;}
      if(SsonBGVVRk == lkmnyAWwaD){TFClCjFykr = true;}
      while(rEZyKAEwsj == OphjiJJiMM){KoYUEDKglE = true;}
      while(SIIlLqcQlF == SIIlLqcQlF){MsWTWpgaSZ = true;}
      while(lkmnyAWwaD == lkmnyAWwaD){ezQFeAbmNW = true;}
      if(znNBDMWLoo == true){znNBDMWLoo = false;}
      if(KjhMrGylRO == true){KjhMrGylRO = false;}
      if(PkcYyHQkAK == true){PkcYyHQkAK = false;}
      if(cIVoketGhy == true){cIVoketGhy = false;}
      if(UQbxtBCZwq == true){UQbxtBCZwq = false;}
      if(BjdLnOKoDw == true){BjdLnOKoDw = false;}
      if(ukLdLCNsbN == true){ukLdLCNsbN = false;}
      if(MrETtyIfdw == true){MrETtyIfdw = false;}
      if(FqoIJsdKAW == true){FqoIJsdKAW = false;}
      if(TFClCjFykr == true){TFClCjFykr = false;}
      if(mJyieJeJQp == true){mJyieJeJQp = false;}
      if(FeKGpEuCUR == true){FeKGpEuCUR = false;}
      if(XDrEsGoSRK == true){XDrEsGoSRK = false;}
      if(rKtlIwsFdz == true){rKtlIwsFdz = false;}
      if(NTsKRntuux == true){NTsKRntuux = false;}
      if(nCdTTiQtoX == true){nCdTTiQtoX = false;}
      if(UMrGxukYxt == true){UMrGxukYxt = false;}
      if(KoYUEDKglE == true){KoYUEDKglE = false;}
      if(MsWTWpgaSZ == true){MsWTWpgaSZ = false;}
      if(ezQFeAbmNW == true){ezQFeAbmNW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJCNMRDNPH
{ 
  void kZOIeKTNYM()
  { 
      bool xJVLCgYHdD = false;
      bool tgoZJPMFcp = false;
      bool qdYMXpDqDb = false;
      bool ezlhTyDxoX = false;
      bool UGnJKLbGUo = false;
      bool AcdeCTjJmL = false;
      bool dgDBYttHFK = false;
      bool MPPFVkpOCM = false;
      bool NwWNaBVGeA = false;
      bool NtJctnClkP = false;
      bool QTBJckNXJR = false;
      bool cUGZxhJpZW = false;
      bool YncFxRFlKg = false;
      bool hEdlwsuNkp = false;
      bool nxwMXsmjfL = false;
      bool dLLOpcqwMK = false;
      bool faNbiYqUdD = false;
      bool mwFjiaqQhD = false;
      bool eVGzDWrOuS = false;
      bool CzBZKNjUdy = false;
      string xlmTEyBgYL;
      string HpmVXrKOaF;
      string mRcbrYdRBX;
      string BhyyMkZlEW;
      string IoUAkopBpm;
      string aODCVeJKae;
      string TieBKYroIm;
      string SXJEwyxbqD;
      string hbaOxmeubg;
      string aOLYCZKTpL;
      string xBrDTCEzFW;
      string hgSXxrHPDW;
      string twMaLDMjBW;
      string mckfFgiXtu;
      string hfoFztwmbK;
      string RtPSRBnRqQ;
      string oUxiiEwmRQ;
      string IjVIoNGHbR;
      string HYIqFsNRNE;
      string rRgdFMiGVt;
      if(xlmTEyBgYL == xBrDTCEzFW){xJVLCgYHdD = true;}
      else if(xBrDTCEzFW == xlmTEyBgYL){QTBJckNXJR = true;}
      if(HpmVXrKOaF == hgSXxrHPDW){tgoZJPMFcp = true;}
      else if(hgSXxrHPDW == HpmVXrKOaF){cUGZxhJpZW = true;}
      if(mRcbrYdRBX == twMaLDMjBW){qdYMXpDqDb = true;}
      else if(twMaLDMjBW == mRcbrYdRBX){YncFxRFlKg = true;}
      if(BhyyMkZlEW == mckfFgiXtu){ezlhTyDxoX = true;}
      else if(mckfFgiXtu == BhyyMkZlEW){hEdlwsuNkp = true;}
      if(IoUAkopBpm == hfoFztwmbK){UGnJKLbGUo = true;}
      else if(hfoFztwmbK == IoUAkopBpm){nxwMXsmjfL = true;}
      if(aODCVeJKae == RtPSRBnRqQ){AcdeCTjJmL = true;}
      else if(RtPSRBnRqQ == aODCVeJKae){dLLOpcqwMK = true;}
      if(TieBKYroIm == oUxiiEwmRQ){dgDBYttHFK = true;}
      else if(oUxiiEwmRQ == TieBKYroIm){faNbiYqUdD = true;}
      if(SXJEwyxbqD == IjVIoNGHbR){MPPFVkpOCM = true;}
      if(hbaOxmeubg == HYIqFsNRNE){NwWNaBVGeA = true;}
      if(aOLYCZKTpL == rRgdFMiGVt){NtJctnClkP = true;}
      while(IjVIoNGHbR == SXJEwyxbqD){mwFjiaqQhD = true;}
      while(HYIqFsNRNE == HYIqFsNRNE){eVGzDWrOuS = true;}
      while(rRgdFMiGVt == rRgdFMiGVt){CzBZKNjUdy = true;}
      if(xJVLCgYHdD == true){xJVLCgYHdD = false;}
      if(tgoZJPMFcp == true){tgoZJPMFcp = false;}
      if(qdYMXpDqDb == true){qdYMXpDqDb = false;}
      if(ezlhTyDxoX == true){ezlhTyDxoX = false;}
      if(UGnJKLbGUo == true){UGnJKLbGUo = false;}
      if(AcdeCTjJmL == true){AcdeCTjJmL = false;}
      if(dgDBYttHFK == true){dgDBYttHFK = false;}
      if(MPPFVkpOCM == true){MPPFVkpOCM = false;}
      if(NwWNaBVGeA == true){NwWNaBVGeA = false;}
      if(NtJctnClkP == true){NtJctnClkP = false;}
      if(QTBJckNXJR == true){QTBJckNXJR = false;}
      if(cUGZxhJpZW == true){cUGZxhJpZW = false;}
      if(YncFxRFlKg == true){YncFxRFlKg = false;}
      if(hEdlwsuNkp == true){hEdlwsuNkp = false;}
      if(nxwMXsmjfL == true){nxwMXsmjfL = false;}
      if(dLLOpcqwMK == true){dLLOpcqwMK = false;}
      if(faNbiYqUdD == true){faNbiYqUdD = false;}
      if(mwFjiaqQhD == true){mwFjiaqQhD = false;}
      if(eVGzDWrOuS == true){eVGzDWrOuS = false;}
      if(CzBZKNjUdy == true){CzBZKNjUdy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SXMDIFDPYA
{ 
  void KBHwffgEiC()
  { 
      bool FCKUdwJwHW = false;
      bool DhpctlxUKR = false;
      bool lFDrAWBsZs = false;
      bool WNVbxioCJw = false;
      bool PoOPChoTnk = false;
      bool SkJASAzSTH = false;
      bool uPVNAoMNfL = false;
      bool xtLOCwpmpR = false;
      bool ggFoakEUIw = false;
      bool jWhBAATBPM = false;
      bool VanbmXZtxW = false;
      bool KLbCZNJglO = false;
      bool kqFibaLJNC = false;
      bool coXcuGscBC = false;
      bool KJXllYtfal = false;
      bool plOAbeUEAM = false;
      bool MPfusVmzGT = false;
      bool UfejDaTTxD = false;
      bool gfibLpZWBQ = false;
      bool kncopucbrQ = false;
      string dqQcwGOKTE;
      string FmJNwkjBcC;
      string lsZHAjQsqH;
      string sVQBTOgaBZ;
      string qxMYbPcdzP;
      string DdeBpkQJbL;
      string pUTLLiVIth;
      string DIzDKngBek;
      string HltaEPqPKh;
      string xXzpjVdANr;
      string sTiQLudbqB;
      string EPdpEDarHu;
      string rGxLkeIJTn;
      string KfnmrmCcPJ;
      string kOXJdhsIkf;
      string ulsRAlWXff;
      string lUIDqYbqyQ;
      string BycxKchnhD;
      string lzXmrYlVmF;
      string QewiWQGUSF;
      if(dqQcwGOKTE == sTiQLudbqB){FCKUdwJwHW = true;}
      else if(sTiQLudbqB == dqQcwGOKTE){VanbmXZtxW = true;}
      if(FmJNwkjBcC == EPdpEDarHu){DhpctlxUKR = true;}
      else if(EPdpEDarHu == FmJNwkjBcC){KLbCZNJglO = true;}
      if(lsZHAjQsqH == rGxLkeIJTn){lFDrAWBsZs = true;}
      else if(rGxLkeIJTn == lsZHAjQsqH){kqFibaLJNC = true;}
      if(sVQBTOgaBZ == KfnmrmCcPJ){WNVbxioCJw = true;}
      else if(KfnmrmCcPJ == sVQBTOgaBZ){coXcuGscBC = true;}
      if(qxMYbPcdzP == kOXJdhsIkf){PoOPChoTnk = true;}
      else if(kOXJdhsIkf == qxMYbPcdzP){KJXllYtfal = true;}
      if(DdeBpkQJbL == ulsRAlWXff){SkJASAzSTH = true;}
      else if(ulsRAlWXff == DdeBpkQJbL){plOAbeUEAM = true;}
      if(pUTLLiVIth == lUIDqYbqyQ){uPVNAoMNfL = true;}
      else if(lUIDqYbqyQ == pUTLLiVIth){MPfusVmzGT = true;}
      if(DIzDKngBek == BycxKchnhD){xtLOCwpmpR = true;}
      if(HltaEPqPKh == lzXmrYlVmF){ggFoakEUIw = true;}
      if(xXzpjVdANr == QewiWQGUSF){jWhBAATBPM = true;}
      while(BycxKchnhD == DIzDKngBek){UfejDaTTxD = true;}
      while(lzXmrYlVmF == lzXmrYlVmF){gfibLpZWBQ = true;}
      while(QewiWQGUSF == QewiWQGUSF){kncopucbrQ = true;}
      if(FCKUdwJwHW == true){FCKUdwJwHW = false;}
      if(DhpctlxUKR == true){DhpctlxUKR = false;}
      if(lFDrAWBsZs == true){lFDrAWBsZs = false;}
      if(WNVbxioCJw == true){WNVbxioCJw = false;}
      if(PoOPChoTnk == true){PoOPChoTnk = false;}
      if(SkJASAzSTH == true){SkJASAzSTH = false;}
      if(uPVNAoMNfL == true){uPVNAoMNfL = false;}
      if(xtLOCwpmpR == true){xtLOCwpmpR = false;}
      if(ggFoakEUIw == true){ggFoakEUIw = false;}
      if(jWhBAATBPM == true){jWhBAATBPM = false;}
      if(VanbmXZtxW == true){VanbmXZtxW = false;}
      if(KLbCZNJglO == true){KLbCZNJglO = false;}
      if(kqFibaLJNC == true){kqFibaLJNC = false;}
      if(coXcuGscBC == true){coXcuGscBC = false;}
      if(KJXllYtfal == true){KJXllYtfal = false;}
      if(plOAbeUEAM == true){plOAbeUEAM = false;}
      if(MPfusVmzGT == true){MPfusVmzGT = false;}
      if(UfejDaTTxD == true){UfejDaTTxD = false;}
      if(gfibLpZWBQ == true){gfibLpZWBQ = false;}
      if(kncopucbrQ == true){kncopucbrQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGVYTERPWC
{ 
  void hpQmhmKRpY()
  { 
      bool uOqICyJsmD = false;
      bool GqGfsHDeig = false;
      bool dQJNRNAapr = false;
      bool kIGcbmBoXd = false;
      bool CuOpWoTNsU = false;
      bool xbBaceFdqo = false;
      bool yiCtSxjcDF = false;
      bool GNHFeiBSpb = false;
      bool tmgUuIGfAx = false;
      bool hXyhfTrTXZ = false;
      bool FpJnOiUwut = false;
      bool clmOtKBhzJ = false;
      bool pDcGXhPYZL = false;
      bool phuQWDcsGL = false;
      bool nKjFTujinU = false;
      bool RKTNiBNDPf = false;
      bool TuWjEupWrp = false;
      bool gIanVeSWlb = false;
      bool yfkEseNhgU = false;
      bool pZcZrsnABY = false;
      string JERibDIfRT;
      string HrEjaZZlfT;
      string KbsgpeddoN;
      string NSTIcZuuoT;
      string NIOhpSTKqs;
      string GEimdhLjrw;
      string YdqEFoYuHA;
      string edxMFBMKqX;
      string LTmwGJjfdu;
      string OLCrujRKcB;
      string sXCpObGWhc;
      string UAsUkEquxw;
      string FrRLlTaFQV;
      string iBhodmQxgd;
      string CMyBaNRhGp;
      string rWMfwAGqDt;
      string BBFMsSSDpy;
      string mtNTsrtPkX;
      string BsyZcLoBsc;
      string fZsmcAHkIH;
      if(JERibDIfRT == sXCpObGWhc){uOqICyJsmD = true;}
      else if(sXCpObGWhc == JERibDIfRT){FpJnOiUwut = true;}
      if(HrEjaZZlfT == UAsUkEquxw){GqGfsHDeig = true;}
      else if(UAsUkEquxw == HrEjaZZlfT){clmOtKBhzJ = true;}
      if(KbsgpeddoN == FrRLlTaFQV){dQJNRNAapr = true;}
      else if(FrRLlTaFQV == KbsgpeddoN){pDcGXhPYZL = true;}
      if(NSTIcZuuoT == iBhodmQxgd){kIGcbmBoXd = true;}
      else if(iBhodmQxgd == NSTIcZuuoT){phuQWDcsGL = true;}
      if(NIOhpSTKqs == CMyBaNRhGp){CuOpWoTNsU = true;}
      else if(CMyBaNRhGp == NIOhpSTKqs){nKjFTujinU = true;}
      if(GEimdhLjrw == rWMfwAGqDt){xbBaceFdqo = true;}
      else if(rWMfwAGqDt == GEimdhLjrw){RKTNiBNDPf = true;}
      if(YdqEFoYuHA == BBFMsSSDpy){yiCtSxjcDF = true;}
      else if(BBFMsSSDpy == YdqEFoYuHA){TuWjEupWrp = true;}
      if(edxMFBMKqX == mtNTsrtPkX){GNHFeiBSpb = true;}
      if(LTmwGJjfdu == BsyZcLoBsc){tmgUuIGfAx = true;}
      if(OLCrujRKcB == fZsmcAHkIH){hXyhfTrTXZ = true;}
      while(mtNTsrtPkX == edxMFBMKqX){gIanVeSWlb = true;}
      while(BsyZcLoBsc == BsyZcLoBsc){yfkEseNhgU = true;}
      while(fZsmcAHkIH == fZsmcAHkIH){pZcZrsnABY = true;}
      if(uOqICyJsmD == true){uOqICyJsmD = false;}
      if(GqGfsHDeig == true){GqGfsHDeig = false;}
      if(dQJNRNAapr == true){dQJNRNAapr = false;}
      if(kIGcbmBoXd == true){kIGcbmBoXd = false;}
      if(CuOpWoTNsU == true){CuOpWoTNsU = false;}
      if(xbBaceFdqo == true){xbBaceFdqo = false;}
      if(yiCtSxjcDF == true){yiCtSxjcDF = false;}
      if(GNHFeiBSpb == true){GNHFeiBSpb = false;}
      if(tmgUuIGfAx == true){tmgUuIGfAx = false;}
      if(hXyhfTrTXZ == true){hXyhfTrTXZ = false;}
      if(FpJnOiUwut == true){FpJnOiUwut = false;}
      if(clmOtKBhzJ == true){clmOtKBhzJ = false;}
      if(pDcGXhPYZL == true){pDcGXhPYZL = false;}
      if(phuQWDcsGL == true){phuQWDcsGL = false;}
      if(nKjFTujinU == true){nKjFTujinU = false;}
      if(RKTNiBNDPf == true){RKTNiBNDPf = false;}
      if(TuWjEupWrp == true){TuWjEupWrp = false;}
      if(gIanVeSWlb == true){gIanVeSWlb = false;}
      if(yfkEseNhgU == true){yfkEseNhgU = false;}
      if(pZcZrsnABY == true){pZcZrsnABY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSSKLXJLNI
{ 
  void jWVKBRVAEO()
  { 
      bool XitarjXQSb = false;
      bool PGpCaJphdF = false;
      bool mFquxbkKSu = false;
      bool rIKkOCAGcD = false;
      bool ILDsQTLIuo = false;
      bool izgFbRqycP = false;
      bool yMyXjHwEnY = false;
      bool IiEZxbCxed = false;
      bool PcPcMsaEIx = false;
      bool KBdMFuMfJI = false;
      bool XHUVfztGIA = false;
      bool OsTzAUxULp = false;
      bool fqwpNGFrUB = false;
      bool OWnWGIIswM = false;
      bool yUwIhQhdLj = false;
      bool yqTSbfKdHZ = false;
      bool sBkHlrFwsq = false;
      bool MDXyrLumIx = false;
      bool XafkCWCUta = false;
      bool xdlWTwjnVo = false;
      string rezXPPFbNa;
      string zJjdNOfNZB;
      string PFefklYejW;
      string LMywrmABFl;
      string DKrSxpkICI;
      string zMhjamzSmd;
      string pZqpPmKnkZ;
      string OeInxEMMhu;
      string AQcbWzdOUF;
      string mgNbudTBCK;
      string ewWbsUDtlW;
      string ZmkrcYxOTP;
      string IwTfmgQfrT;
      string kKJXPDtAhC;
      string uicxeAwVzW;
      string fEhmBicqoM;
      string DWCRlPcNbY;
      string ewgQTYSVAl;
      string ktgUmfcWVf;
      string aCKVyYgKLP;
      if(rezXPPFbNa == ewWbsUDtlW){XitarjXQSb = true;}
      else if(ewWbsUDtlW == rezXPPFbNa){XHUVfztGIA = true;}
      if(zJjdNOfNZB == ZmkrcYxOTP){PGpCaJphdF = true;}
      else if(ZmkrcYxOTP == zJjdNOfNZB){OsTzAUxULp = true;}
      if(PFefklYejW == IwTfmgQfrT){mFquxbkKSu = true;}
      else if(IwTfmgQfrT == PFefklYejW){fqwpNGFrUB = true;}
      if(LMywrmABFl == kKJXPDtAhC){rIKkOCAGcD = true;}
      else if(kKJXPDtAhC == LMywrmABFl){OWnWGIIswM = true;}
      if(DKrSxpkICI == uicxeAwVzW){ILDsQTLIuo = true;}
      else if(uicxeAwVzW == DKrSxpkICI){yUwIhQhdLj = true;}
      if(zMhjamzSmd == fEhmBicqoM){izgFbRqycP = true;}
      else if(fEhmBicqoM == zMhjamzSmd){yqTSbfKdHZ = true;}
      if(pZqpPmKnkZ == DWCRlPcNbY){yMyXjHwEnY = true;}
      else if(DWCRlPcNbY == pZqpPmKnkZ){sBkHlrFwsq = true;}
      if(OeInxEMMhu == ewgQTYSVAl){IiEZxbCxed = true;}
      if(AQcbWzdOUF == ktgUmfcWVf){PcPcMsaEIx = true;}
      if(mgNbudTBCK == aCKVyYgKLP){KBdMFuMfJI = true;}
      while(ewgQTYSVAl == OeInxEMMhu){MDXyrLumIx = true;}
      while(ktgUmfcWVf == ktgUmfcWVf){XafkCWCUta = true;}
      while(aCKVyYgKLP == aCKVyYgKLP){xdlWTwjnVo = true;}
      if(XitarjXQSb == true){XitarjXQSb = false;}
      if(PGpCaJphdF == true){PGpCaJphdF = false;}
      if(mFquxbkKSu == true){mFquxbkKSu = false;}
      if(rIKkOCAGcD == true){rIKkOCAGcD = false;}
      if(ILDsQTLIuo == true){ILDsQTLIuo = false;}
      if(izgFbRqycP == true){izgFbRqycP = false;}
      if(yMyXjHwEnY == true){yMyXjHwEnY = false;}
      if(IiEZxbCxed == true){IiEZxbCxed = false;}
      if(PcPcMsaEIx == true){PcPcMsaEIx = false;}
      if(KBdMFuMfJI == true){KBdMFuMfJI = false;}
      if(XHUVfztGIA == true){XHUVfztGIA = false;}
      if(OsTzAUxULp == true){OsTzAUxULp = false;}
      if(fqwpNGFrUB == true){fqwpNGFrUB = false;}
      if(OWnWGIIswM == true){OWnWGIIswM = false;}
      if(yUwIhQhdLj == true){yUwIhQhdLj = false;}
      if(yqTSbfKdHZ == true){yqTSbfKdHZ = false;}
      if(sBkHlrFwsq == true){sBkHlrFwsq = false;}
      if(MDXyrLumIx == true){MDXyrLumIx = false;}
      if(XafkCWCUta == true){XafkCWCUta = false;}
      if(xdlWTwjnVo == true){xdlWTwjnVo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THIJSGEUAH
{ 
  void znuGqEyeVB()
  { 
      bool kQJzFkOdMf = false;
      bool NBjxOqcdSl = false;
      bool jfrScQfEkR = false;
      bool RQRokNKfus = false;
      bool JxlYRDAztZ = false;
      bool PDJIgEYqWo = false;
      bool FKrtOwiuMA = false;
      bool gwhYcltSAY = false;
      bool PfJLCNHJHf = false;
      bool oSJGnyEqJV = false;
      bool UFltrSUjft = false;
      bool KFqyZYAgrB = false;
      bool nYnfKOmbjd = false;
      bool hCIdDKtPSi = false;
      bool rWcMUibLgP = false;
      bool yWyIguQGid = false;
      bool fszCMHwMtO = false;
      bool ekOJIRwbKb = false;
      bool mbuUfKEAwH = false;
      bool tmgnCzWazN = false;
      string UkzWLluZbi;
      string FotPcxOfKU;
      string ogdnXLGfTc;
      string unFOjYHriQ;
      string VxLXKKLFKc;
      string LUjoAnGLyA;
      string ePGymQjfeE;
      string oWxtzqUFdN;
      string zBVpRaDPNw;
      string RwsikGqMjs;
      string afZFmnXopJ;
      string SBhkAcsPfM;
      string NTRilscOJr;
      string zHVjmSbPCd;
      string CNZEcQOIhH;
      string NbgWeGNpTt;
      string LJfxJLexyh;
      string BcMCKzsMGV;
      string eTfBeXayEf;
      string EkwIRrhbtR;
      if(UkzWLluZbi == afZFmnXopJ){kQJzFkOdMf = true;}
      else if(afZFmnXopJ == UkzWLluZbi){UFltrSUjft = true;}
      if(FotPcxOfKU == SBhkAcsPfM){NBjxOqcdSl = true;}
      else if(SBhkAcsPfM == FotPcxOfKU){KFqyZYAgrB = true;}
      if(ogdnXLGfTc == NTRilscOJr){jfrScQfEkR = true;}
      else if(NTRilscOJr == ogdnXLGfTc){nYnfKOmbjd = true;}
      if(unFOjYHriQ == zHVjmSbPCd){RQRokNKfus = true;}
      else if(zHVjmSbPCd == unFOjYHriQ){hCIdDKtPSi = true;}
      if(VxLXKKLFKc == CNZEcQOIhH){JxlYRDAztZ = true;}
      else if(CNZEcQOIhH == VxLXKKLFKc){rWcMUibLgP = true;}
      if(LUjoAnGLyA == NbgWeGNpTt){PDJIgEYqWo = true;}
      else if(NbgWeGNpTt == LUjoAnGLyA){yWyIguQGid = true;}
      if(ePGymQjfeE == LJfxJLexyh){FKrtOwiuMA = true;}
      else if(LJfxJLexyh == ePGymQjfeE){fszCMHwMtO = true;}
      if(oWxtzqUFdN == BcMCKzsMGV){gwhYcltSAY = true;}
      if(zBVpRaDPNw == eTfBeXayEf){PfJLCNHJHf = true;}
      if(RwsikGqMjs == EkwIRrhbtR){oSJGnyEqJV = true;}
      while(BcMCKzsMGV == oWxtzqUFdN){ekOJIRwbKb = true;}
      while(eTfBeXayEf == eTfBeXayEf){mbuUfKEAwH = true;}
      while(EkwIRrhbtR == EkwIRrhbtR){tmgnCzWazN = true;}
      if(kQJzFkOdMf == true){kQJzFkOdMf = false;}
      if(NBjxOqcdSl == true){NBjxOqcdSl = false;}
      if(jfrScQfEkR == true){jfrScQfEkR = false;}
      if(RQRokNKfus == true){RQRokNKfus = false;}
      if(JxlYRDAztZ == true){JxlYRDAztZ = false;}
      if(PDJIgEYqWo == true){PDJIgEYqWo = false;}
      if(FKrtOwiuMA == true){FKrtOwiuMA = false;}
      if(gwhYcltSAY == true){gwhYcltSAY = false;}
      if(PfJLCNHJHf == true){PfJLCNHJHf = false;}
      if(oSJGnyEqJV == true){oSJGnyEqJV = false;}
      if(UFltrSUjft == true){UFltrSUjft = false;}
      if(KFqyZYAgrB == true){KFqyZYAgrB = false;}
      if(nYnfKOmbjd == true){nYnfKOmbjd = false;}
      if(hCIdDKtPSi == true){hCIdDKtPSi = false;}
      if(rWcMUibLgP == true){rWcMUibLgP = false;}
      if(yWyIguQGid == true){yWyIguQGid = false;}
      if(fszCMHwMtO == true){fszCMHwMtO = false;}
      if(ekOJIRwbKb == true){ekOJIRwbKb = false;}
      if(mbuUfKEAwH == true){mbuUfKEAwH = false;}
      if(tmgnCzWazN == true){tmgnCzWazN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDABXSPEAE
{ 
  void KBcSfpCdNc()
  { 
      bool LNsotNnOik = false;
      bool xMVWPAolbp = false;
      bool ogqPOdAlaJ = false;
      bool RqlbLwVKfO = false;
      bool VjkChzPybl = false;
      bool oZXKEeVcaP = false;
      bool MCmZTGatKS = false;
      bool eeFNUFuogO = false;
      bool NCKnTqSaWg = false;
      bool asiPBSwLhb = false;
      bool YVnIHKTKoz = false;
      bool jfuMCKrzFb = false;
      bool mzWdrluoLB = false;
      bool JiGFoqNBgJ = false;
      bool WIkXwtxWNq = false;
      bool awFGnYzJQU = false;
      bool OeynoBZpWK = false;
      bool wpSwEeNygy = false;
      bool nYbUZMcAQQ = false;
      bool rEjLtrJxhu = false;
      string pBNeuuGlmd;
      string elKkQLiLOr;
      string jFjJIGZVAy;
      string xHUriXfarZ;
      string IxiMnCGzYH;
      string bYlzOkRDVn;
      string VklngWRRCr;
      string eITojmVXUG;
      string AaxrWYUUdx;
      string GbEDEXKtfR;
      string knwfbSExPb;
      string PsiPmtmsRI;
      string BwnEkDDPjL;
      string barDUMdQPD;
      string TXEBhNsnQJ;
      string jRcWPozruY;
      string PoMEAnBfua;
      string PWcOndqmVX;
      string JOzZbJyUnf;
      string MlVqmeLABt;
      if(pBNeuuGlmd == knwfbSExPb){LNsotNnOik = true;}
      else if(knwfbSExPb == pBNeuuGlmd){YVnIHKTKoz = true;}
      if(elKkQLiLOr == PsiPmtmsRI){xMVWPAolbp = true;}
      else if(PsiPmtmsRI == elKkQLiLOr){jfuMCKrzFb = true;}
      if(jFjJIGZVAy == BwnEkDDPjL){ogqPOdAlaJ = true;}
      else if(BwnEkDDPjL == jFjJIGZVAy){mzWdrluoLB = true;}
      if(xHUriXfarZ == barDUMdQPD){RqlbLwVKfO = true;}
      else if(barDUMdQPD == xHUriXfarZ){JiGFoqNBgJ = true;}
      if(IxiMnCGzYH == TXEBhNsnQJ){VjkChzPybl = true;}
      else if(TXEBhNsnQJ == IxiMnCGzYH){WIkXwtxWNq = true;}
      if(bYlzOkRDVn == jRcWPozruY){oZXKEeVcaP = true;}
      else if(jRcWPozruY == bYlzOkRDVn){awFGnYzJQU = true;}
      if(VklngWRRCr == PoMEAnBfua){MCmZTGatKS = true;}
      else if(PoMEAnBfua == VklngWRRCr){OeynoBZpWK = true;}
      if(eITojmVXUG == PWcOndqmVX){eeFNUFuogO = true;}
      if(AaxrWYUUdx == JOzZbJyUnf){NCKnTqSaWg = true;}
      if(GbEDEXKtfR == MlVqmeLABt){asiPBSwLhb = true;}
      while(PWcOndqmVX == eITojmVXUG){wpSwEeNygy = true;}
      while(JOzZbJyUnf == JOzZbJyUnf){nYbUZMcAQQ = true;}
      while(MlVqmeLABt == MlVqmeLABt){rEjLtrJxhu = true;}
      if(LNsotNnOik == true){LNsotNnOik = false;}
      if(xMVWPAolbp == true){xMVWPAolbp = false;}
      if(ogqPOdAlaJ == true){ogqPOdAlaJ = false;}
      if(RqlbLwVKfO == true){RqlbLwVKfO = false;}
      if(VjkChzPybl == true){VjkChzPybl = false;}
      if(oZXKEeVcaP == true){oZXKEeVcaP = false;}
      if(MCmZTGatKS == true){MCmZTGatKS = false;}
      if(eeFNUFuogO == true){eeFNUFuogO = false;}
      if(NCKnTqSaWg == true){NCKnTqSaWg = false;}
      if(asiPBSwLhb == true){asiPBSwLhb = false;}
      if(YVnIHKTKoz == true){YVnIHKTKoz = false;}
      if(jfuMCKrzFb == true){jfuMCKrzFb = false;}
      if(mzWdrluoLB == true){mzWdrluoLB = false;}
      if(JiGFoqNBgJ == true){JiGFoqNBgJ = false;}
      if(WIkXwtxWNq == true){WIkXwtxWNq = false;}
      if(awFGnYzJQU == true){awFGnYzJQU = false;}
      if(OeynoBZpWK == true){OeynoBZpWK = false;}
      if(wpSwEeNygy == true){wpSwEeNygy = false;}
      if(nYbUZMcAQQ == true){nYbUZMcAQQ = false;}
      if(rEjLtrJxhu == true){rEjLtrJxhu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIFKNQDIKG
{ 
  void eSMdmbIhHw()
  { 
      bool ciRnuaPZrd = false;
      bool xisjPRZmZH = false;
      bool LTidWpTttl = false;
      bool yOxTdkNWdj = false;
      bool doqJACKBlg = false;
      bool SnEiyJzmRF = false;
      bool GVeFeilYFe = false;
      bool DCIodVbZcT = false;
      bool fSHMTKJNUU = false;
      bool kZFYdHJkdR = false;
      bool QkuGdPePFc = false;
      bool gZKyYmOSlU = false;
      bool YXEktcxjLV = false;
      bool LpuKCtXBiD = false;
      bool fsIqmLPHzp = false;
      bool sqzJssfKMA = false;
      bool StEiQpezwe = false;
      bool PMihneONxi = false;
      bool MpkVbUqkRI = false;
      bool ONnhkloYax = false;
      string KIdlkhNema;
      string oVszbuxUMH;
      string VKHDiDCXCb;
      string qNWJrtxNxn;
      string DVTRsxnrOG;
      string HRzfHzBaCg;
      string epbKiaziHh;
      string xjXXEzqpJl;
      string OKIuTYOqBs;
      string sWKPJMsIhR;
      string yFkfJXtabI;
      string ILQQSTggpK;
      string MIgNoZZIOq;
      string GhHrnJZbkw;
      string emOsjgGtxo;
      string fLSXEpXWqi;
      string xlMkCZDXbI;
      string sEuseZsndH;
      string TfLYKtOjny;
      string lDkBzsadqJ;
      if(KIdlkhNema == yFkfJXtabI){ciRnuaPZrd = true;}
      else if(yFkfJXtabI == KIdlkhNema){QkuGdPePFc = true;}
      if(oVszbuxUMH == ILQQSTggpK){xisjPRZmZH = true;}
      else if(ILQQSTggpK == oVszbuxUMH){gZKyYmOSlU = true;}
      if(VKHDiDCXCb == MIgNoZZIOq){LTidWpTttl = true;}
      else if(MIgNoZZIOq == VKHDiDCXCb){YXEktcxjLV = true;}
      if(qNWJrtxNxn == GhHrnJZbkw){yOxTdkNWdj = true;}
      else if(GhHrnJZbkw == qNWJrtxNxn){LpuKCtXBiD = true;}
      if(DVTRsxnrOG == emOsjgGtxo){doqJACKBlg = true;}
      else if(emOsjgGtxo == DVTRsxnrOG){fsIqmLPHzp = true;}
      if(HRzfHzBaCg == fLSXEpXWqi){SnEiyJzmRF = true;}
      else if(fLSXEpXWqi == HRzfHzBaCg){sqzJssfKMA = true;}
      if(epbKiaziHh == xlMkCZDXbI){GVeFeilYFe = true;}
      else if(xlMkCZDXbI == epbKiaziHh){StEiQpezwe = true;}
      if(xjXXEzqpJl == sEuseZsndH){DCIodVbZcT = true;}
      if(OKIuTYOqBs == TfLYKtOjny){fSHMTKJNUU = true;}
      if(sWKPJMsIhR == lDkBzsadqJ){kZFYdHJkdR = true;}
      while(sEuseZsndH == xjXXEzqpJl){PMihneONxi = true;}
      while(TfLYKtOjny == TfLYKtOjny){MpkVbUqkRI = true;}
      while(lDkBzsadqJ == lDkBzsadqJ){ONnhkloYax = true;}
      if(ciRnuaPZrd == true){ciRnuaPZrd = false;}
      if(xisjPRZmZH == true){xisjPRZmZH = false;}
      if(LTidWpTttl == true){LTidWpTttl = false;}
      if(yOxTdkNWdj == true){yOxTdkNWdj = false;}
      if(doqJACKBlg == true){doqJACKBlg = false;}
      if(SnEiyJzmRF == true){SnEiyJzmRF = false;}
      if(GVeFeilYFe == true){GVeFeilYFe = false;}
      if(DCIodVbZcT == true){DCIodVbZcT = false;}
      if(fSHMTKJNUU == true){fSHMTKJNUU = false;}
      if(kZFYdHJkdR == true){kZFYdHJkdR = false;}
      if(QkuGdPePFc == true){QkuGdPePFc = false;}
      if(gZKyYmOSlU == true){gZKyYmOSlU = false;}
      if(YXEktcxjLV == true){YXEktcxjLV = false;}
      if(LpuKCtXBiD == true){LpuKCtXBiD = false;}
      if(fsIqmLPHzp == true){fsIqmLPHzp = false;}
      if(sqzJssfKMA == true){sqzJssfKMA = false;}
      if(StEiQpezwe == true){StEiQpezwe = false;}
      if(PMihneONxi == true){PMihneONxi = false;}
      if(MpkVbUqkRI == true){MpkVbUqkRI = false;}
      if(ONnhkloYax == true){ONnhkloYax = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCKCDPVPLN
{ 
  void ufGTItGihg()
  { 
      bool tnGAEoaxdr = false;
      bool ToyoHqEWQC = false;
      bool HsFodjhWdZ = false;
      bool BjMMqbfqLV = false;
      bool dsZDgskKIK = false;
      bool GfNTyAhRVT = false;
      bool GDSDpjclxe = false;
      bool LNKuYOSBHk = false;
      bool zXOSTVWsNp = false;
      bool sNVrOZZVMw = false;
      bool QyMdzsURtj = false;
      bool ggJjTioAiU = false;
      bool NjXHkxrSgy = false;
      bool nxnLUBKjSa = false;
      bool AEydIMEkXe = false;
      bool jZmrifZFrC = false;
      bool BBkwujryPS = false;
      bool XEhITIktyY = false;
      bool sGuBNOKwbn = false;
      bool aFrQZyTChX = false;
      string jUipYgzbXx;
      string yhUsbLpqlk;
      string tHfzcGWNjP;
      string xguxztUjCD;
      string TixGLpKhjS;
      string UpMcobojMR;
      string JlrHzRmWth;
      string pGoiQLJZnm;
      string wocQtHURIW;
      string FkWjshppGt;
      string DmnCcNAcLc;
      string ROuZVUJbMr;
      string wUOWbFjFoi;
      string UTStiIAamg;
      string GqGeEpoxNY;
      string XOcOxhYQaW;
      string dunbIywBpN;
      string TinfkFOiSk;
      string PmqQKFpDwB;
      string iiAQCKDdWG;
      if(jUipYgzbXx == DmnCcNAcLc){tnGAEoaxdr = true;}
      else if(DmnCcNAcLc == jUipYgzbXx){QyMdzsURtj = true;}
      if(yhUsbLpqlk == ROuZVUJbMr){ToyoHqEWQC = true;}
      else if(ROuZVUJbMr == yhUsbLpqlk){ggJjTioAiU = true;}
      if(tHfzcGWNjP == wUOWbFjFoi){HsFodjhWdZ = true;}
      else if(wUOWbFjFoi == tHfzcGWNjP){NjXHkxrSgy = true;}
      if(xguxztUjCD == UTStiIAamg){BjMMqbfqLV = true;}
      else if(UTStiIAamg == xguxztUjCD){nxnLUBKjSa = true;}
      if(TixGLpKhjS == GqGeEpoxNY){dsZDgskKIK = true;}
      else if(GqGeEpoxNY == TixGLpKhjS){AEydIMEkXe = true;}
      if(UpMcobojMR == XOcOxhYQaW){GfNTyAhRVT = true;}
      else if(XOcOxhYQaW == UpMcobojMR){jZmrifZFrC = true;}
      if(JlrHzRmWth == dunbIywBpN){GDSDpjclxe = true;}
      else if(dunbIywBpN == JlrHzRmWth){BBkwujryPS = true;}
      if(pGoiQLJZnm == TinfkFOiSk){LNKuYOSBHk = true;}
      if(wocQtHURIW == PmqQKFpDwB){zXOSTVWsNp = true;}
      if(FkWjshppGt == iiAQCKDdWG){sNVrOZZVMw = true;}
      while(TinfkFOiSk == pGoiQLJZnm){XEhITIktyY = true;}
      while(PmqQKFpDwB == PmqQKFpDwB){sGuBNOKwbn = true;}
      while(iiAQCKDdWG == iiAQCKDdWG){aFrQZyTChX = true;}
      if(tnGAEoaxdr == true){tnGAEoaxdr = false;}
      if(ToyoHqEWQC == true){ToyoHqEWQC = false;}
      if(HsFodjhWdZ == true){HsFodjhWdZ = false;}
      if(BjMMqbfqLV == true){BjMMqbfqLV = false;}
      if(dsZDgskKIK == true){dsZDgskKIK = false;}
      if(GfNTyAhRVT == true){GfNTyAhRVT = false;}
      if(GDSDpjclxe == true){GDSDpjclxe = false;}
      if(LNKuYOSBHk == true){LNKuYOSBHk = false;}
      if(zXOSTVWsNp == true){zXOSTVWsNp = false;}
      if(sNVrOZZVMw == true){sNVrOZZVMw = false;}
      if(QyMdzsURtj == true){QyMdzsURtj = false;}
      if(ggJjTioAiU == true){ggJjTioAiU = false;}
      if(NjXHkxrSgy == true){NjXHkxrSgy = false;}
      if(nxnLUBKjSa == true){nxnLUBKjSa = false;}
      if(AEydIMEkXe == true){AEydIMEkXe = false;}
      if(jZmrifZFrC == true){jZmrifZFrC = false;}
      if(BBkwujryPS == true){BBkwujryPS = false;}
      if(XEhITIktyY == true){XEhITIktyY = false;}
      if(sGuBNOKwbn == true){sGuBNOKwbn = false;}
      if(aFrQZyTChX == true){aFrQZyTChX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVNNKPGHKZ
{ 
  void UaFMLpFTzT()
  { 
      bool WccKbhFZiE = false;
      bool dtXLtlgYrM = false;
      bool shOdpaXpYI = false;
      bool ZZylZQAyZM = false;
      bool gwlWatbFPK = false;
      bool ajqdLoOyUB = false;
      bool JPBadEulld = false;
      bool khzeexwqDu = false;
      bool ySaOhphUZj = false;
      bool BBdYDRuKrW = false;
      bool zpTlYrjMyO = false;
      bool sXuYDqnlsn = false;
      bool VZMCbiDZbN = false;
      bool BkygwIzopo = false;
      bool FVWKpdGEVM = false;
      bool cIREAYcQJo = false;
      bool oKjjMIYOct = false;
      bool qywEhADBLx = false;
      bool czEPjsStfW = false;
      bool eheAzuklxg = false;
      string HUmaxZcqud;
      string kynDfeuWdN;
      string KbJOoJoHnu;
      string XzobkJuVfe;
      string IJeWsdYwCl;
      string dhgLsfLYkm;
      string jUCAGlJLSV;
      string jYqzFAxlUL;
      string ksFBRoRchE;
      string yWjrtmHdQG;
      string TMcfCEpgFs;
      string iYDZCqPAhQ;
      string TgdNWNnzFS;
      string sSVNqXPZzM;
      string zkWoVZSKoD;
      string XGuAmmiPIo;
      string PqbmzQCohe;
      string aoAVQiJoqx;
      string tdJCumWUaE;
      string oAQJwIIjpF;
      if(HUmaxZcqud == TMcfCEpgFs){WccKbhFZiE = true;}
      else if(TMcfCEpgFs == HUmaxZcqud){zpTlYrjMyO = true;}
      if(kynDfeuWdN == iYDZCqPAhQ){dtXLtlgYrM = true;}
      else if(iYDZCqPAhQ == kynDfeuWdN){sXuYDqnlsn = true;}
      if(KbJOoJoHnu == TgdNWNnzFS){shOdpaXpYI = true;}
      else if(TgdNWNnzFS == KbJOoJoHnu){VZMCbiDZbN = true;}
      if(XzobkJuVfe == sSVNqXPZzM){ZZylZQAyZM = true;}
      else if(sSVNqXPZzM == XzobkJuVfe){BkygwIzopo = true;}
      if(IJeWsdYwCl == zkWoVZSKoD){gwlWatbFPK = true;}
      else if(zkWoVZSKoD == IJeWsdYwCl){FVWKpdGEVM = true;}
      if(dhgLsfLYkm == XGuAmmiPIo){ajqdLoOyUB = true;}
      else if(XGuAmmiPIo == dhgLsfLYkm){cIREAYcQJo = true;}
      if(jUCAGlJLSV == PqbmzQCohe){JPBadEulld = true;}
      else if(PqbmzQCohe == jUCAGlJLSV){oKjjMIYOct = true;}
      if(jYqzFAxlUL == aoAVQiJoqx){khzeexwqDu = true;}
      if(ksFBRoRchE == tdJCumWUaE){ySaOhphUZj = true;}
      if(yWjrtmHdQG == oAQJwIIjpF){BBdYDRuKrW = true;}
      while(aoAVQiJoqx == jYqzFAxlUL){qywEhADBLx = true;}
      while(tdJCumWUaE == tdJCumWUaE){czEPjsStfW = true;}
      while(oAQJwIIjpF == oAQJwIIjpF){eheAzuklxg = true;}
      if(WccKbhFZiE == true){WccKbhFZiE = false;}
      if(dtXLtlgYrM == true){dtXLtlgYrM = false;}
      if(shOdpaXpYI == true){shOdpaXpYI = false;}
      if(ZZylZQAyZM == true){ZZylZQAyZM = false;}
      if(gwlWatbFPK == true){gwlWatbFPK = false;}
      if(ajqdLoOyUB == true){ajqdLoOyUB = false;}
      if(JPBadEulld == true){JPBadEulld = false;}
      if(khzeexwqDu == true){khzeexwqDu = false;}
      if(ySaOhphUZj == true){ySaOhphUZj = false;}
      if(BBdYDRuKrW == true){BBdYDRuKrW = false;}
      if(zpTlYrjMyO == true){zpTlYrjMyO = false;}
      if(sXuYDqnlsn == true){sXuYDqnlsn = false;}
      if(VZMCbiDZbN == true){VZMCbiDZbN = false;}
      if(BkygwIzopo == true){BkygwIzopo = false;}
      if(FVWKpdGEVM == true){FVWKpdGEVM = false;}
      if(cIREAYcQJo == true){cIREAYcQJo = false;}
      if(oKjjMIYOct == true){oKjjMIYOct = false;}
      if(qywEhADBLx == true){qywEhADBLx = false;}
      if(czEPjsStfW == true){czEPjsStfW = false;}
      if(eheAzuklxg == true){eheAzuklxg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PONDICLJEQ
{ 
  void yGfkSwjiVU()
  { 
      bool BsnMCpIBxn = false;
      bool TudAnunQrZ = false;
      bool IpRTNcqeoj = false;
      bool WlnVzICmXk = false;
      bool LBnQCoHaKA = false;
      bool JdXYzLbTzZ = false;
      bool ycMMRhHHAf = false;
      bool sAsHOHBARX = false;
      bool UQTnZrOOVn = false;
      bool fhnxmhnazU = false;
      bool gAZeHIjQKr = false;
      bool JaBbFgIYlY = false;
      bool SskMzKMwTg = false;
      bool TaBxqUqofQ = false;
      bool IyDdeFgMrF = false;
      bool YOnZBnONex = false;
      bool wnwdYiZDkk = false;
      bool oTrVQUoHgt = false;
      bool dADNHElawC = false;
      bool FdKiUUBZEw = false;
      string DcJYTpzqll;
      string wKZobWjTBE;
      string iGVFmTeqZe;
      string eWiCTbEAdj;
      string NXLGjjkdga;
      string qqAuKwGElA;
      string KHRGHZaWVz;
      string SjpRpLuOVC;
      string hBKynmVnqW;
      string UzOdZGFEzJ;
      string JNHgIGBiEz;
      string BriiRIxTRT;
      string DlezeSULqj;
      string FpPLsTtdog;
      string lljrUcQeLQ;
      string JlmeFWiICp;
      string koqTsLbWpy;
      string OSdkhRCmeB;
      string BpAZaTDkFV;
      string kkazuxuPzI;
      if(DcJYTpzqll == JNHgIGBiEz){BsnMCpIBxn = true;}
      else if(JNHgIGBiEz == DcJYTpzqll){gAZeHIjQKr = true;}
      if(wKZobWjTBE == BriiRIxTRT){TudAnunQrZ = true;}
      else if(BriiRIxTRT == wKZobWjTBE){JaBbFgIYlY = true;}
      if(iGVFmTeqZe == DlezeSULqj){IpRTNcqeoj = true;}
      else if(DlezeSULqj == iGVFmTeqZe){SskMzKMwTg = true;}
      if(eWiCTbEAdj == FpPLsTtdog){WlnVzICmXk = true;}
      else if(FpPLsTtdog == eWiCTbEAdj){TaBxqUqofQ = true;}
      if(NXLGjjkdga == lljrUcQeLQ){LBnQCoHaKA = true;}
      else if(lljrUcQeLQ == NXLGjjkdga){IyDdeFgMrF = true;}
      if(qqAuKwGElA == JlmeFWiICp){JdXYzLbTzZ = true;}
      else if(JlmeFWiICp == qqAuKwGElA){YOnZBnONex = true;}
      if(KHRGHZaWVz == koqTsLbWpy){ycMMRhHHAf = true;}
      else if(koqTsLbWpy == KHRGHZaWVz){wnwdYiZDkk = true;}
      if(SjpRpLuOVC == OSdkhRCmeB){sAsHOHBARX = true;}
      if(hBKynmVnqW == BpAZaTDkFV){UQTnZrOOVn = true;}
      if(UzOdZGFEzJ == kkazuxuPzI){fhnxmhnazU = true;}
      while(OSdkhRCmeB == SjpRpLuOVC){oTrVQUoHgt = true;}
      while(BpAZaTDkFV == BpAZaTDkFV){dADNHElawC = true;}
      while(kkazuxuPzI == kkazuxuPzI){FdKiUUBZEw = true;}
      if(BsnMCpIBxn == true){BsnMCpIBxn = false;}
      if(TudAnunQrZ == true){TudAnunQrZ = false;}
      if(IpRTNcqeoj == true){IpRTNcqeoj = false;}
      if(WlnVzICmXk == true){WlnVzICmXk = false;}
      if(LBnQCoHaKA == true){LBnQCoHaKA = false;}
      if(JdXYzLbTzZ == true){JdXYzLbTzZ = false;}
      if(ycMMRhHHAf == true){ycMMRhHHAf = false;}
      if(sAsHOHBARX == true){sAsHOHBARX = false;}
      if(UQTnZrOOVn == true){UQTnZrOOVn = false;}
      if(fhnxmhnazU == true){fhnxmhnazU = false;}
      if(gAZeHIjQKr == true){gAZeHIjQKr = false;}
      if(JaBbFgIYlY == true){JaBbFgIYlY = false;}
      if(SskMzKMwTg == true){SskMzKMwTg = false;}
      if(TaBxqUqofQ == true){TaBxqUqofQ = false;}
      if(IyDdeFgMrF == true){IyDdeFgMrF = false;}
      if(YOnZBnONex == true){YOnZBnONex = false;}
      if(wnwdYiZDkk == true){wnwdYiZDkk = false;}
      if(oTrVQUoHgt == true){oTrVQUoHgt = false;}
      if(dADNHElawC == true){dADNHElawC = false;}
      if(FdKiUUBZEw == true){FdKiUUBZEw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BPKXCODPEA
{ 
  void zzYsnUkBfi()
  { 
      bool TsEsrLpXUA = false;
      bool shHpYRaVWV = false;
      bool fxtIrPifEs = false;
      bool eBxDSmPPHr = false;
      bool hYxkcBhTaG = false;
      bool UdIgJVywAb = false;
      bool cKSaVqjEWl = false;
      bool CLNemHAJeq = false;
      bool hOFxYArQsx = false;
      bool nSOePXFVPk = false;
      bool QdxoEJQdsC = false;
      bool VoQJtNEVCU = false;
      bool zTKZxiwhOP = false;
      bool BdstaDRPsO = false;
      bool jNWqazBEkB = false;
      bool SjTtlwSWqU = false;
      bool MhOcAquWip = false;
      bool uobmkkwTyy = false;
      bool grxNxRKyHd = false;
      bool ktYXCBytpj = false;
      string nnJtKUsEAJ;
      string CKVMKoGztC;
      string QYtRIRTaCH;
      string xKbjIRNtHy;
      string FLjpWxSQpl;
      string EESiuPtqks;
      string BRCsLrhlEr;
      string bMrwxFnEuL;
      string zDkPDrqsns;
      string XVIOxmJpde;
      string PgLxKqMVlp;
      string aowZtxgloT;
      string AoxLUFDczK;
      string wxaPwRqmFL;
      string eVHxRhZiUz;
      string FWBJdZiAcF;
      string miVatcOfdb;
      string GsfcodgAsl;
      string fUIAEYwRkV;
      string ipKAYuzfCo;
      if(nnJtKUsEAJ == PgLxKqMVlp){TsEsrLpXUA = true;}
      else if(PgLxKqMVlp == nnJtKUsEAJ){QdxoEJQdsC = true;}
      if(CKVMKoGztC == aowZtxgloT){shHpYRaVWV = true;}
      else if(aowZtxgloT == CKVMKoGztC){VoQJtNEVCU = true;}
      if(QYtRIRTaCH == AoxLUFDczK){fxtIrPifEs = true;}
      else if(AoxLUFDczK == QYtRIRTaCH){zTKZxiwhOP = true;}
      if(xKbjIRNtHy == wxaPwRqmFL){eBxDSmPPHr = true;}
      else if(wxaPwRqmFL == xKbjIRNtHy){BdstaDRPsO = true;}
      if(FLjpWxSQpl == eVHxRhZiUz){hYxkcBhTaG = true;}
      else if(eVHxRhZiUz == FLjpWxSQpl){jNWqazBEkB = true;}
      if(EESiuPtqks == FWBJdZiAcF){UdIgJVywAb = true;}
      else if(FWBJdZiAcF == EESiuPtqks){SjTtlwSWqU = true;}
      if(BRCsLrhlEr == miVatcOfdb){cKSaVqjEWl = true;}
      else if(miVatcOfdb == BRCsLrhlEr){MhOcAquWip = true;}
      if(bMrwxFnEuL == GsfcodgAsl){CLNemHAJeq = true;}
      if(zDkPDrqsns == fUIAEYwRkV){hOFxYArQsx = true;}
      if(XVIOxmJpde == ipKAYuzfCo){nSOePXFVPk = true;}
      while(GsfcodgAsl == bMrwxFnEuL){uobmkkwTyy = true;}
      while(fUIAEYwRkV == fUIAEYwRkV){grxNxRKyHd = true;}
      while(ipKAYuzfCo == ipKAYuzfCo){ktYXCBytpj = true;}
      if(TsEsrLpXUA == true){TsEsrLpXUA = false;}
      if(shHpYRaVWV == true){shHpYRaVWV = false;}
      if(fxtIrPifEs == true){fxtIrPifEs = false;}
      if(eBxDSmPPHr == true){eBxDSmPPHr = false;}
      if(hYxkcBhTaG == true){hYxkcBhTaG = false;}
      if(UdIgJVywAb == true){UdIgJVywAb = false;}
      if(cKSaVqjEWl == true){cKSaVqjEWl = false;}
      if(CLNemHAJeq == true){CLNemHAJeq = false;}
      if(hOFxYArQsx == true){hOFxYArQsx = false;}
      if(nSOePXFVPk == true){nSOePXFVPk = false;}
      if(QdxoEJQdsC == true){QdxoEJQdsC = false;}
      if(VoQJtNEVCU == true){VoQJtNEVCU = false;}
      if(zTKZxiwhOP == true){zTKZxiwhOP = false;}
      if(BdstaDRPsO == true){BdstaDRPsO = false;}
      if(jNWqazBEkB == true){jNWqazBEkB = false;}
      if(SjTtlwSWqU == true){SjTtlwSWqU = false;}
      if(MhOcAquWip == true){MhOcAquWip = false;}
      if(uobmkkwTyy == true){uobmkkwTyy = false;}
      if(grxNxRKyHd == true){grxNxRKyHd = false;}
      if(ktYXCBytpj == true){ktYXCBytpj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRZCMZMJYE
{ 
  void xrguXArngt()
  { 
      bool ASCUSmsbOZ = false;
      bool UnuZnwhfyX = false;
      bool kbKWTeyeHu = false;
      bool pbXinCSRlV = false;
      bool GyhJAKdcWD = false;
      bool pSqMjYHeAn = false;
      bool nOUTjsQMlk = false;
      bool cQsbRlsBVJ = false;
      bool AVHDFWjKzO = false;
      bool umQxgqdOZH = false;
      bool sRqlZYYPuy = false;
      bool eGJqmSHQNM = false;
      bool JFNWppzutZ = false;
      bool IdbNPhdVcf = false;
      bool xUPBjodZKN = false;
      bool jMAMynETuj = false;
      bool ZdUVoAeuaF = false;
      bool nknhPnpMmA = false;
      bool MYkfoucOPb = false;
      bool dKZrFTzsLi = false;
      string YNXrgXcULS;
      string LqlREXVFak;
      string CpeteHfNtp;
      string OpXEhMiJbt;
      string ZWaBIUwUTf;
      string sYsSnhhdMZ;
      string qOaUEUThjq;
      string nMcfKfOckK;
      string KLtNxpwEPz;
      string dFxCDKwGxm;
      string BOkbrfuNHH;
      string TErBOeUMXO;
      string XORjNhPZcz;
      string jIfyIwaRVQ;
      string tixIfYMumX;
      string pjhiOlxAOJ;
      string QUjHXKYtsS;
      string ECpGToRIEn;
      string VUmEJzZxiV;
      string yZDLzYyokU;
      if(YNXrgXcULS == BOkbrfuNHH){ASCUSmsbOZ = true;}
      else if(BOkbrfuNHH == YNXrgXcULS){sRqlZYYPuy = true;}
      if(LqlREXVFak == TErBOeUMXO){UnuZnwhfyX = true;}
      else if(TErBOeUMXO == LqlREXVFak){eGJqmSHQNM = true;}
      if(CpeteHfNtp == XORjNhPZcz){kbKWTeyeHu = true;}
      else if(XORjNhPZcz == CpeteHfNtp){JFNWppzutZ = true;}
      if(OpXEhMiJbt == jIfyIwaRVQ){pbXinCSRlV = true;}
      else if(jIfyIwaRVQ == OpXEhMiJbt){IdbNPhdVcf = true;}
      if(ZWaBIUwUTf == tixIfYMumX){GyhJAKdcWD = true;}
      else if(tixIfYMumX == ZWaBIUwUTf){xUPBjodZKN = true;}
      if(sYsSnhhdMZ == pjhiOlxAOJ){pSqMjYHeAn = true;}
      else if(pjhiOlxAOJ == sYsSnhhdMZ){jMAMynETuj = true;}
      if(qOaUEUThjq == QUjHXKYtsS){nOUTjsQMlk = true;}
      else if(QUjHXKYtsS == qOaUEUThjq){ZdUVoAeuaF = true;}
      if(nMcfKfOckK == ECpGToRIEn){cQsbRlsBVJ = true;}
      if(KLtNxpwEPz == VUmEJzZxiV){AVHDFWjKzO = true;}
      if(dFxCDKwGxm == yZDLzYyokU){umQxgqdOZH = true;}
      while(ECpGToRIEn == nMcfKfOckK){nknhPnpMmA = true;}
      while(VUmEJzZxiV == VUmEJzZxiV){MYkfoucOPb = true;}
      while(yZDLzYyokU == yZDLzYyokU){dKZrFTzsLi = true;}
      if(ASCUSmsbOZ == true){ASCUSmsbOZ = false;}
      if(UnuZnwhfyX == true){UnuZnwhfyX = false;}
      if(kbKWTeyeHu == true){kbKWTeyeHu = false;}
      if(pbXinCSRlV == true){pbXinCSRlV = false;}
      if(GyhJAKdcWD == true){GyhJAKdcWD = false;}
      if(pSqMjYHeAn == true){pSqMjYHeAn = false;}
      if(nOUTjsQMlk == true){nOUTjsQMlk = false;}
      if(cQsbRlsBVJ == true){cQsbRlsBVJ = false;}
      if(AVHDFWjKzO == true){AVHDFWjKzO = false;}
      if(umQxgqdOZH == true){umQxgqdOZH = false;}
      if(sRqlZYYPuy == true){sRqlZYYPuy = false;}
      if(eGJqmSHQNM == true){eGJqmSHQNM = false;}
      if(JFNWppzutZ == true){JFNWppzutZ = false;}
      if(IdbNPhdVcf == true){IdbNPhdVcf = false;}
      if(xUPBjodZKN == true){xUPBjodZKN = false;}
      if(jMAMynETuj == true){jMAMynETuj = false;}
      if(ZdUVoAeuaF == true){ZdUVoAeuaF = false;}
      if(nknhPnpMmA == true){nknhPnpMmA = false;}
      if(MYkfoucOPb == true){MYkfoucOPb = false;}
      if(dKZrFTzsLi == true){dKZrFTzsLi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DOFPKEAPXG
{ 
  void kppfqFKhaC()
  { 
      bool xypSaLjEbU = false;
      bool wLyjkbVVwn = false;
      bool QMFxnMlhSH = false;
      bool pfDeogyDYs = false;
      bool oNlYMhoahV = false;
      bool KPzIVkrrdO = false;
      bool ZBlTeQHTuD = false;
      bool dSxCyCZgjG = false;
      bool WKAwxafuIE = false;
      bool oFYKTmbRtw = false;
      bool ZVedrrRwJS = false;
      bool KKIXqOAoVD = false;
      bool jMKqNYsmiK = false;
      bool aImmgBeWEF = false;
      bool IjkpsdxBSE = false;
      bool llwpMMKnPS = false;
      bool ydMyqBXUqo = false;
      bool idjPuzbUxj = false;
      bool brTeXoMxZT = false;
      bool qqGkHeWlzq = false;
      string BqJcGpYIkN;
      string JXlfUWVPEm;
      string WnhtMqgdrn;
      string OSjrDjDADr;
      string imybWjPcPN;
      string WaLUIMJOPO;
      string JtPwzpntbj;
      string SVLLEipFXc;
      string bEOdQmGOiq;
      string aojnioXBbf;
      string wVAftBOzQY;
      string WDqmmFfkfM;
      string iYKkJdkWcO;
      string LndqfFDhjO;
      string XHxJUWyxBc;
      string JlVPxWLOWQ;
      string QrVCNhZAGh;
      string BxBQnbaAQl;
      string fnVAFZRNtI;
      string snLSyfkuwl;
      if(BqJcGpYIkN == wVAftBOzQY){xypSaLjEbU = true;}
      else if(wVAftBOzQY == BqJcGpYIkN){ZVedrrRwJS = true;}
      if(JXlfUWVPEm == WDqmmFfkfM){wLyjkbVVwn = true;}
      else if(WDqmmFfkfM == JXlfUWVPEm){KKIXqOAoVD = true;}
      if(WnhtMqgdrn == iYKkJdkWcO){QMFxnMlhSH = true;}
      else if(iYKkJdkWcO == WnhtMqgdrn){jMKqNYsmiK = true;}
      if(OSjrDjDADr == LndqfFDhjO){pfDeogyDYs = true;}
      else if(LndqfFDhjO == OSjrDjDADr){aImmgBeWEF = true;}
      if(imybWjPcPN == XHxJUWyxBc){oNlYMhoahV = true;}
      else if(XHxJUWyxBc == imybWjPcPN){IjkpsdxBSE = true;}
      if(WaLUIMJOPO == JlVPxWLOWQ){KPzIVkrrdO = true;}
      else if(JlVPxWLOWQ == WaLUIMJOPO){llwpMMKnPS = true;}
      if(JtPwzpntbj == QrVCNhZAGh){ZBlTeQHTuD = true;}
      else if(QrVCNhZAGh == JtPwzpntbj){ydMyqBXUqo = true;}
      if(SVLLEipFXc == BxBQnbaAQl){dSxCyCZgjG = true;}
      if(bEOdQmGOiq == fnVAFZRNtI){WKAwxafuIE = true;}
      if(aojnioXBbf == snLSyfkuwl){oFYKTmbRtw = true;}
      while(BxBQnbaAQl == SVLLEipFXc){idjPuzbUxj = true;}
      while(fnVAFZRNtI == fnVAFZRNtI){brTeXoMxZT = true;}
      while(snLSyfkuwl == snLSyfkuwl){qqGkHeWlzq = true;}
      if(xypSaLjEbU == true){xypSaLjEbU = false;}
      if(wLyjkbVVwn == true){wLyjkbVVwn = false;}
      if(QMFxnMlhSH == true){QMFxnMlhSH = false;}
      if(pfDeogyDYs == true){pfDeogyDYs = false;}
      if(oNlYMhoahV == true){oNlYMhoahV = false;}
      if(KPzIVkrrdO == true){KPzIVkrrdO = false;}
      if(ZBlTeQHTuD == true){ZBlTeQHTuD = false;}
      if(dSxCyCZgjG == true){dSxCyCZgjG = false;}
      if(WKAwxafuIE == true){WKAwxafuIE = false;}
      if(oFYKTmbRtw == true){oFYKTmbRtw = false;}
      if(ZVedrrRwJS == true){ZVedrrRwJS = false;}
      if(KKIXqOAoVD == true){KKIXqOAoVD = false;}
      if(jMKqNYsmiK == true){jMKqNYsmiK = false;}
      if(aImmgBeWEF == true){aImmgBeWEF = false;}
      if(IjkpsdxBSE == true){IjkpsdxBSE = false;}
      if(llwpMMKnPS == true){llwpMMKnPS = false;}
      if(ydMyqBXUqo == true){ydMyqBXUqo = false;}
      if(idjPuzbUxj == true){idjPuzbUxj = false;}
      if(brTeXoMxZT == true){brTeXoMxZT = false;}
      if(qqGkHeWlzq == true){qqGkHeWlzq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSRIVQTMQU
{ 
  void eZIHEIUBRg()
  { 
      bool KePHwOyiiz = false;
      bool srOLXOmjnV = false;
      bool TEDIVmgXiE = false;
      bool PUgNCwnXRg = false;
      bool PcQsTaWMnE = false;
      bool grgDsFaHlJ = false;
      bool gZAeiXLAJa = false;
      bool ZOSGFqnKnu = false;
      bool QTjeWWndTw = false;
      bool VflIApclJu = false;
      bool OVDMeSZZxB = false;
      bool RPTqsMpUIM = false;
      bool jhgMFscKGP = false;
      bool OCBrftQWAD = false;
      bool wNfReFMuOm = false;
      bool AHcwKgoqHk = false;
      bool pPThmPNaLy = false;
      bool uSUEPWCOhz = false;
      bool gguSPGYEhy = false;
      bool FZPONgsyeO = false;
      string ktMqDVbZhU;
      string TtBSjqjmCY;
      string DhAkBJlSUx;
      string VpusZZhrBB;
      string ifKVobYCOJ;
      string BihpDCtbot;
      string iIFjzczHrK;
      string IrkBpWXewY;
      string kjDLulIEpX;
      string fGCHSZaZVM;
      string cQJEAJxgAf;
      string dOfQJyFsnN;
      string UtQUeCpdhQ;
      string uxJjuTZzKl;
      string nbEKsQakxT;
      string UgkIqizoZy;
      string STyjjfFwUo;
      string XGiCYroGaN;
      string aEfNuNMArM;
      string TkYLSUcUZN;
      if(ktMqDVbZhU == cQJEAJxgAf){KePHwOyiiz = true;}
      else if(cQJEAJxgAf == ktMqDVbZhU){OVDMeSZZxB = true;}
      if(TtBSjqjmCY == dOfQJyFsnN){srOLXOmjnV = true;}
      else if(dOfQJyFsnN == TtBSjqjmCY){RPTqsMpUIM = true;}
      if(DhAkBJlSUx == UtQUeCpdhQ){TEDIVmgXiE = true;}
      else if(UtQUeCpdhQ == DhAkBJlSUx){jhgMFscKGP = true;}
      if(VpusZZhrBB == uxJjuTZzKl){PUgNCwnXRg = true;}
      else if(uxJjuTZzKl == VpusZZhrBB){OCBrftQWAD = true;}
      if(ifKVobYCOJ == nbEKsQakxT){PcQsTaWMnE = true;}
      else if(nbEKsQakxT == ifKVobYCOJ){wNfReFMuOm = true;}
      if(BihpDCtbot == UgkIqizoZy){grgDsFaHlJ = true;}
      else if(UgkIqizoZy == BihpDCtbot){AHcwKgoqHk = true;}
      if(iIFjzczHrK == STyjjfFwUo){gZAeiXLAJa = true;}
      else if(STyjjfFwUo == iIFjzczHrK){pPThmPNaLy = true;}
      if(IrkBpWXewY == XGiCYroGaN){ZOSGFqnKnu = true;}
      if(kjDLulIEpX == aEfNuNMArM){QTjeWWndTw = true;}
      if(fGCHSZaZVM == TkYLSUcUZN){VflIApclJu = true;}
      while(XGiCYroGaN == IrkBpWXewY){uSUEPWCOhz = true;}
      while(aEfNuNMArM == aEfNuNMArM){gguSPGYEhy = true;}
      while(TkYLSUcUZN == TkYLSUcUZN){FZPONgsyeO = true;}
      if(KePHwOyiiz == true){KePHwOyiiz = false;}
      if(srOLXOmjnV == true){srOLXOmjnV = false;}
      if(TEDIVmgXiE == true){TEDIVmgXiE = false;}
      if(PUgNCwnXRg == true){PUgNCwnXRg = false;}
      if(PcQsTaWMnE == true){PcQsTaWMnE = false;}
      if(grgDsFaHlJ == true){grgDsFaHlJ = false;}
      if(gZAeiXLAJa == true){gZAeiXLAJa = false;}
      if(ZOSGFqnKnu == true){ZOSGFqnKnu = false;}
      if(QTjeWWndTw == true){QTjeWWndTw = false;}
      if(VflIApclJu == true){VflIApclJu = false;}
      if(OVDMeSZZxB == true){OVDMeSZZxB = false;}
      if(RPTqsMpUIM == true){RPTqsMpUIM = false;}
      if(jhgMFscKGP == true){jhgMFscKGP = false;}
      if(OCBrftQWAD == true){OCBrftQWAD = false;}
      if(wNfReFMuOm == true){wNfReFMuOm = false;}
      if(AHcwKgoqHk == true){AHcwKgoqHk = false;}
      if(pPThmPNaLy == true){pPThmPNaLy = false;}
      if(uSUEPWCOhz == true){uSUEPWCOhz = false;}
      if(gguSPGYEhy == true){gguSPGYEhy = false;}
      if(FZPONgsyeO == true){FZPONgsyeO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICEOFJNVNJ
{ 
  void qApTrXlnuy()
  { 
      bool yFrtyiJXph = false;
      bool AGxzqhEtiQ = false;
      bool tihTzjVpJp = false;
      bool TZTRaPQuBh = false;
      bool OXJxgKeTJz = false;
      bool zHpEoPXXtN = false;
      bool MTOzOZleYb = false;
      bool RIrBBVYjmo = false;
      bool FCgJpLiPbL = false;
      bool rrAnUtJJiG = false;
      bool XzuhhqPoCT = false;
      bool pnjEIJmFJC = false;
      bool qWDMiYHEfH = false;
      bool MPAgRFHybz = false;
      bool wtMIVEHweL = false;
      bool HDAgOBuhyI = false;
      bool iKIuGamDmC = false;
      bool BndJFxJuqe = false;
      bool QLYUzIOSRP = false;
      bool JZASPklQBt = false;
      string zROOZKVsYX;
      string oquXsiwWpI;
      string FFiFYjZOYp;
      string iRATUkbReh;
      string NZOTwQYaoJ;
      string XnOktsiIpo;
      string kGUioWpaCI;
      string HdqIueqPJH;
      string KyYPSuDPZb;
      string BSbpxGFfdY;
      string axYgBswGoO;
      string CTzhdlhEQs;
      string TZBaHoCBLo;
      string ZLkkgNZrNY;
      string yxaKZhTsLK;
      string XAPkEAwxYM;
      string qttAopiNBQ;
      string MoqqtWzpAZ;
      string VIpAQYwzfg;
      string QbSAhECZVi;
      if(zROOZKVsYX == axYgBswGoO){yFrtyiJXph = true;}
      else if(axYgBswGoO == zROOZKVsYX){XzuhhqPoCT = true;}
      if(oquXsiwWpI == CTzhdlhEQs){AGxzqhEtiQ = true;}
      else if(CTzhdlhEQs == oquXsiwWpI){pnjEIJmFJC = true;}
      if(FFiFYjZOYp == TZBaHoCBLo){tihTzjVpJp = true;}
      else if(TZBaHoCBLo == FFiFYjZOYp){qWDMiYHEfH = true;}
      if(iRATUkbReh == ZLkkgNZrNY){TZTRaPQuBh = true;}
      else if(ZLkkgNZrNY == iRATUkbReh){MPAgRFHybz = true;}
      if(NZOTwQYaoJ == yxaKZhTsLK){OXJxgKeTJz = true;}
      else if(yxaKZhTsLK == NZOTwQYaoJ){wtMIVEHweL = true;}
      if(XnOktsiIpo == XAPkEAwxYM){zHpEoPXXtN = true;}
      else if(XAPkEAwxYM == XnOktsiIpo){HDAgOBuhyI = true;}
      if(kGUioWpaCI == qttAopiNBQ){MTOzOZleYb = true;}
      else if(qttAopiNBQ == kGUioWpaCI){iKIuGamDmC = true;}
      if(HdqIueqPJH == MoqqtWzpAZ){RIrBBVYjmo = true;}
      if(KyYPSuDPZb == VIpAQYwzfg){FCgJpLiPbL = true;}
      if(BSbpxGFfdY == QbSAhECZVi){rrAnUtJJiG = true;}
      while(MoqqtWzpAZ == HdqIueqPJH){BndJFxJuqe = true;}
      while(VIpAQYwzfg == VIpAQYwzfg){QLYUzIOSRP = true;}
      while(QbSAhECZVi == QbSAhECZVi){JZASPklQBt = true;}
      if(yFrtyiJXph == true){yFrtyiJXph = false;}
      if(AGxzqhEtiQ == true){AGxzqhEtiQ = false;}
      if(tihTzjVpJp == true){tihTzjVpJp = false;}
      if(TZTRaPQuBh == true){TZTRaPQuBh = false;}
      if(OXJxgKeTJz == true){OXJxgKeTJz = false;}
      if(zHpEoPXXtN == true){zHpEoPXXtN = false;}
      if(MTOzOZleYb == true){MTOzOZleYb = false;}
      if(RIrBBVYjmo == true){RIrBBVYjmo = false;}
      if(FCgJpLiPbL == true){FCgJpLiPbL = false;}
      if(rrAnUtJJiG == true){rrAnUtJJiG = false;}
      if(XzuhhqPoCT == true){XzuhhqPoCT = false;}
      if(pnjEIJmFJC == true){pnjEIJmFJC = false;}
      if(qWDMiYHEfH == true){qWDMiYHEfH = false;}
      if(MPAgRFHybz == true){MPAgRFHybz = false;}
      if(wtMIVEHweL == true){wtMIVEHweL = false;}
      if(HDAgOBuhyI == true){HDAgOBuhyI = false;}
      if(iKIuGamDmC == true){iKIuGamDmC = false;}
      if(BndJFxJuqe == true){BndJFxJuqe = false;}
      if(QLYUzIOSRP == true){QLYUzIOSRP = false;}
      if(JZASPklQBt == true){JZASPklQBt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTLYSUNYJX
{ 
  void ERxwjkDkxH()
  { 
      bool AwxNqUOcTz = false;
      bool lkulTxlefs = false;
      bool fsXbTSnNcB = false;
      bool DCVouHmPkq = false;
      bool VCkCoITFgs = false;
      bool QZVXuHYUsY = false;
      bool fBzRwjPFqL = false;
      bool KVsoWcHVmK = false;
      bool yifjkdfxsn = false;
      bool iSWMKUDTFE = false;
      bool sOOVhufgBS = false;
      bool zDghZxUPfS = false;
      bool ERLCbrzgdB = false;
      bool ZmPiRjTJBp = false;
      bool yyuanelnlN = false;
      bool znnmAaCLsp = false;
      bool wyCzsLnyQp = false;
      bool cKNpUFVkOx = false;
      bool GLtQClzbip = false;
      bool gIQLtzwwhb = false;
      string CcdhMuMMDd;
      string RVsUxDOXah;
      string KsdJAHrDBT;
      string TXWSlaYFLm;
      string OcZFWphzAc;
      string bfzXbJzUgE;
      string DILjKtyZhW;
      string eJLmSgTXlK;
      string ZsDXqmYzpc;
      string aEXGjGRpuc;
      string qHQdySULEt;
      string obhWeKFnrW;
      string UziEuakEDM;
      string PdcJSRbZYX;
      string SMtwmzVBaZ;
      string AdxXHqXMhX;
      string hPIreLyYEN;
      string hfOTEHEmQw;
      string EjdcLkfEBb;
      string sPqApCECRb;
      if(CcdhMuMMDd == qHQdySULEt){AwxNqUOcTz = true;}
      else if(qHQdySULEt == CcdhMuMMDd){sOOVhufgBS = true;}
      if(RVsUxDOXah == obhWeKFnrW){lkulTxlefs = true;}
      else if(obhWeKFnrW == RVsUxDOXah){zDghZxUPfS = true;}
      if(KsdJAHrDBT == UziEuakEDM){fsXbTSnNcB = true;}
      else if(UziEuakEDM == KsdJAHrDBT){ERLCbrzgdB = true;}
      if(TXWSlaYFLm == PdcJSRbZYX){DCVouHmPkq = true;}
      else if(PdcJSRbZYX == TXWSlaYFLm){ZmPiRjTJBp = true;}
      if(OcZFWphzAc == SMtwmzVBaZ){VCkCoITFgs = true;}
      else if(SMtwmzVBaZ == OcZFWphzAc){yyuanelnlN = true;}
      if(bfzXbJzUgE == AdxXHqXMhX){QZVXuHYUsY = true;}
      else if(AdxXHqXMhX == bfzXbJzUgE){znnmAaCLsp = true;}
      if(DILjKtyZhW == hPIreLyYEN){fBzRwjPFqL = true;}
      else if(hPIreLyYEN == DILjKtyZhW){wyCzsLnyQp = true;}
      if(eJLmSgTXlK == hfOTEHEmQw){KVsoWcHVmK = true;}
      if(ZsDXqmYzpc == EjdcLkfEBb){yifjkdfxsn = true;}
      if(aEXGjGRpuc == sPqApCECRb){iSWMKUDTFE = true;}
      while(hfOTEHEmQw == eJLmSgTXlK){cKNpUFVkOx = true;}
      while(EjdcLkfEBb == EjdcLkfEBb){GLtQClzbip = true;}
      while(sPqApCECRb == sPqApCECRb){gIQLtzwwhb = true;}
      if(AwxNqUOcTz == true){AwxNqUOcTz = false;}
      if(lkulTxlefs == true){lkulTxlefs = false;}
      if(fsXbTSnNcB == true){fsXbTSnNcB = false;}
      if(DCVouHmPkq == true){DCVouHmPkq = false;}
      if(VCkCoITFgs == true){VCkCoITFgs = false;}
      if(QZVXuHYUsY == true){QZVXuHYUsY = false;}
      if(fBzRwjPFqL == true){fBzRwjPFqL = false;}
      if(KVsoWcHVmK == true){KVsoWcHVmK = false;}
      if(yifjkdfxsn == true){yifjkdfxsn = false;}
      if(iSWMKUDTFE == true){iSWMKUDTFE = false;}
      if(sOOVhufgBS == true){sOOVhufgBS = false;}
      if(zDghZxUPfS == true){zDghZxUPfS = false;}
      if(ERLCbrzgdB == true){ERLCbrzgdB = false;}
      if(ZmPiRjTJBp == true){ZmPiRjTJBp = false;}
      if(yyuanelnlN == true){yyuanelnlN = false;}
      if(znnmAaCLsp == true){znnmAaCLsp = false;}
      if(wyCzsLnyQp == true){wyCzsLnyQp = false;}
      if(cKNpUFVkOx == true){cKNpUFVkOx = false;}
      if(GLtQClzbip == true){GLtQClzbip = false;}
      if(gIQLtzwwhb == true){gIQLtzwwhb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWWOGAPZLQ
{ 
  void zzKtEIlmDz()
  { 
      bool tSLGnGbOLk = false;
      bool IGcNCMUlEE = false;
      bool jADClTprQM = false;
      bool cltJPnExhK = false;
      bool CXukEEefLB = false;
      bool btoBqtPITU = false;
      bool PiyzIWMSxN = false;
      bool IWEtBLFRyg = false;
      bool nKgPkhwsSV = false;
      bool YwdMtTZucg = false;
      bool rLhxrEouze = false;
      bool nyJmfFBiOZ = false;
      bool aSAboMsrzg = false;
      bool kJnQnbciWf = false;
      bool sAsngZlpgo = false;
      bool RqgDGYLFIf = false;
      bool LxwRseJryD = false;
      bool bRLhgZZLuO = false;
      bool aCKJOtckKP = false;
      bool QXapUuEatC = false;
      string DMzcAWxtDl;
      string ZXcstZnRlD;
      string DACtUaDpeT;
      string HmdFGuoBri;
      string BcBchfQjku;
      string GGAhWDJEHY;
      string SHOjemsWlz;
      string klZDCayZMo;
      string KTEiMBmwiD;
      string ljtSPsNRyu;
      string lsxlKUfweu;
      string EiqSOzCeWc;
      string AxmiNAqHmI;
      string MgbRCQWSYq;
      string UpQnyCrbDQ;
      string qhtUuoFNYK;
      string cYIWhWHZPx;
      string bjGeIJfzkK;
      string HPDVRdmGWN;
      string LIsNOwgtFa;
      if(DMzcAWxtDl == lsxlKUfweu){tSLGnGbOLk = true;}
      else if(lsxlKUfweu == DMzcAWxtDl){rLhxrEouze = true;}
      if(ZXcstZnRlD == EiqSOzCeWc){IGcNCMUlEE = true;}
      else if(EiqSOzCeWc == ZXcstZnRlD){nyJmfFBiOZ = true;}
      if(DACtUaDpeT == AxmiNAqHmI){jADClTprQM = true;}
      else if(AxmiNAqHmI == DACtUaDpeT){aSAboMsrzg = true;}
      if(HmdFGuoBri == MgbRCQWSYq){cltJPnExhK = true;}
      else if(MgbRCQWSYq == HmdFGuoBri){kJnQnbciWf = true;}
      if(BcBchfQjku == UpQnyCrbDQ){CXukEEefLB = true;}
      else if(UpQnyCrbDQ == BcBchfQjku){sAsngZlpgo = true;}
      if(GGAhWDJEHY == qhtUuoFNYK){btoBqtPITU = true;}
      else if(qhtUuoFNYK == GGAhWDJEHY){RqgDGYLFIf = true;}
      if(SHOjemsWlz == cYIWhWHZPx){PiyzIWMSxN = true;}
      else if(cYIWhWHZPx == SHOjemsWlz){LxwRseJryD = true;}
      if(klZDCayZMo == bjGeIJfzkK){IWEtBLFRyg = true;}
      if(KTEiMBmwiD == HPDVRdmGWN){nKgPkhwsSV = true;}
      if(ljtSPsNRyu == LIsNOwgtFa){YwdMtTZucg = true;}
      while(bjGeIJfzkK == klZDCayZMo){bRLhgZZLuO = true;}
      while(HPDVRdmGWN == HPDVRdmGWN){aCKJOtckKP = true;}
      while(LIsNOwgtFa == LIsNOwgtFa){QXapUuEatC = true;}
      if(tSLGnGbOLk == true){tSLGnGbOLk = false;}
      if(IGcNCMUlEE == true){IGcNCMUlEE = false;}
      if(jADClTprQM == true){jADClTprQM = false;}
      if(cltJPnExhK == true){cltJPnExhK = false;}
      if(CXukEEefLB == true){CXukEEefLB = false;}
      if(btoBqtPITU == true){btoBqtPITU = false;}
      if(PiyzIWMSxN == true){PiyzIWMSxN = false;}
      if(IWEtBLFRyg == true){IWEtBLFRyg = false;}
      if(nKgPkhwsSV == true){nKgPkhwsSV = false;}
      if(YwdMtTZucg == true){YwdMtTZucg = false;}
      if(rLhxrEouze == true){rLhxrEouze = false;}
      if(nyJmfFBiOZ == true){nyJmfFBiOZ = false;}
      if(aSAboMsrzg == true){aSAboMsrzg = false;}
      if(kJnQnbciWf == true){kJnQnbciWf = false;}
      if(sAsngZlpgo == true){sAsngZlpgo = false;}
      if(RqgDGYLFIf == true){RqgDGYLFIf = false;}
      if(LxwRseJryD == true){LxwRseJryD = false;}
      if(bRLhgZZLuO == true){bRLhgZZLuO = false;}
      if(aCKJOtckKP == true){aCKJOtckKP = false;}
      if(QXapUuEatC == true){QXapUuEatC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJWDGKSBQD
{ 
  void VsttNRkemP()
  { 
      bool wktQMLmUxf = false;
      bool nPkRffhgsZ = false;
      bool ujVMmzhUVL = false;
      bool rupcajCjiH = false;
      bool HKTeDLZZxR = false;
      bool xCXOfMPhcM = false;
      bool cSzkmrYIqu = false;
      bool dyylRjPpIb = false;
      bool ZIWDNoXbwO = false;
      bool UTGWdoLiqL = false;
      bool lQhBnyElxw = false;
      bool wYZBlUuuXx = false;
      bool UxLcaKrbHb = false;
      bool XgzxoJZVPO = false;
      bool kkdARutEjI = false;
      bool tQKspoEFZd = false;
      bool GcdUXPYbLc = false;
      bool uZfIMjSLKf = false;
      bool PnqzhHVGGA = false;
      bool ETulIHGJbB = false;
      string pAqptNYELn;
      string RjEHopSTBj;
      string zmoWJwBaJP;
      string zOCDBPlbRw;
      string oGglDYlDjr;
      string PSCJrCKTgx;
      string LxtwoChAFZ;
      string EqBEtrGDTj;
      string JyqRAgLrKy;
      string ERuTjqMkxA;
      string qlxKnXQxOA;
      string wHAwmMGbuH;
      string qppGUlugTD;
      string eUGTrXBgdb;
      string PNcJCxRygX;
      string kjooIBwpoB;
      string cidLUaBfEP;
      string KYxTrcMfEW;
      string UwAwSufQKq;
      string bLqcyfjQoa;
      if(pAqptNYELn == qlxKnXQxOA){wktQMLmUxf = true;}
      else if(qlxKnXQxOA == pAqptNYELn){lQhBnyElxw = true;}
      if(RjEHopSTBj == wHAwmMGbuH){nPkRffhgsZ = true;}
      else if(wHAwmMGbuH == RjEHopSTBj){wYZBlUuuXx = true;}
      if(zmoWJwBaJP == qppGUlugTD){ujVMmzhUVL = true;}
      else if(qppGUlugTD == zmoWJwBaJP){UxLcaKrbHb = true;}
      if(zOCDBPlbRw == eUGTrXBgdb){rupcajCjiH = true;}
      else if(eUGTrXBgdb == zOCDBPlbRw){XgzxoJZVPO = true;}
      if(oGglDYlDjr == PNcJCxRygX){HKTeDLZZxR = true;}
      else if(PNcJCxRygX == oGglDYlDjr){kkdARutEjI = true;}
      if(PSCJrCKTgx == kjooIBwpoB){xCXOfMPhcM = true;}
      else if(kjooIBwpoB == PSCJrCKTgx){tQKspoEFZd = true;}
      if(LxtwoChAFZ == cidLUaBfEP){cSzkmrYIqu = true;}
      else if(cidLUaBfEP == LxtwoChAFZ){GcdUXPYbLc = true;}
      if(EqBEtrGDTj == KYxTrcMfEW){dyylRjPpIb = true;}
      if(JyqRAgLrKy == UwAwSufQKq){ZIWDNoXbwO = true;}
      if(ERuTjqMkxA == bLqcyfjQoa){UTGWdoLiqL = true;}
      while(KYxTrcMfEW == EqBEtrGDTj){uZfIMjSLKf = true;}
      while(UwAwSufQKq == UwAwSufQKq){PnqzhHVGGA = true;}
      while(bLqcyfjQoa == bLqcyfjQoa){ETulIHGJbB = true;}
      if(wktQMLmUxf == true){wktQMLmUxf = false;}
      if(nPkRffhgsZ == true){nPkRffhgsZ = false;}
      if(ujVMmzhUVL == true){ujVMmzhUVL = false;}
      if(rupcajCjiH == true){rupcajCjiH = false;}
      if(HKTeDLZZxR == true){HKTeDLZZxR = false;}
      if(xCXOfMPhcM == true){xCXOfMPhcM = false;}
      if(cSzkmrYIqu == true){cSzkmrYIqu = false;}
      if(dyylRjPpIb == true){dyylRjPpIb = false;}
      if(ZIWDNoXbwO == true){ZIWDNoXbwO = false;}
      if(UTGWdoLiqL == true){UTGWdoLiqL = false;}
      if(lQhBnyElxw == true){lQhBnyElxw = false;}
      if(wYZBlUuuXx == true){wYZBlUuuXx = false;}
      if(UxLcaKrbHb == true){UxLcaKrbHb = false;}
      if(XgzxoJZVPO == true){XgzxoJZVPO = false;}
      if(kkdARutEjI == true){kkdARutEjI = false;}
      if(tQKspoEFZd == true){tQKspoEFZd = false;}
      if(GcdUXPYbLc == true){GcdUXPYbLc = false;}
      if(uZfIMjSLKf == true){uZfIMjSLKf = false;}
      if(PnqzhHVGGA == true){PnqzhHVGGA = false;}
      if(ETulIHGJbB == true){ETulIHGJbB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWYZHSQFUY
{ 
  void YWxxVzHCGS()
  { 
      bool dFrxUxGwef = false;
      bool QuZdYsGXjE = false;
      bool NqVcLoZCGd = false;
      bool dIouOmZBOL = false;
      bool iMWCTJTeHz = false;
      bool zlmnkmiOke = false;
      bool XEoBCHFePk = false;
      bool SEIYVATTIC = false;
      bool VuuGeqVAJb = false;
      bool EKQjmdXVzM = false;
      bool DoPWgtdNSj = false;
      bool SPGiIbIhWL = false;
      bool kFVmgHnYkq = false;
      bool cyTwzgfYZj = false;
      bool NIgYInEgaL = false;
      bool UoynaxSboY = false;
      bool GEbbHTuKjb = false;
      bool wjImycYwdr = false;
      bool DGxZVnAfVB = false;
      bool NDiAdIfERo = false;
      string cpLqmAETjl;
      string UWWwUeyItc;
      string cuFYTKBORt;
      string PAYogTGYlC;
      string nZpetqfBqu;
      string HmmYchjmXb;
      string zoCpWTxhPB;
      string YYVqoCFZdb;
      string eAXVlbNAMz;
      string iTBJDyWzIa;
      string txkpWhRujZ;
      string bKIuxyQgDt;
      string GwUQREXLnp;
      string fFQDhgOgyD;
      string KRQmWXKFME;
      string gpwOUxcUXR;
      string KFHstWsFNP;
      string jiizinfhts;
      string sRziIpJCik;
      string EtJfsFKWsz;
      if(cpLqmAETjl == txkpWhRujZ){dFrxUxGwef = true;}
      else if(txkpWhRujZ == cpLqmAETjl){DoPWgtdNSj = true;}
      if(UWWwUeyItc == bKIuxyQgDt){QuZdYsGXjE = true;}
      else if(bKIuxyQgDt == UWWwUeyItc){SPGiIbIhWL = true;}
      if(cuFYTKBORt == GwUQREXLnp){NqVcLoZCGd = true;}
      else if(GwUQREXLnp == cuFYTKBORt){kFVmgHnYkq = true;}
      if(PAYogTGYlC == fFQDhgOgyD){dIouOmZBOL = true;}
      else if(fFQDhgOgyD == PAYogTGYlC){cyTwzgfYZj = true;}
      if(nZpetqfBqu == KRQmWXKFME){iMWCTJTeHz = true;}
      else if(KRQmWXKFME == nZpetqfBqu){NIgYInEgaL = true;}
      if(HmmYchjmXb == gpwOUxcUXR){zlmnkmiOke = true;}
      else if(gpwOUxcUXR == HmmYchjmXb){UoynaxSboY = true;}
      if(zoCpWTxhPB == KFHstWsFNP){XEoBCHFePk = true;}
      else if(KFHstWsFNP == zoCpWTxhPB){GEbbHTuKjb = true;}
      if(YYVqoCFZdb == jiizinfhts){SEIYVATTIC = true;}
      if(eAXVlbNAMz == sRziIpJCik){VuuGeqVAJb = true;}
      if(iTBJDyWzIa == EtJfsFKWsz){EKQjmdXVzM = true;}
      while(jiizinfhts == YYVqoCFZdb){wjImycYwdr = true;}
      while(sRziIpJCik == sRziIpJCik){DGxZVnAfVB = true;}
      while(EtJfsFKWsz == EtJfsFKWsz){NDiAdIfERo = true;}
      if(dFrxUxGwef == true){dFrxUxGwef = false;}
      if(QuZdYsGXjE == true){QuZdYsGXjE = false;}
      if(NqVcLoZCGd == true){NqVcLoZCGd = false;}
      if(dIouOmZBOL == true){dIouOmZBOL = false;}
      if(iMWCTJTeHz == true){iMWCTJTeHz = false;}
      if(zlmnkmiOke == true){zlmnkmiOke = false;}
      if(XEoBCHFePk == true){XEoBCHFePk = false;}
      if(SEIYVATTIC == true){SEIYVATTIC = false;}
      if(VuuGeqVAJb == true){VuuGeqVAJb = false;}
      if(EKQjmdXVzM == true){EKQjmdXVzM = false;}
      if(DoPWgtdNSj == true){DoPWgtdNSj = false;}
      if(SPGiIbIhWL == true){SPGiIbIhWL = false;}
      if(kFVmgHnYkq == true){kFVmgHnYkq = false;}
      if(cyTwzgfYZj == true){cyTwzgfYZj = false;}
      if(NIgYInEgaL == true){NIgYInEgaL = false;}
      if(UoynaxSboY == true){UoynaxSboY = false;}
      if(GEbbHTuKjb == true){GEbbHTuKjb = false;}
      if(wjImycYwdr == true){wjImycYwdr = false;}
      if(DGxZVnAfVB == true){DGxZVnAfVB = false;}
      if(NDiAdIfERo == true){NDiAdIfERo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJMKIYVNZY
{ 
  void WaWwFXmMVM()
  { 
      bool pxmXKVRfwm = false;
      bool CxZOGTkwcw = false;
      bool mwQOgJOxlr = false;
      bool WphailpAnM = false;
      bool LNLebDYzdV = false;
      bool INiFAsfXpA = false;
      bool HUsEQLPyfT = false;
      bool cjIPkYklmc = false;
      bool kOSQiIHcZp = false;
      bool GSKmFqUGNQ = false;
      bool nZTKrYFSUa = false;
      bool HskMPrBbUI = false;
      bool EmYpMJYUKt = false;
      bool EdXVoLuIYJ = false;
      bool CnIyhMhxXN = false;
      bool oslFMBAdxh = false;
      bool zjIZWcVOXD = false;
      bool wsCKFPeZHA = false;
      bool bbwwEKrSJn = false;
      bool KQKpKRfhbF = false;
      string AWapSjMzdS;
      string RUOuEqddFf;
      string kxPItTaXJW;
      string lLZVGwWIYY;
      string SybDMbnNOb;
      string dtsHpDHSwy;
      string JnpGfFtsnI;
      string UVFgMlVMuR;
      string fNIgsrSSfD;
      string oELZOeIUWH;
      string guZGGHoMtD;
      string htWeSweINn;
      string mbMjSQKeRh;
      string cApmjjmCal;
      string CFYbUtggGS;
      string zAHhUFhomp;
      string xJuLZgEjti;
      string IchbkgDjOY;
      string jcYyicsHSe;
      string ByOjosKMCn;
      if(AWapSjMzdS == guZGGHoMtD){pxmXKVRfwm = true;}
      else if(guZGGHoMtD == AWapSjMzdS){nZTKrYFSUa = true;}
      if(RUOuEqddFf == htWeSweINn){CxZOGTkwcw = true;}
      else if(htWeSweINn == RUOuEqddFf){HskMPrBbUI = true;}
      if(kxPItTaXJW == mbMjSQKeRh){mwQOgJOxlr = true;}
      else if(mbMjSQKeRh == kxPItTaXJW){EmYpMJYUKt = true;}
      if(lLZVGwWIYY == cApmjjmCal){WphailpAnM = true;}
      else if(cApmjjmCal == lLZVGwWIYY){EdXVoLuIYJ = true;}
      if(SybDMbnNOb == CFYbUtggGS){LNLebDYzdV = true;}
      else if(CFYbUtggGS == SybDMbnNOb){CnIyhMhxXN = true;}
      if(dtsHpDHSwy == zAHhUFhomp){INiFAsfXpA = true;}
      else if(zAHhUFhomp == dtsHpDHSwy){oslFMBAdxh = true;}
      if(JnpGfFtsnI == xJuLZgEjti){HUsEQLPyfT = true;}
      else if(xJuLZgEjti == JnpGfFtsnI){zjIZWcVOXD = true;}
      if(UVFgMlVMuR == IchbkgDjOY){cjIPkYklmc = true;}
      if(fNIgsrSSfD == jcYyicsHSe){kOSQiIHcZp = true;}
      if(oELZOeIUWH == ByOjosKMCn){GSKmFqUGNQ = true;}
      while(IchbkgDjOY == UVFgMlVMuR){wsCKFPeZHA = true;}
      while(jcYyicsHSe == jcYyicsHSe){bbwwEKrSJn = true;}
      while(ByOjosKMCn == ByOjosKMCn){KQKpKRfhbF = true;}
      if(pxmXKVRfwm == true){pxmXKVRfwm = false;}
      if(CxZOGTkwcw == true){CxZOGTkwcw = false;}
      if(mwQOgJOxlr == true){mwQOgJOxlr = false;}
      if(WphailpAnM == true){WphailpAnM = false;}
      if(LNLebDYzdV == true){LNLebDYzdV = false;}
      if(INiFAsfXpA == true){INiFAsfXpA = false;}
      if(HUsEQLPyfT == true){HUsEQLPyfT = false;}
      if(cjIPkYklmc == true){cjIPkYklmc = false;}
      if(kOSQiIHcZp == true){kOSQiIHcZp = false;}
      if(GSKmFqUGNQ == true){GSKmFqUGNQ = false;}
      if(nZTKrYFSUa == true){nZTKrYFSUa = false;}
      if(HskMPrBbUI == true){HskMPrBbUI = false;}
      if(EmYpMJYUKt == true){EmYpMJYUKt = false;}
      if(EdXVoLuIYJ == true){EdXVoLuIYJ = false;}
      if(CnIyhMhxXN == true){CnIyhMhxXN = false;}
      if(oslFMBAdxh == true){oslFMBAdxh = false;}
      if(zjIZWcVOXD == true){zjIZWcVOXD = false;}
      if(wsCKFPeZHA == true){wsCKFPeZHA = false;}
      if(bbwwEKrSJn == true){bbwwEKrSJn = false;}
      if(KQKpKRfhbF == true){KQKpKRfhbF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URLBIJCEAK
{ 
  void yeKCnXCqyH()
  { 
      bool nHwORBojcE = false;
      bool xSNIfJwKEk = false;
      bool DuDldBDxUb = false;
      bool nWxJBssxsp = false;
      bool bCGDRTNKDU = false;
      bool FwNPMsEJkQ = false;
      bool yqOBQZUEGm = false;
      bool PyQOIAnzUK = false;
      bool nrtAVqJhwH = false;
      bool njMcqjmFmr = false;
      bool yIEPEHfzHL = false;
      bool EFoacGxOeY = false;
      bool QmHyyeknWX = false;
      bool NiLbLemduO = false;
      bool LJZkDiulAk = false;
      bool mXZNbLBGRY = false;
      bool WqcixVsMOx = false;
      bool STSQNGMVuP = false;
      bool jynkkoJxAA = false;
      bool cgMVqTgqng = false;
      string elmHlFtnjw;
      string ErAArzjdxD;
      string umfkLskfYq;
      string yZNAHtqupF;
      string ajFtCTUIFI;
      string anUnDrGCur;
      string TOOsyddArx;
      string HnnrbKhkhr;
      string YcZQPJFZwP;
      string nnAxkMVLuY;
      string pUPIAlzbLr;
      string KUUDTpnycn;
      string YDDcJTmqGP;
      string oVpIBDNRQc;
      string KcOEESSxdu;
      string XWiGAlRlyf;
      string zIVwDodLBP;
      string cWhzduoyYp;
      string ApMLqRliIO;
      string laSjdBHRBP;
      if(elmHlFtnjw == pUPIAlzbLr){nHwORBojcE = true;}
      else if(pUPIAlzbLr == elmHlFtnjw){yIEPEHfzHL = true;}
      if(ErAArzjdxD == KUUDTpnycn){xSNIfJwKEk = true;}
      else if(KUUDTpnycn == ErAArzjdxD){EFoacGxOeY = true;}
      if(umfkLskfYq == YDDcJTmqGP){DuDldBDxUb = true;}
      else if(YDDcJTmqGP == umfkLskfYq){QmHyyeknWX = true;}
      if(yZNAHtqupF == oVpIBDNRQc){nWxJBssxsp = true;}
      else if(oVpIBDNRQc == yZNAHtqupF){NiLbLemduO = true;}
      if(ajFtCTUIFI == KcOEESSxdu){bCGDRTNKDU = true;}
      else if(KcOEESSxdu == ajFtCTUIFI){LJZkDiulAk = true;}
      if(anUnDrGCur == XWiGAlRlyf){FwNPMsEJkQ = true;}
      else if(XWiGAlRlyf == anUnDrGCur){mXZNbLBGRY = true;}
      if(TOOsyddArx == zIVwDodLBP){yqOBQZUEGm = true;}
      else if(zIVwDodLBP == TOOsyddArx){WqcixVsMOx = true;}
      if(HnnrbKhkhr == cWhzduoyYp){PyQOIAnzUK = true;}
      if(YcZQPJFZwP == ApMLqRliIO){nrtAVqJhwH = true;}
      if(nnAxkMVLuY == laSjdBHRBP){njMcqjmFmr = true;}
      while(cWhzduoyYp == HnnrbKhkhr){STSQNGMVuP = true;}
      while(ApMLqRliIO == ApMLqRliIO){jynkkoJxAA = true;}
      while(laSjdBHRBP == laSjdBHRBP){cgMVqTgqng = true;}
      if(nHwORBojcE == true){nHwORBojcE = false;}
      if(xSNIfJwKEk == true){xSNIfJwKEk = false;}
      if(DuDldBDxUb == true){DuDldBDxUb = false;}
      if(nWxJBssxsp == true){nWxJBssxsp = false;}
      if(bCGDRTNKDU == true){bCGDRTNKDU = false;}
      if(FwNPMsEJkQ == true){FwNPMsEJkQ = false;}
      if(yqOBQZUEGm == true){yqOBQZUEGm = false;}
      if(PyQOIAnzUK == true){PyQOIAnzUK = false;}
      if(nrtAVqJhwH == true){nrtAVqJhwH = false;}
      if(njMcqjmFmr == true){njMcqjmFmr = false;}
      if(yIEPEHfzHL == true){yIEPEHfzHL = false;}
      if(EFoacGxOeY == true){EFoacGxOeY = false;}
      if(QmHyyeknWX == true){QmHyyeknWX = false;}
      if(NiLbLemduO == true){NiLbLemduO = false;}
      if(LJZkDiulAk == true){LJZkDiulAk = false;}
      if(mXZNbLBGRY == true){mXZNbLBGRY = false;}
      if(WqcixVsMOx == true){WqcixVsMOx = false;}
      if(STSQNGMVuP == true){STSQNGMVuP = false;}
      if(jynkkoJxAA == true){jynkkoJxAA = false;}
      if(cgMVqTgqng == true){cgMVqTgqng = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYBVOXOANQ
{ 
  void FGERffgPJl()
  { 
      bool bKybRJuSyk = false;
      bool NqpUkhSnVN = false;
      bool gSYBUeAuoi = false;
      bool SxZtJWXirG = false;
      bool llADojGcXN = false;
      bool XTEHyJlwGl = false;
      bool JAcOSQRuKO = false;
      bool JiwObtRUMj = false;
      bool YWXaKzsRwA = false;
      bool jbbFxlIkkY = false;
      bool RLRIDnWofD = false;
      bool qRiVNlcCDT = false;
      bool XzzKehGqRo = false;
      bool lfjnRNEOXW = false;
      bool bDlsISrGrK = false;
      bool IGhRBSMGdV = false;
      bool gfWpRKguDA = false;
      bool gNdgqTNGCL = false;
      bool pAyHfeySmz = false;
      bool AxjBowfuax = false;
      string tOwlkueFrn;
      string rVwNXuUTfm;
      string hBkjjPkmVd;
      string LAQpHLAzDs;
      string DRDumaEPxT;
      string zdpttsdMCV;
      string KriOcrFGGM;
      string tVQmjQxowJ;
      string LVoCdhJVuN;
      string gnwhiKhnSu;
      string UxIkZdMCKd;
      string unPsJoCgkt;
      string hiLreGZiEY;
      string hIWBnNMEcA;
      string UHLQSsYDXt;
      string IADXMklPGS;
      string EdylumRNEw;
      string byEkZaXtZk;
      string gVKJPhFyoC;
      string awyJuqIZUf;
      if(tOwlkueFrn == UxIkZdMCKd){bKybRJuSyk = true;}
      else if(UxIkZdMCKd == tOwlkueFrn){RLRIDnWofD = true;}
      if(rVwNXuUTfm == unPsJoCgkt){NqpUkhSnVN = true;}
      else if(unPsJoCgkt == rVwNXuUTfm){qRiVNlcCDT = true;}
      if(hBkjjPkmVd == hiLreGZiEY){gSYBUeAuoi = true;}
      else if(hiLreGZiEY == hBkjjPkmVd){XzzKehGqRo = true;}
      if(LAQpHLAzDs == hIWBnNMEcA){SxZtJWXirG = true;}
      else if(hIWBnNMEcA == LAQpHLAzDs){lfjnRNEOXW = true;}
      if(DRDumaEPxT == UHLQSsYDXt){llADojGcXN = true;}
      else if(UHLQSsYDXt == DRDumaEPxT){bDlsISrGrK = true;}
      if(zdpttsdMCV == IADXMklPGS){XTEHyJlwGl = true;}
      else if(IADXMklPGS == zdpttsdMCV){IGhRBSMGdV = true;}
      if(KriOcrFGGM == EdylumRNEw){JAcOSQRuKO = true;}
      else if(EdylumRNEw == KriOcrFGGM){gfWpRKguDA = true;}
      if(tVQmjQxowJ == byEkZaXtZk){JiwObtRUMj = true;}
      if(LVoCdhJVuN == gVKJPhFyoC){YWXaKzsRwA = true;}
      if(gnwhiKhnSu == awyJuqIZUf){jbbFxlIkkY = true;}
      while(byEkZaXtZk == tVQmjQxowJ){gNdgqTNGCL = true;}
      while(gVKJPhFyoC == gVKJPhFyoC){pAyHfeySmz = true;}
      while(awyJuqIZUf == awyJuqIZUf){AxjBowfuax = true;}
      if(bKybRJuSyk == true){bKybRJuSyk = false;}
      if(NqpUkhSnVN == true){NqpUkhSnVN = false;}
      if(gSYBUeAuoi == true){gSYBUeAuoi = false;}
      if(SxZtJWXirG == true){SxZtJWXirG = false;}
      if(llADojGcXN == true){llADojGcXN = false;}
      if(XTEHyJlwGl == true){XTEHyJlwGl = false;}
      if(JAcOSQRuKO == true){JAcOSQRuKO = false;}
      if(JiwObtRUMj == true){JiwObtRUMj = false;}
      if(YWXaKzsRwA == true){YWXaKzsRwA = false;}
      if(jbbFxlIkkY == true){jbbFxlIkkY = false;}
      if(RLRIDnWofD == true){RLRIDnWofD = false;}
      if(qRiVNlcCDT == true){qRiVNlcCDT = false;}
      if(XzzKehGqRo == true){XzzKehGqRo = false;}
      if(lfjnRNEOXW == true){lfjnRNEOXW = false;}
      if(bDlsISrGrK == true){bDlsISrGrK = false;}
      if(IGhRBSMGdV == true){IGhRBSMGdV = false;}
      if(gfWpRKguDA == true){gfWpRKguDA = false;}
      if(gNdgqTNGCL == true){gNdgqTNGCL = false;}
      if(pAyHfeySmz == true){pAyHfeySmz = false;}
      if(AxjBowfuax == true){AxjBowfuax = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYOFRUFVXZ
{ 
  void VFTNhEPAsr()
  { 
      bool lPNeoEWYCw = false;
      bool xbZqscjicC = false;
      bool QgqZkadqkz = false;
      bool JUaPftxbzR = false;
      bool XWgbWruaEi = false;
      bool iucrMEXmtN = false;
      bool ZenDlcBJKz = false;
      bool fIjKdtAPDr = false;
      bool eDlCPNrhCa = false;
      bool VJgkqshdpt = false;
      bool qlQFCaLSOS = false;
      bool EIjCiWrlmX = false;
      bool kTHjcWazTk = false;
      bool LWZIAslgzo = false;
      bool BYSiWNYeBT = false;
      bool AwpRJWdfcf = false;
      bool AMzdHgiaBp = false;
      bool jLlyWLAXMO = false;
      bool xuxzkOgHzc = false;
      bool OGESooZobp = false;
      string mkJEIXJVpu;
      string dLjshICLsG;
      string HSQzPFwdih;
      string apBVopOkLx;
      string HsdQPQaGWn;
      string YhqXVTTJnC;
      string afmHUnKOEr;
      string tQAuzOozjz;
      string epGuIrydAU;
      string WExIVaFVwa;
      string FMCesHhwXG;
      string eTYnXkYryb;
      string pgOiUoTqYY;
      string ISDIsSnbBB;
      string JBFspCfIjk;
      string BNWTjYxSJD;
      string nqWzyMQPtF;
      string wxpxRnaVsS;
      string JKGnWuuiXU;
      string UVSyMSeFud;
      if(mkJEIXJVpu == FMCesHhwXG){lPNeoEWYCw = true;}
      else if(FMCesHhwXG == mkJEIXJVpu){qlQFCaLSOS = true;}
      if(dLjshICLsG == eTYnXkYryb){xbZqscjicC = true;}
      else if(eTYnXkYryb == dLjshICLsG){EIjCiWrlmX = true;}
      if(HSQzPFwdih == pgOiUoTqYY){QgqZkadqkz = true;}
      else if(pgOiUoTqYY == HSQzPFwdih){kTHjcWazTk = true;}
      if(apBVopOkLx == ISDIsSnbBB){JUaPftxbzR = true;}
      else if(ISDIsSnbBB == apBVopOkLx){LWZIAslgzo = true;}
      if(HsdQPQaGWn == JBFspCfIjk){XWgbWruaEi = true;}
      else if(JBFspCfIjk == HsdQPQaGWn){BYSiWNYeBT = true;}
      if(YhqXVTTJnC == BNWTjYxSJD){iucrMEXmtN = true;}
      else if(BNWTjYxSJD == YhqXVTTJnC){AwpRJWdfcf = true;}
      if(afmHUnKOEr == nqWzyMQPtF){ZenDlcBJKz = true;}
      else if(nqWzyMQPtF == afmHUnKOEr){AMzdHgiaBp = true;}
      if(tQAuzOozjz == wxpxRnaVsS){fIjKdtAPDr = true;}
      if(epGuIrydAU == JKGnWuuiXU){eDlCPNrhCa = true;}
      if(WExIVaFVwa == UVSyMSeFud){VJgkqshdpt = true;}
      while(wxpxRnaVsS == tQAuzOozjz){jLlyWLAXMO = true;}
      while(JKGnWuuiXU == JKGnWuuiXU){xuxzkOgHzc = true;}
      while(UVSyMSeFud == UVSyMSeFud){OGESooZobp = true;}
      if(lPNeoEWYCw == true){lPNeoEWYCw = false;}
      if(xbZqscjicC == true){xbZqscjicC = false;}
      if(QgqZkadqkz == true){QgqZkadqkz = false;}
      if(JUaPftxbzR == true){JUaPftxbzR = false;}
      if(XWgbWruaEi == true){XWgbWruaEi = false;}
      if(iucrMEXmtN == true){iucrMEXmtN = false;}
      if(ZenDlcBJKz == true){ZenDlcBJKz = false;}
      if(fIjKdtAPDr == true){fIjKdtAPDr = false;}
      if(eDlCPNrhCa == true){eDlCPNrhCa = false;}
      if(VJgkqshdpt == true){VJgkqshdpt = false;}
      if(qlQFCaLSOS == true){qlQFCaLSOS = false;}
      if(EIjCiWrlmX == true){EIjCiWrlmX = false;}
      if(kTHjcWazTk == true){kTHjcWazTk = false;}
      if(LWZIAslgzo == true){LWZIAslgzo = false;}
      if(BYSiWNYeBT == true){BYSiWNYeBT = false;}
      if(AwpRJWdfcf == true){AwpRJWdfcf = false;}
      if(AMzdHgiaBp == true){AMzdHgiaBp = false;}
      if(jLlyWLAXMO == true){jLlyWLAXMO = false;}
      if(xuxzkOgHzc == true){xuxzkOgHzc = false;}
      if(OGESooZobp == true){OGESooZobp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORBSHWWPYJ
{ 
  void WaeNsTWddA()
  { 
      bool ofEgMltgqg = false;
      bool aOGtOhHwAw = false;
      bool NFsLuqDMLL = false;
      bool FeMcoZooXy = false;
      bool zxrXnrgzhF = false;
      bool swTZfimrkU = false;
      bool ihUebuBcFn = false;
      bool rSYCxQNVXD = false;
      bool JEdGSILmxF = false;
      bool mwDCPQbMws = false;
      bool pDttMaXRbO = false;
      bool VRUgLeDOMS = false;
      bool jOezAwOVlf = false;
      bool nAYdNFJitq = false;
      bool ksKhjVaVqk = false;
      bool MNzdJaXusP = false;
      bool MBewaUrqTF = false;
      bool UUTVgpDwPe = false;
      bool VreBSZBuUm = false;
      bool gOpeeiNNHO = false;
      string aPZVjrfgWP;
      string KNCnxoRtDu;
      string FXxAdfqKgs;
      string DErKpbnquo;
      string XeVKKEjkFH;
      string bkWdNCRZrD;
      string BVAdLGUrxV;
      string AZyOWaBmpZ;
      string wFEYQShNxn;
      string KOzqmBdryE;
      string irnjGClHGl;
      string BejSHwRaMs;
      string YHtJKlaHaU;
      string wJnkqERTRO;
      string fZGLlfegjq;
      string jDeEfaxdZU;
      string beglorpybC;
      string exIyNyAiWe;
      string GtWjksdjFP;
      string GmtwmBsUVt;
      if(aPZVjrfgWP == irnjGClHGl){ofEgMltgqg = true;}
      else if(irnjGClHGl == aPZVjrfgWP){pDttMaXRbO = true;}
      if(KNCnxoRtDu == BejSHwRaMs){aOGtOhHwAw = true;}
      else if(BejSHwRaMs == KNCnxoRtDu){VRUgLeDOMS = true;}
      if(FXxAdfqKgs == YHtJKlaHaU){NFsLuqDMLL = true;}
      else if(YHtJKlaHaU == FXxAdfqKgs){jOezAwOVlf = true;}
      if(DErKpbnquo == wJnkqERTRO){FeMcoZooXy = true;}
      else if(wJnkqERTRO == DErKpbnquo){nAYdNFJitq = true;}
      if(XeVKKEjkFH == fZGLlfegjq){zxrXnrgzhF = true;}
      else if(fZGLlfegjq == XeVKKEjkFH){ksKhjVaVqk = true;}
      if(bkWdNCRZrD == jDeEfaxdZU){swTZfimrkU = true;}
      else if(jDeEfaxdZU == bkWdNCRZrD){MNzdJaXusP = true;}
      if(BVAdLGUrxV == beglorpybC){ihUebuBcFn = true;}
      else if(beglorpybC == BVAdLGUrxV){MBewaUrqTF = true;}
      if(AZyOWaBmpZ == exIyNyAiWe){rSYCxQNVXD = true;}
      if(wFEYQShNxn == GtWjksdjFP){JEdGSILmxF = true;}
      if(KOzqmBdryE == GmtwmBsUVt){mwDCPQbMws = true;}
      while(exIyNyAiWe == AZyOWaBmpZ){UUTVgpDwPe = true;}
      while(GtWjksdjFP == GtWjksdjFP){VreBSZBuUm = true;}
      while(GmtwmBsUVt == GmtwmBsUVt){gOpeeiNNHO = true;}
      if(ofEgMltgqg == true){ofEgMltgqg = false;}
      if(aOGtOhHwAw == true){aOGtOhHwAw = false;}
      if(NFsLuqDMLL == true){NFsLuqDMLL = false;}
      if(FeMcoZooXy == true){FeMcoZooXy = false;}
      if(zxrXnrgzhF == true){zxrXnrgzhF = false;}
      if(swTZfimrkU == true){swTZfimrkU = false;}
      if(ihUebuBcFn == true){ihUebuBcFn = false;}
      if(rSYCxQNVXD == true){rSYCxQNVXD = false;}
      if(JEdGSILmxF == true){JEdGSILmxF = false;}
      if(mwDCPQbMws == true){mwDCPQbMws = false;}
      if(pDttMaXRbO == true){pDttMaXRbO = false;}
      if(VRUgLeDOMS == true){VRUgLeDOMS = false;}
      if(jOezAwOVlf == true){jOezAwOVlf = false;}
      if(nAYdNFJitq == true){nAYdNFJitq = false;}
      if(ksKhjVaVqk == true){ksKhjVaVqk = false;}
      if(MNzdJaXusP == true){MNzdJaXusP = false;}
      if(MBewaUrqTF == true){MBewaUrqTF = false;}
      if(UUTVgpDwPe == true){UUTVgpDwPe = false;}
      if(VreBSZBuUm == true){VreBSZBuUm = false;}
      if(gOpeeiNNHO == true){gOpeeiNNHO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJZTDHNUSD
{ 
  void PFMwKsHTAS()
  { 
      bool nFVGugmxLN = false;
      bool imuOdeetey = false;
      bool WyQYXmRPDJ = false;
      bool MqAkcJfuUM = false;
      bool ItPciNIMxK = false;
      bool hZkUBpnwhI = false;
      bool PXtBBqlKkU = false;
      bool yjZRobhmoJ = false;
      bool eFRralFfim = false;
      bool UiMLxkANbr = false;
      bool bxbcMyATeY = false;
      bool HBHXcJFBZO = false;
      bool kGaxzOWNTE = false;
      bool bULxhgcofc = false;
      bool lkAKfTbnim = false;
      bool eymNGVVdcx = false;
      bool bmAZwlpJpw = false;
      bool fQVxczFQRf = false;
      bool mhefZdgxqM = false;
      bool KzLhBykZNs = false;
      string KTyRiEXHRh;
      string AMxyMjgfor;
      string YadIUFrEAk;
      string KuddSlyHoz;
      string uBmVNXIglH;
      string TECrsjppwd;
      string LSHgWFiSea;
      string kYqpxWnHux;
      string xLSrQGrkji;
      string uILKmbtFyI;
      string noBKWtMMuW;
      string whtzfAAOPQ;
      string MyhwecNfCV;
      string bhJlIHJHVW;
      string sepNmNNLel;
      string afphupHFfs;
      string gfKYtOYHpY;
      string qsrsWgHTJR;
      string OBBPtwqaqR;
      string ADabpMUQTX;
      if(KTyRiEXHRh == noBKWtMMuW){nFVGugmxLN = true;}
      else if(noBKWtMMuW == KTyRiEXHRh){bxbcMyATeY = true;}
      if(AMxyMjgfor == whtzfAAOPQ){imuOdeetey = true;}
      else if(whtzfAAOPQ == AMxyMjgfor){HBHXcJFBZO = true;}
      if(YadIUFrEAk == MyhwecNfCV){WyQYXmRPDJ = true;}
      else if(MyhwecNfCV == YadIUFrEAk){kGaxzOWNTE = true;}
      if(KuddSlyHoz == bhJlIHJHVW){MqAkcJfuUM = true;}
      else if(bhJlIHJHVW == KuddSlyHoz){bULxhgcofc = true;}
      if(uBmVNXIglH == sepNmNNLel){ItPciNIMxK = true;}
      else if(sepNmNNLel == uBmVNXIglH){lkAKfTbnim = true;}
      if(TECrsjppwd == afphupHFfs){hZkUBpnwhI = true;}
      else if(afphupHFfs == TECrsjppwd){eymNGVVdcx = true;}
      if(LSHgWFiSea == gfKYtOYHpY){PXtBBqlKkU = true;}
      else if(gfKYtOYHpY == LSHgWFiSea){bmAZwlpJpw = true;}
      if(kYqpxWnHux == qsrsWgHTJR){yjZRobhmoJ = true;}
      if(xLSrQGrkji == OBBPtwqaqR){eFRralFfim = true;}
      if(uILKmbtFyI == ADabpMUQTX){UiMLxkANbr = true;}
      while(qsrsWgHTJR == kYqpxWnHux){fQVxczFQRf = true;}
      while(OBBPtwqaqR == OBBPtwqaqR){mhefZdgxqM = true;}
      while(ADabpMUQTX == ADabpMUQTX){KzLhBykZNs = true;}
      if(nFVGugmxLN == true){nFVGugmxLN = false;}
      if(imuOdeetey == true){imuOdeetey = false;}
      if(WyQYXmRPDJ == true){WyQYXmRPDJ = false;}
      if(MqAkcJfuUM == true){MqAkcJfuUM = false;}
      if(ItPciNIMxK == true){ItPciNIMxK = false;}
      if(hZkUBpnwhI == true){hZkUBpnwhI = false;}
      if(PXtBBqlKkU == true){PXtBBqlKkU = false;}
      if(yjZRobhmoJ == true){yjZRobhmoJ = false;}
      if(eFRralFfim == true){eFRralFfim = false;}
      if(UiMLxkANbr == true){UiMLxkANbr = false;}
      if(bxbcMyATeY == true){bxbcMyATeY = false;}
      if(HBHXcJFBZO == true){HBHXcJFBZO = false;}
      if(kGaxzOWNTE == true){kGaxzOWNTE = false;}
      if(bULxhgcofc == true){bULxhgcofc = false;}
      if(lkAKfTbnim == true){lkAKfTbnim = false;}
      if(eymNGVVdcx == true){eymNGVVdcx = false;}
      if(bmAZwlpJpw == true){bmAZwlpJpw = false;}
      if(fQVxczFQRf == true){fQVxczFQRf = false;}
      if(mhefZdgxqM == true){mhefZdgxqM = false;}
      if(KzLhBykZNs == true){KzLhBykZNs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZXGRBWKRWP
{ 
  void nYEDVfOigT()
  { 
      bool qMSOFsZSMg = false;
      bool famqhLtbUe = false;
      bool ObCuklTMuO = false;
      bool WattSfFyux = false;
      bool eCkRIXcmVb = false;
      bool XjdFSPJWcS = false;
      bool ZNWyKEgrYC = false;
      bool GwfXALqjlN = false;
      bool JfpSplwnbD = false;
      bool VhUbWQelHD = false;
      bool qjOTVbDGFG = false;
      bool XZkPIsWDIX = false;
      bool HrQUfXaDAi = false;
      bool gEbhWYRWxN = false;
      bool hphVewxFSd = false;
      bool sadiuyTsmx = false;
      bool BzFWYTxCsj = false;
      bool aAGtpRKuoj = false;
      bool aUjWoFarmX = false;
      bool EXiAMhjLwL = false;
      string ZKybNSyqtK;
      string zhSZQhGiDO;
      string ikwgLPCHgD;
      string KFwSMBwxkF;
      string LyCBfaFSuS;
      string TQhtRoORPx;
      string QpJqAtkANP;
      string kIyxCkhtAj;
      string JiLNisXBBW;
      string lehmoVnKBl;
      string oFEfhKSjrf;
      string GTQengdwIH;
      string VjzqcGaLIg;
      string wXsOuEdfeX;
      string ZmJUPSNCyH;
      string qqCtPFFNCa;
      string jHbKjiaBjj;
      string CxQjghZeaK;
      string rXMApEUyzo;
      string yQdEnSLykg;
      if(ZKybNSyqtK == oFEfhKSjrf){qMSOFsZSMg = true;}
      else if(oFEfhKSjrf == ZKybNSyqtK){qjOTVbDGFG = true;}
      if(zhSZQhGiDO == GTQengdwIH){famqhLtbUe = true;}
      else if(GTQengdwIH == zhSZQhGiDO){XZkPIsWDIX = true;}
      if(ikwgLPCHgD == VjzqcGaLIg){ObCuklTMuO = true;}
      else if(VjzqcGaLIg == ikwgLPCHgD){HrQUfXaDAi = true;}
      if(KFwSMBwxkF == wXsOuEdfeX){WattSfFyux = true;}
      else if(wXsOuEdfeX == KFwSMBwxkF){gEbhWYRWxN = true;}
      if(LyCBfaFSuS == ZmJUPSNCyH){eCkRIXcmVb = true;}
      else if(ZmJUPSNCyH == LyCBfaFSuS){hphVewxFSd = true;}
      if(TQhtRoORPx == qqCtPFFNCa){XjdFSPJWcS = true;}
      else if(qqCtPFFNCa == TQhtRoORPx){sadiuyTsmx = true;}
      if(QpJqAtkANP == jHbKjiaBjj){ZNWyKEgrYC = true;}
      else if(jHbKjiaBjj == QpJqAtkANP){BzFWYTxCsj = true;}
      if(kIyxCkhtAj == CxQjghZeaK){GwfXALqjlN = true;}
      if(JiLNisXBBW == rXMApEUyzo){JfpSplwnbD = true;}
      if(lehmoVnKBl == yQdEnSLykg){VhUbWQelHD = true;}
      while(CxQjghZeaK == kIyxCkhtAj){aAGtpRKuoj = true;}
      while(rXMApEUyzo == rXMApEUyzo){aUjWoFarmX = true;}
      while(yQdEnSLykg == yQdEnSLykg){EXiAMhjLwL = true;}
      if(qMSOFsZSMg == true){qMSOFsZSMg = false;}
      if(famqhLtbUe == true){famqhLtbUe = false;}
      if(ObCuklTMuO == true){ObCuklTMuO = false;}
      if(WattSfFyux == true){WattSfFyux = false;}
      if(eCkRIXcmVb == true){eCkRIXcmVb = false;}
      if(XjdFSPJWcS == true){XjdFSPJWcS = false;}
      if(ZNWyKEgrYC == true){ZNWyKEgrYC = false;}
      if(GwfXALqjlN == true){GwfXALqjlN = false;}
      if(JfpSplwnbD == true){JfpSplwnbD = false;}
      if(VhUbWQelHD == true){VhUbWQelHD = false;}
      if(qjOTVbDGFG == true){qjOTVbDGFG = false;}
      if(XZkPIsWDIX == true){XZkPIsWDIX = false;}
      if(HrQUfXaDAi == true){HrQUfXaDAi = false;}
      if(gEbhWYRWxN == true){gEbhWYRWxN = false;}
      if(hphVewxFSd == true){hphVewxFSd = false;}
      if(sadiuyTsmx == true){sadiuyTsmx = false;}
      if(BzFWYTxCsj == true){BzFWYTxCsj = false;}
      if(aAGtpRKuoj == true){aAGtpRKuoj = false;}
      if(aUjWoFarmX == true){aUjWoFarmX = false;}
      if(EXiAMhjLwL == true){EXiAMhjLwL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVPNWAKUCR
{ 
  void MQfjqzNpAS()
  { 
      bool KzKWxVfzPk = false;
      bool UWuWNoMJxM = false;
      bool fNlJlmuueJ = false;
      bool NzwTrxaBUw = false;
      bool IxsXwabKbr = false;
      bool GtYHRwNAjJ = false;
      bool ajUGXVabeP = false;
      bool OKnBEhTNNL = false;
      bool LjTlCSZnBu = false;
      bool jaQLUYcmAZ = false;
      bool AzeLduGXDj = false;
      bool bzlYypPhDE = false;
      bool wlaifmtcff = false;
      bool FgNnKLFIIH = false;
      bool MBkRSjorMd = false;
      bool ItjwdNYwfp = false;
      bool BcrXdulxNm = false;
      bool kGYurtBIPu = false;
      bool yBPBWKwRKx = false;
      bool lIcSGiJNnX = false;
      string WyUdkmSBVB;
      string qgFnugDbTk;
      string zwzulBARLt;
      string zMDpkEfLPp;
      string jrHZfdoJAF;
      string ndehNZyYqj;
      string mBpaBedODp;
      string AqLdAHoZOI;
      string MqQFFVgUbL;
      string GGUeDiBgXB;
      string AZFJFxRBhG;
      string kYKiWujkUf;
      string xJlrjtWfZR;
      string FIBNHlkHAI;
      string DfmVZhwkHH;
      string zQLrDqnNZK;
      string akbPBbWwak;
      string KckMbRVQRC;
      string xkXRSnwJJQ;
      string yXgohSEWUy;
      if(WyUdkmSBVB == AZFJFxRBhG){KzKWxVfzPk = true;}
      else if(AZFJFxRBhG == WyUdkmSBVB){AzeLduGXDj = true;}
      if(qgFnugDbTk == kYKiWujkUf){UWuWNoMJxM = true;}
      else if(kYKiWujkUf == qgFnugDbTk){bzlYypPhDE = true;}
      if(zwzulBARLt == xJlrjtWfZR){fNlJlmuueJ = true;}
      else if(xJlrjtWfZR == zwzulBARLt){wlaifmtcff = true;}
      if(zMDpkEfLPp == FIBNHlkHAI){NzwTrxaBUw = true;}
      else if(FIBNHlkHAI == zMDpkEfLPp){FgNnKLFIIH = true;}
      if(jrHZfdoJAF == DfmVZhwkHH){IxsXwabKbr = true;}
      else if(DfmVZhwkHH == jrHZfdoJAF){MBkRSjorMd = true;}
      if(ndehNZyYqj == zQLrDqnNZK){GtYHRwNAjJ = true;}
      else if(zQLrDqnNZK == ndehNZyYqj){ItjwdNYwfp = true;}
      if(mBpaBedODp == akbPBbWwak){ajUGXVabeP = true;}
      else if(akbPBbWwak == mBpaBedODp){BcrXdulxNm = true;}
      if(AqLdAHoZOI == KckMbRVQRC){OKnBEhTNNL = true;}
      if(MqQFFVgUbL == xkXRSnwJJQ){LjTlCSZnBu = true;}
      if(GGUeDiBgXB == yXgohSEWUy){jaQLUYcmAZ = true;}
      while(KckMbRVQRC == AqLdAHoZOI){kGYurtBIPu = true;}
      while(xkXRSnwJJQ == xkXRSnwJJQ){yBPBWKwRKx = true;}
      while(yXgohSEWUy == yXgohSEWUy){lIcSGiJNnX = true;}
      if(KzKWxVfzPk == true){KzKWxVfzPk = false;}
      if(UWuWNoMJxM == true){UWuWNoMJxM = false;}
      if(fNlJlmuueJ == true){fNlJlmuueJ = false;}
      if(NzwTrxaBUw == true){NzwTrxaBUw = false;}
      if(IxsXwabKbr == true){IxsXwabKbr = false;}
      if(GtYHRwNAjJ == true){GtYHRwNAjJ = false;}
      if(ajUGXVabeP == true){ajUGXVabeP = false;}
      if(OKnBEhTNNL == true){OKnBEhTNNL = false;}
      if(LjTlCSZnBu == true){LjTlCSZnBu = false;}
      if(jaQLUYcmAZ == true){jaQLUYcmAZ = false;}
      if(AzeLduGXDj == true){AzeLduGXDj = false;}
      if(bzlYypPhDE == true){bzlYypPhDE = false;}
      if(wlaifmtcff == true){wlaifmtcff = false;}
      if(FgNnKLFIIH == true){FgNnKLFIIH = false;}
      if(MBkRSjorMd == true){MBkRSjorMd = false;}
      if(ItjwdNYwfp == true){ItjwdNYwfp = false;}
      if(BcrXdulxNm == true){BcrXdulxNm = false;}
      if(kGYurtBIPu == true){kGYurtBIPu = false;}
      if(yBPBWKwRKx == true){yBPBWKwRKx = false;}
      if(lIcSGiJNnX == true){lIcSGiJNnX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEPEDUZPGD
{ 
  void ZiujceAxjs()
  { 
      bool ksfYTlqCkx = false;
      bool YFhEVJgpCu = false;
      bool bkkuktOpbt = false;
      bool MqVcKOLOnS = false;
      bool iqgydpLtFM = false;
      bool uFWjIAHjmZ = false;
      bool XBZpjgiEsG = false;
      bool xSBjLjDmQt = false;
      bool hUkPzHUlUK = false;
      bool GabOthRpNw = false;
      bool HGAyObDlXX = false;
      bool wUTrqDPJqc = false;
      bool MxjiAWpmpc = false;
      bool SNYUmbTmAW = false;
      bool DiNwNlHjXq = false;
      bool SHykjJWQyr = false;
      bool lQwuEiuyEO = false;
      bool icIUYdjmVN = false;
      bool OGPzKLOmjc = false;
      bool FDoIkmlRrd = false;
      string ioSlYzWtQl;
      string eRlsDleTYb;
      string bCIbOdNZLB;
      string HVYbCzypjW;
      string JNkGRgSGox;
      string JwOdTggqWt;
      string kxiOdJsJpD;
      string nniBRNQCJg;
      string KHkNrKGtHV;
      string SGSplMdWbI;
      string nIQkJVNNMG;
      string PdhpjdMUVT;
      string CyCTkgUsPE;
      string jtaBrCpzDW;
      string wsgBFnYcFH;
      string zIAIFpGwAc;
      string AUxHVVDfxg;
      string nNQyWIQBNw;
      string HqmHEasSuC;
      string wsyaVbuZej;
      if(ioSlYzWtQl == nIQkJVNNMG){ksfYTlqCkx = true;}
      else if(nIQkJVNNMG == ioSlYzWtQl){HGAyObDlXX = true;}
      if(eRlsDleTYb == PdhpjdMUVT){YFhEVJgpCu = true;}
      else if(PdhpjdMUVT == eRlsDleTYb){wUTrqDPJqc = true;}
      if(bCIbOdNZLB == CyCTkgUsPE){bkkuktOpbt = true;}
      else if(CyCTkgUsPE == bCIbOdNZLB){MxjiAWpmpc = true;}
      if(HVYbCzypjW == jtaBrCpzDW){MqVcKOLOnS = true;}
      else if(jtaBrCpzDW == HVYbCzypjW){SNYUmbTmAW = true;}
      if(JNkGRgSGox == wsgBFnYcFH){iqgydpLtFM = true;}
      else if(wsgBFnYcFH == JNkGRgSGox){DiNwNlHjXq = true;}
      if(JwOdTggqWt == zIAIFpGwAc){uFWjIAHjmZ = true;}
      else if(zIAIFpGwAc == JwOdTggqWt){SHykjJWQyr = true;}
      if(kxiOdJsJpD == AUxHVVDfxg){XBZpjgiEsG = true;}
      else if(AUxHVVDfxg == kxiOdJsJpD){lQwuEiuyEO = true;}
      if(nniBRNQCJg == nNQyWIQBNw){xSBjLjDmQt = true;}
      if(KHkNrKGtHV == HqmHEasSuC){hUkPzHUlUK = true;}
      if(SGSplMdWbI == wsyaVbuZej){GabOthRpNw = true;}
      while(nNQyWIQBNw == nniBRNQCJg){icIUYdjmVN = true;}
      while(HqmHEasSuC == HqmHEasSuC){OGPzKLOmjc = true;}
      while(wsyaVbuZej == wsyaVbuZej){FDoIkmlRrd = true;}
      if(ksfYTlqCkx == true){ksfYTlqCkx = false;}
      if(YFhEVJgpCu == true){YFhEVJgpCu = false;}
      if(bkkuktOpbt == true){bkkuktOpbt = false;}
      if(MqVcKOLOnS == true){MqVcKOLOnS = false;}
      if(iqgydpLtFM == true){iqgydpLtFM = false;}
      if(uFWjIAHjmZ == true){uFWjIAHjmZ = false;}
      if(XBZpjgiEsG == true){XBZpjgiEsG = false;}
      if(xSBjLjDmQt == true){xSBjLjDmQt = false;}
      if(hUkPzHUlUK == true){hUkPzHUlUK = false;}
      if(GabOthRpNw == true){GabOthRpNw = false;}
      if(HGAyObDlXX == true){HGAyObDlXX = false;}
      if(wUTrqDPJqc == true){wUTrqDPJqc = false;}
      if(MxjiAWpmpc == true){MxjiAWpmpc = false;}
      if(SNYUmbTmAW == true){SNYUmbTmAW = false;}
      if(DiNwNlHjXq == true){DiNwNlHjXq = false;}
      if(SHykjJWQyr == true){SHykjJWQyr = false;}
      if(lQwuEiuyEO == true){lQwuEiuyEO = false;}
      if(icIUYdjmVN == true){icIUYdjmVN = false;}
      if(OGPzKLOmjc == true){OGPzKLOmjc = false;}
      if(FDoIkmlRrd == true){FDoIkmlRrd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCNRORWWHC
{ 
  void sJgDJsGSDU()
  { 
      bool jWchQcZdWt = false;
      bool iXBSSrsiSe = false;
      bool WZSNEbRnBh = false;
      bool pVRUKusePE = false;
      bool DBAFMKtmlg = false;
      bool NsMTRJDOcn = false;
      bool KlcnDMGgHX = false;
      bool zOTObUZNBt = false;
      bool hdBTTxJxCA = false;
      bool qeBasRYLCz = false;
      bool ENeOhzYxqx = false;
      bool jpNhGgjITF = false;
      bool DIdHfUMsVK = false;
      bool wNLBpUymlU = false;
      bool XLFFQBQTUL = false;
      bool gPqwwuiXhN = false;
      bool lebgBWeLrk = false;
      bool hxVzgrCYpe = false;
      bool DsYJcfVOFt = false;
      bool kaEYisiYEt = false;
      string noSGYyictA;
      string hNxCdTGgrM;
      string TwMAPfGkJU;
      string xtSNWooTVI;
      string nVrPMOwpcY;
      string JxSEBqcSpr;
      string ryTZCmujfn;
      string elKjXxDwmA;
      string iPHjLAaNLe;
      string MVcdPpBSNZ;
      string TMKntXmigE;
      string mffpJbpiNC;
      string LhXAaIIgTg;
      string ukiMgWFSpn;
      string MrfHqgplUm;
      string zSELNknKMk;
      string OFPAICxSJm;
      string WWsZoTCQIt;
      string SVMfgcfWzu;
      string huFEYHcfzn;
      if(noSGYyictA == TMKntXmigE){jWchQcZdWt = true;}
      else if(TMKntXmigE == noSGYyictA){ENeOhzYxqx = true;}
      if(hNxCdTGgrM == mffpJbpiNC){iXBSSrsiSe = true;}
      else if(mffpJbpiNC == hNxCdTGgrM){jpNhGgjITF = true;}
      if(TwMAPfGkJU == LhXAaIIgTg){WZSNEbRnBh = true;}
      else if(LhXAaIIgTg == TwMAPfGkJU){DIdHfUMsVK = true;}
      if(xtSNWooTVI == ukiMgWFSpn){pVRUKusePE = true;}
      else if(ukiMgWFSpn == xtSNWooTVI){wNLBpUymlU = true;}
      if(nVrPMOwpcY == MrfHqgplUm){DBAFMKtmlg = true;}
      else if(MrfHqgplUm == nVrPMOwpcY){XLFFQBQTUL = true;}
      if(JxSEBqcSpr == zSELNknKMk){NsMTRJDOcn = true;}
      else if(zSELNknKMk == JxSEBqcSpr){gPqwwuiXhN = true;}
      if(ryTZCmujfn == OFPAICxSJm){KlcnDMGgHX = true;}
      else if(OFPAICxSJm == ryTZCmujfn){lebgBWeLrk = true;}
      if(elKjXxDwmA == WWsZoTCQIt){zOTObUZNBt = true;}
      if(iPHjLAaNLe == SVMfgcfWzu){hdBTTxJxCA = true;}
      if(MVcdPpBSNZ == huFEYHcfzn){qeBasRYLCz = true;}
      while(WWsZoTCQIt == elKjXxDwmA){hxVzgrCYpe = true;}
      while(SVMfgcfWzu == SVMfgcfWzu){DsYJcfVOFt = true;}
      while(huFEYHcfzn == huFEYHcfzn){kaEYisiYEt = true;}
      if(jWchQcZdWt == true){jWchQcZdWt = false;}
      if(iXBSSrsiSe == true){iXBSSrsiSe = false;}
      if(WZSNEbRnBh == true){WZSNEbRnBh = false;}
      if(pVRUKusePE == true){pVRUKusePE = false;}
      if(DBAFMKtmlg == true){DBAFMKtmlg = false;}
      if(NsMTRJDOcn == true){NsMTRJDOcn = false;}
      if(KlcnDMGgHX == true){KlcnDMGgHX = false;}
      if(zOTObUZNBt == true){zOTObUZNBt = false;}
      if(hdBTTxJxCA == true){hdBTTxJxCA = false;}
      if(qeBasRYLCz == true){qeBasRYLCz = false;}
      if(ENeOhzYxqx == true){ENeOhzYxqx = false;}
      if(jpNhGgjITF == true){jpNhGgjITF = false;}
      if(DIdHfUMsVK == true){DIdHfUMsVK = false;}
      if(wNLBpUymlU == true){wNLBpUymlU = false;}
      if(XLFFQBQTUL == true){XLFFQBQTUL = false;}
      if(gPqwwuiXhN == true){gPqwwuiXhN = false;}
      if(lebgBWeLrk == true){lebgBWeLrk = false;}
      if(hxVzgrCYpe == true){hxVzgrCYpe = false;}
      if(DsYJcfVOFt == true){DsYJcfVOFt = false;}
      if(kaEYisiYEt == true){kaEYisiYEt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BERWIWSXNH
{ 
  void XhwhcXpgCY()
  { 
      bool CcTEoPjCGC = false;
      bool nTzgTbdjsp = false;
      bool mWdNAHrBWt = false;
      bool FWCztKVMFJ = false;
      bool LHLxZJWjuN = false;
      bool HHpfEezFDg = false;
      bool XhfMwQRAmJ = false;
      bool FQeideLfmq = false;
      bool kHFJlygWuO = false;
      bool KQJXkdbzBJ = false;
      bool qVwlHqcHBY = false;
      bool TSRMwPbVZy = false;
      bool jtFXyoHGxA = false;
      bool DMddzOLSBu = false;
      bool UYUVurywaU = false;
      bool BFYDZxQYnS = false;
      bool iVJBVGnnNh = false;
      bool EIUecKZibF = false;
      bool pKebzxmaDC = false;
      bool xmehLzPTzn = false;
      string DyhDkYgTLB;
      string UAfkOWBNLe;
      string lVxfCpxLHg;
      string JhTJsmoidl;
      string AAMrIluOui;
      string WeRxTgACBu;
      string aULdrlgVrb;
      string gSiYekJFWP;
      string uiPXKdQVpM;
      string mlgiKeniAV;
      string FYVTBDwsSh;
      string XtelAqFmTN;
      string VKfeotlANz;
      string wZEAJVNwWG;
      string hWDHnrHuhT;
      string ZAPlAurpdG;
      string RueSlxodbd;
      string dJQMfyHYqx;
      string mpRtZuKRAO;
      string cWRPolrjVq;
      if(DyhDkYgTLB == FYVTBDwsSh){CcTEoPjCGC = true;}
      else if(FYVTBDwsSh == DyhDkYgTLB){qVwlHqcHBY = true;}
      if(UAfkOWBNLe == XtelAqFmTN){nTzgTbdjsp = true;}
      else if(XtelAqFmTN == UAfkOWBNLe){TSRMwPbVZy = true;}
      if(lVxfCpxLHg == VKfeotlANz){mWdNAHrBWt = true;}
      else if(VKfeotlANz == lVxfCpxLHg){jtFXyoHGxA = true;}
      if(JhTJsmoidl == wZEAJVNwWG){FWCztKVMFJ = true;}
      else if(wZEAJVNwWG == JhTJsmoidl){DMddzOLSBu = true;}
      if(AAMrIluOui == hWDHnrHuhT){LHLxZJWjuN = true;}
      else if(hWDHnrHuhT == AAMrIluOui){UYUVurywaU = true;}
      if(WeRxTgACBu == ZAPlAurpdG){HHpfEezFDg = true;}
      else if(ZAPlAurpdG == WeRxTgACBu){BFYDZxQYnS = true;}
      if(aULdrlgVrb == RueSlxodbd){XhfMwQRAmJ = true;}
      else if(RueSlxodbd == aULdrlgVrb){iVJBVGnnNh = true;}
      if(gSiYekJFWP == dJQMfyHYqx){FQeideLfmq = true;}
      if(uiPXKdQVpM == mpRtZuKRAO){kHFJlygWuO = true;}
      if(mlgiKeniAV == cWRPolrjVq){KQJXkdbzBJ = true;}
      while(dJQMfyHYqx == gSiYekJFWP){EIUecKZibF = true;}
      while(mpRtZuKRAO == mpRtZuKRAO){pKebzxmaDC = true;}
      while(cWRPolrjVq == cWRPolrjVq){xmehLzPTzn = true;}
      if(CcTEoPjCGC == true){CcTEoPjCGC = false;}
      if(nTzgTbdjsp == true){nTzgTbdjsp = false;}
      if(mWdNAHrBWt == true){mWdNAHrBWt = false;}
      if(FWCztKVMFJ == true){FWCztKVMFJ = false;}
      if(LHLxZJWjuN == true){LHLxZJWjuN = false;}
      if(HHpfEezFDg == true){HHpfEezFDg = false;}
      if(XhfMwQRAmJ == true){XhfMwQRAmJ = false;}
      if(FQeideLfmq == true){FQeideLfmq = false;}
      if(kHFJlygWuO == true){kHFJlygWuO = false;}
      if(KQJXkdbzBJ == true){KQJXkdbzBJ = false;}
      if(qVwlHqcHBY == true){qVwlHqcHBY = false;}
      if(TSRMwPbVZy == true){TSRMwPbVZy = false;}
      if(jtFXyoHGxA == true){jtFXyoHGxA = false;}
      if(DMddzOLSBu == true){DMddzOLSBu = false;}
      if(UYUVurywaU == true){UYUVurywaU = false;}
      if(BFYDZxQYnS == true){BFYDZxQYnS = false;}
      if(iVJBVGnnNh == true){iVJBVGnnNh = false;}
      if(EIUecKZibF == true){EIUecKZibF = false;}
      if(pKebzxmaDC == true){pKebzxmaDC = false;}
      if(xmehLzPTzn == true){xmehLzPTzn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STZBGGOTYT
{ 
  void enxBjzXbmC()
  { 
      bool zDzkpgsgZM = false;
      bool MnWGubmiXh = false;
      bool MRGFJlxTWd = false;
      bool uNSuCQPsyX = false;
      bool RqxgCqENEC = false;
      bool nOOSKhxtaE = false;
      bool jZKuQzUaDe = false;
      bool MtjAQUUZDS = false;
      bool giPTpgzAjT = false;
      bool TURtmrgBPC = false;
      bool VcJZpteNCp = false;
      bool NWqIXAJqFj = false;
      bool AUqjKqboMX = false;
      bool nSKAxDZodu = false;
      bool BkytGwdJWm = false;
      bool howeCBlZOy = false;
      bool RpBdBtMpKT = false;
      bool ZTMJiPVxcN = false;
      bool NRRYpyVeyw = false;
      bool RAZfcLiUrM = false;
      string ySNnCtUXyY;
      string bdlmgEVEVI;
      string WqormMfycb;
      string DaUJIJZSsu;
      string NwcDVjBwWU;
      string dipauGcVAo;
      string NVtVVAIceW;
      string dCKZuaNkVD;
      string LibIyTktOC;
      string fEREhrBGhV;
      string aXRzpbYPfT;
      string rrAxcdslXB;
      string OOObqYjFrD;
      string ZHDzbnQcRW;
      string uVOtJnEUaD;
      string yOifGMIoIQ;
      string qSXcsknAUo;
      string NQUBGszTSC;
      string UOeoELYWsP;
      string ebTAebxlBX;
      if(ySNnCtUXyY == aXRzpbYPfT){zDzkpgsgZM = true;}
      else if(aXRzpbYPfT == ySNnCtUXyY){VcJZpteNCp = true;}
      if(bdlmgEVEVI == rrAxcdslXB){MnWGubmiXh = true;}
      else if(rrAxcdslXB == bdlmgEVEVI){NWqIXAJqFj = true;}
      if(WqormMfycb == OOObqYjFrD){MRGFJlxTWd = true;}
      else if(OOObqYjFrD == WqormMfycb){AUqjKqboMX = true;}
      if(DaUJIJZSsu == ZHDzbnQcRW){uNSuCQPsyX = true;}
      else if(ZHDzbnQcRW == DaUJIJZSsu){nSKAxDZodu = true;}
      if(NwcDVjBwWU == uVOtJnEUaD){RqxgCqENEC = true;}
      else if(uVOtJnEUaD == NwcDVjBwWU){BkytGwdJWm = true;}
      if(dipauGcVAo == yOifGMIoIQ){nOOSKhxtaE = true;}
      else if(yOifGMIoIQ == dipauGcVAo){howeCBlZOy = true;}
      if(NVtVVAIceW == qSXcsknAUo){jZKuQzUaDe = true;}
      else if(qSXcsknAUo == NVtVVAIceW){RpBdBtMpKT = true;}
      if(dCKZuaNkVD == NQUBGszTSC){MtjAQUUZDS = true;}
      if(LibIyTktOC == UOeoELYWsP){giPTpgzAjT = true;}
      if(fEREhrBGhV == ebTAebxlBX){TURtmrgBPC = true;}
      while(NQUBGszTSC == dCKZuaNkVD){ZTMJiPVxcN = true;}
      while(UOeoELYWsP == UOeoELYWsP){NRRYpyVeyw = true;}
      while(ebTAebxlBX == ebTAebxlBX){RAZfcLiUrM = true;}
      if(zDzkpgsgZM == true){zDzkpgsgZM = false;}
      if(MnWGubmiXh == true){MnWGubmiXh = false;}
      if(MRGFJlxTWd == true){MRGFJlxTWd = false;}
      if(uNSuCQPsyX == true){uNSuCQPsyX = false;}
      if(RqxgCqENEC == true){RqxgCqENEC = false;}
      if(nOOSKhxtaE == true){nOOSKhxtaE = false;}
      if(jZKuQzUaDe == true){jZKuQzUaDe = false;}
      if(MtjAQUUZDS == true){MtjAQUUZDS = false;}
      if(giPTpgzAjT == true){giPTpgzAjT = false;}
      if(TURtmrgBPC == true){TURtmrgBPC = false;}
      if(VcJZpteNCp == true){VcJZpteNCp = false;}
      if(NWqIXAJqFj == true){NWqIXAJqFj = false;}
      if(AUqjKqboMX == true){AUqjKqboMX = false;}
      if(nSKAxDZodu == true){nSKAxDZodu = false;}
      if(BkytGwdJWm == true){BkytGwdJWm = false;}
      if(howeCBlZOy == true){howeCBlZOy = false;}
      if(RpBdBtMpKT == true){RpBdBtMpKT = false;}
      if(ZTMJiPVxcN == true){ZTMJiPVxcN = false;}
      if(NRRYpyVeyw == true){NRRYpyVeyw = false;}
      if(RAZfcLiUrM == true){RAZfcLiUrM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFXPPUUTPV
{ 
  void TmETQfqeBr()
  { 
      bool gXNEtoawOI = false;
      bool rPdguffipC = false;
      bool eCZbOgiFRe = false;
      bool GqarmnPhjs = false;
      bool BhtqTZzkfF = false;
      bool yGLEseykoN = false;
      bool FUeiBBnltG = false;
      bool QyzwAxHhHo = false;
      bool gyYLgzeWyI = false;
      bool pdrVngCKpS = false;
      bool kNqZnzHPDw = false;
      bool WPdAfHuSCB = false;
      bool VRnkPlFcIT = false;
      bool twrnDTGzXg = false;
      bool rPSBkZArpf = false;
      bool kjInxTZFJC = false;
      bool tdHjCZXowL = false;
      bool BwuVJGzlAo = false;
      bool lNlchJnEqj = false;
      bool tBoUmNHizK = false;
      string VXLBCoATdB;
      string dIyIoFFDUF;
      string tGRUHBkwDu;
      string eaNZlqSjDt;
      string RmfDJCrQMD;
      string LPYmWOGqsB;
      string EEPhWCuYVy;
      string lVzamHaNLF;
      string ITiAjOBaCW;
      string kbpCpMWxgG;
      string GTtORoQyzP;
      string nrensjVPxI;
      string AUVzMJfwjZ;
      string jdgFznYTiu;
      string yDamirxCJF;
      string qHzXFlyuBH;
      string JTNYeJKZoE;
      string LBgCJxsiQU;
      string McmdiceIzM;
      string odSakepBHY;
      if(VXLBCoATdB == GTtORoQyzP){gXNEtoawOI = true;}
      else if(GTtORoQyzP == VXLBCoATdB){kNqZnzHPDw = true;}
      if(dIyIoFFDUF == nrensjVPxI){rPdguffipC = true;}
      else if(nrensjVPxI == dIyIoFFDUF){WPdAfHuSCB = true;}
      if(tGRUHBkwDu == AUVzMJfwjZ){eCZbOgiFRe = true;}
      else if(AUVzMJfwjZ == tGRUHBkwDu){VRnkPlFcIT = true;}
      if(eaNZlqSjDt == jdgFznYTiu){GqarmnPhjs = true;}
      else if(jdgFznYTiu == eaNZlqSjDt){twrnDTGzXg = true;}
      if(RmfDJCrQMD == yDamirxCJF){BhtqTZzkfF = true;}
      else if(yDamirxCJF == RmfDJCrQMD){rPSBkZArpf = true;}
      if(LPYmWOGqsB == qHzXFlyuBH){yGLEseykoN = true;}
      else if(qHzXFlyuBH == LPYmWOGqsB){kjInxTZFJC = true;}
      if(EEPhWCuYVy == JTNYeJKZoE){FUeiBBnltG = true;}
      else if(JTNYeJKZoE == EEPhWCuYVy){tdHjCZXowL = true;}
      if(lVzamHaNLF == LBgCJxsiQU){QyzwAxHhHo = true;}
      if(ITiAjOBaCW == McmdiceIzM){gyYLgzeWyI = true;}
      if(kbpCpMWxgG == odSakepBHY){pdrVngCKpS = true;}
      while(LBgCJxsiQU == lVzamHaNLF){BwuVJGzlAo = true;}
      while(McmdiceIzM == McmdiceIzM){lNlchJnEqj = true;}
      while(odSakepBHY == odSakepBHY){tBoUmNHizK = true;}
      if(gXNEtoawOI == true){gXNEtoawOI = false;}
      if(rPdguffipC == true){rPdguffipC = false;}
      if(eCZbOgiFRe == true){eCZbOgiFRe = false;}
      if(GqarmnPhjs == true){GqarmnPhjs = false;}
      if(BhtqTZzkfF == true){BhtqTZzkfF = false;}
      if(yGLEseykoN == true){yGLEseykoN = false;}
      if(FUeiBBnltG == true){FUeiBBnltG = false;}
      if(QyzwAxHhHo == true){QyzwAxHhHo = false;}
      if(gyYLgzeWyI == true){gyYLgzeWyI = false;}
      if(pdrVngCKpS == true){pdrVngCKpS = false;}
      if(kNqZnzHPDw == true){kNqZnzHPDw = false;}
      if(WPdAfHuSCB == true){WPdAfHuSCB = false;}
      if(VRnkPlFcIT == true){VRnkPlFcIT = false;}
      if(twrnDTGzXg == true){twrnDTGzXg = false;}
      if(rPSBkZArpf == true){rPSBkZArpf = false;}
      if(kjInxTZFJC == true){kjInxTZFJC = false;}
      if(tdHjCZXowL == true){tdHjCZXowL = false;}
      if(BwuVJGzlAo == true){BwuVJGzlAo = false;}
      if(lNlchJnEqj == true){lNlchJnEqj = false;}
      if(tBoUmNHizK == true){tBoUmNHizK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TXFCWBBVGS
{ 
  void yKoAyzIIyZ()
  { 
      bool fxMrCcnqMt = false;
      bool eXgYYObfsg = false;
      bool pLOKjxqqnL = false;
      bool PlwwEbKJFn = false;
      bool pahCIBChei = false;
      bool XsobyThCIF = false;
      bool kwCAdsajUw = false;
      bool DRZEqPcLCh = false;
      bool tIMEnVxUyk = false;
      bool sIBADsXhYO = false;
      bool ZSNieFTjji = false;
      bool pWAZLbjxMH = false;
      bool uGliCuQZBx = false;
      bool qummIbudZh = false;
      bool CMkPtWIbna = false;
      bool IZUQTTgdfj = false;
      bool otimquiMQi = false;
      bool gGXeEiVVof = false;
      bool lokanQZVTn = false;
      bool uQxorIdyXy = false;
      string aATQFnblpF;
      string mxApCuVwVq;
      string WasHblxNAL;
      string GnlaDSMmgK;
      string GVeMmYdpPP;
      string EwrocAGMoT;
      string pOkdzzKYmi;
      string ihPLkAwgUC;
      string HGykHJuxxC;
      string MAyMTrkANn;
      string NEDggWfgDb;
      string EZrmLjPAWo;
      string DNajWhiCrs;
      string PuSfnCDRDk;
      string cNsVylILBi;
      string bkcXjAdSJz;
      string mcnKMIGLyI;
      string gywlLoUFlj;
      string ZXBIReRuwn;
      string YjHEyzZhIo;
      if(aATQFnblpF == NEDggWfgDb){fxMrCcnqMt = true;}
      else if(NEDggWfgDb == aATQFnblpF){ZSNieFTjji = true;}
      if(mxApCuVwVq == EZrmLjPAWo){eXgYYObfsg = true;}
      else if(EZrmLjPAWo == mxApCuVwVq){pWAZLbjxMH = true;}
      if(WasHblxNAL == DNajWhiCrs){pLOKjxqqnL = true;}
      else if(DNajWhiCrs == WasHblxNAL){uGliCuQZBx = true;}
      if(GnlaDSMmgK == PuSfnCDRDk){PlwwEbKJFn = true;}
      else if(PuSfnCDRDk == GnlaDSMmgK){qummIbudZh = true;}
      if(GVeMmYdpPP == cNsVylILBi){pahCIBChei = true;}
      else if(cNsVylILBi == GVeMmYdpPP){CMkPtWIbna = true;}
      if(EwrocAGMoT == bkcXjAdSJz){XsobyThCIF = true;}
      else if(bkcXjAdSJz == EwrocAGMoT){IZUQTTgdfj = true;}
      if(pOkdzzKYmi == mcnKMIGLyI){kwCAdsajUw = true;}
      else if(mcnKMIGLyI == pOkdzzKYmi){otimquiMQi = true;}
      if(ihPLkAwgUC == gywlLoUFlj){DRZEqPcLCh = true;}
      if(HGykHJuxxC == ZXBIReRuwn){tIMEnVxUyk = true;}
      if(MAyMTrkANn == YjHEyzZhIo){sIBADsXhYO = true;}
      while(gywlLoUFlj == ihPLkAwgUC){gGXeEiVVof = true;}
      while(ZXBIReRuwn == ZXBIReRuwn){lokanQZVTn = true;}
      while(YjHEyzZhIo == YjHEyzZhIo){uQxorIdyXy = true;}
      if(fxMrCcnqMt == true){fxMrCcnqMt = false;}
      if(eXgYYObfsg == true){eXgYYObfsg = false;}
      if(pLOKjxqqnL == true){pLOKjxqqnL = false;}
      if(PlwwEbKJFn == true){PlwwEbKJFn = false;}
      if(pahCIBChei == true){pahCIBChei = false;}
      if(XsobyThCIF == true){XsobyThCIF = false;}
      if(kwCAdsajUw == true){kwCAdsajUw = false;}
      if(DRZEqPcLCh == true){DRZEqPcLCh = false;}
      if(tIMEnVxUyk == true){tIMEnVxUyk = false;}
      if(sIBADsXhYO == true){sIBADsXhYO = false;}
      if(ZSNieFTjji == true){ZSNieFTjji = false;}
      if(pWAZLbjxMH == true){pWAZLbjxMH = false;}
      if(uGliCuQZBx == true){uGliCuQZBx = false;}
      if(qummIbudZh == true){qummIbudZh = false;}
      if(CMkPtWIbna == true){CMkPtWIbna = false;}
      if(IZUQTTgdfj == true){IZUQTTgdfj = false;}
      if(otimquiMQi == true){otimquiMQi = false;}
      if(gGXeEiVVof == true){gGXeEiVVof = false;}
      if(lokanQZVTn == true){lokanQZVTn = false;}
      if(uQxorIdyXy == true){uQxorIdyXy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNNKDGVWDF
{ 
  void QiiwdzbBet()
  { 
      bool xbPnlCZYSt = false;
      bool sNjyZTDhVL = false;
      bool zzZHbstPAJ = false;
      bool WxCPrIVxZd = false;
      bool dLgpKTgwzm = false;
      bool LjYQGyCHMr = false;
      bool IKXIWuKTFR = false;
      bool xFIqhnRiwI = false;
      bool MxPNylXlJt = false;
      bool FOkhVTnXSP = false;
      bool IMqhpGbhhR = false;
      bool fSKEfKtKKk = false;
      bool WXKKLhTaVN = false;
      bool AsQgzzGhWq = false;
      bool KpDqOlEgBK = false;
      bool YdMhrkCfVH = false;
      bool lALUQlCcEf = false;
      bool EMmSZgTSwY = false;
      bool cmYKoWginO = false;
      bool xaMOFJdiZb = false;
      string mdzfpblenW;
      string WBYLIpoYie;
      string lTfNLNGGnn;
      string RDkVJkCyIx;
      string seBWGrUTyV;
      string JonMqSykUb;
      string UeqzESPDCX;
      string mqQkkHSIHS;
      string rmIRecPYdp;
      string lQdgcNmBSm;
      string cRQZhSYCaj;
      string AodCigWYUb;
      string DqYLlWMiHX;
      string TQpTpZWhjM;
      string DNyspwlbxw;
      string qOgpjlsFnK;
      string FotCQjzJMI;
      string KnnIXpreVo;
      string kklLgEjzjE;
      string gQtYHOSucF;
      if(mdzfpblenW == cRQZhSYCaj){xbPnlCZYSt = true;}
      else if(cRQZhSYCaj == mdzfpblenW){IMqhpGbhhR = true;}
      if(WBYLIpoYie == AodCigWYUb){sNjyZTDhVL = true;}
      else if(AodCigWYUb == WBYLIpoYie){fSKEfKtKKk = true;}
      if(lTfNLNGGnn == DqYLlWMiHX){zzZHbstPAJ = true;}
      else if(DqYLlWMiHX == lTfNLNGGnn){WXKKLhTaVN = true;}
      if(RDkVJkCyIx == TQpTpZWhjM){WxCPrIVxZd = true;}
      else if(TQpTpZWhjM == RDkVJkCyIx){AsQgzzGhWq = true;}
      if(seBWGrUTyV == DNyspwlbxw){dLgpKTgwzm = true;}
      else if(DNyspwlbxw == seBWGrUTyV){KpDqOlEgBK = true;}
      if(JonMqSykUb == qOgpjlsFnK){LjYQGyCHMr = true;}
      else if(qOgpjlsFnK == JonMqSykUb){YdMhrkCfVH = true;}
      if(UeqzESPDCX == FotCQjzJMI){IKXIWuKTFR = true;}
      else if(FotCQjzJMI == UeqzESPDCX){lALUQlCcEf = true;}
      if(mqQkkHSIHS == KnnIXpreVo){xFIqhnRiwI = true;}
      if(rmIRecPYdp == kklLgEjzjE){MxPNylXlJt = true;}
      if(lQdgcNmBSm == gQtYHOSucF){FOkhVTnXSP = true;}
      while(KnnIXpreVo == mqQkkHSIHS){EMmSZgTSwY = true;}
      while(kklLgEjzjE == kklLgEjzjE){cmYKoWginO = true;}
      while(gQtYHOSucF == gQtYHOSucF){xaMOFJdiZb = true;}
      if(xbPnlCZYSt == true){xbPnlCZYSt = false;}
      if(sNjyZTDhVL == true){sNjyZTDhVL = false;}
      if(zzZHbstPAJ == true){zzZHbstPAJ = false;}
      if(WxCPrIVxZd == true){WxCPrIVxZd = false;}
      if(dLgpKTgwzm == true){dLgpKTgwzm = false;}
      if(LjYQGyCHMr == true){LjYQGyCHMr = false;}
      if(IKXIWuKTFR == true){IKXIWuKTFR = false;}
      if(xFIqhnRiwI == true){xFIqhnRiwI = false;}
      if(MxPNylXlJt == true){MxPNylXlJt = false;}
      if(FOkhVTnXSP == true){FOkhVTnXSP = false;}
      if(IMqhpGbhhR == true){IMqhpGbhhR = false;}
      if(fSKEfKtKKk == true){fSKEfKtKKk = false;}
      if(WXKKLhTaVN == true){WXKKLhTaVN = false;}
      if(AsQgzzGhWq == true){AsQgzzGhWq = false;}
      if(KpDqOlEgBK == true){KpDqOlEgBK = false;}
      if(YdMhrkCfVH == true){YdMhrkCfVH = false;}
      if(lALUQlCcEf == true){lALUQlCcEf = false;}
      if(EMmSZgTSwY == true){EMmSZgTSwY = false;}
      if(cmYKoWginO == true){cmYKoWginO = false;}
      if(xaMOFJdiZb == true){xaMOFJdiZb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HICADSCYQN
{ 
  void aVSpqexPXq()
  { 
      bool uLTtOBjkei = false;
      bool LbIbPhWAez = false;
      bool fwyAAXHirT = false;
      bool lkSMxkTeIE = false;
      bool wYGgeAZRJi = false;
      bool tOQaCyNTtp = false;
      bool sBrKxZJwde = false;
      bool OqraDHoRUA = false;
      bool ypYJYWUqKz = false;
      bool XAjSKtfwiF = false;
      bool pdmdTDWpXt = false;
      bool IuztrDbika = false;
      bool ERleHOHZPI = false;
      bool ashOJTDtoV = false;
      bool zeTPpbApZG = false;
      bool SxLIAYrHWF = false;
      bool uxZOTPNjjX = false;
      bool AgsOaZxVof = false;
      bool NQzJpchZOk = false;
      bool buXjZCFFua = false;
      string wsupDaBgXH;
      string jesECtjtfO;
      string SApCcFWfQP;
      string AlsfPRhzxV;
      string mFBXZojLbu;
      string GqdUTuCrNx;
      string EUQHHykNnk;
      string LjxKaNzRcm;
      string VKEVJIHYMU;
      string OokzQSnsPb;
      string EWXqiVtSsF;
      string wkPZbtPuyz;
      string pLATVVzxtI;
      string ZFCBiymNln;
      string NoeGYdZKXV;
      string DsuQkrVDUM;
      string WwYjfphOqc;
      string HBIJkBfstr;
      string wnZXFfKlPq;
      string cisZRRPuah;
      if(wsupDaBgXH == EWXqiVtSsF){uLTtOBjkei = true;}
      else if(EWXqiVtSsF == wsupDaBgXH){pdmdTDWpXt = true;}
      if(jesECtjtfO == wkPZbtPuyz){LbIbPhWAez = true;}
      else if(wkPZbtPuyz == jesECtjtfO){IuztrDbika = true;}
      if(SApCcFWfQP == pLATVVzxtI){fwyAAXHirT = true;}
      else if(pLATVVzxtI == SApCcFWfQP){ERleHOHZPI = true;}
      if(AlsfPRhzxV == ZFCBiymNln){lkSMxkTeIE = true;}
      else if(ZFCBiymNln == AlsfPRhzxV){ashOJTDtoV = true;}
      if(mFBXZojLbu == NoeGYdZKXV){wYGgeAZRJi = true;}
      else if(NoeGYdZKXV == mFBXZojLbu){zeTPpbApZG = true;}
      if(GqdUTuCrNx == DsuQkrVDUM){tOQaCyNTtp = true;}
      else if(DsuQkrVDUM == GqdUTuCrNx){SxLIAYrHWF = true;}
      if(EUQHHykNnk == WwYjfphOqc){sBrKxZJwde = true;}
      else if(WwYjfphOqc == EUQHHykNnk){uxZOTPNjjX = true;}
      if(LjxKaNzRcm == HBIJkBfstr){OqraDHoRUA = true;}
      if(VKEVJIHYMU == wnZXFfKlPq){ypYJYWUqKz = true;}
      if(OokzQSnsPb == cisZRRPuah){XAjSKtfwiF = true;}
      while(HBIJkBfstr == LjxKaNzRcm){AgsOaZxVof = true;}
      while(wnZXFfKlPq == wnZXFfKlPq){NQzJpchZOk = true;}
      while(cisZRRPuah == cisZRRPuah){buXjZCFFua = true;}
      if(uLTtOBjkei == true){uLTtOBjkei = false;}
      if(LbIbPhWAez == true){LbIbPhWAez = false;}
      if(fwyAAXHirT == true){fwyAAXHirT = false;}
      if(lkSMxkTeIE == true){lkSMxkTeIE = false;}
      if(wYGgeAZRJi == true){wYGgeAZRJi = false;}
      if(tOQaCyNTtp == true){tOQaCyNTtp = false;}
      if(sBrKxZJwde == true){sBrKxZJwde = false;}
      if(OqraDHoRUA == true){OqraDHoRUA = false;}
      if(ypYJYWUqKz == true){ypYJYWUqKz = false;}
      if(XAjSKtfwiF == true){XAjSKtfwiF = false;}
      if(pdmdTDWpXt == true){pdmdTDWpXt = false;}
      if(IuztrDbika == true){IuztrDbika = false;}
      if(ERleHOHZPI == true){ERleHOHZPI = false;}
      if(ashOJTDtoV == true){ashOJTDtoV = false;}
      if(zeTPpbApZG == true){zeTPpbApZG = false;}
      if(SxLIAYrHWF == true){SxLIAYrHWF = false;}
      if(uxZOTPNjjX == true){uxZOTPNjjX = false;}
      if(AgsOaZxVof == true){AgsOaZxVof = false;}
      if(NQzJpchZOk == true){NQzJpchZOk = false;}
      if(buXjZCFFua == true){buXjZCFFua = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZADJDKWGDB
{ 
  void wSPTespjeC()
  { 
      bool EFeQGXyZZm = false;
      bool duTALbfNZV = false;
      bool gabfInXDhc = false;
      bool LaBaDAyuoD = false;
      bool QSFszwtpif = false;
      bool fQKGJddyIR = false;
      bool AtrwbCtsxL = false;
      bool cjYWFOUigM = false;
      bool shUBxuQtQZ = false;
      bool WzmXCVZJRw = false;
      bool BBrWDwrmBu = false;
      bool ItRuXRZpzf = false;
      bool kzbWocxATi = false;
      bool nLQkKroxyA = false;
      bool CdsVRbhqzj = false;
      bool wjKkKCYVgZ = false;
      bool zqTRGwcgkf = false;
      bool cbqycHFGFN = false;
      bool uFBilEBfZH = false;
      bool STPXBLKaOU = false;
      string xmydbJWFhT;
      string WeRAtamdKH;
      string okhLskggrt;
      string AmfVNQVCVq;
      string qVHcrlIIFq;
      string IbieOMFmjq;
      string cpMnSiyuld;
      string EjHTPTcETG;
      string bXbAkYEBGB;
      string KiReOBITJI;
      string mMWbmXUPPu;
      string iATcOEOLDt;
      string exojSUSbFN;
      string KJtKTOBzNN;
      string EnkLRKOnPJ;
      string mwPPdpXlIR;
      string FrJBjZFJJz;
      string DOypppLcSI;
      string FdLuaOsegc;
      string qOpuHMejbq;
      if(xmydbJWFhT == mMWbmXUPPu){EFeQGXyZZm = true;}
      else if(mMWbmXUPPu == xmydbJWFhT){BBrWDwrmBu = true;}
      if(WeRAtamdKH == iATcOEOLDt){duTALbfNZV = true;}
      else if(iATcOEOLDt == WeRAtamdKH){ItRuXRZpzf = true;}
      if(okhLskggrt == exojSUSbFN){gabfInXDhc = true;}
      else if(exojSUSbFN == okhLskggrt){kzbWocxATi = true;}
      if(AmfVNQVCVq == KJtKTOBzNN){LaBaDAyuoD = true;}
      else if(KJtKTOBzNN == AmfVNQVCVq){nLQkKroxyA = true;}
      if(qVHcrlIIFq == EnkLRKOnPJ){QSFszwtpif = true;}
      else if(EnkLRKOnPJ == qVHcrlIIFq){CdsVRbhqzj = true;}
      if(IbieOMFmjq == mwPPdpXlIR){fQKGJddyIR = true;}
      else if(mwPPdpXlIR == IbieOMFmjq){wjKkKCYVgZ = true;}
      if(cpMnSiyuld == FrJBjZFJJz){AtrwbCtsxL = true;}
      else if(FrJBjZFJJz == cpMnSiyuld){zqTRGwcgkf = true;}
      if(EjHTPTcETG == DOypppLcSI){cjYWFOUigM = true;}
      if(bXbAkYEBGB == FdLuaOsegc){shUBxuQtQZ = true;}
      if(KiReOBITJI == qOpuHMejbq){WzmXCVZJRw = true;}
      while(DOypppLcSI == EjHTPTcETG){cbqycHFGFN = true;}
      while(FdLuaOsegc == FdLuaOsegc){uFBilEBfZH = true;}
      while(qOpuHMejbq == qOpuHMejbq){STPXBLKaOU = true;}
      if(EFeQGXyZZm == true){EFeQGXyZZm = false;}
      if(duTALbfNZV == true){duTALbfNZV = false;}
      if(gabfInXDhc == true){gabfInXDhc = false;}
      if(LaBaDAyuoD == true){LaBaDAyuoD = false;}
      if(QSFszwtpif == true){QSFszwtpif = false;}
      if(fQKGJddyIR == true){fQKGJddyIR = false;}
      if(AtrwbCtsxL == true){AtrwbCtsxL = false;}
      if(cjYWFOUigM == true){cjYWFOUigM = false;}
      if(shUBxuQtQZ == true){shUBxuQtQZ = false;}
      if(WzmXCVZJRw == true){WzmXCVZJRw = false;}
      if(BBrWDwrmBu == true){BBrWDwrmBu = false;}
      if(ItRuXRZpzf == true){ItRuXRZpzf = false;}
      if(kzbWocxATi == true){kzbWocxATi = false;}
      if(nLQkKroxyA == true){nLQkKroxyA = false;}
      if(CdsVRbhqzj == true){CdsVRbhqzj = false;}
      if(wjKkKCYVgZ == true){wjKkKCYVgZ = false;}
      if(zqTRGwcgkf == true){zqTRGwcgkf = false;}
      if(cbqycHFGFN == true){cbqycHFGFN = false;}
      if(uFBilEBfZH == true){uFBilEBfZH = false;}
      if(STPXBLKaOU == true){STPXBLKaOU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMXINXHXKE
{ 
  void txpqiRzHlI()
  { 
      bool upxtqZhBOM = false;
      bool XrnlAswxeW = false;
      bool dlLGzwpQnJ = false;
      bool GRgzeSBkgb = false;
      bool bsZDTPbtpl = false;
      bool mNYglIdquu = false;
      bool iQNFFGKnGg = false;
      bool rKQCtkLIli = false;
      bool TwZBVsszNV = false;
      bool oKplrKeUxN = false;
      bool EmmIscxVlB = false;
      bool wUEMampLiM = false;
      bool NLakrhUdJj = false;
      bool FqLXdgIRHs = false;
      bool wWMMYTFdLF = false;
      bool TSkkAsMCPL = false;
      bool ISMCuFJfht = false;
      bool eYEpPqyOLY = false;
      bool bpSEPlGZXk = false;
      bool TGBwkcKKQT = false;
      string GibklfQSeb;
      string VfScYrksFj;
      string dpyhMMVBdb;
      string CpHktffGSs;
      string ZkNlJYerAu;
      string QiJpXQksYZ;
      string JPoCYfXhir;
      string MdZLJsbLXm;
      string hcAhLTfRNd;
      string ulhsjKuLNd;
      string AxJIimIyfd;
      string nYUkrfOGqE;
      string zGTFwZugby;
      string yPxtlkTrzX;
      string LhkioVQwBD;
      string woUIdscELI;
      string rbVgfYaazH;
      string LWHSsRVjPZ;
      string IyeYCJtoPr;
      string HPfpejLDDP;
      if(GibklfQSeb == AxJIimIyfd){upxtqZhBOM = true;}
      else if(AxJIimIyfd == GibklfQSeb){EmmIscxVlB = true;}
      if(VfScYrksFj == nYUkrfOGqE){XrnlAswxeW = true;}
      else if(nYUkrfOGqE == VfScYrksFj){wUEMampLiM = true;}
      if(dpyhMMVBdb == zGTFwZugby){dlLGzwpQnJ = true;}
      else if(zGTFwZugby == dpyhMMVBdb){NLakrhUdJj = true;}
      if(CpHktffGSs == yPxtlkTrzX){GRgzeSBkgb = true;}
      else if(yPxtlkTrzX == CpHktffGSs){FqLXdgIRHs = true;}
      if(ZkNlJYerAu == LhkioVQwBD){bsZDTPbtpl = true;}
      else if(LhkioVQwBD == ZkNlJYerAu){wWMMYTFdLF = true;}
      if(QiJpXQksYZ == woUIdscELI){mNYglIdquu = true;}
      else if(woUIdscELI == QiJpXQksYZ){TSkkAsMCPL = true;}
      if(JPoCYfXhir == rbVgfYaazH){iQNFFGKnGg = true;}
      else if(rbVgfYaazH == JPoCYfXhir){ISMCuFJfht = true;}
      if(MdZLJsbLXm == LWHSsRVjPZ){rKQCtkLIli = true;}
      if(hcAhLTfRNd == IyeYCJtoPr){TwZBVsszNV = true;}
      if(ulhsjKuLNd == HPfpejLDDP){oKplrKeUxN = true;}
      while(LWHSsRVjPZ == MdZLJsbLXm){eYEpPqyOLY = true;}
      while(IyeYCJtoPr == IyeYCJtoPr){bpSEPlGZXk = true;}
      while(HPfpejLDDP == HPfpejLDDP){TGBwkcKKQT = true;}
      if(upxtqZhBOM == true){upxtqZhBOM = false;}
      if(XrnlAswxeW == true){XrnlAswxeW = false;}
      if(dlLGzwpQnJ == true){dlLGzwpQnJ = false;}
      if(GRgzeSBkgb == true){GRgzeSBkgb = false;}
      if(bsZDTPbtpl == true){bsZDTPbtpl = false;}
      if(mNYglIdquu == true){mNYglIdquu = false;}
      if(iQNFFGKnGg == true){iQNFFGKnGg = false;}
      if(rKQCtkLIli == true){rKQCtkLIli = false;}
      if(TwZBVsszNV == true){TwZBVsszNV = false;}
      if(oKplrKeUxN == true){oKplrKeUxN = false;}
      if(EmmIscxVlB == true){EmmIscxVlB = false;}
      if(wUEMampLiM == true){wUEMampLiM = false;}
      if(NLakrhUdJj == true){NLakrhUdJj = false;}
      if(FqLXdgIRHs == true){FqLXdgIRHs = false;}
      if(wWMMYTFdLF == true){wWMMYTFdLF = false;}
      if(TSkkAsMCPL == true){TSkkAsMCPL = false;}
      if(ISMCuFJfht == true){ISMCuFJfht = false;}
      if(eYEpPqyOLY == true){eYEpPqyOLY = false;}
      if(bpSEPlGZXk == true){bpSEPlGZXk = false;}
      if(TGBwkcKKQT == true){TGBwkcKKQT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDEZXJLOBT
{ 
  void LOgsQUYkPd()
  { 
      bool faTZVMZdSt = false;
      bool txYiqSfnTG = false;
      bool dbFHZTRRhX = false;
      bool skfWJVOSQB = false;
      bool jRsHaMSLdC = false;
      bool qAIQTEVLAB = false;
      bool uIwtBJRCZU = false;
      bool EMXRVMhxgM = false;
      bool BFnfgrbPDF = false;
      bool zCSOGbUzGQ = false;
      bool uQlIxdcqtH = false;
      bool VYemAoTPMI = false;
      bool hBzTUBtJLs = false;
      bool qhpPRjSehD = false;
      bool OkUwiaWeOQ = false;
      bool HFmxisRRmu = false;
      bool jTfBPmhPUP = false;
      bool VnhJtwgCkt = false;
      bool eOttklurfY = false;
      bool SBrlSuFTfu = false;
      string SCfELCaSIh;
      string OFUmYKIPDx;
      string NbHooNekub;
      string OFBASeKUED;
      string zgoZjhKGeS;
      string VnuUWqupPy;
      string WoXfSIDTUt;
      string zmKAyglgFH;
      string CXGbFaKgcb;
      string iTFGfJIIGa;
      string dqlkTidtWo;
      string EOkHuyiuZr;
      string yWprKegETo;
      string XdZdcLlVIW;
      string wPJnXUhyKh;
      string ZNhNbHAsZn;
      string BZahQZnHdj;
      string MNmDuhMCUp;
      string xislOKwLBV;
      string KruUUWobWx;
      if(SCfELCaSIh == dqlkTidtWo){faTZVMZdSt = true;}
      else if(dqlkTidtWo == SCfELCaSIh){uQlIxdcqtH = true;}
      if(OFUmYKIPDx == EOkHuyiuZr){txYiqSfnTG = true;}
      else if(EOkHuyiuZr == OFUmYKIPDx){VYemAoTPMI = true;}
      if(NbHooNekub == yWprKegETo){dbFHZTRRhX = true;}
      else if(yWprKegETo == NbHooNekub){hBzTUBtJLs = true;}
      if(OFBASeKUED == XdZdcLlVIW){skfWJVOSQB = true;}
      else if(XdZdcLlVIW == OFBASeKUED){qhpPRjSehD = true;}
      if(zgoZjhKGeS == wPJnXUhyKh){jRsHaMSLdC = true;}
      else if(wPJnXUhyKh == zgoZjhKGeS){OkUwiaWeOQ = true;}
      if(VnuUWqupPy == ZNhNbHAsZn){qAIQTEVLAB = true;}
      else if(ZNhNbHAsZn == VnuUWqupPy){HFmxisRRmu = true;}
      if(WoXfSIDTUt == BZahQZnHdj){uIwtBJRCZU = true;}
      else if(BZahQZnHdj == WoXfSIDTUt){jTfBPmhPUP = true;}
      if(zmKAyglgFH == MNmDuhMCUp){EMXRVMhxgM = true;}
      if(CXGbFaKgcb == xislOKwLBV){BFnfgrbPDF = true;}
      if(iTFGfJIIGa == KruUUWobWx){zCSOGbUzGQ = true;}
      while(MNmDuhMCUp == zmKAyglgFH){VnhJtwgCkt = true;}
      while(xislOKwLBV == xislOKwLBV){eOttklurfY = true;}
      while(KruUUWobWx == KruUUWobWx){SBrlSuFTfu = true;}
      if(faTZVMZdSt == true){faTZVMZdSt = false;}
      if(txYiqSfnTG == true){txYiqSfnTG = false;}
      if(dbFHZTRRhX == true){dbFHZTRRhX = false;}
      if(skfWJVOSQB == true){skfWJVOSQB = false;}
      if(jRsHaMSLdC == true){jRsHaMSLdC = false;}
      if(qAIQTEVLAB == true){qAIQTEVLAB = false;}
      if(uIwtBJRCZU == true){uIwtBJRCZU = false;}
      if(EMXRVMhxgM == true){EMXRVMhxgM = false;}
      if(BFnfgrbPDF == true){BFnfgrbPDF = false;}
      if(zCSOGbUzGQ == true){zCSOGbUzGQ = false;}
      if(uQlIxdcqtH == true){uQlIxdcqtH = false;}
      if(VYemAoTPMI == true){VYemAoTPMI = false;}
      if(hBzTUBtJLs == true){hBzTUBtJLs = false;}
      if(qhpPRjSehD == true){qhpPRjSehD = false;}
      if(OkUwiaWeOQ == true){OkUwiaWeOQ = false;}
      if(HFmxisRRmu == true){HFmxisRRmu = false;}
      if(jTfBPmhPUP == true){jTfBPmhPUP = false;}
      if(VnhJtwgCkt == true){VnhJtwgCkt = false;}
      if(eOttklurfY == true){eOttklurfY = false;}
      if(SBrlSuFTfu == true){SBrlSuFTfu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMKLYGVIEK
{ 
  void BEeFijgDXU()
  { 
      bool LxThaaABZc = false;
      bool QkwNjCydQB = false;
      bool EaqHiSJhEQ = false;
      bool OyEqUlIgik = false;
      bool TlXbXMZpzC = false;
      bool LDfCzkGLzI = false;
      bool QSxJOSfFsx = false;
      bool tQtehRCOjW = false;
      bool sThBFLRBri = false;
      bool ewhaUAoONE = false;
      bool fTxCItIAUg = false;
      bool hrabOwjuED = false;
      bool AeNJRxhTKg = false;
      bool cmAepYVfrK = false;
      bool CQfKBmUGLX = false;
      bool QsKKDAGnjL = false;
      bool MopnEtqwko = false;
      bool aDDtBjzCId = false;
      bool bbHlPicpap = false;
      bool ShugxMarGG = false;
      string waaPAENeim;
      string yGfHBeAsJX;
      string lDHXkKGrGk;
      string ZtiPebbsbQ;
      string VLBKyDrKjC;
      string dJIehrTDeo;
      string xUYyMEXQcY;
      string DHQsBZBwZg;
      string SuIDGPkDhl;
      string IXOlSAmDxs;
      string fbhKzWrOdH;
      string pXcxWCLUrx;
      string SThpQeseaA;
      string lyyfApNxDi;
      string WVZZujtQOP;
      string oRKAZLsqtT;
      string dNncVrYxxg;
      string oNRJZwtItf;
      string jbPKLTmyFo;
      string xVDiEJhwED;
      if(waaPAENeim == fbhKzWrOdH){LxThaaABZc = true;}
      else if(fbhKzWrOdH == waaPAENeim){fTxCItIAUg = true;}
      if(yGfHBeAsJX == pXcxWCLUrx){QkwNjCydQB = true;}
      else if(pXcxWCLUrx == yGfHBeAsJX){hrabOwjuED = true;}
      if(lDHXkKGrGk == SThpQeseaA){EaqHiSJhEQ = true;}
      else if(SThpQeseaA == lDHXkKGrGk){AeNJRxhTKg = true;}
      if(ZtiPebbsbQ == lyyfApNxDi){OyEqUlIgik = true;}
      else if(lyyfApNxDi == ZtiPebbsbQ){cmAepYVfrK = true;}
      if(VLBKyDrKjC == WVZZujtQOP){TlXbXMZpzC = true;}
      else if(WVZZujtQOP == VLBKyDrKjC){CQfKBmUGLX = true;}
      if(dJIehrTDeo == oRKAZLsqtT){LDfCzkGLzI = true;}
      else if(oRKAZLsqtT == dJIehrTDeo){QsKKDAGnjL = true;}
      if(xUYyMEXQcY == dNncVrYxxg){QSxJOSfFsx = true;}
      else if(dNncVrYxxg == xUYyMEXQcY){MopnEtqwko = true;}
      if(DHQsBZBwZg == oNRJZwtItf){tQtehRCOjW = true;}
      if(SuIDGPkDhl == jbPKLTmyFo){sThBFLRBri = true;}
      if(IXOlSAmDxs == xVDiEJhwED){ewhaUAoONE = true;}
      while(oNRJZwtItf == DHQsBZBwZg){aDDtBjzCId = true;}
      while(jbPKLTmyFo == jbPKLTmyFo){bbHlPicpap = true;}
      while(xVDiEJhwED == xVDiEJhwED){ShugxMarGG = true;}
      if(LxThaaABZc == true){LxThaaABZc = false;}
      if(QkwNjCydQB == true){QkwNjCydQB = false;}
      if(EaqHiSJhEQ == true){EaqHiSJhEQ = false;}
      if(OyEqUlIgik == true){OyEqUlIgik = false;}
      if(TlXbXMZpzC == true){TlXbXMZpzC = false;}
      if(LDfCzkGLzI == true){LDfCzkGLzI = false;}
      if(QSxJOSfFsx == true){QSxJOSfFsx = false;}
      if(tQtehRCOjW == true){tQtehRCOjW = false;}
      if(sThBFLRBri == true){sThBFLRBri = false;}
      if(ewhaUAoONE == true){ewhaUAoONE = false;}
      if(fTxCItIAUg == true){fTxCItIAUg = false;}
      if(hrabOwjuED == true){hrabOwjuED = false;}
      if(AeNJRxhTKg == true){AeNJRxhTKg = false;}
      if(cmAepYVfrK == true){cmAepYVfrK = false;}
      if(CQfKBmUGLX == true){CQfKBmUGLX = false;}
      if(QsKKDAGnjL == true){QsKKDAGnjL = false;}
      if(MopnEtqwko == true){MopnEtqwko = false;}
      if(aDDtBjzCId == true){aDDtBjzCId = false;}
      if(bbHlPicpap == true){bbHlPicpap = false;}
      if(ShugxMarGG == true){ShugxMarGG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KASBVOAYNX
{ 
  void JRSVkIrMuE()
  { 
      bool KjgIMnFnrr = false;
      bool LKsXYkUTYH = false;
      bool zFrotLgYZT = false;
      bool zVGIEpOfuz = false;
      bool cqndMkbNCy = false;
      bool dywDiFrqOB = false;
      bool GgOYsoDkSh = false;
      bool WnYZdHQOcJ = false;
      bool jTWaoBZDYz = false;
      bool yXRtrwbPjX = false;
      bool gquTaoZWYa = false;
      bool ndNERmKmir = false;
      bool PALTizWegh = false;
      bool eBdFcrYCzA = false;
      bool bCdyKUJMcE = false;
      bool knfrHfebkb = false;
      bool StoqumAIbY = false;
      bool OImiQMWMIO = false;
      bool pKBbwpUkxw = false;
      bool MxQXggNlDW = false;
      string DNIxqleWAo;
      string eIgKYMJqAJ;
      string apDKAMFNwl;
      string FrqgjkrgqN;
      string PGmWIttNnu;
      string yyRBAMKxwe;
      string fQaNilQAZn;
      string UbAlsUDfCF;
      string RrZBnHZpgW;
      string atkLhyeYnV;
      string dtmAZWyfHf;
      string JdupMmqZZb;
      string LZSDMZpnDt;
      string odrfbWFYaQ;
      string IthBNwzuyu;
      string GFyLJDbimz;
      string gJbMqelOOp;
      string hSzJSRrQpP;
      string auoInifgWY;
      string uVkajzRVKh;
      if(DNIxqleWAo == dtmAZWyfHf){KjgIMnFnrr = true;}
      else if(dtmAZWyfHf == DNIxqleWAo){gquTaoZWYa = true;}
      if(eIgKYMJqAJ == JdupMmqZZb){LKsXYkUTYH = true;}
      else if(JdupMmqZZb == eIgKYMJqAJ){ndNERmKmir = true;}
      if(apDKAMFNwl == LZSDMZpnDt){zFrotLgYZT = true;}
      else if(LZSDMZpnDt == apDKAMFNwl){PALTizWegh = true;}
      if(FrqgjkrgqN == odrfbWFYaQ){zVGIEpOfuz = true;}
      else if(odrfbWFYaQ == FrqgjkrgqN){eBdFcrYCzA = true;}
      if(PGmWIttNnu == IthBNwzuyu){cqndMkbNCy = true;}
      else if(IthBNwzuyu == PGmWIttNnu){bCdyKUJMcE = true;}
      if(yyRBAMKxwe == GFyLJDbimz){dywDiFrqOB = true;}
      else if(GFyLJDbimz == yyRBAMKxwe){knfrHfebkb = true;}
      if(fQaNilQAZn == gJbMqelOOp){GgOYsoDkSh = true;}
      else if(gJbMqelOOp == fQaNilQAZn){StoqumAIbY = true;}
      if(UbAlsUDfCF == hSzJSRrQpP){WnYZdHQOcJ = true;}
      if(RrZBnHZpgW == auoInifgWY){jTWaoBZDYz = true;}
      if(atkLhyeYnV == uVkajzRVKh){yXRtrwbPjX = true;}
      while(hSzJSRrQpP == UbAlsUDfCF){OImiQMWMIO = true;}
      while(auoInifgWY == auoInifgWY){pKBbwpUkxw = true;}
      while(uVkajzRVKh == uVkajzRVKh){MxQXggNlDW = true;}
      if(KjgIMnFnrr == true){KjgIMnFnrr = false;}
      if(LKsXYkUTYH == true){LKsXYkUTYH = false;}
      if(zFrotLgYZT == true){zFrotLgYZT = false;}
      if(zVGIEpOfuz == true){zVGIEpOfuz = false;}
      if(cqndMkbNCy == true){cqndMkbNCy = false;}
      if(dywDiFrqOB == true){dywDiFrqOB = false;}
      if(GgOYsoDkSh == true){GgOYsoDkSh = false;}
      if(WnYZdHQOcJ == true){WnYZdHQOcJ = false;}
      if(jTWaoBZDYz == true){jTWaoBZDYz = false;}
      if(yXRtrwbPjX == true){yXRtrwbPjX = false;}
      if(gquTaoZWYa == true){gquTaoZWYa = false;}
      if(ndNERmKmir == true){ndNERmKmir = false;}
      if(PALTizWegh == true){PALTizWegh = false;}
      if(eBdFcrYCzA == true){eBdFcrYCzA = false;}
      if(bCdyKUJMcE == true){bCdyKUJMcE = false;}
      if(knfrHfebkb == true){knfrHfebkb = false;}
      if(StoqumAIbY == true){StoqumAIbY = false;}
      if(OImiQMWMIO == true){OImiQMWMIO = false;}
      if(pKBbwpUkxw == true){pKBbwpUkxw = false;}
      if(MxQXggNlDW == true){MxQXggNlDW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHHVBFQLMO
{ 
  void KUWHBrfTQn()
  { 
      bool ujrNaVSBAt = false;
      bool UONKSwtyHY = false;
      bool MTVZTVdgCg = false;
      bool zuEhuOzAwb = false;
      bool cOhfIehAny = false;
      bool LeSZebNSsF = false;
      bool qlySuZJePE = false;
      bool wtCfuykoRn = false;
      bool mdrEUTbeDT = false;
      bool BgGqjpQOkh = false;
      bool UCkjBRcmdg = false;
      bool pXAERNtsxa = false;
      bool xebuCPmKuF = false;
      bool gWEiTjsHCD = false;
      bool qoAWccfBYW = false;
      bool wWQJkpaogk = false;
      bool dRrYzSTQkg = false;
      bool UlptjHeFSZ = false;
      bool jlkXIKFuyc = false;
      bool JDaRYYxaWK = false;
      string AtGAsMESqZ;
      string tqFyGeTjOw;
      string iQOMLLyyez;
      string KfpotzWJmG;
      string VJWENwGjuG;
      string mwtqxjftnh;
      string NFmrPNBPDG;
      string IKwHaZsJyP;
      string FOCYLNkyqK;
      string ScVFrPVeoz;
      string tqfoyczlQX;
      string pWuYczDOfB;
      string bDXsmfnqPK;
      string DOUyUNhNZi;
      string OzgTTwgwcr;
      string MHymXqSlBS;
      string nIVGUbBxDO;
      string RpnxmcVEYp;
      string zrNXywPhad;
      string tuLHtFcazq;
      if(AtGAsMESqZ == tqfoyczlQX){ujrNaVSBAt = true;}
      else if(tqfoyczlQX == AtGAsMESqZ){UCkjBRcmdg = true;}
      if(tqFyGeTjOw == pWuYczDOfB){UONKSwtyHY = true;}
      else if(pWuYczDOfB == tqFyGeTjOw){pXAERNtsxa = true;}
      if(iQOMLLyyez == bDXsmfnqPK){MTVZTVdgCg = true;}
      else if(bDXsmfnqPK == iQOMLLyyez){xebuCPmKuF = true;}
      if(KfpotzWJmG == DOUyUNhNZi){zuEhuOzAwb = true;}
      else if(DOUyUNhNZi == KfpotzWJmG){gWEiTjsHCD = true;}
      if(VJWENwGjuG == OzgTTwgwcr){cOhfIehAny = true;}
      else if(OzgTTwgwcr == VJWENwGjuG){qoAWccfBYW = true;}
      if(mwtqxjftnh == MHymXqSlBS){LeSZebNSsF = true;}
      else if(MHymXqSlBS == mwtqxjftnh){wWQJkpaogk = true;}
      if(NFmrPNBPDG == nIVGUbBxDO){qlySuZJePE = true;}
      else if(nIVGUbBxDO == NFmrPNBPDG){dRrYzSTQkg = true;}
      if(IKwHaZsJyP == RpnxmcVEYp){wtCfuykoRn = true;}
      if(FOCYLNkyqK == zrNXywPhad){mdrEUTbeDT = true;}
      if(ScVFrPVeoz == tuLHtFcazq){BgGqjpQOkh = true;}
      while(RpnxmcVEYp == IKwHaZsJyP){UlptjHeFSZ = true;}
      while(zrNXywPhad == zrNXywPhad){jlkXIKFuyc = true;}
      while(tuLHtFcazq == tuLHtFcazq){JDaRYYxaWK = true;}
      if(ujrNaVSBAt == true){ujrNaVSBAt = false;}
      if(UONKSwtyHY == true){UONKSwtyHY = false;}
      if(MTVZTVdgCg == true){MTVZTVdgCg = false;}
      if(zuEhuOzAwb == true){zuEhuOzAwb = false;}
      if(cOhfIehAny == true){cOhfIehAny = false;}
      if(LeSZebNSsF == true){LeSZebNSsF = false;}
      if(qlySuZJePE == true){qlySuZJePE = false;}
      if(wtCfuykoRn == true){wtCfuykoRn = false;}
      if(mdrEUTbeDT == true){mdrEUTbeDT = false;}
      if(BgGqjpQOkh == true){BgGqjpQOkh = false;}
      if(UCkjBRcmdg == true){UCkjBRcmdg = false;}
      if(pXAERNtsxa == true){pXAERNtsxa = false;}
      if(xebuCPmKuF == true){xebuCPmKuF = false;}
      if(gWEiTjsHCD == true){gWEiTjsHCD = false;}
      if(qoAWccfBYW == true){qoAWccfBYW = false;}
      if(wWQJkpaogk == true){wWQJkpaogk = false;}
      if(dRrYzSTQkg == true){dRrYzSTQkg = false;}
      if(UlptjHeFSZ == true){UlptjHeFSZ = false;}
      if(jlkXIKFuyc == true){jlkXIKFuyc = false;}
      if(JDaRYYxaWK == true){JDaRYYxaWK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWRMFLVUYJ
{ 
  void FrnsXrCcha()
  { 
      bool lEEGfdYJQZ = false;
      bool xTRABJTtng = false;
      bool IZJUILgHca = false;
      bool LCsBtAgQZc = false;
      bool nZRhxXkHxZ = false;
      bool JmoDVLujxT = false;
      bool wQgoNuaPFA = false;
      bool bDULrhIaWk = false;
      bool aZKCQYMpei = false;
      bool FxSGfWsbTB = false;
      bool wVBxxGRdKn = false;
      bool CTMMsWGdXo = false;
      bool ikjWtejOeV = false;
      bool ngHUnFYNEK = false;
      bool GieqfljGMJ = false;
      bool PPDeSLkeCS = false;
      bool VDynzVLrXn = false;
      bool xsYNhzFrpI = false;
      bool udBVGYccBb = false;
      bool TtKloCjprJ = false;
      string RhmqNzTTdH;
      string JuLHITcOrz;
      string fCRZsZeqQE;
      string oysmiYcJlf;
      string ZukPEkdasa;
      string VyOwXOPNym;
      string UbCYRKCXYj;
      string qScMYkQCUI;
      string wDyohqjwPU;
      string IOLyLyrMxt;
      string iFCIiDVBWl;
      string xNrpqQdMqa;
      string aFHDbbHdBa;
      string rEEaYpBoFe;
      string VhZdWtWVHu;
      string TfUWSdyygH;
      string uqAwsrIRQA;
      string OoGLFsfdgg;
      string FlWGHMjhHu;
      string rCHyidgdje;
      if(RhmqNzTTdH == iFCIiDVBWl){lEEGfdYJQZ = true;}
      else if(iFCIiDVBWl == RhmqNzTTdH){wVBxxGRdKn = true;}
      if(JuLHITcOrz == xNrpqQdMqa){xTRABJTtng = true;}
      else if(xNrpqQdMqa == JuLHITcOrz){CTMMsWGdXo = true;}
      if(fCRZsZeqQE == aFHDbbHdBa){IZJUILgHca = true;}
      else if(aFHDbbHdBa == fCRZsZeqQE){ikjWtejOeV = true;}
      if(oysmiYcJlf == rEEaYpBoFe){LCsBtAgQZc = true;}
      else if(rEEaYpBoFe == oysmiYcJlf){ngHUnFYNEK = true;}
      if(ZukPEkdasa == VhZdWtWVHu){nZRhxXkHxZ = true;}
      else if(VhZdWtWVHu == ZukPEkdasa){GieqfljGMJ = true;}
      if(VyOwXOPNym == TfUWSdyygH){JmoDVLujxT = true;}
      else if(TfUWSdyygH == VyOwXOPNym){PPDeSLkeCS = true;}
      if(UbCYRKCXYj == uqAwsrIRQA){wQgoNuaPFA = true;}
      else if(uqAwsrIRQA == UbCYRKCXYj){VDynzVLrXn = true;}
      if(qScMYkQCUI == OoGLFsfdgg){bDULrhIaWk = true;}
      if(wDyohqjwPU == FlWGHMjhHu){aZKCQYMpei = true;}
      if(IOLyLyrMxt == rCHyidgdje){FxSGfWsbTB = true;}
      while(OoGLFsfdgg == qScMYkQCUI){xsYNhzFrpI = true;}
      while(FlWGHMjhHu == FlWGHMjhHu){udBVGYccBb = true;}
      while(rCHyidgdje == rCHyidgdje){TtKloCjprJ = true;}
      if(lEEGfdYJQZ == true){lEEGfdYJQZ = false;}
      if(xTRABJTtng == true){xTRABJTtng = false;}
      if(IZJUILgHca == true){IZJUILgHca = false;}
      if(LCsBtAgQZc == true){LCsBtAgQZc = false;}
      if(nZRhxXkHxZ == true){nZRhxXkHxZ = false;}
      if(JmoDVLujxT == true){JmoDVLujxT = false;}
      if(wQgoNuaPFA == true){wQgoNuaPFA = false;}
      if(bDULrhIaWk == true){bDULrhIaWk = false;}
      if(aZKCQYMpei == true){aZKCQYMpei = false;}
      if(FxSGfWsbTB == true){FxSGfWsbTB = false;}
      if(wVBxxGRdKn == true){wVBxxGRdKn = false;}
      if(CTMMsWGdXo == true){CTMMsWGdXo = false;}
      if(ikjWtejOeV == true){ikjWtejOeV = false;}
      if(ngHUnFYNEK == true){ngHUnFYNEK = false;}
      if(GieqfljGMJ == true){GieqfljGMJ = false;}
      if(PPDeSLkeCS == true){PPDeSLkeCS = false;}
      if(VDynzVLrXn == true){VDynzVLrXn = false;}
      if(xsYNhzFrpI == true){xsYNhzFrpI = false;}
      if(udBVGYccBb == true){udBVGYccBb = false;}
      if(TtKloCjprJ == true){TtKloCjprJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MIIZOCOIQF
{ 
  void rrVXMxBlDo()
  { 
      bool EDGcqZwbNT = false;
      bool qHNYAdEXUO = false;
      bool VFtAcpJCab = false;
      bool cNDdMaQSRP = false;
      bool qIsNcjSHWF = false;
      bool IzTofzIGzA = false;
      bool PsAlpdEiMZ = false;
      bool NkGFWMLgXr = false;
      bool WBfVSctNyM = false;
      bool RJSQzxIHWy = false;
      bool fiuwrWsNRS = false;
      bool mbiHcONdSM = false;
      bool jqkzHDSoGY = false;
      bool DEJYMnGidu = false;
      bool jfueZpaLmk = false;
      bool jdnJOnywoo = false;
      bool EDHsPiRJuo = false;
      bool HeAXcDwFZR = false;
      bool bGCUoZPAJX = false;
      bool pKtopfXCPp = false;
      string FSNcMZKWZc;
      string yjTBDfTLyb;
      string dUdJewTyAt;
      string TnQmYdMJqQ;
      string qUNNiRKKzI;
      string JNiATknDxP;
      string GMVfIJSgbY;
      string SJUgjIGQZN;
      string lIyrjGFPSm;
      string oILaKezhFY;
      string ydhaozsCPL;
      string eXdjcxOcuC;
      string EDOniJysVF;
      string JXKBPHZXDj;
      string MDzGIReayN;
      string QVmDUuPtqe;
      string BzfKCGMbUU;
      string WpZKoADHfR;
      string dWuIomkHgU;
      string rfgXiNXoEB;
      if(FSNcMZKWZc == ydhaozsCPL){EDGcqZwbNT = true;}
      else if(ydhaozsCPL == FSNcMZKWZc){fiuwrWsNRS = true;}
      if(yjTBDfTLyb == eXdjcxOcuC){qHNYAdEXUO = true;}
      else if(eXdjcxOcuC == yjTBDfTLyb){mbiHcONdSM = true;}
      if(dUdJewTyAt == EDOniJysVF){VFtAcpJCab = true;}
      else if(EDOniJysVF == dUdJewTyAt){jqkzHDSoGY = true;}
      if(TnQmYdMJqQ == JXKBPHZXDj){cNDdMaQSRP = true;}
      else if(JXKBPHZXDj == TnQmYdMJqQ){DEJYMnGidu = true;}
      if(qUNNiRKKzI == MDzGIReayN){qIsNcjSHWF = true;}
      else if(MDzGIReayN == qUNNiRKKzI){jfueZpaLmk = true;}
      if(JNiATknDxP == QVmDUuPtqe){IzTofzIGzA = true;}
      else if(QVmDUuPtqe == JNiATknDxP){jdnJOnywoo = true;}
      if(GMVfIJSgbY == BzfKCGMbUU){PsAlpdEiMZ = true;}
      else if(BzfKCGMbUU == GMVfIJSgbY){EDHsPiRJuo = true;}
      if(SJUgjIGQZN == WpZKoADHfR){NkGFWMLgXr = true;}
      if(lIyrjGFPSm == dWuIomkHgU){WBfVSctNyM = true;}
      if(oILaKezhFY == rfgXiNXoEB){RJSQzxIHWy = true;}
      while(WpZKoADHfR == SJUgjIGQZN){HeAXcDwFZR = true;}
      while(dWuIomkHgU == dWuIomkHgU){bGCUoZPAJX = true;}
      while(rfgXiNXoEB == rfgXiNXoEB){pKtopfXCPp = true;}
      if(EDGcqZwbNT == true){EDGcqZwbNT = false;}
      if(qHNYAdEXUO == true){qHNYAdEXUO = false;}
      if(VFtAcpJCab == true){VFtAcpJCab = false;}
      if(cNDdMaQSRP == true){cNDdMaQSRP = false;}
      if(qIsNcjSHWF == true){qIsNcjSHWF = false;}
      if(IzTofzIGzA == true){IzTofzIGzA = false;}
      if(PsAlpdEiMZ == true){PsAlpdEiMZ = false;}
      if(NkGFWMLgXr == true){NkGFWMLgXr = false;}
      if(WBfVSctNyM == true){WBfVSctNyM = false;}
      if(RJSQzxIHWy == true){RJSQzxIHWy = false;}
      if(fiuwrWsNRS == true){fiuwrWsNRS = false;}
      if(mbiHcONdSM == true){mbiHcONdSM = false;}
      if(jqkzHDSoGY == true){jqkzHDSoGY = false;}
      if(DEJYMnGidu == true){DEJYMnGidu = false;}
      if(jfueZpaLmk == true){jfueZpaLmk = false;}
      if(jdnJOnywoo == true){jdnJOnywoo = false;}
      if(EDHsPiRJuo == true){EDHsPiRJuo = false;}
      if(HeAXcDwFZR == true){HeAXcDwFZR = false;}
      if(bGCUoZPAJX == true){bGCUoZPAJX = false;}
      if(pKtopfXCPp == true){pKtopfXCPp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBTDNRYEKY
{ 
  void WfHgmrywQO()
  { 
      bool GEtHJHYKqA = false;
      bool AAWPuEgffn = false;
      bool YWJIboCDpE = false;
      bool fraAAHmBkr = false;
      bool gZDdOhOSVa = false;
      bool HjPrFitleU = false;
      bool EUUlTHYVPn = false;
      bool RfumHzTfst = false;
      bool ZigOxwchuQ = false;
      bool NBVPnLERJH = false;
      bool IsDhJbockG = false;
      bool ONrjuVnGoX = false;
      bool eqayZPKfzw = false;
      bool tCWllgfyEV = false;
      bool HAxnBzIkUR = false;
      bool XybkbQREHs = false;
      bool RJcoLMpFyO = false;
      bool poBTQdtlxa = false;
      bool GYLgXwZlJU = false;
      bool OapKEyWIco = false;
      string RUWLQlLpdk;
      string WSBMPFVCBN;
      string DDdpbeOMLj;
      string LiCydNpcGW;
      string jRPkaUuEEa;
      string eNkCeOqfik;
      string XzdsYmPDiC;
      string OswdclmrPH;
      string iJHkEyyATO;
      string WJsUyjmVMm;
      string ErVBLlRGYr;
      string ayQaCOqsna;
      string oPiTeEzaes;
      string yRfbDqnFYS;
      string frbanYsRSj;
      string rsgkxnICWH;
      string lpafsJRnXK;
      string ZkUVtxnIeG;
      string LhIuAFjtdO;
      string hkiRfoQuge;
      if(RUWLQlLpdk == ErVBLlRGYr){GEtHJHYKqA = true;}
      else if(ErVBLlRGYr == RUWLQlLpdk){IsDhJbockG = true;}
      if(WSBMPFVCBN == ayQaCOqsna){AAWPuEgffn = true;}
      else if(ayQaCOqsna == WSBMPFVCBN){ONrjuVnGoX = true;}
      if(DDdpbeOMLj == oPiTeEzaes){YWJIboCDpE = true;}
      else if(oPiTeEzaes == DDdpbeOMLj){eqayZPKfzw = true;}
      if(LiCydNpcGW == yRfbDqnFYS){fraAAHmBkr = true;}
      else if(yRfbDqnFYS == LiCydNpcGW){tCWllgfyEV = true;}
      if(jRPkaUuEEa == frbanYsRSj){gZDdOhOSVa = true;}
      else if(frbanYsRSj == jRPkaUuEEa){HAxnBzIkUR = true;}
      if(eNkCeOqfik == rsgkxnICWH){HjPrFitleU = true;}
      else if(rsgkxnICWH == eNkCeOqfik){XybkbQREHs = true;}
      if(XzdsYmPDiC == lpafsJRnXK){EUUlTHYVPn = true;}
      else if(lpafsJRnXK == XzdsYmPDiC){RJcoLMpFyO = true;}
      if(OswdclmrPH == ZkUVtxnIeG){RfumHzTfst = true;}
      if(iJHkEyyATO == LhIuAFjtdO){ZigOxwchuQ = true;}
      if(WJsUyjmVMm == hkiRfoQuge){NBVPnLERJH = true;}
      while(ZkUVtxnIeG == OswdclmrPH){poBTQdtlxa = true;}
      while(LhIuAFjtdO == LhIuAFjtdO){GYLgXwZlJU = true;}
      while(hkiRfoQuge == hkiRfoQuge){OapKEyWIco = true;}
      if(GEtHJHYKqA == true){GEtHJHYKqA = false;}
      if(AAWPuEgffn == true){AAWPuEgffn = false;}
      if(YWJIboCDpE == true){YWJIboCDpE = false;}
      if(fraAAHmBkr == true){fraAAHmBkr = false;}
      if(gZDdOhOSVa == true){gZDdOhOSVa = false;}
      if(HjPrFitleU == true){HjPrFitleU = false;}
      if(EUUlTHYVPn == true){EUUlTHYVPn = false;}
      if(RfumHzTfst == true){RfumHzTfst = false;}
      if(ZigOxwchuQ == true){ZigOxwchuQ = false;}
      if(NBVPnLERJH == true){NBVPnLERJH = false;}
      if(IsDhJbockG == true){IsDhJbockG = false;}
      if(ONrjuVnGoX == true){ONrjuVnGoX = false;}
      if(eqayZPKfzw == true){eqayZPKfzw = false;}
      if(tCWllgfyEV == true){tCWllgfyEV = false;}
      if(HAxnBzIkUR == true){HAxnBzIkUR = false;}
      if(XybkbQREHs == true){XybkbQREHs = false;}
      if(RJcoLMpFyO == true){RJcoLMpFyO = false;}
      if(poBTQdtlxa == true){poBTQdtlxa = false;}
      if(GYLgXwZlJU == true){GYLgXwZlJU = false;}
      if(OapKEyWIco == true){OapKEyWIco = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZURUJHMZM
{ 
  void kRsCXxTmAe()
  { 
      bool RuEJimpEKh = false;
      bool YAzHSRGwsg = false;
      bool jrzYVYzwSB = false;
      bool aBcdVPWjtM = false;
      bool rIHusqGxuh = false;
      bool hPxQwYwfnK = false;
      bool ntlJGWWVlC = false;
      bool tWCfobkDed = false;
      bool SBAjSLEMgx = false;
      bool TqwjYyVynV = false;
      bool TjLsmKMQbU = false;
      bool nrAJqlsBpt = false;
      bool SKoniCZSHp = false;
      bool FmPIKhoHxH = false;
      bool ynkLJapmrl = false;
      bool FTHsDJuXKj = false;
      bool ktIkPBcrzJ = false;
      bool wlEhueYcdI = false;
      bool MmaVkkeVEA = false;
      bool lRxMWEeAuI = false;
      string YJhWUeYNtr;
      string BDwSRxUyVR;
      string zWaQTBTCDX;
      string BXEuOqPZZT;
      string WNEXXqQDmw;
      string MrSgjBhRCT;
      string KWKWpdyADZ;
      string gtYBtkSCrb;
      string kPOHLJEWLN;
      string JxWGJAChht;
      string sQAMORSRmy;
      string hfZahuHCLf;
      string YbnpQjXRrs;
      string hjUxiTPBrs;
      string pljNecXwXO;
      string sAWBUQbKwe;
      string sBZsPyLbqO;
      string eFJRpmraKn;
      string LbtdAhNScS;
      string rFFNzoLpxg;
      if(YJhWUeYNtr == sQAMORSRmy){RuEJimpEKh = true;}
      else if(sQAMORSRmy == YJhWUeYNtr){TjLsmKMQbU = true;}
      if(BDwSRxUyVR == hfZahuHCLf){YAzHSRGwsg = true;}
      else if(hfZahuHCLf == BDwSRxUyVR){nrAJqlsBpt = true;}
      if(zWaQTBTCDX == YbnpQjXRrs){jrzYVYzwSB = true;}
      else if(YbnpQjXRrs == zWaQTBTCDX){SKoniCZSHp = true;}
      if(BXEuOqPZZT == hjUxiTPBrs){aBcdVPWjtM = true;}
      else if(hjUxiTPBrs == BXEuOqPZZT){FmPIKhoHxH = true;}
      if(WNEXXqQDmw == pljNecXwXO){rIHusqGxuh = true;}
      else if(pljNecXwXO == WNEXXqQDmw){ynkLJapmrl = true;}
      if(MrSgjBhRCT == sAWBUQbKwe){hPxQwYwfnK = true;}
      else if(sAWBUQbKwe == MrSgjBhRCT){FTHsDJuXKj = true;}
      if(KWKWpdyADZ == sBZsPyLbqO){ntlJGWWVlC = true;}
      else if(sBZsPyLbqO == KWKWpdyADZ){ktIkPBcrzJ = true;}
      if(gtYBtkSCrb == eFJRpmraKn){tWCfobkDed = true;}
      if(kPOHLJEWLN == LbtdAhNScS){SBAjSLEMgx = true;}
      if(JxWGJAChht == rFFNzoLpxg){TqwjYyVynV = true;}
      while(eFJRpmraKn == gtYBtkSCrb){wlEhueYcdI = true;}
      while(LbtdAhNScS == LbtdAhNScS){MmaVkkeVEA = true;}
      while(rFFNzoLpxg == rFFNzoLpxg){lRxMWEeAuI = true;}
      if(RuEJimpEKh == true){RuEJimpEKh = false;}
      if(YAzHSRGwsg == true){YAzHSRGwsg = false;}
      if(jrzYVYzwSB == true){jrzYVYzwSB = false;}
      if(aBcdVPWjtM == true){aBcdVPWjtM = false;}
      if(rIHusqGxuh == true){rIHusqGxuh = false;}
      if(hPxQwYwfnK == true){hPxQwYwfnK = false;}
      if(ntlJGWWVlC == true){ntlJGWWVlC = false;}
      if(tWCfobkDed == true){tWCfobkDed = false;}
      if(SBAjSLEMgx == true){SBAjSLEMgx = false;}
      if(TqwjYyVynV == true){TqwjYyVynV = false;}
      if(TjLsmKMQbU == true){TjLsmKMQbU = false;}
      if(nrAJqlsBpt == true){nrAJqlsBpt = false;}
      if(SKoniCZSHp == true){SKoniCZSHp = false;}
      if(FmPIKhoHxH == true){FmPIKhoHxH = false;}
      if(ynkLJapmrl == true){ynkLJapmrl = false;}
      if(FTHsDJuXKj == true){FTHsDJuXKj = false;}
      if(ktIkPBcrzJ == true){ktIkPBcrzJ = false;}
      if(wlEhueYcdI == true){wlEhueYcdI = false;}
      if(MmaVkkeVEA == true){MmaVkkeVEA = false;}
      if(lRxMWEeAuI == true){lRxMWEeAuI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JESJJDVQVB
{ 
  void gCeOhkJPmx()
  { 
      bool qVLIULnoXr = false;
      bool HjIYBrlTmo = false;
      bool zXTPlMjORS = false;
      bool mNAzLkRGLZ = false;
      bool uCoTpmeXFR = false;
      bool subZYSBuWH = false;
      bool bZXFFsiJMP = false;
      bool aeINtxiAZz = false;
      bool hLIzYqkaZs = false;
      bool jVjDxVdiOw = false;
      bool DVKpqNmNfb = false;
      bool jBVXYPQXfN = false;
      bool IIiTeEtEPY = false;
      bool SzkduMBSIL = false;
      bool DXtyIiAMeh = false;
      bool EGDBnulqKl = false;
      bool SiyHJkQrbM = false;
      bool OyPUJkNjLw = false;
      bool EhYhTMujoA = false;
      bool ZKHVrUYmnW = false;
      string xkVPyYMXCX;
      string nZcFjBOgoN;
      string GOeNnrPXDs;
      string cHTQzEztDz;
      string lQgusGQaoU;
      string qNqdIhFIbG;
      string JnUJtgGMFf;
      string BTdpbpgjTg;
      string aoiiCPPpHR;
      string yqSwoxwXAM;
      string AEUJSWiACS;
      string AVnteUFlGe;
      string RQEngKBgBd;
      string tJiHgWTYPe;
      string gOmnQcCYRU;
      string rKQVtjzfcI;
      string UBzYYqlgMI;
      string AfVbxCcPXD;
      string HcPfkjrNMx;
      string WmwHJePOPY;
      if(xkVPyYMXCX == AEUJSWiACS){qVLIULnoXr = true;}
      else if(AEUJSWiACS == xkVPyYMXCX){DVKpqNmNfb = true;}
      if(nZcFjBOgoN == AVnteUFlGe){HjIYBrlTmo = true;}
      else if(AVnteUFlGe == nZcFjBOgoN){jBVXYPQXfN = true;}
      if(GOeNnrPXDs == RQEngKBgBd){zXTPlMjORS = true;}
      else if(RQEngKBgBd == GOeNnrPXDs){IIiTeEtEPY = true;}
      if(cHTQzEztDz == tJiHgWTYPe){mNAzLkRGLZ = true;}
      else if(tJiHgWTYPe == cHTQzEztDz){SzkduMBSIL = true;}
      if(lQgusGQaoU == gOmnQcCYRU){uCoTpmeXFR = true;}
      else if(gOmnQcCYRU == lQgusGQaoU){DXtyIiAMeh = true;}
      if(qNqdIhFIbG == rKQVtjzfcI){subZYSBuWH = true;}
      else if(rKQVtjzfcI == qNqdIhFIbG){EGDBnulqKl = true;}
      if(JnUJtgGMFf == UBzYYqlgMI){bZXFFsiJMP = true;}
      else if(UBzYYqlgMI == JnUJtgGMFf){SiyHJkQrbM = true;}
      if(BTdpbpgjTg == AfVbxCcPXD){aeINtxiAZz = true;}
      if(aoiiCPPpHR == HcPfkjrNMx){hLIzYqkaZs = true;}
      if(yqSwoxwXAM == WmwHJePOPY){jVjDxVdiOw = true;}
      while(AfVbxCcPXD == BTdpbpgjTg){OyPUJkNjLw = true;}
      while(HcPfkjrNMx == HcPfkjrNMx){EhYhTMujoA = true;}
      while(WmwHJePOPY == WmwHJePOPY){ZKHVrUYmnW = true;}
      if(qVLIULnoXr == true){qVLIULnoXr = false;}
      if(HjIYBrlTmo == true){HjIYBrlTmo = false;}
      if(zXTPlMjORS == true){zXTPlMjORS = false;}
      if(mNAzLkRGLZ == true){mNAzLkRGLZ = false;}
      if(uCoTpmeXFR == true){uCoTpmeXFR = false;}
      if(subZYSBuWH == true){subZYSBuWH = false;}
      if(bZXFFsiJMP == true){bZXFFsiJMP = false;}
      if(aeINtxiAZz == true){aeINtxiAZz = false;}
      if(hLIzYqkaZs == true){hLIzYqkaZs = false;}
      if(jVjDxVdiOw == true){jVjDxVdiOw = false;}
      if(DVKpqNmNfb == true){DVKpqNmNfb = false;}
      if(jBVXYPQXfN == true){jBVXYPQXfN = false;}
      if(IIiTeEtEPY == true){IIiTeEtEPY = false;}
      if(SzkduMBSIL == true){SzkduMBSIL = false;}
      if(DXtyIiAMeh == true){DXtyIiAMeh = false;}
      if(EGDBnulqKl == true){EGDBnulqKl = false;}
      if(SiyHJkQrbM == true){SiyHJkQrbM = false;}
      if(OyPUJkNjLw == true){OyPUJkNjLw = false;}
      if(EhYhTMujoA == true){EhYhTMujoA = false;}
      if(ZKHVrUYmnW == true){ZKHVrUYmnW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUJKYSILDO
{ 
  void gCJxeKyjnr()
  { 
      bool cPIYZaufzS = false;
      bool frZsNxtOCC = false;
      bool uZCRQdAtSy = false;
      bool FoCGJGZuXs = false;
      bool FBGtOLqbnf = false;
      bool tBKQlCMpHw = false;
      bool ZBNANqoTjG = false;
      bool WypJwtTICF = false;
      bool lYFlEDelUG = false;
      bool tjnbSDnFgX = false;
      bool VXrgIuKATq = false;
      bool iEmCKBuawJ = false;
      bool MDzcMmKOqs = false;
      bool GOadiOfXdJ = false;
      bool sdScXowkRR = false;
      bool HMJXLRYOUU = false;
      bool jwJZkTcISw = false;
      bool UWxlPhkVFW = false;
      bool pZxYksFDSR = false;
      bool oQDIYxTrqD = false;
      string KOhPgbhLsQ;
      string TyqgGqSTlC;
      string CbUfZdGiEt;
      string uKqihbuCeT;
      string ShhztbLMGg;
      string APAVQhtBoC;
      string VzGzVIHIzd;
      string uQnSiUsVly;
      string SscXseKVRz;
      string htMbySaick;
      string UDNbkjahlw;
      string nYPqjbWiGp;
      string ylpzwBDMUP;
      string sKrAdPfAlJ;
      string DciVLJeVrV;
      string wrclmhMNfj;
      string fOMVCdfONT;
      string uVwwmUCUnl;
      string WhTyTAhFMu;
      string DRUCdnPMSh;
      if(KOhPgbhLsQ == UDNbkjahlw){cPIYZaufzS = true;}
      else if(UDNbkjahlw == KOhPgbhLsQ){VXrgIuKATq = true;}
      if(TyqgGqSTlC == nYPqjbWiGp){frZsNxtOCC = true;}
      else if(nYPqjbWiGp == TyqgGqSTlC){iEmCKBuawJ = true;}
      if(CbUfZdGiEt == ylpzwBDMUP){uZCRQdAtSy = true;}
      else if(ylpzwBDMUP == CbUfZdGiEt){MDzcMmKOqs = true;}
      if(uKqihbuCeT == sKrAdPfAlJ){FoCGJGZuXs = true;}
      else if(sKrAdPfAlJ == uKqihbuCeT){GOadiOfXdJ = true;}
      if(ShhztbLMGg == DciVLJeVrV){FBGtOLqbnf = true;}
      else if(DciVLJeVrV == ShhztbLMGg){sdScXowkRR = true;}
      if(APAVQhtBoC == wrclmhMNfj){tBKQlCMpHw = true;}
      else if(wrclmhMNfj == APAVQhtBoC){HMJXLRYOUU = true;}
      if(VzGzVIHIzd == fOMVCdfONT){ZBNANqoTjG = true;}
      else if(fOMVCdfONT == VzGzVIHIzd){jwJZkTcISw = true;}
      if(uQnSiUsVly == uVwwmUCUnl){WypJwtTICF = true;}
      if(SscXseKVRz == WhTyTAhFMu){lYFlEDelUG = true;}
      if(htMbySaick == DRUCdnPMSh){tjnbSDnFgX = true;}
      while(uVwwmUCUnl == uQnSiUsVly){UWxlPhkVFW = true;}
      while(WhTyTAhFMu == WhTyTAhFMu){pZxYksFDSR = true;}
      while(DRUCdnPMSh == DRUCdnPMSh){oQDIYxTrqD = true;}
      if(cPIYZaufzS == true){cPIYZaufzS = false;}
      if(frZsNxtOCC == true){frZsNxtOCC = false;}
      if(uZCRQdAtSy == true){uZCRQdAtSy = false;}
      if(FoCGJGZuXs == true){FoCGJGZuXs = false;}
      if(FBGtOLqbnf == true){FBGtOLqbnf = false;}
      if(tBKQlCMpHw == true){tBKQlCMpHw = false;}
      if(ZBNANqoTjG == true){ZBNANqoTjG = false;}
      if(WypJwtTICF == true){WypJwtTICF = false;}
      if(lYFlEDelUG == true){lYFlEDelUG = false;}
      if(tjnbSDnFgX == true){tjnbSDnFgX = false;}
      if(VXrgIuKATq == true){VXrgIuKATq = false;}
      if(iEmCKBuawJ == true){iEmCKBuawJ = false;}
      if(MDzcMmKOqs == true){MDzcMmKOqs = false;}
      if(GOadiOfXdJ == true){GOadiOfXdJ = false;}
      if(sdScXowkRR == true){sdScXowkRR = false;}
      if(HMJXLRYOUU == true){HMJXLRYOUU = false;}
      if(jwJZkTcISw == true){jwJZkTcISw = false;}
      if(UWxlPhkVFW == true){UWxlPhkVFW = false;}
      if(pZxYksFDSR == true){pZxYksFDSR = false;}
      if(oQDIYxTrqD == true){oQDIYxTrqD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBLEHBAMEO
{ 
  void KPDKRgusQf()
  { 
      bool ybuMwzXlOh = false;
      bool kReHIWJhaj = false;
      bool EdzjjnbeYw = false;
      bool LlrwrLkqra = false;
      bool lICXaRCWyG = false;
      bool ufCofTbLbH = false;
      bool WrMSWyZhPx = false;
      bool lRoAywabJS = false;
      bool kEgRBeiCPX = false;
      bool jYPjDsujBb = false;
      bool rTHBUdpCqj = false;
      bool szCJVRKuRq = false;
      bool PWSqNMBExE = false;
      bool BpagZQxfxW = false;
      bool ofLfejWGOk = false;
      bool hzSKMVBQnH = false;
      bool bkFmhCYUiE = false;
      bool UextBiKlMc = false;
      bool otpLVBXQUE = false;
      bool PgrouDaYxb = false;
      string RXRcSZzTDF;
      string udosTWpMHR;
      string jafSLklBIJ;
      string VZVTINAREU;
      string qNSQmDrOnm;
      string AGOIkprzQh;
      string myLsiUHUjF;
      string VYHmaVIPeI;
      string rXMUJPLNiS;
      string VBAWgsBYhR;
      string uWdhQbybhO;
      string hbTIoPkpjS;
      string JtlRjUXkFg;
      string UigNMUsdDg;
      string RjeTjsgqgR;
      string HKnPHAkMyw;
      string DNVAtzuFwU;
      string VHmCAZPShp;
      string mfDnZJtRFL;
      string jgeHdENdZk;
      if(RXRcSZzTDF == uWdhQbybhO){ybuMwzXlOh = true;}
      else if(uWdhQbybhO == RXRcSZzTDF){rTHBUdpCqj = true;}
      if(udosTWpMHR == hbTIoPkpjS){kReHIWJhaj = true;}
      else if(hbTIoPkpjS == udosTWpMHR){szCJVRKuRq = true;}
      if(jafSLklBIJ == JtlRjUXkFg){EdzjjnbeYw = true;}
      else if(JtlRjUXkFg == jafSLklBIJ){PWSqNMBExE = true;}
      if(VZVTINAREU == UigNMUsdDg){LlrwrLkqra = true;}
      else if(UigNMUsdDg == VZVTINAREU){BpagZQxfxW = true;}
      if(qNSQmDrOnm == RjeTjsgqgR){lICXaRCWyG = true;}
      else if(RjeTjsgqgR == qNSQmDrOnm){ofLfejWGOk = true;}
      if(AGOIkprzQh == HKnPHAkMyw){ufCofTbLbH = true;}
      else if(HKnPHAkMyw == AGOIkprzQh){hzSKMVBQnH = true;}
      if(myLsiUHUjF == DNVAtzuFwU){WrMSWyZhPx = true;}
      else if(DNVAtzuFwU == myLsiUHUjF){bkFmhCYUiE = true;}
      if(VYHmaVIPeI == VHmCAZPShp){lRoAywabJS = true;}
      if(rXMUJPLNiS == mfDnZJtRFL){kEgRBeiCPX = true;}
      if(VBAWgsBYhR == jgeHdENdZk){jYPjDsujBb = true;}
      while(VHmCAZPShp == VYHmaVIPeI){UextBiKlMc = true;}
      while(mfDnZJtRFL == mfDnZJtRFL){otpLVBXQUE = true;}
      while(jgeHdENdZk == jgeHdENdZk){PgrouDaYxb = true;}
      if(ybuMwzXlOh == true){ybuMwzXlOh = false;}
      if(kReHIWJhaj == true){kReHIWJhaj = false;}
      if(EdzjjnbeYw == true){EdzjjnbeYw = false;}
      if(LlrwrLkqra == true){LlrwrLkqra = false;}
      if(lICXaRCWyG == true){lICXaRCWyG = false;}
      if(ufCofTbLbH == true){ufCofTbLbH = false;}
      if(WrMSWyZhPx == true){WrMSWyZhPx = false;}
      if(lRoAywabJS == true){lRoAywabJS = false;}
      if(kEgRBeiCPX == true){kEgRBeiCPX = false;}
      if(jYPjDsujBb == true){jYPjDsujBb = false;}
      if(rTHBUdpCqj == true){rTHBUdpCqj = false;}
      if(szCJVRKuRq == true){szCJVRKuRq = false;}
      if(PWSqNMBExE == true){PWSqNMBExE = false;}
      if(BpagZQxfxW == true){BpagZQxfxW = false;}
      if(ofLfejWGOk == true){ofLfejWGOk = false;}
      if(hzSKMVBQnH == true){hzSKMVBQnH = false;}
      if(bkFmhCYUiE == true){bkFmhCYUiE = false;}
      if(UextBiKlMc == true){UextBiKlMc = false;}
      if(otpLVBXQUE == true){otpLVBXQUE = false;}
      if(PgrouDaYxb == true){PgrouDaYxb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIQETMLKVO
{ 
  void MUHHPCugpq()
  { 
      bool hDKxpCBOak = false;
      bool RxENcpUGHa = false;
      bool tpnKtwEqEW = false;
      bool sBeDXRrJCB = false;
      bool sGSNGeaGTd = false;
      bool DIjVArOzCs = false;
      bool xJKEqQSAoL = false;
      bool yKEFgmWaEO = false;
      bool VyWZTkQIDf = false;
      bool DrGIEiwOVo = false;
      bool MZQIerDdoM = false;
      bool UmunXzljjG = false;
      bool zJxJIGEwBx = false;
      bool qIFOCwhOua = false;
      bool hlTpKPxSjF = false;
      bool wMdOoCbGAY = false;
      bool nHcqVMgfkb = false;
      bool RXoJXMpHzr = false;
      bool IkLuAdepZz = false;
      bool TaOWmaJcUy = false;
      string DeRnyNNqof;
      string LnCktBZNUy;
      string XwxYgDFTBz;
      string gQAkpBQRpj;
      string fOOPMsiIlu;
      string xcsHNGhsGt;
      string HspoztnQts;
      string jHXkRIhgLn;
      string UxgGCEWrWj;
      string TXLubmYZQS;
      string FSNsKoEIpF;
      string YAgRZKMilt;
      string XusKYMwcJe;
      string jIPsiCinuN;
      string zOCRLSqsVR;
      string aomVtKYDTy;
      string sbzLUPjmiX;
      string bXnYtIrazG;
      string UCHrEtUtyX;
      string ceTxUXPqwu;
      if(DeRnyNNqof == FSNsKoEIpF){hDKxpCBOak = true;}
      else if(FSNsKoEIpF == DeRnyNNqof){MZQIerDdoM = true;}
      if(LnCktBZNUy == YAgRZKMilt){RxENcpUGHa = true;}
      else if(YAgRZKMilt == LnCktBZNUy){UmunXzljjG = true;}
      if(XwxYgDFTBz == XusKYMwcJe){tpnKtwEqEW = true;}
      else if(XusKYMwcJe == XwxYgDFTBz){zJxJIGEwBx = true;}
      if(gQAkpBQRpj == jIPsiCinuN){sBeDXRrJCB = true;}
      else if(jIPsiCinuN == gQAkpBQRpj){qIFOCwhOua = true;}
      if(fOOPMsiIlu == zOCRLSqsVR){sGSNGeaGTd = true;}
      else if(zOCRLSqsVR == fOOPMsiIlu){hlTpKPxSjF = true;}
      if(xcsHNGhsGt == aomVtKYDTy){DIjVArOzCs = true;}
      else if(aomVtKYDTy == xcsHNGhsGt){wMdOoCbGAY = true;}
      if(HspoztnQts == sbzLUPjmiX){xJKEqQSAoL = true;}
      else if(sbzLUPjmiX == HspoztnQts){nHcqVMgfkb = true;}
      if(jHXkRIhgLn == bXnYtIrazG){yKEFgmWaEO = true;}
      if(UxgGCEWrWj == UCHrEtUtyX){VyWZTkQIDf = true;}
      if(TXLubmYZQS == ceTxUXPqwu){DrGIEiwOVo = true;}
      while(bXnYtIrazG == jHXkRIhgLn){RXoJXMpHzr = true;}
      while(UCHrEtUtyX == UCHrEtUtyX){IkLuAdepZz = true;}
      while(ceTxUXPqwu == ceTxUXPqwu){TaOWmaJcUy = true;}
      if(hDKxpCBOak == true){hDKxpCBOak = false;}
      if(RxENcpUGHa == true){RxENcpUGHa = false;}
      if(tpnKtwEqEW == true){tpnKtwEqEW = false;}
      if(sBeDXRrJCB == true){sBeDXRrJCB = false;}
      if(sGSNGeaGTd == true){sGSNGeaGTd = false;}
      if(DIjVArOzCs == true){DIjVArOzCs = false;}
      if(xJKEqQSAoL == true){xJKEqQSAoL = false;}
      if(yKEFgmWaEO == true){yKEFgmWaEO = false;}
      if(VyWZTkQIDf == true){VyWZTkQIDf = false;}
      if(DrGIEiwOVo == true){DrGIEiwOVo = false;}
      if(MZQIerDdoM == true){MZQIerDdoM = false;}
      if(UmunXzljjG == true){UmunXzljjG = false;}
      if(zJxJIGEwBx == true){zJxJIGEwBx = false;}
      if(qIFOCwhOua == true){qIFOCwhOua = false;}
      if(hlTpKPxSjF == true){hlTpKPxSjF = false;}
      if(wMdOoCbGAY == true){wMdOoCbGAY = false;}
      if(nHcqVMgfkb == true){nHcqVMgfkb = false;}
      if(RXoJXMpHzr == true){RXoJXMpHzr = false;}
      if(IkLuAdepZz == true){IkLuAdepZz = false;}
      if(TaOWmaJcUy == true){TaOWmaJcUy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DPJKTXQAKG
{ 
  void mqmGkLGKdq()
  { 
      bool ycdotPmiSf = false;
      bool OcqAHqlKcG = false;
      bool YClSbLTCLD = false;
      bool VXccRBjZnQ = false;
      bool MZEyRmpVsp = false;
      bool hVcHkuqKNi = false;
      bool ujXOKpANhF = false;
      bool GLWLtzynAo = false;
      bool UyJUVAuVrV = false;
      bool KZMFVbBoma = false;
      bool lcmmjWyQNl = false;
      bool xCJYOwaCsJ = false;
      bool udVLtgzRoR = false;
      bool xJAZCqKVkz = false;
      bool BdIFYIPnpY = false;
      bool AzucfIHasC = false;
      bool WgauonBjVW = false;
      bool kFRtIRVPml = false;
      bool RKaPRyOWtt = false;
      bool jjchbUCNQk = false;
      string quOBOFXMxi;
      string ymTXHfrGpc;
      string JZDJLWaBQf;
      string UbereFfuBY;
      string GgbAiwHDIN;
      string tCjSaRrFpr;
      string dWuRNVHbsC;
      string AxFRVcxCZP;
      string PXsCkSrMRM;
      string NZEJtikKmM;
      string neKFNxxRwx;
      string UoeabGdsgt;
      string ctKfnZruXl;
      string qlPNajMmom;
      string VaPTrXtdgn;
      string FqcrisTeQm;
      string FBtJGhZQAr;
      string spEsYCeqmQ;
      string eOOigzJWeg;
      string PhVBhUfGNK;
      if(quOBOFXMxi == neKFNxxRwx){ycdotPmiSf = true;}
      else if(neKFNxxRwx == quOBOFXMxi){lcmmjWyQNl = true;}
      if(ymTXHfrGpc == UoeabGdsgt){OcqAHqlKcG = true;}
      else if(UoeabGdsgt == ymTXHfrGpc){xCJYOwaCsJ = true;}
      if(JZDJLWaBQf == ctKfnZruXl){YClSbLTCLD = true;}
      else if(ctKfnZruXl == JZDJLWaBQf){udVLtgzRoR = true;}
      if(UbereFfuBY == qlPNajMmom){VXccRBjZnQ = true;}
      else if(qlPNajMmom == UbereFfuBY){xJAZCqKVkz = true;}
      if(GgbAiwHDIN == VaPTrXtdgn){MZEyRmpVsp = true;}
      else if(VaPTrXtdgn == GgbAiwHDIN){BdIFYIPnpY = true;}
      if(tCjSaRrFpr == FqcrisTeQm){hVcHkuqKNi = true;}
      else if(FqcrisTeQm == tCjSaRrFpr){AzucfIHasC = true;}
      if(dWuRNVHbsC == FBtJGhZQAr){ujXOKpANhF = true;}
      else if(FBtJGhZQAr == dWuRNVHbsC){WgauonBjVW = true;}
      if(AxFRVcxCZP == spEsYCeqmQ){GLWLtzynAo = true;}
      if(PXsCkSrMRM == eOOigzJWeg){UyJUVAuVrV = true;}
      if(NZEJtikKmM == PhVBhUfGNK){KZMFVbBoma = true;}
      while(spEsYCeqmQ == AxFRVcxCZP){kFRtIRVPml = true;}
      while(eOOigzJWeg == eOOigzJWeg){RKaPRyOWtt = true;}
      while(PhVBhUfGNK == PhVBhUfGNK){jjchbUCNQk = true;}
      if(ycdotPmiSf == true){ycdotPmiSf = false;}
      if(OcqAHqlKcG == true){OcqAHqlKcG = false;}
      if(YClSbLTCLD == true){YClSbLTCLD = false;}
      if(VXccRBjZnQ == true){VXccRBjZnQ = false;}
      if(MZEyRmpVsp == true){MZEyRmpVsp = false;}
      if(hVcHkuqKNi == true){hVcHkuqKNi = false;}
      if(ujXOKpANhF == true){ujXOKpANhF = false;}
      if(GLWLtzynAo == true){GLWLtzynAo = false;}
      if(UyJUVAuVrV == true){UyJUVAuVrV = false;}
      if(KZMFVbBoma == true){KZMFVbBoma = false;}
      if(lcmmjWyQNl == true){lcmmjWyQNl = false;}
      if(xCJYOwaCsJ == true){xCJYOwaCsJ = false;}
      if(udVLtgzRoR == true){udVLtgzRoR = false;}
      if(xJAZCqKVkz == true){xJAZCqKVkz = false;}
      if(BdIFYIPnpY == true){BdIFYIPnpY = false;}
      if(AzucfIHasC == true){AzucfIHasC = false;}
      if(WgauonBjVW == true){WgauonBjVW = false;}
      if(kFRtIRVPml == true){kFRtIRVPml = false;}
      if(RKaPRyOWtt == true){RKaPRyOWtt = false;}
      if(jjchbUCNQk == true){jjchbUCNQk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRWNAWRXDO
{ 
  void lgNfFbtcaU()
  { 
      bool QRhlHRgYrZ = false;
      bool YoQnXHoSIz = false;
      bool JkjnXbcrIj = false;
      bool sxcJlMtLAk = false;
      bool TxheSofayO = false;
      bool yTsUdegsNf = false;
      bool noQIfbMHBK = false;
      bool NcRXeLDEVi = false;
      bool wCstkYDIeG = false;
      bool fBxUwegYzq = false;
      bool cXYnAUBVpR = false;
      bool bcXeiluVXH = false;
      bool XEbueMfxbz = false;
      bool ddFdFXcFsQ = false;
      bool WgRMeCcSlJ = false;
      bool jLBrSYwdIn = false;
      bool oEtpnxXsYK = false;
      bool IpcGjplOPb = false;
      bool iMKRPScNLg = false;
      bool bzwEaRmaYg = false;
      string BbMpysdEla;
      string fhityVQxxB;
      string YcTuoIRGAQ;
      string aCgzAnaMzr;
      string eoLOflmZfk;
      string gYWtgYIQAo;
      string bXEVAcAisK;
      string uExFViQFPD;
      string UqZOjCfmRb;
      string fJMJQHkpOD;
      string lDfUocaQYy;
      string HCBxUjxoly;
      string wNQRelqmoN;
      string xaqLQRKEZG;
      string aPNTUcHOof;
      string KwDPGYlOpC;
      string kmbLAfLofD;
      string YrOeWgzxxC;
      string ecyIDBWaFr;
      string ewOWVmmCTn;
      if(BbMpysdEla == lDfUocaQYy){QRhlHRgYrZ = true;}
      else if(lDfUocaQYy == BbMpysdEla){cXYnAUBVpR = true;}
      if(fhityVQxxB == HCBxUjxoly){YoQnXHoSIz = true;}
      else if(HCBxUjxoly == fhityVQxxB){bcXeiluVXH = true;}
      if(YcTuoIRGAQ == wNQRelqmoN){JkjnXbcrIj = true;}
      else if(wNQRelqmoN == YcTuoIRGAQ){XEbueMfxbz = true;}
      if(aCgzAnaMzr == xaqLQRKEZG){sxcJlMtLAk = true;}
      else if(xaqLQRKEZG == aCgzAnaMzr){ddFdFXcFsQ = true;}
      if(eoLOflmZfk == aPNTUcHOof){TxheSofayO = true;}
      else if(aPNTUcHOof == eoLOflmZfk){WgRMeCcSlJ = true;}
      if(gYWtgYIQAo == KwDPGYlOpC){yTsUdegsNf = true;}
      else if(KwDPGYlOpC == gYWtgYIQAo){jLBrSYwdIn = true;}
      if(bXEVAcAisK == kmbLAfLofD){noQIfbMHBK = true;}
      else if(kmbLAfLofD == bXEVAcAisK){oEtpnxXsYK = true;}
      if(uExFViQFPD == YrOeWgzxxC){NcRXeLDEVi = true;}
      if(UqZOjCfmRb == ecyIDBWaFr){wCstkYDIeG = true;}
      if(fJMJQHkpOD == ewOWVmmCTn){fBxUwegYzq = true;}
      while(YrOeWgzxxC == uExFViQFPD){IpcGjplOPb = true;}
      while(ecyIDBWaFr == ecyIDBWaFr){iMKRPScNLg = true;}
      while(ewOWVmmCTn == ewOWVmmCTn){bzwEaRmaYg = true;}
      if(QRhlHRgYrZ == true){QRhlHRgYrZ = false;}
      if(YoQnXHoSIz == true){YoQnXHoSIz = false;}
      if(JkjnXbcrIj == true){JkjnXbcrIj = false;}
      if(sxcJlMtLAk == true){sxcJlMtLAk = false;}
      if(TxheSofayO == true){TxheSofayO = false;}
      if(yTsUdegsNf == true){yTsUdegsNf = false;}
      if(noQIfbMHBK == true){noQIfbMHBK = false;}
      if(NcRXeLDEVi == true){NcRXeLDEVi = false;}
      if(wCstkYDIeG == true){wCstkYDIeG = false;}
      if(fBxUwegYzq == true){fBxUwegYzq = false;}
      if(cXYnAUBVpR == true){cXYnAUBVpR = false;}
      if(bcXeiluVXH == true){bcXeiluVXH = false;}
      if(XEbueMfxbz == true){XEbueMfxbz = false;}
      if(ddFdFXcFsQ == true){ddFdFXcFsQ = false;}
      if(WgRMeCcSlJ == true){WgRMeCcSlJ = false;}
      if(jLBrSYwdIn == true){jLBrSYwdIn = false;}
      if(oEtpnxXsYK == true){oEtpnxXsYK = false;}
      if(IpcGjplOPb == true){IpcGjplOPb = false;}
      if(iMKRPScNLg == true){iMKRPScNLg = false;}
      if(bzwEaRmaYg == true){bzwEaRmaYg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLJQEHVBWZ
{ 
  void VNVSmXZfsJ()
  { 
      bool LTprrsxwXj = false;
      bool lieGKDxuCT = false;
      bool XwwtWfKrQN = false;
      bool KWJezGVwxt = false;
      bool zOcXbaTeap = false;
      bool VJbHnOWwVL = false;
      bool iEfJYPYzGD = false;
      bool hAxIUITYRu = false;
      bool MeRZqBtBqk = false;
      bool iZakKtiSzM = false;
      bool BTYWHVLTme = false;
      bool uydZyDmFSX = false;
      bool UXIVTHYMxZ = false;
      bool ZAYFssGtSV = false;
      bool oaOLokuAmG = false;
      bool HdzbrdKCCA = false;
      bool wzWMFtYYgE = false;
      bool xrlxhtIwgi = false;
      bool MXZpSuAxMO = false;
      bool iDrSYpDBGt = false;
      string PZmHXfwYiF;
      string RlUPgqCecD;
      string YXeOihIEVe;
      string LWbNlEIhct;
      string icejBUFiOQ;
      string tEhniruYYp;
      string XqDEsuKHdc;
      string hTCiUwrtNN;
      string cYpEjHonds;
      string IjJmVqYapF;
      string KxFliZBySm;
      string zALLMyByTl;
      string GWcjTyKPMd;
      string WREHCeTEVJ;
      string FpUqsIXyZW;
      string pZGDznUURj;
      string PlkoPhwEIg;
      string ewcKfPBkpL;
      string ZLopmwKAHO;
      string KylktSEebL;
      if(PZmHXfwYiF == KxFliZBySm){LTprrsxwXj = true;}
      else if(KxFliZBySm == PZmHXfwYiF){BTYWHVLTme = true;}
      if(RlUPgqCecD == zALLMyByTl){lieGKDxuCT = true;}
      else if(zALLMyByTl == RlUPgqCecD){uydZyDmFSX = true;}
      if(YXeOihIEVe == GWcjTyKPMd){XwwtWfKrQN = true;}
      else if(GWcjTyKPMd == YXeOihIEVe){UXIVTHYMxZ = true;}
      if(LWbNlEIhct == WREHCeTEVJ){KWJezGVwxt = true;}
      else if(WREHCeTEVJ == LWbNlEIhct){ZAYFssGtSV = true;}
      if(icejBUFiOQ == FpUqsIXyZW){zOcXbaTeap = true;}
      else if(FpUqsIXyZW == icejBUFiOQ){oaOLokuAmG = true;}
      if(tEhniruYYp == pZGDznUURj){VJbHnOWwVL = true;}
      else if(pZGDznUURj == tEhniruYYp){HdzbrdKCCA = true;}
      if(XqDEsuKHdc == PlkoPhwEIg){iEfJYPYzGD = true;}
      else if(PlkoPhwEIg == XqDEsuKHdc){wzWMFtYYgE = true;}
      if(hTCiUwrtNN == ewcKfPBkpL){hAxIUITYRu = true;}
      if(cYpEjHonds == ZLopmwKAHO){MeRZqBtBqk = true;}
      if(IjJmVqYapF == KylktSEebL){iZakKtiSzM = true;}
      while(ewcKfPBkpL == hTCiUwrtNN){xrlxhtIwgi = true;}
      while(ZLopmwKAHO == ZLopmwKAHO){MXZpSuAxMO = true;}
      while(KylktSEebL == KylktSEebL){iDrSYpDBGt = true;}
      if(LTprrsxwXj == true){LTprrsxwXj = false;}
      if(lieGKDxuCT == true){lieGKDxuCT = false;}
      if(XwwtWfKrQN == true){XwwtWfKrQN = false;}
      if(KWJezGVwxt == true){KWJezGVwxt = false;}
      if(zOcXbaTeap == true){zOcXbaTeap = false;}
      if(VJbHnOWwVL == true){VJbHnOWwVL = false;}
      if(iEfJYPYzGD == true){iEfJYPYzGD = false;}
      if(hAxIUITYRu == true){hAxIUITYRu = false;}
      if(MeRZqBtBqk == true){MeRZqBtBqk = false;}
      if(iZakKtiSzM == true){iZakKtiSzM = false;}
      if(BTYWHVLTme == true){BTYWHVLTme = false;}
      if(uydZyDmFSX == true){uydZyDmFSX = false;}
      if(UXIVTHYMxZ == true){UXIVTHYMxZ = false;}
      if(ZAYFssGtSV == true){ZAYFssGtSV = false;}
      if(oaOLokuAmG == true){oaOLokuAmG = false;}
      if(HdzbrdKCCA == true){HdzbrdKCCA = false;}
      if(wzWMFtYYgE == true){wzWMFtYYgE = false;}
      if(xrlxhtIwgi == true){xrlxhtIwgi = false;}
      if(MXZpSuAxMO == true){MXZpSuAxMO = false;}
      if(iDrSYpDBGt == true){iDrSYpDBGt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGAEIRGLEE
{ 
  void RPLMxVbHcp()
  { 
      bool JjbXcMdNWp = false;
      bool utesjhfqUE = false;
      bool xrWHSxNYOD = false;
      bool cuJQMdKFOz = false;
      bool elGSpGRBpy = false;
      bool qIJwsRMTFf = false;
      bool zEzSMAjNgG = false;
      bool XZbVYKlERL = false;
      bool fMiQMUkNXt = false;
      bool QpzizZmmFo = false;
      bool VDUiZQfmWh = false;
      bool fHCtAmVhFr = false;
      bool PWolohZsVz = false;
      bool Xyzbobqzpw = false;
      bool nxppOImFhM = false;
      bool EEhMZyOhsr = false;
      bool pmRXJgIZFY = false;
      bool uVrJDRgyWg = false;
      bool tUKJtTQlCp = false;
      bool NIFyFBfSfg = false;
      string NczFCVPGOt;
      string qYpzgrWGBB;
      string PsBimwfVgn;
      string buKDMDopVn;
      string gaeWaVPSte;
      string JPMjoTaQRF;
      string osZZSuNmld;
      string CfkNUnNeHQ;
      string gNaBdLiaOr;
      string bYXPymBFEf;
      string IbfQbcezOA;
      string FwIBXaRXwG;
      string MlXtBdIUPg;
      string lIabHFhJYB;
      string fiMNmePVqW;
      string UcIxTVElPy;
      string UJjgNwVftS;
      string sIzuacZJHV;
      string NldrLJzcIl;
      string AwtZfWzeAp;
      if(NczFCVPGOt == IbfQbcezOA){JjbXcMdNWp = true;}
      else if(IbfQbcezOA == NczFCVPGOt){VDUiZQfmWh = true;}
      if(qYpzgrWGBB == FwIBXaRXwG){utesjhfqUE = true;}
      else if(FwIBXaRXwG == qYpzgrWGBB){fHCtAmVhFr = true;}
      if(PsBimwfVgn == MlXtBdIUPg){xrWHSxNYOD = true;}
      else if(MlXtBdIUPg == PsBimwfVgn){PWolohZsVz = true;}
      if(buKDMDopVn == lIabHFhJYB){cuJQMdKFOz = true;}
      else if(lIabHFhJYB == buKDMDopVn){Xyzbobqzpw = true;}
      if(gaeWaVPSte == fiMNmePVqW){elGSpGRBpy = true;}
      else if(fiMNmePVqW == gaeWaVPSte){nxppOImFhM = true;}
      if(JPMjoTaQRF == UcIxTVElPy){qIJwsRMTFf = true;}
      else if(UcIxTVElPy == JPMjoTaQRF){EEhMZyOhsr = true;}
      if(osZZSuNmld == UJjgNwVftS){zEzSMAjNgG = true;}
      else if(UJjgNwVftS == osZZSuNmld){pmRXJgIZFY = true;}
      if(CfkNUnNeHQ == sIzuacZJHV){XZbVYKlERL = true;}
      if(gNaBdLiaOr == NldrLJzcIl){fMiQMUkNXt = true;}
      if(bYXPymBFEf == AwtZfWzeAp){QpzizZmmFo = true;}
      while(sIzuacZJHV == CfkNUnNeHQ){uVrJDRgyWg = true;}
      while(NldrLJzcIl == NldrLJzcIl){tUKJtTQlCp = true;}
      while(AwtZfWzeAp == AwtZfWzeAp){NIFyFBfSfg = true;}
      if(JjbXcMdNWp == true){JjbXcMdNWp = false;}
      if(utesjhfqUE == true){utesjhfqUE = false;}
      if(xrWHSxNYOD == true){xrWHSxNYOD = false;}
      if(cuJQMdKFOz == true){cuJQMdKFOz = false;}
      if(elGSpGRBpy == true){elGSpGRBpy = false;}
      if(qIJwsRMTFf == true){qIJwsRMTFf = false;}
      if(zEzSMAjNgG == true){zEzSMAjNgG = false;}
      if(XZbVYKlERL == true){XZbVYKlERL = false;}
      if(fMiQMUkNXt == true){fMiQMUkNXt = false;}
      if(QpzizZmmFo == true){QpzizZmmFo = false;}
      if(VDUiZQfmWh == true){VDUiZQfmWh = false;}
      if(fHCtAmVhFr == true){fHCtAmVhFr = false;}
      if(PWolohZsVz == true){PWolohZsVz = false;}
      if(Xyzbobqzpw == true){Xyzbobqzpw = false;}
      if(nxppOImFhM == true){nxppOImFhM = false;}
      if(EEhMZyOhsr == true){EEhMZyOhsr = false;}
      if(pmRXJgIZFY == true){pmRXJgIZFY = false;}
      if(uVrJDRgyWg == true){uVrJDRgyWg = false;}
      if(tUKJtTQlCp == true){tUKJtTQlCp = false;}
      if(NIFyFBfSfg == true){NIFyFBfSfg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSTOSGKSBP
{ 
  void AFKQwcZXZl()
  { 
      bool SiAapbqpTU = false;
      bool MYNlsFggSM = false;
      bool rSgwxgVIOK = false;
      bool GDYKyNCOKx = false;
      bool pKzBOJbLub = false;
      bool IlJlTABDcI = false;
      bool FhaJNJADmf = false;
      bool CRWVVhSfhn = false;
      bool FJMlBTslqy = false;
      bool LzlCqHjpmE = false;
      bool IYXPYqPmQl = false;
      bool gVUoDuVnHt = false;
      bool POLoTDeTeN = false;
      bool xcrceflxMK = false;
      bool DGUERpdxyu = false;
      bool luhsntMiuV = false;
      bool LuHCnDcrJW = false;
      bool JYaxpJsGXd = false;
      bool YhVjbCuznk = false;
      bool TDBqyHySQN = false;
      string AoFxuKAGXF;
      string AJqBYMUmay;
      string mEtsonWDXI;
      string MXbOjYUZYA;
      string NApZCarfaR;
      string fgXwDwtMHG;
      string nxiPrcgcRA;
      string rtOajmOUqO;
      string upbFbezfKn;
      string dISRLQRZgY;
      string sPOZZkSxLQ;
      string hYVsLyUcmM;
      string cASdWibwOT;
      string VnmRUfaBfq;
      string MCUtGEmYGN;
      string unmTusxkDp;
      string IWhrtslDYf;
      string WTxwAafXWR;
      string wDoBYgBSVb;
      string hpxohpTczM;
      if(AoFxuKAGXF == sPOZZkSxLQ){SiAapbqpTU = true;}
      else if(sPOZZkSxLQ == AoFxuKAGXF){IYXPYqPmQl = true;}
      if(AJqBYMUmay == hYVsLyUcmM){MYNlsFggSM = true;}
      else if(hYVsLyUcmM == AJqBYMUmay){gVUoDuVnHt = true;}
      if(mEtsonWDXI == cASdWibwOT){rSgwxgVIOK = true;}
      else if(cASdWibwOT == mEtsonWDXI){POLoTDeTeN = true;}
      if(MXbOjYUZYA == VnmRUfaBfq){GDYKyNCOKx = true;}
      else if(VnmRUfaBfq == MXbOjYUZYA){xcrceflxMK = true;}
      if(NApZCarfaR == MCUtGEmYGN){pKzBOJbLub = true;}
      else if(MCUtGEmYGN == NApZCarfaR){DGUERpdxyu = true;}
      if(fgXwDwtMHG == unmTusxkDp){IlJlTABDcI = true;}
      else if(unmTusxkDp == fgXwDwtMHG){luhsntMiuV = true;}
      if(nxiPrcgcRA == IWhrtslDYf){FhaJNJADmf = true;}
      else if(IWhrtslDYf == nxiPrcgcRA){LuHCnDcrJW = true;}
      if(rtOajmOUqO == WTxwAafXWR){CRWVVhSfhn = true;}
      if(upbFbezfKn == wDoBYgBSVb){FJMlBTslqy = true;}
      if(dISRLQRZgY == hpxohpTczM){LzlCqHjpmE = true;}
      while(WTxwAafXWR == rtOajmOUqO){JYaxpJsGXd = true;}
      while(wDoBYgBSVb == wDoBYgBSVb){YhVjbCuznk = true;}
      while(hpxohpTczM == hpxohpTczM){TDBqyHySQN = true;}
      if(SiAapbqpTU == true){SiAapbqpTU = false;}
      if(MYNlsFggSM == true){MYNlsFggSM = false;}
      if(rSgwxgVIOK == true){rSgwxgVIOK = false;}
      if(GDYKyNCOKx == true){GDYKyNCOKx = false;}
      if(pKzBOJbLub == true){pKzBOJbLub = false;}
      if(IlJlTABDcI == true){IlJlTABDcI = false;}
      if(FhaJNJADmf == true){FhaJNJADmf = false;}
      if(CRWVVhSfhn == true){CRWVVhSfhn = false;}
      if(FJMlBTslqy == true){FJMlBTslqy = false;}
      if(LzlCqHjpmE == true){LzlCqHjpmE = false;}
      if(IYXPYqPmQl == true){IYXPYqPmQl = false;}
      if(gVUoDuVnHt == true){gVUoDuVnHt = false;}
      if(POLoTDeTeN == true){POLoTDeTeN = false;}
      if(xcrceflxMK == true){xcrceflxMK = false;}
      if(DGUERpdxyu == true){DGUERpdxyu = false;}
      if(luhsntMiuV == true){luhsntMiuV = false;}
      if(LuHCnDcrJW == true){LuHCnDcrJW = false;}
      if(JYaxpJsGXd == true){JYaxpJsGXd = false;}
      if(YhVjbCuznk == true){YhVjbCuznk = false;}
      if(TDBqyHySQN == true){TDBqyHySQN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWIJSRVFAP
{ 
  void luIgjhXFrB()
  { 
      bool fYVShQFUVq = false;
      bool TOuYEJrrxY = false;
      bool bVmRsRAhxM = false;
      bool yLWEBDyeCb = false;
      bool stoJbDtdkx = false;
      bool mdfwEJkDYQ = false;
      bool QWXJrIrqXA = false;
      bool LMpVfggdpo = false;
      bool WVxAYUeZzq = false;
      bool StGlKVWfQS = false;
      bool LDGkkZnKQX = false;
      bool cHMjsuZWjX = false;
      bool dRqfgQGEKK = false;
      bool KBNXdTPMOz = false;
      bool fTJbOKgWrP = false;
      bool wzurnsLZDT = false;
      bool SjAGMbtoFZ = false;
      bool fMIjrJHPRW = false;
      bool ijLtNLFUij = false;
      bool IoIugwTDOm = false;
      string GlIUqIzIMA;
      string ZKWxpVAKHD;
      string LYeHbmPaVE;
      string yAaskbQuSN;
      string HKVdJDVCPb;
      string mJxBAhHBrD;
      string rYmHBYidLO;
      string FFqtwACByY;
      string RNKsRnDYsC;
      string TPCPUhXObj;
      string TrpBWgRDEz;
      string eGCSkeNtoN;
      string VJkJtpDbZN;
      string bnYOFZWJVk;
      string VAUsXNMido;
      string UdYNNJGgGg;
      string dpcpXqgnNL;
      string HDXErVorkg;
      string cTxjsyOLAu;
      string SpDoHeWdUg;
      if(GlIUqIzIMA == TrpBWgRDEz){fYVShQFUVq = true;}
      else if(TrpBWgRDEz == GlIUqIzIMA){LDGkkZnKQX = true;}
      if(ZKWxpVAKHD == eGCSkeNtoN){TOuYEJrrxY = true;}
      else if(eGCSkeNtoN == ZKWxpVAKHD){cHMjsuZWjX = true;}
      if(LYeHbmPaVE == VJkJtpDbZN){bVmRsRAhxM = true;}
      else if(VJkJtpDbZN == LYeHbmPaVE){dRqfgQGEKK = true;}
      if(yAaskbQuSN == bnYOFZWJVk){yLWEBDyeCb = true;}
      else if(bnYOFZWJVk == yAaskbQuSN){KBNXdTPMOz = true;}
      if(HKVdJDVCPb == VAUsXNMido){stoJbDtdkx = true;}
      else if(VAUsXNMido == HKVdJDVCPb){fTJbOKgWrP = true;}
      if(mJxBAhHBrD == UdYNNJGgGg){mdfwEJkDYQ = true;}
      else if(UdYNNJGgGg == mJxBAhHBrD){wzurnsLZDT = true;}
      if(rYmHBYidLO == dpcpXqgnNL){QWXJrIrqXA = true;}
      else if(dpcpXqgnNL == rYmHBYidLO){SjAGMbtoFZ = true;}
      if(FFqtwACByY == HDXErVorkg){LMpVfggdpo = true;}
      if(RNKsRnDYsC == cTxjsyOLAu){WVxAYUeZzq = true;}
      if(TPCPUhXObj == SpDoHeWdUg){StGlKVWfQS = true;}
      while(HDXErVorkg == FFqtwACByY){fMIjrJHPRW = true;}
      while(cTxjsyOLAu == cTxjsyOLAu){ijLtNLFUij = true;}
      while(SpDoHeWdUg == SpDoHeWdUg){IoIugwTDOm = true;}
      if(fYVShQFUVq == true){fYVShQFUVq = false;}
      if(TOuYEJrrxY == true){TOuYEJrrxY = false;}
      if(bVmRsRAhxM == true){bVmRsRAhxM = false;}
      if(yLWEBDyeCb == true){yLWEBDyeCb = false;}
      if(stoJbDtdkx == true){stoJbDtdkx = false;}
      if(mdfwEJkDYQ == true){mdfwEJkDYQ = false;}
      if(QWXJrIrqXA == true){QWXJrIrqXA = false;}
      if(LMpVfggdpo == true){LMpVfggdpo = false;}
      if(WVxAYUeZzq == true){WVxAYUeZzq = false;}
      if(StGlKVWfQS == true){StGlKVWfQS = false;}
      if(LDGkkZnKQX == true){LDGkkZnKQX = false;}
      if(cHMjsuZWjX == true){cHMjsuZWjX = false;}
      if(dRqfgQGEKK == true){dRqfgQGEKK = false;}
      if(KBNXdTPMOz == true){KBNXdTPMOz = false;}
      if(fTJbOKgWrP == true){fTJbOKgWrP = false;}
      if(wzurnsLZDT == true){wzurnsLZDT = false;}
      if(SjAGMbtoFZ == true){SjAGMbtoFZ = false;}
      if(fMIjrJHPRW == true){fMIjrJHPRW = false;}
      if(ijLtNLFUij == true){ijLtNLFUij = false;}
      if(IoIugwTDOm == true){IoIugwTDOm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEEBNXJFOH
{ 
  void zeDDFddwee()
  { 
      bool TNZNGQCjOk = false;
      bool KSdFcquNVP = false;
      bool socQUNsHbm = false;
      bool lTgPQhDEeQ = false;
      bool LDVkOcAYmt = false;
      bool VBiRqekJsr = false;
      bool WtIbzqlNot = false;
      bool mpiFDoTqBq = false;
      bool NUUgRkjOYl = false;
      bool xtLlsQtslW = false;
      bool qlisGeRdNB = false;
      bool KsHBeCYbKN = false;
      bool HWoDwsexMm = false;
      bool tZFeAbkbal = false;
      bool SGBWaDlJGq = false;
      bool qSiXPTwfwM = false;
      bool zUQZHkncAD = false;
      bool QxAXuAURcs = false;
      bool GUpUubqgOf = false;
      bool eEfNmyoaPo = false;
      string iEBqGOAdle;
      string ghVLHcEEsZ;
      string zLXeNjGOrw;
      string KSPUIEtsoI;
      string TYHURkEAXS;
      string ZXUfrWgWcV;
      string IklpTORADC;
      string hKOkFaDDMc;
      string eGqYVlyibk;
      string XXQTAilRAD;
      string SExVjPIiZR;
      string TcJApBtMTh;
      string PhXReKtujW;
      string nlDJJaJVoG;
      string dOJKRtNQcy;
      string oZxSmjfepY;
      string UNzDcgZzpP;
      string rYXMDBYNAj;
      string wdRkgNnkWZ;
      string udePkQPFgj;
      if(iEBqGOAdle == SExVjPIiZR){TNZNGQCjOk = true;}
      else if(SExVjPIiZR == iEBqGOAdle){qlisGeRdNB = true;}
      if(ghVLHcEEsZ == TcJApBtMTh){KSdFcquNVP = true;}
      else if(TcJApBtMTh == ghVLHcEEsZ){KsHBeCYbKN = true;}
      if(zLXeNjGOrw == PhXReKtujW){socQUNsHbm = true;}
      else if(PhXReKtujW == zLXeNjGOrw){HWoDwsexMm = true;}
      if(KSPUIEtsoI == nlDJJaJVoG){lTgPQhDEeQ = true;}
      else if(nlDJJaJVoG == KSPUIEtsoI){tZFeAbkbal = true;}
      if(TYHURkEAXS == dOJKRtNQcy){LDVkOcAYmt = true;}
      else if(dOJKRtNQcy == TYHURkEAXS){SGBWaDlJGq = true;}
      if(ZXUfrWgWcV == oZxSmjfepY){VBiRqekJsr = true;}
      else if(oZxSmjfepY == ZXUfrWgWcV){qSiXPTwfwM = true;}
      if(IklpTORADC == UNzDcgZzpP){WtIbzqlNot = true;}
      else if(UNzDcgZzpP == IklpTORADC){zUQZHkncAD = true;}
      if(hKOkFaDDMc == rYXMDBYNAj){mpiFDoTqBq = true;}
      if(eGqYVlyibk == wdRkgNnkWZ){NUUgRkjOYl = true;}
      if(XXQTAilRAD == udePkQPFgj){xtLlsQtslW = true;}
      while(rYXMDBYNAj == hKOkFaDDMc){QxAXuAURcs = true;}
      while(wdRkgNnkWZ == wdRkgNnkWZ){GUpUubqgOf = true;}
      while(udePkQPFgj == udePkQPFgj){eEfNmyoaPo = true;}
      if(TNZNGQCjOk == true){TNZNGQCjOk = false;}
      if(KSdFcquNVP == true){KSdFcquNVP = false;}
      if(socQUNsHbm == true){socQUNsHbm = false;}
      if(lTgPQhDEeQ == true){lTgPQhDEeQ = false;}
      if(LDVkOcAYmt == true){LDVkOcAYmt = false;}
      if(VBiRqekJsr == true){VBiRqekJsr = false;}
      if(WtIbzqlNot == true){WtIbzqlNot = false;}
      if(mpiFDoTqBq == true){mpiFDoTqBq = false;}
      if(NUUgRkjOYl == true){NUUgRkjOYl = false;}
      if(xtLlsQtslW == true){xtLlsQtslW = false;}
      if(qlisGeRdNB == true){qlisGeRdNB = false;}
      if(KsHBeCYbKN == true){KsHBeCYbKN = false;}
      if(HWoDwsexMm == true){HWoDwsexMm = false;}
      if(tZFeAbkbal == true){tZFeAbkbal = false;}
      if(SGBWaDlJGq == true){SGBWaDlJGq = false;}
      if(qSiXPTwfwM == true){qSiXPTwfwM = false;}
      if(zUQZHkncAD == true){zUQZHkncAD = false;}
      if(QxAXuAURcs == true){QxAXuAURcs = false;}
      if(GUpUubqgOf == true){GUpUubqgOf = false;}
      if(eEfNmyoaPo == true){eEfNmyoaPo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VINYMPXMRU
{ 
  void QeUsrGobjT()
  { 
      bool WIjIdbhfYr = false;
      bool hWwtoYiJbe = false;
      bool eTGZxMFGYE = false;
      bool fiOMiHSmls = false;
      bool TURyzgcIPV = false;
      bool LYlYLDBKLQ = false;
      bool VaGTLzHjKg = false;
      bool GwWiLJBIaP = false;
      bool ixpCsHwoBf = false;
      bool GIbVWrOxlz = false;
      bool YsxhPPBDNB = false;
      bool BriugYkDaE = false;
      bool CShdaxTAMS = false;
      bool uEVappzImd = false;
      bool FsbAeNYfnx = false;
      bool HKWhxGLTHR = false;
      bool uBquFxWIFq = false;
      bool YcQxzIpgzN = false;
      bool YnMOKkhndi = false;
      bool dfAVhECguh = false;
      string ymCYlXdtTm;
      string RmRHuppAHA;
      string jYxjFBHbke;
      string DhRAcySgou;
      string yYghLGMFky;
      string htSEmYpSTj;
      string PCJoijURdw;
      string WJKMBKrOXy;
      string oCqmwJONMD;
      string IANFeuPryb;
      string ltanbYjGCb;
      string gatUuNKWrZ;
      string VHEanVwFgF;
      string uAPwMtaCKX;
      string ZHKkWgGrJQ;
      string jszYFepAAF;
      string ceZxgfKxHB;
      string mILTzNwSDG;
      string PDuQUBAqph;
      string EZCFuuhNEp;
      if(ymCYlXdtTm == ltanbYjGCb){WIjIdbhfYr = true;}
      else if(ltanbYjGCb == ymCYlXdtTm){YsxhPPBDNB = true;}
      if(RmRHuppAHA == gatUuNKWrZ){hWwtoYiJbe = true;}
      else if(gatUuNKWrZ == RmRHuppAHA){BriugYkDaE = true;}
      if(jYxjFBHbke == VHEanVwFgF){eTGZxMFGYE = true;}
      else if(VHEanVwFgF == jYxjFBHbke){CShdaxTAMS = true;}
      if(DhRAcySgou == uAPwMtaCKX){fiOMiHSmls = true;}
      else if(uAPwMtaCKX == DhRAcySgou){uEVappzImd = true;}
      if(yYghLGMFky == ZHKkWgGrJQ){TURyzgcIPV = true;}
      else if(ZHKkWgGrJQ == yYghLGMFky){FsbAeNYfnx = true;}
      if(htSEmYpSTj == jszYFepAAF){LYlYLDBKLQ = true;}
      else if(jszYFepAAF == htSEmYpSTj){HKWhxGLTHR = true;}
      if(PCJoijURdw == ceZxgfKxHB){VaGTLzHjKg = true;}
      else if(ceZxgfKxHB == PCJoijURdw){uBquFxWIFq = true;}
      if(WJKMBKrOXy == mILTzNwSDG){GwWiLJBIaP = true;}
      if(oCqmwJONMD == PDuQUBAqph){ixpCsHwoBf = true;}
      if(IANFeuPryb == EZCFuuhNEp){GIbVWrOxlz = true;}
      while(mILTzNwSDG == WJKMBKrOXy){YcQxzIpgzN = true;}
      while(PDuQUBAqph == PDuQUBAqph){YnMOKkhndi = true;}
      while(EZCFuuhNEp == EZCFuuhNEp){dfAVhECguh = true;}
      if(WIjIdbhfYr == true){WIjIdbhfYr = false;}
      if(hWwtoYiJbe == true){hWwtoYiJbe = false;}
      if(eTGZxMFGYE == true){eTGZxMFGYE = false;}
      if(fiOMiHSmls == true){fiOMiHSmls = false;}
      if(TURyzgcIPV == true){TURyzgcIPV = false;}
      if(LYlYLDBKLQ == true){LYlYLDBKLQ = false;}
      if(VaGTLzHjKg == true){VaGTLzHjKg = false;}
      if(GwWiLJBIaP == true){GwWiLJBIaP = false;}
      if(ixpCsHwoBf == true){ixpCsHwoBf = false;}
      if(GIbVWrOxlz == true){GIbVWrOxlz = false;}
      if(YsxhPPBDNB == true){YsxhPPBDNB = false;}
      if(BriugYkDaE == true){BriugYkDaE = false;}
      if(CShdaxTAMS == true){CShdaxTAMS = false;}
      if(uEVappzImd == true){uEVappzImd = false;}
      if(FsbAeNYfnx == true){FsbAeNYfnx = false;}
      if(HKWhxGLTHR == true){HKWhxGLTHR = false;}
      if(uBquFxWIFq == true){uBquFxWIFq = false;}
      if(YcQxzIpgzN == true){YcQxzIpgzN = false;}
      if(YnMOKkhndi == true){YnMOKkhndi = false;}
      if(dfAVhECguh == true){dfAVhECguh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LNBBTVZTCP
{ 
  void ktfmqlClDD()
  { 
      bool mSrWUCIdeH = false;
      bool ANqqAkBRGK = false;
      bool PXyhtybtpd = false;
      bool oLSSXzqfbc = false;
      bool hsphGTupIL = false;
      bool nVFINOUKbV = false;
      bool aOnBRntYSB = false;
      bool tVpdcVhQba = false;
      bool DlkepSGKEJ = false;
      bool dgEGCSEnPR = false;
      bool ZVWGRSfbfr = false;
      bool gDhBRocJLz = false;
      bool hiTJWMRiaJ = false;
      bool RtBKBgOdNX = false;
      bool ldeMbazCnN = false;
      bool pubQipCNjE = false;
      bool AxAWZmCXAj = false;
      bool ZywnMEEHgw = false;
      bool NOuNSWRkaK = false;
      bool eBtIWodIlo = false;
      string mDXjPQgLgb;
      string KJwmZYeIUb;
      string lyIPgVfJKT;
      string NGGShndHBB;
      string dskaVBiFen;
      string LNkbwouHCt;
      string kXBNODCcFk;
      string uXHSxsMgsf;
      string lZdVHAVdWr;
      string sVEGQFqXMS;
      string yFAtsnFReC;
      string bNOWIKsfFN;
      string gYGMqZSBCr;
      string BoUaggZjcS;
      string tDzTQfHhyF;
      string LLRzkZzmCS;
      string VEOlAmsnob;
      string kJDmTdYlwL;
      string SjCxfpXVoH;
      string glgJxonMSd;
      if(mDXjPQgLgb == yFAtsnFReC){mSrWUCIdeH = true;}
      else if(yFAtsnFReC == mDXjPQgLgb){ZVWGRSfbfr = true;}
      if(KJwmZYeIUb == bNOWIKsfFN){ANqqAkBRGK = true;}
      else if(bNOWIKsfFN == KJwmZYeIUb){gDhBRocJLz = true;}
      if(lyIPgVfJKT == gYGMqZSBCr){PXyhtybtpd = true;}
      else if(gYGMqZSBCr == lyIPgVfJKT){hiTJWMRiaJ = true;}
      if(NGGShndHBB == BoUaggZjcS){oLSSXzqfbc = true;}
      else if(BoUaggZjcS == NGGShndHBB){RtBKBgOdNX = true;}
      if(dskaVBiFen == tDzTQfHhyF){hsphGTupIL = true;}
      else if(tDzTQfHhyF == dskaVBiFen){ldeMbazCnN = true;}
      if(LNkbwouHCt == LLRzkZzmCS){nVFINOUKbV = true;}
      else if(LLRzkZzmCS == LNkbwouHCt){pubQipCNjE = true;}
      if(kXBNODCcFk == VEOlAmsnob){aOnBRntYSB = true;}
      else if(VEOlAmsnob == kXBNODCcFk){AxAWZmCXAj = true;}
      if(uXHSxsMgsf == kJDmTdYlwL){tVpdcVhQba = true;}
      if(lZdVHAVdWr == SjCxfpXVoH){DlkepSGKEJ = true;}
      if(sVEGQFqXMS == glgJxonMSd){dgEGCSEnPR = true;}
      while(kJDmTdYlwL == uXHSxsMgsf){ZywnMEEHgw = true;}
      while(SjCxfpXVoH == SjCxfpXVoH){NOuNSWRkaK = true;}
      while(glgJxonMSd == glgJxonMSd){eBtIWodIlo = true;}
      if(mSrWUCIdeH == true){mSrWUCIdeH = false;}
      if(ANqqAkBRGK == true){ANqqAkBRGK = false;}
      if(PXyhtybtpd == true){PXyhtybtpd = false;}
      if(oLSSXzqfbc == true){oLSSXzqfbc = false;}
      if(hsphGTupIL == true){hsphGTupIL = false;}
      if(nVFINOUKbV == true){nVFINOUKbV = false;}
      if(aOnBRntYSB == true){aOnBRntYSB = false;}
      if(tVpdcVhQba == true){tVpdcVhQba = false;}
      if(DlkepSGKEJ == true){DlkepSGKEJ = false;}
      if(dgEGCSEnPR == true){dgEGCSEnPR = false;}
      if(ZVWGRSfbfr == true){ZVWGRSfbfr = false;}
      if(gDhBRocJLz == true){gDhBRocJLz = false;}
      if(hiTJWMRiaJ == true){hiTJWMRiaJ = false;}
      if(RtBKBgOdNX == true){RtBKBgOdNX = false;}
      if(ldeMbazCnN == true){ldeMbazCnN = false;}
      if(pubQipCNjE == true){pubQipCNjE = false;}
      if(AxAWZmCXAj == true){AxAWZmCXAj = false;}
      if(ZywnMEEHgw == true){ZywnMEEHgw = false;}
      if(NOuNSWRkaK == true){NOuNSWRkaK = false;}
      if(eBtIWodIlo == true){eBtIWodIlo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALPRHYMCDB
{ 
  void Ebdynfuhej()
  { 
      bool hDpPUXKTSR = false;
      bool FTSMOmTQAX = false;
      bool xRbFtfUuyb = false;
      bool HogpNXWmgI = false;
      bool gMcItrzLqw = false;
      bool pfoPmPbjUo = false;
      bool DPVpKPmbzp = false;
      bool PfjrqkoSLC = false;
      bool gJDBlaAQDx = false;
      bool wmRqFRqlxe = false;
      bool EXLAfJwxYB = false;
      bool aIYSItLTEj = false;
      bool PVYCtcOrmZ = false;
      bool tCVgyIxDVb = false;
      bool dDrBWmOziK = false;
      bool FWhNOhzJFD = false;
      bool uEKyHYmqUz = false;
      bool wIybFMcWeG = false;
      bool OOIbTWTHRP = false;
      bool JnxRgZrssy = false;
      string mkoioOsiJd;
      string SeqJDaCDnq;
      string cawCSTEkWA;
      string ftYxoApFzn;
      string ATaWPsFGDG;
      string HBoVbMolQU;
      string JHMJyYFsTD;
      string jxEApJzZmY;
      string NygQrdECVb;
      string LEnddrGRYp;
      string nMlAVJxofS;
      string MPzqHKauQT;
      string TCXqqfJZVy;
      string ChAwkAMgui;
      string gPWDPwFwWT;
      string RKBEVkntIo;
      string AWSgPeOCGG;
      string ysAglEeUbu;
      string aMDCgqgwaA;
      string MRYFiJxpmk;
      if(mkoioOsiJd == nMlAVJxofS){hDpPUXKTSR = true;}
      else if(nMlAVJxofS == mkoioOsiJd){EXLAfJwxYB = true;}
      if(SeqJDaCDnq == MPzqHKauQT){FTSMOmTQAX = true;}
      else if(MPzqHKauQT == SeqJDaCDnq){aIYSItLTEj = true;}
      if(cawCSTEkWA == TCXqqfJZVy){xRbFtfUuyb = true;}
      else if(TCXqqfJZVy == cawCSTEkWA){PVYCtcOrmZ = true;}
      if(ftYxoApFzn == ChAwkAMgui){HogpNXWmgI = true;}
      else if(ChAwkAMgui == ftYxoApFzn){tCVgyIxDVb = true;}
      if(ATaWPsFGDG == gPWDPwFwWT){gMcItrzLqw = true;}
      else if(gPWDPwFwWT == ATaWPsFGDG){dDrBWmOziK = true;}
      if(HBoVbMolQU == RKBEVkntIo){pfoPmPbjUo = true;}
      else if(RKBEVkntIo == HBoVbMolQU){FWhNOhzJFD = true;}
      if(JHMJyYFsTD == AWSgPeOCGG){DPVpKPmbzp = true;}
      else if(AWSgPeOCGG == JHMJyYFsTD){uEKyHYmqUz = true;}
      if(jxEApJzZmY == ysAglEeUbu){PfjrqkoSLC = true;}
      if(NygQrdECVb == aMDCgqgwaA){gJDBlaAQDx = true;}
      if(LEnddrGRYp == MRYFiJxpmk){wmRqFRqlxe = true;}
      while(ysAglEeUbu == jxEApJzZmY){wIybFMcWeG = true;}
      while(aMDCgqgwaA == aMDCgqgwaA){OOIbTWTHRP = true;}
      while(MRYFiJxpmk == MRYFiJxpmk){JnxRgZrssy = true;}
      if(hDpPUXKTSR == true){hDpPUXKTSR = false;}
      if(FTSMOmTQAX == true){FTSMOmTQAX = false;}
      if(xRbFtfUuyb == true){xRbFtfUuyb = false;}
      if(HogpNXWmgI == true){HogpNXWmgI = false;}
      if(gMcItrzLqw == true){gMcItrzLqw = false;}
      if(pfoPmPbjUo == true){pfoPmPbjUo = false;}
      if(DPVpKPmbzp == true){DPVpKPmbzp = false;}
      if(PfjrqkoSLC == true){PfjrqkoSLC = false;}
      if(gJDBlaAQDx == true){gJDBlaAQDx = false;}
      if(wmRqFRqlxe == true){wmRqFRqlxe = false;}
      if(EXLAfJwxYB == true){EXLAfJwxYB = false;}
      if(aIYSItLTEj == true){aIYSItLTEj = false;}
      if(PVYCtcOrmZ == true){PVYCtcOrmZ = false;}
      if(tCVgyIxDVb == true){tCVgyIxDVb = false;}
      if(dDrBWmOziK == true){dDrBWmOziK = false;}
      if(FWhNOhzJFD == true){FWhNOhzJFD = false;}
      if(uEKyHYmqUz == true){uEKyHYmqUz = false;}
      if(wIybFMcWeG == true){wIybFMcWeG = false;}
      if(OOIbTWTHRP == true){OOIbTWTHRP = false;}
      if(JnxRgZrssy == true){JnxRgZrssy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVMYOVMRVM
{ 
  void ltaWkjjQIB()
  { 
      bool JCwjwmWNGC = false;
      bool XKXPdgcFim = false;
      bool LxZsBehTWU = false;
      bool pYgCxtkqsX = false;
      bool bwOtRzByRC = false;
      bool EaUVELbCiQ = false;
      bool FDqkLydUSi = false;
      bool wlLLKPifbB = false;
      bool ciCTPPELxk = false;
      bool ShHbRYEciS = false;
      bool VgfhGSPIKo = false;
      bool cuagmVBWUw = false;
      bool tRXgQNdjsl = false;
      bool KFxJfwDTNx = false;
      bool zuAIIWHZnw = false;
      bool WgHmXDJzQr = false;
      bool nfOXdXyRBq = false;
      bool SgJXwyROYt = false;
      bool GEuxOcxKkb = false;
      bool mDCVJTgbdj = false;
      string XDRsrhmRyc;
      string WCAnLtGRRH;
      string sOceFdAKJR;
      string aLnzuBFqdE;
      string thIAjojnRm;
      string qOyBhIamnN;
      string hbIgBLNBrK;
      string oPmNMKGctQ;
      string sLsVaMMmRm;
      string ZRCPWSZayY;
      string aiuHybaknW;
      string BxsXUVimGn;
      string yaiEjWMWpt;
      string keeVoJQlXz;
      string laytlcYeuB;
      string jlUJZAzpWb;
      string OEttlVSWhK;
      string EwPGCXcoSH;
      string xgaoKyKVwo;
      string JZOujhgDIP;
      if(XDRsrhmRyc == aiuHybaknW){JCwjwmWNGC = true;}
      else if(aiuHybaknW == XDRsrhmRyc){VgfhGSPIKo = true;}
      if(WCAnLtGRRH == BxsXUVimGn){XKXPdgcFim = true;}
      else if(BxsXUVimGn == WCAnLtGRRH){cuagmVBWUw = true;}
      if(sOceFdAKJR == yaiEjWMWpt){LxZsBehTWU = true;}
      else if(yaiEjWMWpt == sOceFdAKJR){tRXgQNdjsl = true;}
      if(aLnzuBFqdE == keeVoJQlXz){pYgCxtkqsX = true;}
      else if(keeVoJQlXz == aLnzuBFqdE){KFxJfwDTNx = true;}
      if(thIAjojnRm == laytlcYeuB){bwOtRzByRC = true;}
      else if(laytlcYeuB == thIAjojnRm){zuAIIWHZnw = true;}
      if(qOyBhIamnN == jlUJZAzpWb){EaUVELbCiQ = true;}
      else if(jlUJZAzpWb == qOyBhIamnN){WgHmXDJzQr = true;}
      if(hbIgBLNBrK == OEttlVSWhK){FDqkLydUSi = true;}
      else if(OEttlVSWhK == hbIgBLNBrK){nfOXdXyRBq = true;}
      if(oPmNMKGctQ == EwPGCXcoSH){wlLLKPifbB = true;}
      if(sLsVaMMmRm == xgaoKyKVwo){ciCTPPELxk = true;}
      if(ZRCPWSZayY == JZOujhgDIP){ShHbRYEciS = true;}
      while(EwPGCXcoSH == oPmNMKGctQ){SgJXwyROYt = true;}
      while(xgaoKyKVwo == xgaoKyKVwo){GEuxOcxKkb = true;}
      while(JZOujhgDIP == JZOujhgDIP){mDCVJTgbdj = true;}
      if(JCwjwmWNGC == true){JCwjwmWNGC = false;}
      if(XKXPdgcFim == true){XKXPdgcFim = false;}
      if(LxZsBehTWU == true){LxZsBehTWU = false;}
      if(pYgCxtkqsX == true){pYgCxtkqsX = false;}
      if(bwOtRzByRC == true){bwOtRzByRC = false;}
      if(EaUVELbCiQ == true){EaUVELbCiQ = false;}
      if(FDqkLydUSi == true){FDqkLydUSi = false;}
      if(wlLLKPifbB == true){wlLLKPifbB = false;}
      if(ciCTPPELxk == true){ciCTPPELxk = false;}
      if(ShHbRYEciS == true){ShHbRYEciS = false;}
      if(VgfhGSPIKo == true){VgfhGSPIKo = false;}
      if(cuagmVBWUw == true){cuagmVBWUw = false;}
      if(tRXgQNdjsl == true){tRXgQNdjsl = false;}
      if(KFxJfwDTNx == true){KFxJfwDTNx = false;}
      if(zuAIIWHZnw == true){zuAIIWHZnw = false;}
      if(WgHmXDJzQr == true){WgHmXDJzQr = false;}
      if(nfOXdXyRBq == true){nfOXdXyRBq = false;}
      if(SgJXwyROYt == true){SgJXwyROYt = false;}
      if(GEuxOcxKkb == true){GEuxOcxKkb = false;}
      if(mDCVJTgbdj == true){mDCVJTgbdj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBGALWWOPM
{ 
  void TpwFzDhRwb()
  { 
      bool hKUQCLkiol = false;
      bool MYLTcdxGuP = false;
      bool DRmAfPwsnN = false;
      bool urNSaLWNfb = false;
      bool ZKnChzBkaN = false;
      bool bBktgQWUjm = false;
      bool OquaqULssQ = false;
      bool GjZSprcjSf = false;
      bool NKSZlsGTkJ = false;
      bool nCcsNhPMLN = false;
      bool nIrJGrbSDn = false;
      bool mlCEYEYUoy = false;
      bool NrHicEGgFH = false;
      bool cQYEqFSITs = false;
      bool RnPxWBAYTI = false;
      bool JtXMzwAIgC = false;
      bool kuNuLWNxMT = false;
      bool kPBugZbKMa = false;
      bool DhMwyirMFu = false;
      bool EJbQIWZTkA = false;
      string wwJzuwOAQW;
      string UUTwdqdrbe;
      string eTQZRuKfib;
      string BNhETLhawY;
      string fAzoALUehU;
      string hXIiyceihA;
      string lhQnUHmOcS;
      string JCuCzdUbZF;
      string aeyOtdEzGp;
      string fysumxjKTs;
      string YFBPKfbFjU;
      string HCJbZGjBtp;
      string CmIllLJzPB;
      string sKHffUchDO;
      string CyOkhdnQVf;
      string NiPdpkwPcz;
      string WbpiaxucuE;
      string cBxfnDYXDI;
      string WrdinKtdou;
      string YNFDrZIfJj;
      if(wwJzuwOAQW == YFBPKfbFjU){hKUQCLkiol = true;}
      else if(YFBPKfbFjU == wwJzuwOAQW){nIrJGrbSDn = true;}
      if(UUTwdqdrbe == HCJbZGjBtp){MYLTcdxGuP = true;}
      else if(HCJbZGjBtp == UUTwdqdrbe){mlCEYEYUoy = true;}
      if(eTQZRuKfib == CmIllLJzPB){DRmAfPwsnN = true;}
      else if(CmIllLJzPB == eTQZRuKfib){NrHicEGgFH = true;}
      if(BNhETLhawY == sKHffUchDO){urNSaLWNfb = true;}
      else if(sKHffUchDO == BNhETLhawY){cQYEqFSITs = true;}
      if(fAzoALUehU == CyOkhdnQVf){ZKnChzBkaN = true;}
      else if(CyOkhdnQVf == fAzoALUehU){RnPxWBAYTI = true;}
      if(hXIiyceihA == NiPdpkwPcz){bBktgQWUjm = true;}
      else if(NiPdpkwPcz == hXIiyceihA){JtXMzwAIgC = true;}
      if(lhQnUHmOcS == WbpiaxucuE){OquaqULssQ = true;}
      else if(WbpiaxucuE == lhQnUHmOcS){kuNuLWNxMT = true;}
      if(JCuCzdUbZF == cBxfnDYXDI){GjZSprcjSf = true;}
      if(aeyOtdEzGp == WrdinKtdou){NKSZlsGTkJ = true;}
      if(fysumxjKTs == YNFDrZIfJj){nCcsNhPMLN = true;}
      while(cBxfnDYXDI == JCuCzdUbZF){kPBugZbKMa = true;}
      while(WrdinKtdou == WrdinKtdou){DhMwyirMFu = true;}
      while(YNFDrZIfJj == YNFDrZIfJj){EJbQIWZTkA = true;}
      if(hKUQCLkiol == true){hKUQCLkiol = false;}
      if(MYLTcdxGuP == true){MYLTcdxGuP = false;}
      if(DRmAfPwsnN == true){DRmAfPwsnN = false;}
      if(urNSaLWNfb == true){urNSaLWNfb = false;}
      if(ZKnChzBkaN == true){ZKnChzBkaN = false;}
      if(bBktgQWUjm == true){bBktgQWUjm = false;}
      if(OquaqULssQ == true){OquaqULssQ = false;}
      if(GjZSprcjSf == true){GjZSprcjSf = false;}
      if(NKSZlsGTkJ == true){NKSZlsGTkJ = false;}
      if(nCcsNhPMLN == true){nCcsNhPMLN = false;}
      if(nIrJGrbSDn == true){nIrJGrbSDn = false;}
      if(mlCEYEYUoy == true){mlCEYEYUoy = false;}
      if(NrHicEGgFH == true){NrHicEGgFH = false;}
      if(cQYEqFSITs == true){cQYEqFSITs = false;}
      if(RnPxWBAYTI == true){RnPxWBAYTI = false;}
      if(JtXMzwAIgC == true){JtXMzwAIgC = false;}
      if(kuNuLWNxMT == true){kuNuLWNxMT = false;}
      if(kPBugZbKMa == true){kPBugZbKMa = false;}
      if(DhMwyirMFu == true){DhMwyirMFu = false;}
      if(EJbQIWZTkA == true){EJbQIWZTkA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HGLGIKGMMZ
{ 
  void FWEOzioVsr()
  { 
      bool XaxnTqSPeW = false;
      bool RMKqIuETVY = false;
      bool RzttjaUCTW = false;
      bool mLGXsbrGrc = false;
      bool GnVJciqnTZ = false;
      bool WeWMAYgCDs = false;
      bool WQuHjGGmyg = false;
      bool DybsSdcjQB = false;
      bool ifhtAHotWT = false;
      bool uoCzGorNYW = false;
      bool cDplWYDcsW = false;
      bool wwkCJphBHb = false;
      bool RLQekNubld = false;
      bool kOKtYfpwXa = false;
      bool DLAAXzDApQ = false;
      bool GqGxFQmKBI = false;
      bool daqPlgkqcc = false;
      bool zldfXFLPGl = false;
      bool JtlVWsINnH = false;
      bool setOxcTjNq = false;
      string LLYtQgMQWl;
      string hIzJGcFncI;
      string fXzlKzQgrH;
      string WtiQJOFfUr;
      string NpOSRiPgrm;
      string ngZxLnLljR;
      string PfXOOnYhAr;
      string WYSktoIgUb;
      string ijoEToUlFU;
      string CSwDbhRzDc;
      string JhgzPOOnCV;
      string fdRIhfpTtZ;
      string SmbepDcPIM;
      string XIdqRBDonF;
      string afijoXBnUw;
      string ryEdKVFBJL;
      string kzfpyWzapg;
      string cAeoymErpR;
      string CotLTYEAgu;
      string wCfcUbzrkS;
      if(LLYtQgMQWl == JhgzPOOnCV){XaxnTqSPeW = true;}
      else if(JhgzPOOnCV == LLYtQgMQWl){cDplWYDcsW = true;}
      if(hIzJGcFncI == fdRIhfpTtZ){RMKqIuETVY = true;}
      else if(fdRIhfpTtZ == hIzJGcFncI){wwkCJphBHb = true;}
      if(fXzlKzQgrH == SmbepDcPIM){RzttjaUCTW = true;}
      else if(SmbepDcPIM == fXzlKzQgrH){RLQekNubld = true;}
      if(WtiQJOFfUr == XIdqRBDonF){mLGXsbrGrc = true;}
      else if(XIdqRBDonF == WtiQJOFfUr){kOKtYfpwXa = true;}
      if(NpOSRiPgrm == afijoXBnUw){GnVJciqnTZ = true;}
      else if(afijoXBnUw == NpOSRiPgrm){DLAAXzDApQ = true;}
      if(ngZxLnLljR == ryEdKVFBJL){WeWMAYgCDs = true;}
      else if(ryEdKVFBJL == ngZxLnLljR){GqGxFQmKBI = true;}
      if(PfXOOnYhAr == kzfpyWzapg){WQuHjGGmyg = true;}
      else if(kzfpyWzapg == PfXOOnYhAr){daqPlgkqcc = true;}
      if(WYSktoIgUb == cAeoymErpR){DybsSdcjQB = true;}
      if(ijoEToUlFU == CotLTYEAgu){ifhtAHotWT = true;}
      if(CSwDbhRzDc == wCfcUbzrkS){uoCzGorNYW = true;}
      while(cAeoymErpR == WYSktoIgUb){zldfXFLPGl = true;}
      while(CotLTYEAgu == CotLTYEAgu){JtlVWsINnH = true;}
      while(wCfcUbzrkS == wCfcUbzrkS){setOxcTjNq = true;}
      if(XaxnTqSPeW == true){XaxnTqSPeW = false;}
      if(RMKqIuETVY == true){RMKqIuETVY = false;}
      if(RzttjaUCTW == true){RzttjaUCTW = false;}
      if(mLGXsbrGrc == true){mLGXsbrGrc = false;}
      if(GnVJciqnTZ == true){GnVJciqnTZ = false;}
      if(WeWMAYgCDs == true){WeWMAYgCDs = false;}
      if(WQuHjGGmyg == true){WQuHjGGmyg = false;}
      if(DybsSdcjQB == true){DybsSdcjQB = false;}
      if(ifhtAHotWT == true){ifhtAHotWT = false;}
      if(uoCzGorNYW == true){uoCzGorNYW = false;}
      if(cDplWYDcsW == true){cDplWYDcsW = false;}
      if(wwkCJphBHb == true){wwkCJphBHb = false;}
      if(RLQekNubld == true){RLQekNubld = false;}
      if(kOKtYfpwXa == true){kOKtYfpwXa = false;}
      if(DLAAXzDApQ == true){DLAAXzDApQ = false;}
      if(GqGxFQmKBI == true){GqGxFQmKBI = false;}
      if(daqPlgkqcc == true){daqPlgkqcc = false;}
      if(zldfXFLPGl == true){zldfXFLPGl = false;}
      if(JtlVWsINnH == true){JtlVWsINnH = false;}
      if(setOxcTjNq == true){setOxcTjNq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFQMFYSBIX
{ 
  void kUYNbJLdiZ()
  { 
      bool iGkrCuSOWh = false;
      bool NjVQcRIoYn = false;
      bool GGfKEtfckE = false;
      bool stRJWkJVEZ = false;
      bool ZhjiSAZchg = false;
      bool HQATFbZZnI = false;
      bool OpdSnSSLsq = false;
      bool ImjyOXVxrD = false;
      bool TDtEwbtxEt = false;
      bool KihwLjERtz = false;
      bool hNiqYUgCEh = false;
      bool FchjnKuYVL = false;
      bool YUHzfYEnle = false;
      bool TECrUFTDfb = false;
      bool urrVnhBxHB = false;
      bool newhaNGjLz = false;
      bool PrPZOBZpPh = false;
      bool prssQgbkKx = false;
      bool XGgkqnHURG = false;
      bool zjqfLCbSHl = false;
      string YbxkuFPSVA;
      string aiRPoRZqAw;
      string QdNUwlEhDf;
      string lYqdLYZWbZ;
      string tpkNmMOjpH;
      string lgXmHtNboI;
      string AhOoNCqmEP;
      string rDOaCaszhi;
      string WUqutFADWR;
      string LxgSYLauAj;
      string UafaPiRxjg;
      string BNtFkfpTuI;
      string CmQmDuVuBp;
      string zxzxOwoQfL;
      string mCTpPxCbgs;
      string UGzrghKrWU;
      string MWwtgDOwqo;
      string pZnjUzTZWG;
      string rtNHUrxHQf;
      string kwsKyQGYIM;
      if(YbxkuFPSVA == UafaPiRxjg){iGkrCuSOWh = true;}
      else if(UafaPiRxjg == YbxkuFPSVA){hNiqYUgCEh = true;}
      if(aiRPoRZqAw == BNtFkfpTuI){NjVQcRIoYn = true;}
      else if(BNtFkfpTuI == aiRPoRZqAw){FchjnKuYVL = true;}
      if(QdNUwlEhDf == CmQmDuVuBp){GGfKEtfckE = true;}
      else if(CmQmDuVuBp == QdNUwlEhDf){YUHzfYEnle = true;}
      if(lYqdLYZWbZ == zxzxOwoQfL){stRJWkJVEZ = true;}
      else if(zxzxOwoQfL == lYqdLYZWbZ){TECrUFTDfb = true;}
      if(tpkNmMOjpH == mCTpPxCbgs){ZhjiSAZchg = true;}
      else if(mCTpPxCbgs == tpkNmMOjpH){urrVnhBxHB = true;}
      if(lgXmHtNboI == UGzrghKrWU){HQATFbZZnI = true;}
      else if(UGzrghKrWU == lgXmHtNboI){newhaNGjLz = true;}
      if(AhOoNCqmEP == MWwtgDOwqo){OpdSnSSLsq = true;}
      else if(MWwtgDOwqo == AhOoNCqmEP){PrPZOBZpPh = true;}
      if(rDOaCaszhi == pZnjUzTZWG){ImjyOXVxrD = true;}
      if(WUqutFADWR == rtNHUrxHQf){TDtEwbtxEt = true;}
      if(LxgSYLauAj == kwsKyQGYIM){KihwLjERtz = true;}
      while(pZnjUzTZWG == rDOaCaszhi){prssQgbkKx = true;}
      while(rtNHUrxHQf == rtNHUrxHQf){XGgkqnHURG = true;}
      while(kwsKyQGYIM == kwsKyQGYIM){zjqfLCbSHl = true;}
      if(iGkrCuSOWh == true){iGkrCuSOWh = false;}
      if(NjVQcRIoYn == true){NjVQcRIoYn = false;}
      if(GGfKEtfckE == true){GGfKEtfckE = false;}
      if(stRJWkJVEZ == true){stRJWkJVEZ = false;}
      if(ZhjiSAZchg == true){ZhjiSAZchg = false;}
      if(HQATFbZZnI == true){HQATFbZZnI = false;}
      if(OpdSnSSLsq == true){OpdSnSSLsq = false;}
      if(ImjyOXVxrD == true){ImjyOXVxrD = false;}
      if(TDtEwbtxEt == true){TDtEwbtxEt = false;}
      if(KihwLjERtz == true){KihwLjERtz = false;}
      if(hNiqYUgCEh == true){hNiqYUgCEh = false;}
      if(FchjnKuYVL == true){FchjnKuYVL = false;}
      if(YUHzfYEnle == true){YUHzfYEnle = false;}
      if(TECrUFTDfb == true){TECrUFTDfb = false;}
      if(urrVnhBxHB == true){urrVnhBxHB = false;}
      if(newhaNGjLz == true){newhaNGjLz = false;}
      if(PrPZOBZpPh == true){PrPZOBZpPh = false;}
      if(prssQgbkKx == true){prssQgbkKx = false;}
      if(XGgkqnHURG == true){XGgkqnHURG = false;}
      if(zjqfLCbSHl == true){zjqfLCbSHl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OAZDHTWCMD
{ 
  void NxCyPfRYhg()
  { 
      bool YtqXCKJxby = false;
      bool UfhTGSwxiJ = false;
      bool jEaTsKmYgW = false;
      bool ESzMVXdUxU = false;
      bool KzdbekEmGz = false;
      bool MhwTRUTXdq = false;
      bool WjPFtBgUyh = false;
      bool obzOyjayoH = false;
      bool GAShJVWfuB = false;
      bool EGpGxaiXhc = false;
      bool EinXJjigUg = false;
      bool tUhWkWQguX = false;
      bool eAZwdilsRX = false;
      bool BCPLCXLuYY = false;
      bool moLNHiXTUZ = false;
      bool JBbKxDJrsa = false;
      bool yoPwfqFWTN = false;
      bool KVIWkpoLou = false;
      bool LRXqOzZFOz = false;
      bool OTBxaxYOhP = false;
      string HHuwxmdSFU;
      string mpCnTlrWWL;
      string oihhercxZY;
      string aBCVhhSOap;
      string EJkgezYzfE;
      string xLbHXYZMRF;
      string KgrgskmgFl;
      string ScwfHfyBCe;
      string ScQVaOYtyI;
      string HFxUfWQDmt;
      string LrttkTPwAr;
      string aYJllgQVGe;
      string LsiwdNfazk;
      string OtNISaiWjG;
      string ybtFhiuKhz;
      string FuxIhSJxPX;
      string noxOcfKBTK;
      string xtlzfiycOu;
      string RUrzeTwFaz;
      string RlGMRJefcB;
      if(HHuwxmdSFU == LrttkTPwAr){YtqXCKJxby = true;}
      else if(LrttkTPwAr == HHuwxmdSFU){EinXJjigUg = true;}
      if(mpCnTlrWWL == aYJllgQVGe){UfhTGSwxiJ = true;}
      else if(aYJllgQVGe == mpCnTlrWWL){tUhWkWQguX = true;}
      if(oihhercxZY == LsiwdNfazk){jEaTsKmYgW = true;}
      else if(LsiwdNfazk == oihhercxZY){eAZwdilsRX = true;}
      if(aBCVhhSOap == OtNISaiWjG){ESzMVXdUxU = true;}
      else if(OtNISaiWjG == aBCVhhSOap){BCPLCXLuYY = true;}
      if(EJkgezYzfE == ybtFhiuKhz){KzdbekEmGz = true;}
      else if(ybtFhiuKhz == EJkgezYzfE){moLNHiXTUZ = true;}
      if(xLbHXYZMRF == FuxIhSJxPX){MhwTRUTXdq = true;}
      else if(FuxIhSJxPX == xLbHXYZMRF){JBbKxDJrsa = true;}
      if(KgrgskmgFl == noxOcfKBTK){WjPFtBgUyh = true;}
      else if(noxOcfKBTK == KgrgskmgFl){yoPwfqFWTN = true;}
      if(ScwfHfyBCe == xtlzfiycOu){obzOyjayoH = true;}
      if(ScQVaOYtyI == RUrzeTwFaz){GAShJVWfuB = true;}
      if(HFxUfWQDmt == RlGMRJefcB){EGpGxaiXhc = true;}
      while(xtlzfiycOu == ScwfHfyBCe){KVIWkpoLou = true;}
      while(RUrzeTwFaz == RUrzeTwFaz){LRXqOzZFOz = true;}
      while(RlGMRJefcB == RlGMRJefcB){OTBxaxYOhP = true;}
      if(YtqXCKJxby == true){YtqXCKJxby = false;}
      if(UfhTGSwxiJ == true){UfhTGSwxiJ = false;}
      if(jEaTsKmYgW == true){jEaTsKmYgW = false;}
      if(ESzMVXdUxU == true){ESzMVXdUxU = false;}
      if(KzdbekEmGz == true){KzdbekEmGz = false;}
      if(MhwTRUTXdq == true){MhwTRUTXdq = false;}
      if(WjPFtBgUyh == true){WjPFtBgUyh = false;}
      if(obzOyjayoH == true){obzOyjayoH = false;}
      if(GAShJVWfuB == true){GAShJVWfuB = false;}
      if(EGpGxaiXhc == true){EGpGxaiXhc = false;}
      if(EinXJjigUg == true){EinXJjigUg = false;}
      if(tUhWkWQguX == true){tUhWkWQguX = false;}
      if(eAZwdilsRX == true){eAZwdilsRX = false;}
      if(BCPLCXLuYY == true){BCPLCXLuYY = false;}
      if(moLNHiXTUZ == true){moLNHiXTUZ = false;}
      if(JBbKxDJrsa == true){JBbKxDJrsa = false;}
      if(yoPwfqFWTN == true){yoPwfqFWTN = false;}
      if(KVIWkpoLou == true){KVIWkpoLou = false;}
      if(LRXqOzZFOz == true){LRXqOzZFOz = false;}
      if(OTBxaxYOhP == true){OTBxaxYOhP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITZZNGEXIK
{ 
  void gFUEGttFQi()
  { 
      bool buUPgbWhhw = false;
      bool znKnXlpboZ = false;
      bool nARcPejJGi = false;
      bool pzkIyCsIPW = false;
      bool jVRoDoORuz = false;
      bool oWlYXbdrAB = false;
      bool qNazFADCoV = false;
      bool sgLRpShcYa = false;
      bool QSOHtSMLjW = false;
      bool YBIOfVtSiD = false;
      bool kLcZGHKThF = false;
      bool tBSYjXyTFm = false;
      bool mqSRwqXxkT = false;
      bool XOsVoFpoAl = false;
      bool HrdecXiidH = false;
      bool WaNwPtsKcP = false;
      bool iNiNgeHwje = false;
      bool hJSSeuNmoX = false;
      bool IoScxxBxGu = false;
      bool LfLkCtJPyx = false;
      string uxyXQneboY;
      string DdalxmrkyS;
      string XkAETZRhyB;
      string aOTmlURPxT;
      string ZwxBkaeGuo;
      string tjlyQKwsDq;
      string WxcnxnKnAb;
      string UcnesanzTs;
      string tLmJGpcUVa;
      string YXLFxbTIDw;
      string PqFSTRwGFo;
      string WwZJwKKSgH;
      string LpRYDxQhhQ;
      string HewWcDFUpn;
      string sWPgEbyBJl;
      string RAbwkZYfOW;
      string BOXngqADgs;
      string FpcsNoZkUa;
      string yOYwzHDAkD;
      string dZFTleyazM;
      if(uxyXQneboY == PqFSTRwGFo){buUPgbWhhw = true;}
      else if(PqFSTRwGFo == uxyXQneboY){kLcZGHKThF = true;}
      if(DdalxmrkyS == WwZJwKKSgH){znKnXlpboZ = true;}
      else if(WwZJwKKSgH == DdalxmrkyS){tBSYjXyTFm = true;}
      if(XkAETZRhyB == LpRYDxQhhQ){nARcPejJGi = true;}
      else if(LpRYDxQhhQ == XkAETZRhyB){mqSRwqXxkT = true;}
      if(aOTmlURPxT == HewWcDFUpn){pzkIyCsIPW = true;}
      else if(HewWcDFUpn == aOTmlURPxT){XOsVoFpoAl = true;}
      if(ZwxBkaeGuo == sWPgEbyBJl){jVRoDoORuz = true;}
      else if(sWPgEbyBJl == ZwxBkaeGuo){HrdecXiidH = true;}
      if(tjlyQKwsDq == RAbwkZYfOW){oWlYXbdrAB = true;}
      else if(RAbwkZYfOW == tjlyQKwsDq){WaNwPtsKcP = true;}
      if(WxcnxnKnAb == BOXngqADgs){qNazFADCoV = true;}
      else if(BOXngqADgs == WxcnxnKnAb){iNiNgeHwje = true;}
      if(UcnesanzTs == FpcsNoZkUa){sgLRpShcYa = true;}
      if(tLmJGpcUVa == yOYwzHDAkD){QSOHtSMLjW = true;}
      if(YXLFxbTIDw == dZFTleyazM){YBIOfVtSiD = true;}
      while(FpcsNoZkUa == UcnesanzTs){hJSSeuNmoX = true;}
      while(yOYwzHDAkD == yOYwzHDAkD){IoScxxBxGu = true;}
      while(dZFTleyazM == dZFTleyazM){LfLkCtJPyx = true;}
      if(buUPgbWhhw == true){buUPgbWhhw = false;}
      if(znKnXlpboZ == true){znKnXlpboZ = false;}
      if(nARcPejJGi == true){nARcPejJGi = false;}
      if(pzkIyCsIPW == true){pzkIyCsIPW = false;}
      if(jVRoDoORuz == true){jVRoDoORuz = false;}
      if(oWlYXbdrAB == true){oWlYXbdrAB = false;}
      if(qNazFADCoV == true){qNazFADCoV = false;}
      if(sgLRpShcYa == true){sgLRpShcYa = false;}
      if(QSOHtSMLjW == true){QSOHtSMLjW = false;}
      if(YBIOfVtSiD == true){YBIOfVtSiD = false;}
      if(kLcZGHKThF == true){kLcZGHKThF = false;}
      if(tBSYjXyTFm == true){tBSYjXyTFm = false;}
      if(mqSRwqXxkT == true){mqSRwqXxkT = false;}
      if(XOsVoFpoAl == true){XOsVoFpoAl = false;}
      if(HrdecXiidH == true){HrdecXiidH = false;}
      if(WaNwPtsKcP == true){WaNwPtsKcP = false;}
      if(iNiNgeHwje == true){iNiNgeHwje = false;}
      if(hJSSeuNmoX == true){hJSSeuNmoX = false;}
      if(IoScxxBxGu == true){IoScxxBxGu = false;}
      if(LfLkCtJPyx == true){LfLkCtJPyx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBVJXRSYSE
{ 
  void MseICTLopm()
  { 
      bool bJdeJHnAqq = false;
      bool PSkcQlRCuy = false;
      bool fQMhImqbnt = false;
      bool kuLqWNJpUM = false;
      bool BMwMiFkARu = false;
      bool EmVNMKxwVW = false;
      bool PLMwGUGtFC = false;
      bool cahhwSTzzD = false;
      bool BpKroyZxdM = false;
      bool QMUxxozzGN = false;
      bool yptOScEmQt = false;
      bool pyxRUYBUGH = false;
      bool uIQslPGjkH = false;
      bool SUrkFLwwZM = false;
      bool slgjVSPCcX = false;
      bool neryRoZBcC = false;
      bool WTCJaVFLLJ = false;
      bool cFutNJbgWT = false;
      bool ADHNSnbsSQ = false;
      bool ktTWoZiXIA = false;
      string PkjEHFPBmi;
      string ArgZQEoKWp;
      string yzKHBnTcJa;
      string gzGfiGrWYF;
      string pZNiSFNiQz;
      string rEwMCQacDT;
      string kmrMBBkBpJ;
      string MSkRAXlbou;
      string ZjMJhbCsdS;
      string eOTETChAgR;
      string TMsGlZTeMd;
      string eznHsAZhdY;
      string yrWXeyzfxx;
      string pkuWaMqFWI;
      string IXfAmfZLLS;
      string bzWHSboUbn;
      string amgPntEQgf;
      string JUKVQaLWjy;
      string XnUdUpNmEz;
      string XVdihVpQLs;
      if(PkjEHFPBmi == TMsGlZTeMd){bJdeJHnAqq = true;}
      else if(TMsGlZTeMd == PkjEHFPBmi){yptOScEmQt = true;}
      if(ArgZQEoKWp == eznHsAZhdY){PSkcQlRCuy = true;}
      else if(eznHsAZhdY == ArgZQEoKWp){pyxRUYBUGH = true;}
      if(yzKHBnTcJa == yrWXeyzfxx){fQMhImqbnt = true;}
      else if(yrWXeyzfxx == yzKHBnTcJa){uIQslPGjkH = true;}
      if(gzGfiGrWYF == pkuWaMqFWI){kuLqWNJpUM = true;}
      else if(pkuWaMqFWI == gzGfiGrWYF){SUrkFLwwZM = true;}
      if(pZNiSFNiQz == IXfAmfZLLS){BMwMiFkARu = true;}
      else if(IXfAmfZLLS == pZNiSFNiQz){slgjVSPCcX = true;}
      if(rEwMCQacDT == bzWHSboUbn){EmVNMKxwVW = true;}
      else if(bzWHSboUbn == rEwMCQacDT){neryRoZBcC = true;}
      if(kmrMBBkBpJ == amgPntEQgf){PLMwGUGtFC = true;}
      else if(amgPntEQgf == kmrMBBkBpJ){WTCJaVFLLJ = true;}
      if(MSkRAXlbou == JUKVQaLWjy){cahhwSTzzD = true;}
      if(ZjMJhbCsdS == XnUdUpNmEz){BpKroyZxdM = true;}
      if(eOTETChAgR == XVdihVpQLs){QMUxxozzGN = true;}
      while(JUKVQaLWjy == MSkRAXlbou){cFutNJbgWT = true;}
      while(XnUdUpNmEz == XnUdUpNmEz){ADHNSnbsSQ = true;}
      while(XVdihVpQLs == XVdihVpQLs){ktTWoZiXIA = true;}
      if(bJdeJHnAqq == true){bJdeJHnAqq = false;}
      if(PSkcQlRCuy == true){PSkcQlRCuy = false;}
      if(fQMhImqbnt == true){fQMhImqbnt = false;}
      if(kuLqWNJpUM == true){kuLqWNJpUM = false;}
      if(BMwMiFkARu == true){BMwMiFkARu = false;}
      if(EmVNMKxwVW == true){EmVNMKxwVW = false;}
      if(PLMwGUGtFC == true){PLMwGUGtFC = false;}
      if(cahhwSTzzD == true){cahhwSTzzD = false;}
      if(BpKroyZxdM == true){BpKroyZxdM = false;}
      if(QMUxxozzGN == true){QMUxxozzGN = false;}
      if(yptOScEmQt == true){yptOScEmQt = false;}
      if(pyxRUYBUGH == true){pyxRUYBUGH = false;}
      if(uIQslPGjkH == true){uIQslPGjkH = false;}
      if(SUrkFLwwZM == true){SUrkFLwwZM = false;}
      if(slgjVSPCcX == true){slgjVSPCcX = false;}
      if(neryRoZBcC == true){neryRoZBcC = false;}
      if(WTCJaVFLLJ == true){WTCJaVFLLJ = false;}
      if(cFutNJbgWT == true){cFutNJbgWT = false;}
      if(ADHNSnbsSQ == true){ADHNSnbsSQ = false;}
      if(ktTWoZiXIA == true){ktTWoZiXIA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HNXRPNVPDX
{ 
  void ProwsKoVcT()
  { 
      bool DnxaqmlZoG = false;
      bool WdiathHOOd = false;
      bool YCISiLJUhQ = false;
      bool GoYxbWdZAF = false;
      bool auyXZCMEhu = false;
      bool UAoluAeere = false;
      bool dRqYzhElzX = false;
      bool EgOJCcEkrg = false;
      bool zFlmwGzlCb = false;
      bool qzhVbJEYXq = false;
      bool xaFKqmkfiR = false;
      bool wtlKeXeEbs = false;
      bool hRiXfFzsgr = false;
      bool YeMAjYAawJ = false;
      bool UTCkexMWpD = false;
      bool ezxeIeqgel = false;
      bool mrypsQhkaG = false;
      bool XDISXOPyri = false;
      bool rcCcNYhhqE = false;
      bool gSwJVcULrO = false;
      string aAOTqudlIw;
      string RukSgpmbmd;
      string nZGyEQKgbT;
      string hKyuTAjGep;
      string CacZZUEfNz;
      string fxrGBAtQOa;
      string kwJnNHxpyf;
      string GgwwbNxgXj;
      string MeTcmkRqtS;
      string GTqEFFQnLR;
      string WNggszAwem;
      string DMrdNGcgBc;
      string pGufZlorpV;
      string wIVFNyxmin;
      string jUMGOtaNpz;
      string cimhbQSBHG;
      string KIFIpupmPO;
      string IoxMrVsoRf;
      string LbBqsMVmdx;
      string fwfcdbOEPT;
      if(aAOTqudlIw == WNggszAwem){DnxaqmlZoG = true;}
      else if(WNggszAwem == aAOTqudlIw){xaFKqmkfiR = true;}
      if(RukSgpmbmd == DMrdNGcgBc){WdiathHOOd = true;}
      else if(DMrdNGcgBc == RukSgpmbmd){wtlKeXeEbs = true;}
      if(nZGyEQKgbT == pGufZlorpV){YCISiLJUhQ = true;}
      else if(pGufZlorpV == nZGyEQKgbT){hRiXfFzsgr = true;}
      if(hKyuTAjGep == wIVFNyxmin){GoYxbWdZAF = true;}
      else if(wIVFNyxmin == hKyuTAjGep){YeMAjYAawJ = true;}
      if(CacZZUEfNz == jUMGOtaNpz){auyXZCMEhu = true;}
      else if(jUMGOtaNpz == CacZZUEfNz){UTCkexMWpD = true;}
      if(fxrGBAtQOa == cimhbQSBHG){UAoluAeere = true;}
      else if(cimhbQSBHG == fxrGBAtQOa){ezxeIeqgel = true;}
      if(kwJnNHxpyf == KIFIpupmPO){dRqYzhElzX = true;}
      else if(KIFIpupmPO == kwJnNHxpyf){mrypsQhkaG = true;}
      if(GgwwbNxgXj == IoxMrVsoRf){EgOJCcEkrg = true;}
      if(MeTcmkRqtS == LbBqsMVmdx){zFlmwGzlCb = true;}
      if(GTqEFFQnLR == fwfcdbOEPT){qzhVbJEYXq = true;}
      while(IoxMrVsoRf == GgwwbNxgXj){XDISXOPyri = true;}
      while(LbBqsMVmdx == LbBqsMVmdx){rcCcNYhhqE = true;}
      while(fwfcdbOEPT == fwfcdbOEPT){gSwJVcULrO = true;}
      if(DnxaqmlZoG == true){DnxaqmlZoG = false;}
      if(WdiathHOOd == true){WdiathHOOd = false;}
      if(YCISiLJUhQ == true){YCISiLJUhQ = false;}
      if(GoYxbWdZAF == true){GoYxbWdZAF = false;}
      if(auyXZCMEhu == true){auyXZCMEhu = false;}
      if(UAoluAeere == true){UAoluAeere = false;}
      if(dRqYzhElzX == true){dRqYzhElzX = false;}
      if(EgOJCcEkrg == true){EgOJCcEkrg = false;}
      if(zFlmwGzlCb == true){zFlmwGzlCb = false;}
      if(qzhVbJEYXq == true){qzhVbJEYXq = false;}
      if(xaFKqmkfiR == true){xaFKqmkfiR = false;}
      if(wtlKeXeEbs == true){wtlKeXeEbs = false;}
      if(hRiXfFzsgr == true){hRiXfFzsgr = false;}
      if(YeMAjYAawJ == true){YeMAjYAawJ = false;}
      if(UTCkexMWpD == true){UTCkexMWpD = false;}
      if(ezxeIeqgel == true){ezxeIeqgel = false;}
      if(mrypsQhkaG == true){mrypsQhkaG = false;}
      if(XDISXOPyri == true){XDISXOPyri = false;}
      if(rcCcNYhhqE == true){rcCcNYhhqE = false;}
      if(gSwJVcULrO == true){gSwJVcULrO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PENWVVTIDD
{ 
  void HRoJrHzRxb()
  { 
      bool HrreFIaaHs = false;
      bool AGutwCycWa = false;
      bool MMmyqwSdch = false;
      bool kfkVtBNXGe = false;
      bool TgHgjtlfFf = false;
      bool XUaVWuFsnJ = false;
      bool owyYHTVZzu = false;
      bool naVqGfFGOx = false;
      bool JmYxKPFOyz = false;
      bool wUjxoXhhYP = false;
      bool XMfKqxziPp = false;
      bool ozepACXBOq = false;
      bool OHaAzTqXCi = false;
      bool xWgyYxGNFN = false;
      bool QVzHJxosxm = false;
      bool zgSgAPkfLW = false;
      bool FagfrRRgRC = false;
      bool uJuBasISpB = false;
      bool dyaOiQEAxJ = false;
      bool LaCiHpnSPq = false;
      string zMxdWlkoRq;
      string wGoplqUBrs;
      string XEomuJgOih;
      string LCLyNLbKTA;
      string mmWVpMemIC;
      string AKdEIuXKiM;
      string FVFiestpcZ;
      string PJhqFjgSxh;
      string dsFfhBYHpS;
      string nRbGuQgmpw;
      string RnKimpclyX;
      string NENAhLPZBc;
      string UmAJlxhawn;
      string CsbAQphWrq;
      string XmISEjEbXi;
      string BHlMaenAwp;
      string IBoKVUbMjr;
      string csgKFhdhFC;
      string sGDMmtHOZk;
      string BgZChWxywj;
      if(zMxdWlkoRq == RnKimpclyX){HrreFIaaHs = true;}
      else if(RnKimpclyX == zMxdWlkoRq){XMfKqxziPp = true;}
      if(wGoplqUBrs == NENAhLPZBc){AGutwCycWa = true;}
      else if(NENAhLPZBc == wGoplqUBrs){ozepACXBOq = true;}
      if(XEomuJgOih == UmAJlxhawn){MMmyqwSdch = true;}
      else if(UmAJlxhawn == XEomuJgOih){OHaAzTqXCi = true;}
      if(LCLyNLbKTA == CsbAQphWrq){kfkVtBNXGe = true;}
      else if(CsbAQphWrq == LCLyNLbKTA){xWgyYxGNFN = true;}
      if(mmWVpMemIC == XmISEjEbXi){TgHgjtlfFf = true;}
      else if(XmISEjEbXi == mmWVpMemIC){QVzHJxosxm = true;}
      if(AKdEIuXKiM == BHlMaenAwp){XUaVWuFsnJ = true;}
      else if(BHlMaenAwp == AKdEIuXKiM){zgSgAPkfLW = true;}
      if(FVFiestpcZ == IBoKVUbMjr){owyYHTVZzu = true;}
      else if(IBoKVUbMjr == FVFiestpcZ){FagfrRRgRC = true;}
      if(PJhqFjgSxh == csgKFhdhFC){naVqGfFGOx = true;}
      if(dsFfhBYHpS == sGDMmtHOZk){JmYxKPFOyz = true;}
      if(nRbGuQgmpw == BgZChWxywj){wUjxoXhhYP = true;}
      while(csgKFhdhFC == PJhqFjgSxh){uJuBasISpB = true;}
      while(sGDMmtHOZk == sGDMmtHOZk){dyaOiQEAxJ = true;}
      while(BgZChWxywj == BgZChWxywj){LaCiHpnSPq = true;}
      if(HrreFIaaHs == true){HrreFIaaHs = false;}
      if(AGutwCycWa == true){AGutwCycWa = false;}
      if(MMmyqwSdch == true){MMmyqwSdch = false;}
      if(kfkVtBNXGe == true){kfkVtBNXGe = false;}
      if(TgHgjtlfFf == true){TgHgjtlfFf = false;}
      if(XUaVWuFsnJ == true){XUaVWuFsnJ = false;}
      if(owyYHTVZzu == true){owyYHTVZzu = false;}
      if(naVqGfFGOx == true){naVqGfFGOx = false;}
      if(JmYxKPFOyz == true){JmYxKPFOyz = false;}
      if(wUjxoXhhYP == true){wUjxoXhhYP = false;}
      if(XMfKqxziPp == true){XMfKqxziPp = false;}
      if(ozepACXBOq == true){ozepACXBOq = false;}
      if(OHaAzTqXCi == true){OHaAzTqXCi = false;}
      if(xWgyYxGNFN == true){xWgyYxGNFN = false;}
      if(QVzHJxosxm == true){QVzHJxosxm = false;}
      if(zgSgAPkfLW == true){zgSgAPkfLW = false;}
      if(FagfrRRgRC == true){FagfrRRgRC = false;}
      if(uJuBasISpB == true){uJuBasISpB = false;}
      if(dyaOiQEAxJ == true){dyaOiQEAxJ = false;}
      if(LaCiHpnSPq == true){LaCiHpnSPq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQFGXHAJVA
{ 
  void KFIhNhAKmj()
  { 
      bool rbkDhnPhoh = false;
      bool TuKJmwLcPz = false;
      bool esfPYgrMgO = false;
      bool WbmLONxpwj = false;
      bool JoEGxfhHZh = false;
      bool sHuzmywUdA = false;
      bool uCBaLrIzuY = false;
      bool yUgfoooZRr = false;
      bool zkmzVOfmXQ = false;
      bool RbMwnHnduF = false;
      bool XhLBiXaOKy = false;
      bool JWDkAJPBEw = false;
      bool LUaeGWIjqg = false;
      bool AKdMUQZkPx = false;
      bool nRcZGuYaue = false;
      bool rmYytCHgtM = false;
      bool OpXcxyrqQi = false;
      bool jdlGHtrBXL = false;
      bool ygoMoNkfRR = false;
      bool JrqDhyszbI = false;
      string GJuXaQeluW;
      string HcwfSrLmlg;
      string HDYgEPrAKm;
      string dagYrIIoZm;
      string UiWgRnOZOB;
      string zPrWMCjNTL;
      string YdaHrfwWnK;
      string iVMzMXgrOP;
      string BRlJmNiJMp;
      string XuVONpHOnl;
      string rqlDRdDrKn;
      string UryEKGrRUe;
      string xlKymnzykV;
      string PRDcWJfhqI;
      string KpzXUfxREH;
      string yptJnGgnQd;
      string dFGnYCnUgB;
      string ZJaLTGmlcG;
      string phsdXZXtnQ;
      string brQNdEjKzR;
      if(GJuXaQeluW == rqlDRdDrKn){rbkDhnPhoh = true;}
      else if(rqlDRdDrKn == GJuXaQeluW){XhLBiXaOKy = true;}
      if(HcwfSrLmlg == UryEKGrRUe){TuKJmwLcPz = true;}
      else if(UryEKGrRUe == HcwfSrLmlg){JWDkAJPBEw = true;}
      if(HDYgEPrAKm == xlKymnzykV){esfPYgrMgO = true;}
      else if(xlKymnzykV == HDYgEPrAKm){LUaeGWIjqg = true;}
      if(dagYrIIoZm == PRDcWJfhqI){WbmLONxpwj = true;}
      else if(PRDcWJfhqI == dagYrIIoZm){AKdMUQZkPx = true;}
      if(UiWgRnOZOB == KpzXUfxREH){JoEGxfhHZh = true;}
      else if(KpzXUfxREH == UiWgRnOZOB){nRcZGuYaue = true;}
      if(zPrWMCjNTL == yptJnGgnQd){sHuzmywUdA = true;}
      else if(yptJnGgnQd == zPrWMCjNTL){rmYytCHgtM = true;}
      if(YdaHrfwWnK == dFGnYCnUgB){uCBaLrIzuY = true;}
      else if(dFGnYCnUgB == YdaHrfwWnK){OpXcxyrqQi = true;}
      if(iVMzMXgrOP == ZJaLTGmlcG){yUgfoooZRr = true;}
      if(BRlJmNiJMp == phsdXZXtnQ){zkmzVOfmXQ = true;}
      if(XuVONpHOnl == brQNdEjKzR){RbMwnHnduF = true;}
      while(ZJaLTGmlcG == iVMzMXgrOP){jdlGHtrBXL = true;}
      while(phsdXZXtnQ == phsdXZXtnQ){ygoMoNkfRR = true;}
      while(brQNdEjKzR == brQNdEjKzR){JrqDhyszbI = true;}
      if(rbkDhnPhoh == true){rbkDhnPhoh = false;}
      if(TuKJmwLcPz == true){TuKJmwLcPz = false;}
      if(esfPYgrMgO == true){esfPYgrMgO = false;}
      if(WbmLONxpwj == true){WbmLONxpwj = false;}
      if(JoEGxfhHZh == true){JoEGxfhHZh = false;}
      if(sHuzmywUdA == true){sHuzmywUdA = false;}
      if(uCBaLrIzuY == true){uCBaLrIzuY = false;}
      if(yUgfoooZRr == true){yUgfoooZRr = false;}
      if(zkmzVOfmXQ == true){zkmzVOfmXQ = false;}
      if(RbMwnHnduF == true){RbMwnHnduF = false;}
      if(XhLBiXaOKy == true){XhLBiXaOKy = false;}
      if(JWDkAJPBEw == true){JWDkAJPBEw = false;}
      if(LUaeGWIjqg == true){LUaeGWIjqg = false;}
      if(AKdMUQZkPx == true){AKdMUQZkPx = false;}
      if(nRcZGuYaue == true){nRcZGuYaue = false;}
      if(rmYytCHgtM == true){rmYytCHgtM = false;}
      if(OpXcxyrqQi == true){OpXcxyrqQi = false;}
      if(jdlGHtrBXL == true){jdlGHtrBXL = false;}
      if(ygoMoNkfRR == true){ygoMoNkfRR = false;}
      if(JrqDhyszbI == true){JrqDhyszbI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRZTIIBYLW
{ 
  void KLRqHBRkwC()
  { 
      bool MpzNqmFDCI = false;
      bool PwQLwyQmMe = false;
      bool DjQcqpbmZb = false;
      bool BirUrwhHKm = false;
      bool TyDjzSKXPN = false;
      bool SsjVTcYVVA = false;
      bool KScZHgDuSz = false;
      bool PJcZKEfgcY = false;
      bool fEWMJIzVBP = false;
      bool XLkJbBVccS = false;
      bool OOEPxJPKKO = false;
      bool wrsxTFuQQy = false;
      bool ghtDbEXTxJ = false;
      bool iDEKJRzGOA = false;
      bool roKlSeSmoW = false;
      bool FEMdkgTBns = false;
      bool kwMBfsminC = false;
      bool GoBPGrWIjw = false;
      bool kjdaEdqaYb = false;
      bool yxSVOwbJGY = false;
      string IelharFjsf;
      string OyiYNIyImb;
      string nBAHBUfUWU;
      string xmmxfrZdlU;
      string tLqgYZaUuF;
      string YyRrKGddgF;
      string LkMYhaLlsV;
      string iUVSgcJTia;
      string tLYRuzVtmY;
      string NuwfIJySyx;
      string OobYWDbzKh;
      string wKuFLALtci;
      string FQyTImYoJX;
      string dqUkMFiAuq;
      string WVjFbCAqTI;
      string yEoOrxpIQi;
      string elolEFoJrG;
      string RLylMigsqF;
      string mgVBZYCFsP;
      string OaiLLjgxBW;
      if(IelharFjsf == OobYWDbzKh){MpzNqmFDCI = true;}
      else if(OobYWDbzKh == IelharFjsf){OOEPxJPKKO = true;}
      if(OyiYNIyImb == wKuFLALtci){PwQLwyQmMe = true;}
      else if(wKuFLALtci == OyiYNIyImb){wrsxTFuQQy = true;}
      if(nBAHBUfUWU == FQyTImYoJX){DjQcqpbmZb = true;}
      else if(FQyTImYoJX == nBAHBUfUWU){ghtDbEXTxJ = true;}
      if(xmmxfrZdlU == dqUkMFiAuq){BirUrwhHKm = true;}
      else if(dqUkMFiAuq == xmmxfrZdlU){iDEKJRzGOA = true;}
      if(tLqgYZaUuF == WVjFbCAqTI){TyDjzSKXPN = true;}
      else if(WVjFbCAqTI == tLqgYZaUuF){roKlSeSmoW = true;}
      if(YyRrKGddgF == yEoOrxpIQi){SsjVTcYVVA = true;}
      else if(yEoOrxpIQi == YyRrKGddgF){FEMdkgTBns = true;}
      if(LkMYhaLlsV == elolEFoJrG){KScZHgDuSz = true;}
      else if(elolEFoJrG == LkMYhaLlsV){kwMBfsminC = true;}
      if(iUVSgcJTia == RLylMigsqF){PJcZKEfgcY = true;}
      if(tLYRuzVtmY == mgVBZYCFsP){fEWMJIzVBP = true;}
      if(NuwfIJySyx == OaiLLjgxBW){XLkJbBVccS = true;}
      while(RLylMigsqF == iUVSgcJTia){GoBPGrWIjw = true;}
      while(mgVBZYCFsP == mgVBZYCFsP){kjdaEdqaYb = true;}
      while(OaiLLjgxBW == OaiLLjgxBW){yxSVOwbJGY = true;}
      if(MpzNqmFDCI == true){MpzNqmFDCI = false;}
      if(PwQLwyQmMe == true){PwQLwyQmMe = false;}
      if(DjQcqpbmZb == true){DjQcqpbmZb = false;}
      if(BirUrwhHKm == true){BirUrwhHKm = false;}
      if(TyDjzSKXPN == true){TyDjzSKXPN = false;}
      if(SsjVTcYVVA == true){SsjVTcYVVA = false;}
      if(KScZHgDuSz == true){KScZHgDuSz = false;}
      if(PJcZKEfgcY == true){PJcZKEfgcY = false;}
      if(fEWMJIzVBP == true){fEWMJIzVBP = false;}
      if(XLkJbBVccS == true){XLkJbBVccS = false;}
      if(OOEPxJPKKO == true){OOEPxJPKKO = false;}
      if(wrsxTFuQQy == true){wrsxTFuQQy = false;}
      if(ghtDbEXTxJ == true){ghtDbEXTxJ = false;}
      if(iDEKJRzGOA == true){iDEKJRzGOA = false;}
      if(roKlSeSmoW == true){roKlSeSmoW = false;}
      if(FEMdkgTBns == true){FEMdkgTBns = false;}
      if(kwMBfsminC == true){kwMBfsminC = false;}
      if(GoBPGrWIjw == true){GoBPGrWIjw = false;}
      if(kjdaEdqaYb == true){kjdaEdqaYb = false;}
      if(yxSVOwbJGY == true){yxSVOwbJGY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGLOJUJLZJ
{ 
  void lgWVdFfaMw()
  { 
      bool uztKLtaihl = false;
      bool FXlNxUsfQq = false;
      bool xchzQpTgfc = false;
      bool RdsdBGklqh = false;
      bool KYEMpchBTr = false;
      bool CzPqWSQtsU = false;
      bool asDETbdHLp = false;
      bool iHohgYXVIn = false;
      bool HSNmaSNCGi = false;
      bool oqsVGQUzrO = false;
      bool yZocJuJgKy = false;
      bool ttlFNIfPdA = false;
      bool NbAcArOSbQ = false;
      bool DXdtogcjde = false;
      bool JgqInuEmIx = false;
      bool jFVqAWZLbR = false;
      bool gqFstWQqPf = false;
      bool eulzqgjroF = false;
      bool maKdgyClsS = false;
      bool HRIMyRbyNQ = false;
      string rUqjrzhSPz;
      string RTqFVWmeiV;
      string gmwAQdPjla;
      string kmMyRsmRJW;
      string gaWgXFjytZ;
      string qjTnwEYqTN;
      string ixfoNdGrmb;
      string iUUMoGQObK;
      string sRpLiBTXCN;
      string UwywnjtgTs;
      string yqKRqVOGyo;
      string nKPITRGTFL;
      string KipYHmVYYF;
      string LithMCGYUN;
      string lMYMZKgpbV;
      string cZbHiPBlKD;
      string AphscEPgwR;
      string KhyrZxJczw;
      string GfwCckHmyw;
      string AUORMwefiU;
      if(rUqjrzhSPz == yqKRqVOGyo){uztKLtaihl = true;}
      else if(yqKRqVOGyo == rUqjrzhSPz){yZocJuJgKy = true;}
      if(RTqFVWmeiV == nKPITRGTFL){FXlNxUsfQq = true;}
      else if(nKPITRGTFL == RTqFVWmeiV){ttlFNIfPdA = true;}
      if(gmwAQdPjla == KipYHmVYYF){xchzQpTgfc = true;}
      else if(KipYHmVYYF == gmwAQdPjla){NbAcArOSbQ = true;}
      if(kmMyRsmRJW == LithMCGYUN){RdsdBGklqh = true;}
      else if(LithMCGYUN == kmMyRsmRJW){DXdtogcjde = true;}
      if(gaWgXFjytZ == lMYMZKgpbV){KYEMpchBTr = true;}
      else if(lMYMZKgpbV == gaWgXFjytZ){JgqInuEmIx = true;}
      if(qjTnwEYqTN == cZbHiPBlKD){CzPqWSQtsU = true;}
      else if(cZbHiPBlKD == qjTnwEYqTN){jFVqAWZLbR = true;}
      if(ixfoNdGrmb == AphscEPgwR){asDETbdHLp = true;}
      else if(AphscEPgwR == ixfoNdGrmb){gqFstWQqPf = true;}
      if(iUUMoGQObK == KhyrZxJczw){iHohgYXVIn = true;}
      if(sRpLiBTXCN == GfwCckHmyw){HSNmaSNCGi = true;}
      if(UwywnjtgTs == AUORMwefiU){oqsVGQUzrO = true;}
      while(KhyrZxJczw == iUUMoGQObK){eulzqgjroF = true;}
      while(GfwCckHmyw == GfwCckHmyw){maKdgyClsS = true;}
      while(AUORMwefiU == AUORMwefiU){HRIMyRbyNQ = true;}
      if(uztKLtaihl == true){uztKLtaihl = false;}
      if(FXlNxUsfQq == true){FXlNxUsfQq = false;}
      if(xchzQpTgfc == true){xchzQpTgfc = false;}
      if(RdsdBGklqh == true){RdsdBGklqh = false;}
      if(KYEMpchBTr == true){KYEMpchBTr = false;}
      if(CzPqWSQtsU == true){CzPqWSQtsU = false;}
      if(asDETbdHLp == true){asDETbdHLp = false;}
      if(iHohgYXVIn == true){iHohgYXVIn = false;}
      if(HSNmaSNCGi == true){HSNmaSNCGi = false;}
      if(oqsVGQUzrO == true){oqsVGQUzrO = false;}
      if(yZocJuJgKy == true){yZocJuJgKy = false;}
      if(ttlFNIfPdA == true){ttlFNIfPdA = false;}
      if(NbAcArOSbQ == true){NbAcArOSbQ = false;}
      if(DXdtogcjde == true){DXdtogcjde = false;}
      if(JgqInuEmIx == true){JgqInuEmIx = false;}
      if(jFVqAWZLbR == true){jFVqAWZLbR = false;}
      if(gqFstWQqPf == true){gqFstWQqPf = false;}
      if(eulzqgjroF == true){eulzqgjroF = false;}
      if(maKdgyClsS == true){maKdgyClsS = false;}
      if(HRIMyRbyNQ == true){HRIMyRbyNQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGAYDYOFTH
{ 
  void OnxrjXPqhJ()
  { 
      bool mDojoslZya = false;
      bool IplPJqWkAy = false;
      bool ojjHYULdrk = false;
      bool wpVhJySoaB = false;
      bool uRGIzyuWfW = false;
      bool ZUZjpDThLT = false;
      bool gHhNeSUEGL = false;
      bool XhJzCXcaHZ = false;
      bool YoyULaPkqG = false;
      bool dkcGTnisdf = false;
      bool dqQUyqLagS = false;
      bool ZrZlurJNBD = false;
      bool DiNzgmFDeO = false;
      bool ojxbwgXcVT = false;
      bool PoDXflLqKa = false;
      bool dUqactdQmL = false;
      bool lHuSdpuxpN = false;
      bool TfrgmNfoSu = false;
      bool bNrDjTrWzB = false;
      bool DHoJhHtktp = false;
      string tHqxLPtJpu;
      string hTTnBNKRDM;
      string zQnLENXGBy;
      string FIYRwWjuuT;
      string fjrwLIPRSO;
      string ZqsRjdSfsx;
      string qmHqoYuBrd;
      string dOVjgPYrzu;
      string yGnlXOPHhR;
      string DECxbrbAGl;
      string NNYnkLUIjT;
      string FafxzjzVSa;
      string JmSZaZMXHn;
      string nYkMhkgABM;
      string sGWOMcXEyr;
      string sGgfcZuzNL;
      string ywAwfgoTPO;
      string CzTGhCQENx;
      string BHYPuhrFiI;
      string ohmpOwFahf;
      if(tHqxLPtJpu == NNYnkLUIjT){mDojoslZya = true;}
      else if(NNYnkLUIjT == tHqxLPtJpu){dqQUyqLagS = true;}
      if(hTTnBNKRDM == FafxzjzVSa){IplPJqWkAy = true;}
      else if(FafxzjzVSa == hTTnBNKRDM){ZrZlurJNBD = true;}
      if(zQnLENXGBy == JmSZaZMXHn){ojjHYULdrk = true;}
      else if(JmSZaZMXHn == zQnLENXGBy){DiNzgmFDeO = true;}
      if(FIYRwWjuuT == nYkMhkgABM){wpVhJySoaB = true;}
      else if(nYkMhkgABM == FIYRwWjuuT){ojxbwgXcVT = true;}
      if(fjrwLIPRSO == sGWOMcXEyr){uRGIzyuWfW = true;}
      else if(sGWOMcXEyr == fjrwLIPRSO){PoDXflLqKa = true;}
      if(ZqsRjdSfsx == sGgfcZuzNL){ZUZjpDThLT = true;}
      else if(sGgfcZuzNL == ZqsRjdSfsx){dUqactdQmL = true;}
      if(qmHqoYuBrd == ywAwfgoTPO){gHhNeSUEGL = true;}
      else if(ywAwfgoTPO == qmHqoYuBrd){lHuSdpuxpN = true;}
      if(dOVjgPYrzu == CzTGhCQENx){XhJzCXcaHZ = true;}
      if(yGnlXOPHhR == BHYPuhrFiI){YoyULaPkqG = true;}
      if(DECxbrbAGl == ohmpOwFahf){dkcGTnisdf = true;}
      while(CzTGhCQENx == dOVjgPYrzu){TfrgmNfoSu = true;}
      while(BHYPuhrFiI == BHYPuhrFiI){bNrDjTrWzB = true;}
      while(ohmpOwFahf == ohmpOwFahf){DHoJhHtktp = true;}
      if(mDojoslZya == true){mDojoslZya = false;}
      if(IplPJqWkAy == true){IplPJqWkAy = false;}
      if(ojjHYULdrk == true){ojjHYULdrk = false;}
      if(wpVhJySoaB == true){wpVhJySoaB = false;}
      if(uRGIzyuWfW == true){uRGIzyuWfW = false;}
      if(ZUZjpDThLT == true){ZUZjpDThLT = false;}
      if(gHhNeSUEGL == true){gHhNeSUEGL = false;}
      if(XhJzCXcaHZ == true){XhJzCXcaHZ = false;}
      if(YoyULaPkqG == true){YoyULaPkqG = false;}
      if(dkcGTnisdf == true){dkcGTnisdf = false;}
      if(dqQUyqLagS == true){dqQUyqLagS = false;}
      if(ZrZlurJNBD == true){ZrZlurJNBD = false;}
      if(DiNzgmFDeO == true){DiNzgmFDeO = false;}
      if(ojxbwgXcVT == true){ojxbwgXcVT = false;}
      if(PoDXflLqKa == true){PoDXflLqKa = false;}
      if(dUqactdQmL == true){dUqactdQmL = false;}
      if(lHuSdpuxpN == true){lHuSdpuxpN = false;}
      if(TfrgmNfoSu == true){TfrgmNfoSu = false;}
      if(bNrDjTrWzB == true){bNrDjTrWzB = false;}
      if(DHoJhHtktp == true){DHoJhHtktp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KZRERRDAWI
{ 
  void DdokChsnqj()
  { 
      bool lcSJjGPDLw = false;
      bool nunPQikrDF = false;
      bool xrbLIUbzuL = false;
      bool nRZDBaORHG = false;
      bool MGKWZTAUdI = false;
      bool DOXedsBGBO = false;
      bool eQHAHVVjOo = false;
      bool TSjxsphElo = false;
      bool UHUlIYstYH = false;
      bool YHQrbuzKPD = false;
      bool xPFonjeZlm = false;
      bool LwUMtWwUqh = false;
      bool caLGPMCqVx = false;
      bool qWohqFBfyY = false;
      bool tSIkwclDyE = false;
      bool zdTgaWEzYb = false;
      bool gmEownGmVo = false;
      bool VPWRnJSZJm = false;
      bool ZysQxMDIHT = false;
      bool BCGVqGNSoI = false;
      string TTTjBUpnQo;
      string hUcpfgWFFF;
      string yXaXFDTJQV;
      string VfrNmrZnWK;
      string CqifgsyhdD;
      string XBRBawswdx;
      string AgWuTBbPDm;
      string GhhuDGnupL;
      string EkeMyTOqlp;
      string zdJZJVTnLe;
      string RieqxoTWyT;
      string HyFSsPBJwz;
      string mkcMnbXHlg;
      string lAiKtVGnPI;
      string zqrRhAXqgs;
      string TKqMrfGRDU;
      string QLjQhGOtYX;
      string JNtnAurKdm;
      string EgarNbJWSN;
      string OnkurnHaja;
      if(TTTjBUpnQo == RieqxoTWyT){lcSJjGPDLw = true;}
      else if(RieqxoTWyT == TTTjBUpnQo){xPFonjeZlm = true;}
      if(hUcpfgWFFF == HyFSsPBJwz){nunPQikrDF = true;}
      else if(HyFSsPBJwz == hUcpfgWFFF){LwUMtWwUqh = true;}
      if(yXaXFDTJQV == mkcMnbXHlg){xrbLIUbzuL = true;}
      else if(mkcMnbXHlg == yXaXFDTJQV){caLGPMCqVx = true;}
      if(VfrNmrZnWK == lAiKtVGnPI){nRZDBaORHG = true;}
      else if(lAiKtVGnPI == VfrNmrZnWK){qWohqFBfyY = true;}
      if(CqifgsyhdD == zqrRhAXqgs){MGKWZTAUdI = true;}
      else if(zqrRhAXqgs == CqifgsyhdD){tSIkwclDyE = true;}
      if(XBRBawswdx == TKqMrfGRDU){DOXedsBGBO = true;}
      else if(TKqMrfGRDU == XBRBawswdx){zdTgaWEzYb = true;}
      if(AgWuTBbPDm == QLjQhGOtYX){eQHAHVVjOo = true;}
      else if(QLjQhGOtYX == AgWuTBbPDm){gmEownGmVo = true;}
      if(GhhuDGnupL == JNtnAurKdm){TSjxsphElo = true;}
      if(EkeMyTOqlp == EgarNbJWSN){UHUlIYstYH = true;}
      if(zdJZJVTnLe == OnkurnHaja){YHQrbuzKPD = true;}
      while(JNtnAurKdm == GhhuDGnupL){VPWRnJSZJm = true;}
      while(EgarNbJWSN == EgarNbJWSN){ZysQxMDIHT = true;}
      while(OnkurnHaja == OnkurnHaja){BCGVqGNSoI = true;}
      if(lcSJjGPDLw == true){lcSJjGPDLw = false;}
      if(nunPQikrDF == true){nunPQikrDF = false;}
      if(xrbLIUbzuL == true){xrbLIUbzuL = false;}
      if(nRZDBaORHG == true){nRZDBaORHG = false;}
      if(MGKWZTAUdI == true){MGKWZTAUdI = false;}
      if(DOXedsBGBO == true){DOXedsBGBO = false;}
      if(eQHAHVVjOo == true){eQHAHVVjOo = false;}
      if(TSjxsphElo == true){TSjxsphElo = false;}
      if(UHUlIYstYH == true){UHUlIYstYH = false;}
      if(YHQrbuzKPD == true){YHQrbuzKPD = false;}
      if(xPFonjeZlm == true){xPFonjeZlm = false;}
      if(LwUMtWwUqh == true){LwUMtWwUqh = false;}
      if(caLGPMCqVx == true){caLGPMCqVx = false;}
      if(qWohqFBfyY == true){qWohqFBfyY = false;}
      if(tSIkwclDyE == true){tSIkwclDyE = false;}
      if(zdTgaWEzYb == true){zdTgaWEzYb = false;}
      if(gmEownGmVo == true){gmEownGmVo = false;}
      if(VPWRnJSZJm == true){VPWRnJSZJm = false;}
      if(ZysQxMDIHT == true){ZysQxMDIHT = false;}
      if(BCGVqGNSoI == true){BCGVqGNSoI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALYXJKZGVS
{ 
  void TOXxTCTzEg()
  { 
      bool aWknXwenJi = false;
      bool VDpWwfULIN = false;
      bool clTNxwJqeC = false;
      bool KntrMiQXiR = false;
      bool tDhblbyTzg = false;
      bool OGbhknCXpb = false;
      bool lmJGXhIxKM = false;
      bool PwbpSZDraV = false;
      bool xorxnELLGX = false;
      bool frhHfHsaDE = false;
      bool SBJmRRelPL = false;
      bool kKwTdwuMSS = false;
      bool VxplfWOTKL = false;
      bool fbnWDwfEeW = false;
      bool ZZwumVwNci = false;
      bool LgIjhUKXGu = false;
      bool DKaDfIVZPh = false;
      bool QphwswBuzJ = false;
      bool aApbzzTDnh = false;
      bool lIxjTOyrOe = false;
      string VeLmgPkSqN;
      string oJcYALbzUU;
      string tlVLgrWbZR;
      string hDkpJhCmFY;
      string IxtgNADzVS;
      string fFgtbjIzFn;
      string sIrZflXlOS;
      string JotwLwroyf;
      string nWFHlbVqOZ;
      string YCgQeAETAb;
      string cQkDJpKjie;
      string qTBZAVCkmD;
      string PgXnsHIcQL;
      string rXoWDWkBxu;
      string QlHihFBHQI;
      string xSfwMurwKB;
      string hgTWmTddVc;
      string kAmrlcYoGm;
      string FBMHOZqrKI;
      string enquNiSkuN;
      if(VeLmgPkSqN == cQkDJpKjie){aWknXwenJi = true;}
      else if(cQkDJpKjie == VeLmgPkSqN){SBJmRRelPL = true;}
      if(oJcYALbzUU == qTBZAVCkmD){VDpWwfULIN = true;}
      else if(qTBZAVCkmD == oJcYALbzUU){kKwTdwuMSS = true;}
      if(tlVLgrWbZR == PgXnsHIcQL){clTNxwJqeC = true;}
      else if(PgXnsHIcQL == tlVLgrWbZR){VxplfWOTKL = true;}
      if(hDkpJhCmFY == rXoWDWkBxu){KntrMiQXiR = true;}
      else if(rXoWDWkBxu == hDkpJhCmFY){fbnWDwfEeW = true;}
      if(IxtgNADzVS == QlHihFBHQI){tDhblbyTzg = true;}
      else if(QlHihFBHQI == IxtgNADzVS){ZZwumVwNci = true;}
      if(fFgtbjIzFn == xSfwMurwKB){OGbhknCXpb = true;}
      else if(xSfwMurwKB == fFgtbjIzFn){LgIjhUKXGu = true;}
      if(sIrZflXlOS == hgTWmTddVc){lmJGXhIxKM = true;}
      else if(hgTWmTddVc == sIrZflXlOS){DKaDfIVZPh = true;}
      if(JotwLwroyf == kAmrlcYoGm){PwbpSZDraV = true;}
      if(nWFHlbVqOZ == FBMHOZqrKI){xorxnELLGX = true;}
      if(YCgQeAETAb == enquNiSkuN){frhHfHsaDE = true;}
      while(kAmrlcYoGm == JotwLwroyf){QphwswBuzJ = true;}
      while(FBMHOZqrKI == FBMHOZqrKI){aApbzzTDnh = true;}
      while(enquNiSkuN == enquNiSkuN){lIxjTOyrOe = true;}
      if(aWknXwenJi == true){aWknXwenJi = false;}
      if(VDpWwfULIN == true){VDpWwfULIN = false;}
      if(clTNxwJqeC == true){clTNxwJqeC = false;}
      if(KntrMiQXiR == true){KntrMiQXiR = false;}
      if(tDhblbyTzg == true){tDhblbyTzg = false;}
      if(OGbhknCXpb == true){OGbhknCXpb = false;}
      if(lmJGXhIxKM == true){lmJGXhIxKM = false;}
      if(PwbpSZDraV == true){PwbpSZDraV = false;}
      if(xorxnELLGX == true){xorxnELLGX = false;}
      if(frhHfHsaDE == true){frhHfHsaDE = false;}
      if(SBJmRRelPL == true){SBJmRRelPL = false;}
      if(kKwTdwuMSS == true){kKwTdwuMSS = false;}
      if(VxplfWOTKL == true){VxplfWOTKL = false;}
      if(fbnWDwfEeW == true){fbnWDwfEeW = false;}
      if(ZZwumVwNci == true){ZZwumVwNci = false;}
      if(LgIjhUKXGu == true){LgIjhUKXGu = false;}
      if(DKaDfIVZPh == true){DKaDfIVZPh = false;}
      if(QphwswBuzJ == true){QphwswBuzJ = false;}
      if(aApbzzTDnh == true){aApbzzTDnh = false;}
      if(lIxjTOyrOe == true){lIxjTOyrOe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPAJNGUCXA
{ 
  void FQLWytpfFD()
  { 
      bool BcANPQiUZh = false;
      bool QbuDiZRwiA = false;
      bool ysCuGuzDWg = false;
      bool ZirJhTHeQx = false;
      bool ltmuUppxCY = false;
      bool iHPFZHaFHT = false;
      bool QexsIhjkUO = false;
      bool RmflNEGHZQ = false;
      bool FBByxRTmjZ = false;
      bool sCWwfGwtlm = false;
      bool FEbmGubcqU = false;
      bool ASeqOOdzup = false;
      bool OxBuVPQiGH = false;
      bool HMUmKAZOqC = false;
      bool ppuOYaWfhQ = false;
      bool bxywXIDgRq = false;
      bool erVjNnxrfN = false;
      bool oPHsAXClVt = false;
      bool rjBpeJNYOC = false;
      bool xrxAWxTKBk = false;
      string VWReQmTrhc;
      string PfswFybzUk;
      string RDXjuGgReX;
      string ePddWfMjOy;
      string ErEAWfOVBY;
      string QabGnRyhiJ;
      string GCMKyzBOYY;
      string krjVfYzWMP;
      string rKPFGDnWpF;
      string hdBErCetCX;
      string dzwcnYqGaO;
      string SaUSRulGDt;
      string LeYTpGpfcd;
      string sFUolrNlRg;
      string MgwalHJhmx;
      string PXpHLzZclg;
      string iKcxUNGfgY;
      string gzoVhdhxhi;
      string xIsfNUOMcl;
      string RkAkyBEzFX;
      if(VWReQmTrhc == dzwcnYqGaO){BcANPQiUZh = true;}
      else if(dzwcnYqGaO == VWReQmTrhc){FEbmGubcqU = true;}
      if(PfswFybzUk == SaUSRulGDt){QbuDiZRwiA = true;}
      else if(SaUSRulGDt == PfswFybzUk){ASeqOOdzup = true;}
      if(RDXjuGgReX == LeYTpGpfcd){ysCuGuzDWg = true;}
      else if(LeYTpGpfcd == RDXjuGgReX){OxBuVPQiGH = true;}
      if(ePddWfMjOy == sFUolrNlRg){ZirJhTHeQx = true;}
      else if(sFUolrNlRg == ePddWfMjOy){HMUmKAZOqC = true;}
      if(ErEAWfOVBY == MgwalHJhmx){ltmuUppxCY = true;}
      else if(MgwalHJhmx == ErEAWfOVBY){ppuOYaWfhQ = true;}
      if(QabGnRyhiJ == PXpHLzZclg){iHPFZHaFHT = true;}
      else if(PXpHLzZclg == QabGnRyhiJ){bxywXIDgRq = true;}
      if(GCMKyzBOYY == iKcxUNGfgY){QexsIhjkUO = true;}
      else if(iKcxUNGfgY == GCMKyzBOYY){erVjNnxrfN = true;}
      if(krjVfYzWMP == gzoVhdhxhi){RmflNEGHZQ = true;}
      if(rKPFGDnWpF == xIsfNUOMcl){FBByxRTmjZ = true;}
      if(hdBErCetCX == RkAkyBEzFX){sCWwfGwtlm = true;}
      while(gzoVhdhxhi == krjVfYzWMP){oPHsAXClVt = true;}
      while(xIsfNUOMcl == xIsfNUOMcl){rjBpeJNYOC = true;}
      while(RkAkyBEzFX == RkAkyBEzFX){xrxAWxTKBk = true;}
      if(BcANPQiUZh == true){BcANPQiUZh = false;}
      if(QbuDiZRwiA == true){QbuDiZRwiA = false;}
      if(ysCuGuzDWg == true){ysCuGuzDWg = false;}
      if(ZirJhTHeQx == true){ZirJhTHeQx = false;}
      if(ltmuUppxCY == true){ltmuUppxCY = false;}
      if(iHPFZHaFHT == true){iHPFZHaFHT = false;}
      if(QexsIhjkUO == true){QexsIhjkUO = false;}
      if(RmflNEGHZQ == true){RmflNEGHZQ = false;}
      if(FBByxRTmjZ == true){FBByxRTmjZ = false;}
      if(sCWwfGwtlm == true){sCWwfGwtlm = false;}
      if(FEbmGubcqU == true){FEbmGubcqU = false;}
      if(ASeqOOdzup == true){ASeqOOdzup = false;}
      if(OxBuVPQiGH == true){OxBuVPQiGH = false;}
      if(HMUmKAZOqC == true){HMUmKAZOqC = false;}
      if(ppuOYaWfhQ == true){ppuOYaWfhQ = false;}
      if(bxywXIDgRq == true){bxywXIDgRq = false;}
      if(erVjNnxrfN == true){erVjNnxrfN = false;}
      if(oPHsAXClVt == true){oPHsAXClVt = false;}
      if(rjBpeJNYOC == true){rjBpeJNYOC = false;}
      if(xrxAWxTKBk == true){xrxAWxTKBk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCFOAYZOOY
{ 
  void NsoSpMVZkr()
  { 
      bool XyyjcqIxeR = false;
      bool iGMATtBNyE = false;
      bool WrOBnSfxtd = false;
      bool EXuZYNxlxO = false;
      bool irMFQqImap = false;
      bool hEjNOejxwJ = false;
      bool KKDBNKKlaG = false;
      bool wOPjUefJjx = false;
      bool KrVDuAmhKs = false;
      bool dApmDYnLrF = false;
      bool fVLTtSnAsj = false;
      bool zZMyzRnzFN = false;
      bool XcbhcuYcfw = false;
      bool pTRdRnfCJc = false;
      bool LmoasDmqml = false;
      bool joFdhCtdqy = false;
      bool sLTxseHigL = false;
      bool klpbBjnAnY = false;
      bool HgotLBOmuO = false;
      bool tCKKiASqhN = false;
      string SgWUDzUqxG;
      string IJikjloJpr;
      string IrKzGmraQg;
      string KyJEAAFDpD;
      string KuuKYiZRmK;
      string VkPCBZVWNQ;
      string GtZPuJAdjj;
      string fkTlgMxAZX;
      string MZnGLZhHCa;
      string dhpZwQUfOO;
      string hugCdkRcUn;
      string cVxpDfFTEV;
      string asbJFxuspQ;
      string rQkKoRskbZ;
      string HFlNxIkzWP;
      string LAbsnoTXxg;
      string pXmDwLjlBl;
      string mTrdNVGNLx;
      string MuWZFrorWA;
      string xUnujjRiRk;
      if(SgWUDzUqxG == hugCdkRcUn){XyyjcqIxeR = true;}
      else if(hugCdkRcUn == SgWUDzUqxG){fVLTtSnAsj = true;}
      if(IJikjloJpr == cVxpDfFTEV){iGMATtBNyE = true;}
      else if(cVxpDfFTEV == IJikjloJpr){zZMyzRnzFN = true;}
      if(IrKzGmraQg == asbJFxuspQ){WrOBnSfxtd = true;}
      else if(asbJFxuspQ == IrKzGmraQg){XcbhcuYcfw = true;}
      if(KyJEAAFDpD == rQkKoRskbZ){EXuZYNxlxO = true;}
      else if(rQkKoRskbZ == KyJEAAFDpD){pTRdRnfCJc = true;}
      if(KuuKYiZRmK == HFlNxIkzWP){irMFQqImap = true;}
      else if(HFlNxIkzWP == KuuKYiZRmK){LmoasDmqml = true;}
      if(VkPCBZVWNQ == LAbsnoTXxg){hEjNOejxwJ = true;}
      else if(LAbsnoTXxg == VkPCBZVWNQ){joFdhCtdqy = true;}
      if(GtZPuJAdjj == pXmDwLjlBl){KKDBNKKlaG = true;}
      else if(pXmDwLjlBl == GtZPuJAdjj){sLTxseHigL = true;}
      if(fkTlgMxAZX == mTrdNVGNLx){wOPjUefJjx = true;}
      if(MZnGLZhHCa == MuWZFrorWA){KrVDuAmhKs = true;}
      if(dhpZwQUfOO == xUnujjRiRk){dApmDYnLrF = true;}
      while(mTrdNVGNLx == fkTlgMxAZX){klpbBjnAnY = true;}
      while(MuWZFrorWA == MuWZFrorWA){HgotLBOmuO = true;}
      while(xUnujjRiRk == xUnujjRiRk){tCKKiASqhN = true;}
      if(XyyjcqIxeR == true){XyyjcqIxeR = false;}
      if(iGMATtBNyE == true){iGMATtBNyE = false;}
      if(WrOBnSfxtd == true){WrOBnSfxtd = false;}
      if(EXuZYNxlxO == true){EXuZYNxlxO = false;}
      if(irMFQqImap == true){irMFQqImap = false;}
      if(hEjNOejxwJ == true){hEjNOejxwJ = false;}
      if(KKDBNKKlaG == true){KKDBNKKlaG = false;}
      if(wOPjUefJjx == true){wOPjUefJjx = false;}
      if(KrVDuAmhKs == true){KrVDuAmhKs = false;}
      if(dApmDYnLrF == true){dApmDYnLrF = false;}
      if(fVLTtSnAsj == true){fVLTtSnAsj = false;}
      if(zZMyzRnzFN == true){zZMyzRnzFN = false;}
      if(XcbhcuYcfw == true){XcbhcuYcfw = false;}
      if(pTRdRnfCJc == true){pTRdRnfCJc = false;}
      if(LmoasDmqml == true){LmoasDmqml = false;}
      if(joFdhCtdqy == true){joFdhCtdqy = false;}
      if(sLTxseHigL == true){sLTxseHigL = false;}
      if(klpbBjnAnY == true){klpbBjnAnY = false;}
      if(HgotLBOmuO == true){HgotLBOmuO = false;}
      if(tCKKiASqhN == true){tCKKiASqhN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYAVIVAXAM
{ 
  void IluaVTfeyF()
  { 
      bool ebqnrWNPGW = false;
      bool ZwEaIwdLNn = false;
      bool FuZKwQHGDq = false;
      bool hrJeTGfTqi = false;
      bool ZVlZnrXmVb = false;
      bool JfGDViBfqb = false;
      bool PHMOoglZHC = false;
      bool PKUeNjJAWE = false;
      bool rTjahBkGIj = false;
      bool EzbOTSIWkG = false;
      bool FyfSLyLbpl = false;
      bool ZBJmiuWlfm = false;
      bool ufQWxPiFKt = false;
      bool blPQztnQPj = false;
      bool pJPWJDpneX = false;
      bool wWpxKYgIVu = false;
      bool OFQwKmksno = false;
      bool GFVwxlQtNt = false;
      bool ZtZlxFuRFZ = false;
      bool MfuTUjrTLV = false;
      string kDBztlaXOj;
      string gdmMmijuZq;
      string zZLgkVajUq;
      string lOWlyekETg;
      string rHjocuSzBY;
      string ntJQEKqUOY;
      string KqDWxRHBNI;
      string yearzqpWDo;
      string CahwCrEFgn;
      string nPpuVBEMqK;
      string nRlsZJSRRN;
      string UTQZViJGUF;
      string NBTZThnfVx;
      string lcesAkonVs;
      string ZmnSSUzQYl;
      string ryqlxmxLZq;
      string UluTbqoWYj;
      string tUkbeZMBGz;
      string iXHiFnlswN;
      string ncNdYmrUqb;
      if(kDBztlaXOj == nRlsZJSRRN){ebqnrWNPGW = true;}
      else if(nRlsZJSRRN == kDBztlaXOj){FyfSLyLbpl = true;}
      if(gdmMmijuZq == UTQZViJGUF){ZwEaIwdLNn = true;}
      else if(UTQZViJGUF == gdmMmijuZq){ZBJmiuWlfm = true;}
      if(zZLgkVajUq == NBTZThnfVx){FuZKwQHGDq = true;}
      else if(NBTZThnfVx == zZLgkVajUq){ufQWxPiFKt = true;}
      if(lOWlyekETg == lcesAkonVs){hrJeTGfTqi = true;}
      else if(lcesAkonVs == lOWlyekETg){blPQztnQPj = true;}
      if(rHjocuSzBY == ZmnSSUzQYl){ZVlZnrXmVb = true;}
      else if(ZmnSSUzQYl == rHjocuSzBY){pJPWJDpneX = true;}
      if(ntJQEKqUOY == ryqlxmxLZq){JfGDViBfqb = true;}
      else if(ryqlxmxLZq == ntJQEKqUOY){wWpxKYgIVu = true;}
      if(KqDWxRHBNI == UluTbqoWYj){PHMOoglZHC = true;}
      else if(UluTbqoWYj == KqDWxRHBNI){OFQwKmksno = true;}
      if(yearzqpWDo == tUkbeZMBGz){PKUeNjJAWE = true;}
      if(CahwCrEFgn == iXHiFnlswN){rTjahBkGIj = true;}
      if(nPpuVBEMqK == ncNdYmrUqb){EzbOTSIWkG = true;}
      while(tUkbeZMBGz == yearzqpWDo){GFVwxlQtNt = true;}
      while(iXHiFnlswN == iXHiFnlswN){ZtZlxFuRFZ = true;}
      while(ncNdYmrUqb == ncNdYmrUqb){MfuTUjrTLV = true;}
      if(ebqnrWNPGW == true){ebqnrWNPGW = false;}
      if(ZwEaIwdLNn == true){ZwEaIwdLNn = false;}
      if(FuZKwQHGDq == true){FuZKwQHGDq = false;}
      if(hrJeTGfTqi == true){hrJeTGfTqi = false;}
      if(ZVlZnrXmVb == true){ZVlZnrXmVb = false;}
      if(JfGDViBfqb == true){JfGDViBfqb = false;}
      if(PHMOoglZHC == true){PHMOoglZHC = false;}
      if(PKUeNjJAWE == true){PKUeNjJAWE = false;}
      if(rTjahBkGIj == true){rTjahBkGIj = false;}
      if(EzbOTSIWkG == true){EzbOTSIWkG = false;}
      if(FyfSLyLbpl == true){FyfSLyLbpl = false;}
      if(ZBJmiuWlfm == true){ZBJmiuWlfm = false;}
      if(ufQWxPiFKt == true){ufQWxPiFKt = false;}
      if(blPQztnQPj == true){blPQztnQPj = false;}
      if(pJPWJDpneX == true){pJPWJDpneX = false;}
      if(wWpxKYgIVu == true){wWpxKYgIVu = false;}
      if(OFQwKmksno == true){OFQwKmksno = false;}
      if(GFVwxlQtNt == true){GFVwxlQtNt = false;}
      if(ZtZlxFuRFZ == true){ZtZlxFuRFZ = false;}
      if(MfuTUjrTLV == true){MfuTUjrTLV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIKYZQPNJU
{ 
  void wCZgPwuEnN()
  { 
      bool TrEgQGNxxW = false;
      bool TKxtlUBAHf = false;
      bool PuxIzxaGky = false;
      bool ZZILNEZReC = false;
      bool iGOAKMoqwL = false;
      bool riFuqYtuhT = false;
      bool fGMzxsBlfg = false;
      bool uiVFxIfxyl = false;
      bool IiKZFpUMTo = false;
      bool KdiLVbtPDQ = false;
      bool KCLOQINzyi = false;
      bool sxxuKxwlsG = false;
      bool YnSqWQzJjU = false;
      bool OPsgbGXwJx = false;
      bool cUOkwMgnAY = false;
      bool fHVxrVjUqz = false;
      bool IDPcTcDPTE = false;
      bool ZzcucDZguK = false;
      bool iLIKoGswnF = false;
      bool WDFJoYEkQS = false;
      string bgcOsdFgGc;
      string ZdyyXxiSZn;
      string rBqWdHdfLG;
      string rHmZobuzbn;
      string SgQMrRHRgx;
      string EtfOpZoFjl;
      string zYVAjSqXIu;
      string BjqkVLkeeL;
      string zMzNBxaXiP;
      string loOonsKPbY;
      string aiJkuUDtsd;
      string oKaXlmZHzl;
      string qSosJLUCxb;
      string AUCFkQDNRg;
      string tgeEabOpCB;
      string SDQogHtQbj;
      string zAxQcTHVlV;
      string jMoSrKnjSh;
      string xdzwIxEMXd;
      string WmlhgsjNaG;
      if(bgcOsdFgGc == aiJkuUDtsd){TrEgQGNxxW = true;}
      else if(aiJkuUDtsd == bgcOsdFgGc){KCLOQINzyi = true;}
      if(ZdyyXxiSZn == oKaXlmZHzl){TKxtlUBAHf = true;}
      else if(oKaXlmZHzl == ZdyyXxiSZn){sxxuKxwlsG = true;}
      if(rBqWdHdfLG == qSosJLUCxb){PuxIzxaGky = true;}
      else if(qSosJLUCxb == rBqWdHdfLG){YnSqWQzJjU = true;}
      if(rHmZobuzbn == AUCFkQDNRg){ZZILNEZReC = true;}
      else if(AUCFkQDNRg == rHmZobuzbn){OPsgbGXwJx = true;}
      if(SgQMrRHRgx == tgeEabOpCB){iGOAKMoqwL = true;}
      else if(tgeEabOpCB == SgQMrRHRgx){cUOkwMgnAY = true;}
      if(EtfOpZoFjl == SDQogHtQbj){riFuqYtuhT = true;}
      else if(SDQogHtQbj == EtfOpZoFjl){fHVxrVjUqz = true;}
      if(zYVAjSqXIu == zAxQcTHVlV){fGMzxsBlfg = true;}
      else if(zAxQcTHVlV == zYVAjSqXIu){IDPcTcDPTE = true;}
      if(BjqkVLkeeL == jMoSrKnjSh){uiVFxIfxyl = true;}
      if(zMzNBxaXiP == xdzwIxEMXd){IiKZFpUMTo = true;}
      if(loOonsKPbY == WmlhgsjNaG){KdiLVbtPDQ = true;}
      while(jMoSrKnjSh == BjqkVLkeeL){ZzcucDZguK = true;}
      while(xdzwIxEMXd == xdzwIxEMXd){iLIKoGswnF = true;}
      while(WmlhgsjNaG == WmlhgsjNaG){WDFJoYEkQS = true;}
      if(TrEgQGNxxW == true){TrEgQGNxxW = false;}
      if(TKxtlUBAHf == true){TKxtlUBAHf = false;}
      if(PuxIzxaGky == true){PuxIzxaGky = false;}
      if(ZZILNEZReC == true){ZZILNEZReC = false;}
      if(iGOAKMoqwL == true){iGOAKMoqwL = false;}
      if(riFuqYtuhT == true){riFuqYtuhT = false;}
      if(fGMzxsBlfg == true){fGMzxsBlfg = false;}
      if(uiVFxIfxyl == true){uiVFxIfxyl = false;}
      if(IiKZFpUMTo == true){IiKZFpUMTo = false;}
      if(KdiLVbtPDQ == true){KdiLVbtPDQ = false;}
      if(KCLOQINzyi == true){KCLOQINzyi = false;}
      if(sxxuKxwlsG == true){sxxuKxwlsG = false;}
      if(YnSqWQzJjU == true){YnSqWQzJjU = false;}
      if(OPsgbGXwJx == true){OPsgbGXwJx = false;}
      if(cUOkwMgnAY == true){cUOkwMgnAY = false;}
      if(fHVxrVjUqz == true){fHVxrVjUqz = false;}
      if(IDPcTcDPTE == true){IDPcTcDPTE = false;}
      if(ZzcucDZguK == true){ZzcucDZguK = false;}
      if(iLIKoGswnF == true){iLIKoGswnF = false;}
      if(WDFJoYEkQS == true){WDFJoYEkQS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIRCNQLBTB
{ 
  void DNmODUqrkZ()
  { 
      bool akayuNUpWQ = false;
      bool RUzKcLfyCS = false;
      bool cfjYmYHfMT = false;
      bool SCAqmelMhL = false;
      bool xBxKZskoxa = false;
      bool pmtaZuACLW = false;
      bool GndDxOUHXx = false;
      bool YSPqVahYzs = false;
      bool nRhldfIYQr = false;
      bool djALEJXtNK = false;
      bool YcRzBWWCFz = false;
      bool MaDSinFrZR = false;
      bool GupeToREmL = false;
      bool CmLnTKAijG = false;
      bool IFTReCfhcP = false;
      bool DfUuDdmlfM = false;
      bool ESPswYPOyX = false;
      bool nWISIAaYzR = false;
      bool IjaWIWSQko = false;
      bool XNCWBopZUG = false;
      string jIztqioiwX;
      string BsRQwFQUze;
      string osbKRrCOnr;
      string GKVhTrqtdY;
      string euGecPYKVR;
      string BrlXXqfnby;
      string fauDQpXiwE;
      string NWpazslwhC;
      string SrrVqOYxJc;
      string MCRerEADOl;
      string roNRDdBKXd;
      string EiGZemhYMC;
      string RZZTrLEKiu;
      string sihuJdeZSM;
      string MNZeYcuqAE;
      string VapMURPtZr;
      string ZpbbkUBKPB;
      string IHGzoEAtuO;
      string PNKdZRrUaq;
      string OjAZmVkxtD;
      if(jIztqioiwX == roNRDdBKXd){akayuNUpWQ = true;}
      else if(roNRDdBKXd == jIztqioiwX){YcRzBWWCFz = true;}
      if(BsRQwFQUze == EiGZemhYMC){RUzKcLfyCS = true;}
      else if(EiGZemhYMC == BsRQwFQUze){MaDSinFrZR = true;}
      if(osbKRrCOnr == RZZTrLEKiu){cfjYmYHfMT = true;}
      else if(RZZTrLEKiu == osbKRrCOnr){GupeToREmL = true;}
      if(GKVhTrqtdY == sihuJdeZSM){SCAqmelMhL = true;}
      else if(sihuJdeZSM == GKVhTrqtdY){CmLnTKAijG = true;}
      if(euGecPYKVR == MNZeYcuqAE){xBxKZskoxa = true;}
      else if(MNZeYcuqAE == euGecPYKVR){IFTReCfhcP = true;}
      if(BrlXXqfnby == VapMURPtZr){pmtaZuACLW = true;}
      else if(VapMURPtZr == BrlXXqfnby){DfUuDdmlfM = true;}
      if(fauDQpXiwE == ZpbbkUBKPB){GndDxOUHXx = true;}
      else if(ZpbbkUBKPB == fauDQpXiwE){ESPswYPOyX = true;}
      if(NWpazslwhC == IHGzoEAtuO){YSPqVahYzs = true;}
      if(SrrVqOYxJc == PNKdZRrUaq){nRhldfIYQr = true;}
      if(MCRerEADOl == OjAZmVkxtD){djALEJXtNK = true;}
      while(IHGzoEAtuO == NWpazslwhC){nWISIAaYzR = true;}
      while(PNKdZRrUaq == PNKdZRrUaq){IjaWIWSQko = true;}
      while(OjAZmVkxtD == OjAZmVkxtD){XNCWBopZUG = true;}
      if(akayuNUpWQ == true){akayuNUpWQ = false;}
      if(RUzKcLfyCS == true){RUzKcLfyCS = false;}
      if(cfjYmYHfMT == true){cfjYmYHfMT = false;}
      if(SCAqmelMhL == true){SCAqmelMhL = false;}
      if(xBxKZskoxa == true){xBxKZskoxa = false;}
      if(pmtaZuACLW == true){pmtaZuACLW = false;}
      if(GndDxOUHXx == true){GndDxOUHXx = false;}
      if(YSPqVahYzs == true){YSPqVahYzs = false;}
      if(nRhldfIYQr == true){nRhldfIYQr = false;}
      if(djALEJXtNK == true){djALEJXtNK = false;}
      if(YcRzBWWCFz == true){YcRzBWWCFz = false;}
      if(MaDSinFrZR == true){MaDSinFrZR = false;}
      if(GupeToREmL == true){GupeToREmL = false;}
      if(CmLnTKAijG == true){CmLnTKAijG = false;}
      if(IFTReCfhcP == true){IFTReCfhcP = false;}
      if(DfUuDdmlfM == true){DfUuDdmlfM = false;}
      if(ESPswYPOyX == true){ESPswYPOyX = false;}
      if(nWISIAaYzR == true){nWISIAaYzR = false;}
      if(IjaWIWSQko == true){IjaWIWSQko = false;}
      if(XNCWBopZUG == true){XNCWBopZUG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYWCIAGBCC
{ 
  void RkcuWtUoAE()
  { 
      bool bYjOBLMPGY = false;
      bool pFANTuazYZ = false;
      bool saFqEVQBdn = false;
      bool GucVxUqNIn = false;
      bool dZSUjubaZZ = false;
      bool XsRTVATrKe = false;
      bool tKkSRtbdPz = false;
      bool ENpjwSIjHJ = false;
      bool tpbEQNdIzw = false;
      bool AyDctSoACo = false;
      bool SxKaUKCgWD = false;
      bool rijAkEifCE = false;
      bool QTdSyFJNpc = false;
      bool dIhSpweAjF = false;
      bool KwkwEROCro = false;
      bool jIyyXzSqcO = false;
      bool AoptZiBRKn = false;
      bool YhwwsThhOg = false;
      bool qGUBsUJjtq = false;
      bool cnXUEVFqWU = false;
      string KCtYcOFadw;
      string WPLMPNbTWI;
      string RHgiUHWGhs;
      string CDHCpRCaVC;
      string uGsdqlUpor;
      string AykCbDVKDU;
      string rysktSHJVy;
      string KAxTNLNCrh;
      string mgRorDSFam;
      string wqXAKxMIjY;
      string eKTpgAARoP;
      string oSSUgLgErp;
      string AChiCScwIP;
      string yFSSDcMbHr;
      string DAPKycYCTz;
      string PIPsYcbkmN;
      string WEIYQiAzRE;
      string yEwAmzlWkZ;
      string tacJzppYtZ;
      string AbntVzrptO;
      if(KCtYcOFadw == eKTpgAARoP){bYjOBLMPGY = true;}
      else if(eKTpgAARoP == KCtYcOFadw){SxKaUKCgWD = true;}
      if(WPLMPNbTWI == oSSUgLgErp){pFANTuazYZ = true;}
      else if(oSSUgLgErp == WPLMPNbTWI){rijAkEifCE = true;}
      if(RHgiUHWGhs == AChiCScwIP){saFqEVQBdn = true;}
      else if(AChiCScwIP == RHgiUHWGhs){QTdSyFJNpc = true;}
      if(CDHCpRCaVC == yFSSDcMbHr){GucVxUqNIn = true;}
      else if(yFSSDcMbHr == CDHCpRCaVC){dIhSpweAjF = true;}
      if(uGsdqlUpor == DAPKycYCTz){dZSUjubaZZ = true;}
      else if(DAPKycYCTz == uGsdqlUpor){KwkwEROCro = true;}
      if(AykCbDVKDU == PIPsYcbkmN){XsRTVATrKe = true;}
      else if(PIPsYcbkmN == AykCbDVKDU){jIyyXzSqcO = true;}
      if(rysktSHJVy == WEIYQiAzRE){tKkSRtbdPz = true;}
      else if(WEIYQiAzRE == rysktSHJVy){AoptZiBRKn = true;}
      if(KAxTNLNCrh == yEwAmzlWkZ){ENpjwSIjHJ = true;}
      if(mgRorDSFam == tacJzppYtZ){tpbEQNdIzw = true;}
      if(wqXAKxMIjY == AbntVzrptO){AyDctSoACo = true;}
      while(yEwAmzlWkZ == KAxTNLNCrh){YhwwsThhOg = true;}
      while(tacJzppYtZ == tacJzppYtZ){qGUBsUJjtq = true;}
      while(AbntVzrptO == AbntVzrptO){cnXUEVFqWU = true;}
      if(bYjOBLMPGY == true){bYjOBLMPGY = false;}
      if(pFANTuazYZ == true){pFANTuazYZ = false;}
      if(saFqEVQBdn == true){saFqEVQBdn = false;}
      if(GucVxUqNIn == true){GucVxUqNIn = false;}
      if(dZSUjubaZZ == true){dZSUjubaZZ = false;}
      if(XsRTVATrKe == true){XsRTVATrKe = false;}
      if(tKkSRtbdPz == true){tKkSRtbdPz = false;}
      if(ENpjwSIjHJ == true){ENpjwSIjHJ = false;}
      if(tpbEQNdIzw == true){tpbEQNdIzw = false;}
      if(AyDctSoACo == true){AyDctSoACo = false;}
      if(SxKaUKCgWD == true){SxKaUKCgWD = false;}
      if(rijAkEifCE == true){rijAkEifCE = false;}
      if(QTdSyFJNpc == true){QTdSyFJNpc = false;}
      if(dIhSpweAjF == true){dIhSpweAjF = false;}
      if(KwkwEROCro == true){KwkwEROCro = false;}
      if(jIyyXzSqcO == true){jIyyXzSqcO = false;}
      if(AoptZiBRKn == true){AoptZiBRKn = false;}
      if(YhwwsThhOg == true){YhwwsThhOg = false;}
      if(qGUBsUJjtq == true){qGUBsUJjtq = false;}
      if(cnXUEVFqWU == true){cnXUEVFqWU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZYZAEMEYD
{ 
  void yaxjVamPRz()
  { 
      bool SOnuqPuwos = false;
      bool WhnSmLKRLJ = false;
      bool LKaNriCsKS = false;
      bool NkStTJyUOR = false;
      bool JDOtYnVVOd = false;
      bool waPNaHmaDI = false;
      bool MBkVekOtzd = false;
      bool NpDtzIwgnD = false;
      bool MfegWmVFSL = false;
      bool VXRFEIRrOm = false;
      bool YbWkQFXVNS = false;
      bool LGlzugWEzq = false;
      bool PJamHpXxoq = false;
      bool pDRBdkJsQQ = false;
      bool PAqAAOkRKX = false;
      bool lMsXXPBjca = false;
      bool hZgWbIokUK = false;
      bool WcniaPRZls = false;
      bool EGlQFcKsdO = false;
      bool iZPoioTUXr = false;
      string iSnygciHsV;
      string pLduRWzWMh;
      string jmydJYXcVe;
      string epWEFiobcN;
      string zmBLUIaqIt;
      string GwMRHwTKoH;
      string FGkNpznYoi;
      string gWtzhxkmIA;
      string xgTaXicFwJ;
      string OemUIsBmUV;
      string TBBZNiBNiK;
      string KgBoKXlKpG;
      string VicfTBjZpo;
      string wyRmfuetNo;
      string hPVlzhcxJj;
      string HqxNzjYUFL;
      string yaXtOMOOIO;
      string sqwAYGNpgl;
      string XmPFhEADmu;
      string WJoCpGrbXm;
      if(iSnygciHsV == TBBZNiBNiK){SOnuqPuwos = true;}
      else if(TBBZNiBNiK == iSnygciHsV){YbWkQFXVNS = true;}
      if(pLduRWzWMh == KgBoKXlKpG){WhnSmLKRLJ = true;}
      else if(KgBoKXlKpG == pLduRWzWMh){LGlzugWEzq = true;}
      if(jmydJYXcVe == VicfTBjZpo){LKaNriCsKS = true;}
      else if(VicfTBjZpo == jmydJYXcVe){PJamHpXxoq = true;}
      if(epWEFiobcN == wyRmfuetNo){NkStTJyUOR = true;}
      else if(wyRmfuetNo == epWEFiobcN){pDRBdkJsQQ = true;}
      if(zmBLUIaqIt == hPVlzhcxJj){JDOtYnVVOd = true;}
      else if(hPVlzhcxJj == zmBLUIaqIt){PAqAAOkRKX = true;}
      if(GwMRHwTKoH == HqxNzjYUFL){waPNaHmaDI = true;}
      else if(HqxNzjYUFL == GwMRHwTKoH){lMsXXPBjca = true;}
      if(FGkNpznYoi == yaXtOMOOIO){MBkVekOtzd = true;}
      else if(yaXtOMOOIO == FGkNpznYoi){hZgWbIokUK = true;}
      if(gWtzhxkmIA == sqwAYGNpgl){NpDtzIwgnD = true;}
      if(xgTaXicFwJ == XmPFhEADmu){MfegWmVFSL = true;}
      if(OemUIsBmUV == WJoCpGrbXm){VXRFEIRrOm = true;}
      while(sqwAYGNpgl == gWtzhxkmIA){WcniaPRZls = true;}
      while(XmPFhEADmu == XmPFhEADmu){EGlQFcKsdO = true;}
      while(WJoCpGrbXm == WJoCpGrbXm){iZPoioTUXr = true;}
      if(SOnuqPuwos == true){SOnuqPuwos = false;}
      if(WhnSmLKRLJ == true){WhnSmLKRLJ = false;}
      if(LKaNriCsKS == true){LKaNriCsKS = false;}
      if(NkStTJyUOR == true){NkStTJyUOR = false;}
      if(JDOtYnVVOd == true){JDOtYnVVOd = false;}
      if(waPNaHmaDI == true){waPNaHmaDI = false;}
      if(MBkVekOtzd == true){MBkVekOtzd = false;}
      if(NpDtzIwgnD == true){NpDtzIwgnD = false;}
      if(MfegWmVFSL == true){MfegWmVFSL = false;}
      if(VXRFEIRrOm == true){VXRFEIRrOm = false;}
      if(YbWkQFXVNS == true){YbWkQFXVNS = false;}
      if(LGlzugWEzq == true){LGlzugWEzq = false;}
      if(PJamHpXxoq == true){PJamHpXxoq = false;}
      if(pDRBdkJsQQ == true){pDRBdkJsQQ = false;}
      if(PAqAAOkRKX == true){PAqAAOkRKX = false;}
      if(lMsXXPBjca == true){lMsXXPBjca = false;}
      if(hZgWbIokUK == true){hZgWbIokUK = false;}
      if(WcniaPRZls == true){WcniaPRZls = false;}
      if(EGlQFcKsdO == true){EGlQFcKsdO = false;}
      if(iZPoioTUXr == true){iZPoioTUXr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOLTVHWXQP
{ 
  void CtDOAGDIGQ()
  { 
      bool SeWhBuZnAR = false;
      bool asGQMIuUnT = false;
      bool PqbyosAGwV = false;
      bool MaAUfOAeMu = false;
      bool nikjZKqOjp = false;
      bool IWqcUbCXsI = false;
      bool tSqdEArkjy = false;
      bool IQIrefFqYe = false;
      bool BlWFNpjXAE = false;
      bool LclEBVrHfZ = false;
      bool RFelgrOyxn = false;
      bool VKzNGIwkQN = false;
      bool QUkelfeEqI = false;
      bool nyKyMwGjYU = false;
      bool bkZLiAdXxs = false;
      bool ZGpSJxTAAB = false;
      bool NKGozWAAAK = false;
      bool BLMuletZwk = false;
      bool BGGyihHroP = false;
      bool bGjWHRdkML = false;
      string LMFXBhfBHL;
      string AzmVmCTLnG;
      string jCsaHFiyhc;
      string LDZIZFoVJp;
      string kFmPzYukrV;
      string XzmSEITdQw;
      string yhTezxZeug;
      string NyCxUdOcbh;
      string JyGLELQHDR;
      string lLENqDlIPC;
      string zQoKIZxoxZ;
      string spChlzbHZn;
      string fRaduCsnGR;
      string rGNYisJuDe;
      string NaKdXuIVar;
      string adiaWhpLPG;
      string fIiehmcdzr;
      string pfEuaFGwFz;
      string sWNNpOWlCA;
      string DxexyErfwk;
      if(LMFXBhfBHL == zQoKIZxoxZ){SeWhBuZnAR = true;}
      else if(zQoKIZxoxZ == LMFXBhfBHL){RFelgrOyxn = true;}
      if(AzmVmCTLnG == spChlzbHZn){asGQMIuUnT = true;}
      else if(spChlzbHZn == AzmVmCTLnG){VKzNGIwkQN = true;}
      if(jCsaHFiyhc == fRaduCsnGR){PqbyosAGwV = true;}
      else if(fRaduCsnGR == jCsaHFiyhc){QUkelfeEqI = true;}
      if(LDZIZFoVJp == rGNYisJuDe){MaAUfOAeMu = true;}
      else if(rGNYisJuDe == LDZIZFoVJp){nyKyMwGjYU = true;}
      if(kFmPzYukrV == NaKdXuIVar){nikjZKqOjp = true;}
      else if(NaKdXuIVar == kFmPzYukrV){bkZLiAdXxs = true;}
      if(XzmSEITdQw == adiaWhpLPG){IWqcUbCXsI = true;}
      else if(adiaWhpLPG == XzmSEITdQw){ZGpSJxTAAB = true;}
      if(yhTezxZeug == fIiehmcdzr){tSqdEArkjy = true;}
      else if(fIiehmcdzr == yhTezxZeug){NKGozWAAAK = true;}
      if(NyCxUdOcbh == pfEuaFGwFz){IQIrefFqYe = true;}
      if(JyGLELQHDR == sWNNpOWlCA){BlWFNpjXAE = true;}
      if(lLENqDlIPC == DxexyErfwk){LclEBVrHfZ = true;}
      while(pfEuaFGwFz == NyCxUdOcbh){BLMuletZwk = true;}
      while(sWNNpOWlCA == sWNNpOWlCA){BGGyihHroP = true;}
      while(DxexyErfwk == DxexyErfwk){bGjWHRdkML = true;}
      if(SeWhBuZnAR == true){SeWhBuZnAR = false;}
      if(asGQMIuUnT == true){asGQMIuUnT = false;}
      if(PqbyosAGwV == true){PqbyosAGwV = false;}
      if(MaAUfOAeMu == true){MaAUfOAeMu = false;}
      if(nikjZKqOjp == true){nikjZKqOjp = false;}
      if(IWqcUbCXsI == true){IWqcUbCXsI = false;}
      if(tSqdEArkjy == true){tSqdEArkjy = false;}
      if(IQIrefFqYe == true){IQIrefFqYe = false;}
      if(BlWFNpjXAE == true){BlWFNpjXAE = false;}
      if(LclEBVrHfZ == true){LclEBVrHfZ = false;}
      if(RFelgrOyxn == true){RFelgrOyxn = false;}
      if(VKzNGIwkQN == true){VKzNGIwkQN = false;}
      if(QUkelfeEqI == true){QUkelfeEqI = false;}
      if(nyKyMwGjYU == true){nyKyMwGjYU = false;}
      if(bkZLiAdXxs == true){bkZLiAdXxs = false;}
      if(ZGpSJxTAAB == true){ZGpSJxTAAB = false;}
      if(NKGozWAAAK == true){NKGozWAAAK = false;}
      if(BLMuletZwk == true){BLMuletZwk = false;}
      if(BGGyihHroP == true){BGGyihHroP = false;}
      if(bGjWHRdkML == true){bGjWHRdkML = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBZHSZWEBD
{ 
  void ZxHcSaSwhr()
  { 
      bool sIPmQxULSf = false;
      bool UrAesETFQx = false;
      bool ciwcrzmJWl = false;
      bool niemzbWrwL = false;
      bool xWeeHZMkcb = false;
      bool qfLALJLmuQ = false;
      bool JKofrlMNeR = false;
      bool haJEAGERVS = false;
      bool mCguuHWeao = false;
      bool PjxfBlgymU = false;
      bool MyFLtPWGAE = false;
      bool FtQbcHdtkj = false;
      bool OhlpBxdcCN = false;
      bool ZFeAFnxUAf = false;
      bool jPdWiUTUCt = false;
      bool ImNCGdMOJw = false;
      bool ksEmeAPPWn = false;
      bool KJsEAyDPHg = false;
      bool dJaHFlqbta = false;
      bool bhKDupLqqh = false;
      string ifXHEwnRPc;
      string yUbBzRmTHP;
      string xiyrrFuRFO;
      string kAWkLFXwui;
      string NtsNlqDxkY;
      string pAikmAgfOz;
      string BWMBqyypos;
      string spYYBCpkFB;
      string ByffYkQkyL;
      string XqhugqhrVn;
      string sNHrfzbKij;
      string JwZNyDpgbG;
      string gMqdUBHcqJ;
      string TyORImpmAY;
      string JGBOBbQUxd;
      string ABPPGfVcXd;
      string ryTZPLhIFK;
      string MDfDwaKccs;
      string kmeNJShyLb;
      string RMPVgKlbyo;
      if(ifXHEwnRPc == sNHrfzbKij){sIPmQxULSf = true;}
      else if(sNHrfzbKij == ifXHEwnRPc){MyFLtPWGAE = true;}
      if(yUbBzRmTHP == JwZNyDpgbG){UrAesETFQx = true;}
      else if(JwZNyDpgbG == yUbBzRmTHP){FtQbcHdtkj = true;}
      if(xiyrrFuRFO == gMqdUBHcqJ){ciwcrzmJWl = true;}
      else if(gMqdUBHcqJ == xiyrrFuRFO){OhlpBxdcCN = true;}
      if(kAWkLFXwui == TyORImpmAY){niemzbWrwL = true;}
      else if(TyORImpmAY == kAWkLFXwui){ZFeAFnxUAf = true;}
      if(NtsNlqDxkY == JGBOBbQUxd){xWeeHZMkcb = true;}
      else if(JGBOBbQUxd == NtsNlqDxkY){jPdWiUTUCt = true;}
      if(pAikmAgfOz == ABPPGfVcXd){qfLALJLmuQ = true;}
      else if(ABPPGfVcXd == pAikmAgfOz){ImNCGdMOJw = true;}
      if(BWMBqyypos == ryTZPLhIFK){JKofrlMNeR = true;}
      else if(ryTZPLhIFK == BWMBqyypos){ksEmeAPPWn = true;}
      if(spYYBCpkFB == MDfDwaKccs){haJEAGERVS = true;}
      if(ByffYkQkyL == kmeNJShyLb){mCguuHWeao = true;}
      if(XqhugqhrVn == RMPVgKlbyo){PjxfBlgymU = true;}
      while(MDfDwaKccs == spYYBCpkFB){KJsEAyDPHg = true;}
      while(kmeNJShyLb == kmeNJShyLb){dJaHFlqbta = true;}
      while(RMPVgKlbyo == RMPVgKlbyo){bhKDupLqqh = true;}
      if(sIPmQxULSf == true){sIPmQxULSf = false;}
      if(UrAesETFQx == true){UrAesETFQx = false;}
      if(ciwcrzmJWl == true){ciwcrzmJWl = false;}
      if(niemzbWrwL == true){niemzbWrwL = false;}
      if(xWeeHZMkcb == true){xWeeHZMkcb = false;}
      if(qfLALJLmuQ == true){qfLALJLmuQ = false;}
      if(JKofrlMNeR == true){JKofrlMNeR = false;}
      if(haJEAGERVS == true){haJEAGERVS = false;}
      if(mCguuHWeao == true){mCguuHWeao = false;}
      if(PjxfBlgymU == true){PjxfBlgymU = false;}
      if(MyFLtPWGAE == true){MyFLtPWGAE = false;}
      if(FtQbcHdtkj == true){FtQbcHdtkj = false;}
      if(OhlpBxdcCN == true){OhlpBxdcCN = false;}
      if(ZFeAFnxUAf == true){ZFeAFnxUAf = false;}
      if(jPdWiUTUCt == true){jPdWiUTUCt = false;}
      if(ImNCGdMOJw == true){ImNCGdMOJw = false;}
      if(ksEmeAPPWn == true){ksEmeAPPWn = false;}
      if(KJsEAyDPHg == true){KJsEAyDPHg = false;}
      if(dJaHFlqbta == true){dJaHFlqbta = false;}
      if(bhKDupLqqh == true){bhKDupLqqh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWUTUTKCXI
{ 
  void gsYmKbmiGC()
  { 
      bool KgYdyFdoJW = false;
      bool VZGCosaHdE = false;
      bool meZUHwGnjg = false;
      bool hskGdmyzim = false;
      bool FCVstBGYdq = false;
      bool oaEnefHEWC = false;
      bool yoFbnbozYB = false;
      bool taXqykJfZF = false;
      bool ohJrrGnwbx = false;
      bool etcgoPwsES = false;
      bool LHAbwNDNot = false;
      bool WadQNQeMjg = false;
      bool nsXaVAyqBi = false;
      bool nPaHtgghwe = false;
      bool DZHgaDPLSY = false;
      bool jjJXeSjYFu = false;
      bool OLMFGHAWWf = false;
      bool ixPFcNkpAR = false;
      bool kmXczDGDca = false;
      bool xIbAPrNBaT = false;
      string EacYCFfFNN;
      string dpazEwxzMt;
      string YmSDcxEEop;
      string fjsgwaoFgL;
      string TjEHWeGHgJ;
      string pOgfuQIZwE;
      string AaPWhsxtDc;
      string HqSBaniLgx;
      string pxXeAQDMle;
      string SPJbKrUgYc;
      string hLDDCyweFG;
      string gxrzNCDjWR;
      string ojIXKrhqph;
      string TClDOesUcB;
      string UXHexVWJNI;
      string ojKGnyDfrK;
      string QEoXmeKoki;
      string JiGUxQccZo;
      string UXdhsirePP;
      string bNbSjPiirS;
      if(EacYCFfFNN == hLDDCyweFG){KgYdyFdoJW = true;}
      else if(hLDDCyweFG == EacYCFfFNN){LHAbwNDNot = true;}
      if(dpazEwxzMt == gxrzNCDjWR){VZGCosaHdE = true;}
      else if(gxrzNCDjWR == dpazEwxzMt){WadQNQeMjg = true;}
      if(YmSDcxEEop == ojIXKrhqph){meZUHwGnjg = true;}
      else if(ojIXKrhqph == YmSDcxEEop){nsXaVAyqBi = true;}
      if(fjsgwaoFgL == TClDOesUcB){hskGdmyzim = true;}
      else if(TClDOesUcB == fjsgwaoFgL){nPaHtgghwe = true;}
      if(TjEHWeGHgJ == UXHexVWJNI){FCVstBGYdq = true;}
      else if(UXHexVWJNI == TjEHWeGHgJ){DZHgaDPLSY = true;}
      if(pOgfuQIZwE == ojKGnyDfrK){oaEnefHEWC = true;}
      else if(ojKGnyDfrK == pOgfuQIZwE){jjJXeSjYFu = true;}
      if(AaPWhsxtDc == QEoXmeKoki){yoFbnbozYB = true;}
      else if(QEoXmeKoki == AaPWhsxtDc){OLMFGHAWWf = true;}
      if(HqSBaniLgx == JiGUxQccZo){taXqykJfZF = true;}
      if(pxXeAQDMle == UXdhsirePP){ohJrrGnwbx = true;}
      if(SPJbKrUgYc == bNbSjPiirS){etcgoPwsES = true;}
      while(JiGUxQccZo == HqSBaniLgx){ixPFcNkpAR = true;}
      while(UXdhsirePP == UXdhsirePP){kmXczDGDca = true;}
      while(bNbSjPiirS == bNbSjPiirS){xIbAPrNBaT = true;}
      if(KgYdyFdoJW == true){KgYdyFdoJW = false;}
      if(VZGCosaHdE == true){VZGCosaHdE = false;}
      if(meZUHwGnjg == true){meZUHwGnjg = false;}
      if(hskGdmyzim == true){hskGdmyzim = false;}
      if(FCVstBGYdq == true){FCVstBGYdq = false;}
      if(oaEnefHEWC == true){oaEnefHEWC = false;}
      if(yoFbnbozYB == true){yoFbnbozYB = false;}
      if(taXqykJfZF == true){taXqykJfZF = false;}
      if(ohJrrGnwbx == true){ohJrrGnwbx = false;}
      if(etcgoPwsES == true){etcgoPwsES = false;}
      if(LHAbwNDNot == true){LHAbwNDNot = false;}
      if(WadQNQeMjg == true){WadQNQeMjg = false;}
      if(nsXaVAyqBi == true){nsXaVAyqBi = false;}
      if(nPaHtgghwe == true){nPaHtgghwe = false;}
      if(DZHgaDPLSY == true){DZHgaDPLSY = false;}
      if(jjJXeSjYFu == true){jjJXeSjYFu = false;}
      if(OLMFGHAWWf == true){OLMFGHAWWf = false;}
      if(ixPFcNkpAR == true){ixPFcNkpAR = false;}
      if(kmXczDGDca == true){kmXczDGDca = false;}
      if(xIbAPrNBaT == true){xIbAPrNBaT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKHBBOVDPH
{ 
  void RjGotkgsHu()
  { 
      bool NJMhMmEweQ = false;
      bool FMBihnBALh = false;
      bool zGUkquAPTY = false;
      bool ffmooExwGQ = false;
      bool OttRUBllKR = false;
      bool mERYkHnaqR = false;
      bool locFjZYLtc = false;
      bool qEsuTFMDPo = false;
      bool INEBlaOOEg = false;
      bool QVEndZRngt = false;
      bool cZrhahLVFe = false;
      bool ukLBJXjaTI = false;
      bool LJHMLUAEQs = false;
      bool mXVVMhVWaE = false;
      bool PrJYlfKDeF = false;
      bool oqUXhSSfVF = false;
      bool hGELrXOpoa = false;
      bool CMzOsTAhZf = false;
      bool KwZKEwCymt = false;
      bool PoBVWImxgO = false;
      string qxJGurmXoq;
      string YaNZVIqDwK;
      string ObKaxmBRMZ;
      string tEBStfhiWk;
      string JWOUfpGIZz;
      string odueaPmhIH;
      string qVKPwTYufp;
      string aIgKBrMouH;
      string grqNkPJWqd;
      string rzZOtmLzXL;
      string RKcjXgxjci;
      string DxmBaydxdf;
      string KCDBxahRPN;
      string gMRipVPHoE;
      string SYsIatMXmw;
      string JNVrBOHblw;
      string yeTPBpfDLF;
      string iVIZMkItZD;
      string OJdTDTpZha;
      string OnVrGnEcHj;
      if(qxJGurmXoq == RKcjXgxjci){NJMhMmEweQ = true;}
      else if(RKcjXgxjci == qxJGurmXoq){cZrhahLVFe = true;}
      if(YaNZVIqDwK == DxmBaydxdf){FMBihnBALh = true;}
      else if(DxmBaydxdf == YaNZVIqDwK){ukLBJXjaTI = true;}
      if(ObKaxmBRMZ == KCDBxahRPN){zGUkquAPTY = true;}
      else if(KCDBxahRPN == ObKaxmBRMZ){LJHMLUAEQs = true;}
      if(tEBStfhiWk == gMRipVPHoE){ffmooExwGQ = true;}
      else if(gMRipVPHoE == tEBStfhiWk){mXVVMhVWaE = true;}
      if(JWOUfpGIZz == SYsIatMXmw){OttRUBllKR = true;}
      else if(SYsIatMXmw == JWOUfpGIZz){PrJYlfKDeF = true;}
      if(odueaPmhIH == JNVrBOHblw){mERYkHnaqR = true;}
      else if(JNVrBOHblw == odueaPmhIH){oqUXhSSfVF = true;}
      if(qVKPwTYufp == yeTPBpfDLF){locFjZYLtc = true;}
      else if(yeTPBpfDLF == qVKPwTYufp){hGELrXOpoa = true;}
      if(aIgKBrMouH == iVIZMkItZD){qEsuTFMDPo = true;}
      if(grqNkPJWqd == OJdTDTpZha){INEBlaOOEg = true;}
      if(rzZOtmLzXL == OnVrGnEcHj){QVEndZRngt = true;}
      while(iVIZMkItZD == aIgKBrMouH){CMzOsTAhZf = true;}
      while(OJdTDTpZha == OJdTDTpZha){KwZKEwCymt = true;}
      while(OnVrGnEcHj == OnVrGnEcHj){PoBVWImxgO = true;}
      if(NJMhMmEweQ == true){NJMhMmEweQ = false;}
      if(FMBihnBALh == true){FMBihnBALh = false;}
      if(zGUkquAPTY == true){zGUkquAPTY = false;}
      if(ffmooExwGQ == true){ffmooExwGQ = false;}
      if(OttRUBllKR == true){OttRUBllKR = false;}
      if(mERYkHnaqR == true){mERYkHnaqR = false;}
      if(locFjZYLtc == true){locFjZYLtc = false;}
      if(qEsuTFMDPo == true){qEsuTFMDPo = false;}
      if(INEBlaOOEg == true){INEBlaOOEg = false;}
      if(QVEndZRngt == true){QVEndZRngt = false;}
      if(cZrhahLVFe == true){cZrhahLVFe = false;}
      if(ukLBJXjaTI == true){ukLBJXjaTI = false;}
      if(LJHMLUAEQs == true){LJHMLUAEQs = false;}
      if(mXVVMhVWaE == true){mXVVMhVWaE = false;}
      if(PrJYlfKDeF == true){PrJYlfKDeF = false;}
      if(oqUXhSSfVF == true){oqUXhSSfVF = false;}
      if(hGELrXOpoa == true){hGELrXOpoa = false;}
      if(CMzOsTAhZf == true){CMzOsTAhZf = false;}
      if(KwZKEwCymt == true){KwZKEwCymt = false;}
      if(PoBVWImxgO == true){PoBVWImxgO = false;}
    } 
}; 
