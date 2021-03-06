#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <exception>
#include <queue>
#include "graph.h"
using namespace std;

typedef pair<double, int> edge;

struct greater_second {
    constexpr bool operator()(
        edge const& a,
        edge const& b)
        const noexcept
    {
        return a.second > b.second;
    }
};

class PriorityQueue {
public:
    PriorityQueue():pq(), contents(){};
    void chgPriority(edge, double priority); //changes the priority (node value) of queue element.
    void minPriority(); 
    bool contains(edge e);
    void insert(edge e);
    edge top();
    int size();
private:
    priority_queue <edge, vector<edge>, greater_second> pq;
    vector <int> contents;
};

// void PriorityQueue::chgPriority(int priority, edge e){
    
// }

void PriorityQueue::minPriority(){
    return pq.pop();
}

bool PriorityQueue::contains(edge e){
    auto it = find (contents.begin(), contents.end(), e.first);
    if (it != contents.end())
        return 1;
    else
        return 0;
}

void PriorityQueue::insert(edge e){
    pq.push(e);
    contents.push_back(e.first);
}

edge PriorityQueue::top(){
    return pq.top();
}

int PriorityQueue::size(){
    return pq.size();
}

int main(void){
    Graph test(50, 0.1);

    PriorityQueue pq;
    pq.insert(make_pair(0, 100));
    pq.insert(make_pair(1, 7));
    auto result = pq.top();
    cout << result.first;
    
    return 0;
}
