#pragma once

#include "config/LogConfig.h"
#include "log/logStream/LogStream.h"

namespace log
{
	extern LogStream v;
	extern LogStream i;
	extern LogStream w;
	extern LogStream e;

	/// line end
	void endl(LogStream& stream);
	/// message start
	void startm(LogStream& stream);
	/// message end
	void endm(LogStream& stream);

	void initialize(const LogConfig& config);
}