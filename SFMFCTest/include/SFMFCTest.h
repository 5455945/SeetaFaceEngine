
// SFMFCTest.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#include "../res/resource.h"		// 主符号


// CSFMFCTestApp: 
// 有关此类的实现，请参阅 SFMFCTest.cpp
//

class CSFMFCTestApp : public CWinApp
{
public:
	CSFMFCTestApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CSFMFCTestApp theApp;