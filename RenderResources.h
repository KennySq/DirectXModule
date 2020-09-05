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

		// 업캐스팅된 아래 쉐이더 인터페이스 멤버들을 보관합니다.
		std::map<size_t, IUnknown**> Interfaces;

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
		inline _Ty* RequestInterface()
		{
			_Ty* Shader;

			// 쉐이더 인터페이스들이 공통적으로 상속받는 IUnknown의 형태로
			// 업캐스팅되어 Interfaces라는 하나의 컨테이너에 보관됩니다.

			// 보관에 사용하는 키는 빠른 접근을 위해 문자가 아닌
			// typeid로 알아낸 자료형의 hash 값을 사용합니다.
			auto DC = Interfaces[typeid(_Ty).hash_code()];

			if (*DC == nullptr)
				return nullptr;

			// 만약 _Ty의 hash 값에 해당하는 멤버가 _Ty에 해당하는 인터페이스로
			// Query가 불가능하다면 함수는 nullptr를 반환합니다.
			if (FAILED(DC[0]->QueryInterface<_Ty>(&Shader)))
				return nullptr;

			return Shader;
			
		}

		template<typename _Ty>
		inline _Ty** RequestAddressOfInterface() // 2차원 포인터로 수정 (Out-Parameter)
		{
			_Ty** Shader = (_Ty**)Interfaces[typeid(_Ty).hash_code()];
			return Shader;
		}



		D3DAMaterial()
		{


			// 이 방법은 아직까지는 수작업으로 type에 관한 정보를 전달 받아야 합니다.
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