#include "headers.h"
void go_to(vector<string> params)
{
    if(params.size()==1)
    {
        error("Target directory not provided");
    }
    else if(params.size()==2)
    {
        string destination_path=path_processor(params[1]);
        if(directory_query(destination_path))
        {
            dir_backward_stream.push(dir_current_path);
            dir_current_path=destination_path;
            refresh_screen();
            success("Moved to : ["+dir_current_path+"]");
        }
        else
        {
            error("Invalid target directory");
        }
    }
    else
    {
        error("Incorrect number of parameters");
    }
}