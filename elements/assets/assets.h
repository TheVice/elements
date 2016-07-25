/*
The MIT License (MIT)
Copyright (c) 2016 Alexey Yegorov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#ifndef ASSETS_ASSETS_H_INCLUDED
#define ASSETS_ASSETS_H_INCLUDED

#include <string>
#include "utils/std/pointer.h"

namespace eps {

namespace io { struct system; }

struct asset
{
    asset()
    {}

    virtual ~asset()
    {}

    explicit asset(const std::string & resource)
        : resource_(resource)
    {}

    asset(const asset &) = delete;
    asset & operator=(const asset &) = delete;
    asset(asset &&) = default;
    asset & operator=(asset&&) = default;

    const std::string & get_resource() const { return resource_; }

public:

    virtual bool load(utils::link<io::system> fs, const std::string & resource) = 0;

private:

    std::string resource_;
};

} /* eps */

#endif // ASSET_ASSETS_H_INCLUDED
