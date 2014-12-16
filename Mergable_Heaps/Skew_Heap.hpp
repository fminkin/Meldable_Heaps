#pragma once
#include"Mergable_Heaps.hpp"

IHeap* return_SkewHeap();
//UnmergableHeapsException ex;
class SkewHeapNode{
public:
	SkewHeapNode *left, *right;
	int key;
	SkewHeapNode();
	~SkewHeapNode();
	friend void swap_nodes(SkewHeapNode *a, SkewHeapNode *b);
};

class SkewHeap : public IHeap{
private:
	SkewHeapNode *root;
public:
	virtual void insert(const int key);
	virtual void meld(IHeap *casting_heap);
	virtual int extract_min();
	SkewHeap(const int k);
	SkewHeap();
	~SkewHeap();
};


