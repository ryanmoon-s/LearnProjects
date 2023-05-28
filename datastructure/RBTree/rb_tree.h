#pragma once
enum Color {
	kRed,
	kBlack,
};

template <class T>
struct RBNode
{
	int key;
	T data;
	Color color;
	RBNode* left;
	RBNode* right;
	RBNode* parent;  //频繁和父节点交互
	RBNode() {
		color = kRed;  //默认为红色，如果是黑色，会破坏第五点条件
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	RBNode(int in_key, T in_data) :RBNode() {  //委托构造
		key = in_key;
		data = in_data;
	}
};

template <class T>
class RBTree {
public:
	RBTree() {
		root_ = new RBNode<T>();
	}

	void Insert(int key, T data);

private:
	RBNode<T>* root_;  //头节点，不存储数据，其它节点连在它的右孩子上
	//插入节点，参一是递归用，不能暴露给用户。
	void _InertNodeToTree(RBNode<T>* root, int key, T data);
	//右旋，有父节点，不用传引用
	void _Right(RBNode<T> * root);
	//左旋
	void _Left(RBNode<T> * root);

};

template<class T>
inline void RBTree<T>::Insert(int key, T data)
{
	//保证根节点为黑色
	if (root_->right == nullptr) {
		root_->right = new RBNode<T>(key, data);
		root_->right->color = kBlack;
		root_->right->parent = root_;
	}
	else {
		_InertNodeToTree(root_->right, key, data);
	}
}

template<class T>
inline void RBTree<T>::_InertNodeToTree(RBNode<T>* root, int key, T data)
{
	//key相等，data替换即可
	if (key == root->key) {
		root->data = data;
		return;
	}
	//key大于，向右递归寻找插入点
	else if (key > root->key) {
		if (root->right != nullptr) {  //递归查找 
			_InertNodeToTree(root->right, key, data);
			if (root->right != nullptr && root->color == kRed && root->right->color == kRed) {  //我和孩子都是红色，是逐层向上调整的情况，如果旋转了，我可能没有孩子
				root->color = kBlack;
				root->parent->left->color = kBlack;
				if (root->parent->parent->parent != nullptr)
					root->parent->color = kRed;
			}
		}
		else {  //找到，插入
			root->right = new RBNode<T>(key, data);
			root->right->parent = root;  //分配父亲
			//插入后检查是否需要调整，孩子默认为红色
			if (root->color == kBlack)   //我是黑色，不用再调整
				return;
			else {  
				if (root == root->parent->right) {  //我是父亲的右孩子，右右的情况
					if (root->parent->left != nullptr && root->parent->left->color == kRed) {  //兄弟节点为红色，逐层向上调整
						if (root->parent->parent->parent != nullptr)
							root->parent->color = kRed;
						root->color = kBlack;
						root->parent->left->color = kBlack;
						return;
					}
					_Left(root->parent);  //绕父亲左旋
					root->color = kBlack;  //我颜色改变
					root->left->color = kRed;  //左孩子颜色改变  
					if (root->left->left != nullptr && root->left->left->color == kBlack)   //旋转前的兄弟节点为黑色，现在是孙子
						root->right->color = kBlack;  //右孩子颜色改变  
				}
				else {  //左右的情况
					if (root->parent->right != nullptr && root->parent->right->color == kRed) {  //兄弟节点为红色，逐层向上调整
						if (root->parent->parent->parent != nullptr)
							root->parent->color = kRed;
						root->color = kBlack;
						root->parent->right->color = kBlack;
						return;
					}
					_Left(root);  //绕自己左旋
					_Right(root->parent);   //绕父亲右旋转
					root->color = kBlack;  //我颜色改变
					root->right->color = kRed;  //右孩子颜色改变 
					if (root->right->right!= nullptr && root->right->right->color == kBlack)   //兄弟节点为黑色
						root->left->color = kBlack;  //左孩子颜色改变
				}
			}
		}
	}
	//key小于，向左递归寻找插入点
	else if (key < root->key) {
		if (root->left != nullptr) {  //继续向下查找 
			_InertNodeToTree(root->left, key, data);
			if (root->left!= nullptr && root->color == kRed && root->left->color == kRed) {  //我和孩子都是红色，是逐层向上调整的情况
				root->color = kBlack;
				root->parent->right->color = kBlack;
				if (root->parent->parent->parent != nullptr)
					root->parent->color = kRed;
			}
		}
		else {  //找到，插入
			root->left = new RBNode<T>(key, data);
			root->left->parent = root;
			// 插入后检查是否需要调整，孩子默认为红色
			if (root->color == kBlack)  //我是黑色，不用再调整
				return;
			else {
				if (root == root->parent->left) {  //我是父亲的左孩子，左左情况
					if (root->parent->right != nullptr && root->parent->right->color == kRed) {  //逐层向上调整
						root->color = kBlack;
						root->parent->right->color = kBlack;
						if (root->parent->parent->parent != nullptr)
							root->parent->color = kRed;
						return;
					}
					_Right(root->parent);  //绕父亲右旋
					root->color = kBlack;
					root->right->color = kRed;
					if (root->right->right!= nullptr && root->right->right->color == kBlack)
						root->left->color = kBlack;
				}
				else {  //右左情况
					if (root->parent->right->color == kRed) {  //兄弟节点为红色，逐层向上调整
						if (root->parent->parent->parent != nullptr)
							root->parent->color = kRed;
						root->color = kBlack;
						root->parent->left->color = kBlack;
						return;
					}
					_Right(root);  //绕自己右旋
					_Left(root->parent);   //绕父亲左旋
					root->color = kBlack;  //我颜色改变
					root->left->color = kRed;  //右孩子颜色改变 
					if (root->left->left!= nullptr && root->left->left->color == kBlack)   //兄弟节点为黑色
						root->right->color = kBlack;  //左孩子颜色改变
				}
			}
		}
	}
}

template<class T>
inline void RBTree<T>::_Right(RBNode<T>* root)
{
	RBNode<T>* tmp = root;
	root = tmp->left;
	//建立父子关系
	if (tmp == tmp->parent->right)
		tmp->parent->right = root;
	else
		tmp->parent->left = root;
	root->parent = tmp->parent;
	tmp->parent = root;
	//旋转
	if (root->right == nullptr)   //右孩子为空，直接转
		tmp->left = nullptr;
	else  //右孩子不为空，需要转移到tmp
		tmp->left = root->right;
	root->right = tmp;
}

template<class T>
inline void RBTree<T>::_Left(RBNode<T>* root)
{
	RBNode<T>* tmp = root;
	root = tmp->right;
	//建立父子关系
	if (tmp == tmp->parent->right)
		tmp->parent->right = root;
	else
		tmp->parent->left = root;
	root->parent = tmp->parent;
	tmp->parent = root;
	//旋转
	if (root->left == nullptr)
		tmp->right = nullptr;
	else
		tmp->right = root->left;
	root->left = tmp;
}

