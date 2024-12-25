#include "graph.h"
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <climits>

//////////////////////////////////////////////
///           UNWEIGHTED GRAPHS            ///
//////////////////////////////////////////////

void Graph::addEdge(int v, int w){
  adj[v].push_back(w);
  adj[w].push_back(v);
}

void Graph::BFS(int s){
  visited.clear();

  std::queue<int> Q;
  Q.push(s);

  while(!Q.empty()){
    int current = Q.front();
    Q.pop();

    if(visited.find(current) != visited.end()) 
      continue; //if we already visited, just continue

    visited.insert(current); //insert the element we visited
    std::cout << current << ' ';

    for(int& neighbour : adj[current])
      if(visited.find(neighbour) == visited.end())
        Q.push(neighbour); //if its equal to end, it means we didnt visit
  }
  std::cout << '\n';
}

void Graph::DFS(int s){
  visited.clear();

  std::stack<int> S;
  S.push(s);

  while(!S.empty()){
    int current = S.top();
    S.pop();

    if(visited.find(current) != visited.end()) 
      continue; //if we already visited, just continue

    visited.insert(current); //insert the element we visited
    std::cout << current << ' ';

    for(auto it = adj[current].rbegin(); it != adj[current].rend(); it++){
      if(visited.find(*it) == visited.end()){
        S.push(*it);
      }
    }
  }
  std::cout << '\n';
}

void Graph::DFStraverse(int s){
  visited.insert(s);
  std::cout << s << ' ';

  for(const int& neighbour : adj[s]){
    if(visited.find(neighbour) == visited.end()){
      DFStraverse(neighbour);
    }
  }
}

void Graph::DFS_Rec(int s){
  visited.clear();
  DFStraverse(s);
  std::cout << '\n';
}

Graph::~Graph(){
  std::cout << "Deleted\n";
}

//////////////////////////////////////////////
///             WEIGHTED GRAPHS            ///
//////////////////////////////////////////////

void WeightedGraph::addEdge(char u, char v, int w)
{
    adj[u].push_back({v,w});
    all_edges.insert(u);
    all_edges.insert(v);
}

void WeightedGraph::setWeightToINF(std::unordered_map<char,int> &distance){
    for(const auto edge : all_edges){
        distance[edge] = INT_MAX;
        std::cout<<edge<<' ';
    }

    std::cout<<std::endl;
}

void WeightedGraph::dijkstra(const char start){
    visited.clear();
    std::unordered_map<char,int> distance; //distance value of nodes

    setWeightToINF(distance);

    distance[start] = 0; //we start from a 0

    std::priority_queue<
        std::pair<int, char>,
        std::vector<std::pair<int, char>>,
        std::greater<std::pair<int,char>>
    > pq;

    pq.push({0, start});

    while( !pq.empty() ){
        std::pair<int, char> current = pq.top(); //grab the one w smallest int
        pq.pop();

        char current_vert = current.second;
        int current_distance = current.first;

        if(visited.find(current_vert) != visited.end())
            continue;

        std::cout << "Current Vertex: " << current_vert << " Current Distance: " << current_distance << '\n';

        visited.insert((current_vert));

        for(const auto& edge : adj[current_vert]){
           char neighbor = edge.first;
           int neighbor_distance = edge.second;
           int new_distance = current_distance + neighbor_distance;

           std::cout << "   Neighbour: " << neighbor << '\n';
           std::cout << "       Neighbours Distance: " << neighbor_distance << '\n';

           if(new_distance < distance[neighbor]){
               distance[neighbor] = new_distance;
               previous[neighbor] = current_vert;
               std::cout << "       Neighbours Parent:" << (char)previous[neighbor] << '\n';
               std::cout << "       NEW Neighbours Distance: " << distance[neighbor] << '\n';
               pq.push({new_distance,neighbor});
           }
        }
    }

    //print all vertices and their distances
    
    for(const auto vertex : adj){ 
        std::cout << vertex.first<<' '<<distance[vertex.first]<<' ';
    }
    std::cout<<std::endl;
}
