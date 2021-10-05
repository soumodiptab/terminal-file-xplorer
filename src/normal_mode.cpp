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
    clear_screen();
    reset_cursor();
    display_directories(dir_current_path);
    display_banner();
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
    for(int i=0;i<terminal_width;i++)
        cout<<"-";
    cout<<endl;  
}
void move_up()
{
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
}
void move_down()
{
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
}
void move_back()
{

}
void move_forward()
{
    if(!dir_forward_stream.empty())
    {
        dir_backward_stream.push(dir_current_path);
        dir_
    }
}
void enter()
{
    struct stat entity;
    string name=parse(dir_current_path,dir_current_stream[row+dir_offset-2]);
    stat(name.c_str(),&entity);
    if(S_ISDIR(entity.st_mode))
    {
        if()
    }
    else
    {
        pid_t pid=fork();
        if(pid==0)
        {
            execlp("xdg-open","xdg-open",name,NULL);
			exit(0);
        }
    }
}
void navigator()
{
    reset_cursor();
    arrow();
    char ch=' ';
	while(ch!='q'){
	
			ch=cin.get();	

			switch(ch){
				case ':':;break;//command mode

				case 10:enter();break;//enter key

				case 127:;break;//backspace

				case 65:move_up();break; // up arrow

                case 66:move_down();break; // down arrow

                case 67:;break; //-> aroow

				case 68:;break; // <- arrow

				case 107:;break;//scroll up

				case 104:;break;//home

                case 108:;break;//scroll down
				
				default:break;
		}
	}
}