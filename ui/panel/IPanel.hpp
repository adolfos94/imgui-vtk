#pragma once

#include <pch.h>

namespace ui
{
	namespace panel
	{
		class IPanel
		{
		public:

			enum PanelType
			{
				ThreeDPanel,
			};

			void removePanelCallback(std::function<void(std::list<IPanel*>::iterator)> callback)
			{
				removePanel = callback;
			}

			inline std::string GetID()
			{
				return m_name + "##" + std::to_string((size_t)this);
			}

			virtual void gui(std::list<IPanel*>::iterator it) = 0;

			virtual void render() = 0;

		protected:

			bool m_open = true;
			std::string m_name;

			void begin_gui(std::list<IPanel*>::iterator it)
			{
				ImGui::Begin(GetID().c_str(), &m_open);

				if (!m_open)
					std::thread(removePanel, it).detach();
			}

			void end_gui()
			{
				ImGui::End();
			}

		private:

			std::function<void(std::list<IPanel*>::iterator it)> removePanel;
		};
	}
}