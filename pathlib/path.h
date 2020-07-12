//
// Created by shu on 2020/7/7.
//

#ifndef PATH_LIB_H
#define PATH_LIB_H

#include <cstring>
#include "vector"

extern std::string SEP;

namespace pathlib{
    std::string dirname(std::string path);
    std::vector<std::string> split(std::string path);
    std::vector<std::string> _splittext(const std::string& path, const std::string&  altsep, const std::string& extsep);
    std::vector<std::string> splittext(std::string path);
    std::string basename(std::string path);

    template <typename T>
    std::string join(std::initializer_list<T> list);

    std::string removeRedundantSep(const std::string& path);

    std::vector<std::string> listAllPath(std::string path);
}
void test();
#endif //UNTITLED_PATH_LIB_H

