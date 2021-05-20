#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <exception>
using namespace std;

#include "graph.h"

// class PriorityQueue {
// public:
//     chgPrioirity(PQ, priority): changes the priority (node value) of queue element.
//     minPrioirty(PQ): removes the top element of the queue.
//     contains(PQ, queue_element): does the queue contain queue_element.
//     Insert(PQ, queue_element): insert queue_element into queue
//     top(PQ):returns the top element of the queue.
//     size(PQ): return the number of queue_elements.
// private:

// }


int main(void) {
    Graph test(50, 0.1);
    test.print(1);
    cout << test.E();
}
