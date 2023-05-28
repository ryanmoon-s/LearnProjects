#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 20 
//二叉树存储结构
typedef struct BinNode {
	char data;
	struct BinNode *LChild;
	struct BinNode *RChild;
}BinNode;
//线索二叉树存储结构
typedef struct ThBinNode {
	char data;
	unsigned int Ltag;  //为1时为线索，0时不是线索
	unsigned int Rtag;
	struct ThBinNode *LChild;
	struct ThBinNode *RChild;
}ThBinNode;
//哈夫曼树存储结构
typedef struct HuffBinNode {
	int weight;
	struct HuffBinNode *LChild;
	struct HuffBinNode *RChild;
}HuffBinNode;
//二叉树
void create_BinTree(BinNode **root, char *arr, int *i);   //创建
void pre_recu_BinTree(BinNode *root);   //先序递归遍历
void mid_recu_BinTree(BinNode *root);   //中序递归遍历
void post_recu_BinTree(BinNode *root);   //后序递归遍历
void pre_non_BinTree(BinNode *root);   //先序非递归遍历
void mid_non_BinTree(BinNode *root);   //中序非递归遍历
void post_non_BinTree(BinNode *root);   //后序非递归遍历
void level_trav_BinTree(BinNode *root);   //层次遍历
//线索二叉树
void create_ThBinTree(ThBinNode **root, char *arr, int *i);   //创建线索二叉树
void index_ThBinTree(ThBinNode **root);   //为线索二叉树建立先序索引
//哈夫曼树
int minofarr(HuffBinNode **arr, int n);  //获取weight最小的元素的下标值
void deleone(HuffBinNode **arr, int index, int *n);   //从数组中删除指定元素
HuffBinNode* create_huffTree(int *elem, int n);   //哈夫曼树的创建
void code_HuffTree(HuffBinNode *root, int depth);   //哈夫曼树递归编码，depth表示深度
int main()
{
	BinNode *bintree;
	int i = 0;
	char elem[21] = { 'A','B','D','H','\0','\0','I','\0','\0','E','J','\0','\0','\0','C','F','\0','\0','G','\0','\0' };
	create_BinTree(&bintree, elem, &i);  //创建
	printf("先序递归遍历：");
	pre_recu_BinTree(bintree);
	printf("\n");

	printf("中序递归遍历：");
	mid_recu_BinTree(bintree);
	printf("\n");

	printf("后序递归遍历：");
	post_recu_BinTree(bintree);
	printf("\n\n");

	printf("先序非递归遍历：");
	pre_non_BinTree(bintree);
	printf("\n");

	printf("中序非递归遍历：");
	mid_non_BinTree(bintree);
	printf("\n");

	printf("后序非递归遍历：");
	post_non_BinTree(bintree);
	printf("\n\n");

	printf("层次遍历：");
	level_trav_BinTree(bintree);
	printf("\n\n");

	//线索二叉树
	ThBinNode *thbintree;
	i = 0;
	create_ThBinTree(&thbintree, elem, &i);  //创建
	index_ThBinTree(&thbintree);  //建立先序索引
	int c = 2;
	//哈夫曼树
	HuffBinNode *huffbinnode;
	int huf[8] = { 8,5,7,2,12,6 };
	huffbinnode = create_huffTree(huf, 6);
	printf("哈夫曼树编码：\n");
	code_HuffTree(huffbinnode, 0);  //参二表示深度，根结点，深度为0
}


void create_BinTree(BinNode **root, char *arr, int *i) {
	if ('\0' == arr[*i]){
		*i += 1;
		*root = NULL;
		return;
	}else {
		BinNode *node = (BinNode*)malloc(sizeof(BinNode));
		*root = node;
		node->data = arr[*i];
		*i += 1;
		create_BinTree(&((*root)->LChild), arr, i);
		create_BinTree(&((*root)->RChild), arr, i);
	}
}

void pre_recu_BinTree(BinNode *root) {
	if (NULL == root)
		return;
	printf("%c ", root->data);
	pre_recu_BinTree(root->LChild);
	pre_recu_BinTree(root->RChild);
}

