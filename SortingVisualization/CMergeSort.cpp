#include "stdafx.h"
#include "CMergeSort.h"


CMergeSort::CMergeSort() : CSortProvider(L"Merge Sort")
{
}
CMergeSort::~CMergeSort()
{
}

void CMergeSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	int * result = (int*)malloc(sizeof(int) *arrLen);

	merge_sort(0, arrLen - 1, result);

	SortEnd();
}

void CMergeSort::merge(int start, int end, int *result)
{
	int left_length = (end - start + 1) / 2 + 1;
	int left_index = start;
	int right_index = start + left_length;
	int result_index = start;
	while (left_index < start + left_length && right_index < end + 1)  //store data into new array
	{
		if (arr[left_index] <= arr[right_index]) {
			result[result_index++] = arr[left_index++];
			SortAccess(result_index);
		}
		else {
			result[result_index++] = arr[right_index++];
			SortAccess(result_index);
		}
	}
	while (left_index < start + left_length) {
		result[result_index++] = arr[left_index++];
		SortAccess(result_index);
	}
	while (right_index < end + 1) {
		result[result_index++] = arr[right_index++];
		SortAccess(result_index);
	}
}

void CMergeSort::merge_sort(int start, int end, int *result)
{
	if (1 == end - start)   //last only two elements
	{
		if (arr[start] > arr[end] && SortCompare(start, end))
		{
			Swap(start, end);
		}
		return;
	}
	else if (end == start)
		return; //last one element then there is no need to sort;
	else {
		//continue to divide the interval
		merge_sort( start, (end - start + 1) / 2 + start, result);
		merge_sort((end - start + 1) / 2 + start + 1, end, result);
		//start to merge sorted data
		merge(start, end, result);
		for (int i = start; i <= end; ++i)
		{
			arr[i] = result[i];
		}
	}

}
