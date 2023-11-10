#include "UIManager.h"

void ui::UIManager::render()
{
	RenderGui();
	
	for (auto& panel : m_panels)
	{
		panel->gui();
		panel->render();
	}
}

void ui::UIManager::RenderGui()
{
	// Manipulate the window flags to make it inaccessible to the user (no titlebar, resize/move, or navigation)
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	
	auto viewport = ImGui::GetMainViewport();
	
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	
	// Remove padding
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Dock Space", nullptr, window_flags);
	ImGui::PopStyleVar();
	
	// MenuBar
	if (ImGui::BeginMenuBar())
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
					1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate
					);
		
		ImGui::EndMenuBar();
	}
	
	// Dock space
	ImGuiID dock_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dock_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
	
	// Dock windows
	DockGui(dock_id);
	
	ImGui::End();
}

void ui::UIManager::DockGui(ImGuiID dock_id)
{
	static bool dock = true;
	
	if (!dock)
		return;
	
	ImVec2 workPos = ImGui::GetMainViewport()->WorkPos;
	ImVec2 workSize = ImGui::GetMainViewport()->WorkSize;
	
	ImGui::DockBuilderRemoveNode(dock_id);
	ImGui::DockBuilderAddNode(dock_id);
	
	ImGui::DockBuilderSetNodeSize(dock_id, workSize);
	ImGui::DockBuilderSetNodePos(dock_id, workPos);
	
	m_dockInspector = ImGui::DockBuilderSplitNode(dock_id, ImGuiDir_Left, 0.2f, nullptr, &dock_id);
	m_dockScene = ImGui::DockBuilderSplitNode(dock_id, ImGuiDir_Right, 0.8f, nullptr, &dock_id);
	m_dockConsole = ImGui::DockBuilderSplitNode(m_dockScene, ImGuiDir_Down, 0.2f, nullptr, &m_dockScene);
	
	ImGui::DockBuilderDockWindow(INSPECTOR_PANEL_NAME, m_dockInspector);
	ImGui::DockBuilderDockWindow(SCENE_PANEL_NAME, m_dockScene);
	ImGui::DockBuilderDockWindow(CONSOLE_PANEL_NAME, m_dockConsole);
	
	ImGui::DockBuilderFinish(dock_id);
	
	dock = false;
}
