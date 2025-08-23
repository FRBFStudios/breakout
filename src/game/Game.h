#ifndef GAME_H
#define GAME_H

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game {
	GameState state;
	bool keys[1024];
	unsigned int width, height;
	Game(unsigned int width, unsigned int height);
	~Game();
	void Init();
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};

#endif //GAME_H
