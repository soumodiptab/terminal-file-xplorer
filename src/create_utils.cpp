#include "headers.h"
bool create_file(string &filename, string &destination_path)
{
    string final_path=destination_path+"/"+filename;
    int return_Stat=creat(final_path.c_str(), O_RDONLY | O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(return_Stat==-1)
        return false;
    else 
        return true;
}
bool create_file_util(vector<string> &tokens)
{
    //token[0] is command token[1] is file token[n-1] is directory
    /*
    1: if no destination path given then create in current directory
    2:first find if path is relative or absolute
    3:check if 1 file given or multiple files (for now do 1 file)
    */

    if(tokens.size()==1)
        return false;
    if(tokens.size()==2)
    {
        return create_file(tokens[0],dir_current_path);
    }
    else
    {
        string destination_path=path_processor(tokens[tokens.size()-1]);
        for(int i=1;i<tokens.size()-2;i++)
        {
            
        }
    }

}