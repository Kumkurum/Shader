#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

GLuint vao_handle;
float position_data[] = {
	0.0f,0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	-0.5f,-0.5f,0.0f
};
float color_data[] = {
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f
};

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"//layout (=0) ������������� �������� vertex_position ����
"layout(location = 1) in vec3 vertex_color;"   //(������ ��� �� ������� ��������� ������ � ���������� � 0)
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color,1.0);"
"}";


int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "glfw falled!" << std::endl;
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);///////////// �������� ���� (�������)
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
	///////////////////////���� ��� ������� � ������//////////////////////////////

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

	///////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////������� ������ ������� 
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);//��������� ������            vs -���������� �������
	if (0 == vs) {
		std::cout << "Error creating vertex shader" << std::endl;
		return -1;
	}
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);///////////////////////////////////////���������� �������
	GLint result;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);////////// ��������� ��������� �������� ��������
	if (GL_FALSE == result) {
		std::cout << "Vertex shader compile failed! " << std::endl;
		return -1;
	}
	//////////////////////////////////����������� ������ ����� �� ��� � ��������� 
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);
	////////////////////////////////

	GLuint program_handle = glCreateProgram();///////������� ������ ���������
	glAttachShader(program_handle, vs);///// ���������� � ������� ���������
	glAttachShader(program_handle, fs);
	glLinkProgram(program_handle);/////������������ ��������� � ���� �� ����� �������� � ������� (while(!window)) glUseProgram

	/////////////////////////////////////////////////////
	//������� � ��������� �������� �������
	GLuint vbo_handles[2];
	glGenBuffers(2, vbo_handles);//��������� ����� 2 �������� �������
	GLuint position_buffer_handle = vbo_handles[0];
	GLuint color_buffer_handle = vbo_handles[1];
	//��������� ����� ������
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);//���������� ��������� ������� � ������ �������� GL_ARRAY_BUFFER(������ -�����)
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), position_data, GL_STATIC_DRAW);//����� �������� ����� ���������
	//��������� ����� ������
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer_handle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), color_data, GL_STATIC_DRAW);//GL_STATIC_DRAW ��� ���� ��� �� ������ ����� ����������� ���������� � �������

	//////////////////// �������� 39 ����� 3//////////////////
	//����� ��������� �������� �������� �� ����� ���������� � ����� ������� ������ VAO
	//�������� ������� ������� ������
	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);//���������� ����������� ������ ������� � ���������� ���������� vao_handle 

	/////////////////////////////////////////

	glEnableVertexAttribArray(0);//���� ������
	glEnableVertexAttribArray(1);//���� ������

	/////////////////////////////////////////

	//��������� ������ 0 �� ������� � ������������
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//1 - ������ 2 - ����� ����������� �� ���� ������� 3 -��� ������ 4 -����� ������������ 5 -���(��������)

	////////////////////////////////////////////////////////
	//��������� ������ 1 �� �������� � ������
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	/////////////////////////////////////////////////////////////



		glClearColor(0, 0, 1, 1);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program_handle); //���������� ��������� � �������!

		glBindVertexArray(vao_handle);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}