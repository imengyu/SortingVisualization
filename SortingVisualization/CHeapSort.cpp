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

// 递归方式构建大根堆(len是arr的长度，index是第一个非叶子节点的下标)
void CHeapSort::adjust(int len, int index)
{
	int left = 2 * index + 1; // index的左子节点
	int right = 2 * index + 2;// index的右子节点

	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx] && SortCompare(left, maxIdx))     maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx] && SortCompare(right, maxIdx))     maxIdx = right;

	if (maxIdx != index)
	{
		Swap(maxIdx, index);
		adjust(len, maxIdx);
	}

}

// 堆排序
void CHeapSort::heapSort(int size)
{
	// 构建大根堆（从最后一个非叶子节点向上）
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		adjust( size, i);
	}
	// 调整大根堆
	for (int i = size - 1; i >= 1; i--)
	{
		Swap(0, i);           // 将当前最大的放置到数组末尾
		adjust(i, 0);              // 将未完成排序的部分继续进行堆排序
	}
}