#ifndef azaza
#define azaza
#include<typeinfo>//exception bad_cast
#include<iostream>

using namespace std;
bad_cast ex;
enum list_of_heaps{
	MH_BHEAP,
	MH_LEFTIST,
	MH_SKEW,
	NOTMH_SET,
	NOTMH_QUEUE
};

class IHeap{
public:
	virtual void insert(const int key) = 0;
	virtual void meld(IHeap *casting_heap) = 0;
	virtual int extract_min() = 0;
	virtual ~IHeap(){
	};
};

IHeap* create_mergable_heap(list_of_heaps a);

#endif