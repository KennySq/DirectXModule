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

void D3DARS::D3DATransform::Rotate(float Pitch, float Yaw, float Roll)
{
	auto Rot = XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll);
	auto Ori = XMLoadFloat4x4(&World);

	Ori *= Rot;

	XMStoreFloat4x4(&World, Ori);

}

void D3DARS::D3DATransform::Translate(float x, float y, float z)
{
	auto Rot = XMMatrixTranslation(x, y, z);
	auto Ori = XMLoadFloat4x4(&World);

	Ori *= Rot;

	XMStoreFloat4x4(&World, XMMatrixTranspose(Ori));

}

D3DATransform::D3DATransform()
{}


D3DATransform::~D3DATransform()
{}


