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

        // Punctuation / symbols
        Space,
        Minus, Equals,
        LeftBracket, RightBracket,
        Backslash,
        Semicolon, Apostrophe,
        Comma, Period, Slash,
        Backtick,
        Exclamation,   // !
        At,            // @
        Hash,          // #
        Dollar,        // $
        Percent,       // %
        Caret,         // ^
        Ampersand,     // &
        Asterisk,      // *
        LeftParen,     // (
        RightParen,    // )

        // Controls
        Enter,
        Escape,
        Tab,
        Backspace,

        // Navigation
        Up,
        Down,
        Left,
        Right,
        Home,
        End,
        PageUp,
        PageDown,
        Insert,
        DeleteKey,

        // Function keys
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        Unknown
    };

    struct event {
        key  keycode{key::None};
        bool pressed{false};
    };

    bool pollEvent(event& e);
    std::string keyToString(key k);

} // namespace input