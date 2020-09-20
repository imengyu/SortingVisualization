#pragma once
#include "CSortProvider.h"
class CRadixSort :
	public CSortProvider
{
public:
	CRadixSort();
	~CRadixSort();
	void StartSort(int * arr, int * arrStatus, int * arrCompare, int arrLen);
	bool rxsort(int A[], int l, int h, int d, int k);
};

