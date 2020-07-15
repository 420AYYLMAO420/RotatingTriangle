#pragma once

#include "WindowsHeader.h"
#include "BuildLibrary.h"
#include <memory>

class EXAPI WinApp {
public:
	WinApp(HINSTANCE& hInstance, LPWSTR NewTitle = (LPWSTR)L"DefaultTitle", const UINT& NewPosX = CW_USEDEFAULT, const UINT& NewPosY = CW_USEDEFAULT,
		const UINT& NewWidth = CW_USEDEFAULT, const UINT& NewHeight = CW_USEDEFAULT);
	~WinApp();
	WPARAM Run();//main loop
private:
	void OnCreationFinished();//event that fires when the window has been created and shown

	class Window* WindowPanel;//pointer to Window class
	class Graphics* GraphicsPanel;//pointer to Graphics class
	class Time* Timer;//pointer to Time class
	BOOL bQuit;//boolean that determines if the user quit the program
	WPARAM wParam;//the exit code that Run() will return
};

