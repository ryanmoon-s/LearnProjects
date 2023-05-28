#include <iostream>
#include "BTree.h"

int main()
{
	//BTree<int> tree;
	//tree.insert(10, 1);
	//tree.insert(20, 2);
	//tree.insert(30, 3);

	//tree.insert(5, 4);
	//tree.insert(40, 5);
	//
	//tree.insert(15, 6);
	//tree.insert(18, 7);

	//tree.insert(35, 8);
	////tree.insert(16, 9);

	//int result;
	//bool ret = tree.search(6, result);

	////tree.deleteT(15);
	////tree.deleteT(5);
	////tree.deleteT(10);
	////tree.deleteT(30);
	//tree.deleteT(20);

	BTree<int> *tree = new BTree<int>();

	for (int i = 0; i < 5; i++) {
		tree->insert(i, i + 1);
	}
	
	delete tree;

	while (1);
}

