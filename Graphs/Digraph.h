#pragma once

#include "Graph.h"

class Digraph : public Graph
{
public:
	// quelle, senke
	int nQ;
	int nS;

	bool DoMaxFlowMinCut();
	bool EdmondsKarpAlg();

private:
	void Init1();

	void BuildPlusNeighborsMap();

	std::map<int, std::vector<int>> mpPlusNeighbors;

};