#pragma once
#include "CSortProvider.h"
class CShellSort :
	public CSortProvider
{
public:
	CShellSort();
	~CShellSort();
	void StartSort(int * arr, int * arrStatus, int * arrCompare, int arrLen);
};

