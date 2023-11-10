#include "OpenGLContext.h"

static void glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool render::OpenGLContext::init(window::IWindow *window)
{
	IRenderContext::init(window);

	// Setup window
	glfwSetErrorCallback(glfw_error_callback);

	/* Initialize the library */
	if (!glfwInit())
	{
		fprintf(stderr, "Error: GLFW Window couldn't be initialized\n");
		return false;
	}

	// Use GL 3.2 (All Platforms)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window with graphics context
	GLFWwindow *glWindow = glfwCreateWindow(	
		m_Window->m_Width,
		m_Window->m_Height,
		m_Window->m_Title.c_str(),
		NULL, NULL);

	// Set GLFWwindow to GLWindow
	m_Window->SetWindow(glWindow);

	if (!glWindow)
	{
		fprintf(stderr, "Error: GLFW Window couldn't be created\n");
		return false;
	}

	glfwMakeContextCurrent(glWindow);
	glfwSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader
	if (gl3wInit() != 0)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	return true;
}

void render::OpenGLContext::pre_render()
{
	glViewport(0, 0, m_Window->m_Width, m_Window->m_Height);
	glClear(GL_COLOR_BUFFER_BIT);
}

void render::OpenGLContext::post_render()
{
	// TODO Check if glfwPollEvents needs to be moved to pre_render()
	glfwPollEvents();
	glfwSwapBuffers((GLFWwindow *)m_Window->GetWindow());
}

void render::OpenGLContext::end()
{
	glfwDestroyWindow((GLFWwindow *)m_Window->GetWindow());
	glfwTerminate();
}
