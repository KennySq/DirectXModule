#pragma once
using namespace std;
using namespace D3DARS;
using namespace D3DVERTEX;
using namespace D3DHW;
namespace D3DRS
{
	class D3DRSBuffer
	{
	public:
		template<typename _VertTy>
		static std::shared_ptr<D3DAMeshBuffer>
			CreateConstantMeshBuffer(shared_ptr<D3DAMesh<StandardVertex>> Mesh)
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
	
		template<typename _Ty>
		static std::shared_ptr<D3DAConstBuffer>
			CreateConstantBuffer(_Ty& InitialData)
		{
			HRESULT Result;
			ID3D11Device* Device = D3DHW::GetDevice();
			shared_ptr<D3DAConstBuffer> buffer = make_shared<D3DAConstBuffer>();

			D3D11_BUFFER_DESC desc{};

			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(_Ty);

			Result = Device->CreateBuffer(&desc, nullptr, buffer->CB.GetAddressOf());
			resource_assert(buffer->CB.Get());
			return buffer;
		}

	};

}

