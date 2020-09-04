#include"pch.h"
#include "GUIShaderEditor.h"

using namespace std;

void GUIShaderEditor::Editor()
{

	ImGui::Begin("Shader Editor");
	ImGui::InputTextMultiline("Edit", Buffer.begin(), (size_t)Buffer.size());
	
	ImGui::End();
	
}

HRESULT GUIShaderEditor::Open(string Path)
{
	if (OpenStream.is_open())
	{
		Save();
		Close();
	}

	OpenStream.open(Path);

	if (OpenStream.is_open())
	{
		while (!OpenStream.eof())
		{
			string Str;
			getline(OpenStream, Str);
			Buffer.push_back(*Str.c_str());
		}
	}

	return S_OK;
}

void GUIShaderEditor::Close()
{
	if(OpenStream.is_open())
		OpenStream.close();
}

void GUIShaderEditor::Save()
{
	auto RawTexts = Buffer.Data;
	
	SaveStream.write(RawTexts, sizeof(Buffer.Size));

}

HRESULT GUIShaderEditor::Compile()
{
	return E_NOTIMPL;
}

GUIShaderEditor::GUIShaderEditor()
{}


GUIShaderEditor::~GUIShaderEditor()
{}
