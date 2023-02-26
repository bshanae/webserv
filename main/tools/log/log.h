#pragma once

#include "tools/log/stream/LogStream.h"

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

	void initialize();
}