#include"../include/squip-ecs/entity.h"

#include"../include/squip-ecs/component.h"
#include"../include/squip-ecs/world.h"

#include<iostream>
#include<string>

using namespace squip::ecs;

squip::ecs::Entity::~Entity()
{
	// Call onRemove on all components
	for (auto& c : component_list) {
		c->onRemove();
	}
	component_list.clear();
}

squip::ecs::Entity::Entity(const std::string & id, World * world)
{
	this->id = id;
	this->world = world;
	this->enabled = true;
}

void squip::ecs::Entity::onUpdate()
{
	// Update all components
	for (int i = 0; i < component_list.size(); i++) {
		component_list.at(i).get()->onUpdate();
	}
}
