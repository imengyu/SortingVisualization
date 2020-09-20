#pragma once
#include "CSortProvider.h"
class CSelectionSort :
	public CSortProvider
{
public:
	CSelectionSort();
	~CSelectionSort();
	void StartSort(int * arr, int * arrStatus, int * arrCompare, int arrLen);
};

