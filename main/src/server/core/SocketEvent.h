#pragma once

namespace webserv
{
	enum SocketEvent
	{
		SocketEventError,
		SocketEventCanRead,
		SocketEventCanWrite
	};
}