#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include "graph.h"
#include "queue.h"
using namespace std;

typedef pair<int, double> edge;

class MST {
public:
    MST(Graph g);
    vector<int> vertices();
    int find_mst(); //return the path cost associated with the MST
private:
    Graph g;
    vector<int> paths;
};

MST::MST(Graph g){
    this->g = g;
}

vector<int> MST::vertices(){
    vector<int> vertices;

    for(int i = 0; i < g.V(); i++) {
        vertices.push_back(i);
    }
    return vertices;
}

int MST::find_mst() {
    PriorityQueue pq;
    edge top;
    int node;
    int n_nodes = g.V();
    // srand(time(0))
    int u = rand()%(n_nodes) + 0;
    int total_cost = 0;
    // cout << n_nodes;
    int i = 0;

	pq.insert(make_pair(u, 0));
    cout << "Finding MST" << endl;
    cout << "Starting at Node " << u << endl;

    while (!pq.empty()) {
    // while (i < 20) {
        top = pq.top();
        node = top.first;
        total_cost += top.second;
        pq.minPriority();
        cout << "-> Node " << node << ", Total Distance = " << total_cost << endl;
        paths.push_back(node);
        vector<int> n = g.neighbors(node);
        
        for(int dest: n) {
            
            bool contain_in_paths = false;
            double y = g.get_edge_value(node, dest);
            cout << ", Checking Node " << dest << ", Distance = " << y;

            for (int vertice: paths) {
                if (vertice == dest) 
                    contain_in_paths = true;
            }

            cout << ", Contain In Path = " << contain_in_paths;
            cout << ", In Queue = " << pq.contains(dest);

            if (!contain_in_paths) {
                
                if (!pq.contains(dest)) {
                    pq.insert(make_pair(dest, y));
                }
                else {
                    if (y < g.get_node_value(dest)) {
                        cout << ", Updated Value = " << g.get_node_value(dest) << " -> " << y;
                        pq.chgPriority(dest, y);
                    }
                }
                g.set_node_value(dest, y);
            }
            cout << endl;
        }
        
        cout << ", Queue Size:" << pq.size() << " ";
        pq.print();
        cout << "Paths {";
        for (auto e: paths){
            cout << e << " ";
        }
        cout << "}";
        cout << endl;
        i++;
        // break;
    }
    if (paths.size() != n_nodes) {
        cout << "No MST found, graph is not fully connected";
        return 0;
    }
    else {
        cout << "MST Total Cost = " << total_cost;
        return total_cost;
    }
}


int main(void){

    Graph test("sample_data.txt");
    MST JarnikPrim(test);
    JarnikPrim.find_mst();
    
    return 0;
}





