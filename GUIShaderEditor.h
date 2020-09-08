#pragma once
using namespace std;
class GUIShaderEditor
{

	shared_ptr<D3DAMaterial>* Shader;
	
	std::string Path;
	std::string Buffer;

	

	std::fstream Stream;
public:

	void Editor();
	HRESULT Open(string Path);
	void Close();

	void Save();
	HRESULT Compile();



	GUIShaderEditor();
	~GUIShaderEditor();
};

