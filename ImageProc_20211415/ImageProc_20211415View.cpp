
// ImageProc_20211415View.cpp: CImageProc20211415View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20211415.h"
#endif

#include "ImageProc_20211415Doc.h"
#include "ImageProc_20211415View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CAngleInputDialog.h"

#include <vfw.h>

// CImageProc20211415View

IMPLEMENT_DYNCREATE(CImageProc20211415View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProc20211415View, CScrollView)
//ON_COMMAND(ID_MANUTEST, &CImageProc20211415View::OnManutest)
ON_COMMAND(ID_FIXEL_ADD, &CImageProc20211415View::OnFixelAdd)
ON_COMMAND(ID_FIXEL_DIV, &CImageProc20211415View::OnFixelDiv)
ON_COMMAND(ID_FIXEL_SUB, &CImageProc20211415View::OnFixelSub)
ON_COMMAND(ID_FIXEL_MUL, &CImageProc20211415View::OnFixelMul)
ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProc20211415View::OnPixelHistoEq)
ON_COMMAND(ID_PIXEL_STRETCHING, &CImageProc20211415View::OnPixelStretching)
ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProc20211415View::OnPixelBinarization)
ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProc20211415View::OnPixelTwoImageAdd)
ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImageProc20211415View::OnPixelTwoImageSub)
ON_COMMAND(ID_REGION_SHARPENING, &CImageProc20211415View::OnRegionSharpening)
ON_COMMAND(ID_REGION_SMOOTHING, &CImageProc20211415View::OnRegionSmoothing)
ON_COMMAND(ID_REGION_EMBOSSING, &CImageProc20211415View::OnRegionEmbossing)
ON_COMMAND(ID_REGION_PREWITT, &CImageProc20211415View::OnRegionPrewitt)
ON_COMMAND(ID_REGION_ROBERTS, &CImageProc20211415View::OnRegionRoberts)
ON_COMMAND(ID_REGION_SOBEL, &CImageProc20211415View::OnRegionSobel)
ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CImageProc20211415View::OnRegionAverageFiltering)
ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CImageProc20211415View::OnRegionMedianFiltering)
ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CImageProc20211415View::OnMopologyBinarization)
ON_COMMAND(ID_MOPOLOGY_EROSION, &CImageProc20211415View::OnMopologyErosion)
ON_COMMAND(ID_MOPOLOGY_COLOR_TO_GRAY, &CImageProc20211415View::OnMopologyColorToGray)
ON_COMMAND(ID_MOPOLOGY_DILATION, &CImageProc20211415View::OnMopologyDilation)
ON_COMMAND(ID_MOPOLOGY_OPENING, &CImageProc20211415View::OnMopologyOpening)
ON_COMMAND(ID_MOPOLOGY_CLOSING, &CImageProc20211415View::OnMopologyClosing)
ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProc20211415View::OnGeometryZoominPixelCopy)
ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEAR_INTERPOLATION, &CImageProc20211415View::OnGeometryZoominBilinearInterpolation)
ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProc20211415View::OnGeometryZoomoutSubsampling)
ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUBSAMPLING, &CImageProc20211415View::OnGeometryZoomoutMeanSubsampling)
ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG_SAMPLING, &CImageProc20211415View::OnGeometryZoomoutAvgSampling)
ON_COMMAND(ID_GEOMETRY_ROTATION, &CImageProc20211415View::OnGeometryRotation)
ON_COMMAND(ID_GEOMETRY_MIRROR, &CImageProc20211415View::OnGeometryMirror)
ON_COMMAND(ID_GROMETRY_FLIP, &CImageProc20211415View::OnGrometryFlip)
ON_COMMAND(ID_GEOMETRY_WARPING, &CImageProc20211415View::OnGeometryWarping)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_COMMAND(ID_AVI_VIEW, &CImageProc20211415View::OnAviView)
END_MESSAGE_MAP()

// CImageProc20211415View 생성/소멸

CImageProc20211415View::CImageProc20211415View() noexcept
{
	bAviMode = false;

}

CImageProc20211415View::~CImageProc20211415View()
{
}

BOOL CImageProc20211415View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProc20211415View 그리기

void CImageProc20211415View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProc20211415View 진단

