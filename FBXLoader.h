#pragma once
using namespace D3DARS;
using namespace D3DRS;
using namespace std;
using namespace D3DARS::D3DVERTEX;
class FBXLoader
{
private:
	FbxScene* Scene;
	shared_ptr<D3DAModel> Model;

	shared_ptr<D3DAMesh<StandardVertex>> TemporalMesh;
	vector<XMFLOAT4> Positions;
	vector<XMFLOAT3> Normals;
	vector<XMFLOAT2> UVs;

public:
	shared_ptr<D3DAModel> Load(string Path);
	

	void LoadNode(FbxNode* Node);
	void GetVertex(FbxMesh* Mesh);

	XMFLOAT3 ReadNormal(FbxMesh* Mesh, int CPI, int VertexCount, int PolyIndex, int PolyVertex);
};

