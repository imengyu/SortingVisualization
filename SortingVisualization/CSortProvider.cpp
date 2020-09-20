#include "stdafx.h"
#include "CSortProvider.h"

float sortDealy = 10;

CSortProvider::CSortProvider(const wchar_t * name)
{
	wcscpy_s(this->name, name);
}
CSortProvider::~CSortProvider()
{
}

void CSortProvider::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	this->arr = arr;
	this->arrStatus = arrStatus;
	this->arrCompare = arrCompare;
	this->arrLen = arrLen;

	accessCount = 0;
	compareCount = 0;
}

void USleep(long lTime)
{
	LARGE_INTEGER litmp;
	LONGLONG QPart1, QPart2;
	double dfMinus, dfFreq, dfTim, dfSpec;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;
	dfSpec = 0.000001*lTime;

	do
	{
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;
		dfMinus = (double)(QPart2 - QPart1);
		dfTim = dfMinus / dfFreq;
	} while (dfTim < dfSpec);
}

void CSortProvider::Swap(int i1, int i2)
{
	int n = arr[i1];
	arr[i1] = arr[i2]; SortAccess(i1);
	arr[i2] = n; SortAccess(i2);
}

bool CSortProvider::SortAccess(int i)
{
	accessCount++;
	arrStatus[i] = SORT_STATUS_TICK;

	if (sortStatusChangedCallback)
		sortStatusChangedCallback(true, accessCount , -1);

	if (sortDealy > 0)
		USleep(static_cast<long>(sortDealy * 1000));

	return true;
}
bool CSortProvider::SortCompare(int i1, int i2)
{
	compareCount++;

	arrCompare[i1] = SORT_STATUS_TICK;
	arrCompare[i2] = SORT_STATUS_TICK;

	if (sortStatusChangedCallback)
		sortStatusChangedCallback(true, -1, compareCount);

	return true;
}
void CSortProvider::SortEnd()
{
	if (sortStatusChangedCallback)
		sortStatusChangedCallback(false, -1, -1);
}
