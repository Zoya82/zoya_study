#pragma once

#include <iostream>
using namespace std;
//�ڵ�
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

//������
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
				return false; //�������ظ�
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
				return true; //��ȵ�ʱ��
		}

		return false;        //û����ȵ�ʱ��
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
				//���ɾ��
				if (cur->_left == nullptr) //������Ϊ��
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
				else if (cur->_right == nullptr) //������Ϊ��
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
				else //���Ҷ���Ϊ��
				{
					//������������С�ڵ�������������������ڵ㣩
					Node* replaceParent = cur;  //��ʱ�Ѿ�ȷ����������
					Node* replace = cur->_right;
					while (replace->_left)
					{
						replaceParent = replace;
						replace = replace->_left;
					}

					swap(cur->_key, replace->_key);

					//�����ж�replace��replaceParent�����ӻ����Һ���
					if (replaceParent->_left == replace) //����
					{
						replaceParent->_left = replace->_right; //replace���ܻ����Һ��ӣ�Ҳ������nullptr
					}
					else //�Һ���
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

	void InOrder() //���ⲿ���õĺ��������õ�ʱ����֪���ڲ���_root
	{
		_InOrder(_root);//���ڲ�����֪���ڲ���Ա����
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