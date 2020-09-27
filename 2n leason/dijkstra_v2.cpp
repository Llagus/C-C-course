#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Graph{
    public: 
        Graph(int size, double density){
            this->nodes.resize(size);
            for (int i = 0; i<size; i++){
                this->nodes[i] = i; 
            }
        }
        int n_nodes(){
            return this->nodes.size();
        }
    private: 
        vector<int> nodes; 
};

int main(){
    const int size = 7; 
    const double density = 0.2; 
    Graph* g = new Graph(size, density); 
    cout<<  g->n_nodes()<<endl;
    return 0; 
}