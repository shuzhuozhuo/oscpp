#include <iostream>
#include <dirent.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <cstring>
#include <vector>
#include "../utils/tools.cpp"

bool file_exists(const std::string &path){
    return access(path.c_str(), F_OK) == 0;
}

bool is_dir(const std::string &path){
    struct stat stat_buf{};
    lstat(path.c_str(), &stat_buf);
    return  S_ISDIR(stat_buf.st_mode);
}

std::vector<std::string> listDir(const std::string &dir_path, bool addPrefix = false){

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf{};
    std::vector<std::string> dirname_vec;
    std::string dirname;

    if ( (dp = opendir(dir_path.c_str())) == nullptr){
        
        std::cout << "Can not open the Directory " << dir_path << std::endl;
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

void listAppend(vector<string>&src, const vector<string>& candidate){
    for(const string& m : candidate) {
        src.push_back(m);
    }
}

vector<string> listAllPath(const string &dir_path){
    vector<string> all_path;
    vector<string> stack;
    vector<string> t_stack;
    string temp_path;

    if( ! is_dir(dir_path)){
//        all_path.push_back(dir_path);
        return all_path;
    }

    all_path = listDir(dir_path, true);

    for(auto& m : all_path){
        if(is_dir(m)) stack.push_back(m);
    }

    if(all_path.empty()){
        return all_path;
    }

    while (! stack.empty()) {
        temp_path = stack.back();
        stack.pop_back();

        if (is_dir(temp_path)) t_stack = listDir(temp_path, true);
        else {
            all_path.push_back(temp_path);
            continue;
        }

        if (t_stack.empty()) continue;
        else listAppend(all_path, t_stack);

        for(auto &m : t_stack){
            if(is_dir(m)) stack.push_back(m);
        }
    }

    return all_path;
}

void testFileLib(){
    std::string dirpath = "/media/shu/KINGSTON/CPP/7-6/";
    std::vector<std::string> vec;
    vec = listAllPath(dirpath);
    // for(std::string value : vec){
    //     std::cout << value << std::endl;}
    ostools::show1dVector(vec);
}
