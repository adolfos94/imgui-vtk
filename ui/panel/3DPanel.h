#pragma once

#include <pch.h>
#include <ui/panel/IPanel.hpp>

namespace ui
{
	namespace panel
	{
		class ThreeDPanel : public IPanel
		{
		public:

			ThreeDPanel(const std::string& name, ImGuiDir_ _direction = ImGuiDir_Left);

			// Inherited via IPanel
			void gui() override;
			void render() override;

		private:

			
		
		};
	}
}