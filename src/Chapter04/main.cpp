#include <stdio.h>
//#include "../../include/Chapter04/Queen.h"
#include "Chapter04/Migong.h"

int main(int argc, char *argv[])
{
	Cell laby[LABY_MAX][LABY_MAX] = { {}, {} };
	Cell *startCell = laby[0];
	Cell *endCell = laby[0] + LABY_MAX;
	labyrinth(laby, startCell, endCell);

	//placeQueen(8);

	// binary convert
	/*Stack<char> s;
	convert(s, 178, 16);

	int size = s.size();
	while (size--)
		printf("%c", s.pop());*/

	getchar();
	return 0;
}