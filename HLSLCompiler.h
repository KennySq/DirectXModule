#pragma once

// �н��� ������ ���̴� �Ӽ��� ��Ʈ ����ŷ���� �����մϴ�.
// �̷��� ������ �̿��Ͽ� ��Ƽ�н� �������� �۾��� ���� �����ϰ� ���� �� �� �ֽ��ϴ�.
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