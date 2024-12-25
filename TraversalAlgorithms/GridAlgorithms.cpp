#include "grid.h"
#include <iostream>

void WeightedGrid::initGrid(unsigned int width, unsigned int height){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            adjGrid[i].push_back(INT_MAX);
        }
    }
}

void WeightedGrid::setWall(unsigned int x, unsigned int y){
    adjGrid[y][x] = -1;
}

void WeightedGrid::pushNeighbour(int &vertexX, int &vertexY, int &cost,
        std::priority_queue<std::pair<int, std::pair<unsigned int, unsigned int> >,
                        std::vector< std::pair<int, std::pair<unsigned int, unsigned int> > >,
                        std::greater< std::pair<int, std::pair<unsigned int, unsigned int> > >
    > &pq){
        //////////// NOT DIAGONAL ///////////

        if( (vertexX-1) >= 0 && adjGrid[vertexY][vertexX]+10 < adjGrid[vertexY][vertexX-1]){
            adjGrid[vertexY][vertexX-1] = adjGrid[vertexY][vertexX]+10;
            pq.push(std::make_pair(adjGrid[vertexY][vertexX-1], std::make_pair(vertexY,vertexX-1)));
            previousCell[{vertexY,vertexX-1}] = {vertexY,vertexX};
        }
        if( (vertexY-1) >= 0 && adjGrid[vertexY][vertexX]+10 < adjGrid[vertexY-1][vertexX]){
           adjGrid[vertexY-1][vertexX] = adjGrid[vertexY][vertexX]+10;
           pq.push(std::make_pair(adjGrid[vertexY-1][vertexX], std::make_pair(vertexY-1,vertexX)));
           previousCell[{vertexY-1,vertexX}] = {vertexY,vertexX};
        }
        if( (vertexX+1) < 8 && adjGrid[vertexY][vertexX]+10 < adjGrid[vertexY][vertexX+1]){
            adjGrid[vertexY][vertexX+1] = adjGrid[vertexY][vertexX]+10;
            pq.push(std::make_pair(adjGrid[vertexY][vertexX+1], std::make_pair(vertexY,vertexX+1)));
            previousCell[{vertexY,vertexX+1}] = {vertexY,vertexX};
        }
        if( (vertexY+1) < 8 && adjGrid[vertexY][vertexX]+10 < adjGrid[vertexY+1][vertexX]){
            adjGrid[vertexY+1][vertexX] = adjGrid[vertexY][vertexX]+10;
            pq.push(std::make_pair(adjGrid[vertexY+1][vertexX], std::make_pair(vertexY+1,vertexX)));
            previousCell[{vertexY+1,vertexX}] = {vertexY,vertexX};
        }

        //////////// DIAGONAL ///////////

        if( (vertexX-1) >= 0 && (vertexY-1) >= 0 && adjGrid[vertexY][vertexX]+14 < adjGrid[vertexY-1][vertexX-1]){
            adjGrid[vertexY-1][vertexX-1] = adjGrid[vertexY][vertexX]+14;
            pq.push(std::make_pair(adjGrid[vertexY-1][vertexX-1], std::make_pair(vertexY-1,vertexX-1)));
            previousCell[{vertexY-1,vertexX-1}] = {vertexY,vertexX};
        }
        if( (vertexX-1) >= 0 && (vertexY+1) < 8 && adjGrid[vertexY][vertexX]+14 < adjGrid[vertexY+1][vertexX-1]){
            adjGrid[vertexY+1][vertexX-1] = adjGrid[vertexY][vertexX]+14;
            pq.push(std::make_pair(adjGrid[vertexY+1][vertexX-1], std::make_pair(vertexY+1,vertexX-1)));
            previousCell[{vertexY+1,vertexX-1}] = {vertexY,vertexX};
        }

        if( (vertexX+1) < 8 && (vertexY-1) >= 0 && adjGrid[vertexY][vertexX]+14 < adjGrid[vertexY-1][vertexX+1]){
            adjGrid[vertexY-1][vertexX+1] = adjGrid[vertexY][vertexX]+14;
            pq.push(std::make_pair(adjGrid[vertexY-1][vertexX+1], std::make_pair(vertexY-1,vertexX+1)));
            previousCell[{vertexY-1,vertexX+1}] = {vertexY,vertexX};
        }
        if( (vertexX+1) < 8 && (vertexY+1) < 8 && adjGrid[vertexY][vertexX]+14 < adjGrid[vertexY+1][vertexX+1]){
            adjGrid[vertexY+1][vertexX+1] = adjGrid[vertexY][vertexX]+14;
            pq.push(std::make_pair(adjGrid[vertexY+1][vertexX+1], std::make_pair(vertexY+1,vertexX+1)));
            previousCell[{vertexY+1,vertexX+1}] = {vertexY,vertexX};
        }
}

void WeightedGrid::dijkstraGrid(unsigned int x, unsigned int y){
    visitedCell.clear();


    adjGrid[y][x] = 0; // set start
    startX = x;
    startY = y;

    std::priority_queue<std::pair<int, std::pair<unsigned int, unsigned int> >,
                        std::vector< std::pair<int, std::pair<unsigned int, unsigned int> > >,
                        std::greater< std::pair<int, std::pair<unsigned int, unsigned int> > >
    > pq;

    pq.push(std::make_pair(0, std::make_pair(y,x)));

    while(!pq.empty()){
        std::pair< int,  int> current_vertex = pq.top().second;
        int cost = pq.top().first;
        int vertexY = current_vertex.first;
        int vertexX = current_vertex.second;
        pq.pop();

        if(visitedCell.find(current_vertex) != visitedCell.end()){
            continue;
        }

        if(cost == -1)
            continue;

        std::cout << "Y, X: " << vertexY << ", " << vertexX << ". Distance: " << cost << '\n';

        visitedCell.insert(std::make_pair(vertexY, vertexX));

        pushNeighbour(vertexX, vertexY, cost, pq);
    }
}

void WeightedGrid::printGrid(unsigned int width, unsigned int height){
    for(int i = 0; i < height; i++){
        std::cout<<'\n';
        for(int j = 0; j < width; j++){
            std::cout<<adjGrid[i][j]<<' ';
        }
    }
    std::cout<<std::endl<<std::endl;
}

void WeightedGrid::findPath(unsigned int endX, unsigned int endY){
    std::pair<unsigned int, unsigned int> start = {startY,startX};
    std::pair<unsigned int, unsigned int> prev;
    std::vector<std::pair<unsigned int, unsigned int>> path;

    int x = endX, y = endY;
    path.push_back({y,x});

    while(prev != start){
        prev = previousCell[{y,x}];
        y = prev.first;
        x = prev.second;
        path.push_back(prev);
    }

    std::reverse(path.begin(), path.end());

    for(auto const &cell : path){
        std::cout << cell.first << ' ' << cell.second << '\n';
    }
}
