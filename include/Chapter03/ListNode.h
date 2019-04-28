#include <stdio.h>
#include <assert.h>

typedef int Rank;
#define ListNodePos(T) ListNode<T>*

template<typename T>
struct ListNode
{
	T data;
	ListNodePos(T) pred;
	ListNodePos(T) succ;

	ListNode(){}
	ListNode(T e, ListNodePos(T) p = NULL, ListNodePos(T) s= NULL)
		:data(e), pred(p), succ(s){}

	T data(){ return data; }
	ListNodePos(T) insertAsPred(const T &e);
	ListNodePos(T) insertAsSucc(const T &e);
};

template<typename T>
ListNode<T>::insertAsPred(const T &e)
{
	ListNodePos(T) preNode = this->pred;
	ListNode *node = new ListNode(e, preNode, this);
	preNode->succ = node;
	this->pred = node;
	return node;
}

template<typename T>
ListNode<T>::insertAsSucc(const T &e)
{
	ListNodePos(T) succNode = this->succ;
	ListNode *node = new ListNode(e, this, succNode);

	this->succ = node;
	succNode->pred = node;
	return node;
}