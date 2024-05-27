## Assignment 2 - Graphs (Classes and Namespaces)

In this assignment, we created a graph object and ran different algorithms on it
The graph was defined in its classic way - a group of vertices, to represent the group of edges, I mapped each cell to its weight, while for the rest I ignored edges with a weight of 0.

The file `Graph.cpp` contains an implementation of a graph and various graph actions using operators.

The file `Algorithms.cpp` contains implementations for algorithms on graphs. Including:

- `isConnected(g)` - The algorithm accepts a graph and returns 1 if the graph is connected (otherwise returns 0). To realize this algorithm, I chose to use the technique of lateral search while running on all the vertices, and checking whether in a certain run, I reached all the vertices from a certain vertex.
- `shortestPath(g,start,end)` - The algorithm receives a graph, a start vertex, and an end vertex and returns the easiest path (in case the graph is not weighted - the shortest) between the two vertices. If there is no such route, the algorithm will return -1. To implement this algorithm, since the weight of the edges can be negative, I chose to use the Balman Ford algorithm, which will return me the shortest path even if there are negative weights in the graph.
- `isContainsCycle(g)` - The algorithm receives a graph and prints some cycles. If there is no circle in the graph, the algorithm will return 0. In implementing this algorithm, I used lateral search, and thus I could go over the graph several times until I found the circle.
- `isBipartite(g)` - The algorithm accepts a graph and returns the partition of the graph into a bipartite graph. If the graph cannot be divided, the algorithm will return 0. In implementing this algorithm, I went through all the edges to check if it is possible to color each pair of vertices connected by an edge with two separate colors.
- `negativeCycle(g)` - the algorithm receives a graph and finds a negative cycle (that is, a cycle whose sum of the weights of the sides is negative). If no such circle exists, the algorithm will print that there is no negative circle.

The `Demo.cpp` file contains examples of inputs and outputs.
The `Test.cpp` file contains various tests for the functions performed in the program, including tests for various end cases such as an empty graph and a graph with a negative circle.

## Usage

```cpp
#include "Algorithms.hpp"
#include "Graph.hpp"

ariel::Graph g;
ariel::Graph g2;

//You should load both graphs before usage;

std::string s = ariel::Algorithms::shortestPath(graph, 0, 2);
std::string bipar = Algorithms::isBipartite(g);
bool connected = ariel::Algorithms::isConnected(graph);
bool contains = Algorithms::isContainsCycle(g);

ariel::Graph g3 = g1 + g2;
g1 *= -2;
cout << g3;   
```

  
