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

#ifndef __CVA_IMAGE_PLANE_H__
#define __CVA_IMAGE_PLANE_H__

namespace CVA {

template<typename T>
class ImagePlane
{
public:
    ImagePlane(const std::size_t width, const std::size_t height) :
        _width(width), _height(height), _stride(width), _isCopy(true)
    {
        _size = width * height;
        _data = new T[_size];
    }

    ImagePlane(const T* data, const std::size_t size, const std::size_t width, const std::size_t height,
        const std::size_t stride, const bool copy = false) :
        _size(size), _width(width), _height(height), _stride(stride), _isCopy(copy)
    {
        assert(data);

        if (_isCopy)
        {
            _data = new T[size];

            std::copy(data, data + size, _data);
        }
        else
        {
            _data = const_cast<T*>(data);
        }
    }

    ~ImagePlane()
    {
        if (_isCopy)
            delete _data;
    }

    inline T getPixel(const std::size_t index) const
    {
        assert(index < pixels());

        return _data[index];
    }

    inline T operator[](const std::size_t index) const
    {
        return getPixel(index);
    }

    inline T getPixel(const std::size_t x, const std::size_t y) const
    {
        assert(x < width() && y < height());

        return _data[y * _stride + x];
    }

    inline T* getPixelPtr(const std::size_t index) const
    {
        assert(index < pixels());

        return &_data[index];
    }

    inline T* getPixelPtr(const std::size_t x, const std::size_t y) const
    {
        assert(x < width() && y < height());

        return &_data[y * _stride + x];
    }

    inline void setPixel(const T value)
    {
        std::fill(_data, _data + _size, value);
    }

    inline void setPixel(const std::size_t index, const T value)
    {
        assert(index < pixels());

        _data[index] = value;
    }

    inline void setPixel(const std::size_t x, const std::size_t y, const T value)
    {
        assert(x < width() && y < height());

        _data[y * _stride + x] = value;
    }

    inline ImagePlane<T>& operator=(const ImagePlane<T>& plane)
    {
        assert(width() == plane.width() && height() == plane.height());

        for (std::size_t i = 0; i < pixels(); i++)
        {
            setPixel(i, plane[i]);
        }

        return *this;
    }

    inline bool operator==(const ImagePlane<T>& plane) const
    {
        assert(width() == plane.width() && height() == plane.height());

        for (std::size_t i = 0; i < plane.pixels(); i++)
        {
            if (getPixel(i) != plane[i])
                return false;
        }

        return true;
    }

    inline std::size_t pixels() const
    {
        return _size;
    }

    inline T* data() const
    {
        return _data;
    }

    inline std::size_t size() const
    {
        return _size * sizeof(T);
    }

    inline std::size_t width() const
    {
        return _width;
    }

    inline std::size_t height() const
    {
        return _height;
    }

    inline std::size_t stride() const
    {
        return _stride;
    }

private:
    T* _data;
    std::size_t _size;
    std::size_t _width;
    std::size_t _height;
    std::size_t _stride;
    bool _isCopy;
};

};

#endif
