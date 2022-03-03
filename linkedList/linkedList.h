//链表 --线性表的链式描述
#include<iostream>
#include<string>
#define INITIALCAPACITY 10
using namespace std;

//链节点
template<typename T>
class listNode
{
public:
	T element;
	listNode<T>* next;

	//方法
	listNode() = default;
	listNode(const T& element){ this->element = element; }
	listNode(const T& element, listNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};


//链表
template<typename T>
class linkedList
{
public:
	//构造函数
	linkedList(int initialCapacity = INITIALCAPACITY);
	linkedList(const linkedList<T>&);
	~linkedList();

	//ADT方法
	bool empty() const { return listsize == 0; }
	int size() const { return listsize; }
	T& get(int index) const;
	int indexOf(const T& element) const;
	void erase(int index);
	void insert(int index, const T& element);
	void output(ostream& out) const;

	class listIterator {
		//前向迭代器
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//构造函数
		listIterator(listNode<T>* Node = NULL) { node = Node; }

		//解引用操作符
		T& operator*()const {return node->element; }
		T* operator->()const { return &node->element; }

		//迭代器加法操作
		listIterator& operator++() { node = node->next; return *this; }  //前加
		listIterator operator++(int) {
			listIterator old = *this;
			node = node->next;
			return old;
		}

		//相等校验
		bool operator!=(const listIterator right)const { return node != right.node; }
		bool operator==(const listIterator left)const { return node == right.node; }

	protected:
		listNode<T>* node;
	};

	//返回迭代器函数
	listIterator begin() { return listIterator(root->next); }
	//end永远为NULL，因为链表总以NULL结尾
	listIterator end() { return listIterator(NULL); }

	//last节点函数
	T& back();
	void clear();
	void push_back(const T& element);

protected:
	void checkIndex(int index) const;  //检查索引
	listNode<T>* root;
	listNode<T>* last; //最后一个节点
	int listsize;
};
	
template<typename T>
void linkedList<T>::checkIndex(int index) const
{
	if (listsize == 0)
		cerr << "no elements!" << endl;
	if (index <0 || index > listsize)
		cerr << "illgal index!" << endl;
}

//构造函数
template<typename T>
linkedList<T>::linkedList(int initalCapacity)
{
	if (initalCapacity < 1)
	{
		cerr << "Initial capacity = " << initalCapacity
			<< " Must be > 0";
		exit(1);
	}
	root = new listNode<T>;
	last = new listNode<T>;
	root->next = NULL;
	last = root->next;
	listsize = 0;
}

//复制构造函数
template<typename T>
linkedList<T>::linkedList(const linkedList<T>& list)
{
	listsize = list.listsize;
	last = list->last;
	if (listsize == 0)
	{
		root->next = NULL;
		return;
	}

	//非空
	listNode<T>* source = list.root->next;  //复制源
	listNode<T>* targetNode = root;
	while (source != NULL)
	{
		targetNode->next = new listNode<T>(source->element);
		targetNode = targetNode->next;
		source = source->next;
	}
	targetNode->next = NULL;  //最后一个节点的next为Null
}

//析构函数
//逐个删除节点，包括root
template<typename T>
linkedList<T>::~linkedList()
{
	listNode<T>* nextNode;
	while (root)
	{
		nextNode = root->next;
		delete root;
		root = nextNode;
	}
	//last不用析构，因为所有节点已经析构
}

//返回索引为index的元素
template<typename T>
T& linkedList<T>::get(int index) const
{
	checkIndex(index);

	//移向所在节点
	listNode<T>* ptr = root->next;
	int i = 0;
	while (ptr&&i!=index)
	{
		ptr = ptr->next;
		i++;
	}
	if (!ptr)
	{
		cout << "index = " << i << " not found!";
		exit(1);
	}
	return ptr->element;
}

//获取元素对应的索引
template<typename T>
int linkedList<T>::indexOf(const T& element) const
{
	listNode<T>* ptr = root->next;
	int index = 0;
	while (ptr && ptr->element != element)
	{
		ptr = ptr->next;
		index++;
	}
	if (ptr == NULL)
		return -1;
	return index;
}

//删除指定索引元素
template<typename T>
void linkedList<T>::erase(int index)
{
	checkIndex(index);
	listNode<T>* del;
	
	//删除第一个元素
	if (index == 0)
	{
		del = root->next;
		root->next = root->next->next;
		last = root->next;
	}
	else
	{
		listNode<T>* p = root->next;
		for (int i = 1; i < index; i++)
			p = p->next;
		if (index == listsize - 1)
			last = p;  //删除最后一个元素
		del = p->next;
		p->next = p->next->next;
	}
	listsize--;  //减小容量

	cout << del->element << " is removed" << endl;
	delete del;
}

//插入指定索引元素
template<typename T>
void linkedList<T>::insert(int index, const T& element)
{
	if (index<0 || index>listsize)
		throw out_of_range("wrong insert range!");
	listNode<T>* temp = new listNode<T>(element);
	//插入第一位
	if (index == 0)
	{
		temp->next = root->next;
		root->next = temp;
		cout << "successfully insert in first node" << endl;
	}
	else
	{
		listNode<T>* ptr = root->next;
		for (int i = 1; i < index; i++)
			ptr = ptr->next;
		temp->next = ptr->next;
		ptr->next = temp;
		cout << element << " successfully insert after " 
			<< ptr->element << endl;
	}
	listsize++;
	//插入最后一位,更新last
	if (index == listsize - 1)
		last = temp;
}

//输出链表
template<typename T>
void linkedList<T>::output(ostream& out) const
{
	for (listNode<T>* ptr = root->next;
		ptr != NULL; ptr = ptr->next)
		out << ptr->element << " ";
	out << "done!" << endl;
}

//重载<<
template<typename T>
ostream& operator<<(ostream& out, const linkedList<T>& x)
{
	x.output(out);
	return out;
}

//清空
template<typename T>
void linkedList<T>::clear()
{
	while (root->next)
	{
		listNode<T> nextnode = root->next;
		delete root;
		root = nextnode;
	}
	listsize = 0;
}

template<typename T>
void linkedList<T>::push_back(const T& element)
{
	listNode<T>* tmp = new listNode<T>(element, NULL);
	//链表为空
	if (root->next == NULL)
	{
		root->next = tmp;
		last = tmp;
		cout << "\nsucessfully push back in first node" << endl;
	}
	else
	{
		last->next = tmp;
		cout << "\nsuccessfully push back after " 
			<< last->element << endl;
		last = tmp;
	}
	listsize++;
}

//输出最后一个元素
template<typename T>
T& linkedList<T>::back() {
	if (root->next == last)
		throw out_of_range("No element!");  //没有元素
	return last->element;
}