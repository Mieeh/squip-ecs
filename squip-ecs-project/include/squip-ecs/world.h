#pragma once

#include<vector>
#include<queue>
#include<map>
#include<memory>

namespace squip { namespace ecs { 

class Entity;
class BaseSystem;

class World {
public:
	/*
	- Clears all world related objects 
	*/
	~World();

	/*
	- Return raw pointer of entity that with id that resides in this world
	*/
	Entity* getEntity(const std::string& id);

	/*
	- Adds new entity with id to this world
	- Returns false if entity couldn't be created
	- No two entities with the same exact id can exists at the same time in the world!
	*/
	Entity* addEntity(const std::string& id);

	/*
	- Removes entity with id from this world imediatly
	*/
	void removeEntityImediate(const std::string& id);
	/*
	- Tag entity to be removed before next update step
	*/
	void removeEntityNextUpdate(const std::string& id);
	/*
	- Makes the world empty and fresh
	- removes all entities and systems
	*/
	void clearWorld();

	/*
	- Moves entity to the front of the list, i.e making it update "first"
	*/
	void moveEntityToFront(const std::string& id);

	/*
	- Moves entity to the back of the list, i.e making it update "last"
	*/
	void moveEntityToBack(const std::string& id);

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
	- Removes system of type _T if it exists in this world
	*/
	//template<typename _T>
	//void removeSystem();

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

private:
	/*
	- Helper method for caching(s)
	*/
	inline void cacheIdToIndex(const std::string& id, int index);
	void cacheTagToIndex(const std::string& tag, int index);

private:
	/*
	- Members
	*/
	// Entity related
	std::vector<std::unique_ptr<Entity>> entity_list;
	std::map<std::string, int> id_to_index; // Caching unique name
	std::map<std::string, std::vector<int>> tag_to_indices; // Caching tags for grouping
	// System related
	std::vector<std::unique_ptr<BaseSystem>> system_list;
	std::map<std::string, int> type_to_index;
	std::deque<std::string> remove_list;
};

#include"world.inl"

}} 