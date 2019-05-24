#pragma once

namespace squip { namespace ecs { 

	struct World;

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