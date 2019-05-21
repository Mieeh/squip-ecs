#include<iostream>

#include"../include/entity.h"
#include"../include/component.h"
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

int main() {

	ecs::World world;
	
	world.addEntity("tyler");
	ecs::Entity* entity = world.getEntity("tyler");
	entity->addComponet<Transform>();

	// Simulate the world 10 times
	for (int i = 0; i < 10; i++) {
		entity->getComponent<Transform>()->foo++;
		world.onUpdate();
	}

	std::cin.get(); 
}