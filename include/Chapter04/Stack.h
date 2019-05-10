#ifndef _STACK_H
#define _STACK_H

#include "../../include/Chapter02/Vector.h"

template<typename T>
class Stack
	:public Vector<T>
{
public:
	void push(const T&e){ insert(size(), e); }
	T pop(){ return remove(size()-1); }
	T& top(){ return (*this)[size()-1]; }
};

void convert(Stack<int> &s, int n, int base);

void convert(Stack<char> &s, int n, int base)
{
	static char digit[] =
	{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	while (n > 0)
	{
		s.push(digit[n % base]);
		n /= base;
	}
}

#endif