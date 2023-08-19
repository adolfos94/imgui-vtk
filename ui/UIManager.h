#pragma once

#include <pch.h>
#include <ui/panel/IPanel.hpp>
#include <ui/panel/Inspector.h>
#include <ui/panel/Console.h>
#include <ui/panel/3DPanel.h>

namespace ui
{
	class UIManager
	{
	public:

		UIManager() {};
		~UIManager() {};

		void render();

	private:

		void menu_gui();
		void dock_gui();

		const std::list<ui::panel::IPanel*> m_panels
		{
			new ui::panel::InspectorPanel(INSPECTOR_PANEL_NAME),
			new ui::panel::ThreeDPanel(SCENE_PANEL_NAME),
			new ui::panel::ConsolePanel(CONSOLE_PANEL_NAME),
		};
	};
}