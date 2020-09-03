#pragma once
namespace D3DARS
{
	class D3DATransform
	{
		XMFLOAT4X4 World;

		XMFLOAT4 Position;
		XMFLOAT4 Rotation;
		XMFLOAT4 Scale;

		ComPtr<ID3D11Buffer> TransformBuffer;
	public:
		void MakeTransform();

		ComPtr<ID3D11Buffer> GetBuffer() { return TransformBuffer; }

		void Rotate(float Pitch, float Yaw, float Roll);
		void Translate(float x, float y, float z);

		XMFLOAT4X4& GetMatrix() { return World; }

		D3DATransform();
		~D3DATransform();
	};

	

}

