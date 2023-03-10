#pragma once

class LogConfig
{
public:

	bool verboseLevelEnabled() const;
	bool infoLevelEnabled() const;
	bool warningLevelEnabled() const;
	bool errorLevelEnabled() const;
};
