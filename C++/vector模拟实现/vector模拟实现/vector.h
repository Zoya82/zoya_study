#pragma once
#include <assert.h>
#include <algorithm>

namespace zoya
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin() { return _start; } //迭代器访问接口
		iterator end() { return _finish; }
		const_iterator begin()const { return _start; }
		const_iterator end() const { return _finish; }

		vector() {} //默认构造函数
		//vector(const vector& v) 等价
		//因为类名本身是模板类 vector<T>，所以写成 vector 实际就是 vector<T>。
		vector(const vector<T>& v)  //拷贝构造函数
		{
			reverse(v.size());  //预留空间
			for (auto& e : v)  
			//由于 e 是引用（auto&），但 v 是 const，所以 e 的类型其实是 const T&
			{
				push_back(e);  //每个e加到新vector中
			}
		}

		~vector()
		{
			delete[] _start;  
			//reserve中new T[n]申请了内存，所以_start指向的内存是动态申请的，要在析构函数delete[]释放
			_start = _finish = _end_of_storage = nullptr;
		}

		/* 普通写法 赋值运算符
		//vector& operator=(const vector& v)
		vector<T>& operator=(const vector<T>& v)
		{
			if (this != &v)
			{
				delete[] _start;
				_start = _finish = _end_of_storage = nullptr;;
				reserve(v.size());
				for (auto& e : v)
				{
					push__back(e);
				}
			}
			return *this;
		}*/

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		//vector<T>& operator=(vector<T>& v)
		//错误写法，这样会让v1=v2，也让v2=v1了
		vector<T>& operator=(vector<T> v)
		{
			this->swap(v);
			//swap(v)
			//this-> 明确告诉编译器去当前类作用域里找名为 swap 的成员函数
			//但swap(v)这是一个非限定名调用，编译器会优先查找当前作用域中是否有 swap 函数。也可能不自动从当前类中查找成员，可能有编译错误或歧义
			return *this;
		}

		void resize(size_t n, const T& val = T()) 
		//T 是模板参数，代表用 vector 这个模板类时，实际存储的数据类型。
		//int()=0,double()=0,string()=""，也可以直接用数字填充resize(10,6)
		{
			if (n < size)
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
				while (_finish != _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t oldSize = size();
				T* tmp = new T[n];
				for (size_t i = 0; i < oldSize; i++)
				{
					tmp[i] = _start[i];
				}

				delete[] _start;

				_start = tmp;
				_finish = _start + oldSize;  //大小看起来没变，但更新地址
				_end_of_storage = _start + n;
			}
		}

		size_t capacity() const //在调用时不会修改类中的任何成员变量
		{
			return _end_of_storage - _start;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		T& operator[](size_t i)  
		//操作非const的vector对象
		{
			assert(i < size());
			return _start[i];
		}

		const T& operator[](size_t i) const 
		//操作const的vector对象，且成员函数不会修改对象本身
		{
			assert(i < size());
			return _start[i];
		}

		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}

			//*_finish = x;
			new (_finish) T(x);
			++_finish;
		}

		void pop_back()
		{
			assert(_finish > _start);
			--_finish;
			_finish->~T();
		}

		void insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}

			iterator it = _finish - 1;
			while (it >= pos)
			{
				*(it + 1) = *it;
				--it;
			}

			*pos = x;
			++_finish;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			iterator it = pos + 1;
			while (it < _finish)
			{
				*(it - 1) = *it;
				++it;
			}

			--_finish;

			return pos;
		}

	private:
		iterator _start = nullptr;  //数据起始位置
		iterator _finish = nullptr;  //最后一个有效元素的下一个位置
		iterator _end_of_storage = nullptr;  //当前申请空间的结尾
	};
}