#pragma once

#include<assert.h>

//class list {
//public:
//
//private:
//
//}; //����ֱ��������ṹ��ʼ��Ҫ�����ռ��Լ�ʹ��ģ����

namespace zoya {
	template<class T>
	struct list_node //����һ��ͨ�ýڵ�ģ�壬�������ֻ���list_node�����㲻ͬ��������ڵ�ṹ���������ڿ��Ըı���Node
	{
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;

		list_node(const T& x = T())  //������ù��캯��ʱ�����Σ����Զ�����T���͵�Ĭ�Ϲ��캯������һ��Ĭ��ֵ
			:_next(nullptr), _prev(nullptr), _data(x)
		{}
	};

	template<class T,class Ref,class Ptr>
	struct list_iterator
	{
		typedef list_node<T> Node;
		typedef list_iterator<T, Ref, Ptr> Self;

		Node* _node;

		list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*() { return _node->_data; }  //_node->_data��ʵ��ֵ������������������������ֵ
		Ptr operator->() { return &_node->_data; } //����node��data�ĵ�ַ��&ȡֵ

		Self& operator++()
		{
			_node = _node->_next;
			return *this; //this��Self*��*this��Self&
		}

		Self operator++(int) //���ð汾it++
		{
			Self tmp(*this); //�õ�ǰ��������Self
			_node = _node->_next; //��ǰ������ǰ��
			return tmp; //����ԭ����λ��
		}

		Self operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const Self& it) const //�Ƚ������������ڲ��Ľڵ�ָ���Ƿ�ָ��ͬһ��λ��
		{
			/*if (it->data == *this->data)
			{
				return true;
			}
			else 
				return false;*/
			return _node != it._node;
		}

		bool operator==(const Self& it) const
		{
			return _node == it._node;
		}
	};

	template<class Iterator,class Ref,class Ptr>
	struct Reverse_iterator
	{
		typedef Reverse_iterator<Iterator, Ref, Ptr> Self;

		Iterator _it; //����������ڲ���_itʵ����������������� ��ǰλ�õ���һ��Ԫ��

		Reverse_iterator(Iterator it) :_it(it) {}

		Ref operator*() 
		{
			Iterator tmp = _it; //�涨_itָ��������һ��Ԫ�صĺ�һ��λ��
			return *--tmp;
		}

		Ptr operator->()
		{
			return &(operator*());
		}

		Self& operator++()
		{
			--_it;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp = _it;
			--_it;
			return *tmp;
		}

		Self& operator--()
		{
			++_it;
			return *this;
		}

		Self operator--(int)
		{
			Self tmp = _it;
			++_it;
			return *tmp;
		}

		bool operator!=(const Self& it) const
		{
			return _it != it._it;
		}

		bool operator==(const Self& it) const
		{
			return _it == it._it;
		}
	};

	template<class T>
	class list
	{
		typedef list_node<T> Node;  //Ĭ��Ϊprivate���������ڲ��������͹�ע��
	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;


		list()
		{
			empty_init();
		}

		list(std::initializer_list<T> lt) //{1, 2, 3, 4} �����﷨���� C++11 �б����Ϊ�ᱻ�Զ�ת��Ϊһ�� std::initializer_list<int> ���͵Ķ���
		{
			empty_init();
			for (const auto& e : lt)
			{
				push_back(e);
			}

		}

		list(const list<T>& lt)
		{
			empty_init();
			for (const auto& e : lt)
			{
				push_back(e);
			}
		}

		list<T>& operator=(list<T> lt) //�����list<T>& lt���Ͳ��ܽ���swap()�������޸�const���á������ϲ��ǽ��������ÿ��Ǳ����õ�list����
		{
			swap(lt);
			return *this; //���ر���ֵ�ı���
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		iterator begin() { return iterator(_head->_next); }
		iterator end() { return iterator(_head); } //ѭ��˫���������Ե�head��ʾ����������������

		const_iterator begin() const { return const_iterator(_head->_next); }
		const_iterator end() const { return const_iterator(_head); }

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		size_t size() const { return _size; }

		bool empty() const { return _size == 0; }

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			++_size;
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;

			delete cur;
			--_size;

			return iterator(next);
		}

		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

	private:
		void empty_init()
		{
			//_head = NULL;
			_head = new Node;  //���Ϸ��������ڴ��ָ��
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		Node* _head;
		size_t _size;
	};
}