module;

#include "../enum_class.hpp"

#include <GLFW/glfw3.h>

export module keycap.window : input_mappings;

namespace keycap
{
    /// <summary>
    /// Represents a state an input can be in
    /// </summary>
    export enum class input_action {
        /// <summary>
        /// This should not be possible and hints at uninitialized data
        /// </summary>
        none = -1,

        /// <summary>
        /// An input is released (e.g. a button is not pressed)
        /// </summary>
        release = GLFW_RELEASE,

        /// <summary>
        /// An input is pressed
        /// </summary>
        press = GLFW_PRESS,

        /// <summary>
        /// An input is being repeated (while holding down a button)
        /// </summary>
        repeat = GLFW_REPEAT,
    };

    /// <summary>
    /// Modifiers on the keyboard that can be pressed alongside an input. May be used as a mask to denote multiple
    /// active modifiers
    /// </summary>
    export enum class input_modifiers {
        /// <summary>
        /// No modifier is pressed
        /// </summary>
        none = 0,

        /// <summary>
        /// Shift key
        /// </summary>
        shift = GLFW_MOD_SHIFT,

        /// <summary>
        /// Control (Ctrl) key
        /// </summary>
        control = GLFW_MOD_CONTROL,

        /// <summary>
        /// Alt key
        /// </summary>
        alt = GLFW_MOD_ALT,

        /// <summary>
        /// Super (Windows) key
        /// </summary>
        super = GLFW_MOD_SUPER,

        /// <summary>
        /// Capslock key
        /// </summary>
        capslock = GLFW_MOD_CAPS_LOCK,

        /// <summary>
        /// Numlock (Num) key
        /// </summary>
        numlock = GLFW_MOD_NUM_LOCK,
    };
    export enable_bitmask_operators(input_modifiers);

    /// <summary>
    /// An input button on a mouse
    /// </summary>
    export enum class mouse_button {
        /// <summary>
        /// Should not be possible and hints at uninitialized data
        /// </summary>
        none = -1,

        button_1 = GLFW_MOUSE_BUTTON_1,
        button_2 = GLFW_MOUSE_BUTTON_2,
        button_3 = GLFW_MOUSE_BUTTON_3,
        button_4 = GLFW_MOUSE_BUTTON_4,
        button_5 = GLFW_MOUSE_BUTTON_5,
        button_6 = GLFW_MOUSE_BUTTON_6,
        button_7 = GLFW_MOUSE_BUTTON_7,
        button_8 = GLFW_MOUSE_BUTTON_8,

        left = GLFW_MOUSE_BUTTON_1,
        right = GLFW_MOUSE_BUTTON_2,
        middle = GLFW_MOUSE_BUTTON_3,
    };

    /// <summary>
    /// May be used as a mask to denote multiple active hats
    /// </summary>
    enum class joystick_hat
    {
        centered = GLFW_HAT_CENTERED,

        up = GLFW_HAT_UP,
        down = GLFW_HAT_DOWN,

        right = GLFW_HAT_RIGHT,
        left = GLFW_HAT_LEFT,

        right_up = GLFW_HAT_RIGHT_UP,
        right_down = GLFW_HAT_RIGHT_DOWN,

        left_up = GLFW_HAT_LEFT_UP,
        left_down = GLFW_HAT_LEFT_DOWN,
    };
    export enable_bitmask_operators(joystick_hat);

    /// <summary>
    /// An input button on a joystick
    /// </summary>
    export enum class joystick_button {
        none = -1,
        button1 = GLFW_JOYSTICK_1,
        button2 = GLFW_JOYSTICK_2,
        button3 = GLFW_JOYSTICK_3,
        button4 = GLFW_JOYSTICK_4,
        button5 = GLFW_JOYSTICK_5,
        button6 = GLFW_JOYSTICK_6,
        button7 = GLFW_JOYSTICK_7,
        button8 = GLFW_JOYSTICK_8,
        button9 = GLFW_JOYSTICK_9,
        button10 = GLFW_JOYSTICK_10,
        button11 = GLFW_JOYSTICK_11,
        button12 = GLFW_JOYSTICK_12,
        button13 = GLFW_JOYSTICK_13,
        button14 = GLFW_JOYSTICK_14,
        button15 = GLFW_JOYSTICK_15,
        button16 = GLFW_JOYSTICK_16,
    };

