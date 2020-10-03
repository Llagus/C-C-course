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


class Node{
    public: 
        int id,current_cost; 
        bool visited; 
        
        Node(int id = 0, bool visited = false, int current_cost = 0):id(id),visited(visited),current_cost(current_cost){}

        bool operator==(Node& node){
            if(this->current_cost==node.current_cost && this->id == node.id && this->visited == node.visited) return true; 
            return false;
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
                this->nodes[i] = {i,false,0}; 
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

        Graph():nodes(0),l_edge(0),graph(0){}//null constructor

        //Methods
        int N_nodes(){return this->nodes.size();}

        int N_edges(){return this->l_edge.size();}

        bool adjacent(int x, int y){
            for(vector<graphEdge>::iterator it = l_edge.begin(); it!=l_edge.end(); ++it){
                if (it->start_ver==x && it->end_ver == y) return true; 
            }
            return false; 
        }

        vector<graphEdge> neighbors(int x){
            vector<graphEdge> neighbors; 
            cout<<"The node "<<x<<" has and edge with:";
            for (vector<graphEdge>::iterator it = l_edge.begin(); it!=l_edge.end(); ++it){
                if (it->start_ver==x){
                    neighbors.push_back(*it);
                    cout<<it->end_ver<<" "; 
                }
            }
            cout<<endl; 
            return neighbors; 
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

        void del(int node_x, int node_y){
            int i = 0;
            if(this->adjacent(node_x, node_y)){
                this->graph[node_x][node_y] = 0;

                for(vector<graphEdge>::iterator it = this->l_edge.begin(); it!= this->l_edge.end(); ++it){
                    if(it->start_ver==node_x && it->end_ver==node_y){
                        l_edge.erase(it); 
                        break;
                    }
                }
            }
            else{
                cout<<"This edge doesn't exist"<<endl;
            }
        }

        graphEdge get_edge(int node_x, int node_y){
            for(vector<graphEdge>::iterator  it = this->l_edge.begin(); it!=this->l_edge.end(); ++it){
                if (it->start_ver == node_x && it->end_ver == node_y) return *it;
            }
            cout<<"This edge doesn't exit."<<endl; 
            return 0;  
        }

        int get_edge_value(int node_x, int node_y){
            return this->graph[node_x][node_y];
        }

        void set_edge_value(int node_x, int node_y, int value){
            for (vector<graphEdge>::iterator it = this->l_edge.begin();it!=this->l_edge.end(); ++it){
                if (it->start_ver==node_x && it->end_ver==node_y){
                    it->cost = value;
                    break;
                }
            }
            graphEdge e = {node_x, node_y, value}; 
            this->l_edge.push_back(e);
            this->graph[node_x][node_y] = e.cost; 
        }

        void print();

    private:
        vector<Node> nodes; 
        vector<graphEdge> l_edge;
        vector<vector<int>> graph; 
};


class PriorityQueue{
    public:
        PriorityQueue():queue(0){}//null constructor

        PriorityQueue(Node node){
            this->queue.push_back(node);
        }

        void chgPriority(int priority){}
        //removes the top element of the queue; 
        void minPriority(){
            for(vector<Node>::iterator it = this->queue.begin(); it!=this->queue.end(); ++it){
                this->queue.erase(it); 
                break; 
            }
        }

        bool contains(Node node){
            Node n;  
            return n == node;
            for(vector<Node>::iterator it = this->queue.begin(); it!=queue.end(); ++it ){
                if (node == *it) return true;
            }
            return false; 
        }

        void insert(Node node){
            if (this->contains(node)){
                cout<<"This node is already in the queue"<<endl; 
            }else{
                for(vector<Node>::iterator it = this->queue.begin(); it!=queue.end(); ++it ){
                    if (it->id != node.id){
                        if (it->current_cost>node.current_cost|| static_cast<Node>(0,false,0) == *it){ 
                        this->queue.emplace(it,node);
                        break;
                        }
                    }else if(it->id == node.id && it->current_cost>node.current_cost){
                        this->queue.emplace(it,node); 
                        break;
                    }                  
                }
            }   
        }
        void resize(int lenght){
            this->queue.resize(lenght);
        } 

        Node* top(){
            return &this->queue.front(); 
        }

        Node back(){
            return this->queue.back();
        }

        int size(){
            return this->queue.size();
        }

        bool empty(){
            return this->queue.empty();
        }

    private:
        vector<Node> queue; 
};


class ShortestPath{
    public:
        //constructor 
        ShortestPath(Graph* g = 0, Node* start_node = 0, Node* end_node= 0):g(g),start_node(start_node),end_node(end_node){
            this->close_set->resize(g->N_nodes());
            this->open_set->resize(g->N_nodes());
        }

        void vertices(Node start_node){
            vector<graphEdge> neighbors = this->g->neighbors(start_node.id);
            for(vector<graphEdge>::iterator it = neighbors.begin(); it!= neighbors.end();++it){
                Node* n = new Node(it->end_ver,false,it->cost+start_node.current_cost);
                this->open_set->insert(*n); 
            }            

        }

        void path(Node node_x, Node node_y){
            this->close_set->insert(node_x); 
            this->current_node = &node_x;    
            this->vertices(*this->current_node);
            while(!this->close_set->contains(node_y)||this->open_set->empty()){
                this->close_set->insert(*this->open_set->top()); 
                this->current_node = this->open_set->top();
                
                vertices(*current_node);
            }
        }

        int path_size(Node node_x, Node node_y){
            this->close_set->insert(node_x); 
            this->current_node = &node_x;    
            this->vertices(*this->current_node);
            while(!this->close_set->contains(node_y)||this->open_set->empty()){
                this->close_set->insert(*this->open_set->top()); 
                this->current_node = this->open_set->top();
                this->open_set->minPriority();
                vertices(*current_node);
            }
            return this->close_set->back().current_cost;
        }

    private: 
        Graph *g = new Graph(); 
        PriorityQueue *close_set = new PriorityQueue();
        PriorityQueue *open_set = new PriorityQueue(); 
        Node* start_node = new Node();
        Node* end_node = new Node(); 
        Node* current_node = new Node();
        vector<graphEdge> l_edge; 
};


int main (){

    const int n_nodes = 7; 
    const double density = 0.2; 
    //radomize values
    srand(time(0));//create the seed
    Graph* g = new Graph(n_nodes, density);  
    Node* start_node = new Node(0,false,0);
    Node* end_node = new Node(n_nodes-1, false, 0);
    cout<<"The number of nodes is: "<<static_cast<int>(g->N_nodes())<<endl;
    cout<<"The number of edges is:"<<g->N_edges()<<endl;
    cout<<"The nodes 1 have and edge with node 3: "<<static_cast<bool>(g->adjacent(1,3))<<endl; 
    g->add(3,0);
    g->neighbors(3); 
    g->del(3,0);
    g->neighbors(3);
    ShortestPath* dijkstra = new ShortestPath(g, start_node, end_node);
    cout<<"the path size from node:"<<start_node->id<<" to node: "<<end_node->id<<" is "<<dijkstra->path_size(start_node->id,end_node->id)<<endl;
    //g.print();

    return 0; 
}
/***************************
 * End of code
***************************/

