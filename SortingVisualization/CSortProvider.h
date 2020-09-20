#pragma once

typedef void(*SortStatusChanged)(bool isSorting, int accessCount, int compareCount);

#define SORT_STATUS_TICK 2

class CSortProvider
{
public:
	CSortProvider(const wchar_t * name);
	~CSortProvider();

	wchar_t name[64];

	void SetSortStatusChangedCallback(SortStatusChanged callback) {
		sortStatusChangedCallback = callback;
	}

	void virtual StartSort(int * arr, int * arrStatus, int * arrCompare, int arrLen);

	void Swap(int i1, int i2);

protected:

	bool SortAccess(int i);
	bool SortCompare(int i1, int i2);
	void SortEnd();

	int * arr;
	int * arrStatus;
	int * arrCompare;
	int arrLen;

private:
	SortStatusChanged sortStatusChangedCallback;

	int accessCount;
	int compareCount;
};

