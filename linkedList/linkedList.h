//���� --���Ա����ʽ����
#include<iostream>
#include<string>
#define INITIALCAPACITY 10
using namespace std;

//���ڵ�
template<typename T>
class listNode
{
public:
	T element;
	listNode<T>* next;

	//����
	listNode() = default;
	listNode(const T& element){ this->element = element; }
	listNode(const T& element, listNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};


//����
template<typename T>
class linkedList
{
public:
	//���캯��
	linkedList(int initialCapacity = INITIALCAPACITY);
	linkedList(const linkedList<T>&);
	~linkedList();

	//ADT����
	bool empty() const { return listsize == 0; }
	int size() const { return listsize; }
	T& get(int index) const;
	int indexOf(const T& element) const;
	void erase(int index);
	void insert(int index, const T& element);
	void output(ostream& out) const;

	class listIterator {
		//ǰ�������
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//���캯��
		listIterator(listNode<T>* Node = NULL) { node = Node; }

		//�����ò�����
		T& operator*()const {return node->element; }
		T* operator->()const { return &node->element; }

		//�������ӷ�����
		listIterator& operator++() { node = node->next; return *this; }  //ǰ��
		listIterator operator++(int) {
			listIterator old = *this;
			node = node->next;
			return old;
		}

		//���У��
		bool operator!=(const listIterator right)const { return node != right.node; }
		bool operator==(const listIterator left)const { return node == right.node; }

	protected:
		listNode<T>* node;
	};

	//���ص���������
	listIterator begin() { return listIterator(root->next); }
	//end��ԶΪNULL����Ϊ��������NULL��β
	listIterator end() { return listIterator(NULL); }

	//last�ڵ㺯��
	T& back();
	void clear();
	void push_back(const T& element);

protected:
	void checkIndex(int index) const;  //�������
	listNode<T>* root;
	listNode<T>* last; //���һ���ڵ�
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

//���캯��
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

//���ƹ��캯��
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

	//�ǿ�
	listNode<T>* source = list.root->next;  //����Դ
	listNode<T>* targetNode = root;
	while (source != NULL)
	{
		targetNode->next = new listNode<T>(source->element);
		targetNode = targetNode->next;
		source = source->next;
	}
	targetNode->next = NULL;  //���һ���ڵ��nextΪNull
}

//��������
//���ɾ���ڵ㣬����root
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
	//last������������Ϊ���нڵ��Ѿ�����
}

//��������Ϊindex��Ԫ��
template<typename T>
T& linkedList<T>::get(int index) const
{
	checkIndex(index);

	//�������ڽڵ�
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

//��ȡԪ�ض�Ӧ������
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

//ɾ��ָ������Ԫ��
template<typename T>
void linkedList<T>::erase(int index)
{
	checkIndex(index);
	listNode<T>* del;
	
	//ɾ����һ��Ԫ��
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
			last = p;  //ɾ�����һ��Ԫ��
		del = p->next;
		p->next = p->next->next;
	}
	listsize--;  //��С����

	cout << del->element << " is removed" << endl;
	delete del;
}

//����ָ������Ԫ��
template<typename T>
void linkedList<T>::insert(int index, const T& element)
{
	if (index<0 || index>listsize)
		throw out_of_range("wrong insert range!");
	listNode<T>* temp = new listNode<T>(element);
	//�����һλ
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
	//�������һλ,����last
	if (index == listsize - 1)
		last = temp;
}

//�������
template<typename T>
void linkedList<T>::output(ostream& out) const
{
	for (listNode<T>* ptr = root->next;
		ptr != NULL; ptr = ptr->next)
		out << ptr->element << " ";
	out << "done!" << endl;
}

//����<<
template<typename T>
ostream& operator<<(ostream& out, const linkedList<T>& x)
{
	x.output(out);
	return out;
}

//���
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
	//����Ϊ��
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

//������һ��Ԫ��
template<typename T>
T& linkedList<T>::back() {
	if (root->next == last)
		throw out_of_range("No element!");  //û��Ԫ��
	return last->element;
}