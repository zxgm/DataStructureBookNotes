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
#endif