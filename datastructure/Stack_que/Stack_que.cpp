#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 30
/*-----------------------------顺序结构------------------------------*/
//顺序栈存储结构
typedef struct LinearStack {
	int list[MAXSIZE];
	int top;
}LinearStack;
//顺序栈函数申明
void init_LinearStack(LinearStack* stack);   //初始化
void create_LinearStack(LinearStack* stack, int* arr, int n);   //创建
void push_LinearStack(LinearStack* stack, int val); ///入栈
int pop_LinearStack(LinearStack* stack);   //出栈
void ch_LinearStack(LinearStack* stack, int pos, int val);   //修改元素
int sea_LinearStack(LinearStack stack, int val);   //查找元素

//循环队列存储结构
typedef struct CircularQueue {
	int list[MAXSIZE];
	int front;
	int rear;
	int num;
}CircularQueue;
//循环队列函数申明
void init_CircularQueue(CircularQueue* queue);   //初始化
void create_CircularQueue(CircularQueue* queue, int* arr, int n);   //创建
void in_CircularQueue(CircularQueue* queue, int val);   //入队
int out_CircularQueue(CircularQueue* queue);   //出队
void ch_CircularQueue(CircularQueue* queue, int pos, int val);   //修改
int sea_CircularQueue(CircularQueue queue, int val);   //查找
/*-----------------------------链式结构------------------------------*/
//链栈存储结构
typedef struct node{ //结点
	struct node* next;
	int data;
}node;
typedef struct LinkStack { //链栈主体
	int num;
	node* top;
}LinkStack;
//链栈函数申明
void init_LinkStack(LinkStack* Lstack);   //初始化
void create_LinkStack(LinkStack* Lstack, int* arr, int n);   //创建
void push_LinkStack(LinkStack* Lstack, int val);   //入栈
int pop_LinkStack(LinkStack* Lstack);  //出栈
void ch_LinkStack(LinkStack *Lstack, int pos, int val);   //修改
int sea_LinkStack(LinkStack Lstack, int val);   //查找

//链队列存储结构
typedef struct Lode {  //链队列结点
	int data;
	struct Lode* next;
}Lnode;
typedef struct LinkQueue {  //链队列主体
	Lnode* front;
	Lnode* rear;
	int num;
}LinkQueue;
//链队列函数申明
void init_LinkQueue(LinkQueue* Lqueue);   //初始化
void create_LinkQueue(LinkQueue* Lqueue, int* arr, int n);   //创建
void in_LinkQueue(LinkQueue* Lqueue, int val);   //入队
int out_LinkQueue(LinkQueue* Lqueue);   //出队
void ch_LinkQueue(LinkQueue *Lqueue, int pos, int val);  //修改
int sea_LinkQueue(LinkQueue Lqueue, int val);   //查找
int main()
{
    //顺序栈
	LinearStack stack;
	init_LinearStack(&stack);
	int lis[10] = { 1,2,3,4,5,6,7,8,9,10 };
	create_LinearStack(&stack, lis, 10);  //1 2 3 4 5 6 7 8 9 10
	push_LinearStack(&stack, 50);  //1 2 3 4 5 6 7 8 9 10 50
	int pop_val = pop_LinearStack(&stack);  //1 2 3 4 5 6 7 8 9 10
	ch_LinearStack(&stack, 2, 250);  //1 250 3 4 5 6 7 8 9 10
	int ret_lis = sea_LinearStack(stack, 250);  //return 2
	//循环队列
	CircularQueue queue;
	init_CircularQueue(&queue);
	int liq[10] = { 1,2,3,4,5,6,7,8,9,10 };
	create_CircularQueue(&queue, liq, 10); //1 2 3 4 5 6 7 8 9 10
	for (int i = 1; i <= 9; i++)  //出队9个
	{
		out_CircularQueue(&queue); //---------10---
	}
	for (int i = 1; i <= 25; i++)  //入队25个
	{
		in_CircularQueue(&queue, i);
	}
	ch_CircularQueue(&queue, 2, 1000);  //5->10  6->1000
	int ret_liq = sea_CircularQueue(queue, 22);  //return 19
	//链栈
	LinkStack Lstack;
	init_LinkStack(&Lstack);
	int lns[10] = { 1,2,3,4,5,6,7,8,9,10 };
	create_LinkStack(&Lstack, lns, 10);
	for (int i = 1; i <= 5; i++) //入栈5个 1 2 3 ... 10 1 2 3 4 5
	{
		push_LinkStack(&Lstack, i);
	}
	for (int i = 0; i < 10; i++)  //出栈10个 1 2 3 4 5 
	{
		pop_LinkStack(&Lstack);
	}
	ch_LinkStack(&Lstack, 3, 500);  //1 2 500 4 5
	int ret_lns = sea_LinkStack(Lstack, 500);  //return 3
	//链队列
	LinkQueue Lqueue;
	init_LinkQueue(&Lqueue);
	int lnq[10] = { 1,2,3,4,5,6,7,8,9,10 };
	create_LinkQueue(&Lqueue, lnq, 10);  //1 2 3 ...10
	for (int i = 1; i <= 5; i++)  //入队5个 1 2 3 ...10 1 2 3 4 5
	{
		in_LinkQueue(&Lqueue, i);
	}
	for (int i = 0; i < 3; i++)  //出队3个 4 5 6 ...10 1 2 3 4 5
	{
		out_LinkQueue(&Lqueue);
	}
	ch_LinkQueue(&Lqueue, 3, 1000);  //7 8 9 10 1 2 3 4 5 4 5 1000
	int ret_lnq = sea_LinkQueue(Lqueue, 10);  //return 4
}

