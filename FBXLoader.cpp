#include"pch.h"
#include "FBXLoader.h"

using namespace std;

shared_ptr<D3DAModel> FBXLoader::Load(string Path)
{
	FbxManager* Manager = FbxManager::Create();
	FbxIOSettings* IOSetting = FbxIOSettings::Create(Manager,IOSROOT);
	Manager->SetIOSettings(IOSetting);
	FbxImporter* Importer = FbxImporter::Create(Manager, "");

	bool Result = Importer->Initialize(Path.c_str(), -1, Manager->GetIOSettings());
	if (Result != true)
	{
		debug_logger("Failed to import .fbx file");
		debug_logger(Importer->GetStatus().GetErrorString());
		MessageBoxA(nullptr, "Failed to import .fbx file", 0, 0);
	}

	Model = make_shared<D3DAModel>(	);

	D3DVERTEX::StandardVertex Vertex;
	
	Scene = FbxScene::Create(Manager, "Scene");
	Importer->Import(Scene);

	Importer->Destroy();

	FbxNode* Root = Scene->GetRootNode();
	LoadNode(Root);
	
	IOSetting->Destroy();
	Manager->Destroy();

	return Model;
}

void FBXLoader::LoadNode(FbxNode* Node)
{
	FbxNodeAttribute* NodeAtt = Node->GetNodeAttribute();
	static int MeshCounter = 0;
	D3DVERTEX::StandardVertex Vertex;
	
	XMFLOAT4 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 UV;
	
	
	shared_ptr<D3DAMesh<D3DVERTEX::StandardVertex>> TemporalMesh =
		make_shared<D3DAMesh<D3DVERTEX::StandardVertex>>(
			D3DAMesh<D3DVERTEX::StandardVertex>()
			);
	
	if (NodeAtt)
	{
		if (NodeAtt->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			FbxMesh* Mesh = Node->GetMesh();
			GetVertex(Mesh);
		
			unsigned int TriCount = Mesh->GetPolygonCount();
			unsigned int VertexCount = 0;

			for (unsigned int i = 0; i < TriCount; i++)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					int CPI = Mesh->GetPolygonVertex(i, j);

					XMFLOAT4& Position = Positions[CPI];
					XMFLOAT3 Normal = ReadNormal(Mesh, CPI, VertexCount);
					
					Vertex.Position = Position;
					Vertex.Normal = Normal;

					TemporalMesh->Vertices.push_back(Vertex);
					TemporalMesh->Indices.push_back(CPI);

					VertexCount++;
				}
			}
		
		}

		auto Buffer = D3DRSBuffer::CreateConstantMeshBuffer
			<D3DVERTEX::StandardVertex>(TemporalMesh);
		
		Model->Meshes.emplace_back(Buffer);
		
		MeshCounter++;
	}


	const int ChildCount = Node->GetChildCount();
	for (int i = 0; i < ChildCount; i++)
	{
		LoadNode(Node->GetChild(i));
	}



}

void FBXLoader::GetVertex(FbxMesh* Mesh)
{
	unsigned int Count = Mesh->GetControlPointsCount();
	Positions = new XMFLOAT4[Count];
	Normals = new XMFLOAT3[Count];
	UVs = new XMFLOAT2[Count];

	for (int i = 0; i < Count; i++)
	{
		XMFLOAT4 Position;
		XMFLOAT3 Normal;
		XMFLOAT2 UV;

		Position.x = static_cast<float>(Mesh->GetControlPointAt(i).mData[0]);
		Position.y = static_cast<float>(Mesh->GetControlPointAt(i).mData[1]);
		Position.z = static_cast<float>(Mesh->GetControlPointAt(i).mData[2]);

		Positions[i] = Position;

	}

}

XMFLOAT3 FBXLoader::ReadNormal(FbxMesh* Mesh, int CPI, int VertexCount)
{
	if (Mesh->GetElementNormalCount() < 1)
	{
		debug_logger("There is no nomrals.");
	}

	FbxGeometryElementNormal* VertexNormal = Mesh->GetElementNormal();
	XMFLOAT3 Normal;

	switch (VertexNormal->GetMappingMode())
	{
		case FbxGeometryElement::eByControlPoint:
		{
			switch (VertexNormal->GetReferenceMode())
			{
				case FbxGeometryElement::eNormal:
				{
					Normal.x = static_cast<float>(VertexNormal->GetDirectArray().GetAt(CPI).mData[0]);
					Normal.y = static_cast<float>(VertexNormal->GetDirectArray().GetAt(CPI).mData[1]);
					Normal.z = static_cast<float>(VertexNormal->GetDirectArray().GetAt(CPI).mData[2]);
				} break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int Index = VertexNormal->GetIndexArray().GetAt(CPI);
					Normal.x = static_cast<float>(VertexNormal->GetDirectArray().GetAt(Index).mData[0]);
					Normal.y = static_cast<float>(VertexNormal->GetDirectArray().GetAt(Index).mData[1]);
					Normal.z = static_cast<float>(VertexNormal->GetDirectArray().GetAt(Index).mData[2]);
				} break;



				

			}
			break;
		case FbxGeometryElement::eByPolygonVertex:
		{
			switch (VertexNormal->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					Normal.x = static_cast<float>(VertexNormal->GetDirectArray().GetAt(VertexCount).mData[0]);
					Normal.y = static_cast<float>(VertexNormal->GetDirectArray().GetAt(VertexCount).mData[1]);
					Normal.z = static_cast<float>(VertexNormal->GetDirectArray().GetAt(VertexCount).mData[2]);
				} break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int Index = VertexNormal->GetIndexArray().GetAt(VertexCount);
					Normal.x = static_cast<float>(VertexNormal->GetDirectArray().GetAt(Index).mData[0]);
					Normal.y = static_cast<float>(VertexNormal->GetDirectArray().GetAt(Index).mData[1]);
					Normal.z = static_cast<float>(VertexNormal->GetDirectArray().GetAt(Index).mData[2]);
				} break;
			}
		}
			break;
		}
	
	}


	return Normal;
}
