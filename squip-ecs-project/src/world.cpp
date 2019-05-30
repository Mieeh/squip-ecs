#include "../include/world.h"

#include"../include/entity.h"
#include"../include/system.h"

#include<algorithm>
#include<string>

using namespace squip::ecs;

squip::ecs::World::~World()
{
	// Everything is smart pointers so this is all we should have to do!
	clearWorld(); // This clears entities and systems
}

Entity* World::getEntity(const std::string& id)
{
	return entity_list.at(id_to_index.at(id)).get(); // Return entity using cached index position for given id
}

Entity* World::addEntity(const std::string& id)
{
	if (entityExists(id)) return nullptr; // Make sure entity with id doesn't already exists

	entity_list.push_back(std::make_unique<Entity>(id, this)); // Add unique_ptr<Entity> to entity_list
	cacheIdToIndex(id, entity_list.size() - 1);

	return entity_list.back().get();
}

void squip::ecs::World::removeEntity(const std::string& id)
{
	entity_list.erase(std::remove_if(entity_list.begin(), entity_list.end(), 
		[id](auto const& entity) { return (entity.get()->id == id); }), entity_list.end()); // Removes entity with id from list
	id_to_index.erase(id); // Remove entry from the id_to_index map
}

void squip::ecs::World::clearWorld()
{
	// Entity clear
	entity_list.clear();
	id_to_index.clear();

	// System clear
	for (auto i = 0; i < system_list.size(); i++) {
		system_list.at(i).get()->onRemove();
	}
	system_list.clear();
	type_to_index.clear();
}

void squip::ecs::World::moveEntityToFront(const std::string & id)
{
	// Get the elements
	auto& entity_to_be_front = entity_list.at(id_to_index.at(id));
	auto& current_front = entity_list.front();

	// Swap places

}

void squip::ecs::World::moveEntityToBack(const std::string & id)
{

}

bool squip::ecs::World::entityExists(const std::string & id)
{
	return id_to_index.find(id) != id_to_index.end();
}

void World::onUpdate()
{
	// Update all systems
	for (int i = system_list.size()-1; i >= 0; i--) {
		if (system_list.at(i).get()->enabled) {      
			system_list.at(i).get()->onUpdate();
		}
	}

	// Update all entities
	for (int i = entity_list.size()-1; i >= 0; i--) {
		if (entity_list.at(i)->enabled) {
			entity_list.at(i)->onUpdate();
		}
	}
}

inline void squip::ecs::World::cacheIdToIndex(const std::string & id, int index)
{
	id_to_index.insert(std::pair<std::string, int>(id, entity_list.size() - 1)); // Cache index of entity with this id
}

void squip::ecs::World::cacheTagToIndex(const std::string & tag, int index)
{
	
}
