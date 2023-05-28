#pragma once
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
typedef int keyType;

template<typename T>
struct Index_t {
	keyType key;
	T data;
	Index_t(keyType key, T data):key(key), data(data) {}
};

template<typename T>
struct Bnode {
	Bnode<T>* parent;  //父节点
	vector<Index_t<T> > index;   //索引
	vector<Bnode<T>* > ptr;    //指向子节点
	Bnode(keyType key, T data) {
		parent = nullptr;
		this->index.push_back(Index_t<T>(key, data));
		ptr.push_back(nullptr);   //构造第一个时，两个空孩子
		ptr.push_back(nullptr);
	}
};

template<typename T>
class BTree {
public:
	BTree() { pRoot = nullptr; }
	/*1 索引 2 数据*/
	bool insert(keyType key, T data);     
	bool deleteT(keyType key);
	bool search(keyType key, T& data);   //要求传入实体，返回是否找到，如果找到，实体则被赋上找到的值
	~BTree();
private:
	Bnode<T>* pRoot;
	void _insertNodeToTree(Bnode<T>* & root, keyType key, T data);
	void _separate(Bnode<T>* & root);  //分裂
	void _deleteNodeFromTree(Bnode<T>* & root, keyType key);
	void _deleteLeafNode(Bnode<T>* & root);
	bool _search(const Bnode<T>* root, keyType key, T& data);
	void _release(Bnode<T>* & root);
};

template<typename T>
inline bool BTree<T>::insert(keyType key, T data)
{
	if (_search(pRoot, key, data))   //如果树里面有，就不插入
		return false;
	_insertNodeToTree(pRoot, key, data);
	return true;
}

template<typename T>
inline bool BTree<T>::deleteT(keyType key)
{
	T data;
	if (!_search(pRoot, key, data))   //如果树里面没有，就不删
		return false;
	_deleteNodeFromTree(pRoot, key);
	return true;
}

template<typename T>
inline bool BTree<T>::search(keyType key, T & data)
{
	return _search(pRoot, key, data);
}

template<typename T>
inline BTree<T>::~BTree()
{
	_release(pRoot);
}

template<typename T>
inline void BTree<T>::_insertNodeToTree(Bnode<T>*& root, keyType key, T data)
{
	//1 为空，新建节点
	if (!root) {
		root = new Bnode<T>(key, data);
		return;
	}

	//2 没有孩子，是叶子节点，以索引形式插在本层
	if (!root->ptr[0]) {
		//查找插入点
		auto iter = find_if(root->index.begin(), root->index.end(), [key](Index_t<T> index) {
			return index.key > key;
		});
		//插入
		root->index.insert(iter, Index_t<T>(key, data));
		root->ptr.push_back(nullptr);  //叶子节点，孩子都是空
	}
	//3 有孩子，是根节点，找到合适的位置递归插入孩子节点
	else {
		int x = 0;   //标记进入哪个孩子
		//查找插入点
		auto iter = find_if(root->index.begin(), root->index.end(), [&x, key](Index_t<T> index) {
			if (index.key > key)
				return true;
			else {
				x++;
				return false;
			}
		});
		//插入
		_insertNodeToTree(root->ptr[x], key, data);
	}

	//4 如果索引数量等于3，那么需要分裂。    第 2 步以叶子节点身份进入此步，第 3 步以根节点身份进入此步
	if (root->index.size() == 3) {
		_separate(root);
	}
}

