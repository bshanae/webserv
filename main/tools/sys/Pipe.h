#pragma once

#include "FDescriptor.h"

namespace sys
{
	class Pipe
	{
	public:

		Pipe();
		Pipe(const Pipe& that);
		Pipe& operator=(const Pipe& that);

		FDescriptor& r();
		FDescriptor r() const;

		FDescriptor& w();
		FDescriptor w() const;

	private:

		union
		{
			FDescriptor _fds[2];
			struct
			{
				FDescriptor _fdR;
				FDescriptor _fdW;
			};
		};
	};
}