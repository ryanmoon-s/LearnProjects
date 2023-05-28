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
	RBNode* parent;  //Ƶ���͸��ڵ㽻��
	RBNode() {
		color = kRed;  //Ĭ��Ϊ��ɫ������Ǻ�ɫ�����ƻ����������
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	RBNode(int in_key, T in_data) :RBNode() {  //ί�й���
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
	RBNode<T>* root_;  //ͷ�ڵ㣬���洢���ݣ������ڵ����������Һ�����
	//����ڵ㣬��һ�ǵݹ��ã����ܱ�¶���û���
	void _InertNodeToTree(RBNode<T>* root, int key, T data);
	//�������и��ڵ㣬���ô�����
	void _Right(RBNode<T> * root);
	//����
	void _Left(RBNode<T> * root);

};

template<class T>
inline void RBTree<T>::Insert(int key, T data)
{
	//��֤���ڵ�Ϊ��ɫ
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
	//key��ȣ�data�滻����
	if (key == root->key) {
		root->data = data;
		return;
	}
	//key���ڣ����ҵݹ�Ѱ�Ҳ����
	else if (key > root->key) {
		if (root->right != nullptr) {  //�ݹ���� 
			_InertNodeToTree(root->right, key, data);
			if (root->right != nullptr && root->color == kRed && root->right->color == kRed) {  //�Һͺ��Ӷ��Ǻ�ɫ����������ϵ���������������ת�ˣ��ҿ���û�к���
				root->color = kBlack;
				root->parent->left->color = kBlack;
				if (root->parent->parent->parent != nullptr)
					root->parent->color = kRed;
			}
		}
		else {  //�ҵ�������
			root->right = new RBNode<T>(key, data);
			root->right->parent = root;  //���丸��
			//��������Ƿ���Ҫ����������Ĭ��Ϊ��ɫ
			if (root->color == kBlack)   //���Ǻ�ɫ�������ٵ���
				return;
			else {  
				if (root == root->parent->right) {  //���Ǹ��׵��Һ��ӣ����ҵ����
					if (root->parent->left != nullptr && root->parent->left->color == kRed) {  //�ֵܽڵ�Ϊ��ɫ��������ϵ���
						if (root->parent->parent->parent != nullptr)
							root->parent->color = kRed;
						root->color = kBlack;
						root->parent->left->color = kBlack;
						return;
					}
					_Left(root->parent);  //�Ƹ�������
					root->color = kBlack;  //����ɫ�ı�
					root->left->color = kRed;  //������ɫ�ı�  
					if (root->left->left != nullptr && root->left->left->color == kBlack)   //��תǰ���ֵܽڵ�Ϊ��ɫ������������
						root->right->color = kBlack;  //�Һ�����ɫ�ı�  
				}
				else {  //���ҵ����
					if (root->parent->right != nullptr && root->parent->right->color == kRed) {  //�ֵܽڵ�Ϊ��ɫ��������ϵ���
						if (root->parent->parent->parent != nullptr)
							root->parent->color = kRed;
						root->color = kBlack;
						root->parent->right->color = kBlack;
						return;
					}
					_Left(root);  //���Լ�����
					_Right(root->parent);   //�Ƹ�������ת
					root->color = kBlack;  //����ɫ�ı�
					root->right->color = kRed;  //�Һ�����ɫ�ı� 
					if (root->right->right!= nullptr && root->right->right->color == kBlack)   //�ֵܽڵ�Ϊ��ɫ
						root->left->color = kBlack;  //������ɫ�ı�
				}
			}
		}
	}
	//keyС�ڣ�����ݹ�Ѱ�Ҳ����
	else if (key < root->key) {
		if (root->left != nullptr) {  //�������²��� 
			_InertNodeToTree(root->left, key, data);
			if (root->left!= nullptr && root->color == kRed && root->left->color == kRed) {  //�Һͺ��Ӷ��Ǻ�ɫ����������ϵ��������
				root->color = kBlack;
				root->parent->right->color = kBlack;
				if (root->parent->parent->parent != nullptr)
					root->parent->color = kRed;
			}
		}
		else {  //�ҵ�������
			root->left = new RBNode<T>(key, data);
			root->left->parent = root;
			// ��������Ƿ���Ҫ����������Ĭ��Ϊ��ɫ
			if (root->color == kBlack)  //���Ǻ�ɫ�������ٵ���
				return;
			else {
				if (root == root->parent->left) {  //���Ǹ��׵����ӣ��������
					if (root->parent->right != nullptr && root->parent->right->color == kRed) {  //������ϵ���
						root->color = kBlack;
						root->parent->right->color = kBlack;
						if (root->parent->parent->parent != nullptr)
							root->parent->color = kRed;
						return;
					}
					_Right(root->parent);  //�Ƹ�������
					root->color = kBlack;
					root->right->color = kRed;
					if (root->right->right!= nullptr && root->right->right->color == kBlack)
						root->left->color = kBlack;
				}
				else {  //�������
					if (root->parent->right->color == kRed) {  //�ֵܽڵ�Ϊ��ɫ��������ϵ���
						if (root->parent->parent->parent != nullptr)
							root->parent->color = kRed;
						root->color = kBlack;
						root->parent->left->color = kBlack;
						return;
					}
					_Right(root);  //���Լ�����
					_Left(root->parent);   //�Ƹ�������
					root->color = kBlack;  //����ɫ�ı�
					root->left->color = kRed;  //�Һ�����ɫ�ı� 
					if (root->left->left!= nullptr && root->left->left->color == kBlack)   //�ֵܽڵ�Ϊ��ɫ
						root->right->color = kBlack;  //������ɫ�ı�
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
	//�������ӹ�ϵ
	if (tmp == tmp->parent->right)
		tmp->parent->right = root;
	else
		tmp->parent->left = root;
	root->parent = tmp->parent;
	tmp->parent = root;
	//��ת
	if (root->right == nullptr)   //�Һ���Ϊ�գ�ֱ��ת
		tmp->left = nullptr;
	else  //�Һ��Ӳ�Ϊ�գ���Ҫת�Ƶ�tmp
		tmp->left = root->right;
	root->right = tmp;
}

template<class T>
inline void RBTree<T>::_Left(RBNode<T>* root)
{
	RBNode<T>* tmp = root;
	root = tmp->right;
	//�������ӹ�ϵ
	if (tmp == tmp->parent->right)
		tmp->parent->right = root;
	else
		tmp->parent->left = root;
	root->parent = tmp->parent;
	tmp->parent = root;
	//��ת
	if (root->left == nullptr)
		tmp->right = nullptr;
	else
		tmp->right = root->left;
	root->left = tmp;
}

