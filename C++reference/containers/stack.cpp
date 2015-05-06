/*
堆栈stack是容器适配器，它是以序列容器为底层实现。stack支持后入先出(LIFO)，数据的插入和删除都
是在堆栈的顶部进行的，不能够访问堆栈内部的数据。stack不支持迭代器。

template <class T, class Container = deque<T> > class stack;

stack::emplace
stack::empty  测试堆栈容器适配器类型是否为空
stack::pop    弹出堆栈容器适配器栈顶的数据
stack::push   将数据压入堆栈容器适配器
stack::size   返回堆栈容器适配器中的数据个数
stack::swap   
stack::top    访问堆栈容器适配器栈顶数据

bool empty() const;
void pop();
void push (const value_type& val);
void push (value_type&& val);
size_type size() const;
void swap (stack& x)
      reference& top();
const_reference& top() const;
*/

#include <iostream>       // std::cin, std::cout
#include <stack>          // std::stack
#include <string>         // std::string, std::getline(string)
#include <vector>         // std::vector
#include <deque>          // std::deque

//using namespace std; 

int main ()
{
	//实例化一个堆栈类
	std::stack<std::string> mystack;

	//将数据压入堆栈容器适配器
	mystack.push ("First sentence");
	mystack.push ("Second sentence");

	//返回堆栈容器适配器中的数据个数
	std::cout << "stack size: " << mystack.size() << '\n';

	std::cout << "mystack contains:\n";

	//测试堆栈容器适配器类型是否为空
	while (!mystack.empty())
	{

		//访问堆栈容器适配器栈顶数据
		std::cout << mystack.top() << '\n';
		//弹出堆栈容器适配器栈顶的数据
		mystack.pop();
	}

	//堆栈是容器适配器，它是以序列容器为底层实现.标准的容器类模板vector, deque 和list可以使用，默认情况下，
	//如果没有容器类被指定成为一个特别的stack 类，标准的容器类模板就是deque 队列
	std::deque<int> mydeque (3,100);          // deque with 3 elements {100, 100, 100}
	std::vector<int> myvector (2,200);        // vector with 2 elements {200, 200}

	std::stack<int> first;                    // empty stack
	std::stack<int> second (mydeque);         // stack initialized to copy of deque

	std::stack<int,std::vector<int> > third;  // empty stack using vector
	std::stack<int,std::vector<int> > fourth (myvector);

	/*
	(gdb) print first
	$2 = std::stack wrapping: std::deque with 0 elements
	(gdb) print second
	$3 = std::stack wrapping: std::deque with 3 elements = {100, 100, 100}
	(gdb) print third
	$4 = std::stack wrapping: std::vector of length 0, capacity 0
	(gdb) print fourth
	$5 = std::stack wrapping: std::vector of length 2, capacity 2 = {200, 200}
	*/

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';
	std::cout << "The top of fourth: " << fourth.top() << '\n';

	return 0;
}
/*
output:
stack size: 2
mystack contains:
Second sentence
First sentence
size of first: 0
size of second: 3
size of third: 0
size of fourth: 2
size of fourth: 200
*/