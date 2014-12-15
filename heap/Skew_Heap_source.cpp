#include"Skew_Heap.hpp"
#include<typeinfo>
using namespace std;
bad_cast unable_to_merge_e;

IHeap* return_SkewHeap(){
	return new SkewHeap;
}
//SkewHeapNode methods
SkewHeapNode::SkewHeapNode(){
	right = NULL;
	left = NULL;
}
SkewHeapNode::~SkewHeapNode(){
	if (right)
		delete right;
	if (left)
		delete left;
}
void swap_nodes(SkewHeapNode *a, SkewHeapNode *b){
	int temp = a->key;
	a->key = b->key;
	b->key = temp;
	SkewHeapNode *temp_v;
	temp_v = a->left;
	a->left = b->left;
	b->left = temp_v;
	temp_v = a->right;
	a->right = b->right;
	b->right = temp_v;

}

void SkewHeap::insert(const int key){
	SkewHeap *H = new SkewHeap(key);
	meld(H);
}

void SkewHeap::meld(IHeap *casting_heap){
	if (dynamic_cast<SkewHeap *>(casting_heap) == NULL && casting_heap != 0)
		throw unable_to_merge_e;

	SkewHeap *new_heap = dynamic_cast<SkewHeap *>(casting_heap);
	if (!root){ // rank = 0, if node is equal to NULL
		root = new_heap->root;
		return;
	}
	if (!new_heap->root){
		return;
	}
	if (root->key > new_heap->root->key)
		swap_nodes(root, new_heap->root);

	SkewHeapNode *temp_root = root;
	root = root->right;
	meld(new_heap); // melding with right child
	temp_root->right = root;
	root = temp_root;
	SkewHeapNode *temp = root->right;
	root->right = root->left;
	root->left = temp;


}

int SkewHeap::extract_min(){
	SkewHeap *temp_heap = new SkewHeap();
	temp_heap->root = root->right;
	SkewHeapNode *min_pointer = root;

	int min = min_pointer->key;
	if (root->left)
		root = root->left;
	else{
		root = NULL;
		delete min_pointer;
		return min;
	}
	min_pointer->left = 0;
	min_pointer->right = 0;
	meld(temp_heap);
	delete min_pointer;

	return min;
}

SkewHeap::SkewHeap(const int k){
	root = new SkewHeapNode();
	root->key = k;
}

SkewHeap::SkewHeap(){
}

SkewHeap::~SkewHeap(){
	if (root)
		delete root;
}

