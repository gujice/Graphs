#pragma once

#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>

struct Edge
{
	int nVFrom;
	int nVTo;

	int nC;
	int nF;

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

	int Rest() { return nC - nF; }
};

class Graph
{
protected:
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

	void Init();
	bool IsBipartit();

	bool CreateWaysByDijkstra(int nStartEcke);

	std::vector<int> CreateTreeByBreadthFirst(int nStartEcke);

};