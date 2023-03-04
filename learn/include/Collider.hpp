#pragma once
#include "SFML\Graphics.hpp"

class CustomCollider: public sf::ConvexShape {
public:
	CustomCollider();
	~CustomCollider();

	//sf::Vector2f getVertices();

	void setColliderPoint(int count, const sf::Vector2f& vertex);


private:
	std::vector<sf::Vector2f> m_vertices;

	friend class Collision;
};