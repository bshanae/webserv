#include "CGIExecutor.h"

#include <ostream>
#include "utils/exceptions/SystemException.h"
#include "utils/sys/sys.path.h"
#include "utils/sys/Process.h"
#include "utils/io/io.h"
#include "utils/algo/str.h"
#include "common/exceptions/WebException.h"
#include "log/log.h"

using namespace webserv;
using namespace webserv::config;

CGIExecutor::CGIExecutor(const ServerConfig& serverConfig)
{
	_constEnv = collectConstEnv(serverConfig);
}

CGIOutput CGIExecutor::executeCGI(const Request& request, const std::string& cgiPath) const
{
	try
	{
		log::i << *this << log::startm << "Staring CGI script at '" << cgiPath << "'" << log::endm;

		const std::vector<std::string> arg;
		const std::vector<std::string> env = collectEnv(request);

		sys::Process process(cgiPath, arg, env);

		// write stdin
		process.stdIn() << request.body() << std::flush;

		// wait for exit
		const int exitCode = process.wait();

		// read stdin and stderr
		const std::string stdOut = io::to_string(process.stdOut());
		const std::string stdErr = io::to_string(process.stdErr());

		if (exitCode == 0)
		{
			log::i << *this << log::startm << "CGI script exited with code " << exitCode << log::endm;
		}
		else
		{
			log::e << *this << log::startm << "CGI exited with code " << exitCode << log::endl
				   << "STDERR:" << log::endl
				   << stdErr << log::endm;
			throw SystemException("Can't execute CGI");
		}

		return parseCGIOutput(stdOut);
	}
	catch (std::exception& e)
	{
		log::e << *this << log::startm
			   << "Can't execute script at " << cgiPath << log::endl
			   << "Exception:" << e.what() << log::endm;
		throw WebException(StatusCodeInternalServerError, "Can't execute CGI");
	}
}

std::vector<std::string> CGIExecutor::collectConstEnv(const ServerConfig& serverConfig) const
{
	std::vector<std::string> env;

	env.push_back("SERVER_ADDR=" + serverConfig.address().host);
	env.push_back("SERVER_NAME=" + serverConfig.address().host);
	env.push_back("SERVER_PORT=" + std::to_string(serverConfig.address().port));
	env.push_back("REMOTE_ADDR=" + serverConfig.address().host);
	env.push_back("REMOTE_PORT=" + std::to_string(serverConfig.address().port));
	env.push_back("SERVER_SOFTWARE=webserv/1.0");
	env.push_back("GATEWAY_INTERFACE=CGI/1.1");

	return env;
}

std::vector<std::string> CGIExecutor::collectEnv(const Request& request) const
{
	std::vector<std::string> env = _constEnv;

	env.push_back("SERVER_PROTOCOL=" + request.protocol());
	env.push_back("QUERY_STRING=" + request.query());
	env.push_back("REQUEST_METHOD=" + toString(request.method()));
	env.push_back("REQUEST_URI=" + request.uri());

	Optional<std::string> contentLength = request.findHeader(HeaderName::ContentLength);
	if (contentLength)
		env.push_back("CONTENT_LENGTH=" + *contentLength);

	Optional<std::string> contentType = request.findHeader(HeaderName::ContentType);
	if (contentType)
		env.push_back("CONTENT_TYPE=" + *contentType);

	Optional<std::string> cookie = request.findHeader(HeaderName::Cookie);
	if (cookie)
		env.push_back("HTTP_COOKIE=" + *cookie);

	return env;
}

CGIOutput CGIExecutor::parseCGIOutput(const std::string& rawOutput) const
{
	CGIOutput output;

	size_t lower = 0;
	size_t current;
	while ((current = rawOutput.find("\r\n", lower)) != std::string::npos)
	{
		if (lower == current)
		{
			// Empty line is encountered. Stop reading headers.
			break;
		}

		output.headers.push_back(algo::range(rawOutput, lower, current));
		lower = current + 2;
	}

	output.body = algo::range(rawOutput, current + 2, rawOutput.length());

	return output;
}

std::ostream& operator<<(std::ostream& stream, const webserv::CGIExecutor& executor)
{
	stream << "[CGIExecutor]";
	return stream;
}