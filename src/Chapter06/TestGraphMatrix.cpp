#include <stdio.h>
#include "Chapter06/GraphMatrix.h"

#include <stdint.h>

// Test multiple vector assign.
#if defined(TEST_MUL_VEC)
#include <vector>
using std::vector;

vector<vector<int> > g_testVector;
int n;

void P()
{
	printf("包含%d个vector\n", g_testVector.size());
	for (int32_t i = 0; i < g_testVector.size(); i++)
	{
		vector<int>& tmp = g_testVector.at(i);
		printf("第%d个vector元素个数:%d.值:",i,tmp.size());
		for (int32_t j = 0; j < tmp.size(); j++)
			printf("%d ",tmp.at(j));
		printf("\n");
	}

	printf("\n---------------------------\n");
}

void insert(const int& vertex)
{
	for (int j = 0; j < n; j++)
		g_testVector[j].push_back(-1);
	n++;
	g_testVector.push_back(vector<int>(n, -1));
}
#endif

int main(int argc, char *argv[])
{
#if defined(TEST_MUL_VEC)
	for (int i = 0; i < 5; i++)
	{
		P();
		insert(i);
	}
	P();
#endif

	GraphMatrix<int,int> gm;
	for (int i = 0; i < 4;i++)
		gm.insert(i);

	gm.remove(3);
	getchar();
	return 0;
}