template<typename T>
inline void BTree<T>::_separate(Bnode<T>*& root)
{
	//1 如果父节点为空、索引为空，那么就要新建根节点
	if (!root->parent || root->parent->index.empty()) {
		Bnode<T>* right = new Bnode<T>(root->index[2].key, root->index[2].data);  //右边节点分裂成新节点
		Bnode<T>* parent = new Bnode<T>(root->index[1].key, root->index[1].data);  //中间节点构造父节点
		parent->ptr[0] = root;   //父节点两个孩子指针指向两个节点
		parent->ptr[1] = right;
		root->parent = parent; //分裂点父指针指向父亲
		right->parent = parent;
		//除掉已分裂出去的数据
		for (int i = 0; i < 2; i++) {
			root->index.pop_back();
			right->ptr[1 - i] = root->ptr[3 - i];    //分裂前的右边两个孩子指针给right
			if (right->ptr[1 - i])  //如果孩子不为空，要为它更改父亲
				right->ptr[1 - i]->parent = right;
			root->ptr.pop_back();
		}
		pRoot = parent;   //根节点更新
	}
	//2 父节点不为空，中间节点插入到父节点，父节点孩子指针指向分裂节点，分三种情况
	else {
		Index_t<T> middle(root->index[1].key, root->index[1].data);  //中间节点变成索引插入父节点
		//1 从左边分裂
		if (root->index[0].key < root->parent->index[0].key) {
			Bnode<T>* left = new Bnode<T>(root->index[0].key, root->index[0].data);  //左边节点分裂成新节点
			root->parent->index.insert(root->parent->index.begin(), middle);  //中间节点插入父节点
			Bnode<T>* temp = root;  //父节点的孩子指针移动会造成，我的root引用失效
			root->parent->ptr.insert(root->parent->ptr.begin(), left);  //父节点左孩子指向分裂点
			root = temp;
			left->parent = root->parent;  //分裂点父指针指向父亲，从root分裂出去的，它们是一个父亲
			//除掉已分裂的数据
			for (int i = 0; i < 2; i++) {
				root->index.erase(root->index.begin());
				left->ptr[i] = root->ptr[i];   //分裂前的左边两个孩子指针给left
				if (left->ptr[i])  //如果孩子不为空，要为它更改父亲
					left->ptr[i]->parent = left;
				root->ptr.erase(root->ptr.begin());
			}
		}
		//2 从右边分裂
		else if (root->index[0].key > root->parent->index[0].key) {
			Bnode<T>* right = new Bnode<T>(root->index[2].key, root->index[2].data);  //右边节点分裂成新节点
			root->parent->index.insert(root->parent->index.end(), middle);  //中间节点插入父节点
			//父节点的孩子指针移动会造成，我的root引用失效
			Bnode<T>* temp = root;
			root->parent->ptr.insert(root->parent->ptr.end(), right);  //父节点右孩子指向分裂点
			root = temp;
			right->parent = root->parent;  //分裂点父指针指向父亲，从root分裂出去的，它们是一个父亲
			//除掉已分裂的数据
			for (int i = 0; i < 2; i++) {
				root->index.pop_back();
				right->ptr[1 - i] = root->ptr[3 - i];   //分裂前的右边两个孩子指针给right
				if (right->ptr[1 - i])  //如果孩子不为空，要为它更改父亲
					right->ptr[1 - i]->parent = right;
				root->ptr.pop_back();
			}
		}
		//3 从中间分裂
		else {
			Bnode<T>* right = new Bnode<T>(root->index[2].key, root->index[2].data);  //右边节点分裂成新节点
			root->parent->index.insert(root->parent->index.begin() + 1, middle);  //中间节点插入父节点
			//父节点的孩子指针移动会造成，我的root引用失效
			Bnode<T>* temp = root;
			root->parent->ptr.insert(root->parent->ptr.begin() + 2, right);  //父节点第三根孩子指向分裂点
			root = temp;
			right->parent = root->parent;   //分裂点父指针指向父亲，从root分裂出去的，它们是一个父亲
			//除掉已分裂的数据
			for (int i = 0; i < 2; i++) {
				root->index.pop_back();
				right->ptr[1 - i] = root->ptr[3 - i];    //分裂前的右边两个孩子指针给right
				if (right->ptr[1 - i])  //如果孩子不为空，要为它更改父亲
					right->ptr[1 - i]->parent = right;
				root->ptr.pop_back();
			}
		}
	}
}