//顺序栈函数
void init_LinearStack(LinearStack* stack) {
	for (int i = 0; i < MAXSIZE; i++)
	{
		stack->list[i] = 0;
	}
	stack->top = -1;
}

void create_LinearStack(LinearStack* stack, int* arr, int n) {
	//个数是否合法
	if (n > MAXSIZE)
		return;
	for (int i = 0; i < n; i++)
	{
		stack->list[i] = arr[i];
		stack->top++;
	}
}

void push_LinearStack(LinearStack* stack, int val) {
	//栈满
	if (MAXSIZE - 1 == stack->top)
		return;
	//入栈
	stack->list[++stack->top] = val;
}

int pop_LinearStack(LinearStack* stack) {
	//栈空
	if (-1 == stack->top)
		exit(1);
	//出栈
	int temp = stack->list[stack->top];
	stack->list[stack->top--] = 0;
	return temp;
}

void ch_LinearStack(LinearStack* stack, int pos, int val) {  //pos表示从栈底数起的第几个
	//pos是否合法
	if ((pos < 0) || (pos > stack->top))
		return;
	//修改位置以上装入临时栈
	LinearStack Tstack;
	init_LinearStack(&Tstack);
	for (int i = stack->top; i >= pos; i--)
	{
		push_LinearStack(&Tstack, pop_LinearStack(stack));
	}
	//弹出修改元素，修改后装入
	int temp = pop_LinearStack(stack);
	temp = val;
	push_LinearStack(stack, temp);
	//临时栈还原
	for (int i = Tstack.top; i >= 0; i--)
	{
		push_LinearStack(stack, pop_LinearStack(&Tstack));
	}
}

int sea_LinearStack(LinearStack stack, int val) {  //返回从栈底开始数，满足的元素是第几个，失败返回-1
	//取元素判断，不满足则装入临时栈，直至满足或者栈空，不需要恢复栈。
	LinearStack Tstack;
	init_LinearStack(&Tstack);
	int times = stack.top;
	int pos = -1;
	for (int i = 0; i <= times; i++)
	{
		if (pop_LinearStack(&stack) == val) {
			pos = times - i + 1;
			break;
		}
	}
	return pos;
}

//循环队列函数
void init_CircularQueue(CircularQueue* queue) {
	for (int i = 0; i < MAXSIZE; i++)
	{
		queue->list[i] = 0;
	}
	queue->front = queue->rear = 0;
	queue->num = 0;
}

void create_CircularQueue(CircularQueue* queue, int* arr, int n) {
	//个数是否合法
	if (n > MAXSIZE)
		return;
	for (int i = 0; i < n; i++)
	{
		//尾指向下标增大的方向(保证头尾都在加，方便取余)     尾进，头出，rear-1有数据，front有数据
		queue->list[queue->rear] = arr[i];
		queue->rear = (queue->rear++) % MAXSIZE;
		queue->num++;
	}
}

void in_CircularQueue(CircularQueue* queue, int val) {
	//队满，牺牲一个位置不放数据
	if (queue->rear == queue->front - 1) {
		return;
	}
	//入队
	queue->list[queue->rear] = val;
	queue->rear = (queue->rear + 1) % MAXSIZE;
	queue->num++;
}

int out_CircularQueue(CircularQueue* queue) {
	//队空
	if (queue->rear == queue->front) {
		exit(1);
	}
	//出队
	int temp = queue->list[queue->front];
	queue->list[queue->front] = 0;
	queue->front = (queue->front + 1) % MAXSIZE;
	queue->num--;
	return temp;
}

void ch_CircularQueue(CircularQueue* queue, int pos, int val) {  //pos表示从front开始的位移量，队内第几个
	//出队的进队尾
	for (int i = 0; i < pos; i++)
	{
		if (i == pos - 1) {
			//修改值
			out_CircularQueue(queue);
			in_CircularQueue(queue, val);
		}
		in_CircularQueue(queue, out_CircularQueue(queue));
	}
}

int sea_CircularQueue(CircularQueue queue, int val) {
	//从front开始出队列，直到找到元素或者队列空 ，没找到返回-1，找到了返回相对于初始front的偏移量
	int temp, pos = 0;
	while (queue.rear != queue.front - 1) {
		temp = out_CircularQueue(&queue);
		if (temp == val) {
			return pos;
		}
		pos += 1;
	}
	return -1;
}

//链栈函数
void init_LinkStack(LinkStack* Lstack) {
	Lstack->top = NULL; //类似于顺序栈的-1
	Lstack->num = 0;
}

