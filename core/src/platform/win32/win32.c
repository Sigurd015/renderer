#include "pch.h"

#ifdef WINDOWS
#include "core/platform.h"
#include "core/event.h"
#include "renderer/renderer.h"

#include <Windows.h>
#include <Windowsx.h>

#define CLASS_NAME L"Core"

typedef struct {
	platform_specification spec;
	HWND window_handle;
	HDC memory_dc;
	byte* back_buffer;

	b8 previous_key_state[256];
	b8 current_key_state[256];

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
	case WM_SIZE:
	{
		// Skip the first WM_SIZE message, it's sent before the window is shown
		{
			static b8 first_time = TRUE;
			if (first_time)
			{
				first_time = FALSE;
				return 0;
			}
		}

		event_context context = { 0 };
		context.wnd_resize.width = LOWORD(lParam);
		context.wnd_resize.height = HIWORD(lParam);
		event e = event_create(EVENT_TYPE_WINDOW_RESIZE, context);
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
		event_context context = { 0 };
		context.key_pressed.key = (key_code)wParam;
		context.key_pressed.repeat = lParam & 0x40000000 ? TRUE : FALSE;
		event e = event_create(EVENT_TYPE_KEY_PRESSED, context);
		s_state.spec.msg_callback(e);
		return 0;
		return 0;
	}
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		event_context context = { 0 };
		context.key_released.key = (key_code)wParam;
		event e = event_create(EVENT_TYPE_KEY_RELEASED, context);
		s_state.spec.msg_callback(e);
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

	// Register Window Class and Create Window
	{
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
	}

	// Create Back Buffer
	{
		HDC window_dc = GetDC(s_state.window_handle);
		s_state.memory_dc = CreateCompatibleDC(window_dc);
		ReleaseDC(s_state.window_handle, window_dc);

		BITMAPINFOHEADER bi_header;
		platform_zero_memory(&bi_header, sizeof(BITMAPINFOHEADER));
		bi_header.biSize = sizeof(BITMAPINFOHEADER);
		bi_header.biWidth = s_state.spec.width;
		bi_header.biHeight = -s_state.spec.height;  /* top-down */
		bi_header.biPlanes = 1;
		bi_header.biBitCount = 32;
		bi_header.biCompression = BI_RGB;
		HBITMAP dib_bitmap = CreateDIBSection(s_state.memory_dc, (BITMAPINFO*)&bi_header,
			DIB_RGB_COLORS, (void**)&s_state.back_buffer, NULL, 0);

		CORE_ASSERT(dib_bitmap, "platform_init - CreateDIBSection Failed");

		HBITMAP old_bitmap = (HBITMAP)SelectObject(s_state.memory_dc, dib_bitmap);
		DeleteObject(old_bitmap);
	}

	// Initialize Renderer and Show Window
	{
		// Notice format is ARGB
		renderer_init(s_state.spec.width, s_state.spec.height, IMAGE_FORMAT_ARGB);

		ShowWindow(s_state.window_handle, SW_SHOW);
	}

	// Clock
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		s_state.clock_frequency = 1.0f / (f64)frequency.QuadPart;
		QueryPerformanceCounter(&s_state.clock_start);
	}
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

	renderer_swap_buffers();
}

void platform_shutdown()
{
	if (s_state.window_handle)
		DestroyWindow(s_state.window_handle);
	if (s_state.memory_dc)
		DeleteDC(s_state.memory_dc);
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

void platform_set_window_title(const char* title)
{
	char temp[256];
	string_format(temp, 256, "%s - %s", s_state.spec.name, title);
	SetWindowTextA(s_state.window_handle, temp);
}

f64 platform_get_time()
{
	LARGE_INTEGER now_time;
	QueryPerformanceCounter(&now_time);
	return (f64)(now_time.QuadPart - s_state.clock_start.QuadPart) * s_state.clock_frequency;
}

f64 platform_get_absolute_time()
{
	LARGE_INTEGER now_time;
	QueryPerformanceCounter(&now_time);
	return (f64)now_time.QuadPart * s_state.clock_frequency;
}

// Input
void platform_input_update()
{
	for (u32 KeyCode = 0; KeyCode < 256; KeyCode++)
	{
		s_state.previous_key_state[KeyCode] = s_state.current_key_state[KeyCode];
		s_state.current_key_state[KeyCode] = (GetAsyncKeyState(KeyCode) & 0x8000) != 0;
	}
}

b8 platform_is_key(key_code key)
{
	return s_state.current_key_state[key] && s_state.previous_key_state[key];
}

b8 platform_is_key_down(key_code key)
{
	return s_state.current_key_state[key] && !s_state.previous_key_state[key];
}

b8 platform_is_mouse_button(mouse_button button)
{
	return s_state.current_key_state[button] && s_state.previous_key_state[button];
}

b8 platform_is_mouse_button_down(mouse_button button)
{
	return s_state.current_key_state[button] && !s_state.previous_key_state[button];
}

vec2 platform_get_mouse_position()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(s_state.window_handle, &point);
	return vec2_create((f32)point.x, (f32)point.y);
}

void platform_set_cursor(b8 visible)
{
	ShowCursor(visible);
}

// Renderer 
void platform_present(image* buffer)
{
	CORE_ASSERT(s_state.spec.width == image_get_width(buffer) &&
		s_state.spec.height == image_get_height(buffer) &&
		image_get_format(buffer) == IMAGE_FORMAT_ARGB,
		"platform_present - Invalid buffer");

	image_copy_to_data(buffer, s_state.back_buffer);

	HDC window_dc = GetDC(s_state.window_handle);
	BitBlt(window_dc, 0, 0, s_state.spec.width, s_state.spec.height, s_state.memory_dc, 0, 0, SRCCOPY);
	ReleaseDC(s_state.window_handle, window_dc);
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