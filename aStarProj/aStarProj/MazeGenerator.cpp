#include "MazeGenerator.h"


MazeGenerator::MazeGenerator(const int Length, const int Width, const int rand_seed)
{
	srand(rand_seed);
	
	list < pair < int, int> > drillers;
	maze.resize(Length);
	
	for (size_t y=0;y<Length;y++)
		maze[y].resize(Width);

	for (size_t x=0;x<Width;x++)
		for (size_t y=0;y<Length;y++)
			maze[y][x]=false;

	drillers.push_back(make_pair(Width/2,Length/2));
	while(drillers.size()>0)
	{
		list < pair < int, int> >::iterator m,_m,temp;
		m=drillers.begin();
		_m=drillers.end();
		
		while (m!=_m)
		{
			bool remove_driller=false;
			switch(rand()%4)
			{
			case 0:
				(*m).second-=2;
				if ((*m).second<0 || maze[(*m).second][(*m).first])
				{
					remove_driller=true;
					break;
				}
				maze[(*m).second+1][(*m).first]=true;
				openTiles.push_back(make_pair((*m).second+1,(*m).first));
			break;
			case 1:
				(*m).second+=2;
				if ((*m).second>=Length || maze[(*m).second][(*m).first])
				{
					remove_driller=true;
					break;
				}
				maze[(*m).second-1][(*m).first]=true;
				openTiles.push_back(make_pair((*m).second-1,(*m).first));
			break;
			case 2:
				(*m).first-=2;
				if ((*m).first<0 || maze[(*m).second][(*m).first])
				{
					remove_driller=true;
					break;
				}
				maze[(*m).second][(*m).first+1]=true;
				openTiles.push_back(make_pair((*m).second,(*m).first+1));
			break;
			case 3:
				(*m).first+=2;
				if ((*m).first>=Width || maze[(*m).second][(*m).first])
				{
					remove_driller=true;
					break;
				}
				maze[(*m).second][(*m).first-1]=true;
				openTiles.push_back(make_pair((*m).second,(*m).first-1));
			break;
			}
			
			if (remove_driller)
				m = drillers.erase(m);
			else
			{
				drillers.push_back(make_pair((*m).first,(*m).second));
				// uncomment the line below to make the maze easier
				// if (rand()%2)
				drillers.push_back(make_pair((*m).first,(*m).second));
				
				maze[(*m).second][(*m).first]=true;
				openTiles.push_back(make_pair((*m).second,(*m).first));
				++m;
			}
		}
	}
}


MazeGenerator::~MazeGenerator(void)
{
}