#ifdef _DEBUG
void CImageProc20211415View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProc20211415View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProc20211415Doc* CImageProc20211415View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc20211415Doc)));
	return (CImageProc20211415Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProc20211415View 메시지 처리기


void CImageProc20211415View::OnManutest()
{
}


void CImageProc20211415View::OnFixelAdd()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	if (pDoc->Inputimg == NULL) return; // 사용자가 모르고 눌렀을때 프로그램 다운을 막음

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->Inputimg[y][x] + 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x] = value;
			} // 흑백일 경우
			else
			{
				value = pDoc->Inputimg[y][x * 3 + 0] + 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 0] = value;

				value = pDoc->Inputimg[y][x * 3 + 1] + 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 1] = value;

				value = pDoc->Inputimg[y][x * 3 + 2] + 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 2] = value;
			} // 컬러일 경우
		}

	Invalidate(); // 화면 다시 호출

}


void CImageProc20211415View::OnFixelSub()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->Inputimg[y][x] - 20;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				value = pDoc->Inputimg[y][x * 3 + 0] - 20; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 0] = value;

				value = pDoc->Inputimg[y][x * 3 + 1] - 20; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 1] = value;

				value = pDoc->Inputimg[y][x * 3 + 2] - 20;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 2] = value;
			}
		}
	Invalidate();
		
}


void CImageProc20211415View::OnFixelMul()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->Inputimg[y][x] * 1.5;
				if (value > 255) value = 255;
				else if (value < 0)value = 0;

				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				value = pDoc->Inputimg[y][x * 3 + 0] * 1.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 0] = value;

				value = pDoc->Inputimg[y][x * 3 + 1] * 1.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 1] = value;

				value = pDoc->Inputimg[y][x * 3 + 2] * 1.5;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 2] = value;
			}
		}
	Invalidate();
}


void CImageProc20211415View::OnFixelDiv()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->Inputimg[y][x] - 20;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				value = pDoc->Inputimg[y][x * 3 + 0] / 3; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 0] = value;

				value = pDoc->Inputimg[y][x * 3 + 1] / 3; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 1] = value;

				value = pDoc->Inputimg[y][x * 3 + 2] / 3;

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x * 3 + 2] = value;
			}
		}
	Invalidate();
}


void CImageProc20211415View::OnPixelHistoEq()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y, k;
	int acc_hist = 0;
	int N = 256 * 256;
	int hist[256], sum[256];

	for (int k = 0; k < 256; k++)		hist[k] = 0;
	
	//히스토그램 구하기
	for(y=0; y<256; y++)
		for (x = 0; x < 256; x++)
		{
			k = pDoc->Inputimg[y][x];
			hist[k]++;
		}

	//누적분포
	acc_hist = 0;
	for (k = 0; k < 256; k++) 
	{
		acc_hist += hist[k];
		sum[k] = acc_hist;
	}

	//픽셀 밝기 변환
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			k = pDoc->Inputimg[y][x];
			pDoc->Resultimg[y][x] = (float)sum[k] / N*255;
		}

	Invalidate();

}


void CImageProc20211415View::OnPixelStretching()
{
	CImageProc20211415Doc* pDoc = GetDocument();
	
	int min = 256, max = -1;
	int rmin = 256, rmax = -1, gmin = 256, gmax = -1, bmin = 256, bmax = -1;
	int x, y, p;

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			if (pDoc->depth == 1) {	 //흑백 이미지
				if (pDoc->Inputimg[y][x] < min) min = pDoc->Inputimg[y][x];
				if (pDoc->Inputimg[y][x] > max) max = pDoc->Inputimg[y][x];
			}
			else {	 //컬러 이미지
				if (pDoc->Inputimg[y][x * 3 + 0] < rmin) rmin = pDoc->Inputimg[y][x * 3 + 0];
				if (pDoc->Inputimg[y][x * 3 + 0] > rmax) rmax = pDoc->Inputimg[y][x * 3 + 0];

				if (pDoc->Inputimg[y][x * 3 + 1] < gmin) gmin = pDoc->Inputimg[y][x * 3 + 1];
				if (pDoc->Inputimg[y][x * 3 + 1] > gmax) gmax = pDoc->Inputimg[y][x * 3 + 1];

				if (pDoc->Inputimg[y][x * 3 + 2] < bmin) bmin = pDoc->Inputimg[y][x * 3 + 2];
				if (pDoc->Inputimg[y][x * 3 + 2] > bmax) bmax = pDoc->Inputimg[y][x * 3 + 2];
			}
		}
	}
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			if (pDoc->depth == 1) {	 //흑백 이미지
				p = pDoc->Inputimg[y][x];
				pDoc->Resultimg[y][x] = (float)(p - min) / (max - min) * 255;
			}
			else {	 //컬러 이미지
				p = pDoc->Inputimg[y][x * 3 + 0];
				pDoc->Resultimg[y][x * 3 + 0] = (float)(p - rmin) / (rmax - rmin) * 255;

				p = pDoc->Inputimg[y][x * 3 + 1];
				pDoc->Resultimg[y][x * 3 + 1] = (float)(p - gmin) / (gmax - gmin) * 255;

				p = pDoc->Inputimg[y][x * 3 + 2];
				pDoc->Resultimg[y][x * 3 + 2] = (float)(p - bmin) / (bmax - bmin) * 255;
			}
		}
	}

	Invalidate();
}


