#include "stpch.h"
#include "Collision.hpp"

Collision Collision::Instance;

bool Collision::SATCollision(const Collider& body, const Collider& other, sf::Vector2f& MPV) {
    uint32_t bodyCount = body.m_verticesCount;
    uint32_t otherCount = other.m_verticesCount;

    // filter if colliders are circles
    if (bodyCount + otherCount == 0) // if both colliders are circles
        return SATCollision((const CircleCollider&)body, (const CircleCollider&)other, MPV);
    else if (bodyCount == 0) // if first collider is circle
        return SATCollision((const CircleCollider&)body, other, MPV);
    else if (otherCount == 0) // if second collider is circle
        return SATCollision(body, (const CircleCollider&)other, MPV);

    // check collider to collider SATCollision
    bool allPointsPositive = true;
    sf::Vector2f* bodyVertices = body.m_vertices;
    sf::Vector2f* otherVertices = other.m_vertices;
    sf::Vector2f endPoint;

    // check first collider to second 
    for (uint32_t i = 0; i < bodyCount; i++) {
        endPoint = (i == bodyCount - 1) ? bodyVertices[0] : bodyVertices[i + 1];
        for (uint32_t j = 0; j < otherCount; j++) {
            allPointsPositive = true;
            //Print(i, "&", j, ": point ", posPoint.x, "&", posPoint.y, " l1 ", posL1.x, "&", posL1.y, " l2 ", posL2.x, "&", posL2.y, " ", PointToLine(otherVertices[j], bodyVertices[i], endPoint), " \n");
            if (PointToLine(otherVertices[j], bodyVertices[i], endPoint) <= 0) {
                allPointsPositive = false;
                break;
            }
        }
        if (allPointsPositive) return false;
    }
    // check second collider to first
    for (uint32_t i = 0; i < otherCount; i++) {
        endPoint = (i == otherCount - 1) ? otherVertices[0] : otherVertices[i + 1];
        for (uint32_t j = 0; j < bodyCount; j++) {
            allPointsPositive = true;
            if (PointToLine(bodyVertices[j], otherVertices[i], endPoint) <= 0) {
                allPointsPositive = false;
                break;
            }
        }
        if (allPointsPositive) return false;
    }

    return true;
}

bool Collision::SATCollision(const Collider& body, const CircleCollider& other, sf::Vector2f& MPV) {
    uint32_t colliderCount = body.m_verticesCount;
    sf::Vector2f* colliderVers = body.m_vertices;
    sf::Vector2f circlePos = other.GetPosition();
    sf::Vector2f endPoint;
    float circleRad = other.GetRadius();

    for (uint32_t i = 0; i < colliderCount; i++) {
        if (Distance(colliderVers[i], circlePos) - circleRad <= 0) {
            return true;
        }
    }
    return false;
}

bool Collision::SATCollision(const CircleCollider& body, const Collider& other, sf::Vector2f& MPV) {

    return SATCollision(other, body, MPV);
}

bool Collision::SATCollision(const CircleCollider& body, const CircleCollider& other, sf::Vector2f& MPV) {

    return false;
}

Collision::Collision() {

}

Collision::~Collision() {

}