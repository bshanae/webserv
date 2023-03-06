#include "CGIExecutor.h"

#include <ostream>
#include "tools/log/log.h"
#include "tools/sys/sys.path.h"
#include "tools/sys/Process.h"
#include "tools/io/io.h"

CGIExecutor::CGIExecutor(Context& context) : _context(context)
{
}

bool CGIExecutor::isCGI(const std::string& path) const
{
	const std::string extension = sys::path::extension(path);
	const std::set<std::string> cgiExtensions = _context.getConfig().getCGIExtensions();
	if (cgiExtensions.find(extension) == cgiExtensions.end())
		return false;

	const std::string directory = sys::path::directory(path);
	const std::set<std::string> cgiRoots = _context.getConfig().getCGIRoots();
	if (cgiRoots.find(directory) == cgiRoots.end())
		return false;

	if (!_context.getProject().isFile(path))
		return false;

	return true;
}

CGIOutput CGIExecutor::executeCGI(const Request& request) const
{
	try
	{
		log::i << *this << log::startm << "Staring CGI script at '" << request.getPath() << "'" << log::endm;

		const std::string absolutePath = sys::path::concat(_context.getConfig().getProjectRoot(), request.getPath());
		const std::vector<std::string> arg;
		const std::vector<std::string> env = collectEnv(request);

		sys::Process process(absolutePath, arg, env);

		// write stdin
		process.stdIn() << "Hello world!" << std::endl;

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
			log::e << *this << log::startm << "CGI exited with code " << exitCode << ", stderr:" << log::endl
				   << stdErr << log::endm;
		}

		return parseCGIOutput(stdOut);
	}
	catch (std::exception &e)
	{
		log::e << *this << log::startm
			   << "Can't execute script at " << request.getPath() << log::endl
			   << "Exception:" << e.what() << log::endm;
		throw std::runtime_error("Can't execute CGI");
	}
}

std::vector<std::string> CGIExecutor::collectEnv(const Request& request) const
{
	std::vector<std::string> env;

	env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	env.push_back("QUERY_STRING=" + request.getQuery());
	env.push_back("REMOTE_ADDR=" + _context.getConfig().getServerAddress());
	env.push_back("REQUEST_METHOD=" + to_string(request.getMethod()));
	env.push_back("REQUEST_URI=" + request.getUri());
	env.push_back("SERVER_NAME=" + _context.getConfig().getServerHost());
	env.push_back("SERVER_PROTOCOL=" + request.getProtocol());
	env.push_back("SERVER_PORT=" + std::to_string(_context.getConfig().getServerPort()));
	env.push_back("SERVER_SOFTWARE=" + std::to_string(_context.getConfig().getServerPort()));
	env.push_back("SERVER_SOFTWARE=webserv/1.0");

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

		output.headers.push_back(rawOutput.substr(lower, current));
		lower = current + 2;
	}

	output.body = rawOutput.substr(current + 2, rawOutput.length() - 1);

	return output;
}

std::ostream& operator<<(std::ostream& stream, const CGIExecutor& executor)
{
	stream << "[CGIExecutor]";
	return stream;
}