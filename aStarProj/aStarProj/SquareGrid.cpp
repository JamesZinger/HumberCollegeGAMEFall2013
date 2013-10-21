#include "SquareGrid.h"


SquareGrid::SquareGrid(const int Length, const int Width, const int rand_seed)
{
	mNodes.resize(Length);
	for (int i = 0; i < Length; i++)
		mNodes[i].resize(Width);

	_gen = new MazeGenerator(Length, Width, rand_seed);

	vector < vector < bool > > maze = _gen->GetMaze();

	for (int x = 0; x < Length; x++)
	{
		for (int y = 0; y < Width; y++)
		{
			mNodes[x][y] = new GridNode(maze[x][y]);
		}
	}
	

	for (int x = 0; x < Length; x++)
	{
		for (int y = 0; y < Width; y++)
		{
			if (x == 0)
			{
				mNodes[x][y]->Right = mNodes[x+1][y];
			}
			else if (x == Length - 1)
			{
				mNodes[x][y]->Left = mNodes[x-1][y];
			}

			else
			{
				mNodes[x][y]->Right = mNodes[x+1][y];
				mNodes[x][y]->Left = mNodes[x-1][y];
			}

			if (y == 0)
			{
				mNodes[x][y]->Down = mNodes[x][y+1];
			}
			else if (y == Width - 1)
			{
				mNodes[x][y]->Up = mNodes[x][y-1];
			}
			else 
			{
				mNodes[x][y]->Down = mNodes[x][y+1];
				mNodes[x][y]->Up = mNodes[x][y-1];
			}
		}
	}
}


SquareGrid::~SquareGrid(void)
{
}
