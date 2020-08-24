#include"pch.h"
#include "Buffer.h"

template<typename _VertTy>
inline shared_ptr<D3DAMeshBuffer> D3DRS::Buffer::CreateConstantMeshBuffer(shared_ptr<D3DARS::D3DAMesh<D3DVERTEX::StandardVertex>> Mesh)
{
	shared_ptr<D3DAMeshBuffer> BufferInst = make_shared<D3DAMeshBuffer>();
	ID3D11Device* Device = GetDevice();

	D3D11_BUFFER_DESC Desc{};
	D3D11_SUBRESOURCE_DATA SubData{};
	Desc.ByteWidth = sizeof(_VertTy) * Mesh->Vertices.size();
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	
	SubData.pSysMem = Mesh->Vertices.data();

	Device->CreateBuffer(&Desc, &SubData, BufferInst->VB.GetAddressOf());
	resource_assert(BufferInst->VB.Get());

	ZeroMemory(&Desc, sizeof(Desc));

	Desc.ByteWidth = sizeof(MeshIndex) * Mesh->Indices.size();
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	
	SubData.pSysMem = Mesh->Indices.data();

	Device->CreateBuffer(&Desc, &SubData, BufferInst->IB.GetAddressOf());
	resource_assert(BufferInst->IB.Get());

	return BufferInst;
}