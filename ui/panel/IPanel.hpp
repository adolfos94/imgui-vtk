#pragma once

#include <pch.h>

namespace ui
{
	namespace panel
	{
		class IPanel
		{
		public:

			IPanel(ImGuiDir_ _direction) 
			{
				direction = _direction;
			};

			void addPanelCallbak(std::function<void(ImGuiDir_)> callback)
			{
				addPanel = callback;
			}

			virtual void gui() = 0;

			virtual void render() = 0;

		protected:

			std::string m_name;
			ImGuiDir_ direction;

			void begin_gui()
			{
				ImGui::Begin(m_name.c_str(), nullptr, ImGuiWindowFlags_MenuBar);

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Panel"))
					{
						if (ImGui::MenuItem("Split Right"))
							addPanel(ImGuiDir_Right);

						if (ImGui::MenuItem("Split Left"))
							addPanel(ImGuiDir_Left);

						if (ImGui::MenuItem("Split Down"))
							addPanel(ImGuiDir_Down);

						if (ImGui::MenuItem("Split Up"))
							addPanel(ImGuiDir_Up);

						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
			}

			void end_gui()
			{
				ImGui::End();
			}

		private:
		
			std::function<void(ImGuiDir_)> addPanel;
			std::function<void()> removePanel;
		};
	}
}