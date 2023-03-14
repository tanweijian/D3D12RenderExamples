#include "D3D12RHI.h"

D3D12RHI::D3D12RHI()
{
}

D3D12RHI::~D3D12RHI()
{
}

bool D3D12RHI::Initialize()
{
	HRESULT hr = E_FAIL;
	if (GetD3D12DebugLayerEnabled())
	{
		ID3D12Debug* debugInterface;
		hr = D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface));
		if (SUCCEEDED(hr))
		{
			debugInterface->EnableDebugLayer();
			if (GetD3D12DebugGBV())
			{
				ID3D12Debug1* debugInterface1;
				hr = debugInterface->QueryInterface(IID_PPV_ARGS(&debugInterface1));
				if (SUCCEEDED(hr))
				{
					debugInterface1->SetEnableGPUBasedValidation(true);
					debugInterface1->Release();
				}
			}
			debugInterface->Release();
		}
	}

	IDXGIFactory2* factory;
	{
		hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory));
		if (FAILED(hr))
		{
			__debugbreak();
			return false;
		}
	}

	IDXGIAdapter1* adapter;
	{
		hr = EnumAdapters(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, factory, &adapter);
		if (FAILED(hr))
		{
			__debugbreak();
			return false;
		}
	}

	{
		hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));
		if (FAILED(hr))
		{
			__debugbreak();
			return false;
		}
	}

	{
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		hr = device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue));
		if (FAILED(hr))
		{
			__debugbreak();
			return false;
		}
	}

	{
		/*hr = Display::viewport.CreateSwapChainHWND(factory, commandQueue, false);
		if (FAILED(hr))
		{
			__debugbreak();
			return false;
		}*/
	}

	return true;
}

HRESULT D3D12RHI::EnumAdapters(int adapterIndex, DXGI_GPU_PREFERENCE gpuPreference, IDXGIFactory1* const factory, IDXGIAdapter1** adapter)
{
	HRESULT hr = E_FAIL;
	IDXGIFactory6* dxgiFactory6;
	hr = factory->QueryInterface(&dxgiFactory6);
	if (SUCCEEDED(hr))
	{
		hr = dxgiFactory6->EnumAdapterByGpuPreference(adapterIndex, gpuPreference, IID_PPV_ARGS(adapter));
	}
	else
	{
		hr = factory->EnumAdapters1(adapterIndex, adapter);
	}
	return hr;
}

bool D3D12RHI::Shutdown()
{
	return true;
}

bool D3D12RHI::GetD3D12DebugLayerEnabled()
{
#if defined(_DEBUG)
	return true;
#else
	return debugLayerEnable;
#endif
}

bool D3D12RHI::GetD3D12DebugGBV()
{
	return enableGBV;
}
