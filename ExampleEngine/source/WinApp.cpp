#include "WinApp.h"
#include "WindowsHeader.h"
#include <chrono>
#include <sstream>
#include "Time.h"

WinApp::WinApp(HINSTANCE& hInstance, LPWSTR NewTitle, const UINT& NewPosX, const UINT& NewPosY, const UINT& NewWidth, const UINT& NewHeight)
{
    bQuit = FALSE;
    WindowPanel = std::make_unique<Window>(hInstance, NewTitle, NewPosX, NewPosY, NewWidth, NewHeight);
    GraphicsPanel = std::make_unique<Graphics>(WindowPanel.get());
    OnCreationFinished();
}

WinApp::~WinApp() {

}

WPARAM WinApp::Run()
{
    //Handle messages
    
    while (!bQuit)
    {
        //Handle events 
        bQuit = WindowPanel->HandleEvents();
        //Render graphics
        GraphicsPanel->Render(Timer->GetTimeSinceStart());
    }
    
    return WindowPanel->GetWPARAM();
}

void WinApp::OnCreationFinished()
{
    OutputDebugStringW(L"\nWindow Creation Finished");
    Timer = std::make_unique<Time>();
    Timer->Start();
}
