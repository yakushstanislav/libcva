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

#ifndef __CVA_DRAWING_H__
#define __CVA_DRAWING_H__

namespace CVA {

namespace Drawing {

// Bresenham's line algorithm
template<typename T>
void drawLine(ImagePlane<T>& plane, const Point& start, const Point& end, const T value)
{
    int x1 = start.getX();
    int y1 = start.getY();
    int x2 = end.getX();
    int y2 = end.getY();
    const int deltaX = std::abs(x2 - x1);
    const int deltaY = std::abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

    int error = deltaX - deltaY;

    plane.setPixel(x2, y2, value);

    while (x1 != x2 || y1 != y2)
    {
        plane.setPixel(x1, y1, value);

        const int error2 = error * 2;

        if (error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }

        if (error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

template<typename T>
void drawLines(ImagePlane<T>& plane, const std::vector<Point>& points, const T value)
{
    assert(points.size() >= 2);

    Point lastPoint = points[0];
    for (std::size_t i = 1; i < points.size(); i++)
    {
        drawLine(plane, lastPoint, points[i], value);
        lastPoint = points[i];
    }
}

template<typename T>
void drawRectangle(ImagePlane<T>& plane, const Point& start, const Point& end, const T value)
{
    drawLine(plane, start, Point(end.getX(), start.getY()), value);
    drawLine(plane, start, Point(start.getX(), end.getY()), value);
    drawLine(plane, Point(end.getX(), start.getY()), end, value);
    drawLine(plane, Point(start.getX(), end.getY()), end, value);
}

};

};

#endif
