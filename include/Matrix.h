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

#ifndef __CVA_MATRIX_H__
#define __CVA_MATRIX_H__

namespace CVA {

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
class Matrix
{
private:
    static const std::size_t DIMENSION = ROWS * COLUMNS;

public:
    Matrix()
    {
        _data.fill(0);
    }

    template<typename... Ts>
    Matrix(const Ts... args) :
        _data({args...})
    {
    }

    Matrix(const std::array<T, DIMENSION>& data) :
        _data(data)
    {
    }

    inline T get(const std::size_t index) const
    {
        assert(index < DIMENSION);

        return _data[index];
    }

    inline T get(const std::size_t row, const std::size_t column) const
    {
        assert(row < ROWS && column < COLUMNS);

        return _data[row * COLUMNS + column];
    }

    inline void set(const std::size_t index, const T value)
    {
        assert(index < DIMENSION);

        _data[index] = value;
    }

    inline void set(const std::size_t row, const std::size_t column, const T value)
    {
        assert(row < ROWS && column < COLUMNS);

        _data[row * COLUMNS + column] = value;
    }

    inline Matrix<T, ROWS, COLUMNS> transpose() const
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

    inline Matrix<T, ROWS, COLUMNS> sort() const
    {
        std::array<T, DIMENSION> data = _data;

        std::sort(data.begin(), data.end());

        return data;
    }

    inline T sum() const
    {
        return std::accumulate(_data.begin(), _data.end(), (T)0);
    }

    inline std::size_t rows() const
    {
        return ROWS;
    }

    inline std::size_t columns() const
    {
        return COLUMNS;
    }

    inline std::size_t dimension() const
    {
        return DIMENSION;
    }

    inline T operator[](const std::size_t index) const
    {
        return get(index);
    }

    inline bool operator==(const Matrix<T, ROWS, COLUMNS>& matrix) const
    {
        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            if (_data[i] != matrix[i])
                return false;
        }

        return true;
    }

    inline Matrix<T, ROWS, COLUMNS> operator+(const Matrix<T, ROWS, COLUMNS>& matrix) const
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] + matrix[i];
        }

        return data;
    }

    inline Matrix<T, ROWS, COLUMNS> operator-(const Matrix<T, ROWS, COLUMNS>& matrix) const
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] - matrix[i];
        }

        return data;
    }

    inline Matrix<T, ROWS, COLUMNS> operator*(const Matrix<T, ROWS, COLUMNS>& matrix) const
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

    inline Matrix<T, ROWS, COLUMNS> operator+(const T value) const
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] + value;
        }

        return data;
    }

    inline Matrix<T, ROWS, COLUMNS> operator-(const T value) const
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] - value;
        }

        return data;
    }

    inline Matrix<T, ROWS, COLUMNS> operator*(const T value) const
    {
        std::array<T, DIMENSION> data;

        for (std::size_t i = 0; i < DIMENSION; i++)
        {
            data[i] = _data[i] * value;
        }

        return data;
    }

    inline Matrix<T, ROWS, COLUMNS> operator/(const T value) const
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

template<typename T>
using Matrix3x3 = Matrix<T, 3, 3>;

};

#endif
