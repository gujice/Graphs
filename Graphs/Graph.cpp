#include "Graph.h"

using namespace std;

void Graph::AddVertices(int* pVerts, int count)
{
	for (int i = 0; i < count; i++)
	{
		m_vcVertices.push_back(pVerts[i]);
	}
}

void Graph::AddEdges(int* pEdges, int count)
{
	for (int i = 0; i < count; i++)
	{
		m_vcEdges.push_back(pEdges[i]);
	}
}

void Graph::Init()
{
	InitGraph();
}

bool Graph::IsBipartit()
{
	enum eSet { NO, V1, V2 } eV = NO;
	std::set<int> setV1;
	std::set<int> setV2;

	for (auto itv = m_vcVertices.begin(); itv != m_vcVertices.end(); itv++)
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

		for (auto e : m_mpDelta)
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
	if (m_vcVertices.size() != (setV1.size() + setV2.size()))
	{
		printf("Graph is NOT bipartit! (different count of elements %d <-> %d)\n", (int)m_vcVertices.size(), (int)(setV1.size() + setV2.size()));
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
	int nVCount = (int)m_vcVertices.size();
	std::map<int, std::vector<int>> mpPlusNeighbors;

	try
	{
		for (auto itv = m_vcVertices.begin(); itv != m_vcVertices.end(); itv++)
		{
			int v = *itv;
			for (auto ite = m_vcEdges.begin(); ite != m_vcEdges.end(); ite++)
			{
				int ei = *ite;

				// must exists
				auto fe = m_mpDelta.find(ei);
				if (fe != m_mpDelta.end())
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
			int nNeighbour = m_mpDelta[nNeighbourEdge].nVTo;
			if (nNeighbour == nNextEcke)
				nNeighbour = m_mpDelta[nNeighbourEdge].nVFrom;
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
	int m_nEckenCount = (int)m_vcVertices.size();
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

		for (auto it = m_vcEdges.begin(); it != m_vcEdges.end(); it++)
		{
			Edge k = m_mpDelta[*it];
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

void Graph::BuildNeighborsMap()
{
	mpNeighbors.clear();
	mpCoveredEdgesByV.clear();

	for (auto itv = m_vcVertices.begin(); itv != m_vcVertices.end(); itv++)
	{
		int v = *itv;
		for (auto ite = m_vcEdges.begin(); ite != m_vcEdges.end(); ite++)
		{
			int ei = *ite;

			// must exists
			auto fe = m_mpDelta.find(ei);
			if (fe != m_mpDelta.end())
			{
				Edge& e = fe->second;
				if (e.nVFrom == v || e.nVTo == v) // here the only one difference with digraph!!!
				{
					mpCoveredEdgesByV[v].push_back(ei);
					mpNeighbors[v].push_back(e.GetOtherV(v));
				}
			}
		}
	}
}
