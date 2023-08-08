#include <pch.h>
#include <application.h>

int main(int argc, char* argv[])
{
	auto app = std::make_unique<Application>("ImGui VTK");

	app->loop();

	return 0;
}