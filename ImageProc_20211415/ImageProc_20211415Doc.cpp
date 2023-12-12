
// ImageProc_20211415Doc.cpp: CImageProc20211415Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20211415.h"
#endif

#include "ImageProc_20211415Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CAngleInputDialog.h"

// CImageProc20211415Doc

IMPLEMENT_DYNCREATE(CImageProc20211415Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProc20211415Doc, CDocument)
END_MESSAGE_MAP()


// CImageProc20211415Doc 생성/소멸

CImageProc20211415Doc::CImageProc20211415Doc() noexcept
{
	Inputimg = NULL;
	Inputimg2 = NULL;
	Resultimg = NULL;

	gResultimg = NULL;

}

CImageProc20211415Doc::~CImageProc20211415Doc()
{
	int i;

	if (Inputimg != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(Inputimg[i]);
		free(Inputimg);
	}

	if (Inputimg2 != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(Inputimg2[i]);
		free(Inputimg2);
	}

	if (Resultimg != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(Resultimg[i]);
		free(Resultimg);
	}

	if (gResultimg != NULL)
	{
		for (i = 0; i < gImageHeight; i++)
			free(gResultimg[i]);
		free(gResultimg);
	}
}

BOOL CImageProc20211415Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProc20211415Doc serialization

void CImageProc20211415Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{

		LoadImageFile(ar);
		/* CFile* fp = ar.GetFile();
		if (fp->GetLength() == 256 * 256) ar.Read(Inputimg, 256 * 256);
		else AfxMessageBox("256x256 크기의 화일만 사용 가능합니다.");
		*/

	}
}

void CImageProc20211415Doc::LoadTwoImages(void)
{
	CFile file;						// CFile 객체 선언
	CFileDialog dlg(TRUE);			// 파일 선택 대화상자 객체 선언

	AfxMessageBox("Select the First Image");
	
	if (dlg.DoModal() == IDOK) {		// 파일 선택 대화상자 실행
		file.Open(dlg.GetPathName(), CFile::modeRead);		// 파일 열기
		CArchive ar(&file, CArchive::load);
		LoadSecondImageFile(ar);
		file.Close();		// 파일 닫기
	}
}


#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProc20211415Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProc20211415Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProc20211415Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProc20211415Doc 진단

#ifdef _DEBUG
void CImageProc20211415Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProc20211415Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProc20211415Doc 명령



void CImageProc20211415Doc::LoadImageFile(CArchive& ar)
{
	int i, maxValue;
	char type[16], buf[256];

	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;
	// 파일의 헤더 읽기 
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".PGM") == 0 || strcmp(strrchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);
		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0) {
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp 화일임을 나타내는 "BM"마커가 있는 지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) return;

		// bitmap info header읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih)); 
		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		if (depth == 1)
		{	//palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{

		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}
		Inputimg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
		Resultimg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
		for (i = 0; i < ImageHeight; i++) {
			Inputimg[i] = (unsigned char*)malloc(ImageWidth * depth);
			Resultimg[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

		if (!isbmp) {
			// 영상 데이터 읽기 
					for (i = 0; i < ImageHeight; i++)
						ar.Read(Inputimg[i], ImageWidth * depth);
		}
		else 
		{
			// 파일에서 읽어서 저장
			BYTE nu[4];
			int widthfile;
			widthfile = (ImageWidth * 3 * 8 + 31) / 32 * 4;
			for (i = 0; i < ImageHeight; i++)
			{
				if (depth == 1)
					ar.Read(Inputimg[ImageHeight - 1 - i], ImageWidth * depth);

				else
				{
					//BGR -> RGB
					BYTE r, g, b;
					for (int j = 0; j < ImageWidth; j++)
					{
						ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);
						Inputimg[ImageHeight - 1 - i][3 * j + 0] = r;
						Inputimg[ImageHeight - 1 - i][3 * j + 1] = g;
						Inputimg[ImageHeight - 1 - i][3 * j + 2] = b;
					}
				}

				if ((widthfile - ImageWidth * depth) != 0)
					ar.Read(nu, (widthfile - ImageWidth * depth));
			}
			
		}
		return;
}

void CImageProc20211415Doc::LoadSecondImageFile(CArchive& ar)
{
	int w, h, d;
	int maxValue, i;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), "pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &w, &h);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)		d = 1;
		else                                d = 3;
	}
	

	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0) {
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp 화일임을 나타내는 "BM"마커가 있는 지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) return;

		// bitmap info header읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		w = bih.biWidth;
		h = bih.biHeight;
		d = bih.biBitCount / 8;

		if (depth == 1)
		{	//palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		w = 256;
		h = 256;
		d = 1;
	}
	if (ImageWidth != w || ImageHeight != h || depth != d)
	{
		AfxMessageBox("가로, 세로, 색상수가 같아야만 처리할 수 있습니다.");
		return;
	}

	Inputimg2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < ImageHeight; i++)
	{
		Inputimg2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	if (!isbmp) {
		// 영상 데이터 읽기 
		for (i = 0; i < ImageHeight; i++)
			ar.Read(Inputimg2[i], ImageWidth * depth);
	}
	else
	{
		// 파일에서 읽어서 저장
		BYTE nu[4];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;
		for (i = 0; i < ImageHeight; i++)
		{
			if (depth == 1)
				ar.Read(Inputimg2[ImageHeight - 1 - i], ImageWidth * depth);

			else
			{
				//BGR -> RGB
				BYTE r, g, b;
				for (int j = 0; j < ImageWidth; j++)
				{
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);
					Inputimg2[ImageHeight - 1 - i][3 * j + 0] = r;
					Inputimg2[ImageHeight - 1 - i][3 * j + 1] = g;
					Inputimg2[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0)
				ar.Read(nu, (widthfile - ImageWidth) * depth);
		}

	}

	return;
}


void CImageProc20211415Doc::PixelTwoImageAdd(void)
{
	int value = 0;

	LoadTwoImages();

	for (int y = 0; y < ImageHeight; y++)
		for (int x = 0; x < ImageWidth * depth; x++) {
			value = Inputimg[y][x] + Inputimg2[y][x];
			if (value > 256) Resultimg[y][x] = 256;
			else Resultimg[y][x] = value;
		}

}