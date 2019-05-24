#include "../include/world.h"

#include"../include/entity.h"
#include"../include/system.h"

#include<algorithm>
#include<string>

using namespace squip::ecs;

Entity* World::getEntity(const std::string& id)
{
	return entity_list.at(id_to_index.at(id)).get(); // Return entity using cached index position for given id
}

bool World::addEntity(const std::string& id)
{
	if (entityExists(id)) return false; // Make sure entity with id doesn't already exists

	entity_list.push_back(std::make_unique<Entity>(id)); // Add unique_ptr<Entity> to entity_list
	cacheIdToIndex(id, entity_list.size() - 1);

	return true;
}

void squip::ecs::World::removeEntity(const std::string& id)
{
	entity_list.erase(std::remove_if(entity_list.begin(), entity_list.end(), 
		[id](auto const& entity) { return (entity.get()->id == id); }), entity_list.end()); // Removes entity with id from list
	id_to_index.erase(id); // Remove entry from the id_to_index map
}

bool squip::ecs::World::entityExists(const std::string & id)
{
	return id_to_index.count(id) > 0;
}

void World::onUpdate()
{
	// Update all systems
	for (int i = 0; i < system_list.size(); i++) {
		if (system_list.at(i).get()->enabled) {      
			system_list.at(i).get()->onUpdate();
		}
	}

	// Update all entities
	for (int i = 0; i < entity_list.size(); i++) {
		if (entity_list.at(i)->enabled) {
			entity_list.at(i)->onUpdate();
		}
	}
}

void squip::ecs::World::cacheIdToIndex(const std::string & id, int index)
{
	id_to_index.insert(std::pair<std::string, int>(id, entity_list.size() - 1)); // Cache index of entity with this id
}

void squip::ecs::World::cacheTagToIndex(const std::string & tag, int index)
{
	if()
}
