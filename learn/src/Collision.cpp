#include "stpch.h"
#include "Collision.hpp"

bool isPointToLinePositive(sf::Vector2f point, sf::Vector2f line1, sf::Vector2f line2) {
    float h = line2.y - line1.y, s = line2.x - line1.x;
    return ((s * (point.y - line1.y) - h * (point.x - line1.x)) / sqrt(s * s + h * h)) >= 0;
}

sf::Vector2f getGlobalCoors(sf::Vector2f localCoors, sf::Vector2f position, float rotation) {
    float sinA = sin(rotation * DEG2RAD), cosA = cos(rotation * DEG2RAD);
    sf::Vector2f l(localCoors.x * cosA - localCoors.y * sinA, localCoors.y * cosA + localCoors.x * sinA);
    return position + l;
}

Collision Collision::Instance;

bool Collision::isCollide(const CustomCollider& body, const CustomCollider& other) {
    bool last = false;
    auto endline = body.m_vertices.end();
    for (auto it1 = body.m_vertices.begin(); it1 != body.m_vertices.end(); it1++) {
        for (auto it2 = other.m_vertices.begin(); it2 != other.m_vertices.end(); it2++) {
            last = false;
            endline = (it1 == body.m_vertices.end() - 1) ? body.m_vertices.begin() : endline = it1 + 1;
            if (isPointToLinePositive(
                getGlobalCoors(*it2, other.getPosition(), other.getRotation()),
                getGlobalCoors(*it1, body.getPosition(), body.getRotation()),
                getGlobalCoors(*(endline), body.getPosition(), body.getRotation())
            )) {
                last = true;
                break;
            }
        }
        if (!last) return false;
    }
    return true;
}

bool Collision::SATCollision(const CustomCollider& body, const CustomCollider& other, sf::Vector2f& MTV) {
    return isCollide(body, other) && isCollide(other, body);
    //return !(!isCollide(body, other) || !isCollide(other, body));
}


Collision::Collision() {

}

Collision::~Collision() {

}