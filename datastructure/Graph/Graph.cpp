#include <stdio.h>
#include <stdlib.h>
#define MAXNODE 10
#define INFINITE 50000
//图的邻接矩阵存储结构
typedef struct GraphMatrix {
	int num;  //顶点数
	char vertex[MAXNODE];  //顶点
	int matrix[MAXNODE][MAXNODE];   //矩阵
}GraphMatrix;
void init_GraphMatrix(GraphMatrix **graph);   //初始化
void create_GraphMatrix(GraphMatrix **graph, char* ver, int *mat, int vernum, int group);   //创建
//图的邻接表存储结构
typedef struct GraphNode {//后继结点
	int no;
	struct GraphNode *next;
}GraphNode;
typedef struct GraphHeadNode {//头结点
	int no;
	char vertex;
	GraphNode *next;
}GraphHeadNode;
typedef struct GraphList {//邻接表
	int num;
	GraphHeadNode *list[MAXNODE];
}GraphList;
void init_GraphList(GraphList **graph);   //初始化
void create_GraphList(GraphList **graph, char* ver, int *mat, int vernum, int group);   //创建
//深度优先遍历(邻接表)
void depGraph(GraphList *graph, int *visited, int id);  //递归函数
void Depth_List_Graph(GraphList *graph);   //遍历起始函数
//广度优先遍历(邻接表)
void breGraph(GraphList *graph, int *visited, int id);  //遍历函数
void Breadth_List_Graph(GraphList *graph);  //起始函数
//最小生成树(邻接矩阵)
GraphMatrix* Prim_Graph_Matrix(GraphMatrix *graph, int begin);  //Prim算法
//最短路径(邻接矩阵)
void Dijkstra_Graph_Matrix(GraphMatrix *graph, int begin);  //Dijkstra算法
//拓扑排序
int Topsort_Graph_List(GraphList *graph);    //成功返回1，失败返回0
int main() {
	//邻接矩阵
	GraphMatrix *graph;
	init_GraphMatrix(&graph);
	char vertex[6] = { 'A', 'B','C', 'D' ,'E', 'F' };
	int matrix[48] = { 0,1,1,0,4,4,0,2,2,1,0,1,1,3,3,2,0,2,2,3,2,2,4,3,2,5,5,3,1,3,3,2,2,3,5,4,4,0,4,4,2,3,5,2,5,5,3,4 };
	create_GraphMatrix(&graph, vertex, matrix, 6, 16);  //图 顶点数组 矩阵数组 顶点数 矩阵的组数(v1 v2 w)
	//邻接表
	GraphList *graph2;
	init_GraphList(&graph2);
	char vertex2[6] = { 'A', 'B','C', 'D' ,'E', 'F' };
	int matrix2[32] = { 0,1,0,4,0,2,1,0,1,3,2,0,2,3,2,4,2,5,3,1,3,2,3,5,4,0,4,2,5,2,5,3 };
	create_GraphList(&graph2, vertex2, matrix2, 6, 16);
	//深度优先遍历(邻接表形式)
	printf("深度优先遍历(邻接表形式)：");
	Depth_List_Graph(graph2);
	printf("\n");
	//广度优先遍历(邻接表形式)
	printf("广度优先遍历(邻接表形式)：");
	Breadth_List_Graph(graph2);
	printf("\n");
	//最小生成树(邻接矩阵)
	GraphMatrix *tree;
	tree = Prim_Graph_Matrix(graph, 0); //传入图、起始生成点的下标
	//最短路径(邻接矩阵)
	GraphMatrix *graph_de;
	init_GraphMatrix(&graph_de); 
	char vertex3[6] = { '0', '1','2', '3' ,'4','5' };
	int matrix3[33] = {0,1,5,0,2,30,0,3,35,1,2,24,1,4,29,1,5,10,2,5,17,3,0,15,4,5,25,5,3,8,5,4,12};
	create_GraphMatrix(&graph_de, vertex3, matrix3, 6, 11); //生成有向图(邻接矩阵)
	Dijkstra_Graph_Matrix(graph_de, 0);  //生成最短路径
	printf("\n");
	//拓扑排序
	GraphList *graph_top;
	init_GraphList(&graph_top);
	char vertex4[6] = { 'A', 'B','C', 'D' ,'E', 'F' };
	int matrix4[18] = { 0,1,0,2,0,3,1,2,1,4,1,5,2,5,4,5,5,3};
	create_GraphList(&graph_top, vertex4, matrix4, 6, 9);  //生成有向图(邻接表)
	int ret = Topsort_Graph_List(graph_top);

}

