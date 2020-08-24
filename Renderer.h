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

public:

private:

public:
	RenderManager();
	~RenderManager();

	void AddRenderViewport(float U, float V, UINT Width, UINT Height, float MaxDepth);
	_inline D3D11_VIEWPORT& GetViewport(int Index) { return RenderViewports[Index]; }

	shared_ptr<D3DRenderableTexture> GetSwapChainBuffer(UINT Index = 0);
	shared_ptr<D3DDepthStencilTexture> GetSwapChainDepthBuffer();

	shared_ptr<D3DRenderableTexture> GetGBuffer(UINT Index) { return GBuffers[Index]; }
	shared_ptr<D3DDepthStencilTexture> GetSwapChainDepthStencil() { return SwapChainDepth; }

	void ClearTexture2D(shared_ptr<D3DRenderableTexture> Texture, XMVECTORF32 Color = Colors::Black);
	void ClearDepthStencil(shared_ptr<D3DDepthStencilTexture> DepthStencil);

	void FlushCommand(ID3D11DeviceContext* Context);

	void Execute();

	
};

