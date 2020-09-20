#include "stdafx.h"
#include "CBubbleSort.h"

CBubbleSort::CBubbleSort() : CSortProvider(L"Bubble Sort")
{
}
CBubbleSort::~CBubbleSort()
{
}

void CBubbleSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	int i, k;
	for (k = 0; k < arrLen; k++)
		for (i = 0; i < arrLen - k; i++)
			if (arr[i] > arr[i + 1] && SortCompare(i, i + 1))
			{
				Swap(i, i + 1);
			}

	SortEnd();
}
