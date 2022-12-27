#pragma once

#include "../../depend/glad/include/glad/glad.h"
#include "../../depend/glfw/include/GLFW/glfw3.h"
#include <iostream>
#include <chrono>

#include "Entity/Entity.h"
#include <thread>
#include <memory>
#include "Ring_Buffer.h"

#ifdef PLATFORM_WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>
#elif PLATFROM_UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>.
#endif

#include "util.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void lobby_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void lobby_mouse_callback(GLFWwindow* window, int button, int action, int mods);

void main_game_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void main_game_mouse_callback(GLFWwindow* window, int button, int action, int mods);

static void (*key_callback_specific_ptr)(GLFWwindow* window, int key, int scancode, int action, int mods) = nullptr;
static void (*mouse_callback_specific_ptr)(GLFWwindow* window, int button, int action, int mods) = nullptr;
static void (*specific_draw)() = nullptr;
static void (*specific_update)() = nullptr;




static GLFWwindow* window;
static int window_width;
static int window_height;
static float application_time;
static std::chrono::steady_clock::time_point start_time_global;
static std::chrono::steady_clock::time_point start_time_frame;
static double target_frame_rate = 144.0;
static double target_elapsed_time = 1.0f / target_frame_rate;
static float deltaT = 0.0;

static bool keyboard[256];
static bool mouse[8];
static Ring_Buffer<Coord_Pos, 10> mouse_left_clicks;
static Ring_Buffer<Coord_Pos, 10> mouse_left_releases;
static Ring_Buffer<Coord_Pos, 10> mouse_right_clicks;
static Ring_Buffer<Coord_Pos, 10> mouse_right_releases;

static double mouseX;
static double mouseY;
static std::unique_ptr<Game_Background> game_background_ptr;
static std::unique_ptr<Create_Lobby_Button> create_lobby_button_ptr;
static std::unique_ptr<Join_Lobby_Button> join_lobby_button_ptr;
static std::unique_ptr<Player> p;
 
static float vol_x = 0;
static float vol_y = 0;

void init_game();
void run();
void destroy_game();

void finish_frame();
void prepare_frame();


void set_gamestate_maingame();
void update_main_game();
void show_main_game();

void set_gamestate_lobby();
void show_lobby_screen();


