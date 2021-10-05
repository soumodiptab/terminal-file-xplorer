#include "headers.h"
struct termios old_terminal;
struct termios new_terminal;
int terminal_height;
int terminal_width;
int row_offset=1;
int col_offset=1;
int dir_max_entries;
int dir_offset;
int divider_position;
int row,col;
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
	cout<<"\033[0;31m";
    cout<<message;
	cout<<"\033[0m";
}
void highlight_green(string message)
{
    cout<<"\033[0;32m";
    cout<<message;
    cout<<"\033[0m";
}
void move_cursor(int x,int y) {
	cout<<"\033["<<x<<";"<<y<<"H";
	fflush(stdout);
}
void move_cursor(int x)
{
    move_cursor(x,col_offset);
}
void clear_line()
{
    cout<<"\033[K";
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
}
void error(string message)
{
    move_cursor(terminal_height-2,0);
    clear_line();
    highlight_red(message);
}
void status(string message)
{

}
void success(string message)
{

}