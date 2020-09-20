#include "stdafx.h"
#include "CSelectionSort.h"


CSelectionSort::CSelectionSort() : CSortProvider(L"Selection Sort")
{
}
CSelectionSort::~CSelectionSort()
{
}

void CSelectionSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	for (int i = 0; i < arrLen; i++) {
		// �ҵ���i��ʼ�����һ��Ԫ������С��Ԫ��,k�洢��СԪ�ص��±�.
		int k = i;
		for (int j = i + 1; j < arrLen; j++) {
			if (arr[j] < arr[k] && SortCompare(k, j)) { k = j; }
		}

		// ����С��Ԫ��a[k] �� ��ʼ��Ԫ��a[i] ��������.
		if (k != i && SortCompare(k, i))
			Swap(k, i);
	}

	SortEnd();
}
