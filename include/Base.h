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

#ifndef __CVA_BASE_H__
#define __CVA_BASE_H__

#include <map>

#include "Image.h"

namespace CVA {

template<typename T>
void getPixelStat(const ImagePlane<T>& plane, T& minPixelValue, T& maxPixelValue, float& averagePixelValue)
{
    minPixelValue = maxPixelValue = plane[0];
    averagePixelValue = 0.0;

    for (std::size_t i = 0; i < plane.pixels(); i++)
    {
        const T pixel = plane[i];

        minPixelValue = std::min(minPixelValue, pixel);
        maxPixelValue = std::max(maxPixelValue, pixel);

        averagePixelValue += pixel;
    }

    averagePixelValue /= plane.pixels();
}

template<typename T>
std::map<T, std::size_t> getHistogramm(const ImagePlane<T>& plane)
{
    std::map<T, std::size_t> histogramm;

    for (std::size_t i = 0; i < plane.pixels(); i++)
    {
        const T pixel = plane[i];

        typename std::map<T, std::size_t>::iterator it = histogramm.find(pixel);
        if (it == histogramm.end())
        {
            histogramm.insert(std::pair<T, std::size_t>(pixel, 1));
        }
        else
        {
            it->second++;
        }
    }

    return histogramm;
}

template<typename T>
Matrix3x3<T> getMatrix3x3(const ImagePlane<T>& plane, size_t x, size_t y)
{
    const Matrix3x3<T> matrix(
        plane.getPixel(x - 1, y - 1), plane.getPixel(x, y - 1), plane.getPixel(x + 1, y - 1),
        plane.getPixel(x - 1, y),     plane.getPixel(x, y),     plane.getPixel(x + 1, y),
        plane.getPixel(x - 1, y + 1), plane.getPixel(x, y + 1), plane.getPixel(x + 1, y + 1)
    );

    return matrix;
}

};

#endif
