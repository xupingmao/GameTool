
// ImageMerger.h : ImageMerger Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CImageMergerApp:
// �йش����ʵ�֣������ ImageMerger.cpp
//

class CImageMergerApp : public CWinApp
{
public:
	CImageMergerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	ULONG_PTR m_gdiPlusToken;

};

extern CImageMergerApp theApp;
