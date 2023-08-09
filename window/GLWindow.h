#pragma once

#include <pch.h>
#include <IWindow.hpp>
#include <OpenGLContext.h>
#include <UIContext.h>

namespace window
{
	class GLWindow : IWindow
	{
	public:
		GLWindow();

		void init(int width, int height, const std::string& title);
		void render();
		void end();

		bool is_running() { return m_IsRunning; }

		// Inherited via IWindow
		virtual void* GetWindow() override
		{
			return m_Window;
		}

		virtual void SetWindow(void* window) override
		{
			m_Window = (GLFWwindow*)window;
		}

	private:

		bool m_IsRunning = false;
		GLFWwindow* m_Window = nullptr;

		// Render contexts
		std::unique_ptr<render::OpenGLContext> m_OpenGLRender;
		std::unique_ptr<render::UIContext> m_UIRender;
	};
}