#include "renderer.h"

renderer::renderer()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(64*scale, 32*scale, "Chip-8 Emulator", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	myShader.init("../../res/vertexShader.shader", "../../res/fragmentShader.shader");
	glViewport(0, 0, 64 * scale, 32 * scale);
	glClearColor(0.37647f, 0.529411f, 0.662745f, 1.0f);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
}

renderer::~renderer()
{
	glfwTerminate();
}

void renderer::updateQuad(uint32_t video[64 * 32], uint8_t keys[16])
{
	processInput(window, keys);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 64 * 32; i++)
	{
		if (video[i] > 0)
		{
			int x = i % 64, y = i / 64+1;

			// translate the coordinates to what OpenGL expects
			float x_translated = (float)(x - 32) / 32;		
			float y_translated = (float)(-y + 16) / 16;		
			float inc_x = (float)1 / 32;
			float inc_y = (float)1 / 16;

			float vertices[] =
			{
				x_translated,         y_translated, 				//top left
				x_translated + inc_x, y_translated,					//top right
				x_translated + inc_x, y_translated + inc_y,			//bottom right
				x_translated,         y_translated + inc_y			//bottom left
			};

			unsigned int indices[] =
			{
				0,1,2,
				0,3,2
			};

			drawQuad(vertices, indices, sizeof(vertices), sizeof(indices));
		}
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
	
}

void renderer::drawQuad(float vertices[], unsigned int indices[], int sizeofVertices, int sizeofIndices)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofVertices, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	myShader.use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderer::processInput(GLFWwindow* window, uint8_t keys[16])
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		keys[0] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		keys[1] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		keys[2] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		keys[3] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		keys[4] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		keys[5] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		keys[6] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		keys[7] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		keys[8] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		keys[9] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		keys[0xA] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		keys[0xB] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		keys[0xC] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		keys[0xD] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		keys[0xE] = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		keys[0xF] = 1;
	}


	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
	{
		keys[0] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE)
	{
		keys[1] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE)
	{
		keys[2] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_RELEASE)
	{
		keys[3] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
	{
		keys[4] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
	{
		keys[5] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
	{
		keys[6] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
	{
		keys[7] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
	{
		keys[8] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
	{
		keys[9] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE)
	{
		keys[0xA] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
	{
		keys[0xB] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_RELEASE)
	{
		keys[0xC] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
	{
		keys[0xD] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
	{
		keys[0xE] = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE)
	{
		keys[0xF] = 0;
	}
}
