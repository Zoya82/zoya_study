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

		iterator begin() { return _start; } //���������ʽӿ�
		iterator end() { return _finish; }
		const_iterator begin()const { return _start; }
		const_iterator end() const { return _finish; }

		vector() {} //Ĭ�Ϲ��캯��
		//vector(const vector& v) �ȼ�
		//��Ϊ����������ģ���� vector<T>������д�� vector ʵ�ʾ��� vector<T>��
		vector(const vector<T>& v)  //�������캯��
		{
			reverse(v.size());  //Ԥ���ռ�
			for (auto& e : v)  
			//���� e �����ã�auto&������ v �� const������ e ��������ʵ�� const T&
			{
				push_back(e);  //ÿ��e�ӵ���vector��
			}
		}

		~vector()
		{
			delete[] _start;  
			//reserve��new T[n]�������ڴ棬����_startָ����ڴ��Ƕ�̬����ģ�Ҫ����������delete[]�ͷ�
			_start = _finish = _end_of_storage = nullptr;
		}

		/* ��ͨд�� ��ֵ�����
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
		//����д������������v1=v2��Ҳ��v2=v1��
		vector<T>& operator=(vector<T> v)
		{
			this->swap(v);
			//swap(v)
			//this-> ��ȷ���߱�����ȥ��ǰ��������������Ϊ swap �ĳ�Ա����
			//��swap(v)����һ�����޶������ã������������Ȳ��ҵ�ǰ���������Ƿ��� swap ������Ҳ���ܲ��Զ��ӵ�ǰ���в��ҳ�Ա�������б�����������
			return *this;
		}

		void resize(size_t n, const T& val = T()) 
		//T ��ģ������������� vector ���ģ����ʱ��ʵ�ʴ洢���������͡�
		//int()=0,double()=0,string()=""��Ҳ����ֱ�����������resize(10,6)
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
				_finish = _start + oldSize;  //��С������û�䣬�����µ�ַ
				_end_of_storage = _start + n;
			}
		}

		size_t capacity() const //�ڵ���ʱ�����޸����е��κγ�Ա����
		{
			return _end_of_storage - _start;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		T& operator[](size_t i)  
		//������const��vector����
		{
			assert(i < size());
			return _start[i];
		}

		const T& operator[](size_t i) const 
		//����const��vector�����ҳ�Ա���������޸Ķ�����
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
		iterator _start = nullptr;  //������ʼλ��
		iterator _finish = nullptr;  //���һ����ЧԪ�ص���һ��λ��
		iterator _end_of_storage = nullptr;  //��ǰ����ռ�Ľ�β
	};
}