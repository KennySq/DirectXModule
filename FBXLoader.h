#pragma once
using namespace D3DARS;
class FBXLoader
{
private:
	FbxScene* Scene;
	shared_ptr<D3DAModel<D3DVERTEX::StandardVertex>> Model;

	XMFLOAT4* Positions = nullptr;
	XMFLOAT3* Normals = nullptr;
	XMFLOAT2* UVs = nullptr;
public:
	shared_ptr<D3DAModel<D3DVERTEX::StandardVertex>> Load(string Path);
	

	void LoadNode(FbxNode* Node);
	void GetVertex(FbxMesh* Mesh);
	XMFLOAT3 ReadNormal(FbxMesh* Mesh, int CPI, int VertexCount);
};

