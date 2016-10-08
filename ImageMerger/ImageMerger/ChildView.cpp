
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "ImageMerger.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{

}

CChildView::~CChildView()
{
	for (auto iter = imageVector.begin(); iter != imageVector.end(); iter++)
	{
		delete *iter; // 释放image
	}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_32771, &CChildView::OnAddImage)
	ON_COMMAND(ID_32772, &CChildView::OnSaveImage)
	ON_WM_CREATE()

	ON_BN_CLICKED(IDC_ADD_BTN, &CChildView::OnAddImage)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CChildView::OnSaveImage)
	ON_BN_CLICKED(IDC_REMOVE_BTN, &CChildView::OnRemoveImage)

END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);
	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	//CButton btn;
	//CString btnText("Hello");
	//btn.SetWindowTextW(btnText);
	// TODO: 在此处添加消息处理程序代码
	RePaintAll();
	// 不要为绘制消息而调用 CWnd::OnPaint()
}


void CChildView::RePaintAll()
{
	Gdiplus::Graphics graphics(this->GetDC()->GetSafeHdc());

	this->width = 0;

	for (auto iter = imageVector.begin(); iter != imageVector.end(); iter++)
	{
		Gdiplus::Image* img = *iter;

		if (img == nullptr)
		{
			continue;
		}

		int x, y, width, height;
		x = this->width;
		y = 0;

		width = img->GetWidth();
		height = img->GetHeight();

		graphics.DrawImage(img, x, y + m_startY, width, height);

		this->width += width;
		this->height = max(height, this->height);
	}
}

void CChildView::OnAddImage()
{
	// TODO: 在此添加命令处理程序代码

	CFileDialog dialog(true, _T("BMP"), _T("*.BMP"));

	if (dialog.DoModal())
	{
		CString pathName = dialog.GetPathName();

		Gdiplus::Image* img = Gdiplus::Image::FromFile(pathName);
		if (img != NULL)
		{
			imageVector.push_back(img);
			RePaintAll();
		}
	}

}

void CChildView::OnRemoveImage()
{
	if (imageVector.size() > 0) {
		imageVector.pop_back();
	}

	Gdiplus::Graphics graphics(this->GetDC()->GetSafeHdc());
	graphics.Clear(Gdiplus::Color::White); // 先清空绘图区域
	// RePaintAll();
	RedrawWindow();
}

/**
@name    GetEncoderClsid
@brief   取图片类型GLSID
@param[in]        const WCHAR * format
@param[in]        CLSID * pClsid
@return           int
来源 http://blog.csdn.net/friendan/article/details/42168981
这并不是一个微软的内置函数
*/

int CChildView::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	using namespace Gdiplus;
	UINT  num = 0;
	UINT  size = 0;
	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return -1;
}

void CChildView::OnSaveImage()
{
	// TODO: 在此添加命令处理程序代码

	if (imageVector.size() == 0) {
		return;
	}

	Gdiplus::Graphics graphics(this->GetDC()->GetSafeHdc());
	CImage cImage;
	cImage.Create(width, height, 24);
	BitBlt(cImage.GetDC(), 0, 0, width, height, this->GetDC()->GetSafeHdc(), 0, m_startY, SRCCOPY);

	cImage.ReleaseDC();

	COleStreamFile cImgStream;
	cImgStream.CreateMemoryStream(NULL);
	cImage.Save(cImgStream.GetStream(), Gdiplus::ImageFormatBMP);
	
	Gdiplus::Image image(cImgStream.GetStream());
	cImgStream.Close();

	CLSID clsid;
	GetEncoderClsid(L"image/png", &clsid);
	image.Save(_T("./join.png"), &clsid);

	AfxMessageBox(_T("保存成功!"));
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	m_addBtn.Create(_T("打开文件"),                       //按钮标题
		WS_CHILD | WS_VISIBLE | WS_BORDER,//按钮风格
		CRect(40, 10, 200, 60),            //按钮大小
		this,                          //按钮父指针
		IDC_ADD_BTN);
	m_addBtn.ShowWindow(SW_SHOWNORMAL);

	m_saveBtn.Create(_T("保存文件"),                       //按钮标题
		WS_CHILD | WS_VISIBLE | WS_BORDER,//按钮风格
		CRect(220, 10, 380, 60),            //按钮大小
		this,                          //按钮父指针
		IDC_SAVE_BTN);
	m_saveBtn.ShowWindow(SW_SHOWNORMAL);

	m_removeBtn.Create(_T("移除最后一个文件"),                       //按钮标题
		WS_CHILD | WS_VISIBLE | WS_BORDER,//按钮风格
		CRect(400, 10, 560, 60),            //按钮大小
		this,                          //按钮父指针
		IDC_REMOVE_BTN);
	m_removeBtn.ShowWindow(SW_SHOWNORMAL);

	m_startY = 70;

	return 0;
}
