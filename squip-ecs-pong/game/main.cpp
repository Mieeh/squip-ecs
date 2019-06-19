#include<iostream>

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include<squip-ecs/squip-ecs.h>

using namespace squip;

/*
Game related headers & macros
*/
#include"Paddle.h" // Component
#include"Ball.h" // Component
#include"game_system.h" // System

#include<fstream>

struct SaveData {
	int someIntegerData;
	float someFloatData;
	std::string someStringData;
};

void writeToBinaryFile(std::string file, const SaveData& saveData); 
void readFromBinaryFile(std::string file, SaveData& saveData);

int main() {
	// Setup sfml window
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "squip::ecs Game!");
	window->setFramerateLimit(60);

	srand(time(NULL));

	SaveData saveData{ 30, 3.14159f, "starlord dave" };
	writeToBinaryFile("save.bat", saveData);

	SaveData loadData;
	readFromBinaryFile("save.bat", loadData);

	// Create world & entities
	ecs::World world;

	world.addSystem<GameSystem>();
	world.getSystem<GameSystem>()->window = window;
	world.getSystem<GameSystem>()->startGame();

	sf::Clock clock;
	clock.restart();
	int fps = 0;

	while (window->isOpen()) {

		if (clock.getElapsedTime().asSeconds() >= 1.0f) {
			clock.restart();
			std::cout << fps << std::endl;
			fps = 0;
		}

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

		fps++;
	}

	return 0;
}

void writeToBinaryFile(std::string file, const SaveData& saveData) 
{
	std::ofstream ofile(file, std::ios::binary);
	ofile.write((char*)&saveData.someIntegerData, sizeof(saveData.someIntegerData));
	ofile.write((char*)&saveData.someFloatData, sizeof(saveData.someFloatData));
	ofile.write((char*)&saveData.someStringData, sizeof(saveData.someStringData));
}

void readFromBinaryFile(std::string file, SaveData& saveData)
{
	std::ifstream ifile(file, std::ios::binary);
	ifile.read((char*)&saveData.someIntegerData, sizeof(int));
	ifile.read((char*)&saveData.someFloatData, sizeof(float));
	ifile.read((char*)&saveData.someStringData, sizeof(std::string));
}