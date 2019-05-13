#ifndef _QUEUE_H
#define _QUEUE_H

#include "Chapter03/List.h"

template<typename T>
class Queue
	:public List<T>
{
public:
	void enqueue(const T &t){ insertAsLast(t); }
	void dequeue(){ remove(first()); }
	T& front(){ return first()->data; }
};
#endif