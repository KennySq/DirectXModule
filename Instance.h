#pragma once
using namespace D3DARS;
using namespace D3DRS;
using namespace std;

class Scene;

class Instance : public IRenderer
{
private:
	string Name;
	shared_ptr<D3DAModel> Model;
	vector<shared_ptr<D3DAMaterial>> Materials;

	vector<ID3D11Buffer*> VertexBuffers;
	vector<ID3D11Buffer*> IndexBuffers;
	
	shared_ptr<Scene> InstanceScene;

	shared_ptr<D3DARS::D3DATransform> InstTransform;
	
public:

	explicit Instance();
	virtual ~Instance();
	void SetMesh(shared_ptr<D3DAModel> pModel) override;
	void DrawMesh() override;
	void AddMaterial(shared_ptr<D3DAMaterial> Material) override;

	inline void SetName(const char* NewName) { Name = NewName; }

	inline void SetScene(shared_ptr<Scene> NewScene) {
		if (InstanceScene != nullptr)
		{
			debug_logger("This instance already has been assigned, You might have to call EmigrateScene");
			return;
		}
		if (NewScene == nullptr)
		{
			debug_logger("This scene is empty!");
			return;
		}

		InstTransform = make_shared<D3DARS::D3DATransform>();
		InstanceScene = NewScene;
	}

	inline D3DARS::D3DATransform* GetTransform() { return InstTransform.get(); }
	
};
