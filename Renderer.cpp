#include"pch.h"
#include "Renderer.h"

using namespace WRL;
// 단일 렌더타겟 자원을 지정한 Color 로 Clear 합니다.
void RenderManager::ClearTexture2D(shared_ptr<D3DRenderableTexture> Texture, XMVECTORF32 Color)
{
	static auto Context = GetAwaitingContext();
	
	Context->ClearRenderTargetView(*Texture->GetResource(), Color);

	FlushCommand(Context);

	
}

// 단일 깊이-스텐실 자원을 Clear 합니다.
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
	// 하드웨어를 초기화합니다.
	Device = D3DHWDevice::GetHWDevice();

}

RenderManager::~RenderManager()
{
	
}

// 사용자가 지정한 뷰포트를 추가합니다.
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

// 스왑체인 인터페이스로부터 버퍼를 받아옵니다.
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

// 인자로 전달받는 Deferred-Context에 예약된 명령들을 전부 Flush 하여 명령목록에 기록합니다.
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

// 대기중인 모든 ID3D11CommandList 들의 명령을 Immediate-Context로 전달하여 한 번에 실행시킵니다.
void RenderManager::Execute()
{
	static ID3D11DeviceContext* Context = GetContext();
	ComPtr<ID3D11CommandList>* Cmds = Device->GetDeferredCommandLists();


	for (int i = 0; i < D3DHWDevice::GetCurrentContext(); i++)
	{
		Context->ExecuteCommandList(Cmds[i].Get(), false);
	}
}
// *위와 같은 구조를 이용하여 불필요한 DrawCall을 최소화합니다.