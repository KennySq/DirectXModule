#pragma once
using namespace std;
class GUIShaderEditor
{
	std::string Path;
	ImVector<char> Buffer;

	std::ifstream OpenStream;
	std::ofstream SaveStream;
public:

	void Editor();
	HRESULT Open(string Path);
	void Close();

	void Save();
	HRESULT Compile();



	GUIShaderEditor();
	~GUIShaderEditor();
};

