#pragma once
using namespace DirectX;

namespace D3DARS
{
	struct D3DViewProject
	{
		XMFLOAT4X4 View;
		XMFLOAT4X4 Projection;
	};

	class D3DACamera :
		public VirtualObject
	{
	private:
		D3DViewProject ViewProject;
		ComPtr<ID3D11Buffer> CameraBuffer;
		float FOV;
	public:
		inline XMMATRIX GetView() { return XMMatrixTranspose(XMLoadFloat4x4(&ViewProject.View)); }
		inline XMMATRIX GetProjection() { return XMMatrixTranspose(XMLoadFloat4x4(&ViewProject.Projection)); }
		inline ComPtr<ID3D11Buffer> GetBuffer() { return CameraBuffer; }

		D3DACamera();
		D3DACamera(XMVECTOR Position, XMVECTOR Rotation, float FOV, float Near, float Far);
		virtual ~D3DACamera();
	private:
		virtual bool OnInit() override;
		virtual void OnUpdate(float Delta) override;
		virtual void OnRender(float Delta) override;
		virtual void OnRelease() override;

	};


}
