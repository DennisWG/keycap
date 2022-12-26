module;

#include <filesystem>
#include <vector>

export module keycap.window : input_events;

import : input_mappings;

namespace keycap
{
    /// <summary>
    /// The base class containing information that's included with every other event
    /// </summary>
    export struct input_event
    {
        /// <summary>
        /// The time when this event was fired
        /// </summary>
        double const time = 0;

        /// <summary>
        /// Was this event handled?
        /// </summary>
        bool handled = false;

        explicit input_event(double time)
          : time{time}
        {
        }
    };

    /// <summary>
    /// This event will be fired whenever the mouse moves within a window owned by the application
    /// </summary>
    export struct mouse_move_event : public input_event
    {
        /// <summary>
        /// The mouse's x-coordinate
        /// </summary>
        float x = 0;

        /// <summary>
        /// The mouse's y-coordinate
        /// </summary>
        float y = 0;

        /// <summary>
        /// The mouse's x-coordinate relative to the last time it moved
        /// </summary>
        float delta_x = 0;

        /// <summary>
        /// The mouse's y-coordinate relative to the last time it moved
        /// </summary>
        float delta_y = 0;

        mouse_move_event(double time, float x, float y, float delta_x, float delta_y)
          : input_event{time}
          , x{x}
          , y{y}
          , delta_x{delta_x}
          , delta_y{delta_y}
        {
        }
    };

    /// <summary>
    /// This event will be fired whenever the mouse wheel is being turned within a window owned by the application
    /// </summary>
    export struct mouse_wheel_event : public input_event
    {
        /// <summary>
        /// The amount the wheel got turned in the x-direction
        /// </summary>
        float x = 0;

        /// <summary>
        /// The amount the wheel got turned in the y-direction
        /// </summary>
        float y = 0;

        mouse_wheel_event(double time, float x, float y)
          : input_event{time}
          , x{x}
          , y{y}
        {
        }
    };

    /// <summary>
    /// This event will be fired whenever a mouse button changes state
    /// </summary>
    export struct mouse_button_event : public input_event
    {
        /// <summary>
        /// The button that changed states
        /// </summary>
        mouse_button button = mouse_button::none;

        /// <summary>
        /// The action representing the changed state
        /// </summary>
        input_action action = input_action::none;

        /// <summary>
        /// A mask of modifiers that was pressed alongside the mouse button
        /// </summary>
        input_modifiers modifiers = input_modifiers::none;

        mouse_button_event(double time, mouse_button button, input_action action, input_modifiers modifiers)
          : input_event{time}
          , button{button}
          , action{action}
          , modifiers{modifiers}
        {
        }
    };

    /// <summary>
    /// This event will be fired whenever a key on the keyboard changes state
    /// </summary>
    export struct keyboard_event : public input_event
    {
        /// <summary>
        /// The key that changed states
        /// </summary>
        key key = keycap::key::key_unknown;

        /// <summary>
        /// The key's scancode
        /// </summary>
        int scancode = 0;

        /// <summary>
        /// The action representing the changed state
        /// </summary>
        input_action action = input_action::none;

        /// <summary>
        /// A mask of modifiers that was pressed alongside the key
        /// </summary>
        input_modifiers modifiers = input_modifiers::none;

        keyboard_event(double time, keycap::key key, int scancode, input_action action, input_modifiers modifiers)
          : input_event{time}
          , key{key}
          , scancode{scancode}
          , action{action}
          , modifiers{modifiers}
        {
        }
    };

    /// <summary>
    /// This event will be fired whenever a number of files was dragged & dropped into the window
    /// </summary>
    export struct drop_files_event : public input_event
    {
        /// <summary>
        /// The files that where dropped into the window
        /// </summary>
        std::vector<std::filesystem::path> files;

        drop_files_event(double time, std::vector<std::filesystem::path> files)
          : input_event{time}
          , files{files}
        {
        }
    };
}