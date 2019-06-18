#include "BST.h"

template<typename T> class RedBlack :public BST<T>
{
protected:
	void solveDoubleRed(BinNodePos(T) x);
	void solveDoubleBlack(BinNodePos(T) x);
	int updateHeight(BinNodePos(T) x);
public:
	BinNodePos(T) insert(const T &e);
	bool remove(const T &e);
};

template<typename T>
void RedBlack<T>::solveDoubleRed(BinNodePos(T) x)
{
	if (IsRoot(*x))
	{
		_root->color = RB_BLACK;
		_root->height++;
		return;
	}

	BinNodePos(T) p = x->parent;
	if (IsBlack(p))
		return;

	BinNodePos(T) g = p->parent;
	BinNodePos(t) u = uncle(x);

	if (IsBlack(u))
	{
		if (IsLChild(*x) == IsLChild(*p))
			p->color = RB_BLACK;
		else
			x->color = RB_BLACK;
		g->color = RB_RED;
		BinNodePos(T) gg = g->parent;
		BinNodePos(T) r = FromParentTo(*g) = rotateAt(x);
		r->parent = gg;
	}
	else
	{
		p->color = RB_BLACK;
		p->height++;
		u->color = RB_BLACK;
		u->height++;
		if (!IsRoot(*g))
			g->color = RB_RED;
		solveDoubleRed(g);
	}
}

template<typename T>
RedBlack<T>::insert(const T &e)
{
	BinNodePos(T) &x = search(e);
	if (x)
		return x;
	x = new BinNode<T>(e, _hot, NULL, NULL, -1);
	_size++;
	solveDoubleRed(x);
	return x ? x : _hot->parent;
}

#define IsBlack(p) (!(p) || (RB_BLACK==(p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) \
	(stature((x).lc) == stature((x).rc) && \
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc)+1)))

	template<typename T> int RedBlack<T>::updateHeight(BinNodePos(T) x)
	{
		x->height = max(stature(x->lc), stature(x->rc));
		return IsBlack(x) ? x->height++ : x->height;
	}
