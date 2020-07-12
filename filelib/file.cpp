
#include <iostream>
#include <dirent.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h> 
#include <cstring>
#include <vector>
#include "../pathlib/path.h"
#include "file.h"
#include "../utils/tools.h"

using namespace std;

bool filelib::file_exists(const std::string &path){
    return access(path.c_str(), F_OK) == 0;
}

bool filelib::is_dir(const std::string &path){
    struct stat stat_buf{};
    lstat(path.c_str(), &stat_buf);
    return  S_ISDIR(stat_buf.st_mode);
}

std::vector<std::string> filelib::listDir(const std::string &dir_path, bool addPrefix){

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf{};
    std::vector<std::string> dirname_vec;
    std::string dirname;

    if ( (dp = opendir(dir_path.c_str())) == nullptr){
        
        std::cout << "Can not open the Directory " << dir_path << std::endl;
        return dirname_vec;
    }

    chdir(dir_path.c_str());
    // entry = readdir(dp);
    while ((entry = readdir(dp)) != nullptr){
        lstat(entry->d_name, &statbuf);
        // printf("Current d_name is %s\n", entry->d_name);
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        else {
            dirname = entry->d_name;
            if(! addPrefix) dirname_vec.push_back(std::move(dirname));
            else dirname_vec.push_back(pathlib::join({dir_path, dirname}));
        }
    }
    chdir("..");
    closedir(dp);
    return dirname_vec;
}

void filelib::listAppend(vector<string>&src, const vector<string>& candidate){
    for(const string& m : candidate) {
        src.push_back(m);
    }
}

vector<string> filelib::listAllPath(const string &dir_path){
    vector<string> all_path;
    vector<string> stack;
    vector<string> t_stack;
    string temp_path;

    if( ! filelib::is_dir(dir_path)){
//        all_path.push_back(dir_path);
        return all_path;
    }

    all_path = filelib::listDir(dir_path, true);

    for(auto& m : all_path){
        if(filelib::is_dir(m)) stack.push_back(m);
    }

    if(all_path.empty()){
        return all_path;
    }

    while (! stack.empty()) {
        temp_path = stack.back();
        stack.pop_back();

        if (filelib::is_dir(temp_path)) t_stack = filelib::listDir(temp_path, true);
        else {
            all_path.push_back(temp_path);
            continue;
        }

        if (t_stack.empty()) continue;
        else filelib::listAppend(all_path, t_stack);

        for(auto &m : t_stack){
            if(filelib::is_dir(m)) stack.push_back(m);
        }
    }

    return all_path;
}

vector<string>  filelib::getPathList(const string& path, const string& suffix) {
    vector<string> path_list;
    vector<string> temp_split;
    vector<string> all_path;
    if(! filelib::is_dir(path)){
        temp_split = pathlib::splittext(path);
        if(temp_split[1] == suffix){
            path_list.push_back(path);
        }
        return path_list;
    }

    else{
        all_path = filelib::listAllPath(path);
        for(string& value : all_path){
//            printf("path is : %s\n", value.c_str());
            temp_split = pathlib::splittext(value);
//            printf("suffix is : %s\n", temp_split[1].c_str());
            if(temp_split[1] == suffix){
                path_list.push_back(value);
            }
        }
    }
    return path_list;
}

void testFileLib(){
    std::string dirpath = "/media/shu/KINGSTON/CPP/7-6";
    std::vector<std::string> vec;
    vec = filelib::getPathList(dirpath, ".json");
    // for(std::string value : vec){
    //     std::cout << value << std::endl;}
    ostools::show1dVector(vec);
//    int length = vec.size();
//    printf("have %d files and dirs", length);
}
