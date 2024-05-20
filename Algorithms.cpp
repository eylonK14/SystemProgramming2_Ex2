#include "Algorithms.hpp"

bool ariel::Algorithms::isConnected(ariel::Graph graph)
{
    std::vector<std::size_t> visited = {};

    for (std::size_t vertex : graph.getVertexs())
    {
        bfs(graph, vertex, visited);
        if (graph.getVertexsSize() == visited.size())
        {
            return true;
        }

        visited.clear();
    }

    return false;
}

std::string ariel::Algorithms::isContainsCycle(const ariel::Graph &graph)
{
    std::vector<bool> ack;
    if (findCycle(graph, ack))
    {
        bool foundFirst = false;
        std::string firstNode;
        std::string path = "The cycle is: ";

        for (std::size_t i = 0; i < ack.size(); i++)
        {
            if (ack[i])
            {
                if (!foundFirst)
                {
                    foundFirst = true;
                    firstNode = std::to_string(i);
                    path += firstNode;
                    path += "->";
                }
                else
                {
                    path += std::to_string(i);
                    path += "->";
                }
            }
        }

        path += firstNode;
        return path;
    }

    return "0";
}

std::string ariel::Algorithms::isBipartite(const ariel::Graph& graph)
{
    std::vector<int> color;
    if (isBipartite(graph, 0, color))
    {
        std::string firstGroup = "{";
        std::string secondGroup = "{";
        for (std::size_t i = 0; i < color.size(); i++)
        {
            if (color[i] == 1)
            {
                firstGroup += std::to_string(i);
                firstGroup += ", ";
            }
            else if (color[i] == -1)
            {
                secondGroup += std::to_string(i);
                secondGroup += ", ";
            }
        }

        firstGroup.pop_back();
        firstGroup.pop_back();

        secondGroup.pop_back();
        secondGroup.pop_back();

        firstGroup.push_back('}');
        secondGroup.push_back('}');

        return "The graph is bipartite: A=" + firstGroup + ", B=" + secondGroup + ".";
    }
    return "0";
}

std::string ariel::Algorithms::shortestPath(const ariel::Graph &graph, int start, int end)
{
    std::size_t newStart = static_cast<std::size_t>(start);
    std::size_t newEnd = static_cast<std::size_t>(end);

    if (graph.getVertexs().find(newStart) == graph.getVertexs().end() || graph.getVertexs().find(newEnd) == graph.getVertexs().end())
    {
        return "-1";
    }

    std::vector<std::size_t> parentList;
    std::vector<int> distanceList;

    std::string Bellmanford = BellmanFord(graph, newStart, distanceList, parentList);

    if (Bellmanford == "There are no negative cycles in the graph.")
    {
        std::string path = std::to_string(newEnd);
        for (std::size_t i = parentList[newEnd]; i >= start && i != __INT_MAX__;)
        {
            path += ">-";
            path += std::to_string(i);
            i = parentList[i];
        }

        std::reverse(path.begin(), path.end());
        if (path[0] == (char)(start + '0'))
        {
            return path;
        }
        return "-1";
    }
    return "-1";
}

std::string ariel::Algorithms::negativeCycle(const ariel::Graph &graph)
{
    std::vector<std::size_t> parentList;
    std::vector<int> distanceList;
    std::string bellmanFord = BellmanFord(graph, 0, distanceList, parentList);

    if (bellmanFord == "There are no negative cycles in the graph.")
    {
        return bellmanFord;
    }

    std::reverse(bellmanFord.begin(), bellmanFord.end());
    std::string cycle = "The negative cycle is: " + bellmanFord;
    return cycle;
}

bool ariel::Algorithms::findCycle(const ariel::Graph &graph, std::vector<bool> &ack)
{
    std::vector<bool> visited;
    std::set<std::pair<std::size_t, std::size_t>> usedEdges;

    for (long i = 0; i < graph.getVertexsSize(); i++)
    {
        visited.insert(visited.begin() + i, false);
        ack.insert(ack.begin() + i, false);
    }

    for (std::size_t i = 0; i < graph.getVertexsSize(); i++)
    {
        if (!visited[i] && cycleIteration(graph, i, usedEdges, visited, ack))
        {
            return true;
        }
    }

    return false;
}