void CImageProc20211415View::OnPixelBinarization()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y;
	int threshold = 150;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			if (pDoc->Inputimg[y][x] >= threshold) pDoc->Resultimg[y][x] = 255;
			else								  pDoc->Resultimg[y][x] = 0;
		}

	Invalidate();

}


void CImageProc20211415View::OnPixelTwoImageAdd()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					pDoc->Resultimg[y][x] = 0.5 * pDoc->Inputimg[y][x] + 0.5 * pDoc->Inputimg2[y][x];
				}
				else
				{
					pDoc->Resultimg[y][3 * x + 0] = 0.5 * pDoc->Inputimg[y][3 * x + 0] + 0.5 * pDoc->Inputimg2[y][3 * x + 0];
					pDoc->Resultimg[y][3 * x + 1] = 0.5 * pDoc->Inputimg[y][3 * x + 1] + 0.5 * pDoc->Inputimg2[y][3 * x + 1];
					pDoc->Resultimg[y][3 * x + 2] = 0.5 * pDoc->Inputimg[y][3 * x + 2] + 0.5 * pDoc->Inputimg2[y][3 * x + 2];
				}
			}
		Invalidate();
	}
}


void CImageProc20211415View::LoadTwoImage()
{
	CImageProc20211415Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		CFile file;
		file.Open(dlg.GetPathName(), CFile::modeRead);		//화일열기
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);

		file.Close();

	}
}


void CImageProc20211415View::OnPixelTwoImageSub()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	LoadTwoImage();
	int x, y, value;

	for (y = 0; y < pDoc -> ImageHeight; y++)
		for (x = 0; x < pDoc -> ImageWidth; x++)
		{
			value = pDoc->Inputimg[y][x] - pDoc->Inputimg2[y][x];
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			if (value > 64) value = 255;
			else			value = 0;
			pDoc->Resultimg[y][x] = value;
		}

	Invalidate();
}


void CImageProc20211415View::OnRegionSharpening()
{
	CImageProc20211415Doc * pDoc = GetDocument();
	
	float kernel[3][3] = { {0,-1,0}, {-1,5,-1}, {0,-1, 0} };
	
	convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20211415View::convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3] , int bias, int depth)
{
	int x, y;
	int i, j;
	int sum, rsum, gsum, bsum;

	for (y = 1; y < rows - 1; y++)
		for (x = 1; x < cols - 1; x++)
		{
			if (depth == 1)
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += (inimg[y + j - 1][x + i - 1] * mask[j][i]);
					}
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				outimg[y][x] = sum;

			}
			else
			{
				rsum = 0;	gsum = 0;	bsum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += (inimg[y + j - 1][3 * (x + i - 1) + 0] * mask[j][i]);
						gsum += (inimg[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
						bsum += (inimg[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);
					}
				rsum += bias;
				gsum += bias;
				bsum += bias;

				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				outimg[y][3 * x + 0] = rsum;
				outimg[y][3 * x + 1] = gsum;
				outimg[y][3 * x + 2] = bsum;
			}
		}
}


void CImageProc20211415View::OnRegionSmoothing()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	float kernel[3][3] = { {1 / 9.0f, 1 / 9.0f, 1 / 9.0f}, {1 / 9.0f, 1 / 9.0f, 1 / 9.0f} , {1 / 9.0f, 1 / 9.0f, 1 / 9.0f} };

	convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20211415View::OnRegionEmbossing()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	float kernel[3][3] = { {-1, 0, 0}, {0, 0, 0}, {0, 0, 1} };

	convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 128, pDoc->depth);

	Invalidate();

}


