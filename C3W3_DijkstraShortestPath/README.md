<h1> Assignment: Dijkstra Shortest Path Algorithm </h1>

<h3> 1. Approach </h3>
<p>To create the algorithm, I followed the suggested approach in the assignment brief. Three different classes are constructed: Graph, PriorityQueue and ShortestPath. Graph and PriorityQueue classes can be found in the header files graph.h and queue.h. The ShortestPath class can be found on the shortest.cpp, which #include graph.h and queue.h.

STLs are used to implement these classes to carry out basic operations. For example, using vector and its operations for storing and retriving information. However, STLs that provide complex functionalities to generate graph, implement priority queue and find shortest path out-of-the-box are avoided. For example, there is an existing STL for priority queue which was not used for this project. Having to implement these functionalities on my own ensures that I understand their purpose and behaviour.</p>
<br>

<h3> 2. Classes </h3>


<p> <i>Graph</i>. To implement the Graph class, I referred to the following source:

> Geeks for Geeks (2020, Sep 8). *Graph and Its Representations*. https://www.geeksforgeeks.org/graph-and-its-representations/<br>

The graph class helps to generate random graph based on the desired number of nodes and graph density. It also provides methods for basic graph operations such as inserting new nodes, getting the total number of edges in the graph and getting the edge value between 2 nodes. For this class, I use vector for pairs to track the edges and their respective value. 
</p> <br>
 
<p> <i>PriorityQueue</i>. To implement the PriorityQueue class, I referred to the following source:

> Geeks for Geeks (2021, March 8). *Binary Heap*. https://www.geeksforgeeks.org/binary-heap/<br>

The priority queue class stores nodes and their corresponding value. It is based on min. heap implementation and therefore, the top element is one with the least node value. This class supports basic operations such as insertion and deletion. During insert and delete, the class will re-organize itself to maintain the min. heap structure.
</p> <br>
  
<p> <i>ShortestPath</i>. This class utilizes both the graph and priority queue classes to implement Dijkstra's shortest path algorithm. In this class, I also implemented a container to store shortest path results, allowing the computation of average shortest path after running the shortest path algorithm from the node in focus to every other nodes.
</p> <br>


<h3> 3. Lessons </h3>
<p> <i>Importance of Data Structure</i>. Coming from a Python background, C++ is much less forgiving and more demanding in ensuring that the data type are declared correctly. One of the issue I faced when starting the assignment is deciding how the private data members should be declared. For instance, for the graph class, my approach requires me to initialize a vector with a given size. However, initiating this directly with a dynamic size is not allowed. After a lot reading and research, the best solution to this turns out to initiate a pointer variable to a vector and then initialize the vector with a given size using `<addr>` in the constructor method.
</p> <br>

<p> <i>Pointers and Memory Management.</i>. 
</p> <br>

<p> <i>Error Message Clarity.</i>. 
</p> <br>


