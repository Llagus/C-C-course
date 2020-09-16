/*********************************************************
Homework 1: Convert a C program to C++
**********************************************************/

#include <iostream>
#include <vector>
using namespace std; 
const int lenght = 60;

//create the function sum, that will sum all the elements of a vector
inline void sum (int& result, int range, vector<int> v){
    result = 0;
    for(int i = 0; i < range; ++i){
        result = result + v[i];
    }
}

int main(){
    //initialize variables
    int acum;
    vector<int> numeric_list(lenght); 
    //fill the empty vector
    for(int i = 0; i < lenght; ++i){
        numeric_list[i]=i;
    }
    //call function sum and display the results
    sum(acum, lenght, numeric_list);
    cout <<"Sum is "<< acum << endl;
    return 0;
}

/*********************************************************
end of code. 
**********************************************************/