void init_GraphMatrix(GraphMatrix **graph) {
	*graph = (GraphMatrix*)malloc(sizeof(GraphMatrix));
	(*graph)->num = 0;
	for (int i = 0; i < MAXNODE; i++)
	{
		for (int j = 0; j < MAXNODE; j++)
		{
			(*graph)->matrix[i][j] = INFINITE;  //默认无穷
		}
		(*graph)->vertex[i] = '\0';
	}
	//自己与自己的距离设为0
	for (int i = 0; i < MAXNODE; i++)
	{
		for (int j = 0; j < MAXNODE; j++)
		{
			if (i == j)
				(*graph)->matrix[i][j] = 0;
		}
	}
}

void create_GraphMatrix(GraphMatrix **graph, char* ver, int *mat, int vernum, int group) {
	int v1, v2, we;
	//为顶点赋值
	for (int i = 0; i < vernum; i++)
	{
		(*graph)->vertex[i] = ver[i];
	}
	//为顶点数赋值
	(*graph)->num = vernum;
	//为矩阵赋值
	for (int i = 0; i < group; i++)
	{
		//取值
		v1 = mat[i * 3 + 0];
		v2 = mat[i * 3 + 1];
		we = mat[i * 3 + 2];
		//赋值
		(*graph)->matrix[v1][v2] = we;
	}
}

void init_GraphList(GraphList **graph) {
	*graph = (GraphList*)malloc(sizeof(GraphList));
	for (int i = 0; i < MAXNODE; i++)
	{
		(*graph)->list[i] = NULL;
	}
	(*graph)->num = 0;
}

void create_GraphList(GraphList **graph, char* ver, int *mat, int vernum, int group) {
	GraphNode *node;
	GraphHeadNode *head;
	(*graph)->num = vernum;
	//创建头结点并装入表
	for (int i = 0; i < vernum; i++)
	{
		head = (GraphHeadNode*)malloc(sizeof(GraphHeadNode));
		head->no = i;
		head->vertex = ver[i];
		head->next = NULL;
		(*graph)->list[i] = head;
	}
	//为表中每个头结点链接后继结点
	for (int ind = 0; ind < vernum; ind++)  //每个头结点
	{
		for (int i = 0; i < group; i++)  //在矩阵中找头结点的后继结点
		{
			if (mat[i*2] == ind) {  //找到这个头结点的后继结点
				//赋值
				node = (GraphNode*)malloc(sizeof(GraphNode));
				node->no = mat[i * 2 + 1];
				//头插
				node->next = (*graph)->list[ind]->next;
				(*graph)->list[ind]->next = node;
			}
		}
	}
}

void depGraph(GraphList *graph, int *visited, int id) {
	//类似于二叉树的先序递归遍历，一直递归深入到都被访问过，才回到调用处对下个结点进行递归
	visited[id] = 1;
	printf("%c ", graph->list[id]->vertex);
	//头结点的以后的所有结点：如果没访问就递归访问(进入该点的头结点)
	GraphNode *temp = graph->list[id]->next;
	while (NULL != temp) {
		//该结点的下个结点未被访问过，递归进入下个结点的头结点
		if (!visited[temp->no])
			depGraph(graph, visited, temp->no);
		//回到调用点后再进入下个结点
		temp = temp->next;
	}
}

