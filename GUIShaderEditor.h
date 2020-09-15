#pragma once
using namespace std;
using namespace D3DARS;

class GUIShaderEditor
{

	shared_ptr<D3DARS::D3DAMaterial> Shader;

	std::string Path;
	std::string Buffer;

	

	std::fstream Stream;
public:

	void Editor();
	HRESULT Open(string Path, shared_ptr<D3DAMaterial> LinkMaterial);
	void Close();

	void Save();
	HRESULT Compile();



	GUIShaderEditor();
	~GUIShaderEditor();
};

