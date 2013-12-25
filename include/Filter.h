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

#ifndef __CVA_FILTER_H__
#define __CVA_FILTER_H__

#include "Matrix3x3.h"

namespace CVA {

template<typename T>
T applyMatrixFilter3x3(const Matrix3x3<T>& matrix, const Matrix3x3<T>& convolution, int div = 1, T offset = 0)
{
    assert(div);

    const T tmp = matrix.get(0, 0) * convolution.get(0, 0) +
        matrix.get(0, 1) * convolution.get(0, 1) +
        matrix.get(0, 2) * convolution.get(0, 2) +
        matrix.get(1, 0) * convolution.get(1, 0) +
        matrix.get(1, 1) * convolution.get(1, 1) +
        matrix.get(1, 2) * convolution.get(1, 2) +
        matrix.get(2, 0) * convolution.get(2, 0) +
        matrix.get(2, 1) * convolution.get(2, 1) +
        matrix.get(2, 2) * convolution.get(2, 2);

    return tmp * 1.0 / div + offset;
}

};

#endif
