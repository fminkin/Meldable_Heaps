#include"Heap_tests.hpp"
#include<ctime>
#include<algorithm>
#include<string>
#include<random>

std::default_random_engine generator;

Test::~Test(){
	heaps.clear();
};

Test::Test(size_t s){
	size = s;
	heaps.resize(3);
	heaps[0] = create_mergable_heap(MH_BHEAP);
	heaps[1] = create_mergable_heap(MH_LEFTIST);
	heaps[2] = create_mergable_heap(MH_SKEW);
}

void Test::test_insert_extract(){
	clock_t time;
	cout << "testing insert n-i\n";
	usual_insert(IN_MAX); // n-i
	cout << "testing extracts n-i\n";
	usual_extract(false);
	cout << endl;
	cout << "testing insert i+1\n";
	usual_insert(IN_MIN); // i+1
	cout << "testing extracts i+1\n";
	usual_extract(false);
	cout << endl;
	cout << "testing random shuffle inserts\n";
	shuffle.resize(size);
	for (size_t i = 0; i < size; i++)
		shuffle[i] = i + 1;
	random_shuffle(shuffle.begin(), shuffle.end());
	usual_insert(IN_SHUFFLE); // random shuffle 
	cout << "testing extracts of random shuffle\n";
	usual_extract(false);
	cout << "testing random sequence\n";
	uniform_int_distribution<int> rand_int(-INT_MAX, INT_MAX);
	for (size_t i = 0; i < size; i++)
		shuffle[i] = rand_int(generator);
	cout << "testing insert rand sequence\n";
	usual_insert(IN_SHUFFLE); // rand sequence

	sort(shuffle.begin(), shuffle.end());
	cout << "testing extracts rand sequence\n";
	usual_extract(true);

}

void Test::test_melding(){
	vector<IHeap*> test_vector(size);
	clock_t time;
	vector<list_of_heaps> order = { MH_BHEAP, MH_LEFTIST, MH_SKEW };
	for (size_t i = 0; i < 3; i++){
		test_vector.resize(size);
		for (size_t j = 0; j < size; j++){
			test_vector[j] = create_mergable_heap(order[i]);
			test_vector[j]->insert(j);
		}
		//after melding it must contain 1 to size ints
		size_t j = 0;
		time = clock();
		while (test_vector.size() != 1){
			try{
				test_vector[j]->meld(test_vector[j + 1]);
				test_vector[j + 1] = test_vector[test_vector.size() - 1];
				test_vector.pop_back();
			}
			catch (bad_cast){
				cout << "attempt to merge 2 unmergable heaps\n";
				break;
			}
		}
		time = clock() - time;
		//now it must contain 1 to size ints, check it;
		for (size_t j = 0; j < size; j++){
			if (test_vector[0]->extract_min() != j){
				cout << "INCORRECT MELDING\n";
				break;
			}
		}
		cout << typeid(*(test_vector[0])).name() << "`s melding time : " << static_cast<double>(time) / CLOCKS_PER_SEC << endl;
		test_vector.clear();
	}
}

void Test::usual_insert(cases a){
	bool ok = true;
	clock_t time;
	for (size_t i = 0; i < 3; i++){
		time = clock();
		for (size_t j = 0; j < size; j++){
			switch (a){
			case IN_MAX:{
							heaps[i]->insert(size - j);
							break;
			}
			case IN_MIN:{
							heaps[i]->insert(j + 1);
							break;
			}
			case IN_SHUFFLE:{
								heaps[i]->insert(shuffle[j]);
								break;
			}
			default:{
						heaps[i]->insert(j + 1);
						break;
			}
			}
		}
		time = clock() - time;
		cout << typeid(*heaps[i]).name() << "`s working time " << static_cast<double>(time) / CLOCKS_PER_SEC << endl;
		cout << endl;
	}
}

void Test::usual_extract(bool usual){
	bool ok = true;
	clock_t time;
	for (size_t i = 0; i < 3; i++){
		time = clock();
		for (size_t j = 0; j < size; j++){
			if (usual){
				int t = heaps[i]->extract_min();
				if (t != shuffle[j]){
					cout << typeid(*heaps[i]).name() << " works ";
					cout << "INCORRECT\n";
					ok = false;
					break;
				}
			}
			else
			if (heaps[i]->extract_min() != j + 1){
				cout << typeid(*heaps[i]).name() << " works ";
				cout << "INCORRECT\n";
				ok = false;
				break;
			}
		}
		if (ok)
			cout << typeid(*heaps[i]).name() << " works CORRECT\n";
		ok = true;
		time = clock() - time;
		cout << typeid(*heaps[i]).name() << "`s working time " << static_cast<double>(time) / CLOCKS_PER_SEC << endl;
		cout << endl;
	}
}
	