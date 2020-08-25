#include "pch.h"
#include "Texture.h"

using namespace D3DHW;
using namespace D3DRS;
using namespace WRL;

HRESULT D3DRS::D3DTexture2D::MakeD3D11Texture2D(DXGI_FORMAT Format, UINT Width, UINT Height, D3D11_BIND_FLAG BindFlag)
{
	HRESULT Result;
	D3D11_TEXTURE2D_DESC TexDesc{};
	ID3D11Device* Device = GetDevice();

	TexDesc.Format = Format;
	TexDesc.Width = Width;
	TexDesc.Height = Height;
	TexDesc.ArraySize = 1;
	TexDesc.SampleDesc.Count = 1;
	TexDesc.SampleDesc.Quality = 0;
	TexDesc.CPUAccessFlags = 0;
	TexDesc.BindFlags = BindFlag;
		
	Result = Device->CreateTexture2D(&TexDesc, nullptr, RawTexture.GetAddressOf());
	resource_assert(RawTexture.Get());

	return S_OK;
}

HRESULT D3DRS::D3DRenderableTexture::MakeSwapChainBuffer(DXGI_FORMAT Format, UINT Width, UINT Height, UINT Index)
{
	HRESULT Result;
	ID3D11Device* Device = GetDevice();
	IDXGISwapChain* SwapChain = GetSwapChain();

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc{};
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc{};

	SRVDesc.Format = Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	RTVDesc.Format = Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	//Result = MakeD3D11Texture2D(Format, Width, Height, D3D11_BIND_RENDER_TARGET);

	Result = SwapChain->GetBuffer(Index, __uuidof(ID3D11Texture2D*), (void**)RawTexture.GetAddressOf());
	resource_assert(RawTexture.Get());

	RTV = MakeRenderTargetView(RawTexture.Get(), RTVDesc);
	resource_assert(RTV.Get());

	return S_OK;
}

ComPtr<ID3D11RenderTargetView> D3DRS::MakeRenderTargetView(ID3D11Resource* Resource, D3D11_RENDER_TARGET_VIEW_DESC RTVDesc)
{
	HRESULT Result;
	ID3D11Device* Device = GetDevice();

	ComPtr<ID3D11RenderTargetView> RTV;

	Result = Device->CreateRenderTargetView(Resource, &RTVDesc, RTV.GetAddressOf());
	resource_assert(RTV.Get());

	return RTV;
}

ComPtr<ID3D11ShaderResourceView> D3DRS::MakeShaderResourceView(ID3D11Resource* Resource, D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc)
{
	HRESULT Result;
	ID3D11Device* Device = GetDevice();

	ComPtr<ID3D11ShaderResourceView> SRV;

	Result = Device->CreateShaderResourceView(Resource, &SRVDesc, SRV.GetAddressOf());
	resource_assert(SRV.Get());

	return SRV;
}

ComPtr<ID3D11UnorderedAccessView> D3DRS::MakeUnorderedAccessView(ID3D11Resource* Resource, D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc)
{
	HRESULT Result;
	ID3D11Device* Device = GetDevice();

	ComPtr<ID3D11UnorderedAccessView> UAV;

	Result = Device->CreateUnorderedAccessView(Resource, &UAVDesc, UAV.GetAddressOf());
	resource_assert(UAV.Get());

	return UAV;
}

ComPtr<ID3D11DepthStencilView> D3DRS::MakeDepthStencilView(ID3D11Resource* Resource, D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc)
{
	HRESULT Result;
	ID3D11Device* Device = GetDevice();

	ComPtr<ID3D11DepthStencilView> DSV;

	Result = Device->CreateDepthStencilView(Resource, &DSVDesc, DSV.GetAddressOf());
	resource_assert(DSV.Get());

	return DSV;
}
