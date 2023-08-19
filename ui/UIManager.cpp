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
	static bool dock = true;

	if (!dock)
		return;

	ImVec2 workPos = ImGui::GetMainViewport()->WorkPos;
	workPos.y += ImGui::GetFrameHeight();

	ImVec2 workSize = ImGui::GetMainViewport()->WorkSize;

	ImGuiID id = ImGui::GetID("MainWindowGroup");	
	ImGui::DockBuilderRemoveNode(id);
	ImGui::DockBuilderAddNode(id);

	ImGui::DockBuilderSetNodeSize(id, workSize);
	ImGui::DockBuilderSetNodePos(id, workPos);

	ImGuiID dockInspector = ImGui::DockBuilderSplitNode(id, ImGuiDir_Left, 0.2f, nullptr, &id);
	ImGuiID dockScene = ImGui::DockBuilderSplitNode(id, ImGuiDir_Right, 0.8f, nullptr, &id);
	ImGuiID dockConsole = ImGui::DockBuilderSplitNode(dockScene, ImGuiDir_Down, 0.2f, nullptr, &dockScene);

	ImGui::DockBuilderDockWindow(INSPECTOR_PANEL_NAME, dockInspector);
	ImGui::DockBuilderDockWindow(SCENE_PANEL_NAME, dockScene);
	ImGui::DockBuilderDockWindow(CONSOLE_PANEL_NAME, dockConsole);

	ImGui::DockBuilderFinish(id);

	dock = false;
}

