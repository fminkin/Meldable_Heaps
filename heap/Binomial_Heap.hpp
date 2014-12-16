#pragma once

#include"Mergable_Heaps.hpp"

IHeap* return_BHeap();

class BTree{
public:
	BTree *sibling, *child;
	int degree, key;
	void link(BTree *z);
	BTree();
	~BTree();
};

class BHeap : public IHeap{
	BTree *head;
public:
	virtual void insert(const int key);
	virtual void meld(IHeap *casting_heap);
	virtual int extract_min();
	void merge(BHeap *a);
	BTree* GetMin();
	BHeap();
	~BHeap();
};
