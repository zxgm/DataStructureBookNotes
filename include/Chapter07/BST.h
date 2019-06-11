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

template<typename T> BinNodePos(T) BST<T>::connect34(
	BinNodePos(T) a, BinNodePos(T) b, BinNodePos(T) c,
	BinNodePos(T) t0, BinNodePos(T) t1, BinNodePos(T) t2, BinNodePos(T) t3)
{
	a->lc = t0;
	if (t0)
		t0->parent = a;
	a->rc = t1;
	if (t1)
		t1->parent = a;
	updateHeight(a);
	c->lc = t2;
	if (t2)
		t2->parent = c;
	c->rc = t3;
	if (t3)
		t3->parent = c;
	updateHeight(c);
	b->lc = a;
	a->parent = b;
	b->rc = c;
	c->parent = b;
	updateHeight(b);

	return b;
}

template<typename T>
BinNodePos(T) BST<T>::rotateAt(BinNodePos(T) v)
{
	BinNodePos(T) p = v->parent;
	BinNodePos(T) g = p->parent;
	if (IsLChild(*p))
	{
		if (IsLChild(*v))
		{
			p->parent = g->parent;
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else
	{
		if (IsRChild(*v))
		{
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else
		{
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
	}
}
#endif