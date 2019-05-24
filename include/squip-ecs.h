#pragma once

#define MAJOR_VERSION 0
#define MINOR_VERSION 1

#include<string>

/* 
- Include all headers related to squip-ecs
*/
#include"world.h"
#include"system.h"
#include"entity.h"
#include"component.h"

namespace squip { namespace ecs { 

	static std::string getVersionString() {
		return "squip-ecs Version: " + std::string(std::to_string(MAJOR_VERSION) + "." + std::to_string(MINOR_VERSION));
	}

} }