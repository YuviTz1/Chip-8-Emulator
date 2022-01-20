#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"shader_class.h"
#include"Chip8.h"

class renderer
{
private:
	unsigned int VBO, VAO, EBO;
	Shader myShader;
	int scale = 15;			// chip-8 has a resolution of just 64*32 :)

public:
	GLFWwindow* window;

	renderer();
	~renderer();

	void updateQuad(uint32_t video[64*32], uint8_t keys[16]);
	void drawQuad(float vertices[], unsigned int indices[], int sizeofVertices, int sizeofIndices);
	void processInput(GLFWwindow* window, uint8_t keys[16]);
};

