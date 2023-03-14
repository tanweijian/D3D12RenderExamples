#pragma once

#include <EngineLoop.h>

#include "RHI/D3D12RHI.h"
#include "RHI/D3D12Viewport.h"

class Triangle final : public EngineLoop
{
public:
	Triangle();
	~Triangle();

	void Initialize() override;
	void Tick() override;
	void Shutdown() override;
	void GetWindowsSize(int& width, int& height) override;

private:
	D3D12RHI* rhi;
	D3D12Viewport* viewport;
};
