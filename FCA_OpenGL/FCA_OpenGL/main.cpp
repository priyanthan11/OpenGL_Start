#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	// Initiate the window
	glfwInit();

	// Letting know which version of opengl we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating window object
	GLFWwindow* window = glfwCreateWindow(800,800,"FCA_OPENGL",NULL,NULL);
	if (window==NULL)
	{
		std::cout << "Failed to create OpenGL window" << std::endl;
		glfwTerminate();
		return -1;

	}

	// Use the created window object
	glfwMakeContextCurrent(window);

	// Window loop
	while (!glfwWindowShouldClose(window))
	{
		// poll the all events of windows
		glfwPollEvents();
	}



	// Destroy the window
	glfwDestroyWindow(window);
	// Terminate the window 
	glfwTerminate();
	return 0;
}