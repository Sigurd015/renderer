#include "pch.h"
#include "input.h"
#include "core/platform.h"

b8 input_is_key(key_code key)
{
	return platform_is_key(key);
}

b8 input_is_key_down(key_code key)
{
	return platform_is_key_down(key);
}

b8 input_is_mouse_button(mouse_button button)
{
	return platform_is_mouse_button(button);
}

b8 input_is_mouse_button_down(mouse_button button)
{
	return platform_is_mouse_button_down(button);
}

vec2 input_get_mouse_position()
{
	return platform_get_mouse_position();
}

void input_set_cursor(b8 visible)
{
	platform_set_cursor(visible);
}