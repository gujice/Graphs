#include "Graph.h"

void Graph::AddVertices(int* pVerts, int count)
{
	for (int i = 0; i < count; i++)
	{
		vcVertices.push_back(pVerts[i]);
	}
}

void Graph::AddEdges(int* pEdges, int count)
{
	for (int i = 0; i < count; i++)
	{
		vcEdges.push_back(pEdges[i]);
	}
}

void Graph::Init()
{
	int V[6] = { 1, 2, 3, 4, 5, 6 };
	int E[6] = { 12, 14, 23, 36, 45, 56 };

	AddVertices(V, 6);
	AddEdges(E, 6);

	// kanten
	mpDelta = {
		{12, Edge(1, 2, 3) },
		{14, Edge(1, 4, 7) },
		{23, Edge(2, 3, 3) },
		{36, Edge(3, 6, 4) },
		{45, Edge(4, 5, 5) },
		{56, Edge(5, 6, 3) },
		{34, Edge(3, 4, 3) },
		{24, Edge(2, 5, 3) },
		{16, Edge(1, 6, 3) }
	};

	IsBipartit();
}

bool Graph::IsBipartit()
{
	enum eSet { NO, V1, V2 } eV = NO;
	std::set<int> setV1;
	std::set<int> setV2;

	for (auto itv = vcVertices.begin(); itv != vcVertices.end(); itv++)
	{
		eV = NO;
		int v = *itv;

		if (setV1.find(v) != setV1.end())
			eV = V1;
		if (setV2.find(v) != setV2.end())
			eV = V2;

		if (eV == NO)
		{
			setV1.insert(v);
			eV = V1;
		}

		for (auto e : mpDelta)
		{
			int ei = e.first;
			const Edge& edge = e.second;

			if (edge.nVFrom == v)
			{
				if (eV == V1)
					setV2.insert(edge.nVTo);
				else
					setV1.insert(edge.nVTo);
			}
			else if (edge.nVTo == v)
			{
				if (eV == V1)
					setV2.insert(edge.nVFrom);
				else
					setV1.insert(edge.nVFrom);
			}
		}
	}

	// first fast check
	// both sets should be have at all the same count of elements as V
	if (vcVertices.size() != (setV1.size() + setV2.size()))
	{
		printf("Graph is NOT bipartit! (different count of elements %d <-> %d)\n", vcVertices.size(), (setV1.size() + setV2.size()));
		return false;
	}

	// no common elements
	for (auto e : setV1)
	{
		if (setV2.find(e) != setV2.end())
		{
			printf("Graph is NOT bipartit! (common element %d)\n", e);
			return false;
		}
	}

	printf("Graph is bipartit!!!\n");
	return true;
}