template<typename T>
inline void BTree<T>::_deleteNodeFromTree(Bnode<T>*& root, keyType key)
{
	//1 如果节点为空，说明找到叶子节点以下，return
	if (!root)
		return;

	//2 在索引列表里面找
	auto it_equal = find_if(root->index.begin(), root->index.end(), [key](Index_t<T> index) {
		return index.key == key;
	});
	//找到，实施删除
	if (it_equal != root->index.end()) {
		if (root->ptr[0]) {  //有孩子，是父节点，找其左子树的最大索引，值赋给这个节点
			Bnode<T>* temp = root->ptr[0];
			while (temp->ptr[0]) {  //有孩子，继续向下找
				temp = *(temp->ptr.end() - 1);
			}
			//值赋给要删除的索引
			if (key == root->index[0].key) //是我的左索引
				*it_equal = *(temp->index.end() - 1);
			else { //是我的右索引
				root->index[1] = root->index[0];
				root->index[0] = *(temp->index.end() - 1);
			}
			//查看temp有无其它索引
			if (temp->index.size() == 2) {   //有，直接删除
				temp->index.pop_back();
				temp->ptr.pop_back();
			}
			else {
				//无，删除左子树最大值叶子节点
				_deleteLeafNode(temp);
			}
		}
		else {  //无孩子，是叶子节点
			//查看root有无其它索引
			if (root->index.size() == 2) {   //有，直接删除
				root->index.erase(it_equal);
				root->ptr.pop_back();
			}
			else {
				//无，删除叶子节点
				_deleteLeafNode(root);
			}
		}
	}
	//未找到，递归进入子节点
	else {
		int x = 0;   //标记进入哪个孩子
		auto it_enter = find_if(root->index.begin(), root->index.end(), [&x, key](Index_t<T> index) {
			if (index.key > key)
				return true;
			else {
				x++;
				return false;
			}
		});
		//递归进入子节点删除
		_deleteNodeFromTree(root->ptr[x], key);
	}

	//3 如果索引为0，说明是子节点进行了最难的一种删除，这个节点也需要删除。
	if (root) {   //有root才进入，没有root，说明已经删到了根节点
		if (root->index.size() == 0)
			_deleteLeafNode(root);
	}
}

