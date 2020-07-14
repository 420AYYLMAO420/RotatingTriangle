#include "VertexShader.h"
#include <d3dcompiler.h>
#include <comdef.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "comsuppw.lib")

VertexShader::VertexShader()
{
}

VertexShader::VertexShader(LPCWSTR FilePath)
{
	BindFile(FilePath);
}

VertexShader::~VertexShader()
{
	GetCompiledCode()->Release();
}

void VertexShader::CreateShader(ID3D11Device* Device)
{
	HRESULT hr = Device->CreateVertexShader(GetCompiledCode()->GetBufferPointer(), GetCompiledCode()->GetBufferSize(), NULL, GetVertexShaderComponent().GetAddressOf());
}	

void VertexShader::SetToPipeline(ID3D11DeviceContext* DeviceContext)
{
	DeviceContext->VSSetShader(VertexShaderComponent.Get(), nullptr, NULL);
}

void VertexShader::BindFile(LPCWSTR FilePath)
{
	auto CompiledCode = GetCompiledCode();
	D3DCompileFromFile(FilePath, nullptr, nullptr, "main", "vs_4_0", 0, 0, &CompiledCode, nullptr);
}
