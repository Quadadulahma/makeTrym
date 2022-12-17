#include "makeTrym.h"

const int PORT = 80;
const int BACKLOG = 10;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GLFWwindow* window;
std::unique_ptr<ShaderProgram> background_shaderprogram_unq_ptr;
GLuint VAO;
GLuint VBO;
GLuint EBO;


void draw() {
	glfwMakeContextCurrent(window);
	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	background_shaderprogram_unq_ptr->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}


#ifdef PLATFORM_WINDOWS
void accept_connections(SOCKET sockfd) {
	while (true) {
	sockaddr_in client_addr;
	int client_addr_size = sizeof(client_addr);
	SOCKET client_fd = accept(sockfd, (sockaddr*)&client_addr, &client_addr_size);
	std::cout << "accepted connection" << std::endl;
 	if (client_fd == INVALID_SOCKET) {
		std::cerr << "Error accepting connection: " << WSAGetLastError() << std::endl;
		return;
	}

	char buffer[1];
	std::string message;

	while (true) {
		std::cout <<"uncompletet message :" <<  message << std::endl;
		int bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
		if (bytes_read == SOCKET_ERROR) {
			// An error occurred while reading from the socket
			// ...
			break;
		} else if (bytes_read == 0) {
			// The client closed the connection
			// ...
			break;
		} else {
			message += std::string(buffer, bytes_read);
			if (buffer[0] == '\0') {
				std::cout << "end of message" << std::endl;
			}
		}
		std::cout << "------------------" << std::endl;
	}
	std::cout << message << std::endl;
	
	// Send a message to the client
	std::string return_message = "Hello, client!\n";
	std::cout << "sending message back to client" << std::endl;
	send(client_fd, message.c_str(), message.size(), 0);
	
	// Close the client socket
	closesocket(client_fd);
	}
}
#elif PLATFORM_UNIX
void accept_connections(int sockfd) {
	
}
#endif

int main()
{
#ifdef PLATFORM_WINDOWS
	// Initialize Winsock
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0) {
		std::cerr << "Error initializing Winsock: " << result << std::endl;
		return 1;
	}

	// Create a socket
	SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == INVALID_SOCKET) {
		std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	// Bind the socket to a local address
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	if (bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		std::cerr << "Error binding socket to local address: " << WSAGetLastError() << std::endl;
		closesocket(sockfd);
		WSACleanup();
		return 1;
	}

	// Put the socket in listen mode
	if (listen(sockfd, BACKLOG) == SOCKET_ERROR) {
		std::cerr << "Error putting socket in listen mode: " << WSAGetLastError() << std::endl;
		closesocket(sockfd);
		WSACleanup();
		return 1;
	}
#endif
	std::cout << "HELLO THIS IS SLING: TYPE IN IP ADDRESS TO ASTABLISH CONNECTION. OR WAIT FOR CONNECTION" << std::endl;
	std::string ip;
	std::cin >> ip;

	if (!glfwInit()) {
		std::cout << "glfw init failed" << std::endl;
	};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	
	GLFWmonitor* main_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* main_monitor_vidmode = glfwGetVideoMode(main_monitor);
	std::cout << main_monitor_vidmode->width << " " << main_monitor_vidmode->height << std::endl;;

	window = glfwCreateWindow(main_monitor_vidmode->width/2, main_monitor_vidmode->height/2, "Sling", 0, 0);
	if (!window) {
		std::cout << "window or opengl failed" << std::endl;
	}
	glfwMakeContextCurrent(window);

	glfwSetWindowPos(window, 50,50);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

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

	background_shaderprogram_unq_ptr = std::make_unique<ShaderProgram>("Background");

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

	std::thread accept_thread(accept_connections, sockfd);
	while (!glfwWindowShouldClose(window)) {

		draw();
		glfwPollEvents();
		// Accept incoming connections
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);

	glfwTerminate();

#ifdef PLATFORM_WINDOWS
	// Close the server socket
	closesocket(sockfd);

	// Clean up Winsock
	WSACleanup();
#endif
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height);
	draw();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}