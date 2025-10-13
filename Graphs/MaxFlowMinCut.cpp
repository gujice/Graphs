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

	// create neightbours list
	BuildPlusNeighborsMap();

	for (int i = 0; i < 3; i++)
	{
		// init area
		std::vector<int> vcW;
		std::set<int> setVVisited = {nQ};
		bSReached = false;
		bNoNext = false;
		v = nQ;
		c = INT_MAX;

		printf("%d\n", v);

		while (!bSReached && !bNoNext)
		{
			if (mpPlusNeighbors.find(v) != mpPlusNeighbors.end())
			{
				for (auto it = mpPlusNeighbors[v].begin(); it != mpPlusNeighbors[v].end(); it++)
				{
					int ei = *it;
					Edge& e = mpDelta[ei];

					// check already visited
					if (setVVisited.find(e.nVTo) == setVVisited.end() && (e.nC > e.nF))
					{
						if (e.nVTo == nS)
						{
							bSReached = true;
						}

						// capacity 
						if (e.Rest() < c)
							c = e.Rest();

						// next vertix
						v = e.nVTo;
						vcW.push_back(ei);

						// visited!
						setVVisited.insert(e.nVTo);

						printf("%d\n", v);
						break;
					}
				}
			}
			else
				bNoNext = false;
		}

		printf("\nCapacity %d\n", c);
		for (auto& ei : vcW)
		{
			printf("%d-%d ", mpDelta[ei].nVFrom, mpDelta[ei].nVTo);

			mpDelta[ei].nF += c;
		}
	}

	return true;
}

void Digraph::BuildPlusNeighborsMap()
{
	mpPlusNeighbors.clear();

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
