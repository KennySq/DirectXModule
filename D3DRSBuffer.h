#pragma once
using namespace std;
namespace D3DRS
{
	class D3DRSBuffer
	{
	public:
		template<typename _VertTy>
		static std::shared_ptr<D3DAMeshBuffer>
			CreateConstantMeshBuffer(shared_ptr<D3DARS::D3DAMesh<D3DVERTEX::StandardVertex>> Mesh);
	
		template<typename _Ty>
		static std::shared_ptr<D3DAConstBuffer>
			CreateConstantBuffer(_Ty& InitialData);
	};

}

