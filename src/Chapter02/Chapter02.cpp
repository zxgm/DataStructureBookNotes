#include <stdio.h>
#include "Chapter02\Vector.h"

int main(int argc, char *argv[])
{
	Vector<int> myVec;
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
	myVec.deduplicate();

	getchar();
	return 0;
}
