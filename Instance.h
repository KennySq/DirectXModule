#pragma once
using namespace D3DARS;
using namespace D3DRS;

class Instance : public IRenderer
{
private:
	shared_ptr<D3DAMeshBuffer> Model;
	vector<shared_ptr<D3DAMaterial>> Materials;

public:

	Instance();
	virtual ~Instance();
	void SetMesh(shared_ptr<D3DAMeshBuffer> Model) override;
	void DrawMesh() override;
	virtual void AddMaterial(shared_ptr<D3DAMaterial> Material) override;
};
