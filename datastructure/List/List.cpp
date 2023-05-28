#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 100

//顺序表存储结构
typedef struct LinearList {
	int list[MAXNUM];
	int last;
}LinearList;

//顺序表申明
void init_LinearList(LinearList* ListS);  //初始化
void create_LinearList(LinearList* ListS, int* arr, int n);  //创建
void insert_LinearList(LinearList* ListS, int pos, int val);   //插入
void del_LinearList(LinearList* ListS, int pos);   //删除
void ch_LinearList(LinearList* ListS, int pos, int val);   //修改
int sea_LinearList(LinearList ListS, int val);   //查找

//链表存储结构
typedef struct node {
	node* next;
	int data;
}LinkList;

//链表申明
void init_LinkList(LinkList** ListL);  //初始化
int getlen_Linklist(LinkList** ListL);   //获取链表长度
void create_LinkList(LinkList** ListL, int* arr, int n);   //创建
void insert_LinkList(LinkList** ListL, int pos, int val);   //插入
void del_LinkList(LinkList** ListL, int pos);   //删除
void ch_LinkList(LinkList** ListL, int pos, int val);   //修改
int sea_LinkList(LinkList* ListL, int val);   //查找
int main()
{
	//顺序表
	LinearList ListS;
	init_LinearList(&ListS);
	int Sarr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	create_LinearList(&ListS, Sarr, 10); //1 2 3 4 5 ...
	insert_LinearList(&ListS, 2, 50); //1 50 2 3 4 ...
	del_LinearList(&ListS, 3); //1 50 3 4 ...
	ch_LinearList(&ListS, 3, 100);  //1 50 100 4 5 ...
	int ret = sea_LinearList(ListS, 50); //return 2

	//链表
	LinkList* head = NULL;
	int Larr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	init_LinkList(&head);
	create_LinkList(&head, Larr, 10); //10 9 8 7  ...
	insert_LinkList(&head, 2, 50);  //10 50 9 8 7 ...
	del_LinkList(&head, 3);  //10 50 8 7 6 ...
	ch_LinkList(&head, 3, 100);  //10 50 100 7 6 5 ...
	int ret1 = sea_LinkList(head, 50); //return 2
}

//顺序表函数
void init_LinearList(LinearList* ListS) {
	for (int i = 0; i < MAXNUM; i++)
	{
		ListS->list[i] = 0;
	}
	ListS->last = -1;
}

void create_LinearList(LinearList* ListS, int* arr, int n) {
	for (int i = 0; i < n; i++)
	{
		ListS->list[i] = arr[i];
	}
	ListS->last = n-1;
}

void insert_LinearList(LinearList* ListS, int pos, int val) {  //pos表示第几个
	//满了
	if ((MAXNUM - 1) == ListS->last)
		return;
	//pos是否合法
	if ((pos < 1) || (pos > ListS->last + 1))
		return;
	//插入
	for (int i = ListS->last; i >= pos - 1; i--)
	{
		ListS->list[i + 1] = ListS->list[i];
	}
	ListS->list[pos - 1] = val;
	ListS->last += 1;
}

void del_LinearList(LinearList* ListS, int pos) {
	//空了
	if (-1 == ListS->last)
		return;
	//pos是否合法
	if ((pos < 1) || (pos > ListS->last + 1))
		return;
	//删除
	for (int i = pos - 1; i <= ListS->last; i++)
	{
		ListS->list[i] = ListS->list[i + 1];
	}
	ListS->last -= 1;
}

void ch_LinearList(LinearList* ListS, int pos, int val) {  //pos表示是第几个
	//pos是否合法
	if ((pos < 1) || (pos > ListS->last + 1))
		return;
	ListS->list[pos - 1] = val;
}

int sea_LinearList(LinearList ListS, int val) {  //返回该值是第几个，没找到返回-1
	if (-1 == ListS.last)
		return -1;
	for (int i = 0; i <= ListS.last; i++)
	{
		if (ListS.list[i] == val) {
			return i + 1;
		}
	}
	return -1;
}

//链表函数
void init_LinkList(LinkList** ListL) {
	//ListL接收一个LinkList类型的指针，为其申请内存
	*ListL = (LinkList*)malloc(sizeof(LinkList));
	(*ListL)->data = 0;
	(*ListL)->next = NULL;
}

void create_LinkList(LinkList** ListL, int* arr, int n) {
	LinkList* node = NULL;
	for (int i = 0; i < n; i++)
	{
		node = (LinkList*)malloc(sizeof(LinkList));
		node->data = arr[i];
		//头插法
		node->next = (*ListL)->next;
		(*ListL)->next = node;
	}
}

int getlen_Linklist(LinkList** ListL) {
	//获取链表长度
	int len = 0;
	LinkList* iterator = (*ListL);
	while (NULL != iterator->next) {
		iterator = iterator->next;
		len += 1;
	}
	return len;
}


void insert_LinkList(LinkList** ListL, int pos, int val) {  //pos表示第几个
	//pos值判断
	if ((pos < 1) || (pos > getlen_Linklist(ListL)))
		return;
	//找插入位置前一个结点
	LinkList* leftnode = (*ListL);
	for (int i = 0; i < pos -1; i++)
	{
		leftnode = leftnode->next;
	}
	//插入
	LinkList* insertnode = (LinkList*)malloc(sizeof(LinkList));
	insertnode->data = val;
	insertnode->next = leftnode->next;
	leftnode->next = insertnode;
}

void del_LinkList(LinkList** ListL, int pos) {
	//pos值判断
	if ((pos < 1) || (pos > getlen_Linklist(ListL)))
		return;
	//找删除位置前一个结点
	LinkList* leftnode = (*ListL);
	for (int i = 0; i < pos - 1; i++)
	{
		leftnode = leftnode->next;
	}
	//删除
	LinkList* freenode = leftnode->next;
	leftnode->next = leftnode->next->next;
	free(freenode);
	freenode = NULL;
}

void ch_LinkList(LinkList** ListL, int pos, int val) {
	//pos值判断
	if ((pos < 1) || (pos > getlen_Linklist(ListL)))
		return;
	//找修改位置前一个结点
	LinkList* leftnode = (*ListL);
	for (int i = 0; i < pos - 1; i++)
	{
		leftnode = leftnode->next;
	}
	//修改
	leftnode->next->data = val;
}

int sea_LinkList(LinkList* ListL, int val) {  //返回是第几个结点，没找到返回 -1
	int len = getlen_Linklist(&ListL);
	//查找
	int pos = 0;
	LinkList* iterator = (ListL);
	while (NULL != iterator->next) {
		iterator = iterator->next;
		pos += 1;
		if (iterator->data == val) {
			return pos;
		}
	}
	return -1;
}