#include "headers.h"
string dir_home_path=".";
string dir_home_absolute_path="";
string dir_current_absolute_path="";
string dir_current_path=".";
void linux_mode()
{
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL)
        homedir = getpwuid(getuid())->pw_dir;
    string temp_path=dir_home_absolute_path;
    dir_home_absolute_path=string(homedir);
    chdir(dir_home_absolute_path.c_str());
    stack<string>dirs;
    while(temp_path != dir_home_absolute_path)
    {
        dirs.push(extract_name(temp_path));
        temp_path=parse_retrace(temp_path);
    }
    while(!dirs.empty())
    {
        dir_current_path=parse(dir_current_path,dirs.top());
        dirs.pop();
    }
}
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
    if(!temp_str.empty())
    tokens.push_back(temp_str);
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
        computed_path=dir_current_path+"/"+path;
    }
    return computed_path;
}
pair<double,string> get_human_readable(long long int bytes)
{
    string suffix[]={"B","KB","MB","GB"};
    int length=4;
    double dbl_bytes = bytes;
    int i = 0;
    if (bytes > 1024)
    {
        for (i = 0; (bytes / 1024) > 0 && i < length - 1; i++, bytes /= 1024)
            dbl_bytes = bytes / 1024.0;
    }
    return make_pair(dbl_bytes,suffix[i]);
}
string parse(string a,string b)
{
    string c=a+"/"+b;
    return c;
}
void compute_cwd()
{
    char buffer[1024];
    getcwd(buffer,1024);
    dir_current_absolute_path=buffer;
    dir_home_absolute_path=dir_current_absolute_path;
}
string parse_retrace(string path)
{
    string last_path=path.substr(0,path.find_last_of("/"));
    return last_path;
}
string extract_name(string path)
{
    int loc=path.find_last_of("/");
    string name=path.substr(loc+1,path.length()-loc-1);
    return name;
}
void update_absolute_path()
{
    if(dir_current_path==".")
        dir_current_absolute_path=dir_home_absolute_path;
    else
    {
        string relative_path=dir_current_path.substr(2,dir_current_path.size()-1);
        dir_current_absolute_path=dir_home_absolute_path+"/"+relative_path;
    }
}
bool directory_query(string path)
{
    struct stat entity;
    if(stat(path.c_str(),&entity)==-1)
    {
        return false;
    }
    if(!S_ISDIR(entity.st_mode))
    {
        return false;
    }
    return true;
}
bool file_query(string path)
{
    struct stat entity;
    if(stat(path.c_str(),&entity)==-1)
    {
        return false;
    }
    if(!S_ISREG(entity.st_mode))
    {
        return false;
    }
    return true;
}