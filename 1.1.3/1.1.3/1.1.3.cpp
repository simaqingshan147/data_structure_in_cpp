//1.1.3 冒泡排序,版本1A
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

//不要忘记传引用调用!
//哪怕swap能修改数据
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

	//生成随机数数组
	srand(time(NULL));
	vector<int> arr;
	for (i = 0; i < SIZE; i++)
		arr.push_back(rand());

	QueryPerformanceFrequency(&Freg);    //调用API函数，获得系统计时器频率
	QueryPerformanceCounter(&start);    //开始时间
	BubbleSort1A(arr);		    //排序函数
	QueryPerformanceCounter(&end);     //结束时间
	runtime = (double)(end.QuadPart - start.QuadPart)
		/ (double)Freg.QuadPart * 1000.0;

	i = 1;   //打印
	for (auto a : arr)
	{
		cout << a << ' ';
		if (i++ % 100 == 0)
			cout << '\n';
	}
	cout << endl;

	cout << "运行时间为 " << runtime << "ms" << endl;
	return 0;
}