#include "Graph.h"

using namespace std;

void Graph::DoGreedyAlg()
{
	map<int, int> mpColors;
	int nextColor = 1;

	// build neighbours map
	BuildNeighborsMap();

	// loop vertices
	for (auto v : m_vcVertices)
	{
		int maxColor = 0;
		if (mpNeighbors.find(v) != mpNeighbors.end())
		{
			// find max used color
			for (auto nv : mpNeighbors[v])
			{
				if (mpColors.find(nv) != mpColors.end())
				{
					if (maxColor < mpColors[nv])
						maxColor = mpColors[nv];
				}
			}
		}

		if (maxColor > 0)
			mpColors[v] = maxColor + 1;
		else
			mpColors[v] = 1; // start color!
	}

	// result coloring
	printf("\n");
	for(auto it : mpColors)
		printf("%d = %d\n", it.first, it.second);
	printf("\n");
}