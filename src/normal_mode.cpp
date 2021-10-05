#include "headers.h"
void init_screen()
{
    initialize_terminal();
    tcgetattr(STDIN_FILENO, &old_terminal);
    display_directories(dir_current_path);
    display_banner();
}
void refresh_screen()
{
    clear_screen();
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
    for(int i=0;i<terminal_width;i++)
        cout<<"-";
    cout<<endl;
    move_cursor(divider_position);   
}
void move_up()
{
    
}
void move_down()
{

}
void navigator()
{
    char ch=' ';
	while(ch!='q'){
	
			ch=cin.get();	

			switch(ch){
				case ':':;break;//command mode

				case 10:;break;//enter key

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