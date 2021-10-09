#include "headers.h"
void move_util(vector<string> &tokens)
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
        error("Invalid number of arguments");
        return;
    }
    else
    {
        string destination_path=path_processor(tokens[tokens.size()-1]);
        if(!directory_query(destination_path))
        {
            error("Destination directory does not exist");
        }
        for(int i=1;i<tokens.size()-1;i++)
        {
            string eval_source_path=parse(dir_current_path,tokens[i]);
            if(directory_query(eval_source_path))
            {
                copy_directory_recursive(eval_source_path,destination_path);
                delete_directory_recursive(eval_source_path);
                refresh_screen();
            }
            else if(file_query(eval_source_path))
            {
                string new_dest_path=parse(destination_path,tokens[i]);
                copy_file(eval_source_path,new_dest_path);
                delete_file(eval_source_path);
                refresh_screen();
            }
            else
            {
                errors.push_back(tokens[i]);
            }
        }
    }
    if(errors.empty())
    {
        refresh_screen();
        success("Files/Folders successfully moved");
    }
    else
    {
        string message="";
        for(string i:errors)
        {
            message=message+" "+i;
        }
        error("Unable to move: ["+message+" ]");
    }
}