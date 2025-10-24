#include "Digraph.h"

int main()
{
	Digraph d;
	// d.DoMaxFlowMinCut();
	d.EdmondsKarpAlg();

	return 0;

	Graph graph;
	graph.Init();

	// graph.CreateTreeByBreadthFirst(1);
	// graph.CreateWaysByDijkstra(1);

	graph.IsEulerian();
	graph.FindEulertour();

	graph.CheckKorollarORE();
	graph.CheckKorollarDIRAC();
	graph.CheckTheoremCHVATAL();
	graph.DoHamiltonAlg();

	return 0;
}
