#include "Digraph.h"


void Digraph::Init()
{
	/*
	int V[6] = { 0, 1, 2, 3, 4, 5 };
	int E[9] = { 1, 2, 13, 14, 21, 24, 34, 35, 45 };

	d.AddVertices(V, 6);
	d.AddEdges(E, 9);

	// quelle, senke
	d.nQ = 0;
	d.nS = 5;

	// kanten
	d.mpDelta = {
		{1, Edge(0, 1, 3) },
		{2, Edge(0, 2, 7) },
		{13, Edge(1, 3, 3) },
		{14, Edge(1, 4, 4) },
		{21, Edge(2, 1, 5) },
		{24, Edge(2, 4, 3) },
		{34, Edge(3, 4, 3) },
		{35, Edge(3, 5, 2) },
		{45, Edge(4, 5, 6) }
	};
	*/

	/*
	int V[4] = { 0, 1, 2, 3 };
	int E[5] = { 1, 2, 12, 13, 23 };

	d.AddVertices(V, 4);
	d.AddEdges(E, 5);

	// quelle, senke
	d.nQ = 0;
	d.nS = 3;

	// kanten
	d.mpDelta = {
		{1, Edge(0, 1, 13) },
		{2, Edge(0, 2, 13) },
		{12, Edge(1, 2, 1) },
		{13, Edge(1, 3, 13) },
		{23, Edge(2, 3, 13) }
	};
	*/

#define tri 30
#define jedan 10
#define korendva 14

	int V[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int E[15] = { 1, 4, 5, 51, 14, 45, 23, 36, 67, 27, 62, 37, 12, 34, 56 };

	AddVertices(V, 8);
	AddEdges(E, 15);

	// quelle, senke
	nQ = 0;
	nS = 7;

	// kanten
	m_mpDelta = {
		{1, Edge(0, 1, tri) },
		{4, Edge(0, 4, tri) },
		{5, Edge(0, 5, tri) },
		{51, Edge(5, 1, tri) },
		{14, Edge(1, 4, tri) },
		{45, Edge(4, 5, tri) },
		{23, Edge(2, 3, tri) },
		{36, Edge(3, 6, tri) },
		{67, Edge(6, 7, tri) },
		{27, Edge(2, 7, tri) },
		{62, Edge(6, 2, tri) },
		{37, Edge(3, 7, tri) },
		{12, Edge(1, 2, jedan) },
		{34, Edge(3, 4, tri) },
		{56, Edge(5, 6, korendva) }
	};

}

bool Digraph::DoMaxFlowMinCut()
{
	Init();

	std::set<int> setVVisited;
	int v = nQ;
	int prevV = nQ;
	bool bSReached = false;
	bool bNoNext = false;
	int c = INT_MAX;
	int nFlow = 0;

	for (int i = 0; i < 6; i++)
	{
		// init area
		std::vector<int> vcW;
		std::set<int> setVVisited = {nQ};
		bSReached = false;
		bNoNext = false;
		v = nQ;
		c = INT_MAX;

		printf("%d\n", v);

		// create neightbours list
		BuildPlusNeighborsMap();

		while (!bSReached && !bNoNext)
		{
			if (mpPlusNeighbors.find(v) != mpPlusNeighbors.end())
			{
				bool bFoundNext = false;
				for (auto it = mpPlusNeighbors[v].begin(); it != mpPlusNeighbors[v].end(); it++)
				{
					int ei = *it;
					Edge& e = m_mpDelta[ei];

					// check already visited
					if (setVVisited.find(e.nVTo) == setVVisited.end() && (e.nC > e.nF))
					{
						if (e.nVTo == nS)
						{
							bSReached = true;
						}

						// capacity 
						if (e.nC < c)
							c = e.nC;

						// next vertix
						prevV = v;
						v = e.nVTo;
						vcW.push_back(ei);
						bFoundNext = true;

						// visited!
						setVVisited.insert(e.nVTo);

						printf("%d\n", v);
						break;
					}
				}

				if (!bFoundNext)
				{
					// setVVisited.insert(v);
					if (v == prevV) // break!!!
					{
						c = 0;
						bNoNext = true;
					}
					else
						v = prevV;
				}
			}
			else
			{
				c = 0;
				bNoNext = true;
			}
		}

		printf("\nCapacity %d\n", c);
		if (c > 0)
		{
			for (auto& ei : vcW)
			{
				printf("%d-%d ", m_mpDelta[ei].nVFrom, m_mpDelta[ei].nVTo);

				if (m_mpDelta[ei].nC - c > 0)
				{
					m_mpDelta[ei].nC = m_mpDelta[ei].nC - c;
				}
				else
				{
					m_mpDelta[ei].nC = c;

					int fromto = m_mpDelta[ei].nVFrom;
					m_mpDelta[ei].nVFrom = m_mpDelta[ei].nVTo;
					m_mpDelta[ei].nVTo = fromto;
				}
			}
		}

		// count FLOW
		nFlow += c;
	}

	// RESULT
	printf("Flow is: %d\n", nFlow);

	return true;
}

void Digraph::BuildPlusNeighborsMap()
{
	mpPlusNeighbors.clear();

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
				if (e.nVFrom == v)
				{
					// mpPlusNeighbors[v].push_back(e.nVTo);
					mpPlusNeighbors[v].push_back(ei);
				}
			}
		}
	}
}
