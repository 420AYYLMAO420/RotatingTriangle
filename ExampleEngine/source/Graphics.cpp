#include "Graphics.h"
#include <d3dcompiler.h>
#include <cmath>
#include <iterator>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")

// Struct that defines each vertex
struct VERTEX { 
    FLOAT X, Y, Z; 
    FLOAT R, G, B, A; 
};

//Array of Vertices 
const VERTEX Vertices[] =
{
    {0.f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
    {0.5f, -.5f, 0.f, 0.0f, 1.0f, 0.0f, 1.0f},
    {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
    {-.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
    {0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}
};

//Array of indices pointing to vertices
const unsigned short Indices[] = {
    0, 1, 2,
};

Graphics::Graphics(Window* window)
{
    //Describes swap chain 
    DXGI_SWAP_CHAIN_DESC SwapChainDesc;
    //initialize struct's members to NULL
    SecureZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
    // fill the swap chain description struct
    SwapChainDesc.BufferCount = 1;                                   // 1 back buffer for double buffering
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // uses 32-bit color
    SwapChainDesc.BufferDesc.Width = window->GetWidth();             // set the back buffer width equal to the window width
    SwapChainDesc.BufferDesc.Height = window->GetHeight();           // set the back buffer height equal to the window height
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // uses a resource as render target
    SwapChainDesc.OutputWindow = window->GetHWND();                  // uses the current window to output
    SwapChainDesc.SampleDesc.Count = 4;                              // how many multisamples per pixel(used for MSAA)
    SwapChainDesc.Windowed = TRUE;                                   // the window is windowed(not full-screen)
    SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow toggling between windowed and full-screen 

    // pass in swapchan description to create device, device context, and swap chain
    D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
        D3D11_SDK_VERSION, &SwapChainDesc, SwapChain.GetAddressOf(), Device.GetAddressOf(), NULL, DeviceContext.GetAddressOf());

    // create 2D texture 
    ID3D11Texture2D* pBackBuffer;
    //get pointer to back buffer to initialize pBackBuffer
    SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use texture to create back buffer object
    Device->CreateRenderTargetView(pBackBuffer, NULL, BackBuffer.GetAddressOf());
    pBackBuffer->Release();

    // set current render target as the back buffer object
    DeviceContext->OMSetRenderTargets(1, BackBuffer.GetAddressOf(), NULL);

    //create viewport struct
    D3D11_VIEWPORT Viewport;
    //initialize struct's members to NULL
    SecureZeroMemory(&Viewport, sizeof(D3D11_VIEWPORT));
    Viewport.TopLeftX = 0;                        //draw from the x-coordinate 0 on the screen
    Viewport.TopLeftY = 0;                        //draw from the y-coordinate 0 on the screen
    Viewport.Width = (FLOAT)window->GetWidth();   //draw all the way from left to right of the screen
    Viewport.Height = (FLOAT)window->GetHeight(); //draw all the way from top to bottom of the screen

    //set current viewport as viewport struct
    DeviceContext->RSSetViewports(1, &Viewport);

    //create memory objects to hold compiled code of shaders
    ID3D10Blob* VS, * PS;
    //compile vertex shader code and place it in the VS memory object
    D3DCompileFromFile(L"shaders\\VertexShader.hlsl", nullptr, nullptr, "main", "vs_4_0", 0, 0, &VS, nullptr);
    //compile pixel shader code and place it in the PS memory object
    D3DCompileFromFile(L"shaders\\PixelShader.hlsl", nullptr, nullptr, "main", "ps_4_0", 0, 0, &PS, nullptr);

    //create a vertex shader object using the VS memory object
    Device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, VertexShader.GetAddressOf());
    //create a pixel shader object using the PS memory object
    Device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, PixelShader.GetAddressOf());

    //set current vertex shader to vertex shader object
    DeviceContext->VSSetShader(VertexShader.Get(), 0, 0);
    // set current pixel shader to pixel shader object
    DeviceContext->PSSetShader(PixelShader.Get(), 0, 0);

    //Array of input element descriptions
    D3D11_INPUT_ELEMENT_DESC InputElements[] =
    {
        //defines position element which holds 3 floats and is the first input element to be used
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        //defines color element which holds 4 floats and is the second input element to be used
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    //creates an input layout object using the array of input elements(uses vertex shader to validate the array)
    Device->CreateInputLayout(InputElements, (UINT)std::size(InputElements), VS->GetBufferPointer(), VS->GetBufferSize(), InputLayout.GetAddressOf());
    //set current input layout as the input layout object
    DeviceContext->IASetInputLayout(InputLayout.Get());

    //free memory from the memory objects(no longer being used)
    VS->Release();
    PS->Release();

    //fill the vertex buffer description struct
    D3D11_BUFFER_DESC VertexBufferDesc;
    //initialize struct's members to NULL
    SecureZeroMemory(&VertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
    VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;                                 //CPU will write to buffer and GPU will read from it
    VertexBufferDesc.ByteWidth = (UINT)sizeof(VERTEX) * (UINT)std::size(Vertices);//size of the buffer is the size of the Vertices array
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;                        //use as a vertex buffer
    VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;                     //allow CPU to write in the buffer
    //create the vertex buffer object using the description struct
    Device->CreateBuffer(&VertexBufferDesc, NULL, VertexBuffer.GetAddressOf());   

    //create a struct for mapping the vertex buffer
    D3D11_MAPPED_SUBRESOURCE MappedVertices;
    //map the buffer using the struct(shuts GPU access off)
    DeviceContext->Map(VertexBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MappedVertices);   
    //copy the data from the CPU to the GPU(GPU cannot interfere with the copying because it is mapped)
    memcpy(MappedVertices.pData, Vertices, sizeof(Vertices));  
    //unmap the buffer so that the GPU can have access to it again
    DeviceContext->Unmap(VertexBuffer.Get(), NULL);                                      

    //create variable to hold how many bytes each vertex is
    UINT stride = sizeof(VERTEX);
    //create variable to let D3D know that there is nothing between the start of the buffer to the first element that will be used
    UINT offset = 0;
    //set the current vertex buffer to the vertex buffer object using the stride and offset variables
    DeviceContext->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &stride, &offset);
    //set the way how each vertex is supposed to behave(how they connect)
    DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //fill the index buffer description struct
    D3D11_BUFFER_DESC IndexBufferDesc;
    //initialize struct's members to NULL
    SecureZeroMemory(&IndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;                          //use as an index buffer
    IndexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;                                  //CPU will write to buffer and GPU will read from it
    IndexBufferDesc.ByteWidth = sizeof(unsigned short) * (UINT)std::size(Indices);//size of the buffer is the size of the Indices array
    IndexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;                      //allow CPU to write in the buffer
    //create the index buffer object using the description struct
    Device->CreateBuffer(&IndexBufferDesc, NULL, IndexBuffer.GetAddressOf());

    //create a struct for mapping the index buffer
    D3D11_MAPPED_SUBRESOURCE MappedIndices;
    //map the buffer using the struct(shuts GPU access off)
    DeviceContext->Map(IndexBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MappedIndices);    
    //copy the data from the CPU to the GPU(GPU cannot interfere with the copying because it is mapped)
    memcpy(MappedIndices.pData, Indices, sizeof(Indices));  
    //unmap the buffer so that the GPU can have access to it again
    DeviceContext->Unmap(IndexBuffer.Get(), NULL);                                      

    //set the index buffer object to the input assembly stage using the stride and offset variables
    DeviceContext->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

void Graphics::Render(float angle)
{
    //color array used for clearing back buffer
    const float color[] = {
        std::cos(angle), //R
        std::sin(angle), //G
        -std::cos(angle),//B
        1.f              //A
    };

    //yaw rotation matrix 
    const float Constants[] = {
        std::cos(angle), std::sin(angle), 0.f, 0.f,
        -std::sin(angle), std::cos(angle), 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };

    //declare constant buffer object
    Microsoft::WRL::ComPtr <ID3D11Buffer> ConstantBuffer;

    //describes constant buffer
    D3D11_BUFFER_DESC ConstantBufferDesc;
    ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;  //use as a constant buffer
    ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;             //CPU can only write to buffer while GPU can only read from buffer
    ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPU is allowed to write to buffer
    ConstantBufferDesc.MiscFlags = 0u;                          //optional flags not needed
    ConstantBufferDesc.ByteWidth = sizeof(Constants);           //set size of buffer to size of Constants array
    ConstantBufferDesc.StructureByteStride = 0u;                //buffer is not structured so stride is not needed

    //struct that stores the constants data
    D3D11_SUBRESOURCE_DATA InitialConstants;
    InitialConstants.pSysMem = Constants;     //point to the Constants array for initializing buffer
    InitialConstants.SysMemPitch = 0;         //not using 2D or 3D texture data
    InitialConstants.SysMemSlicePitch = 0;    //not using 3D texture data
    //create the constant buffer using the subresource struct for initialization
    Device->CreateBuffer(&ConstantBufferDesc, &InitialConstants, ConstantBuffer.GetAddressOf());
    //set constant buffer object to the vertex shader stage
    DeviceContext->VSSetConstantBuffers(0, 1, ConstantBuffer.GetAddressOf());

    //clear backbuffer using the color array
    DeviceContext->ClearRenderTargetView(BackBuffer.Get(), color);
    //draw to the screen using indices
    DeviceContext->DrawIndexed((UINT)std::size(Indices), 0, 0);
    //swap front and back buffers
    SwapChain->Present(0, 0);
}

Graphics::~Graphics()
{
    //before closing the window, it must be in windowed mode(if full-screen, set window to windowed mode)
    SwapChain->SetFullscreenState(FALSE, NULL);    
}