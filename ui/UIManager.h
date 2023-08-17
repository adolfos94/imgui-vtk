#pragma once

#include <pch.h>
#include <ui/panel/IPanel.hpp>
#include <ui/panel/3DPanel.h>

namespace ui
{
	class UIManager
	{
	public:

		UIManager();

		void render();

		void add_panel(ImGuiDir_ direction);

	private:

		std::list<ui::panel::IPanel*> m_panels;
	};
}