#include <iostream>
#include <cstdlib>
#include <cfloat>
#include <ctime>
#include <vector>
#include <iomanip>
#include <exception>
using namespace std;

const double MIN_DIST = 10.0;
const double MAX_DIST = 100.0;
const double RANGE = MAX_DIST - MIN_DIST;

typedef pair<int, double> edge;

double prob() {
    return double(rand())/RAND_MAX;
}

class Graph {
public:
    Graph(int n, double density);
    int V();
    int E();
    int adjacent(int u, int v);
    vector<int> neighbors(int u);
    void add(int u, int v, double dist);
    void remove(int u, int v);
    double get_node_value(int u);
    void set_node_value(int u, double a);
    double get_edge_value(int u, int v);
    void set_edge_value(int u, int v, double dist);
    void print(int x);
private:
    int n;
    vector <edge>* edges;
    double* vertices;
};

Graph::Graph(int n, double density){
    srand(time(0));
    this->n = n;
    edges = new vector <edge> [n];
    vertices = new double [n];
    int count = 0;

    for (int i = 0; i < n; i++){
        vertices[i] = DBL_MAX;
        for (int j = 0; j < n; j++){
            if (i == j) 
                continue;
            else
                if (prob() < density && !Graph::adjacent(i, j) && !Graph::adjacent(j, i)) {
                    double dist = (MIN_DIST + (rand() % int(RANGE)))/10.0;
                    Graph::add(i, j, dist);
                    count++;
                }           
        }
    }
};

int Graph::V(){
    return n;
}

int Graph::E(){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += edges[i].size();
    }
    return sum/2;
}

void Graph::add( int u, int v, double dist){
    edges[u].push_back(make_pair(v, dist));
    edges[v].push_back(make_pair(u, dist));
};

void Graph::remove(int u, int v){
    int w;
    int nodes[2] = {u, v};
    int flag = 1;

    auto it = find_if( edges[u].begin(), edges[u].end(), 
        [&v](const edge& element){ return (element.first == v);} );

    if (it != edges[u].end()) {
        edges[u].erase(it);
        auto it = find_if( edges[v].begin(), edges[v].end(), 
            [&u](const edge& element){ return (element.first == u);} );
        edges[v].erase(it);
    }
}


int Graph::adjacent(int u, int v){

    auto it = find_if( edges[u].begin(), edges[u].end(), 
        [&v](const edge& element){ return (element.first == v);} );
    bool output = (it != edges[u].end()) ? output : 0;

    return output;
}

vector<int> Graph::neighbors(int u){
    vector<int> neighbors_nodes;
    int w;

    for (auto it=edges[u].begin(); it!=edges[u].end(); it++){
        w = it->first;
        neighbors_nodes.push_back(w);
    }
    return neighbors_nodes;
}

void Graph::print(int x = RAND_MAX){
    double u, v;
    int length = (n > x) ? x : n;

    for (int i = 0; i < length; i++){
        cout << "Node " << i << "\n";
        for (auto it=edges[i].begin(); it!=edges[i].end(); it++){
            cout << "\t-> ";
            u = it->first;
            v = it->second;
            cout << "[" << u << ", dist=";
            cout << setprecision(2) << v << "]\n";
        }
        cout << "\n";
    }
}

double Graph::get_node_value(int u){
    return vertices[u];
}

void Graph::set_node_value(int u, double a){
    vertices[u] = a;
}

double Graph::get_edge_value(int u, int v){

    auto it = find_if( edges[u].begin(), edges[u].end(), 
        [&v](const edge& element){ return (element.first == v);} );
    double output = (it != edges[u].end()) ? it->second : -1.0;
    
    return output;
}

void Graph::set_edge_value(int u, int v, double dist) {

    auto it = find_if( edges[u].begin(), edges[u].end(), 
        [&v](const edge& element){ return (element.first == v);} );
    double output = (it != edges[u].end()) ? (it->second = dist) : 0;
    
}

// int main(void){
//     Graph test(50, 0.1);
//     test.print(1);
//     return 0;
// }






