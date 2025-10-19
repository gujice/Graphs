#include "Graph.h"

bool Graph::IsEulerian()
{
	bool bResult = true;

	BuildNeighborsMap();

	for (auto it : mpCoveredEdgesByV)
	{
		if (it.second.size() % 2 != 0)
		{
			printf("Ecke %d, Grad %d\n", it.first, it.second.size());
			bResult = false;
			break;
		}
	}

	if (bResult)
		printf("\nGraph ist eulerisch!\n");
	else
		printf("\nGraph ist NICHT eulerisch!\n");

	return bResult;
}

std::vector<int> Graph::FindEulertour()
{
	struct EdgeTrace
	{
		int from1 = -1;
		int from2 = -1;

		bool Full() { return from1 != -1 && from2 != -1; }
	};

	std::vector<int> vcTour;
	int v = m_vcVertices[0];
	int cnt = 0;
	std::map<int, EdgeTrace> mpEdgesUsedFlag;

	while (cnt <= 2 * m_vcVertices.size())
	{
		bool bFoundNext = false;
		int next_ei = -1;

		for (auto ei : mpCoveredEdgesByV[v])
		{
			Edge& e = m_mpDelta[ei];

			auto itUsed = mpEdgesUsedFlag.find(ei);
			if (itUsed == mpEdgesUsedFlag.end())
			{
				int next_v = e.GetOtherV(v);
				mpEdgesUsedFlag[ei] = {v, -1};
				vcTour.push_back(ei);

				v = next_v;
				bFoundNext = true;
				break;
			}
			else if (mpEdgesUsedFlag[ei].from1 != v && mpEdgesUsedFlag[ei].from2 != v)
			{
				next_ei = ei;
			}
		}

		if (!bFoundNext)
		{
			int ei = (next_ei == -1) ? vcTour[vcTour.size() - 1] : next_ei;;
			if (mpEdgesUsedFlag[ei].Full())
			{
				// ende!
				break;
			}
			Edge& e = m_mpDelta[ei];
			mpEdgesUsedFlag[ei].from2 = v;
			v = e.GetOtherV(v);
			vcTour.push_back(ei);
		}
	}

	printf("\n");
	for (auto ei : vcTour)
		printf("%d ", ei);
	printf("\n");

	return vcTour;
}