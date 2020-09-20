#pragma once
#include "CSortProvider.h"

class CBubbleSort :
	public CSortProvider
{
public:
	CBubbleSort();
	~CBubbleSort();

	void StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen);
};

