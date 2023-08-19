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

			ThreeDPanel(const std::string& name);

			// Inherited via IPanel
			void gui(std::list<IPanel*>::iterator it) override;
			void render() override;

		private:
		};
	}
}