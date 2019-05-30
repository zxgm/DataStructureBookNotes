/* Minimum spanning tree header file. */
#pragma once
#ifndef _PRIMPU_H
#define _PRIMPU_H

template<typename Tv,typename Te>
struct PrimPU
{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
	{
		if (g->status(v) == UNDISCOVERED)
		{
			if (g->priority(v) > g->weight(uk, v))
			{
				g->priority(v) = g->weight(uk, v);
				g->parent(v) = uk;
			}
		}
	}
};
#endif