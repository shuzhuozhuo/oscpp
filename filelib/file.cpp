#include <iostream>
#include <dirent.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <string.h>
#include <vector>
#include "../utils/tools.cpp"

bool file_exists(const std::string &path){
    if(access(path.c_str(), F_OK) == 0){
        return true;
    }
    else return false;
}

std::vector<std::string> listDir(const std::string &dir_name){

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    std::vector<std::string> dirname_vec;
    std::string dirname;

    if ( (dp = opendir(dir_name.c_str())) == NULL){
        
        std::cout << "Can not open the Directory " << dir_name << std::endl;
    }

    chdir(dir_name.c_str());
    // entry = readdir(dp);
    while ((entry = readdir(dp)) != NULL){
        lstat(entry->d_name, &statbuf);
        // printf("Current d_name is %s\n", entry->d_name);
        if(S_ISDIR(statbuf.st_mode)){
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
            else {
                dirname = entry->d_name;
                dirname_vec.push_back(std::move(dirname));
                }
        }
    }
    chdir("..");
    closedir(dp);
    return dirname_vec;
}



void testFileLib(){
    std::string dirpath = "/home/pi/7-6";
    std::vector<std::string> vec;
    vec = listDir(dirpath);
    // for(std::string value : vec){
    //     std::cout << value << std::endl;}
    ostools::show1dVector(vec);
}
