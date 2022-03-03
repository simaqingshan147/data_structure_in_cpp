#include "LinearList.h"

int main()
{
	arrayList<int> test;
	int n, i, con;
	con = 1;
	while (con)
	{
		cout << "1:创建初始表" << endl;
		cout << "2: 顺序表遍历" << endl;
		cout << "3: 获取索引" << endl;
		cout << "4: 删除数字" << endl;
		cout << "5: 迭代器测试" << endl;
		cout << "输入测试数: ";
		cin >> n;
		switch (n)
		{
		case 1:
		{
			cout << "创建初始表" << endl;
			for (i = 0; i < 100; i++)
				test.insert(i,i);
			break;
		}
		case 2:
		{
			cout << "顺序表遍历" << endl;
			test.output(cout);
			break;
		}
		case 3:
		{
			cout << "获取索引" << endl;
			int num;
			cout << "输入要搜索的数:(按-1退出)" << endl;
			while (cin >> num && num != -1)
			{
				cout << test.indexOf(num) << endl;
				cout << "输入要搜索的数:(按-1退出)" << endl;
			}
			break;
		}
		case 4:
		{
			cout << "删除数字" << endl;
			int index;
			cout << "输入删除元素索引:(-1退出)";
			while (cin >> index && index != -1)
			{
				cout << "原元素: ";
				test.output(cout);
				cout << endl;
				test.erase(index);
				cout << "修改元素: ";
				test.output(cout);
				cout << endl;
				cout << "输入删除元素索引:(-1退出)";
			}
			break;
		}
		case 5:
		{
			cout << "迭代器测试:";
			auto beg = test.begin();
			auto end = test.end();
			for (; beg != end; beg++)
				cout << *beg << " ";
			cout << "\ndone!" << endl;
			break;
		}
		default:
			break;
		}
		cout << "\n是否继续(0 or 1):";
		cin >> con;
	}
	return 0;
}