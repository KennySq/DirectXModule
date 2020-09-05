#include"pch.h"
#include "GUIShaderEditor.h"

using namespace std;

struct ResizeCallback
{
	static int MyResizeCallback(ImGuiInputTextCallbackData* data)
	{
		if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
		{
			string* my_str = (string*)data->UserData;
			IM_ASSERT((char*)my_str->c_str() == data->Buf);
			my_str->resize(data->BufSize);
			data->Buf = (char*)my_str->c_str();
		}
		return 0;
	}

	static bool MyInputTextMultiline(const char* label, string* my_str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0)
	{
		IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
		return ImGui::InputTextMultiline(label, (char*)my_str->c_str(), (size_t)my_str->size(), size, flags | ImGuiInputTextFlags_CallbackResize, ResizeCallback::MyResizeCallback, (void*)my_str);
	}
};

void GUIShaderEditor::Editor()
{

	ImGui::Begin("Shader Editor");
	
	ResizeCallback::MyInputTextMultiline(Path.c_str(), &Buffer);
	//ImGui::InputTextMultiline(Path.c_str(), (char*)Buffer.data(), 65536, ImVec2(0,0),
	//						  ImGuiInputTextFlags_CallbackResize,ImGuiInputTextCallback);


	
	if(ImGui::Button("Save and Compile"))
	{
		Compile();
	}
	ImGui::SameLine();
	if(ImGui::Button("Save"))
	{
		Save();
	}
	ImGui::End();
	
}

HRESULT GUIShaderEditor::Open(string FilePath)
{

	if (Stream.is_open())
	{
		//Save();
		Close();
	}
	Path = FilePath;

	Stream.open(Path);

	if (Stream.is_open())
	{
		while (!Stream.eof())
		{
			string Str;
			std::getline(Stream, Str);
			Buffer.append(Str.c_str());
			Buffer.push_back('\n');
		} 
	}

	Stream.close();

	std::ofstream ClearStream;
	ClearStream.open(FilePath, ios::trunc);
	ClearStream.close();
	


	return S_OK;
}

void GUIShaderEditor::Close()
{
	if(Stream.is_open())
		Stream.close();
}

void GUIShaderEditor::Save()
{
	Stream.open(Path);
	Stream.write(Buffer.c_str(), Buffer.length());
	Stream.close();
}

HRESULT GUIShaderEditor::Compile()
{
	
	CompilePass(Path.c_str(), )
	
	
	return S_OK;
}

GUIShaderEditor::GUIShaderEditor()
{}


GUIShaderEditor::~GUIShaderEditor()
{
	Close();
	
}
