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
	Bnode<T>* parent;  //���ڵ�
	vector<Index_t<T> > index;   //����
	vector<Bnode<T>* > ptr;    //ָ���ӽڵ�
	Bnode(keyType key, T data) {
		parent = nullptr;
		this->index.push_back(Index_t<T>(key, data));
		ptr.push_back(nullptr);   //�����һ��ʱ�������պ���
		ptr.push_back(nullptr);
	}
};

template<typename T>
class BTree {
public:
	BTree() { pRoot = nullptr; }
	/*1 ���� 2 ����*/
	bool insert(keyType key, T data);     
	bool deleteT(keyType key);
	bool search(keyType key, T& data);   //Ҫ����ʵ�壬�����Ƿ��ҵ�������ҵ���ʵ���򱻸����ҵ���ֵ
	~BTree();
private:
	Bnode<T>* pRoot;
	void _insertNodeToTree(Bnode<T>* & root, keyType key, T data);
	void _separate(Bnode<T>* & root);  //����
	void _deleteNodeFromTree(Bnode<T>* & root, keyType key);
	void _deleteLeafNode(Bnode<T>* & root);
	bool _search(const Bnode<T>* root, keyType key, T& data);
	void _release(Bnode<T>* & root);
};

template<typename T>
inline bool BTree<T>::insert(keyType key, T data)
{
	if (_search(pRoot, key, data))   //����������У��Ͳ�����
		return false;
	_insertNodeToTree(pRoot, key, data);
	return true;
}

template<typename T>
inline bool BTree<T>::deleteT(keyType key)
{
	T data;
	if (!_search(pRoot, key, data))   //���������û�У��Ͳ�ɾ
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
	//1 Ϊ�գ��½��ڵ�
	if (!root) {
		root = new Bnode<T>(key, data);
		return;
	}

	//2 û�к��ӣ���Ҷ�ӽڵ㣬��������ʽ���ڱ���
	if (!root->ptr[0]) {
		//���Ҳ����
		auto iter = find_if(root->index.begin(), root->index.end(), [key](Index_t<T> index) {
			return index.key > key;
		});
		//����
		root->index.insert(iter, Index_t<T>(key, data));
		root->ptr.push_back(nullptr);  //Ҷ�ӽڵ㣬���Ӷ��ǿ�
	}
	//3 �к��ӣ��Ǹ��ڵ㣬�ҵ����ʵ�λ�õݹ���뺢�ӽڵ�
	else {
		int x = 0;   //��ǽ����ĸ�����
		//���Ҳ����
		auto iter = find_if(root->index.begin(), root->index.end(), [&x, key](Index_t<T> index) {
			if (index.key > key)
				return true;
			else {
				x++;
				return false;
			}
		});
		//����
		_insertNodeToTree(root->ptr[x], key, data);
	}

	//4 ���������������3����ô��Ҫ���ѡ�    �� 2 ����Ҷ�ӽڵ���ݽ���˲����� 3 ���Ը��ڵ���ݽ���˲�
	if (root->index.size() == 3) {
		_separate(root);
	}
}

