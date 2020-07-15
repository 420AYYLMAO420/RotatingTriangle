#include "WinApp.h"
#include "Window.h"
#include "Graphics.h"
#include "Time.h"


WinApp::WinApp(HINSTANCE& hInstance, LPWSTR NewTitle, const UINT& NewPosX, const UINT& NewPosY, const UINT& NewWidth, const UINT& NewHeight)
{
    bQuit = FALSE;
    WindowPanel = new Window(hInstance, NewTitle, NewPosX, NewPosY, NewWidth, NewHeight);
    GraphicsPanel = new Graphics(WindowPanel);
    OnCreationFinished();
}

WinApp::~WinApp() {
    delete WindowPanel, GraphicsPanel, Timer;
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
    Timer = new Time();
    Timer->Start();
}
