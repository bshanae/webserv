#pragma once

#include "config/CGIConfig.h"
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

	CGIExecutor(
		const config::CGIConfig& cgiConfig,
		const config::ServerConfig& serverConfig,
		Project& project
	);

	bool isCGI(const std::string& remotePath, const std::string& localPath) const;
	CGIOutput executeCGI(const Request& request) const;

private:

	std::vector<std::string> _constEnv;
	std::set<std::string> _roots;
	std::set<std::string> _extensions;
	Project& _project;

	std::vector<std::string> collectConstEnv(const config::ServerConfig& serverConfig) const;
	std::vector<std::string> collectEnv(const Request& request) const;
	CGIOutput parseCGIOutput(const std::string& rawOutput) const;
};