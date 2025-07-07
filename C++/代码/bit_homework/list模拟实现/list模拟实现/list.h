#pragma once

#include<assert.h>

//class list {
//public:
//
//private:
//
//}; //不能直接以这个结构开始，要命名空间以及使用模板类

namespace zoya {
	template<class T>
	struct list_node //这是一个通用节点模板，所以名字还用list_node，方便不同容器共享节点结构，在容器内可以改别名Node
	{
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;

		list_node(const T& x = T())  //如果调用构造函数时不传参，就自动调用T类型的默认构造函数生成一个默认值
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

		Ref operator*() { return _node->_data; }  //_node->_data是实际值，引用它即访问它，可做左值
		Ptr operator->() { return &_node->_data; } //返回node的data的地址，&取值

		Self& operator++()
		{
			_node = _node->_next;
			return *this; //this是Self*，*this是Self&
		}

		Self operator++(int) //后置版本it++
		{
			Self tmp(*this); //用当前对象构造新Self
			_node = _node->_next; //当前对象本身前进
			return tmp; //返回原来的位置
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

		bool operator!=(const Self& it) const //比较两个迭代器内部的节点指针是否指向同一个位置
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

		Iterator _it; //反向迭代器内部的_it实际上是正向迭代器中 当前位置的下一个元素

		Reverse_iterator(Iterator it) :_it(it) {}

		Ref operator*() 
		{
			Iterator tmp = _it; //规定_it指向的是最后一个元素的后一个位置
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
		typedef list_node<T> Node;  //默认为private，辅助性内部别名，低关注度
	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;


		list()
		{
			empty_init();
		}

		list(std::initializer_list<T> lt) //{1, 2, 3, 4} 这种语法，在 C++11 中被设计为会被自动转换为一个 std::initializer_list<int> 类型的对象。
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

		list<T>& operator=(list<T> lt) //如果用list<T>& lt，就不能进行swap()，因不能修改const引用。本质上不是交换，不用考虑本引用的list本身
		{
			swap(lt);
			return *this; //返回被赋值的本身
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		iterator begin() { return iterator(_head->_next); }
		iterator end() { return iterator(_head); } //循环双向链表，所以到head表示整个链表都遍历完了

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
			_head = new Node;  //堆上分配的这块内存的指针
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		Node* _head;
		size_t _size;
	};
}