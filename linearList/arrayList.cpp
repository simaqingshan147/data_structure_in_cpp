#include "LinearList.h"

int main()
{
	arrayList<int> test;
	int n, i, con;
	con = 1;
	while (con)
	{
		cout << "1:������ʼ��" << endl;
		cout << "2: ˳������" << endl;
		cout << "3: ��ȡ����" << endl;
		cout << "4: ɾ������" << endl;
		cout << "5: ����������" << endl;
		cout << "���������: ";
		cin >> n;
		switch (n)
		{
		case 1:
		{
			cout << "������ʼ��" << endl;
			for (i = 0; i < 100; i++)
				test.insert(i,i);
			break;
		}
		case 2:
		{
			cout << "˳������" << endl;
			test.output(cout);
			break;
		}
		case 3:
		{
			cout << "��ȡ����" << endl;
			int num;
			cout << "����Ҫ��������:(��-1�˳�)" << endl;
			while (cin >> num && num != -1)
			{
				cout << test.indexOf(num) << endl;
				cout << "����Ҫ��������:(��-1�˳�)" << endl;
			}
			break;
		}
		case 4:
		{
			cout << "ɾ������" << endl;
			int index;
			cout << "����ɾ��Ԫ������:(-1�˳�)";
			while (cin >> index && index != -1)
			{
				cout << "ԭԪ��: ";
				test.output(cout);
				cout << endl;
				test.erase(index);
				cout << "�޸�Ԫ��: ";
				test.output(cout);
				cout << endl;
				cout << "����ɾ��Ԫ������:(-1�˳�)";
			}
			break;
		}
		case 5:
		{
			cout << "����������:";
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
		cout << "\n�Ƿ����(0 or 1):";
		cin >> con;
	}
	return 0;
}