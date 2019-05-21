#ifndef _BINTREE_H
#define _BINTREE_H
#include "BinNode.h"

template<typename T>
class BinTree
{
protected:
	int _size;
	BinNodePos(T) _root;
	virtual int updateHeight(BinNodePos(T) x);
	void updateHeightAbove(BinNodePos(T) x);

public:
	BinTree() :_size(0), _root(NULL){}
	~BinTree()
	{
		if (_size)
		{
			remove(_root);
		}
	}
	int size() const { return _size; }
	bool empty() const{ return !_root; }
	BinNodePos(T) root() const { return _root; }
	BinNodePos(T) insertAsRoot(const T &t);
	BinNodePos(T) insertAsLc(BinNodePos(T) p, const T &t);
	BinNodePos(T) insertAsRc(BinNodePos(T) p, const T &t);
	BinNodePos(T) attachAsLc(BinNodePos(T) p, BinTree<T> *&t);
	BinNodePos(T) attachAsRc(BinNodePos(T) p, BinTree<T> *&t);
	int remove(BinNodePos(T) p);
	BinTree<T>* secede(BinNodePos(T) p);
	template<typename VST>
	void travLevel(VST &visit)
	{

	}
};
#endif