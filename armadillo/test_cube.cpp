#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
	//三维矩阵 3D matrices
  	cube x(1,2,3);
	cube y = randu<cube>(4,5,6);
	cout << y << endl;

	mat A = y.slice(1);  // extract a slice from the cube
	                     // (each slice is a matrix)
	cout << A << endl;

	mat B = randu<mat>(4,5);
	y.slice(2) = B;     // set a slice in the cube

	cube q = y + y;     // cube addition
	// 对应元素相乘
	cube r = y % y;     // element-wise cube multiplication

	cube::fixed<4,5,6> f;
	// 所有元素都为1
	f.ones();
	cout << f << endl;

  }