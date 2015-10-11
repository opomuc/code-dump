#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <Eigen/Sparse>
#include <Eigen/Eigenvalues>

using namespace Eigen;
using namespace std;

int main(int argc, char** argv)
{
  clock_t begin = clock();

  ifstream input;
  ofstream output("output.txt");
  double param = 0.1; // parameter in iterative method
  if (argc == 1)
  {
    cout << "Please provide input file. Usage: <program> <filename>" << endl;
    cout << "Optional: -p <parameter value>" << endl;
    exit(-2);
  }
  if (argc > 1)
  {
    if (argv[1] != "-p")
    {
      try
      {
        input.open(argv[1]);
      }
      catch(...)
      {
        cout << "## ERROR: Incorrect input filename" << endl;
        exit(-1);
      }
      if (argv[2] != "-p") 
      {
        param = strtod(argv[3], NULL);
      }
    }
    else
    {
      cout << "Please provide input file. Usage: <program> <filename>" << endl;
      cout << "Optional: -p <parameter value>" << endl;
      exit(-1);
    }
  }

  double epsilon = 0;
  int matrix_size = 0;

  // get precision and matrix size
  input >> epsilon;
  input >> matrix_size;
  //cout << epsilon << endl;
  //cout << matrix_size << endl;

  // declare all necessary matrices & vectors
  MatrixXd A_Matrix(matrix_size, matrix_size);
  MatrixXd U_Matrix(matrix_size, matrix_size);
  MatrixXd L_Matrix(matrix_size, matrix_size);
  MatrixXd D_Matrix(matrix_size, matrix_size);
  MatrixXd M_Matrix(matrix_size, matrix_size);
  MatrixXd F_Matrix(matrix_size, matrix_size);
  MatrixXd G_Matrix(matrix_size, matrix_size);
  VectorXd Value_vector(matrix_size);
  VectorXd Init_vector(matrix_size);
  VectorXd Result_vector(matrix_size);
  VectorXd g_vector(matrix_size);
  // set zero approximation to zero vector
  Init_vector.setZero();

  // input free values
  for (int i = 0; i < matrix_size; i++)
  {
    if (input.eof())
    {
      cout << "## ERROR: Not enough data for vector. please provide " << matrix_size << " values!" << endl;
      input.close();
      output.close();
      exit(-1);
    }
    input >> Value_vector(i);
  }
  // input Matrix_A from file
  for (int i = 0; i < matrix_size; i++)
  {
    for (int j = 0; j < matrix_size; j++)
    {
      if (input.eof())
      {
        cout << "## ERROR: Not enough data for matrix. please provide " << matrix_size * matrix_size << " values!" << endl;
        input.close();
        output.close();
        exit(-1);
      }
      input >> A_Matrix(i, j);
    }
  }

  // we need symmetrical matrix, so we make it that way
  A_Matrix = A_Matrix * A_Matrix.transpose();
  Value_vector = A_Matrix.transpose() * Value_vector;
  // calculating matrices derived from A
  U_Matrix = A_Matrix.triangularView<StrictlyUpper>();
  L_Matrix = A_Matrix.triangularView<StrictlyLower>();
  D_Matrix = A_Matrix.diagonal().asDiagonal();
  M_Matrix = L_Matrix + (D_Matrix / (1 + param));
  F_Matrix = U_Matrix + param / (1 + param) * D_Matrix;
  M_Matrix = M_Matrix.inverse();
  G_Matrix = - M_Matrix * F_Matrix;
  g_vector = M_Matrix * Value_vector;

  /*// estimating number of iterations
  SelfAdjointEigenSolver<MatrixXd> es(G_Matrix);
  double q = es.eigenvalues().maxCoeff();
  cout << q << endl;
  int estimate = 0;
  estimate = ceil(log((epsilon * (1-q))/g_vector.norm()) / log(q));
  cout << "Estimated number of iterations: " << estimate << endl;
  */
  // calculating result using iterative method
  cout << "Parameter: p = " << param << endl; 
  cout << "Calculating..." << endl;
  int N = 0;
  for (N = 0; ; N++)
  {
    Result_vector = M_Matrix * (Value_vector - F_Matrix * Init_vector);
    if ((Result_vector - Init_vector).norm() <= epsilon) break;
    Init_vector = Result_vector;
  }
  // saving the solution
  output << Result_vector;
  
  output.close();
  input.close();
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "The method has taken: " << elapsed_secs << " seconds" << endl;
  cout << "There was " << N + 1 << " iterations" << endl; 
  return 0;
}
