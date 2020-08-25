#pragma once

_inline void resource_assert(ID3D11Resource* Resource)
{
	assert(Resource != nullptr && (std::string("Resource didn't initialized!") + typeid(Resource).name()).c_str());
}

_inline void resource_assert(ID3D11View* View)
{
	assert(View != nullptr && (std::string("View didn't initialized! ") + typeid(View).name()).c_str());
}

_inline void device_assert(IUnknown* Interface)
{
	assert(Interface != nullptr && (std::string("Interface didn't initialized!") + typeid(Interface).name()).c_str());
}

_inline void debug_logger(const char* Str)
{
#ifdef _DEBUG
	std::cout << Str << std::endl;
#endif
}