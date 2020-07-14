#include "PixelShader.h"
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")


PixelShader::PixelShader(LPCWSTR CompiledShaderObjectPath) {
	//D3DReadFileToBlob(CompiledShaderObjectPath, GetCompiledCode().GetAddressOf());
}

PixelShader::~PixelShader() {

}

void PixelShader::SetToPipeline(ID3D11DeviceContext* DeviceContext) {
	DeviceContext->PSSetShader(PixelShaderComponent.Get(), nullptr, NULL);
}

