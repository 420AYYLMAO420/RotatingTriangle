#pragma once

#include "Shader.h"
#include <d3d11.h>
#include <wrl/client.h>

class VertexShader : public Shader {
public:
	VertexShader();
	VertexShader(LPCWSTR FilePath);
	~VertexShader();
	void CreateShader(ID3D11Device* Device);
	void SetToPipeline(ID3D11DeviceContext* DeviceContext);
	void BindFile(LPCWSTR FilePath);
	inline Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVertexShaderComponent() const { return VertexShaderComponent; }
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShaderComponent;

};

