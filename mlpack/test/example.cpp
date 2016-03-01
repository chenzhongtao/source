// Includes all relevant components of MLPACK.
#include <mlpack/core.hpp>

// Convenience.
using namespace mlpack;
using namespace std;
using namespace arma;

int main()
{
  // First, load the data.
  arma::mat data1;
  // Use data::Load() which transposes the matrix.
  // mlpack 自己的方法是按列存储
  data::Load("data.csv", data1, true);
  
  cout <<"n_rows: " << data1.n_rows <<" n_cols: " << data1.n_cols << endl;

  // Now compute the covariance.  We assume that the data is already centered.
  // Remember, because the matrix is column-major, the covariance operation is
  // transposed.
   arma::mat cov = data1 * trans(data1) / data1.n_cols;

  // Save the output.
  data::Save("cov.csv", cov, true);
  
  mat A = randu<mat>(2,5);
  // arma 是按行存储
  A.save("A.csv", csv_ascii);
  mat B;
  B.load("data.csv", csv_ascii);
  cout <<"n_rows: " << B.n_rows <<" n_cols: " << B.n_cols << endl;
}