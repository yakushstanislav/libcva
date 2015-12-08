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

namespace CVA {

namespace Filter {

template<typename T>
T applyMatrixFilter3x3(const Matrix3x3<T>& matrix, const Matrix3x3<T>& convolution,
    const int div = 1, const T offset = 0)
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

template<typename T>
void applyMatrixFilter3x3(const ImagePlane<T>& src, ImagePlane<T>& dest, const Matrix3x3<T>& convolution,
    const int div = 1, const T offset = 0)
{
    assert(src.width() == dest.width() && src.height() == dest.height());

    for (std::size_t y = 1; y < src.height() - 1; y++)
    {
        for (std::size_t x = 1; x < src.width() - 1; x++)
        {
            const Matrix3x3<T>& matrix = Base::getMatrix3x3(src, x, y);
            const T pixel = applyMatrixFilter3x3(matrix, convolution, div, offset);

            dest.setPixel(x, y, pixel);
        }
    }
}

template<typename T>
inline T applyMedianFilter3x3(const Matrix3x3<T>& matrix)
{
    return matrix.sort()[4];
}

template<typename T>
void applyMedianFilter3x3(const ImagePlane<T>& src, ImagePlane<T>& dest)
{
    assert(src.width() == dest.width() && src.height() == dest.height());

    for (std::size_t y = 1; y < src.height() - 1; y++)
    {
        for (std::size_t x = 1; x < src.width() - 1; x++)
        {
            const Matrix3x3<T>& matrix = Base::getMatrix3x3(src, x, y);

            dest.setPixel(x, y, applyMedianFilter3x3(matrix));
        }
    }
}

};

};

#endif
