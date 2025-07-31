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

	// 左右都不为空
	t.Erase(8);
	t.InOrder();

	t.Erase(3);
	t.InOrder();

	// 右为空
	t.Erase(14);
	t.InOrder();

	// 左为空
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
//	dict.Insert("insert", "插入");
//	dict.Insert("erase", "删除");
//	dict.Insert("left", "左边");
//	dict.Insert("string", "字符串");
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
//			cout << "单词拼写错误" << endl;
//		}
//	}
//
//	string strs[] = { "苹果", "西瓜", "苹果", "樱桃", "苹果", "樱桃", "苹果", "樱桃", "苹果" };
//	// 统计水果出现的次
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