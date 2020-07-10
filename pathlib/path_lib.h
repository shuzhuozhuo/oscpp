//
// Created by shu on 2020/7/7.
//

#ifndef UNTITLED_PATH_LIB_H
#define UNTITLED_PATH_LIB_H

#endif //UNTITLED_PATH_LIB_H

#include "string.h"
#include "vector"

using namespace std;

string SEP = "/";

namespace pathlib{
    string dirname(string path);
    vector<string> split(string path);
    vector<string> _splittext(const string& path, const string&  altsep, const string& extsep);
    vector<string> splittext(string path);
    string basename(string path);

    template <typename T>
    string join(std::initializer_list<T> list);

    string removeRedundantSep(const string& path);

    vector<string> listAllPath(string path);
}