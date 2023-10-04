#include "UIManager.h"

void ui::UIManager::render()
{
	menu_gui();
	dock_gui();

	for (auto& panel : m_panels)
	{
		panel->gui();
		panel->render();
	}
}

void ui::UIManager::menu_gui()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate
		);

		ImGui::EndMainMenuBar();
	}
}

void ui::UIManager::dock_gui()
{
	if (!m_dock)
		return;

	ImVec2 workPos = ImGui::GetMainViewport()->WorkPos;
	workPos.y += ImGui::GetFrameHeight();

	ImVec2 workSize = ImGui::GetMainViewport()->WorkSize;

	ImGuiID id = ImGui::GetID("MainWindowGroup");
	ImGui::DockBuilderRemoveNode(id);
	ImGui::DockBuilderAddNode(id);

	ImGui::DockBuilderSetNodeSize(id, workSize);
	ImGui::DockBuilderSetNodePos(id, workPos);

	m_dockInspector = ImGui::DockBuilderSplitNode(id, ImGuiDir_Left, 0.2f, nullptr, &id);
	m_dockScene = ImGui::DockBuilderSplitNode(id, ImGuiDir_Right, 0.8f, nullptr, &id);
	m_dockConsole = ImGui::DockBuilderSplitNode(m_dockScene, ImGuiDir_Down, 0.2f, nullptr, &m_dockScene);

	ImGui::DockBuilderDockWindow(INSPECTOR_PANEL_NAME, m_dockInspector);
	ImGui::DockBuilderDockWindow(SCENE_PANEL_NAME, m_dockScene);
	ImGui::DockBuilderDockWindow(CONSOLE_PANEL_NAME, m_dockConsole);

	ImGui::DockBuilderFinish(id);

	m_dock = false;
}