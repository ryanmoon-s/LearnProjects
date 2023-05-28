#include "rb_tree.h"
#include <iostream>
using namespace std;

int main()
{
	RBTree<int> tree;

	for (int i = 10; i >= 1; i--) {
		tree.Insert(i, i);
	}

	system("pause");
}
