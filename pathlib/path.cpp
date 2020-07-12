#include<string>
#include<cstdarg>
#include "iostream"
#include<vector>
#include"path.h"

using namespace std;

string SEP = "/";

vector<string> pathlib::split(string path){

    int length = path.length();
    int i = length;
    vector<string> result;
    string head;
    string tail;
    string temp;
    while(true){
        temp = path[i-1];
        if ((i > 0) && (temp!=SEP)){
            i--;
        }
        else break;
    }
    std::cout << "i is " << i << endl;
    head = path.substr(0, i);
    tail = path.substr(i);

    result.push_back(head);
    result.push_back(tail);
    return result;
}

string pathlib::dirname(string path) {
    vector<string> path_vec = pathlib::split(std::move(path));
    return path_vec[0];
}

string pathlib::basename(string path) {
    vector<string> path_vec = pathlib::split(std::move(path));
    return path_vec[0];
}

vector<string> pathlib::_splittext(const string& path, const string& altsep, const string& extsep) {
    vector<string> result;
    string head, tail, temp;
    int dot_index, sep_index, filename_index;

    sep_index = path.rfind(altsep);
    dot_index = path.rfind(extsep);


    if(dot_index > sep_index){
        filename_index = sep_index + 1;
        while (filename_index <= dot_index){
            temp = path.substr(filename_index, filename_index+1);
            if(temp != extsep){
                head = path.substr(0, dot_index);
                tail = path.substr(dot_index);
                result.push_back(head);
                result.push_back(tail);
                return result;
            }
            filename_index += 1;
        }
    }
    result.push_back(path);
    tail = path.substr(0, 0);
    result.push_back(tail);
    return result;
}

vector<string> pathlib::splittext(string path) {
    return pathlib::_splittext(path, "/", ".");
}

string pathlib::removeRedundantSep(const string& path){
    string new_path;
    int length = path.size();
    int new_length = 0;

    for(int i = 0; i < length; i++){
        if(i == 0){
            new_path.append(path.substr(i, i + 1));
            new_length += 1;
        }
        else{
            if(path.substr(i, 1) == SEP){
                if(new_path.substr(new_length - 1, 1) == SEP){
                    ;
                }
                else{
                    new_path.append(path.substr(i, 1));
                    new_length += 1;
                }
            }
            else {
                new_path.append(path.substr(i, 1));
                new_length += 1;
            }
        }
    }
    return new_path;
}

template <typename T>
string pathlib::join(std::initializer_list<T> list){
    string str;
    for(T i: list){
        str += i;
        str += SEP;
    }
    str.pop_back();
    return pathlib::removeRedundantSep(str);
}



void test(){

    string args1 = "/home/pi";
    string args2 = "zengshu";
    string args3 = "/abc";
    string path;
    path = pathlib::join({args1, args2, args3});
    cout << "join path is " << path << endl;
    vector<string> a;
    a = pathlib::splittext(path);
    cout << "0" << a[0] << endl;
    cout << "1" << a[1] << endl;
}