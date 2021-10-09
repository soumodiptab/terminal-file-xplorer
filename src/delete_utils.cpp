#include "headers.h"
bool delete_file(string &destination_path)
{
    int return_status=remove(destination_path.c_str());
    if(return_status==-1)
        return false;
    return true;
}

bool delete_directory(string &destination_path)
{
    int return_status=rmdir(destination_path.c_str());
    if(return_status==-1)
        return false;
    return true;
}
void delete_file_util(vector<string> &tokens)
{
    if(tokens.size()==1)
    {
        error("No arguments provided");
        return;
    }
    else if(tokens.size()==2)
    {
        string destination_path=path_processor(tokens[1]);
        if(delete_file(destination_path))
        {
            refresh_screen();
            success("Successfully deleted: [ "+destination_path+" ]");
        }
        else
        {
            error("Unable to delete: ["+destination_path+" ]");
        }
    }
    else
    {
        error("Too many arguments provided");
    }
}
bool delete_directory_recursive(string &path)
{
    bool flag=true;
    DIR* dir_stream=opendir(path.c_str());
    if(dir_stream==NULL)
    {
        return false;
    }
    struct dirent* entity=readdir(dir_stream);
    while(entity!=NULL)
    {
        string new_path=parse(path,string(entity->d_name));
        if(strcmp(entity->d_name,".")!=0 && strcmp(entity->d_name,"..")!=0)
        {
            struct stat new_entity;
            if(stat(new_path.c_str(),&new_entity)!=-1)
            {
                if(S_ISDIR(new_entity.st_mode))
                {
                    flag&=delete_directory_recursive(new_path);
                }
                else
                {
                    flag&=delete_file(new_path);
                }
            }
        }
        if(!flag)
        {
            closedir(dir_stream);
            return flag;
        }
        entity=readdir(dir_stream);
    }
    closedir(dir_stream);
    delete_directory(path);
    return flag;
}
void delete_directory_util(vector<string> &tokens)
{
    if(tokens.size()==1)
    {
        error("No arguments provided");
        return;
    }
    else if(tokens.size()==2)
    {
        string destination_path=path_processor(tokens[1]);
        if(directory_query(destination_path))
        {
            if(delete_directory_recursive(destination_path))
            {
                refresh_screen();
                success("Successfully deleted: [ "+destination_path+" ]");
            }
            else
            {
                error("Could not delete directory");
            }
        }
        else
        {
            error("Directory does not exist");
        }
    }
    else
    {
        error("Too many arguments provided");
    }
}