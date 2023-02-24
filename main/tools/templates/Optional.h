#pragma once

#include "tools/exceptions/InvalidStateException.h"

template<typename T>
struct Optional
{
public:

	Optional()
	{
	}

	Optional(const T& value)
	{
		this->_hasValue = true;
		this->_value = value;
	}

	Optional(const Optional<T>& that) : _value(that._value), _hasValue(that._hasValue)
	{
		this->_hasValue = that._hasValue;
		this->_value = that._value;
	}

	Optional& operator=(const Optional<T>& that)
	{
		this->_hasValue = that._hasValue;
		this->_value = that._value;
	}

	Optional& operator=(const T& value)
	{
		_hasValue = true;
		_value = value;

		return *this;
	}

	T& operator*()
	{
		return getValue();
	}

	const T& operator*() const
	{
		return getValue();
	}

	T* operator->()
	{
		return &getValue();
	}

	const T* operator->() const
	{
		return &getValue();
	}

	bool hasValue() const
	{
		return _hasValue;
	}

	void reset()
	{
		_hasValue = false;
	}

	T& getValue()
	{
		if (!_hasValue)
			throw InvalidStateException("Value is not set!");

		return _value;
	}

	const T& getValue() const
	{
		if (!_hasValue)
			throw InvalidStateException("Value is not set!");

		return _value;
	}

private:

	bool _hasValue;
	T _value;

};