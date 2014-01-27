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

#ifndef __CVA_CROPPING_H__
#define __CVA_CROPPING_H__

namespace CVA {

namespace Cropping {

template<typename T>
void cropRectangle(const ImagePlane<T>& src, ImagePlane<T>& dest, const Point& start, const Point& end)
{
    const std::size_t minPointValueX = std::min(start.getX(), end.getX());
    const std::size_t maxPointValueX = std::max(start.getX(), end.getX());
    const std::size_t minPointValueY = std::min(start.getY(), end.getY());
    const std::size_t maxPointValueY = std::max(start.getY(), end.getY());

    assert(dest.width() >= (maxPointValueX - minPointValueX) &&
        dest.height() >= (maxPointValueY - minPointValueY));

    for (std::size_t x = minPointValueX; x < maxPointValueX; x++)
    {
        for (std::size_t y = minPointValueY; y < maxPointValueY; y++)
        {
            dest.setPixel(x - minPointValueX, y - minPointValueY, src.getPixel(x, y));
        }
    }
}

};

};

#endif
