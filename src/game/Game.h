#ifndef GAME_H
#define GAME_H

#include "../gfx/SpriteRenderer.h"
#include "GameLevel.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game {
public:
	SpriteRenderer* Renderer;
	GameState state;
	bool keys[1024];
	unsigned int width, height;
	std::vector<GameLevel> Levels;
	Level activeLevel;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void UpdateDimensions(unsigned int width, unsigned int height);

	void Render();
};

#endif //GAME_H
