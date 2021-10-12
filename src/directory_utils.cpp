#include "headers.h"
stack<string> dir_backward_stream;
stack<string> dir_forward_stream;
vector<string> dir_current_stream;
void display_directories(string path)
{
    reset_cursor();
    dir_current_stream.clear();
    DIR *dir_stream = opendir(dir_current_path.c_str());
    if(dir_stream==NULL)
    {
        error("Directories cannot be displayed");
        return;
    }
    struct dirent *entry;
    entry=readdir(dir_stream);
    while(entry!=NULL)
    {
        dir_current_stream.push_back(entry->d_name);
        entry=readdir(dir_stream);
    }
    sort(dir_current_stream.begin(),dir_current_stream.end());
    int total_items=dir_current_stream.size();
    for(int line_no=0,window_offset=dir_offset-1;line_no < dir_max_entries  && window_offset < total_items; window_offset++, line_no++)
    {
        display_directory_entry(path,dir_current_stream[window_offset]);
    }
}
void display_directory_entry(int position)
{
    display_directory_entry(dir_current_path,dir_current_stream[position-1]);
}
void display_directory_entry(string path,string name)
{
    path=path+"/"+name;
    struct stat entity;
    if(stat(path.c_str(),&entity)==-1)
    {
        error("Entry cannot be accessed");
        return;
    }
    clear_line();
    cout<<"  ";
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
    cout<<((flag& S_IRUSR)? "r":"-");
    cout<<((flag & S_IWUSR)? "w":"-");
    cout<<((flag & S_IXUSR)? "x":"-");
    cout<<((flag & S_IRGRP)? "r":"-");
    cout<<((flag & S_IWGRP)? "w":"-");
    cout<<((flag & S_IXGRP)? "x":"-");
    cout<<((flag & S_IROTH)? "r":"-");
    cout<<((flag & S_IWOTH)? "w":"-");
    cout<<((flag & S_IXOTH)? "x":"-");
    cout<<" ";
    string owner_name="";
    if (getpwuid(entity.st_uid) != NULL)
        owner_name=getpwuid(entity.st_uid)->pw_name;
    cout<<"\033[34m";
    cout<<setw(15)<<owner_name;
    cout<<"\033[0m";
    cout<<" ";
    string group_name="";
    if(getgrgid(entity.st_gid)!=NULL)
        group_name=getgrgid(entity.st_gid)->gr_name;
    cout<<"\033[34m";
    cout<<setw(15)<<group_name;
    cout<<"\033[0m";
    cout<<" ";
    pair<double,string> size=get_human_readable(entity.st_size);
    cout << setw(10)<< fixed << setprecision(2) << size.first;
    cout <<" ";
    cout << setw(2)<<size.second;
    cout<<" ";
    string mod_time=ctime(&entity.st_mtime);
    mod_time.pop_back();
    cout<<"\033[33m";
    cout<<setw(26)<<mod_time;
    cout<<"\033[0m";
    cout<<" ";
    switch (flag & S_IFMT)
    {
        case S_IFDIR:  highlight_green(name);break;
        case S_IFLNK:  highlight_blue(name);break;
        default:
        cout<<name;
    }
    cout<<endl;
}