    /// <summary>
    /// An input button on a gamepad
    /// </summary>
    export enum class gamepad_button {
        none = -1,
        a = GLFW_GAMEPAD_BUTTON_A,
        b = GLFW_GAMEPAD_BUTTON_B,
        x = GLFW_GAMEPAD_BUTTON_X,
        y = GLFW_GAMEPAD_BUTTON_Y,

        left_bumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
        right_bumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,

        back = GLFW_GAMEPAD_BUTTON_BACK,
        start = GLFW_GAMEPAD_BUTTON_START,
        guide = GLFW_GAMEPAD_BUTTON_GUIDE,

        left_thumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
        right_thumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,

        dpad_up = GLFW_GAMEPAD_BUTTON_DPAD_UP,
        dpad_right = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
        dpad_down = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
        dpad_left = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,

        cross = a,
        circle = b,
        square = x,
        triangle = y,
    };

    /// <summary>
    /// An input axis on a gamepad
    /// </summary>
    export enum class gamepad_axis {
        none = -1,

        left_x = GLFW_GAMEPAD_AXIS_LEFT_X,
        left_y = GLFW_GAMEPAD_AXIS_LEFT_Y,

        right_x = GLFW_GAMEPAD_AXIS_RIGHT_X,
        right_y = GLFW_GAMEPAD_AXIS_RIGHT_Y,

        left_trigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
        right_trigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
    };

    /// <summary>
    /// An input key on a keyboard
    /// </summary>
    export enum class key {
        /* The unknown key */
        key_unknown = GLFW_KEY_UNKNOWN - 1,

        /* Printable keys */
        key_space = GLFW_KEY_SPACE,
        key_apostrophe = GLFW_KEY_APOSTROPHE,
        key_comma = GLFW_KEY_COMMA,
        key_minus = GLFW_KEY_MINUS,
        key_period = GLFW_KEY_PERIOD,
        key_slash = GLFW_KEY_SLASH,
        key_0 = GLFW_KEY_0,
        key_1 = GLFW_KEY_1,
        key_2 = GLFW_KEY_2,
        key_3 = GLFW_KEY_3,
        key_4 = GLFW_KEY_4,
        key_5 = GLFW_KEY_5,
        key_6 = GLFW_KEY_6,
        key_7 = GLFW_KEY_7,
        key_8 = GLFW_KEY_8,
        key_9 = GLFW_KEY_9,
        key_semicolon = GLFW_KEY_SEMICOLON,
        key_equal = GLFW_KEY_EQUAL,
        key_a = GLFW_KEY_A,
        key_b = GLFW_KEY_B,
        key_c = GLFW_KEY_C,
        key_d = GLFW_KEY_D,
        key_e = GLFW_KEY_E,
        key_f = GLFW_KEY_F,
        key_g = GLFW_KEY_G,
        key_h = GLFW_KEY_H,
        key_i = GLFW_KEY_I,
        key_j = GLFW_KEY_J,
        key_k = GLFW_KEY_K,
        key_l = GLFW_KEY_L,
        key_m = GLFW_KEY_M,
        key_n = GLFW_KEY_N,
        key_o = GLFW_KEY_O,
        key_p = GLFW_KEY_P,
        key_q = GLFW_KEY_Q,
        key_r = GLFW_KEY_R,
        key_s = GLFW_KEY_S,
        key_t = GLFW_KEY_T,
        key_u = GLFW_KEY_U,
        key_v = GLFW_KEY_V,
        key_w = GLFW_KEY_W,
        key_x = GLFW_KEY_X,
        key_y = GLFW_KEY_Y,
        key_z = GLFW_KEY_Z,
        key_left_bracket = GLFW_KEY_LEFT_BRACKET,
        key_backslash = GLFW_KEY_BACKSLASH,
        key_right_bracket = GLFW_KEY_RIGHT_BRACKET,
        key_grave_accent = GLFW_KEY_GRAVE_ACCENT,
        key_world_1 = GLFW_KEY_WORLD_1,
        key_world_2 = GLFW_KEY_WORLD_2,

