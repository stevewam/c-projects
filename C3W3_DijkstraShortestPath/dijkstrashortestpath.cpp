#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const double MIN_DIST = 1.0;
const double MAX_DIST = 10.0;

double prob() {
    return (rand() % 100)/100;
}

class Graph {
public:
    // Graph(): n(0), adj(0) {}
    Graph(int n, double density);
    int V();
    // void E(vector <pair<int, double> > adj[]);
    void adjacent(vector <pair<int, double> > adj[], int u, int v);
    // void neighbors(vector <pair<int, double> > adj[], int u);
    void add(int u, int v, double dist);
    // void remove(vector <pair<int, double> > adj[], int u, int v, double dist);
    // void get_node_value(vector <pair<int, double> > adj[], int u);
    // void set_node_value(vector <pair<int, double> > adj[], int u);
    // void get_edge_value(vector <pair<int, double> > adj[], int u, int v);
    // void set_edge_value(vector <pair<int, double> > adj[], int u, int v, double dist);
    void print();
private:
    int n;
    vector <pair<int, double> >* adj;
};

Graph::Graph(int n, double density){
    srand(time(0));
    this->n = n;
    adj = new vector <pair<int, double> > [n];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j) 
                continue;
            else
                if (prob() < density) {
                    double dist = MIN_DIST + (rand() % int(MAX_DIST));
                    Graph::add(i, j, dist);
                }           
        }
    }
};

int Graph::V(){
    return n;
}

void Graph::add( int u, int v, double dist){
    adj[u].push_back(make_pair(v, dist));
    adj[v].push_back(make_pair(u, dist));
};

void Graph::print(){
    int v, w;
    for (int u = 0; u < n; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it=adj[u].begin(); it!=adj[u].end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight ="
                 << w << "\n";
        }
        cout << "\n";
    }
}

int main(void) {
    Graph test(50, 0.4);
    test.print();
    cout << "Done" << static_cast<int>(test.V());
    
    return 0;
}






