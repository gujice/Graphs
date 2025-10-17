#include "Digraph.h"

int main()
{
	/*
	Digraph d;
	d.DoMaxFlowMinCut();
	*/

	Graph graph;
	graph.Init();

	graph.CreateTreeByBreadthFirst(1);
	graph.CreateWaysByDijkstra(1);

	return 0;
}
