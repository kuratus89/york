#include "input.h"

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <cstdio>
#endif

namespace input {

// ================= ASCII / PUNCTUATION MAPPING =================
static key mapAscii(int c) {
    // Letters
    if (c >= 'a' && c <= 'z')
        return key(c - 'a' + static_cast<int>(key::A));
    if (c >= 'A' && c <= 'Z')
        return key(c - 'A' + static_cast<int>(key::A));

    // Numbers
    if (c >= '0' && c <= '9')
        return key(c - '0' + static_cast<int>(key::Num0));

    switch (c) {
        case ' ':  return key::Space;
        case '-':  return key::Minus;
        case '=':  return key::Equals;
        case '[':  return key::LeftBracket;
        case ']':  return key::RightBracket;
        case '\\': return key::Backslash;
        case ';':  return key::Semicolon;
        case '\'': return key::Apostrophe;
        case ',':  return key::Comma;
        case '.':  return key::Period;
        case '/':  return key::Slash;
        case '`':  return key::Backtick;

        // Shifted symbols
        case '!':  return key::Exclamation;
        case '@':  return key::At;
        case '#':  return key::Hash;
        case '$':  return key::Dollar;
        case '%':  return key::Percent;
        case '^':  return key::Caret;
        case '&':  return key::Ampersand;
        case '*':  return key::Asterisk;
        case '(':  return key::LeftParen;
        case ')':  return key::RightParen;

        case '\n':
        case '\r': return key::Enter;
        case '\t': return key::Tab;
        case 8:
        case 127:  return key::Backspace;
        case 27:   return key::Escape;
        default:   return key::Unknown;
    }
}

// ================= KEY TO STRING =================
std::string keyToString(key k) {
    // Letters
    if (k >= key::A && k <= key::Z) {
        char c = 'A' + (static_cast<int>(k) - static_cast<int>(key::A));
        return std::string(1, c);
    }
    // Numbers
    if (k >= key::Num0 && k <= key::Num9) {
        char c = '0' + (static_cast<int>(k) - static_cast<int>(key::Num0));
        return std::string(1, c);
    }

    switch (k) {
        case key::Space:        return " ";
        case key::Minus:        return "-";
        case key::Equals:       return "=";
        case key::LeftBracket:  return "[";
        case key::RightBracket: return "]";
        case key::Backslash:    return "\\";
        case key::Semicolon:    return ";";
        case key::Apostrophe:   return "'";
        case key::Comma:        return ",";
        case key::Period:       return ".";
        case key::Slash:        return "/";
        case key::Backtick:     return "`";

        case key::Exclamation:  return "!";
        case key::At:           return "@";
        case key::Hash:         return "#";
        case key::Dollar:       return "$";
        case key::Percent:      return "%";
        case key::Caret:        return "^";
        case key::Ampersand:    return "&";
        case key::Asterisk:     return "*";
        case key::LeftParen:    return "(";
        case key::RightParen:   return ")";

        case key::Enter:        return "Enter";
        case key::Escape:       return "Escape";
        case key::Tab:          return "Tab";
        case key::Backspace:    return "Backspace";

        case key::Up:           return "Up";
        case key::Down:         return "Down";
        case key::Left:         return "Left";
        case key::Right:        return "Right";
        case key::Home:         return "Home";
        case key::End:          return "End";
        case key::PageUp:       return "PageUp";
        case key::PageDown:     return "PageDown";
        case key::Insert:       return "Insert";
        case key::DeleteKey:    return "Delete";

        case key::F1:  return "F1";
        case key::F2:  return "F2";
        case key::F3:  return "F3";
        case key::F4:  return "F4";
        case key::F5:  return "F5";
        case key::F6:  return "F6";
        case key::F7:  return "F7";
        case key::F8:  return "F8";
        case key::F9:  return "F9";
        case key::F10: return "F10";
        case key::F11: return "F11";
        case key::F12: return "F12";

        case key::None:         return "None";
        default:                return "Unknown";
    }
}

#ifdef _WIN32
// ================= WINDOWS =================
bool pollEvent(event& e) {
    if (!_kbhit())
        return false;

    int ch = _getch();

    // Extended / special keys start with 0 or 224
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
            case 72: e.keycode = key::Up;       break;
            case 80: e.keycode = key::Down;     break;
            case 75: e.keycode = key::Left;     break;
            case 77: e.keycode = key::Right;    break;
            case 71: e.keycode = key::Home;     break;
            case 79: e.keycode = key::End;      break;
            case 73: e.keycode = key::PageUp;   break;
            case 81: e.keycode = key::PageDown; break;
            case 82: e.keycode = key::Insert;   break;
            case 83: e.keycode = key::DeleteKey;break;

            // Function keys
            case 59: e.keycode = key::F1;  break;
            case 60: e.keycode = key::F2;  break;
            case 61: e.keycode = key::F3;  break;
            case 62: e.keycode = key::F4;  break;
            case 63: e.keycode = key::F5;  break;
            case 64: e.keycode = key::F6;  break;
            case 65: e.keycode = key::F7;  break;
            case 66: e.keycode = key::F8;  break;
            case 67: e.keycode = key::F9;  break;
            case 68: e.keycode = key::F10; break;
            case 133: e.keycode = key::F11; break;
            case 134: e.keycode = key::F12; break;
            default: e.keycode = key::Unknown;    break;
        }
    } else {
        key k = mapAscii(ch);
        if (k != key::Unknown) {
            e.keycode = k;
        } else if (ch >= 1 && ch <= 26) { // Ctrl+A .. Ctrl+Z
            e.keycode = key((ch - 1) + static_cast<int>(key::A));
        } else {
            e.keycode = key::Unknown;
        }
    }

    e.pressed = true;
    return true;
}