void mid_recu_BinTree(BinNode *root) {
	if (NULL == root)
		return;
	mid_recu_BinTree(root->LChild);
	printf("%c ", root->data);
	mid_recu_BinTree(root->RChild);
}

void post_recu_BinTree(BinNode *root) {
	if (NULL == root)
		return;
	post_recu_BinTree(root->LChild);
	post_recu_BinTree(root->RChild);
	printf("%c ", root->data);
}

void pre_non_BinTree(BinNode *root) {
	//用栈实现，访问后压栈，指向左。遇到NULL时就要出栈(指针回退，用栈才能实现)，并将指针指向它的右
	BinNode *p = root;
	BinNode *Stack[MAXSIZE];
	int top = -1;
	while ((p != NULL) || (top != -1)) {
		while (p != NULL) {  //遍历左子树，访问并压栈
			printf("%c ", p->data);
			Stack[++top] = p;
			p = p->LChild;
		}
		if (p == NULL) {  //指针回退
			p = Stack[top--];
			p = p->RChild;
		}
	}
}

void mid_non_BinTree(BinNode *root) {
	//和非递归先序思想一样，不过先序是先访问再入栈、中序是先出栈再访问
	BinNode *p = root;
	BinNode *Stack[MAXSIZE];
	int top = -1;
	while ((p != NULL) || (top != -1)) {
		while (p != NULL) {    //左子树压栈
			Stack[++top] = p;
			p = p->LChild;
		}
		if (p == NULL) {   //出栈，指针回退并访问
			p = Stack[top--];
			printf("%c ", p->data);
			p = p->RChild;
		}
	}
}

void post_non_BinTree(BinNode *root) {
	/*
	后序遍历方法：左 右 根
	可以按：根 右 左 的方式压入一个栈，再访问就是正常顺序
	而：根 右 左 这个顺序和先序的：根 左 右 方法一致，刚好反一个方向访问
	所以，按先序相反的顺序访问，把先序的访问动作变成压另一个栈，最后访问另一个栈即可
	*/
	BinNode *p = root;
	BinNode *Stack1[MAXSIZE];  //访问栈
	int top1 = -1;
	BinNode *Stack2[MAXSIZE];  //存入栈
	int top2 = -1;
	//访问并压入另一个栈
	while ((p != NULL) || (top1 != -1)) {
		while (p != NULL) {
			Stack2[++top2] = p;  //压入新栈
			Stack1[++top1] = p;  //和先序相反的压栈
			p = p->RChild;
		}
		if (p == NULL) {
			p = Stack1[top1--];
			p = p->LChild;
		}
	}
	//另一个栈出栈并访问
	while (top2 != -1) {
		printf("%c ", Stack2[top2--]->data);
	}
}

void level_trav_BinTree(BinNode *root) {
	//层次遍历用队列的性质  front out      ------      rear  in
	BinNode *Queue[MAXSIZE];
	int front = 0, rear = 0;
	Queue[rear++] = root;
	BinNode *p;  //遍历因子
	while (front != rear) {
		p = Queue[front++];
		printf("%c ", p->data);
		if (p->LChild != NULL) {
			Queue[rear++] = p->LChild;
		}
		if (p->RChild != NULL) {
			Queue[rear++] = p->RChild;
		}
	}
}

void create_ThBinTree(ThBinNode **root, char *arr, int *i) {
	if ('\0' == arr[*i]) {
		*i += 1;
		*root = NULL;
		return;
	}
	else {
		ThBinNode *node = (ThBinNode*)malloc(sizeof(ThBinNode));
		*root = node;
		node->data = arr[*i];
		*i += 1;
		create_ThBinTree(&((*root)->LChild), arr, i);
		create_ThBinTree(&((*root)->RChild), arr, i);
	}
}

