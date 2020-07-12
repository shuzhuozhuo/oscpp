//
// Created by shu on 2020/7/12.
//

#ifndef OSCPP_FILE_H
#define OSCPP_FILE_H

namespace filelib{
    bool file_exists(const std::string &path);
    bool is_dir(const std::string &path);
    std::vector<std::string> listDir(const std::string &dir_path, bool addPrefix = false);
    void listAppend(std::vector<std::string>&src, const std::vector<std::string>& candidate);
    std::vector<std::string> listAllPath(const std::string &dir_path);
    std::vector<std::string>  getPathList(const std::string& path, const std::string& suffix);
    void testFileLib();
}

#endif //OSCPP_FILE_H
