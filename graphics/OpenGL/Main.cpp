#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<Windows.h>

#include"VAO.h"
#include"VBO.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // pointer index
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

int main()
{
	glfwInit();

	// GLFW 버전 명시
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// OPENGL 프로필 설정 (Core 프로필)
	// Core 프로필: 최신 함수들만 사용
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices_1[] =
	{
		-0.09f, -0.088f, 0.0f,
		0.11f, -0.088f, 0.0f,
		0.01f, -0.012f, 0.0f,
	};
	GLfloat vertices_2[] =
	{
		-0.09f, -0.284f, 0.0f,
		0.11f, -0.284f, 0.0f,
		0.01f, -0.184f, 0.0f,
	};
	GLfloat vertices_3[] =
	{
		-0.09f, -0.578f, 0.0f,
		0.11f, -0.578f, 0.0f,
		0.01f, -0.478f, 0.0f,
	};

	// 창 이름이 "OpenGL" 인 800 x 800 GLFWwindow 객체 생성
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();

	//Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap - up / Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices_1, sizeof(vertices_1));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	Sleep(1000);
	glfwSwapBuffers(window);

	new VBO(vertices_2, sizeof(vertices_2));
	VAO1.LinkVBO(VBO1, 0);
	Sleep(1000);
	glfwSwapBuffers(window);

	new VBO(vertices_2, sizeof(vertices_2));
	VAO1.LinkVBO(VBO1, 0);
	Sleep(1000);
	glfwSwapBuffers(window);
	// 윈도우 창 x 버튼 누를 경우에만 프로그램이 꺼지도록 설정
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{


		// Take care of all GLFW events
		glfwPollEvents();
	}

	VAO1.Unbind();
	VBO1.Unbind();
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}