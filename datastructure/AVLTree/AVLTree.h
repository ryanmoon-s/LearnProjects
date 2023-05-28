#pragma once
/*
	防止头文件重复引入，等效于：
	#ifndef _AVLTREE_H_
	#define _AVLTREE_H_
	...
	#endif
*/

//节点数据结构
template<typename T>
struct TreeNode {
	T data;
	int height;
	TreeNode* pLeft;
	TreeNode* pRight;

	TreeNode(const T & data) {    //构造
		this->data = data;
		pLeft = pRight = nullptr;
		height = 1;    //默认为是0，没有左右孩子时，左右孩子高度为0
	}
};

//树类，有一个根节点成员
template<typename T>
class ALVTree {
public:
	ALVTree() { pRoot = nullptr; }
	~ALVTree() {}

	//插入节点，在外部看来，只需要把这个数甩给它，不关心它怎么插入
	void insertT(const T & data);     //减少值拷贝，加const安全
	void deleteT(const T & data);

private:
	TreeNode<T>* pRoot;
	/*
		作用：递归调整，所以必须要传入节点来递归。
		前面加_标记是私有
		本来是一级指针，所以要至少要声明为指针。还要修改它，变为这个指针的引用，函数里面直接修改这个指针
	*/
	void _insertNodeToTree(TreeNode<T>* & root, const T & data);  
	//获取节点高度
	int _getHeight(TreeNode<T>* pRoot);
	//左旋
	void _left(TreeNode<T>* & root);
	//右旋
	void _right(TreeNode<T>* & root);
	void _deleteNodeToTree(TreeNode<T>* & root, const T & data);
};

template<typename T>
inline void ALVTree<T>::insertT(const T & data)
{
	_insertNodeToTree(pRoot, data);
}

template<typename T>
inline void ALVTree<T>::deleteT(const T & data)
{
	_deleteNodeToTree(pRoot, data);
}

template<typename T>
inline void ALVTree<T>::_insertNodeToTree(TreeNode<T>* & root, const T & data)
{
	//1 以BST方式，从上而下递归插入
	if (root == nullptr) {
		root = new TreeNode<T>(data);    //已构造
		return;
	}
	else if (data > root->data) {
		_insertNodeToTree(root->pRight, data);
		//自下而上更新高度
		root->height = root->pRight->height + 1;
		//向右子树插入，右子树肯定比左子树高，检查高度差是否超过1
		//上一句递归向下进入，这一句是逐层向上返回，向上调整
		//不放在最下面的原因是：放在最下面，还要判断是这里哪个if进去的，即左右子树哪个树更高
		if (_getHeight(root->pRight) - _getHeight(root->pLeft) > 1) { 
			//判断是哪种不平衡导致的
			if (data > root->pRight->data) {
				//向右子树的右边跑了，左旋
				_left(root);
			}
			else {
				//向右子树的左边跑了，右左旋
				_right(root->pRight);
				_left(root);
			}
		}
	}
	else {
		_insertNodeToTree(root->pLeft, data);
		//自下而上更新高度
		root->height = root->pLeft->height + 1;
		//向左子树插入，左子树肯定比右子树高，检查高度差是否超过1
		if (_getHeight(root->pLeft) - _getHeight(root->pRight) > 1) {
			//判断是哪种不平衡导致的
			if (data < root->pLeft->data) {
				//向左子树的左边跑了，右旋
				_right(root);
			}
			else {
				//向左子树的右边跑了，左右旋
				_left(root->pLeft);
				_right(root);
			}
		}
	}
}

template<typename T>
inline int ALVTree<T>::_getHeight(TreeNode<T>* pRoot)
{
	if (pRoot == nullptr) {           //如果为空，返回高度0
		return 0;
	}
	return pRoot->height;
}

template<typename T>
inline void ALVTree<T>::_left(TreeNode<T>*& root)
{
	TreeNode<T>* temp = root;
	root = temp->pRight;
	if (!root->pLeft) {
		//root左边没值，直接连
		root->pLeft = temp;
		temp->pRight = nullptr;
	}
	else {
		//root左边有值，这个值要换转换到temp右边
		temp->pRight = root->pLeft;
		root->pLeft = temp;
	}
	//平衡高度
	//左旋转后，左边必定有节点
	root->pLeft->height = root->pRight->height;
}

