#include "Game.h"
#include "../src/gfx/ResourceManager.h"

Game::Game(unsigned int width, unsigned int height) {

}

Game::~Game() {

}

void Game::Init() {
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
		static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").activate().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").setMatrix4("projection", projection);
	// set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// load textures
	ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
}

void Game::ProcessInput(float dt) {

}

void Game::Update(float dt) {

}

void Game::Render() {

}