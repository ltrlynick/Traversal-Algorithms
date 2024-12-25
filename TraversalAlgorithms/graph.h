#include <unordered_map>
#include <unordered_set>
#include <list>

class Graph{
  private:
    std::unordered_map<int, std::list<int>> adj;
    std::unordered_set<int> visited;
  public:
    void addEdge(int v, int w);
    void BFS(int s);
    void DFS(int s);
    void DFStraverse(int s);
    void DFS_Rec(int s);
    ~Graph();
};

class WeightedGraph{
    private:
        std::unordered_set<char> visited;
        std::unordered_map<char, std::list<std::pair<char,unsigned int>>> adj;
        std::unordered_set<char> all_edges;
        std::unordered_map<char, int> previous;

    public:
        void addEdge(char u, char v, int w);
        void setWeightToINF(std::unordered_map<char,int> &distance);
        void dijkstra(const char start);
};
