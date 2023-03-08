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
		//std::cout << DT << std::endl;
	}
}

void Application::Update() {
	// update first Collider to mouse position
	sf::Vector2i mousePos = sf::Mouse::getPosition(Window);
	m_Colliders[currentCollider]->SetPosition(sf::Vector2f(mousePos.x, mousePos.y));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_Colliders[currentCollider]->SetRotation(m_Colliders[currentCollider]->GetRotation() + 100.0f * dt);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		(currentCollider == m_Colliders.size() - 1) ? currentCollider = 0 : currentCollider += 1;

	CheckCollisions();
}

void Application::Render() {

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
	sf::Vector2f MPV;
	if (Collision::Instance.SATCollision(*m_Colliders[0], *m_Colliders[1], MPV))
		Print("collided");
	else
		Print("not collided");
	Print("\n");
	/*if () {
		m_Colliders[1]->setFillColor(sf::Color::Red);
	}
	else {
		m_Colliders[1]->setFillColor(sf::Color::Transparent);
	}*/
}

void Application::CreateColliders() {
	{
		CircleCollider* c = new CircleCollider();
		c->Create(100.0f);
		c->SetPosition(sf::Vector2f(650.0f, 250.0f));
		m_Colliders.push_back(c);
	}
	{
		BoxCollider* c = new BoxCollider();
		c->Create(sf::Vector2f(100.0f, 200.0f));
		c->SetOrigin(sf::Vector2f(50.0f, 100.0f));
		c->SetPosition(sf::Vector2f(50.0f, 50.0f));
		//c->SetRotation(25.0f);
		m_Colliders.push_back(c);
	}
	{
		BoxCollider* c = new BoxCollider();
		c->Create(sf::Vector2f(200.0f, 100.0f));
		c->SetPosition(sf::Vector2f(200.0f, 100.0f));
		//c->SetRotation(25.0f);
		m_Colliders.push_back(c);
	}
	{
		CustomCollider* c = new CustomCollider(6);
		c->GetVertices(0) = sf::Vector2f(100.0f, 0.0f);
		c->GetVertices(1) = sf::Vector2f(200.0f, 0.0f);
		c->GetVertices(2) = sf::Vector2f(260.0f, 60.0f);
		c->GetVertices(3) = sf::Vector2f(160.0f, 120.0f);
		c->GetVertices(4) = sf::Vector2f(80.0f, 120.0f);
		c->GetVertices(5) = sf::Vector2f(0.0f, 50.0f);
		c->SetPosition(sf::Vector2f(400.0f, 400.0f));
		m_Colliders.push_back(c);
	}
	
}
