//1.1.3 ð������,�汾1A
#include<iostream>
#include<vector>
#include<Windows.h>
#include<ctime>
#define SIZE 1000
using std::vector;
using std::cout;
using std::endl;

void swap(int& a, int& b)
{
	int c = b;
	b = a;
	a = c;
}

//��Ҫ���Ǵ����õ���!
//����swap���޸�����
void BubbleSort1A(vector<int>& a)
{
	bool sorted = false;
	auto end = a.end();
	decltype(end) beg;

	while (!sorted)
	{
		sorted = true;
		for (beg = ++a.begin(); beg != end; beg++)
		{
			if (*(beg-1) > *(beg))
			{
				swap(*(beg-1), *beg);
				sorted = false;
			}
		}
		--end;
	}
}

int main()
{
	int i;
	LARGE_INTEGER Freg;
	LARGE_INTEGER start, end;
	double runtime;

	//�������������
	srand(time(NULL));
	vector<int> arr;
	for (i = 0; i < SIZE; i++)
		arr.push_back(rand());

	QueryPerformanceFrequency(&Freg);    //����API���������ϵͳ��ʱ��Ƶ��
	QueryPerformanceCounter(&start);    //��ʼʱ��
	BubbleSort1A(arr);		    //������
	QueryPerformanceCounter(&end);     //����ʱ��
	runtime = (double)(end.QuadPart - start.QuadPart)
		/ (double)Freg.QuadPart * 1000.0;

	i = 1;   //��ӡ
	for (auto a : arr)
	{
		cout << a << ' ';
		if (i++ % 100 == 0)
			cout << '\n';
	}
	cout << endl;

	cout << "����ʱ��Ϊ " << runtime << "ms" << endl;
	return 0;
}