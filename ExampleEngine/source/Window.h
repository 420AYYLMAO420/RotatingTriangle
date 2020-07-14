#pragma once

#include "WindowsHeader.h"

class Window {
public:
	Window(HINSTANCE& hInstance, LPWSTR NewTitle = (LPWSTR)L"DefaultTitle", const UINT& NewPosX = CW_USEDEFAULT, const UINT& NewPosY = CW_USEDEFAULT,
		const UINT& NewWidth = CW_USEDEFAULT, const UINT& NewHeight = CW_USEDEFAULT);
	Window(Window& window) = delete;

public:
	void Show();//show the window after creation
	BOOL HandleEvents();//handle Windows messages 

	//getters
	inline LPWSTR GetTitle() const { return Title; }
	inline UINT GetPosX() const { return PosX; }
	inline UINT GetPosY() const { return PosY; }
	inline UINT GetWidth() const { return Width; }
	inline UINT GetHeight() const { return Height; }
	inline HWND GetHWND() const { return hWnd; }
	inline WPARAM GetWPARAM() const { return msg.wParam; }

	//setters
	inline void SetTitle(const LPWSTR NewTitle) { Title = NewTitle; }
	inline void SetPosX(const UINT& NewPosX) { PosX = NewPosX; }
	inline void SetPosY(const UINT& NewPosY) { PosY = NewPosY; }
	inline void SetWidth(const UINT& NewWidth) { Width = NewWidth; }
	inline void SetHeight(const UINT& NewHeight) { Height = NewHeight; }


private:
	LPWSTR Title;//title of the window(appears on the non-client region)
	UINT PosX, PosY;//position of where to place the window on the screen(from the top left corner)
	UINT Width, Height;//dimensions of the window
	HWND hWnd;//handle to the window
	MSG msg;//struct that holds message info
};