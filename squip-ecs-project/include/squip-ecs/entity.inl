#include "entity.h"
#pragma once

template<typename _T, typename... _Args>
inline bool squip::ecs::Entity::addComponet(_Args&&... arg)
{
	bool isDerivedFromComponent = std::is_base_of<Component, _T>();
	if (isDerivedFromComponent && !hasComponent<_T>()) { // Make sure _T is derived correctly + _T doesn't already exists!
		component_list.push_back(std::unique_ptr<_T>(new _T(std::forward<_Args>(arg)...)));
		// Cache typename
		typename_to_index.insert(std::pair<std::string, int>(typeid(_T).name(), component_list.size() - 1));
		component_list.back()->entity = this;
		component_list.back()->onAdd(); // Logcally call this now!
		return true;
	}

	return false;
}

template<typename _T>
inline _T *squip::ecs::Entity::getComponent()
{
	if (hasComponent<_T>()) {
		return static_cast<_T*>(component_list.at(typename_to_index.at(typeid(_T).name())).get());
	}
	return nullptr;
}

template<typename _T>
inline bool squip::ecs::Entity::hasComponent()
{
	return typename_to_index.count(typeid(_T).name()) > 0;
}
