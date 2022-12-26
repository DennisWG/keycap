module;

#include <GLFW/glfw3.h>

#include <string>

export module keycap.window : window;
export import : input_events;
export import : input_mappings;
import : fragments;

import keycap.core;

namespace keycap
{
    /// <summary>
    /// Encapsulates the delta time between two frames
    /// </summary>
    export class timestep
    {
      public:
        explicit timestep(float time = 0.f) noexcept
          : time_{time}
        {
        }

        /// <summary>
        /// Returns the delta time in seconds
        /// </summary>
        [[nodiscard]] float seconds() const noexcept
        {
            return time_;
        }

        /// <summary>
        /// Returns the delta time in milliseconds
        /// </summary>
        [[nodiscard]] float milliseconds() const noexcept
        {
            return time_ * 1000.f;
        }

      private:
        float time_ = 0.f;
    };

    class window;

    /// <summary>
    /// An interface that provides entry points that will be called whenever a new frame is ready to be rendered
    /// </summary>
    export struct frame_handler
    {
        virtual ~frame_handler() = default;

        /// <summary>
        /// Will be called whenever a new frame is ready but before on_frame
        /// </summary>
        /// <param name="delta_time">The delta time since the beginning of the last frame</param>
        /// <returns>May return false to skip the subsequent on_frame call</returns>
        [[nodiscard]] virtual bool on_pre_frame(window& window, timestep delta_time) = 0;

        /// <summary>
        /// Will be called whenever a new frame is in flight. Gets called after on_pre_frame and before on_post_frame
        /// </summary>
        /// <param name="delta_time">The delta time since the beginning of the last frame</param>
        virtual void on_frame(window& window, timestep delta_time) = 0;

        /// <summary>
        /// Will be called after on_frame, swapping the buffers and polling events. This is the last call before the
        /// render loop moves to the next iteration
        /// </summary>
        /// <param name="delta_time">The delta time since the beginning of the last frame</param>
        virtual void on_post_frame(window& window, timestep delta_time) = 0;
    };

    /// <summary>
    /// An interface that provides entry points that will be called whenver an input event is handled by the window
    /// </summary>
    export struct input_event_handler
    {
        virtual ~input_event_handler() = default;

        /// <summary>
        /// Will be called whenever the mouse was moved within the window
        /// </summary>
        virtual void on_mouse_move(mouse_move_event event) = 0;

        /// <summary>
        /// Will be called whenever the mouse wheel was turned within the window
        /// </summary>
        virtual void on_mouse_wheel(mouse_wheel_event event) = 0;

        /// <summary>
        /// Will be called whenever a mouse button changed state within the window
        /// </summary>
        virtual void on_mouse_button(mouse_button_event event) = 0;

        /// <summary>
        /// Will be called whenever a key on the keyboard changed state within the window
        /// </summary>
        virtual void on_keyboard(keyboard_event event) = 0;

        /// <summary>
        /// Will be called whenever a number of files was dragged & dropped into the window
        /// </summary>
        virtual void on_drop_files(drop_files_event event) = 0;
    };

    export struct window_creation_parameters
    {
        std::string title = "Window";
        u32 width = 0;
        u32 height = 0;
        bool resizable = false;
        bool maximize = true;
    };

    /// <summary>
    /// A window. What else is there to say?
    /// </summary>
    export class window
    {
        friend class window_context;

      public:
        ~window() noexcept
        {
            glfwDestroyWindow(window_);
        }

