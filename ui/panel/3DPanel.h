#pragma once

#include <pch.h>
#include <ui/panel/IPanel.hpp>
#include <ui/panel/Console.h>

namespace ui
{
	namespace panel
	{
		class ThreeDPanel : public IPanel
		{
		public:

			ThreeDPanel(const std::string& name);

			// Inherited via IPanel
			void gui() override;
			void render() override;

		private:

			ImVec4 backgroundColor;

			VtkViewer* vtkViewer = nullptr;
		};
	}
}