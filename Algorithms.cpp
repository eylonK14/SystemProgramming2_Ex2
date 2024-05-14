#include "Algorithms.hpp"

bool ariel::Algorithms::isConnected(ariel::Graph g)
{
    std::vector<std::size_t> visited = {};

    for (std::size_t v : g.getVertexs())
    {
        bfs(g, v, visited);
        if(g.getVertexsSize() == visited.size())
            return true;

        visited.clear();
    }

    return false;
}

std::string ariel::Algorithms::isContainsCycle(ariel::Graph g)
{
    std::vector<bool> ack;
    if (findCycle(g, ack))
    {
        bool foundFirst = false;
        std::string firstNode = "";
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

std::string ariel::Algorithms::isBipartite(ariel::Graph g)
{
    std::vector<int> color;
    if (isBipartite(g, 0, color))
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

std::string ariel::Algorithms::shortestPath(ariel::Graph g, int start, int end)
{
    std::size_t s = static_cast<std::size_t>(start);
    std::size_t e = static_cast<std::size_t>(end);

    if (g.getVertexs().find(s) == g.getVertexs().end() || g.getVertexs().find(e) == g.getVertexs().end())
    {
        return "-1";
    }

    std::vector<std::size_t> parentList;
    std::vector<int> distanceList;

    std::string Bellmanford = BellmanFord(g, s, distanceList, parentList);

    if (Bellmanford.compare("There are no negative cycles in the graph.") == 0)
    {
        std::string path = std::to_string(e);
        for (std::size_t i = parentList[e]; i >= start && i != __INT_MAX__;)
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

std::string ariel::Algorithms::negativeCycle(ariel::Graph g)
{
    std::vector<std::size_t> parentList;
    std::vector<int> distanceList;
    std::string bellmanFord = BellmanFord(g, 0, distanceList, parentList);

    if (bellmanFord.compare("There are no negative cycles in the graph.") == 0)
    {
        return bellmanFord;
    }

    std::reverse(bellmanFord.begin(), bellmanFord.end());
    std::string cycle = "The negative cycle is: " + bellmanFord;
    return cycle;
}

bool ariel::Algorithms::findCycle(ariel::Graph g, std::vector<bool> &ack)
{
    std::vector<bool> visited;
    std::set<std::pair<std::size_t, std::size_t>> usedEdges;

    for (long i = 0; i < g.getVertexsSize(); i++)
    {
        visited.insert(visited.begin() + i, false);
        ack.insert(ack.begin() + i, false);
    }

    for (std::size_t i = 0; i < g.getVertexsSize(); i++)
    {
        if (!visited[i] && cycleIteration(g, i, usedEdges, visited, ack))
            return true;
    }

    return false;
}

bool ariel::Algorithms::cycleIteration(ariel::Graph g, std::size_t v, std::set<std::pair<std::size_t, std::size_t>> &usedEdges, std::vector<bool> &visited, std::vector<bool> &ack)
{
    if (!visited[v])
    {
        visited[v] = true;
        ack[v] = true;
    }

    for (auto &edge : g.getEdges())
    {
        if (edge.first.first == v && (usedEdges.find(edge.first) == usedEdges.end()) && usedEdges.find(std::make_pair(edge.first.second, edge.first.first)) == usedEdges.end())
        {
            usedEdges.insert(edge.first);
            usedEdges.insert(std::make_pair(edge.first.second, edge.first.first));

            if (!visited[edge.first.second] && cycleIteration(g, edge.first.second, usedEdges, visited, ack))
                return true;
            else if (ack[edge.first.second])
                return true;
        }
    }

    ack[v] = false;
    return false;
}

bool ariel::Algorithms::isBipartite(ariel::Graph g, int start, std::vector<int> &color)
{
    std::size_t s = static_cast<std::size_t>(start);
    std::queue<std::size_t> q;

    for (long i = 0; i < g.getVertexs().size(); i++)
    {
        color.insert(color.begin() + i, 0);
    }

    color[s] = 1;
    q.push(s);

    while (!q.empty())
    {
        std::size_t ver = q.front();
        q.pop();

        for (const auto &edge : g.getEdges())
        {
            if (edge.first.first == ver)
            {
                std::size_t secVer = edge.first.second;
                if (color[secVer] == 0)
                {
                    if (color[ver] == 1)
                        color[secVer] = -1;
                    else
                        color[secVer] = 1;
                    q.push(secVer);
                }
                else if (color[ver] == color[secVer])
                    return false;
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

std::string ariel::Algorithms::BellmanFord(ariel::Graph g, std::size_t start, std::vector<int> &distanceList, std::vector<std::size_t> &parentList)
{
    for (long i = 0; i < g.getVertexs().size(); i++)
    {
        distanceList.insert(distanceList.begin() + i, __INT_MAX__);
        parentList.insert(parentList.begin() + i, __INT_MAX__);
    }

    distanceList[start] = 0;

    for (std::size_t i = 0; i < g.getVertexsSize() - 1; i++)
    {
        for (const auto &edge : g.getEdges())
        {
            relax(edge, distanceList, parentList);
        }
    }

    for (const auto &edge : g.getEdges())
    {
        if (distanceList[edge.first.second] > distanceList[edge.first.first] + edge.second)
        {
            std::size_t father = edge.first.first;
            std::string path = std::to_string(father);
            std::size_t i = parentList[father];
            bool flag = true;

            while (flag)
            {
                path += ">-";
                path += std::to_string(i);
                i = parentList[i];
                flag = !(i == parentList[father]);
            }

            return path;
        }
    }

    return "There are no negative cycles in the graph.";
}

void ariel::Algorithms::bfs(ariel::Graph &g, std::size_t s, std::vector<std::size_t> &visited)
{
    std::vector<int> color;
    std::vector<int> distance;
     for (long v = 0; v < g.getVertexs().size(); v++)
    {
        color.insert(color.begin() + v, -1);
        distance.insert(distance.begin() + v, __INT_MAX__);
    }

    color[s] = 0;
    distance[s] = 0;
    visited.push_back(s);

    std::queue<std::size_t> q;
    q.push(s);

    while (!q.empty())
    {
        std::size_t u = q.front();
        q.pop();

        for (const auto &edge : g.getEdges())
        {
            std::size_t ver = edge.first.first;
            if (ver == s)
            {
                std::size_t secVer = edge.first.second;
                if(color[secVer] == -1)
                {
                    color[secVer] = 0;
                    visited.push_back(secVer);
                    distance[secVer] = distance[u] + 1;
                    q.push(secVer);
                }
            }
        }

        color[u] = 1;
    }
}