#pragma once

class GridNode
{
public:
	GridNode(bool Passable);
	~GridNode(void);

	bool Passable;

	GridNode* Up;
	GridNode* Down;
	GridNode* Right;
	GridNode* Left;
};

