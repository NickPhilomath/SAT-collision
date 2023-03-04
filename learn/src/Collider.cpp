#include "stpch.h"
#include "Collider.hpp"


const sf::Color ColliderColor(255, 255, 255);

Collider::Collider(uint32_t count) 
	: m_verticesCount(count)
	, m_vertices(nullptr)
	, m_position(0.0f, 0.0f)
	, m_origin(0.0f, 0.0f)
	, m_rotation(0.0f)
{
	if (!count)
		return;

	m_vertices = new sf::Vector2f[count];
}

Collider::~Collider() {
	delete[] m_vertices;
}

void Collider::SetPosition(sf::Vector2f position) {
	sf::Vector2f diff = position - m_position - m_origin;

	for (uint32_t i = 0; i < m_verticesCount; i++) {
		auto v = m_vertices[i];

		v += diff;
	}

	m_position = position - m_origin;
}

void Collider::SetOrigin(sf::Vector2f origin) {
	m_origin = origin;

	SetPosition(m_position);
}

void Collider::SetRotation(float angle) {
	float diff = angle - m_rotation;

	for (uint32_t i = 0; i < m_verticesCount; i++) {
		auto& v = m_vertices[i];

		v = ::Rotate(v, m_position + m_origin, diff);
	}

	m_rotation = angle;
}

void Collider::Move(sf::Vector2f offset) {
	SetPosition(m_position + offset + m_origin);
}

void Collider::Rotate(float angle) {
	SetRotation(m_rotation + angle);
}

sf::Vector2f Collider::GetPosition() const {
	return m_position + m_origin;
}

sf::Vector2f Collider::GetOrigin() const {
	return m_origin;
}

float Collider::GetRotation() const {
	return m_rotation;
}

BoxCollider::BoxCollider()
	: Collider(4)
{

}

BoxCollider::~BoxCollider() {

}

void BoxCollider::Create(sf::Vector2f size) {
	auto& v = m_vertices;

	sf::Vector2f pos = m_position - m_origin;

	v[0] = pos + sf::Vector2f(0.0f, 0.0f);
	v[1] = pos + sf::Vector2f(size.x, 0.0f);
	v[2] = pos + sf::Vector2f(size.x, size.y);
	v[3] = pos + sf::Vector2f(0.0f, size.y);
}

void BoxCollider::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	static sf::Vertex v[6];

	for (int i = 0; i < 4; i++)
		v[i] = sf::Vertex(m_vertices[i], ColliderColor);
	 
	v[4] = sf::Vertex(m_vertices[0], ColliderColor);
	v[5] = sf::Vertex(m_vertices[2], ColliderColor);

	target.draw(v, 6, sf::LineStrip);
}

CustomCollider::CustomCollider() {

}

CustomCollider::~CustomCollider() {

}

void CustomCollider::setColliderPoint(int count, const sf::Vector2f& vertex) {
	this->setPoint(count, vertex);
	m_vertices.push_back(vertex);
}