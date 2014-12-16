#pragma once
#include"Mergable_Heaps.hpp"

IHeap* return_LeftistHeap();
//UnmergableHeapsException ex;
class LeftistHeapNode{
public:
	LeftistHeapNode *left, *right;
	int key, rank;
	LeftistHeapNode();
	~LeftistHeapNode();
	inline friend void swap_nodes(LeftistHeapNode *a, LeftistHeapNode *b);
};

class LeftistHeap : public IHeap{
public:
	LeftistHeapNode *root;
	virtual void insert(const int key);
	virtual void meld(IHeap *aa);
	virtual int extract_min();
	LeftistHeap(const int k);
	LeftistHeap();
	~LeftistHeap();
};

