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

	int* counts = new int[k];//���ڼ�������ĸ������ݣ������������
	int* temp = new int[size];//���ڴ洢�������������
	int index;
	int pval = 1;
	//���δ���ͬ��λ
	for (int i = 0; i < d; i++) {
		//counts��������
		for (int j = 0; j < k; j++)
			counts[j] = 0;

		for (int j = l; j <= h; j++) {
			/*
			1.data[j]/pval��ȥ������data[j]�ĺ�i���������磺
			��data[j]=1234,i=2ʱ����ʱpval=100,data[j]/pval=12;
			2.(data[j]/pval)%k��ȡ����data[j]/pval�����һλ��
			3.(int)(data[j]/pval)%k:ȡ����data[j]�ĵ�iλ��
			*/
			index = (int)(A[j] / pval) % k;

			SortAccess(j);
			/*
			ͳ������A��ÿ�����ֵĵ�iλ���и������ֵ�Ƶ��,���ڼ�������
			*/
			counts[index]++;
		}
		//�����ۼ�Ƶ�����û���������
		for (int j = 1; j < k; j++)
			counts[j] = counts[j] + counts[j - 1];
		//ʹ�õ�����i+1λ����A��������
		for (int j = h; j >= l; j--) {
			index = (int)(A[j] / pval) % k;
			temp[counts[index] - 1] = A[j];
			counts[index]--;

			SortAccess(j);
		}
		//������iΪ�������Ľ�����������A��
		for (int j = 0; j < size; j++){
			A[j + l] = temp[j];
			SortAccess(j + l);
		}

		//����pval
		pval = pval * k;
	}
	delete[] counts;
	delete[] temp;
}