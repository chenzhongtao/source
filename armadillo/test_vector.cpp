#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {

	// �����ĳ�ʼ�������������
	
	// ������ vec = clovec
	vec a(10);
	vec b = zeros<vec>(10);

	mat c = randu<mat>(10,10);
	
	//��ȡ����ĵ�����
	vec d = c.col(5); // extract a column vector
	cout << c << endl;
	cout << d << endl;

	//����������ȡ����ĵ�����
	rowvec e = c.row(5); // extract a row vector
	cout << e << endl;
	

	

  }