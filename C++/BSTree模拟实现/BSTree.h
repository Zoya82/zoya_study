#pragma once

#include <iostream>
using namespace std;
//节点
template<class K>
struct BSTNode
{
	K _key;
	BSTNode<K>* _left;
	BSTNode<K>* _right;

	BSTNode(const K& key)
		:_key(key)
		,_left(nullptr)
		,_right(nullptr)
	{}
};

//二叉树
template<class K>
class BSTree
{
	typedef BSTNode<K> Node;

public:
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false; //不允许重复
		}

		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		return true;
	}

	bool Find(const K& key)
	{
		Node* cur = _root;

		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
				return true; //相等的时候
		}

		return false;        //没有相等的时候
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//相等删除
				if (cur->_left == nullptr) //左子树为空
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{

						if (cur == parent->_left)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;

						}
					}

					delete cur;
				}
				else if (cur->_right == nullptr) //右子树为空
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{

						if (cur == parent->_left)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;

						}
					}

					delete cur;
				}
				else //左右都不为空
				{
					//用右子树的最小节点替代（或左子树的最大节点）
					Node* replaceParent = cur;  //此时已经确定向右子树
					Node* replace = cur->_right;
					while (replace->_left)
					{
						replaceParent = replace;
						replace = replace->_left;
					}

					swap(cur->_key, replace->_key);

					//用来判断replace是replaceParent的左孩子还是右孩子
					if (replaceParent->_left == replace) //左孩子
					{
						replaceParent->_left = replace->_right; //replace可能还有右孩子，也可能是nullptr
					}
					else //右孩子
					{
						replaceParent->_right = replace->_right;
					}

					delete replace;
				}

				return true;
			}
		}

		return false;
	}

	void InOrder() //在外部调用的函数，调用的时候不能知道内部的_root
	{
		_InOrder(_root);//类内部可以知道内部成员变量
		cout << endl;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

private:
	Node* _root = nullptr;
};