        /* Function keys */
        key_escape = GLFW_KEY_ESCAPE,
        key_enter = GLFW_KEY_ENTER,
        key_tab = GLFW_KEY_TAB,
        key_backspace = GLFW_KEY_BACKSPACE,
        key_insert = GLFW_KEY_INSERT,
        key_delete = GLFW_KEY_DELETE,
        key_right = GLFW_KEY_RIGHT,
        key_left = GLFW_KEY_LEFT,
        key_down = GLFW_KEY_DOWN,
        key_up = GLFW_KEY_UP,
        key_page_up = GLFW_KEY_PAGE_UP,
        key_page_down = GLFW_KEY_PAGE_DOWN,
        key_home = GLFW_KEY_HOME,
        key_end = GLFW_KEY_END,
        key_caps_lock = GLFW_KEY_CAPS_LOCK,
        key_scroll_lock = GLFW_KEY_SCROLL_LOCK,
        key_num_lock = GLFW_KEY_NUM_LOCK,
        key_print_screen = GLFW_KEY_PRINT_SCREEN,
        key_pause = GLFW_KEY_PAUSE,
        key_f1 = GLFW_KEY_F1,
        key_f2 = GLFW_KEY_F2,
        key_f3 = GLFW_KEY_F3,
        key_f4 = GLFW_KEY_F4,
        key_f5 = GLFW_KEY_F5,
        key_f6 = GLFW_KEY_F6,
        key_f7 = GLFW_KEY_F7,
        key_f8 = GLFW_KEY_F8,
        key_f9 = GLFW_KEY_F9,
        key_f10 = GLFW_KEY_F10,
        key_f11 = GLFW_KEY_F11,
        key_f12 = GLFW_KEY_F12,
        key_f13 = GLFW_KEY_F13,
        key_f14 = GLFW_KEY_F14,
        key_f15 = GLFW_KEY_F15,
        key_f16 = GLFW_KEY_F16,
        key_f17 = GLFW_KEY_F17,
        key_f18 = GLFW_KEY_F18,
        key_f19 = GLFW_KEY_F19,
        key_f20 = GLFW_KEY_F20,
        key_f21 = GLFW_KEY_F21,
        key_f22 = GLFW_KEY_F22,
        key_f23 = GLFW_KEY_F23,
        key_f24 = GLFW_KEY_F24,
        key_f25 = GLFW_KEY_F25,
        key_kp_0 = GLFW_KEY_KP_0,
        key_kp_1 = GLFW_KEY_KP_1,
        key_kp_2 = GLFW_KEY_KP_2,
        key_kp_3 = GLFW_KEY_KP_3,
        key_kp_4 = GLFW_KEY_KP_4,
        key_kp_5 = GLFW_KEY_KP_5,
        key_kp_6 = GLFW_KEY_KP_6,
        key_kp_7 = GLFW_KEY_KP_7,
        key_kp_8 = GLFW_KEY_KP_8,
        key_kp_9 = GLFW_KEY_KP_9,
        key_kp_decimal = GLFW_KEY_KP_DECIMAL,
        key_kp_divide = GLFW_KEY_KP_DIVIDE,
        key_kp_multiply = GLFW_KEY_KP_MULTIPLY,
        key_kp_subtract = GLFW_KEY_KP_SUBTRACT,
        key_kp_add = GLFW_KEY_KP_ADD,
        key_kp_enter = GLFW_KEY_KP_ENTER,
        key_kp_equal = GLFW_KEY_KP_EQUAL,
        key_left_shift = GLFW_KEY_LEFT_SHIFT,
        key_left_control = GLFW_KEY_LEFT_CONTROL,
        key_left_alt = GLFW_KEY_LEFT_ALT,
        key_left_super = GLFW_KEY_LEFT_SUPER,
        key_right_shift = GLFW_KEY_RIGHT_SHIFT,
        key_right_control = GLFW_KEY_RIGHT_CONTROL,
        key_right_alt = GLFW_KEY_RIGHT_ALT,
        key_right_super = GLFW_KEY_RIGHT_SUPER,
        key_menu = GLFW_KEY_MENU,
    };
}