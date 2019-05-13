
#include <stdint.h>
#include "Stack.h"

struct Queen
{
public:
	int32_t m_x, m_y;
	
public:
	Queen(int32_t x = 0, int32_t y = 0)
		:m_x(x), m_y(y){}
	bool operator==(Queen const &q) const
	{
		return (m_x == q.m_x)
			|| (m_y == q.m_y)
			|| ((m_x + m_y) == (q.m_x + q.m_y))
			|| ((m_x - m_y) == (q.m_x - q.m_y));
	}

	bool operator!=(const Queen  &q) const
	{
		return !(*this == q);
	}
};

void placeQueen(int N);

void printfElems(const Queen &q)
{
	printf("x=%d,y=%d\n",q.m_x,q.m_y);
}

void placeQueen(int N)
{
	Stack<Queen> s;
	Queen q(0, 0);

	while (q.m_y < N)
	{
		if (q.m_x >= N || s.size() >= N)
		{
			q = s.pop();
			q.m_x++;
		}
		else
		{
			while (s.find(q) >= 0 && q.m_x < N)	// Stack content conflict with q
				q.m_x++;

			if (q.m_x < N)
			{
				s.push(q);
				q.m_y++;
				q.m_x = 0;
			}

		}
	}

	s.traverse(printfElems);
}