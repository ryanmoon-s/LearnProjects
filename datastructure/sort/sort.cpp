/*------------------------------------------十大排序算法-----------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

#define MAXSIZE 101
typedef struct range {   //快排非递归用
	int start;
	int end;
}range;
typedef struct node {  //桶排用
	int data;
	struct node *next;
}node;

void SelectionSort(int *Arr, int n); //选择

void InsertionSort(int *Arr, int n); //插入

void BubbleSort(int *Arr, int n); //冒泡

void ShellSort(int *Arr, int n);  //希尔

void MergeSort(int *Arr, int n);  //归并启动函数
void MergeSort_Re(int *arr, int *temp, int start, int end);  //归并 递归版
//void merge_nore(int *Arr, int n);  //归并 非递归版

void QuickSort(int *Arr, int n);  //快排启动函数
void swap(int *a, int *b);  //交换两个元素
void QuickSort_Re(int *arr, int start, int end);  //快排递归版
range set_range(int st, int en);  //非递归设置范围
void QuickSort_NoRe(int *arr, int n); //快排非递归版

void HeapSort(int *Arr, int n);  //堆排序启动函数
void heap_sort(int *arr, int n);  //堆排序操作函数
void max_heap(int *arr, int start, int end);  //创建最大堆

void CountingSort(int *Arr, int n);  //计数排序启动函数
void count_final(int *arr, int n);  //计数排序优化版

void BucketSort(int *Arr, int n);  //桶排序启动函数
void bucket_sort(int *arr, int n, int load_num);  //桶排序

void RadixSort(int *Arr, int n);  //基数排序启动函数
void radix_sort(int *arr, int n);  //基数排序

void PrintArr(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
    cout << endl << endl;
}

int main() {
	int arr[MAXSIZE];
	srand(time(NULL));
	for (int i = 0; i < MAXSIZE; i++)
	{
		arr[i] = rand() % MAXSIZE;  //0-99
	}

	// SelectionSort(arr, MAXSIZE);  //1    
	// InsertionSort(arr, MAXSIZE);  //2
	// BubbleSort(arr, MAXSIZE);  //3
	// ShellSort(arr, MAXSIZE);  //4
	// MergeSort(arr, MAXSIZE);  //5
	// QuickSort(arr, MAXSIZE);  //6
	// HeapSort(arr, MAXSIZE);  //7
	// CountingSort(arr, MAXSIZE);  //8
	// BucketSort(arr, MAXSIZE);  //9
	RadixSort(arr, MAXSIZE);  //10
}


//1
void SelectionSort(int *Arr, int n)
{
	/*
		选择出最小的和第一个交换位置，剩下的选择最小的和第二个交换位置 ...
	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	int min_index, temp;
	for (int i = 0; i < n - 1; i++)
	{
		//选择
		min_index = i;  //等于i，如果是i+1，那么当i本身是最小值时，就会出错了
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_index])
				min_index = j;
		}
		//交换
		temp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = temp;
	}
    PrintArr(arr, n);
} // 时间复杂度：n^2，空间复杂度：1，原地排序，非稳定排序

//2
void InsertionSort(int *Arr, int n)
{
	/*
		从第二个开始，对于每一个元素，(抽出来，找到前面一个比它小的位置，插进去)
	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	int temp, j;
	for (int i = 1; i < n; i++)
	{
		//抽出来
		temp = arr[i];
		//从i - 1到0，如果大于插入者，则向后移
		for (j = i - 1; j >= 0 && temp < arr[j]; j--)
		{
			arr[j + 1] = arr[j];
		}
		//插入  arr[j] < temp 插在arr[j + 1]
		arr[j + 1] = temp;
	}
    PrintArr(arr, n);
}  // 时间复杂度：n^2，空间复杂度：1，原地排序，稳定排序


//3
void BubbleSort(int *Arr, int n)
{
	/*
		一轮：从第一个开始，对于每一个元素，如果后面的比它小，则交换
		一轮后，最大的元素在最右边，第二轮后，第二大的元素在倒数第二
		n轮后完成排序
		优化：第一轮下来没有元素变化，就已经是有序的了，不用再浪费后续时间
	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	int temp, flag = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (arr[j] > arr[j + 1]) {
				//交换
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = 1;
			}
		}
		if (flag == 0) {
			return;
		}
	}
    PrintArr(arr, n);
}  // 时间复杂度：n^2，空间复杂度：1，原地排序，非稳定排序

//4
void ShellSort(int *Arr, int n)
{
	/*
		插入排序的变种，用的是插入排序的方法，不过要分组，10/2 分成 5 组，每组增量为 5
		从 5(第一个组的第二个元素)开始，对5在本组插入排序，对6在本组插入排序...到n
		所以是依次对不同的组操作
		每分一次组，就更有序一点，下次操作更快。直到最后一次1个1组，就排序完成了
	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	int temp, i , j, gap;
	for (gap = n / 2; gap > 0; gap /= 2)  //第一次除以2，下次除以4 ...(循环一次，分一次组)
	{
		//对这次分出来的每组进行排序(gap为第一个小组的第二个元素)
		for (i = gap; i < n; i++)
		{
			temp = arr[i];  //插入者，下标为i
			//挪动从上个增量的值开始，如果大于插入者大于等于0则后移
			for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
			{
				arr[j + gap] = arr[j];
			}
			//上个循环终止条件：arr[j] < temp  所以插入到arr[j+gap]
			arr[j + gap] = temp;
		}
	}
    PrintArr(arr, n);
}  // 时间复杂度：O(n^(1.3—2))，空间复杂度：1，原地排序，非稳定排序

//5
void MergeSort(int *Arr, int n)
{
	/*
		分而治之
		递归将大数组切割至不可分割(逻辑上)，每层返回时都按照大小顺序进入备用数组，全部进入再移到主数组里面
		当最后一层递归返回后，就排序完成了
	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	//递归版
	int start = 0, end = n - 1;
	int temp[MAXSIZE];
	MergeSort_Re(arr, temp, start, end);
	//非递归版
	//merge_nore(arr, n);
    PrintArr(arr, n);
}  // 时间复杂度：nlog2n，空间复杂度：n(最后一次要全装入)，非原地排序，稳定排序

void MergeSort_Re(int *arr, int *temp,  int start, int end)
{
	//递归终止条件，只有一个元素时
	if (start >= end)
		return;
	//分成两半，len并不是具体长度，只作为分成两半的条件  右移一位：/2
  	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid, start2 = mid + 1, end2 = end;
	//左右分别递归
	MergeSort_Re(arr, temp, start1, end1);
	MergeSort_Re(arr, temp, start2, end2);
	//排序
	int k = start;  //装在相同的位置
	while (start1 <= end1 && start2 <= end2) {  
		//两个子数组(逻辑上的)中，挨个比较，小的进入临时数组。进入的才++
		temp[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
	}
	while (start1 <= end1) {
		//子数组1(逻辑上的)有剩下没进入的元素
		temp[k++] = arr[start1++];
	}
	while (start2 <= end2) {
		//子数组2(逻辑上的)有剩下没进入的元素
		temp[k++] = arr[start2++];
	}
	//临时数组还原到原数组，返回供上层继续使用
	for (int i = start; i <= end; i++)
	{
		arr[i] = temp[i];
	}
}

//void merge_nore(int *arr, int n) {
//	
//}

//6
void QuickSort(int *Arr, int n)
{
	/*
		分而治之
		随便找一个元素mid(这里找的end)，一根指针left从左向右，一根指针right从右向左，比较
		left比mid大的和right比mid小的交换，这样就分成了两块，比mid小的在左边，大的在右边。
		再分别对左边和右边递归。
		当所有递归返回时，排序完成
	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	//递归版
	QuickSort_Re(arr, 0, n - 1);
	//非递归版
	QuickSort_NoRe(arr, n);
}  // 时间复杂度：nlog2n，空间复杂度：nlog2n，原地排序，非稳定排序

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void QuickSort_Re(int *arr, int start, int end)
{
	//递归终止条件
	if (start >= end)
		return;
	int left = start, right = end - 1, mid = arr[end];
	while (left < right) {
		//当left上的值小于mid时不用交换，指针后移
		while (arr[left] < mid && left < right)   
			left++;
		//当left上的值大于等于mid时不用交换，指针前移。如果没有等号，就是大于不换，如果left和right上相等，则一直死循环
		while (arr[right] >= mid && left < right) 
			right--;
		//交换
		swap(&arr[left], &arr[right]);
	}
	//mid肯定要和一个比我大的交换撒，如果和一个比我小的交换，最后一个不就不满足了：右边都比我大
	//保证left上面是mid，第一个大于mid的数，在left 或 left + 1 上
	if (arr[left] < mid) 
		left++;
	swap(&arr[left], &arr[end]);
	QuickSort_Re(arr, start, left - 1); //递归左边
	QuickSort_Re(arr, left + 1, end);//递归右边，left是正中间的数，不用再加入里面
}

range set_range(int st, int en)
{
	range ra;
	ra.start = st;
	ra.end = en;
	return ra;
}

void QuickSort_NoRe(int *arr, int n)
{
	/*
		迭代版和递归版差不多，只是把重入的参数保存在结构体range里面，利用栈来完成递归的过程
		类似于二叉树的层次遍历：先将根入队，出栈访问再将子结构入队，出栈访问子结构再将...
	*/
	//判断n是否合法
	if (n <= 0)
		return;
	//维护一个range栈
	int top = -1;
	range Stack[MAXSIZE];
	//最大范围入栈
	range temp = set_range(0, n - 1);
	Stack[++top] = temp;
	//迭代
	while (top != -1) {
		//弹出栈顶元素
		temp = Stack[top--];
		if (temp.start >= temp.end)
			continue;
		//设置参数
		int left = temp.start, right = temp.end - 1, mid = arr[temp.end];
		//排序
		while (left < right) {
			while (arr[left] < mid && left < right)
				left++;
			while (arr[right] >= mid && left < right)
				right--;
			swap(&arr[left], &arr[right]);
		}
		if (arr[left] > mid)
			swap(&arr[left], &arr[temp.end]);
		else {
			left++;
			swap(&arr[left], &arr[temp.end]);
		}
		//更新栈
		if(left)
			Stack[++top] = set_range(temp.start, left - 1);
		Stack[++top] = set_range(left + 1, temp.end);
	}
}

