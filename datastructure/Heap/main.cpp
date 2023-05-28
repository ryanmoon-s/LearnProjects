#include "heap.h"

int main()
{
	int m_array[100];
	int size = 50;

	for (int i = 0; i < size; i++) {
		m_array[i] = int(rand() % 100);
	}

	build_heap(m_array, size);

	remove_max(m_array, size);

	insert_heap(m_array, size, 103);
	insert_heap(m_array, size, 95);

	heap_sort(m_array, size);

	for_each(m_array, m_array + size, [](int val) {cout << val << endl; });

	system("pause");
}

