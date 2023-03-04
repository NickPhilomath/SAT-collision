#include "Collider.hpp"

CustomCollider::CustomCollider() {

}

CustomCollider::~CustomCollider() {

}

void CustomCollider::setColliderPoint(int count, const sf::Vector2f& vertex) {
	this->setPoint(count, vertex);
	m_vertices.push_back(vertex);
}