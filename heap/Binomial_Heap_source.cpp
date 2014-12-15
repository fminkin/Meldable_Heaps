#include"Binomial_Heap.hpp"
#include<typeinfo>

using namespace std;
bad_cast unable_to_merge_exp;

IHeap* return_BHeap(){
	return new BHeap();
}

void BTree::link(BTree *z){
	sibling = z->child;
	z->child = this;
	z->degree = z->degree + 1;
}

BTree::BTree(){
	sibling = 0;
	child = 0;
	degree = 0;
	key = 0;
}

BTree::~BTree(){
	if (degree){
		if (sibling)
			delete sibling;
		if (child)
			delete child;
	}
}

BHeap::BHeap(){
}

BHeap::~BHeap(){
	if (head)
		delete head;
}

BTree* BHeap::GetMin(){
	BTree *y = 0, *x = head;
	int min;
	if (x){
		min = x->key; // mark first element as minimum
		y = x;
	}
	else
		return NULL;
	while (x != 0){
		if (x->key < min){
			y = x;
			min = x->key;
		}
		x = x->sibling;
	}//take minimum from root list	
	return y;
}

void BHeap::merge(BHeap *a){ // making a new root list from last and additional one
	BTree *first_list_iterator,
		*second_list_iterator,
		*main_iterator;
	first_list_iterator = head;
	second_list_iterator = a->head;
	if (head){  // choose head of new root list
		if (a->head){
			if (head->degree <= a->head->degree){
				first_list_iterator = head->sibling;
				main_iterator = head;
			}
			else {
				main_iterator = a->head;
				second_list_iterator = a->head->sibling;
			}
		}
		else {
			main_iterator = head;
			first_list_iterator = head->sibling;
		}
	}
	else {
		main_iterator = a->head;
		second_list_iterator = a->head->sibling;
		first_list_iterator = 0;
	}
	head = main_iterator;
	while (first_list_iterator != 0 || second_list_iterator != 0){ //changing other pointers of root list
		if (first_list_iterator != 0){
			if (second_list_iterator != 0){
				if (first_list_iterator->degree <= second_list_iterator->degree){
					main_iterator->sibling = first_list_iterator;
					main_iterator = main_iterator->sibling;
					first_list_iterator = first_list_iterator->sibling;
				}
				else{
					main_iterator->sibling = second_list_iterator;
					main_iterator = main_iterator->sibling;
					second_list_iterator = second_list_iterator->sibling;
				}
			}
			else{
				main_iterator->sibling = first_list_iterator;
				main_iterator = main_iterator->sibling;
				first_list_iterator = first_list_iterator->sibling;
			}
		}
		else{
			if (second_list_iterator != 0){
				main_iterator->sibling = second_list_iterator;
				main_iterator = main_iterator->sibling;
				second_list_iterator = second_list_iterator->sibling;
			}
		}
	}
}

void BHeap::meld(IHeap *casting_heap){
	if (dynamic_cast<BHeap *> (casting_heap) == NULL && casting_heap != 0)
		throw unable_to_merge_exp;
	BHeap *new_heap = dynamic_cast<BHeap *> (casting_heap);
	merge(new_heap); // make new 
	BTree *x, *next_x, *prev_x;
	prev_x = 0;
	x = head;
	if (head)
		next_x = x->sibling;
	else
		next_x = 0;
	while (next_x != 0){
		if (x->degree != next_x->degree || (next_x->sibling != 0 && next_x->sibling->degree == x->degree)){
			prev_x = x; // pointers move on
			x = next_x;
		}
		else if (x->key <= next_x->key){
			x->sibling = next_x->sibling;
			next_x->link(x); //linking next tree with previous
		}
		else{
			if (prev_x == 0){
				head = next_x;
			}
			else
				prev_x->sibling = next_x;
			x->link(next_x);//linking previous tree with next tree
			x = next_x;
		}
		next_x = x->sibling;
	}
}

void BHeap::insert(const int key){
	BHeap *H = new BHeap;
	H->head = new BTree;
	H->head->degree = 0;
	H->head->key = key;
	meld(H);
}

int BHeap::extract_min(){
	BTree *min_pointer = GetMin(), *x, *y, *z, *next_x;
	if (head != min_pointer){
		for (x = head; x->sibling != min_pointer; x = x->sibling){ // moving x to the last sibling before minimum pointer
		}
		x->sibling = min_pointer->sibling; // deleting min_pointer from the root list
	}
	else{
		head = min_pointer->sibling;
	}
	BHeap *H1 = new BHeap;
	for (x = min_pointer->child; x != 0 && x->sibling != 0; x = x->sibling){
	}
	H1->head = x;
	y = 0;
	x = min_pointer->child;
	while (x != 0){ //reversing list of childs
		z = x;
		x = x->sibling;
		z->sibling = y;
		y = z;
	}
	if (H1->head)
		meld(H1); //melding old heap without minimum and new heap which contains of min_pointer`s childs

	int key = min_pointer->key;
	min_pointer->sibling = 0;
	min_pointer->child = 0;
	delete min_pointer;
	return key;
}
