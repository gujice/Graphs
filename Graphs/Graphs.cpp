#include "MaxFlowMinCut.h"

int main()
{
	Digraph d;

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

	d.DoMaxFlowMinCut();

	return 0;
}
