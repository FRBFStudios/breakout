#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/BreakoutGame.h>
#include <caffeine-gl/gfx/ResourceManager.h>

int WIDTH;
int HEIGHT;

BreakoutGame* Breakout;

bool testBool = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void error_callback(int error, const char* description);

int main() {
	glfwSetErrorCallback(error_callback);

	glfwInit();

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

	WIDTH = videoMode->width;
	HEIGHT = videoMode->height;

	Breakout = new BreakoutGame(WIDTH, HEIGHT);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Breakout", primaryMonitor, nullptr);
	if(window == nullptr) {
		std::cout << "Failed to initialize GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Breakout->Init();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;


	while(!glfwWindowShouldClose(window)) {
		const auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		Breakout->ProcessInput(deltaTime);
		Breakout->Update(deltaTime);
		Breakout->Render();

		glfwSwapBuffers(window);
	}
	ResourceManager::Clear();
	Breakout->~BreakoutGame();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	WIDTH = width;
	HEIGHT = height;

	glViewport(0, 0, width, height);
	Breakout->UpdateDimensions(width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			Breakout->keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			Breakout->keys[key] = false;
			Breakout->processedKeys[key] = false;
		}
	}
}

void error_callback(int error, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}