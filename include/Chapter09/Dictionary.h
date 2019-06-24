#pragma once
#ifndef _DICTIONARY_H
#define _DICTIONARY_H

template<typename K, typename V> struct Dictionary
{
	virtual int size() const = 0;
	virtual bool put(K, V) = 0;
	virtual V* get(K k) = 0;
	virtual bool remove(K k) = 0;
};
#endif