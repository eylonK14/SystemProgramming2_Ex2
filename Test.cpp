#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

#define FIVE 5 

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph graph;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(graph) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    graph.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(graph) == false);
    vector<vector<int>> graph3 = {{0}};
    graph.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(graph) == true);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph graph;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph.loadGraph(graph1);
    CHECK(ariel::Algorithms::shortestPath(graph, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    graph.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(graph, 0, 4) == "-1");
    CHECK(ariel::Algorithms::shortestPath(graph, 0, 0) == "0");

    vector<vector<int>> graphFIVE = {
        {0, 1, -4},
        {-2, 0, 3},
        {4, -3, 0}};
    graph.loadGraph(graphFIVE);
    CHECK(ariel::Algorithms::shortestPath(graph, 0, 2) == "-1");

    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, FIVE},
        {0, 0, 0, FIVE, 0}};
    graph.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(graph, 0, 4) == "0->1->2->3->4");

    vector<vector<int>> graph3 = {{0}};
    graph.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(graph, 0, 0) == "0");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph graph;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(graph) == "0");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    graph.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(graph) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graphFIVE = {
        {0, 1, -4},
        {-2, 0, 3},
        {4, -3, 0}};
    graph.loadGraph(graphFIVE);
    CHECK(ariel::Algorithms::isContainsCycle(graph) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph3 = {{0}};
    graph.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(graph) == "0");
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph graph;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph.loadGraph(graph1);
    CHECK(ariel::Algorithms::isBipartite(graph) == "The graph is bipartite: A={0, 2}, B={1}.");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    graph.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(graph) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, FIVE},
        {0, 0, 0, FIVE, 0}};
    graph.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(graph) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}.");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph graph;
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, FIVE}};
    CHECK_THROWS(graph.loadGraph(graph1));
}

TEST_CASE("Test negativeCycle")
{
    ariel::Graph graph;
    vector<vector<int>> graphFIVE = {
        {0, 1, -4},
        {-2, 0, 3},
        {4, -3, 0}};
    graph.loadGraph(graphFIVE);
    CHECK(ariel::Algorithms::negativeCycle(graph) == "The negative cycle is: 0->2->1->0");

    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph.loadGraph(graph1);
    CHECK(ariel::Algorithms::negativeCycle(graph) == "There are no negative cycles in the graph.");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    graph.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(graph) == "There are no negative cycles in the graph.");
}

TEST_CASE("Test graph addition")
{
    ariel::Graph graph1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph1.loadGraph(graph);
    ariel::Graph graph2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    graph2.loadGraph(weightedGraph);
    ariel::Graph graph3 = graph1 + graph2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    ariel::Graph newG;
    newG.loadGraph(expectedGraph);
    CHECK(graph3 == newG);

    graph1++;
    ++graph1;
    vector<vector<int>> graph22 = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    ariel::Graph gFIVE;
    gFIVE.loadGraph(graph22);
    CHECK(gFIVE == graph1);
    CHECK(+gFIVE == gFIVE);
}

TEST_CASE("Test graph subtraction")
{
    ariel::Graph graph1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph1.loadGraph(graph);
    ariel::Graph graph2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    graph2.loadGraph(weightedGraph);
    ariel::Graph graph3 = graph1 - graph2;
    vector<vector<int>> expectedGraph = {
        {0, 0, -1},
        {0, 0, -1},
        {-1, -1, 0}};
    ariel::Graph newG;
    newG.loadGraph(expectedGraph);
    CHECK(graph3 == newG);

    graph1--;
    --graph1;
    vector<vector<int>> graph22 = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    ariel::Graph gFIVE;
    gFIVE.loadGraph(graph22);
    CHECK(gFIVE == graph1);
    graph1.loadGraph(graph);
    CHECK(gFIVE == -graph1);
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph graph1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph1.loadGraph(graph);
    ariel::Graph graph2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    graph2.loadGraph(weightedGraph);
    ariel::Graph graph4 = graph1 * graph2;
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    ariel::Graph newG;
    newG.loadGraph(expectedGraph);
    CHECK(graph4 == newG);

    graph1 *= FIVE;
    vector<vector<int>> graph22 = {
        {0, FIVE, 0},
        {FIVE, 0, FIVE},
        {0, FIVE, 0}};
    ariel::Graph gFIVE;
    gFIVE.loadGraph(graph22);
    CHECK(gFIVE == graph1);

    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}};

    graph1.loadGraph(graph3);
    graph1 *= 0;

    vector<vector<int>> graph44 = {
        {0, 0},
        {0, 0}};
    graph2.loadGraph(graph44);
    CHECK(graph1 == graph2);
}

TEST_CASE("Test graph division")
{
    ariel::Graph graph2;
    vector<vector<int>> weightedGraph = {
        {0, 2, 2},
        {2, 0, 2},
        {2, 2, 0}};
    graph2.loadGraph(weightedGraph);
    graph2 /= 2;
    vector<vector<int>> expectedGraph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    ariel::Graph newG;
    newG.loadGraph(expectedGraph);
    CHECK(graph2 == newG);
}

TEST_CASE("Boolean Operations")
{
    ariel::Graph graph1;
    ariel::Graph graph2;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}};

    graph1.loadGraph(graph3);
    graph1 *= 0;

    vector<vector<int>> graph4 = {
        {0, 0},
        {0, 0}};
    graph2.loadGraph(graph3);
    CHECK(graph1 != graph2);

    graph1.loadGraph(graph);

    CHECK(graph1 > graph2);
    CHECK(graph1 >= graph2);

    graph1.loadGraph(graph3);
    graph2.loadGraph(graph);

    CHECK(graph1 < graph2);
    CHECK(graph1 <= graph2);
}

TEST_CASE("Invalid operations")
{
    ariel::Graph graph1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    graph1.loadGraph(graph);
    ariel::Graph graph2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(graph2.loadGraph(weightedGraph));
    ariel::Graph gFIVE;
    vector<vector<int>> graph22 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    gFIVE.loadGraph(graph22);
    CHECK_THROWS(gFIVE * graph1);
    CHECK_THROWS(graph1 * graph2);

    // Addition of two graphs with different dimensions
    ariel::Graph graph6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    graph6.loadGraph(graph3);
    CHECK_THROWS(graph1 + graph6);

    CHECK_THROWS(graph1 /= 0);
}