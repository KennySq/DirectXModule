#pragma once
namespace D3DRS
{
	class Buffer
	{
		template<typename _VertTy>
		static shared_ptr<D3DAMeshBuffer>
			CreateConstantMeshBuffer(shared_ptr<D3DARS::D3DAMesh<D3DVERTEX::StandardVertex>> Mesh);
	

	};

}

