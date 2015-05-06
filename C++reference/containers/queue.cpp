/*
����queue����������������������������Ϊ�ײ�ʵ�֡�queue֧�������ȳ�(FIFO)��ֻ�����ں�˲�����
����ǰ��ɾ�����ݣ����ܹ����ʶ����ڲ������ݡ�queue��֧�ֵ�����

template <class T, class Container = deque<T> > class queue;

queue::back     ���ʶ������������������һ������
queue::emplace  
queue::empty    ���Զ��������������Ƿ�Ϊ��
queue::front    ���ʶ��������������е�һ������
queue::pop      ɾ�����������������п�ͷ������
queue::push     �����������������ĩβ���һ������
queue::size     ���ض��������������е����ݵĸ���
queue::swap

*/

#include <iostream>       // std::cout
#include <queue>          // std::queue
#include <deque>          // std::deque
#include <list>           // std::list
#include <vector>         // std::vector

int main ()
{
	std::queue<int> myqueue;

	//�����������������ĩβ���һ������
	myqueue.push(12);
	myqueue.push(75);   // this is now the back

	//���ض��������������е����ݵĸ���
	std::cout << "queue size: " << myqueue.size() << '\n';

	// ���ʶ������������������һ������
	myqueue.back() -= myqueue.front();

	std::cout << "myqueue.back() is now " << myqueue.back() << '\n';

	//���Զ��������������Ƿ�Ϊ��
	while (!myqueue.empty())
	{
		//���ʶ��������������е�һ������
		std::cout << ' ' << myqueue.front();
		//ɾ�����������������п�ͷ������
		myqueue.pop();
	}
		std::cout << '\n';

	// ����queue_t����������������������������Ϊ�ײ�ʵ��.��׼��������ģ��vector, deque ��list����ʹ�ã�Ĭ������£�
	//���û�������౻ָ����Ϊһ���ر��stack �࣬��׼��������ģ�����deque ����
	std::deque<int> mydeck (3,100);        // deque with 3 elements
	std::list<int> mylist (2,200);         // list with 2 elements
	std::vector<int> myvector (2,200);        // vector with 2 elements {200, 200}

	std::queue<int> first;                 // empty queue
	std::queue<int> second (mydeck);       // queue initialized to copy of deque

	std::queue<int,std::vector<int> > third(myvector); 
	std::queue<int,std::list<int> > fourth (mylist);
	/*
	(gdb) print first
	$1 = std::queue wrapping: std::deque with 0 elements
	(gdb) print second
	$2 = std::queue wrapping: std::deque with 3 elements = {100, 100, 100}
	(gdb) print third
	$3 = std::queue wrapping: std::vector of length 2, capacity 2 = {200, 200}
	(gdb) print fourth
	$4 = std::queue wrapping: std::list = {
	  [0] = 200,
	  [1] = 200
	}
	*/

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';
	return 0;
}/*
output:

queue size: 2
myqueue.back() is now 63
 12 63
size of first: 0
size of second: 3
size of third: 2
size of fourth: 2

*/
