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

		// 업캐스팅된 아래 쉐이더 인터페이스 멤버들을 보관합니다.
		std::map<size_t, WRL::ComPtr<ID3D11DeviceChild>> Interfaces;

		WRL::ComPtr<ID3D11VertexShader> VS;
		WRL::ComPtr<ID3D11PixelShader> PS;
		WRL::ComPtr<ID3D11ComputeShader> CS;
		WRL::ComPtr<ID3D11GeometryShader> GS;
		WRL::ComPtr<ID3D11HullShader> HS;
		WRL::ComPtr<ID3D11DomainShader> DS;

		WRL::ComPtr<ID3D11InputLayout> IL;

	public:
		// 각 인터페이스를 은닉함과 동시에 템플릿을 이용하여 접근성을 높입니다.
		template<typename _Ty>
		inline WRL::ComPtr<_Ty> RequestInterface()
		{
			WRL::ComPtr<_Ty> Shader;

			// 쉐이더 인터페이스들이 공통적으로 상속받는 ID3D11DeviceChild의 형태로
			// 업캐스팅되어 Interfaces라는 하나의 컨테이너에 보관됩니다.

			// 보관에 사용하는 키는 빠른 접근을 위해 문자가 아닌
			// typeid로 알아낸 자료형의 hash 값을 사용합니다.
			WRL::ComPtr<ID3D11DeviceChild> DC = Interfaces[typeid(_Ty).hash_code()];

			// 만약 _Ty의 hash 값에 해당하는 멤버가 _Ty에 해당하는 인터페이스로
			// Query가 불가능하다면 함수는 nullptr를 반환합니다.
			if(FAILED(DC->QueryInterface<_Ty>(Shader.GetAddressOf())))
			   return nullptr;

			return Shader;
			
		}

		
		D3DAMaterial()
		{
			// 이 방법은 아직까지는 수작업으로 type에 관한 정보를 전달 받아야 합니다.
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

		// 지정된 _Ty 형태로 인터페이스를 초기화합니다.
		template<typename _Ty>
		inline void SetInterface(WRL::ComPtr<_Ty> Inter)
		{
			// 만약 해당 인터페이스를 포함하지 않는경우 예외로 간주해 로그를 남기고 함수를 종료합니다
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