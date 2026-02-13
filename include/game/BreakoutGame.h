#ifndef BREAKOUTGAME_H
#define BREAKOUTGAME_H

#include "caffeine-gl/game/Game.h"

#include "caffeine-gl/game/BallClass.h"
#include "caffeine-gl/gfx/SpriteRenderer.h"
#include "caffeine-gl/game/GameLevel.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
typedef std::tuple<bool, Direction, glm::vec2> Collision;

class BreakoutGame : public Game {
public:
	SpriteRenderer* Renderer;
	GameState state;
	bool keys[1024];
	bool processedKeys[1024];
	unsigned int width, height;
	std::vector<GameLevel> Levels;
	Level activeLevel;

	GameObject* Player;
	BallClass* Ball;
	ParticleGenerator *BallTrail;

	BreakoutGame(unsigned int width, unsigned int height);
	~BreakoutGame() override;

	void Init() override;

	void ProcessInput(float deltaTime);
	void Update(float deltaTime) override;
	void UpdateDimensions(unsigned int width, unsigned int height);

	void DoCollisions();

	void Render() override;

	static Direction VectorDirection(glm::vec2 target);
	static bool CheckCollision(GameObject &one, GameObject &two);
	static Collision CheckCollision(BallClass &ball, GameObject &block);

	void ResetLevel();
	void ResetPlayer();
};

#endif //BREAKOUTGAME_H