void CImageProc20211415View::OnRegionPrewitt()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {-1, -1, -1}, {0, 0, 0}, {1, 1, 1} };
	float kernel_v[3][3] = { {1, 0, -1}, {1, 0, -1}, {1, 0, -1} };

	unsigned char** Er, ** Ec;
	int x, y, i;
	int value;
	int rvalue, gvalue, bvalue;

	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc -> ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);


	

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
			value = sqrt((Er[y][x]-128) * (Er[y][x]-128) + (Ec[y][x]-128) * (Ec[y][x]-128));
				if (value > 255)    value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else 
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rvalue > 255) rvalue = 255;
				else if (rvalue < 0) rvalue = 0;

				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gvalue > 255) gvalue = 255;
				else if (gvalue < 0) gvalue = 0;

				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bvalue > 255) bvalue = 255;
				else if (bvalue < 0) bvalue = 0;

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)    value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20211415View::OnRegionRoberts()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {-1, 0, 0}, {0, 1, 0}, {0, 0, 0} };
	float kernel_v[3][3] = { {0, -0, -1}, {0, 1, 0}, {0, 0, 0} };

	unsigned char** Er, ** Ec;
	int x, y, i;
	int value;
	int rvalue, gvalue, bvalue;

	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);




	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)    value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)    value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20211415View::OnRegionSobel()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
	float kernel_v[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} };

	unsigned char** Er, ** Ec;
	int x, y, i;
	int value;
	int rvalue, gvalue, bvalue;

	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);




	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)    value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rvalue > 255) rvalue = 255;
				else if (rvalue < 0) rvalue = 0;

				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gvalue > 255) gvalue = 255;
				else if (gvalue < 0) gvalue = 0;

				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bvalue > 255) bvalue = 255;
				else if (bvalue < 0) bvalue = 0;

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)    value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20211415View::OnRegionAverageFiltering()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y, i, j;
	int xpos, ypos;
	int sum, rsum, gsum, bsum;
	int pixelcount;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			sum = 0; pixelcount = 0; rsum = gsum = bsum = 0;
			for (j = -2; j <= 2; j++) 
				for (i = -2; i <= 2; i++) 
				{
					xpos = x + i;
					ypos = y + j;
					if (xpos > 0 && xpos <= pDoc->ImageWidth - 1 && ypos >= 0 && ypos <= pDoc->ImageHeight - 1) 
					{
						if(pDoc->depth == 1)
						sum += pDoc->Inputimg[y+j][x+i];
						else
						{
							rsum += pDoc->Inputimg[y + j][3 * (x + i) + 0];
							gsum += pDoc->Inputimg[y + j][3 * (x + i) + 1];
							bsum += pDoc->Inputimg[y + j][3 * (x + i) + 2];
						}
						pixelcount++;
					}
				}
			if(pDoc->depth == 1)
				pDoc->Resultimg[y][x] = sum / pixelcount;
			else
			{
				pDoc->Resultimg[y][3 * x + 0] = rsum / pixelcount;
				pDoc->Resultimg[y][3 * x + 1] = gsum / pixelcount;
				pDoc->Resultimg[y][3 * x + 2] = bsum / pixelcount;
			}
		}
	Invalidate();
}


