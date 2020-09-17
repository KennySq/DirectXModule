#pragma once
using namespace DirectX;
using namespace WRL;
// Direct 3D App Resouce namespace
enum PASSTYPE;

namespace D3DARS
{
	namespace D3DVERTEX
	{
		struct StandardVertex
		{
			DirectX::XMFLOAT4 Position;
			DirectX::XMFLOAT3 Normal;
			DirectX::XMFLOAT2 UV;


			bool operator<(StandardVertex& Other)
			{
				return (XMVector4Length(XMLoadFloat4(&Position)).m128_f32[0] < XMVector4Length(XMLoadFloat4(&Other.Position)).m128_f32[0]);
			}

			bool operator==(StandardVertex& Other)
			{
				return (Position.x == Other.Position.x && Position.y == Other.Position.y && Position.z == Other.Position.z) &&
					(Normal.x == Other.Normal.x && Normal.y == Other.Normal.y && Normal.z == Other.Normal.z) &&
					(UV.x == Other.UV.x && UV.y == Other.UV.y);
			}
		};

		struct CompactVertex
		{
			DirectX::XMFLOAT4 Position;
		};
	}


	template<typename _VertTy>
	struct D3DAMesh
	{
		vector<_VertTy> Vertices;
		vector<MeshIndex> Indices;
	};

	struct D3DAShader
	{
		string Path;
		

		
	};

	struct D3DAMaterial
	{
	private:

		// ��ĳ���õ� �Ʒ� ���̴� �������̽� ������� �����մϴ�.
		std::map<size_t, IUnknown**> Interfaces;

		WRL::ComPtr<ID3D11VertexShader> VS;
		WRL::ComPtr<ID3D11PixelShader> PS;
		WRL::ComPtr<ID3D11ComputeShader> CS;
		WRL::ComPtr<ID3D11GeometryShader> GS;
		WRL::ComPtr<ID3D11HullShader> HS;
		WRL::ComPtr<ID3D11DomainShader> DS;

		WRL::ComPtr<ID3D11InputLayout> IL;

		int PassType;
		
	public:

		int GetPassType() { return PassType; }
		void AddPassType(PASSTYPE Flag) { PassType |= Flag; }
		
		// �� �������̽��� �����԰� ���ÿ� ���ø��� �̿��Ͽ� ���ټ��� ���Դϴ�.
		template<typename _Ty>
		inline _Ty* RequestInterface()
		{
			_Ty* Shader;

			// ���̴� �������̽����� ���������� ��ӹ޴� IUnknown�� ���·�
			// ��ĳ���õǾ� Interfaces��� �ϳ��� �����̳ʿ� �����˴ϴ�.

			// ������ ����ϴ� Ű�� ���� ������ ���� ���ڰ� �ƴ�
			// typeid�� �˾Ƴ� �ڷ����� hash ���� ����մϴ�.
			auto DC = Interfaces[typeid(_Ty).hash_code()];

			if (*DC == nullptr)
				return nullptr;

			// ���� _Ty�� hash ���� �ش��ϴ� ����� _Ty�� �ش��ϴ� �������̽���
			// Query�� �Ұ����ϴٸ� �Լ��� nullptr�� ��ȯ�մϴ�.
			if (FAILED(DC[0]->QueryInterface<_Ty>(&Shader)))
				return nullptr;

			return Shader;
			
		}

		template<typename _Ty>
		inline _Ty** RequestAddressOfInterface() // 2���� �����ͷ� ���� (Out-Parameter)
		{
			_Ty** Shader = (_Ty**)Interfaces[typeid(_Ty).hash_code()];
			return Shader;
		}



		D3DAMaterial()
		{
			PassType = 0;

			// �� ����� ���������� ���۾����� type�� ���� ������ ���� �޾ƾ� �մϴ�.
			Interfaces.insert_or_assign(typeid(ID3D11VertexShader).hash_code(), (IUnknown**)VS.GetAddressOf());
			Interfaces.insert_or_assign(typeid(ID3D11PixelShader).hash_code(), (IUnknown**)PS.GetAddressOf());
			Interfaces.insert_or_assign(typeid(ID3D11ComputeShader).hash_code(), (IUnknown**)CS.GetAddressOf());
			Interfaces.insert_or_assign(typeid(ID3D11GeometryShader).hash_code(), (IUnknown**)GS.GetAddressOf());
			Interfaces.insert_or_assign(typeid(ID3D11HullShader).hash_code(), (IUnknown**)HS.GetAddressOf());
			Interfaces.insert_or_assign(typeid(ID3D11DomainShader).hash_code(), (IUnknown**)DS.GetAddressOf());
			Interfaces.insert_or_assign(typeid(ID3D11InputLayout).hash_code(), (IUnknown**)IL.GetAddressOf());
		}
		~D3DAMaterial()
		{

		}

		// ������ _Ty ���·� �������̽��� �ʱ�ȭ�մϴ�.
		template<typename _Ty>
		inline void SetInterface(WRL::ComPtr<_Ty> Inter)
		{
			// ���� �ش� �������̽��� �������� �ʴ°�� ���ܷ� ������ �α׸� ����� �Լ��� �����մϴ�
			if (Interfaces.find(typeid(_Ty).hash_code()) == nullptr)
			{
				debug_logger("There is no such interface in this material.");
				return;
			}

			Interfaces[typeid(_Ty).hash_code()] = Inter;
		}

	};
	
	struct D3DAConstBuffer
	{
		WRL::ComPtr<ID3D11Buffer> CB;
	};

	struct D3DAMeshBuffer
	{
		WRL::ComPtr<ID3D11Buffer> VB; // Vertex Buffer
		WRL::ComPtr<ID3D11Buffer> IB; // Index Buffer
	};

	struct	D3DAModel
	{
		vector<shared_ptr<D3DAMeshBuffer>> Meshes;
		unsigned int* Stride;

		D3DAModel()
		{
		}
		~D3DAModel() {}

	private:
		
	};

	
	struct D3DAStructBuffer
	{
		WRL::ComPtr<ID3D11Buffer> SB; // Struct Buffer u* register only
		WRL::ComPtr<ID3D11UnorderedAccessView> UAV;
		UINT Count;
		UINT Stride;
	};

}