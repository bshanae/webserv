#pragma once

#include "config/CGIConfig.h"
#include "config/VirtualServerConfig.h"
#include "server/core/messages/Request.h"
#include "server/app/project/Project.h"
#include "CGIOutput.h"

class CGIExecutor
{
public:

	CGIExecutor(
		const CGIConfig& cgiConfig,
		const VirtualServerConfig& vServerConfig,
		Project& project
	);

	bool isCGI(const std::string& remotePath, const std::string& localPath) const;
	CGIOutput executeCGI(const Request& request) const;

private:

	std::vector<std::string> _constEnv;
	std::set<std::string> _roots;
	std::set<std::string> _extensions;
	Project& _project;

	std::vector<std::string> collectConstEnv(const VirtualServerConfig& vServerConfig) const;
	std::vector<std::string> collectEnv(const Request& request) const;
	CGIOutput parseCGIOutput(const std::string& rawOutput) const;
};

std::ostream& operator<<(std::ostream& stream, const CGIExecutor& executor);