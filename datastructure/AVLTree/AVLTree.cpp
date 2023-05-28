#include <iostream>
#include "AVLTree.h"

int main()
{
	ALVTree<int> tree;
	for (int i = 1; i < 20; i++) {
		tree.insertT(i);
	}

//	tree.deleteT(16);
	tree.deleteT(9);
	tree.deleteT(11);

	while (1);
}
