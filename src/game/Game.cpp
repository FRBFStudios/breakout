#include "Game.h"
#include "../src/gfx/ResourceManager.h"

SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height) {

}

Game::~Game() {
	Renderer->~SpriteRenderer();
}

void Game::Init() {
	ResourceManager::LoadShader("src/shaders/default.vert", "src/shaders/default.frag", nullptr, "sprite");
	// configure shaders
	glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(this->width),
		static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").activate().setInteger("image", 0);
	ResourceManager::GetShader("sprite").setMatrix4("projectionMatrix", projectionMatrix);

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("resources/awesomeface.png", true, "face");
}

void Game::UpdateDimensions(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;

	glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(this->width),
		static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").setMatrix4("projectionMatrix", projectionMatrix);
}


void Game::ProcessInput(float dt) {

}

void Game::Update(float dt) {

}

void Game::Render() {
	Texture texture = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(texture,
	glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}