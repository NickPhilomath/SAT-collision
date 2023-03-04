#pragma once

#include "Collider.hpp"

class Collision {
public:
	Collision();
	~Collision();

	static Collision Instance;

	bool isCollide(const CustomCollider& body, const CustomCollider& other);
	bool SATCollision(const CustomCollider& body, const CustomCollider& other, sf::Vector2f& MTV);
private:
};