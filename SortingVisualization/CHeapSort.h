#pragma once
#include "CSortProvider.h"
class CHeapSort :
	public CSortProvider
{
public:
	CHeapSort();
	~CHeapSort();
	void StartSort(int * arr, int * arrStatus, int * arrCompare, int arrLen);
	void adjust(int len, int index);
	void heapSort(int size);
};

