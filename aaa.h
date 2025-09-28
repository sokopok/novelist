#ifndef AAA_H
#define AAA_H

#include <QSharedDataPointer>

class aaaData;

class aaa
{
public:
    aaa();
    aaa(const aaa &);
    aaa(aaa &&);
    aaa &operator=(const aaa &);
    aaa &operator=(aaa &&);
    ~aaa();

private:
    QSharedDataPointer<aaaData> data;
};

#endif // AAA_H
