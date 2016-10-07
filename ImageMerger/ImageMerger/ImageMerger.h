
// ImageMerger.h : ImageMerger 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CImageMergerApp:
// 有关此类的实现，请参阅 ImageMerger.cpp
//

class CImageMergerApp : public CWinApp
{
public:
	CImageMergerApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	ULONG_PTR m_gdiPlusToken;

};

extern CImageMergerApp theApp;
