#include "UIManager.h"


void ui::UIManager::render()
{
	for (auto& panel : m_panels)
	{
		panel->gui();
		panel->render();
	}

}

void ui::UIManager::add_panel(ImGuiDir_ direction)
{
	auto panel = new ui::panel::ThreeDPanel("3D Panel #" + std::to_string(m_panels.size()), direction);
	panel->addPanelCallbak(std::bind(&UIManager::add_panel, this, direction));

	m_panels.push_back(panel);
}


ui::UIManager::UIManager()
{
	add_panel(ImGuiDir_Left);
}