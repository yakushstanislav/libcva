/*
   Copyright (c) 2014 Stanislav Yakush (st.yakush@yandex.ru)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include <gtest/gtest.h>
#include <cva/cva.h>

using namespace CVA;

TEST(Matrix3x3, Initialization)
{
    const Matrix3x3<unsigned char> matrix(10, 20, 30, 40, 50, 60, 70, 80, 90);

    EXPECT_EQ(matrix[0], 10);
    EXPECT_EQ(matrix[1], 20);
    EXPECT_EQ(matrix[2], 30);
    EXPECT_EQ(matrix[3], 40);
    EXPECT_EQ(matrix[4], 50);
    EXPECT_EQ(matrix[5], 60);
    EXPECT_EQ(matrix[6], 70);
    EXPECT_EQ(matrix[7], 80);
    EXPECT_EQ(matrix[8], 90);
}

TEST(Matrix3x3, SetValue)
{
    Matrix3x3<int> matrix;

    matrix.set(0, 0, 10);
    matrix.set(0, 1, 15);
    matrix.set(1, 0, 20);
    matrix.set(1, 1, 30);
    matrix.set(2, 0, 35);
    matrix.set(2, 2, 40);

    EXPECT_EQ(matrix.get(0, 0), 10);
    EXPECT_EQ(matrix.get(0, 1), 15);
    EXPECT_EQ(matrix.get(0, 2), 0);
    EXPECT_EQ(matrix.get(1, 0), 20);
    EXPECT_EQ(matrix.get(1, 1), 30);
    EXPECT_EQ(matrix.get(1, 2), 0);
    EXPECT_EQ(matrix.get(2, 0), 35);
    EXPECT_EQ(matrix.get(2, 1), 0);
    EXPECT_EQ(matrix.get(2, 2), 40);
}

TEST(Matrix3x3, Transponse)
{
    Matrix3x3<int> matrix(1, 2, 3, 4, 5, 6, 7, 8, 9);
    const Matrix3x3<int> matrixTransposed(1, 4, 7, 2, 5, 8, 3, 6, 9);

    EXPECT_FALSE(matrix == matrixTransposed);

    matrix = matrix.transpose();

    EXPECT_TRUE(matrix == matrixTransposed);
}

TEST(Matrix3x3, Sort)
{
    const Matrix3x3<int> matrix1(1, 10, 2, 20, 15, 30, 5, 100, 50);
    const Matrix3x3<double> matrix2(1.0, 10.5, -0.5, 100.0, 0.0, 7.0, 15.0, 8.0, 30.0);
    const Matrix3x3<int> result1(1, 2, 5, 10, 15, 20, 30, 50, 100);
    const Matrix3x3<double> result2(-0.5, 0.0, 1.0, 7.0, 8.0, 10.5, 15.0, 30.0, 100.0);

    EXPECT_TRUE(matrix1.sort() == result1);
    EXPECT_TRUE(matrix2.sort() == result2);
}

TEST(Matrix3x3, Sum)
{
    const Matrix3x3<int> matrix1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    const Matrix3x3<double> matrix2(10.08, 11.10, 24.5, 24.0, 30.70, 50.50, 70.90, 80.05, 100.70);

    EXPECT_EQ(matrix1.sum(), 45);
    EXPECT_EQ(matrix2.sum(), 402.53);
}

TEST(Matrix3x3, Rows)
{
    const Matrix3x3<int> matrix(1, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_EQ(matrix.rows(), 3);
}

TEST(Matrix3x3, Columns)
{
    const Matrix3x3<int> matrix(1, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_EQ(matrix.columns(), 3);
}

TEST(Matrix3x3, Dimension)
{
    const Matrix3x3<int> matrix(1, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_EQ(matrix.dimension(), 9);
}

TEST(Matrix3x3, Compare)
{
    const Matrix3x3<int> matrix1(100, 200, 300, 400, 500, 600, 700, 800, 900);
    Matrix3x3<int> matrix2 = matrix1;

    EXPECT_TRUE(matrix1 == matrix2);

    matrix2.set(0, 0, matrix1.get(0, 0) + 1);

    EXPECT_FALSE(matrix1 == matrix2);
}

TEST(Matrix3x3, SumMatrix)
{
    const Matrix3x3<int> matrix1(100, 200, 300, 400, 500, 600, 700, 800, 900);
    const Matrix3x3<int> matrix2(900, 800, 700, 600, 500, 400, 300, 200, 100);
    const Matrix3x3<int> result(1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000);

    EXPECT_TRUE((matrix1 + matrix2) == result);
}

TEST(Matrix3x3, SubMatrix)
{
    const Matrix3x3<int> matrix1(900, 800, 700, 600, 500, 400, 300, 200, 100);
    const Matrix3x3<int> matrix2(100, 200, 300, 400, 500, 600, 700, 800, 900);
    const Matrix3x3<int> result(800, 600, 400, 200, 0, -200, -400, -600, -800);

    EXPECT_TRUE((matrix1 - matrix2) == result);
}

TEST(Matrix3x3, MulMatrix)
{
    const Matrix3x3<int> matrix1(0, 1, 2, 3, 4, 5, 6, 7, 8);
    const Matrix3x3<int> matrix2(9, 10, 11, 12, 13, 14, 15, 16, 17);
    const Matrix3x3<int> result(42, 45, 48, 150, 162, 174, 258, 279, 300);

    EXPECT_TRUE((matrix1 * matrix2) == result);
}

TEST(Matrix3x3, AddValue)
{
    const Matrix3x3<int> matrix(10, 20, 30, 40, 50, 60, 70, 80, 90);
    const Matrix3x3<int> result(20, 30, 40, 50, 60, 70, 80, 90, 100);

    EXPECT_TRUE((matrix + 10) == result);
}

TEST(Matrix3x3, SubValue)
{
    const Matrix3x3<int> matrix(20, 30, 40, 50, 60, 70, 80, 90, 100);
    const Matrix3x3<int> result(10, 20, 30, 40, 50, 60, 70, 80, 90);

    EXPECT_TRUE((matrix - 10) == result);
}

TEST(Matrix3x3, MulValue)
{
    const Matrix3x3<int> matrix(10, 20, 30, 40, 50, 60, 70, 80, 90);
    const Matrix3x3<int> result(100, 200, 300, 400, 500, 600, 700, 800, 900);

    EXPECT_TRUE((matrix * 10) == result);
}

TEST(Matrix3x3, DivValue)
{
    const Matrix3x3<int> matrix(100, 200, 300, 400, 500, 600, 700, 800, 900);
    const Matrix3x3<int> result(10, 20, 30, 40, 50, 60, 70, 80, 90);

    EXPECT_TRUE((matrix / 10) == result);
}
