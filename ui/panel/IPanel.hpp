#pragma once

#include <pch.h>

constexpr char* INSPECTOR_PANEL_NAME = "Inspector";
constexpr char* CONSOLE_PANEL_NAME = "Console";
constexpr char* SCENE_PANEL_NAME = "3D Scene";

namespace ui
{
	namespace panel
	{
		class IPanel
		{
		public:

			virtual void gui() = 0;
			virtual void render() = 0;

		protected:

			bool m_open = true;
			std::string m_name;

		private:

		};
	}
}