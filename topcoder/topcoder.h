
// topcoder.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtopcoderApp:
// �йش����ʵ�֣������ topcoder.cpp
//

class CtopcoderApp : public CWinApp
{
public:
	CtopcoderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtopcoderApp theApp;