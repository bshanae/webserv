#pragma once

namespace algo
{
	template <typename TC, typename T>
	bool contains(const TC& container, const T& item)
	{
		return container.find(item) != container.end();
	}
}