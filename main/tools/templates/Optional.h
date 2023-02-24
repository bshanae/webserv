#pragma once

#include "tools/exceptions/InvalidStateException.h"

template <typename T>
struct Optional
{
public:

	Optional &operator =(const T &value)
	{
		_hasValue = true;
		_value = value;

		return *this;
	}

	void reset()
	{
		_hasValue = false;
	}

	bool hasValue() const
	{
		return _hasValue;
	}

	T &operator *()
	{
		if (!_hasValue)
			throw InvalidStateException("Value is not set!");

		return _value;
	}

	const T &operator *() const
	{
		if (!_hasValue)
			throw InvalidStateException("Value is not set!");

		return _value;
	}

private:

	bool _hasValue;
	T _value;
};