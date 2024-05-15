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

        Graph operator*(const Graph &);
        Graph& operator*(int);

        bool operator==(const Graph &) const;
        bool operator!=(const Graph & other)  const {return !(*this == other);};
        bool operator>(const Graph &)  const;
        bool operator<(const Graph &other) const {return other == *this;};
        bool operator>=(const Graph & other) const {return (*this > other) || (*this == other);};
        bool operator<=(const Graph & other) const {return (*this < other) || (*this == other);};;

        friend std::ostream& operator<<(std::ostream&, const Graph&);
    };
}