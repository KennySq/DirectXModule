#include"pch.h"
#include "Instance.h"



Instance::Instance()
{}


Instance::~Instance()
{}

void Instance::SetMesh(shared_ptr<D3DAModel> pModel)
{
	if (pModel == nullptr)
	{
		debug_logger("This Model is empty.");
		return;
	}
	
	Model = pModel;

	for(auto V : pModel->Meshes)
	{
		VertexBuffers.emplace_back(V->VB.Get());
		IndexBuffers.emplace_back(V->IB.Get());
	}
	
	return;
}

void Instance::DrawMesh(RenderManager* Renderer)
{
	static auto Context = D3DHW::GetAwaitingContext();
	static UINT Strides[] = { sizeof(D3DVERTEX::StandardVertex) };
	static UINT Offsets[] = { 0 };
	static D3D11_BUFFER_DESC IDesc;
	static auto Camera = InstanceScene->GetCamera(0);
	static ID3D11Buffer* BasicBuffers[] = {InstTransform->GetBuffer().Get(), Camera->GetBuffer().Get()};

	auto IL = Materials[0]->RequestInterface<ID3D11InputLayout>();
	auto VS = Materials[0]->RequestInterface<ID3D11VertexShader>();
	auto GS = Materials[0]->RequestInterface<ID3D11GeometryShader>();
	auto HS = Materials[0]->RequestInterface<ID3D11HullShader>();
	auto DS = Materials[0]->RequestInterface<ID3D11DomainShader>();
	auto CS = Materials[0]->RequestInterface<ID3D11ComputeShader>();
	auto PS = Materials[0]->RequestInterface<ID3D11PixelShader>();

	Model->Meshes[0]->IB->GetDesc(&IDesc);

	UINT IndexCount = IDesc.ByteWidth / sizeof(MeshIndex);
	
	Context->IASetVertexBuffers(0, Model->Meshes.size(), VertexBuffers.data(), Strides, Offsets);
#ifdef _INDEX32
	Context->IASetIndexBuffer(IndexBuffers[0], DXGI_FORMAT_R32_UINT, 0);
#else
	Context->IASetIndexBuffer(IndexBuffers[0], DXGI_FORMAT_R16_UINT, 0);
#endif
		
	Context->IASetInputLayout(IL);
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	Context->VSSetShader(VS, nullptr, 0);
	Context->PSSetShader(PS, nullptr, 0);
	//Context->VSSetConstantBuffers(0, 1, Camera->GetBuffer().GetAddressOf());
	Context->VSSetConstantBuffers(0, 2, BasicBuffers);
	Context->DrawIndexed(IndexCount, 0, 0);
	
	Renderer->FlushCommand(Context);
}

void Instance::AddMaterial(shared_ptr<D3DAMaterial> Material)
{
	
	if(Material == nullptr)
		debug_logger((string("This resource is empty! => ")
					  + string(typeid(Material).name())).c_str());

	Materials.emplace_back(Material);
}

void Instance::SetRasterizerState(RenderManager * Renderer, UINT Index)
{
	static auto Context = GetAwaitingContext();
	Context->RSSetState(Renderer->GetRasterizerState(Index));
}
