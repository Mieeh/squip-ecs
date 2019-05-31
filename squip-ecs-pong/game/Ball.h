#pragma once

#include<random>

#include<SFML\Graphics.hpp>

#include<squip-ecs/squip-ecs.h>

using namespace squip;

// Forward declerations
class Paddle;
class GameSystem;

class Ball : public ecs::Component {
public:
	static float radius;
	static float start_velocity;
	static float velocity_factor;

	sf::RenderWindow* renderWindow;
	sf::CircleShape shape;

	sf::Vector2f velocity;

	ecs::Entity* right_paddle;
	ecs::Entity* left_paddle;

	// Score tracking
	GameSystem *game_system;

	Ball(sf::RenderWindow* renderWindow, ecs::Entity* pleft, ecs::Entity* pright);

	void onAdd() override;

	void onUpdate() override;

	void scored();

	void bounceOnPaddle() {
		velocity.x *= -1;
		velocity *= velocity_factor;
	}

	void resetBall();

};