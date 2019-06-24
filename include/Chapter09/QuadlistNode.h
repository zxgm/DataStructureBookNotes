#pragma once
#ifndef _QUADLISTNODE_H
#define _QUADLISTNODE_H

#include "Chapter07/Entry.h"
#define QlistNodePos(T) QuadlistNode<T>*

template<typename T> struct QuadlistNode
{
	T entry;
	QlistNodePos(T) pred;
	QlistNodePos(T) succ;
	QlistNodePos(T) above;
	QlistNodePos(T) below;
	
	QuadlistNode(T e = T(), QlistNodePos(T) p = NULL,
		QlistNodePos(T) s = NULL, QlistNodePos(T) a = NULL,
		QlistNodePos(T) bx = NULL)
		:entry(e), pred(p), succ(s), above(a), below(b){}
	QlistNodePos(T) insertAsSuccAbove(const T&e, QlistNodePos(T) b = NULL);
};

template<typename T>
QuadlistNode<T>::insertAsSuccAbove(const T&e, QlistNodePos(T) b /*= NULL*/)
{
	QlistNodePos(T) x = new QuadlistNode<T>(e, this, succ, NULL, b);
	succ->pred = x;
	succ = x;
	if (b)
		b->above = x;
	return x;
}

#endif