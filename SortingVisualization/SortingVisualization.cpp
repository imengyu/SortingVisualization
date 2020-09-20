// SortingVisualization.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include <d3d11.h>
#include <d3d9.h>
#include <time.h>
#include <vector>
#include <thread>
#include "SortingVisualization.h"
#include "COpenGLRenderer.h"
#include "COpenGLView.h"
#include "CArrayDataRenderer.h"
#include "CSortProvider.h"
#include "CBubbleSort.h"
#include "CQuickSort.h"
#include "CInsertionSort.h"
#include "CSelectionSort.h"
#include "CHeapSort.h"
#include "CShellSort.h"
#include "CMergeSort.h"
#include "CRadixSort.h"
#include "CRandomData.h"
#include "resource.h"

using namespace std;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

#define APP_TITLE L"Sorting Visualization (Win32 OpenGL)"


COpenGLView *OpenGLView;
CArrayDataRenderer * ArrayDataRenderer;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	

	switch (uiMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		OpenGLView->OnPaint();
		break;
	case WM_SIZE:
		OpenGLView->OnSize(LOWORD(lParam), HIWORD(lParam));
		break;
	default:
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	return 0;
}

// ================================================


HWND hDialogTool = NULL;
HWND hEditDealy, hEditArrLen, hComboMethod, hButtonStart, hButtonReset;

int *arrayBuffer = nullptr;
int *arrayAccessBuffer = nullptr;
int *arrayCompareBuffer = nullptr;
int arrayLength = 2000;
bool sorting = false;
bool reseting = false;
vector<CSortProvider*> sortProviders;
CSortProvider *sortCurrent = nullptr;
CRandomData ramdomData;

extern float sortDealy;
HANDLE sortThread = NULL;
HANDLE resetingThread = NULL;

// ================================================
//  排序、数据控制相关
// ================================================

void UpdateSortVals() {

	WCHAR v[32];
	GetWindowText(hEditDealy, v, 32);
	sortDealy = static_cast<float>(_wtof(v));
	if (sortDealy < 0) {
		sortDealy = 0;
		SetWindowText(hEditDealy, L"0");
	}
	if (sortDealy > 1000) {
		sortDealy = 1000;
		SetWindowText(hEditDealy, L"1000");
	}

	GetWindowText(hEditArrLen, v, 32);
	if (wcscmp(v, L"") != 0) {
		int newArrayLength = _wtoi(v);
		if (newArrayLength < 10) {
			newArrayLength = 10;
			SetWindowText(hEditArrLen, L"10");
		}
		if (newArrayLength > 10000) {
			newArrayLength = 10000;
			SetWindowText(hEditArrLen, L"10000");
		}
		if (arrayLength != newArrayLength) {
			arrayLength = newArrayLength;
			
			DeleteArrayBuffer();
			InitArrayBuffer();
		}
	}

	int sel = SendMessage(hComboMethod, CB_GETCURSEL, 0, 0);
	if (sel >= 0 && sel < (int)sortProviders.size()) {
		sortCurrent = sortProviders[sel];
		ArrayDataRenderer->SetSortMethodName(sortCurrent->name);
	}
	else sortCurrent = nullptr;
}
void UpdateSortStatus(bool isSorting, int accessCount, int compareCount) {
	if (accessCount >= 0) ArrayDataRenderer->accessCount = accessCount;
	if (compareCount >= 0) ArrayDataRenderer->compareCount = compareCount;
	if (sorting != isSorting) {
		sorting = isSorting;
		EnableWindow(hComboMethod, !sorting);
		EnableWindow(hEditArrLen, !sorting);	
		SetWindowText(hButtonStart, sorting ? L"停止" : L"排序完成");
	}
}
void UpdateResetingStatus(bool isReseting) {
	if (reseting != isReseting) {
		reseting = isReseting;
		ArrayDataRenderer->SetSortMethodName(reseting ? L"Resetting data..." : L"");
		EnableWindow(hComboMethod, !reseting);
		EnableWindow(hEditArrLen, !reseting);
		EnableWindow(hButtonStart, !reseting);
		EnableWindow(hButtonReset, !reseting);
	}
}
void ResetSort() {
	SetWindowText(hButtonStart, L"开始排序");
	FillRandomData();
}

void InitArrayBuffer() {
	arrayAccessBuffer = (int*)malloc(arrayLength * sizeof(int));
	arrayCompareBuffer = (int*)malloc(arrayLength * sizeof(int));
	arrayBuffer = (int*)malloc(arrayLength * sizeof(int));

	if (ArrayDataRenderer) {
		ArrayDataRenderer->arrayMaxValue = arrayLength;
		ArrayDataRenderer->arrayLength = arrayLength;
		ArrayDataRenderer->arrayBuffer = arrayBuffer;
		ArrayDataRenderer->arrayAccessBuffer = arrayAccessBuffer;
		ArrayDataRenderer->arrayCompareBuffer = arrayCompareBuffer;
	}
}
void DeleteArrayBuffer() {

	if (arrayBuffer) free(arrayBuffer);
	if (arrayAccessBuffer) free(arrayAccessBuffer);
	if (arrayCompareBuffer) free(arrayCompareBuffer);

	arrayCompareBuffer = nullptr;
	arrayAccessBuffer = nullptr;
	arrayBuffer = nullptr;
}
void FillRandomData() {
	UpdateSortVals();

	if (!reseting) {
		UpdateResetingStatus(true);
		resetingThread = CreateThread(NULL, NULL, ResetThread, 0, 0, NULL);
	}
}

