#include"Meldable_Heaps.hpp"
#include"Binomial_Heap.hpp"
#include"Leftist_Heap.hpp"
#include"Skew_Heap.hpp"

IHeap* create_mergable_heap(list_of_heaps a){
	switch (a){
	case MH_BHEAP:
		return return_BHeap();
	case MH_LEFTIST:
		return return_LeftistHeap();
	case MH_SKEW:
		return return_SkewHeap();
	default:
		return NULL;
	}
}
