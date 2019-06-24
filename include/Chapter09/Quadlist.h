#pragma once
#ifndef _QUADLIST_H
#define _QUADLIST_H

#include "QuadlistNode.h"

template<typename T> class Quadlist
{
private:
	int _size;
	QlistNodePos(T) header;
	QlistNodePos(T) trailer;

protected:
	void init();
	int clear();

public:
	Quadlist(){ init(); }
	~Quadlist(){ clear(); delete header; delete trailer; }

	Rank size() const{ return _size; }
	bool empty() const { return _size <= 0; }
	QlistNodePos(T) first() const{ return header->succ; }
	QlistNodePos(T) last() const { return trailer->pred; }
	bool valid(QlistNodePos(T) p)
	{
		return p && (trailer != p) && (header != p);
	}

	T remove(QlistNodePos(T) p);
	QlistNodePos(T) insertAfterAbove(const T &e, 
		QlistNodePos(T) p, QlistNodePos(T) b = NULL);

	void traverse(void(*)(T &));
	template<typename VST> void traverse(VST &);
};

template<typename T>
int Quadlist<T>::clear()
{
	int oldSize = _size;
	while (0<_size)
	{
		remove(header->succ);
	}

	return oldSize;
}

template<typename T>
T Quadlist<T>::remove(QlistNodePos(T) p)
{
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	_size--;
	T e = p->entry;
	delete p;
	return e;
}

template<typename T>
Quadlist<T>::insertAfterAbove(const T &e, 
	QlistNodePos(T) p, QlistNodePos(T) b /*= NULL*/)
{
	_size++;
	return p->insertAsSuccAbove(e, b);
}

template<typename T>
void Quadlist<T>::init()
{
	header = new QuadlistNode<T>;
	trailer = new QuadlistNode<T>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	header->above = trailer->above = NULL;
	header->below = trailer->below = NULL;
	_size = 0;
}

#endif