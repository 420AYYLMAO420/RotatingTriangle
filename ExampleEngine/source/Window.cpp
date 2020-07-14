#include "Window.h"

//window procedure used to handle Windows messages
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);
}

Window::Window(HINSTANCE& hInstance, LPWSTR NewTitle, const UINT& NewPosX, const UINT& NewPosY, const UINT& NewWidth, const UINT& NewHeight)
    : Title(NewTitle), PosX(NewPosX), PosY(NewPosY), Width(NewWidth), Height(NewHeight)
{
    //create a struct used to define a window class
    WNDCLASSEXW WindowClass;
    //set struct's member variables to NULL
    SecureZeroMemory(&WindowClass, sizeof(WNDCLASSEX));
    WindowClass.cbSize = sizeof(WNDCLASSEX);           //size of the struct
    WindowClass.style = CS_HREDRAW | CS_VREDRAW;       //redraw window if client region changes
    WindowClass.lpfnWndProc = WindowProc;              //pointer that holds function pointer to window procedure
    WindowClass.hInstance = hInstance;                 //handle to the instance of the program
    WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW); //use the default cursor class
    WindowClass.lpszClassName = L"WindowClass";        //set the name of the window class
    //register the window class using the struct
    RegisterClassExW(&WindowClass);

    //create a rectangle struct using the position and dimension values passed into the constructor
    RECT WindowRect = { (LONG)PosX, (LONG)PosY, (LONG)Width, (LONG)Height };

    //pass struct to receive new values of each member(will be used to define client region)
    //creating the window without the struct can cause stretching because the client region is not taken into consideration
    AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE);

    //create window using the WindowClass struct and the WindowRect struct
    hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, WindowClass.lpszClassName, Title, WS_OVERLAPPEDWINDOW, PosX, PosY,
        WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, nullptr, nullptr, hInstance, nullptr);

    //show the window(window is not shown directly after creation by default)
    Show();
}

void Window::Show()
{
    //show the window as it is
    ShowWindow(hWnd, SW_SHOW);
}

BOOL Window::HandleEvents()
{
    //check if message is in the message queue
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        //translate any virtual key message into WM_CHAR message
        TranslateMessage(&msg);
        //Send the message to the window procedure
        DispatchMessage(&msg);

        //if the WM_QUIT message is invoked, return true
        if (msg.message == WM_QUIT)
            return TRUE;
    }
    return FALSE;
}





