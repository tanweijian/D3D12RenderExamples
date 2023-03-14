#pragma once

#include <string>

class EngineLoop
{
public:
	virtual void Initialize() = 0;
	virtual void Tick() = 0;
	virtual void Shutdown() = 0;

public:
	virtual void GetWindowsSize(int& width, int& height) = 0;
};
