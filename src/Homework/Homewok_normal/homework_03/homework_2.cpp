/*模仿Stack栈类设计线性表类*/
#include <iostream>
#include <new>
using namespace std;

class MyLinkedList
{
public:
	struct LinkedNode
	{
		int val;
		LinkedNode *next;
		LinkedNode(int val) : val(val), next(nullptr) {}
	};
	//初始化
	MyLinkedList()
	{
		_LinkList = new LinkedNode(0);
		_size = 0;
	}
	//获取链表中第 index 个节点的值。如果索引无效，则返回-1
	int get(int index);
	//在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点
	void addAtHead(int val);
	//将值为 val 的节点追加到链表的最后一个元素
	void addAtTail(int val);
	/*在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。
	如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。*/
	void addAtIndex(int index, int val);
	//如果索引 index 有效，则删除链表中的第 index 个节点。
	void deleteAtIndex(int index);
	//链表的遍历
	void travelList();

private:
	int _size;
	LinkedNode *_LinkList;
};

int main()
{
	MyLinkedList *linkedList = new MyLinkedList();
	linkedList->addAtHead(1);
	linkedList->addAtTail(3);
	linkedList->addAtIndex(1, 2); //链表变为1-> 2-> 3
	cout << "此时遍历链表的结果为: " << endl;
	linkedList->travelList();
	linkedList->get(1);			  //返回2
	linkedList->deleteAtIndex(1); //现在链表是1-> 3
	cout << "此时链表索引为1的元素的值是: " << linkedList->get(1) << endl;	//返回3
	return 0;
}

//获取链表中第 index 个节点的值。如果索引无效，则返回-1
int MyLinkedList::get(int index)
{
	if (index > (_size - 1) || index < 0)
		return -1;
	LinkedNode *cur = _LinkList->next;
	while (index--)
	{
		cur = cur->next;
	}
	return cur->val;
}

//在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点
void MyLinkedList::addAtHead(int val)
{
	LinkedNode *t = new LinkedNode(val);
	t->next = _LinkList->next;
	_LinkList->next = t;
	_size++;
}

//将值为 val 的节点追加到链表的最后一个元素
void MyLinkedList::addAtTail(int val)
{
	LinkedNode *cur = _LinkList;
	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
	LinkedNode *newNode = new LinkedNode(val);
	cur->next = newNode;
	_size++;
}

/*在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。
	如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。*/
void MyLinkedList::addAtIndex(int index, int val)
{
	if (index > _size)
		return;
	LinkedNode *cur = _LinkList;
	while (index--)
	{
		cur = cur->next;
	}
	LinkedNode *newNode = new LinkedNode(val);
	newNode->next = cur->next;
	cur->next = newNode;
	_size++;
}

//如果索引 index 有效，则删除链表中的第 index 个节点。
void MyLinkedList::deleteAtIndex(int index)
{
	if (index < 0 || index >= _size)
		return;
	LinkedNode *cur = _LinkList;
	while (index--)
	{
		cur = cur->next;
	}
	LinkedNode *t = cur->next;
	cur->next = cur->next->next;
	delete t;
	_size--;
}

//遍历链表
void MyLinkedList::travelList()
{
	LinkedNode * p = _LinkList->next;
	while(p != nullptr)
	{
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}
