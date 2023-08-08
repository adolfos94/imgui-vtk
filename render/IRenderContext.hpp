#pragma once

#include <pch.h>
#include <window/IWindow.hpp>

namespace render
{
	class IRenderContext
	{
	public:
		IRenderContext() : m_Window(nullptr) {}

		virtual bool init(window::IWindow* window)
		{
			m_Window = window;

			return true;
		}

		virtual void pre_render() = 0;
		virtual void post_render() = 0;

		virtual void end() = 0;

	protected:

		window::IWindow* m_Window;
	};
}