#include <iostream>
#include <ctime> 
#include <cstdlib>
#include "C++_course/shit.h"
using namespace std; 

double prob(){
    double prob = 0.0; 
        prob = rand()%360; 
        if (prob > 360.0) prob = 1.0; 
        else if (prob < 0.0 ) prob = 0.0; 
        else prob = prob/360.0; 
    return prob; 
}

bool is_connected(bool* graph[], int size){

    //initialize open and close arrays:
    int old_size = 0, c_size = 0;
    bool* close = new bool[size];
    bool* open = new bool[size];
    for(int i = 0; i < size; i++)
        open[i]=close[i]=false;
    open[0] = true;

    while(c_size<size){
        for (int i = 0; i < size; ++i){
            old_size = c_size;
            if (open[i]&&(close[i]==false)){
                close[i]= true;
                c_size++;
            }
            for (int j = 0; j < size;j++){
                open[j] = open[j]||graph[i][j];
            }
        }
        if (c_size == size) return true;
        if (old_size == c_size)return false;
    }

}

int main (){
    const int size = 7;
    const double density = 0.2; 

    //create a matrix from a graphs with the nodes:
    bool** graph; 
        srand(time(0));//seed
        graph = new bool*[size]; 
        for (int i = 0; i < size;i++){
            graph[i] = new bool[size]; 
        }
    //create the edges: 
    for (int i = 0;i < size; i++){
        for (int j = 0; j<size;j++){
            if (i == j) graph[i][j]= false; 
            else graph[i][j]=graph[j][i]=(prob()<density);
        }
    }
    //represent the graph: 
    for (int i = 0;i < size; i++){
        cout<< i<<"->";
        for (int j = 0; j<size;j++){
            if (j == size -1){
                if (graph[i][j] == true)cout<<j<<endl;
                else cout<<endl;
            }
            else if (graph[i][j] == true) cout<< j<<",";    
        }
    }
    //graph connected or not?
    if (is_connected(graph, size)) cout<<"Is a connected graph"<<endl;
    else cout<<"Unconnected graph"<<endl;

    return 0;
}