template<typename T>
inline void BTree<T>::_separate(Bnode<T>*& root)
{
	//1 ������ڵ�Ϊ�ա�����Ϊ�գ���ô��Ҫ�½����ڵ�
	if (!root->parent || root->parent->index.empty()) {
		Bnode<T>* right = new Bnode<T>(root->index[2].key, root->index[2].data);  //�ұ߽ڵ���ѳ��½ڵ�
		Bnode<T>* parent = new Bnode<T>(root->index[1].key, root->index[1].data);  //�м�ڵ㹹�츸�ڵ�
		parent->ptr[0] = root;   //���ڵ���������ָ��ָ�������ڵ�
		parent->ptr[1] = right;
		root->parent = parent; //���ѵ㸸ָ��ָ����
		right->parent = parent;
		//�����ѷ��ѳ�ȥ������
		for (int i = 0; i < 2; i++) {
			root->index.pop_back();
			right->ptr[1 - i] = root->ptr[3 - i];    //����ǰ���ұ���������ָ���right
			if (right->ptr[1 - i])  //������Ӳ�Ϊ�գ�ҪΪ�����ĸ���
				right->ptr[1 - i]->parent = right;
			root->ptr.pop_back();
		}
		pRoot = parent;   //���ڵ����
	}
	//2 ���ڵ㲻Ϊ�գ��м�ڵ���뵽���ڵ㣬���ڵ㺢��ָ��ָ����ѽڵ㣬���������
	else {
		Index_t<T> middle(root->index[1].key, root->index[1].data);  //�м�ڵ����������븸�ڵ�
		//1 ����߷���
		if (root->index[0].key < root->parent->index[0].key) {
			Bnode<T>* left = new Bnode<T>(root->index[0].key, root->index[0].data);  //��߽ڵ���ѳ��½ڵ�
			root->parent->index.insert(root->parent->index.begin(), middle);  //�м�ڵ���븸�ڵ�
			Bnode<T>* temp = root;  //���ڵ�ĺ���ָ���ƶ�����ɣ��ҵ�root����ʧЧ
			root->parent->ptr.insert(root->parent->ptr.begin(), left);  //���ڵ�����ָ����ѵ�
			root = temp;
			left->parent = root->parent;  //���ѵ㸸ָ��ָ���ף���root���ѳ�ȥ�ģ�������һ������
			//�����ѷ��ѵ�����
			for (int i = 0; i < 2; i++) {
				root->index.erase(root->index.begin());
				left->ptr[i] = root->ptr[i];   //����ǰ�������������ָ���left
				if (left->ptr[i])  //������Ӳ�Ϊ�գ�ҪΪ�����ĸ���
					left->ptr[i]->parent = left;
				root->ptr.erase(root->ptr.begin());
			}
		}
		//2 ���ұ߷���
		else if (root->index[0].key > root->parent->index[0].key) {
			Bnode<T>* right = new Bnode<T>(root->index[2].key, root->index[2].data);  //�ұ߽ڵ���ѳ��½ڵ�
			root->parent->index.insert(root->parent->index.end(), middle);  //�м�ڵ���븸�ڵ�
			//���ڵ�ĺ���ָ���ƶ�����ɣ��ҵ�root����ʧЧ
			Bnode<T>* temp = root;
			root->parent->ptr.insert(root->parent->ptr.end(), right);  //���ڵ��Һ���ָ����ѵ�
			root = temp;
			right->parent = root->parent;  //���ѵ㸸ָ��ָ���ף���root���ѳ�ȥ�ģ�������һ������
			//�����ѷ��ѵ�����
			for (int i = 0; i < 2; i++) {
				root->index.pop_back();
				right->ptr[1 - i] = root->ptr[3 - i];   //����ǰ���ұ���������ָ���right
				if (right->ptr[1 - i])  //������Ӳ�Ϊ�գ�ҪΪ�����ĸ���
					right->ptr[1 - i]->parent = right;
				root->ptr.pop_back();
			}
		}
		//3 ���м����
		else {
			Bnode<T>* right = new Bnode<T>(root->index[2].key, root->index[2].data);  //�ұ߽ڵ���ѳ��½ڵ�
			root->parent->index.insert(root->parent->index.begin() + 1, middle);  //�м�ڵ���븸�ڵ�
			//���ڵ�ĺ���ָ���ƶ�����ɣ��ҵ�root����ʧЧ
			Bnode<T>* temp = root;
			root->parent->ptr.insert(root->parent->ptr.begin() + 2, right);  //���ڵ����������ָ����ѵ�
			root = temp;
			right->parent = root->parent;   //���ѵ㸸ָ��ָ���ף���root���ѳ�ȥ�ģ�������һ������
			//�����ѷ��ѵ�����
			for (int i = 0; i < 2; i++) {
				root->index.pop_back();
				right->ptr[1 - i] = root->ptr[3 - i];    //����ǰ���ұ���������ָ���right
				if (right->ptr[1 - i])  //������Ӳ�Ϊ�գ�ҪΪ�����ĸ���
					right->ptr[1 - i]->parent = right;
				root->ptr.pop_back();
			}
		}
	}
}

