#pragma once

namespace squip { namespace ecs { 

	class World;

	class BaseSystem {
		friend struct World;
	public:
		/*
		- Called on world update
		*/
		virtual void onUpdate() { }

		/*
		- Called when added to a world
		*/
		virtual void onAdd() { }

		/*
		- Calle when system gets removed and or the application closes
		*/
		virtual void onRemove() { }

		/*
		- Virtual destructor
		*/
		~BaseSystem() { }

	protected:
		/*
		- world this system is attached to 
		*/
		World* world;
		/*
		- Determines if the system gets update by the world
		*/
		bool enabled = true;
	};

} } 