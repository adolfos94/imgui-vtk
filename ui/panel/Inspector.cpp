#include "Inspector.h"

void ui::panel::InspectorPanel::gui()
{
}

void ui::panel::InspectorPanel::render()
{
	ImGui::Begin(m_name.c_str(), nullptr, ImGuiWindowFlags_NoMove);

	ImGui::End();
}

ui::panel::InspectorPanel::InspectorPanel(const std::string& name)
{
	m_name = name;
}
