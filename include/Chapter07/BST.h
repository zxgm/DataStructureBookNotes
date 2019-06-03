/* Binary search tree header file. */
#pragma once
#ifndef _BST_H
#define _BST_H

#include "BinTree.h"

template<typename T>
class BST :public BinTree<T>
{
protected:
	BinNodePos(T) _hot;
	BinNodePos(T) connect34(BinNodePos(T), BinNodePos(T), BinNodePos(T),
		BinNodePos(T), BinNodePos(T), BinNodePos(T), BinNodePos(T));
	BinNodePos(t) rotateAt(BinNodePos(T) x);

public:
	virtual BinNodePos(T)& search(const T &e);
	virtual BinNodePos(T) insert(const T &e);
	virtual bool remove(const T &e);
};

template<typename T>
BinNodePos(T)& BST<T>::search(const T &e)
{
	return searchIn(_root, e, _hot = NULL);
}

template<typename T>
static BinNodePos(T)& searchIn(BinNodePos(T) &v, const T &e, BinNodePos(T) &hot)
{
	if (!v || (e == v->data))
		return v;
	hot = v;
	return searchIn(((e < v->data) ? v->lc : v->rc),e,hot);
}

template<typename T> BinNodePos(T) BST<T>::insert(const T &e)
{
	BinNodePos(T) &x = search(e);
	if (x)
		return x;
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);
	return x;
}

template<typename T> 
bool BST<T>::remove(const T &e)
{
	BinNodePos(T) &x = search(e);
	if (!x)
		return false;
	removeAt(x, _hot);
	_size--;
	updateHeightAbove(_hot);
	return true;
}

template<typename T>
static BinNodePos(T)removeAt(BinNodePos(T) &x, BinNodePos(T) &hot)
{
	BinNodePos(T) w = x;
	BinNodePos(T) succ = NULL;
	if (!HasLChild(*x))
		succ = x = x->rc;
	if (!HasRChild(*x))
		succ = x = x->lc;
	else
	{
		w = w->succ();
		swap(x->data, w->data);
		BinNodePos(T) u = w->parent;
		(u == x ? u->rc : u->lc) = succ = w->rc;
	}

	hot = w->parent;
	if (succ)
		succ->parent = hot;
	release(w->data);
	release(w);
	return succ;
}
#endif