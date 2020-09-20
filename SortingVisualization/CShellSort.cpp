#include "stdafx.h"
#include "CShellSort.h"


CShellSort::CShellSort() : CSortProvider(L"Shell Sort")
{
}
CShellSort::~CShellSort()
{
}

void CShellSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	int increment = arrLen;
	while (increment > 1)
	{
		increment = increment / 3 + 1;
		for (int i = increment; i < arrLen; i++)
		{
			int temp = arr[i];
			if (arr[i] < arr[i - increment] && SortCompare(i, i - increment))
			{
				int j;
				for (j = i - increment; j >= 0 && arr[j] > temp && SortCompare(j, i); j = j - increment) {
					arr[j + increment] = arr[j]; SortAccess(j + increment);
				}

				arr[j + increment] = temp; SortAccess(j + increment);
			}
		}
	}

	SortEnd();
}
