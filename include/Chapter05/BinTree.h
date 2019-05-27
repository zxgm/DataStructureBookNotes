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

	template<typename VST> void travLevel(VST &visit)
	{
		if (_root)
			_root->travLevel(visit);
	}

	template<typename VST> void travPre(VST &visit)
	{
		if (_root)
			_root->travPre(visit);
	}

	template<typename VST> void travIn(VST &visit)
	{
		if (_root)
			_root->travIn(visit);
	}

	template<typename VST> void travPost(VST &visit)
	{
		if (_root)
			_root->travPost(visit);
	}

	bool operator<(BinTree<T> const &t)
	{
		return _root&&t._root&&lt(_root, t._root);
	}

	bool operator==(const BinTree<T> &t)
	{
		return _root && t._root && (_root && t._root);
	}

	template<typename T> int BinTree<T>::updateHeight(BinNodePos(T) x)
	{
		return x->height = 1 + max(stature(x->lc), stature(x->rc));
	}

	template<typename T> void BinTree<T>::updateHeightAbove(BinNodePos(T) x)
	{
		while (x)
		{
			updateHeight(x);
			x = x->parent;
		}
	}

	template<typename T> BinNodePos(T) BinTree<T>::insertAsRoot(const T &t)
	{
		_size++;
		return _root = new BinNode(t);
	}

	template<typename T> BinNodePos(T) BinTree<T>::insertAsLc(BinNodePos(T) p, const T &t)
	{
		_size++;
		p->insertAsLc(t);
		updateHeightAbove(p);
		return p->lc;
	}

	template<typename T> BinNodePos(T) BinTree<T>::insertAsRc(BinNodePos(T) p, const T &t)
	{
		_size++;
		p->insertAsRc(t);
		updateHeightAbove(p);
		return p->rc;
	}

	template<typename T> BinNodePos(T) BinTree<T>::attachAsLc(BinNodePos(T) p, BinTree<T> *&t)
	{
		p->lc = t->_root;
		t->_root->parent = p;

		_size += t->_size;
		updateHeightAbove(p);

		t->_root = NULL;
		t->_size = 0;
		release(t);
		t = NULL;
		return p;
	}

	template<typename T> BinNodePos(T) BinTree<T>::attachAsRc(BinNodePos(T) p, BinTree<T> *&t)
	{
		p->rc = t->_root;
		p->rc->parent = p;

		_size += t->_size;
		updateHeightAbove(p);

		t->_root = NULL;
		t->_size = 0;
		release(t);
		t = NULL;
		return p;
	}

	template<typename T> int BinTree<T>::remove(BinNodePos(T) p)
	{
		FromParentTo(*p) = NULL;
		updateHeightAbove(p->parent);
		int n = removeAt(x);
		_size -= n;
		return n;
	}

	template<typename T> int removeAt(BinNodePos(T) x)
	{
		if (!x)
			return 0;
		int n = 1 + removeAt(x->lc) + removeAt(x->rc);
		release(x->data);
		release(x);
		return n;
	}

	template<typename T> BinTree<T>* BinTree<T>::secede(BinNodePos(T) p)
	{
		FromParentTo(*p) = NULL;
		updateHeightAbove(p->parent);

		BinTree<T>* binTree = new BinTree<T>();
		binTree->parent = NULL;
		binTree->_root = p;
		binTree->_size = p->size();
		_size -= binTree->_size;
		return binTree;
	}

};

template<typename T,typename VST>
static void visitAlongLeftBranch(BinNodePos(T) x, VST &visit, Stack<BinNodePos(T)> &s)
{
	while (x)
	{
		visit(x->data);
		s.push(x->rc);
		x = x->lc;
	}
}


template<typename T,typename VST>
void travIn_I2(BinNodePos(T) x, VST &visit)
{
	Stack<BinNodePos(T)> s;
	while (true)
	{
		if (x)
		{
			s.push(x);
			x = x->lc;
		}
		else if (!s.empty())
		{
			x = s.pop();
			visit(x->data);
			x = x->rc;
		}
		else
			break;
	}
}

template<typename T,typename VST>
void travIn_I3(BinNodePos(T) x, VST &visit)
{
	bool backtrack = false;
	while (true)
	{
		if (!backtrack && HasLChild(*x))
		{
			x = x->lc;
		}
		else
		{
			visit(x->data);
			if (HasRChild(*x))
			{
				x = x->rc;
				backtrack = false;
			}
			else
			{
				if (!(x = x->succ()))
					break;
				backtrack = true;
			}
		}
	}
}

template<typename T>
static void gotoHLVFL(Stack<BinNodePos(T)> &s)
{
	while (BinNodePos(T) x = s.top())
	{
		if (HasLChild(*x))
		{
			if (HasRChild(*x))
				s.push(x->rc);
			s.push(x->lc);
		}
		else{
			s.push(x->rc);
		}
	}

	s.pop();
}

template<typename T,typename VST>
void travPost_I(BinNodePos(T) x, VST &visit)
{
	Stack<BinNodePos(T)> s;
	if (x)
		s.push(x);
	while (!s.empty())
	{
		if (s.top() != x->parent)
			gotoHLVFL(s);
		x = s.pop();
		visit(x->data);
	}
}

template<typename T>
static void goAlongLeftBranch(BinNodePos(T) x, Stack<BinNodePos(T)> &s)
{
	while (x)
	{
		s.push(x);
		x = x->lc;
	}
}

template<typename T,typename VST>
void travIn_I1(BinNodePos(T) x, VST &visit)
{
	Stack<BinNodePos(T)> s;
	while (true)
	{
		goAlongLeftBranch(x, s);
		if (s.empty())
			break;
		BinNodePos(T) p = s.pop();
		visit(p->data);
		x = p->rc;
	}
}

template<typename T,typename VST>
void travPre_I2(BinNodePos(T) x, VST &visit)
{
	Stack<BinNodePos(T)> s;
	while (true)
	{
		visitAlongLeftBranch(x,visit,s);
		if (s.empty())
			break;
		x = s.pop();
	}
}


/*template<typename T,typename VST>
void travPre_R(BinNodePos(T) x, VST &visit)
{
	if (!x) return;
	visit(x->data);
	travPre_R((x->lc, visit);
	travPre_R(x->rc, visit);
}

template<typename T,typename VST>
void travPost_R(BinNodePos(T) x, VST &visit)
{
	if (!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}

template<typename T,typename VST>
void travIn_R(BinNodePos(T) x, VST &visit)
{
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}*/
#endif