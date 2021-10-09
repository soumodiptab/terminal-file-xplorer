#include "headers.h"
bool rename_file(string &old_name,string &new_name)
{
    int return_status = rename(old_name.c_str(), new_name.c_str());
    if (return_status == -1)
    {
        return false;
    }
    return true;
}
void rename_util(vector<string>&tokens)
{
    if(tokens.size()==1)
    {
        error("No arguments provided");
        return;
    }
    else if(tokens.size()==3)
    {
        string old_filename=parse(dir_current_path,tokens[1]);
        string new_name=parse(dir_current_path,tokens[2]);
        if(rename_file(old_filename,new_name))
        {
            refresh_screen();
            success("File has been renamed from [ "+tokens[1]+" to "+tokens[2]+" ]");
        }
        else
        {
            error("Unable to rename file");
        }
    }
    else
    {
        error("Invalid number of arguments");
    }
}