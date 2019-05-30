#include<iostream>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include<squip-ecs.h>

using namespace squip;

/*
Game related headers & macros
*/
#include"Paddle.h" // Component
#include"Ball.h" // Component

#define WIDTH 700
#define HEIGHT 700

int main() {
	// Setup sfml window
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "squip::ecs Game!");
	window->setFramerateLimit(60);

	srand(time(NULL));

	// Create world & entities
	ecs::World world;
	
	/* Add paddles */
	world.addEntity("left_paddle");
	world.getEntity("left_paddle")->addComponet<Paddle>(window, 10, sf::Keyboard::Key::W, sf::Keyboard::Key::S);
	
	world.addEntity("right_paddle");
	world.getEntity("right_paddle")->addComponet<Paddle>(window, WIDTH-Paddle::paddle_size.x-10, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down);

	/* Add ball */
	world.addEntity("ball");
	world.getEntity("ball")->addComponet<Ball>(window, world.getEntity("left_paddle"), world.getEntity("right_paddle"));

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) { 
				window->close();
			}
		}

		window->clear(sf::Color::Black);

		world.onUpdate(); // Update all game entities

		window->display();
	}

	return 0;
}