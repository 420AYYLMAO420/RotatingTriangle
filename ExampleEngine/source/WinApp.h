#pragma once

#include "BuildLibrary.h"
#include "Window.h"
#include "Graphics.h"
#include <memory>

class EXAPI WinApp {
public:
	WinApp(HINSTANCE& hInstance, LPWSTR NewTitle = (LPWSTR)L"DefaultTitle", const UINT& NewPosX = CW_USEDEFAULT, const UINT& NewPosY = CW_USEDEFAULT,
		const UINT& NewWidth = CW_USEDEFAULT, const UINT& NewHeight = CW_USEDEFAULT);
	~WinApp();
	WPARAM Run();//main loop
private:
	void OnCreationFinished();//event that fires when the window has been created and shown

	std::unique_ptr<Window> WindowPanel;//pointer to Window class
	std::unique_ptr<Graphics> GraphicsPanel;//pointer to Graphics class
	std::unique_ptr<class Time> Timer;//pointer to Time class
	BOOL bQuit;//boolean that determines if the user quit the program
	WPARAM wParam;//the exit code that Run() will return
};

