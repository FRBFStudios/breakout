#include "BallClass.h"

BallClass::BallClass(): GameObject(), radius(12.5f), stuck(true) { }

BallClass::BallClass(glm::vec2 position, float radius, glm::vec2 velocity, Texture sprite)
		: GameObject(position, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity),
		radius(radius), stuck(true) { }

glm::vec2 BallClass::Move(float dt, unsigned int window_width) {
	if(!this->stuck) {
		this->position += this->velocity * dt;
		if(this->position.x <= 0.0f) {
			this->velocity.x = -this->velocity.x;
			this->position.x = 0.0f;
		}
		else if(this->position.x + this->size.x >= window_width) {
			this->velocity.x = -this->velocity.x;
			this->position.x = window_width - this->size.x;
		}
		if(this->position.y <= 0.0f) {
			this->velocity.y = -this->velocity.y;
			this->position.y = 0.0f;
		}
	}
	return this->position;
}

void BallClass::Reset(glm::vec2 position, glm::vec2 velocity) {
	this->position = position;
	this->velocity = velocity;
}

