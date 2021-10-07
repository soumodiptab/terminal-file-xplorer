#include "headers.h"
bool delete_file(string &name, string &destination_path)
{
    string final_path=parse(destination_path,name);
    int return_status=remove(final_path.c_str());
    if(return_status==-1)
    {
        return false;
    }
        return true;
}
bool delete_directory(string &name, string &destination_path)
{
    
}
void delete_file_util(vector<string> &tokens)
{
    bool flag=true;
    vector<string>errors;
    if(tokens.size()==1)
    {
        error("No arguments provided");
        return;
    }
    else if(tokens.size()==2)
    {
         if(!delete_file(tokens[1],dir_current_path))
         {
             errors.push_back(tokens[1]);
         }
    }
    else
    {
        string destination_path=path_processor(tokens[tokens.size()-1]);
        for(int i=1;i<tokens.size()-1;i++)
        {
            if(!delete_file(tokens[i],destination_path))
            {
                errors.push_back(tokens[i]);
            }
        }
    }
    if(errors.empty())
    {
        success("File/s deleted successfully");
    }
    else
    {
        string message="";
        for(string i:errors)
        {
            message=message+" "+i;
        }
        error("Unable to delete: ["+message+" ]");
    }
}
void delete_directory_util(vector<string> &tokens)
{

}