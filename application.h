#pragma once

#include <pch.h>
#include <GLWindow.h>

class Application
{
public:

	Application(const std::string& app_name);
	~Application();

	// Main render loop
	void loop();

private:

	std::unique_ptr<window::GLWindow> m_Window;
};