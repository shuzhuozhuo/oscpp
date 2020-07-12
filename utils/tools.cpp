#include"tools.h"
#include<iostream>
#include<vector>

template<typename T>
void ostools::show1dVector(std::vector<T> vec){

    for(T value : vec){
        std::cout << value << std::endl;
    }
}

