#pragma once

#include<vector>
#include<memory>
#include<type_traits>
#include<map>

#include"component.h"

namespace squip { namespace ecs {

class World;

class Entity {
friend struct std::default_delete<Entity>;
public:
	/*
	- Creates new empty entity with id that knows what world it's attached to
	*/
	Entity(const std::string& id, World* world);	

	/*
	- Called on world.onUpdate();
	*/
	void onUpdate();

	/*
	- Adds component of type _T
	- _T needs to be derived from squip::ecs::Component
	- Returns false if component of type _T failed to be inserted (_T need to be derived from Component!)
	- Return false if entity already has component of type _T
	*/
	template<typename _T, typename... _Args>
	bool addComponet(_Args&&... arg);

	/*
	- 
	*/
	template<typename _T>
	_T* getComponent();

	/*
	- Returns false or true dependent on if entity has a component of type _T in it's list
	*/
	template<typename _T> 
	bool hasComponent();

	/*
	- Unique identifier id for entity
	*/
	std::string id;
	/*
	- Is entity enabled/disabled
	*/
	bool enabled;
	/*
	- World this entity resides in
	*/
	World* world;
	/*
	- List of all components attatched to entity
	*/
	std::vector<std::unique_ptr<Component>> component_list;
	/*
	- We cache component typenames to which index they're in!
	*/
	std::map<std::string, int> typename_to_index;

public:
	/*
	- Destructor
	*/
	~Entity();
};

#include"entity.inl"

}}