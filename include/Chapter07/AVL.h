/* AVL header file. */
#pragma once 
#ifndef _AVL_H
#define _AVL_H

#include "BST.h"
template<typename T> class AVL
	:public BST<T>
{
public:
	BinNodePos(T) insert(const T &t);
	bool remove(const T &e);
};

#define Balance(x) (stature((x).lc) == stature((x).rc))
#define BalFac(x) (stature((x).lc)-stature((x).rc))
#define AvlBalanced(x) ((-2<BalFac(x)) && (BalFac(x)<2))

#define tallerChild(x) ( \
	stature((x)->lc)>stature((x)->rc) ? (x)->lc : ( \
	stature((x)->lc)<stature((x)->rc) ? (x)->rc : ( \
	IsChild(*(x)) ? (x)->lc : (x)->rc \
	) \
	) \
)

template<typename T> BinNodePos(T) AVL<T>::insert(const T &e)
{
	BinNodePos(T) &x = search(e);
	if (x)
		return x;
	BinNodePos(T) xx = x = new BinNode<T>(e, _hot);
	_size++;

	for (BinNodePos(T) g = _hot; g; g = g->parent)
	{
		if (!AvlBalanced(*g))
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			break;
		}
		else
			updateHeight(g);
	}

	return xx;
}

template<typename T> bool AVL<T>::remove(const T &e)
{
	BinNodePos(T) &x = search(e);
	if (!x)
		return false;
	removeAt(x, _hot);
	_size--;
	for (BinNodePos(T) g = _hot; g; g = g->parent)
	{
		if (!AvlBalanced(*g))
		{
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
		}
		updateHeight(g);
	}
	return true;
}
#endif