#include "Console.h"

ImGuiTextBuffer ui::panel::ConsolePanel::Buf;
ImGuiTextFilter ui::panel::ConsolePanel::Filter;
ImVector<int>	ui::panel::ConsolePanel::LineOffsets;
bool			ui::panel::ConsolePanel::AutoScroll = true;

void ui::panel::ConsolePanel::gui()
{
}

void ui::panel::ConsolePanel::render()
{
	ImGui::Begin(m_name.c_str());

	// Options menu
	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-scroll", &AutoScroll);
		ImGui::EndPopup();
	}

	// Main window
	if (ImGui::Button("Options"))
		ImGui::OpenPopup("Options");
	ImGui::SameLine();

	bool clear = ImGui::Button("Clear");
	ImGui::SameLine();

	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	Filter.Draw("Filter", -100.0f);

	ImGui::Separator();

	if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
	{
		if (clear)
			Clear();

		if (copy)
			ImGui::LogToClipboard();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = Buf.begin();
		const char* buf_end = Buf.end();

		if (Filter.IsActive())
		{
			for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;

				if (Filter.PassFilter(line_start, line_end))
					TextColor(line_start, line_end);
			}
		}
		else
		{
			ImGuiListClipper clipper;
			clipper.Begin(LineOffsets.Size);
			while (clipper.Step())
			{
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
					TextColor(line_start, line_end);
				}
			}
			clipper.End();
		}

		ImGui::PopStyleVar();

		// Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
		// Using a scrollbar or mouse-wheel will take away from the bottom edge.
		if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);
	}
	ImGui::EndChild();

	ImGui::End();
}

void ui::panel::ConsolePanel::TextColor(const char* text, const char* text_end)
{
	ImVec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	std::string str(text, text_end);

	if (str.find("WARN") != std::string::npos)
		color = { 1.0f, 0.8f, 0.0f, 1.0f };
	else if (str.find("ERROR") != std::string::npos)
		color = { 0.8f, 0.2f, 0.0f, 1.0f };

	ImGui::PushStyleColor(ImGuiCol_Text, color);

	ImGui::TextUnformatted(text, text_end);

	ImGui::PopStyleColor();
}

ui::panel::ConsolePanel::ConsolePanel(const std::string& name)
{
	m_name = name;

	Clear();
	
	InfoLog("This is a info message!");
	WarnLog("This is a warning message!");
	ErrorLog("This is a error message!");
	
}