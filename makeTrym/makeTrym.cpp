#include "makeTrym.h"


int main()
{
	std::cout << "Hello CMake." << std::endl;
	std::cout << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(500, 500, "hasoidj", 0, 0);

	glfwMakeContextCurrent(window);
	int version = gladLoadGL();
	std::cout << version << std::endl;
	if (version == 0) {
		printf("Failed to initialize OpenGL context\n");
		return -1;
	}


	float vertices[] =
	{
		1.0, 1.0,
		1.0, -1.0,
		-1.0,-1.0,
		-1.0, 1.0,
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	ShaderProgram sp = ShaderProgram("Background");

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glCreateBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glViewport(0, 0, 500, 500);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		sp.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
