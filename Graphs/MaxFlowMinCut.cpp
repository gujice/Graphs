#include "MaxFlowMinCut.h"

void Digraph::AddVertices(int* pVerts, int count)
{
	for (int i = 0; i < count; i++)
	{
		vcVertices.push_back(pVerts[i]);
	}
}

void Digraph::AddEdges(int* pEdges, int count)
{
	for (int i = 0; i < count; i++)
	{
		vcEdges.push_back(pEdges[i]);
	}
}

bool Digraph::DoMaxFlowMinCut()
{
	std::set<int> setVVisited;
	int v = nQ;
	bool bSReached = false;
	bool bNoNext = false;

	int c = INT_MAX;

	printf("%d\n", v);

	// create neightbours list
	BuildPlusNeighborsMap();

	while (!bSReached && !bNoNext)
	{
		if (mpPlusNeighbors.find(v) != mpPlusNeighbors.end())
		{
			for (auto it = mpPlusNeighbors[v].begin(); it != mpPlusNeighbors[v].end(); it++)
			{
				Edge& e = mpDelta[*it];
				if (e.nVTo == nS)
				{
					bSReached = true;
				}

				// capacity 
				if (e.nC < c)
					c = e.nC;

				// next vertix
				v = e.nVTo;

				printf("%d\n", v);
				break;
			}
		}
		else
			bNoNext = false;
	}

	printf("Capacity %d\n", c);

	return true;
}

void Digraph::BuildPlusNeighborsMap()
{
	for (auto itv = vcVertices.begin(); itv != vcVertices.end(); itv++)
	{
		int v = *itv;
		for (auto ite = vcEdges.begin(); ite != vcEdges.end(); ite++)
		{
			int ei = *ite;

			// must exists
			auto fe = mpDelta.find(ei);
			if (fe != mpDelta.end())
			{
				Edge& e = fe->second;
				if (e.nVFrom == v)
				{
					// mpPlusNeighbors[v].push_back(e.nVTo);
					mpPlusNeighbors[v].push_back(ei);
				}
			}
		}
	}
}
