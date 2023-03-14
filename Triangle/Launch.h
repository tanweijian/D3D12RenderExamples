#pragma once

#include <string>
#include <Windows.h>

#include "LogSystem.h"
#include "EngineLoop.h"

namespace Entry
{
	int RunApplication(EngineLoop& engine, const wchar_t* name, HINSTANCE hInstance, int nCmdShow);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool InitializeEngine(EngineLoop& engine, HWND hwnd);
	bool UpdateEngine(EngineLoop& engine);
	bool TerminateEngine(EngineLoop& engine);
	void OpenConsole();
	void CloseConsole();

	int RunApplication(EngineLoop& engine, const wchar_t* name, HINSTANCE hInstance, int nCmdShow)
	{
		OpenConsole();

		WNDCLASSEXW wcex{};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WindowProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = name;
		ATOM result = ::RegisterClassExW(&wcex);
		if (result == 0)
		{
			return -1;
		}

		int width, height;
		engine.GetWindowsSize(width, height);
		RECT rect = { 0L, 0L, (LONG)width, (LONG)height };
		::AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

		HWND hwnd = ::CreateWindowExW(0, name, name, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, &engine);

		InitializeEngine(engine, hwnd);

		::ShowWindow(hwnd, SW_SHOW);
		::SetForegroundWindow(hwnd);
		::SetFocus(hwnd);

		do
		{
			MSG msg = {};
			BOOL exit = false;
			while (::PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessageW(&msg);
				if (msg.message == WM_QUIT)
				{
					exit = true;
					break;
				}
			}
			if (exit) break;

		} while (UpdateEngine(engine));

		TerminateEngine(engine);

		CloseConsole();

		return 0;
	}

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		EngineLoop* engine = reinterpret_cast<EngineLoop*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		switch (uMsg)
		{
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;

		default:
			return ::DefWindowProcW(hwnd, uMsg, wParam, lParam);
		}
		return 0;
	}

	bool InitializeEngine(EngineLoop& engine, HWND hwnd)
	{
		engine.Initialize();
		return true;
	}

	bool UpdateEngine(EngineLoop& engine)
	{
		engine.Tick();
		return true;
	}

	bool TerminateEngine(EngineLoop& engine)
	{
		engine.Shutdown();
		return true;
	}

	void OpenConsole()
	{
		AllocConsole();
		SetConsoleOutputCP(65001);
	}

	void CloseConsole()
	{
		FreeConsole();
	}
}
