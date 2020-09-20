#include "stdafx.h"
#include "COpenGLView.h"
#include <stdio.h>

COpenGLView::COpenGLView(COpenGLRenderer *renderer)
{
	this->OpenGLRenderer = renderer;
	this->OpenGLTextRender = new COpenGLTextRender(this);
	this->OpenGLRenderer->View = this;
}
COpenGLView::~COpenGLView()
{
	delete this->OpenGLTextRender;
}

#define IDR_TIMER_REFESH 226

bool COpenGLView::Init(HINSTANCE hInstance, LPCWSTR Title, int Width, int Height, WNDPROC wndproc)
{
	this->Title = Title;
	this->Width = Width;
	this->Height = Height;
	this->TextPadding = 10.0f / (this->Width / 2.0f);

	WNDCLASSEX WndClassEx;

	memset(&WndClassEx, 0, sizeof(WNDCLASSEX));

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = wndproc;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.lpszClassName = L"Win32OpenGLWindow";

	if (RegisterClassEx(&WndClassEx) == 0)
	{
		WriteErrorLog(L"RegisterClassEx failed!");
		return false;
	}

	DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, WndClassEx.lpszClassName, Title, Style, 0, 0, Width, Height, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		WriteErrorLog(L"CreateWindowEx failed!");
		return false;
	}

	HDC hDC = GetDC(hWnd);

	if (hDC == NULL)
	{
		WriteErrorLog(L"GetDC failed!");
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int PixelFormat = ChoosePixelFormat(hDC, &pfd);

	if (PixelFormat == 0)
	{
		WriteErrorLog(L"ChoosePixelFormat failed!");
		return false;
	}

	if (SetPixelFormat(hDC, PixelFormat, &pfd) == FALSE)
	{
		WriteErrorLog(L"SetPixelFormat failed!");
		return false;
	}

	hGLRC = wglCreateContext(hDC);

	if (hGLRC == NULL)
	{
		WriteErrorLog(L"wglCreateContext failed!");
		return false;
	}

	if (wglMakeCurrent(hDC, hGLRC) == FALSE)
	{
		WriteErrorLog(L"wglMakeCurrent failed!");
		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		WriteErrorLog(L"glewInit failed!");
		return false;
	}

	if (WGLEW_EXT_swap_control)
	{
		wglSwapIntervalEXT(0);
	}

	Rendering = true;
	hThread = CreateThread(0, 0, RenderThread, this, 0, 0);

	sprintf_s(SizeText, "%dx%d - %s",  Width, Height, (char*)glGetString(GL_RENDERER));

	OpenGLTextRender->Init();
	if (OpenGLRenderer) 
		return OpenGLRenderer->Init();

	return false;
}
void COpenGLView::Show(bool Maximized)
{
	RECT dRect, wRect, cRect;

	GetWindowRect(GetDesktopWindow(), &dRect);
	GetWindowRect(hWnd, &wRect);
	GetClientRect(hWnd, &cRect);

	wRect.right += Width - cRect.right;
	wRect.bottom += Height - cRect.bottom;
	wRect.right -= wRect.left;
	wRect.bottom -= wRect.top;
	wRect.left = dRect.right / 2 - wRect.right / 2;
	wRect.top = dRect.bottom / 2 - wRect.bottom / 2;

	MoveWindow(hWnd, wRect.left, wRect.top, wRect.right, wRect.bottom, FALSE);
	
	ShowWindow(hWnd, Maximized ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
}
void COpenGLView::MessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
void COpenGLView::WriteErrorLog(LPCWSTR str) {
	wcscpy_s(ErrorLog, str);
}
void COpenGLView::Destroy()
{
	if (OpenGLRenderer) OpenGLRenderer->Destroy();
	wglDeleteContext(hGLRC);

	Rendering = false;
	DestroyWindow(hWnd);
}
void COpenGLView::Invalid() {
	InvalidateRect(hWnd, NULL, FALSE);
}
void COpenGLView::Render() {

	static DWORD LastFPSTime = GetTickCount(), LastFrameTime = LastFPSTime, FPS = 0;

	DWORD Time = GetTickCount();

	float FrameTime = (Time - LastFrameTime) * 0.001f;

	LastFrameTime = Time;

	if (Time - LastFPSTime > 1000)
	{
		sprintf_s(FPSText, "FPS: %d", FPS);

		LastFPSTime = Time;
		FPS = 0;
	}
	else
	{
		FPS++;
	}

	//绘制
	glClear(GL_COLOR_BUFFER_BIT);

	if (OpenGLRenderer) OpenGLRenderer->Render(FrameTime);
	else {
		//绘制警告
		glColor3f(1.0f, 0.0f, 0.0);
		OpenGLTextRender->DrawStringPos("No Render !", 0, 0);
	}

	//绘制fps
	glColor3f(1.0f, 1.0f, 1.0);
	OpenGLTextRender->DrawStringPos(FPSText, 0.8f, 0.9f - (5.0f / (Height * 2.0f)));
	OpenGLTextRender->DrawStringPos(SizeText, 0, 0.9f - (65.0f / (Height * 2.0f)));
}
	
DWORD WINAPI COpenGLView::RenderThread(LPVOID lpParam)
{
	COpenGLView * view = (COpenGLView*)lpParam;
	while (view->Rendering) {
		Sleep(40);
		view->Invalid();
	}
	return 0;
}

void COpenGLView::OnPaint()
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	Render();

	SwapBuffers(hDC);
	EndPaint(hWnd, &ps);	
}
void COpenGLView::OnSize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	sprintf_s(SizeText, "%dx%d - %s", Width, Height, (char*)glGetString(GL_RENDERER));

	if (OpenGLRenderer) OpenGLRenderer->Resize(Width, Height);
}


COpenGLRenderer * COpenGLView::GetRenderer()
{
	return OpenGLRenderer;
}
COpenGLTextRender * COpenGLView::GetTextRender()
{
	return OpenGLTextRender;
}
