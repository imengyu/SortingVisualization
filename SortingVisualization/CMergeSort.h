#pragma once
#include "CSortProvider.h"
class CMergeSort :
	public CSortProvider
{
public:
	CMergeSort();
	~CMergeSort();
	void StartSort(int * arr, int * arrStatus, int * arrCompare, int arrLen);
	void merge(int start, int end, int * result);
	void merge_sort(int start, int end, int * result);
};

