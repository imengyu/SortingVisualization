#pragma once
#include "COpenGLRenderer.h"

class CArrayDataRenderer :
	public COpenGLRenderer
{
public:
	CArrayDataRenderer();
	~CArrayDataRenderer();

	bool Init();
	void Render(float FrameTime);
	void Resize(int Width, int Height);
	void Destroy();

	int *arrayBuffer;
	int *arrayAccessBuffer;
	int *arrayCompareBuffer;
	int arrayLength;
	int arrayMaxValue;
	int accessCount;
	int compareCount;

	void SetSortMethodName(LPCWSTR name);

private:
	char sortMethodName[50];
	char accessCountBuffer[50];
	char compareCountBuffer[50];

};