void Depth_List_Graph(GraphList *graph) {
	//维护一个访问表，标记结点是否被访问
	int visited[MAXNODE];
	for (int i = 0; i < MAXNODE; i++)
	{
		visited[i] = 0;//0表示没访问过，1表示访问过
	}
	//对所有结点实施深度优先遍历，如果访问过则不进入，主要针对非连通图，连通图第一次就能访问完全
	for (int i = 0; i < graph->num; i++)
	{
		if (!visited[i])
			depGraph(graph, visited, i);
	}
}

void breGraph(GraphList *graph, int *visited, int id) {
	GraphNode *p;  //当遍历因子，将某个结点所有后继结点入队
	GraphHeadNode *temp;  //接收出队的头结点
	GraphHeadNode *Queue[2 * MAXNODE];
	int rear = 0, front = 0;
	Queue[rear++] = graph->list[id]; //第一个结点先进队列
	while (front != rear) {
		//出队列
		temp = Queue[front++];
		//如果没被访问过就访问
		if (!visited[temp->no]) {
			visited[temp->no] = 1;
			printf("%c ", temp->vertex);
		}
		//头结点所连的所有后继结点入队列(未访问的)
		p = temp->next;
		while (p != NULL) {
			if (!visited[p->no])  //未被访问
				Queue[rear++] = graph->list[p->no];
			p = p->next;
		}
	}
}

void Breadth_List_Graph(GraphList *graph) {
	//和二叉树层次遍历相似，要把每个结点相连的所有结点访问完了，再对访问过的结点做相同的动作，用队列实现
	//维护一个访问表，标记结点是否被访问
	int visited[MAXNODE];
	for (int i = 0; i < MAXNODE; i++)
	{
		visited[i] = 0;//0表示没访问过，1表示访问过
	}
	//对所有结点实施广度优先遍历，如果访问过则不进入，主要针对非连通图，连通图第一次就能访问完全
	for (int i = 0; i < graph->num; i++)
	{
		if (!visited[i])
			breGraph(graph, visited, i);
	}
}

GraphMatrix* Prim_Graph_Matrix(GraphMatrix *graph, int begin) {
	GraphMatrix *tree;
	init_GraphMatrix(&tree);
	int compnent[MAXNODE];  //存放已被加入树的结点，加入为1，未加入为0
	int neighbor[MAXNODE];  //存放所有结点的邻居(默认为begin，每轮更新一次)
	int distance[MAXNODE];  //存放与邻居的距离，更换了邻居就要同时更换距离
	//初始化
	for (int i = 0; i < graph->num; i++)
	{
		//每个点初始的邻居都是begin
		neighbor[i] = begin;
		//与邻居的距离
		distance[i] = graph->matrix[begin][i];
		//所有结点未加入树
		compnent[i] = 0;
	}
	//结点begin加入树
	compnent[begin] = 1;
	int addin;  //新加入结点的下标
	int min;  //迭代获取距离最小的结点
	for (int i = 1; i < graph->num; i++)  //执行n-1次，每次加入一个结点
	{
		min = INFINITE;
		//搜索未被加入树且距离已加入树最近的结点
		for (int j = 0; j < graph->num; j++)
		{
			if (!compnent[j] && distance[j] < min) {
				min = distance[j];
				addin = j;
			}
		}
		if (min < INFINITE) {  //找到了最佳结点
			//加入树
			compnent[addin] = 1;
			tree->matrix[addin][neighbor[addin]] = distance[addin];  //加入点与它的邻居的weight
			tree->matrix[neighbor[addin]][addin] = distance[addin];  //对称加入
			//更新剩下结点的neighbor与distance信息，保证每个结点与树的已加入结点的距离最小
			for (int k = 0; k < graph->num; k++)
			{
				//未加入树且与新加入结点的距离小于原distance，则更新。否则保持原有distance。
				if (!compnent[k] && graph->matrix[addin][k] < distance[k]) {
					distance[k] = graph->matrix[addin][k];  //distance更新为与新加入结点的距离
					neighbor[k] = addin;
				}
			}
		}
		else  //未找到
			break;
	}
	//更新其它信息到树(结点名，结点数) 
	for (int i = 0; i < graph->num; i++)
	{
		tree->vertex[i] = graph->vertex[i];
	}
	tree->num = graph->num;
	return tree;
}

