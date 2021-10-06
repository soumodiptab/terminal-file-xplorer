#include "headers.h"
struct termios old_terminal;
struct termios new_terminal;
int terminal_height;
int terminal_width;
int row_offset=1;
int col_offset=0;
int dir_max_entries;
int dir_offset=1;
int divider_position;
int row=1;
int col=0;
void initialize_terminal()
{
    struct winsize term;
    ioctl(STDOUT_FILENO, TIOCGWINSZ,&term);
    terminal_height=term.ws_row;
    terminal_width=term.ws_col;
    dir_max_entries=terminal_height-8;
    divider_position=dir_max_entries+1;
}
void window_resize(int signal)
{
    initialize_terminal();
    exit_raw_mode();
    FLAG_WINDOW_RESIZED=true;
    enter_raw_mode();
}
void enter_raw_mode()
{
    new_terminal = old_terminal;
    new_terminal.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_terminal);//changes will occur after flush
}
void exit_raw_mode()
{
    tcsetattr(STDIN_FILENO,TCSANOW,&old_terminal);//changes will occur now
}
void highlight_red(string message)
{
	cout<<"\033[31m";
    cout<<message;
	cout<<"\033[0m";
}
void highlight_green(string message)
{
    cout<<"\033[32m";
    cout<<message;
    cout<<"\033[0m";
}
void highlight_blue(string message)
{
    cout<<"\033[34m";
    cout<<message;
    cout<<"\033[0m";
}
void highlight_cyan(string message)
{
    cout<<"\033[36m";
    cout<<message;
    cout<<"\033[0m";
}
void highlight_yellow(string message)
{
    cout<<"\033[33m";
    cout<<message;
    cout<<"\033[0m";
}
void highlight_purple(string message)
{
    cout<<"\033[35m";
    cout<<message;
    cout<<"\033[0m";
}
void hide_cursor()
{
    cout<<"\e[?25l";
}
void show_cursor()
{
    cout<<"\e[?25h";
}
void arrow()
{
    highlight_yellow("->");
    move_cursor(row);
}
void reset_cursor()
{
    move_cursor(row_offset);
}
void move_cursor(int x,int y) {
    fflush(stdout);
	cout<<"\033["<<x<<";"<<y<<"H";
}
void move_cursor(int x)
{
    move_cursor(x,col_offset);
}
void clear_line()
{
    cout<<"\033[K";
    fflush(stdout);
}
void clear_screen()
{
    cout<<"\033[H\033[J";
}
void switch_to_alternate_screen()
{
    cout<<"\0337\033[?47h";
}
void switch_back()
{
    cout<<"\033[2J\033[?47l\0338";
}
void alert(string message)
{
    move_cursor(terminal_height-2,0);
    clear_line();
    highlight_yellow(message);
    move_cursor(row);
}
void error(string message)
{
    move_cursor(terminal_height-2,0);
    clear_line();
    highlight_red(message);
    move_cursor(row);
}
void status(string message)
{

}
void success(string message)
{
    move_cursor(terminal_height-2,0);
    clear_line();
    highlight_green(message);
    move_cursor(row);
}
void clear_status()
{
    move_cursor(terminal_height-2,0);
    clear_line();
    move_cursor(row);
}