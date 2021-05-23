#include <iostream>
#include <cstdlib>
#include <cfloat>
#include <ctime>
#include <vector>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;

int main(void){
    ifstream file("sample_data.txt");
    istream_iterator<int> start(file), end;

    int size = *start;
    vector<pair<int, int> > storage[size];
    int temp_container[2];
    
    int i = 0;
    for (auto it=++start; it!=end; ++it) {
        if (i % 3 == 0) 
            temp_container[0] = *it;
        else if (i % 3 == 1) 
            temp_container[1] = *it;
        else
            storage[temp_container[0]].push_back(make_pair(temp_container[1], *it));
        i++;
    }
        
    for(auto node: storage) {
        cout << "Node " ;
        for (auto edge: node) {
            cout << edge.first << " -> "<< edge.second << endl;
        }
    }
}
