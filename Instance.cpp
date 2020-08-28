#include"pch.h"
#include "Instance.h"



Instance::Instance()
{}


Instance::~Instance()
{}

void Instance::SetMesh(shared_ptr<D3DAMeshBuffer> Model)
{
	
}

void Instance::DrawMesh()
{
}

void Instance::AddMaterial(shared_ptr<D3DAMaterial> Material)
{
	if(Material.get() == nullptr)
		debug_logger((string("This resource is empty! => ")
					  + string(typeid(Material).name())).c_str());

	Materials.emplace_back(Material);

	return;
}
