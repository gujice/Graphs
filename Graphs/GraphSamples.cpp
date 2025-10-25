#include "Graph.h"

void Graph::InitGraph()
{
	enum
	{
		SAMPLE_1,
		UNGARIAN_ALG_S,
		EULER_side_118,
		EULER_no_euler,
		EULERIAN_II,
		HAMILTON_page_151,
		HAMILTON_page_147,
		FORD_FULCERSON_youtube, // https://www.youtube.com/watch?v=hEHooOdsNdk
		FORD_FULCERSON_youtube2, // https://www.youtube.com/watch?v=ZKEi6zf0O9g&t=112s
		Edmonds_Karp_WIKI, // https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm
		Edmonds_Karp_WIKI2, // https://de.wikipedia.org/wiki/Algorithmus_von_Ford_und_Fulkerson
		Edmonds_Karp_WIKI3,
		Edmons_Karp_side242, // example, more steps
		BIPARTIT_4X4 
	} 
	GraphSamples = UNGARIAN_ALG_S;

	switch (GraphSamples)
	{
		/********                 **********/
		case SAMPLE_1:
		{
			int V[] = { 1, 2, 3, 4, 5, 6 };
			int E[] = { 12, 14, 23, 36, 45, 56 };

			AddVertices(V, sizeof(V)/sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));

			// kanten
			m_mpDelta = {
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
		}
		break;

		/********  UNGARIAN_ALG_S  **********/
		case UNGARIAN_ALG_S:
		{
			int V[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			int E[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

			AddVertices(V, sizeof(V)/sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));

			// kanten
			m_mpDelta = {
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
		}
		break;

		/********  EULER_SIDE_118  **********/
		case EULER_side_118:
		{
			// beispiele seite 118
			// euler
			int V[6] = { 1, 2, 3, 4, 5, 6 };
			int E[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

			AddVertices(V, 6);
			AddEdges(E, 10);

			// kanten
			m_mpDelta = {
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
		}
		break;

		/********  EULER_NO_EULER  **********/
		case EULER_no_euler:
		{

			// euler, no eulerian
			int V[5] = { 1, 2, 3, 5, 6 };
			int E[8] = { 1, 2, 5, 6, 7, 8, 9, 10 };

			AddVertices(V, 5);
			AddEdges(E, 8);

			// kanten
			m_mpDelta = {
				{1, Edge(1, 2, 0) },
				{2, Edge(2, 3, 0) },
				{5, Edge(5, 6, 0) },
				{6, Edge(6, 1, 0) },
				{7, Edge(6, 2, 0) },
				{8, Edge(6, 3, 0) },
				{9, Edge(5, 2, 0) },
				{10, Edge(5, 3, 0) }
			};
		}
		break;
		/********  EULERIAN_II  **********/
		case EULERIAN_II :
		{
			// eulerian II
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
		}
		break;
		/********  HAMILTON_PAGE_151  **********/
		case HAMILTON_page_151:
		{
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
		}
		break;
		/********  HAMILTON_PAGE_147  **********/
		case HAMILTON_page_147:
		{
			// hamilton, page 147
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
		}
		break;
		// example from internet (youtube: FORD_FULCERSON_youtube: https://www.youtube.com/watch?v=hEHooOdsNdk)
		case FORD_FULCERSON_youtube:
		{
			int V[] = { 1, 2, 3, 4, 5, 6 };
			int E[] = { 12, 23, 34, 54, 65, 16, 62, 25, 35 };

			AddVertices(V, sizeof(V) / sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));

			m_mpDelta = {
				{12, Edge(1, 2, 5) },
				{23, Edge(2, 3, 4) },
				{34, Edge(3, 4, 4) },
				{54, Edge(5, 4, 12) },
				{35, Edge(3, 5, 6) },
				{25, Edge(2, 5, 5) },
				{65, Edge(6, 5, 5) },
				{16, Edge(1, 6, 10) },
				{62, Edge(6, 2, 6) }
			};
		}
		break;
		// example from internet (youtube: FORD_FULCERSON_youtube: https://www.youtube.com/watch?v=ZKEi6zf0O9g&t=112s)
		case FORD_FULCERSON_youtube2:
		{
			int V[] = { 1, 2, 3, 4, 5, 6 };
			int E[] = { 12, 23, 34, 54, 65, 16, 62, 36, 53 };

			AddVertices(V, sizeof(V) / sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));

			m_mpDelta = {
				{12, Edge(1, 2, 15) },
				{23, Edge(2, 3, 11) },
				{34, Edge(3, 4, 20) },
				{54, Edge(5, 4, 6) },
				{53, Edge(5, 3, 8) },
				{36, Edge(3, 6, 8) },
				{65, Edge(6, 5, 14) },
				{16, Edge(1, 6, 13) },
				{62, Edge(6, 2, 4) }
			};
		}
		break;
		// example from internet (WIKIPEDIA)
		case Edmonds_Karp_WIKI:
		{
			int V[] = { 1, 2, 3, 4, 5, 6, 7 };
			int E[] = { 12, 14, 31, 35, 23, 34, 52, 45, 46, 67, 57 };

			AddVertices(V, sizeof(V) / sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));

			m_mpDelta = {
				{12, Edge(1, 2, 3) },
				{14, Edge(1, 4, 3) },
				{31, Edge(3, 1, 3) },
				{35, Edge(3, 5, 2) },
				{23, Edge(2, 3, 4) },
				{34, Edge(3, 4, 1) },
				{52, Edge(5, 2, 1) },
				{45, Edge(4, 5, 2) },
				{46, Edge(4, 6, 6) },
				{67, Edge(6, 7, 9) },
				{57, Edge(5, 7, 1) }
			};
		}
		break;
		// example from internet (WIKIPEDIA)
		case Edmonds_Karp_WIKI2:
		{
			int V[] = { 1, 2, 3, 4 };
			int E[] = { 12, 23, 24, 14, 43 };

			AddVertices(V, sizeof(V) / sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));

			m_mpDelta = {
				{12, Edge(1, 2, 4) },
				{23, Edge(2, 3, 1) },
				{24, Edge(2, 4, 3) },
				{14, Edge(1, 4, 2) },
				{43, Edge(4, 3, 6) }
			};
		}
		break;
		// example from internet (WIKIPEDIA) https://sr.wikipedia.org/wiki/%D0%A4%D0%BE%D1%80%D0%B4-%D0%A4%D1%83%D0%BB%D0%BA%D0%B5%D1%80%D1%81%D0%BE%D0%BD%D0%BE%D0%B2_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%B0%D0%BC
		case Edmonds_Karp_WIKI3:
		{
			int V[] = { 1, 2, 3, 4, 5 };
			int E[] = { 12, 23, 14, 43, 45, 35 };

			AddVertices(V, sizeof(V) / sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));
			SetQandS(1, 5);

			m_mpDelta = {
				{12, Edge(1, 2, 7) },
				{14, Edge(1, 4, 6) },
				{23, Edge(2, 3, 3) },
				{43, Edge(4, 3, 2) },
				{35, Edge(3, 5, 5) },
				{45, Edge(4, 5, 2) }
			};
		}
		break;
		// side 242
		case Edmons_Karp_side242:
		{
			enum {c = 10};
			int V[] = { 1, 2, 3, 4 };
			int E[] = { 12, 23, 43, 14, 24 };

			AddVertices(V, sizeof(V) / sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));
			SetQandS(1, 3);

			m_mpDelta = {
				{12, Edge(1, 2, c) },
				{43, Edge(4, 3, c) },
				{23, Edge(2, 3, c) },
				{14, Edge(1, 4, c) },
				{24, Edge(2, 4, 1) }
			};
		}
		break;
		// bipartit 4 x 4
		case BIPARTIT_4X4:
		{
			int V[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
			int E[] = { 15, 16, 17, 18, 25, 26, 27, 28, 35, 36, 37, 38, 45, 46, 47, 48 };

			AddVertices(V, sizeof(V) / sizeof(V[0]));
			AddEdges(E, sizeof(E) / sizeof(E[0]));

			m_mpDelta = {
				{15, Edge(1, 5, 1) },
				{16, Edge(1, 6, 1) },
				{17, Edge(1, 7, 1) },
				{18, Edge(1, 8, 1) },
				{25, Edge(2, 5, 1) },
				{26, Edge(2, 6, 1) },
				{27, Edge(2, 7, 1) },
				{28, Edge(2, 8, 1) },
				{35, Edge(3, 5, 1) },
				{36, Edge(3, 6, 1) },
				{37, Edge(3, 7, 1) },
				{38, Edge(3, 8, 1) },
				{45, Edge(4, 5, 1) },
				{46, Edge(4, 6, 1) },
				{47, Edge(4, 7, 1) },
				{48, Edge(4, 8, 1) }
			};
		}
		break;
	}
}