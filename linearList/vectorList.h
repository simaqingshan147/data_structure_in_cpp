#include<vector>
#include "LinearList.h"

// vector, ������50 % -100 % ����
// vector���캯����arrayList��һ��
// vector��get, indexof��output����(û���±�ӿ�)
// erase��insert�����������������ڴ��ַ

/*
* linearList��������
* ���Ա��vectorʵ��
*/
template<typename T>
class vectorList :public linearList<T>
{
public:
	
	//���캯��,���ƹ��캯������������
	vectorList(int initialCapacity = INITCAPACITY);
	vectorList(const vectorList<T>&);
	~vectorList() { delete element; }

	//ADT����
	bool empty()const { return element->empty(); }
	int size()const { return (int)element->size(); }
	T& get(int index)const;
	int indexOf(const T& Element)const;
	void erase(int index);
	void insert(int index, const T& Element);
	void output(ostream& out)const;

	//��������
	int capacity()const { return (int)element->capacity(); }

	//���Ա������
	typedef typename vector<T>::iterator iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }

protected:
	void checkIndex(int index)const;
	vector<T>* element;
};


//���캯��
template<typename T>
vectorList<T>::vectorList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cerr << "Initial capacity = "
			<< initialCapacity << " Must be > 0" << endl;
		exit(1);
	}
	element = new vector<T>;   //������vector
	element->reserve(initialCapacity);    //��������
}

//���ƹ��캯��
template<typename T>
vectorList<T>::vectorList(const vectorList<T>& List)
{
	element = new vector<T>(*List->element);
}

//ɾ��ָ������Ԫ��
template<typename T>
void vectorList<T>::erase(int index)
{
	checkIndex(index);
	element->erase(begin() + index);
}

//����Ԫ����ָ������
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