void InitAllSortMethods() {

	sortProviders.push_back(new CInsertionSort());
	sortProviders.push_back(new CShellSort());

	sortProviders.push_back(new CSelectionSort());
	sortProviders.push_back(new CHeapSort());

	sortProviders.push_back(new CBubbleSort());
	sortProviders.push_back(new CQuickSort());

	sortProviders.push_back(new CMergeSort());
	sortProviders.push_back(new CRadixSort());

	vector<CSortProvider*>::iterator it;
	for (it = sortProviders.begin(); it != sortProviders.end(); it++) {
		(*it)->SetSortStatusChangedCallback(UpdateSortStatus);
	}
}
void DestroyAllSortMethods() {
	vector<CSortProvider*>::iterator it;
	for (it = sortProviders.begin(); it != sortProviders.end(); it++) {
		CSortProvider *sortItem = *it;
		delete sortItem;
	}
	sortProviders.clear();
}

DWORD WINAPI ResetThread(LPVOID lpParam) {
	sortDealy = 1;
	ramdomData.StartSort(arrayBuffer, arrayAccessBuffer, arrayCompareBuffer, arrayLength);
	UpdateResetingStatus(false);
	UpdateSortStatus(false, 0, 0);
	return 0;
}
DWORD WINAPI SortThreadH(LPVOID lpParam) {
	if (sortCurrent) {
		UpdateSortStatus(true, 0, 0);
		sortCurrent->StartSort(arrayBuffer, arrayAccessBuffer, arrayCompareBuffer, arrayLength);
	}
	return 0;
}
void DoSort() {

	UpdateSortVals();

	if (sortCurrent)
		sortThread = CreateThread(NULL, NULL, SortThreadH, 0, 0, NULL);
	else MessageBox(hDialogTool, L"请选择排序方法", L"提示", MB_ICONINFORMATION);
}
void StopSort() {

	if (sortThread != NULL) {
		TerminateThread(sortThread, 0);
		sortThread = NULL;
	}

	UpdateSortStatus(false, -1, -1);
}

// ================================================
//  UI 控制窗口相关
// ================================================


INT_PTR CALLBACK ToolDialogWndProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case WM_INITDIALOG: {
		hEditDealy = GetDlgItem(hDlg, IDC_EDIT_TICK_DEALY);
		hEditArrLen = GetDlgItem(hDlg, IDC_EDIT_ARR_LEN);
		hComboMethod = GetDlgItem(hDlg, IDC_COMBO_SORT_METHOD);
		hButtonStart = GetDlgItem(hDlg, IDC_SORT);
		hButtonReset = GetDlgItem(hDlg, IDC_RESET);
		SetWindowText(hEditDealy, L"1");
		SetWindowText(hEditArrLen, L"2000");
		vector<CSortProvider*>::iterator it;
		for (it = sortProviders.begin(); it != sortProviders.end(); it++) {
			CSortProvider *sortItem = *it;
			SendMessage(hComboMethod, CB_ADDSTRING, NULL, (LPARAM)sortItem->name);
		}
		SendMessage(hComboMethod, CB_SELECTSTRING, -1, (LPARAM)(*sortProviders.begin())->name);
		return TRUE;
	}
	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_CHANGE: {
			UpdateSortVals();
			break;
		}
		case IDC_SORT: {
			if (sorting) {
				if (MessageBox(hDlg, L"排序正在进行中，是否停止？", L"提示", MB_YESNO) == IDYES)
					StopSort();
			}
			else DoSort();
			break;
		}
		case IDC_RESET: {
			if (sorting) {
				if (MessageBox(hDlg, L"排序正在进行中，是否停止并重置？", L"提示", MB_YESNO) == IDYES) {
					StopSort();
					ResetSort();
				}
			}
			else ResetSort();
			break;
		}
		case IDCANCEL: {
			if (sorting) {
				if (MessageBox(hDlg, L"排序正在进行中，是否停止并退出？", L"提示", MB_YESNO) == IDYES) {
					StopSort();
					EndDialog(hDlg, wParam);
					PostQuitMessage(0);
				}
			}
			else {
				EndDialog(hDlg, wParam);
				PostQuitMessage(0);
			}
			break;
		}	  
		default:
			break;
		}
		break;
	}
	return FALSE;
}

void CreateToolDialog(HINSTANCE hInstance) {
	hDialogTool = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_CONTROL_TOOL), NULL, ToolDialogWndProc);
	ShowWindow(hDialogTool, SW_SHOW);
	UpdateWindow(hDialogTool);
}

// ================================================

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPWSTR lpCmdLine,  int nCmdShow)
{
	srand(static_cast<UINT>(time(NULL)));

	ArrayDataRenderer = new CArrayDataRenderer();
	OpenGLView = new COpenGLView(ArrayDataRenderer);

	InitAllSortMethods();
	InitArrayBuffer();
	FillRandomData();
	
	if (OpenGLView->Init(hInstance, APP_TITLE, 800, 600, WndProc))
	{
		CreateToolDialog(hInstance);

		OpenGLView->Show();
		OpenGLView->MessageLoop();
	}
	else
	{
		MessageBox(NULL, OpenGLView->ErrorLog, APP_TITLE, MB_OK | MB_ICONERROR);
	}

	OpenGLView->Destroy();
	DestroyAllSortMethods();
	EndDialog(hDialogTool, IDOK);
	delete OpenGLView;
	delete ArrayDataRenderer;

	DeleteArrayBuffer();

	return 0;
}