#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include "Window.h"

namespace wrl = Microsoft::WRL;

class Graphics {

public:

	Graphics(Window* window);
	~Graphics();

	void Render(float angle);//will be called from the main loop

private:
	wrl::ComPtr<IDXGISwapChain> SwapChain;//series of buffers
	wrl::ComPtr<ID3D11Device> Device;//use to create resources
	wrl::ComPtr<ID3D11DeviceContext> DeviceContext;//set resources to the graphics pipeline(also issue draw calls)
	wrl::ComPtr<ID3D11RenderTargetView> BackBuffer;//render target view object that acts as the back buffer
	wrl::ComPtr<ID3D11InputLayout> InputLayout;//layout of each vertex
	wrl::ComPtr<ID3D11VertexShader> VertexShader;//vertex shader object
	wrl::ComPtr<ID3D11PixelShader> PixelShader;//pixel shader object
	wrl::ComPtr<ID3D11Buffer> VertexBuffer;//vertex buffer object
	wrl::ComPtr<ID3D11Buffer> IndexBuffer;//index buffer object
};
