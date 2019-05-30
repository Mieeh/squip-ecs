#include<iostream>

#include"../include/squip-ecs.h"

#include<chrono>

using namespace squip;

class InputSystem : public ecs::BaseSystem {
public:
	void rankmebitch() {
		std::cout << "RANK ME BITCH\n";
	}

	void onAdd() override {
		std::cout << "Added input system to world!" << std::endl;
	}

	void onRemove() override {
		std::cout << "Removed input system from world" << std::endl;
	}

	void onUpdate() override {
		std::cout << "Input System Updated" << std::endl;
	}
};

class Transform : public ecs::Component {
private:
	int foo = 0;

public:
	Transform() {
		foo = 0;
	}

	Transform(int x) {
		foo = x;
	}

	void onUpdate() override {
		std::cout << "Transform component was updated" << std::endl;
	}

	void onAdd() override {
		std::cout << "Transform component was added!" << std::endl;
	}

	void onRemove() override {
		std::cout << "Transform component was removed!" << std::endl;
	}
};

void create_alot_entities(ecs::World& world) {
	for (int i = 1; i < 10; i++) {
		world.addEntity(std::to_string(i));
		world.getEntity(std::to_string(i))->addComponet<Transform>();
	}
}

int main() {

	std::cout << ecs::getVersionString() << std::endl;

	ecs::World world;
	auto boy = world.addEntity("auto boys");
	world.getEntity("auto boys")->addComponet<Transform>(120);
	
	/*
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	create_alot_entities(world);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << "Time it took to do create_alot_entities (microseconds 1 000 000 ms = 1 second) : ";
	std::cout << duration << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
	world.onUpdate();
	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << "Time it took to update world (microseconds 1 000 000 ms = 1 second) : ";
	std::cout << duration << std::endl;
	*/

	std::cin.get();
	return 0;
}