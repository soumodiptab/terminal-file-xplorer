#include "headers.h"
bool search(string path,string target)
{
    bool flag=false;
    DIR* dir_stream=opendir(path.c_str());
    if(dir_stream==NULL)
    {
        return false;
    }
    struct dirent* entity=readdir(dir_stream);
    while(entity!=NULL)
    {
        string new_path=parse(path,string(entity->d_name));
        if(string(entity->d_name) == target)
        {
            success("Found at [ "+new_path+" ]");
            closedir(dir_stream);
            return true;
        }
        if(entity->d_type == DT_DIR && strcmp(entity->d_name,".")!=0 && strcmp(entity->d_name,"..")!=0)
        {
            flag= flag || search(new_path,target);
            if(flag)
            {
                closedir(dir_stream);
                return flag;   
            }
        }
        entity=readdir(dir_stream);
    }
    closedir(dir_stream);
    return false;
}
void search_util(vector<string> &tokens)
{
    if(tokens.size()==1)
    {
        error("No arguments provided");
    }
    if(tokens.size()==2)
    {
        if(!search(dir_current_path,tokens[1]))
        {
            error("Could not find Folder/File");
        }  
    }
    else
    {
        error("Too many arguments provided");
    }
}