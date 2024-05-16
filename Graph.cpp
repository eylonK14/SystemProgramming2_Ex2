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

std::string ariel::Graph::printGraph()
{
    std::string graph;

    std::vector<std::vector<int>> matrixGraph = this->getGraphAsMatrix();
    for (std::size_t v : this->_vertexs)
    {
        graph += "[";

        for (std::size_t secV : this->_vertexs)
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

    return graph;
}

std::vector<std::vector<int>> ariel::Graph::getGraphAsMatrix()
{
    std::vector<std::vector<int>> matrix = {{}};

    for (std::size_t i = 0; i < this->_vertexs.size(); i++)
        for (std::size_t j = 0; j < this->_vertexs.size(); j++)
            matrix[i][j] = 0;

    for (auto &edge : this->_edges)
    {
        matrix[edge.first.first][edge.first.second] = edge.second;
    }

    return matrix;
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

ariel::Graph &ariel::Graph::operator*=(int scalar)
{
    for (auto &edge : this->_edges)
    {
        edge.second *= scalar;
    }

    return *this;
}

ariel::Graph &ariel::Graph::operator/=(int scalar)
{
    for (auto &edge : this->_edges)
    {
        edge.second /= scalar;
    }

    return *this;
}

ariel::Graph ariel::Graph::operator*(Graph &other)
{
    if (this->_vertexs.size() != other._vertexs.size())
    {
        throw std::invalid_argument("Both graphs must be the same size.");
    }

    std::vector<std::vector<int>> firstGraph = this->getGraphAsMatrix();
    std::vector<std::vector<int>> secondGraph = other.getGraphAsMatrix();
    std::vector<std::vector<int>> newGraph = {{}};

    for (std::size_t i = 0; i < this->_vertexs.size(); i++)
    {
        for (std::size_t j = 0; j < this->_vertexs.size(); j++)
        {
            newGraph[i][j] = 0;

            for (std::size_t k = 0; k < this->_vertexs.size(); k++)
            {
                newGraph[i][j] += firstGraph[i][k] * secondGraph[k][j];
            }
        }
    }

    Graph g;
    g.loadGraph(newGraph);
    return g;
}

std::ostream &operator<<(std::ostream &stream, const ariel::Graph &other)
{
    std::string graph;

    std::vector<std::vector<int>> matrixGraph = other.getGraphAsMatrix(); //need to fix
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
    return (stream << graph);
}