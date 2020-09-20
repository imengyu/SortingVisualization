#include "stdafx.h"
#include "CInsertionSort.h"

CInsertionSort::CInsertionSort() : CSortProvider(L"Insertion Sort")
{

}
CInsertionSort::~CInsertionSort()
{
}

void CInsertionSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	for (int i = 1; i < arrLen; i++)
	{
		for (int j = i - 1; j >= 0 && arr[j + 1] < arr[j] && SortCompare(j, j + 1); j--)
			Swap(j, j + 1);
	}

	SortEnd();
}
