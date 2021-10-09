#include "headers.h"
void set_metadata(string path,struct stat meta)
{
    chmod(path.c_str(),meta.st_mode);
    chown(path.c_str(),meta.st_uid,meta.st_gid);
}

bool copy_file(string &source,string &destination)
{
    int file_descriptor_source,file_descriptor_dest;
    struct stat source_details;
    file_descriptor_source=open(source.c_str(),O_RDONLY);
    file_descriptor_dest=open(destination.c_str(),O_WRONLY | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH);
    if(file_descriptor_source==-1 || file_descriptor_dest ==-1)
    {
        close(file_descriptor_source);
        close(file_descriptor_dest);
        return false;
    }
    stat(source.c_str(),&source_details);
    blksize_t optimal_buffer_size= source_details.st_blksize;
    char buffer[optimal_buffer_size];
    while(read(file_descriptor_source,&buffer,optimal_buffer_size))
    {
        write(file_descriptor_dest,&buffer,optimal_buffer_size);
    }
    close(file_descriptor_source);
    close(file_descriptor_dest);
    set_metadata(destination,source_details);
    return true;

}
/**
 * @brief create empty directory
 * 
 * @param source 
 * @param destination 
 * @return true 
 * @return false 
 */
bool copy_directory(string &source,string &destination)
{

}

bool copy_directory_recursive(string &source_path,string &destination_path)
{
    bool flag=true;
    DIR* dir_stream=opendir(source_path.c_str());
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

void copy_util(vector<string> &tokens)
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
        refresh_screen();
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