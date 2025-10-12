#pragma once

#include <vector>
#include <map>
#include <set>

struct Edge
{
	int nVFrom;
	int nVTo;

	int nF;
	int nC;

	Edge()
	{
		nVFrom = 0;
		nVTo = 0;
		nF = 0;
		nC = 0;
	}

	Edge(int from, int to, int c)
	{
		nVFrom = from;
		nVTo = to;
		nF = 0;
		nC = c;
	}
};

class Digraph
{
	std::vector<int> vcVertices;
	std::vector<int> vcEdges;

public:

	// edge -> (vert1, vert2)
	std::map<int, Edge> mpDelta;

	// quelle, senke
	int nQ;
	int nS;

	void AddVertices(int* pVerts, int count);
	void AddEdges(int* pEdges, int count);

	bool DoMaxFlowMinCut();

private:

	void BuildPlusNeighborsMap();

	std::map<int, std::vector<int>> mpPlusNeighbors;

};