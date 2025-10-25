#pragma once

#include "Graph.h"

class Digraph : public Graph
{
public:
	Digraph();

public:
	bool DoMaxFlowMinCut();
	bool EdmondsKarpAlg();

private:
	void Init1();

	void BuildPlusNeighborsMap();

	std::map<int, std::vector<int>> mpPlusNeighbors;

};