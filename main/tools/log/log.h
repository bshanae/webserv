#pragma once

#include "handler/Handler.h"

namespace log
{
	extern Handler i;
	extern Handler w;
	extern Handler e;

	/// line end
	extern std::string endl;
	/// message end
	extern std::string endm;
	extern std::string entity;
}