#pragma once

#include <vector>
#include <string>

struct CGIOutput
{
	std::vector<std::string> headers;
	std::string body;
};