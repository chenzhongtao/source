/*
��ջstack����������������������������Ϊ�ײ�ʵ�֡�stack֧�ֺ����ȳ�(LIFO)�����ݵĲ����ɾ����
���ڶ�ջ�Ķ������еģ����ܹ����ʶ�ջ�ڲ������ݡ�stack��֧�ֵ�������

template <class T, class Container = deque<T> > class stack;

stack::emplace
stack::empty  ���Զ�ջ���������������Ƿ�Ϊ��
stack::pop    ������ջ����������ջ��������
stack::push   ������ѹ���ջ����������
stack::size   ���ض�ջ�����������е����ݸ���
stack::swap   
stack::top    ���ʶ�ջ����������ջ������

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
	//ʵ����һ����ջ��
	std::stack<std::string> mystack;

	//������ѹ���ջ����������
	mystack.push ("First sentence");
	mystack.push ("Second sentence");

	//���ض�ջ�����������е����ݸ���
	std::cout << "stack size: " << mystack.size() << '\n';

	std::cout << "mystack contains:\n";

	//���Զ�ջ���������������Ƿ�Ϊ��
	while (!mystack.empty())
	{

		//���ʶ�ջ����������ջ������
		std::cout << mystack.top() << '\n';
		//������ջ����������ջ��������
		mystack.pop();
	}

	//��ջ����������������������������Ϊ�ײ�ʵ��.��׼��������ģ��vector, deque ��list����ʹ�ã�Ĭ������£�
	//���û�������౻ָ����Ϊһ���ر��stack �࣬��׼��������ģ�����deque ����
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