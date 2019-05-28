#ifndef _VECTOR_H
#define _VECTOR_H

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
	void merge(Rank lo, Rank mid, Rank hi);
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
	// 针对已排序的容器
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
	int32_t uniquify();		// 有序向量的唯一化

	void traverse(void(*)(T &));
	template<typename VST> void traverse(VST &);

};

template<typename T>
void Vector<T>::merge(Rank lo, Rank mid, Rank hi)
{
	T *a = _elem + lo;
	Rank l = mid - lo;
	T *lp = new T[l];
	for (Rank i = 0; i < l; lp[i] = a[i++]);

	Rank r = hi - mid;
	T *rp = _elem + mid;

	// i:记录排序的下标 j:记录前向向量
	// 选中两者中最小的数值追加；如果某向量结束，剩余向量全部追加
	for (Rank i = 0, j = 0, k = 0; (j < l || k < r);)
	{
		if (j<l && (k>=r || lp[j] <= rp[k]))
			a[i++] = lp[j++];
		if (k<r && (j >= l || rp[k] < lp[j]))
			a[i++] = rp[k++];
	}

	delete[] lp;
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi-lo < 2) return;
	int32_t mid = (hi+lo) >> 1;
	mergeSort(lo, mid);
	mergeSort(mid, hi);
	merge(lo, mid, hi);
}

// 一趟扫描，排最大值
template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
	bool isSort = true;
	while (++lo < hi)
	{
		if (_elem[lo - 1] > _elem[lo])
		{
			T tmp = _elem[lo - 1];
			_elem[lo - 1] = _elem[lo];
			_elem[lo] = tmp;

			isSort = false;
		}
	}

	return isSort;
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (!bubble(lo,hi--));// 全部扫描
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand()%5)
	{
	case 1:bubbleSort(lo, hi);break;
	//case 2:selectionSort(lo, hi);break;
	case 3:mergeSort(lo, hi);break;
	//case 4:heapSort(lo, hi); break;
	//default:quickSort(lo, hi);break;
	}
}

template<typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const
{
	// 三分支版本的二分查找
	/*int32_t med = 0;
	while (lo < hi)
	{
		med = (lo + hi) >> 1;
		if (_elem[med] > e)
			hi = med;
		else if (_elem[med] < e)
			lo = med+1;
		else
			return med;
	}

	return -1;*/

	// 二分支版本的二分查找
	/*int32_t med = 0;
	while (1 < hi-lo)
	{
	med = (hi+lo)>>1;
	_elem[med] > e ? hi=med:lo=med;
	}

	return _elem[lo] != e ? -1 : lo;*/

	// 
	while (lo < hi)
	{
		Rank med = (hi+lo) >> 1;
		_elem[med] > e ? hi = med:lo = med + 1;
	}

	return --lo;

	// 三分支版本的斐波那契查找
	/*FibUtil fibUtil(hi-lo);
	int32_t med = 0;
	while (lo < hi)
	{
	int64_t tmp = fibUtil.getlt(hi - lo);
	if (tmp == -1)
	break;

	med = lo + tmp;
	if (_elem[med] > e)
	hi = med;
	else if (_elem[med] < e)
	lo = med + 1;
	else
	return med;
	}

	return -1;*/
}

template<typename T> template<typename VST>
void Vector<T>::traverse(VST &vst)
{
	for (int32_t index = 0; index < _size; ++index)
		vst(_elem[index]);
}

template<typename T>
int32_t Vector<T>::uniquify()
{
	int32_t pos = 1, oldSize = _size;
	for (int32_t index = 1; index < _size; ++index)
	{
		if (_elem[index-1] == _elem[index])
			continue;
		_elem[pos++] = _elem[index];
	}

	_size = pos;
	shrink();
	return oldSize - _size;
}

template<typename T>
int Vector<T>::disordered() const
{
	int32_t n = 0;
	for (int32_t index = 1; index < _size; ++index)
		if (_elem[index-1] > _elem[index])
			n++;

	return n;
}

template<typename T>
void Vector<T>::traverse(void(*fun)(T &))
{
	for (int32_t index = 0; index < _size; ++index)
		fun(_elem[index]);
}

template<typename T>
int32_t Vector<T>::deduplicate()
{
	int32_t pos = 1;
	for (int32_t index = 1; index < _size; ++index)
	{
		Rank r = find(_elem[index], 0, pos);
		if (r < 0)	// 前缀未重复元素
			_elem[pos++] = _elem[index];
	}
	
	size_t oldSize = _size;
	_size = pos;
	shrink();
	return oldSize - pos;
}

template<typename T>
int32_t Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi-lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T t = _elem[r];
	remove(r, r+1);
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
	assert(r >= 0 && r < _size);
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
	
	delete[] oldElem;
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

#endif
