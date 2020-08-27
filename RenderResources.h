#pragma once
using namespace DirectX;
using namespace WRL;
// Direct 3D App Resouce namespace
namespace D3DARS
{
	namespace D3DVERTEX
	{
		struct StandardVertex
		{
			DirectX::XMFLOAT4 Position;
			DirectX::XMFLOAT3 Normal;
			DirectX::XMFLOAT2 UV;
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
		std::map<size_t, WRL::ComPtr<ID3D11DeviceChild>> Interfaces;

		WRL::ComPtr<ID3D11VertexShader> VS;
		WRL::ComPtr<ID3D11PixelShader> PS;
		WRL::ComPtr<ID3D11ComputeShader> CS;
		WRL::ComPtr<ID3D11GeometryShader> GS;
		WRL::ComPtr<ID3D11HullShader> HS;
		WRL::ComPtr<ID3D11DomainShader> DS;

		WRL::ComPtr<ID3D11InputLayout> IL;

	public:
		// �� �������̽��� �����԰� ���ÿ� ���ø��� �̿��Ͽ� ���ټ��� ���Դϴ�.
		template<typename _Ty>
		inline WRL::ComPtr<_Ty> RequestInterface()
		{
			WRL::ComPtr<_Ty> Shader;

			// ���̴� �������̽����� ���������� ��ӹ޴� ID3D11DeviceChild�� ���·�
			// ��ĳ���õǾ� Interfaces��� �ϳ��� �����̳ʿ� �����˴ϴ�.

			// ������ ����ϴ� Ű�� ���� ������ ���� ���ڰ� �ƴ�
			// typeid�� �˾Ƴ� �ڷ����� hash ���� ����մϴ�.
			WRL::ComPtr<ID3D11DeviceChild> DC = Interfaces[typeid(_Ty).hash_code()];

			// ���� _Ty�� hash ���� �ش��ϴ� ����� _Ty�� �ش��ϴ� �������̽���
			// Query�� �Ұ����ϴٸ� �Լ��� nullptr�� ��ȯ�մϴ�.
			if(FAILED(DC->QueryInterface<_Ty>(Shader.GetAddressOf())))
			   return nullptr;

			return Shader;
			
		}

		
		D3DAMaterial()
		{
			// �� ����� ���������� ���۾����� type�� ���� ������ ���� �޾ƾ� �մϴ�.
			Interfaces.insert_or_assign(typeid(ID3D11VertexShader).hash_code(), VS);
			Interfaces.insert_or_assign(typeid(ID3D11PixelShader).hash_code(), PS);
			Interfaces.insert_or_assign(typeid(ID3D11ComputeShader).hash_code(), CS);
			Interfaces.insert_or_assign(typeid(ID3D11GeometryShader).hash_code(), GS);
			Interfaces.insert_or_assign(typeid(ID3D11HullShader).hash_code(), HS);
			Interfaces.insert_or_assign(typeid(ID3D11DomainShader).hash_code(), DS);
			Interfaces.insert_or_assign(typeid(ID3D11InputLayout).hash_code(), IL);
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


	template<typename _VertTy>
	struct D3DAModel
	{
		shared_ptr<vector<D3DAMesh<_VertTy>>> Mesh;

		D3DAModel<_VertTy>()
		{
			Mesh = make_shared<vector<D3DAMesh<_VertTy>>>();
		}
		~D3DAModel<_VertTy>() {	}

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

	struct D3DAStructBuffer
	{
		WRL::ComPtr<ID3D11Buffer> SB; // Struct Buffer u* register only
		WRL::ComPtr<ID3D11UnorderedAccessView> UAV;
		UINT Count;
		UINT Stride;
	};

}