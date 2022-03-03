#include "linkedList.h"
//测试链表数据结构
using namespace std;

int main()
{
	linkedList<int> test;
	string word;
	cout << "a --- 插入100个节点\n"
		<< "b --- 返回索引\n"
		<< "c --- 返回索引对应值\n"
		<< "d --- 指定位置插入\n"
		<< "e --- 指定位置删除\n"
		<< "f --- 输出链表所有元素\n"
		<< "h --- 输出最后一个元素\n"
		<< "i --- 在链表尾部追加元素" << endl;
	cout << "链表测试:(输入q退出)";
	while (cin >> word && word.front() != 'q')
	{
		switch (word.front()) {
		case 'a': {
			cout << "\na:开始插入" << endl;
			for (int i = 0; i < 100; i++)
				test.insert(i, i);
			cout << "\n插入完成!" << endl;
			break;
		}
		case 'b': {
			int num;
			if (!test.empty())
			{
				cout << "\n请输入值:";
				cin >> num;
				cout << "\n";
				cout << num << "对应的索引为" << test.indexOf(num) << endl;
			}
			else
				cout << "\ntest为空" << endl;
			break;
		}
		case 'c': {
			int index;
			if (!test.empty())
			{
				cout << "\n请输入索引:";
				cin >>index;
				cout << "\n";
				cout << index << "对应的值为" << test.get(index) << endl;
			}
			else
				cout << "\ntest为空" << endl;
			break;
		}
		case 'd': {
			int pos, num;
			cout << "\n请输入位置，值:";
			cin >> pos >> num;
			test.insert(pos, num);
			cout << "\n插入完成!" << endl;
			break;
		}
		case 'e': {
			int pos;
			cout << "\n请输入位置:";
			cin >> pos;
			test.erase(pos);
			cout << "\n删除完成!" << endl;
			break;
		}
		case 'f': {
			cout << "\n输出所有元素:" << endl;
			test.output(cout);
			cout << "\n输出完成!" << endl;
		}
		case 'h': {
			cout << "\n最后一个元素为:" << test.back() << endl;
			break;
		}
		case 'i': {
			cout << "\n请输入插入值:";
			int num;
			cin >> num;
			test.push_back(num);
			break;
		}
		default: {
			cout << "\n无对应操作!" << endl;
			break;
		}
		}
		cout << "a --- 插入100个节点\n"
			<< "b --- 返回索引\n"
			<< "c --- 返回索引对应值\n"
			<< "d --- 指定位置插入\n"
			<< "e --- 指定位置删除\n"
			<< "f --- 输出链表所有元素\n"
			<< "h --- 输出最后一个元素\n"
			<< "i --- 在链表尾部追加元素" << endl;
		cout << "链表测试:(输入q退出)";
	}

	return 0;
}