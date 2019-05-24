#include<iostream>

#include"../include/squip-ecs.h"

using namespace squip;

struct Transform : ecs::Component {
	int foo = 0;
	
	void onUpdate() override {
		foo++;
	}

	Transform() {

	}

	Transform(int x, int y, int z) {
		foo = x + y + z;
	}

	~Transform() {
		std::cout << "Transform component dead" << std::endl;
	}
};

class InputSystem : public ecs::BaseSystem {
public:
	ecs::Entity* tyler;

	void rankmebitch() {
		std::cout << "RANK ME BITCH\n";
	}

	void onAdd() override {
		tyler = world->getEntity("tyler");
	}

	void onUpdate() override {
		std::cout << "Input System Updated" << std::endl;
	}
};

int main() {

	std::cout << ecs::getVersionString() << std::endl;

	ecs::World world;
	
	world.addEntity("tyler");
	ecs::Entity* entity = world.getEntity("tyler");
	entity->addComponet<Transform>(3, 3, 3);

	// Simulate the world 10 times
	for (int i = 0; i < 10; i++) {
		world.onUpdate();
	}

	std::cin.get(); 
}