#include <iostream>
#include <ctime> 
#include <cstdlib>
using namespace std; 

double prob(){
    double prob = 0.0; 
        prob = rand()%360; 
        if (prob > 360.0) prob = 1.0; 
        else if (prob < 0.0 ) prob = 0.0; 
        else prob = prob/360.0; 
    return prob; 
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
}

