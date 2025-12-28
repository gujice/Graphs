#include "Digraph.h"

int main()
{
	Graph graph;
	graph.Init();

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

	g.DoGreedyAlg();
	*/
	graph.DoHamiltonAlg();

	return 0;
}
