#include "pch.h"

#ifdef WINDOWS
#include "core/platform.h"
#include "core/event.h"

#include <Windows.h>

#define CLASS_NAME L"CORE"

typedef struct {
	platform_specification spec;
	HWND window_handle;
} internal_state;
static internal_state s_state;

LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			event_context context = { 0 };
			event e = event_create(EVENT_TYPE_WINDOW_CLOSE, context);
			s_state.spec.msg_callback(e);
			return 0;
		}
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

void platform_init(platform_specification* spec)
{
	s_state.spec = *spec;
	WNDCLASSEX wndClass = { sizeof(WNDCLASSEX), CS_OWNDC,
			WndProc, 0, 0, GetModuleHandle(0), NULL,
			NULL, NULL, NULL, CLASS_NAME, NULL };

	b8 result = RegisterClassEx(&wndClass);

	CORE_ASSERT(result, "platform_init - RegisterClass Failed");

	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

	if (s_state.spec.minimizable)
		style |= WS_MINIMIZEBOX;

	if (s_state.spec.maximizable)
		style |= WS_MAXIMIZEBOX;

	if (s_state.spec.resizable)
		style |= WS_THICKFRAME;

	RECT rect = { 0, 0, s_state.spec.width, s_state.spec.height };
	AdjustWindowRect(&rect, style, FALSE);

	s_state.window_handle = CreateWindowEx(0, wndClass.lpszClassName, s_state.spec.name,
		style, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, wndClass.hInstance, NULL);

	CORE_ASSERT(s_state.window_handle, "platform_init - CreateWindow Failed");

	ShowWindow(s_state.window_handle, SW_SHOW);
}

void DispatchMsg()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void platform_update()
{
	DispatchMsg();
}

void platform_shutdown()
{
	if (s_state.window_handle)
		DestroyWindow(s_state.window_handle);
}

void* platform_get_window_handle()
{
	return s_state.window_handle;
}

u32 platform_get_window_width()
{
	return s_state.spec.width;
}

u32 platform_get_window_height()
{
	return s_state.spec.height;
}

#endif