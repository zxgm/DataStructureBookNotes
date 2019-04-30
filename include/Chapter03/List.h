#include "ListNode.h"

template<typename T>
class List
{
private:
	int _size;
	ListNodePos(T) header;
	ListNodePos(T) trailer;

protected:
	void init();
	int clear();
	void copyNodes(ListNodePos(T), int);
	void merge(ListNodePos(T)&, int, List<T> &, ListNodePos(T), int);
	void mergeSort(ListNodePos(T) &, int);
	void selectionSort(ListNodePos(T), int);
	void insertionSort(ListNodePos(T), int);

public:
	List(){ init(); }

	List(List<T> const & l);
	List(List<T> const &l, Rank r, int n);
	List(ListNodePos(T) p, int n);
	~List();

	Rank size(){ return _size; }
	bool empty(){ return !_size; }
	T& operator[](Rank r) const;
	ListNodePos(T) first() const{return header->succ;}
	ListNodePos(T) last() const{ return trailer->pred; }
	bool valid(ListNodePos(T) p)
	{
		return p&&p != header&&p != trailer;
	}
	int disordered() const;
	ListNodePos(T) find(T const &e) const
	{
		return find(e, _size, trailer);
	}

	ListNodePos(T) find(const T &e, int n, ListNodePos(T) p) const;
	ListNodePos(T) search(const T &e) const
	{
		return search(e, _size, trailer);
	}

	ListNodePos(T) search(const T &e, int n, ListNodePos(T) p) const;
	ListNodePos(T) selectMax(ListNodePos(T) p, int n);
	ListNodePos(T) selectMax(){ return selectMax(header->succ, _size); }

	ListNodePos(T) insertAsFirst(const T &e);
	ListNodePos(T) insertAsLast(const T &e);
	// p节点之后插入数据e
	ListNodePos(T) insertA(ListNodePos(T) p, const T &e);
	ListNodePos(T) insertB(ListNodePos(T) p, const T &e);
	T remove(ListNodePos(T) p);
	void merge(List<T> & l){ merge(first(),_size,l,l.first(),l.size()); }
	void sort(ListNodePos(T) p, int n);
	void sort(){ sort(first(), _size); }
	int deduplicate();
	int uniquify();
	void reverse();

	void traverse(void(*)(T &));
	template<typename VST>
	void traverse(VST &vst);

private:
	// 交换指针指向的值
	void swap(ListNodePos(T) a, ListNodePos(T) b);
};

template<typename T>
void List<T>::sort(ListNodePos(T) p, int n)
{
	switch (rand() % 3)
	{
	case 1:insertionSort(p, n); break;
	case 2:selectionSort(p, n); break;
	default:mergeSort(p, n); break;
	}
}

template<typename T>
void List<T>::insertionSort(ListNodePos(T) p, int n)
{
	int sortedSize = 0;
	while (n--)
	{
		ListNodePos(T) searchNode = search(p->data, sortedSize, p);
		this->insertA(searchNode, p->data);

		p = p->succ;
		remove(p->pred);

		sortedSize++;
	}
}

template<typename T>
List<T>::search(const T &e, int n, ListNodePos(T) p) const
{
	while (n--)
		if ((p = p->pred)->data <= e)
			break;

	return p;
}

template<typename T>
void List<T>::swap(ListNodePos(T) a, ListNodePos(T) b)
{
	T tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

template<typename T>
void List<T>::reverse()
{
	ListNodePos(T) backNode = header;
	ListNodePos(T) forwardNode = trailer;

	while ((backNode = backNode->succ) != (forwardNode = forwardNode->pred))
		swap(backNode, forwardNode);
}

// 有序列表的唯一化
template<typename T>
int List<T>::uniquify()
{
	if (_size < 2) return 0;

	int oldSize = size();
	ListNodePos(T) preNode = first();
	ListNodePos(T) pNode = NULL;
	while ((pNode = preNode->succ) != trailer)
		pNode->data == preNode->data ? remove(pNode) : preNode = pNode;

	return oldSize - _size;
}

template<typename T>
void List<T>::traverse(void(*visit)(T &))
{
	for (ListNodePos(T) node = header->succ;
		node != trailer; node = node->succ;)
	{
		visit(node->data);
	}
}

template<typename T> template<typename VST>
void List<T>::traverse(VST &vst)
{
	for (ListNodePos(T) node = header->succ;
		node != trailer; node = node->succ)
	{
		vst(node->data);
	}
}

template<typename T>
int List<T>::deduplicate()
{
	assert(_size > 1);

	ListNodePos(T) predIndex = first();
	int predSize = 1, oldSize = _size;
	ListNodePos(T) currentIndex = NULL;
	while (--_size)
	{
		currentIndex = predIndex->succ;
		ListNodePos(T) pNode = \
			find(currentIndex->data, predSize, currentIndex);
		if (pNode)
			remove(pNode);
		else
		{
			predIndex = currentIndex;
			predSize++;
		}
	}

	return oldSize - predSize;
}

template<typename T>
List<T>::~List()
{
	clear();
	delete header;
	header = NULL;
	delete trailer;
	trailer = NULL;
}

template<typename T>
List<T>::List(List<T> const &l, Rank r, int n)
{
	ListNodePos(T) pNode = l.first();
	while (r-- && pNode)
		pNode = pNode->succ;
	copyNodes(pNode, n);
}

template<typename T>
List<T>::List(List<T> const & l)
{
	copyNodes(l.first(), l.size());
}

template<typename T>
List<T>::List(ListNodePos(T) p, int n)
{
	copyNodes(p, n);
}

template<typename T>
T List<T>::remove(ListNodePos(T) p)
{
	ListNodePos(T) predNode = p->pred;
	ListNodePos(T) succNode = p->succ;
	predNode->succ = succNode;
	succNode->pred = predNode;

	T e = p->data;
	delete p;
	p = NULL;
	--_size;
	return e;
}

template<typename T>
ListNodePos(T) List<T>::insertA(ListNodePos(T) p, const T &e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
ListNodePos(T) List<T>::insertB(ListNodePos(T) p, const T &e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
ListNodePos(T) List::insertAsLast(const T &e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template<typename T>
ListNodePos(T) List<T>::insertAsFirst(const T &e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
ListNodePos(T)
List<T>::find(const T &e, int n, ListNodePos(T) p) const
{
	while (n--)
		if (e == (p = p->pred)->data)
			return p;

	return NULL;
}

template<typename T>
T& List<T>::operator[](Rank r) const
{
	assert(0 <= r < _size);

	ListNodePos(T) pNode = first();
	while (r-- && pNode)
		pNode = pNode->succ;

	return pNode->data;
}

template<typename T>
void List<T>::copyNodes(ListNodePos(T) p, int n)
{
	init();
	while (n-- && p)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
int List<T>::clear()
{
	ListNodePos(T) listNode = first();
	while (listNode != trailer)
	{
		ListNodePos(T) tmpNode = listNode->succ;
		delete listNode;
		listNode = NULL;
		listNode = tmpNode;
	}

	int oldSize = _size;
	_size = 0;
	return oldSize;
}

template<typename T>
void List<T>::init()
{
	_size = 0;
	header = new ListNode<T>();
	trailer = new ListNode<T>();
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
}
