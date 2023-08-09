#include "GLWindow.h"

using namespace window;

void window::GLWindow::init(int width, int height, const std::string& title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;

	// Init Render Contexts
	if (!m_OpenGLRender->init(this) || !m_UIRender->init(this))
		return;


	m_IsRunning = true;
}

void window::GLWindow::render()
{
	m_OpenGLRender->pre_render();
	m_UIRender->pre_render();

	// Render panels

	m_UIRender->post_render();
	m_OpenGLRender->post_render();
}

void window::GLWindow::end()
{
	m_OpenGLRender->end();
	m_UIRender->end();

	m_IsRunning = false;
}

GLWindow::GLWindow()
{
	m_OpenGLRender = std::make_unique<render::OpenGLContext>();
	m_UIRender = std::make_unique<render::UIContext>();
}