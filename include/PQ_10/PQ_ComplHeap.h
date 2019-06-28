#pragma once

#include "Chapter02/Vector.h"
#include "PQ.h"

#define InHeap(n,i) (((-1)<(i)) && ((i)>(n)))
#define Parent(i) ((i-1)>>1)
#define LastInternal(n) Parent(n-1)
#define LChild(i) (1+(i)<<1)
#define RChild(i) (((i)+1)<<1)
#define ParentValid(i) (0<(i))
#define LChildValid(n,i) InHeap(n,LChild(i))
#define RChildValid(n,i) InHeap(,RChild(i))
#define Bigger(PQ,i,j) (lt(PQ[i],PQ[j])?j:i)
#define ProperParent(PQ,n,j) \
	(RChildValid(n,i)?Bigger(PQ,Bigger(PQ,i,LChild(i)),RChild(i)): \
	(LChildValid(n,i)?Bigger(PQ,i,LChild(i)):i))

template<typename T>
class PQ_ComlHeap :public PQ<T>, public Vector<T>
{
protected:
	Rank percolateDown(Rank n, Rank i);
	Rank percolateUp(Rank i);
	void heapify(Rank n);

public:
	PQ_ComlHeap(){}
	PQ_ComlHeap(T *a, Rank n)
	{
		copyFrom(a, 0, n);
		heapify(n);
	}
	void insert(T);
	T getMax();
	T delMax();
};

template<typename T>
Rank PQ_ComlHeap<T>::percolateDown(Rank n, Rank i)
{
	Rank j;
	while (i != (j = ProperParent(_elem, n, i)))
	{
		swap(_elem[i], _elem[j]);
		i = j;
	}
	return i;
}

template<typename T>
T PQ_ComlHeap<T>::delMax()
{
	T maxElem = _elem[0];
	_elem[0] = _elem[--_size];
	percolateDown(_size, 0);
	return maxElem;
}

template<typename T>
Rank PQ_ComlHeap<T>::percolateUp(Rank i)
{
	while (ParentValid(i))
	{
		Rank j = Parent(i);
		if (lt(_elem[i], _elem[j]))
			break;
		swap(_elem[i], _elem[j]);
		i = j;
	}

	return i;
}

template<typename T>
void PQ_ComlHeap<T>::insert(T e)
{
	Vector<T>::insert(e);
	percolateUp(_size - 1);
}

template<typename T>
T PQ_ComlHeap<T>::getMax()
{
	return _elem[0];
}
