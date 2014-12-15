#pragma once

#include"Mergable_Heaps.hpp"
#include<vector>

enum cases{
	IN_SHUFFLE,
	IN_MAX,
	IN_MIN
};

class Test{
private:
	vector<int> shuffle;
	static const size_t default_size = 100000;
	void usual_insert(cases a);
	void usual_extract(bool usual);
public:
	vector<IHeap *> heaps;
	size_t size;
	~Test();
	Test(size_t s = Test::default_size);
	void test_melding();
	void test_insert_extract();
};