void CImageProc20211415View::OnRegionMedianFiltering()
{
	CImageProc20211415Doc* pDoc = GetDocument();
	
	int x, y, i, j;
	int n[9], temp;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)
		{
			if (pDoc->depth == 1)
			{
				n[0] = pDoc->Inputimg[y - 1][x - 1];
				n[1] = pDoc->Inputimg[y - 1][x - 0];
				n[2] = pDoc->Inputimg[y - 1][x + 1];

				n[3] = pDoc->Inputimg[y - 0][x - 1];
				n[4] = pDoc->Inputimg[y - 0][x - 0];
				n[5] = pDoc->Inputimg[y - 0][x + 1];

				n[6] = pDoc->Inputimg[y + 1][x - 1];
				n[7] = pDoc->Inputimg[y + 1][x - 0];
				n[8] = pDoc->Inputimg[y + 1][x + 1];

			// 버블소팅(오름차순)
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) 
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->Resultimg[y][x] = n[4];
			}
			else {
				n[0] = pDoc->Inputimg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->Inputimg[y - 1][3 * (x + 0) + 0];
				n[2] = pDoc->Inputimg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->Inputimg[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->Inputimg[y - 0][3 * (x + 0) + 0];
				n[5] = pDoc->Inputimg[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->Inputimg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->Inputimg[y + 1][3 * (x + 0) + 0];
				n[8] = pDoc->Inputimg[y + 1][3 * (x + 1) + 0];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->Resultimg[y][3 * x + 0] = n[4];

				n[0] = pDoc->Inputimg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->Inputimg[y - 1][3 * (x + 0) + 1];
				n[2] = pDoc->Inputimg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->Inputimg[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->Inputimg[y - 0][3 * (x + 0) + 1];
				n[5] = pDoc->Inputimg[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->Inputimg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->Inputimg[y + 1][3 * (x + 0) + 1];
				n[8] = pDoc->Inputimg[y + 1][3 * (x + 1) + 1];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->Resultimg[y][3 * x + 1] = n[4];

				n[0] = pDoc->Inputimg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->Inputimg[y - 1][3 * (x + 0) + 2];
				n[2] = pDoc->Inputimg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->Inputimg[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->Inputimg[y - 0][3 * (x + 0) + 2];
				n[5] = pDoc->Inputimg[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->Inputimg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->Inputimg[y + 1][3 * (x + 0) + 2];
				n[8] = pDoc->Inputimg[y + 1][3 * (x + 1) + 2];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->Resultimg[y][3 * x + 2] = n[4];
			}
		}
	Invalidate();

}


void CImageProc20211415View::OnMopologyColorToGray()
{
	CImageProc20211415Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;

	for (y = 1; y < pDoc->ImageHeight; y++)
		for (x = 1; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->Inputimg[y][3 * x + 0] + pDoc->Inputimg[y][3 * x + 1] + pDoc->Inputimg[y][3 * x + 2]) / 3;
			pDoc->Inputimg[y][3 * x + 0] = gray;
			pDoc->Inputimg[y][3 * x + 1] = gray;
			pDoc->Inputimg[y][3 * x + 2] = gray;
		}
	Invalidate();
}


void CImageProc20211415View::OnMopologyBinarization()
{
	CImageProc20211415Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray, threshold = 100;

	for (y = 1; y < pDoc->ImageHeight; y++)
		for (x = 1; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->Inputimg[y][x] > threshold) pDoc->Inputimg[y][x] = 255;
				else                                  pDoc->Inputimg[y][x] = 0;
			}
			else
			{
				if ((pDoc->Inputimg[y][3 * x + 0] + pDoc->Inputimg[y][3 * x + 1] + pDoc->Inputimg[y][3 * x + 2]) / 3 > threshold)
				{
					pDoc->Inputimg[y][3 * x + 0] = 255;
					pDoc->Inputimg[y][3 * x + 1] = 255;
					pDoc->Inputimg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->Inputimg[y][3 * x + 0] = 0;
					pDoc->Inputimg[y][3 * x + 1] = 0;
					pDoc->Inputimg[y][3 * x + 2] = 0;
				}
			}

		}
	Invalidate();
}


void CImageProc20211415View::OnMopologyErosion()
{
	CImageProc20211415Doc* pDoc = GetDocument();
	int x, y, i, j;
	int min = 255;
	int rmin, gmin, bmin;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			min = 255; rmin = 255; gmin = 255; bmin = 255;
			for(j=-1; j<= 1; j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->Inputimg[y + j][x + i] < min)	min = pDoc->Inputimg[y + j][x + i];
					}
					else
					{
						if (pDoc->Inputimg[y + j][3 * (x + i) + 0] < rmin)	rmin = pDoc->Inputimg[y + j][3 * (x + i) + 0];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 1] < gmin)	gmin = pDoc->Inputimg[y + j][3 * (x + i) + 1];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 2] < bmin)	bmin = pDoc->Inputimg[y + j][3 * (x + i) + 2];
					}
					
				}
			if(pDoc->depth == 1)
				pDoc->Resultimg[y][x] = min;
			else {
				pDoc->Resultimg[y][3 * x + 0] = rmin;
				pDoc->Resultimg[y][3 * x + 1] = gmin;
				pDoc->Resultimg[y][3 * x + 2] = bmin;
			}
			
		}
	Invalidate();
}

void CImageProc20211415View::OnMopologyDilation()
{
	CImageProc20211415Doc* pDoc = GetDocument();
	int x, y, i, j;
	int max, rmax, gmax, bmax;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			max = 0; rmax = 0; gmax = 0; bmax = 0;
			for (j = -1; j <= 1; j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->Inputimg[y + j][x + i] > max)	max = pDoc->Inputimg[y + j][x + i];
					}
					else
					{
						if (pDoc->Inputimg[y + j][3 * (x + i) + 0] > rmax)	rmax = pDoc->Inputimg[y + j][3 * (x + i) + 0];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 1] > gmax)	gmax = pDoc->Inputimg[y + j][3 * (x + i) + 1];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 2] > bmax)	bmax = pDoc->Inputimg[y + j][3 * (x + i) + 2];
					}

				}
			if (pDoc->depth == 1)
				pDoc->Resultimg[y][x] = max;
			else {
				pDoc->Resultimg[y][3 * x + 0] = rmax;
				pDoc->Resultimg[y][3 * x + 1] = gmax;
				pDoc->Resultimg[y][3 * x + 2] = bmax;
			}

		}
	Invalidate();
}


