#pragma once
#include "COpenGLRenderer.h"
#include "COpenGLTextRender.h"

class COpenGLView
{
protected:
	LPCWSTR Title;
	int Width, Height;
	HWND hWnd;
	HGLRC hGLRC;
	COpenGLTextRender *OpenGLTextRender = NULL;
	COpenGLRenderer *OpenGLRenderer = NULL;
	HANDLE hThread;

private:
	char FPSText[25];
	char SizeText[250];
	float TextPadding = 0;
	bool Rendering = 0;

public:
	COpenGLView(COpenGLRenderer *renderer);
	~COpenGLView();

	wchar_t ErrorLog[250];

	bool Init(HINSTANCE hInstance, LPCWSTR Title, int Width, int Height, WNDPROC wndproc);
	void Show(bool Maximized = false);
	void MessageLoop();
	void WriteErrorLog(LPCWSTR str);
	void Destroy();
	void Invalid();
	void Render();

	static DWORD WINAPI RenderThread(LPVOID lpParam);

	void OnPaint();
	void OnSize(int Width, int Height);

	char*GetFpsText() {
		return FPSText;
	}

	COpenGLRenderer * GetRenderer();
	COpenGLTextRender *GetTextRender();
};