//7
void HeapSort(int *Arr, int n)
{
	/*
		堆排序，堆的数据结构：完全二叉树。存储方式：线性表。
		一个结点i的父结点：(i-1)/2 一个结点的左孩子：2*i+1 右：2*i+2
		先将堆排成最大堆(大的在上面)
		1.将根与最后一个元素交换，从根到交换元素前一个排成最大堆
		2.将根与倒数第二个元素交换，从根到交换元素前一个排成最大堆
		...  直到只剩下根，排序完成

	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	heap_sort(arr, n);
    PrintArr(arr, n);
}  // 时间复杂度：nlog2n，空间复杂度：1，原地排序，非稳定排序

void max_heap(int *arr, int start, int end)
{
	int dad = start;
	int son = 2 * dad + 1; //左孩子
	while (son <= end) {
		//如果右孩子大于左孩子，则切换到右孩子
		if (son + 1 <= end && arr[son] < arr[son + 1])
			son++;
		if (arr[dad] >= arr[son]) //父结点大于等于最大的孩子，排序完成
			return;
		else {  //父结点小于最大的孩子
			//交换
			swap(&arr[dad], &arr[son]);
			//交换的孩子升级成为父结点，继续迭代
			//因为调用这个函数时是从下向上调用，下面都是排好的，如果不发生交换就不用再向后迭代
			//相反，发生了交换，就要向下迭代，防止交换的又比下面的小
			dad = son;
			son = 2 * son + 1;
		}
	}
}

void heap_sort(int *arr, int n)
{
	//开始先建立成最大堆
	//从最后一个父结点开始排，循环向上走，最后一个结点：n-1 它的父：(n-1 -1)/2
	for (int i = (n-2)/2; i >= 0; i--)
	{
		max_heap(arr, i, n - 1);  //此结点到最后，如果发生交换会向后迭代
	}
	//交换根与最后的下标
	for (int j = n - 1; j > 0; j--)  //等于0时没有意义，已经完成
	{
		swap(&arr[0], &arr[j]);  //交换
		max_heap(arr, 0, j - 1);  //生成最大堆
	}
}

//8
void CountingSort(int *Arr, int n)
{
	/*
		计数排序，相当于一个桶只放一个元素的桶排序
		用一个数组统计每个元素存在的次数，再一一数出来 
		在知道元素范围，且范围不大的情况下使用
		在实际工作中，所有数据分布比较集中，出现次数多时，应该采用计数排序

		1.计算最小与最大的差值size
		2.创建对应大小size的临时计数数组
		3.对每一个元素进行计数，从min-max偏移到0-(size-1)
		4.还原计的数到到原数组，反偏移还原

	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	count_final(arr, n);
    PrintArr(arr, n);
}  // 时间复杂度：n + k，空间复杂度：k(k为临时数组大小)，非原地排序，稳定排序

void count_final(int *arr, int n)
{
	//找到范围，以创建相应大小的计数数组
	int min = arr[0], max = min;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < min)
			min = arr[i];
		else if(arr[i] > max)
			max = arr[i];
	}
	//计算范围(把min-max映射到0-(size-1)来，节约存储空间)
	int size = max - min + 1; //计数数组元素个数
	int *countarr = (int*)malloc(size * sizeof(int));
	//初始化
	for (int i = 0; i < size; i++)
	{
		countarr[i] = 0;
	}
	//计数
	for (int i = 0; i < n; i++)
	{
		countarr[arr[i] - min]++;  //-min为偏移到0-----(size-1)
	}
	//写回原数组
	int index = 0; //写回原数组用的下标
	int count; //计一个位置有几个值
	for (int j = 0; j < size; j++)
	{
		count = countarr[j];
		while (count > 0) {
			arr[index++] = j + min;  //+min为反偏移
			count--;
		}
	}
}

//9
void BucketSort(int *Arr, int n)
{
	/*
		桶排序，将一定范围的数放在一个桶中，升级版的计数排序，当跨度大时节约空间
		桶排序是对计数排序的改进，计数排序申请的额外空间跨度从最小元素值到最大元素值
		，若待排序集合中元素不是依次递增的，则必然有空间浪费情况。
		映射规则很大程度上决定了效果的好坏。
		如果数据分布比较均匀：x-min 从min-max映射到0-(size-1)，(x-min)/N 一个桶装N个元素
		1.数据入桶
		2.桶内排序
		3.数据回数组
		/1.2合并，入桶时采用插入排序的方法，出桶顺序出桶
		          也可以顺序入桶，出桶时选择出桶
				  也可以顺序入桶，桶内排序，再顺序出桶
	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	bucket_sort(arr, n, 10);
    PrintArr(arr, n);
} // 时间复杂度：n + k，空间复杂度：n + k(k为临时数组大小)，非原地排序，稳定排序
//n:每个结点需要空间

void bucket_sort(int *arr, int n, int load_num)
{
	//根据映射规划申请桶空间
	int min = arr[0], max = min;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < min)
			min = arr[i];
		else if (arr[i] > max)
			max = arr[i];
	}
    int range_num = max - min + 1;         // min、max之间有多少个实数
	int bucket_num = range_num / load_num; // 桶数量，一个桶装load_num个元素
    if (range_num % 2 == 1) // 如果是奇数，会少一个
    {
        bucket_num += 1;
    }
	node **bucket = (node**)malloc(bucket_num * sizeof(node*));
	for (int i = 0; i < bucket_num; i++)
	{
		bucket[i] = (node*)malloc(sizeof(node));  //头结点
		bucket[i]->data = 0;
		bucket[i]->next = NULL;
	}
	//根据规则，使用插入排序的方法入桶
	node *temp, *insert;
	for (int i = 0; i < n; i++)
	{
		insert = (node*)malloc(sizeof(node)); //分配节点
		insert->data = arr[i];
        int index = (arr[i] - min) / load_num;
		temp = bucket[index];  //i对应的value落入的桶，映射 
		if (temp->next == NULL) {  //链为空，直接插入
			insert->next = temp->next;
			temp->next = insert;
		}
		else {  //链不为空，找到第一个大于它的元素前面插入，从小到大排序
			while (temp->next != NULL) {
				//当value小于temp->next的value时，插入到temp的后面
				if (temp->next->data >= insert->data) {
					insert->next = temp->next;
					temp->next = insert;
					break;
				}
				temp = temp->next;
			}
			// 前面没插入，插入到最后
			if (temp->next == NULL) {
				insert->next = temp->next;
				temp->next = insert;
			}
		}
	}
	//将不为空的桶出到数组中
	int index = 0;  //入数组下标
	for (int i = 0; i < bucket_num; i++)
	{
		temp = bucket[i];
		while (temp->next != NULL) {
			arr[index++] = temp->next->data;
			temp = temp->next;
		}
	}
}

//10
void RadixSort(int *Arr, int n)
{
	/*
		基数排序，将所有数字补成一样长，前面补0，先个位有序，再十位有序，再...最终全部有序
		对每个基数排序时要选择稳定的排序方法，不然排高位时会将低位打乱
		MSD：先从高位开始进行排序，在每个关键字上，可采用计数排序(稳定)：将高位相同的进行低位排序
		LSD：先从低位开始进行排序，在每个关键字上，可采用桶排序(稳定)：将所有进行的进行排序
		位只有0-9，一对多，使用桶才能装下

	*/
	int arr[MAXSIZE];
	for (int i = 0; i < n; i++)
	{
		arr[i] = Arr[i];
	}
	/*-------------------------------------------------------------------------*/
	radix_sort(arr, n);
    PrintArr(arr, n);
} // 时间复杂度：n*k，空间复杂度：n + k(k为临时数组大小)，非原地排序，稳定排序