void CImageProc20211415View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();

}


void CImageProc20211415View::CopyResultToInput()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{
			pDoc->Inputimg[y][x] = pDoc->Resultimg[y][x];
		}
}


void CImageProc20211415View::OnMopologyClosing()
{
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();

	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	
}


void CImageProc20211415View::OnGeometryZoominPixelCopy()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int xscale = 3;
	int yscale = 2;
	int x, y, i;

	if (pDoc->gResultimg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;

	pDoc-> gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++) 
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

/*
	// 전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
				pDoc->gResultimg[y* yscale][x * xscale] = pDoc->Inputimg[y][x];
			
		}
*/

	// 역방향 사상
	for(y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if(pDoc->depth == 1)
				pDoc->gResultimg[y][x] = pDoc->Inputimg[y / yscale][x / xscale];
			else
			{
				pDoc->gResultimg[y][3 * x + 0] = pDoc->Inputimg[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultimg[y][3 * x + 1] = pDoc->Inputimg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultimg[y][3 * x + 2] = pDoc->Inputimg[y / yscale][3 * (x / xscale) + 2];
			}
		}
	Invalidate();

}


void CImageProc20211415View::OnGeometryZoominBilinearInterpolation()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	float xscale = 2.1;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int x, y, i;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultimg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	pDoc->gImageWidth =(pDoc->ImageWidth) * xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) * yscale;

	pDoc->gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1)
			{
				E = (1 - alpha) * pDoc->Inputimg[Ay][Ax] + alpha * pDoc->Inputimg[By][Bx];
				F = (1 - alpha) * pDoc->Inputimg[Cy][Cx] + alpha * pDoc->Inputimg[Dy][Dx];
				
				pDoc->gResultimg[y][x] = (1 - beta) * E + beta * F;
			}

			else
			{
				E = (1 - alpha) * pDoc->Inputimg[Ay][3 * Ax + 0] + alpha * pDoc->Inputimg[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3 * Cx + 0] + alpha * pDoc->Inputimg[Dy][3 * Dx + 0];
				pDoc->gResultimg[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->Inputimg[Ay][3 * Ax + 1] + alpha * pDoc->Inputimg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3 * Cx + 1] + alpha * pDoc->Inputimg[Dy][3 * Dx + 1];
				pDoc->gResultimg[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->Inputimg[Ay][3 * Ax + 2] + alpha * pDoc->Inputimg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3 * Cx + 2] + alpha * pDoc->Inputimg[Dy][3 * Dx + 2];
				pDoc->gResultimg[y][3 * x + 2] = (1 - beta) * E + beta * F;

			}
			
		}
	Invalidate();
}


void CImageProc20211415View::OnGeometryZoomoutSubsampling()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y, i;
	int xscale = 3;			// 3분의 1로 축소
	int yscale = 2;			// 2분의 1로 축소

	if (pDoc->gResultimg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) / xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) / yscale;

	// 메모리 할당
	pDoc->gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1) {
				pDoc->gResultimg[y][x] = pDoc->Inputimg[y * yscale][x * xscale];
			}
			else
			{
				pDoc->gResultimg[y][3 * x + 0] = pDoc->Inputimg[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultimg[y][3 * x + 1] = pDoc->Inputimg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultimg[y][3 * x + 2] = pDoc->Inputimg[y * yscale][3 * (x * xscale) + 2];
			}
		}
	Invalidate();
}


void CImageProc20211415View::OnGeometryZoomoutMeanSubsampling()
{
	OnRegionSmoothing();		// 영역기반처리의 흐리게 하기
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();		// 축소 서브 샘플링

}


