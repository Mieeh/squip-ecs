#include"Paddle.h"

float Paddle::speed = 5.0f;
sf::Vector2f Paddle::paddle_size = sf::Vector2f(10, 50); // In pixels

Paddle::Paddle(sf::RenderWindow * renderWindow, float x, sf::Keyboard::Key up, sf::Keyboard::Key down)
{
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

void Paddle::onUpdate()
{
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
	//renderWindow->draw(shape);
}
