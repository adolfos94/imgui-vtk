#include "UIManager.h"

void ui::UIManager::render()
{
	std::lock_guard<std::mutex> guard(m_panels_mutex);

	menu_gui();
	sidebar_gui();

	for (auto it = m_panels.begin(); it != m_panels.end(); ++it)
	{
		auto panel = (*it);

		panel->gui(it);
		panel->render();
	}
}

void ui::UIManager::menu_gui()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Panel"))
		{
			if (ImGui::MenuItem("3D Panel"))
				std::thread(&UIManager::add_panel, this, panel::IPanel::PanelType::ThreeDPanel).detach();

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void ui::UIManager::sidebar_gui()
{
}

void ui::UIManager::add_panel(ui::panel::IPanel::PanelType panelType)
{
	std::lock_guard<std::mutex> guard(m_panels_mutex);

	ui::panel::IPanel* panel = nullptr;

	switch (panelType)
	{
	case ui::panel::IPanel::ThreeDPanel:
		panel = new ui::panel::ThreeDPanel("3D Panel");
		break;
	default:
		break;
	}

	panel->removePanelCallback(std::bind(&UIManager::remove_panel, this, std::placeholders::_1));

	m_panels.push_back(panel);
}

void ui::UIManager::remove_panel(std::list<ui::panel::IPanel*>::iterator it)
{
	std::lock_guard<std::mutex> guard(m_panels_mutex);

	if (m_panels.empty())
		return;

	m_panels.erase(it);
}