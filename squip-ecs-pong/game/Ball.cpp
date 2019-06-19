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
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() & 255;
	shape.setFillColor(sf::Color(r,g,b));

	resetBall();
}

// This is where we know what entity is
void Ball::onAdd() {
	game_system = entity->world->getSystem<GameSystem>();
}

void Ball::onUpdate()
{
	shape.move(velocity);
	// Move ball
#define MAX_VEL 7
	
	if (velocity.x >= MAX_VEL) {
		velocity.x = MAX_VEL;
	}
	if (velocity.y >= MAX_VEL) {
		velocity.y = MAX_VEL;
	}

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
		//sresetBall();
		//sgame_system->score.y++;
		scored();
		velocity.x *= -1;
		velocity *= velocity_factor;
	}
	else if (shape.getPosition().x > renderWindow->getSize().x) {
		//resetBall();
		//game_system->score.x++;
		scored();
		velocity.x *= -1;
		velocity *= velocity_factor;
	}

	// Render
	renderWindow->draw(shape);
}

void Ball::scored()
{
	if (game_system->numberOfBalls > 1) {
		entity->world->removeEntityNextUpdate(entity->id);
		game_system->numberOfBalls--;
		//std::cout << "Remove ball" << std::endl;
	}
}

void Ball::resetBall()
{
	float x = rand() % renderWindow->getSize().x;
	float y = rand() % renderWindow->getSize().y;
	// Reset position and velocity
	shape.setPosition({ x, y });
	//shape.setPosition(sf::Vector2f(renderWindow->getSize().x / 2, renderWindow->getSize().y / 2));

	// Velocity for the ball
	float angle = rand() % 360;
	velocity.x = start_velocity * cos(angle);
	velocity.y = start_velocity * sin(angle);
}
