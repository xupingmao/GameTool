
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include <vector>

using namespace std;
// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddImage();

	void RePaintAll();

private:
	vector<Gdiplus::Image*> imageVector;

	int width = 0;
	int height = 0;

public:
	afx_msg void OnSaveImage();
	int CChildView::GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
};
