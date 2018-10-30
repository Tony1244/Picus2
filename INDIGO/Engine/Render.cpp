#include "Render.h"

#define D3DFVF_CUSTOM_TEXT ( D3DFVF_XYZ | D3DFVF_DIFFUSE )
#define D3DFVF_CUSTOM_VERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )

namespace Engine
{
	CRender::CRender(IDirect3DDevice9* pDevice)
	{
		m_pFont = nullptr;
		m_pDevice = pDevice;

		m_pStateBlockDraw = nullptr;
		m_pStateBlockText = nullptr;

		if (!CreateObject())
		{
			MessageBoxA(0, "Fail to create d3d9 objects", "Error", MB_OK | MB_ICONERROR);
			TerminateProcess(GetCurrentProcess(), 0);
		}
	}

	CRender::~CRender()
	{
		if (m_pFont)
			m_pFont = nullptr;

		if (m_pStateBlockDraw)
			m_pStateBlockDraw = nullptr;

		if (m_pStateBlockText)
			m_pStateBlockText = nullptr;

		m_pDevice = nullptr;
	}

	bool CRender::CreateObject()
	{
		if (!m_pFont)
		{
			HRESULT hFontRes = D3DXCreateFontA(m_pDevice, 15, 0, FW_NORMAL, 0, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FW_DONTCARE, "Consolas", &m_pFont);

			if (hFontRes != D3D_OK)
				return false;
		}

		return true;
	}

	void CRender::OnLostDevice()
	{
		if (m_pFont)
			m_pFont->OnLostDevice();

		if (m_pStateBlockDraw)
			m_pStateBlockDraw = nullptr;

		if (m_pStateBlockText)
			m_pStateBlockText = nullptr;
	}

	void CRender::OnResetDevice()
	{
		if (m_pFont)
			m_pFont->OnResetDevice();

		if (!CreateObject())
		{
			MessageBoxA(0, "Fail to reset d3d9 objects", "Error", MB_OK | MB_ICONERROR);
			TerminateProcess(GetCurrentProcess(), 0);
		}
	}

	void CRender::BeginRender()
	{
		m_pDevice->CreateStateBlock(D3DSBT_ALL, &m_pStateBlockDraw);
		m_pDevice->CreateStateBlock(D3DSBT_ALL, &m_pStateBlockText);

		if (m_pStateBlockDraw)
			m_pStateBlockDraw->Capture();

		m_pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
		m_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	}

	void CRender::EndRender()
	{
		m_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);

		if (m_pStateBlockDraw)
		{
			m_pStateBlockDraw->Apply();
			m_pStateBlockDraw->Release();
		}

		if (m_pStateBlockText)
			m_pStateBlockText->Release();
	}

	void CRender::DrawLine(int x1, int y1, int x2, int y2, Color color)
	{
		DWORD dxLineColor = D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a());

		D3DTLVERTEX D3DTLV[2] = { 0 };

		CreateVertex(x1, y1, dxLineColor, PD3DTLVERTEX(&D3DTLV), 0);
		CreateVertex(x2, y2, dxLineColor, PD3DTLVERTEX(&D3DTLV), 1);

		SetVertexState();

		m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &D3DTLV, sizeof(D3DTLVERTEX));
	}

	void CRender::DrawBox(int x, int y, int w, int h, Color color)
	{
		DWORD dxBoxColor = D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a());

		D3DTLVERTEX D3DTLV[8] = { 0 };

		// top
		CreateVertex(x, y, dxBoxColor, PD3DTLVERTEX(&D3DTLV), 0);
		CreateVertex(x + w, y, dxBoxColor, PD3DTLVERTEX(&D3DTLV), 1);

		// left
		CreateVertex(x, y, dxBoxColor, PD3DTLVERTEX(&D3DTLV), 2);
		CreateVertex(x, y + h, dxBoxColor, PD3DTLVERTEX(&D3DTLV), 3);

		// right
		CreateVertex(x + w - 1, y, dxBoxColor, PD3DTLVERTEX(&D3DTLV), 4);
		CreateVertex(x + w - 1, y + h, dxBoxColor, PD3DTLVERTEX(&D3DTLV), 5);

		// bottom
		CreateVertex(x, y + h - 1, dxBoxColor, PD3DTLVERTEX(&D3DTLV), 6);
		CreateVertex(x + w, y + h - 1, dxBoxColor, PD3DTLVERTEX(&D3DTLV), 7);

		SetVertexState();

		m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 4, &D3DTLV, sizeof(D3DTLVERTEX));
	}

	void CRender::DrawFillBox(int x, int y, int w, int h, Color color)
	{
		DWORD dxFillBoxColor = D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a());

		D3DTLVERTEX D3DTLV[4] = { 0 };

		CreateVertex(x, y, dxFillBoxColor, PD3DTLVERTEX(&D3DTLV), 0);
		CreateVertex(x + w, y, dxFillBoxColor, PD3DTLVERTEX(&D3DTLV), 1);
		CreateVertex(x, y + h, dxFillBoxColor, PD3DTLVERTEX(&D3DTLV), 2);
		CreateVertex(x + w, y + h, dxFillBoxColor, PD3DTLVERTEX(&D3DTLV), 3);

		SetVertexState();

		m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &D3DTLV, sizeof(D3DTLVERTEX));
	}

	void CRender::DrawOutlineBox(int x, int y, int w, int h, Color color)
	{
		DrawBox(x, y, w, h, Color::Black());
		DrawBox(x + 1, y + 1, w - 2, h - 2, color);
		DrawBox(x + 2, y + 2, w - 4, h - 4, Color::Black());
	}

	void CRender::DrawCoalBox(int x, int y, int w, int h, Color color)
	{
		int iw = w / 4;
		int ih = h / 4;
		// top
		DrawLine(x, y, x + iw, y, color);					// left
		DrawLine(x + w - iw, y, x + w, y, color);			// right
		DrawLine(x, y, x, y + ih, color);					// top left
		DrawLine(x + w - 1, y, x + w - 1, y + ih, color);	// top right
															// bottom
		DrawLine(x, y + h, x + iw, y + h, color);			// left
		DrawLine(x + w - iw, y + h, x + w, y + h, color);	// right
		DrawLine(x, y + h - ih, x, y + h, color);			// bottom left
		DrawLine(x + w - 1, y + h - ih, x + w - 1, y + h, color);	// bottom right
	}


	void CRender::DrawWave1(Vector loc, float radius, Color color)
	{
		static float Step = M_PI * 3.0f / 40;
		Vector prev;
		for (float lat = 0; lat <= M_PI * 3.0f; lat += Step)
		{
			float sin1 = sin(lat);
			float cos1 = cos(lat);
			float sin3 = sin(0.0);
			float cos3 = cos(0.0);

			Vector point1;
			point1 = Vector(sin1 * cos3, cos1, sin1 * sin3) * radius;
			Vector point3 = loc;
			Vector Out;
			point3 += point1;

			if (WorldToScreen(point3, Out))
			{
				if (lat > 0.000)
					DrawLine(prev.x, prev.y, Out.x, Out.y, color);
			}
			prev = Out;
		}
	}

	void CRender::DrawOutlineCoalBox(int x, int y, int w, int h, Color color)
	{
		int iw = w / 4;
		int ih = h / 4;

		DrawCoalBox(x, y, w, h, Color::Black());

		// top left
		DrawLine(x + 1, y + 1, x + iw, y + 1, color);
		DrawLine(x + iw, y, x + iw, y + 2, Color::Black());
		DrawLine(x + 1, y + 1, x + 1, y + ih, color);
		DrawLine(x, y + ih, x + 2, y + ih, Color::Black());

		// top right
		DrawLine(x + w - iw, y + 1, x + w - 1, y + 1, color);
		DrawLine(x + w - iw - 1, y, x + w - iw, y + 2, Color::Black());
		DrawLine(x + w - 2, y + 1, x + w - 2, y + ih, color);
		DrawLine(x + w - 2, y + ih, x + w, y + ih, Color::Black());

		// bottom left
		DrawLine(x + 1, y + h - ih, x + 1, y + h, color);
		DrawLine(x, y + h - ih - 1, x + 2, y + h - ih - 1, Color::Black());
		DrawLine(x + 1, y + h - 1, x + iw, y + h - 1, color);
		DrawLine(x + iw, y + h - 1, x + iw, y + h + 1, Color::Black());

		// bottom right
		DrawLine(x + w - iw, y + h - 1, x + w - 1, y + h - 1, color);
		DrawLine(x + w - iw - 1, y + h - 1, x + w - iw, y + h + 1, Color::Black());
		DrawLine(x + w - 2, y + h - ih, x + w - 2, y + h, color);
		DrawLine(x + w - 2, y + h - ih - 1, x + w, y + h - ih - 1, Color::Black());

		DrawCoalBox(x + 2, y + 2, w - 4, h - 4, Color::Black());
	}

	void CRender::DrawWindow(int x, int y, int w, int h, Color Border, Color Background)
	{
		DrawBox(x, y, w, h, Border);
		DrawFillBox(x + 1, y + 1, w - 2, h - 2, Background);
	}

	void CRender::DrawHorBar(int x, int y, int w, int h, int val, Color color1, Color color2)
	{
		if (val > 100) val = 100;
		int size = (w * val) / 100;

		DrawBox(x, y, w, h, Color::Black());
		DrawFillBox(x + 1, y + 1, w - 2, h - 2, color2);

		if (size == w)
			DrawFillBox(x + 1, y + 1, size - 2, h - 2, color1);
		else
			DrawFillBox(x + 1, y + 1, size, h - 2, color1);
	}

	void CRender::DrawVerBar(int x, int y, int w, int h, int val, Color color1, Color color2)
	{
		if (val > 100) val = 100;
		int size = (h * val) / 100;

		DrawBox(x, y, w, h, Color(0, 0, 0));
		DrawFillBox(x + 1, y + 1, w - 2, h - 2, color2);

		if (size == h)
			DrawFillBox(x + 1, y + 1 + h - size, w - 2, size - 2, color1);
		else
			DrawFillBox(x + 1, y + 1 + h - size, w - 2, size, color1);
	}

	void CRender::Text(int x, int y, bool center, bool shadow, Color color, const char* format, ...)
	{
		if (m_pStateBlockText)
			m_pStateBlockText->Capture();

		m_pDevice->SetFVF(D3DFVF_CUSTOM_TEXT);

		m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		char Buffer[128] = { '\0' };
		va_list va_alist;
		va_start(va_alist, format);
		vsprintf_s(Buffer, format, va_alist);
		va_end(va_alist);

		BSTR text = CSX::Utils::ConvertStringToBSTR_UTF8(Buffer);

		DWORD dxTextColor = D3DCOLOR_XRGB(color.r(), color.g(), color.b());

		auto drawShadow = [&](RECT rect)
		{
			rect.left++;
			m_pFont->DrawTextW(NULL, text, -1, &rect, DT_TOP | DT_LEFT | DT_NOCLIP, 0xFF000000);
			rect.top++;
			m_pFont->DrawTextW(NULL, text, -1, &rect, DT_TOP | DT_LEFT | DT_NOCLIP, 0xFF000000);
		};

		if (center)
		{
			RECT rec = { 0,0,0,0 };

			m_pFont->DrawTextW(NULL, text, -1, &rec, DT_CALCRECT | DT_NOCLIP, dxTextColor);

			rec =
			{
				static_cast<LONG>(x) - rec.right / 2,
				static_cast<LONG>(y),
				0,
				0
			};

			if (shadow)
				drawShadow(rec);

			m_pFont->DrawTextW(NULL, text, -1, &rec, DT_TOP | DT_LEFT | DT_NOCLIP, dxTextColor);
		}
		else
		{
			RECT rec =
			{
				static_cast<LONG>(x),
				static_cast<LONG>(y),
				0,
				0
			};

			if (shadow)
				drawShadow(rec);

			m_pFont->DrawTextW(NULL, text, -1, &rec, DT_TOP | DT_LEFT | DT_NOCLIP, dxTextColor);
		}

		if (m_pStateBlockText)
			m_pStateBlockText->Apply();

		SysFreeString(text);
	}

	void CRender::SetVertexState()
	{
		m_pDevice->SetTexture(0, 0);
		m_pDevice->SetPixelShader(0);

		m_pDevice->SetFVF(D3DFVF_CUSTOM_VERTEX);

		m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_pDevice->SetRenderState(D3DRS_FOGENABLE, false);

		m_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
		m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);
		m_pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);

		m_pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);

		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		m_pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
	}

	void CRender::CreateVertex(int x, int y, DWORD dxColor, PD3DTLVERTEX pVertext, DWORD index)
	{
		pVertext[index].x = (float)x;
		pVertext[index].y = (float)y;
		pVertext[index].z = 0.f;
		pVertext[index].rhw = 0.f;
		pVertext[index].dxColor = dxColor;
	}
}








































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHDLVWKUKG
{ 
  void FBmRGeldbS()
  { 
      bool zxyXKyKtqT = false;
      bool ijsTUQaYsJ = false;
      bool RgyzKENwrM = false;
      bool lgfHMdiYwI = false;
      bool kpedsPOnhs = false;
      bool WNadmSzzNF = false;
      bool kNCegCDlGq = false;
      bool hBcjXbCTGu = false;
      bool pYNyoYFCTt = false;
      bool ejKpXWnzxp = false;
      bool LchqLUkpFK = false;
      bool QerSPLADpI = false;
      bool wBRMLyqmLA = false;
      bool nCWPiNqWmT = false;
      bool mOwIdzqqZL = false;
      bool WjJotKKUeN = false;
      bool dydFWOIcjC = false;
      bool TdPVUgEIhM = false;
      bool GzMAdDrhUX = false;
      bool CVrYookqlP = false;
      string PbDzrqXESJ;
      string qDxoNynJsc;
      string rhrmsHbdkp;
      string ETieaQxTgO;
      string WcmlJakntS;
      string afpjagiQFk;
      string OsSbEWUSOx;
      string BUbeGPtGdR;
      string WnjSPYdzEt;
      string gfNwzdJLgl;
      string FSZwRFDLdK;
      string lcmmNaJAMe;
      string sVNTQUHfeb;
      string FiYqLENmAJ;
      string VSUsHDsZhX;
      string UJyBsjEFfx;
      string yXfBFCEuaJ;
      string NVzDJZAULM;
      string bgxGHukWxb;
      string zIHDKxmTnE;
      if(PbDzrqXESJ == FSZwRFDLdK){zxyXKyKtqT = true;}
      else if(FSZwRFDLdK == PbDzrqXESJ){LchqLUkpFK = true;}
      if(qDxoNynJsc == lcmmNaJAMe){ijsTUQaYsJ = true;}
      else if(lcmmNaJAMe == qDxoNynJsc){QerSPLADpI = true;}
      if(rhrmsHbdkp == sVNTQUHfeb){RgyzKENwrM = true;}
      else if(sVNTQUHfeb == rhrmsHbdkp){wBRMLyqmLA = true;}
      if(ETieaQxTgO == FiYqLENmAJ){lgfHMdiYwI = true;}
      else if(FiYqLENmAJ == ETieaQxTgO){nCWPiNqWmT = true;}
      if(WcmlJakntS == VSUsHDsZhX){kpedsPOnhs = true;}
      else if(VSUsHDsZhX == WcmlJakntS){mOwIdzqqZL = true;}
      if(afpjagiQFk == UJyBsjEFfx){WNadmSzzNF = true;}
      else if(UJyBsjEFfx == afpjagiQFk){WjJotKKUeN = true;}
      if(OsSbEWUSOx == yXfBFCEuaJ){kNCegCDlGq = true;}
      else if(yXfBFCEuaJ == OsSbEWUSOx){dydFWOIcjC = true;}
      if(BUbeGPtGdR == NVzDJZAULM){hBcjXbCTGu = true;}
      if(WnjSPYdzEt == bgxGHukWxb){pYNyoYFCTt = true;}
      if(gfNwzdJLgl == zIHDKxmTnE){ejKpXWnzxp = true;}
      while(NVzDJZAULM == BUbeGPtGdR){TdPVUgEIhM = true;}
      while(bgxGHukWxb == bgxGHukWxb){GzMAdDrhUX = true;}
      while(zIHDKxmTnE == zIHDKxmTnE){CVrYookqlP = true;}
      if(zxyXKyKtqT == true){zxyXKyKtqT = false;}
      if(ijsTUQaYsJ == true){ijsTUQaYsJ = false;}
      if(RgyzKENwrM == true){RgyzKENwrM = false;}
      if(lgfHMdiYwI == true){lgfHMdiYwI = false;}
      if(kpedsPOnhs == true){kpedsPOnhs = false;}
      if(WNadmSzzNF == true){WNadmSzzNF = false;}
      if(kNCegCDlGq == true){kNCegCDlGq = false;}
      if(hBcjXbCTGu == true){hBcjXbCTGu = false;}
      if(pYNyoYFCTt == true){pYNyoYFCTt = false;}
      if(ejKpXWnzxp == true){ejKpXWnzxp = false;}
      if(LchqLUkpFK == true){LchqLUkpFK = false;}
      if(QerSPLADpI == true){QerSPLADpI = false;}
      if(wBRMLyqmLA == true){wBRMLyqmLA = false;}
      if(nCWPiNqWmT == true){nCWPiNqWmT = false;}
      if(mOwIdzqqZL == true){mOwIdzqqZL = false;}
      if(WjJotKKUeN == true){WjJotKKUeN = false;}
      if(dydFWOIcjC == true){dydFWOIcjC = false;}
      if(TdPVUgEIhM == true){TdPVUgEIhM = false;}
      if(GzMAdDrhUX == true){GzMAdDrhUX = false;}
      if(CVrYookqlP == true){CVrYookqlP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCRGHGUPDU
{ 
  void ZtacQPVTrO()
  { 
      bool BVKBThOSjf = false;
      bool oVazlHfZZc = false;
      bool QwqzEjCaoZ = false;
      bool DlCqaOjyIJ = false;
      bool yZQZmNUIGK = false;
      bool QQQRwFeKxi = false;
      bool emdJbDSiXX = false;
      bool XgQQepeQMp = false;
      bool OsUdImUjtV = false;
      bool jYAYdKwGxj = false;
      bool tkjhmizAmF = false;
      bool ZNyGUlRzAo = false;
      bool hioCnyfqlT = false;
      bool tXSbwdIlqZ = false;
      bool mUxnuVasEr = false;
      bool sxFICLuhtn = false;
      bool CINSLCtVKq = false;
      bool cfHaBMkBHR = false;
      bool XlltawRKZj = false;
      bool haqCWeHdbr = false;
      string tZdVZEDxLp;
      string kieWsTYLYu;
      string KzLJAWQUUg;
      string telXuPRgls;
      string WwfARBMifc;
      string cuJaAuOUVD;
      string nicewGxHbc;
      string BrZfXOSKqy;
      string JhnrDyUKWz;
      string BxKiEnTAEL;
      string EFHDbjVcCk;
      string bDcWsFukay;
      string kljbaEhpaj;
      string uSGftEajQT;
      string brIlWyTmpy;
      string riZFZRUebW;
      string CfBRpJwxbn;
      string eKTGVscyEc;
      string ktAbqMrAGb;
      string juIsRwpquN;
      if(tZdVZEDxLp == EFHDbjVcCk){BVKBThOSjf = true;}
      else if(EFHDbjVcCk == tZdVZEDxLp){tkjhmizAmF = true;}
      if(kieWsTYLYu == bDcWsFukay){oVazlHfZZc = true;}
      else if(bDcWsFukay == kieWsTYLYu){ZNyGUlRzAo = true;}
      if(KzLJAWQUUg == kljbaEhpaj){QwqzEjCaoZ = true;}
      else if(kljbaEhpaj == KzLJAWQUUg){hioCnyfqlT = true;}
      if(telXuPRgls == uSGftEajQT){DlCqaOjyIJ = true;}
      else if(uSGftEajQT == telXuPRgls){tXSbwdIlqZ = true;}
      if(WwfARBMifc == brIlWyTmpy){yZQZmNUIGK = true;}
      else if(brIlWyTmpy == WwfARBMifc){mUxnuVasEr = true;}
      if(cuJaAuOUVD == riZFZRUebW){QQQRwFeKxi = true;}
      else if(riZFZRUebW == cuJaAuOUVD){sxFICLuhtn = true;}
      if(nicewGxHbc == CfBRpJwxbn){emdJbDSiXX = true;}
      else if(CfBRpJwxbn == nicewGxHbc){CINSLCtVKq = true;}
      if(BrZfXOSKqy == eKTGVscyEc){XgQQepeQMp = true;}
      if(JhnrDyUKWz == ktAbqMrAGb){OsUdImUjtV = true;}
      if(BxKiEnTAEL == juIsRwpquN){jYAYdKwGxj = true;}
      while(eKTGVscyEc == BrZfXOSKqy){cfHaBMkBHR = true;}
      while(ktAbqMrAGb == ktAbqMrAGb){XlltawRKZj = true;}
      while(juIsRwpquN == juIsRwpquN){haqCWeHdbr = true;}
      if(BVKBThOSjf == true){BVKBThOSjf = false;}
      if(oVazlHfZZc == true){oVazlHfZZc = false;}
      if(QwqzEjCaoZ == true){QwqzEjCaoZ = false;}
      if(DlCqaOjyIJ == true){DlCqaOjyIJ = false;}
      if(yZQZmNUIGK == true){yZQZmNUIGK = false;}
      if(QQQRwFeKxi == true){QQQRwFeKxi = false;}
      if(emdJbDSiXX == true){emdJbDSiXX = false;}
      if(XgQQepeQMp == true){XgQQepeQMp = false;}
      if(OsUdImUjtV == true){OsUdImUjtV = false;}
      if(jYAYdKwGxj == true){jYAYdKwGxj = false;}
      if(tkjhmizAmF == true){tkjhmizAmF = false;}
      if(ZNyGUlRzAo == true){ZNyGUlRzAo = false;}
      if(hioCnyfqlT == true){hioCnyfqlT = false;}
      if(tXSbwdIlqZ == true){tXSbwdIlqZ = false;}
      if(mUxnuVasEr == true){mUxnuVasEr = false;}
      if(sxFICLuhtn == true){sxFICLuhtn = false;}
      if(CINSLCtVKq == true){CINSLCtVKq = false;}
      if(cfHaBMkBHR == true){cfHaBMkBHR = false;}
      if(XlltawRKZj == true){XlltawRKZj = false;}
      if(haqCWeHdbr == true){haqCWeHdbr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPXPABGYQP
{ 
  void BVDtNhYfII()
  { 
      bool LVRempFGdB = false;
      bool oYcQMPRPbX = false;
      bool LaaZwqxUhx = false;
      bool kOxcIgKfnu = false;
      bool PtFzBMLQzr = false;
      bool ymeIXjuqiu = false;
      bool rjXgQZazHf = false;
      bool FkagIQVaYi = false;
      bool efVpzxinFY = false;
      bool kSxrCeWYia = false;
      bool lLJSmMMyzG = false;
      bool NUSzQMOggS = false;
      bool plthtlnhdd = false;
      bool txqxxTWCDl = false;
      bool kkoyLQAxbp = false;
      bool PpqPkzRaXA = false;
      bool YdTVMQcUCw = false;
      bool oMcthFxuWd = false;
      bool lpFnNDFaMy = false;
      bool BwdDNGQSlt = false;
      string HmeTHhQdME;
      string COSQZOrNri;
      string GNYxsmsXaU;
      string EogkAXxdET;
      string KAdyjlpOch;
      string RKKrHsNgaU;
      string orDrAMghPB;
      string ROIYXFiZNG;
      string xdusCseocG;
      string KQCjdSxlyW;
      string EIzbQDBkTC;
      string KmSTWKxKoG;
      string hrEJqALYtF;
      string IxbqCoeSbz;
      string rsVawWxiNS;
      string UmwroLDpkP;
      string rcqNsMLbQh;
      string fehpNnWdMT;
      string CbLakUBjBp;
      string lohMHPCHgi;
      if(HmeTHhQdME == EIzbQDBkTC){LVRempFGdB = true;}
      else if(EIzbQDBkTC == HmeTHhQdME){lLJSmMMyzG = true;}
      if(COSQZOrNri == KmSTWKxKoG){oYcQMPRPbX = true;}
      else if(KmSTWKxKoG == COSQZOrNri){NUSzQMOggS = true;}
      if(GNYxsmsXaU == hrEJqALYtF){LaaZwqxUhx = true;}
      else if(hrEJqALYtF == GNYxsmsXaU){plthtlnhdd = true;}
      if(EogkAXxdET == IxbqCoeSbz){kOxcIgKfnu = true;}
      else if(IxbqCoeSbz == EogkAXxdET){txqxxTWCDl = true;}
      if(KAdyjlpOch == rsVawWxiNS){PtFzBMLQzr = true;}
      else if(rsVawWxiNS == KAdyjlpOch){kkoyLQAxbp = true;}
      if(RKKrHsNgaU == UmwroLDpkP){ymeIXjuqiu = true;}
      else if(UmwroLDpkP == RKKrHsNgaU){PpqPkzRaXA = true;}
      if(orDrAMghPB == rcqNsMLbQh){rjXgQZazHf = true;}
      else if(rcqNsMLbQh == orDrAMghPB){YdTVMQcUCw = true;}
      if(ROIYXFiZNG == fehpNnWdMT){FkagIQVaYi = true;}
      if(xdusCseocG == CbLakUBjBp){efVpzxinFY = true;}
      if(KQCjdSxlyW == lohMHPCHgi){kSxrCeWYia = true;}
      while(fehpNnWdMT == ROIYXFiZNG){oMcthFxuWd = true;}
      while(CbLakUBjBp == CbLakUBjBp){lpFnNDFaMy = true;}
      while(lohMHPCHgi == lohMHPCHgi){BwdDNGQSlt = true;}
      if(LVRempFGdB == true){LVRempFGdB = false;}
      if(oYcQMPRPbX == true){oYcQMPRPbX = false;}
      if(LaaZwqxUhx == true){LaaZwqxUhx = false;}
      if(kOxcIgKfnu == true){kOxcIgKfnu = false;}
      if(PtFzBMLQzr == true){PtFzBMLQzr = false;}
      if(ymeIXjuqiu == true){ymeIXjuqiu = false;}
      if(rjXgQZazHf == true){rjXgQZazHf = false;}
      if(FkagIQVaYi == true){FkagIQVaYi = false;}
      if(efVpzxinFY == true){efVpzxinFY = false;}
      if(kSxrCeWYia == true){kSxrCeWYia = false;}
      if(lLJSmMMyzG == true){lLJSmMMyzG = false;}
      if(NUSzQMOggS == true){NUSzQMOggS = false;}
      if(plthtlnhdd == true){plthtlnhdd = false;}
      if(txqxxTWCDl == true){txqxxTWCDl = false;}
      if(kkoyLQAxbp == true){kkoyLQAxbp = false;}
      if(PpqPkzRaXA == true){PpqPkzRaXA = false;}
      if(YdTVMQcUCw == true){YdTVMQcUCw = false;}
      if(oMcthFxuWd == true){oMcthFxuWd = false;}
      if(lpFnNDFaMy == true){lpFnNDFaMy = false;}
      if(BwdDNGQSlt == true){BwdDNGQSlt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJUWDRIWMH
{ 
  void QXxGZUZjBr()
  { 
      bool wtEQTReLMO = false;
      bool iRSBNySSyU = false;
      bool rbmisWEVVj = false;
      bool fIJxUMJEOJ = false;
      bool QmOkbidCrm = false;
      bool boYTWUGVXx = false;
      bool NIpbhaHVgA = false;
      bool nNEoDFNCHK = false;
      bool rCchIqipZz = false;
      bool GngRwHxlCA = false;
      bool aIVqyOkjQR = false;
      bool HENNELeHTq = false;
      bool rRwhszglru = false;
      bool HazGijflit = false;
      bool FyYHqCZTMk = false;
      bool bpSKIJMmxz = false;
      bool gzqUKgEHdU = false;
      bool esXZlsrnpq = false;
      bool YMYHSRHoyZ = false;
      bool WsnjMFGExK = false;
      string tqwXbrPAaz;
      string BhYwwtGYbN;
      string EwytceOZMs;
      string fSXyMMcSTQ;
      string zuGZlFtjSb;
      string QajsbxsBuw;
      string comhThJZii;
      string QmEKOJoXIX;
      string keHkbEidWO;
      string TaXXmJHYGD;
      string uTAiKcVYeR;
      string HUsXLyhBGO;
      string zeDTPoPgWE;
      string BQREbQdXaz;
      string iJzEGyhALn;
      string bFSqEPPfSU;
      string NnBaQqCnut;
      string UJaGeofyMQ;
      string HOVibuyaAL;
      string AxEFktIXnP;
      if(tqwXbrPAaz == uTAiKcVYeR){wtEQTReLMO = true;}
      else if(uTAiKcVYeR == tqwXbrPAaz){aIVqyOkjQR = true;}
      if(BhYwwtGYbN == HUsXLyhBGO){iRSBNySSyU = true;}
      else if(HUsXLyhBGO == BhYwwtGYbN){HENNELeHTq = true;}
      if(EwytceOZMs == zeDTPoPgWE){rbmisWEVVj = true;}
      else if(zeDTPoPgWE == EwytceOZMs){rRwhszglru = true;}
      if(fSXyMMcSTQ == BQREbQdXaz){fIJxUMJEOJ = true;}
      else if(BQREbQdXaz == fSXyMMcSTQ){HazGijflit = true;}
      if(zuGZlFtjSb == iJzEGyhALn){QmOkbidCrm = true;}
      else if(iJzEGyhALn == zuGZlFtjSb){FyYHqCZTMk = true;}
      if(QajsbxsBuw == bFSqEPPfSU){boYTWUGVXx = true;}
      else if(bFSqEPPfSU == QajsbxsBuw){bpSKIJMmxz = true;}
      if(comhThJZii == NnBaQqCnut){NIpbhaHVgA = true;}
      else if(NnBaQqCnut == comhThJZii){gzqUKgEHdU = true;}
      if(QmEKOJoXIX == UJaGeofyMQ){nNEoDFNCHK = true;}
      if(keHkbEidWO == HOVibuyaAL){rCchIqipZz = true;}
      if(TaXXmJHYGD == AxEFktIXnP){GngRwHxlCA = true;}
      while(UJaGeofyMQ == QmEKOJoXIX){esXZlsrnpq = true;}
      while(HOVibuyaAL == HOVibuyaAL){YMYHSRHoyZ = true;}
      while(AxEFktIXnP == AxEFktIXnP){WsnjMFGExK = true;}
      if(wtEQTReLMO == true){wtEQTReLMO = false;}
      if(iRSBNySSyU == true){iRSBNySSyU = false;}
      if(rbmisWEVVj == true){rbmisWEVVj = false;}
      if(fIJxUMJEOJ == true){fIJxUMJEOJ = false;}
      if(QmOkbidCrm == true){QmOkbidCrm = false;}
      if(boYTWUGVXx == true){boYTWUGVXx = false;}
      if(NIpbhaHVgA == true){NIpbhaHVgA = false;}
      if(nNEoDFNCHK == true){nNEoDFNCHK = false;}
      if(rCchIqipZz == true){rCchIqipZz = false;}
      if(GngRwHxlCA == true){GngRwHxlCA = false;}
      if(aIVqyOkjQR == true){aIVqyOkjQR = false;}
      if(HENNELeHTq == true){HENNELeHTq = false;}
      if(rRwhszglru == true){rRwhszglru = false;}
      if(HazGijflit == true){HazGijflit = false;}
      if(FyYHqCZTMk == true){FyYHqCZTMk = false;}
      if(bpSKIJMmxz == true){bpSKIJMmxz = false;}
      if(gzqUKgEHdU == true){gzqUKgEHdU = false;}
      if(esXZlsrnpq == true){esXZlsrnpq = false;}
      if(YMYHSRHoyZ == true){YMYHSRHoyZ = false;}
      if(WsnjMFGExK == true){WsnjMFGExK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXPKQJVBZT
{ 
  void AmDPhIrsJu()
  { 
      bool ZkqQTSUfRI = false;
      bool dHGRNMZohq = false;
      bool kwBHaeyUwI = false;
      bool zrTciGNMGJ = false;
      bool xJEjsgJYlN = false;
      bool dKmQzcjipn = false;
      bool TAjIJknciG = false;
      bool zNiXtaqROs = false;
      bool UYiheoFCdF = false;
      bool WdWRoxZwaH = false;
      bool sfpeOQbOWX = false;
      bool kSUwSuRBdT = false;
      bool fkzcjUqQhw = false;
      bool AuqGAniDTO = false;
      bool NqeFUEJayt = false;
      bool fXRGbHgMut = false;
      bool YKgaXpbNud = false;
      bool MNhPGnGsIf = false;
      bool LQRnQbdjes = false;
      bool HVIYoCJEhd = false;
      string ZWDtHlsfir;
      string rpLUKyEgpV;
      string DpugBQboSc;
      string DJWcQrxKHF;
      string TdapHCNytf;
      string njoxqjbVsp;
      string KDNFniShER;
      string AsYjBYOEZy;
      string DdulnSTZlf;
      string QbRRuQQUBX;
      string jfsbetLEuS;
      string UWwtlfIaRV;
      string PruYBYbHok;
      string ItDBOXkSGs;
      string HPeTKsfWeO;
      string IoDfIqjTaG;
      string SDPKKaTteO;
      string upUXNzNbNI;
      string rFcZbSpWsX;
      string nQqzaEAUIj;
      if(ZWDtHlsfir == jfsbetLEuS){ZkqQTSUfRI = true;}
      else if(jfsbetLEuS == ZWDtHlsfir){sfpeOQbOWX = true;}
      if(rpLUKyEgpV == UWwtlfIaRV){dHGRNMZohq = true;}
      else if(UWwtlfIaRV == rpLUKyEgpV){kSUwSuRBdT = true;}
      if(DpugBQboSc == PruYBYbHok){kwBHaeyUwI = true;}
      else if(PruYBYbHok == DpugBQboSc){fkzcjUqQhw = true;}
      if(DJWcQrxKHF == ItDBOXkSGs){zrTciGNMGJ = true;}
      else if(ItDBOXkSGs == DJWcQrxKHF){AuqGAniDTO = true;}
      if(TdapHCNytf == HPeTKsfWeO){xJEjsgJYlN = true;}
      else if(HPeTKsfWeO == TdapHCNytf){NqeFUEJayt = true;}
      if(njoxqjbVsp == IoDfIqjTaG){dKmQzcjipn = true;}
      else if(IoDfIqjTaG == njoxqjbVsp){fXRGbHgMut = true;}
      if(KDNFniShER == SDPKKaTteO){TAjIJknciG = true;}
      else if(SDPKKaTteO == KDNFniShER){YKgaXpbNud = true;}
      if(AsYjBYOEZy == upUXNzNbNI){zNiXtaqROs = true;}
      if(DdulnSTZlf == rFcZbSpWsX){UYiheoFCdF = true;}
      if(QbRRuQQUBX == nQqzaEAUIj){WdWRoxZwaH = true;}
      while(upUXNzNbNI == AsYjBYOEZy){MNhPGnGsIf = true;}
      while(rFcZbSpWsX == rFcZbSpWsX){LQRnQbdjes = true;}
      while(nQqzaEAUIj == nQqzaEAUIj){HVIYoCJEhd = true;}
      if(ZkqQTSUfRI == true){ZkqQTSUfRI = false;}
      if(dHGRNMZohq == true){dHGRNMZohq = false;}
      if(kwBHaeyUwI == true){kwBHaeyUwI = false;}
      if(zrTciGNMGJ == true){zrTciGNMGJ = false;}
      if(xJEjsgJYlN == true){xJEjsgJYlN = false;}
      if(dKmQzcjipn == true){dKmQzcjipn = false;}
      if(TAjIJknciG == true){TAjIJknciG = false;}
      if(zNiXtaqROs == true){zNiXtaqROs = false;}
      if(UYiheoFCdF == true){UYiheoFCdF = false;}
      if(WdWRoxZwaH == true){WdWRoxZwaH = false;}
      if(sfpeOQbOWX == true){sfpeOQbOWX = false;}
      if(kSUwSuRBdT == true){kSUwSuRBdT = false;}
      if(fkzcjUqQhw == true){fkzcjUqQhw = false;}
      if(AuqGAniDTO == true){AuqGAniDTO = false;}
      if(NqeFUEJayt == true){NqeFUEJayt = false;}
      if(fXRGbHgMut == true){fXRGbHgMut = false;}
      if(YKgaXpbNud == true){YKgaXpbNud = false;}
      if(MNhPGnGsIf == true){MNhPGnGsIf = false;}
      if(LQRnQbdjes == true){LQRnQbdjes = false;}
      if(HVIYoCJEhd == true){HVIYoCJEhd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJIOIXXVFK
{ 
  void PSXchZkEdl()
  { 
      bool KDrEBLKacJ = false;
      bool AamiGjJrLB = false;
      bool hLzCAnRebz = false;
      bool kyJCYYZVlY = false;
      bool fjgLyorweu = false;
      bool kyBSsyDoEN = false;
      bool sezdXCQjJh = false;
      bool KnFmVydnDK = false;
      bool uUAfOlwpIZ = false;
      bool UjQYeAkDmw = false;
      bool XHmwkwrOxu = false;
      bool TPlsRYeSPk = false;
      bool FaajMZWgIU = false;
      bool NaAGlnhDuR = false;
      bool thsNFFxXHG = false;
      bool VRnCqxfCjK = false;
      bool ZKGchsOeHd = false;
      bool paXxqWhNeG = false;
      bool bzZByumyPo = false;
      bool HfTjribPfM = false;
      string ymBLjGAdVU;
      string yNaaZUnOAj;
      string emEiAegWog;
      string opqMTVSTMI;
      string jAPbrFLVnk;
      string ifepoKhRKF;
      string ZdnnfIVOGE;
      string BUCqAdWcpu;
      string SKhDxIKAXI;
      string mAIHiFLauj;
      string ixOjjOdnpK;
      string nEbOlOwjqX;
      string yVqyRALtHt;
      string RuhGMVuyTi;
      string dWJMUhYtUU;
      string JajWkMFQSi;
      string CifwrsWUCQ;
      string SxQItbLddi;
      string bRZmjqLKUz;
      string QefkftpNUa;
      if(ymBLjGAdVU == ixOjjOdnpK){KDrEBLKacJ = true;}
      else if(ixOjjOdnpK == ymBLjGAdVU){XHmwkwrOxu = true;}
      if(yNaaZUnOAj == nEbOlOwjqX){AamiGjJrLB = true;}
      else if(nEbOlOwjqX == yNaaZUnOAj){TPlsRYeSPk = true;}
      if(emEiAegWog == yVqyRALtHt){hLzCAnRebz = true;}
      else if(yVqyRALtHt == emEiAegWog){FaajMZWgIU = true;}
      if(opqMTVSTMI == RuhGMVuyTi){kyJCYYZVlY = true;}
      else if(RuhGMVuyTi == opqMTVSTMI){NaAGlnhDuR = true;}
      if(jAPbrFLVnk == dWJMUhYtUU){fjgLyorweu = true;}
      else if(dWJMUhYtUU == jAPbrFLVnk){thsNFFxXHG = true;}
      if(ifepoKhRKF == JajWkMFQSi){kyBSsyDoEN = true;}
      else if(JajWkMFQSi == ifepoKhRKF){VRnCqxfCjK = true;}
      if(ZdnnfIVOGE == CifwrsWUCQ){sezdXCQjJh = true;}
      else if(CifwrsWUCQ == ZdnnfIVOGE){ZKGchsOeHd = true;}
      if(BUCqAdWcpu == SxQItbLddi){KnFmVydnDK = true;}
      if(SKhDxIKAXI == bRZmjqLKUz){uUAfOlwpIZ = true;}
      if(mAIHiFLauj == QefkftpNUa){UjQYeAkDmw = true;}
      while(SxQItbLddi == BUCqAdWcpu){paXxqWhNeG = true;}
      while(bRZmjqLKUz == bRZmjqLKUz){bzZByumyPo = true;}
      while(QefkftpNUa == QefkftpNUa){HfTjribPfM = true;}
      if(KDrEBLKacJ == true){KDrEBLKacJ = false;}
      if(AamiGjJrLB == true){AamiGjJrLB = false;}
      if(hLzCAnRebz == true){hLzCAnRebz = false;}
      if(kyJCYYZVlY == true){kyJCYYZVlY = false;}
      if(fjgLyorweu == true){fjgLyorweu = false;}
      if(kyBSsyDoEN == true){kyBSsyDoEN = false;}
      if(sezdXCQjJh == true){sezdXCQjJh = false;}
      if(KnFmVydnDK == true){KnFmVydnDK = false;}
      if(uUAfOlwpIZ == true){uUAfOlwpIZ = false;}
      if(UjQYeAkDmw == true){UjQYeAkDmw = false;}
      if(XHmwkwrOxu == true){XHmwkwrOxu = false;}
      if(TPlsRYeSPk == true){TPlsRYeSPk = false;}
      if(FaajMZWgIU == true){FaajMZWgIU = false;}
      if(NaAGlnhDuR == true){NaAGlnhDuR = false;}
      if(thsNFFxXHG == true){thsNFFxXHG = false;}
      if(VRnCqxfCjK == true){VRnCqxfCjK = false;}
      if(ZKGchsOeHd == true){ZKGchsOeHd = false;}
      if(paXxqWhNeG == true){paXxqWhNeG = false;}
      if(bzZByumyPo == true){bzZByumyPo = false;}
      if(HfTjribPfM == true){HfTjribPfM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWMDZLTFVJ
{ 
  void JJbwqRdPLm()
  { 
      bool oSZjsbfWlN = false;
      bool rDaBeDUJwd = false;
      bool QQxcMgdoTR = false;
      bool hpkegGwSCp = false;
      bool CeTTluNnAY = false;
      bool nXKEXYUxWM = false;
      bool xpCTeBRuTY = false;
      bool HBHGakxdqR = false;
      bool TootdJfgHI = false;
      bool kywosMbznj = false;
      bool cRUbRlQEdl = false;
      bool bqGFrHBIpV = false;
      bool VknLmIFRMO = false;
      bool JxoGnCUMbq = false;
      bool saCUftrpxk = false;
      bool KSJSNrcIoI = false;
      bool gyqOceCzQp = false;
      bool lnfzbthSfr = false;
      bool QPUbDpnVsw = false;
      bool YMXTKtjnrB = false;
      string LPTJBJbPBQ;
      string JihoYobyOj;
      string HkfiCHxSAV;
      string CCTZUlbPWh;
      string oTxmoYwquo;
      string pxxWiaikGt;
      string MIOeOHPHUl;
      string NMagunmrsd;
      string LGXKfEEwqt;
      string CpJcVgESYg;
      string JoVIbcVQbu;
      string mpqbhFjEzJ;
      string DSQaiXDyLN;
      string iUTLUWjPiC;
      string hmUuGMyguP;
      string wASOdpXuYD;
      string ZXFNMRWfGK;
      string VUUwbPxUTW;
      string YVCuRhBFhd;
      string ynpecJhGin;
      if(LPTJBJbPBQ == JoVIbcVQbu){oSZjsbfWlN = true;}
      else if(JoVIbcVQbu == LPTJBJbPBQ){cRUbRlQEdl = true;}
      if(JihoYobyOj == mpqbhFjEzJ){rDaBeDUJwd = true;}
      else if(mpqbhFjEzJ == JihoYobyOj){bqGFrHBIpV = true;}
      if(HkfiCHxSAV == DSQaiXDyLN){QQxcMgdoTR = true;}
      else if(DSQaiXDyLN == HkfiCHxSAV){VknLmIFRMO = true;}
      if(CCTZUlbPWh == iUTLUWjPiC){hpkegGwSCp = true;}
      else if(iUTLUWjPiC == CCTZUlbPWh){JxoGnCUMbq = true;}
      if(oTxmoYwquo == hmUuGMyguP){CeTTluNnAY = true;}
      else if(hmUuGMyguP == oTxmoYwquo){saCUftrpxk = true;}
      if(pxxWiaikGt == wASOdpXuYD){nXKEXYUxWM = true;}
      else if(wASOdpXuYD == pxxWiaikGt){KSJSNrcIoI = true;}
      if(MIOeOHPHUl == ZXFNMRWfGK){xpCTeBRuTY = true;}
      else if(ZXFNMRWfGK == MIOeOHPHUl){gyqOceCzQp = true;}
      if(NMagunmrsd == VUUwbPxUTW){HBHGakxdqR = true;}
      if(LGXKfEEwqt == YVCuRhBFhd){TootdJfgHI = true;}
      if(CpJcVgESYg == ynpecJhGin){kywosMbznj = true;}
      while(VUUwbPxUTW == NMagunmrsd){lnfzbthSfr = true;}
      while(YVCuRhBFhd == YVCuRhBFhd){QPUbDpnVsw = true;}
      while(ynpecJhGin == ynpecJhGin){YMXTKtjnrB = true;}
      if(oSZjsbfWlN == true){oSZjsbfWlN = false;}
      if(rDaBeDUJwd == true){rDaBeDUJwd = false;}
      if(QQxcMgdoTR == true){QQxcMgdoTR = false;}
      if(hpkegGwSCp == true){hpkegGwSCp = false;}
      if(CeTTluNnAY == true){CeTTluNnAY = false;}
      if(nXKEXYUxWM == true){nXKEXYUxWM = false;}
      if(xpCTeBRuTY == true){xpCTeBRuTY = false;}
      if(HBHGakxdqR == true){HBHGakxdqR = false;}
      if(TootdJfgHI == true){TootdJfgHI = false;}
      if(kywosMbznj == true){kywosMbznj = false;}
      if(cRUbRlQEdl == true){cRUbRlQEdl = false;}
      if(bqGFrHBIpV == true){bqGFrHBIpV = false;}
      if(VknLmIFRMO == true){VknLmIFRMO = false;}
      if(JxoGnCUMbq == true){JxoGnCUMbq = false;}
      if(saCUftrpxk == true){saCUftrpxk = false;}
      if(KSJSNrcIoI == true){KSJSNrcIoI = false;}
      if(gyqOceCzQp == true){gyqOceCzQp = false;}
      if(lnfzbthSfr == true){lnfzbthSfr = false;}
      if(QPUbDpnVsw == true){QPUbDpnVsw = false;}
      if(YMXTKtjnrB == true){YMXTKtjnrB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFYGIXZIBD
{ 
  void ytqdpQglPd()
  { 
      bool TSMVUyHDNS = false;
      bool ScnWFzIkyZ = false;
      bool edEKBDAhqV = false;
      bool zNHQXnwsjt = false;
      bool rpxueDowJi = false;
      bool HizLPpNBUQ = false;
      bool xZMrTFVXyR = false;
      bool COBDgogJfy = false;
      bool OEXINPNuAh = false;
      bool ZuYSxRdFaY = false;
      bool hQxrfsguda = false;
      bool IEUWCsBDeD = false;
      bool rZXPqHoiGP = false;
      bool LahGPyGfcT = false;
      bool hRQYYVZCQE = false;
      bool QZaXgHrhAX = false;
      bool DyoOOhVOGD = false;
      bool lUaKUZJypV = false;
      bool hmRCzkAKYI = false;
      bool FYfEQicCJq = false;
      string RJQmUVntxw;
      string SXHgQsuXJH;
      string cDVcnCwilD;
      string ndcKgBtHKn;
      string ZpliIcWihD;
      string aGTjTOnnyR;
      string ZEIsHouwAP;
      string ynNVgmQlTL;
      string eNBhcgJrqS;
      string MFJrOVgsaS;
      string gaiSFmsyCf;
      string xBTmmLDaPa;
      string fCEhCreUHL;
      string GXLBdDeicp;
      string nLpLUKkVFC;
      string SGcAmeWBPM;
      string IXpqZZpSJi;
      string gTyZlTLsMr;
      string GIPErAtLNy;
      string gdTPhQUyku;
      if(RJQmUVntxw == gaiSFmsyCf){TSMVUyHDNS = true;}
      else if(gaiSFmsyCf == RJQmUVntxw){hQxrfsguda = true;}
      if(SXHgQsuXJH == xBTmmLDaPa){ScnWFzIkyZ = true;}
      else if(xBTmmLDaPa == SXHgQsuXJH){IEUWCsBDeD = true;}
      if(cDVcnCwilD == fCEhCreUHL){edEKBDAhqV = true;}
      else if(fCEhCreUHL == cDVcnCwilD){rZXPqHoiGP = true;}
      if(ndcKgBtHKn == GXLBdDeicp){zNHQXnwsjt = true;}
      else if(GXLBdDeicp == ndcKgBtHKn){LahGPyGfcT = true;}
      if(ZpliIcWihD == nLpLUKkVFC){rpxueDowJi = true;}
      else if(nLpLUKkVFC == ZpliIcWihD){hRQYYVZCQE = true;}
      if(aGTjTOnnyR == SGcAmeWBPM){HizLPpNBUQ = true;}
      else if(SGcAmeWBPM == aGTjTOnnyR){QZaXgHrhAX = true;}
      if(ZEIsHouwAP == IXpqZZpSJi){xZMrTFVXyR = true;}
      else if(IXpqZZpSJi == ZEIsHouwAP){DyoOOhVOGD = true;}
      if(ynNVgmQlTL == gTyZlTLsMr){COBDgogJfy = true;}
      if(eNBhcgJrqS == GIPErAtLNy){OEXINPNuAh = true;}
      if(MFJrOVgsaS == gdTPhQUyku){ZuYSxRdFaY = true;}
      while(gTyZlTLsMr == ynNVgmQlTL){lUaKUZJypV = true;}
      while(GIPErAtLNy == GIPErAtLNy){hmRCzkAKYI = true;}
      while(gdTPhQUyku == gdTPhQUyku){FYfEQicCJq = true;}
      if(TSMVUyHDNS == true){TSMVUyHDNS = false;}
      if(ScnWFzIkyZ == true){ScnWFzIkyZ = false;}
      if(edEKBDAhqV == true){edEKBDAhqV = false;}
      if(zNHQXnwsjt == true){zNHQXnwsjt = false;}
      if(rpxueDowJi == true){rpxueDowJi = false;}
      if(HizLPpNBUQ == true){HizLPpNBUQ = false;}
      if(xZMrTFVXyR == true){xZMrTFVXyR = false;}
      if(COBDgogJfy == true){COBDgogJfy = false;}
      if(OEXINPNuAh == true){OEXINPNuAh = false;}
      if(ZuYSxRdFaY == true){ZuYSxRdFaY = false;}
      if(hQxrfsguda == true){hQxrfsguda = false;}
      if(IEUWCsBDeD == true){IEUWCsBDeD = false;}
      if(rZXPqHoiGP == true){rZXPqHoiGP = false;}
      if(LahGPyGfcT == true){LahGPyGfcT = false;}
      if(hRQYYVZCQE == true){hRQYYVZCQE = false;}
      if(QZaXgHrhAX == true){QZaXgHrhAX = false;}
      if(DyoOOhVOGD == true){DyoOOhVOGD = false;}
      if(lUaKUZJypV == true){lUaKUZJypV = false;}
      if(hmRCzkAKYI == true){hmRCzkAKYI = false;}
      if(FYfEQicCJq == true){FYfEQicCJq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITXRWGUORG
{ 
  void GYFPZSfGuO()
  { 
      bool kSHJGNDmVZ = false;
      bool LEhaqQjihG = false;
      bool BpnNPHVhOP = false;
      bool VrcbqndQXH = false;
      bool MrCbsPfUKE = false;
      bool FOgBttdssy = false;
      bool rUXFDTbGiC = false;
      bool mTLatJnMUz = false;
      bool bAXKJHLagx = false;
      bool KkWYOqUwXY = false;
      bool nZlHQkCFGk = false;
      bool FRXtVrxMuw = false;
      bool IAYlrCxlLC = false;
      bool nrowLCOPsY = false;
      bool EFTwrsNcCW = false;
      bool tHAaQmAzPO = false;
      bool mPtDwNbahT = false;
      bool dgSWqCfbtz = false;
      bool oUjnIgqNfY = false;
      bool BOAekoKPAd = false;
      string PzJbGywiUF;
      string jjcjAGIKzt;
      string xBCEQtmzjc;
      string SXhGYKxdBb;
      string tWVUkxcPUV;
      string rmqHBOwELM;
      string LwyrlLCVKp;
      string IdIWAafhTT;
      string RXeNkefaFK;
      string NsSoQxXdhY;
      string uGEeNNdUGZ;
      string hOkrunRjGG;
      string eaQzbPLTGC;
      string DBzuYKSzAW;
      string ALTebzIatb;
      string fmWbsTpEDy;
      string CKNEWgOoSj;
      string VRjjFTHkWb;
      string GkZdVPeXBE;
      string UNwBUpxOIu;
      if(PzJbGywiUF == uGEeNNdUGZ){kSHJGNDmVZ = true;}
      else if(uGEeNNdUGZ == PzJbGywiUF){nZlHQkCFGk = true;}
      if(jjcjAGIKzt == hOkrunRjGG){LEhaqQjihG = true;}
      else if(hOkrunRjGG == jjcjAGIKzt){FRXtVrxMuw = true;}
      if(xBCEQtmzjc == eaQzbPLTGC){BpnNPHVhOP = true;}
      else if(eaQzbPLTGC == xBCEQtmzjc){IAYlrCxlLC = true;}
      if(SXhGYKxdBb == DBzuYKSzAW){VrcbqndQXH = true;}
      else if(DBzuYKSzAW == SXhGYKxdBb){nrowLCOPsY = true;}
      if(tWVUkxcPUV == ALTebzIatb){MrCbsPfUKE = true;}
      else if(ALTebzIatb == tWVUkxcPUV){EFTwrsNcCW = true;}
      if(rmqHBOwELM == fmWbsTpEDy){FOgBttdssy = true;}
      else if(fmWbsTpEDy == rmqHBOwELM){tHAaQmAzPO = true;}
      if(LwyrlLCVKp == CKNEWgOoSj){rUXFDTbGiC = true;}
      else if(CKNEWgOoSj == LwyrlLCVKp){mPtDwNbahT = true;}
      if(IdIWAafhTT == VRjjFTHkWb){mTLatJnMUz = true;}
      if(RXeNkefaFK == GkZdVPeXBE){bAXKJHLagx = true;}
      if(NsSoQxXdhY == UNwBUpxOIu){KkWYOqUwXY = true;}
      while(VRjjFTHkWb == IdIWAafhTT){dgSWqCfbtz = true;}
      while(GkZdVPeXBE == GkZdVPeXBE){oUjnIgqNfY = true;}
      while(UNwBUpxOIu == UNwBUpxOIu){BOAekoKPAd = true;}
      if(kSHJGNDmVZ == true){kSHJGNDmVZ = false;}
      if(LEhaqQjihG == true){LEhaqQjihG = false;}
      if(BpnNPHVhOP == true){BpnNPHVhOP = false;}
      if(VrcbqndQXH == true){VrcbqndQXH = false;}
      if(MrCbsPfUKE == true){MrCbsPfUKE = false;}
      if(FOgBttdssy == true){FOgBttdssy = false;}
      if(rUXFDTbGiC == true){rUXFDTbGiC = false;}
      if(mTLatJnMUz == true){mTLatJnMUz = false;}
      if(bAXKJHLagx == true){bAXKJHLagx = false;}
      if(KkWYOqUwXY == true){KkWYOqUwXY = false;}
      if(nZlHQkCFGk == true){nZlHQkCFGk = false;}
      if(FRXtVrxMuw == true){FRXtVrxMuw = false;}
      if(IAYlrCxlLC == true){IAYlrCxlLC = false;}
      if(nrowLCOPsY == true){nrowLCOPsY = false;}
      if(EFTwrsNcCW == true){EFTwrsNcCW = false;}
      if(tHAaQmAzPO == true){tHAaQmAzPO = false;}
      if(mPtDwNbahT == true){mPtDwNbahT = false;}
      if(dgSWqCfbtz == true){dgSWqCfbtz = false;}
      if(oUjnIgqNfY == true){oUjnIgqNfY = false;}
      if(BOAekoKPAd == true){BOAekoKPAd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUYRSLHGLN
{ 
  void GFTmUCiuOW()
  { 
      bool wSDgEOchhi = false;
      bool lWCokOYWdj = false;
      bool rhdHixtcys = false;
      bool QoeujotJjt = false;
      bool mTMswohJYR = false;
      bool UBIlrNnuyG = false;
      bool UzinRwqGEu = false;
      bool UPliwYVkKs = false;
      bool OjDgYPgsDW = false;
      bool BzLdZnjXaz = false;
      bool ybEdxEOYoS = false;
      bool qDjEqjuCPC = false;
      bool PxDhtVEIJI = false;
      bool oxKLumfZjT = false;
      bool BHEjexOGlo = false;
      bool rhIXjAYWib = false;
      bool AFPfdtsYIE = false;
      bool EVSuBIsSCw = false;
      bool GxWTQGolau = false;
      bool OIqITurXFk = false;
      string PVwtfOFixA;
      string WByoPyyCQW;
      string FHtrzOBtQZ;
      string HZWTsrjaZB;
      string hVILtqdoyn;
      string bMCsPHaEtQ;
      string NKRWrwddwW;
      string NXcPnizixI;
      string kLwcytXdEl;
      string RffInWEkSx;
      string MzsaZEjmEf;
      string HrGlfBOoYx;
      string YAZKFgqTaR;
      string eNPAukSUCs;
      string KjYXdYYscl;
      string IOMUXMYhVs;
      string MQLmBscGpu;
      string hslemoaCff;
      string IxqoJQBtbh;
      string LjzJftXlWj;
      if(PVwtfOFixA == MzsaZEjmEf){wSDgEOchhi = true;}
      else if(MzsaZEjmEf == PVwtfOFixA){ybEdxEOYoS = true;}
      if(WByoPyyCQW == HrGlfBOoYx){lWCokOYWdj = true;}
      else if(HrGlfBOoYx == WByoPyyCQW){qDjEqjuCPC = true;}
      if(FHtrzOBtQZ == YAZKFgqTaR){rhdHixtcys = true;}
      else if(YAZKFgqTaR == FHtrzOBtQZ){PxDhtVEIJI = true;}
      if(HZWTsrjaZB == eNPAukSUCs){QoeujotJjt = true;}
      else if(eNPAukSUCs == HZWTsrjaZB){oxKLumfZjT = true;}
      if(hVILtqdoyn == KjYXdYYscl){mTMswohJYR = true;}
      else if(KjYXdYYscl == hVILtqdoyn){BHEjexOGlo = true;}
      if(bMCsPHaEtQ == IOMUXMYhVs){UBIlrNnuyG = true;}
      else if(IOMUXMYhVs == bMCsPHaEtQ){rhIXjAYWib = true;}
      if(NKRWrwddwW == MQLmBscGpu){UzinRwqGEu = true;}
      else if(MQLmBscGpu == NKRWrwddwW){AFPfdtsYIE = true;}
      if(NXcPnizixI == hslemoaCff){UPliwYVkKs = true;}
      if(kLwcytXdEl == IxqoJQBtbh){OjDgYPgsDW = true;}
      if(RffInWEkSx == LjzJftXlWj){BzLdZnjXaz = true;}
      while(hslemoaCff == NXcPnizixI){EVSuBIsSCw = true;}
      while(IxqoJQBtbh == IxqoJQBtbh){GxWTQGolau = true;}
      while(LjzJftXlWj == LjzJftXlWj){OIqITurXFk = true;}
      if(wSDgEOchhi == true){wSDgEOchhi = false;}
      if(lWCokOYWdj == true){lWCokOYWdj = false;}
      if(rhdHixtcys == true){rhdHixtcys = false;}
      if(QoeujotJjt == true){QoeujotJjt = false;}
      if(mTMswohJYR == true){mTMswohJYR = false;}
      if(UBIlrNnuyG == true){UBIlrNnuyG = false;}
      if(UzinRwqGEu == true){UzinRwqGEu = false;}
      if(UPliwYVkKs == true){UPliwYVkKs = false;}
      if(OjDgYPgsDW == true){OjDgYPgsDW = false;}
      if(BzLdZnjXaz == true){BzLdZnjXaz = false;}
      if(ybEdxEOYoS == true){ybEdxEOYoS = false;}
      if(qDjEqjuCPC == true){qDjEqjuCPC = false;}
      if(PxDhtVEIJI == true){PxDhtVEIJI = false;}
      if(oxKLumfZjT == true){oxKLumfZjT = false;}
      if(BHEjexOGlo == true){BHEjexOGlo = false;}
      if(rhIXjAYWib == true){rhIXjAYWib = false;}
      if(AFPfdtsYIE == true){AFPfdtsYIE = false;}
      if(EVSuBIsSCw == true){EVSuBIsSCw = false;}
      if(GxWTQGolau == true){GxWTQGolau = false;}
      if(OIqITurXFk == true){OIqITurXFk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MHMVMJPLBX
{ 
  void kRJLqJHSOk()
  { 
      bool KSNxhfQfaY = false;
      bool PmRmgaUNrb = false;
      bool DxubwkPgUs = false;
      bool knmbSbVOBB = false;
      bool ynROBHdlGK = false;
      bool wPVQuMXlAw = false;
      bool PjKhnazpUF = false;
      bool EFLqcOffao = false;
      bool GdZKxURWfF = false;
      bool DjOFkOcjaZ = false;
      bool HnQBFpEemg = false;
      bool grLLplJAjT = false;
      bool IcKPBTqGFO = false;
      bool luFAhSMXEH = false;
      bool PmizXLYCOy = false;
      bool EbAHRdcBAl = false;
      bool yyZYulmKdW = false;
      bool ZlwcDVsLqo = false;
      bool toqGJJuyhD = false;
      bool oKWRIQMKEk = false;
      string tNCmHcAAYB;
      string RCgQbhkffQ;
      string YaOpOLWkYa;
      string JGsrSXYJms;
      string PAjmmTTozh;
      string dbicRTyMYu;
      string FPbyqLInxE;
      string IbsmBYqbCu;
      string qhkpxhWPaz;
      string YLjqmzXlub;
      string KfquYBiwbr;
      string cWJcDXelAJ;
      string nrNyexqBzC;
      string BFfajLpoQu;
      string yZniWBBGnP;
      string UlklmSRsQb;
      string KgxZpXqisq;
      string hoUFKNDeac;
      string ujMjgOTsnQ;
      string twYnkQcOrz;
      if(tNCmHcAAYB == KfquYBiwbr){KSNxhfQfaY = true;}
      else if(KfquYBiwbr == tNCmHcAAYB){HnQBFpEemg = true;}
      if(RCgQbhkffQ == cWJcDXelAJ){PmRmgaUNrb = true;}
      else if(cWJcDXelAJ == RCgQbhkffQ){grLLplJAjT = true;}
      if(YaOpOLWkYa == nrNyexqBzC){DxubwkPgUs = true;}
      else if(nrNyexqBzC == YaOpOLWkYa){IcKPBTqGFO = true;}
      if(JGsrSXYJms == BFfajLpoQu){knmbSbVOBB = true;}
      else if(BFfajLpoQu == JGsrSXYJms){luFAhSMXEH = true;}
      if(PAjmmTTozh == yZniWBBGnP){ynROBHdlGK = true;}
      else if(yZniWBBGnP == PAjmmTTozh){PmizXLYCOy = true;}
      if(dbicRTyMYu == UlklmSRsQb){wPVQuMXlAw = true;}
      else if(UlklmSRsQb == dbicRTyMYu){EbAHRdcBAl = true;}
      if(FPbyqLInxE == KgxZpXqisq){PjKhnazpUF = true;}
      else if(KgxZpXqisq == FPbyqLInxE){yyZYulmKdW = true;}
      if(IbsmBYqbCu == hoUFKNDeac){EFLqcOffao = true;}
      if(qhkpxhWPaz == ujMjgOTsnQ){GdZKxURWfF = true;}
      if(YLjqmzXlub == twYnkQcOrz){DjOFkOcjaZ = true;}
      while(hoUFKNDeac == IbsmBYqbCu){ZlwcDVsLqo = true;}
      while(ujMjgOTsnQ == ujMjgOTsnQ){toqGJJuyhD = true;}
      while(twYnkQcOrz == twYnkQcOrz){oKWRIQMKEk = true;}
      if(KSNxhfQfaY == true){KSNxhfQfaY = false;}
      if(PmRmgaUNrb == true){PmRmgaUNrb = false;}
      if(DxubwkPgUs == true){DxubwkPgUs = false;}
      if(knmbSbVOBB == true){knmbSbVOBB = false;}
      if(ynROBHdlGK == true){ynROBHdlGK = false;}
      if(wPVQuMXlAw == true){wPVQuMXlAw = false;}
      if(PjKhnazpUF == true){PjKhnazpUF = false;}
      if(EFLqcOffao == true){EFLqcOffao = false;}
      if(GdZKxURWfF == true){GdZKxURWfF = false;}
      if(DjOFkOcjaZ == true){DjOFkOcjaZ = false;}
      if(HnQBFpEemg == true){HnQBFpEemg = false;}
      if(grLLplJAjT == true){grLLplJAjT = false;}
      if(IcKPBTqGFO == true){IcKPBTqGFO = false;}
      if(luFAhSMXEH == true){luFAhSMXEH = false;}
      if(PmizXLYCOy == true){PmizXLYCOy = false;}
      if(EbAHRdcBAl == true){EbAHRdcBAl = false;}
      if(yyZYulmKdW == true){yyZYulmKdW = false;}
      if(ZlwcDVsLqo == true){ZlwcDVsLqo = false;}
      if(toqGJJuyhD == true){toqGJJuyhD = false;}
      if(oKWRIQMKEk == true){oKWRIQMKEk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXSQHKSGUW
{ 
  void bBJbRfdKtA()
  { 
      bool iTNElpdoIE = false;
      bool MGEZVWUBjb = false;
      bool DoPFRILLKN = false;
      bool afYgRCjxlf = false;
      bool GdMjDjDeKF = false;
      bool TZQAAsEHld = false;
      bool eRetdghXIS = false;
      bool mWODUYbfCh = false;
      bool EfBEsAPXfX = false;
      bool ybLHBozSGW = false;
      bool BeVqRwKMfa = false;
      bool QYFDZyPZAc = false;
      bool QJqjULLHCe = false;
      bool ZJZegYJJlw = false;
      bool oDrFHZWHhC = false;
      bool ZYRcGrmlWG = false;
      bool kDKABGzaWA = false;
      bool nFmEmNQlct = false;
      bool nEZzFArwXn = false;
      bool kXmeLkrrEA = false;
      string jockqcxBpk;
      string KqRiLtwGfi;
      string OGsXIoMAVF;
      string WCKUZgbtVj;
      string BTxnSPtLzH;
      string EWyRNdwEbC;
      string QxfkOHgwId;
      string SBjwgtJFFs;
      string uBANAzErHw;
      string jWSTSDnMYK;
      string hxCUnDmCjS;
      string UqzhGPwRjO;
      string DnoMtuhPcd;
      string GwfuKyyfZx;
      string MBHnbsXkND;
      string GVbKGtHpas;
      string UWZGMXKDWI;
      string QQrmCCgAkA;
      string WxCYWjTUnQ;
      string pIFfcoaAbD;
      if(jockqcxBpk == hxCUnDmCjS){iTNElpdoIE = true;}
      else if(hxCUnDmCjS == jockqcxBpk){BeVqRwKMfa = true;}
      if(KqRiLtwGfi == UqzhGPwRjO){MGEZVWUBjb = true;}
      else if(UqzhGPwRjO == KqRiLtwGfi){QYFDZyPZAc = true;}
      if(OGsXIoMAVF == DnoMtuhPcd){DoPFRILLKN = true;}
      else if(DnoMtuhPcd == OGsXIoMAVF){QJqjULLHCe = true;}
      if(WCKUZgbtVj == GwfuKyyfZx){afYgRCjxlf = true;}
      else if(GwfuKyyfZx == WCKUZgbtVj){ZJZegYJJlw = true;}
      if(BTxnSPtLzH == MBHnbsXkND){GdMjDjDeKF = true;}
      else if(MBHnbsXkND == BTxnSPtLzH){oDrFHZWHhC = true;}
      if(EWyRNdwEbC == GVbKGtHpas){TZQAAsEHld = true;}
      else if(GVbKGtHpas == EWyRNdwEbC){ZYRcGrmlWG = true;}
      if(QxfkOHgwId == UWZGMXKDWI){eRetdghXIS = true;}
      else if(UWZGMXKDWI == QxfkOHgwId){kDKABGzaWA = true;}
      if(SBjwgtJFFs == QQrmCCgAkA){mWODUYbfCh = true;}
      if(uBANAzErHw == WxCYWjTUnQ){EfBEsAPXfX = true;}
      if(jWSTSDnMYK == pIFfcoaAbD){ybLHBozSGW = true;}
      while(QQrmCCgAkA == SBjwgtJFFs){nFmEmNQlct = true;}
      while(WxCYWjTUnQ == WxCYWjTUnQ){nEZzFArwXn = true;}
      while(pIFfcoaAbD == pIFfcoaAbD){kXmeLkrrEA = true;}
      if(iTNElpdoIE == true){iTNElpdoIE = false;}
      if(MGEZVWUBjb == true){MGEZVWUBjb = false;}
      if(DoPFRILLKN == true){DoPFRILLKN = false;}
      if(afYgRCjxlf == true){afYgRCjxlf = false;}
      if(GdMjDjDeKF == true){GdMjDjDeKF = false;}
      if(TZQAAsEHld == true){TZQAAsEHld = false;}
      if(eRetdghXIS == true){eRetdghXIS = false;}
      if(mWODUYbfCh == true){mWODUYbfCh = false;}
      if(EfBEsAPXfX == true){EfBEsAPXfX = false;}
      if(ybLHBozSGW == true){ybLHBozSGW = false;}
      if(BeVqRwKMfa == true){BeVqRwKMfa = false;}
      if(QYFDZyPZAc == true){QYFDZyPZAc = false;}
      if(QJqjULLHCe == true){QJqjULLHCe = false;}
      if(ZJZegYJJlw == true){ZJZegYJJlw = false;}
      if(oDrFHZWHhC == true){oDrFHZWHhC = false;}
      if(ZYRcGrmlWG == true){ZYRcGrmlWG = false;}
      if(kDKABGzaWA == true){kDKABGzaWA = false;}
      if(nFmEmNQlct == true){nFmEmNQlct = false;}
      if(nEZzFArwXn == true){nEZzFArwXn = false;}
      if(kXmeLkrrEA == true){kXmeLkrrEA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWVIDEZPQD
{ 
  void oTIRpooRnU()
  { 
      bool AnqwAGwxPl = false;
      bool HGPmmmgmIf = false;
      bool TENaEIIdbx = false;
      bool IuNNFfdiVV = false;
      bool VhxagFOUNC = false;
      bool BzQJqwaQqq = false;
      bool ySVRdLrBhH = false;
      bool JyRlJlGlsy = false;
      bool tnQYuIeDWJ = false;
      bool ENqdXDMfxU = false;
      bool NMlFsDhdAE = false;
      bool pnWsxJCwVU = false;
      bool gneYCwGmNG = false;
      bool ZZoYkgBKfq = false;
      bool aADRSQpygO = false;
      bool APJbnZhNDw = false;
      bool xuQtePyyHP = false;
      bool HqQdtfjNFk = false;
      bool FHFyFJPNjL = false;
      bool znGitfjJlD = false;
      string eDrJOFnKcj;
      string mHIQVDxGtU;
      string NJrAICHCTc;
      string DhdibEflNr;
      string cFgHekcOiR;
      string tzTeBVLrBM;
      string ylpAgEdZoQ;
      string XKsCrIbjVW;
      string YrSChDNygF;
      string smjAspOgaZ;
      string HCYRsiGRmr;
      string taWemGSmRd;
      string qerjXkasIB;
      string ttJuPWSBJz;
      string wuKnKRPFMm;
      string XaPwhbKosI;
      string INIlyzRaOQ;
      string mQdSguUDYG;
      string UUfVcSeNNn;
      string LdHApimYpL;
      if(eDrJOFnKcj == HCYRsiGRmr){AnqwAGwxPl = true;}
      else if(HCYRsiGRmr == eDrJOFnKcj){NMlFsDhdAE = true;}
      if(mHIQVDxGtU == taWemGSmRd){HGPmmmgmIf = true;}
      else if(taWemGSmRd == mHIQVDxGtU){pnWsxJCwVU = true;}
      if(NJrAICHCTc == qerjXkasIB){TENaEIIdbx = true;}
      else if(qerjXkasIB == NJrAICHCTc){gneYCwGmNG = true;}
      if(DhdibEflNr == ttJuPWSBJz){IuNNFfdiVV = true;}
      else if(ttJuPWSBJz == DhdibEflNr){ZZoYkgBKfq = true;}
      if(cFgHekcOiR == wuKnKRPFMm){VhxagFOUNC = true;}
      else if(wuKnKRPFMm == cFgHekcOiR){aADRSQpygO = true;}
      if(tzTeBVLrBM == XaPwhbKosI){BzQJqwaQqq = true;}
      else if(XaPwhbKosI == tzTeBVLrBM){APJbnZhNDw = true;}
      if(ylpAgEdZoQ == INIlyzRaOQ){ySVRdLrBhH = true;}
      else if(INIlyzRaOQ == ylpAgEdZoQ){xuQtePyyHP = true;}
      if(XKsCrIbjVW == mQdSguUDYG){JyRlJlGlsy = true;}
      if(YrSChDNygF == UUfVcSeNNn){tnQYuIeDWJ = true;}
      if(smjAspOgaZ == LdHApimYpL){ENqdXDMfxU = true;}
      while(mQdSguUDYG == XKsCrIbjVW){HqQdtfjNFk = true;}
      while(UUfVcSeNNn == UUfVcSeNNn){FHFyFJPNjL = true;}
      while(LdHApimYpL == LdHApimYpL){znGitfjJlD = true;}
      if(AnqwAGwxPl == true){AnqwAGwxPl = false;}
      if(HGPmmmgmIf == true){HGPmmmgmIf = false;}
      if(TENaEIIdbx == true){TENaEIIdbx = false;}
      if(IuNNFfdiVV == true){IuNNFfdiVV = false;}
      if(VhxagFOUNC == true){VhxagFOUNC = false;}
      if(BzQJqwaQqq == true){BzQJqwaQqq = false;}
      if(ySVRdLrBhH == true){ySVRdLrBhH = false;}
      if(JyRlJlGlsy == true){JyRlJlGlsy = false;}
      if(tnQYuIeDWJ == true){tnQYuIeDWJ = false;}
      if(ENqdXDMfxU == true){ENqdXDMfxU = false;}
      if(NMlFsDhdAE == true){NMlFsDhdAE = false;}
      if(pnWsxJCwVU == true){pnWsxJCwVU = false;}
      if(gneYCwGmNG == true){gneYCwGmNG = false;}
      if(ZZoYkgBKfq == true){ZZoYkgBKfq = false;}
      if(aADRSQpygO == true){aADRSQpygO = false;}
      if(APJbnZhNDw == true){APJbnZhNDw = false;}
      if(xuQtePyyHP == true){xuQtePyyHP = false;}
      if(HqQdtfjNFk == true){HqQdtfjNFk = false;}
      if(FHFyFJPNjL == true){FHFyFJPNjL = false;}
      if(znGitfjJlD == true){znGitfjJlD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AMGOWJRROR
{ 
  void hWIEnipGed()
  { 
      bool dIpjHGYqSl = false;
      bool UTUOUBcPnE = false;
      bool lWmPFtrPmK = false;
      bool DCpHFiqKIs = false;
      bool DFpRNNjMWt = false;
      bool hchRhGUaeM = false;
      bool NJEIhRcMIl = false;
      bool JSHtBgfVBq = false;
      bool KfrrcaUXZy = false;
      bool OPfuetBgju = false;
      bool kXDkjOVmQB = false;
      bool ZzYmCgQMfG = false;
      bool xEmJXtlLPH = false;
      bool fzkGGlcGHN = false;
      bool FhHYYOqsrx = false;
      bool coBdyfktNp = false;
      bool bJXJUaNRfP = false;
      bool EJESAOxNkI = false;
      bool CsSRdqxHHa = false;
      bool BisQkuKyDx = false;
      string LpDTWmHGbm;
      string ImpPxNkaeZ;
      string VwSlmMCwhd;
      string IMfiYNtxiw;
      string fSlZxhCUcX;
      string shlIrPXRgK;
      string kLXyeuGGpj;
      string TmqitDJrnF;
      string JhSJjZaXqJ;
      string ocQYKTtmtC;
      string budsEFqDOo;
      string FecbBDsNNF;
      string ThPgtqWSXZ;
      string IWylcNDZFe;
      string iXJCDKzoXH;
      string agZohtfxyM;
      string iXenfifqym;
      string ATHiVwYMcj;
      string qguPzbwJDi;
      string gFarwKrVWU;
      if(LpDTWmHGbm == budsEFqDOo){dIpjHGYqSl = true;}
      else if(budsEFqDOo == LpDTWmHGbm){kXDkjOVmQB = true;}
      if(ImpPxNkaeZ == FecbBDsNNF){UTUOUBcPnE = true;}
      else if(FecbBDsNNF == ImpPxNkaeZ){ZzYmCgQMfG = true;}
      if(VwSlmMCwhd == ThPgtqWSXZ){lWmPFtrPmK = true;}
      else if(ThPgtqWSXZ == VwSlmMCwhd){xEmJXtlLPH = true;}
      if(IMfiYNtxiw == IWylcNDZFe){DCpHFiqKIs = true;}
      else if(IWylcNDZFe == IMfiYNtxiw){fzkGGlcGHN = true;}
      if(fSlZxhCUcX == iXJCDKzoXH){DFpRNNjMWt = true;}
      else if(iXJCDKzoXH == fSlZxhCUcX){FhHYYOqsrx = true;}
      if(shlIrPXRgK == agZohtfxyM){hchRhGUaeM = true;}
      else if(agZohtfxyM == shlIrPXRgK){coBdyfktNp = true;}
      if(kLXyeuGGpj == iXenfifqym){NJEIhRcMIl = true;}
      else if(iXenfifqym == kLXyeuGGpj){bJXJUaNRfP = true;}
      if(TmqitDJrnF == ATHiVwYMcj){JSHtBgfVBq = true;}
      if(JhSJjZaXqJ == qguPzbwJDi){KfrrcaUXZy = true;}
      if(ocQYKTtmtC == gFarwKrVWU){OPfuetBgju = true;}
      while(ATHiVwYMcj == TmqitDJrnF){EJESAOxNkI = true;}
      while(qguPzbwJDi == qguPzbwJDi){CsSRdqxHHa = true;}
      while(gFarwKrVWU == gFarwKrVWU){BisQkuKyDx = true;}
      if(dIpjHGYqSl == true){dIpjHGYqSl = false;}
      if(UTUOUBcPnE == true){UTUOUBcPnE = false;}
      if(lWmPFtrPmK == true){lWmPFtrPmK = false;}
      if(DCpHFiqKIs == true){DCpHFiqKIs = false;}
      if(DFpRNNjMWt == true){DFpRNNjMWt = false;}
      if(hchRhGUaeM == true){hchRhGUaeM = false;}
      if(NJEIhRcMIl == true){NJEIhRcMIl = false;}
      if(JSHtBgfVBq == true){JSHtBgfVBq = false;}
      if(KfrrcaUXZy == true){KfrrcaUXZy = false;}
      if(OPfuetBgju == true){OPfuetBgju = false;}
      if(kXDkjOVmQB == true){kXDkjOVmQB = false;}
      if(ZzYmCgQMfG == true){ZzYmCgQMfG = false;}
      if(xEmJXtlLPH == true){xEmJXtlLPH = false;}
      if(fzkGGlcGHN == true){fzkGGlcGHN = false;}
      if(FhHYYOqsrx == true){FhHYYOqsrx = false;}
      if(coBdyfktNp == true){coBdyfktNp = false;}
      if(bJXJUaNRfP == true){bJXJUaNRfP = false;}
      if(EJESAOxNkI == true){EJESAOxNkI = false;}
      if(CsSRdqxHHa == true){CsSRdqxHHa = false;}
      if(BisQkuKyDx == true){BisQkuKyDx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUWVDBKHVZ
{ 
  void gcEsgmHTIU()
  { 
      bool VBSulPsTwr = false;
      bool JOgNIcCzcl = false;
      bool zCfmbfyTQc = false;
      bool tgNbiypopC = false;
      bool jrEoNetRSL = false;
      bool izbJWTUeTG = false;
      bool RZDSxbBFdJ = false;
      bool lMIaCGxqZw = false;
      bool lfAEtuFEEP = false;
      bool cLVjjJolql = false;
      bool domIZVpBHP = false;
      bool VdEWTkYzXC = false;
      bool VxAOgZpYpr = false;
      bool RLzmRwsrdY = false;
      bool EEwnsyGyPz = false;
      bool koNnPgnYbA = false;
      bool eQKPxKeREX = false;
      bool rgUzxQALUh = false;
      bool SrJqHbxKWk = false;
      bool HTQdsnsgqi = false;
      string YkMQtkoRAc;
      string pCmqdBjhZl;
      string kfMMjkANiT;
      string XBFRaLsoTt;
      string AAmDrgSePd;
      string TGduUrXzgJ;
      string kahfEoxUQR;
      string HtOflksJUC;
      string RVxEzQXJxh;
      string msHJJYRGyC;
      string ixNyVYrxJj;
      string zOedqPddgm;
      string RmXheNmEWN;
      string SmLRSUHzia;
      string YZANiYOcSt;
      string tnZKjwZfTH;
      string lnauQMDNKW;
      string HdtFOrlKyF;
      string zJkbSdMAgW;
      string tbfaokyEwW;
      if(YkMQtkoRAc == ixNyVYrxJj){VBSulPsTwr = true;}
      else if(ixNyVYrxJj == YkMQtkoRAc){domIZVpBHP = true;}
      if(pCmqdBjhZl == zOedqPddgm){JOgNIcCzcl = true;}
      else if(zOedqPddgm == pCmqdBjhZl){VdEWTkYzXC = true;}
      if(kfMMjkANiT == RmXheNmEWN){zCfmbfyTQc = true;}
      else if(RmXheNmEWN == kfMMjkANiT){VxAOgZpYpr = true;}
      if(XBFRaLsoTt == SmLRSUHzia){tgNbiypopC = true;}
      else if(SmLRSUHzia == XBFRaLsoTt){RLzmRwsrdY = true;}
      if(AAmDrgSePd == YZANiYOcSt){jrEoNetRSL = true;}
      else if(YZANiYOcSt == AAmDrgSePd){EEwnsyGyPz = true;}
      if(TGduUrXzgJ == tnZKjwZfTH){izbJWTUeTG = true;}
      else if(tnZKjwZfTH == TGduUrXzgJ){koNnPgnYbA = true;}
      if(kahfEoxUQR == lnauQMDNKW){RZDSxbBFdJ = true;}
      else if(lnauQMDNKW == kahfEoxUQR){eQKPxKeREX = true;}
      if(HtOflksJUC == HdtFOrlKyF){lMIaCGxqZw = true;}
      if(RVxEzQXJxh == zJkbSdMAgW){lfAEtuFEEP = true;}
      if(msHJJYRGyC == tbfaokyEwW){cLVjjJolql = true;}
      while(HdtFOrlKyF == HtOflksJUC){rgUzxQALUh = true;}
      while(zJkbSdMAgW == zJkbSdMAgW){SrJqHbxKWk = true;}
      while(tbfaokyEwW == tbfaokyEwW){HTQdsnsgqi = true;}
      if(VBSulPsTwr == true){VBSulPsTwr = false;}
      if(JOgNIcCzcl == true){JOgNIcCzcl = false;}
      if(zCfmbfyTQc == true){zCfmbfyTQc = false;}
      if(tgNbiypopC == true){tgNbiypopC = false;}
      if(jrEoNetRSL == true){jrEoNetRSL = false;}
      if(izbJWTUeTG == true){izbJWTUeTG = false;}
      if(RZDSxbBFdJ == true){RZDSxbBFdJ = false;}
      if(lMIaCGxqZw == true){lMIaCGxqZw = false;}
      if(lfAEtuFEEP == true){lfAEtuFEEP = false;}
      if(cLVjjJolql == true){cLVjjJolql = false;}
      if(domIZVpBHP == true){domIZVpBHP = false;}
      if(VdEWTkYzXC == true){VdEWTkYzXC = false;}
      if(VxAOgZpYpr == true){VxAOgZpYpr = false;}
      if(RLzmRwsrdY == true){RLzmRwsrdY = false;}
      if(EEwnsyGyPz == true){EEwnsyGyPz = false;}
      if(koNnPgnYbA == true){koNnPgnYbA = false;}
      if(eQKPxKeREX == true){eQKPxKeREX = false;}
      if(rgUzxQALUh == true){rgUzxQALUh = false;}
      if(SrJqHbxKWk == true){SrJqHbxKWk = false;}
      if(HTQdsnsgqi == true){HTQdsnsgqi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVFTTEJAVF
{ 
  void nNxXyPgWYp()
  { 
      bool iLrSxaOhBL = false;
      bool bPHTyYuiOe = false;
      bool ApNkKmMhEp = false;
      bool ZfPRUNJATc = false;
      bool CrEDMLNVVR = false;
      bool klLLKsxGIJ = false;
      bool OfdKkuzoyj = false;
      bool OuPlcHkJXz = false;
      bool YpMmFnUDHb = false;
      bool PCqJOVOsSR = false;
      bool LYWkCoVZiC = false;
      bool HmiJkXTpEx = false;
      bool awhWULDGWG = false;
      bool rrqGmATajQ = false;
      bool RuTETbThXq = false;
      bool CXnVpPpAQp = false;
      bool kPCcKPwbVk = false;
      bool EsGnefbcCr = false;
      bool rVhfDTDVPX = false;
      bool JSJteCrqtE = false;
      string pFPlJyyoYg;
      string JTUWnjFFbH;
      string gOKWiGfNQw;
      string hCYBrAgTrl;
      string ejSodcnctn;
      string hALddaurDC;
      string RjXbzGtTen;
      string CkNocwuUsF;
      string SDTcOgptWQ;
      string EnQoTtMqpW;
      string hTxGkwmVBh;
      string eZzxjOQtNR;
      string PAwNiNUXVh;
      string jEdVWyFNqR;
      string tUsokeoSEF;
      string dRdYGhWjXW;
      string aOzSxaucZl;
      string ICCuWuGHbD;
      string YCSQERaFPo;
      string aVpTpfUZqK;
      if(pFPlJyyoYg == hTxGkwmVBh){iLrSxaOhBL = true;}
      else if(hTxGkwmVBh == pFPlJyyoYg){LYWkCoVZiC = true;}
      if(JTUWnjFFbH == eZzxjOQtNR){bPHTyYuiOe = true;}
      else if(eZzxjOQtNR == JTUWnjFFbH){HmiJkXTpEx = true;}
      if(gOKWiGfNQw == PAwNiNUXVh){ApNkKmMhEp = true;}
      else if(PAwNiNUXVh == gOKWiGfNQw){awhWULDGWG = true;}
      if(hCYBrAgTrl == jEdVWyFNqR){ZfPRUNJATc = true;}
      else if(jEdVWyFNqR == hCYBrAgTrl){rrqGmATajQ = true;}
      if(ejSodcnctn == tUsokeoSEF){CrEDMLNVVR = true;}
      else if(tUsokeoSEF == ejSodcnctn){RuTETbThXq = true;}
      if(hALddaurDC == dRdYGhWjXW){klLLKsxGIJ = true;}
      else if(dRdYGhWjXW == hALddaurDC){CXnVpPpAQp = true;}
      if(RjXbzGtTen == aOzSxaucZl){OfdKkuzoyj = true;}
      else if(aOzSxaucZl == RjXbzGtTen){kPCcKPwbVk = true;}
      if(CkNocwuUsF == ICCuWuGHbD){OuPlcHkJXz = true;}
      if(SDTcOgptWQ == YCSQERaFPo){YpMmFnUDHb = true;}
      if(EnQoTtMqpW == aVpTpfUZqK){PCqJOVOsSR = true;}
      while(ICCuWuGHbD == CkNocwuUsF){EsGnefbcCr = true;}
      while(YCSQERaFPo == YCSQERaFPo){rVhfDTDVPX = true;}
      while(aVpTpfUZqK == aVpTpfUZqK){JSJteCrqtE = true;}
      if(iLrSxaOhBL == true){iLrSxaOhBL = false;}
      if(bPHTyYuiOe == true){bPHTyYuiOe = false;}
      if(ApNkKmMhEp == true){ApNkKmMhEp = false;}
      if(ZfPRUNJATc == true){ZfPRUNJATc = false;}
      if(CrEDMLNVVR == true){CrEDMLNVVR = false;}
      if(klLLKsxGIJ == true){klLLKsxGIJ = false;}
      if(OfdKkuzoyj == true){OfdKkuzoyj = false;}
      if(OuPlcHkJXz == true){OuPlcHkJXz = false;}
      if(YpMmFnUDHb == true){YpMmFnUDHb = false;}
      if(PCqJOVOsSR == true){PCqJOVOsSR = false;}
      if(LYWkCoVZiC == true){LYWkCoVZiC = false;}
      if(HmiJkXTpEx == true){HmiJkXTpEx = false;}
      if(awhWULDGWG == true){awhWULDGWG = false;}
      if(rrqGmATajQ == true){rrqGmATajQ = false;}
      if(RuTETbThXq == true){RuTETbThXq = false;}
      if(CXnVpPpAQp == true){CXnVpPpAQp = false;}
      if(kPCcKPwbVk == true){kPCcKPwbVk = false;}
      if(EsGnefbcCr == true){EsGnefbcCr = false;}
      if(rVhfDTDVPX == true){rVhfDTDVPX = false;}
      if(JSJteCrqtE == true){JSJteCrqtE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXHUZWMXNE
{ 
  void TmeeamcuQy()
  { 
      bool CQqxjFMgHD = false;
      bool kBTpqVdXIL = false;
      bool DBsEAhcPAs = false;
      bool hyxDZAfebx = false;
      bool MkLdGIyQdC = false;
      bool nIjeWAWlwC = false;
      bool bwfOVmEQPq = false;
      bool ozuLzSoPyr = false;
      bool iLlxFYNSfY = false;
      bool cshZUPExHT = false;
      bool DhAlMoMYeE = false;
      bool LHnDSQKhJw = false;
      bool YkkqOuQVpi = false;
      bool NrHdnBKzkP = false;
      bool LnmaNUFeGE = false;
      bool FVnLtSxJXQ = false;
      bool YqhupTzKPR = false;
      bool FLxsjkyJds = false;
      bool plOldrDwiV = false;
      bool DBaTqTGqjt = false;
      string enjjYTdsFE;
      string BIaFEGhjwk;
      string HXqQYITgis;
      string GZCbtbiQhA;
      string uWGBWeDhrn;
      string WrcsrHxSKP;
      string AxJMxaFyLc;
      string XRCwpkQpts;
      string EkntWNxIil;
      string dPFSzxNtDu;
      string YFVPQFpgDH;
      string qHYQKOIPoj;
      string dwPYyHLjwr;
      string WVmyUzOYdR;
      string XPFauWqnHj;
      string oyESRboxRI;
      string sFjLkUUZwK;
      string zjkXLNqndb;
      string QXbMCYRTgr;
      string JRGVXRfspa;
      if(enjjYTdsFE == YFVPQFpgDH){CQqxjFMgHD = true;}
      else if(YFVPQFpgDH == enjjYTdsFE){DhAlMoMYeE = true;}
      if(BIaFEGhjwk == qHYQKOIPoj){kBTpqVdXIL = true;}
      else if(qHYQKOIPoj == BIaFEGhjwk){LHnDSQKhJw = true;}
      if(HXqQYITgis == dwPYyHLjwr){DBsEAhcPAs = true;}
      else if(dwPYyHLjwr == HXqQYITgis){YkkqOuQVpi = true;}
      if(GZCbtbiQhA == WVmyUzOYdR){hyxDZAfebx = true;}
      else if(WVmyUzOYdR == GZCbtbiQhA){NrHdnBKzkP = true;}
      if(uWGBWeDhrn == XPFauWqnHj){MkLdGIyQdC = true;}
      else if(XPFauWqnHj == uWGBWeDhrn){LnmaNUFeGE = true;}
      if(WrcsrHxSKP == oyESRboxRI){nIjeWAWlwC = true;}
      else if(oyESRboxRI == WrcsrHxSKP){FVnLtSxJXQ = true;}
      if(AxJMxaFyLc == sFjLkUUZwK){bwfOVmEQPq = true;}
      else if(sFjLkUUZwK == AxJMxaFyLc){YqhupTzKPR = true;}
      if(XRCwpkQpts == zjkXLNqndb){ozuLzSoPyr = true;}
      if(EkntWNxIil == QXbMCYRTgr){iLlxFYNSfY = true;}
      if(dPFSzxNtDu == JRGVXRfspa){cshZUPExHT = true;}
      while(zjkXLNqndb == XRCwpkQpts){FLxsjkyJds = true;}
      while(QXbMCYRTgr == QXbMCYRTgr){plOldrDwiV = true;}
      while(JRGVXRfspa == JRGVXRfspa){DBaTqTGqjt = true;}
      if(CQqxjFMgHD == true){CQqxjFMgHD = false;}
      if(kBTpqVdXIL == true){kBTpqVdXIL = false;}
      if(DBsEAhcPAs == true){DBsEAhcPAs = false;}
      if(hyxDZAfebx == true){hyxDZAfebx = false;}
      if(MkLdGIyQdC == true){MkLdGIyQdC = false;}
      if(nIjeWAWlwC == true){nIjeWAWlwC = false;}
      if(bwfOVmEQPq == true){bwfOVmEQPq = false;}
      if(ozuLzSoPyr == true){ozuLzSoPyr = false;}
      if(iLlxFYNSfY == true){iLlxFYNSfY = false;}
      if(cshZUPExHT == true){cshZUPExHT = false;}
      if(DhAlMoMYeE == true){DhAlMoMYeE = false;}
      if(LHnDSQKhJw == true){LHnDSQKhJw = false;}
      if(YkkqOuQVpi == true){YkkqOuQVpi = false;}
      if(NrHdnBKzkP == true){NrHdnBKzkP = false;}
      if(LnmaNUFeGE == true){LnmaNUFeGE = false;}
      if(FVnLtSxJXQ == true){FVnLtSxJXQ = false;}
      if(YqhupTzKPR == true){YqhupTzKPR = false;}
      if(FLxsjkyJds == true){FLxsjkyJds = false;}
      if(plOldrDwiV == true){plOldrDwiV = false;}
      if(DBaTqTGqjt == true){DBaTqTGqjt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUAARAOETQ
{ 
  void AFZhPremln()
  { 
      bool BwRFZfHCdU = false;
      bool lktxGaOamJ = false;
      bool jGPKZYOCIo = false;
      bool IzuPOzHrXg = false;
      bool oSxTQeFFjm = false;
      bool DFTcsugHeB = false;
      bool REtnMmpeiH = false;
      bool TVCFURJwsu = false;
      bool TISVlCfRWT = false;
      bool SzMWPjXIHc = false;
      bool nZWcSgDNIa = false;
      bool ljNjhIlYCJ = false;
      bool HYHPnUJfpj = false;
      bool sAoQHsloCE = false;
      bool zRJuhhlcnG = false;
      bool yzGxVORHoy = false;
      bool XWWXhkuxbn = false;
      bool WwWxKoOMgG = false;
      bool hfqjltsqtr = false;
      bool aeADgctlNw = false;
      string mEkoDsnjXc;
      string fxTHjJnqhn;
      string UcbfgydYyR;
      string GITtuGIwaZ;
      string wdTschTbrB;
      string xVeCwKcFHE;
      string OPlGVXdZMd;
      string ArPIqqIiDz;
      string dCfwTjcRyj;
      string cDnVKgrMWE;
      string EtPOBEGWKF;
      string BsCIZLiplk;
      string uLabAxEtxK;
      string ywLyujmRuO;
      string dFGsiiAewz;
      string xCZkJrTmOD;
      string AMYAGFhENp;
      string YRtWHoFhsQ;
      string wYxyMwVanC;
      string PzDqORgGmc;
      if(mEkoDsnjXc == EtPOBEGWKF){BwRFZfHCdU = true;}
      else if(EtPOBEGWKF == mEkoDsnjXc){nZWcSgDNIa = true;}
      if(fxTHjJnqhn == BsCIZLiplk){lktxGaOamJ = true;}
      else if(BsCIZLiplk == fxTHjJnqhn){ljNjhIlYCJ = true;}
      if(UcbfgydYyR == uLabAxEtxK){jGPKZYOCIo = true;}
      else if(uLabAxEtxK == UcbfgydYyR){HYHPnUJfpj = true;}
      if(GITtuGIwaZ == ywLyujmRuO){IzuPOzHrXg = true;}
      else if(ywLyujmRuO == GITtuGIwaZ){sAoQHsloCE = true;}
      if(wdTschTbrB == dFGsiiAewz){oSxTQeFFjm = true;}
      else if(dFGsiiAewz == wdTschTbrB){zRJuhhlcnG = true;}
      if(xVeCwKcFHE == xCZkJrTmOD){DFTcsugHeB = true;}
      else if(xCZkJrTmOD == xVeCwKcFHE){yzGxVORHoy = true;}
      if(OPlGVXdZMd == AMYAGFhENp){REtnMmpeiH = true;}
      else if(AMYAGFhENp == OPlGVXdZMd){XWWXhkuxbn = true;}
      if(ArPIqqIiDz == YRtWHoFhsQ){TVCFURJwsu = true;}
      if(dCfwTjcRyj == wYxyMwVanC){TISVlCfRWT = true;}
      if(cDnVKgrMWE == PzDqORgGmc){SzMWPjXIHc = true;}
      while(YRtWHoFhsQ == ArPIqqIiDz){WwWxKoOMgG = true;}
      while(wYxyMwVanC == wYxyMwVanC){hfqjltsqtr = true;}
      while(PzDqORgGmc == PzDqORgGmc){aeADgctlNw = true;}
      if(BwRFZfHCdU == true){BwRFZfHCdU = false;}
      if(lktxGaOamJ == true){lktxGaOamJ = false;}
      if(jGPKZYOCIo == true){jGPKZYOCIo = false;}
      if(IzuPOzHrXg == true){IzuPOzHrXg = false;}
      if(oSxTQeFFjm == true){oSxTQeFFjm = false;}
      if(DFTcsugHeB == true){DFTcsugHeB = false;}
      if(REtnMmpeiH == true){REtnMmpeiH = false;}
      if(TVCFURJwsu == true){TVCFURJwsu = false;}
      if(TISVlCfRWT == true){TISVlCfRWT = false;}
      if(SzMWPjXIHc == true){SzMWPjXIHc = false;}
      if(nZWcSgDNIa == true){nZWcSgDNIa = false;}
      if(ljNjhIlYCJ == true){ljNjhIlYCJ = false;}
      if(HYHPnUJfpj == true){HYHPnUJfpj = false;}
      if(sAoQHsloCE == true){sAoQHsloCE = false;}
      if(zRJuhhlcnG == true){zRJuhhlcnG = false;}
      if(yzGxVORHoy == true){yzGxVORHoy = false;}
      if(XWWXhkuxbn == true){XWWXhkuxbn = false;}
      if(WwWxKoOMgG == true){WwWxKoOMgG = false;}
      if(hfqjltsqtr == true){hfqjltsqtr = false;}
      if(aeADgctlNw == true){aeADgctlNw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJHEOUASBI
{ 
  void cmjVUitKky()
  { 
      bool SKSQMmLemj = false;
      bool CHzopDkKFe = false;
      bool AQbRIyAVIm = false;
      bool HhylDEMByZ = false;
      bool VqpEoAPSck = false;
      bool AzxMOBiBHN = false;
      bool moVAcUJMlk = false;
      bool qiLfIJZWbI = false;
      bool igsWlHjlWB = false;
      bool VLtklgUpaU = false;
      bool pCfqtQnQEF = false;
      bool aLYzeFwyNU = false;
      bool kXpkPfnZsb = false;
      bool njwHRgABcV = false;
      bool SShRZJluGg = false;
      bool jVcFjSLubO = false;
      bool bNXbQqPRgy = false;
      bool EuVrCRpYLF = false;
      bool ssTMqRGpXz = false;
      bool UFYNsEuFAh = false;
      string ushmBYmkNN;
      string XFiWgPGiau;
      string BdufXfpuyd;
      string GkCqZxlgbk;
      string PCgfmxhlea;
      string PMxGsRyBPV;
      string hrliHlDqwi;
      string cYHofywOrZ;
      string xEPWNtnwyH;
      string ykRGDXPxYA;
      string tqowypEHat;
      string VjIoXcbOUN;
      string yGsnjrHBlI;
      string hyoqfGPTYX;
      string ofVDlNbbhZ;
      string uBbLCmxALF;
      string iDVSLWuQJR;
      string NIoxXRkoBV;
      string PeSLMgVdor;
      string IOITokKDqP;
      if(ushmBYmkNN == tqowypEHat){SKSQMmLemj = true;}
      else if(tqowypEHat == ushmBYmkNN){pCfqtQnQEF = true;}
      if(XFiWgPGiau == VjIoXcbOUN){CHzopDkKFe = true;}
      else if(VjIoXcbOUN == XFiWgPGiau){aLYzeFwyNU = true;}
      if(BdufXfpuyd == yGsnjrHBlI){AQbRIyAVIm = true;}
      else if(yGsnjrHBlI == BdufXfpuyd){kXpkPfnZsb = true;}
      if(GkCqZxlgbk == hyoqfGPTYX){HhylDEMByZ = true;}
      else if(hyoqfGPTYX == GkCqZxlgbk){njwHRgABcV = true;}
      if(PCgfmxhlea == ofVDlNbbhZ){VqpEoAPSck = true;}
      else if(ofVDlNbbhZ == PCgfmxhlea){SShRZJluGg = true;}
      if(PMxGsRyBPV == uBbLCmxALF){AzxMOBiBHN = true;}
      else if(uBbLCmxALF == PMxGsRyBPV){jVcFjSLubO = true;}
      if(hrliHlDqwi == iDVSLWuQJR){moVAcUJMlk = true;}
      else if(iDVSLWuQJR == hrliHlDqwi){bNXbQqPRgy = true;}
      if(cYHofywOrZ == NIoxXRkoBV){qiLfIJZWbI = true;}
      if(xEPWNtnwyH == PeSLMgVdor){igsWlHjlWB = true;}
      if(ykRGDXPxYA == IOITokKDqP){VLtklgUpaU = true;}
      while(NIoxXRkoBV == cYHofywOrZ){EuVrCRpYLF = true;}
      while(PeSLMgVdor == PeSLMgVdor){ssTMqRGpXz = true;}
      while(IOITokKDqP == IOITokKDqP){UFYNsEuFAh = true;}
      if(SKSQMmLemj == true){SKSQMmLemj = false;}
      if(CHzopDkKFe == true){CHzopDkKFe = false;}
      if(AQbRIyAVIm == true){AQbRIyAVIm = false;}
      if(HhylDEMByZ == true){HhylDEMByZ = false;}
      if(VqpEoAPSck == true){VqpEoAPSck = false;}
      if(AzxMOBiBHN == true){AzxMOBiBHN = false;}
      if(moVAcUJMlk == true){moVAcUJMlk = false;}
      if(qiLfIJZWbI == true){qiLfIJZWbI = false;}
      if(igsWlHjlWB == true){igsWlHjlWB = false;}
      if(VLtklgUpaU == true){VLtklgUpaU = false;}
      if(pCfqtQnQEF == true){pCfqtQnQEF = false;}
      if(aLYzeFwyNU == true){aLYzeFwyNU = false;}
      if(kXpkPfnZsb == true){kXpkPfnZsb = false;}
      if(njwHRgABcV == true){njwHRgABcV = false;}
      if(SShRZJluGg == true){SShRZJluGg = false;}
      if(jVcFjSLubO == true){jVcFjSLubO = false;}
      if(bNXbQqPRgy == true){bNXbQqPRgy = false;}
      if(EuVrCRpYLF == true){EuVrCRpYLF = false;}
      if(ssTMqRGpXz == true){ssTMqRGpXz = false;}
      if(UFYNsEuFAh == true){UFYNsEuFAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFTGEFRJYG
{ 
  void icVdXYLCPt()
  { 
      bool nNYjSuNMVE = false;
      bool AkIlIqBEoh = false;
      bool VgdcNcbAHm = false;
      bool lGgZmkKaYS = false;
      bool FHsKWdowIQ = false;
      bool dAEnmHjwWo = false;
      bool TMFhRsEhzW = false;
      bool fafVbNnSGi = false;
      bool mfrqJlBrmf = false;
      bool BNDjzrCKsc = false;
      bool ZGwkjCUhLZ = false;
      bool SRomBmUNYf = false;
      bool rLuTVRWuVj = false;
      bool KcYcJfiGHG = false;
      bool QSgNMiYQhM = false;
      bool XokMkOLcPR = false;
      bool eYLbPprMdU = false;
      bool ENGSPYehHl = false;
      bool sGNJLUqMrt = false;
      bool UGqpaqHExW = false;
      string RuhoWtMDTa;
      string uqrRfoAIrM;
      string YIsYraLmXG;
      string jQVtwkVtot;
      string iClpVUKuTi;
      string pFfAWJBIww;
      string hYfNpeUxUt;
      string TGSxcVVCDX;
      string PQTnQejVXm;
      string iMxsLJWYzq;
      string ANZYPilhWA;
      string mzFXfRFqwL;
      string tzZhLGIYlS;
      string zxDMXCpuYg;
      string rCyWzjHYNt;
      string EfbnwAmrNI;
      string ZMwDBpwsAc;
      string bJROSrACia;
      string ziLqOTUOPW;
      string OyhQHfFtVI;
      if(RuhoWtMDTa == ANZYPilhWA){nNYjSuNMVE = true;}
      else if(ANZYPilhWA == RuhoWtMDTa){ZGwkjCUhLZ = true;}
      if(uqrRfoAIrM == mzFXfRFqwL){AkIlIqBEoh = true;}
      else if(mzFXfRFqwL == uqrRfoAIrM){SRomBmUNYf = true;}
      if(YIsYraLmXG == tzZhLGIYlS){VgdcNcbAHm = true;}
      else if(tzZhLGIYlS == YIsYraLmXG){rLuTVRWuVj = true;}
      if(jQVtwkVtot == zxDMXCpuYg){lGgZmkKaYS = true;}
      else if(zxDMXCpuYg == jQVtwkVtot){KcYcJfiGHG = true;}
      if(iClpVUKuTi == rCyWzjHYNt){FHsKWdowIQ = true;}
      else if(rCyWzjHYNt == iClpVUKuTi){QSgNMiYQhM = true;}
      if(pFfAWJBIww == EfbnwAmrNI){dAEnmHjwWo = true;}
      else if(EfbnwAmrNI == pFfAWJBIww){XokMkOLcPR = true;}
      if(hYfNpeUxUt == ZMwDBpwsAc){TMFhRsEhzW = true;}
      else if(ZMwDBpwsAc == hYfNpeUxUt){eYLbPprMdU = true;}
      if(TGSxcVVCDX == bJROSrACia){fafVbNnSGi = true;}
      if(PQTnQejVXm == ziLqOTUOPW){mfrqJlBrmf = true;}
      if(iMxsLJWYzq == OyhQHfFtVI){BNDjzrCKsc = true;}
      while(bJROSrACia == TGSxcVVCDX){ENGSPYehHl = true;}
      while(ziLqOTUOPW == ziLqOTUOPW){sGNJLUqMrt = true;}
      while(OyhQHfFtVI == OyhQHfFtVI){UGqpaqHExW = true;}
      if(nNYjSuNMVE == true){nNYjSuNMVE = false;}
      if(AkIlIqBEoh == true){AkIlIqBEoh = false;}
      if(VgdcNcbAHm == true){VgdcNcbAHm = false;}
      if(lGgZmkKaYS == true){lGgZmkKaYS = false;}
      if(FHsKWdowIQ == true){FHsKWdowIQ = false;}
      if(dAEnmHjwWo == true){dAEnmHjwWo = false;}
      if(TMFhRsEhzW == true){TMFhRsEhzW = false;}
      if(fafVbNnSGi == true){fafVbNnSGi = false;}
      if(mfrqJlBrmf == true){mfrqJlBrmf = false;}
      if(BNDjzrCKsc == true){BNDjzrCKsc = false;}
      if(ZGwkjCUhLZ == true){ZGwkjCUhLZ = false;}
      if(SRomBmUNYf == true){SRomBmUNYf = false;}
      if(rLuTVRWuVj == true){rLuTVRWuVj = false;}
      if(KcYcJfiGHG == true){KcYcJfiGHG = false;}
      if(QSgNMiYQhM == true){QSgNMiYQhM = false;}
      if(XokMkOLcPR == true){XokMkOLcPR = false;}
      if(eYLbPprMdU == true){eYLbPprMdU = false;}
      if(ENGSPYehHl == true){ENGSPYehHl = false;}
      if(sGNJLUqMrt == true){sGNJLUqMrt = false;}
      if(UGqpaqHExW == true){UGqpaqHExW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOGIBZQIPR
{ 
  void gEnjSYloyh()
  { 
      bool cEpzhDUQEO = false;
      bool AlupoLfRWT = false;
      bool GLnjAYsjCY = false;
      bool mVCGIkDfaf = false;
      bool lioJxnLCYT = false;
      bool NBUKTQQGzI = false;
      bool KjNfaejogE = false;
      bool HzpqgXVelL = false;
      bool MpLiKlBqlr = false;
      bool UxgSVCUJhS = false;
      bool EWUULOKddw = false;
      bool tlTmuTXeUo = false;
      bool drDoiKRXUe = false;
      bool CMwTGpUqWw = false;
      bool aXNoxictWB = false;
      bool eporoLSfkB = false;
      bool xmIythoAfE = false;
      bool yfIXNFeNrA = false;
      bool hXBTAMWEdu = false;
      bool XoGUznOOuP = false;
      string lyQxgLWYLn;
      string BdoCcezajy;
      string VRJpKGQuAd;
      string qDktEyzIXc;
      string ZjAsWUCobS;
      string RUHFmUoalZ;
      string tbYgwyruxd;
      string fpDGXkQPTp;
      string DbTgMWufHj;
      string IYWxhyLSxY;
      string bHqxmaRAgB;
      string DYGwWSHrUY;
      string CMmNVHTFYZ;
      string ZxStNukVsl;
      string FuyFfiRZZP;
      string pSyXVOTcbe;
      string GLbGaFGMia;
      string glyhSHNggl;
      string pteJjGztXy;
      string aHsNftTrea;
      if(lyQxgLWYLn == bHqxmaRAgB){cEpzhDUQEO = true;}
      else if(bHqxmaRAgB == lyQxgLWYLn){EWUULOKddw = true;}
      if(BdoCcezajy == DYGwWSHrUY){AlupoLfRWT = true;}
      else if(DYGwWSHrUY == BdoCcezajy){tlTmuTXeUo = true;}
      if(VRJpKGQuAd == CMmNVHTFYZ){GLnjAYsjCY = true;}
      else if(CMmNVHTFYZ == VRJpKGQuAd){drDoiKRXUe = true;}
      if(qDktEyzIXc == ZxStNukVsl){mVCGIkDfaf = true;}
      else if(ZxStNukVsl == qDktEyzIXc){CMwTGpUqWw = true;}
      if(ZjAsWUCobS == FuyFfiRZZP){lioJxnLCYT = true;}
      else if(FuyFfiRZZP == ZjAsWUCobS){aXNoxictWB = true;}
      if(RUHFmUoalZ == pSyXVOTcbe){NBUKTQQGzI = true;}
      else if(pSyXVOTcbe == RUHFmUoalZ){eporoLSfkB = true;}
      if(tbYgwyruxd == GLbGaFGMia){KjNfaejogE = true;}
      else if(GLbGaFGMia == tbYgwyruxd){xmIythoAfE = true;}
      if(fpDGXkQPTp == glyhSHNggl){HzpqgXVelL = true;}
      if(DbTgMWufHj == pteJjGztXy){MpLiKlBqlr = true;}
      if(IYWxhyLSxY == aHsNftTrea){UxgSVCUJhS = true;}
      while(glyhSHNggl == fpDGXkQPTp){yfIXNFeNrA = true;}
      while(pteJjGztXy == pteJjGztXy){hXBTAMWEdu = true;}
      while(aHsNftTrea == aHsNftTrea){XoGUznOOuP = true;}
      if(cEpzhDUQEO == true){cEpzhDUQEO = false;}
      if(AlupoLfRWT == true){AlupoLfRWT = false;}
      if(GLnjAYsjCY == true){GLnjAYsjCY = false;}
      if(mVCGIkDfaf == true){mVCGIkDfaf = false;}
      if(lioJxnLCYT == true){lioJxnLCYT = false;}
      if(NBUKTQQGzI == true){NBUKTQQGzI = false;}
      if(KjNfaejogE == true){KjNfaejogE = false;}
      if(HzpqgXVelL == true){HzpqgXVelL = false;}
      if(MpLiKlBqlr == true){MpLiKlBqlr = false;}
      if(UxgSVCUJhS == true){UxgSVCUJhS = false;}
      if(EWUULOKddw == true){EWUULOKddw = false;}
      if(tlTmuTXeUo == true){tlTmuTXeUo = false;}
      if(drDoiKRXUe == true){drDoiKRXUe = false;}
      if(CMwTGpUqWw == true){CMwTGpUqWw = false;}
      if(aXNoxictWB == true){aXNoxictWB = false;}
      if(eporoLSfkB == true){eporoLSfkB = false;}
      if(xmIythoAfE == true){xmIythoAfE = false;}
      if(yfIXNFeNrA == true){yfIXNFeNrA = false;}
      if(hXBTAMWEdu == true){hXBTAMWEdu = false;}
      if(XoGUznOOuP == true){XoGUznOOuP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TAUKQEIFJY
{ 
  void QikCczMCmg()
  { 
      bool FrrLykzHHc = false;
      bool DbpKBBUwji = false;
      bool ewmxPeJOky = false;
      bool OGWQFpDnCr = false;
      bool GJDdboydXU = false;
      bool jaZBoJFtuS = false;
      bool bkWJOwEYFK = false;
      bool xfsqbVsJVZ = false;
      bool gfpPNmfVau = false;
      bool kIrjQVlsPf = false;
      bool kYYNWEhhYT = false;
      bool QuYVkutGua = false;
      bool PhyJZomJZG = false;
      bool iztonHGcsJ = false;
      bool FxwGeojWyU = false;
      bool afxnPCaPmh = false;
      bool QXISjRBigd = false;
      bool oRNlVRlqdj = false;
      bool FQKFeDBFZk = false;
      bool gqoKrgocVN = false;
      string HDDoQCdCOg;
      string HRHmsfAoDM;
      string YLPyDSWPqJ;
      string QSeTodHjWh;
      string HurEIuDbJc;
      string ddjfLunFkx;
      string eOKEPnmnxO;
      string XQRUFdTKoH;
      string PuFNfliyHt;
      string pCzZCrjmnT;
      string IPeuENMOah;
      string bcPcgjIwYc;
      string FnfDYVQrSM;
      string sfVVzAPKIR;
      string ZTXYRMmVrR;
      string imOLOTibVi;
      string wUwNowGtdg;
      string TynGDlQHkL;
      string huzAdGQKGf;
      string RnnYVFWJjU;
      if(HDDoQCdCOg == IPeuENMOah){FrrLykzHHc = true;}
      else if(IPeuENMOah == HDDoQCdCOg){kYYNWEhhYT = true;}
      if(HRHmsfAoDM == bcPcgjIwYc){DbpKBBUwji = true;}
      else if(bcPcgjIwYc == HRHmsfAoDM){QuYVkutGua = true;}
      if(YLPyDSWPqJ == FnfDYVQrSM){ewmxPeJOky = true;}
      else if(FnfDYVQrSM == YLPyDSWPqJ){PhyJZomJZG = true;}
      if(QSeTodHjWh == sfVVzAPKIR){OGWQFpDnCr = true;}
      else if(sfVVzAPKIR == QSeTodHjWh){iztonHGcsJ = true;}
      if(HurEIuDbJc == ZTXYRMmVrR){GJDdboydXU = true;}
      else if(ZTXYRMmVrR == HurEIuDbJc){FxwGeojWyU = true;}
      if(ddjfLunFkx == imOLOTibVi){jaZBoJFtuS = true;}
      else if(imOLOTibVi == ddjfLunFkx){afxnPCaPmh = true;}
      if(eOKEPnmnxO == wUwNowGtdg){bkWJOwEYFK = true;}
      else if(wUwNowGtdg == eOKEPnmnxO){QXISjRBigd = true;}
      if(XQRUFdTKoH == TynGDlQHkL){xfsqbVsJVZ = true;}
      if(PuFNfliyHt == huzAdGQKGf){gfpPNmfVau = true;}
      if(pCzZCrjmnT == RnnYVFWJjU){kIrjQVlsPf = true;}
      while(TynGDlQHkL == XQRUFdTKoH){oRNlVRlqdj = true;}
      while(huzAdGQKGf == huzAdGQKGf){FQKFeDBFZk = true;}
      while(RnnYVFWJjU == RnnYVFWJjU){gqoKrgocVN = true;}
      if(FrrLykzHHc == true){FrrLykzHHc = false;}
      if(DbpKBBUwji == true){DbpKBBUwji = false;}
      if(ewmxPeJOky == true){ewmxPeJOky = false;}
      if(OGWQFpDnCr == true){OGWQFpDnCr = false;}
      if(GJDdboydXU == true){GJDdboydXU = false;}
      if(jaZBoJFtuS == true){jaZBoJFtuS = false;}
      if(bkWJOwEYFK == true){bkWJOwEYFK = false;}
      if(xfsqbVsJVZ == true){xfsqbVsJVZ = false;}
      if(gfpPNmfVau == true){gfpPNmfVau = false;}
      if(kIrjQVlsPf == true){kIrjQVlsPf = false;}
      if(kYYNWEhhYT == true){kYYNWEhhYT = false;}
      if(QuYVkutGua == true){QuYVkutGua = false;}
      if(PhyJZomJZG == true){PhyJZomJZG = false;}
      if(iztonHGcsJ == true){iztonHGcsJ = false;}
      if(FxwGeojWyU == true){FxwGeojWyU = false;}
      if(afxnPCaPmh == true){afxnPCaPmh = false;}
      if(QXISjRBigd == true){QXISjRBigd = false;}
      if(oRNlVRlqdj == true){oRNlVRlqdj = false;}
      if(FQKFeDBFZk == true){FQKFeDBFZk = false;}
      if(gqoKrgocVN == true){gqoKrgocVN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTBGMUSWJL
{ 
  void TucWTunPou()
  { 
      bool eTxbjzgflI = false;
      bool lngjnZTrBw = false;
      bool mmiFcbLHfK = false;
      bool VUWbxTXyIS = false;
      bool GEzRkZPZwC = false;
      bool HhbcEqjqyH = false;
      bool nYAamQQElU = false;
      bool BVihphnRUD = false;
      bool MlKcDmrsWF = false;
      bool igzAegEXeU = false;
      bool IKmbAkzsmW = false;
      bool DSWutBNXXz = false;
      bool YXhfkUWhDI = false;
      bool dQlztCyibR = false;
      bool nzGACQJEFc = false;
      bool TgzfukbHqe = false;
      bool OQpdrmgWAr = false;
      bool DeuFLZQgdT = false;
      bool LSbZowQGDJ = false;
      bool ZqqwDWIbIO = false;
      string FXmsiPcyPU;
      string aNOAggtuPQ;
      string lNuIUAMXkR;
      string BUMyEOxkrh;
      string QsSCSgIfKd;
      string BqUGpqbeYh;
      string DENxTGBPuS;
      string jIDhzstspm;
      string rgNHQKzFHM;
      string lSMJeLfUhL;
      string fsjrtrnmHx;
      string xinkpVqFgJ;
      string HuHifRwsCm;
      string MYKdHzxVNX;
      string VLxKPDdaTJ;
      string UZnYEjkALb;
      string utkTjXYJdq;
      string YUrImwyxTb;
      string nVZsSmkkZX;
      string NwJkcbZdZq;
      if(FXmsiPcyPU == fsjrtrnmHx){eTxbjzgflI = true;}
      else if(fsjrtrnmHx == FXmsiPcyPU){IKmbAkzsmW = true;}
      if(aNOAggtuPQ == xinkpVqFgJ){lngjnZTrBw = true;}
      else if(xinkpVqFgJ == aNOAggtuPQ){DSWutBNXXz = true;}
      if(lNuIUAMXkR == HuHifRwsCm){mmiFcbLHfK = true;}
      else if(HuHifRwsCm == lNuIUAMXkR){YXhfkUWhDI = true;}
      if(BUMyEOxkrh == MYKdHzxVNX){VUWbxTXyIS = true;}
      else if(MYKdHzxVNX == BUMyEOxkrh){dQlztCyibR = true;}
      if(QsSCSgIfKd == VLxKPDdaTJ){GEzRkZPZwC = true;}
      else if(VLxKPDdaTJ == QsSCSgIfKd){nzGACQJEFc = true;}
      if(BqUGpqbeYh == UZnYEjkALb){HhbcEqjqyH = true;}
      else if(UZnYEjkALb == BqUGpqbeYh){TgzfukbHqe = true;}
      if(DENxTGBPuS == utkTjXYJdq){nYAamQQElU = true;}
      else if(utkTjXYJdq == DENxTGBPuS){OQpdrmgWAr = true;}
      if(jIDhzstspm == YUrImwyxTb){BVihphnRUD = true;}
      if(rgNHQKzFHM == nVZsSmkkZX){MlKcDmrsWF = true;}
      if(lSMJeLfUhL == NwJkcbZdZq){igzAegEXeU = true;}
      while(YUrImwyxTb == jIDhzstspm){DeuFLZQgdT = true;}
      while(nVZsSmkkZX == nVZsSmkkZX){LSbZowQGDJ = true;}
      while(NwJkcbZdZq == NwJkcbZdZq){ZqqwDWIbIO = true;}
      if(eTxbjzgflI == true){eTxbjzgflI = false;}
      if(lngjnZTrBw == true){lngjnZTrBw = false;}
      if(mmiFcbLHfK == true){mmiFcbLHfK = false;}
      if(VUWbxTXyIS == true){VUWbxTXyIS = false;}
      if(GEzRkZPZwC == true){GEzRkZPZwC = false;}
      if(HhbcEqjqyH == true){HhbcEqjqyH = false;}
      if(nYAamQQElU == true){nYAamQQElU = false;}
      if(BVihphnRUD == true){BVihphnRUD = false;}
      if(MlKcDmrsWF == true){MlKcDmrsWF = false;}
      if(igzAegEXeU == true){igzAegEXeU = false;}
      if(IKmbAkzsmW == true){IKmbAkzsmW = false;}
      if(DSWutBNXXz == true){DSWutBNXXz = false;}
      if(YXhfkUWhDI == true){YXhfkUWhDI = false;}
      if(dQlztCyibR == true){dQlztCyibR = false;}
      if(nzGACQJEFc == true){nzGACQJEFc = false;}
      if(TgzfukbHqe == true){TgzfukbHqe = false;}
      if(OQpdrmgWAr == true){OQpdrmgWAr = false;}
      if(DeuFLZQgdT == true){DeuFLZQgdT = false;}
      if(LSbZowQGDJ == true){LSbZowQGDJ = false;}
      if(ZqqwDWIbIO == true){ZqqwDWIbIO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMDUTBJRYW
{ 
  void ftEEWnZNiu()
  { 
      bool TxRQaQhzMS = false;
      bool njRcNXTzta = false;
      bool mNFpDfnOHS = false;
      bool zftJRacAwF = false;
      bool DgKpBOrDsn = false;
      bool EkprOFraMu = false;
      bool cSrtSIoILl = false;
      bool tTCoWFDOoo = false;
      bool mkUTOOoCtM = false;
      bool iBmBckoPXs = false;
      bool YjqGsjhBUJ = false;
      bool BdlXHrxXfD = false;
      bool SmNyDrfBMl = false;
      bool PmqwPCsNad = false;
      bool gmgkKFPOtk = false;
      bool mQjTZlWrDA = false;
      bool EgoisNmpIE = false;
      bool yjxBWfFbny = false;
      bool cQHbzyDWWc = false;
      bool fAKaYAyyqx = false;
      string OMurhHdwQr;
      string iLZASqsDMc;
      string QbTOtzeNNZ;
      string IVNzcKTYzZ;
      string SEJnHXPgNu;
      string gaAjPmrgyh;
      string cQiqiNxaWI;
      string XTDmKMSfGV;
      string jxARrhUcip;
      string RlaRwBVREt;
      string ZnJFXMXNZD;
      string UMZbyePQyB;
      string rUrgpkskpI;
      string pAaLuunute;
      string KHDeVEMyTR;
      string lESDCFwcOl;
      string TlXRMTkOfC;
      string qUWTqjRMKk;
      string YuRXWlgWJp;
      string yKfHLXjkSB;
      if(OMurhHdwQr == ZnJFXMXNZD){TxRQaQhzMS = true;}
      else if(ZnJFXMXNZD == OMurhHdwQr){YjqGsjhBUJ = true;}
      if(iLZASqsDMc == UMZbyePQyB){njRcNXTzta = true;}
      else if(UMZbyePQyB == iLZASqsDMc){BdlXHrxXfD = true;}
      if(QbTOtzeNNZ == rUrgpkskpI){mNFpDfnOHS = true;}
      else if(rUrgpkskpI == QbTOtzeNNZ){SmNyDrfBMl = true;}
      if(IVNzcKTYzZ == pAaLuunute){zftJRacAwF = true;}
      else if(pAaLuunute == IVNzcKTYzZ){PmqwPCsNad = true;}
      if(SEJnHXPgNu == KHDeVEMyTR){DgKpBOrDsn = true;}
      else if(KHDeVEMyTR == SEJnHXPgNu){gmgkKFPOtk = true;}
      if(gaAjPmrgyh == lESDCFwcOl){EkprOFraMu = true;}
      else if(lESDCFwcOl == gaAjPmrgyh){mQjTZlWrDA = true;}
      if(cQiqiNxaWI == TlXRMTkOfC){cSrtSIoILl = true;}
      else if(TlXRMTkOfC == cQiqiNxaWI){EgoisNmpIE = true;}
      if(XTDmKMSfGV == qUWTqjRMKk){tTCoWFDOoo = true;}
      if(jxARrhUcip == YuRXWlgWJp){mkUTOOoCtM = true;}
      if(RlaRwBVREt == yKfHLXjkSB){iBmBckoPXs = true;}
      while(qUWTqjRMKk == XTDmKMSfGV){yjxBWfFbny = true;}
      while(YuRXWlgWJp == YuRXWlgWJp){cQHbzyDWWc = true;}
      while(yKfHLXjkSB == yKfHLXjkSB){fAKaYAyyqx = true;}
      if(TxRQaQhzMS == true){TxRQaQhzMS = false;}
      if(njRcNXTzta == true){njRcNXTzta = false;}
      if(mNFpDfnOHS == true){mNFpDfnOHS = false;}
      if(zftJRacAwF == true){zftJRacAwF = false;}
      if(DgKpBOrDsn == true){DgKpBOrDsn = false;}
      if(EkprOFraMu == true){EkprOFraMu = false;}
      if(cSrtSIoILl == true){cSrtSIoILl = false;}
      if(tTCoWFDOoo == true){tTCoWFDOoo = false;}
      if(mkUTOOoCtM == true){mkUTOOoCtM = false;}
      if(iBmBckoPXs == true){iBmBckoPXs = false;}
      if(YjqGsjhBUJ == true){YjqGsjhBUJ = false;}
      if(BdlXHrxXfD == true){BdlXHrxXfD = false;}
      if(SmNyDrfBMl == true){SmNyDrfBMl = false;}
      if(PmqwPCsNad == true){PmqwPCsNad = false;}
      if(gmgkKFPOtk == true){gmgkKFPOtk = false;}
      if(mQjTZlWrDA == true){mQjTZlWrDA = false;}
      if(EgoisNmpIE == true){EgoisNmpIE = false;}
      if(yjxBWfFbny == true){yjxBWfFbny = false;}
      if(cQHbzyDWWc == true){cQHbzyDWWc = false;}
      if(fAKaYAyyqx == true){fAKaYAyyqx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQAEJWQVNU
{ 
  void sfKSnnIBWQ()
  { 
      bool aNkgCPcXnL = false;
      bool acyDEJEOck = false;
      bool MeUlrczDks = false;
      bool WcTTTJEbXy = false;
      bool SFcYJXOrBG = false;
      bool bwwTowsyoY = false;
      bool PYltoyJejt = false;
      bool EbqeSHBucT = false;
      bool OHBeQZfzeW = false;
      bool QGmyisShjK = false;
      bool OjHGBAFRBh = false;
      bool txVVKHXHdO = false;
      bool RJAMdyoruZ = false;
      bool nSLSFeAucP = false;
      bool UOywcTjQna = false;
      bool VLEUrEjucC = false;
      bool LMVasbkDPe = false;
      bool HbdNsDLDjJ = false;
      bool OXEUEcOpZA = false;
      bool uERaEIsWDB = false;
      string ErSHNjlGiO;
      string yffWwqdBnc;
      string ZRGbLuxmPC;
      string BFbTXhunqD;
      string BRXtUAahcO;
      string nItsUmlquR;
      string mzpgMsDLzN;
      string upJkaHtLGK;
      string TPJAOsKizk;
      string wErYQBaqgb;
      string xPhPSyyJRM;
      string sZjjyWppRT;
      string hTLNQqykTZ;
      string fCddNEgtgQ;
      string tARlrWTHas;
      string LkYNscDTyb;
      string ANoqgpuFWs;
      string puIBZgCZVt;
      string XpJaOucQkj;
      string BMuFQfKZFC;
      if(ErSHNjlGiO == xPhPSyyJRM){aNkgCPcXnL = true;}
      else if(xPhPSyyJRM == ErSHNjlGiO){OjHGBAFRBh = true;}
      if(yffWwqdBnc == sZjjyWppRT){acyDEJEOck = true;}
      else if(sZjjyWppRT == yffWwqdBnc){txVVKHXHdO = true;}
      if(ZRGbLuxmPC == hTLNQqykTZ){MeUlrczDks = true;}
      else if(hTLNQqykTZ == ZRGbLuxmPC){RJAMdyoruZ = true;}
      if(BFbTXhunqD == fCddNEgtgQ){WcTTTJEbXy = true;}
      else if(fCddNEgtgQ == BFbTXhunqD){nSLSFeAucP = true;}
      if(BRXtUAahcO == tARlrWTHas){SFcYJXOrBG = true;}
      else if(tARlrWTHas == BRXtUAahcO){UOywcTjQna = true;}
      if(nItsUmlquR == LkYNscDTyb){bwwTowsyoY = true;}
      else if(LkYNscDTyb == nItsUmlquR){VLEUrEjucC = true;}
      if(mzpgMsDLzN == ANoqgpuFWs){PYltoyJejt = true;}
      else if(ANoqgpuFWs == mzpgMsDLzN){LMVasbkDPe = true;}
      if(upJkaHtLGK == puIBZgCZVt){EbqeSHBucT = true;}
      if(TPJAOsKizk == XpJaOucQkj){OHBeQZfzeW = true;}
      if(wErYQBaqgb == BMuFQfKZFC){QGmyisShjK = true;}
      while(puIBZgCZVt == upJkaHtLGK){HbdNsDLDjJ = true;}
      while(XpJaOucQkj == XpJaOucQkj){OXEUEcOpZA = true;}
      while(BMuFQfKZFC == BMuFQfKZFC){uERaEIsWDB = true;}
      if(aNkgCPcXnL == true){aNkgCPcXnL = false;}
      if(acyDEJEOck == true){acyDEJEOck = false;}
      if(MeUlrczDks == true){MeUlrczDks = false;}
      if(WcTTTJEbXy == true){WcTTTJEbXy = false;}
      if(SFcYJXOrBG == true){SFcYJXOrBG = false;}
      if(bwwTowsyoY == true){bwwTowsyoY = false;}
      if(PYltoyJejt == true){PYltoyJejt = false;}
      if(EbqeSHBucT == true){EbqeSHBucT = false;}
      if(OHBeQZfzeW == true){OHBeQZfzeW = false;}
      if(QGmyisShjK == true){QGmyisShjK = false;}
      if(OjHGBAFRBh == true){OjHGBAFRBh = false;}
      if(txVVKHXHdO == true){txVVKHXHdO = false;}
      if(RJAMdyoruZ == true){RJAMdyoruZ = false;}
      if(nSLSFeAucP == true){nSLSFeAucP = false;}
      if(UOywcTjQna == true){UOywcTjQna = false;}
      if(VLEUrEjucC == true){VLEUrEjucC = false;}
      if(LMVasbkDPe == true){LMVasbkDPe = false;}
      if(HbdNsDLDjJ == true){HbdNsDLDjJ = false;}
      if(OXEUEcOpZA == true){OXEUEcOpZA = false;}
      if(uERaEIsWDB == true){uERaEIsWDB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQFNYOOTYB
{ 
  void ayItDrOkJt()
  { 
      bool ZEnIPOIkuX = false;
      bool dFMrCEchCe = false;
      bool PjaUJWHFwF = false;
      bool oRyBoxuOgA = false;
      bool EUtNTwOPWT = false;
      bool djVGwpdTzr = false;
      bool GDnphMGKCF = false;
      bool IOBBatpMAM = false;
      bool IricbFurFz = false;
      bool SaOotAgDfH = false;
      bool oEMQKPhUeB = false;
      bool zQTmiNULOc = false;
      bool QOEClgzMHa = false;
      bool NlgrWEfRRL = false;
      bool WaNDACHbFf = false;
      bool eUoCqazKdc = false;
      bool PVMEmMiaQe = false;
      bool hDsCFoABBj = false;
      bool ZXHbusxdBu = false;
      bool EUmowBOIPn = false;
      string sIQJomNEiY;
      string zuAODwiuNa;
      string GLOhEmNxsI;
      string IENOzQeycn;
      string YIMqejomKp;
      string QJPMrgthFC;
      string ZQLZQthkOm;
      string QjRYByzWCU;
      string xZlCrynBWR;
      string WxrZNIxmZk;
      string BEXXYfrpKs;
      string hWekFAdIgS;
      string FgNxPTqrKs;
      string BLxRSsBOdM;
      string GxpdiARHUN;
      string dnFHeUpaHE;
      string nzeRrVZMSL;
      string yOeULHpjOP;
      string BjWxONGoly;
      string CaHYXGSYkM;
      if(sIQJomNEiY == BEXXYfrpKs){ZEnIPOIkuX = true;}
      else if(BEXXYfrpKs == sIQJomNEiY){oEMQKPhUeB = true;}
      if(zuAODwiuNa == hWekFAdIgS){dFMrCEchCe = true;}
      else if(hWekFAdIgS == zuAODwiuNa){zQTmiNULOc = true;}
      if(GLOhEmNxsI == FgNxPTqrKs){PjaUJWHFwF = true;}
      else if(FgNxPTqrKs == GLOhEmNxsI){QOEClgzMHa = true;}
      if(IENOzQeycn == BLxRSsBOdM){oRyBoxuOgA = true;}
      else if(BLxRSsBOdM == IENOzQeycn){NlgrWEfRRL = true;}
      if(YIMqejomKp == GxpdiARHUN){EUtNTwOPWT = true;}
      else if(GxpdiARHUN == YIMqejomKp){WaNDACHbFf = true;}
      if(QJPMrgthFC == dnFHeUpaHE){djVGwpdTzr = true;}
      else if(dnFHeUpaHE == QJPMrgthFC){eUoCqazKdc = true;}
      if(ZQLZQthkOm == nzeRrVZMSL){GDnphMGKCF = true;}
      else if(nzeRrVZMSL == ZQLZQthkOm){PVMEmMiaQe = true;}
      if(QjRYByzWCU == yOeULHpjOP){IOBBatpMAM = true;}
      if(xZlCrynBWR == BjWxONGoly){IricbFurFz = true;}
      if(WxrZNIxmZk == CaHYXGSYkM){SaOotAgDfH = true;}
      while(yOeULHpjOP == QjRYByzWCU){hDsCFoABBj = true;}
      while(BjWxONGoly == BjWxONGoly){ZXHbusxdBu = true;}
      while(CaHYXGSYkM == CaHYXGSYkM){EUmowBOIPn = true;}
      if(ZEnIPOIkuX == true){ZEnIPOIkuX = false;}
      if(dFMrCEchCe == true){dFMrCEchCe = false;}
      if(PjaUJWHFwF == true){PjaUJWHFwF = false;}
      if(oRyBoxuOgA == true){oRyBoxuOgA = false;}
      if(EUtNTwOPWT == true){EUtNTwOPWT = false;}
      if(djVGwpdTzr == true){djVGwpdTzr = false;}
      if(GDnphMGKCF == true){GDnphMGKCF = false;}
      if(IOBBatpMAM == true){IOBBatpMAM = false;}
      if(IricbFurFz == true){IricbFurFz = false;}
      if(SaOotAgDfH == true){SaOotAgDfH = false;}
      if(oEMQKPhUeB == true){oEMQKPhUeB = false;}
      if(zQTmiNULOc == true){zQTmiNULOc = false;}
      if(QOEClgzMHa == true){QOEClgzMHa = false;}
      if(NlgrWEfRRL == true){NlgrWEfRRL = false;}
      if(WaNDACHbFf == true){WaNDACHbFf = false;}
      if(eUoCqazKdc == true){eUoCqazKdc = false;}
      if(PVMEmMiaQe == true){PVMEmMiaQe = false;}
      if(hDsCFoABBj == true){hDsCFoABBj = false;}
      if(ZXHbusxdBu == true){ZXHbusxdBu = false;}
      if(EUmowBOIPn == true){EUmowBOIPn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBHXFSRPYZ
{ 
  void ynVEKCzflZ()
  { 
      bool rTJkBYNsjj = false;
      bool nNeacwDham = false;
      bool tMeQfxQMBd = false;
      bool MQWppMEBAE = false;
      bool oWthyasOac = false;
      bool VKNeUforFD = false;
      bool HBqFWWpokP = false;
      bool rChWxXRwSE = false;
      bool DClYHCCrUJ = false;
      bool WLwwwnenKa = false;
      bool jEcKkTbpgx = false;
      bool NrZAAFOSyU = false;
      bool UyTbrfGlaJ = false;
      bool rckqUzYanm = false;
      bool aLKXudkuwp = false;
      bool YMppGlkBSE = false;
      bool NoPXFkGifA = false;
      bool fneKsImwfN = false;
      bool tKpjkemukh = false;
      bool OWIiZkwmRK = false;
      string wcWiZzCBGH;
      string mcUqkoVeeW;
      string ufweaVuRCZ;
      string pSUqmZQBVF;
      string YGNXuCdUng;
      string ErgMLPgqHE;
      string EkygRUIcEL;
      string YTJYxnSXjY;
      string rZcVUykIeX;
      string sYtRBnHgGZ;
      string sAQcIjhHOW;
      string xIHhLdHcLS;
      string izxfSzZrXJ;
      string glRJfqIAMj;
      string PctHajRLFW;
      string fdUmqsDjJJ;
      string KpjEpLqxCT;
      string VHPbDGFoFi;
      string gNlBcDQdSl;
      string nXpDZZsoRP;
      if(wcWiZzCBGH == sAQcIjhHOW){rTJkBYNsjj = true;}
      else if(sAQcIjhHOW == wcWiZzCBGH){jEcKkTbpgx = true;}
      if(mcUqkoVeeW == xIHhLdHcLS){nNeacwDham = true;}
      else if(xIHhLdHcLS == mcUqkoVeeW){NrZAAFOSyU = true;}
      if(ufweaVuRCZ == izxfSzZrXJ){tMeQfxQMBd = true;}
      else if(izxfSzZrXJ == ufweaVuRCZ){UyTbrfGlaJ = true;}
      if(pSUqmZQBVF == glRJfqIAMj){MQWppMEBAE = true;}
      else if(glRJfqIAMj == pSUqmZQBVF){rckqUzYanm = true;}
      if(YGNXuCdUng == PctHajRLFW){oWthyasOac = true;}
      else if(PctHajRLFW == YGNXuCdUng){aLKXudkuwp = true;}
      if(ErgMLPgqHE == fdUmqsDjJJ){VKNeUforFD = true;}
      else if(fdUmqsDjJJ == ErgMLPgqHE){YMppGlkBSE = true;}
      if(EkygRUIcEL == KpjEpLqxCT){HBqFWWpokP = true;}
      else if(KpjEpLqxCT == EkygRUIcEL){NoPXFkGifA = true;}
      if(YTJYxnSXjY == VHPbDGFoFi){rChWxXRwSE = true;}
      if(rZcVUykIeX == gNlBcDQdSl){DClYHCCrUJ = true;}
      if(sYtRBnHgGZ == nXpDZZsoRP){WLwwwnenKa = true;}
      while(VHPbDGFoFi == YTJYxnSXjY){fneKsImwfN = true;}
      while(gNlBcDQdSl == gNlBcDQdSl){tKpjkemukh = true;}
      while(nXpDZZsoRP == nXpDZZsoRP){OWIiZkwmRK = true;}
      if(rTJkBYNsjj == true){rTJkBYNsjj = false;}
      if(nNeacwDham == true){nNeacwDham = false;}
      if(tMeQfxQMBd == true){tMeQfxQMBd = false;}
      if(MQWppMEBAE == true){MQWppMEBAE = false;}
      if(oWthyasOac == true){oWthyasOac = false;}
      if(VKNeUforFD == true){VKNeUforFD = false;}
      if(HBqFWWpokP == true){HBqFWWpokP = false;}
      if(rChWxXRwSE == true){rChWxXRwSE = false;}
      if(DClYHCCrUJ == true){DClYHCCrUJ = false;}
      if(WLwwwnenKa == true){WLwwwnenKa = false;}
      if(jEcKkTbpgx == true){jEcKkTbpgx = false;}
      if(NrZAAFOSyU == true){NrZAAFOSyU = false;}
      if(UyTbrfGlaJ == true){UyTbrfGlaJ = false;}
      if(rckqUzYanm == true){rckqUzYanm = false;}
      if(aLKXudkuwp == true){aLKXudkuwp = false;}
      if(YMppGlkBSE == true){YMppGlkBSE = false;}
      if(NoPXFkGifA == true){NoPXFkGifA = false;}
      if(fneKsImwfN == true){fneKsImwfN = false;}
      if(tKpjkemukh == true){tKpjkemukh = false;}
      if(OWIiZkwmRK == true){OWIiZkwmRK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRRAHTMTEN
{ 
  void eNpoTkWGRs()
  { 
      bool xzQaggMZZV = false;
      bool WlBRQPMWtJ = false;
      bool efOgeBwZWy = false;
      bool TiwXzBZoBN = false;
      bool ddpPeMLZSB = false;
      bool xHeHuRkjue = false;
      bool jlCbBnpcSO = false;
      bool oWUfeAozBS = false;
      bool pVHVALDnbg = false;
      bool QptWcrbONq = false;
      bool WhHELZlycu = false;
      bool bkhcoOdfao = false;
      bool jBAkxzcyDl = false;
      bool XakKuHODKa = false;
      bool YFLgFfHQhO = false;
      bool NumYGVgVGL = false;
      bool xnupWBAXhg = false;
      bool AZVAQepTfR = false;
      bool qLQnYcmMDZ = false;
      bool ZrwydkJUKD = false;
      string sPYeWdNgRW;
      string HwyPwcepRI;
      string HBpLdRlDAh;
      string oFFmAOTUmP;
      string bNJMEsoTnd;
      string KCllHrYNBE;
      string rKgihCqKOg;
      string IKDBgtqcHj;
      string bROVXlTTfI;
      string pGShWQgZdC;
      string CdFGUzyjEN;
      string AuFRbawKLw;
      string hWeGqCrVeP;
      string MRzFhyLHBX;
      string mjORItABFw;
      string UVNhTezzPS;
      string GcFoAhwAjd;
      string OnJnIyINxx;
      string BqQhtqDQkC;
      string yMriQKeZQZ;
      if(sPYeWdNgRW == CdFGUzyjEN){xzQaggMZZV = true;}
      else if(CdFGUzyjEN == sPYeWdNgRW){WhHELZlycu = true;}
      if(HwyPwcepRI == AuFRbawKLw){WlBRQPMWtJ = true;}
      else if(AuFRbawKLw == HwyPwcepRI){bkhcoOdfao = true;}
      if(HBpLdRlDAh == hWeGqCrVeP){efOgeBwZWy = true;}
      else if(hWeGqCrVeP == HBpLdRlDAh){jBAkxzcyDl = true;}
      if(oFFmAOTUmP == MRzFhyLHBX){TiwXzBZoBN = true;}
      else if(MRzFhyLHBX == oFFmAOTUmP){XakKuHODKa = true;}
      if(bNJMEsoTnd == mjORItABFw){ddpPeMLZSB = true;}
      else if(mjORItABFw == bNJMEsoTnd){YFLgFfHQhO = true;}
      if(KCllHrYNBE == UVNhTezzPS){xHeHuRkjue = true;}
      else if(UVNhTezzPS == KCllHrYNBE){NumYGVgVGL = true;}
      if(rKgihCqKOg == GcFoAhwAjd){jlCbBnpcSO = true;}
      else if(GcFoAhwAjd == rKgihCqKOg){xnupWBAXhg = true;}
      if(IKDBgtqcHj == OnJnIyINxx){oWUfeAozBS = true;}
      if(bROVXlTTfI == BqQhtqDQkC){pVHVALDnbg = true;}
      if(pGShWQgZdC == yMriQKeZQZ){QptWcrbONq = true;}
      while(OnJnIyINxx == IKDBgtqcHj){AZVAQepTfR = true;}
      while(BqQhtqDQkC == BqQhtqDQkC){qLQnYcmMDZ = true;}
      while(yMriQKeZQZ == yMriQKeZQZ){ZrwydkJUKD = true;}
      if(xzQaggMZZV == true){xzQaggMZZV = false;}
      if(WlBRQPMWtJ == true){WlBRQPMWtJ = false;}
      if(efOgeBwZWy == true){efOgeBwZWy = false;}
      if(TiwXzBZoBN == true){TiwXzBZoBN = false;}
      if(ddpPeMLZSB == true){ddpPeMLZSB = false;}
      if(xHeHuRkjue == true){xHeHuRkjue = false;}
      if(jlCbBnpcSO == true){jlCbBnpcSO = false;}
      if(oWUfeAozBS == true){oWUfeAozBS = false;}
      if(pVHVALDnbg == true){pVHVALDnbg = false;}
      if(QptWcrbONq == true){QptWcrbONq = false;}
      if(WhHELZlycu == true){WhHELZlycu = false;}
      if(bkhcoOdfao == true){bkhcoOdfao = false;}
      if(jBAkxzcyDl == true){jBAkxzcyDl = false;}
      if(XakKuHODKa == true){XakKuHODKa = false;}
      if(YFLgFfHQhO == true){YFLgFfHQhO = false;}
      if(NumYGVgVGL == true){NumYGVgVGL = false;}
      if(xnupWBAXhg == true){xnupWBAXhg = false;}
      if(AZVAQepTfR == true){AZVAQepTfR = false;}
      if(qLQnYcmMDZ == true){qLQnYcmMDZ = false;}
      if(ZrwydkJUKD == true){ZrwydkJUKD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDPEFTEQXI
{ 
  void eHzDmbllwA()
  { 
      bool SahDJVJLFF = false;
      bool SGWBVzzTta = false;
      bool algqOLqCNA = false;
      bool JPJohdCPrJ = false;
      bool csQUMbANFH = false;
      bool AYEhzfspoy = false;
      bool dGxEuDwgTq = false;
      bool xibkxgUMdm = false;
      bool KcxGzkLapB = false;
      bool jLaseWuLZJ = false;
      bool eTtNKRwTjS = false;
      bool LgMBnBJqFJ = false;
      bool rUqSGkHhFa = false;
      bool kImUIqiiwg = false;
      bool nqpXoDzZFd = false;
      bool MEGPRJbbGY = false;
      bool KONJgCsqsx = false;
      bool SauYUAdTcD = false;
      bool lhbaNgCWCy = false;
      bool OGbWWZdgpm = false;
      string HjfOUdfkCw;
      string etuRjdkMbf;
      string MHziwpTLnW;
      string VeztXwTGkw;
      string VRZyZORBQX;
      string EOyrizkxRd;
      string KTxeZztBtm;
      string JeafJugAIh;
      string YRuQRGgHKX;
      string LWoGkBUuYa;
      string UPHcNZmRhn;
      string RjojFrYgNS;
      string SmpVbmoUuI;
      string ZlbhMIJRCr;
      string SPYWFahEAr;
      string cngFHgZlBa;
      string jSWZNfIGWx;
      string iHdVACOSPA;
      string EjTCelFWZf;
      string hXPbHAsyJZ;
      if(HjfOUdfkCw == UPHcNZmRhn){SahDJVJLFF = true;}
      else if(UPHcNZmRhn == HjfOUdfkCw){eTtNKRwTjS = true;}
      if(etuRjdkMbf == RjojFrYgNS){SGWBVzzTta = true;}
      else if(RjojFrYgNS == etuRjdkMbf){LgMBnBJqFJ = true;}
      if(MHziwpTLnW == SmpVbmoUuI){algqOLqCNA = true;}
      else if(SmpVbmoUuI == MHziwpTLnW){rUqSGkHhFa = true;}
      if(VeztXwTGkw == ZlbhMIJRCr){JPJohdCPrJ = true;}
      else if(ZlbhMIJRCr == VeztXwTGkw){kImUIqiiwg = true;}
      if(VRZyZORBQX == SPYWFahEAr){csQUMbANFH = true;}
      else if(SPYWFahEAr == VRZyZORBQX){nqpXoDzZFd = true;}
      if(EOyrizkxRd == cngFHgZlBa){AYEhzfspoy = true;}
      else if(cngFHgZlBa == EOyrizkxRd){MEGPRJbbGY = true;}
      if(KTxeZztBtm == jSWZNfIGWx){dGxEuDwgTq = true;}
      else if(jSWZNfIGWx == KTxeZztBtm){KONJgCsqsx = true;}
      if(JeafJugAIh == iHdVACOSPA){xibkxgUMdm = true;}
      if(YRuQRGgHKX == EjTCelFWZf){KcxGzkLapB = true;}
      if(LWoGkBUuYa == hXPbHAsyJZ){jLaseWuLZJ = true;}
      while(iHdVACOSPA == JeafJugAIh){SauYUAdTcD = true;}
      while(EjTCelFWZf == EjTCelFWZf){lhbaNgCWCy = true;}
      while(hXPbHAsyJZ == hXPbHAsyJZ){OGbWWZdgpm = true;}
      if(SahDJVJLFF == true){SahDJVJLFF = false;}
      if(SGWBVzzTta == true){SGWBVzzTta = false;}
      if(algqOLqCNA == true){algqOLqCNA = false;}
      if(JPJohdCPrJ == true){JPJohdCPrJ = false;}
      if(csQUMbANFH == true){csQUMbANFH = false;}
      if(AYEhzfspoy == true){AYEhzfspoy = false;}
      if(dGxEuDwgTq == true){dGxEuDwgTq = false;}
      if(xibkxgUMdm == true){xibkxgUMdm = false;}
      if(KcxGzkLapB == true){KcxGzkLapB = false;}
      if(jLaseWuLZJ == true){jLaseWuLZJ = false;}
      if(eTtNKRwTjS == true){eTtNKRwTjS = false;}
      if(LgMBnBJqFJ == true){LgMBnBJqFJ = false;}
      if(rUqSGkHhFa == true){rUqSGkHhFa = false;}
      if(kImUIqiiwg == true){kImUIqiiwg = false;}
      if(nqpXoDzZFd == true){nqpXoDzZFd = false;}
      if(MEGPRJbbGY == true){MEGPRJbbGY = false;}
      if(KONJgCsqsx == true){KONJgCsqsx = false;}
      if(SauYUAdTcD == true){SauYUAdTcD = false;}
      if(lhbaNgCWCy == true){lhbaNgCWCy = false;}
      if(OGbWWZdgpm == true){OGbWWZdgpm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTPIHNVSML
{ 
  void iWOgjOfDUw()
  { 
      bool mInWASZKoI = false;
      bool FELCLtloTz = false;
      bool nwonIehcSh = false;
      bool toszKlpjar = false;
      bool fjAXVMLcGG = false;
      bool YOmyOpTzOV = false;
      bool jwrGOPLMrZ = false;
      bool DBOaTEwRRw = false;
      bool SEWMJfCtjT = false;
      bool RpVEIiqsJG = false;
      bool AzkfCXzLeK = false;
      bool tBhSDfZfwh = false;
      bool MQbXHNfKSj = false;
      bool MCILuSSpKl = false;
      bool fqPZYPICAc = false;
      bool JLwasjXNYn = false;
      bool qosuxrsVXk = false;
      bool MiUKBVBBzq = false;
      bool EcJpZAFgRK = false;
      bool tFRVtpxUbg = false;
      string mqMoUxMcnm;
      string ZgVbrkjPrg;
      string kkgiicVUCR;
      string nmsnuqUDaU;
      string QRqdPWYhVx;
      string mlUlBBKdFq;
      string braVymnggB;
      string QfnXPTtCSM;
      string EmzFeBRGls;
      string fqyjrYqUec;
      string iqBTfGxwVh;
      string HILsmnrUqx;
      string UgumUZhEeq;
      string bYWocNleYX;
      string DVkDkXeExD;
      string fVdhIBwNzG;
      string XsQeFikVPZ;
      string CNwSszwqCx;
      string tdHbKGtogb;
      string QXfSAKEGyC;
      if(mqMoUxMcnm == iqBTfGxwVh){mInWASZKoI = true;}
      else if(iqBTfGxwVh == mqMoUxMcnm){AzkfCXzLeK = true;}
      if(ZgVbrkjPrg == HILsmnrUqx){FELCLtloTz = true;}
      else if(HILsmnrUqx == ZgVbrkjPrg){tBhSDfZfwh = true;}
      if(kkgiicVUCR == UgumUZhEeq){nwonIehcSh = true;}
      else if(UgumUZhEeq == kkgiicVUCR){MQbXHNfKSj = true;}
      if(nmsnuqUDaU == bYWocNleYX){toszKlpjar = true;}
      else if(bYWocNleYX == nmsnuqUDaU){MCILuSSpKl = true;}
      if(QRqdPWYhVx == DVkDkXeExD){fjAXVMLcGG = true;}
      else if(DVkDkXeExD == QRqdPWYhVx){fqPZYPICAc = true;}
      if(mlUlBBKdFq == fVdhIBwNzG){YOmyOpTzOV = true;}
      else if(fVdhIBwNzG == mlUlBBKdFq){JLwasjXNYn = true;}
      if(braVymnggB == XsQeFikVPZ){jwrGOPLMrZ = true;}
      else if(XsQeFikVPZ == braVymnggB){qosuxrsVXk = true;}
      if(QfnXPTtCSM == CNwSszwqCx){DBOaTEwRRw = true;}
      if(EmzFeBRGls == tdHbKGtogb){SEWMJfCtjT = true;}
      if(fqyjrYqUec == QXfSAKEGyC){RpVEIiqsJG = true;}
      while(CNwSszwqCx == QfnXPTtCSM){MiUKBVBBzq = true;}
      while(tdHbKGtogb == tdHbKGtogb){EcJpZAFgRK = true;}
      while(QXfSAKEGyC == QXfSAKEGyC){tFRVtpxUbg = true;}
      if(mInWASZKoI == true){mInWASZKoI = false;}
      if(FELCLtloTz == true){FELCLtloTz = false;}
      if(nwonIehcSh == true){nwonIehcSh = false;}
      if(toszKlpjar == true){toszKlpjar = false;}
      if(fjAXVMLcGG == true){fjAXVMLcGG = false;}
      if(YOmyOpTzOV == true){YOmyOpTzOV = false;}
      if(jwrGOPLMrZ == true){jwrGOPLMrZ = false;}
      if(DBOaTEwRRw == true){DBOaTEwRRw = false;}
      if(SEWMJfCtjT == true){SEWMJfCtjT = false;}
      if(RpVEIiqsJG == true){RpVEIiqsJG = false;}
      if(AzkfCXzLeK == true){AzkfCXzLeK = false;}
      if(tBhSDfZfwh == true){tBhSDfZfwh = false;}
      if(MQbXHNfKSj == true){MQbXHNfKSj = false;}
      if(MCILuSSpKl == true){MCILuSSpKl = false;}
      if(fqPZYPICAc == true){fqPZYPICAc = false;}
      if(JLwasjXNYn == true){JLwasjXNYn = false;}
      if(qosuxrsVXk == true){qosuxrsVXk = false;}
      if(MiUKBVBBzq == true){MiUKBVBBzq = false;}
      if(EcJpZAFgRK == true){EcJpZAFgRK = false;}
      if(tFRVtpxUbg == true){tFRVtpxUbg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPICQAHCEA
{ 
  void YjNuphFuVd()
  { 
      bool ESnEwDMQaw = false;
      bool aYKzcAoQQu = false;
      bool xMbZoNPgjT = false;
      bool YNnjrDTlDC = false;
      bool lbEPWUcOQb = false;
      bool XfjpYqqNPi = false;
      bool nffGWMkZGZ = false;
      bool fDMOIUIMDU = false;
      bool jAPIwsdxLB = false;
      bool LGWUNGwxrJ = false;
      bool jDHquTTUhD = false;
      bool ieKuymPXKd = false;
      bool imNFNZgrAB = false;
      bool YKTtjgsYNc = false;
      bool YIPIRgubVa = false;
      bool qXmNawoBcU = false;
      bool maUfdYKQKR = false;
      bool tpKgEZXEng = false;
      bool eFVYKAWGSn = false;
      bool qquroxnidr = false;
      string CuNnrUWryt;
      string SZJiQipmEc;
      string sonINTXbCj;
      string OAFqnneypB;
      string RypPXxWgWg;
      string UITVcMGEaY;
      string xtpNfRUSuc;
      string DqwDLuzYkP;
      string wpFVPFfiNa;
      string gaWQEWIbiF;
      string bDksccLQKh;
      string NhTLbGoTya;
      string llFTwcTfzn;
      string mWoemrELsl;
      string sOXfMyGLny;
      string hndIToyRxz;
      string JfRWtqsnXj;
      string BdaMgWOYGx;
      string VIqAGzsfLx;
      string tmOscMxAkV;
      if(CuNnrUWryt == bDksccLQKh){ESnEwDMQaw = true;}
      else if(bDksccLQKh == CuNnrUWryt){jDHquTTUhD = true;}
      if(SZJiQipmEc == NhTLbGoTya){aYKzcAoQQu = true;}
      else if(NhTLbGoTya == SZJiQipmEc){ieKuymPXKd = true;}
      if(sonINTXbCj == llFTwcTfzn){xMbZoNPgjT = true;}
      else if(llFTwcTfzn == sonINTXbCj){imNFNZgrAB = true;}
      if(OAFqnneypB == mWoemrELsl){YNnjrDTlDC = true;}
      else if(mWoemrELsl == OAFqnneypB){YKTtjgsYNc = true;}
      if(RypPXxWgWg == sOXfMyGLny){lbEPWUcOQb = true;}
      else if(sOXfMyGLny == RypPXxWgWg){YIPIRgubVa = true;}
      if(UITVcMGEaY == hndIToyRxz){XfjpYqqNPi = true;}
      else if(hndIToyRxz == UITVcMGEaY){qXmNawoBcU = true;}
      if(xtpNfRUSuc == JfRWtqsnXj){nffGWMkZGZ = true;}
      else if(JfRWtqsnXj == xtpNfRUSuc){maUfdYKQKR = true;}
      if(DqwDLuzYkP == BdaMgWOYGx){fDMOIUIMDU = true;}
      if(wpFVPFfiNa == VIqAGzsfLx){jAPIwsdxLB = true;}
      if(gaWQEWIbiF == tmOscMxAkV){LGWUNGwxrJ = true;}
      while(BdaMgWOYGx == DqwDLuzYkP){tpKgEZXEng = true;}
      while(VIqAGzsfLx == VIqAGzsfLx){eFVYKAWGSn = true;}
      while(tmOscMxAkV == tmOscMxAkV){qquroxnidr = true;}
      if(ESnEwDMQaw == true){ESnEwDMQaw = false;}
      if(aYKzcAoQQu == true){aYKzcAoQQu = false;}
      if(xMbZoNPgjT == true){xMbZoNPgjT = false;}
      if(YNnjrDTlDC == true){YNnjrDTlDC = false;}
      if(lbEPWUcOQb == true){lbEPWUcOQb = false;}
      if(XfjpYqqNPi == true){XfjpYqqNPi = false;}
      if(nffGWMkZGZ == true){nffGWMkZGZ = false;}
      if(fDMOIUIMDU == true){fDMOIUIMDU = false;}
      if(jAPIwsdxLB == true){jAPIwsdxLB = false;}
      if(LGWUNGwxrJ == true){LGWUNGwxrJ = false;}
      if(jDHquTTUhD == true){jDHquTTUhD = false;}
      if(ieKuymPXKd == true){ieKuymPXKd = false;}
      if(imNFNZgrAB == true){imNFNZgrAB = false;}
      if(YKTtjgsYNc == true){YKTtjgsYNc = false;}
      if(YIPIRgubVa == true){YIPIRgubVa = false;}
      if(qXmNawoBcU == true){qXmNawoBcU = false;}
      if(maUfdYKQKR == true){maUfdYKQKR = false;}
      if(tpKgEZXEng == true){tpKgEZXEng = false;}
      if(eFVYKAWGSn == true){eFVYKAWGSn = false;}
      if(qquroxnidr == true){qquroxnidr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYRRRVUVUZ
{ 
  void dGrKPVhMxN()
  { 
      bool IzuTySPiYP = false;
      bool ecsEUGdCeA = false;
      bool NhCVlwAqBM = false;
      bool hJpBWShjbr = false;
      bool OSRzylQKtQ = false;
      bool eJaOiaxYhC = false;
      bool RXgMhVlqgB = false;
      bool YsamltQDWz = false;
      bool eowkgXibSw = false;
      bool VICZaplFRc = false;
      bool AZcsqlimbn = false;
      bool KsCiXbbueJ = false;
      bool mKYkeQqBMw = false;
      bool ILksyFMDtu = false;
      bool ouzdkcFTBy = false;
      bool OpZIppArNZ = false;
      bool tgaffzIIjR = false;
      bool PXBiTrLtzC = false;
      bool KXzNhSkcDI = false;
      bool ETpTBHTSyl = false;
      string KKxpjdTpJD;
      string cEcQyMTyZK;
      string NiIoizMDzO;
      string uxKyPsRbFf;
      string QaiPXBPEDU;
      string AzBdUaCIGj;
      string QQptIeseAE;
      string trsstmzrRh;
      string jHzdOwwgcn;
      string qJUUOAjnHr;
      string HkEyZHFHjh;
      string aJqYAJQMfM;
      string iMBLNkXXes;
      string CKkYZyDAEG;
      string pnwuMgRuUE;
      string iXIuJuirkn;
      string jgcpePXRzB;
      string GQHYVtPGyf;
      string ScDZKdCpPd;
      string PKPPWILGPw;
      if(KKxpjdTpJD == HkEyZHFHjh){IzuTySPiYP = true;}
      else if(HkEyZHFHjh == KKxpjdTpJD){AZcsqlimbn = true;}
      if(cEcQyMTyZK == aJqYAJQMfM){ecsEUGdCeA = true;}
      else if(aJqYAJQMfM == cEcQyMTyZK){KsCiXbbueJ = true;}
      if(NiIoizMDzO == iMBLNkXXes){NhCVlwAqBM = true;}
      else if(iMBLNkXXes == NiIoizMDzO){mKYkeQqBMw = true;}
      if(uxKyPsRbFf == CKkYZyDAEG){hJpBWShjbr = true;}
      else if(CKkYZyDAEG == uxKyPsRbFf){ILksyFMDtu = true;}
      if(QaiPXBPEDU == pnwuMgRuUE){OSRzylQKtQ = true;}
      else if(pnwuMgRuUE == QaiPXBPEDU){ouzdkcFTBy = true;}
      if(AzBdUaCIGj == iXIuJuirkn){eJaOiaxYhC = true;}
      else if(iXIuJuirkn == AzBdUaCIGj){OpZIppArNZ = true;}
      if(QQptIeseAE == jgcpePXRzB){RXgMhVlqgB = true;}
      else if(jgcpePXRzB == QQptIeseAE){tgaffzIIjR = true;}
      if(trsstmzrRh == GQHYVtPGyf){YsamltQDWz = true;}
      if(jHzdOwwgcn == ScDZKdCpPd){eowkgXibSw = true;}
      if(qJUUOAjnHr == PKPPWILGPw){VICZaplFRc = true;}
      while(GQHYVtPGyf == trsstmzrRh){PXBiTrLtzC = true;}
      while(ScDZKdCpPd == ScDZKdCpPd){KXzNhSkcDI = true;}
      while(PKPPWILGPw == PKPPWILGPw){ETpTBHTSyl = true;}
      if(IzuTySPiYP == true){IzuTySPiYP = false;}
      if(ecsEUGdCeA == true){ecsEUGdCeA = false;}
      if(NhCVlwAqBM == true){NhCVlwAqBM = false;}
      if(hJpBWShjbr == true){hJpBWShjbr = false;}
      if(OSRzylQKtQ == true){OSRzylQKtQ = false;}
      if(eJaOiaxYhC == true){eJaOiaxYhC = false;}
      if(RXgMhVlqgB == true){RXgMhVlqgB = false;}
      if(YsamltQDWz == true){YsamltQDWz = false;}
      if(eowkgXibSw == true){eowkgXibSw = false;}
      if(VICZaplFRc == true){VICZaplFRc = false;}
      if(AZcsqlimbn == true){AZcsqlimbn = false;}
      if(KsCiXbbueJ == true){KsCiXbbueJ = false;}
      if(mKYkeQqBMw == true){mKYkeQqBMw = false;}
      if(ILksyFMDtu == true){ILksyFMDtu = false;}
      if(ouzdkcFTBy == true){ouzdkcFTBy = false;}
      if(OpZIppArNZ == true){OpZIppArNZ = false;}
      if(tgaffzIIjR == true){tgaffzIIjR = false;}
      if(PXBiTrLtzC == true){PXBiTrLtzC = false;}
      if(KXzNhSkcDI == true){KXzNhSkcDI = false;}
      if(ETpTBHTSyl == true){ETpTBHTSyl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZDCBJMSSD
{ 
  void eLtGbpNcKY()
  { 
      bool RjGMmLzmuT = false;
      bool JHOriSMCed = false;
      bool KaaWValqXF = false;
      bool rCdPnHTctp = false;
      bool PWCxwXigTe = false;
      bool YEQPnpIjpL = false;
      bool ZHPoaHdzEb = false;
      bool yjHnOmXdZy = false;
      bool rEXrfnlOax = false;
      bool yjmhQHHMVo = false;
      bool ticrfoxcBA = false;
      bool SeKrTUjWJm = false;
      bool VOYGcOwYXG = false;
      bool fLIjDJbfLp = false;
      bool pINZeTZuOu = false;
      bool WjDhTeKVPR = false;
      bool rXFtUHWZnJ = false;
      bool sEKSwMAybI = false;
      bool oBJbiuHZPX = false;
      bool zFQtySDSFX = false;
      string USnrSdRgIL;
      string UhSlQxNcJo;
      string ijCRyzpOmt;
      string iHVQtRaXwB;
      string JKnxWxtDuQ;
      string umllakPWtS;
      string nCtOcMLBqz;
      string WogHeYuFtA;
      string EmTWyuVjoJ;
      string BDdcNGPZTK;
      string krLusFGdGC;
      string oKbsOAiWPg;
      string qbLhxSLDtY;
      string IUkjPMbXcs;
      string oqcmTqbjOM;
      string WsKmTIfcya;
      string tCjgsUYrdB;
      string YLsWrzyXOG;
      string qaohCOKyQG;
      string fyYCylGwty;
      if(USnrSdRgIL == krLusFGdGC){RjGMmLzmuT = true;}
      else if(krLusFGdGC == USnrSdRgIL){ticrfoxcBA = true;}
      if(UhSlQxNcJo == oKbsOAiWPg){JHOriSMCed = true;}
      else if(oKbsOAiWPg == UhSlQxNcJo){SeKrTUjWJm = true;}
      if(ijCRyzpOmt == qbLhxSLDtY){KaaWValqXF = true;}
      else if(qbLhxSLDtY == ijCRyzpOmt){VOYGcOwYXG = true;}
      if(iHVQtRaXwB == IUkjPMbXcs){rCdPnHTctp = true;}
      else if(IUkjPMbXcs == iHVQtRaXwB){fLIjDJbfLp = true;}
      if(JKnxWxtDuQ == oqcmTqbjOM){PWCxwXigTe = true;}
      else if(oqcmTqbjOM == JKnxWxtDuQ){pINZeTZuOu = true;}
      if(umllakPWtS == WsKmTIfcya){YEQPnpIjpL = true;}
      else if(WsKmTIfcya == umllakPWtS){WjDhTeKVPR = true;}
      if(nCtOcMLBqz == tCjgsUYrdB){ZHPoaHdzEb = true;}
      else if(tCjgsUYrdB == nCtOcMLBqz){rXFtUHWZnJ = true;}
      if(WogHeYuFtA == YLsWrzyXOG){yjHnOmXdZy = true;}
      if(EmTWyuVjoJ == qaohCOKyQG){rEXrfnlOax = true;}
      if(BDdcNGPZTK == fyYCylGwty){yjmhQHHMVo = true;}
      while(YLsWrzyXOG == WogHeYuFtA){sEKSwMAybI = true;}
      while(qaohCOKyQG == qaohCOKyQG){oBJbiuHZPX = true;}
      while(fyYCylGwty == fyYCylGwty){zFQtySDSFX = true;}
      if(RjGMmLzmuT == true){RjGMmLzmuT = false;}
      if(JHOriSMCed == true){JHOriSMCed = false;}
      if(KaaWValqXF == true){KaaWValqXF = false;}
      if(rCdPnHTctp == true){rCdPnHTctp = false;}
      if(PWCxwXigTe == true){PWCxwXigTe = false;}
      if(YEQPnpIjpL == true){YEQPnpIjpL = false;}
      if(ZHPoaHdzEb == true){ZHPoaHdzEb = false;}
      if(yjHnOmXdZy == true){yjHnOmXdZy = false;}
      if(rEXrfnlOax == true){rEXrfnlOax = false;}
      if(yjmhQHHMVo == true){yjmhQHHMVo = false;}
      if(ticrfoxcBA == true){ticrfoxcBA = false;}
      if(SeKrTUjWJm == true){SeKrTUjWJm = false;}
      if(VOYGcOwYXG == true){VOYGcOwYXG = false;}
      if(fLIjDJbfLp == true){fLIjDJbfLp = false;}
      if(pINZeTZuOu == true){pINZeTZuOu = false;}
      if(WjDhTeKVPR == true){WjDhTeKVPR = false;}
      if(rXFtUHWZnJ == true){rXFtUHWZnJ = false;}
      if(sEKSwMAybI == true){sEKSwMAybI = false;}
      if(oBJbiuHZPX == true){oBJbiuHZPX = false;}
      if(zFQtySDSFX == true){zFQtySDSFX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYZBPADLMY
{ 
  void CtCVrFEehM()
  { 
      bool DFlBOfcecE = false;
      bool VYysnCOyuu = false;
      bool joPzmoaZcQ = false;
      bool bHuObmjZpz = false;
      bool RJoFWUqYIM = false;
      bool eJmMCNpmNZ = false;
      bool FCCMcNcjRA = false;
      bool SnIudazKcS = false;
      bool xBRQkRTiLO = false;
      bool xxMQtOHccI = false;
      bool qHHItpAqib = false;
      bool NeJubDkkaK = false;
      bool ttXCCUbrBO = false;
      bool SWhTbpsIVt = false;
      bool RbAiARmRnp = false;
      bool cVCROwiEGY = false;
      bool OIpTJqxpSk = false;
      bool KcPfsRtoCj = false;
      bool gJDLlwTPFe = false;
      bool HnCweIlfZI = false;
      string OIoaTImLzL;
      string zaGKypFjOX;
      string qMEgQQerWG;
      string fmlUzfMhou;
      string GrwOxAPZjj;
      string tuWwkBEIKD;
      string cunrfLokLS;
      string dWuSQzQojP;
      string AFIlLjPojx;
      string aEXkSLDDik;
      string LdOQGXADfl;
      string kOYuDWlCfu;
      string wzBNqYzJAF;
      string uMGyDVqren;
      string jLJyLLfchu;
      string ZAXmoLcAYh;
      string YpDapYIZqg;
      string fsXrKjpDBf;
      string sVbEetoSJr;
      string spSxPtIiHm;
      if(OIoaTImLzL == LdOQGXADfl){DFlBOfcecE = true;}
      else if(LdOQGXADfl == OIoaTImLzL){qHHItpAqib = true;}
      if(zaGKypFjOX == kOYuDWlCfu){VYysnCOyuu = true;}
      else if(kOYuDWlCfu == zaGKypFjOX){NeJubDkkaK = true;}
      if(qMEgQQerWG == wzBNqYzJAF){joPzmoaZcQ = true;}
      else if(wzBNqYzJAF == qMEgQQerWG){ttXCCUbrBO = true;}
      if(fmlUzfMhou == uMGyDVqren){bHuObmjZpz = true;}
      else if(uMGyDVqren == fmlUzfMhou){SWhTbpsIVt = true;}
      if(GrwOxAPZjj == jLJyLLfchu){RJoFWUqYIM = true;}
      else if(jLJyLLfchu == GrwOxAPZjj){RbAiARmRnp = true;}
      if(tuWwkBEIKD == ZAXmoLcAYh){eJmMCNpmNZ = true;}
      else if(ZAXmoLcAYh == tuWwkBEIKD){cVCROwiEGY = true;}
      if(cunrfLokLS == YpDapYIZqg){FCCMcNcjRA = true;}
      else if(YpDapYIZqg == cunrfLokLS){OIpTJqxpSk = true;}
      if(dWuSQzQojP == fsXrKjpDBf){SnIudazKcS = true;}
      if(AFIlLjPojx == sVbEetoSJr){xBRQkRTiLO = true;}
      if(aEXkSLDDik == spSxPtIiHm){xxMQtOHccI = true;}
      while(fsXrKjpDBf == dWuSQzQojP){KcPfsRtoCj = true;}
      while(sVbEetoSJr == sVbEetoSJr){gJDLlwTPFe = true;}
      while(spSxPtIiHm == spSxPtIiHm){HnCweIlfZI = true;}
      if(DFlBOfcecE == true){DFlBOfcecE = false;}
      if(VYysnCOyuu == true){VYysnCOyuu = false;}
      if(joPzmoaZcQ == true){joPzmoaZcQ = false;}
      if(bHuObmjZpz == true){bHuObmjZpz = false;}
      if(RJoFWUqYIM == true){RJoFWUqYIM = false;}
      if(eJmMCNpmNZ == true){eJmMCNpmNZ = false;}
      if(FCCMcNcjRA == true){FCCMcNcjRA = false;}
      if(SnIudazKcS == true){SnIudazKcS = false;}
      if(xBRQkRTiLO == true){xBRQkRTiLO = false;}
      if(xxMQtOHccI == true){xxMQtOHccI = false;}
      if(qHHItpAqib == true){qHHItpAqib = false;}
      if(NeJubDkkaK == true){NeJubDkkaK = false;}
      if(ttXCCUbrBO == true){ttXCCUbrBO = false;}
      if(SWhTbpsIVt == true){SWhTbpsIVt = false;}
      if(RbAiARmRnp == true){RbAiARmRnp = false;}
      if(cVCROwiEGY == true){cVCROwiEGY = false;}
      if(OIpTJqxpSk == true){OIpTJqxpSk = false;}
      if(KcPfsRtoCj == true){KcPfsRtoCj = false;}
      if(gJDLlwTPFe == true){gJDLlwTPFe = false;}
      if(HnCweIlfZI == true){HnCweIlfZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SWDEKWCYRE
{ 
  void BHJTNYbxdA()
  { 
      bool EmaSwFzQlA = false;
      bool NaHkoGnZfI = false;
      bool VuggUfRbBt = false;
      bool cXqFmJElWs = false;
      bool NwmgEtpODB = false;
      bool lrhprIFsyP = false;
      bool nXOrWpiBxf = false;
      bool BBDmuZIAcZ = false;
      bool pDXAHkoBNd = false;
      bool EKnGEpgtKN = false;
      bool LnRXzjotuS = false;
      bool AEQXZkzOkk = false;
      bool AhnSbpNxhE = false;
      bool rNoOOCkAAW = false;
      bool wuFudztPgT = false;
      bool qSJYNcAywJ = false;
      bool WrLqZlOBJW = false;
      bool zyNNoFbrnb = false;
      bool wyPOMZEQBk = false;
      bool CmEqADiOUr = false;
      string OZVGcDkzPC;
      string SFKdGPzfSY;
      string YfstuhlRoa;
      string jLhYyKWCfu;
      string kbQOLAPVrc;
      string oHLnAigaLt;
      string RTKnRHXkfw;
      string sxAXmxOdht;
      string RPYMlbzsYP;
      string cuqlcRQbxE;
      string cepwirHnAC;
      string TCsQcCtxCo;
      string HdMPSyFNtV;
      string flgdQmYccs;
      string ULrVwZBZIa;
      string WSZHwzRack;
      string lsseVhVOzp;
      string dRTJUwkqTr;
      string wfFTyMMZhR;
      string UxzrHaSNzN;
      if(OZVGcDkzPC == cepwirHnAC){EmaSwFzQlA = true;}
      else if(cepwirHnAC == OZVGcDkzPC){LnRXzjotuS = true;}
      if(SFKdGPzfSY == TCsQcCtxCo){NaHkoGnZfI = true;}
      else if(TCsQcCtxCo == SFKdGPzfSY){AEQXZkzOkk = true;}
      if(YfstuhlRoa == HdMPSyFNtV){VuggUfRbBt = true;}
      else if(HdMPSyFNtV == YfstuhlRoa){AhnSbpNxhE = true;}
      if(jLhYyKWCfu == flgdQmYccs){cXqFmJElWs = true;}
      else if(flgdQmYccs == jLhYyKWCfu){rNoOOCkAAW = true;}
      if(kbQOLAPVrc == ULrVwZBZIa){NwmgEtpODB = true;}
      else if(ULrVwZBZIa == kbQOLAPVrc){wuFudztPgT = true;}
      if(oHLnAigaLt == WSZHwzRack){lrhprIFsyP = true;}
      else if(WSZHwzRack == oHLnAigaLt){qSJYNcAywJ = true;}
      if(RTKnRHXkfw == lsseVhVOzp){nXOrWpiBxf = true;}
      else if(lsseVhVOzp == RTKnRHXkfw){WrLqZlOBJW = true;}
      if(sxAXmxOdht == dRTJUwkqTr){BBDmuZIAcZ = true;}
      if(RPYMlbzsYP == wfFTyMMZhR){pDXAHkoBNd = true;}
      if(cuqlcRQbxE == UxzrHaSNzN){EKnGEpgtKN = true;}
      while(dRTJUwkqTr == sxAXmxOdht){zyNNoFbrnb = true;}
      while(wfFTyMMZhR == wfFTyMMZhR){wyPOMZEQBk = true;}
      while(UxzrHaSNzN == UxzrHaSNzN){CmEqADiOUr = true;}
      if(EmaSwFzQlA == true){EmaSwFzQlA = false;}
      if(NaHkoGnZfI == true){NaHkoGnZfI = false;}
      if(VuggUfRbBt == true){VuggUfRbBt = false;}
      if(cXqFmJElWs == true){cXqFmJElWs = false;}
      if(NwmgEtpODB == true){NwmgEtpODB = false;}
      if(lrhprIFsyP == true){lrhprIFsyP = false;}
      if(nXOrWpiBxf == true){nXOrWpiBxf = false;}
      if(BBDmuZIAcZ == true){BBDmuZIAcZ = false;}
      if(pDXAHkoBNd == true){pDXAHkoBNd = false;}
      if(EKnGEpgtKN == true){EKnGEpgtKN = false;}
      if(LnRXzjotuS == true){LnRXzjotuS = false;}
      if(AEQXZkzOkk == true){AEQXZkzOkk = false;}
      if(AhnSbpNxhE == true){AhnSbpNxhE = false;}
      if(rNoOOCkAAW == true){rNoOOCkAAW = false;}
      if(wuFudztPgT == true){wuFudztPgT = false;}
      if(qSJYNcAywJ == true){qSJYNcAywJ = false;}
      if(WrLqZlOBJW == true){WrLqZlOBJW = false;}
      if(zyNNoFbrnb == true){zyNNoFbrnb = false;}
      if(wyPOMZEQBk == true){wyPOMZEQBk = false;}
      if(CmEqADiOUr == true){CmEqADiOUr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUMUJAQZEE
{ 
  void AkOgreMDDu()
  { 
      bool kCBobmHnTk = false;
      bool sMTXSwBglo = false;
      bool CHFzVIJSCn = false;
      bool xjYTQbMmaE = false;
      bool XmUssOOIzK = false;
      bool beyWZcxCTS = false;
      bool cokemJmzGp = false;
      bool jNFgQOmLGG = false;
      bool sASrLSkCsn = false;
      bool eKSIaiBoFi = false;
      bool aOCJaOYQFL = false;
      bool okwNYcVsTU = false;
      bool XkGSKYtxGh = false;
      bool MyGWedyJRx = false;
      bool sUwhytOFiy = false;
      bool NIVjLpIiyB = false;
      bool TbKXyqeZht = false;
      bool eMaWbDoXUQ = false;
      bool JnOHTDcVKo = false;
      bool UOKPcRJXiG = false;
      string sbMmTSehfy;
      string xOYftqoEJo;
      string imVeADEOFW;
      string WqNfQIdMca;
      string qUklFAKixb;
      string pUoxGGFhmQ;
      string NPcJaGBrOl;
      string MbaixOBjYA;
      string rURdfBBPYK;
      string CwZLMbqbKz;
      string zRUKONsFAr;
      string EUJmYryzcZ;
      string EkSDjQCPWV;
      string WZYYAaAHOS;
      string HuPgGglmmT;
      string dqyktOyQZx;
      string LdieUdwjlx;
      string rpjJRJUlwC;
      string eOcCrebnel;
      string bigRHdLkMc;
      if(sbMmTSehfy == zRUKONsFAr){kCBobmHnTk = true;}
      else if(zRUKONsFAr == sbMmTSehfy){aOCJaOYQFL = true;}
      if(xOYftqoEJo == EUJmYryzcZ){sMTXSwBglo = true;}
      else if(EUJmYryzcZ == xOYftqoEJo){okwNYcVsTU = true;}
      if(imVeADEOFW == EkSDjQCPWV){CHFzVIJSCn = true;}
      else if(EkSDjQCPWV == imVeADEOFW){XkGSKYtxGh = true;}
      if(WqNfQIdMca == WZYYAaAHOS){xjYTQbMmaE = true;}
      else if(WZYYAaAHOS == WqNfQIdMca){MyGWedyJRx = true;}
      if(qUklFAKixb == HuPgGglmmT){XmUssOOIzK = true;}
      else if(HuPgGglmmT == qUklFAKixb){sUwhytOFiy = true;}
      if(pUoxGGFhmQ == dqyktOyQZx){beyWZcxCTS = true;}
      else if(dqyktOyQZx == pUoxGGFhmQ){NIVjLpIiyB = true;}
      if(NPcJaGBrOl == LdieUdwjlx){cokemJmzGp = true;}
      else if(LdieUdwjlx == NPcJaGBrOl){TbKXyqeZht = true;}
      if(MbaixOBjYA == rpjJRJUlwC){jNFgQOmLGG = true;}
      if(rURdfBBPYK == eOcCrebnel){sASrLSkCsn = true;}
      if(CwZLMbqbKz == bigRHdLkMc){eKSIaiBoFi = true;}
      while(rpjJRJUlwC == MbaixOBjYA){eMaWbDoXUQ = true;}
      while(eOcCrebnel == eOcCrebnel){JnOHTDcVKo = true;}
      while(bigRHdLkMc == bigRHdLkMc){UOKPcRJXiG = true;}
      if(kCBobmHnTk == true){kCBobmHnTk = false;}
      if(sMTXSwBglo == true){sMTXSwBglo = false;}
      if(CHFzVIJSCn == true){CHFzVIJSCn = false;}
      if(xjYTQbMmaE == true){xjYTQbMmaE = false;}
      if(XmUssOOIzK == true){XmUssOOIzK = false;}
      if(beyWZcxCTS == true){beyWZcxCTS = false;}
      if(cokemJmzGp == true){cokemJmzGp = false;}
      if(jNFgQOmLGG == true){jNFgQOmLGG = false;}
      if(sASrLSkCsn == true){sASrLSkCsn = false;}
      if(eKSIaiBoFi == true){eKSIaiBoFi = false;}
      if(aOCJaOYQFL == true){aOCJaOYQFL = false;}
      if(okwNYcVsTU == true){okwNYcVsTU = false;}
      if(XkGSKYtxGh == true){XkGSKYtxGh = false;}
      if(MyGWedyJRx == true){MyGWedyJRx = false;}
      if(sUwhytOFiy == true){sUwhytOFiy = false;}
      if(NIVjLpIiyB == true){NIVjLpIiyB = false;}
      if(TbKXyqeZht == true){TbKXyqeZht = false;}
      if(eMaWbDoXUQ == true){eMaWbDoXUQ = false;}
      if(JnOHTDcVKo == true){JnOHTDcVKo = false;}
      if(UOKPcRJXiG == true){UOKPcRJXiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKVISHYGHZ
{ 
  void BRNzcFebfn()
  { 
      bool GlAgpoqYWg = false;
      bool YUcsAtTNxi = false;
      bool BuBHQOBkyB = false;
      bool oWtlxGhTdG = false;
      bool KyKHaadOHI = false;
      bool WRtONLjsQb = false;
      bool mFZVqBZqut = false;
      bool MAipXDjtfp = false;
      bool jmcodWbfYl = false;
      bool WoDCSEYoPY = false;
      bool AmTNwWiEpJ = false;
      bool aoNaqAckqU = false;
      bool YtRIXXxgWS = false;
      bool eueGoxTPsG = false;
      bool nXoOLgbbKR = false;
      bool bnxuAGUKpY = false;
      bool ZBgWeeKGks = false;
      bool gMqkfBEDwp = false;
      bool wUVEqqxjGi = false;
      bool cIZUgmqRif = false;
      string iNbtYsiRug;
      string rlauDtIgfZ;
      string NCUTcLecGK;
      string zkQwrDQRZh;
      string SstCrGQXlp;
      string JWKsqfsIQN;
      string OFLjhHUeCz;
      string cpGyGTIRaW;
      string tGqPAcZWEM;
      string KIAMSMgKUj;
      string klUlNTPMmW;
      string XagsTHOwiF;
      string hyZpnTptet;
      string lyxplHlFCg;
      string MMjhnjbHsL;
      string ykaPClMexs;
      string cVgrjYcpGL;
      string VJtCrUNrBE;
      string rhBTuBWhnz;
      string uHHIDqfqxO;
      if(iNbtYsiRug == klUlNTPMmW){GlAgpoqYWg = true;}
      else if(klUlNTPMmW == iNbtYsiRug){AmTNwWiEpJ = true;}
      if(rlauDtIgfZ == XagsTHOwiF){YUcsAtTNxi = true;}
      else if(XagsTHOwiF == rlauDtIgfZ){aoNaqAckqU = true;}
      if(NCUTcLecGK == hyZpnTptet){BuBHQOBkyB = true;}
      else if(hyZpnTptet == NCUTcLecGK){YtRIXXxgWS = true;}
      if(zkQwrDQRZh == lyxplHlFCg){oWtlxGhTdG = true;}
      else if(lyxplHlFCg == zkQwrDQRZh){eueGoxTPsG = true;}
      if(SstCrGQXlp == MMjhnjbHsL){KyKHaadOHI = true;}
      else if(MMjhnjbHsL == SstCrGQXlp){nXoOLgbbKR = true;}
      if(JWKsqfsIQN == ykaPClMexs){WRtONLjsQb = true;}
      else if(ykaPClMexs == JWKsqfsIQN){bnxuAGUKpY = true;}
      if(OFLjhHUeCz == cVgrjYcpGL){mFZVqBZqut = true;}
      else if(cVgrjYcpGL == OFLjhHUeCz){ZBgWeeKGks = true;}
      if(cpGyGTIRaW == VJtCrUNrBE){MAipXDjtfp = true;}
      if(tGqPAcZWEM == rhBTuBWhnz){jmcodWbfYl = true;}
      if(KIAMSMgKUj == uHHIDqfqxO){WoDCSEYoPY = true;}
      while(VJtCrUNrBE == cpGyGTIRaW){gMqkfBEDwp = true;}
      while(rhBTuBWhnz == rhBTuBWhnz){wUVEqqxjGi = true;}
      while(uHHIDqfqxO == uHHIDqfqxO){cIZUgmqRif = true;}
      if(GlAgpoqYWg == true){GlAgpoqYWg = false;}
      if(YUcsAtTNxi == true){YUcsAtTNxi = false;}
      if(BuBHQOBkyB == true){BuBHQOBkyB = false;}
      if(oWtlxGhTdG == true){oWtlxGhTdG = false;}
      if(KyKHaadOHI == true){KyKHaadOHI = false;}
      if(WRtONLjsQb == true){WRtONLjsQb = false;}
      if(mFZVqBZqut == true){mFZVqBZqut = false;}
      if(MAipXDjtfp == true){MAipXDjtfp = false;}
      if(jmcodWbfYl == true){jmcodWbfYl = false;}
      if(WoDCSEYoPY == true){WoDCSEYoPY = false;}
      if(AmTNwWiEpJ == true){AmTNwWiEpJ = false;}
      if(aoNaqAckqU == true){aoNaqAckqU = false;}
      if(YtRIXXxgWS == true){YtRIXXxgWS = false;}
      if(eueGoxTPsG == true){eueGoxTPsG = false;}
      if(nXoOLgbbKR == true){nXoOLgbbKR = false;}
      if(bnxuAGUKpY == true){bnxuAGUKpY = false;}
      if(ZBgWeeKGks == true){ZBgWeeKGks = false;}
      if(gMqkfBEDwp == true){gMqkfBEDwp = false;}
      if(wUVEqqxjGi == true){wUVEqqxjGi = false;}
      if(cIZUgmqRif == true){cIZUgmqRif = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DETQBOQEWD
{ 
  void fJZoiZlNZC()
  { 
      bool uoTqHLweLx = false;
      bool jhEjjhprHr = false;
      bool OkxPljBboU = false;
      bool gPjUidNiRT = false;
      bool JqenOibKbT = false;
      bool RrVYkJqEFX = false;
      bool KUppPUxjAF = false;
      bool UHZmhWFIAC = false;
      bool IpzUDotKiY = false;
      bool mJctIoBoYt = false;
      bool kqJVyJShqN = false;
      bool DhDDPTUUla = false;
      bool ZmBbSKeees = false;
      bool VQjGQQgdVt = false;
      bool VLTVUEFZeo = false;
      bool UfCxUypgDn = false;
      bool emDxrmxxly = false;
      bool lqyrENSfGN = false;
      bool EEAoXoOmlR = false;
      bool azahOiIVdh = false;
      string SCjHXxmcma;
      string UFApkhdSye;
      string rPYMzUoOKb;
      string OeIdTGfjAE;
      string iJpDaiVCrx;
      string bEKUYDcWIC;
      string IYSKMoxVWd;
      string BsStwhYVlP;
      string zlVMAKTnFQ;
      string dJbxuJpfpk;
      string lzfNwhkQYp;
      string eGkrDWCFJC;
      string VIQGArRUyl;
      string rseBcAGHQS;
      string YDPPlWYitY;
      string GkVnPdiZNE;
      string QQSlykbiPD;
      string QunqcRsBUd;
      string ThZZeGWplz;
      string QgtMCHkcQA;
      if(SCjHXxmcma == lzfNwhkQYp){uoTqHLweLx = true;}
      else if(lzfNwhkQYp == SCjHXxmcma){kqJVyJShqN = true;}
      if(UFApkhdSye == eGkrDWCFJC){jhEjjhprHr = true;}
      else if(eGkrDWCFJC == UFApkhdSye){DhDDPTUUla = true;}
      if(rPYMzUoOKb == VIQGArRUyl){OkxPljBboU = true;}
      else if(VIQGArRUyl == rPYMzUoOKb){ZmBbSKeees = true;}
      if(OeIdTGfjAE == rseBcAGHQS){gPjUidNiRT = true;}
      else if(rseBcAGHQS == OeIdTGfjAE){VQjGQQgdVt = true;}
      if(iJpDaiVCrx == YDPPlWYitY){JqenOibKbT = true;}
      else if(YDPPlWYitY == iJpDaiVCrx){VLTVUEFZeo = true;}
      if(bEKUYDcWIC == GkVnPdiZNE){RrVYkJqEFX = true;}
      else if(GkVnPdiZNE == bEKUYDcWIC){UfCxUypgDn = true;}
      if(IYSKMoxVWd == QQSlykbiPD){KUppPUxjAF = true;}
      else if(QQSlykbiPD == IYSKMoxVWd){emDxrmxxly = true;}
      if(BsStwhYVlP == QunqcRsBUd){UHZmhWFIAC = true;}
      if(zlVMAKTnFQ == ThZZeGWplz){IpzUDotKiY = true;}
      if(dJbxuJpfpk == QgtMCHkcQA){mJctIoBoYt = true;}
      while(QunqcRsBUd == BsStwhYVlP){lqyrENSfGN = true;}
      while(ThZZeGWplz == ThZZeGWplz){EEAoXoOmlR = true;}
      while(QgtMCHkcQA == QgtMCHkcQA){azahOiIVdh = true;}
      if(uoTqHLweLx == true){uoTqHLweLx = false;}
      if(jhEjjhprHr == true){jhEjjhprHr = false;}
      if(OkxPljBboU == true){OkxPljBboU = false;}
      if(gPjUidNiRT == true){gPjUidNiRT = false;}
      if(JqenOibKbT == true){JqenOibKbT = false;}
      if(RrVYkJqEFX == true){RrVYkJqEFX = false;}
      if(KUppPUxjAF == true){KUppPUxjAF = false;}
      if(UHZmhWFIAC == true){UHZmhWFIAC = false;}
      if(IpzUDotKiY == true){IpzUDotKiY = false;}
      if(mJctIoBoYt == true){mJctIoBoYt = false;}
      if(kqJVyJShqN == true){kqJVyJShqN = false;}
      if(DhDDPTUUla == true){DhDDPTUUla = false;}
      if(ZmBbSKeees == true){ZmBbSKeees = false;}
      if(VQjGQQgdVt == true){VQjGQQgdVt = false;}
      if(VLTVUEFZeo == true){VLTVUEFZeo = false;}
      if(UfCxUypgDn == true){UfCxUypgDn = false;}
      if(emDxrmxxly == true){emDxrmxxly = false;}
      if(lqyrENSfGN == true){lqyrENSfGN = false;}
      if(EEAoXoOmlR == true){EEAoXoOmlR = false;}
      if(azahOiIVdh == true){azahOiIVdh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSHKGPNOJA
{ 
  void GxORrTWpoH()
  { 
      bool PYzArojuhG = false;
      bool YzpwglIIaC = false;
      bool CEgMzamtmU = false;
      bool yrIRuGAnwD = false;
      bool PLdjRbtzsD = false;
      bool xzSPrKqmBQ = false;
      bool CoHNHgpXBZ = false;
      bool kULWmqZxtW = false;
      bool gmBjWyZsZj = false;
      bool ONlfBZDQbk = false;
      bool kWySSbnucB = false;
      bool ktsdjOnXqJ = false;
      bool HxyQKXhfVM = false;
      bool mIVJkKohQt = false;
      bool KdQXyUUIul = false;
      bool kfZRcnXgHu = false;
      bool tHZPObYjsZ = false;
      bool ZFGwzcgaSp = false;
      bool CZjiaGiDfx = false;
      bool lHZVACEAJV = false;
      string AuYhSjtAuy;
      string zDbobdrYIX;
      string PHxRPSdIPX;
      string AnIDiRdcEK;
      string wxAlmDuXHn;
      string FhpLZsxGRA;
      string FljWxLuYFK;
      string zOTyaRGKeL;
      string XFAbSSxwco;
      string TXKDEJMcna;
      string IVSxnpNqjH;
      string lmaGbzlHEe;
      string NyuPqbEPsQ;
      string FdVECBmCmb;
      string EGMUDfwDbE;
      string XEXJNKZCGM;
      string lxxSCIQWEa;
      string MiUcaGkaMK;
      string fAnorAGMpq;
      string bkwZoGIsRt;
      if(AuYhSjtAuy == IVSxnpNqjH){PYzArojuhG = true;}
      else if(IVSxnpNqjH == AuYhSjtAuy){kWySSbnucB = true;}
      if(zDbobdrYIX == lmaGbzlHEe){YzpwglIIaC = true;}
      else if(lmaGbzlHEe == zDbobdrYIX){ktsdjOnXqJ = true;}
      if(PHxRPSdIPX == NyuPqbEPsQ){CEgMzamtmU = true;}
      else if(NyuPqbEPsQ == PHxRPSdIPX){HxyQKXhfVM = true;}
      if(AnIDiRdcEK == FdVECBmCmb){yrIRuGAnwD = true;}
      else if(FdVECBmCmb == AnIDiRdcEK){mIVJkKohQt = true;}
      if(wxAlmDuXHn == EGMUDfwDbE){PLdjRbtzsD = true;}
      else if(EGMUDfwDbE == wxAlmDuXHn){KdQXyUUIul = true;}
      if(FhpLZsxGRA == XEXJNKZCGM){xzSPrKqmBQ = true;}
      else if(XEXJNKZCGM == FhpLZsxGRA){kfZRcnXgHu = true;}
      if(FljWxLuYFK == lxxSCIQWEa){CoHNHgpXBZ = true;}
      else if(lxxSCIQWEa == FljWxLuYFK){tHZPObYjsZ = true;}
      if(zOTyaRGKeL == MiUcaGkaMK){kULWmqZxtW = true;}
      if(XFAbSSxwco == fAnorAGMpq){gmBjWyZsZj = true;}
      if(TXKDEJMcna == bkwZoGIsRt){ONlfBZDQbk = true;}
      while(MiUcaGkaMK == zOTyaRGKeL){ZFGwzcgaSp = true;}
      while(fAnorAGMpq == fAnorAGMpq){CZjiaGiDfx = true;}
      while(bkwZoGIsRt == bkwZoGIsRt){lHZVACEAJV = true;}
      if(PYzArojuhG == true){PYzArojuhG = false;}
      if(YzpwglIIaC == true){YzpwglIIaC = false;}
      if(CEgMzamtmU == true){CEgMzamtmU = false;}
      if(yrIRuGAnwD == true){yrIRuGAnwD = false;}
      if(PLdjRbtzsD == true){PLdjRbtzsD = false;}
      if(xzSPrKqmBQ == true){xzSPrKqmBQ = false;}
      if(CoHNHgpXBZ == true){CoHNHgpXBZ = false;}
      if(kULWmqZxtW == true){kULWmqZxtW = false;}
      if(gmBjWyZsZj == true){gmBjWyZsZj = false;}
      if(ONlfBZDQbk == true){ONlfBZDQbk = false;}
      if(kWySSbnucB == true){kWySSbnucB = false;}
      if(ktsdjOnXqJ == true){ktsdjOnXqJ = false;}
      if(HxyQKXhfVM == true){HxyQKXhfVM = false;}
      if(mIVJkKohQt == true){mIVJkKohQt = false;}
      if(KdQXyUUIul == true){KdQXyUUIul = false;}
      if(kfZRcnXgHu == true){kfZRcnXgHu = false;}
      if(tHZPObYjsZ == true){tHZPObYjsZ = false;}
      if(ZFGwzcgaSp == true){ZFGwzcgaSp = false;}
      if(CZjiaGiDfx == true){CZjiaGiDfx = false;}
      if(lHZVACEAJV == true){lHZVACEAJV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQIYZLGRRT
{ 
  void jJAWsfoHjh()
  { 
      bool EwtLxcXMVx = false;
      bool pmiWtqYkia = false;
      bool sjVBWDhsDB = false;
      bool cfEpnCgcuW = false;
      bool wENfikdrBj = false;
      bool EdSKAUasnt = false;
      bool ueIUTJiriq = false;
      bool KuoMeoWoSk = false;
      bool YpqTwzNsoT = false;
      bool bnnAbRwrLY = false;
      bool ClJKYInGfL = false;
      bool ykZDVEmoYU = false;
      bool woCOOWHojM = false;
      bool rdcshlfgtm = false;
      bool LHMcUqNkeW = false;
      bool dHTqcMituC = false;
      bool BzVTSUIfUi = false;
      bool XGtkJocYtX = false;
      bool IVJNikJkQU = false;
      bool DllrkLlsJA = false;
      string eHJXrDjkPd;
      string IFGhgnNFWd;
      string gixsEpOqaa;
      string IonUTleRFB;
      string xEGqwLmXcw;
      string NIHqHuJQTB;
      string orJnUTRkNt;
      string IwzUfcbGxs;
      string DpOdMzgwMX;
      string bOxEMFtSVc;
      string sBJinRImKe;
      string TDSaxydfaV;
      string lUXoRtyuIa;
      string iIjTzBgfpu;
      string qtlhEYuWGO;
      string aNrApYcTQs;
      string TNeiwKTzbu;
      string Qxpferipks;
      string zbnsAUQidZ;
      string YNPwbdOClt;
      if(eHJXrDjkPd == sBJinRImKe){EwtLxcXMVx = true;}
      else if(sBJinRImKe == eHJXrDjkPd){ClJKYInGfL = true;}
      if(IFGhgnNFWd == TDSaxydfaV){pmiWtqYkia = true;}
      else if(TDSaxydfaV == IFGhgnNFWd){ykZDVEmoYU = true;}
      if(gixsEpOqaa == lUXoRtyuIa){sjVBWDhsDB = true;}
      else if(lUXoRtyuIa == gixsEpOqaa){woCOOWHojM = true;}
      if(IonUTleRFB == iIjTzBgfpu){cfEpnCgcuW = true;}
      else if(iIjTzBgfpu == IonUTleRFB){rdcshlfgtm = true;}
      if(xEGqwLmXcw == qtlhEYuWGO){wENfikdrBj = true;}
      else if(qtlhEYuWGO == xEGqwLmXcw){LHMcUqNkeW = true;}
      if(NIHqHuJQTB == aNrApYcTQs){EdSKAUasnt = true;}
      else if(aNrApYcTQs == NIHqHuJQTB){dHTqcMituC = true;}
      if(orJnUTRkNt == TNeiwKTzbu){ueIUTJiriq = true;}
      else if(TNeiwKTzbu == orJnUTRkNt){BzVTSUIfUi = true;}
      if(IwzUfcbGxs == Qxpferipks){KuoMeoWoSk = true;}
      if(DpOdMzgwMX == zbnsAUQidZ){YpqTwzNsoT = true;}
      if(bOxEMFtSVc == YNPwbdOClt){bnnAbRwrLY = true;}
      while(Qxpferipks == IwzUfcbGxs){XGtkJocYtX = true;}
      while(zbnsAUQidZ == zbnsAUQidZ){IVJNikJkQU = true;}
      while(YNPwbdOClt == YNPwbdOClt){DllrkLlsJA = true;}
      if(EwtLxcXMVx == true){EwtLxcXMVx = false;}
      if(pmiWtqYkia == true){pmiWtqYkia = false;}
      if(sjVBWDhsDB == true){sjVBWDhsDB = false;}
      if(cfEpnCgcuW == true){cfEpnCgcuW = false;}
      if(wENfikdrBj == true){wENfikdrBj = false;}
      if(EdSKAUasnt == true){EdSKAUasnt = false;}
      if(ueIUTJiriq == true){ueIUTJiriq = false;}
      if(KuoMeoWoSk == true){KuoMeoWoSk = false;}
      if(YpqTwzNsoT == true){YpqTwzNsoT = false;}
      if(bnnAbRwrLY == true){bnnAbRwrLY = false;}
      if(ClJKYInGfL == true){ClJKYInGfL = false;}
      if(ykZDVEmoYU == true){ykZDVEmoYU = false;}
      if(woCOOWHojM == true){woCOOWHojM = false;}
      if(rdcshlfgtm == true){rdcshlfgtm = false;}
      if(LHMcUqNkeW == true){LHMcUqNkeW = false;}
      if(dHTqcMituC == true){dHTqcMituC = false;}
      if(BzVTSUIfUi == true){BzVTSUIfUi = false;}
      if(XGtkJocYtX == true){XGtkJocYtX = false;}
      if(IVJNikJkQU == true){IVJNikJkQU = false;}
      if(DllrkLlsJA == true){DllrkLlsJA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGIJKASAQN
{ 
  void rtHCCQOSYE()
  { 
      bool gUdEXEDRBV = false;
      bool IOUFcalGAK = false;
      bool AjclYRhTkW = false;
      bool sxhVaUAgKU = false;
      bool HfhXuTfEeJ = false;
      bool EICITwrrfG = false;
      bool VjfdcLgyeH = false;
      bool aFueCTBEpE = false;
      bool kdobSjuYCd = false;
      bool cIBEzXzDuj = false;
      bool mhYWhyMWFz = false;
      bool tmBaUqtELs = false;
      bool PHuAeSEqfe = false;
      bool UxJGRDFRtT = false;
      bool WXTDjpGZiH = false;
      bool curCTelYqO = false;
      bool tVqadwctIQ = false;
      bool lbJqVrmrQo = false;
      bool MdHXBZFHml = false;
      bool QfaeZBfsYm = false;
      string MHAfRMAoXf;
      string LChcKcoqZC;
      string orumgGErHR;
      string TeCoUgDUcd;
      string TPGEWjAZzc;
      string XjLdlULMzL;
      string IHhGMfzsHd;
      string ZTOuhYkqPw;
      string FdrdtjTXCA;
      string VpVRVLhArp;
      string jGRVDDUPwM;
      string iTxCFdODMb;
      string MbqHIiyxZV;
      string pkzYMyLWap;
      string OEboRBsTLq;
      string wenPdIPKMT;
      string FXoZVxUXpH;
      string SrbVNHzBpH;
      string pdkiZLxjtD;
      string hAJHjpOCTT;
      if(MHAfRMAoXf == jGRVDDUPwM){gUdEXEDRBV = true;}
      else if(jGRVDDUPwM == MHAfRMAoXf){mhYWhyMWFz = true;}
      if(LChcKcoqZC == iTxCFdODMb){IOUFcalGAK = true;}
      else if(iTxCFdODMb == LChcKcoqZC){tmBaUqtELs = true;}
      if(orumgGErHR == MbqHIiyxZV){AjclYRhTkW = true;}
      else if(MbqHIiyxZV == orumgGErHR){PHuAeSEqfe = true;}
      if(TeCoUgDUcd == pkzYMyLWap){sxhVaUAgKU = true;}
      else if(pkzYMyLWap == TeCoUgDUcd){UxJGRDFRtT = true;}
      if(TPGEWjAZzc == OEboRBsTLq){HfhXuTfEeJ = true;}
      else if(OEboRBsTLq == TPGEWjAZzc){WXTDjpGZiH = true;}
      if(XjLdlULMzL == wenPdIPKMT){EICITwrrfG = true;}
      else if(wenPdIPKMT == XjLdlULMzL){curCTelYqO = true;}
      if(IHhGMfzsHd == FXoZVxUXpH){VjfdcLgyeH = true;}
      else if(FXoZVxUXpH == IHhGMfzsHd){tVqadwctIQ = true;}
      if(ZTOuhYkqPw == SrbVNHzBpH){aFueCTBEpE = true;}
      if(FdrdtjTXCA == pdkiZLxjtD){kdobSjuYCd = true;}
      if(VpVRVLhArp == hAJHjpOCTT){cIBEzXzDuj = true;}
      while(SrbVNHzBpH == ZTOuhYkqPw){lbJqVrmrQo = true;}
      while(pdkiZLxjtD == pdkiZLxjtD){MdHXBZFHml = true;}
      while(hAJHjpOCTT == hAJHjpOCTT){QfaeZBfsYm = true;}
      if(gUdEXEDRBV == true){gUdEXEDRBV = false;}
      if(IOUFcalGAK == true){IOUFcalGAK = false;}
      if(AjclYRhTkW == true){AjclYRhTkW = false;}
      if(sxhVaUAgKU == true){sxhVaUAgKU = false;}
      if(HfhXuTfEeJ == true){HfhXuTfEeJ = false;}
      if(EICITwrrfG == true){EICITwrrfG = false;}
      if(VjfdcLgyeH == true){VjfdcLgyeH = false;}
      if(aFueCTBEpE == true){aFueCTBEpE = false;}
      if(kdobSjuYCd == true){kdobSjuYCd = false;}
      if(cIBEzXzDuj == true){cIBEzXzDuj = false;}
      if(mhYWhyMWFz == true){mhYWhyMWFz = false;}
      if(tmBaUqtELs == true){tmBaUqtELs = false;}
      if(PHuAeSEqfe == true){PHuAeSEqfe = false;}
      if(UxJGRDFRtT == true){UxJGRDFRtT = false;}
      if(WXTDjpGZiH == true){WXTDjpGZiH = false;}
      if(curCTelYqO == true){curCTelYqO = false;}
      if(tVqadwctIQ == true){tVqadwctIQ = false;}
      if(lbJqVrmrQo == true){lbJqVrmrQo = false;}
      if(MdHXBZFHml == true){MdHXBZFHml = false;}
      if(QfaeZBfsYm == true){QfaeZBfsYm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMCYTWIDKL
{ 
  void BzYJAABsaS()
  { 
      bool OKlGBGenfR = false;
      bool DDGXcRGlUd = false;
      bool lHjeutuksq = false;
      bool eYAhUuNAlJ = false;
      bool trCUiZstCG = false;
      bool oUonRGZHLH = false;
      bool LtunldCXDg = false;
      bool DFAKjtFOuU = false;
      bool AAimBKjMQN = false;
      bool VFoeyAxNiE = false;
      bool XUqUCiUdDX = false;
      bool BKLpGKKImb = false;
      bool toHoLyQVMi = false;
      bool xqfqxfJNjR = false;
      bool pFIsMKtyXn = false;
      bool ooaGKhNCJE = false;
      bool SyRUZJeUsa = false;
      bool BxXUlnfNcA = false;
      bool DRxXsHPZfP = false;
      bool RHDfzqnnSC = false;
      string VzaewbERdD;
      string jaBStPMguB;
      string lTnxBJozzR;
      string xYePeIbTpY;
      string KqWVhMxqfM;
      string KogMTCKdcl;
      string mFRLFKwkmk;
      string mrpVpuxSOn;
      string MySmGIrRuc;
      string xyqElFZKQW;
      string QMDtYRzKVY;
      string FrOnYoldFx;
      string SdoKnoBljj;
      string UlBqXAtYNn;
      string JguVXFiCew;
      string TuFTElWsGi;
      string QMZlESpXQY;
      string uMPQmliSmi;
      string GzGnQZghml;
      string dAReXwGJRE;
      if(VzaewbERdD == QMDtYRzKVY){OKlGBGenfR = true;}
      else if(QMDtYRzKVY == VzaewbERdD){XUqUCiUdDX = true;}
      if(jaBStPMguB == FrOnYoldFx){DDGXcRGlUd = true;}
      else if(FrOnYoldFx == jaBStPMguB){BKLpGKKImb = true;}
      if(lTnxBJozzR == SdoKnoBljj){lHjeutuksq = true;}
      else if(SdoKnoBljj == lTnxBJozzR){toHoLyQVMi = true;}
      if(xYePeIbTpY == UlBqXAtYNn){eYAhUuNAlJ = true;}
      else if(UlBqXAtYNn == xYePeIbTpY){xqfqxfJNjR = true;}
      if(KqWVhMxqfM == JguVXFiCew){trCUiZstCG = true;}
      else if(JguVXFiCew == KqWVhMxqfM){pFIsMKtyXn = true;}
      if(KogMTCKdcl == TuFTElWsGi){oUonRGZHLH = true;}
      else if(TuFTElWsGi == KogMTCKdcl){ooaGKhNCJE = true;}
      if(mFRLFKwkmk == QMZlESpXQY){LtunldCXDg = true;}
      else if(QMZlESpXQY == mFRLFKwkmk){SyRUZJeUsa = true;}
      if(mrpVpuxSOn == uMPQmliSmi){DFAKjtFOuU = true;}
      if(MySmGIrRuc == GzGnQZghml){AAimBKjMQN = true;}
      if(xyqElFZKQW == dAReXwGJRE){VFoeyAxNiE = true;}
      while(uMPQmliSmi == mrpVpuxSOn){BxXUlnfNcA = true;}
      while(GzGnQZghml == GzGnQZghml){DRxXsHPZfP = true;}
      while(dAReXwGJRE == dAReXwGJRE){RHDfzqnnSC = true;}
      if(OKlGBGenfR == true){OKlGBGenfR = false;}
      if(DDGXcRGlUd == true){DDGXcRGlUd = false;}
      if(lHjeutuksq == true){lHjeutuksq = false;}
      if(eYAhUuNAlJ == true){eYAhUuNAlJ = false;}
      if(trCUiZstCG == true){trCUiZstCG = false;}
      if(oUonRGZHLH == true){oUonRGZHLH = false;}
      if(LtunldCXDg == true){LtunldCXDg = false;}
      if(DFAKjtFOuU == true){DFAKjtFOuU = false;}
      if(AAimBKjMQN == true){AAimBKjMQN = false;}
      if(VFoeyAxNiE == true){VFoeyAxNiE = false;}
      if(XUqUCiUdDX == true){XUqUCiUdDX = false;}
      if(BKLpGKKImb == true){BKLpGKKImb = false;}
      if(toHoLyQVMi == true){toHoLyQVMi = false;}
      if(xqfqxfJNjR == true){xqfqxfJNjR = false;}
      if(pFIsMKtyXn == true){pFIsMKtyXn = false;}
      if(ooaGKhNCJE == true){ooaGKhNCJE = false;}
      if(SyRUZJeUsa == true){SyRUZJeUsa = false;}
      if(BxXUlnfNcA == true){BxXUlnfNcA = false;}
      if(DRxXsHPZfP == true){DRxXsHPZfP = false;}
      if(RHDfzqnnSC == true){RHDfzqnnSC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTFWZMVGME
{ 
  void GfzRtYOCXE()
  { 
      bool hDcdFGGhZX = false;
      bool IwVfsIYkYY = false;
      bool WnQKVhcmgm = false;
      bool KEWqYfSgWe = false;
      bool pyKjcJJwjx = false;
      bool XFdUwtmSHX = false;
      bool dSAmMDZdGN = false;
      bool oqNthXcfgM = false;
      bool XgDiPFZCte = false;
      bool rAYzBXxXXY = false;
      bool jeoVIfqjlY = false;
      bool QGkuzwPQXG = false;
      bool cWjbUoSOsK = false;
      bool ZEIIcsqgai = false;
      bool NpQVNlPdAE = false;
      bool HgAQuMtNAT = false;
      bool NcqayMybSG = false;
      bool FhpnsmGONi = false;
      bool YnOnCsDqMP = false;
      bool ydgHVkzoXB = false;
      string AdrBCzxDZx;
      string fICVFEsdXF;
      string hWpURsBJht;
      string BIPPIOHEKm;
      string WQzVEefbql;
      string MTtrIdnWiI;
      string xmUfwWsmNp;
      string wnTjhRWTPm;
      string MZRwhgOXGe;
      string ajUCoiwTYh;
      string lsOBoXAJJq;
      string GTHwuXVXxP;
      string HVfhOMTQuz;
      string UCthBTKPGK;
      string fFNPXHcXGR;
      string NXVJZPNfmc;
      string DiOKVDYYub;
      string MGRmiCHQKG;
      string iuKclxgkIk;
      string GecdGwqDsT;
      if(AdrBCzxDZx == lsOBoXAJJq){hDcdFGGhZX = true;}
      else if(lsOBoXAJJq == AdrBCzxDZx){jeoVIfqjlY = true;}
      if(fICVFEsdXF == GTHwuXVXxP){IwVfsIYkYY = true;}
      else if(GTHwuXVXxP == fICVFEsdXF){QGkuzwPQXG = true;}
      if(hWpURsBJht == HVfhOMTQuz){WnQKVhcmgm = true;}
      else if(HVfhOMTQuz == hWpURsBJht){cWjbUoSOsK = true;}
      if(BIPPIOHEKm == UCthBTKPGK){KEWqYfSgWe = true;}
      else if(UCthBTKPGK == BIPPIOHEKm){ZEIIcsqgai = true;}
      if(WQzVEefbql == fFNPXHcXGR){pyKjcJJwjx = true;}
      else if(fFNPXHcXGR == WQzVEefbql){NpQVNlPdAE = true;}
      if(MTtrIdnWiI == NXVJZPNfmc){XFdUwtmSHX = true;}
      else if(NXVJZPNfmc == MTtrIdnWiI){HgAQuMtNAT = true;}
      if(xmUfwWsmNp == DiOKVDYYub){dSAmMDZdGN = true;}
      else if(DiOKVDYYub == xmUfwWsmNp){NcqayMybSG = true;}
      if(wnTjhRWTPm == MGRmiCHQKG){oqNthXcfgM = true;}
      if(MZRwhgOXGe == iuKclxgkIk){XgDiPFZCte = true;}
      if(ajUCoiwTYh == GecdGwqDsT){rAYzBXxXXY = true;}
      while(MGRmiCHQKG == wnTjhRWTPm){FhpnsmGONi = true;}
      while(iuKclxgkIk == iuKclxgkIk){YnOnCsDqMP = true;}
      while(GecdGwqDsT == GecdGwqDsT){ydgHVkzoXB = true;}
      if(hDcdFGGhZX == true){hDcdFGGhZX = false;}
      if(IwVfsIYkYY == true){IwVfsIYkYY = false;}
      if(WnQKVhcmgm == true){WnQKVhcmgm = false;}
      if(KEWqYfSgWe == true){KEWqYfSgWe = false;}
      if(pyKjcJJwjx == true){pyKjcJJwjx = false;}
      if(XFdUwtmSHX == true){XFdUwtmSHX = false;}
      if(dSAmMDZdGN == true){dSAmMDZdGN = false;}
      if(oqNthXcfgM == true){oqNthXcfgM = false;}
      if(XgDiPFZCte == true){XgDiPFZCte = false;}
      if(rAYzBXxXXY == true){rAYzBXxXXY = false;}
      if(jeoVIfqjlY == true){jeoVIfqjlY = false;}
      if(QGkuzwPQXG == true){QGkuzwPQXG = false;}
      if(cWjbUoSOsK == true){cWjbUoSOsK = false;}
      if(ZEIIcsqgai == true){ZEIIcsqgai = false;}
      if(NpQVNlPdAE == true){NpQVNlPdAE = false;}
      if(HgAQuMtNAT == true){HgAQuMtNAT = false;}
      if(NcqayMybSG == true){NcqayMybSG = false;}
      if(FhpnsmGONi == true){FhpnsmGONi = false;}
      if(YnOnCsDqMP == true){YnOnCsDqMP = false;}
      if(ydgHVkzoXB == true){ydgHVkzoXB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJYOSKEMKD
{ 
  void uZGCwAatGy()
  { 
      bool PwNtrJiMrE = false;
      bool LXjyEhrLZs = false;
      bool WOKGhttZLb = false;
      bool rOpgTkkJCM = false;
      bool oKMNcoelwh = false;
      bool aXwFaAkHLx = false;
      bool OJAQMwgDdT = false;
      bool xiJNELCxcs = false;
      bool PHcdATRjGS = false;
      bool AcxExfKwBg = false;
      bool HbHckrOiBO = false;
      bool ymdShGfWPr = false;
      bool dxwLSTkFPX = false;
      bool BGwwkmzAsI = false;
      bool FihrUMzdWq = false;
      bool AmfICKewJQ = false;
      bool GJSdMqqght = false;
      bool GedGmuOEpG = false;
      bool UGhXWOamtZ = false;
      bool IDqbBwQEed = false;
      string BGqgMiNeqT;
      string yILQKmGgkM;
      string hMFOOucohb;
      string BkehqweHbx;
      string MWgPOczLRB;
      string nuqGNoAcRR;
      string GXwPRNcdYO;
      string IyEmzKfpAk;
      string wQXgnGtYUB;
      string uBpKqoaRyA;
      string AVlDrppDGC;
      string JKcfUoAPaK;
      string TDIWTGIswK;
      string jOqzkZeTny;
      string PqSSrjYJoC;
      string oKpmgwNOil;
      string gwGwSuTcuu;
      string Jfbcuckpej;
      string gyEtVYXERn;
      string MPkBQSjWzx;
      if(BGqgMiNeqT == AVlDrppDGC){PwNtrJiMrE = true;}
      else if(AVlDrppDGC == BGqgMiNeqT){HbHckrOiBO = true;}
      if(yILQKmGgkM == JKcfUoAPaK){LXjyEhrLZs = true;}
      else if(JKcfUoAPaK == yILQKmGgkM){ymdShGfWPr = true;}
      if(hMFOOucohb == TDIWTGIswK){WOKGhttZLb = true;}
      else if(TDIWTGIswK == hMFOOucohb){dxwLSTkFPX = true;}
      if(BkehqweHbx == jOqzkZeTny){rOpgTkkJCM = true;}
      else if(jOqzkZeTny == BkehqweHbx){BGwwkmzAsI = true;}
      if(MWgPOczLRB == PqSSrjYJoC){oKMNcoelwh = true;}
      else if(PqSSrjYJoC == MWgPOczLRB){FihrUMzdWq = true;}
      if(nuqGNoAcRR == oKpmgwNOil){aXwFaAkHLx = true;}
      else if(oKpmgwNOil == nuqGNoAcRR){AmfICKewJQ = true;}
      if(GXwPRNcdYO == gwGwSuTcuu){OJAQMwgDdT = true;}
      else if(gwGwSuTcuu == GXwPRNcdYO){GJSdMqqght = true;}
      if(IyEmzKfpAk == Jfbcuckpej){xiJNELCxcs = true;}
      if(wQXgnGtYUB == gyEtVYXERn){PHcdATRjGS = true;}
      if(uBpKqoaRyA == MPkBQSjWzx){AcxExfKwBg = true;}
      while(Jfbcuckpej == IyEmzKfpAk){GedGmuOEpG = true;}
      while(gyEtVYXERn == gyEtVYXERn){UGhXWOamtZ = true;}
      while(MPkBQSjWzx == MPkBQSjWzx){IDqbBwQEed = true;}
      if(PwNtrJiMrE == true){PwNtrJiMrE = false;}
      if(LXjyEhrLZs == true){LXjyEhrLZs = false;}
      if(WOKGhttZLb == true){WOKGhttZLb = false;}
      if(rOpgTkkJCM == true){rOpgTkkJCM = false;}
      if(oKMNcoelwh == true){oKMNcoelwh = false;}
      if(aXwFaAkHLx == true){aXwFaAkHLx = false;}
      if(OJAQMwgDdT == true){OJAQMwgDdT = false;}
      if(xiJNELCxcs == true){xiJNELCxcs = false;}
      if(PHcdATRjGS == true){PHcdATRjGS = false;}
      if(AcxExfKwBg == true){AcxExfKwBg = false;}
      if(HbHckrOiBO == true){HbHckrOiBO = false;}
      if(ymdShGfWPr == true){ymdShGfWPr = false;}
      if(dxwLSTkFPX == true){dxwLSTkFPX = false;}
      if(BGwwkmzAsI == true){BGwwkmzAsI = false;}
      if(FihrUMzdWq == true){FihrUMzdWq = false;}
      if(AmfICKewJQ == true){AmfICKewJQ = false;}
      if(GJSdMqqght == true){GJSdMqqght = false;}
      if(GedGmuOEpG == true){GedGmuOEpG = false;}
      if(UGhXWOamtZ == true){UGhXWOamtZ = false;}
      if(IDqbBwQEed == true){IDqbBwQEed = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCPOUYZNSV
{ 
  void xRZPcMFRPu()
  { 
      bool jQpYjORnoY = false;
      bool rTqVKWrObq = false;
      bool DayshtHOFr = false;
      bool mGjrGetEzF = false;
      bool NuKHqUwUuK = false;
      bool OKJARJRxqo = false;
      bool HChxkkjyOf = false;
      bool bmOWcHPqCM = false;
      bool ymTuccxjax = false;
      bool MxNJxLMNVF = false;
      bool kxFPibulWK = false;
      bool saueqUimTI = false;
      bool mAXRSdYEYR = false;
      bool tCUwaBgDLB = false;
      bool gKMQDlCiSc = false;
      bool cZsNSkZnwE = false;
      bool CqNFPqFyDp = false;
      bool meaSbbmHNg = false;
      bool bpkuoUIHdp = false;
      bool asGHypxHAM = false;
      string PyxEYOixNw;
      string ZYfAhOJEeb;
      string MAZNdyWPzi;
      string uSklWBcpcj;
      string gVjRbydDwl;
      string gWuYhPYiaZ;
      string rTxeAHmtcf;
      string lTbttqQHle;
      string TSSNCXXMEH;
      string csOCrNXERU;
      string LjaPzMuAdp;
      string zQxwGZAjcb;
      string iaoVDrEZCg;
      string TLoRTjqDNo;
      string cWhNILwSuS;
      string MnbokjtEMH;
      string HVywWmaebW;
      string hxVmzMraNq;
      string wkdjUfjAfi;
      string ompGgGYkqU;
      if(PyxEYOixNw == LjaPzMuAdp){jQpYjORnoY = true;}
      else if(LjaPzMuAdp == PyxEYOixNw){kxFPibulWK = true;}
      if(ZYfAhOJEeb == zQxwGZAjcb){rTqVKWrObq = true;}
      else if(zQxwGZAjcb == ZYfAhOJEeb){saueqUimTI = true;}
      if(MAZNdyWPzi == iaoVDrEZCg){DayshtHOFr = true;}
      else if(iaoVDrEZCg == MAZNdyWPzi){mAXRSdYEYR = true;}
      if(uSklWBcpcj == TLoRTjqDNo){mGjrGetEzF = true;}
      else if(TLoRTjqDNo == uSklWBcpcj){tCUwaBgDLB = true;}
      if(gVjRbydDwl == cWhNILwSuS){NuKHqUwUuK = true;}
      else if(cWhNILwSuS == gVjRbydDwl){gKMQDlCiSc = true;}
      if(gWuYhPYiaZ == MnbokjtEMH){OKJARJRxqo = true;}
      else if(MnbokjtEMH == gWuYhPYiaZ){cZsNSkZnwE = true;}
      if(rTxeAHmtcf == HVywWmaebW){HChxkkjyOf = true;}
      else if(HVywWmaebW == rTxeAHmtcf){CqNFPqFyDp = true;}
      if(lTbttqQHle == hxVmzMraNq){bmOWcHPqCM = true;}
      if(TSSNCXXMEH == wkdjUfjAfi){ymTuccxjax = true;}
      if(csOCrNXERU == ompGgGYkqU){MxNJxLMNVF = true;}
      while(hxVmzMraNq == lTbttqQHle){meaSbbmHNg = true;}
      while(wkdjUfjAfi == wkdjUfjAfi){bpkuoUIHdp = true;}
      while(ompGgGYkqU == ompGgGYkqU){asGHypxHAM = true;}
      if(jQpYjORnoY == true){jQpYjORnoY = false;}
      if(rTqVKWrObq == true){rTqVKWrObq = false;}
      if(DayshtHOFr == true){DayshtHOFr = false;}
      if(mGjrGetEzF == true){mGjrGetEzF = false;}
      if(NuKHqUwUuK == true){NuKHqUwUuK = false;}
      if(OKJARJRxqo == true){OKJARJRxqo = false;}
      if(HChxkkjyOf == true){HChxkkjyOf = false;}
      if(bmOWcHPqCM == true){bmOWcHPqCM = false;}
      if(ymTuccxjax == true){ymTuccxjax = false;}
      if(MxNJxLMNVF == true){MxNJxLMNVF = false;}
      if(kxFPibulWK == true){kxFPibulWK = false;}
      if(saueqUimTI == true){saueqUimTI = false;}
      if(mAXRSdYEYR == true){mAXRSdYEYR = false;}
      if(tCUwaBgDLB == true){tCUwaBgDLB = false;}
      if(gKMQDlCiSc == true){gKMQDlCiSc = false;}
      if(cZsNSkZnwE == true){cZsNSkZnwE = false;}
      if(CqNFPqFyDp == true){CqNFPqFyDp = false;}
      if(meaSbbmHNg == true){meaSbbmHNg = false;}
      if(bpkuoUIHdp == true){bpkuoUIHdp = false;}
      if(asGHypxHAM == true){asGHypxHAM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDKGEUCNKN
{ 
  void DxBTXtgEKy()
  { 
      bool YXkcSOpymu = false;
      bool ijtrRFxEDU = false;
      bool sCXPiILVrl = false;
      bool lPptsAWDFa = false;
      bool joLLdLWKEH = false;
      bool WRSVcVzVsJ = false;
      bool DTGBJSsAyQ = false;
      bool itzbjDqMlW = false;
      bool kBRkPTxURW = false;
      bool AAJuXQiKBK = false;
      bool SWLnXcSpkY = false;
      bool emjWXBCUkp = false;
      bool VYiaQhjEDT = false;
      bool UfLaEOocMm = false;
      bool BGirqNQlWV = false;
      bool NNYKosnkXp = false;
      bool rOlQEybJRJ = false;
      bool MYIyoOopiD = false;
      bool RxghGGGAkK = false;
      bool aEFVulTRms = false;
      string ssDbyrhBaw;
      string zAHSWeisTZ;
      string WuHnKBgnQm;
      string bySuYGJoAH;
      string AYVROFzYVm;
      string dLFnDxkPQx;
      string LtjnUBgMtP;
      string UtrMZyYpYF;
      string CHSdJQrera;
      string VsYDwFnhxN;
      string XmeFRiSsOF;
      string XtpKtDbFeD;
      string ICUTtaVoQT;
      string JqrLhOcNMZ;
      string xzQlCaCNIr;
      string diDsEUSLKp;
      string NdctugBebf;
      string ZOsEGIlhQS;
      string YHfXpanzGM;
      string wRCWMTWVqV;
      if(ssDbyrhBaw == XmeFRiSsOF){YXkcSOpymu = true;}
      else if(XmeFRiSsOF == ssDbyrhBaw){SWLnXcSpkY = true;}
      if(zAHSWeisTZ == XtpKtDbFeD){ijtrRFxEDU = true;}
      else if(XtpKtDbFeD == zAHSWeisTZ){emjWXBCUkp = true;}
      if(WuHnKBgnQm == ICUTtaVoQT){sCXPiILVrl = true;}
      else if(ICUTtaVoQT == WuHnKBgnQm){VYiaQhjEDT = true;}
      if(bySuYGJoAH == JqrLhOcNMZ){lPptsAWDFa = true;}
      else if(JqrLhOcNMZ == bySuYGJoAH){UfLaEOocMm = true;}
      if(AYVROFzYVm == xzQlCaCNIr){joLLdLWKEH = true;}
      else if(xzQlCaCNIr == AYVROFzYVm){BGirqNQlWV = true;}
      if(dLFnDxkPQx == diDsEUSLKp){WRSVcVzVsJ = true;}
      else if(diDsEUSLKp == dLFnDxkPQx){NNYKosnkXp = true;}
      if(LtjnUBgMtP == NdctugBebf){DTGBJSsAyQ = true;}
      else if(NdctugBebf == LtjnUBgMtP){rOlQEybJRJ = true;}
      if(UtrMZyYpYF == ZOsEGIlhQS){itzbjDqMlW = true;}
      if(CHSdJQrera == YHfXpanzGM){kBRkPTxURW = true;}
      if(VsYDwFnhxN == wRCWMTWVqV){AAJuXQiKBK = true;}
      while(ZOsEGIlhQS == UtrMZyYpYF){MYIyoOopiD = true;}
      while(YHfXpanzGM == YHfXpanzGM){RxghGGGAkK = true;}
      while(wRCWMTWVqV == wRCWMTWVqV){aEFVulTRms = true;}
      if(YXkcSOpymu == true){YXkcSOpymu = false;}
      if(ijtrRFxEDU == true){ijtrRFxEDU = false;}
      if(sCXPiILVrl == true){sCXPiILVrl = false;}
      if(lPptsAWDFa == true){lPptsAWDFa = false;}
      if(joLLdLWKEH == true){joLLdLWKEH = false;}
      if(WRSVcVzVsJ == true){WRSVcVzVsJ = false;}
      if(DTGBJSsAyQ == true){DTGBJSsAyQ = false;}
      if(itzbjDqMlW == true){itzbjDqMlW = false;}
      if(kBRkPTxURW == true){kBRkPTxURW = false;}
      if(AAJuXQiKBK == true){AAJuXQiKBK = false;}
      if(SWLnXcSpkY == true){SWLnXcSpkY = false;}
      if(emjWXBCUkp == true){emjWXBCUkp = false;}
      if(VYiaQhjEDT == true){VYiaQhjEDT = false;}
      if(UfLaEOocMm == true){UfLaEOocMm = false;}
      if(BGirqNQlWV == true){BGirqNQlWV = false;}
      if(NNYKosnkXp == true){NNYKosnkXp = false;}
      if(rOlQEybJRJ == true){rOlQEybJRJ = false;}
      if(MYIyoOopiD == true){MYIyoOopiD = false;}
      if(RxghGGGAkK == true){RxghGGGAkK = false;}
      if(aEFVulTRms == true){aEFVulTRms = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHWYBSIXFT
{ 
  void yUUpfMVNGK()
  { 
      bool pcDcRtOSWe = false;
      bool sziWaXDIZr = false;
      bool CayhLMlmxC = false;
      bool lEgVQcKqNp = false;
      bool OPwgrMzUCk = false;
      bool pXJVyOeVRF = false;
      bool HbVUsnRMGx = false;
      bool NMtjcmeQoz = false;
      bool MQkMMNuKXB = false;
      bool ynZIhltbmD = false;
      bool tlOEWddZrL = false;
      bool jNfSsqqJHf = false;
      bool sGoFzZllBp = false;
      bool rDdlEaCfoi = false;
      bool jVRMQjIHPq = false;
      bool ujTHKmxJFx = false;
      bool qrXBSgjtNS = false;
      bool oKTYwXncnO = false;
      bool QeVKuIiVaQ = false;
      bool crarqqxQsi = false;
      string MosRPIESNn;
      string WHFCcdgqit;
      string ahkatDPPKq;
      string KeMJLVaipq;
      string MMyNdKWIab;
      string WwazsdESWL;
      string roIWdrtuqG;
      string CxBrgNjWwi;
      string gHoiUNDMPg;
      string QILeyXEbjl;
      string PaQTZYuhSe;
      string tgVmdkzYCP;
      string nhfKpslVsI;
      string JImKTGpVJu;
      string SVsjmjmXAN;
      string XeZTyhtGcf;
      string lYoKVktKTX;
      string udPGwSnuXG;
      string FNUfjdiSMl;
      string LircJtgiOB;
      if(MosRPIESNn == PaQTZYuhSe){pcDcRtOSWe = true;}
      else if(PaQTZYuhSe == MosRPIESNn){tlOEWddZrL = true;}
      if(WHFCcdgqit == tgVmdkzYCP){sziWaXDIZr = true;}
      else if(tgVmdkzYCP == WHFCcdgqit){jNfSsqqJHf = true;}
      if(ahkatDPPKq == nhfKpslVsI){CayhLMlmxC = true;}
      else if(nhfKpslVsI == ahkatDPPKq){sGoFzZllBp = true;}
      if(KeMJLVaipq == JImKTGpVJu){lEgVQcKqNp = true;}
      else if(JImKTGpVJu == KeMJLVaipq){rDdlEaCfoi = true;}
      if(MMyNdKWIab == SVsjmjmXAN){OPwgrMzUCk = true;}
      else if(SVsjmjmXAN == MMyNdKWIab){jVRMQjIHPq = true;}
      if(WwazsdESWL == XeZTyhtGcf){pXJVyOeVRF = true;}
      else if(XeZTyhtGcf == WwazsdESWL){ujTHKmxJFx = true;}
      if(roIWdrtuqG == lYoKVktKTX){HbVUsnRMGx = true;}
      else if(lYoKVktKTX == roIWdrtuqG){qrXBSgjtNS = true;}
      if(CxBrgNjWwi == udPGwSnuXG){NMtjcmeQoz = true;}
      if(gHoiUNDMPg == FNUfjdiSMl){MQkMMNuKXB = true;}
      if(QILeyXEbjl == LircJtgiOB){ynZIhltbmD = true;}
      while(udPGwSnuXG == CxBrgNjWwi){oKTYwXncnO = true;}
      while(FNUfjdiSMl == FNUfjdiSMl){QeVKuIiVaQ = true;}
      while(LircJtgiOB == LircJtgiOB){crarqqxQsi = true;}
      if(pcDcRtOSWe == true){pcDcRtOSWe = false;}
      if(sziWaXDIZr == true){sziWaXDIZr = false;}
      if(CayhLMlmxC == true){CayhLMlmxC = false;}
      if(lEgVQcKqNp == true){lEgVQcKqNp = false;}
      if(OPwgrMzUCk == true){OPwgrMzUCk = false;}
      if(pXJVyOeVRF == true){pXJVyOeVRF = false;}
      if(HbVUsnRMGx == true){HbVUsnRMGx = false;}
      if(NMtjcmeQoz == true){NMtjcmeQoz = false;}
      if(MQkMMNuKXB == true){MQkMMNuKXB = false;}
      if(ynZIhltbmD == true){ynZIhltbmD = false;}
      if(tlOEWddZrL == true){tlOEWddZrL = false;}
      if(jNfSsqqJHf == true){jNfSsqqJHf = false;}
      if(sGoFzZllBp == true){sGoFzZllBp = false;}
      if(rDdlEaCfoi == true){rDdlEaCfoi = false;}
      if(jVRMQjIHPq == true){jVRMQjIHPq = false;}
      if(ujTHKmxJFx == true){ujTHKmxJFx = false;}
      if(qrXBSgjtNS == true){qrXBSgjtNS = false;}
      if(oKTYwXncnO == true){oKTYwXncnO = false;}
      if(QeVKuIiVaQ == true){QeVKuIiVaQ = false;}
      if(crarqqxQsi == true){crarqqxQsi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYJNMXPPGI
{ 
  void uGCTYRTSzk()
  { 
      bool XJHffpfPgR = false;
      bool rXDnDuAZaA = false;
      bool lgoUpgSuZr = false;
      bool fgIybfwmsN = false;
      bool tlcabidWMp = false;
      bool rgItAqUmoz = false;
      bool XkoolLOFMX = false;
      bool zMgMGADNsG = false;
      bool CwhjzyYOxj = false;
      bool KIyspIxnoP = false;
      bool UYJopezwnA = false;
      bool nGthxbCFom = false;
      bool mAHbMpOmVx = false;
      bool DOYclclrsT = false;
      bool zbaxwEOPuO = false;
      bool GqzBbTRhbA = false;
      bool QMZpxYgQuU = false;
      bool oJLUnKYKeI = false;
      bool ayrHqLPXAR = false;
      bool KEQsDmCjzX = false;
      string WFrbhoggbe;
      string PfUVAKIelp;
      string CDoPuSgDXw;
      string BukjNACuYm;
      string XWCtSfjJCk;
      string MWTUXSPcgO;
      string HcJfcUtjHz;
      string INGzSfAuwO;
      string hXBmidaQMt;
      string jZNJeuNWRy;
      string lzBCbzQUCr;
      string SUgRfjbVwy;
      string sdXNOiAwUX;
      string RccxciVyKj;
      string NGNUbPswct;
      string SqaSEIbnns;
      string zTzeZoqiox;
      string OcLLklPDkz;
      string pDTZEZCKsT;
      string HgKQksGitm;
      if(WFrbhoggbe == lzBCbzQUCr){XJHffpfPgR = true;}
      else if(lzBCbzQUCr == WFrbhoggbe){UYJopezwnA = true;}
      if(PfUVAKIelp == SUgRfjbVwy){rXDnDuAZaA = true;}
      else if(SUgRfjbVwy == PfUVAKIelp){nGthxbCFom = true;}
      if(CDoPuSgDXw == sdXNOiAwUX){lgoUpgSuZr = true;}
      else if(sdXNOiAwUX == CDoPuSgDXw){mAHbMpOmVx = true;}
      if(BukjNACuYm == RccxciVyKj){fgIybfwmsN = true;}
      else if(RccxciVyKj == BukjNACuYm){DOYclclrsT = true;}
      if(XWCtSfjJCk == NGNUbPswct){tlcabidWMp = true;}
      else if(NGNUbPswct == XWCtSfjJCk){zbaxwEOPuO = true;}
      if(MWTUXSPcgO == SqaSEIbnns){rgItAqUmoz = true;}
      else if(SqaSEIbnns == MWTUXSPcgO){GqzBbTRhbA = true;}
      if(HcJfcUtjHz == zTzeZoqiox){XkoolLOFMX = true;}
      else if(zTzeZoqiox == HcJfcUtjHz){QMZpxYgQuU = true;}
      if(INGzSfAuwO == OcLLklPDkz){zMgMGADNsG = true;}
      if(hXBmidaQMt == pDTZEZCKsT){CwhjzyYOxj = true;}
      if(jZNJeuNWRy == HgKQksGitm){KIyspIxnoP = true;}
      while(OcLLklPDkz == INGzSfAuwO){oJLUnKYKeI = true;}
      while(pDTZEZCKsT == pDTZEZCKsT){ayrHqLPXAR = true;}
      while(HgKQksGitm == HgKQksGitm){KEQsDmCjzX = true;}
      if(XJHffpfPgR == true){XJHffpfPgR = false;}
      if(rXDnDuAZaA == true){rXDnDuAZaA = false;}
      if(lgoUpgSuZr == true){lgoUpgSuZr = false;}
      if(fgIybfwmsN == true){fgIybfwmsN = false;}
      if(tlcabidWMp == true){tlcabidWMp = false;}
      if(rgItAqUmoz == true){rgItAqUmoz = false;}
      if(XkoolLOFMX == true){XkoolLOFMX = false;}
      if(zMgMGADNsG == true){zMgMGADNsG = false;}
      if(CwhjzyYOxj == true){CwhjzyYOxj = false;}
      if(KIyspIxnoP == true){KIyspIxnoP = false;}
      if(UYJopezwnA == true){UYJopezwnA = false;}
      if(nGthxbCFom == true){nGthxbCFom = false;}
      if(mAHbMpOmVx == true){mAHbMpOmVx = false;}
      if(DOYclclrsT == true){DOYclclrsT = false;}
      if(zbaxwEOPuO == true){zbaxwEOPuO = false;}
      if(GqzBbTRhbA == true){GqzBbTRhbA = false;}
      if(QMZpxYgQuU == true){QMZpxYgQuU = false;}
      if(oJLUnKYKeI == true){oJLUnKYKeI = false;}
      if(ayrHqLPXAR == true){ayrHqLPXAR = false;}
      if(KEQsDmCjzX == true){KEQsDmCjzX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUZUQKNOUW
{ 
  void iHxpyNrJHw()
  { 
      bool dMpFOzyNoF = false;
      bool qrxCDSmaoY = false;
      bool LiemCzHTdw = false;
      bool KCtnmWqpBF = false;
      bool pXVjlVFuFN = false;
      bool MeEqTuhDDP = false;
      bool rdjstoxJOf = false;
      bool awZiinNtBf = false;
      bool sLOPjfyDUr = false;
      bool onmkMLmbpx = false;
      bool YwfYmPFUHe = false;
      bool gnBWVfPUJN = false;
      bool psoWqmInVX = false;
      bool BkDEGxfocT = false;
      bool acwoKAlPOg = false;
      bool uSSbGfHJgz = false;
      bool GRzjdujxQY = false;
      bool AaqomMwzLq = false;
      bool AsYobhSbxa = false;
      bool oVHcMJdMKO = false;
      string oqBGspsJGW;
      string KFCDaZqVXJ;
      string sGnVkAhtjr;
      string IXeEUStLyy;
      string YaecXxpxRj;
      string UYznwiCeVs;
      string IyZONmZxiH;
      string feXYjRaLxm;
      string KjbAWjXqIk;
      string QOoEpaBQOk;
      string WrOKDpBaDd;
      string IqghhXVZqd;
      string OioxqQoSiJ;
      string QKwMQRURwg;
      string hxmdcYgHWR;
      string EbYkWmDRTm;
      string AiqtNxtUQQ;
      string CEcKuQuKTR;
      string ihwQFnlLpc;
      string ODxJgzFsPf;
      if(oqBGspsJGW == WrOKDpBaDd){dMpFOzyNoF = true;}
      else if(WrOKDpBaDd == oqBGspsJGW){YwfYmPFUHe = true;}
      if(KFCDaZqVXJ == IqghhXVZqd){qrxCDSmaoY = true;}
      else if(IqghhXVZqd == KFCDaZqVXJ){gnBWVfPUJN = true;}
      if(sGnVkAhtjr == OioxqQoSiJ){LiemCzHTdw = true;}
      else if(OioxqQoSiJ == sGnVkAhtjr){psoWqmInVX = true;}
      if(IXeEUStLyy == QKwMQRURwg){KCtnmWqpBF = true;}
      else if(QKwMQRURwg == IXeEUStLyy){BkDEGxfocT = true;}
      if(YaecXxpxRj == hxmdcYgHWR){pXVjlVFuFN = true;}
      else if(hxmdcYgHWR == YaecXxpxRj){acwoKAlPOg = true;}
      if(UYznwiCeVs == EbYkWmDRTm){MeEqTuhDDP = true;}
      else if(EbYkWmDRTm == UYznwiCeVs){uSSbGfHJgz = true;}
      if(IyZONmZxiH == AiqtNxtUQQ){rdjstoxJOf = true;}
      else if(AiqtNxtUQQ == IyZONmZxiH){GRzjdujxQY = true;}
      if(feXYjRaLxm == CEcKuQuKTR){awZiinNtBf = true;}
      if(KjbAWjXqIk == ihwQFnlLpc){sLOPjfyDUr = true;}
      if(QOoEpaBQOk == ODxJgzFsPf){onmkMLmbpx = true;}
      while(CEcKuQuKTR == feXYjRaLxm){AaqomMwzLq = true;}
      while(ihwQFnlLpc == ihwQFnlLpc){AsYobhSbxa = true;}
      while(ODxJgzFsPf == ODxJgzFsPf){oVHcMJdMKO = true;}
      if(dMpFOzyNoF == true){dMpFOzyNoF = false;}
      if(qrxCDSmaoY == true){qrxCDSmaoY = false;}
      if(LiemCzHTdw == true){LiemCzHTdw = false;}
      if(KCtnmWqpBF == true){KCtnmWqpBF = false;}
      if(pXVjlVFuFN == true){pXVjlVFuFN = false;}
      if(MeEqTuhDDP == true){MeEqTuhDDP = false;}
      if(rdjstoxJOf == true){rdjstoxJOf = false;}
      if(awZiinNtBf == true){awZiinNtBf = false;}
      if(sLOPjfyDUr == true){sLOPjfyDUr = false;}
      if(onmkMLmbpx == true){onmkMLmbpx = false;}
      if(YwfYmPFUHe == true){YwfYmPFUHe = false;}
      if(gnBWVfPUJN == true){gnBWVfPUJN = false;}
      if(psoWqmInVX == true){psoWqmInVX = false;}
      if(BkDEGxfocT == true){BkDEGxfocT = false;}
      if(acwoKAlPOg == true){acwoKAlPOg = false;}
      if(uSSbGfHJgz == true){uSSbGfHJgz = false;}
      if(GRzjdujxQY == true){GRzjdujxQY = false;}
      if(AaqomMwzLq == true){AaqomMwzLq = false;}
      if(AsYobhSbxa == true){AsYobhSbxa = false;}
      if(oVHcMJdMKO == true){oVHcMJdMKO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGJJYMZJZG
{ 
  void pOnEesuFik()
  { 
      bool HeVazhAZno = false;
      bool kWTmGGSAzL = false;
      bool GBmcOcFhuo = false;
      bool tIgcpNnQzX = false;
      bool MeiRnkLPsy = false;
      bool XRleuGqsMV = false;
      bool bSdzucoqxs = false;
      bool RCBbzaRUnc = false;
      bool RpnwRcWBgj = false;
      bool VuDdusAjWL = false;
      bool uUSAgVQJfT = false;
      bool nWEiDkdhgR = false;
      bool FmJMXVyWgF = false;
      bool ahycgxXnOw = false;
      bool MMVNuzpUZJ = false;
      bool OSDEFIKFcK = false;
      bool WscZsFYbBG = false;
      bool NpSjFsRwRY = false;
      bool fdxWpHesWY = false;
      bool lSLDYTjwTo = false;
      string ngUHKSCnoq;
      string oMnSmXjAJb;
      string gVWZYwJAks;
      string MkgPWIYRlF;
      string qUsejzInuQ;
      string UMLmfSJtiN;
      string JCCweEfXwd;
      string ySNDkMbroZ;
      string nVFTYzZsiD;
      string yehXwnRxAf;
      string SjqQSBzHCT;
      string pREJZmxiWf;
      string dlnreSjoHw;
      string uerJGDdnAW;
      string zRqPNgZYxI;
      string qhZTBfuykz;
      string RJzFXLYuCW;
      string IIhAfMuYey;
      string rKqzFMEXHZ;
      string HeCAFpRlqC;
      if(ngUHKSCnoq == SjqQSBzHCT){HeVazhAZno = true;}
      else if(SjqQSBzHCT == ngUHKSCnoq){uUSAgVQJfT = true;}
      if(oMnSmXjAJb == pREJZmxiWf){kWTmGGSAzL = true;}
      else if(pREJZmxiWf == oMnSmXjAJb){nWEiDkdhgR = true;}
      if(gVWZYwJAks == dlnreSjoHw){GBmcOcFhuo = true;}
      else if(dlnreSjoHw == gVWZYwJAks){FmJMXVyWgF = true;}
      if(MkgPWIYRlF == uerJGDdnAW){tIgcpNnQzX = true;}
      else if(uerJGDdnAW == MkgPWIYRlF){ahycgxXnOw = true;}
      if(qUsejzInuQ == zRqPNgZYxI){MeiRnkLPsy = true;}
      else if(zRqPNgZYxI == qUsejzInuQ){MMVNuzpUZJ = true;}
      if(UMLmfSJtiN == qhZTBfuykz){XRleuGqsMV = true;}
      else if(qhZTBfuykz == UMLmfSJtiN){OSDEFIKFcK = true;}
      if(JCCweEfXwd == RJzFXLYuCW){bSdzucoqxs = true;}
      else if(RJzFXLYuCW == JCCweEfXwd){WscZsFYbBG = true;}
      if(ySNDkMbroZ == IIhAfMuYey){RCBbzaRUnc = true;}
      if(nVFTYzZsiD == rKqzFMEXHZ){RpnwRcWBgj = true;}
      if(yehXwnRxAf == HeCAFpRlqC){VuDdusAjWL = true;}
      while(IIhAfMuYey == ySNDkMbroZ){NpSjFsRwRY = true;}
      while(rKqzFMEXHZ == rKqzFMEXHZ){fdxWpHesWY = true;}
      while(HeCAFpRlqC == HeCAFpRlqC){lSLDYTjwTo = true;}
      if(HeVazhAZno == true){HeVazhAZno = false;}
      if(kWTmGGSAzL == true){kWTmGGSAzL = false;}
      if(GBmcOcFhuo == true){GBmcOcFhuo = false;}
      if(tIgcpNnQzX == true){tIgcpNnQzX = false;}
      if(MeiRnkLPsy == true){MeiRnkLPsy = false;}
      if(XRleuGqsMV == true){XRleuGqsMV = false;}
      if(bSdzucoqxs == true){bSdzucoqxs = false;}
      if(RCBbzaRUnc == true){RCBbzaRUnc = false;}
      if(RpnwRcWBgj == true){RpnwRcWBgj = false;}
      if(VuDdusAjWL == true){VuDdusAjWL = false;}
      if(uUSAgVQJfT == true){uUSAgVQJfT = false;}
      if(nWEiDkdhgR == true){nWEiDkdhgR = false;}
      if(FmJMXVyWgF == true){FmJMXVyWgF = false;}
      if(ahycgxXnOw == true){ahycgxXnOw = false;}
      if(MMVNuzpUZJ == true){MMVNuzpUZJ = false;}
      if(OSDEFIKFcK == true){OSDEFIKFcK = false;}
      if(WscZsFYbBG == true){WscZsFYbBG = false;}
      if(NpSjFsRwRY == true){NpSjFsRwRY = false;}
      if(fdxWpHesWY == true){fdxWpHesWY = false;}
      if(lSLDYTjwTo == true){lSLDYTjwTo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPVNFUIWOE
{ 
  void VOqZereYAa()
  { 
      bool WAftTBfKZw = false;
      bool QPQIesgRbw = false;
      bool sWVKOCjTtR = false;
      bool ZqJmYLrCTb = false;
      bool oIXfBegbWg = false;
      bool JPxGIzdVeR = false;
      bool QMQHWZGcjS = false;
      bool BeyzHjzpJj = false;
      bool VIwMIKsCeY = false;
      bool gVWBLbrPIa = false;
      bool YDqDfeRyzX = false;
      bool AnMuwIPDzM = false;
      bool fDxLkeHwne = false;
      bool righKRQsfc = false;
      bool rtDHXsJbFC = false;
      bool LnPwtUFfRA = false;
      bool XVKTeRHejd = false;
      bool qWWWTlzpnr = false;
      bool VfpkSESjmo = false;
      bool LkafFWjjbG = false;
      string CAXmIMAAPz;
      string YDmMhZCoLF;
      string SuxPjqyInI;
      string RiXrhyklCi;
      string YdAxlIHmaq;
      string QQlmfHCHCR;
      string NqLGgofudi;
      string nQlbgotzca;
      string jLgwrBwkMa;
      string ucikVgRtQw;
      string cLIrCzeKFp;
      string MDeagCKPNf;
      string suiDmKgAGA;
      string XzhfyXCoss;
      string VleVNryIDS;
      string WCfjDgcFEq;
      string RdEFSMUybJ;
      string zUVUJHQMou;
      string MYwmdVTybR;
      string uxkCaqgZDB;
      if(CAXmIMAAPz == cLIrCzeKFp){WAftTBfKZw = true;}
      else if(cLIrCzeKFp == CAXmIMAAPz){YDqDfeRyzX = true;}
      if(YDmMhZCoLF == MDeagCKPNf){QPQIesgRbw = true;}
      else if(MDeagCKPNf == YDmMhZCoLF){AnMuwIPDzM = true;}
      if(SuxPjqyInI == suiDmKgAGA){sWVKOCjTtR = true;}
      else if(suiDmKgAGA == SuxPjqyInI){fDxLkeHwne = true;}
      if(RiXrhyklCi == XzhfyXCoss){ZqJmYLrCTb = true;}
      else if(XzhfyXCoss == RiXrhyklCi){righKRQsfc = true;}
      if(YdAxlIHmaq == VleVNryIDS){oIXfBegbWg = true;}
      else if(VleVNryIDS == YdAxlIHmaq){rtDHXsJbFC = true;}
      if(QQlmfHCHCR == WCfjDgcFEq){JPxGIzdVeR = true;}
      else if(WCfjDgcFEq == QQlmfHCHCR){LnPwtUFfRA = true;}
      if(NqLGgofudi == RdEFSMUybJ){QMQHWZGcjS = true;}
      else if(RdEFSMUybJ == NqLGgofudi){XVKTeRHejd = true;}
      if(nQlbgotzca == zUVUJHQMou){BeyzHjzpJj = true;}
      if(jLgwrBwkMa == MYwmdVTybR){VIwMIKsCeY = true;}
      if(ucikVgRtQw == uxkCaqgZDB){gVWBLbrPIa = true;}
      while(zUVUJHQMou == nQlbgotzca){qWWWTlzpnr = true;}
      while(MYwmdVTybR == MYwmdVTybR){VfpkSESjmo = true;}
      while(uxkCaqgZDB == uxkCaqgZDB){LkafFWjjbG = true;}
      if(WAftTBfKZw == true){WAftTBfKZw = false;}
      if(QPQIesgRbw == true){QPQIesgRbw = false;}
      if(sWVKOCjTtR == true){sWVKOCjTtR = false;}
      if(ZqJmYLrCTb == true){ZqJmYLrCTb = false;}
      if(oIXfBegbWg == true){oIXfBegbWg = false;}
      if(JPxGIzdVeR == true){JPxGIzdVeR = false;}
      if(QMQHWZGcjS == true){QMQHWZGcjS = false;}
      if(BeyzHjzpJj == true){BeyzHjzpJj = false;}
      if(VIwMIKsCeY == true){VIwMIKsCeY = false;}
      if(gVWBLbrPIa == true){gVWBLbrPIa = false;}
      if(YDqDfeRyzX == true){YDqDfeRyzX = false;}
      if(AnMuwIPDzM == true){AnMuwIPDzM = false;}
      if(fDxLkeHwne == true){fDxLkeHwne = false;}
      if(righKRQsfc == true){righKRQsfc = false;}
      if(rtDHXsJbFC == true){rtDHXsJbFC = false;}
      if(LnPwtUFfRA == true){LnPwtUFfRA = false;}
      if(XVKTeRHejd == true){XVKTeRHejd = false;}
      if(qWWWTlzpnr == true){qWWWTlzpnr = false;}
      if(VfpkSESjmo == true){VfpkSESjmo = false;}
      if(LkafFWjjbG == true){LkafFWjjbG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGHXGNFEVG
{ 
  void WyCAaSrMwZ()
  { 
      bool SXhEyYBFkS = false;
      bool VRbQurMmEW = false;
      bool kKrLBTctJO = false;
      bool pctTgwlUTo = false;
      bool HfhkWsZOYd = false;
      bool lNGaDIeVCd = false;
      bool uGwVbsWIiz = false;
      bool FqSPPFbGoH = false;
      bool sOVfccVTPY = false;
      bool QPRosAiLId = false;
      bool VRfZXttqKy = false;
      bool fYgtkgkPrz = false;
      bool XDrKhpZcVO = false;
      bool VQxLlaiwIi = false;
      bool hdIQrriWEM = false;
      bool PSTJGRYUqh = false;
      bool UQVucPaVIJ = false;
      bool ynHJRsuaRp = false;
      bool GCYJzCwnET = false;
      bool BNEZNQIMnb = false;
      string pdpRTZXmhl;
      string oJZroSoXqh;
      string kcTObjYKDV;
      string bytWRBDlhc;
      string zyJFwtifBR;
      string VQDypMJapi;
      string BNjMJqPCZn;
      string PCoNhlTOSh;
      string BrIkALuugF;
      string qbuzblOxwF;
      string dfFNCSbpPD;
      string suIIhIEyMx;
      string uTVUwmGpkw;
      string XWRMDUmuig;
      string jEecLwSmQT;
      string hPkyJKJkQO;
      string LkETeWcuFM;
      string VIOeNpnrIA;
      string TTYROIkSDs;
      string KCeTVyALyo;
      if(pdpRTZXmhl == dfFNCSbpPD){SXhEyYBFkS = true;}
      else if(dfFNCSbpPD == pdpRTZXmhl){VRfZXttqKy = true;}
      if(oJZroSoXqh == suIIhIEyMx){VRbQurMmEW = true;}
      else if(suIIhIEyMx == oJZroSoXqh){fYgtkgkPrz = true;}
      if(kcTObjYKDV == uTVUwmGpkw){kKrLBTctJO = true;}
      else if(uTVUwmGpkw == kcTObjYKDV){XDrKhpZcVO = true;}
      if(bytWRBDlhc == XWRMDUmuig){pctTgwlUTo = true;}
      else if(XWRMDUmuig == bytWRBDlhc){VQxLlaiwIi = true;}
      if(zyJFwtifBR == jEecLwSmQT){HfhkWsZOYd = true;}
      else if(jEecLwSmQT == zyJFwtifBR){hdIQrriWEM = true;}
      if(VQDypMJapi == hPkyJKJkQO){lNGaDIeVCd = true;}
      else if(hPkyJKJkQO == VQDypMJapi){PSTJGRYUqh = true;}
      if(BNjMJqPCZn == LkETeWcuFM){uGwVbsWIiz = true;}
      else if(LkETeWcuFM == BNjMJqPCZn){UQVucPaVIJ = true;}
      if(PCoNhlTOSh == VIOeNpnrIA){FqSPPFbGoH = true;}
      if(BrIkALuugF == TTYROIkSDs){sOVfccVTPY = true;}
      if(qbuzblOxwF == KCeTVyALyo){QPRosAiLId = true;}
      while(VIOeNpnrIA == PCoNhlTOSh){ynHJRsuaRp = true;}
      while(TTYROIkSDs == TTYROIkSDs){GCYJzCwnET = true;}
      while(KCeTVyALyo == KCeTVyALyo){BNEZNQIMnb = true;}
      if(SXhEyYBFkS == true){SXhEyYBFkS = false;}
      if(VRbQurMmEW == true){VRbQurMmEW = false;}
      if(kKrLBTctJO == true){kKrLBTctJO = false;}
      if(pctTgwlUTo == true){pctTgwlUTo = false;}
      if(HfhkWsZOYd == true){HfhkWsZOYd = false;}
      if(lNGaDIeVCd == true){lNGaDIeVCd = false;}
      if(uGwVbsWIiz == true){uGwVbsWIiz = false;}
      if(FqSPPFbGoH == true){FqSPPFbGoH = false;}
      if(sOVfccVTPY == true){sOVfccVTPY = false;}
      if(QPRosAiLId == true){QPRosAiLId = false;}
      if(VRfZXttqKy == true){VRfZXttqKy = false;}
      if(fYgtkgkPrz == true){fYgtkgkPrz = false;}
      if(XDrKhpZcVO == true){XDrKhpZcVO = false;}
      if(VQxLlaiwIi == true){VQxLlaiwIi = false;}
      if(hdIQrriWEM == true){hdIQrriWEM = false;}
      if(PSTJGRYUqh == true){PSTJGRYUqh = false;}
      if(UQVucPaVIJ == true){UQVucPaVIJ = false;}
      if(ynHJRsuaRp == true){ynHJRsuaRp = false;}
      if(GCYJzCwnET == true){GCYJzCwnET = false;}
      if(BNEZNQIMnb == true){BNEZNQIMnb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWABLCILHS
{ 
  void qQghwLmCoW()
  { 
      bool MkOjQzrknt = false;
      bool iRmPpeiBFf = false;
      bool MaMLIqtHPm = false;
      bool azCDurSgAb = false;
      bool dPZRiWhyxL = false;
      bool pfelrlXCbZ = false;
      bool EkUBTjPjUy = false;
      bool LBAdBwBubk = false;
      bool IwKEwtTQLJ = false;
      bool TPFZWsuXxz = false;
      bool HydyzoeBju = false;
      bool jcZqQIZQEY = false;
      bool PyXKdwwaGH = false;
      bool BcxccJRLEH = false;
      bool ORfPYqoOJN = false;
      bool TdTYiJZSUD = false;
      bool sEuctHexNG = false;
      bool pNMxKxRIlm = false;
      bool GhRrnWJYsT = false;
      bool jzqBNJWDUQ = false;
      string nIYljXfhJs;
      string sbZTYGSrZK;
      string OpCHOGHPNL;
      string fYpAVKRhkX;
      string ULxAfGBTux;
      string WGNGRyGRXd;
      string QPTxMTkYyN;
      string ojGBoDrCbH;
      string EmTQoZLiiX;
      string EAJHHEqAmL;
      string UcVgIlzLRO;
      string FDoQZdwDIl;
      string IBoZJnaztj;
      string LrOPlbQlHC;
      string ZzRURBKshc;
      string InqBDTmuXT;
      string LARgDNnZex;
      string MJuGMIjUIH;
      string cgRQaWBNMS;
      string oVOmpYhkRE;
      if(nIYljXfhJs == UcVgIlzLRO){MkOjQzrknt = true;}
      else if(UcVgIlzLRO == nIYljXfhJs){HydyzoeBju = true;}
      if(sbZTYGSrZK == FDoQZdwDIl){iRmPpeiBFf = true;}
      else if(FDoQZdwDIl == sbZTYGSrZK){jcZqQIZQEY = true;}
      if(OpCHOGHPNL == IBoZJnaztj){MaMLIqtHPm = true;}
      else if(IBoZJnaztj == OpCHOGHPNL){PyXKdwwaGH = true;}
      if(fYpAVKRhkX == LrOPlbQlHC){azCDurSgAb = true;}
      else if(LrOPlbQlHC == fYpAVKRhkX){BcxccJRLEH = true;}
      if(ULxAfGBTux == ZzRURBKshc){dPZRiWhyxL = true;}
      else if(ZzRURBKshc == ULxAfGBTux){ORfPYqoOJN = true;}
      if(WGNGRyGRXd == InqBDTmuXT){pfelrlXCbZ = true;}
      else if(InqBDTmuXT == WGNGRyGRXd){TdTYiJZSUD = true;}
      if(QPTxMTkYyN == LARgDNnZex){EkUBTjPjUy = true;}
      else if(LARgDNnZex == QPTxMTkYyN){sEuctHexNG = true;}
      if(ojGBoDrCbH == MJuGMIjUIH){LBAdBwBubk = true;}
      if(EmTQoZLiiX == cgRQaWBNMS){IwKEwtTQLJ = true;}
      if(EAJHHEqAmL == oVOmpYhkRE){TPFZWsuXxz = true;}
      while(MJuGMIjUIH == ojGBoDrCbH){pNMxKxRIlm = true;}
      while(cgRQaWBNMS == cgRQaWBNMS){GhRrnWJYsT = true;}
      while(oVOmpYhkRE == oVOmpYhkRE){jzqBNJWDUQ = true;}
      if(MkOjQzrknt == true){MkOjQzrknt = false;}
      if(iRmPpeiBFf == true){iRmPpeiBFf = false;}
      if(MaMLIqtHPm == true){MaMLIqtHPm = false;}
      if(azCDurSgAb == true){azCDurSgAb = false;}
      if(dPZRiWhyxL == true){dPZRiWhyxL = false;}
      if(pfelrlXCbZ == true){pfelrlXCbZ = false;}
      if(EkUBTjPjUy == true){EkUBTjPjUy = false;}
      if(LBAdBwBubk == true){LBAdBwBubk = false;}
      if(IwKEwtTQLJ == true){IwKEwtTQLJ = false;}
      if(TPFZWsuXxz == true){TPFZWsuXxz = false;}
      if(HydyzoeBju == true){HydyzoeBju = false;}
      if(jcZqQIZQEY == true){jcZqQIZQEY = false;}
      if(PyXKdwwaGH == true){PyXKdwwaGH = false;}
      if(BcxccJRLEH == true){BcxccJRLEH = false;}
      if(ORfPYqoOJN == true){ORfPYqoOJN = false;}
      if(TdTYiJZSUD == true){TdTYiJZSUD = false;}
      if(sEuctHexNG == true){sEuctHexNG = false;}
      if(pNMxKxRIlm == true){pNMxKxRIlm = false;}
      if(GhRrnWJYsT == true){GhRrnWJYsT = false;}
      if(jzqBNJWDUQ == true){jzqBNJWDUQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEDWZGGVHE
{ 
  void FUnTVRkcpk()
  { 
      bool GXbUeMVdsK = false;
      bool YMrtQHQjHL = false;
      bool bwIdpPwFby = false;
      bool VUIXRenUHE = false;
      bool oodisZisVS = false;
      bool yYiNcKPydP = false;
      bool PQBunEDTbk = false;
      bool SwbDVmRZjP = false;
      bool gDjJzxkttH = false;
      bool PpprnYmito = false;
      bool VOQjzBwfqp = false;
      bool soNOiMfrup = false;
      bool SJYUVcFjOx = false;
      bool zheusRlzJx = false;
      bool BECENZbbJa = false;
      bool rtnDVMouOW = false;
      bool wMRtpKKSUQ = false;
      bool afhxoNGUGu = false;
      bool BdanEFtaYg = false;
      bool cpkmBomIOD = false;
      string MZlScBguHB;
      string jLGAOdCWGB;
      string BhINDJTQsq;
      string DKjeaplnbo;
      string COynamBYqo;
      string cnxjjeRYPS;
      string gPCPyYaaZX;
      string qOuQzliTlP;
      string IuZDNONAuu;
      string XNYIHlMipC;
      string LaySxOsfkx;
      string uxlzKlpyBi;
      string LafdzdpmIM;
      string ZAdjDhwGGz;
      string VgOxAaaYxV;
      string wOgGpkuUTT;
      string YGXXXuTCwc;
      string pirCNeLhcY;
      string DQomQLSXtS;
      string mamlZPIqZF;
      if(MZlScBguHB == LaySxOsfkx){GXbUeMVdsK = true;}
      else if(LaySxOsfkx == MZlScBguHB){VOQjzBwfqp = true;}
      if(jLGAOdCWGB == uxlzKlpyBi){YMrtQHQjHL = true;}
      else if(uxlzKlpyBi == jLGAOdCWGB){soNOiMfrup = true;}
      if(BhINDJTQsq == LafdzdpmIM){bwIdpPwFby = true;}
      else if(LafdzdpmIM == BhINDJTQsq){SJYUVcFjOx = true;}
      if(DKjeaplnbo == ZAdjDhwGGz){VUIXRenUHE = true;}
      else if(ZAdjDhwGGz == DKjeaplnbo){zheusRlzJx = true;}
      if(COynamBYqo == VgOxAaaYxV){oodisZisVS = true;}
      else if(VgOxAaaYxV == COynamBYqo){BECENZbbJa = true;}
      if(cnxjjeRYPS == wOgGpkuUTT){yYiNcKPydP = true;}
      else if(wOgGpkuUTT == cnxjjeRYPS){rtnDVMouOW = true;}
      if(gPCPyYaaZX == YGXXXuTCwc){PQBunEDTbk = true;}
      else if(YGXXXuTCwc == gPCPyYaaZX){wMRtpKKSUQ = true;}
      if(qOuQzliTlP == pirCNeLhcY){SwbDVmRZjP = true;}
      if(IuZDNONAuu == DQomQLSXtS){gDjJzxkttH = true;}
      if(XNYIHlMipC == mamlZPIqZF){PpprnYmito = true;}
      while(pirCNeLhcY == qOuQzliTlP){afhxoNGUGu = true;}
      while(DQomQLSXtS == DQomQLSXtS){BdanEFtaYg = true;}
      while(mamlZPIqZF == mamlZPIqZF){cpkmBomIOD = true;}
      if(GXbUeMVdsK == true){GXbUeMVdsK = false;}
      if(YMrtQHQjHL == true){YMrtQHQjHL = false;}
      if(bwIdpPwFby == true){bwIdpPwFby = false;}
      if(VUIXRenUHE == true){VUIXRenUHE = false;}
      if(oodisZisVS == true){oodisZisVS = false;}
      if(yYiNcKPydP == true){yYiNcKPydP = false;}
      if(PQBunEDTbk == true){PQBunEDTbk = false;}
      if(SwbDVmRZjP == true){SwbDVmRZjP = false;}
      if(gDjJzxkttH == true){gDjJzxkttH = false;}
      if(PpprnYmito == true){PpprnYmito = false;}
      if(VOQjzBwfqp == true){VOQjzBwfqp = false;}
      if(soNOiMfrup == true){soNOiMfrup = false;}
      if(SJYUVcFjOx == true){SJYUVcFjOx = false;}
      if(zheusRlzJx == true){zheusRlzJx = false;}
      if(BECENZbbJa == true){BECENZbbJa = false;}
      if(rtnDVMouOW == true){rtnDVMouOW = false;}
      if(wMRtpKKSUQ == true){wMRtpKKSUQ = false;}
      if(afhxoNGUGu == true){afhxoNGUGu = false;}
      if(BdanEFtaYg == true){BdanEFtaYg = false;}
      if(cpkmBomIOD == true){cpkmBomIOD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZLMWENWTM
{ 
  void VKmLsDILxq()
  { 
      bool qiZMZTJeLE = false;
      bool HchkcWFYZW = false;
      bool PmCqkIFwZe = false;
      bool efrTyaCkaC = false;
      bool LOkCAHKSNq = false;
      bool ctpQqDfiaQ = false;
      bool ONFfYbkNmB = false;
      bool UTyXKBCApd = false;
      bool ylhhCjpabt = false;
      bool tSKJnxIFcY = false;
      bool VweLVIwSGp = false;
      bool BesxSbeWco = false;
      bool lKlsHBIniN = false;
      bool rwXQHBHVMs = false;
      bool nXUlsOZNpL = false;
      bool RkbnlLKlET = false;
      bool zHiryEHboR = false;
      bool TJKjAOpzzr = false;
      bool auyWuGUidu = false;
      bool qURrsgnbno = false;
      string dkBeMlWyWK;
      string kfhdcrKIku;
      string ZWlguiiLRF;
      string oASfwefVbg;
      string dsmsdXVgoA;
      string pRGMpHyUjc;
      string DLgRVkMBgx;
      string MnfERfirCW;
      string NBVQPWtGpo;
      string gKlycRMVXs;
      string KTAqnBkBtK;
      string XFSMPCoPBz;
      string qGLrQBBgbz;
      string SNUIMsAecN;
      string lrLfQarZia;
      string cxTYCDIIal;
      string zDYurJjJzV;
      string BJmnNyufao;
      string JbyAVVtwGI;
      string krEpOhSPmG;
      if(dkBeMlWyWK == KTAqnBkBtK){qiZMZTJeLE = true;}
      else if(KTAqnBkBtK == dkBeMlWyWK){VweLVIwSGp = true;}
      if(kfhdcrKIku == XFSMPCoPBz){HchkcWFYZW = true;}
      else if(XFSMPCoPBz == kfhdcrKIku){BesxSbeWco = true;}
      if(ZWlguiiLRF == qGLrQBBgbz){PmCqkIFwZe = true;}
      else if(qGLrQBBgbz == ZWlguiiLRF){lKlsHBIniN = true;}
      if(oASfwefVbg == SNUIMsAecN){efrTyaCkaC = true;}
      else if(SNUIMsAecN == oASfwefVbg){rwXQHBHVMs = true;}
      if(dsmsdXVgoA == lrLfQarZia){LOkCAHKSNq = true;}
      else if(lrLfQarZia == dsmsdXVgoA){nXUlsOZNpL = true;}
      if(pRGMpHyUjc == cxTYCDIIal){ctpQqDfiaQ = true;}
      else if(cxTYCDIIal == pRGMpHyUjc){RkbnlLKlET = true;}
      if(DLgRVkMBgx == zDYurJjJzV){ONFfYbkNmB = true;}
      else if(zDYurJjJzV == DLgRVkMBgx){zHiryEHboR = true;}
      if(MnfERfirCW == BJmnNyufao){UTyXKBCApd = true;}
      if(NBVQPWtGpo == JbyAVVtwGI){ylhhCjpabt = true;}
      if(gKlycRMVXs == krEpOhSPmG){tSKJnxIFcY = true;}
      while(BJmnNyufao == MnfERfirCW){TJKjAOpzzr = true;}
      while(JbyAVVtwGI == JbyAVVtwGI){auyWuGUidu = true;}
      while(krEpOhSPmG == krEpOhSPmG){qURrsgnbno = true;}
      if(qiZMZTJeLE == true){qiZMZTJeLE = false;}
      if(HchkcWFYZW == true){HchkcWFYZW = false;}
      if(PmCqkIFwZe == true){PmCqkIFwZe = false;}
      if(efrTyaCkaC == true){efrTyaCkaC = false;}
      if(LOkCAHKSNq == true){LOkCAHKSNq = false;}
      if(ctpQqDfiaQ == true){ctpQqDfiaQ = false;}
      if(ONFfYbkNmB == true){ONFfYbkNmB = false;}
      if(UTyXKBCApd == true){UTyXKBCApd = false;}
      if(ylhhCjpabt == true){ylhhCjpabt = false;}
      if(tSKJnxIFcY == true){tSKJnxIFcY = false;}
      if(VweLVIwSGp == true){VweLVIwSGp = false;}
      if(BesxSbeWco == true){BesxSbeWco = false;}
      if(lKlsHBIniN == true){lKlsHBIniN = false;}
      if(rwXQHBHVMs == true){rwXQHBHVMs = false;}
      if(nXUlsOZNpL == true){nXUlsOZNpL = false;}
      if(RkbnlLKlET == true){RkbnlLKlET = false;}
      if(zHiryEHboR == true){zHiryEHboR = false;}
      if(TJKjAOpzzr == true){TJKjAOpzzr = false;}
      if(auyWuGUidu == true){auyWuGUidu = false;}
      if(qURrsgnbno == true){qURrsgnbno = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTIIHTVXVT
{ 
  void BmpegQVAMa()
  { 
      bool ScyzIrLAIe = false;
      bool kuGqrOxOIb = false;
      bool ZelbmlWRGk = false;
      bool jEdtcmNxlT = false;
      bool gzkxrfHFFz = false;
      bool TAdPYmpWMV = false;
      bool VssXufRLOF = false;
      bool BAcnuatoiG = false;
      bool eQMHQjaNVo = false;
      bool wqjPxmFMCL = false;
      bool OuqzyTXoUx = false;
      bool rAmFqEflHL = false;
      bool FDpYIKQMpH = false;
      bool UhmWrjZMIw = false;
      bool LlsYwwDdYs = false;
      bool GTFqGLESqn = false;
      bool DKyMbKNPNG = false;
      bool eTcKzTJRbL = false;
      bool GlnxABbwQg = false;
      bool eGVUsBmfwl = false;
      string aAIBGrOsoj;
      string uldLqPmpEZ;
      string AapaINsxEz;
      string ChmAWgtILZ;
      string hkWJQaZJlj;
      string TitkCAKgss;
      string zQophMzdoK;
      string UddeqODfKg;
      string miLTeSnByV;
      string VNPSZRugaD;
      string awTaOoFOtm;
      string wdVLFPEUKP;
      string YyfTnHOKEY;
      string SVEHGqOjFo;
      string MYGKYrqDNJ;
      string MaVLecPAmH;
      string atJUTZYOFN;
      string ATPVCzqUtw;
      string PLxuMrzsbd;
      string aNxxORPlqz;
      if(aAIBGrOsoj == awTaOoFOtm){ScyzIrLAIe = true;}
      else if(awTaOoFOtm == aAIBGrOsoj){OuqzyTXoUx = true;}
      if(uldLqPmpEZ == wdVLFPEUKP){kuGqrOxOIb = true;}
      else if(wdVLFPEUKP == uldLqPmpEZ){rAmFqEflHL = true;}
      if(AapaINsxEz == YyfTnHOKEY){ZelbmlWRGk = true;}
      else if(YyfTnHOKEY == AapaINsxEz){FDpYIKQMpH = true;}
      if(ChmAWgtILZ == SVEHGqOjFo){jEdtcmNxlT = true;}
      else if(SVEHGqOjFo == ChmAWgtILZ){UhmWrjZMIw = true;}
      if(hkWJQaZJlj == MYGKYrqDNJ){gzkxrfHFFz = true;}
      else if(MYGKYrqDNJ == hkWJQaZJlj){LlsYwwDdYs = true;}
      if(TitkCAKgss == MaVLecPAmH){TAdPYmpWMV = true;}
      else if(MaVLecPAmH == TitkCAKgss){GTFqGLESqn = true;}
      if(zQophMzdoK == atJUTZYOFN){VssXufRLOF = true;}
      else if(atJUTZYOFN == zQophMzdoK){DKyMbKNPNG = true;}
      if(UddeqODfKg == ATPVCzqUtw){BAcnuatoiG = true;}
      if(miLTeSnByV == PLxuMrzsbd){eQMHQjaNVo = true;}
      if(VNPSZRugaD == aNxxORPlqz){wqjPxmFMCL = true;}
      while(ATPVCzqUtw == UddeqODfKg){eTcKzTJRbL = true;}
      while(PLxuMrzsbd == PLxuMrzsbd){GlnxABbwQg = true;}
      while(aNxxORPlqz == aNxxORPlqz){eGVUsBmfwl = true;}
      if(ScyzIrLAIe == true){ScyzIrLAIe = false;}
      if(kuGqrOxOIb == true){kuGqrOxOIb = false;}
      if(ZelbmlWRGk == true){ZelbmlWRGk = false;}
      if(jEdtcmNxlT == true){jEdtcmNxlT = false;}
      if(gzkxrfHFFz == true){gzkxrfHFFz = false;}
      if(TAdPYmpWMV == true){TAdPYmpWMV = false;}
      if(VssXufRLOF == true){VssXufRLOF = false;}
      if(BAcnuatoiG == true){BAcnuatoiG = false;}
      if(eQMHQjaNVo == true){eQMHQjaNVo = false;}
      if(wqjPxmFMCL == true){wqjPxmFMCL = false;}
      if(OuqzyTXoUx == true){OuqzyTXoUx = false;}
      if(rAmFqEflHL == true){rAmFqEflHL = false;}
      if(FDpYIKQMpH == true){FDpYIKQMpH = false;}
      if(UhmWrjZMIw == true){UhmWrjZMIw = false;}
      if(LlsYwwDdYs == true){LlsYwwDdYs = false;}
      if(GTFqGLESqn == true){GTFqGLESqn = false;}
      if(DKyMbKNPNG == true){DKyMbKNPNG = false;}
      if(eTcKzTJRbL == true){eTcKzTJRbL = false;}
      if(GlnxABbwQg == true){GlnxABbwQg = false;}
      if(eGVUsBmfwl == true){eGVUsBmfwl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UITNXMQABG
{ 
  void mpcjHEJKgs()
  { 
      bool zhhesPBfBc = false;
      bool MKeOpdZzeX = false;
      bool ouHHDsBcGE = false;
      bool KNZeVRQamf = false;
      bool fitLkAXLKb = false;
      bool dMdsgEZabA = false;
      bool NYZxRzkzsY = false;
      bool MyMyqGAwVC = false;
      bool UpRdayjgxR = false;
      bool qpzmRHIxsl = false;
      bool PXRlPeAeBa = false;
      bool DcEZeXGuVT = false;
      bool ODCbhWzYgj = false;
      bool xDDjlwXfOw = false;
      bool xFeWNNkYIt = false;
      bool ANaYWLVpEr = false;
      bool eaxQdzZUmh = false;
      bool zafZVJYeNT = false;
      bool kaQljjcdMa = false;
      bool agbWQWHNrO = false;
      string NgSWPCtIlm;
      string CdcXtyAIun;
      string twZdNFYBak;
      string araWFuEkiB;
      string WgtPZqXctO;
      string hHxdfQHnJK;
      string csgBLKCFSz;
      string tPZtQMCJDV;
      string guGMDSuwpo;
      string mPbXXdArDP;
      string oRKuURhCNS;
      string NxjmdhlUys;
      string PFPcLenBWm;
      string MJGngOkKqk;
      string jriXapentp;
      string qetKAiCgjp;
      string dgfaFEqwFO;
      string wbdNIWVrCU;
      string zzGfuhPwny;
      string LDZBGDMIRW;
      if(NgSWPCtIlm == oRKuURhCNS){zhhesPBfBc = true;}
      else if(oRKuURhCNS == NgSWPCtIlm){PXRlPeAeBa = true;}
      if(CdcXtyAIun == NxjmdhlUys){MKeOpdZzeX = true;}
      else if(NxjmdhlUys == CdcXtyAIun){DcEZeXGuVT = true;}
      if(twZdNFYBak == PFPcLenBWm){ouHHDsBcGE = true;}
      else if(PFPcLenBWm == twZdNFYBak){ODCbhWzYgj = true;}
      if(araWFuEkiB == MJGngOkKqk){KNZeVRQamf = true;}
      else if(MJGngOkKqk == araWFuEkiB){xDDjlwXfOw = true;}
      if(WgtPZqXctO == jriXapentp){fitLkAXLKb = true;}
      else if(jriXapentp == WgtPZqXctO){xFeWNNkYIt = true;}
      if(hHxdfQHnJK == qetKAiCgjp){dMdsgEZabA = true;}
      else if(qetKAiCgjp == hHxdfQHnJK){ANaYWLVpEr = true;}
      if(csgBLKCFSz == dgfaFEqwFO){NYZxRzkzsY = true;}
      else if(dgfaFEqwFO == csgBLKCFSz){eaxQdzZUmh = true;}
      if(tPZtQMCJDV == wbdNIWVrCU){MyMyqGAwVC = true;}
      if(guGMDSuwpo == zzGfuhPwny){UpRdayjgxR = true;}
      if(mPbXXdArDP == LDZBGDMIRW){qpzmRHIxsl = true;}
      while(wbdNIWVrCU == tPZtQMCJDV){zafZVJYeNT = true;}
      while(zzGfuhPwny == zzGfuhPwny){kaQljjcdMa = true;}
      while(LDZBGDMIRW == LDZBGDMIRW){agbWQWHNrO = true;}
      if(zhhesPBfBc == true){zhhesPBfBc = false;}
      if(MKeOpdZzeX == true){MKeOpdZzeX = false;}
      if(ouHHDsBcGE == true){ouHHDsBcGE = false;}
      if(KNZeVRQamf == true){KNZeVRQamf = false;}
      if(fitLkAXLKb == true){fitLkAXLKb = false;}
      if(dMdsgEZabA == true){dMdsgEZabA = false;}
      if(NYZxRzkzsY == true){NYZxRzkzsY = false;}
      if(MyMyqGAwVC == true){MyMyqGAwVC = false;}
      if(UpRdayjgxR == true){UpRdayjgxR = false;}
      if(qpzmRHIxsl == true){qpzmRHIxsl = false;}
      if(PXRlPeAeBa == true){PXRlPeAeBa = false;}
      if(DcEZeXGuVT == true){DcEZeXGuVT = false;}
      if(ODCbhWzYgj == true){ODCbhWzYgj = false;}
      if(xDDjlwXfOw == true){xDDjlwXfOw = false;}
      if(xFeWNNkYIt == true){xFeWNNkYIt = false;}
      if(ANaYWLVpEr == true){ANaYWLVpEr = false;}
      if(eaxQdzZUmh == true){eaxQdzZUmh = false;}
      if(zafZVJYeNT == true){zafZVJYeNT = false;}
      if(kaQljjcdMa == true){kaQljjcdMa = false;}
      if(agbWQWHNrO == true){agbWQWHNrO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRCEHNZQUS
{ 
  void KIwSWJrrGB()
  { 
      bool jyrBAnEeYl = false;
      bool qsWxKYUJrm = false;
      bool yQxzqBqefW = false;
      bool bTyUtoDois = false;
      bool TdjqDtiQIz = false;
      bool WtacmTArJz = false;
      bool xYyCKXuBDV = false;
      bool VfZzSUfFwx = false;
      bool SaWgzgrUha = false;
      bool oKejuteggf = false;
      bool ygMldqTbKS = false;
      bool muwLfWCRDc = false;
      bool eZTbgKApDX = false;
      bool oyYPzkNjCH = false;
      bool NQKOmsOSEY = false;
      bool rMdEAYMkFT = false;
      bool qdXlcnVfMt = false;
      bool JROwOOOEnm = false;
      bool whkeebUTPZ = false;
      bool YcdiQjrYkz = false;
      string YqMfOslpfH;
      string YnCQdQEIsz;
      string LxPzZtnnwn;
      string CLLyVIINbD;
      string kOXLInBZjS;
      string sPbPjabMFT;
      string EytqFNcDuU;
      string HqfoOwZEpk;
      string sNEctmjuOt;
      string guHIymUfGu;
      string LxdOKCilBm;
      string AXWUapsQwR;
      string dgoAmMiXqa;
      string bsxuZuioRr;
      string DytasJYmgH;
      string sDjnRdHday;
      string TLtZLHZaue;
      string GEzEOemOGd;
      string mupjhYJJdu;
      string mFNTXrDTPl;
      if(YqMfOslpfH == LxdOKCilBm){jyrBAnEeYl = true;}
      else if(LxdOKCilBm == YqMfOslpfH){ygMldqTbKS = true;}
      if(YnCQdQEIsz == AXWUapsQwR){qsWxKYUJrm = true;}
      else if(AXWUapsQwR == YnCQdQEIsz){muwLfWCRDc = true;}
      if(LxPzZtnnwn == dgoAmMiXqa){yQxzqBqefW = true;}
      else if(dgoAmMiXqa == LxPzZtnnwn){eZTbgKApDX = true;}
      if(CLLyVIINbD == bsxuZuioRr){bTyUtoDois = true;}
      else if(bsxuZuioRr == CLLyVIINbD){oyYPzkNjCH = true;}
      if(kOXLInBZjS == DytasJYmgH){TdjqDtiQIz = true;}
      else if(DytasJYmgH == kOXLInBZjS){NQKOmsOSEY = true;}
      if(sPbPjabMFT == sDjnRdHday){WtacmTArJz = true;}
      else if(sDjnRdHday == sPbPjabMFT){rMdEAYMkFT = true;}
      if(EytqFNcDuU == TLtZLHZaue){xYyCKXuBDV = true;}
      else if(TLtZLHZaue == EytqFNcDuU){qdXlcnVfMt = true;}
      if(HqfoOwZEpk == GEzEOemOGd){VfZzSUfFwx = true;}
      if(sNEctmjuOt == mupjhYJJdu){SaWgzgrUha = true;}
      if(guHIymUfGu == mFNTXrDTPl){oKejuteggf = true;}
      while(GEzEOemOGd == HqfoOwZEpk){JROwOOOEnm = true;}
      while(mupjhYJJdu == mupjhYJJdu){whkeebUTPZ = true;}
      while(mFNTXrDTPl == mFNTXrDTPl){YcdiQjrYkz = true;}
      if(jyrBAnEeYl == true){jyrBAnEeYl = false;}
      if(qsWxKYUJrm == true){qsWxKYUJrm = false;}
      if(yQxzqBqefW == true){yQxzqBqefW = false;}
      if(bTyUtoDois == true){bTyUtoDois = false;}
      if(TdjqDtiQIz == true){TdjqDtiQIz = false;}
      if(WtacmTArJz == true){WtacmTArJz = false;}
      if(xYyCKXuBDV == true){xYyCKXuBDV = false;}
      if(VfZzSUfFwx == true){VfZzSUfFwx = false;}
      if(SaWgzgrUha == true){SaWgzgrUha = false;}
      if(oKejuteggf == true){oKejuteggf = false;}
      if(ygMldqTbKS == true){ygMldqTbKS = false;}
      if(muwLfWCRDc == true){muwLfWCRDc = false;}
      if(eZTbgKApDX == true){eZTbgKApDX = false;}
      if(oyYPzkNjCH == true){oyYPzkNjCH = false;}
      if(NQKOmsOSEY == true){NQKOmsOSEY = false;}
      if(rMdEAYMkFT == true){rMdEAYMkFT = false;}
      if(qdXlcnVfMt == true){qdXlcnVfMt = false;}
      if(JROwOOOEnm == true){JROwOOOEnm = false;}
      if(whkeebUTPZ == true){whkeebUTPZ = false;}
      if(YcdiQjrYkz == true){YcdiQjrYkz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYLFBYYVGS
{ 
  void YRVjBNkGtL()
  { 
      bool oFmSdOFijw = false;
      bool cbPgkzkCse = false;
      bool TQfHKRmFLb = false;
      bool JjCDaVqTOf = false;
      bool wxEjeturUs = false;
      bool VgIWGXZeIL = false;
      bool aAWIlrZMGP = false;
      bool HQnMiWMucQ = false;
      bool VukRGcbfxC = false;
      bool wLLDFwZuxm = false;
      bool UikFlEswni = false;
      bool LdCrofPECJ = false;
      bool QtPDTwFkHm = false;
      bool wQyoumJefB = false;
      bool ifqNqRITNY = false;
      bool fVrmVaThlo = false;
      bool zInBmueMwC = false;
      bool VjXAakCBMB = false;
      bool mkXhGaXKSU = false;
      bool SasqCaqpau = false;
      string OmhqQzWddk;
      string PWdAfUUKZI;
      string VJhImMIHYT;
      string cNrFzNauni;
      string aCZpTWqBaz;
      string kjlqUEEYDE;
      string qPEKHBdXAS;
      string tZWqgSjqoP;
      string UGfYhsaBku;
      string IBqiqKyPhR;
      string rSAIFLMuKC;
      string TNjmijjfbO;
      string acmFKrhmzV;
      string UTIXXCGWTW;
      string ffpiatRDAH;
      string aRnTqPftxM;
      string dYungAFLPg;
      string dMMFitlDeP;
      string admruCfofH;
      string VLZGsHjCBa;
      if(OmhqQzWddk == rSAIFLMuKC){oFmSdOFijw = true;}
      else if(rSAIFLMuKC == OmhqQzWddk){UikFlEswni = true;}
      if(PWdAfUUKZI == TNjmijjfbO){cbPgkzkCse = true;}
      else if(TNjmijjfbO == PWdAfUUKZI){LdCrofPECJ = true;}
      if(VJhImMIHYT == acmFKrhmzV){TQfHKRmFLb = true;}
      else if(acmFKrhmzV == VJhImMIHYT){QtPDTwFkHm = true;}
      if(cNrFzNauni == UTIXXCGWTW){JjCDaVqTOf = true;}
      else if(UTIXXCGWTW == cNrFzNauni){wQyoumJefB = true;}
      if(aCZpTWqBaz == ffpiatRDAH){wxEjeturUs = true;}
      else if(ffpiatRDAH == aCZpTWqBaz){ifqNqRITNY = true;}
      if(kjlqUEEYDE == aRnTqPftxM){VgIWGXZeIL = true;}
      else if(aRnTqPftxM == kjlqUEEYDE){fVrmVaThlo = true;}
      if(qPEKHBdXAS == dYungAFLPg){aAWIlrZMGP = true;}
      else if(dYungAFLPg == qPEKHBdXAS){zInBmueMwC = true;}
      if(tZWqgSjqoP == dMMFitlDeP){HQnMiWMucQ = true;}
      if(UGfYhsaBku == admruCfofH){VukRGcbfxC = true;}
      if(IBqiqKyPhR == VLZGsHjCBa){wLLDFwZuxm = true;}
      while(dMMFitlDeP == tZWqgSjqoP){VjXAakCBMB = true;}
      while(admruCfofH == admruCfofH){mkXhGaXKSU = true;}
      while(VLZGsHjCBa == VLZGsHjCBa){SasqCaqpau = true;}
      if(oFmSdOFijw == true){oFmSdOFijw = false;}
      if(cbPgkzkCse == true){cbPgkzkCse = false;}
      if(TQfHKRmFLb == true){TQfHKRmFLb = false;}
      if(JjCDaVqTOf == true){JjCDaVqTOf = false;}
      if(wxEjeturUs == true){wxEjeturUs = false;}
      if(VgIWGXZeIL == true){VgIWGXZeIL = false;}
      if(aAWIlrZMGP == true){aAWIlrZMGP = false;}
      if(HQnMiWMucQ == true){HQnMiWMucQ = false;}
      if(VukRGcbfxC == true){VukRGcbfxC = false;}
      if(wLLDFwZuxm == true){wLLDFwZuxm = false;}
      if(UikFlEswni == true){UikFlEswni = false;}
      if(LdCrofPECJ == true){LdCrofPECJ = false;}
      if(QtPDTwFkHm == true){QtPDTwFkHm = false;}
      if(wQyoumJefB == true){wQyoumJefB = false;}
      if(ifqNqRITNY == true){ifqNqRITNY = false;}
      if(fVrmVaThlo == true){fVrmVaThlo = false;}
      if(zInBmueMwC == true){zInBmueMwC = false;}
      if(VjXAakCBMB == true){VjXAakCBMB = false;}
      if(mkXhGaXKSU == true){mkXhGaXKSU = false;}
      if(SasqCaqpau == true){SasqCaqpau = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNFRSQEVQQ
{ 
  void gNDsbKGfku()
  { 
      bool QzafFbaSGH = false;
      bool idyKlHVBtE = false;
      bool fWqZdFqNZA = false;
      bool qlybReXHll = false;
      bool msbBqBLQRd = false;
      bool JpJXztIACz = false;
      bool jMrFQweWrH = false;
      bool iNOHQltohb = false;
      bool tawwqBcabW = false;
      bool WWFmBaBWkt = false;
      bool VnXKuubBGM = false;
      bool ASSZEJPwNO = false;
      bool TEtUjLIaGp = false;
      bool kWEnFFClAw = false;
      bool ZaTOWDEfhq = false;
      bool KEJVaRsCZi = false;
      bool mAuQbcNdTy = false;
      bool HduRorjfyf = false;
      bool GcsOefNhNn = false;
      bool MzLRJYfDms = false;
      string trFGbYkkbi;
      string iVYKDwxyKp;
      string NinohZkYmB;
      string hUohTARykq;
      string wcJJbHQeCY;
      string dCaLLKEPYB;
      string mLyaBOfqqC;
      string eyNStkZdNZ;
      string IFVNWesdVJ;
      string wBYiDjdhIM;
      string aZnAseoIRa;
      string jZByshokDV;
      string UCVgFdYeOJ;
      string HqUBziRVTq;
      string pkLuYVzZpV;
      string urelqYDGtP;
      string GKsISsEAzJ;
      string QSRLfipZHi;
      string dynrNOMhJZ;
      string eKbDkeqDbf;
      if(trFGbYkkbi == aZnAseoIRa){QzafFbaSGH = true;}
      else if(aZnAseoIRa == trFGbYkkbi){VnXKuubBGM = true;}
      if(iVYKDwxyKp == jZByshokDV){idyKlHVBtE = true;}
      else if(jZByshokDV == iVYKDwxyKp){ASSZEJPwNO = true;}
      if(NinohZkYmB == UCVgFdYeOJ){fWqZdFqNZA = true;}
      else if(UCVgFdYeOJ == NinohZkYmB){TEtUjLIaGp = true;}
      if(hUohTARykq == HqUBziRVTq){qlybReXHll = true;}
      else if(HqUBziRVTq == hUohTARykq){kWEnFFClAw = true;}
      if(wcJJbHQeCY == pkLuYVzZpV){msbBqBLQRd = true;}
      else if(pkLuYVzZpV == wcJJbHQeCY){ZaTOWDEfhq = true;}
      if(dCaLLKEPYB == urelqYDGtP){JpJXztIACz = true;}
      else if(urelqYDGtP == dCaLLKEPYB){KEJVaRsCZi = true;}
      if(mLyaBOfqqC == GKsISsEAzJ){jMrFQweWrH = true;}
      else if(GKsISsEAzJ == mLyaBOfqqC){mAuQbcNdTy = true;}
      if(eyNStkZdNZ == QSRLfipZHi){iNOHQltohb = true;}
      if(IFVNWesdVJ == dynrNOMhJZ){tawwqBcabW = true;}
      if(wBYiDjdhIM == eKbDkeqDbf){WWFmBaBWkt = true;}
      while(QSRLfipZHi == eyNStkZdNZ){HduRorjfyf = true;}
      while(dynrNOMhJZ == dynrNOMhJZ){GcsOefNhNn = true;}
      while(eKbDkeqDbf == eKbDkeqDbf){MzLRJYfDms = true;}
      if(QzafFbaSGH == true){QzafFbaSGH = false;}
      if(idyKlHVBtE == true){idyKlHVBtE = false;}
      if(fWqZdFqNZA == true){fWqZdFqNZA = false;}
      if(qlybReXHll == true){qlybReXHll = false;}
      if(msbBqBLQRd == true){msbBqBLQRd = false;}
      if(JpJXztIACz == true){JpJXztIACz = false;}
      if(jMrFQweWrH == true){jMrFQweWrH = false;}
      if(iNOHQltohb == true){iNOHQltohb = false;}
      if(tawwqBcabW == true){tawwqBcabW = false;}
      if(WWFmBaBWkt == true){WWFmBaBWkt = false;}
      if(VnXKuubBGM == true){VnXKuubBGM = false;}
      if(ASSZEJPwNO == true){ASSZEJPwNO = false;}
      if(TEtUjLIaGp == true){TEtUjLIaGp = false;}
      if(kWEnFFClAw == true){kWEnFFClAw = false;}
      if(ZaTOWDEfhq == true){ZaTOWDEfhq = false;}
      if(KEJVaRsCZi == true){KEJVaRsCZi = false;}
      if(mAuQbcNdTy == true){mAuQbcNdTy = false;}
      if(HduRorjfyf == true){HduRorjfyf = false;}
      if(GcsOefNhNn == true){GcsOefNhNn = false;}
      if(MzLRJYfDms == true){MzLRJYfDms = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZNCVKWZEL
{ 
  void yfKgkqbqoK()
  { 
      bool TgrWGWjGiG = false;
      bool FHSglluIpL = false;
      bool zATIhkHRhW = false;
      bool DsqRPmkHrt = false;
      bool YjjREUhaNR = false;
      bool agSxcSMjnV = false;
      bool ORXMDMPBRz = false;
      bool BnQwmOQCDN = false;
      bool CgEPuWZtnw = false;
      bool aBSVfGLXOr = false;
      bool EfIOQmPWJN = false;
      bool CJfaTgNIQf = false;
      bool lUNVYAUuPg = false;
      bool DsnLIVYpyI = false;
      bool GDjatQUrCz = false;
      bool rDGhFjSmoQ = false;
      bool SUHcKIVURx = false;
      bool IXJIZiklbI = false;
      bool ebrPnzlFGY = false;
      bool DlAhokwGPk = false;
      string iykDDDeYAp;
      string ZSMJOORbRL;
      string tVPAVpPbsR;
      string MjVaFmbfnf;
      string eHjyiZVcPl;
      string qakrSMhjhN;
      string mCfhcpxlEb;
      string llnkfmlRRu;
      string TmMGZkycIr;
      string ErxasbbBUr;
      string bjYnAFmALf;
      string ZQRlsAoYHr;
      string rTcLWsoMrE;
      string LjwYSiNYGU;
      string xyQcRnZLgs;
      string mCscAIHMQG;
      string PaHHTpTsSK;
      string lQRmtsCAsi;
      string TdezQIpSYK;
      string bBIAEWpJIb;
      if(iykDDDeYAp == bjYnAFmALf){TgrWGWjGiG = true;}
      else if(bjYnAFmALf == iykDDDeYAp){EfIOQmPWJN = true;}
      if(ZSMJOORbRL == ZQRlsAoYHr){FHSglluIpL = true;}
      else if(ZQRlsAoYHr == ZSMJOORbRL){CJfaTgNIQf = true;}
      if(tVPAVpPbsR == rTcLWsoMrE){zATIhkHRhW = true;}
      else if(rTcLWsoMrE == tVPAVpPbsR){lUNVYAUuPg = true;}
      if(MjVaFmbfnf == LjwYSiNYGU){DsqRPmkHrt = true;}
      else if(LjwYSiNYGU == MjVaFmbfnf){DsnLIVYpyI = true;}
      if(eHjyiZVcPl == xyQcRnZLgs){YjjREUhaNR = true;}
      else if(xyQcRnZLgs == eHjyiZVcPl){GDjatQUrCz = true;}
      if(qakrSMhjhN == mCscAIHMQG){agSxcSMjnV = true;}
      else if(mCscAIHMQG == qakrSMhjhN){rDGhFjSmoQ = true;}
      if(mCfhcpxlEb == PaHHTpTsSK){ORXMDMPBRz = true;}
      else if(PaHHTpTsSK == mCfhcpxlEb){SUHcKIVURx = true;}
      if(llnkfmlRRu == lQRmtsCAsi){BnQwmOQCDN = true;}
      if(TmMGZkycIr == TdezQIpSYK){CgEPuWZtnw = true;}
      if(ErxasbbBUr == bBIAEWpJIb){aBSVfGLXOr = true;}
      while(lQRmtsCAsi == llnkfmlRRu){IXJIZiklbI = true;}
      while(TdezQIpSYK == TdezQIpSYK){ebrPnzlFGY = true;}
      while(bBIAEWpJIb == bBIAEWpJIb){DlAhokwGPk = true;}
      if(TgrWGWjGiG == true){TgrWGWjGiG = false;}
      if(FHSglluIpL == true){FHSglluIpL = false;}
      if(zATIhkHRhW == true){zATIhkHRhW = false;}
      if(DsqRPmkHrt == true){DsqRPmkHrt = false;}
      if(YjjREUhaNR == true){YjjREUhaNR = false;}
      if(agSxcSMjnV == true){agSxcSMjnV = false;}
      if(ORXMDMPBRz == true){ORXMDMPBRz = false;}
      if(BnQwmOQCDN == true){BnQwmOQCDN = false;}
      if(CgEPuWZtnw == true){CgEPuWZtnw = false;}
      if(aBSVfGLXOr == true){aBSVfGLXOr = false;}
      if(EfIOQmPWJN == true){EfIOQmPWJN = false;}
      if(CJfaTgNIQf == true){CJfaTgNIQf = false;}
      if(lUNVYAUuPg == true){lUNVYAUuPg = false;}
      if(DsnLIVYpyI == true){DsnLIVYpyI = false;}
      if(GDjatQUrCz == true){GDjatQUrCz = false;}
      if(rDGhFjSmoQ == true){rDGhFjSmoQ = false;}
      if(SUHcKIVURx == true){SUHcKIVURx = false;}
      if(IXJIZiklbI == true){IXJIZiklbI = false;}
      if(ebrPnzlFGY == true){ebrPnzlFGY = false;}
      if(DlAhokwGPk == true){DlAhokwGPk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SBVRXEOJPA
{ 
  void kKFQbZwYwp()
  { 
      bool dJpocXAcDm = false;
      bool eoDWqLloHt = false;
      bool WBTqsRylBS = false;
      bool zwwOqIiYmV = false;
      bool fPLMYeCtsk = false;
      bool NQMEHcoyuL = false;
      bool YOaknirnfh = false;
      bool cNBkNHoGSO = false;
      bool ODsQEhjrHN = false;
      bool SjcbwRnaYp = false;
      bool lOOKHzOaqz = false;
      bool mhegwVVKfF = false;
      bool yAfRPrkYnu = false;
      bool SOhcbzohIE = false;
      bool SIAIajEufa = false;
      bool wduSqkiwuP = false;
      bool OplufYACFw = false;
      bool gmBamoAXqe = false;
      bool mosNzoTOlp = false;
      bool QrmspcWFbB = false;
      string jhdTXsZONS;
      string BPzqiyrtfx;
      string ufFNwrgjxJ;
      string dAdZdXIDDm;
      string DEIdKRfuSw;
      string iJQbUEcQXf;
      string LpREnBlZMK;
      string oopstpWaCd;
      string LkQBZUjCEZ;
      string ureXaMmEpJ;
      string eGiHGtTXhd;
      string gBNtTZZQdT;
      string QjVlPxJSRg;
      string DRksyFCJtf;
      string BLTZstdkDA;
      string mWZVrukwrJ;
      string jAFAaOPUuO;
      string XPVxSFPusU;
      string SYOQsgrOAD;
      string UFRjwAGTyd;
      if(jhdTXsZONS == eGiHGtTXhd){dJpocXAcDm = true;}
      else if(eGiHGtTXhd == jhdTXsZONS){lOOKHzOaqz = true;}
      if(BPzqiyrtfx == gBNtTZZQdT){eoDWqLloHt = true;}
      else if(gBNtTZZQdT == BPzqiyrtfx){mhegwVVKfF = true;}
      if(ufFNwrgjxJ == QjVlPxJSRg){WBTqsRylBS = true;}
      else if(QjVlPxJSRg == ufFNwrgjxJ){yAfRPrkYnu = true;}
      if(dAdZdXIDDm == DRksyFCJtf){zwwOqIiYmV = true;}
      else if(DRksyFCJtf == dAdZdXIDDm){SOhcbzohIE = true;}
      if(DEIdKRfuSw == BLTZstdkDA){fPLMYeCtsk = true;}
      else if(BLTZstdkDA == DEIdKRfuSw){SIAIajEufa = true;}
      if(iJQbUEcQXf == mWZVrukwrJ){NQMEHcoyuL = true;}
      else if(mWZVrukwrJ == iJQbUEcQXf){wduSqkiwuP = true;}
      if(LpREnBlZMK == jAFAaOPUuO){YOaknirnfh = true;}
      else if(jAFAaOPUuO == LpREnBlZMK){OplufYACFw = true;}
      if(oopstpWaCd == XPVxSFPusU){cNBkNHoGSO = true;}
      if(LkQBZUjCEZ == SYOQsgrOAD){ODsQEhjrHN = true;}
      if(ureXaMmEpJ == UFRjwAGTyd){SjcbwRnaYp = true;}
      while(XPVxSFPusU == oopstpWaCd){gmBamoAXqe = true;}
      while(SYOQsgrOAD == SYOQsgrOAD){mosNzoTOlp = true;}
      while(UFRjwAGTyd == UFRjwAGTyd){QrmspcWFbB = true;}
      if(dJpocXAcDm == true){dJpocXAcDm = false;}
      if(eoDWqLloHt == true){eoDWqLloHt = false;}
      if(WBTqsRylBS == true){WBTqsRylBS = false;}
      if(zwwOqIiYmV == true){zwwOqIiYmV = false;}
      if(fPLMYeCtsk == true){fPLMYeCtsk = false;}
      if(NQMEHcoyuL == true){NQMEHcoyuL = false;}
      if(YOaknirnfh == true){YOaknirnfh = false;}
      if(cNBkNHoGSO == true){cNBkNHoGSO = false;}
      if(ODsQEhjrHN == true){ODsQEhjrHN = false;}
      if(SjcbwRnaYp == true){SjcbwRnaYp = false;}
      if(lOOKHzOaqz == true){lOOKHzOaqz = false;}
      if(mhegwVVKfF == true){mhegwVVKfF = false;}
      if(yAfRPrkYnu == true){yAfRPrkYnu = false;}
      if(SOhcbzohIE == true){SOhcbzohIE = false;}
      if(SIAIajEufa == true){SIAIajEufa = false;}
      if(wduSqkiwuP == true){wduSqkiwuP = false;}
      if(OplufYACFw == true){OplufYACFw = false;}
      if(gmBamoAXqe == true){gmBamoAXqe = false;}
      if(mosNzoTOlp == true){mosNzoTOlp = false;}
      if(QrmspcWFbB == true){QrmspcWFbB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POAINXMMQG
{ 
  void UBJBQNQMfn()
  { 
      bool qHYuDqcnVK = false;
      bool kcueaWOPLZ = false;
      bool RBBWuLhAqy = false;
      bool dleIbNmFmW = false;
      bool CCiArjEfXl = false;
      bool LwtUHpGCzq = false;
      bool JbwXfzxmCM = false;
      bool jIcnWOSBeK = false;
      bool HCcEmgqJAl = false;
      bool HkFuNZFKTr = false;
      bool mQcKCCTGyr = false;
      bool XFWojGyrkz = false;
      bool HnlQFzCgZw = false;
      bool JHglXpZSCj = false;
      bool MkKIOCNQKH = false;
      bool bNZTjyeLED = false;
      bool zmfBiQXkQt = false;
      bool gfoAmWddCD = false;
      bool llVSUugNCZ = false;
      bool KNNzjZFJYy = false;
      string VANuTaYaPp;
      string prmXfMKacs;
      string dNoVhEMByE;
      string PBPCgNhrrT;
      string IzwhzcMlfQ;
      string nEVKpHLrMP;
      string OWcLZockqR;
      string eRiJkdRGVF;
      string qZVhPLeFLY;
      string BpfcEkWkHK;
      string zbuNlVVLYL;
      string pEWGXoBuuN;
      string JWZRPolFFz;
      string HgyKFPdIus;
      string pTfzixSZEO;
      string jbotAcCdxx;
      string jPGZEJFLAI;
      string LrzBXpqZhS;
      string VMBpOeqEKc;
      string MzKyJZMFuZ;
      if(VANuTaYaPp == zbuNlVVLYL){qHYuDqcnVK = true;}
      else if(zbuNlVVLYL == VANuTaYaPp){mQcKCCTGyr = true;}
      if(prmXfMKacs == pEWGXoBuuN){kcueaWOPLZ = true;}
      else if(pEWGXoBuuN == prmXfMKacs){XFWojGyrkz = true;}
      if(dNoVhEMByE == JWZRPolFFz){RBBWuLhAqy = true;}
      else if(JWZRPolFFz == dNoVhEMByE){HnlQFzCgZw = true;}
      if(PBPCgNhrrT == HgyKFPdIus){dleIbNmFmW = true;}
      else if(HgyKFPdIus == PBPCgNhrrT){JHglXpZSCj = true;}
      if(IzwhzcMlfQ == pTfzixSZEO){CCiArjEfXl = true;}
      else if(pTfzixSZEO == IzwhzcMlfQ){MkKIOCNQKH = true;}
      if(nEVKpHLrMP == jbotAcCdxx){LwtUHpGCzq = true;}
      else if(jbotAcCdxx == nEVKpHLrMP){bNZTjyeLED = true;}
      if(OWcLZockqR == jPGZEJFLAI){JbwXfzxmCM = true;}
      else if(jPGZEJFLAI == OWcLZockqR){zmfBiQXkQt = true;}
      if(eRiJkdRGVF == LrzBXpqZhS){jIcnWOSBeK = true;}
      if(qZVhPLeFLY == VMBpOeqEKc){HCcEmgqJAl = true;}
      if(BpfcEkWkHK == MzKyJZMFuZ){HkFuNZFKTr = true;}
      while(LrzBXpqZhS == eRiJkdRGVF){gfoAmWddCD = true;}
      while(VMBpOeqEKc == VMBpOeqEKc){llVSUugNCZ = true;}
      while(MzKyJZMFuZ == MzKyJZMFuZ){KNNzjZFJYy = true;}
      if(qHYuDqcnVK == true){qHYuDqcnVK = false;}
      if(kcueaWOPLZ == true){kcueaWOPLZ = false;}
      if(RBBWuLhAqy == true){RBBWuLhAqy = false;}
      if(dleIbNmFmW == true){dleIbNmFmW = false;}
      if(CCiArjEfXl == true){CCiArjEfXl = false;}
      if(LwtUHpGCzq == true){LwtUHpGCzq = false;}
      if(JbwXfzxmCM == true){JbwXfzxmCM = false;}
      if(jIcnWOSBeK == true){jIcnWOSBeK = false;}
      if(HCcEmgqJAl == true){HCcEmgqJAl = false;}
      if(HkFuNZFKTr == true){HkFuNZFKTr = false;}
      if(mQcKCCTGyr == true){mQcKCCTGyr = false;}
      if(XFWojGyrkz == true){XFWojGyrkz = false;}
      if(HnlQFzCgZw == true){HnlQFzCgZw = false;}
      if(JHglXpZSCj == true){JHglXpZSCj = false;}
      if(MkKIOCNQKH == true){MkKIOCNQKH = false;}
      if(bNZTjyeLED == true){bNZTjyeLED = false;}
      if(zmfBiQXkQt == true){zmfBiQXkQt = false;}
      if(gfoAmWddCD == true){gfoAmWddCD = false;}
      if(llVSUugNCZ == true){llVSUugNCZ = false;}
      if(KNNzjZFJYy == true){KNNzjZFJYy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXVLEKNCXY
{ 
  void AzXhzNPwcG()
  { 
      bool xXXIHUjkWZ = false;
      bool ZbHLxBuewN = false;
      bool PDMjWbKRJt = false;
      bool YwqHDLchCo = false;
      bool qNURawRjBc = false;
      bool UEJWytKmkf = false;
      bool KSacBdjzIk = false;
      bool YMcGVChuJa = false;
      bool JZPgZUlTJI = false;
      bool BpwWeYlrQx = false;
      bool MRbPEHaDBu = false;
      bool MOdKVjCtCg = false;
      bool qPpAjhPFax = false;
      bool QoeMOqyAcR = false;
      bool siSNwlMlAu = false;
      bool WroiFwbbeV = false;
      bool qUbDeWjRwd = false;
      bool lBRkmIwbDx = false;
      bool VdFfaXzuGR = false;
      bool PWVGaXGPiY = false;
      string yCAZuURQKi;
      string yJctPGtFqI;
      string tmLammeirr;
      string lfkhbFiKiG;
      string bUQqiQCwRR;
      string wCubpKpYlH;
      string ohXSwRYuRK;
      string WiVkgYWUrW;
      string jiRauijIqR;
      string PJYaQsxxtQ;
      string rHeHtNgKuQ;
      string nVgPXGQwWM;
      string hPDAtMKtUm;
      string bYZadbEJfh;
      string CZNZcscJDJ;
      string cAZgicEdMg;
      string DlpHoOuFku;
      string BHQoKICcWB;
      string jBqKKayrrB;
      string XZwyePiGkO;
      if(yCAZuURQKi == rHeHtNgKuQ){xXXIHUjkWZ = true;}
      else if(rHeHtNgKuQ == yCAZuURQKi){MRbPEHaDBu = true;}
      if(yJctPGtFqI == nVgPXGQwWM){ZbHLxBuewN = true;}
      else if(nVgPXGQwWM == yJctPGtFqI){MOdKVjCtCg = true;}
      if(tmLammeirr == hPDAtMKtUm){PDMjWbKRJt = true;}
      else if(hPDAtMKtUm == tmLammeirr){qPpAjhPFax = true;}
      if(lfkhbFiKiG == bYZadbEJfh){YwqHDLchCo = true;}
      else if(bYZadbEJfh == lfkhbFiKiG){QoeMOqyAcR = true;}
      if(bUQqiQCwRR == CZNZcscJDJ){qNURawRjBc = true;}
      else if(CZNZcscJDJ == bUQqiQCwRR){siSNwlMlAu = true;}
      if(wCubpKpYlH == cAZgicEdMg){UEJWytKmkf = true;}
      else if(cAZgicEdMg == wCubpKpYlH){WroiFwbbeV = true;}
      if(ohXSwRYuRK == DlpHoOuFku){KSacBdjzIk = true;}
      else if(DlpHoOuFku == ohXSwRYuRK){qUbDeWjRwd = true;}
      if(WiVkgYWUrW == BHQoKICcWB){YMcGVChuJa = true;}
      if(jiRauijIqR == jBqKKayrrB){JZPgZUlTJI = true;}
      if(PJYaQsxxtQ == XZwyePiGkO){BpwWeYlrQx = true;}
      while(BHQoKICcWB == WiVkgYWUrW){lBRkmIwbDx = true;}
      while(jBqKKayrrB == jBqKKayrrB){VdFfaXzuGR = true;}
      while(XZwyePiGkO == XZwyePiGkO){PWVGaXGPiY = true;}
      if(xXXIHUjkWZ == true){xXXIHUjkWZ = false;}
      if(ZbHLxBuewN == true){ZbHLxBuewN = false;}
      if(PDMjWbKRJt == true){PDMjWbKRJt = false;}
      if(YwqHDLchCo == true){YwqHDLchCo = false;}
      if(qNURawRjBc == true){qNURawRjBc = false;}
      if(UEJWytKmkf == true){UEJWytKmkf = false;}
      if(KSacBdjzIk == true){KSacBdjzIk = false;}
      if(YMcGVChuJa == true){YMcGVChuJa = false;}
      if(JZPgZUlTJI == true){JZPgZUlTJI = false;}
      if(BpwWeYlrQx == true){BpwWeYlrQx = false;}
      if(MRbPEHaDBu == true){MRbPEHaDBu = false;}
      if(MOdKVjCtCg == true){MOdKVjCtCg = false;}
      if(qPpAjhPFax == true){qPpAjhPFax = false;}
      if(QoeMOqyAcR == true){QoeMOqyAcR = false;}
      if(siSNwlMlAu == true){siSNwlMlAu = false;}
      if(WroiFwbbeV == true){WroiFwbbeV = false;}
      if(qUbDeWjRwd == true){qUbDeWjRwd = false;}
      if(lBRkmIwbDx == true){lBRkmIwbDx = false;}
      if(VdFfaXzuGR == true){VdFfaXzuGR = false;}
      if(PWVGaXGPiY == true){PWVGaXGPiY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDCQQBVGUF
{ 
  void CPhcsgjdRT()
  { 
      bool MikSUXOFyJ = false;
      bool FXHGwhzpJK = false;
      bool oPPwxKPfMB = false;
      bool SedzcYCoJk = false;
      bool erUmYCJaWJ = false;
      bool homuDxSnUK = false;
      bool IisxqZtIcX = false;
      bool eKfYewucXt = false;
      bool BoICTcqhuf = false;
      bool FNTzbwyXwy = false;
      bool IAxzdWIOPG = false;
      bool CpQZITapdN = false;
      bool hMMwSQqgwi = false;
      bool xWfYlAqIYx = false;
      bool TcSndOxspI = false;
      bool UIthQwnAgM = false;
      bool eaRfIeKqmI = false;
      bool cRRfsFsXSD = false;
      bool TyqmNocyIp = false;
      bool MpaLRsKlez = false;
      string rdmpBiOKKX;
      string zsxAzJWrgQ;
      string gOiKRHFWHH;
      string CFmdDcqXsR;
      string nneazfVSHa;
      string VFKZGdtcYs;
      string dqDDUsFSwW;
      string SzyObsiIKk;
      string llPfkwuNXZ;
      string iOzznxkbGF;
      string ZCVkIWGuxM;
      string tlRmHqbWRY;
      string yrtWnEAzae;
      string HHBELiPdXN;
      string oAPKexwMqw;
      string VNJhHgHzxE;
      string VHUSEljMaY;
      string axzEiybjqp;
      string HnHdJtxTxd;
      string aQgTqhexFr;
      if(rdmpBiOKKX == ZCVkIWGuxM){MikSUXOFyJ = true;}
      else if(ZCVkIWGuxM == rdmpBiOKKX){IAxzdWIOPG = true;}
      if(zsxAzJWrgQ == tlRmHqbWRY){FXHGwhzpJK = true;}
      else if(tlRmHqbWRY == zsxAzJWrgQ){CpQZITapdN = true;}
      if(gOiKRHFWHH == yrtWnEAzae){oPPwxKPfMB = true;}
      else if(yrtWnEAzae == gOiKRHFWHH){hMMwSQqgwi = true;}
      if(CFmdDcqXsR == HHBELiPdXN){SedzcYCoJk = true;}
      else if(HHBELiPdXN == CFmdDcqXsR){xWfYlAqIYx = true;}
      if(nneazfVSHa == oAPKexwMqw){erUmYCJaWJ = true;}
      else if(oAPKexwMqw == nneazfVSHa){TcSndOxspI = true;}
      if(VFKZGdtcYs == VNJhHgHzxE){homuDxSnUK = true;}
      else if(VNJhHgHzxE == VFKZGdtcYs){UIthQwnAgM = true;}
      if(dqDDUsFSwW == VHUSEljMaY){IisxqZtIcX = true;}
      else if(VHUSEljMaY == dqDDUsFSwW){eaRfIeKqmI = true;}
      if(SzyObsiIKk == axzEiybjqp){eKfYewucXt = true;}
      if(llPfkwuNXZ == HnHdJtxTxd){BoICTcqhuf = true;}
      if(iOzznxkbGF == aQgTqhexFr){FNTzbwyXwy = true;}
      while(axzEiybjqp == SzyObsiIKk){cRRfsFsXSD = true;}
      while(HnHdJtxTxd == HnHdJtxTxd){TyqmNocyIp = true;}
      while(aQgTqhexFr == aQgTqhexFr){MpaLRsKlez = true;}
      if(MikSUXOFyJ == true){MikSUXOFyJ = false;}
      if(FXHGwhzpJK == true){FXHGwhzpJK = false;}
      if(oPPwxKPfMB == true){oPPwxKPfMB = false;}
      if(SedzcYCoJk == true){SedzcYCoJk = false;}
      if(erUmYCJaWJ == true){erUmYCJaWJ = false;}
      if(homuDxSnUK == true){homuDxSnUK = false;}
      if(IisxqZtIcX == true){IisxqZtIcX = false;}
      if(eKfYewucXt == true){eKfYewucXt = false;}
      if(BoICTcqhuf == true){BoICTcqhuf = false;}
      if(FNTzbwyXwy == true){FNTzbwyXwy = false;}
      if(IAxzdWIOPG == true){IAxzdWIOPG = false;}
      if(CpQZITapdN == true){CpQZITapdN = false;}
      if(hMMwSQqgwi == true){hMMwSQqgwi = false;}
      if(xWfYlAqIYx == true){xWfYlAqIYx = false;}
      if(TcSndOxspI == true){TcSndOxspI = false;}
      if(UIthQwnAgM == true){UIthQwnAgM = false;}
      if(eaRfIeKqmI == true){eaRfIeKqmI = false;}
      if(cRRfsFsXSD == true){cRRfsFsXSD = false;}
      if(TyqmNocyIp == true){TyqmNocyIp = false;}
      if(MpaLRsKlez == true){MpaLRsKlez = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGFDIEBOCO
{ 
  void qUPbykyIsH()
  { 
      bool saSwoVeEDD = false;
      bool RsxdDGFaxO = false;
      bool acnqrwZLRJ = false;
      bool kVyolWKLOO = false;
      bool OzNnwQUgCV = false;
      bool SmGUrQmbDr = false;
      bool wTltRwuIqf = false;
      bool usMhAbOzta = false;
      bool bsIwpxPcwV = false;
      bool jhIVStMTVA = false;
      bool VLoWZYZXUP = false;
      bool CmhbPDLoDU = false;
      bool gSLVwNjqPF = false;
      bool PudtFQDlWR = false;
      bool WqHfSxAgFP = false;
      bool iWPBSCASZM = false;
      bool niIPAGInVz = false;
      bool zYSlxpLeCy = false;
      bool NDkAVrfbaC = false;
      bool PkLKcniqfL = false;
      string Bldmuxspbx;
      string mBaCAglXFS;
      string XOgMWNdnDX;
      string ZNiHRrwzYI;
      string QJIaVRWuno;
      string YThZOmEQPh;
      string TFmEXYRTjI;
      string jlzwBNGGqF;
      string phANyFeIse;
      string mfjqoKWDDw;
      string zDKeFmUlXA;
      string gyZKqkEZFR;
      string sJaFUECHGp;
      string qCDtFmWUHL;
      string ksjrxoGYzD;
      string FxykDpbFKB;
      string jMegIeueFD;
      string OjRsgzYhHf;
      string ydHDjtDRqO;
      string KRKGbXODjS;
      if(Bldmuxspbx == zDKeFmUlXA){saSwoVeEDD = true;}
      else if(zDKeFmUlXA == Bldmuxspbx){VLoWZYZXUP = true;}
      if(mBaCAglXFS == gyZKqkEZFR){RsxdDGFaxO = true;}
      else if(gyZKqkEZFR == mBaCAglXFS){CmhbPDLoDU = true;}
      if(XOgMWNdnDX == sJaFUECHGp){acnqrwZLRJ = true;}
      else if(sJaFUECHGp == XOgMWNdnDX){gSLVwNjqPF = true;}
      if(ZNiHRrwzYI == qCDtFmWUHL){kVyolWKLOO = true;}
      else if(qCDtFmWUHL == ZNiHRrwzYI){PudtFQDlWR = true;}
      if(QJIaVRWuno == ksjrxoGYzD){OzNnwQUgCV = true;}
      else if(ksjrxoGYzD == QJIaVRWuno){WqHfSxAgFP = true;}
      if(YThZOmEQPh == FxykDpbFKB){SmGUrQmbDr = true;}
      else if(FxykDpbFKB == YThZOmEQPh){iWPBSCASZM = true;}
      if(TFmEXYRTjI == jMegIeueFD){wTltRwuIqf = true;}
      else if(jMegIeueFD == TFmEXYRTjI){niIPAGInVz = true;}
      if(jlzwBNGGqF == OjRsgzYhHf){usMhAbOzta = true;}
      if(phANyFeIse == ydHDjtDRqO){bsIwpxPcwV = true;}
      if(mfjqoKWDDw == KRKGbXODjS){jhIVStMTVA = true;}
      while(OjRsgzYhHf == jlzwBNGGqF){zYSlxpLeCy = true;}
      while(ydHDjtDRqO == ydHDjtDRqO){NDkAVrfbaC = true;}
      while(KRKGbXODjS == KRKGbXODjS){PkLKcniqfL = true;}
      if(saSwoVeEDD == true){saSwoVeEDD = false;}
      if(RsxdDGFaxO == true){RsxdDGFaxO = false;}
      if(acnqrwZLRJ == true){acnqrwZLRJ = false;}
      if(kVyolWKLOO == true){kVyolWKLOO = false;}
      if(OzNnwQUgCV == true){OzNnwQUgCV = false;}
      if(SmGUrQmbDr == true){SmGUrQmbDr = false;}
      if(wTltRwuIqf == true){wTltRwuIqf = false;}
      if(usMhAbOzta == true){usMhAbOzta = false;}
      if(bsIwpxPcwV == true){bsIwpxPcwV = false;}
      if(jhIVStMTVA == true){jhIVStMTVA = false;}
      if(VLoWZYZXUP == true){VLoWZYZXUP = false;}
      if(CmhbPDLoDU == true){CmhbPDLoDU = false;}
      if(gSLVwNjqPF == true){gSLVwNjqPF = false;}
      if(PudtFQDlWR == true){PudtFQDlWR = false;}
      if(WqHfSxAgFP == true){WqHfSxAgFP = false;}
      if(iWPBSCASZM == true){iWPBSCASZM = false;}
      if(niIPAGInVz == true){niIPAGInVz = false;}
      if(zYSlxpLeCy == true){zYSlxpLeCy = false;}
      if(NDkAVrfbaC == true){NDkAVrfbaC = false;}
      if(PkLKcniqfL == true){PkLKcniqfL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LEQCCBHWIP
{ 
  void AbmDJFbxYC()
  { 
      bool qrBkCcFWbo = false;
      bool yMTFqGWRgx = false;
      bool INIkXKdrMe = false;
      bool TwtBIYAdAw = false;
      bool iLsyaldtKc = false;
      bool LMdhNciPMq = false;
      bool zMKwUCSRwR = false;
      bool GrQkOwTJJl = false;
      bool fjhjTHRMnf = false;
      bool ojQIwVBwdY = false;
      bool TMxrWSurTQ = false;
      bool IYFaLOdZcM = false;
      bool jFdQbVbHnr = false;
      bool uWfkRTlpNB = false;
      bool MYsWWQepxh = false;
      bool qaTQoNhfPA = false;
      bool qmEaVksUIq = false;
      bool bnMbAKMGsL = false;
      bool qlKGBTDOwE = false;
      bool kFZMJYUSAk = false;
      string hnFdHEjlPs;
      string PwsGpSboyj;
      string XbNWZemNJI;
      string hmQJNtxIwa;
      string MfPgLMNUbj;
      string qDGKRGaiEb;
      string QVbGLcfiru;
      string USsXWrLgKM;
      string RRlYQdfFrH;
      string TNETJpDIVi;
      string gebgPXKhmZ;
      string tsYqKyiDog;
      string wZqkaGOYNf;
      string nCKaflpFJs;
      string TySRMZoMJK;
      string HzTomGmqFI;
      string JlTGlqixKX;
      string IdtwMyHZXA;
      string RCPCYniVnZ;
      string zyzBihdLeV;
      if(hnFdHEjlPs == gebgPXKhmZ){qrBkCcFWbo = true;}
      else if(gebgPXKhmZ == hnFdHEjlPs){TMxrWSurTQ = true;}
      if(PwsGpSboyj == tsYqKyiDog){yMTFqGWRgx = true;}
      else if(tsYqKyiDog == PwsGpSboyj){IYFaLOdZcM = true;}
      if(XbNWZemNJI == wZqkaGOYNf){INIkXKdrMe = true;}
      else if(wZqkaGOYNf == XbNWZemNJI){jFdQbVbHnr = true;}
      if(hmQJNtxIwa == nCKaflpFJs){TwtBIYAdAw = true;}
      else if(nCKaflpFJs == hmQJNtxIwa){uWfkRTlpNB = true;}
      if(MfPgLMNUbj == TySRMZoMJK){iLsyaldtKc = true;}
      else if(TySRMZoMJK == MfPgLMNUbj){MYsWWQepxh = true;}
      if(qDGKRGaiEb == HzTomGmqFI){LMdhNciPMq = true;}
      else if(HzTomGmqFI == qDGKRGaiEb){qaTQoNhfPA = true;}
      if(QVbGLcfiru == JlTGlqixKX){zMKwUCSRwR = true;}
      else if(JlTGlqixKX == QVbGLcfiru){qmEaVksUIq = true;}
      if(USsXWrLgKM == IdtwMyHZXA){GrQkOwTJJl = true;}
      if(RRlYQdfFrH == RCPCYniVnZ){fjhjTHRMnf = true;}
      if(TNETJpDIVi == zyzBihdLeV){ojQIwVBwdY = true;}
      while(IdtwMyHZXA == USsXWrLgKM){bnMbAKMGsL = true;}
      while(RCPCYniVnZ == RCPCYniVnZ){qlKGBTDOwE = true;}
      while(zyzBihdLeV == zyzBihdLeV){kFZMJYUSAk = true;}
      if(qrBkCcFWbo == true){qrBkCcFWbo = false;}
      if(yMTFqGWRgx == true){yMTFqGWRgx = false;}
      if(INIkXKdrMe == true){INIkXKdrMe = false;}
      if(TwtBIYAdAw == true){TwtBIYAdAw = false;}
      if(iLsyaldtKc == true){iLsyaldtKc = false;}
      if(LMdhNciPMq == true){LMdhNciPMq = false;}
      if(zMKwUCSRwR == true){zMKwUCSRwR = false;}
      if(GrQkOwTJJl == true){GrQkOwTJJl = false;}
      if(fjhjTHRMnf == true){fjhjTHRMnf = false;}
      if(ojQIwVBwdY == true){ojQIwVBwdY = false;}
      if(TMxrWSurTQ == true){TMxrWSurTQ = false;}
      if(IYFaLOdZcM == true){IYFaLOdZcM = false;}
      if(jFdQbVbHnr == true){jFdQbVbHnr = false;}
      if(uWfkRTlpNB == true){uWfkRTlpNB = false;}
      if(MYsWWQepxh == true){MYsWWQepxh = false;}
      if(qaTQoNhfPA == true){qaTQoNhfPA = false;}
      if(qmEaVksUIq == true){qmEaVksUIq = false;}
      if(bnMbAKMGsL == true){bnMbAKMGsL = false;}
      if(qlKGBTDOwE == true){qlKGBTDOwE = false;}
      if(kFZMJYUSAk == true){kFZMJYUSAk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYZLTCQSRS
{ 
  void xFQdJYOeWo()
  { 
      bool OsFQDXOUEa = false;
      bool ptiBoyJXFK = false;
      bool IjxiaPjhLC = false;
      bool PINddpXtPP = false;
      bool xmRFxVtyzX = false;
      bool mXUIhewWom = false;
      bool mfIBKhfFXz = false;
      bool aOHpNVRqkE = false;
      bool UlhnPqmFuz = false;
      bool tAFbcQeQtP = false;
      bool poaAwXPduM = false;
      bool MFljSAxUlT = false;
      bool taJXFaJeNw = false;
      bool qBwVOeLhqr = false;
      bool bIJimnNUJb = false;
      bool TKdaVOfCtV = false;
      bool NjQzVKIQUm = false;
      bool oOctqkQakQ = false;
      bool MoVlcgWVAA = false;
      bool zInUdqrJNb = false;
      string UNhAuDSiwY;
      string nxiVxrxVGH;
      string bxlhdWLhBg;
      string CsiBHeSgNQ;
      string XFBreogucG;
      string ywyYqXbzWY;
      string rjgPWtNhNS;
      string ZQHojVwtDn;
      string pPEuhFuJKj;
      string DSKoYmXkUk;
      string bzhKfhnIoU;
      string bgwhhbelhQ;
      string yDXdPGFSQw;
      string xKZSLqhtOz;
      string RmTpIVWbHx;
      string IlDDlYaEtZ;
      string cUqsWQGdVp;
      string sjXizLigUs;
      string jdLTmLHWfm;
      string PdzoWwuaTq;
      if(UNhAuDSiwY == bzhKfhnIoU){OsFQDXOUEa = true;}
      else if(bzhKfhnIoU == UNhAuDSiwY){poaAwXPduM = true;}
      if(nxiVxrxVGH == bgwhhbelhQ){ptiBoyJXFK = true;}
      else if(bgwhhbelhQ == nxiVxrxVGH){MFljSAxUlT = true;}
      if(bxlhdWLhBg == yDXdPGFSQw){IjxiaPjhLC = true;}
      else if(yDXdPGFSQw == bxlhdWLhBg){taJXFaJeNw = true;}
      if(CsiBHeSgNQ == xKZSLqhtOz){PINddpXtPP = true;}
      else if(xKZSLqhtOz == CsiBHeSgNQ){qBwVOeLhqr = true;}
      if(XFBreogucG == RmTpIVWbHx){xmRFxVtyzX = true;}
      else if(RmTpIVWbHx == XFBreogucG){bIJimnNUJb = true;}
      if(ywyYqXbzWY == IlDDlYaEtZ){mXUIhewWom = true;}
      else if(IlDDlYaEtZ == ywyYqXbzWY){TKdaVOfCtV = true;}
      if(rjgPWtNhNS == cUqsWQGdVp){mfIBKhfFXz = true;}
      else if(cUqsWQGdVp == rjgPWtNhNS){NjQzVKIQUm = true;}
      if(ZQHojVwtDn == sjXizLigUs){aOHpNVRqkE = true;}
      if(pPEuhFuJKj == jdLTmLHWfm){UlhnPqmFuz = true;}
      if(DSKoYmXkUk == PdzoWwuaTq){tAFbcQeQtP = true;}
      while(sjXizLigUs == ZQHojVwtDn){oOctqkQakQ = true;}
      while(jdLTmLHWfm == jdLTmLHWfm){MoVlcgWVAA = true;}
      while(PdzoWwuaTq == PdzoWwuaTq){zInUdqrJNb = true;}
      if(OsFQDXOUEa == true){OsFQDXOUEa = false;}
      if(ptiBoyJXFK == true){ptiBoyJXFK = false;}
      if(IjxiaPjhLC == true){IjxiaPjhLC = false;}
      if(PINddpXtPP == true){PINddpXtPP = false;}
      if(xmRFxVtyzX == true){xmRFxVtyzX = false;}
      if(mXUIhewWom == true){mXUIhewWom = false;}
      if(mfIBKhfFXz == true){mfIBKhfFXz = false;}
      if(aOHpNVRqkE == true){aOHpNVRqkE = false;}
      if(UlhnPqmFuz == true){UlhnPqmFuz = false;}
      if(tAFbcQeQtP == true){tAFbcQeQtP = false;}
      if(poaAwXPduM == true){poaAwXPduM = false;}
      if(MFljSAxUlT == true){MFljSAxUlT = false;}
      if(taJXFaJeNw == true){taJXFaJeNw = false;}
      if(qBwVOeLhqr == true){qBwVOeLhqr = false;}
      if(bIJimnNUJb == true){bIJimnNUJb = false;}
      if(TKdaVOfCtV == true){TKdaVOfCtV = false;}
      if(NjQzVKIQUm == true){NjQzVKIQUm = false;}
      if(oOctqkQakQ == true){oOctqkQakQ = false;}
      if(MoVlcgWVAA == true){MoVlcgWVAA = false;}
      if(zInUdqrJNb == true){zInUdqrJNb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALSQFUFUAS
{ 
  void uzBzLORkeN()
  { 
      bool FNMBZYKwMt = false;
      bool RTsACBrOHf = false;
      bool cKCCiyuhSq = false;
      bool OgdMzzFggq = false;
      bool lWFZYIYiet = false;
      bool xCMGGuLJSb = false;
      bool cbcUejogBD = false;
      bool wLhQsGEbcZ = false;
      bool YMDYsLUXGD = false;
      bool muOFNJskuo = false;
      bool TrhaxlUuMz = false;
      bool pjfrCQXEaS = false;
      bool ORZxPAwcDj = false;
      bool NTgnGgdbaH = false;
      bool qYKGNDOVCw = false;
      bool knJbZCSkLx = false;
      bool oqrclWDrlU = false;
      bool ludTapHSiM = false;
      bool kaZGyYKENE = false;
      bool OsQdSzggTq = false;
      string kNMyubhxQb;
      string RwUcVIUZkK;
      string VsYGUqYiZf;
      string rqQYwLHmqU;
      string UKZYStMyCO;
      string YFkfKrnFdE;
      string CyXkiZeufK;
      string AgiQoKSAnZ;
      string eafKGmGjOE;
      string WCJmSVmoos;
      string PQRrNqWTqz;
      string YnRDZaSMdw;
      string SufbmyXuyS;
      string WdKtKNJnxP;
      string PmsOeikFNq;
      string DaKrZTkpEP;
      string TaVXbucWsL;
      string RePOffCQwE;
      string NRhGPwSSUp;
      string cSiguoRUli;
      if(kNMyubhxQb == PQRrNqWTqz){FNMBZYKwMt = true;}
      else if(PQRrNqWTqz == kNMyubhxQb){TrhaxlUuMz = true;}
      if(RwUcVIUZkK == YnRDZaSMdw){RTsACBrOHf = true;}
      else if(YnRDZaSMdw == RwUcVIUZkK){pjfrCQXEaS = true;}
      if(VsYGUqYiZf == SufbmyXuyS){cKCCiyuhSq = true;}
      else if(SufbmyXuyS == VsYGUqYiZf){ORZxPAwcDj = true;}
      if(rqQYwLHmqU == WdKtKNJnxP){OgdMzzFggq = true;}
      else if(WdKtKNJnxP == rqQYwLHmqU){NTgnGgdbaH = true;}
      if(UKZYStMyCO == PmsOeikFNq){lWFZYIYiet = true;}
      else if(PmsOeikFNq == UKZYStMyCO){qYKGNDOVCw = true;}
      if(YFkfKrnFdE == DaKrZTkpEP){xCMGGuLJSb = true;}
      else if(DaKrZTkpEP == YFkfKrnFdE){knJbZCSkLx = true;}
      if(CyXkiZeufK == TaVXbucWsL){cbcUejogBD = true;}
      else if(TaVXbucWsL == CyXkiZeufK){oqrclWDrlU = true;}
      if(AgiQoKSAnZ == RePOffCQwE){wLhQsGEbcZ = true;}
      if(eafKGmGjOE == NRhGPwSSUp){YMDYsLUXGD = true;}
      if(WCJmSVmoos == cSiguoRUli){muOFNJskuo = true;}
      while(RePOffCQwE == AgiQoKSAnZ){ludTapHSiM = true;}
      while(NRhGPwSSUp == NRhGPwSSUp){kaZGyYKENE = true;}
      while(cSiguoRUli == cSiguoRUli){OsQdSzggTq = true;}
      if(FNMBZYKwMt == true){FNMBZYKwMt = false;}
      if(RTsACBrOHf == true){RTsACBrOHf = false;}
      if(cKCCiyuhSq == true){cKCCiyuhSq = false;}
      if(OgdMzzFggq == true){OgdMzzFggq = false;}
      if(lWFZYIYiet == true){lWFZYIYiet = false;}
      if(xCMGGuLJSb == true){xCMGGuLJSb = false;}
      if(cbcUejogBD == true){cbcUejogBD = false;}
      if(wLhQsGEbcZ == true){wLhQsGEbcZ = false;}
      if(YMDYsLUXGD == true){YMDYsLUXGD = false;}
      if(muOFNJskuo == true){muOFNJskuo = false;}
      if(TrhaxlUuMz == true){TrhaxlUuMz = false;}
      if(pjfrCQXEaS == true){pjfrCQXEaS = false;}
      if(ORZxPAwcDj == true){ORZxPAwcDj = false;}
      if(NTgnGgdbaH == true){NTgnGgdbaH = false;}
      if(qYKGNDOVCw == true){qYKGNDOVCw = false;}
      if(knJbZCSkLx == true){knJbZCSkLx = false;}
      if(oqrclWDrlU == true){oqrclWDrlU = false;}
      if(ludTapHSiM == true){ludTapHSiM = false;}
      if(kaZGyYKENE == true){kaZGyYKENE = false;}
      if(OsQdSzggTq == true){OsQdSzggTq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIIIKYRHEW
{ 
  void dZOWCUjzOf()
  { 
      bool WcwqwESoRt = false;
      bool EqXbDGxmbZ = false;
      bool KGsIIlcyHK = false;
      bool dMFVeadEbS = false;
      bool fBROcYLllS = false;
      bool nBoYmPjmiJ = false;
      bool bUgHQqlCwb = false;
      bool brLItIodei = false;
      bool aqMoVcXfiP = false;
      bool pqURpLUKyl = false;
      bool mJoJpuofee = false;
      bool aFIAikHrkn = false;
      bool SFTgkkXtSi = false;
      bool nderuRBCya = false;
      bool mrBDnkhUiE = false;
      bool DcZKThoHXF = false;
      bool XuMuqxaQEQ = false;
      bool jFsJAZDPsA = false;
      bool CCKNfLEUXN = false;
      bool bsesDqeGMq = false;
      string GEgmUULulT;
      string jWAifaswMx;
      string GUiEqshqWy;
      string HOwVBSjnfE;
      string zMxzBAEtFi;
      string yWLPVlUcwb;
      string mUXmLVZdhM;
      string qEQIxsWiCp;
      string nnknAkDgAO;
      string xGrDReoJmf;
      string aZLsrtGCRb;
      string OkZFmyiima;
      string SscTOjMMqS;
      string DNwWPNbrwG;
      string eAPXzMflQS;
      string uFWMMhxrdH;
      string gsLyYBoDpY;
      string VpmguSdFTC;
      string EawXWyqiJh;
      string QjNoYknQzx;
      if(GEgmUULulT == aZLsrtGCRb){WcwqwESoRt = true;}
      else if(aZLsrtGCRb == GEgmUULulT){mJoJpuofee = true;}
      if(jWAifaswMx == OkZFmyiima){EqXbDGxmbZ = true;}
      else if(OkZFmyiima == jWAifaswMx){aFIAikHrkn = true;}
      if(GUiEqshqWy == SscTOjMMqS){KGsIIlcyHK = true;}
      else if(SscTOjMMqS == GUiEqshqWy){SFTgkkXtSi = true;}
      if(HOwVBSjnfE == DNwWPNbrwG){dMFVeadEbS = true;}
      else if(DNwWPNbrwG == HOwVBSjnfE){nderuRBCya = true;}
      if(zMxzBAEtFi == eAPXzMflQS){fBROcYLllS = true;}
      else if(eAPXzMflQS == zMxzBAEtFi){mrBDnkhUiE = true;}
      if(yWLPVlUcwb == uFWMMhxrdH){nBoYmPjmiJ = true;}
      else if(uFWMMhxrdH == yWLPVlUcwb){DcZKThoHXF = true;}
      if(mUXmLVZdhM == gsLyYBoDpY){bUgHQqlCwb = true;}
      else if(gsLyYBoDpY == mUXmLVZdhM){XuMuqxaQEQ = true;}
      if(qEQIxsWiCp == VpmguSdFTC){brLItIodei = true;}
      if(nnknAkDgAO == EawXWyqiJh){aqMoVcXfiP = true;}
      if(xGrDReoJmf == QjNoYknQzx){pqURpLUKyl = true;}
      while(VpmguSdFTC == qEQIxsWiCp){jFsJAZDPsA = true;}
      while(EawXWyqiJh == EawXWyqiJh){CCKNfLEUXN = true;}
      while(QjNoYknQzx == QjNoYknQzx){bsesDqeGMq = true;}
      if(WcwqwESoRt == true){WcwqwESoRt = false;}
      if(EqXbDGxmbZ == true){EqXbDGxmbZ = false;}
      if(KGsIIlcyHK == true){KGsIIlcyHK = false;}
      if(dMFVeadEbS == true){dMFVeadEbS = false;}
      if(fBROcYLllS == true){fBROcYLllS = false;}
      if(nBoYmPjmiJ == true){nBoYmPjmiJ = false;}
      if(bUgHQqlCwb == true){bUgHQqlCwb = false;}
      if(brLItIodei == true){brLItIodei = false;}
      if(aqMoVcXfiP == true){aqMoVcXfiP = false;}
      if(pqURpLUKyl == true){pqURpLUKyl = false;}
      if(mJoJpuofee == true){mJoJpuofee = false;}
      if(aFIAikHrkn == true){aFIAikHrkn = false;}
      if(SFTgkkXtSi == true){SFTgkkXtSi = false;}
      if(nderuRBCya == true){nderuRBCya = false;}
      if(mrBDnkhUiE == true){mrBDnkhUiE = false;}
      if(DcZKThoHXF == true){DcZKThoHXF = false;}
      if(XuMuqxaQEQ == true){XuMuqxaQEQ = false;}
      if(jFsJAZDPsA == true){jFsJAZDPsA = false;}
      if(CCKNfLEUXN == true){CCKNfLEUXN = false;}
      if(bsesDqeGMq == true){bsesDqeGMq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCVOZCZFCH
{ 
  void wozyHfLQlC()
  { 
      bool tIfCEZlkjM = false;
      bool wpIfNjBbID = false;
      bool IIfABPwmAw = false;
      bool eGYISYQzsd = false;
      bool RCbIcfyyeR = false;
      bool XTjkXlbfBn = false;
      bool dyknhpQzMo = false;
      bool TCielGfXWU = false;
      bool RxIiXKVmkg = false;
      bool wkyEASQnZl = false;
      bool OykoxVkFyQ = false;
      bool FEIfWfpCPX = false;
      bool TdOfriDddT = false;
      bool orxjFSLSkC = false;
      bool YQnTarbRhT = false;
      bool bOYCRkjFxO = false;
      bool SHaebNGXaE = false;
      bool TWQMyDotFz = false;
      bool GlwKrZTuST = false;
      bool hGUWjRpJqM = false;
      string FHxPfzEVPu;
      string LawpCiWLdK;
      string ngqtyrCEZJ;
      string luyKYTWSLA;
      string CgfPBcBgGy;
      string odaZjYPDQn;
      string xzuGIQckRh;
      string LEzcHHAasV;
      string pUyaTITXZA;
      string ETBXDClZHj;
      string APPYmkeyRc;
      string XnJuybBTlA;
      string wELRdqDaYF;
      string VaTIUaFZni;
      string cVFxbPJGZa;
      string BRmHmuExtu;
      string gDYMHwUBZW;
      string WafCWazOoN;
      string hxBxDDmMUZ;
      string VHerCZwrof;
      if(FHxPfzEVPu == APPYmkeyRc){tIfCEZlkjM = true;}
      else if(APPYmkeyRc == FHxPfzEVPu){OykoxVkFyQ = true;}
      if(LawpCiWLdK == XnJuybBTlA){wpIfNjBbID = true;}
      else if(XnJuybBTlA == LawpCiWLdK){FEIfWfpCPX = true;}
      if(ngqtyrCEZJ == wELRdqDaYF){IIfABPwmAw = true;}
      else if(wELRdqDaYF == ngqtyrCEZJ){TdOfriDddT = true;}
      if(luyKYTWSLA == VaTIUaFZni){eGYISYQzsd = true;}
      else if(VaTIUaFZni == luyKYTWSLA){orxjFSLSkC = true;}
      if(CgfPBcBgGy == cVFxbPJGZa){RCbIcfyyeR = true;}
      else if(cVFxbPJGZa == CgfPBcBgGy){YQnTarbRhT = true;}
      if(odaZjYPDQn == BRmHmuExtu){XTjkXlbfBn = true;}
      else if(BRmHmuExtu == odaZjYPDQn){bOYCRkjFxO = true;}
      if(xzuGIQckRh == gDYMHwUBZW){dyknhpQzMo = true;}
      else if(gDYMHwUBZW == xzuGIQckRh){SHaebNGXaE = true;}
      if(LEzcHHAasV == WafCWazOoN){TCielGfXWU = true;}
      if(pUyaTITXZA == hxBxDDmMUZ){RxIiXKVmkg = true;}
      if(ETBXDClZHj == VHerCZwrof){wkyEASQnZl = true;}
      while(WafCWazOoN == LEzcHHAasV){TWQMyDotFz = true;}
      while(hxBxDDmMUZ == hxBxDDmMUZ){GlwKrZTuST = true;}
      while(VHerCZwrof == VHerCZwrof){hGUWjRpJqM = true;}
      if(tIfCEZlkjM == true){tIfCEZlkjM = false;}
      if(wpIfNjBbID == true){wpIfNjBbID = false;}
      if(IIfABPwmAw == true){IIfABPwmAw = false;}
      if(eGYISYQzsd == true){eGYISYQzsd = false;}
      if(RCbIcfyyeR == true){RCbIcfyyeR = false;}
      if(XTjkXlbfBn == true){XTjkXlbfBn = false;}
      if(dyknhpQzMo == true){dyknhpQzMo = false;}
      if(TCielGfXWU == true){TCielGfXWU = false;}
      if(RxIiXKVmkg == true){RxIiXKVmkg = false;}
      if(wkyEASQnZl == true){wkyEASQnZl = false;}
      if(OykoxVkFyQ == true){OykoxVkFyQ = false;}
      if(FEIfWfpCPX == true){FEIfWfpCPX = false;}
      if(TdOfriDddT == true){TdOfriDddT = false;}
      if(orxjFSLSkC == true){orxjFSLSkC = false;}
      if(YQnTarbRhT == true){YQnTarbRhT = false;}
      if(bOYCRkjFxO == true){bOYCRkjFxO = false;}
      if(SHaebNGXaE == true){SHaebNGXaE = false;}
      if(TWQMyDotFz == true){TWQMyDotFz = false;}
      if(GlwKrZTuST == true){GlwKrZTuST = false;}
      if(hGUWjRpJqM == true){hGUWjRpJqM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MCMJMALVKL
{ 
  void NqYwttVHyk()
  { 
      bool uWSkXlKRSS = false;
      bool iqQIYbqsMy = false;
      bool dGuYkgBCYf = false;
      bool glgGNRUtnc = false;
      bool uNRjawNlIi = false;
      bool NOBNfoasAp = false;
      bool kIslkxJKtH = false;
      bool HwEiDPoLyn = false;
      bool TOsoSSjSZY = false;
      bool patxrlTeyd = false;
      bool lCqBbQKSKP = false;
      bool zOuLWVOETS = false;
      bool MqkVQfCHqR = false;
      bool wKMTBQWrMB = false;
      bool HRIJYafhZW = false;
      bool XOKfRuRVku = false;
      bool OCarSoCaJG = false;
      bool yWqSKthawo = false;
      bool ATgTshzgCG = false;
      bool yBGRlFpPqj = false;
      string oDbwenolBC;
      string jgysRAAfNM;
      string LBTxzImFiJ;
      string BTaMyCKdfJ;
      string YfFQaejKeO;
      string cMFMmmiexW;
      string AiCrAQFltP;
      string oWzEmfuDVT;
      string XbaUgnNOYK;
      string SefJIpcNPK;
      string ZyQOYFMAYH;
      string qeJdyXHgKL;
      string CpMixKppwx;
      string ChnKsZLMwa;
      string aMpRTmVCKj;
      string hwCDIilgRN;
      string PWEbEJqyjY;
      string MukjkoAtPJ;
      string omfLPFfjCK;
      string nethLEHNMJ;
      if(oDbwenolBC == ZyQOYFMAYH){uWSkXlKRSS = true;}
      else if(ZyQOYFMAYH == oDbwenolBC){lCqBbQKSKP = true;}
      if(jgysRAAfNM == qeJdyXHgKL){iqQIYbqsMy = true;}
      else if(qeJdyXHgKL == jgysRAAfNM){zOuLWVOETS = true;}
      if(LBTxzImFiJ == CpMixKppwx){dGuYkgBCYf = true;}
      else if(CpMixKppwx == LBTxzImFiJ){MqkVQfCHqR = true;}
      if(BTaMyCKdfJ == ChnKsZLMwa){glgGNRUtnc = true;}
      else if(ChnKsZLMwa == BTaMyCKdfJ){wKMTBQWrMB = true;}
      if(YfFQaejKeO == aMpRTmVCKj){uNRjawNlIi = true;}
      else if(aMpRTmVCKj == YfFQaejKeO){HRIJYafhZW = true;}
      if(cMFMmmiexW == hwCDIilgRN){NOBNfoasAp = true;}
      else if(hwCDIilgRN == cMFMmmiexW){XOKfRuRVku = true;}
      if(AiCrAQFltP == PWEbEJqyjY){kIslkxJKtH = true;}
      else if(PWEbEJqyjY == AiCrAQFltP){OCarSoCaJG = true;}
      if(oWzEmfuDVT == MukjkoAtPJ){HwEiDPoLyn = true;}
      if(XbaUgnNOYK == omfLPFfjCK){TOsoSSjSZY = true;}
      if(SefJIpcNPK == nethLEHNMJ){patxrlTeyd = true;}
      while(MukjkoAtPJ == oWzEmfuDVT){yWqSKthawo = true;}
      while(omfLPFfjCK == omfLPFfjCK){ATgTshzgCG = true;}
      while(nethLEHNMJ == nethLEHNMJ){yBGRlFpPqj = true;}
      if(uWSkXlKRSS == true){uWSkXlKRSS = false;}
      if(iqQIYbqsMy == true){iqQIYbqsMy = false;}
      if(dGuYkgBCYf == true){dGuYkgBCYf = false;}
      if(glgGNRUtnc == true){glgGNRUtnc = false;}
      if(uNRjawNlIi == true){uNRjawNlIi = false;}
      if(NOBNfoasAp == true){NOBNfoasAp = false;}
      if(kIslkxJKtH == true){kIslkxJKtH = false;}
      if(HwEiDPoLyn == true){HwEiDPoLyn = false;}
      if(TOsoSSjSZY == true){TOsoSSjSZY = false;}
      if(patxrlTeyd == true){patxrlTeyd = false;}
      if(lCqBbQKSKP == true){lCqBbQKSKP = false;}
      if(zOuLWVOETS == true){zOuLWVOETS = false;}
      if(MqkVQfCHqR == true){MqkVQfCHqR = false;}
      if(wKMTBQWrMB == true){wKMTBQWrMB = false;}
      if(HRIJYafhZW == true){HRIJYafhZW = false;}
      if(XOKfRuRVku == true){XOKfRuRVku = false;}
      if(OCarSoCaJG == true){OCarSoCaJG = false;}
      if(yWqSKthawo == true){yWqSKthawo = false;}
      if(ATgTshzgCG == true){ATgTshzgCG = false;}
      if(yBGRlFpPqj == true){yBGRlFpPqj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LXVMYBKTPR
{ 
  void TEucUCHnmc()
  { 
      bool VqlYkTdSiQ = false;
      bool lXpTfLUdeZ = false;
      bool YhIGDRNIZq = false;
      bool srEADcNwRe = false;
      bool JacmxGgfSm = false;
      bool PioDamieUT = false;
      bool FVrrWtSpQD = false;
      bool yYMAQxEUJx = false;
      bool jhpmaKCBYP = false;
      bool thbyYmikQD = false;
      bool mqPOoqWold = false;
      bool iNVWiXeFQM = false;
      bool qRQAJPwOad = false;
      bool OSEFJsRayj = false;
      bool nNOuggLEOB = false;
      bool HcUELVZOFY = false;
      bool tHNIOPIPMo = false;
      bool FEHgYdCVTc = false;
      bool ErzZVlyAsn = false;
      bool TCUZofzGfQ = false;
      string kuelpNLtzL;
      string YBlkEFxRNn;
      string mTtlUEhdPR;
      string ORihphmSNI;
      string UWHJhckGDq;
      string SVObDQBsQl;
      string egegwGSEtV;
      string RdDFSQLjDr;
      string SaaXysDHdY;
      string gsBacmrZNa;
      string JgMhYnRIIl;
      string FQoYTDGGiC;
      string CLZUoYcbbe;
      string YlWbhkOszJ;
      string auyqTPEcHZ;
      string gkqKXyGqsA;
      string LpgdNTtMpi;
      string oNHYbHMiBY;
      string TzUCymtMDi;
      string eWzyykNUdA;
      if(kuelpNLtzL == JgMhYnRIIl){VqlYkTdSiQ = true;}
      else if(JgMhYnRIIl == kuelpNLtzL){mqPOoqWold = true;}
      if(YBlkEFxRNn == FQoYTDGGiC){lXpTfLUdeZ = true;}
      else if(FQoYTDGGiC == YBlkEFxRNn){iNVWiXeFQM = true;}
      if(mTtlUEhdPR == CLZUoYcbbe){YhIGDRNIZq = true;}
      else if(CLZUoYcbbe == mTtlUEhdPR){qRQAJPwOad = true;}
      if(ORihphmSNI == YlWbhkOszJ){srEADcNwRe = true;}
      else if(YlWbhkOszJ == ORihphmSNI){OSEFJsRayj = true;}
      if(UWHJhckGDq == auyqTPEcHZ){JacmxGgfSm = true;}
      else if(auyqTPEcHZ == UWHJhckGDq){nNOuggLEOB = true;}
      if(SVObDQBsQl == gkqKXyGqsA){PioDamieUT = true;}
      else if(gkqKXyGqsA == SVObDQBsQl){HcUELVZOFY = true;}
      if(egegwGSEtV == LpgdNTtMpi){FVrrWtSpQD = true;}
      else if(LpgdNTtMpi == egegwGSEtV){tHNIOPIPMo = true;}
      if(RdDFSQLjDr == oNHYbHMiBY){yYMAQxEUJx = true;}
      if(SaaXysDHdY == TzUCymtMDi){jhpmaKCBYP = true;}
      if(gsBacmrZNa == eWzyykNUdA){thbyYmikQD = true;}
      while(oNHYbHMiBY == RdDFSQLjDr){FEHgYdCVTc = true;}
      while(TzUCymtMDi == TzUCymtMDi){ErzZVlyAsn = true;}
      while(eWzyykNUdA == eWzyykNUdA){TCUZofzGfQ = true;}
      if(VqlYkTdSiQ == true){VqlYkTdSiQ = false;}
      if(lXpTfLUdeZ == true){lXpTfLUdeZ = false;}
      if(YhIGDRNIZq == true){YhIGDRNIZq = false;}
      if(srEADcNwRe == true){srEADcNwRe = false;}
      if(JacmxGgfSm == true){JacmxGgfSm = false;}
      if(PioDamieUT == true){PioDamieUT = false;}
      if(FVrrWtSpQD == true){FVrrWtSpQD = false;}
      if(yYMAQxEUJx == true){yYMAQxEUJx = false;}
      if(jhpmaKCBYP == true){jhpmaKCBYP = false;}
      if(thbyYmikQD == true){thbyYmikQD = false;}
      if(mqPOoqWold == true){mqPOoqWold = false;}
      if(iNVWiXeFQM == true){iNVWiXeFQM = false;}
      if(qRQAJPwOad == true){qRQAJPwOad = false;}
      if(OSEFJsRayj == true){OSEFJsRayj = false;}
      if(nNOuggLEOB == true){nNOuggLEOB = false;}
      if(HcUELVZOFY == true){HcUELVZOFY = false;}
      if(tHNIOPIPMo == true){tHNIOPIPMo = false;}
      if(FEHgYdCVTc == true){FEHgYdCVTc = false;}
      if(ErzZVlyAsn == true){ErzZVlyAsn = false;}
      if(TCUZofzGfQ == true){TCUZofzGfQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSVCDEMMGM
{ 
  void hUSTYBXCwj()
  { 
      bool nTbrQdjcpc = false;
      bool FKYwBhAide = false;
      bool VkfRmEinBX = false;
      bool UlsPEjnOxU = false;
      bool wDyyLKHFhZ = false;
      bool GoZkFCnJEL = false;
      bool uwaSITQJrQ = false;
      bool tklJhSmgGc = false;
      bool wdGaQeMIJB = false;
      bool wdKkYAbfpr = false;
      bool syNRfUDPDm = false;
      bool PGDaORpzBc = false;
      bool GIzpTQaAjh = false;
      bool pHpOjyQouw = false;
      bool awEWlpZiVH = false;
      bool KceNkkyWxO = false;
      bool sCfUxIPoqQ = false;
      bool BAEEBKDcEd = false;
      bool precXMccdy = false;
      bool AsqfCYQjYc = false;
      string XnAZKLLNik;
      string zZCRSfMyJT;
      string QbaOyRrrak;
      string GBbmuMSgqF;
      string LHDxhSVIDz;
      string FXRAKuNlas;
      string SSmydyyPVG;
      string NfGDIJYcgf;
      string ujoafhjacA;
      string ygFylsTFSj;
      string TGlxlYROrA;
      string VkEuxicMRw;
      string OXlVHfaIQO;
      string oTKxMoxroH;
      string QVhbdNbKAC;
      string PHmVVuUQpF;
      string yIxdLCZHhI;
      string lkWKfrpJqs;
      string EPHNzgfnbQ;
      string UgCiIHXEQb;
      if(XnAZKLLNik == TGlxlYROrA){nTbrQdjcpc = true;}
      else if(TGlxlYROrA == XnAZKLLNik){syNRfUDPDm = true;}
      if(zZCRSfMyJT == VkEuxicMRw){FKYwBhAide = true;}
      else if(VkEuxicMRw == zZCRSfMyJT){PGDaORpzBc = true;}
      if(QbaOyRrrak == OXlVHfaIQO){VkfRmEinBX = true;}
      else if(OXlVHfaIQO == QbaOyRrrak){GIzpTQaAjh = true;}
      if(GBbmuMSgqF == oTKxMoxroH){UlsPEjnOxU = true;}
      else if(oTKxMoxroH == GBbmuMSgqF){pHpOjyQouw = true;}
      if(LHDxhSVIDz == QVhbdNbKAC){wDyyLKHFhZ = true;}
      else if(QVhbdNbKAC == LHDxhSVIDz){awEWlpZiVH = true;}
      if(FXRAKuNlas == PHmVVuUQpF){GoZkFCnJEL = true;}
      else if(PHmVVuUQpF == FXRAKuNlas){KceNkkyWxO = true;}
      if(SSmydyyPVG == yIxdLCZHhI){uwaSITQJrQ = true;}
      else if(yIxdLCZHhI == SSmydyyPVG){sCfUxIPoqQ = true;}
      if(NfGDIJYcgf == lkWKfrpJqs){tklJhSmgGc = true;}
      if(ujoafhjacA == EPHNzgfnbQ){wdGaQeMIJB = true;}
      if(ygFylsTFSj == UgCiIHXEQb){wdKkYAbfpr = true;}
      while(lkWKfrpJqs == NfGDIJYcgf){BAEEBKDcEd = true;}
      while(EPHNzgfnbQ == EPHNzgfnbQ){precXMccdy = true;}
      while(UgCiIHXEQb == UgCiIHXEQb){AsqfCYQjYc = true;}
      if(nTbrQdjcpc == true){nTbrQdjcpc = false;}
      if(FKYwBhAide == true){FKYwBhAide = false;}
      if(VkfRmEinBX == true){VkfRmEinBX = false;}
      if(UlsPEjnOxU == true){UlsPEjnOxU = false;}
      if(wDyyLKHFhZ == true){wDyyLKHFhZ = false;}
      if(GoZkFCnJEL == true){GoZkFCnJEL = false;}
      if(uwaSITQJrQ == true){uwaSITQJrQ = false;}
      if(tklJhSmgGc == true){tklJhSmgGc = false;}
      if(wdGaQeMIJB == true){wdGaQeMIJB = false;}
      if(wdKkYAbfpr == true){wdKkYAbfpr = false;}
      if(syNRfUDPDm == true){syNRfUDPDm = false;}
      if(PGDaORpzBc == true){PGDaORpzBc = false;}
      if(GIzpTQaAjh == true){GIzpTQaAjh = false;}
      if(pHpOjyQouw == true){pHpOjyQouw = false;}
      if(awEWlpZiVH == true){awEWlpZiVH = false;}
      if(KceNkkyWxO == true){KceNkkyWxO = false;}
      if(sCfUxIPoqQ == true){sCfUxIPoqQ = false;}
      if(BAEEBKDcEd == true){BAEEBKDcEd = false;}
      if(precXMccdy == true){precXMccdy = false;}
      if(AsqfCYQjYc == true){AsqfCYQjYc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXWNTTBHLE
{ 
  void iECAYNjxKS()
  { 
      bool pegTPJxILZ = false;
      bool kofEOlkiPR = false;
      bool hEdRtcLiTQ = false;
      bool pteObtobWj = false;
      bool zQHmxMiDjm = false;
      bool cLUbxlBOZm = false;
      bool xOoujqKRcT = false;
      bool xJMeSRwqTg = false;
      bool tHzgmdZDRp = false;
      bool sZBjljbMDG = false;
      bool CRaPoTzoIe = false;
      bool oJusrpPHHF = false;
      bool QHzlZWHcsi = false;
      bool pjnMdbfiqS = false;
      bool ejtlAidIqu = false;
      bool TTExpuRopS = false;
      bool MVuZoFViOQ = false;
      bool JgQoZfMMlp = false;
      bool szkxPVepWi = false;
      bool JqrYFIoUwu = false;
      string AWrINFCaNr;
      string cyuakUGuQO;
      string LHLoVnURlq;
      string boDORHnVDc;
      string NlAiBhbShQ;
      string xkFfPrKCmZ;
      string kjoVQmugIc;
      string gkqnAYHcmm;
      string MBjVtpiXzZ;
      string wkhdrdxdRO;
      string muKEjLtRep;
      string khPANiASba;
      string DWgiguDMuW;
      string bcKYzQqflh;
      string uRrInNVgQI;
      string deCqLPNaWn;
      string IgVIOIXqAw;
      string rTgsekeYtS;
      string ZVwmswZTMi;
      string CPIyZOujsf;
      if(AWrINFCaNr == muKEjLtRep){pegTPJxILZ = true;}
      else if(muKEjLtRep == AWrINFCaNr){CRaPoTzoIe = true;}
      if(cyuakUGuQO == khPANiASba){kofEOlkiPR = true;}
      else if(khPANiASba == cyuakUGuQO){oJusrpPHHF = true;}
      if(LHLoVnURlq == DWgiguDMuW){hEdRtcLiTQ = true;}
      else if(DWgiguDMuW == LHLoVnURlq){QHzlZWHcsi = true;}
      if(boDORHnVDc == bcKYzQqflh){pteObtobWj = true;}
      else if(bcKYzQqflh == boDORHnVDc){pjnMdbfiqS = true;}
      if(NlAiBhbShQ == uRrInNVgQI){zQHmxMiDjm = true;}
      else if(uRrInNVgQI == NlAiBhbShQ){ejtlAidIqu = true;}
      if(xkFfPrKCmZ == deCqLPNaWn){cLUbxlBOZm = true;}
      else if(deCqLPNaWn == xkFfPrKCmZ){TTExpuRopS = true;}
      if(kjoVQmugIc == IgVIOIXqAw){xOoujqKRcT = true;}
      else if(IgVIOIXqAw == kjoVQmugIc){MVuZoFViOQ = true;}
      if(gkqnAYHcmm == rTgsekeYtS){xJMeSRwqTg = true;}
      if(MBjVtpiXzZ == ZVwmswZTMi){tHzgmdZDRp = true;}
      if(wkhdrdxdRO == CPIyZOujsf){sZBjljbMDG = true;}
      while(rTgsekeYtS == gkqnAYHcmm){JgQoZfMMlp = true;}
      while(ZVwmswZTMi == ZVwmswZTMi){szkxPVepWi = true;}
      while(CPIyZOujsf == CPIyZOujsf){JqrYFIoUwu = true;}
      if(pegTPJxILZ == true){pegTPJxILZ = false;}
      if(kofEOlkiPR == true){kofEOlkiPR = false;}
      if(hEdRtcLiTQ == true){hEdRtcLiTQ = false;}
      if(pteObtobWj == true){pteObtobWj = false;}
      if(zQHmxMiDjm == true){zQHmxMiDjm = false;}
      if(cLUbxlBOZm == true){cLUbxlBOZm = false;}
      if(xOoujqKRcT == true){xOoujqKRcT = false;}
      if(xJMeSRwqTg == true){xJMeSRwqTg = false;}
      if(tHzgmdZDRp == true){tHzgmdZDRp = false;}
      if(sZBjljbMDG == true){sZBjljbMDG = false;}
      if(CRaPoTzoIe == true){CRaPoTzoIe = false;}
      if(oJusrpPHHF == true){oJusrpPHHF = false;}
      if(QHzlZWHcsi == true){QHzlZWHcsi = false;}
      if(pjnMdbfiqS == true){pjnMdbfiqS = false;}
      if(ejtlAidIqu == true){ejtlAidIqu = false;}
      if(TTExpuRopS == true){TTExpuRopS = false;}
      if(MVuZoFViOQ == true){MVuZoFViOQ = false;}
      if(JgQoZfMMlp == true){JgQoZfMMlp = false;}
      if(szkxPVepWi == true){szkxPVepWi = false;}
      if(JqrYFIoUwu == true){JqrYFIoUwu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NIRAXPVQWN
{ 
  void MngigAmxYq()
  { 
      bool iJPNafwFwA = false;
      bool hkUmugcQwu = false;
      bool BwAoJhkbrP = false;
      bool MPVFDQroCR = false;
      bool HzpBiKiVGW = false;
      bool MytaemIaDs = false;
      bool tUNfmRPOjd = false;
      bool onOdmBFzGz = false;
      bool zPUVCNUuZP = false;
      bool IQkIXmlJNQ = false;
      bool tTkbgXjPmc = false;
      bool gJUDsdzrdY = false;
      bool xUnTVXCFGA = false;
      bool PwkoFedrnd = false;
      bool dEIwizwhOs = false;
      bool mtfnSZfRGI = false;
      bool VdJlNjXeyO = false;
      bool zHDztrMqkW = false;
      bool bUpMMVQwWf = false;
      bool zMleIAuViy = false;
      string AkJDVhaywr;
      string HpHhWplMrT;
      string VpwlJZukPs;
      string rbwqIcOast;
      string sMtdsYIFXi;
      string eUhsoJoXtw;
      string lpiDAetQYs;
      string bLSyaJwRrj;
      string QpNfNXsCCz;
      string npgxIDdpdN;
      string erfdHTBjRf;
      string MWfKeucCob;
      string lqOZEkdVpX;
      string eGndEYJiYs;
      string VJkWmRKVSM;
      string ZaBBbncGZV;
      string ofttAGhBFF;
      string ktduFbGrll;
      string ZICcxEElBQ;
      string uDICDpPpVg;
      if(AkJDVhaywr == erfdHTBjRf){iJPNafwFwA = true;}
      else if(erfdHTBjRf == AkJDVhaywr){tTkbgXjPmc = true;}
      if(HpHhWplMrT == MWfKeucCob){hkUmugcQwu = true;}
      else if(MWfKeucCob == HpHhWplMrT){gJUDsdzrdY = true;}
      if(VpwlJZukPs == lqOZEkdVpX){BwAoJhkbrP = true;}
      else if(lqOZEkdVpX == VpwlJZukPs){xUnTVXCFGA = true;}
      if(rbwqIcOast == eGndEYJiYs){MPVFDQroCR = true;}
      else if(eGndEYJiYs == rbwqIcOast){PwkoFedrnd = true;}
      if(sMtdsYIFXi == VJkWmRKVSM){HzpBiKiVGW = true;}
      else if(VJkWmRKVSM == sMtdsYIFXi){dEIwizwhOs = true;}
      if(eUhsoJoXtw == ZaBBbncGZV){MytaemIaDs = true;}
      else if(ZaBBbncGZV == eUhsoJoXtw){mtfnSZfRGI = true;}
      if(lpiDAetQYs == ofttAGhBFF){tUNfmRPOjd = true;}
      else if(ofttAGhBFF == lpiDAetQYs){VdJlNjXeyO = true;}
      if(bLSyaJwRrj == ktduFbGrll){onOdmBFzGz = true;}
      if(QpNfNXsCCz == ZICcxEElBQ){zPUVCNUuZP = true;}
      if(npgxIDdpdN == uDICDpPpVg){IQkIXmlJNQ = true;}
      while(ktduFbGrll == bLSyaJwRrj){zHDztrMqkW = true;}
      while(ZICcxEElBQ == ZICcxEElBQ){bUpMMVQwWf = true;}
      while(uDICDpPpVg == uDICDpPpVg){zMleIAuViy = true;}
      if(iJPNafwFwA == true){iJPNafwFwA = false;}
      if(hkUmugcQwu == true){hkUmugcQwu = false;}
      if(BwAoJhkbrP == true){BwAoJhkbrP = false;}
      if(MPVFDQroCR == true){MPVFDQroCR = false;}
      if(HzpBiKiVGW == true){HzpBiKiVGW = false;}
      if(MytaemIaDs == true){MytaemIaDs = false;}
      if(tUNfmRPOjd == true){tUNfmRPOjd = false;}
      if(onOdmBFzGz == true){onOdmBFzGz = false;}
      if(zPUVCNUuZP == true){zPUVCNUuZP = false;}
      if(IQkIXmlJNQ == true){IQkIXmlJNQ = false;}
      if(tTkbgXjPmc == true){tTkbgXjPmc = false;}
      if(gJUDsdzrdY == true){gJUDsdzrdY = false;}
      if(xUnTVXCFGA == true){xUnTVXCFGA = false;}
      if(PwkoFedrnd == true){PwkoFedrnd = false;}
      if(dEIwizwhOs == true){dEIwizwhOs = false;}
      if(mtfnSZfRGI == true){mtfnSZfRGI = false;}
      if(VdJlNjXeyO == true){VdJlNjXeyO = false;}
      if(zHDztrMqkW == true){zHDztrMqkW = false;}
      if(bUpMMVQwWf == true){bUpMMVQwWf = false;}
      if(zMleIAuViy == true){zMleIAuViy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CWBGGSMQRS
{ 
  void dZIalBOAHb()
  { 
      bool inMXKjrThJ = false;
      bool CpDWNAkSLW = false;
      bool oCkPHbZKTr = false;
      bool ITpQdCJsFl = false;
      bool CrNkmDppPq = false;
      bool IiVpMgDxQh = false;
      bool JgAoBiAlsK = false;
      bool prNZTwnzbD = false;
      bool ljtbjYxzEw = false;
      bool yMcWbVrXjE = false;
      bool CDxFAQVuWP = false;
      bool sEUMwZmXFb = false;
      bool kBhwMcPpyy = false;
      bool EPOWAilobT = false;
      bool DCcnDtqPZB = false;
      bool hUSITBUBrX = false;
      bool AexXLdoyLN = false;
      bool nyukYiXtrR = false;
      bool kzPwPjwGDz = false;
      bool NkwESXEEbZ = false;
      string aAbOGARQrc;
      string bgGmgKqdab;
      string KrKFxAICqs;
      string xOWzZnkjVK;
      string XdAlbfjCYq;
      string TDxeZhoWQF;
      string qOYyeMJHMs;
      string ZHHQDgrYcQ;
      string QFcAZtRrYr;
      string yNSPSJECGO;
      string VbpeQLugbs;
      string pQsAolkXXk;
      string uRhUuLorxs;
      string boROtnPxiN;
      string ykPeBhTSZg;
      string XgdVTEtVjF;
      string WDihRAyeFB;
      string VmnKmKBDSN;
      string qWRQVuLwtp;
      string tsNdqtBhNB;
      if(aAbOGARQrc == VbpeQLugbs){inMXKjrThJ = true;}
      else if(VbpeQLugbs == aAbOGARQrc){CDxFAQVuWP = true;}
      if(bgGmgKqdab == pQsAolkXXk){CpDWNAkSLW = true;}
      else if(pQsAolkXXk == bgGmgKqdab){sEUMwZmXFb = true;}
      if(KrKFxAICqs == uRhUuLorxs){oCkPHbZKTr = true;}
      else if(uRhUuLorxs == KrKFxAICqs){kBhwMcPpyy = true;}
      if(xOWzZnkjVK == boROtnPxiN){ITpQdCJsFl = true;}
      else if(boROtnPxiN == xOWzZnkjVK){EPOWAilobT = true;}
      if(XdAlbfjCYq == ykPeBhTSZg){CrNkmDppPq = true;}
      else if(ykPeBhTSZg == XdAlbfjCYq){DCcnDtqPZB = true;}
      if(TDxeZhoWQF == XgdVTEtVjF){IiVpMgDxQh = true;}
      else if(XgdVTEtVjF == TDxeZhoWQF){hUSITBUBrX = true;}
      if(qOYyeMJHMs == WDihRAyeFB){JgAoBiAlsK = true;}
      else if(WDihRAyeFB == qOYyeMJHMs){AexXLdoyLN = true;}
      if(ZHHQDgrYcQ == VmnKmKBDSN){prNZTwnzbD = true;}
      if(QFcAZtRrYr == qWRQVuLwtp){ljtbjYxzEw = true;}
      if(yNSPSJECGO == tsNdqtBhNB){yMcWbVrXjE = true;}
      while(VmnKmKBDSN == ZHHQDgrYcQ){nyukYiXtrR = true;}
      while(qWRQVuLwtp == qWRQVuLwtp){kzPwPjwGDz = true;}
      while(tsNdqtBhNB == tsNdqtBhNB){NkwESXEEbZ = true;}
      if(inMXKjrThJ == true){inMXKjrThJ = false;}
      if(CpDWNAkSLW == true){CpDWNAkSLW = false;}
      if(oCkPHbZKTr == true){oCkPHbZKTr = false;}
      if(ITpQdCJsFl == true){ITpQdCJsFl = false;}
      if(CrNkmDppPq == true){CrNkmDppPq = false;}
      if(IiVpMgDxQh == true){IiVpMgDxQh = false;}
      if(JgAoBiAlsK == true){JgAoBiAlsK = false;}
      if(prNZTwnzbD == true){prNZTwnzbD = false;}
      if(ljtbjYxzEw == true){ljtbjYxzEw = false;}
      if(yMcWbVrXjE == true){yMcWbVrXjE = false;}
      if(CDxFAQVuWP == true){CDxFAQVuWP = false;}
      if(sEUMwZmXFb == true){sEUMwZmXFb = false;}
      if(kBhwMcPpyy == true){kBhwMcPpyy = false;}
      if(EPOWAilobT == true){EPOWAilobT = false;}
      if(DCcnDtqPZB == true){DCcnDtqPZB = false;}
      if(hUSITBUBrX == true){hUSITBUBrX = false;}
      if(AexXLdoyLN == true){AexXLdoyLN = false;}
      if(nyukYiXtrR == true){nyukYiXtrR = false;}
      if(kzPwPjwGDz == true){kzPwPjwGDz = false;}
      if(NkwESXEEbZ == true){NkwESXEEbZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEFUXDOITN
{ 
  void bhXPSdDkKD()
  { 
      bool tFSEVZtpdZ = false;
      bool RJChfsYDjo = false;
      bool oODjfTHmXA = false;
      bool QolsfucuuD = false;
      bool McRFMUDHwu = false;
      bool KlnpweBiYC = false;
      bool SGRdJbXICk = false;
      bool QcIfcLxyWL = false;
      bool PAqboeAwwB = false;
      bool ssWrkGKmuj = false;
      bool wtFLegcINj = false;
      bool gDLMmSPooe = false;
      bool abMArWGPuW = false;
      bool BKDlOVufxH = false;
      bool BrhMUohJFS = false;
      bool pUxPJUhESH = false;
      bool aNMqiVzYyQ = false;
      bool XjrgdhszfC = false;
      bool owKbffMmcs = false;
      bool mpMpgmeqcy = false;
      string pMLsUqToac;
      string CCkPYLxQbe;
      string uuWKedpigp;
      string ituDSRkRVH;
      string GseCDnCAuy;
      string wjCpOupBOq;
      string BkIksIGhwH;
      string aftTYBQTGq;
      string apmhtzrFnX;
      string ajDeGVktIu;
      string gUEnXQohRM;
      string eVtWPKxapt;
      string PBsXfpbPMC;
      string QWKKJFlzKd;
      string JKmbsFofOu;
      string YKDOfebfIg;
      string nZUOwILiNK;
      string YyQMjFNRdZ;
      string AuARdGSwed;
      string dFpcojoYek;
      if(pMLsUqToac == gUEnXQohRM){tFSEVZtpdZ = true;}
      else if(gUEnXQohRM == pMLsUqToac){wtFLegcINj = true;}
      if(CCkPYLxQbe == eVtWPKxapt){RJChfsYDjo = true;}
      else if(eVtWPKxapt == CCkPYLxQbe){gDLMmSPooe = true;}
      if(uuWKedpigp == PBsXfpbPMC){oODjfTHmXA = true;}
      else if(PBsXfpbPMC == uuWKedpigp){abMArWGPuW = true;}
      if(ituDSRkRVH == QWKKJFlzKd){QolsfucuuD = true;}
      else if(QWKKJFlzKd == ituDSRkRVH){BKDlOVufxH = true;}
      if(GseCDnCAuy == JKmbsFofOu){McRFMUDHwu = true;}
      else if(JKmbsFofOu == GseCDnCAuy){BrhMUohJFS = true;}
      if(wjCpOupBOq == YKDOfebfIg){KlnpweBiYC = true;}
      else if(YKDOfebfIg == wjCpOupBOq){pUxPJUhESH = true;}
      if(BkIksIGhwH == nZUOwILiNK){SGRdJbXICk = true;}
      else if(nZUOwILiNK == BkIksIGhwH){aNMqiVzYyQ = true;}
      if(aftTYBQTGq == YyQMjFNRdZ){QcIfcLxyWL = true;}
      if(apmhtzrFnX == AuARdGSwed){PAqboeAwwB = true;}
      if(ajDeGVktIu == dFpcojoYek){ssWrkGKmuj = true;}
      while(YyQMjFNRdZ == aftTYBQTGq){XjrgdhszfC = true;}
      while(AuARdGSwed == AuARdGSwed){owKbffMmcs = true;}
      while(dFpcojoYek == dFpcojoYek){mpMpgmeqcy = true;}
      if(tFSEVZtpdZ == true){tFSEVZtpdZ = false;}
      if(RJChfsYDjo == true){RJChfsYDjo = false;}
      if(oODjfTHmXA == true){oODjfTHmXA = false;}
      if(QolsfucuuD == true){QolsfucuuD = false;}
      if(McRFMUDHwu == true){McRFMUDHwu = false;}
      if(KlnpweBiYC == true){KlnpweBiYC = false;}
      if(SGRdJbXICk == true){SGRdJbXICk = false;}
      if(QcIfcLxyWL == true){QcIfcLxyWL = false;}
      if(PAqboeAwwB == true){PAqboeAwwB = false;}
      if(ssWrkGKmuj == true){ssWrkGKmuj = false;}
      if(wtFLegcINj == true){wtFLegcINj = false;}
      if(gDLMmSPooe == true){gDLMmSPooe = false;}
      if(abMArWGPuW == true){abMArWGPuW = false;}
      if(BKDlOVufxH == true){BKDlOVufxH = false;}
      if(BrhMUohJFS == true){BrhMUohJFS = false;}
      if(pUxPJUhESH == true){pUxPJUhESH = false;}
      if(aNMqiVzYyQ == true){aNMqiVzYyQ = false;}
      if(XjrgdhszfC == true){XjrgdhszfC = false;}
      if(owKbffMmcs == true){owKbffMmcs = false;}
      if(mpMpgmeqcy == true){mpMpgmeqcy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQHXRKLROB
{ 
  void JbfFbxQWso()
  { 
      bool mpuYJIHZjH = false;
      bool VxrSeTJPdK = false;
      bool QdiGwWhrXw = false;
      bool TZPcYTueCB = false;
      bool HoUxoaGVUA = false;
      bool jgmRkJHocm = false;
      bool aPCnmugPsK = false;
      bool XdMbDaIkQU = false;
      bool QMWWLllxqO = false;
      bool MGCOarmgKs = false;
      bool tqbKcFTLOJ = false;
      bool BVXHWNrebA = false;
      bool JiXexQaxAK = false;
      bool naaXaZjMtG = false;
      bool SahgNqhtrM = false;
      bool zHEJjKSxML = false;
      bool dVKEVZtAfx = false;
      bool dejVhhBpQG = false;
      bool ifFmKfWRmQ = false;
      bool GlzibwQdLm = false;
      string JCCzNzpcgX;
      string LNbuVjhndJ;
      string jYmsadDRbQ;
      string HaekiACaMQ;
      string ujDlAscxiJ;
      string WngspjPJXi;
      string wYAPPkiqLU;
      string gHbMNzVAsh;
      string AFhStTskty;
      string ksCcUWimVP;
      string KlkOcPMTfq;
      string OOPoipphVw;
      string qxwNimEyqq;
      string QhecXNUTod;
      string GZFDiWcMte;
      string fARZYMpWeo;
      string KNbnZgimRU;
      string UWrqoRqseM;
      string KqEMKPPFEK;
      string XynATsxQcC;
      if(JCCzNzpcgX == KlkOcPMTfq){mpuYJIHZjH = true;}
      else if(KlkOcPMTfq == JCCzNzpcgX){tqbKcFTLOJ = true;}
      if(LNbuVjhndJ == OOPoipphVw){VxrSeTJPdK = true;}
      else if(OOPoipphVw == LNbuVjhndJ){BVXHWNrebA = true;}
      if(jYmsadDRbQ == qxwNimEyqq){QdiGwWhrXw = true;}
      else if(qxwNimEyqq == jYmsadDRbQ){JiXexQaxAK = true;}
      if(HaekiACaMQ == QhecXNUTod){TZPcYTueCB = true;}
      else if(QhecXNUTod == HaekiACaMQ){naaXaZjMtG = true;}
      if(ujDlAscxiJ == GZFDiWcMte){HoUxoaGVUA = true;}
      else if(GZFDiWcMte == ujDlAscxiJ){SahgNqhtrM = true;}
      if(WngspjPJXi == fARZYMpWeo){jgmRkJHocm = true;}
      else if(fARZYMpWeo == WngspjPJXi){zHEJjKSxML = true;}
      if(wYAPPkiqLU == KNbnZgimRU){aPCnmugPsK = true;}
      else if(KNbnZgimRU == wYAPPkiqLU){dVKEVZtAfx = true;}
      if(gHbMNzVAsh == UWrqoRqseM){XdMbDaIkQU = true;}
      if(AFhStTskty == KqEMKPPFEK){QMWWLllxqO = true;}
      if(ksCcUWimVP == XynATsxQcC){MGCOarmgKs = true;}
      while(UWrqoRqseM == gHbMNzVAsh){dejVhhBpQG = true;}
      while(KqEMKPPFEK == KqEMKPPFEK){ifFmKfWRmQ = true;}
      while(XynATsxQcC == XynATsxQcC){GlzibwQdLm = true;}
      if(mpuYJIHZjH == true){mpuYJIHZjH = false;}
      if(VxrSeTJPdK == true){VxrSeTJPdK = false;}
      if(QdiGwWhrXw == true){QdiGwWhrXw = false;}
      if(TZPcYTueCB == true){TZPcYTueCB = false;}
      if(HoUxoaGVUA == true){HoUxoaGVUA = false;}
      if(jgmRkJHocm == true){jgmRkJHocm = false;}
      if(aPCnmugPsK == true){aPCnmugPsK = false;}
      if(XdMbDaIkQU == true){XdMbDaIkQU = false;}
      if(QMWWLllxqO == true){QMWWLllxqO = false;}
      if(MGCOarmgKs == true){MGCOarmgKs = false;}
      if(tqbKcFTLOJ == true){tqbKcFTLOJ = false;}
      if(BVXHWNrebA == true){BVXHWNrebA = false;}
      if(JiXexQaxAK == true){JiXexQaxAK = false;}
      if(naaXaZjMtG == true){naaXaZjMtG = false;}
      if(SahgNqhtrM == true){SahgNqhtrM = false;}
      if(zHEJjKSxML == true){zHEJjKSxML = false;}
      if(dVKEVZtAfx == true){dVKEVZtAfx = false;}
      if(dejVhhBpQG == true){dejVhhBpQG = false;}
      if(ifFmKfWRmQ == true){ifFmKfWRmQ = false;}
      if(GlzibwQdLm == true){GlzibwQdLm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLZPXERWQL
{ 
  void BStzOotqzx()
  { 
      bool ipDxtVkFnc = false;
      bool ExcGIRcxTp = false;
      bool ldEmuCSYky = false;
      bool SIDFARmZCN = false;
      bool YWarHzseKR = false;
      bool phsLiFlPCr = false;
      bool CMToKwsXGq = false;
      bool dDtGQPCLfu = false;
      bool InNTHkOrVu = false;
      bool eXWKKMDlhK = false;
      bool FVYTnmmmtT = false;
      bool CajHiOyzgY = false;
      bool hBCKMGfjuE = false;
      bool MQdUomOsfU = false;
      bool yayCrEmPau = false;
      bool NDEIcESNHg = false;
      bool GDqpGlwPRw = false;
      bool AFTLaGDASH = false;
      bool SQIAqJLUqk = false;
      bool TAlyOuiHuF = false;
      string iHWXPOthiP;
      string lfQUUWNetm;
      string DeeDiNWhdd;
      string sdNVGSIdiL;
      string TJpPGgEeED;
      string kJthgEcTnB;
      string rLDEWHSuNB;
      string NiuiTtnOwB;
      string JrdZsijfnB;
      string pnohSIGlsy;
      string OJQCpBOKOm;
      string QNXmrAgcLm;
      string XmGMLYsNPK;
      string mBUxmAabjq;
      string UZQBkbQCoS;
      string acZFaaCEpQ;
      string IBtDzOrZzr;
      string YFrURxVFaj;
      string HpXxiJbOVM;
      string xWlTiTeNBV;
      if(iHWXPOthiP == OJQCpBOKOm){ipDxtVkFnc = true;}
      else if(OJQCpBOKOm == iHWXPOthiP){FVYTnmmmtT = true;}
      if(lfQUUWNetm == QNXmrAgcLm){ExcGIRcxTp = true;}
      else if(QNXmrAgcLm == lfQUUWNetm){CajHiOyzgY = true;}
      if(DeeDiNWhdd == XmGMLYsNPK){ldEmuCSYky = true;}
      else if(XmGMLYsNPK == DeeDiNWhdd){hBCKMGfjuE = true;}
      if(sdNVGSIdiL == mBUxmAabjq){SIDFARmZCN = true;}
      else if(mBUxmAabjq == sdNVGSIdiL){MQdUomOsfU = true;}
      if(TJpPGgEeED == UZQBkbQCoS){YWarHzseKR = true;}
      else if(UZQBkbQCoS == TJpPGgEeED){yayCrEmPau = true;}
      if(kJthgEcTnB == acZFaaCEpQ){phsLiFlPCr = true;}
      else if(acZFaaCEpQ == kJthgEcTnB){NDEIcESNHg = true;}
      if(rLDEWHSuNB == IBtDzOrZzr){CMToKwsXGq = true;}
      else if(IBtDzOrZzr == rLDEWHSuNB){GDqpGlwPRw = true;}
      if(NiuiTtnOwB == YFrURxVFaj){dDtGQPCLfu = true;}
      if(JrdZsijfnB == HpXxiJbOVM){InNTHkOrVu = true;}
      if(pnohSIGlsy == xWlTiTeNBV){eXWKKMDlhK = true;}
      while(YFrURxVFaj == NiuiTtnOwB){AFTLaGDASH = true;}
      while(HpXxiJbOVM == HpXxiJbOVM){SQIAqJLUqk = true;}
      while(xWlTiTeNBV == xWlTiTeNBV){TAlyOuiHuF = true;}
      if(ipDxtVkFnc == true){ipDxtVkFnc = false;}
      if(ExcGIRcxTp == true){ExcGIRcxTp = false;}
      if(ldEmuCSYky == true){ldEmuCSYky = false;}
      if(SIDFARmZCN == true){SIDFARmZCN = false;}
      if(YWarHzseKR == true){YWarHzseKR = false;}
      if(phsLiFlPCr == true){phsLiFlPCr = false;}
      if(CMToKwsXGq == true){CMToKwsXGq = false;}
      if(dDtGQPCLfu == true){dDtGQPCLfu = false;}
      if(InNTHkOrVu == true){InNTHkOrVu = false;}
      if(eXWKKMDlhK == true){eXWKKMDlhK = false;}
      if(FVYTnmmmtT == true){FVYTnmmmtT = false;}
      if(CajHiOyzgY == true){CajHiOyzgY = false;}
      if(hBCKMGfjuE == true){hBCKMGfjuE = false;}
      if(MQdUomOsfU == true){MQdUomOsfU = false;}
      if(yayCrEmPau == true){yayCrEmPau = false;}
      if(NDEIcESNHg == true){NDEIcESNHg = false;}
      if(GDqpGlwPRw == true){GDqpGlwPRw = false;}
      if(AFTLaGDASH == true){AFTLaGDASH = false;}
      if(SQIAqJLUqk == true){SQIAqJLUqk = false;}
      if(TAlyOuiHuF == true){TAlyOuiHuF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMKIPRJHKB
{ 
  void OpoATuxfQh()
  { 
      bool gVUFjNDgKF = false;
      bool XGfYLVDTpD = false;
      bool HlcAWicfgR = false;
      bool CqTzLOOFJY = false;
      bool POUIdKsJAz = false;
      bool sLgulusThA = false;
      bool jXArDflgNw = false;
      bool GyKRmrRTWM = false;
      bool pTegXpKYMQ = false;
      bool VuWInqObEy = false;
      bool XMuDsuBPHt = false;
      bool cYxUKQrSUM = false;
      bool UMTwZLaBcu = false;
      bool doOYndXbnb = false;
      bool ouQSmxxCyW = false;
      bool zwGrcLrzch = false;
      bool UAlMPmJYgg = false;
      bool sQdrXYwBJc = false;
      bool NYDGwhhWuc = false;
      bool kYyGHoJECA = false;
      string qpOSsbIuoc;
      string OZDXNQOdUG;
      string FTMEnMBkuX;
      string XpYGCyOrDc;
      string JtcGmAKkYt;
      string istkxXcJdf;
      string ZXzQFXAxUO;
      string BVarxKpFQm;
      string CQLAndwmIe;
      string VENWDkuLBP;
      string zNQKrNSCnm;
      string hWrpdJMzca;
      string bNnprwHDnL;
      string PeEBnozAHa;
      string LszVxzMXst;
      string YuiZmlYZRw;
      string FONbWCRpCn;
      string JLqBOhOSss;
      string jjKtlTueNB;
      string QZhLUxfWyt;
      if(qpOSsbIuoc == zNQKrNSCnm){gVUFjNDgKF = true;}
      else if(zNQKrNSCnm == qpOSsbIuoc){XMuDsuBPHt = true;}
      if(OZDXNQOdUG == hWrpdJMzca){XGfYLVDTpD = true;}
      else if(hWrpdJMzca == OZDXNQOdUG){cYxUKQrSUM = true;}
      if(FTMEnMBkuX == bNnprwHDnL){HlcAWicfgR = true;}
      else if(bNnprwHDnL == FTMEnMBkuX){UMTwZLaBcu = true;}
      if(XpYGCyOrDc == PeEBnozAHa){CqTzLOOFJY = true;}
      else if(PeEBnozAHa == XpYGCyOrDc){doOYndXbnb = true;}
      if(JtcGmAKkYt == LszVxzMXst){POUIdKsJAz = true;}
      else if(LszVxzMXst == JtcGmAKkYt){ouQSmxxCyW = true;}
      if(istkxXcJdf == YuiZmlYZRw){sLgulusThA = true;}
      else if(YuiZmlYZRw == istkxXcJdf){zwGrcLrzch = true;}
      if(ZXzQFXAxUO == FONbWCRpCn){jXArDflgNw = true;}
      else if(FONbWCRpCn == ZXzQFXAxUO){UAlMPmJYgg = true;}
      if(BVarxKpFQm == JLqBOhOSss){GyKRmrRTWM = true;}
      if(CQLAndwmIe == jjKtlTueNB){pTegXpKYMQ = true;}
      if(VENWDkuLBP == QZhLUxfWyt){VuWInqObEy = true;}
      while(JLqBOhOSss == BVarxKpFQm){sQdrXYwBJc = true;}
      while(jjKtlTueNB == jjKtlTueNB){NYDGwhhWuc = true;}
      while(QZhLUxfWyt == QZhLUxfWyt){kYyGHoJECA = true;}
      if(gVUFjNDgKF == true){gVUFjNDgKF = false;}
      if(XGfYLVDTpD == true){XGfYLVDTpD = false;}
      if(HlcAWicfgR == true){HlcAWicfgR = false;}
      if(CqTzLOOFJY == true){CqTzLOOFJY = false;}
      if(POUIdKsJAz == true){POUIdKsJAz = false;}
      if(sLgulusThA == true){sLgulusThA = false;}
      if(jXArDflgNw == true){jXArDflgNw = false;}
      if(GyKRmrRTWM == true){GyKRmrRTWM = false;}
      if(pTegXpKYMQ == true){pTegXpKYMQ = false;}
      if(VuWInqObEy == true){VuWInqObEy = false;}
      if(XMuDsuBPHt == true){XMuDsuBPHt = false;}
      if(cYxUKQrSUM == true){cYxUKQrSUM = false;}
      if(UMTwZLaBcu == true){UMTwZLaBcu = false;}
      if(doOYndXbnb == true){doOYndXbnb = false;}
      if(ouQSmxxCyW == true){ouQSmxxCyW = false;}
      if(zwGrcLrzch == true){zwGrcLrzch = false;}
      if(UAlMPmJYgg == true){UAlMPmJYgg = false;}
      if(sQdrXYwBJc == true){sQdrXYwBJc = false;}
      if(NYDGwhhWuc == true){NYDGwhhWuc = false;}
      if(kYyGHoJECA == true){kYyGHoJECA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVEYRBWPDS
{ 
  void clMzSOVmhu()
  { 
      bool AiuwKTdyor = false;
      bool rjokpUwXNo = false;
      bool fhTJVYYkLV = false;
      bool AZQKUSprCG = false;
      bool nLhRWwYSWr = false;
      bool caQczRPlal = false;
      bool urmTrSSdQX = false;
      bool eDVGATABmY = false;
      bool zFOTrYJmKC = false;
      bool DEQPKuYNZE = false;
      bool ctCyNYEJbf = false;
      bool RNyClpdSaS = false;
      bool IfSNUZmFuF = false;
      bool ulbiwFCPGT = false;
      bool TzLekoFOcU = false;
      bool QFmGuxaodm = false;
      bool lzNWkelPFg = false;
      bool mOMHzJTnce = false;
      bool TXcanozVny = false;
      bool dNkShUlntF = false;
      string MxfRRxRBfo;
      string aGrXlQhSbl;
      string gohUAnhfgF;
      string yMEIRlGVdp;
      string ZCphpULyjS;
      string YNgZgWPLQd;
      string OlTZpOBjGz;
      string KLnkMdyzde;
      string bjwOgjfebt;
      string WuFAamiQqa;
      string TbqjIMYuMC;
      string YPgkBdoFsG;
      string iWIMcPGnJY;
      string uhICLzrLGT;
      string KjRYVHNUyw;
      string ycXkrwTeHr;
      string GkknGpGdYB;
      string ldzYuzEipV;
      string BloMaRKXKO;
      string fNENMYzdRf;
      if(MxfRRxRBfo == TbqjIMYuMC){AiuwKTdyor = true;}
      else if(TbqjIMYuMC == MxfRRxRBfo){ctCyNYEJbf = true;}
      if(aGrXlQhSbl == YPgkBdoFsG){rjokpUwXNo = true;}
      else if(YPgkBdoFsG == aGrXlQhSbl){RNyClpdSaS = true;}
      if(gohUAnhfgF == iWIMcPGnJY){fhTJVYYkLV = true;}
      else if(iWIMcPGnJY == gohUAnhfgF){IfSNUZmFuF = true;}
      if(yMEIRlGVdp == uhICLzrLGT){AZQKUSprCG = true;}
      else if(uhICLzrLGT == yMEIRlGVdp){ulbiwFCPGT = true;}
      if(ZCphpULyjS == KjRYVHNUyw){nLhRWwYSWr = true;}
      else if(KjRYVHNUyw == ZCphpULyjS){TzLekoFOcU = true;}
      if(YNgZgWPLQd == ycXkrwTeHr){caQczRPlal = true;}
      else if(ycXkrwTeHr == YNgZgWPLQd){QFmGuxaodm = true;}
      if(OlTZpOBjGz == GkknGpGdYB){urmTrSSdQX = true;}
      else if(GkknGpGdYB == OlTZpOBjGz){lzNWkelPFg = true;}
      if(KLnkMdyzde == ldzYuzEipV){eDVGATABmY = true;}
      if(bjwOgjfebt == BloMaRKXKO){zFOTrYJmKC = true;}
      if(WuFAamiQqa == fNENMYzdRf){DEQPKuYNZE = true;}
      while(ldzYuzEipV == KLnkMdyzde){mOMHzJTnce = true;}
      while(BloMaRKXKO == BloMaRKXKO){TXcanozVny = true;}
      while(fNENMYzdRf == fNENMYzdRf){dNkShUlntF = true;}
      if(AiuwKTdyor == true){AiuwKTdyor = false;}
      if(rjokpUwXNo == true){rjokpUwXNo = false;}
      if(fhTJVYYkLV == true){fhTJVYYkLV = false;}
      if(AZQKUSprCG == true){AZQKUSprCG = false;}
      if(nLhRWwYSWr == true){nLhRWwYSWr = false;}
      if(caQczRPlal == true){caQczRPlal = false;}
      if(urmTrSSdQX == true){urmTrSSdQX = false;}
      if(eDVGATABmY == true){eDVGATABmY = false;}
      if(zFOTrYJmKC == true){zFOTrYJmKC = false;}
      if(DEQPKuYNZE == true){DEQPKuYNZE = false;}
      if(ctCyNYEJbf == true){ctCyNYEJbf = false;}
      if(RNyClpdSaS == true){RNyClpdSaS = false;}
      if(IfSNUZmFuF == true){IfSNUZmFuF = false;}
      if(ulbiwFCPGT == true){ulbiwFCPGT = false;}
      if(TzLekoFOcU == true){TzLekoFOcU = false;}
      if(QFmGuxaodm == true){QFmGuxaodm = false;}
      if(lzNWkelPFg == true){lzNWkelPFg = false;}
      if(mOMHzJTnce == true){mOMHzJTnce = false;}
      if(TXcanozVny == true){TXcanozVny = false;}
      if(dNkShUlntF == true){dNkShUlntF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSQTWHXKVJ
{ 
  void emZkHzeqMQ()
  { 
      bool kneYoyGPgb = false;
      bool JfgnXPfkaD = false;
      bool WfMyopnmAk = false;
      bool xbdsCdUndT = false;
      bool aqcSRFBzoZ = false;
      bool SXKwOFafjy = false;
      bool KTPudgBnls = false;
      bool trHHceCsgi = false;
      bool onxZSZRhdw = false;
      bool CnDeIHbhoj = false;
      bool EMMweZPCTi = false;
      bool DhzAJVWocE = false;
      bool PTKppFoczV = false;
      bool DUEwebbAur = false;
      bool JONtsUoCUl = false;
      bool jmFjUkCWFY = false;
      bool kmDyfhcDVh = false;
      bool tVsjtBFPwU = false;
      bool QlHMkPPTat = false;
      bool YEtWGWKONK = false;
      string snVsdnDaNQ;
      string aYTQuuOzZX;
      string anxEyhPGMn;
      string nFMnMlybRH;
      string OZaYYeILAC;
      string KnEuaEqQtu;
      string YxOYcVLeDJ;
      string wmhRJANXfT;
      string YDGJczBRNH;
      string tggViQLBuC;
      string ScIpFWGmla;
      string qSkaVUqEwd;
      string UtRuOOGMhr;
      string oMbcAwuPEG;
      string sNflQbwFzO;
      string ZGFRhYKMbp;
      string QsEsldpHaZ;
      string YaAokGOeem;
      string SAMSRhHKub;
      string kimNozJlAl;
      if(snVsdnDaNQ == ScIpFWGmla){kneYoyGPgb = true;}
      else if(ScIpFWGmla == snVsdnDaNQ){EMMweZPCTi = true;}
      if(aYTQuuOzZX == qSkaVUqEwd){JfgnXPfkaD = true;}
      else if(qSkaVUqEwd == aYTQuuOzZX){DhzAJVWocE = true;}
      if(anxEyhPGMn == UtRuOOGMhr){WfMyopnmAk = true;}
      else if(UtRuOOGMhr == anxEyhPGMn){PTKppFoczV = true;}
      if(nFMnMlybRH == oMbcAwuPEG){xbdsCdUndT = true;}
      else if(oMbcAwuPEG == nFMnMlybRH){DUEwebbAur = true;}
      if(OZaYYeILAC == sNflQbwFzO){aqcSRFBzoZ = true;}
      else if(sNflQbwFzO == OZaYYeILAC){JONtsUoCUl = true;}
      if(KnEuaEqQtu == ZGFRhYKMbp){SXKwOFafjy = true;}
      else if(ZGFRhYKMbp == KnEuaEqQtu){jmFjUkCWFY = true;}
      if(YxOYcVLeDJ == QsEsldpHaZ){KTPudgBnls = true;}
      else if(QsEsldpHaZ == YxOYcVLeDJ){kmDyfhcDVh = true;}
      if(wmhRJANXfT == YaAokGOeem){trHHceCsgi = true;}
      if(YDGJczBRNH == SAMSRhHKub){onxZSZRhdw = true;}
      if(tggViQLBuC == kimNozJlAl){CnDeIHbhoj = true;}
      while(YaAokGOeem == wmhRJANXfT){tVsjtBFPwU = true;}
      while(SAMSRhHKub == SAMSRhHKub){QlHMkPPTat = true;}
      while(kimNozJlAl == kimNozJlAl){YEtWGWKONK = true;}
      if(kneYoyGPgb == true){kneYoyGPgb = false;}
      if(JfgnXPfkaD == true){JfgnXPfkaD = false;}
      if(WfMyopnmAk == true){WfMyopnmAk = false;}
      if(xbdsCdUndT == true){xbdsCdUndT = false;}
      if(aqcSRFBzoZ == true){aqcSRFBzoZ = false;}
      if(SXKwOFafjy == true){SXKwOFafjy = false;}
      if(KTPudgBnls == true){KTPudgBnls = false;}
      if(trHHceCsgi == true){trHHceCsgi = false;}
      if(onxZSZRhdw == true){onxZSZRhdw = false;}
      if(CnDeIHbhoj == true){CnDeIHbhoj = false;}
      if(EMMweZPCTi == true){EMMweZPCTi = false;}
      if(DhzAJVWocE == true){DhzAJVWocE = false;}
      if(PTKppFoczV == true){PTKppFoczV = false;}
      if(DUEwebbAur == true){DUEwebbAur = false;}
      if(JONtsUoCUl == true){JONtsUoCUl = false;}
      if(jmFjUkCWFY == true){jmFjUkCWFY = false;}
      if(kmDyfhcDVh == true){kmDyfhcDVh = false;}
      if(tVsjtBFPwU == true){tVsjtBFPwU = false;}
      if(QlHMkPPTat == true){QlHMkPPTat = false;}
      if(YEtWGWKONK == true){YEtWGWKONK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHFOBMOTMR
{ 
  void SDhzNHxrHG()
  { 
      bool UCZxekeSfj = false;
      bool LBTaKTbMyE = false;
      bool QhCQaxBwLV = false;
      bool BFlDSJJUaQ = false;
      bool wQFjSVpTDC = false;
      bool BApgZlzJWg = false;
      bool ihHKhGOQHA = false;
      bool KHlgIzbSyE = false;
      bool HhsITAOEdg = false;
      bool KAxshNJuBL = false;
      bool GZMCrtOJYZ = false;
      bool JgKRZAoyph = false;
      bool qJmZpJJryt = false;
      bool ogRlxhVpQY = false;
      bool lFfDWcofTg = false;
      bool YLETUxllMh = false;
      bool kVKdjbPYTq = false;
      bool ezgRuldiDM = false;
      bool UdXRVdcxRA = false;
      bool ujdimQtCSt = false;
      string gmqTrfzuwB;
      string rjRZmNMJUM;
      string fyepQhgtDC;
      string wGdMLiOECN;
      string qdDIesUMtI;
      string SPQFyhIACJ;
      string yEqsEkGEND;
      string zHGGVCuVLW;
      string NUzujgpYNc;
      string aNBrPllJDs;
      string mPyqJKIJjw;
      string llnfwdEwIX;
      string uhpkckGOqi;
      string QkRSjxWIlZ;
      string XfnRqnYVwk;
      string goBfyFZNOX;
      string DtSAfATVuy;
      string GwKhzOsXsn;
      string MjRFCajlTe;
      string XJtNWdNnlp;
      if(gmqTrfzuwB == mPyqJKIJjw){UCZxekeSfj = true;}
      else if(mPyqJKIJjw == gmqTrfzuwB){GZMCrtOJYZ = true;}
      if(rjRZmNMJUM == llnfwdEwIX){LBTaKTbMyE = true;}
      else if(llnfwdEwIX == rjRZmNMJUM){JgKRZAoyph = true;}
      if(fyepQhgtDC == uhpkckGOqi){QhCQaxBwLV = true;}
      else if(uhpkckGOqi == fyepQhgtDC){qJmZpJJryt = true;}
      if(wGdMLiOECN == QkRSjxWIlZ){BFlDSJJUaQ = true;}
      else if(QkRSjxWIlZ == wGdMLiOECN){ogRlxhVpQY = true;}
      if(qdDIesUMtI == XfnRqnYVwk){wQFjSVpTDC = true;}
      else if(XfnRqnYVwk == qdDIesUMtI){lFfDWcofTg = true;}
      if(SPQFyhIACJ == goBfyFZNOX){BApgZlzJWg = true;}
      else if(goBfyFZNOX == SPQFyhIACJ){YLETUxllMh = true;}
      if(yEqsEkGEND == DtSAfATVuy){ihHKhGOQHA = true;}
      else if(DtSAfATVuy == yEqsEkGEND){kVKdjbPYTq = true;}
      if(zHGGVCuVLW == GwKhzOsXsn){KHlgIzbSyE = true;}
      if(NUzujgpYNc == MjRFCajlTe){HhsITAOEdg = true;}
      if(aNBrPllJDs == XJtNWdNnlp){KAxshNJuBL = true;}
      while(GwKhzOsXsn == zHGGVCuVLW){ezgRuldiDM = true;}
      while(MjRFCajlTe == MjRFCajlTe){UdXRVdcxRA = true;}
      while(XJtNWdNnlp == XJtNWdNnlp){ujdimQtCSt = true;}
      if(UCZxekeSfj == true){UCZxekeSfj = false;}
      if(LBTaKTbMyE == true){LBTaKTbMyE = false;}
      if(QhCQaxBwLV == true){QhCQaxBwLV = false;}
      if(BFlDSJJUaQ == true){BFlDSJJUaQ = false;}
      if(wQFjSVpTDC == true){wQFjSVpTDC = false;}
      if(BApgZlzJWg == true){BApgZlzJWg = false;}
      if(ihHKhGOQHA == true){ihHKhGOQHA = false;}
      if(KHlgIzbSyE == true){KHlgIzbSyE = false;}
      if(HhsITAOEdg == true){HhsITAOEdg = false;}
      if(KAxshNJuBL == true){KAxshNJuBL = false;}
      if(GZMCrtOJYZ == true){GZMCrtOJYZ = false;}
      if(JgKRZAoyph == true){JgKRZAoyph = false;}
      if(qJmZpJJryt == true){qJmZpJJryt = false;}
      if(ogRlxhVpQY == true){ogRlxhVpQY = false;}
      if(lFfDWcofTg == true){lFfDWcofTg = false;}
      if(YLETUxllMh == true){YLETUxllMh = false;}
      if(kVKdjbPYTq == true){kVKdjbPYTq = false;}
      if(ezgRuldiDM == true){ezgRuldiDM = false;}
      if(UdXRVdcxRA == true){UdXRVdcxRA = false;}
      if(ujdimQtCSt == true){ujdimQtCSt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RODWHFSXZN
{ 
  void bHtcCqOuPo()
  { 
      bool JshHDNDhum = false;
      bool tuTnbYYOeC = false;
      bool LOUOAjDGSZ = false;
      bool OOJEQbtRAM = false;
      bool SAuaIgRZxb = false;
      bool SQaojuXSHT = false;
      bool KwOUXekOWA = false;
      bool eHOSiKSsFT = false;
      bool RcJqHynUTV = false;
      bool DaKfCWlZDc = false;
      bool uCDwwLBHFZ = false;
      bool beMmBglXNZ = false;
      bool qQtBwDwiQM = false;
      bool YrpcXPZMtu = false;
      bool wfOtsYNWeU = false;
      bool jNMcldHBAr = false;
      bool PSqrAjojPk = false;
      bool GZcRdKCAHX = false;
      bool pYDucKfMqs = false;
      bool IXMBfcoVtJ = false;
      string MypWJqVjTZ;
      string HRgRVMzgbZ;
      string DbMnTRuxOT;
      string NTLTFIJmgy;
      string xIVkPDbZQx;
      string oKZnYjkCCr;
      string wYUzMnFMMM;
      string DMAdctGbXQ;
      string oUfRdCtXuU;
      string XGknBXmVXb;
      string xONDtcKuLe;
      string dIekDbsDUK;
      string shRrowbLcF;
      string GjEwSZGbWB;
      string qyMQpObzkY;
      string ejBNhPxUOx;
      string BzSFYtEiRc;
      string UQfTSuUBBa;
      string UbZDZVhpND;
      string ckNZArfGqw;
      if(MypWJqVjTZ == xONDtcKuLe){JshHDNDhum = true;}
      else if(xONDtcKuLe == MypWJqVjTZ){uCDwwLBHFZ = true;}
      if(HRgRVMzgbZ == dIekDbsDUK){tuTnbYYOeC = true;}
      else if(dIekDbsDUK == HRgRVMzgbZ){beMmBglXNZ = true;}
      if(DbMnTRuxOT == shRrowbLcF){LOUOAjDGSZ = true;}
      else if(shRrowbLcF == DbMnTRuxOT){qQtBwDwiQM = true;}
      if(NTLTFIJmgy == GjEwSZGbWB){OOJEQbtRAM = true;}
      else if(GjEwSZGbWB == NTLTFIJmgy){YrpcXPZMtu = true;}
      if(xIVkPDbZQx == qyMQpObzkY){SAuaIgRZxb = true;}
      else if(qyMQpObzkY == xIVkPDbZQx){wfOtsYNWeU = true;}
      if(oKZnYjkCCr == ejBNhPxUOx){SQaojuXSHT = true;}
      else if(ejBNhPxUOx == oKZnYjkCCr){jNMcldHBAr = true;}
      if(wYUzMnFMMM == BzSFYtEiRc){KwOUXekOWA = true;}
      else if(BzSFYtEiRc == wYUzMnFMMM){PSqrAjojPk = true;}
      if(DMAdctGbXQ == UQfTSuUBBa){eHOSiKSsFT = true;}
      if(oUfRdCtXuU == UbZDZVhpND){RcJqHynUTV = true;}
      if(XGknBXmVXb == ckNZArfGqw){DaKfCWlZDc = true;}
      while(UQfTSuUBBa == DMAdctGbXQ){GZcRdKCAHX = true;}
      while(UbZDZVhpND == UbZDZVhpND){pYDucKfMqs = true;}
      while(ckNZArfGqw == ckNZArfGqw){IXMBfcoVtJ = true;}
      if(JshHDNDhum == true){JshHDNDhum = false;}
      if(tuTnbYYOeC == true){tuTnbYYOeC = false;}
      if(LOUOAjDGSZ == true){LOUOAjDGSZ = false;}
      if(OOJEQbtRAM == true){OOJEQbtRAM = false;}
      if(SAuaIgRZxb == true){SAuaIgRZxb = false;}
      if(SQaojuXSHT == true){SQaojuXSHT = false;}
      if(KwOUXekOWA == true){KwOUXekOWA = false;}
      if(eHOSiKSsFT == true){eHOSiKSsFT = false;}
      if(RcJqHynUTV == true){RcJqHynUTV = false;}
      if(DaKfCWlZDc == true){DaKfCWlZDc = false;}
      if(uCDwwLBHFZ == true){uCDwwLBHFZ = false;}
      if(beMmBglXNZ == true){beMmBglXNZ = false;}
      if(qQtBwDwiQM == true){qQtBwDwiQM = false;}
      if(YrpcXPZMtu == true){YrpcXPZMtu = false;}
      if(wfOtsYNWeU == true){wfOtsYNWeU = false;}
      if(jNMcldHBAr == true){jNMcldHBAr = false;}
      if(PSqrAjojPk == true){PSqrAjojPk = false;}
      if(GZcRdKCAHX == true){GZcRdKCAHX = false;}
      if(pYDucKfMqs == true){pYDucKfMqs = false;}
      if(IXMBfcoVtJ == true){IXMBfcoVtJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTPSUJHQLW
{ 
  void hkKuwPZhum()
  { 
      bool xESCGiwiqH = false;
      bool OUugcgxuLZ = false;
      bool ZOTElntbFf = false;
      bool BJfHDaeiZj = false;
      bool iCtUfaLxKr = false;
      bool JBSbAijNQR = false;
      bool nTdLFFnncB = false;
      bool COVbqXUzYK = false;
      bool cxRMWApDGU = false;
      bool qQSIuPYhOZ = false;
      bool lWUJpufqkc = false;
      bool OjnGnqCQnF = false;
      bool PkhIKkuMfb = false;
      bool ylkzXFcHWb = false;
      bool TyRcGGcMTD = false;
      bool MHtIKBoLyE = false;
      bool zSKJdczohh = false;
      bool OtsMkQTEBD = false;
      bool IisbOprboW = false;
      bool QQJSbBnHzd = false;
      string pLlHMXdfKV;
      string WEaeYfpbVB;
      string pfRwMmFtia;
      string qOqaJJUKoC;
      string eWhokNtUxy;
      string asdbSKtouY;
      string SixjdHMzUO;
      string KelSVSybLy;
      string skwjzyjPIz;
      string PePPjuZyKc;
      string AtzinuGLFz;
      string LRdxfhmMje;
      string WxqVzfPWia;
      string sARhxykNwE;
      string qYJImxASjC;
      string IMOfFCCdiI;
      string ejbeGLAwzg;
      string wYQenynhhB;
      string exlfSflkbt;
      string uHenZHweCa;
      if(pLlHMXdfKV == AtzinuGLFz){xESCGiwiqH = true;}
      else if(AtzinuGLFz == pLlHMXdfKV){lWUJpufqkc = true;}
      if(WEaeYfpbVB == LRdxfhmMje){OUugcgxuLZ = true;}
      else if(LRdxfhmMje == WEaeYfpbVB){OjnGnqCQnF = true;}
      if(pfRwMmFtia == WxqVzfPWia){ZOTElntbFf = true;}
      else if(WxqVzfPWia == pfRwMmFtia){PkhIKkuMfb = true;}
      if(qOqaJJUKoC == sARhxykNwE){BJfHDaeiZj = true;}
      else if(sARhxykNwE == qOqaJJUKoC){ylkzXFcHWb = true;}
      if(eWhokNtUxy == qYJImxASjC){iCtUfaLxKr = true;}
      else if(qYJImxASjC == eWhokNtUxy){TyRcGGcMTD = true;}
      if(asdbSKtouY == IMOfFCCdiI){JBSbAijNQR = true;}
      else if(IMOfFCCdiI == asdbSKtouY){MHtIKBoLyE = true;}
      if(SixjdHMzUO == ejbeGLAwzg){nTdLFFnncB = true;}
      else if(ejbeGLAwzg == SixjdHMzUO){zSKJdczohh = true;}
      if(KelSVSybLy == wYQenynhhB){COVbqXUzYK = true;}
      if(skwjzyjPIz == exlfSflkbt){cxRMWApDGU = true;}
      if(PePPjuZyKc == uHenZHweCa){qQSIuPYhOZ = true;}
      while(wYQenynhhB == KelSVSybLy){OtsMkQTEBD = true;}
      while(exlfSflkbt == exlfSflkbt){IisbOprboW = true;}
      while(uHenZHweCa == uHenZHweCa){QQJSbBnHzd = true;}
      if(xESCGiwiqH == true){xESCGiwiqH = false;}
      if(OUugcgxuLZ == true){OUugcgxuLZ = false;}
      if(ZOTElntbFf == true){ZOTElntbFf = false;}
      if(BJfHDaeiZj == true){BJfHDaeiZj = false;}
      if(iCtUfaLxKr == true){iCtUfaLxKr = false;}
      if(JBSbAijNQR == true){JBSbAijNQR = false;}
      if(nTdLFFnncB == true){nTdLFFnncB = false;}
      if(COVbqXUzYK == true){COVbqXUzYK = false;}
      if(cxRMWApDGU == true){cxRMWApDGU = false;}
      if(qQSIuPYhOZ == true){qQSIuPYhOZ = false;}
      if(lWUJpufqkc == true){lWUJpufqkc = false;}
      if(OjnGnqCQnF == true){OjnGnqCQnF = false;}
      if(PkhIKkuMfb == true){PkhIKkuMfb = false;}
      if(ylkzXFcHWb == true){ylkzXFcHWb = false;}
      if(TyRcGGcMTD == true){TyRcGGcMTD = false;}
      if(MHtIKBoLyE == true){MHtIKBoLyE = false;}
      if(zSKJdczohh == true){zSKJdczohh = false;}
      if(OtsMkQTEBD == true){OtsMkQTEBD = false;}
      if(IisbOprboW == true){IisbOprboW = false;}
      if(QQJSbBnHzd == true){QQJSbBnHzd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUBOCSZVTO
{ 
  void drwkDKaGmp()
  { 
      bool fqGmJOXyem = false;
      bool pSfEwxsfnr = false;
      bool nbOcXancIE = false;
      bool zFacKNnOKg = false;
      bool RVYwigQQpi = false;
      bool ZdGHQEccOi = false;
      bool ZuoZmjqDti = false;
      bool JeUGaRCRtp = false;
      bool KXlYeVzSLF = false;
      bool jKzbHWfyJz = false;
      bool oNVHYuIzgy = false;
      bool BKiXXBIPuR = false;
      bool kYqnyzeszD = false;
      bool lDIuBxBeAi = false;
      bool MzkNDZbaEF = false;
      bool OPDrNQVgIZ = false;
      bool PPAcMyBmWa = false;
      bool AcPLEkmdkX = false;
      bool WEosoVAQgj = false;
      bool aUVZTxzIAF = false;
      string cplqdIEWkZ;
      string bWictJVgpC;
      string rBBHgMDQmz;
      string QnFbEpxnsW;
      string kYoBHpMhCG;
      string dtXUfbodKQ;
      string EnikJmRHXE;
      string MgmTQTLAAp;
      string zVOgVVQjwc;
      string BSdbRxpDqT;
      string YFJytwGEEM;
      string PndTRiZCPn;
      string WgLuCsDLCT;
      string dIIfQtLPmZ;
      string OLfiMMoJKh;
      string XmnDxqtOuA;
      string ruBjiHfxCW;
      string XJPpYKBbhp;
      string EtBUupTEiZ;
      string zxUlgTKuAE;
      if(cplqdIEWkZ == YFJytwGEEM){fqGmJOXyem = true;}
      else if(YFJytwGEEM == cplqdIEWkZ){oNVHYuIzgy = true;}
      if(bWictJVgpC == PndTRiZCPn){pSfEwxsfnr = true;}
      else if(PndTRiZCPn == bWictJVgpC){BKiXXBIPuR = true;}
      if(rBBHgMDQmz == WgLuCsDLCT){nbOcXancIE = true;}
      else if(WgLuCsDLCT == rBBHgMDQmz){kYqnyzeszD = true;}
      if(QnFbEpxnsW == dIIfQtLPmZ){zFacKNnOKg = true;}
      else if(dIIfQtLPmZ == QnFbEpxnsW){lDIuBxBeAi = true;}
      if(kYoBHpMhCG == OLfiMMoJKh){RVYwigQQpi = true;}
      else if(OLfiMMoJKh == kYoBHpMhCG){MzkNDZbaEF = true;}
      if(dtXUfbodKQ == XmnDxqtOuA){ZdGHQEccOi = true;}
      else if(XmnDxqtOuA == dtXUfbodKQ){OPDrNQVgIZ = true;}
      if(EnikJmRHXE == ruBjiHfxCW){ZuoZmjqDti = true;}
      else if(ruBjiHfxCW == EnikJmRHXE){PPAcMyBmWa = true;}
      if(MgmTQTLAAp == XJPpYKBbhp){JeUGaRCRtp = true;}
      if(zVOgVVQjwc == EtBUupTEiZ){KXlYeVzSLF = true;}
      if(BSdbRxpDqT == zxUlgTKuAE){jKzbHWfyJz = true;}
      while(XJPpYKBbhp == MgmTQTLAAp){AcPLEkmdkX = true;}
      while(EtBUupTEiZ == EtBUupTEiZ){WEosoVAQgj = true;}
      while(zxUlgTKuAE == zxUlgTKuAE){aUVZTxzIAF = true;}
      if(fqGmJOXyem == true){fqGmJOXyem = false;}
      if(pSfEwxsfnr == true){pSfEwxsfnr = false;}
      if(nbOcXancIE == true){nbOcXancIE = false;}
      if(zFacKNnOKg == true){zFacKNnOKg = false;}
      if(RVYwigQQpi == true){RVYwigQQpi = false;}
      if(ZdGHQEccOi == true){ZdGHQEccOi = false;}
      if(ZuoZmjqDti == true){ZuoZmjqDti = false;}
      if(JeUGaRCRtp == true){JeUGaRCRtp = false;}
      if(KXlYeVzSLF == true){KXlYeVzSLF = false;}
      if(jKzbHWfyJz == true){jKzbHWfyJz = false;}
      if(oNVHYuIzgy == true){oNVHYuIzgy = false;}
      if(BKiXXBIPuR == true){BKiXXBIPuR = false;}
      if(kYqnyzeszD == true){kYqnyzeszD = false;}
      if(lDIuBxBeAi == true){lDIuBxBeAi = false;}
      if(MzkNDZbaEF == true){MzkNDZbaEF = false;}
      if(OPDrNQVgIZ == true){OPDrNQVgIZ = false;}
      if(PPAcMyBmWa == true){PPAcMyBmWa = false;}
      if(AcPLEkmdkX == true){AcPLEkmdkX = false;}
      if(WEosoVAQgj == true){WEosoVAQgj = false;}
      if(aUVZTxzIAF == true){aUVZTxzIAF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLNQJNNMXR
{ 
  void bOLZAzJZbk()
  { 
      bool IPdMsVhgHV = false;
      bool hFGtMuTzfT = false;
      bool huFWKaYEyY = false;
      bool wYLmrzRHFu = false;
      bool gILmAAdCkn = false;
      bool FBMpLMKGBS = false;
      bool xdihYItTCM = false;
      bool dLtjmZjRWK = false;
      bool wWSKSuMVaf = false;
      bool oKGmyDYcOq = false;
      bool GKzYJtGbDl = false;
      bool bsjqVaLYOd = false;
      bool wXrVXSFHli = false;
      bool AHDeDlWtAY = false;
      bool njRoDwaOQW = false;
      bool rAOkuhRdBq = false;
      bool ozoTkUoEmi = false;
      bool ERYpoLFDRb = false;
      bool qppPqArSjU = false;
      bool TsrIiotyDi = false;
      string UzzsrxgJne;
      string GZWzTWMhmn;
      string yMVNLQyJjd;
      string RERaDlGHFp;
      string alifTRojzm;
      string dQATwHckhb;
      string zWYJNCHwwg;
      string PFcwMMdpts;
      string bNKxABEyew;
      string JVYdqEMYRR;
      string KsnSWYmDGj;
      string clqozkMbJM;
      string yJQAWtfzEI;
      string AFXcihYqZb;
      string NAqtSWdjdF;
      string qjPFTAbnub;
      string rnzyjXOOFR;
      string LUBhyxSVgA;
      string PwUzRPpSIh;
      string GkwxiYBsKt;
      if(UzzsrxgJne == KsnSWYmDGj){IPdMsVhgHV = true;}
      else if(KsnSWYmDGj == UzzsrxgJne){GKzYJtGbDl = true;}
      if(GZWzTWMhmn == clqozkMbJM){hFGtMuTzfT = true;}
      else if(clqozkMbJM == GZWzTWMhmn){bsjqVaLYOd = true;}
      if(yMVNLQyJjd == yJQAWtfzEI){huFWKaYEyY = true;}
      else if(yJQAWtfzEI == yMVNLQyJjd){wXrVXSFHli = true;}
      if(RERaDlGHFp == AFXcihYqZb){wYLmrzRHFu = true;}
      else if(AFXcihYqZb == RERaDlGHFp){AHDeDlWtAY = true;}
      if(alifTRojzm == NAqtSWdjdF){gILmAAdCkn = true;}
      else if(NAqtSWdjdF == alifTRojzm){njRoDwaOQW = true;}
      if(dQATwHckhb == qjPFTAbnub){FBMpLMKGBS = true;}
      else if(qjPFTAbnub == dQATwHckhb){rAOkuhRdBq = true;}
      if(zWYJNCHwwg == rnzyjXOOFR){xdihYItTCM = true;}
      else if(rnzyjXOOFR == zWYJNCHwwg){ozoTkUoEmi = true;}
      if(PFcwMMdpts == LUBhyxSVgA){dLtjmZjRWK = true;}
      if(bNKxABEyew == PwUzRPpSIh){wWSKSuMVaf = true;}
      if(JVYdqEMYRR == GkwxiYBsKt){oKGmyDYcOq = true;}
      while(LUBhyxSVgA == PFcwMMdpts){ERYpoLFDRb = true;}
      while(PwUzRPpSIh == PwUzRPpSIh){qppPqArSjU = true;}
      while(GkwxiYBsKt == GkwxiYBsKt){TsrIiotyDi = true;}
      if(IPdMsVhgHV == true){IPdMsVhgHV = false;}
      if(hFGtMuTzfT == true){hFGtMuTzfT = false;}
      if(huFWKaYEyY == true){huFWKaYEyY = false;}
      if(wYLmrzRHFu == true){wYLmrzRHFu = false;}
      if(gILmAAdCkn == true){gILmAAdCkn = false;}
      if(FBMpLMKGBS == true){FBMpLMKGBS = false;}
      if(xdihYItTCM == true){xdihYItTCM = false;}
      if(dLtjmZjRWK == true){dLtjmZjRWK = false;}
      if(wWSKSuMVaf == true){wWSKSuMVaf = false;}
      if(oKGmyDYcOq == true){oKGmyDYcOq = false;}
      if(GKzYJtGbDl == true){GKzYJtGbDl = false;}
      if(bsjqVaLYOd == true){bsjqVaLYOd = false;}
      if(wXrVXSFHli == true){wXrVXSFHli = false;}
      if(AHDeDlWtAY == true){AHDeDlWtAY = false;}
      if(njRoDwaOQW == true){njRoDwaOQW = false;}
      if(rAOkuhRdBq == true){rAOkuhRdBq = false;}
      if(ozoTkUoEmi == true){ozoTkUoEmi = false;}
      if(ERYpoLFDRb == true){ERYpoLFDRb = false;}
      if(qppPqArSjU == true){qppPqArSjU = false;}
      if(TsrIiotyDi == true){TsrIiotyDi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMQOCQDGML
{ 
  void hRooDQpgZQ()
  { 
      bool XcynFbjMUl = false;
      bool AofRAuQxqY = false;
      bool yUuDLkSATR = false;
      bool yVkpfxqWRA = false;
      bool XVHhrXtCXL = false;
      bool HRVVADgucU = false;
      bool IjsDneEpkD = false;
      bool DtepBbNMKm = false;
      bool pPbIJgzOoc = false;
      bool PwsxrncDsN = false;
      bool TDRUHNleUX = false;
      bool oUjodrHksH = false;
      bool eoBHmHAhyN = false;
      bool zJSxTmyGAw = false;
      bool tTtQmuLDTz = false;
      bool fqKlhdCJhz = false;
      bool MEfHYfBmVp = false;
      bool sAjwMKukTr = false;
      bool wwNzgIygOp = false;
      bool joYAipnmrH = false;
      string AOseFadtQt;
      string ytRYLRRmcq;
      string BRnwghhNck;
      string zLldSfXPsQ;
      string IzmxhGSuak;
      string XwUtBiaxxW;
      string sPQftmHmFe;
      string sCtLiBdpOZ;
      string OllqMDqrcj;
      string FaRVXriHCt;
      string yfpurUBIKz;
      string EjiXHGdYSq;
      string uPJUZRjYnq;
      string RWmTbiupzr;
      string BigcfUrtNQ;
      string OJnLziVUVZ;
      string kcTTggxPwY;
      string LmZapMigoE;
      string ZoLWbIibUr;
      string NZTYGYONuz;
      if(AOseFadtQt == yfpurUBIKz){XcynFbjMUl = true;}
      else if(yfpurUBIKz == AOseFadtQt){TDRUHNleUX = true;}
      if(ytRYLRRmcq == EjiXHGdYSq){AofRAuQxqY = true;}
      else if(EjiXHGdYSq == ytRYLRRmcq){oUjodrHksH = true;}
      if(BRnwghhNck == uPJUZRjYnq){yUuDLkSATR = true;}
      else if(uPJUZRjYnq == BRnwghhNck){eoBHmHAhyN = true;}
      if(zLldSfXPsQ == RWmTbiupzr){yVkpfxqWRA = true;}
      else if(RWmTbiupzr == zLldSfXPsQ){zJSxTmyGAw = true;}
      if(IzmxhGSuak == BigcfUrtNQ){XVHhrXtCXL = true;}
      else if(BigcfUrtNQ == IzmxhGSuak){tTtQmuLDTz = true;}
      if(XwUtBiaxxW == OJnLziVUVZ){HRVVADgucU = true;}
      else if(OJnLziVUVZ == XwUtBiaxxW){fqKlhdCJhz = true;}
      if(sPQftmHmFe == kcTTggxPwY){IjsDneEpkD = true;}
      else if(kcTTggxPwY == sPQftmHmFe){MEfHYfBmVp = true;}
      if(sCtLiBdpOZ == LmZapMigoE){DtepBbNMKm = true;}
      if(OllqMDqrcj == ZoLWbIibUr){pPbIJgzOoc = true;}
      if(FaRVXriHCt == NZTYGYONuz){PwsxrncDsN = true;}
      while(LmZapMigoE == sCtLiBdpOZ){sAjwMKukTr = true;}
      while(ZoLWbIibUr == ZoLWbIibUr){wwNzgIygOp = true;}
      while(NZTYGYONuz == NZTYGYONuz){joYAipnmrH = true;}
      if(XcynFbjMUl == true){XcynFbjMUl = false;}
      if(AofRAuQxqY == true){AofRAuQxqY = false;}
      if(yUuDLkSATR == true){yUuDLkSATR = false;}
      if(yVkpfxqWRA == true){yVkpfxqWRA = false;}
      if(XVHhrXtCXL == true){XVHhrXtCXL = false;}
      if(HRVVADgucU == true){HRVVADgucU = false;}
      if(IjsDneEpkD == true){IjsDneEpkD = false;}
      if(DtepBbNMKm == true){DtepBbNMKm = false;}
      if(pPbIJgzOoc == true){pPbIJgzOoc = false;}
      if(PwsxrncDsN == true){PwsxrncDsN = false;}
      if(TDRUHNleUX == true){TDRUHNleUX = false;}
      if(oUjodrHksH == true){oUjodrHksH = false;}
      if(eoBHmHAhyN == true){eoBHmHAhyN = false;}
      if(zJSxTmyGAw == true){zJSxTmyGAw = false;}
      if(tTtQmuLDTz == true){tTtQmuLDTz = false;}
      if(fqKlhdCJhz == true){fqKlhdCJhz = false;}
      if(MEfHYfBmVp == true){MEfHYfBmVp = false;}
      if(sAjwMKukTr == true){sAjwMKukTr = false;}
      if(wwNzgIygOp == true){wwNzgIygOp = false;}
      if(joYAipnmrH == true){joYAipnmrH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MCJQOWLLQU
{ 
  void DJsJQeZrKw()
  { 
      bool VmdcpfWwxV = false;
      bool XzsKMdtIBA = false;
      bool BkqstVuIqU = false;
      bool kORNFDyGZN = false;
      bool qByYtOTsxF = false;
      bool YgCGcjwjhU = false;
      bool jOEbjJgeFJ = false;
      bool fmimIAmRzf = false;
      bool CCKlwDLLkU = false;
      bool GNYEdcwWnk = false;
      bool gnnnZkyOxb = false;
      bool wekCSgDSeg = false;
      bool xVtjCROeJf = false;
      bool EQcNyNNWLL = false;
      bool FxNIYbbWkw = false;
      bool YcqHnKtEkH = false;
      bool WSFRXfBXDF = false;
      bool TgGTazHkLa = false;
      bool prsMGaZUZn = false;
      bool SJlEnlqwkr = false;
      string TSytHgFsya;
      string DPTKZmZgnE;
      string SjDmIHrNaQ;
      string ujfkkfQwft;
      string LpXBGrCiJq;
      string CzHMuiPLkA;
      string orRgfSjiZt;
      string VcAtrbMBfQ;
      string FIDjOucSoB;
      string QFKfFTXpVm;
      string HSJOUYyNTS;
      string WNeUufnhRj;
      string pRtXdQRUoY;
      string EWfrIlyoOp;
      string wOyVeCZpkY;
      string epXkxpXlkD;
      string GdYuOAglLI;
      string hzSbnaSYsa;
      string qbiPsOyuuS;
      string NMDKjSpDGe;
      if(TSytHgFsya == HSJOUYyNTS){VmdcpfWwxV = true;}
      else if(HSJOUYyNTS == TSytHgFsya){gnnnZkyOxb = true;}
      if(DPTKZmZgnE == WNeUufnhRj){XzsKMdtIBA = true;}
      else if(WNeUufnhRj == DPTKZmZgnE){wekCSgDSeg = true;}
      if(SjDmIHrNaQ == pRtXdQRUoY){BkqstVuIqU = true;}
      else if(pRtXdQRUoY == SjDmIHrNaQ){xVtjCROeJf = true;}
      if(ujfkkfQwft == EWfrIlyoOp){kORNFDyGZN = true;}
      else if(EWfrIlyoOp == ujfkkfQwft){EQcNyNNWLL = true;}
      if(LpXBGrCiJq == wOyVeCZpkY){qByYtOTsxF = true;}
      else if(wOyVeCZpkY == LpXBGrCiJq){FxNIYbbWkw = true;}
      if(CzHMuiPLkA == epXkxpXlkD){YgCGcjwjhU = true;}
      else if(epXkxpXlkD == CzHMuiPLkA){YcqHnKtEkH = true;}
      if(orRgfSjiZt == GdYuOAglLI){jOEbjJgeFJ = true;}
      else if(GdYuOAglLI == orRgfSjiZt){WSFRXfBXDF = true;}
      if(VcAtrbMBfQ == hzSbnaSYsa){fmimIAmRzf = true;}
      if(FIDjOucSoB == qbiPsOyuuS){CCKlwDLLkU = true;}
      if(QFKfFTXpVm == NMDKjSpDGe){GNYEdcwWnk = true;}
      while(hzSbnaSYsa == VcAtrbMBfQ){TgGTazHkLa = true;}
      while(qbiPsOyuuS == qbiPsOyuuS){prsMGaZUZn = true;}
      while(NMDKjSpDGe == NMDKjSpDGe){SJlEnlqwkr = true;}
      if(VmdcpfWwxV == true){VmdcpfWwxV = false;}
      if(XzsKMdtIBA == true){XzsKMdtIBA = false;}
      if(BkqstVuIqU == true){BkqstVuIqU = false;}
      if(kORNFDyGZN == true){kORNFDyGZN = false;}
      if(qByYtOTsxF == true){qByYtOTsxF = false;}
      if(YgCGcjwjhU == true){YgCGcjwjhU = false;}
      if(jOEbjJgeFJ == true){jOEbjJgeFJ = false;}
      if(fmimIAmRzf == true){fmimIAmRzf = false;}
      if(CCKlwDLLkU == true){CCKlwDLLkU = false;}
      if(GNYEdcwWnk == true){GNYEdcwWnk = false;}
      if(gnnnZkyOxb == true){gnnnZkyOxb = false;}
      if(wekCSgDSeg == true){wekCSgDSeg = false;}
      if(xVtjCROeJf == true){xVtjCROeJf = false;}
      if(EQcNyNNWLL == true){EQcNyNNWLL = false;}
      if(FxNIYbbWkw == true){FxNIYbbWkw = false;}
      if(YcqHnKtEkH == true){YcqHnKtEkH = false;}
      if(WSFRXfBXDF == true){WSFRXfBXDF = false;}
      if(TgGTazHkLa == true){TgGTazHkLa = false;}
      if(prsMGaZUZn == true){prsMGaZUZn = false;}
      if(SJlEnlqwkr == true){SJlEnlqwkr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFZSQFMGIZ
{ 
  void rDkWsneKno()
  { 
      bool CDKSDCxuUV = false;
      bool FJzjrVEdPc = false;
      bool ObsQDKaaoJ = false;
      bool onXWdQisxT = false;
      bool ZihbPYyXaX = false;
      bool SrsLoaJsOr = false;
      bool aWGLfRkbFb = false;
      bool lKgwDetRBd = false;
      bool MCAQpxtLgD = false;
      bool GpdErDbVux = false;
      bool mVSylHKxIJ = false;
      bool gqqkeXWpUi = false;
      bool XYtCUugcDA = false;
      bool DXWEqqjBdh = false;
      bool mwDXWOysZU = false;
      bool fkAMZNaPdp = false;
      bool ahsIGIUmsn = false;
      bool mVMmuaVWeG = false;
      bool xmDiTRWJec = false;
      bool PTXmGFDuQN = false;
      string wIWukkdziE;
      string kZOGNxwdnL;
      string hMsYJOmQRZ;
      string NgnFigPuRm;
      string IAfOykiTLJ;
      string IspxyiPxkW;
      string xNhJpDlJXf;
      string gBLAChfdZY;
      string eSEHQUpqGA;
      string RRJuotRWYu;
      string zZwebHgotQ;
      string CkWMqdIZrV;
      string MtDWNPqQKH;
      string PJFeZFVYfJ;
      string nBwpxguxEK;
      string lrdChEWYQM;
      string PQdlAseqll;
      string HithgLyMZg;
      string TtLAVXeDxV;
      string hxISsXWJoD;
      if(wIWukkdziE == zZwebHgotQ){CDKSDCxuUV = true;}
      else if(zZwebHgotQ == wIWukkdziE){mVSylHKxIJ = true;}
      if(kZOGNxwdnL == CkWMqdIZrV){FJzjrVEdPc = true;}
      else if(CkWMqdIZrV == kZOGNxwdnL){gqqkeXWpUi = true;}
      if(hMsYJOmQRZ == MtDWNPqQKH){ObsQDKaaoJ = true;}
      else if(MtDWNPqQKH == hMsYJOmQRZ){XYtCUugcDA = true;}
      if(NgnFigPuRm == PJFeZFVYfJ){onXWdQisxT = true;}
      else if(PJFeZFVYfJ == NgnFigPuRm){DXWEqqjBdh = true;}
      if(IAfOykiTLJ == nBwpxguxEK){ZihbPYyXaX = true;}
      else if(nBwpxguxEK == IAfOykiTLJ){mwDXWOysZU = true;}
      if(IspxyiPxkW == lrdChEWYQM){SrsLoaJsOr = true;}
      else if(lrdChEWYQM == IspxyiPxkW){fkAMZNaPdp = true;}
      if(xNhJpDlJXf == PQdlAseqll){aWGLfRkbFb = true;}
      else if(PQdlAseqll == xNhJpDlJXf){ahsIGIUmsn = true;}
      if(gBLAChfdZY == HithgLyMZg){lKgwDetRBd = true;}
      if(eSEHQUpqGA == TtLAVXeDxV){MCAQpxtLgD = true;}
      if(RRJuotRWYu == hxISsXWJoD){GpdErDbVux = true;}
      while(HithgLyMZg == gBLAChfdZY){mVMmuaVWeG = true;}
      while(TtLAVXeDxV == TtLAVXeDxV){xmDiTRWJec = true;}
      while(hxISsXWJoD == hxISsXWJoD){PTXmGFDuQN = true;}
      if(CDKSDCxuUV == true){CDKSDCxuUV = false;}
      if(FJzjrVEdPc == true){FJzjrVEdPc = false;}
      if(ObsQDKaaoJ == true){ObsQDKaaoJ = false;}
      if(onXWdQisxT == true){onXWdQisxT = false;}
      if(ZihbPYyXaX == true){ZihbPYyXaX = false;}
      if(SrsLoaJsOr == true){SrsLoaJsOr = false;}
      if(aWGLfRkbFb == true){aWGLfRkbFb = false;}
      if(lKgwDetRBd == true){lKgwDetRBd = false;}
      if(MCAQpxtLgD == true){MCAQpxtLgD = false;}
      if(GpdErDbVux == true){GpdErDbVux = false;}
      if(mVSylHKxIJ == true){mVSylHKxIJ = false;}
      if(gqqkeXWpUi == true){gqqkeXWpUi = false;}
      if(XYtCUugcDA == true){XYtCUugcDA = false;}
      if(DXWEqqjBdh == true){DXWEqqjBdh = false;}
      if(mwDXWOysZU == true){mwDXWOysZU = false;}
      if(fkAMZNaPdp == true){fkAMZNaPdp = false;}
      if(ahsIGIUmsn == true){ahsIGIUmsn = false;}
      if(mVMmuaVWeG == true){mVMmuaVWeG = false;}
      if(xmDiTRWJec == true){xmDiTRWJec = false;}
      if(PTXmGFDuQN == true){PTXmGFDuQN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCFICAWOXZ
{ 
  void ILfFGhEYHb()
  { 
      bool zQKqcuNTfx = false;
      bool jEDLzuZwZN = false;
      bool UGJuLwErYx = false;
      bool VHmWNFUjbW = false;
      bool LMKEWwyNqI = false;
      bool DDpOdsHOef = false;
      bool qVuhacQgys = false;
      bool apTCBHwEYP = false;
      bool ypAQsSQYrU = false;
      bool yFEweoRbct = false;
      bool eQOyhNinMV = false;
      bool wCpOgBVdoI = false;
      bool LqndtUkWWM = false;
      bool pUbekgaBie = false;
      bool ibMWXwPpPd = false;
      bool TmlUhmckDM = false;
      bool cLRAeaaLdz = false;
      bool ZTuJYjeRFy = false;
      bool FuHrrChHwx = false;
      bool EoyVCWKMqw = false;
      string FzJkbNetsd;
      string IBGwyPXBdI;
      string oqtOQaSTOo;
      string JAaAtwFzlw;
      string NYIhAOFwkf;
      string qxPgaNFuTB;
      string uKfETIaFBB;
      string JXPguPhLNC;
      string UVhixMjtZf;
      string qJejBCsEOr;
      string mztiVSghkK;
      string ftgRgZcwGH;
      string XffVKzsefr;
      string WdxVOUayNd;
      string fBIPAwcNDa;
      string ZxxGTHTYYV;
      string ZBBrmBxLCM;
      string ydicaVWPUN;
      string WebFSZgpCH;
      string ABZqDdAPby;
      if(FzJkbNetsd == mztiVSghkK){zQKqcuNTfx = true;}
      else if(mztiVSghkK == FzJkbNetsd){eQOyhNinMV = true;}
      if(IBGwyPXBdI == ftgRgZcwGH){jEDLzuZwZN = true;}
      else if(ftgRgZcwGH == IBGwyPXBdI){wCpOgBVdoI = true;}
      if(oqtOQaSTOo == XffVKzsefr){UGJuLwErYx = true;}
      else if(XffVKzsefr == oqtOQaSTOo){LqndtUkWWM = true;}
      if(JAaAtwFzlw == WdxVOUayNd){VHmWNFUjbW = true;}
      else if(WdxVOUayNd == JAaAtwFzlw){pUbekgaBie = true;}
      if(NYIhAOFwkf == fBIPAwcNDa){LMKEWwyNqI = true;}
      else if(fBIPAwcNDa == NYIhAOFwkf){ibMWXwPpPd = true;}
      if(qxPgaNFuTB == ZxxGTHTYYV){DDpOdsHOef = true;}
      else if(ZxxGTHTYYV == qxPgaNFuTB){TmlUhmckDM = true;}
      if(uKfETIaFBB == ZBBrmBxLCM){qVuhacQgys = true;}
      else if(ZBBrmBxLCM == uKfETIaFBB){cLRAeaaLdz = true;}
      if(JXPguPhLNC == ydicaVWPUN){apTCBHwEYP = true;}
      if(UVhixMjtZf == WebFSZgpCH){ypAQsSQYrU = true;}
      if(qJejBCsEOr == ABZqDdAPby){yFEweoRbct = true;}
      while(ydicaVWPUN == JXPguPhLNC){ZTuJYjeRFy = true;}
      while(WebFSZgpCH == WebFSZgpCH){FuHrrChHwx = true;}
      while(ABZqDdAPby == ABZqDdAPby){EoyVCWKMqw = true;}
      if(zQKqcuNTfx == true){zQKqcuNTfx = false;}
      if(jEDLzuZwZN == true){jEDLzuZwZN = false;}
      if(UGJuLwErYx == true){UGJuLwErYx = false;}
      if(VHmWNFUjbW == true){VHmWNFUjbW = false;}
      if(LMKEWwyNqI == true){LMKEWwyNqI = false;}
      if(DDpOdsHOef == true){DDpOdsHOef = false;}
      if(qVuhacQgys == true){qVuhacQgys = false;}
      if(apTCBHwEYP == true){apTCBHwEYP = false;}
      if(ypAQsSQYrU == true){ypAQsSQYrU = false;}
      if(yFEweoRbct == true){yFEweoRbct = false;}
      if(eQOyhNinMV == true){eQOyhNinMV = false;}
      if(wCpOgBVdoI == true){wCpOgBVdoI = false;}
      if(LqndtUkWWM == true){LqndtUkWWM = false;}
      if(pUbekgaBie == true){pUbekgaBie = false;}
      if(ibMWXwPpPd == true){ibMWXwPpPd = false;}
      if(TmlUhmckDM == true){TmlUhmckDM = false;}
      if(cLRAeaaLdz == true){cLRAeaaLdz = false;}
      if(ZTuJYjeRFy == true){ZTuJYjeRFy = false;}
      if(FuHrrChHwx == true){FuHrrChHwx = false;}
      if(EoyVCWKMqw == true){EoyVCWKMqw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYDHMESXXE
{ 
  void CpAnfxhCsR()
  { 
      bool YrloDVrpHO = false;
      bool eTPjwsJqNH = false;
      bool ZwdDbMkoPe = false;
      bool FSIMboFgrF = false;
      bool NnPSuULWfC = false;
      bool aQqnwcNhNp = false;
      bool kCZcILLCHG = false;
      bool mbzItkfLIH = false;
      bool BNJMEobUQz = false;
      bool bWTBTKNmJi = false;
      bool JIOYPyQitK = false;
      bool wCZFoWsMXT = false;
      bool jqlIePHxni = false;
      bool WsBYyrzjxF = false;
      bool YsaFCYxOMw = false;
      bool RBOpzSWGtz = false;
      bool qStKnDBAHx = false;
      bool XJPSuqQfFG = false;
      bool SskqQVdLYe = false;
      bool UroyOFyPRy = false;
      string AhbJSEMoVM;
      string PbSmdCJbtp;
      string ZoQKFoIGuB;
      string ClmPTaqcNB;
      string DbOOOIoZiZ;
      string aZRPbKRREc;
      string wGsTJcnCSD;
      string KgOrlyaBux;
      string zhWUacUWnJ;
      string JZXjFxhtFk;
      string TmHeOsKZdd;
      string jPVHdNiXsg;
      string IQOItkIdlo;
      string PfwKcMZrGg;
      string RtsJZsDQGq;
      string NJBXcCXykd;
      string kgmoNDTLdQ;
      string nqRLPNXEiB;
      string grWuaFdXhZ;
      string naGbwjHEwV;
      if(AhbJSEMoVM == TmHeOsKZdd){YrloDVrpHO = true;}
      else if(TmHeOsKZdd == AhbJSEMoVM){JIOYPyQitK = true;}
      if(PbSmdCJbtp == jPVHdNiXsg){eTPjwsJqNH = true;}
      else if(jPVHdNiXsg == PbSmdCJbtp){wCZFoWsMXT = true;}
      if(ZoQKFoIGuB == IQOItkIdlo){ZwdDbMkoPe = true;}
      else if(IQOItkIdlo == ZoQKFoIGuB){jqlIePHxni = true;}
      if(ClmPTaqcNB == PfwKcMZrGg){FSIMboFgrF = true;}
      else if(PfwKcMZrGg == ClmPTaqcNB){WsBYyrzjxF = true;}
      if(DbOOOIoZiZ == RtsJZsDQGq){NnPSuULWfC = true;}
      else if(RtsJZsDQGq == DbOOOIoZiZ){YsaFCYxOMw = true;}
      if(aZRPbKRREc == NJBXcCXykd){aQqnwcNhNp = true;}
      else if(NJBXcCXykd == aZRPbKRREc){RBOpzSWGtz = true;}
      if(wGsTJcnCSD == kgmoNDTLdQ){kCZcILLCHG = true;}
      else if(kgmoNDTLdQ == wGsTJcnCSD){qStKnDBAHx = true;}
      if(KgOrlyaBux == nqRLPNXEiB){mbzItkfLIH = true;}
      if(zhWUacUWnJ == grWuaFdXhZ){BNJMEobUQz = true;}
      if(JZXjFxhtFk == naGbwjHEwV){bWTBTKNmJi = true;}
      while(nqRLPNXEiB == KgOrlyaBux){XJPSuqQfFG = true;}
      while(grWuaFdXhZ == grWuaFdXhZ){SskqQVdLYe = true;}
      while(naGbwjHEwV == naGbwjHEwV){UroyOFyPRy = true;}
      if(YrloDVrpHO == true){YrloDVrpHO = false;}
      if(eTPjwsJqNH == true){eTPjwsJqNH = false;}
      if(ZwdDbMkoPe == true){ZwdDbMkoPe = false;}
      if(FSIMboFgrF == true){FSIMboFgrF = false;}
      if(NnPSuULWfC == true){NnPSuULWfC = false;}
      if(aQqnwcNhNp == true){aQqnwcNhNp = false;}
      if(kCZcILLCHG == true){kCZcILLCHG = false;}
      if(mbzItkfLIH == true){mbzItkfLIH = false;}
      if(BNJMEobUQz == true){BNJMEobUQz = false;}
      if(bWTBTKNmJi == true){bWTBTKNmJi = false;}
      if(JIOYPyQitK == true){JIOYPyQitK = false;}
      if(wCZFoWsMXT == true){wCZFoWsMXT = false;}
      if(jqlIePHxni == true){jqlIePHxni = false;}
      if(WsBYyrzjxF == true){WsBYyrzjxF = false;}
      if(YsaFCYxOMw == true){YsaFCYxOMw = false;}
      if(RBOpzSWGtz == true){RBOpzSWGtz = false;}
      if(qStKnDBAHx == true){qStKnDBAHx = false;}
      if(XJPSuqQfFG == true){XJPSuqQfFG = false;}
      if(SskqQVdLYe == true){SskqQVdLYe = false;}
      if(UroyOFyPRy == true){UroyOFyPRy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSBYAMBGBH
{ 
  void AaLkSwXOkf()
  { 
      bool UgVTrKkFqF = false;
      bool cmYYreVNYP = false;
      bool zdnZAMNlgQ = false;
      bool BsxWAFywJO = false;
      bool XYIUwHQWlT = false;
      bool LcrrSpsuSe = false;
      bool wzYZEipCXl = false;
      bool fYEJraVSdr = false;
      bool wqzNFXBFDJ = false;
      bool MDceSXAhPM = false;
      bool RNzAmlYhzr = false;
      bool UaRahFzLUf = false;
      bool hkzNZcwYpT = false;
      bool amCQaiqzZS = false;
      bool zSFKokkCwN = false;
      bool YnNjdfOkZK = false;
      bool pzqfRgXAzz = false;
      bool NAkBgOfnYn = false;
      bool qsbculZSlu = false;
      bool TGYPczbYsH = false;
      string sdCJrrDKQo;
      string CwgBVQreHh;
      string OPLqWriBKz;
      string jgNhWjwUzK;
      string UbhNTubeyj;
      string MxLFTcRLmA;
      string JBAREUhzek;
      string UWexNlhyXa;
      string QDCZmlUHOs;
      string RjhzATbQIy;
      string NcANPoSNrh;
      string uTnMiFzadS;
      string AZklTjofxs;
      string JQoYMmDoKy;
      string THPfxywUPt;
      string TBlpymrNsf;
      string zlQyXedOzw;
      string CJQfyrKEoU;
      string mUQCZIezaY;
      string uoudygqQHS;
      if(sdCJrrDKQo == NcANPoSNrh){UgVTrKkFqF = true;}
      else if(NcANPoSNrh == sdCJrrDKQo){RNzAmlYhzr = true;}
      if(CwgBVQreHh == uTnMiFzadS){cmYYreVNYP = true;}
      else if(uTnMiFzadS == CwgBVQreHh){UaRahFzLUf = true;}
      if(OPLqWriBKz == AZklTjofxs){zdnZAMNlgQ = true;}
      else if(AZklTjofxs == OPLqWriBKz){hkzNZcwYpT = true;}
      if(jgNhWjwUzK == JQoYMmDoKy){BsxWAFywJO = true;}
      else if(JQoYMmDoKy == jgNhWjwUzK){amCQaiqzZS = true;}
      if(UbhNTubeyj == THPfxywUPt){XYIUwHQWlT = true;}
      else if(THPfxywUPt == UbhNTubeyj){zSFKokkCwN = true;}
      if(MxLFTcRLmA == TBlpymrNsf){LcrrSpsuSe = true;}
      else if(TBlpymrNsf == MxLFTcRLmA){YnNjdfOkZK = true;}
      if(JBAREUhzek == zlQyXedOzw){wzYZEipCXl = true;}
      else if(zlQyXedOzw == JBAREUhzek){pzqfRgXAzz = true;}
      if(UWexNlhyXa == CJQfyrKEoU){fYEJraVSdr = true;}
      if(QDCZmlUHOs == mUQCZIezaY){wqzNFXBFDJ = true;}
      if(RjhzATbQIy == uoudygqQHS){MDceSXAhPM = true;}
      while(CJQfyrKEoU == UWexNlhyXa){NAkBgOfnYn = true;}
      while(mUQCZIezaY == mUQCZIezaY){qsbculZSlu = true;}
      while(uoudygqQHS == uoudygqQHS){TGYPczbYsH = true;}
      if(UgVTrKkFqF == true){UgVTrKkFqF = false;}
      if(cmYYreVNYP == true){cmYYreVNYP = false;}
      if(zdnZAMNlgQ == true){zdnZAMNlgQ = false;}
      if(BsxWAFywJO == true){BsxWAFywJO = false;}
      if(XYIUwHQWlT == true){XYIUwHQWlT = false;}
      if(LcrrSpsuSe == true){LcrrSpsuSe = false;}
      if(wzYZEipCXl == true){wzYZEipCXl = false;}
      if(fYEJraVSdr == true){fYEJraVSdr = false;}
      if(wqzNFXBFDJ == true){wqzNFXBFDJ = false;}
      if(MDceSXAhPM == true){MDceSXAhPM = false;}
      if(RNzAmlYhzr == true){RNzAmlYhzr = false;}
      if(UaRahFzLUf == true){UaRahFzLUf = false;}
      if(hkzNZcwYpT == true){hkzNZcwYpT = false;}
      if(amCQaiqzZS == true){amCQaiqzZS = false;}
      if(zSFKokkCwN == true){zSFKokkCwN = false;}
      if(YnNjdfOkZK == true){YnNjdfOkZK = false;}
      if(pzqfRgXAzz == true){pzqfRgXAzz = false;}
      if(NAkBgOfnYn == true){NAkBgOfnYn = false;}
      if(qsbculZSlu == true){qsbculZSlu = false;}
      if(TGYPczbYsH == true){TGYPczbYsH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YFBNSLPZRV
{ 
  void FPINNripwx()
  { 
      bool PEhQmATmUs = false;
      bool cSTusDLjFA = false;
      bool DEVXqKlBxw = false;
      bool duxKuOKNNi = false;
      bool LKKlrwkRGZ = false;
      bool tqpCeKhKYb = false;
      bool ORoXOhVIzd = false;
      bool sxVWorsjeu = false;
      bool YUuXClFtfk = false;
      bool fzokUtVlWK = false;
      bool abRbfwVTNl = false;
      bool QyecDsVQVb = false;
      bool bacOxsIjCt = false;
      bool WGMUUwCTqF = false;
      bool QlgsThULha = false;
      bool YEPthzzDdl = false;
      bool nkRSOJkKIG = false;
      bool pBYQLptjtP = false;
      bool YwCaVRpRmU = false;
      bool xzoEQeTOdJ = false;
      string TFBHRGGCXk;
      string pgcIHSPEIX;
      string YenbgoTDrh;
      string wYpcjGJkoV;
      string VqEMhpDNSu;
      string sHZcNnRYZb;
      string mDKonQqAYB;
      string JdOlCgabtp;
      string lGkxnozMPw;
      string ojKMiSgOXQ;
      string zDoRkOrmZf;
      string MoejogRMAz;
      string RdjbLYSBCj;
      string zLEdqhRSLY;
      string wLljiAFaXC;
      string AUOXyUSMGM;
      string upjpfBkAsG;
      string PzBaCFrAsK;
      string TrdAjexfeV;
      string PEMzcGbwDh;
      if(TFBHRGGCXk == zDoRkOrmZf){PEhQmATmUs = true;}
      else if(zDoRkOrmZf == TFBHRGGCXk){abRbfwVTNl = true;}
      if(pgcIHSPEIX == MoejogRMAz){cSTusDLjFA = true;}
      else if(MoejogRMAz == pgcIHSPEIX){QyecDsVQVb = true;}
      if(YenbgoTDrh == RdjbLYSBCj){DEVXqKlBxw = true;}
      else if(RdjbLYSBCj == YenbgoTDrh){bacOxsIjCt = true;}
      if(wYpcjGJkoV == zLEdqhRSLY){duxKuOKNNi = true;}
      else if(zLEdqhRSLY == wYpcjGJkoV){WGMUUwCTqF = true;}
      if(VqEMhpDNSu == wLljiAFaXC){LKKlrwkRGZ = true;}
      else if(wLljiAFaXC == VqEMhpDNSu){QlgsThULha = true;}
      if(sHZcNnRYZb == AUOXyUSMGM){tqpCeKhKYb = true;}
      else if(AUOXyUSMGM == sHZcNnRYZb){YEPthzzDdl = true;}
      if(mDKonQqAYB == upjpfBkAsG){ORoXOhVIzd = true;}
      else if(upjpfBkAsG == mDKonQqAYB){nkRSOJkKIG = true;}
      if(JdOlCgabtp == PzBaCFrAsK){sxVWorsjeu = true;}
      if(lGkxnozMPw == TrdAjexfeV){YUuXClFtfk = true;}
      if(ojKMiSgOXQ == PEMzcGbwDh){fzokUtVlWK = true;}
      while(PzBaCFrAsK == JdOlCgabtp){pBYQLptjtP = true;}
      while(TrdAjexfeV == TrdAjexfeV){YwCaVRpRmU = true;}
      while(PEMzcGbwDh == PEMzcGbwDh){xzoEQeTOdJ = true;}
      if(PEhQmATmUs == true){PEhQmATmUs = false;}
      if(cSTusDLjFA == true){cSTusDLjFA = false;}
      if(DEVXqKlBxw == true){DEVXqKlBxw = false;}
      if(duxKuOKNNi == true){duxKuOKNNi = false;}
      if(LKKlrwkRGZ == true){LKKlrwkRGZ = false;}
      if(tqpCeKhKYb == true){tqpCeKhKYb = false;}
      if(ORoXOhVIzd == true){ORoXOhVIzd = false;}
      if(sxVWorsjeu == true){sxVWorsjeu = false;}
      if(YUuXClFtfk == true){YUuXClFtfk = false;}
      if(fzokUtVlWK == true){fzokUtVlWK = false;}
      if(abRbfwVTNl == true){abRbfwVTNl = false;}
      if(QyecDsVQVb == true){QyecDsVQVb = false;}
      if(bacOxsIjCt == true){bacOxsIjCt = false;}
      if(WGMUUwCTqF == true){WGMUUwCTqF = false;}
      if(QlgsThULha == true){QlgsThULha = false;}
      if(YEPthzzDdl == true){YEPthzzDdl = false;}
      if(nkRSOJkKIG == true){nkRSOJkKIG = false;}
      if(pBYQLptjtP == true){pBYQLptjtP = false;}
      if(YwCaVRpRmU == true){YwCaVRpRmU = false;}
      if(xzoEQeTOdJ == true){xzoEQeTOdJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCQFGIMEPL
{ 
  void JNaKhLWzHJ()
  { 
      bool RirBeznsQz = false;
      bool DQtPxVEgOu = false;
      bool aYtcOmJnFc = false;
      bool OugrWMVPJi = false;
      bool EkQcEmwGWD = false;
      bool EnsDYroOlr = false;
      bool pAnmkHjBsj = false;
      bool znWeqoHQYb = false;
      bool pDQCYZBdTd = false;
      bool WGcRsExdrw = false;
      bool CtMlDPROLi = false;
      bool kYoKBlilOK = false;
      bool GFhPMsLFkm = false;
      bool rdXcYwqezI = false;
      bool ImRjsyQSQH = false;
      bool UKPgpxLxYK = false;
      bool ELdYqGAMkF = false;
      bool uEmFCTmyVO = false;
      bool bsodRgOqlb = false;
      bool jsFoDwJssm = false;
      string MQdwMUgZBT;
      string eJwrgpaDto;
      string HqXVTYDhue;
      string SrhIhHyFcg;
      string lxeUxpFrpm;
      string whgPoUsHcn;
      string RyeVBlanJZ;
      string rUaNCJMDXc;
      string SKqIikKSTN;
      string NpcoPmSJSK;
      string ORhQuaGTMe;
      string IpjzUGHVlP;
      string aITwLBqlyP;
      string pCjMNBbaNI;
      string dqFnFXGdUI;
      string fxXCjGxlEs;
      string iUVxoFFWkS;
      string dfIdljDfqn;
      string uNQoisegcH;
      string DpVUYIVHzz;
      if(MQdwMUgZBT == ORhQuaGTMe){RirBeznsQz = true;}
      else if(ORhQuaGTMe == MQdwMUgZBT){CtMlDPROLi = true;}
      if(eJwrgpaDto == IpjzUGHVlP){DQtPxVEgOu = true;}
      else if(IpjzUGHVlP == eJwrgpaDto){kYoKBlilOK = true;}
      if(HqXVTYDhue == aITwLBqlyP){aYtcOmJnFc = true;}
      else if(aITwLBqlyP == HqXVTYDhue){GFhPMsLFkm = true;}
      if(SrhIhHyFcg == pCjMNBbaNI){OugrWMVPJi = true;}
      else if(pCjMNBbaNI == SrhIhHyFcg){rdXcYwqezI = true;}
      if(lxeUxpFrpm == dqFnFXGdUI){EkQcEmwGWD = true;}
      else if(dqFnFXGdUI == lxeUxpFrpm){ImRjsyQSQH = true;}
      if(whgPoUsHcn == fxXCjGxlEs){EnsDYroOlr = true;}
      else if(fxXCjGxlEs == whgPoUsHcn){UKPgpxLxYK = true;}
      if(RyeVBlanJZ == iUVxoFFWkS){pAnmkHjBsj = true;}
      else if(iUVxoFFWkS == RyeVBlanJZ){ELdYqGAMkF = true;}
      if(rUaNCJMDXc == dfIdljDfqn){znWeqoHQYb = true;}
      if(SKqIikKSTN == uNQoisegcH){pDQCYZBdTd = true;}
      if(NpcoPmSJSK == DpVUYIVHzz){WGcRsExdrw = true;}
      while(dfIdljDfqn == rUaNCJMDXc){uEmFCTmyVO = true;}
      while(uNQoisegcH == uNQoisegcH){bsodRgOqlb = true;}
      while(DpVUYIVHzz == DpVUYIVHzz){jsFoDwJssm = true;}
      if(RirBeznsQz == true){RirBeznsQz = false;}
      if(DQtPxVEgOu == true){DQtPxVEgOu = false;}
      if(aYtcOmJnFc == true){aYtcOmJnFc = false;}
      if(OugrWMVPJi == true){OugrWMVPJi = false;}
      if(EkQcEmwGWD == true){EkQcEmwGWD = false;}
      if(EnsDYroOlr == true){EnsDYroOlr = false;}
      if(pAnmkHjBsj == true){pAnmkHjBsj = false;}
      if(znWeqoHQYb == true){znWeqoHQYb = false;}
      if(pDQCYZBdTd == true){pDQCYZBdTd = false;}
      if(WGcRsExdrw == true){WGcRsExdrw = false;}
      if(CtMlDPROLi == true){CtMlDPROLi = false;}
      if(kYoKBlilOK == true){kYoKBlilOK = false;}
      if(GFhPMsLFkm == true){GFhPMsLFkm = false;}
      if(rdXcYwqezI == true){rdXcYwqezI = false;}
      if(ImRjsyQSQH == true){ImRjsyQSQH = false;}
      if(UKPgpxLxYK == true){UKPgpxLxYK = false;}
      if(ELdYqGAMkF == true){ELdYqGAMkF = false;}
      if(uEmFCTmyVO == true){uEmFCTmyVO = false;}
      if(bsodRgOqlb == true){bsodRgOqlb = false;}
      if(jsFoDwJssm == true){jsFoDwJssm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKTOQVLZBW
{ 
  void KEnWlJFZZg()
  { 
      bool JzCXhUwNrw = false;
      bool ToikYHNYWu = false;
      bool OCMdTRRief = false;
      bool AaEGaauuHp = false;
      bool oUNniKcdPl = false;
      bool iESDAHmXEP = false;
      bool CMiMusjcKy = false;
      bool MSQfFtoXtJ = false;
      bool onTrwuIBFT = false;
      bool nWprmbkAsp = false;
      bool ZzTRYQnlyF = false;
      bool SOctaNsqPz = false;
      bool jiXpJpbYrd = false;
      bool JneEjoUBTf = false;
      bool HWCzBYswQZ = false;
      bool itjsFqbcHi = false;
      bool oOsUwdjYKl = false;
      bool srXjqNfXok = false;
      bool weIStPEkzr = false;
      bool MrsjqschDW = false;
      string qzTaeSZUPI;
      string bEquxzbBZl;
      string lsKyrxOsBJ;
      string eqypdqZokN;
      string CzPGlecGft;
      string YIeeYxnUig;
      string EfSGdkGAQF;
      string ZmPLjldEMM;
      string UHMHjWMSRg;
      string CEFEJVfIcA;
      string YboZTlrSul;
      string SjIVMwTLWG;
      string YmijDVgLCN;
      string FUbLnrRlmy;
      string dsWeNRujrM;
      string CUlVaksFWy;
      string EgPhfyIwgT;
      string dgXXceQDVk;
      string ZxTpKkiFjD;
      string zMPosxdoyP;
      if(qzTaeSZUPI == YboZTlrSul){JzCXhUwNrw = true;}
      else if(YboZTlrSul == qzTaeSZUPI){ZzTRYQnlyF = true;}
      if(bEquxzbBZl == SjIVMwTLWG){ToikYHNYWu = true;}
      else if(SjIVMwTLWG == bEquxzbBZl){SOctaNsqPz = true;}
      if(lsKyrxOsBJ == YmijDVgLCN){OCMdTRRief = true;}
      else if(YmijDVgLCN == lsKyrxOsBJ){jiXpJpbYrd = true;}
      if(eqypdqZokN == FUbLnrRlmy){AaEGaauuHp = true;}
      else if(FUbLnrRlmy == eqypdqZokN){JneEjoUBTf = true;}
      if(CzPGlecGft == dsWeNRujrM){oUNniKcdPl = true;}
      else if(dsWeNRujrM == CzPGlecGft){HWCzBYswQZ = true;}
      if(YIeeYxnUig == CUlVaksFWy){iESDAHmXEP = true;}
      else if(CUlVaksFWy == YIeeYxnUig){itjsFqbcHi = true;}
      if(EfSGdkGAQF == EgPhfyIwgT){CMiMusjcKy = true;}
      else if(EgPhfyIwgT == EfSGdkGAQF){oOsUwdjYKl = true;}
      if(ZmPLjldEMM == dgXXceQDVk){MSQfFtoXtJ = true;}
      if(UHMHjWMSRg == ZxTpKkiFjD){onTrwuIBFT = true;}
      if(CEFEJVfIcA == zMPosxdoyP){nWprmbkAsp = true;}
      while(dgXXceQDVk == ZmPLjldEMM){srXjqNfXok = true;}
      while(ZxTpKkiFjD == ZxTpKkiFjD){weIStPEkzr = true;}
      while(zMPosxdoyP == zMPosxdoyP){MrsjqschDW = true;}
      if(JzCXhUwNrw == true){JzCXhUwNrw = false;}
      if(ToikYHNYWu == true){ToikYHNYWu = false;}
      if(OCMdTRRief == true){OCMdTRRief = false;}
      if(AaEGaauuHp == true){AaEGaauuHp = false;}
      if(oUNniKcdPl == true){oUNniKcdPl = false;}
      if(iESDAHmXEP == true){iESDAHmXEP = false;}
      if(CMiMusjcKy == true){CMiMusjcKy = false;}
      if(MSQfFtoXtJ == true){MSQfFtoXtJ = false;}
      if(onTrwuIBFT == true){onTrwuIBFT = false;}
      if(nWprmbkAsp == true){nWprmbkAsp = false;}
      if(ZzTRYQnlyF == true){ZzTRYQnlyF = false;}
      if(SOctaNsqPz == true){SOctaNsqPz = false;}
      if(jiXpJpbYrd == true){jiXpJpbYrd = false;}
      if(JneEjoUBTf == true){JneEjoUBTf = false;}
      if(HWCzBYswQZ == true){HWCzBYswQZ = false;}
      if(itjsFqbcHi == true){itjsFqbcHi = false;}
      if(oOsUwdjYKl == true){oOsUwdjYKl = false;}
      if(srXjqNfXok == true){srXjqNfXok = false;}
      if(weIStPEkzr == true){weIStPEkzr = false;}
      if(MrsjqschDW == true){MrsjqschDW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXUFZQAPCD
{ 
  void MUmEsSJQNl()
  { 
      bool IfHKVVDHLn = false;
      bool nUAAnpQZVk = false;
      bool coPoyGHnPm = false;
      bool FaqDfTtOag = false;
      bool AlgcTCWVcz = false;
      bool lxKQDSPSMO = false;
      bool OOrXhNdwUU = false;
      bool wCyokpImUu = false;
      bool ilLPAIPZAM = false;
      bool EbBMSktIuG = false;
      bool YZAIDjzUfM = false;
      bool JbxQecDbWY = false;
      bool xDwHPTAkWz = false;
      bool wzrOVJkCLQ = false;
      bool JutmCbdjgo = false;
      bool hRlVIVdrri = false;
      bool iNyfQKjiuV = false;
      bool qAQGPCIIFn = false;
      bool pQDgRdNVGA = false;
      bool frJcguwOWr = false;
      string NIcfQqOMKK;
      string AwPndyejmx;
      string ZbxsRTYwtp;
      string jQBiSeKSmE;
      string GoUOXEgsRn;
      string JsCSnkLjNw;
      string RSSTajugUy;
      string mLwipkHhUM;
      string mfdGfpNhug;
      string TaFplnWAmm;
      string IAXTAywTbD;
      string dcOAJlnMmk;
      string WNkmeMFGxC;
      string NGuhDmHKFh;
      string ssGqDpMEgA;
      string zJMCQuOjnn;
      string rpWYoWhgxV;
      string ddGFqcHsjn;
      string zBYxDDtrQI;
      string XXVRpDWgCf;
      if(NIcfQqOMKK == IAXTAywTbD){IfHKVVDHLn = true;}
      else if(IAXTAywTbD == NIcfQqOMKK){YZAIDjzUfM = true;}
      if(AwPndyejmx == dcOAJlnMmk){nUAAnpQZVk = true;}
      else if(dcOAJlnMmk == AwPndyejmx){JbxQecDbWY = true;}
      if(ZbxsRTYwtp == WNkmeMFGxC){coPoyGHnPm = true;}
      else if(WNkmeMFGxC == ZbxsRTYwtp){xDwHPTAkWz = true;}
      if(jQBiSeKSmE == NGuhDmHKFh){FaqDfTtOag = true;}
      else if(NGuhDmHKFh == jQBiSeKSmE){wzrOVJkCLQ = true;}
      if(GoUOXEgsRn == ssGqDpMEgA){AlgcTCWVcz = true;}
      else if(ssGqDpMEgA == GoUOXEgsRn){JutmCbdjgo = true;}
      if(JsCSnkLjNw == zJMCQuOjnn){lxKQDSPSMO = true;}
      else if(zJMCQuOjnn == JsCSnkLjNw){hRlVIVdrri = true;}
      if(RSSTajugUy == rpWYoWhgxV){OOrXhNdwUU = true;}
      else if(rpWYoWhgxV == RSSTajugUy){iNyfQKjiuV = true;}
      if(mLwipkHhUM == ddGFqcHsjn){wCyokpImUu = true;}
      if(mfdGfpNhug == zBYxDDtrQI){ilLPAIPZAM = true;}
      if(TaFplnWAmm == XXVRpDWgCf){EbBMSktIuG = true;}
      while(ddGFqcHsjn == mLwipkHhUM){qAQGPCIIFn = true;}
      while(zBYxDDtrQI == zBYxDDtrQI){pQDgRdNVGA = true;}
      while(XXVRpDWgCf == XXVRpDWgCf){frJcguwOWr = true;}
      if(IfHKVVDHLn == true){IfHKVVDHLn = false;}
      if(nUAAnpQZVk == true){nUAAnpQZVk = false;}
      if(coPoyGHnPm == true){coPoyGHnPm = false;}
      if(FaqDfTtOag == true){FaqDfTtOag = false;}
      if(AlgcTCWVcz == true){AlgcTCWVcz = false;}
      if(lxKQDSPSMO == true){lxKQDSPSMO = false;}
      if(OOrXhNdwUU == true){OOrXhNdwUU = false;}
      if(wCyokpImUu == true){wCyokpImUu = false;}
      if(ilLPAIPZAM == true){ilLPAIPZAM = false;}
      if(EbBMSktIuG == true){EbBMSktIuG = false;}
      if(YZAIDjzUfM == true){YZAIDjzUfM = false;}
      if(JbxQecDbWY == true){JbxQecDbWY = false;}
      if(xDwHPTAkWz == true){xDwHPTAkWz = false;}
      if(wzrOVJkCLQ == true){wzrOVJkCLQ = false;}
      if(JutmCbdjgo == true){JutmCbdjgo = false;}
      if(hRlVIVdrri == true){hRlVIVdrri = false;}
      if(iNyfQKjiuV == true){iNyfQKjiuV = false;}
      if(qAQGPCIIFn == true){qAQGPCIIFn = false;}
      if(pQDgRdNVGA == true){pQDgRdNVGA = false;}
      if(frJcguwOWr == true){frJcguwOWr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGQHXGPMOU
{ 
  void pAjiumbFsO()
  { 
      bool FGOlTxLBdG = false;
      bool INeVoXCsnd = false;
      bool QabDbhAfdt = false;
      bool QEBKMjKLez = false;
      bool bKGYTkfSFP = false;
      bool ZWfQcddLJk = false;
      bool xfXjpDMTIE = false;
      bool NqOnCFUDip = false;
      bool BhaNTsYjhi = false;
      bool FzBsCwmWiP = false;
      bool YMJACiIqOW = false;
      bool JabSiOEJQw = false;
      bool eblZyOoUlG = false;
      bool SxUSRoXZLj = false;
      bool khVKZeWhJm = false;
      bool qcFlkwajCm = false;
      bool tmEIELGIAt = false;
      bool qdyfKwGazT = false;
      bool rGLzOpqhhU = false;
      bool NnXXpycMGO = false;
      string ySPrYSkwqy;
      string nZQyILFaLy;
      string GldmfJXWmg;
      string JhZEqGRyPw;
      string OuhplKeRYd;
      string aVTCBMncLP;
      string tNJKnFALGB;
      string sHKOiKDnAU;
      string dFyJFnOWCe;
      string RolzCBkXBf;
      string KTLWjSKESp;
      string IzbqlnPzEA;
      string qcIbjEUKMh;
      string YfmTKKtaZl;
      string cJELWRNuNN;
      string klTBogKimf;
      string yArjQcMHfb;
      string snZRWhYwER;
      string pZxywmLkec;
      string zLntncQTts;
      if(ySPrYSkwqy == KTLWjSKESp){FGOlTxLBdG = true;}
      else if(KTLWjSKESp == ySPrYSkwqy){YMJACiIqOW = true;}
      if(nZQyILFaLy == IzbqlnPzEA){INeVoXCsnd = true;}
      else if(IzbqlnPzEA == nZQyILFaLy){JabSiOEJQw = true;}
      if(GldmfJXWmg == qcIbjEUKMh){QabDbhAfdt = true;}
      else if(qcIbjEUKMh == GldmfJXWmg){eblZyOoUlG = true;}
      if(JhZEqGRyPw == YfmTKKtaZl){QEBKMjKLez = true;}
      else if(YfmTKKtaZl == JhZEqGRyPw){SxUSRoXZLj = true;}
      if(OuhplKeRYd == cJELWRNuNN){bKGYTkfSFP = true;}
      else if(cJELWRNuNN == OuhplKeRYd){khVKZeWhJm = true;}
      if(aVTCBMncLP == klTBogKimf){ZWfQcddLJk = true;}
      else if(klTBogKimf == aVTCBMncLP){qcFlkwajCm = true;}
      if(tNJKnFALGB == yArjQcMHfb){xfXjpDMTIE = true;}
      else if(yArjQcMHfb == tNJKnFALGB){tmEIELGIAt = true;}
      if(sHKOiKDnAU == snZRWhYwER){NqOnCFUDip = true;}
      if(dFyJFnOWCe == pZxywmLkec){BhaNTsYjhi = true;}
      if(RolzCBkXBf == zLntncQTts){FzBsCwmWiP = true;}
      while(snZRWhYwER == sHKOiKDnAU){qdyfKwGazT = true;}
      while(pZxywmLkec == pZxywmLkec){rGLzOpqhhU = true;}
      while(zLntncQTts == zLntncQTts){NnXXpycMGO = true;}
      if(FGOlTxLBdG == true){FGOlTxLBdG = false;}
      if(INeVoXCsnd == true){INeVoXCsnd = false;}
      if(QabDbhAfdt == true){QabDbhAfdt = false;}
      if(QEBKMjKLez == true){QEBKMjKLez = false;}
      if(bKGYTkfSFP == true){bKGYTkfSFP = false;}
      if(ZWfQcddLJk == true){ZWfQcddLJk = false;}
      if(xfXjpDMTIE == true){xfXjpDMTIE = false;}
      if(NqOnCFUDip == true){NqOnCFUDip = false;}
      if(BhaNTsYjhi == true){BhaNTsYjhi = false;}
      if(FzBsCwmWiP == true){FzBsCwmWiP = false;}
      if(YMJACiIqOW == true){YMJACiIqOW = false;}
      if(JabSiOEJQw == true){JabSiOEJQw = false;}
      if(eblZyOoUlG == true){eblZyOoUlG = false;}
      if(SxUSRoXZLj == true){SxUSRoXZLj = false;}
      if(khVKZeWhJm == true){khVKZeWhJm = false;}
      if(qcFlkwajCm == true){qcFlkwajCm = false;}
      if(tmEIELGIAt == true){tmEIELGIAt = false;}
      if(qdyfKwGazT == true){qdyfKwGazT = false;}
      if(rGLzOpqhhU == true){rGLzOpqhhU = false;}
      if(NnXXpycMGO == true){NnXXpycMGO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSSDIJPNAP
{ 
  void wtzpaDnLfq()
  { 
      bool ButjMIbnpB = false;
      bool GRiBwRMgIn = false;
      bool rYFJYXNjBY = false;
      bool PRznqiXRNY = false;
      bool rgTqLjAFci = false;
      bool plNHMbpkLo = false;
      bool trmQknStKN = false;
      bool ttSjuLFNxo = false;
      bool WHGRidErbP = false;
      bool rmGYeztDFX = false;
      bool RFuPouTdLB = false;
      bool VbmWRllVgH = false;
      bool jaStUGnsEw = false;
      bool QCIZWRMqbm = false;
      bool KZfZsPzjHr = false;
      bool MYVxmqmAth = false;
      bool HZYPjTTNzA = false;
      bool ZustxJtrBE = false;
      bool HDlMirfKlf = false;
      bool dLwsfjBQpY = false;
      string pwCkfiWCml;
      string yEBYWJTrwQ;
      string IXuEfJIXqm;
      string tMjiOxRRZN;
      string BGeFgSfCxq;
      string bxjSQSByEV;
      string ZyKzrlUSKZ;
      string qCShOCroXN;
      string dFaALxcRSu;
      string wTNDnCweNt;
      string yNrXzYdBDO;
      string aLaqrTXKnu;
      string JCzOcXoOtM;
      string GMbcOQNCAl;
      string SaNETjsWLT;
      string dlqRjuNdta;
      string jPHqIOixbb;
      string GVJCbioutr;
      string eSCahUVJrS;
      string CiHZBDSWuF;
      if(pwCkfiWCml == yNrXzYdBDO){ButjMIbnpB = true;}
      else if(yNrXzYdBDO == pwCkfiWCml){RFuPouTdLB = true;}
      if(yEBYWJTrwQ == aLaqrTXKnu){GRiBwRMgIn = true;}
      else if(aLaqrTXKnu == yEBYWJTrwQ){VbmWRllVgH = true;}
      if(IXuEfJIXqm == JCzOcXoOtM){rYFJYXNjBY = true;}
      else if(JCzOcXoOtM == IXuEfJIXqm){jaStUGnsEw = true;}
      if(tMjiOxRRZN == GMbcOQNCAl){PRznqiXRNY = true;}
      else if(GMbcOQNCAl == tMjiOxRRZN){QCIZWRMqbm = true;}
      if(BGeFgSfCxq == SaNETjsWLT){rgTqLjAFci = true;}
      else if(SaNETjsWLT == BGeFgSfCxq){KZfZsPzjHr = true;}
      if(bxjSQSByEV == dlqRjuNdta){plNHMbpkLo = true;}
      else if(dlqRjuNdta == bxjSQSByEV){MYVxmqmAth = true;}
      if(ZyKzrlUSKZ == jPHqIOixbb){trmQknStKN = true;}
      else if(jPHqIOixbb == ZyKzrlUSKZ){HZYPjTTNzA = true;}
      if(qCShOCroXN == GVJCbioutr){ttSjuLFNxo = true;}
      if(dFaALxcRSu == eSCahUVJrS){WHGRidErbP = true;}
      if(wTNDnCweNt == CiHZBDSWuF){rmGYeztDFX = true;}
      while(GVJCbioutr == qCShOCroXN){ZustxJtrBE = true;}
      while(eSCahUVJrS == eSCahUVJrS){HDlMirfKlf = true;}
      while(CiHZBDSWuF == CiHZBDSWuF){dLwsfjBQpY = true;}
      if(ButjMIbnpB == true){ButjMIbnpB = false;}
      if(GRiBwRMgIn == true){GRiBwRMgIn = false;}
      if(rYFJYXNjBY == true){rYFJYXNjBY = false;}
      if(PRznqiXRNY == true){PRznqiXRNY = false;}
      if(rgTqLjAFci == true){rgTqLjAFci = false;}
      if(plNHMbpkLo == true){plNHMbpkLo = false;}
      if(trmQknStKN == true){trmQknStKN = false;}
      if(ttSjuLFNxo == true){ttSjuLFNxo = false;}
      if(WHGRidErbP == true){WHGRidErbP = false;}
      if(rmGYeztDFX == true){rmGYeztDFX = false;}
      if(RFuPouTdLB == true){RFuPouTdLB = false;}
      if(VbmWRllVgH == true){VbmWRllVgH = false;}
      if(jaStUGnsEw == true){jaStUGnsEw = false;}
      if(QCIZWRMqbm == true){QCIZWRMqbm = false;}
      if(KZfZsPzjHr == true){KZfZsPzjHr = false;}
      if(MYVxmqmAth == true){MYVxmqmAth = false;}
      if(HZYPjTTNzA == true){HZYPjTTNzA = false;}
      if(ZustxJtrBE == true){ZustxJtrBE = false;}
      if(HDlMirfKlf == true){HDlMirfKlf = false;}
      if(dLwsfjBQpY == true){dLwsfjBQpY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGXWEQSGXE
{ 
  void OYZkdcbgjf()
  { 
      bool CgjaencXom = false;
      bool FsbGcLZTyF = false;
      bool rxWqyTNutS = false;
      bool iJXCidpLxi = false;
      bool NTBeRMNPqN = false;
      bool KkdzYEKrbL = false;
      bool ahcWDuVZWy = false;
      bool UOWOrXwqYk = false;
      bool FyDgIxfYcd = false;
      bool TxilIfpdaW = false;
      bool qnrsruOOHA = false;
      bool ISTpFcdwOG = false;
      bool OxwsdWejGM = false;
      bool gSPCtRGJnM = false;
      bool hRQbVAdrgf = false;
      bool BtPUHtryOV = false;
      bool PeIuSpCQwn = false;
      bool WUIBYxfTXd = false;
      bool rmDaKmCuuz = false;
      bool YHtRwCJVJe = false;
      string sCgwQYPocO;
      string uAWnHhwPuH;
      string TVAmZyUokd;
      string mlxKtQxxhp;
      string sTSVagPOJG;
      string JLUfdWCsVR;
      string DaDybIDMtp;
      string kzgFNzDdLs;
      string hGeeUaRQfW;
      string ODaPlSQUtS;
      string dDTSVJdPRe;
      string TXhcjxuYdA;
      string qlfXbgXRSu;
      string hijsOemMIK;
      string xCzBCpVxfo;
      string WrqsarXwqn;
      string lMwWwknnNF;
      string KiPSDnldUk;
      string LZlcXprpRW;
      string GpVUYkFcFR;
      if(sCgwQYPocO == dDTSVJdPRe){CgjaencXom = true;}
      else if(dDTSVJdPRe == sCgwQYPocO){qnrsruOOHA = true;}
      if(uAWnHhwPuH == TXhcjxuYdA){FsbGcLZTyF = true;}
      else if(TXhcjxuYdA == uAWnHhwPuH){ISTpFcdwOG = true;}
      if(TVAmZyUokd == qlfXbgXRSu){rxWqyTNutS = true;}
      else if(qlfXbgXRSu == TVAmZyUokd){OxwsdWejGM = true;}
      if(mlxKtQxxhp == hijsOemMIK){iJXCidpLxi = true;}
      else if(hijsOemMIK == mlxKtQxxhp){gSPCtRGJnM = true;}
      if(sTSVagPOJG == xCzBCpVxfo){NTBeRMNPqN = true;}
      else if(xCzBCpVxfo == sTSVagPOJG){hRQbVAdrgf = true;}
      if(JLUfdWCsVR == WrqsarXwqn){KkdzYEKrbL = true;}
      else if(WrqsarXwqn == JLUfdWCsVR){BtPUHtryOV = true;}
      if(DaDybIDMtp == lMwWwknnNF){ahcWDuVZWy = true;}
      else if(lMwWwknnNF == DaDybIDMtp){PeIuSpCQwn = true;}
      if(kzgFNzDdLs == KiPSDnldUk){UOWOrXwqYk = true;}
      if(hGeeUaRQfW == LZlcXprpRW){FyDgIxfYcd = true;}
      if(ODaPlSQUtS == GpVUYkFcFR){TxilIfpdaW = true;}
      while(KiPSDnldUk == kzgFNzDdLs){WUIBYxfTXd = true;}
      while(LZlcXprpRW == LZlcXprpRW){rmDaKmCuuz = true;}
      while(GpVUYkFcFR == GpVUYkFcFR){YHtRwCJVJe = true;}
      if(CgjaencXom == true){CgjaencXom = false;}
      if(FsbGcLZTyF == true){FsbGcLZTyF = false;}
      if(rxWqyTNutS == true){rxWqyTNutS = false;}
      if(iJXCidpLxi == true){iJXCidpLxi = false;}
      if(NTBeRMNPqN == true){NTBeRMNPqN = false;}
      if(KkdzYEKrbL == true){KkdzYEKrbL = false;}
      if(ahcWDuVZWy == true){ahcWDuVZWy = false;}
      if(UOWOrXwqYk == true){UOWOrXwqYk = false;}
      if(FyDgIxfYcd == true){FyDgIxfYcd = false;}
      if(TxilIfpdaW == true){TxilIfpdaW = false;}
      if(qnrsruOOHA == true){qnrsruOOHA = false;}
      if(ISTpFcdwOG == true){ISTpFcdwOG = false;}
      if(OxwsdWejGM == true){OxwsdWejGM = false;}
      if(gSPCtRGJnM == true){gSPCtRGJnM = false;}
      if(hRQbVAdrgf == true){hRQbVAdrgf = false;}
      if(BtPUHtryOV == true){BtPUHtryOV = false;}
      if(PeIuSpCQwn == true){PeIuSpCQwn = false;}
      if(WUIBYxfTXd == true){WUIBYxfTXd = false;}
      if(rmDaKmCuuz == true){rmDaKmCuuz = false;}
      if(YHtRwCJVJe == true){YHtRwCJVJe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KKHTBXHSSK
{ 
  void holjLkTgBm()
  { 
      bool LVOrrkMIwQ = false;
      bool BTKqMTKZTG = false;
      bool EweKYinIDN = false;
      bool PUeyEMxrRH = false;
      bool dnGOTiEFzJ = false;
      bool tttAyPqDSI = false;
      bool wDFiBfoLlA = false;
      bool WSILbQoPpo = false;
      bool eiIsSUZeAo = false;
      bool UsYJLahXNn = false;
      bool trSzmblhXg = false;
      bool ZaNcdMtLPf = false;
      bool FJLxedszAB = false;
      bool hRBCulQJFq = false;
      bool iqGSOsfwey = false;
      bool fVIhijgUUJ = false;
      bool hmhWzIZLhq = false;
      bool wkGXwNCrhk = false;
      bool xxTBULJTSK = false;
      bool EunwJwJjTG = false;
      string oOzLNMqJGc;
      string PSxopUMLqF;
      string qjzmTUySOU;
      string KmCfuoiYzb;
      string hHRARONJhw;
      string ZKyyGFPLqs;
      string NYukScQQtA;
      string lmLOXjRzUE;
      string GojRuznDZp;
      string ZWgGOJLfgo;
      string ywPgKlzjaV;
      string mPpllXncpS;
      string nMpEZOGEAN;
      string YlRfGJZDHJ;
      string AEbEDJftTp;
      string UhoOAkGKGu;
      string eujMxAyKfb;
      string yjVgSjjlAP;
      string hLjJrpwCfU;
      string DOwMdFUOGC;
      if(oOzLNMqJGc == ywPgKlzjaV){LVOrrkMIwQ = true;}
      else if(ywPgKlzjaV == oOzLNMqJGc){trSzmblhXg = true;}
      if(PSxopUMLqF == mPpllXncpS){BTKqMTKZTG = true;}
      else if(mPpllXncpS == PSxopUMLqF){ZaNcdMtLPf = true;}
      if(qjzmTUySOU == nMpEZOGEAN){EweKYinIDN = true;}
      else if(nMpEZOGEAN == qjzmTUySOU){FJLxedszAB = true;}
      if(KmCfuoiYzb == YlRfGJZDHJ){PUeyEMxrRH = true;}
      else if(YlRfGJZDHJ == KmCfuoiYzb){hRBCulQJFq = true;}
      if(hHRARONJhw == AEbEDJftTp){dnGOTiEFzJ = true;}
      else if(AEbEDJftTp == hHRARONJhw){iqGSOsfwey = true;}
      if(ZKyyGFPLqs == UhoOAkGKGu){tttAyPqDSI = true;}
      else if(UhoOAkGKGu == ZKyyGFPLqs){fVIhijgUUJ = true;}
      if(NYukScQQtA == eujMxAyKfb){wDFiBfoLlA = true;}
      else if(eujMxAyKfb == NYukScQQtA){hmhWzIZLhq = true;}
      if(lmLOXjRzUE == yjVgSjjlAP){WSILbQoPpo = true;}
      if(GojRuznDZp == hLjJrpwCfU){eiIsSUZeAo = true;}
      if(ZWgGOJLfgo == DOwMdFUOGC){UsYJLahXNn = true;}
      while(yjVgSjjlAP == lmLOXjRzUE){wkGXwNCrhk = true;}
      while(hLjJrpwCfU == hLjJrpwCfU){xxTBULJTSK = true;}
      while(DOwMdFUOGC == DOwMdFUOGC){EunwJwJjTG = true;}
      if(LVOrrkMIwQ == true){LVOrrkMIwQ = false;}
      if(BTKqMTKZTG == true){BTKqMTKZTG = false;}
      if(EweKYinIDN == true){EweKYinIDN = false;}
      if(PUeyEMxrRH == true){PUeyEMxrRH = false;}
      if(dnGOTiEFzJ == true){dnGOTiEFzJ = false;}
      if(tttAyPqDSI == true){tttAyPqDSI = false;}
      if(wDFiBfoLlA == true){wDFiBfoLlA = false;}
      if(WSILbQoPpo == true){WSILbQoPpo = false;}
      if(eiIsSUZeAo == true){eiIsSUZeAo = false;}
      if(UsYJLahXNn == true){UsYJLahXNn = false;}
      if(trSzmblhXg == true){trSzmblhXg = false;}
      if(ZaNcdMtLPf == true){ZaNcdMtLPf = false;}
      if(FJLxedszAB == true){FJLxedszAB = false;}
      if(hRBCulQJFq == true){hRBCulQJFq = false;}
      if(iqGSOsfwey == true){iqGSOsfwey = false;}
      if(fVIhijgUUJ == true){fVIhijgUUJ = false;}
      if(hmhWzIZLhq == true){hmhWzIZLhq = false;}
      if(wkGXwNCrhk == true){wkGXwNCrhk = false;}
      if(xxTBULJTSK == true){xxTBULJTSK = false;}
      if(EunwJwJjTG == true){EunwJwJjTG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWJPXWTLCC
{ 
  void LCuglfbyOB()
  { 
      bool rckeNyHCgZ = false;
      bool qUJabQBddS = false;
      bool owGzRCAVMy = false;
      bool BQDgSflAmC = false;
      bool rjAunPCFAz = false;
      bool geVjEwVlNK = false;
      bool ykohXaRcIu = false;
      bool dApbaEwKKB = false;
      bool zuVNRWuTcW = false;
      bool JAmbDHuRXN = false;
      bool yZwFUfnsIA = false;
      bool ALaLLDOaQA = false;
      bool eyAlkdNOXT = false;
      bool IdlwDYyQsl = false;
      bool iBKcWyYaQA = false;
      bool rTBWhzZKTp = false;
      bool SZVoqVZeIl = false;
      bool FyhdRdnXOm = false;
      bool ElxWaobOND = false;
      bool zmwDTJfUkA = false;
      string msmwRQfhwQ;
      string SEMHAHSjCi;
      string NKQRkmYoJg;
      string MXQqtWHuah;
      string WpcNcrXtzy;
      string ADbYwcbVLd;
      string rpXOEtnVNd;
      string zXJTMXgDnr;
      string OeoLgIwqtQ;
      string uliwpfRNIh;
      string ECgVyctILY;
      string uYgSONALhu;
      string ywawhNnMdf;
      string FStFnMxTNE;
      string OmfVVWEQgc;
      string eGfNjHakmk;
      string ngeeSbdbeC;
      string PgycfKQFaL;
      string JXeABzmgVf;
      string kMgbPhIACs;
      if(msmwRQfhwQ == ECgVyctILY){rckeNyHCgZ = true;}
      else if(ECgVyctILY == msmwRQfhwQ){yZwFUfnsIA = true;}
      if(SEMHAHSjCi == uYgSONALhu){qUJabQBddS = true;}
      else if(uYgSONALhu == SEMHAHSjCi){ALaLLDOaQA = true;}
      if(NKQRkmYoJg == ywawhNnMdf){owGzRCAVMy = true;}
      else if(ywawhNnMdf == NKQRkmYoJg){eyAlkdNOXT = true;}
      if(MXQqtWHuah == FStFnMxTNE){BQDgSflAmC = true;}
      else if(FStFnMxTNE == MXQqtWHuah){IdlwDYyQsl = true;}
      if(WpcNcrXtzy == OmfVVWEQgc){rjAunPCFAz = true;}
      else if(OmfVVWEQgc == WpcNcrXtzy){iBKcWyYaQA = true;}
      if(ADbYwcbVLd == eGfNjHakmk){geVjEwVlNK = true;}
      else if(eGfNjHakmk == ADbYwcbVLd){rTBWhzZKTp = true;}
      if(rpXOEtnVNd == ngeeSbdbeC){ykohXaRcIu = true;}
      else if(ngeeSbdbeC == rpXOEtnVNd){SZVoqVZeIl = true;}
      if(zXJTMXgDnr == PgycfKQFaL){dApbaEwKKB = true;}
      if(OeoLgIwqtQ == JXeABzmgVf){zuVNRWuTcW = true;}
      if(uliwpfRNIh == kMgbPhIACs){JAmbDHuRXN = true;}
      while(PgycfKQFaL == zXJTMXgDnr){FyhdRdnXOm = true;}
      while(JXeABzmgVf == JXeABzmgVf){ElxWaobOND = true;}
      while(kMgbPhIACs == kMgbPhIACs){zmwDTJfUkA = true;}
      if(rckeNyHCgZ == true){rckeNyHCgZ = false;}
      if(qUJabQBddS == true){qUJabQBddS = false;}
      if(owGzRCAVMy == true){owGzRCAVMy = false;}
      if(BQDgSflAmC == true){BQDgSflAmC = false;}
      if(rjAunPCFAz == true){rjAunPCFAz = false;}
      if(geVjEwVlNK == true){geVjEwVlNK = false;}
      if(ykohXaRcIu == true){ykohXaRcIu = false;}
      if(dApbaEwKKB == true){dApbaEwKKB = false;}
      if(zuVNRWuTcW == true){zuVNRWuTcW = false;}
      if(JAmbDHuRXN == true){JAmbDHuRXN = false;}
      if(yZwFUfnsIA == true){yZwFUfnsIA = false;}
      if(ALaLLDOaQA == true){ALaLLDOaQA = false;}
      if(eyAlkdNOXT == true){eyAlkdNOXT = false;}
      if(IdlwDYyQsl == true){IdlwDYyQsl = false;}
      if(iBKcWyYaQA == true){iBKcWyYaQA = false;}
      if(rTBWhzZKTp == true){rTBWhzZKTp = false;}
      if(SZVoqVZeIl == true){SZVoqVZeIl = false;}
      if(FyhdRdnXOm == true){FyhdRdnXOm = false;}
      if(ElxWaobOND == true){ElxWaobOND = false;}
      if(zmwDTJfUkA == true){zmwDTJfUkA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGZZRBTIYK
{ 
  void xufwXkYKKG()
  { 
      bool GopITiZsMC = false;
      bool yKEKFjrzft = false;
      bool qJnNDccMZg = false;
      bool GiEfLNLItp = false;
      bool lqESFQtfTL = false;
      bool rnheqxBcEq = false;
      bool FMTfwPGYzr = false;
      bool XiFoHzFVIm = false;
      bool hwrNnRAYnN = false;
      bool MiDDjYXXVp = false;
      bool JUgbmJirWr = false;
      bool reURIJTFrd = false;
      bool OgkkfoeCEh = false;
      bool bgARcMPQad = false;
      bool iHCwVgOlta = false;
      bool FReqbcjuuy = false;
      bool dfnnPKeCnw = false;
      bool sDeNuGenPz = false;
      bool arHccJBIpA = false;
      bool cUVbACTNfK = false;
      string bBSWBbMzBc;
      string VbSELwmnBx;
      string DctcsmUajP;
      string KzGwoKRCyz;
      string cxGIPgVIdp;
      string hDZDkzHocN;
      string HkPlSVUVOB;
      string djoBUFVkML;
      string QMwtgHZDLo;
      string CbYkqqgUpt;
      string MzsbLyNXie;
      string dVcQwunUEL;
      string wRKZzCKEKc;
      string XBuSzQSTii;
      string sBTfLgzInw;
      string DMPdxuoTcI;
      string mINFGcZJRf;
      string bTlVRtxdOR;
      string DCQNZLkQVD;
      string bzqZwknNZi;
      if(bBSWBbMzBc == MzsbLyNXie){GopITiZsMC = true;}
      else if(MzsbLyNXie == bBSWBbMzBc){JUgbmJirWr = true;}
      if(VbSELwmnBx == dVcQwunUEL){yKEKFjrzft = true;}
      else if(dVcQwunUEL == VbSELwmnBx){reURIJTFrd = true;}
      if(DctcsmUajP == wRKZzCKEKc){qJnNDccMZg = true;}
      else if(wRKZzCKEKc == DctcsmUajP){OgkkfoeCEh = true;}
      if(KzGwoKRCyz == XBuSzQSTii){GiEfLNLItp = true;}
      else if(XBuSzQSTii == KzGwoKRCyz){bgARcMPQad = true;}
      if(cxGIPgVIdp == sBTfLgzInw){lqESFQtfTL = true;}
      else if(sBTfLgzInw == cxGIPgVIdp){iHCwVgOlta = true;}
      if(hDZDkzHocN == DMPdxuoTcI){rnheqxBcEq = true;}
      else if(DMPdxuoTcI == hDZDkzHocN){FReqbcjuuy = true;}
      if(HkPlSVUVOB == mINFGcZJRf){FMTfwPGYzr = true;}
      else if(mINFGcZJRf == HkPlSVUVOB){dfnnPKeCnw = true;}
      if(djoBUFVkML == bTlVRtxdOR){XiFoHzFVIm = true;}
      if(QMwtgHZDLo == DCQNZLkQVD){hwrNnRAYnN = true;}
      if(CbYkqqgUpt == bzqZwknNZi){MiDDjYXXVp = true;}
      while(bTlVRtxdOR == djoBUFVkML){sDeNuGenPz = true;}
      while(DCQNZLkQVD == DCQNZLkQVD){arHccJBIpA = true;}
      while(bzqZwknNZi == bzqZwknNZi){cUVbACTNfK = true;}
      if(GopITiZsMC == true){GopITiZsMC = false;}
      if(yKEKFjrzft == true){yKEKFjrzft = false;}
      if(qJnNDccMZg == true){qJnNDccMZg = false;}
      if(GiEfLNLItp == true){GiEfLNLItp = false;}
      if(lqESFQtfTL == true){lqESFQtfTL = false;}
      if(rnheqxBcEq == true){rnheqxBcEq = false;}
      if(FMTfwPGYzr == true){FMTfwPGYzr = false;}
      if(XiFoHzFVIm == true){XiFoHzFVIm = false;}
      if(hwrNnRAYnN == true){hwrNnRAYnN = false;}
      if(MiDDjYXXVp == true){MiDDjYXXVp = false;}
      if(JUgbmJirWr == true){JUgbmJirWr = false;}
      if(reURIJTFrd == true){reURIJTFrd = false;}
      if(OgkkfoeCEh == true){OgkkfoeCEh = false;}
      if(bgARcMPQad == true){bgARcMPQad = false;}
      if(iHCwVgOlta == true){iHCwVgOlta = false;}
      if(FReqbcjuuy == true){FReqbcjuuy = false;}
      if(dfnnPKeCnw == true){dfnnPKeCnw = false;}
      if(sDeNuGenPz == true){sDeNuGenPz = false;}
      if(arHccJBIpA == true){arHccJBIpA = false;}
      if(cUVbACTNfK == true){cUVbACTNfK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYTAZDRITV
{ 
  void hBnGQpNhkk()
  { 
      bool NEDPWAcAAX = false;
      bool RTcocpkicH = false;
      bool OIcsSXrgfV = false;
      bool CKHacIWWZc = false;
      bool sWXTipmYpk = false;
      bool YVNoZFaKwy = false;
      bool HwTdVHLBLU = false;
      bool SNIANqjIKc = false;
      bool kTquxfxSAX = false;
      bool gMabUwDsya = false;
      bool dkMURKNMbi = false;
      bool URzTNnFYgo = false;
      bool KsAnnGmgfQ = false;
      bool nqKjyzGVcl = false;
      bool SjpRDOMHOf = false;
      bool qdLIQkjYfK = false;
      bool WfgKudHPUN = false;
      bool giutVZCikZ = false;
      bool tfSzZJeCSN = false;
      bool OhoSOlDfVZ = false;
      string fpNljFKDsd;
      string mJNklzApLT;
      string TaBdliPuKL;
      string bYYZzUzMFx;
      string YfnzkBtWia;
      string cnBkSFnjzB;
      string pOsgCOkmlR;
      string AmjOtnmCrk;
      string osMihmWmGt;
      string fPNEGJmGwV;
      string QGjRapEmqe;
      string SlqOLwCJzP;
      string qxgqkkZfHk;
      string AfFWTiIuIr;
      string ijwbbtYyrK;
      string HdHgeSYsfo;
      string QXfGdlfUtc;
      string nHAHfGAFPq;
      string MamwcWXXqB;
      string JPOSaKEpxo;
      if(fpNljFKDsd == QGjRapEmqe){NEDPWAcAAX = true;}
      else if(QGjRapEmqe == fpNljFKDsd){dkMURKNMbi = true;}
      if(mJNklzApLT == SlqOLwCJzP){RTcocpkicH = true;}
      else if(SlqOLwCJzP == mJNklzApLT){URzTNnFYgo = true;}
      if(TaBdliPuKL == qxgqkkZfHk){OIcsSXrgfV = true;}
      else if(qxgqkkZfHk == TaBdliPuKL){KsAnnGmgfQ = true;}
      if(bYYZzUzMFx == AfFWTiIuIr){CKHacIWWZc = true;}
      else if(AfFWTiIuIr == bYYZzUzMFx){nqKjyzGVcl = true;}
      if(YfnzkBtWia == ijwbbtYyrK){sWXTipmYpk = true;}
      else if(ijwbbtYyrK == YfnzkBtWia){SjpRDOMHOf = true;}
      if(cnBkSFnjzB == HdHgeSYsfo){YVNoZFaKwy = true;}
      else if(HdHgeSYsfo == cnBkSFnjzB){qdLIQkjYfK = true;}
      if(pOsgCOkmlR == QXfGdlfUtc){HwTdVHLBLU = true;}
      else if(QXfGdlfUtc == pOsgCOkmlR){WfgKudHPUN = true;}
      if(AmjOtnmCrk == nHAHfGAFPq){SNIANqjIKc = true;}
      if(osMihmWmGt == MamwcWXXqB){kTquxfxSAX = true;}
      if(fPNEGJmGwV == JPOSaKEpxo){gMabUwDsya = true;}
      while(nHAHfGAFPq == AmjOtnmCrk){giutVZCikZ = true;}
      while(MamwcWXXqB == MamwcWXXqB){tfSzZJeCSN = true;}
      while(JPOSaKEpxo == JPOSaKEpxo){OhoSOlDfVZ = true;}
      if(NEDPWAcAAX == true){NEDPWAcAAX = false;}
      if(RTcocpkicH == true){RTcocpkicH = false;}
      if(OIcsSXrgfV == true){OIcsSXrgfV = false;}
      if(CKHacIWWZc == true){CKHacIWWZc = false;}
      if(sWXTipmYpk == true){sWXTipmYpk = false;}
      if(YVNoZFaKwy == true){YVNoZFaKwy = false;}
      if(HwTdVHLBLU == true){HwTdVHLBLU = false;}
      if(SNIANqjIKc == true){SNIANqjIKc = false;}
      if(kTquxfxSAX == true){kTquxfxSAX = false;}
      if(gMabUwDsya == true){gMabUwDsya = false;}
      if(dkMURKNMbi == true){dkMURKNMbi = false;}
      if(URzTNnFYgo == true){URzTNnFYgo = false;}
      if(KsAnnGmgfQ == true){KsAnnGmgfQ = false;}
      if(nqKjyzGVcl == true){nqKjyzGVcl = false;}
      if(SjpRDOMHOf == true){SjpRDOMHOf = false;}
      if(qdLIQkjYfK == true){qdLIQkjYfK = false;}
      if(WfgKudHPUN == true){WfgKudHPUN = false;}
      if(giutVZCikZ == true){giutVZCikZ = false;}
      if(tfSzZJeCSN == true){tfSzZJeCSN = false;}
      if(OhoSOlDfVZ == true){OhoSOlDfVZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RYYZGIBCUG
{ 
  void TjIWmppWTR()
  { 
      bool pjGSgRgUku = false;
      bool mKuUbyZcXH = false;
      bool NlBnVNHTOA = false;
      bool VYLccDWsLN = false;
      bool VrTZZrPulK = false;
      bool KjnlVEhSwT = false;
      bool JNGkZNyRqX = false;
      bool bfQJlVRaNd = false;
      bool xLhEplkYHY = false;
      bool UExrDHlizL = false;
      bool syENidSdzA = false;
      bool lGERVyfBun = false;
      bool cZKRCXiYGd = false;
      bool iibBkzGTVL = false;
      bool SGZGmOzeVF = false;
      bool bjnLiTmmLK = false;
      bool tsXVQCeCgW = false;
      bool qLfiVVADdn = false;
      bool XEDBBztQSQ = false;
      bool LTIKRYiDpj = false;
      string HcVKuwVMoD;
      string lmsElQMBpf;
      string HQCGSMCwRj;
      string jTAAkdsjQr;
      string rSHwMKTAzg;
      string mYRMRqaPri;
      string tZtFSSmrSH;
      string XbjxnoIFsH;
      string rBxkwLCmhs;
      string DcrgySXCdt;
      string WahrJLoTYc;
      string hUWkprcJIH;
      string PzKYDtjCyU;
      string RGbzjRTEbk;
      string WhOFLiGGqF;
      string oOsVdXPInO;
      string alVDKarWAY;
      string YXgXkhjFNT;
      string mcLreDNFVM;
      string CKQNJjMLtj;
      if(HcVKuwVMoD == WahrJLoTYc){pjGSgRgUku = true;}
      else if(WahrJLoTYc == HcVKuwVMoD){syENidSdzA = true;}
      if(lmsElQMBpf == hUWkprcJIH){mKuUbyZcXH = true;}
      else if(hUWkprcJIH == lmsElQMBpf){lGERVyfBun = true;}
      if(HQCGSMCwRj == PzKYDtjCyU){NlBnVNHTOA = true;}
      else if(PzKYDtjCyU == HQCGSMCwRj){cZKRCXiYGd = true;}
      if(jTAAkdsjQr == RGbzjRTEbk){VYLccDWsLN = true;}
      else if(RGbzjRTEbk == jTAAkdsjQr){iibBkzGTVL = true;}
      if(rSHwMKTAzg == WhOFLiGGqF){VrTZZrPulK = true;}
      else if(WhOFLiGGqF == rSHwMKTAzg){SGZGmOzeVF = true;}
      if(mYRMRqaPri == oOsVdXPInO){KjnlVEhSwT = true;}
      else if(oOsVdXPInO == mYRMRqaPri){bjnLiTmmLK = true;}
      if(tZtFSSmrSH == alVDKarWAY){JNGkZNyRqX = true;}
      else if(alVDKarWAY == tZtFSSmrSH){tsXVQCeCgW = true;}
      if(XbjxnoIFsH == YXgXkhjFNT){bfQJlVRaNd = true;}
      if(rBxkwLCmhs == mcLreDNFVM){xLhEplkYHY = true;}
      if(DcrgySXCdt == CKQNJjMLtj){UExrDHlizL = true;}
      while(YXgXkhjFNT == XbjxnoIFsH){qLfiVVADdn = true;}
      while(mcLreDNFVM == mcLreDNFVM){XEDBBztQSQ = true;}
      while(CKQNJjMLtj == CKQNJjMLtj){LTIKRYiDpj = true;}
      if(pjGSgRgUku == true){pjGSgRgUku = false;}
      if(mKuUbyZcXH == true){mKuUbyZcXH = false;}
      if(NlBnVNHTOA == true){NlBnVNHTOA = false;}
      if(VYLccDWsLN == true){VYLccDWsLN = false;}
      if(VrTZZrPulK == true){VrTZZrPulK = false;}
      if(KjnlVEhSwT == true){KjnlVEhSwT = false;}
      if(JNGkZNyRqX == true){JNGkZNyRqX = false;}
      if(bfQJlVRaNd == true){bfQJlVRaNd = false;}
      if(xLhEplkYHY == true){xLhEplkYHY = false;}
      if(UExrDHlizL == true){UExrDHlizL = false;}
      if(syENidSdzA == true){syENidSdzA = false;}
      if(lGERVyfBun == true){lGERVyfBun = false;}
      if(cZKRCXiYGd == true){cZKRCXiYGd = false;}
      if(iibBkzGTVL == true){iibBkzGTVL = false;}
      if(SGZGmOzeVF == true){SGZGmOzeVF = false;}
      if(bjnLiTmmLK == true){bjnLiTmmLK = false;}
      if(tsXVQCeCgW == true){tsXVQCeCgW = false;}
      if(qLfiVVADdn == true){qLfiVVADdn = false;}
      if(XEDBBztQSQ == true){XEDBBztQSQ = false;}
      if(LTIKRYiDpj == true){LTIKRYiDpj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NETQVHHTTW
{ 
  void PIttwQJytg()
  { 
      bool hSuWtjZRia = false;
      bool KNaUNSVolX = false;
      bool xqNdrsobQF = false;
      bool mGgZRFjbfQ = false;
      bool xSbXecGDhH = false;
      bool QLDWNqFQdA = false;
      bool txBcmDgACI = false;
      bool isJVZdPpzP = false;
      bool lltIobCJMa = false;
      bool ATyeWARyja = false;
      bool wGAZYXChxi = false;
      bool bPROOICsnL = false;
      bool BWmbIOtdzZ = false;
      bool MQFXTfkTiR = false;
      bool ZUMcyjBiPO = false;
      bool xXKYZYSXRJ = false;
      bool cXiWVKJsui = false;
      bool WiJVkgJJdX = false;
      bool NLNkcnGgxt = false;
      bool MNCZoCkpHn = false;
      string XWlEaaaRXM;
      string qCVPpbGDWR;
      string VbTdHUXSgo;
      string gOJyQdPdbo;
      string NrIFubeoSE;
      string VAprsuCIxF;
      string CHkiecrWzM;
      string LbagEcTNhf;
      string oiAbSfYRFU;
      string aGgVmFHYaS;
      string iIpGrsZImP;
      string boaRQSHIQy;
      string DaRdkFuEtz;
      string VtmOxgssjY;
      string GPdoskfPFT;
      string yyIbPHpLUm;
      string yUOnthCMTi;
      string ZNYqrnxbkA;
      string YezZBWkLzo;
      string qgXwalApuK;
      if(XWlEaaaRXM == iIpGrsZImP){hSuWtjZRia = true;}
      else if(iIpGrsZImP == XWlEaaaRXM){wGAZYXChxi = true;}
      if(qCVPpbGDWR == boaRQSHIQy){KNaUNSVolX = true;}
      else if(boaRQSHIQy == qCVPpbGDWR){bPROOICsnL = true;}
      if(VbTdHUXSgo == DaRdkFuEtz){xqNdrsobQF = true;}
      else if(DaRdkFuEtz == VbTdHUXSgo){BWmbIOtdzZ = true;}
      if(gOJyQdPdbo == VtmOxgssjY){mGgZRFjbfQ = true;}
      else if(VtmOxgssjY == gOJyQdPdbo){MQFXTfkTiR = true;}
      if(NrIFubeoSE == GPdoskfPFT){xSbXecGDhH = true;}
      else if(GPdoskfPFT == NrIFubeoSE){ZUMcyjBiPO = true;}
      if(VAprsuCIxF == yyIbPHpLUm){QLDWNqFQdA = true;}
      else if(yyIbPHpLUm == VAprsuCIxF){xXKYZYSXRJ = true;}
      if(CHkiecrWzM == yUOnthCMTi){txBcmDgACI = true;}
      else if(yUOnthCMTi == CHkiecrWzM){cXiWVKJsui = true;}
      if(LbagEcTNhf == ZNYqrnxbkA){isJVZdPpzP = true;}
      if(oiAbSfYRFU == YezZBWkLzo){lltIobCJMa = true;}
      if(aGgVmFHYaS == qgXwalApuK){ATyeWARyja = true;}
      while(ZNYqrnxbkA == LbagEcTNhf){WiJVkgJJdX = true;}
      while(YezZBWkLzo == YezZBWkLzo){NLNkcnGgxt = true;}
      while(qgXwalApuK == qgXwalApuK){MNCZoCkpHn = true;}
      if(hSuWtjZRia == true){hSuWtjZRia = false;}
      if(KNaUNSVolX == true){KNaUNSVolX = false;}
      if(xqNdrsobQF == true){xqNdrsobQF = false;}
      if(mGgZRFjbfQ == true){mGgZRFjbfQ = false;}
      if(xSbXecGDhH == true){xSbXecGDhH = false;}
      if(QLDWNqFQdA == true){QLDWNqFQdA = false;}
      if(txBcmDgACI == true){txBcmDgACI = false;}
      if(isJVZdPpzP == true){isJVZdPpzP = false;}
      if(lltIobCJMa == true){lltIobCJMa = false;}
      if(ATyeWARyja == true){ATyeWARyja = false;}
      if(wGAZYXChxi == true){wGAZYXChxi = false;}
      if(bPROOICsnL == true){bPROOICsnL = false;}
      if(BWmbIOtdzZ == true){BWmbIOtdzZ = false;}
      if(MQFXTfkTiR == true){MQFXTfkTiR = false;}
      if(ZUMcyjBiPO == true){ZUMcyjBiPO = false;}
      if(xXKYZYSXRJ == true){xXKYZYSXRJ = false;}
      if(cXiWVKJsui == true){cXiWVKJsui = false;}
      if(WiJVkgJJdX == true){WiJVkgJJdX = false;}
      if(NLNkcnGgxt == true){NLNkcnGgxt = false;}
      if(MNCZoCkpHn == true){MNCZoCkpHn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYXQEKGVKR
{ 
  void NODJuQwKZr()
  { 
      bool jpRmwiJFez = false;
      bool PLfSpNryyU = false;
      bool lzHAeZuaUs = false;
      bool ANqCZhrYYt = false;
      bool yZQFYpVNPV = false;
      bool qcHQxkiRIV = false;
      bool mijkyCUcrH = false;
      bool USYEVMiCan = false;
      bool EhKyCWGaEo = false;
      bool zZQCHPoeGW = false;
      bool VrVHBYECuk = false;
      bool BgqUREXlib = false;
      bool usXCItCVxG = false;
      bool XDwESMMCwc = false;
      bool SDeTmSiwkC = false;
      bool qCwdabTSzG = false;
      bool WhFoNyklBF = false;
      bool rVoFJqOEPp = false;
      bool KFktOUHRcp = false;
      bool rsDpGjypFn = false;
      string RbiSryelrm;
      string UyDTbjfWEu;
      string GyzMusbQWd;
      string rlyRYHPrsp;
      string KKlUgkSBnK;
      string dPbAYScVXz;
      string VOPNthzktU;
      string TmcNkuMdeJ;
      string ZacLAcJyrG;
      string dsUtTwuXZz;
      string khGSpqmNPd;
      string FzqNYukDNR;
      string XBrnpaRhtn;
      string AoDfYrTJVI;
      string owhOBeBHUX;
      string KqJHajoScP;
      string YFTbcQuLog;
      string bbgEcbTcmK;
      string YKMVcIeuEo;
      string CBfGjibFkj;
      if(RbiSryelrm == khGSpqmNPd){jpRmwiJFez = true;}
      else if(khGSpqmNPd == RbiSryelrm){VrVHBYECuk = true;}
      if(UyDTbjfWEu == FzqNYukDNR){PLfSpNryyU = true;}
      else if(FzqNYukDNR == UyDTbjfWEu){BgqUREXlib = true;}
      if(GyzMusbQWd == XBrnpaRhtn){lzHAeZuaUs = true;}
      else if(XBrnpaRhtn == GyzMusbQWd){usXCItCVxG = true;}
      if(rlyRYHPrsp == AoDfYrTJVI){ANqCZhrYYt = true;}
      else if(AoDfYrTJVI == rlyRYHPrsp){XDwESMMCwc = true;}
      if(KKlUgkSBnK == owhOBeBHUX){yZQFYpVNPV = true;}
      else if(owhOBeBHUX == KKlUgkSBnK){SDeTmSiwkC = true;}
      if(dPbAYScVXz == KqJHajoScP){qcHQxkiRIV = true;}
      else if(KqJHajoScP == dPbAYScVXz){qCwdabTSzG = true;}
      if(VOPNthzktU == YFTbcQuLog){mijkyCUcrH = true;}
      else if(YFTbcQuLog == VOPNthzktU){WhFoNyklBF = true;}
      if(TmcNkuMdeJ == bbgEcbTcmK){USYEVMiCan = true;}
      if(ZacLAcJyrG == YKMVcIeuEo){EhKyCWGaEo = true;}
      if(dsUtTwuXZz == CBfGjibFkj){zZQCHPoeGW = true;}
      while(bbgEcbTcmK == TmcNkuMdeJ){rVoFJqOEPp = true;}
      while(YKMVcIeuEo == YKMVcIeuEo){KFktOUHRcp = true;}
      while(CBfGjibFkj == CBfGjibFkj){rsDpGjypFn = true;}
      if(jpRmwiJFez == true){jpRmwiJFez = false;}
      if(PLfSpNryyU == true){PLfSpNryyU = false;}
      if(lzHAeZuaUs == true){lzHAeZuaUs = false;}
      if(ANqCZhrYYt == true){ANqCZhrYYt = false;}
      if(yZQFYpVNPV == true){yZQFYpVNPV = false;}
      if(qcHQxkiRIV == true){qcHQxkiRIV = false;}
      if(mijkyCUcrH == true){mijkyCUcrH = false;}
      if(USYEVMiCan == true){USYEVMiCan = false;}
      if(EhKyCWGaEo == true){EhKyCWGaEo = false;}
      if(zZQCHPoeGW == true){zZQCHPoeGW = false;}
      if(VrVHBYECuk == true){VrVHBYECuk = false;}
      if(BgqUREXlib == true){BgqUREXlib = false;}
      if(usXCItCVxG == true){usXCItCVxG = false;}
      if(XDwESMMCwc == true){XDwESMMCwc = false;}
      if(SDeTmSiwkC == true){SDeTmSiwkC = false;}
      if(qCwdabTSzG == true){qCwdabTSzG = false;}
      if(WhFoNyklBF == true){WhFoNyklBF = false;}
      if(rVoFJqOEPp == true){rVoFJqOEPp = false;}
      if(KFktOUHRcp == true){KFktOUHRcp = false;}
      if(rsDpGjypFn == true){rsDpGjypFn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYWTKKWZQZ
{ 
  void qqIcbQrwqJ()
  { 
      bool CdgoiWRRIt = false;
      bool mHsBuSnJTb = false;
      bool BhGrUFMhgM = false;
      bool HMQKpgeXbB = false;
      bool EyQEFfOZLV = false;
      bool iewJBTXnTc = false;
      bool KijulZpiKN = false;
      bool nQhSXDRBmo = false;
      bool qmWKdcQGIW = false;
      bool JpDyqVNURe = false;
      bool ofOyhRxdky = false;
      bool BWAelWLYRJ = false;
      bool JjZnExMiaB = false;
      bool owiIzLXXcL = false;
      bool flUKUmpYMU = false;
      bool JoDIVFGatj = false;
      bool FNDjJEmreZ = false;
      bool ynwFcWOOSQ = false;
      bool HnVGrAsZmt = false;
      bool FxdsGRikAP = false;
      string tQMIjScJzH;
      string ltXeZtQPwt;
      string OlSaxleDre;
      string MuSZBjRYBN;
      string rbAwmgsVlc;
      string BaKfOIxkLx;
      string mYRUtpbydo;
      string brOhCmkVnP;
      string rIQOdkkmLs;
      string lgNDaSJfCw;
      string FurwBIMbca;
      string WbxuFdHCqI;
      string FnljCudLHj;
      string cETqJwQUNU;
      string YIKjVKjSyw;
      string KGnsqRJIsG;
      string eBUsyRIFkI;
      string NmoWjwdCOr;
      string LLMKYVQZzr;
      string mHaGoWnQlD;
      if(tQMIjScJzH == FurwBIMbca){CdgoiWRRIt = true;}
      else if(FurwBIMbca == tQMIjScJzH){ofOyhRxdky = true;}
      if(ltXeZtQPwt == WbxuFdHCqI){mHsBuSnJTb = true;}
      else if(WbxuFdHCqI == ltXeZtQPwt){BWAelWLYRJ = true;}
      if(OlSaxleDre == FnljCudLHj){BhGrUFMhgM = true;}
      else if(FnljCudLHj == OlSaxleDre){JjZnExMiaB = true;}
      if(MuSZBjRYBN == cETqJwQUNU){HMQKpgeXbB = true;}
      else if(cETqJwQUNU == MuSZBjRYBN){owiIzLXXcL = true;}
      if(rbAwmgsVlc == YIKjVKjSyw){EyQEFfOZLV = true;}
      else if(YIKjVKjSyw == rbAwmgsVlc){flUKUmpYMU = true;}
      if(BaKfOIxkLx == KGnsqRJIsG){iewJBTXnTc = true;}
      else if(KGnsqRJIsG == BaKfOIxkLx){JoDIVFGatj = true;}
      if(mYRUtpbydo == eBUsyRIFkI){KijulZpiKN = true;}
      else if(eBUsyRIFkI == mYRUtpbydo){FNDjJEmreZ = true;}
      if(brOhCmkVnP == NmoWjwdCOr){nQhSXDRBmo = true;}
      if(rIQOdkkmLs == LLMKYVQZzr){qmWKdcQGIW = true;}
      if(lgNDaSJfCw == mHaGoWnQlD){JpDyqVNURe = true;}
      while(NmoWjwdCOr == brOhCmkVnP){ynwFcWOOSQ = true;}
      while(LLMKYVQZzr == LLMKYVQZzr){HnVGrAsZmt = true;}
      while(mHaGoWnQlD == mHaGoWnQlD){FxdsGRikAP = true;}
      if(CdgoiWRRIt == true){CdgoiWRRIt = false;}
      if(mHsBuSnJTb == true){mHsBuSnJTb = false;}
      if(BhGrUFMhgM == true){BhGrUFMhgM = false;}
      if(HMQKpgeXbB == true){HMQKpgeXbB = false;}
      if(EyQEFfOZLV == true){EyQEFfOZLV = false;}
      if(iewJBTXnTc == true){iewJBTXnTc = false;}
      if(KijulZpiKN == true){KijulZpiKN = false;}
      if(nQhSXDRBmo == true){nQhSXDRBmo = false;}
      if(qmWKdcQGIW == true){qmWKdcQGIW = false;}
      if(JpDyqVNURe == true){JpDyqVNURe = false;}
      if(ofOyhRxdky == true){ofOyhRxdky = false;}
      if(BWAelWLYRJ == true){BWAelWLYRJ = false;}
      if(JjZnExMiaB == true){JjZnExMiaB = false;}
      if(owiIzLXXcL == true){owiIzLXXcL = false;}
      if(flUKUmpYMU == true){flUKUmpYMU = false;}
      if(JoDIVFGatj == true){JoDIVFGatj = false;}
      if(FNDjJEmreZ == true){FNDjJEmreZ = false;}
      if(ynwFcWOOSQ == true){ynwFcWOOSQ = false;}
      if(HnVGrAsZmt == true){HnVGrAsZmt = false;}
      if(FxdsGRikAP == true){FxdsGRikAP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBKLBQZTQO
{ 
  void zkGnPWEOcV()
  { 
      bool hxYbqxqaEM = false;
      bool rcmQLHMQDa = false;
      bool CqtdWBFcKa = false;
      bool ABdUQAfRBK = false;
      bool IgCtqMumhz = false;
      bool NyJSiqCuFo = false;
      bool qNPdMqyRAL = false;
      bool atPrSUnAlK = false;
      bool GSuLNCrLkY = false;
      bool xjMMTtRYhA = false;
      bool NcmVXShQzO = false;
      bool DCJtiXSDQK = false;
      bool ymgaNqgDYY = false;
      bool DORlwcfYnt = false;
      bool TaLVVtaRcu = false;
      bool aNIXBZwLIf = false;
      bool ldraLnkWxG = false;
      bool rsPVpXaKFT = false;
      bool QOZdxoGtkV = false;
      bool fUQHIoikKg = false;
      string HCzHIKimYo;
      string cRtCfNSBfi;
      string WSpJRXamDO;
      string lldutFchaX;
      string gWnoHgqDWs;
      string pPkdnnMopj;
      string juiKCpmzHZ;
      string kjZHCAdACk;
      string gXQKYVBAHF;
      string smrqnlmdlR;
      string squwHFocbn;
      string KMmECMdYkg;
      string nlqCfyriTP;
      string NANjqpbTCT;
      string fYXTugAmna;
      string HNrFcHAsPJ;
      string MGJLaJyCNM;
      string jJWRAPOWGz;
      string xFtrIzHHHj;
      string ohDsGZPMsl;
      if(HCzHIKimYo == squwHFocbn){hxYbqxqaEM = true;}
      else if(squwHFocbn == HCzHIKimYo){NcmVXShQzO = true;}
      if(cRtCfNSBfi == KMmECMdYkg){rcmQLHMQDa = true;}
      else if(KMmECMdYkg == cRtCfNSBfi){DCJtiXSDQK = true;}
      if(WSpJRXamDO == nlqCfyriTP){CqtdWBFcKa = true;}
      else if(nlqCfyriTP == WSpJRXamDO){ymgaNqgDYY = true;}
      if(lldutFchaX == NANjqpbTCT){ABdUQAfRBK = true;}
      else if(NANjqpbTCT == lldutFchaX){DORlwcfYnt = true;}
      if(gWnoHgqDWs == fYXTugAmna){IgCtqMumhz = true;}
      else if(fYXTugAmna == gWnoHgqDWs){TaLVVtaRcu = true;}
      if(pPkdnnMopj == HNrFcHAsPJ){NyJSiqCuFo = true;}
      else if(HNrFcHAsPJ == pPkdnnMopj){aNIXBZwLIf = true;}
      if(juiKCpmzHZ == MGJLaJyCNM){qNPdMqyRAL = true;}
      else if(MGJLaJyCNM == juiKCpmzHZ){ldraLnkWxG = true;}
      if(kjZHCAdACk == jJWRAPOWGz){atPrSUnAlK = true;}
      if(gXQKYVBAHF == xFtrIzHHHj){GSuLNCrLkY = true;}
      if(smrqnlmdlR == ohDsGZPMsl){xjMMTtRYhA = true;}
      while(jJWRAPOWGz == kjZHCAdACk){rsPVpXaKFT = true;}
      while(xFtrIzHHHj == xFtrIzHHHj){QOZdxoGtkV = true;}
      while(ohDsGZPMsl == ohDsGZPMsl){fUQHIoikKg = true;}
      if(hxYbqxqaEM == true){hxYbqxqaEM = false;}
      if(rcmQLHMQDa == true){rcmQLHMQDa = false;}
      if(CqtdWBFcKa == true){CqtdWBFcKa = false;}
      if(ABdUQAfRBK == true){ABdUQAfRBK = false;}
      if(IgCtqMumhz == true){IgCtqMumhz = false;}
      if(NyJSiqCuFo == true){NyJSiqCuFo = false;}
      if(qNPdMqyRAL == true){qNPdMqyRAL = false;}
      if(atPrSUnAlK == true){atPrSUnAlK = false;}
      if(GSuLNCrLkY == true){GSuLNCrLkY = false;}
      if(xjMMTtRYhA == true){xjMMTtRYhA = false;}
      if(NcmVXShQzO == true){NcmVXShQzO = false;}
      if(DCJtiXSDQK == true){DCJtiXSDQK = false;}
      if(ymgaNqgDYY == true){ymgaNqgDYY = false;}
      if(DORlwcfYnt == true){DORlwcfYnt = false;}
      if(TaLVVtaRcu == true){TaLVVtaRcu = false;}
      if(aNIXBZwLIf == true){aNIXBZwLIf = false;}
      if(ldraLnkWxG == true){ldraLnkWxG = false;}
      if(rsPVpXaKFT == true){rsPVpXaKFT = false;}
      if(QOZdxoGtkV == true){QOZdxoGtkV = false;}
      if(fUQHIoikKg == true){fUQHIoikKg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLEOFJZSPV
{ 
  void sKYuibRpgQ()
  { 
      bool kWiDffRrgD = false;
      bool ObhyHluDUE = false;
      bool KyYsJakBfB = false;
      bool SulBiWEuUD = false;
      bool nXbocGitpQ = false;
      bool NkURsmxpsF = false;
      bool tPLfkTpfOj = false;
      bool hAiRQmWjQD = false;
      bool qpKPmhZUIw = false;
      bool YOBPIXLuEI = false;
      bool QCfFhNCDAF = false;
      bool QNYpNEFwrC = false;
      bool sVXSKTySIs = false;
      bool bafHmnKEgZ = false;
      bool fWTDeLoLBE = false;
      bool SODBOueMuN = false;
      bool OitHdpgRCY = false;
      bool sAPSWWBUmz = false;
      bool elQEZMWdrr = false;
      bool JyJSKxbMYo = false;
      string wjaXRELtOq;
      string JAdeYnuJlT;
      string guVqYPfgMq;
      string ipdcyNttHs;
      string dwMOdBYEpd;
      string hpVmQAOiyB;
      string XegWHTVAgL;
      string sBBspkhHNW;
      string pbpiJsUpMx;
      string zKuGUyOpGJ;
      string eXWejfobwf;
      string SHVbKwoyNO;
      string zenjMiGtYr;
      string VrADqRELzc;
      string DrtfdroTwX;
      string JQbrKAjmSB;
      string ZtDEJaGRjr;
      string rdzjKGkHFU;
      string smyAiFPIsq;
      string hQrxDJnpVD;
      if(wjaXRELtOq == eXWejfobwf){kWiDffRrgD = true;}
      else if(eXWejfobwf == wjaXRELtOq){QCfFhNCDAF = true;}
      if(JAdeYnuJlT == SHVbKwoyNO){ObhyHluDUE = true;}
      else if(SHVbKwoyNO == JAdeYnuJlT){QNYpNEFwrC = true;}
      if(guVqYPfgMq == zenjMiGtYr){KyYsJakBfB = true;}
      else if(zenjMiGtYr == guVqYPfgMq){sVXSKTySIs = true;}
      if(ipdcyNttHs == VrADqRELzc){SulBiWEuUD = true;}
      else if(VrADqRELzc == ipdcyNttHs){bafHmnKEgZ = true;}
      if(dwMOdBYEpd == DrtfdroTwX){nXbocGitpQ = true;}
      else if(DrtfdroTwX == dwMOdBYEpd){fWTDeLoLBE = true;}
      if(hpVmQAOiyB == JQbrKAjmSB){NkURsmxpsF = true;}
      else if(JQbrKAjmSB == hpVmQAOiyB){SODBOueMuN = true;}
      if(XegWHTVAgL == ZtDEJaGRjr){tPLfkTpfOj = true;}
      else if(ZtDEJaGRjr == XegWHTVAgL){OitHdpgRCY = true;}
      if(sBBspkhHNW == rdzjKGkHFU){hAiRQmWjQD = true;}
      if(pbpiJsUpMx == smyAiFPIsq){qpKPmhZUIw = true;}
      if(zKuGUyOpGJ == hQrxDJnpVD){YOBPIXLuEI = true;}
      while(rdzjKGkHFU == sBBspkhHNW){sAPSWWBUmz = true;}
      while(smyAiFPIsq == smyAiFPIsq){elQEZMWdrr = true;}
      while(hQrxDJnpVD == hQrxDJnpVD){JyJSKxbMYo = true;}
      if(kWiDffRrgD == true){kWiDffRrgD = false;}
      if(ObhyHluDUE == true){ObhyHluDUE = false;}
      if(KyYsJakBfB == true){KyYsJakBfB = false;}
      if(SulBiWEuUD == true){SulBiWEuUD = false;}
      if(nXbocGitpQ == true){nXbocGitpQ = false;}
      if(NkURsmxpsF == true){NkURsmxpsF = false;}
      if(tPLfkTpfOj == true){tPLfkTpfOj = false;}
      if(hAiRQmWjQD == true){hAiRQmWjQD = false;}
      if(qpKPmhZUIw == true){qpKPmhZUIw = false;}
      if(YOBPIXLuEI == true){YOBPIXLuEI = false;}
      if(QCfFhNCDAF == true){QCfFhNCDAF = false;}
      if(QNYpNEFwrC == true){QNYpNEFwrC = false;}
      if(sVXSKTySIs == true){sVXSKTySIs = false;}
      if(bafHmnKEgZ == true){bafHmnKEgZ = false;}
      if(fWTDeLoLBE == true){fWTDeLoLBE = false;}
      if(SODBOueMuN == true){SODBOueMuN = false;}
      if(OitHdpgRCY == true){OitHdpgRCY = false;}
      if(sAPSWWBUmz == true){sAPSWWBUmz = false;}
      if(elQEZMWdrr == true){elQEZMWdrr = false;}
      if(JyJSKxbMYo == true){JyJSKxbMYo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UOFDKOBMAI
{ 
  void dFeUwzWAKJ()
  { 
      bool mQHAWcniey = false;
      bool HOdimabPBx = false;
      bool PoljizDpNg = false;
      bool BghELookbh = false;
      bool SfXGSDsrdK = false;
      bool ynybDydXQX = false;
      bool YxVxwZgYXy = false;
      bool kqmTejQfRf = false;
      bool GKLDiMiFBM = false;
      bool LRUEIUJaJr = false;
      bool WTUfYHAdwS = false;
      bool hxGjROlSOj = false;
      bool paXKlTVhLK = false;
      bool ZpWYJloedb = false;
      bool LFIheNKjmt = false;
      bool iqLYCuuKtE = false;
      bool kSSlrrZhZe = false;
      bool YGnlXkRpeY = false;
      bool IkuRbidxVO = false;
      bool qekZqsmVom = false;
      string JLkkFOgQGM;
      string QPerRCVEQO;
      string JqBFOWUYkx;
      string XRfItYjNZh;
      string CsBZYRcWEW;
      string xgppXSKeVi;
      string sHeJoyiVys;
      string RHdhMQoagx;
      string tyTNzqapka;
      string OFqpotNrkZ;
      string hGYLEoCIdH;
      string ciyYoumRJx;
      string WskWdMPmsR;
      string CxpGOmYIJK;
      string oSLdyeHSBs;
      string HwhmCnVCgr;
      string YOOLEerqKB;
      string VeHzIEgHXy;
      string FxlzKGODEZ;
      string RWaRkaDzYT;
      if(JLkkFOgQGM == hGYLEoCIdH){mQHAWcniey = true;}
      else if(hGYLEoCIdH == JLkkFOgQGM){WTUfYHAdwS = true;}
      if(QPerRCVEQO == ciyYoumRJx){HOdimabPBx = true;}
      else if(ciyYoumRJx == QPerRCVEQO){hxGjROlSOj = true;}
      if(JqBFOWUYkx == WskWdMPmsR){PoljizDpNg = true;}
      else if(WskWdMPmsR == JqBFOWUYkx){paXKlTVhLK = true;}
      if(XRfItYjNZh == CxpGOmYIJK){BghELookbh = true;}
      else if(CxpGOmYIJK == XRfItYjNZh){ZpWYJloedb = true;}
      if(CsBZYRcWEW == oSLdyeHSBs){SfXGSDsrdK = true;}
      else if(oSLdyeHSBs == CsBZYRcWEW){LFIheNKjmt = true;}
      if(xgppXSKeVi == HwhmCnVCgr){ynybDydXQX = true;}
      else if(HwhmCnVCgr == xgppXSKeVi){iqLYCuuKtE = true;}
      if(sHeJoyiVys == YOOLEerqKB){YxVxwZgYXy = true;}
      else if(YOOLEerqKB == sHeJoyiVys){kSSlrrZhZe = true;}
      if(RHdhMQoagx == VeHzIEgHXy){kqmTejQfRf = true;}
      if(tyTNzqapka == FxlzKGODEZ){GKLDiMiFBM = true;}
      if(OFqpotNrkZ == RWaRkaDzYT){LRUEIUJaJr = true;}
      while(VeHzIEgHXy == RHdhMQoagx){YGnlXkRpeY = true;}
      while(FxlzKGODEZ == FxlzKGODEZ){IkuRbidxVO = true;}
      while(RWaRkaDzYT == RWaRkaDzYT){qekZqsmVom = true;}
      if(mQHAWcniey == true){mQHAWcniey = false;}
      if(HOdimabPBx == true){HOdimabPBx = false;}
      if(PoljizDpNg == true){PoljizDpNg = false;}
      if(BghELookbh == true){BghELookbh = false;}
      if(SfXGSDsrdK == true){SfXGSDsrdK = false;}
      if(ynybDydXQX == true){ynybDydXQX = false;}
      if(YxVxwZgYXy == true){YxVxwZgYXy = false;}
      if(kqmTejQfRf == true){kqmTejQfRf = false;}
      if(GKLDiMiFBM == true){GKLDiMiFBM = false;}
      if(LRUEIUJaJr == true){LRUEIUJaJr = false;}
      if(WTUfYHAdwS == true){WTUfYHAdwS = false;}
      if(hxGjROlSOj == true){hxGjROlSOj = false;}
      if(paXKlTVhLK == true){paXKlTVhLK = false;}
      if(ZpWYJloedb == true){ZpWYJloedb = false;}
      if(LFIheNKjmt == true){LFIheNKjmt = false;}
      if(iqLYCuuKtE == true){iqLYCuuKtE = false;}
      if(kSSlrrZhZe == true){kSSlrrZhZe = false;}
      if(YGnlXkRpeY == true){YGnlXkRpeY = false;}
      if(IkuRbidxVO == true){IkuRbidxVO = false;}
      if(qekZqsmVom == true){qekZqsmVom = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEWNSOSXEW
{ 
  void OVrjQePToB()
  { 
      bool qGFuhGDPKN = false;
      bool NFAkpMUxaA = false;
      bool PbmWIiAqcf = false;
      bool rcuuzGTHcF = false;
      bool GjcxoiCKBq = false;
      bool ZFyFwOSimz = false;
      bool FLldVkJEkj = false;
      bool sNUVsezpgY = false;
      bool fpplGldozk = false;
      bool nkTdzuyyaE = false;
      bool YyYRyMkcMQ = false;
      bool PcBNSPVAXi = false;
      bool GTFAwIspVy = false;
      bool gAObAhRYns = false;
      bool BBchUKiFLi = false;
      bool ZxZqyErXUo = false;
      bool StGNjPNYNj = false;
      bool ywMdhEpWek = false;
      bool YnelYiZWdu = false;
      bool osDyaGtPyF = false;
      string dGTANYncSS;
      string HhAtkVBlbg;
      string jxMNHwUTeK;
      string nxFEVpeUDY;
      string rRdJbIXQUM;
      string ZBspcfsFsR;
      string DTyIeKcwYt;
      string qghCnSSDlz;
      string XEyRjlDObo;
      string wYalUYTVdQ;
      string ebrZVsTqCJ;
      string NoTtszUfYs;
      string HOTiyRGwgP;
      string yxYUTwMXwq;
      string RMLRbHFfsV;
      string DnxkJQHIbD;
      string mXJmLPPyax;
      string mwjgauCCHq;
      string MZDLLKAnLD;
      string nDwrEtCYGL;
      if(dGTANYncSS == ebrZVsTqCJ){qGFuhGDPKN = true;}
      else if(ebrZVsTqCJ == dGTANYncSS){YyYRyMkcMQ = true;}
      if(HhAtkVBlbg == NoTtszUfYs){NFAkpMUxaA = true;}
      else if(NoTtszUfYs == HhAtkVBlbg){PcBNSPVAXi = true;}
      if(jxMNHwUTeK == HOTiyRGwgP){PbmWIiAqcf = true;}
      else if(HOTiyRGwgP == jxMNHwUTeK){GTFAwIspVy = true;}
      if(nxFEVpeUDY == yxYUTwMXwq){rcuuzGTHcF = true;}
      else if(yxYUTwMXwq == nxFEVpeUDY){gAObAhRYns = true;}
      if(rRdJbIXQUM == RMLRbHFfsV){GjcxoiCKBq = true;}
      else if(RMLRbHFfsV == rRdJbIXQUM){BBchUKiFLi = true;}
      if(ZBspcfsFsR == DnxkJQHIbD){ZFyFwOSimz = true;}
      else if(DnxkJQHIbD == ZBspcfsFsR){ZxZqyErXUo = true;}
      if(DTyIeKcwYt == mXJmLPPyax){FLldVkJEkj = true;}
      else if(mXJmLPPyax == DTyIeKcwYt){StGNjPNYNj = true;}
      if(qghCnSSDlz == mwjgauCCHq){sNUVsezpgY = true;}
      if(XEyRjlDObo == MZDLLKAnLD){fpplGldozk = true;}
      if(wYalUYTVdQ == nDwrEtCYGL){nkTdzuyyaE = true;}
      while(mwjgauCCHq == qghCnSSDlz){ywMdhEpWek = true;}
      while(MZDLLKAnLD == MZDLLKAnLD){YnelYiZWdu = true;}
      while(nDwrEtCYGL == nDwrEtCYGL){osDyaGtPyF = true;}
      if(qGFuhGDPKN == true){qGFuhGDPKN = false;}
      if(NFAkpMUxaA == true){NFAkpMUxaA = false;}
      if(PbmWIiAqcf == true){PbmWIiAqcf = false;}
      if(rcuuzGTHcF == true){rcuuzGTHcF = false;}
      if(GjcxoiCKBq == true){GjcxoiCKBq = false;}
      if(ZFyFwOSimz == true){ZFyFwOSimz = false;}
      if(FLldVkJEkj == true){FLldVkJEkj = false;}
      if(sNUVsezpgY == true){sNUVsezpgY = false;}
      if(fpplGldozk == true){fpplGldozk = false;}
      if(nkTdzuyyaE == true){nkTdzuyyaE = false;}
      if(YyYRyMkcMQ == true){YyYRyMkcMQ = false;}
      if(PcBNSPVAXi == true){PcBNSPVAXi = false;}
      if(GTFAwIspVy == true){GTFAwIspVy = false;}
      if(gAObAhRYns == true){gAObAhRYns = false;}
      if(BBchUKiFLi == true){BBchUKiFLi = false;}
      if(ZxZqyErXUo == true){ZxZqyErXUo = false;}
      if(StGNjPNYNj == true){StGNjPNYNj = false;}
      if(ywMdhEpWek == true){ywMdhEpWek = false;}
      if(YnelYiZWdu == true){YnelYiZWdu = false;}
      if(osDyaGtPyF == true){osDyaGtPyF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVWLBWHIRG
{ 
  void hxRGJHdkYi()
  { 
      bool LIJnectmab = false;
      bool MExlFdRUew = false;
      bool rSqnlBkxag = false;
      bool QTYZTUtVnl = false;
      bool sfYTmEbuxJ = false;
      bool EulnMsRVBc = false;
      bool rwMsLreWSk = false;
      bool iwgsDMtWBh = false;
      bool YpAQcUhkNZ = false;
      bool DYUKswSeIt = false;
      bool YEbLaIOskA = false;
      bool ytUSDCwwQp = false;
      bool KtJsgKbVzG = false;
      bool sPNGJUNopT = false;
      bool GozMaJEBGq = false;
      bool AVNSiduieP = false;
      bool gsseGifNIi = false;
      bool nHGwjVuxRX = false;
      bool GZOIFXBuXf = false;
      bool ZeJZmNuUFq = false;
      string dopjgCnLTN;
      string uNEgixzrCh;
      string onZxFqutYb;
      string nqyfntgNtr;
      string IVeJyLVSRa;
      string UTXfnpPrep;
      string HtlqYEPYso;
      string PkxKZTIQzs;
      string VbbyGUSRqx;
      string doiEkNjmjt;
      string uwYcKjVNGU;
      string gzrkUeRnkD;
      string kxguKaBsZL;
      string jVfExYDzmW;
      string zELWQewxiG;
      string wuCfIyPcRj;
      string hbntkLSnmu;
      string aSAOEgkKee;
      string dEJSPnTAwz;
      string IZgDnWQRkE;
      if(dopjgCnLTN == uwYcKjVNGU){LIJnectmab = true;}
      else if(uwYcKjVNGU == dopjgCnLTN){YEbLaIOskA = true;}
      if(uNEgixzrCh == gzrkUeRnkD){MExlFdRUew = true;}
      else if(gzrkUeRnkD == uNEgixzrCh){ytUSDCwwQp = true;}
      if(onZxFqutYb == kxguKaBsZL){rSqnlBkxag = true;}
      else if(kxguKaBsZL == onZxFqutYb){KtJsgKbVzG = true;}
      if(nqyfntgNtr == jVfExYDzmW){QTYZTUtVnl = true;}
      else if(jVfExYDzmW == nqyfntgNtr){sPNGJUNopT = true;}
      if(IVeJyLVSRa == zELWQewxiG){sfYTmEbuxJ = true;}
      else if(zELWQewxiG == IVeJyLVSRa){GozMaJEBGq = true;}
      if(UTXfnpPrep == wuCfIyPcRj){EulnMsRVBc = true;}
      else if(wuCfIyPcRj == UTXfnpPrep){AVNSiduieP = true;}
      if(HtlqYEPYso == hbntkLSnmu){rwMsLreWSk = true;}
      else if(hbntkLSnmu == HtlqYEPYso){gsseGifNIi = true;}
      if(PkxKZTIQzs == aSAOEgkKee){iwgsDMtWBh = true;}
      if(VbbyGUSRqx == dEJSPnTAwz){YpAQcUhkNZ = true;}
      if(doiEkNjmjt == IZgDnWQRkE){DYUKswSeIt = true;}
      while(aSAOEgkKee == PkxKZTIQzs){nHGwjVuxRX = true;}
      while(dEJSPnTAwz == dEJSPnTAwz){GZOIFXBuXf = true;}
      while(IZgDnWQRkE == IZgDnWQRkE){ZeJZmNuUFq = true;}
      if(LIJnectmab == true){LIJnectmab = false;}
      if(MExlFdRUew == true){MExlFdRUew = false;}
      if(rSqnlBkxag == true){rSqnlBkxag = false;}
      if(QTYZTUtVnl == true){QTYZTUtVnl = false;}
      if(sfYTmEbuxJ == true){sfYTmEbuxJ = false;}
      if(EulnMsRVBc == true){EulnMsRVBc = false;}
      if(rwMsLreWSk == true){rwMsLreWSk = false;}
      if(iwgsDMtWBh == true){iwgsDMtWBh = false;}
      if(YpAQcUhkNZ == true){YpAQcUhkNZ = false;}
      if(DYUKswSeIt == true){DYUKswSeIt = false;}
      if(YEbLaIOskA == true){YEbLaIOskA = false;}
      if(ytUSDCwwQp == true){ytUSDCwwQp = false;}
      if(KtJsgKbVzG == true){KtJsgKbVzG = false;}
      if(sPNGJUNopT == true){sPNGJUNopT = false;}
      if(GozMaJEBGq == true){GozMaJEBGq = false;}
      if(AVNSiduieP == true){AVNSiduieP = false;}
      if(gsseGifNIi == true){gsseGifNIi = false;}
      if(nHGwjVuxRX == true){nHGwjVuxRX = false;}
      if(GZOIFXBuXf == true){GZOIFXBuXf = false;}
      if(ZeJZmNuUFq == true){ZeJZmNuUFq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIYKZVPMNQ
{ 
  void LJnBuniMTQ()
  { 
      bool MCClqLqbMz = false;
      bool RqIPjfmsAe = false;
      bool HOQHeOwxCI = false;
      bool MxrxIgBgTI = false;
      bool TQqfWzSDWY = false;
      bool INduOxluHb = false;
      bool PtZEmUyLHC = false;
      bool dFZqKqXjje = false;
      bool usZczySxhK = false;
      bool uGZqsZpmsC = false;
      bool BHuUuDnmjX = false;
      bool ZBKcfVUwFn = false;
      bool BBdwGXfhyk = false;
      bool AjpgcnxFhu = false;
      bool KfMJktuwLW = false;
      bool FthFBAczNX = false;
      bool XFnzWoKdzq = false;
      bool XONJdUnTKM = false;
      bool biWafGCkfc = false;
      bool LyqKXErNmu = false;
      string EyaFKOMZZY;
      string OTAjcSAGYz;
      string XPOhTqqBNA;
      string eaaApFnQyC;
      string GmGTkOuPKi;
      string WqTJinjrkS;
      string XKLYtmrAtW;
      string eiHWrjJtxF;
      string waqecmHQQC;
      string VuffdubgYy;
      string VtVmDniwRz;
      string doufWwTfwH;
      string ebjrBjDbrw;
      string IcVyiBFEao;
      string DLzRXfzzIh;
      string bwjQStKckT;
      string jGDUqATwwV;
      string qPEHETbSTU;
      string jETKULsEfo;
      string qbSHEwHeZW;
      if(EyaFKOMZZY == VtVmDniwRz){MCClqLqbMz = true;}
      else if(VtVmDniwRz == EyaFKOMZZY){BHuUuDnmjX = true;}
      if(OTAjcSAGYz == doufWwTfwH){RqIPjfmsAe = true;}
      else if(doufWwTfwH == OTAjcSAGYz){ZBKcfVUwFn = true;}
      if(XPOhTqqBNA == ebjrBjDbrw){HOQHeOwxCI = true;}
      else if(ebjrBjDbrw == XPOhTqqBNA){BBdwGXfhyk = true;}
      if(eaaApFnQyC == IcVyiBFEao){MxrxIgBgTI = true;}
      else if(IcVyiBFEao == eaaApFnQyC){AjpgcnxFhu = true;}
      if(GmGTkOuPKi == DLzRXfzzIh){TQqfWzSDWY = true;}
      else if(DLzRXfzzIh == GmGTkOuPKi){KfMJktuwLW = true;}
      if(WqTJinjrkS == bwjQStKckT){INduOxluHb = true;}
      else if(bwjQStKckT == WqTJinjrkS){FthFBAczNX = true;}
      if(XKLYtmrAtW == jGDUqATwwV){PtZEmUyLHC = true;}
      else if(jGDUqATwwV == XKLYtmrAtW){XFnzWoKdzq = true;}
      if(eiHWrjJtxF == qPEHETbSTU){dFZqKqXjje = true;}
      if(waqecmHQQC == jETKULsEfo){usZczySxhK = true;}
      if(VuffdubgYy == qbSHEwHeZW){uGZqsZpmsC = true;}
      while(qPEHETbSTU == eiHWrjJtxF){XONJdUnTKM = true;}
      while(jETKULsEfo == jETKULsEfo){biWafGCkfc = true;}
      while(qbSHEwHeZW == qbSHEwHeZW){LyqKXErNmu = true;}
      if(MCClqLqbMz == true){MCClqLqbMz = false;}
      if(RqIPjfmsAe == true){RqIPjfmsAe = false;}
      if(HOQHeOwxCI == true){HOQHeOwxCI = false;}
      if(MxrxIgBgTI == true){MxrxIgBgTI = false;}
      if(TQqfWzSDWY == true){TQqfWzSDWY = false;}
      if(INduOxluHb == true){INduOxluHb = false;}
      if(PtZEmUyLHC == true){PtZEmUyLHC = false;}
      if(dFZqKqXjje == true){dFZqKqXjje = false;}
      if(usZczySxhK == true){usZczySxhK = false;}
      if(uGZqsZpmsC == true){uGZqsZpmsC = false;}
      if(BHuUuDnmjX == true){BHuUuDnmjX = false;}
      if(ZBKcfVUwFn == true){ZBKcfVUwFn = false;}
      if(BBdwGXfhyk == true){BBdwGXfhyk = false;}
      if(AjpgcnxFhu == true){AjpgcnxFhu = false;}
      if(KfMJktuwLW == true){KfMJktuwLW = false;}
      if(FthFBAczNX == true){FthFBAczNX = false;}
      if(XFnzWoKdzq == true){XFnzWoKdzq = false;}
      if(XONJdUnTKM == true){XONJdUnTKM = false;}
      if(biWafGCkfc == true){biWafGCkfc = false;}
      if(LyqKXErNmu == true){LyqKXErNmu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHXVOFYSKZ
{ 
  void bVchDGPbqN()
  { 
      bool sThIrxZQXu = false;
      bool cLAXDrfiNb = false;
      bool SBsbTgdyyQ = false;
      bool CaruYAcgar = false;
      bool DEgaUXmyce = false;
      bool SLDknqaFoL = false;
      bool TbRHrBSEyD = false;
      bool PyHUXNURHu = false;
      bool seUTyqXGHg = false;
      bool YWrPYbmZiS = false;
      bool FhAYOTDhNZ = false;
      bool WJxsRnGxIA = false;
      bool dLxQdrGruw = false;
      bool auinpKeuFd = false;
      bool noshKPYzxk = false;
      bool VoQhoskiuV = false;
      bool NKlRzaZJDG = false;
      bool IKreMoRPGN = false;
      bool SHuKZleBzw = false;
      bool ZwAiPcCbhi = false;
      string IwtFSilphS;
      string EmzSmFQgmD;
      string ZUbQLTezZn;
      string laLRdUpwOd;
      string AEcHPKancr;
      string qqsxJmTdty;
      string ElQsgcbhnS;
      string PUSIDVqTAB;
      string sqWgxthOHq;
      string ALBQZNmiam;
      string hrAJbWYksn;
      string wAcsEMOiwl;
      string tMZxSDSCho;
      string hIsNSBqNEa;
      string VxUTtAiILN;
      string zElnrURDpY;
      string DWCEFnGOZD;
      string UBdVPxrGCS;
      string UKpTpdVEVx;
      string inWfWztQNG;
      if(IwtFSilphS == hrAJbWYksn){sThIrxZQXu = true;}
      else if(hrAJbWYksn == IwtFSilphS){FhAYOTDhNZ = true;}
      if(EmzSmFQgmD == wAcsEMOiwl){cLAXDrfiNb = true;}
      else if(wAcsEMOiwl == EmzSmFQgmD){WJxsRnGxIA = true;}
      if(ZUbQLTezZn == tMZxSDSCho){SBsbTgdyyQ = true;}
      else if(tMZxSDSCho == ZUbQLTezZn){dLxQdrGruw = true;}
      if(laLRdUpwOd == hIsNSBqNEa){CaruYAcgar = true;}
      else if(hIsNSBqNEa == laLRdUpwOd){auinpKeuFd = true;}
      if(AEcHPKancr == VxUTtAiILN){DEgaUXmyce = true;}
      else if(VxUTtAiILN == AEcHPKancr){noshKPYzxk = true;}
      if(qqsxJmTdty == zElnrURDpY){SLDknqaFoL = true;}
      else if(zElnrURDpY == qqsxJmTdty){VoQhoskiuV = true;}
      if(ElQsgcbhnS == DWCEFnGOZD){TbRHrBSEyD = true;}
      else if(DWCEFnGOZD == ElQsgcbhnS){NKlRzaZJDG = true;}
      if(PUSIDVqTAB == UBdVPxrGCS){PyHUXNURHu = true;}
      if(sqWgxthOHq == UKpTpdVEVx){seUTyqXGHg = true;}
      if(ALBQZNmiam == inWfWztQNG){YWrPYbmZiS = true;}
      while(UBdVPxrGCS == PUSIDVqTAB){IKreMoRPGN = true;}
      while(UKpTpdVEVx == UKpTpdVEVx){SHuKZleBzw = true;}
      while(inWfWztQNG == inWfWztQNG){ZwAiPcCbhi = true;}
      if(sThIrxZQXu == true){sThIrxZQXu = false;}
      if(cLAXDrfiNb == true){cLAXDrfiNb = false;}
      if(SBsbTgdyyQ == true){SBsbTgdyyQ = false;}
      if(CaruYAcgar == true){CaruYAcgar = false;}
      if(DEgaUXmyce == true){DEgaUXmyce = false;}
      if(SLDknqaFoL == true){SLDknqaFoL = false;}
      if(TbRHrBSEyD == true){TbRHrBSEyD = false;}
      if(PyHUXNURHu == true){PyHUXNURHu = false;}
      if(seUTyqXGHg == true){seUTyqXGHg = false;}
      if(YWrPYbmZiS == true){YWrPYbmZiS = false;}
      if(FhAYOTDhNZ == true){FhAYOTDhNZ = false;}
      if(WJxsRnGxIA == true){WJxsRnGxIA = false;}
      if(dLxQdrGruw == true){dLxQdrGruw = false;}
      if(auinpKeuFd == true){auinpKeuFd = false;}
      if(noshKPYzxk == true){noshKPYzxk = false;}
      if(VoQhoskiuV == true){VoQhoskiuV = false;}
      if(NKlRzaZJDG == true){NKlRzaZJDG = false;}
      if(IKreMoRPGN == true){IKreMoRPGN = false;}
      if(SHuKZleBzw == true){SHuKZleBzw = false;}
      if(ZwAiPcCbhi == true){ZwAiPcCbhi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOXJOEIXAC
{ 
  void jIQMzhaNxO()
  { 
      bool fllZSEsyFI = false;
      bool kSnGNJXgNG = false;
      bool wtFEijLxKO = false;
      bool Qbsaujhsqz = false;
      bool YiiGHZxwZP = false;
      bool wRRhKkghph = false;
      bool sunqqJYNLd = false;
      bool aeoOhNKywI = false;
      bool lOXuRzJLPJ = false;
      bool CACIGcurOx = false;
      bool BjkunRbCAw = false;
      bool ZhkhwdXrYr = false;
      bool ANxBbabgIE = false;
      bool SSizHCdbHA = false;
      bool WGKSjTOUMb = false;
      bool FCSWxmliTM = false;
      bool outwdHylZs = false;
      bool zujYUsDdRH = false;
      bool MHTfzPzMBT = false;
      bool PuHuKbMOoc = false;
      string HuNqmsKhOB;
      string XKPAahIpzT;
      string PdRlXVYBop;
      string hkSlGHpksj;
      string cfsDSobfrE;
      string EJEfDdcaSR;
      string UJsXSmqdtT;
      string qWxOqikOSi;
      string srIjkXfmhc;
      string dOSaPTmUje;
      string xylXMhMpoU;
      string sOHiXbAImt;
      string GEwQpcDVyX;
      string wPenluGkXD;
      string LpxNjPGiCn;
      string TdhoYrBUhj;
      string dqqRXcjTxc;
      string VOkjiPHiga;
      string VUSKDRgoOs;
      string skDmYUzeoG;
      if(HuNqmsKhOB == xylXMhMpoU){fllZSEsyFI = true;}
      else if(xylXMhMpoU == HuNqmsKhOB){BjkunRbCAw = true;}
      if(XKPAahIpzT == sOHiXbAImt){kSnGNJXgNG = true;}
      else if(sOHiXbAImt == XKPAahIpzT){ZhkhwdXrYr = true;}
      if(PdRlXVYBop == GEwQpcDVyX){wtFEijLxKO = true;}
      else if(GEwQpcDVyX == PdRlXVYBop){ANxBbabgIE = true;}
      if(hkSlGHpksj == wPenluGkXD){Qbsaujhsqz = true;}
      else if(wPenluGkXD == hkSlGHpksj){SSizHCdbHA = true;}
      if(cfsDSobfrE == LpxNjPGiCn){YiiGHZxwZP = true;}
      else if(LpxNjPGiCn == cfsDSobfrE){WGKSjTOUMb = true;}
      if(EJEfDdcaSR == TdhoYrBUhj){wRRhKkghph = true;}
      else if(TdhoYrBUhj == EJEfDdcaSR){FCSWxmliTM = true;}
      if(UJsXSmqdtT == dqqRXcjTxc){sunqqJYNLd = true;}
      else if(dqqRXcjTxc == UJsXSmqdtT){outwdHylZs = true;}
      if(qWxOqikOSi == VOkjiPHiga){aeoOhNKywI = true;}
      if(srIjkXfmhc == VUSKDRgoOs){lOXuRzJLPJ = true;}
      if(dOSaPTmUje == skDmYUzeoG){CACIGcurOx = true;}
      while(VOkjiPHiga == qWxOqikOSi){zujYUsDdRH = true;}
      while(VUSKDRgoOs == VUSKDRgoOs){MHTfzPzMBT = true;}
      while(skDmYUzeoG == skDmYUzeoG){PuHuKbMOoc = true;}
      if(fllZSEsyFI == true){fllZSEsyFI = false;}
      if(kSnGNJXgNG == true){kSnGNJXgNG = false;}
      if(wtFEijLxKO == true){wtFEijLxKO = false;}
      if(Qbsaujhsqz == true){Qbsaujhsqz = false;}
      if(YiiGHZxwZP == true){YiiGHZxwZP = false;}
      if(wRRhKkghph == true){wRRhKkghph = false;}
      if(sunqqJYNLd == true){sunqqJYNLd = false;}
      if(aeoOhNKywI == true){aeoOhNKywI = false;}
      if(lOXuRzJLPJ == true){lOXuRzJLPJ = false;}
      if(CACIGcurOx == true){CACIGcurOx = false;}
      if(BjkunRbCAw == true){BjkunRbCAw = false;}
      if(ZhkhwdXrYr == true){ZhkhwdXrYr = false;}
      if(ANxBbabgIE == true){ANxBbabgIE = false;}
      if(SSizHCdbHA == true){SSizHCdbHA = false;}
      if(WGKSjTOUMb == true){WGKSjTOUMb = false;}
      if(FCSWxmliTM == true){FCSWxmliTM = false;}
      if(outwdHylZs == true){outwdHylZs = false;}
      if(zujYUsDdRH == true){zujYUsDdRH = false;}
      if(MHTfzPzMBT == true){MHTfzPzMBT = false;}
      if(PuHuKbMOoc == true){PuHuKbMOoc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHASZRAFYN
{ 
  void PPlLitrFtR()
  { 
      bool YIwYbsbGRh = false;
      bool PBQAUfHhjo = false;
      bool IpRKjwfqHI = false;
      bool bUPwRKnRBA = false;
      bool JryVKjiWan = false;
      bool TrzjRhpkne = false;
      bool NkzJFtkThJ = false;
      bool rpgieQqwzz = false;
      bool NIQSoiVfej = false;
      bool UCcVmYsoPQ = false;
      bool zPoQwdKPEA = false;
      bool qtknREUgUV = false;
      bool XFoyooMLwG = false;
      bool XCfiAyTAVK = false;
      bool YGadsZQoDi = false;
      bool DMUtstaqaG = false;
      bool RzSxcnOCmT = false;
      bool jUKJxRdKEO = false;
      bool XWHNCLhkpG = false;
      bool WcYOsYmdAE = false;
      string cSJkOaMnKr;
      string WTLWoDydqS;
      string QILiYIHRuc;
      string XePrrMPWzd;
      string KddfTqzYpY;
      string JObeOTGaLG;
      string TtrgTrETdb;
      string mbeMHldfPg;
      string IhbVTJCkcX;
      string FoKsKPkwMa;
      string mftNlhjOWb;
      string oZKdykSWNJ;
      string pSpGVxQkCr;
      string AgTntbnOjl;
      string ZmNAiedfuY;
      string xOiCkTpnqn;
      string QyMebHGVjV;
      string wDlbjCEoXq;
      string SjpdtlyQDZ;
      string kAWuUaaiYa;
      if(cSJkOaMnKr == mftNlhjOWb){YIwYbsbGRh = true;}
      else if(mftNlhjOWb == cSJkOaMnKr){zPoQwdKPEA = true;}
      if(WTLWoDydqS == oZKdykSWNJ){PBQAUfHhjo = true;}
      else if(oZKdykSWNJ == WTLWoDydqS){qtknREUgUV = true;}
      if(QILiYIHRuc == pSpGVxQkCr){IpRKjwfqHI = true;}
      else if(pSpGVxQkCr == QILiYIHRuc){XFoyooMLwG = true;}
      if(XePrrMPWzd == AgTntbnOjl){bUPwRKnRBA = true;}
      else if(AgTntbnOjl == XePrrMPWzd){XCfiAyTAVK = true;}
      if(KddfTqzYpY == ZmNAiedfuY){JryVKjiWan = true;}
      else if(ZmNAiedfuY == KddfTqzYpY){YGadsZQoDi = true;}
      if(JObeOTGaLG == xOiCkTpnqn){TrzjRhpkne = true;}
      else if(xOiCkTpnqn == JObeOTGaLG){DMUtstaqaG = true;}
      if(TtrgTrETdb == QyMebHGVjV){NkzJFtkThJ = true;}
      else if(QyMebHGVjV == TtrgTrETdb){RzSxcnOCmT = true;}
      if(mbeMHldfPg == wDlbjCEoXq){rpgieQqwzz = true;}
      if(IhbVTJCkcX == SjpdtlyQDZ){NIQSoiVfej = true;}
      if(FoKsKPkwMa == kAWuUaaiYa){UCcVmYsoPQ = true;}
      while(wDlbjCEoXq == mbeMHldfPg){jUKJxRdKEO = true;}
      while(SjpdtlyQDZ == SjpdtlyQDZ){XWHNCLhkpG = true;}
      while(kAWuUaaiYa == kAWuUaaiYa){WcYOsYmdAE = true;}
      if(YIwYbsbGRh == true){YIwYbsbGRh = false;}
      if(PBQAUfHhjo == true){PBQAUfHhjo = false;}
      if(IpRKjwfqHI == true){IpRKjwfqHI = false;}
      if(bUPwRKnRBA == true){bUPwRKnRBA = false;}
      if(JryVKjiWan == true){JryVKjiWan = false;}
      if(TrzjRhpkne == true){TrzjRhpkne = false;}
      if(NkzJFtkThJ == true){NkzJFtkThJ = false;}
      if(rpgieQqwzz == true){rpgieQqwzz = false;}
      if(NIQSoiVfej == true){NIQSoiVfej = false;}
      if(UCcVmYsoPQ == true){UCcVmYsoPQ = false;}
      if(zPoQwdKPEA == true){zPoQwdKPEA = false;}
      if(qtknREUgUV == true){qtknREUgUV = false;}
      if(XFoyooMLwG == true){XFoyooMLwG = false;}
      if(XCfiAyTAVK == true){XCfiAyTAVK = false;}
      if(YGadsZQoDi == true){YGadsZQoDi = false;}
      if(DMUtstaqaG == true){DMUtstaqaG = false;}
      if(RzSxcnOCmT == true){RzSxcnOCmT = false;}
      if(jUKJxRdKEO == true){jUKJxRdKEO = false;}
      if(XWHNCLhkpG == true){XWHNCLhkpG = false;}
      if(WcYOsYmdAE == true){WcYOsYmdAE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QICPXMAPTD
{ 
  void GNKnsazqXa()
  { 
      bool bTdirGHbtY = false;
      bool RpHcxWqVKH = false;
      bool IZwYVAOhPY = false;
      bool TUxgOrblUJ = false;
      bool YTxiQAwkIF = false;
      bool JJIXYBXEMr = false;
      bool rYMUFwsZOF = false;
      bool tFAAincNHV = false;
      bool DdZJPJMZIN = false;
      bool TXZbQzHbcT = false;
      bool HVWCLDIHoj = false;
      bool XKxqoOzCEu = false;
      bool iSQAkVeXii = false;
      bool gBjmNgGWyL = false;
      bool AFkYoIZimC = false;
      bool AEWhjoFVQo = false;
      bool XjXGDWaJcH = false;
      bool HbErtdhrKc = false;
      bool wwkfhbdBCX = false;
      bool bkFJnQheVS = false;
      string VPTmdJAAqu;
      string KtGVirgNns;
      string hSOWPagApV;
      string NnsYLZCGYD;
      string wIlqGnyiNh;
      string uTeYoCBxXC;
      string bzKVhVBgKJ;
      string oankxZgWPa;
      string cymHZsIUjI;
      string YFhWawxPJk;
      string lQXEsUetaP;
      string VehwZdLCwn;
      string NgxBjirRKA;
      string bQMeoLZhOE;
      string NOsTmsXkww;
      string juTUWFTVTJ;
      string cMianFRDHN;
      string DcnqZyncOp;
      string LGUNQfwqHi;
      string qDOFbBeSeg;
      if(VPTmdJAAqu == lQXEsUetaP){bTdirGHbtY = true;}
      else if(lQXEsUetaP == VPTmdJAAqu){HVWCLDIHoj = true;}
      if(KtGVirgNns == VehwZdLCwn){RpHcxWqVKH = true;}
      else if(VehwZdLCwn == KtGVirgNns){XKxqoOzCEu = true;}
      if(hSOWPagApV == NgxBjirRKA){IZwYVAOhPY = true;}
      else if(NgxBjirRKA == hSOWPagApV){iSQAkVeXii = true;}
      if(NnsYLZCGYD == bQMeoLZhOE){TUxgOrblUJ = true;}
      else if(bQMeoLZhOE == NnsYLZCGYD){gBjmNgGWyL = true;}
      if(wIlqGnyiNh == NOsTmsXkww){YTxiQAwkIF = true;}
      else if(NOsTmsXkww == wIlqGnyiNh){AFkYoIZimC = true;}
      if(uTeYoCBxXC == juTUWFTVTJ){JJIXYBXEMr = true;}
      else if(juTUWFTVTJ == uTeYoCBxXC){AEWhjoFVQo = true;}
      if(bzKVhVBgKJ == cMianFRDHN){rYMUFwsZOF = true;}
      else if(cMianFRDHN == bzKVhVBgKJ){XjXGDWaJcH = true;}
      if(oankxZgWPa == DcnqZyncOp){tFAAincNHV = true;}
      if(cymHZsIUjI == LGUNQfwqHi){DdZJPJMZIN = true;}
      if(YFhWawxPJk == qDOFbBeSeg){TXZbQzHbcT = true;}
      while(DcnqZyncOp == oankxZgWPa){HbErtdhrKc = true;}
      while(LGUNQfwqHi == LGUNQfwqHi){wwkfhbdBCX = true;}
      while(qDOFbBeSeg == qDOFbBeSeg){bkFJnQheVS = true;}
      if(bTdirGHbtY == true){bTdirGHbtY = false;}
      if(RpHcxWqVKH == true){RpHcxWqVKH = false;}
      if(IZwYVAOhPY == true){IZwYVAOhPY = false;}
      if(TUxgOrblUJ == true){TUxgOrblUJ = false;}
      if(YTxiQAwkIF == true){YTxiQAwkIF = false;}
      if(JJIXYBXEMr == true){JJIXYBXEMr = false;}
      if(rYMUFwsZOF == true){rYMUFwsZOF = false;}
      if(tFAAincNHV == true){tFAAincNHV = false;}
      if(DdZJPJMZIN == true){DdZJPJMZIN = false;}
      if(TXZbQzHbcT == true){TXZbQzHbcT = false;}
      if(HVWCLDIHoj == true){HVWCLDIHoj = false;}
      if(XKxqoOzCEu == true){XKxqoOzCEu = false;}
      if(iSQAkVeXii == true){iSQAkVeXii = false;}
      if(gBjmNgGWyL == true){gBjmNgGWyL = false;}
      if(AFkYoIZimC == true){AFkYoIZimC = false;}
      if(AEWhjoFVQo == true){AEWhjoFVQo = false;}
      if(XjXGDWaJcH == true){XjXGDWaJcH = false;}
      if(HbErtdhrKc == true){HbErtdhrKc = false;}
      if(wwkfhbdBCX == true){wwkfhbdBCX = false;}
      if(bkFJnQheVS == true){bkFJnQheVS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTTSWQBBLU
{ 
  void AbqXEUePHl()
  { 
      bool eKQuorUUzX = false;
      bool YtozpkXncL = false;
      bool WdxadKKDuF = false;
      bool NzurpNCHJs = false;
      bool admcznpKwf = false;
      bool VlSpLBMpQd = false;
      bool gQZsJYywIc = false;
      bool hQejjspUbp = false;
      bool UzHPibgEgn = false;
      bool AMpeLKEsSZ = false;
      bool otCSxFHiGS = false;
      bool LqNaJgIJKh = false;
      bool rsPTbVZzXZ = false;
      bool nwCBAZxoRd = false;
      bool TyyNcJyOVd = false;
      bool Buikhwdhqb = false;
      bool eIKfeOoMai = false;
      bool jTrfNsuBpS = false;
      bool WKdtYrNRTE = false;
      bool wPypyLnRiO = false;
      string DAYbYWfnic;
      string qSfCNLMVFn;
      string HCwhQImPwq;
      string CDrzKAKTME;
      string cuGsEzfqzy;
      string huUWaADpKP;
      string jPqqamZfrN;
      string BsIAKLwDdR;
      string bwQyJHiVYJ;
      string wTJxUMEORQ;
      string YAzlwnlTLO;
      string DALrnnzrhT;
      string EEHhQgjLfy;
      string HgkNsaxeCU;
      string UOJJGuIQIf;
      string MLgyMUrQUO;
      string EanNHWPyzM;
      string qUpMzouybV;
      string XTCzkwzlAY;
      string ifJmQsauCi;
      if(DAYbYWfnic == YAzlwnlTLO){eKQuorUUzX = true;}
      else if(YAzlwnlTLO == DAYbYWfnic){otCSxFHiGS = true;}
      if(qSfCNLMVFn == DALrnnzrhT){YtozpkXncL = true;}
      else if(DALrnnzrhT == qSfCNLMVFn){LqNaJgIJKh = true;}
      if(HCwhQImPwq == EEHhQgjLfy){WdxadKKDuF = true;}
      else if(EEHhQgjLfy == HCwhQImPwq){rsPTbVZzXZ = true;}
      if(CDrzKAKTME == HgkNsaxeCU){NzurpNCHJs = true;}
      else if(HgkNsaxeCU == CDrzKAKTME){nwCBAZxoRd = true;}
      if(cuGsEzfqzy == UOJJGuIQIf){admcznpKwf = true;}
      else if(UOJJGuIQIf == cuGsEzfqzy){TyyNcJyOVd = true;}
      if(huUWaADpKP == MLgyMUrQUO){VlSpLBMpQd = true;}
      else if(MLgyMUrQUO == huUWaADpKP){Buikhwdhqb = true;}
      if(jPqqamZfrN == EanNHWPyzM){gQZsJYywIc = true;}
      else if(EanNHWPyzM == jPqqamZfrN){eIKfeOoMai = true;}
      if(BsIAKLwDdR == qUpMzouybV){hQejjspUbp = true;}
      if(bwQyJHiVYJ == XTCzkwzlAY){UzHPibgEgn = true;}
      if(wTJxUMEORQ == ifJmQsauCi){AMpeLKEsSZ = true;}
      while(qUpMzouybV == BsIAKLwDdR){jTrfNsuBpS = true;}
      while(XTCzkwzlAY == XTCzkwzlAY){WKdtYrNRTE = true;}
      while(ifJmQsauCi == ifJmQsauCi){wPypyLnRiO = true;}
      if(eKQuorUUzX == true){eKQuorUUzX = false;}
      if(YtozpkXncL == true){YtozpkXncL = false;}
      if(WdxadKKDuF == true){WdxadKKDuF = false;}
      if(NzurpNCHJs == true){NzurpNCHJs = false;}
      if(admcznpKwf == true){admcznpKwf = false;}
      if(VlSpLBMpQd == true){VlSpLBMpQd = false;}
      if(gQZsJYywIc == true){gQZsJYywIc = false;}
      if(hQejjspUbp == true){hQejjspUbp = false;}
      if(UzHPibgEgn == true){UzHPibgEgn = false;}
      if(AMpeLKEsSZ == true){AMpeLKEsSZ = false;}
      if(otCSxFHiGS == true){otCSxFHiGS = false;}
      if(LqNaJgIJKh == true){LqNaJgIJKh = false;}
      if(rsPTbVZzXZ == true){rsPTbVZzXZ = false;}
      if(nwCBAZxoRd == true){nwCBAZxoRd = false;}
      if(TyyNcJyOVd == true){TyyNcJyOVd = false;}
      if(Buikhwdhqb == true){Buikhwdhqb = false;}
      if(eIKfeOoMai == true){eIKfeOoMai = false;}
      if(jTrfNsuBpS == true){jTrfNsuBpS = false;}
      if(WKdtYrNRTE == true){WKdtYrNRTE = false;}
      if(wPypyLnRiO == true){wPypyLnRiO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZUUWGFJQN
{ 
  void qLGhOrllBM()
  { 
      bool hqPPqaDfCG = false;
      bool sBqNrryeII = false;
      bool kFipKVHJXH = false;
      bool sAacmLDeaJ = false;
      bool ADLNyHAoEg = false;
      bool YgKtqcIZFU = false;
      bool TsIuNrZNag = false;
      bool oSEyIhsVrC = false;
      bool USFqhMoglJ = false;
      bool DcZFpGtQzF = false;
      bool hmNXqGbMlJ = false;
      bool ilhCzAnRMB = false;
      bool DsbQcLryHB = false;
      bool mcVlUhEgzb = false;
      bool jcubZQuXGo = false;
      bool ScDyCoLxte = false;
      bool NdEjWGPuhQ = false;
      bool wGRkQaxzqM = false;
      bool QUrRhJYWje = false;
      bool WHmTOFXKFT = false;
      string tYHCsOestW;
      string QXWUqrclgi;
      string VllTNVVnGu;
      string laHnmDQZOB;
      string axLOOLIgtU;
      string fwzayImnoW;
      string rqlykoPign;
      string aCXeIYaXEB;
      string NoslPobgoe;
      string QckrIjKMcY;
      string wYzGsdYTSZ;
      string hOimIDxAiu;
      string NisCWxReWX;
      string NNufFnolsl;
      string QIOPwBtyjF;
      string lKdgLNexiu;
      string LswtLUTDhT;
      string OKHxeEUdFU;
      string DTuRkDiNTq;
      string IrDxZWLTDb;
      if(tYHCsOestW == wYzGsdYTSZ){hqPPqaDfCG = true;}
      else if(wYzGsdYTSZ == tYHCsOestW){hmNXqGbMlJ = true;}
      if(QXWUqrclgi == hOimIDxAiu){sBqNrryeII = true;}
      else if(hOimIDxAiu == QXWUqrclgi){ilhCzAnRMB = true;}
      if(VllTNVVnGu == NisCWxReWX){kFipKVHJXH = true;}
      else if(NisCWxReWX == VllTNVVnGu){DsbQcLryHB = true;}
      if(laHnmDQZOB == NNufFnolsl){sAacmLDeaJ = true;}
      else if(NNufFnolsl == laHnmDQZOB){mcVlUhEgzb = true;}
      if(axLOOLIgtU == QIOPwBtyjF){ADLNyHAoEg = true;}
      else if(QIOPwBtyjF == axLOOLIgtU){jcubZQuXGo = true;}
      if(fwzayImnoW == lKdgLNexiu){YgKtqcIZFU = true;}
      else if(lKdgLNexiu == fwzayImnoW){ScDyCoLxte = true;}
      if(rqlykoPign == LswtLUTDhT){TsIuNrZNag = true;}
      else if(LswtLUTDhT == rqlykoPign){NdEjWGPuhQ = true;}
      if(aCXeIYaXEB == OKHxeEUdFU){oSEyIhsVrC = true;}
      if(NoslPobgoe == DTuRkDiNTq){USFqhMoglJ = true;}
      if(QckrIjKMcY == IrDxZWLTDb){DcZFpGtQzF = true;}
      while(OKHxeEUdFU == aCXeIYaXEB){wGRkQaxzqM = true;}
      while(DTuRkDiNTq == DTuRkDiNTq){QUrRhJYWje = true;}
      while(IrDxZWLTDb == IrDxZWLTDb){WHmTOFXKFT = true;}
      if(hqPPqaDfCG == true){hqPPqaDfCG = false;}
      if(sBqNrryeII == true){sBqNrryeII = false;}
      if(kFipKVHJXH == true){kFipKVHJXH = false;}
      if(sAacmLDeaJ == true){sAacmLDeaJ = false;}
      if(ADLNyHAoEg == true){ADLNyHAoEg = false;}
      if(YgKtqcIZFU == true){YgKtqcIZFU = false;}
      if(TsIuNrZNag == true){TsIuNrZNag = false;}
      if(oSEyIhsVrC == true){oSEyIhsVrC = false;}
      if(USFqhMoglJ == true){USFqhMoglJ = false;}
      if(DcZFpGtQzF == true){DcZFpGtQzF = false;}
      if(hmNXqGbMlJ == true){hmNXqGbMlJ = false;}
      if(ilhCzAnRMB == true){ilhCzAnRMB = false;}
      if(DsbQcLryHB == true){DsbQcLryHB = false;}
      if(mcVlUhEgzb == true){mcVlUhEgzb = false;}
      if(jcubZQuXGo == true){jcubZQuXGo = false;}
      if(ScDyCoLxte == true){ScDyCoLxte = false;}
      if(NdEjWGPuhQ == true){NdEjWGPuhQ = false;}
      if(wGRkQaxzqM == true){wGRkQaxzqM = false;}
      if(QUrRhJYWje == true){QUrRhJYWje = false;}
      if(WHmTOFXKFT == true){WHmTOFXKFT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DABRBEJOLR
{ 
  void npYqCWsdIl()
  { 
      bool ADLBXnUzgR = false;
      bool ukVTszZtrG = false;
      bool gdxNbaSlJH = false;
      bool mnkOcGcCZd = false;
      bool IanagnIPlx = false;
      bool uyONYWGyZx = false;
      bool VioYeGAGql = false;
      bool WXTNyGoWgm = false;
      bool RDAMLnZWoF = false;
      bool AdbcIZlOuZ = false;
      bool nBXzaXeAPR = false;
      bool hiRleRhbNq = false;
      bool gdRklruqFY = false;
      bool UZaGzQeAln = false;
      bool IYGWXQMpxp = false;
      bool qJBErKjlMh = false;
      bool bmtqxHIKlO = false;
      bool lhpYhIWtNV = false;
      bool eFsPhLXWOn = false;
      bool gsmDLVePZP = false;
      string DZgnObhNHO;
      string edQGpokfCy;
      string XkYtNgHqZx;
      string zGjCUgLjDX;
      string QXHDntPMjj;
      string gNzAyRBlZh;
      string UpmJOYtOlJ;
      string cAbehzdUFS;
      string QuHoQkGiDC;
      string fZJUDZjxnP;
      string ABZaGfkUSy;
      string nffHRZiyrd;
      string RKKicDqHbI;
      string OfgpRPUghk;
      string zlQEOzsBDc;
      string plFKxpppxD;
      string ndsJjHzooB;
      string ECQGdftFUc;
      string KoDyRcZVrb;
      string YdiewVsGUG;
      if(DZgnObhNHO == ABZaGfkUSy){ADLBXnUzgR = true;}
      else if(ABZaGfkUSy == DZgnObhNHO){nBXzaXeAPR = true;}
      if(edQGpokfCy == nffHRZiyrd){ukVTszZtrG = true;}
      else if(nffHRZiyrd == edQGpokfCy){hiRleRhbNq = true;}
      if(XkYtNgHqZx == RKKicDqHbI){gdxNbaSlJH = true;}
      else if(RKKicDqHbI == XkYtNgHqZx){gdRklruqFY = true;}
      if(zGjCUgLjDX == OfgpRPUghk){mnkOcGcCZd = true;}
      else if(OfgpRPUghk == zGjCUgLjDX){UZaGzQeAln = true;}
      if(QXHDntPMjj == zlQEOzsBDc){IanagnIPlx = true;}
      else if(zlQEOzsBDc == QXHDntPMjj){IYGWXQMpxp = true;}
      if(gNzAyRBlZh == plFKxpppxD){uyONYWGyZx = true;}
      else if(plFKxpppxD == gNzAyRBlZh){qJBErKjlMh = true;}
      if(UpmJOYtOlJ == ndsJjHzooB){VioYeGAGql = true;}
      else if(ndsJjHzooB == UpmJOYtOlJ){bmtqxHIKlO = true;}
      if(cAbehzdUFS == ECQGdftFUc){WXTNyGoWgm = true;}
      if(QuHoQkGiDC == KoDyRcZVrb){RDAMLnZWoF = true;}
      if(fZJUDZjxnP == YdiewVsGUG){AdbcIZlOuZ = true;}
      while(ECQGdftFUc == cAbehzdUFS){lhpYhIWtNV = true;}
      while(KoDyRcZVrb == KoDyRcZVrb){eFsPhLXWOn = true;}
      while(YdiewVsGUG == YdiewVsGUG){gsmDLVePZP = true;}
      if(ADLBXnUzgR == true){ADLBXnUzgR = false;}
      if(ukVTszZtrG == true){ukVTszZtrG = false;}
      if(gdxNbaSlJH == true){gdxNbaSlJH = false;}
      if(mnkOcGcCZd == true){mnkOcGcCZd = false;}
      if(IanagnIPlx == true){IanagnIPlx = false;}
      if(uyONYWGyZx == true){uyONYWGyZx = false;}
      if(VioYeGAGql == true){VioYeGAGql = false;}
      if(WXTNyGoWgm == true){WXTNyGoWgm = false;}
      if(RDAMLnZWoF == true){RDAMLnZWoF = false;}
      if(AdbcIZlOuZ == true){AdbcIZlOuZ = false;}
      if(nBXzaXeAPR == true){nBXzaXeAPR = false;}
      if(hiRleRhbNq == true){hiRleRhbNq = false;}
      if(gdRklruqFY == true){gdRklruqFY = false;}
      if(UZaGzQeAln == true){UZaGzQeAln = false;}
      if(IYGWXQMpxp == true){IYGWXQMpxp = false;}
      if(qJBErKjlMh == true){qJBErKjlMh = false;}
      if(bmtqxHIKlO == true){bmtqxHIKlO = false;}
      if(lhpYhIWtNV == true){lhpYhIWtNV = false;}
      if(eFsPhLXWOn == true){eFsPhLXWOn = false;}
      if(gsmDLVePZP == true){gsmDLVePZP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPIPMFAICI
{ 
  void CeOguWSDYR()
  { 
      bool BkPAHkkSwG = false;
      bool dpFbtCQijj = false;
      bool tVEOyOOPyw = false;
      bool kUJdWNPaLt = false;
      bool PKLMwhqaSu = false;
      bool GGnUNefABs = false;
      bool VVTzVJgbFf = false;
      bool lpXpTiJrSP = false;
      bool WnxCoegnQq = false;
      bool gOYRXtpMqm = false;
      bool BPVlJQhxAd = false;
      bool UnhkWhXRJq = false;
      bool csLNzWQFRZ = false;
      bool rxAfOGSLsY = false;
      bool wimlVsgmuo = false;
      bool WYCAKIEHml = false;
      bool AcfakXmCWP = false;
      bool PMXktsFYrF = false;
      bool pcKbCTuAVG = false;
      bool CKYHYSDLBx = false;
      string MyJKwOYkcU;
      string TDHMCqJwWw;
      string yJToWCRzwy;
      string bXkHzNBfUQ;
      string tkXtrVLVsp;
      string yTszOCdUms;
      string xZoesuSzNn;
      string odaFCMlZwA;
      string pwGGAIeksw;
      string jgraTUwsBx;
      string DLHEATrnxB;
      string QDXlCAShdj;
      string QgGQEHkAlg;
      string PsYzxenCFg;
      string PpnqefIFYS;
      string BNPQfWFqzs;
      string hrBPlXdXoX;
      string LQcwTZrOkX;
      string yfaSeBcITZ;
      string YxCMyXoXFH;
      if(MyJKwOYkcU == DLHEATrnxB){BkPAHkkSwG = true;}
      else if(DLHEATrnxB == MyJKwOYkcU){BPVlJQhxAd = true;}
      if(TDHMCqJwWw == QDXlCAShdj){dpFbtCQijj = true;}
      else if(QDXlCAShdj == TDHMCqJwWw){UnhkWhXRJq = true;}
      if(yJToWCRzwy == QgGQEHkAlg){tVEOyOOPyw = true;}
      else if(QgGQEHkAlg == yJToWCRzwy){csLNzWQFRZ = true;}
      if(bXkHzNBfUQ == PsYzxenCFg){kUJdWNPaLt = true;}
      else if(PsYzxenCFg == bXkHzNBfUQ){rxAfOGSLsY = true;}
      if(tkXtrVLVsp == PpnqefIFYS){PKLMwhqaSu = true;}
      else if(PpnqefIFYS == tkXtrVLVsp){wimlVsgmuo = true;}
      if(yTszOCdUms == BNPQfWFqzs){GGnUNefABs = true;}
      else if(BNPQfWFqzs == yTszOCdUms){WYCAKIEHml = true;}
      if(xZoesuSzNn == hrBPlXdXoX){VVTzVJgbFf = true;}
      else if(hrBPlXdXoX == xZoesuSzNn){AcfakXmCWP = true;}
      if(odaFCMlZwA == LQcwTZrOkX){lpXpTiJrSP = true;}
      if(pwGGAIeksw == yfaSeBcITZ){WnxCoegnQq = true;}
      if(jgraTUwsBx == YxCMyXoXFH){gOYRXtpMqm = true;}
      while(LQcwTZrOkX == odaFCMlZwA){PMXktsFYrF = true;}
      while(yfaSeBcITZ == yfaSeBcITZ){pcKbCTuAVG = true;}
      while(YxCMyXoXFH == YxCMyXoXFH){CKYHYSDLBx = true;}
      if(BkPAHkkSwG == true){BkPAHkkSwG = false;}
      if(dpFbtCQijj == true){dpFbtCQijj = false;}
      if(tVEOyOOPyw == true){tVEOyOOPyw = false;}
      if(kUJdWNPaLt == true){kUJdWNPaLt = false;}
      if(PKLMwhqaSu == true){PKLMwhqaSu = false;}
      if(GGnUNefABs == true){GGnUNefABs = false;}
      if(VVTzVJgbFf == true){VVTzVJgbFf = false;}
      if(lpXpTiJrSP == true){lpXpTiJrSP = false;}
      if(WnxCoegnQq == true){WnxCoegnQq = false;}
      if(gOYRXtpMqm == true){gOYRXtpMqm = false;}
      if(BPVlJQhxAd == true){BPVlJQhxAd = false;}
      if(UnhkWhXRJq == true){UnhkWhXRJq = false;}
      if(csLNzWQFRZ == true){csLNzWQFRZ = false;}
      if(rxAfOGSLsY == true){rxAfOGSLsY = false;}
      if(wimlVsgmuo == true){wimlVsgmuo = false;}
      if(WYCAKIEHml == true){WYCAKIEHml = false;}
      if(AcfakXmCWP == true){AcfakXmCWP = false;}
      if(PMXktsFYrF == true){PMXktsFYrF = false;}
      if(pcKbCTuAVG == true){pcKbCTuAVG = false;}
      if(CKYHYSDLBx == true){CKYHYSDLBx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBOGJIXBAN
{ 
  void cpeqPByByV()
  { 
      bool rpcYjYssRP = false;
      bool FEzElwADRa = false;
      bool JzwXPdAWcb = false;
      bool JIIHzyCkDO = false;
      bool PqziaFZUWH = false;
      bool SLiSkrsEJG = false;
      bool YWPoFxurFm = false;
      bool sPACKRzMxJ = false;
      bool DeAVIyYoVG = false;
      bool FyaxosbJdd = false;
      bool JhOiODKfIT = false;
      bool rfHzCsVtfH = false;
      bool XGWyhunDNQ = false;
      bool ooiSAVQQGF = false;
      bool msfBNYqbtu = false;
      bool WhdVGDLQBT = false;
      bool OHSrdCwnzg = false;
      bool cFmaUeZUkJ = false;
      bool DMIRsHLNMw = false;
      bool JAPmqeZnXK = false;
      string dBXfTBtail;
      string qmaohDscMt;
      string MXigKZBcbA;
      string NlZsCYJAgS;
      string LmWOZoVfHs;
      string gOMasGRpUs;
      string zQyhYEMgmJ;
      string srwthYAUHV;
      string EUUiTyYyzu;
      string HTfmSuoooU;
      string bnsyznSSrU;
      string GxhyoewONa;
      string fOgqBZMIam;
      string jLfmtPaVif;
      string eGFeoJkgyn;
      string zZaNnNGBwZ;
      string bKqFktRuEY;
      string DZfhwYICCr;
      string neJmnJkRyf;
      string JZYIETPAtu;
      if(dBXfTBtail == bnsyznSSrU){rpcYjYssRP = true;}
      else if(bnsyznSSrU == dBXfTBtail){JhOiODKfIT = true;}
      if(qmaohDscMt == GxhyoewONa){FEzElwADRa = true;}
      else if(GxhyoewONa == qmaohDscMt){rfHzCsVtfH = true;}
      if(MXigKZBcbA == fOgqBZMIam){JzwXPdAWcb = true;}
      else if(fOgqBZMIam == MXigKZBcbA){XGWyhunDNQ = true;}
      if(NlZsCYJAgS == jLfmtPaVif){JIIHzyCkDO = true;}
      else if(jLfmtPaVif == NlZsCYJAgS){ooiSAVQQGF = true;}
      if(LmWOZoVfHs == eGFeoJkgyn){PqziaFZUWH = true;}
      else if(eGFeoJkgyn == LmWOZoVfHs){msfBNYqbtu = true;}
      if(gOMasGRpUs == zZaNnNGBwZ){SLiSkrsEJG = true;}
      else if(zZaNnNGBwZ == gOMasGRpUs){WhdVGDLQBT = true;}
      if(zQyhYEMgmJ == bKqFktRuEY){YWPoFxurFm = true;}
      else if(bKqFktRuEY == zQyhYEMgmJ){OHSrdCwnzg = true;}
      if(srwthYAUHV == DZfhwYICCr){sPACKRzMxJ = true;}
      if(EUUiTyYyzu == neJmnJkRyf){DeAVIyYoVG = true;}
      if(HTfmSuoooU == JZYIETPAtu){FyaxosbJdd = true;}
      while(DZfhwYICCr == srwthYAUHV){cFmaUeZUkJ = true;}
      while(neJmnJkRyf == neJmnJkRyf){DMIRsHLNMw = true;}
      while(JZYIETPAtu == JZYIETPAtu){JAPmqeZnXK = true;}
      if(rpcYjYssRP == true){rpcYjYssRP = false;}
      if(FEzElwADRa == true){FEzElwADRa = false;}
      if(JzwXPdAWcb == true){JzwXPdAWcb = false;}
      if(JIIHzyCkDO == true){JIIHzyCkDO = false;}
      if(PqziaFZUWH == true){PqziaFZUWH = false;}
      if(SLiSkrsEJG == true){SLiSkrsEJG = false;}
      if(YWPoFxurFm == true){YWPoFxurFm = false;}
      if(sPACKRzMxJ == true){sPACKRzMxJ = false;}
      if(DeAVIyYoVG == true){DeAVIyYoVG = false;}
      if(FyaxosbJdd == true){FyaxosbJdd = false;}
      if(JhOiODKfIT == true){JhOiODKfIT = false;}
      if(rfHzCsVtfH == true){rfHzCsVtfH = false;}
      if(XGWyhunDNQ == true){XGWyhunDNQ = false;}
      if(ooiSAVQQGF == true){ooiSAVQQGF = false;}
      if(msfBNYqbtu == true){msfBNYqbtu = false;}
      if(WhdVGDLQBT == true){WhdVGDLQBT = false;}
      if(OHSrdCwnzg == true){OHSrdCwnzg = false;}
      if(cFmaUeZUkJ == true){cFmaUeZUkJ = false;}
      if(DMIRsHLNMw == true){DMIRsHLNMw = false;}
      if(JAPmqeZnXK == true){JAPmqeZnXK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKSEYBZWXA
{ 
  void wxINNISUPC()
  { 
      bool jgVBMiguqO = false;
      bool zalkmLhHQg = false;
      bool ridBDrJUgw = false;
      bool wqXGrddrnj = false;
      bool cYUmDguubE = false;
      bool SluzMADTxT = false;
      bool ZMNtRIDerJ = false;
      bool hoSfETNpxW = false;
      bool xNrcdJuXtr = false;
      bool aJuTKQKZUu = false;
      bool dPDRVcSOus = false;
      bool lMVaVMTjQI = false;
      bool NejAiXtzVn = false;
      bool ImUCrgKZHA = false;
      bool qgcBFNnTxy = false;
      bool waJMhyfCix = false;
      bool iTsHjyqSio = false;
      bool BtcPQgCitU = false;
      bool jaBXqgdIUs = false;
      bool BHqJRWmVQG = false;
      string hYSXVRbKwL;
      string DuQQVFdkhV;
      string oePfxXEXaM;
      string XRPyuljOME;
      string PyABfkaxGq;
      string AJXlIDJlZx;
      string MDijnkeSVj;
      string UOXdGpdNAM;
      string wHRjLNtdpq;
      string bxnOqLPQNt;
      string FIbVVkksfR;
      string ZwkMAFlyXZ;
      string pBcdIWaIlt;
      string aMAFHneuOa;
      string cAyXReMaOl;
      string ZQrnEDfyNy;
      string KbHkqMueFM;
      string ZpjxwoDELc;
      string KztATJTMBD;
      string IggPPAsMgE;
      if(hYSXVRbKwL == FIbVVkksfR){jgVBMiguqO = true;}
      else if(FIbVVkksfR == hYSXVRbKwL){dPDRVcSOus = true;}
      if(DuQQVFdkhV == ZwkMAFlyXZ){zalkmLhHQg = true;}
      else if(ZwkMAFlyXZ == DuQQVFdkhV){lMVaVMTjQI = true;}
      if(oePfxXEXaM == pBcdIWaIlt){ridBDrJUgw = true;}
      else if(pBcdIWaIlt == oePfxXEXaM){NejAiXtzVn = true;}
      if(XRPyuljOME == aMAFHneuOa){wqXGrddrnj = true;}
      else if(aMAFHneuOa == XRPyuljOME){ImUCrgKZHA = true;}
      if(PyABfkaxGq == cAyXReMaOl){cYUmDguubE = true;}
      else if(cAyXReMaOl == PyABfkaxGq){qgcBFNnTxy = true;}
      if(AJXlIDJlZx == ZQrnEDfyNy){SluzMADTxT = true;}
      else if(ZQrnEDfyNy == AJXlIDJlZx){waJMhyfCix = true;}
      if(MDijnkeSVj == KbHkqMueFM){ZMNtRIDerJ = true;}
      else if(KbHkqMueFM == MDijnkeSVj){iTsHjyqSio = true;}
      if(UOXdGpdNAM == ZpjxwoDELc){hoSfETNpxW = true;}
      if(wHRjLNtdpq == KztATJTMBD){xNrcdJuXtr = true;}
      if(bxnOqLPQNt == IggPPAsMgE){aJuTKQKZUu = true;}
      while(ZpjxwoDELc == UOXdGpdNAM){BtcPQgCitU = true;}
      while(KztATJTMBD == KztATJTMBD){jaBXqgdIUs = true;}
      while(IggPPAsMgE == IggPPAsMgE){BHqJRWmVQG = true;}
      if(jgVBMiguqO == true){jgVBMiguqO = false;}
      if(zalkmLhHQg == true){zalkmLhHQg = false;}
      if(ridBDrJUgw == true){ridBDrJUgw = false;}
      if(wqXGrddrnj == true){wqXGrddrnj = false;}
      if(cYUmDguubE == true){cYUmDguubE = false;}
      if(SluzMADTxT == true){SluzMADTxT = false;}
      if(ZMNtRIDerJ == true){ZMNtRIDerJ = false;}
      if(hoSfETNpxW == true){hoSfETNpxW = false;}
      if(xNrcdJuXtr == true){xNrcdJuXtr = false;}
      if(aJuTKQKZUu == true){aJuTKQKZUu = false;}
      if(dPDRVcSOus == true){dPDRVcSOus = false;}
      if(lMVaVMTjQI == true){lMVaVMTjQI = false;}
      if(NejAiXtzVn == true){NejAiXtzVn = false;}
      if(ImUCrgKZHA == true){ImUCrgKZHA = false;}
      if(qgcBFNnTxy == true){qgcBFNnTxy = false;}
      if(waJMhyfCix == true){waJMhyfCix = false;}
      if(iTsHjyqSio == true){iTsHjyqSio = false;}
      if(BtcPQgCitU == true){BtcPQgCitU = false;}
      if(jaBXqgdIUs == true){jaBXqgdIUs = false;}
      if(BHqJRWmVQG == true){BHqJRWmVQG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDFSSLFSIT
{ 
  void opeMpuilAO()
  { 
      bool ZFEcRIDcDP = false;
      bool PWPasqDCBi = false;
      bool VqKHjBgTAf = false;
      bool gfDTQmUmsP = false;
      bool xtlYURpmJt = false;
      bool kcNqKitwrP = false;
      bool bibWijSwJG = false;
      bool VQIkkaElmR = false;
      bool KsKGtERLIh = false;
      bool rXtdnNSOpj = false;
      bool ysdDXUTbGi = false;
      bool dIJaEhYVbd = false;
      bool SHnbNxVexX = false;
      bool IpuCSQOHiZ = false;
      bool joFYEjOSYF = false;
      bool oxmLRqFCpZ = false;
      bool yoeianMHHn = false;
      bool TRlBtcCPXc = false;
      bool iDGrhLCjkb = false;
      bool LMRIbtKWyQ = false;
      string quhnYjeMQh;
      string XUIIHCYrpG;
      string mWlUJeoIbl;
      string LdwxaJiQKA;
      string AXgXYSAZND;
      string uSnGaUIMet;
      string uVjdVtYKgy;
      string THhpFPoOwp;
      string ePuYpspoVG;
      string AVkQFdmCBe;
      string torPjmkyAL;
      string ftQnOfaLnc;
      string DinaxyWRka;
      string blNQwpXfnC;
      string IrnKaGFxBZ;
      string DaOXbKAQRl;
      string QTMYjsfArY;
      string IuWlULtdAq;
      string rZPKXBWook;
      string oGOCkoeOag;
      if(quhnYjeMQh == torPjmkyAL){ZFEcRIDcDP = true;}
      else if(torPjmkyAL == quhnYjeMQh){ysdDXUTbGi = true;}
      if(XUIIHCYrpG == ftQnOfaLnc){PWPasqDCBi = true;}
      else if(ftQnOfaLnc == XUIIHCYrpG){dIJaEhYVbd = true;}
      if(mWlUJeoIbl == DinaxyWRka){VqKHjBgTAf = true;}
      else if(DinaxyWRka == mWlUJeoIbl){SHnbNxVexX = true;}
      if(LdwxaJiQKA == blNQwpXfnC){gfDTQmUmsP = true;}
      else if(blNQwpXfnC == LdwxaJiQKA){IpuCSQOHiZ = true;}
      if(AXgXYSAZND == IrnKaGFxBZ){xtlYURpmJt = true;}
      else if(IrnKaGFxBZ == AXgXYSAZND){joFYEjOSYF = true;}
      if(uSnGaUIMet == DaOXbKAQRl){kcNqKitwrP = true;}
      else if(DaOXbKAQRl == uSnGaUIMet){oxmLRqFCpZ = true;}
      if(uVjdVtYKgy == QTMYjsfArY){bibWijSwJG = true;}
      else if(QTMYjsfArY == uVjdVtYKgy){yoeianMHHn = true;}
      if(THhpFPoOwp == IuWlULtdAq){VQIkkaElmR = true;}
      if(ePuYpspoVG == rZPKXBWook){KsKGtERLIh = true;}
      if(AVkQFdmCBe == oGOCkoeOag){rXtdnNSOpj = true;}
      while(IuWlULtdAq == THhpFPoOwp){TRlBtcCPXc = true;}
      while(rZPKXBWook == rZPKXBWook){iDGrhLCjkb = true;}
      while(oGOCkoeOag == oGOCkoeOag){LMRIbtKWyQ = true;}
      if(ZFEcRIDcDP == true){ZFEcRIDcDP = false;}
      if(PWPasqDCBi == true){PWPasqDCBi = false;}
      if(VqKHjBgTAf == true){VqKHjBgTAf = false;}
      if(gfDTQmUmsP == true){gfDTQmUmsP = false;}
      if(xtlYURpmJt == true){xtlYURpmJt = false;}
      if(kcNqKitwrP == true){kcNqKitwrP = false;}
      if(bibWijSwJG == true){bibWijSwJG = false;}
      if(VQIkkaElmR == true){VQIkkaElmR = false;}
      if(KsKGtERLIh == true){KsKGtERLIh = false;}
      if(rXtdnNSOpj == true){rXtdnNSOpj = false;}
      if(ysdDXUTbGi == true){ysdDXUTbGi = false;}
      if(dIJaEhYVbd == true){dIJaEhYVbd = false;}
      if(SHnbNxVexX == true){SHnbNxVexX = false;}
      if(IpuCSQOHiZ == true){IpuCSQOHiZ = false;}
      if(joFYEjOSYF == true){joFYEjOSYF = false;}
      if(oxmLRqFCpZ == true){oxmLRqFCpZ = false;}
      if(yoeianMHHn == true){yoeianMHHn = false;}
      if(TRlBtcCPXc == true){TRlBtcCPXc = false;}
      if(iDGrhLCjkb == true){iDGrhLCjkb = false;}
      if(LMRIbtKWyQ == true){LMRIbtKWyQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QQIXUHEGXX
{ 
  void WluoEwJDJF()
  { 
      bool OcxEfBZSDV = false;
      bool JnjlxEVbJg = false;
      bool kZkVuMiEJL = false;
      bool UABpOOEbdU = false;
      bool olaeQBOaCu = false;
      bool pxVqRnqaJT = false;
      bool RUJqBJltWh = false;
      bool AtynqzzGEs = false;
      bool xIBOUWdKYa = false;
      bool XcRJCUcidH = false;
      bool PUDUtwygAR = false;
      bool ojWPVIStWd = false;
      bool eaUwJXbolV = false;
      bool WPcxdcEgUX = false;
      bool YwKGknGCns = false;
      bool BhLzcnAGKV = false;
      bool UJudtYGYks = false;
      bool DlZzFhQNKV = false;
      bool RYArUoDcUp = false;
      bool byWyCOBfLM = false;
      string whRpXNqnnf;
      string mAbahnVbLb;
      string auEWeXYcHO;
      string IdzWTGNScY;
      string kGTkghMamV;
      string FWboLActKz;
      string oOfZXJAFHa;
      string ZDzmpUbSpx;
      string KxokIlBJLS;
      string dTHdjWZsNX;
      string gHSMwCXoyq;
      string YKENnqYtQl;
      string HqtnwGuVCT;
      string thFRQDdcoG;
      string NMKTtSOtos;
      string xecaQpNePo;
      string GBlewpElwk;
      string MwFJXtfZtd;
      string qBfJVPEdAa;
      string ozMAAMZfXD;
      if(whRpXNqnnf == gHSMwCXoyq){OcxEfBZSDV = true;}
      else if(gHSMwCXoyq == whRpXNqnnf){PUDUtwygAR = true;}
      if(mAbahnVbLb == YKENnqYtQl){JnjlxEVbJg = true;}
      else if(YKENnqYtQl == mAbahnVbLb){ojWPVIStWd = true;}
      if(auEWeXYcHO == HqtnwGuVCT){kZkVuMiEJL = true;}
      else if(HqtnwGuVCT == auEWeXYcHO){eaUwJXbolV = true;}
      if(IdzWTGNScY == thFRQDdcoG){UABpOOEbdU = true;}
      else if(thFRQDdcoG == IdzWTGNScY){WPcxdcEgUX = true;}
      if(kGTkghMamV == NMKTtSOtos){olaeQBOaCu = true;}
      else if(NMKTtSOtos == kGTkghMamV){YwKGknGCns = true;}
      if(FWboLActKz == xecaQpNePo){pxVqRnqaJT = true;}
      else if(xecaQpNePo == FWboLActKz){BhLzcnAGKV = true;}
      if(oOfZXJAFHa == GBlewpElwk){RUJqBJltWh = true;}
      else if(GBlewpElwk == oOfZXJAFHa){UJudtYGYks = true;}
      if(ZDzmpUbSpx == MwFJXtfZtd){AtynqzzGEs = true;}
      if(KxokIlBJLS == qBfJVPEdAa){xIBOUWdKYa = true;}
      if(dTHdjWZsNX == ozMAAMZfXD){XcRJCUcidH = true;}
      while(MwFJXtfZtd == ZDzmpUbSpx){DlZzFhQNKV = true;}
      while(qBfJVPEdAa == qBfJVPEdAa){RYArUoDcUp = true;}
      while(ozMAAMZfXD == ozMAAMZfXD){byWyCOBfLM = true;}
      if(OcxEfBZSDV == true){OcxEfBZSDV = false;}
      if(JnjlxEVbJg == true){JnjlxEVbJg = false;}
      if(kZkVuMiEJL == true){kZkVuMiEJL = false;}
      if(UABpOOEbdU == true){UABpOOEbdU = false;}
      if(olaeQBOaCu == true){olaeQBOaCu = false;}
      if(pxVqRnqaJT == true){pxVqRnqaJT = false;}
      if(RUJqBJltWh == true){RUJqBJltWh = false;}
      if(AtynqzzGEs == true){AtynqzzGEs = false;}
      if(xIBOUWdKYa == true){xIBOUWdKYa = false;}
      if(XcRJCUcidH == true){XcRJCUcidH = false;}
      if(PUDUtwygAR == true){PUDUtwygAR = false;}
      if(ojWPVIStWd == true){ojWPVIStWd = false;}
      if(eaUwJXbolV == true){eaUwJXbolV = false;}
      if(WPcxdcEgUX == true){WPcxdcEgUX = false;}
      if(YwKGknGCns == true){YwKGknGCns = false;}
      if(BhLzcnAGKV == true){BhLzcnAGKV = false;}
      if(UJudtYGYks == true){UJudtYGYks = false;}
      if(DlZzFhQNKV == true){DlZzFhQNKV = false;}
      if(RYArUoDcUp == true){RYArUoDcUp = false;}
      if(byWyCOBfLM == true){byWyCOBfLM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMRNGWTKMB
{ 
  void zBhBMTKnxj()
  { 
      bool bxKqHrMxer = false;
      bool seWdHzmnsF = false;
      bool KRXYNrSoRi = false;
      bool tohqdjAHmC = false;
      bool UjYMYfsrAC = false;
      bool ZGerNJYkdP = false;
      bool ZWewyDxfAX = false;
      bool zfAqjasKAh = false;
      bool yZoPJmJodT = false;
      bool KOcXbxEcOU = false;
      bool iNrcCsGnIm = false;
      bool QNjwQzhPlK = false;
      bool sIBfMjDbOm = false;
      bool VQweyjhLMQ = false;
      bool fVgqDxdgGc = false;
      bool OopEaaMLPS = false;
      bool peZUQARFxg = false;
      bool QWCVdXaKcO = false;
      bool FVUkXgZrDX = false;
      bool XWutZBuLZC = false;
      string jgeDEybStf;
      string CEPWKoMlub;
      string bBadkHTlig;
      string hJBimGrjJG;
      string UjHWrhIArr;
      string zfjYUhFBSw;
      string epiMyrCfjE;
      string xccnHrsDlD;
      string zStqhCZcOE;
      string ApQNbdBuXz;
      string ecQnuVCuQc;
      string oCPOwLwrew;
      string SYQeDHMPMc;
      string pxflXWCGuL;
      string zdLkPyaBQQ;
      string hIQbgGLljn;
      string JlinmqVcqY;
      string IowTwnMfOF;
      string gKyutggEFR;
      string LQWHBNtXyX;
      if(jgeDEybStf == ecQnuVCuQc){bxKqHrMxer = true;}
      else if(ecQnuVCuQc == jgeDEybStf){iNrcCsGnIm = true;}
      if(CEPWKoMlub == oCPOwLwrew){seWdHzmnsF = true;}
      else if(oCPOwLwrew == CEPWKoMlub){QNjwQzhPlK = true;}
      if(bBadkHTlig == SYQeDHMPMc){KRXYNrSoRi = true;}
      else if(SYQeDHMPMc == bBadkHTlig){sIBfMjDbOm = true;}
      if(hJBimGrjJG == pxflXWCGuL){tohqdjAHmC = true;}
      else if(pxflXWCGuL == hJBimGrjJG){VQweyjhLMQ = true;}
      if(UjHWrhIArr == zdLkPyaBQQ){UjYMYfsrAC = true;}
      else if(zdLkPyaBQQ == UjHWrhIArr){fVgqDxdgGc = true;}
      if(zfjYUhFBSw == hIQbgGLljn){ZGerNJYkdP = true;}
      else if(hIQbgGLljn == zfjYUhFBSw){OopEaaMLPS = true;}
      if(epiMyrCfjE == JlinmqVcqY){ZWewyDxfAX = true;}
      else if(JlinmqVcqY == epiMyrCfjE){peZUQARFxg = true;}
      if(xccnHrsDlD == IowTwnMfOF){zfAqjasKAh = true;}
      if(zStqhCZcOE == gKyutggEFR){yZoPJmJodT = true;}
      if(ApQNbdBuXz == LQWHBNtXyX){KOcXbxEcOU = true;}
      while(IowTwnMfOF == xccnHrsDlD){QWCVdXaKcO = true;}
      while(gKyutggEFR == gKyutggEFR){FVUkXgZrDX = true;}
      while(LQWHBNtXyX == LQWHBNtXyX){XWutZBuLZC = true;}
      if(bxKqHrMxer == true){bxKqHrMxer = false;}
      if(seWdHzmnsF == true){seWdHzmnsF = false;}
      if(KRXYNrSoRi == true){KRXYNrSoRi = false;}
      if(tohqdjAHmC == true){tohqdjAHmC = false;}
      if(UjYMYfsrAC == true){UjYMYfsrAC = false;}
      if(ZGerNJYkdP == true){ZGerNJYkdP = false;}
      if(ZWewyDxfAX == true){ZWewyDxfAX = false;}
      if(zfAqjasKAh == true){zfAqjasKAh = false;}
      if(yZoPJmJodT == true){yZoPJmJodT = false;}
      if(KOcXbxEcOU == true){KOcXbxEcOU = false;}
      if(iNrcCsGnIm == true){iNrcCsGnIm = false;}
      if(QNjwQzhPlK == true){QNjwQzhPlK = false;}
      if(sIBfMjDbOm == true){sIBfMjDbOm = false;}
      if(VQweyjhLMQ == true){VQweyjhLMQ = false;}
      if(fVgqDxdgGc == true){fVgqDxdgGc = false;}
      if(OopEaaMLPS == true){OopEaaMLPS = false;}
      if(peZUQARFxg == true){peZUQARFxg = false;}
      if(QWCVdXaKcO == true){QWCVdXaKcO = false;}
      if(FVUkXgZrDX == true){FVUkXgZrDX = false;}
      if(XWutZBuLZC == true){XWutZBuLZC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEHASXANBA
{ 
  void JbySLHVZIi()
  { 
      bool poSzEmQcog = false;
      bool VDcOGSYjgN = false;
      bool BFdWKJTFGe = false;
      bool lhUIDLzBoW = false;
      bool XRGHnUZMnX = false;
      bool qfIpmkKwot = false;
      bool TLVJtmhTLt = false;
      bool TXtKpjyWho = false;
      bool iGRinFZdVS = false;
      bool ACLuDLuwMA = false;
      bool lFBsDSlxAC = false;
      bool lmNzLMtmVn = false;
      bool NDyrsQLzHd = false;
      bool nCKhDcFXeU = false;
      bool TbdSgMoLjq = false;
      bool RIaXmiHJzm = false;
      bool HlpVOicfwh = false;
      bool GVHATkYfKf = false;
      bool azPQMfbltT = false;
      bool VwYqNhlIEx = false;
      string xwHLSwwMfw;
      string TfAMUyWOAh;
      string NPKNYWWjqf;
      string KoIAfJqVNh;
      string ZnyHKVKlFX;
      string CKGqhgkslu;
      string ZLUAkdWzfK;
      string HAASHYRCDC;
      string MjeSczhRRz;
      string YyiRHOSxWf;
      string zLGtQBJnjJ;
      string PhpjipfBXl;
      string wFhgkJRiKr;
      string GTfXDBckCa;
      string psgIjqHzhQ;
      string hQZkiscZIH;
      string jZcqDuBSfh;
      string MuzxuCXZwt;
      string BRBsJotunJ;
      string XDbtpPPpEn;
      if(xwHLSwwMfw == zLGtQBJnjJ){poSzEmQcog = true;}
      else if(zLGtQBJnjJ == xwHLSwwMfw){lFBsDSlxAC = true;}
      if(TfAMUyWOAh == PhpjipfBXl){VDcOGSYjgN = true;}
      else if(PhpjipfBXl == TfAMUyWOAh){lmNzLMtmVn = true;}
      if(NPKNYWWjqf == wFhgkJRiKr){BFdWKJTFGe = true;}
      else if(wFhgkJRiKr == NPKNYWWjqf){NDyrsQLzHd = true;}
      if(KoIAfJqVNh == GTfXDBckCa){lhUIDLzBoW = true;}
      else if(GTfXDBckCa == KoIAfJqVNh){nCKhDcFXeU = true;}
      if(ZnyHKVKlFX == psgIjqHzhQ){XRGHnUZMnX = true;}
      else if(psgIjqHzhQ == ZnyHKVKlFX){TbdSgMoLjq = true;}
      if(CKGqhgkslu == hQZkiscZIH){qfIpmkKwot = true;}
      else if(hQZkiscZIH == CKGqhgkslu){RIaXmiHJzm = true;}
      if(ZLUAkdWzfK == jZcqDuBSfh){TLVJtmhTLt = true;}
      else if(jZcqDuBSfh == ZLUAkdWzfK){HlpVOicfwh = true;}
      if(HAASHYRCDC == MuzxuCXZwt){TXtKpjyWho = true;}
      if(MjeSczhRRz == BRBsJotunJ){iGRinFZdVS = true;}
      if(YyiRHOSxWf == XDbtpPPpEn){ACLuDLuwMA = true;}
      while(MuzxuCXZwt == HAASHYRCDC){GVHATkYfKf = true;}
      while(BRBsJotunJ == BRBsJotunJ){azPQMfbltT = true;}
      while(XDbtpPPpEn == XDbtpPPpEn){VwYqNhlIEx = true;}
      if(poSzEmQcog == true){poSzEmQcog = false;}
      if(VDcOGSYjgN == true){VDcOGSYjgN = false;}
      if(BFdWKJTFGe == true){BFdWKJTFGe = false;}
      if(lhUIDLzBoW == true){lhUIDLzBoW = false;}
      if(XRGHnUZMnX == true){XRGHnUZMnX = false;}
      if(qfIpmkKwot == true){qfIpmkKwot = false;}
      if(TLVJtmhTLt == true){TLVJtmhTLt = false;}
      if(TXtKpjyWho == true){TXtKpjyWho = false;}
      if(iGRinFZdVS == true){iGRinFZdVS = false;}
      if(ACLuDLuwMA == true){ACLuDLuwMA = false;}
      if(lFBsDSlxAC == true){lFBsDSlxAC = false;}
      if(lmNzLMtmVn == true){lmNzLMtmVn = false;}
      if(NDyrsQLzHd == true){NDyrsQLzHd = false;}
      if(nCKhDcFXeU == true){nCKhDcFXeU = false;}
      if(TbdSgMoLjq == true){TbdSgMoLjq = false;}
      if(RIaXmiHJzm == true){RIaXmiHJzm = false;}
      if(HlpVOicfwh == true){HlpVOicfwh = false;}
      if(GVHATkYfKf == true){GVHATkYfKf = false;}
      if(azPQMfbltT == true){azPQMfbltT = false;}
      if(VwYqNhlIEx == true){VwYqNhlIEx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRDQFTZXJM
{ 
  void NxdIncubJu()
  { 
      bool yNOcxbrdXx = false;
      bool UaLuunRCRK = false;
      bool mhoXXtehKe = false;
      bool VrdnRFPkgM = false;
      bool MlbRBHMThI = false;
      bool SmgJQQXqFC = false;
      bool xKTsbbxWcp = false;
      bool YfUFyBGXWP = false;
      bool hKzBLhKUWB = false;
      bool gYfePBRioY = false;
      bool KpqrjlRbKP = false;
      bool JAToTlKRgs = false;
      bool QcAbIAzpow = false;
      bool jWhyFrTGRZ = false;
      bool QiJHqgEpKd = false;
      bool qzBuHgpOjj = false;
      bool lamOelRVjb = false;
      bool RDAHchTrkb = false;
      bool uIfLEjVmpX = false;
      bool BFWhmoutbE = false;
      string AfWOunEeJG;
      string HYzGgTteyE;
      string icDflPIxdK;
      string cdyHnelQfr;
      string AMMxSnzYLi;
      string kfgXwXbqcf;
      string eHBzdcZrSB;
      string hczGEVQGNx;
      string PikuYxwaKP;
      string DunAMrLMTo;
      string NHGJBHfaTZ;
      string HVcePwVGZf;
      string gzhCylnztL;
      string KDmXjIcasR;
      string QVHjIgSJjQ;
      string WFmmINYELO;
      string TgfHPDhEtH;
      string StMIOKrysQ;
      string TeOdoFPAPV;
      string iXPdxjozTE;
      if(AfWOunEeJG == NHGJBHfaTZ){yNOcxbrdXx = true;}
      else if(NHGJBHfaTZ == AfWOunEeJG){KpqrjlRbKP = true;}
      if(HYzGgTteyE == HVcePwVGZf){UaLuunRCRK = true;}
      else if(HVcePwVGZf == HYzGgTteyE){JAToTlKRgs = true;}
      if(icDflPIxdK == gzhCylnztL){mhoXXtehKe = true;}
      else if(gzhCylnztL == icDflPIxdK){QcAbIAzpow = true;}
      if(cdyHnelQfr == KDmXjIcasR){VrdnRFPkgM = true;}
      else if(KDmXjIcasR == cdyHnelQfr){jWhyFrTGRZ = true;}
      if(AMMxSnzYLi == QVHjIgSJjQ){MlbRBHMThI = true;}
      else if(QVHjIgSJjQ == AMMxSnzYLi){QiJHqgEpKd = true;}
      if(kfgXwXbqcf == WFmmINYELO){SmgJQQXqFC = true;}
      else if(WFmmINYELO == kfgXwXbqcf){qzBuHgpOjj = true;}
      if(eHBzdcZrSB == TgfHPDhEtH){xKTsbbxWcp = true;}
      else if(TgfHPDhEtH == eHBzdcZrSB){lamOelRVjb = true;}
      if(hczGEVQGNx == StMIOKrysQ){YfUFyBGXWP = true;}
      if(PikuYxwaKP == TeOdoFPAPV){hKzBLhKUWB = true;}
      if(DunAMrLMTo == iXPdxjozTE){gYfePBRioY = true;}
      while(StMIOKrysQ == hczGEVQGNx){RDAHchTrkb = true;}
      while(TeOdoFPAPV == TeOdoFPAPV){uIfLEjVmpX = true;}
      while(iXPdxjozTE == iXPdxjozTE){BFWhmoutbE = true;}
      if(yNOcxbrdXx == true){yNOcxbrdXx = false;}
      if(UaLuunRCRK == true){UaLuunRCRK = false;}
      if(mhoXXtehKe == true){mhoXXtehKe = false;}
      if(VrdnRFPkgM == true){VrdnRFPkgM = false;}
      if(MlbRBHMThI == true){MlbRBHMThI = false;}
      if(SmgJQQXqFC == true){SmgJQQXqFC = false;}
      if(xKTsbbxWcp == true){xKTsbbxWcp = false;}
      if(YfUFyBGXWP == true){YfUFyBGXWP = false;}
      if(hKzBLhKUWB == true){hKzBLhKUWB = false;}
      if(gYfePBRioY == true){gYfePBRioY = false;}
      if(KpqrjlRbKP == true){KpqrjlRbKP = false;}
      if(JAToTlKRgs == true){JAToTlKRgs = false;}
      if(QcAbIAzpow == true){QcAbIAzpow = false;}
      if(jWhyFrTGRZ == true){jWhyFrTGRZ = false;}
      if(QiJHqgEpKd == true){QiJHqgEpKd = false;}
      if(qzBuHgpOjj == true){qzBuHgpOjj = false;}
      if(lamOelRVjb == true){lamOelRVjb = false;}
      if(RDAHchTrkb == true){RDAHchTrkb = false;}
      if(uIfLEjVmpX == true){uIfLEjVmpX = false;}
      if(BFWhmoutbE == true){BFWhmoutbE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWGQZHQWFZ
{ 
  void tZwlGQXonB()
  { 
      bool OszhxtACSJ = false;
      bool cBcrBrxpBO = false;
      bool KqgUOuyPse = false;
      bool MHsyroTfZL = false;
      bool IfEWfQaRks = false;
      bool AfgujWLdSB = false;
      bool wkInwVIdzL = false;
      bool XRPpFemKoy = false;
      bool UfdzegZxOV = false;
      bool dpMXOXWPZJ = false;
      bool IwRYVhPqoE = false;
      bool iBnUgPGJJP = false;
      bool wKPdhhEqah = false;
      bool IWjfoXOEdw = false;
      bool QhIJlcBrqz = false;
      bool QMGKNxgnqm = false;
      bool dXQGwMRIeJ = false;
      bool BBfNzNCGrE = false;
      bool gMAaRuQYSr = false;
      bool qaNpSrRBMZ = false;
      string pFJpgYjfSc;
      string UfELtJtpQD;
      string pJVhJMSZJo;
      string pkuxdwXPob;
      string bzlUuiylgL;
      string lpVpcfjafT;
      string FJWdlijHgx;
      string leAoapXBla;
      string OfsxDAPEUx;
      string MwiVVScIhM;
      string yqFjZGpfOl;
      string IhoFFZQZal;
      string SelikpwdSH;
      string NPSZbXaIWw;
      string JipiodHcPw;
      string CDgusSEWzj;
      string KLMHYsPOdh;
      string zHCecioDtG;
      string hSNWFJhXgI;
      string SDJmkxVhKu;
      if(pFJpgYjfSc == yqFjZGpfOl){OszhxtACSJ = true;}
      else if(yqFjZGpfOl == pFJpgYjfSc){IwRYVhPqoE = true;}
      if(UfELtJtpQD == IhoFFZQZal){cBcrBrxpBO = true;}
      else if(IhoFFZQZal == UfELtJtpQD){iBnUgPGJJP = true;}
      if(pJVhJMSZJo == SelikpwdSH){KqgUOuyPse = true;}
      else if(SelikpwdSH == pJVhJMSZJo){wKPdhhEqah = true;}
      if(pkuxdwXPob == NPSZbXaIWw){MHsyroTfZL = true;}
      else if(NPSZbXaIWw == pkuxdwXPob){IWjfoXOEdw = true;}
      if(bzlUuiylgL == JipiodHcPw){IfEWfQaRks = true;}
      else if(JipiodHcPw == bzlUuiylgL){QhIJlcBrqz = true;}
      if(lpVpcfjafT == CDgusSEWzj){AfgujWLdSB = true;}
      else if(CDgusSEWzj == lpVpcfjafT){QMGKNxgnqm = true;}
      if(FJWdlijHgx == KLMHYsPOdh){wkInwVIdzL = true;}
      else if(KLMHYsPOdh == FJWdlijHgx){dXQGwMRIeJ = true;}
      if(leAoapXBla == zHCecioDtG){XRPpFemKoy = true;}
      if(OfsxDAPEUx == hSNWFJhXgI){UfdzegZxOV = true;}
      if(MwiVVScIhM == SDJmkxVhKu){dpMXOXWPZJ = true;}
      while(zHCecioDtG == leAoapXBla){BBfNzNCGrE = true;}
      while(hSNWFJhXgI == hSNWFJhXgI){gMAaRuQYSr = true;}
      while(SDJmkxVhKu == SDJmkxVhKu){qaNpSrRBMZ = true;}
      if(OszhxtACSJ == true){OszhxtACSJ = false;}
      if(cBcrBrxpBO == true){cBcrBrxpBO = false;}
      if(KqgUOuyPse == true){KqgUOuyPse = false;}
      if(MHsyroTfZL == true){MHsyroTfZL = false;}
      if(IfEWfQaRks == true){IfEWfQaRks = false;}
      if(AfgujWLdSB == true){AfgujWLdSB = false;}
      if(wkInwVIdzL == true){wkInwVIdzL = false;}
      if(XRPpFemKoy == true){XRPpFemKoy = false;}
      if(UfdzegZxOV == true){UfdzegZxOV = false;}
      if(dpMXOXWPZJ == true){dpMXOXWPZJ = false;}
      if(IwRYVhPqoE == true){IwRYVhPqoE = false;}
      if(iBnUgPGJJP == true){iBnUgPGJJP = false;}
      if(wKPdhhEqah == true){wKPdhhEqah = false;}
      if(IWjfoXOEdw == true){IWjfoXOEdw = false;}
      if(QhIJlcBrqz == true){QhIJlcBrqz = false;}
      if(QMGKNxgnqm == true){QMGKNxgnqm = false;}
      if(dXQGwMRIeJ == true){dXQGwMRIeJ = false;}
      if(BBfNzNCGrE == true){BBfNzNCGrE = false;}
      if(gMAaRuQYSr == true){gMAaRuQYSr = false;}
      if(qaNpSrRBMZ == true){qaNpSrRBMZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHRULJLSKV
{ 
  void wuoBLECzZw()
  { 
      bool kbdPbYFCGk = false;
      bool UescqgyiLE = false;
      bool QqLKwbzDoA = false;
      bool UKjVDCYCYt = false;
      bool oSTULlVFei = false;
      bool DFXfesPSTA = false;
      bool ZBNGQKuWZn = false;
      bool HwKRPxXqyK = false;
      bool FtYGxOmEqJ = false;
      bool mGhYTnFNDB = false;
      bool pzfpaGuFPh = false;
      bool VYTJtfbGJB = false;
      bool WqfPBBNkxa = false;
      bool rJmxTGNiep = false;
      bool ShnInNlYdn = false;
      bool MyECezSQoZ = false;
      bool sJIooLkWpn = false;
      bool RraThoCWam = false;
      bool OoHJOsFkRT = false;
      bool nxsEwJYzTb = false;
      string bUnhhEHURy;
      string PRNCeEEGEp;
      string SUzjXjxSRC;
      string wxnBFdRUEu;
      string bychACPJKg;
      string sPPTsHUDKy;
      string HoCOCSdMxB;
      string ljCJNUqQjV;
      string UmIkJfgUHx;
      string INKGnmuNfg;
      string YDLJtJMGFX;
      string PETndTfQFV;
      string kIEArYYuVZ;
      string YdkCwQbzqA;
      string TaOjhEsVcT;
      string GeIJwPzLQV;
      string jRkezlSRrM;
      string qgZFCKtURn;
      string eDSBTtVaFg;
      string QPhVPCoiju;
      if(bUnhhEHURy == YDLJtJMGFX){kbdPbYFCGk = true;}
      else if(YDLJtJMGFX == bUnhhEHURy){pzfpaGuFPh = true;}
      if(PRNCeEEGEp == PETndTfQFV){UescqgyiLE = true;}
      else if(PETndTfQFV == PRNCeEEGEp){VYTJtfbGJB = true;}
      if(SUzjXjxSRC == kIEArYYuVZ){QqLKwbzDoA = true;}
      else if(kIEArYYuVZ == SUzjXjxSRC){WqfPBBNkxa = true;}
      if(wxnBFdRUEu == YdkCwQbzqA){UKjVDCYCYt = true;}
      else if(YdkCwQbzqA == wxnBFdRUEu){rJmxTGNiep = true;}
      if(bychACPJKg == TaOjhEsVcT){oSTULlVFei = true;}
      else if(TaOjhEsVcT == bychACPJKg){ShnInNlYdn = true;}
      if(sPPTsHUDKy == GeIJwPzLQV){DFXfesPSTA = true;}
      else if(GeIJwPzLQV == sPPTsHUDKy){MyECezSQoZ = true;}
      if(HoCOCSdMxB == jRkezlSRrM){ZBNGQKuWZn = true;}
      else if(jRkezlSRrM == HoCOCSdMxB){sJIooLkWpn = true;}
      if(ljCJNUqQjV == qgZFCKtURn){HwKRPxXqyK = true;}
      if(UmIkJfgUHx == eDSBTtVaFg){FtYGxOmEqJ = true;}
      if(INKGnmuNfg == QPhVPCoiju){mGhYTnFNDB = true;}
      while(qgZFCKtURn == ljCJNUqQjV){RraThoCWam = true;}
      while(eDSBTtVaFg == eDSBTtVaFg){OoHJOsFkRT = true;}
      while(QPhVPCoiju == QPhVPCoiju){nxsEwJYzTb = true;}
      if(kbdPbYFCGk == true){kbdPbYFCGk = false;}
      if(UescqgyiLE == true){UescqgyiLE = false;}
      if(QqLKwbzDoA == true){QqLKwbzDoA = false;}
      if(UKjVDCYCYt == true){UKjVDCYCYt = false;}
      if(oSTULlVFei == true){oSTULlVFei = false;}
      if(DFXfesPSTA == true){DFXfesPSTA = false;}
      if(ZBNGQKuWZn == true){ZBNGQKuWZn = false;}
      if(HwKRPxXqyK == true){HwKRPxXqyK = false;}
      if(FtYGxOmEqJ == true){FtYGxOmEqJ = false;}
      if(mGhYTnFNDB == true){mGhYTnFNDB = false;}
      if(pzfpaGuFPh == true){pzfpaGuFPh = false;}
      if(VYTJtfbGJB == true){VYTJtfbGJB = false;}
      if(WqfPBBNkxa == true){WqfPBBNkxa = false;}
      if(rJmxTGNiep == true){rJmxTGNiep = false;}
      if(ShnInNlYdn == true){ShnInNlYdn = false;}
      if(MyECezSQoZ == true){MyECezSQoZ = false;}
      if(sJIooLkWpn == true){sJIooLkWpn = false;}
      if(RraThoCWam == true){RraThoCWam = false;}
      if(OoHJOsFkRT == true){OoHJOsFkRT = false;}
      if(nxsEwJYzTb == true){nxsEwJYzTb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYEYYPVCGR
{ 
  void bKmRKhqgWF()
  { 
      bool HXhakXAxeZ = false;
      bool yPFYjCQfKS = false;
      bool JSKLDrGeSp = false;
      bool AWWTSTXGyg = false;
      bool wYnbGVJbbH = false;
      bool zgJatoNVWr = false;
      bool RVdnYarlFP = false;
      bool dJhcVkdhFg = false;
      bool hdCKqTMwYd = false;
      bool FBiFPauzDe = false;
      bool dWVLdozfEJ = false;
      bool KePoKmSSxF = false;
      bool NwNaKcabNt = false;
      bool peeaDKHpgB = false;
      bool UgqOTZltub = false;
      bool HbCxQgJuBA = false;
      bool OWSJTeAokz = false;
      bool ebkwjgFyHj = false;
      bool pfflmNcgKW = false;
      bool BMoflxNgun = false;
      string JLhGzbVceM;
      string DOReAWsYGg;
      string zOFMkTquIF;
      string dpEcIsIeDg;
      string LpwprZuJaR;
      string aSSVOtGVVe;
      string kZUZhNKoWH;
      string ONVZVJSOTK;
      string XhTpeLWiON;
      string llJXwkUVId;
      string PGmTDMwszE;
      string brBKHCGduV;
      string qaZIUbEycj;
      string nwFotRtzmR;
      string OcjJktjyQs;
      string eqZlmofdza;
      string HyPPPflMQo;
      string IGpcGNqQXa;
      string qFhjFxVTBE;
      string kPALKQMTsE;
      if(JLhGzbVceM == PGmTDMwszE){HXhakXAxeZ = true;}
      else if(PGmTDMwszE == JLhGzbVceM){dWVLdozfEJ = true;}
      if(DOReAWsYGg == brBKHCGduV){yPFYjCQfKS = true;}
      else if(brBKHCGduV == DOReAWsYGg){KePoKmSSxF = true;}
      if(zOFMkTquIF == qaZIUbEycj){JSKLDrGeSp = true;}
      else if(qaZIUbEycj == zOFMkTquIF){NwNaKcabNt = true;}
      if(dpEcIsIeDg == nwFotRtzmR){AWWTSTXGyg = true;}
      else if(nwFotRtzmR == dpEcIsIeDg){peeaDKHpgB = true;}
      if(LpwprZuJaR == OcjJktjyQs){wYnbGVJbbH = true;}
      else if(OcjJktjyQs == LpwprZuJaR){UgqOTZltub = true;}
      if(aSSVOtGVVe == eqZlmofdza){zgJatoNVWr = true;}
      else if(eqZlmofdza == aSSVOtGVVe){HbCxQgJuBA = true;}
      if(kZUZhNKoWH == HyPPPflMQo){RVdnYarlFP = true;}
      else if(HyPPPflMQo == kZUZhNKoWH){OWSJTeAokz = true;}
      if(ONVZVJSOTK == IGpcGNqQXa){dJhcVkdhFg = true;}
      if(XhTpeLWiON == qFhjFxVTBE){hdCKqTMwYd = true;}
      if(llJXwkUVId == kPALKQMTsE){FBiFPauzDe = true;}
      while(IGpcGNqQXa == ONVZVJSOTK){ebkwjgFyHj = true;}
      while(qFhjFxVTBE == qFhjFxVTBE){pfflmNcgKW = true;}
      while(kPALKQMTsE == kPALKQMTsE){BMoflxNgun = true;}
      if(HXhakXAxeZ == true){HXhakXAxeZ = false;}
      if(yPFYjCQfKS == true){yPFYjCQfKS = false;}
      if(JSKLDrGeSp == true){JSKLDrGeSp = false;}
      if(AWWTSTXGyg == true){AWWTSTXGyg = false;}
      if(wYnbGVJbbH == true){wYnbGVJbbH = false;}
      if(zgJatoNVWr == true){zgJatoNVWr = false;}
      if(RVdnYarlFP == true){RVdnYarlFP = false;}
      if(dJhcVkdhFg == true){dJhcVkdhFg = false;}
      if(hdCKqTMwYd == true){hdCKqTMwYd = false;}
      if(FBiFPauzDe == true){FBiFPauzDe = false;}
      if(dWVLdozfEJ == true){dWVLdozfEJ = false;}
      if(KePoKmSSxF == true){KePoKmSSxF = false;}
      if(NwNaKcabNt == true){NwNaKcabNt = false;}
      if(peeaDKHpgB == true){peeaDKHpgB = false;}
      if(UgqOTZltub == true){UgqOTZltub = false;}
      if(HbCxQgJuBA == true){HbCxQgJuBA = false;}
      if(OWSJTeAokz == true){OWSJTeAokz = false;}
      if(ebkwjgFyHj == true){ebkwjgFyHj = false;}
      if(pfflmNcgKW == true){pfflmNcgKW = false;}
      if(BMoflxNgun == true){BMoflxNgun = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APRPYVXULX
{ 
  void lLyYMrgjkK()
  { 
      bool klFFyXylhz = false;
      bool gGWNAiMMlP = false;
      bool GIsujhiLeK = false;
      bool AJAXKaiOah = false;
      bool HcgswHzFoA = false;
      bool BpcQKbsJVP = false;
      bool olGWyXFyCY = false;
      bool AylEHdbzzc = false;
      bool icVdJJfjNh = false;
      bool hYsKsUVJtX = false;
      bool BBDQADEYIf = false;
      bool AsKrfLQbNo = false;
      bool rVkTpaFaKm = false;
      bool HRFbbhZEdG = false;
      bool FHbghoOAdh = false;
      bool DswFffPiZY = false;
      bool xdNUYhmiQy = false;
      bool kLxHijtDkB = false;
      bool MFwciNVzuu = false;
      bool RpeFIbsGHA = false;
      string CGoyEJnENL;
      string WzMsLOWpML;
      string WeIWToDQus;
      string kenHuCXRPu;
      string aNrGjxXjYq;
      string ugdIhXxSeO;
      string FWJUaqLFyJ;
      string pFZQjImClV;
      string RTrExDAeYW;
      string EEmBoEEXer;
      string lRlOApGMXY;
      string kufIxleFWW;
      string pffaFlSYbf;
      string EPWtjzgcDH;
      string xnHAlJXdDC;
      string ZzAIBGlLJN;
      string XhkrUUXlYx;
      string EBBOZCYfnw;
      string NnUYFFOOrd;
      string NVSpjOCOfQ;
      if(CGoyEJnENL == lRlOApGMXY){klFFyXylhz = true;}
      else if(lRlOApGMXY == CGoyEJnENL){BBDQADEYIf = true;}
      if(WzMsLOWpML == kufIxleFWW){gGWNAiMMlP = true;}
      else if(kufIxleFWW == WzMsLOWpML){AsKrfLQbNo = true;}
      if(WeIWToDQus == pffaFlSYbf){GIsujhiLeK = true;}
      else if(pffaFlSYbf == WeIWToDQus){rVkTpaFaKm = true;}
      if(kenHuCXRPu == EPWtjzgcDH){AJAXKaiOah = true;}
      else if(EPWtjzgcDH == kenHuCXRPu){HRFbbhZEdG = true;}
      if(aNrGjxXjYq == xnHAlJXdDC){HcgswHzFoA = true;}
      else if(xnHAlJXdDC == aNrGjxXjYq){FHbghoOAdh = true;}
      if(ugdIhXxSeO == ZzAIBGlLJN){BpcQKbsJVP = true;}
      else if(ZzAIBGlLJN == ugdIhXxSeO){DswFffPiZY = true;}
      if(FWJUaqLFyJ == XhkrUUXlYx){olGWyXFyCY = true;}
      else if(XhkrUUXlYx == FWJUaqLFyJ){xdNUYhmiQy = true;}
      if(pFZQjImClV == EBBOZCYfnw){AylEHdbzzc = true;}
      if(RTrExDAeYW == NnUYFFOOrd){icVdJJfjNh = true;}
      if(EEmBoEEXer == NVSpjOCOfQ){hYsKsUVJtX = true;}
      while(EBBOZCYfnw == pFZQjImClV){kLxHijtDkB = true;}
      while(NnUYFFOOrd == NnUYFFOOrd){MFwciNVzuu = true;}
      while(NVSpjOCOfQ == NVSpjOCOfQ){RpeFIbsGHA = true;}
      if(klFFyXylhz == true){klFFyXylhz = false;}
      if(gGWNAiMMlP == true){gGWNAiMMlP = false;}
      if(GIsujhiLeK == true){GIsujhiLeK = false;}
      if(AJAXKaiOah == true){AJAXKaiOah = false;}
      if(HcgswHzFoA == true){HcgswHzFoA = false;}
      if(BpcQKbsJVP == true){BpcQKbsJVP = false;}
      if(olGWyXFyCY == true){olGWyXFyCY = false;}
      if(AylEHdbzzc == true){AylEHdbzzc = false;}
      if(icVdJJfjNh == true){icVdJJfjNh = false;}
      if(hYsKsUVJtX == true){hYsKsUVJtX = false;}
      if(BBDQADEYIf == true){BBDQADEYIf = false;}
      if(AsKrfLQbNo == true){AsKrfLQbNo = false;}
      if(rVkTpaFaKm == true){rVkTpaFaKm = false;}
      if(HRFbbhZEdG == true){HRFbbhZEdG = false;}
      if(FHbghoOAdh == true){FHbghoOAdh = false;}
      if(DswFffPiZY == true){DswFffPiZY = false;}
      if(xdNUYhmiQy == true){xdNUYhmiQy = false;}
      if(kLxHijtDkB == true){kLxHijtDkB = false;}
      if(MFwciNVzuu == true){MFwciNVzuu = false;}
      if(RpeFIbsGHA == true){RpeFIbsGHA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXTEYZUMCD
{ 
  void PFcNSCuTJm()
  { 
      bool xZKOzdIrzf = false;
      bool ChgwqtSMEh = false;
      bool DfRombZTFC = false;
      bool GdCYZUumJb = false;
      bool iAjsIcRqXc = false;
      bool bJzUQRHUbX = false;
      bool DomwYXfHWW = false;
      bool yeCbzCwYgJ = false;
      bool JiubZwehII = false;
      bool NZLkYsNmTj = false;
      bool xJTBdwGWUN = false;
      bool UhnRNUtKVb = false;
      bool sxzOJYTQDF = false;
      bool nIFwLAOsxd = false;
      bool pIMtmelsXE = false;
      bool zCQqqAKFrF = false;
      bool coSPYMcqGN = false;
      bool GAMrljjEbd = false;
      bool maszFlrNFL = false;
      bool oIBrAAoxVZ = false;
      string priIlhskPN;
      string bOeLqWFInF;
      string dsGChPbLzc;
      string FKrJZwVghe;
      string tQIQsErUzy;
      string oINTWwlgZV;
      string GglmIQVVlu;
      string AXZIKNjoId;
      string WHLAmwwYlc;
      string JoHLYMdUIb;
      string hWiExQhFIJ;
      string LwXwyyVlzL;
      string TxiJkLQOix;
      string iOgguAXHCW;
      string OqPcQNQLMZ;
      string qrVwHjnZTl;
      string zTVLZxPqAy;
      string aNicxbhFrW;
      string tFBJGqsjYK;
      string LynPWtVEDT;
      if(priIlhskPN == hWiExQhFIJ){xZKOzdIrzf = true;}
      else if(hWiExQhFIJ == priIlhskPN){xJTBdwGWUN = true;}
      if(bOeLqWFInF == LwXwyyVlzL){ChgwqtSMEh = true;}
      else if(LwXwyyVlzL == bOeLqWFInF){UhnRNUtKVb = true;}
      if(dsGChPbLzc == TxiJkLQOix){DfRombZTFC = true;}
      else if(TxiJkLQOix == dsGChPbLzc){sxzOJYTQDF = true;}
      if(FKrJZwVghe == iOgguAXHCW){GdCYZUumJb = true;}
      else if(iOgguAXHCW == FKrJZwVghe){nIFwLAOsxd = true;}
      if(tQIQsErUzy == OqPcQNQLMZ){iAjsIcRqXc = true;}
      else if(OqPcQNQLMZ == tQIQsErUzy){pIMtmelsXE = true;}
      if(oINTWwlgZV == qrVwHjnZTl){bJzUQRHUbX = true;}
      else if(qrVwHjnZTl == oINTWwlgZV){zCQqqAKFrF = true;}
      if(GglmIQVVlu == zTVLZxPqAy){DomwYXfHWW = true;}
      else if(zTVLZxPqAy == GglmIQVVlu){coSPYMcqGN = true;}
      if(AXZIKNjoId == aNicxbhFrW){yeCbzCwYgJ = true;}
      if(WHLAmwwYlc == tFBJGqsjYK){JiubZwehII = true;}
      if(JoHLYMdUIb == LynPWtVEDT){NZLkYsNmTj = true;}
      while(aNicxbhFrW == AXZIKNjoId){GAMrljjEbd = true;}
      while(tFBJGqsjYK == tFBJGqsjYK){maszFlrNFL = true;}
      while(LynPWtVEDT == LynPWtVEDT){oIBrAAoxVZ = true;}
      if(xZKOzdIrzf == true){xZKOzdIrzf = false;}
      if(ChgwqtSMEh == true){ChgwqtSMEh = false;}
      if(DfRombZTFC == true){DfRombZTFC = false;}
      if(GdCYZUumJb == true){GdCYZUumJb = false;}
      if(iAjsIcRqXc == true){iAjsIcRqXc = false;}
      if(bJzUQRHUbX == true){bJzUQRHUbX = false;}
      if(DomwYXfHWW == true){DomwYXfHWW = false;}
      if(yeCbzCwYgJ == true){yeCbzCwYgJ = false;}
      if(JiubZwehII == true){JiubZwehII = false;}
      if(NZLkYsNmTj == true){NZLkYsNmTj = false;}
      if(xJTBdwGWUN == true){xJTBdwGWUN = false;}
      if(UhnRNUtKVb == true){UhnRNUtKVb = false;}
      if(sxzOJYTQDF == true){sxzOJYTQDF = false;}
      if(nIFwLAOsxd == true){nIFwLAOsxd = false;}
      if(pIMtmelsXE == true){pIMtmelsXE = false;}
      if(zCQqqAKFrF == true){zCQqqAKFrF = false;}
      if(coSPYMcqGN == true){coSPYMcqGN = false;}
      if(GAMrljjEbd == true){GAMrljjEbd = false;}
      if(maszFlrNFL == true){maszFlrNFL = false;}
      if(oIBrAAoxVZ == true){oIBrAAoxVZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTDQESLSAG
{ 
  void jbkxYCRwMr()
  { 
      bool hidLJAxtII = false;
      bool eCjXCAKfBu = false;
      bool dBjdWowVbA = false;
      bool tUwqnLXhLu = false;
      bool ljxHggIzHr = false;
      bool FqBSFgyAoU = false;
      bool EbRHNKGsiq = false;
      bool bcUGItDcwo = false;
      bool gxOjuCSclG = false;
      bool MWsppKSpsW = false;
      bool ZOPPPcWtKL = false;
      bool dVEAnHMhML = false;
      bool qdGcdFjdQy = false;
      bool aMiYORhzTR = false;
      bool eYSabpSrCi = false;
      bool yjdhfwHlkK = false;
      bool ssdMjRlekV = false;
      bool YNNtfRLfAn = false;
      bool lqagzqhBsS = false;
      bool JuNJYkuGqK = false;
      string SaJyuAcjVZ;
      string ciHoEiNcse;
      string PoqIEadUPl;
      string twuNYNcSqB;
      string LkOuyOLtxh;
      string SEHgYcjBtT;
      string VHUiefmsPp;
      string GtkrTeZwJp;
      string PiXhSpoOnw;
      string dbXXeDQfPS;
      string aReGaXTPNt;
      string DnqEEljlPo;
      string qYETMdVNNP;
      string OtgqOxEQGu;
      string WYBtrpjTSr;
      string TdPZaCNLtw;
      string CFBxfIHAoG;
      string hSfURRXKaW;
      string tCtVujeGPL;
      string jsWJrQXDOi;
      if(SaJyuAcjVZ == aReGaXTPNt){hidLJAxtII = true;}
      else if(aReGaXTPNt == SaJyuAcjVZ){ZOPPPcWtKL = true;}
      if(ciHoEiNcse == DnqEEljlPo){eCjXCAKfBu = true;}
      else if(DnqEEljlPo == ciHoEiNcse){dVEAnHMhML = true;}
      if(PoqIEadUPl == qYETMdVNNP){dBjdWowVbA = true;}
      else if(qYETMdVNNP == PoqIEadUPl){qdGcdFjdQy = true;}
      if(twuNYNcSqB == OtgqOxEQGu){tUwqnLXhLu = true;}
      else if(OtgqOxEQGu == twuNYNcSqB){aMiYORhzTR = true;}
      if(LkOuyOLtxh == WYBtrpjTSr){ljxHggIzHr = true;}
      else if(WYBtrpjTSr == LkOuyOLtxh){eYSabpSrCi = true;}
      if(SEHgYcjBtT == TdPZaCNLtw){FqBSFgyAoU = true;}
      else if(TdPZaCNLtw == SEHgYcjBtT){yjdhfwHlkK = true;}
      if(VHUiefmsPp == CFBxfIHAoG){EbRHNKGsiq = true;}
      else if(CFBxfIHAoG == VHUiefmsPp){ssdMjRlekV = true;}
      if(GtkrTeZwJp == hSfURRXKaW){bcUGItDcwo = true;}
      if(PiXhSpoOnw == tCtVujeGPL){gxOjuCSclG = true;}
      if(dbXXeDQfPS == jsWJrQXDOi){MWsppKSpsW = true;}
      while(hSfURRXKaW == GtkrTeZwJp){YNNtfRLfAn = true;}
      while(tCtVujeGPL == tCtVujeGPL){lqagzqhBsS = true;}
      while(jsWJrQXDOi == jsWJrQXDOi){JuNJYkuGqK = true;}
      if(hidLJAxtII == true){hidLJAxtII = false;}
      if(eCjXCAKfBu == true){eCjXCAKfBu = false;}
      if(dBjdWowVbA == true){dBjdWowVbA = false;}
      if(tUwqnLXhLu == true){tUwqnLXhLu = false;}
      if(ljxHggIzHr == true){ljxHggIzHr = false;}
      if(FqBSFgyAoU == true){FqBSFgyAoU = false;}
      if(EbRHNKGsiq == true){EbRHNKGsiq = false;}
      if(bcUGItDcwo == true){bcUGItDcwo = false;}
      if(gxOjuCSclG == true){gxOjuCSclG = false;}
      if(MWsppKSpsW == true){MWsppKSpsW = false;}
      if(ZOPPPcWtKL == true){ZOPPPcWtKL = false;}
      if(dVEAnHMhML == true){dVEAnHMhML = false;}
      if(qdGcdFjdQy == true){qdGcdFjdQy = false;}
      if(aMiYORhzTR == true){aMiYORhzTR = false;}
      if(eYSabpSrCi == true){eYSabpSrCi = false;}
      if(yjdhfwHlkK == true){yjdhfwHlkK = false;}
      if(ssdMjRlekV == true){ssdMjRlekV = false;}
      if(YNNtfRLfAn == true){YNNtfRLfAn = false;}
      if(lqagzqhBsS == true){lqagzqhBsS = false;}
      if(JuNJYkuGqK == true){JuNJYkuGqK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILGRSXEDVJ
{ 
  void eutMPdsfca()
  { 
      bool ewRENEmBpb = false;
      bool cFEJEzSyeE = false;
      bool octpViQZGE = false;
      bool XojDJbmNIp = false;
      bool aOzXAIxxyA = false;
      bool aTFMhCBahe = false;
      bool mNtkEnVBzb = false;
      bool MFondZcVpM = false;
      bool lTbFdDiXUH = false;
      bool ZMedDNTOTM = false;
      bool muxVnVeRhH = false;
      bool ZejVsTlnHA = false;
      bool EyfrBAZKjQ = false;
      bool FOCdZpVFRI = false;
      bool YQoNgtbJki = false;
      bool aeGTHnOFTn = false;
      bool uThRBLcFwC = false;
      bool yfWzbnJSKH = false;
      bool XQZBoaHiWk = false;
      bool bPldMEiWLV = false;
      string jTFQxfoXZS;
      string VdCegLcRiI;
      string EQVZzbBRqR;
      string QKkgXumCPw;
      string dDaVIfNmYR;
      string TsebzSyfRU;
      string eWfIBKsUGk;
      string XZBmdBpzQS;
      string ONsYxWfIhE;
      string xGjuQGWSTx;
      string msgmtsqqyx;
      string cyOzGRdHKe;
      string ejlBnQoGVX;
      string dXfTfVgFeD;
      string enKkbyrknz;
      string bPHoSCGezc;
      string DkVZTESuTj;
      string kXbGzpZBZo;
      string YERWuOPpAc;
      string OBGCAtSjQW;
      if(jTFQxfoXZS == msgmtsqqyx){ewRENEmBpb = true;}
      else if(msgmtsqqyx == jTFQxfoXZS){muxVnVeRhH = true;}
      if(VdCegLcRiI == cyOzGRdHKe){cFEJEzSyeE = true;}
      else if(cyOzGRdHKe == VdCegLcRiI){ZejVsTlnHA = true;}
      if(EQVZzbBRqR == ejlBnQoGVX){octpViQZGE = true;}
      else if(ejlBnQoGVX == EQVZzbBRqR){EyfrBAZKjQ = true;}
      if(QKkgXumCPw == dXfTfVgFeD){XojDJbmNIp = true;}
      else if(dXfTfVgFeD == QKkgXumCPw){FOCdZpVFRI = true;}
      if(dDaVIfNmYR == enKkbyrknz){aOzXAIxxyA = true;}
      else if(enKkbyrknz == dDaVIfNmYR){YQoNgtbJki = true;}
      if(TsebzSyfRU == bPHoSCGezc){aTFMhCBahe = true;}
      else if(bPHoSCGezc == TsebzSyfRU){aeGTHnOFTn = true;}
      if(eWfIBKsUGk == DkVZTESuTj){mNtkEnVBzb = true;}
      else if(DkVZTESuTj == eWfIBKsUGk){uThRBLcFwC = true;}
      if(XZBmdBpzQS == kXbGzpZBZo){MFondZcVpM = true;}
      if(ONsYxWfIhE == YERWuOPpAc){lTbFdDiXUH = true;}
      if(xGjuQGWSTx == OBGCAtSjQW){ZMedDNTOTM = true;}
      while(kXbGzpZBZo == XZBmdBpzQS){yfWzbnJSKH = true;}
      while(YERWuOPpAc == YERWuOPpAc){XQZBoaHiWk = true;}
      while(OBGCAtSjQW == OBGCAtSjQW){bPldMEiWLV = true;}
      if(ewRENEmBpb == true){ewRENEmBpb = false;}
      if(cFEJEzSyeE == true){cFEJEzSyeE = false;}
      if(octpViQZGE == true){octpViQZGE = false;}
      if(XojDJbmNIp == true){XojDJbmNIp = false;}
      if(aOzXAIxxyA == true){aOzXAIxxyA = false;}
      if(aTFMhCBahe == true){aTFMhCBahe = false;}
      if(mNtkEnVBzb == true){mNtkEnVBzb = false;}
      if(MFondZcVpM == true){MFondZcVpM = false;}
      if(lTbFdDiXUH == true){lTbFdDiXUH = false;}
      if(ZMedDNTOTM == true){ZMedDNTOTM = false;}
      if(muxVnVeRhH == true){muxVnVeRhH = false;}
      if(ZejVsTlnHA == true){ZejVsTlnHA = false;}
      if(EyfrBAZKjQ == true){EyfrBAZKjQ = false;}
      if(FOCdZpVFRI == true){FOCdZpVFRI = false;}
      if(YQoNgtbJki == true){YQoNgtbJki = false;}
      if(aeGTHnOFTn == true){aeGTHnOFTn = false;}
      if(uThRBLcFwC == true){uThRBLcFwC = false;}
      if(yfWzbnJSKH == true){yfWzbnJSKH = false;}
      if(XQZBoaHiWk == true){XQZBoaHiWk = false;}
      if(bPldMEiWLV == true){bPldMEiWLV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKINAQPNCA
{ 
  void OyWCJgHaFF()
  { 
      bool mRcgykRtHQ = false;
      bool WdwKrnoNxH = false;
      bool PShlMkHyzj = false;
      bool UpqPxlFkBL = false;
      bool SpWIZVgBUC = false;
      bool WiIPoUiqUM = false;
      bool dTtXwgmgMG = false;
      bool iDLknZwZLq = false;
      bool EFcxNkgbab = false;
      bool DNQnhzuyLr = false;
      bool iAoOSSWXaP = false;
      bool YIfdIXpxJK = false;
      bool AKGjDVlXDo = false;
      bool dxOSHEQOet = false;
      bool NIBLDthmfJ = false;
      bool IyoArYsELx = false;
      bool fzUlkbtMVE = false;
      bool HbSOwqJugI = false;
      bool mzqsffHNZi = false;
      bool KMDgOOnPZb = false;
      string JPYWSXWgle;
      string HTFEmqzlFL;
      string ZeeoptbYaD;
      string YuZBEBYrYU;
      string dIWaWJcpCq;
      string XiLdadjigX;
      string wxGhGLsEzl;
      string SGNkhRIESg;
      string RkWieojwZZ;
      string QoLAXfBnUK;
      string PXpPYRUZwJ;
      string UfPzGKaWDQ;
      string bweYUctMMC;
      string PUiIQsuGKN;
      string TJAPFjYLtN;
      string EejEiTsQtw;
      string WIMtsAxHiM;
      string PTMpwRwOTj;
      string DhSzxkjdYx;
      string AdLNpLxGWE;
      if(JPYWSXWgle == PXpPYRUZwJ){mRcgykRtHQ = true;}
      else if(PXpPYRUZwJ == JPYWSXWgle){iAoOSSWXaP = true;}
      if(HTFEmqzlFL == UfPzGKaWDQ){WdwKrnoNxH = true;}
      else if(UfPzGKaWDQ == HTFEmqzlFL){YIfdIXpxJK = true;}
      if(ZeeoptbYaD == bweYUctMMC){PShlMkHyzj = true;}
      else if(bweYUctMMC == ZeeoptbYaD){AKGjDVlXDo = true;}
      if(YuZBEBYrYU == PUiIQsuGKN){UpqPxlFkBL = true;}
      else if(PUiIQsuGKN == YuZBEBYrYU){dxOSHEQOet = true;}
      if(dIWaWJcpCq == TJAPFjYLtN){SpWIZVgBUC = true;}
      else if(TJAPFjYLtN == dIWaWJcpCq){NIBLDthmfJ = true;}
      if(XiLdadjigX == EejEiTsQtw){WiIPoUiqUM = true;}
      else if(EejEiTsQtw == XiLdadjigX){IyoArYsELx = true;}
      if(wxGhGLsEzl == WIMtsAxHiM){dTtXwgmgMG = true;}
      else if(WIMtsAxHiM == wxGhGLsEzl){fzUlkbtMVE = true;}
      if(SGNkhRIESg == PTMpwRwOTj){iDLknZwZLq = true;}
      if(RkWieojwZZ == DhSzxkjdYx){EFcxNkgbab = true;}
      if(QoLAXfBnUK == AdLNpLxGWE){DNQnhzuyLr = true;}
      while(PTMpwRwOTj == SGNkhRIESg){HbSOwqJugI = true;}
      while(DhSzxkjdYx == DhSzxkjdYx){mzqsffHNZi = true;}
      while(AdLNpLxGWE == AdLNpLxGWE){KMDgOOnPZb = true;}
      if(mRcgykRtHQ == true){mRcgykRtHQ = false;}
      if(WdwKrnoNxH == true){WdwKrnoNxH = false;}
      if(PShlMkHyzj == true){PShlMkHyzj = false;}
      if(UpqPxlFkBL == true){UpqPxlFkBL = false;}
      if(SpWIZVgBUC == true){SpWIZVgBUC = false;}
      if(WiIPoUiqUM == true){WiIPoUiqUM = false;}
      if(dTtXwgmgMG == true){dTtXwgmgMG = false;}
      if(iDLknZwZLq == true){iDLknZwZLq = false;}
      if(EFcxNkgbab == true){EFcxNkgbab = false;}
      if(DNQnhzuyLr == true){DNQnhzuyLr = false;}
      if(iAoOSSWXaP == true){iAoOSSWXaP = false;}
      if(YIfdIXpxJK == true){YIfdIXpxJK = false;}
      if(AKGjDVlXDo == true){AKGjDVlXDo = false;}
      if(dxOSHEQOet == true){dxOSHEQOet = false;}
      if(NIBLDthmfJ == true){NIBLDthmfJ = false;}
      if(IyoArYsELx == true){IyoArYsELx = false;}
      if(fzUlkbtMVE == true){fzUlkbtMVE = false;}
      if(HbSOwqJugI == true){HbSOwqJugI = false;}
      if(mzqsffHNZi == true){mzqsffHNZi = false;}
      if(KMDgOOnPZb == true){KMDgOOnPZb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJWYHCHIVT
{ 
  void JaiPyXVaok()
  { 
      bool PEMUSuKpcg = false;
      bool eJLUtNXLkV = false;
      bool cmiQbmnlPn = false;
      bool zSqUQdclqp = false;
      bool LAzMUQPTpK = false;
      bool exyjNcVwre = false;
      bool GXanhMRqEQ = false;
      bool jkTuKbmVuL = false;
      bool XUwFJCTGHn = false;
      bool IfsMimZLeI = false;
      bool yYPYZtcDYk = false;
      bool ozAgHlbUdf = false;
      bool sLjPIDqGLW = false;
      bool CbqmMyEWeO = false;
      bool YQgVzIfMFw = false;
      bool KEgyPmozPV = false;
      bool CWqBiMINTI = false;
      bool hFpPGcdNQA = false;
      bool XdBPMyurXZ = false;
      bool JEGIMCYfml = false;
      string cykxuTtumz;
      string XZBbrZJIxV;
      string ZXyNUcKUGY;
      string juZKFpQIXH;
      string SFIIDrsQPB;
      string YsDkPEAWcR;
      string JZoOPczpWB;
      string JBjpDTPoKb;
      string isFEzpqotA;
      string ptfFxsQssa;
      string rCtNrXINgu;
      string oKMAiPUjOY;
      string kKwVLOUdrK;
      string DVwiifzqMa;
      string gdHyKegeWh;
      string YgdTohGXCc;
      string DeUWrTOcRC;
      string PcWnqHCxLg;
      string hpGJkVqbtA;
      string ZbojXCIjGp;
      if(cykxuTtumz == rCtNrXINgu){PEMUSuKpcg = true;}
      else if(rCtNrXINgu == cykxuTtumz){yYPYZtcDYk = true;}
      if(XZBbrZJIxV == oKMAiPUjOY){eJLUtNXLkV = true;}
      else if(oKMAiPUjOY == XZBbrZJIxV){ozAgHlbUdf = true;}
      if(ZXyNUcKUGY == kKwVLOUdrK){cmiQbmnlPn = true;}
      else if(kKwVLOUdrK == ZXyNUcKUGY){sLjPIDqGLW = true;}
      if(juZKFpQIXH == DVwiifzqMa){zSqUQdclqp = true;}
      else if(DVwiifzqMa == juZKFpQIXH){CbqmMyEWeO = true;}
      if(SFIIDrsQPB == gdHyKegeWh){LAzMUQPTpK = true;}
      else if(gdHyKegeWh == SFIIDrsQPB){YQgVzIfMFw = true;}
      if(YsDkPEAWcR == YgdTohGXCc){exyjNcVwre = true;}
      else if(YgdTohGXCc == YsDkPEAWcR){KEgyPmozPV = true;}
      if(JZoOPczpWB == DeUWrTOcRC){GXanhMRqEQ = true;}
      else if(DeUWrTOcRC == JZoOPczpWB){CWqBiMINTI = true;}
      if(JBjpDTPoKb == PcWnqHCxLg){jkTuKbmVuL = true;}
      if(isFEzpqotA == hpGJkVqbtA){XUwFJCTGHn = true;}
      if(ptfFxsQssa == ZbojXCIjGp){IfsMimZLeI = true;}
      while(PcWnqHCxLg == JBjpDTPoKb){hFpPGcdNQA = true;}
      while(hpGJkVqbtA == hpGJkVqbtA){XdBPMyurXZ = true;}
      while(ZbojXCIjGp == ZbojXCIjGp){JEGIMCYfml = true;}
      if(PEMUSuKpcg == true){PEMUSuKpcg = false;}
      if(eJLUtNXLkV == true){eJLUtNXLkV = false;}
      if(cmiQbmnlPn == true){cmiQbmnlPn = false;}
      if(zSqUQdclqp == true){zSqUQdclqp = false;}
      if(LAzMUQPTpK == true){LAzMUQPTpK = false;}
      if(exyjNcVwre == true){exyjNcVwre = false;}
      if(GXanhMRqEQ == true){GXanhMRqEQ = false;}
      if(jkTuKbmVuL == true){jkTuKbmVuL = false;}
      if(XUwFJCTGHn == true){XUwFJCTGHn = false;}
      if(IfsMimZLeI == true){IfsMimZLeI = false;}
      if(yYPYZtcDYk == true){yYPYZtcDYk = false;}
      if(ozAgHlbUdf == true){ozAgHlbUdf = false;}
      if(sLjPIDqGLW == true){sLjPIDqGLW = false;}
      if(CbqmMyEWeO == true){CbqmMyEWeO = false;}
      if(YQgVzIfMFw == true){YQgVzIfMFw = false;}
      if(KEgyPmozPV == true){KEgyPmozPV = false;}
      if(CWqBiMINTI == true){CWqBiMINTI = false;}
      if(hFpPGcdNQA == true){hFpPGcdNQA = false;}
      if(XdBPMyurXZ == true){XdBPMyurXZ = false;}
      if(JEGIMCYfml == true){JEGIMCYfml = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLUUGUPYRE
{ 
  void NJreoZSbQZ()
  { 
      bool ERaRlGtibT = false;
      bool sucthrIeuq = false;
      bool dANDHnArsi = false;
      bool QekDKRBzBV = false;
      bool nuOSJqcsuE = false;
      bool YaGbKEEWJx = false;
      bool GCpsCNKYiP = false;
      bool pIcZDilutQ = false;
      bool LGwoJpYIsG = false;
      bool NdpEPkFVPu = false;
      bool fEJeNPyfXb = false;
      bool SIcslzGAiM = false;
      bool oBfcCMSYKS = false;
      bool cPeyjHwRat = false;
      bool rrkQnEAwSP = false;
      bool dElDFdXgcB = false;
      bool wYVFyCddId = false;
      bool CoZoUxQOox = false;
      bool LWGtnYdbrF = false;
      bool iPnZxSVeRl = false;
      string cmBbIOnKMW;
      string bOiRqntdjC;
      string maGIdsEefG;
      string lUgTOFpQHN;
      string sJnDrRKPJR;
      string JZJHCBfsxO;
      string KJdFkGhODl;
      string ydVWJdmDPM;
      string hnVOxLLYRM;
      string YwSrCjehSl;
      string iwMWTfDmyY;
      string OcdjfVmPIY;
      string uIxqMCKcTY;
      string yFkcdlbytR;
      string HXasywShLf;
      string wPZsqazVKR;
      string UZSYZIrAGt;
      string toUpQWgDsP;
      string jcRmcheqlC;
      string lFncwhFCSo;
      if(cmBbIOnKMW == iwMWTfDmyY){ERaRlGtibT = true;}
      else if(iwMWTfDmyY == cmBbIOnKMW){fEJeNPyfXb = true;}
      if(bOiRqntdjC == OcdjfVmPIY){sucthrIeuq = true;}
      else if(OcdjfVmPIY == bOiRqntdjC){SIcslzGAiM = true;}
      if(maGIdsEefG == uIxqMCKcTY){dANDHnArsi = true;}
      else if(uIxqMCKcTY == maGIdsEefG){oBfcCMSYKS = true;}
      if(lUgTOFpQHN == yFkcdlbytR){QekDKRBzBV = true;}
      else if(yFkcdlbytR == lUgTOFpQHN){cPeyjHwRat = true;}
      if(sJnDrRKPJR == HXasywShLf){nuOSJqcsuE = true;}
      else if(HXasywShLf == sJnDrRKPJR){rrkQnEAwSP = true;}
      if(JZJHCBfsxO == wPZsqazVKR){YaGbKEEWJx = true;}
      else if(wPZsqazVKR == JZJHCBfsxO){dElDFdXgcB = true;}
      if(KJdFkGhODl == UZSYZIrAGt){GCpsCNKYiP = true;}
      else if(UZSYZIrAGt == KJdFkGhODl){wYVFyCddId = true;}
      if(ydVWJdmDPM == toUpQWgDsP){pIcZDilutQ = true;}
      if(hnVOxLLYRM == jcRmcheqlC){LGwoJpYIsG = true;}
      if(YwSrCjehSl == lFncwhFCSo){NdpEPkFVPu = true;}
      while(toUpQWgDsP == ydVWJdmDPM){CoZoUxQOox = true;}
      while(jcRmcheqlC == jcRmcheqlC){LWGtnYdbrF = true;}
      while(lFncwhFCSo == lFncwhFCSo){iPnZxSVeRl = true;}
      if(ERaRlGtibT == true){ERaRlGtibT = false;}
      if(sucthrIeuq == true){sucthrIeuq = false;}
      if(dANDHnArsi == true){dANDHnArsi = false;}
      if(QekDKRBzBV == true){QekDKRBzBV = false;}
      if(nuOSJqcsuE == true){nuOSJqcsuE = false;}
      if(YaGbKEEWJx == true){YaGbKEEWJx = false;}
      if(GCpsCNKYiP == true){GCpsCNKYiP = false;}
      if(pIcZDilutQ == true){pIcZDilutQ = false;}
      if(LGwoJpYIsG == true){LGwoJpYIsG = false;}
      if(NdpEPkFVPu == true){NdpEPkFVPu = false;}
      if(fEJeNPyfXb == true){fEJeNPyfXb = false;}
      if(SIcslzGAiM == true){SIcslzGAiM = false;}
      if(oBfcCMSYKS == true){oBfcCMSYKS = false;}
      if(cPeyjHwRat == true){cPeyjHwRat = false;}
      if(rrkQnEAwSP == true){rrkQnEAwSP = false;}
      if(dElDFdXgcB == true){dElDFdXgcB = false;}
      if(wYVFyCddId == true){wYVFyCddId = false;}
      if(CoZoUxQOox == true){CoZoUxQOox = false;}
      if(LWGtnYdbrF == true){LWGtnYdbrF = false;}
      if(iPnZxSVeRl == true){iPnZxSVeRl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UPJXFLYNZN
{ 
  void atjxtjtNwx()
  { 
      bool WJFIklbsaL = false;
      bool oXmzoNsAsh = false;
      bool zbEPTREhsw = false;
      bool hzbxGLFqqh = false;
      bool ZeuMKoIuYF = false;
      bool sJSQbuEooS = false;
      bool htzdcpwosc = false;
      bool HBIKITfrEe = false;
      bool JJJmDXgLVL = false;
      bool HQCXAeeQjU = false;
      bool sSBuxqBHHH = false;
      bool OMkKJYkLaE = false;
      bool JjTgVqzjKc = false;
      bool nPHjlpHNpL = false;
      bool WYDNxtfqNa = false;
      bool tSpeLIzUYG = false;
      bool rQweSzFAYT = false;
      bool QWVOgjgFjb = false;
      bool LHViiVYbXc = false;
      bool pmnjTGbYuy = false;
      string ntkFsSuiYA;
      string JzcQlOKSYp;
      string czJSAgEZSW;
      string WmWYplLqtf;
      string cJLDGNMLaX;
      string YHweenkREM;
      string NVPCdWbDZz;
      string DTXsMTmFLm;
      string TsztxOprtB;
      string AsmhSHsJYj;
      string kIkbUFiDSK;
      string BeFRrUVVEO;
      string fjJYyJfpZF;
      string ZcgbBLHXZr;
      string fmYizUmUox;
      string kXFKDAyMcL;
      string YscNjXydPg;
      string MywLirLaYc;
      string VKAcTCXWYA;
      string MutNSlKLyb;
      if(ntkFsSuiYA == kIkbUFiDSK){WJFIklbsaL = true;}
      else if(kIkbUFiDSK == ntkFsSuiYA){sSBuxqBHHH = true;}
      if(JzcQlOKSYp == BeFRrUVVEO){oXmzoNsAsh = true;}
      else if(BeFRrUVVEO == JzcQlOKSYp){OMkKJYkLaE = true;}
      if(czJSAgEZSW == fjJYyJfpZF){zbEPTREhsw = true;}
      else if(fjJYyJfpZF == czJSAgEZSW){JjTgVqzjKc = true;}
      if(WmWYplLqtf == ZcgbBLHXZr){hzbxGLFqqh = true;}
      else if(ZcgbBLHXZr == WmWYplLqtf){nPHjlpHNpL = true;}
      if(cJLDGNMLaX == fmYizUmUox){ZeuMKoIuYF = true;}
      else if(fmYizUmUox == cJLDGNMLaX){WYDNxtfqNa = true;}
      if(YHweenkREM == kXFKDAyMcL){sJSQbuEooS = true;}
      else if(kXFKDAyMcL == YHweenkREM){tSpeLIzUYG = true;}
      if(NVPCdWbDZz == YscNjXydPg){htzdcpwosc = true;}
      else if(YscNjXydPg == NVPCdWbDZz){rQweSzFAYT = true;}
      if(DTXsMTmFLm == MywLirLaYc){HBIKITfrEe = true;}
      if(TsztxOprtB == VKAcTCXWYA){JJJmDXgLVL = true;}
      if(AsmhSHsJYj == MutNSlKLyb){HQCXAeeQjU = true;}
      while(MywLirLaYc == DTXsMTmFLm){QWVOgjgFjb = true;}
      while(VKAcTCXWYA == VKAcTCXWYA){LHViiVYbXc = true;}
      while(MutNSlKLyb == MutNSlKLyb){pmnjTGbYuy = true;}
      if(WJFIklbsaL == true){WJFIklbsaL = false;}
      if(oXmzoNsAsh == true){oXmzoNsAsh = false;}
      if(zbEPTREhsw == true){zbEPTREhsw = false;}
      if(hzbxGLFqqh == true){hzbxGLFqqh = false;}
      if(ZeuMKoIuYF == true){ZeuMKoIuYF = false;}
      if(sJSQbuEooS == true){sJSQbuEooS = false;}
      if(htzdcpwosc == true){htzdcpwosc = false;}
      if(HBIKITfrEe == true){HBIKITfrEe = false;}
      if(JJJmDXgLVL == true){JJJmDXgLVL = false;}
      if(HQCXAeeQjU == true){HQCXAeeQjU = false;}
      if(sSBuxqBHHH == true){sSBuxqBHHH = false;}
      if(OMkKJYkLaE == true){OMkKJYkLaE = false;}
      if(JjTgVqzjKc == true){JjTgVqzjKc = false;}
      if(nPHjlpHNpL == true){nPHjlpHNpL = false;}
      if(WYDNxtfqNa == true){WYDNxtfqNa = false;}
      if(tSpeLIzUYG == true){tSpeLIzUYG = false;}
      if(rQweSzFAYT == true){rQweSzFAYT = false;}
      if(QWVOgjgFjb == true){QWVOgjgFjb = false;}
      if(LHViiVYbXc == true){LHViiVYbXc = false;}
      if(pmnjTGbYuy == true){pmnjTGbYuy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSSTSKSFHY
{ 
  void nDzjhpsLGh()
  { 
      bool RPqTWQtnwT = false;
      bool MVjwexZFNO = false;
      bool KozzZuwbxo = false;
      bool XRAJZrzCbF = false;
      bool VgTYHgeeED = false;
      bool hsiUobPrtb = false;
      bool URpGutUZWm = false;
      bool xWdHrcUaqr = false;
      bool QQXtHeifUx = false;
      bool cHIzjDqNdM = false;
      bool MEIRGKOabL = false;
      bool HnABLDtwzP = false;
      bool LnFYKoNdXo = false;
      bool lHxeeLIGmw = false;
      bool PIEIonHGmf = false;
      bool JtNNBXziGQ = false;
      bool xkDlZAqVWz = false;
      bool unIDzDjwjW = false;
      bool hGqqfqsicH = false;
      bool MYzWyeERio = false;
      string ElzsRcVmbH;
      string NciuFEodfO;
      string NgTaKVYSbF;
      string lBHYoFHKcC;
      string cByPbrLlCA;
      string WRNfMWSYhu;
      string ECKWVMVJFA;
      string xeBdkMiDyR;
      string KmQahUmaMR;
      string lhbgxZpatP;
      string VCfBDrPjtz;
      string mOaPkQljnB;
      string ZuwmNPDTfK;
      string VIJhwIHOXo;
      string ECfMdWHLwg;
      string nGmspaFrmm;
      string nwEjdeFrTc;
      string JWMywWOjIq;
      string HqWyWPUQrU;
      string COajBHywiz;
      if(ElzsRcVmbH == VCfBDrPjtz){RPqTWQtnwT = true;}
      else if(VCfBDrPjtz == ElzsRcVmbH){MEIRGKOabL = true;}
      if(NciuFEodfO == mOaPkQljnB){MVjwexZFNO = true;}
      else if(mOaPkQljnB == NciuFEodfO){HnABLDtwzP = true;}
      if(NgTaKVYSbF == ZuwmNPDTfK){KozzZuwbxo = true;}
      else if(ZuwmNPDTfK == NgTaKVYSbF){LnFYKoNdXo = true;}
      if(lBHYoFHKcC == VIJhwIHOXo){XRAJZrzCbF = true;}
      else if(VIJhwIHOXo == lBHYoFHKcC){lHxeeLIGmw = true;}
      if(cByPbrLlCA == ECfMdWHLwg){VgTYHgeeED = true;}
      else if(ECfMdWHLwg == cByPbrLlCA){PIEIonHGmf = true;}
      if(WRNfMWSYhu == nGmspaFrmm){hsiUobPrtb = true;}
      else if(nGmspaFrmm == WRNfMWSYhu){JtNNBXziGQ = true;}
      if(ECKWVMVJFA == nwEjdeFrTc){URpGutUZWm = true;}
      else if(nwEjdeFrTc == ECKWVMVJFA){xkDlZAqVWz = true;}
      if(xeBdkMiDyR == JWMywWOjIq){xWdHrcUaqr = true;}
      if(KmQahUmaMR == HqWyWPUQrU){QQXtHeifUx = true;}
      if(lhbgxZpatP == COajBHywiz){cHIzjDqNdM = true;}
      while(JWMywWOjIq == xeBdkMiDyR){unIDzDjwjW = true;}
      while(HqWyWPUQrU == HqWyWPUQrU){hGqqfqsicH = true;}
      while(COajBHywiz == COajBHywiz){MYzWyeERio = true;}
      if(RPqTWQtnwT == true){RPqTWQtnwT = false;}
      if(MVjwexZFNO == true){MVjwexZFNO = false;}
      if(KozzZuwbxo == true){KozzZuwbxo = false;}
      if(XRAJZrzCbF == true){XRAJZrzCbF = false;}
      if(VgTYHgeeED == true){VgTYHgeeED = false;}
      if(hsiUobPrtb == true){hsiUobPrtb = false;}
      if(URpGutUZWm == true){URpGutUZWm = false;}
      if(xWdHrcUaqr == true){xWdHrcUaqr = false;}
      if(QQXtHeifUx == true){QQXtHeifUx = false;}
      if(cHIzjDqNdM == true){cHIzjDqNdM = false;}
      if(MEIRGKOabL == true){MEIRGKOabL = false;}
      if(HnABLDtwzP == true){HnABLDtwzP = false;}
      if(LnFYKoNdXo == true){LnFYKoNdXo = false;}
      if(lHxeeLIGmw == true){lHxeeLIGmw = false;}
      if(PIEIonHGmf == true){PIEIonHGmf = false;}
      if(JtNNBXziGQ == true){JtNNBXziGQ = false;}
      if(xkDlZAqVWz == true){xkDlZAqVWz = false;}
      if(unIDzDjwjW == true){unIDzDjwjW = false;}
      if(hGqqfqsicH == true){hGqqfqsicH = false;}
      if(MYzWyeERio == true){MYzWyeERio = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBOKOCHZVW
{ 
  void FlEorPMCJj()
  { 
      bool jbHmqccuVl = false;
      bool uGdIwRrosQ = false;
      bool qqSduwjqwS = false;
      bool pwwsTsBFjP = false;
      bool pjEnzkaAaU = false;
      bool WjhqSsJcru = false;
      bool slyDuyKjoD = false;
      bool QlFdZGmddJ = false;
      bool VjPbwGOFaa = false;
      bool jXMoWEkAsB = false;
      bool apKXDjeERL = false;
      bool FeyiYJVWHo = false;
      bool iEJNTrYQHU = false;
      bool UlkcheYrXL = false;
      bool bJnOUEYdPM = false;
      bool iOsERVfxEL = false;
      bool KNwwpStVAs = false;
      bool kcyuNZQtsO = false;
      bool SuBtlGsgKL = false;
      bool ybnMBNMqYB = false;
      string xEoxQMThXq;
      string EalYPcnMgq;
      string FhrglLSOhA;
      string BTUxcKxeYc;
      string pwxbuOxNYl;
      string XtpCGPLHKF;
      string sFzXokFnwF;
      string eInDAJjPlW;
      string NEpubHcRpM;
      string ypTSikwZlJ;
      string IJRTGOGlCx;
      string fwUmqoODuh;
      string HnxjGooUUP;
      string MJdbOEmVoM;
      string AqOsfCUfas;
      string VrdDCTLhMR;
      string ZlQmkWRrYm;
      string BsOigQYEDE;
      string UIsasTeZZt;
      string rFIXlOZbHJ;
      if(xEoxQMThXq == IJRTGOGlCx){jbHmqccuVl = true;}
      else if(IJRTGOGlCx == xEoxQMThXq){apKXDjeERL = true;}
      if(EalYPcnMgq == fwUmqoODuh){uGdIwRrosQ = true;}
      else if(fwUmqoODuh == EalYPcnMgq){FeyiYJVWHo = true;}
      if(FhrglLSOhA == HnxjGooUUP){qqSduwjqwS = true;}
      else if(HnxjGooUUP == FhrglLSOhA){iEJNTrYQHU = true;}
      if(BTUxcKxeYc == MJdbOEmVoM){pwwsTsBFjP = true;}
      else if(MJdbOEmVoM == BTUxcKxeYc){UlkcheYrXL = true;}
      if(pwxbuOxNYl == AqOsfCUfas){pjEnzkaAaU = true;}
      else if(AqOsfCUfas == pwxbuOxNYl){bJnOUEYdPM = true;}
      if(XtpCGPLHKF == VrdDCTLhMR){WjhqSsJcru = true;}
      else if(VrdDCTLhMR == XtpCGPLHKF){iOsERVfxEL = true;}
      if(sFzXokFnwF == ZlQmkWRrYm){slyDuyKjoD = true;}
      else if(ZlQmkWRrYm == sFzXokFnwF){KNwwpStVAs = true;}
      if(eInDAJjPlW == BsOigQYEDE){QlFdZGmddJ = true;}
      if(NEpubHcRpM == UIsasTeZZt){VjPbwGOFaa = true;}
      if(ypTSikwZlJ == rFIXlOZbHJ){jXMoWEkAsB = true;}
      while(BsOigQYEDE == eInDAJjPlW){kcyuNZQtsO = true;}
      while(UIsasTeZZt == UIsasTeZZt){SuBtlGsgKL = true;}
      while(rFIXlOZbHJ == rFIXlOZbHJ){ybnMBNMqYB = true;}
      if(jbHmqccuVl == true){jbHmqccuVl = false;}
      if(uGdIwRrosQ == true){uGdIwRrosQ = false;}
      if(qqSduwjqwS == true){qqSduwjqwS = false;}
      if(pwwsTsBFjP == true){pwwsTsBFjP = false;}
      if(pjEnzkaAaU == true){pjEnzkaAaU = false;}
      if(WjhqSsJcru == true){WjhqSsJcru = false;}
      if(slyDuyKjoD == true){slyDuyKjoD = false;}
      if(QlFdZGmddJ == true){QlFdZGmddJ = false;}
      if(VjPbwGOFaa == true){VjPbwGOFaa = false;}
      if(jXMoWEkAsB == true){jXMoWEkAsB = false;}
      if(apKXDjeERL == true){apKXDjeERL = false;}
      if(FeyiYJVWHo == true){FeyiYJVWHo = false;}
      if(iEJNTrYQHU == true){iEJNTrYQHU = false;}
      if(UlkcheYrXL == true){UlkcheYrXL = false;}
      if(bJnOUEYdPM == true){bJnOUEYdPM = false;}
      if(iOsERVfxEL == true){iOsERVfxEL = false;}
      if(KNwwpStVAs == true){KNwwpStVAs = false;}
      if(kcyuNZQtsO == true){kcyuNZQtsO = false;}
      if(SuBtlGsgKL == true){SuBtlGsgKL = false;}
      if(ybnMBNMqYB == true){ybnMBNMqYB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGHZOHFIOZ
{ 
  void ulWITETBqP()
  { 
      bool xYpGDmUHZg = false;
      bool KqCwrIrkzI = false;
      bool RHAMtRiaxZ = false;
      bool iRoPAitPRH = false;
      bool iTiMGAzpsj = false;
      bool rCfKYoYdLk = false;
      bool EtJzxrCluJ = false;
      bool ObTqZxYmFs = false;
      bool RrhNhfldqL = false;
      bool JQDfCnKjOO = false;
      bool yMtiVPinka = false;
      bool PkXRSLMwRR = false;
      bool FXujzxYnok = false;
      bool moYquEyyqR = false;
      bool xxsQwYskMp = false;
      bool bORxIZRKjX = false;
      bool qtzznaMfWN = false;
      bool NNEATIdema = false;
      bool EmayIXWaiU = false;
      bool mmNTZDxtbU = false;
      string LZUnBqakXi;
      string xjQQOMFalW;
      string MqXFgnCiYJ;
      string ulnyWbadlq;
      string FspiibHrsM;
      string YSrPSTBPHM;
      string orLNmLwSsl;
      string lantQTBoWE;
      string gJoMjcsXeC;
      string ZLWYCMgbuX;
      string fnzGaxdyyz;
      string SLrCfeDzdK;
      string SXnpMZEPrE;
      string lZtyYrKhll;
      string ztZfjOSTsW;
      string JhykEIAItA;
      string sOGtMsRtdm;
      string TVMqKXxIGx;
      string HjVUtEaJsQ;
      string rCmlsknfSp;
      if(LZUnBqakXi == fnzGaxdyyz){xYpGDmUHZg = true;}
      else if(fnzGaxdyyz == LZUnBqakXi){yMtiVPinka = true;}
      if(xjQQOMFalW == SLrCfeDzdK){KqCwrIrkzI = true;}
      else if(SLrCfeDzdK == xjQQOMFalW){PkXRSLMwRR = true;}
      if(MqXFgnCiYJ == SXnpMZEPrE){RHAMtRiaxZ = true;}
      else if(SXnpMZEPrE == MqXFgnCiYJ){FXujzxYnok = true;}
      if(ulnyWbadlq == lZtyYrKhll){iRoPAitPRH = true;}
      else if(lZtyYrKhll == ulnyWbadlq){moYquEyyqR = true;}
      if(FspiibHrsM == ztZfjOSTsW){iTiMGAzpsj = true;}
      else if(ztZfjOSTsW == FspiibHrsM){xxsQwYskMp = true;}
      if(YSrPSTBPHM == JhykEIAItA){rCfKYoYdLk = true;}
      else if(JhykEIAItA == YSrPSTBPHM){bORxIZRKjX = true;}
      if(orLNmLwSsl == sOGtMsRtdm){EtJzxrCluJ = true;}
      else if(sOGtMsRtdm == orLNmLwSsl){qtzznaMfWN = true;}
      if(lantQTBoWE == TVMqKXxIGx){ObTqZxYmFs = true;}
      if(gJoMjcsXeC == HjVUtEaJsQ){RrhNhfldqL = true;}
      if(ZLWYCMgbuX == rCmlsknfSp){JQDfCnKjOO = true;}
      while(TVMqKXxIGx == lantQTBoWE){NNEATIdema = true;}
      while(HjVUtEaJsQ == HjVUtEaJsQ){EmayIXWaiU = true;}
      while(rCmlsknfSp == rCmlsknfSp){mmNTZDxtbU = true;}
      if(xYpGDmUHZg == true){xYpGDmUHZg = false;}
      if(KqCwrIrkzI == true){KqCwrIrkzI = false;}
      if(RHAMtRiaxZ == true){RHAMtRiaxZ = false;}
      if(iRoPAitPRH == true){iRoPAitPRH = false;}
      if(iTiMGAzpsj == true){iTiMGAzpsj = false;}
      if(rCfKYoYdLk == true){rCfKYoYdLk = false;}
      if(EtJzxrCluJ == true){EtJzxrCluJ = false;}
      if(ObTqZxYmFs == true){ObTqZxYmFs = false;}
      if(RrhNhfldqL == true){RrhNhfldqL = false;}
      if(JQDfCnKjOO == true){JQDfCnKjOO = false;}
      if(yMtiVPinka == true){yMtiVPinka = false;}
      if(PkXRSLMwRR == true){PkXRSLMwRR = false;}
      if(FXujzxYnok == true){FXujzxYnok = false;}
      if(moYquEyyqR == true){moYquEyyqR = false;}
      if(xxsQwYskMp == true){xxsQwYskMp = false;}
      if(bORxIZRKjX == true){bORxIZRKjX = false;}
      if(qtzznaMfWN == true){qtzznaMfWN = false;}
      if(NNEATIdema == true){NNEATIdema = false;}
      if(EmayIXWaiU == true){EmayIXWaiU = false;}
      if(mmNTZDxtbU == true){mmNTZDxtbU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQXXNTANDV
{ 
  void KaitnyeDMI()
  { 
      bool CBflxXNLQP = false;
      bool yDhmhUtlIO = false;
      bool TnJdXEeAUP = false;
      bool HpXmGSlEmN = false;
      bool LQVIxdsuAI = false;
      bool UYllYNqCOr = false;
      bool rMqAIIfugO = false;
      bool ipzuCDSBfs = false;
      bool LjALuhDkNr = false;
      bool aiouUyYUzo = false;
      bool yyNkZdZqiV = false;
      bool toWUfIMeFZ = false;
      bool FtgnnzAEZE = false;
      bool dxBpuMVOlQ = false;
      bool ILCqykMUOM = false;
      bool ktPYjDQZxa = false;
      bool dUQerwnfZS = false;
      bool lxsnRsropC = false;
      bool lfpNSihbGr = false;
      bool wwRLlmuWzB = false;
      string YDhpVkahTg;
      string eIMKeoCPzj;
      string LdkxoEuUZb;
      string fLYySFKOYn;
      string iYRbEwEYHj;
      string zLtRyuSjAQ;
      string pFIrASiNqY;
      string emqKAmMJss;
      string AVMocURHAX;
      string maNHxdPZak;
      string MpghFLUiQL;
      string iJpHPUrSOe;
      string BbNTlDYiMW;
      string WlhIgKnejQ;
      string AhponcjGrc;
      string kxKuijbMwB;
      string mkVtnwahZF;
      string fNiyeTlYeI;
      string TRqjkZblYw;
      string hahhdOLuAr;
      if(YDhpVkahTg == MpghFLUiQL){CBflxXNLQP = true;}
      else if(MpghFLUiQL == YDhpVkahTg){yyNkZdZqiV = true;}
      if(eIMKeoCPzj == iJpHPUrSOe){yDhmhUtlIO = true;}
      else if(iJpHPUrSOe == eIMKeoCPzj){toWUfIMeFZ = true;}
      if(LdkxoEuUZb == BbNTlDYiMW){TnJdXEeAUP = true;}
      else if(BbNTlDYiMW == LdkxoEuUZb){FtgnnzAEZE = true;}
      if(fLYySFKOYn == WlhIgKnejQ){HpXmGSlEmN = true;}
      else if(WlhIgKnejQ == fLYySFKOYn){dxBpuMVOlQ = true;}
      if(iYRbEwEYHj == AhponcjGrc){LQVIxdsuAI = true;}
      else if(AhponcjGrc == iYRbEwEYHj){ILCqykMUOM = true;}
      if(zLtRyuSjAQ == kxKuijbMwB){UYllYNqCOr = true;}
      else if(kxKuijbMwB == zLtRyuSjAQ){ktPYjDQZxa = true;}
      if(pFIrASiNqY == mkVtnwahZF){rMqAIIfugO = true;}
      else if(mkVtnwahZF == pFIrASiNqY){dUQerwnfZS = true;}
      if(emqKAmMJss == fNiyeTlYeI){ipzuCDSBfs = true;}
      if(AVMocURHAX == TRqjkZblYw){LjALuhDkNr = true;}
      if(maNHxdPZak == hahhdOLuAr){aiouUyYUzo = true;}
      while(fNiyeTlYeI == emqKAmMJss){lxsnRsropC = true;}
      while(TRqjkZblYw == TRqjkZblYw){lfpNSihbGr = true;}
      while(hahhdOLuAr == hahhdOLuAr){wwRLlmuWzB = true;}
      if(CBflxXNLQP == true){CBflxXNLQP = false;}
      if(yDhmhUtlIO == true){yDhmhUtlIO = false;}
      if(TnJdXEeAUP == true){TnJdXEeAUP = false;}
      if(HpXmGSlEmN == true){HpXmGSlEmN = false;}
      if(LQVIxdsuAI == true){LQVIxdsuAI = false;}
      if(UYllYNqCOr == true){UYllYNqCOr = false;}
      if(rMqAIIfugO == true){rMqAIIfugO = false;}
      if(ipzuCDSBfs == true){ipzuCDSBfs = false;}
      if(LjALuhDkNr == true){LjALuhDkNr = false;}
      if(aiouUyYUzo == true){aiouUyYUzo = false;}
      if(yyNkZdZqiV == true){yyNkZdZqiV = false;}
      if(toWUfIMeFZ == true){toWUfIMeFZ = false;}
      if(FtgnnzAEZE == true){FtgnnzAEZE = false;}
      if(dxBpuMVOlQ == true){dxBpuMVOlQ = false;}
      if(ILCqykMUOM == true){ILCqykMUOM = false;}
      if(ktPYjDQZxa == true){ktPYjDQZxa = false;}
      if(dUQerwnfZS == true){dUQerwnfZS = false;}
      if(lxsnRsropC == true){lxsnRsropC = false;}
      if(lfpNSihbGr == true){lfpNSihbGr = false;}
      if(wwRLlmuWzB == true){wwRLlmuWzB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWQFONDQKR
{ 
  void dezOJiNgOM()
  { 
      bool mIcxkEOIll = false;
      bool adtLJufVTo = false;
      bool fJlplrgpDS = false;
      bool INQCRkqgey = false;
      bool SyqVeXbXqj = false;
      bool PHdTPcVmKs = false;
      bool XXFSdNMqsX = false;
      bool DzpUWgRQKO = false;
      bool PIzSDBixmo = false;
      bool PEVkatsYqR = false;
      bool KjdTfQQJxh = false;
      bool LEbwcOYlPc = false;
      bool dPEEHzcFtb = false;
      bool nsZsEfeelm = false;
      bool jZzEcLbZIM = false;
      bool UGIOmtfZLg = false;
      bool mKOUtRdirx = false;
      bool jtAbrEPAaw = false;
      bool WDxhGgjLFJ = false;
      bool zETFAYKdKL = false;
      string rxRRAscbHz;
      string aHEnrdPnqz;
      string ugZoUkYSbV;
      string yKNAhREJtx;
      string sDJWmKQhWY;
      string PTuzFKWbxO;
      string UKzkAPsDGa;
      string YGtsGrXCCJ;
      string TquDFePNuW;
      string tbMeciDXWW;
      string RNbwzJYBsN;
      string mTZmtcOwfU;
      string zeIifwsOPW;
      string ozfeqGOzEw;
      string FOThjaCYkz;
      string TGrBXlEsQD;
      string PJlWXmntun;
      string OPriOkLayE;
      string sUdPChHdHF;
      string BViBfucxJw;
      if(rxRRAscbHz == RNbwzJYBsN){mIcxkEOIll = true;}
      else if(RNbwzJYBsN == rxRRAscbHz){KjdTfQQJxh = true;}
      if(aHEnrdPnqz == mTZmtcOwfU){adtLJufVTo = true;}
      else if(mTZmtcOwfU == aHEnrdPnqz){LEbwcOYlPc = true;}
      if(ugZoUkYSbV == zeIifwsOPW){fJlplrgpDS = true;}
      else if(zeIifwsOPW == ugZoUkYSbV){dPEEHzcFtb = true;}
      if(yKNAhREJtx == ozfeqGOzEw){INQCRkqgey = true;}
      else if(ozfeqGOzEw == yKNAhREJtx){nsZsEfeelm = true;}
      if(sDJWmKQhWY == FOThjaCYkz){SyqVeXbXqj = true;}
      else if(FOThjaCYkz == sDJWmKQhWY){jZzEcLbZIM = true;}
      if(PTuzFKWbxO == TGrBXlEsQD){PHdTPcVmKs = true;}
      else if(TGrBXlEsQD == PTuzFKWbxO){UGIOmtfZLg = true;}
      if(UKzkAPsDGa == PJlWXmntun){XXFSdNMqsX = true;}
      else if(PJlWXmntun == UKzkAPsDGa){mKOUtRdirx = true;}
      if(YGtsGrXCCJ == OPriOkLayE){DzpUWgRQKO = true;}
      if(TquDFePNuW == sUdPChHdHF){PIzSDBixmo = true;}
      if(tbMeciDXWW == BViBfucxJw){PEVkatsYqR = true;}
      while(OPriOkLayE == YGtsGrXCCJ){jtAbrEPAaw = true;}
      while(sUdPChHdHF == sUdPChHdHF){WDxhGgjLFJ = true;}
      while(BViBfucxJw == BViBfucxJw){zETFAYKdKL = true;}
      if(mIcxkEOIll == true){mIcxkEOIll = false;}
      if(adtLJufVTo == true){adtLJufVTo = false;}
      if(fJlplrgpDS == true){fJlplrgpDS = false;}
      if(INQCRkqgey == true){INQCRkqgey = false;}
      if(SyqVeXbXqj == true){SyqVeXbXqj = false;}
      if(PHdTPcVmKs == true){PHdTPcVmKs = false;}
      if(XXFSdNMqsX == true){XXFSdNMqsX = false;}
      if(DzpUWgRQKO == true){DzpUWgRQKO = false;}
      if(PIzSDBixmo == true){PIzSDBixmo = false;}
      if(PEVkatsYqR == true){PEVkatsYqR = false;}
      if(KjdTfQQJxh == true){KjdTfQQJxh = false;}
      if(LEbwcOYlPc == true){LEbwcOYlPc = false;}
      if(dPEEHzcFtb == true){dPEEHzcFtb = false;}
      if(nsZsEfeelm == true){nsZsEfeelm = false;}
      if(jZzEcLbZIM == true){jZzEcLbZIM = false;}
      if(UGIOmtfZLg == true){UGIOmtfZLg = false;}
      if(mKOUtRdirx == true){mKOUtRdirx = false;}
      if(jtAbrEPAaw == true){jtAbrEPAaw = false;}
      if(WDxhGgjLFJ == true){WDxhGgjLFJ = false;}
      if(zETFAYKdKL == true){zETFAYKdKL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTHEVCHXII
{ 
  void NrABqlFDZD()
  { 
      bool olIVxGyJgY = false;
      bool zYYmCdHjiE = false;
      bool LnuhnyOyjR = false;
      bool LnlslexKwx = false;
      bool ksjzlAetzx = false;
      bool lEKakBpZgy = false;
      bool qAZOMKmfBX = false;
      bool gwmkTREuwm = false;
      bool TUylfHdLIk = false;
      bool nXcxGkTUma = false;
      bool NzraQoQZHT = false;
      bool wtdseVBmhF = false;
      bool gbWPjJTodh = false;
      bool xiIVZUbWVp = false;
      bool pEDnnssiSk = false;
      bool ifmgskbbqG = false;
      bool VbwYVMlHTJ = false;
      bool sdRqPcXibp = false;
      bool PjVrzRwbbn = false;
      bool szfOUOIeSa = false;
      string gUsAQQToBE;
      string jHoSxbPUtS;
      string MVLmysJwDx;
      string YbTPNReRmd;
      string RHAQyiBWPn;
      string QlmtaLIGCX;
      string HXlEeHmZEe;
      string wygPAEVtnO;
      string rlfOfloZoC;
      string IYPPVtVukq;
      string uaSjrSFWsV;
      string oORmeVqWYs;
      string RNjCVXhQsG;
      string hZIxTQTuWM;
      string gRfSMtGbjz;
      string CyVrYhpPOT;
      string jndmnPFUTO;
      string CwAMLAhRpa;
      string QFgsEiDQYk;
      string ZDgCbsnsew;
      if(gUsAQQToBE == uaSjrSFWsV){olIVxGyJgY = true;}
      else if(uaSjrSFWsV == gUsAQQToBE){NzraQoQZHT = true;}
      if(jHoSxbPUtS == oORmeVqWYs){zYYmCdHjiE = true;}
      else if(oORmeVqWYs == jHoSxbPUtS){wtdseVBmhF = true;}
      if(MVLmysJwDx == RNjCVXhQsG){LnuhnyOyjR = true;}
      else if(RNjCVXhQsG == MVLmysJwDx){gbWPjJTodh = true;}
      if(YbTPNReRmd == hZIxTQTuWM){LnlslexKwx = true;}
      else if(hZIxTQTuWM == YbTPNReRmd){xiIVZUbWVp = true;}
      if(RHAQyiBWPn == gRfSMtGbjz){ksjzlAetzx = true;}
      else if(gRfSMtGbjz == RHAQyiBWPn){pEDnnssiSk = true;}
      if(QlmtaLIGCX == CyVrYhpPOT){lEKakBpZgy = true;}
      else if(CyVrYhpPOT == QlmtaLIGCX){ifmgskbbqG = true;}
      if(HXlEeHmZEe == jndmnPFUTO){qAZOMKmfBX = true;}
      else if(jndmnPFUTO == HXlEeHmZEe){VbwYVMlHTJ = true;}
      if(wygPAEVtnO == CwAMLAhRpa){gwmkTREuwm = true;}
      if(rlfOfloZoC == QFgsEiDQYk){TUylfHdLIk = true;}
      if(IYPPVtVukq == ZDgCbsnsew){nXcxGkTUma = true;}
      while(CwAMLAhRpa == wygPAEVtnO){sdRqPcXibp = true;}
      while(QFgsEiDQYk == QFgsEiDQYk){PjVrzRwbbn = true;}
      while(ZDgCbsnsew == ZDgCbsnsew){szfOUOIeSa = true;}
      if(olIVxGyJgY == true){olIVxGyJgY = false;}
      if(zYYmCdHjiE == true){zYYmCdHjiE = false;}
      if(LnuhnyOyjR == true){LnuhnyOyjR = false;}
      if(LnlslexKwx == true){LnlslexKwx = false;}
      if(ksjzlAetzx == true){ksjzlAetzx = false;}
      if(lEKakBpZgy == true){lEKakBpZgy = false;}
      if(qAZOMKmfBX == true){qAZOMKmfBX = false;}
      if(gwmkTREuwm == true){gwmkTREuwm = false;}
      if(TUylfHdLIk == true){TUylfHdLIk = false;}
      if(nXcxGkTUma == true){nXcxGkTUma = false;}
      if(NzraQoQZHT == true){NzraQoQZHT = false;}
      if(wtdseVBmhF == true){wtdseVBmhF = false;}
      if(gbWPjJTodh == true){gbWPjJTodh = false;}
      if(xiIVZUbWVp == true){xiIVZUbWVp = false;}
      if(pEDnnssiSk == true){pEDnnssiSk = false;}
      if(ifmgskbbqG == true){ifmgskbbqG = false;}
      if(VbwYVMlHTJ == true){VbwYVMlHTJ = false;}
      if(sdRqPcXibp == true){sdRqPcXibp = false;}
      if(PjVrzRwbbn == true){PjVrzRwbbn = false;}
      if(szfOUOIeSa == true){szfOUOIeSa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WRLICMURKA
{ 
  void usuiGMnqnh()
  { 
      bool PyZtewuSxx = false;
      bool CaTeXUYyJk = false;
      bool fXnmzSQFjC = false;
      bool KAyJMhjroT = false;
      bool mffpnbZkAI = false;
      bool lAsYtqJmtM = false;
      bool eoiulBbKSp = false;
      bool jgJoxzrxzW = false;
      bool rfFbPKHZOU = false;
      bool XxxcoxxjEl = false;
      bool APSJXFqDau = false;
      bool yLmXTyjGfb = false;
      bool tCuxSmifAz = false;
      bool BIsMVbMuEJ = false;
      bool SEzTWLJZIp = false;
      bool NpEcqyUVpj = false;
      bool VKCaspSZBr = false;
      bool lnCVIpDaZH = false;
      bool dJWKlKEQUX = false;
      bool GqFTnIBXag = false;
      string DYwkOkBJNj;
      string SFNStNayNh;
      string SIrqgTmZLp;
      string fqjVLqEhfz;
      string HdZDLDMyDV;
      string nNsqPtgEDu;
      string yaxXEaVqGD;
      string IsSNZninfd;
      string GnWpCRyrFR;
      string JAdjBgfCyj;
      string hUqAMttfRb;
      string LrYZnJDHVl;
      string cclosIOhMr;
      string HfpuulwWcH;
      string XSadFRbEwq;
      string cYgMHEiCGE;
      string eLSYTeCcdC;
      string MgdNOKCIib;
      string gKlUPhzdnp;
      string DtPXcLzCJZ;
      if(DYwkOkBJNj == hUqAMttfRb){PyZtewuSxx = true;}
      else if(hUqAMttfRb == DYwkOkBJNj){APSJXFqDau = true;}
      if(SFNStNayNh == LrYZnJDHVl){CaTeXUYyJk = true;}
      else if(LrYZnJDHVl == SFNStNayNh){yLmXTyjGfb = true;}
      if(SIrqgTmZLp == cclosIOhMr){fXnmzSQFjC = true;}
      else if(cclosIOhMr == SIrqgTmZLp){tCuxSmifAz = true;}
      if(fqjVLqEhfz == HfpuulwWcH){KAyJMhjroT = true;}
      else if(HfpuulwWcH == fqjVLqEhfz){BIsMVbMuEJ = true;}
      if(HdZDLDMyDV == XSadFRbEwq){mffpnbZkAI = true;}
      else if(XSadFRbEwq == HdZDLDMyDV){SEzTWLJZIp = true;}
      if(nNsqPtgEDu == cYgMHEiCGE){lAsYtqJmtM = true;}
      else if(cYgMHEiCGE == nNsqPtgEDu){NpEcqyUVpj = true;}
      if(yaxXEaVqGD == eLSYTeCcdC){eoiulBbKSp = true;}
      else if(eLSYTeCcdC == yaxXEaVqGD){VKCaspSZBr = true;}
      if(IsSNZninfd == MgdNOKCIib){jgJoxzrxzW = true;}
      if(GnWpCRyrFR == gKlUPhzdnp){rfFbPKHZOU = true;}
      if(JAdjBgfCyj == DtPXcLzCJZ){XxxcoxxjEl = true;}
      while(MgdNOKCIib == IsSNZninfd){lnCVIpDaZH = true;}
      while(gKlUPhzdnp == gKlUPhzdnp){dJWKlKEQUX = true;}
      while(DtPXcLzCJZ == DtPXcLzCJZ){GqFTnIBXag = true;}
      if(PyZtewuSxx == true){PyZtewuSxx = false;}
      if(CaTeXUYyJk == true){CaTeXUYyJk = false;}
      if(fXnmzSQFjC == true){fXnmzSQFjC = false;}
      if(KAyJMhjroT == true){KAyJMhjroT = false;}
      if(mffpnbZkAI == true){mffpnbZkAI = false;}
      if(lAsYtqJmtM == true){lAsYtqJmtM = false;}
      if(eoiulBbKSp == true){eoiulBbKSp = false;}
      if(jgJoxzrxzW == true){jgJoxzrxzW = false;}
      if(rfFbPKHZOU == true){rfFbPKHZOU = false;}
      if(XxxcoxxjEl == true){XxxcoxxjEl = false;}
      if(APSJXFqDau == true){APSJXFqDau = false;}
      if(yLmXTyjGfb == true){yLmXTyjGfb = false;}
      if(tCuxSmifAz == true){tCuxSmifAz = false;}
      if(BIsMVbMuEJ == true){BIsMVbMuEJ = false;}
      if(SEzTWLJZIp == true){SEzTWLJZIp = false;}
      if(NpEcqyUVpj == true){NpEcqyUVpj = false;}
      if(VKCaspSZBr == true){VKCaspSZBr = false;}
      if(lnCVIpDaZH == true){lnCVIpDaZH = false;}
      if(dJWKlKEQUX == true){dJWKlKEQUX = false;}
      if(GqFTnIBXag == true){GqFTnIBXag = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KZMGGFLKZI
{ 
  void jzLePgyNrV()
  { 
      bool kfCXZhqoDo = false;
      bool rQTlCheCog = false;
      bool kqfecMrcua = false;
      bool TARJjoTIJW = false;
      bool KSihwhmfAE = false;
      bool HerGBsAWuN = false;
      bool oOscVryJCM = false;
      bool NWsRWRIxiu = false;
      bool YMbqSnHKIp = false;
      bool owNuhuZGME = false;
      bool jddmpklaji = false;
      bool kCnznbmBJg = false;
      bool jmBLXRIxia = false;
      bool rBkeKuinBg = false;
      bool CgaYFmINGG = false;
      bool IXxeTwbRPY = false;
      bool bnqJqjRJns = false;
      bool ryAbeCMbFk = false;
      bool IupcRUDGKO = false;
      bool SQXcENpQhU = false;
      string zmZMLGKFLU;
      string IXFxJBBGGP;
      string wtRiXlxDrt;
      string QHqtMVsyYs;
      string lrPhKTNehl;
      string DZaVNFUpoY;
      string JHNRDAgLkm;
      string IDhMcEejXD;
      string YRUFqqgVgH;
      string BCIAjeeydJ;
      string mCttdzrNrI;
      string akRkzqlHZM;
      string TLedlFtgby;
      string ZfFNQWXabq;
      string yScXgQjXAs;
      string sWXRpbXQIX;
      string FLktiteDUc;
      string SLfhNAiGwV;
      string VWfiFCImXo;
      string zGSDlmghnm;
      if(zmZMLGKFLU == mCttdzrNrI){kfCXZhqoDo = true;}
      else if(mCttdzrNrI == zmZMLGKFLU){jddmpklaji = true;}
      if(IXFxJBBGGP == akRkzqlHZM){rQTlCheCog = true;}
      else if(akRkzqlHZM == IXFxJBBGGP){kCnznbmBJg = true;}
      if(wtRiXlxDrt == TLedlFtgby){kqfecMrcua = true;}
      else if(TLedlFtgby == wtRiXlxDrt){jmBLXRIxia = true;}
      if(QHqtMVsyYs == ZfFNQWXabq){TARJjoTIJW = true;}
      else if(ZfFNQWXabq == QHqtMVsyYs){rBkeKuinBg = true;}
      if(lrPhKTNehl == yScXgQjXAs){KSihwhmfAE = true;}
      else if(yScXgQjXAs == lrPhKTNehl){CgaYFmINGG = true;}
      if(DZaVNFUpoY == sWXRpbXQIX){HerGBsAWuN = true;}
      else if(sWXRpbXQIX == DZaVNFUpoY){IXxeTwbRPY = true;}
      if(JHNRDAgLkm == FLktiteDUc){oOscVryJCM = true;}
      else if(FLktiteDUc == JHNRDAgLkm){bnqJqjRJns = true;}
      if(IDhMcEejXD == SLfhNAiGwV){NWsRWRIxiu = true;}
      if(YRUFqqgVgH == VWfiFCImXo){YMbqSnHKIp = true;}
      if(BCIAjeeydJ == zGSDlmghnm){owNuhuZGME = true;}
      while(SLfhNAiGwV == IDhMcEejXD){ryAbeCMbFk = true;}
      while(VWfiFCImXo == VWfiFCImXo){IupcRUDGKO = true;}
      while(zGSDlmghnm == zGSDlmghnm){SQXcENpQhU = true;}
      if(kfCXZhqoDo == true){kfCXZhqoDo = false;}
      if(rQTlCheCog == true){rQTlCheCog = false;}
      if(kqfecMrcua == true){kqfecMrcua = false;}
      if(TARJjoTIJW == true){TARJjoTIJW = false;}
      if(KSihwhmfAE == true){KSihwhmfAE = false;}
      if(HerGBsAWuN == true){HerGBsAWuN = false;}
      if(oOscVryJCM == true){oOscVryJCM = false;}
      if(NWsRWRIxiu == true){NWsRWRIxiu = false;}
      if(YMbqSnHKIp == true){YMbqSnHKIp = false;}
      if(owNuhuZGME == true){owNuhuZGME = false;}
      if(jddmpklaji == true){jddmpklaji = false;}
      if(kCnznbmBJg == true){kCnznbmBJg = false;}
      if(jmBLXRIxia == true){jmBLXRIxia = false;}
      if(rBkeKuinBg == true){rBkeKuinBg = false;}
      if(CgaYFmINGG == true){CgaYFmINGG = false;}
      if(IXxeTwbRPY == true){IXxeTwbRPY = false;}
      if(bnqJqjRJns == true){bnqJqjRJns = false;}
      if(ryAbeCMbFk == true){ryAbeCMbFk = false;}
      if(IupcRUDGKO == true){IupcRUDGKO = false;}
      if(SQXcENpQhU == true){SQXcENpQhU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBPOSNDGZM
{ 
  void DxjSrsOyOW()
  { 
      bool nFVyMnfzeu = false;
      bool QZsrHZGQuq = false;
      bool yHmAqpppMy = false;
      bool VZHiujCRLh = false;
      bool GHWZIoNfnm = false;
      bool mGYJtfRUHV = false;
      bool yplgYqSJxX = false;
      bool WoFNjpkNrC = false;
      bool cKCZKPAxnO = false;
      bool RhKojQVpBR = false;
      bool WDhQPyAKZD = false;
      bool uEbFsmnMVI = false;
      bool qUViFneQdT = false;
      bool UtMafZbkJM = false;
      bool PoXjSNFEuw = false;
      bool cIUraBhzLb = false;
      bool SjgFiBrBYT = false;
      bool LCCIsBxkPr = false;
      bool iZUhpLYTAd = false;
      bool qbZhteIRBQ = false;
      string cCJbGYbAks;
      string IlGOzoaxty;
      string XFJllncucY;
      string ZUWDFdExXe;
      string CTTAhHXFgk;
      string uRlpnWsWoR;
      string wfWMSnOCJU;
      string kcZPwDlIEd;
      string QXOrcIhgPi;
      string kgHFhVxHht;
      string sUuMASqVsj;
      string jkSLBYRdiJ;
      string FhmaiDUTga;
      string FeaJkwbBrK;
      string RLmeyzOwDJ;
      string ESXXnLgUcw;
      string yWoSdFKIaF;
      string xPlYrstHbj;
      string oYQXWmGCUZ;
      string OGYuMtWUAs;
      if(cCJbGYbAks == sUuMASqVsj){nFVyMnfzeu = true;}
      else if(sUuMASqVsj == cCJbGYbAks){WDhQPyAKZD = true;}
      if(IlGOzoaxty == jkSLBYRdiJ){QZsrHZGQuq = true;}
      else if(jkSLBYRdiJ == IlGOzoaxty){uEbFsmnMVI = true;}
      if(XFJllncucY == FhmaiDUTga){yHmAqpppMy = true;}
      else if(FhmaiDUTga == XFJllncucY){qUViFneQdT = true;}
      if(ZUWDFdExXe == FeaJkwbBrK){VZHiujCRLh = true;}
      else if(FeaJkwbBrK == ZUWDFdExXe){UtMafZbkJM = true;}
      if(CTTAhHXFgk == RLmeyzOwDJ){GHWZIoNfnm = true;}
      else if(RLmeyzOwDJ == CTTAhHXFgk){PoXjSNFEuw = true;}
      if(uRlpnWsWoR == ESXXnLgUcw){mGYJtfRUHV = true;}
      else if(ESXXnLgUcw == uRlpnWsWoR){cIUraBhzLb = true;}
      if(wfWMSnOCJU == yWoSdFKIaF){yplgYqSJxX = true;}
      else if(yWoSdFKIaF == wfWMSnOCJU){SjgFiBrBYT = true;}
      if(kcZPwDlIEd == xPlYrstHbj){WoFNjpkNrC = true;}
      if(QXOrcIhgPi == oYQXWmGCUZ){cKCZKPAxnO = true;}
      if(kgHFhVxHht == OGYuMtWUAs){RhKojQVpBR = true;}
      while(xPlYrstHbj == kcZPwDlIEd){LCCIsBxkPr = true;}
      while(oYQXWmGCUZ == oYQXWmGCUZ){iZUhpLYTAd = true;}
      while(OGYuMtWUAs == OGYuMtWUAs){qbZhteIRBQ = true;}
      if(nFVyMnfzeu == true){nFVyMnfzeu = false;}
      if(QZsrHZGQuq == true){QZsrHZGQuq = false;}
      if(yHmAqpppMy == true){yHmAqpppMy = false;}
      if(VZHiujCRLh == true){VZHiujCRLh = false;}
      if(GHWZIoNfnm == true){GHWZIoNfnm = false;}
      if(mGYJtfRUHV == true){mGYJtfRUHV = false;}
      if(yplgYqSJxX == true){yplgYqSJxX = false;}
      if(WoFNjpkNrC == true){WoFNjpkNrC = false;}
      if(cKCZKPAxnO == true){cKCZKPAxnO = false;}
      if(RhKojQVpBR == true){RhKojQVpBR = false;}
      if(WDhQPyAKZD == true){WDhQPyAKZD = false;}
      if(uEbFsmnMVI == true){uEbFsmnMVI = false;}
      if(qUViFneQdT == true){qUViFneQdT = false;}
      if(UtMafZbkJM == true){UtMafZbkJM = false;}
      if(PoXjSNFEuw == true){PoXjSNFEuw = false;}
      if(cIUraBhzLb == true){cIUraBhzLb = false;}
      if(SjgFiBrBYT == true){SjgFiBrBYT = false;}
      if(LCCIsBxkPr == true){LCCIsBxkPr = false;}
      if(iZUhpLYTAd == true){iZUhpLYTAd = false;}
      if(qbZhteIRBQ == true){qbZhteIRBQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DEDOXUEELP
{ 
  void RSUfGPnpKM()
  { 
      bool NzaxouYpAa = false;
      bool qJLKYKuIhb = false;
      bool dXNCntVPbz = false;
      bool ZBhkaPMkir = false;
      bool lpmwTLHRsd = false;
      bool wFdnOolYIu = false;
      bool ZJOBBoaajJ = false;
      bool yKZopnkQhb = false;
      bool mDVxDUXtVl = false;
      bool dmbnSbblud = false;
      bool jghifkfnxa = false;
      bool EUpgIVmRxf = false;
      bool RgExfKhlWN = false;
      bool MyUDqFUmQR = false;
      bool njwuhIwuew = false;
      bool oKnOMDbkDU = false;
      bool DtQjOFAloC = false;
      bool BAAfrhkJPX = false;
      bool OmGaYCJFqn = false;
      bool djiwOtSMfb = false;
      string eMGztGDaCu;
      string PlhoWpFPot;
      string jemnFNyjti;
      string tWAWCqdLck;
      string oZeDwmWMsA;
      string UGOLOzZRtf;
      string ISgSAslKmf;
      string LsmEFKAiqR;
      string qkqtOnHoHD;
      string QLQxbVsLDC;
      string BLZNnaTKFE;
      string yqacoXbmEL;
      string lwCiOAbpci;
      string QneoPeKcFm;
      string UwiDEZknHD;
      string tGHqQEIqzn;
      string ydhWmKLkMK;
      string NygQqoNzen;
      string OnhYnKfnXK;
      string VTcRoqOLQs;
      if(eMGztGDaCu == BLZNnaTKFE){NzaxouYpAa = true;}
      else if(BLZNnaTKFE == eMGztGDaCu){jghifkfnxa = true;}
      if(PlhoWpFPot == yqacoXbmEL){qJLKYKuIhb = true;}
      else if(yqacoXbmEL == PlhoWpFPot){EUpgIVmRxf = true;}
      if(jemnFNyjti == lwCiOAbpci){dXNCntVPbz = true;}
      else if(lwCiOAbpci == jemnFNyjti){RgExfKhlWN = true;}
      if(tWAWCqdLck == QneoPeKcFm){ZBhkaPMkir = true;}
      else if(QneoPeKcFm == tWAWCqdLck){MyUDqFUmQR = true;}
      if(oZeDwmWMsA == UwiDEZknHD){lpmwTLHRsd = true;}
      else if(UwiDEZknHD == oZeDwmWMsA){njwuhIwuew = true;}
      if(UGOLOzZRtf == tGHqQEIqzn){wFdnOolYIu = true;}
      else if(tGHqQEIqzn == UGOLOzZRtf){oKnOMDbkDU = true;}
      if(ISgSAslKmf == ydhWmKLkMK){ZJOBBoaajJ = true;}
      else if(ydhWmKLkMK == ISgSAslKmf){DtQjOFAloC = true;}
      if(LsmEFKAiqR == NygQqoNzen){yKZopnkQhb = true;}
      if(qkqtOnHoHD == OnhYnKfnXK){mDVxDUXtVl = true;}
      if(QLQxbVsLDC == VTcRoqOLQs){dmbnSbblud = true;}
      while(NygQqoNzen == LsmEFKAiqR){BAAfrhkJPX = true;}
      while(OnhYnKfnXK == OnhYnKfnXK){OmGaYCJFqn = true;}
      while(VTcRoqOLQs == VTcRoqOLQs){djiwOtSMfb = true;}
      if(NzaxouYpAa == true){NzaxouYpAa = false;}
      if(qJLKYKuIhb == true){qJLKYKuIhb = false;}
      if(dXNCntVPbz == true){dXNCntVPbz = false;}
      if(ZBhkaPMkir == true){ZBhkaPMkir = false;}
      if(lpmwTLHRsd == true){lpmwTLHRsd = false;}
      if(wFdnOolYIu == true){wFdnOolYIu = false;}
      if(ZJOBBoaajJ == true){ZJOBBoaajJ = false;}
      if(yKZopnkQhb == true){yKZopnkQhb = false;}
      if(mDVxDUXtVl == true){mDVxDUXtVl = false;}
      if(dmbnSbblud == true){dmbnSbblud = false;}
      if(jghifkfnxa == true){jghifkfnxa = false;}
      if(EUpgIVmRxf == true){EUpgIVmRxf = false;}
      if(RgExfKhlWN == true){RgExfKhlWN = false;}
      if(MyUDqFUmQR == true){MyUDqFUmQR = false;}
      if(njwuhIwuew == true){njwuhIwuew = false;}
      if(oKnOMDbkDU == true){oKnOMDbkDU = false;}
      if(DtQjOFAloC == true){DtQjOFAloC = false;}
      if(BAAfrhkJPX == true){BAAfrhkJPX = false;}
      if(OmGaYCJFqn == true){OmGaYCJFqn = false;}
      if(djiwOtSMfb == true){djiwOtSMfb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWNSGAFKQM
{ 
  void aNOMONiXXr()
  { 
      bool nLXjuLmliD = false;
      bool pNEkVjGRhX = false;
      bool iYliTDuHYm = false;
      bool IuaYQjzCnz = false;
      bool tCEjwGrMPo = false;
      bool QEBGyOYnPq = false;
      bool PfNwttleUl = false;
      bool kEchdgUCmN = false;
      bool LiqiWDsTaC = false;
      bool KKlxiNoIoB = false;
      bool UNqcEMbTcR = false;
      bool tWBCegndYq = false;
      bool BSESbZReyP = false;
      bool rMNkrxqOdK = false;
      bool bZqIInJjRC = false;
      bool ZKixACIYBe = false;
      bool twUNYgIQJh = false;
      bool oYzOPaauJn = false;
      bool QgNwogcPjp = false;
      bool oRNzPeFcia = false;
      string rXnaaTLFYh;
      string XnLLAllkjM;
      string TCXpIBaoHf;
      string kTuQsxbrYy;
      string JaKTmVErCH;
      string VPQKMoAxRY;
      string sVxrxEruRD;
      string JsLkCrrEDl;
      string ximAKUCjED;
      string wdZAFmdSVi;
      string dJZyxbEfHT;
      string xusebJixgb;
      string BHpNGfSKeP;
      string OYhUImIoDi;
      string QWbjGBjuYw;
      string EgkthVSLqR;
      string IsArFXMYWn;
      string AssyKdeFHF;
      string uXliKgnnmm;
      string TxylZWVjeh;
      if(rXnaaTLFYh == dJZyxbEfHT){nLXjuLmliD = true;}
      else if(dJZyxbEfHT == rXnaaTLFYh){UNqcEMbTcR = true;}
      if(XnLLAllkjM == xusebJixgb){pNEkVjGRhX = true;}
      else if(xusebJixgb == XnLLAllkjM){tWBCegndYq = true;}
      if(TCXpIBaoHf == BHpNGfSKeP){iYliTDuHYm = true;}
      else if(BHpNGfSKeP == TCXpIBaoHf){BSESbZReyP = true;}
      if(kTuQsxbrYy == OYhUImIoDi){IuaYQjzCnz = true;}
      else if(OYhUImIoDi == kTuQsxbrYy){rMNkrxqOdK = true;}
      if(JaKTmVErCH == QWbjGBjuYw){tCEjwGrMPo = true;}
      else if(QWbjGBjuYw == JaKTmVErCH){bZqIInJjRC = true;}
      if(VPQKMoAxRY == EgkthVSLqR){QEBGyOYnPq = true;}
      else if(EgkthVSLqR == VPQKMoAxRY){ZKixACIYBe = true;}
      if(sVxrxEruRD == IsArFXMYWn){PfNwttleUl = true;}
      else if(IsArFXMYWn == sVxrxEruRD){twUNYgIQJh = true;}
      if(JsLkCrrEDl == AssyKdeFHF){kEchdgUCmN = true;}
      if(ximAKUCjED == uXliKgnnmm){LiqiWDsTaC = true;}
      if(wdZAFmdSVi == TxylZWVjeh){KKlxiNoIoB = true;}
      while(AssyKdeFHF == JsLkCrrEDl){oYzOPaauJn = true;}
      while(uXliKgnnmm == uXliKgnnmm){QgNwogcPjp = true;}
      while(TxylZWVjeh == TxylZWVjeh){oRNzPeFcia = true;}
      if(nLXjuLmliD == true){nLXjuLmliD = false;}
      if(pNEkVjGRhX == true){pNEkVjGRhX = false;}
      if(iYliTDuHYm == true){iYliTDuHYm = false;}
      if(IuaYQjzCnz == true){IuaYQjzCnz = false;}
      if(tCEjwGrMPo == true){tCEjwGrMPo = false;}
      if(QEBGyOYnPq == true){QEBGyOYnPq = false;}
      if(PfNwttleUl == true){PfNwttleUl = false;}
      if(kEchdgUCmN == true){kEchdgUCmN = false;}
      if(LiqiWDsTaC == true){LiqiWDsTaC = false;}
      if(KKlxiNoIoB == true){KKlxiNoIoB = false;}
      if(UNqcEMbTcR == true){UNqcEMbTcR = false;}
      if(tWBCegndYq == true){tWBCegndYq = false;}
      if(BSESbZReyP == true){BSESbZReyP = false;}
      if(rMNkrxqOdK == true){rMNkrxqOdK = false;}
      if(bZqIInJjRC == true){bZqIInJjRC = false;}
      if(ZKixACIYBe == true){ZKixACIYBe = false;}
      if(twUNYgIQJh == true){twUNYgIQJh = false;}
      if(oYzOPaauJn == true){oYzOPaauJn = false;}
      if(QgNwogcPjp == true){QgNwogcPjp = false;}
      if(oRNzPeFcia == true){oRNzPeFcia = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXGEMJFPEA
{ 
  void gXQICjGNOJ()
  { 
      bool JZVWnKJyEm = false;
      bool odPJVNeDet = false;
      bool sSYONTTycF = false;
      bool dQuuCiWPTx = false;
      bool nJCcTAgcfo = false;
      bool BptoeqBGIT = false;
      bool qKVzIXiUGm = false;
      bool qOihFiQuuN = false;
      bool lpSmEmVFPL = false;
      bool gQHAFcnDTu = false;
      bool QMVrymGMiw = false;
      bool aFKuhAriuV = false;
      bool BcEuFaHibc = false;
      bool uMaAwYTZoQ = false;
      bool fJWTkbFLSF = false;
      bool kEIysmIalW = false;
      bool fXjGANdKyI = false;
      bool fRsdorGjJd = false;
      bool UuQWqpEcGI = false;
      bool QsnRkIZPTX = false;
      string WrJcoCmChf;
      string bJJaHVobUU;
      string DXxWnExyno;
      string fRhZQCSweG;
      string TFOZCMAnWF;
      string lPlLxzulok;
      string FoOsAKaiKE;
      string DswNBxIXUa;
      string EIahDQeWbQ;
      string HfHtBdpUZr;
      string kQcSBrSYJz;
      string pXRNfwNgpi;
      string fEHtwWlBMW;
      string HnxconfIfK;
      string xGMbajOsOE;
      string PJepLgJiVe;
      string GRLlrCZoXr;
      string QFAflYqeTM;
      string IrmHHxIHQI;
      string dxlBDftZjX;
      if(WrJcoCmChf == kQcSBrSYJz){JZVWnKJyEm = true;}
      else if(kQcSBrSYJz == WrJcoCmChf){QMVrymGMiw = true;}
      if(bJJaHVobUU == pXRNfwNgpi){odPJVNeDet = true;}
      else if(pXRNfwNgpi == bJJaHVobUU){aFKuhAriuV = true;}
      if(DXxWnExyno == fEHtwWlBMW){sSYONTTycF = true;}
      else if(fEHtwWlBMW == DXxWnExyno){BcEuFaHibc = true;}
      if(fRhZQCSweG == HnxconfIfK){dQuuCiWPTx = true;}
      else if(HnxconfIfK == fRhZQCSweG){uMaAwYTZoQ = true;}
      if(TFOZCMAnWF == xGMbajOsOE){nJCcTAgcfo = true;}
      else if(xGMbajOsOE == TFOZCMAnWF){fJWTkbFLSF = true;}
      if(lPlLxzulok == PJepLgJiVe){BptoeqBGIT = true;}
      else if(PJepLgJiVe == lPlLxzulok){kEIysmIalW = true;}
      if(FoOsAKaiKE == GRLlrCZoXr){qKVzIXiUGm = true;}
      else if(GRLlrCZoXr == FoOsAKaiKE){fXjGANdKyI = true;}
      if(DswNBxIXUa == QFAflYqeTM){qOihFiQuuN = true;}
      if(EIahDQeWbQ == IrmHHxIHQI){lpSmEmVFPL = true;}
      if(HfHtBdpUZr == dxlBDftZjX){gQHAFcnDTu = true;}
      while(QFAflYqeTM == DswNBxIXUa){fRsdorGjJd = true;}
      while(IrmHHxIHQI == IrmHHxIHQI){UuQWqpEcGI = true;}
      while(dxlBDftZjX == dxlBDftZjX){QsnRkIZPTX = true;}
      if(JZVWnKJyEm == true){JZVWnKJyEm = false;}
      if(odPJVNeDet == true){odPJVNeDet = false;}
      if(sSYONTTycF == true){sSYONTTycF = false;}
      if(dQuuCiWPTx == true){dQuuCiWPTx = false;}
      if(nJCcTAgcfo == true){nJCcTAgcfo = false;}
      if(BptoeqBGIT == true){BptoeqBGIT = false;}
      if(qKVzIXiUGm == true){qKVzIXiUGm = false;}
      if(qOihFiQuuN == true){qOihFiQuuN = false;}
      if(lpSmEmVFPL == true){lpSmEmVFPL = false;}
      if(gQHAFcnDTu == true){gQHAFcnDTu = false;}
      if(QMVrymGMiw == true){QMVrymGMiw = false;}
      if(aFKuhAriuV == true){aFKuhAriuV = false;}
      if(BcEuFaHibc == true){BcEuFaHibc = false;}
      if(uMaAwYTZoQ == true){uMaAwYTZoQ = false;}
      if(fJWTkbFLSF == true){fJWTkbFLSF = false;}
      if(kEIysmIalW == true){kEIysmIalW = false;}
      if(fXjGANdKyI == true){fXjGANdKyI = false;}
      if(fRsdorGjJd == true){fRsdorGjJd = false;}
      if(UuQWqpEcGI == true){UuQWqpEcGI = false;}
      if(QsnRkIZPTX == true){QsnRkIZPTX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGNYSVWPVV
{ 
  void CwpjLMwtRw()
  { 
      bool eLzOFJYDmW = false;
      bool uLZBrXjxlh = false;
      bool JpKhNdtesS = false;
      bool PAezoTUsuk = false;
      bool fdONziUmEx = false;
      bool eMshsnBRAb = false;
      bool OtKUHufaMX = false;
      bool DqBBBebxhe = false;
      bool IGZwmDGxFA = false;
      bool SCrTVlTtGE = false;
      bool CtaftnKrfN = false;
      bool MEjVSITOgE = false;
      bool niULFAygfP = false;
      bool LgpcbOfsBz = false;
      bool rOQrnOSVBN = false;
      bool REMCQTZOas = false;
      bool ocMPCeNGtE = false;
      bool bZMhLYRcXp = false;
      bool gcfRyGUnLH = false;
      bool oRSIJOCBoJ = false;
      string DhDwSqqzys;
      string xLmGfxGIYl;
      string hRbOyDAWST;
      string TZhsXwYduR;
      string JdWnBByFxk;
      string RllyxlGoyO;
      string qUfdZWdthi;
      string XcMGcEtmMw;
      string FtZhChniul;
      string pjeganysOe;
      string XEXNMoYeVr;
      string rScCJwuxar;
      string itywrnxffn;
      string FAYgYAWLVM;
      string IINDtXHcXe;
      string sARWwcGbVY;
      string rsygmqsucI;
      string YjbOiZguBT;
      string fTIBtEhCju;
      string tuoxUPJfPC;
      if(DhDwSqqzys == XEXNMoYeVr){eLzOFJYDmW = true;}
      else if(XEXNMoYeVr == DhDwSqqzys){CtaftnKrfN = true;}
      if(xLmGfxGIYl == rScCJwuxar){uLZBrXjxlh = true;}
      else if(rScCJwuxar == xLmGfxGIYl){MEjVSITOgE = true;}
      if(hRbOyDAWST == itywrnxffn){JpKhNdtesS = true;}
      else if(itywrnxffn == hRbOyDAWST){niULFAygfP = true;}
      if(TZhsXwYduR == FAYgYAWLVM){PAezoTUsuk = true;}
      else if(FAYgYAWLVM == TZhsXwYduR){LgpcbOfsBz = true;}
      if(JdWnBByFxk == IINDtXHcXe){fdONziUmEx = true;}
      else if(IINDtXHcXe == JdWnBByFxk){rOQrnOSVBN = true;}
      if(RllyxlGoyO == sARWwcGbVY){eMshsnBRAb = true;}
      else if(sARWwcGbVY == RllyxlGoyO){REMCQTZOas = true;}
      if(qUfdZWdthi == rsygmqsucI){OtKUHufaMX = true;}
      else if(rsygmqsucI == qUfdZWdthi){ocMPCeNGtE = true;}
      if(XcMGcEtmMw == YjbOiZguBT){DqBBBebxhe = true;}
      if(FtZhChniul == fTIBtEhCju){IGZwmDGxFA = true;}
      if(pjeganysOe == tuoxUPJfPC){SCrTVlTtGE = true;}
      while(YjbOiZguBT == XcMGcEtmMw){bZMhLYRcXp = true;}
      while(fTIBtEhCju == fTIBtEhCju){gcfRyGUnLH = true;}
      while(tuoxUPJfPC == tuoxUPJfPC){oRSIJOCBoJ = true;}
      if(eLzOFJYDmW == true){eLzOFJYDmW = false;}
      if(uLZBrXjxlh == true){uLZBrXjxlh = false;}
      if(JpKhNdtesS == true){JpKhNdtesS = false;}
      if(PAezoTUsuk == true){PAezoTUsuk = false;}
      if(fdONziUmEx == true){fdONziUmEx = false;}
      if(eMshsnBRAb == true){eMshsnBRAb = false;}
      if(OtKUHufaMX == true){OtKUHufaMX = false;}
      if(DqBBBebxhe == true){DqBBBebxhe = false;}
      if(IGZwmDGxFA == true){IGZwmDGxFA = false;}
      if(SCrTVlTtGE == true){SCrTVlTtGE = false;}
      if(CtaftnKrfN == true){CtaftnKrfN = false;}
      if(MEjVSITOgE == true){MEjVSITOgE = false;}
      if(niULFAygfP == true){niULFAygfP = false;}
      if(LgpcbOfsBz == true){LgpcbOfsBz = false;}
      if(rOQrnOSVBN == true){rOQrnOSVBN = false;}
      if(REMCQTZOas == true){REMCQTZOas = false;}
      if(ocMPCeNGtE == true){ocMPCeNGtE = false;}
      if(bZMhLYRcXp == true){bZMhLYRcXp = false;}
      if(gcfRyGUnLH == true){gcfRyGUnLH = false;}
      if(oRSIJOCBoJ == true){oRSIJOCBoJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZIMBXXWKT
{ 
  void AQUZdUOtIP()
  { 
      bool FxMsFkIHlK = false;
      bool wPlDYLpjwG = false;
      bool dwBSjpUVRL = false;
      bool nzGJVHcQME = false;
      bool hNcGyWKYnI = false;
      bool QcbxaJutIP = false;
      bool QmpaWxIchQ = false;
      bool iYXrXQStTN = false;
      bool ewhJtLWJhM = false;
      bool MhHwmuWCjB = false;
      bool OhpWYqEjYK = false;
      bool pAaujUFffK = false;
      bool ZztVEBRaEc = false;
      bool sPKRzxFKjD = false;
      bool GljWVMHMLS = false;
      bool oqVYaPmURX = false;
      bool ZdfwRZoIwm = false;
      bool PtucEmOWzr = false;
      bool tEOkmBskqj = false;
      bool JjrMccGnFu = false;
      string BXaYIjbsYC;
      string SyJrSBYHYl;
      string lSrXbberab;
      string obtPDcQCfj;
      string YjzrRHeKMj;
      string nDBYhifDxg;
      string FjRwMpEsno;
      string jVanNBSzFT;
      string xTeqnkaVhU;
      string xNEzdnSCfa;
      string DkVWzRcMKg;
      string PfxdikFaIa;
      string PiLTrVQaKY;
      string iPTdPLyHqV;
      string IOKBEQQaQr;
      string irtELUZBed;
      string BBBlxzLTNW;
      string mxilSAXKOa;
      string EoKRpqVPRu;
      string lxcMTHMYDF;
      if(BXaYIjbsYC == DkVWzRcMKg){FxMsFkIHlK = true;}
      else if(DkVWzRcMKg == BXaYIjbsYC){OhpWYqEjYK = true;}
      if(SyJrSBYHYl == PfxdikFaIa){wPlDYLpjwG = true;}
      else if(PfxdikFaIa == SyJrSBYHYl){pAaujUFffK = true;}
      if(lSrXbberab == PiLTrVQaKY){dwBSjpUVRL = true;}
      else if(PiLTrVQaKY == lSrXbberab){ZztVEBRaEc = true;}
      if(obtPDcQCfj == iPTdPLyHqV){nzGJVHcQME = true;}
      else if(iPTdPLyHqV == obtPDcQCfj){sPKRzxFKjD = true;}
      if(YjzrRHeKMj == IOKBEQQaQr){hNcGyWKYnI = true;}
      else if(IOKBEQQaQr == YjzrRHeKMj){GljWVMHMLS = true;}
      if(nDBYhifDxg == irtELUZBed){QcbxaJutIP = true;}
      else if(irtELUZBed == nDBYhifDxg){oqVYaPmURX = true;}
      if(FjRwMpEsno == BBBlxzLTNW){QmpaWxIchQ = true;}
      else if(BBBlxzLTNW == FjRwMpEsno){ZdfwRZoIwm = true;}
      if(jVanNBSzFT == mxilSAXKOa){iYXrXQStTN = true;}
      if(xTeqnkaVhU == EoKRpqVPRu){ewhJtLWJhM = true;}
      if(xNEzdnSCfa == lxcMTHMYDF){MhHwmuWCjB = true;}
      while(mxilSAXKOa == jVanNBSzFT){PtucEmOWzr = true;}
      while(EoKRpqVPRu == EoKRpqVPRu){tEOkmBskqj = true;}
      while(lxcMTHMYDF == lxcMTHMYDF){JjrMccGnFu = true;}
      if(FxMsFkIHlK == true){FxMsFkIHlK = false;}
      if(wPlDYLpjwG == true){wPlDYLpjwG = false;}
      if(dwBSjpUVRL == true){dwBSjpUVRL = false;}
      if(nzGJVHcQME == true){nzGJVHcQME = false;}
      if(hNcGyWKYnI == true){hNcGyWKYnI = false;}
      if(QcbxaJutIP == true){QcbxaJutIP = false;}
      if(QmpaWxIchQ == true){QmpaWxIchQ = false;}
      if(iYXrXQStTN == true){iYXrXQStTN = false;}
      if(ewhJtLWJhM == true){ewhJtLWJhM = false;}
      if(MhHwmuWCjB == true){MhHwmuWCjB = false;}
      if(OhpWYqEjYK == true){OhpWYqEjYK = false;}
      if(pAaujUFffK == true){pAaujUFffK = false;}
      if(ZztVEBRaEc == true){ZztVEBRaEc = false;}
      if(sPKRzxFKjD == true){sPKRzxFKjD = false;}
      if(GljWVMHMLS == true){GljWVMHMLS = false;}
      if(oqVYaPmURX == true){oqVYaPmURX = false;}
      if(ZdfwRZoIwm == true){ZdfwRZoIwm = false;}
      if(PtucEmOWzr == true){PtucEmOWzr = false;}
      if(tEOkmBskqj == true){tEOkmBskqj = false;}
      if(JjrMccGnFu == true){JjrMccGnFu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PZQCXAZZTI
{ 
  void hSxFAVwBLg()
  { 
      bool JOwxXnAazK = false;
      bool jTLKBACmIn = false;
      bool fWQRPJTqoh = false;
      bool HhnHAPGMnu = false;
      bool UFZkTDfbbc = false;
      bool PCocYmxdgN = false;
      bool UIkRCBfEJk = false;
      bool soyMTaxfyM = false;
      bool cqPMRErKhN = false;
      bool RcfZaLTHhR = false;
      bool XbRpjaDbJy = false;
      bool pReTkcrYzx = false;
      bool IUVwSPIYlI = false;
      bool GoxfnAZZcq = false;
      bool BPAiXAxLox = false;
      bool SuIjICFVXT = false;
      bool RepBrATzfj = false;
      bool DSwIwrUmXS = false;
      bool SwinoKgNWl = false;
      bool uDBIYVZzqW = false;
      string TiHnGtfxJb;
      string uIYuAqpZGz;
      string MOFylSHYYG;
      string JkWQKGxLJd;
      string NWuyCbOnfe;
      string CXMIoFcJBn;
      string lGXDRJlIjt;
      string sdPckoSGuK;
      string DTstElYNaF;
      string cnJUqHzrfr;
      string oGDlkXHjWz;
      string mWNqjRMdyf;
      string kXgeQFUukd;
      string pZZCUwQHIf;
      string enqaRGZRkY;
      string tUsAHQYXUf;
      string CMyrJMwLVm;
      string BFUSAxgFMK;
      string eCJLjUfZuD;
      string WrlccSoyRF;
      if(TiHnGtfxJb == oGDlkXHjWz){JOwxXnAazK = true;}
      else if(oGDlkXHjWz == TiHnGtfxJb){XbRpjaDbJy = true;}
      if(uIYuAqpZGz == mWNqjRMdyf){jTLKBACmIn = true;}
      else if(mWNqjRMdyf == uIYuAqpZGz){pReTkcrYzx = true;}
      if(MOFylSHYYG == kXgeQFUukd){fWQRPJTqoh = true;}
      else if(kXgeQFUukd == MOFylSHYYG){IUVwSPIYlI = true;}
      if(JkWQKGxLJd == pZZCUwQHIf){HhnHAPGMnu = true;}
      else if(pZZCUwQHIf == JkWQKGxLJd){GoxfnAZZcq = true;}
      if(NWuyCbOnfe == enqaRGZRkY){UFZkTDfbbc = true;}
      else if(enqaRGZRkY == NWuyCbOnfe){BPAiXAxLox = true;}
      if(CXMIoFcJBn == tUsAHQYXUf){PCocYmxdgN = true;}
      else if(tUsAHQYXUf == CXMIoFcJBn){SuIjICFVXT = true;}
      if(lGXDRJlIjt == CMyrJMwLVm){UIkRCBfEJk = true;}
      else if(CMyrJMwLVm == lGXDRJlIjt){RepBrATzfj = true;}
      if(sdPckoSGuK == BFUSAxgFMK){soyMTaxfyM = true;}
      if(DTstElYNaF == eCJLjUfZuD){cqPMRErKhN = true;}
      if(cnJUqHzrfr == WrlccSoyRF){RcfZaLTHhR = true;}
      while(BFUSAxgFMK == sdPckoSGuK){DSwIwrUmXS = true;}
      while(eCJLjUfZuD == eCJLjUfZuD){SwinoKgNWl = true;}
      while(WrlccSoyRF == WrlccSoyRF){uDBIYVZzqW = true;}
      if(JOwxXnAazK == true){JOwxXnAazK = false;}
      if(jTLKBACmIn == true){jTLKBACmIn = false;}
      if(fWQRPJTqoh == true){fWQRPJTqoh = false;}
      if(HhnHAPGMnu == true){HhnHAPGMnu = false;}
      if(UFZkTDfbbc == true){UFZkTDfbbc = false;}
      if(PCocYmxdgN == true){PCocYmxdgN = false;}
      if(UIkRCBfEJk == true){UIkRCBfEJk = false;}
      if(soyMTaxfyM == true){soyMTaxfyM = false;}
      if(cqPMRErKhN == true){cqPMRErKhN = false;}
      if(RcfZaLTHhR == true){RcfZaLTHhR = false;}
      if(XbRpjaDbJy == true){XbRpjaDbJy = false;}
      if(pReTkcrYzx == true){pReTkcrYzx = false;}
      if(IUVwSPIYlI == true){IUVwSPIYlI = false;}
      if(GoxfnAZZcq == true){GoxfnAZZcq = false;}
      if(BPAiXAxLox == true){BPAiXAxLox = false;}
      if(SuIjICFVXT == true){SuIjICFVXT = false;}
      if(RepBrATzfj == true){RepBrATzfj = false;}
      if(DSwIwrUmXS == true){DSwIwrUmXS = false;}
      if(SwinoKgNWl == true){SwinoKgNWl = false;}
      if(uDBIYVZzqW == true){uDBIYVZzqW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYHZOLDOTA
{ 
  void AENJdhHlXe()
  { 
      bool REpHeEwddm = false;
      bool nDhnhoqdUL = false;
      bool rhkJlszsJX = false;
      bool XqfQOeTLqi = false;
      bool zZNszeHQMB = false;
      bool QEeqejTgUl = false;
      bool FDUGPwWRZD = false;
      bool UflkLSTqJH = false;
      bool kifHGTMold = false;
      bool LlpFduFHdD = false;
      bool HppJfkRsfM = false;
      bool QbXNAVWMzu = false;
      bool jhfuqiogHP = false;
      bool MLNGztrWaV = false;
      bool BSJYNiObEH = false;
      bool YrHhSZKuRx = false;
      bool uklPzEORNG = false;
      bool dAkdtRYGhI = false;
      bool TNczqTEemZ = false;
      bool jxEcZQgsZJ = false;
      string zjsUMgIRdI;
      string EWBAKegOAW;
      string uLrtAXnKdu;
      string lyGIoNLaEE;
      string laFemyXspr;
      string FPfqJmqyTn;
      string rynhVFQrLw;
      string TGKwjUGMGB;
      string zuTlpWRPzB;
      string WNGPLmmWJg;
      string gfgtXzEjGo;
      string gdqSnxdBry;
      string nBsJYGztjx;
      string giDZUTNZNq;
      string ShJKUrVnbO;
      string IkeKsflWUR;
      string zJzIHxaRxT;
      string iEnAfFrinf;
      string jKSVnwErfn;
      string hpEuqIhACX;
      if(zjsUMgIRdI == gfgtXzEjGo){REpHeEwddm = true;}
      else if(gfgtXzEjGo == zjsUMgIRdI){HppJfkRsfM = true;}
      if(EWBAKegOAW == gdqSnxdBry){nDhnhoqdUL = true;}
      else if(gdqSnxdBry == EWBAKegOAW){QbXNAVWMzu = true;}
      if(uLrtAXnKdu == nBsJYGztjx){rhkJlszsJX = true;}
      else if(nBsJYGztjx == uLrtAXnKdu){jhfuqiogHP = true;}
      if(lyGIoNLaEE == giDZUTNZNq){XqfQOeTLqi = true;}
      else if(giDZUTNZNq == lyGIoNLaEE){MLNGztrWaV = true;}
      if(laFemyXspr == ShJKUrVnbO){zZNszeHQMB = true;}
      else if(ShJKUrVnbO == laFemyXspr){BSJYNiObEH = true;}
      if(FPfqJmqyTn == IkeKsflWUR){QEeqejTgUl = true;}
      else if(IkeKsflWUR == FPfqJmqyTn){YrHhSZKuRx = true;}
      if(rynhVFQrLw == zJzIHxaRxT){FDUGPwWRZD = true;}
      else if(zJzIHxaRxT == rynhVFQrLw){uklPzEORNG = true;}
      if(TGKwjUGMGB == iEnAfFrinf){UflkLSTqJH = true;}
      if(zuTlpWRPzB == jKSVnwErfn){kifHGTMold = true;}
      if(WNGPLmmWJg == hpEuqIhACX){LlpFduFHdD = true;}
      while(iEnAfFrinf == TGKwjUGMGB){dAkdtRYGhI = true;}
      while(jKSVnwErfn == jKSVnwErfn){TNczqTEemZ = true;}
      while(hpEuqIhACX == hpEuqIhACX){jxEcZQgsZJ = true;}
      if(REpHeEwddm == true){REpHeEwddm = false;}
      if(nDhnhoqdUL == true){nDhnhoqdUL = false;}
      if(rhkJlszsJX == true){rhkJlszsJX = false;}
      if(XqfQOeTLqi == true){XqfQOeTLqi = false;}
      if(zZNszeHQMB == true){zZNszeHQMB = false;}
      if(QEeqejTgUl == true){QEeqejTgUl = false;}
      if(FDUGPwWRZD == true){FDUGPwWRZD = false;}
      if(UflkLSTqJH == true){UflkLSTqJH = false;}
      if(kifHGTMold == true){kifHGTMold = false;}
      if(LlpFduFHdD == true){LlpFduFHdD = false;}
      if(HppJfkRsfM == true){HppJfkRsfM = false;}
      if(QbXNAVWMzu == true){QbXNAVWMzu = false;}
      if(jhfuqiogHP == true){jhfuqiogHP = false;}
      if(MLNGztrWaV == true){MLNGztrWaV = false;}
      if(BSJYNiObEH == true){BSJYNiObEH = false;}
      if(YrHhSZKuRx == true){YrHhSZKuRx = false;}
      if(uklPzEORNG == true){uklPzEORNG = false;}
      if(dAkdtRYGhI == true){dAkdtRYGhI = false;}
      if(TNczqTEemZ == true){TNczqTEemZ = false;}
      if(jxEcZQgsZJ == true){jxEcZQgsZJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOEUXAVVLG
{ 
  void JpHrMMidxx()
  { 
      bool JPiskIjZlW = false;
      bool znYWDHNxIA = false;
      bool prDNxOkKMf = false;
      bool KYOHOYaLML = false;
      bool oRodzHQDfB = false;
      bool fwtgERMVwW = false;
      bool WZNGMaZRHd = false;
      bool gCkxLXDYNo = false;
      bool xhdLzNdgCx = false;
      bool MEPonOEiRY = false;
      bool hyuCUcKxVg = false;
      bool OmIGZouCGy = false;
      bool wrOKRbmwIw = false;
      bool SUHoHylbpV = false;
      bool CgLUhYwIPy = false;
      bool TCbSbpjjkr = false;
      bool pOnZOtfSza = false;
      bool DTLjwOgscr = false;
      bool edfJcQroMQ = false;
      bool OBqyemslGn = false;
      string gfXtkILoJA;
      string fQzoFrSOHG;
      string CZrryqNEpM;
      string pKKOIVgdHH;
      string MzqIroXnhM;
      string MRjMfGnfut;
      string uGzxKVFkgi;
      string KnGztDiizJ;
      string TYVdzXZyiB;
      string gAhNLFztxW;
      string ilHyBXLjRb;
      string XEglaVjVxl;
      string uHCfCJGrno;
      string DolcZgRXba;
      string MpfGccTump;
      string UdwLbajbwr;
      string RSwcYhSEMs;
      string EMtVZEbwCY;
      string oKEyTYraAy;
      string wpaiJttDgt;
      if(gfXtkILoJA == ilHyBXLjRb){JPiskIjZlW = true;}
      else if(ilHyBXLjRb == gfXtkILoJA){hyuCUcKxVg = true;}
      if(fQzoFrSOHG == XEglaVjVxl){znYWDHNxIA = true;}
      else if(XEglaVjVxl == fQzoFrSOHG){OmIGZouCGy = true;}
      if(CZrryqNEpM == uHCfCJGrno){prDNxOkKMf = true;}
      else if(uHCfCJGrno == CZrryqNEpM){wrOKRbmwIw = true;}
      if(pKKOIVgdHH == DolcZgRXba){KYOHOYaLML = true;}
      else if(DolcZgRXba == pKKOIVgdHH){SUHoHylbpV = true;}
      if(MzqIroXnhM == MpfGccTump){oRodzHQDfB = true;}
      else if(MpfGccTump == MzqIroXnhM){CgLUhYwIPy = true;}
      if(MRjMfGnfut == UdwLbajbwr){fwtgERMVwW = true;}
      else if(UdwLbajbwr == MRjMfGnfut){TCbSbpjjkr = true;}
      if(uGzxKVFkgi == RSwcYhSEMs){WZNGMaZRHd = true;}
      else if(RSwcYhSEMs == uGzxKVFkgi){pOnZOtfSza = true;}
      if(KnGztDiizJ == EMtVZEbwCY){gCkxLXDYNo = true;}
      if(TYVdzXZyiB == oKEyTYraAy){xhdLzNdgCx = true;}
      if(gAhNLFztxW == wpaiJttDgt){MEPonOEiRY = true;}
      while(EMtVZEbwCY == KnGztDiizJ){DTLjwOgscr = true;}
      while(oKEyTYraAy == oKEyTYraAy){edfJcQroMQ = true;}
      while(wpaiJttDgt == wpaiJttDgt){OBqyemslGn = true;}
      if(JPiskIjZlW == true){JPiskIjZlW = false;}
      if(znYWDHNxIA == true){znYWDHNxIA = false;}
      if(prDNxOkKMf == true){prDNxOkKMf = false;}
      if(KYOHOYaLML == true){KYOHOYaLML = false;}
      if(oRodzHQDfB == true){oRodzHQDfB = false;}
      if(fwtgERMVwW == true){fwtgERMVwW = false;}
      if(WZNGMaZRHd == true){WZNGMaZRHd = false;}
      if(gCkxLXDYNo == true){gCkxLXDYNo = false;}
      if(xhdLzNdgCx == true){xhdLzNdgCx = false;}
      if(MEPonOEiRY == true){MEPonOEiRY = false;}
      if(hyuCUcKxVg == true){hyuCUcKxVg = false;}
      if(OmIGZouCGy == true){OmIGZouCGy = false;}
      if(wrOKRbmwIw == true){wrOKRbmwIw = false;}
      if(SUHoHylbpV == true){SUHoHylbpV = false;}
      if(CgLUhYwIPy == true){CgLUhYwIPy = false;}
      if(TCbSbpjjkr == true){TCbSbpjjkr = false;}
      if(pOnZOtfSza == true){pOnZOtfSza = false;}
      if(DTLjwOgscr == true){DTLjwOgscr = false;}
      if(edfJcQroMQ == true){edfJcQroMQ = false;}
      if(OBqyemslGn == true){OBqyemslGn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVCUMFITRD
{ 
  void ulYbMgxUMJ()
  { 
      bool bnWfztKKqH = false;
      bool pWywcQdddx = false;
      bool EtOnQlKXhW = false;
      bool iidUnGVaGF = false;
      bool cTLraRQeyE = false;
      bool VcfMkhYhON = false;
      bool imbUYGscIW = false;
      bool uDWYTjhWNy = false;
      bool UfYdAGCRjF = false;
      bool gmLsVpqqTT = false;
      bool YmWbISFHrA = false;
      bool zCUPrDOyTR = false;
      bool DarCoHqdCd = false;
      bool rqCsZhIxUh = false;
      bool AuYjGeSwAS = false;
      bool bsXBPxuUlB = false;
      bool baEOIHzapK = false;
      bool tQckRICIuK = false;
      bool oudjCyTBcc = false;
      bool mnKTGZpJay = false;
      string zrFsJbfMnB;
      string PjjEWLMgnK;
      string dfmSTGpRwu;
      string dCAVUtAIuK;
      string VXpwqBJadd;
      string jOUApSFlYD;
      string lOQsXNiOjc;
      string KEkdoGppaS;
      string wOnSKOgAeB;
      string nNirXHHwXd;
      string RuqATfdpLj;
      string cPLGGXZxhI;
      string fhiinwVrGg;
      string ysRxAAWmye;
      string kpouYYCckA;
      string gJNOxiLILW;
      string JkjdkixOFF;
      string AmzDXosnKP;
      string tsGGzneDzQ;
      string oObbUAGKJo;
      if(zrFsJbfMnB == RuqATfdpLj){bnWfztKKqH = true;}
      else if(RuqATfdpLj == zrFsJbfMnB){YmWbISFHrA = true;}
      if(PjjEWLMgnK == cPLGGXZxhI){pWywcQdddx = true;}
      else if(cPLGGXZxhI == PjjEWLMgnK){zCUPrDOyTR = true;}
      if(dfmSTGpRwu == fhiinwVrGg){EtOnQlKXhW = true;}
      else if(fhiinwVrGg == dfmSTGpRwu){DarCoHqdCd = true;}
      if(dCAVUtAIuK == ysRxAAWmye){iidUnGVaGF = true;}
      else if(ysRxAAWmye == dCAVUtAIuK){rqCsZhIxUh = true;}
      if(VXpwqBJadd == kpouYYCckA){cTLraRQeyE = true;}
      else if(kpouYYCckA == VXpwqBJadd){AuYjGeSwAS = true;}
      if(jOUApSFlYD == gJNOxiLILW){VcfMkhYhON = true;}
      else if(gJNOxiLILW == jOUApSFlYD){bsXBPxuUlB = true;}
      if(lOQsXNiOjc == JkjdkixOFF){imbUYGscIW = true;}
      else if(JkjdkixOFF == lOQsXNiOjc){baEOIHzapK = true;}
      if(KEkdoGppaS == AmzDXosnKP){uDWYTjhWNy = true;}
      if(wOnSKOgAeB == tsGGzneDzQ){UfYdAGCRjF = true;}
      if(nNirXHHwXd == oObbUAGKJo){gmLsVpqqTT = true;}
      while(AmzDXosnKP == KEkdoGppaS){tQckRICIuK = true;}
      while(tsGGzneDzQ == tsGGzneDzQ){oudjCyTBcc = true;}
      while(oObbUAGKJo == oObbUAGKJo){mnKTGZpJay = true;}
      if(bnWfztKKqH == true){bnWfztKKqH = false;}
      if(pWywcQdddx == true){pWywcQdddx = false;}
      if(EtOnQlKXhW == true){EtOnQlKXhW = false;}
      if(iidUnGVaGF == true){iidUnGVaGF = false;}
      if(cTLraRQeyE == true){cTLraRQeyE = false;}
      if(VcfMkhYhON == true){VcfMkhYhON = false;}
      if(imbUYGscIW == true){imbUYGscIW = false;}
      if(uDWYTjhWNy == true){uDWYTjhWNy = false;}
      if(UfYdAGCRjF == true){UfYdAGCRjF = false;}
      if(gmLsVpqqTT == true){gmLsVpqqTT = false;}
      if(YmWbISFHrA == true){YmWbISFHrA = false;}
      if(zCUPrDOyTR == true){zCUPrDOyTR = false;}
      if(DarCoHqdCd == true){DarCoHqdCd = false;}
      if(rqCsZhIxUh == true){rqCsZhIxUh = false;}
      if(AuYjGeSwAS == true){AuYjGeSwAS = false;}
      if(bsXBPxuUlB == true){bsXBPxuUlB = false;}
      if(baEOIHzapK == true){baEOIHzapK = false;}
      if(tQckRICIuK == true){tQckRICIuK = false;}
      if(oudjCyTBcc == true){oudjCyTBcc = false;}
      if(mnKTGZpJay == true){mnKTGZpJay = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWLIBEWADN
{ 
  void pUatErrwEU()
  { 
      bool ekGRpTdcFF = false;
      bool ZedlAHnSSV = false;
      bool QjBDboMuVm = false;
      bool pHBrqLYodm = false;
      bool YnSGZOQyXS = false;
      bool TFmjKujDoB = false;
      bool HiGSORdlto = false;
      bool izoewbRtdM = false;
      bool YNXCSkUQgw = false;
      bool aVzcfpgArI = false;
      bool keEijUQHmi = false;
      bool coYbbsKDzc = false;
      bool xMEyNNzLyG = false;
      bool uRBVbtJnSy = false;
      bool UMdySlwWAl = false;
      bool ecBPKYZFVV = false;
      bool UEIfmLmDAh = false;
      bool jWjAIjhFea = false;
      bool RbLLaRPlKD = false;
      bool TDSxcQDxLH = false;
      string PNzjZBQtKJ;
      string fdRpGyAiun;
      string gOKgZTENqI;
      string TRFYgZLKxz;
      string JpmnHFPkAe;
      string RbbbRADSKF;
      string wCCBpOXrJg;
      string molwdpbWYU;
      string DTMMprpdGg;
      string VrAqCGnkxs;
      string gXaTqbofxb;
      string XgspCcpoLx;
      string YtlcKuousX;
      string CpYfmfssUN;
      string CJfeInyJnZ;
      string QyZATmlyIw;
      string mtlZYgINDW;
      string jwTxuONGTW;
      string weGTHDQXMz;
      string ttjYaHXFFb;
      if(PNzjZBQtKJ == gXaTqbofxb){ekGRpTdcFF = true;}
      else if(gXaTqbofxb == PNzjZBQtKJ){keEijUQHmi = true;}
      if(fdRpGyAiun == XgspCcpoLx){ZedlAHnSSV = true;}
      else if(XgspCcpoLx == fdRpGyAiun){coYbbsKDzc = true;}
      if(gOKgZTENqI == YtlcKuousX){QjBDboMuVm = true;}
      else if(YtlcKuousX == gOKgZTENqI){xMEyNNzLyG = true;}
      if(TRFYgZLKxz == CpYfmfssUN){pHBrqLYodm = true;}
      else if(CpYfmfssUN == TRFYgZLKxz){uRBVbtJnSy = true;}
      if(JpmnHFPkAe == CJfeInyJnZ){YnSGZOQyXS = true;}
      else if(CJfeInyJnZ == JpmnHFPkAe){UMdySlwWAl = true;}
      if(RbbbRADSKF == QyZATmlyIw){TFmjKujDoB = true;}
      else if(QyZATmlyIw == RbbbRADSKF){ecBPKYZFVV = true;}
      if(wCCBpOXrJg == mtlZYgINDW){HiGSORdlto = true;}
      else if(mtlZYgINDW == wCCBpOXrJg){UEIfmLmDAh = true;}
      if(molwdpbWYU == jwTxuONGTW){izoewbRtdM = true;}
      if(DTMMprpdGg == weGTHDQXMz){YNXCSkUQgw = true;}
      if(VrAqCGnkxs == ttjYaHXFFb){aVzcfpgArI = true;}
      while(jwTxuONGTW == molwdpbWYU){jWjAIjhFea = true;}
      while(weGTHDQXMz == weGTHDQXMz){RbLLaRPlKD = true;}
      while(ttjYaHXFFb == ttjYaHXFFb){TDSxcQDxLH = true;}
      if(ekGRpTdcFF == true){ekGRpTdcFF = false;}
      if(ZedlAHnSSV == true){ZedlAHnSSV = false;}
      if(QjBDboMuVm == true){QjBDboMuVm = false;}
      if(pHBrqLYodm == true){pHBrqLYodm = false;}
      if(YnSGZOQyXS == true){YnSGZOQyXS = false;}
      if(TFmjKujDoB == true){TFmjKujDoB = false;}
      if(HiGSORdlto == true){HiGSORdlto = false;}
      if(izoewbRtdM == true){izoewbRtdM = false;}
      if(YNXCSkUQgw == true){YNXCSkUQgw = false;}
      if(aVzcfpgArI == true){aVzcfpgArI = false;}
      if(keEijUQHmi == true){keEijUQHmi = false;}
      if(coYbbsKDzc == true){coYbbsKDzc = false;}
      if(xMEyNNzLyG == true){xMEyNNzLyG = false;}
      if(uRBVbtJnSy == true){uRBVbtJnSy = false;}
      if(UMdySlwWAl == true){UMdySlwWAl = false;}
      if(ecBPKYZFVV == true){ecBPKYZFVV = false;}
      if(UEIfmLmDAh == true){UEIfmLmDAh = false;}
      if(jWjAIjhFea == true){jWjAIjhFea = false;}
      if(RbLLaRPlKD == true){RbLLaRPlKD = false;}
      if(TDSxcQDxLH == true){TDSxcQDxLH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAAOEVVFCS
{ 
  void gptkJVQpmn()
  { 
      bool HWWiQeeMNB = false;
      bool GnCSukisjS = false;
      bool EMewKbpQCH = false;
      bool sztdyWHbEB = false;
      bool CYqaGUDQKj = false;
      bool LEUbbtraXn = false;
      bool oOJFIHsXUY = false;
      bool cGoiPeVDpo = false;
      bool XYFSwodSBE = false;
      bool dgEPMmOkSy = false;
      bool bfwkGEOlMx = false;
      bool XokhPQIqJT = false;
      bool cZWQuwCYVb = false;
      bool PjkqNrcTLq = false;
      bool ZrFEfouVAw = false;
      bool eXbzVBIepK = false;
      bool CpPjgmEtUX = false;
      bool nnfRsjTSkF = false;
      bool AgYZxrIkVM = false;
      bool ixdBojbVXr = false;
      string uaMAgrzhjI;
      string pKdYIrmgiN;
      string xXQNEbbDGP;
      string WsHPHTILMQ;
      string ltKqtqbNqx;
      string DbAflXKywF;
      string QwaTlxDORn;
      string ibUSbCMYTM;
      string zOMJMusadi;
      string JJPHAoSqFx;
      string nNuDObHgEi;
      string LkeiFBjRHp;
      string DbjhdYLMSl;
      string iUTWYlSJuj;
      string nLWtXYegBy;
      string FBiPsLcMYo;
      string PtNRApRHJS;
      string hZVWBqEoKF;
      string seKUghkEcN;
      string IFjFUtyFtg;
      if(uaMAgrzhjI == nNuDObHgEi){HWWiQeeMNB = true;}
      else if(nNuDObHgEi == uaMAgrzhjI){bfwkGEOlMx = true;}
      if(pKdYIrmgiN == LkeiFBjRHp){GnCSukisjS = true;}
      else if(LkeiFBjRHp == pKdYIrmgiN){XokhPQIqJT = true;}
      if(xXQNEbbDGP == DbjhdYLMSl){EMewKbpQCH = true;}
      else if(DbjhdYLMSl == xXQNEbbDGP){cZWQuwCYVb = true;}
      if(WsHPHTILMQ == iUTWYlSJuj){sztdyWHbEB = true;}
      else if(iUTWYlSJuj == WsHPHTILMQ){PjkqNrcTLq = true;}
      if(ltKqtqbNqx == nLWtXYegBy){CYqaGUDQKj = true;}
      else if(nLWtXYegBy == ltKqtqbNqx){ZrFEfouVAw = true;}
      if(DbAflXKywF == FBiPsLcMYo){LEUbbtraXn = true;}
      else if(FBiPsLcMYo == DbAflXKywF){eXbzVBIepK = true;}
      if(QwaTlxDORn == PtNRApRHJS){oOJFIHsXUY = true;}
      else if(PtNRApRHJS == QwaTlxDORn){CpPjgmEtUX = true;}
      if(ibUSbCMYTM == hZVWBqEoKF){cGoiPeVDpo = true;}
      if(zOMJMusadi == seKUghkEcN){XYFSwodSBE = true;}
      if(JJPHAoSqFx == IFjFUtyFtg){dgEPMmOkSy = true;}
      while(hZVWBqEoKF == ibUSbCMYTM){nnfRsjTSkF = true;}
      while(seKUghkEcN == seKUghkEcN){AgYZxrIkVM = true;}
      while(IFjFUtyFtg == IFjFUtyFtg){ixdBojbVXr = true;}
      if(HWWiQeeMNB == true){HWWiQeeMNB = false;}
      if(GnCSukisjS == true){GnCSukisjS = false;}
      if(EMewKbpQCH == true){EMewKbpQCH = false;}
      if(sztdyWHbEB == true){sztdyWHbEB = false;}
      if(CYqaGUDQKj == true){CYqaGUDQKj = false;}
      if(LEUbbtraXn == true){LEUbbtraXn = false;}
      if(oOJFIHsXUY == true){oOJFIHsXUY = false;}
      if(cGoiPeVDpo == true){cGoiPeVDpo = false;}
      if(XYFSwodSBE == true){XYFSwodSBE = false;}
      if(dgEPMmOkSy == true){dgEPMmOkSy = false;}
      if(bfwkGEOlMx == true){bfwkGEOlMx = false;}
      if(XokhPQIqJT == true){XokhPQIqJT = false;}
      if(cZWQuwCYVb == true){cZWQuwCYVb = false;}
      if(PjkqNrcTLq == true){PjkqNrcTLq = false;}
      if(ZrFEfouVAw == true){ZrFEfouVAw = false;}
      if(eXbzVBIepK == true){eXbzVBIepK = false;}
      if(CpPjgmEtUX == true){CpPjgmEtUX = false;}
      if(nnfRsjTSkF == true){nnfRsjTSkF = false;}
      if(AgYZxrIkVM == true){AgYZxrIkVM = false;}
      if(ixdBojbVXr == true){ixdBojbVXr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCGELPWUUL
{ 
  void PMnYCyCBrE()
  { 
      bool fUhsrPJlPO = false;
      bool ZDjMSHSNSK = false;
      bool ZKdSFPfQKk = false;
      bool xCzmcXqLhI = false;
      bool hONNRAipqj = false;
      bool lYyaZUqOnc = false;
      bool isbeQWDxiu = false;
      bool QHfJbKxQAE = false;
      bool gpZayXDYMI = false;
      bool gbXFZnmhwu = false;
      bool xkGuSdsoyO = false;
      bool XaNiwsTAfs = false;
      bool TdkaOojZjm = false;
      bool XOUFHujdHT = false;
      bool dOaxjFNnJg = false;
      bool UlBDaSAegd = false;
      bool tSEKqIGHaA = false;
      bool JosLOECnpI = false;
      bool auQDSlMQdo = false;
      bool uExdZLJQGb = false;
      string uzBkLJRPch;
      string sJxPuDBYzI;
      string wXQgfFLnMc;
      string DMKHMaauLx;
      string hkQFsWBlRI;
      string FsrnpWiTFG;
      string ycCzdgzoCT;
      string bGMBaLGKmJ;
      string EZVEXJTVRp;
      string qHoFzEiQaM;
      string WLiygyfqMe;
      string PXfwCXGybU;
      string NcXMcTRHCV;
      string cpjalrpXWY;
      string dbImZTarDa;
      string ykoGztnWVM;
      string gXoqCZnFKJ;
      string hiaCpkUklI;
      string sYEaXrAcbq;
      string ESCKrFmRkz;
      if(uzBkLJRPch == WLiygyfqMe){fUhsrPJlPO = true;}
      else if(WLiygyfqMe == uzBkLJRPch){xkGuSdsoyO = true;}
      if(sJxPuDBYzI == PXfwCXGybU){ZDjMSHSNSK = true;}
      else if(PXfwCXGybU == sJxPuDBYzI){XaNiwsTAfs = true;}
      if(wXQgfFLnMc == NcXMcTRHCV){ZKdSFPfQKk = true;}
      else if(NcXMcTRHCV == wXQgfFLnMc){TdkaOojZjm = true;}
      if(DMKHMaauLx == cpjalrpXWY){xCzmcXqLhI = true;}
      else if(cpjalrpXWY == DMKHMaauLx){XOUFHujdHT = true;}
      if(hkQFsWBlRI == dbImZTarDa){hONNRAipqj = true;}
      else if(dbImZTarDa == hkQFsWBlRI){dOaxjFNnJg = true;}
      if(FsrnpWiTFG == ykoGztnWVM){lYyaZUqOnc = true;}
      else if(ykoGztnWVM == FsrnpWiTFG){UlBDaSAegd = true;}
      if(ycCzdgzoCT == gXoqCZnFKJ){isbeQWDxiu = true;}
      else if(gXoqCZnFKJ == ycCzdgzoCT){tSEKqIGHaA = true;}
      if(bGMBaLGKmJ == hiaCpkUklI){QHfJbKxQAE = true;}
      if(EZVEXJTVRp == sYEaXrAcbq){gpZayXDYMI = true;}
      if(qHoFzEiQaM == ESCKrFmRkz){gbXFZnmhwu = true;}
      while(hiaCpkUklI == bGMBaLGKmJ){JosLOECnpI = true;}
      while(sYEaXrAcbq == sYEaXrAcbq){auQDSlMQdo = true;}
      while(ESCKrFmRkz == ESCKrFmRkz){uExdZLJQGb = true;}
      if(fUhsrPJlPO == true){fUhsrPJlPO = false;}
      if(ZDjMSHSNSK == true){ZDjMSHSNSK = false;}
      if(ZKdSFPfQKk == true){ZKdSFPfQKk = false;}
      if(xCzmcXqLhI == true){xCzmcXqLhI = false;}
      if(hONNRAipqj == true){hONNRAipqj = false;}
      if(lYyaZUqOnc == true){lYyaZUqOnc = false;}
      if(isbeQWDxiu == true){isbeQWDxiu = false;}
      if(QHfJbKxQAE == true){QHfJbKxQAE = false;}
      if(gpZayXDYMI == true){gpZayXDYMI = false;}
      if(gbXFZnmhwu == true){gbXFZnmhwu = false;}
      if(xkGuSdsoyO == true){xkGuSdsoyO = false;}
      if(XaNiwsTAfs == true){XaNiwsTAfs = false;}
      if(TdkaOojZjm == true){TdkaOojZjm = false;}
      if(XOUFHujdHT == true){XOUFHujdHT = false;}
      if(dOaxjFNnJg == true){dOaxjFNnJg = false;}
      if(UlBDaSAegd == true){UlBDaSAegd = false;}
      if(tSEKqIGHaA == true){tSEKqIGHaA = false;}
      if(JosLOECnpI == true){JosLOECnpI = false;}
      if(auQDSlMQdo == true){auQDSlMQdo = false;}
      if(uExdZLJQGb == true){uExdZLJQGb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKARFNOUQN
{ 
  void apGsMkVubM()
  { 
      bool pSkDTwHWmg = false;
      bool zyoVYlcFlY = false;
      bool wzQtCNWQkK = false;
      bool qrRwjQlIhB = false;
      bool CwDqwkoeCP = false;
      bool HuEkCqBpAG = false;
      bool ZqlcpGfskI = false;
      bool zUXkVAwYyR = false;
      bool XrOUCungts = false;
      bool OuHabLJZBo = false;
      bool FwssQmXTOC = false;
      bool ucriihbRau = false;
      bool RyzrsDMwIK = false;
      bool pVXJMayUEP = false;
      bool WUSqxlDYrs = false;
      bool iqzFWGxBAM = false;
      bool ZaKDLYEiWI = false;
      bool iHNKXxfHtG = false;
      bool znEPbzWRlF = false;
      bool cwUqpwKOfY = false;
      string tUBwRzojsl;
      string YejGzBicfY;
      string cOYlEObPXZ;
      string ypqYnsMnot;
      string PobsKgHOLn;
      string EfJMjfuPqC;
      string WZLTninLSF;
      string nunlInleaW;
      string GMDjURgdoI;
      string xxwlWpcIFb;
      string rwwFzIqWDu;
      string sQnUwJVbyV;
      string CJVKIqzCOS;
      string LdZydJQyjL;
      string aJatOgIbpM;
      string UAJiZiZkxI;
      string JoHjjPpopl;
      string rXrmuribua;
      string iXLCyKTqYu;
      string ieAaBkBpJz;
      if(tUBwRzojsl == rwwFzIqWDu){pSkDTwHWmg = true;}
      else if(rwwFzIqWDu == tUBwRzojsl){FwssQmXTOC = true;}
      if(YejGzBicfY == sQnUwJVbyV){zyoVYlcFlY = true;}
      else if(sQnUwJVbyV == YejGzBicfY){ucriihbRau = true;}
      if(cOYlEObPXZ == CJVKIqzCOS){wzQtCNWQkK = true;}
      else if(CJVKIqzCOS == cOYlEObPXZ){RyzrsDMwIK = true;}
      if(ypqYnsMnot == LdZydJQyjL){qrRwjQlIhB = true;}
      else if(LdZydJQyjL == ypqYnsMnot){pVXJMayUEP = true;}
      if(PobsKgHOLn == aJatOgIbpM){CwDqwkoeCP = true;}
      else if(aJatOgIbpM == PobsKgHOLn){WUSqxlDYrs = true;}
      if(EfJMjfuPqC == UAJiZiZkxI){HuEkCqBpAG = true;}
      else if(UAJiZiZkxI == EfJMjfuPqC){iqzFWGxBAM = true;}
      if(WZLTninLSF == JoHjjPpopl){ZqlcpGfskI = true;}
      else if(JoHjjPpopl == WZLTninLSF){ZaKDLYEiWI = true;}
      if(nunlInleaW == rXrmuribua){zUXkVAwYyR = true;}
      if(GMDjURgdoI == iXLCyKTqYu){XrOUCungts = true;}
      if(xxwlWpcIFb == ieAaBkBpJz){OuHabLJZBo = true;}
      while(rXrmuribua == nunlInleaW){iHNKXxfHtG = true;}
      while(iXLCyKTqYu == iXLCyKTqYu){znEPbzWRlF = true;}
      while(ieAaBkBpJz == ieAaBkBpJz){cwUqpwKOfY = true;}
      if(pSkDTwHWmg == true){pSkDTwHWmg = false;}
      if(zyoVYlcFlY == true){zyoVYlcFlY = false;}
      if(wzQtCNWQkK == true){wzQtCNWQkK = false;}
      if(qrRwjQlIhB == true){qrRwjQlIhB = false;}
      if(CwDqwkoeCP == true){CwDqwkoeCP = false;}
      if(HuEkCqBpAG == true){HuEkCqBpAG = false;}
      if(ZqlcpGfskI == true){ZqlcpGfskI = false;}
      if(zUXkVAwYyR == true){zUXkVAwYyR = false;}
      if(XrOUCungts == true){XrOUCungts = false;}
      if(OuHabLJZBo == true){OuHabLJZBo = false;}
      if(FwssQmXTOC == true){FwssQmXTOC = false;}
      if(ucriihbRau == true){ucriihbRau = false;}
      if(RyzrsDMwIK == true){RyzrsDMwIK = false;}
      if(pVXJMayUEP == true){pVXJMayUEP = false;}
      if(WUSqxlDYrs == true){WUSqxlDYrs = false;}
      if(iqzFWGxBAM == true){iqzFWGxBAM = false;}
      if(ZaKDLYEiWI == true){ZaKDLYEiWI = false;}
      if(iHNKXxfHtG == true){iHNKXxfHtG = false;}
      if(znEPbzWRlF == true){znEPbzWRlF = false;}
      if(cwUqpwKOfY == true){cwUqpwKOfY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJICHGSAGQ
{ 
  void zFXcVbriWf()
  { 
      bool weeoMhfJYL = false;
      bool xJGZKTNZkq = false;
      bool DkKWxipsUd = false;
      bool OJaUOgxayK = false;
      bool YtwUbDLMCf = false;
      bool hWVMqKTIqd = false;
      bool rlnuwmikKd = false;
      bool VmbZSJoptt = false;
      bool WcqnurnOcE = false;
      bool NniTSlFBXn = false;
      bool TZCYKutush = false;
      bool VdNwGPuzzE = false;
      bool zUHGPgDHHg = false;
      bool DnRGZxaRdz = false;
      bool xrUuijalNC = false;
      bool qFBTnzRuIc = false;
      bool rmnMdhLHWJ = false;
      bool ncVAGHzMXf = false;
      bool GQtEpylxSa = false;
      bool eeJBHKDIQA = false;
      string NjoTzhladN;
      string KjQSOjIdnB;
      string eroXiNTNuN;
      string rZQwKXitzP;
      string kJNUChotpF;
      string OXhyHUtRkk;
      string NYfQUkSTHq;
      string ANdYQUeTVB;
      string XZXoyUqRnp;
      string cRJNBMdxzQ;
      string OUlzEAtJhm;
      string oawiNnBqRA;
      string sAfQNhEPXE;
      string qhTEmCmXjx;
      string ZhjABCVaAM;
      string KlezXNoVkW;
      string wdkdwGGquK;
      string AcGUZLQePL;
      string LcPKsEDUgY;
      string NRmNAwwGEt;
      if(NjoTzhladN == OUlzEAtJhm){weeoMhfJYL = true;}
      else if(OUlzEAtJhm == NjoTzhladN){TZCYKutush = true;}
      if(KjQSOjIdnB == oawiNnBqRA){xJGZKTNZkq = true;}
      else if(oawiNnBqRA == KjQSOjIdnB){VdNwGPuzzE = true;}
      if(eroXiNTNuN == sAfQNhEPXE){DkKWxipsUd = true;}
      else if(sAfQNhEPXE == eroXiNTNuN){zUHGPgDHHg = true;}
      if(rZQwKXitzP == qhTEmCmXjx){OJaUOgxayK = true;}
      else if(qhTEmCmXjx == rZQwKXitzP){DnRGZxaRdz = true;}
      if(kJNUChotpF == ZhjABCVaAM){YtwUbDLMCf = true;}
      else if(ZhjABCVaAM == kJNUChotpF){xrUuijalNC = true;}
      if(OXhyHUtRkk == KlezXNoVkW){hWVMqKTIqd = true;}
      else if(KlezXNoVkW == OXhyHUtRkk){qFBTnzRuIc = true;}
      if(NYfQUkSTHq == wdkdwGGquK){rlnuwmikKd = true;}
      else if(wdkdwGGquK == NYfQUkSTHq){rmnMdhLHWJ = true;}
      if(ANdYQUeTVB == AcGUZLQePL){VmbZSJoptt = true;}
      if(XZXoyUqRnp == LcPKsEDUgY){WcqnurnOcE = true;}
      if(cRJNBMdxzQ == NRmNAwwGEt){NniTSlFBXn = true;}
      while(AcGUZLQePL == ANdYQUeTVB){ncVAGHzMXf = true;}
      while(LcPKsEDUgY == LcPKsEDUgY){GQtEpylxSa = true;}
      while(NRmNAwwGEt == NRmNAwwGEt){eeJBHKDIQA = true;}
      if(weeoMhfJYL == true){weeoMhfJYL = false;}
      if(xJGZKTNZkq == true){xJGZKTNZkq = false;}
      if(DkKWxipsUd == true){DkKWxipsUd = false;}
      if(OJaUOgxayK == true){OJaUOgxayK = false;}
      if(YtwUbDLMCf == true){YtwUbDLMCf = false;}
      if(hWVMqKTIqd == true){hWVMqKTIqd = false;}
      if(rlnuwmikKd == true){rlnuwmikKd = false;}
      if(VmbZSJoptt == true){VmbZSJoptt = false;}
      if(WcqnurnOcE == true){WcqnurnOcE = false;}
      if(NniTSlFBXn == true){NniTSlFBXn = false;}
      if(TZCYKutush == true){TZCYKutush = false;}
      if(VdNwGPuzzE == true){VdNwGPuzzE = false;}
      if(zUHGPgDHHg == true){zUHGPgDHHg = false;}
      if(DnRGZxaRdz == true){DnRGZxaRdz = false;}
      if(xrUuijalNC == true){xrUuijalNC = false;}
      if(qFBTnzRuIc == true){qFBTnzRuIc = false;}
      if(rmnMdhLHWJ == true){rmnMdhLHWJ = false;}
      if(ncVAGHzMXf == true){ncVAGHzMXf = false;}
      if(GQtEpylxSa == true){GQtEpylxSa = false;}
      if(eeJBHKDIQA == true){eeJBHKDIQA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORJIMXPFWH
{ 
  void cPPWwCIefQ()
  { 
      bool oUdRWOiRiB = false;
      bool CSWhQGLqFe = false;
      bool LFBjOADwwW = false;
      bool wWEIkNhyIy = false;
      bool FZIkzuzmxL = false;
      bool jNepAiStCV = false;
      bool KmVMFeOOxC = false;
      bool XNhGYlxQjT = false;
      bool BPyjliqNHB = false;
      bool tnwmmRDweU = false;
      bool fjptmWeYQO = false;
      bool kCKhTtnkZV = false;
      bool mAGuHjQuSH = false;
      bool hBkPmRZExO = false;
      bool ESxsPrdNTs = false;
      bool dSVJhfctlD = false;
      bool FjFJfjQttC = false;
      bool UjnKRTCNeP = false;
      bool GDaZcPebhH = false;
      bool neRsITNnMf = false;
      string GZKccXOQDr;
      string cVACHbmRMj;
      string uXqHtduMkU;
      string mZjsZOrwcH;
      string rwQAjJOENc;
      string mbBLBiiCiz;
      string bBfiECkGbr;
      string ipoEqzGpXj;
      string OqzHhLYYqq;
      string eoNdepQhug;
      string XIbUswmwTC;
      string breyjkCXAr;
      string dMOjMscKZA;
      string hYtpMGOdNl;
      string YbEoPmKPts;
      string msgCDKsrIA;
      string TbWSTDxokc;
      string WYJOTBIZUZ;
      string iMPfNoqqmB;
      string NVVNSwEkUM;
      if(GZKccXOQDr == XIbUswmwTC){oUdRWOiRiB = true;}
      else if(XIbUswmwTC == GZKccXOQDr){fjptmWeYQO = true;}
      if(cVACHbmRMj == breyjkCXAr){CSWhQGLqFe = true;}
      else if(breyjkCXAr == cVACHbmRMj){kCKhTtnkZV = true;}
      if(uXqHtduMkU == dMOjMscKZA){LFBjOADwwW = true;}
      else if(dMOjMscKZA == uXqHtduMkU){mAGuHjQuSH = true;}
      if(mZjsZOrwcH == hYtpMGOdNl){wWEIkNhyIy = true;}
      else if(hYtpMGOdNl == mZjsZOrwcH){hBkPmRZExO = true;}
      if(rwQAjJOENc == YbEoPmKPts){FZIkzuzmxL = true;}
      else if(YbEoPmKPts == rwQAjJOENc){ESxsPrdNTs = true;}
      if(mbBLBiiCiz == msgCDKsrIA){jNepAiStCV = true;}
      else if(msgCDKsrIA == mbBLBiiCiz){dSVJhfctlD = true;}
      if(bBfiECkGbr == TbWSTDxokc){KmVMFeOOxC = true;}
      else if(TbWSTDxokc == bBfiECkGbr){FjFJfjQttC = true;}
      if(ipoEqzGpXj == WYJOTBIZUZ){XNhGYlxQjT = true;}
      if(OqzHhLYYqq == iMPfNoqqmB){BPyjliqNHB = true;}
      if(eoNdepQhug == NVVNSwEkUM){tnwmmRDweU = true;}
      while(WYJOTBIZUZ == ipoEqzGpXj){UjnKRTCNeP = true;}
      while(iMPfNoqqmB == iMPfNoqqmB){GDaZcPebhH = true;}
      while(NVVNSwEkUM == NVVNSwEkUM){neRsITNnMf = true;}
      if(oUdRWOiRiB == true){oUdRWOiRiB = false;}
      if(CSWhQGLqFe == true){CSWhQGLqFe = false;}
      if(LFBjOADwwW == true){LFBjOADwwW = false;}
      if(wWEIkNhyIy == true){wWEIkNhyIy = false;}
      if(FZIkzuzmxL == true){FZIkzuzmxL = false;}
      if(jNepAiStCV == true){jNepAiStCV = false;}
      if(KmVMFeOOxC == true){KmVMFeOOxC = false;}
      if(XNhGYlxQjT == true){XNhGYlxQjT = false;}
      if(BPyjliqNHB == true){BPyjliqNHB = false;}
      if(tnwmmRDweU == true){tnwmmRDweU = false;}
      if(fjptmWeYQO == true){fjptmWeYQO = false;}
      if(kCKhTtnkZV == true){kCKhTtnkZV = false;}
      if(mAGuHjQuSH == true){mAGuHjQuSH = false;}
      if(hBkPmRZExO == true){hBkPmRZExO = false;}
      if(ESxsPrdNTs == true){ESxsPrdNTs = false;}
      if(dSVJhfctlD == true){dSVJhfctlD = false;}
      if(FjFJfjQttC == true){FjFJfjQttC = false;}
      if(UjnKRTCNeP == true){UjnKRTCNeP = false;}
      if(GDaZcPebhH == true){GDaZcPebhH = false;}
      if(neRsITNnMf == true){neRsITNnMf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIPWHTQCJA
{ 
  void IVOWmoZWiX()
  { 
      bool XHZehsJYxg = false;
      bool IcVBKHVySO = false;
      bool FdNqFZiwhw = false;
      bool nRyQZgzPKP = false;
      bool KleZzbSzAI = false;
      bool ehtUMstiYH = false;
      bool KMqAsqeEbd = false;
      bool IFnDESzmqd = false;
      bool GiuYRFWdDf = false;
      bool mPpCExtdgI = false;
      bool xNWWAYsqPs = false;
      bool tGquAaRSim = false;
      bool TBBwprPkyG = false;
      bool YUGifrLXXr = false;
      bool MfNJkgYuBc = false;
      bool fbutnwMagH = false;
      bool JIrJUZAHOI = false;
      bool PstqamnqLJ = false;
      bool TUiUZxZMuj = false;
      bool fkqQiDnDoK = false;
      string EZWqTTsJNr;
      string duQpuHzLbc;
      string BBRrnVrhOk;
      string NgVdmNkaMg;
      string aexlphwaHm;
      string FxbRqDHeDy;
      string aLtcdwYmCg;
      string WXyuCVDeBF;
      string YRaafPEEmi;
      string GFXOFOjUIs;
      string IJXZQgzgOU;
      string AbcxYIkSwN;
      string rUzSaQAiom;
      string kiWIxOtAKy;
      string QXoSidbaow;
      string dRXtBnJFzz;
      string gPqbiQFUAK;
      string OjHyxTegix;
      string nZtrITLbHI;
      string EoBLQAfNiS;
      if(EZWqTTsJNr == IJXZQgzgOU){XHZehsJYxg = true;}
      else if(IJXZQgzgOU == EZWqTTsJNr){xNWWAYsqPs = true;}
      if(duQpuHzLbc == AbcxYIkSwN){IcVBKHVySO = true;}
      else if(AbcxYIkSwN == duQpuHzLbc){tGquAaRSim = true;}
      if(BBRrnVrhOk == rUzSaQAiom){FdNqFZiwhw = true;}
      else if(rUzSaQAiom == BBRrnVrhOk){TBBwprPkyG = true;}
      if(NgVdmNkaMg == kiWIxOtAKy){nRyQZgzPKP = true;}
      else if(kiWIxOtAKy == NgVdmNkaMg){YUGifrLXXr = true;}
      if(aexlphwaHm == QXoSidbaow){KleZzbSzAI = true;}
      else if(QXoSidbaow == aexlphwaHm){MfNJkgYuBc = true;}
      if(FxbRqDHeDy == dRXtBnJFzz){ehtUMstiYH = true;}
      else if(dRXtBnJFzz == FxbRqDHeDy){fbutnwMagH = true;}
      if(aLtcdwYmCg == gPqbiQFUAK){KMqAsqeEbd = true;}
      else if(gPqbiQFUAK == aLtcdwYmCg){JIrJUZAHOI = true;}
      if(WXyuCVDeBF == OjHyxTegix){IFnDESzmqd = true;}
      if(YRaafPEEmi == nZtrITLbHI){GiuYRFWdDf = true;}
      if(GFXOFOjUIs == EoBLQAfNiS){mPpCExtdgI = true;}
      while(OjHyxTegix == WXyuCVDeBF){PstqamnqLJ = true;}
      while(nZtrITLbHI == nZtrITLbHI){TUiUZxZMuj = true;}
      while(EoBLQAfNiS == EoBLQAfNiS){fkqQiDnDoK = true;}
      if(XHZehsJYxg == true){XHZehsJYxg = false;}
      if(IcVBKHVySO == true){IcVBKHVySO = false;}
      if(FdNqFZiwhw == true){FdNqFZiwhw = false;}
      if(nRyQZgzPKP == true){nRyQZgzPKP = false;}
      if(KleZzbSzAI == true){KleZzbSzAI = false;}
      if(ehtUMstiYH == true){ehtUMstiYH = false;}
      if(KMqAsqeEbd == true){KMqAsqeEbd = false;}
      if(IFnDESzmqd == true){IFnDESzmqd = false;}
      if(GiuYRFWdDf == true){GiuYRFWdDf = false;}
      if(mPpCExtdgI == true){mPpCExtdgI = false;}
      if(xNWWAYsqPs == true){xNWWAYsqPs = false;}
      if(tGquAaRSim == true){tGquAaRSim = false;}
      if(TBBwprPkyG == true){TBBwprPkyG = false;}
      if(YUGifrLXXr == true){YUGifrLXXr = false;}
      if(MfNJkgYuBc == true){MfNJkgYuBc = false;}
      if(fbutnwMagH == true){fbutnwMagH = false;}
      if(JIrJUZAHOI == true){JIrJUZAHOI = false;}
      if(PstqamnqLJ == true){PstqamnqLJ = false;}
      if(TUiUZxZMuj == true){TUiUZxZMuj = false;}
      if(fkqQiDnDoK == true){fkqQiDnDoK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNZOJZTOHY
{ 
  void RRDAzZCMkg()
  { 
      bool czcdlLauPG = false;
      bool URIkdOVAWq = false;
      bool UXiIEychwn = false;
      bool ZZPeYPcGIo = false;
      bool RoFWQLjRzG = false;
      bool HtKCNFQTZn = false;
      bool iszagtBcLO = false;
      bool kOrgZfSLrr = false;
      bool NLhofeONQT = false;
      bool zJgUGXpdpV = false;
      bool JHFkVrCcbh = false;
      bool lEbhZWKKtB = false;
      bool fnLqObhXZC = false;
      bool poVViGFxSn = false;
      bool ckkigtgyuj = false;
      bool MeinpUuNVt = false;
      bool JeCZrxiGzS = false;
      bool QNrGYtDcKU = false;
      bool tibpoKFgfN = false;
      bool LrbXdyiKpi = false;
      string LxdLePZFxl;
      string QxzSkIKDqy;
      string DmQMsWRBbA;
      string rqFOTxyzGh;
      string nASdPkBazg;
      string KBddSYgQRI;
      string xYdxsZqjzn;
      string KLwJKCTlwI;
      string VqBtopMauu;
      string PggyjPWUjp;
      string sQaLWzFUTQ;
      string EtTJlGWiHD;
      string NPoEXcdxYt;
      string fyBGOFPpXp;
      string kqHepVMXLd;
      string rmMgccbWmt;
      string UHwYjGrNtg;
      string qfLRRVIJOC;
      string PGkuBskUdl;
      string crCdVduhti;
      if(LxdLePZFxl == sQaLWzFUTQ){czcdlLauPG = true;}
      else if(sQaLWzFUTQ == LxdLePZFxl){JHFkVrCcbh = true;}
      if(QxzSkIKDqy == EtTJlGWiHD){URIkdOVAWq = true;}
      else if(EtTJlGWiHD == QxzSkIKDqy){lEbhZWKKtB = true;}
      if(DmQMsWRBbA == NPoEXcdxYt){UXiIEychwn = true;}
      else if(NPoEXcdxYt == DmQMsWRBbA){fnLqObhXZC = true;}
      if(rqFOTxyzGh == fyBGOFPpXp){ZZPeYPcGIo = true;}
      else if(fyBGOFPpXp == rqFOTxyzGh){poVViGFxSn = true;}
      if(nASdPkBazg == kqHepVMXLd){RoFWQLjRzG = true;}
      else if(kqHepVMXLd == nASdPkBazg){ckkigtgyuj = true;}
      if(KBddSYgQRI == rmMgccbWmt){HtKCNFQTZn = true;}
      else if(rmMgccbWmt == KBddSYgQRI){MeinpUuNVt = true;}
      if(xYdxsZqjzn == UHwYjGrNtg){iszagtBcLO = true;}
      else if(UHwYjGrNtg == xYdxsZqjzn){JeCZrxiGzS = true;}
      if(KLwJKCTlwI == qfLRRVIJOC){kOrgZfSLrr = true;}
      if(VqBtopMauu == PGkuBskUdl){NLhofeONQT = true;}
      if(PggyjPWUjp == crCdVduhti){zJgUGXpdpV = true;}
      while(qfLRRVIJOC == KLwJKCTlwI){QNrGYtDcKU = true;}
      while(PGkuBskUdl == PGkuBskUdl){tibpoKFgfN = true;}
      while(crCdVduhti == crCdVduhti){LrbXdyiKpi = true;}
      if(czcdlLauPG == true){czcdlLauPG = false;}
      if(URIkdOVAWq == true){URIkdOVAWq = false;}
      if(UXiIEychwn == true){UXiIEychwn = false;}
      if(ZZPeYPcGIo == true){ZZPeYPcGIo = false;}
      if(RoFWQLjRzG == true){RoFWQLjRzG = false;}
      if(HtKCNFQTZn == true){HtKCNFQTZn = false;}
      if(iszagtBcLO == true){iszagtBcLO = false;}
      if(kOrgZfSLrr == true){kOrgZfSLrr = false;}
      if(NLhofeONQT == true){NLhofeONQT = false;}
      if(zJgUGXpdpV == true){zJgUGXpdpV = false;}
      if(JHFkVrCcbh == true){JHFkVrCcbh = false;}
      if(lEbhZWKKtB == true){lEbhZWKKtB = false;}
      if(fnLqObhXZC == true){fnLqObhXZC = false;}
      if(poVViGFxSn == true){poVViGFxSn = false;}
      if(ckkigtgyuj == true){ckkigtgyuj = false;}
      if(MeinpUuNVt == true){MeinpUuNVt = false;}
      if(JeCZrxiGzS == true){JeCZrxiGzS = false;}
      if(QNrGYtDcKU == true){QNrGYtDcKU = false;}
      if(tibpoKFgfN == true){tibpoKFgfN = false;}
      if(LrbXdyiKpi == true){LrbXdyiKpi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMHVTKKNXF
{ 
  void sSqgDFGlig()
  { 
      bool VtgmYJnPff = false;
      bool VEuarucoYW = false;
      bool fBepktIfHW = false;
      bool KPQSuQczmM = false;
      bool lnylCrEUdw = false;
      bool JbtEMUPpCe = false;
      bool AHHJVGncea = false;
      bool RcBLjrCrnr = false;
      bool onCLMhULFa = false;
      bool BlwIMefoPu = false;
      bool EbpCdfaiTU = false;
      bool RWCKoLEwxn = false;
      bool kbWDZegsyF = false;
      bool LNcrmNxzgf = false;
      bool HlrkIejlSA = false;
      bool ZjrbJcElcy = false;
      bool zgjOIEtJWb = false;
      bool NFOQfziluu = false;
      bool utZyebUAhK = false;
      bool ILWifZCdbE = false;
      string iUWmHoUOJe;
      string hEtxnfwgko;
      string OwBXSZedFG;
      string wmOnWUNFdg;
      string ycPhwpSYeY;
      string AYlVAlSzTh;
      string JqJChtoFaT;
      string RpDEqkgTbc;
      string GGyfGWAsnj;
      string BOkwWGTMzB;
      string ANyKGJVheO;
      string FzXpaDrcwK;
      string swQpSCEHgj;
      string QUTZcsInZw;
      string BSNYdBqtUT;
      string NpPoHEwHrD;
      string FOBtxkfxNh;
      string uECzJahrLR;
      string LJlMVaEeSX;
      string xAuWqlQSbs;
      if(iUWmHoUOJe == ANyKGJVheO){VtgmYJnPff = true;}
      else if(ANyKGJVheO == iUWmHoUOJe){EbpCdfaiTU = true;}
      if(hEtxnfwgko == FzXpaDrcwK){VEuarucoYW = true;}
      else if(FzXpaDrcwK == hEtxnfwgko){RWCKoLEwxn = true;}
      if(OwBXSZedFG == swQpSCEHgj){fBepktIfHW = true;}
      else if(swQpSCEHgj == OwBXSZedFG){kbWDZegsyF = true;}
      if(wmOnWUNFdg == QUTZcsInZw){KPQSuQczmM = true;}
      else if(QUTZcsInZw == wmOnWUNFdg){LNcrmNxzgf = true;}
      if(ycPhwpSYeY == BSNYdBqtUT){lnylCrEUdw = true;}
      else if(BSNYdBqtUT == ycPhwpSYeY){HlrkIejlSA = true;}
      if(AYlVAlSzTh == NpPoHEwHrD){JbtEMUPpCe = true;}
      else if(NpPoHEwHrD == AYlVAlSzTh){ZjrbJcElcy = true;}
      if(JqJChtoFaT == FOBtxkfxNh){AHHJVGncea = true;}
      else if(FOBtxkfxNh == JqJChtoFaT){zgjOIEtJWb = true;}
      if(RpDEqkgTbc == uECzJahrLR){RcBLjrCrnr = true;}
      if(GGyfGWAsnj == LJlMVaEeSX){onCLMhULFa = true;}
      if(BOkwWGTMzB == xAuWqlQSbs){BlwIMefoPu = true;}
      while(uECzJahrLR == RpDEqkgTbc){NFOQfziluu = true;}
      while(LJlMVaEeSX == LJlMVaEeSX){utZyebUAhK = true;}
      while(xAuWqlQSbs == xAuWqlQSbs){ILWifZCdbE = true;}
      if(VtgmYJnPff == true){VtgmYJnPff = false;}
      if(VEuarucoYW == true){VEuarucoYW = false;}
      if(fBepktIfHW == true){fBepktIfHW = false;}
      if(KPQSuQczmM == true){KPQSuQczmM = false;}
      if(lnylCrEUdw == true){lnylCrEUdw = false;}
      if(JbtEMUPpCe == true){JbtEMUPpCe = false;}
      if(AHHJVGncea == true){AHHJVGncea = false;}
      if(RcBLjrCrnr == true){RcBLjrCrnr = false;}
      if(onCLMhULFa == true){onCLMhULFa = false;}
      if(BlwIMefoPu == true){BlwIMefoPu = false;}
      if(EbpCdfaiTU == true){EbpCdfaiTU = false;}
      if(RWCKoLEwxn == true){RWCKoLEwxn = false;}
      if(kbWDZegsyF == true){kbWDZegsyF = false;}
      if(LNcrmNxzgf == true){LNcrmNxzgf = false;}
      if(HlrkIejlSA == true){HlrkIejlSA = false;}
      if(ZjrbJcElcy == true){ZjrbJcElcy = false;}
      if(zgjOIEtJWb == true){zgjOIEtJWb = false;}
      if(NFOQfziluu == true){NFOQfziluu = false;}
      if(utZyebUAhK == true){utZyebUAhK = false;}
      if(ILWifZCdbE == true){ILWifZCdbE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUBQBRGTZJ
{ 
  void dYmdKqfzWy()
  { 
      bool YyfFkJTKym = false;
      bool SHVpZNeqTJ = false;
      bool WufQZYosEb = false;
      bool jpkoErFeWG = false;
      bool HtPlzHbMbI = false;
      bool LZVracROfM = false;
      bool UaGVDcWgkh = false;
      bool HATNBbftRR = false;
      bool wbQuQJUrNb = false;
      bool ZpyKlgmshW = false;
      bool kubtAKFIpz = false;
      bool xXxOPrJKFs = false;
      bool HdSJIRBJaU = false;
      bool nmLtfBAWuF = false;
      bool EMBOeBrjtt = false;
      bool WcmnOGbRki = false;
      bool IugVKJMDhN = false;
      bool qmPzoucDeH = false;
      bool YROgyLzWeY = false;
      bool YikLwIffEU = false;
      string IOGhWNizHC;
      string mtAjbfHBuM;
      string mTySJqFSIp;
      string YrLKfpMoat;
      string eTxXzmKaQe;
      string TVOiunQmXf;
      string IPqQdthoEk;
      string TSZAgTWZTW;
      string fdCdVCdbOq;
      string YYQulPcfsF;
      string EVWfLAuNCb;
      string RpTBAdNNua;
      string QGZMMuBeOR;
      string ppgNRKHVSU;
      string HPZmZhEPuH;
      string BOkSnyuJTQ;
      string zPyjkbJFjo;
      string WquZTAfmmd;
      string pljHQbENZS;
      string PyCCVqQoCx;
      if(IOGhWNizHC == EVWfLAuNCb){YyfFkJTKym = true;}
      else if(EVWfLAuNCb == IOGhWNizHC){kubtAKFIpz = true;}
      if(mtAjbfHBuM == RpTBAdNNua){SHVpZNeqTJ = true;}
      else if(RpTBAdNNua == mtAjbfHBuM){xXxOPrJKFs = true;}
      if(mTySJqFSIp == QGZMMuBeOR){WufQZYosEb = true;}
      else if(QGZMMuBeOR == mTySJqFSIp){HdSJIRBJaU = true;}
      if(YrLKfpMoat == ppgNRKHVSU){jpkoErFeWG = true;}
      else if(ppgNRKHVSU == YrLKfpMoat){nmLtfBAWuF = true;}
      if(eTxXzmKaQe == HPZmZhEPuH){HtPlzHbMbI = true;}
      else if(HPZmZhEPuH == eTxXzmKaQe){EMBOeBrjtt = true;}
      if(TVOiunQmXf == BOkSnyuJTQ){LZVracROfM = true;}
      else if(BOkSnyuJTQ == TVOiunQmXf){WcmnOGbRki = true;}
      if(IPqQdthoEk == zPyjkbJFjo){UaGVDcWgkh = true;}
      else if(zPyjkbJFjo == IPqQdthoEk){IugVKJMDhN = true;}
      if(TSZAgTWZTW == WquZTAfmmd){HATNBbftRR = true;}
      if(fdCdVCdbOq == pljHQbENZS){wbQuQJUrNb = true;}
      if(YYQulPcfsF == PyCCVqQoCx){ZpyKlgmshW = true;}
      while(WquZTAfmmd == TSZAgTWZTW){qmPzoucDeH = true;}
      while(pljHQbENZS == pljHQbENZS){YROgyLzWeY = true;}
      while(PyCCVqQoCx == PyCCVqQoCx){YikLwIffEU = true;}
      if(YyfFkJTKym == true){YyfFkJTKym = false;}
      if(SHVpZNeqTJ == true){SHVpZNeqTJ = false;}
      if(WufQZYosEb == true){WufQZYosEb = false;}
      if(jpkoErFeWG == true){jpkoErFeWG = false;}
      if(HtPlzHbMbI == true){HtPlzHbMbI = false;}
      if(LZVracROfM == true){LZVracROfM = false;}
      if(UaGVDcWgkh == true){UaGVDcWgkh = false;}
      if(HATNBbftRR == true){HATNBbftRR = false;}
      if(wbQuQJUrNb == true){wbQuQJUrNb = false;}
      if(ZpyKlgmshW == true){ZpyKlgmshW = false;}
      if(kubtAKFIpz == true){kubtAKFIpz = false;}
      if(xXxOPrJKFs == true){xXxOPrJKFs = false;}
      if(HdSJIRBJaU == true){HdSJIRBJaU = false;}
      if(nmLtfBAWuF == true){nmLtfBAWuF = false;}
      if(EMBOeBrjtt == true){EMBOeBrjtt = false;}
      if(WcmnOGbRki == true){WcmnOGbRki = false;}
      if(IugVKJMDhN == true){IugVKJMDhN = false;}
      if(qmPzoucDeH == true){qmPzoucDeH = false;}
      if(YROgyLzWeY == true){YROgyLzWeY = false;}
      if(YikLwIffEU == true){YikLwIffEU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLALVRORVQ
{ 
  void qMaDhLnfxN()
  { 
      bool lgOfrxrahr = false;
      bool xHMAJDFXzW = false;
      bool erUiZQDyCn = false;
      bool fsBCZUKkph = false;
      bool sUhSZMlyDr = false;
      bool apHiPtLfGa = false;
      bool tsXtMEGKan = false;
      bool rUhQdJJBIN = false;
      bool dFuJNokSle = false;
      bool IeeOmzwnFV = false;
      bool FbWOAFIpEF = false;
      bool jJXrxoyNfX = false;
      bool SnXueMpSdd = false;
      bool MVulHChfJH = false;
      bool fuNguzHlRy = false;
      bool BhHhDREbjm = false;
      bool PoLZrONkju = false;
      bool GSEYqWZqAf = false;
      bool FEBfcdNNhp = false;
      bool yGwVqpimnf = false;
      string oFQmjuSHZe;
      string TcOGhcKAIu;
      string sdbkMkobbH;
      string ilxhZDWUDl;
      string DRNajMQGye;
      string MNTCXKdeZy;
      string GqfRuheffe;
      string FoxWraPAAA;
      string UhdwuURuKP;
      string YqtEfMlueC;
      string gkZSYWPxJw;
      string tdeZdXMiWa;
      string PjUQGOtrpe;
      string nUUyTiIKXX;
      string EUkNUtMUaH;
      string zDYEmwPIMK;
      string cXGeHZIfGt;
      string PBLyVtzHwL;
      string BZRhfkuQLW;
      string TzyMugOGFt;
      if(oFQmjuSHZe == gkZSYWPxJw){lgOfrxrahr = true;}
      else if(gkZSYWPxJw == oFQmjuSHZe){FbWOAFIpEF = true;}
      if(TcOGhcKAIu == tdeZdXMiWa){xHMAJDFXzW = true;}
      else if(tdeZdXMiWa == TcOGhcKAIu){jJXrxoyNfX = true;}
      if(sdbkMkobbH == PjUQGOtrpe){erUiZQDyCn = true;}
      else if(PjUQGOtrpe == sdbkMkobbH){SnXueMpSdd = true;}
      if(ilxhZDWUDl == nUUyTiIKXX){fsBCZUKkph = true;}
      else if(nUUyTiIKXX == ilxhZDWUDl){MVulHChfJH = true;}
      if(DRNajMQGye == EUkNUtMUaH){sUhSZMlyDr = true;}
      else if(EUkNUtMUaH == DRNajMQGye){fuNguzHlRy = true;}
      if(MNTCXKdeZy == zDYEmwPIMK){apHiPtLfGa = true;}
      else if(zDYEmwPIMK == MNTCXKdeZy){BhHhDREbjm = true;}
      if(GqfRuheffe == cXGeHZIfGt){tsXtMEGKan = true;}
      else if(cXGeHZIfGt == GqfRuheffe){PoLZrONkju = true;}
      if(FoxWraPAAA == PBLyVtzHwL){rUhQdJJBIN = true;}
      if(UhdwuURuKP == BZRhfkuQLW){dFuJNokSle = true;}
      if(YqtEfMlueC == TzyMugOGFt){IeeOmzwnFV = true;}
      while(PBLyVtzHwL == FoxWraPAAA){GSEYqWZqAf = true;}
      while(BZRhfkuQLW == BZRhfkuQLW){FEBfcdNNhp = true;}
      while(TzyMugOGFt == TzyMugOGFt){yGwVqpimnf = true;}
      if(lgOfrxrahr == true){lgOfrxrahr = false;}
      if(xHMAJDFXzW == true){xHMAJDFXzW = false;}
      if(erUiZQDyCn == true){erUiZQDyCn = false;}
      if(fsBCZUKkph == true){fsBCZUKkph = false;}
      if(sUhSZMlyDr == true){sUhSZMlyDr = false;}
      if(apHiPtLfGa == true){apHiPtLfGa = false;}
      if(tsXtMEGKan == true){tsXtMEGKan = false;}
      if(rUhQdJJBIN == true){rUhQdJJBIN = false;}
      if(dFuJNokSle == true){dFuJNokSle = false;}
      if(IeeOmzwnFV == true){IeeOmzwnFV = false;}
      if(FbWOAFIpEF == true){FbWOAFIpEF = false;}
      if(jJXrxoyNfX == true){jJXrxoyNfX = false;}
      if(SnXueMpSdd == true){SnXueMpSdd = false;}
      if(MVulHChfJH == true){MVulHChfJH = false;}
      if(fuNguzHlRy == true){fuNguzHlRy = false;}
      if(BhHhDREbjm == true){BhHhDREbjm = false;}
      if(PoLZrONkju == true){PoLZrONkju = false;}
      if(GSEYqWZqAf == true){GSEYqWZqAf = false;}
      if(FEBfcdNNhp == true){FEBfcdNNhp = false;}
      if(yGwVqpimnf == true){yGwVqpimnf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJFSKLHTOG
{ 
  void fRODTLduPB()
  { 
      bool RLkDxyriiZ = false;
      bool ZhGcebfWtz = false;
      bool WcIjmjneRA = false;
      bool ZKTNAoThXC = false;
      bool ljcjqMmynt = false;
      bool wHODEoCBQM = false;
      bool KMRiAONsbo = false;
      bool HyzqNmAXsZ = false;
      bool xopWDRuQJL = false;
      bool mSRLrYSsjb = false;
      bool ztWzmyIXpR = false;
      bool neHpOUWtfh = false;
      bool SxjPCogmzn = false;
      bool UGmQZDSpjF = false;
      bool JXZqWHKawW = false;
      bool CXMCICKHxy = false;
      bool RUXBxhqqPL = false;
      bool CfJaYuWrrt = false;
      bool dFqblwtkIX = false;
      bool sLslmnAXto = false;
      string fXxihVktJW;
      string kkNtmIezJu;
      string DqArqsEHlo;
      string PxshnrqoIO;
      string duiquLlKPb;
      string NfjbFoWEqo;
      string QdHTHnqeGt;
      string RoquQIHJwf;
      string GtqJbiMQcz;
      string UlyTyAnPjH;
      string UGDUKXooLx;
      string gNILhVlxrX;
      string bZCHZeqWxP;
      string TqYoKzqWzD;
      string tWFeRGdllb;
      string OpXMetEwuf;
      string gRrucpoSAh;
      string ePyncEUWoS;
      string BFkUBdTMKQ;
      string utaTWceJCa;
      if(fXxihVktJW == UGDUKXooLx){RLkDxyriiZ = true;}
      else if(UGDUKXooLx == fXxihVktJW){ztWzmyIXpR = true;}
      if(kkNtmIezJu == gNILhVlxrX){ZhGcebfWtz = true;}
      else if(gNILhVlxrX == kkNtmIezJu){neHpOUWtfh = true;}
      if(DqArqsEHlo == bZCHZeqWxP){WcIjmjneRA = true;}
      else if(bZCHZeqWxP == DqArqsEHlo){SxjPCogmzn = true;}
      if(PxshnrqoIO == TqYoKzqWzD){ZKTNAoThXC = true;}
      else if(TqYoKzqWzD == PxshnrqoIO){UGmQZDSpjF = true;}
      if(duiquLlKPb == tWFeRGdllb){ljcjqMmynt = true;}
      else if(tWFeRGdllb == duiquLlKPb){JXZqWHKawW = true;}
      if(NfjbFoWEqo == OpXMetEwuf){wHODEoCBQM = true;}
      else if(OpXMetEwuf == NfjbFoWEqo){CXMCICKHxy = true;}
      if(QdHTHnqeGt == gRrucpoSAh){KMRiAONsbo = true;}
      else if(gRrucpoSAh == QdHTHnqeGt){RUXBxhqqPL = true;}
      if(RoquQIHJwf == ePyncEUWoS){HyzqNmAXsZ = true;}
      if(GtqJbiMQcz == BFkUBdTMKQ){xopWDRuQJL = true;}
      if(UlyTyAnPjH == utaTWceJCa){mSRLrYSsjb = true;}
      while(ePyncEUWoS == RoquQIHJwf){CfJaYuWrrt = true;}
      while(BFkUBdTMKQ == BFkUBdTMKQ){dFqblwtkIX = true;}
      while(utaTWceJCa == utaTWceJCa){sLslmnAXto = true;}
      if(RLkDxyriiZ == true){RLkDxyriiZ = false;}
      if(ZhGcebfWtz == true){ZhGcebfWtz = false;}
      if(WcIjmjneRA == true){WcIjmjneRA = false;}
      if(ZKTNAoThXC == true){ZKTNAoThXC = false;}
      if(ljcjqMmynt == true){ljcjqMmynt = false;}
      if(wHODEoCBQM == true){wHODEoCBQM = false;}
      if(KMRiAONsbo == true){KMRiAONsbo = false;}
      if(HyzqNmAXsZ == true){HyzqNmAXsZ = false;}
      if(xopWDRuQJL == true){xopWDRuQJL = false;}
      if(mSRLrYSsjb == true){mSRLrYSsjb = false;}
      if(ztWzmyIXpR == true){ztWzmyIXpR = false;}
      if(neHpOUWtfh == true){neHpOUWtfh = false;}
      if(SxjPCogmzn == true){SxjPCogmzn = false;}
      if(UGmQZDSpjF == true){UGmQZDSpjF = false;}
      if(JXZqWHKawW == true){JXZqWHKawW = false;}
      if(CXMCICKHxy == true){CXMCICKHxy = false;}
      if(RUXBxhqqPL == true){RUXBxhqqPL = false;}
      if(CfJaYuWrrt == true){CfJaYuWrrt = false;}
      if(dFqblwtkIX == true){dFqblwtkIX = false;}
      if(sLslmnAXto == true){sLslmnAXto = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOXBVVTBIV
{ 
  void hxKDaNKNII()
  { 
      bool ZsZAeTEEFH = false;
      bool UGfcCbJLiJ = false;
      bool kZtbwDDBXC = false;
      bool RzuDGyPyje = false;
      bool dTZMMXXFjr = false;
      bool wOCHqAzxEa = false;
      bool QCfCoVKcVE = false;
      bool MLbEfQzgPY = false;
      bool fxReGDxnLG = false;
      bool zRsIOanXXp = false;
      bool Ntiffjlxaa = false;
      bool ARgeuSkAul = false;
      bool YVQPEtSToE = false;
      bool bbJZLkNlzW = false;
      bool QzMkFgjOMu = false;
      bool pmbkQqcTak = false;
      bool RRHWyYIHTJ = false;
      bool EzBYUZIfJX = false;
      bool JDGtNozXJT = false;
      bool IsKNFzqplg = false;
      string OUgOsPQHjb;
      string rrkdzikkiN;
      string ujohSgBYMb;
      string FSgjwJpdLX;
      string ZHkISUrJLl;
      string yHnaGeeyuM;
      string OquIVYKBhp;
      string rHYLmmyfOx;
      string nqNacyeGcR;
      string drhzJiMclt;
      string JqbVtqicmS;
      string fyjxXWdUeX;
      string tEXQLAZZBE;
      string aVsUmxPrfl;
      string OBTJkeIjam;
      string FrxOzFTLJt;
      string RIahrJFOKZ;
      string HknsIrjNeg;
      string qoyOzhYeUh;
      string dDhlUGakRb;
      if(OUgOsPQHjb == JqbVtqicmS){ZsZAeTEEFH = true;}
      else if(JqbVtqicmS == OUgOsPQHjb){Ntiffjlxaa = true;}
      if(rrkdzikkiN == fyjxXWdUeX){UGfcCbJLiJ = true;}
      else if(fyjxXWdUeX == rrkdzikkiN){ARgeuSkAul = true;}
      if(ujohSgBYMb == tEXQLAZZBE){kZtbwDDBXC = true;}
      else if(tEXQLAZZBE == ujohSgBYMb){YVQPEtSToE = true;}
      if(FSgjwJpdLX == aVsUmxPrfl){RzuDGyPyje = true;}
      else if(aVsUmxPrfl == FSgjwJpdLX){bbJZLkNlzW = true;}
      if(ZHkISUrJLl == OBTJkeIjam){dTZMMXXFjr = true;}
      else if(OBTJkeIjam == ZHkISUrJLl){QzMkFgjOMu = true;}
      if(yHnaGeeyuM == FrxOzFTLJt){wOCHqAzxEa = true;}
      else if(FrxOzFTLJt == yHnaGeeyuM){pmbkQqcTak = true;}
      if(OquIVYKBhp == RIahrJFOKZ){QCfCoVKcVE = true;}
      else if(RIahrJFOKZ == OquIVYKBhp){RRHWyYIHTJ = true;}
      if(rHYLmmyfOx == HknsIrjNeg){MLbEfQzgPY = true;}
      if(nqNacyeGcR == qoyOzhYeUh){fxReGDxnLG = true;}
      if(drhzJiMclt == dDhlUGakRb){zRsIOanXXp = true;}
      while(HknsIrjNeg == rHYLmmyfOx){EzBYUZIfJX = true;}
      while(qoyOzhYeUh == qoyOzhYeUh){JDGtNozXJT = true;}
      while(dDhlUGakRb == dDhlUGakRb){IsKNFzqplg = true;}
      if(ZsZAeTEEFH == true){ZsZAeTEEFH = false;}
      if(UGfcCbJLiJ == true){UGfcCbJLiJ = false;}
      if(kZtbwDDBXC == true){kZtbwDDBXC = false;}
      if(RzuDGyPyje == true){RzuDGyPyje = false;}
      if(dTZMMXXFjr == true){dTZMMXXFjr = false;}
      if(wOCHqAzxEa == true){wOCHqAzxEa = false;}
      if(QCfCoVKcVE == true){QCfCoVKcVE = false;}
      if(MLbEfQzgPY == true){MLbEfQzgPY = false;}
      if(fxReGDxnLG == true){fxReGDxnLG = false;}
      if(zRsIOanXXp == true){zRsIOanXXp = false;}
      if(Ntiffjlxaa == true){Ntiffjlxaa = false;}
      if(ARgeuSkAul == true){ARgeuSkAul = false;}
      if(YVQPEtSToE == true){YVQPEtSToE = false;}
      if(bbJZLkNlzW == true){bbJZLkNlzW = false;}
      if(QzMkFgjOMu == true){QzMkFgjOMu = false;}
      if(pmbkQqcTak == true){pmbkQqcTak = false;}
      if(RRHWyYIHTJ == true){RRHWyYIHTJ = false;}
      if(EzBYUZIfJX == true){EzBYUZIfJX = false;}
      if(JDGtNozXJT == true){JDGtNozXJT = false;}
      if(IsKNFzqplg == true){IsKNFzqplg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIILVEMWSI
{ 
  void JrRoFgOCGk()
  { 
      bool pJqLWSxEpX = false;
      bool ttcYbjSMCI = false;
      bool bhsEtSNZEJ = false;
      bool KNKkhfaiOu = false;
      bool khnWkVHfgh = false;
      bool bUSPxIQlRD = false;
      bool EXAgMfjrqw = false;
      bool IiyGWssVTY = false;
      bool LhrWgpttnZ = false;
      bool OnRKqNhGKE = false;
      bool lPokYsWMrD = false;
      bool OtSsrWfcAV = false;
      bool koDQhTRmOJ = false;
      bool LmKOlwsHyn = false;
      bool ShCjLTVXSU = false;
      bool gEFnTwLXDE = false;
      bool ajxirbiEGw = false;
      bool cXeMDDlTFN = false;
      bool ysUtbGgVup = false;
      bool jUEsMikTrj = false;
      string WSBUjPKTeT;
      string hyNCcgZpOJ;
      string yIwCYNXOZW;
      string PTbrhMuNww;
      string CnaMDTuJoq;
      string GZcYTNVyuV;
      string rutHDOWVUQ;
      string kLsRHKhizE;
      string SNZhPppCXU;
      string pxRaEGsSIn;
      string wZoXGugKQI;
      string emzqDdULqN;
      string XTxAansSMA;
      string QPZKHrYBbU;
      string JfkPoCyaWa;
      string lhbuPbbnxR;
      string CNyQqPMnjK;
      string ESjWErhhKX;
      string oRukOimete;
      string QkEJRugUXZ;
      if(WSBUjPKTeT == wZoXGugKQI){pJqLWSxEpX = true;}
      else if(wZoXGugKQI == WSBUjPKTeT){lPokYsWMrD = true;}
      if(hyNCcgZpOJ == emzqDdULqN){ttcYbjSMCI = true;}
      else if(emzqDdULqN == hyNCcgZpOJ){OtSsrWfcAV = true;}
      if(yIwCYNXOZW == XTxAansSMA){bhsEtSNZEJ = true;}
      else if(XTxAansSMA == yIwCYNXOZW){koDQhTRmOJ = true;}
      if(PTbrhMuNww == QPZKHrYBbU){KNKkhfaiOu = true;}
      else if(QPZKHrYBbU == PTbrhMuNww){LmKOlwsHyn = true;}
      if(CnaMDTuJoq == JfkPoCyaWa){khnWkVHfgh = true;}
      else if(JfkPoCyaWa == CnaMDTuJoq){ShCjLTVXSU = true;}
      if(GZcYTNVyuV == lhbuPbbnxR){bUSPxIQlRD = true;}
      else if(lhbuPbbnxR == GZcYTNVyuV){gEFnTwLXDE = true;}
      if(rutHDOWVUQ == CNyQqPMnjK){EXAgMfjrqw = true;}
      else if(CNyQqPMnjK == rutHDOWVUQ){ajxirbiEGw = true;}
      if(kLsRHKhizE == ESjWErhhKX){IiyGWssVTY = true;}
      if(SNZhPppCXU == oRukOimete){LhrWgpttnZ = true;}
      if(pxRaEGsSIn == QkEJRugUXZ){OnRKqNhGKE = true;}
      while(ESjWErhhKX == kLsRHKhizE){cXeMDDlTFN = true;}
      while(oRukOimete == oRukOimete){ysUtbGgVup = true;}
      while(QkEJRugUXZ == QkEJRugUXZ){jUEsMikTrj = true;}
      if(pJqLWSxEpX == true){pJqLWSxEpX = false;}
      if(ttcYbjSMCI == true){ttcYbjSMCI = false;}
      if(bhsEtSNZEJ == true){bhsEtSNZEJ = false;}
      if(KNKkhfaiOu == true){KNKkhfaiOu = false;}
      if(khnWkVHfgh == true){khnWkVHfgh = false;}
      if(bUSPxIQlRD == true){bUSPxIQlRD = false;}
      if(EXAgMfjrqw == true){EXAgMfjrqw = false;}
      if(IiyGWssVTY == true){IiyGWssVTY = false;}
      if(LhrWgpttnZ == true){LhrWgpttnZ = false;}
      if(OnRKqNhGKE == true){OnRKqNhGKE = false;}
      if(lPokYsWMrD == true){lPokYsWMrD = false;}
      if(OtSsrWfcAV == true){OtSsrWfcAV = false;}
      if(koDQhTRmOJ == true){koDQhTRmOJ = false;}
      if(LmKOlwsHyn == true){LmKOlwsHyn = false;}
      if(ShCjLTVXSU == true){ShCjLTVXSU = false;}
      if(gEFnTwLXDE == true){gEFnTwLXDE = false;}
      if(ajxirbiEGw == true){ajxirbiEGw = false;}
      if(cXeMDDlTFN == true){cXeMDDlTFN = false;}
      if(ysUtbGgVup == true){ysUtbGgVup = false;}
      if(jUEsMikTrj == true){jUEsMikTrj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHNCSHYZCX
{ 
  void EBXhFdqSec()
  { 
      bool HucWHPGquA = false;
      bool YxgzQhgVGK = false;
      bool CaGtgefHPm = false;
      bool QHfkCSfjrl = false;
      bool rWGldlxIMl = false;
      bool kbgKYfohpb = false;
      bool jzaIjQRuwy = false;
      bool CwdTSeUTPt = false;
      bool gWtdCoaULW = false;
      bool dxsPCrwxCN = false;
      bool UCMOjnxNqt = false;
      bool LURwtNEwGt = false;
      bool pwiZUEDNRZ = false;
      bool hWQCZeKetO = false;
      bool qNcRKIexUn = false;
      bool nzqIXXSlte = false;
      bool jjuQLnEPVP = false;
      bool DZCrCbSROL = false;
      bool ZGrclhfIeC = false;
      bool LXjOdHRMFW = false;
      string sKYDdYLwgI;
      string muXVORksOE;
      string CXTexLViKw;
      string JCrKSFeDHA;
      string mXJIfOtANT;
      string JUzgdUptFR;
      string CbkjyjCNCJ;
      string mhkNRdOLyi;
      string QVVpmoDLfy;
      string OjxoyKmYJw;
      string LgxEgaikPA;
      string GeuVBgGtxJ;
      string gqgEtCjuPG;
      string qpBCXjXRIL;
      string FRueqjnanQ;
      string ErbAPUzsJe;
      string qnUIJPcsyQ;
      string JnkkEOuBMK;
      string NIHzCyNBmD;
      string jdIdURxmVa;
      if(sKYDdYLwgI == LgxEgaikPA){HucWHPGquA = true;}
      else if(LgxEgaikPA == sKYDdYLwgI){UCMOjnxNqt = true;}
      if(muXVORksOE == GeuVBgGtxJ){YxgzQhgVGK = true;}
      else if(GeuVBgGtxJ == muXVORksOE){LURwtNEwGt = true;}
      if(CXTexLViKw == gqgEtCjuPG){CaGtgefHPm = true;}
      else if(gqgEtCjuPG == CXTexLViKw){pwiZUEDNRZ = true;}
      if(JCrKSFeDHA == qpBCXjXRIL){QHfkCSfjrl = true;}
      else if(qpBCXjXRIL == JCrKSFeDHA){hWQCZeKetO = true;}
      if(mXJIfOtANT == FRueqjnanQ){rWGldlxIMl = true;}
      else if(FRueqjnanQ == mXJIfOtANT){qNcRKIexUn = true;}
      if(JUzgdUptFR == ErbAPUzsJe){kbgKYfohpb = true;}
      else if(ErbAPUzsJe == JUzgdUptFR){nzqIXXSlte = true;}
      if(CbkjyjCNCJ == qnUIJPcsyQ){jzaIjQRuwy = true;}
      else if(qnUIJPcsyQ == CbkjyjCNCJ){jjuQLnEPVP = true;}
      if(mhkNRdOLyi == JnkkEOuBMK){CwdTSeUTPt = true;}
      if(QVVpmoDLfy == NIHzCyNBmD){gWtdCoaULW = true;}
      if(OjxoyKmYJw == jdIdURxmVa){dxsPCrwxCN = true;}
      while(JnkkEOuBMK == mhkNRdOLyi){DZCrCbSROL = true;}
      while(NIHzCyNBmD == NIHzCyNBmD){ZGrclhfIeC = true;}
      while(jdIdURxmVa == jdIdURxmVa){LXjOdHRMFW = true;}
      if(HucWHPGquA == true){HucWHPGquA = false;}
      if(YxgzQhgVGK == true){YxgzQhgVGK = false;}
      if(CaGtgefHPm == true){CaGtgefHPm = false;}
      if(QHfkCSfjrl == true){QHfkCSfjrl = false;}
      if(rWGldlxIMl == true){rWGldlxIMl = false;}
      if(kbgKYfohpb == true){kbgKYfohpb = false;}
      if(jzaIjQRuwy == true){jzaIjQRuwy = false;}
      if(CwdTSeUTPt == true){CwdTSeUTPt = false;}
      if(gWtdCoaULW == true){gWtdCoaULW = false;}
      if(dxsPCrwxCN == true){dxsPCrwxCN = false;}
      if(UCMOjnxNqt == true){UCMOjnxNqt = false;}
      if(LURwtNEwGt == true){LURwtNEwGt = false;}
      if(pwiZUEDNRZ == true){pwiZUEDNRZ = false;}
      if(hWQCZeKetO == true){hWQCZeKetO = false;}
      if(qNcRKIexUn == true){qNcRKIexUn = false;}
      if(nzqIXXSlte == true){nzqIXXSlte = false;}
      if(jjuQLnEPVP == true){jjuQLnEPVP = false;}
      if(DZCrCbSROL == true){DZCrCbSROL = false;}
      if(ZGrclhfIeC == true){ZGrclhfIeC = false;}
      if(LXjOdHRMFW == true){LXjOdHRMFW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJKEEATMXZ
{ 
  void HgYakRxHVg()
  { 
      bool CtsQrBwqbG = false;
      bool amUVcKFdgm = false;
      bool NolaLqJzCb = false;
      bool trqOUwFBpI = false;
      bool HAUYLlCzyn = false;
      bool UDQYOMHRFB = false;
      bool rwoALhuGBf = false;
      bool EEmYeNUNOZ = false;
      bool oJANHpbRzH = false;
      bool nmwoPLLTMc = false;
      bool pwySiPQrtB = false;
      bool rtDeLiwasV = false;
      bool GcGtrRHyIT = false;
      bool BAAlirLhdq = false;
      bool ZiXyOsjQcg = false;
      bool OjaqWMoDZR = false;
      bool ISiZzqtQwT = false;
      bool WNwCuWFIey = false;
      bool gpUaERZJOW = false;
      bool DHILhHAxyW = false;
      string RyiiVSENUz;
      string QdtCoclwTE;
      string zkdnJABqbf;
      string HxXMFYkBYW;
      string mdtWWEhhWM;
      string CQAzngUuYU;
      string RNkorSFgxQ;
      string qjXwQUpGQE;
      string STUPcqxYXX;
      string DpbDFZsFeD;
      string zBjFUSrDhT;
      string pNdTCysVLA;
      string VgIYMBHTqq;
      string bkaNFQiOtK;
      string ytpEhoLIBH;
      string fWsdhRrLsS;
      string KXMqrFlQOk;
      string OeaBCbqEqW;
      string pzSiKEqxem;
      string YWVbzZgyMb;
      if(RyiiVSENUz == zBjFUSrDhT){CtsQrBwqbG = true;}
      else if(zBjFUSrDhT == RyiiVSENUz){pwySiPQrtB = true;}
      if(QdtCoclwTE == pNdTCysVLA){amUVcKFdgm = true;}
      else if(pNdTCysVLA == QdtCoclwTE){rtDeLiwasV = true;}
      if(zkdnJABqbf == VgIYMBHTqq){NolaLqJzCb = true;}
      else if(VgIYMBHTqq == zkdnJABqbf){GcGtrRHyIT = true;}
      if(HxXMFYkBYW == bkaNFQiOtK){trqOUwFBpI = true;}
      else if(bkaNFQiOtK == HxXMFYkBYW){BAAlirLhdq = true;}
      if(mdtWWEhhWM == ytpEhoLIBH){HAUYLlCzyn = true;}
      else if(ytpEhoLIBH == mdtWWEhhWM){ZiXyOsjQcg = true;}
      if(CQAzngUuYU == fWsdhRrLsS){UDQYOMHRFB = true;}
      else if(fWsdhRrLsS == CQAzngUuYU){OjaqWMoDZR = true;}
      if(RNkorSFgxQ == KXMqrFlQOk){rwoALhuGBf = true;}
      else if(KXMqrFlQOk == RNkorSFgxQ){ISiZzqtQwT = true;}
      if(qjXwQUpGQE == OeaBCbqEqW){EEmYeNUNOZ = true;}
      if(STUPcqxYXX == pzSiKEqxem){oJANHpbRzH = true;}
      if(DpbDFZsFeD == YWVbzZgyMb){nmwoPLLTMc = true;}
      while(OeaBCbqEqW == qjXwQUpGQE){WNwCuWFIey = true;}
      while(pzSiKEqxem == pzSiKEqxem){gpUaERZJOW = true;}
      while(YWVbzZgyMb == YWVbzZgyMb){DHILhHAxyW = true;}
      if(CtsQrBwqbG == true){CtsQrBwqbG = false;}
      if(amUVcKFdgm == true){amUVcKFdgm = false;}
      if(NolaLqJzCb == true){NolaLqJzCb = false;}
      if(trqOUwFBpI == true){trqOUwFBpI = false;}
      if(HAUYLlCzyn == true){HAUYLlCzyn = false;}
      if(UDQYOMHRFB == true){UDQYOMHRFB = false;}
      if(rwoALhuGBf == true){rwoALhuGBf = false;}
      if(EEmYeNUNOZ == true){EEmYeNUNOZ = false;}
      if(oJANHpbRzH == true){oJANHpbRzH = false;}
      if(nmwoPLLTMc == true){nmwoPLLTMc = false;}
      if(pwySiPQrtB == true){pwySiPQrtB = false;}
      if(rtDeLiwasV == true){rtDeLiwasV = false;}
      if(GcGtrRHyIT == true){GcGtrRHyIT = false;}
      if(BAAlirLhdq == true){BAAlirLhdq = false;}
      if(ZiXyOsjQcg == true){ZiXyOsjQcg = false;}
      if(OjaqWMoDZR == true){OjaqWMoDZR = false;}
      if(ISiZzqtQwT == true){ISiZzqtQwT = false;}
      if(WNwCuWFIey == true){WNwCuWFIey = false;}
      if(gpUaERZJOW == true){gpUaERZJOW = false;}
      if(DHILhHAxyW == true){DHILhHAxyW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNJNFUTILJ
{ 
  void SJYXjyTXzh()
  { 
      bool RFNnKkiDNO = false;
      bool khdBQbHLgJ = false;
      bool AfIhKVOZez = false;
      bool VyCLnUbzTC = false;
      bool WmNdzPoUHr = false;
      bool pIyNSkwecn = false;
      bool WIYOsleSMu = false;
      bool AIqemNSeiu = false;
      bool gsSmJNAorD = false;
      bool XwVffNNzkM = false;
      bool jWILqhQTaE = false;
      bool SRwgHcpkEe = false;
      bool lpZJWDlKzY = false;
      bool zTsWLJkGua = false;
      bool wfOmjGAoYC = false;
      bool WbtFZtwynm = false;
      bool uFUBFzXZVx = false;
      bool ripdiGamZQ = false;
      bool DxlwCWZmwR = false;
      bool MmSHfpLNhk = false;
      string KznIhGlFrW;
      string fLTJEAdxJP;
      string bmNlwsNEEf;
      string EADUUFKKAL;
      string TuCWjCSmlP;
      string GcTYhXlCMo;
      string shBLSfIznz;
      string pSxyufkqCt;
      string ZaRnZafdmx;
      string THyLSltpDE;
      string tTymYmfVdB;
      string ltARORPMlr;
      string zdLpehUkeJ;
      string ltmxzFbeOl;
      string tKAlLYHfxA;
      string VgDLEPIIHq;
      string RupTOqHCRI;
      string pkyzxodZeG;
      string ZomemFqasj;
      string xTWXUyTfWT;
      if(KznIhGlFrW == tTymYmfVdB){RFNnKkiDNO = true;}
      else if(tTymYmfVdB == KznIhGlFrW){jWILqhQTaE = true;}
      if(fLTJEAdxJP == ltARORPMlr){khdBQbHLgJ = true;}
      else if(ltARORPMlr == fLTJEAdxJP){SRwgHcpkEe = true;}
      if(bmNlwsNEEf == zdLpehUkeJ){AfIhKVOZez = true;}
      else if(zdLpehUkeJ == bmNlwsNEEf){lpZJWDlKzY = true;}
      if(EADUUFKKAL == ltmxzFbeOl){VyCLnUbzTC = true;}
      else if(ltmxzFbeOl == EADUUFKKAL){zTsWLJkGua = true;}
      if(TuCWjCSmlP == tKAlLYHfxA){WmNdzPoUHr = true;}
      else if(tKAlLYHfxA == TuCWjCSmlP){wfOmjGAoYC = true;}
      if(GcTYhXlCMo == VgDLEPIIHq){pIyNSkwecn = true;}
      else if(VgDLEPIIHq == GcTYhXlCMo){WbtFZtwynm = true;}
      if(shBLSfIznz == RupTOqHCRI){WIYOsleSMu = true;}
      else if(RupTOqHCRI == shBLSfIznz){uFUBFzXZVx = true;}
      if(pSxyufkqCt == pkyzxodZeG){AIqemNSeiu = true;}
      if(ZaRnZafdmx == ZomemFqasj){gsSmJNAorD = true;}
      if(THyLSltpDE == xTWXUyTfWT){XwVffNNzkM = true;}
      while(pkyzxodZeG == pSxyufkqCt){ripdiGamZQ = true;}
      while(ZomemFqasj == ZomemFqasj){DxlwCWZmwR = true;}
      while(xTWXUyTfWT == xTWXUyTfWT){MmSHfpLNhk = true;}
      if(RFNnKkiDNO == true){RFNnKkiDNO = false;}
      if(khdBQbHLgJ == true){khdBQbHLgJ = false;}
      if(AfIhKVOZez == true){AfIhKVOZez = false;}
      if(VyCLnUbzTC == true){VyCLnUbzTC = false;}
      if(WmNdzPoUHr == true){WmNdzPoUHr = false;}
      if(pIyNSkwecn == true){pIyNSkwecn = false;}
      if(WIYOsleSMu == true){WIYOsleSMu = false;}
      if(AIqemNSeiu == true){AIqemNSeiu = false;}
      if(gsSmJNAorD == true){gsSmJNAorD = false;}
      if(XwVffNNzkM == true){XwVffNNzkM = false;}
      if(jWILqhQTaE == true){jWILqhQTaE = false;}
      if(SRwgHcpkEe == true){SRwgHcpkEe = false;}
      if(lpZJWDlKzY == true){lpZJWDlKzY = false;}
      if(zTsWLJkGua == true){zTsWLJkGua = false;}
      if(wfOmjGAoYC == true){wfOmjGAoYC = false;}
      if(WbtFZtwynm == true){WbtFZtwynm = false;}
      if(uFUBFzXZVx == true){uFUBFzXZVx = false;}
      if(ripdiGamZQ == true){ripdiGamZQ = false;}
      if(DxlwCWZmwR == true){DxlwCWZmwR = false;}
      if(MmSHfpLNhk == true){MmSHfpLNhk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYTPJPGYZB
{ 
  void tdsQrlGgmR()
  { 
      bool wsKopXFgOp = false;
      bool RTDNKzMzBw = false;
      bool ahbyCtdmMM = false;
      bool cfDTlxDnee = false;
      bool rFMXAPgyWQ = false;
      bool FxBVuOQLmw = false;
      bool sRUCMkQibM = false;
      bool uYTWDUUExl = false;
      bool MfQwHfegYX = false;
      bool frAikakKKP = false;
      bool zyWJVgceSZ = false;
      bool sMOAiNBYtg = false;
      bool FiJDgDXkkc = false;
      bool jJthmNJGZZ = false;
      bool CAOzdTcAzX = false;
      bool ZLQcJPnScR = false;
      bool JrtppiRfMV = false;
      bool EtyTdFUKZM = false;
      bool ZWkMCXsQYX = false;
      bool YpcIQKGYIu = false;
      string tPbRrHQfTg;
      string etKAIqEtJr;
      string yScSWgxRQg;
      string qJbzZbMFAo;
      string MuDXeKiwTF;
      string BnfAVbmIuK;
      string KyPloVSLZf;
      string dztUeDOEnL;
      string yAxKfCcbdy;
      string oEKodOeQhJ;
      string rXVnbCtLUR;
      string MhUjMJAEGm;
      string rqhbpZoEpQ;
      string XyWeTZeJid;
      string HRHLkHiZbU;
      string NaKtQBptxB;
      string NoUDsOKpPl;
      string epVceZiVpi;
      string pOcUCxmbNR;
      string jkMhPRxDRV;
      if(tPbRrHQfTg == rXVnbCtLUR){wsKopXFgOp = true;}
      else if(rXVnbCtLUR == tPbRrHQfTg){zyWJVgceSZ = true;}
      if(etKAIqEtJr == MhUjMJAEGm){RTDNKzMzBw = true;}
      else if(MhUjMJAEGm == etKAIqEtJr){sMOAiNBYtg = true;}
      if(yScSWgxRQg == rqhbpZoEpQ){ahbyCtdmMM = true;}
      else if(rqhbpZoEpQ == yScSWgxRQg){FiJDgDXkkc = true;}
      if(qJbzZbMFAo == XyWeTZeJid){cfDTlxDnee = true;}
      else if(XyWeTZeJid == qJbzZbMFAo){jJthmNJGZZ = true;}
      if(MuDXeKiwTF == HRHLkHiZbU){rFMXAPgyWQ = true;}
      else if(HRHLkHiZbU == MuDXeKiwTF){CAOzdTcAzX = true;}
      if(BnfAVbmIuK == NaKtQBptxB){FxBVuOQLmw = true;}
      else if(NaKtQBptxB == BnfAVbmIuK){ZLQcJPnScR = true;}
      if(KyPloVSLZf == NoUDsOKpPl){sRUCMkQibM = true;}
      else if(NoUDsOKpPl == KyPloVSLZf){JrtppiRfMV = true;}
      if(dztUeDOEnL == epVceZiVpi){uYTWDUUExl = true;}
      if(yAxKfCcbdy == pOcUCxmbNR){MfQwHfegYX = true;}
      if(oEKodOeQhJ == jkMhPRxDRV){frAikakKKP = true;}
      while(epVceZiVpi == dztUeDOEnL){EtyTdFUKZM = true;}
      while(pOcUCxmbNR == pOcUCxmbNR){ZWkMCXsQYX = true;}
      while(jkMhPRxDRV == jkMhPRxDRV){YpcIQKGYIu = true;}
      if(wsKopXFgOp == true){wsKopXFgOp = false;}
      if(RTDNKzMzBw == true){RTDNKzMzBw = false;}
      if(ahbyCtdmMM == true){ahbyCtdmMM = false;}
      if(cfDTlxDnee == true){cfDTlxDnee = false;}
      if(rFMXAPgyWQ == true){rFMXAPgyWQ = false;}
      if(FxBVuOQLmw == true){FxBVuOQLmw = false;}
      if(sRUCMkQibM == true){sRUCMkQibM = false;}
      if(uYTWDUUExl == true){uYTWDUUExl = false;}
      if(MfQwHfegYX == true){MfQwHfegYX = false;}
      if(frAikakKKP == true){frAikakKKP = false;}
      if(zyWJVgceSZ == true){zyWJVgceSZ = false;}
      if(sMOAiNBYtg == true){sMOAiNBYtg = false;}
      if(FiJDgDXkkc == true){FiJDgDXkkc = false;}
      if(jJthmNJGZZ == true){jJthmNJGZZ = false;}
      if(CAOzdTcAzX == true){CAOzdTcAzX = false;}
      if(ZLQcJPnScR == true){ZLQcJPnScR = false;}
      if(JrtppiRfMV == true){JrtppiRfMV = false;}
      if(EtyTdFUKZM == true){EtyTdFUKZM = false;}
      if(ZWkMCXsQYX == true){ZWkMCXsQYX = false;}
      if(YpcIQKGYIu == true){YpcIQKGYIu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSIIAOMBHB
{ 
  void NbOFUEdeqH()
  { 
      bool fqVNJVcSkr = false;
      bool oSunkVEpmp = false;
      bool jOEqgaEjdI = false;
      bool yrwLPaNuBE = false;
      bool OesCCmZiFh = false;
      bool XWRTuRmefh = false;
      bool RroctxViXK = false;
      bool IIoiaFUCns = false;
      bool BUdukaZbPy = false;
      bool niPTlVoQHF = false;
      bool RpLuZOhisp = false;
      bool wjpmgxOsqS = false;
      bool WsTYWYsVwE = false;
      bool PDtibLJiVV = false;
      bool sqiYBDsblo = false;
      bool HwYoiXWlXA = false;
      bool UMlnasoHKV = false;
      bool meXVYfKtWS = false;
      bool fQiHxSdFzD = false;
      bool nXKUAgEtyI = false;
      string JWuHTqICPA;
      string dQyNyShNll;
      string ilgRHynKVP;
      string LWubQJTVmM;
      string fJtjlXunuM;
      string IyqqEXpdzU;
      string DygAnHUWxo;
      string zLaZFYrwei;
      string DzOIGNfEWr;
      string SpVRJgbtwe;
      string DYqGNwWRke;
      string esyPRDjXsa;
      string aQzEVJpJPX;
      string wyAzfeHIuK;
      string pOSrMYqFAF;
      string xEAVEmYmjD;
      string GNBNhgszjl;
      string wbbhjLxGqw;
      string RjJKZrxetr;
      string FUXqEbNFKf;
      if(JWuHTqICPA == DYqGNwWRke){fqVNJVcSkr = true;}
      else if(DYqGNwWRke == JWuHTqICPA){RpLuZOhisp = true;}
      if(dQyNyShNll == esyPRDjXsa){oSunkVEpmp = true;}
      else if(esyPRDjXsa == dQyNyShNll){wjpmgxOsqS = true;}
      if(ilgRHynKVP == aQzEVJpJPX){jOEqgaEjdI = true;}
      else if(aQzEVJpJPX == ilgRHynKVP){WsTYWYsVwE = true;}
      if(LWubQJTVmM == wyAzfeHIuK){yrwLPaNuBE = true;}
      else if(wyAzfeHIuK == LWubQJTVmM){PDtibLJiVV = true;}
      if(fJtjlXunuM == pOSrMYqFAF){OesCCmZiFh = true;}
      else if(pOSrMYqFAF == fJtjlXunuM){sqiYBDsblo = true;}
      if(IyqqEXpdzU == xEAVEmYmjD){XWRTuRmefh = true;}
      else if(xEAVEmYmjD == IyqqEXpdzU){HwYoiXWlXA = true;}
      if(DygAnHUWxo == GNBNhgszjl){RroctxViXK = true;}
      else if(GNBNhgszjl == DygAnHUWxo){UMlnasoHKV = true;}
      if(zLaZFYrwei == wbbhjLxGqw){IIoiaFUCns = true;}
      if(DzOIGNfEWr == RjJKZrxetr){BUdukaZbPy = true;}
      if(SpVRJgbtwe == FUXqEbNFKf){niPTlVoQHF = true;}
      while(wbbhjLxGqw == zLaZFYrwei){meXVYfKtWS = true;}
      while(RjJKZrxetr == RjJKZrxetr){fQiHxSdFzD = true;}
      while(FUXqEbNFKf == FUXqEbNFKf){nXKUAgEtyI = true;}
      if(fqVNJVcSkr == true){fqVNJVcSkr = false;}
      if(oSunkVEpmp == true){oSunkVEpmp = false;}
      if(jOEqgaEjdI == true){jOEqgaEjdI = false;}
      if(yrwLPaNuBE == true){yrwLPaNuBE = false;}
      if(OesCCmZiFh == true){OesCCmZiFh = false;}
      if(XWRTuRmefh == true){XWRTuRmefh = false;}
      if(RroctxViXK == true){RroctxViXK = false;}
      if(IIoiaFUCns == true){IIoiaFUCns = false;}
      if(BUdukaZbPy == true){BUdukaZbPy = false;}
      if(niPTlVoQHF == true){niPTlVoQHF = false;}
      if(RpLuZOhisp == true){RpLuZOhisp = false;}
      if(wjpmgxOsqS == true){wjpmgxOsqS = false;}
      if(WsTYWYsVwE == true){WsTYWYsVwE = false;}
      if(PDtibLJiVV == true){PDtibLJiVV = false;}
      if(sqiYBDsblo == true){sqiYBDsblo = false;}
      if(HwYoiXWlXA == true){HwYoiXWlXA = false;}
      if(UMlnasoHKV == true){UMlnasoHKV = false;}
      if(meXVYfKtWS == true){meXVYfKtWS = false;}
      if(fQiHxSdFzD == true){fQiHxSdFzD = false;}
      if(nXKUAgEtyI == true){nXKUAgEtyI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSCXEBXFSR
{ 
  void bOpqzWGBLl()
  { 
      bool DBcuocmfsS = false;
      bool trHmstojRc = false;
      bool FYYdmSNaDH = false;
      bool hUwhHjxuRA = false;
      bool uOIZTTIFXj = false;
      bool amwTOdbyHW = false;
      bool OMckkYwZeI = false;
      bool xsSQhqQzJS = false;
      bool JICSfuXbSd = false;
      bool HynulhkWnt = false;
      bool XiaPmhTfkX = false;
      bool MconNFJKFo = false;
      bool BTHAByFXez = false;
      bool GtKPuZhmfy = false;
      bool arqtQeJzgf = false;
      bool YaRzrEbZNn = false;
      bool cwAlRSRYsm = false;
      bool XVeGNJcMiW = false;
      bool nFpzafbLWp = false;
      bool yHZqVerEcy = false;
      string XQDAnQCpcB;
      string cfdCcFCJSz;
      string YEVJAGucWd;
      string RWTtyRxDbD;
      string GnwTyjWlzq;
      string OBlBKSttzh;
      string UZTyjFMjDL;
      string HygOsjICKP;
      string jJcePQkSif;
      string WDEtifUyjs;
      string XlhmiPTWIa;
      string KrijyKwniT;
      string TtBXoEtmeM;
      string OJRRrxapuA;
      string wOKIUdTUwY;
      string ifOQYdkKyd;
      string UfquLAaRqA;
      string iGrhWFirCK;
      string kZqGciuBrN;
      string MQrRePWOwU;
      if(XQDAnQCpcB == XlhmiPTWIa){DBcuocmfsS = true;}
      else if(XlhmiPTWIa == XQDAnQCpcB){XiaPmhTfkX = true;}
      if(cfdCcFCJSz == KrijyKwniT){trHmstojRc = true;}
      else if(KrijyKwniT == cfdCcFCJSz){MconNFJKFo = true;}
      if(YEVJAGucWd == TtBXoEtmeM){FYYdmSNaDH = true;}
      else if(TtBXoEtmeM == YEVJAGucWd){BTHAByFXez = true;}
      if(RWTtyRxDbD == OJRRrxapuA){hUwhHjxuRA = true;}
      else if(OJRRrxapuA == RWTtyRxDbD){GtKPuZhmfy = true;}
      if(GnwTyjWlzq == wOKIUdTUwY){uOIZTTIFXj = true;}
      else if(wOKIUdTUwY == GnwTyjWlzq){arqtQeJzgf = true;}
      if(OBlBKSttzh == ifOQYdkKyd){amwTOdbyHW = true;}
      else if(ifOQYdkKyd == OBlBKSttzh){YaRzrEbZNn = true;}
      if(UZTyjFMjDL == UfquLAaRqA){OMckkYwZeI = true;}
      else if(UfquLAaRqA == UZTyjFMjDL){cwAlRSRYsm = true;}
      if(HygOsjICKP == iGrhWFirCK){xsSQhqQzJS = true;}
      if(jJcePQkSif == kZqGciuBrN){JICSfuXbSd = true;}
      if(WDEtifUyjs == MQrRePWOwU){HynulhkWnt = true;}
      while(iGrhWFirCK == HygOsjICKP){XVeGNJcMiW = true;}
      while(kZqGciuBrN == kZqGciuBrN){nFpzafbLWp = true;}
      while(MQrRePWOwU == MQrRePWOwU){yHZqVerEcy = true;}
      if(DBcuocmfsS == true){DBcuocmfsS = false;}
      if(trHmstojRc == true){trHmstojRc = false;}
      if(FYYdmSNaDH == true){FYYdmSNaDH = false;}
      if(hUwhHjxuRA == true){hUwhHjxuRA = false;}
      if(uOIZTTIFXj == true){uOIZTTIFXj = false;}
      if(amwTOdbyHW == true){amwTOdbyHW = false;}
      if(OMckkYwZeI == true){OMckkYwZeI = false;}
      if(xsSQhqQzJS == true){xsSQhqQzJS = false;}
      if(JICSfuXbSd == true){JICSfuXbSd = false;}
      if(HynulhkWnt == true){HynulhkWnt = false;}
      if(XiaPmhTfkX == true){XiaPmhTfkX = false;}
      if(MconNFJKFo == true){MconNFJKFo = false;}
      if(BTHAByFXez == true){BTHAByFXez = false;}
      if(GtKPuZhmfy == true){GtKPuZhmfy = false;}
      if(arqtQeJzgf == true){arqtQeJzgf = false;}
      if(YaRzrEbZNn == true){YaRzrEbZNn = false;}
      if(cwAlRSRYsm == true){cwAlRSRYsm = false;}
      if(XVeGNJcMiW == true){XVeGNJcMiW = false;}
      if(nFpzafbLWp == true){nFpzafbLWp = false;}
      if(yHZqVerEcy == true){yHZqVerEcy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UWIJNCBWVJ
{ 
  void GgGCoZsfHA()
  { 
      bool uIGmHLLeAq = false;
      bool PeWuIknbcX = false;
      bool LhFTsnyCOf = false;
      bool cULVjSTuQc = false;
      bool hGRAQkOSZd = false;
      bool lbSlZNDmtT = false;
      bool MIPUOuSAKo = false;
      bool QrKApFQFCH = false;
      bool YfbksABYwW = false;
      bool PgBxPYpwkV = false;
      bool ROHkMtRSwU = false;
      bool wyjltgfeaO = false;
      bool stEmZjqNjQ = false;
      bool OTTgoKXqXz = false;
      bool iicaaRwOCi = false;
      bool sKUWbXJTKc = false;
      bool CDhfFbdDxi = false;
      bool InGbfJRcMH = false;
      bool mcKBXEyxEQ = false;
      bool AEguweBwVy = false;
      string jSRhoxsBwP;
      string oYQijFMWZI;
      string soFfxwWxHW;
      string JsFjTjEHRx;
      string VykSGaekDT;
      string AIhPCtNljs;
      string autYGwSfPz;
      string AFEbltElYV;
      string QksmVBKphY;
      string WSWYWZELMJ;
      string IzVESuDGcH;
      string paMOboBGDE;
      string kcxqchifFM;
      string psZPNRPoUa;
      string yEMaiwFHxg;
      string XxHHXfBdak;
      string LWAQQxAxBJ;
      string YMlcGgPVHf;
      string baiYnskRqg;
      string QkNiOaEuKl;
      if(jSRhoxsBwP == IzVESuDGcH){uIGmHLLeAq = true;}
      else if(IzVESuDGcH == jSRhoxsBwP){ROHkMtRSwU = true;}
      if(oYQijFMWZI == paMOboBGDE){PeWuIknbcX = true;}
      else if(paMOboBGDE == oYQijFMWZI){wyjltgfeaO = true;}
      if(soFfxwWxHW == kcxqchifFM){LhFTsnyCOf = true;}
      else if(kcxqchifFM == soFfxwWxHW){stEmZjqNjQ = true;}
      if(JsFjTjEHRx == psZPNRPoUa){cULVjSTuQc = true;}
      else if(psZPNRPoUa == JsFjTjEHRx){OTTgoKXqXz = true;}
      if(VykSGaekDT == yEMaiwFHxg){hGRAQkOSZd = true;}
      else if(yEMaiwFHxg == VykSGaekDT){iicaaRwOCi = true;}
      if(AIhPCtNljs == XxHHXfBdak){lbSlZNDmtT = true;}
      else if(XxHHXfBdak == AIhPCtNljs){sKUWbXJTKc = true;}
      if(autYGwSfPz == LWAQQxAxBJ){MIPUOuSAKo = true;}
      else if(LWAQQxAxBJ == autYGwSfPz){CDhfFbdDxi = true;}
      if(AFEbltElYV == YMlcGgPVHf){QrKApFQFCH = true;}
      if(QksmVBKphY == baiYnskRqg){YfbksABYwW = true;}
      if(WSWYWZELMJ == QkNiOaEuKl){PgBxPYpwkV = true;}
      while(YMlcGgPVHf == AFEbltElYV){InGbfJRcMH = true;}
      while(baiYnskRqg == baiYnskRqg){mcKBXEyxEQ = true;}
      while(QkNiOaEuKl == QkNiOaEuKl){AEguweBwVy = true;}
      if(uIGmHLLeAq == true){uIGmHLLeAq = false;}
      if(PeWuIknbcX == true){PeWuIknbcX = false;}
      if(LhFTsnyCOf == true){LhFTsnyCOf = false;}
      if(cULVjSTuQc == true){cULVjSTuQc = false;}
      if(hGRAQkOSZd == true){hGRAQkOSZd = false;}
      if(lbSlZNDmtT == true){lbSlZNDmtT = false;}
      if(MIPUOuSAKo == true){MIPUOuSAKo = false;}
      if(QrKApFQFCH == true){QrKApFQFCH = false;}
      if(YfbksABYwW == true){YfbksABYwW = false;}
      if(PgBxPYpwkV == true){PgBxPYpwkV = false;}
      if(ROHkMtRSwU == true){ROHkMtRSwU = false;}
      if(wyjltgfeaO == true){wyjltgfeaO = false;}
      if(stEmZjqNjQ == true){stEmZjqNjQ = false;}
      if(OTTgoKXqXz == true){OTTgoKXqXz = false;}
      if(iicaaRwOCi == true){iicaaRwOCi = false;}
      if(sKUWbXJTKc == true){sKUWbXJTKc = false;}
      if(CDhfFbdDxi == true){CDhfFbdDxi = false;}
      if(InGbfJRcMH == true){InGbfJRcMH = false;}
      if(mcKBXEyxEQ == true){mcKBXEyxEQ = false;}
      if(AEguweBwVy == true){AEguweBwVy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNSEDFFQCC
{ 
  void dxmxbKtUzs()
  { 
      bool xEfafYiVyu = false;
      bool gKSQzTMCeW = false;
      bool PLTClPqkyR = false;
      bool JnMcMboVSw = false;
      bool OKVaUtySkc = false;
      bool jsjQrkkcoQ = false;
      bool gxWflrxoEX = false;
      bool epjiHEpshr = false;
      bool QYzVhQEuja = false;
      bool qLgBORnonc = false;
      bool wJOMxsIBJn = false;
      bool uquwAIxByV = false;
      bool mCEcgSJhTo = false;
      bool QAEEwGJmXn = false;
      bool HClwezQjBG = false;
      bool UmqSotFkfd = false;
      bool iZhTWtmpzs = false;
      bool zKcJOkQHyh = false;
      bool CYfNUdJkOC = false;
      bool BXGtEgURYk = false;
      string EcirgXdlUr;
      string QYsjCktALD;
      string JLztHrDTVG;
      string rBQDsVzMMi;
      string uKNiSNJltt;
      string aMpdWrdoko;
      string TJPNAOHoqf;
      string lgnbHyxPas;
      string iQYafeLmgA;
      string rJbXPkuzhD;
      string GTuOItYNWX;
      string uNNqFCkohU;
      string DUIqnbEPLV;
      string DygWmOVJRl;
      string GxQIFdujRM;
      string AFRNAkKEZf;
      string oJBAUwfpEq;
      string gaWuOFEAlJ;
      string fUxyVxgTWB;
      string ERikxwwPnI;
      if(EcirgXdlUr == GTuOItYNWX){xEfafYiVyu = true;}
      else if(GTuOItYNWX == EcirgXdlUr){wJOMxsIBJn = true;}
      if(QYsjCktALD == uNNqFCkohU){gKSQzTMCeW = true;}
      else if(uNNqFCkohU == QYsjCktALD){uquwAIxByV = true;}
      if(JLztHrDTVG == DUIqnbEPLV){PLTClPqkyR = true;}
      else if(DUIqnbEPLV == JLztHrDTVG){mCEcgSJhTo = true;}
      if(rBQDsVzMMi == DygWmOVJRl){JnMcMboVSw = true;}
      else if(DygWmOVJRl == rBQDsVzMMi){QAEEwGJmXn = true;}
      if(uKNiSNJltt == GxQIFdujRM){OKVaUtySkc = true;}
      else if(GxQIFdujRM == uKNiSNJltt){HClwezQjBG = true;}
      if(aMpdWrdoko == AFRNAkKEZf){jsjQrkkcoQ = true;}
      else if(AFRNAkKEZf == aMpdWrdoko){UmqSotFkfd = true;}
      if(TJPNAOHoqf == oJBAUwfpEq){gxWflrxoEX = true;}
      else if(oJBAUwfpEq == TJPNAOHoqf){iZhTWtmpzs = true;}
      if(lgnbHyxPas == gaWuOFEAlJ){epjiHEpshr = true;}
      if(iQYafeLmgA == fUxyVxgTWB){QYzVhQEuja = true;}
      if(rJbXPkuzhD == ERikxwwPnI){qLgBORnonc = true;}
      while(gaWuOFEAlJ == lgnbHyxPas){zKcJOkQHyh = true;}
      while(fUxyVxgTWB == fUxyVxgTWB){CYfNUdJkOC = true;}
      while(ERikxwwPnI == ERikxwwPnI){BXGtEgURYk = true;}
      if(xEfafYiVyu == true){xEfafYiVyu = false;}
      if(gKSQzTMCeW == true){gKSQzTMCeW = false;}
      if(PLTClPqkyR == true){PLTClPqkyR = false;}
      if(JnMcMboVSw == true){JnMcMboVSw = false;}
      if(OKVaUtySkc == true){OKVaUtySkc = false;}
      if(jsjQrkkcoQ == true){jsjQrkkcoQ = false;}
      if(gxWflrxoEX == true){gxWflrxoEX = false;}
      if(epjiHEpshr == true){epjiHEpshr = false;}
      if(QYzVhQEuja == true){QYzVhQEuja = false;}
      if(qLgBORnonc == true){qLgBORnonc = false;}
      if(wJOMxsIBJn == true){wJOMxsIBJn = false;}
      if(uquwAIxByV == true){uquwAIxByV = false;}
      if(mCEcgSJhTo == true){mCEcgSJhTo = false;}
      if(QAEEwGJmXn == true){QAEEwGJmXn = false;}
      if(HClwezQjBG == true){HClwezQjBG = false;}
      if(UmqSotFkfd == true){UmqSotFkfd = false;}
      if(iZhTWtmpzs == true){iZhTWtmpzs = false;}
      if(zKcJOkQHyh == true){zKcJOkQHyh = false;}
      if(CYfNUdJkOC == true){CYfNUdJkOC = false;}
      if(BXGtEgURYk == true){BXGtEgURYk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQBFHOLYZT
{ 
  void NRkJPtmHhg()
  { 
      bool WZJublPJrE = false;
      bool SprJAhiLxp = false;
      bool usaGZiCaYK = false;
      bool RUjChhoWXx = false;
      bool pqfpRjFQXt = false;
      bool HeLOhcyCVs = false;
      bool iokgmxGoaS = false;
      bool sLnzzENkop = false;
      bool clDdDmIUUE = false;
      bool jmAeOBGyDT = false;
      bool cPoEBuqMOd = false;
      bool PNMfPxkGdA = false;
      bool nkUWiFKIky = false;
      bool yPhUMMwycH = false;
      bool uwGqoVZUOQ = false;
      bool PzTDeruSVu = false;
      bool jhbQeAerSD = false;
      bool BlcVErddhM = false;
      bool fotThyudpT = false;
      bool RcchXNTpLn = false;
      string sZxnqhpNBq;
      string BdSPbMdApc;
      string tEnnMIaakz;
      string pQkHYJiCjT;
      string wZWlILgWbp;
      string IgrNmokJah;
      string HPbBBjsKpS;
      string cbQWfTgCfB;
      string bDytqIYXUi;
      string XZbCMgxUkX;
      string SVgJMgQVgS;
      string IidZFDRgKr;
      string LUpHtDAOJz;
      string WLQHhFWnhJ;
      string rCpBaouBwI;
      string OPKrMxeYOI;
      string gBMgwwRVrA;
      string gczBAIdogF;
      string HySAjGAXtk;
      string ZxZYbppJEd;
      if(sZxnqhpNBq == SVgJMgQVgS){WZJublPJrE = true;}
      else if(SVgJMgQVgS == sZxnqhpNBq){cPoEBuqMOd = true;}
      if(BdSPbMdApc == IidZFDRgKr){SprJAhiLxp = true;}
      else if(IidZFDRgKr == BdSPbMdApc){PNMfPxkGdA = true;}
      if(tEnnMIaakz == LUpHtDAOJz){usaGZiCaYK = true;}
      else if(LUpHtDAOJz == tEnnMIaakz){nkUWiFKIky = true;}
      if(pQkHYJiCjT == WLQHhFWnhJ){RUjChhoWXx = true;}
      else if(WLQHhFWnhJ == pQkHYJiCjT){yPhUMMwycH = true;}
      if(wZWlILgWbp == rCpBaouBwI){pqfpRjFQXt = true;}
      else if(rCpBaouBwI == wZWlILgWbp){uwGqoVZUOQ = true;}
      if(IgrNmokJah == OPKrMxeYOI){HeLOhcyCVs = true;}
      else if(OPKrMxeYOI == IgrNmokJah){PzTDeruSVu = true;}
      if(HPbBBjsKpS == gBMgwwRVrA){iokgmxGoaS = true;}
      else if(gBMgwwRVrA == HPbBBjsKpS){jhbQeAerSD = true;}
      if(cbQWfTgCfB == gczBAIdogF){sLnzzENkop = true;}
      if(bDytqIYXUi == HySAjGAXtk){clDdDmIUUE = true;}
      if(XZbCMgxUkX == ZxZYbppJEd){jmAeOBGyDT = true;}
      while(gczBAIdogF == cbQWfTgCfB){BlcVErddhM = true;}
      while(HySAjGAXtk == HySAjGAXtk){fotThyudpT = true;}
      while(ZxZYbppJEd == ZxZYbppJEd){RcchXNTpLn = true;}
      if(WZJublPJrE == true){WZJublPJrE = false;}
      if(SprJAhiLxp == true){SprJAhiLxp = false;}
      if(usaGZiCaYK == true){usaGZiCaYK = false;}
      if(RUjChhoWXx == true){RUjChhoWXx = false;}
      if(pqfpRjFQXt == true){pqfpRjFQXt = false;}
      if(HeLOhcyCVs == true){HeLOhcyCVs = false;}
      if(iokgmxGoaS == true){iokgmxGoaS = false;}
      if(sLnzzENkop == true){sLnzzENkop = false;}
      if(clDdDmIUUE == true){clDdDmIUUE = false;}
      if(jmAeOBGyDT == true){jmAeOBGyDT = false;}
      if(cPoEBuqMOd == true){cPoEBuqMOd = false;}
      if(PNMfPxkGdA == true){PNMfPxkGdA = false;}
      if(nkUWiFKIky == true){nkUWiFKIky = false;}
      if(yPhUMMwycH == true){yPhUMMwycH = false;}
      if(uwGqoVZUOQ == true){uwGqoVZUOQ = false;}
      if(PzTDeruSVu == true){PzTDeruSVu = false;}
      if(jhbQeAerSD == true){jhbQeAerSD = false;}
      if(BlcVErddhM == true){BlcVErddhM = false;}
      if(fotThyudpT == true){fotThyudpT = false;}
      if(RcchXNTpLn == true){RcchXNTpLn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZKABLEQVWW
{ 
  void ArXJnVLjde()
  { 
      bool kdFHDoGceL = false;
      bool TPcnqhMChg = false;
      bool iAHUICYImW = false;
      bool CnNBjrNmtc = false;
      bool UUacTDswjz = false;
      bool ZsBZijVkzA = false;
      bool PypHIeBbEz = false;
      bool TZHFLNZeBE = false;
      bool JbYmwJlnRz = false;
      bool WcnsMVeSTn = false;
      bool CRrjeAkuNV = false;
      bool KqjtqmZCLz = false;
      bool rNKEcqlNrp = false;
      bool iGKMCrjnHu = false;
      bool XqZwoersCZ = false;
      bool ubHUunGmHn = false;
      bool OWDXlDgWrz = false;
      bool DluPbBnOPx = false;
      bool zrLStGzoRN = false;
      bool kwfTgAmBJk = false;
      string DFPpYgPIIm;
      string NscBknpFFA;
      string YaQSdVArhi;
      string ExmBEfSKPF;
      string cpbcRDxNaf;
      string PZamJbnwLD;
      string gXaYiPGbwE;
      string UfozWhznAa;
      string YlRBTdWzqc;
      string rWyMYFPDsC;
      string xURVLijaQa;
      string cAuketFYFE;
      string sGkTMxgcaQ;
      string SutydDUuoj;
      string tuiPzqaNhd;
      string zpxoJpjxJN;
      string CHzzIgGxHa;
      string ZKiUJxWUTU;
      string WTtxRbxFom;
      string SWkahmuiGS;
      if(DFPpYgPIIm == xURVLijaQa){kdFHDoGceL = true;}
      else if(xURVLijaQa == DFPpYgPIIm){CRrjeAkuNV = true;}
      if(NscBknpFFA == cAuketFYFE){TPcnqhMChg = true;}
      else if(cAuketFYFE == NscBknpFFA){KqjtqmZCLz = true;}
      if(YaQSdVArhi == sGkTMxgcaQ){iAHUICYImW = true;}
      else if(sGkTMxgcaQ == YaQSdVArhi){rNKEcqlNrp = true;}
      if(ExmBEfSKPF == SutydDUuoj){CnNBjrNmtc = true;}
      else if(SutydDUuoj == ExmBEfSKPF){iGKMCrjnHu = true;}
      if(cpbcRDxNaf == tuiPzqaNhd){UUacTDswjz = true;}
      else if(tuiPzqaNhd == cpbcRDxNaf){XqZwoersCZ = true;}
      if(PZamJbnwLD == zpxoJpjxJN){ZsBZijVkzA = true;}
      else if(zpxoJpjxJN == PZamJbnwLD){ubHUunGmHn = true;}
      if(gXaYiPGbwE == CHzzIgGxHa){PypHIeBbEz = true;}
      else if(CHzzIgGxHa == gXaYiPGbwE){OWDXlDgWrz = true;}
      if(UfozWhznAa == ZKiUJxWUTU){TZHFLNZeBE = true;}
      if(YlRBTdWzqc == WTtxRbxFom){JbYmwJlnRz = true;}
      if(rWyMYFPDsC == SWkahmuiGS){WcnsMVeSTn = true;}
      while(ZKiUJxWUTU == UfozWhznAa){DluPbBnOPx = true;}
      while(WTtxRbxFom == WTtxRbxFom){zrLStGzoRN = true;}
      while(SWkahmuiGS == SWkahmuiGS){kwfTgAmBJk = true;}
      if(kdFHDoGceL == true){kdFHDoGceL = false;}
      if(TPcnqhMChg == true){TPcnqhMChg = false;}
      if(iAHUICYImW == true){iAHUICYImW = false;}
      if(CnNBjrNmtc == true){CnNBjrNmtc = false;}
      if(UUacTDswjz == true){UUacTDswjz = false;}
      if(ZsBZijVkzA == true){ZsBZijVkzA = false;}
      if(PypHIeBbEz == true){PypHIeBbEz = false;}
      if(TZHFLNZeBE == true){TZHFLNZeBE = false;}
      if(JbYmwJlnRz == true){JbYmwJlnRz = false;}
      if(WcnsMVeSTn == true){WcnsMVeSTn = false;}
      if(CRrjeAkuNV == true){CRrjeAkuNV = false;}
      if(KqjtqmZCLz == true){KqjtqmZCLz = false;}
      if(rNKEcqlNrp == true){rNKEcqlNrp = false;}
      if(iGKMCrjnHu == true){iGKMCrjnHu = false;}
      if(XqZwoersCZ == true){XqZwoersCZ = false;}
      if(ubHUunGmHn == true){ubHUunGmHn = false;}
      if(OWDXlDgWrz == true){OWDXlDgWrz = false;}
      if(DluPbBnOPx == true){DluPbBnOPx = false;}
      if(zrLStGzoRN == true){zrLStGzoRN = false;}
      if(kwfTgAmBJk == true){kwfTgAmBJk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULMBZWGDEC
{ 
  void BCiNHTtZEE()
  { 
      bool oBjzpVIDfa = false;
      bool XrxcpmdJwN = false;
      bool lrbWmVZbuD = false;
      bool EIucKJVyJc = false;
      bool gPxlXYUuou = false;
      bool ytEmDwYNMT = false;
      bool wfIcVPwTRg = false;
      bool QfATfVuozN = false;
      bool BdmzEKDIYO = false;
      bool jIlogAHTQI = false;
      bool cAcHdStkHh = false;
      bool AiOySRsIYL = false;
      bool LntDxIsKme = false;
      bool NbYqkAAeVk = false;
      bool PSAqNAtmVO = false;
      bool HzuFwnFZKV = false;
      bool ZixbTYKWNS = false;
      bool QNmmurmDpw = false;
      bool OGnXXOfTtw = false;
      bool taUzLgUXXn = false;
      string KGQIHxusYE;
      string nozVCxgpRy;
      string qMHblAMHTo;
      string hSSkCVRWWl;
      string JeWTaOEyTi;
      string LxSEWyznVH;
      string knZiVVWOTg;
      string eJSeoMpmBX;
      string wNnjcjANOE;
      string WcAPBUFmxE;
      string roemDBemPJ;
      string ILlyLWAoFk;
      string VIAOKBICdT;
      string GCoweGhBgb;
      string FMxEwKqCEd;
      string UQhMiioPbB;
      string sbIuDGVoSE;
      string nyHdfIKwSz;
      string KFyzzpTcNw;
      string RRYfhcDBAp;
      if(KGQIHxusYE == roemDBemPJ){oBjzpVIDfa = true;}
      else if(roemDBemPJ == KGQIHxusYE){cAcHdStkHh = true;}
      if(nozVCxgpRy == ILlyLWAoFk){XrxcpmdJwN = true;}
      else if(ILlyLWAoFk == nozVCxgpRy){AiOySRsIYL = true;}
      if(qMHblAMHTo == VIAOKBICdT){lrbWmVZbuD = true;}
      else if(VIAOKBICdT == qMHblAMHTo){LntDxIsKme = true;}
      if(hSSkCVRWWl == GCoweGhBgb){EIucKJVyJc = true;}
      else if(GCoweGhBgb == hSSkCVRWWl){NbYqkAAeVk = true;}
      if(JeWTaOEyTi == FMxEwKqCEd){gPxlXYUuou = true;}
      else if(FMxEwKqCEd == JeWTaOEyTi){PSAqNAtmVO = true;}
      if(LxSEWyznVH == UQhMiioPbB){ytEmDwYNMT = true;}
      else if(UQhMiioPbB == LxSEWyznVH){HzuFwnFZKV = true;}
      if(knZiVVWOTg == sbIuDGVoSE){wfIcVPwTRg = true;}
      else if(sbIuDGVoSE == knZiVVWOTg){ZixbTYKWNS = true;}
      if(eJSeoMpmBX == nyHdfIKwSz){QfATfVuozN = true;}
      if(wNnjcjANOE == KFyzzpTcNw){BdmzEKDIYO = true;}
      if(WcAPBUFmxE == RRYfhcDBAp){jIlogAHTQI = true;}
      while(nyHdfIKwSz == eJSeoMpmBX){QNmmurmDpw = true;}
      while(KFyzzpTcNw == KFyzzpTcNw){OGnXXOfTtw = true;}
      while(RRYfhcDBAp == RRYfhcDBAp){taUzLgUXXn = true;}
      if(oBjzpVIDfa == true){oBjzpVIDfa = false;}
      if(XrxcpmdJwN == true){XrxcpmdJwN = false;}
      if(lrbWmVZbuD == true){lrbWmVZbuD = false;}
      if(EIucKJVyJc == true){EIucKJVyJc = false;}
      if(gPxlXYUuou == true){gPxlXYUuou = false;}
      if(ytEmDwYNMT == true){ytEmDwYNMT = false;}
      if(wfIcVPwTRg == true){wfIcVPwTRg = false;}
      if(QfATfVuozN == true){QfATfVuozN = false;}
      if(BdmzEKDIYO == true){BdmzEKDIYO = false;}
      if(jIlogAHTQI == true){jIlogAHTQI = false;}
      if(cAcHdStkHh == true){cAcHdStkHh = false;}
      if(AiOySRsIYL == true){AiOySRsIYL = false;}
      if(LntDxIsKme == true){LntDxIsKme = false;}
      if(NbYqkAAeVk == true){NbYqkAAeVk = false;}
      if(PSAqNAtmVO == true){PSAqNAtmVO = false;}
      if(HzuFwnFZKV == true){HzuFwnFZKV = false;}
      if(ZixbTYKWNS == true){ZixbTYKWNS = false;}
      if(QNmmurmDpw == true){QNmmurmDpw = false;}
      if(OGnXXOfTtw == true){OGnXXOfTtw = false;}
      if(taUzLgUXXn == true){taUzLgUXXn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZBETJJWZYN
{ 
  void yINVamcdgy()
  { 
      bool pDmZbOGMsM = false;
      bool htpihagHbG = false;
      bool UwQEcrVQKi = false;
      bool LktNnShHlj = false;
      bool rXuojWZLdY = false;
      bool YxSSrtlixj = false;
      bool soCJBwzcuO = false;
      bool sZUrOwAaTF = false;
      bool RKlkKNSbVs = false;
      bool gyKCpCVlnn = false;
      bool XxQPfzcZEu = false;
      bool tKOqRiDQzn = false;
      bool cXHBhtPRBL = false;
      bool aNmfhUtWFK = false;
      bool jsWZzWjSjH = false;
      bool zEmAKzpOgk = false;
      bool iKXsUfWhJw = false;
      bool ofLnDjAgBL = false;
      bool JwgtLVZmVh = false;
      bool eeoUaZUdFT = false;
      string yeJmyLhkcm;
      string jlnHymKJmi;
      string yxEJmdbibw;
      string swLThJWOOK;
      string BlKmIpijIN;
      string XJykAAZAAU;
      string iyIftnaTZo;
      string PutbgLmQAw;
      string traOYixZTg;
      string jWOtbCddsU;
      string POKSxcOVEn;
      string NIzDZqXtGK;
      string qBAsFsfAAd;
      string hIXfgfhHQw;
      string UaUfSaWKTk;
      string eiWicNOQNE;
      string wNVaFFkTWt;
      string IPcKpPfUZd;
      string VUgOyyknCS;
      string RQtMAGEtZM;
      if(yeJmyLhkcm == POKSxcOVEn){pDmZbOGMsM = true;}
      else if(POKSxcOVEn == yeJmyLhkcm){XxQPfzcZEu = true;}
      if(jlnHymKJmi == NIzDZqXtGK){htpihagHbG = true;}
      else if(NIzDZqXtGK == jlnHymKJmi){tKOqRiDQzn = true;}
      if(yxEJmdbibw == qBAsFsfAAd){UwQEcrVQKi = true;}
      else if(qBAsFsfAAd == yxEJmdbibw){cXHBhtPRBL = true;}
      if(swLThJWOOK == hIXfgfhHQw){LktNnShHlj = true;}
      else if(hIXfgfhHQw == swLThJWOOK){aNmfhUtWFK = true;}
      if(BlKmIpijIN == UaUfSaWKTk){rXuojWZLdY = true;}
      else if(UaUfSaWKTk == BlKmIpijIN){jsWZzWjSjH = true;}
      if(XJykAAZAAU == eiWicNOQNE){YxSSrtlixj = true;}
      else if(eiWicNOQNE == XJykAAZAAU){zEmAKzpOgk = true;}
      if(iyIftnaTZo == wNVaFFkTWt){soCJBwzcuO = true;}
      else if(wNVaFFkTWt == iyIftnaTZo){iKXsUfWhJw = true;}
      if(PutbgLmQAw == IPcKpPfUZd){sZUrOwAaTF = true;}
      if(traOYixZTg == VUgOyyknCS){RKlkKNSbVs = true;}
      if(jWOtbCddsU == RQtMAGEtZM){gyKCpCVlnn = true;}
      while(IPcKpPfUZd == PutbgLmQAw){ofLnDjAgBL = true;}
      while(VUgOyyknCS == VUgOyyknCS){JwgtLVZmVh = true;}
      while(RQtMAGEtZM == RQtMAGEtZM){eeoUaZUdFT = true;}
      if(pDmZbOGMsM == true){pDmZbOGMsM = false;}
      if(htpihagHbG == true){htpihagHbG = false;}
      if(UwQEcrVQKi == true){UwQEcrVQKi = false;}
      if(LktNnShHlj == true){LktNnShHlj = false;}
      if(rXuojWZLdY == true){rXuojWZLdY = false;}
      if(YxSSrtlixj == true){YxSSrtlixj = false;}
      if(soCJBwzcuO == true){soCJBwzcuO = false;}
      if(sZUrOwAaTF == true){sZUrOwAaTF = false;}
      if(RKlkKNSbVs == true){RKlkKNSbVs = false;}
      if(gyKCpCVlnn == true){gyKCpCVlnn = false;}
      if(XxQPfzcZEu == true){XxQPfzcZEu = false;}
      if(tKOqRiDQzn == true){tKOqRiDQzn = false;}
      if(cXHBhtPRBL == true){cXHBhtPRBL = false;}
      if(aNmfhUtWFK == true){aNmfhUtWFK = false;}
      if(jsWZzWjSjH == true){jsWZzWjSjH = false;}
      if(zEmAKzpOgk == true){zEmAKzpOgk = false;}
      if(iKXsUfWhJw == true){iKXsUfWhJw = false;}
      if(ofLnDjAgBL == true){ofLnDjAgBL = false;}
      if(JwgtLVZmVh == true){JwgtLVZmVh = false;}
      if(eeoUaZUdFT == true){eeoUaZUdFT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFBTUJQCWZ
{ 
  void fFOueDmQre()
  { 
      bool EhzoJrOJgD = false;
      bool EJmifVoaJF = false;
      bool JYJhYhRYOP = false;
      bool GdOfSshGPy = false;
      bool CLmuLgnmGs = false;
      bool DkVoAeXRPa = false;
      bool ZotRwZuHPm = false;
      bool nhKKDxlOWr = false;
      bool teSUMVIYen = false;
      bool UQpnYMQVyk = false;
      bool kgXTFUZLlC = false;
      bool sJuXguWZEa = false;
      bool RVbbRXrWlq = false;
      bool gPPkGNHzPr = false;
      bool wwmctLVSGc = false;
      bool oqRXTPEuBg = false;
      bool cDZtVdsJQT = false;
      bool nWJMdUizgF = false;
      bool CYPIBpyqQq = false;
      bool ILxhPsWsHQ = false;
      string OAMpwxgzte;
      string IxVLPNqsix;
      string RgLJfNWHds;
      string eXCNHqZjNI;
      string YymZlyFKBM;
      string oQTxggoDKh;
      string aYUBzjtIEX;
      string nGfaYTtkXh;
      string HLGQDOEEfa;
      string CWZehzckaB;
      string DxGcYikrYN;
      string mEebZOSDxk;
      string eocdVRfArY;
      string pIKVdKEdrT;
      string cLfSnyqyES;
      string gZnoWNTcGG;
      string DkAAWdsJyP;
      string JoKdISJKoX;
      string ahuYqQUUzP;
      string pbWlPrLeuJ;
      if(OAMpwxgzte == DxGcYikrYN){EhzoJrOJgD = true;}
      else if(DxGcYikrYN == OAMpwxgzte){kgXTFUZLlC = true;}
      if(IxVLPNqsix == mEebZOSDxk){EJmifVoaJF = true;}
      else if(mEebZOSDxk == IxVLPNqsix){sJuXguWZEa = true;}
      if(RgLJfNWHds == eocdVRfArY){JYJhYhRYOP = true;}
      else if(eocdVRfArY == RgLJfNWHds){RVbbRXrWlq = true;}
      if(eXCNHqZjNI == pIKVdKEdrT){GdOfSshGPy = true;}
      else if(pIKVdKEdrT == eXCNHqZjNI){gPPkGNHzPr = true;}
      if(YymZlyFKBM == cLfSnyqyES){CLmuLgnmGs = true;}
      else if(cLfSnyqyES == YymZlyFKBM){wwmctLVSGc = true;}
      if(oQTxggoDKh == gZnoWNTcGG){DkVoAeXRPa = true;}
      else if(gZnoWNTcGG == oQTxggoDKh){oqRXTPEuBg = true;}
      if(aYUBzjtIEX == DkAAWdsJyP){ZotRwZuHPm = true;}
      else if(DkAAWdsJyP == aYUBzjtIEX){cDZtVdsJQT = true;}
      if(nGfaYTtkXh == JoKdISJKoX){nhKKDxlOWr = true;}
      if(HLGQDOEEfa == ahuYqQUUzP){teSUMVIYen = true;}
      if(CWZehzckaB == pbWlPrLeuJ){UQpnYMQVyk = true;}
      while(JoKdISJKoX == nGfaYTtkXh){nWJMdUizgF = true;}
      while(ahuYqQUUzP == ahuYqQUUzP){CYPIBpyqQq = true;}
      while(pbWlPrLeuJ == pbWlPrLeuJ){ILxhPsWsHQ = true;}
      if(EhzoJrOJgD == true){EhzoJrOJgD = false;}
      if(EJmifVoaJF == true){EJmifVoaJF = false;}
      if(JYJhYhRYOP == true){JYJhYhRYOP = false;}
      if(GdOfSshGPy == true){GdOfSshGPy = false;}
      if(CLmuLgnmGs == true){CLmuLgnmGs = false;}
      if(DkVoAeXRPa == true){DkVoAeXRPa = false;}
      if(ZotRwZuHPm == true){ZotRwZuHPm = false;}
      if(nhKKDxlOWr == true){nhKKDxlOWr = false;}
      if(teSUMVIYen == true){teSUMVIYen = false;}
      if(UQpnYMQVyk == true){UQpnYMQVyk = false;}
      if(kgXTFUZLlC == true){kgXTFUZLlC = false;}
      if(sJuXguWZEa == true){sJuXguWZEa = false;}
      if(RVbbRXrWlq == true){RVbbRXrWlq = false;}
      if(gPPkGNHzPr == true){gPPkGNHzPr = false;}
      if(wwmctLVSGc == true){wwmctLVSGc = false;}
      if(oqRXTPEuBg == true){oqRXTPEuBg = false;}
      if(cDZtVdsJQT == true){cDZtVdsJQT = false;}
      if(nWJMdUizgF == true){nWJMdUizgF = false;}
      if(CYPIBpyqQq == true){CYPIBpyqQq = false;}
      if(ILxhPsWsHQ == true){ILxhPsWsHQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZFZSARGFL
{ 
  void MrdefEutpi()
  { 
      bool YEpAiawdmg = false;
      bool ufJhaseVMC = false;
      bool BLPFhjwCHh = false;
      bool BashiKgWfG = false;
      bool cjPEDKEfqF = false;
      bool MmoxMNojSy = false;
      bool dtWEeTmazP = false;
      bool LHoFYQuKBW = false;
      bool fPKCVOluVV = false;
      bool VxEgciNLYj = false;
      bool XcgasExjXw = false;
      bool RdhwRNiThQ = false;
      bool hqFctNDIbp = false;
      bool DjlRyDijJR = false;
      bool RCXZDqPHOO = false;
      bool ztcIBfXDge = false;
      bool AnHhrhrPxO = false;
      bool ezKQyeTfZC = false;
      bool yusMqJHcQS = false;
      bool eeCdRctpgU = false;
      string BiIzNbKjwk;
      string laHlNySfPm;
      string afDCzOHyma;
      string QFtuPyqZPT;
      string PqaDbdEFDS;
      string cSdkCUeFzz;
      string TMxUUfgMWP;
      string GsPwWjFzaV;
      string JCtTyybIst;
      string SkZQzDsGiw;
      string xrhnLiChNR;
      string PeedpRRcVV;
      string EXTbwVSywT;
      string pzQdYQTGIO;
      string usuaenFuag;
      string lQjNrYYGqp;
      string QDktaQOBFZ;
      string yLUGZKcrxI;
      string PWXPgYODlz;
      string qNORyqIBzO;
      if(BiIzNbKjwk == xrhnLiChNR){YEpAiawdmg = true;}
      else if(xrhnLiChNR == BiIzNbKjwk){XcgasExjXw = true;}
      if(laHlNySfPm == PeedpRRcVV){ufJhaseVMC = true;}
      else if(PeedpRRcVV == laHlNySfPm){RdhwRNiThQ = true;}
      if(afDCzOHyma == EXTbwVSywT){BLPFhjwCHh = true;}
      else if(EXTbwVSywT == afDCzOHyma){hqFctNDIbp = true;}
      if(QFtuPyqZPT == pzQdYQTGIO){BashiKgWfG = true;}
      else if(pzQdYQTGIO == QFtuPyqZPT){DjlRyDijJR = true;}
      if(PqaDbdEFDS == usuaenFuag){cjPEDKEfqF = true;}
      else if(usuaenFuag == PqaDbdEFDS){RCXZDqPHOO = true;}
      if(cSdkCUeFzz == lQjNrYYGqp){MmoxMNojSy = true;}
      else if(lQjNrYYGqp == cSdkCUeFzz){ztcIBfXDge = true;}
      if(TMxUUfgMWP == QDktaQOBFZ){dtWEeTmazP = true;}
      else if(QDktaQOBFZ == TMxUUfgMWP){AnHhrhrPxO = true;}
      if(GsPwWjFzaV == yLUGZKcrxI){LHoFYQuKBW = true;}
      if(JCtTyybIst == PWXPgYODlz){fPKCVOluVV = true;}
      if(SkZQzDsGiw == qNORyqIBzO){VxEgciNLYj = true;}
      while(yLUGZKcrxI == GsPwWjFzaV){ezKQyeTfZC = true;}
      while(PWXPgYODlz == PWXPgYODlz){yusMqJHcQS = true;}
      while(qNORyqIBzO == qNORyqIBzO){eeCdRctpgU = true;}
      if(YEpAiawdmg == true){YEpAiawdmg = false;}
      if(ufJhaseVMC == true){ufJhaseVMC = false;}
      if(BLPFhjwCHh == true){BLPFhjwCHh = false;}
      if(BashiKgWfG == true){BashiKgWfG = false;}
      if(cjPEDKEfqF == true){cjPEDKEfqF = false;}
      if(MmoxMNojSy == true){MmoxMNojSy = false;}
      if(dtWEeTmazP == true){dtWEeTmazP = false;}
      if(LHoFYQuKBW == true){LHoFYQuKBW = false;}
      if(fPKCVOluVV == true){fPKCVOluVV = false;}
      if(VxEgciNLYj == true){VxEgciNLYj = false;}
      if(XcgasExjXw == true){XcgasExjXw = false;}
      if(RdhwRNiThQ == true){RdhwRNiThQ = false;}
      if(hqFctNDIbp == true){hqFctNDIbp = false;}
      if(DjlRyDijJR == true){DjlRyDijJR = false;}
      if(RCXZDqPHOO == true){RCXZDqPHOO = false;}
      if(ztcIBfXDge == true){ztcIBfXDge = false;}
      if(AnHhrhrPxO == true){AnHhrhrPxO = false;}
      if(ezKQyeTfZC == true){ezKQyeTfZC = false;}
      if(yusMqJHcQS == true){yusMqJHcQS = false;}
      if(eeCdRctpgU == true){eeCdRctpgU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUXUSBJHUH
{ 
  void eBpkGYuZiN()
  { 
      bool IUyXFnIdGU = false;
      bool csSbETFbOU = false;
      bool CEtslnPixY = false;
      bool pRMTTmffoP = false;
      bool JRgGrqRClx = false;
      bool EjLqoEaEkR = false;
      bool YZfgdLfzIQ = false;
      bool nYmzKkXmBt = false;
      bool WMwATFFVdO = false;
      bool MatXpilzcg = false;
      bool KRtUIfxMfE = false;
      bool gmCqtLdeMX = false;
      bool FKUsENePIb = false;
      bool zXKUiFRarn = false;
      bool IsoYhYXDdd = false;
      bool FGmEaAxBQu = false;
      bool AgEEFIchHo = false;
      bool tCmXPMUuKe = false;
      bool obldVrkGsi = false;
      bool HQKwmaokTZ = false;
      string OfbuZjiWoZ;
      string uiIAHykIrz;
      string ORpuoDCrfG;
      string xYzrXKpZpA;
      string BBGUipHHdS;
      string BYpBCwpfFV;
      string gqpibWiPbx;
      string ILRrxMKVLy;
      string utONEYhxpa;
      string UKTTSKLWrM;
      string HrffKoGxEo;
      string kUUGZmbcdC;
      string nkZBcyqxZl;
      string BnczqDOhDO;
      string SksAoApNte;
      string hhrpXVSdDM;
      string yIXSnxqUOW;
      string YtYOiDrYLb;
      string HdDuDSumaV;
      string kjdpQKMaMr;
      if(OfbuZjiWoZ == HrffKoGxEo){IUyXFnIdGU = true;}
      else if(HrffKoGxEo == OfbuZjiWoZ){KRtUIfxMfE = true;}
      if(uiIAHykIrz == kUUGZmbcdC){csSbETFbOU = true;}
      else if(kUUGZmbcdC == uiIAHykIrz){gmCqtLdeMX = true;}
      if(ORpuoDCrfG == nkZBcyqxZl){CEtslnPixY = true;}
      else if(nkZBcyqxZl == ORpuoDCrfG){FKUsENePIb = true;}
      if(xYzrXKpZpA == BnczqDOhDO){pRMTTmffoP = true;}
      else if(BnczqDOhDO == xYzrXKpZpA){zXKUiFRarn = true;}
      if(BBGUipHHdS == SksAoApNte){JRgGrqRClx = true;}
      else if(SksAoApNte == BBGUipHHdS){IsoYhYXDdd = true;}
      if(BYpBCwpfFV == hhrpXVSdDM){EjLqoEaEkR = true;}
      else if(hhrpXVSdDM == BYpBCwpfFV){FGmEaAxBQu = true;}
      if(gqpibWiPbx == yIXSnxqUOW){YZfgdLfzIQ = true;}
      else if(yIXSnxqUOW == gqpibWiPbx){AgEEFIchHo = true;}
      if(ILRrxMKVLy == YtYOiDrYLb){nYmzKkXmBt = true;}
      if(utONEYhxpa == HdDuDSumaV){WMwATFFVdO = true;}
      if(UKTTSKLWrM == kjdpQKMaMr){MatXpilzcg = true;}
      while(YtYOiDrYLb == ILRrxMKVLy){tCmXPMUuKe = true;}
      while(HdDuDSumaV == HdDuDSumaV){obldVrkGsi = true;}
      while(kjdpQKMaMr == kjdpQKMaMr){HQKwmaokTZ = true;}
      if(IUyXFnIdGU == true){IUyXFnIdGU = false;}
      if(csSbETFbOU == true){csSbETFbOU = false;}
      if(CEtslnPixY == true){CEtslnPixY = false;}
      if(pRMTTmffoP == true){pRMTTmffoP = false;}
      if(JRgGrqRClx == true){JRgGrqRClx = false;}
      if(EjLqoEaEkR == true){EjLqoEaEkR = false;}
      if(YZfgdLfzIQ == true){YZfgdLfzIQ = false;}
      if(nYmzKkXmBt == true){nYmzKkXmBt = false;}
      if(WMwATFFVdO == true){WMwATFFVdO = false;}
      if(MatXpilzcg == true){MatXpilzcg = false;}
      if(KRtUIfxMfE == true){KRtUIfxMfE = false;}
      if(gmCqtLdeMX == true){gmCqtLdeMX = false;}
      if(FKUsENePIb == true){FKUsENePIb = false;}
      if(zXKUiFRarn == true){zXKUiFRarn = false;}
      if(IsoYhYXDdd == true){IsoYhYXDdd = false;}
      if(FGmEaAxBQu == true){FGmEaAxBQu = false;}
      if(AgEEFIchHo == true){AgEEFIchHo = false;}
      if(tCmXPMUuKe == true){tCmXPMUuKe = false;}
      if(obldVrkGsi == true){obldVrkGsi = false;}
      if(HQKwmaokTZ == true){HQKwmaokTZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXKWQRLTQX
{ 
  void rQfPsKkisT()
  { 
      bool ELGQGGKkoZ = false;
      bool iGaIeXoTPG = false;
      bool oTAGWMXDxK = false;
      bool GdQADCQNfq = false;
      bool lZAgkdeISw = false;
      bool hAximjKAss = false;
      bool iGmeTEoaFc = false;
      bool HamXUOTSUr = false;
      bool hPkAcGghMS = false;
      bool qQTlIelVNg = false;
      bool oDDpoGMYOX = false;
      bool QreALSVmCM = false;
      bool WHNllpHBPo = false;
      bool byFnDdLtKV = false;
      bool tHSoBylSao = false;
      bool JzSAJgpQDy = false;
      bool zLJZwSlpxg = false;
      bool HabfSPnYjm = false;
      bool EnZZfceEdW = false;
      bool ntqMWiysri = false;
      string yOXpsSQWbE;
      string NNpzXaTcOi;
      string lklyhcWUKb;
      string SWKkDOILuz;
      string RUlepuSDxr;
      string JFfaeNcYIQ;
      string wuMAkpCFuJ;
      string RIhOQRzGIm;
      string KSWSRNqjFp;
      string ljDdDVHktA;
      string rMInaBWRJM;
      string NWQUFcYthX;
      string zRzEWgFDLu;
      string JNMItxJiqQ;
      string pYarbOThYZ;
      string xNCVAZMDQs;
      string uTFNDAKHaH;
      string TpCRgZqGbI;
      string NXelywKpHT;
      string jGRyUWTMob;
      if(yOXpsSQWbE == rMInaBWRJM){ELGQGGKkoZ = true;}
      else if(rMInaBWRJM == yOXpsSQWbE){oDDpoGMYOX = true;}
      if(NNpzXaTcOi == NWQUFcYthX){iGaIeXoTPG = true;}
      else if(NWQUFcYthX == NNpzXaTcOi){QreALSVmCM = true;}
      if(lklyhcWUKb == zRzEWgFDLu){oTAGWMXDxK = true;}
      else if(zRzEWgFDLu == lklyhcWUKb){WHNllpHBPo = true;}
      if(SWKkDOILuz == JNMItxJiqQ){GdQADCQNfq = true;}
      else if(JNMItxJiqQ == SWKkDOILuz){byFnDdLtKV = true;}
      if(RUlepuSDxr == pYarbOThYZ){lZAgkdeISw = true;}
      else if(pYarbOThYZ == RUlepuSDxr){tHSoBylSao = true;}
      if(JFfaeNcYIQ == xNCVAZMDQs){hAximjKAss = true;}
      else if(xNCVAZMDQs == JFfaeNcYIQ){JzSAJgpQDy = true;}
      if(wuMAkpCFuJ == uTFNDAKHaH){iGmeTEoaFc = true;}
      else if(uTFNDAKHaH == wuMAkpCFuJ){zLJZwSlpxg = true;}
      if(RIhOQRzGIm == TpCRgZqGbI){HamXUOTSUr = true;}
      if(KSWSRNqjFp == NXelywKpHT){hPkAcGghMS = true;}
      if(ljDdDVHktA == jGRyUWTMob){qQTlIelVNg = true;}
      while(TpCRgZqGbI == RIhOQRzGIm){HabfSPnYjm = true;}
      while(NXelywKpHT == NXelywKpHT){EnZZfceEdW = true;}
      while(jGRyUWTMob == jGRyUWTMob){ntqMWiysri = true;}
      if(ELGQGGKkoZ == true){ELGQGGKkoZ = false;}
      if(iGaIeXoTPG == true){iGaIeXoTPG = false;}
      if(oTAGWMXDxK == true){oTAGWMXDxK = false;}
      if(GdQADCQNfq == true){GdQADCQNfq = false;}
      if(lZAgkdeISw == true){lZAgkdeISw = false;}
      if(hAximjKAss == true){hAximjKAss = false;}
      if(iGmeTEoaFc == true){iGmeTEoaFc = false;}
      if(HamXUOTSUr == true){HamXUOTSUr = false;}
      if(hPkAcGghMS == true){hPkAcGghMS = false;}
      if(qQTlIelVNg == true){qQTlIelVNg = false;}
      if(oDDpoGMYOX == true){oDDpoGMYOX = false;}
      if(QreALSVmCM == true){QreALSVmCM = false;}
      if(WHNllpHBPo == true){WHNllpHBPo = false;}
      if(byFnDdLtKV == true){byFnDdLtKV = false;}
      if(tHSoBylSao == true){tHSoBylSao = false;}
      if(JzSAJgpQDy == true){JzSAJgpQDy = false;}
      if(zLJZwSlpxg == true){zLJZwSlpxg = false;}
      if(HabfSPnYjm == true){HabfSPnYjm = false;}
      if(EnZZfceEdW == true){EnZZfceEdW = false;}
      if(ntqMWiysri == true){ntqMWiysri = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZDYFSYLBT
{ 
  void kecMOjsadW()
  { 
      bool VUaxCInnRE = false;
      bool KWniGgGFKt = false;
      bool xaLcFJNmgO = false;
      bool KSzmEQjCZg = false;
      bool UmrlepHAuq = false;
      bool ocmCYtJxqr = false;
      bool uBGCtqWBdo = false;
      bool wEedYKhYyP = false;
      bool CMqpYgfwNJ = false;
      bool HmLgkTform = false;
      bool SGWGtkxIdO = false;
      bool LjzapiJPdM = false;
      bool LZmUhJrxrE = false;
      bool dsgKxwpkwn = false;
      bool iWSzxWmjqC = false;
      bool JQLebrSBXk = false;
      bool rzQYjSDodt = false;
      bool rYTocoHnXL = false;
      bool VIGotMgCiE = false;
      bool coMKujFtOd = false;
      string JCbPIkMrnJ;
      string gDSHuOQynO;
      string liBsSHqnPC;
      string YoodOgtcRz;
      string VnAYyHHuEU;
      string lCGqmaAiwA;
      string tYckjrOorN;
      string TmgosxhbtK;
      string AwitPWhxpm;
      string fLfQFwLOoG;
      string sSCpAzVRyo;
      string rYolAyphVM;
      string JQyEhIGPjw;
      string lTmmRgsrtQ;
      string BQzAuHWtPH;
      string GcscxbTxIr;
      string rFhBDYkBTS;
      string ExnFKsQxJZ;
      string lLzbpJaKpp;
      string MujBXwhyxW;
      if(JCbPIkMrnJ == sSCpAzVRyo){VUaxCInnRE = true;}
      else if(sSCpAzVRyo == JCbPIkMrnJ){SGWGtkxIdO = true;}
      if(gDSHuOQynO == rYolAyphVM){KWniGgGFKt = true;}
      else if(rYolAyphVM == gDSHuOQynO){LjzapiJPdM = true;}
      if(liBsSHqnPC == JQyEhIGPjw){xaLcFJNmgO = true;}
      else if(JQyEhIGPjw == liBsSHqnPC){LZmUhJrxrE = true;}
      if(YoodOgtcRz == lTmmRgsrtQ){KSzmEQjCZg = true;}
      else if(lTmmRgsrtQ == YoodOgtcRz){dsgKxwpkwn = true;}
      if(VnAYyHHuEU == BQzAuHWtPH){UmrlepHAuq = true;}
      else if(BQzAuHWtPH == VnAYyHHuEU){iWSzxWmjqC = true;}
      if(lCGqmaAiwA == GcscxbTxIr){ocmCYtJxqr = true;}
      else if(GcscxbTxIr == lCGqmaAiwA){JQLebrSBXk = true;}
      if(tYckjrOorN == rFhBDYkBTS){uBGCtqWBdo = true;}
      else if(rFhBDYkBTS == tYckjrOorN){rzQYjSDodt = true;}
      if(TmgosxhbtK == ExnFKsQxJZ){wEedYKhYyP = true;}
      if(AwitPWhxpm == lLzbpJaKpp){CMqpYgfwNJ = true;}
      if(fLfQFwLOoG == MujBXwhyxW){HmLgkTform = true;}
      while(ExnFKsQxJZ == TmgosxhbtK){rYTocoHnXL = true;}
      while(lLzbpJaKpp == lLzbpJaKpp){VIGotMgCiE = true;}
      while(MujBXwhyxW == MujBXwhyxW){coMKujFtOd = true;}
      if(VUaxCInnRE == true){VUaxCInnRE = false;}
      if(KWniGgGFKt == true){KWniGgGFKt = false;}
      if(xaLcFJNmgO == true){xaLcFJNmgO = false;}
      if(KSzmEQjCZg == true){KSzmEQjCZg = false;}
      if(UmrlepHAuq == true){UmrlepHAuq = false;}
      if(ocmCYtJxqr == true){ocmCYtJxqr = false;}
      if(uBGCtqWBdo == true){uBGCtqWBdo = false;}
      if(wEedYKhYyP == true){wEedYKhYyP = false;}
      if(CMqpYgfwNJ == true){CMqpYgfwNJ = false;}
      if(HmLgkTform == true){HmLgkTform = false;}
      if(SGWGtkxIdO == true){SGWGtkxIdO = false;}
      if(LjzapiJPdM == true){LjzapiJPdM = false;}
      if(LZmUhJrxrE == true){LZmUhJrxrE = false;}
      if(dsgKxwpkwn == true){dsgKxwpkwn = false;}
      if(iWSzxWmjqC == true){iWSzxWmjqC = false;}
      if(JQLebrSBXk == true){JQLebrSBXk = false;}
      if(rzQYjSDodt == true){rzQYjSDodt = false;}
      if(rYTocoHnXL == true){rYTocoHnXL = false;}
      if(VIGotMgCiE == true){VIGotMgCiE = false;}
      if(coMKujFtOd == true){coMKujFtOd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHVPOQUXNF
{ 
  void aUVlHYetHN()
  { 
      bool gZgtrzeGRP = false;
      bool NlHWUOnklF = false;
      bool VSWAYsLGwO = false;
      bool mBaTIiuYNN = false;
      bool hPbMAAAFuA = false;
      bool HKULhODfVz = false;
      bool mYKDcMKmNk = false;
      bool TOWXWFpJzX = false;
      bool rGKuGcfPls = false;
      bool fPCOZJEYjn = false;
      bool oNqKgrmwnb = false;
      bool YsfxGfOPwz = false;
      bool fuBUFEMIyN = false;
      bool BQYLiePzON = false;
      bool oibKTliFHs = false;
      bool tocjItLVFc = false;
      bool feyZZHUUOb = false;
      bool QOAhJwSqAS = false;
      bool UHAESMnoCo = false;
      bool SstlgKjBjM = false;
      string AKfmYHKWtg;
      string AhZbtCkwsp;
      string VuKKTWfxAG;
      string eCQggeUPlK;
      string bnWtQAzsLt;
      string krYMPEAUTB;
      string bMVmBxRruO;
      string hUKhOgXPtT;
      string XlkFVlcDRb;
      string ezwjiORirS;
      string iGyxLPhpyh;
      string fjazdobQRP;
      string UNaSjhYZzz;
      string PnWajRnnsG;
      string ElFiutYwGs;
      string mBRcyVeeMd;
      string qHqySrMzPL;
      string BmWLKhHrXp;
      string IbTFMNWtcO;
      string mIbPOwuGQD;
      if(AKfmYHKWtg == iGyxLPhpyh){gZgtrzeGRP = true;}
      else if(iGyxLPhpyh == AKfmYHKWtg){oNqKgrmwnb = true;}
      if(AhZbtCkwsp == fjazdobQRP){NlHWUOnklF = true;}
      else if(fjazdobQRP == AhZbtCkwsp){YsfxGfOPwz = true;}
      if(VuKKTWfxAG == UNaSjhYZzz){VSWAYsLGwO = true;}
      else if(UNaSjhYZzz == VuKKTWfxAG){fuBUFEMIyN = true;}
      if(eCQggeUPlK == PnWajRnnsG){mBaTIiuYNN = true;}
      else if(PnWajRnnsG == eCQggeUPlK){BQYLiePzON = true;}
      if(bnWtQAzsLt == ElFiutYwGs){hPbMAAAFuA = true;}
      else if(ElFiutYwGs == bnWtQAzsLt){oibKTliFHs = true;}
      if(krYMPEAUTB == mBRcyVeeMd){HKULhODfVz = true;}
      else if(mBRcyVeeMd == krYMPEAUTB){tocjItLVFc = true;}
      if(bMVmBxRruO == qHqySrMzPL){mYKDcMKmNk = true;}
      else if(qHqySrMzPL == bMVmBxRruO){feyZZHUUOb = true;}
      if(hUKhOgXPtT == BmWLKhHrXp){TOWXWFpJzX = true;}
      if(XlkFVlcDRb == IbTFMNWtcO){rGKuGcfPls = true;}
      if(ezwjiORirS == mIbPOwuGQD){fPCOZJEYjn = true;}
      while(BmWLKhHrXp == hUKhOgXPtT){QOAhJwSqAS = true;}
      while(IbTFMNWtcO == IbTFMNWtcO){UHAESMnoCo = true;}
      while(mIbPOwuGQD == mIbPOwuGQD){SstlgKjBjM = true;}
      if(gZgtrzeGRP == true){gZgtrzeGRP = false;}
      if(NlHWUOnklF == true){NlHWUOnklF = false;}
      if(VSWAYsLGwO == true){VSWAYsLGwO = false;}
      if(mBaTIiuYNN == true){mBaTIiuYNN = false;}
      if(hPbMAAAFuA == true){hPbMAAAFuA = false;}
      if(HKULhODfVz == true){HKULhODfVz = false;}
      if(mYKDcMKmNk == true){mYKDcMKmNk = false;}
      if(TOWXWFpJzX == true){TOWXWFpJzX = false;}
      if(rGKuGcfPls == true){rGKuGcfPls = false;}
      if(fPCOZJEYjn == true){fPCOZJEYjn = false;}
      if(oNqKgrmwnb == true){oNqKgrmwnb = false;}
      if(YsfxGfOPwz == true){YsfxGfOPwz = false;}
      if(fuBUFEMIyN == true){fuBUFEMIyN = false;}
      if(BQYLiePzON == true){BQYLiePzON = false;}
      if(oibKTliFHs == true){oibKTliFHs = false;}
      if(tocjItLVFc == true){tocjItLVFc = false;}
      if(feyZZHUUOb == true){feyZZHUUOb = false;}
      if(QOAhJwSqAS == true){QOAhJwSqAS = false;}
      if(UHAESMnoCo == true){UHAESMnoCo = false;}
      if(SstlgKjBjM == true){SstlgKjBjM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLKZBTMZKH
{ 
  void SZhmoryYww()
  { 
      bool gOUFBlpgWR = false;
      bool HehjNYrPWc = false;
      bool FWAoGweUVP = false;
      bool PuyGhOGokN = false;
      bool WfcyTrWhta = false;
      bool PZpIdJNezF = false;
      bool HVLGBMfaBz = false;
      bool SCdJFZsBVN = false;
      bool ZxZtApEpcX = false;
      bool AapfGATWxG = false;
      bool LufuIMugCD = false;
      bool QLJkfKwQFL = false;
      bool HpxcyrMyCE = false;
      bool FVEOBdQdlm = false;
      bool uWmYHoREAw = false;
      bool EDQkzVyDwP = false;
      bool AwexytGtjB = false;
      bool sReSQkCXVJ = false;
      bool aHyGACFTPf = false;
      bool eNhVmyrpaN = false;
      string glRYhHmOcy;
      string lbVlkhWGcd;
      string DHKIIEjomo;
      string NDlGJwrMbE;
      string uYPACCqqGo;
      string YyRqEZbJPc;
      string WxankipObn;
      string pKdXieqKFF;
      string NsiyPPltCj;
      string UhwzhyxaPT;
      string MbPRyOTsIY;
      string hRDKPdOcXU;
      string xuMqSHNepj;
      string hPtlslcQzB;
      string wrlcBDeliD;
      string jTDtVROXzp;
      string AnCXqRWQQd;
      string BxcVXEJjpO;
      string caumANMzPb;
      string WERIAIoNli;
      if(glRYhHmOcy == MbPRyOTsIY){gOUFBlpgWR = true;}
      else if(MbPRyOTsIY == glRYhHmOcy){LufuIMugCD = true;}
      if(lbVlkhWGcd == hRDKPdOcXU){HehjNYrPWc = true;}
      else if(hRDKPdOcXU == lbVlkhWGcd){QLJkfKwQFL = true;}
      if(DHKIIEjomo == xuMqSHNepj){FWAoGweUVP = true;}
      else if(xuMqSHNepj == DHKIIEjomo){HpxcyrMyCE = true;}
      if(NDlGJwrMbE == hPtlslcQzB){PuyGhOGokN = true;}
      else if(hPtlslcQzB == NDlGJwrMbE){FVEOBdQdlm = true;}
      if(uYPACCqqGo == wrlcBDeliD){WfcyTrWhta = true;}
      else if(wrlcBDeliD == uYPACCqqGo){uWmYHoREAw = true;}
      if(YyRqEZbJPc == jTDtVROXzp){PZpIdJNezF = true;}
      else if(jTDtVROXzp == YyRqEZbJPc){EDQkzVyDwP = true;}
      if(WxankipObn == AnCXqRWQQd){HVLGBMfaBz = true;}
      else if(AnCXqRWQQd == WxankipObn){AwexytGtjB = true;}
      if(pKdXieqKFF == BxcVXEJjpO){SCdJFZsBVN = true;}
      if(NsiyPPltCj == caumANMzPb){ZxZtApEpcX = true;}
      if(UhwzhyxaPT == WERIAIoNli){AapfGATWxG = true;}
      while(BxcVXEJjpO == pKdXieqKFF){sReSQkCXVJ = true;}
      while(caumANMzPb == caumANMzPb){aHyGACFTPf = true;}
      while(WERIAIoNli == WERIAIoNli){eNhVmyrpaN = true;}
      if(gOUFBlpgWR == true){gOUFBlpgWR = false;}
      if(HehjNYrPWc == true){HehjNYrPWc = false;}
      if(FWAoGweUVP == true){FWAoGweUVP = false;}
      if(PuyGhOGokN == true){PuyGhOGokN = false;}
      if(WfcyTrWhta == true){WfcyTrWhta = false;}
      if(PZpIdJNezF == true){PZpIdJNezF = false;}
      if(HVLGBMfaBz == true){HVLGBMfaBz = false;}
      if(SCdJFZsBVN == true){SCdJFZsBVN = false;}
      if(ZxZtApEpcX == true){ZxZtApEpcX = false;}
      if(AapfGATWxG == true){AapfGATWxG = false;}
      if(LufuIMugCD == true){LufuIMugCD = false;}
      if(QLJkfKwQFL == true){QLJkfKwQFL = false;}
      if(HpxcyrMyCE == true){HpxcyrMyCE = false;}
      if(FVEOBdQdlm == true){FVEOBdQdlm = false;}
      if(uWmYHoREAw == true){uWmYHoREAw = false;}
      if(EDQkzVyDwP == true){EDQkzVyDwP = false;}
      if(AwexytGtjB == true){AwexytGtjB = false;}
      if(sReSQkCXVJ == true){sReSQkCXVJ = false;}
      if(aHyGACFTPf == true){aHyGACFTPf = false;}
      if(eNhVmyrpaN == true){eNhVmyrpaN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZAGWZMHLY
{ 
  void VcPXcedRkw()
  { 
      bool drIOIeupzN = false;
      bool DclHudMymo = false;
      bool cKCxcCHlbZ = false;
      bool zOdbHUcQlX = false;
      bool ySzbtwsIci = false;
      bool hSjogTpLlF = false;
      bool XIOZOoyJzZ = false;
      bool AuLPqJKZDf = false;
      bool JyJsrfeoun = false;
      bool dRefAoEZMF = false;
      bool yiICilGTyW = false;
      bool JPHFwYyUhh = false;
      bool JJOLwhQfOB = false;
      bool EkNxhaoHKF = false;
      bool ZKpXeNJYib = false;
      bool piqeuoTxGA = false;
      bool VaEwRXCKXV = false;
      bool iqKcIySpgh = false;
      bool XqwmLVsiBs = false;
      bool GrBJjzFsFG = false;
      string HZRCUoFMjf;
      string lQqCeWsjsu;
      string UqDjjplqke;
      string ubDZqmdJIf;
      string BYDKNDYVLz;
      string rRpqdQVhRd;
      string CObFjKMQLq;
      string sjbNswnsWf;
      string RPellckLua;
      string QuqdcmwyZC;
      string qHKUFIpcxh;
      string ccLlMmipSG;
      string YAVkZxrxjG;
      string zoSToKFKfd;
      string mIOMxnjFQp;
      string DFfTdpkZtI;
      string QrrqhmJqwC;
      string hYKoTPlIml;
      string NlftDsJzoy;
      string YeQXMtQWdK;
      if(HZRCUoFMjf == qHKUFIpcxh){drIOIeupzN = true;}
      else if(qHKUFIpcxh == HZRCUoFMjf){yiICilGTyW = true;}
      if(lQqCeWsjsu == ccLlMmipSG){DclHudMymo = true;}
      else if(ccLlMmipSG == lQqCeWsjsu){JPHFwYyUhh = true;}
      if(UqDjjplqke == YAVkZxrxjG){cKCxcCHlbZ = true;}
      else if(YAVkZxrxjG == UqDjjplqke){JJOLwhQfOB = true;}
      if(ubDZqmdJIf == zoSToKFKfd){zOdbHUcQlX = true;}
      else if(zoSToKFKfd == ubDZqmdJIf){EkNxhaoHKF = true;}
      if(BYDKNDYVLz == mIOMxnjFQp){ySzbtwsIci = true;}
      else if(mIOMxnjFQp == BYDKNDYVLz){ZKpXeNJYib = true;}
      if(rRpqdQVhRd == DFfTdpkZtI){hSjogTpLlF = true;}
      else if(DFfTdpkZtI == rRpqdQVhRd){piqeuoTxGA = true;}
      if(CObFjKMQLq == QrrqhmJqwC){XIOZOoyJzZ = true;}
      else if(QrrqhmJqwC == CObFjKMQLq){VaEwRXCKXV = true;}
      if(sjbNswnsWf == hYKoTPlIml){AuLPqJKZDf = true;}
      if(RPellckLua == NlftDsJzoy){JyJsrfeoun = true;}
      if(QuqdcmwyZC == YeQXMtQWdK){dRefAoEZMF = true;}
      while(hYKoTPlIml == sjbNswnsWf){iqKcIySpgh = true;}
      while(NlftDsJzoy == NlftDsJzoy){XqwmLVsiBs = true;}
      while(YeQXMtQWdK == YeQXMtQWdK){GrBJjzFsFG = true;}
      if(drIOIeupzN == true){drIOIeupzN = false;}
      if(DclHudMymo == true){DclHudMymo = false;}
      if(cKCxcCHlbZ == true){cKCxcCHlbZ = false;}
      if(zOdbHUcQlX == true){zOdbHUcQlX = false;}
      if(ySzbtwsIci == true){ySzbtwsIci = false;}
      if(hSjogTpLlF == true){hSjogTpLlF = false;}
      if(XIOZOoyJzZ == true){XIOZOoyJzZ = false;}
      if(AuLPqJKZDf == true){AuLPqJKZDf = false;}
      if(JyJsrfeoun == true){JyJsrfeoun = false;}
      if(dRefAoEZMF == true){dRefAoEZMF = false;}
      if(yiICilGTyW == true){yiICilGTyW = false;}
      if(JPHFwYyUhh == true){JPHFwYyUhh = false;}
      if(JJOLwhQfOB == true){JJOLwhQfOB = false;}
      if(EkNxhaoHKF == true){EkNxhaoHKF = false;}
      if(ZKpXeNJYib == true){ZKpXeNJYib = false;}
      if(piqeuoTxGA == true){piqeuoTxGA = false;}
      if(VaEwRXCKXV == true){VaEwRXCKXV = false;}
      if(iqKcIySpgh == true){iqKcIySpgh = false;}
      if(XqwmLVsiBs == true){XqwmLVsiBs = false;}
      if(GrBJjzFsFG == true){GrBJjzFsFG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQBDRRJFYU
{ 
  void ChyrCYTrdD()
  { 
      bool HrRimmVDWJ = false;
      bool pnwbalwdis = false;
      bool GXghiNSTiV = false;
      bool VstTyYauIW = false;
      bool qxMnwJXPbH = false;
      bool PQpbsjLizZ = false;
      bool UCUBmwtbdC = false;
      bool KBVMCJKrkY = false;
      bool oCqaFFDRZO = false;
      bool NquhCobLBA = false;
      bool PulZwOucZj = false;
      bool YSxajRKtug = false;
      bool rcCOnTFmKN = false;
      bool gzqkIsQQeq = false;
      bool KaqppusUyj = false;
      bool dhPTHmsWlc = false;
      bool IISMCYaMRp = false;
      bool AtPEWRkLYs = false;
      bool ZjnZizjWcV = false;
      bool zseBhCHenR = false;
      string mebtPkhUND;
      string JLHaGVqfpn;
      string fhTqnfqRWc;
      string ZLHXCXJIji;
      string yLSEIyfPls;
      string sQzohELkFj;
      string tQxkdxDiXh;
      string MhuHoTPOio;
      string zaecjIMSpx;
      string LYCAohNhZL;
      string txqEgKVrzN;
      string owBPjSkTBU;
      string kksaVnftRG;
      string GhoXuCjawY;
      string mTScHPWmQV;
      string xsfEZIEPir;
      string eaZsGHHdUg;
      string hKXchQSPTG;
      string RsdwJMBjxl;
      string yUrDsMtYVz;
      if(mebtPkhUND == txqEgKVrzN){HrRimmVDWJ = true;}
      else if(txqEgKVrzN == mebtPkhUND){PulZwOucZj = true;}
      if(JLHaGVqfpn == owBPjSkTBU){pnwbalwdis = true;}
      else if(owBPjSkTBU == JLHaGVqfpn){YSxajRKtug = true;}
      if(fhTqnfqRWc == kksaVnftRG){GXghiNSTiV = true;}
      else if(kksaVnftRG == fhTqnfqRWc){rcCOnTFmKN = true;}
      if(ZLHXCXJIji == GhoXuCjawY){VstTyYauIW = true;}
      else if(GhoXuCjawY == ZLHXCXJIji){gzqkIsQQeq = true;}
      if(yLSEIyfPls == mTScHPWmQV){qxMnwJXPbH = true;}
      else if(mTScHPWmQV == yLSEIyfPls){KaqppusUyj = true;}
      if(sQzohELkFj == xsfEZIEPir){PQpbsjLizZ = true;}
      else if(xsfEZIEPir == sQzohELkFj){dhPTHmsWlc = true;}
      if(tQxkdxDiXh == eaZsGHHdUg){UCUBmwtbdC = true;}
      else if(eaZsGHHdUg == tQxkdxDiXh){IISMCYaMRp = true;}
      if(MhuHoTPOio == hKXchQSPTG){KBVMCJKrkY = true;}
      if(zaecjIMSpx == RsdwJMBjxl){oCqaFFDRZO = true;}
      if(LYCAohNhZL == yUrDsMtYVz){NquhCobLBA = true;}
      while(hKXchQSPTG == MhuHoTPOio){AtPEWRkLYs = true;}
      while(RsdwJMBjxl == RsdwJMBjxl){ZjnZizjWcV = true;}
      while(yUrDsMtYVz == yUrDsMtYVz){zseBhCHenR = true;}
      if(HrRimmVDWJ == true){HrRimmVDWJ = false;}
      if(pnwbalwdis == true){pnwbalwdis = false;}
      if(GXghiNSTiV == true){GXghiNSTiV = false;}
      if(VstTyYauIW == true){VstTyYauIW = false;}
      if(qxMnwJXPbH == true){qxMnwJXPbH = false;}
      if(PQpbsjLizZ == true){PQpbsjLizZ = false;}
      if(UCUBmwtbdC == true){UCUBmwtbdC = false;}
      if(KBVMCJKrkY == true){KBVMCJKrkY = false;}
      if(oCqaFFDRZO == true){oCqaFFDRZO = false;}
      if(NquhCobLBA == true){NquhCobLBA = false;}
      if(PulZwOucZj == true){PulZwOucZj = false;}
      if(YSxajRKtug == true){YSxajRKtug = false;}
      if(rcCOnTFmKN == true){rcCOnTFmKN = false;}
      if(gzqkIsQQeq == true){gzqkIsQQeq = false;}
      if(KaqppusUyj == true){KaqppusUyj = false;}
      if(dhPTHmsWlc == true){dhPTHmsWlc = false;}
      if(IISMCYaMRp == true){IISMCYaMRp = false;}
      if(AtPEWRkLYs == true){AtPEWRkLYs = false;}
      if(ZjnZizjWcV == true){ZjnZizjWcV = false;}
      if(zseBhCHenR == true){zseBhCHenR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YICQNZOOYC
{ 
  void yBxydRDmIU()
  { 
      bool boeIPtCGpD = false;
      bool rpLAlujtsu = false;
      bool wdpcZDUBcn = false;
      bool AQbWeVqHhj = false;
      bool rBUmgkREch = false;
      bool TzoTPxyCiL = false;
      bool YAcCCaOnVQ = false;
      bool EbLICtJDwo = false;
      bool lPXuTBbHHg = false;
      bool WnYVLqYRkF = false;
      bool WchLcrmfRV = false;
      bool nuGsYIcgiB = false;
      bool yHgotPCpxL = false;
      bool VqRpSJgMSb = false;
      bool NwplsahewC = false;
      bool OqijGPwsRM = false;
      bool oxhFzwdPaP = false;
      bool bQOGmCQtwS = false;
      bool hWsuxdIhiC = false;
      bool MntFmQNjlw = false;
      string ZwaaRWmXGm;
      string DrXiqBfRWx;
      string gRkqwTyFzn;
      string IDIUwObdUZ;
      string pVhKbhffKF;
      string WahdNILjey;
      string XhXSeAjDlc;
      string ZBxwGKjZON;
      string mRtsQhVdHn;
      string DqyVCHxOfb;
      string xcsgfUckWC;
      string XkURLFmdCx;
      string dGuyZhDbtz;
      string NUtmPJXNNu;
      string FjGEPSWgKw;
      string TSMixqhuHy;
      string RBqXoDpgBB;
      string gZQGrtzqiG;
      string LVQxetHLpY;
      string bcFPcEshPL;
      if(ZwaaRWmXGm == xcsgfUckWC){boeIPtCGpD = true;}
      else if(xcsgfUckWC == ZwaaRWmXGm){WchLcrmfRV = true;}
      if(DrXiqBfRWx == XkURLFmdCx){rpLAlujtsu = true;}
      else if(XkURLFmdCx == DrXiqBfRWx){nuGsYIcgiB = true;}
      if(gRkqwTyFzn == dGuyZhDbtz){wdpcZDUBcn = true;}
      else if(dGuyZhDbtz == gRkqwTyFzn){yHgotPCpxL = true;}
      if(IDIUwObdUZ == NUtmPJXNNu){AQbWeVqHhj = true;}
      else if(NUtmPJXNNu == IDIUwObdUZ){VqRpSJgMSb = true;}
      if(pVhKbhffKF == FjGEPSWgKw){rBUmgkREch = true;}
      else if(FjGEPSWgKw == pVhKbhffKF){NwplsahewC = true;}
      if(WahdNILjey == TSMixqhuHy){TzoTPxyCiL = true;}
      else if(TSMixqhuHy == WahdNILjey){OqijGPwsRM = true;}
      if(XhXSeAjDlc == RBqXoDpgBB){YAcCCaOnVQ = true;}
      else if(RBqXoDpgBB == XhXSeAjDlc){oxhFzwdPaP = true;}
      if(ZBxwGKjZON == gZQGrtzqiG){EbLICtJDwo = true;}
      if(mRtsQhVdHn == LVQxetHLpY){lPXuTBbHHg = true;}
      if(DqyVCHxOfb == bcFPcEshPL){WnYVLqYRkF = true;}
      while(gZQGrtzqiG == ZBxwGKjZON){bQOGmCQtwS = true;}
      while(LVQxetHLpY == LVQxetHLpY){hWsuxdIhiC = true;}
      while(bcFPcEshPL == bcFPcEshPL){MntFmQNjlw = true;}
      if(boeIPtCGpD == true){boeIPtCGpD = false;}
      if(rpLAlujtsu == true){rpLAlujtsu = false;}
      if(wdpcZDUBcn == true){wdpcZDUBcn = false;}
      if(AQbWeVqHhj == true){AQbWeVqHhj = false;}
      if(rBUmgkREch == true){rBUmgkREch = false;}
      if(TzoTPxyCiL == true){TzoTPxyCiL = false;}
      if(YAcCCaOnVQ == true){YAcCCaOnVQ = false;}
      if(EbLICtJDwo == true){EbLICtJDwo = false;}
      if(lPXuTBbHHg == true){lPXuTBbHHg = false;}
      if(WnYVLqYRkF == true){WnYVLqYRkF = false;}
      if(WchLcrmfRV == true){WchLcrmfRV = false;}
      if(nuGsYIcgiB == true){nuGsYIcgiB = false;}
      if(yHgotPCpxL == true){yHgotPCpxL = false;}
      if(VqRpSJgMSb == true){VqRpSJgMSb = false;}
      if(NwplsahewC == true){NwplsahewC = false;}
      if(OqijGPwsRM == true){OqijGPwsRM = false;}
      if(oxhFzwdPaP == true){oxhFzwdPaP = false;}
      if(bQOGmCQtwS == true){bQOGmCQtwS = false;}
      if(hWsuxdIhiC == true){hWsuxdIhiC = false;}
      if(MntFmQNjlw == true){MntFmQNjlw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNNFRHUTUN
{ 
  void WeANffkThy()
  { 
      bool jAtMyHBSKN = false;
      bool sXJnWFNBqF = false;
      bool lNGkTBEkoh = false;
      bool mnrSuhPDdk = false;
      bool PhKXFiSaZQ = false;
      bool mXJKGVtJsx = false;
      bool CQdbaFepsn = false;
      bool pJXGoEDiek = false;
      bool idLXuOehMY = false;
      bool nFJgizDhwA = false;
      bool DbhkacADUB = false;
      bool SLeINXFFgL = false;
      bool axdTAjzqWp = false;
      bool AUlegHwZxS = false;
      bool OaNLGbaBSK = false;
      bool txBkZGxNkp = false;
      bool dJgeAxZzaG = false;
      bool bfIOxzjRNX = false;
      bool JyXMwCTAEa = false;
      bool JinGnEthKI = false;
      string AYNpUEwKaW;
      string dOMMHjBZAj;
      string GaDCawPpqk;
      string xbuEWnJNWr;
      string klSgueiDmH;
      string rjpErYULOY;
      string nGSpZCSHoS;
      string ZmCIzTHVGu;
      string MMCjrMkqLx;
      string SyyyEeScGs;
      string LaNTgFhhFY;
      string RzFTLbDiyN;
      string QburzboDEU;
      string BeONilyiCm;
      string dDlmfTremb;
      string bidsbjfVTF;
      string PddjXmjrjZ;
      string dTgLiNpILf;
      string iKQbsRAVkz;
      string GbOwWAZBPr;
      if(AYNpUEwKaW == LaNTgFhhFY){jAtMyHBSKN = true;}
      else if(LaNTgFhhFY == AYNpUEwKaW){DbhkacADUB = true;}
      if(dOMMHjBZAj == RzFTLbDiyN){sXJnWFNBqF = true;}
      else if(RzFTLbDiyN == dOMMHjBZAj){SLeINXFFgL = true;}
      if(GaDCawPpqk == QburzboDEU){lNGkTBEkoh = true;}
      else if(QburzboDEU == GaDCawPpqk){axdTAjzqWp = true;}
      if(xbuEWnJNWr == BeONilyiCm){mnrSuhPDdk = true;}
      else if(BeONilyiCm == xbuEWnJNWr){AUlegHwZxS = true;}
      if(klSgueiDmH == dDlmfTremb){PhKXFiSaZQ = true;}
      else if(dDlmfTremb == klSgueiDmH){OaNLGbaBSK = true;}
      if(rjpErYULOY == bidsbjfVTF){mXJKGVtJsx = true;}
      else if(bidsbjfVTF == rjpErYULOY){txBkZGxNkp = true;}
      if(nGSpZCSHoS == PddjXmjrjZ){CQdbaFepsn = true;}
      else if(PddjXmjrjZ == nGSpZCSHoS){dJgeAxZzaG = true;}
      if(ZmCIzTHVGu == dTgLiNpILf){pJXGoEDiek = true;}
      if(MMCjrMkqLx == iKQbsRAVkz){idLXuOehMY = true;}
      if(SyyyEeScGs == GbOwWAZBPr){nFJgizDhwA = true;}
      while(dTgLiNpILf == ZmCIzTHVGu){bfIOxzjRNX = true;}
      while(iKQbsRAVkz == iKQbsRAVkz){JyXMwCTAEa = true;}
      while(GbOwWAZBPr == GbOwWAZBPr){JinGnEthKI = true;}
      if(jAtMyHBSKN == true){jAtMyHBSKN = false;}
      if(sXJnWFNBqF == true){sXJnWFNBqF = false;}
      if(lNGkTBEkoh == true){lNGkTBEkoh = false;}
      if(mnrSuhPDdk == true){mnrSuhPDdk = false;}
      if(PhKXFiSaZQ == true){PhKXFiSaZQ = false;}
      if(mXJKGVtJsx == true){mXJKGVtJsx = false;}
      if(CQdbaFepsn == true){CQdbaFepsn = false;}
      if(pJXGoEDiek == true){pJXGoEDiek = false;}
      if(idLXuOehMY == true){idLXuOehMY = false;}
      if(nFJgizDhwA == true){nFJgizDhwA = false;}
      if(DbhkacADUB == true){DbhkacADUB = false;}
      if(SLeINXFFgL == true){SLeINXFFgL = false;}
      if(axdTAjzqWp == true){axdTAjzqWp = false;}
      if(AUlegHwZxS == true){AUlegHwZxS = false;}
      if(OaNLGbaBSK == true){OaNLGbaBSK = false;}
      if(txBkZGxNkp == true){txBkZGxNkp = false;}
      if(dJgeAxZzaG == true){dJgeAxZzaG = false;}
      if(bfIOxzjRNX == true){bfIOxzjRNX = false;}
      if(JyXMwCTAEa == true){JyXMwCTAEa = false;}
      if(JinGnEthKI == true){JinGnEthKI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKVJRHIEHW
{ 
  void yCaYzuOILP()
  { 
      bool DhaQnazBVd = false;
      bool ZJpRlRlFQh = false;
      bool gDANlFrqDz = false;
      bool nEGnpjhjdi = false;
      bool SPIEJrgmOy = false;
      bool WQlDOzhMdi = false;
      bool iIyVoVDBaC = false;
      bool iCahORtuEt = false;
      bool XEbEbXRCYp = false;
      bool BUFuzKQmPm = false;
      bool neLMOUoEow = false;
      bool FmIjKdftsR = false;
      bool EBckANxfhD = false;
      bool BHeQFsrPoH = false;
      bool hNMckNMVjU = false;
      bool eWtyimCaLA = false;
      bool WJVkuxHqdQ = false;
      bool lQEkipnzAl = false;
      bool BbuMYeMghS = false;
      bool qQEnkYrbhm = false;
      string ETgZbsYcki;
      string jmksXxKhla;
      string eDfMZxSEmc;
      string lePHhQqndO;
      string GeljxpKQys;
      string ewdcJBnUze;
      string ZUpHxFXcLH;
      string FWDWTzQwOj;
      string lBGsypAlxf;
      string cWnynlodlr;
      string ShFpmIrGIK;
      string kqFPsXNxJH;
      string EkeeeihFih;
      string KlJWREwQFp;
      string xtdmukQYFP;
      string XqUengCZLE;
      string ZmXaAyhiyn;
      string bxrSJKHrjs;
      string RIASJSQdij;
      string CWFAPJVClw;
      if(ETgZbsYcki == ShFpmIrGIK){DhaQnazBVd = true;}
      else if(ShFpmIrGIK == ETgZbsYcki){neLMOUoEow = true;}
      if(jmksXxKhla == kqFPsXNxJH){ZJpRlRlFQh = true;}
      else if(kqFPsXNxJH == jmksXxKhla){FmIjKdftsR = true;}
      if(eDfMZxSEmc == EkeeeihFih){gDANlFrqDz = true;}
      else if(EkeeeihFih == eDfMZxSEmc){EBckANxfhD = true;}
      if(lePHhQqndO == KlJWREwQFp){nEGnpjhjdi = true;}
      else if(KlJWREwQFp == lePHhQqndO){BHeQFsrPoH = true;}
      if(GeljxpKQys == xtdmukQYFP){SPIEJrgmOy = true;}
      else if(xtdmukQYFP == GeljxpKQys){hNMckNMVjU = true;}
      if(ewdcJBnUze == XqUengCZLE){WQlDOzhMdi = true;}
      else if(XqUengCZLE == ewdcJBnUze){eWtyimCaLA = true;}
      if(ZUpHxFXcLH == ZmXaAyhiyn){iIyVoVDBaC = true;}
      else if(ZmXaAyhiyn == ZUpHxFXcLH){WJVkuxHqdQ = true;}
      if(FWDWTzQwOj == bxrSJKHrjs){iCahORtuEt = true;}
      if(lBGsypAlxf == RIASJSQdij){XEbEbXRCYp = true;}
      if(cWnynlodlr == CWFAPJVClw){BUFuzKQmPm = true;}
      while(bxrSJKHrjs == FWDWTzQwOj){lQEkipnzAl = true;}
      while(RIASJSQdij == RIASJSQdij){BbuMYeMghS = true;}
      while(CWFAPJVClw == CWFAPJVClw){qQEnkYrbhm = true;}
      if(DhaQnazBVd == true){DhaQnazBVd = false;}
      if(ZJpRlRlFQh == true){ZJpRlRlFQh = false;}
      if(gDANlFrqDz == true){gDANlFrqDz = false;}
      if(nEGnpjhjdi == true){nEGnpjhjdi = false;}
      if(SPIEJrgmOy == true){SPIEJrgmOy = false;}
      if(WQlDOzhMdi == true){WQlDOzhMdi = false;}
      if(iIyVoVDBaC == true){iIyVoVDBaC = false;}
      if(iCahORtuEt == true){iCahORtuEt = false;}
      if(XEbEbXRCYp == true){XEbEbXRCYp = false;}
      if(BUFuzKQmPm == true){BUFuzKQmPm = false;}
      if(neLMOUoEow == true){neLMOUoEow = false;}
      if(FmIjKdftsR == true){FmIjKdftsR = false;}
      if(EBckANxfhD == true){EBckANxfhD = false;}
      if(BHeQFsrPoH == true){BHeQFsrPoH = false;}
      if(hNMckNMVjU == true){hNMckNMVjU = false;}
      if(eWtyimCaLA == true){eWtyimCaLA = false;}
      if(WJVkuxHqdQ == true){WJVkuxHqdQ = false;}
      if(lQEkipnzAl == true){lQEkipnzAl = false;}
      if(BbuMYeMghS == true){BbuMYeMghS = false;}
      if(qQEnkYrbhm == true){qQEnkYrbhm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZLEKYSLNK
{ 
  void tffqNDKlUY()
  { 
      bool ZoqsENZdFH = false;
      bool NSGNSEZZoW = false;
      bool eEaUxHzsLZ = false;
      bool ChKORbESrr = false;
      bool SxZmVbbTzk = false;
      bool kiaLYUNVww = false;
      bool NfRfFfHqwp = false;
      bool zHgxEhemzU = false;
      bool fftanSGzpw = false;
      bool OhWwdletho = false;
      bool TjXIkcCdGq = false;
      bool paWaQhlqql = false;
      bool YIBzbRkkSS = false;
      bool CjEJBuHkoK = false;
      bool QcrzGmLueu = false;
      bool znDwQKhYfT = false;
      bool rQKnnFVMYU = false;
      bool ZBCfVuPCro = false;
      bool GoGXTOgIsp = false;
      bool NiFUSzSDKA = false;
      string WZfNokmpnA;
      string dfwajfAOow;
      string RcaVylYWHO;
      string orRQUPGLkF;
      string fkxhwhfKbn;
      string gLyLZtzJPD;
      string MPiZKkOeFT;
      string ZndjQgerYP;
      string FNuShdtFpa;
      string QwwhsPCXWK;
      string TAFIOrgNus;
      string OGjAxyUPqg;
      string qIoeCcrwqA;
      string dHVOuFImDo;
      string wfKwLKLwjt;
      string ulfpSLKZFk;
      string AkWtOHkVEq;
      string pgLBjLxrTq;
      string RwLxFrbfui;
      string thhSoKJPhE;
      if(WZfNokmpnA == TAFIOrgNus){ZoqsENZdFH = true;}
      else if(TAFIOrgNus == WZfNokmpnA){TjXIkcCdGq = true;}
      if(dfwajfAOow == OGjAxyUPqg){NSGNSEZZoW = true;}
      else if(OGjAxyUPqg == dfwajfAOow){paWaQhlqql = true;}
      if(RcaVylYWHO == qIoeCcrwqA){eEaUxHzsLZ = true;}
      else if(qIoeCcrwqA == RcaVylYWHO){YIBzbRkkSS = true;}
      if(orRQUPGLkF == dHVOuFImDo){ChKORbESrr = true;}
      else if(dHVOuFImDo == orRQUPGLkF){CjEJBuHkoK = true;}
      if(fkxhwhfKbn == wfKwLKLwjt){SxZmVbbTzk = true;}
      else if(wfKwLKLwjt == fkxhwhfKbn){QcrzGmLueu = true;}
      if(gLyLZtzJPD == ulfpSLKZFk){kiaLYUNVww = true;}
      else if(ulfpSLKZFk == gLyLZtzJPD){znDwQKhYfT = true;}
      if(MPiZKkOeFT == AkWtOHkVEq){NfRfFfHqwp = true;}
      else if(AkWtOHkVEq == MPiZKkOeFT){rQKnnFVMYU = true;}
      if(ZndjQgerYP == pgLBjLxrTq){zHgxEhemzU = true;}
      if(FNuShdtFpa == RwLxFrbfui){fftanSGzpw = true;}
      if(QwwhsPCXWK == thhSoKJPhE){OhWwdletho = true;}
      while(pgLBjLxrTq == ZndjQgerYP){ZBCfVuPCro = true;}
      while(RwLxFrbfui == RwLxFrbfui){GoGXTOgIsp = true;}
      while(thhSoKJPhE == thhSoKJPhE){NiFUSzSDKA = true;}
      if(ZoqsENZdFH == true){ZoqsENZdFH = false;}
      if(NSGNSEZZoW == true){NSGNSEZZoW = false;}
      if(eEaUxHzsLZ == true){eEaUxHzsLZ = false;}
      if(ChKORbESrr == true){ChKORbESrr = false;}
      if(SxZmVbbTzk == true){SxZmVbbTzk = false;}
      if(kiaLYUNVww == true){kiaLYUNVww = false;}
      if(NfRfFfHqwp == true){NfRfFfHqwp = false;}
      if(zHgxEhemzU == true){zHgxEhemzU = false;}
      if(fftanSGzpw == true){fftanSGzpw = false;}
      if(OhWwdletho == true){OhWwdletho = false;}
      if(TjXIkcCdGq == true){TjXIkcCdGq = false;}
      if(paWaQhlqql == true){paWaQhlqql = false;}
      if(YIBzbRkkSS == true){YIBzbRkkSS = false;}
      if(CjEJBuHkoK == true){CjEJBuHkoK = false;}
      if(QcrzGmLueu == true){QcrzGmLueu = false;}
      if(znDwQKhYfT == true){znDwQKhYfT = false;}
      if(rQKnnFVMYU == true){rQKnnFVMYU = false;}
      if(ZBCfVuPCro == true){ZBCfVuPCro = false;}
      if(GoGXTOgIsp == true){GoGXTOgIsp = false;}
      if(NiFUSzSDKA == true){NiFUSzSDKA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZKDMDZVFJ
{ 
  void rBJaYJhHCK()
  { 
      bool McUjEGXiHo = false;
      bool XUSsFmKWjU = false;
      bool CxajchNrbC = false;
      bool kIQQLKqgGb = false;
      bool HKCxPhwlHE = false;
      bool hLwJHOBjGW = false;
      bool rfGFEOEBhu = false;
      bool udQINqtdUu = false;
      bool lbjWTYMGIw = false;
      bool JHZjiaDxsA = false;
      bool ctEMIDumwQ = false;
      bool UXOKjQwikf = false;
      bool CxrkknEfYl = false;
      bool mwjURqXWOQ = false;
      bool cYKrbkrOzR = false;
      bool eTMNxfBSaU = false;
      bool zOOJdXmtsr = false;
      bool sYUUCdmAIA = false;
      bool uofGGSjWWl = false;
      bool pEwtQOJAOD = false;
      string ZqoJbnybWX;
      string gOQfUjGSWP;
      string hYpmmSuyjS;
      string ffazznDlXA;
      string phQKumIJqE;
      string XCRaJAABWI;
      string rzrErAmQgf;
      string fTuVYzIfqz;
      string KlHetcOAoy;
      string nBPOIqpLSu;
      string zqbKXDHwBJ;
      string rUKWyGqMJP;
      string lmahreEfNh;
      string JwMwzSJxGp;
      string URyfGTqrPB;
      string zdCCIMQtRs;
      string zbiSAwHOXf;
      string xsFSuTnubX;
      string mLQLhetKmm;
      string COfNqsifeK;
      if(ZqoJbnybWX == zqbKXDHwBJ){McUjEGXiHo = true;}
      else if(zqbKXDHwBJ == ZqoJbnybWX){ctEMIDumwQ = true;}
      if(gOQfUjGSWP == rUKWyGqMJP){XUSsFmKWjU = true;}
      else if(rUKWyGqMJP == gOQfUjGSWP){UXOKjQwikf = true;}
      if(hYpmmSuyjS == lmahreEfNh){CxajchNrbC = true;}
      else if(lmahreEfNh == hYpmmSuyjS){CxrkknEfYl = true;}
      if(ffazznDlXA == JwMwzSJxGp){kIQQLKqgGb = true;}
      else if(JwMwzSJxGp == ffazznDlXA){mwjURqXWOQ = true;}
      if(phQKumIJqE == URyfGTqrPB){HKCxPhwlHE = true;}
      else if(URyfGTqrPB == phQKumIJqE){cYKrbkrOzR = true;}
      if(XCRaJAABWI == zdCCIMQtRs){hLwJHOBjGW = true;}
      else if(zdCCIMQtRs == XCRaJAABWI){eTMNxfBSaU = true;}
      if(rzrErAmQgf == zbiSAwHOXf){rfGFEOEBhu = true;}
      else if(zbiSAwHOXf == rzrErAmQgf){zOOJdXmtsr = true;}
      if(fTuVYzIfqz == xsFSuTnubX){udQINqtdUu = true;}
      if(KlHetcOAoy == mLQLhetKmm){lbjWTYMGIw = true;}
      if(nBPOIqpLSu == COfNqsifeK){JHZjiaDxsA = true;}
      while(xsFSuTnubX == fTuVYzIfqz){sYUUCdmAIA = true;}
      while(mLQLhetKmm == mLQLhetKmm){uofGGSjWWl = true;}
      while(COfNqsifeK == COfNqsifeK){pEwtQOJAOD = true;}
      if(McUjEGXiHo == true){McUjEGXiHo = false;}
      if(XUSsFmKWjU == true){XUSsFmKWjU = false;}
      if(CxajchNrbC == true){CxajchNrbC = false;}
      if(kIQQLKqgGb == true){kIQQLKqgGb = false;}
      if(HKCxPhwlHE == true){HKCxPhwlHE = false;}
      if(hLwJHOBjGW == true){hLwJHOBjGW = false;}
      if(rfGFEOEBhu == true){rfGFEOEBhu = false;}
      if(udQINqtdUu == true){udQINqtdUu = false;}
      if(lbjWTYMGIw == true){lbjWTYMGIw = false;}
      if(JHZjiaDxsA == true){JHZjiaDxsA = false;}
      if(ctEMIDumwQ == true){ctEMIDumwQ = false;}
      if(UXOKjQwikf == true){UXOKjQwikf = false;}
      if(CxrkknEfYl == true){CxrkknEfYl = false;}
      if(mwjURqXWOQ == true){mwjURqXWOQ = false;}
      if(cYKrbkrOzR == true){cYKrbkrOzR = false;}
      if(eTMNxfBSaU == true){eTMNxfBSaU = false;}
      if(zOOJdXmtsr == true){zOOJdXmtsr = false;}
      if(sYUUCdmAIA == true){sYUUCdmAIA = false;}
      if(uofGGSjWWl == true){uofGGSjWWl = false;}
      if(pEwtQOJAOD == true){pEwtQOJAOD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XEDFFNLJYP
{ 
  void jyUmFVRcCN()
  { 
      bool qpkxgGzMbi = false;
      bool xbCjWXbWls = false;
      bool atrfmjpwPf = false;
      bool cwyHKFWwQN = false;
      bool xfgAkAEmRQ = false;
      bool YtRfwxxFJw = false;
      bool QCxwFAcuYQ = false;
      bool AfGXwuNrul = false;
      bool fCdzGieRLN = false;
      bool IRlTxtikuk = false;
      bool XINBPsmsjA = false;
      bool jFJWQNYyoW = false;
      bool UKjLIislZB = false;
      bool LbxKOXociM = false;
      bool ukhKdCHODj = false;
      bool VkuYPMXCrf = false;
      bool AAThoHIzIr = false;
      bool YuOcajcZgF = false;
      bool adipfafYuB = false;
      bool zljCMuRzVW = false;
      string ynzIrTVjfs;
      string BJxxcrjfGB;
      string bTqnWgsyyz;
      string psnVCNTgRe;
      string RPUNRePzAG;
      string qqQgidxLlK;
      string aWkfCHUatO;
      string XDOajLzcVq;
      string RtxqIzbHmX;
      string PItGEteoLJ;
      string KnElincpwW;
      string eUotsfZtXD;
      string fMnWyPIHVo;
      string gKQMfcoLIT;
      string WkLPruSzNX;
      string UjQIcyAhmT;
      string fVUGpUDbOQ;
      string qNkDgtBXeC;
      string wIsxUwsIih;
      string cHXonBQEZW;
      if(ynzIrTVjfs == KnElincpwW){qpkxgGzMbi = true;}
      else if(KnElincpwW == ynzIrTVjfs){XINBPsmsjA = true;}
      if(BJxxcrjfGB == eUotsfZtXD){xbCjWXbWls = true;}
      else if(eUotsfZtXD == BJxxcrjfGB){jFJWQNYyoW = true;}
      if(bTqnWgsyyz == fMnWyPIHVo){atrfmjpwPf = true;}
      else if(fMnWyPIHVo == bTqnWgsyyz){UKjLIislZB = true;}
      if(psnVCNTgRe == gKQMfcoLIT){cwyHKFWwQN = true;}
      else if(gKQMfcoLIT == psnVCNTgRe){LbxKOXociM = true;}
      if(RPUNRePzAG == WkLPruSzNX){xfgAkAEmRQ = true;}
      else if(WkLPruSzNX == RPUNRePzAG){ukhKdCHODj = true;}
      if(qqQgidxLlK == UjQIcyAhmT){YtRfwxxFJw = true;}
      else if(UjQIcyAhmT == qqQgidxLlK){VkuYPMXCrf = true;}
      if(aWkfCHUatO == fVUGpUDbOQ){QCxwFAcuYQ = true;}
      else if(fVUGpUDbOQ == aWkfCHUatO){AAThoHIzIr = true;}
      if(XDOajLzcVq == qNkDgtBXeC){AfGXwuNrul = true;}
      if(RtxqIzbHmX == wIsxUwsIih){fCdzGieRLN = true;}
      if(PItGEteoLJ == cHXonBQEZW){IRlTxtikuk = true;}
      while(qNkDgtBXeC == XDOajLzcVq){YuOcajcZgF = true;}
      while(wIsxUwsIih == wIsxUwsIih){adipfafYuB = true;}
      while(cHXonBQEZW == cHXonBQEZW){zljCMuRzVW = true;}
      if(qpkxgGzMbi == true){qpkxgGzMbi = false;}
      if(xbCjWXbWls == true){xbCjWXbWls = false;}
      if(atrfmjpwPf == true){atrfmjpwPf = false;}
      if(cwyHKFWwQN == true){cwyHKFWwQN = false;}
      if(xfgAkAEmRQ == true){xfgAkAEmRQ = false;}
      if(YtRfwxxFJw == true){YtRfwxxFJw = false;}
      if(QCxwFAcuYQ == true){QCxwFAcuYQ = false;}
      if(AfGXwuNrul == true){AfGXwuNrul = false;}
      if(fCdzGieRLN == true){fCdzGieRLN = false;}
      if(IRlTxtikuk == true){IRlTxtikuk = false;}
      if(XINBPsmsjA == true){XINBPsmsjA = false;}
      if(jFJWQNYyoW == true){jFJWQNYyoW = false;}
      if(UKjLIislZB == true){UKjLIislZB = false;}
      if(LbxKOXociM == true){LbxKOXociM = false;}
      if(ukhKdCHODj == true){ukhKdCHODj = false;}
      if(VkuYPMXCrf == true){VkuYPMXCrf = false;}
      if(AAThoHIzIr == true){AAThoHIzIr = false;}
      if(YuOcajcZgF == true){YuOcajcZgF = false;}
      if(adipfafYuB == true){adipfafYuB = false;}
      if(zljCMuRzVW == true){zljCMuRzVW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGORNXOKBG
{ 
  void oZYfiyPQVi()
  { 
      bool EdoIiixVem = false;
      bool FTuxnDgpWz = false;
      bool LcnUCFpCXF = false;
      bool zoarRbWmkA = false;
      bool ZVldtXJapM = false;
      bool NpgmXapTGc = false;
      bool rtxYnPsCfM = false;
      bool gsFWZpqJae = false;
      bool wPLKqIImTq = false;
      bool kDfHIeXMpd = false;
      bool dGudfUkKNh = false;
      bool ifsbgbimge = false;
      bool HGinacNyNt = false;
      bool ReTwAoUheW = false;
      bool XxYkHEJEag = false;
      bool wkfKWWXGCC = false;
      bool GmxTPEMwaq = false;
      bool GAHJHJhxgV = false;
      bool TIWgxgzJZd = false;
      bool ROebPkAEVC = false;
      string kLdloxghrN;
      string KlxfoPArQp;
      string rzWHOoAmOE;
      string rZesbdxBWa;
      string BESXcKJoCD;
      string kuMdLkoVXz;
      string wtSnUkGEEK;
      string SzUpomgydD;
      string eLkLSxNAgp;
      string obdWdHleDr;
      string EFjqklZVoX;
      string EpqTTkIHUX;
      string XFWNVpVyMh;
      string BBulzZasZg;
      string WqLJlzjJCr;
      string yeJeUzhWUt;
      string PbJHVCtFUt;
      string JPgnAgsNbW;
      string GLuTjWqQRz;
      string rEYeQtgEmi;
      if(kLdloxghrN == EFjqklZVoX){EdoIiixVem = true;}
      else if(EFjqklZVoX == kLdloxghrN){dGudfUkKNh = true;}
      if(KlxfoPArQp == EpqTTkIHUX){FTuxnDgpWz = true;}
      else if(EpqTTkIHUX == KlxfoPArQp){ifsbgbimge = true;}
      if(rzWHOoAmOE == XFWNVpVyMh){LcnUCFpCXF = true;}
      else if(XFWNVpVyMh == rzWHOoAmOE){HGinacNyNt = true;}
      if(rZesbdxBWa == BBulzZasZg){zoarRbWmkA = true;}
      else if(BBulzZasZg == rZesbdxBWa){ReTwAoUheW = true;}
      if(BESXcKJoCD == WqLJlzjJCr){ZVldtXJapM = true;}
      else if(WqLJlzjJCr == BESXcKJoCD){XxYkHEJEag = true;}
      if(kuMdLkoVXz == yeJeUzhWUt){NpgmXapTGc = true;}
      else if(yeJeUzhWUt == kuMdLkoVXz){wkfKWWXGCC = true;}
      if(wtSnUkGEEK == PbJHVCtFUt){rtxYnPsCfM = true;}
      else if(PbJHVCtFUt == wtSnUkGEEK){GmxTPEMwaq = true;}
      if(SzUpomgydD == JPgnAgsNbW){gsFWZpqJae = true;}
      if(eLkLSxNAgp == GLuTjWqQRz){wPLKqIImTq = true;}
      if(obdWdHleDr == rEYeQtgEmi){kDfHIeXMpd = true;}
      while(JPgnAgsNbW == SzUpomgydD){GAHJHJhxgV = true;}
      while(GLuTjWqQRz == GLuTjWqQRz){TIWgxgzJZd = true;}
      while(rEYeQtgEmi == rEYeQtgEmi){ROebPkAEVC = true;}
      if(EdoIiixVem == true){EdoIiixVem = false;}
      if(FTuxnDgpWz == true){FTuxnDgpWz = false;}
      if(LcnUCFpCXF == true){LcnUCFpCXF = false;}
      if(zoarRbWmkA == true){zoarRbWmkA = false;}
      if(ZVldtXJapM == true){ZVldtXJapM = false;}
      if(NpgmXapTGc == true){NpgmXapTGc = false;}
      if(rtxYnPsCfM == true){rtxYnPsCfM = false;}
      if(gsFWZpqJae == true){gsFWZpqJae = false;}
      if(wPLKqIImTq == true){wPLKqIImTq = false;}
      if(kDfHIeXMpd == true){kDfHIeXMpd = false;}
      if(dGudfUkKNh == true){dGudfUkKNh = false;}
      if(ifsbgbimge == true){ifsbgbimge = false;}
      if(HGinacNyNt == true){HGinacNyNt = false;}
      if(ReTwAoUheW == true){ReTwAoUheW = false;}
      if(XxYkHEJEag == true){XxYkHEJEag = false;}
      if(wkfKWWXGCC == true){wkfKWWXGCC = false;}
      if(GmxTPEMwaq == true){GmxTPEMwaq = false;}
      if(GAHJHJhxgV == true){GAHJHJhxgV = false;}
      if(TIWgxgzJZd == true){TIWgxgzJZd = false;}
      if(ROebPkAEVC == true){ROebPkAEVC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYADRTYRUN
{ 
  void aanhXCzlVJ()
  { 
      bool DiHSmUPiqo = false;
      bool rTzwSmEonm = false;
      bool JKKjkxcohK = false;
      bool BsmueWiZTl = false;
      bool dWUhFdxgTs = false;
      bool mNDtUrXXgo = false;
      bool raAfnzgEQu = false;
      bool DeVBImoceG = false;
      bool AwUnWmorZl = false;
      bool yLrdtCVnsG = false;
      bool xrPXoIrCkh = false;
      bool DusaowGMJA = false;
      bool JneewrlqHF = false;
      bool QBiXJHfwyN = false;
      bool umGriDSRoy = false;
      bool wJdsxINkax = false;
      bool WBtfQBMUQg = false;
      bool PJNuFVgmws = false;
      bool YUBIJHWoaB = false;
      bool tuUBqtraag = false;
      string tPcWScppUG;
      string MJhpbYdKZO;
      string rzyLdrtktV;
      string jSRSISitwj;
      string raXHtwkbsl;
      string wEdzktRRra;
      string iEuzWtqPhI;
      string oiOpVRbpRg;
      string GRrIYenRgN;
      string BRBUAmeXkz;
      string EVtkwMpmdT;
      string SbAKTRMmaq;
      string FZhUHXhsph;
      string lDFRckWGLL;
      string oAnNtYRpBh;
      string arxstemZdY;
      string ewxugPVhhi;
      string uFbOCElTZh;
      string GqrHHtFLXy;
      string xxclgrDrge;
      if(tPcWScppUG == EVtkwMpmdT){DiHSmUPiqo = true;}
      else if(EVtkwMpmdT == tPcWScppUG){xrPXoIrCkh = true;}
      if(MJhpbYdKZO == SbAKTRMmaq){rTzwSmEonm = true;}
      else if(SbAKTRMmaq == MJhpbYdKZO){DusaowGMJA = true;}
      if(rzyLdrtktV == FZhUHXhsph){JKKjkxcohK = true;}
      else if(FZhUHXhsph == rzyLdrtktV){JneewrlqHF = true;}
      if(jSRSISitwj == lDFRckWGLL){BsmueWiZTl = true;}
      else if(lDFRckWGLL == jSRSISitwj){QBiXJHfwyN = true;}
      if(raXHtwkbsl == oAnNtYRpBh){dWUhFdxgTs = true;}
      else if(oAnNtYRpBh == raXHtwkbsl){umGriDSRoy = true;}
      if(wEdzktRRra == arxstemZdY){mNDtUrXXgo = true;}
      else if(arxstemZdY == wEdzktRRra){wJdsxINkax = true;}
      if(iEuzWtqPhI == ewxugPVhhi){raAfnzgEQu = true;}
      else if(ewxugPVhhi == iEuzWtqPhI){WBtfQBMUQg = true;}
      if(oiOpVRbpRg == uFbOCElTZh){DeVBImoceG = true;}
      if(GRrIYenRgN == GqrHHtFLXy){AwUnWmorZl = true;}
      if(BRBUAmeXkz == xxclgrDrge){yLrdtCVnsG = true;}
      while(uFbOCElTZh == oiOpVRbpRg){PJNuFVgmws = true;}
      while(GqrHHtFLXy == GqrHHtFLXy){YUBIJHWoaB = true;}
      while(xxclgrDrge == xxclgrDrge){tuUBqtraag = true;}
      if(DiHSmUPiqo == true){DiHSmUPiqo = false;}
      if(rTzwSmEonm == true){rTzwSmEonm = false;}
      if(JKKjkxcohK == true){JKKjkxcohK = false;}
      if(BsmueWiZTl == true){BsmueWiZTl = false;}
      if(dWUhFdxgTs == true){dWUhFdxgTs = false;}
      if(mNDtUrXXgo == true){mNDtUrXXgo = false;}
      if(raAfnzgEQu == true){raAfnzgEQu = false;}
      if(DeVBImoceG == true){DeVBImoceG = false;}
      if(AwUnWmorZl == true){AwUnWmorZl = false;}
      if(yLrdtCVnsG == true){yLrdtCVnsG = false;}
      if(xrPXoIrCkh == true){xrPXoIrCkh = false;}
      if(DusaowGMJA == true){DusaowGMJA = false;}
      if(JneewrlqHF == true){JneewrlqHF = false;}
      if(QBiXJHfwyN == true){QBiXJHfwyN = false;}
      if(umGriDSRoy == true){umGriDSRoy = false;}
      if(wJdsxINkax == true){wJdsxINkax = false;}
      if(WBtfQBMUQg == true){WBtfQBMUQg = false;}
      if(PJNuFVgmws == true){PJNuFVgmws = false;}
      if(YUBIJHWoaB == true){YUBIJHWoaB = false;}
      if(tuUBqtraag == true){tuUBqtraag = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXXMHUGXLL
{ 
  void IjImYPddig()
  { 
      bool WnHJdJUcAP = false;
      bool TkWygclUTu = false;
      bool ZJjbOnMayc = false;
      bool FbSrrcjjgY = false;
      bool gHaSSQtPKM = false;
      bool ARksrMDetp = false;
      bool wtdWKrRdGD = false;
      bool sCnuOSiRIy = false;
      bool swQlcmpYAe = false;
      bool ZEopbldEIa = false;
      bool zQIGSxdpeZ = false;
      bool dlVwxAdrtW = false;
      bool BrdadnNxTb = false;
      bool odIhzcmJSe = false;
      bool IAtaBmhssb = false;
      bool IkKkYGlhce = false;
      bool jgWCjzcnxT = false;
      bool MUYONByCZp = false;
      bool FUDrTDTWIr = false;
      bool pFfntbdqpB = false;
      string sVWQkIUFzT;
      string ZNVzWnugLC;
      string FQwuircGhL;
      string SOyzSMtHdW;
      string zTBCgFJDuS;
      string UBRWZbYags;
      string eNXmBKPVfK;
      string tmCnDlPtOd;
      string hYLOpQxaZp;
      string mTZjqkwNBW;
      string onXjYgycTm;
      string MeLDKGBIxj;
      string MnuoWZNSwR;
      string pBsrntAapI;
      string STHmdIHWZk;
      string jmQQJBshMy;
      string TfgBxLlTOQ;
      string GaSnQsgILO;
      string RqsLhCkbim;
      string BRNqommFoS;
      if(sVWQkIUFzT == onXjYgycTm){WnHJdJUcAP = true;}
      else if(onXjYgycTm == sVWQkIUFzT){zQIGSxdpeZ = true;}
      if(ZNVzWnugLC == MeLDKGBIxj){TkWygclUTu = true;}
      else if(MeLDKGBIxj == ZNVzWnugLC){dlVwxAdrtW = true;}
      if(FQwuircGhL == MnuoWZNSwR){ZJjbOnMayc = true;}
      else if(MnuoWZNSwR == FQwuircGhL){BrdadnNxTb = true;}
      if(SOyzSMtHdW == pBsrntAapI){FbSrrcjjgY = true;}
      else if(pBsrntAapI == SOyzSMtHdW){odIhzcmJSe = true;}
      if(zTBCgFJDuS == STHmdIHWZk){gHaSSQtPKM = true;}
      else if(STHmdIHWZk == zTBCgFJDuS){IAtaBmhssb = true;}
      if(UBRWZbYags == jmQQJBshMy){ARksrMDetp = true;}
      else if(jmQQJBshMy == UBRWZbYags){IkKkYGlhce = true;}
      if(eNXmBKPVfK == TfgBxLlTOQ){wtdWKrRdGD = true;}
      else if(TfgBxLlTOQ == eNXmBKPVfK){jgWCjzcnxT = true;}
      if(tmCnDlPtOd == GaSnQsgILO){sCnuOSiRIy = true;}
      if(hYLOpQxaZp == RqsLhCkbim){swQlcmpYAe = true;}
      if(mTZjqkwNBW == BRNqommFoS){ZEopbldEIa = true;}
      while(GaSnQsgILO == tmCnDlPtOd){MUYONByCZp = true;}
      while(RqsLhCkbim == RqsLhCkbim){FUDrTDTWIr = true;}
      while(BRNqommFoS == BRNqommFoS){pFfntbdqpB = true;}
      if(WnHJdJUcAP == true){WnHJdJUcAP = false;}
      if(TkWygclUTu == true){TkWygclUTu = false;}
      if(ZJjbOnMayc == true){ZJjbOnMayc = false;}
      if(FbSrrcjjgY == true){FbSrrcjjgY = false;}
      if(gHaSSQtPKM == true){gHaSSQtPKM = false;}
      if(ARksrMDetp == true){ARksrMDetp = false;}
      if(wtdWKrRdGD == true){wtdWKrRdGD = false;}
      if(sCnuOSiRIy == true){sCnuOSiRIy = false;}
      if(swQlcmpYAe == true){swQlcmpYAe = false;}
      if(ZEopbldEIa == true){ZEopbldEIa = false;}
      if(zQIGSxdpeZ == true){zQIGSxdpeZ = false;}
      if(dlVwxAdrtW == true){dlVwxAdrtW = false;}
      if(BrdadnNxTb == true){BrdadnNxTb = false;}
      if(odIhzcmJSe == true){odIhzcmJSe = false;}
      if(IAtaBmhssb == true){IAtaBmhssb = false;}
      if(IkKkYGlhce == true){IkKkYGlhce = false;}
      if(jgWCjzcnxT == true){jgWCjzcnxT = false;}
      if(MUYONByCZp == true){MUYONByCZp = false;}
      if(FUDrTDTWIr == true){FUDrTDTWIr = false;}
      if(pFfntbdqpB == true){pFfntbdqpB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCUXCKLJHD
{ 
  void QpkotuyOaQ()
  { 
      bool VwatePulIk = false;
      bool BjDQZXofpn = false;
      bool mINacmMQQn = false;
      bool FakAZGzrkA = false;
      bool RdowyWuRsq = false;
      bool TAxjNNiAQq = false;
      bool CeUTfZzCqS = false;
      bool YxtpVISQbG = false;
      bool ruXYTFdBlM = false;
      bool XzasymIUQY = false;
      bool XraZSWFGNF = false;
      bool tSXKzHHuAa = false;
      bool uxQduZVAqi = false;
      bool AyzDhATxGx = false;
      bool zXngSFaQtq = false;
      bool eMUpdZawes = false;
      bool AFPdEwSUbz = false;
      bool mJoCaXJjLo = false;
      bool zFGADncIYH = false;
      bool ZWSNwtIJbW = false;
      string bRqlnLJmZh;
      string hhgNKduXjP;
      string UuIxETNgkn;
      string OOtYUxnZlB;
      string hOzLFNmCyO;
      string xgKQBfJtgT;
      string ybClSSmHsM;
      string oUkihFuxrp;
      string gKhVqhEdWn;
      string ntrSCFLNrl;
      string aeIlYbubiw;
      string kLBpmmsfuk;
      string OJkEYucSfb;
      string shFGPBCwwO;
      string mbtaDbrBeP;
      string LeSGXQtEMd;
      string zcwGCCGuZk;
      string kwjfylPJBw;
      string DamPPNPyhz;
      string HyiSPJfnXB;
      if(bRqlnLJmZh == aeIlYbubiw){VwatePulIk = true;}
      else if(aeIlYbubiw == bRqlnLJmZh){XraZSWFGNF = true;}
      if(hhgNKduXjP == kLBpmmsfuk){BjDQZXofpn = true;}
      else if(kLBpmmsfuk == hhgNKduXjP){tSXKzHHuAa = true;}
      if(UuIxETNgkn == OJkEYucSfb){mINacmMQQn = true;}
      else if(OJkEYucSfb == UuIxETNgkn){uxQduZVAqi = true;}
      if(OOtYUxnZlB == shFGPBCwwO){FakAZGzrkA = true;}
      else if(shFGPBCwwO == OOtYUxnZlB){AyzDhATxGx = true;}
      if(hOzLFNmCyO == mbtaDbrBeP){RdowyWuRsq = true;}
      else if(mbtaDbrBeP == hOzLFNmCyO){zXngSFaQtq = true;}
      if(xgKQBfJtgT == LeSGXQtEMd){TAxjNNiAQq = true;}
      else if(LeSGXQtEMd == xgKQBfJtgT){eMUpdZawes = true;}
      if(ybClSSmHsM == zcwGCCGuZk){CeUTfZzCqS = true;}
      else if(zcwGCCGuZk == ybClSSmHsM){AFPdEwSUbz = true;}
      if(oUkihFuxrp == kwjfylPJBw){YxtpVISQbG = true;}
      if(gKhVqhEdWn == DamPPNPyhz){ruXYTFdBlM = true;}
      if(ntrSCFLNrl == HyiSPJfnXB){XzasymIUQY = true;}
      while(kwjfylPJBw == oUkihFuxrp){mJoCaXJjLo = true;}
      while(DamPPNPyhz == DamPPNPyhz){zFGADncIYH = true;}
      while(HyiSPJfnXB == HyiSPJfnXB){ZWSNwtIJbW = true;}
      if(VwatePulIk == true){VwatePulIk = false;}
      if(BjDQZXofpn == true){BjDQZXofpn = false;}
      if(mINacmMQQn == true){mINacmMQQn = false;}
      if(FakAZGzrkA == true){FakAZGzrkA = false;}
      if(RdowyWuRsq == true){RdowyWuRsq = false;}
      if(TAxjNNiAQq == true){TAxjNNiAQq = false;}
      if(CeUTfZzCqS == true){CeUTfZzCqS = false;}
      if(YxtpVISQbG == true){YxtpVISQbG = false;}
      if(ruXYTFdBlM == true){ruXYTFdBlM = false;}
      if(XzasymIUQY == true){XzasymIUQY = false;}
      if(XraZSWFGNF == true){XraZSWFGNF = false;}
      if(tSXKzHHuAa == true){tSXKzHHuAa = false;}
      if(uxQduZVAqi == true){uxQduZVAqi = false;}
      if(AyzDhATxGx == true){AyzDhATxGx = false;}
      if(zXngSFaQtq == true){zXngSFaQtq = false;}
      if(eMUpdZawes == true){eMUpdZawes = false;}
      if(AFPdEwSUbz == true){AFPdEwSUbz = false;}
      if(mJoCaXJjLo == true){mJoCaXJjLo = false;}
      if(zFGADncIYH == true){zFGADncIYH = false;}
      if(ZWSNwtIJbW == true){ZWSNwtIJbW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHKWNXQVZT
{ 
  void yjEhXFeNrq()
  { 
      bool DjISuEsSMu = false;
      bool kzQoUSkMNb = false;
      bool XMzOzqXmIZ = false;
      bool hDEmmzztWu = false;
      bool VEtOUDRzxJ = false;
      bool acdjVqjsTE = false;
      bool gGKmNgucCU = false;
      bool SqpRGSRktw = false;
      bool YYoyyEZURu = false;
      bool PGaSOOtHAm = false;
      bool IowbpjmMcC = false;
      bool ZyzWeHQLoJ = false;
      bool GaKGFMQXCq = false;
      bool XJkGnjbMIN = false;
      bool RNqOVQGDmG = false;
      bool yiSqghepWd = false;
      bool SPJkePNriu = false;
      bool fDDaqsiukn = false;
      bool FNjusnqsZF = false;
      bool ElpduCEGjF = false;
      string IcMJoybhCu;
      string FZoitWbnuU;
      string DQwikRubzx;
      string CYmJCfLHNe;
      string ALxqsTPyKs;
      string gHjAyqfdXW;
      string DAiEsgmefO;
      string LUZQTqTFpR;
      string CxRFQtnlKL;
      string zhipbAcryL;
      string fjRwhMhTgG;
      string WanFUFicny;
      string rAUUOdkinS;
      string ObGdkReVWD;
      string LUFEnXscVV;
      string RzDzTfPxgE;
      string azeNruTJUC;
      string ZMFklXuQfq;
      string jINSAPXHKF;
      string ChoSbMoqLs;
      if(IcMJoybhCu == fjRwhMhTgG){DjISuEsSMu = true;}
      else if(fjRwhMhTgG == IcMJoybhCu){IowbpjmMcC = true;}
      if(FZoitWbnuU == WanFUFicny){kzQoUSkMNb = true;}
      else if(WanFUFicny == FZoitWbnuU){ZyzWeHQLoJ = true;}
      if(DQwikRubzx == rAUUOdkinS){XMzOzqXmIZ = true;}
      else if(rAUUOdkinS == DQwikRubzx){GaKGFMQXCq = true;}
      if(CYmJCfLHNe == ObGdkReVWD){hDEmmzztWu = true;}
      else if(ObGdkReVWD == CYmJCfLHNe){XJkGnjbMIN = true;}
      if(ALxqsTPyKs == LUFEnXscVV){VEtOUDRzxJ = true;}
      else if(LUFEnXscVV == ALxqsTPyKs){RNqOVQGDmG = true;}
      if(gHjAyqfdXW == RzDzTfPxgE){acdjVqjsTE = true;}
      else if(RzDzTfPxgE == gHjAyqfdXW){yiSqghepWd = true;}
      if(DAiEsgmefO == azeNruTJUC){gGKmNgucCU = true;}
      else if(azeNruTJUC == DAiEsgmefO){SPJkePNriu = true;}
      if(LUZQTqTFpR == ZMFklXuQfq){SqpRGSRktw = true;}
      if(CxRFQtnlKL == jINSAPXHKF){YYoyyEZURu = true;}
      if(zhipbAcryL == ChoSbMoqLs){PGaSOOtHAm = true;}
      while(ZMFklXuQfq == LUZQTqTFpR){fDDaqsiukn = true;}
      while(jINSAPXHKF == jINSAPXHKF){FNjusnqsZF = true;}
      while(ChoSbMoqLs == ChoSbMoqLs){ElpduCEGjF = true;}
      if(DjISuEsSMu == true){DjISuEsSMu = false;}
      if(kzQoUSkMNb == true){kzQoUSkMNb = false;}
      if(XMzOzqXmIZ == true){XMzOzqXmIZ = false;}
      if(hDEmmzztWu == true){hDEmmzztWu = false;}
      if(VEtOUDRzxJ == true){VEtOUDRzxJ = false;}
      if(acdjVqjsTE == true){acdjVqjsTE = false;}
      if(gGKmNgucCU == true){gGKmNgucCU = false;}
      if(SqpRGSRktw == true){SqpRGSRktw = false;}
      if(YYoyyEZURu == true){YYoyyEZURu = false;}
      if(PGaSOOtHAm == true){PGaSOOtHAm = false;}
      if(IowbpjmMcC == true){IowbpjmMcC = false;}
      if(ZyzWeHQLoJ == true){ZyzWeHQLoJ = false;}
      if(GaKGFMQXCq == true){GaKGFMQXCq = false;}
      if(XJkGnjbMIN == true){XJkGnjbMIN = false;}
      if(RNqOVQGDmG == true){RNqOVQGDmG = false;}
      if(yiSqghepWd == true){yiSqghepWd = false;}
      if(SPJkePNriu == true){SPJkePNriu = false;}
      if(fDDaqsiukn == true){fDDaqsiukn = false;}
      if(FNjusnqsZF == true){FNjusnqsZF = false;}
      if(ElpduCEGjF == true){ElpduCEGjF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYMASLKQLT
{ 
  void jxVBytHmOJ()
  { 
      bool UdzQybYpul = false;
      bool pdWdkBFiJf = false;
      bool GjVqAcudii = false;
      bool THqlPOsxya = false;
      bool wsbRuQnzzc = false;
      bool EIpgojIIQU = false;
      bool fuGMSilkNV = false;
      bool IHjijNIEwj = false;
      bool nweFeLRJxe = false;
      bool GkgctAlOyL = false;
      bool dDkcUwXHxa = false;
      bool bDLfgjPAhH = false;
      bool RcniOXaGoi = false;
      bool asFjGjKCkh = false;
      bool mJMVDCYAwJ = false;
      bool kkgqtAPCNx = false;
      bool URSNzhybZw = false;
      bool ZNPzTHPRfM = false;
      bool yaJeyoMNoF = false;
      bool UInnMUqzVU = false;
      string OMmyltkCBV;
      string FSHHtKYyUV;
      string BFYgchyCnU;
      string cjRKXkjLnp;
      string zdYDBWAHjA;
      string dEumiJnGUE;
      string whOfsVBwiJ;
      string aMJeVXfUfG;
      string gpRmqXneaO;
      string wdqisROsJe;
      string VEYaZQtQQK;
      string cTZNXGPanV;
      string hVUTMwVakE;
      string ImLAkcQqNZ;
      string cWNPlcDcLm;
      string BmEnxziFNd;
      string uTfMCoHZct;
      string oYNOrKIFhj;
      string ssOxCViXDk;
      string tLcjeJqANw;
      if(OMmyltkCBV == VEYaZQtQQK){UdzQybYpul = true;}
      else if(VEYaZQtQQK == OMmyltkCBV){dDkcUwXHxa = true;}
      if(FSHHtKYyUV == cTZNXGPanV){pdWdkBFiJf = true;}
      else if(cTZNXGPanV == FSHHtKYyUV){bDLfgjPAhH = true;}
      if(BFYgchyCnU == hVUTMwVakE){GjVqAcudii = true;}
      else if(hVUTMwVakE == BFYgchyCnU){RcniOXaGoi = true;}
      if(cjRKXkjLnp == ImLAkcQqNZ){THqlPOsxya = true;}
      else if(ImLAkcQqNZ == cjRKXkjLnp){asFjGjKCkh = true;}
      if(zdYDBWAHjA == cWNPlcDcLm){wsbRuQnzzc = true;}
      else if(cWNPlcDcLm == zdYDBWAHjA){mJMVDCYAwJ = true;}
      if(dEumiJnGUE == BmEnxziFNd){EIpgojIIQU = true;}
      else if(BmEnxziFNd == dEumiJnGUE){kkgqtAPCNx = true;}
      if(whOfsVBwiJ == uTfMCoHZct){fuGMSilkNV = true;}
      else if(uTfMCoHZct == whOfsVBwiJ){URSNzhybZw = true;}
      if(aMJeVXfUfG == oYNOrKIFhj){IHjijNIEwj = true;}
      if(gpRmqXneaO == ssOxCViXDk){nweFeLRJxe = true;}
      if(wdqisROsJe == tLcjeJqANw){GkgctAlOyL = true;}
      while(oYNOrKIFhj == aMJeVXfUfG){ZNPzTHPRfM = true;}
      while(ssOxCViXDk == ssOxCViXDk){yaJeyoMNoF = true;}
      while(tLcjeJqANw == tLcjeJqANw){UInnMUqzVU = true;}
      if(UdzQybYpul == true){UdzQybYpul = false;}
      if(pdWdkBFiJf == true){pdWdkBFiJf = false;}
      if(GjVqAcudii == true){GjVqAcudii = false;}
      if(THqlPOsxya == true){THqlPOsxya = false;}
      if(wsbRuQnzzc == true){wsbRuQnzzc = false;}
      if(EIpgojIIQU == true){EIpgojIIQU = false;}
      if(fuGMSilkNV == true){fuGMSilkNV = false;}
      if(IHjijNIEwj == true){IHjijNIEwj = false;}
      if(nweFeLRJxe == true){nweFeLRJxe = false;}
      if(GkgctAlOyL == true){GkgctAlOyL = false;}
      if(dDkcUwXHxa == true){dDkcUwXHxa = false;}
      if(bDLfgjPAhH == true){bDLfgjPAhH = false;}
      if(RcniOXaGoi == true){RcniOXaGoi = false;}
      if(asFjGjKCkh == true){asFjGjKCkh = false;}
      if(mJMVDCYAwJ == true){mJMVDCYAwJ = false;}
      if(kkgqtAPCNx == true){kkgqtAPCNx = false;}
      if(URSNzhybZw == true){URSNzhybZw = false;}
      if(ZNPzTHPRfM == true){ZNPzTHPRfM = false;}
      if(yaJeyoMNoF == true){yaJeyoMNoF = false;}
      if(UInnMUqzVU == true){UInnMUqzVU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNGBFFXHZP
{ 
  void cTWDhjzJUt()
  { 
      bool QkLlxZEDMD = false;
      bool uedVXpMOZI = false;
      bool CUhxIZPqka = false;
      bool buLrOMoXdO = false;
      bool PxeYEeRszb = false;
      bool SDRTewCOdX = false;
      bool KNRkaASlGK = false;
      bool AokLsFpJsc = false;
      bool HVqJHYcrMS = false;
      bool JatFEBesxD = false;
      bool LelnadSGZY = false;
      bool FsVAPnWIdC = false;
      bool XZYnAYteGr = false;
      bool awLoRbiDhc = false;
      bool FWRmMQFtpP = false;
      bool eVPuekFymB = false;
      bool jnzhyIgfhm = false;
      bool ESaAwAIlaj = false;
      bool TzopNEgQJf = false;
      bool VkPgsRWjnD = false;
      string IciwPZXVjj;
      string HkTqVUeAIW;
      string FVQXDanyDK;
      string lLXBiLrgnZ;
      string artcwphXVs;
      string zxSGdlLLrn;
      string kYRYyuMSIJ;
      string bxMiwNbnaM;
      string sPcKLnrRWw;
      string AgnznBZUdB;
      string dPPLQBkjJQ;
      string KWkfuUwHNK;
      string CtuLJtJNtt;
      string mHKZidzRsK;
      string DIHGkcwIDS;
      string FSGTyiTEBV;
      string qWpPcDMKxR;
      string VeNDHtmoZf;
      string yBJaoUAqbA;
      string JuPWSfRrch;
      if(IciwPZXVjj == dPPLQBkjJQ){QkLlxZEDMD = true;}
      else if(dPPLQBkjJQ == IciwPZXVjj){LelnadSGZY = true;}
      if(HkTqVUeAIW == KWkfuUwHNK){uedVXpMOZI = true;}
      else if(KWkfuUwHNK == HkTqVUeAIW){FsVAPnWIdC = true;}
      if(FVQXDanyDK == CtuLJtJNtt){CUhxIZPqka = true;}
      else if(CtuLJtJNtt == FVQXDanyDK){XZYnAYteGr = true;}
      if(lLXBiLrgnZ == mHKZidzRsK){buLrOMoXdO = true;}
      else if(mHKZidzRsK == lLXBiLrgnZ){awLoRbiDhc = true;}
      if(artcwphXVs == DIHGkcwIDS){PxeYEeRszb = true;}
      else if(DIHGkcwIDS == artcwphXVs){FWRmMQFtpP = true;}
      if(zxSGdlLLrn == FSGTyiTEBV){SDRTewCOdX = true;}
      else if(FSGTyiTEBV == zxSGdlLLrn){eVPuekFymB = true;}
      if(kYRYyuMSIJ == qWpPcDMKxR){KNRkaASlGK = true;}
      else if(qWpPcDMKxR == kYRYyuMSIJ){jnzhyIgfhm = true;}
      if(bxMiwNbnaM == VeNDHtmoZf){AokLsFpJsc = true;}
      if(sPcKLnrRWw == yBJaoUAqbA){HVqJHYcrMS = true;}
      if(AgnznBZUdB == JuPWSfRrch){JatFEBesxD = true;}
      while(VeNDHtmoZf == bxMiwNbnaM){ESaAwAIlaj = true;}
      while(yBJaoUAqbA == yBJaoUAqbA){TzopNEgQJf = true;}
      while(JuPWSfRrch == JuPWSfRrch){VkPgsRWjnD = true;}
      if(QkLlxZEDMD == true){QkLlxZEDMD = false;}
      if(uedVXpMOZI == true){uedVXpMOZI = false;}
      if(CUhxIZPqka == true){CUhxIZPqka = false;}
      if(buLrOMoXdO == true){buLrOMoXdO = false;}
      if(PxeYEeRszb == true){PxeYEeRszb = false;}
      if(SDRTewCOdX == true){SDRTewCOdX = false;}
      if(KNRkaASlGK == true){KNRkaASlGK = false;}
      if(AokLsFpJsc == true){AokLsFpJsc = false;}
      if(HVqJHYcrMS == true){HVqJHYcrMS = false;}
      if(JatFEBesxD == true){JatFEBesxD = false;}
      if(LelnadSGZY == true){LelnadSGZY = false;}
      if(FsVAPnWIdC == true){FsVAPnWIdC = false;}
      if(XZYnAYteGr == true){XZYnAYteGr = false;}
      if(awLoRbiDhc == true){awLoRbiDhc = false;}
      if(FWRmMQFtpP == true){FWRmMQFtpP = false;}
      if(eVPuekFymB == true){eVPuekFymB = false;}
      if(jnzhyIgfhm == true){jnzhyIgfhm = false;}
      if(ESaAwAIlaj == true){ESaAwAIlaj = false;}
      if(TzopNEgQJf == true){TzopNEgQJf = false;}
      if(VkPgsRWjnD == true){VkPgsRWjnD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBPCGGDISE
{ 
  void ErdmyKktyH()
  { 
      bool snZgiQgAFA = false;
      bool QGxOEOiWgn = false;
      bool KwuFZChXoj = false;
      bool IQoCDkyCbP = false;
      bool TFyVmWIpeM = false;
      bool bTkoXxrTHf = false;
      bool hIKUrzRtKS = false;
      bool QgtQUFxYRC = false;
      bool trsbIneAdG = false;
      bool sdtwhLtcdm = false;
      bool FNeMwtYUUS = false;
      bool zSCFlpPiME = false;
      bool TQQEZmlyiI = false;
      bool KUuewgMfeN = false;
      bool OKfLHZaoJq = false;
      bool wLQYSoxamJ = false;
      bool IZlLHeXXIE = false;
      bool diDzoJkEwz = false;
      bool LxnqMzDVLH = false;
      bool jksVFoYTDb = false;
      string CuyElNnIhT;
      string hKRSfNbhrV;
      string MwHKZMFPLy;
      string YtSgsnjZSy;
      string eJeYMHwuum;
      string sEgoiFnneY;
      string IXwiumrjZr;
      string cBOtqDRhxS;
      string QKTYFTNdyn;
      string AwuspGMucZ;
      string OLUDKromxe;
      string mFpMIxDWda;
      string ZOllqfFVEj;
      string pWFXDEoQON;
      string eZfSAtGhkr;
      string DoQBAzZiLd;
      string lTiNoQASID;
      string ImIQwziSlx;
      string ZXjLgAFDWD;
      string dFEjaLqRci;
      if(CuyElNnIhT == OLUDKromxe){snZgiQgAFA = true;}
      else if(OLUDKromxe == CuyElNnIhT){FNeMwtYUUS = true;}
      if(hKRSfNbhrV == mFpMIxDWda){QGxOEOiWgn = true;}
      else if(mFpMIxDWda == hKRSfNbhrV){zSCFlpPiME = true;}
      if(MwHKZMFPLy == ZOllqfFVEj){KwuFZChXoj = true;}
      else if(ZOllqfFVEj == MwHKZMFPLy){TQQEZmlyiI = true;}
      if(YtSgsnjZSy == pWFXDEoQON){IQoCDkyCbP = true;}
      else if(pWFXDEoQON == YtSgsnjZSy){KUuewgMfeN = true;}
      if(eJeYMHwuum == eZfSAtGhkr){TFyVmWIpeM = true;}
      else if(eZfSAtGhkr == eJeYMHwuum){OKfLHZaoJq = true;}
      if(sEgoiFnneY == DoQBAzZiLd){bTkoXxrTHf = true;}
      else if(DoQBAzZiLd == sEgoiFnneY){wLQYSoxamJ = true;}
      if(IXwiumrjZr == lTiNoQASID){hIKUrzRtKS = true;}
      else if(lTiNoQASID == IXwiumrjZr){IZlLHeXXIE = true;}
      if(cBOtqDRhxS == ImIQwziSlx){QgtQUFxYRC = true;}
      if(QKTYFTNdyn == ZXjLgAFDWD){trsbIneAdG = true;}
      if(AwuspGMucZ == dFEjaLqRci){sdtwhLtcdm = true;}
      while(ImIQwziSlx == cBOtqDRhxS){diDzoJkEwz = true;}
      while(ZXjLgAFDWD == ZXjLgAFDWD){LxnqMzDVLH = true;}
      while(dFEjaLqRci == dFEjaLqRci){jksVFoYTDb = true;}
      if(snZgiQgAFA == true){snZgiQgAFA = false;}
      if(QGxOEOiWgn == true){QGxOEOiWgn = false;}
      if(KwuFZChXoj == true){KwuFZChXoj = false;}
      if(IQoCDkyCbP == true){IQoCDkyCbP = false;}
      if(TFyVmWIpeM == true){TFyVmWIpeM = false;}
      if(bTkoXxrTHf == true){bTkoXxrTHf = false;}
      if(hIKUrzRtKS == true){hIKUrzRtKS = false;}
      if(QgtQUFxYRC == true){QgtQUFxYRC = false;}
      if(trsbIneAdG == true){trsbIneAdG = false;}
      if(sdtwhLtcdm == true){sdtwhLtcdm = false;}
      if(FNeMwtYUUS == true){FNeMwtYUUS = false;}
      if(zSCFlpPiME == true){zSCFlpPiME = false;}
      if(TQQEZmlyiI == true){TQQEZmlyiI = false;}
      if(KUuewgMfeN == true){KUuewgMfeN = false;}
      if(OKfLHZaoJq == true){OKfLHZaoJq = false;}
      if(wLQYSoxamJ == true){wLQYSoxamJ = false;}
      if(IZlLHeXXIE == true){IZlLHeXXIE = false;}
      if(diDzoJkEwz == true){diDzoJkEwz = false;}
      if(LxnqMzDVLH == true){LxnqMzDVLH = false;}
      if(jksVFoYTDb == true){jksVFoYTDb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MTLDWVAJAJ
{ 
  void nlIkkoZAOL()
  { 
      bool JTulGrxlGa = false;
      bool NxFeCStqQF = false;
      bool kjsOowZkeg = false;
      bool CjwlOjAyZL = false;
      bool CqzKXAlbzT = false;
      bool ldGamZZgxJ = false;
      bool RMGZXdASQR = false;
      bool RwRFCtjiqn = false;
      bool JykLtYcVzo = false;
      bool JTAPspjYls = false;
      bool ATLhCpMAXr = false;
      bool oqoJzTaufz = false;
      bool BeTaHxuBML = false;
      bool KKwxnpmDIE = false;
      bool McxGzSdqPZ = false;
      bool PnsmrUzjZE = false;
      bool tKmLhdtrUI = false;
      bool fXmbmXgMbn = false;
      bool SEkmwVRJFS = false;
      bool qDdEJBokYV = false;
      string LhydHmYIwL;
      string faXStuqwkj;
      string JIsgqnRytR;
      string jSihkFdrDO;
      string ptCWeNcuOa;
      string HhWrFCnQmT;
      string UZOdbNqpgn;
      string QzsVsPFWBd;
      string KWjSKBuqbi;
      string QNFitPeXuR;
      string VmNZJIoAyp;
      string wROIJypuTZ;
      string SANxXDsJbc;
      string jhajHWIJIB;
      string LtrlmzywYu;
      string ZjEUzVYQCG;
      string OeXUFOpeBl;
      string ogmRNYHbKX;
      string EwkgDAcGkl;
      string xrGBlgVXfX;
      if(LhydHmYIwL == VmNZJIoAyp){JTulGrxlGa = true;}
      else if(VmNZJIoAyp == LhydHmYIwL){ATLhCpMAXr = true;}
      if(faXStuqwkj == wROIJypuTZ){NxFeCStqQF = true;}
      else if(wROIJypuTZ == faXStuqwkj){oqoJzTaufz = true;}
      if(JIsgqnRytR == SANxXDsJbc){kjsOowZkeg = true;}
      else if(SANxXDsJbc == JIsgqnRytR){BeTaHxuBML = true;}
      if(jSihkFdrDO == jhajHWIJIB){CjwlOjAyZL = true;}
      else if(jhajHWIJIB == jSihkFdrDO){KKwxnpmDIE = true;}
      if(ptCWeNcuOa == LtrlmzywYu){CqzKXAlbzT = true;}
      else if(LtrlmzywYu == ptCWeNcuOa){McxGzSdqPZ = true;}
      if(HhWrFCnQmT == ZjEUzVYQCG){ldGamZZgxJ = true;}
      else if(ZjEUzVYQCG == HhWrFCnQmT){PnsmrUzjZE = true;}
      if(UZOdbNqpgn == OeXUFOpeBl){RMGZXdASQR = true;}
      else if(OeXUFOpeBl == UZOdbNqpgn){tKmLhdtrUI = true;}
      if(QzsVsPFWBd == ogmRNYHbKX){RwRFCtjiqn = true;}
      if(KWjSKBuqbi == EwkgDAcGkl){JykLtYcVzo = true;}
      if(QNFitPeXuR == xrGBlgVXfX){JTAPspjYls = true;}
      while(ogmRNYHbKX == QzsVsPFWBd){fXmbmXgMbn = true;}
      while(EwkgDAcGkl == EwkgDAcGkl){SEkmwVRJFS = true;}
      while(xrGBlgVXfX == xrGBlgVXfX){qDdEJBokYV = true;}
      if(JTulGrxlGa == true){JTulGrxlGa = false;}
      if(NxFeCStqQF == true){NxFeCStqQF = false;}
      if(kjsOowZkeg == true){kjsOowZkeg = false;}
      if(CjwlOjAyZL == true){CjwlOjAyZL = false;}
      if(CqzKXAlbzT == true){CqzKXAlbzT = false;}
      if(ldGamZZgxJ == true){ldGamZZgxJ = false;}
      if(RMGZXdASQR == true){RMGZXdASQR = false;}
      if(RwRFCtjiqn == true){RwRFCtjiqn = false;}
      if(JykLtYcVzo == true){JykLtYcVzo = false;}
      if(JTAPspjYls == true){JTAPspjYls = false;}
      if(ATLhCpMAXr == true){ATLhCpMAXr = false;}
      if(oqoJzTaufz == true){oqoJzTaufz = false;}
      if(BeTaHxuBML == true){BeTaHxuBML = false;}
      if(KKwxnpmDIE == true){KKwxnpmDIE = false;}
      if(McxGzSdqPZ == true){McxGzSdqPZ = false;}
      if(PnsmrUzjZE == true){PnsmrUzjZE = false;}
      if(tKmLhdtrUI == true){tKmLhdtrUI = false;}
      if(fXmbmXgMbn == true){fXmbmXgMbn = false;}
      if(SEkmwVRJFS == true){SEkmwVRJFS = false;}
      if(qDdEJBokYV == true){qDdEJBokYV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHDEEHFAGH
{ 
  void FLGzqpxsgT()
  { 
      bool sgjMztXJVZ = false;
      bool duQcQOFxfl = false;
      bool ZXYJdedhyG = false;
      bool CAJPtjKPWC = false;
      bool lqyZFHkeVZ = false;
      bool dtiSNUIaiU = false;
      bool QoKOWckAif = false;
      bool EpZcziZzDV = false;
      bool szMXbIQqCY = false;
      bool bigClwfjCc = false;
      bool VjwpVnTFSe = false;
      bool uJXMaQcllO = false;
      bool LtyJEUIXqD = false;
      bool CowaAJDWCn = false;
      bool oKXXdRLTaV = false;
      bool TsymQblllA = false;
      bool fuOPbFMwMR = false;
      bool MFjyZAVZfl = false;
      bool JoxUiIqJKX = false;
      bool XRkBItwIuX = false;
      string hkxzBGASHa;
      string poskTBahic;
      string jfJMwVtgBn;
      string rydgklgCUu;
      string JzBFSPjlVa;
      string GSMbiBbkDf;
      string LTQSirLLAh;
      string UXMmTkeDsg;
      string kIKagYkBxj;
      string JwzojohhWa;
      string DXknGhGYIy;
      string WYqVtDIplJ;
      string GJNQXXYXDd;
      string CwgScMWWUy;
      string SMszMkFctf;
      string frwMTsJUPh;
      string JiUduZrXrg;
      string glUmqtPODm;
      string RucWxJATzi;
      string DBHlnjqPEm;
      if(hkxzBGASHa == DXknGhGYIy){sgjMztXJVZ = true;}
      else if(DXknGhGYIy == hkxzBGASHa){VjwpVnTFSe = true;}
      if(poskTBahic == WYqVtDIplJ){duQcQOFxfl = true;}
      else if(WYqVtDIplJ == poskTBahic){uJXMaQcllO = true;}
      if(jfJMwVtgBn == GJNQXXYXDd){ZXYJdedhyG = true;}
      else if(GJNQXXYXDd == jfJMwVtgBn){LtyJEUIXqD = true;}
      if(rydgklgCUu == CwgScMWWUy){CAJPtjKPWC = true;}
      else if(CwgScMWWUy == rydgklgCUu){CowaAJDWCn = true;}
      if(JzBFSPjlVa == SMszMkFctf){lqyZFHkeVZ = true;}
      else if(SMszMkFctf == JzBFSPjlVa){oKXXdRLTaV = true;}
      if(GSMbiBbkDf == frwMTsJUPh){dtiSNUIaiU = true;}
      else if(frwMTsJUPh == GSMbiBbkDf){TsymQblllA = true;}
      if(LTQSirLLAh == JiUduZrXrg){QoKOWckAif = true;}
      else if(JiUduZrXrg == LTQSirLLAh){fuOPbFMwMR = true;}
      if(UXMmTkeDsg == glUmqtPODm){EpZcziZzDV = true;}
      if(kIKagYkBxj == RucWxJATzi){szMXbIQqCY = true;}
      if(JwzojohhWa == DBHlnjqPEm){bigClwfjCc = true;}
      while(glUmqtPODm == UXMmTkeDsg){MFjyZAVZfl = true;}
      while(RucWxJATzi == RucWxJATzi){JoxUiIqJKX = true;}
      while(DBHlnjqPEm == DBHlnjqPEm){XRkBItwIuX = true;}
      if(sgjMztXJVZ == true){sgjMztXJVZ = false;}
      if(duQcQOFxfl == true){duQcQOFxfl = false;}
      if(ZXYJdedhyG == true){ZXYJdedhyG = false;}
      if(CAJPtjKPWC == true){CAJPtjKPWC = false;}
      if(lqyZFHkeVZ == true){lqyZFHkeVZ = false;}
      if(dtiSNUIaiU == true){dtiSNUIaiU = false;}
      if(QoKOWckAif == true){QoKOWckAif = false;}
      if(EpZcziZzDV == true){EpZcziZzDV = false;}
      if(szMXbIQqCY == true){szMXbIQqCY = false;}
      if(bigClwfjCc == true){bigClwfjCc = false;}
      if(VjwpVnTFSe == true){VjwpVnTFSe = false;}
      if(uJXMaQcllO == true){uJXMaQcllO = false;}
      if(LtyJEUIXqD == true){LtyJEUIXqD = false;}
      if(CowaAJDWCn == true){CowaAJDWCn = false;}
      if(oKXXdRLTaV == true){oKXXdRLTaV = false;}
      if(TsymQblllA == true){TsymQblllA = false;}
      if(fuOPbFMwMR == true){fuOPbFMwMR = false;}
      if(MFjyZAVZfl == true){MFjyZAVZfl = false;}
      if(JoxUiIqJKX == true){JoxUiIqJKX = false;}
      if(XRkBItwIuX == true){XRkBItwIuX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEEZPCLCTW
{ 
  void MBpzJrHXBV()
  { 
      bool BecVsWNsDL = false;
      bool ZuAPXMbBfx = false;
      bool dJofjfZSuC = false;
      bool kEWzCenEww = false;
      bool twkCNdOQNk = false;
      bool nLODJqoxlM = false;
      bool xuxBaUYBNs = false;
      bool YXEiDgXlSG = false;
      bool RJFKNYpToK = false;
      bool oqRjzzyjbr = false;
      bool EMCUMQHezb = false;
      bool SDdeunommC = false;
      bool eFLCDgFTiD = false;
      bool inKaBEGkyx = false;
      bool QKTMrlMmoL = false;
      bool JLwYMzAAQe = false;
      bool KmuusdrDcp = false;
      bool gEoplUlzJR = false;
      bool USeXtXrkNC = false;
      bool DFTTlcOXTN = false;
      string RUqixBndpm;
      string BIxiDYUPrz;
      string PjpdcEQIQz;
      string ZUYfkoWgaX;
      string QAzVsANfkZ;
      string exrgtgdMGs;
      string jeMpNfjQyN;
      string BnnUiOkTkb;
      string pkXpTbcqlD;
      string KJZhnknIIM;
      string QxhWYqIXxf;
      string wKbdCyHVVl;
      string DrdtDqNGfy;
      string ZbLXLsCARb;
      string SFsGHzhwfo;
      string dRmWJXTmTg;
      string dCqzFTyDSJ;
      string uGEsSyyXmD;
      string JRapTHooOm;
      string YOgkyQNtAn;
      if(RUqixBndpm == QxhWYqIXxf){BecVsWNsDL = true;}
      else if(QxhWYqIXxf == RUqixBndpm){EMCUMQHezb = true;}
      if(BIxiDYUPrz == wKbdCyHVVl){ZuAPXMbBfx = true;}
      else if(wKbdCyHVVl == BIxiDYUPrz){SDdeunommC = true;}
      if(PjpdcEQIQz == DrdtDqNGfy){dJofjfZSuC = true;}
      else if(DrdtDqNGfy == PjpdcEQIQz){eFLCDgFTiD = true;}
      if(ZUYfkoWgaX == ZbLXLsCARb){kEWzCenEww = true;}
      else if(ZbLXLsCARb == ZUYfkoWgaX){inKaBEGkyx = true;}
      if(QAzVsANfkZ == SFsGHzhwfo){twkCNdOQNk = true;}
      else if(SFsGHzhwfo == QAzVsANfkZ){QKTMrlMmoL = true;}
      if(exrgtgdMGs == dRmWJXTmTg){nLODJqoxlM = true;}
      else if(dRmWJXTmTg == exrgtgdMGs){JLwYMzAAQe = true;}
      if(jeMpNfjQyN == dCqzFTyDSJ){xuxBaUYBNs = true;}
      else if(dCqzFTyDSJ == jeMpNfjQyN){KmuusdrDcp = true;}
      if(BnnUiOkTkb == uGEsSyyXmD){YXEiDgXlSG = true;}
      if(pkXpTbcqlD == JRapTHooOm){RJFKNYpToK = true;}
      if(KJZhnknIIM == YOgkyQNtAn){oqRjzzyjbr = true;}
      while(uGEsSyyXmD == BnnUiOkTkb){gEoplUlzJR = true;}
      while(JRapTHooOm == JRapTHooOm){USeXtXrkNC = true;}
      while(YOgkyQNtAn == YOgkyQNtAn){DFTTlcOXTN = true;}
      if(BecVsWNsDL == true){BecVsWNsDL = false;}
      if(ZuAPXMbBfx == true){ZuAPXMbBfx = false;}
      if(dJofjfZSuC == true){dJofjfZSuC = false;}
      if(kEWzCenEww == true){kEWzCenEww = false;}
      if(twkCNdOQNk == true){twkCNdOQNk = false;}
      if(nLODJqoxlM == true){nLODJqoxlM = false;}
      if(xuxBaUYBNs == true){xuxBaUYBNs = false;}
      if(YXEiDgXlSG == true){YXEiDgXlSG = false;}
      if(RJFKNYpToK == true){RJFKNYpToK = false;}
      if(oqRjzzyjbr == true){oqRjzzyjbr = false;}
      if(EMCUMQHezb == true){EMCUMQHezb = false;}
      if(SDdeunommC == true){SDdeunommC = false;}
      if(eFLCDgFTiD == true){eFLCDgFTiD = false;}
      if(inKaBEGkyx == true){inKaBEGkyx = false;}
      if(QKTMrlMmoL == true){QKTMrlMmoL = false;}
      if(JLwYMzAAQe == true){JLwYMzAAQe = false;}
      if(KmuusdrDcp == true){KmuusdrDcp = false;}
      if(gEoplUlzJR == true){gEoplUlzJR = false;}
      if(USeXtXrkNC == true){USeXtXrkNC = false;}
      if(DFTTlcOXTN == true){DFTTlcOXTN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWUDIGHYOO
{ 
  void FNlKFAnVOC()
  { 
      bool pYWuWWuMHJ = false;
      bool JteOPJDwBO = false;
      bool AUtGgharLk = false;
      bool uapTBgHifW = false;
      bool YfKFrNEopl = false;
      bool sWsbwVdPNn = false;
      bool wDBWNiEKMh = false;
      bool BUQepTKoOT = false;
      bool dlBYqXhNXf = false;
      bool CqUqaUenqJ = false;
      bool JscHjYGNkb = false;
      bool KoBtKJBbep = false;
      bool ApmfeJzZEU = false;
      bool nVxEJkJsoS = false;
      bool RTbuUNoZgQ = false;
      bool TDJBITFwcZ = false;
      bool ZgJPmorxkY = false;
      bool AHmMXgNqKR = false;
      bool TYrmBkMwuo = false;
      bool eMQOrkJLHf = false;
      string hJwaeKpYsr;
      string ZHfZcwWhnF;
      string KFDAKjiNOT;
      string CeMAXfbnGL;
      string SdjrDlPDZd;
      string jZTedbGuPt;
      string abKZputeCw;
      string UibblgVKxY;
      string UfmjjcLhWw;
      string ZfXLjpTJCI;
      string qjBdJAxqrw;
      string FuyqZunZpM;
      string iLHGWnLPrw;
      string NMHngjdJaj;
      string eTpZpdhgkn;
      string BsSoYebuGU;
      string nhzuismJJp;
      string RdyGhPVgQr;
      string FedDtTsSPC;
      string IiDFuxTtqw;
      if(hJwaeKpYsr == qjBdJAxqrw){pYWuWWuMHJ = true;}
      else if(qjBdJAxqrw == hJwaeKpYsr){JscHjYGNkb = true;}
      if(ZHfZcwWhnF == FuyqZunZpM){JteOPJDwBO = true;}
      else if(FuyqZunZpM == ZHfZcwWhnF){KoBtKJBbep = true;}
      if(KFDAKjiNOT == iLHGWnLPrw){AUtGgharLk = true;}
      else if(iLHGWnLPrw == KFDAKjiNOT){ApmfeJzZEU = true;}
      if(CeMAXfbnGL == NMHngjdJaj){uapTBgHifW = true;}
      else if(NMHngjdJaj == CeMAXfbnGL){nVxEJkJsoS = true;}
      if(SdjrDlPDZd == eTpZpdhgkn){YfKFrNEopl = true;}
      else if(eTpZpdhgkn == SdjrDlPDZd){RTbuUNoZgQ = true;}
      if(jZTedbGuPt == BsSoYebuGU){sWsbwVdPNn = true;}
      else if(BsSoYebuGU == jZTedbGuPt){TDJBITFwcZ = true;}
      if(abKZputeCw == nhzuismJJp){wDBWNiEKMh = true;}
      else if(nhzuismJJp == abKZputeCw){ZgJPmorxkY = true;}
      if(UibblgVKxY == RdyGhPVgQr){BUQepTKoOT = true;}
      if(UfmjjcLhWw == FedDtTsSPC){dlBYqXhNXf = true;}
      if(ZfXLjpTJCI == IiDFuxTtqw){CqUqaUenqJ = true;}
      while(RdyGhPVgQr == UibblgVKxY){AHmMXgNqKR = true;}
      while(FedDtTsSPC == FedDtTsSPC){TYrmBkMwuo = true;}
      while(IiDFuxTtqw == IiDFuxTtqw){eMQOrkJLHf = true;}
      if(pYWuWWuMHJ == true){pYWuWWuMHJ = false;}
      if(JteOPJDwBO == true){JteOPJDwBO = false;}
      if(AUtGgharLk == true){AUtGgharLk = false;}
      if(uapTBgHifW == true){uapTBgHifW = false;}
      if(YfKFrNEopl == true){YfKFrNEopl = false;}
      if(sWsbwVdPNn == true){sWsbwVdPNn = false;}
      if(wDBWNiEKMh == true){wDBWNiEKMh = false;}
      if(BUQepTKoOT == true){BUQepTKoOT = false;}
      if(dlBYqXhNXf == true){dlBYqXhNXf = false;}
      if(CqUqaUenqJ == true){CqUqaUenqJ = false;}
      if(JscHjYGNkb == true){JscHjYGNkb = false;}
      if(KoBtKJBbep == true){KoBtKJBbep = false;}
      if(ApmfeJzZEU == true){ApmfeJzZEU = false;}
      if(nVxEJkJsoS == true){nVxEJkJsoS = false;}
      if(RTbuUNoZgQ == true){RTbuUNoZgQ = false;}
      if(TDJBITFwcZ == true){TDJBITFwcZ = false;}
      if(ZgJPmorxkY == true){ZgJPmorxkY = false;}
      if(AHmMXgNqKR == true){AHmMXgNqKR = false;}
      if(TYrmBkMwuo == true){TYrmBkMwuo = false;}
      if(eMQOrkJLHf == true){eMQOrkJLHf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSBKWNQXCM
{ 
  void EFEFhFsTJu()
  { 
      bool aAhBWLngjN = false;
      bool wbwyJRwWqF = false;
      bool oulAXKVtSN = false;
      bool DqDBYGJXaJ = false;
      bool artcgtMVnu = false;
      bool mzApseNhcM = false;
      bool osNVKEXuYC = false;
      bool IXuhexBISc = false;
      bool yAGWaDqNIt = false;
      bool rauOTgdYSc = false;
      bool WRxklPESKu = false;
      bool dFPzNomqtG = false;
      bool NKldJgbfOx = false;
      bool TbppGgDUjL = false;
      bool zXCMPmKuBd = false;
      bool tmdLOMeSbE = false;
      bool mXEMbBPZsf = false;
      bool lRGiGoHZOW = false;
      bool WgejDgydat = false;
      bool CksfYbTokO = false;
      string LOyhVMePuz;
      string XglbIBQmIU;
      string BJgGTjxEpE;
      string zEGmyUdMbQ;
      string lOHjXsrrlY;
      string RCCSEBhrNk;
      string PaYqzSazdm;
      string WDLqhlCwia;
      string qERQmwCniw;
      string llzpBKoQjE;
      string RsOzCOqKjR;
      string zlIlsKIHDC;
      string QmQgAkEVpX;
      string wkLeIypSOX;
      string FqDQxAdMwq;
      string CgMgmebgyQ;
      string KVUMUNZcdu;
      string TpsfxYizjA;
      string HrZyUPYdqd;
      string WITyNiVqui;
      if(LOyhVMePuz == RsOzCOqKjR){aAhBWLngjN = true;}
      else if(RsOzCOqKjR == LOyhVMePuz){WRxklPESKu = true;}
      if(XglbIBQmIU == zlIlsKIHDC){wbwyJRwWqF = true;}
      else if(zlIlsKIHDC == XglbIBQmIU){dFPzNomqtG = true;}
      if(BJgGTjxEpE == QmQgAkEVpX){oulAXKVtSN = true;}
      else if(QmQgAkEVpX == BJgGTjxEpE){NKldJgbfOx = true;}
      if(zEGmyUdMbQ == wkLeIypSOX){DqDBYGJXaJ = true;}
      else if(wkLeIypSOX == zEGmyUdMbQ){TbppGgDUjL = true;}
      if(lOHjXsrrlY == FqDQxAdMwq){artcgtMVnu = true;}
      else if(FqDQxAdMwq == lOHjXsrrlY){zXCMPmKuBd = true;}
      if(RCCSEBhrNk == CgMgmebgyQ){mzApseNhcM = true;}
      else if(CgMgmebgyQ == RCCSEBhrNk){tmdLOMeSbE = true;}
      if(PaYqzSazdm == KVUMUNZcdu){osNVKEXuYC = true;}
      else if(KVUMUNZcdu == PaYqzSazdm){mXEMbBPZsf = true;}
      if(WDLqhlCwia == TpsfxYizjA){IXuhexBISc = true;}
      if(qERQmwCniw == HrZyUPYdqd){yAGWaDqNIt = true;}
      if(llzpBKoQjE == WITyNiVqui){rauOTgdYSc = true;}
      while(TpsfxYizjA == WDLqhlCwia){lRGiGoHZOW = true;}
      while(HrZyUPYdqd == HrZyUPYdqd){WgejDgydat = true;}
      while(WITyNiVqui == WITyNiVqui){CksfYbTokO = true;}
      if(aAhBWLngjN == true){aAhBWLngjN = false;}
      if(wbwyJRwWqF == true){wbwyJRwWqF = false;}
      if(oulAXKVtSN == true){oulAXKVtSN = false;}
      if(DqDBYGJXaJ == true){DqDBYGJXaJ = false;}
      if(artcgtMVnu == true){artcgtMVnu = false;}
      if(mzApseNhcM == true){mzApseNhcM = false;}
      if(osNVKEXuYC == true){osNVKEXuYC = false;}
      if(IXuhexBISc == true){IXuhexBISc = false;}
      if(yAGWaDqNIt == true){yAGWaDqNIt = false;}
      if(rauOTgdYSc == true){rauOTgdYSc = false;}
      if(WRxklPESKu == true){WRxklPESKu = false;}
      if(dFPzNomqtG == true){dFPzNomqtG = false;}
      if(NKldJgbfOx == true){NKldJgbfOx = false;}
      if(TbppGgDUjL == true){TbppGgDUjL = false;}
      if(zXCMPmKuBd == true){zXCMPmKuBd = false;}
      if(tmdLOMeSbE == true){tmdLOMeSbE = false;}
      if(mXEMbBPZsf == true){mXEMbBPZsf = false;}
      if(lRGiGoHZOW == true){lRGiGoHZOW = false;}
      if(WgejDgydat == true){WgejDgydat = false;}
      if(CksfYbTokO == true){CksfYbTokO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFGVDGCXVL
{ 
  void WHduFYVEAZ()
  { 
      bool LojFAjTtib = false;
      bool XJGbOyCMyC = false;
      bool YWloOfemQW = false;
      bool pVXiJWYIpb = false;
      bool FuBIZaOpmT = false;
      bool IaUBqnCuqT = false;
      bool EgdMkClXSq = false;
      bool YsWWwdVdPn = false;
      bool RnzwOPAVqU = false;
      bool TdRVWYRoWX = false;
      bool npWuuOEyFN = false;
      bool SYeCCQggxV = false;
      bool BQfxXtbAAX = false;
      bool LgGrAaQDBA = false;
      bool KCQcCtzOSG = false;
      bool qjqBVWKZXB = false;
      bool lDygBkSmBb = false;
      bool zdfxKzACuc = false;
      bool uMhtfboEVc = false;
      bool PqeANHEibQ = false;
      string JMhdnXeZlO;
      string AVBtnMaIew;
      string aTYzgDlNfM;
      string suUFCSKUMN;
      string KTNwfknbJC;
      string wgLnQomhwj;
      string kQtZVEBwqU;
      string CGwRlHGcSw;
      string OKEcQMjgoN;
      string ebXbbsYmab;
      string irjnApksCJ;
      string hKOAVaMQJJ;
      string UUGdpZhTpr;
      string hTCqMVZPbZ;
      string apdeeUNXFA;
      string fIdRGOkFxa;
      string HQCKbOIXmz;
      string AwnihdpazV;
      string MJOpLYpkky;
      string jURBRKnTDQ;
      if(JMhdnXeZlO == irjnApksCJ){LojFAjTtib = true;}
      else if(irjnApksCJ == JMhdnXeZlO){npWuuOEyFN = true;}
      if(AVBtnMaIew == hKOAVaMQJJ){XJGbOyCMyC = true;}
      else if(hKOAVaMQJJ == AVBtnMaIew){SYeCCQggxV = true;}
      if(aTYzgDlNfM == UUGdpZhTpr){YWloOfemQW = true;}
      else if(UUGdpZhTpr == aTYzgDlNfM){BQfxXtbAAX = true;}
      if(suUFCSKUMN == hTCqMVZPbZ){pVXiJWYIpb = true;}
      else if(hTCqMVZPbZ == suUFCSKUMN){LgGrAaQDBA = true;}
      if(KTNwfknbJC == apdeeUNXFA){FuBIZaOpmT = true;}
      else if(apdeeUNXFA == KTNwfknbJC){KCQcCtzOSG = true;}
      if(wgLnQomhwj == fIdRGOkFxa){IaUBqnCuqT = true;}
      else if(fIdRGOkFxa == wgLnQomhwj){qjqBVWKZXB = true;}
      if(kQtZVEBwqU == HQCKbOIXmz){EgdMkClXSq = true;}
      else if(HQCKbOIXmz == kQtZVEBwqU){lDygBkSmBb = true;}
      if(CGwRlHGcSw == AwnihdpazV){YsWWwdVdPn = true;}
      if(OKEcQMjgoN == MJOpLYpkky){RnzwOPAVqU = true;}
      if(ebXbbsYmab == jURBRKnTDQ){TdRVWYRoWX = true;}
      while(AwnihdpazV == CGwRlHGcSw){zdfxKzACuc = true;}
      while(MJOpLYpkky == MJOpLYpkky){uMhtfboEVc = true;}
      while(jURBRKnTDQ == jURBRKnTDQ){PqeANHEibQ = true;}
      if(LojFAjTtib == true){LojFAjTtib = false;}
      if(XJGbOyCMyC == true){XJGbOyCMyC = false;}
      if(YWloOfemQW == true){YWloOfemQW = false;}
      if(pVXiJWYIpb == true){pVXiJWYIpb = false;}
      if(FuBIZaOpmT == true){FuBIZaOpmT = false;}
      if(IaUBqnCuqT == true){IaUBqnCuqT = false;}
      if(EgdMkClXSq == true){EgdMkClXSq = false;}
      if(YsWWwdVdPn == true){YsWWwdVdPn = false;}
      if(RnzwOPAVqU == true){RnzwOPAVqU = false;}
      if(TdRVWYRoWX == true){TdRVWYRoWX = false;}
      if(npWuuOEyFN == true){npWuuOEyFN = false;}
      if(SYeCCQggxV == true){SYeCCQggxV = false;}
      if(BQfxXtbAAX == true){BQfxXtbAAX = false;}
      if(LgGrAaQDBA == true){LgGrAaQDBA = false;}
      if(KCQcCtzOSG == true){KCQcCtzOSG = false;}
      if(qjqBVWKZXB == true){qjqBVWKZXB = false;}
      if(lDygBkSmBb == true){lDygBkSmBb = false;}
      if(zdfxKzACuc == true){zdfxKzACuc = false;}
      if(uMhtfboEVc == true){uMhtfboEVc = false;}
      if(PqeANHEibQ == true){PqeANHEibQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYGKBRLJXH
{ 
  void VCyRzOydBu()
  { 
      bool pzbEIhqqKI = false;
      bool TWrjnlttHg = false;
      bool zZNxZTcRId = false;
      bool VSqXmUxaDr = false;
      bool DCdwmtXork = false;
      bool eYXxtPleeo = false;
      bool EYiglAeTwT = false;
      bool oSqOdxwQJe = false;
      bool unZWyxutdX = false;
      bool iSwOneSwJm = false;
      bool PDrYwLgITx = false;
      bool TUUzsPyLho = false;
      bool FjpYjWWbay = false;
      bool dzGVPruBam = false;
      bool PlagDNxwVX = false;
      bool fGOUheMTnY = false;
      bool oEhUSUNziA = false;
      bool UxkuZTJJUW = false;
      bool ZZGDSWjlnk = false;
      bool fbNByKDGNi = false;
      string SOJsbxChuP;
      string szpMICNuxc;
      string OEeYGwBfJg;
      string RuftLEZxZu;
      string uBANJzROyY;
      string gUMaaNikle;
      string uVXOyxSwBD;
      string cQUChNDROG;
      string emhkzxiFTx;
      string VoKuzYclOL;
      string fVNuwQzJrM;
      string KQVeAInmOB;
      string ONcDhmFZDJ;
      string jRCCaJYloi;
      string yZNGlESfuq;
      string joXNxSrJNI;
      string LYGhbsOSEp;
      string iCyfCozVRc;
      string UYeLZtsnFH;
      string QPYfXYSfds;
      if(SOJsbxChuP == fVNuwQzJrM){pzbEIhqqKI = true;}
      else if(fVNuwQzJrM == SOJsbxChuP){PDrYwLgITx = true;}
      if(szpMICNuxc == KQVeAInmOB){TWrjnlttHg = true;}
      else if(KQVeAInmOB == szpMICNuxc){TUUzsPyLho = true;}
      if(OEeYGwBfJg == ONcDhmFZDJ){zZNxZTcRId = true;}
      else if(ONcDhmFZDJ == OEeYGwBfJg){FjpYjWWbay = true;}
      if(RuftLEZxZu == jRCCaJYloi){VSqXmUxaDr = true;}
      else if(jRCCaJYloi == RuftLEZxZu){dzGVPruBam = true;}
      if(uBANJzROyY == yZNGlESfuq){DCdwmtXork = true;}
      else if(yZNGlESfuq == uBANJzROyY){PlagDNxwVX = true;}
      if(gUMaaNikle == joXNxSrJNI){eYXxtPleeo = true;}
      else if(joXNxSrJNI == gUMaaNikle){fGOUheMTnY = true;}
      if(uVXOyxSwBD == LYGhbsOSEp){EYiglAeTwT = true;}
      else if(LYGhbsOSEp == uVXOyxSwBD){oEhUSUNziA = true;}
      if(cQUChNDROG == iCyfCozVRc){oSqOdxwQJe = true;}
      if(emhkzxiFTx == UYeLZtsnFH){unZWyxutdX = true;}
      if(VoKuzYclOL == QPYfXYSfds){iSwOneSwJm = true;}
      while(iCyfCozVRc == cQUChNDROG){UxkuZTJJUW = true;}
      while(UYeLZtsnFH == UYeLZtsnFH){ZZGDSWjlnk = true;}
      while(QPYfXYSfds == QPYfXYSfds){fbNByKDGNi = true;}
      if(pzbEIhqqKI == true){pzbEIhqqKI = false;}
      if(TWrjnlttHg == true){TWrjnlttHg = false;}
      if(zZNxZTcRId == true){zZNxZTcRId = false;}
      if(VSqXmUxaDr == true){VSqXmUxaDr = false;}
      if(DCdwmtXork == true){DCdwmtXork = false;}
      if(eYXxtPleeo == true){eYXxtPleeo = false;}
      if(EYiglAeTwT == true){EYiglAeTwT = false;}
      if(oSqOdxwQJe == true){oSqOdxwQJe = false;}
      if(unZWyxutdX == true){unZWyxutdX = false;}
      if(iSwOneSwJm == true){iSwOneSwJm = false;}
      if(PDrYwLgITx == true){PDrYwLgITx = false;}
      if(TUUzsPyLho == true){TUUzsPyLho = false;}
      if(FjpYjWWbay == true){FjpYjWWbay = false;}
      if(dzGVPruBam == true){dzGVPruBam = false;}
      if(PlagDNxwVX == true){PlagDNxwVX = false;}
      if(fGOUheMTnY == true){fGOUheMTnY = false;}
      if(oEhUSUNziA == true){oEhUSUNziA = false;}
      if(UxkuZTJJUW == true){UxkuZTJJUW = false;}
      if(ZZGDSWjlnk == true){ZZGDSWjlnk = false;}
      if(fbNByKDGNi == true){fbNByKDGNi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQKKVYCREO
{ 
  void WmEiYfhOSl()
  { 
      bool LIhfMNLKnY = false;
      bool qDWPTAUOiY = false;
      bool dXgUNfNdUC = false;
      bool sglQRTYKuU = false;
      bool ZVlIexVQEu = false;
      bool pOuwfnaNSf = false;
      bool zhokfJRFyz = false;
      bool bKSNzHkXoP = false;
      bool KwZYMdlpkd = false;
      bool sKqOVrgAcU = false;
      bool fPSETeugxX = false;
      bool CCYDUDIPYB = false;
      bool XaUUGQTDrG = false;
      bool ajuTiucUFg = false;
      bool iEsMaplntR = false;
      bool jQbaxEtyyD = false;
      bool LqopwSGETZ = false;
      bool ZnKrSThHsP = false;
      bool efJZWKIUWe = false;
      bool AeVCUqPDPI = false;
      string JIhGdkwUYh;
      string JwRPIYMSGc;
      string JcNtHpdRgH;
      string bZimYgGoKJ;
      string HYRuzXdnIP;
      string MGLdugtnzm;
      string GdmRGiNeqa;
      string SWIwUkKRti;
      string LoIQtUOFqr;
      string mRoWCdkAnQ;
      string KzxhwoxPIK;
      string VbsPbQVWWl;
      string UHnynAglsq;
      string AKddYMraTF;
      string WzwfVKXZul;
      string HNcCuCLzsw;
      string ILVRKLyPqO;
      string YtCROVLHbd;
      string bHpHilgahW;
      string BrgXwLcdUK;
      if(JIhGdkwUYh == KzxhwoxPIK){LIhfMNLKnY = true;}
      else if(KzxhwoxPIK == JIhGdkwUYh){fPSETeugxX = true;}
      if(JwRPIYMSGc == VbsPbQVWWl){qDWPTAUOiY = true;}
      else if(VbsPbQVWWl == JwRPIYMSGc){CCYDUDIPYB = true;}
      if(JcNtHpdRgH == UHnynAglsq){dXgUNfNdUC = true;}
      else if(UHnynAglsq == JcNtHpdRgH){XaUUGQTDrG = true;}
      if(bZimYgGoKJ == AKddYMraTF){sglQRTYKuU = true;}
      else if(AKddYMraTF == bZimYgGoKJ){ajuTiucUFg = true;}
      if(HYRuzXdnIP == WzwfVKXZul){ZVlIexVQEu = true;}
      else if(WzwfVKXZul == HYRuzXdnIP){iEsMaplntR = true;}
      if(MGLdugtnzm == HNcCuCLzsw){pOuwfnaNSf = true;}
      else if(HNcCuCLzsw == MGLdugtnzm){jQbaxEtyyD = true;}
      if(GdmRGiNeqa == ILVRKLyPqO){zhokfJRFyz = true;}
      else if(ILVRKLyPqO == GdmRGiNeqa){LqopwSGETZ = true;}
      if(SWIwUkKRti == YtCROVLHbd){bKSNzHkXoP = true;}
      if(LoIQtUOFqr == bHpHilgahW){KwZYMdlpkd = true;}
      if(mRoWCdkAnQ == BrgXwLcdUK){sKqOVrgAcU = true;}
      while(YtCROVLHbd == SWIwUkKRti){ZnKrSThHsP = true;}
      while(bHpHilgahW == bHpHilgahW){efJZWKIUWe = true;}
      while(BrgXwLcdUK == BrgXwLcdUK){AeVCUqPDPI = true;}
      if(LIhfMNLKnY == true){LIhfMNLKnY = false;}
      if(qDWPTAUOiY == true){qDWPTAUOiY = false;}
      if(dXgUNfNdUC == true){dXgUNfNdUC = false;}
      if(sglQRTYKuU == true){sglQRTYKuU = false;}
      if(ZVlIexVQEu == true){ZVlIexVQEu = false;}
      if(pOuwfnaNSf == true){pOuwfnaNSf = false;}
      if(zhokfJRFyz == true){zhokfJRFyz = false;}
      if(bKSNzHkXoP == true){bKSNzHkXoP = false;}
      if(KwZYMdlpkd == true){KwZYMdlpkd = false;}
      if(sKqOVrgAcU == true){sKqOVrgAcU = false;}
      if(fPSETeugxX == true){fPSETeugxX = false;}
      if(CCYDUDIPYB == true){CCYDUDIPYB = false;}
      if(XaUUGQTDrG == true){XaUUGQTDrG = false;}
      if(ajuTiucUFg == true){ajuTiucUFg = false;}
      if(iEsMaplntR == true){iEsMaplntR = false;}
      if(jQbaxEtyyD == true){jQbaxEtyyD = false;}
      if(LqopwSGETZ == true){LqopwSGETZ = false;}
      if(ZnKrSThHsP == true){ZnKrSThHsP = false;}
      if(efJZWKIUWe == true){efJZWKIUWe = false;}
      if(AeVCUqPDPI == true){AeVCUqPDPI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APTMASAWJE
{ 
  void lMQuZUiNVX()
  { 
      bool WhXiaTIDLh = false;
      bool bOauyujrTP = false;
      bool liSrEshIFr = false;
      bool dKcGhJVIQc = false;
      bool HpYrZwYtVj = false;
      bool hTKjEmPedg = false;
      bool kAxSDQlTMo = false;
      bool YbaqHuKZSI = false;
      bool TmlVKJArBu = false;
      bool tqejqHsFnI = false;
      bool JFggKFsTbJ = false;
      bool boLUMxNaIs = false;
      bool QsRRuhxpzA = false;
      bool BFkKzOFFKF = false;
      bool QfPqSEeJWs = false;
      bool tRwurPmPlc = false;
      bool ICTbHWEBVy = false;
      bool rIQDcjdayp = false;
      bool CmTGFjIpRi = false;
      bool apShwOMmjw = false;
      string eqJwAsAVfC;
      string SiBaqJFsQD;
      string KqeELdLyNI;
      string klybXdXOmT;
      string JhPtsoZuKt;
      string pYsyLnLEjV;
      string hCHXRgkYDN;
      string lpGxtcajLW;
      string DPmTSMszPj;
      string RTeQkGZrcM;
      string DBrwIzRwEi;
      string NarNRROnEF;
      string mkJTuSKpLm;
      string ChHzSCXqKT;
      string twufVpaRyT;
      string qlnWYRqXAp;
      string nbjQfeTstP;
      string sXckKqpcxF;
      string qsqrwQsjaB;
      string KApUeSMeAq;
      if(eqJwAsAVfC == DBrwIzRwEi){WhXiaTIDLh = true;}
      else if(DBrwIzRwEi == eqJwAsAVfC){JFggKFsTbJ = true;}
      if(SiBaqJFsQD == NarNRROnEF){bOauyujrTP = true;}
      else if(NarNRROnEF == SiBaqJFsQD){boLUMxNaIs = true;}
      if(KqeELdLyNI == mkJTuSKpLm){liSrEshIFr = true;}
      else if(mkJTuSKpLm == KqeELdLyNI){QsRRuhxpzA = true;}
      if(klybXdXOmT == ChHzSCXqKT){dKcGhJVIQc = true;}
      else if(ChHzSCXqKT == klybXdXOmT){BFkKzOFFKF = true;}
      if(JhPtsoZuKt == twufVpaRyT){HpYrZwYtVj = true;}
      else if(twufVpaRyT == JhPtsoZuKt){QfPqSEeJWs = true;}
      if(pYsyLnLEjV == qlnWYRqXAp){hTKjEmPedg = true;}
      else if(qlnWYRqXAp == pYsyLnLEjV){tRwurPmPlc = true;}
      if(hCHXRgkYDN == nbjQfeTstP){kAxSDQlTMo = true;}
      else if(nbjQfeTstP == hCHXRgkYDN){ICTbHWEBVy = true;}
      if(lpGxtcajLW == sXckKqpcxF){YbaqHuKZSI = true;}
      if(DPmTSMszPj == qsqrwQsjaB){TmlVKJArBu = true;}
      if(RTeQkGZrcM == KApUeSMeAq){tqejqHsFnI = true;}
      while(sXckKqpcxF == lpGxtcajLW){rIQDcjdayp = true;}
      while(qsqrwQsjaB == qsqrwQsjaB){CmTGFjIpRi = true;}
      while(KApUeSMeAq == KApUeSMeAq){apShwOMmjw = true;}
      if(WhXiaTIDLh == true){WhXiaTIDLh = false;}
      if(bOauyujrTP == true){bOauyujrTP = false;}
      if(liSrEshIFr == true){liSrEshIFr = false;}
      if(dKcGhJVIQc == true){dKcGhJVIQc = false;}
      if(HpYrZwYtVj == true){HpYrZwYtVj = false;}
      if(hTKjEmPedg == true){hTKjEmPedg = false;}
      if(kAxSDQlTMo == true){kAxSDQlTMo = false;}
      if(YbaqHuKZSI == true){YbaqHuKZSI = false;}
      if(TmlVKJArBu == true){TmlVKJArBu = false;}
      if(tqejqHsFnI == true){tqejqHsFnI = false;}
      if(JFggKFsTbJ == true){JFggKFsTbJ = false;}
      if(boLUMxNaIs == true){boLUMxNaIs = false;}
      if(QsRRuhxpzA == true){QsRRuhxpzA = false;}
      if(BFkKzOFFKF == true){BFkKzOFFKF = false;}
      if(QfPqSEeJWs == true){QfPqSEeJWs = false;}
      if(tRwurPmPlc == true){tRwurPmPlc = false;}
      if(ICTbHWEBVy == true){ICTbHWEBVy = false;}
      if(rIQDcjdayp == true){rIQDcjdayp = false;}
      if(CmTGFjIpRi == true){CmTGFjIpRi = false;}
      if(apShwOMmjw == true){apShwOMmjw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDZKGTFHGW
{ 
  void cyjeBXCQnb()
  { 
      bool mulBpcXdSy = false;
      bool UPRnApUtRO = false;
      bool OQsRKrRKux = false;
      bool QDjgctEbWP = false;
      bool WkBTOdFItZ = false;
      bool CIJnTWBUqx = false;
      bool KNiUgQfjLF = false;
      bool lrXBrdOZDf = false;
      bool lIPVtItuNG = false;
      bool rikYEICfly = false;
      bool yUwomKkHwo = false;
      bool HbQKKByMaY = false;
      bool VjWFMCGyxi = false;
      bool ahmFhRMahi = false;
      bool XmzXyQSaOC = false;
      bool KoFNbNxqbk = false;
      bool DlKMNYoLbs = false;
      bool oXeqBijzGw = false;
      bool jfjtYlcZcT = false;
      bool TVzwfkblJZ = false;
      string CrirEgJgnX;
      string VITLHoNCyL;
      string ePLAHBzxQX;
      string cDOXkzmJKG;
      string TlMYQJAkBp;
      string PZRkbmghjD;
      string hMQPtRswaI;
      string CEqqqsCmjy;
      string BNuZIDlduy;
      string SEYHYHUxdy;
      string PDJsnLhash;
      string jtxkBTQqHp;
      string fPAcoxejSi;
      string YFIkixEBlw;
      string VLkMNYHnFF;
      string qdonSzDgEp;
      string gyHJJekLBE;
      string POFKUUemPP;
      string ppdMruPUSi;
      string tWxuPXDaDh;
      if(CrirEgJgnX == PDJsnLhash){mulBpcXdSy = true;}
      else if(PDJsnLhash == CrirEgJgnX){yUwomKkHwo = true;}
      if(VITLHoNCyL == jtxkBTQqHp){UPRnApUtRO = true;}
      else if(jtxkBTQqHp == VITLHoNCyL){HbQKKByMaY = true;}
      if(ePLAHBzxQX == fPAcoxejSi){OQsRKrRKux = true;}
      else if(fPAcoxejSi == ePLAHBzxQX){VjWFMCGyxi = true;}
      if(cDOXkzmJKG == YFIkixEBlw){QDjgctEbWP = true;}
      else if(YFIkixEBlw == cDOXkzmJKG){ahmFhRMahi = true;}
      if(TlMYQJAkBp == VLkMNYHnFF){WkBTOdFItZ = true;}
      else if(VLkMNYHnFF == TlMYQJAkBp){XmzXyQSaOC = true;}
      if(PZRkbmghjD == qdonSzDgEp){CIJnTWBUqx = true;}
      else if(qdonSzDgEp == PZRkbmghjD){KoFNbNxqbk = true;}
      if(hMQPtRswaI == gyHJJekLBE){KNiUgQfjLF = true;}
      else if(gyHJJekLBE == hMQPtRswaI){DlKMNYoLbs = true;}
      if(CEqqqsCmjy == POFKUUemPP){lrXBrdOZDf = true;}
      if(BNuZIDlduy == ppdMruPUSi){lIPVtItuNG = true;}
      if(SEYHYHUxdy == tWxuPXDaDh){rikYEICfly = true;}
      while(POFKUUemPP == CEqqqsCmjy){oXeqBijzGw = true;}
      while(ppdMruPUSi == ppdMruPUSi){jfjtYlcZcT = true;}
      while(tWxuPXDaDh == tWxuPXDaDh){TVzwfkblJZ = true;}
      if(mulBpcXdSy == true){mulBpcXdSy = false;}
      if(UPRnApUtRO == true){UPRnApUtRO = false;}
      if(OQsRKrRKux == true){OQsRKrRKux = false;}
      if(QDjgctEbWP == true){QDjgctEbWP = false;}
      if(WkBTOdFItZ == true){WkBTOdFItZ = false;}
      if(CIJnTWBUqx == true){CIJnTWBUqx = false;}
      if(KNiUgQfjLF == true){KNiUgQfjLF = false;}
      if(lrXBrdOZDf == true){lrXBrdOZDf = false;}
      if(lIPVtItuNG == true){lIPVtItuNG = false;}
      if(rikYEICfly == true){rikYEICfly = false;}
      if(yUwomKkHwo == true){yUwomKkHwo = false;}
      if(HbQKKByMaY == true){HbQKKByMaY = false;}
      if(VjWFMCGyxi == true){VjWFMCGyxi = false;}
      if(ahmFhRMahi == true){ahmFhRMahi = false;}
      if(XmzXyQSaOC == true){XmzXyQSaOC = false;}
      if(KoFNbNxqbk == true){KoFNbNxqbk = false;}
      if(DlKMNYoLbs == true){DlKMNYoLbs = false;}
      if(oXeqBijzGw == true){oXeqBijzGw = false;}
      if(jfjtYlcZcT == true){jfjtYlcZcT = false;}
      if(TVzwfkblJZ == true){TVzwfkblJZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLACLFFDLB
{ 
  void QAqlkCNYGA()
  { 
      bool bfpVwbpxPl = false;
      bool EawqqVMxtw = false;
      bool sfTowPjxZZ = false;
      bool ucABQiTGuH = false;
      bool KXIVJzKiFE = false;
      bool DDmKLwMBZf = false;
      bool rrXoqbauaH = false;
      bool BFCmkUXyex = false;
      bool FArUWqpooU = false;
      bool WSfOOSASeh = false;
      bool XOIxDxBzZq = false;
      bool YNVbarACRz = false;
      bool kkGGjhZmYS = false;
      bool TESwYqrtQZ = false;
      bool pqPyuIxEnW = false;
      bool RxAexlHCNV = false;
      bool XNaGWTtYCi = false;
      bool zFlrIsVHKa = false;
      bool kUzBAVEnzm = false;
      bool ipgtCcQIaa = false;
      string WtflfEJgAb;
      string jZfaHsHEgh;
      string XUjGlwkREE;
      string TGqiCVxbJT;
      string CHyHxUrAuY;
      string OEOfxCJZAj;
      string SrbuIdhxYk;
      string ufuNfPVcIR;
      string EkVfoOqLkz;
      string MXbYBJfDzT;
      string ltbJciJBAg;
      string ggQhfgWwGt;
      string lWLYYWDVLV;
      string jScoeJJLCF;
      string EpLDSfHssT;
      string mixFgPiCkG;
      string fnodxODaDW;
      string WKsAouKHFs;
      string PKbriAUXHO;
      string ZGawZPAgGE;
      if(WtflfEJgAb == ltbJciJBAg){bfpVwbpxPl = true;}
      else if(ltbJciJBAg == WtflfEJgAb){XOIxDxBzZq = true;}
      if(jZfaHsHEgh == ggQhfgWwGt){EawqqVMxtw = true;}
      else if(ggQhfgWwGt == jZfaHsHEgh){YNVbarACRz = true;}
      if(XUjGlwkREE == lWLYYWDVLV){sfTowPjxZZ = true;}
      else if(lWLYYWDVLV == XUjGlwkREE){kkGGjhZmYS = true;}
      if(TGqiCVxbJT == jScoeJJLCF){ucABQiTGuH = true;}
      else if(jScoeJJLCF == TGqiCVxbJT){TESwYqrtQZ = true;}
      if(CHyHxUrAuY == EpLDSfHssT){KXIVJzKiFE = true;}
      else if(EpLDSfHssT == CHyHxUrAuY){pqPyuIxEnW = true;}
      if(OEOfxCJZAj == mixFgPiCkG){DDmKLwMBZf = true;}
      else if(mixFgPiCkG == OEOfxCJZAj){RxAexlHCNV = true;}
      if(SrbuIdhxYk == fnodxODaDW){rrXoqbauaH = true;}
      else if(fnodxODaDW == SrbuIdhxYk){XNaGWTtYCi = true;}
      if(ufuNfPVcIR == WKsAouKHFs){BFCmkUXyex = true;}
      if(EkVfoOqLkz == PKbriAUXHO){FArUWqpooU = true;}
      if(MXbYBJfDzT == ZGawZPAgGE){WSfOOSASeh = true;}
      while(WKsAouKHFs == ufuNfPVcIR){zFlrIsVHKa = true;}
      while(PKbriAUXHO == PKbriAUXHO){kUzBAVEnzm = true;}
      while(ZGawZPAgGE == ZGawZPAgGE){ipgtCcQIaa = true;}
      if(bfpVwbpxPl == true){bfpVwbpxPl = false;}
      if(EawqqVMxtw == true){EawqqVMxtw = false;}
      if(sfTowPjxZZ == true){sfTowPjxZZ = false;}
      if(ucABQiTGuH == true){ucABQiTGuH = false;}
      if(KXIVJzKiFE == true){KXIVJzKiFE = false;}
      if(DDmKLwMBZf == true){DDmKLwMBZf = false;}
      if(rrXoqbauaH == true){rrXoqbauaH = false;}
      if(BFCmkUXyex == true){BFCmkUXyex = false;}
      if(FArUWqpooU == true){FArUWqpooU = false;}
      if(WSfOOSASeh == true){WSfOOSASeh = false;}
      if(XOIxDxBzZq == true){XOIxDxBzZq = false;}
      if(YNVbarACRz == true){YNVbarACRz = false;}
      if(kkGGjhZmYS == true){kkGGjhZmYS = false;}
      if(TESwYqrtQZ == true){TESwYqrtQZ = false;}
      if(pqPyuIxEnW == true){pqPyuIxEnW = false;}
      if(RxAexlHCNV == true){RxAexlHCNV = false;}
      if(XNaGWTtYCi == true){XNaGWTtYCi = false;}
      if(zFlrIsVHKa == true){zFlrIsVHKa = false;}
      if(kUzBAVEnzm == true){kUzBAVEnzm = false;}
      if(ipgtCcQIaa == true){ipgtCcQIaa = false;}
    } 
}; 
