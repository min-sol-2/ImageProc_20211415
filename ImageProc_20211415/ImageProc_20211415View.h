
// ImageProc_20211415View.h: CImageProc20211415View 클래스의 인터페이스
//

#pragma once


class CImageProc20211415View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProc20211415View() noexcept;
	DECLARE_DYNCREATE(CImageProc20211415View)

// 특성입니다.
public:
	CImageProc20211415Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC)
	{
		CImageProc20211415Doc* pDoc = GetDocument();

		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		int x, y;

		if (bAviMode)
		{
			LoadAviFile(pDC);
			// avi 화일 재생
			bAviMode = false;
			return;
		}


		if (pDoc->Inputimg != NULL)
		{
			if (pDoc->depth == 1)
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(x, y, RGB(pDoc->Inputimg[y][x], pDoc->Inputimg[y][x], pDoc->Inputimg[y][x]));
			} // 흑백일때 처리 방법
			else
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(x, y, RGB(pDoc->Inputimg[y][x * 3 + 0], pDoc->Inputimg[y][x * 3 + 1], pDoc->Inputimg[y][x * 3 + 2]));
			} // 컬러일때 처리 방법
		}

		if (pDoc->Resultimg != NULL)
		{
			if (pDoc->depth == 1)
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(pDoc->ImageWidth + x + 20, y, RGB(pDoc->Resultimg[y][x], pDoc->Resultimg[y][x], pDoc->Resultimg[y][x]));
			}
			else
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(pDoc->ImageWidth + x + 20, y, RGB(pDoc->Resultimg[y][x * 3 + 0], pDoc->Resultimg[y][x * 3 + 1], pDoc->Resultimg[y][x * 3 + 2]));
			}
		}

		if (pDoc->Inputimg2 != NULL)
		{
			if (pDoc->depth == 1)
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel((pDoc->ImageWidth + 20) * 2 + x, y, RGB(pDoc->Inputimg2[y][x], pDoc->Inputimg2[y][x], pDoc->Inputimg2[y][x]));
			}
			else
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel((pDoc->ImageWidth + 20) * 2 + x, y, RGB(pDoc->Inputimg2[y][x * 3 + 0], pDoc->Inputimg2[y][x * 3 + 1], pDoc->Inputimg2[y][x * 3 + 2]));
			}
		}

		if (pDoc->gResultimg != NULL)
		{
			if (pDoc->depth == 1)
			{
				for (y = 0; y < pDoc->gImageHeight; y++)
					for (x = 0; x < pDoc->gImageWidth; x++)
						pDC->SetPixel(x, pDoc->ImageWidth + 20 + y, RGB(pDoc->gResultimg[y][x], pDoc->gResultimg[y][x], pDoc->gResultimg[y][x]));
			}
			else
			{
				for (y = 0; y < pDoc->gImageHeight; y++)
					for (x = 0; x < pDoc->gImageWidth; x++)
						pDC->SetPixel(x, pDoc->ImageWidth + 20 + y, RGB(pDoc->gResultimg[y][x * 3 + 0], pDoc->gResultimg[y][x * 3 + 1], pDoc->gResultimg[y][x * 3 + 2]));
			}
		}
	}  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CImageProc20211415View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnManutest();
	afx_msg void OnFixelAdd();
	afx_msg void OnFixelSub();
	afx_msg void OnFixelMul();
	afx_msg void OnFixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	void LoadTwoImage();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionSharpening();
	void convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyColorToGray();
	afx_msg void OnMopologyDilation();
	afx_msg void OnMopologyOpening();
	void CopyResultToInput();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSubsampling();
	afx_msg void OnGeometryZoomoutAvgSampling();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGrometryFlip();
	afx_msg void OnGeometryWarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	bool bAviMode;
	CString AVIFileName;
	void LoadAviFile(CDC* pDC);
};

#ifndef _DEBUG  // ImageProc_20211415View.cpp의 디버그 버전
inline CImageProc20211415Doc* CImageProc20211415View::GetDocument() const
   { return reinterpret_cast<CImageProc20211415Doc*>(m_pDocument); }
#endif

