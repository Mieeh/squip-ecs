#include<iostream>

#include"../include/entity.h"
#include"../include/component.h"
#include"../include/system.h"
#include"../include/world.h"

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
		tyler->getComponent<Transform>()->foo++;
	}
};

int main() {

	ecs::World world;
	
	world.addEntity("tyler");
	ecs::Entity* entity = world.getEntity("tyler");
	entity->addComponet<Transform>();

	std::cout << "has syste: " << world.hasSystem<InputSystem>();
	world.getSystem<InputSystem>()->rankmebitch();
	std::cout << "has syste: " << world.hasSystem<InputSystem>();

	// Simulate the world 10 times
	for (int i = 0; i < 10; i++) {
		world.onUpdate();
	}

	std::cin.get(); 
}