#include "GraphAlgorithms.cpp"
#include "GridAlgorithms.cpp"

// ---- GRID ----
#define startX 3
#define startY 4
#define width 6
#define height 6

int main()
{
    WeightedGrid obj1;

    obj1.initGrid(width, height); 

    obj1.setWall(0, 0);
    obj1.setWall(1, 0); 
    obj1.setWall(2, 0); 
    obj1.setWall(3, 0);
    obj1.setWall(4, 0);
    obj1.setWall(5, 0);

    obj1.setWall(0, 1);
    obj1.setWall(5, 1);

    obj1.setWall(0, 2);
    obj1.setWall(2, 2);
    obj1.setWall(3, 2);
    obj1.setWall(5, 2);

    obj1.setWall(0, 3);
    obj1.setWall(2, 3);
    obj1.setWall(5, 3);

    obj1.setWall(0, 4);
    obj1.setWall(5, 4);

    obj1.setWall(0, 5);
    obj1.setWall(1, 5); 
    obj1.setWall(2, 5); 
    obj1.setWall(3, 5);
    obj1.setWall(4, 5);
    obj1.setWall(5, 5);

    obj1.dijkstraGrid(startX, startY);
    obj1.printGrid(width, height);
    obj1.findPath(1, 1);

    std::cout<<std::endl<<std::endl;

    ///////////////////////////////////
    /// DIJKSTRA ON WEIGHTED GRAPHS ///
    ///////////////////////////////////

    WeightedGraph obj2;

    obj2.addEdge('D', 'A', 4);
    obj2.addEdge('D', 'E', 2);
    obj2.addEdge('A', 'E', 4);
    obj2.addEdge('A', 'C', 3);
    obj2.addEdge('E', 'C', 4);
    obj2.addEdge('E', 'G', 5);
    obj2.addEdge('G', 'C', 5);
    obj2.addEdge('G', 'F', 5);
    obj2.addEdge('C', 'F', 5);
    obj2.dijkstra('D');

    std::cout<<std::endl<<std::endl;

    ////////////////////////////////////////////////////////////
    /// DFS AND BFS ON A NON-WEIGHTED AND NON-DIRECTED GRAPH ///
    ////////////////////////////////////////////////////////////

    Graph obj3;

    obj3.addEdge(0, 1);
    obj3.addEdge(0, 2);
    obj3.addEdge(2, 0);
    obj3.addEdge(2, 3);
    obj3.addEdge(3, 3);
    obj3.BFS(2);
    obj3.DFS(2);
    obj3.DFS_Rec(2);
}
