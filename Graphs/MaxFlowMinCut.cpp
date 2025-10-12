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
	int j = 0;
	int k = 1; // counter for edges
	int c = INT_MAX;
	int vk = 0;
	int u = 0;

	std::set<int> Q = { nQ };
	std::set<int> W = {};
	std::set<int> X = {};
	std::vector<int> Es = vcEdges;

	while (Q.size() > 0 && Q.find(nS) == Q.end())
	{
		for (;j < vcVertices.size(); j++)
		{
			for (auto ei : Es)
			{
				Edge& e = mpDelta[ei];

				if (e.nVFrom == vcVertices[j] &&
					(X.find(e.nVTo) == X.end() && Q.find(e.nVTo) == Q.end()) &&
					(e.nC - e.nF) > 0)
				{
					W.insert(ei);
					c = std::min(e.nC - e.nF, c);
					vk = e.nVTo; // vk = u;
					Q.insert(e.nVTo);
					k++;
				}
				else if (e.nVTo == vcVertices[j] &&
					(X.find(e.nVFrom) == X.end() && Q.find(e.nVFrom) == Q.end()) &&
					e.nF > 0)
				{
					W.insert(ei);
					c = std::min(e.nF, c);
					vk = e.nVFrom; // vk = u;
					Q.insert(e.nVFrom);
					k++;
				}

			}
		}

		printf("Capacity: %d, %d", c, W.size());
	}

	return true;
}
