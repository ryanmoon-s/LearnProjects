#pragma once
#include <algorithm>
#include <iostream>
using namespace std;

void heap_justify(int* m_array, int start, int end);  //�ѵ������Ӷ�ָ�����������ֱ�������ĺ��Ӷ���Ϊֹ

void build_heap(int* m_array, int size);  //���������齨��

void insert_heap(int* m_array, int& size, int data);  //�����

void remove_max(int* m_array, int& size);  //�Ƴ����

void heap_sort(int* m_array, int size);  //�������������������飬�����Ƕ