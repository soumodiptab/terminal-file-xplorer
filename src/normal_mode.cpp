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
    row=row_offset;
    dir_offset=1;
    display_directories(dir_current_path);
    display_banner();
    reset_cursor();
    arrow();
}
void display_screen()
{
    init_screen();
    enter_raw_mode();
    navigator();
    exit_raw_mode();
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
void move_level_up()
{
    if(dir_current_path == ".")
    {
        error("Cannot go beyond set home");
    }
    else
    {
        dir_backward_stream.push(dir_current_path);
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
            success("Going into : "+selected_entity);
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
    dir_current_path=dir_home_path;
    refresh_screen();
}
void command()
{
    show_cursor();
    FLAG_COMMAND_MODE=true;
    display_banner();
    start_command_mode();
    hide_cursor();
    refresh_screen();
}
void navigator()
{
    hide_cursor();
    reset_cursor();
    arrow();
    char ch=' ';
	while(ch!='q'){
	
			ch=cin.get();	

			switch(ch){
				case ':':command();break;//command mode

				case 10:enter();break;//enter key

				case 127:move_level_up();break;//backspace

				case 65:move_up();break; // up arrow

                case 66:move_down();break; // down arrow

                case 67:move_forward();break; //-> arrow

				case 68:move_backward();break; // <- arrow

				case 107:;break;//scroll up

				case 104:home();break;//home

                case 108:;break;//scroll down
				
				default:break;
		}
	}
}