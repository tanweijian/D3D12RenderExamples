#pragma once

#include <d3dx12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>

using namespace DirectX;

class D3D12RHI final
{
	static const int NumBackBuffers = 3;

public:
	D3D12RHI();
	virtual ~D3D12RHI();

	bool Initialize();
	bool Shutdown();

	bool GetD3D12DebugLayerEnabled();
	bool GetD3D12DebugGBV();

private:
	bool debugLayerEnable;
	bool enableGBV;

	struct Vertex
	{
		XMFLOAT3 mPosition;
		XMFLOAT4 mColor;
	};

	CD3DX12_VIEWPORT viewPort;
	CD3DX12_RECT scissorRect;

	ID3D12Device* device;

	ID3D12RootSignature* rootSignature;
	ID3D12PipelineState* pipelineState;
	ID3D12DescriptorHeap* rtvHeap;

	ID3D12Resource* renderTargets[NumBackBuffers];

	ID3D12CommandAllocator* commandAllocator;
	ID3D12CommandQueue* commandQueue;
	ID3D12GraphicsCommandList* commandList;

	HRESULT EnumAdapters(int adapterIndex, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory1* const factory, IDXGIAdapter1** adapter);
};
