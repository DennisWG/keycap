#include <catch2/catch_test_macros.hpp>

import keycap.window;

struct dummy_input_handler : keycap::input_event_handler
{
    virtual void on_mouse_move(keycap::mouse_move_event event) override
    {
    }
    virtual void on_mouse_wheel(keycap::mouse_wheel_event event) override
    {
    }
    virtual void on_mouse_button(keycap::mouse_button_event event) override
    {
    }
    virtual void on_keyboard(keycap::keyboard_event event) override
    {
    }
    virtual void on_drop_files(keycap::drop_files_event event) override
    {
    }
};

TEST_CASE("window", "[keycap.window:window]")
{
    keycap::window_context context;
    dummy_input_handler dummy_handler;

    keycap::window_creation_parameters params{
        .title = "Testing",
        .width = 800,
        .height = 600,
        .resizable = true,
        .maximize = false,
    };
    auto window = context.create_window(params);
    window.register_input_events(dummy_handler);

    SECTION("window::run must call a frame_handler's event handlers")
    {
        struct frame_handler : keycap::frame_handler
        {
            virtual bool on_pre_frame(keycap::window& window, keycap::timestep delta_time) override
            {
                on_pre_frame_called = true;
                return true;
            }

            virtual void on_frame(keycap::window& window, keycap::timestep delta_time) override
            {
                on_frame_called = true;
            }

            virtual void on_post_frame(keycap::window& window, keycap::timestep delta_time) override
            {
                on_post_frame_called = true;
                window.close();
            }

            bool on_pre_frame_called = false;
            bool on_frame_called = false;
            bool on_post_frame_called = false;
        } handler;

        window.run(handler);

        REQUIRE(handler.on_pre_frame_called == true);
        REQUIRE(handler.on_frame_called == true);
        REQUIRE(handler.on_post_frame_called == true);
    }

    SECTION("window::handle must not be nullptr")
    {
        REQUIRE(window.handle() != nullptr);
    }

    SECTION("window::size must yield the given size from the window_creation_parameters if they were non-zero and the "
            "window wasn't resized")
    {
        auto&& [width, height] = window.size();

        REQUIRE(width == params.width);
        REQUIRE(height == params.height);
    }

    SECTION("window::size must yield a bigger than given size when the maximize parameter given in "
            "window_creation_parameters is true")
    {
        keycap::window_creation_parameters params2{
            .title = "Testing",
            .width = 5,
            .height = 5,
            .resizable = true,
            .maximize = true,
        };
        auto window2 = context.create_window(params2);
        auto&& [width, height] = window2.size();

        REQUIRE(width != params2.width);
        REQUIRE(height != params2.height);
    }

    SECTION("window::size must yield a non-zero size when the size given in window_creation_parameters is zero")
    {
        keycap::window_creation_parameters params2{
            .title = "Testing",
            .width = 0,
            .height = 0,
            .resizable = true,
            .maximize = false,
        };
        auto window2 = context.create_window(params2);
        auto&& [width, height] = window2.size();

        REQUIRE(width != params2.width);
        REQUIRE(height != params2.height);
    }
}

TEST_CASE("timestep", "[keycap.window:window]")
{
    constexpr float value = 1.f / 5.f;
    keycap::timestep ts{value};

    REQUIRE(ts.seconds() == value);
    REQUIRE(ts.milliseconds() == value * 1'000);
}
