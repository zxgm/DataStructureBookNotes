/* Splay header file. */
#pragma once 
#ifndef _SPLAY_H
#define _SPLAY_H

#include "BST.h"
template<typename T> class Splay
	:public BST<T>
{
protected:
	BinNodePos(T) splay(BinNodePos(T) v);

public:
	BinNodePos(T)& search(const T &e);
	BinNodePos(T) insert(const T &e);
	bool remove(const T &e);
};

template<typename T>
Splay<T>::insert(const T &e)
{
	if (!_root)
	{
		_size++;
		return _root = new BinNode<T>(e);
	}

	if (e == search(e)->data)
		return _root;
	_size++;
	BinNodePos(T) t = _root;
	if (_root->data < e)
	{
		t->parent = _root = new BinNode<T>(e, NULL, t, t->rc);
		if (HasRChild(*t))
		{
			t->rc->parent = _root;
			t->rc = NULL;
		}
	}
	else
	{
		t->parent = _root = new BinNode<T>(e, NULL, t->lc, t); 
		if (HasLChild(*t))
		{
			t->lc->parent = _root;
			t->lc = NULL;
		}
	}
	updateHeightAbove(t);
	return _root;
}

template<typename T>
Splay<T>::search(T) & search(const T &e)
{
	BinNodePos(T) p = searchIn(_root, e, _hot = NULL);
	_root = splay(p ? p : _hot);
	return _root;
}

template<typename NodePos> inline
void attachAsLChild(NodePos p, NodePos lc)
{
	p->lc = lc;
	if (lc)
		lc->parent = p;
}

template<typename NodePos> inline
void attachAsRChild(NodePos p, NodePos rc)
{
	p->rc = rc;
	if (rc)
		rc->parent = p;
}

template<typename T>
BinNodePos(T) Splay<T>::splay(BinNodePos(T) v)
{
	if (!v)
		return NULL;
	BinNodePos(T) p;
	BinNodePos(T) g;

	while ((p = v->parent) && (g = p->parent))
	{
		BinNodePos(T) gg = g->parent;
		if (IsLChild(*v))
		{
			if (IsLChild(*p))
			{
				attachAsLChild(g, p->rc);
				attachAsLChild(p, v->rc);
				attachAsRChild(p, g);
				attachAsRChild(v, p);
			}
			else
			{
				attachAsLChild(p, v->rc);
				attachAsRChild(g, v->lc);
				attachAsLChild(v, g);
				attachAsRChild(v, p);
			}
		}
		else if (IsRChild(*p))
		{
			attachAsRChild(g, p->lc);
			attachAsRChild(p, v->lc);
			attachAsLChild(p, g);
			attachAsLChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lc);
			attachAsLChild(g, v->rc);
			attachAsRChild(v, g);
			attachAsLChild(v, p);
		}

		if (!gg)
			v->parent = NULL;
		else
		{
			(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}

		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	}

	if (p = v->parent)
	{
		if (IsLChild(*v))
		{
			attachAsLChild(p, v->rc);
			attachAsRChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lc);
			attachAsLChild(v, p);
		}

		updateHeight(p);
		updateHeight(v);
	}
	v->parent = NULL;
	return v;
}


#endif