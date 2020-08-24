#pragma once

// 패스가 가지는 쉐이더 속성을 비트 마스킹으로 관리합니다.
// 이러한 관리를 이용하여 멀티패스 렌더링의 작업을 보다 수월하게 관리 할 수 있습니다.
enum PASSTYPE
{
	VER = 1,
	PIX = 2,
	GEO = 4,
	COM = 8,
	HUL = 16,
	DOM = 32,
};

HRESULT CompileVertexShader(const char* Path, const char* Entry, ID3D11VertexShader** OutVS, ID3D11InputLayout** OutIL);
HRESULT CompilePixelShader(const char* Path, const char* Entry, ID3D11PixelShader** OutPS);
HRESULT CompileGeometryShader(const char* Path, const char* Entry, ID3D11GeometryShader** OutGS);
HRESULT CompileComputeShader(const char* Path, const char* Entry, ID3D11ComputeShader** OutCS);
HRESULT CompileHullShader(const char* Path, const char* Entry, ID3D11HullShader** OutHS);
HRESULT CompileDomainShader(const char* Path, const char* Entry, ID3D11DomainShader** OutDS);

HRESULT ReflectShader(ID3DBlob* VBlob, ID3D11InputLayout** pOutInputLayout, ID3D11ShaderReflection** pOutReflection);

HRESULT CompilePass(const char* Path, const char* Pass, int Flag, shared_ptr<D3DAMaterial> Material);