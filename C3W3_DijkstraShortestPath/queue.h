#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdexcept>
// #include "graph.h"
using namespace std;

typedef pair<int, double> edge;

class PriorityQueue
{  
public:
    PriorityQueue():Q(){}
    unsigned int size();
    bool empty();
    void insert(edge e);
    void minPriority();
    edge top();
    bool contains(int e);
    void chgPriority(int e, double priority);
    ~PriorityQueue();
private:
    vector<edge> Q;
    int parent_index(int i) {return (i - 1) / 2;}
    int left_child_index(int i) {return (2*i + 1);}
    int right_child_index(int i) {return (2*i + 2);}
    void heapify_down(int i);
    void heapify_up(int i);
};

PriorityQueue::~PriorityQueue(){
    vector<edge>().swap(Q);
}

void PriorityQueue::heapify_down(int i){// direct children of i violates heap property
    
    int left = left_child_index(i);
    int right = right_child_index(i);
    int smallest = i;

    // compare `A[i]` with its left and right child
    // and find the smallest value
    if (left < Q.size() && Q[left].second < Q[i].second) {
        smallest = left;
    }

    if (right < Q.size() && Q[right].second < Q[smallest].second) {
        smallest = right;
    }

    if (smallest != i){
        swap(Q[i], Q[smallest]);
        heapify_down(smallest);
    }
}
 
void PriorityQueue::heapify_up(int i){
    int parent = parent_index(i);
    if (i && Q[parent].second > Q[i].second){
        swap(Q[i], Q[parent]);
        heapify_up(parent);
    }
}

// return size of the heap
unsigned int PriorityQueue::size() {
    return Q.size();
}

// Function to check if the heap is empty or not
bool PriorityQueue::empty() {
    return size() == 0;
}

void PriorityQueue::insert(edge e)
{
    Q.push_back(e);
    int index = size() - 1;
    heapify_up(index);
}

void PriorityQueue::minPriority() {
    // if the heap has no elements, throw an exception
    if (size() == 0) {
        throw out_of_range("Vector<X>::at() : "
                "index is out of range(Heap underflow)");
    }

    // replace the root of the heap with the last element
    // of the vector
    Q[0] = Q.back();
    Q.pop_back();

    // call heapify-down on the root node
    heapify_down(0);

}

// Function to return an element with the lowest priority (present at the root)
edge PriorityQueue::top(){
    // if the heap has no elements, throw an exception
    if (size() == 0)
    {
        throw out_of_range("Vector<X>::at() : "
                "index is out of range(Heap underflow)");
    }

    // otherwise, return the top (first) element
    return Q.at(0);        // or return A[0];
}

bool PriorityQueue::contains(int e){
    auto it = find_if(Q.begin(), Q.end(),
            [&e](const edge& element){ return (element.first == e);});
    if (it != Q.end())
        return 1;
    else
        return 0;
}

void PriorityQueue::chgPriority(int e, double priority){
    auto it = remove_if(Q.begin(), Q.end(), 
            [&e](const edge& element){ return (element.first == e);});
    insert(make_pair(e, priority));
}

// int main(void){
//     Graph test(50, 0.1);

//     PriorityQueue pq;
//     pq.insert(make_pair(0, 100));
//     pq.insert(make_pair(1, 7));
//     pq.insert(make_pair(2, 54));
//     pq.insert(make_pair(3, 13));
//     pq.insert(make_pair(4, 65));
    
//     auto result = pq.top();
//     cout << result.first << endl;
    
//     pq.minPriority();
//     auto result1 = pq.top();
//     cout << result1.first << endl;
    
//     pq.chgPriority(0, 0);
//     auto result2 = pq.top();
//     cout << result2.first << endl;

//     return 0;
// }
