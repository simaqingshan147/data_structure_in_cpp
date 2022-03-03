//��linearList
#include<iostream>
using namespace std;
#define INITCAPACITY 10

//linearList����
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

//�ı�һά���鳤��
template<typename T>
void changeLength(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
		exit(0);
	T* temp = new T[newLength];

	int num = min(oldLength, newLength);   //����Ԫ�ظ���
	for (int i = 0; i < num; i++)
		temp[i] = a[i];
	
	delete[]a;
	a = temp;
}

//linearList������arrayList
//���Ա����������
template<typename T>
class arrayList :public linearList<T>
{
public:
	//���캯�������ƺ�������������
	arrayList(int initialCapacity = INITCAPACITY);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[]element; }

	//ADT����
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int Index) const;
	int indexOf(const T& element)const;
	void erase(int Index);
	void insert(int Index, const T& element);
	void output(ostream& out)const;

	//��������
	int capacity()const { return arrayLength; }

	//arrayList��˫���������
	class iterator
	{
		//��c++��typedef���ʵ��˫�������
	public:
		//��c++��typedef���ʵ��˫�������
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//���캯��
		iterator(T* Position = 0) { position = Position; }

		//�����ò�����
		T& operator*()const { return *position; }
		T* operator->()const { return &*position; }

		//��������ֵ����
		//++iterator
		iterator& operator++() { ++position; return *this; }
		//iterator++
		iterator operator++(int)
		{
			iterator old = *this;
			++position;
			return old;
		}

		//��������ֵ����
		//--iterator
		iterator& operator--(){ --position; return *this; }
		//iterator--
		iterator operator--(int)
		{
			iterator old = *this;
			--position;
			return old;
		}

		//�����Ƿ����
		bool operator!=(const iterator right) const{
			return position != right.position;
		}
		bool operator==(const iterator right)const {
			return position == right.position;
		}


	protected:
		T* position;    //ָ���Ԫ�ص�ָ��
	};
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }

protected:
	void checkIndex(int Index)const;   //������Ч���׳��쳣
	T* element;            //һά����
	int arrayLength;       //һά��������
	int listSize;          //���Ա�Ԫ�ظ���
};


//���캯��
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

//���ƹ��캯��
template<typename T>
arrayList<T>::arrayList(const arrayList<T>& thelist)
{
	arrayLength = thelist.arrayLength;
	listSize = thelist.listSize;
	element = new T[arrayLength];

	for (int i = 0; i < listSize; i++)
		element[i] = thelist[i];
}

//�������
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

//��������ΪIndex��Ԫ��
template<typename T>
T& arrayList<T>::get(int Index)const {
	checkIndex(Index);
	return element[Index];
}

//����element��һ�γ��ֵ�����
template<typename T>
int arrayList<T>::indexOf(const T& Element)const
{
	int index = (int)(find(element, element + listSize, Element) - element);
	if (index == listSize)   //û�ҵ�
		return -1;
	return index;
}

//ɾ������Ϊindex��Ԫ��
template<typename T>
void arrayList<T>::erase(int Index)
{
	checkIndex(Index);
	//�ƶ���������index��Ԫ��
	copy(element + Index + 1, element + listSize, element + Index);
	element[--listSize].~T();   //������������

	//�޸�ɾ���������Զ�����
	if (listSize < arrayLength / 4)  //������С���������ķ�֮һ
	{
		int newlength = max(INITCAPACITY, arrayLength / 2);   //����С�ڳ�ʼ����
		changeLength(element, arrayLength, newlength);
	}
}

//����
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
	//����ƶ�һ��λ��
	copy_backward(element + Index, element + listSize,
		element + listSize + 1); 
		element[Index] = Element;
		listSize++;
}

//�����Ա���������
template<typename T>
void arrayList<T>::output(ostream& out)const
{
	//ostream_interator��д��Ԫ�صĵ�����
	//" "ָ��д��Ԫ�طָ���Ϊ�ո�
	if (!out)
		copy(element, element + listSize, ostream_iterator<T>(cout, " "));
	else
		copy(element, element + listSize, ostream_iterator<T>(out, " "));
}

//����<<
template<typename T>
ostream& operator<<(ostream& out,const arrayList<T>& x)
{
	x.output(out);
	return out;
}

