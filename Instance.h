#pragma once
using namespace D3DARS;
using namespace D3DRS;
using namespace std;
class Instance : public IRenderer
{
private:
	shared_ptr<D3DAModel> Model;
	vector<shared_ptr<D3DAMaterial>> Materials;

	vector<ID3D11Buffer*> VertexBuffers;
	vector<ID3D11Buffer*> IndexBuffers;
	
	
public:

	Instance();
	virtual ~Instance();
	void SetMesh(shared_ptr<D3DAModel> pModel) override;
	void DrawMesh() override;
	void AddMaterial(shared_ptr<D3DAMaterial> Material) override;
};