template<typename T>
inline void ALVTree<T>::_right(TreeNode<T>*& root)
{
	TreeNode<T>* temp = root;
	root = temp->pLeft;
	if (!root->pRight) {
		//右边没值，直接转
		temp->pLeft = nullptr;
		root->pRight = temp;
	}
	else {
		//右边有值，这个值要转换到temp左边
		temp->pLeft = root->pRight;
		root->pRight= temp;
	}
	//平衡高度
	//右旋转后，右边必定有节点
	root->pRight->height = root->pLeft->height;
}

template<typename T>
inline void ALVTree<T>::_deleteNodeToTree(TreeNode<T>*& root, const T & data)
{
	if (root == nullptr) {
		return;
	}
	else if (root->data == data) {
		//相等，删除
		if (!(root->pLeft && root->pRight)) {
			//左右孩子都为空直接删除
			delete root;
			root = nullptr;
		}
		else {
			if (root->pLeft && !root->pRight) {
				//左孩子空，右孩子不空，右孩子连上来
				TreeNode<T>* temp = root;
				root = temp->pRight;
				delete temp;
				temp = nullptr;
			}
			else if (!root->pLeft && root->pRight) {
				//右孩子空，左孩子不空，左孩子连上来
				TreeNode<T>* temp = root;
				root = temp->pLeft;
				delete temp;
				temp = nullptr;
			}
			else {
				//左右孩子都有，在较高的树中删除
				if (_getHeight(root->pLeft) >= _getHeight(root->pRight)) {
					//左子树更高，删除左边最大的节点，值赋给根节点，并把它的父结节指向它的指针置null
					TreeNode<T>* temp1 = root; //temp1比tmep2慢一步，把指向删除节点的指针置null
					TreeNode<T>* temp2 = root->pLeft;
					while (temp2->pRight) {
						temp1 = temp2;
						temp2 = temp2->pRight;
					}
					root->data = temp2->data;
					if (root->height == 2)    //root是倒数第二层，特殊
						temp1->pLeft = nullptr;
					else
						temp1->pRight = nullptr;
					delete temp2;
					temp2 = nullptr;
				}
				else {
					//右子树更高，删除右边最小的节点，值赋给根节点，并把它的父结节指向它的指针置null
					TreeNode<T>* temp1 = root; //temp1比tmep2慢一步，把指向删除节点的指针置null
					TreeNode<T>* temp2 = root->pRight;
					while (temp2->pLeft) {
						temp1 = temp2;
						temp2 = temp2->pLeft;
					}
					root->data = temp2->data;
					if (root->height == 2)   //root是倒数第二层，特殊
						temp1->pRight = nullptr;
					else
						temp1->pLeft = nullptr;
					delete temp2;
					temp2 = nullptr;
				}
			}
		}
	}
	else if (data > root->data) {
		//大于，右递归找
		_deleteNodeToTree(root->pRight, data);
		//递归返回，看是否需要调整
		//自下而上更新高度，有可能删了下面一个节点，所以要判断它
		if (!root->pRight)
			root->height = 1;
		else
			root->height = root->pRight->height + 1;
		//在右子树删，右子树肯定比左子树矮，检查高度差是否超过1
		//上一句递归向下进入，这一句是逐层向上返回，向上调整
		//不放在最下面的原因是：放在最下面，还要判断是这里哪个if进去的，即左右子树哪个树更高
		if (_getHeight(root->pLeft) - _getHeight(root->pRight) > 1) {
			//右旋
			_right(root);
		}
	}
	else if (data < root->data) {
		//小于，左递归找
		_deleteNodeToTree(root->pLeft, data);
		//递归返回，看是否需要调整
		if (!root->pLeft)
			root->height = 1;
		else
			root->height = root->pLeft->height + 1;
		//在左子树删，左子树肯定比右子树矮，检查高度差是否超过1
		if (_getHeight(root->pRight) - _getHeight(root->pLeft) > 1) {
			//左旋
			_left(root);
		}
	}
}