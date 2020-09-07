#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "glfw falled!" << std::endl;
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		std::cout << "glfwCreateWindow falled!" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
		std::cout << "Error!" << std::endl;
		return -1;
	}
	///////////////////////Инфа про рендеры и версии//////////////////////////////

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MAJOR_VERSION, &minor);

	std::cout << "GL Vendor: " << vendor << std::endl;
	std::cout << "GL Renderer: " << renderer << std::endl;
	std::cout << "GL Version(string): " << version << std::endl;
	std::cout << "GL Version(integer): " << major << "." << minor << std::endl;
	std::cout << "GLSL Version: " << glsl_version << std::endl;

	////////////////////////////////////////////////////////////////////////////////
	glClearColor(0, 0, 1, 1);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}