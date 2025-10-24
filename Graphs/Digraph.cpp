#include "Digraph.h"

using namespace std;

void Digraph::Init1()
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
	*/
}

bool Digraph::DoMaxFlowMinCut()
{
	Init();

	nQ = 1;
	nS = 7;

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

bool Digraph::EdmondsKarpAlg()
{
	Init();

	nQ = 1;
	nS = 5;

	struct VE
	{
		int v;
		int e;
	};

	int nMaxFlowMinCut = 0; // RESULT

	int nVCount = (int)m_vcVertices.size();

	// count
	for (int cnt = 0; cnt < 10000; cnt++)
	{
		std::map<int, std::vector<int>> mpPlusNeighbors;
		int nStartEcke = nQ;

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
						if (e.nVFrom == v) // || e.nVTo == v) // only from for digraphs!!!
							mpPlusNeighbors[v].push_back(ei);
					}
				}
			}
		}
		catch (exception& e)
		{
			string s = e.what();
			printf("%s\n", s.c_str());

			return false; // resTreeEdges;
		}

		queue<int> qEckenToDo;
		set<int> setEckenDone;

		qEckenToDo.emplace(nStartEcke);

		// notice the tree path
		map<int, VE> mpTrace;
		bool bSReached = false;

		while (!qEckenToDo.empty())
		{
			int nNextEcke = qEckenToDo.front();
			qEckenToDo.pop();

			for (auto itn = mpPlusNeighbors[nNextEcke].begin(); itn != mpPlusNeighbors[nNextEcke].end(); itn++)
			{
				int nNeighbourEdge = *itn;
				int nNeighbour = m_mpDelta[nNeighbourEdge].nVTo;
				if (setEckenDone.find(nNeighbour) == setEckenDone.end())
				{
					// resTreeEdges.push_back(nNeighbour);
					printf("***** %2d - %2d (%d) *********\n", nNextEcke, nNeighbour, nNeighbourEdge);
					mpTrace[nNeighbour] = { nNextEcke, nNeighbourEdge };

					if (nNeighbour == nS)
					{
						bSReached = true;
						break;
					}

					setEckenDone.insert(nNeighbour);
					qEckenToDo.emplace(nNeighbour);
				}
			}

			if (bSReached)
				break;

			setEckenDone.insert(nNextEcke);
		}

		if (bSReached)
		{
			// print out
			printf("\n");
			int v = nS;
			int minC = INT_MAX;

			// ******* find minimum capacity **********
			for (int i = 0; v != nQ && i < m_vcVertices.size(); i++) //  auto v : mpTrace)
			{
				if (mpTrace.find(v) != mpTrace.end())
				{
					int ei = mpTrace[v].e;
					if (m_mpDelta.find(ei) != m_mpDelta.end())
					{
						if (minC > m_mpDelta[ei].nC)
							minC = m_mpDelta[ei].nC;
						printf(" %d ", ei);					
					}

					v = mpTrace[v].v;
				}
			}
			printf("\n MIN C %d\n\n", minC);

			// ****** check min found ********
			if (minC > 0 && minC < INT_MAX)
			{
				v = nS;
				while (v != nQ)
				{
					if (m_mpDelta[mpTrace[v].e].nC == minC)
					{
						// revert edge!!! capacity remains the same
						int tmp = m_mpDelta[mpTrace[v].e].nVFrom;
						m_mpDelta[mpTrace[v].e].nVFrom = m_mpDelta[mpTrace[v].e].nVTo;
						m_mpDelta[mpTrace[v].e].nVTo = tmp;
					}
					else // m_mpDelta[mpTrace[v].e].nC > minC
					{
						m_mpDelta[mpTrace[v].e].nC = m_mpDelta[mpTrace[v].e].nC - minC;
					}

					// next vertex
					v = mpTrace[v].v;
				}

				// notice in result!
				nMaxFlowMinCut += minC;
			}
		}

		// cnt < 3

		// ende?
		if (!bSReached)
		{
			printf("\nENDE!!!!\n");
			break;
		}

	}

	// result output
	printf("RESULT: %d\n", nMaxFlowMinCut);

	return true; // resTreeEdges;
}
