#include "Graph.hpp"

void ariel::Graph::loadGraph(std::vector<std::vector<int>> matrix)
{
    this->_vertexs.clear();
    this->_edges.clear();

    for (std::size_t i = 0; i < matrix.size(); i++)
    {
        if (matrix[i].size() != matrix.size())
        {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }

    for (std::size_t i = 0; i < matrix.size(); i++)
    {
        this->_vertexs.insert(i);

        for (std::size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] != 0)
            {
                std::pair<std::size_t, std::size_t> key = std::make_pair(i, j);
                this->_edges[key] = matrix[i][j];
            }
        }
    }
}

// GRAPH OPERATORS PART 1 - MATHEMATIC OPERATORS:

ariel::Graph ariel::Graph::operator+(const Graph &other) const
{
    if (this->_vertexs.size() != other._vertexs.size())
    {
        throw std::invalid_argument("Both graphs have to be the same size");
    }

    std::vector<std::vector<int>> newGraph(this->_vertexs.size(), std::vector<int>(this->_vertexs.size(), 0));

    for (const auto &edge : this->_edges)
    {
        newGraph[edge.first.first][edge.first.second] += edge.second;
    }

    for (const auto &edge : other._edges)
    {
        newGraph[edge.first.first][edge.first.second] += edge.second;
    }

    Graph g;
    g.loadGraph(newGraph);
    return g;
}

ariel::Graph &ariel::Graph::operator+=(const Graph &other)
{
    if (this->_vertexs.size() != other._vertexs.size())
    {
        throw std::invalid_argument("Both graphs have to be the same size");
    }

    for (const auto &edge : other._edges)
    {
        if ((this->_edges.find(edge.first) != this->_edges.end()))
        {
            this->_edges.at(edge.first) += other._edges.at(edge.first);
        }
        else
        {
            this->_edges.insert(edge);
        }
    }

    return *this;
}

ariel::Graph &ariel::Graph::operator+()
{
    for (auto &edge : this->_edges)
    {
        edge.second *= 1;
    }

    return *this;
}

ariel::Graph &ariel::Graph::operator++()
{
    for (auto &edge : this->_edges)
    {
        ++edge.second;
    }

    return *this;
}

ariel::Graph ariel::Graph::operator++(int)
{
    Graph temp = *this;

    for (auto &edge : this->_edges)
    {
        ++edge.second;
    }

    return temp;
}

ariel::Graph ariel::Graph::operator-(const Graph &other) const
{
    if (this->_vertexs.size() != other._vertexs.size())
    {
        throw std::invalid_argument("Both graphs have to be the same size");
    }

    std::vector<std::vector<int>> newGraph(this->_vertexs.size(), std::vector<int>(this->_vertexs.size(), 0));

    for (const auto &edge : this->_edges)
    {
        newGraph[edge.first.first][edge.first.second] -= edge.second;
    }

    for (const auto &edge : other._edges)
    {
        newGraph[edge.first.first][edge.first.second] -= edge.second;
    }

    Graph g;
    g.loadGraph(newGraph);
    return g;
}

ariel::Graph &ariel::Graph::operator-=(const Graph &other)
{
    if (this->_vertexs.size() != other._vertexs.size())
    {
        throw std::invalid_argument("Both graphs have to be the same size");
    }

    for (const auto &edge : other._edges)
    {
        if ((this->_edges.find(edge.first) != this->_edges.end()))
        {
            this->_edges.at(edge.first) -= other._edges.at(edge.first);
        }
        else
        {
            this->_edges.insert(edge);
        }
    }

    return *this;
}

ariel::Graph &ariel::Graph::operator-()
{
    for (auto &edge : this->_edges)
    {
        edge.second *= -1;
    }

    return *this;
}

ariel::Graph &ariel::Graph::operator--()
{
    for (auto &edge : this->_edges)
    {
        --edge.second;
    }

    return *this;
}

ariel::Graph ariel::Graph::operator--(int)
{
    Graph temp = *this;

    for (auto &edge : this->_edges)
    {
        --edge.second;
    }

    return temp;
}

bool ariel::Graph::operator==(const Graph &other) const
{
    if (this->_vertexs.size() != other._vertexs.size())
    {
        return false;
    }

    for (const auto &edge : other._edges)
    {
        if ((this->_edges.find(edge.first) == this->_edges.end()))
            return false;
        else if (this->_edges.at(edge.first) != edge.second)
            return false;
    }
    return true;
}

ariel::Graph& ariel::Graph::operator*(int scalar)
{
        for (auto &edge : this->_edges)
    {
        edge.second *= scalar;
    }

    return *this;
}