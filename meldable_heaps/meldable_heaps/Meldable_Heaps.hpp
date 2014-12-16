#pragma once
#include<exception>
#include<iostream>

using namespace std;
class UnmergableHeapsException : public std::exception {
public:
	virtual const char* what() const throw(){
		return "Attempt to merge two unmergable heaps\n";
	}
};

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

