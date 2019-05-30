#include"world.h"
#pragma once;

#include<type_traits>

template<typename _T>
inline bool squip::ecs::World::addSystem()
{
	bool isDerivedFromBaseSystem = std::is_base_of<BaseSystem, _T>();
	if (isDerivedFromBaseSystem && !hasSystem<_T>()) { // Make sure _T inherits from BaseSystem, and that system already doesn't exist in world
		type_to_index.insert(std::pair<std::string, int>(typeid(_T).name(), system_list.size())); // Cache system typename index
		system_list.push_back(std::make_unique<_T>());
		system_list.back().get()->world = this; // Make sure the system knows this is the world
		system_list.back().get()->onAdd(); // onAdd should logically be called now
		return true;
	}

	return false;
}

template<typename _T>
inline _T * squip::ecs::World::getSystem()
{
	// Try to retrieve system! No assumptions that it exists has been made
	try {
		// Return system using cached typename
		return static_cast<_T*>(system_list.at(type_to_index.at(typeid(_T).name())).get());
	}
	catch (std::exception e) {
		// Cout error!
		std::cout << "Eror with World, system didn't exist: " << e.what() << std::endl;
		return nullptr;
	}

}

template<typename _T>
inline bool squip::ecs::World::hasSystem()
{
	return type_to_index.count(typeid(_T).name()) > 0;
}