template<typename T>
inline void BTree<T>::_deleteLeafNode(Bnode<T>*& root)
{
	Bnode<T>* parent = root->parent;
	Bnode<T>* brother;
	//1 没有父亲并且没有索引，说明已经调整至根节点，且它只有一个孩子节点，让它的孩子做根节点
	if (!root->parent && root->index.empty()) {
		pRoot = root->ptr[0];   //让孩子当根
		pRoot->parent = nullptr;  //当根后，父指针置null
		return;
	}
	else if (!root->parent && !root->index.empty()) { //有索引，就是在删除根节点，此时就一个元素了
		delete root;
		root = nullptr;
		return;
	}

	int CompareKey;  //应对删除叶子向上调整的情况，即我的孩子把我的索引给它兄弟了，我没有index，访问会出错
	if (root->index.size() == 0)
		CompareKey = root->ptr[0]->index[0].key;  //既然我是父节点，一定有孩子，通过孩子判断多在我父亲的哪边
	else
		CompareKey = root->index[0].key;
	if (CompareKey > (parent->index.end() - 1)->key) {  //我在右边，兄弟在我左边
		brother = *(parent->ptr.end() - 2);
		//2 兄弟节点有 2 个索引，将合适的兄弟的索引上移到父节点，父节点索引下移到本节点，不用删除节点。
		if (brother->index.size() == 2 && !brother->ptr[0]) {  //兄弟有2个索引，并且没有孩子
			if (!root->index.empty())
				root->index.pop_back();  //我索引不为空时，删除。为空则是向上调整所致
			root->index.push_back(*(parent->index.end() - 1));  //父索引进入我
			parent->index.pop_back(); //父索引删除
			parent->index.push_back(brother->index[1]);  //兄弟索引进入父
			brother->index.pop_back();  //兄索引删除
			brother->ptr.pop_back();  //索引数改变，指针也要变
		}
		//3 * 兄弟节点仅 1 个索引
		else {
			brother->index.push_back(*(parent->index.end() - 1));  //父节点索引进入兄弟
			parent->index.pop_back();  //父索引删除
			if (root->ptr[0]) { //如果我有孩子，肯定只有一个孩子，是删除我叶子节点造成的，把我的孩子交给我兄弟节点
				brother->ptr.push_back(root->ptr[0]);
				root->ptr[0]->parent = brother;  //更改父亲
			}
			else
				brother->ptr.push_back(nullptr); // 索引数改变，指针也要变
			parent->ptr.pop_back();  //父节点删除与我的联系，在前面删会引起兄弟在vector中前移，而我是取的第一个成员的引用 
			delete root;  //自我终结
			root = nullptr;
		}
	}
	else {  //我在左边或中间，兄弟在我右边
		int op;  //操作父节点哪个索引
		if (CompareKey <= parent->index[0].key) {  //我在最左边，加等号是删除父节点时，叶子节点赋值给父节点，它们相等
			brother = parent->ptr[1];
			op = 0;
		}
		else {  //我在中间
			brother = parent->ptr[2];
			op = 1;
		}
		if (brother->index.size() == 2 && !brother->ptr[0]) {  //兄弟2个索引，且没有孩子，为叶子节点
			if (!root->index.empty())
				root->index.pop_back();  //我索引不为空时，删除。为空则是向上调整所致
			root->index.push_back(parent->index[op]);   //父索引进入我
			parent->index.erase(parent->index.begin() + op); //父索引删除
			parent->index.insert(parent->index.begin(), brother->index[op]);  //兄弟索引进入父
			brother->index.erase(brother->index.begin());  //兄索引删除
			brother->ptr.pop_back();  //索引数改变，指针也要变
		}
		else {  //兄弟只有一个索引
			brother->index.insert(brother->index.begin(), *(parent->index.begin() + op));  //父节点索引进入兄弟
			parent->index.erase(parent->index.begin() + op);  //父索引删除
			if (!root->ptr[0])
				brother->ptr.push_back(nullptr); // 索引数改变，指针也要变
			else { //如果我有孩子，肯定只有一个孩子，是删除我叶子节点造成的，把我的孩子交给我兄弟节点
				brother->ptr.insert(brother->ptr.begin(), root->ptr[0]);
				root->ptr[0]->parent = brother;  //更改父亲
			}
			delete root;  //自我终结
			root = nullptr;
			parent->ptr.erase(parent->ptr.begin() + op); //父节点删除与我的联系，在前面删会引起兄弟在vector中前移，而我是取的第一个成员的引用
		}
	}
	if (parent->index.size() == 0)    //如果父亲没有索引，是向上调整引起的，
		_deleteLeafNode(parent);
	if (brother->index.size() == 3)   //如果兄弟有3个索引，向上调整时给它加的，让它分裂
		_separate(brother);
}

template<typename T>
inline bool BTree<T>::_search(const Bnode<T>* root, keyType key, T& data)
{
	if (!root)
		return false;
	//在索引列表里面找
	auto iter = find_if(root->index.begin(), root->index.end(), [key](Index_t<T> index) {
		return index.key == key;
	});
	//找到
	if (iter != root->index.end()) {
		data = iter->data;
		return true;
	}
	//未找到，递归进入子节点
	else {
		int x = 0;   //标记进入哪个孩子
		auto iter = find_if(root->index.begin(), root->index.end(), [&x, key](Index_t<T> index) {
			if (index.key > key)
				return true;
			else {
				x++;
				return false;
			}
		});
		//递归进入子节点寻找
		return _search(root->ptr[x], key, data);
	}
}

template<typename T>
inline void BTree<T>::_release(Bnode<T>*& root)
{
	if (root == nullptr)
		return;
	if (root->ptr[0] == nullptr) {  //叶子节点
		delete root;
		root = nullptr;
		return;
	}
	for_each(root->ptr.begin(), root->ptr.end(), [this](Bnode<T>* p_delete) {
		_release(p_delete);  //成员函数，要求捕获this
	});
}
