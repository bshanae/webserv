#pragma once

#include <vector>
#include <string>
#include "Pipe.h"
#include "FDStream.h"
#include "tools/templates/Optional.h"

namespace sys
{
	class Process
	{
	public:

		Process(const std::string& cmd, const std::vector<std::string>& args, const std::vector<std::string>& env);
		~Process();

		FDStream& stdIn();
		FDStream& stdOut();
		int stdOut__();
		FDStream& stdErr();

		int wait(); // TODO MK CONST

	private:

		int _pid;
		Pipe _stdInPipe;
		Pipe _stdOutPipe;
		Pipe _stdErrPipe;
		FDStream* _stdInStream;
		FDStream* _stdOutStream;
		FDStream* _stdErrStream;

		Process(Process& that);
		Process& operator=(Process& that);

		void ifParent();
		void ifChild(const std::string& cmd, const std::vector<std::string>& args, const std::vector<std::string>& env);
		void exec(const std::string& cmd, const std::vector<std::string>& args, const std::vector<std::string>& env);

		void checkStreamingUsage() const;
	};
}