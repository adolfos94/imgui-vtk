#include "3DPanel.h"

ui::panel::ThreeDPanel::ThreeDPanel(const std::string& name, ImGuiDir_ _direction) : IPanel(_direction)
{
	m_name = name;
}

void ui::panel::ThreeDPanel::gui()
{
	__super::begin_gui();

	ImGui::Text("This is the 3D Panel!");

	__super::end_gui();
}

void ui::panel::ThreeDPanel::render()
{
	
}