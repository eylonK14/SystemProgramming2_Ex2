#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>

namespace ariel
{
    class Graph
    {
    private:
        std::set<std::size_t> _vertexs;
        std::map<std::pair<std::size_t, std::size_t>, int> _edges;

    public:
        void loadGraph(std::vector<std::vector<int>>);
        void printGraph() { std::cout << "Graph with " << this->_vertexs.size() << " vertices and " << this->_edges.size() << " edges." << std::endl; };

        std::set<std::size_t> getVertexs() { return this->_vertexs; }
        std::map<std::pair<std::size_t, std::size_t>, int> getEdges() { return this->_edges; }
        int getVertexsSize() { return this->_vertexs.size(); }

        Graph operator+(const Graph &other) const;
        Graph &operator+=(const Graph &other);
        Graph &operator+();
        Graph& operator++();
        Graph operator++(int);

        Graph operator-(const Graph &other) const;
        Graph &operator-=(const Graph &other);
        Graph &operator-();
        Graph& operator--();
        Graph operator--(int);
    };
}