template<typename T>
inline void BTree<T>::_deleteNodeFromTree(Bnode<T>*& root, keyType key)
{
	//1 ����ڵ�Ϊ�գ�˵���ҵ�Ҷ�ӽڵ����£�return
	if (!root)
		return;

	//2 �������б�������
	auto it_equal = find_if(root->index.begin(), root->index.end(), [key](Index_t<T> index) {
		return index.key == key;
	});
	//�ҵ���ʵʩɾ��
	if (it_equal != root->index.end()) {
		if (root->ptr[0]) {  //�к��ӣ��Ǹ��ڵ㣬���������������������ֵ��������ڵ�
			Bnode<T>* temp = root->ptr[0];
			while (temp->ptr[0]) {  //�к��ӣ�����������
				temp = *(temp->ptr.end() - 1);
			}
			//ֵ����Ҫɾ��������
			if (key == root->index[0].key) //���ҵ�������
				*it_equal = *(temp->index.end() - 1);
			else { //���ҵ�������
				root->index[1] = root->index[0];
				root->index[0] = *(temp->index.end() - 1);
			}
			//�鿴temp������������
			if (temp->index.size() == 2) {   //�У�ֱ��ɾ��
				temp->index.pop_back();
				temp->ptr.pop_back();
			}
			else {
				//�ޣ�ɾ�����������ֵҶ�ӽڵ�
				_deleteLeafNode(temp);
			}
		}
		else {  //�޺��ӣ���Ҷ�ӽڵ�
			//�鿴root������������
			if (root->index.size() == 2) {   //�У�ֱ��ɾ��
				root->index.erase(it_equal);
				root->ptr.pop_back();
			}
			else {
				//�ޣ�ɾ��Ҷ�ӽڵ�
				_deleteLeafNode(root);
			}
		}
	}
	//δ�ҵ����ݹ�����ӽڵ�
	else {
		int x = 0;   //��ǽ����ĸ�����
		auto it_enter = find_if(root->index.begin(), root->index.end(), [&x, key](Index_t<T> index) {
			if (index.key > key)
				return true;
			else {
				x++;
				return false;
			}
		});
		//�ݹ�����ӽڵ�ɾ��
		_deleteNodeFromTree(root->ptr[x], key);
	}

	//3 �������Ϊ0��˵�����ӽڵ���������ѵ�һ��ɾ��������ڵ�Ҳ��Ҫɾ����
	if (root) {   //��root�Ž��룬û��root��˵���Ѿ�ɾ���˸��ڵ�
		if (root->index.size() == 0)
			_deleteLeafNode(root);
	}
}

