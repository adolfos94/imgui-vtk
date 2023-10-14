#pragma once

#include <pch.h>
#include <ui/panel/IPanel.hpp>

namespace ui
{
	namespace panel
	{
		class ConsolePanel : public IPanel
		{
		public:
			ConsolePanel(const std::string &name);

			// Inherited via IPanel
			void gui() override;
			void render() override;

			static void Clear()
			{
				Buf.clear();
				LineOffsets.clear();
				LineOffsets.push_back(0);
			}

			static void InfoLog(const char *fmt, ...) IM_FMTARGS(1)
			{
				int old_size = Buf.size();
				va_list args;
				va_start(args, fmt);
				Buf.appendf("[INFO] ");
				Buf.appendfv(fmt, args);
				Buf.appendf("\n");
				va_end(args);
				for (int new_size = Buf.size(); old_size < new_size; old_size++)
					if (Buf[old_size] == '\n')
						LineOffsets.push_back(old_size + 1);
			}

			static void WarnLog(const char *fmt, ...) IM_FMTARGS(1)
			{
				int old_size = Buf.size();
				va_list args;
				va_start(args, fmt);
				Buf.appendf("[WARN] ");
				Buf.appendfv(fmt, args);
				Buf.appendf("\n");
				va_end(args);
				for (int new_size = Buf.size(); old_size < new_size; old_size++)
					if (Buf[old_size] == '\n')
						LineOffsets.push_back(old_size + 1);
			}

			static void ErrorLog(const char *fmt, ...) IM_FMTARGS(1)
			{
				int old_size = Buf.size();
				va_list args;
				va_start(args, fmt);
				Buf.appendf("[ERROR] ");
				Buf.appendfv(fmt, args);
				Buf.appendf("\n");
				va_end(args);
				for (int new_size = Buf.size(); old_size < new_size; old_size++)
					if (Buf[old_size] == '\n')
						LineOffsets.push_back(old_size + 1);
			}

		private:
			static ImGuiTextBuffer Buf;
			static ImGuiTextFilter Filter;
			static ImVector<int> LineOffsets;
			static bool AutoScroll;

			static void TextColor(const char *text, const char *text_end = (const char *)0);
		};
	}
}