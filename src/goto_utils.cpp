#include "headers.h"
void go_to(vector<string> params)
{
    if(params.size()==1)
    {
        error("Target directory not provided");
    }
    else if(params.size()==2)
    {
        refresh_screen();
    }
    else
    {
        error("Incorrect number of parameters");
    }
}