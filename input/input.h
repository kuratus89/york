#pragma once
#include <cstdint>
#include <string>

namespace input {

    enum class key : uint16_t {
        None = 0,

        // Letters
        A, B, C, D, E, F, G, H, I, J,
        K, L, M, N, O, P, Q, R, S, T,
        U, V, W, X, Y, Z,

        // Numbers
        Num0, Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8, Num9,

        // Controls
        Space,
        Enter,
        Escape,
        Tab,
        Backspace,

        // Arrows
        Up,
        Down,
        Left,
        Right,

        Unknown
    };

    struct event {
        key  keycode;
        bool pressed;
    };

    bool pollEvent(event& e);
    std::string keyToString(key k);

} // namespace input