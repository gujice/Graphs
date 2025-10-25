#include "Digraph.h"

int main()
{
	Graph g;
	g.Init();

	/*
	Digraph d;
	// d.DoMaxFlowMinCut();
	d.EdmondsKarpAlg();

	return 0;

	// graph.CreateTreeByBreadthFirst(1);
	// graph.CreateWaysByDijkstra(1);

	graph.IsEulerian();
	graph.FindEulertour();

	graph.CheckKorollarORE();
	graph.CheckKorollarDIRAC();
	graph.CheckTheoremCHVATAL();
	graph.DoHamiltonAlg();
	*/

	g.DoGreedyAlg();

	return 0;
}
