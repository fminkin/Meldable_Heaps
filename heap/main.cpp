#include<ctime>
#include<set>
#include<queue>
#include"Heap_tests.hpp"

#include<functional>
using namespace std;
int main(){


	Test t(1e3);
	t.test_insert_extract();
	t.test_melding();

	system("pause");
	return 0;
}