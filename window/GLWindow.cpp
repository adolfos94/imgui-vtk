#include "GLWindow.h"

using namespace window;

void window::GLWindow::init(int width, int height, const std::string& title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;

	// Init OpenGL Render Context
	if (!m_OpenGLRender->init(this))
		return;

	m_IsRunning = true;
}

void window::GLWindow::render()
{
	m_OpenGLRender->pre_render();

	m_OpenGLRender->post_render();
}

void window::GLWindow::end()
{
	m_OpenGLRender->end();

	m_IsRunning = false;
}

GLWindow::GLWindow()
{
	m_OpenGLRender = std::make_unique<render::OpenGLContext>();
}