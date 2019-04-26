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
void List<T>::copyNodes(ListNodePos(T) p, int n)
{
	while (n--)
	{
		T &e = p->data;
		ListNodePos(T) tmpNode = new ListNode(e);

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
	header = new ListNode();
	trailer = new ListNode();
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
}
