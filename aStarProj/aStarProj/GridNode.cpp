#include "GridNode.h"


GridNode::GridNode(bool Passable)
{
	this->Passable = Passable;
	Left = 0;
	Right = 0;
	Up = 0;
	Down = 0;
}


GridNode::~GridNode(void)
{
}
