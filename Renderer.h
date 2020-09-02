#pragma once

using namespace D3DRS;
using namespace D3DHW;
using namespace DirectX;
using namespace WRL;

class RenderManager
{
	enum RENDERORDER
	{
		FORWARD,
		DEFERRED,
	};

private:
	
	std::vector<shared_ptr<D3DRenderableTexture>> GBuffers;
	
	shared_ptr<D3DRenderableTexture> SwapChainTexture;
	shared_ptr<D3DDepthStencilTexture> SwapChainDepth;

	std::vector<D3D11_VIEWPORT> RenderViewports;
	shared_ptr<D3DHWDevice> Device;

	std::vector<ComPtr<ID3D11RasterizerState>> RasterizerStates;

public:

private:

public:
	RenderManager();
	~RenderManager();

	void AddRenderViewport(float U, float V, UINT Width, UINT Height, float MaxDepth);
	_inline D3D11_VIEWPORT& GetViewport(int Index) { return RenderViewports[Index]; }

	HRESULT GetSwapChainBuffer(UINT Index, shared_ptr<D3DRenderableTexture>& pOutTexture);
	HRESULT GetSwapChainDepthBuffer(shared_ptr<D3DDepthStencilTexture>& pOutTexture);
	
	ID3D11RasterizerState* GetRasterizerState(UINT Index) { if (RasterizerStates.size() < Index || Index < 0) return nullptr; return RasterizerStates[Index].Get(); }

	shared_ptr<D3DRenderableTexture> GetGBuffer(UINT Index) { return GBuffers[Index]; }
	shared_ptr<D3DDepthStencilTexture> GetSwapChainDepthStencil() { return SwapChainDepth; }

	HRESULT SetSwapChainDepthStencil(shared_ptr<D3DDepthStencilTexture> Texture) { if (Texture == nullptr) return E_INVALIDARG; SwapChainDepth = Texture; }
	HRESULT SetSwapChainTexture(shared_ptr<D3DRenderableTexture> Texture) { if (Texture == nullptr) return E_INVALIDARG; SwapChainTexture = Texture; }

	void ClearTexture2D(shared_ptr<D3DRenderableTexture> Texture, XMVECTORF32 Color = Colors::Black);
	void ClearDepthStencil(shared_ptr<D3DDepthStencilTexture> DepthStencil);

	void SelectRenderTarget(ID3D11RenderTargetView** RTVs, UINT Count, ID3D11DepthStencilView* DSV = nullptr);

	void CreateRasterizerState(D3D11_CULL_MODE CullMode, D3D11_FILL_MODE FillMode, bool Clockwise );

	void FlushCommand(ID3D11DeviceContext* Context);

	void Execute();

	
};

