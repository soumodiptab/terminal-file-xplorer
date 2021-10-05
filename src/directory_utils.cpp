#include "headers.h"
stack<string> dir_backward_stream;
stack<string> dir_forward_stream;
vector<string> dir_current_stream;
void display_directories(string path)
{
    dir_current_stream.clear();
    DIR *dir_stream = opendir(dir_current_path.c_str());
    if(dir_stream==NULL)
    {
        error("Directories cannot be displayed");
        return;
    }


}
void display_directory_entry(int position)
{
    display_directory_entry("");
}
void display_directory_entry(string path)
{
    struct stat entity;
    if(stat(path.c_str(),&entity)==-1)
    {
        error("Entry cannot be accessed");
        return;
    }
    auto flag=entity.st_mode;
    switch (flag & S_IFMT)
    {
        case S_IFBLK:  cout<<"b";break;
        case S_IFCHR:  cout<<"c";break;
        case S_IFDIR:  cout<<"d";break;
        case S_IFLNK:  cout<<"s";break;
        default:
        cout<<"-";
    }
    cout<<(flag& S_IRUSR)? "r":"-";
    cout<<(flag & S_IWUSR)? "w":"-";
    cout<<(flag & S_IXUSR)? "x":"-";
    cout<<(flag & S_IRGRP)? "r":"-";
    cout<<(flag & S_IWGRP)? "w":"-";
    cout<<(flag & S_IXGRP)? "x":"-";
    cout<<(flag & S_IROTH)? "r":"-";
    cout<<(flag & S_IWOTH)? "w":"-";
    cout<<(flag & S_IXOTH)? "x":"-";
    cout<<" ";
    string owner_name="";
    if (getpwuid(entity.st_uid) != NULL)
        owner_name=getpwuid(entity.st_uid)->pw_name;
    cout<<setw(10)<<owner_name;
    cout<<" ";
    string group_name="";
    if(getgrgid(entity.st_gid)!=NULL)
        group_name=getgrgid(entity.st_gid)->gr_name;
    cout<<setw(10)<<group_name;
    
}