
// MFCLab5.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMFCLab5App:
// Сведения о реализации этого класса: MFCLab5.cpp
//

class CMFCLab5App : public CWinApp
{
public:
	CMFCLab5App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCLab5App theApp;
