#pragma once

#include<random>

#include<SFML\Graphics.hpp>

#include<squip-ecs.h>

#include"Paddle.h"

using namespace squip;

struct Ball : ecs::Component {

	static float radius;
	static float start_velocity;
	static float velocity_factor;

	sf::RenderWindow* renderWindow;
	sf::CircleShape shape;

	sf::Vector2f velocity;

	ecs::Entity* right_paddle;
	ecs::Entity* left_paddle;

	sf::Vector2i score;
	sf::Text score_text;
	sf::Font font;

	Ball(sf::RenderWindow* renderWindow, ecs::Entity* pleft, ecs::Entity* pright) {
		this->renderWindow = renderWindow;
	
		// Paddle entities
		left_paddle = pleft;
		right_paddle = pright;

		// Setup shape 
		shape.setRadius(radius);
		shape.setFillColor(sf::Color::Cyan);

		resetBall();

		score = sf::Vector2i(0, 0);

		score_text.setPosition(sf::Vector2f(0, 0));
		font.loadFromFile("arial.ttf");
		score_text.setFont(font);
		score_text.setCharacterSize(32);
		score_text.setFillColor(sf::Color::Red);
		score_text.setPosition(sf::Vector2f((renderWindow->getSize().x / 2)-score_text.getCharacterSize()/2, 0));
	}

	void onUpdate() {
		// Move ball
		shape.move(velocity);

		// Collision with paddles
		sf::FloatRect rect = left_paddle->getComponent<Paddle>()->shape.getGlobalBounds();
		if (rect.intersects(shape.getGlobalBounds())) {
			bounceOnPaddle();
		}
		rect = right_paddle->getComponent<Paddle>()->shape.getGlobalBounds();
		if (rect.intersects(shape.getGlobalBounds())) {
			bounceOnPaddle();
		}

		// OOB
		if (shape.getPosition().y < 0) {
			velocity.y *= -1;
			velocity *= velocity_factor;
		}
		else if (shape.getPosition().y > renderWindow->getSize().y - radius * 2) {
			velocity.y *= -1;
			velocity *= velocity_factor;
		}

		// Ball reset
		if (shape.getPosition().x < -radius * 2) {
			resetBall();
			score.y++;
		}
		else if (shape.getPosition().x > renderWindow->getSize().x) {
			resetBall();
			score.x++;
		}

		std::string _temp = std::to_string(score.x) + " : " + std::to_string(score.y);
		score_text.setString(_temp);

		// Render
		renderWindow->draw(shape);
		renderWindow->draw(score_text);
	}

	void bounceOnPaddle() {
		velocity.x *= -1;
		velocity *= velocity_factor;
	}

	void resetBall() {
		// Reset position and velocity
		shape.setPosition(sf::Vector2f(renderWindow->getSize().x/2, renderWindow->getSize().y/2));

		// Velocity for the ball
		float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 360));
		velocity.x = start_velocity * cos(angle);
		velocity.y = start_velocity * sin(angle);
	}

};

float Ball::radius = 10.0f; // In pixels
float Ball::start_velocity = 3.0; 
float Ball::velocity_factor = 1.1f; // Increase velocity 10% per hit