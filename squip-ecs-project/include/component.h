#pragma once

#include<iostream>

/*
- Components supposed to be used by entites have to inherit from this
*/

namespace squip { namespace ecs { 

	class Entity;

	class Component {
	public:
		/*
		- Called on entity update
		*/
		virtual void onUpdate() { }

		/*
		- Called when added to a entity
		*/
		virtual void onAdd() { }

		/*
		- Calle when component gets removed from entity
		*/
		virtual void onRemove() { }

		/*
		- Virtual destructor
		*/
		~Component() { }

		/* 
		- Entity that this component is attached to
		*/
		Entity* entity;
	};

} } 