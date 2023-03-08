#pragma once

#include "Collider.hpp"

class Collision {
public:
	Collision();
	~Collision();

	static Collision Instance;

	bool SATCollision(const Collider& body, const Collider& other, sf::Vector2f& MPV);
	bool SATCollision(const Collider& body, const CircleCollider& other, sf::Vector2f& MPV);
	bool SATCollision(const CircleCollider& body, const Collider& other, sf::Vector2f& MPV);
	bool SATCollision(const CircleCollider& body, const CircleCollider& other, sf::Vector2f& MPV);
private:
};