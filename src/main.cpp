#include "headers.h"
bool FLAG_COMMAND_MODE=false;
bool FLAG_WINDOW_RESIZED=false;
bool LINUX_MODE=false;
int main()
{
    atexit(cleanup_screen);
    switch_to_alternate_screen();
    signal(SIGWINCH, window_resize);
    compute_cwd();
    if(LINUX_MODE)
        linux_mode();
    display_screen();
    return 0;
}
