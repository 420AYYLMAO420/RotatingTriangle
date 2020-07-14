#pragma once

#include <d3d11.h>
#include <wrl/client.h>

class Shader {

public:
	Shader();
	~Shader();
	virtual void BindFile(LPCWSTR FilePath) = 0;
	virtual void SetToPipeline(ID3D11DeviceContext* DeviceContext) = 0;
	virtual void CreateShader(ID3D11Device* Device) = 0;
	inline ID3D10Blob* GetCompiledCode() { return CompiledCode; }
	

private:
	ID3D10Blob* CompiledCode;
	
};