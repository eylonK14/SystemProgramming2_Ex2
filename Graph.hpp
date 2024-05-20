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
        std::string printGraph();
        std::vector<std::vector<int>> getGraphAsMatrix() const;

        std::set<std::size_t> getVertexs() const { return this->_vertexs; }
        std::map<std::pair<std::size_t, std::size_t>, int> getEdges() const { return this->_edges; }
        int getVertexsSize() const { return this->_vertexs.size(); }

        Graph operator+(const Graph &) const;
        Graph &operator+=(const Graph &);
        Graph &operator+();
        Graph &operator++();
        Graph operator++(int);

        Graph operator-(const Graph &) const;
        Graph &operator-=(const Graph &);
        Graph &operator-();
        Graph &operator--();
        Graph operator--(int);

        Graph operator*(Graph &);
        Graph &operator*=(int);
        Graph &operator/=(int);

        bool operator==(const Graph &) const;
        bool operator!=(const Graph &other) const { return !(*this == other); };
        bool operator>(const Graph &) const;
        bool operator<(const Graph &other) const { return (other > *this); };
        bool operator>=(const Graph &other) const { return (*this > other) || (*this == other); };
        bool operator<=(const Graph &other) const { return (*this < other) || (*this == other); };

        friend std::ostream &operator<<(std::ostream &stream, const ariel::Graph &other)
        {
            std::string graph;

            std::vector<std::vector<int>> matrixGraph = other.getGraphAsMatrix(); // need to fix
            for (std::size_t v : other.getVertexs())
            {
                graph += "[";

                for (std::size_t secV : other.getVertexs())
                {
                    graph += std::to_string(matrixGraph[v][secV]);
                    graph += ", ";
                }
                graph.pop_back();
                graph.pop_back();
                graph += "], ";
            }

            graph.pop_back();
            graph.pop_back();
            return (stream << graph << std::endl);
        }
    };
}