// Standard Library
#include <iostream>

// OpenGL Loader
// This can be replaced with another loader, e.g. glad, but
// remember to also change the corresponding initialize call!
#include <GL/gl3w.h>            // GL3w, initialized with gl3wInit() below

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// ImGui + imgui-vtk
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "VtkViewer.h"

// VTK
#include <vtkSmartPointer.h>
#include <vtkActor.h>

// File-Specific Includes
#include "imgui_vtk_demo.h" // Actor generator for this demo

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int argc, char* argv[])
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		return 1;
	}

	// Use GL 3.2 (All Platforms)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Decide GLSL version
#ifdef __APPLE__
  // GLSL 150
	const char* glsl_version = "#version 150";
#else
  // GLSL 130
	const char* glsl_version = "#version 130";
#endif

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Dear ImGui VTKViewer Example", NULL, NULL);
	if (window == NULL) {
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader
	if (gl3wInit() != 0) {
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows'

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	VtkViewer* vtkViewer = new VtkViewer();
	vtkViewer->getRenderer()->SetBackground(0, 0, 0); // Black background
	vtkViewer->addActors(GetConeAndOutline());

	std::vector<VtkViewer*> vtkViewers {vtkViewer};

	// Color state
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Viewports"))
			{
				static int num_viewports = 1;
				ImGui::SliderInt("# Viewports", &num_viewports, 1, 6);

				while (num_viewports < vtkViewers.size())
				{
					VtkViewer* vtkViewer = vtkViewers.back();
					vtkViewers.pop_back();

					delete vtkViewer;
				}

				while (num_viewports > vtkViewers.size())
				{
					VtkViewer* vtkViewer = new VtkViewer();
					vtkViewer->getRenderer()->SetBackground(0, 0, 0); // Black background
					vtkViewer->addActor(GetLorenzAttractor());

					vtkViewers.push_back(vtkViewer);
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static bool fullscreen = true;

			if (fullscreen)
			{
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);

				fullscreen = false;
			}

			int num_viewport = 1;
			for (auto& vtkViewer : vtkViewers)
			{
				std::string title = "Viewport window: " + std::to_string(num_viewport++);
				ImGui::Begin(title.c_str(), nullptr, VtkViewer::NoScrollFlags());                          // Create a window called "Hello, world!" and append into it.
				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

				auto renderer = vtkViewer->getRenderer();

				vtkActorCollection* actors = renderer->GetActors();
				actors->InitTraversal();
				for (int i = 0; i < actors->GetNumberOfItems(); i++)
				{
					double actor_color[3]{ clear_color.x, clear_color.y, clear_color.z };

					actors->GetNextActor()->GetProperty()->SetColor(actor_color);
				}

				// Background color
				if (ImGui::Button("VTK Background: Black")) {
					renderer->SetBackground(0, 0, 0);
				}
				ImGui::SameLine();
				if (ImGui::Button("VTK Background: Red")) {
					renderer->SetBackground(1, 0, 0);
				}
				ImGui::SameLine();
				if (ImGui::Button("VTK Background: Green")) {
					renderer->SetBackground(0, 1, 0);
				}
				ImGui::SameLine();
				if (ImGui::Button("VTK Background: Blue")) {
					renderer->SetBackground(0, 0, 1);
				}
				static float vtk2BkgAlpha = 0.2f;
				ImGui::SliderFloat("Background Alpha", &vtk2BkgAlpha, 0.0f, 1.0f);
				renderer->SetBackgroundAlpha(vtk2BkgAlpha);

				vtkViewer->render();

				ImGui::End();
			}
		}

		ImGui::Render();

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}