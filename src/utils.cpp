#include "headers.h"
vector<string> input_processor(string input)
{
    vector<string>tokens;
    string temp_str="";
    for( char c:input)
    {
        if(c==' ')
        {
            tokens.push_back(temp_str);
            temp_str="";
        }
        else
        {
            temp_str+=c;;
        }
    }
    return tokens;
}
string path_processor(string &path)
{
    
}