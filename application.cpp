#include "application.h"

void Application::loop()
{
	while (m_Window->is_running())
	{
		m_Window->render();
	}
}

Application::Application(const std::string& app_name)
{
	m_Window = std::make_unique<window::GLWindow>();
	m_Window->init(1920, 1080, app_name);
}

Application::~Application()
{
	m_Window->end();
}