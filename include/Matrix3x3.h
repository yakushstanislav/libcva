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

#ifndef __CVA_MATRIX3X3_H__
#define __CVA_MATRIX3X3_H__

namespace CVA {

template<typename T>
class Matrix3x3 : public Matrix<Matrix3x3, T>
{
private:
    static const std::size_t ROWS = 3;
    static const std::size_t COLUMNS = 3;
    static const std::size_t DIMENSION = ROWS * COLUMNS;

public:
    Matrix3x3()
    {
        _data.fill(0);
    }

    Matrix3x3(const std::array<T, DIMENSION>& data)
    {
        _data = data;
    }

    Matrix3x3(
        const T n1, const T n2, const T n3,
        const T n4, const T n5, const T n6,
        const T n7, const T n8, const T n9)
    {
        _data[0] = n1;
        _data[1] = n2;
        _data[2] = n3;
        _data[3] = n4;
        _data[4] = n5;
        _data[5] = n6;
        _data[6] = n7;
        _data[7] = n8;
        _data[8] = n9;
    }

    inline T get(const std::size_t index) const override
    {
        assert(index < DIMENSION);

        return _data[index];
    }

    inline T get(const std::size_t row, const std::size_t column) const override
    {
        assert(row < ROWS && column < COLUMNS);

        return _data[row * COLUMNS + column];
    }

    inline void set(const std::size_t index, const T value) override
    {
        assert(index < DIMENSION);

        _data[index] = value;
    }

    inline void set(const std::size_t row, const std::size_t column, const T value) override
    {
        assert(row < ROWS && column < COLUMNS);

        _data[row * COLUMNS + column] = value;
    }

    inline Matrix3x3<T> transpose() const override
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < COLUMNS; i++)
        {
            for (std::size_t j = 0; j < ROWS; j++)
            {
                data[j * COLUMNS + i] = _data[i * COLUMNS + j];
            }
        }

        return data;
    }

    inline Matrix3x3<T> sort() const override
    {
        std::array<T, DIMENSION> data = _data;

        std::sort(data.begin(), data.end());

        return data;
    }

    inline T sum() const override
    {
        return std::accumulate(_data.begin(), _data.end(), (T)0);
    }

    inline std::size_t rows() const override
    {
        return ROWS;
    }

    inline std::size_t columns() const override
    {
        return COLUMNS;
    }

    inline std::size_t dimension() const override
    {
        return DIMENSION;
    }

    inline T operator[](const std::size_t index) const override
    {
        return get(index);
    }

    inline bool operator==(const Matrix3x3<T>& matrix) const override
    {
        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            if (_data[i] != matrix[i])
                return false;
        }

        return true;
    }

    inline Matrix3x3<T> operator+(const Matrix3x3<T>& matrix) const override
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] + matrix[i];
        }

        return data;
    }

    inline Matrix3x3<T> operator-(const Matrix3x3<T>& matrix) const override
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] - matrix[i];
        }

        return data;
    }

    inline Matrix3x3<T> operator*(const Matrix3x3<T>& matrix) const override
    {
        std::array<T, DIMENSION> data = { 0 };

        for (std::size_t i = 0; i < ROWS; i++)
        {
            for (std::size_t j = 0; j < COLUMNS; j++)
            {
                for (std::size_t k = 0; k < COLUMNS; k++)
                {
                    data[i * COLUMNS + j] += _data[i * COLUMNS + k] * matrix.get(k, j);
                }
            }
        }

        return data;
    }

    inline Matrix3x3<T> operator+(const T value) const override
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] + value;
        }

        return data;
    }

    inline Matrix3x3<T> operator-(const T value) const override
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] - value;
        }

        return data;
    }

    inline Matrix3x3<T> operator*(const T value) const override
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] * value;
        }

        return data;
    }

    inline Matrix3x3<T> operator/(const T value) const override
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] / value;
        }

        return data;
    }

private:
    std::array<T, DIMENSION> _data;
};

};

#endif
