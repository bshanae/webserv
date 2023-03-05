#pragma once

#include <vector>
#include <string>

class CGIOutput
{
public:

	std::vector<std::string> headers;
	std::string body;
};