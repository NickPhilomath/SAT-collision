#include "stpch.h"
#include "Application.hpp"

Application* Application::Instance = nullptr;
float		 Application::DT = 0.0f;

const float& dt = Application::DT;

Application::Application() {
	InitWindow();
	CreateColliders();
}

Application::~Application() {
	for (auto c : m_Colliders)
		delete c;
}

void Application::Run() {
	m_dtClock.restart();

	while (Window.isOpen()) {
		HandleEvents();
		Update();
		sf::Image image;
		image.create(20, 20, sf::Color::Yellow);
		image.setPixel(19, 19, sf::Color::Red);

		sf::Texture texture;
		texture.loadFromImage(image);
		sf::Sprite sprite;
		sprite.setTexture(texture, true);
		

		
		Window.clear(sf::Color(13, 17, 31));
		Render();
		Window.draw(sprite);
		Window.display();

		DT = m_dtClock.restart().asSeconds();
		std::cout << DT << std::endl;
	}
}

void Application::Update() {
	// update first Collider to mouse position
	sf::Vector2i mousePos = sf::Mouse::getPosition(Window);
	m_Colliders[currentCollider]->setPosition(mousePos.x, mousePos.y);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_Colliders[currentCollider]->setRotation(m_Colliders[currentCollider]->getRotation() + 100.0f * dt);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		(currentCollider == m_Colliders.size() - 1) ? currentCollider = 0 : currentCollider += 1;

	CheckCollisions();
}

void Application::Render() {
	//std::cout << "wtf" << m_Colliders.size() << std::endl;

	for (auto c : m_Colliders)
		Window.draw(*c);
}

void Application::HandleEvents() {
	while (Window.pollEvent(Event)) {
		switch (Event.type) {
		case sf::Event::Closed:
			Window.close();
		}
	}
}

void Application::InitWindow() {
	sf::VideoMode mode;
	mode.width = WINDOW_WIDTH;
	mode.height = WINDOW_HEIGHT;

	Window.create(mode, "learning fucking sfml !!");
	Window.setFramerateLimit(144);
}

void Application::CheckCollisions() {
	//for (auto c : m_Colliders) {
	//
	//}
	sf::Vector2f MTV;
	if (Collision::Instance.SATCollision(*m_Colliders[0], *m_Colliders[1], MTV)) {
		m_Colliders[1]->setFillColor(sf::Color::Red);
	}
	else {
		m_Colliders[1]->setFillColor(sf::Color::Transparent);
	}
}

void Application::CreateColliders() {
	{
		CustomCollider* c = new CustomCollider();
		c->setPointCount(5);
		c->setColliderPoint(0, sf::Vector2f(-30.f, -20.f));
		c->setColliderPoint(1, sf::Vector2f(150.f, -10.f));
		c->setColliderPoint(2, sf::Vector2f(120.f, 90.f));
		c->setColliderPoint(3, sf::Vector2f(30.f, 100.f));
		c->setColliderPoint(4, sf::Vector2f(0.f, 50.f));
		c->setPosition(sf::Vector2f(150.f, 250.f));
		//c->setRotation(15.f);
		c->setFillColor(sf::Color::Transparent);
		c->setOutlineThickness(1.f);
		m_Colliders.push_back(c);
	}

	{
		CustomCollider* c = new CustomCollider();
		c->setPointCount(4);
		c->setColliderPoint(0, sf::Vector2f(-50.f, -50.f));
		c->setColliderPoint(1, sf::Vector2f(50.f, -50.f));
		c->setColliderPoint(2, sf::Vector2f(50.f, 50.f));
		c->setColliderPoint(3, sf::Vector2f(-50.f, 50.f));
		c->setPosition(sf::Vector2f(200.f, 150.f));
		//c->setRotation(45.f);
		c->setFillColor(sf::Color::Transparent);
		c->setOutlineThickness(1.f);
		m_Colliders.push_back(c);
	}
}
