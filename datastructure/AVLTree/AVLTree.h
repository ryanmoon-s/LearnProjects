#pragma once
/*
	��ֹͷ�ļ��ظ����룬��Ч�ڣ�
	#ifndef _AVLTREE_H_
	#define _AVLTREE_H_
	...
	#endif
*/

//�ڵ����ݽṹ
template<typename T>
struct TreeNode {
	T data;
	int height;
	TreeNode* pLeft;
	TreeNode* pRight;

	TreeNode(const T & data) {    //����
		this->data = data;
		pLeft = pRight = nullptr;
		height = 1;    //Ĭ��Ϊ��0��û�����Һ���ʱ�����Һ��Ӹ߶�Ϊ0
	}
};

//���࣬��һ�����ڵ��Ա
template<typename T>
class ALVTree {
public:
	ALVTree() { pRoot = nullptr; }
	~ALVTree() {}

	//����ڵ㣬���ⲿ������ֻ��Ҫ�������˦����������������ô����
	void insertT(const T & data);     //����ֵ��������const��ȫ
	void deleteT(const T & data);

private:
	TreeNode<T>* pRoot;
	/*
		���ã��ݹ���������Ա���Ҫ����ڵ����ݹ顣
		ǰ���_�����˽��
		������һ��ָ�룬����Ҫ����Ҫ����Ϊָ�롣��Ҫ�޸�������Ϊ���ָ������ã���������ֱ���޸����ָ��
	*/
	void _insertNodeToTree(TreeNode<T>* & root, const T & data);  
	//��ȡ�ڵ�߶�
	int _getHeight(TreeNode<T>* pRoot);
	//����
	void _left(TreeNode<T>* & root);
	//����
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
	//1 ��BST��ʽ�����϶��µݹ����
	if (root == nullptr) {
		root = new TreeNode<T>(data);    //�ѹ���
		return;
	}
	else if (data > root->data) {
		_insertNodeToTree(root->pRight, data);
		//���¶��ϸ��¸߶�
		root->height = root->pRight->height + 1;
		//�����������룬�������϶����������ߣ����߶Ȳ��Ƿ񳬹�1
		//��һ��ݹ����½��룬��һ����������Ϸ��أ����ϵ���
		//�������������ԭ���ǣ����������棬��Ҫ�ж��������ĸ�if��ȥ�ģ������������ĸ�������
		if (_getHeight(root->pRight) - _getHeight(root->pLeft) > 1) { 
			//�ж������ֲ�ƽ�⵼�µ�
			if (data > root->pRight->data) {
				//�����������ұ����ˣ�����
				_left(root);
			}
			else {
				//����������������ˣ�������
				_right(root->pRight);
				_left(root);
			}
		}
	}
	else {
		_insertNodeToTree(root->pLeft, data);
		//���¶��ϸ��¸߶�
		root->height = root->pLeft->height + 1;
		//�����������룬�������϶����������ߣ����߶Ȳ��Ƿ񳬹�1
		if (_getHeight(root->pLeft) - _getHeight(root->pRight) > 1) {
			//�ж������ֲ�ƽ�⵼�µ�
			if (data < root->pLeft->data) {
				//����������������ˣ�����
				_right(root);
			}
			else {
				//�����������ұ����ˣ�������
				_left(root->pLeft);
				_right(root);
			}
		}
	}
}

template<typename T>
inline int ALVTree<T>::_getHeight(TreeNode<T>* pRoot)
{
	if (pRoot == nullptr) {           //���Ϊ�գ����ظ߶�0
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
		//root���ûֵ��ֱ����
		root->pLeft = temp;
		temp->pRight = nullptr;
	}
	else {
		//root�����ֵ�����ֵҪ��ת����temp�ұ�
		temp->pRight = root->pLeft;
		root->pLeft = temp;
	}
	//ƽ��߶�
	//����ת����߱ض��нڵ�
	root->pLeft->height = root->pRight->height;
}

