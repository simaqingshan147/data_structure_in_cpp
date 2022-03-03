#include<vector>
#include "LinearList.h"

// vector, 容量按50 % -100 % 增加
// vector构造函数与arrayList不一样
// vector无get, indexof和output函数(没有下标接口)
// erase和insert不接受索引，而是内存地址

/*
* linearList的派生类
* 线性表的vector实现
*/
template<typename T>
class vectorList :public linearList<T>
{
public:
	
	//构造函数,复制构造函数和析构函数
	vectorList(int initialCapacity = INITCAPACITY);
	vectorList(const vectorList<T>&);
	~vectorList() { delete element; }

	//ADT方法
	bool empty()const { return element->empty(); }
	int size()const { return (int)element->size(); }
	T& get(int index)const;
	int indexOf(const T& Element)const;
	void erase(int index);
	void insert(int index, const T& Element);
	void output(ostream& out)const;

	//其他方法
	int capacity()const { return (int)element->capacity(); }

	//线性表迭代器
	typedef typename vector<T>::iterator iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }

protected:
	void checkIndex(int index)const;
	vector<T>* element;
};


//构造函数
template<typename T>
vectorList<T>::vectorList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cerr << "Initial capacity = "
			<< initialCapacity << " Must be > 0" << endl;
		exit(1);
	}
	element = new vector<T>;   //构建空vector
	element->reserve(initialCapacity);    //分配容量
}

//复制构造函数
template<typename T>
vectorList<T>::vectorList(const vectorList<T>& List)
{
	element = new vector<T>(*List->element);
}

//删除指定索引元素
template<typename T>
void vectorList<T>::erase(int index)
{
	checkIndex(index);
	element->erase(begin() + index);
}

//插入元素于指定索引
template<typename T>
void vectorList<T>::insert(int index, const T& Element)
{
	if (index<0 || index>size())
	{
		cerr << "index = " << index
			<< "size = " << size();
		exit(1);
	}
	element->insert(element->begin() + index, Element);
}