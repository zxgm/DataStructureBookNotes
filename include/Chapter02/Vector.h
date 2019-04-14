#include <stdint.h>
#include <assert.h>

typedef int32_t Rank;
#define DEFAULT_CAPACITY 3

template<typename T> class Vector
{
protected:
	Rank _size;				// Vector实际大小
	int32_t _capacity;		// Vector容量
	T *_elem;				// Vector存储元素的首地址

	void copyFrom(T const *A, Rank lo, Rank hi);
	void expand();
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);
	Rank max(Rank lo, Rank hi);
	void selectionSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank hi);
	void mergeSort(Rank lo, Rank hi);
	Rank partition(Rank lo, Rank hi);
	void quickSort(Rank lo, Rank hi);
	void heapSort(Rank lo, Rank hi);

public:
	Vector(int32_t c = DEFAULT_CAPACITY, int32_t s = 0, T v = 0)
	{
		_elem = new T[_capacity=c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const *A, Rank n){ copyFrom(A, 0, n); }
	Vector(T const *A, Rank lo, Rank hi){ copyFrom(A, lo, hi); }
	Vector(Vector<T> const &v){copyFrom(v._elem, 0, v._size); }
	Vector(Vector<T> const &v, Rank lo, Rank hi){ copyFrom(v._elem, lo, hi); }

	~Vector(){ delete[] _elem; _elem = NULL; }

	Rank size(){ return _size; }
	bool empty(){ return !_size; }
	int disordered() const;
	Rank find(T const &e) const{ return find(e, 0, _size); }

	Rank find(T const &e, Rank lo, Rank hi) const;
	Rank search(T const &e) const
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const &e, Rank lo, Rank hi) const;

	T& operator[](Rank r) const;
	Vector<T>& operator=(Vector<T> const&);
	T remove(Rank r);
	int32_t remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);
	Rank insert(T const &e){ return insert(_size, e); }

	void sort(Rank lo, Rank hi);
	void sort(){ sort(0, _size); }
	void unsort(Rank lo, Rank hi);
	void unsort(){ unsort(0,_size); }
	int32_t deduplicate();
	int32_t uniquify();

	void traverse(void(*)(T &));
	template<typename VST> void traverse(VST &);

};

template<typename T>
int32_t Vector<T>::remove(Rank lo, Rank hi)
{
	for (int32_t index = hi+1; index < _size; index++)
		_elem[lo++] = _elem[index];
	_size -= (hi-lo+1);
	shrink();
	return _elem[lo];
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T t = _elem[r];
	for (int32_t i = r; i < _size-1; i++)
		_elem[i] = _elem[i+1];

	_size--;
	shrink();
	return t;
}

template<typename T>
void permute(Vector<T> &v);

template<typename T>
bool lt(T *a, T *b){ lt(*a,*b); }
template<typename T>
bool lt(T &a, T &b){ return a<b; }
template<typename T>
bool eq(T *a, T *b){ eq(*a,*b); }
template<typename T>
bool eq(T &a, T &b){ return a == b; }

template<typename T>
void permute(Vector<T> &v)
{
	for (int32_t i = size(); i>0; i--)
		swap(v[i-1], v[rand()%i]);
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	expand();
	int32_t i = _size;
	while (i > r)
		_elem[i] = _elem[--i];

	_elem[r] = e;
	_size++;
	return r;
}

template<typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	assert(hi >= lo);
	for (int32_t i = hi; i > lo; i--)
		swap(_elem[i-1],_elem[lo+rand()%(hi-lo)]);
}

template<typename T>
T& Vector<T>::operator[](Rank r) const
{
	assert(0 <= r < _size);
	return _elem[r];
}

template<typename T>
void Vector<T>::shrink()
{
	if (_capacity <= 4*_size)
		return;
	if ((_capacity >>= 1) < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	
	T *oldElem = _elem;
	_elem = new T[_capacity];
	for (int32_t i = 0; i < _size; i++)
		_elem[i] = oldElem[i];

	delete[] oldElem;
}

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	
	T *oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int32_t i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	
	delete[] _elem;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const&v)
{
	if (this == &v)
		return *this;
	
	if (_elem)
	{
		delete[] _elem;
		_elem = NULL;
	}

	copyFrom(v._elem, 0, v.size());
	
	return *this;
}

template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = (hi-lo) << 1];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}
