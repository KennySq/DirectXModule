#pragma once
using namespace std;
class Scene
{
private:
	size_t SceneInstaneID;

	map<size_t, shared_ptr<Instance>> SceneObjects;
	map<size_t, shared_ptr<D3DARS::D3DAMaterial>> MaterialCache;
	

public:
	HRESULT AddInstance(shared_ptr<Instance> Inst)
	{
		if (Inst == nullptr)
		{
			debug_logger("This Instance is empty. ");
			return E_INVALIDARG;
		}

		SceneObjects.insert_or_assign((size_t)(Inst.get()), Inst);

		return S_OK;
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
};

