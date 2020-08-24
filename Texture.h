#pragma once


// D3D Resource namespace
namespace D3DRS
{
	using namespace WRL;
	using namespace std;

	class D3DRenderableTexture;
	class D3DDepthStencilTexture;
	class D3DComputableTexture;
	class D3DTexture2D;

	static ComPtr<ID3D11RenderTargetView> MakeRenderTargetView(ID3D11Resource* Resource, D3D11_RENDER_TARGET_VIEW_DESC RTVDesc = D3D11_RENDER_TARGET_VIEW_DESC());
	static ComPtr<ID3D11ShaderResourceView> MakeShaderResourceView(ID3D11Resource* Resource, D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = D3D11_SHADER_RESOURCE_VIEW_DESC());
	static ComPtr<ID3D11UnorderedAccessView> MakeUnorderedAccessView(ID3D11Resource* Resource, D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc = D3D11_UNORDERED_ACCESS_VIEW_DESC());
	static ComPtr<ID3D11DepthStencilView> MakeDepthStencilView(ID3D11Resource* Resource, D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc = D3D11_DEPTH_STENCIL_VIEW_DESC());


	class D3DTexture2D
	{
	protected:
		WRL::ComPtr<ID3D11Texture2D> RawTexture;
		WRL::ComPtr<ID3D11ShaderResourceView> SRV;


	public:
		template<typename _Ty>
		static shared_ptr<_Ty> MakeTexture2D(DXGI_FORMAT Format, UINT Width, UINT Height, D3D11_BIND_FLAG BindFlag)
		{
			HRESULT Result;
			ID3D11Device* Device = D3DHW::GetDevice();

			D3D11_TEXTURE2D_DESC TexDesc{};
			D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc{};
			D3D11_RENDER_TARGET_VIEW_DESC RTVDesc{};
			D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc{};
			D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc{};

			TexDesc.Format = Format;
			TexDesc.Width = Width;
			TexDesc.Height = Height;
			TexDesc.ArraySize = 1;
			TexDesc.SampleDesc.Count = 1;
			TexDesc.SampleDesc.Quality = 0;
			TexDesc.CPUAccessFlags = 0;
			TexDesc.BindFlags = BindFlag;

			SRVDesc.Format = Format;
			SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			SRVDesc.Texture2D.MipLevels = 1;

			if (BindFlag & D3D11_BIND_UNORDERED_ACCESS)
			{
				shared_ptr<D3DComputableTexture> Texture = make_shared<D3DComputableTexture>();
				UAVDesc.Format = Format;
				UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;

				Result = Device->CreateTexture2D(&TexDesc, nullptr, Texture->RawTexture.GetAddressOf());
				resource_assert(Texture->RawTexture.Get());

				Result = Device->CreateShaderResourceView(Texture->RawTexture.Get(), &SRVDesc, Texture->SRV.GetAddressOf());
				resource_assert(Texture->SRV.Get());

				Result = Device->CreateUnorderedAccessView(Texture->RawTexture.Get(), &UAVDesc, (ID3D11UnorderedAccessView**)Texture->GetResource().GetAddressOf());
				resource_assert(Texture->GetResource().Get());

				return Texture;
			}

			if (BindFlag & D3D11_BIND_RENDER_TARGET)
			{
				shared_ptr<D3DRenderableTexture> Texture = make_shared<D3DRenderableTexture>();

				RTVDesc.Format = Format;
				RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

				Result = Device->CreateTexture2D(&TexDesc, nullptr, Texture->RawTexture.GetAddressOf());
				resource_assert(Texture->RawTexture.Get());

				Result = Device->CreateShaderResourceView(Texture->RawTexture.Get(), &SRVDesc, Texture->SRV.GetAddressOf());
				resource_assert(Texture->SRV.Get());

				Device->CreateRenderTargetView(Texture->RawTexture.Get(), &RTVDesc, (ID3D11RenderTargetView**)Texture->GetResource().GetAddressOf());
				resource_assert(Texture->GetResource().Get());

				return Texture;
			}

			if (BindFlag & D3D11_BIND_DEPTH_STENCIL)
			{
				shared_ptr<D3DDepthStencilTexture> Texture = make_shared<D3DDepthStencilTexture>();

				DSVDesc.Format = DXGI_FORMAT_R32_TYPELESS;
				DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

				Result = Device->CreateTexture2D(&TexDesc, nullptr, Texture->RawTexture.GetAddressOf());
				resource_assert(Texture->RawTexture.Get());

				Result = Device->CreateShaderResourceView(Texture->RawTexture.Get(), &SRVDesc, Texture->SRV.GetAddressOf());
				resource_assert(Texture->SRV.Get());

				Device->CreateDepthStencilView(Texture->RawTexture.Get(), &DSVDesc, (ID3D11DepthStencilView**)Texture->GetResource().GetAddressOf());
				resource_assert(Texture->GetResource().Get());

				return Texture;
			}

			return nullptr;

		}
		HRESULT MakeD3D11Texture2D(DXGI_FORMAT Format, UINT Width, UINT Height, D3D11_BIND_FLAG BindFlag);

	};


	//template<typename _Ty>
	//WRL::ComPtr<_Ty> MakeTexture3D(DXGI_FORMAT Format, UINT Width, UINT Height, UINT Depth, D3D11_BIND_FLAG BindFlag);

	
	class D3DRenderableTexture : public D3DTexture2D
	{
	protected:
		WRL::ComPtr<ID3D11RenderTargetView> RTV = nullptr;

	public:
		HRESULT MakeSwapChainBuffer(DXGI_FORMAT Format, UINT Width, UINT Height, UINT Index);


		decltype(RTV) GetResource() { return RTV.Get(); }
	};

	class D3DDepthStencilTexture : public D3DTexture2D
	{
	protected:
		WRL::ComPtr<ID3D11DepthStencilView> DSV = nullptr;
	public:
		decltype(DSV) GetResource() { return DSV.Get(); };

	};

	class D3DComputableTexture : public D3DTexture2D
	{
	protected:
		WRL::ComPtr<ID3D11UnorderedAccessView> UAV = nullptr;
	public:
		decltype(UAV) GetResource() { return UAV.Get(); };
	};


}



