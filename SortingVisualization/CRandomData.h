#pragma once
#include "CSortProvider.h"
class CRandomData :
	public CSortProvider
{
public:
	CRandomData();
	~CRandomData();
	void StartSort(int * arr, int * arrStatus, int * arrCompare, int arrLen);
};

