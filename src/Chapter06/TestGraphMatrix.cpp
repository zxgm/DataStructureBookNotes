#include <stdio.h>
#include "Chapter06/GraphMatrix.h"

int main(int argc, char *argv[])
{
	GraphMatrix<int,int> gm;
	for (int i = 0; i < 4;i++)
		gm.insert(1);
	
	gm.remove(3);
	getchar();
	return 0;
}
