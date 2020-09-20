#pragma once

#include "resource.h"

void UpdateSortVals();
void UpdateSortStatus(bool isSorting, int accessCount, int compareCount);

void InitArrayBuffer();
void DeleteArrayBuffer();
void FillRandomData();

void InitAllSortMethods();
void DestroyAllSortMethods();

DWORD WINAPI ResetThread(LPVOID lpParam);

DWORD WINAPI SortThreadH(LPVOID lpParam);
void DoSort();
void StopSort();

INT_PTR CALLBACK ToolDialogWndProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);

void CreateToolDialog(HINSTANCE hInstance);
