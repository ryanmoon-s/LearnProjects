#include "heap.h"

void heap_justify(int * m_array, int start, int end)
{
	//堆调整，从start到end进行调整，直到比孩子都大为止
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) {
		if (son + 1 <= end && m_array[son] < m_array[son + 1])  //找出大的孩子
			son++;
		if (m_array[dad] > m_array[son])  //父亲比最大的孩子大，不用再向下递归
			return;
		else {
			swap(m_array[dad], m_array[son]);  //STL库函数，引用
			dad = son;
			son = son * 2 + 1;
		}
	}
}

void build_heap(int * m_array, int size)
{
	//从最后一个有孩子的节点开始，对左边、上面的元素都进行堆调整，自下而上，调整好后成大根堆了。
	for (int i = size/2 - 1; i >= 0; i--) {
		heap_justify(m_array, i, size - 1);
	}
}

void insert_heap(int * m_array, int& size, int data)
{
	//插入都插入到最后，然后从插入元素向上进行堆调整，相当于插入到有序序列中
	m_array[size++] = data;
	int son = size - 1;
	int dad = (son - 1) / 2;
	while (dad >= 0) {
		if (m_array[dad] >= m_array[son])  //大于等于时不调整
			return;
		else {
			swap(m_array[dad], m_array[son]);
			son = dad;
			dad = (son - 1) / 2;
		}
	}
}

void remove_max(int * m_array, int& size)
{
	if (size <= 0)
		return;
	int temp_max = m_array[0];
	m_array[0] = m_array[size - 1];  //最后一个元素赋给堆顶元素
	heap_justify(m_array, 0, size - 1);  //从堆顶向下进行堆调整
	size--;
}

void heap_sort(int * m_array, int size)
{
	build_heap(m_array, size);  //建堆
	
	//原地排序，空间复杂度n
	for (int j = size - 1; j > 0; j--) {  //j=0时，只剩下它一个，不用进行
		swap(m_array[0], m_array[j]);  //堆顶(最大值)和最后元素交换
		heap_justify(m_array, 0, j - 1);   //从堆顶进行堆调整，调整后顶部又为最大值。
	}
}

