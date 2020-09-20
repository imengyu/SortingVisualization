#include "stdafx.h"
#include "CArrayDataRenderer.h"
#include "CSortProvider.h"
#include "COpenGLView.h"

CArrayDataRenderer::CArrayDataRenderer()
{
}
CArrayDataRenderer::~CArrayDataRenderer()
{
}

bool CArrayDataRenderer::Init()
{
	return COpenGLRenderer::Init();
}
void CArrayDataRenderer::Render(float FrameTime)
{
	float lineWidth = (float)this->Width / (float)this->arrayLength;
	float x = -1;
	float y = 0;
	float a = 0;

	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(lineWidth);

	for (int i = 0; i < this->arrayLength && i < 4096; i++) {
		x = (float)i / this->arrayLength * 2.0f -1.0f;
		y = (this->arrayBuffer[i] / (float)this->arrayMaxValue) * 1.8f - 1.0f;

		if (this->arrayAccessBuffer[i] > 0) {
			a = 0.5f + (0.5f * (float)this->arrayAccessBuffer[i] / (float)SORT_STATUS_TICK);
			glColor3f(a, 0.0f, 0.0f);
			this->arrayAccessBuffer[i]--;
		}
		else if (this->arrayCompareBuffer[i] > 0) {
			a = 0.5f + (0.5f * (float)this->arrayCompareBuffer[i] / (float)SORT_STATUS_TICK);
			glColor3f(0, 0.0f, a);
			this->arrayCompareBuffer[i]--;
		}
		else glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_LINES);
		glVertex2f(x, y);
		glVertex2f(x, -1);
		glEnd();
	}

	//Draw string

	sprintf_s(accessCountBuffer, "Array access count : %d", accessCount);
	sprintf_s(compareCountBuffer, "Compare count : %d", compareCount);

	View->GetTextRender()->DrawStringPos(accessCountBuffer, -0.96f, 0.9f - (5.0f / (Height * 2.0f)));
	View->GetTextRender()->DrawStringPos(compareCountBuffer, -0.96f, 0.9f - (65.0f / (Height * 2.0f)));
	View->GetTextRender()->DrawStringPos(sortMethodName, -0.96f, 0.9f - (125.0f / (Height * 2.0f)));

	COpenGLRenderer::Render(FrameTime);
}
void CArrayDataRenderer::Resize(int Width, int Height)
{
	COpenGLRenderer::Resize(Width, Height);
}
void CArrayDataRenderer::Destroy()
{
	COpenGLRenderer::Destroy();
}

void CArrayDataRenderer::SetSortMethodName(LPCWSTR name)
{
	for (int i = 0, c = wcslen(name); i < c; i++)
		sortMethodName[i] = (char)name[i];
	sortMethodName[wcslen(name)] = '\0';
}
