#ifndef IHISTORY_H
#define IHISTORY_H

#include "../googletest/googlemock/include/gmock/gmock.h"
#include <string>
#include <vector>

class IHistory
{
public:
    virtual ~IHistory() {}

    virtual void add(std::string event) = 0;
    virtual std::string get(int i) = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual std::vector<std::string> getHistory() = 0;
};

#endif // IHISTORY_H