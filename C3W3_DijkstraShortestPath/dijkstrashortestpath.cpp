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
    Graph(): adj(0), density(0) {}
    Graph(int n, double density);
    void V(vector <pair<int, double>> adj[]);
    void E(vector <pair<int, double>> adj[]);
    void adjacent(vector <pair<int, double>> adj[], int u, int v);
    void neighbors(vector <pair<int, double>> adj[], int u);
    void add(vector <pair<int, double>> adj[], int u, int v, double dist);
    void remove(vector <pair<int, double>> adj[], int u, int v, double dist);
    void get_node_value(vector <pair<int, double>> adj[], int u);
    void set_node_value(vector <pair<int, double>> adj[], int u);
    void get_edge_value(vector <pair<int, double>> adj[], int u, int v);
    void set_edge_value(vector <pair<int, double>> adj[], int u, int v, double dist);
    void print();
private:
    vector <pair<int, double>>* adj;
    double density;
};

Graph::Graph(int n, double density){
    srand(time(0));
    vector <pair<int, double>> adj[n];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; i++){
            if (i == j) 
                continue;
            else
                if (prob() < density) {
                    double dist = MIN_DIST + (rand() % int(MAX_DIST));
                    Graph::add(adj, i, j, dist);
                }           
        }
    }
};

void Graph::add(vector <pair<int, double>> adj[], int u, int v, double wt){
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
};

int main(void) {
    // Graph test(50, 0.4);
    cout << "Done";
    return 0;
}





// void printGraph(vector<pair<int,int> > adj[], int V)
// {
//     int v, w;
//     for (int u = 0; u < V; u++)
//     {
//         cout << "Node " << u << " makes an edge with \n";
//         for (auto it = adj[u].begin(); it!=adj[u].end(); it++)
//         {
//             v = it->first;
//             w = it->second;
//             cout << "\tNode " << v << " with edge weight ="
//                  << w << "\n";
//         }
//         cout << "\n";
//     }
// }
