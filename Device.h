#pragma once

using namespace std;
using namespace Microsoft;
using namespace WRL;
#define MAXCONTEXTS 8 // 최대 컨텍스트 수를 관리합니다.

// 하드웨어 자원은 모두 D3DHW 네임스페이스에서 관리됩니다.
namespace D3DHW
{
	struct D3DHWDevice : VirtualObject
	{
	private:
		WRL::ComPtr<ID3D11Device> DeviceInstance;
		WRL::ComPtr<ID3D11DeviceContext> ImmediateContextInstance;
		WRL::ComPtr<ID3D11DeviceContext>* DeferredContextInstances;
		WRL::ComPtr<ID3D11CommandList>* DeferredCommandLists;
		WRL::ComPtr<IDXGISwapChain> SwapChainInstance;

		std::map<ComPtr<ID3D11DeviceContext>, ComPtr<ID3D11CommandList>> ContextCommandMap;

		static shared_ptr<D3DHWDevice> pDevice;
		int CurrentContext = 0;
	public:

	private:

		D3DHWDevice(UINT Width, UINT Height, HINSTANCE hInstance, HWND hWnd)
		{
		#ifdef _DEBUG
			DWORD Flag = D3D11_CREATE_DEVICE_DEBUG;
		#endif
			HRESULT Result;

			D3D_FEATURE_LEVEL FeatureLevels[] = {
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0
			};

			DXGI_SWAP_CHAIN_DESC SCDesc{};
			SCDesc.OutputWindow = hWnd;
			SCDesc.BufferDesc.Width = Width;
			SCDesc.BufferDesc.Height = Height;
			SCDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			SCDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			SCDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			SCDesc.BufferCount = 1;
			SCDesc.BufferDesc.RefreshRate.Numerator = 60;
			SCDesc.BufferDesc.RefreshRate.Denominator = 1;
			SCDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SCDesc.SampleDesc.Count = 1;
			SCDesc.SampleDesc.Quality = 0;
			SCDesc.Windowed = true;
			SCDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			Result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, Flag, nullptr, 0,
												   D3D11_SDK_VERSION, &SCDesc, SwapChainInstance.GetAddressOf(), DeviceInstance.GetAddressOf(), &FeatureLevels[0], ImmediateContextInstance.GetAddressOf());
			assert(Result == S_OK);
		
			DeferredContextInstances = new WRL::ComPtr<ID3D11DeviceContext>[MAXCONTEXTS];
			DeferredCommandLists = new WRL::ComPtr<ID3D11CommandList>[MAXCONTEXTS];

			for (int i = 0; i < MAXCONTEXTS; i++)
			{
				DeviceInstance->CreateDeferredContext(0, DeferredContextInstances[i].GetAddressOf());
				device_assert(DeferredContextInstances[i].Get());
			
				ContextCommandMap.insert_or_assign(DeferredContextInstances[i], DeferredCommandLists[i]);
			}
		
			//std::reverse(ContextCommandMap.begin(), ContextCommandMap.end());
		};

	public: // 전역 함수
		_inline static shared_ptr<D3DHWDevice> GetHWDevice()
		{
			if (pDevice == nullptr)
				pDevice = make_shared<D3DHWDevice>(D3DHWDevice(BIWidth, BIHeight, BIAppHandleInst, BIAppWindowHandle));

			return pDevice;
		}

		_inline static auto GetContext() { return GetHWDevice()->ImmediateContextInstance.Get(); }
		_inline static auto GetDevice() { return GetHWDevice()->DeviceInstance.Get(); }
		_inline static auto GetSwapChain() { return GetHWDevice()->SwapChainInstance.Get(); }
		_inline static auto GetDeferredContexts() { return GetHWDevice()->DeferredContextInstances->GetAddressOf(); }
		_inline static auto GetDeferredCommandLists() { return GetHWDevice()->DeferredCommandLists; }

		inline static auto& GetContextCommandMap() { return GetHWDevice()->ContextCommandMap; }
		_inline static int GetCurrentContext() { return GetHWDevice()->CurrentContext; }
		
		_inline static void AddCurrentContext() { GetHWDevice()->CurrentContext++; }
		_inline static void SetCurrentContext(int i) { GetHWDevice()->CurrentContext = i; }
		
		virtual bool OnInit() override;
		virtual void OnUpdate(float Delta) override;
		virtual void OnRender(float Delta) override;
		virtual void OnRelease() override;

	};

	_inline ID3D11Device* GetDevice() { return D3DHWDevice::GetDevice(); }
	_inline ID3D11DeviceContext* GetContext() {	return D3DHWDevice::GetContext(); }
	_inline IDXGISwapChain* GetSwapChain() { return D3DHWDevice::GetSwapChain(); }

	_inline ID3D11DeviceContext* GetAwaitingContext()
	{
		return D3DHWDevice::GetDeferredContexts()[D3DHWDevice::GetCurrentContext()];

	}

	inline auto GetCommandListByContext(ID3D11DeviceContext* Context) { return &D3DHWDevice::GetContextCommandMap()[Context]; }
}