void index_ThBinTree(ThBinNode **root) {
	ThBinNode *p = *root;
	//遍历栈
	ThBinNode *Stack[MAXSIZE];
	int top = -1;
	//成果栈
	ThBinNode *Stack2[MAXSIZE];
	int top2 = -1;
	while ((p != NULL) || (top != -1)) {
		while (p != NULL) {  
			//将原来的二叉树访问改成压入成果栈，将非纯性结构转变为纯性结构
			Stack2[++top2] = p;
			Stack[++top] = p;
			p = p->LChild;
		}
		if (p == NULL) { 
			p = Stack[top--];
			p = p->RChild;
		}
	}
	//建立索引
	int flag = 0;
	while (flag != top2) {
		//左索引
		if (Stack2[flag]->LChild == NULL) {
			Stack2[flag]->Ltag = 1;
			Stack2[flag]->LChild = Stack2[flag - 1];
		}else
			Stack2[flag]->Ltag = 0;
		//右索引
		if (Stack2[flag]->RChild == NULL) {
			Stack2[flag]->Rtag = 1;
			Stack2[flag]->RChild = Stack2[flag + 1];
		}
		else
			Stack2[flag]->Rtag = 0;
		flag++;
	}
	//为最后一个元素建立索引
	Stack2[flag]->Ltag = 1;
	Stack2[flag]->LChild = Stack2[flag - 1];
	Stack2[flag]->Rtag = 1;
	Stack2[flag]->RChild = NULL;
}

HuffBinNode* create_huffTree(int *elem, int n) { //n为数组元素个数
	HuffBinNode *root = NULL;
	int p;
	//为每个元素创建结点，并存入指针数组，后续只负责创建根结点与连接结点。
	//用顺序表加个下标来存每个结点指针，如果动态分配二维数组，只能看得见首地址，不方便断点检查
	HuffBinNode *NodeArr[MAXSIZE];  
	for (int i = 0; i < n; i++)
	{
		NodeArr[i] = (HuffBinNode*)malloc(sizeof(HuffBinNode));
		NodeArr[i]->weight = elem[i];
		NodeArr[i]->LChild = NULL;
		NodeArr[i]->RChild = NULL;
	}
	//从下往上构造
	while (1) { 
		root = (HuffBinNode*)malloc(sizeof(HuffBinNode));
		//左结  
		p = minofarr(NodeArr, n);  //找到weight最小的下标
		root->LChild = NodeArr[p];  //结在根左边
		root->weight = NodeArr[p]->weight;
		deleone(NodeArr, p, &n);  //表中删除结了的这个元素
		//右结
		p = minofarr(NodeArr, n);  //找到weight最小的下标
		root->RChild = NodeArr[p];   //结在根右边
		root->weight += NodeArr[p]->weight;
		deleone(NodeArr, p, &n);  //表中删除结了的这个元素
		//加入根
		if (n != 0)
			NodeArr[n++] = root;  //根加入数组，与其它结点同等竞争
		else
			break;
	}
	return root;
}

int minofarr(HuffBinNode **arr, int n) {  //返回值为weight最小那个结点所在的下标
	if (n == -1)
		exit(1);
	int temp = 0;
	for (int i = 1; i < n; i++)
	{
		if (arr[i]->weight < arr[temp]->weight) {
			temp = i;
		}
	}
	return temp;
}


void deleone(HuffBinNode **arr, int index,int *n) {  //删除指定下标的元素
	if (index == (*n) - 1)
		(*n)--;  //要加括号，否则歧义
	else { 
		for (int i = index; i < (*n) - 1; i++)
		{
			arr[i] = arr[i + 1];
		}
		(*n)--;
	}
}

void code_HuffTree(HuffBinNode *root, int depth) {  //depth为深度，每一层深度相同
	static int code[MAXSIZE];  //静态，不会随着重入而改变
	if (root == NULL)
		return;
	if ((root->LChild == NULL) && (root->RChild == NULL)) {
		//左右孩子为空，说明到底了，打印编码
		printf("权值为：%2d 的叶子的编码为：", root->weight);
		for (int i = 0; i < depth; i++)
		{ //打印至当前深度，当前深度以前的编码是一致的，本层编码取决于本身是左还是右孩子
			printf("%d", code[i]);
		}
		printf("\n");
		return;
	}
	else {
		//进入左右孩子，深度+1
		code[depth] = 0;
		code_HuffTree(root->LChild, depth + 1);
		//进入左右孩子，深度+1
		code[depth] = 1;
		code_HuffTree(root->RChild, depth + 1);

	}
}