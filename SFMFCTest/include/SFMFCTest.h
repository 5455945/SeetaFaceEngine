
// SFMFCTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include "../res/resource.h"		// ������


// CSFMFCTestApp: 
// �йش����ʵ�֣������ SFMFCTest.cpp
//

class CSFMFCTestApp : public CWinApp
{
public:
	CSFMFCTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSFMFCTestApp theApp;