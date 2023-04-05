//
// Created by Azuolas on 2/17/2023.
//

#include "InputReadUtility.h"
#include "AI/Searcher.h"
#ifdef _WIN32
    #include <windows.h>
#else
    #include "sys/time.h"
    #include "sys/select.h"
#endif

int ChessEngine::InputWaiting()
{
#ifdef WIN64
    static int init = 0, pipe;
    static HANDLE inh;
    DWORD dw;

    if (!init)
    {
        init = 1;
        inh = GetStdHandle(STD_INPUT_HANDLE);
        pipe = !GetConsoleMode(inh, &dw);
        if (!pipe)
        {
            SetConsoleMode(inh, dw & ~(ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT));
            FlushConsoleInputBuffer(inh);
        }
    }

    if (pipe)
    {
        if (!PeekNamedPipe(inh, NULL, 0, NULL, &dw, NULL)) return 1;
        return dw;
    }

    else
    {
        GetNumberOfConsoleInputEvents(inh, &dw);
        return dw <= 1 ? 0 : dw;
    }
#else
    fd_set readfds;
    struct timeval tv;

    FD_ZERO (&readfds);
    FD_SET (fileno(stdin), &readfds);
    tv.tv_sec=0; tv.tv_usec = 0;
    select(16, &readfds, nullptr, nullptr, &tv);

    return (FD_ISSET(fileno(stdin), &readfds));
#endif
}

