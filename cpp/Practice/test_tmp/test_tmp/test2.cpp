//#include <iostream>
//#include <string>
//#include <stack>
//
//using namespace std;
//
//int main()
//{
//	string s;
//	cin >> s;
//	stack<pair<char, int>> stk;
//
//	for (char c : s)
//	{
//		if (!stk.empty()&&stk.top().first == c)
//		{
//			stk.top().second++;
//		}
//		else
//		{
//			stk.push({ c,1 });
//		}
//
//		if (!stk.empty()&&stk.top().second >= 3)
//		{
//			stk.pop();
//		}
//	}
//
//	string result;
//	while (!stk.empty())
//	{
//		auto top = stk.top();
//		stk.pop();
//		result = string(top.second, top.first) + result;
//	}
//
//	cout << result << endl;
//}