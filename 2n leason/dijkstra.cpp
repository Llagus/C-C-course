/********************************
 *Dijkstra shortest path algoritm
 *******************************/ 
#include <iostream>
#include <vector>
using namespace std; 

struct graphEdge{
    int start_ver, end_ver, cost;
};
class Graph{
    public: 
        //construct a vector of vectors to represent an edge list
        vector<vector<int>> edgeList; 
        // Graph constructor
        Graph(vector<graphEdge> const &graphEdge, int N){
            edgeList.resize(N);
            //add edges to the directed graph
            for (auto &graphEdge: graphEdge){
                edgeList[graphEdge.start_ver].push_back(graphEdge.end_ver); 
            }
        }

};


int main (){
    int V = 5; 
    vector<int> graph[V];

    return 0; 
}
/***************************
 * End of code
***************************/

