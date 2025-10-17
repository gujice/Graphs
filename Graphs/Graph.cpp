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
	std::map<int, std::vector<int>> mpPlusNeighbors;

	try
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
					if (e.nVFrom == v || e.nVTo == v)
						mpPlusNeighbors[v].push_back(ei);
				}
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
		for (auto itn = mpPlusNeighbors[nNextEcke].begin(); itn != mpPlusNeighbors[nNextEcke].end(); itn++)
		{
			int nNeighbourEdge = *itn;
			int nNeighbour = mpDelta[nNeighbourEdge].nVTo;
			if (nNeighbour == nNextEcke)
				nNeighbour = mpDelta[nNeighbourEdge].nVFrom;
			if (setEckenDone.find(nNeighbour) == setEckenDone.end())
			{
				// resTreeEdges.push_back(nNeighbour);
				printf("***** %2d - %2d (%d) *********\n", nNextEcke, nNeighbour, nNeighbourEdge);

				setEckenDone.insert(nNeighbour);
				qEckenToDo.emplace(nNeighbour);
			}
		}

		setEckenDone.insert(nNextEcke);
	}

	return resTreeEdges;
}

bool Graph::CreateWaysByDijkstra(int nStartEcke)
{
	vector<Edge> m_vcKantenDone;
	bool* m_pEckenDone;
	float* m_pL;
	vector<Edge>* m_vcPaths;
	int m_nEckenCount = (int)vcVertices.size();
	int m_nStartEcke = nStartEcke;

	// reset
	m_pL = new float[m_nEckenCount + 1];
	m_pEckenDone = new bool[m_nEckenCount + 1];
	m_vcPaths = new vector<Edge>[m_nEckenCount + 1];
	memset(m_pL, 0, (m_nEckenCount + 1) * sizeof(unsigned));
	memset(m_pEckenDone, false, (m_nEckenCount + 1) * sizeof(bool));
	m_vcKantenDone.clear();

	if (m_pL == NULL || nStartEcke >= m_nEckenCount || nStartEcke < 0)
		return false;

	m_nStartEcke = nStartEcke;
	m_pEckenDone[nStartEcke] = true;
	for (int i = 0; i < m_nEckenCount; i++)
		m_vcPaths[i].clear();

	for (int i = 0; i < m_nEckenCount; i++)
	{
		float nWeightMin = (float)((unsigned)-1);
		int nEckeMin = -1;
		Edge kDone;
		vector<Edge> vcPath;

		for (auto it = vcEdges.begin(); it != vcEdges.end(); it++)
		{
			Edge k = mpDelta[*it];
			if (m_pEckenDone[k.nVFrom] && !m_pEckenDone[k.nVTo])
			{
				// if (m_pL[k.nVFrom] + k.weight < nWeightMin)
				if (m_pL[k.nVFrom] + 1 < nWeightMin)
				{
					nWeightMin = m_pL[k.nVFrom] + 1; // k.weight;
					nEckeMin = k.nVTo;
					kDone = k;

					// sPath = m_vcPaths[k.from] + ": " + std::to_string(k.from) + " " + std::to_string(k.to) + ", ";
					vcPath.assign(m_vcPaths[k.nVFrom].begin(), m_vcPaths[k.nVFrom].end());
					vcPath.push_back(k);
				}
			}
			else if (m_pEckenDone[k.nVTo] && !m_pEckenDone[k.nVFrom])
			{
				// if (m_pL[k.to] + k.weight < nWeightMin)
				if (m_pL[k.nVFrom] + 1 < nWeightMin)
				{
					nWeightMin = m_pL[k.nVTo] + 1; // k.weight;
					nEckeMin = k.nVTo;
					kDone = k;

					// sPath = m_vcPaths[k.to] + ": " + std::to_string(k.to) + " " + std::to_string(k.from) + ", ";
					vcPath.assign(m_vcPaths[k.nVTo].begin(), m_vcPaths[k.nVTo].end());
					vcPath.push_back(k);
				}
			}
		}

		if (nEckeMin != -1)
		{
			m_pEckenDone[nEckeMin] = true;
			m_pL[nEckeMin] = nWeightMin;
			m_vcPaths[nEckeMin] = vcPath;
			m_vcKantenDone.push_back(kDone);
		}
	}

	int b = 16;
	int d = (int)m_pL[b];

	// wege zwischenspeichern
	vector<Edge> vcPath = m_vcPaths[b];

	return true;
}