void create_LinkStack(LinkStack* Lstack, int* arr, int n) {
	node* block;
	for (int i = 0; i < n; i++)
	{
		block = (node*)malloc(sizeof(node));
		block->data = arr[i];
		block->next = Lstack->top;
		Lstack->top = block;
		Lstack->num++;
	}
}

void push_LinkStack(LinkStack* Lstack, int val) {
	//栈满，即内存不足
	node* block = NULL;
	block = (node*)malloc(sizeof(node));
	if (NULL == block) 
		return;
	//入栈
	block->data = val;
	block->next = Lstack->top;
	Lstack->top = block;
	Lstack->num++;
}

int pop_LinkStack(LinkStack* Lstack) {
	//栈空
	if (NULL == Lstack->top)
		exit(1);
	//出栈
	int temp = Lstack->top->data;
	node* freenode = Lstack->top;
	Lstack->top = Lstack->top->next;
	Lstack->num--;
	//free
	free(freenode);
	freenode = NULL;
	return temp;
}

void ch_LinkStack(LinkStack *Lstack, int pos, int val) {  //pos表示从栈底数出来第几个
	int number = Lstack->num;
	LinkStack tempstack;
	init_LinkStack(&tempstack);  //初始化
	//判断pos是否合法
	if ((pos <= 0) || (pos > number))
		return;
	//修改元素上面的元素全部存入临时栈
	for (int i = pos; i < number; i++)
	{
		push_LinkStack(&tempstack, pop_LinkStack(Lstack));
	}
	//弹出元素，将新结点入栈
	pop_LinkStack(Lstack);
	push_LinkStack(Lstack, val);
	//临时栈元素回栈
	int temp_num = tempstack.num;
	for (int i = 0; i < temp_num; i++)
	{
		push_LinkStack(Lstack, pop_LinkStack(&tempstack));
	}
}

int sea_LinkStack(LinkStack Lstack, int val) {
	//从栈顶出栈找，直接找到或者栈空，值传递，无需恢复栈，返回从栈顶到该值的深度，未找到返回-1
	int temp, pos = 1;
	while (NULL != Lstack.top) {
		temp = pop_LinkStack(&Lstack);
		if (temp == val) {
			return pos;
		}
		pos += 1;
	}
	return -1;
}

//链队列函数
void init_LinkQueue(LinkQueue* Lqueue) {
	//为front分配内存，作为头指针，front和rear都指向它，类似于循环队列它们都指向一个元素。
	//front上没有值，rear上有值。和循环队列相反
	Lqueue->front = (Lnode*)malloc(sizeof(Lnode));
	Lqueue->front->data = 0;
	Lqueue->front->next = NULL;
	Lqueue->num = 0;
	Lqueue->rear = Lqueue->front;
}

void create_LinkQueue(LinkQueue* Lqueue, int* arr, int n) {
	Lnode *block;
	for (int i = 0; i < n; i++)
	{
		block = (Lnode*)malloc(sizeof(Lnode));
		if (block == NULL)  //内存不足
			return;
		block->data = arr[i];
		block->next = NULL;
		Lqueue->rear->next = block;
		Lqueue->rear = block;
		Lqueue->num++;
	}
}

void in_LinkQueue(LinkQueue* Lqueue, int val) {
	Lnode *block;
	block = (Lnode*)malloc(sizeof(Lnode));
	//队列满，即内存不足
	if (NULL == block) 
		return;
	//入队
	block->data = val;
	block->next = NULL;
	Lqueue->rear->next = block;
	Lqueue->rear = block;
	Lqueue->num++;
}

int out_LinkQueue(LinkQueue* Lqueue) {
	//队列空
	if (Lqueue->front == Lqueue->rear)
		exit(1);
	//最后一个元素
	Lnode *freenode;
	if (Lqueue->front->next == Lqueue->rear) {
		freenode = Lqueue->rear;
		Lqueue->rear = Lqueue->front;
		Lqueue->front->next = NULL;
	}
	else {
		//非最后一个元素
		freenode = Lqueue->front->next;
		Lqueue->front->next = freenode->next;
	}
	int temp = freenode->data;
	free(freenode);
	freenode = NULL;
	Lqueue->num--;
	return temp;
}

void ch_LinkQueue(LinkQueue *Lqueue, int pos, int val) {  //pos表示相对于front的位移，第几个
	//判断pos是否合法
	if ((pos <= 0) || (pos > Lqueue->num))
		return;
	//pos前的元素出队头，入队尾
	for (int i = 0; i < pos - 1; i++)
	{
		in_LinkQueue(Lqueue, out_LinkQueue(Lqueue));
	}
	//待修改元素出队，修改值入队
	out_LinkQueue(Lqueue);
	in_LinkQueue(Lqueue, val);
}

int sea_LinkQueue(LinkQueue Lqueue, int val) {
	//从队头开始出队列，直到查到或者队空，返回该值相对于front的位移，失败返回-1
	int temp, pos = 1;
	while (Lqueue.front != Lqueue.rear) {
		temp = out_LinkQueue(&Lqueue);
		if (temp == val) {
			return pos;
		}
		pos++;
	}
	return -1;
}