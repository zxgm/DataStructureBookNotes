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
void RedBlack<T>::solveDoubleBlack(BinNodePos(T) r)
{
	BinNodePos(T) p = r ? r->parent : _hot;
	if (!p)
		return;

	BinNodePos(T) s = (r==p->lc)?p->rc:p->lc;
	if (IsBlack(s))
	{
		BinNodePos(T) t = NULL;
		if (IsRed(s->rc))
			t = s->rc;
		if (IsRed(s->lc))
			t = s->lc;
		if (t)
		{
			RBColor oldColor = p->color;
			BinNodePos(T) b = FromParentTo(*p) = rotateAt(t);
			if (HasLChild(*b))
			{
				b->lc->color = RB_BLACK;
				updateHeight(b->lc);
			}
			if (HasRChild(*b))
			{
				b->rc->color = RB_BLACK;
				updateHeight(b->rc);
			}
			b->color = oldColor;
			updateHeight(b);
		}
		else
		{
			s->color = RB_RED;
			s->height--;
			if (IsRed(p))
				p->color = RB_BLACK;
			else
			{
				p->height--;
				solveDoubleBlack(p);
			}
		}
	}
	else
	{
		s->color = RB_BLACK;
		p->color = RB_RED;
		BinNodePos(T) t = IsLChild(*s) ? s->lc : s->rc;
		_hot = p;
		FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(r);
	}
}

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
