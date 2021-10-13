#include "headers.h"
void init_screen()
{
    initialize_terminal();
    tcgetattr(STDIN_FILENO, &old_terminal);
    reset_cursor();
    display_directories(dir_current_path);
    display_banner();
}
void refresh_screen()
{
    update_absolute_path();
    clear_screen();
    reset_cursor();
    if(FLAG_COMMAND_MODE)
    {
        row=terminal_height;
        col=3;
    }
    else
    {
        row=row_offset;
        col=col_offset;
    }
    dir_offset=1;
    display_directories(dir_current_path);
    display_banner();
    if(!FLAG_COMMAND_MODE)
    {
        reset_cursor();
        arrow();
    }
}
void display_screen()
{
    init_screen();
    enter_raw_mode();
    navigator();
}
void cleanup_screen()
{
    show_cursor();
    exit_raw_mode();
    switch_back();
}
void display_command_symbol()
{
    move_cursor(terminal_height);
    clear_line();
    highlight_blue("~");
    highlight_purple("$");
    move_cursor(row,col);
}
void clear_command()
{
    move_cursor(terminal_height,3);
    clear_line();
}
void display_banner()
{
    move_cursor(divider_position);
    clear_line(); 
    for(int i=0;i<terminal_width;i++)
        cout<<"-";
    cout<<endl;
    clear_line();
    int banner_start=(terminal_width-14)/2;
    for(int i=0;i<banner_start;i++)
        cout<<"-";
    if(FLAG_COMMAND_MODE)
    {
        highlight_purple(">COMMAND MODE<");
    }
    else
    {
        highlight_green("<NORMAL  MODE>");
    }
    for(int i=banner_start+14;i<terminal_width;i++)
    {
        cout<<"-";
    }
    cout<<endl;
    clear_line();
    for(int i=0;i<terminal_width;i++)
        cout<<"-";
    cout<<endl;
    cout<<"home: ";
    highlight_cyan(dir_home_absolute_path);
    cout<<endl;
    cout<<"current: ";
    highlight_cyan(dir_current_path);
    cout<<endl;
    if(FLAG_COMMAND_MODE)
    {
           display_command_symbol();
    }
}
void move_up()
{
    clear_status();
    if(row > 1)
    {
        clear_line();
        display_directory_entry(row+dir_offset-1);
        row--;
        move_cursor(row);
        arrow();
    }
    else if(row == 1 && dir_offset > 1)
    {
        dir_offset--;
        clear_line();
        reset_cursor();
        display_directories(dir_current_path);
        move_cursor(row);
        arrow();
    }
    else
        alert("You hit top");
}
void move_down()
{
    clear_status();
    if(row < dir_max_entries && row < dir_current_stream.size())
    {
        clear_line();
        display_directory_entry(row+dir_offset-1);
        row++;
        move_cursor(row);
        arrow();
    }
    else if(row == dir_max_entries && row+dir_offset-1 < dir_current_stream.size())
    {
        dir_offset++;
        clear_line();
        reset_cursor();
        display_directories(dir_current_path);
        move_cursor(row);
        arrow();
    }
    else
        alert("You hit bottom");
}
void window_scroll_up()
{
    if(dir_offset!=1)
    {
        dir_offset=max(1,dir_offset-dir_max_entries);
        display_directories(dir_current_path);
        move_cursor(row);
        arrow();
    }
}
void window_scroll_down()
{
    int max_value=dir_current_stream.size()-dir_max_entries+1;
    if(dir_offset!=max_value)
    {
        dir_offset=min(max_value,dir_offset+dir_max_entries);
        display_directories(dir_current_path);
        move_cursor(row);
        arrow();
    }
}
void move_level_up()
{
    if(dir_current_path == ".")
    {
        error("Cannot go beyond set home");
    }
    else
    {
        dir_backward_stream.push(dir_current_path);
        while(!dir_forward_stream.empty())
            dir_forward_stream.pop();
        dir_current_path=parse_retrace(dir_current_path);
        refresh_screen();
        alert("Going to parent directory");
    }
}
void move_backward()
{
    if(!dir_backward_stream.empty())
    {
        dir_forward_stream.push(dir_current_path);
        dir_current_path=dir_backward_stream.top();
        dir_backward_stream.pop();
        refresh_screen();
        alert("Going back");
    }
    else
    {
        error("Nothing to go backward");
    }
}
void move_forward()
{
    if(!dir_forward_stream.empty())
    {
        dir_backward_stream.push(dir_current_path);
        dir_current_path=dir_forward_stream.top();
        dir_forward_stream.pop();
        refresh_screen();
        alert("Going forward");
    }
    else
    {
        error("Nothing to go forward");
    }
}
void enter()
{
    struct stat entity;
    string selected_entity=dir_current_stream[row+dir_offset-2];
    string path=parse(dir_current_path,selected_entity);
    string abs_path=parse(dir_current_absolute_path,selected_entity);
    stat(path.c_str(),&entity);
    if(S_ISDIR(entity.st_mode))
    {
        if(selected_entity == ".")
        {
            alert("Already in current directory");
            return;
        }
        else if(selected_entity == "..")
        {
            move_level_up();
        }
        else
        {
            dir_backward_stream.push(dir_current_path);
            dir_current_path=path;
            refresh_screen();
            success("Going into : [ "+selected_entity+" ]");
        }
    }
    else
    {
        pid_t pid=fork();
        if(pid==0)
        {
            execl("/usr/bin/xdg-open","xdg-open",abs_path.c_str(),NULL);
			exit(0);
        }
        else if(pid>0)
        {
            success("File has been opened in default application");
        }
        else
        {
            error("Failed to open file");
        }
    }
}
void home()
{
    if(dir_current_path == dir_home_path)
    {
        error("Already in home");
        return;
    }
    while(!dir_forward_stream.empty())
        dir_forward_stream.pop();
    dir_backward_stream.push(dir_current_path);
    dir_current_path=dir_home_path;
    refresh_screen();
    success("Going to home");
}
void command()
{
    FLAG_COMMAND_MODE=true;
    show_cursor();
    refresh_screen();
    clear_status();
    start_command_mode();
    hide_cursor();
    FLAG_COMMAND_MODE=false;
    refresh_screen();
}
void navigator()
{
    hide_cursor();
    reset_cursor();
    arrow();
    char ch=' ';
	while(ch!='q')
    {
		ch=cin.get();	
		switch(ch)
        {
			case ':':command();break;//command mode
			
            case 10:enter();break;//enter key
			
            case 127:move_level_up();break;//backspace

			case 65:move_up();break; // up arrow

            case 66:move_down();break; // down arrow

            case 67:move_forward();break; //-> arrow

			case 68:move_backward();break; // <- arrow

			case 107:window_scroll_up();break;//scroll up k

			case 104:home();break;//h key
            
            case 108:window_scroll_down();break;//scroll down l
            
            default:break;
		}
	}
    exit(0);
}