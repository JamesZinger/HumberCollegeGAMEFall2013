#pragma once
#include <time.h>
#include <vector>
#include <list>
using namespace std;
class MazeGenerator
{
private:
	vector < vector < bool > > maze;
	
public:
	MazeGenerator(const int length, const int width, const int rand_seed);
	~MazeGenerator(void);

	vector < vector < bool > > GetMaze(void) { return maze; }
	list < pair <int,int> > openTiles;
};

