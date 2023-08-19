#include "3DPanel.h"

void ui::panel::ThreeDPanel::gui()
{
	ImGui::Begin(INSPECTOR_PANEL_NAME);

	ImGui::Text("Scene");
	ImGui::Separator();
	ImGui::ColorEdit3("Background Color", (float*)&backgroundColor);

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