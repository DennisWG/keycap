#include <catch2/catch_test_macros.hpp>

import keycap.window;

TEST_CASE("window", "[keycap.window:window]")
{
    keycap::window_context context;

    auto window = context.create_window(keycap::window_creation_parameters{
        .title = "Testing",
        .width = 800,
        .height = 600,
        .resizable = true,
        .maximize = true,
    });

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
