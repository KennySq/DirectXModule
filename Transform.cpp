#include"pch.h"
#include "Transform.h"



void D3DARS::D3DATransform::MakeTransform()
{
	auto Device = D3DHW::GetDevice();

	XMStoreFloat4x4(&World, XMMatrixIdentity());

	HRESULT Debug;
	D3D11_BUFFER_DESC Desc{};
	D3D11_SUBRESOURCE_DATA Sub{};
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.ByteWidth = sizeof(XMFLOAT4X4);
	Desc.Usage = D3D11_USAGE_DEFAULT;

	Sub.pSysMem = &World;

	Debug = Device->CreateBuffer(&Desc, &Sub, TransformBuffer.GetAddressOf());
	resource_assert(TransformBuffer.Get());
	
}

D3DATransform::D3DATransform()
{}


D3DATransform::~D3DATransform()
{}


