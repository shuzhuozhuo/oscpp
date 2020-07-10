#include<string>
#include<cstdarg>

using namespace std;

template<typename T>
T addString(std::initializer_list<T> list){
    string str;
    int length = list.size();
    for(T i: list){
        cout << "i is :" << i  <<endl;
        str += i;
    }
    cout << "length" << length << endl;
    // for(int i = 0; i < length; i++){
    //     // str += list[i];
    //     ;
    // }
    cout << "str is : " << str << endl;
    return str;
}

void test(){

    string args1 = "123";
    addString({args1, args1, args1});

}