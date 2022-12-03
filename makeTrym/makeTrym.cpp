#include "makeTrym.h"


int main()
{
	std::cout << "Hello CMake." << std::endl;
	std::cout << std::endl;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(500,500,"hasoidj",0,0);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
