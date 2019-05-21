#pragma once

#include<vector>
#include<map>
#include<memory>

namespace squip { namespace ecs { 

class Entity;

struct World {

	/*
	- Return raw pointer of entity that with id that resides in this world
	*/
	Entity* getEntity(const std::string& id);

	/*
	- Adds new entity with id to this world
	- Returns false if entity couldn't be created
	- No two entities with the same exact id can exists at the same time in the world!
	*/
	bool addEntity(const std::string& id);

	/*
	- Removes entity with id from this world
	*/
	void removeEntity(const std::string& id);

	/*
	- Checks if entity with id resides in this world
	*/
	bool entityExists(const std::string& id); 

	/*
	- Calls update on all entities in this world
	*/
	void onUpdate();
	
	/*
	- Members
	*/
	std::vector<std::unique_ptr<Entity>> entity_list;
	std::map<std::string, int> id_to_index;
};

}} 