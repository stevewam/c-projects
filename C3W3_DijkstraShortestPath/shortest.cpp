#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <exception>
#include <queue>
using namespace std;

typedef pair<double, int> edge;



class ShortestPath {
public:
    vertices(List): list of vertices in G(V,E).
    path(u, w): find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
    path_size(u, w): return the path cost associated with the shortest path.
private:
    priority_queue <edge, vector<edge>, greater_second> pq;
    vector <int> contents;
};




