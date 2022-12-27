#include "Game.h"


void init_game() {
	if (!glfwInit()) {
		std::cout << "glfw init failed" << std::endl;
	};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	//glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

	GLFWmonitor* main_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* main_monitor_vidmode = glfwGetVideoMode(main_monitor);
	std::cout << main_monitor_vidmode->width << " " << main_monitor_vidmode->height << std::endl;;


	window_width = main_monitor_vidmode->width / 2;
	window_height = main_monitor_vidmode->height / 2;
	window_width = 500;
	window_height = 500;
	window = glfwCreateWindow(window_width, window_height, "Sling", 0, 0);

	if (!window) {
		std::cout << "window or opengl failed" << std::endl;
	}
	glfwMakeContextCurrent(window);

	glfwSetWindowPos(window, 50, 50);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	int version = gladLoadGL();
	std::cout << version << std::endl;
	if (version == 0) {
		printf("Failed to initialize OpenGL context\n");

	}
	start_time_global = std::chrono::steady_clock::now();

#ifdef PLATFORM_WINDOWS
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Create the socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		// An error occurred
		std::cout << "an error accured (WSASTartup) " << std::endl;
	}
#endif

	game_background_ptr = std::make_unique<Game_Background>();
	create_lobby_button_ptr = std::make_unique<Create_Lobby_Button>();
	join_lobby_button_ptr = std::make_unique<Join_Lobby_Button>();
	p = std::make_unique<Player>();
}
void run()
{
	set_gamestate_lobby();
	while (!glfwWindowShouldClose(window)) {
		prepare_frame();
		specific_update();
		specific_draw();
		finish_frame();
	}
}
void set_gamestate_maingame()
{
	key_callback_specific_ptr = main_game_key_callback;
	mouse_callback_specific_ptr = main_game_mouse_callback;
	specific_draw = show_main_game;

	p->position_x = 0;
	p->position_y = 0;
}

void set_gamestate_lobby()
{
	key_callback_specific_ptr = lobby_key_callback;
	mouse_callback_specific_ptr = lobby_mouse_callback;
	specific_draw = show_lobby_screen;
	specific_update = update_main_game;
}

void show_main_game() {
	//RENDER HERE
	game_background_ptr->draw_background(window_width, window_height, application_time);
	p->draw_Player(window_width, window_height, application_time);
}

void update_main_game() {
	p->rotation = atan2((mouseX - (p->position_x + window_width) / 2), (mouseY - (p->position_y + window_height) / 2));
	if (keyboard[GLFW_KEY_W]) {
		vol_y += 10.0;
	}
	if (keyboard[GLFW_KEY_S]) {
		vol_y -= 10.0;
	}
	if (keyboard[GLFW_KEY_D]) {
		vol_x += 10.0;
	}
	if (keyboard[GLFW_KEY_A]) {
		vol_x -= 10.0;
	}
	p->position_y += vol_y * deltaT;
	p->position_x += vol_x * deltaT;
	if (p->position_y > window_height) {
		p->position_y = -window_height;
	}
	if (p->position_x > window_width) {
		p->position_x = -window_width;
	}
	if (p->position_y < -window_height) {
		p->position_y = window_height;
	}
	if (p->position_x < -window_width) {
		p->position_x = window_width;
	}
}

void prepare_frame() {

	start_time_frame = std::chrono::steady_clock::now();
	glfwMakeContextCurrent(window);
	glfwPollEvents();
	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseY = window_height - mouseY;

	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void finish_frame() {
	glfwSwapBuffers(window);

	auto end_time = std::chrono::steady_clock::now();
	double elapsed_time = std::chrono::duration<double>(end_time - start_time_frame).count();
	if (elapsed_time < target_elapsed_time) {
		std::chrono::milliseconds time_to_wait = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(target_elapsed_time - elapsed_time));
		std::this_thread::sleep_for(time_to_wait);
		auto time_after_sleep = std::chrono::steady_clock::now();
		elapsed_time = std::chrono::duration<double>(time_after_sleep - start_time_frame).count();
	}
	auto time_now = std::chrono::steady_clock::now();

	deltaT = std::chrono::duration<double>(time_now - start_time_frame).count();
	application_time = std::chrono::duration<double>(time_now - start_time_global).count();
}

void destroy_game() {
	glfwDestroyWindow(window);
	glfwTerminate();
}


void show_lobby_screen() {
	game_background_ptr->draw_background(window_width, window_height, application_time);
	create_lobby_button_ptr->draw_button(window_width, window_height, application_time, mouseX, mouseY);
	join_lobby_button_ptr->draw_button(window_width, window_height, application_time, mouseX, mouseY);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glfwMakeContextCurrent(window);
	window_width = width;
	window_height = height;
	glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		keyboard[key] = true;
	}
	if (action == GLFW_RELEASE) {
		keyboard[key] = false;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	key_callback_specific_ptr(window, key , scancode, action, mods);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
{
	glfwGetCursorPos(window, &mouseX,&mouseY);
	mouseY = window_height - mouseY;
	if (action == GLFW_PRESS ) {
		mouse[button] = true;
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			mouse_left_clicks.push({mouseX, mouseY});
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			mouse_right_clicks.push({ mouseX, mouseY });
		}
	}
	if (action == GLFW_RELEASE) {
		mouse[button] = false;
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			mouse_left_releases.push({ mouseX, mouseY });
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			mouse_right_releases.push({ mouseX, mouseY });
		}
	}

	mouse_callback_specific_ptr(window, button, action, mods);
}

void lobby_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void lobby_mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
		if (create_lobby_button_ptr->mouse_on_hitbox(mouseX, mouseY, window_width, window_height)) {
			set_gamestate_maingame();
		}
		else if (false) {

		}
	}


}

void main_game_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void main_game_mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
}
