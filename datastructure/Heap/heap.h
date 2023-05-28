#pragma once
#include <algorithm>
#include <iostream>
using namespace std;

void heap_justify(int* m_array, int start, int end);  //堆调整，从对指定区间调整，直到比它的孩子都大为止

void build_heap(int* m_array, int size);  //从无序数组建堆

void insert_heap(int* m_array, int& size, int data);  //插入堆

void remove_max(int* m_array, int& size);  //移除最大

void heap_sort(int* m_array, int size);  //堆排序，数组变成有序数组，不再是堆