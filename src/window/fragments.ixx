module;

export module keycap.window : fragments;

import keycap.core;

namespace keycap::fragment
{
    enum : u64
    {
        input_events,
        input_mappings,
        window,
    };
}