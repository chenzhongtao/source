#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
  	// typedef Mat <double> mat;
	mat A = randu<mat>(5,5);

	cout << A.n_rows  << endl ;
	cout << A.n_cols  << endl ;
	cout << A.n_elem  << endl ;
	// 下标从零开始
	double x = A(1,1);

	// 所有元素为0
	mat a(4,5, fill::zeros);
	//cout << a << endl;
	
	// 所有元素为1
	mat b(4,4, fill::ones);
	cout << b << endl;

	// 主对角元素为1，其他为0
	mat c(5,4, fill::eye);
	cout << c << endl;
	/*
	 1.0000      0        0        0
        0   1.0000        0        0
        0        0   1.0000        0
        0        0        0   1.0000
        0        0        0        0
	*/

	//数据在0 1 均匀分布
	mat d(4,4, fill::randu);
	cout << d << endl;

	//数据符合标准正态分布
	mat e(4,4, fill::randn);
	cout << e << endl;

	//不赋初值，为内存的随机数
	mat f(4,4, fill::none);
	cout << f << endl;

	//使用辅助内存
	double aux_mem[24];
	mat g(&aux_mem[0], 4, 6, false, true);  // use auxiliary memory
	cout << g << endl;

	// 内存中是按列存储的
	f.reshape(2, 2);
	cout << f << endl;

	f.reshape(30, 40);
	//cout << f << endl;

	//使用固定大小内存分配，效率高，不能reshape
	//内存在栈中分配，大小受到限制
	mat::fixed<30,40> h;

	mat i(5,5);
	// 所有元素赋值为125
	i.fill(123.0);
	cout << i << endl;

	// 有符号的整形矩阵
	imat j(4,4, fill::randn);
	cout << j << endl;
	
	mat B = A + A;
	mat C = A * B;
	mat D = A % B;

	cx_mat X(A,B);

	B.zeros();
	B.set_size(10,10);
	B.ones(5,6);

	//cout << A << endl ;
	// A的转置
	//cout << A.t() << endl ;
	
	//B.print("B:");

	mat E(4,5, fill::zeros);

	

  }