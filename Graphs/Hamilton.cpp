#include "Graph.h"

int compare(const void* arg1, const void* arg2)
{
	return *((int*)arg1) < *((int*)arg2);
}

bool Graph::CheckKorollarORE()
{
	bool bRes = false;

	BuildNeighborsMap();

	int nVSize = (int)m_vcVertices.size();

	for (int i = 0; i < nVSize; i++)
	{
		int vi = m_vcVertices[i];
		for (int j = i + 1; j < nVSize; j++)
		{
			int vj = m_vcVertices[j];
			if (std::find(mpNeighbors[vi].begin(), mpNeighbors[vi].end(), vj) == mpNeighbors[vi].end())
			{
				int dsum = (int)(mpNeighbors[vi].size() + mpNeighbors[vj].size());
				if (dsum < nVSize)
				{
					printf("Ore not fulfilled (%d: %lld + %d: %lld < %d)\n", vi, mpNeighbors[vi].size(), vj, mpNeighbors[vj].size(), nVSize);
					bRes = false;
					return false;
				}
			}
		}
	}

	if (bRes)
		printf("ORE fulfilled!\n");

	return bRes;
}

bool Graph::CheckKorollarDIRAC()
{
	BuildNeighborsMap();

	int delta = INT_MAX;

	for (auto it : mpNeighbors)
	{
		if (it.second.size() < delta)
			delta = (int)it.second.size();
	}

	// info
	printf("minimaler Knotengrad (Minimalgrad): %d\n", delta);

	if (delta >= (m_vcVertices.size() / 2))
	{
		printf("Graph is according to Dirac hamiltonian!\n");
		return true;
	}
	else
	{
		printf("Dirac not fulfilled!\n");
		return false;
	}
}

bool Graph::CheckTheoremCHVATAL()
{
	bool bRes = true;
	int nCount = (int)m_vcVertices.size();
	int* pGradArr = new int[nCount];
	memset(pGradArr, 0, nCount * sizeof(int));

	BuildNeighborsMap();

	int i = 0;
	for (auto it : mpNeighbors)
	{
		pGradArr[i++] = (int)it.second.size();
	}

	// sort grad seq
	qsort((void*)pGradArr, (size_t)nCount, sizeof(int), compare);

	printf("\nGradfolge:");
	for (int i = 0; i < nCount; i++)
		printf("%d ", pGradArr[i]);
	printf("\n");

	// chvatal bedienung
	for (int i = 0; i < (nCount * 1.0/2); i++)
	{
		if (pGradArr[i] <= i)
		{
			bRes = false;
			printf("Chvatal not fulfilled! (%d > %d)\n", pGradArr[i], i);
			break;
		}
	}

	delete[] pGradArr;

	if (bRes)
		printf("Chvatal fulfilled!!!\n");

	return bRes;
}

bool Graph::DoHamiltonAlg()
{
	bool bRes = false;
	std::vector<int> vcPath;
	int nCount = (int)m_vcVertices.size();

	BuildNeighborsMap();

	// build paths
	int v = m_vcVertices[0];
	vcPath.push_back(v);

	for (int i = 0; i < nCount; i++)
	{
		bool bFoundNext = false;
		for (int j = 0; j < mpNeighbors[v].size(); j++)
		{
			int nextV = mpNeighbors[v][j];
			if (std::find(vcPath.begin(), vcPath.end(), nextV) == vcPath.end())
			{
				vcPath.push_back(nextV);
				v = nextV;
				bFoundNext = true;
				break;
			}
		}

		if (!bFoundNext)
		{
			if (vcPath.size() == nCount)
			{
				// check end -> begin
				int nFirst = vcPath.front();
				int nLast = vcPath.back();
				if (std::find(mpNeighbors[nLast].begin(), mpNeighbors[nLast].end(), nFirst) != mpNeighbors[nLast].end())
				{
					bRes = true;
					break;
				}
			}
		}
	}

	return bRes;
}
