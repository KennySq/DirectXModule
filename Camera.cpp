#include"pch.h"
#include "Camera.h"

D3DACamera::D3DACamera()
{
	XMMATRIX ViewMat;
	XMMATRIX ProjectionMat;
	
	D3D11_BUFFER_DESC Desc{};
	D3D11_MAPPED_SUBRESOURCE SubData{};

	ID3D11Device* Device = GetDevice();
	ID3D11DeviceContext* Context = GetContext();
	
	Desc.ByteWidth = sizeof(XMFLOAT4X4) * 2;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	Device->CreateBuffer(&Desc, nullptr, CameraBuffer.GetAddressOf());
	resource_assert(CameraBuffer.Get());

	XMVECTOR Eye = XMVectorSet(5.0f, 0.0f, 5.0f, 1.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	ViewMat = XMMatrixTranspose(XMMatrixLookAtLH(Eye, At, Up));
	ProjectionMat = XMMatrixTranspose(XMMatrixPerspectiveFovLH(FOV, BIAspectRatio, 0.01f, 1000.0f));

	XMStoreFloat4x4(&ViewProject.View, ViewMat);
	XMStoreFloat4x4(&ViewProject.Projection, ProjectionMat);
	
	Context->UpdateSubresource(CameraBuffer.Get(), 0, nullptr, &ViewProject, 0, 0);
}

D3DACamera::D3DACamera(XMVECTOR Position, XMVECTOR Rotation, float FOV, float Near, float Far)
{}

D3DACamera::~D3DACamera()
{}

bool D3DACamera::OnInit()
{
	return true;
}

void D3DACamera::OnUpdate(float Delta)
{}

void D3DACamera::OnRender(float Delta)
{}

void D3DACamera::OnRelease()
{}
