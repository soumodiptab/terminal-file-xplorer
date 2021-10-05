#include "headers.h"
string dir_home_path=".";
string dir_absolute_path;
string dir_current_path=".";
vector<string> input_processor(string input)
{
    vector<string>tokens;
    string temp_str="";
    for( char c:input)
    {
        if(c==' ')
        {
            tokens.push_back(temp_str);
            temp_str="";
        }
        else
        {
            temp_str+=c;;
        }
    }
    return tokens;
}
string path_processor(string &path)
{
    /*
    cases:
    path has . ->current dir
    path has ./xxxxx -> currentdir/xxxxx
    path has ..  [later]
    path has ../ [later]
    path has ~ -> home
    path has ~/foobar -> home/foobar
    path has xxxxx -> currentdir/xxxxx
    */
    string computed_path="";
    if(path==".")
    {
        computed_path=dir_current_path;
    }
    else if(path[0]=='.' && path[1]=='/')
    {
        computed_path=dir_current_path+"/"+path.substr(2,path.length()-2);
    }
    else if(path == "~")
    {
        computed_path=dir_home_path;
    }
    else if(path[0]=='~' && path[1]=='/')
    {
        computed_path=dir_home_path+"/"+path.substr(2,path.length()-2);
    }
    else
    {
        computed_path=dir_current_path+"/"+path.substr(2,path.length()-2);
    }
    return computed_path;
}
