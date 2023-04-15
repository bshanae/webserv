#pragma once

#include "config/ServerConfig.h"
#include "server/core/messages/Request.h"
#include "server/app/project/Project.h"
#include "CGIOutput.h"

namespace webserv
{
	struct CGIExecutor;
}

std::ostream& operator<<(std::ostream& stream, const webserv::CGIExecutor& executor);

class webserv::CGIExecutor
{
public:

	explicit CGIExecutor(const config::ServerConfig& serverConfig);

	CGIOutput executeCGI(const Request& request, const std::string& fullLocalPath) const;

private:

	std::vector<std::string> _constEnv;

	std::vector<std::string> collectConstEnv(const config::ServerConfig& serverConfig) const;
	std::vector<std::string> collectEnv(const Request& request) const;
	CGIOutput parseCGIOutput(const std::string& rawOutput) const;
};