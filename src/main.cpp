#include "headers.h"
bool FLAG_COMMAND_MODE=false;
bool FLAG_WINDOW_RESIZED=false;

int main()
{
    atexit(cleanup_screen);
    switch_to_alternate_screen();
    signal(SIGWINCH, window_resize);
    compute_cwd();
    display_screen();
    return 0;
}
