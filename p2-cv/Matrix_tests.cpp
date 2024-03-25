// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(test_init_basic) {
  Matrix *mat = new Matrix; // create an Image in dynamic memory
    const int width = 4;
    const int height = 5;
    Matrix_init(mat,width, height);
    ASSERT_EQUAL(mat->height, 5);
    ASSERT_EQUAL(mat->width, 4);
}
    
TEST(test_print_basic) {
  Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 2);
  // Capture our output
  ostringstream s;
    *Matrix_at(mat, 0, 0) = 42;
    *Matrix_at(mat, 0, 1) = 41;
    *Matrix_at(mat, 1, 0) = 40;
    *Matrix_at(mat, 1, 1) = 39;
    Matrix_print(mat, s);
  // Correct output
  ostringstream correct;
  correct << "2 2\n";
  correct << "42 41 \n";
  correct << "40 39 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete mat; // delete the Image
}

TEST(test_width_basic) {
  Matrix *mat = new Matrix;
    const int width = 7;
    const int height = 2;
    Matrix_init(mat,width, height);
    Matrix_width(mat);
    //ASSERT_EQUAL(mat->height, 5);
    ASSERT_EQUAL(mat->width, 7);
    delete mat;
}

TEST(test_height_basic) {
  Matrix *mat = new Matrix;
    const int width = 7;
    const int height = 2;
    Matrix_init(mat,width, height);
    Matrix_width(mat);
    ASSERT_EQUAL(mat->height, 2);
    delete mat;
}

TEST(test_row_basic) {
  Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 2);
    *Matrix_at(mat, 0, 0) = 5;
    *Matrix_at(mat, 0, 1) = 4;
    *Matrix_at(mat, 1, 0) = 0;
    *Matrix_at(mat, 1, 1) = 39;
    ASSERT_EQUAL(Matrix_row(mat, Matrix_at(mat, 1, 1)), 1);
    ASSERT_EQUAL(Matrix_row(mat, Matrix_at(mat, 1, 0)), 1);
    delete mat;
}
TEST(test_col_basic) {
  Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 2);
    *Matrix_at(mat, 0, 0) = 5;
    *Matrix_at(mat, 0, 1) = 4;
    *Matrix_at(mat, 1, 0) = 0;
    *Matrix_at(mat, 1, 1) = 39;
    ASSERT_EQUAL(Matrix_column(mat, Matrix_at(mat, 0, 1)), 1);
    ASSERT_EQUAL(Matrix_column(mat, Matrix_at(mat, 1, 0)), 0);
    delete mat;
}

TEST(test_at1_basic) {
  Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 2);
    *Matrix_at(mat, 0, 0) = 5;
    *Matrix_at(mat, 0, 1) = 4;
    *Matrix_at(mat, 1, 0) = 0;
    *Matrix_at(mat, 1, 1) = 39;
    ASSERT_EQUAL(Matrix_at(mat, 1, 0), mat->data + 2);
    delete mat;
}

//how to do at2 test??????

TEST(test_border_basic) {
  Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 2);
    Matrix_fill_border(mat, 1000);
    
    Matrix *mat1 = new Matrix;
      Matrix_init(mat1, 2, 2);
      *Matrix_at(mat1, 0, 0) = 1000;
      *Matrix_at(mat1, 0, 1) = 1000;
      *Matrix_at(mat1, 1, 0) = 1000;
      *Matrix_at(mat1, 1, 1) = 1000;
      Matrix_fill(mat1, 1000);
    ASSERT_EQUAL(*mat->data, *mat1->data);
    ASSERT_EQUAL(*mat->data + 1, *mat1->data + 1);
    ASSERT_EQUAL(*mat->data + 2, *mat1->data + 2);
    ASSERT_EQUAL(*mat->data + 3, *mat1->data + 3);
    delete mat;
    delete mat1;
}

TEST(test_max_basic) {
  Matrix *mat = new Matrix;
    Matrix_init(mat, 1, 1);
    *Matrix_at(mat, 0, 0) = 38;
    ASSERT_EQUAL(Matrix_max(mat), 38);
    delete mat;
    
    Matrix *mat1 = new Matrix;
      Matrix_init(mat1, 4, 2);
    Matrix_fill(mat1, 3);
    Matrix_fill_border(mat1, 10);
      ASSERT_EQUAL(Matrix_max(mat), 10);
      delete mat1;
    
    Matrix *mat2 = new Matrix;
      Matrix_init(mat2, 2, 2);
      *Matrix_at(mat2, 0, 0) = -3;
      *Matrix_at(mat2, 0, 1) = -8;
      *Matrix_at(mat2, 1, 0) = -100;
      *Matrix_at(mat2, 1, 1) = -1;
      ASSERT_EQUAL(Matrix_max(mat), -1);
      delete mat2;
}

TEST(test_min_col_basic) {
  Matrix *mat = new Matrix;
    Matrix_init(mat, 5, 3);
    *Matrix_at(mat, 0, 0) = 1;
    *Matrix_at(mat, 0, 1) = 3;
    *Matrix_at(mat, 0, 2) = 7;
    *Matrix_at(mat, 0, 3) = 1;
    *Matrix_at(mat, 0, 4) = 3;
    *Matrix_at(mat, 1, 0) = 4;
    *Matrix_at(mat, 1, 1) = 0;
    *Matrix_at(mat, 1, 2) = 13;
    *Matrix_at(mat, 1, 3) = 4;
    *Matrix_at(mat, 1, 4) = 3;
    *Matrix_at(mat, 2, 0) = -6;
    *Matrix_at(mat, 2, 1) = 2;
    *Matrix_at(mat, 2, 2) = 10;
    *Matrix_at(mat, 2, 3) = 0;
    *Matrix_at(mat, 2, 4) = 1;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 1, 4), 3);
    delete mat;
}

TEST(test_min_basic) {
  Matrix *mat = new Matrix;
    Matrix_init(mat, 5, 3);
    *Matrix_at(mat, 0, 0) = 1;
    *Matrix_at(mat, 0, 1) = 3;
    *Matrix_at(mat, 0, 2) = 7;
    *Matrix_at(mat, 0, 3) = 1;
    *Matrix_at(mat, 0, 4) = 3;
    *Matrix_at(mat, 1, 0) = 4;
    *Matrix_at(mat, 1, 1) = 0;
    *Matrix_at(mat, 1, 2) = 13;
    *Matrix_at(mat, 1, 3) = 4;
    *Matrix_at(mat, 1, 4) = 3;
    *Matrix_at(mat, 2, 0) = -6;
    *Matrix_at(mat, 2, 1) = 2;
    *Matrix_at(mat, 2, 2) = 10;
    *Matrix_at(mat, 2, 3) = 1;
    *Matrix_at(mat, 2, 4) = 0;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 4, 4), 3);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 4), 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 2, 4), 1);
    delete mat;
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
