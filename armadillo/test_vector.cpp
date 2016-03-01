#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {

	// 向量的初始化跟矩阵很相似
	
	// 列向量 vec = clovec
	vec a(10);
	vec b = zeros<vec>(10);

	mat c = randu<mat>(10,10);
	
	//提取矩阵的第五列
	vec d = c.col(5); // extract a column vector
	cout << c << endl;
	cout << d << endl;

	//行向量，提取矩阵的第五行
	rowvec e = c.row(5); // extract a row vector
	cout << e << endl;
	

	

  }