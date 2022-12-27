#pragma once

#include <vector>
#include "../../glad/include/glad/glad.h"
#include "../ShaderProgram.h"
#include "../../glm/glm/glm.hpp"
#include "../Texture.h"
#include "../util.h"

class Game_Background {
public:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Texture texture0;

	ShaderProgram background_program;
	std::vector<float> Mesh;
	std::vector<unsigned int> indices;
	Game_Background();
	~Game_Background();
	void draw_background(int window_width, int window_height, float time);

};


class Create_Lobby_Button {
public:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Texture texture0;

	ShaderProgram background_program;
	std::vector<float> Mesh;
	std::vector<unsigned int> indices;
	Create_Lobby_Button();
	~Create_Lobby_Button();
	void draw_button(int window_width, int window_height, float time, double mouseX, double mouseY);

	bool mouse_on_hitbox(double mouseX, double mouseY, double window_width, double window_height);
};

class Join_Lobby_Button {
public:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	Texture texture0;
	ShaderProgram background_program;
	std::vector<float> Mesh;
	std::vector<unsigned int> indices;
	Join_Lobby_Button();
	~Join_Lobby_Button();
	void draw_button(int window_width, int window_height, float time, double mouseX, double mouseY);

};

class Player {
public:
	float position_x;
	float position_y;

	float rotation;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Texture texture0;

	ShaderProgram player_shader;
	std::vector<float> Mesh;
	std::vector<unsigned int> indices;
	Player();
	~Player();
	void draw_Player(int window_width, int window_height, float time);
};
