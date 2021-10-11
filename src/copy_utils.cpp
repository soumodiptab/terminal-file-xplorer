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
    size_t offset_size;
    while((offset_size=read(file_descriptor_source,&buffer,optimal_buffer_size))>0)
    {
        write(file_descriptor_dest,&buffer,offset_size);
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
    int return_status=mkdir(destination.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(return_status==-1)
    {
        return false;
    }
    struct stat directory;
    if(stat(source.c_str(),&directory)==-1)
    {
        return false;
    }
    set_metadata(destination,directory);
    return true;
}

bool copy_directory_recursive(string &source_path,string &destination_path)
{
    bool flag=true;
    DIR* dir_stream=opendir(source_path.c_str());
    if(dir_stream==NULL)
    {
        return false;
    }
    string new_dest_path=parse(destination_path,extract_name(source_path));
    copy_directory(source_path,new_dest_path);

    struct dirent* entity=readdir(dir_stream);
    while(entity!=NULL)
    {
        string branch_source_path=parse(source_path,string(entity->d_name));
        if(strcmp(entity->d_name,".")!=0 && strcmp(entity->d_name,"..")!=0)
        {
            struct stat new_entity;
            if(stat(branch_source_path.c_str(),&new_entity)!=-1)
            {
                if(S_ISDIR(new_entity.st_mode))
                {
                    flag&=copy_directory_recursive(branch_source_path,new_dest_path);
                }
                else
                {
                    string branch_dest_path=parse(new_dest_path,string(entity->d_name));
                    flag&=copy_file(branch_source_path,branch_dest_path);
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
        error("Invalid number of arguments");
        return;
    }
    else
    {
        string destination_path=path_processor(tokens[tokens.size()-1]);
        if(!directory_query(destination_path))
        {
            error("Destination directory does not exist");
            return;
        }
        for(int i=1;i<tokens.size()-1;i++)
        {
            string eval_source_path=parse(dir_current_path,tokens[i]);
            if(directory_query(eval_source_path))
            {
                copy_directory_recursive(eval_source_path,destination_path);
                refresh_screen();
            }
            else if(file_query(eval_source_path))
            {
                string new_dest_path=parse(destination_path,tokens[i]);
                copy_file(eval_source_path,new_dest_path);
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
        success("Files/Folders successfully copied");
    }
    else
    {
        string message="";
        for(string i:errors)
        {
            message=message+" "+i;
        }
        error("Unable to copy: ["+message+" ]");
    }
}