#pragma once

namespace window
{
	class IWindow
	{
	public:

		size_t m_Width;
		size_t m_Height;
		std::string m_Title;

		virtual void* GetWindow() = 0;

		virtual void SetWindow(void* window) = 0;
	};
}