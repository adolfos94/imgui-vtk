#include "3DPanel.h"

void ui::panel::ThreeDPanel::gui(std::list<IPanel*>::iterator it)
{
	__super::begin_gui(it);

	ImGui::Text(GetID().c_str());

	__super::end_gui();
}

void ui::panel::ThreeDPanel::render()
{
}

ui::panel::ThreeDPanel::ThreeDPanel(const std::string& name)
{
	m_name = name;
}