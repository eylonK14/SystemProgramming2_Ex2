#include "Graph.hpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>

namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(ariel::Graph);
        static std::string shortestPath(const ariel::Graph&, int, int);
        static std::string isContainsCycle(const ariel::Graph &);
        static std::string isBipartite(const ariel::Graph&);
        static std::string negativeCycle(const ariel::Graph&);

    private:
        static std::string BellmanFord(const ariel::Graph&, std::size_t, std::vector<int> &, std::vector<std::size_t> &);
        static void relax(std::pair<std::pair<std::size_t, std::size_t>, int>, std::vector<int> &, std::vector<std::size_t> &);
        static bool isBipartite(const ariel::Graph&, int, std::vector<int> &);
        static bool cycleIteration(const ariel::Graph&, std::size_t, std::set<std::pair<std::size_t, std::size_t>>&, std::vector<bool> &, std::vector<bool> &);
        static bool findCycle(const ariel::Graph&, std::vector<bool> &);
        static void bfs(ariel::Graph&, std::size_t, std::vector<std::size_t>&);
    };
}