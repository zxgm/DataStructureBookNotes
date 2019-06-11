/* BTree node header file. */
#pragma once 
#ifndef _BTNODE_H
#define _BTNODE_H

#define BTNodePos(T) BTNode<T>*

template<typename T> struct BTNode
{
	BTNodePos(T) parent;
	Vector<T> key;
	Vector<BTNodePos(T)> child;

	BTNode()
	{
		parent = NULL;
		child.insert(0, NULL);
	}

	BTNode(T e, BTNodePos(T) lc = NULL, BTNodePos(T) rc = NULL)
	{
		parent = NULL;
		key.insert(0, lc);
		child.insert(1, rc);
		if (lc)
			lc->parent = this;
		if (rc)
			rc->parent = this;
	}
};
#endif