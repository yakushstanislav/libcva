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

#include <algorithm>
#include <gtest/gtest.h>
#include <cva/cva.h>

#include "LenaGray8.h"

using namespace CVA;
using namespace CVA::Base;

TEST(Base, GetHistogram)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, false);

    const Histogram& planeHistogram = getHistogram(plane);

    EXPECT_EQ(planeHistogram[49], 1); // Min pixel value
    EXPECT_EQ(planeHistogram[255], 375); // Max pixel value
}

TEST(Base, GetPixelStatFromHistoram)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, false);

    const Histogram& planeHistogram = getHistogram(plane);

    unsigned char minPixelValue;
    unsigned char maxPixelValue;
    unsigned char averagePixelValue;

    getPixelStat(planeHistogram, minPixelValue, maxPixelValue, averagePixelValue);

    EXPECT_EQ(minPixelValue, 49);
    EXPECT_EQ(maxPixelValue, 255);
    EXPECT_EQ(averagePixelValue, 179);
}

TEST(Base, GetPixelStat)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, false);

    unsigned char minPixelValue;
    unsigned char maxPixelValue;
    unsigned char averagePixelValue;

    getPixelStat(plane, minPixelValue, maxPixelValue, averagePixelValue);

    EXPECT_EQ(minPixelValue, 49);
    EXPECT_EQ(maxPixelValue, 255);
    EXPECT_EQ(averagePixelValue, 179);
}