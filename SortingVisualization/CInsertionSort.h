#pragma once
#include "CSortProvider.h"

class CInsertionSort :
	public CSortProvider
{
public:
	CInsertionSort();
	~CInsertionSort();

	void StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen);
};

