#include "stdafx.h"
#include "COpenGLTextRender.h"

#define MAX_CHAR       128

COpenGLTextRender::COpenGLTextRender(COpenGLView *view)
{
	View = view;
}
COpenGLTextRender::~COpenGLTextRender()
{
}

bool COpenGLTextRender::Init()
{
	// 申请MAX_CHAR个连续的显示列表编号
	lists = glGenLists(MAX_CHAR);
	// 把每个字符的绘制命令都装到对应的显示列表中
	wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	return true;
}
void COpenGLTextRender::DrawString(const char* str) {
	// 调用每个字符对应的显示列表，绘制每个字符	
	glPushAttrib(GL_LIST_BIT);
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
	glPopAttrib();
}
void COpenGLTextRender::DrawStringPos(const char * str, float x, float y)
{
	glRasterPos2f(x, y);
	DrawString(str);
	glFlush();
}
void COpenGLTextRender::Destroy()
{
	glDeleteLists(lists, MAX_CHAR);
}
