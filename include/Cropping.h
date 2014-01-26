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

// PNPOLY algorithm
static bool isPointInPolygon(const Point& point, const std::vector<Point>& points)
{
    bool result = false;

    for (size_t i = 0, j = points.size() - 1; i < points.size(); i++)
    {
        size_t x = point.getX();
        size_t y = point.getY();
        size_t currX = points[i].getX();
        size_t currY = points[i].getY();
        size_t prevX = points[j].getX();
        size_t prevY = points[j].getY();

        if (currY < y && prevY >= y || prevY < y && currY >= y)
        {
            if (currX + (y - currY) / (prevY - currY) * (prevX - currX) < x)
            {
                result = !result;
            }
        }

        j = i;
    }

    return result;
}

template<typename T>
bool cropPolygon(const ImagePlane<T>& src, ImagePlane<T>& dest, const std::vector<Point>& points)
{
    assert(points.size() >= 3);

    auto minMaxPointValueX = std::minmax_element(points.begin(), points.end(),
        [](Point pt1, Point pt2) { return pt1.getX() < pt2.getX(); });

    auto minMaxPointValueY = std::minmax_element(points.begin(), points.end(),
        [](Point pt1, Point pt2) { return pt1.getY() < pt2.getY(); });

    std::size_t minPointValueX = minMaxPointValueX.first->getX();
    std::size_t maxPointValueX = minMaxPointValueX.second->getX();

    std::size_t minPointValueY = minMaxPointValueY.first->getY();
    std::size_t maxPointValueY = minMaxPointValueY.second->getY();

    assert(dest.width() >= (maxPointValueX - minPointValueX) &&
        dest.height() >= (maxPointValueY - minPointValueY));

    for (std::size_t x = 0; x < src.width(); x++)
    {
        for (std::size_t y = 0; y < src.height(); y++)
        {
            if (isPointInPolygon(Point(x, y), points))
            {
                dest.setPixel(x - minPointValueX - 1, y - minPointValueY - 1, src.getPixel(x, y));
            }
        }
    }
}

template<typename T>
void cropRectangle(const ImagePlane<T>& src, ImagePlane<T>& dest, const Point& start, const Point& end)
{
    std::vector<Point> points;

    points.push_back(start);
    points.push_back(Point(end.getX(), start.getY()));
    points.push_back(end);
    points.push_back(Point(start.getX(), end.getY()));

    cropPolygon(src, dest, points);
}

};

};

#endif
