/* Key-value Object header file. */
#pragma once
#ifndef _ENTRY_H
#define _ENTRY_H

template<typename K, typename V> struct Entry
{
	K key;
	V value;
	Entry(K k = K(), V v = V()) :key(k), value(v){}
	Entry(const Entry &entry) :key(entry.key), value(entry.value){}

	bool operator<(const Entry<K,V> & e){ return this->key < e.key; }
	bool operator>(const Entry<K, V> &e){ return this->key > e.key; }
	bool operator==(const Entry<K, V> &e){ return this->key == e.key; }
	bool operator!=(const Entry<K, V> &e){ return !(operator==(e)); }
};
#endif