void Dijkstra_Graph_Matrix(GraphMatrix *graph, int begin) {
	int distance[MAXNODE]; //存放每个点到起始点的距离，每轮更新
	int fond[MAXNODE];     //标记是否被访问过 1 0
	int path[MAXNODE];     //路径的前个结点
	//初始化
	for (int i = 0; i < graph->num; i++)
	{
		distance[i] = graph->matrix[begin][i];  //所有结点初始都与begin相连
		fond[i] = 0;      //所有结点未被访问
		path[i] = begin;  //所有结点默认前驱结点为begin
	}
	//begin结点加入fond
	fond[begin] = 1;
	distance[begin] = 0;
	//找距离最小的结点，加入fond，并更新dis，每轮加入一个结点，直到所有结点加入
	int min;
	int addin;
	for (int i = 0; i < graph->num; i++)
	{
		min = INFINITE;
		//寻找distance最小的结点
		for (int j = 0; j < graph->num; j++)
		{
			//未被访问过，且距离小于min迭代查找更新
			if (!fond[j] && distance[j] < min) {
				addin = j;
				min = distance[j];
			}
		}
		if (min < INFINITE) {  //找到最小距离结点
			//加入fond
			fond[addin] = 1;
			//更新距离表
			for (int k = 0; k < graph->num; k++)
			{
				//未被访问过且与为新加入结点的后继结点的结点(贪婪类算法，从已知最短路径开始辐射更新所有后继结点的dis)
				if (!fond[k] && graph->matrix[addin][k] < INFINITE) {
					//这些结点中(新结点的dis+新结点到这个点的距离)小于(原dis)
					if (min + graph->matrix[addin][k] < distance[k]) {
						//更新距离->新结点的dis+新结点到这个点的距离
						distance[k] = min + graph->matrix[addin][k];
						path[k] = addin;
					}
				}
			}
		}
	}
	//打印距离表
	printf("最短路径长度(相对于%d)：", begin);
	for (int i = 0; i < graph->num; i++)
	{
		printf("%d ", distance[i]);
	}
}

int Topsort_Graph_List(GraphList *graph) {  //排序成功返回1，失败返回0
	int temp;  //接收出栈下标
	int count = 0;  //排序的数量
	GraphNode *node;
	int inPoint[MAXNODE];  //入度
	int Stack[MAXNODE];  //存入度为0的栈
	int top = -1;
	for (int i = 0; i < MAXNODE; i++)
	{
		inPoint[i] = 0;
		Stack[i] = INFINITE;
	}
	//计算入度
	for (int i = 0; i < graph->num; i++)
	{
		node = graph->list[i]->next;
		while (node != NULL) {
			inPoint[node->no]++;
			node = node->next;
		}
	}
	//入度为0的元素下标进栈
	for (int i = 0; i < graph->num; i++)
	{
		if (inPoint[i] == 0)
			Stack[++top] = i;
	}
	//出栈并访问，重新计算入度，如果出现入度为0则入栈
	printf("拓扑排序：");
	while (top != -1) {
		//出栈
		temp = Stack[top--];
		printf("%c ", graph->list[temp]->vertex);
		count++;
		//将top元素指向的结点入度减1
		node = graph->list[temp]->next;
		while (node != NULL) {
			inPoint[node->no]--;
			//如果出现入度为0，则入栈
			if (inPoint[node->no] == 0) {
				Stack[++top] = node->no;
			}
			node = node->next;
		}
	}
	//如果栈没空，说明有回路
	if (count != graph->num)
		return 0;
	else
		return 1;
}