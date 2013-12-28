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
    ImagePlane(std::size_t width, std::size_t height, std::size_t stride) :
        _width(width), _height(height), _stride(stride), _isCopy(true)
    {
        _size = width * height;
        _data = new T[_size];

        std::fill(_data, _data + _size, 0);
    }

    ImagePlane(const T* data, std::size_t size, std::size_t width, std::size_t height, std::size_t stride, bool copy = false) :
        _size(size), _width(width), _height(height), _stride(stride), _isCopy(copy)
    {
        assert(data);

        if (_isCopy)
        {
            _data = new T[size];
            std::memcpy(_data, data, size);
        }
        else
        {
            _data = (T*)data;
        }
    }

    ~ImagePlane()
    {
        if (_isCopy)
            delete _data;
    }

    inline T getPixel(std::size_t index) const
    {
        assert(index < _width * _height);

        return _data[index];
    }

    inline T getPixel(std::size_t x, std::size_t y) const
    {
        assert(x < _width && y < _height);

        return _data[y * _stride + x];
    }

    inline void setPixel(std::size_t x, std::size_t y, T value)
    {
        assert(x < _width && y < _height);

        _data[y * _stride + x] = value;
    }

    inline T operator[](std::size_t index) const
    {
        return getPixel(index);
    }

    inline std::size_t pixels() const
    {
        return _width * _height;
    }

    inline T* data() const
    {
        return _data;
    }

    inline std::size_t size() const
    {
        return _size;
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
