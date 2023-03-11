#pragma once

#include <vector>
#include <string>

namespace webserv
{
	struct CGIOutput;
}

struct webserv::CGIOutput
{
	std::vector<std::string> headers;
	std::string body;
};