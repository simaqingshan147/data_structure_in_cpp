#include "linkedList.h"
//�����������ݽṹ
using namespace std;

int main()
{
	linkedList<int> test;
	string word;
	cout << "a --- ����100���ڵ�\n"
		<< "b --- ��������\n"
		<< "c --- ����������Ӧֵ\n"
		<< "d --- ָ��λ�ò���\n"
		<< "e --- ָ��λ��ɾ��\n"
		<< "f --- �����������Ԫ��\n"
		<< "h --- ������һ��Ԫ��\n"
		<< "i --- ������β��׷��Ԫ��" << endl;
	cout << "�������:(����q�˳�)";
	while (cin >> word && word.front() != 'q')
	{
		switch (word.front()) {
		case 'a': {
			cout << "\na:��ʼ����" << endl;
			for (int i = 0; i < 100; i++)
				test.insert(i, i);
			cout << "\n�������!" << endl;
			break;
		}
		case 'b': {
			int num;
			if (!test.empty())
			{
				cout << "\n������ֵ:";
				cin >> num;
				cout << "\n";
				cout << num << "��Ӧ������Ϊ" << test.indexOf(num) << endl;
			}
			else
				cout << "\ntestΪ��" << endl;
			break;
		}
		case 'c': {
			int index;
			if (!test.empty())
			{
				cout << "\n����������:";
				cin >>index;
				cout << "\n";
				cout << index << "��Ӧ��ֵΪ" << test.get(index) << endl;
			}
			else
				cout << "\ntestΪ��" << endl;
			break;
		}
		case 'd': {
			int pos, num;
			cout << "\n������λ�ã�ֵ:";
			cin >> pos >> num;
			test.insert(pos, num);
			cout << "\n�������!" << endl;
			break;
		}
		case 'e': {
			int pos;
			cout << "\n������λ��:";
			cin >> pos;
			test.erase(pos);
			cout << "\nɾ�����!" << endl;
			break;
		}
		case 'f': {
			cout << "\n�������Ԫ��:" << endl;
			test.output(cout);
			cout << "\n������!" << endl;
		}
		case 'h': {
			cout << "\n���һ��Ԫ��Ϊ:" << test.back() << endl;
			break;
		}
		case 'i': {
			cout << "\n���������ֵ:";
			int num;
			cin >> num;
			test.push_back(num);
			break;
		}
		default: {
			cout << "\n�޶�Ӧ����!" << endl;
			break;
		}
		}
		cout << "a --- ����100���ڵ�\n"
			<< "b --- ��������\n"
			<< "c --- ����������Ӧֵ\n"
			<< "d --- ָ��λ�ò���\n"
			<< "e --- ָ��λ��ɾ��\n"
			<< "f --- �����������Ԫ��\n"
			<< "h --- ������һ��Ԫ��\n"
			<< "i --- ������β��׷��Ԫ��" << endl;
		cout << "�������:(����q�˳�)";
	}

	return 0;
}