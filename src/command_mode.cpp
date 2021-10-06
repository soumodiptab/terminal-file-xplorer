#include "headers.h"
void process_command(string command_buffer)
{
    vector<string> parameters=input_processor(command_buffer);
    string command=parameters[0];
    if(command == "create_dir")
    {
        
    }
    else if(command == "create_file")
    {
        create_file_util(parameters);
    }
    else if(command == "delete_dir")
    {

    }
    else if(command == "delete_file")
    {

    }
    else if(command == "copy")
    {

    }
    else if(command == "move")
    {

    }
    else if(command == "rename")
    {

    }
    else if(command == "goto")
    {
        go_to(parameters);
    }
    else if(command == "search")
    {

    }
    else
    {
        error("Incorrect command");
    }
}
void start_command_mode()
{
    move_cursor(terminal_height,3);
    char ch;
    while(true)
    {
        string command_buffer;
        while(true)
        {
            ch=cin.get();
            clear_status();
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
            fflush(stdin);
            break;
        }
        clear_command();
        col=3;
        move_cursor(row,col);
    }
}