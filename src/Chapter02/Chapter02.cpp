#include <stdio.h>
#include "Chapter02\Vector.h"
#include "Chapter02\FibUtil.h"
#include <time.h>
#include <stdlib.h>

void Traverse(int64_t i)
{
	printf("%d\t",i);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	//FibUtil fib(22);
	//fib.traverse(Traverse);

	Vector<int> myVec;
	for (int32_t i = 0; i < 10; i++)
		myVec.insert(3);

	//myVec.uniquify();
	myVec.traverse(Traverse);
	Rank r = myVec.search(9);
	//myVec.deduplicate();

	getchar();
	return 0;
}
