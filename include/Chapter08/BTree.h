/* BTree header file. */
#pragma once
#ifndef _BTREE_H
#define _BTREE_H

#include "BTNode.h"

template<typename T> class BTree
{
protected:
	int _size;
	int _order;
	BTNodePos(T) _root;
	BTNodePos(T) _hot;
	void solveOverflow(BTNodePos(T));
	void solveUnderflow(BTNodePos(T));

public:
	BTree(int order = 3)
		:_order(order), _size(0)
	{
		_root = new BinNode<T>();
	}

	~BTree()
	{
		if (_root)
			release(_root);
	}

	int order() const { return _order; }
	int size() const { return _size; }
	BTNodePos(T)& root(){ return _root; }
	bool empty() const { return !_root; }
	BTNodePos(T) search(const T &e);
	bool insert(const T &e);
	bool remove(const T &e);
};
#endif