#include "pch.h"

#ifdef WINDOWS
#include "core/platform.h"
#include "core/event.h"

#include <Windows.h>
#include <Windowsx.h>

#define CLASS_NAME L"Core"

typedef struct {
	platform_specification spec;
	HWND window_handle;

	f64 clock_frequency;
	LARGE_INTEGER clock_start;
} internal_state;
static internal_state s_state;

LRESULT msg_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		return 0;
	}
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		return 0;
	}
	case WM_CHAR:
	{
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		event_context context = { 0 };
		context.mouse_button_pressed.button = MOUSE_BUTTON_RIGHT;
		event e = event_create(EVENT_TYPE_MOUSE_BUTTON_PRESSED, context);
		s_state.spec.msg_callback(e);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		event_context context = { 0 };
		context.mouse_button_pressed.button = MOUSE_BUTTON_MIDDLE;
		event e = event_create(EVENT_TYPE_MOUSE_BUTTON_PRESSED, context);
		s_state.spec.msg_callback(e);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		event_context context = { 0 };
		context.mouse_button_pressed.button = MOUSE_BUTTON_LEFT;
		event e = event_create(EVENT_TYPE_MOUSE_BUTTON_PRESSED, context);
		s_state.spec.msg_callback(e);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		event_context context = { 0 };
		context.mouse_button_pressed.button = MOUSE_BUTTON_RIGHT;
		event e = event_create(EVENT_TYPE_MOUSE_BUTTON_RELEASED, context);
		s_state.spec.msg_callback(e);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		event_context context = { 0 };
		context.mouse_button_pressed.button = MOUSE_BUTTON_MIDDLE;
		event e = event_create(EVENT_TYPE_MOUSE_BUTTON_RELEASED, context);
		s_state.spec.msg_callback(e);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		event_context context = { 0 };
		context.mouse_button_pressed.button = MOUSE_BUTTON_LEFT;
		event e = event_create(EVENT_TYPE_MOUSE_BUTTON_RELEASED, context);
		s_state.spec.msg_callback(e);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		event_context context = { 0 };
		context.mouse_moved.x = GET_X_LPARAM(lParam);
		context.mouse_moved.y = GET_Y_LPARAM(lParam);
		event e = event_create(EVENT_TYPE_MOUSE_MOVED, context);
		s_state.spec.msg_callback(e);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		event_context context = { 0 };
		// (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA
		context.mouse_scrolled.zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		event e = event_create(EVENT_TYPE_MOUSE_SCROLLED, context);
		s_state.spec.msg_callback(e);
		return 0;
	}
	default:
		return DefWindowProcA(hWnd, msg, wParam, lParam);
	}
}

void platform_init(platform_specification* spec)
{
	s_state.spec = *spec;
	WNDCLASSEXA wndClass = {
		sizeof(WNDCLASSEXA),
		CS_OWNDC,
		msg_proc,
		0,
		0,
		GetModuleHandle(0),
		NULL,
		NULL,
		NULL,
		NULL,
		CLASS_NAME,
		NULL
	};

	b8 result = RegisterClassExA(&wndClass);

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

	s_state.window_handle = CreateWindowExA(
		0,
		wndClass.lpszClassName,
		s_state.spec.name,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		wndClass.hInstance,
		NULL
	);

	CORE_ASSERT(s_state.window_handle, "platform_init - CreateWindow Failed");

	ShowWindow(s_state.window_handle, SW_SHOW);

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	s_state.clock_frequency = 1.0f / (f64)frequency.QuadPart;
	QueryPerformanceCounter(&s_state.clock_start);
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

f64 platform_get_time()
{
	LARGE_INTEGER now_time;
	QueryPerformanceCounter(&now_time);
	return (f64)(now_time.QuadPart - s_state.clock_start.QuadPart) * s_state.clock_frequency;
}

// Memory
void platform_zero_memory(void* mem, u64 size)
{
	memset(mem, 0, size);
}

void* platform_allocate(u64 size, u8 alignment)
{
	return malloc(size);
}

void platform_free(void* mem, u8 alignment)
{
	free(mem);
}

void platform_copy_memory(void* dest, void* src, u64 size)
{
	memcpy(dest, src, size);
}

#endif