// /* Your code here! */
#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include "cs225/PNG.h"
#include "dsets.h"
using namespace cs225;
using namespace std;

class SquareMaze {

  public:
    SquareMaze();
    bool canTravel(int x, int y, int dir) const;
    cs225::PNG *drawMaze() const;
    cs225::PNG *drawMazeWithSolution();
    void makeMaze(int width, int height);
    void setWall(int x, int y, int dir, bool exists);
    std::vector<int> solveMaze();

  private:
    DisjointSets mazeDSU;
    vector<vector<bool>> downWalls;
    vector<vector<bool>> rightWalls;
    int w;
    int h;
};


