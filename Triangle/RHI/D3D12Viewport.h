#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>

class D3D12Viewport
{
	static const int kNumBackBuffers = 3;

public:
	D3D12Viewport() : D3D12Viewport(1280, 720) {}
	D3D12Viewport(int width, int height);
	virtual ~D3D12Viewport();

	void Initialize(HWND inHWND);
	void Resize(int width, int height);
	void Present();
	void Shutdown();

	inline int GetWidth() { return width; }
	inline int GetHeight() { return height; }

	HRESULT CreateSwapChainHWND(IDXGIFactory2* const factory, ID3D12CommandQueue* const queue, bool hdrDisplay);

private:
	int width;
	int height;

	HWND hwnd;

	IDXGISwapChain3* swapChain3;
	IDXGISwapChain4* swapChain4;

	DXGI_FORMAT GetBackBufferFormat(bool hdr);
	void GetSwapChainDescription(DXGI_SWAP_CHAIN_DESC1& desc, bool transparent, bool hdrDisplay);
};
