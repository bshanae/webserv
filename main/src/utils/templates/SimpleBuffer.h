#pragma once

#include <vector>
#include <cstring>

template<typename T>
class SimpleBuffer
{
public:

	explicit SimpleBuffer(size_t initial_size): _dataSize(initial_size), _offsetR(0), _offsetW(0)
	{
		_data = new T[initial_size];
	}

	~SimpleBuffer()
	{
		delete[] _data;
	}

	const T* readPtr() const
	{
		return _data + _offsetR;
	}

	size_t availableReadSize() const
	{
		return _offsetW - _offsetR;
	}

	void didRead(size_t size)
	{
		_offsetR += size;
	}

	T* writePtr()
	{
		return _data + _offsetW;
	}

	size_t availableWriteSize() const
	{
		return _dataSize - availableReadSize();
	}

	void didWrite(size_t size)
	{
		_offsetW += size;
	}

	void willWrite(size_t size)
	{
		if (size > availableWriteSize())
			enlarge(size);
	}

	void write(const T* data, size_t dataSize)
	{
		willWrite(dataSize);
		std::memcpy(writePtr(), data, dataSize);
		didWrite(dataSize);
	}

	void pack()
	{
		std::memmove(_data, readPtr(), availableReadSize());

		_offsetW -= _offsetR;
		_offsetR = 0;
	}

	bool full() const
	{
		return _dataSize == _offsetW - 1;
	}

private:

	T* _data;
	size_t _dataSize;
	size_t _offsetR;
	size_t _offsetW;

	SimpleBuffer(SimpleBuffer&);
	SimpleBuffer& operator=(SimpleBuffer&);

	void enlarge(size_t required_size)
	{
		const size_t newSize = std::max(_dataSize * 2, required_size + _offsetW);
		T* newData = new T[newSize];

		std::memcpy(newData, _data, _dataSize);

		delete[] _data;

		_data = newData;
		_dataSize = newSize;
	}
};