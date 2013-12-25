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

#include <cstddef>

namespace CVA {

template<template<typename> class M, typename T>
class Matrix
{
public:
    virtual inline T get(std::size_t index) const = 0;

    virtual inline T get(std::size_t row, std::size_t column) const = 0;

    virtual inline void set(std::size_t index, T value) = 0;

    virtual inline void set(std::size_t row, std::size_t column, T value) = 0;

    virtual M<T> transpose() const = 0;

    virtual T sum() const = 0;

    virtual std::size_t rows() const = 0;

    virtual std::size_t columns() const = 0;

    virtual std::size_t dimension() const = 0;

    virtual bool operator==(const M<T>& matrix) const = 0;

    virtual M<T> operator+(const M<T>& matrix) const = 0;

    virtual M<T> operator-(const M<T>& matrix) const = 0;

    virtual M<T> operator*(const M<T>& matrix) const = 0;

    virtual M<T> operator+(const T value) const = 0;

    virtual M<T> operator-(const T value) const = 0;

    virtual M<T> operator*(const T value) const = 0;

    virtual M<T> operator/(const T value) const = 0;
};

};

#endif
