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