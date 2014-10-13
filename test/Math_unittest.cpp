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
using namespace CVA::Math;

TEST(Math, GetSAD)
{
    const int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const int b[] = {1, 2, 4, 4, 5, 5, 7, 9};

    EXPECT_EQ(getSAD(a, b, sizeof(a) / sizeof(int)), 3);
}

TEST(Math, GetSSD)
{
    const int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const int b[] = {1, 2, 3, 5, 5, 7, 7, 10};

    EXPECT_EQ(getSSD(a, b, sizeof(a) / sizeof(int)), 6);
}
