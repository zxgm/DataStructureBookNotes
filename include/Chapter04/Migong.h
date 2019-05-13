#ifndef _MIGONG_H
#define _MIGONG_H

#include <assert.h>
#include <stdio.h>

// Cell status
typedef enum{AVAILABLE,ROUTE,BACKTRACKED,WALL} CellStatus;
// direct
typedef enum{UNKNOWN,EAST,SOUTH,WEST,NORTH,NO_WAY} ESWN;

#define LABY_MAX 24
struct Cell
{
	int m_x, m_y;
	CellStatus m_status;
	ESWN m_incoming, m_outing;
};

// next direct
ESWN nextESWN(ESWN eswn);

Cell* nextCell(Cell *cell);
Cell* gotoNextCell(Cell *cell);
bool labyrinth(Cell baby[LABY_MAX][LABY_MAX], Cell *startCell, Cell *endCell);
#endif