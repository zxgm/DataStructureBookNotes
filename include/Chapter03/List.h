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
};

template<typename T>
T List<T>::remove(ListNodePos(T) p)
{
	ListNodePos(T) predNode = p->pred;
	ListNodePos(T) succNode = p->succ;
	predNode->succ = succNode;
	succNode->pred = predNode;

	delete p;
	p = NULL;
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
	while (n-- && p)
	{
		T &e = p->data;
		trailer->insertAsPred(e);
		p = p->succ;
	}
}

template<typename T>
int List<T>::clear()
{
	ListNodePos(T) listNode = header;
	while (listNode)
	{
		ListNodePos(T) tmpNode = listNode->succ;
		delete listNode;
		listNode = NULL;
		listNode = tmpNode;
	}

	init();
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
