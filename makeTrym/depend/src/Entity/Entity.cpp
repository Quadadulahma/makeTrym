#include "Entity.h"


Game_Background::Game_Background()
	: background_program("Background"),
	texture0("pic.png")
{
	Mesh = { 1.0,  1.0, 0.0, 1.0, 1.0,
			 1.0, -1.0, 0.0, 1.0, 0.0,
			-1.0, -1.0, 0.0, 0.0, 0.0,
			-1.0,  1.0, 0.0, 0.0, 1.0 };
	indices = { 0, 1, 3, 1, 2, 3 };
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Mesh.size(), &Mesh[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Game_Background::draw_background(int window_width, int window_height, float time) {
	
	background_program.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0.textureID);
	glUniform1i(glGetUniformLocation(background_program.getID(), "texture0"), 0);


	glUniform2f(glGetUniformLocation(background_program.getID(), "Window_Dimension"), (float)window_width, (float)window_height);
	glUniform1f(glGetUniformLocation(background_program.getID(), "Time"), time);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

Game_Background::~Game_Background() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

Create_Lobby_Button::Create_Lobby_Button()
	: background_program("Lobby_Button"),
	texture0("create_lobby_button.png")
{
	Mesh = { 1.0*0.8,  1.0*0.17 + 0.5, 0.0, 1.0, 1.0,
			 1.0*0.8, -1.0*0.17 + 0.5, 0.0, 1.0, 0.0,
			-1.0*0.8, -1.0*0.17 + 0.5, 0.0, 0.0, 0.0,
			-1.0*0.8,  1.0*0.17 + 0.5, 0.0, 0.0, 1.0 };
	indices = { 0, 1, 3, 1, 2, 3 };
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Mesh.size(), &Mesh[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Create_Lobby_Button::draw_button(int window_width, int window_height, float time, double mouseX, double mouseY) {
	background_program.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0.textureID);
	glUniform1i(glGetUniformLocation(background_program.getID(), "texture0"), 0);


	glUniform2f(glGetUniformLocation(background_program.getID(), "Window_Dimension"), (float)window_width, (float)window_height);
	glUniform1f(glGetUniformLocation(background_program.getID(), "Time"), time); 
	glUniform2f(glGetUniformLocation(background_program.getID(), "Mouse_Position"), (float)mouseX, (float)mouseY);


	if (mouse_on_hitbox(mouseX,mouseY, window_width, window_height)) {
		glUniform1f(glGetUniformLocation(background_program.getID(), "Mouse_on_Button"), 1.0);
	}
	else {
		glUniform1f(glGetUniformLocation(background_program.getID(), "Mouse_on_Button"), 0.0);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

bool Create_Lobby_Button::mouse_on_hitbox(double mouseX,double mouseY, double window_width, double window_height)
{
	Coord_Pos cp = {mouseX, mouseY};
	cp.transform_to_openglcoord(window_width, window_height);
	if (cp.x <= Mesh[0] && cp.x >= Mesh[10] && cp.y <= Mesh[1] && cp.y >= Mesh[11]) {
		return true;
	}
	else 
	{
		return false;
	}
}

Create_Lobby_Button::~Create_Lobby_Button() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

Player::Player() 
	:player_shader("Player"), texture0("pic2.png")
{
	Mesh = { 1.0*0.05,  1.0*0.05, 0.0, 1.0, 1.0,
			 1.0*0.05, -1.0*0.05, 0.0, 1.0, 0.0,
			-1.0*0.05, -1.0*0.05, 0.0, 0.0, 0.0,
			-1.0*0.05,  1.0*0.05, 0.0, 0.0, 1.0 };
	indices = { 0, 1, 3, 1, 2, 3 };
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Mesh.size(), &Mesh[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Player::~Player() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Player::draw_Player(int window_width, int window_height, float time)
{

	player_shader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0.textureID);
	glUniform1i(glGetUniformLocation(player_shader.getID(), "texture0"), 0);

	glUniform2f(glGetUniformLocation(player_shader.getID(), "Window_Dimension"), (float)window_width, (float)window_height);
	glUniform2f(glGetUniformLocation(player_shader.getID(), "Player_Position"), position_x, position_y);
	glUniform1f(glGetUniformLocation(player_shader.getID(), "Rotation"), rotation);

	glUniform1f(glGetUniformLocation(player_shader.getID(), "Time"), time);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}



Join_Lobby_Button::Join_Lobby_Button()
	: background_program("Lobby_Button"),
	texture0("join_lobby_button.png")
{
	Mesh = { 1.0 * 0.8,  1.0 * 0.17 + 0.1, 0.0, 1.0, 1.0,
			 1.0 * 0.8, -1.0 * 0.17 + 0.1, 0.0, 1.0, 0.0,
			-1.0 * 0.8, -1.0 * 0.17 + 0.1, 0.0, 0.0, 0.0,
			-1.0 * 0.8,  1.0 * 0.17 + 0.1, 0.0, 0.0, 1.0 };
	indices = { 0, 1, 3, 1, 2, 3 };
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Mesh.size(), &Mesh[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Join_Lobby_Button::draw_button(int window_width, int window_height, float time, double mouseX, double mouseY) {

	background_program.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0.textureID);
	glUniform1i(glGetUniformLocation(background_program.getID(), "texture0"), 0);


	glUniform2f(glGetUniformLocation(background_program.getID(), "Window_Dimension"), (float)window_width, (float)window_height);
	glUniform1f(glGetUniformLocation(background_program.getID(), "Time"), time);

	Coord_Pos cp = {mouseX, mouseY};
	cp.transform_to_openglcoord(window_width, window_height);
	
	if (cp.x <= Mesh[0] && cp.x >= Mesh[10] && cp.y <= Mesh[1] && cp.y >= Mesh[11]) {
		glUniform1f(glGetUniformLocation(background_program.getID(), "Mouse_on_Button"), 1.0);
	}
	else {
		glUniform1f(glGetUniformLocation(background_program.getID(), "Mouse_on_Button"), 0.0);
	}
	glUniform2f(glGetUniformLocation(background_program.getID(), "Mouse_Position"), (float)mouseX, (float)mouseY);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

Join_Lobby_Button::~Join_Lobby_Button() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}