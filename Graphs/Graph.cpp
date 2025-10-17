#include "Graph.h"

using namespace std;

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
	/*
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
	*/
	int V[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int E[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	AddVertices(V, 16);
	AddEdges(E, 16);

	// kanten
	mpDelta = {
		{1, Edge(1, 2, 0) },
		{2, Edge(2, 3, 0) },
		{3, Edge(3, 4, 0) },
		{4, Edge(4, 5, 0) },
		{5, Edge(5, 6, 0) },
		{6, Edge(6, 15, 0) },
		{7, Edge(2, 7, 0) },
		{8, Edge(3, 8, 0) },
		{9, Edge(5, 9, 0) },
		{10, Edge(1, 10, 0) },
		{11, Edge(2, 11, 0) },
		{12, Edge(3, 12, 0) },
		{13, Edge(11, 12, 0) },
		{14, Edge(12, 13, 0) },
		{15, Edge(13, 14, 0) },
		{16, Edge(13, 16, 0) }
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
		printf("Graph is NOT bipartit! (different count of elements %d <-> %d)\n", (int)vcVertices.size(), (int)(setV1.size() + setV2.size()));
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
	printf("PARTITION:\n");
	printf("V1: ");
	for (auto e : setV1)
		printf("%d, ", e);
	printf("\nV2: ");
	for (auto e : setV2)
		printf("%d, ", e);
	printf("\n");

	return true;
}

std::vector<int> Graph::CreateTreeByBreadthFirst(int nStartEcke)
{
	std::vector<int> resTreeEdges;
	int nVCount = (int)vcVertices.size();
	vector<int>* pVcNeighbours = NULL; 

	try
	{
		pVcNeighbours = new vector<int>[nVCount + 1];
		for (auto ite = vcEdges.begin(); ite != vcEdges.end(); ite++)
		{
			if(mpDelta.find(*ite) != mpDelta.end())
			{
				int from = mpDelta[*ite].nVFrom;
				int to = mpDelta[*ite].nVTo;

				pVcNeighbours[from].push_back(to);
				pVcNeighbours[to].push_back(from);
			}
		}
	}
	catch (exception& e)
	{
		string s = e.what();
		printf("%s\n", s.c_str());

		return resTreeEdges;
	}

	queue<int> qEckenToDo;
	set<int> setEckenDone;

	qEckenToDo.emplace(nStartEcke);

	while (!qEckenToDo.empty())
	{
		int nNextEcke = qEckenToDo.front();
		qEckenToDo.pop();
		for (auto itn = pVcNeighbours[nNextEcke].begin(); itn != pVcNeighbours[nNextEcke].end(); itn++)
		{
			int nNeighbour = *itn;
			if (setEckenDone.find(nNeighbour) == setEckenDone.end())
			{
				// resTreeEdges.push_back(nNeighbour);
				printf("***** %d - %d *********\n", nNextEcke, nNeighbour);

				setEckenDone.insert(nNeighbour);
				qEckenToDo.emplace(nNeighbour);
			}
		}

		setEckenDone.insert(nNextEcke);
	}

	return resTreeEdges;
}
