#pragma once
using namespace std;
class Scene
{
private:
	size_t SceneInstaneID;

	vector<size_t> IIDList;
	map<size_t, shared_ptr<Instance>> SceneObjects;
	map<size_t, shared_ptr<D3DARS::D3DAMaterial>> MaterialCache;
	
	vector<shared_ptr<D3DACamera>> SceneCameras;

public:
	size_t AddInstance(shared_ptr<Instance> Inst)
	{
		if (Inst == nullptr)
		{
			debug_logger("This Instance is empty. ");
			return NULL;
		}

		auto IID = (size_t)(Inst.get());
	
		SceneObjects.insert_or_assign(IID, Inst);

		return IID;
	}
	HRESULT RemoveInstance(size_t Inst)
	{
		if ((shared_ptr<Instance>&)(Inst) == nullptr)
		{
			debug_logger("The Inst does not exist. ");
			return E_INVALIDARG;
		}

		SceneObjects.erase(Inst);

		return S_OK;
	}
	HRESULT AddMaterial(shared_ptr<D3DAMaterial> Material)
	{
		if(Material == nullptr)
		{
			debug_logger("This Material is empty.");
			return E_INVALIDARG;
		}

		MaterialCache.insert_or_assign((size_t)(Material.get()),Material);

		return S_OK;
	}
	HRESULT RemoveMaterial(size_t Material)
	{
		if((shared_ptr<D3DAMaterial>&)(Material) == nullptr)
		{
			debug_logger("The Material does not exist");
			return E_INVALIDARG;
		}

		MaterialCache.erase(Material);

		return S_OK;
	}

	inline shared_ptr<D3DACamera> GetCamera(int Index) { return SceneCameras[Index]; }
	inline void AddCamera(shared_ptr<D3DACamera> Camera)
	{
		SceneCameras.emplace_back(Camera);
		
	}

	Instance* MakeInstance(const char* InstName)
	{
		shared_ptr<Instance> Inst = make_shared<Instance>();

		Inst->SetName(InstName);
		Inst->SetScene(make_shared<Scene>(*this));
		
		auto Transform = Inst->GetTransform();
		auto IID = AddInstance(Inst);
		
		IIDList.emplace_back(IID);
		Transform->MakeTransform();

		return Inst.get();
	}

	
	Instance* GetInstance(size_t InstanceID)
	{
		return SceneObjects[InstanceID].get();

	}

	Instance* GetInstance(int Index)
	{
		return SceneObjects[IIDList[Index]].get();
	}

	
	
};

