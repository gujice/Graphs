#pragma once

#include "Graph.h"

class Digraph : public Graph
{
public:
	// quelle, senke
	int nQ;
	int nS;

	bool DoMaxFlowMinCut();

private:
	void Init();

	void BuildPlusNeighborsMap();

	std::map<int, std::vector<int>> mpPlusNeighbors;

};