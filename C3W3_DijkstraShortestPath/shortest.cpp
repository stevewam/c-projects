#include <iostream>
#include <vector>
#include <list>
#include "graph.h"
#include "queue.h"
using namespace std;

typedef pair<int, double> edge;

class ShortestPath {
public:
    ShortestPath(Graph g);
    vector<int> vertices();
    vector<int> path(int u, int w); // find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
    double path_size(int u, int w); //return the path cost associated with the shortest path.
private:
    Graph g;
    vector<int>* paths;
    vector<pair<int, double> >* shortest_paths;
};

ShortestPath::ShortestPath(Graph g){
    this->g = g;
    paths = new vector<int> [g.V()];
    shortest_paths = new vector<pair<int, double> > [g.V()];;
}

vector<int> ShortestPath::vertices(){
    vector<int> vertices;

    for(int i = 0; i < g.V(); i++) {
        vertices.push_back(i);
    }
    return vertices;
}

vector<int> ShortestPath::path(int u, int w) {
    PriorityQueue pq;
    edge top;
    int node;
	pq.insert(make_pair(u, 0));
    g.set_node_value(u, 0);
    paths[u].push_back(u);
    // cout << endl << "Finding shortest path from Node " << u << " to " << w << endl << endl;
    cout << u << " -> " << w;

    while (!pq.empty()) {
        top = pq.top();
        node = top.first;
        if (node == w) {
            // cout << "Shortest Path: ";
            for (auto it=paths[w].begin(); it!=paths[w].end(); it++){
                // cout << " -> " << *it;
            }
            // cout << endl;

            double total_dist = g.get_node_value(w);
            // cout << "Total Distance: " << total_dist << endl;
            cout << " : " << total_dist << endl;
            shortest_paths[u].push_back(make_pair(w, total_dist));
            return paths[w];
        }
        // cout << "- Evaluating Node " << node << endl;
        vector<int> n = g.neighbors(node);
        for(int i = 0; i < n.size(); i++) {
            // cout << "-- Travelling to Node " << n[i] ;
            double y = g.get_node_value(node) + g.get_edge_value(node, n[i]);
            
            // cout << ": Distance = " << y << " -> ";
            if (y <= g.get_node_value(n[i])){
                if (pq.contains(n[i])){
                    pq.chgPriority(n[i], y);
                    // cout << "Node already in Queue, Node value updated to " << y;
                }
                else {
                    g.set_node_value(n[i], y);
                    pq.insert(make_pair(n[i], y));
                    // cout << "Node value updated to " << y;
                }
                paths[n[i]].clear();
                // cout << " -> Path ";
                for (auto it=paths[node].begin(); it!=paths[node].end(); it++){
                    paths[n[i]].push_back(*it);
                    // cout << ":" << *it;
                }
                paths[n[i]].push_back(n[i]); 
                // cout << ":" << n[i];
            }
            // else
            //     cout << "Node value not updated";
            // cout << endl;
        }
        pq.minPriority();
        // cout << endl;
    }
    // cout << "No shortest path available.";
    shortest_paths[u].push_back(make_pair(w, DBL_MAX));
    cout << " : -" << endl;
    return paths[w];
}

double ShortestPath::path_size(int u, int w){
    auto it = find_if(shortest_paths[u].begin(), shortest_paths[u].end(), 
        [&w](const edge& element){ return (element.first == w);} );
    if (it != shortest_paths[u].end())
        return it->second;
    else
        path(u, w);
        return path_size(u, w);
}

int main(void){
    int size = 50;
    double density = 0.2;
    int start_node = 0;
    double sum;
    double avg;
    double dist;
    Graph test(size, density);

    // double* test.vertices();
    // test.print();
    // cout << test.E();
    ShortestPath dijkstra(test);
    vector<int> vertices = dijkstra.vertices();
    cout << "Finding average shortest path from Node " << start_node << endl;

    for(int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == start_node) continue;
        dist = dijkstra.path_size(start_node, vertices[i]);
        if (dist != DBL_MAX)
            sum += dijkstra.path_size(start_node, vertices[i]);
        else
            size--;
    }

    avg = sum/size;
    cout << "Average shortest path from Node " << start_node << " is " << avg;
    
    return 0;
}





