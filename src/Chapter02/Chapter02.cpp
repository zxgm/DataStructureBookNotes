#include <stdio.h>
#include "Chapter02\Vector.h"
#include "Chapter02\FibUtil.h"

void Traverse(int64_t i)
{
	printf("%d\t",i);
}

int main(int argc, char *argv[])
{
	FibUtil fib(22);
	fib.traverse(Traverse);

	/*Vector<int> myVec;
	myVec.insert(2);
	myVec.insert(2);
	myVec.insert(2);
	myVec.insert(2);
	myVec.insert(4);
	myVec.insert(4);
	myVec.insert(5);
	myVec.insert(7);
	myVec.insert(7);
	myVec.insert(9);
	myVec.insert(10);
	myVec.insert(11);
	myVec.insert(11);

	myVec.uniquify();
	Rank r = myVec.search(8);*/
	//myVec.deduplicate();

	getchar();
	return 0;
}
