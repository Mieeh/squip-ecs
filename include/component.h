#pragma once

#include<iostream>

/*
- Components supposed to be used by entites have to inherit from this
*/

namespace squip { namespace ecs { 

	struct Component {
		/*
		- Pure virtual gets called on world.onUpdate();
		*/
		virtual void onUpdate() = 0;
	
		/*
		- Virtual destructor
		*/
		virtual ~Component() { }
	};

} } 