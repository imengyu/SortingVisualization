#include "stdafx.h"
#include "CRandomData.h"
#include <vector>

using namespace std;

#define random(a,b) (rand()%(b-a)+a)

CRandomData::CRandomData() : CSortProvider(L"Random Data")
{
}
CRandomData::~CRandomData()
{
}

void CRandomData::StartSort(int * arr, int * arrStatus, int *arrCompare, int arrLen)
{
	CSortProvider::StartSort(arr, arrStatus, arrCompare, arrLen);

	vector<int> randomNumber;
	for (int i = 0; i < arrLen; i++)
		randomNumber.push_back(i);

	int v = 0;
	for (int i = 0; i < arrLen; i++) {
		v = random(0, randomNumber.size());
		arr[i] = randomNumber[v]; SortAccess(i);
		randomNumber.erase(randomNumber.begin() + v);
	}

	SortEnd();
}