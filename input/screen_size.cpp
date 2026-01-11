#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#include <utility>

std::pair<int, int> screen_size() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return {0, 0};

    int cols = csbi.srWindow.Right - csbi.srWindow.Left ;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top ;
    return {cols, rows};
#else
    winsize w{};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return {0, 0};

    return {w.ws_col-1, w.ws_row-1};
#endif
}
