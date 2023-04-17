#pragma once

#include <string>
#include "utils/exceptions/InvalidStateException.h"

template<typename T>
struct Optional
{
public:

	Optional() : _hasValue(false)
	{
	}

	Optional(const T& value) : _hasValue(true), _value(value)
	{
	}

	Optional(const Optional<T>& that) :  _hasValue(that._hasValue), _value(that._value)
	{
		this->_hasValue = that._hasValue;
		this->_value = that._value;
	}

	Optional& operator=(const Optional<T>& that)
	{
		this->_hasValue = that._hasValue;
		this->_value = that._value;

		return *this;
	}

	Optional& operator=(const T& value)
	{
		_hasValue = true;
		_value = value;

		return *this;
	}

	operator bool() const
	{
		return hasValue();
	}

	T& operator*()
	{
		return value();
	}

	const T& operator*() const
	{
		return value();
	}

	T* operator->()
	{
		return &value();
	}

	const T* operator->() const
	{
		return &value();
	}

	bool hasValue() const
	{
		return _hasValue;
	}

	void reset()
	{
		_hasValue = false;
	}

	T transfer()
	{
		T temp = value();
		reset();

		return temp;
	}

	T& value()
	{
		if (!_hasValue)
			throw InvalidStateException("Value is not set!");

		return _value;
	}

	const T& value() const
	{
		if (!_hasValue)
			throw InvalidStateException("Value is not set!");

		return _value;
	}

	T valueOr(const T& fallback) const
	{
		if (!_hasValue)
			return fallback;

		return _value;
	}

private:

	bool _hasValue;
	T _value;

};