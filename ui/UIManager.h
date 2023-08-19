#pragma once

#include <pch.h>
#include <ui/panel/IPanel.hpp>
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

		std::mutex m_panels_mutex;

		std::list<ui::panel::IPanel*> m_panels;

		void menu_gui();
		void sidebar_gui();

		void add_panel(ui::panel::IPanel::PanelType panelType);
		void remove_panel(std::list<ui::panel::IPanel*>::iterator it);
	};
}