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

#ifndef __CVA_SCALING_H__
#define __CVA_SCALING_H__

namespace CVA {

namespace Scaling {

template<typename T>
void bilinearScale(const ImagePlane<T>& src, ImagePlane<T>& dest)
{
    const float ratioX = (float)(src.width() - 1) / (float)dest.width();
    const float ratioY = (float)(src.height() - 1) / (float)dest.height();
    std::size_t offset = 0;

    for (std::size_t h = 0; h < dest.height(); h++)
    {
        for (std::size_t w = 0; w < dest.width(); w++)
        {
            const std::size_t x = ratioX * w;
            const std::size_t y = ratioY * h;
            const float diffX = (ratioX * w) - x;
            const float diffY = (ratioY * h) - y;
            const std::size_t index = y * src.width() + x;

            const T a = src[index] & 0xFF;
            const T b = src[index + 1] & 0xFF;
            const T c = src[index + src.width()] & 0xFF;
            const T d = src[index + src.width() + 1] & 0xFF;

            const T pixel = (a * (1 - diffX) * (1 - diffY)) + (b * diffX * (1 - diffY)) +
                (c * diffY * (1 - diffX)) + (d * diffX * diffY);

            dest.setPixel(offset++, pixel);
        }
    }
}

};

};

#endif
