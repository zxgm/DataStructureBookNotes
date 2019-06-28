#pragma once
#ifndef _PQ_H
#define _PQ_H

template<typename T> struct PQ
{
	virtual void insert(T e) = 0;
	virtual T getMax() = 0;
	virtual T delMax() = 0;
};
#endif