#pragma once

#include "GridNode.h"
#include "MazeGenerator.h"
#include <array>
#include <vector>

using namespace std;
class SquareGrid
{
private:
	
	
public:
	SquareGrid(const int Length, const int Width, const int rand_seed);
	~SquareGrid(void);
	
	vector<vector<GridNode*>> mNodes;
	
	vector<GridNode*> Pathfind(int startx, int starty, int endx, int endy);

	MazeGenerator* _gen;
};

