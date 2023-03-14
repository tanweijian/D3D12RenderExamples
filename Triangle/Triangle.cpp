#include "Triangle.h"

Triangle::Triangle()
{
	rhi = new D3D12RHI();
	viewport = new D3D12Viewport();
}

Triangle::~Triangle()
{
	delete rhi, viewport;
	rhi = nullptr;
	viewport = nullptr;
}

void Triangle::Initialize()
{
	rhi->Initialize();
}

void Triangle::Tick()
{
}

void Triangle::Shutdown()
{
}

void Triangle::GetWindowsSize(int& width, int& height)
{
	 width = viewport->GetWidth();
	 height = viewport->GetHeight();
}
