#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<Windows.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"

float pos[] = { 0.5, 0.5 };

/*
pos = [x, y]
count = vertex number 

ex) vertices = [1, 1, 0, 5, 4, 0]
count = 2, offset = 3

vertices + pos = [1+x, 1+y, 0, 5+x, 4+y, 0]
=> vertices[0]/[3]  + x
*/

GLfloat* CalVertByPos(GLfloat* vertices, float* pos, int count, int offset, int size)
{
	if (size != count * offset * sizeof(vertices[0]))
	{
		std::cout << "CalVertByPos Invalid: arr_num != count * offset" << std::endl;
	}
	GLfloat* new_vertices = new GLfloat[count * offset]();
	memcpy(new_vertices, vertices, size);
	for (int i = 0; i < count; i++)
	{
		new_vertices[i*offset] += pos[0];
		new_vertices[i*offset + 1] += pos[1];
	}
	return new_vertices;
}

void DrawTriangle(GLfloat* vertices, int size, Shader shadeProgram, GLFWwindow* window)
{
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, size);
	VAO1.LinkVBO(VBO1, 0);

	glClear(GL_COLOR_BUFFER_BIT);
	shadeProgram.Activate();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glfwSwapBuffers(window);

	VAO1.Unbind();
	VBO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
}

int main()
{
	// init window & viewport
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.02f, 0.0f, 0.0f,
		0.02f, 0.0f, 0.0f,
		0.0f, 0.02f, 0.0f,
	};

	int vertices_size = sizeof(vertices);
	GLfloat* new_vertices = CalVertByPos(vertices, pos, 3, 3, vertices_size);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	Shader shadeProgram("default.vert", "default.frag");
	DrawTriangle(new_vertices, vertices_size, shadeProgram, window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Take care of all GLFW events
		glfwPollEvents();
	}

	shadeProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}