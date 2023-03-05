#pragma once

#include "context/Context.h"
#include "../messages/request/Request.h"
#include "CGIOutput.h"

class CGIExecutor
{
public:

	explicit CGIExecutor(Context& context);
	CGIExecutor(const CGIExecutor& that);
	CGIExecutor& operator=(const CGIExecutor& that);

	bool isCGI(const std::string& path) const;
	CGIOutput executeCGI(const Request& request) const;

private:

	Context& _context;

	std::vector<std::string> collectEnv(const Request& request) const;
	CGIOutput parseCGIOutput(const std::string& rawOutput) const;
};

std::ostream& operator<<(std::ostream& stream, const CGIExecutor& executor);