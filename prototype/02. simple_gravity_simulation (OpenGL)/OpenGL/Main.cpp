// For Socket Communication
// rapidjson 포함 순서에 따라 빌드 오류 발생 가능 (원인 미파악)
#include <thread>
#include <map>
#include "rapidjson/document.h"
// Socket Custom
#include "MySocket.h"

// For OpenGL
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<Windows.h>

// OpenGL Custom
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"

using namespace std;

struct GameObject
{
	string name;
	float pos[];
};

void GetPosFromSocket(GameObject* gameObject, int* count) {
	float scale_factor = 0.01;
	MySocket s;
	s.Init();
	s.Connect();
	while (true) {
		std::string data = s.Recv();
		std::cout << data << std::endl;
		rapidjson::Document doc;
		doc.Parse(data.c_str());
		if (doc.HasParseError())
		{
			std::cout << "json data parsing failed";
		}

		// C++ 11 이상 문법
		for (auto& v : doc.GetArray())
		{
			if (v["name"].GetString() == (*gameObject).name)
			{
				(*gameObject).pos[0] = v["pos"][0].GetFloat() * scale_factor;
				(*gameObject).pos[1] = v["pos"][1].GetFloat() * scale_factor;
				*count += 1;
				cout << *count << endl;
			}
		}
	}
}

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
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// Loads GameObjects
	GameObject Dot_01;
	Dot_01.name = "Dot_01";

	int num = 0;
	int count = 0;

	GLfloat vertices[] =
	{
		-0.02f, 0.0f, 0.0f,
		0.02f, 0.0f, 0.0f,
		0.0f, 0.02f, 0.0f,
	};

	thread t1(GetPosFromSocket, &Dot_01, &count);

	int vertices_size = sizeof(vertices);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		if (count > num)
		{
			num = count;
			GLfloat* new_vertices = CalVertByPos(vertices, Dot_01.pos, 3, 3, vertices_size);
			Shader shadeProgram("default.vert", "default.frag");
			DrawTriangle(new_vertices, vertices_size, shadeProgram, window);
			shadeProgram.Delete();
		}
		// Take care of all GLFW events
		glfwPollEvents();
	}

	t1.join();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}