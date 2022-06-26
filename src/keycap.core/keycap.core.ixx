module;

export module keycap.core;

export import : algorithm;
export import : concepts;
export import : error;
export import : math;
export import : scopeguard;
export import : string;
export import : types;

module : private;

namespace keycap::fragment
{
    enum : u64
    {
        algorithm,
        concenpts,
        error,
        math,
        scopeguard,
        string,
        types,
    };
}
