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
	// �±���㿪ʼ
	double x = A(1,1);

	// ����Ԫ��Ϊ0
	mat a(4,5, fill::zeros);
	//cout << a << endl;
	
	// ����Ԫ��Ϊ1
	mat b(4,4, fill::ones);
	cout << b << endl;

	// ���Խ�Ԫ��Ϊ1������Ϊ0
	mat c(5,4, fill::eye);
	cout << c << endl;
	/*
	 1.0000      0        0        0
        0   1.0000        0        0
        0        0   1.0000        0
        0        0        0   1.0000
        0        0        0        0
	*/

	//������0 1 ���ȷֲ�
	mat d(4,4, fill::randu);
	cout << d << endl;

	//���ݷ��ϱ�׼��̬�ֲ�
	mat e(4,4, fill::randn);
	cout << e << endl;

	//������ֵ��Ϊ�ڴ�������
	mat f(4,4, fill::none);
	cout << f << endl;

	//ʹ�ø����ڴ�
	double aux_mem[24];
	mat g(&aux_mem[0], 4, 6, false, true);  // use auxiliary memory
	cout << g << endl;

	// �ڴ����ǰ��д洢��
	f.reshape(2, 2);
	cout << f << endl;

	f.reshape(30, 40);
	//cout << f << endl;

	//ʹ�ù̶���С�ڴ���䣬Ч�ʸߣ�����reshape
	//�ڴ���ջ�з��䣬��С�ܵ�����
	mat::fixed<30,40> h;

	mat i(5,5);
	// ����Ԫ�ظ�ֵΪ125
	i.fill(123.0);
	cout << i << endl;

	// �з��ŵ����ξ���
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
	// A��ת��
	//cout << A.t() << endl ;
	
	//B.print("B:");

	mat E(4,5, fill::zeros);

	

  }