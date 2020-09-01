#include"pch.h"
#include "Renderer.h"

using namespace WRL;
// ���� ����Ÿ�� �ڿ��� ������ Color �� Clear �մϴ�.
void RenderManager::ClearTexture2D(shared_ptr<D3DRenderableTexture> Texture, XMVECTORF32 Color)
{
	static auto Context = GetAwaitingContext();
	
	Context->ClearRenderTargetView(*Texture->GetResource(), Color);

	FlushCommand(Context);

	
}

// ���� ����-���ٽ� �ڿ��� Clear �մϴ�.
void RenderManager::ClearDepthStencil(shared_ptr<D3DDepthStencilTexture> DepthStencil)
{
	static auto Context = GetAwaitingContext();
	
	Context->ClearDepthStencilView(*DepthStencil->GetResource(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void RenderManager::SelectRenderTarget(ID3D11RenderTargetView** RTVs, UINT Count, ID3D11DepthStencilView* DSV)
{
	auto Context = GetContext();

	Context->OMSetRenderTargets(Count, RTVs, DSV);

}

RenderManager::RenderManager()
{
	// �ϵ��� �ʱ�ȭ�մϴ�.
	Device = D3DHWDevice::GetHWDevice();

}

RenderManager::~RenderManager()
{
	
}

// ����ڰ� ������ ����Ʈ�� �߰��մϴ�.
void RenderManager::AddRenderViewport(float U, float V, UINT Width, UINT Height, float MaxDepth)
{
	D3D11_VIEWPORT Viewport;

	Viewport.TopLeftX = U;
	Viewport.TopLeftY = V;
	Viewport.Width = Width;
	Viewport.Height = Height;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = MaxDepth;

	RenderViewports.push_back(Viewport);

}

// ����ü�� �������̽��κ��� ���۸� �޾ƿɴϴ�.
HRESULT RenderManager::GetSwapChainBuffer(UINT Index, shared_ptr<D3DRenderableTexture>& pOutTexture)
{
	HRESULT Result;
	/*if (SwapChainTexture != nullptr)
		return S_OK;
*/
	pOutTexture = make_shared<D3DRenderableTexture>(D3DRenderableTexture());

	pOutTexture->MakeSwapChainBuffer(DXGI_FORMAT_R8G8B8A8_UNORM, BIWidth, BIHeight, Index);
	
	return S_OK;
}

HRESULT RenderManager::GetSwapChainDepthBuffer(shared_ptr<D3DDepthStencilTexture>& pOutTexture)
{

	if (SwapChainDepth != nullptr)
		return S_OK;

	pOutTexture = make_shared<D3DDepthStencilTexture>();

	pOutTexture->MakeTexture2D<D3DDepthStencilTexture>(DXGI_FORMAT_R24G8_TYPELESS,
												   BIWidth, BIHeight,
												   D3D11_BIND_DEPTH_STENCIL);

	
	return S_OK;
}

// ���ڷ� ���޹޴� Deferred-Context�� ����� ��ɵ��� ���� Flush �Ͽ� ��ɸ�Ͽ� ����մϴ�.
void RenderManager::FlushCommand(ID3D11DeviceContext* Context)
{
	HRESULT Result;
	auto Cmds = Device->GetDeferredCommandLists();
	auto Index = D3DHWDevice::GetCurrentContext();

	if (D3DHWDevice::GetCurrentContext() >= MAXCONTEXTS)
		D3DHWDevice::SetCurrentContext(0);
	else
		D3DHWDevice::AddCurrentContext();

	Result = Context->FinishCommandList(false, Cmds[Index].GetAddressOf());
}

// ������� ��� ID3D11CommandList ���� ����� Immediate-Context�� �����Ͽ� �� ���� �����ŵ�ϴ�.
void RenderManager::Execute()
{
	static ID3D11DeviceContext* Context = GetContext();
	ComPtr<ID3D11CommandList>* Cmds = Device->GetDeferredCommandLists();


	for (int i = 0; i < D3DHWDevice::GetCurrentContext(); i++)
	{
		Context->ExecuteCommandList(Cmds[i].Get(), false);
	}
}
// *���� ���� ������ �̿��Ͽ� ���ʿ��� DrawCall�� �ּ�ȭ�մϴ�.