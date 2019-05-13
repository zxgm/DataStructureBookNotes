#include "Chapter04/Migong.h"
#include "Chapter04/Stack.h"

Cell g_laby[LABY_MAX][LABY_MAX];

ESWN nextESWN(ESWN eswn)
{
	return static_cast<ESWN>(eswn + 1);
}

Cell* nextCell(Cell *cell)
{
	assert(cell);

	switch (cell->m_outing)
	{
	case EAST:
		return cell + 1;
		break;
	case SOUTH:
		return cell - LABY_MAX;
		break;
	case WEST:
		return cell - 1;
		break;
	case NORTH:
		return cell + LABY_MAX;
		break;
	default:
		break;
	}
}

Cell* gotoNextCell(Cell *cell)
{
	assert(cell);
	Cell *next = nextCell(cell);
	next->m_incoming = cell->m_outing;

	return next;
}

bool labyrinth(Cell baby[LABY_MAX][LABY_MAX], Cell *startCell, Cell *endCell)
{
	startCell->m_incoming = UNKNOWN;
	startCell->m_status = ROUTE;
	Stack<Cell*> s;
	s.push(startCell);

	while (s.size())
	{
		Cell *cell = s.top();
		if (cell == endCell)
			return true;

		//typedef enum{ UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN;
		while ((cell->m_outing=nextESWN(cell->m_outing)) < NO_WAY)
		{
			if (nextCell(cell)->m_status == AVAILABLE)
				break;
		}

		if (cell->m_outing >= NO_WAY)
		{
			cell->m_status = BACKTRACKED;
			cell = s.pop();
		}
		else
		{
			s.push(cell = gotoNextCell(cell));
			cell->m_outing = UNKNOWN;
			cell->m_status = ROUTE;
		}
	}

	return false;
}