bool ariel::Algorithms::cycleIteration(const ariel::Graph &graph, std::size_t vertex, std::set<std::pair<std::size_t, std::size_t>> &usedEdges, std::vector<bool> &visited, std::vector<bool> &ack)
{
    if (!visited[vertex])
    {
        visited[vertex] = true;
        ack[vertex] = true;
    }

    for (auto &edge : graph.getEdges())
    {
        if (edge.first.first == vertex && (usedEdges.find(edge.first) == usedEdges.end()) && usedEdges.find(std::make_pair(edge.first.second, edge.first.first)) == usedEdges.end())
        {
            usedEdges.insert(edge.first);
            usedEdges.insert(std::make_pair(edge.first.second, edge.first.first));

            if (!visited[edge.first.second] && cycleIteration(graph, edge.first.second, usedEdges, visited, ack))
            {
                return true;
            }
            if (ack[edge.first.second])
            {
                return true;
            }
        }
    }

    ack[vertex] = false;
    return false;
}

bool ariel::Algorithms::isBipartite(const ariel::Graph& graph, int start, std::vector<int> &color)
{
    std::size_t newStart = static_cast<std::size_t>(start);
    std::queue<std::size_t> queue;

    for (long i = 0; i < graph.getVertexs().size(); i++)
    {
        color.insert(color.begin() + i, 0);
    }

    color[newStart] = 1;
    queue.push(newStart);

    while (!queue.empty())
    {
        std::size_t ver = queue.front();
        queue.pop();

        for (const auto &edge : graph.getEdges())
        {
            if (edge.first.first == ver)
            {
                std::size_t secVer = edge.first.second;
                if (color[secVer] == 0)
                {
                    if (color[ver] == 1)
                    {
                                                color[secVer] = -1;
                    }
                    else
                    {
                        color[secVer] = 1;
                    }

                    queue.push(secVer);
                }
                else if (color[ver] == color[secVer])
                {
                    return false;
                }

            }
        }
    }

    return true;
}

void ariel::Algorithms::relax(std::pair<std::pair<std::size_t, std::size_t>, int> edge, std::vector<int> &distanceList, std::vector<std::size_t> &parentList)
{
    if (distanceList[edge.first.second] > distanceList[edge.first.first] + edge.second)
    {
        distanceList[edge.first.second] = distanceList[edge.first.first] + edge.second;
        parentList[edge.first.second] = edge.first.first;
    }
}

std::string ariel::Algorithms::BellmanFord(const ariel::Graph& graph , std::size_t start, std::vector<int> &distanceList, std::vector<std::size_t> &parentList)
{
    for (long i = 0; i < graph.getVertexs().size(); i++)
    {
        distanceList.insert(distanceList.begin() + i, __INT_MAX__);
        parentList.insert(parentList.begin() + i, __INT_MAX__);
    }

    distanceList[start] = 0;

    for (std::size_t i = 0; i < graph.getVertexsSize() - 1; i++)
    {
        for (const auto &edge : graph.getEdges())
        {
            relax(edge, distanceList, parentList);
        }
    }

    for (const auto &edge : graph.getEdges())
    {
        if (distanceList[edge.first.second] > distanceList[edge.first.first] + edge.second)
        {
            std::size_t father = edge.first.first;
            std::string path = std::to_string(father);
            std::size_t index = parentList[father];
            bool flag = true;

            while (flag)
            {
                path += ">-";
                path += std::to_string(index);
                index = parentList[index];
                flag = !(index == parentList[father]);
            }

            return path;
        }
    }

    return "There are no negative cycles in the graph.";
}

void ariel::Algorithms::bfs(ariel::Graph &graph, std::size_t start, std::vector<std::size_t> &visited)
{
    std::vector<int> color;
    std::vector<int> distance;
    for (long vertex = 0; vertex < graph.getVertexs().size(); vertex++)
    {
        color.insert(color.begin() + vertex, -1);
        distance.insert(distance.begin() + vertex, __INT_MAX__);
    }

    color[start] = 0;
    distance[start] = 0;
    visited.push_back(start);

    std::queue<std::size_t> queue;
    queue.push(start);

    while (!queue.empty())
    {
        std::size_t value = queue.front();
        queue.pop();

        for (const auto &edge : graph.getEdges())
        {
            std::size_t ver = edge.first.first;
            if (ver == start)
            {
                std::size_t secVer = edge.first.second;
                if (color[secVer] == -1)
                {
                    color[secVer] = 0;
                    visited.push_back(secVer);
                    distance[secVer] = distance[value] + 1;
                    queue.push(secVer);
                }
            }
        }

        color[value] = 1;
    }
}