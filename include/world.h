#pragma once

#include<vector>
#include<map>
#include<memory>

namespace squip { namespace ecs { 

class Entity;
class BaseSystem;

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
	- Add system of type _T to this world
	- Also makes sure the system is correctly setup
	- _T has to inherit from squip::ecs::BaseSystem
	- World can't have multipile system instances of the same type _T 
	*/
	template<typename _T>
	bool addSystem();

	/*
	- Returns system of type _T attached to this world
	*/
	template<typename _T>
	_T* getSystem();

	/*
	- Return true if world has a system of type _T
	*/
	template<typename _T>
	bool hasSystem();

	/*
	- Calls update on all entities in this world
	*/
	void onUpdate();
	
	/*
	- Members
	*/
	// Entity related
	std::vector<std::unique_ptr<Entity>> entity_list;
	std::map<std::string, int> id_to_index;
	// System related
	std::vector<std::unique_ptr<BaseSystem>> system_list;
	std::map<std::string, int> type_to_index;
};

#include"world.inl"

}} 