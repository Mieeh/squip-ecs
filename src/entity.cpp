#include"../include/entity.h"

#include"../include/component.h"

#include<iostream>
#include<string>

using namespace squip::ecs;

squip::ecs::Entity::Entity(const std::string & id)
{
	this->id = id;
}

squip::ecs::Entity::~Entity()
{
	std::cout << id;
	std::cout << " detroyed" << std::endl;
	component_list.clear();
}

void squip::ecs::Entity::onUpdate()
{
	// Update all components
	for (int i = 0; i < component_list.size(); i++) {
		component_list.at(i).get()->onUpdate();
	}
}
