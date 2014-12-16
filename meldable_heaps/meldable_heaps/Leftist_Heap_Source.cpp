#include"Leftist_Heap.hpp"


using namespace std;


IHeap* return_LeftistHeap(){
	return new LeftistHeap();
}
//LeftistHeapNode methods
LeftistHeapNode::LeftistHeapNode(){
	right = NULL;
	left = NULL;
	rank = 0;
}
LeftistHeapNode::~LeftistHeapNode(){
	if (rank){
		if (right)
			delete right;
		if (left)
			delete left;
	}
}

void swap_nodes(LeftistHeapNode *a, LeftistHeapNode *b){ // swaping nodes function
	int temp = a->key;
	a->key = b->key;
	b->key = temp;

	LeftistHeapNode *temp_v;
	temp_v = a->left;
	a->left = b->left;
	b->left = temp_v;
	temp_v = a->right;
	a->right = b->right;
	b->right = temp_v;
	if (b->right){
		b->rank = b->right->rank + 1;
	}
	else
		b->rank = 1;
	if (a->right)
		a->rank = a->right->rank + 1;
	else
		a->rank = 1;
}

void LeftistHeap::insert(const int key){
	LeftistHeap *H = new LeftistHeap(key);
	meld(H);
}

void LeftistHeap::meld(IHeap *casting_heap){
	if (dynamic_cast<LeftistHeap *> (casting_heap) == NULL && casting_heap != 0)
		throw UnmergableHeapsException();

	LeftistHeap *new_heap = dynamic_cast<LeftistHeap *>(casting_heap);
	if (!root){
		root = new_heap->root;
		return;
	}
	if (!new_heap->root){
		return;
	}
	if (root->key > new_heap->root->key)
		swap_nodes(root, new_heap->root);

	LeftistHeapNode *temp_root = root;
	root = root->right;
	meld(new_heap); // melding with right child
	temp_root->right = root;
	root = temp_root;


	if (!root->left || root->left->rank < root->right->rank){ // rotate
		LeftistHeapNode *temp = root->right;
		root->right = root->left;
		root->left = temp;
	}
	//updating ranks
	if (root->right)
		root->rank = root->right->rank + 1;
	else
		root->rank = 1;
}

int LeftistHeap::extract_min(){
	LeftistHeap *temp_heap = new LeftistHeap();
	temp_heap->root = root->right;
	LeftistHeapNode *min_pointer = root;

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


LeftistHeap::LeftistHeap(){
}

LeftistHeap::LeftistHeap(const int k){
	root = new LeftistHeapNode();
	root->key = k;
}
LeftistHeap::~LeftistHeap(){
	if (root)
		delete root;
}

