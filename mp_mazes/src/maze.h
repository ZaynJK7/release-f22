#ifndef _MAZE_H_
#define _MAZE_H_
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace cs225;

class SquareMaze {
    public:

    //Empty constructor
    SquareMaze();

    bool canTravel(int x, int y, int dir ) const;

    PNG * drawMaze() const;

    PNG* drawMazeWithSolution();

    void makeMaze(int width, int height);

    void setWall(int x, int y, int dir, bool exists);

    std::vector<int> solveMaze();


    private:

    int mazeWidth;
    int mazeHeight;
    DisjointSets set;

    std::vector<bool> down;
    std::vector<bool> right;
    int size;

    int findX(int a) const;
    int findY(int a) const;
    int findPos(int x, int y) const;

};

#endif