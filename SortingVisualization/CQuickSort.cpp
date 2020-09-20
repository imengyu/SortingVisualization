#include "stdafx.h"
#include "CQuickSort.h"


CQuickSort::CQuickSort() : CSortProvider(L"Quick Sort")
{
}
CQuickSort::~CQuickSort()
{
}

void CQuickSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	quick_sort(0, arrLen - 1);

	SortEnd();
}

void CQuickSort::quick_sort(int left, int right)
{
	if (left > right)
		return;
	int j = partition(left, right);
	quick_sort(left, j - 1);
	quick_sort(j + 1, right);
}
int CQuickSort::partition(int left, int right)  //找基准数 划分
{
	int i = left + 1;
	int j = right;
	int temp = arr[left];

	while (i <= j)
	{
		while (arr[i] < temp && SortCompare(i, left))
		{
			i++;
		}
		while (arr[j] > temp && SortCompare(j, left))
		{
			j--;
		}
		if (i < j && SortCompare(i, j))
			Swap(i++, j--);
		else i++;
	}
	Swap(j, left);
	return j;

}