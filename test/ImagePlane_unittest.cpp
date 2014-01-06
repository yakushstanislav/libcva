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

#include "LenaGray8.h"

using namespace CVA;

TEST(ImagePlane, InitializationEmpty)
{
    const ImagePlane<unsigned char> plane1(128, 128, 128);
    const ImagePlane<unsigned long> plane2(4000, 4000, 4000);

    EXPECT_EQ(plane1.pixels(), 128 * 128);
    EXPECT_EQ(plane1.size(), plane1.pixels() * sizeof(unsigned char));
    EXPECT_EQ(plane1.width(), 128);
    EXPECT_EQ(plane1.height(), 128);
    EXPECT_EQ(plane1.stride(), 128);

    EXPECT_EQ(plane2.pixels(), 4000 * 4000);
    EXPECT_EQ(plane2.size(), plane2.pixels() * sizeof(unsigned long));
    EXPECT_EQ(plane2.width(), 4000);
    EXPECT_EQ(plane2.height(), 4000);
    EXPECT_EQ(plane2.stride(), 4000);
}

TEST(ImagePlane, InitializationImage)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, true);

    EXPECT_EQ(plane.pixels(), LENA_GRAY8_WIDTH * LENA_GRAY8_HEIGHT);
    EXPECT_EQ(plane.size(), plane.pixels() * sizeof(unsigned char));
    EXPECT_EQ(plane.width(), LENA_GRAY8_WIDTH);
    EXPECT_EQ(plane.height(), LENA_GRAY8_HEIGHT);
    EXPECT_EQ(plane.stride(), LENA_GRAY8_WIDTH);
}

TEST(ImagePlane, GetPixelByIndex)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, true);

    for (std::size_t i = 0; i < sizeof(lenaGray8); i++)
    {
        EXPECT_EQ(plane.getPixel(i), lenaGray8[i]);
        EXPECT_EQ(plane[i], lenaGray8[i]);
    }
}

TEST(ImagePlane, GetPixelPtrByIndex)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, true);

    for (std::size_t i = 0; i < sizeof(lenaGray8); i++)
    {
        EXPECT_EQ(*plane.getPixelPtr(i), lenaGray8[i]);
    }
}

TEST(ImagePlane, GetPixelByXY)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, true);

    for (std::size_t x = 0; x < plane.width(); x++)
    {
        for (std::size_t y = 0; y < plane.height(); y++)
        {
            EXPECT_EQ(plane.getPixel(x, y), lenaGray8[y * LENA_GRAY8_WIDTH + x]);
        }
    }
}

TEST(ImagePlane, GetPixelPtrByXY)
{
    const ImagePlane<unsigned char> plane(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, true);

    for (std::size_t x = 0; x < plane.width(); x++)
    {
        for (std::size_t y = 0; y < plane.height(); y++)
        {
            EXPECT_EQ(*plane.getPixelPtr(x, y), lenaGray8[y * LENA_GRAY8_WIDTH + x]);
        }
    }
}

TEST(ImagePlane, SetPixel)
{
    ImagePlane<unsigned char> plane(512, 512, 512);

    plane.setPixel(128);

    for (std::size_t i = 0; i < plane.pixels(); i++)
    {
        EXPECT_EQ(plane.getPixel(i), 128);
    }
}

TEST(ImagePlane, SetPixelByIndex)
{
    ImagePlane<unsigned char> plane(256, 256, 256);

    for (std::size_t i = 0; i < plane.pixels(); i++)
    {
        plane.setPixel(i, (unsigned char)i);
    }

    for (std::size_t i = 0; i < plane.pixels(); i++)
    {
        EXPECT_EQ(plane.getPixel(i), (unsigned char)i);
    }
}

TEST(ImagePlane, SetPixelByXY)
{
    ImagePlane<unsigned char> plane(256, 256, 256);

    for (std::size_t x = 0; x < plane.width(); x++)
    {
        for (std::size_t y = 0; y < plane.height(); y++)
        {
            plane.setPixel(x, y, (x + y) / 10);
        }
    }

    for (std::size_t x = 0; x < plane.width(); x++)
    {
        for (std::size_t y = 0; y < plane.height(); y++)
        {
            EXPECT_EQ(plane.getPixel(x, y), (x + y) / 10);
        }
    }
}

TEST(ImagePlane, Copy)
{
    ImagePlane<unsigned char> plane1(256, 256, 256);

    for (std::size_t x = 0; x < plane1.width(); x++)
    {
        for (std::size_t y = 0; y < plane1.height(); y++)
        {
            plane1.setPixel(x, y, (x + y) / 10);
        }
    }

    ImagePlane<unsigned char> plane2(256, 256, 256);

    plane2 = plane1;

    for (std::size_t x = 0; x < plane2.width(); x++)
    {
        for (std::size_t y = 0; y < plane2.height(); y++)
        {
            EXPECT_EQ(plane2.getPixel(x, y), (x + y) / 10);
        }
    }
}

TEST(ImagePlane, Compare)
{
    ImagePlane<unsigned char> plane1(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, true);
    ImagePlane<unsigned char> plane2(lenaGray8, sizeof(lenaGray8),
        LENA_GRAY8_WIDTH, LENA_GRAY8_HEIGHT, LENA_GRAY8_WIDTH, true);

    EXPECT_TRUE(plane1 == plane2);

    plane1.setPixel(128, plane1.getPixel(128) + 1);

    EXPECT_FALSE(plane1 == plane2);
}
