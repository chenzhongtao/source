/*
队列queue是容器适配器，它是以序列容器为底层实现。queue支持先入先出(FIFO)，只允许在后端插入数
据在前端删除数据，不能够访问队列内部的数据。queue不支持迭代器

template <class T, class Container = deque<T> > class queue;

queue::back     访问队列容器适配器中最后一个数据
queue::emplace  
queue::empty    测试队列容器适配器是否为空
queue::front    访问队列容器适配器中第一个数据
queue::pop      删除队列容器适配器中开头的数据
queue::push     向队列容器适配器的末尾添加一个数据
queue::size     返回队列容器适配器中的数据的个数
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

	//向队列容器适配器的末尾添加一个数据
	myqueue.push(12);
	myqueue.push(75);   // this is now the back

	//返回队列容器适配器中的数据的个数
	std::cout << "queue size: " << myqueue.size() << '\n';

	// 访问队列容器适配器中最后一个数据
	myqueue.back() -= myqueue.front();

	std::cout << "myqueue.back() is now " << myqueue.back() << '\n';

	//测试队列容器适配器是否为空
	while (!myqueue.empty())
	{
		//访问队列容器适配器中第一个数据
		std::cout << ' ' << myqueue.front();
		//删除队列容器适配器中开头的数据
		myqueue.pop();
	}
		std::cout << '\n';

	// 队列queue_t是容器适配器，它是以序列容器为底层实现.标准的容器类模板vector, deque 和list可以使用，默认情况下，
	//如果没有容器类被指定成为一个特别的stack 类，标准的容器类模板就是deque 队列
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
