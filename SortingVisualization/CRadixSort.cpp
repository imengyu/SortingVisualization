#include "stdafx.h"
#include "CRadixSort.h"


CRadixSort::CRadixSort() : CSortProvider(L"Radix Sort")
{
}
CRadixSort::~CRadixSort()
{
}

void CRadixSort::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	rxsort(arr, 0, arrLen - 1, 4, 10);

	SortEnd();
}

bool CRadixSort::rxsort(int *A, int l, int h, int d, int k) {
	if (NULL == A || l > h)
		return false;
	int size = h - l + 1;

	int* counts = new int[k];//用于计数排序的辅助数据，详见计数排序
	int* temp = new int[size];//用于存储重新排序的数组
	int index;
	int pval = 1;
	//依次处理不同的位
	for (int i = 0; i < d; i++) {
		//counts数组清零
		for (int j = 0; j < k; j++)
			counts[j] = 0;

		for (int j = l; j <= h; j++) {
			/*
			1.data[j]/pval：去掉数字data[j]的后i个数，例如：
			当data[j]=1234,i=2时，此时pval=100,data[j]/pval=12;
			2.(data[j]/pval)%k：取数字data[j]/pval的最后一位数
			3.(int)(data[j]/pval)%k:取数字data[j]的第i位数
			*/
			index = (int)(A[j] / pval) % k;

			SortAccess(j);
			/*
			统计数组A中每个数字的第i位数中各个数字的频数,用于计数排序；
			*/
			counts[index]++;
		}
		//计算累加频数，用户计数排序
		for (int j = 1; j < k; j++)
			counts[j] = counts[j] + counts[j - 1];
		//使用倒数第i+1位数对A进行排序
		for (int j = h; j >= l; j--) {
			index = (int)(A[j] / pval) % k;
			temp[counts[index] - 1] = A[j];
			counts[index]--;

			SortAccess(j);
		}
		//将按第i为数排序后的结果保存回数组A中
		for (int j = 0; j < size; j++){
			A[j + l] = temp[j];
			SortAccess(j + l);
		}

		//更新pval
		pval = pval * k;
	}
	delete[] counts;
	delete[] temp;
}