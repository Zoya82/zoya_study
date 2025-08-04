#include"BSTree.h"

void TestBSTree1()
{
	int a[] = { 8, 3, 1, 10, 1, 6, 4, 7, 14, 13 };
	BSTree<int> t;

	for (auto e : a)
	{
		t.Insert(e);
	}

	t.InOrder();

	t.Insert(16);
	t.InOrder();

	t.Insert(3);
	t.InOrder();

	// ���Ҷ���Ϊ��
	t.Erase(8);
	t.InOrder();

	t.Erase(3);
	t.InOrder();

	// ��Ϊ��
	t.Erase(14);
	t.InOrder();

	// ��Ϊ��
	t.Erase(6);
	t.InOrder();

	for (auto e : a)
	{
		t.Erase(e);
		t.InOrder();
	}
}

//void TestBSTree2()
//{
//	BSTree<string, string> dict;
//	dict.Insert("insert", "����");
//	dict.Insert("erase", "ɾ��");
//	dict.Insert("left", "���");
//	dict.Insert("string", "�ַ���");
//
//	string str;
//	while (cin >> str)
//	{
//		auto ret = dict.Find(str);
//		if (ret)
//		{
//			cout << str << ":" << ret->_value << endl;
//		}
//		else
//		{
//			cout << "����ƴд����" << endl;
//		}
//	}
//
//	string strs[] = { "ƻ��", "����", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��" };
//	// ͳ��ˮ�����ֵĴ�
//	BSTree<string, int> countTree;
//	for (auto str : strs)
//	{
//		auto ret = countTree.Find(str);
//		if (ret == NULL)
//		{
//			countTree.Insert(str, 1);
//		}
//		else
//		{
//			ret->_value++;
//		}
//	}
//	countTree.InOrder();
//}

int main()
{
	TestBSTree1();

	return 0;
}