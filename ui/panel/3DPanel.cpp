#include "3DPanel.h"

void ui::panel::ThreeDPanel::gui()
{
	ImGuiWindow* cur_window = ImGui::FindWindowByName(m_name.c_str());

	if (cur_window && cur_window->Hidden)
		return;

	ImGui::Begin(INSPECTOR_PANEL_NAME);

	if (ImGui::CollapsingHeader(m_name.c_str()))
	{
		ImGui::Text("Scene");
		ImGui::Separator();
		ImGui::ColorEdit3(GenerateNameWithID("Background Color").c_str(), (float*)&backgroundColor);
	}

	ImGui::End();
}

void ui::panel::ThreeDPanel::render()
{
	ImGui::Begin(m_name.c_str());

	auto renderer = vtkViewer->getRenderer();
	renderer->SetBackground(backgroundColor.x, backgroundColor.y, backgroundColor.z);

	vtkViewer->render();

	ImGui::End();
}

ui::panel::ThreeDPanel::ThreeDPanel(const std::string& name)
{
	m_name = name;

	vtkViewer = new VtkViewer();
	vtkViewer->addActors(GetConeAndOutline());
}