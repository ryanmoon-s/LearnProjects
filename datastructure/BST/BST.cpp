#include <iostream>
using namespace std;
#define N 100
//二分查找树
struct BST_Node {
	int data;
	int count = 0;  //应对重复值
	struct BST_Node* left = NULL;
	struct BST_Node* right = NULL;
};

BST_Node* create_BST_Tree(int* arr, int n);
void insert_BST_Tree(BST_Node** root, int data);
bool search_BST_Tree(BST_Node* root, int val);
void delete_BST_Tree(BST_Node** root, int val);
int Max_Node(BST_Node** root);

int main() {
	int arr[N];
	for (int i = 0; i < N; i++) {
		arr[i] = rand() % 100 + 1;
		cout << arr[i] << " ";
	}
	BST_Node* root;
	root = create_BST_Tree(arr, N);
	bool ret = search_BST_Tree(root, 6);
	//delete_BST_Tree(&root, 1);

	system("pause");
}

BST_Node* create_BST_Tree(int* arr, int n) {
	//root
	BST_Node* root = new BST_Node;
	root->data = arr[0];
	root->count++;
	//other
	for (int i = 1; i < n; i++) {
		insert_BST_Tree(&root, arr[i]);
	}
	return root;
}

void insert_BST_Tree(BST_Node** root, int data) {
	//要对一个指针进行修改操作，且可能未分配内存，要传指针地址
	if (*root == NULL) {
		*root = new BST_Node;
		(*root)->count++;
		(*root)->data = data;
	}
	else if (data < (*root)->data) {
		insert_BST_Tree(&(*root)->left, data);
	}
	else if (data > (*root)->data) {
		insert_BST_Tree(&(*root)->right, data);
	}
	else if (data == (*root)->data) {
		(*root)->count++;
	}
}

bool search_BST_Tree(BST_Node* root, int val) {
	if (root == NULL) {
		return false;
	}
	if (root->data == val) {
		return true;
	}
	if (val < root->data) {
		return search_BST_Tree(root->left, val);
	}
	else if (val > root->data) {
		return search_BST_Tree(root->right, val);
	}
}

void delete_BST_Tree(BST_Node** root, int val) {
	//对一个指针进行修改操作，要修改指针本身内容，传指针地址
	if ((*root) == NULL) {
		return;
	}
	if ((*root)->data == val) {
		if ((*root)->left == NULL && (*root)->right == NULL) {
			//左右孩子为空，直接删
			delete (*root);
			*root = NULL;
			return;
		}
		else {
			(*root)->count--;
			//还有计数
			if ((*root)->count > 0) {
				return;
			}
			//没有计数，要删节点
			if ((*root)->left && (*root)->right) {
				//左右节点都有，找左子树最大的节点，给root，并删除
				(*root)->data = Max_Node(root);
			}
			else if ((*root)->left) {
				//左边没有，删除root，下面连接上来
				BST_Node* temp = *root;
				*root = (*root)->left;
				delete temp;
			}
			else if ((*root)->right) {
				//右边没有，删除root，下面连接上来
				BST_Node* temp = *root;
				*root = (*root)->right;
				delete temp;
			}
		}
	}
	if (val < (*root)->data) {
		return delete_BST_Tree(&(*root)->left, val);
	}
	else if (val > (*root)->data) {
		return delete_BST_Tree(&(*root)->right, val);
	}
}

int Max_Node(BST_Node** root) {
	//返回并删除节点，进行将指针变成NULL，传二级指针
	int ret;
	if ((*root)->right == NULL) {
		ret = (*root)->data;
		*root = NULL;
	}
	return ret;
}
