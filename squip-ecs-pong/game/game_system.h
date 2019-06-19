#pragma once

#include<squip-ecs/squip-ecs.h>
#include<SFML\Graphics.hpp>

/*
- Game headers
*/
#include"Paddle.h"
#include"Ball.h"

using namespace squip;

#define WIDTH 1200
#define HEIGHT 900

class GameSystem : public ecs::BaseSystem {
public:

	sf::RenderWindow *window; // Game window, supplied from outside
	
	int numberOfBalls = 0;

	sf::Text score_text;
	sf::Font font;
	sf::Vector2i score;

	void onAdd() {
		// Setup text elements
		score_text.setPosition(sf::Vector2f(0, 0));
		font.loadFromFile("arial.ttf");
		score_text.setFont(font);
		score_text.setCharacterSize(32);
		score_text.setFillColor(sf::Color::Red);
		score_text.setPosition({ 0,0 });
	}

	void startGame() {
		for (int i = 1; i <= numberOfBalls; i++) {
			world->removeEntityImediate("ball" + std::to_string(i));
		}

		// Remove game entities if they exist
		world->removeEntityImediate("left_paddle");
		world->removeEntityImediate("right_paddle");

		// Populate world with all game entities
		/* Add paddles */
		world->addEntity("left_paddle");
		world->getEntity("left_paddle")->addComponet<Paddle>(window, 10, sf::Keyboard::Key::W, sf::Keyboard::Key::S);
		
		world->addEntity("right_paddle");
		world->getEntity("right_paddle")->addComponet<Paddle>(window, WIDTH - Paddle::paddle_size.x - 10, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down);

		/* Add ball */
		numberOfBalls = 0;

		for (int i = 1; i < 1000; i++) {
			addBall();
		}

		// Start score
		score = sf::Vector2i(0, 0);
	}

	void addBall() {
		numberOfBalls++;
		world->addEntity("ball" + std::to_string(numberOfBalls));
		world->getEntity("ball" + std::to_string(numberOfBalls))->addComponet<Ball>(window, world->getEntity("left_paddle"), world->getEntity("right_paddle"));
	}

	void onUpdate() {
		std::string _temp = std::to_string(score.x) + " : " + std::to_string(score.y);
		score_text.setString(_temp);

		window->draw(score_text);
	}

};