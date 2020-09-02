#include"pch.h"
#include"HLSLCompiler.h"

// 복잡한 내용을 공유하는 쉐이더 컴파일 코드는 .cpp 파일에 모두 넣었습니다.
// 이 모듈에서는 hlsl 모델 5.0 이상을 최소사양으로 지정하고 있습니다
HRESULT CompileVertexShader(const char* Path, const char* Entry, ID3D11VertexShader** OutVS, ID3D11InputLayout** OutIL)
{
	USES_CONVERSION;

#ifdef _DEBUG
	WORD CompileFlag = D3DCOMPILE_DEBUG;
#endif
	HRESULT Result;
	ID3DBlob* VBlob, * ErrBlob;
	ID3D11ShaderReflection* Reflector;

	auto Device = GetDevice();


	Result = D3DCompileFromFile(A2W(Path), nullptr, nullptr, Entry, "vs_5_0", 0, CompileFlag, &VBlob, &ErrBlob);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to compile the .hlsl file.");


	Result = Device->CreateVertexShader(VBlob->GetBufferPointer(), VBlob->GetBufferSize(), nullptr, OutVS);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to create vertex shader.");

	// ID3D11ShaderReflection으로부터 Vertex Shader의 Reflect 데이터를 받아 ID3D11InputLayout 인터페이스 초기화에 사용합니다.
	Result = D3DReflect(VBlob->GetBufferPointer(), 
						VBlob->GetBufferSize(),
						__uuidof(ID3D11ShaderReflection*),
						(void**)&Reflector);
	assert(Result == S_OK);
	if (Result != S_OK)
		debug_logger("Failed to refelct the shader.");

	Result = ReflectShader(VBlob, OutIL, &Reflector);
	assert(Result == S_OK);
	if (Result != S_OK)
		debug_logger("Failed to input layout of the shader.");

	return S_OK;
}

HRESULT CompilePixelShader(const char* Path, const char* Entry, ID3D11PixelShader** OutPS)
{
	USES_CONVERSION;

#ifdef _DEBUG
	WORD CompileFlag = D3DCOMPILE_DEBUG;
#endif
	HRESULT Result;
	ID3DBlob* PBlob, *ErrBlob;
	ID3D11ShaderReflection* Reflector;

	auto Device = GetDevice();

	Result = D3DCompileFromFile(A2W(Path), nullptr, nullptr, Entry, "ps_5_0", 0, CompileFlag, &PBlob, &ErrBlob);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to compile the .hlsl file.");

	Result = Device->CreatePixelShader(PBlob->GetBufferPointer(), PBlob->GetBufferSize(), nullptr, OutPS);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to create pixel shader.");

	return S_OK;
}

// *** Caution! *** (This code is in WIP)
HRESULT CompileGeometryShader(const char* Path, const char* Entry, ID3D11GeometryShader** OutGS)
{
	USES_CONVERSION;

#ifdef _DEBUG
	WORD CompileFlag = D3DCOMPILE_DEBUG;
#endif
	HRESULT Result;
	ID3DBlob* GBlob, * ErrBlob;
	ID3D11ShaderReflection* Reflector;

	auto Device = GetDevice();

	Result = D3DCompileFromFile(A2W(Path), nullptr, nullptr, Entry, "gs_5_0", 0, CompileFlag, &GBlob, &ErrBlob);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to compile the .hlsl file.");

	Result = Device->CreateGeometryShader(GBlob->GetBufferPointer(), GBlob->GetBufferSize(), nullptr, OutGS);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to create geometry shader.");

	return S_OK;
}

HRESULT CompileComputeShader(const char* Path, const char* Entry, ID3D11ComputeShader** OutCS)
{
	USES_CONVERSION;

#ifdef _DEBUG
	WORD CompileFlag = D3DCOMPILE_DEBUG;
#endif
	HRESULT Result;
	ID3DBlob* CBlob, * ErrBlob;
	ID3D11ShaderReflection* Reflector;

	auto Device = GetDevice();

	Result = D3DCompileFromFile(A2W(Path), nullptr, nullptr, Entry, "cs_5_0", 0, CompileFlag, &CBlob, &ErrBlob);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to compile the .hlsl file.");

	Result = Device->CreateComputeShader(CBlob->GetBufferPointer(), CBlob->GetBufferSize(), nullptr, OutCS);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to create compute shader.");

	return S_OK;
}

HRESULT CompileHullShader(const char* Path, const char* Entry, ID3D11HullShader** OutHS)
{
	USES_CONVERSION;

#ifdef _DEBUG
	WORD CompileFlag = D3DCOMPILE_DEBUG;
#endif
	HRESULT Result;
	ID3DBlob* HBlob, * ErrBlob;
	ID3D11ShaderReflection* Reflector;

	auto Device = GetDevice();

	Result = D3DCompileFromFile(A2W(Path), nullptr, nullptr, Entry, "hs_5_0", 0, CompileFlag, &HBlob, &ErrBlob);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to compile the .hlsl file.");

	Result = Device->CreateHullShader(HBlob->GetBufferPointer(), HBlob->GetBufferSize(), nullptr, OutHS);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to create hull shader.");

	return S_OK;
}

