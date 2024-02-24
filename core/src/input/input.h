#pragma once
#include "defines.h"
#include "keycode.h"
#include "math/math.h"

b8 input_is_key(key_code key);
b8 input_is_key_down(key_code key);
b8 input_is_mouse_button(mouse_button button);
b8 input_is_mouse_button_down(mouse_button button);
vec2 input_get_mouse_position();
void input_set_cursor(b8 visible);