template<typename T>
inline void ALVTree<T>::_right(TreeNode<T>*& root)
{
	TreeNode<T>* temp = root;
	root = temp->pLeft;
	if (!root->pRight) {
		//�ұ�ûֵ��ֱ��ת
		temp->pLeft = nullptr;
		root->pRight = temp;
	}
	else {
		//�ұ���ֵ�����ֵҪת����temp���
		temp->pLeft = root->pRight;
		root->pRight= temp;
	}
	//ƽ��߶�
	//����ת���ұ߱ض��нڵ�
	root->pRight->height = root->pLeft->height;
}

template<typename T>
inline void ALVTree<T>::_deleteNodeToTree(TreeNode<T>*& root, const T & data)
{
	if (root == nullptr) {
		return;
	}
	else if (root->data == data) {
		//��ȣ�ɾ��
		if (!(root->pLeft && root->pRight)) {
			//���Һ��Ӷ�Ϊ��ֱ��ɾ��
			delete root;
			root = nullptr;
		}
		else {
			if (root->pLeft && !root->pRight) {
				//���ӿգ��Һ��Ӳ��գ��Һ���������
				TreeNode<T>* temp = root;
				root = temp->pRight;
				delete temp;
				temp = nullptr;
			}
			else if (!root->pLeft && root->pRight) {
				//�Һ��ӿգ����Ӳ��գ�����������
				TreeNode<T>* temp = root;
				root = temp->pLeft;
				delete temp;
				temp = nullptr;
			}
			else {
				//���Һ��Ӷ��У��ڽϸߵ�����ɾ��
				if (_getHeight(root->pLeft) >= _getHeight(root->pRight)) {
					//���������ߣ�ɾ��������Ľڵ㣬ֵ�������ڵ㣬�������ĸ����ָ������ָ����null
					TreeNode<T>* temp1 = root; //temp1��tmep2��һ������ָ��ɾ���ڵ��ָ����null
					TreeNode<T>* temp2 = root->pLeft;
					while (temp2->pRight) {
						temp1 = temp2;
						temp2 = temp2->pRight;
					}
					root->data = temp2->data;
					if (root->height == 2)    //root�ǵ����ڶ��㣬����
						temp1->pLeft = nullptr;
					else
						temp1->pRight = nullptr;
					delete temp2;
					temp2 = nullptr;
				}
				else {
					//���������ߣ�ɾ���ұ���С�Ľڵ㣬ֵ�������ڵ㣬�������ĸ����ָ������ָ����null
					TreeNode<T>* temp1 = root; //temp1��tmep2��һ������ָ��ɾ���ڵ��ָ����null
					TreeNode<T>* temp2 = root->pRight;
					while (temp2->pLeft) {
						temp1 = temp2;
						temp2 = temp2->pLeft;
					}
					root->data = temp2->data;
					if (root->height == 2)   //root�ǵ����ڶ��㣬����
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
		//���ڣ��ҵݹ���
		_deleteNodeToTree(root->pRight, data);
		//�ݹ鷵�أ����Ƿ���Ҫ����
		//���¶��ϸ��¸߶ȣ��п���ɾ������һ���ڵ㣬����Ҫ�ж���
		if (!root->pRight)
			root->height = 1;
		else
			root->height = root->pRight->height + 1;
		//��������ɾ���������϶����������������߶Ȳ��Ƿ񳬹�1
		//��һ��ݹ����½��룬��һ����������Ϸ��أ����ϵ���
		//�������������ԭ���ǣ����������棬��Ҫ�ж��������ĸ�if��ȥ�ģ������������ĸ�������
		if (_getHeight(root->pLeft) - _getHeight(root->pRight) > 1) {
			//����
			_right(root);
		}
	}
	else if (data < root->data) {
		//С�ڣ���ݹ���
		_deleteNodeToTree(root->pLeft, data);
		//�ݹ鷵�أ����Ƿ���Ҫ����
		if (!root->pLeft)
			root->height = 1;
		else
			root->height = root->pLeft->height + 1;
		//��������ɾ���������϶����������������߶Ȳ��Ƿ񳬹�1
		if (_getHeight(root->pRight) - _getHeight(root->pLeft) > 1) {
			//����
			_left(root);
		}
	}
}