//类linearList
#include<iostream>
using namespace std;
#define INITCAPACITY 10

//linearList虚类
template<typename T>
class linearList
{
public:
	virtual ~linearList() {};
	virtual bool empty()const = 0;
	virtual int size()const = 0;
	virtual T& get(int Index) const = 0;
	virtual int indexOf(const T& element)const = 0;
	virtual void erase(int Index) = 0;
	virtual void insert(int Index, const T& element) = 0;
	virtual void output(ostream& out)const = 0;
};

//改变一维数组长度
template<typename T>
void changeLength(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
		exit(0);
	T* temp = new T[newLength];

	int num = min(oldLength, newLength);   //复制元素个数
	for (int i = 0; i < num; i++)
		temp[i] = a[i];
	
	delete[]a;
	a = temp;
}

//linearList派生类arrayList
//线性表的数组描述
template<typename T>
class arrayList :public linearList<T>
{
public:
	//构造函数，复制函数，析构函数
	arrayList(int initialCapacity = INITCAPACITY);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[]element; }

	//ADT方法
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int Index) const;
	int indexOf(const T& element)const;
	void erase(int Index);
	void insert(int Index, const T& element);
	void output(ostream& out)const;

	//其他方法
	int capacity()const { return arrayLength; }

	//arrayList的双向迭代器类
	class iterator
	{
		//用c++的typedef语句实现双向迭代器
	public:
		//用c++的typedef语句实现双向迭代器
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//构造函数
		iterator(T* Position = 0) { position = Position; }

		//解引用操作符
		T& operator*()const { return *position; }
		T* operator->()const { return &*position; }

		//迭代器的值增加
		//++iterator
		iterator& operator++() { ++position; return *this; }
		//iterator++
		iterator operator++(int)
		{
			iterator old = *this;
			++position;
			return old;
		}

		//迭代器的值减少
		//--iterator
		iterator& operator--(){ --position; return *this; }
		//iterator--
		iterator operator--(int)
		{
			iterator old = *this;
			--position;
			return old;
		}

		//测试是否相等
		bool operator!=(const iterator right) const{
			return position != right.position;
		}
		bool operator==(const iterator right)const {
			return position == right.position;
		}


	protected:
		T* position;    //指向表元素的指针
	};
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }

protected:
	void checkIndex(int Index)const;   //索引无效，抛出异常
	T* element;            //一维数组
	int arrayLength;       //一维数组容量
	int listSize;          //线性表元素个数
};


//构造函数
template<typename T>
arrayList<T>::arrayList(int initialCapaticy)
{
	if (initialCapaticy < 1)
	{
		cerr << "Initaial capacity =" << initialCapaticy
			<< " Must be > 0" << endl;
		exit(0);
	}
	arrayLength = initialCapaticy;
	element = new T[arrayLength];
	listSize = 0;
}

//复制构造函数
template<typename T>
arrayList<T>::arrayList(const arrayList<T>& thelist)
{
	arrayLength = thelist.arrayLength;
	listSize = thelist.listSize;
	element = new T[arrayLength];

	for (int i = 0; i < listSize; i++)
		element[i] = thelist[i];
}

//检查索引
template<typename T>
void arrayList<T>::checkIndex(int Index) const
{
	if (Index < 0 || Index >= listSize)
	{
		cerr << "index=" << Index << "size="
			<< listSize << endl;
		exit(0);
	}

}

//返回索引为Index的元素
template<typename T>
T& arrayList<T>::get(int Index)const {
	checkIndex(Index);
	return element[Index];
}

//返回element第一次出现的索引
template<typename T>
int arrayList<T>::indexOf(const T& Element)const
{
	int index = (int)(find(element, element + listSize, Element) - element);
	if (index == listSize)   //没找到
		return -1;
	return index;
}

//删除索引为index的元素
template<typename T>
void arrayList<T>::erase(int Index)
{
	checkIndex(Index);
	//移动索引大于index的元素
	copy(element + Index + 1, element + listSize, element + Index);
	element[--listSize].~T();   //调用析构函数

	//修改删除函数，自动缩容
	if (listSize < arrayLength / 4)  //数据数小于容量的四分之一
	{
		int newlength = max(INITCAPACITY, arrayLength / 2);   //不能小于初始长度
		changeLength(element, arrayLength, newlength);
	}
}

//插入
template<typename T>
void arrayList<T>::insert(int Index, const T& Element)
{
	if (Index<0 || Index>listSize)
	{
		cerr << "index= " << Index << " size= " << listSize;
		exit(0);
	}
	if (listSize == arrayLength)
	{
		changeLength(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	//向后移动一个位置
	copy_backward(element + Index, element + listSize,
		element + listSize + 1); 
		element[Index] = Element;
		listSize++;
}

//把线性表插入输出流
template<typename T>
void arrayList<T>::output(ostream& out)const
{
	//ostream_interator，写入元素的迭代器
	//" "指定写入元素分隔符为空格
	if (!out)
		copy(element, element + listSize, ostream_iterator<T>(cout, " "));
	else
		copy(element, element + listSize, ostream_iterator<T>(out, " "));
}

//重载<<
template<typename T>
ostream& operator<<(ostream& out,const arrayList<T>& x)
{
	x.output(out);
	return out;
}

