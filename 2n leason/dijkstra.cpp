/********************************
 *Dijkstra shortest path algoritm
 *******************************/ 
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std; 

class graphEdge{
    public:
    int start_ver, end_ver, cost;
    graphEdge(int start_ver = 0, int end_ver = 0, int cost = 0):start_ver(start_ver),end_ver(end_ver), cost(cost){
        
    }
};

ostream& operator<< (ostream& out,graphEdge& e){
    out<<"Nodes:"<< e.start_ver<<","<< e.end_ver<< "\t cost:" << e.cost<<endl;
    return out; 
}


double prob(){
    double prob = 0.0; 
        prob = rand()%360; 
        if (prob > 360.0) prob = 1.0; 
        else if (prob < 0.0 ) prob = 0.0; 
        else prob = prob/360.0; 
    return prob; 
}

class Graph{
    public: 
        Graph(int n_nodes, double density){//random graph constructor
            this->nodes.resize(n_nodes);
            this->graph.resize(n_nodes, vector<int> (n_nodes));
            for(int i = 0; i < n_nodes; i++){
                this->nodes[i] = i; 
                for(int j = 0; j < n_nodes; j++){
                    if(i==j||(prob()>density)) this->graph[i][j]= this->graph[j][i]= 0;
                    else{
                        graphEdge edge = {i,j,rand()%10};
                        this->graph[i][j] = edge.cost;
                        this->l_edge.push_back(edge); 
                    } 
                }
            }
        }
        //Graph():nodes(0),l_edge(0),graph(0){}//null constructor
        int N_nodes(){return this->nodes.size();}
        int N_edges(){return this->l_edge.size();}
        bool adjacent(int x, int y){
            for(vector<graphEdge>::iterator it = l_edge.begin(); it!=l_edge.end(); ++it){
                if (it->start_ver==x && it->end_ver == y) return true; 
            }
            return false; 
        }
        void neighbors(int x){
            cout<<"The node "<<x<<" has and edge with:";
            for (vector<graphEdge>::iterator it = l_edge.begin(); it!=l_edge.end(); ++it){
                if (it->start_ver==x){
                    cout<<it->end_ver<<" "; 
                }
            }
            cout<<endl; 
        }
        void add(int node_x, int node_y){
            if (this->adjacent(node_x,node_y)){
                cout<<"This edge already exist"<<endl;
            }else{
                graphEdge e = {node_x, node_y, rand()%10}; 
                this->l_edge.push_back(e);
                this->graph[node_x][node_y] = e.cost; 
            }
        }


        void print();



    private:
        vector<int> nodes; 
        vector<graphEdge> l_edge;
        vector<vector<int>> graph; 
};
/*
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
        Graph():edgeList(0){}
};*/


int main (){

    const int n_nodes = 7; 
    const double density = 0.2; 
    //radomize values
    srand(time(0));//create the seed
    Graph* g = new Graph(n_nodes, density);  
    cout<<"The number of nodes is: "<<static_cast<int>(g->N_nodes())<<endl;
    cout<<"The number of edges is:"<<g->N_edges()<<endl;
    cout<<"The nodes 1 have and edge with node 3: "<<static_cast<bool>(g->adjacent(1,3))<<endl; 
    g->add(3,0);
    g->neighbors(3); 
    
    //g.print();

    return 0; 
}
/***************************
 * End of code
***************************/