HRESULT CompileDomainShader(const char* Path, const char* Entry, ID3D11DomainShader** OutDS)
{
	USES_CONVERSION;

#ifdef _DEBUG
	WORD CompileFlag = D3DCOMPILE_DEBUG;
#endif
	HRESULT Result;
	ID3DBlob* DBlob, * ErrBlob;
	ID3D11ShaderReflection* Reflector;

	auto Device = GetDevice();

	Result = D3DCompileFromFile(A2W(Path), nullptr, nullptr, Entry, "ds_5_0", 0, CompileFlag, &DBlob, &ErrBlob);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to compile the .hlsl file.");

	Result = Device->CreateDomainShader(DBlob->GetBufferPointer(), DBlob->GetBufferSize(), nullptr, OutDS);
	assert(Result == S_OK);

	if (Result != S_OK)
		debug_logger("Failed to create domain shader.");

	return S_OK;
}

HRESULT ReflectShader(ID3DBlob* VBlob, ID3D11InputLayout** pOutInputLayout, ID3D11ShaderReflection** pOutReflection)
{
	HRESULT Result;
	
	auto Device = GetDevice();

	Result = D3DReflect(VBlob->GetBufferPointer(), VBlob->GetBufferSize(), __uuidof(ID3D11ShaderReflection), (void**)pOutReflection);
	assert(Result == S_OK && "Failed to reflect vertex shader.");

	unsigned int ByteOffset = 0;
	D3D11_SHADER_DESC ShaderDesc{};
	vector<D3D11_INPUT_ELEMENT_DESC> InputElements;
	D3D11_SIGNATURE_PARAMETER_DESC SignParam;
	pOutReflection[0]->GetDesc(&ShaderDesc);
	for (int i = 0; i < ShaderDesc.InputParameters; i++)
	{
		pOutReflection[0]->GetInputParameterDesc(i, &SignParam);

		D3D11_INPUT_ELEMENT_DESC Element;

		Element.SemanticName = SignParam.SemanticName;
		Element.SemanticIndex = SignParam.SemanticIndex;
		Element.InputSlot = 0;
		Element.AlignedByteOffset = ByteOffset;
		Element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		Element.InstanceDataStepRate = 0;

		if (SignParam.Mask == 1)
		{
			if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) Element.Format = DXGI_FORMAT_R32_UINT;
			else if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) Element.Format = DXGI_FORMAT_R32_SINT;
			else if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) Element.Format = DXGI_FORMAT_R32_FLOAT;

			ByteOffset += 4;
		}
		else if (SignParam.Mask <= 3)
		{
			if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) Element.Format = DXGI_FORMAT_R32G32_UINT;
			else if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) Element.Format = DXGI_FORMAT_R32G32_SINT;
			else if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) Element.Format = DXGI_FORMAT_R32G32_FLOAT;
			ByteOffset += 8;
		}
		else if (SignParam.Mask <= 7)
		{
			if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) Element.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) Element.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) Element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			ByteOffset += 12;
		}

		else if (SignParam.Mask <= 15)
		{
			if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) Element.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) Element.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (SignParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) Element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			ByteOffset += 16;
		}


		InputElements.push_back(Element);
	}

	Result = Device->CreateInputLayout(InputElements.data(), InputElements.size(), VBlob->GetBufferPointer(), VBlob->GetBufferSize(), pOutInputLayout);
	assert(Result == S_OK && "Failed to create a input layout.");

	return S_OK;
}

HRESULT CompilePass(const char* Path, const char* Pass, int Flag, shared_ptr<D3DAMaterial> Material)
{
	auto VS = Material->RequestAddressOfInterface<ID3D11VertexShader>();
	auto PS = Material->RequestAddressOfInterface<ID3D11PixelShader>();
	auto GS = Material->RequestAddressOfInterface<ID3D11GeometryShader>();
	auto CS = Material->RequestAddressOfInterface<ID3D11ComputeShader>();
	auto HS = Material->RequestAddressOfInterface<ID3D11HullShader>();
	auto DS = Material->RequestAddressOfInterface<ID3D11DomainShader>();
	auto IL = Material->RequestAddressOfInterface<ID3D11InputLayout>();

	string PassName = Pass;

	if(Flag & PASSTYPE::VER)
		CompileVertexShader(Path, (PassName + "VS").c_str(), VS, IL);

	if(Flag & PASSTYPE::PIX)
		CompilePixelShader(Path, (PassName + "PS").c_str(), PS);
	
	if(Flag & PASSTYPE::GEO)
		CompileGeometryShader(Path, (PassName + "GS").c_str(), GS);

	if (Flag & PASSTYPE::COM)
		CompileComputeShader(Path, (PassName + "CS").c_str(), CS);

	if (Flag & PASSTYPE::HUL)
		CompileHullShader(Path, (PassName + "HS").c_str(), HS);

	if (Flag & PASSTYPE::DOM)
		CompileDomainShader(Path, (PassName + "DS").c_str(), DS);

	return S_OK;
}
