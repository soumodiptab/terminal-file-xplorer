#include "headers.h"
bool create_file(string &filename, string &destination_path)
{
    string final_path=parse(destination_path,filename);
    int return_status=creat(final_path.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if(return_status==-1)
    {
        return false;
    }
    else 
        return true;
}
void create_file_util(vector<string> &tokens)
{
    //token[0] is command token[1] is file token[n-1] is directory
    /*
    1: if no destination path given then create in current directory
    2:first find if path is relative or absolute
    3:check if 1 file given or multiple files (for now do 1 file)
    */
    bool flag=true;
    vector<string>errors;
    if(tokens.size()==1)
    {
        error("No arguments provided");
        return;
    }
    if(tokens.size()==2)
    {
         if(!create_file(tokens[1],dir_current_path))
         {
             errors.push_back(tokens[1]);
         }
    }
    else
    {
        string destination_path=path_processor(tokens[tokens.size()-1]);
        for(int i=1;i<tokens.size()-1;i++)
        {
            if(!create_file(tokens[i],destination_path))
            {
                errors.push_back(tokens[i]);
            }
        }
    }
    if(errors.empty())
    {
        success("File/s created successfully");
    }
    else
    {
        string message="";
        for(string i:errors)
        {
            message=message+" "+i;
        }
        error("Unable to create: ["+message+" ]");
    }
}

bool create_directory(string &dir_name, string &destination_path)
{

    string final_path=parse(destination_path,dir_name);

    int return_status=mkdir(final_path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(return_status==-1)
    {
        return false;
    }
    else 
        return true;
}
void create_directory_util(vector<string> &tokens)
{
    bool flag=true;
    vector<string>errors;
    if(tokens.size()==1)
    {
        error("No arguments provided");
        return;
    }
    if(tokens.size()==2)
    {
         if(!create_directory(tokens[1],dir_current_path))
         {
             errors.push_back(tokens[1]);
         }
    }
    else
    {
        string destination_path=path_processor(tokens[tokens.size()-1]);
        for(int i=1;i<tokens.size()-1;i++)
        {
            if(!create_directory(tokens[i],destination_path))
            {
                errors.push_back(tokens[i]);
            }
        }
    }
    if(errors.empty())
    {
        success("Directory/ies created successfully");
    }
    else
    {
        string message="";
        for(string i:errors)
        {
            message=message+" "+i;
        }
        error("Unable to create: ["+message+" ]");
    }
}