#else
// ================= LINUX / POSIX =================
bool pollEvent(event& e) {
    static bool init = false;
    static termios oldt;

    if (!init) {
        termios newt{};
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
        init = true;
    }

    int ch = getchar();
    if (ch == EOF)
        return false;

    if (ch == 27) { // Escape sequence or Escape key
        int a = getchar();
        if (a == EOF) { // plain Escape
            e.keycode = key::Escape;
        } else if (a == '[') {
            int b = getchar();
            if (b == EOF) {
                e.keycode = key::Escape;
            } else if (b >= '0' && b <= '9') {
                int num = b - '0';
                int next = getchar();
                while (next >= '0' && next <= '9') {
                    num = num * 10 + (next - '0');
                    next = getchar();
                }
                if (next == '~') {
                    switch (num) {
                        case 1: case 7:  e.keycode = key::Home;      break;
                        case 2:          e.keycode = key::Insert;    break;
                        case 3:          e.keycode = key::DeleteKey; break;
                        case 4: case 8:  e.keycode = key::End;       break;
                        case 5:          e.keycode = key::PageUp;    break;
                        case 6:          e.keycode = key::PageDown;  break;
                        case 11: e.keycode = key::F1;  break;
                        case 12: e.keycode = key::F2;  break;
                        case 13: e.keycode = key::F3;  break;
                        case 14: e.keycode = key::F4;  break;
                        case 15: e.keycode = key::F5;  break;
                        case 17: e.keycode = key::F6;  break;
                        case 18: e.keycode = key::F7;  break;
                        case 19: e.keycode = key::F8;  break;
                        case 20: e.keycode = key::F9;  break;
                        case 21: e.keycode = key::F10; break;
                        case 23: e.keycode = key::F11; break;
                        case 24: e.keycode = key::F12; break;
                        default: e.keycode = key::Unknown; break;
                    }
                } else {
                    e.keycode = key::Unknown;
                }
            } else {
                switch (b) {
                    case 'A': e.keycode = key::Up;       break;
                    case 'B': e.keycode = key::Down;     break;
                    case 'C': e.keycode = key::Right;    break;
                    case 'D': e.keycode = key::Left;     break;
                    case 'H': e.keycode = key::Home;     break;
                    case 'F': e.keycode = key::End;      break;
                    case 'Z': e.keycode = key::Tab;      break; // Shift+Tab (approx)
                    default:  e.keycode = key::Unknown;  break;
                }
            }
        } else if (a == 'O') {
            int b = getchar();
            switch (b) {
                case 'P': e.keycode = key::F1; break;
                case 'Q': e.keycode = key::F2; break;
                case 'R': e.keycode = key::F3; break;
                case 'S': e.keycode = key::F4; break;
                default:  e.keycode = key::Unknown; break;
            }
        } else {
            e.keycode = key::Escape;
        }
    } else {
        e.keycode = mapAscii(ch);
    }

    e.pressed = true;
    return true;
}
#endif

} // namespace input