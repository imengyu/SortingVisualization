#pragma once
#include "CSortProvider.h"
class CQuickSort :
	public CSortProvider
{
public:
	CQuickSort();
	~CQuickSort();
	void StartSort(int * arr, int * arrStatus, int * arrCompare, int arrLen);
	void quick_sort(int left, int right);
	int partition(int left, int right);
};