void radix_sort(int *arr, int n)
{ //LSD方法(低到高，桶排序)
	//计算位数
	int max = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	int num = 1;  //位数
	while ((max = max / 10) > 0)
		num++;
	//申请10个桶
	node **bucket = (node**)malloc(10 * sizeof(node*));
	for (int i = 0; i < 10; i++)
	{
		bucket[i] = (node*)malloc(sizeof(node));  //头结点
		bucket[i]->data = 0;
		bucket[i]->next = NULL;
	}
	//排序，入桶时插入排序
	node *temp;
	node *dele;  //删除结点用
	node *insert = (node*)malloc(sizeof(node));
	int left;  //0 10 100 取出对应位
	int index;  //输回数组的下标
	for (int i = 0; i < num; i++)  //两位，进行两轮
	{
		left = pow(10, i);
		for (int j = 0; j < n; j++)  //n个元素，每轮按对应位入桶
		{
			temp = bucket[(arr[j] / left) % 10];  //标记桶位置，/left使对应位成个位，%10取个位
			insert = (node*)malloc(sizeof(node)); //分配节点
			insert->data = arr[j];
			//入桶
			if (temp->next == NULL) {  //链空，直接插入
				insert->next = temp->next;
				temp->next = insert;
			}
			else {  //链不为空，找到第一个大于它的元素前面插入
				while (temp->next != NULL) {
					//当value小于temp->next的value时，插入到temp的后面
					if (temp->next->data >= insert->data) {
						insert->next = temp->next;
						temp->next = insert;
						break;
					}
					temp = temp->next;
				}
				//flag = 0说明，前面没插入，插入到最后
				if (temp->next == NULL) {
					insert->next = temp->next;
					temp->next = insert;
				}
			}
		}
		//出桶，将不为空的桶出到数组中，此位完成，为次高位排序准备
		index = 0;  //入数组下标
		for (int l = 0; l < 10; l++)
		{
			//输出到数组
			temp = bucket[l];
			dele = bucket[l];
			while (temp->next != NULL) {  //temp移动输出数据用
				arr[index++] = temp->next->data;
				temp = temp->next;
			}
			//删除结点
			while (dele->next != NULL) {  //del移动，temp删除结点用
				temp = dele->next;
				dele->next = dele->next->next;
				free(temp);
				temp = NULL;
			}
		}
	}
}
