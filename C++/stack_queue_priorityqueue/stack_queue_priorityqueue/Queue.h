#pragma once

#include <vector>
#include <list>
#include <deque>

namespace zoya
{
	template<class T,class Container=deque<T>>
	class queue
	{
	public:
		queue() {}

		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_front();
		}

		const T& front()
		{
			return _con.front();
		}

		const T& back()
		{
			return _con.back();
		}

		size_t size() const
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}