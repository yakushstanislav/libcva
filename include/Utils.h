/*
   Copyright (c) 2015 Stanislav Yakush (st.yakush@yandex.ru)

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

#ifndef __CVA_UTILS_H__
#define __CVA_UTILS_H__

namespace CVA {

namespace Utils {

template<typename T>
bool saveFilePGM(const ImagePlane<T>& plane, const std::string& path)
{
    std::ofstream file(path, std::ios::out | std::ios::trunc | std::ios::binary);

    std::ostringstream ss;

    ss << "P5\n" << plane.width() << " " << plane.height() << "\n255\n";

    const std::string& header = ss.str();

    if (!file.is_open())
        return false;

    if (!file.write(const_cast<char*>(header.c_str()), header.size()))
        goto error;

    if (!file.write(reinterpret_cast<char*>(plane.data()), plane.size()))
        goto error;

    file.close();
    return true;

error:
    file.close();
    return false;
}

};

};

#endif