template<typename T>
inline void BTree<T>::_deleteLeafNode(Bnode<T>*& root)
{
	Bnode<T>* parent = root->parent;
	Bnode<T>* brother;
	//1 û�и��ײ���û��������˵���Ѿ����������ڵ㣬����ֻ��һ�����ӽڵ㣬�����ĺ��������ڵ�
	if (!root->parent && root->index.empty()) {
		pRoot = root->ptr[0];   //�ú��ӵ���
		pRoot->parent = nullptr;  //�����󣬸�ָ����null
		return;
	}
	else if (!root->parent && !root->index.empty()) { //��������������ɾ�����ڵ㣬��ʱ��һ��Ԫ����
		delete root;
		root = nullptr;
		return;
	}

	int CompareKey;  //Ӧ��ɾ��Ҷ�����ϵ�������������ҵĺ��Ӱ��ҵ����������ֵ��ˣ���û��index�����ʻ����
	if (root->index.size() == 0)
		CompareKey = root->ptr[0]->index[0].key;  //��Ȼ���Ǹ��ڵ㣬һ���к��ӣ�ͨ�������ж϶����Ҹ��׵��ı�
	else
		CompareKey = root->index[0].key;
	if (CompareKey > (parent->index.end() - 1)->key) {  //�����ұߣ��ֵ��������
		brother = *(parent->ptr.end() - 2);
		//2 �ֵܽڵ��� 2 �������������ʵ��ֵܵ��������Ƶ����ڵ㣬���ڵ��������Ƶ����ڵ㣬����ɾ���ڵ㡣
		if (brother->index.size() == 2 && !brother->ptr[0]) {  //�ֵ���2������������û�к���
			if (!root->index.empty())
				root->index.pop_back();  //��������Ϊ��ʱ��ɾ����Ϊ���������ϵ�������
			root->index.push_back(*(parent->index.end() - 1));  //������������
			parent->index.pop_back(); //������ɾ��
			parent->index.push_back(brother->index[1]);  //�ֵ��������븸
			brother->index.pop_back();  //������ɾ��
			brother->ptr.pop_back();  //�������ı䣬ָ��ҲҪ��
		}
		//3 * �ֵܽڵ�� 1 ������
		else {
			brother->index.push_back(*(parent->index.end() - 1));  //���ڵ����������ֵ�
			parent->index.pop_back();  //������ɾ��
			if (root->ptr[0]) { //������к��ӣ��϶�ֻ��һ�����ӣ���ɾ����Ҷ�ӽڵ���ɵģ����ҵĺ��ӽ������ֵܽڵ�
				brother->ptr.push_back(root->ptr[0]);
				root->ptr[0]->parent = brother;  //���ĸ���
			}
			else
				brother->ptr.push_back(nullptr); // �������ı䣬ָ��ҲҪ��
			parent->ptr.pop_back();  //���ڵ�ɾ�����ҵ���ϵ����ǰ��ɾ�������ֵ���vector��ǰ�ƣ�������ȡ�ĵ�һ����Ա������ 
			delete root;  //�����ս�
			root = nullptr;
		}
	}
	else {  //������߻��м䣬�ֵ������ұ�
		int op;  //�������ڵ��ĸ�����
		if (CompareKey <= parent->index[0].key) {  //��������ߣ��ӵȺ���ɾ�����ڵ�ʱ��Ҷ�ӽڵ㸳ֵ�����ڵ㣬�������
			brother = parent->ptr[1];
			op = 0;
		}
		else {  //�����м�
			brother = parent->ptr[2];
			op = 1;
		}
		if (brother->index.size() == 2 && !brother->ptr[0]) {  //�ֵ�2����������û�к��ӣ�ΪҶ�ӽڵ�
			if (!root->index.empty())
				root->index.pop_back();  //��������Ϊ��ʱ��ɾ����Ϊ���������ϵ�������
			root->index.push_back(parent->index[op]);   //������������
			parent->index.erase(parent->index.begin() + op); //������ɾ��
			parent->index.insert(parent->index.begin(), brother->index[op]);  //�ֵ��������븸
			brother->index.erase(brother->index.begin());  //������ɾ��
			brother->ptr.pop_back();  //�������ı䣬ָ��ҲҪ��
		}
		else {  //�ֵ�ֻ��һ������
			brother->index.insert(brother->index.begin(), *(parent->index.begin() + op));  //���ڵ����������ֵ�
			parent->index.erase(parent->index.begin() + op);  //������ɾ��
			if (!root->ptr[0])
				brother->ptr.push_back(nullptr); // �������ı䣬ָ��ҲҪ��
			else { //������к��ӣ��϶�ֻ��һ�����ӣ���ɾ����Ҷ�ӽڵ���ɵģ����ҵĺ��ӽ������ֵܽڵ�
				brother->ptr.insert(brother->ptr.begin(), root->ptr[0]);
				root->ptr[0]->parent = brother;  //���ĸ���
			}
			delete root;  //�����ս�
			root = nullptr;
			parent->ptr.erase(parent->ptr.begin() + op); //���ڵ�ɾ�����ҵ���ϵ����ǰ��ɾ�������ֵ���vector��ǰ�ƣ�������ȡ�ĵ�һ����Ա������
		}
	}
	if (parent->index.size() == 0)    //�������û�������������ϵ�������ģ�
		_deleteLeafNode(parent);
	if (brother->index.size() == 3)   //����ֵ���3�����������ϵ���ʱ�����ӵģ���������
		_separate(brother);
}

template<typename T>
inline bool BTree<T>::_search(const Bnode<T>* root, keyType key, T& data)
{
	if (!root)
		return false;
	//�������б�������
	auto iter = find_if(root->index.begin(), root->index.end(), [key](Index_t<T> index) {
		return index.key == key;
	});
	//�ҵ�
	if (iter != root->index.end()) {
		data = iter->data;
		return true;
	}
	//δ�ҵ����ݹ�����ӽڵ�
	else {
		int x = 0;   //��ǽ����ĸ�����
		auto iter = find_if(root->index.begin(), root->index.end(), [&x, key](Index_t<T> index) {
			if (index.key > key)
				return true;
			else {
				x++;
				return false;
			}
		});
		//�ݹ�����ӽڵ�Ѱ��
		return _search(root->ptr[x], key, data);
	}
}

template<typename T>
inline void BTree<T>::_release(Bnode<T>*& root)
{
	if (root == nullptr)
		return;
	if (root->ptr[0] == nullptr) {  //Ҷ�ӽڵ�
		delete root;
		root = nullptr;
		return;
	}
	for_each(root->ptr.begin(), root->ptr.end(), [this](Bnode<T>* p_delete) {
		_release(p_delete);  //��Ա������Ҫ�󲶻�this
	});
}
