#ifndef _BINNODE_H
#define _BINNODE_H

#define BinNodePos(T) BinNode<T>*
#define stature(p) \
	((p)?(p)->height:-1)
typedef enum{RB_RED,RB_BLACK} RBColor;

template<typename T>
struct BinNode
{
	T data;					// data
	BinNodePos(T) parent;	// point parent 
	BinNodePos(T) lc;		// point left child
	BinNodePos(T) rc;		// point right child
	int height;
	int npl;
	RBColor color;

	BinNode()
		:parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}
	BinNode(const T &t, BinNodePos(T) p = NULL, BinNodePos(T) lc=NULL,
		BinNodePos(T) rc=NULL,int h=0,int l=1,RBColor c=RB_RED)
		:data(t), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){}

	int size();
	BinNodePos(T) insertAsLc(const T &t);
	BinNodePos(T) insertAsRc(const T &t);
	BinNodePos(T) succ();
	template<typename VST> void travLevel(VST &);
	template<typename VST> void travPre(VST &);
	template<typename VST> void travIn(VST &);
	template<typename VST> void travPost(VST &);

	bool operator<(const BinNode &bn){ return this->data < bn.data; }
	bool operator==(const BinNode &bn){ return this->data == bn.data; }
};

template<typename T>
void BinNode<T>::travIn(VST &visit)
{
	switch (rand() % 5)
	{
	//case 1:travIn()
	}
}

template<typename T>
BinNode<T>::insertAsRc(const T &t)
{
	return this->rc = new BinNode(t, this);
}

template<typename T>
BinNode<T>::insertAsLc(const T &t)
{
	return lc = new BinNode(t, this);
}

template<typename T> BinNodePos(T) BinNode<T>::succ()
{
	BinNodePos(T) p = this;
	if (rc)
	{
		p = rc;
		while (HasLChild(*p))
			p = p->lc;
	}
	else
	{
		while (IsRChild(*p))
			p = p->parent;
		p = p->parent
	}

	return p;
}

template<typename T,typename VST>
void BinNode<T>::travLevel(VST &visit)
{
	Queue<BinNodePos(T)> q;
	q.enqueue(this);
	while (!q.empty())
	{
		BinNodePos(T) x = q.dequeue();
		visit(x->data);
		if (HasLChild(*x))
			q.enqueue(x->lc);
		if (HasRChild(*x))
			q.enqueue(x->rc);
	}
}

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x)==(x).parent->rc))
#define HasParent(x) !IsRoot(x)
#define HasLChild(x) ((x).lc��
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

// pointer
#define sibling(p) \
	IsLChild(*(p)) ? ((p)->parent->rc):((p)->parent->lc)
#define uncle(p) \
	(IsLChild(*((p)->parent)) ?((p)->parent->parent->rc):((p)->parent->parent->lc))
#define FromParentTo(x) \
	(IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))
#endif