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
/******************************************************      MACROS       *************************************************/
using namespace std;
#define CLEAR_SCREEN printf("\033[H\033[J")
/**
 * @brief coordinate x in the screen space
 * 
 */
extern int x;
/**
 * @brief coordinate y in the screen space
 * 
 */
extern int y;
extern string home_path;
extern string absolute_path;
extern string current_absolute_path;
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
 * @return true 
 * @return false 
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