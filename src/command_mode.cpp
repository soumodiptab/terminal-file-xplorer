#include "headers.h"
void display_command_symbol()
{
    highlight_blue("~");
    highlight_purple("$");
    col=3;
    move_cursor(terminal_height,col);
}
void process_command(string command_buffer)
{

}
void start_command_mode()
{
    move_cursor(terminal_height);
    display_command_symbol();
    char ch;
    while(true)
    {
        fflush(stdin);
        string command_buffer;
        while(true)
        {
            ch=cin.get();
            if(ch == 10 || ch == 27)// 10 - enter 27- esc
                break;
            else if(ch == 127)//backspace
            {
                if(command_buffer.length()>0)
                {
                    command_buffer.pop_back();
                    move_cursor(terminal_height,--col);
                    clear_line();
                }
            }
            else
            {
                command_buffer.push_back(ch);
                cout<<ch;
                col++;
            }
        }
        if(ch == 10)//enter was pressed
        {
            if(command_buffer.length()>1)
            {
                process_command(command_buffer);
            }
            else
            {
                error("No command typed");
            }
        }
        else if(ch == 27)
        {
            break;
        }
        else
        {
            
        }
    }
}