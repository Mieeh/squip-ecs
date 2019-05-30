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
#include"game_system.h" // System

int main() {
	// Setup sfml window
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "squip::ecs Game!");
	window->setFramerateLimit(60);

	srand(time(NULL));

	// Create world & entities
	ecs::World world;

	world.addSystem<GameSystem>();
	world.getSystem<GameSystem>()->window = window;
	world.getSystem<GameSystem>()->startGame();

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) { 
				window->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::X) {
					world.getSystem<GameSystem>()->startGame(); // Restarts the game
				}
				if (event.key.code == sf::Keyboard::C) {
					world.getSystem<GameSystem>()->addBall();
				}
				if (event.key.code == sf::Keyboard::Z) {
					std::cout << "STOP!" << std::endl;
				}
			}
		}

		window->clear(sf::Color::Black);

		world.onUpdate(); // Update all game entities & systems

		window->display();
	}

	return 0;
}