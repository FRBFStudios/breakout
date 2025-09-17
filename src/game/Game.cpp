#include "Game.h"

#include "../src/gfx/ResourceManager.h"
#include "GLFW/glfw3.h"


Game::Game(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	this->state = GAME_ACTIVE;
	this->activeLevel = STANDARD;
}

Game::~Game() {
	Renderer->~SpriteRenderer();
}

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

void Game::Init() {
	ResourceManager::LoadShader("src/shaders/default.vert", "src/shaders/default.frag", nullptr, "sprite");

	glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(this->width),
		static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").activate().setInteger("image", 0);
	ResourceManager::GetShader("sprite").setMatrix4("projectionMatrix", projectionMatrix);

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("resources/textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("resources/textures/paddle.png", true, "paddle");

	ResourceManager::LoadTexture("resources/textures/block.png", false, "block");
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");

	GameLevel standard; standard.Load("resources/levels/standard.lvl", this->width, this->height / 2);
	GameLevel gaps; gaps.Load("resources/levels/gaps.lvl", this->width, this->height / 2);
	GameLevel space_invader; space_invader.Load("resources/levels/space_invader.lvl", this->width, this->height / 2);
	GameLevel bounce_galore; bounce_galore.Load("resources/levels/bounce_galore.lvl", this->width, this->height / 2);

	this->Levels.push_back(standard);
	this->Levels.push_back(gaps);
	this->Levels.push_back(space_invader);
	this->Levels.push_back(bounce_galore);

	this->activeLevel = SPACE_INVADER	;
	this->state = GAME_ACTIVE;

	glm::vec2 playerPos = glm::vec2(
		this->width / 2.0f - PLAYER_SIZE.x / 2.0f,
		this->height - PLAYER_SIZE.y
	);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::UpdateDimensions(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;

	glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(this->width),
		static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").setMatrix4("projectionMatrix", projectionMatrix);
}


void Game::ProcessInput(float dt) {
	if(this->state == GAME_ACTIVE) {
		float velocity = PLAYER_VELOCITY * dt;

		if(this->keys[GLFW_KEY_A]) {
			if(Player->position.x >= 0.0f) {
				Player->position.x -= velocity;
			}
		}
		if(this->keys[GLFW_KEY_D]) {
			if(Player->position.x <= this->width - Player->size.x) {
				Player->position.x += velocity;
			}
		}
	}
}

void Game::Update(float dt) {

}

void Game::Render() {
	if(this->state == GAME_ACTIVE) {
		Renderer->DrawSprite(ResourceManager::GetTexture("background"),
		   glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
		this->Levels[this->activeLevel].Draw(*Renderer);
		Player->Draw(*Renderer);
	}
}