void CImageProc20211415View::OnGeometryZoomoutAvgSampling()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y, i, j;
	int xscale = 3;			// 3분의 1로 축소
	int yscale = 2;			// 2분의 1로 축소
	int sum, rsum, bsum, gsum;
	int src_x, src_y;

	if (pDoc->gResultimg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) / xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) / yscale;

	// 메모리 할당
	pDoc->gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	// 정방향 사상
	for (y = 0; y < pDoc->ImageHeight; y += yscale)
		for (x = 0; x < pDoc->ImageWidth; x += xscale)
		{
			sum = 0; rsum = 0; gsum = 0; bsum = 0;
			for (j = 0; j < yscale; j++)
				for (i = 0; i < xscale; i++)
				{
					src_x = x + i;
					src_y = y + j;
					if (src_x > pDoc->ImageWidth - 1)	src_x = pDoc->ImageWidth - 1;
					if (src_y > pDoc->ImageHeight - 1)	src_y = pDoc->ImageHeight - 1;

					if(pDoc->depth == 1)
						sum += pDoc->Inputimg[src_y][src_x];
					else
					{
						rsum += pDoc->Inputimg[src_y][3 * src_x + 0];
						gsum += pDoc->Inputimg[src_y][3 * src_x + 1];
						bsum += pDoc->Inputimg[src_y][3 * src_x + 2];
					}
				}
			if(pDoc->depth == 1)
				pDoc->gResultimg[y / yscale][x / xscale] = sum / (xscale * yscale);
			else
			{
				pDoc->gResultimg[y / yscale][3 * (x / xscale) + 0] = rsum / (xscale * yscale);
				pDoc->gResultimg[y / yscale][3 * (x / xscale) + 1] = gsum / (xscale * yscale);
				pDoc->gResultimg[y / yscale][3 * (x / xscale) + 2] = bsum / (xscale * yscale);
			}
		}
	Invalidate();
}


#define PI 3.1415926521

void CImageProc20211415View::OnGeometryRotation()
{
	CImageProc20211415Doc* pDoc = GetDocument();
	CAngleInputDialog dlg;

	int x, y, i, j;
	int angle = 30;		// degree 30도
	float radian;
	int Cx, Cy, Oy;
	int xdiff, ydiff;
	int x_source, y_source;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;

	if (pDoc->gResultimg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	radian = 2 * PI / 360 * angle;

	pDoc->gImageWidth = pDoc->ImageHeight * fabs(cos(PI / 2 - radian)) + pDoc->ImageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageHeight * fabs(cos(PI / 2 - radian));

	// 메모리 할당
	pDoc->gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	// 중심점
	Cx = pDoc->ImageWidth / 2; Cy = pDoc->ImageHeight / 2;

	//y의 마지막 좌표
	Oy = pDoc->ImageHeight - 1;
	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for(y =- ydiff; y < pDoc->gImageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = (Oy - y - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Oy - ((Oy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);
			
			if (pDoc->depth == 1) {
					// y_source = Oy - y_source;
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 ||
					y_source < 0 || y_source > pDoc->ImageHeight - 1)
				{
					pDoc->gResultimg[y + ydiff][x + xdiff] = 255;
				}
					
				else {
					pDoc->gResultimg[y + ydiff][x + xdiff] = pDoc->Inputimg[y_source][x_source];
				}
					
			}
			else 
			{
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 ||
					y_source < 0 || y_source > pDoc->ImageHeight - 1)
				{
					pDoc->gResultimg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultimg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultimg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}

				else {
					pDoc->gResultimg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->Inputimg[y_source][3 * x_source + 0];
					pDoc->gResultimg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->Inputimg[y_source][3 * x_source + 1];
					pDoc->gResultimg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->Inputimg[y_source][3 * x_source + 2];
				}
			}
		}
	Invalidate();
}


void CImageProc20211415View::OnGeometryMirror()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) 
			{
				pDoc->Resultimg[y][x] = pDoc->Inputimg[y][pDoc->ImageWidth - 1 - x];
			}
			else
			{
				pDoc->Resultimg[y][3 * x + 0] = pDoc->Inputimg[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
				pDoc->Resultimg[y][3 * x + 1] = pDoc->Inputimg[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
				pDoc->Resultimg[y][3 * x + 2] = pDoc->Inputimg[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
			}
			
		}
	Invalidate();
}


void CImageProc20211415View::OnGrometryFlip()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				pDoc->Resultimg[y][x] = pDoc->Inputimg[pDoc->ImageHeight -1 -y][x];
			}
			else
			{
				pDoc->Resultimg[y][3 * x + 0] = pDoc->Inputimg[pDoc->ImageHeight - 1 - y][3 * x + 0];
				pDoc->Resultimg[y][3 * x + 1] = pDoc->Inputimg[pDoc->ImageHeight - 1 - y][3 * x + 1];
				pDoc->Resultimg[y][3 * x + 2] = pDoc->Inputimg[pDoc->ImageHeight - 1 - y][3 * x + 2];
			}

		}
	Invalidate();
}

