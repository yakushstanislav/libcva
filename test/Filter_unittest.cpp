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
using namespace CVA::Filter;

TEST(Filter, MatrixFilter3x3)
{
    const Matrix3x3<int> matrix1(110, 120, 130, 210, 220, 230, 310, 320, 330);
    const Matrix3x3<double> matrix2(12, 14, 41, 43, 84, 24, 2, 1, 43);
    const Matrix3x3<int> convolution1(0, 1, 0, 0, 0, 0, 0, 0, 0);
    const Matrix3x3<double> convolution2(0.5, 0.75, 0.5, 0.75, 1.0, 0.75, 0.5, 0.75, 0.5);

    EXPECT_EQ(applyMatrixFilter3x3(matrix1, convolution1), 120);
    EXPECT_EQ(applyMatrixFilter3x3(matrix2, convolution2, 6), 32.416666666666664);
}

TEST(Filter, MedianFilter3x3)
{
    const Matrix3x3<int> matrix(10, 50, 200, 150, 70, 30, 20, 15, 80);

    EXPECT_EQ(applyMedianFilter3x3(matrix), 50);
}
