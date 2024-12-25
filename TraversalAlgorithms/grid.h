#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <utility>

class WeightedGrid{
    private:
        unsigned int startX,startY;

        std::unordered_map<unsigned int, std::vector<int>> adjGrid; //represent a grid like this
        std::map< std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> > previousCell;
        std::set<std::pair<unsigned int, unsigned int>> visitedCell; //save visited data
    public:
        void initGrid(unsigned int width, unsigned int height);
        void setWall(unsigned int x, unsigned int y);
        void pushNeighbour(int &vertexX, int &vertexY, int &cost,
        std::priority_queue<std::pair<int, std::pair<unsigned int, unsigned int> >,
                        std::vector< std::pair<int, std::pair<unsigned int, unsigned int> > >,
                        std::greater< std::pair<int, std::pair<unsigned int, unsigned int> > >
                        > &pq
        );
        void dijkstraGrid(unsigned int x, unsigned int y);
        void printGrid(unsigned int width, unsigned int height);
        void findPath(unsigned int endX, unsigned int endy);
};
