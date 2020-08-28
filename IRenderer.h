#pragma once


struct IRenderer
{
	
	virtual void SetMesh(std::shared_ptr<D3DAMeshBuffer> Model) = 0;
	virtual void AddMaterial(shared_ptr<D3DAMaterial> Material);
	virtual void DrawMesh() = 0;

	IRenderer() {}
	virtual ~IRenderer() {}
};