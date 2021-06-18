
// shapeDraw.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CshapeDrawApp:
// Сведения о реализации этого класса: shapeDraw.cpp
//

class CshapeDrawApp : public CWinApp
{
public:
	CshapeDrawApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CshapeDrawApp theApp;
