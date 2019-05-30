#pragma once

#include<squip-ecs.h>
#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>

using namespace squip;

struct Paddle : ecs::Component {

	static float speed;
	static sf::Vector2f paddle_size;

	sf::RenderWindow* renderWindow;

	sf::Keyboard::Key up_key, down_key;
	sf::RectangleShape shape;

	/*
	- Creates sf::Shape and sets up correct position
	*/
	Paddle(sf::RenderWindow* renderWindow, float x, sf::Keyboard::Key up, sf::Keyboard::Key down) {
		this->renderWindow = renderWindow; // Used for rendering our shape

		up_key = up; down_key = down;

		// Setup shape size & position
		shape.setSize(paddle_size);
		sf::Vector2f startPos;
		startPos.x = x;
		startPos.y = (renderWindow->getSize().y / 2) - (paddle_size.y / 2);
		shape.setPosition(startPos);
		// Setup shape color
		shape.setFillColor(sf::Color::White);
	}

	void onUpdate() override {
		if (sf::Keyboard::isKeyPressed(up_key)) {
			shape.move(sf::Vector2f(0, -1)*speed);
		}
		else if (sf::Keyboard::isKeyPressed(down_key)) {
			shape.move(sf::Vector2f(0, 1)*speed);
		}

		// Make sure the shape isn't OOB
		if (shape.getPosition().y < 0) {
			shape.setPosition(sf::Vector2f(shape.getPosition().x, 0));
		}
		else if (shape.getPosition().y > renderWindow->getSize().y - paddle_size.y) {
			shape.setPosition(sf::Vector2f(shape.getPosition().x, renderWindow->getSize().y - paddle_size.y));
		}

		// Render
		renderWindow->draw(shape);
	}

};

float Paddle::speed = 5.0f;
sf::Vector2f Paddle::paddle_size = sf::Vector2f(10, 50); // In pixels