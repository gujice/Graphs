#pragma once

#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <algorithm> 

typedef unsigned char byte;

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
	int GetOtherV(int v) { return v == nVFrom ? nVTo : nVFrom; }
};

class Graph
{
protected:
	std::vector<int> m_vcVertices;
	std::vector<int> m_vcEdges;

	std::map<int, std::vector<int>> mpNeighbors;
	std::map<int, std::vector<int>> mpCoveredEdgesByV;


public:

	// edge -> (vert1, vert2)
	std::map<int, Edge> m_mpDelta;

	// quelle, senke
	int nQ;
	int nS;

	void AddVertices(int* pVerts, int count);
	void AddEdges(int* pEdges, int count);

	void Init();
	bool IsBipartit();

	// euler
	bool IsEulerian();
	std::vector<int> FindEulertour();

	// hamilton
	bool CheckKorollarORE();
	bool CheckKorollarDIRAC();
	bool CheckTheoremCHVATAL();
	bool DoHamiltonAlg();

	bool CreateWaysByDijkstra(int nStartEcke);

	std::vector<int> CreateTreeByBreadthFirst(int nStartEcke);

private:
	void BuildNeighborsMap();

};
