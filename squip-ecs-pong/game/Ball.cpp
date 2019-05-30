#include"Ball.h"

float Ball::radius = 10.0f; // In pixels
float Ball::start_velocity = 3.0;
float Ball::velocity_factor = 1.1f; // Increase velocity 10% per hit

#include"Paddle.h"
#include"game_system.h"

Ball::Ball(sf::RenderWindow * renderWindow, ecs::Entity * pleft, ecs::Entity * pright)
{
	this->renderWindow = renderWindow;

	// Paddle entities
	left_paddle = pleft;
	right_paddle = pright;

	// Setup shape 
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Cyan);

	resetBall();
}

void Ball::onAdd() {
	game_system = entity->world->getSystem<GameSystem>();
}

void Ball::onUpdate()
{
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
		game_system->score.y++;
		
	}
	else if (shape.getPosition().x > renderWindow->getSize().x) {
		resetBall();
		game_system->score.x++;
		
	}

	// Render
	renderWindow->draw(shape);
}

void Ball::resetBall()
{
	// Reset position and velocity
	shape.setPosition(sf::Vector2f(renderWindow->getSize().x / 2, renderWindow->getSize().y / 2));

	// Velocity for the ball
	float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 360));
	velocity.x = start_velocity * cos(angle);
	velocity.y = start_velocity * sin(angle);
}
