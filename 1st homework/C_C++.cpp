/*********************************************************
Homework 1: Convert a C program to C++
**********************************************************/

#include <iostream>
#include <vector>
using namespace std; 
const int lenght = 40;
inline void sum (int& result, int range, vector<int> v){
    result = 0;
    for(int i = 0; i < range; ++i){
        result += v[i];
    }
}

int main(){
    int acum;
    vector<int> numeric_list; 
    //create the vector
    for(int i = 0; i < lenght; ++i){
        numeric_list[i]=i;
    }
    sum(acum, lenght, numeric_list);
    cout <<"Sum is"<< acum << endl;
    return 0;
}