#include "D3D12Viewport.h"

D3D12Viewport::D3D12Viewport(int inWidth, int inHeight) : width(inWidth), height(inHeight)
{
}

D3D12Viewport::~D3D12Viewport()
{
	if (swapChain3 != nullptr)
	{
		swapChain3->Release();
	}
	if (swapChain4 != nullptr)
	{
		swapChain4->Release();
	}
}

void D3D12Viewport::Initialize(HWND inHWND)
{
	hwnd = inHWND;
}

void D3D12Viewport::Resize(int width, int height)
{
}

void D3D12Viewport::Present()
{
}

void D3D12Viewport::Shutdown()
{
}

HRESULT D3D12Viewport::CreateSwapChainHWND(IDXGIFactory2* const factory, ID3D12CommandQueue* const queue, bool hdrDisplay)
{
	HRESULT hr = E_FAIL;
	DXGI_SWAP_CHAIN_DESC1 desc = {};
	GetSwapChainDescription(desc, false, hdrDisplay);
	IDXGISwapChain1* swapChain1;
	hr = factory->CreateSwapChainForHwnd(queue, hwnd, &desc, nullptr, nullptr, &swapChain1);
	if (SUCCEEDED(hr))
	{
		swapChain1->QueryInterface(&swapChain3);
		swapChain1->QueryInterface(&swapChain4);
		swapChain1->Release();
	}
	return hr;
}

DXGI_FORMAT D3D12Viewport::GetBackBufferFormat(bool hdr)
{
	if (hdr)
	{
		return DXGI_FORMAT_R16G16B16A16_FLOAT;
	}
	else
	{
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}
}

void D3D12Viewport::GetSwapChainDescription(DXGI_SWAP_CHAIN_DESC1& desc, bool transparent, bool hdrDisplay)
{
	desc.Stereo = false;
	desc.BufferCount = kNumBackBuffers;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	desc.Width = GetWidth();
	desc.Height = GetHeight();
	desc.Format = GetBackBufferFormat(hdrDisplay);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Scaling = DXGI_SCALING_STRETCH;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
	desc.AlphaMode = transparent ? DXGI_ALPHA_MODE_PREMULTIPLIED : DXGI_ALPHA_MODE_UNSPECIFIED;
}
