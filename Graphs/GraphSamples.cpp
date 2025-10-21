#include "Graph.h"

void Graph::InitGraph()
{
	enum
	{
		UNGARIAN_ALG_S,

	} 
	GraphSamples;

	/*
	int V[6] = { 1, 2, 3, 4, 5, 6 };
	int E[6] = { 12, 14, 23, 36, 45, 56 };

	AddVertices(V, 6);
	AddEdges(E, 6);

	// kanten
	mpDelta = {
		{12, Edge(1, 2, 3) },
		{14, Edge(1, 4, 7) },
		{23, Edge(2, 3, 3) },
		{36, Edge(3, 6, 4) },
		{45, Edge(4, 5, 5) },
		{56, Edge(5, 6, 3) },
		{34, Edge(3, 4, 3) },
		{24, Edge(2, 5, 3) },
		{16, Edge(1, 6, 3) }
	};
	*/

	// ungarische alg.
	/*
	int V[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int E[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	AddVertices(V, 16);
	AddEdges(E, 16);

	// kanten
	mpDelta = {
		{1, Edge(1, 2, 0) },
		{2, Edge(2, 3, 0) },
		{3, Edge(3, 4, 0) },
		{4, Edge(4, 5, 0) },
		{5, Edge(5, 6, 0) },
		{6, Edge(6, 15, 0) },
		{7, Edge(2, 7, 0) },
		{8, Edge(3, 8, 0) },
		{9, Edge(5, 9, 0) },
		{10, Edge(1, 10, 0) },
		{11, Edge(2, 11, 0) },
		{12, Edge(3, 12, 0) },
		{13, Edge(11, 12, 0) },
		{14, Edge(12, 13, 0) },
		{15, Edge(13, 14, 0) },
		{16, Edge(13, 16, 0) }
	};

	// beispiele seite 118
	// euler
	int V[6] = { 1, 2, 3, 4, 5, 6 };
	int E[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	AddVertices(V, 6);
	AddEdges(E, 10);

	// kanten
	mpDelta = {
		{1, Edge(1, 2, 0) },
		{2, Edge(2, 3, 0) },
		{3, Edge(3, 4, 0) },
		{4, Edge(4, 5, 0) },
		{5, Edge(5, 6, 0) },
		{6, Edge(6, 1, 0) },
		{7, Edge(6, 2, 0) },
		{8, Edge(6, 3, 0) },
		{9, Edge(5, 2, 0) },
		{10, Edge(5, 3, 0) }
	};

	// euler, no eulerian
	int V[5] = { 1, 2, 3, 5, 6 };
	int E[8] = { 1, 2, 5, 6, 7, 8, 9, 10 };

	AddVertices(V, 5);
	AddEdges(E, 8);

	// kanten
	mpDelta = {
		{1, Edge(1, 2, 0) },
		{2, Edge(2, 3, 0) },
		{5, Edge(5, 6, 0) },
		{6, Edge(6, 1, 0) },
		{7, Edge(6, 2, 0) },
		{8, Edge(6, 3, 0) },
		{9, Edge(5, 2, 0) },
		{10, Edge(5, 3, 0) }
	};
	*/

	// eulerian II
	/*
	int V[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int E[13] = { 12, 23, 38, 84, 45, 56, 61, 17, 15, 57, 47, 37, 34 };

	AddVertices(V, 8);
	AddEdges(E, 13);

	// kanten
	m_mpDelta = {
		{12, Edge(1, 2, 0) },
		{23, Edge(2, 3, 0) },
		{38, Edge(3, 8, 0) },
		{84, Edge(8, 4, 0) },
		{45, Edge(4, 5, 0) },
		{56, Edge(5, 6, 0) },
		{61, Edge(6, 1, 0) },
		{17, Edge(1, 7, 0) },
		{15, Edge(1, 5, 0) },
		{57, Edge(5, 7, 0) },
		{47, Edge(4, 7, 0) },
		{37, Edge(3, 7, 0) },
		{34, Edge(3, 4, 0) }
	};
	*/

	// hamilton, page 151
	int V[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int E[16] = { 12, 16, 13, 14, 24, 25, 75, 78, 63, 68, 34, 45, 58, 38, 27, 67 };

	AddVertices(V, 8);
	AddEdges(E, 16);

	m_mpDelta = {
		{13, Edge(1, 3, 0) },
		{14, Edge(1, 4, 0) },
		{24, Edge(2, 4, 0) },
		{25, Edge(2, 5, 0) },
		{75, Edge(7, 5, 0) },
		{78, Edge(7, 8, 0) },
		{63, Edge(6, 3, 0) },
		{68, Edge(6, 8, 0) },
		{34, Edge(3, 4, 0) },
		{45, Edge(4, 5, 0) },
		{58, Edge(5, 8, 0) },
		{38, Edge(3, 8, 0) },
		{12, Edge(1, 2, 0) },
		{16, Edge(1, 6, 0) },
		{27, Edge(2, 7, 0) },
		{67, Edge(6, 7, 0) }
	};

	// hamilton, page 147
	/*
	int V[5] = { 1, 2, 3, 4, 5 };
	int E[7] = { 12, 14, 23, 24, 34, 25, 35 };

	AddVertices(V, 5);
	AddEdges(E, 7);

	m_mpDelta = {
		{12, Edge(1, 2, 0) },
		{14, Edge(1, 4, 0) },
		{23, Edge(2, 3, 0) },
		{24, Edge(2, 4, 0) },
		{34, Edge(3, 4, 0) },
		{25, Edge(2, 5, 0) },
		{35, Edge(3, 5, 0) }
	};
	*/
}