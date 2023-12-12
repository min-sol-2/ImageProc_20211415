
// ImageProc_20211415Doc.h: CImageProc20211415Doc 클래스의 인터페이스
//


#pragma once


class CImageProc20211415Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProc20211415Doc() noexcept;
	DECLARE_DYNCREATE(CImageProc20211415Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void LoadTwoImages(void);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProc20211415Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// 입력 이미지
	unsigned char** Inputimg;
	unsigned char** Inputimg2;
	// 출력 이미지
	unsigned char** Resultimg;

	int ImageWidth;
	int ImageHeight;
	int depth; // 1 = 흑백, 3 = 칼라

	int gImageWidth;
	int gImageHeight;
	unsigned char** gResultimg;

	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
	void PixelTwoImageAdd();
};
