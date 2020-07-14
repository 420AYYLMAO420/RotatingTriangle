#include "ExampleEngine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	//create a WinApp object 
	WinApp app(hInstance, (LPWSTR)L"Rotating Triangle", 0, 0, 1280, 720);
	//return exit code
	return (UINT)app.Run();
	
}