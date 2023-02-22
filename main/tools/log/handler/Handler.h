#pragma once

#include <iostream>

namespace log
{
	class Handler
	{
	public:

		bool enabled;

		Handler();
		Handler(const std::string& prefix, const std::string& suffix);
		Handler(const Handler& that);
		Handler& operator=(const Handler& that);

		template<typename T>
		friend Handler& operator<<(Handler& handler, const T& data);

		template<typename T>
		friend Handler& operator<<(Handler& handler, const T& data);

	private:
		std::string _prefix;
		std::string _suffix;
	};

	template<typename T>
	log::Handler& operator<<(log::Handler& handler, const T& data)
	{
		if (!handler.enabled)
			return handler;

		if (!handler._prefix.empty())
			std::cout << handler._prefix;

		std::cout << data;

		if (!handler._suffix.empty())
			std::cout << handler._suffix;

		return handler;
	}
}