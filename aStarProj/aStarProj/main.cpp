#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "SquareGrid.h"
#include <time.h>
#include <list>
using namespace std;
int main ( int argc, const char* argv[] )
{

	ofstream file;
	file.open("Output.txt");
	SquareGrid* Grid = new SquareGrid(20, 10, 251);

	//Insert Grid Generation Algorithm here
	
	file << "   ";

	for (int i = 0; i < 20; i++)
		file << i << " ";

	file << "\n";

	for (int y = 0; y < 10; y++)
	{
		file << y << ": ";
		for (int x = 0; x < 20; x++)
		{
			if (Grid->mNodes[x][y]->Passable)
				file << ". ";
			else
				file << "# ";
		}
		file << "\n";
		
	}

	srand(time(0));

	pair<int,int> start;
	start.first = (Grid->_gen->openTiles.begin())->first;
	start.second = (Grid->_gen->openTiles.begin())->second;
	pair<int,int> end;
	end.first = (Grid->_gen->openTiles.end())->first;
	end.second = (Grid->_gen->openTiles.end())->second;

	file << "Start	X: " << start.first << ", Y: " << start.second << "\n";
	file << "End	X: " << end.first << ", Y: " << end.second << "\n";

	//Grid->Pathfind(start.first, start.second, end.first, end.second);


	file.close();
	//int s;
	//cin >> s;

	return 0;
}