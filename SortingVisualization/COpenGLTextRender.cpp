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
	// ����MAX_CHAR����������ʾ�б���
	lists = glGenLists(MAX_CHAR);
	// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
	wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	return true;
}
void COpenGLTextRender::DrawString(const char* str) {
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�	
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
