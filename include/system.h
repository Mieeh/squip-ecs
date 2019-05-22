#pragma once

#include<memory>

namespace squip { namespace ecs { 

	struct World;

	class BaseSystem {
	public:
		virtual void onUpdate() = 0;

	protected:
		std::unique_ptr<World> world;
	};

} } 