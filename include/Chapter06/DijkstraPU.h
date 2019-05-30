/* Shortest path header file. */
#pragma once
#ifndef _DIJKSTRAPU_H
#define _DIJKSTRAPU_H

template<typename Tv,typename Te>
struct DijkstraPU
{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
	{
		if (g->status(v) == UNDISCOVERED)
		{
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v))
			{
				g->priority(v) = g->priority(uk) + g->weight(uk, v);
				g->parent(v) = uk;
			}
		}
	}
};
#endif