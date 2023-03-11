#include "log.h"

#include <ostream>

using namespace webserv::config;
using namespace webserv::log;

LogStream webserv::log::v;
LogStream webserv::log::i;
LogStream webserv::log::w;
LogStream webserv::log::e;

void webserv::log::endl(LogStream& stream)
{
	stream << std::endl;
}

void webserv::log::startm(LogStream& stream)
{
	stream.addModifier(LogModifier::italic);
	stream << ' ';
}

void webserv::log::endm(LogStream& stream)
{
	stream.resetModifiers();
	stream << std::endl << std::endl;
}

void webserv::log::initialize(const LogConfig& config)
{
	v = LogStream(LogModifier::grey);
	i = LogStream();
	w = LogStream(LogModifier::yellow);
	e = LogStream(LogModifier::red);

	v.enabled = true;
	i.enabled = true;
	w.enabled = true;
	e.enabled = true;
}