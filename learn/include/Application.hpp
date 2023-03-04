#pragma once

#include "SFML\Graphics.hpp"
#include "Collider.hpp"
#include "Collision.hpp"

class Application {
public:
	Application();
	~Application();

	void Run();

	static Application* Instance;
	static float		DT;

	sf::RenderWindow Window;
	sf::Event		 Event;

private:
	sf::Clock m_dtClock;

	std::vector<CustomCollider*> m_Colliders;

	int currentCollider=0;

	void Update();
	void Render();

	void HandleEvents();

	void InitWindow();

	void CheckCollisions();
	void CreateColliders();

};