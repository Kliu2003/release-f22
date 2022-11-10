// /* Your code here! */

#include "maze.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace cs225;

SquareMaze::SquareMaze(){}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(dir == 0){
        if(x >= w-1 || rightWalls[x][y]){
            return false;
        }
        return true;
    }
    else if(dir == 1){
        if(y >= h-1 || downWalls[x][y]){
            return false;
        }
        return true;
    }
    else if(dir == 2){
        if(x <= 0 || rightWalls[x-1][y]){
            return false;
        }
        return true;
    }
    else if(dir == 3){
        if(y <= 0 || downWalls[x][y-1]){
            return false;
        }
        return true;
    }
    return false;
}

PNG* SquareMaze::drawMaze() const {
    PNG *maze = new PNG(w*10+1, h*10+1);
    for(int i = 0; i < h*10+1; i++){
		HSLAPixel &p = maze->getPixel(0,i);
		p.l = 0;
	}

	for(int i = 10; i < w*10+1; i++){
		HSLAPixel &p = maze->getPixel(i,0);
		p.l = 0;
	}
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            if(rightWalls[i][j]){
                for(int k = 0; k < 11;k++){
					HSLAPixel &p = maze->getPixel((i+1)*10,(j*10+k));
					p.l = 0;
				}
            }
            if(downWalls[i][j]){
                for(int k = 0; k < 11;k++){
					HSLAPixel &p = maze->getPixel((10*i+k),(j+1)*10);
					p.l = 0;
				}
            }
        }
    }
    return maze;
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG *maze = drawMaze();
    vector<int>solution = solveMaze();
    int x = 5;
    int y = 5;

    for (size_t i = 0; i < solution.size(); i++) {
        for (int j = 0; j < 10; j++) {
            HSLAPixel &p = maze->getPixel(x, y);
            p.h = 0;
            p.s = 1;
            p.l = 0.5;
            p.a = 1;
            if(solution[i] == 0){
                x++;
            }
            else if(solution[i] == 1){
                y++;
            }
            else if(solution[i] == 2){
                x--;
            }
            else if(solution[i] == 3){
                y--;
            }
        }
    }
    HSLAPixel &p = maze->getPixel(x,y);
    p.h = 0;
    p.s = 1;
    p.l = 0.5;
    p.a = 1;


    x -= 4;
    y += 5;
    for(int i = 0; i < 9; i++){
        HSLAPixel &p = maze->getPixel(x+i,y);
        p.l = 1;
    }
    return maze;
}

void SquareMaze::makeMaze(int width, int height){
    w = width;
    h = height;
    int bs = 0;
    mazeDSU.addelements(w*h);
    for(int i = 0; i < w; i++){
        downWalls.push_back(vector<bool>());
        rightWalls.push_back(vector<bool>());
        for(int j = 0; j < h; j++){
            downWalls[i].push_back(true);
            rightWalls[i].push_back(true);
        }
    }
    while(mazeDSU.size(0) != w*h){
        bs++;
        int randomXCoord = rand()%w;
        int randomYCoord = rand()%h;
        int currentTile = randomYCoord*w + randomXCoord;
        int wall = rand()%2;
        if(wall == 0 && randomXCoord != w-1 && mazeDSU.find(currentTile) != mazeDSU.find(currentTile+1)){
            setWall(randomXCoord, randomYCoord, 0, false);
            mazeDSU.setunion(currentTile, currentTile+1);
        }
        else if(wall == 1 && randomYCoord != h-1 && mazeDSU.find(currentTile) != mazeDSU.find(currentTile+w)){
            setWall(randomXCoord, randomYCoord, 1, false);
            mazeDSU.setunion(currentTile, currentTile+w);
        }
    }
    std::cout<<"bs is "<<bs<<std::endl;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir == 0){
        rightWalls[x][y] = exists;
    }
    if(dir == 1){
        downWalls[x][y] = exists;
    }
}

std::vector<int> SquareMaze::solveMaze(){
    vector<int> res;
    map<int, bool>visited;
    map<int, int>path;
    map<int, int>dist;
    map<int, int>backTrack;
    queue<int>bfs;
    int longestInd = -99999;
    int longestPath = -99999;
    

    bfs.push(0);

    for(int i = 0; i < w*h; i++){
        dist[i] = 0;
        visited[i] = false;
    }

    while(!bfs.empty()){
       
        int square = bfs.front();
        bfs.pop();
        int currX = square % w;
        int currY = square / w;
        if(canTravel(currX, currY, 0) && !visited[square+1]){
            visited[square+1] = true;
            path[square+1] = 0;
            dist[square+1] = dist[square] + 1;
            backTrack[square+1] = square;
            bfs.push(square+1);
        }
        if(canTravel(currX, currY, 1) && !visited[square+w]){
            visited[square+w] = true;
            path[square+w] = 1;
            dist[square+w] = dist[square] + 1;
            backTrack[square+w] = square;
            bfs.push(square+w);
        }
        if(canTravel(currX, currY, 2) && !visited[square-1]){
            visited[square-1] = true;
            path[square-1] = 2;
            dist[square-1] = dist[square] + 1;
            backTrack[square-1] = square;
            bfs.push(square-1);
        }
        if(canTravel(currX, currY, 3) && !visited[square-w]){
            visited[square-w] = true;
            path[square-w] = 3;
            dist[square-w] = dist[square] + 1;
            backTrack[square-w] = square;
            bfs.push(square-w);
        }
    }
    

    for(int i = 0; i < w; i++){
        if(dist[(h-1)*w+i] > longestPath){
            longestInd = (h-1)*w+i;
            longestPath = dist[(h-1)*w+i];
        }
    }

    while(longestInd > 0){
        res.push_back(path[longestInd]);
        longestInd = backTrack[longestInd];
    }

    reverse(res.begin(), res.end());
    return res;
}