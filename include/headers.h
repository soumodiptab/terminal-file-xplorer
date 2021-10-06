#include <bits/stdc++.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include<sys/wait.h> 
#include <sys/types.h>
#include <fcntl.h>
/**************************************************************************************************************************/
/********************************************************** MACROS ********************************************************/
/**************************************************************************************************************************/
using namespace std;


/**************************************************************************************************************************/
/********************************************************* GLOBALS ********************************************************/
/**************************************************************************************************************************/

extern struct termios old_terminal;
extern struct termios new_terminal;

/**
 * @brief cursor row
 * 
 */
extern int row;
/**
 * @brief cursor col
 * 
 */
extern int col;
extern bool FLAG_COMMAND_MODE;
extern bool FLAG_WINDOW_RESIZED;
extern int terminal_height;
extern int terminal_width;
extern int dir_max_entries;
extern int dir_offset;
/**
 * @brief left bound
 * 
 */
extern int col_offset;
/**
 * @brief upper bound
 * 
 */
extern int row_offset;
extern int divider_position;
extern string dir_home_path;
extern string dir_home_absolute_path;
extern string dir_current_absolute_path;
extern string dir_current_path;
extern stack<string> dir_backward_stream;
extern stack<string> dir_forward_stream;
extern vector<string> dir_current_stream;
/**************************************************************************************************************************/
/*************************************************** All api declarations here ********************************************/
/**************************************************************************************************************************/

/**
 * @brief Tokenizes the string and returns the tokens as vectors
 * 
 * @return vector<string> tokens
 */
vector<string> input_processor(string);

/**
 * @brief Create a file and place in destination path
 * 
 * @param filename 
 * @param destination_path 
 * @return status
 */
bool create_file(string &filename, string &destination_path);

bool create_dir(string dirname);
/**
 * @brief create a file and do token processing
 * 
 * @param tokens 
 * @return true 
 * @return false 
 */
bool create_file_util(vector<string> &tokens);

void test_cases();
/**
 * @brief Parse the path and remove unwanted symbols
 * 
 * @param path 
 * @return string 
 */
string path_processor(string &path);
void highlight_red(string message);
void highlight_green(string message);
void highlight_blue(string message);
void highlight_cyan(string message);
void highlight_yellow(string message);
void highlight_purple(string message);
void refresh_screen();
void display_screen();
void enter_raw_mode();
void exit_raw_mode();
void initialize_terminal();
void window_resize(int signal);
void display_directories(string path);
void display_banner();
void display_directory_entry(int position);
void display_directory_entry(string path,string name);
void navigator();
/**
 * @brief clears the entire screen
 * 
 */
void clear_screen();
/**
 * @brief clears the line from cursor position
 * 
 */
void clear_line();
/**
 * @brief Positions the cursor in xth row and yth col
 * 
 * @param x row
 * @param y col
 */
void move_cursor(int x,int y);
void hide_cursor();
void show_cursor();
void reset_cursor();
void move_cursor(int x);
void switch_to_alternate_screen();
void switch_back();
void init_screen();
void alert(string message);
void error(string message);
void status(string message);
void success(string message);
void arrow();
void clear_status();
pair<double,string> get_human_readable(long long int size);
/**
 * @brief 
 * 
 * @param a current_path 
 * @param b entity
 * @return current_path/entity 
 */
string parse(string a,string b);
void compute_cwd();
/**
 * @brief 
 * 
 * @param path path/entity
 * @return string path
 */
string parse_retrace(string path);
void move_forward();
void move_backward();
void move_level_up();
void move_up();
void move_down();
void home();
void command();
void update_absolute_path();
void start_command_mode();