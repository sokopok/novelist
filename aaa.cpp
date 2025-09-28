#include "aaa.h"

#include <utility>

class aaaData : public QSharedData
{
public:
};

aaa::aaa()
    : data(new aaaData)
{}

aaa::aaa(const aaa &rhs)
    : data{rhs.data}
{}

aaa::aaa(aaa &&rhs)
    : data{std::move(rhs.data)}
{}

aaa &aaa::operator=(const aaa &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

aaa &aaa::operator=(aaa &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

aaa::~aaa() {}
