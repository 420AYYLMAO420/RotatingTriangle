#pragma once

#include "Shader.h"

class PixelShader : public Shader
{
public:
	PixelShader(LPCWSTR Path);
	~PixelShader();

	void SetToPipeline(ID3D11DeviceContext* DeviceContext) override;

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShaderComponent;
};



