// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  // Capture our output
  ostringstream s;
  Image_print(img, s);
  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.
TEST(test_print_small) {
  Image *img = new Image; // create an Image in dynamic memory
  const Pixel red = {255, 0, 0};
  Image_init(img, 1, 1);
  Image_set_pixel(img, 0, 0, red);
  // Capture our output
  ostringstream s;
  Image_print(img, s);
  // Correct output
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "255 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete img; // delete the Image
}

TEST(test_init_basic) {
  Image *img = new Image;
  string read_in = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  istringstream input(read_in); 
  Image_init(img, input);
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete img;
}

TEST(test_init_small) {
  Image *img = new Image;
  string read_in = "P3\n1 1\n255\n0 0 0 \n";
  istringstream input(read_in); 
  Image_init(img, input);
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete img;
}

TEST(test_width_height_basic) {
    Image *img = new Image;
    Image_init(img, 1, 2);
    assert(Image_width(img) == 1);
    assert(Image_height(img) == 2);
    delete img;
}

TEST(set_pixel_basic) {
  Image *img = new Image;
  Image *correct_img = new Image;
  string read_in = "P3\n2 2\n255\n255 0 0 0 255 0\n0 0 255 255 255 255";
  istringstream input(read_in);
  Image_init(correct_img, input);
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  assert(Image_equal(img, correct_img));
  delete img;
  delete correct_img;
}

TEST(get_pixel_basic) {
  Image *img = new Image;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  assert(Pixel_equal(Image_get_pixel(img, 0, 0), red));
  assert(Pixel_equal(Image_get_pixel(img, 0, 1), green));
  assert(Pixel_equal(Image_get_pixel(img, 1, 0), blue));
  assert(Pixel_equal(Image_get_pixel(img, 1, 1), white));
  delete img;
}

TEST(test_fill_basic) {
    Image *img = new Image;
    Image *correct_img = new Image;
    const Pixel black = {0, 0, 0};
    Image_init(img, 2, 2);
    Image_fill(img, black);
    Image_init(correct_img, 2, 2);
    Image_set_pixel(correct_img, 0, 0, black);
    Image_set_pixel(correct_img, 0, 1, black);
    Image_set_pixel(correct_img, 1, 0, black);
    Image_set_pixel(correct_img, 1, 1, black);
    assert(Image_equal(img, correct_img));
    delete img;
    delete correct_img;
}

TEST(test_fill_small) {
    Image *img = new Image;
    Image *correct_img = new Image;
    const Pixel white = {255, 255, 255};
    Image_init(img, 1, 1);
    Image_fill(img, white);
    Image_init(correct_img, 1, 1);
    Image_set_pixel(correct_img, 0, 0, white);
    assert(Image_equal(img, correct_img));
    delete img;
    delete correct_img;
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon herex