        /// <summary>
        /// Registers the given input_event_handler to handle all incoming input events
        /// </summary>
        void register_input_events(input_event_handler& input_handler)
        {
            input_handler_ = &input_handler;

            glfwSetCursorPosCallback(window_, [](GLFWwindow* handle, double x, double y) {
                auto* window = static_cast<keycap::window*>(glfwGetWindowUserPointer(handle));
                if (window->input_handler_)
                {
                    auto xx = static_cast<float>(x);
                    auto yy = static_cast<float>(y);
                    window->input_handler_->on_mouse_move({
                        glfwGetTime(),
                        xx,
                        yy,
                        xx - window->last_mouse_x_,
                        window->last_mouse_y_ - yy,
                    });
                }
                window->last_mouse_x_ = static_cast<float>(x);
                window->last_mouse_y_ = static_cast<float>(y);
            });

            glfwSetScrollCallback(window_, [](GLFWwindow* handle, double x, double y) {
                auto* window = static_cast<keycap::window*>(glfwGetWindowUserPointer(handle));
                if (window->input_handler_)
                {
                    window->input_handler_->on_mouse_wheel({
                        glfwGetTime(),
                        static_cast<float>(x),
                        static_cast<float>(y),
                    });
                }
            });

            glfwSetMouseButtonCallback(window_, [](GLFWwindow* handle, int button, int action, int modifier) {
                auto* window = static_cast<keycap::window*>(glfwGetWindowUserPointer(handle));
                if (window->input_handler_)
                {
                    window->input_handler_->on_mouse_button({
                        glfwGetTime(),
                        mouse_button{button},
                        input_action{action},
                        input_modifiers{modifier},
                    });
                }
            });

            glfwSetKeyCallback(window_, [](GLFWwindow* handle, int key, int scancode, int action, int mods) {
                auto* window = static_cast<keycap::window*>(glfwGetWindowUserPointer(handle));
                if (window->input_handler_)
                {
                    window->input_handler_->on_keyboard({
                        glfwGetTime(),
                        keycap::key{key},
                        scancode,
                        input_action{action},
                        input_modifiers{mods},
                    });
                }
            });

            glfwSetDropCallback(window_, [](GLFWwindow* handle, int count, const char** paths) {
                auto* window = static_cast<keycap::window*>(glfwGetWindowUserPointer(handle));
                if (window->input_handler_)
                {
                    std::vector<std::filesystem::path> files(count, "");
                    for (int i = 0; i < count; ++i)
                        files[i] = paths[i];

                    window->input_handler_->on_drop_files({
                        glfwGetTime(),
                        std::move(files),
                    });
                }
            });

            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        /// <summary>
        /// Run the window. This will block until the window closes
        /// </summary>
        /// <param name="frame_handler">The frame_handler to handle frame events</param>
        void run(frame_handler& frame_handler)
        {
            float last_time = 0;

            while (!glfwWindowShouldClose(window_))
            {
                float current_time = static_cast<float>(glfwGetTime());
                timestep delta_time{current_time - last_time};
                last_time = current_time;

                if (frame_handler.on_pre_frame(*this, delta_time))
                {
                    frame_handler.on_frame(*this, delta_time);
                }

                glfwSwapBuffers(window_);
                glfwPollEvents();

                frame_handler.on_post_frame(*this, delta_time);
            }
        }

        /// <summary>
        /// Signals the window to close when next possible
        /// </summary>
        void close() noexcept
        {
            glfwSetWindowShouldClose(window_, GLFW_TRUE);
        }

        /// <summary>
        /// Returns the internal window handle
        /// </summary>
        [[nodiscard]] void* handle() const noexcept
        {
            return window_;
        }

        /// <summary>
        /// Returns the current width and height of the window
        /// </summary>
        [[nodiscard]] std::pair<u32, u32> size() const noexcept
        {
            int width, height;
            glfwGetWindowSize(window_, &width, &height);
            return std::make_pair(static_cast<u32>(width), static_cast<u32>(height));
        }

      private:
        explicit window(window_creation_parameters parameters)
          : parameters_{std::move(parameters)}
        {
            if (parameters.height == 0 || parameters.width == 0)
            {
                auto* monitor = glfwGetPrimaryMonitor();
                auto* mode = glfwGetVideoMode(monitor);

                parameters_.height = static_cast<u32>(mode->height);
                parameters_.width = static_cast<u32>(mode->width);
            }

            window_ = glfwCreateWindow(static_cast<int>(parameters_.width), static_cast<int>(parameters_.height),
                                       parameters_.title.c_str(), nullptr, nullptr);
            if (!window_)
            {
                throw exception(error_code::external_api_error, module::window, fragment::window, __LINE__,
                                "Failed to create window");
            }

            glfwSetWindowUserPointer(window_, this);

            if (parameters_.maximize)
            {
                glfwMaximizeWindow(window_);
            }
        }

        GLFWwindow* window_ = nullptr;
        window_creation_parameters parameters_;

        input_event_handler* input_handler_ = nullptr;

        float last_mouse_x_ = 0;
        float last_mouse_y_ = 0;
    };

    /// <summary>
    /// Provides methods for creating windows. Must only exist once in the entire application
    /// </summary>
    export class window_context
    {
      public:
        window_context()
        {
            if (glfwInit() != GLFW_TRUE)
            {
                throw exception{error_code::external_api_error, module::window, fragment::window, __LINE__,
                                "Failed to initialize glfw"};
            }
        }

        /// <summary>
        /// Creates a new window with the given parameters
        /// </summary>
        [[nodiscard]] window create_window(window_creation_parameters parameters)
        {
            return window{parameters};
        }

        ~window_context()
        {
            glfwTerminate();
        }

      private:
    };
}