typedef struct
{
	int Px, Py;
	int Qx, Qy;
}control_line;

control_line mctrl_source = { 100, 100, 150, 150 };
control_line mctrl_dest = { 100, 100, 200, 200 };

void CImageProc20211415View::OnGeometryWarping()
{
	CImageProc20211415Doc* pDoc = GetDocument();

	control_line source_lines[5] = { {100,100,150,150}, 
		{0,0,pDoc->ImageWidth - 1,0}, {pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1}, 
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1}, {0,pDoc->ImageHeight - 1,0,0} };

	control_line dest_lines[5] = { {100,100,200,200},
		{0,0,pDoc->ImageWidth - 1,0}, {pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1}, {0,pDoc->ImageHeight - 1,0,0} };

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;

	int x, y;
	double u, h, d;
	double tx, ty, xp, yp;
	double weight, totalweight;
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, x2, y1, y2;
	int src_x1, src_x2, src_y1, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5;
	int line;
	int source_x, source_y;
	int last_row, last_col;

	last_row = pDoc->ImageHeight - 1;
	last_col = pDoc->ImageWidth - 1;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			tx = 0.0;
			ty = 0.0;
			totalweight = 0.0;

			//각 제어선의 영향을 계산
			for (line = 0; line < num_lines; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / (double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0)		d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1) d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
				else			d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) - h * (src_x2 - src_x1) / src_line_length;

				weight = pow(pow(dest_line_length, p) / (a + d), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;

				totalweight += weight;
			}
			source_x = x + (tx / totalweight);
			source_y = y + (ty / totalweight);

			if (source_x < 0) source_x = 0;
			else if (source_x > last_col) source_x = last_col;
			if (source_y < 0) source_y = 0;
			else if (source_y > last_row) source_y = last_row;

			if (pDoc->depth == 1) 
			{
				pDoc->Resultimg[y][x] = pDoc->Inputimg[source_y][source_x];
			}
			else
			{
				pDoc->Resultimg[y][3 * x + 0] = pDoc->Inputimg[source_y][3 * source_x + 0];
				pDoc->Resultimg[y][3 * x + 1] = pDoc->Inputimg[source_y][3 * source_x + 1];
				pDoc->Resultimg[y][3 * x + 2] = pDoc->Inputimg[source_y][3 * source_x + 2];
			}
			
		}
	Invalidate();
}

 CPoint mpos_st, mpos_end;

void CImageProc20211415View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CImageProc20211415View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC * pDC = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	pDC->SelectObject(&rpen);

	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);

	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_st.x;
	Ay = mpos_st.y;
	Bx = mpos_end.x;
	By = mpos_end.y;

	if (Ax < Bx) mctrl_source.Px = Ax - (Bx - Ax) / 2;
	else		 mctrl_source.Px = Ax + (Ax - Bx) / 2;

	if (Ay < By) mctrl_source.Py = Ay - (By - Ay) / 2;
	else		 mctrl_source.Py = Ay + (Ay - By) / 2;

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;

	CScrollView::OnLButtonUp(nFlags, point);
}


void CImageProc20211415View::OnAviView()
{
	CFileDialog dlg(true, "", "",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI화일(*.avi)|*.avi|모든화일(*.*)|*.*|");

	if (dlg.DoModal() == IDOK)
	{
		AVIFileName = dlg.GetPathName();
		bAviMode = true;

		Invalidate();
	}
}


void CImageProc20211415View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmpih;
	unsigned char* image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AVIFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++)
	{
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO)
		{
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			for (frame = 0; frame < 100; frame++)
			{
				pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih) continue;

				image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);

				/*
				for(y = 0; y<fi.dwHeight; y++)
					for (x = 0; x < fi.dwWidth; x++)
					{
						pDC->SetPixel(x, fi.dwHeight - 1 - y, RGB(image[(y * fi.dwWidth + x)* 3 + 2],
							image[(y * fi.dwWidth + x) * 3 + 1], image[(y * fi.dwWidth + x) * 3 + 0]));
					}
				*/

				::SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, fi.dwWidth, fi.dwHeight, 0, 0, 0, fi.dwWidth, image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
				Sleep(30);
			}
		}
	}
	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();
}