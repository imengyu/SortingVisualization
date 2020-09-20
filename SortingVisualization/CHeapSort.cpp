#include "stdafx.h"
#include "CHeapSort.h"


CHeapSort::CHeapSort() : CSortProvider(L"Heap Sort")
{
}
CHeapSort::~CHeapSort()
{
}

void CHeapSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	heapSort(arrLen);

	SortEnd();
}

// �ݹ鷽ʽ���������(len��arr�ĳ��ȣ�index�ǵ�һ����Ҷ�ӽڵ���±�)
void CHeapSort::adjust(int len, int index)
{
	int left = 2 * index + 1; // index�����ӽڵ�
	int right = 2 * index + 2;// index�����ӽڵ�

	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx] && SortCompare(left, maxIdx))     maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx] && SortCompare(right, maxIdx))     maxIdx = right;

	if (maxIdx != index)
	{
		Swap(maxIdx, index);
		adjust(len, maxIdx);
	}

}

// ������
void CHeapSort::heapSort(int size)
{
	// ��������ѣ������һ����Ҷ�ӽڵ����ϣ�
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		adjust( size, i);
	}
	// ���������
	for (int i = size - 1; i >= 1; i--)
	{
		Swap(0, i);           // ����ǰ���ķ��õ�����ĩβ
		adjust(i, 0);              // ��δ�������Ĳ��ּ������ж�����
	}
}