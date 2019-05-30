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
	Paddle(sf::RenderWindow* renderWindow, float x, sf::Keyboard::Key up, sf::Keyboard::Key down);

	void onUpdate() override;

};
