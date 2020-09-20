#include "stdafx.h"
#include "CSelectionSort.h"


CSelectionSort::CSelectionSort() : CSortProvider(L"Selection Sort")
{
}
CSelectionSort::~CSelectionSort()
{
}

void CSelectionSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	for (int i = 0; i < arrLen; i++) {
		// 找到从i开始到最后一个元素中最小的元素,k存储最小元素的下标.
		int k = i;
		for (int j = i + 1; j < arrLen; j++) {
			if (arr[j] < arr[k] && SortCompare(k, j)) { k = j; }
		}

		// 将最小的元素a[k] 和 开始的元素a[i] 交换数据.
		if (k != i && SortCompare(k, i))
			Swap(k, i);
	}

	SortEnd();
}
